// usart.c
#include <avr/io.h>
#include <avr/interrupt.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "message_buffer.h"

#include "global.h"
#include "usart.h"
#include "kbd.h"

void USART0_SendBuf(char* str);

#define LOG_BUFFER_LEN 100

void _log(const char *format, ...) {
  char buffer[LOG_BUFFER_LEN];
  memset(buffer, 0, LOG_BUFFER_LEN);

  va_list args;
  va_start(args, format);

  uint8_t len = snprintf(buffer,
			 LOG_BUFFER_LEN,
			 format,
			 args);

  va_end(args);

  if (len + 2 <= LOG_BUFFER_LEN) {
    buffer[len] = '\n';
    buffer[len + 1] = '\r';
  }

  taskENTER_CRITICAL();
  xStreamBufferSend(g_log_tx_buffer_handle,
		    buffer + 1, // first byte will be sent in next command
		    len + 1, // buffer + <\n> + <\r> - <first byte>
		    0);
  taskEXIT_CRITICAL();
  USARTF0_DATA = buffer[0];
}

inline void USART0_init(void) {
  PORTF.OUTSET = PIN3_bm; // TX
  PORTF.DIRSET = PIN3_bm; // TX
  USARTF0.CTRLC = USART_CMODE_ASYNCHRONOUS_gc | USART_PMODE_DISABLED_gc
    | USART_CHSIZE_8BIT_gc;
  USARTF0.CTRLA |= USART_RXCINTLVL_LO_gc | USART_TXCINTLVL_LO_gc | USART_DREINTLVL_OFF_gc;
  USARTF0.BAUDCTRLA = 25; // 9600
  USARTF0.BAUDCTRLB = 0;

  g_log_tx_buffer_handle = xStreamBufferCreate(150, 1);

  USARTF0.CTRLB |= USART_TXEN_bm | USART_RXEN_bm | USART_CLK2X_bm |  USART_TXB8_bm;
}

StreamBufferHandle_t g_log_tx_buffer_handle;

ISR(USARTF0_TXC_vect) {
  char data;
  BaseType_t pxHPTW = pdFALSE;
  size_t read_count =
    xStreamBufferReceiveFromISR(g_log_tx_buffer_handle, // stream handle
				&data,           // buffer pointer
				1,               // buffer length
				&pxHPTW);
  if (read_count > 0)
    USARTF0_DATA = data;

  if (pxHPTW != pdFALSE )
    taskYIELD();
}

ISR(USARTF0_RXC_vect) {
  struct {
    char id;
    char key;
  } data;
  data.id = MSG_KBD;
  data.key = USARTF0_DATA;
  MessageBufferHandle_t* pHandle = context.mail + context.active_app_id;
  BaseType_t hptm1 = pdFALSE;
  BaseType_t hptm2 = pdFALSE;

  UBaseType_t uxSavedInterruptStatus;

  if (data.key >= '0' && data.key <= '9') {
    data.key -= '0';
    data.id = MSG_KBD;
    if (*pHandle != NULL) {
      uxSavedInterruptStatus = taskENTER_CRITICAL_FROM_ISR();
      xMessageBufferSendFromISR(*pHandle, (void*)&data, sizeof(data), &hptm1);
      taskEXIT_CRITICAL_FROM_ISR( uxSavedInterruptStatus );
    }

  } else if (data.key == 'x') {
    data.id = MSG_CLOSE;
    if (*pHandle != NULL) {
      uxSavedInterruptStatus = taskENTER_CRITICAL_FROM_ISR();
      xMessageBufferSendFromISR(*pHandle, (void*)&data, sizeof(char), &hptm1);
      taskEXIT_CRITICAL_FROM_ISR( uxSavedInterruptStatus );
    }

    data.id = MSG_DRAW;
    pHandle = context.mail + MENU_MAILBOX_ID;
    if (*pHandle != NULL) {
      uxSavedInterruptStatus = taskENTER_CRITICAL_FROM_ISR();
      xMessageBufferSendFromISR(*pHandle, (void*)&data, sizeof(char), &hptm2);
      taskEXIT_CRITICAL_FROM_ISR( uxSavedInterruptStatus );
    }
  }

  if ( hptm1 != pdFALSE || hptm2 != pdFALSE )
    taskYIELD();
}

inline void USART0_SendByte(char c) {
  while( !(USARTF0_STATUS & USART_DREIF_bm) ); //Wait until DATA buffer is empty
  USARTF0_DATA = c;
}

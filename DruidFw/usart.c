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


#define LOG_BUFFER_LEN 35

void _log(const char *format, ...) {
  char buffer[LOG_BUFFER_LEN];
  memset(buffer, 0, LOG_BUFFER_LEN);

  va_list args;
  va_start(args, format);

  uint8_t len = vsprintf(buffer,
			  format,
			  args);

  va_end(args);

  if (len + 2 <= LOG_BUFFER_LEN) {
    buffer[len] = '\n';
    buffer[len + 1] = '\r';
  } else {
    buffer[LOG_BUFFER_LEN - 1] = '\n';
    buffer[LOG_BUFFER_LEN - 2] = '\r';
  }

  taskENTER_CRITICAL();
  xStreamBufferSend(g_log_tx_buffer_handle,
		    buffer + 1, // first byte will be sent in next command
		    len + 1, // buffer + <\n> + <\r> - <first byte>
		    0);
  taskEXIT_CRITICAL();
  USARTF0_DATA = buffer[0];

  //while(xMessageBufferIsEmpty(g_log_tx_buffer_handle) != pdTRUE) {}
}

inline void USART0_init(void) {
  PORTF.OUTSET = PIN3_bm; // TX
  PORTF.DIRSET = PIN3_bm; // TX
  USARTF0.CTRLC = USART_CMODE_ASYNCHRONOUS_gc | USART_PMODE_DISABLED_gc
    | USART_CHSIZE_8BIT_gc;
  USARTF0.CTRLA |= USART_RXCINTLVL_LO_gc | USART_TXCINTLVL_LO_gc | USART_DREINTLVL_OFF_gc;
  USARTF0.BAUDCTRLA = 25; // 9600
  USARTF0.BAUDCTRLB = 0;

  g_log_tx_buffer_handle = xStreamBufferCreate(1000, 1);

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

#define SendMsg(HANDLE, DATA, SIZE) ({                                  \
      BaseType_t hptm_ = pdFALSE;                                       \
      UBaseType_t uxSavedInterruptStatus_;                              \
                                                                        \
      uxSavedInterruptStatus_ = taskENTER_CRITICAL_FROM_ISR();          \
      xMessageBufferSendFromISR(HANDLE, DATA, SIZE, &hptm_);            \
      taskEXIT_CRITICAL_FROM_ISR( uxSavedInterruptStatus_ );            \
      (hptm_ == pdTRUE);                                                \
    })

ISR(USARTF0_RXC_vect) {
  struct {
    char id;
    char key;
  } data;

  data.id = MSG_KBD;
  data.key = USARTF0_DATA;
  bool need_yield = false;

  if (data.key >= '0' && data.key <= '9') {
    data.key -= '0';
    data.id = MSG_KBD;
    for (uint8_t i = 0; i < MAILBOX_SIZE; i++) {
      need_yield |= SendMsg(context.mail[i], (void*)&data, sizeof(data));
    }
  } else if (data.key == 'x') {
    data.id = MSG_CLOSE;

    for (uint8_t i = 0; i < MAILBOX_SIZE; i++) {
      need_yield |= SendMsg(context.mail[i], (void*)&(data.id), sizeof(char));
    }
  }

  if ( need_yield )
    taskYIELD();
}

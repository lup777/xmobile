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

StreamBufferHandle_t g_log_tx_buffer_handle;

void _log(const char *format, ...) {
  char buffer[LOG_BUFFER_LEN];
  //memset(buffer, 0, LOG_BUFFER_LEN);

  va_list args;
  va_start(args, format);

  uint8_t len = vsnprintf(buffer,
        (size_t)LOG_BUFFER_LEN,
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
		    buffer, // first byte will be sent in next command
		    len + 2, // buffer + <\n> + <\r> - <first byte>
		    0);
  taskEXIT_CRITICAL();
  USARTF0.CTRLA |= USART_DREINTLVL_LO_gc;

  //while(xMessageBufferIsEmpty(g_log_tx_buffer_handle) != pdTRUE) {}
}

inline void USART0_init(void) {
  PORTF.OUTSET = PIN3_bm; // TX
  PORTF.DIRSET = PIN3_bm; // TX
  USARTF0.CTRLC = USART_CMODE_ASYNCHRONOUS_gc | USART_PMODE_DISABLED_gc
    | USART_CHSIZE_8BIT_gc;
  USARTF0.CTRLA = USART_RXCINTLVL_LO_gc
    | USART_TXCINTLVL_OFF_gc
    | USART_DREINTLVL_OFF_gc;
  //USARTF0.BAUDCTRLA = 25; // 9600
  //USARTF0.BAUDCTRLB = 0; // 9600
  USARTF0.BAUDCTRLA = 19; // 115200
  USARTF0.BAUDCTRLB = 0xC0; // 115200
  //https://planetcalc.ru/747/
  //https://www.dolman-wim.nl/xmega/tools/baudratecalculator/index.php
  g_log_tx_buffer_handle = xStreamBufferCreate(1000, 1);

  USARTF0.CTRLB = USART_TXEN_bm | USART_RXEN_bm | USART_CLK2X_bm |  USART_TXB8_bm;
}

ISR(USARTF0_DRE_vect) {
//ISR(USARTF0_TXC_vect) {
  char data;
  BaseType_t pxHPTW = pdFALSE;
  size_t read_count =
    xStreamBufferReceiveFromISR(g_log_tx_buffer_handle, // stream handle
				&data,           // buffer pointer
				1,               // buffer length
				&pxHPTW);
  if (read_count == 1) {
    USARTF0_DATA = data;
  }
  else
    USARTF0.CTRLA |= USART_DREINTLVL_OFF_gc;

  if (pxHPTW != pdFALSE )
    taskYIELD();
}

ISR(USARTF0_RXC_vect) {
  struct {
    char id;
    char key;
  } data;
  //_log("-");
  data.id = MSG_KBD;
  data.key = USARTF0_DATA;
  bool need_yield = false;

  if (data.key >= '0' && data.key <= '9') {
    data.key -= '0';
    data.id = MSG_KBD;
    for (uint8_t i = 0; i < MAILBOX_SIZE; i++) {
      need_yield |= SendMsg(context.mail[i], &data, sizeof(data));
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

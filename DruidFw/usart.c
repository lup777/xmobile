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
  //return;
  char buffer[LOG_BUFFER_LEN];
  //memset(buffer, 0, LOG_BUFFER_LEN);
  while(xMessageBufferIsEmpty(g_log_tx_buffer_handle) != pdTRUE) {}

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

#if 0
  taskENTER_CRITICAL();
  xStreamBufferSend(g_log_tx_buffer_handle,
		    buffer, // first byte will be sent in next command
		    len + 2, // buffer + <\n> + <\r> - <first byte>
		    0);
  taskEXIT_CRITICAL();
  USARTE1.CTRLA |= USART_DREINTLVL_LO_gc;
#else
  for(uint8_t i = 0; i < len + 2; i ++) {
    while((USARTE1.STATUS & USART_DREIF_bm) == 0) {};
    USARTE1_DATA = buffer[i];
  }
#endif
}

inline void logc(char c) {
  while((USARTE1.STATUS & USART_DREIF_bm) == 0) {};
  USARTE1_DATA = c;

}

inline void logcl(const char* str) {
  size_t size = strlen(str);
  size_t i = 0;
  for(; i< size; i++) {
    logc( str[i] );
  }
}

inline void log_init(void) {
  PORTE.OUTSET = PIN7_bm; // TX
  PORTE.DIRSET = PIN7_bm; // TX
  USARTE1.CTRLC = USART_CMODE_ASYNCHRONOUS_gc | USART_PMODE_DISABLED_gc
    | USART_CHSIZE_8BIT_gc;
  USARTE1.CTRLA = USART_RXCINTLVL_LO_gc
    | USART_TXCINTLVL_OFF_gc
    | USART_DREINTLVL_OFF_gc;

  uint16_t bsel = 1079;
  uint8_t bscale = 5;
  USARTE1.BAUDCTRLA = bsel & 0xff; // 115200  - 32MGz internal osc
  USARTE1.BAUDCTRLB =
    (bsel >> 8) | ((16 - bscale) << 4); // 115200  - 32MGz internal osc
  //https://planetcalc.ru/747/
  //https://www.dolman-wim.nl/xmega/tools/baudratecalculator/index.php
  g_log_tx_buffer_handle = xStreamBufferCreate(500, 1);

  USARTE1.CTRLB = USART_TXEN_bm | USART_RXEN_bm | USART_CLK2X_bm |  USART_TXB8_bm;
}

ISR(USARTE1_DRE_vect) {
//ISR(USARTF0_TXC_vect) {
  char data;
  BaseType_t pxHPTW = pdFALSE;
  size_t read_count =
    xStreamBufferReceiveFromISR(g_log_tx_buffer_handle, // stream handle
				&data,           // buffer pointer
				1,               // buffer length
				&pxHPTW);
  if (read_count == 1) {
    USARTE1_DATA = data;
  }
  else
    USARTE1.CTRLA |= USART_DREINTLVL_OFF_gc;

  if (pxHPTW != pdFALSE )
    taskYIELD();
}

ISR(USARTF0_RXC_vect) {
  struct {
    char id;
    char key;
  } data;

  data.id = MSG_KBD;
  data.key = USARTE1_DATA;
  bool need_yield = false;

  for (uint8_t i = 0; i < MAILBOX_SIZE; i++) {
    need_yield |= SendMsgISR(context.mail[i], &data, sizeof(data));
  }

  if ( need_yield )
    taskYIELD();
}

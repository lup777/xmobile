// usart.c
#include <avr/io.h>
#include <avr/interrupt.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>

#include "FreeRTOS.h"
#include "task.h"
#include "stream_buffer.h"

#include "global.h"

#define LOG_BUFFER_LEN 20

#ifndef DISABLE_LOGS
void send_log_str(char* data, byte len);
#endif

#ifndef DISABLE_LOGS
void _log(const char *format, ...) {
  char buffer[LOG_BUFFER_LEN];

  va_list args;
  va_start(args, format);

  uint8_t len = vsnprintf(buffer,
        (size_t)LOG_BUFFER_LEN,
        format,
        args);

  va_end(args);
  if (len + 2 <= LOG_BUFFER_LEN) {
    buffer[len] = '\r';
    buffer[len + 1] = '\n';
  } else {
    buffer[LOG_BUFFER_LEN - 1] = '\r';
    buffer[LOG_BUFFER_LEN - 2] = '\n';
  }

  send_log_str(buffer, len + 2);
}
#endif

#ifndef DISABLE_LOGS
inline void logc(char c) {
  send_log_str(&c, 1);
}
#endif

#ifndef DISABLE_LOGS
inline void logcl(const char* str) {
  send_log_str((char*)str, strlen(str));
}
#endif

#ifndef DISABLE_LOGS
inline void send_log_str(char* data, byte len) {
  taskENTER_CRITICAL();
  xStreamBufferSend(log_buf_handle, &data, len, 0);
  taskEXIT_CRITICAL();
}
#endif

inline void log_init(void) {
  PORTE.OUTSET = PIN7_bm; // TX
  PORTE.DIRSET = PIN7_bm; // TX
  USARTE1.CTRLC = USART_CMODE_ASYNCHRONOUS_gc | USART_PMODE_DISABLED_gc
    | USART_CHSIZE_8BIT_gc;
  USARTE1.CTRLA = USART_RXCINTLVL_OFF_gc
    | USART_TXCINTLVL_OFF_gc
    | USART_DREINTLVL_OFF_gc;

  uint16_t bsel = 1079;
  uint8_t bscale = 5;
  USARTE1.BAUDCTRLA = bsel & 0xff; // 115200  - 32MGz internal osc
  USARTE1.BAUDCTRLB =
    (bsel >> 8) | ((16 - bscale) << 4); // 115200  - 32MGz internal osc
  // https://planetcalc.ru/747/
  // https://www.dolman-wim.nl/xmega/tools/baudratecalculator/index.php
  USARTE1.CTRLB = USART_TXEN_bm | USART_RXEN_bm | USART_CLK2X_bm |  USART_TXB8_bm;
}

/*ISR(USARTE1_DRE_vect) {}
ISR(USARTF0_RXC_vect) {}*/

#ifndef DISABLE_LOGS
void vLogTask(void* pvParameters) {
  (void)(pvParameters);
  char buf[LOG_BUFFER_LEN];
  size_t i = 0;

  for (;;) { // loop
    size_t rx = xStreamBufferReceive(log_buf_handle, &buf, LOG_BUFFER_LEN, portMAX_DELAY);

    for (i = 0; i < rx; i++) {
      while((USARTE1.STATUS & USART_DREIF_bm) == 0) {};

      USARTE1_DATA = buf[i];
    }
  }
}
#endif

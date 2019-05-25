// usart.c
#include <avr/io.h>
#include <avr/interrupt.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>

#include "FreeRTOS.h"
#include "task.h"
#include "stream_buffer.h"
#include "semphr.h"

#include "global.h"

#define LOG_BUFFER_LEN 40

// ======== Semaphore ======================
SemaphoreHandle_t mutex_handle = NULL;
StaticSemaphore_t mutex_buffer;
// =========================================


#ifndef DISABLE_LOGS
void __log(const char *format, ...) {
  //void __log(PGM_P format, ...) {
  char buffer[LOG_BUFFER_LEN];
  
  va_list args;
  va_start(args, format);

  size_t len = vsnprintf(buffer, LOG_BUFFER_LEN,
			  format, args);

  va_end(args); 

  send_log_str(buffer, len + 1);
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

void send_log_str(char* data, byte len) {
  size_t i = 0;
    //taskENTER_CRITICAL();

  if (xSemaphoreTake(mutex_handle, 0) != pdTRUE)
    return;
  
  for (i = 0; i < len; i++) {
    while((USARTE1.STATUS & USART_DREIF_bm) == 0) {};
    USARTE1_DATA = data[i];
  }
  while((USARTE1.STATUS & USART_DREIF_bm) == 0) {};
  USARTE1_DATA = '\r';

  while((USARTE1.STATUS & USART_DREIF_bm) == 0) {};
  USARTE1_DATA = '\n';

  xSemaphoreGive(mutex_handle);

}
#endif

inline void log_init(void) {

  mutex_handle = xSemaphoreCreateMutexStatic(&mutex_buffer);
  
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
  /*char buf[90];
  raw_logc("_0_");

  for (;;) { // loop
    size_t size = xMessageBufferReceive(log_msg_buf_handle, buf, 90, portMAX_DELAY);
    byte i = 0;
    raw_logc("_2_");
    
    for (i = 0; i < size; i++) {
      while((USARTE1.STATUS & USART_DREIF_bm) == 0) {};
      USARTE1_DATA = buf[i];
    }
    }*/
}
#endif

void raw_logc(const char* str) {
  size_t i = 0;

  if (xSemaphoreTake(mutex_handle, 0) != pdTRUE)
    return;
  
  for (i = 0; i < strlen(str); i++) {
    while((USARTE1.STATUS & USART_DREIF_bm) == 0) {};
    USARTE1_DATA = str[i];
  }
  while((USARTE1.STATUS & USART_DREIF_bm) == 0) {};
  USARTE1_DATA = '\r';
  while((USARTE1.STATUS & USART_DREIF_bm) == 0) {};
  USARTE1_DATA = '\n';

  xSemaphoreGive(mutex_handle);
}

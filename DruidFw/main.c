// main.c

#include <avr/io.h>
#include <stdbool.h>
#include <string.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>

#include "global.h"
#include "core_drv.h"

typedef unsigned char byte;

void log_init(void);
void send_log_str(char* data, byte len);

void log_init(void) {
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


void send_log_str(char* data, byte len) {
  size_t i = 0;

  for (i = 0; i < len; i++) {
    while((USARTE1.STATUS & USART_DREIF_bm) == 0) {};
    USARTE1_DATA = data[i];
  }

  while((USARTE1.STATUS & USART_DREIF_bm) == 0) {};
  USARTE1_DATA = '\r';

  while((USARTE1.STATUS & USART_DREIF_bm) == 0) {};
  USARTE1_DATA = '\n';
}

#define LOG_BUFFER_LEN 40

void _log(const char *format, ...) {
  //void __log(PGM_P format, ...) {
  char buffer[LOG_BUFFER_LEN];
  
  va_list args;
  va_start(args, format);

  size_t len = vsnprintf(buffer, LOG_BUFFER_LEN,
			  format, args);

  va_end(args); 

  send_log_str(buffer, len + 1);
}

int main(void) {
  clk_init();
  log_init();
  sram_init();

  check_sram();

  int j = 0;
  
  while(1) {
    for (j = 0; j < 10000; j++) {
      int k = 0;
      for (k = 0; k < 1000; k++) {}
    }
    send_log_str("hello!", 6);
  }

  return 0;
}

// gsm.c

#include "gsm.h"

#include <string.h>

#include "spi.h"
#include "kbd.h"

void GSM_SendByte(char c);
void GSM_SendCStr(const char* str);
void GSM_SendStr(char* str, uint8_t len);
char GSM_ReadByte(void);

// http://codius.ru/articles/GSM_%D0%BC%D0%BE%D0%B4%D1%83%D0%BB%D1%8C_SIM800L_%D1%87%D0%B0%D1%81%D1%82%D1%8C_1

static TimerHandle_t timerId;

void GSM_Init(void) {
  _clog("GSM Start gsm init");
  PORTD.DIRSET = PIN0_bm;
  PORTD.OUTSET = PIN0_bm;

  // USARTE0

  PORTE.DIRSET = PIN3_bm;
  PORTE.OUTSET = PIN3_bm;

  USARTE0.CTRLC = USART_CMODE_ASYNCHRONOUS_gc | USART_PMODE_DISABLED_gc
    | USART_CHSIZE_8BIT_gc;

  USARTE0.CTRLA = USART_RXCINTLVL_gm | USART_TXCINTLVL_gm | USART_DREINTLVL_gm
    | USART_RXCINTLVL_LO_gc | USART_TXCINTLVL_OFF_gc | USART_DREINTLVL_OFF_gc;

  USARTE0.BAUDCTRLA = 25;
  USARTE0.BAUDCTRLB = 0;//((0x09 << USART_BSCALE_bp) & USART_BSCALE_gm) | 0x0C;

  USARTE0.CTRLB = USART_TXEN_bm | USART_RXEN_bm | USART_CLK2X_bm |  USART_TXB8_bm;

  timerId = xTimeCreate("gsmtimer", period, autoreload, );

  GSM_SendCStr("AT");

  _clog("waiting for GSM responce");
  char buf[2];
  _clog("waite 1st byte");
  buf[0] = GSM_ReadByte();
  _clog("waite 2nd byte");
  buf[1] = GSM_ReadByte();

  _clog("GSM responce received");
  EPD_ShowString(buf, 2, 1, 180);
  KBD_WaiteKey();
}


inline void GSM_ConfigureSpeed(void) {
  GSM_SendCStr("AT");
}

inline void GSM_SetNumericResponceFormat(void) {
  GSM_SendCStr("ATV0");
}

void GSM_SendCStr(const char* str) {
  volatile uint8_t i = 0;
  const uint8_t len = strlen(str);
  for(i = 0; i < len; i++) {
    GSM_SendByte(str[i]);
  }
  GSM_SendByte('\n');
}

void GSM_SendStr(char* str, uint8_t len) {
  volatile uint8_t i = 0;
  for(i = 0; i < len; i++) {
    GSM_SendByte(str[i]);
  }
}

void GSM_SendByte(char c) {
  while( !(USARTE0_STATUS & USART_DREIF_bm) ); //Wait until DATA buffer is empty
  USARTE0_DATA = c;
}

char GSM_ReadByte(uint16_t delay_ms) {
  volatile TickType_t begin_time = xTaskGetTickCount();
  while(1) {
    if (USARTE0.STATUS & USART_RXCIF_bm)
      return USARTC0.DATA;
    else if (xTaskGetTickCount() - begin_time > delay_ms)
      return 127; // fail
    else
      taskYIELD();
  }
}

// Responce format: "\r\n<responce>\r\n"

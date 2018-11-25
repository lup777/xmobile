// gsm.c

#include "gsm.h"

#include <string.h>

#include "spi.h"
#include "kbd.h"

void GSM_SendByte(char c);
void GSM_SendCStr(const char* str);
void GSM_SendStr(char* str, uint8_t len);
char GSM_ReadByte(void);

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

  GSM_SendCStr("AT");

  char buf[2];
  buf[0] = GSM_ReadByte();
  buf[1] = GSM_ReadByte();
  _clog("waiting for GSM responce");
  EPD_ShowString(buf, 2, 1, 180);
  Key key = keyNo;
  do {
    key = KBD_Check();
  } while(key == keyNo);
  
}

void GSM_SendCStr(const char* str) {
  volatile uint8_t i = 0;
  const uint8_t len = strlen(str);
  for(i = 0; i < len; i++) {
    GSM_SendByte(str[i]);
  }
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

char GSM_ReadByte(void) {
    while( !(USARTE0.STATUS & USART_RXCIF_bm) );
    return USARTC0.DATA;
}

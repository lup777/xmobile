// gsm.c

#include "gsm.h"

#include "FreeRTOS.h"
#include "task.h"
#include "message_buffer.h"

#include <string.h>
#include <avr/interrupt.h>

#include "global.h"
#include "spi.h"
#include "kbd2.h"

#define READ_BUFFER_SIZE 255

void GSM_CallCmd(const char* msg);
void GSM_SendCStr(const char* str);
void GSM_SendStr(char* str, uint8_t len);
bool GSM_SendByte(char c, uint16_t delay_ms);
bool GSM_ReadByte(char* out, uint16_t delay_ms);
char GSM_ReadResultCode(uint16_t delay_ms, char* out);

// new 
void send_byte(char byte);

// http://codius.ru/articles/GSM_%D0%BC%D0%BE%D0%B4%D1%83%D0%BB%D1%8C_SIM800L_%D1%87%D0%B0%D1%81%D1%82%D1%8C_1

char rbuf[READ_BUFFER_SIZE];
char gresult;

void GSM_Init(void) {
  //_log("GSM Start gsm init");
  // PA2 - status
  PORTA.DIRCLR = PIN2_bm; // status
  
  PORTD.DIRSET = PIN0_bm;
  PORTD.OUTCLR = PIN0_bm;

  vTaskDelay((TickType_t)(1000 / portTICK_PERIOD_MS));
  
  //gsm_msg_buffer = xMessageBufferCreate( 10 );
  
  PORTD.OUTSET = PIN0_bm;

  // USARTE0

  PORTE.DIRCLR = PIN2_bm; // Rx
  PORTE.DIRSET = PIN3_bm; // Tx
  PORTE.OUTCLR = PIN4_bm; // Tx 

  USARTE0.CTRLC = USART_CMODE_ASYNCHRONOUS_gc | USART_PMODE_DISABLED_gc
    | USART_CHSIZE_8BIT_gc;

  USARTE0.CTRLA =
    USART_RXCINTLVL_LO_gc
    | USART_TXCINTLVL_OFF_gc
    | USART_DREINTLVL_OFF_gc;

  uint16_t bsel = 1079;
  uint8_t bscale = 5;
  USARTE0.BAUDCTRLA = bsel & 0xff; // 115200  - 32MGz internal osc
  USARTE0.BAUDCTRLB =
    (bsel >> 8) | ((16 - bscale) << 4); // 115200  - 32MGz internal osc

  USARTE0.CTRLB = USART_TXEN_bm | USART_RXEN_bm | USART_CLK2X_bm /*| USART_TXB8_bm*/;

  //_log("wait for gsm boot");
  //vTaskDelay((TickType_t)(50000 / portTICK_PERIOD_MS));
  
  //send_byte("AT\n", 3);
  _log("GSM init completed");
}

inline bool gsm_status(void) {
  return ((PORTA.IN & PIN2_bm) != 0);
}

inline void send_byte(char data) {
  while((USARTE0.STATUS & USART_DREIF_bm) == 0) {};
  USARTE0.DATA = data;
}

void send_str(char* data, size_t len) {
  size_t i = 0;
  for(; i < len; i++) {
    send_byte(data[i]);
  }
}

ISR(USARTE0_TXC_vect) {
}

ISR(USARTE0_RXC_vect) {
  char data;
  data = USARTE0.DATA;

  _log("GSM: %c", data);
}

// Responce format: "\r\n<responce>\r\n"

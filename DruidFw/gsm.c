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
#include "task_mgr.h"

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

//char rbuf[READ_BUFFER_SIZE];
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

  uint16_t bsel = 68;
  uint8_t bscale = 0;
  USARTE0.BAUDCTRLA = bsel & 0xff; // 115200  - 32MGz internal osc
  USARTE0.BAUDCTRLB =
    (bsel >> 8) | ((16 - bscale) << 4); // 115200  - 32MGz internal osc

  USARTE0.CTRLB = USART_TXEN_bm | USART_RXEN_bm | USART_CLK2X_bm /*| USART_TXB8_bm*/;

  //_log("wait for gsm boot");
  //vTaskDelay((TickType_t)(50000 / portTICK_PERIOD_MS));

  //send_byte("AT\n", 3);
  _log("waiting for gsm init");
  while( gsm_status() == false );
  _sleep(1000);
  send_str("AT\n\r", 4);
  _sleep(1000);
  send_str("ATE\n\r", 5);
  _sleep(1000);
  send_str("AT+GSN\n\r", 8);
  _sleep(1000);
  send_str("AT+CLVL=8\n\r", 11);
  _sleep(1000);
  send_str("AT+COPS?\n\r", 10);
  _sleep(1000);
  send_str("AT+CRSL=15\n\r", 12);
  _sleep(1000);
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

void send_cstr(const char* data) {
  size_t len = strlen(data);
  size_t i = 0;
  for(; i < len; i++) {
    send_byte( data[i] );
  }
}

void gsm_get_signal_quality(void) {
  send_cstr("AT+CSQ\r\n");
}

ISR(USARTE0_TXC_vect) {
}

ISR(USARTE0_RXC_vect) {
  unsigned char data;
  BaseType_t need_yeld = pdFALSE;
  static unsigned char buffer[50];
  static int idx = 1;

  data = USARTE0.DATA;

  buffer[idx] = data;
  idx++;

  if (idx > 2                     &&
      buffer[idx - 2] == '\r'     &&
      buffer[idx - 1] == '\n'     &&
      idx < 45) {
    buffer[0] = MSG_HEADER_GSM;
    xMessageBufferSendFromISR(tm_msg_buf_handle,
			      buffer,
			      idx - 2,
			      &need_yeld);
    idx = 1;
  }

  if (need_yeld == pdTRUE)
    taskYIELD();
}

// Responce format: "\r\n<responce>\r\n"

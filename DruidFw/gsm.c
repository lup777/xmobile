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
void gsm_sendcstr(char* str, uint8_t len);
bool GSM_SendByte(char c, uint16_t delay_ms);
bool GSM_ReadByte(char* out, uint16_t delay_ms);
char GSM_ReadResultCode(uint16_t delay_ms, char* out);
void gsm_send_cmd_end(void);

// new
void send_byte(char byte);

// http://codius.ru/articles/GSM_%D0%BC%D0%BE%D0%B4%D1%83%D0%BB%D1%8C_SIM800L_%D1%87%D0%B0%D1%81%D1%82%D1%8C_1

//char rbuf[READ_BUFFER_SIZE];
char gresult;

void GSM_Init(void) {
  //_log("GSM Start gsm init");
  // PA2 - status

  PORTD.DIRSET = PIN0_bm; // power key
  PORTD.OUTSET = PIN0_bm; // power key releas//PORTD.OUTCLR = PIN0_bm;

  //vTaskDelay((TickType_t)(1000 / portTICK_PERIOD_MS));

  //gsm_msg_buffer = xMessageBufferCreate( 10 );

  PORTA.DIRCLR = PIN2_bm; // status
  PORTD.DIRCLR = PIN1_bm; // RI
  
  PORTE.DIRCLR = PIN2_bm; // Rx
  PORTE.DIRSET = PIN3_bm; // Tx
  PORTE.DIRCLR = PIN0_bm; // PE0 RTS (open) request to send
  PORTD.DIRCLR = PIN4_bm; // CTS clear to send PD4
  PORTD.DIRCLR = PIN3_bm; // DTR data terminal ready PD3
  PORTD.DIRCLR = PIN2_bm; // DCD data carrier detect PD2
  

  USARTE0.CTRLC = USART_CMODE_ASYNCHRONOUS_gc | USART_PMODE_DISABLED_gc
    | USART_CHSIZE_8BIT_gc;

  USARTE0.CTRLA =
    USART_RXCINTLVL_LO_gc
    | USART_TXCINTLVL_OFF_gc
    | USART_DREINTLVL_OFF_gc;

  uint16_t bsel = 1079;//68;
  uint8_t bscale = 5;//0;
  USARTE0.BAUDCTRLA = bsel & 0xff; // 115200  - 32MGz internal osc
  USARTE0.BAUDCTRLB =
    (bsel >> 8) | ((16 - bscale) << 4); // 115200  - 32MGz internal osc

  USARTE0.CTRLB = USART_TXEN_bm | USART_RXEN_bm | USART_CLK2X_bm /*| USART_TXB8_bm*/;

  _log("GSM init completed");
}

bool gsm_status(void) {
  return ((PORTA.IN & PIN2_bm) != 0);
}

void send_byte(char data) {
  while((USARTE0.STATUS & USART_DREIF_bm) == 0) {};
  USARTE0.DATA = data;
}

void gsm_send_str(char* data, size_t len) {
  gsm_send_str_ne(data, len);
  gsm_send_cmd_end();
}
void gsm_send_str_ne(char* data, size_t len) {
  size_t i = 0;

  for(; i < len; i++) {
    send_byte(data[i]);
  }
}
void gsm_send_cstr(const char* data) {
  gsm_send_str((char*)data, strlen(data));
}

void gsm_send_cstr_ne(const char* data) {
  gsm_send_str_ne((char*)data, strlen(data));
}

void gsm_send_cmd_end(void) {
  send_byte('\r');
}

ISR(USARTE0_TXC_vect) {
}

ISR(USARTE0_RXC_vect) {
  unsigned char data;
  BaseType_t need_yeld = pdFALSE;
  static unsigned char buffer[50];
  static int idx = 1;

  buffer[idx] = USARTE0.DATA;
  data = USARTE0.DATA;
  
  if (idx >= 50)
    idx = 1;
  
  buffer[idx] = data;

  if ((buffer[idx] != '\r') && (buffer[idx] != '\n')) {
    idx++;
  } else {
    if (idx > 2) {
      buffer[0] = MSG_HEADER_GSM;
      xMessageBufferSendFromISR(tm_msg_buf_handle,
				buffer,
				idx,
				&need_yeld);
      idx = 1;
    }
  }

  if (need_yeld == pdTRUE)
    taskYIELD();
}

// Responce format: "\r\n<responce>\r\n"

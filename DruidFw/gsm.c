// gsm.c

#include "gsm.h"

#include "FreeRTOS.h"
#include "task.h"
#include "message_buffer.h"

#include <string.h>
#include <avr/interrupt.h>

#include "global.h"
#include "spi.h"
#include "kbd.h"

#define READ_BUFFER_SIZE 255

void GSM_CallCmd(const char* msg);
void GSM_SendCStr(const char* str);
void GSM_SendStr(char* str, uint8_t len);
bool GSM_SendByte(char c, uint16_t delay_ms);
bool GSM_ReadByte(char* out, uint16_t delay_ms);
char GSM_ReadResultCode(uint16_t delay_ms, char* out);

// http://codius.ru/articles/GSM_%D0%BC%D0%BE%D0%B4%D1%83%D0%BB%D1%8C_SIM800L_%D1%87%D0%B0%D1%81%D1%82%D1%8C_1

char rbuf[READ_BUFFER_SIZE];
char gresult;

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

  _clog("waiting for GSM responce");
  GSM_ReadByte(rbuf, 1000);
  GSM_ReadByte(rbuf + 1, 1000);
  GSM_ReadByte(rbuf + 2, 1000);
  GSM_ReadByte(rbuf + 3, 1000);
  GSM_ReadByte(rbuf + 4, 1000);
  GSM_ReadByte(rbuf + 5, 1000);

  _clog("GSM responce received");
  /*EPD_ShowString(rbuf + 2, 2, 1, 180);

  GSM_CallCmd(CMD_SET_NUMBERIC_RESPONCE_FORMAT);
  GSM_CallCmd(CMD_DISABLE_ECHO);
  GSM_CallCmd(CMD_SET_ERROR_LEVEL_1);
  GSM_CallCmd(CMD_ENABLE_AON);

  _sleep(2000);

  GSM_CallCmd(CMD_CHECK_NET_STATUS);
  GSM_CallCmd(CMD_GET_IMEI);*/
}

ISR(USARTE0_RXC_vect) {
  static volatile uint8_t i = 1;
  BaseType_t higher_priority_task_woken;
  rbuf[i] = USARTE0.DATA;
  i++;

  if (rbuf[i - 1] == 13 || i >= READ_BUFFER_SIZE) {
    i = 1;
    MessageBufferHandle_t* pHandle = context.mail + TELEPHONE_MAILBOX_OFFSET;
    if (*pHandle != NULL) {
      rbuf[0] = MSG_GSM_INPUT;
      xMessageBufferSendFromISR(*pHandle, (void*)rbuf, (size_t)(i - 1),
                                &higher_priority_task_woken);
    }
  }
}

void GSM_CallCmd(const char* msg) {
  GSM_SendCStr(msg);
  char result_code;
  bool result = GSM_ReadResultCode(1000, &result_code);
  _clogu8(msg, (uint8_t)result);
}

void GSM_SendCStr(const char* str) {
  volatile uint8_t i = 0;
  const uint8_t len = strlen(str);
  for(i = 0; i < len; i++) {
    GSM_SendByte(str[i], 1000);
  }
  GSM_SendByte('\n', 1000);
}

void GSM_SendStr(char* str, uint8_t len) {
  volatile uint8_t i = 0;
  for(i = 0; i < len; i++) {
    GSM_SendByte(str[i], 1000);
  }
}

bool GSM_SendByte(char c, uint16_t delay_ms) {
  volatile TickType_t begin_time = xTaskGetTickCount();

  do {
    if (USARTE0_STATUS & USART_DREIF_bm) {
      USARTE0.DATA = c;
      return true;
    }

    if (xTaskGetTickCount() - begin_time > pdMS_TO_TICKS(delay_ms))
      break;
    else
      taskYIELD();

  } while(true);

  _clog("GSM send byte failed");
  return false;
}

bool GSM_ReadByte(char* out, uint16_t delay_ms) {
  volatile TickType_t begin_time = xTaskGetTickCount();

  do {
    if (USARTE0.STATUS & USART_RXCIF_bm) {
      *out = USARTE0.DATA;
      _clogu8("read byte: ", *out);
      return true;
    }
    if (xTaskGetTickCount() - begin_time > pdMS_TO_TICKS(delay_ms))
      break;
    else
      taskYIELD();
  } while(true);

  //_clog("GSM read byte failed");
  return false;
}

char GSM_ReadResultCode(uint16_t delay_ms, char* out) {
  uint8_t i;
  for (i = 0; i < READ_BUFFER_SIZE; i++) {
    if (true == GSM_ReadByte(rbuf + i, delay_ms))
      if ((rbuf[i]) == '\r')
        break;
  }

  // should be 2 bytes = result code + '\r'
  if (i == 1 && rbuf[i] == '\r') {
    *out = rbuf[0];
    return true;
  }

  return false;
}

// Responce format: "\r\n<responce>\r\n"

// gsm.c

#include "gsm.h"

#include <string.h>

#include "spi.h"
#include "kbd.h"

#define READ_BUFFER_SIZE 255

static void vGsmTask(void* pvParameters);
void GSM_CallCmd(const char* msg);
void GSM_SendCStr(const char* str);
void GSM_SendStr(char* str, uint8_t len);
bool GSM_SendByte(char c, uint16_t delay_ms);
bool GSM_ReadByte(uint16_t delay_ms, char* out);
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
  GSM_ReadByte(rbuf[0], 1000);
  GSM_ReadByte(rbuf[1], 100);
  GSM_ReadByte(rbuf[2], 100);
  GSM_ReadByte(rbuf[3], 100);
  GSM_ReadByte(rbuf[4], 100);
  GSM_ReadByte(rbuf[5], 100);

  _clog("GSM responce received");
  EPD_ShowString(buf + 2, 2, 1, 180);

  GSM_CallCmd(CMD_SET_NUMBERIC_RESPONCE_FORMAT);
  GSM_CallCmd(CMD_DISABLE_ECHO);
  GSM_CallCmd(CMD_SET_ERROR_LEVEL_1);
  GSM_CallCmd(CMD_ENABLE_AON);

  /*xTaskCreate( vGsmTask,
               "GsmTask",
               configMINIMAL_STACK_SIZE,
               NULL,
               2,
               &(context.gsm_task_handle) );*/
}

static void vGsmTask(void* pvParameters) {
  while(1) {
    GSM_ReadNotifications();
  }
}
void GSM_CallCmd(const char* msg) {
  GSM_SendCStr(msg);
  result = GSM_ReadResultCode(100);
  _clogu8(CMD_SET_NUMBERIC_RESPONCE_FORMAT, (uint8_t)result);
}

void GSM_SendCStr(const char* str) {
  volatile uint8_t i = 0;
  const uint8_t len = strlen(str);
  for(i = 0; i < len; i++) {
    GSM_SendByte(str[i], 100);
  }
  GSM_SendByte('\n', 100);
}

void GSM_SendStr(char* str, uint8_t len) {
  volatile uint8_t i = 0;
  for(i = 0; i < len; i++) {
    GSM_SendByte(str[i], 100);
  }
}

bool GSM_SendByte(char c, uint16_t delay_ms) {
  volatile TickType_t begin_time = xTaskGetTickCount();

  do {
    if (USARTE0_STATUS & USART_DREIF_bm) {
      USARTE0_DATA = c;
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

bool GSM_ReadByte(uint16_t delay_ms, char* out) {
  volatile TickType_t begin_time = xTaskGetTickCount();

  do {
    if (USARTE0.STATUS & USART_RXCIF_bm) {
      *out = USARTC0.DATA;
      return true;
    }
    if (xTaskGetTickCount() - begin_time > pdMS_TO_TICKS(delay_ms))
      break;
    else
      taskYIELD();
  } while(true);

  _clog("GSM read byte failed");
  return false;
}

char GSM_ReadResultCode(uint16_t delay_ms, char* out) {
  uint8_t i;
  for (i = 0; i < READ_BUFFER_SIZE; i++) {
    if (true == GSM_ReadByte(delay_ms, rbuf + i))
      if ((rbuf[i]) == '\r')
        break;
  }

  // should be 2 bytes = result code + '\r'
  if (i == 1 && rbuf[i] == '\r') {
    *out = rbuf[0];
    return true;
  }

  _clog("GSM read result code error");
  return false;
}

// Responce format: "\r\n<responce>\r\n"

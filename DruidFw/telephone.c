// telephone.c

#include "telephone.h"

#include "FreeRTOS.h"
#include "task.h"
#include "message_buffer.h"

#include "global.h"
#include "epd.h"
#include "gsm.h"

void APP_TelephoneStart(void);
void TEL_Thread(void* pvParameters);
void TEL_MessagePump(void);
void TEL_KeyPressHandler(Key key);
void TEL_DrawHandler(void);
void ShowLine(uint8_t i, uint8_t x, uint8_t y);
void TEL_CloseHandler(void);

#define TEL_MENU_SIZE 6//(sizeof(menu) / sizeof(TelMenu))

static TelMenu menu[TEL_MENU_SIZE] = {
  {"AT+CREG?\0   ", "            "},
  {"AT+GSN\0     ", "            "},
  {"ATE0\0       ", "            "},
  {"AT\0         ", "            "},
  {"\0           ", "            "},
  {"\0           ", "            "},

};

uint8_t g_selected;

void APP_TelephoneStart(void) {
  xTaskCreate(TEL_Thread, "telephoneTask", configMINIMAL_STACK_SIZE,
              NULL, 1, NULL);
  context.active_app_id = TELEPHONE_MAILBOX_ID;
  _sleep(100);

  SendAppMsg(MSG_DRAW, NULL, 0, TELEPHONE_MAILBOX_ID);
}

void TEL_Thread(void* pvParameters) {
  (void)(pvParameters);
  MessageBufferHandle_t* pHandle = context.mail + TELEPHONE_MAILBOX_ID;
  *pHandle = xMessageBufferCreate((size_t)100);

  TEL_MessagePump();
  _log("APP telephone closed");
}

void TEL_MessagePump(void) {
  char data[100];
  size_t len;
  g_selected = 0;

  MessageBufferHandle_t* pHandle = context.mail + TELEPHONE_MAILBOX_ID;

  _log("APP telephone started");

  while(1) {
    len = xMessageBufferReceive(*pHandle, data, 100, portMAX_DELAY);
    if (len > 0) {
      switch(data[0]) {

        case MSG_KBD: {
          _log("APP menu msg: key %d", (uint8_t)(data[1]));
          TEL_KeyPressHandler((Key)data[1]);
          TEL_DrawHandler();
          break;
        } // case MSG_KBD

          case MSG_DRAW: {
            _log("APP menu msg: show");
            TEL_DrawHandler();
            break;
          } // case MSG_DRAW

          case MSG_GSM_INPUT: {
            uint8_t i;
            _log("APP menu msg: gsm input");
            for (i = 0; i < len && i < 100; i ++)
              menu[g_selected].answer[i] = data[i];
	    _log("GSM: %s", data[i]);
            TEL_DrawHandler();
            break;
          }

          case MSG_CLOSE: {
            _log("APP menu msg: close telephonet");

            TEL_CloseHandler();

            context.active_app_id = MENU_MAILBOX_ID;
            vMessageBufferDelete(*pHandle);
            context.mail[TELEPHONE_MAILBOX_ID] = NULL;
            vTaskDelete(NULL);
            return;
          }

          default:
            _log("APP menu msg: not known: %d", (uint8_t)(data[0]));
            break;

      } // switch
    } // if ( len > 0 )
  } // while(1)
}

void TEL_CloseHandler(void) {
}

void TEL_KeyPressHandler(Key key) {
  switch( key ) {
    case key2: {
      if (g_selected < TEL_MENU_SIZE)
        g_selected ++;
      break;
    } // case key2

    case key5: {
      SendGsm(menu[g_selected].cmd);
    } // case key5
    case key8: {
      if (g_selected > 0)
        g_selected --;
      break;
    } // case key8
    default:
      break;
  } // switch ( key )
}

void TEL_DrawHandler(void) {
  return;
  EPD_StartPartial();
  EPD_ContinuePartial("     telephone      ", 20, 1, 185);

  ShowLine(0, 1, 160);
  ShowLine(1, 1, 140);
  ShowLine(2, 1, 120);
  ShowLine(3, 1, 100);
  ShowLine(4, 1, 80);
  ShowLine(5, 1, 60);

  EPD_UpdatePartial();
  EPD_StopPartial();
}

void ShowLine(uint8_t i, uint8_t x, uint8_t y) {
  char marker = '~';
  TelMenu line = menu[i];
  if (i == g_selected) {
    EPD_ContinuePartial(&marker, 1, x-1, y);
  }
  EPD_ContinuePartial(line.cmd, 12, x, y);
  EPD_ContinuePartial(line.answer, 12, x + 12, y);
}

// menu.c
#include "menu.h"

#include "FreeRTOS.h"
#include "task.h"
#include "message_buffer.h"

#include "global.h"
#include "kbd.h"
#include "epd.h"

#define APP_HEADER_LEN 15

static volatile int8_t i;
App* gp_menu;

void App_MenuThread(void* pvParameters);
void APP_MenuMessagePump(void);
void MENU_KeyPressHandler(Key key);
void MENU_DrawHanadler(void);

void APP_MenuStart(App* menu) {
  gp_menu = menu;
  xTaskCreate(App_MenuThread, "menuTask", configMINIMAL_STACK_SIZE,
              NULL, 1, NULL);
  context.active_app_id = MENU_MAILBOX_ID;
  _sleep(100);

  SendAppMsg(MSG_DRAW, NULL, 0, MENU_MAILBOX_ID);
}

void App_MenuThread(void* pvParameters) {
  (void)(pvParameters);
  MessageBufferHandle_t* pHandle = context.mail + MENU_MAILBOX_ID;
  *pHandle = xMessageBufferCreate((size_t)50);
  APP_MenuMessagePump();
  _log("APP menu closed");
}

void APP_MenuMessagePump(void) {
  char data[2];
  size_t len;
  MessageBufferHandle_t* pHandle = context.mail + MENU_MAILBOX_ID;
  i = 0;

  _log("APP menu started");
  while(1) {
    len = xMessageBufferReceive(*pHandle, data, 2, portMAX_DELAY);
    _log("APP menu msg received");
    if (len > 0) {
      switch(data[0]) {
        case MSG_KBD: {
          _log("APP menu msg: key: %d ", (uint8_t)(data[1]));
          MENU_KeyPressHandler((Key)data[1]);
          MENU_DrawHanadler();
          break;
        } // case MSG_KBD

          case MSG_DRAW: {
            _log("APP menu msg: show");
            MENU_DrawHanadler();
            break;
          } // case MSG_DRAW

          default:
            _log("APP menu msg: not known");
            break;

      } // switch
    }
  }
}

void MENU_KeyPressHandler(Key key) {
  int8_t menu_size = (int8_t)(sizeof(gp_menu) / sizeof(App));

  switch(key) {
      case key2:
        i--;
        break;
      case key8:
        i++;
        break;
      case key5:
        if (i >= 0 && i < menu_size) {
          MessageBufferHandle_t handle = context.mail[gp_menu[i].id];
          if (handle == NULL) {
            gp_menu[i].Call();
          } else {
            context.active_app_id = gp_menu[i].id;
            SendAppMsg(MSG_DRAW, NULL, 0, gp_menu[i].id);
          }
        }
        break;
      default:
        break;
    }
}

void MENU_DrawHanadler(void) {
  return;
  int8_t menu_size = MENU_SIZE;//(int8_t)(sizeof(*gp_menu) / sizeof(App));
  _log("menu size: %d ", menu_size);

  EPD_StartPartial();
  EPD_ContinuePartial("      XMobile", 13, 1, 180);

  if (i-3 >= 0 && i-3 < menu_size)
    EPD_ContinuePartial((char*)(gp_menu[i-3].header), APP_HEADER_LEN, 0,
                        180);
  else
    EPD_ContinuePartial("               ", APP_HEADER_LEN, 0, 180);

  if (i-2 >= 0 && i-2 < menu_size)
    EPD_ContinuePartial((char*)(gp_menu[i-2].header), APP_HEADER_LEN, 1,
                        160);
  else
    EPD_ContinuePartial("               ", APP_HEADER_LEN, 1, 160);

  if (i-1 >= 0 && i-1 < menu_size)
    EPD_ContinuePartial((char*)(gp_menu[i-1].header), APP_HEADER_LEN, 2,
                        140);
  else
    EPD_ContinuePartial("               ", APP_HEADER_LEN, 2, 140);

  EPD_ContinuePartial(" -----", 6, 0, 120);
  if (i >= 0 && i < menu_size)
    EPD_ContinuePartial((char*)(gp_menu[i].header), APP_HEADER_LEN, 3,
                        100);
  else
    EPD_ContinuePartial("               ", APP_HEADER_LEN, 3, 100);
  EPD_ContinuePartial(" -----", 6, 0, 80);

  if (i+1 >= 0 && i+1 < menu_size)
    EPD_ContinuePartial((char*)(gp_menu[i+1].header), APP_HEADER_LEN, 2,
                        60);
  else
    EPD_ContinuePartial("               ", APP_HEADER_LEN, 2, 60);

  if (i+2 >= 0 && i+2 < menu_size)
    EPD_ContinuePartial((char*)(gp_menu[i+2].header), APP_HEADER_LEN, 1,
                        40);
  else
    EPD_ContinuePartial("               ", APP_HEADER_LEN, 1, 40);

  if (i+3 >= 0 && i+3 < menu_size)
    EPD_ContinuePartial((char*)(gp_menu[i+3].header), APP_HEADER_LEN, 0,
                        20);
  else
    EPD_ContinuePartial("               ", APP_HEADER_LEN, 0, 20);

  EPD_UpdatePartial();

  EPD_StopPartial();

}

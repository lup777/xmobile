// menu.c
#include "menu.h"

#include "FreeRTOS.h"
#include "task.h"
#include "message_buffer.h"

#include "global.h"
#include "kbd.h"
#include "spi.h"

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
  context.active_app_index = MENU_MAILBOX_OFFSET;
  MessageBufferHandle_t* pHandle = context.mail + MENU_MAILBOX_OFFSET;
  char msg = MSG_DRAW;
  _sleep(100);

  if (*pHandle)
    xMessageBufferSend(*pHandle, &msg, sizeof(char), 1000);
}

void App_MenuThread(void* pvParameters) {
  (void)(pvParameters);
  MessageBufferHandle_t* pHandle = context.mail + MENU_MAILBOX_OFFSET;
  *pHandle = xMessageBufferCreate((size_t)50);
  APP_MenuMessagePump();
  _clog("APP menu closed");
}

void APP_MenuMessagePump(void) {
  char data[2];
  size_t len;
  MessageBufferHandle_t* pHandle = context.mail + MENU_MAILBOX_OFFSET;
  i = 0;

  _clog("APP menu started");
  while(1) {
    len = xMessageBufferReceive(*pHandle, data, 2, portMAX_DELAY);
    _clog("APP menu msg received");
    if (len > 0) {
      switch(data[0]) {
        case MSG_KBD: {
          _clogu8("APP menu msg: key ", (uint8_t)(data[1]));
          MENU_KeyPressHandler((Key)data[1]);
          MENU_DrawHanadler();
          break;
        } // case MSG_KBD

          case MSG_DRAW: {
            _clog("APP menu msg: show");
            MENU_DrawHanadler();
            break;
          } // case MSG_DRAW

          default:
            _clog("APP menu msg: not known");
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
        if (i >= 0 && i < menu_size)
          gp_menu[i].Call();
        break;
      default:
        break;
    }
}

void MENU_DrawHanadler(void) {
  int8_t menu_size = MENU_SIZE;//(int8_t)(sizeof(*gp_menu) / sizeof(App));
  _clogu8("menu size ", menu_size);

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

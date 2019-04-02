// menu.c
#include "menu.h"

#include "FreeRTOS.h"
#include "task.h"
#include "message_buffer.h"

#include "global.h"
#include "kbd.h"
#include "epd.h"
#include "render.h"

#define APP_HEADER_LEN 15
//#define _log(...)
static volatile int8_t i;
App* gp_menu;

void APP_MenuMessagePump(void);
void MENU_KeyPressHandler(char key);
void MENU_DrawHanadler(void);

void APP_MenuStart(App* menu) {
  gp_menu = menu;

  context.active_app_id = MENU_MAILBOX_ID;

  MessageBufferHandle_t* pHandle = context.mail + MENU_MAILBOX_ID;
  *pHandle = xMessageBufferCreate((size_t)5);

  SendAppMsg(MSG_DRAW, NULL, 0, MENU_MAILBOX_ID);

}

void APP_MenuMessagePump(void) {
  char data[2];
  size_t len;
  MessageBufferHandle_t* pHandle = context.mail + MENU_MAILBOX_ID;
  i = 0;

  _log("MENU started");
  while(1) {
    _log("MENU Waiting for msg (%p)", pHandle);
    len = xMessageBufferReceive(*pHandle, data, 2, portMAX_DELAY);

    if (context.active_app_id != MENU_MAILBOX_ID) {
      xMessageBufferReset(*pHandle);
      continue;
    }

    _log("MENU msg received");

    if (len > 0) {
      switch(data[0]) {
      case MSG_KBD: {
        _log("MENU msg: key: %d ", (uint8_t)(data[1]));
        MENU_KeyPressHandler(data[1]);
        break;
      } // case MSG_KBD

      case MSG_DRAW: {
        _log("MENU msg: show");
        MENU_DrawHanadler();
        break;
      } // case MSG_DRAW

      default:
        _log("MENU msg: not known");
        break;

      } // switch
    }
  } // while(1)
  
  _log("MENU closed");
}

void MENU_KeyPressHandler(char key) {
  int8_t menu_size = MENU_SIZE;

  switch(key) {
      case 65:
      case '2':
	_log("key 2");
        i--;
	SendAppMsg(MSG_DRAW, NULL, 0, MENU_MAILBOX_ID);
        break;

      case 66:
      case '8':
	_log("key 8");
        i++;
	SendAppMsg(MSG_DRAW, NULL, 0, MENU_MAILBOX_ID);
        break;

      case 13:
      case '5':
	_log("key 5 (i = %d)", i);
        if (i >= 0 && i < menu_size) {
          MessageBufferHandle_t handle = context.mail[gp_menu[i].id];
          if (handle == NULL) {
	    _log("call");
            gp_menu[i].Call();
          }
	  
	  //context.active_app_id = gp_menu[i].id;
	  //SendAppMsg(MSG_DRAW, NULL, 0, gp_menu[i].id);
        }
        break;
	
      default:
	_log("key %d", key);
        break;
    }
}

void MENU_DrawHanadler(void) {
  int8_t menu_size = MENU_SIZE;//(int8_t)(sizeof(*gp_menu) / sizeof(App));
  _log("menu size: %d ", menu_size);

  displayRenderLine(0, 0,
		    display.buf_cols << 3,
		    display.buf_rows,
		    &display);
  displayRenderLine(0, 0,
		    display.buf_cols << 3,
		    display.buf_rows >> 1,
		    &display);
  displayRenderCircle(50, 50, 30, &display);
  displayRenderRectangle(20, 20, 100, 100, &display);

  displayRenderText(8, 125+i, "hello", 1, &display);
  displayRenderText(12, 140+i, "hello, renderer!", 16, &display);
  displayRenderText(14, 155+i, "hello, renderer!", 16, &display);
  displayRenderText(17, 170+i, "hello, renderer!", 16, &display);
  
  displayFlush();

}

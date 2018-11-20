//ui.c

#include "ui.h"

#include "FreeRTOS.h"
#include "task.h"

#include "global.h"
#include "display_data.h"
#include "spi.h"

static volatile Key g_key = keyNo;
static volatile bool g_need_update = false;

bool UI_IsUpdateNeeded(void);

void UI_SetKey(Key key) {
  taskENTER_CRITICAL();

  g_key = key;
  g_need_update = true;

  taskEXIT_CRITICAL();
}

bool UI_IsUpdateNeeded(void) {
  bool tmp;
  taskENTER_CRITICAL();
  tmp = g_need_update;
  g_need_update = false;
  taskEXIT_CRITICAL();
  return tmp;
}

Key UI_GetKey(void) {
  Key key;
  taskENTER_CRITICAL();

  key = g_key;

  taskEXIT_CRITICAL();
  return key;
}

void vUITask(void* pvParameters) {
  (void)(pvParameters);
  log("UI Task stated");

  uint8_t images_num = 1;

  EPD_Init();
  _sleep(500);

  EPD_ShowFullScreenImage(ucDisplayFullLupImage, 200, 200);
  _sleep(500);

  Image images[images_num];
  images[0].data = test_font_1;
  images[0].width = 2;
  images[0].height = 23;
  images[0].x = 10;
  images[0].y = 100;

  for(;;) {
    if (false == UI_IsUpdateNeeded()) {
      taskYIELD();
    }

    log("UI Notification received");

    switch(UI_GetKey()) {
    case key0:
      log("KBD key ");
      images[0].data = test_font_1;
      break;

    case key1:
      log("KBD key 1");
      images[0].data = test_font_2;
      break;

    case key2:
      log("KBD key 2");
      images[0].data = test_font_3;
      break;

    case key3:
      log("KBD key 3");
      images[0].data = test_font_4;
      break;

    case key4:
      log("KBD key 4");
      images[0].data = test_font_5;
      break;

    case key5:
      log("KBD key 5");
      images[0].data = test_font_1;

      break;
    case key6:
      log("KBD key 6");
      images[0].data = test_font_2;
      break;

    case key7:
      log("KBD key 7");
      images[0].data = test_font_3;
      break;

    case key8:
      log("KBD key 8");
      images[0].data = test_font_4;
      break;

    case key9:
      log("KBD key 9");
      images[0].data = test_font_5;
      break;

    default:
      log("KBD key No");
      images[0].data = test_font_1;
      break;
    } // switch
    EPS_ShowPartialImages(NULL, images, images_num);
    _sleep(300);
  }// for
}

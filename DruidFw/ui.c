//ui.c

#include "ui.h"

#include "FreeRTOS.h"
#include "task.h"

#include "global.h"
#include "fonts.h"
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
  images[0].width = 1;
  images[0].height = 13;
  images[0].x = 10;
  images[0].y = 100;

  for(;;) {
    if (false == UI_IsUpdateNeeded()) {
      taskYIELD();
    }

    log("UI Notification received");

    images[0].data = FONT_GetPicture8x13(UI_GetKey()); // for testing only, wrong logic

    EPS_ShowPartialImages(NULL, images, images_num);
    _sleep(300);
  }// for
}

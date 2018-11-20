//ui.c

#include "ui.h"

#include "FreeRTOS.h"
#include "task.h"

#include "global.h"
#include "fonts.h"
#include "display_data.h"
#include "spi.h"

volatile Key g_key;
volatile bool g_need_update = false;

bool UI_IsUpdateNeeded(void);

void UI_SetKey(Key key) {
  g_key = key;
  g_need_update = true;
}

bool UI_IsUpdateNeeded(void) {
  if (g_need_update) {
    g_need_update = false;
    return true;
  }
  return false;
}

Key UI_GetKey(void) {
  return g_key;
}

void vUITask(void* pvParameters) {
  (void)(pvParameters);
  log("UI Task stated");

  g_key = keyNo;
  uint8_t images_num = 1;

  EPD_Init();
  _sleep(500);

  EPD_ShowFullScreenImage(ucDisplayFullLupImage, 200, 200);
  _sleep(500);
  
  log("UI Task Init completed");

  Image images[images_num];
  images[0].data = test_font_1;
  images[0].width = 1;
  images[0].height = 13;
  images[0].x = 10;
  images[0].y = 100;

  for(;;) {
    if (pdTRUE == xSemaphoreTake(context.ui_sem, portMAX_DELAY)) {
      log("UI Notification received");

      images[0].data = FONT_GetPicture8x13(UI_GetKey()); // for testing only, wrong logic

      EPS_ShowPartialImages(NULL, images, images_num);
      _sleep(100);
    }
  }// for
}

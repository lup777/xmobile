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

  EPD_Init();
  _sleep(500);

  EPD_ShowFullScreenImage(ucDisplayFullLupImage, 200, 200);
  _sleep(500);

  log("UI Task Init completed");

  for(;;) {
    if (pdTRUE == xSemaphoreTake(context.ui_sem, portMAX_DELAY)) {
      log("UI Notification received");
      char msg[2];
      msg[0] = g_key;
      msg[1] = '\n';
      EPD_ShowString( msg, 10, 100 );
      _sleep(100);
    }
  }// for
}

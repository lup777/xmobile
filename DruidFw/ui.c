//ui.c

#include "ui.h"

#include "FreeRTOS.h"
#include "task.h"

#include "global.h"
#include "fonts.h"
#include "display_data.h"
#include "spi.h"

volatile Key g_key;

void UI_SetKey(Key key) {
  g_key = key;
  xSemaphoreGive(context.ui_sem);
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
      EPD_ShowString( msg, 2, 10, 100 );
      _sleep(1000);
    }
  }// for
}

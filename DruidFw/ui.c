//ui.c

#include "ui.h"

#include "FreeRTOS.h"
#include "task.h"

#include "global.h"
#include "display_data.h"
#include "spi.h"

static volatile Key g_key = keyNo;
static volatile bool g_need_update = false;

/*#ifndef pdMS_TO_TICKS
#define pdMS_TO_TICKS( xTimeInMs ) ( ( TickType_t ) ( ( ( TickType_t ) ( xTimeInMs ) * ( TickType_t ) configTICK_RATE_HZ ) / ( TickType_t ) 1000 ) )
#endif*/

void UI_SetKey(Key key) {
  taskENTER_CRITICAL();

  g_key = key;
  
  taskEXIT_CRITICAL(); 
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
  sleep(500);
  EPD_ShowFullScreenImage(ucDisplayFullLupImage, 200, 200);
  sleep(500);
  
  Image images[images_num];
  images[0].data = test_font_1;
  images[0].width = 2;
  images[0].height = 23;
  images[0].x = 10;
  images[0].y = 100;

  uint32_t ulNotifiedValue;
  const TickType_t xBlockTime = pdMS_TO_TICKS( 500 );
  
  for(;;) {
    //while (pdTRUE != xTaskNotifyWait(0x00, 0xFFFFFFFF/*ULONG_MAX*/,
    //NULL,
    //portMAX_DELAY)) {} // indefinitely
    ulNotifiedValue = ulTaskNotifyTake(pdFALSE, xBlockTime/*portMAX_DELAY*/);

    if (ulNotifiedValue == 0)
      continue;
    
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
    sleep(1000);
  }// for
}


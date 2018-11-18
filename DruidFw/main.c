// main.c
#include <avr/io.h>

/* Scheduler include files. */
#include "FreeRTOS.h"
#include "task.h"

#include "usart.h"
#include "spi.h"
#include "display_data.h"
#include "pgm.h"
#include "kbd.h"

#define log(X) USART0_SendStr(X)

static void vTogglePA0Task(void* pvParameters);
void gpio_init(void);
void GPIO_toggle_PA0(void);
void sleep(uint16_t time_ms);
void KBD_Init(void);

/* GPIO
   PORT (those bits controls GPIO lines):
   DIR - direction
   OUT - to write output value
   IN - to read input value 
   PINnCTRL = configuration   
 */

void gpio_init(void) {
  PORTA.DIRSET = PIN0_bm; // PORT A, PIN 0,  OUT
}

void GPIO_toggle_PA0(void) {
  PORTA.OUTTGL = PIN0_bm;
}

int main(void) {
  gpio_init();
  USART0_init();
  KBD_Init();

  xTaskCreate( vTogglePA0Task,
	       "blink_PORTA_0_task",
	       configMINIMAL_STACK_SIZE,
	       (void*) NULL,
	       1,
	       NULL );

  vTaskStartScheduler();
  
  return 0;
}
void sleep(uint16_t time_ms) {
  //TickType_t xDelay = time / portTICK_PERIOD_MS;
  vTaskDelay((TickType_t)(time_ms / portTICK_PERIOD_MS));
}

static void vTogglePA0Task(void* pvParameters) {
  (void)(pvParameters);
  log("Start vTogglePA0Task task");
  sleep(1000);

  EPD_Init();
  sleep(500);
  //EPD_clear();
  EPD_ShowFullScreenImage(ucDisplayFullLupImage, 200, 200);

  sleep(500);
  //EPS_ShowPartialImage(NULL);

  for(;;) {
    GPIO_toggle_PA0();

    Key key = KBD_check();
    if (key != keyNo) {

      // EPD_ShowFullScreenImage(ucDisplayFullLupImage, 200, 200);
      Image images[1];
      switch(key) {
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
      }
      
      images[0].data = test_font_5;
      images[0].width = 2;
      images[0].height = 23;
      images[0].x = 10;
      images[0].y = 100;
      EPS_ShowPartialImages(NULL, images, 1);
      sleep(1000);
    }
  }
}

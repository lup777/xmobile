// main.c

#include "global.h"

#include "FreeRTOS.h"
#include "task.h"

#include "spi.h"
#include "pgm.h"
#include "kbd.h"
#include "ui.h"

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

typedef struct struct_context {
  TaskHandle_t ui_task_handle;
} Context;

Context context;

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

  xTaskCreate(vUITask,
	      "UI tsak",
	      configMINIMAL_STACK_SIZE,
	      NULL,
	      1,
	      &(context.ui_task_handle));
  
  xTaskCreate( vTogglePA0Task,
	       "blink_PORTA_0_task",
	       configMINIMAL_STACK_SIZE,
	       NULL,
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
      UI_SetKey(key);
      //if (pdPASS == xTaskNotify(context.ui_task_handle, 0, eIncrement)) {
      if (pdPASS == xTaskNotifyGive(context.ui_task_handle)) {
	log("MAIN Notification Success");
      } else {
	log("MAIN Notification Failed");
      }
    }
  }
}

// main.c
#include <avr/io.h>

/* Scheduler include files. */
#include "FreeRTOS.h"
#include "task.h"

#include "usart.h"
#include "spi.h"
#include "display_data.h"
#define log(X) USART0_SendStr(X)

static void vTogglePA0Task(void* pvParameters);
void gpio_init(void);
void GPIO_toggle_PA0(void);
void sleep(uint16_t time_ms);

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
  EPS_ShowPartialImage(ucDisplayFullLupImage);

  for(;;) {
    GPIO_toggle_PA0();

    sleep(1000);
    // EPD_ShowFullScreenImage(ucDisplayFullLupImage, 200, 200);
    //EPS_ShowPartialImage(ucDisplayFullLupImage);
    log("Hello from FreeRTOS!");
  }
}

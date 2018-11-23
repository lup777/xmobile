// main.c

#include "global.h"

#include "spi.h"
#include "pgm.h"
#include "kbd.h"
#include "ui.h"

static void vTogglePA0Task(void* pvParameters);
void gpio_init(void);
void GPIO_toggle_PA0(void);
void _sleep(uint16_t time_ms);
void KBD_Init(void);

/* GPIO
   PORT (those bits controls GPIO lines):
   DIR - direction
   OUT - to write output value
   IN - to read input value
   PINnCTRL = configuration
 */

// GLOBAL VARIABLES
Context context;
// ~GLOBAL VARIABLES~

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

  context.log_queue = xQueueCreate(50, sizeof(const char**));
  context.ui_sem = xSemaphoreCreateBinary();

  xTaskCreate( xLogTask,
	       "UsartLogstask",
	       configMINIMAL_STACK_SIZE,
	       NULL,
	       1,
	       NULL );

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
void _sleep(uint16_t time_ms) {
  //TickType_t xDelay = time / portTICK_PERIOD_MS;
  vTaskDelay((TickType_t)(time_ms / portTICK_PERIOD_MS));
}

static void vTogglePA0Task(void* pvParameters) {
  (void)(pvParameters);
  log("MAIN starting main  task");
  _sleep(1000);

  log("MAIN main task init completed");
  for(;;) {

    volatile Key key = KBD_Check();
    if (key != keyNo) {
      UI_SetKey(key);
    }
  }
}


/*
  Если принимающий поток уже был заблокирован и ожидает нотификации, когда нотификация пришла, принимающий поток будет выведен из заблокированного состояния и нотификация будет очищена.
 */

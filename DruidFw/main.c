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
void APP_telephone(void);
Key APP_WaiteKey(void);

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

  context.log_queue = xQueueCreate(5, sizeof(LogPairU8));
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

void APP_telephone(void) {
  Key key;
  char number [20] = "number: +xxxxxxxxxxx";
  _clog("Enter telephone");
  _sleep(100);
  EPD_ShowString((char*)number, 20, 2, 140);
  uint8_t i = 0;
  for (i = 0; i < 12; i++) {
    key = APP_WaiteKey();
    if (key != keyNo) {
      number[i+9] = (char)key + '0';
      EPD_ShowString((char*)number, 20, 2, 140);
    }
  }
  _clog("exit telepone\0");
  }

Key APP_WaiteKey(void) {
  Key key = keyNo;
  _clog("waiting for key");
  do {
    key = KBD_Check();
    /*_sleep(1000);  // waite for UI init
    static uint8_t tmp = 0;
    if (tmp < 9)
      tmp ++;
    else
      tmp = 0;
      key = tmp;*/
  } while(key == keyNo);
  _clog("key pressed");
  return key;
}

static void vTogglePA0Task(void* pvParameters) {
  (void)(pvParameters);
  //_clog("MAIN starting main  task");
  _sleep(2000); // waite for UI init

  _clog("MAIN main task init completed");
  for(;;) {
    APP_telephone();
    APP_WaiteKey();
  }
}

/*
  Если принимающий поток уже был заблокирован и ожидает нотификации, когда нотификация пришла, принимающий поток будет выведен из заблокированного состояния и нотификация будет очищена.
 */

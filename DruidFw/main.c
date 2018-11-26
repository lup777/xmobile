// main.c

#include "global.h"

#include "spi.h"
#include "pgm.h"
#include "kbd.h"
#include "ui.h"
#include "telephone.h"
#include "gsm.h"
#include "menu.h"

static void vTogglePA0Task(void* pvParameters);
void gpio_init(void);
void GPIO_toggle_PA0(void);
void _sleep(uint16_t time_ms);
void KBD_Init(void);
void TestApp1(void);
/* GPIO
   PORT (those bits controls GPIO lines):
   DIR - direction
   OUT - to write output value
   IN - to read input value
   PINnCTRL = configuration
 */

// GLOBAL VARIABLES
Context context;

App menu[] = {
  {APP_Telephone, "telephone      "},
  {TestApp1, "calendar       "},
  {TestApp1, "reader         "},
  {TestApp1, "snake          "},
  {TestApp1, "music player   "}
};

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

  /*xTaskCreate(vUITask,
              "UI tsak",
              configMINIMAL_STACK_SIZE,
              NULL,
              1,
              &(context.ui_task_handle));*/

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

void TestApp1(void) {
  EPD_StartPartial();
  EPD_ContinuePartial("      XMobile", 13, 1, 10);
  EPD_ContinuePartial("not implemented yet", 19, 1, 11);
  EPD_StopPartial();
  KBD_WaiteKey();
}

static void vTogglePA0Task(void* pvParameters) {
  (void)(pvParameters);

  EPD_Init();
  _sleep(100);

  EPD_ShowFullScreenImage(NULL/*ucDisplayFullLupImage*/, 200, 200);
  _sleep(100);

  GSM_Init();

  _clog("MAIN main task init completed");

  PORTD.DIRSET = PIN0_bm;
  PORTD.OUTCLR = PIN0_bm;

  for(;;) {
    MENU_Show(menu);
    //APP_Telephone();
  }
}

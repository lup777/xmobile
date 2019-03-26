// main.c

#include "global.h"

#include <stdio.h>

#include "epd.h"
#include "pgm.h"
#include "kbd.h"
//#include "telephone.h"
#include "gsm.h"
#include "menu.h"

static void vMainTask(void* pvParameters);
void gpio_init(void);
void GPIO_toggle_PA0(void);
void _sleep(uint16_t time_ms);
void KBD_Init(void);
void TestApp1(void);

// GLOBAL VARIABLES
Context context;


static App menu[MENU_SIZE] = {
  {TestApp1, NOT_EXISTS_ID,                   "telephone      "},
  {TestApp1, NOT_EXISTS_ID,                   "calendar       "},
  {TestApp1, NOT_EXISTS_ID,                   "reader         "},
  {TestApp1, NOT_EXISTS_ID,                   "snake          "},
  {TestApp1, NOT_EXISTS_ID,                   "music player   "}
};

// ~GLOBAL VARIABLES~

void gpio_init(void) {
  PORTA.DIRSET = PIN0_bm; // PORT A, PIN 0,  OUT
}

void GPIO_toggle_PA0(void) {
  PORTA.OUTTGL = PIN0_bm;
}

void SendAppMsg(uint8_t msg_id, char* payload, uint8_t payload_len,
                uint8_t mailbox_id) {
  char buf[10];
  if (payload_len > 10 + 1) {
    _log("ERR SendAppMsg: too log msg");
    return;
  }

  if (context.mail[mailbox_id] == NULL) {
    _log("ERR SendAppMsg: mailbox id == NULL");
    return;
  }

  buf[0] = msg_id;
  if (payload)
    for (int i = 0; i < payload_len; i++)
      buf[i + 1] = payload[i]; // copy payload

  size_t xBytesSent;

  taskENTER_CRITICAL();
  //_log("send to %p", context.mail[mailbox_id]);
  xBytesSent = xMessageBufferSend(context.mail[mailbox_id], buf,
                                  (size_t)payload_len + 1, 0);
  taskEXIT_CRITICAL();

  if (xBytesSent != (size_t)payload_len + 1) {
    _log("ERR SendAppMsg: xMessageBufferSend failed");
  }
}

int main(void) {

  //OSC_PLLCTRL = 0x16;  // 2 * 16 = 32MGz
  OSC_CTRL = OSC_RC32MEN_bm;
  
  while( !( OSC_STATUS & OSC_RC32MRDY_bm ) ); // waite while 32MGXz osc ready

  CCP = CCP_IOREG_gc;
  CLK_CTRL = CLK_SCLKSEL_RC32M_gc;
  
  gpio_init();
  USART0_init();
  KBD_Init();

  context.active_app_id = MENU_MAILBOX_ID;

  for (uint8_t i = 0; i < MAILBOX_SIZE; i++)
    context.mail[i] = NULL;

  xTaskCreate( vMainTask,
               "main_task",
               configMINIMAL_STACK_SIZE,
               NULL,
               1,
               NULL );

  vTaskStartScheduler();

  return 0;
}
void _sleep(uint16_t time_ms) {
  vTaskDelay((TickType_t)(time_ms / portTICK_PERIOD_MS));
}

void TestApp1(void) {
  EPD_StartPartial();
  EPD_ContinuePartial("      XMobile", 13, 1, 10);
  EPD_ContinuePartial("not implemented yet", 19, 1, 11);
  EPD_UpdatePartial();
  EPD_StopPartial();
  KBD_WaiteKey();
}

static void vMainTask(void* pvParameters) {
  (void)(pvParameters);

  union {
    uint16_t d;
    uint8_t a[2];
  } t;
  t.d = 1;
  if (t.a[0])
    _log("little endian");
  else
    _log("big endian");

  EPD_Init();
  //_sleep(100);

  EPD_ShowFullScreenImage(ucDisplayFullLupImage, 200, 200);
  
  //_sleep(3000);

  //GSM_Init();
  _log("MAIN main task init completed");

  //APP_TelephoneStart();
  APP_MenuStart(menu);

  for(;;) {
    APP_MenuMessagePump();
  }
  APP_MenuStart(menu);
  APP_MenuMessagePump();
  
}

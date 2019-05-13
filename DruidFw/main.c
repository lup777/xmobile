// main.c

#include "global.h"

#include <stdio.h>

#include "epd.h"
#include "pgm.h"
#include "kbd2.h"
//#include "telephone.h"
#include "gsm.h"
#include "menu.h"
#include "render.h"
#include "core_drv.h"

// local functions
static void vMainTask(void* pvParameters);
void _sleep(uint16_t time_ms);
void TestApp1(void);
void check_endian(void);
// ~ local functions

// GLOBAL VARIABLES
Context context;

static App menu[MENU_SIZE] = {
  {TestApp1, NOT_EXISTS_ID,                   "telephone      "},
  {TestApp1, NOT_EXISTS_ID,                   "calendar       "},
  {TestApp1, NOT_EXISTS_ID,                   "reader         "},
  {TestApp1, NOT_EXISTS_ID,                   "snake          "},
  {TestApp1, NOT_EXISTS_ID,                   "music player   "}
};

MessageBufferHandle_t kbd_rx_buf;
MessageBufferHandle_t gsm_rx_buf;
// ~GLOBAL VARIABLES~

int main(void) {
  kbd_rx_buf = xMessageBufferCreate( KBD_RX_BUFFER_SIZE );
  gsm_rx_buf = xMessageBufferCreate( 50 );

  {  // init modules
    run_on_32mgz();
    log_init();
    kbd_init();
    interrupts_init();
  }

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

static void vMainTask(void* pvParameters) {
  (void)(pvParameters);

  check_endian();

  displayInit();

  EPD_ShowFullScreenImage(ucDisplayFullLupImage, 200, 200);

  GSM_Init();
  _log("MAIN main task init completed");

  //APP_TelephoneStart();
  APP_MenuStart(menu);

  for(;;) {
    char key;
    char gsm_char[45];
    size_t kbd_rx_bytes = xMessageBufferReceive(kbd_rx_buf, &key, 1, 0);
    size_t gsm_rx_bytes = xMessageBufferReceive(gsm_rx_buf, &gsm_char, 45, 0);

    if (kbd_rx_bytes > 0) {
      _log("KBD: 0x%02X", key);
    }

    if (gsm_rx_bytes > 0) {
      //_log("GSM: %c  (0x%02X)", gsm_char, gsm_char);
      logcl("GSM: ");

      size_t i = 0;
      for(; i < gsm_rx_bytes; i++) {
	logc(gsm_char[i]);
      }
      logcl("\n\r");
    }
    //APP_MenuMessagePump();
  }
  APP_MenuStart(menu);
  APP_MenuMessagePump();
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
    _log("ERR SendAppMsg");
  }
}

void _sleep(uint16_t time_ms) {
  vTaskDelay((TickType_t)(time_ms / portTICK_PERIOD_MS));
}

void TestApp1(void) {
  EPD_StartPartial();
  //EPD_ContinuePartial("      XMobile", 13, 1, 10);
  //EPD_ContinuePartial("not implemented yet", 19, 1, 11);
  EPD_UpdatePartial();
  EPD_StopPartial();
  //KBD_WaiteKey();
}

inline void check_endian(void) {
  union {
    uint16_t d;
    uint8_t a[2];
  } t;

  t.d = 1;
  if (t.a[0])
    _log("little endian");
  else
    _log("big endian");
}

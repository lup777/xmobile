// main.c

#include "global.h"

#include <stdio.h>
#include <string.h>
#include "epd.h"
#include "pgm.h"
#include "kbd2.h"
//#include "telephone.h"
#include "gsm.h"
#include "menu.h"
#include "render.h"
#include "core_drv.h"
#include "text_edit.h"
#include "ml_text_edit.h"

// local functions
static void vMainTask(void* pvParameters);

void check_endian(void);
// ~ local functions

// GLOBAL VARIABLES
MessageBufferHandle_t kbd_rx_buf;
MessageBufferHandle_t gsm_rx_buf;
#ifndef DISABLE_LOGS
QueueHandle_t log_buf_handle;
#endif
//MessageBufferHandle_t task_mgr_msg_buf_handle;
enum enum_tasks active_task;

// ~GLOBAL VARIABLES~

int main(void) {
  log_init();  // configure debug USART

  kbd_rx_buf = xMessageBufferCreate( KBD_RX_BUFFER_SIZE ); // kbd input message buffer
  CHECK(kbd_rx_buf);

  gsm_rx_buf = xMessageBufferCreate( 50 );     // GSM input message buffer
  CHECK(gsm_rx_buf);

#ifndef DISABLE_LOGS
  log_buf_handle = xQueueCreate(80, 1); // logging output stream
  CHECK(log_buf_handle);
#endif

  //task_mgr_msg_buf_handle = xMessageBufferCreate( TASK_MGR_BUFFER_SIZE );
  //CHECK(task_mgr_msg_buf_handle);

  {  // init modules (order is significant)
    clk_init();  // set sys clock to internal 32 MGz
    //sram_init(); // configure external SRAM
    kbd_init();  // configure keyboard MAX7370 I2C
    int_init();  // enable ints and clear int flags
  }

  BaseType_t result;

  result = xTaskCreate( vMainTask,
                        "main_task",
                        configMINIMAL_STACK_SIZE,
                        NULL,
                        1,
                        NULL );
  CHECK(result == pdPASS);

#ifndef DISABLE_LOGS
  result = xTaskCreate( vLogTask,
                        "log_task",
                        configMINIMAL_STACK_SIZE,
                        NULL,
                        1,
                        NULL );

  CHECK(result == pdPASS);
#endif

  /*result = xTaskCreate( vTaskMgr,
                        "task_mgr",
                        configMINIMAL_STACK_SIZE,
                        NULL,
                        2,
                        NULL );

  CHECK(result == pdPASS);*/

  raw_logc("start_scheduler");
  vTaskStartScheduler();

  return 0;
}

static void vMainTask(void* pvParameters) {
  (void)(pvParameters);
  check_endian();

  displayInit();
  EPD_ShowFullScreenImage(ucDisplayFullLupImage, 200, 200);

  GSM_Init();
  CHECK(0);

  MlineTextEdit mte;
  mlTextEdit_init(&mte, 25, 7); // result will be checked internally

  TextEdit te;
  textEdit_init(&te, 25); // result will be checked internally

  bool need_update_display = false;

  for(;;) {
    char key;
    char gsm_char[25];

    size_t kbd_rx_bytes = xMessageBufferReceive(kbd_rx_buf, &key, 1, 0);
    size_t gsm_rx_bytes = xMessageBufferReceive(gsm_rx_buf, gsm_char, 25, 0);

    if (kbd_rx_bytes > 0) {
      //_log("KBD: 0x%02X", key);

      if (key == 0x02) { // loud connection
        send_cstr("AT+SNFS=1\n\r");
      } else if (key == 0x1B) { // get signal quality
        gsm_get_signal_quality();
      } else if (key == 0x1D) { // set ring volume
        send_cstr("AT+CRSL=15\n\r");
      } else if (key == 0x18) {//responce the call
        send_cstr("ATA\n\r");
      } else if (key == 17) { // call
        send_cstr("ATD+");
        send_str(te.text, te.idx);
        send_cstr(";\r\n");
      } else {
        _log("KBD: 0x%02X", key);

        char ch;
        if (true == kbd_key_to_char( key, &ch )) {
          textEdit_pushc(&te, ch);
        }

        // draw call number
        displayRenderText(3, 185, "call: +", 7, &display);
        textEdit_render(&te, 60, 185, &display);

        need_update_display = true;
      }
    }

    if (gsm_rx_bytes > 0) {
      mlTextEdit_pushstr(&mte, gsm_char, gsm_rx_bytes);

      //_log("GSM: %c  (0x%02X)", gsm_char, gsm_char);
      logcl("GSM: ");
      send_log_str(gsm_char, gsm_rx_bytes);
      logcl("\n\r");

      // draw GSM log
      mlTextEdit_render(&mte, 8, 24, &display);

      need_update_display = true;
    }

    // update display
    if (need_update_display) {
      need_update_display = false;
      displayFlush();
    }
  }
}

void _sleep(uint16_t time_ms) {
  vTaskDelay((TickType_t)(time_ms / portTICK_PERIOD_MS));
}

void check_endian(void) {
  union {
    uint16_t d;
    uint8_t a[2];
  } t;

  t.d = 1;
  if (t.a[0]) {
    logcl("little endian");
  } else {
    logcl("big endian");
  }
}

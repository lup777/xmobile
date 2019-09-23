// main.c

#include "global.h"

#include <stdio.h>
#include <string.h>
#include "kbd2.h"
//#include "telephone.h"
#include "gsm.h"
#include "menu.h"
#include "render.h"
#include "core_drv.h"
#include "text_edit.h"
#include "ml_text_edit.h"
#include "task_mgr.h"
#include "telephone.h"

#define STACK_SIZE 240

//typedef StaticMessageBuffer_t struct StaticStreamBuffer_t * const

// local functions
//static void vMainTask(void* pvParameters);

void check_endian(void);
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer,
				    StackType_t **ppxIdleTaskStackBuffer,
				    uint32_t *pulIdleTaskStackSize );
void vApplicationStackOverflowHook( TaskHandle_t xTask,
				    signed char *pcTaskName );
void vTelTask(void* pvParameters);
// ~ local functions

// GLOBAL VARIABLES

// ===== KBD MessageBuffer data ===========
MessageBufferHandle_t kbd_msg_buf_handle;
StaticStreamBuffer_t kbd_msg_buf_struct;
static uint8_t kbd_msg_buffer[ 20 ];
// ========================================

// ===== GSM MessageBuffer data ===========
MessageBufferHandle_t gsm_msg_buf_handle;
StaticStreamBuffer_t gsm_msg_buf_struct;
static uint8_t gsm_msg_buffer[ 80 ];
// ========================================

#ifndef DISABLE_LOGS
// ===== LOG MessageBuffer data ===========
//MessageBufferHandle_t log_msg_buf_handle;
//StaticStreamBuffer_t log_msg_buf_struct;
//static uint8_t log_msg_buffer[ 100 ];
// ========================================
#endif

// ====== TASK DATA =======================
// Main
StaticTask_t xMainTaskBuffer;
StackType_t xMainTStack[ STACK_SIZE ];

// Log
//StaticTask_t xLogTaskBuffer;
//StackType_t xLogTStack[ STACK_SIZE ];

// Task mgr
StaticTask_t xTaskMgrBuffer;
StackType_t xTaskMgrTStack[ STACK_SIZE ];

// Tel
StaticTask_t xTelTaskBuffer;
StackType_t xTelStack[ STACK_SIZE ];

//=========================================


// ~GLOBAL VARIABLES~

int main(void) {

  kbd_msg_buf_handle = xMessageBufferCreateStatic(sizeof(kbd_msg_buffer),
						  kbd_msg_buffer,
						  &kbd_msg_buf_struct);

  gsm_msg_buf_handle = xMessageBufferCreateStatic(sizeof(gsm_msg_buffer),
						  gsm_msg_buffer,
						  &gsm_msg_buf_struct);
    
#ifndef DISABLE_LOGS
  //log_msg_buf_handle = xMessageBufferCreateStatic(sizeof(log_msg_buffer),
  //log_msg_buffer,
  //&log_msg_buf_struct);
#endif

  {  // init modules (order is significant)
    clk_init();  // set sys clock to internal 32 MGz
    sram_init(); // configure external SRAM .init0
    log_init();  // configure debug USART
    int_init();  // enable ints and clear int flags
  }
  // ======= MAIN TASK ===================
  /*xTaskCreateStatic( vMainTask, "main_task", STACK_SIZE, NULL, 1,
    xMainTStack, &xMainTaskBuffer);*/
  // =====================================

  // ======= MAIN TASK ===================
  xTaskCreateStatic( vTelTask, "tel_task", STACK_SIZE, NULL, 1,
		     xTelStack, &xTelTaskBuffer);
  // =====================================

  
  // ======= TASK MANAGER  TASK ==========
  xTaskCreateStatic( vTaskMgr, "task mgr", STACK_SIZE, NULL, 2,
		     xTaskMgrTStack, &xMainTaskBuffer);
  // =====================================

  // ======= LOG TASK ====================
#ifndef DISABLE_LOGS
  //xTaskCreateStatic( vLogTask, "log_task", STACK_SIZE, NULL, 1,
  //		     xLogTStack, &xTaskMgrBuffer);
#endif
  // ======================================

  /*result = xTaskCreate( vTaskMgr,
                        "task_mgr",
                        configMINIMAL_STACK_SIZE,
                        NULL,
                        2,
                        NULL );

  CHECK(result == pdPASS);*/

  raw_logc("start_scheduler");

  /*if (check_sram()) {
    _log("MEM test OK");
  } else {
    _log("MEM test FAILED");
  }
  
  CHECK(0);*/
  
  vTaskStartScheduler();

  //vMainTask(NULL);
  vTelTask(NULL);
  return 0;
}
/*
static void vMainTask(void* pvParameters) {
  (void)(pvParameters);
  check_endian();

  //displayInit(display_buffer, dispay_spi_buf);
  

  //GSM_Init();

  //char mle_buf[50];
  //MlineTextEdit mte;
  //mlTextEdit_init(&mte, mle_buf, 50); // result will be checked internally

  static char te_buf[11];
  static TextEdit te;
  textEdit_init(&te, te_buf, 11); // result will be checked internally
  
  bool need_update_display = true;

  for(;;) {
    char key;
    static char gsm_char[25];

    size_t kbd_rx_bytes = xMessageBufferReceive(kbd_msg_buf_handle, &key, 1, 0);
    size_t gsm_rx_bytes = xMessageBufferReceive(gsm_msg_buf_handle, gsm_char, 25, 0);
    
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
        send_str(te.buffer, te.data_len);
        send_cstr(";\r\n");
      } else {
        _log("KBD: 0x%02X", key);

        char ch;
        if (true == kbd_key_to_char( key, &ch )) {
          textEdit_pushc(&te, ch);
        }

        // draw call number
	textEdit_render(&te, 60, 155, &display);
	//DCHECK(0, "_1_");

        need_update_display = true;
      }
    }
    (void)(gsm_rx_bytes);

    // update display
    if (need_update_display) {
      _log("flush display");
      need_update_display = false;
      displayRenderText(3, 155, "call: +", 7, &display);
      displayFlush();
    }
    
  }
}
*/
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
    //logcl("little endian\r\n");
  } else {
    //logcl("big endian\r\n");
  }
}

void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer,
				    StackType_t **ppxIdleTaskStackBuffer,
				    uint32_t *pulIdleTaskStackSize ) {
  /* If the buffers to be provided to the Idle task are declared inside this
function then they must be declared static - otherwise they will be allocated on
the stack and so not exists after this function exits. */
  static StaticTask_t xIdleTaskTCB;
  static StackType_t uxIdleTaskStack[ configMINIMAL_STACK_SIZE ];

  /* Pass out a pointer to the StaticTask_t structure in which the Idle task's
     state will be stored. */
  *ppxIdleTaskTCBBuffer = &xIdleTaskTCB;

  /* Pass out the array that will be used as the Idle task's stack. */
  *ppxIdleTaskStackBuffer = uxIdleTaskStack;

  /* Pass out the size of the array pointed to by *ppxIdleTaskStackBuffer.
    Note that, as the array is necessarily of type StackType_t,
    configMINIMAL_STACK_SIZE is specified in words, not bytes. */
  *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
}

void vApplicationStackOverflowHook( TaskHandle_t xTask,
				    signed char *pcTaskName ) {
  (void)(xTask);
  size_t i;
  static char msg[] = "SOWF";

  for ( i = 0; i < strlen(msg); i++) {
    while((USARTE1.STATUS & USART_DREIF_bm) == 0) {};
    USARTE1_DATA = msg[i];
  }
  
  for (i = 0; i < 7; i++) {
    while((USARTE1.STATUS & USART_DREIF_bm) == 0) {};
    USARTE1_DATA = pcTaskName[i];
  }
  while((USARTE1.STATUS & USART_DREIF_bm) == 0) {};
  USARTE1_DATA = '\n';
  
  while(1);
}

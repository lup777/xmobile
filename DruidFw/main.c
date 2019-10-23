// main.c

#include "global.h"

#define F_CPU 2000000UL
#include <util/delay.h>
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
#include "addr_book.h"
#include "sd.h"

#define STACK_SIZE 300

void check_endian(void);
void vApplicationGetIdleTaskMemory(
	 StaticTask_t **ppxIdleTaskTCBBuffer,
	 StackType_t **ppxIdleTaskStackBuffer,
	 uint32_t *pulIdleTaskStackSize );
void vApplicationStackOverflowHook(
	 TaskHandle_t xTask,
	 signed char *pcTaskName );
// ~ local functions

// GLOBAL VARIABLES

// ===== KBD MessageBuffer data ===========
MessageBufferHandle_t kbd_msg_buf_handle = NULL;
StaticStreamBuffer_t kbd_msg_buf_struct;
static uint8_t kbd_msg_buffer[ 20 ];
// ========================================

// ===== GSM MessageBuffer data ===========
MessageBufferHandle_t gsm_msg_buf_handle = NULL;
StaticStreamBuffer_t gsm_msg_buf_struct;
static uint8_t gsm_msg_buffer[ 80 ];
// ========================================

// ====== TASK DATA =======================
// Addr Book
StaticTask_t xAddrBookTaskBuffer;
StackType_t xAddrBookTStack[ STACK_SIZE ];

// Task mgr
StaticTask_t xTaskMgrBuffer;
StackType_t xTaskMgrTStack[ STACK_SIZE ];

// Tel
StaticTask_t xTelTaskBuffer;
StackType_t xTelStack[ STACK_SIZE ];

//=========================================


// ~GLOBAL VARIABLES~

int main(void) {
  _delay_ms(1000);
  log_init();  // configure debug USART

  kbd_msg_buf_handle = xMessageBufferCreateStatic(
      sizeof(kbd_msg_buffer),
      kbd_msg_buffer,
      &kbd_msg_buf_struct);

  gsm_msg_buf_handle = xMessageBufferCreateStatic(
      sizeof(gsm_msg_buffer),
      gsm_msg_buffer,
      &gsm_msg_buf_struct);

  {  // init modules (order is significant)
    clk_init();  // set sys clock to internal 32 MGz
    sram_init(); // configure external SRAM .init0
    //check_sram();
    kbd_init();  // configure keyboard MAX7370 I2C
    int_init();  // enable ints and clear int flags
  }

  // ======= ADDRESS BOOK TASK ================
  xTaskCreateStatic( addrBook_task, "addrbook", STACK_SIZE,
		     NULL, 1, xAddrBookTStack,
		     &xAddrBookTaskBuffer);
  // ==========================================

  // ======= TELEPHONE TASK ===================
  xTaskCreateStatic( vTelTask, "tel_task", STACK_SIZE, NULL, 1,
		     xTelStack, &xTelTaskBuffer);
  // ==========================================

  // ======= TASK MANAGER  TASK ===============
  xTaskCreateStatic( vTaskMgr, "task mgr", STACK_SIZE, NULL, 3,
		     xTaskMgrTStack, &xTaskMgrBuffer);
  // ==========================================

  raw_logc("start_scheduler");

  vTaskStartScheduler();

  return 0;
}

uint8_t u8min(uint8_t x, uint8_t y) {
  if (x < y)
    return x;
  return y;
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
    //logcl("little endian\r\n");
  } else {
    //logcl("big endian\r\n");
  }
}

void vApplicationGetIdleTaskMemory(
	 StaticTask_t **ppxIdleTaskTCBBuffer,
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

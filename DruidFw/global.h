//global.h
#pragma once

#include <avr/io.h>
#include <stdbool.h>

#include "FreeRTOS.h"
#include "message_buffer.h"
#include "task.h"
#include "semphr.h"

//#define MENU_SIZE 5

#define KBD_RX_BUFFER_SIZE 10
#define TASK_MGR_BUFFER_SIZE 50

#define NO_LOG_THREAD

#define MENU_MAILBOX_ID 0
#define TELEPHONE_MAILBOX_ID 1
#define NOT_EXISTS_ID 2

#define MAILBOX_SIZE 3

#define MSG_KBD 0
#define MSG_DRAW 1
#define MSG_CLOSE 2
#define MSG_GSM_INPUT 3
#define MSG_CALL 4

#define X_MERGIN_PIX 2
#define Y_MERGIN_PIX 1

//#define DISABLE_LOGS

typedef uint8_t byte;
typedef uint16_t word;

#include "usart.h"

void _sleep(uint16_t time_ms);
uint8_t _strlen(char * str);
uint8_t _u8tos(uint8_t value, char* buf, uint8_t buf_size, uint8_t base);
uint8_t _u16tos(uint16_t value, char* buf, uint8_t buf_size, uint8_t base);
uint8_t u8min(uint8_t x, uint8_t y);

// CHECK
// if (X == false) -> show func:line and loop
#define CHECK(X) {				      \
    if((X) == false) {                                \
      _log("CHECK: %s:%d", __FUNCTION__, __LINE__) ;  \
      for(;;) {}                                      \
    }                                                 \
  }

#define DCHECK(X, Y) {				      \
    if((X) == false) {                                \
      raw_logc("CHECK");			      \
      raw_logc(Y);				      \
      for(;;) {}                                      \
    }                                                 \
  }


//#ifndef EBI_CS_ASPACE_gm
//# define EBI_CS_ASPACE_1MB_gc   EBI_CS_ASIZE_1MB_gc
//#endif

enum enum_tasks {
  enum_task_mgr,
  enum_task_tel,
  enum_task_addr_book,
  enum_task_clock
};

// msg for ....
#define MSG_HEADER_KBD 0
#define MSG_HEADER_GSM 1
#define MSG_HEADER_TM  2
#define MSG_HEADER_ADDR_BOOK 3
#define MSG_HEADER_CALL 4

extern enum enum_tasks active_task;

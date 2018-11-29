//global.h
#ifndef __GLOBAL_H__
#define __GLOBAL_H__

#include <avr/io.h>

#include "FreeRTOS.h"
#include "message_buffer.h"
#include "task.h"
#include "semphr.h"

#include "usart.h"

typedef uint8_t bool;
#define true 1
#define false 0

typedef struct struct_gsm_data {
  uint8_t flags; // should be renamed
  // signal level
  // battary level
} GsmData;

#define MENU_MAILBOX_OFFSET 0
#define TELEPHONE_MAILBOX_OFFSET 1

#define MSG_KBD 0
#define MSG_DRAW 1
#define MSG_CLOSE 2
#define MSG_GSM_INPUT 3

typedef struct struct_context {
  TaskHandle_t ui_task_handle;
  TaskHandle_t gsm_task_handle;
  TaskHandle_t log_task_handle;
  QueueHandle_t log_queue;
  SemaphoreHandle_t ui_sem;
  GsmData gsm_data;
  MessageBufferHandle_t mail[2];
  uint8_t active_app_index;
} Context;


typedef struct StructLogPairU8 {
  const char* msg;
  uint8_t value;
} LogPairU8;

extern Context context;

//#define log(X) USART0_SendStr(X)
void _sleep(uint16_t time_ms);
uint8_t _u8tos(uint8_t value, char* buf, uint8_t buf_size, uint8_t base);
uint8_t _u16tos(uint16_t value, char* buf, uint8_t buf_size, uint8_t base);
uint8_t _strlen(char * str);


#endif // __GLOBAL_H__

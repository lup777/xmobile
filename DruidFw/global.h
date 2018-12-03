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

#define MENU_SIZE 5

typedef uint8_t bool;
#define false  0
#define true   1

typedef struct struct_gsm_data {
  uint8_t flags; // should be renamed
  // signal level
  // battary level
} GsmData;

#define NO_LOG_THREAD

#define MENU_MAILBOX_ID 0
#define TELEPHONE_MAILBOX_ID 1
#define NOT_EXISTS_ID 2

#define MAILBOX_SIZE 3

#define MSG_KBD 0
#define MSG_DRAW 1
#define MSG_CLOSE 2
#define MSG_GSM_INPUT 3

typedef struct struct_context {
  TaskHandle_t ui_task_handle;
  TaskHandle_t gsm_task_handle;
  QueueHandle_t log_queue;
  SemaphoreHandle_t ui_sem;
  GsmData gsm_data;
  MessageBufferHandle_t mail[MAILBOX_SIZE];
  uint8_t active_app_id;
} Context;


extern Context context;

void _sleep(uint16_t time_ms);
uint8_t _strlen(char * str);
uint8_t _u8tos(uint8_t value, char* buf, uint8_t buf_size, uint8_t base);
uint8_t _u16tos(uint16_t value, char* buf, uint8_t buf_size, uint8_t base);
void SendAppMsg(uint8_t msg_id, char* payload, uint8_t payload_len,
                uint8_t mailbox_id);

#endif // __GLOBAL_H__

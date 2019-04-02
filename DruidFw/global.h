//global.h
#ifndef __GLOBAL_H__
#define __GLOBAL_H__

#include <avr/io.h>
#include <stdbool.h>

#include "FreeRTOS.h"
#include "message_buffer.h"
#include "task.h"
#include "semphr.h"

#include "usart.h"

#define MENU_SIZE 5

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

typedef uint8_t byte;
typedef uint16_t word;

typedef struct struct_context {
  TaskHandle_t ui_task_handle;
  TaskHandle_t gsm_task_handle;
  GsmData gsm_data;
  MessageBufferHandle_t mail[MAILBOX_SIZE];
  uint8_t active_app_id;
} Context;

typedef struct struct_zone {
  short x_; // coordinates
  short y_; // coordinates
  short ex_; // coordinates
  short ey_; // coordinates
} Zone;

typedef struct struct_display_buffer {
    uint8_t* buffer;
    short buf_rows;
    short buf_cols;
    size_t buf_size;
    Zone zone;
} DispBuf;


extern Context context;
extern DispBuf display;

#define SendMsgISR(HANDLE, DATA, SIZE) ({			  \
      BaseType_t hptm_ = pdFALSE;                                 \
      UBaseType_t uxSavedInterruptStatus_;                        \
      if (HANDLE != NULL) {                                       \
        uxSavedInterruptStatus_ = taskENTER_CRITICAL_FROM_ISR();  \
        xMessageBufferSendFromISR(HANDLE, DATA, SIZE, &hptm_);    \
        taskEXIT_CRITICAL_FROM_ISR( uxSavedInterruptStatus_ );    \
      }                                                           \
      (hptm_ == pdTRUE);                                          \
    })


void _sleep(uint16_t time_ms);
uint8_t _strlen(char * str);
uint8_t _u8tos(uint8_t value, char* buf, uint8_t buf_size, uint8_t base);
uint8_t _u16tos(uint16_t value, char* buf, uint8_t buf_size, uint8_t base);
void SendAppMsg(uint8_t msg_id, char* payload, uint8_t payload_len,
                uint8_t mailbox_id);

#endif // __GLOBAL_H__

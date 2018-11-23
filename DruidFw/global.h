//global.h
#ifndef __GLOBAL_H__
#define __GLOBAL_H__

#include <avr/io.h>

#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

#include "usart.h"

typedef uint8_t bool;
#define true 1
#define false 0

typedef struct struct_context {
  TaskHandle_t ui_task_handle;
  QueueHandle_t log_queue;
  SemaphoreHandle_t ui_sem;
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

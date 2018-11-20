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
  xSemaphoreHandle log_mutex;
} Context;

extern Context context;

//#define log(X) USART0_SendStr(X)
void log(const char* msg);
void _sleep(uint16_t time_ms);

#endif // __GLOBAL_H__

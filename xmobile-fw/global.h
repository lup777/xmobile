//global.h

#ifndef __GLOBAL_H__
#define __GLOBAL_H__

#include <stdlib.h>
#include <string.h>

#ifdef GCC_MEGA_AVR
/* EEPROM routines used only with the WinAVR compiler. */
#include <avr/eeprom.h>
#endif

/* Scheduler include files. */
#include "FreeRTOS.h"
#include "task.h"

#include "queue.h"
#include "usart.h"
#include "stream_buffer.h"

#define CHECK_FOR_NULL(X) { if(X == NULL) vEnablePin13(); }

#define ERROR_MSG_0 "Hellow from FreeRTOS";
#define ERROR_MSG_1 "Hellow from FreeRTOS1";
#define MSG_SPI_DATA_WAS_SENT "spi data was sent"
#define MSG_SPI_DATA_GOINT_TO_SEND "going to send spi data"


struct struct_context
{
    StreamBufferHandle_t xDebugStream;
    StreamBufferHandle_t xDisplayStream;
};
typedef struct struct_context struct_context;

struct struct_context context;

void vEnablePin13(void);
void vDisablePin13(void);
void vTogglePin13(void);



#endif //__GLOBAL_H__

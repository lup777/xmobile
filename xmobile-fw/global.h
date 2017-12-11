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

#define CHECK_FOR_NULL(X) { if(X == NULL) vEnablePin13(); }

#define ERROR_MSG_0 "Hellow from FreeRTOS";
#define ERROR_MSG_1 "Hellow from FreeRTOS1";
#define MSG_SPI_DATA_WAS_SENT "spi data was sent"
#define MSG_SPI_DATA_GOINT_TO_SEND "going to send spi data"

typedef struct struct_queues
{
  QueueHandle_t debug;
  QueueHandle_t spi;
};

inline void vEnablePin13()
{
  DDRB  |= (1 << 7);
  PORTB |= (1 << 7);
}

inline void vDisablePin13()
{
  DDRB  |= (1 << 7);
  PORTB &= ~(1 << 7);
}

inline void vTogglePin13()
{
  //DDRB  |= (1 << 7);
  PORTB ^= (1 << 7);
}



#endif //__GLOBAL_H__

//global.h
#ifndef __GLOBAL_H__
#define __GLOBAL_H__

#include <avr/io.h>
//#include <avr/limits.h>
#include "usart.h"

typedef uint8_t bool;
#define true 1
#define false 0

//#define log(X) USART0_SendStr(X)
void log(const char* msg);
void sleep(uint16_t time_ms);

#endif // __GLOBAL_H__

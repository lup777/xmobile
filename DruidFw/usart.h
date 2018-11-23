// usart.h
#pragma once

#include "queue.h"

void USART0_init(void);
void USART0_SendByte(char c);
void USART0_SendStr(const char* str);
void _clog(const char* msg);
void _log(char* msg);
void xLogTask(void* pvParameters);

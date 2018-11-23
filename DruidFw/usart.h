// usart.h
#pragma once

#include "queue.h"

void USART0_init(void);
void USART0_SendByte(char c);
void USART0_SendStr(const char* str);
void _clog(const char* msg);
void _clogu8(const char* str, uint8_t v);
void xLogTask(void* pvParameters);

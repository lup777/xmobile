// usart.h
#pragma once

#include "queue.h"
#include "stream_buffer.h"


extern StreamBufferHandle_t g_log_tx_buffer_handle;


void USART0_init(void);
void _log(const char *format, ...);
void logc(char c);

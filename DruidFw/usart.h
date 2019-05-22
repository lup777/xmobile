// usart.h
#pragma once

#include "queue.h"
#include "stream_buffer.h"


void log_init(void);
void raw_logc(const char* str);

#ifndef DISABLE_LOGS
extern xSemaphoreHandle log_mutex;
void _log(const char *format, ...);
void logc(char c);
void logcl(const char* str);
void vLogTask(void* pvParameters);
void send_log_str(char* data, byte len);
#else
#  define _log(X, ...) {}
#  define logc(X) {}
#  define logcl(X) {}
#endif

// usart.h
#pragma once

#include "message_buffer.h"
#include <avr/pgmspace.h>


void log_init(void);
void raw_logc(const char* str);

#ifndef DISABLE_LOGS
//extern xSemaphoreHandle log_mutex;

/*#define _log(X, ...) {						\
    static const char _LOG_##__FUNCTION__##__LINE__ [] PROGMEM = X;	\
    __log( _LOG_##__FUNCTION__##__LINE__, ##__VA_ARGS__);		\
    }*/
#define _log(X, ...) __log(X, ##__VA_ARGS__)

extern MessageBufferHandle_t log_msg_buf_handle;

void __log(PGM_P format, ...);
void logc(char c);
void logcl(const char* str);
void vLogTask(void* pvParameters);
void send_log_str(char* data, byte len);
#else
#  define _log(X, ...) raw_logc(X) 
#  define logc(X) {}
#  define logcl(X) {}
#endif

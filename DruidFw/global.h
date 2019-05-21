//global.h
#pragma once

#include <avr/io.h>
#include <stdbool.h>

#include "FreeRTOS.h"
#include "message_buffer.h"
#include "task.h"
#include "semphr.h"

#define MENU_SIZE 5

#define KBD_RX_BUFFER_SIZE 10

#define NO_LOG_THREAD

#define MENU_MAILBOX_ID 0
#define TELEPHONE_MAILBOX_ID 1
#define NOT_EXISTS_ID 2

#define MAILBOX_SIZE 3

#define MSG_KBD 0
#define MSG_DRAW 1
#define MSG_CLOSE 2
#define MSG_GSM_INPUT 3

typedef uint8_t byte;
typedef uint16_t word;

typedef struct struct_zone {
  short x_; // coordinates
  short y_; // coordinates
  short ex_; // coordinates
  short ey_; // coordinates
  bool clean;
} Zone;

typedef struct struct_display_buffer {
    uint8_t* buffer;
    short buf_rows;
    short buf_cols;
    size_t buf_size;
    Zone zone;
} DispBuf;

extern DispBuf display;
extern MessageBufferHandle_t kbd_rx_buf;
extern MessageBufferHandle_t gsm_rx_buf;
#ifndef DISABLE_LOGS
extern StreamBufferHandle_t  log_buf_handle;
#endif

//#define DISABLE_LOGS

#include "usart.h"

void _sleep(uint16_t time_ms);
uint8_t _strlen(char * str);
uint8_t _u8tos(uint8_t value, char* buf, uint8_t buf_size, uint8_t base);
uint8_t _u16tos(uint16_t value, char* buf, uint8_t buf_size, uint8_t base);

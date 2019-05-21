// kbd2.h
#pragma once

#include "FreeRTOS.h"

#include "global.h"

void kbd_init(void);
void kbd_send_reg_byte(uint8_t addr, uint8_t data);

#define KEY_0 10
#define KEY_1 13
#define KEY_2 18
#define KEY_3 25
#define KEY_4 1
#define KEY_5 5
#define KEY_6 3
#define KEY_7 21
#define KEY_8 11
#define KEY_9 0
#define KEY_ASTERISK 8
#define KEY_HASH 16

bool kbd_key_to_char(byte key, char* ch);

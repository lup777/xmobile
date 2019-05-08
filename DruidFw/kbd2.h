// kbd2.h
#pragma once

#include "FreeRTOS.h"

#include "global.h"

void kbd_init(void);
void kbd_send_reg_byte(uint8_t addr, uint8_t data);

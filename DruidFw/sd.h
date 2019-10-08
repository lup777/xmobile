// sd.h
#pragma once

#include "global.h"

bool sd_init(void);
void sd_read_csd(uint8_t* buffer);
bool sd_read_block_512b(uint8_t* buffer, uint32_t addr);


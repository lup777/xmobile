// epd.h

#pragma once

#include "spi.h"

void EPD_ShowFullScreenImage(const uint8_t *image, uint16_t xsize,
                                    uint16_t ysize);
void EPD_UpdatePartial(void);
void EPD_StartPartial(void);
void EPD_ContinuePartial(char* str, uint8_t len, uint8_t x, uint8_t y);
void EPD_StopPartial(void);
void EPD_ShowString(char* str, uint8_t len, uint8_t x, uint8_t y);

void EPD_t1(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1);

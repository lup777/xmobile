 // fonts.h
#pragma once

#include "global.h"

// 1 - 70 - ru and simbols
// 71 - 96 - en

//Source image file: "pt-mono-bold-!-8x13.bmp"
//extern const uint8_t* FONT_nimbus_bold_16_1(uint8_t code);
const uint8_t* FONT_GetPicture8x13(uint8_t code);
extern const byte FONT_max_width;
extern const byte FONT_max_height;

 // fonts.h
#pragma once

#include "global.h"

// 1 - 70 - ru and simbols
// 71 - 96 - en
typedef enum {
  nimbus_mono_10,
  nimbus_bold_16
} Font;

//Source image file: "pt-mono-bold-!-8x13.bmp"
//extern const uint8_t* FONT_nimbus_bold_16_1(uint8_t code);
const uint8_t* FONT_GetPicture(uint8_t code, Font font);
byte FONT_GetHeight(Font font);
byte FONT_GetWidth(Font font);
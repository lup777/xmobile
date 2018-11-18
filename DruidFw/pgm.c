// pgm.c

#include "pgm.h"

const unsigned char test_font_1[46] PROGMEM = // 16x23 pixels
  {0xFF,0xFF,
   0xFF,0xFF,
   0xFF,0xFF,
   0xFF,0xFF,
   0xFF,0xFF,
   0xFF,0xFF,
   0xFC,0x1F,
   0xFB,0xEF,
   0xF7,0xFF,
   0xF7,0xFF,
   0xF0,0x1F,
   0xF3,0xE7,
   0xF7,0xF3,
   0xF7,0xFB,
   0xF3,0xFB,
   0xF4,0xF7,
   0xC6,0x0F,
   0xFF,0xFF,
   0xFF,0xFF,
   0xFF,0xFF,
   0xFF,0xFF,
   0xFF,0xFF,
   0xFF,0xFF};

const unsigned char test_font_2[46] PROGMEM =
  {0xEF,0xFF,
   0xC0,0x3F,
   0xE0,0x1F,
   0xFF,0xCF,
   0xFF,0xE7,
   0xF0,0x67,
   0xE0,0x17,
   0xC7,0xC7,
   0xCF,0xE3,
   0xCF,0xE3,
   0x8F,0xE3,
   0x8F,0xE3,
   0xCF,0xE7,
   0xCF,0xE7,
   0xCF,0xE7,
   0xE7,0x8F,
   0xE0,0x0F,
   0xF8,0x3F,
   0xFF,0xFF,
   0xFF,0xFF,
   0xFF,0xFF,
   0xFF,0xFF,
   0xFF,0xFF};

const unsigned char test_font_3[46] PROGMEM =
  {0xF3,0x9F,
   0xE3,0x8F,
   0xF3,0x9F,
   0xFF,0xFF,
   0xFF,0xFF,
   0xF8,0x3F,
   0xE0,0x1F,
   0xC7,0xCF,
   0xCF,0xE7,
   0xCF,0xE7,
   0xC0,0x07,
   0xC0,0x07,
   0xFF,0xE7,
   0xFF,0xE7,
   0xFF,0xE7,
   0xCF,0x8F,
   0xC0,0x0F,
   0xF0,0x3F,
   0xFF,0xFF,
   0xFF,0xFF,
   0xFF,0xFF,
   0xFF,0xFF,
   0xFF,0xFF};

const unsigned char test_font_4[46] PROGMEM =
  {0xFE,0x3F,
   0xFE,0x3F,
   0xFE,0xFF,
   0xFE,0xFF,
   0xFE,0xFF,
   0xE0,0x0F,
   0xC0,0x07,
   0x8E,0xE3,
   0x9E,0xF3,
   0x9E,0xF3,
   0x9E,0xF3,
   0x9E,0xF3,
   0x9E,0xF3,
   0x9E,0xF3,
   0x9E,0xF3,
   0x8E,0xE3,
   0xC0,0x07,
   0xE0,0x0F,
   0xFE,0xFF,
   0xFE,0xFF,
   0xFE,0xFF,
   0xFE,0xFF,
   0xFE,0xFF};

const unsigned char test_font_5[46] PROGMEM =
  {0xFF,0xFF,
   0xFF,0xFF,
   0xFF,0xFF,
   0xFF,0xFF,
   0xFF,0xFF,
   0xE7,0x73,
   0xE7,0x73,
   0xE7,0x73,
   0xE7,0x73,
   0xE7,0x73,
   0xE7,0x73,
   0xE7,0x73,
   0xE7,0x73,
   0xE7,0x73,
   0xE7,0x73,
   0xE7,0x73,
   0x80,0x03,
   0x80,0x03,
   0x9F,0xFF,
   0x9F,0xFF,
   0x9F,0xFF,
   0xFF,0xFF,
   0xFF,0xFF};


const uint8_t lut_full_update[31] PROGMEM =
  ///C221 25C Full update waveform
  {0x02, 0x02, 0x01, 0x11, 0x12, 0x12, 0x22, 0x22, 0x66, 0x69, 0x69, 0x59,
   0x58, 0x99, 0x99, 0x88, 0x00, 0x00, 0x00, 0x00, 0xF8, 0xB4, 0x13, 0x51,
   0x35, 0x51, 0x51, 0x19, 0x01, 0x00};

const uint8_t lut_partial_update[31] PROGMEM =
  {0x10, 0x18, 0x18, 0x08, 0x18, 0x18, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x13, 0x14, 0x44, 0x12,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

const uint8_t ucDisplayFullLupImage[5000] PROGMEM =
  {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,
   0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,
   0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,
   0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,
   0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,
   0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFC,0xE7,0xFC,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,
   0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFC,0xE7,0xFC,0xFF,0xFE,0x3F,0x1C,0x78,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,
   0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFC,0xFF,0xFC,0xFF,0xFE,0x1E,0x1E,0x79,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,
   0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFC,0xFF,0xFC,0xFF,0xFE,0x1E,0x1F,0x31,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,
   0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF0,0x7C,0xE7,0x84,0xF8,0x7E,0x5C,0x9F,0x13,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,
   0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xE0,0x1C,0xE7,0x00,0xE0,0x1E,0x4C,0x9F,0x87,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,
   0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xC7,0x9C,0xE6,0x38,0xE7,0x9E,0x4C,0x9F,0xC7,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,
   0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xCF,0xCC,0xE6,0x7C,0xCF,0xCE,0x61,0x9F,0xC7,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,
   0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xC0,0x0C,0xE6,0x7C,0xCF,0xCE,0x61,0x9F,0x87,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,
   0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xC0,0x0C,0xE6,0x7C,0xCF,0xCE,0x73,0x9F,0x93,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,
   0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xCC,0xE6,0x7C,0xCF,0xCE,0x73,0x9F,0x31,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,
   0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xDF,0x9C,0xE6,0x38,0xE7,0x9E,0x7F,0x9E,0x39,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,
   0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xC0,0x1C,0xE7,0x00,0xE0,0x1E,0x7F,0x9E,0x7C,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,
   0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xE0,0x7C,0xE7,0x84,0xF8,0x7E,0x7F,0x9C,0x7C,0x7F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,
   0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,
   0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,
   0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,
   0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,
   0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,
   0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,
   0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,
   0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,
   0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,
   0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,
   0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,
   0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,
   0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,
   0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,
   0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,
   0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,
   0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,
   0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,
   0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,
   0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,
   0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,
   0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,
   0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,0x07,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFB,0xFE,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,
   0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFC,0x03,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF9,0xFE,0x7F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,
   0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF8,0xF3,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF8,0xFC,0x7F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,
   0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF9,0xF3,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF8,0x78,0x7F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,
   0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF9,0xF3,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF8,0x30,0x7F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,
   0xFF,0xFF,0xFF,0x80,0xF8,0xF9,0xF9,0xF3,0xE0,0x3E,0x3E,0x7E,0x00,0xF8,0x0D,0x83,0x7F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,
   0xFF,0xFF,0xFF,0x00,0xFC,0x79,0xFC,0xF3,0xC0,0x1F,0x1E,0x7C,0x00,0xF0,0x0C,0xC3,0x3F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,
   0xFF,0xFF,0xFE,0x3F,0xFE,0x39,0xF8,0x03,0x8F,0x8F,0x8E,0x78,0xFC,0xE3,0xFC,0xE7,0x3F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,
   0xFF,0xFF,0xFE,0x7F,0xFF,0x19,0xF0,0x03,0x9F,0xCF,0xC6,0x79,0xFC,0xE7,0xFC,0xFF,0x3F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,
   0xFF,0xFF,0xFE,0x00,0xFF,0x89,0xE3,0xF3,0x9F,0xCF,0xE2,0x79,0xFC,0xE0,0x0C,0xFF,0x3F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,
   0xFF,0xFF,0xFE,0x00,0x7F,0xC1,0xE7,0xF3,0x9F,0xCF,0xF0,0x79,0xFC,0xE0,0x06,0xFF,0xBF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,
   0xFF,0xFF,0xFE,0x7E,0x3F,0xE1,0xE7,0xF3,0x9F,0xCF,0xF8,0x79,0xFC,0xE7,0xE2,0x7F,0x9F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,
   0xFF,0xFF,0xFE,0x7F,0x3F,0xC1,0xE7,0xF3,0x9F,0xCF,0xF0,0x79,0xFC,0xE7,0xF2,0x7F,0x9F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,
   0xFF,0xFF,0xFE,0x7F,0x3F,0x89,0xE7,0xF3,0x9F,0xCF,0xE2,0x79,0xFC,0xE7,0xF2,0x7F,0x9F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,
   0xFF,0xFF,0xFE,0x7F,0x3F,0x19,0xE7,0xF3,0x9F,0xCF,0xC6,0x79,0xFC,0xE7,0xF2,0x7F,0x9F,0xFF,0xFF,0xFE,0x3F,0xFF,0xFF,0xFF,0xFE,
   0xFF,0xFF,0xFE,0x7E,0x3E,0x39,0xE3,0xF3,0x8F,0x8F,0x8E,0x78,0xFC,0xE7,0xE2,0x7F,0x9F,0xFF,0xFF,0xF8,0x0F,0xFF,0xFF,0xFF,0xFE,
   0xFF,0xFF,0xFE,0x00,0x7C,0x79,0xF0,0x03,0xC0,0x1F,0x1E,0x7C,0x00,0xE0,0x07,0x3F,0xCF,0xFF,0xFF,0xF0,0x07,0xFF,0xFF,0xFF,0xFE,
   0xFF,0xFF,0xFE,0x00,0xF8,0xF9,0xF8,0x03,0xE0,0x3E,0x3E,0x7E,0x00,0xE0,0x0F,0x3F,0xCF,0xFF,0xFF,0xF0,0x07,0xFF,0xFF,0xFF,0xFE,
   0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFC,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF0,0x03,0xFF,0xFF,0xFF,0xFE,
   0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFC,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF0,0x03,0xFF,0xFF,0xFF,0xFE,
   0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFC,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF0,0x03,0xFF,0xFF,0xFF,0xFE,
   0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFC,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF0,0x03,0xFF,0xFF,0xFF,0xFE,
   0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFC,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF8,0x03,0xFF,0xFF,0xFF,0xFE,
   0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF8,0x03,0xFF,0xFF,0xFF,0xFE,
   0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF8,0x03,0xFF,0xFF,0xFF,0xFE,
   0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFC,0x03,0xFF,0xFF,0xFF,0xFE,
   0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFC,0x01,0xFF,0xFF,0xFF,0xFE,
   0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFC,0xF3,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFC,0x01,0xFF,0xFF,0xFF,0xFE,
   0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFC,0xF3,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFC,0x01,0xFF,0xFF,0xFF,0xFE,
   0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFC,0xF3,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFC,0x01,0xFF,0xFF,0xFF,0xFE,
   0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFC,0xF3,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,0x01,0xFF,0xFF,0xFF,0xFE,
   0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFC,0x73,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,0x01,0xFF,0xFF,0xFF,0xFE,
   0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFC,0x33,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,0x01,0xFF,0xFF,0xFF,0xFE,
   0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFC,0x93,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x01,0xFF,0xFF,0xFF,0xFE,
   0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFC,0xC3,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x01,0xFF,0xFF,0xFF,0xFE,
   0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFC,0xE3,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x01,0xFF,0xFF,0xFF,0xFE,
   0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFC,0xF3,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x01,0xFF,0xFF,0xFF,0xFE,
   0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFC,0xF3,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x01,0xFF,0xFF,0xFF,0xFE,
   0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFC,0xF3,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x80,0xFF,0xFF,0xFF,0xFE,
   0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFC,0xF3,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x80,0xFF,0xFF,0xFF,0xFE,
   0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x80,0xFF,0xFF,0xFF,0xFE,
   0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xC1,0xFF,0xFF,0xFF,0xFE,
   0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xC1,0xFF,0xFF,0xFF,0xFE,
   0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xC0,0xFF,0xFF,0xFF,0xFE,
   0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xE0,0xFF,0xFF,0xFF,0xFE,
   0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xE0,0xFF,0xFF,0xFF,0xFE,
   0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xE0,0xFF,0xFF,0xFF,0xFE,
   0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xE0,0xFF,0xFF,0xFF,0xFE,
   0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xE0,0xFF,0xFF,0xFF,0xFE,
   0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF0,0x7F,0xFF,0xFF,0xFE,
   0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF0,0x7F,0xFF,0xFF,0xFE,
   0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF0,0x7F,0xFF,0xFF,0xFE,
   0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF0,0x7F,0xFF,0xFF,0xFE,
   0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF0,0x7F,0xFF,0xFF,0xFE,
   0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF0,0x7F,0xFF,0xFF,0xFE,
   0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF0,0x7F,0xFF,0xFF,0xFE,
   0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF8,0x3F,0xFF,0xFF,0xFE,
   0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFC,0x7F,0xFF,0xFF,0xFE,
   0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFC,0x7F,0xFF,0xFF,0xFE,
   0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFC,0x7F,0xFF,0xFF,0xFE,
   0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFC,0x7F,0xFF,0xFF,0xFE,
   0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFC,0x7F,0xFF,0xFF,0xFE,
   0xFF,0xFF,0xFF,0xFF,0xFF,0xE0,0x1F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF8,0x3F,0xFF,0xFF,0xFE,
   0xFF,0xFF,0xFF,0xC0,0x00,0x00,0x00,0x07,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFC,0x1F,0xFF,0xFF,0xFE,
   0xFF,0xFF,0xFF,0x80,0x00,0x00,0x00,0x01,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFC,0x1F,0xFF,0xFF,0xFE,
   0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFC,0x1F,0xFF,0xFF,0xFE,
   0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x1F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFC,0x1F,0xFF,0xFF,0xFE,
   0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x1F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFC,0x1F,0xFF,0xFF,0xFE,
   0xFF,0xFF,0xFE,0x00,0x00,0x00,0x00,0x00,0x0F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xE0,0xFF,0xFF,0xFF,0xFF,0xFE,0x3F,0xFF,0xFF,0xFE,
   0xFF,0xFF,0xFC,0x00,0x00,0x00,0x00,0x00,0x0F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xC0,0x7F,0xFF,0xFF,0xFF,0xFE,0x1F,0xFF,0xFF,0xFE,
   0xFF,0xFF,0xFC,0x01,0xFF,0xE0,0x00,0x00,0x0F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x80,0x7F,0xFF,0xFF,0xFF,0xFE,0x1F,0xFF,0xFF,0xFE,
   0xFF,0xFF,0xF8,0x03,0xFF,0xFF,0xE0,0x00,0x07,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x80,0x7F,0xFF,0xFF,0xFF,0xFF,0x1F,0xFF,0xFF,0xFE,
   0xFF,0xFF,0xF8,0x03,0xFF,0xFF,0xFF,0xF0,0x03,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x80,0x3F,0xFF,0xFF,0xFF,0xFF,0x1F,0xFF,0xFF,0xFE,
   0xFF,0xFF,0xF0,0x03,0xFF,0xFF,0xFF,0xF8,0x03,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x80,0x3F,0xFF,0xFF,0xFF,0xFE,0x0F,0xFF,0xFF,0xFE,
   0xFF,0xFF,0xF0,0x03,0xFF,0xFF,0xFF,0xF8,0x03,0xFF,0xFF,0xFF,0xFF,0xC1,0xFF,0x80,0x3F,0xFF,0xFF,0xFF,0xFE,0x0F,0xFF,0xFF,0xFE,
   0xFF,0xFF,0xE0,0x07,0xFF,0xFF,0xFF,0xF8,0x03,0xFF,0xFF,0xFF,0xFF,0x80,0xFF,0x80,0x3F,0xFF,0xFF,0xFF,0xFF,0x07,0xFF,0xFF,0xFE,
   0xFF,0xFF,0xC0,0x07,0xFF,0xFF,0xFF,0xF8,0x03,0xFF,0xFF,0xFF,0xFF,0x00,0x7F,0x80,0x3F,0xFF,0xFF,0xFF,0xFF,0x07,0xFF,0xFF,0xFE,
   0xFF,0xFF,0xC0,0x0F,0xFF,0xFF,0xFF,0xF8,0x03,0xFF,0xFF,0xFF,0xFF,0x00,0x3F,0x80,0x3F,0xFF,0xFF,0xFF,0xFF,0x07,0xFF,0xFF,0xFE,
   0xFF,0xFF,0x80,0x1F,0xFF,0xFF,0xFF,0xF8,0x03,0xFF,0xFF,0xFF,0xFF,0x00,0x3F,0x80,0x3F,0xFF,0xFF,0xFF,0xFF,0x07,0xFF,0xFF,0xFE,
   0xFF,0xFF,0x80,0x1F,0xFF,0xFF,0xFF,0xF8,0x03,0xFF,0xFF,0xFF,0xFF,0x00,0x1F,0xC0,0x1F,0xFF,0xFF,0xFF,0xFF,0x83,0xFF,0xFF,0xFE,
   0xFF,0xFF,0x80,0x3F,0xFF,0xFF,0xFF,0xF8,0x03,0xFF,0xFF,0xFF,0xFF,0x00,0x1F,0xC0,0x1F,0xFF,0xFF,0xFF,0xFF,0x83,0xFF,0xFF,0xFE,
   0xFF,0xFF,0x80,0x7F,0xFF,0xFF,0xFF,0xF8,0x03,0xFF,0xFF,0xFF,0xFF,0x00,0x1F,0xC0,0x1F,0xFF,0xFF,0xFF,0xFF,0x83,0xFF,0xFF,0xFE,
   0xFF,0xFF,0x00,0x7F,0xFF,0xFF,0xFF,0xF8,0x03,0xFF,0xFF,0xFF,0xFE,0x00,0x1F,0xC0,0x1F,0xFF,0xFF,0xFF,0xFF,0xC3,0xFF,0xFF,0xFE,
   0xFF,0xFF,0x00,0xFF,0xFF,0xFF,0xFF,0xF8,0x03,0xFF,0xFF,0xFF,0xFE,0x00,0x1F,0xC0,0x1F,0xFF,0xFF,0xFF,0xFF,0xC1,0xFF,0xFF,0xFE,
   0xFF,0xFE,0x00,0xFF,0xFF,0xFF,0xFF,0xF8,0x03,0xFF,0xFF,0xFF,0xFC,0x00,0x1F,0xC0,0x1F,0xFF,0xFF,0xFF,0xFF,0xE0,0xFF,0xFF,0xFE,
   0xFF,0xFE,0x00,0xFF,0xFF,0xFF,0xFF,0xF8,0x03,0xFF,0xFF,0xFF,0xFC,0x00,0x1F,0xC0,0x1F,0xFF,0xFF,0xFF,0xFF,0xE0,0xFF,0xFF,0xFE,
   0xFF,0xFE,0x00,0xFF,0xFF,0xFF,0xFF,0xF8,0x03,0xFF,0xFF,0xFF,0xFC,0x00,0x1F,0xE0,0x0F,0xFF,0xFF,0xFF,0xFF,0xE0,0x7F,0xFF,0xFE,
   0xFF,0xFE,0x00,0xFF,0xFF,0xFF,0xFF,0xF8,0x03,0xFF,0xFF,0xFF,0xFC,0x00,0x1F,0xE0,0x0F,0xFF,0xFF,0xFF,0xFF,0xF0,0x7F,0xFF,0xFE,
   0xFF,0xFE,0x00,0xFF,0xFF,0xFF,0xFF,0xF8,0x03,0xFF,0xFF,0xFF,0xFC,0x00,0x1F,0xE0,0x0F,0xFF,0xFF,0xFF,0xFF,0xF0,0x7F,0xFF,0xFE,
   0xFF,0xFE,0x00,0xFF,0xFF,0xFF,0xFF,0xFC,0x03,0xFF,0xFF,0xFF,0xFE,0x00,0x1F,0xE0,0x0F,0xFF,0xFF,0xFF,0xFF,0xF8,0x3F,0xFF,0xFE,
   0xFF,0xFE,0x00,0xFF,0xFF,0xFF,0xFF,0xFC,0x03,0xFF,0xFF,0xFF,0xFE,0x00,0x1F,0xE0,0x0F,0xFF,0xFF,0xFF,0xFF,0xF8,0x1F,0xFF,0xFE,
   0xFF,0xFE,0x00,0x7F,0xFF,0xFF,0xFF,0xFE,0x03,0xFF,0xFF,0xFF,0xFE,0x00,0x1F,0xE0,0x0F,0xFF,0xFF,0xFF,0xFF,0xFC,0x1F,0xFF,0xFE,
   0xFF,0xFE,0x00,0x7F,0xFF,0xFF,0xFF,0xFE,0x03,0xFF,0xFF,0xFF,0xFC,0x00,0x1F,0xF0,0x0F,0xFF,0xFF,0xFF,0xFF,0xFC,0x0F,0xFF,0xFE,
   0xFF,0xFE,0x00,0x3F,0xFF,0xFF,0xFF,0xFE,0x03,0xFF,0xFF,0xFF,0xFC,0x00,0x1F,0xF0,0x0F,0xFF,0xFF,0xFF,0xFF,0xFC,0x07,0xFF,0xFE,
   0xFF,0xFF,0x00,0x0F,0xFF,0xFF,0xFF,0xFE,0x03,0xFF,0xFF,0xFF,0xFC,0x00,0x1F,0xF8,0x0F,0xFF,0xFF,0xFF,0xFF,0xFE,0x07,0xFF,0xFE,
   0xFF,0xFF,0x00,0x07,0xFF,0xFF,0xFF,0xFE,0x03,0xFF,0xFF,0xFF,0xFC,0x00,0x1F,0xF8,0x0F,0xFF,0xFF,0xFF,0xFF,0xFF,0x03,0xFF,0xFE,
   0xFF,0xFF,0x80,0x03,0xFF,0xFF,0xFF,0xFF,0x07,0xFF,0xFF,0xFF,0xF8,0x00,0x1F,0xF8,0x0F,0xFF,0xFF,0xFF,0xFF,0xFF,0x03,0xFF,0xFE,
   0xFF,0xFF,0x80,0x00,0x7F,0xFF,0xFF,0xFF,0x03,0xFF,0xFF,0xFF,0xF8,0x00,0x1F,0xF8,0x0F,0xFF,0xFF,0xFF,0xFF,0xFF,0x81,0xFF,0xFE,
   0xFF,0xFF,0x80,0x00,0x03,0xFF,0xFF,0xFF,0x03,0xFF,0xFF,0xFF,0xF0,0x00,0x1F,0xF8,0x0F,0xFF,0xFF,0xFF,0xFF,0xFF,0x80,0xFF,0xFE,
   0xFF,0xFF,0xC0,0x00,0x00,0x3F,0xFF,0xFF,0x03,0xFF,0xFF,0xFF,0xE0,0x00,0x1F,0xF8,0x0F,0xFF,0xFF,0xFF,0xFF,0xFF,0xC0,0x7F,0xFE,
   0xFF,0xFF,0xE0,0x00,0x00,0x00,0xFF,0xFF,0x03,0xFF,0xFF,0xFF,0xC0,0x00,0x1F,0xF8,0x0F,0xFF,0xFF,0xFF,0xFF,0xFF,0xC0,0x7F,0xFE,
   0xFF,0xFF,0xF8,0x00,0x00,0x00,0x00,0xFF,0x81,0xFF,0xFF,0xFF,0x80,0x00,0x0F,0xF8,0x0F,0xFF,0xFF,0xFF,0xFF,0xFF,0xE0,0x3F,0xFE,
   0xFF,0xFF,0xFC,0x00,0x00,0x00,0x00,0x00,0x01,0xFF,0xFF,0xFF,0x80,0x00,0x0F,0xF8,0x0F,0xFF,0xFF,0xFF,0xFF,0xFF,0xE0,0x3F,0xFE,
   0xFF,0xFF,0xFE,0x00,0x00,0x00,0x00,0x00,0x01,0xFF,0xFF,0xFF,0x00,0x00,0x07,0xF8,0x0F,0xFF,0xFF,0xFF,0xFF,0xFF,0xF0,0x1F,0xFE,
   0xFF,0xFF,0xFF,0x80,0x00,0x00,0x00,0x00,0x01,0xFF,0xFF,0xFF,0x00,0x00,0x01,0xF0,0x0F,0xFF,0xFF,0xFF,0xFF,0xFF,0xF0,0x1F,0xFE,
   0xFF,0xFF,0xFF,0xC0,0x00,0x00,0x00,0x00,0x01,0xFF,0xFF,0xFF,0x00,0x00,0x00,0xE0,0x07,0xFE,0x0F,0xFF,0xFF,0xFF,0xF8,0x1F,0xFE,
   0xFF,0xFF,0xFF,0xF8,0x00,0x00,0x00,0x00,0x01,0xFF,0xFF,0xFF,0x00,0x20,0x00,0x20,0x07,0xFC,0x07,0xFF,0xFF,0xFF,0xF8,0x1F,0xFE,
   0xFF,0xFF,0xFF,0xFF,0xC0,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0x00,0x70,0x00,0x00,0x0F,0xF8,0x03,0xFF,0xFF,0xFF,0xFC,0x0F,0xFE,
   0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0x00,0x78,0x00,0x00,0x0F,0xF8,0x03,0xFF,0xFF,0xFF,0xF8,0x0F,0xFE,
   0xFF,0xFF,0xFF,0xFF,0xFF,0xF8,0x00,0x00,0x00,0xFF,0xFF,0xFF,0x80,0xFC,0x00,0x00,0x1F,0xF8,0x03,0xFF,0xFF,0xFF,0xFC,0x07,0xFE,
   0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF0,0x00,0x00,0x7F,0xFF,0xFF,0xC1,0xFE,0x00,0x00,0x1F,0xF8,0x03,0xFF,0xFF,0xFF,0xFC,0x07,0xFE,
   0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,0x00,0x00,0x3F,0xFF,0xFF,0xFF,0xFE,0x00,0x00,0x1F,0xF0,0x03,0xFF,0xFF,0xFF,0xFC,0x03,0xFE,
   0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF0,0x00,0x3F,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x3F,0xF0,0x03,0xFF,0xFF,0xFF,0xFE,0x01,0xFE,
   0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x88,0x3F,0xFF,0xFF,0xFF,0xFF,0xC0,0x00,0x7F,0xF0,0x07,0xFF,0xFF,0xFF,0xFE,0x01,0xFE,
   0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF8,0x1F,0xFF,0xFF,0xFF,0xFF,0xC0,0x00,0xFF,0xF0,0x07,0xFF,0xFF,0xFF,0xFE,0x01,0xFE,
   0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF8,0x1F,0xFF,0xFF,0xFF,0xFF,0xE0,0x01,0xFF,0xF0,0x07,0xFF,0xFF,0xFF,0xFF,0x01,0xFE,
   0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFC,0x1F,0xFF,0xFF,0xFF,0xFF,0xF0,0x03,0xFF,0xF0,0x07,0xFF,0xFF,0xFF,0xFF,0x00,0xFE,
   0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFC,0x0F,0xFF,0xFF,0xFF,0xFF,0xFC,0x1F,0xFF,0xF0,0x07,0xFF,0xFF,0xFF,0xFF,0x00,0x7E,
   0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,0x0F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF0,0x07,0xF8,0x00,0x00,0x00,0x00,0x7E,
   0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x0F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF0,0x00,0x00,0x00,0x00,0x00,0x00,0x7E,
   0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x87,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF0,0x00,0x00,0x00,0x00,0x00,0x00,0x3E,
   0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x87,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF0,0x00,0x00,0x00,0x00,0x00,0x00,0x1E,
   0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xC3,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF0,0x00,0x00,0x00,0x00,0x00,0x00,0x1E,
   0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xC3,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF8,0x00,0x00,0x00,0x00,0x00,0x00,0x1E,
   0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xE3,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF8,0x00,0x00,0x00,0x00,0x00,0x00,0x3E,
   0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xC1,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF8,0x00,0x00,0x00,0x00,0x00,0x00,0x7E,
   0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xE0,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFC,0x00,0x00,0x00,0x00,0x00,0x00,0xFE,
   0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xE0,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF0,0x01,0xFF,0xFF,0xFF,0xFF,0xFE,
   0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xE0,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,
   0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF0,0x7F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,
   0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF8,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,
   0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF8,0x7F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,
   0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF8,0x7F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,
   0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFC,0x3F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,
   0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFC,0x1F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,
   0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFC,0x1F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,
   0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFC,0x1F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,
   0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,0x0F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,
   0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,0x0F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,
   0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,0x0F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,
   0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,0x07,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,
   0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,0x07,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,
   0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x03,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,
   0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,0x03,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,
   0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x03,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,
   0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x03,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,
   0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x83,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,
   0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x81,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,
   0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x81,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,
   0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x80,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,
   0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x80,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,
   0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x80,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,
   0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x80,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,
   0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x7F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,
   0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x7F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,
   0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x7F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,
   0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x80,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,
   0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xC1,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,
   0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xE3,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE};


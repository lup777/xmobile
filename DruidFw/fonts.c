// fonts.c

#include "fonts.h"

#include <avr/pgmspace.h>

#define FONTS_NUM 128

const uint8_t FONT_nimbus_bold_16_1[][FONTS_NUM] PROGMEM = {
  {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
  {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
  {0x8, 0x19, 12, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},//32
  //(пробел) Source image file: "F:\Images\xmobile-fonts\pt-mono-bold\8x13\bmp\pt-mono-bold-dot-8x13.bmp"
  
  {0x10, 0x19, 12, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x3f, 0xff, 0x3f, 0xff, 0x3f, 0xff, 0x3f, 0xff, 0x3f, 0xff, 0x3f, 0xff, 0x3f, 0xff, 0x3f, 0xff, 0x3f, 0xff, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0x3f, 0xff, 0x3f, 0xff, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff}, //33
  //!  Source image file: "pt-mono-bold-$-8x13.bmp"
  
  {0x10, 0x19, 12, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x9f, 0xf9, 0x9f, 0xf9, 0x9f, 0xf9, 0x9f, 0xf9, 0x9f, 0xf9, 0x9f, 0xf9, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},//34
  //" Source image file: "pt-mono-bold-6-8x13.bmp"
  
  {0x10, 0x16, 12, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x3f, 0xf3, 0xbf, 0xf3, 0xbf, 0xfb, 0xbf, 0xfb, 0x3, 0xc0, 0x3, 0xc0, 0xdf, 0xf9, 0xdf, 0xfd, 0xcf, 0xfd, 0x1, 0xe0, 0x1, 0xe0, 0xef, 0xfc, 0xef, 0xfe, 0xe7, 0xfe, 0x67, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},//35
  //# Source image file: "pt-mono-bold-i-8x13.bmp"
  
  {0x10, 0x18, 12, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0xff, 0x7f, 0xff, 0x1f, 0xfc, 0xf, 0xf8, 0x47, 0xfb, 0x67, 0xff, 0x67, 0xff, 0xf, 0xfe, 0x1f, 0xf8, 0x7f, 0xf1, 0x7f, 0xf3, 0x7f, 0xf3, 0x77, 0xf1, 0x7, 0xf8, 0xf, 0xfc, 0x7f, 0xff, 0x7f, 0xff, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff},//36
  //$  Source image file: "pt-mono-bold-(-8x13.bmp"
  
  {0x10, 0x13, 12, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe3, 0xfb, 0xdd, 0xfb, 0xdd, 0xfd, 0xdd, 0xfc, 0xdd, 0xfe, 0x63, 0xff, 0x7f, 0xe3, 0xbf, 0xdd, 0x9f, 0xdd, 0xdf, 0xdd, 0xef, 0xdd, 0xef, 0xe3, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},//37
  //% Source image file: "pt-mono-bold-plus-8x13.bmp"
  
  {0x10, 0x18, 12, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x1f, 0xfe, 0xf, 0xfc, 0xc7, 0xfd, 0xe7, 0xff, 0xe7, 0xff, 0xc7, 0xff, 0x87, 0xff, 0x3, 0xcf, 0x31, 0xc6, 0x79, 0xe4, 0xf9, 0xe0, 0xf9, 0xf1, 0xe3, 0xe0, 0x3, 0xc4, 0xf, 0x8f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},//38
  //& Source image file: "pt-mono-bold-b-8x13.bmp"
  
  {0x8, 0x18, 12, 0xff, 0xff, 0xff, 0xff, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},//39
  //' Source image file: "pt-mono-bold-8-8x13.bmp"
  
  {0x8, 0x18, 12, 0xff, 0xff, 0xff, 0xff, 0xcf, 0xef, 0xe7, 0xe7, 0xf7, 0xf3, 0xf3, 0xf3, 0xf3, 0xf3, 0xf3, 0xf3, 0xf3, 0xe7, 0xe7, 0xe7, 0xef, 0xcf, 0xff, 0xff},//40
  //( Source image file: "pt-mono-bold-)-8x13.bmp"
  
  {0x8, 0x18, 12, 0xff, 0xff, 0xff, 0xff, 0xf3, 0xf7, 0xe7, 0xe7, 0xef, 0xcf, 0xcf, 0xcf, 0xcf, 0xcf, 0xcf, 0xcf, 0xcf, 0xe7, 0xe7, 0xe7, 0xf7, 0xf3, 0xff, 0xff},//41
  //)  Source image file: "pt-mono-bold-1-8x13.bmp"
  
  {0x10, 0x18, 12, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0xff, 0x7f, 0xff, 0x77, 0xf7, 0x4f, 0xf9, 0x3f, 0xfe, 0x3f, 0xfe, 0x4f, 0xf9, 0x77, 0xf7, 0x7f, 0xff, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},//42
  //* Source image file: "pt-mono-bold-t-8x13.bmp"
  
  {0x10, 0x16, 12, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0xfe, 0x7f, 0xfe, 0x7f, 0xfe, 0x7f, 0xfe, 0x7f, 0xfe, 0x3, 0xc0, 0x3, 0xc0, 0x7f, 0xfe, 0x7f, 0xfe, 0x7f, 0xfe, 0x7f, 0xfe, 0x7f, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},//43
  //+ Source image file: "pt-mono-bold-r-8x13.bmp"
  
  {0x8, 0x18, 6, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf3, 0xf3, 0xf3, 0xf9, 0xfd, 0xff, 0xff},//44
  //, Source image file: "pt-mono-bold-{-8x13.bmp"
  
  {0x8, 0x18, 12, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc1, 0xc1, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},//45
  //- Source image file: "pt-mono-bold-n-8x13.bmp"
  
  {0x8, 0x18, 6, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf3, 0xf3, 0xff, 0xff, 0xff, 0xff, 0xff},//46
  //. Source image file: "F:\Images\xmobile-fonts\pt-mono-bold\8x13\bmp\pt-mono-bold-0-8x13.bmp"
  
  {0x8, 0x18, 12, 0xff, 0xff, 0xff, 0xff, 0x9f, 0x8f, 0xcf, 0xcf, 0xcf, 0xe7, 0xe7, 0xe7, 0xf3, 0xf3, 0xf3, 0xf9, 0xf9, 0xf9, 0xf8, 0xfc, 0xff, 0xff, 0xff, 0xff},//47
  /// Source image file: "pt-mono-bold-star-8x13.bmp"
  
  {0x10, 0x18, 11, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x1f, 0xfe, 0xf, 0xfc, 0xe7, 0xf9, 0xe7, 0xf9, 0xf3, 0xf3, 0xf3, 0xf3, 0xf3, 0xf3, 0xf3, 0xf3, 0xf3, 0xf3, 0xf3, 0xf3, 0xf3, 0xf3, 0xe7, 0xf9, 0xe7, 0xf9, 0xf, 0xfc, 0x1f, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},//48
  //0 Source image file: "F:\Images\xmobile-fonts\pt-mono-bold\8x13\bmp\pt-mono-bold-dvoetochie-8x13.bmp"
  
  {0x10, 0x18, 11, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x1f, 0xfe, 0x7, 0xfe, 0x67, 0xfe, 0x7f, 0xfe, 0x7f, 0xfe, 0x7f, 0xfe, 0x7f, 0xfe, 0x7f, 0xfe, 0x7f, 0xfe, 0x7f, 0xfe, 0x7f, 0xfe, 0x7f, 0xfe, 0x7f, 0xfe, 0xf, 0xf0, 0xf, 0xf0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},//49
  //1  Source image file: "pt-mono-bold-2-8x13.bmp"
  
  {0x10, 0x18, 11, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7, 0xfe, 0x3, 0xfc, 0xfb, 0xf8, 0xff, 0xf9, 0xff, 0xf9, 0xff, 0xf9, 0xff, 0xfc, 0x7f, 0xfc, 0x3f, 0xfe, 0x3f, 0xff, 0x8f, 0xff, 0xc7, 0xff, 0xe3, 0xff, 0x3, 0xf8, 0x3, 0xf8, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},//50
  //2 Source image file: "pt-mono-bold-222-8x13.bmp"
  
  {0x10, 0x18, 11, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7, 0xfe, 0x3, 0xfc, 0xfb, 0xf8, 0xff, 0xf9, 0xff, 0xf9, 0xff, 0xf8, 0x1f, 0xfe, 0x1f, 0xfc, 0xff, 0xf9, 0xff, 0xf3, 0xff, 0xf3, 0xff, 0xf3, 0xfb, 0xf1, 0x3, 0xf8, 0x7, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},//51
  //3 Source image file: "pt-mono-bold-4-8x13.bmp"
  
  {0x10, 0x18, 11, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x7f, 0xf8, 0x7f, 0xf9, 0x3f, 0xf9, 0xbf, 0xf9, 0x9f, 0xf9, 0xcf, 0xf9, 0xef, 0xf9, 0xe7, 0xf9, 0xf3, 0xf9, 0x3, 0xe0, 0x3, 0xe0, 0xff, 0xf9, 0xff, 0xf9, 0xff, 0xf9, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},//52
  //4 Source image file: "pt-mono-bold-44-8x13.bmp"
  
  {0x10, 0x18, 11, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7, 0xfc, 0x7, 0xfc, 0xe7, 0xff, 0xe7, 0xff, 0xe7, 0xff, 0x7, 0xfe, 0x7, 0xfc, 0xf7, 0xf8, 0xff, 0xf9, 0xff, 0xf9, 0xff, 0xf9, 0xff, 0xf9, 0xfb, 0xfc, 0x3, 0xfc, 0x7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},//53
  //5 Source image file: "pt-mono-bold-555-8x13.bmp"
  
  {0x10, 0x18, 11, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x3f, 0xfc, 0xf, 0xf8, 0xc7, 0xfb, 0xe7, 0xff, 0xe3, 0xff, 0xf3, 0xff, 0x33, 0xfc, 0x3, 0xf8, 0xe3, 0xf1, 0xf3, 0xf3, 0xf3, 0xf3, 0xf3, 0xf3, 0xe7, 0xf1, 0x7, 0xf8, 0x1f, 0xfc, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},//54
  //6 Source image file: "pt-mono-bold-7-8x13.bmp"
  
  {0x10, 0x18, 11, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x3, 0xf0, 0x3, 0xf0, 0xff, 0xf9, 0xff, 0xf9, 0xff, 0xf9, 0xff, 0xfc, 0xff, 0xfc, 0xff, 0xfc, 0x7f, 0xfe, 0x7f, 0xfe, 0x7f, 0xfe, 0x3f, 0xff, 0x3f, 0xff, 0x3f, 0xff, 0x9f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},//55
  //7 Source image file: "pt-mono-bold-777-8x13.bmp"
  
  {0x10, 0x18, 11, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf, 0xfc, 0x7, 0xf8, 0xe3, 0xf1, 0xf3, 0xf3, 0xf3, 0xf3, 0xe7, 0xf9, 0xf, 0xfc, 0x7, 0xf8, 0xe7, 0xf9, 0xf3, 0xf3, 0xf3, 0xf3, 0xf3, 0xf3, 0xe3, 0xf1, 0x7, 0xf8, 0xf, 0xfc, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},//56
  //8 Source image file: "pt-mono-bold-9-8x13.bmp"
  
  {0x10, 0x18, 11, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf, 0xfe, 0x7, 0xf8, 0xe3, 0xf9, 0xf3, 0xf3, 0xf3, 0xf3, 0xf3, 0xf3, 0xe3, 0xf1, 0x7, 0xf0, 0xf, 0xf3, 0xff, 0xf3, 0xff, 0xf1, 0xff, 0xf9, 0xf7, 0xf8, 0x7, 0xfc, 0xf, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},//57
  //9 Source image file: "pt-mono-bold-[-8x13.bmp"
  
  {0x8, 0x18, 6, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf3, 0xf3, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf3, 0xf3, 0xff, 0xff, 0xff, 0xff, 0xff},//58
  //: Source image file: "pt-mono-bold-a-8x13.bmp"
  
  {},
  {0x10, 0x16, 12, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xdf, 0xff, 0xc3, 0x7f, 0xe0, 0xf, 0xfc, 0x83, 0xff, 0x83, 0xff, 0xf, 0xfc, 0x7f, 0xe0, 0xff, 0xc3, 0xff, 0xdf, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},//60
  //< Source image file: "pt-mono-bold-3-8x13.bmp"
      
  {0x18, 0x18, 12, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x1f, 0x0, 0xfc, 0x1f, 0x0, 0xfc, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x1f, 0x0, 0xfc, 0x1f, 0x0, 0xfc, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff}, // 61
  // =
  
  {0x18, 0x18, 12, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xdf, 0xff, 0xff, 0x1f, 0xfe, 0xff, 0x3f, 0xf0, 0xff, 0xff, 0x81, 0xff, 0xff, 0xf, 0xfc, 0xff, 0x3f, 0xfc, 0xff, 0xf, 0xfc, 0xff, 0x81, 0xff, 0x3f, 0xf0, 0xff, 0x1f, 0xfe, 0xff, 0xdf, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff}, // 62
  // >
  
  
  {0x10, 0x18, 12, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf, 0xfe, 0x7, 0xfc, 0xf7, 0xf8, 0xff, 0xf9, 0xff, 0xf9, 0xff, 0xf8, 0x7f, 0xfc, 0x3f, 0xfe, 0x1f, 0xff, 0x9f, 0xff, 0x9f, 0xff, 0x9f, 0xff, 0xff, 0xff, 0x9f, 0xff, 0x9f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},//63
  //? Source image file: "pt-mono-bold-x-8x13.bmp"
  
  {0x18, 0x18, 12, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x81, 0xff, 0x7f, 0x0, 0xfc, 0x3f, 0x7c, 0xf8, 0x1f, 0xff, 0xf1, 0x8f, 0xff, 0xf3, 0xcf, 0x23, 0xe7, 0xe7, 0x1, 0xe7, 0xe7, 0x18, 0xe7, 0xe7, 0x3c, 0xe7, 0xe7, 0x3c, 0xe3, 0xe7, 0x18, 0xf1, 0xe7, 0x1, 0xf8, 0xcf, 0x23, 0xfe, 0x8f, 0xff, 0xff, 0x1f, 0xff, 0xfe, 0x3f, 0x3e, 0xfe, 0x7f, 0x0, 0xff, 0xff, 0xc1, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff}, // 64
  // @
  
    
  // ENGLISH
  {0x10, 0x18, 12, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x3f, 0xfe, 0x3f, 0xfe, 0x3f, 0xfe, 0x9f, 0xfc, 0x9f, 0xfc, 0x8f, 0xf8, 0xcf, 0xf9, 0xcf, 0xf9, 0xe7, 0xf3, 0xe7, 0xf3, 0x7, 0xf0, 0x3, 0xe0, 0xf3, 0xe7, 0xf3, 0xe7, 0xf9, 0xcf, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff}, // 65
  // A
  
  {0x10, 0x18, 12, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7, 0xfc, 0x7, 0xf8, 0xe7, 0xf1, 0xe7, 0xf3, 0xe7, 0xf3, 0xe7, 0xf1, 0x7, 0xf8, 0x7, 0xf8, 0xe7, 0xf3, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xe3, 0x7, 0xf0, 0x7, 0xf8, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff}, // 66
  // B
  
  {0x10, 0x18, 12, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x3f, 0xe0, 0xf, 0xc0, 0x8f, 0xdf, 0xe7, 0xff, 0xe3, 0xff, 0xf3, 0xff, 0xf3, 0xff, 0xf3, 0xff, 0xf3, 0xff, 0xf3, 0xff, 0xe3, 0xff, 0xe7, 0xff, 0x8f, 0xdf, 0xf, 0xc0, 0x3f, 0xe0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff}, // 67
  // C
  
  {0x10, 0x18, 12, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x3, 0xfc, 0x3, 0xf0, 0xf3, 0xe1, 0xf3, 0xe7, 0xf3, 0xc7, 0xf3, 0xcf, 0xf3, 0xcf, 0xf3, 0xcf, 0xf3, 0xcf, 0xf3, 0xcf, 0xf3, 0xc7, 0xf3, 0xe7, 0xf3, 0xe1, 0x3, 0xf0, 0x3, 0xfc, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff}, // 68
  // D
  
  {0x10, 0x18, 12, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7, 0xf0, 0x7, 0xf0, 0xe7, 0xff, 0xe7, 0xff, 0xe7, 0xff, 0xe7, 0xff, 0x7, 0xf0, 0x7, 0xf0, 0xe7, 0xff, 0xe7, 0xff, 0xe7, 0xff, 0xe7, 0xff, 0xe7, 0xff, 0x7, 0xf0, 0x7, 0xf0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff}, // 69
  // E
  
  {0x10, 0x18, 12, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf, 0xf0, 0xf, 0xf0, 0xcf, 0xff, 0xcf, 0xff, 0xcf, 0xff, 0xcf, 0xff, 0xf, 0xf8, 0xf, 0xf8, 0xcf, 0xff, 0xcf, 0xff, 0xcf, 0xff, 0xcf, 0xff, 0xcf, 0xff, 0xcf, 0xff, 0xcf, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff}, // 70
  // F
  
  {0x10, 0x18, 12, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x1f, 0xf0, 0x7, 0xe0, 0xc3, 0xef, 0xf3, 0xff, 0xf1, 0xff, 0xf9, 0xff, 0xf9, 0xff, 0xf9, 0xc1, 0xf9, 0xc1, 0xf9, 0xcf, 0xf1, 0xcf, 0xf3, 0xcf, 0xc7, 0xcf, 0xf, 0xe0, 0x1f, 0xf8, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff}, // 71
  // G
  
  {0x10, 0x18, 12, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf3, 0xe7, 0xf3, 0xe7, 0xf3, 0xe7, 0xf3, 0xe7, 0xf3, 0xe7, 0xf3, 0xe7, 0x3, 0xe0, 0x3, 0xe0, 0xf3, 0xe7, 0xf3, 0xe7, 0xf3, 0xe7, 0xf3, 0xe7, 0xf3, 0xe7, 0xf3, 0xe7, 0xf3, 0xe7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff}, // 72
  // H
  
  {0x8, 0x18, 5, 0xff, 0xff, 0xff, 0xff, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xff, 0xff, 0xff, 0xff, 0xff}, // 73
  // I
  
  {0x8, 0x18, 12, 0xff, 0xff, 0xff, 0xff, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xe3, 0xf0, 0xf8, 0xff}, // 74
  // J
  
  {0x10, 0x18, 12, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe7, 0xe3, 0xe7, 0xf1, 0xe7, 0xf8, 0x67, 0xfc, 0x27, 0xfe, 0x7, 0xff, 0x87, 0xff, 0x87, 0xff, 0x7, 0xff, 0x27, 0xfe, 0x67, 0xfc, 0xe7, 0xf8, 0xe7, 0xf1, 0xe7, 0xe3, 0xe7, 0xc7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff}, // 75
  // K
  
  {0x10, 0x18, 12, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xcf, 0xff, 0xcf, 0xff, 0xcf, 0xff, 0xcf, 0xff, 0xcf, 0xff, 0xcf, 0xff, 0xcf, 0xff, 0xcf, 0xff, 0xcf, 0xff, 0xcf, 0xff, 0xcf, 0xff, 0xcf, 0xff, 0xcf, 0xff, 0xf, 0xe0, 0xf, 0xe0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff}, // 76
  // L
  
  {0x18, 0x18, 15, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x1f, 0x3e, 0xfc, 0x1f, 0x3e, 0xfc, 0x1f, 0x3e, 0xfc, 0x9f, 0x9c, 0xfc, 0x9f, 0x9c, 0xfc, 0x9f, 0x9c, 0xfc, 0x9f, 0xc9, 0xfc, 0x9f, 0xc9, 0xfc, 0x9f, 0xc9, 0xfc, 0x9f, 0xe3, 0xfc, 0x9f, 0xe3, 0xfc, 0x9f, 0xe3, 0xfc, 0x9f, 0xff, 0xfc, 0x9f, 0xff, 0xfc, 0x9f, 0xff, 0xfc, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff}, // 77
  // M
  
  {0x10, 0x18, 12, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe3, 0xe7, 0xc3, 0xe7, 0xc3, 0xe7, 0x83, 0xe7, 0x93, 0xe7, 0x13, 0xe7, 0x33, 0xe7, 0x33, 0xe6, 0x73, 0xe6, 0x73, 0xe4, 0xf3, 0xe4, 0xf3, 0xe0, 0xf3, 0xe1, 0xf3, 0xe3, 0xf3, 0xe3, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff}, // 78
  // N
  
  {0x10, 0x18, 12, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x1f, 0xf8, 0x7, 0xe0, 0xc7, 0xe3, 0xf3, 0xcf, 0xf1, 0x8f, 0xf9, 0x9f, 0xf9, 0x9f, 0xf9, 0x9f, 0xf9, 0x9f, 0xf9, 0x9f, 0xf1, 0x8f, 0xf3, 0xcf, 0xc7, 0xe3, 0x7, 0xe0, 0x1f, 0xf8, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff}, // 79
  // O
  
  {0x10, 0x18, 12, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7, 0xfc, 0x7, 0xf8, 0xe7, 0xf1, 0xe7, 0xf3, 0xe7, 0xf3, 0xe7, 0xf3, 0xe7, 0xf1, 0x7, 0xf8, 0x7, 0xfc, 0xe7, 0xff, 0xe7, 0xff, 0xe7, 0xff, 0xe7, 0xff, 0xe7, 0xff, 0xe7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff}, // 80
  // P
  
  {0x10, 0x18, 12, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x1f, 0xf8, 0x7, 0xe0, 0xc7, 0xc3, 0xf3, 0xcf, 0xf1, 0x8f, 0xf9, 0x9f, 0xf9, 0x9f, 0xf9, 0x9f, 0xf9, 0x9f, 0xf9, 0x9f, 0xf1, 0x8f, 0xf3, 0xcf, 0xc7, 0xe3, 0x7, 0xf0, 0x1f, 0xf8, 0xff, 0xf1, 0xff, 0xe3, 0xff, 0xe7, 0xff, 0xff, 0xff, 0xff}, // 81
  // Q
  
  {0x10, 0x18, 12, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7, 0xfc, 0x7, 0xf8, 0xe7, 0xf1, 0xe7, 0xf3, 0xe7, 0xf3, 0xe7, 0xf1, 0x7, 0xf8, 0x7, 0xfc, 0xe7, 0xf8, 0xe7, 0xf1, 0xe7, 0xf3, 0xe7, 0xf3, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xcf, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff}, // 82
  // R
  
  {0x10, 0x18, 10, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf, 0xfc, 0x7, 0xf8, 0xe3, 0xfb, 0xf3, 0xff, 0xf3, 0xff, 0xe3, 0xff, 0x7, 0xff, 0xf, 0xfc, 0xff, 0xf8, 0xff, 0xf3, 0xff, 0xf3, 0xff, 0xf3, 0xfb, 0xf1, 0x3, 0xf8, 0x7, 0xfc, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff}, // 83
  // S
  
  {0x10, 0x18, 12, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x1, 0xe0, 0x1, 0xe0, 0x3f, 0xff, 0x3f, 0xff, 0x3f, 0xff, 0x3f, 0xff, 0x3f, 0xff, 0x3f, 0xff, 0x3f, 0xff, 0x3f, 0xff, 0x3f, 0xff, 0x3f, 0xff, 0x3f, 0xff, 0x3f, 0xff, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff}, // 84
  // T
  
  {0x10, 0x18, 12, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf3, 0xe7, 0xf3, 0xe7, 0xf3, 0xe7, 0xf3, 0xe7, 0xf3, 0xe7, 0xf3, 0xe7, 0xf3, 0xe7, 0xf3, 0xe7, 0xf3, 0xe7, 0xf3, 0xe7, 0xf3, 0xe7, 0xe3, 0xe3, 0xe7, 0xf3, 0x7, 0xf0, 0x1f, 0xfc, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff}, // 85
  // U
  
  {0x10, 0x18, 12, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf9, 0xcf, 0xf3, 0xe7, 0xf3, 0xe7, 0xf3, 0xe7, 0xe7, 0xf3, 0xe7, 0xf3, 0xe7, 0xf3, 0xcf, 0xf9, 0xcf, 0xf9, 0x8f, 0xf8, 0x9f, 0xfc, 0x9f, 0xfc, 0x3f, 0xfe, 0x3f, 0xfe, 0x3f, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff}, // 86
  // V
  
  {0x18, 0x18, 15, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe7, 0xc3, 0xe7, 0xe7, 0xc3, 0xe7, 0xcf, 0xc3, 0xf3, 0xcf, 0xc3, 0xf3, 0xcf, 0x99, 0xf3, 0xcf, 0x99, 0xf3, 0x9f, 0x99, 0xf9, 0x9f, 0x99, 0xf9, 0x9f, 0x3c, 0xf9, 0x9f, 0x3c, 0xf9, 0x1f, 0x3c, 0xfc, 0x3f, 0x3c, 0xfc, 0x3f, 0x3c, 0xfc, 0x3f, 0x7e, 0xfc, 0x3f, 0x7e, 0xfc, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff}, // 87
  // W
  
  {0x10, 0x18, 12, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc7, 0xc7, 0xcf, 0xe7, 0x8f, 0xf3, 0x9f, 0xf1, 0x3f, 0xf9, 0x3f, 0xfc, 0x7f, 0xfc, 0x7f, 0xfc, 0x3f, 0xfc, 0x3f, 0xf8, 0x9f, 0xf9, 0x8f, 0xf3, 0xcf, 0xe3, 0xe7, 0xe7, 0xe3, 0xc7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff}, // 88
  // X
  
  {0x10, 0x18, 12, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf1, 0xe3, 0xf3, 0xf3, 0xe7, 0xf9, 0xc7, 0xf8, 0xcf, 0xfc, 0xf, 0xfc, 0x1f, 0xfe, 0x3f, 0xff, 0x3f, 0xff, 0x3f, 0xff, 0x3f, 0xff, 0x3f, 0xff, 0x3f, 0xff, 0x3f, 0xff, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff}, // 89
  // Y
  
  {0x10, 0x18, 12, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x3, 0xc0, 0x3, 0xc0, 0xff, 0xe7, 0xff, 0xf3, 0xff, 0xf1, 0xff, 0xf8, 0x7f, 0xfc, 0x7f, 0xfe, 0x3f, 0xff, 0x1f, 0xff, 0x8f, 0xff, 0xcf, 0xff, 0xe7, 0xff, 0x3, 0xc0, 0x3, 0xc0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff}, // 90
  // Z

  {0x8, 0x18, 12, 0xff, 0xff, 0xff, 0xff, 0xc3, 0xc3, 0xf3, 0xf3, 0xf3, 0xf3, 0xf3, 0xf3, 0xf3, 0xf3, 0xf3, 0xf3, 0xf3, 0xf3, 0xf3, 0xf3, 0xc3, 0xc3, 0xff, 0xff},//91
  //[ Source image file: "pt-mono-bold-]-8x13.bmp"
  
  {0x8, 0x18, 12, 0xff, 0xff, 0xff, 0xff, 0xfc, 0xf8, 0xf9, 0xf9, 0xf9, 0xf3, 0xf3, 0xf3, 0xe7, 0xe7, 0xe7, 0xcf, 0xcf, 0xcf, 0x8f, 0x9f, 0xff, 0xff, 0xff, 0xff},//92
  //\ Source image file: "pt-mono-bold-5-8x13.bmp"
  
  {0x8, 0x18, 12, 0xff, 0xff, 0xff, 0xff, 0xc3, 0xc3, 0xcf, 0xcf, 0xcf, 0xcf, 0xcf, 0xcf, 0xcf, 0xcf, 0xcf, 0xcf, 0xcf, 0xcf, 0xcf, 0xcf, 0xc3, 0xc3, 0xff, 0xff},//93
  //] Source image file: "pt-mono-bold-_i-8x13.bmp"
  
  {0x18, 0x18, 12, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe3, 0xff, 0xff, 0xc9, 0xff, 0xff, 0x9c, 0xff, 0x7f, 0x3e, 0xff, 0x3f, 0x7f, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff}, //94
  // ^
  
  {0x10, 0x18, 12, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7, 0xe0, 0x7, 0xe0}, // 95
  // _
  
  {0x10, 0x18, 12, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xcf, 0xff, 0x9f, 0xff, 0x3f, 0xff, 0x7f, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff}, // 96
  // `


  {0x10, 0x18, 12, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf, 0xfe, 0x7, 0xfc, 0xf7, 0xf8, 0xff, 0xf9, 0xf, 0xf8, 0x7, 0xf8, 0xf3, 0xf9, 0xf3, 0xf9, 0xf3, 0xf8, 0x3, 0xf8, 0x7, 0xf9, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},//97
  //a Source image file: "pt-mono-bold-b-8x13.bmp"
  
  {0x10, 0x18, 12, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe7, 0xff, 0xe7, 0xff, 0xe7, 0xff, 0xe7, 0xff, 0x27, 0xf8, 0x7, 0xf0, 0xc7, 0xf3, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xc7, 0xf3, 0x7, 0xf0, 0x27, 0xf8, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},//98
  //b Source image file: "pt-mono-bold-c-8x13.bmp"
  
  {0x10, 0x18, 12, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x3f, 0xf8, 0xf, 0xf0, 0x8f, 0xf7, 0xc7, 0xff, 0xe7, 0xff, 0xe7, 0xff, 0xe7, 0xff, 0xc7, 0xff, 0x8f, 0xf7, 0xf, 0xf0, 0x3f, 0xf8, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},//99
  //c Source image file: "pt-mono-bold-d-8x13.bmp"
  
  {0x10, 0x18, 12, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf3, 0xff, 0xf3, 0xff, 0xf3, 0xff, 0xf3, 0xf, 0xf2, 0x7, 0xf0, 0xe7, 0xf1, 0xf3, 0xf3, 0xf3, 0xf3, 0xf3, 0xf3, 0xf3, 0xf3, 0xf3, 0xf3, 0xe7, 0xf1, 0x7, 0xf0, 0xf, 0xf2, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},//100
  //d Source image file: "pt-mono-bold-e-8x13.bmp"
  
  {0x10, 0x18, 12, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x1f, 0xfc, 0x7, 0xf8, 0xe7, 0xf1, 0xf3, 0xf3, 0x3, 0xf0, 0x3, 0xf0, 0xf3, 0xff, 0xf3, 0xff, 0xc7, 0xf7, 0xf, 0xf0, 0x1f, 0xf8, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},//101
  //e Source image file: "pt-mono-bold-f-8x13.bmp"
  
  {0x10, 0x18, 12, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0xf8, 0x3f, 0xf8, 0x3f, 0xff, 0x3f, 0xff, 0xf, 0xf8, 0xf, 0xf8, 0x3f, 0xff, 0x3f, 0xff, 0x3f, 0xff, 0x3f, 0xff, 0x3f, 0xff, 0x3f, 0xff, 0x3f, 0xff, 0x3f, 0xff, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},//102
  //f Source image file: "pt-mono-bold-g-8x13.bmp"
  
  {0x10, 0x18, 12, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf, 0xf2, 0x7, 0xf0, 0xe7, 0xf1, 0xf3, 0xf3, 0xf3, 0xf3, 0xf3, 0xf3, 0xf3, 0xf3, 0xf3, 0xf3, 0xe7, 0xf1, 0x7, 0xf0, 0xf, 0xf2, 0xff, 0xf3, 0xf7, 0xf9, 0x7, 0xf8, 0xf, 0xfe, 0xff, 0xff},//103
  //g Source image file: "pt-mono-bold-h-8x13.bmp"
  
  {0x10, 0x18, 12, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe7, 0xff, 0xe7, 0xff, 0xe7, 0xff, 0xe7, 0xff, 0x27, 0xfc, 0x7, 0xf8, 0xc7, 0xf1, 0xe7, 0xf3, 0xe7, 0xf3, 0xe7, 0xf3, 0xe7, 0xf3, 0xe7, 0xf3, 0xe7, 0xf3, 0xe7, 0xf3, 0xe7, 0xf3, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},//104
  //h Source image file: "pt-mono-bold-i-8x13.bmp"
  
  {0x8, 0x18, 6, 0xff, 0xff, 0xff, 0xff, 0xe7, 0xe7, 0xff, 0xff, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xff, 0xff, 0xff, 0xff, 0xff},//105
  //i Source image file: "pt-mono-bold-j-8x13.bmp"
  
  {0x8, 0x18, 6, 0xff, 0xff, 0xff, 0xff, 0xe7, 0xe7, 0xff, 0xff, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xf1, 0xf1, 0xff},//106
  //j Source image file: "pt-mono-bold-k-8x13.bmp"
  
  {0x10, 0x18, 12, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xcf, 0xff, 0xcf, 0xff, 0xcf, 0xff, 0xcf, 0xff, 0xcf, 0xe3, 0xcf, 0xf1, 0xcf, 0xf8, 0x4f, 0xfc, 0xf, 0xfe, 0xf, 0xff, 0xf, 0xfe, 0x4f, 0xfc, 0xcf, 0xf8, 0xcf, 0xf1, 0xcf, 0xe3, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},//107
  //k Source image file: "pt-mono-bold-l-8x13.bmp"
  
  {0x8, 0x18, 6, 0xff, 0xff, 0xff, 0xff, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xff, 0xff, 0xff, 0xff, 0xff},//108
  //l Source image file: "pt-mono-bold-m-8x13.bmp"
  
  {0x18, 0x18, 20, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x4f, 0x38, 0xfc, 0xf, 0x10, 0xf8, 0x8f, 0xc3, 0xf1, 0xcf, 0xe7, 0xf3, 0xcf, 0xe7, 0xf3, 0xcf, 0xe7, 0xf3, 0xcf, 0xe7, 0xf3, 0xcf, 0xe7, 0xf3, 0xcf, 0xe7, 0xf3, 0xcf, 0xe7, 0xf3, 0xcf, 0xe7, 0xf3, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},//109
  //m Source image file: "pt-mono-bold-n-8x13.bmp"
  
  {0x10, 0x18, 12, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x27, 0xfc, 0x7, 0xf8, 0xc7, 0xf1, 0xe7, 0xf3, 0xe7, 0xf3, 0xe7, 0xf3, 0xe7, 0xf3, 0xe7, 0xf3, 0xe7, 0xf3, 0xe7, 0xf3, 0xe7, 0xf3, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},//110
  //n Source image file: "pt-mono-bold-o-8x13.bmp"
  
  {0x10, 0x18, 12, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x1f, 0xfe, 0x7, 0xf8, 0xe7, 0xf9, 0xf3, 0xf3, 0xf3, 0xf3, 0xf3, 0xf3, 0xf3, 0xf3, 0xf3, 0xf3, 0xe7, 0xf9, 0x7, 0xf8, 0x1f, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},//111
  //o Source image file: "pt-mono-bold-p-8x13.bmp"
  
  {0x10, 0x18, 12, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x27, 0xf8, 0x7, 0xf0, 0xc7, 0xf3, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xc7, 0xf3, 0x7, 0xf0, 0x27, 0xf8, 0xe7, 0xff, 0xe7, 0xff, 0xe7, 0xff, 0xe7, 0xff, 0xff, 0xff},//112
  //p Source image file: "pt-mono-bold-q-8x13.bmp"
  
  {0x10, 0x18, 12, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf, 0xf2, 0x7, 0xf0, 0xe7, 0xf1, 0xf3, 0xf3, 0xf3, 0xf3, 0xf3, 0xf3, 0xf3, 0xf3, 0xf3, 0xf3, 0xe7, 0xf1, 0x7, 0xf0, 0xf, 0xf2, 0xff, 0xf3, 0xff, 0xf3, 0xff, 0xf3, 0xff, 0xf3, 0xff, 0xff},//113
  //q Source image file: "pt-mono-bold-r-8x13.bmp"
  
  {0x10, 0x18, 12, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x9f, 0xf8, 0x1f, 0xf8, 0x1f, 0xff, 0x9f, 0xff, 0x9f, 0xff, 0x9f, 0xff, 0x9f, 0xff, 0x9f, 0xff, 0x9f, 0xff, 0x9f, 0xff, 0x9f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},//114
  //r Source image file: "pt-mono-bold-s-8x13.bmp"
  
  {0x10, 0x18, 12, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x1f, 0xfc, 0x7, 0xf8, 0xe7, 0xfb, 0xe7, 0xff, 0x7, 0xfe, 0x1f, 0xfc, 0xff, 0xf8, 0xff, 0xf9, 0xf7, 0xf9, 0x7, 0xf8, 0xf, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},//115
  //s Source image file: "pt-mono-bold-t-8x13.bmp"
  
  {0x8, 0x18, 10, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf3, 0xf3, 0xf3, 0x1, 0x1, 0xf3, 0xf3, 0xf3, 0xf3, 0xf3, 0xf3, 0xf3, 0x3, 0x7, 0xff, 0xff, 0xff, 0xff, 0xff},//116
  //t Source image file: "pt-mono-bold-u-8x13.bmp"
  
  {0x10, 0x18, 12, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe7, 0xf3, 0xe7, 0xf3, 0xe7, 0xf3, 0xe7, 0xf3, 0xe7, 0xf3, 0xe7, 0xf3, 0xe7, 0xf3, 0xe7, 0xf3, 0xc7, 0xf1, 0xf, 0xf0, 0x1f, 0xf2, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},//117
  //u Source image file: "pt-mono-bold-v-8x13.bmp"
  
  {0x10, 0x18, 12, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf3, 0xe7, 0xe7, 0xf3, 0xe7, 0xf3, 0xe7, 0xf3, 0xcf, 0xf9, 0xcf, 0xf9, 0x9f, 0xfc, 0x9f, 0xfc, 0x9f, 0xfc, 0x3f, 0xfe, 0x3f, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},//118
  //v Source image file: "pt-mono-bold-w-8x13.bmp"
  
  {0x18, 0x18, 12, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xcf, 0xe3, 0xf9, 0xcf, 0xe3, 0xf9, 0x9f, 0xeb, 0xfc, 0x9f, 0xc9, 0xfc, 0x9f, 0xc9, 0xfc, 0x9f, 0xc9, 0xfc, 0x3f, 0x5d, 0xfe, 0x3f, 0x1c, 0xfe, 0x3f, 0x1c, 0xfe, 0x7f, 0x3e, 0xff, 0x7f, 0x3e, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},//119
  //w Source image file: "pt-mono-bold-x-8x13.bmp"
  
  {0x10, 0x18, 12, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe3, 0xe3, 0xc7, 0xf1, 0x8f, 0xf8, 0x9f, 0xfc, 0x3f, 0xfe, 0x3f, 0xfe, 0x1f, 0xfc, 0x9f, 0xfc, 0xcf, 0xf9, 0xc7, 0xf1, 0xe3, 0xe3, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},//120
  //x Source image file: "pt-mono-bold-y-8x13.bmp"
  
  {0x10, 0x18, 12, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf3, 0xe7, 0xe7, 0xf3, 0xe7, 0xf3, 0xc7, 0xf9, 0xcf, 0xf9, 0x8f, 0xf8, 0x9f, 0xfc, 0x9f, 0xfc, 0x3f, 0xfe, 0x3f, 0xfe, 0x3f, 0xff, 0x3f, 0xff, 0x1f, 0xff, 0x87, 0xff, 0xc7, 0xff, 0xff, 0xff},//121
  //y Source image file: "pt-mono-bold-z-8x13.bmp"
  
  {0x10, 0x18, 12, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7, 0xf0, 0x7, 0xf0, 0xff, 0xf9, 0xff, 0xfc, 0x7f, 0xfc, 0x3f, 0xfe, 0x1f, 0xff, 0x9f, 0xff, 0x8f, 0xff, 0x7, 0xf0, 0x7, 0xf0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},//122
  // z
  
  {0x10, 0x18, 12, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x7f, 0xf0, 0x7f, 0xfe, 0x7f, 0xfe, 0x7f, 0xfe, 0x7f, 0xfe, 0x7f, 0xfe, 0x7f, 0xfe, 0xf, 0xff, 0xf, 0xff, 0x3f, 0xfe, 0x7f, 0xfe, 0x7f, 0xfe, 0x7f, 0xfe, 0x7f, 0xfe, 0x7f, 0xfe, 0x7f, 0xf0, 0xff, 0xf0, 0xff, 0xff, 0xff, 0xff},//123
  //{ Source image file: "pt-mono-bold-}-8x13.bmp"

  {0x10, 0x18, 6, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x3f, 0xfe, 0x3f, 0xfe, 0x3f, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x3f, 0xfe, 0x3f, 0xfe, 0x3f, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff}, // 124
  // :
  
  {0x10, 0x18, 12, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x87, 0xff, 0x7, 0xff, 0x3f, 0xff, 0x3f, 0xff, 0x3f, 0xff, 0x3f, 0xff, 0x3f, 0xff, 0x3f, 0xff, 0x7f, 0xf8, 0x7f, 0xf8, 0x3f, 0xfe, 0x3f, 0xff, 0x3f, 0xff, 0x3f, 0xff, 0x3f, 0xff, 0x3f, 0xff, 0x7, 0xff, 0x87, 0xff, 0xff, 0xff, 0xff, 0xff},//125
  //}
  
  {0xFF, 0xFF, 12, 0xFF, 0xFF, 0xF3, 0x81, 0x8F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},//126
  //~ Source image file: "pt-mono-bold-ts-8x13.bmp"
  
  {0,0,0}};

const uint8_t FONT_pt_mono_bold_8x13_2[][FONTS_NUM] PROGMEM = {
  {},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},
  {},{},{},{},

  
  {0xFF, 0xFF, 0xFF, 0xC3, 0x83, 0x9F, 0x83, 0x99, 0x01, 0x03, 0xFF, 0xFF, 0xFF},//160
  //а Source image file: "pt-mono-bold-and-8x13.bmp"
  {0x9F, 0x83, 0xF1, 0xC1, 0x81, 0x38, 0x3D, 0x19, 0x81, 0xC3, 0xFF, 0xFF, 0xFF},//161
  //б Source image file: "pt-mono-bold-bl-8x13.bmp"
  {0xFF, 0xFF, 0xFF, 0xC0, 0xC0, 0xCC, 0xC0, 0x9C, 0x80, 0xC0, 0xFF, 0xFF, 0xFF},//162
  //в Source image file: "pt-mono-bold-vopros-8x13.bmp"
  {0xFF, 0xFF, 0xFF, 0x01, 0x01, 0x33, 0xF3, 0xF3, 0xC1, 0xC1, 0xFF, 0xFF, 0xFF},//163
  //г Source image file: "pt-mono-bold-gz-8x13.bmp"
  {0xFF, 0xFF, 0xFF, 0x83, 0x83, 0x93, 0x9B, 0x99, 0x00, 0x00, 0x3C, 0x3C, 0xFF},//164
  //д Source image file: "pt-mono-bold-e-8x13.bmp"
  {0xFF, 0xFF, 0xFF, 0xC3, 0x81, 0x39, 0x01, 0xF9, 0x81, 0x83, 0xFF, 0xFF, 0xFF},//165
  //е Source image file: "pt-mono-bold-ee-8x13.bmp"
  {0xFF, 0xFF, 0xFF, 0x24, 0xA1, 0x81, 0x81, 0xA1, 0x25, 0x24, 0xFF, 0xFF, 0xFF},//166
  //ж Source image file: "pt-mono-bold-hash-8x13.bmp"
  {0xFF, 0xFF, 0xFF, 0x83, 0x81, 0x99, 0x8F, 0x3F, 0x81, 0x83, 0xFF, 0xFF, 0xFF},//167
  //з Source image file: "pt-mono-bold-zapataia-8x13.bmp"
  {0xFF, 0xFF, 0xFF, 0xB9, 0x99, 0x89, 0xA1, 0xB1, 0xB1, 0xB9, 0xFF, 0xFF, 0xFF},//168
  //и Source image file: "pt-mono-bold-ia-8x13.bmp"
  {0xD3, 0xC7, 0xFF, 0xB9, 0x99, 0x09, 0xA1, 0xB1, 0xB1, 0xB9, 0xFF, 0xFF, 0xFF},//169
  //й Source image file: "F:\Images\xmobile-fonts\pt-mono-bold\8x13\bmp\pt-mono-bold-space-8x13.bmp"
  {0xFF, 0xFF, 0xFF, 0x39, 0x99, 0xC9, 0xC1, 0xC9, 0x19, 0x39, 0xFF, 0xFF, 0xFF},//170
  //к Source image file: "pt-mono-bold-l-8x13.bmp"
  {0xFF, 0xFF, 0xFF, 0x83, 0x83, 0x93, 0x9B, 0x99, 0x98, 0x9C, 0xFF, 0xFF, 0xFF},//171
  //л Source image file: "pt-mono-bold-m-8x13.bmp"
  {0xFF, 0xFF, 0xFF, 0x38, 0x18, 0x00, 0x24, 0x2C, 0x3C, 0x3C, 0xFF, 0xFF, 0xFF},//172
  //м Source image file: "pt-mono-bold-miaz-8x13.bmp"
  {0xFF, 0xFF, 0xFF, 0x39, 0x39, 0x01, 0x01, 0x39, 0x39, 0x39, 0xFF, 0xFF, 0xFF},//173
  //н Source image file: "pt-mono-bold-o-8x13.bmp"
  {0xFF, 0xFF, 0xFF, 0xC3, 0x81, 0x39, 0x3C, 0x39, 0x81, 0xC3, 0xFF, 0xFF, 0xFF},//174
  //о Source image file: "pt-mono-bold-p-8x13.bmp"
  {0xFF, 0xFF, 0xFF, 0x01, 0x01, 0x39, 0x39, 0x39, 0x39, 0x39, 0xFF, 0xFF, 0xFF},//175
  //п Source image file: "pt-mono-bold-persent-8x13.bmp"
  {0xFF, 0xFF, 0xFF, 0x80, 0x80, 0x39, 0x39, 0x19, 0x81, 0xC1, 0xF9, 0xF9, 0xF9},//224
  //р Source image file: "pt-mono-bold-sh-8x13.bmp"
  {0xFF, 0xFF, 0xFF, 0x87, 0x83, 0xB9, 0xF9, 0xF9, 0x83, 0x87, 0xFF, 0xFF, 0xFF},//225
  //с Source image file: "pt-mono-bold-d-8x13.bmp"
  {0xFF, 0xFF, 0xFF, 0x01, 0x01, 0x25, 0xE7, 0xE7, 0x81, 0x81, 0xFF, 0xFF, 0xFF},//226
  //т Source image file: "pt-mono-bold-tilda-8x13.bmp"
  {0xFF, 0xFF, 0xFF, 0x3C, 0x39, 0x99, 0x93, 0x93, 0xC7, 0xC7, 0xCF, 0xE1, 0xF3},//227
  //у Source image file: "pt-mono-bold-z-8x13.bmp"
  {0xE3, 0xE3, 0xE7, 0x81, 0x01, 0x24, 0x24, 0x24, 0x01, 0x81, 0xE7, 0xE7, 0xE7},//228
  //ф Source image file: "pt-mono-bold-g-8x13.bmp"
  {0xFF, 0xFF, 0xFF, 0x39, 0x93, 0xC3, 0xC7, 0xC3, 0x99, 0x39, 0xFF, 0xFF, 0xFF},//229
  //х Source image file: "pt-mono-bold-y-8x13.bmp"
  {0xFE, 0xFE, 0xFE, 0x98, 0x98, 0x98, 0x98, 0x98, 0x00, 0x00, 0x7E, 0x7E, 0xFE},//230
  //ц Source image file: "pt-mono-bold-tvz-8x13.bmp"
  {0xFF, 0xFF, 0xFF, 0xB9, 0xB9, 0x99, 0x81, 0x83, 0xBF, 0xBF, 0xFF, 0xFF, 0xFF},//231
  //ч (буква че) Source image file: "pt-mono-bold-4444-8x13.bmp"
  {0xFF, 0xFF, 0xFF, 0x24, 0x24, 0x24, 0x24, 0x24, 0x00, 0x00, 0xFF, 0xFF, 0xFF},//232
  //ш Source image file: "pt-mono-bold-shb-8x13.bmp"
  {0xFF, 0xFF, 0xFF, 0xA4, 0xA4, 0xA4, 0xA4, 0xA4, 0x00, 0x00, 0x7F, 0x7F, 0xFF},//233
  //щ Source image file: "pt-mono-bold-slash-8x13.bmp"
  {0xFF, 0xFF, 0xFF, 0xF0, 0xF0, 0x83, 0x03, 0x33, 0x83, 0x83, 0xFF, 0xFF, 0xFF},//234
  //ъ Source image file: "pt-mono-bold-v-8x13.bmp"
  {0xFF, 0xFF, 0xFF, 0x3C, 0x3C, 0x20, 0x00, 0x0C, 0x20, 0x20, 0xFF, 0xFF, 0xFF},//235
  //ы Source image file: "pt-mono-bold-c-8x13.bmp"
  {0xFF, 0xFF, 0xFF, 0xF9, 0xF9, 0x81, 0x81, 0x19, 0x81, 0xC1, 0xFF, 0xFF, 0xFF},//236
  //ь Source image file: "pt-mono-bold-minus-8x13.bmp"
  {0xFF, 0xFF, 0xFF, 0xC1, 0x81, 0x1D, 0x07, 0x1F, 0x81, 0xC1, 0xFF, 0xFF, 0xFF},//237
  //э Source image file: "pt-mono-bold-ii-8x13.bmp"
  {0xFF, 0xFF, 0xFF, 0x8D, 0x05, 0x21, 0x21, 0x25, 0x05, 0x8D, 0xFF, 0xFF, 0xFF},//238
  //ю Source image file: "pt-mono-bold-k-8x13.bmp"
  {0xFF, 0xFF, 0xFF, 0x83, 0x81, 0xB9, 0x81, 0x83, 0xB1, 0xB9, 0xFF, 0xFF, 0xFF},//239
  //я Source image file: "pt-mono-bold-ie-8x13.bmp"
  {},

  
  
  {0x9B, 0x9B, 0xFF, 0xC3, 0x81, 0x39, 0x01, 0xF9, 0x81, 0x83, 0xFF, 0xFF, 0xFF}//241
  //ё Source image file: "pt-mono-bold-f-8x13.bmp"
  

  };

const byte FONT_max_width = 12;
const byte FONT_max_height = 24;

const uint8_t* FONT_GetPicture8x13(byte code) {
  
  if (code >= 1 && code <= 127)
    return FONT_nimbus_bold_16_1[code];
  else
    return FONT_nimbus_bold_16_1[1];
  
}

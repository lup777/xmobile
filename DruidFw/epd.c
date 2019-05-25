// epd.c
#include "epd.h"

#include <avr/io.h>

#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

#include "usart.h"
#include "spi.h"
#include "fonts.h"

#define __log(...)
//#define __log _log

const uint8_t* gbackground;
static volatile uint8_t gi;


void EPD_Init(void) {
  //SPIC_Init();
  __log("SPI init completed");
  gbackground = NULL;
  // CS configured to out in SPIC_Init()
  PORTA.DIRSET = PIN1_bm; // DC
  PORTA.DIRSET = PIN4_bm; // Reset
  PORTA.DIRCLR = PIN3_bm; // Busy
  EPD_CSHi();

  EPD_Reset();

  __log("EPD init");
  {
    uint8_t data[3] = {0xC7, 0x00, 0x00};
    EPD_SendFromRam(DRIVER_OUTPUT_CONTROL, data, 3);
  }

  {
    uint8_t data[3] = {0xD7, 0xD6, 0x9D};
    EPD_SendFromRam(BOOSTER_SOFT_START_CONTROL, data, 3);
  }

  EPD_SendFromGen(WRITE_VCOM_REGISTER, 0xA8, 1);
  EPD_SendFromGen(SET_DUMMY_LINE_PERIOD, 0x1A, 1);
  EPD_SendFromGen(SET_GATE_TIME, 0x08, 1);
  EPD_SendFromGen(DATA_ENTRY_MODE_SETTING, 0x01, 1);

  __log("EPD Init completed");

}

void EPD_StartPartial(void) {
  __log("EPD Start PU _1_");
  //EPD_WaitUntilIdle(); // wait
  __log("EPD Start PU _2_");

  EPD_SetLut(lut_partial_update);
  EPD_PowerOn();

  EPD_SetMemoryArea(0, EPD_WIDTH_BYTES - 1, EPD_HEIGHT - 1, 0);
  EPD_LoadFlashImageToDisplayRam(EPD_WIDTH, EPD_HEIGHT, gbackground);

  EPD_SetMemoryArea(0, EPD_WIDTH_BYTES - 1, EPD_HEIGHT - 1, 0);
  EPD_LoadFlashImageToDisplayRam(EPD_WIDTH, EPD_HEIGHT, gbackground);

  __log("EPD Start PU _3_");
}

/*void EPD_ContinuePartial(char* str, uint8_t len, uint8_t x, uint8_t y) {
  __log("c>");
  x = 24 - x;
  for (gi = 0; gi < len; gi++) {
    const uint8_t* picture = FONT_GetPicture8x13( (uint8_t)(str[gi]));
    uint8_t width = 1; // byte
    uint8_t height = 13; // bits

    EPD_SetMemoryArea(x, x + width - 1, y, y + height - 1);
    EPD_LoadFlashImageToDisplayRam(width * 8, height, picture);


    if (x > 0) {
      x -= 1;
    } else {
      break;
    }
  }
  __log("c<");
  //EPD_UpdatePartial();
  }*/

void EPD_ContinuePartial(word x, word y, byte* data,
			 size_t steps, size_t step) {
  // x - column number (byte) to update
  // y - row number (bit) to start update
  // steps - number of row to update
  // step - step for data buffer iterator(byte) (display row width)
  EPD_SetMemoryArea(x, x, y, y + steps);
  EPD_SendFromDisplayBuf(WRITE_RAM, data, steps, step);
}

void EPD_StopPartial(void) {
  EPD_PowerOff();
}

void EPD_ShowString(char* str, uint8_t len, uint8_t x, uint8_t y) {
  //_sleep(200);
  __log("EPD_StopPartial take mutex");

  EPD_SetLut(lut_partial_update);

  EPD_PowerOn();

  EPD_SetMemoryArea(0, EPD_WIDTH_BYTES - 1, EPD_HEIGHT - 1, 0);
  EPD_LoadFlashImageToDisplayRam(EPD_WIDTH, EPD_HEIGHT, gbackground);

  x = 24 - x;
  for (gi = 0; gi < len; gi++) {
    const uint8_t* picture = FONT_GetPicture8x13( (uint8_t)(str[gi]) );
    uint8_t width = 1; // byte
    uint8_t height = 13; // bits

    EPD_SetMemoryArea(x, x + width - 1, y, y + height - 1);
    EPD_LoadFlashImageToDisplayRam(width * 8, height, picture);
    if (x > 0) {
      x -= 1;
    } else {
      break;
    }
  }

  EPD_UpdatePartial();
  EPD_PowerOff();
}

void EPD_UpdatePartial(void) {
  __log("update");
  EPD_SendFromGen(0x22, 0x04, 1);
  EPD_SendFromRam(0x20, NULL, 0);
  EPD_SendFromRam(0xFF, NULL, 0);
}

void EPD_ShowFullScreenImage(const uint8_t *image,
                             uint16_t xsize,
                             uint16_t ysize) {
  __log("EPD show full screen image");
  //Get xbytes from xsize, rounding up
  uint8_t xbytes;
  xbytes = ( xsize + 7 ) >> 3;

  EPD_SetLut(lut_full_update);

  EPD_PowerOn();

  EPD_SetMemoryArea(0,          // X start
		    xbytes - 1, // X end
		    ysize - 1,  // Y start
		    0);         // Y end
  //EPD_SetMemoryPointer(0, 0);

  EPD_LoadFlashImageToDisplayRam(xsize, ysize, image);
  EPD_UpdateFull();

  EPD_PowerOff();
}

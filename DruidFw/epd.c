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
  __log("SPI init completed");
  gbackground = NULL;
  // CS configured to out in SPIC_Init()
  PORTA.DIRSET = PIN1_bm; // DC
  PORTA.DIRSET = PIN4_bm; // Reset
  PORTA.DIRCLR = PIN3_bm; // Busy
  EPD_CSHi();

  EPD_Reset();

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
}

void EPD_StartPartial(void) {
  EPD_SetLut(lut_partial_update);
  EPD_PowerOn();
}

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

void EPD_UpdatePartial(void) {
  EPD_SendFromGen(0x22, 0x04, 1);
  EPD_SendFromRam(0x20, NULL, 0);
  EPD_SendFromRam(0xFF, NULL, 0);
}

void EPD_ShowFullScreenImage(const uint8_t *image,
                             uint16_t xsize,
                             uint16_t ysize) {
  //Get xbytes from xsize, rounding up
  uint8_t xbytes;
  xbytes = ( xsize + 7 ) >> 3;

  EPD_SetLut(lut_full_update);

  EPD_PowerOn();

  EPD_SetMemoryArea(0,          // X start
		    xbytes - 1, // X end
		    ysize - 1,  // Y start
		    0);         // Y end
  EPD_LoadFlashImageToDisplayRam(xsize, ysize, image);
  EPD_UpdateFull();

  EPD_PowerOff();
}

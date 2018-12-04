// epd.c
#include "epd.h"

#include <avr/io.h>

#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

#include "usart.h"
#include "spi.h"
#include "fonts.h"

volatile SemaphoreHandle_t gEpdMutex;
const uint8_t* gbackground;
static volatile uint8_t gi;

void EPD_Init(void) {
  SPIC_Init();
  _log("SPI init completed");
  gbackground = NULL;
  // CS configured to out in SPIC_Init()
  PORTA.DIRSET = PIN1_bm; // DC
  PORTA.DIRSET = PIN4_bm; // Reset
  PORTA.DIRCLR = PIN3_bm; // Busy
  EPD_CSHi();

  EPD_Reset();

  _log("EPD init");
  //EPD_CSLow();
  //EPD_SendCmdByte(DRIVER_OUTPUT_CONTROL);
  //EPD_SendDataByte(/*(EPD_HEIGHT - 1) & 0xFF*/0xC7);
  //EPD_SendDataByte(/*((EPD_HEIGHT - 1) >> 8) & 0xFF*/0x00);
  //EPD_SendDataByte(0x00); // GD = 0, SM = 0, TB = 0
  //EPD_CSHi();
  {
    const char data[] = {0xC7, 0x00, 0x00};
    EPD_SendFromRam(DRIVER_OUTPUT_CONTROL, data);
  }
  
  
  EPD_CSLow();
  EPD_SendCmdByte(BOOSTER_SOFT_START_CONTROL);
  EPD_SendDataByte(0xD7);
  EPD_SendDataByte(0xD6);
  EPD_SendDataByte(0x9D);
  EPD_CSHi();

  EPD_CSLow();
  EPD_SendCmdByte(WRITE_VCOM_REGISTER);
  EPD_SendDataByte(0xA8);
  EPD_CSHi();

  EPD_CSLow();
  EPD_SendCmdByte(SET_DUMMY_LINE_PERIOD);
  EPD_SendDataByte(0x1A);
  EPD_CSHi();

  EPD_CSLow();
  EPD_SendCmdByte(SET_GATE_TIME);
  EPD_SendDataByte(0x08);
  EPD_CSHi();

  EPD_CSLow();
  EPD_SendCmdByte(DATA_ENTRY_MODE_SETTING);
  EPD_SendDataByte(0x01); // 0x03
  EPD_CSHi();

  _log("EPD Init completed");

  EPD_clear();

  gEpdMutex = xSemaphoreCreateMutex();
}

void EPD_StartPartial(void) {
  _log("EPD Start partial update");
  if (xSemaphoreTake(gEpdMutex, (TickType_t)150) != pdTRUE) {
    _log("EPD_StartPartial Failed to take mutex");
    return;
  }
  EPD_WaitUntilIdle(); // wait

  EPD_SetLut(lut_partial_update);
  EPD_PowerOn();

  EPD_SetMemoryArea(0, EPD_WIDTH_BYTES - 1, EPD_HEIGHT - 1, 0);
  EPD_LoadFlashImageToDisplayRam(EPD_WIDTH, EPD_HEIGHT, gbackground);

  EPD_SetMemoryArea(0, EPD_WIDTH_BYTES - 1, EPD_HEIGHT - 1, 0);
  EPD_LoadFlashImageToDisplayRam(EPD_WIDTH, EPD_HEIGHT, gbackground);
}

void EPD_ContinuePartial(char* str, uint8_t len, uint8_t x, uint8_t y) {
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

  //EPD_UpdatePartial();
}

void EPD_StopPartial(void) {
  EPD_PowerOff();
  _log("EPD_StopPartial give mutex");
  xSemaphoreGive(gEpdMutex);
}

void EPD_ShowString(char* str, uint8_t len, uint8_t x, uint8_t y) {
  _log("EPD Show partial image");
  //_sleep(200);
  EPD_WaitUntilIdle(); // wait
  _log("EPD_StopPartial take mutex");
  if (xSemaphoreTake(gEpdMutex, (TickType_t)50) != pdTRUE) {
    _log("EPD_StartPartial Failed to take mutex");
    return;
  }

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
  xSemaphoreGive(gEpdMutex);
}

void EPD_UpdatePartial(void)
{
  EPD_CSLow();
  EPD_SendCmdByte(0x22);
  EPD_SendDataByte(0x04);
  EPD_CSHi();

  EPD_CSLow();
  EPD_SendCmdByte(0x20);
  EPD_CSHi();

  EPD_CSLow();
  EPD_SendCmdByte(0xFF);
  EPD_CSHi();
}

void EPD_ShowFullScreenImage(const uint8_t *image,
                             uint16_t xsize,
                             uint16_t ysize)
{
  _log("EPD show full screen image");
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

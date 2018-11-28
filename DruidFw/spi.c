// spi.c
#include "spi.h"

#include <avr/io.h>
#include <string.h>

#include "FreeRTOS.h"
#include "task.h"

#include "global.h"
#include "usart.h"
#include "display_data.h"
#include "pgm.h"
#include "fonts.h"

typedef uint8_t bool;
#define false  0
#define true   1

//#define _clog(X) USART0_SendStr(X)
#define _clog(X) {}

uint8_t gi;
const uint8_t* gbackground;
volatile SemaphoreHandle_t gEpdMutex;

/*
  E-Paper info

  GPIO
  BUSY - PORTA 3
  RESET - PORTA 4
  DC (data/command) - PORTA 1

  SPI C
  -- PORTC 6 (MISO) --
  CS (chip select) - PORTC 4 (SS)
  CLK (clock) - PORTC 7 (SCK)
  DIN (data input) - PORTC 5 (MOSI)
*/

inline void EPD_Init(void);
void EPD_SetLut(const uint8_t* lut);

void EPD_SetMemoryArea(uint8_t  RAM_XST,uint8_t  RAM_XEND,
		       uint16_t RAM_YST,uint16_t RAM_YEND);

void EPD_ClearFrameMemory(uint8_t color);
void EPD_SetMemoryPointer(int x, int y);
void EPD_WaitUntilIdle(void);
void EPD_DisplayFrame(void);
uint8_t SPIC_TransferByte(uint8_t data_out);
inline void EPD_Reset(void);
inline void SPIC_Init(void);
void EPD_DelayMs(uint16_t time);
void EPD_SendData(uint8_t* arr, size_t len);
inline void EPD_SendDataByte(uint8_t byte);
void EPD_SendCmd(uint8_t* arr, size_t len);
inline void EPD_SendCmdByte(uint8_t byte);
inline void EPD_SelectData(void);
inline void EPD_SelectCommand(void);
inline void EPD_ResetEnable(void);
inline void EPD_ResetDisable(void);
inline bool EPD_Busy(void);
inline void EPD_CSLow(void);
inline void EPD_CSHi(void);
inline void EPD_ShowFullScreenImage(const uint8_t *image, uint16_t xsize,
                                    uint16_t ysize);
void EPD_ShowPartialImages(const uint8_t* background, Image* images, size_t len);
inline void EPD_PowerOn(void);
inline void EPD_PowerOff(void);
inline void EPD_UpdateFull(void);
void EPD_UpdatePartial(void);
inline void EPD_LoadFlashImageToDisplayRam(uint8_t  XSize, uint16_t YSize,
                                           const uint8_t  *image);

inline void EPD_CSLow(void) {
  if ((PORTC.OUT & PIN4_bm) != 0)
    PORTC.OUTCLR = PIN4_bm; // CS low
}

inline void EPD_CSHi(void) {
  if ((PORTC.OUT & PIN4_bm) == 0)
    PORTC.OUTSET = PIN4_bm; // CS hi
}

inline bool EPD_Busy(void) {
  return (0 != (PORTA.IN & PIN3_bm)); // if eq 1
}

inline void EPD_ResetDisable(void) {
  PORTA.OUTSET = PIN4_bm; // Reset
}

inline void EPD_ResetEnable(void) {
  PORTA.OUTCLR = PIN4_bm; // Reset
}

inline void EPD_SelectData(void) {
  if ((PORTA.OUT & PIN1_bm) == 0)
    PORTA.OUTSET = PIN1_bm; // DC hi
}

inline void EPD_SelectCommand(void) {
  if ((PORTA.OUT & PIN1_bm) != 0)
    PORTA.OUTCLR = PIN1_bm; // DC low
}

inline void EPD_SendCmdByte(uint8_t byte) {
  EPD_SelectCommand();
  SPIC_TransferByte(byte);
}

void EPD_SendCmd(uint8_t* arr, size_t len) {
  EPD_SelectCommand();
  for(gi = 0; gi < len; gi++) {
    SPIC_TransferByte(arr[gi]);
  }
}

inline void EPD_SendDataByte(uint8_t byte) {
  EPD_SelectData();
  SPIC_TransferByte(byte);
}

void EPD_SendData(uint8_t* arr, size_t len) {
  EPD_SelectData();
  for(gi = 0; gi < len; gi++) {
    SPIC_TransferByte(arr[gi]);
  }
}

void EPD_DelayMs(uint16_t time) {
  const TickType_t xDelay = time / portTICK_PERIOD_MS;
  vTaskDelay(xDelay);
}

inline void SPIC_Init(void) {
  PORTC.DIRSET = PIN5_bm | PIN7_bm | PIN4_bm; // SPI pins
  EPD_CSHi(); // PIN4_bm
  PORTA.DIRCLR = PIN3_bm;
  SPIC.CTRL = SPI_MASTER_bm | SPI_ENABLE_bm | SPI_PRESCALER_DIV4_gc
    | SPI_MODE_0_gc;
}

inline void EPD_Reset(void) {
  _clog("EPD Reset start");
  EPD_ResetEnable();
  EPD_DelayMs(100);
  EPD_ResetDisable();
  EPD_DelayMs(100);
}

uint8_t SPIC_TransferByte(uint8_t data_out) {
  //EPD_CSDisable(); // LOW

  SPIC.DATA = data_out;
  while (0 == (SPIC.STATUS & SPI_IF_bm));
#if 0
  uint8_t data_in =  SPIC.DATA;

  //EPD_CSEnable(); // HI
  return data_in;
#else
//EPD_CSEnable(); // HI
  return 0;
#endif
}

void EPD_DisplayFrame(void) {
  _clog("EPD display frame");
  //taskENTER_CRITICAL();
  EPD_CSLow();
  EPD_SendCmdByte(DISPLAY_UPDATE_CONTROL_2);
  EPD_SendDataByte(0xC4);
  EPD_CSHi();
  //taskEXIT_CRITICAL();

  //taskENTER_CRITICAL();
  EPD_CSLow();
  EPD_SendCmdByte(MASTER_ACTIVATION);
  EPD_CSHi();
  //taskEXIT_CRITICAL();

  //taskENTER_CRITICAL();
  EPD_CSLow();
  EPD_SendCmdByte(TERMINATE_FRAME_READ_WRITE);
  EPD_CSHi();
  //taskEXIT_CRITICAL();

  EPD_WaitUntilIdle();
}

void EPD_WaitUntilIdle(void) {
  _clog("EPD waite busy");
  while(EPD_Busy() == true) {      //LOW: idle, HIGH: busy
    EPD_DelayMs(100);
  }
}

void EPD_SetMemoryPointer(int x, int y) {
  EPD_WaitUntilIdle();

  _clog("EPD set memory pointer");
  //taskENTER_CRITICAL();
  EPD_CSLow();
  EPD_SendCmdByte(SET_RAM_X_ADDRESS_COUNTER);
    /* x point must be the multiple of 8 or the last 3 bits will be ignored */
  EPD_SendDataByte((x >> 3) & 0xFF);
  EPD_CSHi();
  //taskEXIT_CRITICAL();

  //taskENTER_CRITICAL();
  EPD_CSLow();
  EPD_SendCmdByte(SET_RAM_Y_ADDRESS_COUNTER);
  EPD_SendDataByte(y & 0xFF);
  EPD_SendDataByte((y >> 8) & 0xFF);
  EPD_CSHi();
  //taskEXIT_CRITICAL();
}

void EPD_ClearFrameMemory(uint8_t color) {
  _clog("EPD clear frame memory");
  EPD_SetMemoryArea(0, 0, EPD_WIDTH - 1, EPD_HEIGHT - 1);
  //EPD_SetMemoryPointer(0, 0);

  //taskENTER_CRITICAL();
  EPD_CSLow();
  EPD_SendCmdByte(WRITE_RAM);
  /* send the color data */
  for (int i = 0; i < EPD_WIDTH / 8 * EPD_HEIGHT; i++) {
    EPD_SendDataByte(color);
  }
  EPD_CSHi();
  //taskEXIT_CRITICAL();
}

void EPD_SetMemoryArea(uint8_t  RAM_XST,uint8_t  RAM_XEND,
		       uint16_t RAM_YST,uint16_t RAM_YEND) {
  _clog("EPD set memory area");

  //taskENTER_CRITICAL();
  //Set region X
  EPD_CSLow();
  EPD_SendCmdByte(0x44); // command
  EPD_SendDataByte(RAM_XST);
  EPD_SendDataByte(RAM_XEND);
  EPD_CSHi();
  //taskEXIT_CRITICAL();

  //Set region Y
  //taskENTER_CRITICAL();
  EPD_CSLow();
  EPD_SendCmdByte(0x45); // command
  EPD_SendDataByte((uint8_t)(RAM_YST&0x00FF));
  EPD_SendDataByte((uint8_t)(RAM_YST>>8));
  EPD_SendDataByte((uint8_t)(RAM_YEND&0x00FF));
  EPD_SendDataByte((uint8_t)(RAM_YEND>>8));
  EPD_CSHi();
  //taskEXIT_CRITICAL();

  //Set origin X
  //taskENTER_CRITICAL();
  EPD_CSLow();
  EPD_SendCmdByte(0x4e); //command
  EPD_SendDataByte(RAM_XST);
  EPD_CSHi();
  //taskEXIT_CRITICAL();

  //Set origin Y
  //taskENTER_CRITICAL();
  EPD_CSLow();
  EPD_SendCmdByte(0x4f);
  EPD_SendDataByte((uint8_t)(RAM_YST&0x00FF));
  EPD_SendDataByte((uint8_t)(RAM_YST>>8));
  EPD_CSHi();
  //taskEXIT_CRITICAL();
}

void EPD_SetLut(const uint8_t* lut) {
  _clog("EPD set lut");
  //taskENTER_CRITICAL();
  EPD_CSLow();
  EPD_SendCmdByte(WRITE_LUT_REGISTER);

  for (gi = 0; gi < 30; gi ++) {
    EPD_SendDataByte(pgm_read_byte(&lut[gi]));
  }
  EPD_CSHi();
  //taskEXIT_CRITICAL();
}

inline void EPD_Init(void) {
  SPIC_Init();
  _clog("SPI init completed");
  gbackground = NULL;
  // CS configured to out in SPIC_Init()
  PORTA.DIRSET = PIN1_bm; // DC
  PORTA.DIRSET = PIN4_bm; // Reset
  PORTA.DIRCLR = PIN3_bm; // Busy
  EPD_CSHi();

  EPD_Reset();

  _clog("EPD init");
  //taskENTER_CRITICAL();
  EPD_CSLow();
  EPD_SendCmdByte(DRIVER_OUTPUT_CONTROL);
  EPD_SendDataByte(/*(EPD_HEIGHT - 1) & 0xFF*/0xC7);
  EPD_SendDataByte(/*((EPD_HEIGHT - 1) >> 8) & 0xFF*/0x00);
  EPD_SendDataByte(0x00); // GD = 0, SM = 0, TB = 0
  EPD_CSHi();
  //taskEXIT_CRITICAL();

  //taskENTER_CRITICAL();
  EPD_CSLow();
  EPD_SendCmdByte(BOOSTER_SOFT_START_CONTROL);
  EPD_SendDataByte(0xD7);
  EPD_SendDataByte(0xD6);
  EPD_SendDataByte(0x9D);
  EPD_CSHi();
  //taskEXIT_CRITICAL();

  //taskENTER_CRITICAL();
  EPD_CSLow();
  EPD_SendCmdByte(WRITE_VCOM_REGISTER);
  EPD_SendDataByte(0xA8);
  EPD_CSHi();
  //taskEXIT_CRITICAL();

  //taskENTER_CRITICAL();
  EPD_CSLow();
  EPD_SendCmdByte(SET_DUMMY_LINE_PERIOD);
  EPD_SendDataByte(0x1A);
  EPD_CSHi();
  //taskEXIT_CRITICAL();

  //taskENTER_CRITICAL();
  EPD_CSLow();
  EPD_SendCmdByte(SET_GATE_TIME);
  EPD_SendDataByte(0x08);
  EPD_CSHi();
  //taskEXIT_CRITICAL();

  //taskENTER_CRITICAL();
  EPD_CSLow();
  EPD_SendCmdByte(DATA_ENTRY_MODE_SETTING);
  EPD_SendDataByte(0x01); // 0x03
  EPD_CSHi();
  //taskEXIT_CRITICAL();

  _clog("EPD Init completed");

  EPD_clear();

  gEpdMutex = xSemaphoreCreateMutex();
}

void EPD_clear(void) {
  // clear EPD
  _clog("EPD clear");
  EPD_ClearFrameMemory(0xFF);   // bit set = white, bit reset = black
  EPD_DisplayFrame();
  EPD_ClearFrameMemory(0x00);   // bit set = white, bit reset = black
  EPD_DisplayFrame();
}

inline void EPD_PowerOn(void) {
  _clog("EPD power on");
  //taskENTER_CRITICAL();
  EPD_CSLow();
  EPD_SendCmdByte(0x22);
  EPD_SendDataByte(0xC0);
  EPD_CSHi();
  //taskEXIT_CRITICAL();

  //taskENTER_CRITICAL();
  EPD_CSLow();
  EPD_SendCmdByte(0x20);
  EPD_CSHi();
  //taskEXIT_CRITICAL();
  EPD_WaitUntilIdle();
}

inline void EPD_PowerOff(void) {
  _clog("EPD power off");
  //taskENTER_CRITICAL();
  EPD_CSLow();
  EPD_SendCmdByte(0x22);
  EPD_SendDataByte(0xC0);
  EPD_CSHi();
  //taskEXIT_CRITICAL();

  //taskENTER_CRITICAL();
  EPD_CSLow();
  EPD_SendCmdByte(0x20);
  EPD_CSHi();
  //taskEXIT_CRITICAL();

  EPD_WaitUntilIdle(); // wait
}

inline void EPD_UpdateFull(void) {
  _clog("EPD full update");
    //0x22 = Display Update Control 2
    //Display Update Sequence Option
    //Executes set bits like a mini program, from MSB to LSB
    //    C    7
    // 1100 0111
    // |||| ||||-- CLK/OSC DISABLE  (0x01)
    // |||| |||--- CP DISABLE       (0x02)
    // |||| ||---- DISPLAY_PATTERN  (0x04) <<
    // |||| |----- INITIAL DISPLAY  (0x08)
    // ||||------- LOAD LUT         (0x10)
    // |||-------- LOAD TEMPERATURE (0x20)
    // ||--------- CP ENABLE        (0x40)
    // |---------- CLK/OSC ENABLE   (0x80)
  EPD_WaitUntilIdle(); // wait

  //taskENTER_CRITICAL();
  EPD_CSLow();
  EPD_SendCmdByte(DISPLAY_UPDATE_CONTROL_2);
  EPD_SendDataByte(0xC7);
  EPD_CSHi();
  //taskEXIT_CRITICAL();
    // 0x20 = Master Activation
    // Activate Display Update Sequence
    // The Display Update Sequence Option is
    // located at R22h
  //taskENTER_CRITICAL();
  EPD_CSLow();
  EPD_SendCmdByte(MASTER_ACTIVATION);
  EPD_CSHi();
  //taskEXIT_CRITICAL();
    //0xFF = NOP
    //This command is an empty command; it
    //does not have any effect on the display module.
    //However it can be used to terminate Frame Memory
    //Write or Read Commands.
  //taskENTER_CRITICAL();
  EPD_CSLow();
  EPD_SendCmdByte(TERMINATE_FRAME_READ_WRITE);
  EPD_CSHi();
  //taskEXIT_CRITICAL();

  EPD_WaitUntilIdle(); // wait
}

void EPD_ShowFullScreenImage(const uint8_t *image,
				    uint16_t xsize,
				    uint16_t ysize)
{
  _clog("EPD show full screen image");
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

inline void EPD_LoadFlashImageToDisplayRam(uint8_t  XSize,
                                           uint16_t YSize,
                                           const uint8_t  *image) {
  _clog("EPD load image to RAM");
  uint8_t x;
  uint16_t y;
  uint16_t index = 0;

  //Convert Xsize from pixels to bytes, rounding up
  XSize = ( XSize + 7 ) >> 3;
  //taskENTER_CRITICAL();
  EPD_CSLow();
  EPD_SendCmdByte(WRITE_RAM);
  for( y = 0; y < YSize; y++ ) {
    for( x = 0; x < XSize; x++ ) {
      if (image == NULL)
        EPD_SendDataByte( 0xFF );
      else
        EPD_SendDataByte( pgm_read_byte( &image[index++] ) );
    }
  }
  EPD_CSHi();
  //taskEXIT_CRITICAL();
}

void EPD_StartPartial(void) {
  _clog("EPD Start partial update");
  if (xSemaphoreTake(gEpdMutex, (TickType_t)50) != pdTRUE) {
    _clog("EPD_StartPartial Failed to take mutex");
  }
  EPD_WaitUntilIdle(); // wait

  taskENTER_CRITICAL();
  EPD_SetLut(lut_partial_update);
  EPD_PowerOn();

  EPD_SetMemoryArea(0, EPD_WIDTH_BYTES - 1, EPD_HEIGHT - 1, 0);
  EPD_LoadFlashImageToDisplayRam(EPD_WIDTH, EPD_HEIGHT, gbackground);

  EPD_SetMemoryArea(0, EPD_WIDTH_BYTES - 1, EPD_HEIGHT - 1, 0);
  EPD_LoadFlashImageToDisplayRam(EPD_WIDTH, EPD_HEIGHT, gbackground);
  taskEXIT_CRITICAL();
}

void EPD_ContinuePartial(char* str, uint8_t len, uint8_t x, uint8_t y) {
  x = 24 - x;
  for (gi = 0; gi < len; gi++) {
    const uint8_t* picture = FONT_GetPicture8x13( (uint8_t)(str[gi]));
    uint8_t width = 1; // byte
    uint8_t height = 13; // bits

    taskENTER_CRITICAL();
    EPD_SetMemoryArea(x, x + width - 1, y, y + height - 1);
    EPD_LoadFlashImageToDisplayRam(width * 8, height, picture);
    taskEXIT_CRITICAL();

    if (x > 0) {
      x -= 1;
    } else {
      break;
    }
  }

  //EPD_UpdatePartial();
}

void EPD_StopPartial(void) {
  taskENTER_CRITICAL();
  EPD_PowerOff();
  taskEXIT_CRITICAL();
  xSemaphoreGive(gEpdMutex);
  _clog("EPD_StopPartial give mutex");
}

void EPD_ShowString(char* str, uint8_t len, uint8_t x, uint8_t y) {
  _clog("EPD Show partial image");
  //_sleep(200);
  EPD_WaitUntilIdle(); // wait
  if (xSemaphoreTake(gEpdMutex, (TickType_t)50) != pdTRUE) {
    _clog("EPD_StartPartial Failed to take mutex");
  }
  taskENTER_CRITICAL();

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
  taskEXIT_CRITICAL();
  xSemaphoreGive(gEpdMutex);
}

void EPD_UpdatePartial(void)
{
  //0x22 = Display Update Control 2
  //Display Update Sequence Option
  //Executes set bits like a mini program, from MSB to LSB
  //    0    4
  // 0000 0100
  // |||| ||||-- CLK/OSC DISABLE  (0x01)
  // |||| |||--- CP DISABLE       (0x02)
  // |||| ||---- DISPLAY_PATTERN  (0x04)  <<
  // |||| |----- INITIAL DISPLAY  (0x08)
  // ||||------- LOAD LUT         (0x10)
  // |||-------- LOAD TEMPERATURE (0x20)
  // ||--------- CP ENABLE        (0x40)
  // |---------- CLK/OSC ENABLE   (0x80)
  taskENTER_CRITICAL();
  EPD_CSLow();
  EPD_SendCmdByte(0x22);
  EPD_SendDataByte(0x04);
  EPD_CSHi();
  //taskEXIT_CRITICAL();

  // 0x20 = Master Activation
  // Activate Display Update Sequence
  // The Display Update Sequence Option is
  // located at R22h
  //taskENTER_CRITICAL();
  EPD_CSLow();
  EPD_SendCmdByte(0x20);
  EPD_CSHi();
  //taskEXIT_CRITICAL();

  //0xFF = NOP
  //This command is an empty command; it
  //does not have any effect on the display module.
  //However it can be used to terminate Frame Memory
  //Write or Read Commands.
  //taskENTER_CRITICAL();
  EPD_CSLow();
  EPD_SendCmdByte(0xFF);
  EPD_CSHi();
  taskEXIT_CRITICAL();
}

// spi.h
#pragma once

#include "global.h"
#include "display_data.h"
#include "pgm.h"

typedef struct struct_spi_order {
  uint8_t* buffer;             // pointer to data
  size_t length;               // buffer length
  bool is_pgm;                 // is buffer is in pgm
  size_t repeat;               // how many times send buffer
  size_t step;                 // step to increase data pointer
} SpiOrder;

typedef struct struct_ImagePack {
  const uint8_t* data;
  uint8_t width;  // bytes
  uint8_t height; // bits
  uint8_t x; // bytes
  uint8_t y; // bits
} Image;

//extern uint8_t g_spi_tx_buffer[SPI_TX_BUFFER_SIZE];
//extern MessageBufferHandle_t g_epd_tx_buffer_handle;

// Display resolution
#define EPD_WIDTH       200
#define EPD_HEIGHT      200
#define EPD_WIDTH_BYTES 25

// EPD1IN54 commands
#define DRIVER_OUTPUT_CONTROL                       0x01
#define BOOSTER_SOFT_START_CONTROL                  0x0C
#define GATE_SCAN_START_POSITION                    0x0F
#define DEEP_SLEEP_MODE                             0x10
#define DATA_ENTRY_MODE_SETTING                     0x11
#define SW_RESET                                    0x12
#define TEMPERATURE_SENSOR_CONTROL                  0x1A
#define MASTER_ACTIVATION                           0x20
#define DISPLAY_UPDATE_CONTROL_1                    0x21
#define DISPLAY_UPDATE_CONTROL_2                    0x22
#define WRITE_RAM                                   0x24
#define WRITE_VCOM_REGISTER                         0x2C
#define WRITE_LUT_REGISTER                          0x32
#define SET_DUMMY_LINE_PERIOD                       0x3A
#define SET_GATE_TIME                               0x3B
#define BORDER_WAVEFORM_CONTROL                     0x3C
#define SET_RAM_X_ADDRESS_START_END_POSITION        0x44
#define SET_RAM_Y_ADDRESS_START_END_POSITION        0x45
#define SET_RAM_X_ADDRESS_COUNTER                   0x4E
#define SET_RAM_Y_ADDRESS_COUNTER                   0x4F
#define TERMINATE_FRAME_READ_WRITE                  0xFF

bool EPD_IsCsLow(void);
void EPD_SendFromRam(uint8_t cmd, uint8_t* data, size_t data_len);
void EPD_SendFromRam_(uint8_t cmd, uint8_t* data,
		     size_t data_len, size_t step);
void EPD_SendFromFlash(uint8_t cmd, const uint8_t* data, size_t data_len);
void EPD_SendFromGen(uint8_t cmd, uint8_t example, size_t repeat);
void EPD_SendFromDisplayBuf(uint8_t cmd, uint8_t* data,
			    size_t steps, size_t step);

void EPD_Init(void);
uint8_t SPIC_TransferByte(uint8_t data);
void EPD_clear(void);
void EPD_ShowFullScreenImage(const uint8_t *image,
                             uint16_t xsize,
                             uint16_t ysize);
void EPD_WaitUntilIdle(void);
void EPD_SetLut(const uint8_t* lut);
void EPD_LoadFlashImageToDisplayRam(uint8_t  XSize, uint16_t YSize,
                                           const uint8_t  *image);
void EPD_LoadRamImageToDisplayRam(uint8_t  XSize,
					 uint16_t YSize,
					 uint8_t  *image);
void EPD_PowerOn(void);
void EPD_PowerOff(void);
void EPD_UpdateFull(void);
void EPD_SetMemoryArea(uint8_t  RAM_XST,uint8_t  RAM_XEND,
		       uint16_t RAM_YST,uint16_t RAM_YEND);

void EPD_ClearFrameMemory(uint8_t color);
void EPD_SetMemoryPointer(int x, int y);
void EPD_DisplayFrame(void);
uint8_t SPIC_TransferByte(uint8_t data_out);
void EPD_Reset(void);
void SPIC_Init(byte* g_spi_tx_buffer);
void EPD_DelayMs(uint16_t time);
void EPD_SelectData(void);
void EPD_SelectCommand(void);
void EPD_ResetEnable(void);
void EPD_ResetDisable(void);
bool EPD_Busy(void);
void EPD_CSLow(void);
void EPD_CSHi(void);
void EPD_ShowPartialImages(const uint8_t* background, Image* images, size_t len);

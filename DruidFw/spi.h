// spi.h
//#pragma once
#ifndef __SPI_H__
#define __SPI_H__

#include <avr/io.h>
#include <avr/pgmspace.h>

typedef struct struct_ImagePack {
  const uint8_t* data;
  uint8_t width;  // bytes
  uint8_t height; // bits
  uint8_t x; // bytes
  uint8_t y; // bits
} Image;

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

void EPD_Init(void);
uint8_t SPIC_TransferByte(uint8_t data);
void EPD_clear(void);
extern void EPD_ShowFullScreenImage(const uint8_t *image,
				    uint16_t xsize,
				    uint16_t ysize);
void EPS_ShowPartialImages(const uint8_t* background, Image* images,
			   size_t len);


#endif //__SPI_H__

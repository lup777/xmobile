// spi.c
#include "spi.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <string.h>

#include "FreeRTOS.h"
#include "task.h"

#include "usart.h"

//#define _clog(X) USART0_SendStr(X)
#define _clog(X) {}

static volatile uint8_t gi;

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

inline void SPIC_Init(void) {
  PORTC.DIRSET = PIN5_bm | PIN7_bm | PIN4_bm; // SPI pins
  EPD_CSHi(); // PIN4_bm
  PORTA.DIRCLR = PIN3_bm;
  SPIC.INTCTRL = SPI_INTLVL_LO_gc;

  g_epd_tx_buffer_handle = xMessageBufferCreate(sizeof(SpiOrder) * 15);

  SPIC.CTRL = SPI_MASTER_bm | SPI_ENABLE_bm | SPI_PRESCALER_DIV4_gc
    | SPI_MODE_0_gc;
}

MessageBufferHandle_t g_epd_tx_buffer_handle;
uint8_t g_spi_tx_buffer[SPI_TX_BUFFER_SIZE];

ISR(SPIC_INT_vect) {
  static SpiOrder order = {0};
  static size_t sent_cnt = 0; // they should be equal on start,
                                  // even if order is not inited
  static size_t repeat_cnt = 0;
  BaseType_t hptw = pdFALSE;
  size_t received_bytes;

  if (sent_cnt >= order.length) {
    repeat_cnt ++;

    if (repeat_cnt < order.repeat) {
      sent_cnt = 0; // repeat transfering buffer
      // continue transferring
    } else {
      received_bytes = xMessageBufferReceiveFromISR(g_epd_tx_buffer_handle,
                                                    &order,
                                                    sizeof(order),
                                                    &hptw);
      if (received_bytes != sizeof(order)) { // last order was sent, no more to TX
        // Stop transfering
        // sent_cnt EQ order.length, so ...
      } else { // received new order, starting to tx it
        sent_cnt = 0; // last order was sent full, ready to start TX the next one
        repeat_cnt = 0;
      }
    }
  }

  // continue transferring
  if (sent_cnt < order.length) {
    EPD_SelectData();
    if (order.is_pgm)
      SPIC.DATA = pgm_read_byte(order.buffer + sent_cnt);
    else
      SPIC.DATA = order.buffer[sent_cnt];
    sent_cnt ++;
  } else { // all data from current order was sent
           // Also it can be if we need to send only one byte.
           // In this case we need only to drive CS hi.
    EPD_CSHi(); // Stop transfering
  }

  if ( hptw != pdFALSE )
    taskYIELD();
}

void EPD_SendFromFlash(uint8_t cmd, const uint8_t* data, size_t data_len) {
  size_t bytes_sent;
  //size_t data_len = sizeof(data);
  SpiOrder order;
  order.is_pgm = true;
  order.buffer = (uint8_t*)data;
  order.length = data_len;
  order.repeat = 1;

  while( EPD_IsCsLow() ) {}

  if (data_len > 0) {
    bytes_sent = xMessageBufferSend(g_epd_tx_buffer_handle,
                                    &order,
                                    sizeof(order),
                                    pdMS_TO_TICKS(2000));
    if (bytes_sent != sizeof(order)) {
      _log("[ERR] SPI_Send::xMessageBufferSend failed");
      return;
    }

    EPD_CSLow();
    EPD_SelectCommand();
    SPIC.DATA = cmd;
  }
}

void EPD_SendFromGen(uint8_t cmd, uint8_t example, size_t repeat) {// generator
  size_t bytes_sent;
  SpiOrder order;
  order.is_pgm = false;
  order.buffer = g_spi_tx_buffer;  // first byte will be send from in this func
  order.length = 1;
  order.repeat = repeat;

  while( EPD_IsCsLow() ) {}
  _log("SPI send cmd");

  g_spi_tx_buffer[0] = example;

  if (repeat > 0) {
    bytes_sent = xMessageBufferSend(g_epd_tx_buffer_handle,
                                    &order,
                                    sizeof(order),
                                    pdMS_TO_TICKS(2000));
    if (bytes_sent != sizeof(order)) {
      _log("[ERR] SPI_Send::xMessageBufferSend failed");
      return;
    }

    EPD_CSLow();
    EPD_SelectCommand();
    SPIC.DATA = cmd;
  }

}

void EPD_SendFromRam(uint8_t cmd, uint8_t* data, size_t data_len) {
  size_t bytes_sent;
  SpiOrder order;
  order.is_pgm = false;
  order.buffer = g_spi_tx_buffer;  // first byte will be send from in this func
  order.length = data_len;
  order.repeat = 1;

  if (data_len > SPI_TX_BUFFER_SIZE) {
    _log("ERR: TOO MUTCH DATA, NOT SUPPORTED");
    return;
  }

  while( EPD_IsCsLow() ) {}
  _log("SPI send cmd");

  for(size_t i = 0; i < data_len; i++)
    g_spi_tx_buffer[i] = data[i];

  if (data_len > 0) {
    bytes_sent = xMessageBufferSend(g_epd_tx_buffer_handle,
                                    &order,
                                    sizeof(order),
                                    pdMS_TO_TICKS(2000));
    if (bytes_sent != sizeof(order)) {
      _log("[ERR] SPI_Send::xMessageBufferSend failed");
      return;
    }

    EPD_CSLow();
    EPD_SelectCommand();
    SPIC.DATA = cmd;
  }
}

bool EPD_IsCsLow(void) {
  return (PORTC.OUT & PIN4_bm) == 0;
}

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

void EPD_DelayMs(uint16_t time) {
  const TickType_t xDelay = time / portTICK_PERIOD_MS;
  vTaskDelay(xDelay);
}

inline void EPD_Reset(void) {
  _clog("EPD Reset start");
  EPD_ResetEnable();
  EPD_DelayMs(100);
  EPD_ResetDisable();
  EPD_DelayMs(100);
}

void EPD_DisplayFrame(void) {
  _clog("EPD display frame");

  EPD_SendFromGen(DISPLAY_UPDATE_CONTROL_2, 0xC4, 1);
  EPD_SendFromRam(MASTER_ACTIVATION, NULL, 0);
  EPD_SendFromRam(TERMINATE_FRAME_READ_WRITE, NULL, 0);

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

  EPD_SendFromGen(SET_RAM_X_ADDRESS_COUNTER, (x >> 3) & 0xFF, 1);

  {
    uint8_t data[2] = {y & 0xFF, (y >> 8) & 0xFF};
    EPD_SendFromRam(SET_RAM_Y_ADDRESS_COUNTER, data, 2);
  }
}

void EPD_ClearFrameMemory(uint8_t color) {
  _clog("EPD clear frame memory");
  EPD_SetMemoryArea(0, 0, EPD_WIDTH - 1, EPD_HEIGHT - 1);

  EPD_SendFromGen(WRITE_RAM, color, EPD_WIDTH / 8 * EPD_HEIGHT);
}

void EPD_SetMemoryArea(uint8_t  RAM_XST,uint8_t  RAM_XEND,
		       uint16_t RAM_YST,uint16_t RAM_YEND) {
  _clog("EPD set memory area");

  {
    uint8_t data[2] = {RAM_XST, RAM_XEND};
    EPD_SendFromRam(0x44, data, 2);
  }

  {
    uint8_t data[4] = {RAM_YST & 0x00FF,
                       RAM_YST >> 8,
                       RAM_YEND & 0x00FF,
                       RAM_YEND >> 8};
    EPD_SendFromRam(0x45, data, 4);
  }

  EPD_SendFromGen(0x4e, RAM_XST, 1);

  {
    uint8_t data[2] = {RAM_YST & 0x00FF,
                       RAM_YST >> 8};
    EPD_SendFromRam(0x4f, data, 2);
  }
}

void EPD_SetLut(const uint8_t* lut) {
  _clog("EPD set lut");

  EPD_SendFromFlash(WRITE_LUT_REGISTER, lut, 30);
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
  EPD_SendFromGen(0x22, 0xC0, 1);

  EPD_SendFromRam(0x20, NULL, 0);

  EPD_WaitUntilIdle();
}

inline void EPD_PowerOff(void) {
  _clog("EPD power off");

  EPD_SendFromGen(0x22, 0xC0, 1);

  EPD_SendFromRam(0x20, NULL, 0);

  EPD_WaitUntilIdle(); // wait
}

inline void EPD_UpdateFull(void) {
  _clog("EPD full update");

  EPD_WaitUntilIdle(); // wait

  EPD_SendFromGen(DISPLAY_UPDATE_CONTROL_2, 0xC7, 1);
  EPD_SendFromRam(MASTER_ACTIVATION, NULL, 0);
  EPD_SendFromRam(TERMINATE_FRAME_READ_WRITE, NULL, 0);

  EPD_WaitUntilIdle(); // wait
}

inline void EPD_LoadFlashImageToDisplayRam(uint8_t  XSize,
                                           uint16_t YSize,
                                           const uint8_t  *image) {
  _clog("EPD load image to RAM");

  //Convert Xsize from pixels to bytes, rounding up
  XSize = ( XSize + 7 ) >> 3;

  if (image == NULL)
    EPD_SendFromGen(WRITE_RAM, 0xFF, XSize * YSize);
  else
    EPD_SendFromFlash(WRITE_RAM, image, XSize * YSize);
}

const char display_update_control[] PROGMEM = {
  DISPLAY_UPDATE_CONTROL_2, 0xC4};
const char master_activation[] PROGMEM = {
  MASTER_ACTIVATION};
const char terminate_frame_read_write[] PROGMEM = {
  TERMINATE_FRAME_READ_WRITE};

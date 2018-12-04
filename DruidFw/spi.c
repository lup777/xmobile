// spi.c
#include "spi.h"

#include <avr/io.h>
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

  g_epd_tx_buffer_handle = xStreamBufferCreate(150, 1);

  SPIC.CTRL = SPI_MASTER_bm | SPI_ENABLE_bm | SPI_PRESCALER_DIV4_gc
    | SPI_MODE_0_gc;
}

ISR(SPIC_INT_vect) {
  static SpiOrder order;
  static sent_cnt = order.length; // they should be equal on start,
                                  // even if order is not inited
  BaseType_t hptw = pdFALSE;
  size_t rec_bytes;

  if (sent_cnt == order.length) {
    rec_bytes = xMessageBufferReceiveFromISR(g_epd_tx_buffer_handle,
                                             &order,
                                             sizeof(order),
                                             &hptw);
    if (rec_bytes != sizeof(order)) { // last order was sent, no more to TX
      // Stop transfering
      // sent_cnt EQ order.length, so ...
    } else {
      sent_cnt = 0; // last order was sent full, ready to start TX the next one
    }
  }

  if (sent_cnt < order.length ) {
    EPD_SelectData();
    SPIC.DATA = pgm_read_byte(data + sent_cnt);
    sent_cnt ++;
  } else { // all data from current order was sent
           // Also it can be if we need to send only one byte.
           // In this case we need only to drive CS hi.
    EPD_CSHi(); // Stop transfering
  }

  if ( hptw != pdFALSE )
    taskYIELD();
}

void EPD_SendFlash(const char* data) {
  size_t bytes_sent;
  size_t data_len = sizeof(data);
  SpiOrder order;
  order.buffer = data + 1; // first byte will be send from in this func
  order.length = data_len - 1;

  while( EPD_IsCsLow() ) {}

  if (data_len - 1 > 0) {
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
    SPIC.DATA = data[0];
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

const char display_update_control[] PROGMEM = {
  DISPLAY_UPDATE_CONTROL_2, 0xC4};
const char master_activation[] PROGMEM = {
  MASTER_ACTIVATION};
const char terminate_frame_read_write[] PROGMEM = {
  TERMINATE_FRAME_READ_WRITE};

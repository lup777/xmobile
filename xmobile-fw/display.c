//display.c
#include "display.h"

// PARTIAL UPDATE
// vDisplayPowerOn()
// vDisplaySetArea()
// vDisplayLoadImage()
// vDisplayUpdatepartial
// vDisplayPowerOff



//FULL SCREEN UPDATE

inline void vDiasplayLoadLUTForFullUpdate(void)
{
  SpiSendStream(pcDisplayLUTFullUpdate, 31);
}

#define DISPLAY_PIN_CS //SPI chip select
#define DISPLAY_PIN_RST //reset (arduino 37) PORTC0
#define DISPLAY_PIN_BUSY //busy
#define DISPLAY_PIN_DC // data/command write 
#define DISPLAY_PIN_DIN // SPI MOSI
#define DISPLAY_PIN_CLK // SPI SCK

inline void vDisplay_DC_DATA(void)
{
  DDRG |= (1 << 2);
  PORTG |= (1 << 2);
  //arduino pin 39
}
inline void vDisplay_DC_CMD(void)
{
  DDRG |= (1 << 2);
  PORTG &= ~(1 << 2);
  //arduino pin 39
}

inline void vDosiplay_reset_up(void)
{
  DDRC |= (1 << 0);
  PORTC |= (1 << 0);
}

inline void vDosiplay_reset_dow(void)
{
  DDRC |= (1 << 0);
  PORTC &= (1 << 0);
}

inline void vDisplayWriteCmdString(uint8_t *data, size_t data_len)
{
  //CS pin -> low

  //firt byte in string is command
  vDisplay_DC_CMD();
  SpiSendStream(*data++);
  data_len--;

  // other bytes are data
  vDisplay_DC_DATA();
  
  for(size_t i = 0; i < len ; i++)
    {
      SpiSendStream(*data++);
    }
  //CS pin -> up
}

// vDisplayPowerOn
// vDisplaySetArea
// vDisplayLoadImage
// vDisplayUpdateFull
// vDisplayPowerOff


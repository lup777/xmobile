//display.c
#include "global.h"
#include "display.h"
#include "spi.h"
#include "display_data.h"

void vDisplayPowerOff(void);
void vDisplayPowerOn(void);
void vDisplaySetArea(uint8_t  RAM_XST,uint8_t  RAM_XEND,
                     uint16_t RAM_YST,uint16_t RAM_YEND);
void vDisplayLoadFlashImageToDisplayRam(uint8_t  XSize,
                                        uint16_t YSize,
                                        const uint8_t  *image);
void vDisplayUpdateFull(void);
void vDisplayInit(void);
void vDisplayShowFullScreenImage(const uint8_t *image,
                                 uint16_t xsize,
                                 uint16_t ysize);
void vDisplayUpdatePartial(void);
void vDisplayWriteCmdPair(uint8_t cmd, uint8_t data);
void vDisplayWriteCmdString(const uint8_t *data, size_t data_len);
void vDisplaySendCmd(uint8_t command);
void vDisplaySendData(uint8_t data);
bool bDisplayIsBysy(void);
void vDisplay_reset_down(void);
void vDisplay_reset_up(void);
void vDisplay_DC_CMD(void);
void vDisplay_DC_DATA(void);
void vDiasplayLoadLUTForFullUpdate(void);


void vDisplayTask( void* pvParameters )
{
    (void)(pvParameters);

    vDisplayInit();
        
    for(;;)
        {

        }
}

inline void vDiasplayLoadLUTForFullUpdate(void)
{
    vSpiSendStream(pcDisplayLUTFullUpdate, 31);
}

#define DISPLAY_PIN_CS //SPI chip select
#define DISPLAY_PIN_RST //reset (arduino 37) PORTC0
#define DISPLAY_PIN_BUSY //busy
#define DISPLAY_PIN_DC // data/command write 
#define DISPLAY_PIN_DIN // SPI MOSI
#define DISPLAY_PIN_CLK // SPI SCK
#define DISPLAY_PIN_BS // SPI mode select

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

inline void vDisplay_reset_up(void)
{
  DDRC |= (1 << 0);
  PORTC |= (1 << 0);
}

inline void vDisplay_reset_down(void)
{
  DDRC |= (1 << 0);
  PORTC &= (1 << 0);
}

inline bool bDisplayIsBysy(void)
{ // PORTC 1. NEED TO CHECK !!!
#pragma message "!!! CHECK AND CONFIGURE BISY PIN OF DISPLAY !!!!!!!"
    DDRC &= ~(1 < 1);
    return ((PORTC >> 1) & (~1));
}

inline void vDisplaySendCmd(uint8_t command)
  {
      //ePaper_CS_0;
      vDisplay_DC_CMD();
      vSpiSendStreamByte(command);
  }

inline void vDisplaySendData(uint8_t data)
  {
      //ePaper_CS_0;
      vDisplay_DC_DATA();
      vSpiSendStreamByte(data);
  }

inline void vDisplayWriteCmdString(const uint8_t *data, size_t data_len)
{
  //CS pin -> low

  //firt byte in string is command
  vDisplay_DC_CMD();
  vSpiSendStreamByte(*data++);
  data_len--;

  // other bytes are data
  vDisplay_DC_DATA();

  vSpiSendStream(data, data_len);
  //CS pin -> up
}

inline void vDisplayWriteCmdPair(uint8_t cmd, uint8_t data)
{
  //CS pin -> low

  //firt byte in string is command
  vDisplay_DC_CMD();
  vSpiSendStreamByte(cmd);

  // other bytes are data
  vDisplay_DC_DATA();
  
  vSpiSendStreamByte(data);

  //CS pin -> up
}

// vDisplayPowerOn
// vDisplaySetArea
// vDisplayLoadFlashImageToDisplayRam
// vDisplayUpdateFull
// vDisplayPowerOff

inline void vDisplayUpdatePartial(void)
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
    vDisplayWriteCmdPair(0x22, 0x04);
    // 0x20 = Master Activation
    // Activate Display Update Sequence
    // The Display Update Sequence Option is
    // located at R22h    
    vDisplaySendCmd(0x20);
    //0xFF = NOP
    //This command is an empty command; it
    //does not have any effect on the display module.
    //However it can be used to terminate Frame Memory
    //Write or Read Commands.   
    vDisplaySendCmd(0xff);
}

const uint8_t GDOControl[]       PROGMEM = {0x01,0xC7,0x00,0x00}; //for 1.54inch
const uint8_t softstart[]        PROGMEM = {0x0c,0xd7,0xd6,0x9d};
const uint8_t VCOMVol[]          PROGMEM = {0x2c,0xa8}; // VCOM 7c
const uint8_t DummyLine[]        PROGMEM = {0x3a,0x1a}; // 4 dummy line per gate
const uint8_t Gatetime[]         PROGMEM = {0x3b,0x08}; // 2us per line
const uint8_t RamDataEntryMode[] PROGMEM = {0x11,0x01}; // Ram data entry mode

#ifndef F_CPU
#define F_CPU   16000000UL
#endif
#include <util/delay.h>

inline void vDisplayShowFullScreenImage(const uint8_t *image,
                                        uint16_t xsize,
                                        uint16_t ysize)
{
    //Get xbytes from xsize, rounding up
    uint8_t xbytes;
    xbytes = ( xsize + 7 ) >> 3;

    vDiasplayLoadLUTForFullUpdate();
    vDisplayPowerOn();

    vDisplaySetArea(0,          // X start
                    xbytes - 1, // X end
                    ysize - 1,  // Y start
                    0);         // Y end

    vDisplayLoadFlashImageToDisplayRam(xsize, ysize, image);
    vDisplayUpdateFull();  

    vDisplayPowerOff();
}

inline void vDisplayInit(void)
{
#pragma message "!!! CHECK AND CONFIGURE BS (BUS SELELECT) PIN OF DISPLAY !!!!!!!"
    //ePaper_BS_0;    // 4 wire spi mode selected
    DDRF |= (1 << 2);
    PORTF &= ~(1 << 2);
#pragma message "!!! CHECK AND CONFIGURE BS (BUS SELELECT) PIN OF DISPLAY !!!!!!!"
    
    //Reset the controller
    vDisplay_reset_down();
    _delay_ms(100);
    vDisplay_reset_up();
    _delay_ms(100);
    
    // Panel configuration, Gate selection
    vDisplayWriteCmdString(GDOControl, sizeof(GDOControl));
    // X decrease, Y decrease
    vDisplayWriteCmdString(softstart, sizeof(softstart));
    // VCOM setting
    vDisplayWriteCmdString(VCOMVol, sizeof(VCOMVol));
    //dummy line per gate
    vDisplayWriteCmdString(DummyLine, sizeof(DummyLine));
    // Gate time setting
    vDisplayWriteCmdString(Gatetime, sizeof(Gatetime));
    // X decrease, Y decrease
    vDisplayWriteCmdString(RamDataEntryMode, sizeof(RamDataEntryMode));
}

inline void vDisplayUpdateFull(void)
{
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
    vDisplayWriteCmdPair(0x22, 0xc7);
    // 0x20 = Master Activation
    // Activate Display Update Sequence
    // The Display Update Sequence Option is
    // located at R22h    
    vDisplaySendCmd(0x20);
    //0xFF = NOP
    //This command is an empty command; it
    //does not have any effect on the display module.
    //However it can be used to terminate Frame Memory
    //Write or Read Commands.   
    vDisplaySendCmd(0xff);
}

inline void vDisplayLoadFlashImageToDisplayRam(uint8_t  XSize,
                                        uint16_t YSize,
                                        const uint8_t  *image)
{
    uint8_t x;
    uint16_t y;
    uint16_t index = 0;

    //Convert Xsize from pixels to bytes, rounding up
    XSize = ( XSize + 7 ) >> 3;

    while( true == bDisplayIsBysy() ); // wait 
  
    //Select the controller   
    //ePaper_CS_0;                     

    //Write the command, 0x24
    //ePaper_DC_0;
    vDisplaySendCmd( 0x24 );

    //Pump the image out as data    
    //ePaper_DC_1;

    for( y = 0; y < YSize; y++ )
        {
            for( x = 0; x < XSize; x++ )
                {
                    vDisplaySendData( pgm_read_byte( &image[index++] ) );
                }
        }
    //Deslect the controller   
    //ePaper_CS_1;
}

inline void vDisplaySetArea(uint8_t  RAM_XST,uint8_t  RAM_XEND,
                     uint16_t RAM_YST,uint16_t RAM_YEND)
{
    uint8_t buffer[5];
    //Set region X
    buffer[0] = 0x44; // command
    buffer[1] = RAM_XST;
    buffer[2] = RAM_XEND;
    vDisplayWriteCmdString(buffer,3);
    //Set region Y
    buffer[0] = 0x45; // command
    buffer[1] = (uint8_t)(RAM_YST&0x00FF);
    buffer[2] = (uint8_t)(RAM_YST>>8);
    buffer[3] = (uint8_t)(RAM_YEND&0x00FF);
    buffer[4] = (uint8_t)(RAM_YEND>>8);
    vDisplayWriteCmdString(buffer,5);

    //Set origin X
    buffer[0] = 0x4e; //command
    buffer[1] = RAM_XST;
    vDisplayWriteCmdString(buffer, 2);
    //Set origin Y
    buffer[0] = 0x4f;
    buffer[1] = (uint8_t)(RAM_YST&0x00FF);
    buffer[2] = (uint8_t)(RAM_YST>>8);
    vDisplayWriteCmdString(buffer, 3);
}

inline void vDisplayPowerOn(void)
  {
      vDisplayWriteCmdPair(0x22, 0xC0);

      vDisplaySendCmd(0x20);

      while( true == bDisplayIsBysy() ); // wait 
  }
inline void vDisplayPowerOff(void)
  {
      vDisplayWriteCmdPair(0x22, 0xC0);

      vDisplaySendCmd(0x20);

      while( true == bDisplayIsBysy() ); // wait 
  }

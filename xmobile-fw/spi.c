//spi.c
#include "spi.h"

void vSpiSendByte(char byte);
void vSpiSendByte(char byte)
{
  PORTB &= ~0x01;
  SPDR = byte;
  while(!(SPSR & (1 << SPIF)));
  PORTB |= 0x01;
}

void vSpiSendTask(void* pvParameters)
{
  (void)(pvParameters);
  char ch;
  size_t result;
  
  for(;;)
      {
          result = xStreamBufferReceive( context.xDebugStream,
                                       &ch,
                                       sizeof(ch),
                                       portMAX_DELAY ); // infinite waite
          
          if( result == 1 )
              {
                  dbg("SPI begin");
                  vSpiSendByte(ch);
                  dbg("SPI end");
              }
      }
}

/*void vSpiReadTask(void* pvParameters)
{
    (void)(pvParameters);
    }*/

void SpiSendStream(char* msg)
{
    size_t len = strlen(msg);
    size_t i;
    size_t result;
    
    const TickType_t xDelayMs = pdMS_TO_TICKS( 100 );

    for(i = 0; i < len; i++)
        {
            result = xStreamBufferSend( context.xDisplayStream, //target stream
                                        (void*) (msg + i),               //data byte
                                        (size_t)1,            // data size in bytes
                                        xDelayMs );               // time in ticks  to waite

            if(result != 1)
                {
                    vEnablePin13();
                }
        }
}

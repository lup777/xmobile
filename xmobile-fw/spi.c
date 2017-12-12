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
  unsigned char ch;
  size_t result;
  
  for(;;)
      {
          result = xStreamBufferReceive( context.xDisplayStream,
                                       &ch,
                                       sizeof(ch),
                                       portMAX_DELAY ); // infinite waite
          
          if( result == 1 )
	    {
	      vSpiSendByte(ch);
	    }
      }
}

/*void vSpiReadTask(void* pvParameters)
{
    (void)(pvParameters);
    }*/

void SpiSendStream(unsiged char* msg, size_t len)
{
    size_t result;
    
    const TickType_t xDelayMs = pdMS_TO_TICKS( 100 );

    result = xStreamBufferSend( context.xDisplayStream, //target stream
				(void*) msg,               //data byte
				len,            // data size in bytes
				xDelayMs );               // time in ticks  to waite

    if(result != len)
      {
	vEnablePin13();
      }
}

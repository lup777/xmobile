//spi.c
#include "spi.h"

void vSpiSend(char byte)
{
  PORTB &= ~0x01;
  SPDR = byte;
  while(!(SPSR & (1 << SPIF)));
  PORTB |= 0x01;
}

void vSpiSendTask(void* pvParameters)
{
  TickType_t xLastWakeTime;

  struct struct_queues* pxQueues = (QueueHandle_t) pvParameters;
  char data;
  
  for(;;)
    {
      if( xQueueReceive(pxQueues->spi, &data, (TickType_t) 0) == pdPASS)
	{
	  dbg(pxQueues, 3);
	  vSpiSend(data);
	  //vTaskDelayUntil(&xLastWakeTime, 40);
	    //MSG_SPI_DATA_WAS_SENT
	  dbg(pxQueues, 2);
	  
	}
    }
}

void vSpiReadTask(void* pvParameters)
{
  
}

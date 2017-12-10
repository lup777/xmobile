//spi.c
#include "spi.h"

void vSpiSend(char byte)
{
  SPDR = byte;
  while(!(SPSR & (1 << SPIF)));
}

void vSpiSendTask(void* pvParameters)
{
  TickType_t xLastWakeTime;

  QueueHandle_t xQueue = (QueueHandle_t) pvParameters;
  char data;
  
  for(;;)
    {
      if( xQueueReceive(xQueue, &data, (TickType_t) 0) == pdPASS)
	{
	  vSpiSend(data);
	  //vTaskDelayUntil(&xLastWakeTime, 40);
	}
    }
}

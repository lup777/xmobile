//usart.c
#include "usart.h"

void vUsartSendTask(void* pvParameters)
{
  TickType_t xLastWakeTime;
  unsigned char errno = 0;
  char* msg = NULL;

  QueueHandle_t xQueue = (QueueHandle_t) pvParameters;
  
  for(;;)
    {
      if( xQueueReceive(xQueue, &errno, (TickType_t) 0) == pdPASS)
	{
	  switch(errno)
	    {
	    case 0: msg = ERROR_MSG_1;
	      break;
	      
	    default:
	      msg = ERROR_MSG_0;
	      break;
	    } // switch (errno)

	  unsigned char len = strlen(msg);
	  
	  for(unsigned char i = 0; i < len ; i++)
	    {
	      while( !(UCSR0A & (1 << UDRE0) ) );
	      UDR0 = msg[i];
	      
	      //vTaskDelayUntil(&xLastWakeTime, 40);
	    }

	  while( !(UCSR0A & (1 << UDRE0) ) );
	  UDR0 = '\n';
	}// if
    }
}

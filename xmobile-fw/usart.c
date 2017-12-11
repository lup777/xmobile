//usart.c
#include "usart.h"

void dbg(struct struct_queues* pxQueues, unsigned char ucMsgNo)
{
  xQueueSend(pxQueues->debug, (void*) &ucMsgNo, (TickType_t) 0);
}

void vUsartSendTask(void* pvParameters)
{
  TickType_t xLastWakeTime;
  unsigned char errno = 0;
  char* msg = NULL;

  struct struct_queues* pxQueues = (QueueHandle_t) pvParameters;
  
  for(;;)
    {
      if( xQueueReceive(pxQueues->debug, &errno, (TickType_t) 0) == pdPASS)
	{
	  switch(errno)
	    {
	    case 0: msg = ERROR_MSG_1;
	      break;

	    case 2: msg = MSG_SPI_DATA_WAS_SENT;
	      break;

	    case 3: msg = MSG_SPI_DATA_GOINT_TO_SEND;
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

// main.c

#include "global.h"
#include "usart.h"
#include "spi.h"
static void vTestTask( void* pvParameters );

/*-----------------------------------------------------------*/

void vHwInitAtmega2560()
{
  /* USART 0 */
  UBRR0H &= ~0x0F;

  //UBRR0L = 103; //9600 bps, 16MGz
  //UBRR0L = 68;  //14400 bps, 16MGz
  //UBRR0L = 51;  //19200 bps, 16MGz
  //UBRR0L = 34;  //28800 bps, 16MGz
  //UBRR0L = 25;  //38400 bps, 16MGz
  UBRR0L = 16;  //57600 bps, 16MGz
  //UBRR0L = 12;  //76800 bps, 16MGz
  //UBRR0L = 8;   //115200 bps, 16MGz
  
  UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
  UCSR0B = (1 << RXEN0) | (1 << TXEN0);

  /* Debug */
  vDisablePin13();

  /* SPI Master */
  /*MOSI - PB2
    MISO - PB3
    SS   - PB0
    SCK  - PB1
  */
  DDRB |= (1 << 2);  // MOSI
  DDRB &= ~(1 << 3); // MISO
  DDRB |= (1 << 1);  // SCK
  
  SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR0); // f/16
}
typedef struct struct_queues
{
  QueueHandle_t debug;
  QueueHandle_t spi;
};

void main( void )
{
  /* Initialisations */
  vHwInitAtmega2560();
  
  /* Variables */
  QueueHandle_t xDebugQueue = xQueueCreate(5, sizeof(unsigned char));
  CHECK_FOR_NULL(xDebugQueue);
  QueueHandle_t xSpiQueue = xQueueCreate(5, sizeof(unsigned char));
  CHECK_FOR_NULL(xDebugQueue);

  struct_queues queues;
  queues.debug = xDebugQueue;
  queues.spi = xSpiQueue;
  
  /* Tasks */
  xTaskCreate( vUsartSendTask,
	       (signed char*)"send_uart_task",
	       configMINIMAL_STACK_SIZE,
	       (void*) xDebugQueue,
	       1,
	       NULL );

  xTaskCreate( vSpiSendTask,
	       (signed char*)"send_spi_task",
	       configMINIMAL_STACK_SIZE,
	       (void*) xSpiQueue,
	       1,
	       NULL );

  xTaskCreate( vTestTask,
	       (signed char*)"blink_GPIO_7_task",
	       configMINIMAL_STACK_SIZE,
	       (void*) &queues,
	       1,
	       NULL );
	
  vTaskStartScheduler();

}
/*-----------------------------------------------------------*/


static void vTestTask( void* pvParameters )
{
  struct_queues* queues  = (struct struct_queues *) pvParameters;

  TickType_t xLastWakeTime;
  unsigned long delay = 1000;
  unsigned char errno = 0;
  char ch = 'a';

  for(;;)
    {
      vTogglePin13();

      xQueueSend(queues->debug, (void*) &errno, (TickType_t) 0);
      xQueueSend(queues->spi, (void*) &ch, (TickType_t) 0);
      
      vTaskDelayUntil(&xLastWakeTime, delay);
    }
}


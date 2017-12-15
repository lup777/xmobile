// main.c

#include "global.h"
#include "usart.h"
#include "spi.h"
#include "display.h"

static void vTestTask( void* pvParameters );
void vMainInitContext(void);
void vHwInitAtmega2560(void);
/*-----------------------------------------------------------*/

void vHwInitAtmega2560(void)
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
  //DDRB &= ~(1 << 3); // MISO
  DDRB |= (1 << 1);  // SCK
  DDRB |= (1 << 0);     // SS
  PORTB &= ~(1 << 0);
  
  SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR0) | (1 << SPR1); // f/128
  

  /* DISPLAY */
  DDRC  &= ~(1 < 1); // BUSY
  
  DDRC  |= (1 << 0); // RESET
  PORTC |= (1 << 0); // RESET
  
  DDRG  |= (1 << 2); // DC
  PORTG |= (1 << 2); // DC

  PORTB |= (1 << 0); // CS
}

void vMainInitContext(void)
{
    context.xDebugStream = xStreamBufferCreate(200, // size
                                               1);  //trigger level
    CHECK_FOR_NULL(context.xDebugStream);

    
    context.xDisplayStream = xStreamBufferCreate(200, // size
                                                 1);  //trigger level
    CHECK_FOR_NULL(context.xDisplayStream);
}

struct struct_context context;

int main( void )
{
  /* Initialisations */
  vHwInitAtmega2560();

  vMainInitContext();
  
  /* Variables */
  
  /* Tasks */
  /*xTaskCreate( vUsartSendTask,
	       "send_uart_task",
	       configMINIMAL_STACK_SIZE,
	       (void*) NULL,
	       1,
	       NULL );*/

  /*xTaskCreate( vSpiSendTask,
	       "send_spi_task",
	       configMINIMAL_STACK_SIZE,
	       (void*) NULL,
	       1,
	       NULL );*/

  xTaskCreate( vTestTask,
	       "test_task",
	       configMINIMAL_STACK_SIZE,
	       (void*) NULL,
	       1,
	       NULL );

  /*xTaskCreate( vDisplayTask,
	       "display_task",
	       configMINIMAL_STACK_SIZE,
	       (void*) NULL,
	       1,
	       NULL );*/
	
  vTaskStartScheduler();
  return 0;
}
/*-----------------------------------------------------------*/


static void vTestTask( void* pvParameters )
{
    (void)(pvParameters);
    TickType_t xLastWakeTime;
    unsigned long delay = 2000;

    dbg("init display\n");
    vDisplayInit();
      
    for(;;)
        {
	  vEnablePin13();
	    //dbg("draw background\n");
	    vUsartSendString("draw background\n");
            //SpiSendStream("Hello from SPI\n");
	    vDisplayShowBackground();
	    vDisablePin13();
            
            vTaskDelayUntil(&xLastWakeTime, delay);
        }
}

inline void vEnablePin13(void)
{
  DDRB  |= (1 << 6);
  PORTB |= (1 << 6);
}

inline void vDisablePin13(void)
{
  DDRB  |= (1 << 6);
  PORTB &= ~(1 << 6);
}

inline void vTogglePin13(void)
{
  //DDRB  |= (1 << 7);
  PORTB ^= (1 << 6);
}

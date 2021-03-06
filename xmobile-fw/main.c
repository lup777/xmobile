// main.c

#include "global.h"
#include "usart.h"
#include "spi.h"
#include "display.h"
#include "gsm.h"
#include <stdio.h>
#include <string.h>
#include "disp42/epd4in2.h"

static void vTestTask( void* pvParameters );
void vMainInitContext(void);
void vHwInitAtmega2560(void);
void dbg(char* format, ...);
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
  //UBRR0L = 16;  //57600 bps, 16MGz
  //UBRR0L = 12;  //76800 bps, 16MGz
  UBRR0L = 8;   //115200 bps, 16MGz
  
  UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
  UCSR0B = (1 << RXEN0) | (1 << TXEN0);

  vGsmUart1Init(57600);
    
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
  DDRB |= 0x01;     // SS
  PORTB &= ~0x01;
  
  SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR0); // f/16
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

  /*  xTaskCreate( vSpiSendTask,
	       "send_spi_task",
	       configMINIMAL_STACK_SIZE,
	       (void*) NULL,
	       1,
	       NULL );*/

  xTaskCreate( vTestTask,
	       "blink_GPIO_7_task",
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
    unsigned long delay = 1000;

    for(;;)
        {
            vTogglePin13();
	    //vGsmUsartTest("gsm usart test\n");
            //SpiSendStream("Hello from SPI\n");
	    //vGsmModuleInit();

	    dbg("Hello from %s:%d", __PRETTY_FUNCTION__, __LINE__);
            vTaskDelayUntil(&xLastWakeTime, delay);
        }
}

inline void vEnablePin13(void)
{
  DDRB  |= (1 << 7);
  PORTB |= (1 << 7);
}

inline void vDisablePin13(void)
{
  DDRB  |= (1 << 7);
  PORTB &= ~(1 << 7);
}

inline void vTogglePin13(void)
{
  //DDRB  |= (1 << 7);
  PORTB ^= (1 << 7);
}

inline void dbg(char* format, ...)
{
  char buffer[50];
  va_list argptr;
  va_start(argptr, format);
  vsprintf(buffer, format, argptr);
  va_end(argptr);
  
  int len = strlen(buffer);
  for(int i = 0; i < len; i++)
    {
      vUsartSendByte(buffer[i]);
    }
  vUsartSendByte(13);
  vUsartSendByte(10);
}

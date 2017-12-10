/*
 * FreeRTOS Kernel V10.0.0
 * Copyright (C) 2017 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software. If you wish to use our Amazon
 * FreeRTOS name, please do so in a fair use way that does not cause confusion.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * http://www.FreeRTOS.org
 * http://aws.amazon.com/freertos
 *
 * 1 tab == 4 spaces!
 */

/*
 * Creates all the demo application tasks, then starts the scheduler.  The WEB
 * documentation provides more details of the demo application tasks.
 *
 * Main. c also creates a task called "Check".  This only executes every three
 * seconds but has the highest priority so is guaranteed to get processor time.
 * Its main function is to check that all the other tasks are still operational.
 * Each task that does not flash an LED maintains a unique count that is
 * incremented each time the task successfully completes its function.  Should
 * any error occur within such a task the count is permanently halted.  The
 * check task inspects the count of each task to ensure it has changed since
 * the last time the check task executed.  If all the count variables have
 * changed all the tasks are still executing error free, and the check task
 * toggles an LED.  Should any task contain an error at any time the LED toggle
 * will stop.
 *
 * The LED flash and communications test tasks do not maintain a count.
 */

/*
Changes from V1.2.0

	+ Changed the baud rate for the serial test from 19200 to 57600.

Changes from V1.2.3

	+ The integer and comtest tasks are now used when the cooperative scheduler
	  is being used.  Previously they were only used with the preemptive
	  scheduler.

Changes from V1.2.5

	+ Set the baud rate to 38400.  This has a smaller error percentage with an
	  8MHz clock (according to the manual).

Changes from V2.0.0

	+ Delay periods are now specified using variables and constants of
	  TickType_t rather than unsigned long.

Changes from V2.6.1

	+ The IAR and WinAVR AVR ports are now maintained separately.

Changes from V4.0.5

	+ Modified to demonstrate the use of co-routines.

*/

#include <stdlib.h>
#include <string.h>

#ifdef GCC_MEGA_AVR
	/* EEPROM routines used only with the WinAVR compiler. */
	#include <avr/eeprom.h>
#endif

/* Scheduler include files. */
#include "FreeRTOS.h"
#include "task.h"
#include "croutine.h"

/* Demo file headers. */
#include "PollQ.h"
#include "integer.h"
#include "serial.h"
#include "comtest.h"
#include "crflash.h"
#include "print.h"
#include "partest.h"
#include "regtest.h"

/* Priority definitions for most of the tasks in the demo application.  Some
tasks just use the idle priority. */
#define mainLED_TASK_PRIORITY			( tskIDLE_PRIORITY + 1 )
#define mainCOM_TEST_PRIORITY			( tskIDLE_PRIORITY + 2 )
#define mainQUEUE_POLL_PRIORITY			( tskIDLE_PRIORITY + 2 )
#define mainCHECK_TASK_PRIORITY			( tskIDLE_PRIORITY + 3 )

/* Baud rate used by the serial port tasks. */
#define mainCOM_TEST_BAUD_RATE			( ( unsigned long ) 38400 )

/* LED used by the serial port tasks.  This is toggled on each character Tx,
and mainCOM_TEST_LED + 1 is toggles on each character Rx. */
#define mainCOM_TEST_LED				( 5 ) //( 4 )

/* LED that is toggled by the check task.  The check task periodically checks
that all the other tasks are operating without error.  If no errors are found
the LED is toggled.  If an error is found at any time the LED is never toggles
again. */
#define mainCHECK_TASK_LED				( 5 ) //( 7 )

/* The period between executions of the check task. */
#define mainCHECK_PERIOD				( ( TickType_t ) 3000 / portTICK_PERIOD_MS  )

/* An address in the EEPROM used to count resets.  This is used to check that
the demo application is not unexpectedly resetting. */
#define mainRESET_COUNT_ADDRESS			( ( void * ) 0x50 )

/* The number of coroutines to create. */
#define mainNUM_FLASH_COROUTINES		( 3 )

/*
 * The task function for the "Check" task.
 */
static void vErrorChecks( void *pvParameters );

/*
 * Checks the unique counts of other tasks to ensure they are still operational.
 * Flashes an LED if everything is okay.
 */
static void prvCheckOtherTasksAreStillRunning( void );

/*
 * Called on boot to increment a count stored in the EEPROM.  This is used to
 * ensure the CPU does not reset unexpectedly.
 */
static void prvIncrementResetCount( void );

/*
 * The idle hook is used to scheduler co-routines.
 */
void vApplicationIdleHook( void );

static void vBlikGpio13Task( void* pvParameters );
static void vBlikGpio7Task( void* pvParameters );
inline void vTogglePin13();
inline void vEnablePin13();
inline void vDisablePin13();
static void vUsartSendTask(void* pvParameters);
/*-----------------------------------------------------------*/

void vHwInitAtmega328p()
{
  /*UART 0*/
  /* UCSR0A
     |  7   |  6   |  5    |  4  |   3  |  2   |  1   |  0    |
     | RXC0 | TXC0 | UDRE0 | FE0 | DOR0 | UPE0 | U2X0 | MPCM0 |
     Bit7 - RXC0: USART receive complete flag. Is set when there is 
                  unread data in buffer.
     Bit6 - TXC0: USART transmit complete flag. Is set when a frame
                  in shift register has been shifted out.
     Bit5 - UDRE0:USART data register empty. Ready to receive new data.
                  1 - buffer is empty
     Bit4 - FE0:  frame error. (this bit received in Master mod)
     Bit3 - DOR0: Data OverRun.
     Bit2 - UPE0: USART Parity Error. Always set thi bit to zero 
                  when writing to UCSR0A. (this bit received in Master 
                  mod)
     Bit1 - U2X0: Double the USART trabsmission speed. Only for async 
                  operation. write to 0 when using synchronous 
                  operation/
     Bit0 - MPCM0: Multi-processor communication mode. */
  

  /* UCSR0B
     |   7    |   6    |   5    |  4    |  3    |   2    |   1   |  0  |
     | RXCIE0 | TXCIE0 | UDRIE0 | RXEN0 | TXEN0 | UCSZ02 | RXB80 |TXB80|
     7 - RXCIE0: разрешение прерывания по завершению приёма.
                 1 - приём завершён
     6 - TXCIE0: разрешение прерываня по завершению передачи.
     5 - UDRIE0: разрешение прерывания по опустошению регистра
                 передатчика.
     4 - RXEN0:  разрешение приёма. 
                 1 - приём разрешён, переопределяется функционироване 
                 вывода RXD
     3 - TXEN0:  разрешенте передачи.
     2 - UCSZ02: формат послок, сколько бит будет передавать в посылках 
                 (5, 6, 7, 8 или 9)
     1 - RXB80:  9й разряд принимаемых данных
     0 - TXB80:  9й разряд передаваемых данных
   */

  
  /* UCSR0C
     |   7     |   6     |   5   |  4    |  3   |   2   |   1   |  0 |
     | UMSEL01 | UMSEL00 | UPM01 | UPM00 | USBS0|UCSZ01/|UCSZ00/|UCPOL0|
     |         |         |       |       |      |UDORD0 |UCPHA0 |
     
     7..6 - UMSEL0n: USART mode select.
            UMSEL0[1:0] | mode
	             00 | async USART
		     01 | sync USART
		     10 | reserved
		     11 | master SPI
     5..4 - USART parity mode. Режим проверки на чётность и нечётность
     UPM[1:0] | mode
           00 | Выключен
	   10 | включён, проверка на чётность
	   11 | включен, проверка на нечётность

     3 - USBS: количество стоп битов.
               1 - два стоп бита
	       0 - один стоп бит
	
     2 - UCSZ01: character size
  */

  /* 
     UBRR0L - скорость обмена данными 8bit used for boud rate
     UBRR0H - скорость обмена данными 4bit register high [3-0] 
              (наиболее значимые)
     Для 16 мегагерц:
     9600 bps: UBRRn = 103
     1152k bps: UBRRn = 8
     57.6  bps: UBRRn = 16
*/
  UBRR0H &= ~0x0F;
  UBRR0L = 103; //9600 bps, 16MGz
  //UBRR0L = 51; //9600 bps, 8MGz
  UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
  UCSR0B = (1 << RXEN0) | (1 << TXEN0);
}

void main( void )
{
  vHwInitAtmega328p();
  //prvIncrementResetCount();
  
  vParTestInitialise();

  xTaskCreate( vUsartSendTask,
	       (signed char*)"send_uart__task",
	       configMINIMAL_STACK_SIZE,
	       NULL,
	       1,
	       NULL );

  xTaskCreate( vBlikGpio7Task,
	       (signed char*)"blink_GPIO_7_task",
	       configMINIMAL_STACK_SIZE,
	       NULL,
	       1,
	       NULL );
	
  vTaskStartScheduler();

}
/*-----------------------------------------------------------*/

static void vUsartSendTask(void* pvParameters)
{
  TickType_t xLastWakeTime;
  char ch = 0;
  
  for(;;)
    {
      for(ch = 0; ch < 255; ch++)
	{
	  UDR0 = ch;

	  while(UCSR0A & (1 << TXC0) == 0) {}

	  vTogglePin13();
      
	  vTaskDelayUntil(&xLastWakeTime, 500);
	}
    }
}

static void vBlikGpio7Task( void* pvParameters )
{
  unsigned char pin7 = (1 << 7);
  
  DDRD |= pin7;
  PORTD |= pin7;
  TickType_t xLastWakeTime;
  unsigned long delay = 1000;
  
  for(;;)
    {
      PORTD ^= pin7;
      vTaskDelayUntil(&xLastWakeTime, delay);
    }
}

inline void vEnablePin13()
{
  DDRB  |= (1 << 5);
  PORTB |= (1 << 5);
}
inline void vDisablePin13()
{
  DDRB  |= (1 << 5);
  PORTB &= ~(1 << 5);
}
inline void vTogglePin13()
{
  DDRB  |= (1 << 5);
  PORTB ^= (1 << 5);
}

static void vErrorChecks( void *pvParameters )
{
static volatile unsigned long ulDummyVariable = 3UL;

	/* The parameters are not used. */
	( void ) pvParameters;

	/* Cycle for ever, delaying then checking all the other tasks are still
	operating without error. */
	for( ;; )
	{
		vTaskDelay( mainCHECK_PERIOD );

		/* Perform a bit of 32bit maths to ensure the registers used by the
		integer tasks get some exercise. The result here is not important -
		see the demo application documentation for more info. */
		ulDummyVariable *= 3;

		prvCheckOtherTasksAreStillRunning();
	}
}
/*-----------------------------------------------------------*/

static void prvCheckOtherTasksAreStillRunning( void )
{
static portBASE_TYPE xErrorHasOccurred = pdFALSE;

	if( xAreIntegerMathsTaskStillRunning() != pdTRUE )
	{
		xErrorHasOccurred = pdTRUE;
	}

	if( xAreComTestTasksStillRunning() != pdTRUE )
	{
		xErrorHasOccurred = pdTRUE;
	}

	if( xArePollingQueuesStillRunning() != pdTRUE )
	{
		xErrorHasOccurred = pdTRUE;
	}

	if( xAreRegTestTasksStillRunning() != pdTRUE )
	{
		xErrorHasOccurred = pdTRUE;
	}

	if( xErrorHasOccurred == pdFALSE )
	{
		/* Toggle the LED if everything is okay so we know if an error occurs even if not
		using console IO. */
		vParTestToggleLED( mainCHECK_TASK_LED );
	}
}
/*-----------------------------------------------------------*/

static void prvIncrementResetCount( void )
{
unsigned char ucCount;

	eeprom_read_block( &ucCount, mainRESET_COUNT_ADDRESS, sizeof( ucCount ) );
	ucCount++;
	eeprom_write_byte( mainRESET_COUNT_ADDRESS, ucCount );
}
/*-----------------------------------------------------------*/

void vApplicationIdleHook( void )
{
	vCoRoutineSchedule();
}


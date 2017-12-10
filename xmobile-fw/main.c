#include <stdlib.h>
#include <string.h>

#ifdef GCC_MEGA_AVR
	/* EEPROM routines used only with the WinAVR compiler. */
	#include <avr/eeprom.h>
#endif

/* Scheduler include files. */
#include "FreeRTOS.h"
#include "task.h"

/* Demo file headers. */
//#include "integer.h"
#include "queue.h"
#include "string.h"

static void vBlikGpio13Task( void* pvParameters );
static void vBlikGpio7Task( void* pvParameters );
inline void vTogglePin13();
inline void vEnablePin13();
inline void vDisablePin13();
static void vUsartSendTask(void* pvParameters);

/*-----------------------------------------------------------*/

void vHwInitAtmega2560()
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
     7 - RXCIE0: ���������� ���������� �� ���������� ��ɣ��.
                 1 - ��ɣ� �����ۣ�
     6 - TXCIE0: ���������� ��������� �� ���������� ��������.
     5 - UDRIE0: ���������� ���������� �� ����������� ��������
                 �����������.
     4 - RXEN0:  ���������� ��ɣ��. 
                 1 - ��ɣ� �����ۣ�, ���������������� ��������������� 
                 ������ RXD
     3 - TXEN0:  ���������� ��������.
     2 - UCSZ02: ������ ������, ������� ��� ����� ���������� � �������� 
                 (5, 6, 7, 8 ��� 9)
     1 - RXB80:  9� ������ ����������� ������
     0 - TXB80:  9� ������ ������������ ������
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
     5..4 - USART parity mode. ����� �������� �� ޣ������ � ��ޣ������
     UPM[1:0] | mode
           00 | ��������
	   10 | ����ޣ�, �������� �� ޣ������
	   11 | �������, �������� �� ��ޣ������

     3 - USBS: ���������� ���� �����.
               1 - ��� ���� ����
	       0 - ���� ���� ���
	
     2 - UCSZ01: character size
  */

  /* 
     UBRR0L - �������� ������ ������� 8bit used for boud rate
     UBRR0H - �������� ������ ������� 4bit register high [3-0] 
              (�������� ��������)
     ��� 16 ��������:
     9600 bps: UBRRn = 103
     1152k bps: UBRRn = 8
     57.6  bps: UBRRn = 16
*/
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
}

#define CHECK_FOR_NULL(X) { if(X == NULL) vEnablePin13(); }

#define ERROR_MSG_0 "Hellow from FreeRTOS";
#define ERROR_MSG_1 "Hellow from FreeRTOS1";

void main( void )
{
  /* Initialisations */
  vHwInitAtmega2560();
  
  /* Variables */
  QueueHandle_t xDebugQueue = xQueueCreate(5, sizeof(unsigned char));
  CHECK_FOR_NULL(xDebugQueue);

  /* Tasks */
  xTaskCreate( vUsartSendTask,
	       (signed char*)"send_uart__task",
	       configMINIMAL_STACK_SIZE,
	       (void*) xDebugQueue,
	       1,
	       NULL );

  xTaskCreate( vBlikGpio7Task,
	       (signed char*)"blink_GPIO_7_task",
	       configMINIMAL_STACK_SIZE,
	       (void*) xDebugQueue,
	       1,
	       NULL );
	
  vTaskStartScheduler();

}
/*-----------------------------------------------------------*/

static void vUsartSendTask(void* pvParameters)
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

static void vBlikGpio7Task( void* pvParameters )
{
  QueueHandle_t xQueue = (QueueHandle_t) pvParameters;

  TickType_t xLastWakeTime;
  unsigned long delay = 1000;
  unsigned char errno = 0;
  for(;;)
    {
      vTogglePin13();
      xQueueSend(xQueue, (void*) &errno, (TickType_t) 0);
      vTaskDelayUntil(&xLastWakeTime, delay);
    }
}

inline void vEnablePin13()
{
  DDRB  |= (1 << 7);
  PORTB |= (1 << 7);
}
inline void vDisablePin13()
{
  DDRB  |= (1 << 7);
  PORTB &= ~(1 << 7);
}
inline void vTogglePin13()
{
  //DDRB  |= (1 << 7);
  PORTB ^= (1 << 7);
}

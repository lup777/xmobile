// main.c
#include <avr/io.h>
#include <string.h>

/* Scheduler include files. */
#include "FreeRTOS.h"
#include "task.h"

typedef uint8_t bool;
#define false  0
#define true   1

#define USART0_SendStr(X) log(X)

static void vTogglePA0Task(void* pvParameters);
/* GPIO
   PORT (those bits controls GPIO lines):
   DIR - direction
   OUT - to write output value
   IN - to read input value 
   PINnCTRL = configuration   
 */

void gpio_init() {
  //PINnCTRL  //pull down
  PORTA.DIRSET = PIN0_bm; // PORT A, PIN 0,  OUT
}

void GPIO_toggle_PA0() {
  PORTA.OUTTGL = PIN0_bm;
}

void USART_init() {
  // 1. Set the TxD pin value high, and optionally set the XCK low
  PORTF.OUTSET = PIN3_bm;
  // 2. Set the TxD and optionally the XCK pin as output.
  PORTF.DIRSET = PIN3_bm;
  // 3. Set the baud rate and frame format.
  // Communication mode: Asynchronous USART
  // Data bits: 8
  // Stop bits: 1
  // Parity: Disabled
  USARTF0.CTRLC = USART_CMODE_ASYNCHRONOUS_gc | USART_PMODE_DISABLED_gc
    | USART_CHSIZE_8BIT_gc;
  // Receive complete interrupt: Low Level
  // Transmit complete interrupt: Disabled
  // Data register empty interrupt: Disabled
  USARTF0.CTRLA |= USART_RXCINTLVL_gm | USART_TXCINTLVL_gm | USART_DREINTLVL_gm
    | USART_RXCINTLVL_LO_gc | USART_TXCINTLVL_OFF_gc | USART_DREINTLVL_OFF_gc;

  // Required Baud rate: 9600
  // Real Baud Rate: 9601.0 (x2 Mode), Error: 0.0 %
  USARTF0.BAUDCTRLA = 25;
  USARTF0.BAUDCTRLB = 0;//((0x09 << USART_BSCALE_bp) & USART_BSCALE_gm) | 0x0C;
  // Receiver: On
  // Transmitter: On
  // Double transmission speed mode: On
  // Multi-processor communication mode: Off
  USARTF0.CTRLB |= USART_TXEN_bm | USART_CLK2X_bm |  USART_TXB8_bm;

  // 4. Set the mode of operation (enables XCK pin output in synchronous mode).
  // 5. Enable the transmitter or the receiver, depending on the usage.2.
  
}

int main( void ) {
  gpio_init();
  USART_init();

  xTaskCreate( vTogglePA0Task,
	       "blink_PORTA_0_task",
	       configMINIMAL_STACK_SIZE,
	       (void*) NULL,
	       1,
	       NULL );

  vTaskStartScheduler();
  
  return 0;
}

void USART0_SendByte(char c) {
  while( !(USARTF0_STATUS & USART_DREIF_bm) ); //Wait until DATA buffer is empty
  USARTF0_DATA = c;
}

void USART0_SendStr(const char* str) {
  volatile uint8_t i = 0;
  uint8_t len = strlen(str);
  for(i = 0; i < len; i++) {
    USART0_SendByte(str[i]);
  }
  USART0_SendByte('\n');
  USART0_SendByte('\r');
}

static void vTogglePA0Task(void* pvParameters) {
  (void)(pvParameters);
  const TickType_t xDelay = 1000 / portTICK_PERIOD_MS;
  log("Start vTogglePA0Task task");
  
  for(;;) {
    GPIO_toggle_PA0();

    vTaskDelay(xDelay);

    log("Hello from FreeRTOS!");
  }
}

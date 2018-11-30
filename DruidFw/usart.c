// usart.c
#include <avr/io.h>
#include <avr/interrupt.h>
#include <string.h>

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "message_buffer.h"

#include "global.h"
#include "usart.h"
#include "kbd.h"

void USART0_SendBuf(char* str);

void _clogu8(const char* str, uint8_t v) {
  LogPairU8 pair;
  pair.msg = str;
  pair.value = v;
  xQueueSend(context.log_queue, &pair, (TickType_t)100);
}

void _clog(const char* msg) {
  LogPairU8 pair;
  pair.msg = msg;
  pair.value = 0;
  xQueueSend(context.log_queue, &pair, (TickType_t)100);
}

void xLogTask(void* pvParameters) {
  (void)(pvParameters);

  for(;;) {
    LogPairU8 pair;
    if (uxQueueMessagesWaiting(context.log_queue) > 0) {
      if( pdTRUE == xQueueReceive(context.log_queue,
				  &pair, portMAX_DELAY) ) {
	USART0_SendStr(pair.msg);

	char buf[] = " ___";
	_u8tos(pair.value, buf + 1, 3, 10);
	USART0_SendBuf(buf);

	USART0_SendByte('\n');
	USART0_SendByte('\r');
      }
    }
  }
}

inline void USART0_init(void) {
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
  USARTF0.CTRLA |= USART_RXCINTLVL_LO_gc | USART_TXCINTLVL_OFF_gc | USART_DREINTLVL_OFF_gc;

  // Required Baud rate: 9600
  // Real Baud Rate: 9601.0 (x2 Mode), Error: 0.0 %
  USARTF0.BAUDCTRLA = 25;
  USARTF0.BAUDCTRLB = 0;//((0x09 << USART_BSCALE_bp) & USART_BSCALE_gm) | 0x0C;
  // Receiver: On
  // Transmitter: On
  // Double transmission speed mode: On
  // Multi-processor communication mode: Off
  USARTF0.CTRLB |= USART_TXEN_bm | USART_RXEN_bm | USART_CLK2X_bm |  USART_TXB8_bm;

  // 4. Set the mode of operation (enables XCK pin output in synchronous mode).
  // 5. Enable the transmitter or the receiver, depending on the usage.2.

}

ISR(USARTF0_RXC_vect) {
  struct {
    char id;
    char key;
  } data;
  data.id = MSG_KBD;
  data.key = USARTF0_DATA;
  MessageBufferHandle_t* pHandle = context.mail + context.active_app_index;
  BaseType_t hptm;
  //if (xMessageBufferSpacesAvailable(*pHandle) + (size_t)2 >= sizeof(data)) { // 2 - sizeof(void*)
  if (data.key >= '0' && data.key <= '9') {
    data.key -= '0';
    data.id = MSG_KBD;
    if (*pHandle != NULL)
      xMessageBufferSendFromISR(*pHandle, (void*)&data, sizeof(data), &hptm);

  } else if (data.key == 'x') {
    data.id = MSG_CLOSE;
    if (*pHandle != NULL)
      xMessageBufferSendFromISR(*pHandle, (void*)&data, sizeof(char), &hptm);

    data.id = MSG_DRAW;
    pHandle = context.mail + MENU_MAILBOX_OFFSET;
    if (*pHandle != NULL)
      xMessageBufferSendFromISR(*pHandle, (void*)&data, sizeof(char), &hptm);
  }
  //}
}

inline void USART0_SendByte(char c) {
  while( !(USARTF0_STATUS & USART_DREIF_bm) ); //Wait until DATA buffer is empty
  USARTF0_DATA = c;
}



void USART0_SendStr(const char* str) {
  volatile uint8_t i = 0;
  const uint8_t len = strlen(str);
  for(i = 0; i < len; i++) {
    USART0_SendByte(str[i]);
  }
}

void USART0_SendBuf(char* str) {
  volatile uint8_t i = 0;
  const uint8_t len = _strlen(str);
  for(i = 0; i < len; i++) {
    USART0_SendByte(str[i]);
  }
}

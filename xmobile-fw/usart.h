//usart.h

#ifndef __USART_H__
#define __USART_H__
#include "global.h"

extern void vUsartSendTask(void* pvParameters);
extern void dbg_const(const char* msg);
extern void dbg_char(char msg);
extern void dbg(char* msg);
extern void vUsartSendByte(char ch);

#endif //__USART_H__

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

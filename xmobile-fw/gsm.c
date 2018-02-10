//gsm.c
#include "gsm.h"
#include <string.h>
void vGsmSendTextModeSms(char* phoneNumber, char* text);
void vGsmSendPduModeSms(char* phoneNumber, char* text);
void vGsmUsart1SendByte(char ch);
char cGsmReadByte(void);


inline void vGsmModuleInit(void)
{
  DDRB |= (1 << 6);
  PORTB &= (1 << 6);
  
  vGsmSendString("AT\n");
  dbg("AT\n");
  int counter = 2;

  do
    {
      char ch = cGsmReadByte();
      dbg_const("from GSM: ");
      dbg_char(ch);
      dbg_const("\n");
      counter --;
    }
  while(counter > 0);

  PORTB |= (1 << 6);
}

inline char cGsmReadByte(void)
{
  while( !(UCSR1A & (1 << RXC1)) );
  return UDR1;
}

inline void vGsmUsart1SendByte(char ch)
{
  while( !(UCSR1A & (1 << UDRE1) ) );
  UDR1 = ch;
}

void vGsmSendString(char* str)
{
  size_t i;
  
  for(i = 0; i < strlen(str); i++)
    {
      vGsmUsart1SendByte(str[i]);
    }
}

inline void vGsmUart1Init(uint32_t speed)
{
    /* USART 0 */
  UBRR1H &= ~0x0F;

  switch(speed)
    {
    case 9600:
      UBRR1L = 103; //9600 bps, 16MGz
      break;

    case 14400:
      UBRR1L = 68;  //14400 bps, 16MGz
      break;

    case 19200:  
      UBRR1L = 51;  //19200 bps, 16MGz
      break;

    case 28800:
      UBRR1L = 34;  //28800 bps, 16MGz
      break;

    case 38400:
      UBRR1L = 25;  //38400 bps, 16MGz
      break;

    case 57600:
      UBRR1L = 16;  //57600 bps, 16MGz
      break;

    case 76800:
      UBRR1L = 12;  //76800 bps, 16MGz
      break;

    case 115200:
      UBRR1L = 8;   //115200 bps, 16MGz
      break;

    default:
      UBRR1L = 16;  //57600 bps, 16MGz
      break;
    }
  
  UCSR1C = (1 << UCSZ11) | (1 << UCSZ10);
  UCSR1B = (1 << RXEN1) | (1 << TXEN1);

}


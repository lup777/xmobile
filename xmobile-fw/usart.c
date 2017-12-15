//usart.c
#include "usart.h"

void vUsartSendByte(char ch);

void dbg(const char* msg)
{
    //context.xDebugStream
    size_t len = strlen(msg);
    size_t result; //num of bytes was sent
    const TickType_t x0ms = pdMS_TO_TICKS( 0 );
    
    result = xStreamBufferSend( context.xDebugStream, //target stream
				(void*)(msg),               //data byte
				len,            // data size in bytes
				x0ms );               // time in ticks  to waite
    if(result != len)
      {
	vEnablePin13();
      }
}

inline void vUsartSendByte(char ch)
{
  while( !(UCSR0A & (1 << UDRE0) ) );
  UDR0 = ch;
}

inline void vUsartSendString(char* str)
{
  size_t len = strlen(str);
  
  for(size_t i = 0; i < len; i++)
    {
      while( !(UCSR0A & (1 << UDRE0) ) );
      UDR0 = str[i];
    }
}

void vUsartSendTask(void* pvParameters)
{
    (void)(pvParameters);
    char ch;
    size_t result;

    dbg("USART start\n");
  
    for(;;)
        {
            result = xStreamBufferReceive( context.xDebugStream,
                                           &ch,
                                           sizeof(ch),
                                           portMAX_DELAY ); // infinite waite
            if( result == 1 )
                {
                    vUsartSendByte(ch);
                }
	}
}

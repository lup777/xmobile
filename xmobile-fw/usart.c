//usart.c
#include "usart.h"

void vUsartSendByte(char ch);

void dbg(const char* msg)
{
    //context.xDebugStream
    size_t i;
    size_t len = sizeof(msg);
    size_t result; //num of bytes was sent
    const TickType_t x0ms = pdMS_TO_TICKS( 0 );
    
    
    for(i = 0; i < len; i++)
        {
            result = xStreamBufferSend( context.xDebugStream, //target stream
                                        (void*)(msg + i),               //data byte
                                        (size_t)1,            // data size in bytes
                                        x0ms );               // time in ticks  to waite
            if(result != 1)
                {
                    vEnablePin13();
                }
        }
}

inline void vUsartSendByte(char ch)
{
    while( !(UCSR0A & (1 << UDRE0) ) );
    UDR0 = ch;
}

void vUsartSendTask(void* pvParameters)
{
    (void)(pvParameters);
    char ch;
    size_t result;
  
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

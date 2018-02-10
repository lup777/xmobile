//usart.c
#include "usart.h"

#define DEBUG

void vUsartSendByte(char ch);

void dbg_const(const char* msg)
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

void dbg_char(char msg)
{
  size_t result; //num of bytes was sent
  const TickType_t x0ms = pdMS_TO_TICKS( 0 );
  
  result = xStreamBufferSend( context.xDebugStream, //target stream
			      (void*)(&msg),               //data byte
			      1,            // data size in bytes
			      x0ms );               // time in ticks  to waite
    if(result != 1)
      {
	vEnablePin13();
      }
}
  
void dbg(char* msg)
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
#ifdef DEBUG
  while( !(UCSR0A & (1 << UDRE0) ) );
  UDR0 = ch;
#else
  (void)(ch);
#endif //DEBUG
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

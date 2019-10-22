// cb.c
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

// circular buffer

//#define CBUF_INIT(__TYPE__, __SIZE__)
typedef uint16_t u16;
typedef uint8_t u8;
typedef int8_t i8;

#define CB_LEN_TYPE u16

typedef struct CBuffer8 {
  union {
    u8* u;
    i8* s;
  };
  CB_LEN_TYPE buf_len;
  CB_LEN_TYPE data_len;
  CB_LEN_TYPE x0;
  CB_LEN_TYPE x1;
} CBuffer8;


void cb_init(CBuffer8* cbuf, void* buffer, CB_LEN_TYPE size) {
  cbuf->u = (u8*)cbuf;
  cbuf->buf_len = size;
}

void cb_pushi(CBuffer8* cbuf, i8 byte) {
  cbuf->s[x1] = byte;

  x1++;
  
  if (x1 >= vbuf->buf_len) {// end of the buffer
    x1 = 0;
    
    if (x0 == 0)
      x0++;
  }
  
}

int main() {
  static char buf[50];
  CBuffer8 cb;
  
  cb_init(&cb, buf, 50);

  
  
  return 0;
}

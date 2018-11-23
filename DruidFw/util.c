// util.c
#include "global.h"
// uint8_t value - value to be converted to string
// char* buf - converted string will be placed here
// uint8_t size - of buffer
uint8_t _u8tos(uint8_t value, char* buf, uint8_t buf_size, uint8_t base) {
  uint8_t i = 8;
  switch(base) { // max char num for uint8_t
    case 16: i = 2; break;
    case 10: i = 3; break;
    case 2: i = 8; break;
    default: i = 8; break;
  }
  if (buf_size < i)
    _clog("ERROR: _u8tos");
  do {
    i--;
    uint8_t digit = (value % base);
    if (digit > 9)
      buf[i] = (value % base) + 'A' - 10;
    else
      buf[i] = (value % base) + '0';
    value /= base;
  } while(i > 0);
  return 3 - i;
}

uint8_t _strlen(char * str) {
  uint8_t len = 0;
  for (; len <= 254; len++) { // 254 to avoid warning about always true
    if (str[len] == 0)
      break;
  }
  return len + 1; // + zero
}

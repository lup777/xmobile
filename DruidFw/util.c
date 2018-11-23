// util.c
#include "global.h"

// uint8_t value - value to be converted to string
// char* buf - converted string will be placed here
// uint8_t size - of buffer

uint8_t _u8tos(uint8_t value, char* buf, uint8_t buf_size, uint8_t base) {
  uint8_t max_len;
  switch(base) { // max char num for uint8_t
    case 16: max_len = 2; break;
    case 10: max_len = 3; break;
    case 2: max_len = 8; break;
    default: max_len = 8; break;
  }
  if (max_len > buf_size)
    max_len = buf_size;
  uint8_t i = max_len;
  do {
    i--;
    uint8_t digit = (value % base);
    if (digit > 9)
      buf[i] = (value % base) + 'A' - 10;
    else
      buf[i] = (value % base) + '0';
    value /= base;
  } while(i > 0);
  return max_len - i;
}

uint8_t _u16tos(uint16_t value, char* buf, uint8_t buf_size, uint8_t base) {
  uint8_t max_len;
  switch(base) { // max char num for uint8_t
    case 16: max_len = 4; break;
    case 10: max_len = 5; break;
    case 2: max_len = 16; break;
    default: max_len = 16; break;
  }
  if (max_len > buf_size)
    max_len = buf_size;
  uint8_t i = max_len;
  do {
    i--;
    uint8_t digit = (value % base);
    if (digit > 9)
      buf[i] = (value % base) + 'A' - 10;
    else
      buf[i] = (value % base) + '0';
    value /= base;
  } while(i > 0);
  return max_len - i;
}

uint8_t _strlen(char * str) {
  uint8_t len = 0;
  for (; len <= 254; len++) { // 254 to avoid warning about always true
    if (str[len] == 0)
      break;
  }
  return len + 1; // + zero
}

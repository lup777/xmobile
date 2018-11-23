// string.c tests
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#define STRLEN(s) (sizeof(s)/sizeof(s[0]))

uint8_t _u8tos(uint8_t value, char* buf, uint8_t buf_size, uint8_t base);

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
  printf("i = %d ", i);
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
  for (; len <= 255; len++) {
    if (str[len] == 0)
      break;
  }
  return len + 1; // + zero
}

int main(void) {
  char buf[] = "K:___";
  const char cstr[] = "const";
  _u8tos(255, buf + 2, 3, 10);
  printf("%s\n", buf);

  printf("strlen: %d\n", _strlen(buf));
  printf("sizeof: %ld\n", sizeof(cstr));

  return 0;
}

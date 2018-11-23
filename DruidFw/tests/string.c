// string.c tests
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#define STRLEN(s) (sizeof(s)/sizeof(s[0]))

uint8_t _u8tos(uint8_t value, char* buf, uint8_t buf_size, uint8_t base);

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

uint8_t _strlen(char * str) {
  uint8_t len = 0;
  for (; len <= 254; len++) { // 254 to avoid warning about always true
    if (str[len] == 0)
      break;
  }
  return len + 1; // + zero
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

int main(void) {
  char buf[] = "K:________________";
  const char cstr[] = "const";
  _u16tos(54550, buf + 2, 16, 2);
  printf("%s\n", buf);

  printf("strlen: %d\n", _strlen(buf));
  printf("sizeof: %ld\n", sizeof(cstr));

  return 0;
}

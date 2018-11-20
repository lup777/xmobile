// struct.c

#include <stdio.h>

const char data[][7] = {
{'f', 'i', 'r', 's', 't', '_'},
{'s', 'e', 'c', 'o', 'n', 'd'},
{'t', 'h', 'e', 'r', 'd', '_'}};

int main(void) {
  int i = 0;
  printf("%s\n", data[1]);
}

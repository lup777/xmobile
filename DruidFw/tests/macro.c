// macro.c

#include <stdio.h>

#define concat(x, y) x ## y
#define T1 "hello "
#define T2 "world\n"


int main() {
  printf(concat(T1,T2));
  return 0;
}

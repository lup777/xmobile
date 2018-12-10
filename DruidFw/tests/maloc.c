// maloc.c
#include <stdio.h>
#include <stdlib.h>

#pragma pack(push)
#pragma pack(1)
union {
  unsigned int d;
  unsigned char a[4];
  char b;
} addr;
#pragma pack(pop)

int main() {

  addr.d = 0x1;

  for (size_t i = 0; i < sizeof(addr); i ++)
    printf("d -> %01X \n", addr.a[i]);

  printf("b = %04X\n", addr.b);

  return 0;
}

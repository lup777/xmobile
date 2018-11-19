// string.c tests
#include <stdio.h>
#define STRLEN(s) (sizeof(s)/sizeof(s[0]))

const char* smg1 = "message 1";
void* imgs[STRLEN(smg1) - 1];

struct struct_msg {
  const char* msg = "message 2";
  void* imgs[STRLEN(msg) - 1];
} MSG1;

int main() {

  printf("size of imgs: %lu\n", sizeof(MSG1.imgs) / sizeof(void*));
  return 0;
}

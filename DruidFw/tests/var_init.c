//var_init.c
#include <stdio.h>

void func(int t) {
  int arr[3] = {4, 3, 2 + 5};

  for (int i = 0; i < 3; i++) {
    printf("arr[%d] = %d\n", i, arr[i]);
  }
}

int main() {
  func(5);
  return 0;
}

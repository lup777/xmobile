// class.c
#include "stdio.h"

typedef struct struct_app {
  // local fields
  struct {
    key;
  } l;

  // methods
  void(*Start)(void);
  void(*OnShow)(void);
  void(*OnKeyPressed)(int key);
  void(*OnClose)(void);
} App;

void start(void) {
  printf("start\n");
}

void OnShow(void) {
  printf("OnShow\n");
}

void OnKeyPressed(int key) {
  printf("OnKeyPressed %d\n", key);
}

void OnClose(void) {
  printf("OnClose");
}

App app;

int main(void) {

  app.start();
  app.OnShow();
  app.OnKeyPressed(3);
  app.OnClose();

  return 0;
}

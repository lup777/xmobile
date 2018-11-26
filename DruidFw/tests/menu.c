// menu.c
#include <ncurses.h>

#define APP_HEADER_LEN 15
//#define MENU_LEN 3
#define FONT_HEIGHT_BITS 1//13
#define SCREEN_MENU_LINES 5

uint8_t menu_state;

void EPD_StartPartial(void) {
  clear();
}
void EPD_UpdatePartial(void) {}
void EPD_StopPartial(void) {}
void EPD_ContinuePartial(const char* msg, uint8_t len,
                         uint8_t x, uint8_t y) {
  for(int i = 0; i < len; i++) {
    if (x >= 24)
      break;

    move(y, x);
    addch(msg[i]);
    x++;
  }
}

char KBD_WaiteKey(void) {
  return getch();
}

void TestApp1(void) {
  EPD_StartPartial();
  EPD_ContinuePartial("      XMobile", 13, 1, 10);
  EPD_ContinuePartial("not implemented yet", 19, 1, 11);
  EPD_StopPartial();
  KBD_WaiteKey();
}


typedef struct struct_application {
  void (*Call) (void);
  const char* header;
} App;

App menu[] = {
  {TestApp1, "telephone      "},
  {TestApp1, "calendar       "},
  {TestApp1, "reader         "},
  {TestApp1, "snake          "},
  {TestApp1, "music player   "}
};

int main() {
  int i = 0;
  char key;
  size_t menu_size = (sizeof(menu) / sizeof(App));

  EPD_StartPartial();
  initscr();
  EPD_ContinuePartial("Hello XMobile", 13, 1, 10);
  EPD_UpdatePartial();
  EPD_StopPartial();
  do {
    key = KBD_WaiteKey();
    switch(key) {
      case '1':
        //if (i > 0)
          i--;
        break;
      case '2':
        //if (i < menu_size - 1)
          i++;
        break;
      case 'e':
        if (i >= 0 && i < menu_size)
          menu[i].Call();
        break;
    }
    EPD_StartPartial();
    //SCREEN_MENU_LINES
    if (i-3 >= 0 && i-3 < menu_size)
      EPD_ContinuePartial(menu[i-3].header, APP_HEADER_LEN, 0,
                          9);
    if (i-2 >= 0 && i-2 < menu_size)
      EPD_ContinuePartial(menu[i-2].header, APP_HEADER_LEN, 1,
                          10);
    if (i-1 >= 0 && i-1 < menu_size)
      EPD_ContinuePartial(menu[i-1].header, APP_HEADER_LEN, 2,
                          11);

    EPD_ContinuePartial("1) ----", 7, 0,12);
    if (i >= 0 && i < menu_size)
      EPD_ContinuePartial(menu[i].header, APP_HEADER_LEN, 3,
                          13);
    EPD_ContinuePartial("2) ----", 7, 0,14);

    if (i+1 >= 0 && i+1 < menu_size)
      EPD_ContinuePartial(menu[i+1].header, APP_HEADER_LEN, 2,
                          15);
    if (i+2 >= 0 && i+2 < menu_size)
      EPD_ContinuePartial(menu[i+2].header, APP_HEADER_LEN, 1,
                          16);
    if (i+3 >= 0 && i+3 < menu_size)
      EPD_ContinuePartial(menu[i+3].header, APP_HEADER_LEN, 0,
                          17);
    EPD_StopPartial();

  } while(key != 'q');


  endwin();

  return 0;
}

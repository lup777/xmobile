// menu.c
#include "menu.h"

#include "kbd.h"
#include "spi.h"

#define APP_HEADER_LEN 15

void MENU_Show(const App* menu) {
  int8_t i = 0;
  Key key;
  int8_t menu_size = (int8_t)((sizeof(menu) / sizeof(App)));

  EPD_StartPartial();
  EPD_ContinuePartial("      XMobile", 13, 1, 10);
  EPD_UpdatePartial();
  EPD_StopPartial();
  do {
    key = KBD_WaiteKey();
    switch(key) {
      case key2:
        i--;
        break;
      case key8:
        i++;
        break;
      case key5:
        if (i >= 0 && i < menu_size)
          menu[i].Call();
        break;
      default:
        break;
    }

    EPD_StartPartial();
    if (i-3 >= 0 && i-3 < menu_size)
      EPD_ContinuePartial((char*)(menu[i-3].header), APP_HEADER_LEN, 0,
                          9);
    if (i-2 >= 0 && i-2 < menu_size)
      EPD_ContinuePartial((char*)(menu[i-2].header), APP_HEADER_LEN, 1,
                          10);
    if (i-1 >= 0 && i-1 < menu_size)
      EPD_ContinuePartial((char*)(menu[i-1].header), APP_HEADER_LEN, 2,
                          11);

    EPD_ContinuePartial(" -----", 6, 0, 12);
    if (i >= 0 && i < menu_size)
      EPD_ContinuePartial((char*)(menu[i].header), APP_HEADER_LEN, 3,
                          13);
    EPD_ContinuePartial(" -----", 6, 0, 14);

    if (i+1 >= 0 && i+1 < menu_size)
      EPD_ContinuePartial((char*)(menu[i+1].header), APP_HEADER_LEN, 2,
                          15);
    if (i+2 >= 0 && i+2 < menu_size)
      EPD_ContinuePartial((char*)(menu[i+2].header), APP_HEADER_LEN, 1,
                          16);
    if (i+3 >= 0 && i+3 < menu_size)
      EPD_ContinuePartial((char*)(menu[i+3].header), APP_HEADER_LEN, 0,
                          17);
    EPD_UpdatePartial();
  } while(key != key3);

  EPD_StopPartial();
}

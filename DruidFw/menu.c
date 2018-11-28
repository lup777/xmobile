// menu.c
#include "menu.h"

#include "global.h"
#include "kbd.h"
#include "spi.h"

#define APP_HEADER_LEN 15

void MENU_Show(App* menu) {
  int8_t i = 0;
  Key key;
  int8_t menu_size = 5;//(int8_t)((sizeof(menu) / sizeof(App)));

  _clogu8("Start menu", (uint8_t)menu_size);
  EPD_StartPartial();
  EPD_ContinuePartial("      XMobile", 13, 1, 180);
  EPD_UpdatePartial();
  EPD_StopPartial();

  do {

    key = KBD_WaiteKey();
    switch(key) {
      case key1:
        i--;
        break;
      case key7:
        i++;
        break;
      case key4:
        if (i >= 0 && i < menu_size)
          menu[i].Call();
        break;
      default:
        break;
    }

    EPD_StartPartial();
    if (i-3 >= 0 && i-3 < menu_size)
      EPD_ContinuePartial((char*)(menu[i-3].header), APP_HEADER_LEN, 0,
                          180);
    else
      EPD_ContinuePartial("               ", APP_HEADER_LEN, 0, 180);

    if (i-2 >= 0 && i-2 < menu_size)
      EPD_ContinuePartial((char*)(menu[i-2].header), APP_HEADER_LEN, 1,
                          160);
    else
      EPD_ContinuePartial("               ", APP_HEADER_LEN, 1, 160);

    if (i-1 >= 0 && i-1 < menu_size)
      EPD_ContinuePartial((char*)(menu[i-1].header), APP_HEADER_LEN, 2,
                          140);
    else
      EPD_ContinuePartial("               ", APP_HEADER_LEN, 2, 140);

    EPD_ContinuePartial(" -----", 6, 0, 120);
    if (i >= 0 && i < menu_size)
      EPD_ContinuePartial((char*)(menu[i].header), APP_HEADER_LEN, 3,
                          100);
    else
      EPD_ContinuePartial("               ", APP_HEADER_LEN, 3, 100);
    EPD_ContinuePartial(" -----", 6, 0, 80);

    if (i+1 >= 0 && i+1 < menu_size)
      EPD_ContinuePartial((char*)(menu[i+1].header), APP_HEADER_LEN, 2,
                          60);
    else
      EPD_ContinuePartial("               ", APP_HEADER_LEN, 2, 60);

    if (i+2 >= 0 && i+2 < menu_size)
      EPD_ContinuePartial((char*)(menu[i+2].header), APP_HEADER_LEN, 1,
                          40);
    else
      EPD_ContinuePartial("               ", APP_HEADER_LEN, 1, 40);

    if (i+3 >= 0 && i+3 < menu_size)
      EPD_ContinuePartial((char*)(menu[i+3].header), APP_HEADER_LEN, 0,
                          20);
    else
      EPD_ContinuePartial("               ", APP_HEADER_LEN, 0, 20);

    EPD_UpdatePartial();
    EPD_StopPartial();
  } while(key != key3);


}

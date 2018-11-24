// telephone.c

#include "telephone.h"

#include "global.h"
#include "spi.h"

void APP_Telephone(void) {
  Key key;
  char number [20] = "number: +xxxxxxxxxxx";
  _clog("Enter telephone");
  _sleep(100);

  EPD_StartPartial();
  EPD_ContinuePartial((char*)number, 20, 2, 140);
  
  uint8_t i = 0;
  for (i = 0; i < 12; i++) {
    key = APP_WaiteKey();
    if (key != keyNo) {
      number[i+9] = (char)key + '0';
      EPD_ContinuePartial((char*)number, 20, 2, 140);
    }
  }
  EPD_StopPartial();
  _clog("exit telepone\0");
}

Key APP_WaiteKey(void) {
  Key key = keyNo;
  _clog("waiting for key");
  do {
    key = KBD_Check();
  } while(key == keyNo);
  _clog("key pressed");
  return key;
}

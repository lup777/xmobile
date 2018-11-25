// telephone.c

#include "telephone.h"

#include <string.h>

#include "global.h"
#include "spi.h"

void APP_Telephone(void) {
  Key key;

  char* number = pvPortMalloc(11);
  memset(number, ' ', 11);
  if (number == NULL) {
    _clog("ERROR Malloc failed");
    return;
  }
  
  const char msg[9] = "number: +";
  _clog("Enter telephone");
  _sleep(100);

  EPD_StartPartial();
  EPD_ContinuePartial((char*)msg, 9, 2, 140);
  EPD_ContinuePartial((char*)number, 11, 2 + 9, 140);
  EPD_UpdatePartial();  
  //EPD_FlushPartial();
  
  uint8_t i = 0;
  for (i = 0; i < 12; i++) {
    key = APP_WaiteKey();
    if (key != keyNo) {
      number[i] = (char)key + '0';
      EPD_ContinuePartial((char*)msg, 9, 2, 140);
      EPD_ContinuePartial((char*)number, 11, 2 + 9, 140);
      EPD_UpdatePartial();  
      //EPD_FlushPartial();
    }
  }
  EPD_StopPartial();
  if(number)
    vPortFree(number);
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

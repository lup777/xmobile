// menu.h

#pragma once

#include "global.h"

typedef struct struct_application {
  void (*Call) (void);
  uint8_t id;
  const char* header;
} App;

void APP_MenuStart(App* menu);

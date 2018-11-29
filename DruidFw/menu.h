// menu.h

#pragma once

typedef struct struct_application {
  void (*Call) (void);
  const char* header;
} App;

void APP_MenuStart(App* menu);
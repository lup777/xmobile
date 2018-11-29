// telephone.h

#pragma once

#include "kbd.h"

typedef struct struct_menu {
  char cmd[12];
  char answer[12];
} TelMenu;

void APP_Telephone(void);
void APP_TelephoneStart(void);

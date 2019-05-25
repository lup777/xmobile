// check_box.h
#include "render.h"

#pragma once

typedef struct {
  bool value;
} CheckBox;

void checkBox_render(CheckBox* cb, short x, short y, DispBuf* pdisplay);
void checkBox_set_value(CheckBox* cb, bool value);

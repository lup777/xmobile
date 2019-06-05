// text_edit.h

#pragma once

#include "global.h"
#include "render.h"
#include "fonts.h"

typedef struct {
  byte data_len;
  byte buffer_len;
  Font font;
  char* buffer;
} TextEdit;

void textEdit_clear (TextEdit* te);
bool textEdit_init  (TextEdit* te, char* buffer, byte len, Font font);
bool textEdit_pushc (TextEdit* te, char c);
byte textEdit_setstr(TextEdit* te, char* str, byte len);
byte textEdit_setcstr(TextEdit* te, const char* str);
bool textEdit_pop   (TextEdit* te, char* c);
void textEdit_render(TextEdit* te, short x, short y, DispBuf* pdisplay);

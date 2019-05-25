// text_edit.h

#pragma once

#include "global.h"
#include "render.h"

typedef struct {
  byte data_len;
  byte buffer_len;
  char* buffer;
} TextEdit;

void textEdit_clear (TextEdit* te);
bool textEdit_init  (TextEdit* te, char* buffer, byte len);
bool textEdit_pushc (TextEdit* te, char c);
byte textEdit_setstr(TextEdit* te, char* str, byte len);
byte textEdit_setcstr(TextEdit* te, const char* str);
bool textEdit_pop   (TextEdit* te, char* c);
void textEdit_render(TextEdit* te, short x, short y, DispBuf* pdisplay);

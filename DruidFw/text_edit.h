// text_edit.h

#pragma once

#include "global.h"

typedef struct {
  byte idx;
  char* text;
  byte len;
} TextEdit;

void textEdit_clear (TextEdit* te);
bool textEdit_init  (TextEdit* te, byte len);
void textEddit_free (TextEdit* te);
bool textEdit_pushc (TextEdit* te, char c);
byte textEdit_setstr(TextEdit* te, char* str, byte len);
byte textEdit_setcstr(TextEdit* te, const char* str);
bool textEdit_pop   (TextEdit* te, char* c);
void textEdit_render(TextEdit* te, short x, short y, DispBuf* pdisplay);

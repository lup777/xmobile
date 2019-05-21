// text_edit.h

#pragma once

typedef struct {
  int8_t idx;
  char* text;
  byte len;
} TextEdit;

void textEdit_clear (TextEdit* te);
bool textEdit_init  (TextEdit* te, byte len);
void textEddit_free (TextEdit* te);
bool textEdit_pushc (TextEdit* te, char c);
bool textEdit_pop   (TextEdit* te, char* c);
void textEdit_render(TextEdit* te, short x, short y, DispBuf* pdisplay);

// text_edit.h

#pragma once

#define TEXT_EDIT_LEN 25

typedef struct {
  int8_t idx;
  char* text;
  byte len;
} TextEdit;

bool textEdit_init(TextEdit* te, byte len);
void textEddit_free(TextEdit* te);
bool textEdit_pushc(TextEdit* te, char c);
bool textEdit_pop(TextEdit* te, char* c);
void textEdit_render(TextEdit* te, short x, short y, DispBuf* pdisplay);

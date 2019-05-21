// text_edit.h

#pragma once

#define TEXT_EDIT_LEN 25

typedef struct {
  int8_t idx;
  char text[TEXT_EDIT_LEN];
} TextEdit;

bool textEdit_init(TextEdit* te);
bool textEdit_pushc(TextEdit* te, char c);
bool textEdit_pop(TextEdit* te, char* c);
void textEdit_render(TextEdit* te, short x, short y, DispBuf* pdisplay);

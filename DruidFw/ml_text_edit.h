// ml_text_edit.h
#pragma once

#include "global.h"

typedef struct {
  TextEdit* lines_arr;
  byte line_len;
  byte lines_num;
  byte line_idx;
} MlineTextEdit;

bool mlTextEdit_init(MlineTextEdit* mte, byte line_len, byte lines_num);
bool mlTextEdit_pushc(MlineTextEdit* mte, char c);
bool mlTextEdit_pushstr(MlineTextEdit* mte, char* str, byte len);
bool mlTextEdit_pushcstr(MlineTextEdit* mte, const char* str);
void mlTextEdit_render(MlineTextEdit* mte, short x, short y, DispBuf* pdisplay);

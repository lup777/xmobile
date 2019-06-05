// ml_text_edit.h
#pragma once

#include "global.h"

typedef struct {
  int8_t lines_num;
  byte   line_len;
  Font font;
  char*  buffer[7];
} MlineTextEdit;

bool mlTextEdit_init(MlineTextEdit* mte, int8_t lines_num, byte line_len, char* line1,
		     char* line2, char* line3, char* line4, char* line5, char* line6,
		     char* line7, Font font);
bool mlTextEdit_pushc(MlineTextEdit* mte, char c);
bool mlTextEdit_pushstr(MlineTextEdit* mte, char* str, byte len);
bool mlTextEdit_pushcstr(MlineTextEdit* mte, const char* str);
void mlTextEdit_render(MlineTextEdit* mte, short x, short y, DispBuf* pdisplay);

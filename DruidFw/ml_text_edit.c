// ml_text_edit.c
#include <string.h>

#include "render.h"
#include "fonts.h"
#include "ml_text_edit.h"

static void move_lines_back(MlineTextEdit* mte);

bool mlTextEdit_init(MlineTextEdit* mte, int8_t lines_num, byte line_len, char* line1,
		     char* line2, char* line3, char* line4, char* line5, char* line6,
		     char* line7, Font font) {
  CHECK(mte);

  mte->buffer[0] = line1;
  mte->buffer[1] = line2;
  mte->buffer[2] = line3;
  mte->buffer[3] = line4;
  mte->buffer[4] = line5;
  mte->buffer[5] = line6;
  mte->buffer[6] = line7;

  mte->lines_num = lines_num;

  byte i = 0;
  for (i = 0; i < lines_num; i++) {
    CHECK(mte->buffer[i]);
    memset(mte->buffer[i], ' ', mte->line_len);
  }
  mte->font = font;
  mte->line_len = line_len;
  
  return true;
}

bool mlTextEdit_pushc(MlineTextEdit* mte, char c) {
  CHECK(mte);
  (void)(c);
  
  return true;
}

bool mlTextEdit_pushcstr(MlineTextEdit* mte, const char* str) {
  return mlTextEdit_pushstr(mte, (char*)str, strlen(str));
}

bool mlTextEdit_pushstr(MlineTextEdit* mte, char* str, byte len) {
  CHECK(mte);
  CHECK(str);
  
  move_lines_back(mte);

  if (len > mte->line_len)
    len = mte->line_len;
  
  memcpy(mte->buffer[mte->lines_num - 1], str, len);

  return true;
}

static void move_lines_back(MlineTextEdit* mte) {
  CHECK(mte);
  int8_t i = 1;
  for (i = 1; i < mte->lines_num; i++) {
    memcpy(mte->buffer[i-1], mte->buffer[i], mte->line_len);
  }
  memset(mte->buffer[mte->lines_num - 1], ' ', mte->line_len);
}

void mlTextEdit_render(MlineTextEdit* mte, short x, short y, DispBuf* pdisplay) {
  CHECK(mte);
  
  int8_t i = 0;
  byte font_width = FONT_GetWidth(mte->font);
  byte font_height = FONT_GetWidth(mte->font);

  displayRenderRectangle(x, y,
			 x + (font_width * mte->line_len),
			 y + (font_height * mte->lines_num), pdisplay);

  x += 3; y += 3;
  for (i = 0; i < mte->lines_num; i++) {
    displayRenderText(x, y, mte->buffer[i], mte->line_len, mte->font, 
                      pdisplay);
    y += font_height;
    
  }
}

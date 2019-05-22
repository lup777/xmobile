// ml_text_edit.c
#include <string.h>

#include "text_edit.h"

#include "ml_text_edit.h"
#include "render.h"

void exchange_tes(TextEdit* tel, TextEdit* ter);
static void move_lines_back(MlineTextEdit* mte);

bool mlTextEdit_init(MlineTextEdit* mte, byte line_len, byte lines_num) {
  byte i = 0;
  CHECK(mte);

  { // alloc array for line pointers
    size_t size = sizeof(TextEdit*) * lines_num;
    mte->lines_num = lines_num;

    mte->lines_arr = (TextEdit*)pvPortMalloc(size);
    CHECK(mte->lines_arr);
  }

  for (i = 0; i < lines_num; i++) { // for each line
    TextEdit* te = mte->lines_arr + i;  // current line
    textEdit_init(te, line_len);    // result will be checked internally
  }

  mte->line_idx = 0;

  return true;
}

bool mlTextEdit_pushc(MlineTextEdit* mte, char c) {
  CHECK(mte);

  TextEdit* te = mte->lines_arr + (mte->lines_num - 1);
  CHECK(te);

  return textEdit_pushc(te, c);
}

bool mlTextEdit_pushcstr(MlineTextEdit* mte, const char* str) {
  return mlTextEdit_pushstr(mte, (char*)str, strlen(str));
}

bool mlTextEdit_pushstr(MlineTextEdit* mte, char* str, byte len) {
  CHECK(mte);
  CHECK(str);

  move_lines_back(mte);
  TextEdit* te = mte->lines_arr + (mte->lines_num - 1);

  bool result = textEdit_setstr(te, str, len); // set string to TE
  if (result == false)
    return false;

  return true;
}

static void move_lines_back(MlineTextEdit* mte) {
  byte i = 0;
  CHECK(mte);

  for (i = 1; i < mte->lines_num; i ++) {
    CHECK(mte->lines_arr + i);

    memcpy(mte->lines_arr + i - 1,
           mte->lines_arr + i,
           sizeof(TextEdit));
  }
  //mte->line_idx--;
}

inline void exchange_tes(TextEdit* tel, TextEdit* ter) { // exchange TextEdit instances
  CHECK(tel);
  CHECK(ter);

  TextEdit* tmp = ter;
  ter = tel;
  tel = tmp;
}

void mlTextEdit_render(MlineTextEdit* mte, short x, short y, DispBuf* pdisplay) {
  byte char_height = 15; // height of char place (to get in font info)
  byte char_width = 8; // width of char place (to get in font info)

  CHECK(mte);
  CHECK(pdisplay);

  byte i = 0;
  for (i = 0; i < mte->lines_num; i++) { // for each line
    TextEdit* te = mte->lines_arr + i;
    CHECK(te);
    textEdit_render(te, x, y + (char_height * i), pdisplay); // render line
  }
  if (mte->lines_num > 0) {
    byte len_chars = mte->lines_arr[0].len;
    displayRenderRectangle(x, y, len_chars * char_width,
                           mte->lines_num * char_height, pdisplay);
  }
}

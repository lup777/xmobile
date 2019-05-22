// ml_text_edit.c
#include "text_edit.h"

#include "ml_text_edit.h"

void exchange_tes(TextEdit* tel, TextEdit* ter);

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

  TextEdit* te = mte->lines_arr + mte->line_idx;
  CHECK(te);

  return textEdit_pushc(te, c);
}

bool mlTextEdit_pushstr(MlineTextEdit* mte, char* str, byte len) {
  CHECK(mte);
  CHECK(str);

  if (mte->line_idx >= mte->lines_num) {
    // move all lines back
  }

  TextEdit* te = mte->lines_arr + mte->line_idx;
  CHECK(te);

  bool result = textEdit_pushstr(te, str, len);
  if (result == false)
    return false;

  mte->line_idx++;
  return true;
}

bool mlTextEdit_pushcstr(MlineTextEdit* mte, const char* str) {
  CHECK(mte);
  CHECK(str);

  if (mte->line_idx >= mte->lines_num) {
    // move all lines back
  }

  TextEdit* te = mte->lines_arr + mte->line_idx;
  CHECK(te);

  bool result = textEdit_pushcstr(te, str);
  if (result == false)
    return false;

  mte->line_idx++;
  return true;
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

  CHECK(mte);
  CHECK(pdisplay);

  byte i = 0;
  for (i = 0; i < mte->lines_num; i++) { // for each line
    TextEdit* te = mte->lines_arr + i;
    CHECK(te);
    textEdit_render(te, x, y + (char_height * i), pdisplay); // render line
  }
}

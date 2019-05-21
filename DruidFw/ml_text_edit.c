// ml_text_edit.c

#include "text_edit.h"

void exchange_tes(TextEdit* tel, TextEdit* ter);

typedef struct {
  TextEdit* lines;
  byte line_len;
  byte lines_num;
  byte line_idx;
} MlineTextEdit;

bool mlTextEdit_init(MlineTextEdit* mte, byte line_len, byte lines_num) {
  if (!mte)
    return false;

  // alloc array for line pointers
  mte->lines = (TextEdit*)pvPortMalloc(sizeof(TextEdit*) * lines_num);

  if (!(mte->lines))
    return false;

  mte->lines_num = line_num;

  byte i = 0;
  for (i = 0; i < lines_num; i++) { // for each line
    //mte->lines[i].text = pvPortMalloc( line_len ); // alloc text fiels
    TextEdit* te = &(mte->lines[i]);
    if (!textEdit_init(te, line_len))
      return false;
  }
  mte->line_idx = 0;

  return true;
}

bool mlTextEdit_pushc(MlineTextEdit* mte, char c) {
  if (!mte)
    return false;

  TextEdit* te = mte->lines[line_idx];
  if (!te)
    return false;

  return textEdit_clear(te, c);
}



inline void exchange_tes(TextEdit* tel, TextEdit* ter) { // exchange TextEdit instances
  TextEdit* tmp = ter;
  ter = tel;
  tel = tmp;
}

void mlTextEdit_render(MlineTextEdit* mte, short x, short y, DispBuf* pdisplay) {
  byte char_height = 15; // height of char place (to get in font info)

  if (!mte)
    return;

  byte i = 0;
  for (i = 0; i < mte->lines_num; i++) { // for each line
    TextEdit* te = mte->lines[i];
    if (te)
      textEdit_render(te, x, y + (char_height * i), pdisplay); // render line
  }
}

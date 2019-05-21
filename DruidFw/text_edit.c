// text_edit.c

#include "render.h"

#include "text_edit.h"

bool textEdit_init(TextEdit* te, byte len) {
  if (te == NULL)
    return false;

  te->text = pvPortMalloc(len);
  if (te->text == NULL)
    return false;

  te->idx = -1;
  te->len = len;
  return true;
}

void textEddit_free(TextEdit* te) {
  if (te == NULL)
    return;

  if (te->text)
    vPortFree(te->text);

  te->idx = -1;
  te->text = NULL;
  te->len = 0;
}

bool textEdit_pushc(TextEdit* te, char c) {
  if (te == NULL)
    return false;

  if (te->idx >= TEXT_EDIT_LEN) {// if full
    textEdit_init(te);          // clear text field
  }

  if (te->idx < TEXT_EDIT_LEN) {
    te->text[ te->idx ] = c;
    te->idx ++;
    return true;
  }

  return false;
}

bool textEdit_pop(TextEdit* te, char* c) {
  if (te == NULL || c == NULL)
    return false;

  if (te->idx >= 0) {
    *c = te->text[ te->idx ];
    te->idx --;
    return true;
  }
  return false;
}

void textEdit_render(TextEdit* te, short x, short y, DispBuf* pdisplay) {
  byte char_width = 8; // width of char place (to get in font info)
  byte char_height = 15; // height of char place (to get in font info)
  displayRenderText(x, y, te->text, te->idx, pdisplay);
  displayRenderRectangle(x, y, (x + char_width) * te->idx, y + char_height, pdisplay);
}

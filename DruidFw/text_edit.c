// text_edit.c

#include "render.h"

#include "text_edit.h"

bool textEdit_init(TextEdit* te, byte len) {
  CHECK(te);

  te->text = pvPortMalloc(len);
  CHECK(te->text);

  te->idx = 0;
  te->len = len;
  return true;
}

void textEddit_free(TextEdit* te) {
  CHECK(te);

  if (te->text)
    vPortFree(te->text);

  te->idx = 0;
  te->text = NULL;
  te->len = 0;
}

void textEdit_clear(TextEdit* te) {
  te->idx = 0;
}

bool textEdit_pushc(TextEdit* te, char c) {
  CHECK(te);

  if (te->idx >= te->len) {// if full
    te->idx = 0;
  }

  if (te->idx < te->len) {
    te->text[ te->idx ] = c;
    te->idx ++;
    return true;
  }

  return false;
}

bool textEdit_pop(TextEdit* te, char* c) {
  CHECK(te);
  CHECK(c);

  if (te->idx > 0) {
    te->idx --;
    *c = te->text[ te->idx ];
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

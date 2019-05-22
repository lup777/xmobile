// text_edit.c

#include <string.h>

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
  CHECK(te->text);

  vPortFree(te->text);

  te->idx = 0;
  te->text = NULL;
  te->len = 0;
}

void textEdit_clear(TextEdit* te) {
  CHECK(te);
  te->idx = 0;
}

byte textEdit_setstr(TextEdit* te, char* str, byte len) {
  byte i = 0;
  CHECK(te);
  CHECK(str);

  for (i = 0; i < len; i++) {
    textEdit_pushc(te, str[i]);
  }
  te->idx = len;
  return i;
}

byte textEdit_setcstr(TextEdit* te, const char* str) {
  return textEdit_setstr(te, (char*)str, strlen(str));
}

bool textEdit_pushc(TextEdit* te, char c) {
  CHECK(te);
  CHECK(te->text);

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
  CHECK(te->text);

  if (te->idx > 0) {
    te->idx --;
    *c = te->text[ te->idx ];
    return true;
  }
  return false;
}

void textEdit_render(TextEdit* te, short x, short y, DispBuf* pdisplay) {
  CHECK(te);
  CHECK(te->text);
  CHECK(pdisplay);

  byte char_width = 8; // width of char place (to get in font info)
  byte char_height = 15; // height of char place (to get in font info)
  displayRenderText(x, y, te->text, te->idx, pdisplay);
  displayRenderRectangle(x, y, (x + char_width) * te->idx,
                         y + char_height, pdisplay);
}

// text_edit.c

#include <string.h>

#include "text_edit.h"
#include "fonts.h"

bool textEdit_init(TextEdit* te, char* buffer_, byte buffer_len_) {
  CHECK(te);

  //te->text = pvPortMalloc(len);
  te->buffer = buffer_;
  CHECK(te->buffer);

  te->data_len = 0;
  te->buffer_len = buffer_len_;
  return true;
}

void textEdit_clear(TextEdit* te) {
  CHECK(te);
  te->data_len = 0;
}

byte textEdit_setstr(TextEdit* te, char* str, byte len) {
  byte i = 0;
  CHECK(te);
  CHECK(str);

  for (i = 0; i < len; i++) {
    textEdit_pushc(te, str[i]);
  }
  te->data_len = len;
  return i;
}

byte textEdit_setcstr(TextEdit* te, const char* str) {
  return textEdit_setstr(te, (char*)str, strlen(str));
}

bool textEdit_pushc(TextEdit* te, char c) {
  CHECK(te);
  CHECK(te->buffer);
  
  if (te->data_len >= te->buffer_len) {// if full
    te->data_len = 0;
  }

  if (te->data_len < te->buffer_len) {
    te->buffer[ te->data_len ] = c;
    te->data_len ++;
    return true;
  }

  return false;
}

bool textEdit_pop(TextEdit* te, char* c) {
  CHECK(te);
  CHECK(c);
  CHECK(te->buffer);

  if (te->data_len > 0) {
    *c = te->buffer[ te->data_len - 1 ];
    te->data_len --;
    return true;
  }
  
  return false;
}

void textEdit_render(TextEdit* te, short x, short y, DispBuf* pdisplay) {
  CHECK(te);
  CHECK(te->buffer);
  CHECK(pdisplay);

  byte xm = X_MERGIN_PIX;
  byte ym = Y_MERGIN_PIX;

  (void)x;
  (void)y;
  if (te->data_len > 0) {
    displayRenderText(x + xm, y + ym,
		      te->buffer, te->data_len, pdisplay);
  }

  displayRenderRectangle(x, y, x + (FONT_max_width * te->buffer_len) + xm + xm,
  y + FONT_max_height + ym, pdisplay);
}

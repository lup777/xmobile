// text_edit.c

#include <string.h>

#include "text_edit.h"

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

  if (len > te->buffer_len)
    len = te->buffer_len;

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
  
  byte char_width = 8; // width of char place (to get in font info)
  byte char_height = 15; // height of char place (to get in font info)

  byte xm = X_MERGIN_PIX;
  byte ym = Y_MERGIN_PIX;
  
  if (te->data_len > 0) {
    displayRenderText(x + xm, y + ym,
		      te->buffer, te->data_len, pdisplay);
  }

  displayRenderRectangle(x, y, x + (char_width * te->data_len) + xm + xm,
                         y + char_height + ym, pdisplay);
}

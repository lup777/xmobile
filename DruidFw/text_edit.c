// text_edit.c

#include <string.h>

#include "text_edit.h"
#include "fonts.h"

bool textEdit_init(TextEdit* te, char* buffer_, byte buffer_len_, Font font) {
  CHECK(te);

  //te->text = pvPortMalloc(len);
  te->buffer = buffer_;
  CHECK(te->buffer);

  te->font = font;
  te->data_len = 0;
  te->buffer_len = buffer_len_;
  te->fixed_size = false;
  return true;
}

void textEdit_maximize(TextEdit* te) {
  if (te)
    te->fixed_size = true;
}

void textEdit_select(TextEdit* te) {
  if (te)
    te->selected = true;
}

void textEdit_deselect(TextEdit* te) {
  te->selected = false;
}

void textEdit_clear(TextEdit* te) {
  CHECK(te);
  te->data_len = 0;
}

byte textEdit_setstr(TextEdit* te, char* str, byte len) {
  textEdit_clear(te);
  byte i = 0;
  CHECK(te);
  CHECK(str);

  for (i = 0; i < len; i++) {
    textEdit_pushc(te, str[i]);
  }
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
  CHECK(te->font);

  byte xm = X_MERGIN_PIX;
  byte ym = Y_MERGIN_PIX;
  byte font_height = FONT_GetHeight(te->font);
  byte text_width = 0;
  
  if (te->data_len > 0) {
    text_width = displayRenderText(x + xm, y + ym,
		     te->buffer, te->data_len, te->font, pdisplay);
  }

  if (te->fixed_size)
    text_width = te->buffer_len * FONT_GetWidth(te->font);
  else
    text_width = te->data_len * FONT_GetWidth(te->font);
  
  uint8_t width = x + text_width + xm + xm;
  uint8_t height = y + font_height + ym + ym;
  
  displayRenderRectangle(x, y, width, height, pdisplay);
  
  if (te->selected) {
    displayRenderRectangle(x+1, y+1, width+1, height+1, pdisplay);
    displayRenderRectangle(x-1, y-1, width-1, height-1, pdisplay);
  }
}

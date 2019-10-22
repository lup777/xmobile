// text_edit.h

#pragma once

#include "global.h"
#include "render.h"
#include "fonts.h"

typedef struct {
  byte data_len;
  byte buffer_len;
  Font font;
  char* buffer;
  bool fixed_size;
  bool selected;
  bool render_rect;
} TextEdit;

void textEdit_select(TextEdit* te);
void textEdit_deselect(TextEdit* te);
void textEdit_maximize(TextEdit* te);
void textEdit_render_rect(TextEdit* te, bool render);
void textEdit_clear (TextEdit* te);
bool textEdit_init  (TextEdit* te, char* buffer, byte len, Font font);
bool textEdit_pushc (TextEdit* te, char c);
byte textEdit_setstr(TextEdit* te, char* str, byte len);
byte textEdit_setcstr(TextEdit* te, const char* str);
bool textEdit_pop   (TextEdit* te, char* c);
void textEdit_render(TextEdit* te, short x, short y, DispBuf* pdisplay);

/*TEXT_EDIT(__BUFFER_SIZE__, __HANDLE__)            \
{                                                   \
  static char __HANDLE__##buffer [__BUFFER_SIZE__]; \
  TextEdit __HANDLE__;                              \
}
*/

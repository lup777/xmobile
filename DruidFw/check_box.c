// check_box.c

#include "check_box.h"
#include "global.h"

void checkBox_render(CheckBox* cb, short x, short y, DispBuf* pdisplay) {
  CHECK(cb);

  byte xm = X_MERGIN_PIX;
  byte ym = Y_MERGIN_PIX;

  if (cb->value == true)
    displayRenderText(x + xm - 1, y + ym + 1, "*", 1, pdisplay);

  //byte char_width = 8; // width of char place (to get in font info)
  //byte char_height = 15; // height of char place (to get in font info)
  
  //displayRenderRectangle(x, y, x + char_width + xm + xm,
  //y + char_height + ym, pdisplay);
  displayRenderCircle(x + 8, y + 12, 7, pdisplay);
}

void checkBox_set_value(CheckBox* cb, bool value) {
  CHECK(cb);
  cb->value = value;
}

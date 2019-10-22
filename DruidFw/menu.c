// menu.c
#include "text_edit.h"

#include "menu.h"

#ifdef SANDER
void raw_log(char* path, u8 len) {
  for (u8 i = 0; i <= len; i++) {
    putchar(path[i]);
  }
}
#endif

void menu_init(Menu* pmenu, GetTextFptr get_text_fptr) {
  memset(pmenu->buffer, 0, pmenu->buffer_len);
  pmenu->get_text = get_text_fptr;
  pmenu->selected = 0;
  pmenu->start_line = 0;
  // TODO: Add UI elements init
}

void menu_render(Menu* pmenu, short x, short y) {
  short x0 = x;
  short y0 = y;
  i8 line_start = pmenu->selected - (pmenu->lines_num / 2);
  i8 line_end = line_start + pmenu->lines_num;
  Font font = nimbus_bold_16;

  for (i8 line_num = line_start; line_num < line_end; line_num++) {
    String str = pmenu->get_text(pmenu->line_len, line_num);

#ifdef SANDER
    if (pmenu->selected == line_num)
      _log("(%2d) -> ", line_num);
    else
      _log("(%2d)    ", line_num);

    if (str.len == 0)
      _log("------\n");
    else {
      raw_log(str.str, str.len);  _log("\n");
    }
#else
    // TODO: Fill and show UI elements

    u8 text_width = displayRenderText(x, y, str.str, str.len,
                                      nimbus_bold_16, &display);
    u8 font_height = FONT_GetHeight(font);
    
    if (pmenu->selected == line_num) {
      displayRenderRectangle(x - 1, y - 1,
                             text_width,
                             y + font_height, &display);
    }
    
    y += font_height;

#endif
  } // for

  displayRenderRectangle(x0 - 2, y0 - 1,
                         pmenu->line_len * FONT_GetWidth(font),
                         pmenu->lines_num* FONT_GetHeight(font) + y0 + 2,
                         &display);
}

void menu_prev(Menu* pmenu) {
  if (pmenu->selected > 0)
    pmenu->selected--;
}
void menu_next(Menu* pmenu) {
  pmenu->selected++;
}
void menu_enter(Menu* pmenu) {
  pmenu->enter(pmenu->selected);
}

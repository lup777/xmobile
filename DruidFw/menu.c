// menu.c
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

void menu_show(Menu* pmenu) {
  i8 line_start = pmenu->selected - (pmenu->lines_num / 2);
  i8 line_end = line_start + pmenu->lines_num;

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
    (void)(str);
#endif
  } // for
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

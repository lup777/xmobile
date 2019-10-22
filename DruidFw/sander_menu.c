// sander_menu.c
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

#include "menu.h"

char* test_str = "Hello, the is test text from provide_text function. \
It is pointer to function bla bla and so other akjfbsjkfhbksjdfbgkjzhbgkjhbfgkjsh";

String provide_text(u8 max_len, i8 entry_num) {
  u8 len = max_len;
  u8 position = entry_num * len;

  if (entry_num < 0 || position + max_len > strlen(test_str))
    return (String){"", 0};
  String str = (String){
    .str = test_str + position,
      .len = len};
  return str;
}

void call(i8 entry_num) {
  _log("CALL: %d\n", entry_num);
}

MENU(5, 20, main_menu, call);

int main(void) {
  menu_init(&main_menu, provide_text);

  menu_next(&main_menu);
  menu_show(&main_menu);
  menu_enter(&main_menu);

  return 0;
}

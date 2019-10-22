//addr_book.h

#pragma once

#include <string.h>

#include "global.h"


extern MessageBufferHandle_t addr_book_msg_buf_handle;

void addrBook_task(void* pvParameters);
void addrBook_init(void);

#define NAME_LEN 24
#define PHONE_LEN 12
#define ENTRY_FIELD_LEN 24
#define LINE_BUF_LEN 21

typedef unsigned char uint8_t;

typedef struct struct_EntryName {
  char str[NAME_LEN];
  uint8_t len;
} EntryName;

typedef struct struct_EntryPhone {
  char str[PHONE_LEN];
  uint8_t len;
} EntryPhone;

typedef struct EntryStruct {
  EntryName name;
  EntryPhone phone1;
  EntryPhone phone2;
} EntryStruct;

typedef union union_Entry {
  EntryStruct data;
  uint8_t bytes[sizeof(struct EntryStruct)];
} Entry;

#define INIT_ENTRY(ENTRY_NAME, ENTRY_PHONE1, ENTRY_PHONE2)  \
  {   .data.name.str = ENTRY_NAME,                         \
      .data.name.len = strlen(ENTRY_NAME),                 \
      .data.phone1.str = ENTRY_PHONE1,                     \
      .data.phone1.len = strlen(ENTRY_PHONE1),             \
      .data.phone2.str = ENTRY_PHONE2,                     \
      .data.phone2.len = strlen(ENTRY_PHONE2)              \
  }

#define MENU_SIZE 6

typedef struct MenuAB {
  EntryStruct* entries[MENU_SIZE];
  uint8_t menu_index;
  Entry* book;
  int8_t book_index;
} MenuAB;

#define INIT_MENU(BOOK_PTR)                     \
  { .menu_index = 0,                            \
    .book = BOOK_PTR,                           \
    .book_index = 0                             \
  }

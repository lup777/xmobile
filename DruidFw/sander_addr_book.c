// sander_addr_book.c
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "ext2.h"
#include "ext2.proto.h"

#include "addr_book.h"

#define _log printf

bool read_image(FILE** fi, u8* buffer_, long int addr, size_t size) {
  size_t i = 0;
  if (fseek(*fi, addr, SEEK_SET) != 0) {
    _log("seek 0x%08lX failed", addr);
    return false;
  }

  while (!feof(*fi) && i < size) {
    buffer_[i++] = fgetc(*fi);
    //printf("0x%02X\n", buffer[i-1]);
  }

  if (i < size) {
    _log("!! read 0x%08lX failed !!\n", addr);
    return false;
  }

  //show_hex(buffer_, addr, 0, 256);
  return true;
}


bool open_image(FILE** fi) {
  *fi = fopen("/home/alexander/tmp/image.img", "r");
  //fi = fopen("image.img", "r");

  if (fi == NULL) {
    printf("open failed\n");
    return false;
  }
  return true;
}

void send_log_str(char* path, u32 len) {
  for (u32 i = 0; i <= len; i++) {
    putchar(path[i]);
  }
}

Entry book[] = {
  INIT_ENTRY("mother", "+79213258134", "-"),
  INIT_ENTRY("futher", "+79213258134", "+79213258144"),
  INIT_ENTRY("markovka", "+79213258154", "+79213258164"),
  INIT_ENTRY("mother1", "+79213258124", "-"),
  INIT_ENTRY("futher1", "+79213258134", "+79213258144"),
  INIT_ENTRY("markovka1", "+79213258154", "+79213258164"),
  INIT_ENTRY("lup", "+79213258124", "+79213258164")
};

int main(void) {
  FILE* f = fopen("address_book.ab", "wb");
  if (f != NULL) {
    fwrite((void*)book, sizeof(book), 1, f);
    fclose(f);
    printf("write success\n");
    //return 0;
  } else {
    printf("fopen failed\n");
    return 1;
  }

  if (!ext2_init())
    return false;

  File file;
  static char buf[6000000];

  if (open_cpath("/address_book.ab", &file)) {
    file.internal_seek_address = 0;
    u32 result = read_file2(&file, buf, 12900);

    Entry* e = (Entry*)buf;
    printf("name: ");
    send_log_str(e->data.name.str, e->data.name.len);
    printf("\n");

    printf("phone1: ");
    send_log_str(e->data.phone1.str, e->data.phone1.len);
    printf("\n");

    printf("phone2: ");
    send_log_str(e->data.phone2.str, e->data.phone2.len);
    printf("\n");
  }




}

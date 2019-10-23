// sander_ext2.c
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "ext2.h"
#include "ext2.proto.h"

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

#define _log printf

int main(void) {
  if (!ext2_init())
    return false;

  File file;
  //if (open_cpath("/debut-v-echo.fb2", &file)) {
  //if (open_cpath("/lup_test_dir/druidFolderLevel2/Level3/readme.txt", &file)) {
  if (open_cpath("/frai-chuzhak.fb2", &file)) {
    _log("data:\n");

    static char buf[6000000];
    //read_file2(&file, buf, 2000);
    //u32 result = read_file2(&file, buf, 590000);
    //file.internal_seek_address = 2150718 - 7190;
    file.internal_seek_address = 0;
    u32 result = read_file2(&file, buf, 12900);
    send_log_str(buf, result); _log("\n");
    //show_inode(&file.inode);

    _log("\n--\n");
  }

  //open_cpath("/file1.txt");
  //open_cpath("/lup_test_dir/druidFolderLevel2/Level3/readme.txt");

  fclose(fi);
}

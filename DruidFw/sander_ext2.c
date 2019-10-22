// sander_ext2.c
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "fs.h"

static FILE* fi;
static ext2_dir_entry tmp_entry;

void raw_log(char* path, u32 len) {
  for (u32 i = 0; i <= len; i++) {
    putchar(path[i]);
  }
}


void show_hex(long int display_offset, u32 start, u32 num) {
  for (u32 i = start; i < start + num; i+=16 ) {
    _log ("%08lX: %02X %02X %02X %02X  %02X %02X %02X %02X  %02X %02X %02X %02X  %02X %02X %02X %02X  %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",
          display_offset + i,
          buffer[i + 0], buffer[i + 1], buffer[i + 2], buffer[i + 3], buffer[i + 4],
          buffer[i + 5], buffer[i + 6], buffer[i + 7], buffer[i + 8], buffer[i + 9],
          buffer[i + 10], buffer[i + 11], buffer[i + 12], buffer[i + 13],
          buffer[i + 14], buffer[i + 15],
          buffer[i + 0], buffer[i + 1], buffer[i + 2], buffer[i + 3], buffer[i + 4],
          buffer[i + 5], buffer[i + 6], buffer[i + 7], buffer[i + 8], buffer[i + 9],
          buffer[i + 10], buffer[i + 11], buffer[i + 12], buffer[i + 13],
          buffer[i + 14], buffer[i + 15]);
  }
}







int main(void) {
  ext2_init();

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
    raw_log(buf, result); _log("\n");
    //show_inode(&file.inode);



    _log("\n--\n");
  }

  //open_cpath("/file1.txt");
  //open_cpath("/lup_test_dir/druidFolderLevel2/Level3/readme.txt");

  fclose(fi);
}

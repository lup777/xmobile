// sander_ext2.c
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "ext2.h"
#include "ext2.proto.h"

#define _log printf

typedef unsigned int u32;

bool compare_with_ref_file(char* fname, char* buffer, int start, int count);
void calc_double_indirect_addr(u32 byte_index);

u32 min(u32 x, u32 y) {
  if (x < y)
    return x;
  return y;
}

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
  *fi = fopen("image.img", "r");
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
    //printf("%d", path[i]);
  }
}

#define _log printf

void test_fs_read(File* file, char* buf, u32 step, u32 length);
File* open_path(char* path);
  
int main(void) {

  /*calc_addr_test(1);
  calc_addr_test(8);
  calc_addr_test(20);
  _log("singly: "); calc_addr_test(11 +
                                  128);
  _log("doubly: "); calc_addr_test(11 + 255 +
                                   (255 * 215) + 2); // singly
  _log("doubly: "); calc_addr_test(11 + 255 +
                                   (255 * 2) + 215); // singly
  _log("doubly: "); calc_addr_test(11 + 255 +
                                   (255 * 102) + 101); // singly
  _log("doubly: "); calc_addr_test(11 + 255 +
                                   (255 * 202) + 201); // singly
  _log("triply: "); calc_addr_test(11 + 255 + (255 * 255) +
                                   (255 * 255 * 100) + (255 * 5) + 7); // doubly
  _log("triply: "); calc_addr_test(11 + 255 + (255 * 255) +
                                   (255 * 255 * 3) + (255 * 215) + 207); // doubly
  
                                   return 0;  */
  
  if (!ext2_init())
    return false;
  _log("ext2 inited\n");


  open_path("/");  
  

  return 0;
  
  File file;
  //if (open_cpath("/debut-v-echo.fb2", &file)) {
  //if (open_cpath("/lup_test_dir/druidFolderLevel2/Level3/readme.txt", &file)) {
  if (open_cpath("/frai-chuzhak.fb2", &file)) {
    _log("data:\n");

    _log("file inode i_block: [");
    for (int i = 0; i < 11; i++) {
      _log("%d ", file.inode.i_block[i]);
    }
    _log("%d(I) ", file.inode.i_block[12]);
    _log("%d(II)", file.inode.i_block[13]);
    _log("]\n");

    static char buf[6000000];
    test_fs_read(&file, buf, 1024, 1024);
    //send_log_str(buf, result); _log("\n");
    //show_inode(&file.inode);

    _log("\n--\n");
  } else {
    _log("open cpath failed");
  }

  //open_cpath("/file1.txt");
  //open_cpath("/lup_test_dir/druidFolderLevel2/Level3/readme.txt");

  fclose(fi);
}
/* *** test_fs_read ***
   IN:
      step - size of increase if seek address for next step
      length - how many byte need to read on each step
      buf - buffer to read
*/
void test_fs_read(File* file, char* buf, u32 step, u32 length) {
    file->internal_seek_address = 0;

    if (step < length) {
      _log("shoud be step >= length. it is needed for correctly cmp with ref file\n");
    }
    // 274432 + 1024
    for (u32 start_point = 0; start_point < file->inode.i_size;) {
      u32 r = read_file3(file, buf + start_point, length);

      /*_log("_____________________\n");
      send_log_str(buf+start_point, r); _log("\n");
      _log("^^^^^^^^^^^^^^^^^^^^^\n");*/

      if (r != length) {
        _log("TEST: read wrong amount of bytes (%d != %d) on offset 0x%08X (%d)\n",
             r, length, start_point, start_point);
        break;
      }

      
      if (false == compare_with_ref_file("frai-chuzhak.fb2", buf,
                                         0, min(start_point + length, file->inode.i_size)))
        break;

      if (r == 0)
        break;

      file->internal_seek_address -= length;
      file->internal_seek_address += step;

      start_point += step;
    }
}

bool compare_with_ref_file(char* fname, char* buffer, int start, int count) {
  // open reference file
  FILE* reff = fopen(fname, "rb");
  if (reff == NULL) {
    _log("failed to open refference file");
    return false;
  }

  if (fseek(reff, start, SEEK_SET) != 0) {
    _log("ref seek 0x%08X failed", start);
    fclose(reff);
    return false;
  }
  int i = 0;
  for (; i < count; i++) {
    //putchar(buffer[i]);
   
    char c;
    char result = fread(&c, 1, 1, reff);

    if (result != 1) {
      _log("fread failed\n");
      return false;
    }
    if (buffer[i] != c) {
      _log("\ncompare with ref file failed on offset: 0x%08X\n", i);

      fclose(reff);
      return false;
    }
    //putchar(buffer[i]);
  }
  _log("\ncompare with ref file success (0x%08X)\n", i);
  fclose(reff);
  return true;
}


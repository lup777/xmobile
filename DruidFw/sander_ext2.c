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

void sd_read_csd(uint8_t* buffer) {

}

void raw_logc(const char* str) {
  printf("%s\n", str);
}

#define _log printf



int main(void) {

  /*  calc_double_indirect_addr(1023);
  calc_double_indirect_addr(1024);
  calc_double_indirect_addr(1025);  
  calc_double_indirect_addr(1026);
  calc_double_indirect_addr(1024 * 20);
  calc_double_indirect_addr(1024 * 150);
  calc_double_indirect_addr((255 * 1024) - 4);
  calc_double_indirect_addr((255 * 1024) - 3);
  calc_double_indirect_addr((255 * 1024) - 2);
  calc_double_indirect_addr((255 * 1024) - 1);
  calc_double_indirect_addr((255 * 1024));
  calc_double_indirect_addr((255 * 1024) + 1);
  calc_double_indirect_addr((255 * 1024) + 2);
  calc_double_indirect_addr((255 * 1024) + 3);
  calc_double_indirect_addr((255 * 1024) + 4);
  calc_double_indirect_addr(255 * 1024 * 255);

  
return 0;  */
  
  if (!ext2_init())
    return false;
  _log("ext2 inited");
 
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
    //read_file2(&file, buf, 2000);
    //u32 result = read_file2(&file, buf, 590000);
    //file.internal_seek_address = 2150718 - 7190;
    file.internal_seek_address = 0;

    // max success bytes amount = 274432 (0x43000)

    u32 result = read_file3(&file, buf, 14000);
    compare_with_ref_file("frai-chuzhak.fb2", buf, 0, result);

    result += read_file3(&file, buf + result, 200000);
compare_with_ref_file("frai-chuzhak.fb2", buf, 0, result);

    result += read_file3(&file, buf + result,  0x42C00 - result + 100);
    compare_with_ref_file("frai-chuzhak.fb2", buf, 0, result);

send_log_str(buf, result); _log("\n");
    //show_inode(&file.inode);

    _log("\n--\n");
  } else {
    _log("open cpath failed");
  }

  //open_cpath("/file1.txt");
  //open_cpath("/lup_test_dir/druidFolderLevel2/Level3/readme.txt");

  fclose(fi);
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

void calc_double_indirect_addr(u32 point) {
  // direct pointers: 0 - 11
  // single idirect pointer: 12
  //            [Inode Double Indirect Pointer (13)]
  /*                           |
         [PP             P              PP]       //  0 lvl (pointers to next lvl)
          |              |              |         
     [PP  P  PP]    [PP  P  PP]     [PP  PP PP]   //  1 lvl (pointers to data blocks)
      /   |   \      /   |   \       /   |   \
    [DD] [D] [DD]  [DD] [D]  [DD]  [DD] [D]  [DD] //  2 lvl (data blocks)
  */

  u32 block_size = 1024;

  u32 blk_size_1lvl = block_size; // 1024
  u32 blk_size_2lvl = blk_size_1lvl * 255; // 261120

  // current block id on 2lvl
  u32 _2lvl_block_point = point / blk_size_2lvl; // amount of address block 3 lvl

  // current block id on 1lvl
  u32 _1lvl_buffer_point = (point % blk_size_2lvl) / blk_size_1lvl;

  // current position in data block
  u32 _0lvl_data_point = (point % blk_size_2lvl) % blk_size_1lvl;

  _log("byte 0x%8X: |##|  0lvl: %4X    |##|     1lvl: %4X     |##|     2lvl: %4X      |##|\n",
       point,
       _0lvl_data_point,
       _1lvl_buffer_point,
       _2lvl_block_point);

}

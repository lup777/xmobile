// sander_mbr.c
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "fs.h"


void show_mbr_info(Partition* p);
bool img_read(long int addr, size_t size, u8* buffer);
void show_super_block_info(ext2_super_block* sb);
bool read_mbr(u8* buffer);
bool read_sector_in_block(u32 block_group_ind, u32 block_ind, u32 sector_in_block);
void show_hex(u32 start, u32 num, u32);
void read_inode(u32 id, ext2_inode* inode, u8* grp_desc_table);
void read_iblock(ext2_inode* inode, u32 blk_num);
void get_root_dir(void);
void read_directory(void);
//u8 buffer[sizeof(Mbr)];

u8 get_start_head(Partition* p) {
  return p->start_chs[0];
}

u16 get_start_cylinder(Partition* p) {
  return ((((u16)p->start_chs[1]) && 0x0003) << 8) | (u16)(p->start_chs[2]);
}

u8 get_start_sector(Partition* p) {
  return (p->start_chs[1] >> 2) && 0x3F;
}

u8 get_end_head(Partition* p) {
  return p->end_chs[0];
}

u16 get_end_cylinder(Partition* p) {
  return ((((u16)p->end_chs[1]) && 0x0003) << 8) | (u16)(p->start_chs[2]);
}

u8 get_end_sector(Partition* p) {
  return (p->end_chs[1] >> 2) && 0x3F;
}

static u8 buffer[1024];

static FILE* fi;

// context
static u32 part_start_addr;
static u32 super_block_addr;
static u32 block_groups_number;
static u32 block_size;
static u32 blocks_per_group;
static u32 inodes_per_group;

// end of context
int main(void) {
  fi = fopen("image.img", "r");

  if (fi == NULL) {
    printf("open failed");
    return 1;
  }

  printf("sizeof MBR 0x%04lX\n", sizeof(Mbr));

  read_mbr(buffer);
  _log("MBR signature: 0x%04X\n", ((Mbr*)buffer)->mbr_signature);
  _log(" \n PART 1: ");
  show_mbr_info(&(((Mbr*)buffer)->p1));

  Mbr* mbr = (Mbr*)buffer;

  part_start_addr = ((mbr->p1.abs_start_sector + 2) * SECTOR_SIZE) - 1024;
  _log("part_start_addr = 0x%08X\n", part_start_addr);

  super_block_addr =
    ((mbr->p1.abs_start_sector + 2) * SECTOR_SIZE);
  _log("super block addr: 0x%08X\n", super_block_addr);

  {
    img_read(super_block_addr, sizeof(ext2_super_block), buffer);

    static ext2_super_block* sb = (ext2_super_block*)buffer;
    show_super_block_info(sb);
    block_size = 1024 << sb->s_log_block_size;
    blocks_per_group = sb->s_blocks_per_group;
    inodes_per_group = sb->s_inodes_per_group;

    block_groups_number = sb->s_blocks_count
      / sb->s_blocks_per_group;
    printf("block_groups_number = %d\n", block_groups_number);


    //which block group contains first non reserved inode
    u32 block_group = (FIRST_NON_RESERVERD_INOD - 1)
      / sb->s_inodes_per_group;
    printf("block_group = %d\n", block_group);

    printf("s_blocks_per_group = %d\n", sb->s_blocks_per_group);

    // inode index in block group
    u32 index = (FIRST_NON_RESERVERD_INOD - 1)
      % sb->s_inodes_per_group;
    printf("inode index = %d\n", index);

    // which block contains our inode
    u32 containing_block = (index * INODE_SIZE) /
      (1024 << sb->s_log_block_size);
    printf("containing_block = %d\n", containing_block);

    u32 inode_addr = part_start_addr
      + (containing_block * (1024 << sb->s_log_block_size))
      + ((index + 1) * INODE_SIZE);

    printf("inode_addr = 0x%08X\n", inode_addr);

    _log("s_inodes_per_group = %d\n", sb->s_inodes_per_group);
    u32 inodes_per_block = sb->s_inodes_per_group / sb->s_blocks_per_group;
    printf("inodes_per_block = %d\n", inodes_per_block);
    _log("mount point: %s\n", sb->s_last_munted);

    _log("inodes count: %d\n", sb->s_inodes_per_group * sb->s_blocks_per_group);
  }
  // https://wiki.osdev.org/Ext2

  // read block group descriptor table
  read_sector_in_block(0, 2, 0);
  ext2_group_desc_table* gt = (ext2_group_desc_table*)buffer;
  _log("bg_inode_table = %d\n", gt->bg_inode_table);

  u32 bg_inode_table = gt->bg_inode_table;
  u32 bg_inode_bitmap = gt->bg_inode_bitmap;

  // read inode bitmap
  read_sector_in_block(0, bg_inode_bitmap, 0);
  //show_hex(0, 512, 0);

  // read inode table
  read_sector_in_block(0, bg_inode_table, 0);
  ext2_inode* in = (ext2_inode*)buffer;

  for (u16 i = 11; i < 14; i++) {
    _log("INODE %d", i);
    _log("  i_mode = 0x%04X\n", in->i_mode);
    //show_hex(i * INODE_SIZE, INODE_SIZE, 0);
  }

  get_root_dir();
  
  fclose(fi);
  return 0;
}

void read_iblock(ext2_inode* inode, u32 blk_num) {
  // data block number
  u32 pos = inode->i_block[0] * block_size;
  _log("iblock pos = %d (0x%08X)\n", pos, pos);
  read_sector_in_block(0, inode->i_block[0], 0);
}

void get_root_dir(void) {
  
  {
    static ext2_inode inode;

    read_inode(2, &inode, NULL);
    _log("root i_mode = 0x%04X\n", inode.i_mode);
    _log("root i_size = 0x%04X\n", inode.i_size);
    _log("root i_blocks = 0x%04X\n", inode.i_blocks);
    _log("root i_faddr = 0x%04X\n", inode.i_faddr);

    if (inode.i_mode & 0x4000)
      _log("it is directory\n ");

      read_iblock(&inode, 0); // in buffer
  }

  read_directory();
}

void read_directory(void) {
  ext2_dir_entry* e =  (ext2_dir_entry*)buffer;
  u16 offset = 0;

  for (u8 i = 0; offset < block_size ; i ++) {
    _log("%2d | %4d | name: %s\n",
	 e->inode, e->entry_size, e->name);
    //e = (ext2_dir_entry*)((u8*)e + e->entry_size);
    offset += e->entry_size;
    e = (ext2_dir_entry*)((u8*)buffer + offset);
  }

}


// if grp_desc_table is NULL -> read it from SD
// else it allready in buffer
void read_inode(u32 id, ext2_inode* inode, u8* grp_desc_table) {
  _log("====== read inode %d ========\n", id);
  u32 group = (id - 1) / inodes_per_group;
  _log("group = %d\n", group);
  // read group descriptors table
  if (grp_desc_table == NULL)
    read_sector_in_block(0, 2, 0);
  grp_desc gd;
  memcpy((u8*)&gd, buffer + (group * sizeof(grp_desc)),
	 sizeof(grp_desc));
  // calc indode index in inode grp
  __u32 index = (id - 1) % inodes_per_group;
  __u32 addr = (gd.bg_inode_table * block_size)
    + (index * INODE_SIZE);

  //part_start_addr
  read_sector_in_block(0, gd.bg_inode_table, 0);
  u32 pos = index * INODE_SIZE;
  _log("inode addr offet (pos) 0x%08X\n", pos);

  memcpy(inode, buffer + pos, INODE_SIZE);
  show_hex(pos, INODE_SIZE, pos);
  
  _log("gd.bg_inode_table block= %d\n", gd.bg_inode_table);
  _log("inode index = %d\n", index);
  _log("inodex addr = 0x%08X\n", addr);
  _log("====== ============ ========\n");
}



void show_hex(u32 start, u32 num, u32 display_offset) {

  for (u32 i = start; i < start + num; i+=16 ) {
    _log ("%08X: %02X %02X %02X %02X  %02X %02X %02X %02X  %02X %02X %02X %02X  %02X %02X %02X %02X\n",
          display_offset + i,
          buffer[i + 0], buffer[i + 1], buffer[i + 2], buffer[i + 3], buffer[i + 4],
          buffer[i + 5], buffer[i + 6], buffer[i + 7], buffer[i + 8], buffer[i + 9],
          buffer[i + 10], buffer[i + 11], buffer[i + 12], buffer[i + 13],
          buffer[i + 14], buffer[i + 15]);
  }
}

bool read_sector_in_block(u32 block_group_ind, u32 block_ind, u32 sector_in_block) {
  u32 addr = part_start_addr
    + (block_group_ind * blocks_per_group * block_size)
    + (block_ind * block_size)
    + (sector_in_block * SECTOR_SIZE);

  _log("read_sector_in_block adr: 0x%08X\n", addr);
  return img_read(addr, SECTOR_SIZE, buffer);
}

bool read_mbr(u8* buffer) {
  return img_read(0, 512, buffer);
}

bool img_read(long int addr, size_t size, u8* buffer) {
  int result = fseek(fi, addr, SEEK_SET);
  int i = 0;

  if (result != 0) {
    _log("seek failed");
  }

  while (!feof(fi) && i < size) {
    buffer[i++] = fgetc(fi);
    //printf("0x%02X\n", buffer[i-1]);
  }

  if (i < size) {
    _log("!! read failed !!");
    return false;
  }
  return true;
}

void show_super_block_info(ext2_super_block* sb) {
  printf("s_inodes_count = %d\n", sb->s_inodes_count);
  printf("s_blocks_count = %d\n", sb->s_blocks_count);
  printf("s_free_blocks_count = %d\n", sb->s_free_blocks_count);
  printf("s_first_data_block = %d\n", sb->s_first_data_block);
  printf("s_rev_level = %d\n", sb->s_rev_level);
  printf("s_log_block_size = %d\n", 1024 << sb->s_log_block_size);
  printf("s_log_frag_size = %d\n", 1024 << sb->s_log_frag_size);
}

void show_mbr_info(Partition* p) {
  _log("PART is_active: 0x%02X\n", p->is_active);
  _log("PART start_head 0x%02X\n", get_start_head(p));
  _log("PART start_sector 0x%02X\n", get_start_sector(p));
  _log("PART start_cylinder 0x%04X\n", get_start_cylinder(p));
  _log("PART part_type 0x%02X\n", p->part_type);
  _log("PART end_head 0x%02X\n", get_end_head(p));
  _log("PART end_sector 0x%02X\n", get_start_sector(p));
  _log("PART end_cylinder 0x%04X\n", get_start_cylinder(p));
  _log("PART start_abs_sector 0x%02X%02X%02X%02X\n",
       *((u8*)(&p->abs_start_sector) + 3),
       *((u8*)(&p->abs_start_sector) + 2),
       *((u8*)(&p->abs_start_sector) + 1),
       *((u8*)(&p->abs_start_sector)));
  _log("PART sectors_in_part 0x%02X%02X%02X%02X\n\n",
       *((u8*)(&p->sectors_in_part)+3),
       *((u8*)(&p->sectors_in_part)+2),
       *((u8*)(&p->sectors_in_part)+1),
       *((u8*)(&p->sectors_in_part)));

}

// C - 0x100
// H - 0x20
// S - 0x01

// TH - 0xBE
// TS - 0x01

// (C * TH * TS) + (H * TS) + (S - 1) = LBA
// (100 * BE * 1) + (20 * 1) + (1 - 1) = BE00 + 20 = BE20 LBA

// https://thestarman.pcministry.com/asm/mbr/PartTables.htm

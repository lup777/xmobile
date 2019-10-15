// sander_ext2.c
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "fs.h"

static FILE* fi;
static u8 buffer[1024]; // block size
static ext2_inode iroot;
static ext2_dir_entry tmp_entry;

void raw_log(char* path, u8 len) {
  for (u8 i = 0; i < len; i++) {
    putchar(path[i]);
  }
}

bool open_image(void) {
  fi = fopen("/home/alexander/tmp/image.img", "r");

  if (fi == NULL) {
    printf("open failed");
    return false;
  }
  return true;
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

bool read_image(long int addr, size_t size) {
  size_t i = 0;
  if (fseek(fi, addr, SEEK_SET) != 0) {
    _log("seek 0x%08lX failed", addr);
    return false;
  }

  while (!feof(fi) && i < size) {
    buffer[i++] = fgetc(fi);
    //printf("0x%02X\n", buffer[i-1]);
  }

  if (i < size) {
    _log("!! read 0x%08lX failed !!\n", addr);
    return false;
  }

  //show_hex(addr, 0, /*size*/256);
  return true;
}

static u32 part_start_addr = 0;
static u16 block_size = 1024;
static u32 blocks_per_group = 0;
static u32 inodes_per_group = 0;
static u32 inode_table_block = 0;

bool read_sector(u32 sector_num) {
  if (read_image(sector_num * SECTOR_SIZE, SECTOR_SIZE))
    return true;

  _log("read_sector: failed 0x%04x%04x",
       (u16)sector_num, (u16)(sector_num >> 16));
  return false;
}

bool read_block(u32 block_num) { // block num related to partition start
  if (read_image(block_num * block_size, block_size))
    return true;

  _log("read_block: failed 0x%04X%04X", (u16)block_num,
       (u16)(block_num >> 16));
  return false;
}

void parse_mbr(void) {
  Mbr* mbr = (Mbr*)buffer;

  part_start_addr = mbr->p1.abs_start_sector * SECTOR_SIZE;
}

#define MBR_SECTOR 0
#define PART_START_BLOCK (part_start_addr / block_size)
#define SUPER_BLOCK_NUM (PART_START_BLOCK + 1)
#define GROUP_DESCR_TABLE_BLOCK (SUPER_BLOCK_NUM + 1)

void parse_super_block(void) {
  static ext2_super_block* sb = (ext2_super_block*)buffer;
  block_size = 1024 << sb->s_log_block_size;
  blocks_per_group = sb->s_blocks_per_group;
  inodes_per_group = sb->s_inodes_per_group;
  _log("----------------- super block info ----------------------\n");
  _log("blk size: %d | blocks_per_group %d | inodes_per_group %d\n",
       block_size, blocks_per_group, inodes_per_group);
  _log("---------------------------------------------------------\n");
}

void parse_grp_descr_table(void) {
  ext2_group_desc_table* gt = (ext2_group_desc_table*)buffer;
  _log("----------------- grp descr table info ----------------------\n");
  inode_table_block = gt->bg_inode_table;
  _log("inode table block = %d\n", inode_table_block);
  _log("-------------------------------------------------------------\n");
}

u32 get_inode_table_block_for_group(u32 group) {
  //_log("get_inode_table_block_for_group (%d)>>>\n", group);
  if (group * sizeof(ext2_group_desc_table) > block_size) {
    _log("get_inode_table_block_for_group: invalid group\n");
    return 0;
  }
  // read group descriptor table
  read_block(GROUP_DESCR_TABLE_BLOCK);

  ext2_group_desc_table* gt = (ext2_group_desc_table*)buffer;

  gt += group;
  /*_log("get_inode_table_block_for_group: bg_block_bitmap = %d\n",
       gt->bg_block_bitmap);
  _log("get_inode_table_block_for_group: bg_inode_bitmap = %d\n",
       gt->bg_inode_bitmap);
  _log("get_inode_table_block_for_group: g_inode_table  = %d\n",
       gt->bg_inode_table);*/

  return gt->bg_inode_table;
}

#define ROOT_INODE 2
#define ROOT_GROUP 0

bool is_dir(ext2_inode* pinode) {
  return (pinode->i_mode & 0x4000) != 0;
}

void show_inode(ext2_inode* inode) {
  _log("-------------- inode -------------\n");
  _log("i_mode 0x%04X | size 0x%08X | blocks %d\n",
       inode->i_mode, inode->i_size, inode->i_blocks);
  if (is_dir(inode))
    _log("directory\n");
  else
    _log("file\n");
  _log("----------------------------------\n");
}

bool read_inode(ext2_inode* pinode, u32 inode_num) {
  _log("read_inode >>> ");
  u16 group = (inode_num - 1) / inodes_per_group;
  u16 inode = (inode_num - 1) - (group * inodes_per_group);

  _log("| group: %d | ", group);
  _log("inode: %4d | \n", inode);
  u32 inode_table_block = get_inode_table_block_for_group(group);

  u8 inodes_per_block = block_size / INODE_SIZE;
  u16 inode_table_block_offset = inode / inodes_per_block;
  inode -= (inode_table_block_offset * inodes_per_block);

  // read inode table
  u32 block = inode_table_block + PART_START_BLOCK +
                                  inode_table_block_offset;
  _log("               read_inode: inode table block %d | \n",
       block);

  if (true != read_block(block))
    return false;

  ext2_inode* source = (ext2_inode*)buffer;
  source += inode;

  memcpy(pinode, source, sizeof(ext2_inode));
  return true;
}

bool get_directory_entry(ext2_inode* pinode, u32 entry_num,
                         ext2_dir_entry* pentry_out) {
  //_log("get_directory_entry >>>\n");
  bool result = true;

#if 1
  static u8 local_buf[1024];
  ext2_dir_entry* pentry = (ext2_dir_entry*)local_buf;
  memcpy(local_buf, buffer, 1024);
#else
  ext2_dir_entry* pentry = (ext2_dir_entry*)buffer;
#endif

  for (u8 iblock_id = 0; iblock_id < 12; iblock_id++) { // direct block pointers
    if (pinode->i_block[iblock_id] == 0) {
      _log("error. inode i_block = 0; return");
      return false;
    }

    // why -2?
    if (!read_block(pinode->i_block[iblock_id] + PART_START_BLOCK))
      return false;

    u32 offset = 0;

    for (u32 i = 0; offset < block_size; i++, offset += pentry->entry_size) {
      pentry = (ext2_dir_entry*)(buffer + offset);
      //_log("entry: %s\n", pentry->name);
      if (i == entry_num) {
        //_log("found entry: %s\n", pentry->name);
        memcpy(pentry_out, pentry, sizeof(ext2_dir_entry));
        return true;
      }
    } // for offset
  } // for iblock_id
  return false;
}

u8 u8min(u8 first, u8 second) {
  if(first < second)
    return first;
  return second;
}

bool get_inode_child_by_name(ext2_inode* parent, char* name,
                             u8 len, ext2_dir_entry* entry_out) {
  _log("get_inode_child_by_name >>> ");
  raw_log(name, len);
  static ext2_dir_entry entry;
  u16 i = 0;

  while(get_directory_entry(parent, i++, &entry) == true) {
    //_log("entry: "); raw_log(entry.name, entry.name_len); _log("\n");
    if (0 == memcmp(name, entry.name,
                    u8min(entry.name_len, len))) {
      memcpy(entry_out, &entry, sizeof(ext2_dir_entry));
      _log(" -- found! | ");
      _log("entry name: | "); raw_log(entry.name, entry.name_len);
      _log(" | entry inode: %d | ", entry.inode);
      _log("entry entry size: %d |\n", entry.entry_size);
      return true;
    }
  }
  _log("-- %s not found\n", name);
  return false;
}

bool get_inode_child_by_cname(ext2_inode* parent, const char* name,
                              ext2_dir_entry* entry_out) {
  return get_inode_child_by_name(parent, (char*)name, strlen(name), entry_out);
}

bool get_entry_child_by_name(ext2_dir_entry* parent, char* name,
                             u8 name_len, ext2_dir_entry* child) {
  ext2_dir_entry tmp_out;
  _log("get_entry_child_by_name >>> ");
  raw_log(name, name_len); _log("\n");
  static ext2_inode inode; // TODO: use buffer for this

  _log("### inode %d\n", parent->inode);
  if(true != read_inode(&inode, parent->inode)) {
    _log("get_entry_child_by_name: ");
    raw_log(name, name_len);
    _log(" read_inode failed\n");
    return false;
  }

  show_inode(&inode);

  if (true != is_dir(&inode)) {
    _log("it is not directory\n");
    return false;
  }
  return get_inode_child_by_name(&inode, name, name_len, child);
}

bool get_entry_child_by_cname(ext2_dir_entry* parent, const char* name,
                              ext2_dir_entry* child) {
  return get_entry_child_by_name(parent, (char*)name,
                                 strlen(name), child);
}

entry_type get_entry_type(ext2_dir_entry* e) {
  switch((entry_type)e->enum_type) {
    case fifo:
    case character_device:
    case directory:
    case block_device:
    case file:
    case symbolic_link:
    case unix_socket:
      return (entry_type)e->enum_type;
    default:
      break;
  }
  return unkown;
}

void show_dir_entry(ext2_dir_entry* e) {
  //_log("show_dir_entry >>>\n");
  static ext2_inode inode;  // TODO: use buffer for this
  read_inode(&inode, e->inode);

  _log("-------- dir entry ---------------\n");
  _log("name: ");
  raw_log(e->name, e->name_len);
  _log(" | type: %s | mode: 0x%04X (0x%02X) | inode %d | size: %d\n",
       is_dir(&inode) ? "directory" : "file", inode.i_mode,  e->enum_type,
       e->inode, e->entry_size);
  _log("----------------------------------\n");
}

bool ext2_init() {
  if (!open_image())
    return false;

  // read MBR
  if (!read_sector(0))
    return false;
  parse_mbr();

  // read Super Block
  if (!read_block(SUPER_BLOCK_NUM))
    return false;
  parse_super_block();

  // read root inode
  if (!read_inode(&iroot, ROOT_INODE)) // 2
      return false;
  //show_inode(&iroot);
  return true;
}

bool open_file(char* name, size_t name_len, ext2_dir_entry* parent_entry) {
  static ext2_dir_entry e;
  // read file
  if (parent_entry != NULL) {
    if (!get_entry_child_by_name(parent_entry, name, name_len, &e))
      return false;
  } else {
    if (!get_inode_child_by_name(&iroot, name, name_len, &e))
      return false;
  }

  /*if (get_entry_type(&e) != file) {
    show_dir_entry(&e);
    _log("it is not regular file\n");
    //return false;
  }*/




  static ext2_inode i;
  if (!read_inode(&i, e.inode))
    return false;
  show_inode(&i);

  _log("file content: (%d), size: %d bytes\n", i.i_block[0], i.i_size);
  if (!read_block(i.i_block[0] + PART_START_BLOCK))
    return false;

  raw_log((char*)buffer, i.i_size);
  return true;
}

bool open_cpath(const char* path) {
  _log("open_cfile: %s\n", path);
  size_t str_len = strlen(path);
  bool once_happend = false;

  if (path[0] != '/') {
    _log("path should start from //");
    return false;
  }

  size_t start = 0; // position of first / char
  size_t end = start; // position of next / char

  for(; end < str_len; end++) {
    if (path[end] == '/') {
      if (end - start > 1) {// at leas 1 char /x/
        _log("entry: ");
        raw_log((char*)(path + start + 1), end - start - 1); _log("\n");

        if (!once_happend) {
          if (!get_inode_child_by_name(&iroot, (char*)(path + start + 1),
                                       end - start - 1, &tmp_entry))
            return false;

          once_happend = true;
        } else {
          if (!get_entry_child_by_name(&tmp_entry,
                                      (char*)(path + start + 1),
                                      end - start - 1, &tmp_entry))
            return false;
        } // } else {
        start = end;
      } // if !once_happend
    } // end - start > 1
  } // for

  if (end - start > 1) {
    _log("last entry: ");
    raw_log((char*)(path + start + 1), end - start);  _log("\n");

    ext2_dir_entry* parent_entry = NULL;
    if (once_happend)
      parent_entry = &tmp_entry;

    if (!open_file((char*)(path + start + 1), end - start, parent_entry))
      return false;
  } else {
    _log("file not found\n");
    return false;
  }

  return true;
}

int main(void) {

  ext2_init();

  //open_cpath("/frai-chuzhak.fb2");
  open_cpath("/file1.txt");
  //open_cpath("/lup_test_dir/druidFolderLevel2/Level3/readme.txt");

  fclose(fi);
}
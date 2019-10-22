// ext2.proto.h
#pragma once

#ifdef SANDER
bool read_image(long int addr, size_t size);
bool open_image(void);
#endif

bool read_sector(u32 sector_num);
bool read_block(u32 block_num);
void parse_mbr(void);
void parse_super_block(void);
void parse_grp_descr_table(void);
u32 get_inode_table_block_for_group(u32 group);
bool is_dir(ext2_inode* pinode);
void show_inode(ext2_inode* inode);
bool read_inode(ext2_inode* pinode, u32 inode_num);
bool get_directory_entry(ext2_inode* pinode, u32 entry_num,
                         ext2_dir_entry* pentry_out);
u32 umin(u32 first, u32 second);
bool get_inode_child_by_name(ext2_inode* parent, char* name,
                             u8 len, ext2_dir_entry* entry_out);
bool get_inode_child_by_cname(ext2_inode* parent, const char* name,
                              ext2_dir_entry* entry_out);
bool get_entry_child_by_name(ext2_dir_entry* in_out, char* name, u8 name_len);
bool get_entry_child_by_cname(ext2_dir_entry* in_out, const char* name);
inode_type get_inode_type(ext2_inode* e);
entry_type get_entry_type(ext2_dir_entry* e);
void show_dir_entry(ext2_dir_entry* e);
bool open_file(char* name, size_t name_len, File* file);
u32 read_block_of_data_blocks(u32 root_block_id, char* out, u32 offset, u32 out_len);


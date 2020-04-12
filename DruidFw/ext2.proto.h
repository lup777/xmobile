// ext2.proto.h
#pragma once

#ifdef SANDER
bool read_image(FILE** fi, u8* buffer, long int addr, size_t size);
bool open_image(FILE** fi);
void send_log_str(char* path, u32 len);
extern FILE* fi;
#endif

void show_hex(u8* buffer_, long int display_offset, u32 start, u32 num);
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
bool open_file(u32 inode, File* file);
u32 read_block_of_data_blocks(u32 root_block_id, char* out, u32 offset, u32 out_len);
u16 read_data_block_by_id(u32 block_id, u16 block_offset, char* out, u32 copy_len);
u32 read_direct_data_blocks(File* file,
                            u32 data_block_serial_number,
                            u16 first_data_block_offset,
                            char* out,
                            u32 out_len);
u32 read_singly_indirect_data_blocks(File* file,
                                     u32 data_block_serial_number,
                                     u16 first_data_block_offset,
                                     char* out,
                                     u32 out_len);
u32 get_indirect_subblock_id(u32 block_id, u16 index);
u32 read_doubly_indirect_data_blocks(File* file,
                                     u32 data_block_serial_number,
                                     u16 data_block_offset,
                                     char* out,
                                     u32 out_len);

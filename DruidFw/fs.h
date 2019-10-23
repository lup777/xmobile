// fs.h
#pragma once
#ifdef SANDER
typedef unsigned char uint8_t;
typedef unsigned short int uint16_t;
typedef unsigned int uint32_t;

typedef signed char int8_t;
typedef signed short int int16_t;
typedef signed int int32_t;
#else
#include "global.h"
#endif
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;

typedef uint32_t __u32;
typedef uint32_t __le32;
typedef uint16_t __le16;
typedef uint16_t __u16;
typedef int32_t __s32;
typedef int16_t __s16;
typedef uint8_t __u8;

#define EXT2_NDIR_BLOCKS 12

#define EXT2_IND_BLOCK     EXT2_NDIR_BLOCKS

#define EXT2_DIND_BLOCK (EXT2_IND_BLOCK + 1)

#define EXT2_TIND_BLOCK (EXT2_DIND_BLOCK + 1)

#define EXT2_N_BLOCKS   (EXT2_TIND_BLOCK + 1)

typedef struct ext2_super_block {
  __u32   s_inodes_count;        /*  Количество индексных дескрипторов в ФС */
  __u32   s_blocks_count;        /*  Количество блоков в ФС */
  __u32   s_r_blocks_count;      /*  Количество зарезервированых блоков */
  __u32   s_free_blocks_count;   /*  Количество свободных блоков */
  __u32   s_free_inodes_count;   /*  Количество свободных индексных дескрипторов */
  __u32   s_first_data_block;    /*  Номер данного блока */
  __u32   s_log_block_size;      /*  log2(размер блока)-10 */
  __s32   s_log_frag_size;       /*  log2(размер фрагмента)-10 */
  __u32   s_blocks_per_group;    /*  #  Кол-во блоков в группе */
  __u32   s_frags_per_group;     /*  #  Кол-во фрагментов в группе */
  __u32   s_inodes_per_group;    /*  #  Кол-во индексных дескрипторов в группе */
  __u32   s_mtime;               /*  Время последнего монтирования в POSIX времени */
  __u32   s_wtime;               /*  Время последней записи в POSIX времени */
  __u16   s_mnt_count;
  __s16   s_max_mnt_count;
  __u16   s_magic;
  __u16   s_state;
  __u16   s_errors;              /*  Код ошибки(см.ниже) */
  __u16   s_pad;
  __u32   s_lastcheck;           /*  POSIX время последней проверки */
  __u32   s_checkinterval;       /*  POSIX время между принудительными проверками */
  __u32   s_creator_os;          /*  ID ОС (см. ниже)  */
  __u32   s_rev_level;           /*  Версия */
  __u16   s_def_resuid;          /*  UserID, могущий использовать зар. блоки */
  __u16   s_def_resgid;          /*  GroupID, могущий использовать зар. блоки */
  __u32   s_first_ino;
  __u16   s_inode_size;
  __u16   s_block_group_nr;
  __u32   s_feature_compat;
  __u32   s_feature_incompat;
  __u32   s_feature_ro_compat;
  __u8    s_uuid[16];
  __u8    s_volume_name[16];
  char    s_last_munted[64];
  __u32   s_algo_bitmap;
  __u32   s_reserved[67];       /*  Зарезервировано */
} ext2_super_block;

#ifdef SANDER
#  pragma pack(push,1)
#endif
typedef struct Partition {
  u8 is_active; // 00h
  u8 start_chs[3]; // head, sector and cylinder 01h..03h
  u8 part_type; // 04h
  u8 end_chs[3]; // end head, sector, cylinder 05h ..07h
  u32 abs_start_sector; // 08h..0Bh (LBA)
  u32 sectors_in_part; // 0Ch..0Fh (num of sectors in part LBA)
} Partition;

typedef struct Mbr {
  u8 code[139];        // 0000..008A
  u8 err_msgs[80];     // 008B..00DA
  u8 padding[227];     // 00DB..01BD    zeros (or NT drive serial number)
  union {
    u8 part_table[64];   // 01BE..01FD
    struct {
      struct Partition p1;
      struct Partition p2;
      struct Partition p3;
      struct Partition p4;
    };
  };
  u16 mbr_signature; // 01FE..01FF    0xAA55h [55, AA]
} Mbr;

typedef struct ext2_inode {
  __le16	i_mode;		/* File mode */
  __le16	i_uid;		/* Low 16 bits of Owner Uid */
  __le32	i_size;		/* Size in bytes */
  __le32	i_atime;	/* Access time */
  __le32	i_ctime;	/* Creation time */
  __le32	i_mtime;	/* Modification time */
  __le32	i_dtime;	/* Deletion Time */
  __le16	i_gid;		/* Low 16 bits of Group Id */
  __le16	i_links_count;	/* Links count */
  __le32	i_blocks;	/* Blocks count */
  __le32	i_flags;	/* File flags */
  union {
    struct {
      __le32  l_i_reserved1;
    } linux1;
    struct {
      __le32  h_i_translator;
    } hurd1;
    struct {
      __le32  m_i_reserved1;
    } masix1;
  } osd1;				/* OS dependent 1 */
  __le32	i_block[EXT2_N_BLOCKS];/* Pointers to blocks */
  __le32	i_generation;	/* File version (for NFS) */
  __le32	i_file_acl;	/* File ACL */
  __le32	i_dir_acl;	/* Directory ACL */
  __le32	i_faddr;	/* Fragment address */
  union {
    struct {
      __u8	l_i_frag;	/* Fragment number */
      __u8	l_i_fsize;	/* Fragment size */
      __u16	i_pad1;
      __le16	l_i_uid_high;	/* these 2 fields    */
      __le16	l_i_gid_high;	/* were reserved2[0] */
      __u32	l_i_reserved2;
    } linux2;
    struct {
      __u8	h_i_frag;	/* Fragment number */
      __u8	h_i_fsize;	/* Fragment size */
      __le16	h_i_mode_high;
      __le16	h_i_uid_high;
      __le16	h_i_gid_high;
      __u32	h_i_author;
    } hurd2;
    struct {
      __u8	m_i_frag;	/* Fragment number */
      __u8	m_i_fsize;	/* Fragment size */
      __u16	m_pad1;
      __u32	m_i_reserved2[2];
    } masix2;
  } osd2;				/* OS dependent 2 */
} ext2_inode;

typedef struct ext2_group_desc_table {
  u32 bg_block_bitmap; // block id of the first block of the block bitmap in cur group
  u32 bg_inode_bitmap; // block id of the first block of the inode bitmap
  u32 bg_inode_table;
  u16 bg_free_blocks_count;
  u16 bg_free_inodes_count;
  u16 bg_used_dirs_count;
  u16 bg_pad;
  u8  bg_reerved[12];
} ext2_group_desc_table;

typedef struct grp_desc {
  __u32 bg_block_bitmap;
  __u32 bg_inode_bitmap;
  __u32 bg_inode_table;
} grp_desc;

typedef struct ext2_dir_entry {
  union {
    struct {
    __u32 inode;
    __u16 entry_size;
    __u8 name_len;
    __u8 enum_type;
    char name[];
    };
    __u8* b[0x80];
  };
} ext2_dir_entry;
#ifdef SANDER
#  pragma pack(pop)
#endif

#define ROOT_INODE_INDEX 2
#define SECTOR_SIZE 512
#define INODE_SIZE 128
#define FIRST_NON_RESERVERD_INOD 11
#define DIRECT_BLOCK_POINTERS_NUM 12
#define SINGLE_INDERECT_BLOCK_ID 12
#define DOUBLY_INDERECT_BLOCK_ID 13

#define INVALID_BLOCK_POINT 0xFF

typedef struct File {
  ext2_dir_entry entry;
  ext2_inode inode;
  u32 first_inderect_block_point;
  u32 block_point;
  u32 buffer_point;
  u32 internal_seek_address;
} File;

typedef enum inode_type {
  ififo = 0x1000,
  icharacter_device = 0x2000,
  idirectory = 0x4000,
  iblock_device = 0x6000,
  ifile = 0x8000,
  isymbolic_link = 0xA000,
  iunix_socket = 0xC000,
  iunkown,
} inode_type;

typedef enum entry_type {
  eunknown = 0,
  efile = 1,
  edirectory = 2,
  echaracter_device = 3,
  eblock_device = 4,
  efifo = 5,
  esocket = 6,
  esymbolic_link = 7,
} entry_type;

//bool open_root(File* file);
//enum_fs();

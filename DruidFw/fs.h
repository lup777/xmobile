// fs.h

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
  __u16   s_errors;              /*  Код ошибки(см.ниже) */
  __u16   s_pad;
  __u32   s_lastcheck;           /*  POSIX время последней проверки */
  __u32   s_checkinterval;       /*  POSIX время между принудительными проверками */
  __u32   s_creator_os;          /*  ID ОС (см. ниже)  */
  __u32   s_rev_level;           /*  Версия */
  __u16   s_def_resuid;          /*  UserID, могущий использовать зар. блоки */
  __u16   s_def_resgid;          /*  GroupID, могущий использовать зар. блоки */
  __u32   s_reserved[235];       /*  Зарезервировано */
} ext2_super_block;

#define _log printf

#pragma pack(push,1)
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
#pragma pack(pop)

#define SECTOR_SIZE 512
#define INODE_SIZE 128
#define FIRST_NON_RESERVERD_INOD 11

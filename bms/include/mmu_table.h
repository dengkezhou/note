#ifndef __MMU_TABLE_H__
#define __MMU_TABLE_H__

#include <common.h>

typedef enum {
  MT_VAILD = 1 << 0,

  MT_R = 1 << 1,
  MT_W = 1 << 2,
  MT_X = 1 << 3,

  MT_USER_ACCESS  = 1 << 4,
  MT_THREAD_SHARE = 1 << 5,
  MT_ACCESS       = 1 << 6,
  MT_DIRTY        = 1 << 7,
  MT_THREAD_FULL  = 0xff,
  MT_THREAD_MASK  = 0xff,

  //MT_TRUSTABLE    = 1UL << 59,
  //MT_SHAREABLE    = 1UL << 60,
  //MT_BUFFERABLE   = 1UL << 61,
  //MT_CACHEABLE    = 1UL << 62,
  //MT_STRONG_ORDER = 1UL << 63,
  //MT_FLAGS_MASK   = 0x1fUL << 59,
	MT_MEMORY				= MT_DIRTY | MT_ACCESS | MT_THREAD_SHARE | MT_R | MT_W | MT_X,
	MT_DEVICE				= MT_DIRTY | MT_ACCESS | MT_THREAD_SHARE | MT_R | MT_W,
} mmap_attr_t;

typedef struct mmap_region {
  unsigned long base;
  unsigned long size;
  mmap_attr_t attr;
} mmap_region_t;

#define MAX_MMAP_REGIONS 8

#define ENTRY_SIZE_SHIFT 3
#define PAGE_SIZE_SHIFT  12
#define TABLE_SIZE_SHIFT PAGE_SIZE_SHIFT

#define TABLE_SIZE          (1 << TABLE_SIZE_SHIFT)
#define TABLE_ENTRIES_SHIFT (TABLE_SIZE_SHIFT - ENTRY_SIZE_SHIFT)
#define TABLE_ENTRIES       (1 << TABLE_ENTRIES_SHIFT)
#define TABLE_ENTRIES_MASK  (TABLE_ENTRIES - 1)

#define L3_ADDRESS_SHIFT PAGE_SIZE_SHIFT
#define L2_ADDRESS_SHIFT (L3_ADDRESS_SHIFT + TABLE_ENTRIES_SHIFT)
#define L1_ADDRESS_SHIFT (L2_ADDRESS_SHIFT + TABLE_ENTRIES_SHIFT)

#define UNSET_DESC     ~0ul
#define INVALID_DESC   0x0
#define TABLE_DESC     0xc1
#define MAX_SUB_TABLES 3

enum { ALIGN_DOWN, ALIGN_UP };

enum { MMAP_UNIT_NONE, MMAP_UNIT_SUCCESS, MMAP_UNIT_ERROR };

extern void configure_mmu(void);
extern void mmu_enable(void);
extern void mmu_disable(void);
extern int is_cfg_mmu(void);

#endif

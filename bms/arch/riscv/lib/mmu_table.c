#include <common.h>
#include <mmu_table.h>

//#define DEBUG_MMU_TABLE

#ifdef DEBUG_MMU_TABLE
#define mmu_dbg(...) printf(__VA_ARGS__)
#else
#define mmu_dbg(...) ((void)0)
#endif

static mmap_region_t mmap_regions[MAX_MMAP_REGIONS] = {0};

uint64_t l1_table[TABLE_ENTRIES] __aligned(TABLE_ENTRIES * sizeof(uint64_t));

static uint64_t sub_tables[MAX_SUB_TABLES][TABLE_ENTRIES] __aligned(
    TABLE_ENTRIES * sizeof(uint64_t));
static unsigned next_sub = 0;

static void print_mmap(void) {
#ifdef DEBUG_MMU_TABLE
  mmu_dbg("mmap:\n");
  mmap_region_t *mm = mmap_regions;
  while (mm->size) {
    mmu_dbg(" %010lx %10lx %lx\n", mm->base, mm->size, mm->attr);
    ++mm;
  };
  mmu_dbg("\n");
#endif
}

int mmap_add_region(unsigned long base, unsigned long size,
                    unsigned long attr) {
  mmap_region_t *mm      = mmap_regions;
  mmap_region_t *mm_last = mm + MAX_MMAP_REGIONS - 1;

  mmu_dbg("mmap base 0x%llx, size 0x%llx, attr 0x%llx\n", base, size, attr);

  if (!size)
    return -1;

  while (base > mm->base && mm->size)
    mm++;

	while (base == mm->base && (mm->size > size))
		mm++;

  /* Make room for new region by moving other regions up by one place */
  memmove(mm + 1, mm, (uintptr_t)mm_last - (uintptr_t)mm);

  mm->base = base;
  mm->size = size;
  mm->attr = attr;
  return 0;
}

void mmap_add(const mmap_region_t *mm) {
  while (mm->size) {
    mmap_add_region(mm->base, mm->size, mm->attr);
    ++mm;
  }
}

static unsigned long mmap_desc(unsigned long attr, unsigned long addr,
                               unsigned level) {
  unsigned long desc = (addr >> 2);

  desc |= (attr | MT_VAILD);
  return desc;
}

static unsigned long mmap_region_attr(mmap_region_t *mm, unsigned long base,
                                      unsigned long size) {
  unsigned long attr = mm->attr;

  for (;;) {
    ++mm;

    if (!mm->size)
      return attr; /* Reached end of list */

    if (mm->base >= base + size)
      return attr; /* Next region is after area so end */

    if (mm->base + mm->size <= base)
      continue; /* Next region has already been overtaken */

    if ((mm->attr & attr) == attr)
      continue; /* Region doesn't override attribs so skip */

    attr &= mm->attr;

    if (mm->base > base || mm->base + mm->size < base + size)
      return -1; /* Region doesn't fully cover our area */
  }
}

static mmap_region_t *init_table(mmap_region_t *mm, unsigned long base,
                                 unsigned long *table, unsigned level) {
  unsigned long level_size_shift =
      L1_ADDRESS_SHIFT - (level - 1) * TABLE_ENTRIES_SHIFT;
  unsigned long level_size       = 1 << level_size_shift;
  unsigned long level_index_mask = TABLE_ENTRIES_MASK << level_size_shift;

  do {
    unsigned long desc = UNSET_DESC;

    if ((mm->base + mm->size) <= base) {
      mm++;
      continue;
    }

    if (mm->base >= (base + level_size)) {
      desc = INVALID_DESC;
    } else if (mm->base <= base &&
               (mm->base + mm->size) >= (base + level_size)) {
      unsigned long attr = mmap_region_attr(mm, base, level_size);
      if (attr >= 0)
        desc = mmap_desc(attr, base, level);
    }

    if (desc == UNSET_DESC) {
      unsigned long *new_table = sub_tables[next_sub++];
      if (next_sub > MAX_SUB_TABLES) {
        mmu_dbg("Lack mmu tables\n");
        return NULL;
      }
      desc = TABLE_DESC | (unsigned long)new_table;

      mm = init_table(mm, base, new_table, level + 1);
    }

    *table++ = desc;
    if (desc != UNSET_DESC && desc != INVALID_DESC)
      mmu_dbg("table 0x%llx\n", desc);
    base += level_size;
  } while (mm && mm->size && (base & level_index_mask));

  return mm;
}

void init_tables(void) {
  print_mmap();
  init_table(mmap_regions, 0, l1_table, 1);
}

#define DEVICE0_BASE 0x0UL
#define DEVICE0_SIZE 0x40000000UL

/* register space */
#define DEVICE1_BASE 0xc0000000UL
#define DEVICE1_SIZE 0x40000000UL

/* ddr 16G */
#define DEVICE2_BASE 0x100000000UL
#define DEVICE2_SIZE 0x400000000UL

/*
 * Table of regions to map using the MMU.
 */
const mmap_region_t fvp_mmap[] = {
    {DEVICE0_BASE, DEVICE0_SIZE, MT_MEMORY},
		{DEVICE1_BASE, DEVICE1_SIZE, MT_DEVICE},
		{DEVICE2_BASE, DEVICE2_SIZE, MT_MEMORY},
    {0}};

/*******************************************************************************
 * Setup the pagetables as per the platform memory map & initialize the mmu
 *******************************************************************************/
int is_cfg_mmu(void) {
	uint64_t satp = __get_SATP();
	return satp;
}

__attribute__ ((noinline)) void configure_mmu(void) {
  mmap_add(fvp_mmap);
  init_tables();
  __set_SATP(((uint64_t)&l1_table >> 12));
}

void mmu_enable(void) {
	csi_mmu_enable(MMU_MODE_48);
}

void mmu_disable(void) {
	csi_mmu_disable();
}

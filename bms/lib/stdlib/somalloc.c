#include <common.h>
#include <malloc.h>
#include <linux/list.h>

/* Sololz malloc algorithm, the best and most effecient algorithm
 * for memory managment.
 */
/* reserve 512K memory for malloc handling */

#ifndef CONFIG_COMPILE_RTL
#ifndef CONFIG_COMPILE_ROM
#ifdef CONFIG_TB_RUN_IRAM
#define MALC_RESV (0x4000)
#else
#define MALC_RESV (0x80000)
#endif
#else
#define MALC_RESV (0x1000)
#endif
#else
/*to improve speed int rtl*/
/* cae needs more times malloc which is not free. */
#ifdef CONFIG_C920
#define MALC_RESV (0x8000)
#else
#define MALC_RESV (0x2000)
#endif
#endif

#define MALC_PIECE     (0x40)
#define MALC_PIECE_MSK (MALC_PIECE - 1)

/* use the high 2 bits as status indicator,
 * thus, an allocation can not exceed 1GB limit.
 *
 * this very node stored on end edge of memory
 * will be used as an all node indicator.
 * In this case: start means the location of the
 * front node. size is set to be a magic:
 * 0x11111111
 */
struct so_m {
  void *start;
  long size;
  struct list_head link;
};

struct so_m_pool {
  int count;   /* count of total m nodes */
  int free;    /* count of available m nodes */
  void *start; /* start address of malloc location */
  void *end;   /* end address of malloc location */
  long used;   /* used size of malloc location */
  struct list_head list;
} m_pool;

int inline so_m_isused(struct so_m *m) { return !!((m->size) & 0xc0000000); }

void inline so_m_set_used(struct so_m *m) { m->size |= 0x40000000; }

void inline so_m_unset_used(struct so_m *m) { m->size &= ~0xc0000000; }

uint32_t inline so_m_get_size(struct so_m *m) { return m->size & ~0xc0000000; }

// FIXME don't know why inline is not passing compile, fuck it
void so_m_set_size(struct so_m *m, uint32_t size) {
  m->size &= 0xc0000000;
  m->size |= (size & ~0xc0000000);
}

struct so_m *so_m_alloc(void) {
  int i;
  struct so_m *m = (struct so_m *)m_pool.start;

  for (i = 0; i < m_pool.count; i++)
    if (!m[i].size) {
      m_pool.free--;
      return &m[i];
    }
  return NULL;
}

void so_m_remove(struct so_m *m) {
  m->size  = 0;
  m->start = 0;
  m_pool.free++;
}

extern uint8_t *__lds_malloc_start[];
extern uint8_t *__lds_malloc_end[];
int sOMEMINIt(void) {
  struct so_m *m;

  m_pool.end   = (void *)(((size_t)__lds_malloc_end) & ~MALC_PIECE_MSK);
  m_pool.start = (void *)((((size_t)__lds_malloc_start) + MALC_PIECE_MSK) &
                          ~MALC_PIECE_MSK);

  if (m_pool.end - m_pool.start <= MALC_RESV)
    /* I will fuxk you if I can use printf */
    return -1;

  m_pool.count = MALC_RESV / sizeof(struct so_m);
  m_pool.free  = m_pool.count;
  INIT_LIST_HEAD(&m_pool.list);

#ifndef CONFIG_COMPILE_RTL
  /*no need in rtl, rtl initiliazed ddr zero*/
  /* init m_pool */
  memset((uint8_t *)m_pool.start, 0, MALC_RESV);
#endif

  /* init head node, all memory is in head node,
   * and also, is free */
  m = so_m_alloc();
  so_m_set_size(m, m_pool.end - m_pool.start - MALC_RESV);
  m->start = m_pool.start + MALC_RESV;
  list_add_tail(&m->link, &m_pool.list);

  return 0;
}
void *sOMALLOc(size_t bytes) {
  struct so_m *m, *n = NULL;

  if (!bytes)
    return NULL;

  /* align bytes to a smallest piece */
  bytes = (bytes + MALC_PIECE_MSK) & ~MALC_PIECE_MSK;

  /* find a suitable block */
  list_for_each_entry(m, &m_pool.list, link) {
    if (so_m_isused(m) || (so_m_get_size(m) < bytes))
      continue;
    if (!n || (so_m_get_size(m) < so_m_get_size(n)))
      n = m;

    if (n)
      goto __alloc_done;
  }

  return NULL;

__alloc_done:
  if (so_m_get_size(n) > bytes) {
    m = so_m_alloc();
    if (unlikely(m == NULL))
      /* failed, can not alloc a memory node. */
      return NULL;

    so_m_set_size(m, so_m_get_size(n) - bytes);
    m->start = n->start + bytes;
    so_m_set_size(n, bytes);
    list_add(&m->link, &n->link);
  }

  so_m_set_used(n);
  m_pool.used += so_m_get_size(n);
  return (void *)n->start;
}

void *sOCALLOc(size_t count, size_t bytes) {
  void *p;

  /* allocate 'count' objects of size 'bytes' */
  p = sOMALLOc(count * bytes);

  /* zero the memory */
  if (p)
    memset(p, 0, count * bytes);

  return p;
}
/* merge 'n' to 'm', 'n' nolonger exist after merge */
void __sOMERGe(struct so_m *m, struct so_m *n) {
  if (so_m_isused(m) || so_m_isused(n))
    return;

  so_m_set_size(m, so_m_get_size(m) + so_m_get_size(n));
  list_del(&n->link);
  /* free node */
  so_m_remove(n);
}

void sOFREe(void *mem) {
  struct so_m *m, *n;
  if (unlikely(mem == NULL))
    /* no memory is provided */
    return;

  list_for_each_entry(m, &m_pool.list, link) {
    if (m->start == mem)
      goto __free_done;
  }

  /* this piece of memory is not in control */
  return;

__free_done:
  if (!so_m_isused(m))
    /* you can not free a piece not in use */
    return;

  so_m_unset_used(m);
  m_pool.used -= so_m_get_size(m);

  /* merge the next node */
  if (!list_is_last(&m->link, &m_pool.list)) {
    n = list_entry(m->link.next, struct so_m, link);
    __sOMERGe(m, n);
  }

  /* merge the previous node */
  if (!list_is_first(&m->link, &m_pool.list)) {
    n = list_entry(m->link.prev, struct so_m, link);
    __sOMERGe(n, m);
  }

  return;
}

void __sOINFo(void) {
  struct so_m *m;
  printf("Nodes : %u all, %u free.\n", m_pool.count, m_pool.free);
  printf("Memory: %lx all, 0x%lx used. (%ld%%)\n",
         m_pool.end - m_pool.start - MALC_RESV, m_pool.used,
         m_pool.used * 100 / (m_pool.end - m_pool.start - MALC_RESV));

  printf("Memory layout: \n");
  printf("-------------------\n");

  list_for_each_entry(m, &m_pool.list, link)
      printf("start: %p, size: 0x%08x, inuse: %d\n", m->start, so_m_get_size(m),
             so_m_isused(m));
}

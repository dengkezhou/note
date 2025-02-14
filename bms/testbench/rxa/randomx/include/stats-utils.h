#ifndef __STATS_UTILS_H__
#define __STATS_UTILS_H__

//#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
//#include <unistd.h>

#include "utils.h"

#ifdef __cplusplus
extern "C" {
#endif

#define INS_ISSUE 5

#define PERF_LVL_ROUTINE 0
#define PERF_LVL_ROUND   1
#define PERF_LVL_TOTAL   2

#define PERF_DETAIL 2

typedef struct routine_perf_ {
  char name[32];
  int cnt[4]; // 0: for a specific routine, 1: for one complete round, 2: for
              // total stats
  int us_min[4], us_all[4], us_max[4];
  unsigned long t0;
} routine_perf_t;

extern void perf_poke(routine_perf_t *rp);
extern void perf_peek(routine_perf_t *rp);
extern routine_perf_t *perf_alloc(const char *name);
extern void perf_flush(int lvl, const char *);

#define POKE(vp, _n)                                                           \
  static routine_perf_t *vp = NULL;                                            \
  do {                                                                         \
    if (!vp)                                                                   \
      vp = perf_alloc(_n);                                                     \
    perf_poke(vp);                                                             \
  } while (0)

#define PEEK(vp) perf_peek(vp)
#define PEOO()   perf_peek(NULL)

#define POKC(x)                                                                \
  do {                                                                         \
    POKE(x, #x);                                                               \
    PEEK(x);                                                                   \
  } while (0)

// op stats for randomx
struct opdesc {
  int op;
  int src;
  int dst;
  int force_break;
  uint32_t imm;
  uint32_t addr;
  int pr; // paralelle row
};

typedef struct InsStats_ {
  struct opdesc op[256];
} InsStats;

extern int dump_instr;
extern int st_ic;
extern uint64_t *st_nreg;
extern int progN, dump_regs_mem, dump_regs_full;

extern void cmpRegs(int opcode, int indi, int ic, uint64_t *regs);

struct op_info_ {
  const char *name;
  int latency;
  int mem;
};
extern struct op_info_ op_info[];

#ifdef __cplusplus
}
#endif
#endif // __STATS_UTILS_H__

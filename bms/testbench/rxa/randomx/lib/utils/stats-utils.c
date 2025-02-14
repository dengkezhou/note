#include <linux/types.h>
#include <common.h>
#include <malloc.h>
#include "stats-utils.h"
#include <stdio.h>
#include <string.h>

static routine_perf_t *grp = NULL, rp_db[32] = {0};
static int rp_count = 0;

void perf_clear(routine_perf_t *rp, int cap) {
  for (int i = cap; i >= 0; i--) {
    rp->cnt[i]    = 0;
    rp->us_min[i] = 0;
    rp->us_all[i] = 0;
    rp->us_max[i] = 0;
  }
}

void perf_poke(routine_perf_t *rp) { rp->t0 = get_timer_us(0); }

void perf_peek(routine_perf_t *rp) {
  unsigned long t1;
  t1 = get_timer_us(0);

  if (grp && rp != grp && PERF_DETAIL == 0 && grp->cnt[0]) {
    printf("%32s ||| %d rounds, %d us\n", grp->name, grp->cnt[0],
           grp->us_all[0]);
    perf_clear(grp, 0);
    grp = rp;
  }

  if (!rp)
    return;

  int us = (t1 - rp->t0);
  rp->t0 = t1;
	
	if (!strcmp(rp->name, "gen 256 12 code"))
  	printf("us %d\n", us);

#define MINX(a, b)    a = !a || (a) > (b) ? (b) : (a)
#define MAXX(a, b)    a = (a) > (b) ? (a) : (b)
#define AVGX(a, c, b) a = ((a) * (c) + (b)) / (c + 1)
  for (int i = PERF_DETAIL; i < 3; i++) {
    MINX(rp->us_min[i], us);
    MAXX(rp->us_max[i], us);
    rp->us_all[i] += us;
    rp->cnt[i]++;
  }

  grp = rp;
}

routine_perf_t *perf_alloc(const char *name) {
  routine_perf_t *rp = &rp_db[rp_count++];
  strcpy(rp->name, name);
  return rp;
}

void perf_flush(int lvl, const char *prefix) {
  if (prefix)
    printf("\n=== showing perf: %s ===\n", prefix);
  for (int i = 0; i < rp_count; i++) {
    routine_perf_t *rp = &rp_db[i];
    if (!rp->cnt[lvl])
      continue;

    if (prefix)
      printf("%32s ||| %d rounds, %d us <%d, %d, %d>\n", rp->name, rp->cnt[lvl],
             rp->us_all[lvl], rp->us_min[lvl], rp->us_all[lvl] / rp->cnt[lvl],
             rp->us_max[lvl]);
    perf_clear(rp, lvl);
  }
}

int dump_instr = 0;

int st_ic         = 0;
uint64_t *st_nreg = NULL;
int progN         = 0;
int dump_regs_mem = 0;
// int dump_regs_mem = 10 << 20;
int dump_regs_full = 0;

void cmpRegs(int opcode, int indi, int ic, uint64_t *regs) {
#if 0
  static int fd = -1, step = 0;
  static uint64_t *p = NULL;
  int __e            = 0;

  if (!dump_regs_mem)
    return;

  if (fd < 0) {
    fd = open("./regs.dump", O_RDONLY);
    p  = (uint64_t *)malloc(20 << 20);
    read(fd, p, 16 << 20);
    p += 8;
    close(fd);
  }

  p++;

  int a = *p++;

  printf("p%d step %d, %x, loop=%d, op=%d\n", progN, step++, indi, ic, opcode);
  if (indi != a)
    printf("indicator diff %x <> %x\n", indi, a);

  a = *p++;
  if (indi != 0x1d && opcode != a)
    printf("opcode diff %d <> %d\n", opcode, a);

  a = *p++;
  if (ic != a)
    printf("ic diff %x <> %x\n", ic, a);

  a = *p++;
  if (indi == 0x1d)
    printf("ma offset %x <> %x\n", opcode, a);

  p++;
  uint64_t b = *p++;
  if (b != *regs) {
    printf("r0 diff %zx <> %zx\n", *regs, b);
    __e = 1;
  }
  p++;

  if (dump_regs_full) {
    if (indi == 0x1d) {
      p += 24;
      return;
    }

    for (int i = 0; i < 8; i++) {
      b = *p++;
      if (b != *(regs + i)) {
        __e = 1;
        printf("r%d diff %zx <> %zx\n", i, *(regs + i), b);
      }
    }

    regs += 8;
    for (int i = 0; i < 8; i++) {
      b = *p++;
      if (b != *(regs + i)) {
        __e = 1;
        printf("f%d.%d diff %zx <> %zx\n", i >> 1, i & 1, *(regs + i), b);
      }
    }

    regs += 8;
    for (int i = 0; i < 8; i++) {
      b = *p++;
      if (b != *(regs + i)) {
        __e = 1;
        printf("e%d.%d diff %zx <> %zx\n", i >> 1, i & 1, *(regs + i), b);
      }
    }
  }

  if (__e)
    exit(1);
#endif
}

struct op_info_ op_info[] = {
    {
        .latency = 1,
        .mem     = 0,
        .name    = "IADD_RS",
    },
    {
        .latency = 1,
        .mem     = 1,
        .name    = "IADD_M",
    },
    {
        .latency = 1,
        .mem     = 0,
        .name    = "ISUB_R",
    },
    {
        .latency = 1,
        .mem     = 1,
        .name    = "ISUB_M",
    },
    {
        .latency = 1,
        .mem     = 0,
        .name    = "IMUL_R",
    },
    {
        .latency = 1,
        .mem     = 1,
        .name    = "IMUL_M",
    },
    {
        .latency = 1,
        .mem     = 0,
        .name    = "IMULH_R",
    },
    {
        .latency = 1,
        .mem     = 1,
        .name    = "IMULH_M",
    },
    {
        .latency = 1,
        .mem     = 0,
        .name    = "ISMULH_R",
    },
    {
        .latency = 1,
        .mem     = 1,
        .name    = "ISMULH_M",
    },
    {
        .latency = 1,
        .mem     = 0,
        .name    = "IMUL_RCP",
    },
    {
        .latency = 1,
        .mem     = 0,
        .name    = "INEG_R",
    },
    {
        .latency = 1,
        .mem     = 0,
        .name    = "IXOR_R",
    },
    {
        .latency = 1,
        .mem     = 1,
        .name    = "IXOR_M",
    },
    {
        .latency = 1,
        .mem     = 0,
        .name    = "IROR_R",
    },
    {
        .latency = 1,
        .mem     = 0,
        .name    = "IROL_R",
    },
    {
        .latency = 1,
        .mem     = 0,
        .name    = "ISWAP_R",
    },
    {
        .latency = 1,
        .mem     = 0,
        .name    = "FSWAP_R",
    },
    {
        .latency = 1,
        .mem     = 0,
        .name    = "FADD_R",
    },
    {
        .latency = 1,
        .mem     = 1,
        .name    = "FADD_M",
    },
    {
        .latency = 1,
        .mem     = 0,
        .name    = "FSUB_R",
    },
    {
        .latency = 1,
        .mem     = 1,
        .name    = "FSUB_M",
    },
    {
        .latency = 1,
        .mem     = 0,
        .name    = "FSCAL_R",
    },
    {
        .latency = 1,
        .mem     = 0,
        .name    = "FMUL_R",
    },
    {
        .latency = 1,
        .mem     = 1,
        .name    = "FDIV_M",
    },
    {
        .latency = 1,
        .mem     = 0,
        .name    = "FSQRT_R",
    },
    {
        .latency = 1,
        .mem     = 0,
        .name    = "CBRANCH",
    },
    {
        .latency = 1,
        .mem     = 0,
        .name    = "CFROUND",
    },
    {
        .latency = 1,
        .mem     = 2,
        .name    = "ISTORE",
    },
    {
        .latency = 1,
        .mem     = 0,
        .name    = "NOP",
    },
};

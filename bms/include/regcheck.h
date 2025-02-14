#ifndef __REGCHECK_H__
#define __REGCHECK_H__

struct reg_check {
  uint32_t addr;
  uint32_t mask;
};

#define REG_CHECK_INIT(_addr, _mask)                                           \
  { .addr = _addr, .mask = _mask, }

static __inline__ int common_reg_check(struct reg_check *reg, int num,
                                       uint32_t val) {
  int i = 0;

  for (i = 0; i < num; i++) {
    writel(val & reg[i].mask, reg[i].addr);
    if ((readl(reg[i].addr) & reg[i].mask) != (val & reg[i].mask)) {
      printf("addr is 0x%x, val is 0x%x\n", reg[i].addr,
             readl(reg[i].addr));
      return -1;
    }
  }
  return 0;
}

#endif

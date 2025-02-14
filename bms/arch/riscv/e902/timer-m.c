#include <common.h>
#include <initcall.h>
#include <asm/io.h>
#include <div64.h>
#include <core_rv32.h>

unsigned long g_ticks_per_us;
int init_timer(void) {
  g_ticks_per_us = lldiv_roundup(itcs_pll_get_clock(SAP, "spll"), 1000000);
  return 0;
}

unsigned long long get_ticks(void) {
  return ((unsigned long long)csi_coret_get_valueh() << 32) |
         csi_coret_get_value();
}

void udelay(unsigned long us) {
  unsigned long long t = get_ticks();
  while (get_ticks() < (t + us * g_ticks_per_us))
    ;
}

// in ms
unsigned long get_timer(unsigned long base) {
  unsigned long t;
  t = lldiv_roundup(get_ticks(), g_ticks_per_us * 1000);
  return t - base;
}

void timer_register(void) { init_timer(); }
module_init(timer_register);

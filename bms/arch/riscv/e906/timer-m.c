#include <common.h>
#include <initcall.h>
#include <asm/io.h>
#include <div64.h>
#include <core_rv32.h>

unsigned long g_ticks_per_us, g_ticks_per_ns;
int init_timer(void) {
  g_ticks_per_us = lldiv(itcs_pll_get_clock(SAP, "spll"), 1000000);
  g_ticks_per_ns = lldiv(itcs_pll_get_clock(SAP, "spll"), 1000);
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

void nsdelay(unsigned long ns) {
  unsigned long long t = get_ticks();
  while (get_ticks() < (t + ns * g_ticks_per_ns))
    ;
}

// in ms
unsigned long get_timer(unsigned long base) {
  unsigned long t;
	// round
  t = lldiv(get_ticks() + g_ticks_per_us * 1000 / 2 - 1, g_ticks_per_us * 1000);
  return t - base;
}

#ifdef CONFIG_COMPILE_ASIC
#if !defined(CONFIG_COMPILE_ROM)
void timer_register(void) { init_timer(); }
module_init(timer_register);
#endif
#else
void timer_register(void) { init_timer(); }
module_init(timer_register);
#endif

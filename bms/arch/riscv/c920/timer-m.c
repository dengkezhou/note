#include <common.h>
#include <initcall.h>
#include <asm/io.h>
#include <div64.h>
#include <csi_rv64_gcc.h>

unsigned long g_ticks_per_us,g_ticks_per_ns;
int init_timer(void) {
  g_ticks_per_us = itcs_pll_get_clock(CPU, "apll") / 1000000;
#ifndef CONFIG_COMPILE_FPGA
	// axi clk
	g_ticks_per_us /= 4;
#endif
  return 0;
}

unsigned long long get_ticks(void) { return __get_MTIME(); }

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

// in us
unsigned long get_timer_us(unsigned long base) {
  unsigned long t;
	// round
  t = lldiv(get_ticks() + g_ticks_per_us / 2 - 1, g_ticks_per_us);
  return t - base;
}

void timer_register(void) { init_timer(); }
module_init(timer_register);

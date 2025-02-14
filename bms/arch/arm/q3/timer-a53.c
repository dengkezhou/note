
#include <common.h>
#include <initcall.h>
#include <asm/io.h>
#include <div64.h>
unsigned long g_ticks_per_us;
int init_timer(void) {
  unsigned long t;

  return 0;
}

// in us
unsigned long long get_ticks(void) { return 0; }

static inline unsigned long get_ticks_per_us(void) { return g_ticks_per_us; }

void udelay(unsigned long us) {
  unsigned long long t   = get_ticks();
  unsigned long ticks_us = get_ticks_per_us();

  while (get_ticks() < t + us * ticks_us)
    ;
}

// in ms
unsigned long get_timer(unsigned long base) {
  unsigned long t;
  t = lldiv(get_ticks(), get_ticks_per_us() * 1000);
  return t - base;
}

void timer_reigister(void) { init_timer(); }
module_init(timer_reigister);

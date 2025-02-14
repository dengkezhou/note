
#include <common.h>
#include <malloc.h>
#include <serial.h>
#include <version.h>
#include <asm/io.h>
#include <csi_rv32_gcc.h>
#include <core_rv32.h>
#include <sysmap.h>
#include <rtl.h>
#include <sysm.h>

extern unsigned long __init_f_start;
extern unsigned long __init_f_end;

void __initcall(void) {
  int len    = &__init_f_end - &__init_f_start;
  void **__f = (void **)&__init_f_start;
  void (*__the_f)(void);

  // printf("initcall: len:%d, section:%p\n", len, __f);
  for (; len > 0; len--) {
    __the_f = *__f++;
    // printf("initcall: exec@%p\n", __the_f);
    __the_f();
  }
}

void init_core(void) {
  uint32_t val;

  /* enable FS */
  val = __get_MSTATUS();
  val |= (1 << 13);
  __set_MSTATUS(val);

  /* initialize system map */
  //  systemmap_config();
}

void set_clk(void) { itcs_pll_set_clock(SAP, "spll", 500000000, false); }

int main(void) {
  extern uint32_t __lds_rtl_case[];
  extern uint32_t __lds_soc_base[];
  unsigned long soc_base = (unsigned long)__lds_soc_base;

#ifdef CONFIG_COMPILE_RTL
  puts_enable(0);
#endif

  init_core();

  /* init malloc */
  init_malloc();

#ifdef CONFIG_COMPILE_RTL
  set_clk();
#endif

  init_serial();

  printf("\nSoC Testbench: ROM\n");
#ifndef CONFIG_COMPILE_RTL
  /* call init functions */
  __initcall();
#endif

  if (*(uint32_t *)__lds_rtl_case == (uint32_t)RTL_MAGIC) {
#ifdef CONFIG_BOOT_OTHER_CORE
    itcs_sysm_boot_core(CPU, 0, soc_base);
#else
    asm volatile("jalr ra, %0;" ::"r"(soc_base));
#endif
  }

#ifndef CONFIG_COMPILE_RTL
  main_loop();
#endif
  for (;;)
    ;
  return 0;
}

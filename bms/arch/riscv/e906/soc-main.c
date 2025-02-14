
#include <common.h>
#include <malloc.h>
#include <serial.h>
#include <version.h>
#include <asm/io.h>
#include <csi_rv32_gcc.h>
#include <core_rv32.h>
#include <sysmap.h>
#include <rtl.h>
#include <pads.h>
#include <cache.h>

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

void asic_set_clk(void) {
    // itcs_pll_set_clock(CPU, "apll", 2496000000, false);
  itcs_pll_set_clock(CPU, "dpll", 1500000000, false);
  itcs_pll_set_clock(CPU, "epll", 1160000000, true);
  // itcs_pll_set_clock(CPU, "vpll", 2112000000, false);

  itcs_module_set_clock(CPU, "apb", NULL, 100800000, false);
  itcs_module_set_clock(SAP, "apb", NULL, 100800000, false);

  itcs_module_set_clock(CPU, "bus1", "dpll", 375000000, false);
  itcs_module_set_clock(CPU, "bus2", "dpll", 375000000, false);
  }

void set_clk(void) {
    // itcs_pll_set_clock(CPU, "apll", 2496000000, false);
  itcs_pll_set_clock(CPU, "dpll", 1500000000, false);
  itcs_pll_set_clock(CPU, "epll", 2457600000, true);
  // itcs_pll_set_clock(CPU, "vpll", 2112000000, false);

  itcs_module_set_clock(CPU, "apb", NULL, 104000000, false);
  itcs_module_set_clock(SAP, "apb", NULL, 100800000, false);

  itcs_module_set_clock(CPU, "bus1", "dpll", 375000000, false);
  itcs_module_set_clock(CPU, "bus2", "dpll", 375000000, false);
}

int main(void) {
#ifdef CONFIG_COMPILE_RTL
  puts_enable(0);
#endif

#ifdef CONFIG_SYSMAP
  systemmap_config();
#endif

#ifdef CONFIG_CACHE
  itcs_dcache_enable();
  itcs_icache_enable();
#endif
  /* init malloc */
  init_malloc();

#ifdef CONFIG_COMPILE_RTL
  set_clk();
#endif

#ifdef CONFIG_COMPILE_ASIC
  asic_set_clk();
#endif

#if defined(CONFIG_COMPILE_FPGA) || defined(CONFIG_ASIC_TEST_ON_FPGA)
  /* ? Need in fpga for frank.lin config all io to func mode in bootrom
   * temporarily */
  itcs_pads_set_mode(CPU, PADSRANGE(22, 93), PADS_MODE_IN, 1);
#endif

  init_serial();

  printf("\n\n");
  printf("WSS: Running on " CONFIG_MACHINE "\n");
  printf("WSS: " BMS_COMMIT_ID "\n");
  printf("WSS: " BMS_COMPILE_INFO "\n\n");

  /* For reading rtc register by jtags*/
  //*((uint32_t *)(0xd2e0020c)) = 1;

  /* call init functions */
  __initcall();

  /* enter shell */
  printf("\n\n");
#ifdef CONFIG_COMPILE_RTL
  /* judge RTL is relevant environment */
  if (try_rtl())
    for (;;)
      ;
#endif

  main_loop();
  /* BUG if executation pass main_loop */
  for (;;)
    ;
}

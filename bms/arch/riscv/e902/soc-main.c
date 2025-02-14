
#include <common.h>
#include <malloc.h>
#include <serial.h>
#include <version.h>
#include <asm/io.h>
#include <csi_rv32_gcc.h>
#include <core_rv32.h>
#include <sysmap.h>
#include <rtl.h>

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

void set_clk(void) {
  itcs_pll_set_clock(CPU, "apll", 2500000000, false);
  itcs_pll_set_clock(CPU, "dpll", 2500000000, false);
  itcs_pll_set_clock(CPU, "epll", 2400000000, false);
  itcs_pll_set_clock(CPU, "vpll", 2166000000, false);

  itcs_module_set_clock(CPU, "apb", NULL, 125000000, false);
  itcs_module_set_clock(SAP, "apb", NULL, 125000000, false);

  itcs_module_set_clock(CPU, "bus1", "dpll", 500000000, false);
  itcs_module_set_clock(CPU, "bus2", "dpll", 500000000, false);
}

int main(void) {
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

  printf("\n\n");
  printf("WSS: " BMS_COMMIT_ID "\n");
  printf("WSS: " BMS_COMPILE_INFO "\n\n");

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

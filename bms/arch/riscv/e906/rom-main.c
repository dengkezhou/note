
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
#include <lpddr4.h>
#ifdef CONFIG_COMPILE_ASIC
#include <ff.h>
#define PAYLOAD_NAME "soc.bin"
  #if defined(CONFIG_TB_RUN_DDR) || defined(CONFIG_TB_RUN_DDR1)
  #define PAYLOAD_LOAD_ADDR ITCS_SDDR_ADDR
  #else
  #define PAYLOAD_LOAD_ADDR ITCS_BRAM_ADDR
  #endif
#endif

// #define REBOOT_STRESS_TEST
#ifdef REBOOT_STRESS_TEST
#include <rtc-sysm.h>
#endif

extern unsigned long __init_f_start;
extern unsigned long __init_f_end;
extern uint32_t __lds_rtl_case[];
extern uint32_t __lds_soc_base[];

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
#ifdef CONFIG_COMPILE_ASIC
  systemmap_config();
#endif
}



void set_clk(void) {
  itcs_pll_set_clock(SAP, "spll", 504000000, false);
  itcs_pll_set_clock(CPU, "apll", 2016000000, false);
  itcs_pll_set_clock(CPU, "vpll", 2112000000, false);
  itcs_pll_set_clock(CPU, "bpll", 2376000000, false);
  itcs_pll_set_clock(CPU, "cpll", 2016000000, false);
  itcs_pll_set_clock(CPU, "dpll", 1500000000, false);
  itcs_pll_set_clock(CPU, "epll", 2424000000, true);
}

void asic_set_clk(void) {
    itcs_pll_set_clock(SAP, "spll", 504000000, false);
    itcs_pll_set_clock(CPU, "apll", 1600000000, false);
    itcs_pll_set_clock(CPU, "vpll", 2112000000, false);
    itcs_pll_set_clock(CPU, "bpll", 2376000000, false);
    itcs_pll_set_clock(CPU, "dpll", 1500000000, false);
  }

#ifdef CONFIG_COMPILE_ASIC
extern int fatfs_init(void);

static int load_payload(uintptr_t addr)
{
  int fd;
  int ret;

  puts("Loading " PAYLOAD_NAME " from SD card...\n");

  if ((ret = fatfs_init()) < 0) {
    printf("mount failed, ret = %d\n", ret);
    return ret;
  } else if ((fd = open(PAYLOAD_NAME, O_RDONLY)) < 0) {
    printf("open failed, fd = %d\n", fd);
    return fd;
  } else {
    void *buf = (void *)addr;
    ssize_t file_size = flen(fd);
    ssize_t br;
    if ((br = read(fd, buf, file_size)) < 0) {
      printf("read failed, br = %d\n", br);
      close(fd);
      return -1;
    }

    printf("Successfully loaded %d bytes to 0x%lx\n", br, addr);
    close(fd);
  }

  return 0;
}
#endif

static int get_bootm(void) {
#ifndef CONFIG_COMPILE_ASIC
  return itcs_sysm_get_boot_mode(SAP) & 0xf;
#else
  return CONFIG_BOOTM;
#endif
}

static int use_intleave = 0;

static void ddr_intleave_init(void){
  //When fpga switch set to 1, use ddr intleave mode.
  if(use_intleave != USE_INTLEAVE){
    printf("disable ddr interleave\n");
    //disable bypass
    writel(readl(ITCS_C_SAP_AFE_BASE  + 0x2c) | USE_INTLEAVE_MASK, ITCS_C_SAP_AFE_BASE  + 0x2c);
    writel(readl(ITCS_C_CPU_AFE_BASE  + 0x2c) | USE_INTLEAVE_MASK, ITCS_C_CPU_AFE_BASE  + 0x2c);
    writel(readl(ITCS_C_BUS1_AFE_BASE + 0x2c) | USE_INTLEAVE_MASK, ITCS_C_BUS1_AFE_BASE + 0x2c);
    writel(readl(ITCS_C_BUS2_AFE_BASE + 0x2c) | USE_INTLEAVE_MASK, ITCS_C_BUS2_AFE_BASE + 0x2c);
    writel(readl(ITCS_C_BUS3_AFE_BASE + 0x2c) | USE_INTLEAVE_MASK, ITCS_C_BUS3_AFE_BASE + 0x2c);
    writel(readl(ITCS_C_BUS4_AFE_BASE + 0x2c) | USE_INTLEAVE_MASK, ITCS_C_BUS4_AFE_BASE + 0x2c);
    writel(readl(ITCS_C_BUS5_AFE_BASE + 0x2c) | USE_INTLEAVE_MASK, ITCS_C_BUS5_AFE_BASE + 0x2c);
    writel(readl(ITCS_C_BUS6_AFE_BASE + 0x2c) | USE_INTLEAVE_MASK, ITCS_C_BUS6_AFE_BASE + 0x2c);
    //disable ddr intleave
    writel(0x0, ITCS_DRAM_ADDRMODE);
    //run in ddr1
    #ifdef CONFIG_TB_RUN_DDR1
      writel(16, ITCS_SAP_EDRAM_BASE);
    #else
      writel(0, ITCS_SAP_EDRAM_BASE);
    #endif
  }else{
    printf("enable ddr interleave\n");
    //enable bypass
    writel(readl(ITCS_C_SAP_AFE_BASE  + 0x2c) & (~USE_INTLEAVE_MASK), ITCS_C_SAP_AFE_BASE  + 0x2c);
    writel(readl(ITCS_C_CPU_AFE_BASE  + 0x2c) & (~USE_INTLEAVE_MASK), ITCS_C_CPU_AFE_BASE  + 0x2c);
    writel(readl(ITCS_C_BUS1_AFE_BASE + 0x2c) & (~USE_INTLEAVE_MASK), ITCS_C_BUS1_AFE_BASE + 0x2c);
    writel(readl(ITCS_C_BUS2_AFE_BASE + 0x2c) & (~USE_INTLEAVE_MASK), ITCS_C_BUS2_AFE_BASE + 0x2c);
    writel(readl(ITCS_C_BUS3_AFE_BASE + 0x2c) & (~USE_INTLEAVE_MASK), ITCS_C_BUS3_AFE_BASE + 0x2c);
    writel(readl(ITCS_C_BUS4_AFE_BASE + 0x2c) & (~USE_INTLEAVE_MASK), ITCS_C_BUS4_AFE_BASE + 0x2c);
    writel(readl(ITCS_C_BUS5_AFE_BASE + 0x2c) & (~USE_INTLEAVE_MASK), ITCS_C_BUS5_AFE_BASE + 0x2c);
    writel(readl(ITCS_C_BUS6_AFE_BASE + 0x2c) & (~USE_INTLEAVE_MASK), ITCS_C_BUS6_AFE_BASE + 0x2c);
    //enable ddr intleave
    writel(0x1, ITCS_DRAM_ADDRMODE);
  }
}

#ifndef CONFIG_TB_RUN_IRAM

#ifdef CONFIG_BOOT_OTHER_CORE
static void sysmap_config_region(void){
  itcs_sysm_switch_bram(CPU, L2CACHE_MODE);
  itcs_sysmap_config_region(0, 0x18000000, 0x0);
  itcs_sysmap_config_region(1, 0x20000000, 0x1);
  itcs_sysmap_config_region(2, 0x40000000, 0x1);
  itcs_sysmap_config_region(3, 0xc0000000, 0x1);
  itcs_sysmap_config_region(4, 0xd0000000, 0x2);
  #ifdef CONFIG_DDR_DATA_UNCACHEABLE
    #ifdef CONFIG_TB_RUN_DDR1
    itcs_sysmap_config_region(5, 0x500000000, 0x2);
    itcs_sysmap_config_region(6, 0x500100000, 0x1);
    #else
    itcs_sysmap_config_region(5, 0x100000000, 0x2);
    itcs_sysmap_config_region(6, 0x100100000, 0x1);
    #endif
    itcs_sysmap_config_region(7, 0xfffffff000, 0x0);
  #else
    #ifdef CONFIG_TB_RUN_DDR1
    itcs_sysmap_config_region(5, 0xe0000000, 0x2);
    itcs_sysmap_config_region(6, 0x500000000, 0x2);
    #else
    itcs_sysmap_config_region(5, 0xe0000000, 0x2);
    itcs_sysmap_config_region(6, 0x100000000, 0x2);
    #endif
    itcs_sysmap_config_region(7, 0xfffffff000, 0x1);
  #endif
}
#endif

static void ddr_init(int bootm)
{
  switch(bootm){
    case BOOTM_LPDDR4_DDR1_NO_INTLEAVE:{
        printf("lpddr4 ddr1 no interleave\n");
        writel(0x0, ITCS_C_SYSM_MPU1_BASE + 0X28);//enable ddr1
        lpddr4_init(1);//init ddr1
      break;
    }
    case BOOTM_LPDDR4_NO_INTLEAVE:{
        printf("lpddr4 ddr0 no interleave\n");
        writel(0x0, ITCS_C_SYSM_MPU0_BASE + 0X28);//enable ddr0
        lpddr4_init(0);//init ddr0
      break;
    }
    case BOOTM_LPDDR4_WITH_INTLEAVE:{
      printf("enable lpddr4 0&1 interleave\n");
      writel(0x0, ITCS_C_SYSM_MPU0_BASE + 0X28);//enable ddr0
      lpddr4_init(0);//init ddr0
      writel(0x0, ITCS_C_SYSM_MPU1_BASE + 0X28);//enable ddr1
      lpddr4_init(1);//init ddr1
      break;
    }
    case BOOTM_DDR_NO_INTLEAVE:{
      printf("ddr0 no interleave\n");
      writel(0x0, ITCS_C_SYSM_MPU0_BASE + 0X28);//enable ddr0
      itcs_module_enable(CPU, "ddr"); //init ddr0
      break;
    }
    case BOOTM_DDR_WITH_INTLEAVE:{
      printf("ddr0&1 interleave\n");
      writel(0x0, ITCS_C_SYSM_MPU0_BASE + 0X28);//enable ddr0
      itcs_module_enable(CPU, "ddr");//init ddr0
      writel(0x0, ITCS_C_SYSM_MPU1_BASE + 0X28);//enable ddr1
      itcs_module_enable(CPU, "ddr1");//init ddr1
      break;
    }
    case BOOTM_DDR1_NO_INTLEAVE:{
      printf("ddr1 no interleave\n");
      writel(0x0, ITCS_C_SYSM_MPU1_BASE + 0X28);//enable ddr1
      itcs_module_enable(CPU, "ddr1");//init ddr1 
      break;
    }
    default:
      printf("bootm = %d , should not be here\n", bootm);
      return;
    break;
  }
}

#endif
int main(void) {
  int bootm = get_bootm();

#ifndef CONFIG_TB_RUN_DDR
  #ifndef CONFIG_TB_RUN_DDR1
  unsigned long soc_base = (unsigned long)__lds_soc_base;
  (void)bootm;
  (void)soc_base;
  #endif
#endif

#ifdef CONFIG_COMPILE_RTL
  puts_enable(0);
#endif

  init_core();

  /* init malloc */
  init_malloc();

#ifdef CONFIG_COMPILE_RTL
  set_clk();
#endif

#ifdef CONFIG_COMPILE_ASIC
  asic_set_clk();
#endif

#if defined(CONFIG_COMPILE_ASIC) && defined(CONFIG_COMPILE_ROM)
  init_timer();
#endif

  init_serial();

  //disable ddr0 & ddr1
  writel(0x3, ITCS_C_SYSM_MPU0_BASE + 0X28);
  writel(0x3, ITCS_C_SYSM_MPU1_BASE + 0X28);

#ifdef CONFIG_COMPILE_ASIC
  #ifdef CONFIG_DDR_INTERLEAVE
    use_intleave = USE_INTLEAVE;
  #endif
#else
  //RTL env
  if (*(uint32_t *)__lds_rtl_case == (uint32_t)RTL_MAGIC) {
    if((bootm == BOOTM_LPDDR4_WITH_INTLEAVE) || (bootm == BOOTM_DDR_WITH_INTLEAVE) ){
      use_intleave = USE_INTLEAVE;
    }
  }else{
    //read sw in fpga 
    use_intleave = readl(ITCS_S_SAP_BASE + 0x8) & 0xf;
  }
#endif

  ddr_intleave_init();
  
  printf("\nSoC Testbench: ROM\n");

#ifdef REBOOT_STRESS_TEST
  union {
    uint32_t boot_cnt;
    uint8_t boot_cnt_byte[4];
  } boot_cnt;

  for (int i = 0; i < 4; i++)
    boot_cnt.boot_cnt_byte[i] = rtc_info_get(RSTUNCLR, i);

  printf("Boot count: %u\n", boot_cnt.boot_cnt);

  boot_cnt.boot_cnt++;

  for (int i = 0; i < 4; i++)
    rtc_info_set(RSTUNCLR, i, boot_cnt.boot_cnt_byte[i]);

#ifdef MMC0_REBOOT_TEST
extern int itcs_sdmmc_simple_init(int devn);

  if (itcs_sdmmc_simple_init(1) < 0)
#endif
  {
    rtc_set_event(RTC_SOFTRESET);
  }
#endif /* REBOOT_STRESS_TEST */

#ifndef CONFIG_COMPILE_ASIC
  if (*(uint32_t *)__lds_rtl_case == (uint32_t)RTL_MAGIC)
#endif
  {

#ifdef CONFIG_BOOT_OTHER_CORE
  #if defined(CONFIG_TB_RUN_DDR) || defined(CONFIG_TB_RUN_DDR1)
    uint64_t boot_addr = ITCS_CDDR_ADDR;
    sysmap_config_region();
    printf("soc.bin would run in c920 ddr\n");
    ddr_init(bootm);
    if((bootm == BOOTM_LPDDR4_DDR1_NO_INTLEAVE) || (bootm == BOOTM_DDR1_NO_INTLEAVE)){
      boot_addr = ITCS_CDDR_END;
    }

    #ifdef CONFIG_COMPILE_ASIC
      if (load_payload(PAYLOAD_LOAD_ADDR) != 0) {
        puts("Load " PAYLOAD_NAME " failed\n");
        goto err;
      }
      tstc();
    #endif

    itcs_core_enable(CPU, 0, boot_addr, 0);

  #else
    #ifdef CONFIG_COMPILE_ASIC
        if (load_payload(PAYLOAD_LOAD_ADDR) != 0) {
          puts("Load " PAYLOAD_NAME " failed\n");
          goto err;
        }
        tstc();
        itcs_core_enable(CPU, 0, PAYLOAD_LOAD_ADDR, 0);
    #else
        itcs_core_enable(CPU, 0, soc_base, 0);
    #endif
  #endif//end of defined(CONFIG_TB_RUN_DDR) || defined(CONFIG_TB_RUN_DDR1)
#else // else for #ifdef CONFIG_BOOT_OTHER_CORE
  #if defined(CONFIG_TB_RUN_DDR) || defined(CONFIG_TB_RUN_DDR1)
    printf("soc.bin would run in e906 ddr\n");
    ddr_init(bootm);
    udelay(1);

    #ifdef CONFIG_COMPILE_ASIC
      if (load_payload(PAYLOAD_LOAD_ADDR) != 0) {
        puts("Load " PAYLOAD_NAME " failed\n");
        goto err;
      }
        tstc();
    #endif
    asm volatile("jalr ra, %0;" ::"r"(ITCS_SDDR_ADDR));

  #else
    /* for cache lite malloc */
    #ifdef CONFIG_E906
        itcs_module_enable(CPU, "ddr");
    #endif

    #ifdef CONFIG_COMPILE_ASIC
        if (load_payload(PAYLOAD_LOAD_ADDR) != 0) {
          puts("Load " PAYLOAD_NAME " failed\n");
          goto err;
        }
        tstc();
        asm volatile("jalr ra, %0;" ::"r"(PAYLOAD_LOAD_ADDR));
    #else
        asm volatile("jalr ra, %0;" ::"r"(soc_base));
    #endif
  #endif
#endif//end #ifdef CONFIG_BOOT_OTHER_CORE
  }

#ifndef CONFIG_COMPILE_ASIC
  else{
    uint64_t boot_addr = ITCS_CDDR_ADDR;
    sysmap_config_region();

    printf("soc.bin would run in c920 ddr0 FPGA\n");
    writel(0x0, ITCS_C_SYSM_MPU0_BASE + 0X28);//enable ddr0
    itcs_module_enable(CPU, "ddr"); //init ddr0
    itcs_core_enable(CPU, 0, boot_addr, 0);
    for (;;);
  }
#endif

#ifdef CONFIG_COMPILE_ASIC
	for (;;)
		;
#endif

#if !defined(CONFIG_COMPILE_RTL) || defined(CONFIG_TB)
  /* call init functions */
  __initcall();
#endif

  /* enter shell */
  printf("\n\n");
#ifdef CONFIG_COMPILE_RTL
#ifdef CONFIG_TB
  /* judge RTL is relevant environment */
  if (try_rtl())
    for (;;)
      ;
#endif
#else

#ifdef CONFIG_LIB_SHELL
  main_loop();
#endif
#endif

err:
  for (;;)
    ;
  return 0;
}

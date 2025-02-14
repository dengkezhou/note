/*
 * Copyright (C) intchains Holding Limited
 */

/******************************************************************************
 * @file     wdt-main.c
 * @brief    watch dog testBench
 * @version  V1.0
 * @date     03.28 2022

 * @name     wdt-main
 * author    jason.liu
 ******************************************************************************/
#include <common.h>
#include <command.h>
#include <testbench.h>
#include <malloc.h>
#include <wdt.h>
#include <irq.h>
#include <asm/io.h>
#include <getopt.h>

#define WDT_FLAG_REG (ITCS_R_BASE + 0XC0)
#define WDT_RESTART_COUNT_REG (ITCS_R_BASE + 0X100)
#define WDT_RESET_FLAG 0x66
#define WDT_EXTERNAL_FLAG 0x88

int exit_flg;
static unsigned long long wdt_ticks;
extern int __lds_print[];

static void wdt_show_usage(void) {
  printf("Usage: wdt [OPTION]...\n\n");
  printf("-h, --help\t\tcommand help\n");
  printf("-c, --cpu\t\tCPU_WDT\n");
  printf("-s, --sap\t\tSAP_WDT\n");
  printf("-r, --reset\t\treset  case\n");
  printf("-e, --external\t\ttest external case\n");
  printf("-a, --restart\t\ttest restart&interrupt&stop case\n");
}

void wdt_irq_test_handler (wdt_handler_t* handler ) 
{
  DEBUG_WDT_LOG("wdt irq time: %d\n", get_timer(wdt_ticks));
  uint32_t restart_count =  readl(WDT_RESTART_COUNT_REG);
  if(restart_count >= 3){
    writel(0x00, WDT_RESTART_COUNT_REG);
    printf("Test WDT Restart Pass.\n");
#ifdef CONFIG_COMPILE_RTL
    exit_flg = 1;
#endif
    return;
  }

  DEBUG_WDT_LOG("WDT irq arrive.\n");
  writel(++restart_count, WDT_RESTART_COUNT_REG);
  itcs_wdt_feed(handler);
  itcs_wdt_start(handler);

}

static int wdt_reset_test(WDT WDTx){ 
    int ret;
    struct wdt_handler_s* handler;
    struct wdt_init_s init;
    init.callback = NULL;
    init.mode = MODE_RST;
    init.WDTx = WDTx;   
#ifdef CONFIG_COMPILE_RTL
    init.timeout_ms = 1;
#else
    init.timeout_ms = 1000;
#endif

    handler = itcs_wdt_init(&init);
    if(handler == NULL){
         return -1;
    }

    writel(WDT_RESET_FLAG, WDT_FLAG_REG);
    udelay(1);
    printf("testebench wdt reset case, set 0x%x register to 0x%x\n",WDT_FLAG_REG, readl(WDT_FLAG_REG));

#ifdef CONFIG_COMPILE_RTL
    // WDT DEBUG MODE, FAST
    writel(0x137085, ITCS_S_WDT_BASE + 0x10);
    itcs_wdt_counter_ctrl(handler, 0, 0);
    itcs_wdt_feed(handler);
#endif
    
    ret = itcs_wdt_start(handler);
    if (ret != CDNS_RET_SUCCESS) {
        return -1;
    }

#ifdef CONFIG_COMPILE_RTL
    while(1){
        udelay(1);
        if(exit_flg){
            return 0;
        }
    }
#endif

    return 0;
}

static int wdt_external_test(WDT WDTx){ 
    int ret;
    struct wdt_handler_s* handler;
    struct wdt_init_s init;
    init.callback = NULL;
    init.mode = MODE_EXT;
    init.WDTx = WDTx;
#ifdef CONFIG_COMPILE_RTL
    init.timeout_ms = 1;
#else
    init.timeout_ms = 1000;
#endif

    // check if reset case already pass.
    uint32_t reset_flag = readl(WDT_FLAG_REG);
    printf("testebench wdt external case, read 0x%x register = 0x%x\n",WDT_FLAG_REG, reset_flag);
    if(reset_flag == WDT_EXTERNAL_FLAG){
        writel(0x0, WDT_FLAG_REG);
        printf("Test WDT External Pass.\n");
        return 0;
    }

    handler = itcs_wdt_init(&init);
    if(handler == NULL){
         return -1;
    }

    writel(WDT_EXTERNAL_FLAG, WDT_FLAG_REG);
    udelay(1);
    printf("testebench wdt external case, set 0x%x register to 0x%x\n",WDT_FLAG_REG, readl(WDT_FLAG_REG));

#ifdef CONFIG_COMPILE_RTL
    // WDT DEBUG MODE, FAST
    writel(0x137085, ITCS_S_WDT_BASE + 0x10);
    itcs_wdt_counter_ctrl(handler, 0, 0);
    itcs_wdt_feed(handler);
#endif

    ret = itcs_wdt_start(handler);
    if (ret != CDNS_RET_SUCCESS) {
        return -1;
    }

#ifdef CONFIG_COMPILE_RTL
    while(1){
        udelay(1);
        if(exit_flg){
            return 0;
        }
    }
#endif

    return 0;
}
  
static int wdt_restart_test(WDT WDTx){ 
    int ret;
    struct wdt_handler_s* handler;
    struct wdt_init_s init;
    init.callback = wdt_irq_test_handler;
    init.mode = MODE_IRQ;
    init.WDTx = WDTx;
#ifdef CONFIG_COMPILE_RTL
    init.timeout_ms = 1;
#else
    init.timeout_ms = 1000;
#endif

    handler = itcs_wdt_init(&init);
    if(handler == NULL){
        return -1;
    }
    
#ifdef CONFIG_COMPILE_RTL
    // WDT DEBUG MODE, FAST
    writel(0x137085, ITCS_S_WDT_BASE + 0x10);
    itcs_wdt_counter_ctrl(handler, 0, 0);
    itcs_wdt_feed(handler);
#endif

    //restart count 1
    writel(0x01, WDT_RESTART_COUNT_REG);

    wdt_ticks = get_timer(0);
    ret = itcs_wdt_start(handler);
    if (ret != CDNS_RET_SUCCESS) {
        return -1;
    }

#ifdef CONFIG_COMPILE_RTL
    while(1){
        udelay(1);
        if(exit_flg){
            return 0;
        }
    }
#endif

    return 0;
}

int wdt_main(int argc, char *argv[]) {
  int option_index = 0, c, ret = 0;
  int wdt_case = 0;
  int wdt_port = 0;
  uint32_t reset_flag;
  exit_flg = 0;
  static const char short_options[]         = "hcsrea";
  static const struct option long_options[] = {{"help", 0, 0, 'h'},
                                               {"cpu", 0, 0, 'c'},
                                               {"sap", 0, 0, 's'},
                                               {"reset", 0, 0, 'r'},
                                               {"external", 0, 0, 'e'},
                                               {"restart", 0, 0, 'a'},
                                               {0, 0, 0, 0}};
  
    // check if reset case already pass.
    reset_flag = readl(WDT_FLAG_REG);
    printf("testebench wdt case, read 0x%x register = 0x%x\n",WDT_FLAG_REG, reset_flag);
    if(reset_flag == WDT_RESET_FLAG){
        writel(0x0, WDT_FLAG_REG);
        printf("Test WDT Reset Pass.\n");
        udelay(1000);
        return 0;
    }else if(reset_flag == WDT_EXTERNAL_FLAG){
        writel(0x0, WDT_FLAG_REG);
        printf("Test WDT External Pass.\n");
        udelay(1000);
        return 0;
    }

  /* Get all arguements. */
  while ((c = getopt_long(argc, argv, short_options, long_options,
                          &option_index)) != -1) {
    switch (c) {
    case 'c':
      wdt_port = CPU_WDT;
      break;
    case 's':
      wdt_port = SAP_WDT;
      break;
    case 'r':
      wdt_case = 1;
      break;
    case 'e':
      wdt_case = 2;
      break;
    case 'a':
      wdt_case = 3;
      break;
    case 'h':
    default:
      wdt_show_usage();
      ret = -1;
      return ret;
    }
  }

  if (optind == 1) {
    wdt_show_usage();
    ret = -1;
    return ret;
  }

  if(wdt_case == 1){
    printf("WDT Reset Test...\n");
    wdt_reset_test(SAP_WDT);
  }else if(wdt_case == 2){
    printf("WDT External Test...\n");
    wdt_external_test(CPU_WDT);
  }else if(wdt_case == 3){
    printf("WDT Restart Test...\n");
    wdt_restart_test(wdt_port);
  }else{
    printf("WDT Test should not be here!\n");
  }
  
  return 0;
}

void wdt_init(void) { register_testbench("wdt", wdt_main , NULL); }

testbench_init(wdt_init);

/*
 * Copyright (C) intchains Holding Limited
 */

/******************************************************************************
 * @file     arm-spi-main.c
 * @brief    arm spi testBench
 * @version  V1.0
 * @date     11.08 2022

 * @name     arm-spi-main
 * @author   jason.liu
 ******************************************************************************/
#include <common.h>
#include <command.h>
#include <testbench.h>
#include <spi.h>
#include <stdbool.h>
#include <malloc.h>
#include <getopt.h>
#include "spi_flash.h"
#include "pads.h"

#ifdef CONFIG_COMPILE_RTL
#define SPI_BUF_MAX_SIZE 32
#else
#define SPI_BUF_MAX_SIZE 64
#endif

#define SPI_FLASH_TEST_ADDR 0

#define ARM_SPI_DEFAULT_INIT_PARAM                                             \
  {                                                                            \
    SPI0, SPI_TYPE_ARM_SSP, false, false, SPI_MODE_MASTER, SPI_DATASIZE_8BIT,  \
        SPI_POLARITY_LOW, SPI_PHASE_1EDGE, 1000000, HW_SPI_CS_MODE, 0, NULL    \
  }

#define SPI_FLASH_DEFAULT_INIT_PARAM                                           \
  {                                                                            \
    false, SPI_TYPE_ARM_SSP, NULL, SPI0, SPI_DATASIZE_8BIT, 0, 1000000,        \
        HW_SPI_CS_MODE, 0, 1, SPI_NOR_FLASH, false                             \
  }
static void spi_show_usage(void) {
  printf("Usage: dwc-spi [OPTION]...\n\n");
  printf("-h, --help\t\tcommand help\n");
  printf("-m, --master\t\t0-3\n");
  printf("-s, --slave\t\t0-3\n");
  printf("-e, --mode\t\t0-3\n");
  printf("-d, --dma\t\tenable dma\n");
  printf("-r, --ddr\t\tdual date rate\n");
  printf("-l, --loop\t\tloopback mode\n");
  printf("-n, --nand\t\tspi nand flash test\n");
  printf("-o, --nor\t\tspi nor flash test\n");
  printf("-f, --func\t\tspi function mode test\n");
}

struct pads_modules_bundle rtl_spi1_func_test_iolist[] = {
    {"spi1-func1-cpads-29-32", PADSRANGE(29, 32), PADS_FUNC1, PADS_PULL_UP, CPU},
    {"spi1-func1-cpads-80-83", PADSRANGE(80, 83), PADS_FUNC1, PADS_PULL_UP, CPU},
    {NULL},
};

struct pads_modules_bundle rtl_spi2_func_test_iolist[] = {
    {"spi2-func1-cpads-35-38", PADSRANGE(35, 38), PADS_FUNC1, PADS_PULL_UP, CPU},
    {NULL},
};

struct pads_modules_bundle rtl_spi3_func_test_iolist[] = {
    {"spi3-func1-cpads-23-26", PADSRANGE(23, 26), PADS_FUNC1, PADS_PULL_UP, CPU},
    {"spi3-func1-cpads-39-42", PADSRANGE(39, 42), PADS_FUNC1, PADS_PULL_UP, CPU},
    {NULL},
};

struct spi_test_st {
  bool dma;
  bool ddr;
  bool nand;
  bool nor;
  bool loop;
  int mode;
  int master;
  int slave;
  bool func;
};

static int check_args(struct spi_test_st *test) {
  if (test->mode > 3) {
    printf("spi mode error, should be 0-3\n");
    return -1;
  }

  if (test->master > 3) {
    printf("spi master index error, should be 0-3\n");
    return -1;
  }

  if (test->slave > 3) {
    printf("spi slave index error, should be 0-3\n");
    return -1;
  }

  return 0;
}

static SPI get_SPIx(int index) {
  switch (index) {
  case 0:
    return SPI0;
    break;
  case 1:
    return SPI1;
    break;
  case 2:
    return SPI2;
    break;
  case 3:
    return SPI3;
    break;
  default:
    return SPI0;
    break;
  }
}

static void get_pha_pol_from_mode(int mode, uint32_t *CLKPolarity,
                                  uint32_t *CLKPhase) {
  switch (mode) {
  case 0:
    *CLKPolarity = 0;
    *CLKPhase    = 0;
    break;
  case 1:
    *CLKPolarity = 0;
    *CLKPhase    = 1;
    break;
  case 2:
    *CLKPolarity = 1;
    *CLKPhase    = 0;
    break;
  case 3:
    *CLKPolarity = 1;
    *CLKPhase    = 1;
    break;
  }
}

static unsigned long tbh_spi_get_base_addr(SPI SPIx) {
  switch (SPIx) {
  case SPI0:
    return ITCS_S_SPI0_BASE;
    break;
  case SPI1:
    return ITCS_C_SPI1_BASE;
    break;
  case SPI2:
    return ITCS_C_SPI2_BASE;
    break;
  case SPI3:
    return ITCS_C_SPI3_BASE;
    break;
  default:
    return ITCS_S_SPI0_BASE;
    break;
  }
}

static int loopback_test(int master) {
  int res;
  SPI_HandleTypeDef *handler;
  unsigned long regs;
  uint32_t tmpReg;
  SPI_InitTypeDef init = ARM_SPI_DEFAULT_INIT_PARAM;

  uint8_t spi_rx_buffer[SPI_BUF_MAX_SIZE];
  uint8_t spi_tx_buffer[SPI_BUF_MAX_SIZE];

  init.SPIx        = get_SPIx(master);
  init.CLKPolarity = SPI_POLARITY_LOW;
  init.CLKPhase    = SPI_PHASE_1EDGE;

  handler = itcs_spi_init(&init);

  regs = tbh_spi_get_base_addr(master);

  tmpReg = readl(regs + 0x04);
  tmpReg &= (~(0x1UL << 1));
  writel(tmpReg, regs + 0x04);

  tmpReg |= 1;
  writel(tmpReg, regs + 0x04);

  tmpReg = readl(regs + 0x04);
  tmpReg |= ((0x1UL << 1));
  writel(tmpReg, regs + 0x04);

  for (int i = 0; i < SPI_BUF_MAX_SIZE; i++) {
    spi_tx_buffer[i] = i;
  }

  itcs_spi_transmit_receive(handler, spi_tx_buffer, spi_rx_buffer,
                            SPI_BUF_MAX_SIZE, true);

  res = memcmp(spi_tx_buffer, spi_rx_buffer, SPI_BUF_MAX_SIZE);
  if (!res) {
    printf("Test SPI Loopback Pass.\n");
  }
  return 0;
}

/* All test case in Interconnecting the two SPIs */
static int two_spi_connect_rw_test(bool dma, bool ddr, int mode, int master,
                                   int slave) {
  SPI_InitTypeDef init_a = ARM_SPI_DEFAULT_INIT_PARAM;
  SPI_InitTypeDef init_b = ARM_SPI_DEFAULT_INIT_PARAM;
  SPI_HandleTypeDef *handler_a, *handler_b;

  uint8_t spi_a_tx_buffer[SPI_BUF_MAX_SIZE];
  uint8_t spi_b_rx_buffer[SPI_BUF_MAX_SIZE];

  init_a.enable_dma = dma;
  init_b.enable_dma = dma;
  init_a.enable_ddr = ddr;
  init_b.enable_ddr = ddr;
  init_a.SPIx       = get_SPIx(master);
  init_b.SPIx       = get_SPIx(slave);
  init_b.mode       = SPI_MODE_SLAVE;
  get_pha_pol_from_mode(mode, &init_a.CLKPolarity, &init_a.CLKPhase);
  get_pha_pol_from_mode(mode, &init_b.CLKPolarity, &init_b.CLKPhase);

  handler_a = itcs_spi_init(&init_a);
  handler_b = itcs_spi_init(&init_b);

  for (int i = 0; i < SPI_BUF_MAX_SIZE; i++) {
    spi_a_tx_buffer[i] = 0xaa;
  }

  itcs_spi_receive(handler_b, spi_b_rx_buffer, SPI_BUF_MAX_SIZE, false);
  itcs_spi_transmit(handler_a, spi_a_tx_buffer, SPI_BUF_MAX_SIZE, true);
  while (1) {
    if (itcs_spi_get_transfer_status(handler_b, false) == SPI_STA_RX_COMPLETE) {
      if (memcmp(spi_b_rx_buffer, spi_a_tx_buffer, SPI_BUF_MAX_SIZE)) {
        printf("send:\n");
        for (int i = 0; i < SPI_BUF_MAX_SIZE; i++) {
          if ((i % 0x10) == 0)
            printf("\n");
          printf("0x%x ", spi_a_tx_buffer[i]);
        }
        printf("\n");
        printf("recv:\n");

        for (int i = 0; i < SPI_BUF_MAX_SIZE; i++) {
          if ((i % 0x10) == 0)
            printf("\n");
          printf("0x%x ", spi_b_rx_buffer[i]);
        }
        printf("\n");
        printf("The bytes received is not same as transmitted!\n");
        return -1;
      } else {
        if (dma) {
          printf("Test SPI DMA Pass.\n");
        } else if (ddr) {
          printf("Test SPI DDR Pass.\n", mode);
        } else {
          printf("Test SPI Interrupt-mode%d Pass.\n", mode);
        }
        return 0;
      }
    }
  }
  return 0;
}

/* SPI flash test case */
static int spi_flash_rw_test(int master, int test_idx) {

#ifdef CONFIG_DRV_SPI_FLASH
  int res;
  struct spi_flash_obj *flash;
  struct spi_flash_init_s init = SPI_FLASH_DEFAULT_INIT_PARAM;

  uint8_t *spi_rx_buffer = (uint8_t *)malloc(SPI_BUF_MAX_SIZE);
  uint8_t *spi_tx_buffer = (uint8_t *)malloc(SPI_BUF_MAX_SIZE);
  switch(master){
  case 0:
    init.cs_pin  = 7;
    init.cs_mode = GPIO_CS_MODE;
  break;  
  case 1:
    init.cs_pin  = 48;
    init.cs_mode = GPIO_CS_MODE;
  break;
  case 2:
    init.cs_pin  = 54;
    init.cs_mode = GPIO_CS_MODE;
  break;
  case 3:
    init.cs_pin  = 58;
    init.cs_mode = GPIO_CS_MODE;
  break;
  default:
    printf("please specify a spi flash master\n");
    return -1;
  break;
  }
  
  

  init.spi_instance = get_SPIx(master);
  if (test_idx == 1) {
    init.flash_type      = SPI_NOR_FLASH;
    init.compatible_name = "spi_nor";
  } else if(test_idx == 0){
    init.flash_type      = SPI_NAND_FLASH;
    init.compatible_name = "spi_nand";
  } 

  flash = itcs_spi_flash_init(&init);

  for (int i = 0; i < SPI_BUF_MAX_SIZE; i++) {
    spi_tx_buffer[i] = i;
  }

  itcs_spi_flash_write(flash, spi_tx_buffer, SPI_FLASH_TEST_ADDR,
                       SPI_BUF_MAX_SIZE);
  itcs_spi_flash_read(flash, spi_rx_buffer, SPI_FLASH_TEST_ADDR,
                      SPI_BUF_MAX_SIZE);

  res = memcmp(spi_tx_buffer, spi_rx_buffer, SPI_BUF_MAX_SIZE);
  if (!res) {
    if (test_idx == 1) {
      printf("Test SPI Connect With Nor Flash Pass.\n");
    } else if (test_idx == 0) {
      printf("Test SPI Connect With Nand Flash Pass.\n");
    } 
  } else {
    printf("tx data:\n");
    for (int i = 0; i < SPI_BUF_MAX_SIZE; i++) {
      if ((i % 0x10) == 0)
        printf("\n");
      printf("0x%x ", spi_tx_buffer[i]);
    }
    printf("\n");

    printf("rx data:\n");
    for (int i = 0; i < SPI_BUF_MAX_SIZE; i++) {
      if ((i % 0x10) == 0)
        printf("\n");
      printf("0x%x ", spi_rx_buffer[i]);
    }
    printf("\n");

    printf("Inconsistent reading and writing of SPI flash.\n");
    free(spi_tx_buffer);
    free(spi_rx_buffer);
    return -1;
  }
  free(spi_tx_buffer);
  free(spi_rx_buffer);
#endif // CONFIG_DRV_SPI_FLASH
  return 0;
}

static int spi_func_test_single(int master, struct pads_modules_bundle* m_pads, 
                                int slave, struct pads_modules_bundle* s_pads){
  SPI_InitTypeDef init_a = ARM_SPI_DEFAULT_INIT_PARAM;
  SPI_InitTypeDef init_b = ARM_SPI_DEFAULT_INIT_PARAM;
  SPI_HandleTypeDef *handler_a, *handler_b;

  uint8_t spi_a_tx_buffer[SPI_BUF_MAX_SIZE];
  uint8_t spi_b_rx_buffer[SPI_BUF_MAX_SIZE];
  if(m_pads){
    init_a.pads = m_pads;
  }
  if(s_pads){
    init_b.pads = s_pads;
  }
  init_a.SPIx       = get_SPIx(master);
  init_b.SPIx       = get_SPIx(slave);
  init_b.mode       = SPI_MODE_SLAVE;
  get_pha_pol_from_mode(0, &init_a.CLKPolarity, &init_a.CLKPhase);
  get_pha_pol_from_mode(0, &init_b.CLKPolarity, &init_b.CLKPhase);

  handler_a = itcs_spi_init(&init_a);
  handler_b = itcs_spi_init(&init_b);

  for (int i = 0; i < SPI_BUF_MAX_SIZE; i++) {
    spi_a_tx_buffer[i] = 0xaa;
  }

  itcs_spi_receive(handler_b, spi_b_rx_buffer, SPI_BUF_MAX_SIZE, false);
  itcs_spi_transmit(handler_a, spi_a_tx_buffer, SPI_BUF_MAX_SIZE, true);
  while (1) {
    if (itcs_spi_get_transfer_status(handler_b, false) == SPI_STA_RX_COMPLETE) {
      if (memcmp(spi_b_rx_buffer, spi_a_tx_buffer, SPI_BUF_MAX_SIZE)) {
        printf("send:\n");
        for (int i = 0; i < SPI_BUF_MAX_SIZE; i++) {
          if ((i % 0x10) == 0)
            printf("\n");
          printf("0x%x ", spi_a_tx_buffer[i]);
        }
        printf("\n");
        printf("recv:\n");

        for (int i = 0; i < SPI_BUF_MAX_SIZE; i++) {
          if ((i % 0x10) == 0)
            printf("\n");
          printf("0x%x ", spi_b_rx_buffer[i]);
        }
        printf("\n");
        printf("The bytes received is not same as transmitted!\n");
        return -1;
      } else {
        return 0;
      }
    }
  }
  return 0;
}

static int spi_func_test(int master){
    int fail = 0;
    if(master == 0){
        if(!spi_func_test_single(1, &rtl_spi1_func_test_iolist[0], 3, &rtl_spi3_func_test_iolist[0])){
            printf("Test SPI Function Mode %s with %s Pass.\n", rtl_spi1_func_test_iolist[0].name, rtl_spi3_func_test_iolist[0].name);
        }else{
            fail++;
        }
    }else if(master == 1){
        if(!spi_func_test_single(1, &rtl_spi1_func_test_iolist[1], 3, &rtl_spi3_func_test_iolist[1])){
            printf("Test SPI Function Mode %s with %s Pass.\n", rtl_spi1_func_test_iolist[1].name, rtl_spi3_func_test_iolist[1].name);
        }else{
            fail++;
        }
    }else if(master == 2){
        if(!spi_func_test_single(0, NULL, 2, &rtl_spi2_func_test_iolist[0])){
            printf("Test SPI Function Mode %s Pass.\n", rtl_spi2_func_test_iolist[0].name);
        }else{
            fail++;
        }
    }

    if(fail){
        return -1;
    }
    printf("Test SPI Function Mode Pass.\n");
    return 0;
}

static int start_test(struct spi_test_st *test) {
  if (test->loop) {
    printf("spi loopback test......\n");
    loopback_test(test->master);
  } else if (test->nand) {
    printf("spi nand flash test......\n");
    spi_flash_rw_test(test->master, 0);
  } else if (test->nor) {
    printf("spi nor flash test......\n");
    spi_flash_rw_test(test->master, 1);
  } else if (test->ddr) {
    printf("spi ddr test......\n");
    two_spi_connect_rw_test(test->dma, true, test->mode, test->master,
                            test->slave);
  } else if (test->dma) {
    printf("spi dma test......\n");
    two_spi_connect_rw_test(true, false, test->mode, test->master, test->slave);
  } else if (test->func) {
    printf("spi function mode test......\n");
    spi_func_test(test->master);
  }  else {
    printf("spi%d master spi%d slave connect test......\n", test->master,
           test->slave);
    two_spi_connect_rw_test(false, false, test->mode, test->master,
                            test->slave);
  }
  return 0;
}

#if 0
static int easy_test() {
#if 1
  itcs_pads_set_mode(CPU, 47, PADS_MODE_OUT, 1);
  itcs_pads_set_mode(SAP, 5, PADS_MODE_OUT, 1);
  while (1) {
    itcs_pads_set_value(SAP, 5, 1);
    itcs_pads_set_value(CPU, 47, 1);
    udelay(1000 * 1000);
    itcs_pads_set_value(SAP, 5, 0);
    itcs_pads_set_value(CPU, 47, 0);
    udelay(1000 * 1000);
  }
#endif
#if 0
  SPI_InitTypeDef init_a = ARM_SPI_DEFAULT_INIT_PARAM;
  SPI_InitTypeDef init_b = ARM_SPI_DEFAULT_INIT_PARAM;
  SPI_HandleTypeDef *handler_a;
  SPI_HandleTypeDef *handler_b;
  //uint8_t spi_a_rx_buffer[SPI_BUF_MAX_SIZE];
  uint8_t spi_a_tx_buffer[SPI_BUF_MAX_SIZE];
  uint8_t spi_b_rx_buffer[SPI_BUF_MAX_SIZE];
  //uint8_t spi_b_tx_buffer[SPI_BUF_MAX_SIZE];

  init_a.SPIx       = get_SPIx(2);
  //init_a.cs_mode    = GPIO_CS_MODE;
  //init_a.cs_pin     = 54; 

  init_b.SPIx       = get_SPIx(3);
  init_b.mode       = SPI_MODE_SLAVE;
  get_pha_pol_from_mode(0, &init_a.CLKPolarity, &init_a.CLKPhase);
  get_pha_pol_from_mode(0, &init_b.CLKPolarity, &init_b.CLKPhase);

  for (int i = 0; i < SPI_BUF_MAX_SIZE; i++) {
    spi_a_tx_buffer[i] = i;
  }
  
  handler_a = itcs_spi_init(&init_a);
  handler_b = itcs_spi_init(&init_b);

  itcs_spi_receive(handler_b, spi_b_rx_buffer, SPI_BUF_MAX_SIZE, false);
  itcs_spi_transmit(handler_a, spi_a_tx_buffer, SPI_BUF_MAX_SIZE, true);
  while(1){
    if (itcs_spi_get_transfer_status(handler_b, false) == SPI_STA_RX_COMPLETE) {
        printf("recv:");
        for(int i = 0; i<SPI_BUF_MAX_SIZE ; i++)
          printf(" 0x%x",spi_b_rx_buffer[i]);
        printf("\n");
        return 0;
    }
    udelay(1000);
  }
#endif
  return 0;
}
#endif

static int arm_spi_tb_main(int argc, char *argv[]) {
  int option_index = 0, c, ret = 0;
  struct spi_test_st spi_test       = {false, false, false, false, false, 0, -1, -1, false};
  static const char short_options[] = "hm:s:e:dfrlnof";
  static const struct option long_options[] = {
      {"help", 0, 0, 'h'}, {"master", 1, 0, 'm'}, {"slave", 1, 0, 's'},
      {"mode", 1, 0, 'e'}, {"dma", 0, 0, 'd'},    {"ddr", 0, 0, 'r'},
      {"loop", 0, 0, 'l'}, {"nand", 0, 0, 'n'},   {"nor", 0, 0, 'o'},
      {"func", 0, 0, 'f'}, {0, 0, 0, 0}};

  /* Get all arguements. */
  while ((c = getopt_long(argc, argv, short_options, long_options,
                          &option_index)) != -1) {
    switch (c) {
    case 'm':
      spi_test.master = simple_strtoul(optarg, NULL, 10);
      break;
    case 's':
      spi_test.slave = simple_strtoul(optarg, NULL, 10);
      break;
    case 'e':
      spi_test.mode = simple_strtoul(optarg, NULL, 10);
      break;
    case 'd':
      spi_test.dma = true;
      break;
    case 'f':
      spi_test.func = true;
      break;
    case 'r':
      spi_test.ddr = true;
      break;
    case 'l':
      spi_test.loop = true;
      break;
    case 'n':
      spi_test.nand = true;
      break;
    case 'o':
      spi_test.nor = true;
      break;
    default:
      spi_show_usage();
      ret = -1;
      return ret;
    }
  }

  if (optind == 1) {
    spi_show_usage();
    ret = -1;
    return ret;
  }

  /* Check arguements. */
  if (check_args(&spi_test)) {
    printf("cmdline param invalild, please refer to test case document.\n");
    ret = -1;
    return ret;
  }

  /* Test case entry */
  start_test(&spi_test);

  return 0;
}

void arm_spi_tb_init(void) { register_testbench("spi", arm_spi_tb_main, NULL); }

testbench_init(arm_spi_tb_init);

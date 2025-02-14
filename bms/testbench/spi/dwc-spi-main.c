/*
 * Copyright (C) intchains Holding Limited
 */

/******************************************************************************
 * @file     dwc-spi-main.c
 * @brief    dwc spi testBench
 * @version  V1.0
 * @date     07.28 2022

 * @name     dwc-spi-main
 * @author   jason.liu
 ******************************************************************************/
#include <common.h>
#include <command.h>
#include <testbench.h>
#include <spi.h>
#include <stdbool.h>
#include <getopt.h>
#include "spi_flash.h"

#ifdef CONFIG_COMPILE_RTL
#define SPI_BUF_MAX_SIZE 32
#else
#define SPI_BUF_MAX_SIZE 32
#endif

#define SPI_FLASH_TEST_ADDR 0

#define SPI_FLASH_DEFAULT_INIT_PARAM                                           \
  {                                                                            \
    false, SPI_TYPE_DWC_SSI, NULL, SPI0, SPI_DATASIZE_8BIT, 0, 1000000, HW_SPI_CS_MODE, 0, 1,    \
        SPI_NOR_FLASH, false                                                   \
  }

static void spi_show_usage(void) {
  printf("Usage: dwc-spi [OPTION]...\n\n");
  printf("-h, --help\t\tcommand help\n");
  printf("-m, --master\t\t0-3\n");
  printf("-s, --slave\t\t0-3\n");
  printf("-e, --mode\t\t0-3\n");
  printf("-d, --dma\t\tenable dma\n");
  printf("-r, --ddr\t\tdual date rate\n");
  printf("-n, --nand\t\tdevice loopback mode\n");
  printf("-o, --nor\t\tdevice loopback mode\n");
}

struct spi_test_st {
  bool dma;
  bool ddr;
  bool nand;
  bool nor;
  int master;
  int slave;
};

static int check_args(struct spi_test_st *test) {
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

/* SPI nor flash test case */
static int spi_nor_flash_rw_test(int master) {
  int res;
  struct spi_flash_obj *flash;
  struct spi_flash_init_s init = SPI_FLASH_DEFAULT_INIT_PARAM;
  init.cs_mode                 = GPIO_CS_MODE;
  init.cs_pin                  = 48;
  init.flash_type              = SPI_NOR_FLASH;
  init.compatible_name         = "spi_nor";

  uint8_t spi_rx_buffer[SPI_BUF_MAX_SIZE];
  uint8_t spi_tx_buffer[SPI_BUF_MAX_SIZE];

  init.spi_instance = master;

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
    printf("Test SPI Connect With Nor Flash Pass.\n");
  } else {
    printf("Inconsistent reading and writing of SPI flash.\n");
    return -1;
  }

  return 0;
}

/* SPI nand flash test case */
static int spi_nand_flash_rw_test(int master) {
  int res;
  struct spi_flash_obj *flash;
  struct spi_flash_init_s init = SPI_FLASH_DEFAULT_INIT_PARAM;
  init.flash_type              = SPI_NAND_FLASH;
  init.cs_mode                 = GPIO_CS_MODE;
  init.cs_pin                  = 54;
  init.compatible_name         = "spi_nand";

  uint8_t spi_tx_buffer[SPI_BUF_MAX_SIZE];
  uint8_t spi_rx_buffer[SPI_BUF_MAX_SIZE];

  init.spi_instance = master;

  flash = itcs_spi_flash_init(&init);

  for (int i = 0; i < SPI_BUF_MAX_SIZE; i++) {
    spi_tx_buffer[i] = i;
  }

  itcs_spi_flash_write(flash, spi_tx_buffer, SPI_FLASH_TEST_ADDR,
                       SPI_BUF_MAX_SIZE);

  itcs_spi_flash_read(flash, spi_rx_buffer, SPI_FLASH_TEST_ADDR,
                      SPI_BUF_MAX_SIZE);
  
  for (int i = 0; i < SPI_BUF_MAX_SIZE; i++) {
    printf("read buf[%d] = %d\n",i ,spi_rx_buffer[i]);
  }
  
  res = memcmp(spi_tx_buffer, spi_rx_buffer, SPI_BUF_MAX_SIZE);
  if (!res) {
    printf("Test SPI Connect With Nand Flash Pass.\n");
  } else {
    printf("Inconsistent reading and writing of SPI flash.\n");
    return -1;
  }

  return 0;
}

static int start_test(struct spi_test_st *test) {
  if (test->nand) {
    spi_nand_flash_rw_test(test->master);
  } else if (test->nor) {
    spi_nor_flash_rw_test(test->master);
  }
  return 0;
}

static int dwc_spi_main(int argc, char *argv[]) {
  int option_index = 0, c, ret = 0;
  struct spi_test_st spi_test       = {false, false, false, false, -1, -1};
  static const char short_options[] = "hm:s:drno";
  static const struct option long_options[] = {
      {"help", 0, 0, 'h'}, {"master", 1, 0, 'm'}, {"slave", 1, 0, 's'},
      {"dma", 0, 0, 'd'},  {"ddr", 0, 0, 'r'},    {"nand", 0, 0, 'n'},
      {"nor", 0, 0, 'o'},  {0, 0, 0, 0}};
  // easy_test();
  // return 0;
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
    case 'd':
      spi_test.dma = true;
      break;
    case 'r':
      spi_test.ddr = true;
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

void dwc_spi_init(void) { register_testbench("spi", dwc_spi_main, NULL); }

testbench_init(dwc_spi_init);

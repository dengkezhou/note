/*
 * Copyright (C) intchains Holding Limited
 */

/******************************************************************************
 * @file     xspi-main.c
 * @brief    xspi testBench
 * @version  V1.0
 * @date     08.12 2022

 * @name     xspi-main
 * @author   jason.liu
 ******************************************************************************/
#include <common.h>
#include <command.h>
#include <testbench.h>
#include <stdbool.h>
#include <getopt.h>
#include "xspi_flash.h"
#include "spi_flash.h"
#include "image.h"
#include <malloc.h>
#include <pads.h>

#define SPI_FLASH_TEST_ADDR (0)
#ifdef CONFIG_COMPILE_RTL
#define XSPI_BUF_MAX_SIZE   (256)
#else
#define XSPI_BUF_MAX_SIZE   (256)
#endif

enum Test_MEM {
  XSPI_DD_TEST        = 1,
  XSPI_NOR_TEST       = 3,
  XSPI_NAND_TEST      = 4,
  XSPI_HYP_FLASH_TEST = 5,
  XSPI_HYP_RAM_TEST   = 6
};

enum Test_Type { XSPI_TYPE_OSPI = 0, XSPI_TYPE_QSPI = 1 };

enum Test_Line {
  XSPI_LINE_1 = 1,
  XSPI_LINE_2 = 2,
  XSPI_LINE_4 = 4,
  XSPI_LINE_8 = 8
};

int dd_test;
bool boot_test;
bool xip_test;
bool ddr;
bool cpu_acess;
static enum Test_MEM test_mem;
static enum Test_Type test_port;
static int test_mode;
static enum Test_Line test_line;

static void spi_show_usage(void) {
  printf("Usage: xspi [OPTION]...\n\n");
  printf("-h, --help\t\tcommand help\n");
  printf("-p, --port\t\t0(qspi) / 1(ospi)\n");
  printf("-l, --line\t\t1 / 2 / 4 / 8\n");
  printf("-m, --mode\t\t0-3(direct/stig/pio/cdma)\n");
  printf("-w, --workmode\t\twork mode test\n");
  printf("-r, --nor_flash\t\tspi nor flash test\n");
  printf("-n, --nand_flash\t\tspi nand flash test\n");
  printf("-y, --hyperflash\t\thyperflash test\n");
  printf("-a, --hyperram\t\thyperram test\n");
  printf("-f, --devdis\t\t1-auto,2-sdfp ,device discovery test\n");
  printf("-d, --dtr\t\tdouble data rete test\n");
  printf("-b, --boot\t\t1-pre_load, 2-boot status, boot test\n");
  printf("-x, --xip\t\txip test\n");
  printf("-c, --cpu\t\taccess by cpu\n");
}

#define XSPI_DEFAULT_INIT_PARAM                                                \
  { QSPI, 0, 1, SPI_NOR_FLASH, true, 0, 0, 0, 0 }

#define XSPI_FLASH_DEFAULT_INIT_PARAM                                           \
  {                                                                             \
    true, 0, NULL, QSPI, SPI_DATASIZE_8BIT, 0, 1000000, HW_SPI_CS_MODE, 0, 1,   \
        SPI_NOR_FLASH, false, false                                             \
  }

#define TEST_WORK_MODE_STR "Test %s %d-wire %s Pass"

static int check_args() {
  if (test_mode > 3) {
    printf("spi test mode error, should be 0-3\n");
    return -1;
  }

  if (test_port > 1) {
    printf("xspi test type error, should be 0/1\n");
    return -1;
  }
  if (test_port == 0) {
    if ((test_line != 1) && (test_line != 2) && (test_line != 4) &&
        (test_line != 8)) {
      printf("xspi slave index error, should be 1/2/4/8\n");
      return -1;
    }
  } else {
    if ((test_line != 1) && (test_line != 2) && (test_line != 4)) {
      printf("xspi slave index error, should be  1/2/4\n");
      return -1;
    }
  }

  return 0;
}

static int xspi_dd_test(bool aut) {

  struct spi_flash_init_s init = XSPI_FLASH_DEFAULT_INIT_PARAM;
  struct spi_flash_obj *obj;
  bool res;
  
  printf("xspi device discovery test start\n");
  init.spi_instance = test_port;
  init.line_num = test_line;
  obj = itcs_spi_flash_init(&init);
  if (aut == true) {
    // full auto dd test
    res = xspi_flash_device_discovery(obj->xhandler, true);
   
    if (res == true) {
      uint32_t status;
      int cnt = 100;
      do{
        status =  readl(obj->xhandler->reg_base + 0x260);
        printf("xSPI Device Discovery Status = 0x%x\n", status);
        if(status & 0x4){
            printf("Test xSPI FULL AutoMated Mode DD Pass.\n");
            return 0;
        }
#ifdef CONFIG_COMPILE_RTL
        udelay(100);
#else
        udelay(1000* 100);
#endif
        cnt --;
      }while(cnt);
      
    } 
    printf("Test xSPI SFDP FULL AutoMated Mode DD Failed.\n");
    return -1;
  } else {
    // give preconfig sfdp dd test
    obj->xhandler->init.line_num = test_line;
    res = xspi_flash_device_discovery(obj->xhandler, false);

    if (res == true) {
      uint32_t status;
      int cnt = 100;
      do{
        status =  readl(obj->xhandler->reg_base + 0x260);
        printf("xSPI Device Discovery Status = 0x%x\n", status);
        if(status & 0x4){
            printf("Test xSPI SFDP Pre-configured Mode DD Pass.\n");
            return 0;
        }
#ifdef CONFIG_COMPILE_RTL
        udelay(100);
#else
        udelay(1000* 100);
#endif
        cnt --;
      }while(cnt);
    }
    printf("Test xSPI SFDP Pre-configured Mode DD Failed.\n");
    return -1;
  }

  return 0;
}

static int xspi_boot_test() {
  bool res;
  uint8_t* boot_dest_ptr = (uint8_t*)malloc(BMS_IMAGE_LENGTH);
  printf("xspi boot test start\n");
  // write image to spi flash
  bms_image_init();
  bms_image_head.image_dest_addr  = (uintptr_t)boot_dest_ptr;
  res = xspi_write_image_to_flash(test_port, (uint8_t*) (&bms_image_head), sizeof(struct bms_image_head_s), bms_image.image_ptr, bms_image.image_length, bms_image_head.image_start_addr);
  if(res == false){
    printf("Test XSPI Boot Failed---write image error\n");
    return -1;
  }

  xspi_flash_boot(test_port);

  if(!memcmp((uint8_t*)(bms_image_head.image_dest_addr), bms_image.image_ptr, bms_image.image_length)){
    printf("Test %s Boot Pass\n", test_port == 0 ? "OSPI":"QSPI");
  }else{
    printf("Test XSPI Boot Failed\n");
    printf("boot data:\n");
    for(int i = 0; i < bms_image.image_length; i++){
      printf("0x%x ", boot_dest_ptr[i]);
      if(i % 16 == 15){
        printf("\n");
      }
    }
    printf("\n");
    printf("image data:\n");
    for(int i = 0; i < bms_image.image_length; i++){
      printf("0x%x ", bms_image.image_ptr[i]);
      if(i % 16 == 15){
        printf("\n");
      }
    }
    printf("\n");
  }

  
  return 0;
}

static int xspi_xip_test() {
  int ret;
  struct spi_flash_init_s init = XSPI_FLASH_DEFAULT_INIT_PARAM;
  struct spi_flash_obj *obj;
  init.line_num     = test_line;
  init.spi_instance = test_port;
  if (test_mem == XSPI_NOR_TEST) {
#ifdef CONFIG_COMPILE_RTL
    init.compatible_name = "gd_nor";
#else
    init.compatible_name = "xspi_nor";
#endif
    init.flash_type = SPI_NOR_FLASH;
  } else if (test_mem == XSPI_NAND_TEST) {
    init.compatible_name = "xspi_nand";
    init.flash_type = SPI_NAND_FLASH;
  }
  
  printf("xspi workmode test start...\n");

  obj = itcs_spi_flash_init(&init);
  if(!obj)
    return -1;
  ret = xspi_nor_flash_xip(obj);
  if(!ret){
    printf("Test xSPI XIP Pass!\n");
    return 0;
  }else{
    printf("Test xSPI XIP Failed!\n");
    return -1;
  }
}

static int xspi_dtr_test() {
  uint32_t ret;
  struct spi_flash_init_s init = XSPI_FLASH_DEFAULT_INIT_PARAM;
  struct spi_flash_obj *obj;
  uint8_t* xspi_rx_buffer = (uint8_t *)malloc(XSPI_BUF_MAX_SIZE);
  uint8_t* xspi_tx_buffer = (uint8_t *)malloc(XSPI_BUF_MAX_SIZE);
  init.ddr = true;
  init.line_num     = test_line;
  init.spi_instance = test_port;
  if (test_mem == XSPI_NOR_TEST) {
#ifdef CONFIG_COMPILE_RTL
    init.compatible_name = "gd_nor";
#else
    init.compatible_name = "xspi_nor";
#endif
  } else if (test_mem == XSPI_NAND_TEST) {
    init.compatible_name = "xspi_nand";
    init.flash_type = SPI_NAND_FLASH;
  }
  
  printf("xspi dtr test start...\n");

  obj = itcs_spi_flash_init(&init);
  if(!obj)
    return -1;

  for (int i = 0; i < XSPI_BUF_MAX_SIZE; i++) {
    xspi_tx_buffer[i] = i;
  }
  
  obj->xhandler->work_mode = CDNS_XSPI_MODE_STIG;

  ret = itcs_spi_flash_write(obj, xspi_tx_buffer, SPI_FLASH_TEST_ADDR,
                             XSPI_BUF_MAX_SIZE);
  if (ret != XSPI_BUF_MAX_SIZE) {
    printf("xspi write error!\n");
    return -1;
  }
  
  ret = itcs_spi_flash_read(obj, xspi_rx_buffer, SPI_FLASH_TEST_ADDR,
                            XSPI_BUF_MAX_SIZE);
  if (ret != XSPI_BUF_MAX_SIZE) {
    printf("xspi read error!\n");
    return -1;
  }

  if (memcmp(xspi_tx_buffer, xspi_rx_buffer, XSPI_BUF_MAX_SIZE)) {
    printf("The bytes read is not same as write!\n");
    printf("tx data:\n");
    for(int i = 0; i < XSPI_BUF_MAX_SIZE; i++) {
        printf("%x ", xspi_tx_buffer[i]);
        if(i % 16 == 15)
            printf("\n");
    }
    printf("\n");
    printf("rx data:\n");
    for(int i = 0; i < XSPI_BUF_MAX_SIZE; i++) {
        printf("%x ", xspi_rx_buffer[i]);
        if(i % 16 == 15)
            printf("\n");
    }
    printf("\n");
    return -2;
  } else {
    char str[256] = {0} ;
    sprintf(str, "Test %s DTR Pass", (test_port == XSPI_TYPE_OSPI ? "ospi":"qspi"));
    printf("%s\n", str);
  }
  


  return 0;
}

static int xspi_work_mode_test() {
  uint32_t ret;
  char *work_mode = NULL;
  struct spi_flash_init_s init = XSPI_FLASH_DEFAULT_INIT_PARAM;
  struct spi_flash_obj *obj;
  uint8_t* xspi_rx_buffer = (uint8_t *)malloc(XSPI_BUF_MAX_SIZE);
  uint8_t* xspi_tx_buffer = (uint8_t *)malloc(XSPI_BUF_MAX_SIZE);

  init.line_num     = test_line;
  init.spi_instance = test_port;
  if (test_mem == XSPI_NOR_TEST) {
#ifdef CONFIG_COMPILE_RTL
  if (test_line == 8)
    init.compatible_name = "gd_nor";
  else
    init.compatible_name = "mxic_nor";
#else
    init.compatible_name = "xspi_nor";
#endif
    init.flash_type = SPI_NOR_FLASH;
  } else if (test_mem == XSPI_NAND_TEST) {
    init.compatible_name = "xspi_nand";
    init.flash_type = SPI_NAND_FLASH;
  }
  
  init.ddr = ddr;
  
  printf("xspi workmode test start...\n");

  obj = itcs_spi_flash_init(&init);
  if(!obj)
    return -1;

  for (int i = 0; i < XSPI_BUF_MAX_SIZE; i++) {
    xspi_tx_buffer[i] = (uint8_t)(i & 0xff);
  }
  


  switch (test_mode) {
  case 0:
    work_mode                = "DIRECT";
    obj->xhandler->work_mode = CDNS_XSPI_MODE_DIRECT;
    break;
  case 1:
    work_mode                = "STIG";
    obj->xhandler->work_mode = CDNS_XSPI_MODE_STIG;
    break;
  case 2:
    work_mode                = "PIO";
    obj->xhandler->work_mode = CDNS_XSPI_MODE_ACMD_PIO;
    break;
  case 3:
    work_mode                = "CDMA";
    obj->xhandler->work_mode = CDNS_XSPI_MODE_ACMD_CMDA;
    break;
  default:
    printf("please select work mode\n");
    return -1;
  }

  ret = itcs_spi_flash_write(obj, xspi_tx_buffer, SPI_FLASH_TEST_ADDR,
                            XSPI_BUF_MAX_SIZE);
  if (ret != XSPI_BUF_MAX_SIZE) {
    printf("xspi write error!\n");
    return -1;
  }
  ret = itcs_spi_flash_read(obj, xspi_rx_buffer, SPI_FLASH_TEST_ADDR,
                            XSPI_BUF_MAX_SIZE);
  if (ret != XSPI_BUF_MAX_SIZE) {
    printf("xspi read error!\n");
    return -1;
  }


  if (memcmp(xspi_tx_buffer, xspi_rx_buffer, XSPI_BUF_MAX_SIZE)) {
    printf("The bytes read is not same as write!\n");
    printf("tx data:\n");
    for(int i = 0; i < XSPI_BUF_MAX_SIZE; i++) {
        printf("%x ", xspi_tx_buffer[i]);
        if(i % 16 == 15)
            printf("\n");
    }
    printf("\n");
    printf("rx data:\n");
    for(int i = 0; i < XSPI_BUF_MAX_SIZE; i++) {
        printf("%x ", xspi_rx_buffer[i]);
        if(i % 16 == 15)
            printf("\n");
    }
    printf("\n");

    obj->xhandler->work_mode = CDNS_XSPI_MODE_STIG;
    obj->xhandler->init.line_num = 1;
    ret = itcs_spi_flash_read(obj, xspi_rx_buffer, SPI_FLASH_TEST_ADDR,
                            XSPI_BUF_MAX_SIZE);
    printf("stig rx data:\n");
    for(int i = 0; i < XSPI_BUF_MAX_SIZE; i++) {
        printf("%x ", xspi_rx_buffer[i]);
        if(i % 16 == 15)
            printf("\n");
    }
    printf("\n");

    return -2;
  } else {
    char str[256] = {0} ;
    sprintf(str, TEST_WORK_MODE_STR, (test_port == XSPI_TYPE_OSPI ? "OSPI":"QSPI"), test_line, work_mode);
    printf("%s\n", str);
  }
  


  return 0;
}

static int xspi_cpu_access_test() {
  uint32_t ret;
  struct spi_flash_init_s init = XSPI_FLASH_DEFAULT_INIT_PARAM;
  struct spi_flash_obj *obj;
  uint8_t* xspi_rx_buffer = (uint8_t *)malloc(XSPI_BUF_MAX_SIZE);
  uint8_t* xspi_tx_buffer = (uint8_t *)malloc(XSPI_BUF_MAX_SIZE);

  init.line_num     = test_line;
  init.spi_instance = test_port;
  if (test_mem == XSPI_NOR_TEST) {
#ifdef CONFIG_COMPILE_RTL
  if (test_line == 8)
    init.compatible_name = "gd_nor";
  else
    init.compatible_name = "mxic_nor";
#else
    init.compatible_name = "xspi_nor";
#endif
    init.flash_type = SPI_NOR_FLASH;
  } else if (test_mem == XSPI_NAND_TEST) {
    init.compatible_name = "xspi_nand";
    init.flash_type = SPI_NAND_FLASH;
  }
  
  init.ddr = ddr;
  
  printf("xspi cpu access test start...\n");

  obj = itcs_spi_flash_init(&init);
  if(!obj)
    return -1;
  if(obj->xhandler == NULL){
    return -1;
  }

  for (int i = 0; i < XSPI_BUF_MAX_SIZE; i++) {
    xspi_tx_buffer[i] = (uint8_t)(0xaa & 0xff);
  }
  
  obj->xhandler->work_mode = CDNS_XSPI_MODE_DIRECT;
  obj->xhandler->cpu_access = true;

  ret = itcs_spi_flash_write(obj, xspi_tx_buffer, SPI_FLASH_TEST_ADDR,
                             XSPI_BUF_MAX_SIZE);
  if (ret != XSPI_BUF_MAX_SIZE) {
    printf("xspi write error!\n");
    return -1;
  }
 
  ret = itcs_spi_flash_read(obj, xspi_rx_buffer, SPI_FLASH_TEST_ADDR,
                            XSPI_BUF_MAX_SIZE);
  if (ret != XSPI_BUF_MAX_SIZE) {
    printf("xspi read error!\n");
    return -1;
  }

  if (memcmp(xspi_tx_buffer, xspi_rx_buffer, XSPI_BUF_MAX_SIZE)) {
    printf("The bytes read is not same as write!\n");
    printf("tx data:\n");
    for(int i = 0; i < XSPI_BUF_MAX_SIZE; i++) {
        printf("%x ", xspi_tx_buffer[i]);
        if(i % 16 == 15)
            printf("\n");
    }
    printf("\n");
    printf("rx data:\n");
    for(int i = 0; i < XSPI_BUF_MAX_SIZE; i++) {
        printf("%x ", xspi_rx_buffer[i]);
        if(i % 16 == 15)
            printf("\n");
    }
    printf("\n");
    return -2;
  } else {
    for(int i = 0; i < XSPI_BUF_MAX_SIZE; i++) {
        printf("%x ", xspi_rx_buffer[i]);
        if(i % 16 == 15)
            printf("\n");
    }
    printf("\n");
    printf("Test CPU Access Pass\n");
  }
  
  return 0;
}

static int xspi_hyper_flash_test() {
  struct spi_flash_init_s init = XSPI_FLASH_DEFAULT_INIT_PARAM;
  struct spi_flash_obj *obj;

  uint8_t* xspi_rx_buffer = (uint8_t *)malloc(XSPI_BUF_MAX_SIZE);
  uint8_t* xspi_tx_buffer = (uint8_t *)malloc(XSPI_BUF_MAX_SIZE);

  init.line_num     = 8;
  init.spi_instance = 0;
  init.flash_type   = HYPER_FLASH;
  init.compatible_name = "xspi_hyper_flash";

  printf("xspi hyperflash test start\n");

  obj = itcs_spi_flash_init(&init);
  printf("xspi hyperflash init done.\n");

  for (int i = 0; i < XSPI_BUF_MAX_SIZE; i++) {
    xspi_tx_buffer[i] = i;
  }
  
  printf("xspi hyperflash write start ....\n");
  itcs_spi_flash_write(obj, xspi_tx_buffer, SPI_FLASH_TEST_ADDR,
                             XSPI_BUF_MAX_SIZE);
  printf("xspi hyperflash write done.\n");

  printf("xspi hyperflash read start ....\n");
  itcs_spi_flash_read(obj, xspi_rx_buffer, SPI_FLASH_TEST_ADDR,
                            XSPI_BUF_MAX_SIZE);
  printf("xspi hyperflash read done.\n");
  if (memcmp(xspi_tx_buffer, xspi_rx_buffer, XSPI_BUF_MAX_SIZE)) {
    printf("The bytes read is not same as write!\n");
    printf("tx data:\n");
    for(int i = 0; i < XSPI_BUF_MAX_SIZE; i++) {
        printf("%x ", xspi_tx_buffer[i]);
        if(i % 16 == 15)
            printf("\n");
    }
    printf("\n");
    printf("rx data:\n");
    for(int i = 0; i < XSPI_BUF_MAX_SIZE; i++) {
        printf("%x ", xspi_rx_buffer[i]);
        if(i % 16 == 15)
            printf("\n");
    }
    printf("\n");
    return -2;
  } else {
    printf("Test OSPI Connect With 8-wire HyperFLASH Pass.\n");
  }
  return 0;
}

static int xspi_hyper_ram_test() {
  struct spi_flash_init_s init = XSPI_FLASH_DEFAULT_INIT_PARAM;
  struct spi_flash_obj *obj;
  int tets_len = 128;
  uint8_t* xspi_rx_buffer = (uint8_t *)malloc(tets_len);
  uint8_t* xspi_tx_buffer = (uint8_t *)malloc(tets_len);

  init.line_num     = 8;
  init.spi_instance = 0;
  init.flash_type   = HYPER_RAM;
  init.compatible_name = "xspi_hyper_ram";
  
  printf("xspi hyperram test start\n");

  obj = itcs_spi_flash_init(&init);

  for (int i = 0; i < tets_len; i++) {
    xspi_tx_buffer[i] = i;
  }

  itcs_spi_flash_write(obj, xspi_tx_buffer, SPI_FLASH_TEST_ADDR,
                             tets_len);

  itcs_spi_flash_read(obj, xspi_rx_buffer, SPI_FLASH_TEST_ADDR,
                            tets_len);

  if (memcmp(xspi_tx_buffer, xspi_rx_buffer, tets_len)) {
    printf("The bytes read is not same as write!\n");
    printf("tx data:\n");
    for(int i = 0; i < tets_len; i++) {
        printf("%x ", xspi_tx_buffer[i]);
        if(i % 16 == 15)
            printf("\n");
    }
    printf("\n");
    printf("rx data:\n");
    for(int i = 0; i < tets_len; i++) {
        printf("%x ", xspi_rx_buffer[i]);
        if(i % 16 == 15)
            printf("\n");
    }
    printf("\n");
    return -2;
  } else {
    printf("Test OSPI Connect With 8-wire HyperRAM Pass.\n");
  }
  return 0;
}

#if 0
static struct spi_flash_obj * easy_test_init(int XSPIx, bool nand){
  struct spi_flash_init_s init = XSPI_FLASH_DEFAULT_INIT_PARAM;
  struct spi_flash_obj *obj;

  init.line_num     = 1;
  if(XSPIx == QSPI)
    init.spi_instance = QSPI;
  else
    init.spi_instance = OSPI;
  if(nand){
    init.compatible_name = "xspi_nand";
    init.flash_type = SPI_NAND_FLASH;  
  }else{
    init.compatible_name = "xspi_nor";
    init.flash_type = SPI_NOR_FLASH;
  }

  init.ddr = false;

  obj = itcs_spi_flash_init(&init);
  if(!obj)
    return NULL;
  return obj;
}

static void easy_test_read(struct spi_flash_obj *obj, int addr, int len, int mode)
{
    obj->xhandler->work_mode = mode;
    uint8_t* xspi_rx_buffer = (uint8_t *)malloc(len);

    itcs_spi_flash_read(obj, xspi_rx_buffer, addr,
                            len);

    printf("rx data start =%x, len=%d:\n", addr, len);
    for(int i = 0; i < len; i++) {
        printf("%x ", xspi_rx_buffer[i]);
        if(i % 16 == 15)
            printf("\n");
    }
    printf("\n");
}

static void easy_test_erase(struct spi_flash_obj *obj, int addr){
    if(obj->xhandler->init.flash_type == SPI_NOR_FLASH){
        itcs_spi_flash_erase(obj, SPI_FLASH_ERASE_SECTOR, addr);
    }else{
        itcs_spi_flash_erase(obj, SPI_FLASH_ERASE_BLOCK, addr);
    }
    
}

static void easy_test_write(struct spi_flash_obj *obj, int addr, int len, int mode)
{
    obj->xhandler->work_mode = mode;
    uint8_t* xspi_tx_buffer = (uint8_t *)malloc(len);
    for(int i = 0; i < len; i++) {
        xspi_tx_buffer[i] = i;
    }
    itcs_spi_flash_write(obj, xspi_tx_buffer, addr, len);
    printf("tx data start =%x, len=%d:\n", addr, len);
    for(int i = 0; i < len; i++) {
        printf("%x ", xspi_tx_buffer[i]);
        if(i % 16 == 15)
            printf("\n");
    }
    printf("\n");
}

static void easy_test(){
    struct spi_flash_obj *obj;
    obj = easy_test_init(QSPI, true);
    printf("-----------------read before erase ----------------\n");
    easy_test_read(obj, 0, 1024, CDNS_XSPI_MODE_STIG);
    easy_test_erase(obj, 0);
    printf("-----------------read after erase ----------------\n");
    easy_test_read(obj, 0, 1024, CDNS_XSPI_MODE_ACMD_PIO);
    easy_test_write(obj, 0, 1024, CDNS_XSPI_MODE_ACMD_PIO);
    printf("-----------------read after write ----------------\n");
    easy_test_read(obj, 0, 1024, CDNS_XSPI_MODE_ACMD_PIO);
    
    //easy_test_write(obj, 0, 1024, CDNS_XSPI_MODE_DIRECT);
    //easy_test_write(obj, 0, 1024, CDNS_XSPI_MODE_STIG);
    //easy_test_write(obj, 0, 1024, CDNS_XSPI_MODE_ACMD_PIO);
    //easy_test_write(obj, 0, 1024, CDNS_XSPI_MODE_ACMD_CMDA);

    //easy_test_read(obj, 0, 1024, CDNS_XSPI_MODE_DIRECT);
    //easy_test_read(obj, 0, 1024, CDNS_XSPI_MODE_STIG);
    //easy_test_read(obj, 0, 1024, CDNS_XSPI_MODE_ACMD_PIO);
    //easy_test_read(obj, 0, 1024, CDNS_XSPI_MODE_ACMD_CMDA);    
}

#endif

static int start_test() {
  switch (test_mem) {
  case XSPI_DD_TEST:
    if (dd_test == 1) {
      xspi_dd_test(true);
    } else if (dd_test == 2) {
      xspi_dd_test(false);
    }
    break;
  case XSPI_HYP_FLASH_TEST:
    xspi_hyper_flash_test();
    break;
  case XSPI_HYP_RAM_TEST:
    xspi_hyper_ram_test();
    break;
  default:
    if(ddr){
      return xspi_dtr_test();
    }
    if(cpu_acess){
      return xspi_cpu_access_test();
    }
    if (boot_test) {
      return xspi_boot_test();
    }else if(xip_test){
      return xspi_xip_test();
    }else{
        xspi_work_mode_test();
    }
    break;
  }
  return 0;
}

static int xspi_main(int argc, char *argv[]) {
#if 0
  easy_test();
  return 0;
#endif
  int option_index = 0, c, ret = 0;
  static const char short_options[]         = "hp:l:m:rnyadf:bxc";
  static const struct option long_options[] = {
      {"help", 0, 0, 'h'}, {"port", 1, 0, 'p'},  {"line", 1, 0, 'l'},
      {"mode", 1, 0, 'm'}, {"nor", 0, 0, 'r'},   {"nand", 0, 0, 'n'},
      {"hf", 0, 0, 'y'},   {"hr", 0, 0, 'a'},    {"ddr", 0, 0, 'd'},
      {"dd", 1, 0, 'f'},   {"boot", 0, 0, 'b'},  {"xip", 0, 0, 'x'}, 
      {"cpu", 0, 0, 'c'},  {0, 0, 0, 0}};

  boot_test      = false;
  ddr            = false;
  xip_test       = false;
  cpu_acess      = false;
  /* Get all arguements. */
  while ((c = getopt_long(argc, argv, short_options, long_options,
                          &option_index)) != -1) {
    switch (c) {
    case 'f':
      test_mem = XSPI_DD_TEST;
      dd_test  = simple_strtoul(optarg, NULL, 10);
      break;
    case 'b':
      boot_test = true;
      break;
    case 'a':
      test_mem = XSPI_HYP_RAM_TEST;
      break;
    case 'y':
      test_mem = XSPI_HYP_FLASH_TEST;
      break;
    case 'n':
      test_mem = XSPI_NAND_TEST;
      break;
    case 'r':
      test_mem = XSPI_NOR_TEST;
      break;
    case 'p':
      test_port = simple_strtoul(optarg, NULL, 10);
      break;
    case 'l':
      test_line = simple_strtoul(optarg, NULL, 10);
      break;
    case 'm':
      test_mode = simple_strtoul(optarg, NULL, 10);
      break;
    case 'd':
      ddr = true;
      break;
    case 'x':
      xip_test = true;
      break;
    case 'c':
      cpu_acess = true;
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
  if (check_args()) {
    printf("cmdline param invalild, please refer to test case document.\n");
    ret = -1;
    return ret;
  }

  /* Test case entry */
  start_test();

  return 0;
}

void xspi_init(void) { register_testbench("xspi", xspi_main, NULL); }

testbench_init(xspi_init);

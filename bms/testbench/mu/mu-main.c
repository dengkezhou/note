/*
 * Copyright (C) intchains Holding Limited
 */

/******************************************************************************
 * @file     mu-main.c
 * @brief    mu testBench
 * @version  V1.0
 * @date     09.06 2022

 * @name     mu-main
 * @author   jason.liu
 ******************************************************************************/
#include <common.h>
#include <stdio.h>
#include <command.h>
#include <testbench.h>
#include <malloc.h>
#include <irq.h>
#include <mu.h>
#include <asm/io.h>
#include <getopt.h>

#define MU_BUF_LEN 32

static void mu_show_usage(void) {
  printf("Usage: wdt [OPTION]...\n\n");
  printf("-h, --help\t\tcommand help\n");
  printf("-l, --local\t\tlocal CPU MU test\n");
  printf("-i, --irq\t\tirq group register,should be 0 / 1\n");
  printf("-p, --port\t\tmu port, 0:c_mu,1:s_mu\n");
  printf("-r, --rw\t\tread then write test\n");
  printf("-w, --wr\t\twrite then read test\n");
  printf("-a, --al\t\tatomic lock test\n");
  printf("-c, --cpu\t\tcpu side\n");
  printf("-s, --sap\t\tsap side\n");
}

static int mu_local_cpu_test(domain_t domain, int irq_group) {
  MU_Handler *a_handler = NULL;
  MU_Handler *b_handler = NULL;
  uint8_t a_tx_buf[MU_BUF_LEN];
  uint8_t a_rx_buf[MU_BUF_LEN];
  uint8_t b_tx_buf[MU_BUF_LEN];
  uint8_t b_rx_buf[MU_BUF_LEN];

  a_handler = itcs_mu_init(domain, MU_A_SIDE, irq_group);
  b_handler = itcs_mu_init(domain, MU_B_SIDE, irq_group);

  if (!a_handler || !b_handler)
    return -1;

  for (int i = 0; i < MU_BUF_LEN; i++) {
    a_tx_buf[i] = i;
  }

  itcs_mu_read(b_handler, b_rx_buf, MU_BUF_LEN, false);
  itcs_mu_write(a_handler, a_tx_buf, MU_BUF_LEN, true);
  while (1) {
    uint16_t status = itcs_mu_get_status(b_handler, MU_READ);
    if (status == MU_RX_COMPLETE) {
      if (memcmp(b_rx_buf, a_tx_buf, MU_BUF_LEN)) {
        printf("Test MU a->b Failed.\n");
        return -1;
      } else {
        memcpy(b_tx_buf, b_rx_buf, MU_BUF_LEN);
        itcs_mu_read(a_handler, a_rx_buf, MU_BUF_LEN, false);
        itcs_mu_write(b_handler, b_tx_buf, MU_BUF_LEN, true);
        while (1) {
          uint16_t status = itcs_mu_get_status(a_handler, MU_READ);
          if (status == MU_RX_COMPLETE) {
            if (memcmp(a_rx_buf, b_tx_buf, MU_BUF_LEN)) {
              printf("Test MU b->a Failed.\n");
              return -1;
            } else {
              printf("Test MU Pass.\n");
              return 0;
            }
          }
        }
      }
    }
    udelay(1000);
  }
}

static int mu_data_test(bool wr, domain_t domain, int mu_side, int irq_group) {
  MU_Handler *handler = NULL;

  uint8_t tx_buf[MU_BUF_LEN];
  uint8_t rx_buf[MU_BUF_LEN];
  if (wr) {
    DEBUG_LOG_MU("wr = true.\n");
  } else {
    DEBUG_LOG_MU("wr = false.\n");
  }

  if (domain == CPU) {
    DEBUG_LOG_MU("domain = CPU.\n");
  } else {
    DEBUG_LOG_MU("domain = SAP.\n");
  }

  if (mu_side == MU_A_SIDE) {
    DEBUG_LOG_MU("mu_side = MU_A_SIDE.\n");
  } else {
    DEBUG_LOG_MU("mu_side = MU_B_SIDE.\n");
  }

  DEBUG_LOG_MU("irq_group = %d.\n", irq_group);

  handler = itcs_mu_init(domain, mu_side, irq_group);

  if (!handler)
    return -1;

  for (int i = 0; i < MU_BUF_LEN; i++) {
    tx_buf[i] = i;
  }

  if (wr) {
    itcs_mu_read(handler, rx_buf, MU_BUF_LEN, false);
    while(1){
      uint32_t value = readl(handler->base_addr + MU_ATOMIC_LOCK_BASE_OFFSET );
      DEBUG_LOG_MU("read value =  %d.\n", value);
      if (value != 0x1) {
        udelay(1);
      }else{
        writel(0x0, handler->base_addr + MU_ATOMIC_LOCK_BASE_OFFSET);
        break;
      }
    }
    DEBUG_LOG_MU("prepare write.\n");
    itcs_mu_write(handler, tx_buf, MU_BUF_LEN, true);
    DEBUG_LOG_MU("write over.\n");
    while (1) {
      uint16_t status = itcs_mu_get_status(handler, MU_READ);
      if (status == MU_RX_COMPLETE) {
        if (memcmp(rx_buf, tx_buf, MU_BUF_LEN)) {
          printf("Test MU Failed.\n");
          return -1;
        } else {
          if (domain == CPU) {
            printf("Test C_MU ReadWrite Pass.\n");
          } else {
            printf("Test S_MU ReadWrite Pass.\n");
          }
          return 0;
        }
      }
      udelay(1);
    }
  } else {
    itcs_mu_read(handler, rx_buf, MU_BUF_LEN, false);
    DEBUG_LOG_MU("read opened.\n");
    writel(0x01, handler->base_addr + MU_ATOMIC_LOCK_BASE_OFFSET);
    DEBUG_LOG_MU("already write %d in atomic lock reg.\n",readl(handler->base_addr + MU_ATOMIC_LOCK_BASE_OFFSET ));
    while (1) {
      uint16_t status = itcs_mu_get_status(handler, MU_READ);
      if (status == MU_RX_COMPLETE) {
        itcs_mu_write(handler, rx_buf, MU_BUF_LEN, true);
      }
      udelay(1);
    }
  }
  return 0;
}

#define MU_ATOMIC_01 0X01
#define MU_ATOMIC_02 0X00
static int mu_atomic_lock_test(bool wr, domain_t domain, int mu_side) {
  MU_Handler *handler = NULL;
  handler             = itcs_mu_init(domain, mu_side, 0);
  int atomic_reg_num = 0;
  if (wr) {
      for (int i = 0; i < MU_ATOMIC_LOCK_REG_NUM; i++) {
        writel(MU_ATOMIC_01, handler->base_addr + MU_ATOMIC_LOCK_BASE_OFFSET + (i * 4));
      }
      while(1){
        for (int i = 0; i < MU_ATOMIC_LOCK_REG_NUM; i++) {
            uint32_t value =
                readl(handler->base_addr + MU_ATOMIC_LOCK_BASE_OFFSET + (i * 4));
            if (value != MU_ATOMIC_02) {
                udelay(1);
                atomic_reg_num = 0;
                break;
            }else{
                atomic_reg_num++;
                if (atomic_reg_num == MU_ATOMIC_LOCK_REG_NUM){
                    printf("Test %s Atomic Lock Pass.\n", (domain == CPU) ? "C_MU" : "S_MU");
                    return 0;
                }
            }
        }
      }
      return 0;
  }else{
    while(1){
        for (int i = 0; i < MU_ATOMIC_LOCK_REG_NUM; i++) {
            uint32_t value =
                readl(handler->base_addr + MU_ATOMIC_LOCK_BASE_OFFSET + (i * 4));
            if (value != MU_ATOMIC_01) {
                udelay(1);
                atomic_reg_num = 0;
                break;
            }else{
                atomic_reg_num++;
                if (atomic_reg_num == MU_ATOMIC_LOCK_REG_NUM){
                    for (int i = 0; i < MU_ATOMIC_LOCK_REG_NUM; i++) {
                        writel(MU_ATOMIC_02, handler->base_addr + MU_ATOMIC_LOCK_BASE_OFFSET + (i * 4));
                    }
                    return 0;
                }
            }
        }
    }
  }

  return 0;
}

int mu_main(int argc, char *argv[]) {
  int option_index = 0, c, ret = 0;
  static bool write_then_read               = false;
  static domain_t domain                    = CPU;
  static int mu_side                        = MU_A_SIDE;
  static bool atomic_lock_test              = false;
  static bool local_test                    = false;
  static int irq_group                      = 0;
  static int port                           = 0;
  static const char short_options[]         = "hli:p:rwacs";
  static const struct option long_options[] = {
      {"help", 0, 0, 'h'}, {"local", 0, 0, 'l'}, {"irq", 1, 0, 'i'},
      {"port", 1, 0, 'p'}, {"rw", 0, 0, 'r'},    {"wr", 0, 0, 'w'},
      {"al", 0, 0, 'a'},   {"cpu", 0, 0, 'c'},   {"sap", 0, 0, 's'},
      {0, 0, 0, 0}};

  /* Get all arguements. */
  while ((c = getopt_long(argc, argv, short_options, long_options,
                          &option_index)) != -1) {
    switch (c) {
    case 'l':
      local_test = true;
      break;
    case 'i':
      irq_group = simple_strtoul(optarg, NULL, 10);
      break;
    case 'a':
      atomic_lock_test = true;
      break;
    case 'p':
      port = simple_strtoul(optarg, NULL, 10);
      if (port == 0) {
        domain = CPU;
      } else {
        domain = SAP;
      }
      break;
    case 'r':
      write_then_read = false;
      break;
    case 'w':
      write_then_read = true;
      break;
    case 'c':
      mu_side = MU_B_SIDE;
      break;
    case 's':
      mu_side = MU_A_SIDE;
      break;
    default:
      mu_show_usage();
      ret = -1;
      return ret;
    }
  }

  if (optind == 1) {
    mu_show_usage();
    ret = -1;
    return ret;
  }
  if (local_test) {
    printf("MU Local Testing...\n");
    mu_local_cpu_test(domain, irq_group);
  } else if (atomic_lock_test) {
    printf("MU Atomic Lock Testing...\n");
    mu_atomic_lock_test(write_then_read, domain, mu_side);
  } else {
    printf("MU Data Testing...\n");
    mu_data_test(write_then_read, domain, mu_side, irq_group);
  }

  return 0;
}

void mu_init(void) { register_testbench("mu", mu_main, NULL); }

testbench_init(mu_init);

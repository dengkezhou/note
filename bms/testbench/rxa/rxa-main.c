/*
 * (C) Copyright 2000
 * Wolfgang Denk, DENX Software Engineering, wd@denx.de.
 *
 * See file CREDITS for list of people who contributed to this
 * project.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

/*
 * Memory Functions
 *
 * Copied from FADS ROM, Dan Malek (dmalek@jlc.net)
 */

#include <common.h>
#include <command.h>
#include <testbench.h>
#include <malloc.h>
#include <getopt.h>
#include <exports.h>
#include <rxa.h>
#include <linux/bitops.h>
#include <randomx-api.h>

enum {
  RXA_SINGLE_CMD_TEST,
  RXA_GENERAL_REG_TEST,
  RXA_STEP_MODE_TEST,
  RXA_BREAK_TEST,
  RXA_FETCH_WIDTH_TEST,
  RXA_STRESS_TEST,
  RXA_MINING_TEST,
  RXA_PBUF_TEST,
};

static char *rxa_command[8] = {"rxbench", "--jit", "--mine",    "--nonces",
                               "3",       "--rxa", "--softAes", "--fastCache"};

#define OFFSPREFETCH   0x300
#define OFFSREGF       OFFSPREFETCH + 0x80
#define OFFSCODE       OFFSREGF + 0x180
#define OFFSDAG        0x110000000
#define OFFSSCRATCHPAD 0x200000 // need align with SCRATCHPAD
#define OFFSCIPHERDECR 0x80

static void rxa_init_config(rxa_cfg_t *cfg) {
  if (!cfg)
    return;

  memset(cfg->e_or, 0, sizeof(cfg->e_or));
  cfg->e_and[0] = 0xffffffff;
  cfg->e_and[1] = 0x00ffffff;
  cfg->e_and[2] = 0xffffffff;
  cfg->e_and[3] = 0x00ffffff;
  memset(cfg->r, 0, sizeof(cfg->r));
  SET(exec_mode)     = RXAI_NORMAL;
  SET(fetch_width)   = RXAI_ISA_FETCH_WIDTH1;
  SET(cfg_cond_offs) = 8;
  SET(en_regf)       = true;
  SET(offs_prfc)     = OFFSPREFETCH;
  SET(offs_regf)     = OFFSREGF;
  SET(offs_code)     = OFFSCODE;
  SET(offs_spad)     = OFFSSCRATCHPAD;
  SET(offs_dag)      = OFFSDAG;
}

int ilog2(int data) {
  int i = -1;
  while (data) {
    data >>= 1;
    i++;
  }

  return i;
}

extern int rxa_single_isa_test(rxa_device_t *dev, char *name);
extern void rxa_isa_test_callback(void *data);
extern case_cmd_t instrs[];
extern int instrnums;
static int rxa_single_cmd_test(int idx, char *name, int bytes) {
  rxa_cfg_t cfg;
  rxa_device_t *dev;
  int ret;
  int nums = strcmp(name, "all") ? 1 : instrnums;

  for (int i = 0; i < nums; i++) {
    rxa_init_config(&cfg);
    dev = itcs_rxa_init(idx, &cfg, rxa_isa_test_callback, NULL);
    if (!dev) {
      printf("RXA INIT Err\n");
      return -1;
    }
    rxa_set_fetch_width(dev, ilog2(bytes));

    if (nums == 1)
      ret = rxa_single_isa_test(dev, name);
    else
      ret = rxa_single_isa_test(dev, instrs[i].name);

    itcs_rxa_exit(dev);

    if (ret < 0)
      break;
  }
  return ret;
}

typedef struct rxa_test {
  char *name;
  int mode;
  int para;
  int complete;
  rxa_device_t *dev;
} rxa_test_t;

#define RXA_TEST_CFG(test, _name, _mode, _para, _complete, _dev)               \
  test.name     = _name;                                                       \
  test.mode     = _mode;                                                       \
  test.para     = _para;                                                       \
  test.complete = _complete;                                                   \
  test.dev      = _dev;

void rxa_test_callback(void *data) {
  rxa_test_t *test   = (rxa_test_t *)data;
  uint64_t dbgval[2] = {0};
  uint64_t cmp;

  printf("RXA %s Callback\n", test->name);
  switch (test->mode) {
  case RXA_GENERAL_REG_TEST:
    if (test->para) {
      for (int i = x2; i < x31; i += 2) {
        cmp = 0x1111111111111111 * ((i - x0) / 2);
        rxa_dbg_readq(test->dev, i, dbgval);
        printf("dbgval[0] 0x%lx\n", dbgval[0]);
        if (dbgval[0] != cmp) {
          test->complete = -1;
          break;
        }
      }
    } else {
      for (int i = v2; i < v31; i += 2) {
        if (i == v30)
          cmp = 0xfff0000000000000UL; // float
        else
          cmp = 0x1111111111111111UL * ((i - v0) / 2);
        rxa_dbg_readq(test->dev, i, dbgval);
        printf("%d: 0x%lx, 0x%lx\n", i - v0, dbgval[0], dbgval[1]);
        if ((dbgval[0] != cmp) || (dbgval[1] != cmp)) {
          test->complete = -1;
          break;
        }
      }
    }
    break;
  case RXA_STEP_MODE_TEST:
    rxa_dbg_readq(test->dev, x4, dbgval);
    if (dbgval[0] != 0x2222222222222222UL) {
      test->complete = -1;
      return;
    }
    break;
  case RXA_BREAK_TEST:
    test->para++;
    rxa_dbg_readq(test->dev, x6, dbgval);
    cmp = 0x1111111111111111UL * test->para;
    if (test->para < 5) {
      if (dbgval[0] != cmp) {
        test->complete = -1;
        return;
      }
      rxa_start(test->dev);
    } else
      test->complete = 1;
    return;
  case RXA_FETCH_WIDTH_TEST:
    for (int i = x17; i < x25; i++) {
      if ((i - x17) < test->para)
        cmp = 0x2222222222222222UL;
      else
        cmp = 0;

      rxa_dbg_readq(test->dev, i, dbgval);
      if (dbgval[0] != cmp) {
        test->complete = -1;
        return;
      }
    }
    break;
  case RXA_STRESS_TEST:
    break;
  case RXA_MINING_TEST:
    break;
  default:
    printf("Unrecognized this callback: %d\n", test->mode);
    test->complete = -1;
    return;
  }

  if (!test->complete)
    test->complete = 1;
}

static int rxa_general_reg_test(int idx, int bytes) {
  rxa_cfg_t cfg;
  rxa_device_t *dev;
  rxa_test_t test;
  uint64_t dbgval[2] = {0};
  uint32_t *code;
  int ret;

  rxa_init_config(&cfg);
  dev = itcs_rxa_init(idx, &cfg, rxa_test_callback, &test);
  if (!dev) {
    printf("RXA INIT Err\n");
    return -1;
  }
  rxa_set_fetch_width(dev, ilog2(bytes));

  RXA_TEST_CFG(test, "XReg", RXA_GENERAL_REG_TEST, 1, 0, dev);
  code = rxa_get_code(dev);
  for (int i = x1; i < x31; i += 2) {
    dbgval[0] = 0x1111111111111111UL * (i / 2 + 1);
    rxa_dbg_writeq(dev, i, dbgval);
    RXAC(RXA_ISA_ADDI, (i + 1), i, 0, 0);
  }
  RXAC(RXA_ISA_END, 0, 0, 0, 0);

  rxa_start(dev);

  while (!test.complete)
    udelay(5);

  printf("Test RXA XReg %s\n", (test.complete > 0) ? "Pass" : "Failed");
  if (test.complete < 0)
    goto err;

  code = rxa_get_code(dev);
  rxa_set_code_offs(dev, cfg.offs_code);
  dbgval[0] = 0;
  rxa_dbg_writeq(dev, x1, dbgval);
  RXA_TEST_CFG(test, "VReg", RXA_GENERAL_REG_TEST, 0, 0, dev);
  for (int i = v1; i < v31; i += 2) {
    dbgval[0] = 0x1111111111111111UL * ((i - v0) / 2 + 1);
    dbgval[1] = 0x1111111111111111UL * ((i - v0) / 2 + 1);
    rxa_dbg_writeq(dev, i, dbgval);
    RXAC(RXA_ISA_VADD_D, (i + 1), i, 0, 0);
  }
  RXAC(RXA_ISA_END, 0, 0, 0, 0);

  rxa_start(dev);

  while (!test.complete)
    udelay(5);

  printf("Test RXA VReg %s\n", (test.complete > 0) ? "Pass" : "Failed");

err:
  itcs_rxa_exit(dev);
  return ret;
}

static int rxa_step_mode_test(int idx, int bytes) {
  rxa_cfg_t cfg;
  rxa_device_t *dev;
  rxa_test_t test;
  uint64_t dbgval[2] = {0};
  uint32_t *code;

  rxa_init_config(&cfg);
  dev = itcs_rxa_init(idx, &cfg, rxa_test_callback, &test);
  if (!dev) {
    printf("RXA INIT Err\n");
    return -1;
  }
  rxa_set_fetch_width(dev, ilog2(bytes));
  rxa_set_stepmode(dev, RXAI_STEP, 1);
  RXA_TEST_CFG(test, "Step", RXA_STEP_MODE_TEST, 0, 0, dev);

  code      = rxa_get_code(dev);
  dbgval[0] = 0x1111111111111111UL;
  rxa_dbg_writeq(dev, x1, dbgval);
  rxa_dbg_writeq(dev, x2, dbgval);
  rxa_dbg_writeq(dev, x3, dbgval);
  RXAC(RXA_ISA_ADD, x4, x2, 0, x1);
  RXAC(RXA_ISA_ADD, x4, x4, 0, x3);
  RXAC(RXA_ISA_END, 0, 0, 0, 0);
  rxa_start(dev);

  while (!test.complete)
    udelay(5);

  printf("Test RXA Step %s\n", (test.complete > 0) ? "Pass" : "Failed");
  itcs_rxa_exit(dev);
  return 0;
}

int rxa_break_test(int idx, int bytes) {
  rxa_cfg_t cfg;
  rxa_device_t *dev;
  rxa_test_t test;
  uint64_t dbgval[2] = {0};
  uint32_t *code;
  uint64_t index;

  rxa_init_config(&cfg);
  dev = itcs_rxa_init(idx, &cfg, rxa_test_callback, &test);
  if (!dev) {
    printf("RXA INIT Err\n");
    return -1;
  }
  rxa_set_fetch_width(dev, ilog2(bytes));
  RXA_TEST_CFG(test, "Break", RXA_BREAK_TEST, 0, 0, dev);

  code = rxa_get_code(dev);

  index     = (unsigned long)code - (unsigned long)rxa_get_sram(dev);
  dbgval[0] = 0x1111111111111111UL;
  rxa_dbg_writeq(dev, x1, dbgval);
  rxa_dbg_writeq(dev, x2, dbgval);
  rxa_dbg_writeq(dev, x3, dbgval);
  rxa_dbg_writeq(dev, x4, dbgval);
  rxa_dbg_writeq(dev, x5, dbgval);
  RXAC(RXA_ISA_ADD, x6, x1, 0, x0);
  rxa_set_break(dev, RXAI_BREAK_POINT0, index);
  RXAC(RXA_ISA_ADD, x6, x6, 0, x2);
  rxa_set_break(dev, RXAI_BREAK_POINT1, index + 4);
  RXAC(RXA_ISA_ADD, x6, x6, 0, x3);
  rxa_set_break(dev, RXAI_BREAK_POINT2, index + 8);
  RXAC(RXA_ISA_ADD, x6, x6, 0, x4);
  rxa_set_break(dev, RXAI_BREAK_POINT3, index + 12);
  RXAC(RXA_ISA_ADD, x6, x6, 0, x5);
  rxa_set_break(dev, RXAI_BREAK_POINT4, index + 16);
  RXAC(RXA_ISA_END, 0, 0, 0, 0);
  rxa_start(dev);

  while (!test.complete)
    udelay(5);

  printf("Test RXA Step %s\n", (test.complete > 0) ? "Pass" : "Failed");
  itcs_rxa_exit(dev);
  return 0;
}

int rxa_fetch_width_test(int idx, int bytes) {
  rxa_cfg_t cfg;
  rxa_device_t *dev;
  rxa_test_t test;
  uint64_t dbgval[2] = {0};
  uint32_t *code;

  rxa_init_config(&cfg);
  dev = itcs_rxa_init(idx, &cfg, rxa_test_callback, NULL);
  if (!dev) {
    printf("RXA INIT Err\n");
    return -1;
  }
  rxa_set_fetch_width(dev, ilog2(bytes));
  RXA_TEST_CFG(test, "Fetch Width", RXA_FETCH_WIDTH_TEST, bytes, 0, dev);

  code      = rxa_get_code(dev);
  dbgval[0] = 0x1111111111111111UL;
  for (int i = x1; i < x25; i++) {
    if (i < x17)
      // init src reg
      rxa_dbg_writeq(dev, i, dbgval);
    else
      // init dst reg
      rxa_dbg_writeq(dev, i, &dbgval[1]);
  }

  for (int i = x1; i < x17; i += 2)
    RXAC(RXA_ISA_ADD, x16 + i - x0, i + 1, 0, i);
  RXAC(RXA_ISA_END, 0, 0, 0, 0);
  rxa_start(dev);

  while (!test.complete)
    udelay(5);

  printf("Test RXA Step %s\n", (test.complete > 0) ? "Pass" : "Failed");
  itcs_rxa_exit(dev);
  return 0;
}
#ifdef CONFIG_RANDOMX_MINING
extern int rxa_mining_main(int argc, char **argv);
#endif
int rxa_dispatch_case(int cmd, int idx, char *name, int bytes) {
  int ret = -1;

  switch (cmd) {
  case RXA_SINGLE_CMD_TEST:
    ret = rxa_single_cmd_test(idx, name, bytes);
    break;
  case RXA_GENERAL_REG_TEST:
    ret = rxa_general_reg_test(idx, bytes);
    break;
  case RXA_STEP_MODE_TEST:
    ret = rxa_step_mode_test(idx, bytes);
    break;
  case RXA_BREAK_TEST:
    ret = rxa_break_test(idx, bytes);
    break;
  case RXA_FETCH_WIDTH_TEST:
    ret = rxa_fetch_width_test(idx, bytes);
    break;
  case RXA_STRESS_TEST:
#ifdef CONFIG_RANDOMX_MINING
    rxa_mining_main(8, rxa_command);
#endif
    break;
  case RXA_MINING_TEST: {
#ifdef CONFIG_RANDOMX_MINING
    rxa_mining_t *mining = rxa_mining_init(1, true, 3);
    rxa_work_t work      = {
        .work_id = 1,
        .blob    = {0x07, 0x07, 0xf7, 0xa4, 0xf0, 0xd6, 0x05, 0xb3, 0x03, 0x26,
                 0x08, 0x16, 0xba, 0x3f, 0x10, 0x90, 0x2e, 0x1a, 0x14, 0x5a,
                 0xc5, 0xfa, 0xd3, 0xaa, 0x3a, 0xf6, 0xea, 0x44, 0xc1, 0x18,
                 0x69, 0xdc, 0x4f, 0x85, 0x3f, 0x00, 0x2b, 0x2e, 0xea, 0x00,
                 0x00, 0x00, 0x00, 0x77, 0xb2, 0x06, 0xa0, 0x2c, 0xa5, 0xb1,
                 0xd4, 0xce, 0x6b, 0xbf, 0xdf, 0x0a, 0xca, 0xc3, 0x8b, 0xde,
                 0xd3, 0x4d, 0x2d, 0xcd, 0xee, 0xf9, 0x5c, 0xd2, 0x0c, 0xef,
                 0xc1, 0x2f, 0x61, 0xd5, 0x61, 0x09},
    };
    if (!mining) {
      printf("mining init Err\n");
      break;
    }

    rxa_mining_update_work(mining, &work);

    rxa_mining_start(mining);

    while (rxa_mining_status(mining) == RXA_RUNNING)
      rxa_mining_get_nonces(mining);

    rxa_mining_get_nonces(mining);
    rxa_mining_exit(mining);
#endif
  } break;
  case RXA_PBUF_TEST: {
    printf("RXA_PBUF_TEST\n");
    uint8_t *code = (uint8_t *)ITCS_RXA_DRAM_ADDR(0);
    itcs_module_enable(CPU, "rxa0");
    // int i = 4;
    for (;;) {
      for (int i = 1; i < 16; i <<= 1)
        for (int j = 0; j < 0x200000; j += i) {
          int val = j % 0xff;
          switch (i) {
          case 1:
            writeb(val, code + j);
            if (!(j % 100))
              printf("%p: val %d, %d\n", code + j, val, readb(code + j));
            if (val != readb(code + j)) {
              printf("Pbuf Memory%p(1 byte) Err: (0x%x, 0x%x)\n", code + j, val,
                     readb(code + j));
              return -1;
            }
            break;
          case 2:
            writew(val, code + j);
            if (!(j % 100))
              printf("%p: val %d, %d\n", code + j, val, readw(code + j));
            if (val != readw(code + j)) {
              printf("Pbuf Memory(2 byte) Err: (0x%x, 0x%x)\n", val,
                     readw(code + j));
              return -1;
            }
            break;
          case 4:
            // printf("val %d, code + j %p\n", val, code + j);
            // writel(val, code + j);
            *(uint32_t *)(code + j) = val;
            if (!(j % 100))
              printf("%p: val %d, %d\n", code + j, val,
                     *(uint32_t *)(code + j));
            if (val != *(uint32_t *)(code + j)) {
              printf("Pbuf Memory(4 byte) Err: (0x%x, 0x%x)\n", val,
                     readl(code + j));
              return -1;
            }
            break;
          case 8:
            *(uint64_t *)(code + j) = val;
            if (!(j % 100))
              printf("%p: val %d, %d\n", code + j, val,
                     *(uint64_t *)(code + j));
            if (val != *(uint64_t *)(code + j)) {
              printf("Pbuf Memory(4 byte) Err: (0x%x, 0x%x)\n", val,
                     readl(code + j));
              return -1;
            }
            break;
          default:
            printf("Do not support this mode: %d\n", i);
            return -1;
          }
        }
    }
    printf("Pbuf Memory Test Pass\n");
  } break;
  default:
    printf("Do not support this cmd: %d\n", cmd);
    return -1;
  }

  return ret;
}

static void rxa_show_usage(void) {
  printf("Usage: rxa [OPTION]...\n\n");
  printf("-h, --help\t\tcommand help\n");
  printf("--case\t\tcase id(0~6, single cmd, general reg, step, break, fetch "
         "width, stress, mining)\n");
  printf("--index\t\trxa id(0~23)\n");
  printf("--name\t\tif case id is single cmd, name can be NOP, LD, LD.ADD, "
         "...END\n");
  printf("\t\t\tif case id is crypto, name can be Blake2b, Aes1R4, Aes1R4 Hash "
         "or Aes4R4\n");
  printf("--bytes\t\tfetch width: 1, 2, 4 or 8\n");
}

int rxa_main(int argc, char *argv[]) {
  int option_index = 0, c, ret = 0;
  static const char short_options[]         = "c:i:n:b:h";
  static const struct option long_options[] = {
      {"case", 1, 0, 'c'},  {"index", 1, 0, 'i'}, {"name", 1, 0, 'n'},
      {"bytes", 1, 0, 'b'}, {"help", 0, 0, 'h'},  {0, 0, 0, 0},
  };
  int cmd = -1, bytes = 1, idx = 0;
  char *name = NULL;

  while ((c = getopt_long(argc, argv, short_options, long_options,
                          &option_index)) != -1) {
    switch (c) {
    case 'c':
      cmd = ustrtoul(optarg, NULL, 10);
      break;
    case 'i':
      idx = ustrtoul(optarg, NULL, 10);
      break;
    case 'n':
      name = optarg;
      break;
    case 'b':
      bytes = ustrtoul(optarg, NULL, 10);
      break;
    case 'h':
      rxa_show_usage();
      break;
    default:
      rxa_show_usage();
      ret = -1;
      goto err;
    }
  }

  if (optind == 1) {
    rxa_show_usage();
    ret = -1;
    goto err;
  }

  ret = rxa_dispatch_case(cmd, idx, name, bytes);
err:
  optind = 1;
  return ret;
}

void rxa_init(void) { register_testbench("rxa", rxa_main, NULL); }

testbench_init(rxa_init);

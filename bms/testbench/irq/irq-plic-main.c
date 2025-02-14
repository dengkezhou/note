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
#include <irq.h>
#include <asm/io.h>
#include <getopt.h>
#include <core_rv64.h>
#include <exports.h>
#include <sysm.h>

static void irq_show_usage(void) {
  printf("Usage: irq [OPTION]...\n\n");
  printf("-h, --help\t\tcommand help\n");
  printf("-s, --sirq\t\ttime soft irq case\n");
  printf("-t, --timer\t\ttest timer irq case\n");
  printf("-e, --eirq\t\ttest extern irq case\n");
  printf("-o, --show\t\tshow requested irqs\n");
}

static int irq_exit = 0;
static int coreid   = 0;
void coret_interrupt(void *regs) {
  csi_coret_config(coreid, 0xffffffff, 0x0);
  irq_exit++;
  printf("Test Coret IRQ Pass\n");
}

void soft_interrupt(void *regs) {
  csi_softirq_trigger(coreid, 0);
  irq_exit++;
  printf("Test Soft IRQ Pass\n");
}

#define WDT_MODE    0x0
#define WDT_CTRL    0x4
#define WDT_RESTART 0x8
#define WDT_STATUS  0xc
#define WDT_DBG     0x10
static unsigned long wdtbase = ITCS_C_WDT_BASE;

int wdt_irqhandler(int irq, void *args) {
  /* restart wdt and clear irq */
  writel(0x1999, wdtbase + WDT_RESTART);
  /* disable wdt */
  writel((0xabc << 12), wdtbase + WDT_MODE);
  irq_exit++;
  printf("Test External IRQ Pass\n");
  return 0;
}

void wdt_irq_test(void) {
  int ret;

  itcs_module_enable(CPU, "wdt");

  ret = request_irq(C_WDT_IRQn, wdt_irqhandler, "cpu wdt", NULL);
  if (ret < 0) {
		ret = replace_irq(C_WDT_IRQn, wdt_irqhandler, "cpu wdt", NULL);
		if (ret < 0) {
			printf("Request watchdog irq Err\n");
    	return;
		}
  }
  irq_set_affinity(C_WDT_IRQn, coreid);

  writel((0x248 << 6), wdtbase + WDT_CTRL);
  /* restart wdt */
  writel(0x1999, wdtbase + WDT_RESTART);

  writel(0x137085, wdtbase + WDT_DBG);
  /* enable irq & wdt */
  writel(((0xabc << 12) | 5), wdtbase + WDT_MODE);
}

#define VIRTUAL_IRQ(irq)        (irq - S_WDT_IRQn)
#define VIRTUAL_IRQ_GROUP       32
#define VIRTUAL_IRQ_MAX         256
#define VIRTUAL_IRQ_OFFSET(num) (num % VIRTUAL_IRQ_GROUP)
#define VIRTUAL_IRQ_LEVEL(num)                                                 \
  (ITCS_C_DINT_BASE + num / VIRTUAL_IRQ_GROUP * 0x4)
#define VIRTUAL_IRQ_EN(num)                                                    \
  (ITCS_C_DINT_BASE + 0x4 * 8 + num / VIRTUAL_IRQ_GROUP * 0x4)

static void virtual_irq_control(int irq, bool flags) {
  uint32_t val;

  if (irq >= VIRTUAL_IRQ_MAX)
    return;

  val = readl(VIRTUAL_IRQ_EN(irq));
  if (flags)
    val |= (1 << VIRTUAL_IRQ_OFFSET(irq));
  else
    val &= ~(1 << VIRTUAL_IRQ_OFFSET(irq));
  writel(val, VIRTUAL_IRQ_EN(irq));
}

static void virtual_irq_set_level(int irq, int level) {
  uint32_t val;

  if (irq >= VIRTUAL_IRQ_MAX)
    return;

  val = readl(VIRTUAL_IRQ_LEVEL(irq));
  if (level > 0)
    val |= (1 << VIRTUAL_IRQ_OFFSET(irq));
  else
    val &= ~(1 << VIRTUAL_IRQ_OFFSET(irq));

  writel(val, VIRTUAL_IRQ_LEVEL(irq));
}

int virtual_irqhandler(int irq, void *args) {
  printf("Virtual IRQ%d Call\n", irq);
  virtual_irq_control(VIRTUAL_IRQ(irq), false);
  irq_exit++;
  return 0;
}

int virtual_irq_test(int irq) {
  char name[16] = {0};
  int ret;

  // itcs_sysm_set_plic_trigger_level(CPU, irq, PLIC_PULSE);
  sprintf(name, "virtual irq%d", irq);
  ret = request_irq(irq, virtual_irqhandler, name, NULL);
  if (ret < 0) {
    printf("Request %s Err\n", name);
    return -1;
  }

  virtual_irq_control(VIRTUAL_IRQ(irq), true);
  virtual_irq_set_level(VIRTUAL_IRQ(irq), 1);
  virtual_irq_set_level(VIRTUAL_IRQ(irq), 0);

  return 0;
}

int irq_main(int argc, char *argv[]) {
  int option_index = 0, c, ret = 0;
  static const char short_options[]         = "s:t:e:v:oh";
  static const struct option long_options[] = {
      {"sirq", 1, 0, 's'},    {"timer", 1, 0, 't'}, {"eirq", 1, 0, 'e'},
      {"virtual", 1, 0, 'v'}, {"show", 0, 0, 'o'},  {"help", 0, 0, 'h'},
      {0, 0, 0, 0},
  };

  while ((c = getopt_long(argc, argv, short_options, long_options,
                          &option_index)) != -1) {
    switch (c) {
    case 's':
      irq_exit = 0;
      coreid   = ustrtoul(optarg, NULL, 10);
      csi_softirq_trigger(coreid, 0);
      csi_softirq_trigger(coreid, 1);
      break;
    case 't':
      irq_exit = 0;
      coreid   = ustrtoul(optarg, NULL, 10);
      // csi_coret_config(coreid, 0xffffffff, 0x0);
#ifdef CONFIG_COMPILE_RTL
      csi_coret_config(coreid, 100, 0);
#else
      csi_coret_config(coreid, 20000000 / 100, 0);
#endif
      break;
    case 'e':
      irq_exit = 0;
      coreid   = ustrtoul(optarg, NULL, 10);
      wdt_irq_test();
      /* wait other core quit. */
      udelay(500);
      break;
    case 'v':
      irq_exit = 0;
      virtual_irq_test(S_WDT_IRQn);
      break;
    case 'o':
      show_interrupts();
      break;
    case 'h':
    default:
      irq_show_usage();
      ret = -1;
      goto err;
    }
  }

  if (optind == 1) {
    irq_show_usage();
    ret = -1;
    goto err;
  }

  while (!irq_exit)
    udelay(10);

err:
  optind = 1;
  return ret;
}

int irq_rtl(int id) {
  printf("invoking id: %d\n", id);
  return 0;
}

void irq_init(void) { register_testbench("irq", irq_main, irq_rtl); }

testbench_init(irq_init);

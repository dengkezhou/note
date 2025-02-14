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

static void irq_show_usage(void) {
  printf("Usage: irq [OPTION]...\n\n");
  printf("-h, --help\t\tcommand help\n");
  printf("-s, --sirq\t\ttime soft irq case\n");
  printf("-t, --coret\t\ttest coret irq case\n");
  printf("-e, --eirq\t\ttest extern irq case\n");
  printf("-o, --show\t\tshow requested irqs\n");
}

static int irq_exit = 0;
int coret_irqhandler(int irq, void *args) {
  csi_coret_stop();
  irq_exit++;
  printf("Test Coret IRQ Pass\n");
  return 0;
}

int soft_irqhandler(int irq, void *args) {
  csi_softirq_trigger(0);
  irq_exit++;
  printf("Test Soft IRQ Pass\n");
  return 0;
}

#ifndef CONFIG_E902
#define WDT_MODE    0x0
#define WDT_CTRL    0x4
#define WDT_RESTART 0x8
#define WDT_STATUS  0xc
#define WDT_DBG     0x10

static unsigned long wdtbase = ITCS_S_WDT_BASE;

int wdt_irqhandler(int irq, void *args) {
  /* restart wdt and clear irq */
  writel(0x1999, wdtbase + WDT_RESTART);
  /* disable wdt */
  writel((0xabc << 12), wdtbase + WDT_MODE);
  irq_exit++;
  printf("Test External IRQ(%d) Pass\n", irq);
  return 0;
}

enum {
  NORMAL_IRQ,
  NMI_IRQ,
  EXT_IRQ,
};

void nmi_interrupt(void *regs) {
  /* restart wdt and clear irq */
  writel(0x1999, wdtbase + WDT_RESTART);
  /* disable wdt */
  writel((0xabc << 12), wdtbase + WDT_MODE);
  irq_exit++;
  printf("Test NMI IRQ Pass\n");
}

void ext_irq_test(int mode) {
  int irqn = S_WDT_IRQn;
  int ret;

  itcs_module_enable(CPU, "wdt");

  if (mode == EXT_IRQ)
    irqn = Machine_External_IRQn;

  if (mode != NMI_IRQ) {
    ret = request_irq(irqn, wdt_irqhandler, "sap wdt", NULL);
		if (ret < 0) {
			ret = replace_irq(irqn, wdt_irqhandler, "sap wdt", NULL);
			if (ret < 0) {
				printf("Request watchdog irq Err\n");
				return;
			}
		}
  }

  writel((0x248 << 6), wdtbase + WDT_CTRL);
  /* restart wdt */
  writel(0x1999, wdtbase + WDT_RESTART);

  writel(0x137085, wdtbase + WDT_DBG);
  /* enable irq & wdt */
  writel(((0xabc << 12) | 5), wdtbase + WDT_MODE);
}

#else
#include <timer.h>

static timer_handle_t pcsi_timer;

void timer_event_cb_fun(timer_handle_t handle) {
  irq_exit++;
  csi_timer_stop(pcsi_timer);
  printf("Test External IRQ Pass\n");
}

void ext_irq_test(int mode) {

  pcsi_timer = csi_timer_initialize(0, timer_event_cb_fun);
  csi_timer_config(pcsi_timer, 1);
  csi_timer_set_timeout(pcsi_timer, 10 /* ms */);
  csi_timer_start(pcsi_timer);
}
#endif

extern void clic_set_nmi_irq(int irqn);
extern void clic_set_ext_irq(int irqn);

int irq_main(int argc, char *argv[]) {
  int option_index = 0, c, ret = 0;
  static const char short_options[]         = "s:t:e:n:x:oh";
  static const struct option long_options[] = {
      {"sirq", 1, 0, 's'}, {"coret", 1, 0, 't'},  {"eirq", 1, 0, 'e'},
      {"nmi", 1, 0, 'n'},  {"extirq", 1, 0, 'x'}, {"show", 0, 0, 'o'},
      {"help", 0, 0, 'h'}, {0, 0, 0, 0},
  };
  // int id = 0;

  while ((c = getopt_long(argc, argv, short_options, long_options,
                          &option_index)) != -1) {
    switch (c) {
    case 's':
      irq_exit = 0;

      request_irq(Machine_Software_IRQn, soft_irqhandler, "soft irq", NULL);

      csi_softirq_trigger(0);
      csi_softirq_trigger(1);
      break;
    case 't':
      irq_exit = 0;

      request_irq(CORET_IRQn, coret_irqhandler, "core timer", NULL);

      csi_coret_stop();
#ifdef CONFIG_COMPILE_RTL
      csi_coret_config(24000000 / 100, 0);
#else
      csi_coret_config(100, 0);
#endif
      break;
    case 'e':
      irq_exit = 0;
      ext_irq_test(NORMAL_IRQ);
      break;
    case 'n':
      irq_exit = 0;
      clic_set_nmi_irq(S_WDT_IRQn - 16);
      ext_irq_test(NMI_IRQ);
      break;
    case 'x':
      irq_exit = 0;
      clic_set_ext_irq(S_WDT_IRQn - 16);
      ext_irq_test(EXT_IRQ);
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

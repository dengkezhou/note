// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (C) 2017 SiFive
 * Copyright (C) 2018 Christoph Hellwig
 */
#define pr_fmt(fmt) "plic: " fmt
#include <stdbool.h>
#include <common.h>
#include <asm/io.h>
#include <irq.h>
#include <initcall.h>
#include <asm-generic/errno.h>
#ifdef CONFIG_64BIT
#include <csi_rv64_gcc.h>
#else
#include <csi_rv32_gcc.h>
#endif
#include <sysm.h>
#include <pm.h>

/*
 * This driver implements a version of the RISC-V PLIC with the actual layout
 * specified in chapter 8 of the SiFive U5 Coreplex Series Manual:
 *
 *     https://static.dev.sifive.com/U54-MC-RVCoreIP.pdf
 *
 * The largest number supported by devices marked as 'sifive,plic-1.0.0', is
 * 1024, of which device 0 is defined as non-existent by the RISC-V Privileged
 * Spec.
 */

#define MAX_DEVICES  1024
#define MAX_CONTEXTS 15872

/*
 * Each interrupt source has a priority register associated with it.
 * We always hardwire it to one in Linux.
 */
#define PRIORITY_BASE   0
#define PRIORITY_PER_ID 4

/*
 * Each interrupts source has a ip priority register associated with it.
 * we need not hander it except init
 */
#define PENDING_BASE 0x1000

/*
 * Each hart context has a vector of interrupt enable bits associated with it.
 * There's one bit for each interrupt source.
 */
#define ENABLE_BASE     0x2000
#define ENABLE_PER_HART 0x100
#define ENABLE_SMODE    0x80

/*
 * Each hart context has a set of control registers associated with it.  Right
 * now there's only two: a source priority threshold over which the hart will
 * take an interrupt, and a register to claim interrupts.
 */
#define CONTEXT_BASE      0x200000
#define CONTEXT_PER_HART  0x2000
#define CONTEXT_SMODE     0x1000
#define CONTEXT_THRESHOLD 0x00
#define CONTEXT_CLAIM     0x04

#define PLIC_DISABLE_THRESHOLD 0x7
#define PLIC_ENABLE_THRESHOLD  0

#define PLIC_CTRL 0x1ffffc

#define NR_GIC_CPU_IF 8

struct plic_priv {
  void *regs;
};

struct plic_handler {
  bool present;
  void *hart_base;
  void *enable_base;
  struct plic_priv *priv;
};
struct plic_handler plic_handlers[NR_CPUS] = {0};

static struct plic_priv plic_priv = {
    .regs = (void *)PLIC_BASE,
};

#define this_cpu_ptr(x)     x[__get_MHARTID()]
#define per_cpu_ptr(x, cpu) x[cpu]

static inline void plic_toggle(struct plic_handler *handler, int irq,
                               int enable) {
#ifdef CONFIG_RISCV_SMODE
  u32 *reg = handler->enable_base + ENABLE_SMODE + (irq / 32) * sizeof(u32);
#else
  u32 *reg = handler->enable_base + (irq / 32) * sizeof(u32);
#endif
  u32 hwirq_mask = 1 << (irq % 32);

  if (enable)
    writel(readl(reg) | hwirq_mask, reg);
  else
    writel(readl(reg) & ~hwirq_mask, reg);
}

static inline void plic_irq_toggle(int cpu, int irq, int enable) {
  struct plic_handler *handler = per_cpu_ptr(&plic_handlers, cpu);

  plic_toggle(handler, irq, enable);
}

static void plic_irq_unmask(struct irq_data *d) {
  plic_irq_toggle(d->cpu, d->irq, 1);
}

static void plic_irq_mask(struct irq_data *d) {
  plic_irq_toggle(d->cpu, d->irq, 0);
}

static int plic_set_affinity(struct irq_data *d, unsigned int cpu) {
  plic_irq_mask(d);
  d->cpu = cpu;
  plic_irq_unmask(d);

  return IRQ_SET_MASK_OK_DONE;
}

static void plic_irq_eoi(struct irq_data *d) {
  struct plic_handler *handler = per_cpu_ptr(&plic_handlers, d->cpu);
#ifdef CONFIG_RISCV_SMODE
  writel(d->irq, handler->hart_base + CONTEXT_SMODE + CONTEXT_CLAIM);
#else
  writel(d->irq, handler->hart_base + CONTEXT_CLAIM);
#endif
}

/*
 * Handling an interrupt is a two-step process: first you claim the interrupt
 * by reading the claim register, then you complete the interrupt by writing
 * that source ID back to the same claim register.  This automatically enables
 * and disables the interrupt, so there's nothing else to do.
 */
void plic_handle_irq(void *regs) {
  percpu_data_t *cpu           = itcs_get_percpu_data();
  struct plic_handler *handler = per_cpu_ptr(&plic_handlers, cpu->hartid);
  int irq;

#ifdef CONFIG_RISCV_SMODE
  while ((irq = readl(handler->hart_base + CONTEXT_SMODE + CONTEXT_CLAIM)))
#else
  while ((irq = readl(handler->hart_base + CONTEXT_CLAIM)))
#endif
    handle_IRQ(irq, regs);
}

static struct irq_chip plic_chip = {
    .name             = "T-Head PLIC",
    .irq_mask         = plic_irq_mask,
    .irq_unmask       = plic_irq_unmask,
    .irq_eoi          = plic_irq_eoi,
    .irq_set_affinity = plic_set_affinity,
    .irq_handle       = plic_handle_irq,
};

static void plic_set_threshold(struct plic_handler *handler, u32 threshold) {
  /* priority must be > threshold to trigger an interrupt */
  writel(threshold, handler->hart_base + CONTEXT_THRESHOLD);
}

static int plic_starting_cpu(int cpu) {
  struct plic_handler *handler = per_cpu_ptr(&plic_handlers, cpu);
  struct plic_priv *priv       = handler->priv;

  // set plic_ctrl
  writel(1, priv->regs + PLIC_CTRL);
  plic_set_threshold(handler, PLIC_ENABLE_THRESHOLD);
  return 0;
}

void itcs_set_irq_priority(int irq_num, uint32_t prio){
	if(prio > 0x1f){
		printf("prio out of range, set to max value 0x1f\n");
		prio = 0x1f;
	}

	writel(prio, PLIC_BASE  + irq_num * 4);
}

uint32_t itcs_get_irq_priority(int irq_num){
  return readl(PLIC_BASE  + irq_num * 4);
}

static void plic_module_init(struct plic_handler *handler, int cpu) {
  int i                  = 0;
  struct plic_priv *priv = handler->priv;

  if (!cpu) {
    /* set highest priority */
    for (i = 1; i < MAX_IRQn; i++)
      writel(0x1f, priv->regs + PRIORITY_BASE + i * PRIORITY_PER_ID);
#ifndef CONFIG_COMPILE_RTL
    /* clear pending status */
    for (i = 0; i < DIV_ROUND_UP(MAX_IRQn, 32); i++)
      writel(0x0, priv->regs + PENDING_BASE + i * 4);
#endif
  }

  /* disable all irq */
  for (i = 0; i < DIV_ROUND_UP(MAX_IRQn, 32); i++) {
    writel(0x0, handler->enable_base + i * 4);
#ifdef CONFIG_RISCV_SMODE
    writel(0x0, handler->enable_base + ENABLE_SMODE + i * 4);
#endif
  }
#ifndef CONFIG_COMPILE_RTL
  /* clear old irq */
  for (i = 1; i < MAX_IRQn; i++) {
    writel(i, handler->hart_base + CONTEXT_CLAIM);
#ifdef CONFIG_RISCV_SMODE
    writel(i, handler->hart_base + CONTEXT_SMODE + CONTEXT_CLAIM);
#endif
  }
#endif
}

void irq_env_enable(void) {
#ifdef CONFIG_RISCV_SMODE
  uint32_t sie = __get_SIE();
  sie |= ((1 << 1) | (1 << 5) | (1 << 9));
  __set_SIE(sie);
#else
  uint32_t mie = __get_MIE();

  /* 1 << 3: enable msoft interrupt
   * 1 << 11: enable extern interrupt
   * 1 << 7: enable coret interrupt
   */
  mie |= ((1 << 3) | (1 << 11) | (1 << 7));
  __set_MIE(mie);
#endif
  __enable_excp_irq();
}

void irq_env_disable(void) {
#ifdef CONFIG_RISCV_SMODE
  uint32_t sie = __get_SIE();
  sie &= ~((1 << 1) | (1 << 5) | (1 << 9));
  __set_SIE(sie);
#else
  uint32_t mie = __get_MIE();

  /* 1 << 3: enable msoft interrupt
   * 1 << 11: enable extern interrupt
   * 1 << 7: enable coret interrupt
   */
  mie &= ~((1 << 3) | (1 << 11) | (1 << 7));
  __set_MIE(mie);
#endif
  __disable_excp_irq();
}

typedef struct suspend_plic {
  uint32_t mprio[1023];
  uint32_t mth[NR_CPUS];
  uint32_t mie[NR_CPUS][32];
} suspend_plic_t;

#ifndef CONFIG_COMPILE_RTL
static suspend_plic_t savePlic;
#endif
int plic_pm_suspend(void *privdata) {
#ifndef CONFIG_COMPILE_RTL
  int i, j;
#endif

  irq_env_disable();
#ifndef CONFIG_COMPILE_RTL
  for (i = 0; i < MAX_IRQn; i++)
    savePlic.mprio[i] =
        readl(plic_priv.regs + PRIORITY_BASE + i * PRIORITY_PER_ID);

  for (i = 0; i < NR_CPUS; i++) {
    savePlic.mth[i] =
        readl(plic_priv.regs + CONTEXT_BASE + i * CONTEXT_PER_HART);
    for (j = 0; j < DIV_ROUND_UP(MAX_IRQn, 32); j++) {
      savePlic.mie[i][j] =
          readl(plic_priv.regs + ENABLE_BASE + i * ENABLE_PER_HART + j * 4);
      // disable irq
      writel(0x0, plic_priv.regs + ENABLE_BASE + i * ENABLE_PER_HART + j * 4);
    }
  }
#endif
  return 0;
}

int plic_pm_resume(void *privdata) {
#ifndef CONFIG_COMPILE_RTL
  int i, j;
#endif

  irq_env_enable();
#ifndef CONFIG_COMPILE_RTL
  for (i = 0; i < DIV_ROUND_UP(MAX_IRQn, 32); i++)
    writel(0x0, plic_priv.regs + PENDING_BASE + i * 4);

  for (i = 0; i < MAX_IRQn; i++)
    writel(savePlic.mprio[i],
           plic_priv.regs + PRIORITY_BASE + i * PRIORITY_PER_ID);

  for (i = 0; i < NR_CPUS; i++) {
    writel(savePlic.mth[i],
           plic_priv.regs + CONTEXT_BASE + i * CONTEXT_PER_HART);
    for (j = 0; j < DIV_ROUND_UP(MAX_IRQn, 32); j++) {
      writel(savePlic.mie[i][j],
             plic_priv.regs + ENABLE_BASE + i * ENABLE_PER_HART + j * 4);
    }
  }
  writel(1, plic_priv.regs + PLIC_CTRL);
#endif
  return 0;
}

SIMPLE_PM_OPS(plic, plic_pm_suspend, plic_pm_resume, NULL);

static void plic_init(void) {
  int i;
  struct plic_priv *priv;
  struct plic_handler *handler;

  irq_env_enable();

  priv = &plic_priv;
  for (i = 0; i < NR_CPUS; i++) {
    /*
     * When running in M-mode we need to ignore the S-mode handler.
     * Here we assume it always comes later, but that might be a
     * little fragile.
     */
    handler = per_cpu_ptr(&plic_handlers, i);
    if (handler->present) {
      printf("handler already present for context %d.\n", i);
      plic_set_threshold(handler, PLIC_ENABLE_THRESHOLD);
      goto done;
    }

    handler->present     = true;
    handler->hart_base   = priv->regs + CONTEXT_BASE + i * CONTEXT_PER_HART;
    handler->enable_base = priv->regs + ENABLE_BASE + i * ENABLE_PER_HART;
    handler->priv        = priv;
  done:
    plic_module_init(handler, i);
  }

  /*
   * We can have multiple PLIC instances so setup cpuhp state only
   * when context handler for current/boot CPU is present.
   */
  plic_starting_cpu(0);

  register_irq_chip(&plic_chip);
  itcs_register_pm(&pm_plic);
}

module_init(plic_init);

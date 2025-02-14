// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (C) 2017 SiFive
 * Copyright (C) 2018 Christoph Hellwig
 */
#define pr_fmt(fmt) "clic: " fmt
#include <stdbool.h>
#include <common.h>
#include <asm/io.h>
#include <irq.h>
#include <initcall.h>
#include <asm-generic/errno.h>
#include <csi_rv32_gcc.h>
#include <core_rv32.h>

/*
 * Each hart context has a set of control registers associated with it.  Right
 * now there's only two: a source priority threshold over which the hart will
 * take an interrupt, and a register to claim interrupts.
 */
#define HART_BASE 0x1000

#define CLICCFG    0x0
#define CLICINFO   0x4
#define MINTTHRESH 0x8

#define CLICINTIP         0x0
#define CLICINTIE         0x1
#define CLICINTATTR       0x2
#define CLICINTCTL        0x3
#define CLICINT_PER_GROUP 0x4

#define CLIC_DISABLE_THRESHOLD 0xff
#define CLIC_ENABLE_THRESHOLD  0

struct clic_priv {
  void *regs;
};

struct clic_handler {
  bool present;
  void *hart_base;
  struct clic_priv *priv;
};
struct clic_handler clic_handlers;

static struct clic_priv clic_priv = {
    .regs = (void *)CLIC_BASE,
};

static int clic_get_ctlbit(struct clic_handler *handler) {
  struct clic_priv *priv = handler->priv;
  return ((readl(priv->regs + CLICINFO) & CLIC_INFO_CLICINTCTLBITS_Msk) >>
          CLIC_INFO_CLICINTCTLBITS_Pos);
}

void clic_irq_set_priority(struct clic_handler *handler, int irq,
                           int priority) {
  int nlbits = clic_get_ctlbit(handler);
  uint8_t ctl;

  ctl = readb(handler->hart_base + CLICINTCTL + irq * CLICINT_PER_GROUP);
  ctl &= (~CLIC_INTCFG_PRIO_Msk);
  ctl |= (priority << (8 - nlbits));
  writeb(ctl, handler->hart_base + CLICINTCTL + irq * CLICINT_PER_GROUP);
}

int clic_irq_get_priority(struct clic_handler *handler, int irq) {
  int nlbits = clic_get_ctlbit(handler);

  return (readb(handler->hart_base + CLICINTCTL + irq * CLICINT_PER_GROUP) >>
          (8 - nlbits));
}

void itcs_set_irq_priority(int irq_num, uint32_t prio){
	if(prio > 0xff){
		printf("prio out of range, set to max value 0xff\n");
		prio = 0xff;
	}

	clic_irq_set_priority(&clic_handlers, irq_num, prio);
}

uint32_t itcs_get_irq_priority(int irq_num){
  return clic_irq_get_priority(&clic_handlers, irq_num);
}

static inline void clic_toggle(struct clic_handler *handler, int irq,
                               int enable) {
  u32 *reg = handler->hart_base + CLICINTIE + irq * CLICINT_PER_GROUP;

  if (enable)
    writeb(readb(reg) | CLIC_INTIE_IE_Msk, reg);
  else
    writeb(readb(reg) & ~CLIC_INTIE_IE_Msk, reg);
}

static inline void clic_irq_toggle(int cpu, int irq, int enable) {
  struct clic_handler *handler = &clic_handlers;

  /* lowest priority */
  clic_irq_set_priority(handler, irq, 0);
  /* enable irq */
  clic_toggle(handler, irq, enable);
}

static void clic_irq_unmask(struct irq_data *d) {
  clic_irq_toggle(d->cpu, d->irq, 1);
}

static void clic_irq_mask(struct irq_data *d) {
  clic_irq_toggle(d->cpu, d->irq, 0);
}

/*
 * Handling an interrupt is a two-step process: first you claim the interrupt
 * by reading the claim register, then you complete the interrupt by writing
 * that source ID back to the same claim register.  This automatically enables
 * and disables the interrupt, so there's nothing else to do.
 */
void clic_handle_irq(void *regs) {
  int irq = __get_MCAUSE() & 0xfff;

#if !defined(CONFIG_COMPILE_SIM) && !defined(CONFIG_E902)
  struct clic_handler *handler = &clic_handlers;
  if (irq == S_WDT_IRQn || irq == C_WDT_IRQn)
    writeb(0, handler->hart_base + CLICINTIP + irq * CLICINT_PER_GROUP);
#endif

  handle_IRQ(irq, regs);
}

static struct irq_chip clic_chip = {
    .name       = "T-Head CLIC",
    .irq_mask   = clic_irq_mask,
    .irq_unmask = clic_irq_unmask,
    .irq_handle = clic_handle_irq,
};

static void clic_set_threshold(struct clic_handler *handler, u32 threshold) {
  struct clic_priv *priv = handler->priv;
  /* priority must be > threshold to trigger an interrupt */
  writel(threshold, priv->regs + MINTTHRESH);
}

static void irq_env_enable(void) { __enable_excp_irq(); }

static void clic_configure(struct clic_handler *handler) {
  struct clic_priv *priv = handler->priv;
  uint8_t tmp;
  int irq;

  /* disable IRQn */
  for (irq = 0; irq < MAX_IRQn; irq++)
    clic_toggle(handler, irq, 0);

  /* set nlbits */
  tmp = readb(priv->regs + CLICCFG);
  tmp |= (clic_get_ctlbit(handler) << CLIC_CLICCFG_NLBIT_Pos);
  writeb(tmp, priv->regs + CLICCFG);

  /* clear pending */
  for (irq = 0; irq < MAX_IRQn; irq++)
    writeb(0x0, handler->hart_base + CLICINTIP + irq * CLICINT_PER_GROUP);

  /*
   * set attr: level trigger, novector irq
   */
  for (irq = 0; irq < MAX_IRQn; irq++)
    writeb(0x0, handler->hart_base + CLICINTATTR + irq * CLICINT_PER_GROUP);

#if !defined(CONFIG_COMPILE_SIM) && !defined(CONFIG_E902)
  /* wdt pulse irq, so set positive edge */
  writeb(0x1 << 1,
         handler->hart_base + CLICINTATTR + S_WDT_IRQn * CLICINT_PER_GROUP);
  writeb(0x1 << 1,
         handler->hart_base + CLICINTATTR + C_WDT_IRQn * CLICINT_PER_GROUP);
#endif

  clic_set_threshold(handler, CLIC_ENABLE_THRESHOLD);
}

void clic_set_nmi_irq(int irqn) {
  if (irqn > 0x7f || irqn < 0)
    return;

  writel(0x7f & irqn, 0xd2f08820);
}

void clic_set_ext_irq(int irqn) {
  if (irqn > 0x7f || irqn < 0)
    return;

  writel(0x7f & irqn, 0xd2f08824);
}

static void clic_init(void) {
  struct clic_priv *priv;
  struct clic_handler *handler;

  irq_env_enable();

#if !defined(CONFIG_COMPILE_SIM) && !defined(CONFIG_E902)
  /* set default nmi */
  clic_set_nmi_irq(0x79);
  /* set default extern irq */
  clic_set_ext_irq(0x79);
#endif

  priv    = &clic_priv;
  handler = &clic_handlers;
  if (handler->present) {
    printf("handler already present\n");
    clic_set_threshold(handler, CLIC_DISABLE_THRESHOLD);
    goto done;
  }

  handler->present   = true;
  handler->hart_base = priv->regs + HART_BASE;
  handler->priv      = priv;
done:
  clic_configure(handler);

  register_irq_chip(&clic_chip);
}

module_init(clic_init);

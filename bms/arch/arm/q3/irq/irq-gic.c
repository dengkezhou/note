/*
 * ported from linux/arch/arm/common/gic.c
 */

#include <common.h>
#include <irq.h>
#include <arm-gic.h>
#include <asm/io.h>
#include <asm/errno.h>
#include <testbench.h>
#include <lib/aarch64/arch_helpers.h>

#define ENABLE_GRP0 (1 << 0)
#define ENABLE_GRP1 (1 << 1)

/* GICC_CTLR bit definitions */
#define EOI_MODE_NS      (1 << 10)
#define EOI_MODE_S       (1 << 9)
#define IRQ_BYP_DIS_GRP1 (1 << 8)
#define FIQ_BYP_DIS_GRP1 (1 << 7)
#define IRQ_BYP_DIS_GRP0 (1 << 6)
#define FIQ_BYP_DIS_GRP0 (1 << 5)
#define CBPR             (1 << 4)
#define FIQ_EN           (1 << 3)
#define ACK_CTL          (1 << 2)

union gic_base {
  void *common_base;
  void **percpu_base;
};

struct gic_chip_data {
  union gic_base dist_base;
  union gic_base cpu_base;
  struct irq_domain *domain;
  unsigned int gic_irqs;
};
static struct gic_chip_data gic_data;

/*
 * The GIC mapping of CPU interfaces does not necessarily match
 * the logical CPU numbering.  Let's use a mapping as returned
 * by the GIC itself.
 */
#define NR_GIC_CPU_IF 8
static u8 gic_cpu_map[NR_GIC_CPU_IF];

#define gic_dist_base(...)      ((void *)GIC_DISTRIBUTOR_ADDR)
#define gic_cpu_base(...)       ((void *)GIC_CPUI_BASE_ADDR)
#define gic_data_dist_base(...) gic_dist_base()
#define gic_data_cpu_base(...)  gic_cpu_base()

/*******************************************************************************
 * Enable secure interrupts and use FIQs to route them. Disable legacy bypass
 * and set the priority mask register to allow all interrupts to trickle in.
 ******************************************************************************/
static void gic_cpuif_setup(void) {
  unsigned int val;
  // unsigned int gic_irqs = gic->gic_irqs;
  // void *base = gic_data_dist_base(gic);
  // val = gicc_read_iidr(gicc_base);
  // val = readl(base + GIC_CTRL);
  val = 0;
  /*
   * If GICv3 we need to do a bit of additional setup. We want to
   * allow default GICv2 behaviour but allow the next stage to
   * enable full gicv3 features.
   */
  /*if (((val >> GICC_IIDR_ARCH_SHIFT) & GICC_IIDR_ARCH_MASK) >= 3) {
          gicv3_cpuif_setup();
  }*/

  val = ENABLE_GRP0 /*| FIQ_EN*/ | FIQ_BYP_DIS_GRP0;
  val |= IRQ_BYP_DIS_GRP0 | FIQ_BYP_DIS_GRP1 | IRQ_BYP_DIS_GRP1;

  // gicc_write_pmr(gicc_base, GIC_PRI_MASK);
  // gicc_write_ctlr(gicc_base, val);
  writel(val, gic_cpu_base() + GIC_CPU_CTRL);
}

/*
 * Routines to acknowledge, disable and enable interrupts
 */
static void gic_mask_irq(unsigned int irq) {
  u32 mask = 1 << (irq % 32);
  writel(mask, gic_dist_base() + GIC_DIST_ENABLE_CLEAR + (irq / 32) * 4);
}

static void gic_unmask_irq(unsigned int irq) {
  u32 mask = 1 << (irq % 32);
  writel(mask, gic_dist_base() + GIC_DIST_ENABLE_SET + (irq / 32) * 4);
}

static void gic_eoi_irq(unsigned int irq) {
  writel(irq, gic_cpu_base() + GIC_CPU_EOI);
}

static int gic_set_type(unsigned int irq, unsigned int type) {
  void *base          = gic_dist_base();
  unsigned int gicirq = irq;
  u32 enablemask      = 1 << (gicirq % 32);
  u32 enableoff       = (gicirq / 32) * 4;
  u32 confmask        = 0x2 << ((gicirq % 16) * 2);
  u32 confoff         = (gicirq / 16) * 4;
  int enabled         = 0;
  u32 val;

  /* Interrupt configuration for SGIs can't be changed */
  if (gicirq < 16)
    return -EINVAL;

  if (type != IRQ_TYPE_LEVEL_HIGH && type != IRQ_TYPE_EDGE_RISING)
    return -EINVAL;

  val = readl(base + GIC_DIST_CONFIG + confoff);
  if (type == IRQ_TYPE_LEVEL_HIGH)
    val &= ~confmask;
  else if (type == IRQ_TYPE_EDGE_RISING)
    val |= confmask;

  /*
   * As recommended by the spec, disable the interrupt before changing
   * the configuration
   */
  if (readl(base + GIC_DIST_ENABLE_SET + enableoff) & enablemask) {
    writel(enablemask, base + GIC_DIST_ENABLE_CLEAR + enableoff);
    enabled = 1;
  }

  writel(val, base + GIC_DIST_CONFIG + confoff);

  if (enabled)
    writel(enablemask, base + GIC_DIST_ENABLE_SET + enableoff);

  return 0;
}

/* linux driver use cpumask_any_and to pick a random cpu from
 * the mask, so this API assign IRQ to a single processor.
 */
static int gic_set_affinity(unsigned int irq, unsigned int cpu) {
  void *reg          = gic_dist_base() + GIC_DIST_TARGET + (irq & ~3);
  unsigned int shift = (irq % 4) * 8;
  u32 val, mask;

  if (cpu >= NR_GIC_CPU_IF)
    return -EINVAL;

  mask = gic_cpu_map[cpu];
  val  = readl(reg) & ~(0xff << shift);
  writel(val | mask, reg);

  return IRQ_SET_MASK_OK;
}

static void gic_handle_irq(struct pt_regs *regs) {
  u32 irqstat, irqnr;
  void *cpu_base = gic_data_cpu_base();

  do {
    irqstat = readl(cpu_base + GIC_CPU_INTACK);
    irqnr   = irqstat & ~0x1c00;

    if (likely(irqnr > 15 && irqnr < 1021)) {
      handle_IRQ(irqnr, regs);
      continue;
    }
    if (irqnr < 16) {
      writel(irqstat, cpu_base + GIC_CPU_EOI);

      printf("soft IRQ %d\n", irqnr);
      continue;
    }
    break;
  } while (1);
}

static struct irq_chip gic_chip = {
    .name             = "GIC",
    .irq_mask         = gic_mask_irq,
    .irq_unmask       = gic_unmask_irq,
    .irq_eoi          = gic_eoi_irq,
    .irq_set_type     = gic_set_type,
    .irq_set_affinity = gic_set_affinity,
    .irq_handle       = gic_handle_irq,
};

static u8 gic_get_cpumask(struct gic_chip_data *gic) {
  void *base = gic_data_dist_base(gic);
  u32 mask, i;

  for (i = mask = 0; i < 32; i += 4) {
    mask = readl(base + GIC_DIST_TARGET + i);
    mask |= mask >> 16;
    mask |= mask >> 8;
    if (mask)
      break;
  }

  if (!mask) {
    printf("GIC CPU mask not found - kernel will fail to boot.\n");
    for (;;)
      ;
  }

  return mask;
}

static void gic_dist_init(struct gic_chip_data *gic) {
  unsigned int i;
  u32 cpumask;
  unsigned int gic_irqs = gic->gic_irqs;
  void *base            = gic_data_dist_base(gic);

  writel(0, base + GIC_DIST_CTRL);

  /*
   * Set all global interrupts to be level triggered, active low.
   */
  for (i = 32; i < gic_irqs; i += 16)
    writel(0, base + GIC_DIST_CONFIG + i * 4 / 16);

  /*
   * Set all global interrupts to this CPU only.
   */
  cpumask = gic_get_cpumask(gic);
  cpumask |= cpumask << 8;
  cpumask |= cpumask << 16;
  for (i = 32; i < gic_irqs; i += 4)
    writel(cpumask, base + GIC_DIST_TARGET + i * 4 / 4);

  /*
   * Set priority on all global interrupts.
   */
  for (i = 32; i < gic_irqs; i += 4)
    writel(0xa0a0a0a0, base + GIC_DIST_PRI + i * 4 / 4);

  /*
   * Disable all interrupts.  Leave the PPI and SGIs alone
   * as these enables are banked registers.
   */
  for (i = 32; i < gic_irqs; i += 32)
    writel(0xffffffff, base + GIC_DIST_ENABLE_CLEAR + i * 4 / 32);

  writel(1, base + GIC_DIST_CTRL);
}

/* this must do for each CPU */
static void gic_cpu_init(struct gic_chip_data *gic) {
  void *dist_base = gic_data_dist_base(gic);
  void *base      = gic_data_cpu_base(gic);

#define smp_processor_id(...) 0
  /* FIXME: smp_processor_id should be implemented */
  unsigned int cpu_mask, cpu = smp_processor_id();
  int i;

  /*
   * Get what the GIC says our CPU mask is.
   */
  cpu_mask         = gic_get_cpumask(gic);
  gic_cpu_map[cpu] = cpu_mask;

  printf("gic: this cpu mask: %x\n", cpu_mask);

  /*
   * Clear our mask from the other map entries in case they're
   * still undefined.
   */
  for (i = 0; i < NR_GIC_CPU_IF; i++)
    if (i != cpu) {
      gic_cpu_map[i] = 0xff;
      gic_cpu_map[i] &= ~cpu_mask;
    }

  /*
   * Deal with the banked PPI and SGI interrupts - disable all
   * PPI interrupts, ensure all SGI interrupts are enabled.
   */
  writel(0xffff0000, dist_base + GIC_DIST_ENABLE_CLEAR);
  writel(0x0000ffff, dist_base + GIC_DIST_ENABLE_SET);

  /*
   * Set priority on PPI and SGI interrupts
   */
  for (i = 0; i < 32; i += 4)
    writel(0xa0a0a0a0, dist_base + GIC_DIST_PRI + i * 4 / 4);

  writel(0xf0, base + GIC_CPU_PRIMASK);
  writel(1, base + GIC_CPU_CTRL);
}

#if 1
#ifndef for_each_cpu
#define for_each_cpu(cpu, mask)                                                \
  for ((cpu) = 0; (cpu) < 1; (cpu)++, (void)(mask))
#endif
void gic_raise_softirq(const void *mask, unsigned int irq) {
  int cpu;
  unsigned long map = 0;

  /* Convert our logical CPU mask into a physical one. */
  for_each_cpu(cpu, mask) map |= gic_cpu_map[cpu];

  /*
   * Ensure that stores to Normal memory are visible to the
   * other CPUs before issuing the IPI.
   */
  //	dsb();

  /* this always happens on GIC0 */
  writel(map << 16 | irq, gic_data_dist_base(&gic_data) + GIC_DIST_SOFTINT);
}
#endif

void gic_init(void) {
  struct gic_chip_data *gic;
  int gic_irqs;

  gic = &gic_data;

  /*
   * Find out how many interrupts are supported.
   * The GIC only supports up to 1020 interrupt sources.
   */
  gic_irqs = readl(gic_data_dist_base(gic) + GIC_DIST_CTR) & 0x1f;
  gic_irqs = (gic_irqs + 1) * 32;
  if (gic_irqs > 1020)
    gic_irqs = 1020;
  gic->gic_irqs = gic_irqs;

  gic_dist_init(gic);
  gic_cpu_init(gic);
  gic_cpuif_setup();
  /* register this irq chip */
  register_irq_chip(&gic_chip);

  /* enable CPSR IRQ bit */
  //	enable_core_irq();
}

#if 1
/* this is for emulation only, and SHOULD be removed
 * when the rom.bin is OK.
 */
extern void irq_x9_emu(void);
void gic_emu_init(void) {
  /* copy irq vector to iRAM */
  // memcpy((void *)0x3c000000, irq_x9_emu, 0x1000);

  /* map iRAM to 0x00000000 */
  // writel(1, 0x21e09820);

  gic_init();
}
module_init(gic_emu_init);
#endif

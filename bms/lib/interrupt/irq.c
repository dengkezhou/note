/*
 * wartis@2014/05/21: ported from arch/arm/kernel/irq.c
 */

#include <common.h>
#include <irq.h>
#include <asm/errno.h>
#include <asm/riscv/ptrace.h>

#define MAX_IRQ_COUNT 256

static struct irq_chip *irqchip = NULL;
static struct irq_desc irqs[MAX_IRQ_COUNT];
static int irq_count = 0;

int show_interrupts(void) {
  int i;

  printf("%10s%10s    %-20s\n", "IRQ", "Count", "Name");
  for (i = 0; i < irq_count; i++) {
    printf("%10d%10lld    %-20s\n", irqs[i].irq, irqs[i].count, irqs[i].name);
  }

  return 0;
}

void asm_do_IRQ(void *regs) {
  if (irqchip)
    irqchip->irq_handle(regs);
}

/*
 * handle_IRQ handles all hardware IRQ's.  Decoded IRQs should
 * not come via this function.  Instead, they should provide their
 * own 'handler'.  Used by platform code implementing C-based 1st
 * level decoding.
 */
void handle_IRQ(unsigned int irq, void *regs) {
  int i, h = 0;

  /* for each possiblly relevant desc */
  for (i = 0; i < irq_count; i++) {
    if (irqs[i].irq == irq) {
      irqs[i].handle_irq(irq, irqs[i].platdata);
      irqs[i].count++;
      h = 1;

      if (irqchip && irqchip->irq_eoi)
        irqchip->irq_eoi(&(irqs[i].irq_data));
    }
  }

  if (!h)
    printf("unregisterd IRQ(%d)\n", irq);
}

struct irq_data *get_irq_data(unsigned int irq) {
  for (int i = 0; i < irq_count; i++) {
    if (irqs[i].irq == irq)
      return &(irqs[i].irq_data);
  }

  return NULL;
}

void enable_irq(unsigned int irq) {
  struct irq_data *irq_data = get_irq_data(irq);
  if (irq_data && irqchip)
    irqchip->irq_unmask(irq_data);
}

void disable_irq(unsigned int irq) {
  struct irq_data *irq_data = get_irq_data(irq);
  if (irq_data && irqchip)
    irqchip->irq_mask(irq_data);
}

int irq_set_affinity(unsigned int irq, unsigned int mask) {
  struct irq_data *irq_data = get_irq_data(irq);
  if (irq_data && irqchip)
    return irqchip->irq_set_affinity(irq_data, mask);

  return -EINVAL;
}

int request_irq(unsigned int irq, irq_handler_t handler, const char *name,
                void *dev) {
  int i;

  //	printf("%s:%d, %p, %p, %s, %d\n", __func__, __LINE__,
  //				irqchip, handler, name, irq);
  if (!irqchip)
    return -1;

  if (!handler || !name)
    return -EINVAL;

  /* check duplicated name */
  for (i = 0; i < irq_count; i++) {
    if (strcmp(irqs[i].name, name) == 0) {
      printf("request IRQ%d failed, name(%s) already exists\n", irq, name);
      return -EINVAL;
    }
  }

  /* check sharment */
  for (i = 0; i < irq_count; i++)
    if (irqs[i].irq == irq)
      printf("sharing IRQ with (%s)\n", irqs[i].name);

  /* register */
  irqs[irq_count].irq        = irq;
  irqs[irq_count].handle_irq = handler;
  irqs[irq_count].name       = name;
  irqs[irq_count].platdata   = dev;
  struct irq_data *irq_data  = &(irqs[irq_count].irq_data);
  irq_data->irq              = irq;
  irq_data->cpu              = 0;

  irqchip->irq_unmask(irq_data);

  irq_count++;
  return 0;
}

/*for test case need different irq handler*/
int replace_irq(unsigned int irq, irq_handler_t handler, const char *name,
                void *dev) {
  int i;

  //	printf("%s:%d, %p, %p, %s, %d\n", __func__, __LINE__,
  //				irqchip, handler, name, irq);
  if (!irqchip)
    return -1;

  if (!handler || !name)
    return -EINVAL;

  /* check duplicated name */
  for (i = 0; i < irq_count; i++) {
    if (strcmp(irqs[i].name, name) == 0) {
      irqs[i].irq               = irq;
      irqs[i].handle_irq        = handler;
      irqs[i].name              = name;
      irqs[i].platdata          = dev;
      struct irq_data *irq_data = &(irqs[irq_count].irq_data);
      irq_data->irq             = irq;
      irq_data->cpu             = 0;

      irqchip->irq_unmask(irq_data);
      printf("request IRQ%d , name(%s) replace succeeded\n", irq, name);
      return 0;
    }
  }
  printf("request IRQ%d , name(%s) replace failed\n", irq, name);
  return -EINVAL;
}

int register_irq_chip(struct irq_chip *chip) {
  irqchip = chip;
  return 0;
}

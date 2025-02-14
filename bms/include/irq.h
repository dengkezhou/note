#ifndef __IRQ_H__
#define __IRQ_H__

#define IRQ_PRIORITY_0 0
#define IRQ_PRIORITY_1 1
#define IRQ_PRIORITY_2 2
#define IRQ_PRIORITY_3 3
#define IRQ_PRIORITY_4 4
#define IRQ_PRIORITY_5 5
#define IRQ_PRIORITY_6 6
#define IRQ_PRIORITY_7 7


typedef int (*irq_handler_t)(int, void *);

struct irq_data {
  unsigned int irq;
  unsigned int cpu;
};

struct irq_desc {
  const char *name;
  irq_handler_t handle_irq;
  struct irq_data irq_data;
  unsigned int irq;
  unsigned int resv;
  unsigned long long count;
	void *platdata;
};

struct irq_chip {

  const char *name;
  void (*irq_enable)(struct irq_data *irq_data);
  void (*irq_disable)(struct irq_data *irq_data);

  void (*irq_ack)(struct irq_data *irq_data);
  void (*irq_mask)(struct irq_data *irq_data);
  void (*irq_unmask)(struct irq_data *irq_data);
  void (*irq_eoi)(struct irq_data *irq_data);

  int (*irq_set_type)(struct irq_data *irq_data, unsigned int type);
  void (*irq_handle)(void *regs);

  int (*irq_set_affinity)(struct irq_data *irq_data, unsigned int mask);
};

extern int show_interrupts(void);
extern void handle_IRQ(unsigned int irq, void *regs);
extern void enable_irq(unsigned int irq);
extern void disable_irq(unsigned int irq);
extern int irq_set_affinity(unsigned int irq, unsigned int mask);
extern void itcs_set_irq_priority(int irq_num, uint32_t prio);
extern uint32_t itcs_get_irq_priority(int irq_num);
extern void gic_raise_softirq(const void *mask, unsigned int irq);
extern int request_irq(unsigned int irq, irq_handler_t handler,
                       const char *name, void *dev);
extern int register_irq_chip(struct irq_chip *chip);
extern int replace_irq(unsigned int irq, irq_handler_t handler,
                       const char *name, void *dev);
extern void asm_do_IRQ(void *regs);
/*
 * Return value for chip->irq_set_affinity()
 *
 * IRQ_SET_MASK_OK  - OK, core updates irq_data.affinity
 * IRQ_SET_MASK_NOCPY   - OK, chip did update irq_data.affinity
 */
enum {
  IRQ_SET_MASK_OK = 0,
  IRQ_SET_MASK_OK_NOCOPY,
  IRQ_SET_MASK_OK_DONE,
};

/*
 * IRQ line status.
 *
 * Bits 0-7 are the same as the IRQF_* bits in linux/interrupt.h
 *
 * IRQ_TYPE_NONE        - default, unspecified type
 * IRQ_TYPE_EDGE_RISING     - rising edge triggered
 * IRQ_TYPE_EDGE_FALLING    - falling edge triggered
 * IRQ_TYPE_EDGE_BOTH       - rising and falling edge triggered
 * IRQ_TYPE_LEVEL_HIGH      - high level triggered
 * IRQ_TYPE_LEVEL_LOW       - low level triggered
 * IRQ_TYPE_LEVEL_MASK      - Mask to filter out the level bits
 * IRQ_TYPE_SENSE_MASK      - Mask for all the above bits
 * IRQ_TYPE_DEFAULT     - For use by some PICs to ask irq_set_type
 *                to setup the HW to a sane default (used
 *                                by irqdomain map() callbacks to synchronize
 *                                the HW state and SW flags for a newly
 *                                allocated descriptor).
 *
 * IRQ_TYPE_PROBE       - Special flag for probing in progress
 *
 * Bits which can be modified via irq_set/clear/modify_status_flags()
 * IRQ_LEVEL            - Interrupt is level type. Will be also
 *                updated in the code when the above trigger
 *                bits are modified via irq_set_irq_type()
 * IRQ_PER_CPU          - Mark an interrupt PER_CPU. Will protect
 *                it from affinity setting
 * IRQ_NOPROBE          - Interrupt cannot be probed by autoprobing
 * IRQ_NOREQUEST        - Interrupt cannot be requested via
 *                request_irq()
 * IRQ_NOTHREAD         - Interrupt cannot be threaded
 * IRQ_NOAUTOEN         - Interrupt is not automatically enabled in
 *                request/setup_irq()
 * IRQ_NO_BALANCING     - Interrupt cannot be balanced (affinity set)
 * IRQ_MOVE_PCNTXT      - Interrupt can be migrated from process context
 * IRQ_NESTED_TRHEAD        - Interrupt nests into another thread
 * IRQ_PER_CPU_DEVID        - Dev_id is a per-cpu variable
 */
enum {
  IRQ_TYPE_NONE         = 0x00000000,
  IRQ_TYPE_EDGE_RISING  = 0x00000001,
  IRQ_TYPE_EDGE_FALLING = 0x00000002,
  IRQ_TYPE_EDGE_BOTH    = (IRQ_TYPE_EDGE_FALLING | IRQ_TYPE_EDGE_RISING),
  IRQ_TYPE_LEVEL_HIGH   = 0x00000004,
  IRQ_TYPE_LEVEL_LOW    = 0x00000008,
  IRQ_TYPE_LEVEL_MASK   = (IRQ_TYPE_LEVEL_LOW | IRQ_TYPE_LEVEL_HIGH),
  IRQ_TYPE_SENSE_MASK   = 0x0000000f,
  IRQ_TYPE_DEFAULT      = IRQ_TYPE_SENSE_MASK,

  IRQ_TYPE_PROBE = 0x00000010,

  IRQ_LEVEL         = (1 << 8),
  IRQ_PER_CPU       = (1 << 9),
  IRQ_NOPROBE       = (1 << 10),
  IRQ_NOREQUEST     = (1 << 11),
  IRQ_NOAUTOEN      = (1 << 12),
  IRQ_NO_BALANCING  = (1 << 13),
  IRQ_MOVE_PCNTXT   = (1 << 14),
  IRQ_NESTED_THREAD = (1 << 15),
  IRQ_NOTHREAD      = (1 << 16),
  IRQ_PER_CPU_DEVID = (1 << 17),
};

#endif /* __IRQ_H__ */

#ifndef __GPIO_IRQ_H__
#define __GPIO_IRQ_H__

#include <irq.h>

#define BANK_NUM 32

#define div_up(a, b) (a + b - 1) / b

enum {
  GPIO_LEVEL_HIGH,
  GPIO_LEVEL_LOW,
  GPIO_EDGE_RISING,
  GPIO_EDGE_FALLING,
};

typedef struct gpio_single {
  const char *name;
  bool inited;
  irq_handler_t handler;
  char *private_data;
} gpio_single_t;

typedef struct gpio_bank {
  char name[16];
  int irq;
  int id;
  domain_t sysmode;
  bool requested;
  gpio_single_t gpios[BANK_NUM];
} gpio_bank_t;

int gpio_request_irq(domain_t domain, int index, irq_handler_t handler,
                     int flags, const char *name, void *dev);
int gpio_replace_irq(domain_t domain, int index, irq_handler_t handler,
                     int flags, const char *name, void *dev);
void gpio_irq_enable(domain_t sysmode, int index);
void gpio_irq_disable(domain_t sysmode, int index);
void gpio_irq_mask(domain_t sysmode, int index);
void gpio_irq_unmask(domain_t sysmode, int index);
int gpio_to_irq(domain_t sysmode, int index);
void gpio_irq_init(void);
#endif

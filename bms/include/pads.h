#ifndef __PADS_H__
#define __PADS_H__

#include <common.h>

enum { PADS_MODE_IN, PADS_MODE_OUT, PADS_MODE_FUNC };

enum { PADS_PULL_DOWN, PADS_PULL_UP, PADS_PULL_NO };

enum { FPGA_BIT_V_RGMII, FPGA_BIT_V_EMMC, FPGA_BIT_V_OSPI, FPGA_BIT_V_MAX };

enum { PADS_SELECTOR_PULLDOWN, PADS_SELECTOR_PULLUP};

#define PADS_CONFIG_IO(mode, n)                                                \
  (((mode == CPU) ? ITCS_C_IOM_BASE : ITCS_S_IOM_BASE) + 0x4 * n)

#define PADS_MUXMODE_OFFSET      0
#define PADS_MUXMODE_MASK        (0x7 << PADS_MUXMODE_OFFSET)
#define PADS_DRSELECTOR_OFFSET   8
#define PADS_DRSELECTOR_MASK     (0xf << PADS_DRSELECTOR_OFFSET)
#define PADS_INPUTEN_OFFSET      12
#define PADS_INPUTEN_MASK        (1 << PADS_INPUTEN_OFFSET)
#define PADS_PULLEN_OFFSET       16
#define PADS_PULLEN_MASK         (1 << PADS_PULLEN_OFFSET)
#define PADS_PULLSELECTOR_OFFSET 17
#define PADS_PULLSELECTOR_MASK   (1 << PADS_PULLSELECTOR_OFFSET)
#define PADS_TRIGGEREN_OFFSET    20
#define PADS_TRIGGEREN_MASK      (1 << PADS_TRIGGEREN_OFFSET)

#define GET_GPIO_BASE_ADDR(mode)                                               \
  ((mode == CPU) ? ITCS_C_GPIO_BASE : ITCS_S_GPIO_BASE)
#define GPIO_BASE(mode, index)   (GET_GPIO_BASE_ADDR(mode) + 0x8 + index * 0x8)
#define GPIO_DEBC(mode)          GET_GPIO_BASE_ADDR(mode)
#define GPIO_IOCTRL(mode, index) GPIO_BASE(mode, index)
#define GPIO_IOSTS(mode, index)  (GPIO_BASE(mode, index) + 0x4)
#define GPIO_MSKINTS(mode, index)                                              \
  (GET_GPIO_BASE_ADDR(mode) + 0x1000 + index / 32 * 0x4)

#define GPIO_MSK_OFFSET 0
#define GPIO_MSK_MASK   (0xffffffff << GPIO_MSK_OFFSET)

#define GPIO_DEBOUNCE_OFFSET 0
#define GPIO_DEBOUNCE_MASK   (0x1ffff << GPIO_DEBOUNCE_OFFSET)

#define GPIO_DIRECTION_OFFSET  0
#define GPIO_DIRECTION_MASK    (1 << GPIO_DIRECTION_OFFSET)
#define GPIO_OUPUTVAL_OFFSET   1
#define GPIO_OUPUTVAL_MASK     (1 << GPIO_OUPUTVAL_OFFSET)
#define GPIO_INPUTEN_OFFSET    2
#define GPIO_INPUTEN_MASK      (1 << GPIO_INPUTEN_OFFSET)
#define GPIO_INOUT_OFFSET      0
#define GPIO_INOUT_MASK        (0x7 << GPIO_INOUT_OFFSET)
#define GPIO_DEBOUNCEEN_OFFSET 3
#define GPIO_DEBOUNCEEN_MASK   (1 << GPIO_DEBOUNCEEN_OFFSET)
#define GPIO_INTEN_OFFSET      4
#define GPIO_INTEN_MASK        (1 << GPIO_INTEN_OFFSET)
#define GPIO_INTMODE_OFFSET    5
#define GPIO_INTMODE_MASK      (0x3 << GPIO_INTMODE_OFFSET)
#define GPIO_INTMASK_OFFSET    7
#define GPIO_INTMASK_MASK      (1 << GPIO_INTMASK_OFFSET)

#define GPIO_INPUTVAL_OFFSET 0
#define GPIO_INPUTVAL_MASK   (1 << GPIO_INPUTVAL_OFFSET)
#define GPIO_RAWINTS_OFFSET  1
#define GPIO_RAWINTS_MASK    (1 << GPIO_RAWINTS_OFFSET)
#define GPIO_EDGECNT_OFFSET  4
#define GPIO_EDGECNT_MASK    (0xf << GPIO_EDGECNT_OFFSET)

#define GPIO_MSKINTS_OFFSET(index) index
#define GPIO_MSKINTS_MASK(index)   (1 << index)

#define ENABLE  1
#define DISABLE 0

#define PADSRANGE(a, b) (b << 16 | a)
#define GetStart(range) (range & 0xffff)
#define GetEnd(range)   ((range >> 16) & 0xffff)

#define pads_readl  nbits_readl
#define pads_writel nbits_writel

#define CPU_GPIO_MAX 142
#define SAP_GPIO_MAX 33
#define RTC_GPIO_MAX 13

enum {
  PADS_FUNC0,
  PADS_FUNC1,
  PADS_FUNC2,
  PADS_FUNC3,
  PADS_FUNC4,
  PADS_FUNC5,
  PADS_FUNC6,
  PADS_FUNC7,
  PADS_FUNC_MAX,
};

#define GPIO_MODE PADS_FUNC7

struct pads_modules_bundle {
  const char *name; /* modules index */
  uint32_t id;      /* pads indexs */
  uint32_t fm;      /* func mode */
  uint32_t pt;      /* pull pattern */
  domain_t sysmode;
  uint32_t index;
  uint32_t drselector; /*defalut 4, set to f when driving at high speed*/
};

#ifdef CONFIG_DRV_SYSM

extern int itcs_pads_get_mode(domain_t sysmode, uint32_t index);
extern int itcs_pads_set_mode(domain_t sysmode, int range, int mode,
                              uint32_t high);
extern int itcs_pads_set_pull(domain_t sysmode, int range, int en,
                              uint32_t pattern);
extern int itcs_pads_get_pull(domain_t sysmode, int index);
extern int itcs_pads_set_value(domain_t sysmode, int range, uint32_t high);
extern int itcs_pads_get_value(domain_t sysmode, int index, int *mode);
extern int itcs_pads_set_drselector(domain_t sysmode, int range, uint32_t ds);
extern int itcs_pads_get_drselector(domain_t sysmode, int index);
extern int itcs_module_set_pads(domain_t sysmode, int bitmode,
                                const char *name);
extern int itcs_module_set_pads_by_index(const char *name, uint32_t index);
#else /* CONFIG_DRV_SYSM */

static inline int itcs_pads_get_mode(domain_t sysmode, uint32_t index) { return 0; }
static inline int itcs_pads_set_mode(domain_t sysmode, int range, int mode,
                              uint32_t high) { return 0; }
static inline int itcs_pads_set_pull(domain_t sysmode, int range, int en,
                              uint32_t pattern) { return 0; }
static inline int itcs_pads_get_pull(domain_t sysmode, int index) { return 0; }
static inline int itcs_pads_set_value(domain_t sysmode, int range, uint32_t high) { return 0; }
static inline int itcs_pads_get_value(domain_t sysmode, int index, int *mode) { return 0; }
static inline int itcs_pads_set_drselector(domain_t sysmode, int range, uint32_t ds) { return 0; }
static inline int itcs_pads_get_drselector(domain_t sysmode, int index) { return 0; }
static inline int itcs_module_set_pads(domain_t sysmode, int bitmode,
                                const char *name) { return 0; }
static int itcs_module_set_pads_by_index(const char *name, uint32_t index) { return 0; }
#endif
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

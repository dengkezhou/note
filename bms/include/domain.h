#ifndef __PWR_H__
#define __PWR_H__

#include <common.h>

#define RESET_CHAN(n) (1 << n)
#define RESET_ALL 0xffffffff

#define PWR_RSTC 0x0
#define PWR_CLKEN 0x4
#define PWR_PWRC 0x8
#define PWR_BUSC 0xc
#define PWR_QOSC 0x10
#define PWR_MEMP 0x14
#define PWR_IOC 0x18
#define PWR_SRST_CLKEN 0x1c

#define PWR_ALL_OFFSET 0
#define PWR_ALL_MASK (0xffffffff << PWR_ALL_OFFSET)

#define PWR_RSTC_OFFSET 0
#define PWR_RSTC_MASK (0xffffffff << PWR_RSTC_OFFSET)

#define PWR_CLKEN_OFFSET 0
#define PWR_CLKEN_MASK (0xffffffff << PWR_CLKEN_OFFSET)

#define PWR_REQ_OFFSET 0
#define PWR_REQ_MASK (1 << PWR_REQ_OFFSET)
#define PWR_ISO_OFFSET 1
#define PWR_ISO_MASK (1 << PWR_ISO_OFFSET)
#define PWR_ACK_OFFSET 4
#define PWR_ACK_MASK (1 << PWR_ACK_OFFSET)

#define PWR_BUSEN_OFFSET 0
#define PWR_BUSEN_MASK (0x3 << PWR_BUSEN_OFFSET)

#define PWR_IOC_OFFSET 0
#define PWR_IOC_MASK (1 << PWR_IOC_OFFSET)

#define pwr_readl nbits_readl
#define pwr_writel nbits_writel

#define R(d, n) (d->addr + n)

typedef struct module_power {
	char *name;
	unsigned long addr;
	domain_t mode;
	uint32_t id;
} module_power_t;

/*driver/sysm/domain_x9.c*/
/*like module_all, this for module clk*/
extern int itcs_module_enable(domain_t mode, const char *module);
extern int itcs_module_disable(domain_t mode, const char *module);
extern int itcs_module_reset(domain_t mode, const char *module);
#endif

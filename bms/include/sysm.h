#ifndef __SYSM_H__
#define __SYSM_H__

#include <asm/riscv/encoding.h>
#include <common.h>

#define CORE_C920_PRODUCTID 0x90c090d
#define CORE_E906_PRODUCTID 0x810010d

#define CPU_SYSM_BASE(cluster, regaddr) \
	(((cluster == CLUSTER0) ? ITCS_C_CPU_CLUSTER0_BASE : ITCS_C_CPU_CLUSTER1_BASE) + regaddr)
#define SAP_SYSM_BASE(regaddr) \
	(ITCS_S_SAP_BASE + regaddr)
#define SYSM_BASE(mode, core_id, regaddr) \
	((mode == CPU) ? ((core_id >= CORE_4) ? CPU_SYSM_BASE(CLUSTER1, regaddr) : CPU_SYSM_BASE(CLUSTER0, regaddr)) : SAP_SYSM_BASE(regaddr))
#define SYSM_C_RESETM 0x0
#define SYSM_C_BOOT_ADDR(id) ((id >= CORE_4) ? (0x30 + (id - CORE_4) * 4) : (0x30 + id * 4))

#define SYSM_C_CORE_SWRSTN_OFFSET(n) (n * 0x4)
#define SYSM_C_CORE_SWRSTN_MASK(n) (1 << SYSM_C_CORE_SWRSTN_OFFSET(n))
#define SYSM_C_CPU_SWRSTN_OFFSET 16
#define SYSM_C_CPU_SWRSTN_MASK (1 << SYSM_C_CPU_SWRSTN_OFFSET)

#define SYSM_C_BOOTADDR_OFFSET 0
#define SYSM_C_BOOTADDR_MASK (0xffffffff << SYSM_C_BOOTADDR_OFFSET)

enum { BRAM_MODE, L2CACHE_MODE };

typedef struct percpu_data {
	int hartid;
} percpu_data_t;

#define SYSM_C_CLKM 0x4
#define SYSM_C_CPU_CGEN_OFFSET 0
#define SYSM_C_CPU_CGEN_MASK (0x1 << SYSM_C_CPU_CGEN_OFFSET)
#define SYSM_C_AXI_CGEN_OFFSET 4
#define SYSM_C_AXI_CGEN_MASK (0x1 << SYSM_C_AXI_CGEN_OFFSET)
#define SYSM_C_REMAP_N_OFFSET 8
#define SYSM_C_REMAP_N_MASK (0x1 << SYSM_C_REMAP_N_OFFSET)

enum {
	BOOTM_LPDDR4_DDR1_NO_INTLEAVE = 0xd,
	BOOTM_LPDDR4_NO_INTLEAVE = 0xf,
	BOOTM_LPDDR4_WITH_INTLEAVE = 0xe,
	BOOTM_DDR_NO_INTLEAVE = 0x1,
	BOOTM_DDR_WITH_INTLEAVE = 0x2,
	BOOTM_DDR1_NO_INTLEAVE = 0x3
};

#define SYSM_BOOTM 0x8
#define SYSM_BOOTM_OFFSET 0
#define SYSM_BOOTM_MASK (0xf << SYSM_BOOTM_OFFSET)

#define SYSM_C_RVBAM 0x2c
#define SYSM_C_REMAP_CTRL_OFFSET(n) ((n >= CORE_4) ? (0x4 * (n - CORE_4)) : (0x4 * n))
#define SYSM_C_REMAP_CTRL_MASK(n) (1 << SYSM_C_REMAP_CTRL_OFFSET(n))
#define SYSM_C_SYSMAP_CTRL_OFFSET 16
#define SYSM_C_SYSMAP_CTRL_MASK (1 << SYSM_C_SYSMAP_CTRL_OFFSET)

enum {
	ITCS_SYSMAP_SECURITY = (1 << 0),
	ITCS_SYSMAP_SHAREABLE = (1 << 1),
	ITCS_SYSMAP_BUFFERABLE = (1 << 2),
	ITCS_SYSMAP_CACHEABLE = (1 << 3),
	ITCS_SYSMAP_STRONGORDE = (1 << 4),
	ITCS_SYSMAP_DEVICE = ITCS_SYSMAP_STRONGORDE | ITCS_SYSMAP_SHAREABLE |
			     ITCS_SYSMAP_SECURITY,
	ITCS_SYSMAP_MEMORY = ITCS_SYSMAP_CACHEABLE | ITCS_SYSMAP_BUFFERABLE |
			     ITCS_SYSMAP_SHAREABLE | ITCS_SYSMAP_SECURITY
};

enum { PLIC_HIGH_LEVEL, PLIC_PULSE };

#define SYSM_C_PLIC_INT_CFG(n) (0x70 + n / 32 * 4)
#define SYSM_C_PLIC_INT_OFFSET(n) (n % 32)
#define SYSM_C_PLIC_INT_MASK(n) (1 << SYSM_C_PLIC_INT_OFFSET(n))

#define SYSM_C_BASE_ADDR(n) (0x90 + n * 4)
#define SYSM_C_SYSMAP_FLAG(n) (0xb0 + n / 4 * 4)
#define SYSM_C_SYSMAPA 0xb0
#define SYSM_C_SYSMAPB 0xb4

#define SYSM_C_BASE_ADDR_OFFSET 0
#define SYSM_C_BASE_ADDR_MASK (0xfffffff << SYSM_C_BASE_ADDR_OFFSET)

#define SYSM_C_SYSMAP_FLAG_OFFSET(n) (8 * (n % 4))
#define SYSM_C_SYSMAP_FLAG_MASK(n) (0x1f << SYSM_C_SYSMAP_FLAG_OFFSET(n))

#define INSERT_FIELD(val, which, fieldval) \
	(((val) & ~(which)) | ((fieldval) * ((which) & ~((which)-1))))

extern int itcs_sysmap_config_region(uint32_t idx, uint64_t base_addr,
				     uint32_t attr);
extern int itcs_sysm_set_plic_trigger_level(domain_t domain, int irq, int type);
extern percpu_data_t *itcs_get_percpu_data(void);
extern int itcs_sysm_identity(void);
extern int itcs_sysm_set_bootaddr(domain_t mode, int id, uint64_t boot_addr);
extern int itcs_sysm_get_boot_mode(domain_t domain);
extern int itcs_sysm_switch_bram(domain_t domain, int mode);
extern void itcs_switch_mode(unsigned long next_mode, unsigned long next_addr);
extern int itcs_send_ecall(unsigned long eid, unsigned long fid,
			   unsigned long a0, unsigned long a1,
			   unsigned long a2);
extern void init_system(void);

/************************************************************************************/

#define SYSM_S_RESETM 0x0

#define SYSM_S_CPU_SWRSTN_OFFSET 0x0
#define SYSM_S_CPU_SWRSTN_MASK (1 << SYSM_S_CPU_SWRSTN_OFFSET)
#define SYSM_S_APB_SWRSTN_OFFSET 0x4
#define SYSM_S_APB_SWRSTN_MASK (1 << SYSM_S_APB_SWRSTN_OFFSET)

enum { WIRE5_JTAGS, WIRE2_JTAGS };

enum { IAHB, DAHB };

enum {
	IAHB_1MB = 0xfff,
	IAHB_2MB = 0xffe,
	IAHB_4MB = 0xffc,
	IAHB_8MB = 0xff8,
	IAHB_16MB = 0xff0,
	IAHB_32MB = 0xfe0,
	IAHB_64MB = 0xfc0,
	IAHB_128MB = 0xf80,
	IAHB_256MB = 0xf00,
	IAHB_512MB = 0xe00,
	IAHB_1GB = 0xc00,
	IAHB_2GB = 0x800,
	IAHB_4GB = 0x000,
};

#define SYSM_S_REMAP 0x10
#define SYSM_S_RESERPC 0x14
#define SYSM_S_BMU_IAHBL 0x18
#define SYSM_S_BMU_DAHBL 0x1c
#define SYSM_S_JTAGM 0x20
#define SYSM_S_SLOCK 0x30

#define SYSM_S_IAHBL_EN_OFFSET 0
#define SYSM_S_IAHBL_EN_MASK (1 << SYSM_S_IAHBL_EN_OFFSET)
#define SYSM_S_IAHBREMAP_OFFSET 1
#define SYSM_S_IAHBREMAP_MASK (0x7fffffff << SYSM_S_IAHBREMAP_OFFSET)

#define SYSM_S_RESERPC_OFFSET 0
#define SYSM_S_RESERPC_MASK (0xffffffff << SYSM_S_RESERPC_OFFSET)

#define SYSM_S_REMAP_OFFSET 0
#define SYSM_S_REMAP_MASK (0xffffffff << SYSM_S_REMAP_OFFSET)

#define SYSM_S_IAHBL_BASE_OFFSET 0
#define SYSM_S_IAHBL_BASE_MASK (0xfff << SYSM_S_IAHBL_BASE_OFFSET)
#define SYSM_S_IAHBL_MASK_OFFSET 16
#define SYSM_S_IAHBL_MASK_MASK (0xfff << SYSM_S_IAHBL_MASK_OFFSET)

#define SYSM_S_DAHBL_BASE_OFFSET 0
#define SYSM_S_DAHBL_BASE_MASK (0xfff << SYSM_S_DAHBL_BASE_OFFSET)
#define SYSM_S_DAHBL_END_OFFSET 16
#define SYSM_S_DAHBL_END_MASK (0xfff << SYSM_S_DAHBL_END_OFFSET)

#define SYSM_S_JTAGMODE_OFFSET 0
#define SYSM_S_JTAGMODE_MASK (0x1 << SYSM_S_JTAGMODE_OFFSET)

#define SYSM_S_SECURTY_OFFSET 0
#define SYSM_S_SECURTY_MASK (1 << SYSM_S_SECURTY_OFFSET)

extern int itcs_sysm_switch_jtag_mode(domain_t domain, int mode);
extern int itcs_sysm_set_ahb_range(domain_t domain, int mode, uint32_t start,
				   uint32_t end);
extern void itcs_sysm_set_security(bool sec);
extern void itcs_sysm_remap(domain_t domain, uint64_t addr);

#define SYSM_S_JTAG_CONTROL 0xd2f09400
#define SYSM_S_STATE 0xd2f09404
#define SYSM_S_JTAG_SWITCH_OFFSET 0
#define SYSM_S_JTAG_SWITCH_MASK (1 << SYSM_S_JTAG_SWITCH_OFFSET)
#define SYSM_S_CJTAGEN_OFFSET 1
#define SYSM_S_CJTAGEN_MASK (1 << SYSM_S_CJTAGEN_OFFSET)
#define SYSM_S_EJTAGEN_OFFSET 2
#define SYSM_S_EJTAGEN_MASK (1 << SYSM_S_EJTAGEN_OFFSET)

#define SYSM_S_STATE_OFFSET 0
#define SYSM_S_STATE_MASK (0xffffffff << SYSM_S_STATE_OFFSET)

enum { C920_JTAGEN, E906_JTAGEN, OTP_LOCK, SYSM_LOCK, OTP_FLAGS, PUFC_VLD };
#define SYSM_S_STATE_BIT_OFFSET(n) n
#define SYSM_S_STATE_BIT_MASK(n) (1 << SYSM_S_STATE_BIT_OFFSET(n))

extern void itcs_sysm_jtag_control(domain_t domain, int en);
extern void itcs_sysm_switch_jtag(domain_t domain);
extern uint32_t itcs_sysm_get_state(void);
enum { CORE_0, CORE_1, CORE_2, CORE_3, CORE_4, CORE_5, CORE_6, CORE_CPU, CORE_MAX };

enum { LOW_POWER, NORMAL_MODE = 0x3 };

#define SYSM_C_PWRM_CPU 0xc
#define SYSM_C_PWRM_CORE(n) ((n >= CORE_4) ? (0x10 + 0x4 * (n - CORE_4)) : (0x10 + 0x4 * n))
#define SYSM_C_IOMK 0x20
#define SYSM_C_MPDM 0x24
#define SYSM_C_PAD_DBG_MASK 0x40
#define SYSM_C_PAD_DBGRQ_B 0x44
#define SYSM_C_PAD_JDB_PM 0x48
#define SYSM_C_PAD_LPMD_B 0x4c
#define SYSM_C_L2CACHE 0x50

#define SYSM_C_POWERON_OFFSET 0
#define SYSM_C_POWERON_MASK (1 << SYSM_C_POWERON_OFFSET)
#define SYSM_C_ISOPOWER_OFFSET 4
#define SYSM_C_ISOPOWER_MASK (1 << SYSM_C_ISOPOWER_OFFSET)
#define SYSM_C_POWERACK_OFFSET 8
#define SYSM_C_POWERACK_MASK (1 << SYSM_C_POWERACK_OFFSET)

#define SYSM_C_LPMD_OFFSET(n) (0x4 * n)
#define SYSM_C_LPMD_MASK(n) (0x3 << SYSM_C_LPMD_OFFSET(n))

#define SYSM_C_COREID_OFFSET(n) ((n >= CORE_4) ? (0x4 * (n - CORE_4)) : (0x4 * n))
#define SYSM_C_COREID_MASK(n) (1 << SYSM_C_COREID_OFFSET(n))

#define SYSM_C_FLUSH_REQ_OFFSET 0
#define SYSM_C_FLUSH_REQ_MASK (1 << SYSM_C_FLUSH_REQ_OFFSET)
#define SYSM_C_FLUSH_DONE_OFFSET 4
#define SYSM_C_FLUSH_DONE_MASK (1 << SYSM_C_FLUSH_DONE_OFFSET)
#define SYSM_C_NO_OP_OFFSET 8
#define SYSM_C_NO_OP_MASK (1 << SYSM_C_NO_OP_OFFSET)

#define sysm_readl nbits_readl
#define sysm_writel nbits_writel

extern int itcs_core_enable(domain_t mode, int coreid, uint64_t boot_addr,
			    uint64_t remap_addr);
extern int itcs_core_disable(domain_t mode, int coreid);
extern void itcs_mask_core_debug(domain_t domain, int coreid, int flags);
extern void hang(void);
#endif

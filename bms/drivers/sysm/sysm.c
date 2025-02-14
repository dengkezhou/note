#include <common.h>
#include <sysm.h>
#include <cache.h>
#include <asm/riscv/encoding.h>
#include <sbi/sbi_ecall_interface.h>

void hang(void)
{
	while (1)
		__WFI();
}

int itcs_send_ecall(unsigned long eid, unsigned long fid, unsigned long a0,
		    unsigned long a1, unsigned long a2)
{
	return SBI_ECALL(eid, fid, a0, a1, a2);
}

static percpu_data_t cpus[NR_CPUS] = { 0 };
percpu_data_t *itcs_get_percpu_data(void)
{
#ifdef CONFIG_RISCV_SMODE
	return (percpu_data_t *)__get_SSCRATCH();
#else
	return (percpu_data_t *)__get_MSCRATCH();
#endif
}

extern void strap_entry(void);
void itcs_switch_mode(unsigned long next_mode, unsigned long next_addr)
{
#ifdef CONFIG_C920
	unsigned long val;
	register unsigned long ra asm("ra");

	/* get ra value */
	asm volatile("add %0, ra, zero" : "=r"(ra));

	switch (next_mode) {
	case PRV_M:
		break;
	case PRV_S:
		if (!is_isa_supported('S'))
			hang();
		break;
	case PRV_U:
		if (!is_isa_supported('U'))
			hang();
		break;
	default:
		hang();
	}

	val = __get_MSTATUS();
	val = INSERT_FIELD(val, MSTATUS_MPP, next_mode);
	val = INSERT_FIELD(val, MSTATUS_MPIE, 0);
	__set_MSTATUS(val);

	if (next_addr)
		__set_MEPC(next_addr);
	else
		__set_MEPC(ra);

	if (next_mode == PRV_S) {
		__set_STVEC((uint64_t)(&strap_entry));
		__set_SATP(0x0);
	}

	__asm__ __volatile__("mret");
	hang();
#endif
}

void itcs_set_pmp_config(void)
{
	mpu_region_attr_t attr;

	attr.r = 1;
	attr.w = 1;
	attr.x = 1;
	attr.a = ADDRESS_MATCHING_TOR;
	attr.l = 0;
	csi_mpu_config_region(0, 0x18000000, REGION_SIZE_4KB, &attr, 1);
	csi_mpu_config_region(1, 0x20000000, REGION_SIZE_4KB, &attr, 1);
	csi_mpu_config_region(2, 0x40000000, REGION_SIZE_4KB, &attr, 1);
	csi_mpu_config_region(3, 0xc0000000, REGION_SIZE_4KB, &attr, 1);
	attr.x = 0;
	csi_mpu_config_region(4, 0xd0000000, REGION_SIZE_4KB, &attr, 1);
	csi_mpu_config_region(5, 0xe0000000, REGION_SIZE_4KB, &attr, 1);
#ifdef CONFIG_C920
	csi_mpu_config_region(6, 0x100000000, REGION_SIZE_4KB, &attr, 1);
	attr.x = 1;
	csi_mpu_config_region(7, 0x800000000, REGION_SIZE_4KB, &attr, 1);
#elif defined(CONFIG_E906)
	csi_mpu_config_region(6, 0xffffffff, REGION_SIZE_4KB, &attr, 1);
#endif
}

/* Only config core c920 */
int itcs_sysmap_config_region(uint32_t idx, uint64_t base_addr, uint32_t attr)
{
	uint32_t addr = 0;

	if (idx > 7)
		return -1;

	addr = base_addr >> 12;

	/* write enable */
	sysm_writel(SYSM_BASE(CPU, CORE_0, SYSM_C_RVBAM), SYSM_C_SYSMAP_CTRL_MASK,
		    SYSM_C_SYSMAP_CTRL_OFFSET, 1);

	/* set base addr */
	sysm_writel(SYSM_BASE(CPU, CORE_0, SYSM_C_BASE_ADDR(idx)),
		    SYSM_C_BASE_ADDR_MASK, SYSM_C_BASE_ADDR_OFFSET, addr);
	/* set flags */
	sysm_writel(SYSM_BASE(CPU, CORE_0, SYSM_C_SYSMAP_FLAG(idx)),
		    SYSM_C_SYSMAP_FLAG_MASK(idx),
		    SYSM_C_SYSMAP_FLAG_OFFSET(idx), attr);
	/* write disable */
	sysm_writel(SYSM_BASE(CPU, CORE_0, SYSM_C_RVBAM), SYSM_C_SYSMAP_CTRL_MASK,
		    SYSM_C_SYSMAP_CTRL_OFFSET, 0);
	return 0;
}

int itcs_sysm_set_plic_trigger_level(domain_t domain, int irq, int type)
{
	int id = irq - C_WDT_IRQn;

	if (domain != CPU)
		return -1;

	sysm_writel(SYSM_BASE(domain, CORE_0, SYSM_C_PLIC_INT_CFG(id)),
		    SYSM_C_PLIC_INT_MASK(id), SYSM_C_PLIC_INT_OFFSET(id), type);
	return 0;
}

void init_system(void)
{
	unsigned long mharted = __get_MHARTID();
#ifdef CONFIG_RISCV_SMODE
	itcs_set_pmp_config();
#if 0
  /* enable ecall delegate */
  uint64_t medeleg = __get_MEDELEG();
  medeleg |= (1 << 9);
  __set_MEDELEG(medeleg);
#endif
	/* enable interrupt delegate */
	uint64_t mideleg = __get_MIDELEG();
	mideleg |= 0x222;
	__set_MIDELEG(mideleg);

	/* enable mcounteren for s-mode */
	__set_MCOUNTEREN(0xffffffff);

	cpus[mharted].hartid = mharted;
	__set_SSCRATCH((unsigned long)&cpus[mharted]);
#else
	cpus[mharted].hartid = mharted;
	__set_MSCRATCH((unsigned long)&cpus[mharted]);
#endif
}

int itcs_sysm_set_bootaddr(domain_t domain, int id, uint64_t boot_addr)
{
	if (id < 0 || id >= NR_CPUS)
		return -1;

	if (domain == CPU) {
		// set remap en
		sysm_writel(SYSM_BASE(domain, id, SYSM_C_RVBAM),
			    SYSM_C_REMAP_CTRL_MASK(id),
			    SYSM_C_REMAP_CTRL_OFFSET(id), 1);
		/* set boot addr */
		sysm_writel(SYSM_BASE(domain, id, SYSM_C_BOOT_ADDR(id)),
			    SYSM_C_BOOTADDR_MASK, SYSM_C_BOOTADDR_OFFSET,
			    (uint32_t)(boot_addr >> 8));
		// set remap dis
		sysm_writel(SYSM_BASE(domain, id, SYSM_C_RVBAM),
			    SYSM_C_REMAP_CTRL_MASK(id),
			    SYSM_C_REMAP_CTRL_OFFSET(id), 0);
	} else {
		sysm_writel(SYSM_BASE(domain, CORE_0, SYSM_S_RESERPC),
			    SYSM_S_RESERPC_MASK, SYSM_S_RESERPC_OFFSET,
			    (uint32_t)boot_addr);
	}
	return 0;
}

void itcs_sysm_remap(domain_t domain, uint64_t addr)
{
	if (domain != SAP)
		return;

	sysm_writel(SYSM_BASE(domain, CORE_0, SYSM_S_RESETM), SYSM_S_CPU_SWRSTN_MASK,
		    SYSM_S_CPU_SWRSTN_OFFSET, 0);
	sysm_writel(SYSM_BASE(domain, CORE_0, SYSM_S_REMAP), SYSM_S_REMAP_MASK,
		    SYSM_S_REMAP_OFFSET, ((uint32_t)addr | 0x1));
	sysm_writel(SYSM_BASE(domain, CORE_0, SYSM_S_RESETM), SYSM_S_CPU_SWRSTN_MASK,
		    SYSM_S_CPU_SWRSTN_OFFSET, 1);
}

int itcs_sysm_switch_bram(domain_t domain, int mode)
{
	uint32_t val;

	if (mode != BRAM_MODE && mode != L2CACHE_MODE)
		return -1;

	if (domain != CPU)
		return -1;

	val = ((mode == L2CACHE_MODE) ? 1 : 0);
	sysm_writel(SYSM_BASE(domain, CORE_0, SYSM_C_CLKM), SYSM_C_REMAP_N_MASK,
		    SYSM_C_REMAP_N_OFFSET, val);
#ifdef CONFIG_CCI_COHERENCY_EN
	sysm_writel(SYSM_BASE(domain, CORE_4, SYSM_C_CLKM), SYSM_C_REMAP_N_MASK,
		    SYSM_C_REMAP_N_OFFSET, val);
#endif
	return 0;
}

int itcs_sysm_switch_jtag_mode(domain_t domain, int mode)
{
	if (domain != SAP)
		return -1;

	if (mode != WIRE5_JTAGS && mode != WIRE2_JTAGS)
		return -1;

	sysm_writel(SYSM_BASE(domain, CORE_0, SYSM_S_JTAGM), SYSM_S_JTAGMODE_MASK,
		    SYSM_S_JTAGMODE_OFFSET, mode);
	return 0;
}

uint32_t itcs_sysm_get_state(void)
{
	return sysm_readl(SYSM_S_STATE, SYSM_S_STATE_MASK, SYSM_S_STATE_OFFSET);
}

void itcs_sysm_jtag_control(domain_t domain, int en)
{
	uint32_t tmp;

	if (domain == CPU)
		sysm_writel(SYSM_S_JTAG_CONTROL, SYSM_S_CJTAGEN_MASK,
			    SYSM_S_CJTAGEN_OFFSET, en);
	else if (domain == SAP)
		sysm_writel(SYSM_S_JTAG_CONTROL, SYSM_S_EJTAGEN_MASK,
			    SYSM_S_EJTAGEN_OFFSET, en);

	tmp = itcs_sysm_get_state();
	printf("C920 JTAG %s, E906 JTAG %s\n",
	       (tmp & SYSM_S_STATE_BIT_MASK(C920_JTAGEN)) ? "enable" :
								  "disable",
	       (tmp & SYSM_S_STATE_BIT_MASK(E906_JTAGEN)) ? "enable" :
								  "disable");
}

void itcs_sysm_switch_jtag(domain_t domain)
{
	if (domain == CPU)
		sysm_writel(SYSM_S_JTAG_CONTROL, SYSM_S_JTAG_SWITCH_MASK,
			    SYSM_S_JTAG_SWITCH_OFFSET, 1);
	else if (domain == SAP)
		sysm_writel(SYSM_S_JTAG_CONTROL, SYSM_S_JTAG_SWITCH_MASK,
			    SYSM_S_JTAG_SWITCH_OFFSET, 0);
}

int itcs_sysm_set_ahb_range(domain_t domain, int mode, uint32_t start,
			    uint32_t end)
{
	if (domain != SAP)
		return -1;

	switch (mode) {
	case IAHB:
		sysm_writel(SYSM_BASE(domain, CORE_0, SYSM_S_BMU_IAHBL),
			    SYSM_S_IAHBL_BASE_MASK, SYSM_S_IAHBL_BASE_OFFSET,
			    (start >> 20));
		sysm_writel(SYSM_BASE(domain, CORE_0, SYSM_S_BMU_IAHBL),
			    SYSM_S_IAHBL_MASK_MASK, SYSM_S_IAHBL_MASK_OFFSET,
			    (end & 0xfff));
		break;
	case DAHB:
		sysm_writel(SYSM_BASE(domain, CORE_0, SYSM_S_BMU_DAHBL),
			    SYSM_S_DAHBL_BASE_MASK, SYSM_S_DAHBL_BASE_OFFSET,
			    (start >> 20));
		sysm_writel(SYSM_BASE(domain, CORE_0, SYSM_S_BMU_DAHBL),
			    SYSM_S_DAHBL_END_MASK, SYSM_S_DAHBL_END_OFFSET,
			    (end >> 20));
		break;
	default:
		printf("Do not support this AHB mode: %d\n", mode);
		return -1;
	}
	return 0;
}

int itcs_sysm_identity(void)
{
#ifdef CONFIG_C920
	return CPU;
#else
	return SAP;
#endif
#if 0
	unsigned long value = 0;

	asm	volatile("csrr %0, mcpuid" : "=r"(value));
	value = (value & 0xffffffff);
//	printf("itcs_sysm_identity 0x%x\n", value);
	switch(value) {
		case CORE_C920_PRODUCTID:
			return CPU;
		case CORE_E906_PRODUCTID:
			return SAP;
		default:
			return CPU;
	}
#endif
}

void itcs_sysm_set_security(bool sec)
{
	sysm_writel(SYSM_BASE(SAP, CORE_0, SYSM_S_SLOCK), SYSM_S_SECURTY_MASK,
		    SYSM_S_SECURTY_OFFSET, (sec ? 1 : 0));
}

#ifndef CONFIG_COMPILE_SIM
int itcs_sysm_get_boot_mode(domain_t domain)
{
	return sysm_readl(SYSM_BASE(domain, CORE_0, SYSM_BOOTM), SYSM_BOOTM_MASK,
			  SYSM_BOOTM_OFFSET);
}
#endif

void itcs_mask_core_debug(domain_t domain, int coreid, int flags)
{
	sysm_writel(SYSM_BASE(domain, coreid, SYSM_C_PAD_DBG_MASK),
		    SYSM_C_COREID_MASK(coreid), SYSM_C_COREID_OFFSET(coreid),
		    flags);
}

int itcs_core_enable(domain_t domain, int coreid, uint64_t boot_addr,
		     uint64_t remap_addr)
{
	if (coreid < CORE_0 || coreid >= CORE_MAX) {
		printf("%s unsupport core id %d\n", __func__, coreid);
		return -1;
	}

	switch (domain) {
	case CPU:
		itcs_sysm_set_bootaddr(domain, coreid, boot_addr);
		sysm_writel(SYSM_BASE(domain, coreid, SYSM_C_RESETM),
			    SYSM_C_COREID_MASK(coreid),
			    SYSM_C_COREID_OFFSET(coreid), 0);
		sysm_writel(SYSM_BASE(domain, coreid, SYSM_C_PWRM_CORE(coreid)),
			    SYSM_C_POWERON_MASK, SYSM_C_POWERON_OFFSET, 1);
#if 0

			while (!pwr_readl(SYSM_BASE(domain, CORE_0, SYSM_C_PWRM_CORE(coreid)), SYSM_C_POWERACK_MASK, SYSM_C_POWERACK_OFFSET))
				;
#endif
		sysm_writel(SYSM_BASE(domain, coreid, SYSM_C_PWRM_CORE(coreid)),
			    SYSM_C_ISOPOWER_MASK, SYSM_C_ISOPOWER_OFFSET, 0);

		sysm_writel(SYSM_BASE(domain, coreid, SYSM_C_RESETM),
			    SYSM_C_CPU_SWRSTN_MASK, SYSM_C_CPU_SWRSTN_OFFSET,
			    1);
		sysm_writel(SYSM_BASE(domain, coreid, SYSM_C_RESETM),
			    SYSM_C_COREID_MASK(coreid),
			    SYSM_C_COREID_OFFSET(coreid), 1);
		break;
	case SAP:
		sysm_writel(SYSM_BASE(domain, CORE_0, SYSM_S_RESETM),
			    SYSM_S_CPU_SWRSTN_MASK, SYSM_S_CPU_SWRSTN_OFFSET,
			    0);
		itcs_sysm_set_bootaddr(domain, coreid, boot_addr);
		sysm_writel(SYSM_BASE(domain, CORE_0, SYSM_S_RESETM),
			    SYSM_S_CPU_SWRSTN_MASK, SYSM_S_CPU_SWRSTN_OFFSET,
			    1);
		break;
	default:
		printf("Do not support to enable this core: %d\n", domain);
		return -1;
	}
	return 0;
}

int itcs_core_disable(domain_t domain, int coreid)
{
	uint32_t val;
	int delays = 0;

	if (coreid < CORE_0 || coreid >= CORE_MAX) {
		printf("%s unsupport core id %d\n", __func__, coreid);
		return -1;
	}

	switch (domain) {
	case CPU:
		val = sysm_readl(SYSM_BASE(domain, coreid, SYSM_C_PAD_LPMD_B),
				 SYSM_C_LPMD_MASK(coreid),
				 SYSM_C_LPMD_OFFSET(coreid));
		while (val != LOW_POWER) {
			udelay(5);
			if (delays > 5) {
				printf("Core %d is not in IDLE status\n");
				return -1;
			}
			delays++;
		}

		sysm_writel(SYSM_BASE(domain, coreid, SYSM_C_PAD_DBG_MASK),
			    SYSM_C_COREID_MASK(coreid),
			    SYSM_C_COREID_OFFSET(coreid), 1);
		sysm_writel(SYSM_BASE(domain, coreid, SYSM_C_PWRM_CORE(coreid)),
			    SYSM_C_ISOPOWER_MASK, SYSM_C_ISOPOWER_OFFSET, 1);
		sysm_writel(SYSM_BASE(domain, coreid, SYSM_C_RESETM),
			    SYSM_C_COREID_MASK(coreid),
			    SYSM_C_COREID_OFFSET(coreid), 0);
		sysm_writel(SYSM_BASE(domain, coreid, SYSM_C_PWRM_CORE(coreid)),
			    SYSM_C_POWERON_MASK, SYSM_C_POWERON_OFFSET, 0);
		if (!coreid) {
			sysm_writel(SYSM_BASE(domain, coreid, SYSM_C_L2CACHE),
				    SYSM_C_FLUSH_REQ_MASK,
				    SYSM_C_FLUSH_REQ_OFFSET, 1);
			while (!sysm_readl(SYSM_BASE(domain, coreid, SYSM_C_L2CACHE),
					   SYSM_C_FLUSH_DONE_MASK,
					   SYSM_C_FLUSH_DONE_OFFSET))
				udelay(5);

			sysm_writel(SYSM_BASE(domain, coreid, SYSM_C_L2CACHE),
				    SYSM_C_FLUSH_REQ_MASK,
				    SYSM_C_FLUSH_REQ_OFFSET, 0);
			while (!sysm_readl(SYSM_BASE(domain, coreid, SYSM_C_L2CACHE),
					   SYSM_C_NO_OP_MASK,
					   SYSM_C_NO_OP_OFFSET))
				udelay(5);
		}
		break;
	case SAP:
		sysm_writel(SYSM_BASE(domain, CORE_0, SYSM_S_RESETM),
			    SYSM_S_CPU_SWRSTN_MASK, SYSM_S_CPU_SWRSTN_OFFSET,
			    0);
		break;
	default:
		printf("Do not support to enable this core: %d\n", domain);
		return -1;
	}
	return 0;
}

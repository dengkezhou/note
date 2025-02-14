#include <common.h>
#include <cache.h>
#include <cci.h>

static void cci_enable_snoop_dvm_reqs(unsigned int slave_id)
{
	/*
	 * Enable Snoops and DVM messages, no need for Read/Modify/Write as
	 * rest of bits are write ignore
	 */
	writel(DVM_EN_BIT | SNOOP_EN_BIT, CCI400_BASE +
		      SLAVE_IFACE_OFFSET(slave_id) + SNOOP_CTRL_REG);
#ifdef CONFIG_CACHE
	itcs_dcache_flush_range(CCI400_BASE + SLAVE_IFACE_OFFSET(slave_id) + SNOOP_CTRL_REG, 4);
#endif
#ifdef CONFIG_C920
	asm("sync.is");
#endif
	/*
	 * Wait for the completion of the write to the Snoop Control Register
	 * before testing the change_pending bit
	 */

	/* Wait for the dust to settle down */
	while ((readl(CCI400_BASE + STATUS_REG) & CHANGE_PENDING_BIT) != 0U)
		;
}

void cci_enable_coherency(void)
{
	/* enable cci cache coherency. */
	// cci_enable_snoop_dvm_reqs(0);
	// cci_enable_snoop_dvm_reqs(1);
	// cci_enable_snoop_dvm_reqs(2);
	cci_enable_snoop_dvm_reqs(3);
	cci_enable_snoop_dvm_reqs(4);
}

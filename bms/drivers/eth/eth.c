#include <common.h>
#include <asm/io.h>
#include <malloc.h>
#include <pads.h>
#include <eth.h>
#include <phy.h>
#include "eth_lowlevel.h"

#define GMAC0_SYSM_BASE 0xc4f01000
#define GMAC1_SYSM_BASE 0xc4f01400
#define GMAC2_SYSM_BASE 0xc4f01800
#define GMAC3_SYSM_BASE 0xd0f00400

#define GMAC_PAD_VOLTAGE_BASE (0xd2e00000 + 0x208)

#define PHY_CTL_BASE 0x30
#define PHY_CTL_USE_RMII (1 << 0)
#define PHY_CTL_USE_INT_REF_CLK (1 << 1)
#define EVEN_PREAMBLE_EN (1 << 3)

#define GMAC0_1V8_EN (1 << 1)
#define GMAC1_1V8_EN (1 << 3)
#define GMAC2_1V8_EN (1 << 5)
#define GMAC3_1V8_EN (1 << 7)

/* for 1000M. */
#define TX_PAD_DLY_REG 0x38
#define RX_PAD_DLY_REG 0x3c

#define PHASE_EN 0x1
#define PHASE_INC 0x2

#define PLL_RESET 0x4
#define PLL_LOCKED_STATUS 0x8
#define PLL_PSDONE_STATUS 0x4

#define BUS_WIDTH_REG 0x2c
#define PLL_PHASE_REG 0x40

#if defined(CONFIG_C920) && \
	(defined(CONFIG_TB_RUN_DDR) || defined(CONFIG_TB_RUN_DDR1))
#define GMAC3_ALLOC_BASE (ITCS_SDDR_ADDR + 0x20000000)
#define GMAC3_ALLOC_OFFSET (0x400000)

static volatile unsigned int gmac3_alloc_index = 0;
volatile unsigned int is_gmac3 = 0;
#endif

extern struct phy_device *marvell_probe(eth_device *dev);
extern struct phy_device *icplus_probe(eth_device *dev);
extern struct phy_device *lan8742a_probe(eth_device *dev);

#if defined(CONFIG_C920) && \
	(defined(CONFIG_TB_RUN_DDR) || defined(CONFIG_TB_RUN_DDR1))
void *gmac3_mem_alloc(void)
{
	unsigned long mem_base = 0;
	mem_base = GMAC3_ALLOC_BASE + GMAC3_ALLOC_OFFSET * gmac3_alloc_index;
	gmac3_alloc_index++;
	return (void *)mem_base;
}
#endif

/* only for 1000m. */
#ifdef CONFIG_COMPILE_ASIC
static void mac_timing_fixup(unsigned long base, int txpaddly, int rxdly)
{
	writel(txpaddly, base + TX_PAD_DLY_REG);
	writel(rxdly, base + RX_PAD_DLY_REG);
}
#else
static void mac_timing_fixup(unsigned long base, int times)
{
	unsigned int val, rd_val = 0;
	int i;

	//printf("rgmii 1000m tx clk timing fixup\n");
	/* pll reset. */
	val = readl(base + PLL_PHASE_REG);
	val |= PLL_RESET;
	writel(val, base + PLL_PHASE_REG);
	udelay(1);
	val = readl(base + PLL_PHASE_REG);
	val &= ~PLL_RESET;
	writel(val, base + PLL_PHASE_REG);

	/* check pll lock status. */
	while (rd_val != PLL_LOCKED_STATUS)
		rd_val = readl(base + BUS_WIDTH_REG) & PLL_LOCKED_STATUS;

	/* phase modulation. inc or dec. one time almost is 30 ps. */
	for (i = 0; i < times; i++) {
		/* psen control enable, active is rise edge.  */
		//writel(PHASE_EN | PHASE_INC, base + PLL_PHASE_REG);
		//writel(PHASE_INC, base + PLL_PHASE_REG);

		/* low level. */
		val = readl(base + PLL_PHASE_REG);
		val &= ~PHASE_EN;
		val |= PHASE_INC;
		writel(val, base + PLL_PHASE_REG);
		/* high level. */
		val = readl(base + PLL_PHASE_REG);
		val |= PHASE_EN;
		writel(val, base + PLL_PHASE_REG);

		rd_val = 0;
		while (rd_val != PLL_PSDONE_STATUS)
			rd_val = readl(base + BUS_WIDTH_REG) &
				 PLL_PSDONE_STATUS;
	}
	//printf("fixup done\n");
}
#endif

#ifdef CONFIG_COMPILE_ASIC
void mac_find_delay_line(int id, int txpaddly, int rxdly)
{
	if (id == 0)
		mac_timing_fixup(GMAC0_SYSM_BASE, txpaddly, rxdly);
	else if (id == 1)
		mac_timing_fixup(GMAC1_SYSM_BASE, txpaddly, rxdly);
	else if (id == 2)
		mac_timing_fixup(GMAC2_SYSM_BASE, txpaddly, rxdly);
	else if (id == 3)
		mac_timing_fixup(GMAC3_SYSM_BASE, txpaddly, rxdly);
	else
		printf("not go to find delay line window\n");
}
#else
void mac_find_txdly_window(int id, int times)
{
	if (id == 0)
		mac_timing_fixup(GMAC0_SYSM_BASE, times);
	else if (id == 1)
		mac_timing_fixup(GMAC1_SYSM_BASE, times);
	else if (id == 2)
		mac_timing_fixup(GMAC2_SYSM_BASE, times);
	else if (id == 3)
		mac_timing_fixup(GMAC3_SYSM_BASE, times);
	else
		printf("not go to find txdly window\n");
}
#endif

int itcs_eth_set_mac_addr(eth_device *dev, mac_addr *addr)
{
	if (dev != NULL && addr != NULL) {
		dev->m_addr = addr;
		return 0;
	} else {
		return -1;
	}
}

mac_addr *itcs_eth_get_mac_addr(eth_device *dev)
{
	if (dev) {
		if (dev->m_addr)
			return dev->m_addr;
	}
	return NULL;
}

int itcs_eth_filter_mac_addr(eth_device *dev, mac_addr *addr, filter_type type,
			     bool enable)
{
	eth_lowlevel_filter_mac(dev, addr, type, enable);
	return 0;
}

int itcs_eth_phy_init(eth_device *dev)
{
	if (dev->config->interface == ETH_RMII) {
		dev->phy_dev = lan8742a_probe(dev);
	} else if (dev->config->interface == ETH_RGMII) {
		dev->phy_dev = marvell_probe(dev);
	} else {
		printf("phy init failed\n");
		return -1;
	}

	if (!dev->phy_dev)
		return -1;
	else
		return 0;
}

int itcs_eth_send(eth_device *dev, unsigned char *buf, unsigned int size,
		  unsigned char is_block)
{
	int ret;

	ret = eth_lowlevel_send(dev, buf, size);
	if (ret == -1)
		return -1;
	if (is_block == BLOCK) {
		while (1) {
			ret = itcs_eth_is_completed(dev, ETH_TX_CHECK);
			if (ret == 1)
				break;
		}
	}
	return 0;
}

int itcs_eth_recv(eth_device *dev, unsigned char *buf, unsigned int size,
		  unsigned char is_block)
{
	int ret;

	ret = eth_lowlevel_recv(dev, buf, size);
	if (ret == -1)
		return -1;
	if (is_block == BLOCK) {
		while (1) {
			ret = itcs_eth_is_completed(dev, ETH_RX_CHECK);
			if (ret == 1)
				break;
		}
	}
	return 0;
}

int itcs_eth_is_completed(eth_device *dev, eth_check check)
{
	return eth_lowlevel_is_completed(dev, check);
}

static int eth_irq_handler(int irq, void *args)
{
	return eth_lowlevel_irq_handler(irq, args);
}

static int register_irq(eth_id id, eth_device *dev)
{
	int ret = 0;
	if (id == ETH0) {
		ret = request_irq(C_GMAC0_WOL_IRQn, eth_irq_handler,
				  "gmac0_irq", dev);
		if (ret)
			return ret;
		ret = request_irq(C_GMAC0_Q_IRQn, eth_irq_handler,
				  "gmac0_q_irq", dev);
		if (ret)
			return ret;
		ret = request_irq(C_GMAC0_E_M_IRQn, eth_irq_handler,
				  "gmac0_e_m_irq", dev);
		if (ret)
			return ret;
	} else if (id == ETH1) {
		ret = request_irq(C_GMAC1_WOL_IRQn, eth_irq_handler,
				  "gmac1_irq", dev);
		if (ret)
			return ret;
		ret = request_irq(C_GMAC1_Q_IRQn, eth_irq_handler,
				  "gmac1_q_irq", dev);
		if (ret)
			return ret;
		ret = request_irq(C_GMAC1_E_M_IRQn, eth_irq_handler,
				  "gmac1_e_m_irq", dev);
		if (ret)
			return ret;
	} else if (id == ETH2) {
		ret = request_irq(C_GMAC2_WOL_IRQn, eth_irq_handler,
				  "gmac2_irq", dev);
		if (ret)
			return ret;
		ret = request_irq(C_GMAC2_Q_IRQn, eth_irq_handler,
				  "gmac2_q_irq", dev);
		if (ret)
			return ret;
		ret = request_irq(C_GMAC2_E_M_IRQn, eth_irq_handler,
				  "gmac2_e_m_irq", dev);
		if (ret)
			return ret;
	} else if (id == ETH3) {
		ret = request_irq(S_GMAC3_WOL_IRQn, eth_irq_handler,
				  "gmac3_irq", dev);
		if (ret)
			return ret;
		ret = request_irq(S_GMAC3_Q_IRQn, eth_irq_handler,
				  "gmac3_q_irq", dev);
		if (ret)
			return ret;
		ret = request_irq(S_GMAC3_E_M_IRQn, eth_irq_handler,
				  "gmac3_e_m_irq", dev);
		if (ret)
			return ret;
	} else {
		return -1;
	}
	return 0;
}

static int eth_module_init(eth_config *config)
{
	char *module_name = NULL;
	unsigned int val;

	switch (config->id) {
	case ETH0:
		module_name = "gmac0";
#ifdef CONFIG_COMPILE_ASIC
		itcs_module_set_pads_by_index("gmac0", 0);
#endif
		break;
	case ETH1:
		module_name = "gmac1";
#ifdef CONFIG_COMPILE_ASIC
		itcs_module_set_pads_by_index("gmac1", 0);
#endif
		break;
	case ETH2:
		module_name = "gmac2";
#ifdef CONFIG_COMPILE_ASIC
		itcs_module_set_pads_by_index("gmac2", 0);
#endif
		break;
	case ETH3:
		module_name = "gmac3";
#ifdef CONFIG_COMPILE_ASIC
		itcs_module_set_pads_by_index("gmac3", 0);
#endif
		break;
	}

	if (config->id < ETH3) {
#ifndef CONFIG_COMPILE_ASIC
		itcs_module_set_pads(CPU, FPGA_BIT_V_RGMII, module_name);
#endif
		itcs_module_set_clock(CPU, "gmac gtx", "dpll", GMAC_GTX_CLK,
				      false);
		itcs_module_set_clock(CPU, "gmac tsu", "dpll", GMAC_TSU_CLK,
				      false);
		itcs_module_set_clock(CPU, "gmac ref", "dpll", GMAC_REF_CLK,
				      false);
	} else if(config->id == ETH3) {
#ifndef CONFIG_COMPILE_ASIC
		itcs_module_set_pads(SAP, FPGA_BIT_V_RGMII, module_name);
#endif
		itcs_pll_set_clock(SAP, "spll", 500000000, false);
		itcs_module_set_clock(SAP, "gmac gtx", "spll", GMAC_GTX_CLK,
				      false);
		itcs_module_set_clock(SAP, "gmac tsu", "spll", GMAC_TSU_CLK,
				      false);
		itcs_module_set_clock(SAP, "gmac ref", "spll", GMAC_REF_CLK,
				      false);
	}

	if (config->interface == ETH_RMII) {
#ifdef CONFIG_COMPILE_ASIC
		if (config->id == ETH1) {
			printf("rmii 1, switch to 3.3v, please insert jump hat to 3.3v in 10 seconds.\n");
			val = readl(GMAC_PAD_VOLTAGE_BASE);
			val &= ~GMAC1_1V8_EN;
			writel(val, GMAC_PAD_VOLTAGE_BASE);
			udelay(10000000);
			printf("rmii 1 in danger! Don't insert jump to 3.3v hat!\n");
		}
#endif
		if (config->id == ETH0) {
			val = readl(GMAC0_SYSM_BASE + PHY_CTL_BASE);
			val |= PHY_CTL_USE_RMII;
			val |= EVEN_PREAMBLE_EN;
			if (config->ext_ref_clk)
				val &= ~PHY_CTL_USE_INT_REF_CLK;
			else
				val |= PHY_CTL_USE_INT_REF_CLK;

			writel(val, GMAC0_SYSM_BASE + PHY_CTL_BASE);
		} else if (config->id == ETH1) {
			val = readl(GMAC1_SYSM_BASE + PHY_CTL_BASE);
			val |= PHY_CTL_USE_RMII;
			val |= EVEN_PREAMBLE_EN;
			if (config->ext_ref_clk)
				val &= ~PHY_CTL_USE_INT_REF_CLK;
			else
				val |= PHY_CTL_USE_INT_REF_CLK;

			writel(val, GMAC1_SYSM_BASE + PHY_CTL_BASE);
		} else if (config->id == ETH2) {
			val = readl(GMAC2_SYSM_BASE + PHY_CTL_BASE);
			val |= PHY_CTL_USE_RMII;
			val |= EVEN_PREAMBLE_EN;
			if (config->ext_ref_clk)
				val &= ~PHY_CTL_USE_INT_REF_CLK;
			else
				val |= PHY_CTL_USE_INT_REF_CLK;

			writel(val, GMAC2_SYSM_BASE + PHY_CTL_BASE);
		} else {
			val = readl(GMAC3_SYSM_BASE + PHY_CTL_BASE);
			val |= PHY_CTL_USE_RMII;
			val |= EVEN_PREAMBLE_EN;
			if (config->ext_ref_clk)
				val &= ~PHY_CTL_USE_INT_REF_CLK;
			else
				val |= PHY_CTL_USE_INT_REF_CLK;

			writel(val, GMAC3_SYSM_BASE + PHY_CTL_BASE);
		}
	} else if (config->interface == ETH_RGMII) {
#ifdef CONFIG_COMPILE_ASIC
		if (config->id == ETH0) {
			printf("rgmii 0, switch to 1.8v\n");
			val = readl(GMAC_PAD_VOLTAGE_BASE);
			val |= GMAC0_1V8_EN;
			writel(val, GMAC_PAD_VOLTAGE_BASE);
		} else if (config->id == ETH2) {
			printf("rgmii 2, switch to 1.8v\n");
			val = readl(GMAC_PAD_VOLTAGE_BASE);
			val |= GMAC2_1V8_EN;
			writel(val, GMAC_PAD_VOLTAGE_BASE);
		} else if (config->id == ETH3) {
			printf("rgmii 3, switch to 1.8v\n");
			val = readl(GMAC_PAD_VOLTAGE_BASE);
			val |= GMAC3_1V8_EN;
			writel(val, GMAC_PAD_VOLTAGE_BASE);
		}
#endif
		if (config->id == ETH0) {
			val = readl(GMAC0_SYSM_BASE + PHY_CTL_BASE);
			val |= EVEN_PREAMBLE_EN;
			writel(val, GMAC0_SYSM_BASE + PHY_CTL_BASE);
		} else if (config->id == ETH1) {
			val = readl(GMAC1_SYSM_BASE + PHY_CTL_BASE);
			val |= EVEN_PREAMBLE_EN;
			writel(val, GMAC1_SYSM_BASE + PHY_CTL_BASE);
		} else if (config->id == ETH2) {
			val = readl(GMAC2_SYSM_BASE + PHY_CTL_BASE);
			val |= EVEN_PREAMBLE_EN;
			writel(val, GMAC2_SYSM_BASE + PHY_CTL_BASE);
		} else {
			val = readl(GMAC3_SYSM_BASE + PHY_CTL_BASE);
			val |= EVEN_PREAMBLE_EN;
			writel(val, GMAC3_SYSM_BASE + PHY_CTL_BASE);
		}
	}
	if (config->id != ETH3)
		itcs_module_enable(CPU, module_name);
	else
		itcs_module_enable(SAP, module_name);
	return 0;
}

eth_device *itcs_eth_init(eth_config *config)
{
	eth_device *dev;
	int ret;

	if (config->id != ETH0 && config->id != ETH1 && config->id != ETH2 &&
	    config->id != ETH3)
		return NULL;

	eth_module_init(config);

#if defined(CONFIG_C920) && \
	(defined(CONFIG_TB_RUN_DDR) || defined(CONFIG_TB_RUN_DDR1))
	if (config->id == ETH3) {
		dev = (eth_device *)gmac3_mem_alloc();
		is_gmac3 = 1;
	} else {
		dev = (eth_device *)malloc(sizeof(eth_device));
	}
#else
	dev = (eth_device *)malloc(sizeof(eth_device));
#endif
	if (dev == NULL) {
		printf("eth device alloc failed!\n");
		return NULL;
	}
	memset(dev, 0x0, sizeof(eth_device));
	dev->config = config;
	ret = eth_lowlevel_init(dev);
	if (ret == -1) {
		printf("eth lowlevel init failed!\n");
		itcs_eth_exit(dev);
		return NULL;
	}

	if (register_irq(config->id, dev)) {
		itcs_eth_exit(dev);
		return NULL;
	}

	eth_lowlevel_enable(dev);

#if defined(CONFIG_COMPILE_FPGA) || defined(CONFIG_ASIC_TEST_ON_FPGA)
	if (config->speed == ETH_SPEED_1000M) {
		if (config->mode != ETH_MODE_LOCAL_LOOPBACK) {
			if (config->id == 0)
				mac_timing_fixup(GMAC0_SYSM_BASE,
						 GMAC0_PHASE_MODULATION_TIMES);
			else if (config->id == 1)
				mac_timing_fixup(GMAC1_SYSM_BASE,
						 GMAC1_PHASE_MODULATION_TIMES);
			else if (config->id == 2)
				mac_timing_fixup(GMAC2_SYSM_BASE,
						 GMAC2_PHASE_MODULATION_TIMES);
			else if (config->id == 3)
				mac_timing_fixup(GMAC3_SYSM_BASE,
						 GMAC3_PHASE_MODULATION_TIMES);
			else
				printf("no phase modulation for 1000m\n");
		}
	}
#endif
	printf("eth%d inited, use %s\n", config->id,
	       config->interface == ETH_RMII ? "rmii" : "rgmii");
	return dev;
}

void itcs_eth_exit(eth_device *dev)
{
	eth_lowlevel_free(dev);
	if (dev->phy_dev) {
		free(dev->phy_dev);
		dev->phy_dev = NULL;
	}
#if defined(CONFIG_C920) && \
	(defined(CONFIG_TB_RUN_DDR) || defined(CONFIG_TB_RUN_DDR1))
	if (dev->config->id == ETH3) {
		is_gmac3 = 0;
		gmac3_alloc_index = 0;
	}
#endif
}

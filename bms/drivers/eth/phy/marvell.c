// SPDX-License-Identifier: GPL-2.0+
/*
 * drivers/net/phy/marvell.c
 *
 * Driver for Marvell PHYs
 *
 * Author: Andy Fleming
 *
 * Copyright (c) 2004 Freescale Semiconductor, Inc.
 *
 * Copyright (c) 2013 Michael Stapelberg <michael@stapelberg.de>
 */
#include <common.h>
#include <asm/io.h>
#include <malloc.h>
#include <pads.h>
#include <eth.h>
#include <phy.h>
#include "../eth_lowlevel.h"

#if DEBUG_ETH
#define net_dev_err(...) printf(__VA_ARGS__)
#else
#define net_dev_err(...)
#endif

#define BIT(nr) (1 << nr)

#define GENMASK(h, l)                                                \
	(((~(unsigned long)(0)) - ((unsigned long)(1) << (l)) + 1) & \
	 (~(unsigned long)(0) >> (BITS_PER_LONG - 1 - (h))))

#define __bf_shf(x) (__builtin_ffsll(x) - 1)
#define FIELD_PREP(_mask, _val) \
	({ ((typeof(_mask))(_val) << __bf_shf(_mask)) & (_mask); })

#define MARVELL_PHY_ID_88E1116R 0x01410e40
#define YT8521SH_ID 0x11a
#define MARVELL_PHY1_ADDR_88E1116R 0x7
#define MARVELL_PHY2_ADDR_88E1116R 0x5
#define MARVELL_PHY3_ADDR_88E1116R 0x4

#define MII_MARVELL_PHY_PAGE 22
#define MII_MARVELL_COPPER_PAGE 0x00
#define MII_MARVELL_FIBER_PAGE 0x01
#define MII_MARVELL_MSCR_PAGE 0x02
#define MII_MARVELL_LED_PAGE 0x03
#define MII_MARVELL_VCT5_PAGE 0x05
#define MII_MARVELL_MISC_TEST_PAGE 0x06
#define MII_MARVELL_VCT7_PAGE 0x07
#define MII_MARVELL_WOL_PAGE 0x11
#define MII_MARVELL_MODE_PAGE 0x12

#define MII_M1011_PHY_SCR 0x10
#define MII_M1011_PHY_SCR_DOWNSHIFT_EN BIT(11)
#define MII_M1011_PHY_SCR_DOWNSHIFT_MASK GENMASK(14, 12)
#define MII_M1011_PHY_SCR_DOWNSHIFT_MAX 8
#define MII_M1011_PHY_SCR_MDI (0x0 << 5)
#define MII_M1011_PHY_SCR_MDI_X (0x1 << 5)
#define MII_M1011_PHY_SCR_AUTO_CROSS (0x3 << 5)

#define MII_88E1121_PHY_MSCR_REG 21
#define MII_88E1121_PHY_MSCR_RX_DELAY BIT(5)
#define MII_88E1121_PHY_MSCR_TX_DELAY BIT(4)
#define MII_88E1121_PHY_MSCR_DELAY_MASK (BIT(5) | BIT(4))

#define MII_PHY_LED_CTRL 16

#define IEEE_STAT_AUTONEGOTIATE_COMPLETE 0x0020
#define IEEE_COPPER_SPECIFIC_STATUS_REG_2 19
#define IEEE_AUTONEG_ERROR_MASK 0x8000
#define IEEE_SPECIFIC_STATUS_REG 17
#define SPEED_DUPLEX_RESLOVED 0X800
#define COPPER_LINK_UP 0X400
#define GLOBAL_COPPER_LINK_UP 0x8

/* cpad_041 or cpad_057 as hardware reset pin. */
#define GMAC0_HW_RESET_PIN 41
#define GMAC1_HW_RESET_PIN 57
#define GMAC2_HW_RESET_PIN 111
#define GMAC3_HW_RESET_PIN 30

extern volatile int enable_mdio_test;
extern volatile int is_inter_connect;

extern int mac_set_tx_clk(eth_device *dev, struct phy_device *phydev);

static int phy_read(struct phy_device *phydev, int reg)
{
	return mdio_read(phydev, reg);
}

static int phy_write(struct phy_device *phydev, int reg, unsigned short val)
{
	return mdio_write(phydev, reg, val);
}

#ifndef CONFIG_COMPILE_ASIC
static int marvell_set_page(struct phy_device *phydev, int page)
{
	return phy_write(phydev, MII_MARVELL_PHY_PAGE, page);
}

static int marvell_set_polarity(struct phy_device *phydev, int polarity)
{
	u16 val;

	switch (polarity) {
	case ETH_TP_MDI:
		val = MII_M1011_PHY_SCR_MDI;
		break;
	case ETH_TP_MDI_X:
		val = MII_M1011_PHY_SCR_MDI_X;
		break;
	case ETH_TP_MDI_AUTO:
	case ETH_TP_MDI_INVALID:
	default:
		val = MII_M1011_PHY_SCR_AUTO_CROSS;
		break;
	}

	return phy_modify(phydev, MII_M1011_PHY_SCR,
			  MII_M1011_PHY_SCR_AUTO_CROSS, val);
}

static int m88e1121_config_aneg_rgmii_delays(struct phy_device *phydev)
{
	int mscr;
	int err;

	err = marvell_set_page(phydev, MII_MARVELL_MSCR_PAGE);
	if (err < 0)
		return err;

	if (phydev->interface == PHY_INTERFACE_MODE_RGMII_ID)
		mscr = MII_88E1121_PHY_MSCR_RX_DELAY |
		       MII_88E1121_PHY_MSCR_TX_DELAY;
	else if (phydev->interface == PHY_INTERFACE_MODE_RGMII_RXID)
		mscr = MII_88E1121_PHY_MSCR_RX_DELAY;
	else if (phydev->interface == PHY_INTERFACE_MODE_RGMII_TXID)
		mscr = MII_88E1121_PHY_MSCR_TX_DELAY;
	else
		mscr = 0;

	err = phy_modify_changed(phydev, MII_88E1121_PHY_MSCR_REG,
				 MII_88E1121_PHY_MSCR_DELAY_MASK, mscr);
	if (err < 0)
		return err;

	err = marvell_set_page(phydev, MII_MARVELL_COPPER_PAGE);
	if (err < 0)
		return err;

	return err;
}

static int genphy_setup_forced(struct phy_device *phydev)
{
	u16 ctl = 0;
	unsigned int val;

	val = phy_read(phydev, MII_BMCR);
	val &= ~BMCR_ANENABLE;
	phy_write(phydev, MII_BMCR, val);

	if (SPEED_1000 == phydev->speed)
		ctl |= BMCR_SPEED1000;
	else if (SPEED_100 == phydev->speed)
		ctl |= BMCR_SPEED100;

	if (DUPLEX_FULL == phydev->duplex)
		ctl |= BMCR_FULLDPLX;

	return phy_modify(phydev, MII_BMCR,
			  ~(BMCR_LOOPBACK | BMCR_ISOLATE | BMCR_PDOWN), ctl);
}
#endif

#ifndef CONFIG_COMPILE_ASIC
static int enable_loopback(struct phy_device *phydev)
{
	unsigned int val;

	/* open loopback. */
	val = phy_read(phydev, MII_BMCR);
	val |= BMCR_LOOPBACK;
	phy_write(phydev, MII_BMCR, val);
	return 0;
}

static int setting_phy(struct phy_device *phydev)
{
	int ret = 0;

	if (phydev->autoneg == AUTONEG_DISABLE)
		ret = genphy_setup_forced(phydev);

	return ret;
}

static int m88e1011_set_downshift(struct phy_device *phydev, u8 cnt)
{
	int val, err;

	if (cnt > MII_M1011_PHY_SCR_DOWNSHIFT_MAX)
		return -1;

	if (!cnt) {
		err = phy_write(phydev, MII_M1011_PHY_SCR,
				MII_M1011_PHY_SCR_DOWNSHIFT_EN);
	} else {
		val = MII_M1011_PHY_SCR_DOWNSHIFT_EN;
		val |= FIELD_PREP(MII_M1011_PHY_SCR_DOWNSHIFT_MASK, cnt - 1);
		err = phy_modify(phydev, MII_M1011_PHY_SCR,
				 MII_M1011_PHY_SCR_DOWNSHIFT_EN |
					 MII_M1011_PHY_SCR_DOWNSHIFT_MASK,
				 val);
	}
	if (err < 0)
		return err;

	return genphy_soft_reset(phydev);
}
#endif

static inline bool phy_interface_is_rgmii(struct phy_device *phydev)
{
	phy_interface_t mode = phydev->interface;
	return mode >= PHY_INTERFACE_MODE_RGMII &&
	       mode <= PHY_INTERFACE_MODE_RGMII_TXID;
}

#ifndef CONFIG_COMPILE_ASIC
static int m88e1116r_config_init(struct phy_device *phydev)
{
	int err;

	err = genphy_soft_reset(phydev);
	if (err < 0)
		return err;

	udelay(500 * 1000);

	err = marvell_set_page(phydev, MII_MARVELL_COPPER_PAGE);
	if (err < 0)
		return err;
	err = marvell_set_polarity(phydev, phydev->mdix_ctrl);
	if (err < 0)
		return err;
	err = m88e1011_set_downshift(phydev, 8);
	if (err < 0)
		return err;
	if (phy_interface_is_rgmii(phydev)) {
		err = m88e1121_config_aneg_rgmii_delays(phydev);
		if (err < 0)
			return err;
	}
	err = setting_phy(phydev);
	if (err < 0)
		return err;

	err = genphy_soft_reset(phydev);
	if (err < 0)
		return err;

	return 0;
}
#endif

#if DEBUG_ETH
static void dump_phy(struct phy_device *phydev)
{
	net_dev_err("phy bmcr: 0x%x\n", phy_read(phydev, MII_BMCR));
	net_dev_err("phy bmsr: 0x%x\n", phy_read(phydev, MII_BMSR));
	net_dev_err("phy id 1: 0x%x\n", phy_read(phydev, MII_PHYSID1));
	net_dev_err("phy id 2: 0x%x\n", phy_read(phydev, MII_PHYSID2));
	net_dev_err("phy advertise: 0x%x\n", phy_read(phydev, MII_ADVERTISE));
	net_dev_err("phy page: 0x%x\n", phy_read(phydev, MII_MARVELL_PHY_PAGE));

	phy_write(phydev, MII_MARVELL_PHY_PAGE, MII_MARVELL_LED_PAGE);
	net_dev_err("after set, phy page: 0x%x\n",
		    phy_read(phydev, MII_MARVELL_PHY_PAGE));
	net_dev_err("phy led ctrl: 0x%x\n", phy_read(phydev, MII_PHY_LED_CTRL));
	phy_write(phydev, MII_MARVELL_PHY_PAGE, MII_MARVELL_COPPER_PAGE);
}
#endif

#ifndef CONFIG_COMPILE_ASIC
static int marvell_get_phy_speed_duplex(struct phy_device *phydev)
{
	unsigned int status, tmp;
	unsigned short partner_caps;
	int timeouts = 0;
	int expected_time = 6000000;
	int interval = 500000;
	int hw_delay = 3000 * 1000;

	if (phydev->autoneg == AUTONEG_ENABLE) {
		printf("waiting for phy completing auto negotiation...\n");
		status = phy_read(phydev, MII_BMSR);
		while (!(status & IEEE_STAT_AUTONEGOTIATE_COMPLETE) &&
		       timeouts <= expected_time) {
			udelay(interval);
			timeouts += interval;
			tmp = phy_read(phydev,
				       IEEE_COPPER_SPECIFIC_STATUS_REG_2);
			if (tmp & IEEE_AUTONEG_ERROR_MASK)
				net_dev_err("Auto negotiation error \r\n");

			status = phy_read(phydev, MII_BMSR);
		}
		if (timeouts > expected_time)
			printf("phy auto negotiation timeout!\n");

		printf("phy auto negotiation completed.\n");
		partner_caps = phy_read(phydev, IEEE_SPECIFIC_STATUS_REG);
		if ((partner_caps >> 14 & 3) == 2)
			phydev->speed = SPEED_1000;
		else if ((partner_caps >> 14 & 3) == 1)
			phydev->speed = SPEED_100;
		else if ((partner_caps >> 14 & 3) == 0)
			phydev->speed = SPEED_10;
		else
			return 0;

		if ((partner_caps >> 13 & 1) == 1)
			phydev->duplex = DUPLEX_FULL;
		else if ((partner_caps >> 13 & 1) == 0)
			phydev->duplex = DUPLEX_HALF;
		else
			return 0;
	} else if (phydev->autoneg == AUTONEG_DISABLE) {
		while (timeouts <= expected_time) {
			udelay(interval);
			timeouts += interval;
			partner_caps =
				phy_read(phydev, IEEE_SPECIFIC_STATUS_REG);
			if (partner_caps & COPPER_LINK_UP &&
			    partner_caps & GLOBAL_COPPER_LINK_UP) {
				/* we need to read bmsr twice referred from linux kernel. */
				status = phy_read(phydev, MII_BMSR);
				if (status & BMSR_LSTATUS)
					break;
				status = phy_read(phydev, MII_BMSR);
				if (status & BMSR_LSTATUS)
					break;
			}
		}
		if (timeouts < hw_delay) {
			udelay(hw_delay);
			timeouts += hw_delay;
		}

		if (timeouts > expected_time)
			printf("phy waiting for manual config completing timeout!\n");

		if (genphy_read_status_fixed(phydev) < 0)
			return 0;
	}
	return 1;
}
#endif

/*
 * macb_set_tx_clk() - Set a clock to a new frequency, only for rgmii
 */
static int macb_set_tx_clk(eth_device *dev, struct phy_device *phydev)
{
	/* In case of MII the PHY is the clock master */
	if (phydev->interface == PHY_INTERFACE_MODE_MII)
		return -1;

	return phy_set_tx_clk(dev, phydev);
}

#if defined(CONFIG_COMPILE_FPGA) || defined(CONFIG_COMPILE_ASIC)
static void phy_hw_reset(domain_t domain, unsigned int pin)
{
	itcs_pads_set_mode(domain, PADSRANGE(pin, pin), PADS_MODE_OUT, 1);
	udelay(100000);
	itcs_pads_set_value(domain, PADSRANGE(pin, pin), 0);
	udelay(150000);
	itcs_pads_set_value(domain, PADSRANGE(pin, pin), 1);
	udelay(100000);
}
#endif

#if defined(CONFIG_COMPILE_RTL) || defined(CONFIG_COMPILE_ASIC)
static int mdio_read_write_test(struct phy_device *phydev)
{
	unsigned int val;

	/* open loopback. */
	val = phy_read(phydev, MII_BMCR);
	printf("bmcr read: 0x%x\n", val);
	val |= BMCR_LOOPBACK;
	printf("bmcr write: 0x%x\n", val);
	phy_write(phydev, MII_BMCR, val);
#ifdef CONFIG_COMPILE_ASIC
	if (val == phy_read(phydev, MII_BMCR))
		return 0;
	else
		return -1;
#endif
}
#endif

struct phy_device *marvell_probe(eth_device *dev)
{
	struct phy_device *phydev;
#ifdef CONFIG_COMPILE_ASIC
	char name[8] = { 0 };
#else
	unsigned int phy_id;
#endif
	int ret;

	phydev = malloc(sizeof(*phydev));
	if (!phydev)
		return NULL;
	memset(phydev, 0, sizeof(*phydev));

	phydev->phy_id = MARVELL_PHY_ID_88E1116R;
	if (dev->config->id == ETH0 || dev->config->id == ETH2)
		phydev->phy_addr = MARVELL_PHY1_ADDR_88E1116R;
	else if (dev->config->id == ETH1 || dev->config->id == ETH3)
		phydev->phy_addr = MARVELL_PHY2_ADDR_88E1116R;
	else
		phydev->phy_addr = MARVELL_PHY1_ADDR_88E1116R;

#ifdef CONFIG_COMPILE_ASIC
	phydev->autoneg = AUTONEG_ENABLE;
#else
	phydev->autoneg = dev->config->auto_nego_en;
#endif
	/* enable crossover. */
	phydev->mdix_ctrl = ETH_TP_MDI_AUTO;
	/* tx clk not internally delay for 1000M transmit. */
	phydev->interface =
		PHY_INTERFACE_MODE_RGMII_RXID; //PHY_INTERFACE_MODE_RGMII_ID
	if (phydev->autoneg == AUTONEG_DISABLE) {
		phydev->duplex = dev->config->duplex;
		switch (dev->config->speed) {
		case ETH_SPEED_10M:
			phydev->speed = SPEED_10;
			break;
		case ETH_SPEED_100M:
			phydev->speed = SPEED_100;
			break;
		case ETH_SPEED_1000M:
			phydev->speed = SPEED_1000;
			break;
		default:
			printf("unsupported net speed!\n");
			goto err;
		}
	}

	mdio_init(dev, phydev);

#if defined(CONFIG_COMPILE_FPGA) || defined(CONFIG_COMPILE_ASIC)
	if (dev->config->id == ETH0)
		phy_hw_reset(CPU, GMAC0_HW_RESET_PIN);
	else if (dev->config->id == ETH1)
		phy_hw_reset(CPU, GMAC1_HW_RESET_PIN);
	else if (dev->config->id == ETH2)
		phy_hw_reset(CPU, GMAC2_HW_RESET_PIN);
	else if (dev->config->id == ETH3)
		phy_hw_reset(SAP, GMAC3_HW_RESET_PIN);
#endif

#if DEBUG_ETH
	dump_phy(phydev);
#endif

#if defined(CONFIG_COMPILE_RTL)
	printf("phy address: 0x%x\n", phydev->phy_addr);
	mdio_read_write_test(phydev);
	return phydev;
#endif

#ifdef CONFIG_COMPILE_ASIC
	/* Auto-detect phy_addr */
	sprintf(name, "eth%d", dev->config->id);
	ret = macb_phy_find(phydev, name);
	if (ret)
		goto err;
	if (enable_mdio_test) {
		printf("phy address: 0x%x\n", phydev->phy_addr);
		if (mdio_read_write_test(phydev) < 0)
			goto err;
		return phydev;
	}
#else
	phy_id = (unsigned int)phy_read(phydev, MII_PHYSID1) << 16;
	phy_id |= phy_read(phydev, MII_PHYSID2);
	if (phy_id != phydev->phy_id) {
		printf("unsupported phy! phy id: 0x%x\n", phy_id);
		goto err;
	}
#endif

#ifdef CONFIG_COMPILE_ASIC
	if (dev->config->id == ETH1 && phydev->phy_id == YT8521SH_ID) {
		/* power on strap. */
		itcs_pads_set_mode(CPU, PADSRANGE(51, 56), PADS_MODE_OUT, 0);
		itcs_pads_set_value(CPU, PADSRANGE(51, 56), 0);

		phy_hw_reset(CPU, GMAC1_HW_RESET_PIN);

		/* restore pad func. */
		itcs_module_set_pads_by_index("gmac1", 0);

		/* Need to read phy id again for unknown reason. */
		ret = macb_phy_find(phydev, name);
		if (ret)
			goto err;
	}
	if (dev->config->phy_loopback)
		phydev->find_window = 1;
	phy_generic_handle(phydev);

	if (is_inter_connect) {
		phydev->duplex = dev->config->duplex;
		switch (dev->config->speed) {
		case ETH_SPEED_10M:
			phydev->speed = SPEED_10;
			break;
		case ETH_SPEED_100M:
			phydev->speed = SPEED_100;
			break;
		case ETH_SPEED_1000M:
			phydev->speed = SPEED_1000;
			break;
		default:
			printf("unsupported net speed!\n");
			goto err;
		}

		phy_set_speed(phydev);
		/* For rtl8211f, 1000M waiting for link up. */
		udelay(5000000);
	}

	/* back to set mac speed and duplex. */
	ret = macb_set_tx_clk(dev, phydev);
	if (ret != 0) {
		printf("back to set mac failed!\n");
		goto err;
	}
#else
	m88e1116r_config_init(phydev);

	if (dev->config->phy_loopback)
		enable_loopback(phydev);

	if (phydev->autoneg == AUTONEG_ENABLE) {
		ret = marvell_get_phy_speed_duplex(phydev);
		if (ret == 0) {
			printf("phy get speed failed!\n");
			goto err;
		}
		/* back to set mac speed and duplex. */
		ret = macb_set_tx_clk(dev, phydev);
		if (ret != 0) {
			printf("back to set mac failed!\n");
			goto err;
		}
	} else {
		ret = marvell_get_phy_speed_duplex(phydev);
		if (ret == 0) {
			printf("phy get speed failed!\n");
			goto err;
		}
	}
#endif

#ifndef CONFIG_COMPILE_ASIC
	printf("eth%d phy speed: %dMbit\n", dev->config->id, phydev->speed);
	printf("eth%d phy duplex: %s\n", dev->config->id,
	       phydev->duplex == DUPLEX_FULL ? "full" : "half");
#endif
	return phydev;
err:
	free(phydev);
	return NULL;
}

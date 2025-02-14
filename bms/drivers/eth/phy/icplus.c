// SPDX-License-Identifier: GPL-2.0+
/*
 * Driver for ICPlus PHYs
 *
 * Copyright (c) 2007 Freescale Semiconductor, Inc.
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

#define IP101GR_PHY_ID 0x02430c54
#define ICPLUS_PHY_ADDR_IP101GR 0x1

#define IP101A_G_AUTO_MDIX_DIS BIT(11)
#define IP101A_G_FORCE_MDIX BIT(3)

#define IP101G_PAGE1 1
#define IP101G_PAGE8 8
#define IP101G_DEFAULT_PAGE 16
#define IP10XX_SPEC_CTRL_STATUS 16 /* Spec. Control Register */
#define IP101A_G_PHY_SPEC_CTRL 30
#define IP101G_PAGE_CONTROL 0x14

#define IP101G_P1_CNT_CTRL 17
#define CNT_CTRL_RX_EN BIT(13)
#define IP101G_P8_CNT_CTRL 17
#define CNT_CTRL_RDCLR_EN BIT(15)
#define IP101G_CNT_REG 18

/* cpad_041 or cpad_057 as hardware reset pin. */
#define GMAC0_HW_RESET_PIN 41
#define GMAC1_HW_RESET_PIN 57
#define GMAC2_HW_RESET_PIN 111
#define GMAC3_HW_RESET_PIN 30

extern int mac_set_tx_clk(eth_device *dev, struct phy_device *phydev);

static int phy_read(struct phy_device *phydev, int reg)
{
	return mdio_read(phydev, reg);
}

static int phy_write(struct phy_device *phydev, int reg, unsigned short val)
{
	return mdio_write(phydev, reg, val);
}

static int phy_set_page(struct phy_device *phydev, int page)
{
	return phy_write(phydev, IP101G_PAGE_CONTROL, page);
}

static int genphy_setup_forced(struct phy_device *phydev)
{
	u16 ctl = 0;
	unsigned int val;

	val = phy_read(phydev, MII_BMCR);
	val &= ~BMCR_ANENABLE;
	phy_write(phydev, MII_BMCR, val);

	if (SPEED_100 == phydev->speed)
		ctl |= BMCR_SPEED100;

	if (DUPLEX_FULL == phydev->duplex)
		ctl |= BMCR_FULLDPLX;

	return phy_modify(phydev, MII_BMCR,
			  ~(BMCR_LOOPBACK | BMCR_ISOLATE | BMCR_PDOWN), ctl);
}

static int ip101a_g_config_mdix(struct phy_device *phydev)
{
	unsigned short ctrl = 0, ctrl2 = 0;
	int oldpage;
	int ret = 0;

	switch (phydev->mdix_ctrl) {
	case ETH_TP_MDI:
		ctrl = IP101A_G_AUTO_MDIX_DIS;
		break;
	case ETH_TP_MDI_X:
		ctrl = IP101A_G_AUTO_MDIX_DIS;
		ctrl2 = IP101A_G_FORCE_MDIX;
		break;
	case ETH_TP_MDI_AUTO:
		break;
	default:
		return -1;
	}

	oldpage = phy_read(phydev, IP101G_PAGE_CONTROL);
	if (oldpage < 0)
		goto out;

	ret = phy_set_page(phydev, IP101G_DEFAULT_PAGE);
	if (ret < 0)
		goto out;

	ret = phy_modify(phydev, IP10XX_SPEC_CTRL_STATUS,
			 IP101A_G_AUTO_MDIX_DIS, ctrl);
	if (ret < 0)
		goto out;

	ret = phy_modify(phydev, IP101A_G_PHY_SPEC_CTRL, IP101A_G_FORCE_MDIX,
			 ctrl2);

out:
	return phy_set_page(phydev, oldpage);
}

static int ip101gr_config_init(struct phy_device *phydev)
{
	int err;

	err = genphy_soft_reset(phydev);
	if (err < 0)
		return err;

	udelay(500 * 1000);

	/* Enable the PHY counters */
	err = phy_set_page(phydev, IP101G_PAGE1);
	if (err < 0)
		return err;

	err = phy_modify(phydev, IP101G_P1_CNT_CTRL, CNT_CTRL_RX_EN,
			 CNT_CTRL_RX_EN);
	if (err < 0)
		return err;

	err = phy_set_page(phydev, IP101G_PAGE8);
	if (err < 0)
		return err;
	/* Clear error counters on read */
	err = phy_modify(phydev, IP101G_P8_CNT_CTRL, CNT_CTRL_RDCLR_EN,
			 CNT_CTRL_RDCLR_EN);
	if (err < 0)
		return err;

	err = ip101a_g_config_mdix(phydev);
	if (err < 0)
		return err;

	if (phydev->autoneg == AUTONEG_DISABLE) {
		err = genphy_setup_forced(phydev);
		if (err < 0)
			return err;
	}

	return 0;
}

#if DEBUG_ETH
static void dump_phy(struct phy_device *phydev)
{
	net_dev_err("phy bmcr: 0x%x\n", phy_read(phydev, MII_BMCR));
	net_dev_err("phy bmsr: 0x%x\n", phy_read(phydev, MII_BMSR));
	net_dev_err("phy id 1: 0x%x\n", phy_read(phydev, MII_PHYSID1));
	net_dev_err("phy id 2: 0x%x\n", phy_read(phydev, MII_PHYSID2));
	net_dev_err("phy advertise: 0x%x\n", phy_read(phydev, MII_ADVERTISE));
}
#endif

static void phy_hw_reset(domain_t domain, unsigned int pin)
{
	itcs_pads_set_mode(domain, PADSRANGE(pin, pin), PADS_MODE_OUT, 1);
	itcs_pads_set_value(domain, PADSRANGE(pin, pin), 0);
	/* ip101gr hardware reset needs at least 10ms. */
	udelay(15000);
	itcs_pads_set_value(domain, PADSRANGE(pin, pin), 1);
}

struct phy_device *icplus_probe(eth_device *dev)
{
	struct phy_device *phydev;
	unsigned int phy_id;
	int ret;

	phydev = malloc(sizeof(*phydev));
	if (!phydev)
		return NULL;
	memset(phydev, 0, sizeof(*phydev));

	phydev->phy_id = IP101GR_PHY_ID;
	phydev->phy_addr = ICPLUS_PHY_ADDR_IP101GR;

	phydev->autoneg = dev->config->auto_nego_en;
	/* enable crossover. */
	phydev->mdix_ctrl = ETH_TP_MDI_AUTO;
	phydev->interface = PHY_INTERFACE_MODE_RMII;
	if (phydev->autoneg == AUTONEG_DISABLE) {
		phydev->duplex = dev->config->duplex;
		switch (dev->config->speed) {
		case ETH_SPEED_10M:
			phydev->speed = SPEED_10;
			break;
		case ETH_SPEED_100M:
			phydev->speed = SPEED_100;
			break;
		default:
			printf("unsupported net speed!\n");
			goto err;
		}
	}

	mdio_init(dev, phydev);

	if (dev->config->id == ETH0)
		phy_hw_reset(CPU, GMAC0_HW_RESET_PIN);
	else if (dev->config->id == ETH1)
		phy_hw_reset(CPU, GMAC1_HW_RESET_PIN);
	else if (dev->config->id == ETH2)
		phy_hw_reset(CPU, GMAC2_HW_RESET_PIN);
	else if (dev->config->id == ETH3)
		phy_hw_reset(SAP, GMAC3_HW_RESET_PIN);

		//udelay(3000 * 1000);

#if DEBUG_ETH
	dump_phy(phydev);
#endif

	ret = ip101gr_config_init(phydev);
	if (ret < 0)
		goto err;

	phy_id = (unsigned int)phy_read(phydev, MII_PHYSID1) << 16;
	phy_id |= phy_read(phydev, MII_PHYSID2);
	if (phy_id != phydev->phy_id) {
		printf("unsupported phy! phy id: 0x%x\n", phy_id);
		goto err;
	}

	if (phydev->autoneg == AUTONEG_ENABLE) {
		ret = get_phy_speed_duplex(phydev);
		if (ret == 0) {
			printf("phy get speed failed!\n");
			goto err;
		}
		/* back to set mac speed and duplex. */
		ret = mac_set_tx_clk(dev, phydev);
		if (ret != 0) {
			printf("back to set mac failed!\n");
			goto err;
		}
	} else {
		ret = get_phy_speed_duplex(phydev);
		if (ret == 0) {
			printf("phy get speed failed!\n");
			goto err;
		}
	}

	printf("eth%d phy speed: %dMbit\n", dev->config->id, phydev->speed);
	printf("eth%d phy duplex: %s\n", dev->config->id,
	       phydev->duplex == DUPLEX_FULL ? "full" : "half");
	return phydev;
err:
	free(phydev);
	return NULL;
}

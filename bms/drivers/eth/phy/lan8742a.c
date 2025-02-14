
#include <common.h>
#include <asm/io.h>
#include <malloc.h>
#include <pads.h>
#include <eth.h>
#include <phy.h>
#include <linux/mii.h>
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

#define LAN8742A_PHY_ID 0x7c131
#define LAN8742A_PHY0_ADDR 0x0
#define LAN8742A_PHY1_ADDR 0x1

#define WAKEUP_CTRL_REG 32784
#define WAKEUP_PIN_SET (1 << 13)
#define RX_ADDRA 32865
#define RX_ADDRB 32866
#define RX_ADDRC 32867

/* cpad_041 or cpad_057 as hardware reset pin. */
#define GMAC0_HW_RESET_PIN 41
#define GMAC1_HW_RESET_PIN 57
#define GMAC2_HW_RESET_PIN 111
#define GMAC3_HW_RESET_PIN 30

extern volatile int enable_mdio_test;
extern int mac_set_tx_clk(eth_device *dev, struct phy_device *phydev);

static int phy_read(struct phy_device *phydev, int reg)
{
	return mdio_read(phydev, reg);
}

static int phy_write(struct phy_device *phydev, int reg, unsigned short val)
{
	return mdio_write(phydev, reg, val);
}

static int phy_read_mmd(struct phy_device *phydev, int devaddr, int reg)
{
	phy_write(phydev, MII_MMD_CTRL, devaddr | MII_MMD_CTRL_ADDR);
	phy_write(phydev, MII_MMD_DATA, reg);

	phy_write(phydev, MII_MMD_CTRL, devaddr | MII_MMD_CTRL_NOINCR);
	return phy_read(phydev, MII_MMD_DATA);
}

static int phy_write_mmd(struct phy_device *phydev, int devaddr, int reg,
			 unsigned short val)
{
	phy_write(phydev, MII_MMD_CTRL, devaddr | MII_MMD_CTRL_ADDR);
	phy_write(phydev, MII_MMD_DATA, reg);

	phy_write(phydev, MII_MMD_CTRL, devaddr | MII_MMD_CTRL_NOINCR);
	return phy_write(phydev, MII_MMD_DATA, val);
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

static int lan8742a_config_init(struct phy_device *phydev)
{
	int err;

	err = genphy_soft_reset(phydev);
	if (err < 0)
		return err;

	udelay(500 * 1000);

	if (phydev->autoneg == AUTONEG_DISABLE) {
		err = genphy_setup_forced(phydev);
		if (err < 0)
			return err;
	}

	return 0;
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

struct phy_device *lan8742a_probe(eth_device *dev)
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

	phydev->phy_id = LAN8742A_PHY_ID;
	phydev->phy_addr = LAN8742A_PHY0_ADDR;

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
	ret = lan8742a_config_init(phydev);
	if (ret < 0)
		goto err;

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

	if (dev->config->phy_enable_wol) {
		/* set phy mac addr. */
		phy_write_mmd(phydev, MDIO_MMD_PCS, RX_ADDRA,
			      (dev->m_addr->mac[5] << 8) | dev->m_addr->mac[4]);
		phy_write_mmd(phydev, MDIO_MMD_PCS, RX_ADDRB,
			      (dev->m_addr->mac[3] << 8) | dev->m_addr->mac[2]);
		phy_write_mmd(phydev, MDIO_MMD_PCS, RX_ADDRC,
			      (dev->m_addr->mac[1] << 8) | dev->m_addr->mac[0]);

		/* set led1 pin as wol and enable magic packet. */
		phy_write_mmd(phydev, MDIO_MMD_PCS, WAKEUP_CTRL_REG,
			      WAKEUP_PIN_SET | (1 << 1));

		/* open wol int */
		phy_write(phydev, 30, 1 << 8);
		printf("phy wol wake ctrl reg: 0x%x\n", phy_read_mmd(phydev, MDIO_MMD_PCS, WAKEUP_CTRL_REG));
		//printf("---flag: 0x%x---\n", phy_read(phydev, 29));
		//while (1) {
		//	udelay(10);
		//	if (phy_read_mmd(phydev, MDIO_MMD_PCS, WAKEUP_CTRL_REG) == 0x2022) {
		//		udelay(200 * 1000);
		//		printf("---flag: 0x%x---\n", phy_read(phydev, 29));
		//		break;
		//	}
		//}
	}

	printf("eth%d phy speed: %dMbit\n", dev->config->id, phydev->speed);
	printf("eth%d phy duplex: %s\n", dev->config->id,
	       phydev->duplex == DUPLEX_FULL ? "full" : "half");
	return phydev;
err:
	free(phydev);
	return NULL;
}

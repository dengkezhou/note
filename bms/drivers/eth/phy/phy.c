
#include <common.h>
#include <asm/io.h>
#include <malloc.h>
#include <pads.h>
#include <eth.h>
#include <phy.h>
#include <linux/mii.h>
#include "../eth_lowlevel.h"

#define IEEE_STAT_AUTONEGOTIATE_COMPLETE 0x0020

static int phy_read(struct phy_device *phydev, int reg)
{
	return mdio_read(phydev, reg);
}

static int phy_write(struct phy_device *phydev, int reg, unsigned short val)
{
	return mdio_write(phydev, reg, val);
}

int phy_modify_changed(struct phy_device *phydev, int reg, u16 mask,
			      u16 set)
{
	int new, ret;

	ret = phy_read(phydev, reg);
	if (ret < 0)
		return ret;

	new = (ret & ~mask) | set;
	if (new == ret)
		return 0;

	ret = phy_write(phydev, reg, new);

	return ret < 0 ? ret : 1;
}

int phy_modify(struct phy_device *phydev, int reg, u16 mask, u16 set)
{
	int ret;
	ret = phy_modify_changed(phydev, reg, mask, set);
	return ret;
}

/*
 * mac_set_tx_clk() - Set a clock to a new frequency, only for rgmii
 */
int mac_set_tx_clk(eth_device *dev, struct phy_device *phydev)
{
	/* In case of MII the PHY is the clock master */
	if (phydev->interface == PHY_INTERFACE_MODE_MII)
		return -1;

	return phy_set_tx_clk(dev, phydev);
}

int macb_phy_find(struct phy_device *phydev, const char *name)
{
	int i;
	unsigned short phy_id1, phy_id2;
	int ret = 0;

	phy_id1 = phy_read(phydev, MII_PHYSID1);
	if (phy_id1 != 0xffff) {
		phydev->phy_id = (unsigned int)phy_id1 << 16;
		phy_id2 = phy_read(phydev, MII_PHYSID2);
		if (phy_id2 != 0xffff) {
			phydev->phy_id |= phy_id2;
			printf("No search, %s: PHY 0x%x present at %d\n", name,
			       phydev->phy_id, phydev->phy_addr);
			ret = 0;
			goto exit;
		}
	}
	/* Search for PHY... */
	for (i = 0; i < 32; i++) {
		phydev->phy_addr = i;
		phy_id1 = phy_read(phydev, MII_PHYSID1);
		if (phy_id1 != 0xffff) {
			phydev->phy_id = (unsigned int)phy_id1 << 16;
			phy_id2 = phy_read(phydev, MII_PHYSID2);
			if (phy_id2 != 0xffff) {
				phydev->phy_id |= phy_id2;
				printf("Search, %s: PHY 0x%x present at %d\n",
				       name, phydev->phy_id, i);
				ret = 0;
				goto exit;
			}
		}
	}
	/* PHY isn't up to snuff */
	printf("%s: PHY not found\n", name);
	return -1;
exit:
	return ret;
}

int genphy_read_status_fixed(struct phy_device *phydev)
{
	int bmcr = phy_read(phydev, MII_BMCR);

	if (bmcr < 0)
		return bmcr;

	if (bmcr & BMCR_FULLDPLX)
		phydev->duplex = DUPLEX_FULL;
	else
		phydev->duplex = DUPLEX_HALF;

	if (bmcr & BMCR_SPEED1000)
		phydev->speed = SPEED_1000;
	else if (bmcr & BMCR_SPEED100)
		phydev->speed = SPEED_100;
	else
		phydev->speed = SPEED_10;

	return 0;
}

int get_phy_speed_duplex(struct phy_device *phydev)
{
	unsigned int status;
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
			status = phy_read(phydev, MII_BMSR);
		}
		if (timeouts > expected_time)
			printf("phy auto negotiation timeout!\n");

		printf("phy auto negotiation completed.\n");
		if (genphy_read_status_fixed(phydev) < 0)
			return 0;
	} else if (phydev->autoneg == AUTONEG_DISABLE) {
		while (timeouts <= expected_time) {
			udelay(interval);
			timeouts += interval;

			/* we need to read bmsr twice referred from linux kernel. */
			status = phy_read(phydev, MII_BMSR);
			if (status & BMSR_LSTATUS)
				break;
			status = phy_read(phydev, MII_BMSR);
			if (status & BMSR_LSTATUS)
				break;
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

static int phy_poll_reset(struct phy_device *phydev)
{
	/* Poll until the reset bit clears (50ms per retry == 0.6 sec) */
	int val, timeouts = 0;

	while (timeouts <= 600000) {
		val = phy_read(phydev, MII_BMCR);
		if ((val & BMCR_RESET) == 0)
			break;

		udelay(50000);
		timeouts += 50000;
	}
	if (timeouts > 600000) {
		printf("poll external phy reset timeout!\n");
		return -1;
	}
	/* Some chips (smsc911x) may still need up to another 1ms after the
	 * BMCR_RESET bit is cleared before they are usable.
	 */
	udelay(1000);
	return 0;
}

int genphy_soft_reset(struct phy_device *phydev)
{
	u16 res = BMCR_RESET;
	int ret;

	if (phydev->autoneg == AUTONEG_ENABLE)
		res |= BMCR_ANRESTART;

	ret = phy_modify(phydev, MII_BMCR, BMCR_ISOLATE, res);
	if (ret < 0)
		return ret;

	/* Clause 22 states that setting bit BMCR_RESET sets control registers
	 * to their default value. Therefore the POWER DOWN bit is supposed to
	 * be cleared after soft reset.
	 */
	ret = phy_poll_reset(phydev);
	if (ret)
		return ret;

	return ret;
}

void phy_enable_loopback(struct phy_device *phydev, bool change_speed)
{
	unsigned int val;

	/* open loopback. */
	val = phy_read(phydev, MII_BMCR);
	val |= BMCR_LOOPBACK;
	val &= ~BMCR_ANENABLE;
	if (change_speed) {
		if (phydev->speed == SPEED_100) {
			val |= (1 << 13);
			val &= ~(1 << 6);
		} else if (phydev->speed == SPEED_10) {
			val &= ~(1 << 13);
			val &= ~(1 << 6);
		}
	}
	if (phydev->interface == PHY_INTERFACE_MODE_RGMII
	    || phydev->interface == PHY_INTERFACE_MODE_RGMII_ID
	    || phydev->interface == PHY_INTERFACE_MODE_RGMII_RXID
	    || phydev->interface == PHY_INTERFACE_MODE_RGMII_TXID) {
		if (phydev->duplex == DUPLEX_HALF) {
			val |= BMCR_FULLDPLX;
			phydev->duplex = DUPLEX_FULL;
		}
	}
	phy_write(phydev, MII_BMCR, val);
}

void phy_set_speed(struct phy_device *phydev)
{
	unsigned int val;

	val = phy_read(phydev, MII_BMCR);
	val &= ~BMCR_ANENABLE;

	if (phydev->speed == SPEED_1000) {
		val &= ~(1 << 13);
		val |= (1 << 6);
	} else if (phydev->speed == SPEED_100) {
		val |= (1 << 13);
		val &= ~(1 << 6);
	} else if (phydev->speed == SPEED_10) {
		val &= ~(1 << 13);
		val &= ~(1 << 6);
	}

	if (phydev->interface == PHY_INTERFACE_MODE_RGMII
	    || phydev->interface == PHY_INTERFACE_MODE_RGMII_ID
	    || phydev->interface == PHY_INTERFACE_MODE_RGMII_RXID
	    || phydev->interface == PHY_INTERFACE_MODE_RGMII_TXID) {
		val |= BMCR_FULLDPLX;
		phydev->duplex = DUPLEX_FULL;
	}
	phy_write(phydev, MII_BMCR, val);
}

int genphy_update_link(struct phy_device *phydev)
{
	unsigned int mii_reg;
	int i = 0;
	unsigned long timeouts = PHY_ANEG_TIMEOUT;

	/*
	 * Wait if the link is up, and autonegotiation is in progress
	 * (ie - we're capable and it's not done)
	 */
	mii_reg = phy_read(phydev, MII_BMSR);

	if (phydev->autoneg == AUTONEG_ENABLE) {
		printf("eth%d Waiting for PHY auto negotiation to complete",
		       phydev->eth_id);
		while (!(mii_reg & BMSR_ANEGCOMPLETE)) {
			/*
			 * Timeout reached ?
			 */
			if (i > timeouts) {
				printf(" TIMEOUT !\n");
				return -ETIMEDOUT;
			}

			if ((i++ % 10) == 0)
				printf(".");

			mii_reg = phy_read(phydev, MII_BMSR);
			//udelay(50000); /* 50 ms */
			udelay(800000); /* 800 ms */
		}
		printf(" done\n");
	}

	return 0;
}

int genphy_parse_link(struct phy_device *phydev)
{
	int mii_reg = phy_read(phydev, MII_BMSR);

	/* We're using autonegotiation */
	if (phydev->autoneg == AUTONEG_ENABLE) {
		u32 lpa = 0;
		int gblpa = 0;
		u32 estatus = 0;

		/* Check for gigabit capability */
		if (phydev->interface != PHY_INTERFACE_MODE_RMII) {
			/* We want a list of states supported by
			 * both PHYs in the link
			 */
			gblpa = phy_read(phydev, MII_STAT1000);
			if (gblpa < 0) {
				printf("Could not read MII_STAT1000. ");
				printf("Ignoring gigabit capability\n");
				gblpa = 0;
			}
			gblpa &= phy_read(phydev, MII_CTRL1000) << 2;
		}

		/* Set the baseline so we only have to set them
		 * if they're different
		 */
		phydev->speed = SPEED_10;
		phydev->duplex = DUPLEX_HALF;

		/* Check the gigabit fields */
		if (gblpa & (PHY_1000BTSR_1000FD | PHY_1000BTSR_1000HD)) {
			phydev->speed = SPEED_1000;
			if (gblpa & PHY_1000BTSR_1000FD)
				phydev->duplex = DUPLEX_FULL;

			/* We're done! */
			return 0;
		}

		lpa = phy_read(phydev, MII_ADVERTISE);
		lpa &= phy_read(phydev, MII_LPA);

		if (lpa & (LPA_100FULL | LPA_100HALF)) {
			phydev->speed = SPEED_100;

			if (lpa & LPA_100FULL)
				phydev->duplex = DUPLEX_FULL;

		} else if (lpa & LPA_10FULL) {
			phydev->duplex = DUPLEX_FULL;
		}

		/*
		 * Extended status may indicate that the PHY supports
		 * 1000BASE-T/X even though the 1000BASE-T registers
		 * are missing. In this case we can't tell whether the
		 * peer also supports it, so we only check extended
		 * status if the 1000BASE-T registers are actually
		 * missing.
		 */
		if ((mii_reg & BMSR_ESTATEN) && !(mii_reg & BMSR_ERCAP))
			estatus = phy_read(phydev, MII_ESTATUS);

		if (estatus & (ESTATUS_1000_XFULL | ESTATUS_1000_XHALF |
			       ESTATUS_1000_TFULL | ESTATUS_1000_THALF)) {
			phydev->speed = SPEED_1000;
			if (estatus & (ESTATUS_1000_XFULL | ESTATUS_1000_TFULL))
				phydev->duplex = DUPLEX_FULL;
		}
	}
	return 0;
}

void phy_generic_handle(struct phy_device *phydev)
{
	genphy_update_link(phydev);
	genphy_parse_link(phydev);

	printf("%dMbps %s-duplex\n", phydev->speed,
	       phydev->duplex == DUPLEX_FULL ? "full" : "half");

	if (phydev->interface == PHY_INTERFACE_MODE_RGMII_RXID
	    || phydev->interface == PHY_INTERFACE_MODE_RGMII_TXID
	    || phydev->interface == PHY_INTERFACE_MODE_RGMII) {
		if (phydev->find_window) {
			if (phydev->interface == PHY_INTERFACE_MODE_RGMII_RXID
			    || phydev->interface == PHY_INTERFACE_MODE_RGMII_TXID
			    || phydev->interface == PHY_INTERFACE_MODE_RGMII) {
				if (phydev->duplex == DUPLEX_HALF)
					printf("force duplex half to full\n");
			}
			phy_enable_loopback(phydev, true);
		}
	}
}

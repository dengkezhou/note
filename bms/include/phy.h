/* SPDX-License-Identifier: GPL-2.0-or-later */
/*
 * Framework and drivers for configuring and reading different PHYs
 * Based on code in sungem_phy.c and (long-removed) gianfar_phy.c
 *
 * Author: Andy Fleming
 *
 * Copyright (c) 2004 Freescale Semiconductor, Inc.
 */

#ifndef __PHY_H__
#define __PHY_H__

/* Generic MII registers. */

#define MII_BMCR 0x00 /* Basic mode control register */
#define MII_BMSR 0x01 /* Basic mode status register  */
#define MII_PHYSID1 0x02 /* PHYS ID 1		       */
#define MII_PHYSID2 0x03 /* PHYS ID 2		       */
#define MII_ADVERTISE 0x04 /* Advertisement control reg   */
#define MII_LPA 0x05 /* Link partner ability reg    */
#define MII_EXPANSION 0x06 /* Expansion register	       */
#define MII_MMD_CTRL 0x0d /* MMD Access Control Register */
#define MII_MMD_DATA 0x0e /* MMD Access Data Register */
#define MII_DCOUNTER 0x12 /* Disconnect counter	       */
#define MII_FCSCOUNTER 0x13 /* False carrier counter       */
#define MII_NWAYTEST 0x14 /* N-way auto-neg test reg     */
#define MII_RERRCOUNTER 0x15 /* Receive error counter       */
#define MII_SREVISION 0x16 /* Silicon revision	       */
#define MII_RESV1 0x17 /* Reserved...		       */
#define MII_LBRERROR 0x18 /* Lpback, rx, bypass error    */
#define MII_PHYADDR 0x19 /* PHY address		       */
#define MII_RESV2 0x1a /* Reserved...		       */
#define MII_TPISTATUS 0x1b /* TPI status for 10mbps       */
#define MII_NCONFIG 0x1c /* Network interface config    */

/* Basic mode control register. */
#define BMCR_RESV 0x003f /* Unused...		       */
#define BMCR_SPEED1000 0x0040 /* MSB of Speed (1000)	       */
#define BMCR_CTST 0x0080 /* Collision test	       */
#define BMCR_FULLDPLX 0x0100 /* Full duplex		       */
#define BMCR_ANRESTART 0x0200 /* Auto negotiation restart    */
#define BMCR_ISOLATE 0x0400 /* Disconnect DP83840 from MII */
#define BMCR_PDOWN 0x0800 /* Powerdown the DP83840       */
#define BMCR_ANENABLE 0x1000 /* Enable auto negotiation     */
#define BMCR_SPEED100 0x2000 /* Select 100Mbps	       */
#define BMCR_LOOPBACK 0x4000 /* TXD loopback bits	       */
#define BMCR_RESET 0x8000 /* Reset the DP83840	       */

/* Basic mode status register. */
#define BMSR_ERCAP 0x0001 /* Ext-reg capability	       */
#define BMSR_JCD 0x0002 /* Jabber detected	       */
#define BMSR_LSTATUS 0x0004 /* Link status		       */
#define BMSR_ANEGCAPABLE 0x0008 /* Able to do auto-negotiation */
#define BMSR_RFAULT 0x0010 /* Remote fault detected       */
#define BMSR_ANEGCOMPLETE 0x0020 /* Auto-negotiation complete   */
#define BMSR_RESV 0x07c0 /* Unused...		       */
#define BMSR_10HALF 0x0800 /* Can do 10mbps, half-duplex  */
#define BMSR_10FULL 0x1000 /* Can do 10mbps, full-duplex  */
#define BMSR_100HALF 0x2000 /* Can do 100mbps, half-duplex */
#define BMSR_100FULL 0x4000 /* Can do 100mbps, full-duplex */
#define BMSR_100BASE4 0x8000 /* Can do 100mbps, 4k packets  */

/* Enable or disable autonegotiation. */
#define AUTONEG_DISABLE 0x00
#define AUTONEG_ENABLE 0x01

/* MDI or MDI-X status/control - if MDI/MDI_X/AUTO is set then
 * the driver is required to renegotiate link
 */
#define ETH_TP_MDI_INVALID 0x00 /* status: unknown; control: unsupported */
#define ETH_TP_MDI 0x01 /* status: MDI;     control: force MDI */
#define ETH_TP_MDI_X 0x02 /* status: MDI-X;   control: force MDI-X */
#define ETH_TP_MDI_AUTO 0x03 /*                  control: auto-select */

#define PHY_INTERRUPT_DISABLED false
#define PHY_INTERRUPT_ENABLED true

/* Which connector port. */
#define PORT_TP 0x00
#define PORT_AUI 0x01
#define PORT_MII 0x02
#define PORT_FIBER 0x03
#define PORT_BNC 0x04
#define PORT_DA 0x05
#define PORT_NONE 0xef
#define PORT_OTHER 0xff

#define SPEED_10 10
#define SPEED_100 100
#define SPEED_1000 1000
#define SPEED_2500 2500
#define SPEED_5000 5000
#define SPEED_10000 10000
#define SPEED_14000 14000
#define SPEED_20000 20000
#define SPEED_25000 25000
#define SPEED_40000 40000
#define SPEED_50000 50000
#define SPEED_56000 56000
#define SPEED_100000 100000
#define SPEED_200000 200000
#define SPEED_400000 400000

#define SPEED_UNKNOWN -1

/* Duplex, half or full. */
#define DUPLEX_HALF 0x00
#define DUPLEX_FULL 0x01
#define DUPLEX_UNKNOWN 0xff

#define BMSR_ESTATEN 0x0100 /* Extended Status in R15      */

/* phy 1000BTSR */
#define PHY_1000BTSR_MSCF	0x8000
#define PHY_1000BTSR_MSCR	0x4000
#define PHY_1000BTSR_LRS	0x2000
#define PHY_1000BTSR_RRS	0x1000
#define PHY_1000BTSR_1000FD	0x0800
#define PHY_1000BTSR_1000HD	0x0400

#define MII_CTRL1000 0x09 /* 1000BASE-T control          */
#define MII_STAT1000 0x0a /* 1000BASE-T status           */

#define LPA_1000FULL 0x0800 /* Link partner 1000BASE-T full duplex */
#define LPA_1000HALF 0x0400 /* Link partner 1000BASE-T half duplex */

#define ESTATUS_1000_XFULL 0x8000 /* Can do 1000BX Full */
#define ESTATUS_1000_XHALF 0x4000 /* Can do 1000BX Half */
#define ESTATUS_1000_TFULL 0x2000 /* Can do 1000BT Full          */
#define ESTATUS_1000_THALF 0x1000 /* Can do 1000BT Half          */

#define PHY_ANEG_TIMEOUT 8 //120

/**
 * enum phy_interface_t - Interface Mode definitions
 *
 * @PHY_INTERFACE_MODE_NA: Not Applicable - don't touch
 * @PHY_INTERFACE_MODE_INTERNAL: No interface, MAC and PHY combined
 * @PHY_INTERFACE_MODE_MII: Media-independent interface
 * @PHY_INTERFACE_MODE_GMII: Gigabit media-independent interface
 * @PHY_INTERFACE_MODE_SGMII: Serial gigabit media-independent interface
 * @PHY_INTERFACE_MODE_TBI: Ten Bit Interface
 * @PHY_INTERFACE_MODE_REVMII: Reverse Media Independent Interface
 * @PHY_INTERFACE_MODE_RMII: Reduced Media Independent Interface
 * @PHY_INTERFACE_MODE_REVRMII: Reduced Media Independent Interface in PHY role
 * @PHY_INTERFACE_MODE_RGMII: Reduced gigabit media-independent interface
 * @PHY_INTERFACE_MODE_RGMII_ID: RGMII with Internal RX+TX delay
 * @PHY_INTERFACE_MODE_RGMII_RXID: RGMII with Internal RX delay
 * @PHY_INTERFACE_MODE_RGMII_TXID: RGMII with Internal RX delay
 * @PHY_INTERFACE_MODE_RTBI: Reduced TBI
 * @PHY_INTERFACE_MODE_SMII: Serial MII
 * @PHY_INTERFACE_MODE_XGMII: 10 gigabit media-independent interface
 * @PHY_INTERFACE_MODE_XLGMII:40 gigabit media-independent interface
 * @PHY_INTERFACE_MODE_MOCA: Multimedia over Coax
 * @PHY_INTERFACE_MODE_QSGMII: Quad SGMII
 * @PHY_INTERFACE_MODE_TRGMII: Turbo RGMII
 * @PHY_INTERFACE_MODE_100BASEX: 100 BaseX
 * @PHY_INTERFACE_MODE_1000BASEX: 1000 BaseX
 * @PHY_INTERFACE_MODE_2500BASEX: 2500 BaseX
 * @PHY_INTERFACE_MODE_5GBASER: 5G BaseR
 * @PHY_INTERFACE_MODE_RXAUI: Reduced XAUI
 * @PHY_INTERFACE_MODE_XAUI: 10 Gigabit Attachment Unit Interface
 * @PHY_INTERFACE_MODE_10GBASER: 10G BaseR
 * @PHY_INTERFACE_MODE_25GBASER: 25G BaseR
 * @PHY_INTERFACE_MODE_USXGMII:  Universal Serial 10GE MII
 * @PHY_INTERFACE_MODE_10GKR: 10GBASE-KR - with Clause 73 AN
 * @PHY_INTERFACE_MODE_MAX: Book keeping
 *
 * Describes the interface between the MAC and PHY.
 */
typedef enum {
	PHY_INTERFACE_MODE_NA,
	PHY_INTERFACE_MODE_INTERNAL,
	PHY_INTERFACE_MODE_MII,
	PHY_INTERFACE_MODE_GMII,
	PHY_INTERFACE_MODE_SGMII,
	PHY_INTERFACE_MODE_TBI,
	PHY_INTERFACE_MODE_REVMII,
	PHY_INTERFACE_MODE_RMII,
	PHY_INTERFACE_MODE_REVRMII,
	PHY_INTERFACE_MODE_RGMII,
	PHY_INTERFACE_MODE_RGMII_ID,
	PHY_INTERFACE_MODE_RGMII_RXID,
	PHY_INTERFACE_MODE_RGMII_TXID,
	PHY_INTERFACE_MODE_RTBI,
	PHY_INTERFACE_MODE_SMII,
	PHY_INTERFACE_MODE_XGMII,
	PHY_INTERFACE_MODE_XLGMII,
	PHY_INTERFACE_MODE_MOCA,
	PHY_INTERFACE_MODE_QSGMII,
	PHY_INTERFACE_MODE_TRGMII,
	PHY_INTERFACE_MODE_100BASEX,
	PHY_INTERFACE_MODE_1000BASEX,
	PHY_INTERFACE_MODE_2500BASEX,
	PHY_INTERFACE_MODE_5GBASER,
	PHY_INTERFACE_MODE_RXAUI,
	PHY_INTERFACE_MODE_XAUI,
	/* 10GBASE-R, XFI, SFI - single lane 10G Serdes */
	PHY_INTERFACE_MODE_10GBASER,
	PHY_INTERFACE_MODE_25GBASER,
	PHY_INTERFACE_MODE_USXGMII,
	/* 10GBASE-KR - with Clause 73 AN */
	PHY_INTERFACE_MODE_10GKR,
	PHY_INTERFACE_MODE_MAX,
} phy_interface_t;

/**
 * struct phy_device - An instance of a PHY
 *
 * @phy_id: UID for this device found during discovery
 * @speed: Current link speed
 * @duplex: Current duplex
 * @autoneg: Flag autoneg being used
 * @mdix_ctrl: User setting of crossover
 * 
 */
struct phy_device {
	int eth_id;
	u32 phy_id;
	unsigned int phy_addr;
	bool autoneg;
	phy_interface_t interface;
	/*
	 * forced speed & duplex (no autoneg)
	 * partner speed & duplex & pause (autoneg)
	 */
	int speed;
	int duplex;
	u8 mdix_ctrl;
	int find_window;
};

int macb_phy_find(struct phy_device *phydev, const char *name);
int genphy_read_status_fixed(struct phy_device *phydev);
int get_phy_speed_duplex(struct phy_device *phydev);
int genphy_soft_reset(struct phy_device *phydev);
void phy_enable_loopback(struct phy_device *phydev, bool change_speed);
int phy_modify_changed(struct phy_device *phydev, int reg, u16 mask,
			      u16 set);
int phy_modify(struct phy_device *phydev, int reg, u16 mask, u16 set);
void phy_set_speed(struct phy_device *phydev);
void phy_generic_handle(struct phy_device *phydev);

#endif /* __PHY_H */

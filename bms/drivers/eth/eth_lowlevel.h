#ifndef __ETH_LOWLEVEL_H__
#define __ETH_LOWLEVEL_H__

/* times for s2c rgmii gmac0 and gmac1 phy 88e1116r. */
#define GMAC0_PHASE_MODULATION_TIMES 108
#define GMAC1_PHASE_MODULATION_TIMES 79
#define GMAC2_PHASE_MODULATION_TIMES 50
#define GMAC3_PHASE_MODULATION_TIMES 83

#define GMAC0_TX_DLY_LINE 48//127//29
#define GMAC0_RX_DLY_LINE 15//127//192
#define GMAC1_TX_DLY_LINE 59//127//33
#define GMAC1_RX_DLY_LINE 5//127//188

#define GMAC2_TX_DLY_LINE 58//127//29
#define GMAC2_RX_DLY_LINE 171//127//192
#define GMAC3_TX_DLY_LINE 34//127//33
#define GMAC3_RX_DLY_LINE 99//127//188

int phy_set_tx_clk(eth_device *dev, struct phy_device *phydev);
void mdio_init(eth_device *dev, struct phy_device *phydev);
int mdio_write(struct phy_device *phydev, int reg, unsigned short val);
int mdio_read(struct phy_device *phydev, int reg);

void eth_lowlevel_filter_mac(eth_device *dev, mac_addr *m_addr,
			     unsigned char type, bool enable);
int eth_lowlevel_irq_handler(int irq, void *args);
int eth_lowlevel_init(eth_device *dev);
void eth_lowlevel_free(eth_device *dev);
int eth_lowlevel_is_completed(eth_device *dev, eth_check check);
int eth_lowlevel_send(eth_device *dev, unsigned char *buf, unsigned int size);
int eth_lowlevel_recv(eth_device *dev, unsigned char *buf, unsigned int size);
void eth_lowlevel_enable(eth_device *dev);

#endif

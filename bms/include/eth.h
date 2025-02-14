#ifndef __ETH_H__
#define __ETH_H__

#include <stdint.h>
#include <irq.h>
#include "cdn_errno.h"
#include "cdn_log.h"
#include "cdn_stdint.h"
#include "cps.h"
#include "edd_data.h"
#include "edd_int.h"
#include <phy.h>

#define GMAC_TSU_CLK 50000000
#define GMAC_GTX_CLK 250000000
#define GMAC_REF_CLK 50000000

#define ETH_SUCCESS_RET 0U
#define ETH_FAILURE_RET 1U

#define ETH_AUTO_NEGOTIATION_DISABLE 0
#define ETH_AUTO_NEGOTIATION_ENABLE 1
#define ETH_JUMBO_DISABLE 0
#define ETH_JUMBO_ENABLE 1
#define ETH_FILTER_ENABLE 1
#define ETH_FILTER_DISABLE 0
#define ETH_EMAC_ENABLE 1
#define ETH_EMAC_DISABLE 0

#define ETH_FORMAT_ETHERNET_II 0U
#define ETH_FORMAT_IEEE_80211 1U

#define ETH_SPEED_10 10
#define ETH_SPEED_100 100
#define ETH_SPEED_1000 1000

#define PHY_LOOPBACK_ENABLE 1
#define PHY_LOOPBACK_DISABLE 0
#define RMII_INT_REF_CLK 0
#define RMII_EXT_REF_CLK 1
#define PHY_WOL_ENABLE 1
#define PHY_WOL_DISABLE 0

enum { NONBLOCK, BLOCK };

typedef enum { ETH_RX_CHECK, ETH_TX_CHECK } eth_check;

typedef enum {
	PARAM_ERROR = 1,
	TRANSMIT_ERROR = 2,
	ALLOC_BUFFER_ERROR = 3,
	FRAMESIZE_TOO_SMALL = 4,
	CONSTITUTE_FRAME_ERROR = 5,
} ETH_Error;

typedef enum { ETH0, ETH1, ETH2, ETH3 } eth_id;

typedef enum {
	ETH_MODE_NORMAL,
	ETH_MODE_LOCAL_LOOPBACK,
	ETH_MODE_SERDES_LOOPBACK
} eth_mode;

typedef enum { ETH_SPEED_10M, ETH_SPEED_100M, ETH_SPEED_1000M } eth_speed;

typedef enum { ETH_HALF_DUPLEX, ETH_FULL_DUPLEX } duplex_mode;

typedef enum { ETH_RGMII, ETH_RMII } eth_interface;

typedef struct {
	eth_id id;
	eth_speed speed; /* 10/100/1000, must be ETH_SPEED_xx */
	eth_mode mode; /* normal or loopback */
	duplex_mode duplex;
	bool jumbo_en; /* giant frame support */
	bool auto_nego_en;
	eth_interface interface;
	bool enable_emac;
	/* phy loopback for rgmii phase modulation. */
	bool phy_loopback;
	bool ext_ref_clk;
	bool phy_enable_wol;
} eth_config;

typedef struct {
	unsigned char mac[6];
} mac_addr;

typedef enum { ETH_FILTER_DST, ETH_FILTER_SRC } filter_type;

/* only 4 mac address filter register */
typedef struct {
	mac_addr addr;
	/* 1:source mac filter  0:destination mac filter */
	unsigned char filter_type;
	/* 0-0x3F, low 6 bits available for mac bytes 0-5,
	 * when set to 1,ingore compare this byte.
	 */
	unsigned char byte_mask;
} mac_filter;

typedef struct {
	eth_config *config;
	mac_addr *m_addr;
	mac_filter filter; /* mac filter                         */
	CEDI_BuffAddr rx_buf; /* point to eth rx Buffer             */
	unsigned int rx_buf_size; /* eth receive buffer size            */
	unsigned int rx_cnt; /* eth received bytes Counter         */
	int rx_finished; /* eth rx status                      */
	CEDI_BuffAddr tx_buf; /* point to eth tx Buffer             */
	unsigned int tx_buf_size; /* eth transfer buffer size           */
	unsigned int tx_cnt; /* eth transfered bytes counter       */
	int tx_finished; /* eth tx status                      */
	struct phy_device *phy_dev;
	CEDI_PrivateData *eMacPrivData[2];
} eth_device;

#if defined(CONFIG_C920) && \
	(defined(CONFIG_TB_RUN_DDR) || defined(CONFIG_TB_RUN_DDR1))
extern volatile unsigned int is_gmac3;
void *gmac3_mem_alloc(void);
#endif

eth_device *itcs_eth_init(eth_config *config);
void itcs_eth_exit(eth_device *dev);
int itcs_eth_phy_init(eth_device *dev);
mac_addr *itcs_eth_get_mac_addr(eth_device *dev);
int itcs_eth_set_mac_addr(eth_device *dev, mac_addr *addr);
int itcs_eth_filter_mac_addr(eth_device *dev, mac_addr *addr, filter_type type,
			     bool enable);
int itcs_eth_send(eth_device *dev, unsigned char *buf, unsigned int size,
		  unsigned char is_block);
int itcs_eth_recv(eth_device *dev, unsigned char *buf, unsigned int size,
		  unsigned char is_block);
int itcs_eth_is_completed(eth_device *dev, eth_check check);

#endif

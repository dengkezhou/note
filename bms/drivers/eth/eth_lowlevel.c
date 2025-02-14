#include <common.h>
#include <asm/io.h>
#include <malloc.h>
#include <pads.h>
#include <cache.h>
#include <eth.h>
#include <phy.h>
#include "eth_lowlevel.h"
#include "cdn_log.h"
#include "edd_support.h"

#if DEBUG_ETH
#define net_dev_err(...) printf(__VA_ARGS__)
#else
#define net_dev_err(...)
#endif

#if defined(CONFIG_COMPILE_FPGA) || defined(CONFIG_COMPILE_ASIC)
#define NORMAL_TXQ_SIZE 12
#define NORMAL_RXQ_SIZE 12
#define RX_BUF_LEN_FOR_QUEUE 2048
#define EMAC_HW_PRIO_QUE_NUMS 1
#elif defined(CONFIG_COMPILE_RTL)
#define HW_PRIO_QUE_NUMS 1
#define NORMAL_TXQ_SIZE 1
#define NORMAL_RXQ_SIZE 1
#define RX_BUF_LEN_FOR_QUEUE 128
#endif

#define JUMBO_TXQ_SIZE 1
#define JUMBO_RXQ_SIZE 1
#define JUMBO_HW_PRIO_QUE_NUMS 1
#define JUMBO_RX_BUF_LEN_FOR_QUEUE 16320

#define JUMBO_TX_FULL_THRESH0_REG 0x04f8

/* module mask: */
#ifdef _HAVE_DBG_LOG_INT_
uint32_t g_dbg_enable_log = 1;
#else
extern uint32_t g_dbg_enable_log;
#endif

/* level, counter, state: */
#ifdef _HAVE_DBG_LOG_INT_
uint32_t g_dbg_log_lvl = DBG_FYI;
uint32_t g_dbg_log_cnt = 0;
uint32_t g_dbg_state = 0;
#else
extern uint32_t g_dbg_log_lvl;
extern uint32_t g_dbg_log_cnt;
extern uint32_t g_dbg_state;
#endif

extern CEDI_Callbacks core_callbacks;
extern uint32_t allocBuffer(uint32_t bytes, uint32_t fill, CEDI_BuffAddr *buf);
extern void insertEthHeader(ethHdr_t *header, CEDI_BuffAddr *buffer);
extern uint32_t initConfigMaxNumQs(uint8_t objInst, uint16_t txQSize,
				   uint16_t rxQSize, uint16_t rxBufLenBytes,
				   uint32_t intrEvents, CEDI_Config *cfg);
extern uint32_t allocSysReqMem(uint8_t objInst, CEDI_SysReq *req,
			       CEDI_Config *cfg);
extern void zeroCallbackCounters(void);
extern long NCPS_freeHWMem(uintptr_t addr);
extern uint8_t WriteRegAndVerify(volatile uint32_t *address, uint32_t value);
extern uint32_t setScrnT2Reg(const int emac, CEDI_MacAddress SrcAddr,
			     uint8_t screenReg, uint8_t compReg,
			     uint8_t queueNum);
#ifdef CONFIG_COMPILE_ASIC
extern void mac_find_delay_line(int id, int txpaddly, int rxdly);
#else
extern void mac_find_txdly_window(int id, int times);
#endif

int phy_set_tx_clk(eth_device *dev, struct phy_device *phydev)
{
	CEDI_PrivateData *pD = privData[dev->config->id];
	const CEDI_Config *config = &(pD->cfg);
	uint32_t regVal = 0U;
	volatile uint32_t *regAddr = &(pD->regs->network_config);

	printf("set mac speed to %dMbit\n", phydev->speed);
	printf("set mac duplex to %s\n",
	       phydev->duplex == DUPLEX_FULL ? "full" : "half");
	regVal = CPS_UncachedRead32(&(pD->regs->network_config));

	/* The following covers MII/GMII/RGMII/SGMII and BASE_X, i.e.
	   excludes XGMII and SERDES where the high speed enable
	   overrides all this anyway. */
	if (config->ifTypeSel <= CEDI_IFSP_BASE_X) {
		if (phydev->speed >= SPEED_1000)
			EMAC_REGS__NETWORK_CONFIG__GIGABIT_MODE_ENABLE__SET(
				regVal);
		else if (phydev->speed > SPEED_10)
			EMAC_REGS__NETWORK_CONFIG__SPEED__SET(regVal);
	}

	if (0U != phydev->duplex)
		EMAC_REGS__NETWORK_CONFIG__FULL_DUPLEX__SET(regVal);

	WriteRegAndVerify(regAddr, regVal);
#ifdef CONFIG_COMPILE_ASIC
	if (dev->config->id == ETH0)
		mac_find_delay_line(dev->config->id, GMAC0_TX_DLY_LINE, GMAC0_RX_DLY_LINE);
	else if (dev->config->id == ETH1)
		mac_find_delay_line(dev->config->id, GMAC1_TX_DLY_LINE, GMAC1_RX_DLY_LINE);
	else if (dev->config->id == ETH2)
		mac_find_delay_line(dev->config->id, GMAC2_TX_DLY_LINE, GMAC2_RX_DLY_LINE);
	else if (dev->config->id == ETH3)
		mac_find_delay_line(dev->config->id, GMAC3_TX_DLY_LINE, GMAC3_RX_DLY_LINE);
#else
	if (phydev->speed == SPEED_1000) {
		if (dev->config->id == 0)
			mac_find_txdly_window(dev->config->id,
					      GMAC0_PHASE_MODULATION_TIMES);
		else if (dev->config->id == 1)
			mac_find_txdly_window(dev->config->id,
					      GMAC1_PHASE_MODULATION_TIMES);
	}
#endif
	return 0;
}

void mdio_init(eth_device *dev, struct phy_device *phydev)
{
	int id = dev->config->id;
	phydev->eth_id = id;
	emacObj[id]->setMdioEnable(privData[id], true);
}

int mdio_write(struct phy_device *phydev, int reg, unsigned short val)
{
	int id = phydev->eth_id;
	int phy_addr = phydev->phy_addr;
	unsigned int status;
	int ret;
	status = emacObj[id]->phyStartMdioWrite(
		privData[id], CEDI_MDIO_FLG_CLAUSE_22, phy_addr, reg, val);
	if (status != CDN_EOK) {
		net_dev_err("mdio write failed!\n");
		return -1;
	}
	while (1) {
		ret = emacObj[id]->getMdioIdle(privData[id]);
		if (ret == 1)
			break;
	}
	return 0;
}

int mdio_read(struct phy_device *phydev, int reg)
{
	int id = phydev->eth_id;
	int phy_addr = phydev->phy_addr;
	unsigned short val = 0;
	int ret;
	unsigned int status;

	status = emacObj[id]->phyStartMdioRead(
		privData[id], CEDI_MDIO_FLG_CLAUSE_22, phy_addr, reg);
	if (status != CDN_EOK) {
		net_dev_err("mdio start read failed!\n");
		return -1;
	}
	while (1) {
		ret = emacObj[id]->getMdioIdle(privData[id]);
		if (ret == 1) {
			status = emacObj[id]->getMdioReadData(privData[id],
							      &val);
			if (status != CDN_EOK) {
				net_dev_err("mdio get read data failed!\n");
				return -1;
			}
			break;
		}
	}
	return val;
}

void eth_lowlevel_filter_mac(eth_device *dev, mac_addr *m_addr,
			     unsigned char type, bool enable)
{
	int id = dev->config->id;
	CEDI_MacAddress *addr = (CEDI_MacAddress *)m_addr;

	if (enable) {
		emacObj[id]->setSpecificAddr(privData[id], 1, addr, type, 0);
		emacObj[id]->setCopyAllFrames(privData[id], 0);
		/* don't receive broadcast frames. */
		emacObj[id]->setNoBroadcast(privData[id], 1);
	} else {
		emacObj[id]->setCopyAllFrames(privData[id], 1);
		emacObj[id]->setNoBroadcast(privData[id], 0);
	}
}

void eth_lowlevel_enable(eth_device *dev)
{
	eth_config *config = dev->config;
	int id = config->id;
	CEDI_MmslStatus mmslStatus;
	uint32_t result;

	/* start EMAC + enable Rx & Tx */
	if (config->enable_emac == ETH_EMAC_ENABLE) {
		emacObj[id]->start(privData[id]);
		//emacObj[id]->enableRx(dev->eMacPrivData[id]);
		//emacObj[id]->enableTx(dev->eMacPrivData[id]);

		//emacObj[id]->clearStats(dev->eMacPrivData[id]);
		result = emacObj[id]->readMmslStatus(privData[id], &mmslStatus);
		if (result != CDN_EOK) {
			printf("readMmslStatus failed!\n");
			return;
		}
	} else {
		emacObj[id]->start(privData[id]);
		emacObj[id]->enableRx(privData[id]);
		emacObj[id]->enableTx(privData[id]);

		emacObj[id]->clearStats(privData[id]);
	}
}

int eth_lowlevel_send(eth_device *dev, unsigned char *buf, unsigned int size)
{
	CEDI_BuffAddr *tx_buf = &dev->tx_buf;
	int id = dev->config->id;
	unsigned int result;

	tx_buf->vAddr = (unsigned long)buf;
	tx_buf->pAddr = (unsigned long)buf;

	if (dev->config->enable_emac)
		result = emacObj[id]->queueTxBuf(
			dev->eMacPrivData[id], 0, tx_buf, size,
			CEDI_TXB_LAST_BUFF | CEDI_TXB_NO_AUTO_CRC);
	else
		result = emacObj[id]->queueTxBuf(privData[id], 0, tx_buf, size,
						 CEDI_TXB_LAST_BUFF);
	if (result != CDN_EOK) {
		printf("queueTxBuf failed!\n");
		return -1;
	}
	dev->tx_finished = 0;
	return 0;
}

int eth_lowlevel_recv(eth_device *dev, unsigned char *buf, unsigned int size)
{
	CEDI_BuffAddr *rx_buf = &dev->rx_buf;

	rx_buf->vAddr = (unsigned long)buf;
	rx_buf->pAddr = (unsigned long)buf;

	dev->rx_buf_size = size;
	dev->rx_cnt = 0;
	dev->rx_finished = 0;
	return 0;
}

int eth_lowlevel_is_completed(eth_device *dev, eth_check check)
{
	if (dev == NULL)
		return -1;

	if (check == ETH_RX_CHECK) {
		if (dev->rx_cnt == dev->rx_buf_size)
			dev->rx_finished = 1;
		else
			dev->rx_finished = 0;

		return dev->rx_finished;
	} else if (check == ETH_TX_CHECK) {
		return dev->tx_finished;
	} else {
		return -1;
	}
}

int eth_lowlevel_irq_handler(int irq, void *args)
{
	eth_device *dev = (eth_device *)args;
	CEDI_BuffAddr *rx_buf = &dev->rx_buf;
	int id = dev->config->id;
	CEDI_RxDescData rxDescDat;
	CEDI_RxStatus rxStatus;
	CEDI_RxDescStat rxDStat;
	CEDI_TxStatus txStatus;
	CEDI_TxDescData txDescDat;
	unsigned int result;
	int i = 0, j = 0;
	unsigned int prio_queue_nums = 0;
	unsigned long rx_buf_nums = 0;
	CEDI_PrivateData *private_data = NULL;

	//printf("-i: %d-\n", irq);

	if (dev->config->enable_emac == ETH_EMAC_ENABLE)
		private_data = dev->eMacPrivData[id];
	else
		private_data = privData[id];

	emacObj[dev->config->id]->isr(private_data);

#if defined(CONFIG_COMPILE_FPGA) || defined(CONFIG_COMPILE_ASIC)
	if (dev->config->enable_emac == ETH_EMAC_ENABLE)
		prio_queue_nums = EMAC_HW_PRIO_QUE_NUMS;
	else
		prio_queue_nums = cfgHwQs(id);
#elif defined(CONFIG_COMPILE_RTL)
	prio_queue_nums = HW_PRIO_QUE_NUMS;
#endif

	/* cache flush for recv. */
	itcs_dcache_flush();
	for (i = 0; i < prio_queue_nums; i++) {
		rx_buf_nums = emacObj[id]->numRxUsed(private_data, i);
		if (rx_buf_nums) {
			for (j = 0; j < rx_buf_nums; j++) {
				//printf("-rx-\n");
				result = emacObj[id]->readRxBuf(private_data, i,
								&nBuf[i][j], 0,
								&rxDescDat);
				if (result != CDN_EOK) {
					printf("readRxBuf failed!\n");
					return 0;
				}
				if (rxDescDat.status != CEDI_RXDATA_SOF_EOF) {
					printf("not CEDI_RXDATA_SOF_EOF\n");
					return 0;
				}

				emacObj[id]->getRxDescStat(private_data,
							   rxDescDat.rxDescStat,
							   &rxDStat);
				if (rxDStat.bufLen <= dev->rx_buf_size) {
					memcpy((unsigned char *)rx_buf->vAddr,
					       (unsigned char *)nBuf[i][j].vAddr,
					       rxDStat.bufLen);
#if 0
					for (int k = 0; k < rxDStat.bufLen; k++)
						printf("[%d]: 0x%x\n", k, *((unsigned char *)rx_buf->vAddr + k));
#endif
					dev->rx_cnt = rxDStat.bufLen;
					dev->rx_finished = 1;
				}

				emacObj[id]->getRxStatus(private_data,
							 &rxStatus);
				if (rxStatus.frameRx) {
					emacObj[id]->clearRxStatus(
						private_data,
						CEDI_RXS_FRAME_RX);
				}
			}
		}
	}

	emacObj[id]->getTxStatus(private_data, &txStatus);
	if (txStatus.usedBitRead || txStatus.txComplete) {
		//printf("-tx-\n");
		emacObj[id]->clearTxStatus(
			private_data,
			(txStatus.txComplete ? CEDI_TXS_TX_COMPLETE : 0) |
				(txStatus.collisionOcc ? CEDI_TXS_COLLISION :
							       0) |
				(txStatus.hRespNotOk ? CEDI_TXS_HRESP_ERR : 0) |
				(txStatus.lateCollision ? CEDI_TXS_LATE_COLL :
								0) |
				(txStatus.retryLimExc ? CEDI_TXS_RETRY_EXC :
							      0) |
				(txStatus.txFrameErr ? CEDI_TXS_FRAME_ERR : 0) |
				(txStatus.txUnderRun ? CEDI_TXS_UNDERRUN : 0) |
				(txStatus.usedBitRead ? CEDI_TXS_USED_READ :
							      0));
		if (txStatus.txComplete)
			dev->tx_finished = 1;
		else
			dev->tx_finished = 0;
		if (txStatus.txComplete) {
			result = emacObj[id]->freeTxDesc(private_data, 0,
							 &txDescDat);
			if (result == CDN_EINVAL)
				dev->tx_finished = 0;
			else
				dev->tx_finished = 1;
		} else {
			dev->tx_finished = 0;
		}
	}
#if 0
	printf("--emac f04: 0x%x---\n", readl(0xc4400000 + 0xf04));
	printf("--emac f18: 0x%x---\n", readl(0xc4400000 + 0xf18));
	printf("--emac f1c: 0x%x---\n", readl(0xc4400000 + 0xf1c));
	printf("--emac f20: 0x%x---\n", readl(0xc4400000 + 0xf20));

	printf("--emac 1014: 0x%x---\n", readl(0xc4400000 + 0x1014));
	printf("--emac 1020: 0x%x---\n", readl(0xc4400000 + 0x1020));

	printf("--emac 1024: 0x%x---\n", readl(0xc4400000 + 0x1024));
#endif
	//printf("-o-\n");
	return 0;
}

static unsigned int gem_mdc_clk_div(void)
{
	unsigned int div;
	unsigned long pclk_hz = itcs_module_get_clock(CPU, "apb");

	if (pclk_hz != 50000000)
		printf("apb clk is not 50MHz! apb clk: %ld\n", pclk_hz);

	if (pclk_hz <= 20000000)
		div = CEDI_MDC_DIV_BY_8;
	else if (pclk_hz <= 40000000)
		div = CEDI_MDC_DIV_BY_16;
	else if (pclk_hz <= 80000000)
		div = CEDI_MDC_DIV_BY_32;
	else if (pclk_hz <= 120000000)
		div = CEDI_MDC_DIV_BY_48;
	else if (pclk_hz <= 160000000)
		div = CEDI_MDC_DIV_BY_64;
	else
		div = CEDI_MDC_DIV_BY_96;

	return div;
}

int eth_lowlevel_init(eth_device *dev)
{
	eth_config *config = dev->config;
	int id = config->id;
	CEDI_Config *cfg = NULL;
	CEDI_SysReq *req = NULL;
	unsigned int result, eventsToEnable, val = 0;
	int i, j;
	unsigned int prio_queue_nums = 0;
	unsigned int t_q_size = NORMAL_TXQ_SIZE;
	unsigned int r_q_size = NORMAL_RXQ_SIZE;
	unsigned int buf_len_bytes = RX_BUF_LEN_FOR_QUEUE;
	CEDI_SegmentsPerQueue seg_per_q = CEDI_SEGMENTS_PER_QUEUE_4;
	CEDI_QueueSegAlloc queueSegAlloc = { &seg_per_q, 1 };
	CEDI_PreemptionConfig preCfg;

#ifdef _HAVE_DBG_LOG_INT_
	g_dbg_enable_log = 1;
	DbgMsgSetLvl(DBG_FYI);
	DbgMsgEnableModule(DBG_GEN_MSG);
#endif
	emacObj[id] = CEDI_GetInstance();

#if defined(CONFIG_C920) && \
	(defined(CONFIG_TB_RUN_DDR) || defined(CONFIG_TB_RUN_DDR1))
	if (id == ETH3)
		cfg = (CEDI_Config *)gmac3_mem_alloc();
	else
		cfg = (CEDI_Config *)malloc(sizeof(CEDI_Config));
#else
	cfg = (CEDI_Config *)malloc(sizeof(CEDI_Config));
#endif
	if (!cfg) {
		printf("cfg malloc failed\n");
		return -1;
	}
	memset(cfg, 0, sizeof(CEDI_Config));

#if defined(CONFIG_C920) && \
	(defined(CONFIG_TB_RUN_DDR) || defined(CONFIG_TB_RUN_DDR1))
	if (id == ETH3)
		req = (CEDI_SysReq *)gmac3_mem_alloc();
	else
		req = (CEDI_SysReq *)malloc(sizeof(CEDI_SysReq));
#else
	req = (CEDI_SysReq *)malloc(sizeof(CEDI_SysReq));
#endif
	if (!req) {
		printf("req malloc failed\n");
		return -1;
	}
	memset(req, 0, sizeof(CEDI_SysReq));

	eventsToEnable = CEDI_EVSET_TX_RX_EVENTS;

	if (config->jumbo_en == ETH_JUMBO_ENABLE) {
		t_q_size = JUMBO_TXQ_SIZE;
		r_q_size = JUMBO_RXQ_SIZE;
		buf_len_bytes = JUMBO_RX_BUF_LEN_FOR_QUEUE;
	}

	if (0 !=
	    (result = initConfigMaxNumQs(id, t_q_size, r_q_size, buf_len_bytes,
					 eventsToEnable, cfg))) {
		printf("Error in initConfig: returned %d\n", result);
		return -1;
	}

	if (config->enable_emac == ETH_EMAC_ENABLE) {
		cfg->incExpressTraffic = 1;
		cfg->eTxQLen[0] = t_q_size;
		cfg->eRxQLen[0] = r_q_size;
	}

	if (config->jumbo_en == ETH_JUMBO_ENABLE)
		cfg->rxJumboFrEn = 1;

	if (config->mode != ETH_MODE_LOCAL_LOOPBACK &&
	    config->mode != ETH_MODE_SERDES_LOOPBACK) {
		cfg->enableMdio = 1;
		cfg->mdcPclkDiv = gem_mdc_clk_div();
	}

	if (config->interface == ETH_RMII) {
		cfg->ifTypeSel = CEDI_IFSP_MII;
		if (config->speed == ETH_SPEED_1000M) {
			printf("rmii doesn't support speed 1000M\n");
			return -1;
		}
	} else if (config->interface == ETH_RGMII) {
		cfg->ifTypeSel = CEDI_IFSP_RGMII;
	} else {
		printf("unsupported interface %d\n", config->interface);
		return -1;
	}

	if ((config->speed == ETH_SPEED_10M) ||
	    (config->speed == ETH_SPEED_100M) ||
	    (config->speed == ETH_SPEED_1000M)) {
		cfg->ifSpeedSel = config->speed;
		cfg->fullDuplex = config->duplex;
	} else {
		cfg->ifSpeedSel = ETH_SPEED_100M;
		cfg->fullDuplex = 1;
	}

	if (CDN_EOK != (result = emacObj[id]->probe(cfg, req))) {
		printf("Invalid return value: %d\n", result);
		return -1;
	}
	if (0 != (result = allocSysReqMem(id, req, cfg))) {
		printf("Error in allocSysReqMem: returned %d\n", result);
		return -1;
	}
	/* if PCS is present, must test using TBI as wrapper is configured differently
	 * (but don't override SGMII if that is selected)
	 */
	if ((0 == EMAC_REGS__DESIGNCFG_DEBUG1__NO_PCS__READ(CPS_UncachedRead32(
			  &(((struct emac_regs *)emac_reg_base[id])
				    ->designcfg_debug1)))) &&
	    ((cfg->ifTypeSel == CEDI_IFSP_MII) ||
	     (cfg->ifTypeSel == CEDI_IFSP_GMII))) {
		cfg->ifTypeSel = CEDI_IFSP_BASE_X;
		cfg->ifSpeedSel = CEDI_SPEED_1000M;
	}

	if (CDN_EOK !=
	    (result = emacObj[id]->init(privData[id], cfg, &core_callbacks))) {
		printf("Error in emacObj%u->init: returned %d\n", id, result);
		return -1;
	}
#if !defined(CSP) && !defined(BIG_CONF)
	/* check if PCS is selected */
	if (EMAC_REGS__NETWORK_CONFIG__PCS_SELECT__READ(
		    CPS_UncachedRead32(regAddr(id, network_config)))) {
		printf("Not available when in PCS mode");
		return -1;
	}
#endif

	if (config->enable_emac == ETH_EMAC_ENABLE) {
		if (privData[id]->cfg.incExpressTraffic == 0) {
			printf("Interspersing Express Traffic is not available or not enabled\n");
			return -1;
		}
		memset(dev->eMacPrivData[id], 0, sizeof(CEDI_PrivateData));
		result = emacObj[id]->getEmac(privData[id],
					      (void *)&dev->eMacPrivData[id]);
		if (result != CDN_EOK) {
			printf("Could not get eMAC private data\n");
			return -1;
		}
	}

	/* jumbo frame */
	if (config->jumbo_en == ETH_JUMBO_ENABLE) {
		emacObj[id]->setJumboFramesRx(privData[id], true);
		if (CDN_EOK !=
		    (result = emacObj[id]->setJumboFrameRxMaxLen(
			     privData[id], MAX_JUMBO_FRAME_LENGTH))) {
			printf("Invalid return value: %d\n", result);
			return -1;
		}

		emacObj[id]->setTxQueueSegAlloc(privData[id], &queueSegAlloc);
		/* expand jumbo frame length and max length is 16287(16175 + 14 * 8). */
		if (id == ETH0) {
			val = readl(EMAC_REG_BASE_ADDRESS0 +
				    JUMBO_TX_FULL_THRESH0_REG);
			val &= ~(0xff << 16);
			val &= ~(0xff << 0);
			writel(val, EMAC_REG_BASE_ADDRESS0 +
					    JUMBO_TX_FULL_THRESH0_REG);
		} else if (id == ETH1) {
			val = readl(EMAC_REG_BASE_ADDRESS1 +
				    JUMBO_TX_FULL_THRESH0_REG);
			val &= ~(0xff << 16);
			val &= ~(0xff << 0);
			writel(val, EMAC_REG_BASE_ADDRESS1 +
					    JUMBO_TX_FULL_THRESH0_REG);
		} else if (id == ETH2) {
			val = readl(EMAC_REG_BASE_ADDRESS2 +
				    JUMBO_TX_FULL_THRESH0_REG);
			val &= ~(0xff << 16);
			val &= ~(0xff << 0);
			writel(val, EMAC_REG_BASE_ADDRESS2 +
					    JUMBO_TX_FULL_THRESH0_REG);
		} else {
			val = readl(EMAC_REG_BASE_ADDRESS3 +
				    JUMBO_TX_FULL_THRESH0_REG);
			val &= ~(0xff << 16);
			val &= ~(0xff << 0);
			writel(val, EMAC_REG_BASE_ADDRESS3 +
					    JUMBO_TX_FULL_THRESH0_REG);
		}
	}

	zeroCallbackCounters();

	/* how many priority Rx queues there are. */
	if (config->jumbo_en == ETH_JUMBO_ENABLE) {
		prio_queue_nums = JUMBO_HW_PRIO_QUE_NUMS;
	} else {
#if defined(CONFIG_COMPILE_FPGA) || defined(CONFIG_COMPILE_ASIC)
		if (config->enable_emac == ETH_EMAC_ENABLE)
			prio_queue_nums = EMAC_HW_PRIO_QUE_NUMS;
		else
			prio_queue_nums = cfgHwQs(id);
#elif defined(CONFIG_COMPILE_RTL)
		prio_queue_nums = HW_PRIO_QUE_NUMS;
#endif
	}

	for (i = 0; i < prio_queue_nums; i++) {
		if (config->enable_emac == ETH_EMAC_ENABLE)
			buf_len_bytes =
				dev->eMacPrivData[id]->cfg.rxBufLength[i] << 6;
		else
			buf_len_bytes = privData[id]->cfg.rxBufLength[i] << 6;
		for (j = 0; j < r_q_size; j++) {
			result = allocBuffer(buf_len_bytes, 0xFAFA0000,
					     &aBuf[i][j]);
			if (result != CDN_EOK) {
				printf("Allocating Rx buffer [%u] failed\n", j);
				return -1;
			}
			if (config->enable_emac == ETH_EMAC_ENABLE)
				result = emacObj[id]->addRxBuf(
					dev->eMacPrivData[id], i, &aBuf[i][j],
					0);
			else
				result = emacObj[id]->addRxBuf(privData[id], i,
							       &aBuf[i][j], 0);
			if (result != CDN_EOK) {
				printf("addRxBuf failed\n");
				return -1;
			}

			result = allocBuffer(buf_len_bytes, 0xABCD0000,
					     &nBuf[i][j]);
			if (result != CDN_EOK) {
				printf("allocating new Rx buffer\[\%u]\n", i);
				return 0;
			}
		}
	}

	if (config->mode == ETH_MODE_LOCAL_LOOPBACK) {
		/* enable local loopback mode */
		if (config->enable_emac == ETH_EMAC_ENABLE)
			result = emacObj[id]->setLoopback(dev->eMacPrivData[id],
							  CEDI_LOCAL_LOOPBACK);

		result = emacObj[id]->setLoopback(privData[id],
						  CEDI_LOCAL_LOOPBACK);
		if (result == CDN_ENOTSUP) {
			printf("local loopback is not available\n");
			return -1;
		}
	} else if (config->mode == ETH_MODE_SERDES_LOOPBACK) {
		/* enable serdes loopback mode */
		result = emacObj[id]->setLoopback(privData[id],
						  CEDI_SERDES_LOOPBACK);
		if (result == CDN_ENOTSUP) {
			printf("serdes loopback is not available\n");
			return -1;
		}
	}

	if (config->enable_emac == ETH_EMAC_ENABLE) {
		emacObj[id]->setCopyAllFrames(dev->eMacPrivData[id], 1);
		emacObj[id]->setRxBadPreamble(dev->eMacPrivData[id], 1);
		emacObj[id]->setIgnoreFcsRx(dev->eMacPrivData[id], 1);
		emacObj[id]->setEventEnable(dev->eMacPrivData[id],
					    CEDI_EVSET_ALL_Q0_EVENTS, 0, 0);
	} else {
		emacObj[id]->setCopyAllFrames(privData[id], 1);
		emacObj[id]->setFcsRemove(privData[id], 1);
	}

	if (config->enable_emac == ETH_EMAC_ENABLE) {
		/* Initiate MMSL */
		preCfg.routeRxToPmac = 0;
		preCfg.enPreeption = 1;
		preCfg.enVerify = 0;
		preCfg.addFragSize = CEDI_FRAG_SIZE_64;
		result =
			emacObj[id]->setPreemptionConfig(privData[id], &preCfg);
		if (result != CDN_EOK) {
			printf("Error configuring MMSL layer on eth%d\n", id);
			return -1;
		}
	}

	if (cfg)
		free(cfg);
	if (req)
		free(req);
	return 0;
}

void eth_lowlevel_free(eth_device *dev)
{
	int id = dev->config->id;
	int i, j;
	unsigned int prio_queue_nums = 0;
	unsigned int r_q_size = NORMAL_RXQ_SIZE;
	CEDI_PreemptionConfig preCfg;

	emacObj[id]->stop(privData[id]);

	if (dev->config->enable_emac == ETH_EMAC_ENABLE) {
		/* reset MMSL config */
		preCfg.routeRxToPmac = 1;
		preCfg.enPreeption = 0;
		emacObj[id]->setPreemptionConfig(privData[id], &preCfg);
	}

	if (dev->config->jumbo_en == ETH_JUMBO_ENABLE)
		r_q_size = JUMBO_RXQ_SIZE;

#if defined(CONFIG_COMPILE_FPGA) || defined(CONFIG_COMPILE_ASIC)
	if (dev->config->enable_emac == ETH_EMAC_ENABLE)
		prio_queue_nums = EMAC_HW_PRIO_QUE_NUMS;
	else
		prio_queue_nums = cfgHwQs(id);
#elif defined(CONFIG_COMPILE_RTL)
	prio_queue_nums = HW_PRIO_QUE_NUMS;
#endif
	for (i = 0; i < prio_queue_nums; i++) {
		for (j = 0; j < r_q_size; j++) {
			NCPS_freeHWMem(nBuf[i][j].vAddr);
			nBuf[i][j].vAddr = 0;
			NCPS_freeHWMem(aBuf[i][j].vAddr);
			aBuf[i][j].vAddr = 0;
		}
	}

	if (emacObj[id])
		emacObj[id]->destroy(privData[id]);

	if (privData[id])
		free(privData[id]);

	privData[id] = NULL;

	if (statRegs[id])
		free(statRegs[id]);

	statRegs[id] = NULL;
}

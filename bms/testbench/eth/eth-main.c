#include <common.h>
#include <command.h>
#include <testbench.h>
#include <malloc.h>
#include <getopt.h>
#include <eth.h>
#include <phy.h>
#include <cache.h>

#if defined(CONFIG_COMPILE_FPGA) || defined(CONFIG_COMPILE_ASIC)
#define ETH_TEST_LEN 1500
#elif defined(CONFIG_COMPILE_RTL)
#define ETH_TEST_LEN 64
#endif

#define ETH_JUMBO_TEST_LEN 16287
#define ETH_RMII_JUMBO_TEST_LEN 10240

#define MAX_PHASE_MODULATION_TIMES 400

#ifdef CONFIG_COMPILE_ASIC
#define MAX_DLY_LINE 255

#define DLY_LINE_1000M_TIMEOUTS 3
#define DLY_LINE_1000M_INTERVAL 1

#define DLY_LINE_100M_TIMEOUTS 13
#define DLY_LINE_100M_INTERVAL 1

#define DLY_LINE_10M_TIMEOUTS 130
#define DLY_LINE_10M_INTERVAL 13

#define DLY_LINE_TEST_LEN 64

#define RX_WINDOW_MIN_CNT 3
#endif

typedef struct {
	unsigned char dst_mac[6];
	unsigned char src_mac[6];
	unsigned char type_len_msb;
	unsigned char type_len_lsb;
} mac_frame_header;

typedef enum {
	CASE_UNDEFINED = 0,
	ETH_TEST,
	LOOPBACK_TEST,
	INTERACTION_TEST,
	FILTER_MAC_TEST,
	JUMBO_TEST,
	ETH_EMAC_TEST,
	PHY_WOL_TEST,
	MAC_MDIO_TEST
} eth_test_case;

volatile int enable_mdio_test = 0;
volatile int is_inter_connect = 1;

#ifdef CONFIG_COMPILE_ASIC
extern void mac_find_delay_line(int id, int txpaddly, int rxdly);
#else
extern void mac_find_txdly_window(int id, int times);
#endif

static void eth_show_usage(void)
{
	printf("Usage: uart [OPTION]...\n\n");
	printf("-h, \t\tcommand help.\n");
	printf("-s0,\t\t10M DMA test\n");
	printf("-s1,\t\t100M DMA test\n");
	printf("-s2,\t\t1000M DMA test\n");
	printf("-lo,\t\tloopback test\n");
	printf("-in,\t\tinteraction test, communicate with pc\n");
	printf("-ft,\t\tfilter mac address test\n");
	printf("-j,\t\tjumbo fram test\n");
}

static int make_ptp_packet(unsigned char *buf, unsigned char *src_mac,
			   unsigned char *dst_mac, unsigned short len)
{
	mac_frame_header header;
	unsigned short type_len = len - sizeof(header);
	int i;

	memcpy(header.dst_mac, dst_mac, 6);
	memcpy(header.src_mac, src_mac, 6);
	header.type_len_msb = (type_len & 0xff00) >> 8;
	header.type_len_lsb = type_len & 0x00ff;

	memcpy(buf, (unsigned char *)&header, sizeof(header));
	for (i = 0; i < type_len; i++)
		buf[sizeof(header) + i] = i;
	return 0;
}

static int make_broadcast_packet(unsigned char *buf, unsigned char *src_mac,
				 unsigned short len)
{
	unsigned char dst_mac[6] = { 0xff, 0xff, 0xff, 0xff, 0xff, 0xff };
	mac_frame_header header;
	unsigned short type_len = len - sizeof(header);
	int i;

	memcpy(header.dst_mac, dst_mac, 6);
	memcpy(header.src_mac, src_mac, 6);
	header.type_len_msb = (type_len & 0xff00) >> 8;
	header.type_len_lsb = type_len & 0x00ff;

	memcpy(buf, (unsigned char *)&header, sizeof(header));
	for (i = 0; i < type_len; i++)
		buf[sizeof(header) + i] = i;
	return 0;
}

static int eth_loopback_test(eth_id id, eth_interface interface, bool emac,
			     bool ext_ref_clk)
{
	eth_config config = { ETH0,
			      ETH_SPEED_1000M,
			      ETH_MODE_LOCAL_LOOPBACK,
			      ETH_FULL_DUPLEX,
			      ETH_JUMBO_DISABLE,
			      ETH_AUTO_NEGOTIATION_DISABLE,
			      ETH_RGMII,
			      ETH_EMAC_DISABLE,
			      PHY_LOOPBACK_DISABLE,
			      RMII_INT_REF_CLK,
			      PHY_WOL_DISABLE };
	eth_device *dev;
	int i, ret;
	unsigned char *rx_buf = NULL;
	unsigned char *tx_buf = NULL;

	config.id = id;
	if (interface == ETH_RMII) {
		config.speed = ETH_SPEED_100M;
		config.interface = ETH_RMII;
		if (ext_ref_clk)
			config.ext_ref_clk = RMII_EXT_REF_CLK;
	}

#if defined(CONFIG_C920) && \
	(defined(CONFIG_TB_RUN_DDR) || defined(CONFIG_TB_RUN_DDR1))
	if (config.id == ETH3) {
		rx_buf = (unsigned char *)gmac3_mem_alloc();
		tx_buf = (unsigned char *)gmac3_mem_alloc();
	} else {
		rx_buf = malloc(ETH_TEST_LEN);
		tx_buf = malloc(ETH_TEST_LEN);
	}
#else
	rx_buf = malloc(ETH_TEST_LEN);
	tx_buf = malloc(ETH_TEST_LEN);
#endif
	if (!rx_buf || !tx_buf) {
		printf("malloc failed!\n");
		return -1;
	}
	memset(rx_buf, 0, ETH_TEST_LEN);
	memset(tx_buf, 0, ETH_TEST_LEN);

	if (emac) {
		config.enable_emac = ETH_EMAC_ENABLE;
		printf("eth emac loopback test\n");
	} else {
		printf("eth loopback test\n");
	}
	printf("test len: %d\n", ETH_TEST_LEN);

	for (i = 0; i < ETH_TEST_LEN; i++)
		tx_buf[i] = i;

	dev = itcs_eth_init(&config);
	if (!dev) {
		printf("eth init failed!\n");
		return -1;
	}

	itcs_eth_recv(dev, rx_buf, ETH_TEST_LEN, NONBLOCK);
	itcs_eth_send(dev, tx_buf, ETH_TEST_LEN, NONBLOCK);

	while (1) {
		if (itcs_eth_is_completed(dev, ETH_RX_CHECK)) {
#if defined(CONFIG_COMPILE_RTL) || defined(CONFIG_COMPILE_ASIC)
			itcs_dcache_flush();
#endif
			if (!memcmp(tx_buf, rx_buf, ETH_TEST_LEN)) {
				if (emac)
					printf("Test ETH emac loopback Pass\n");
				else
					printf("Test ETH loopback Pass\n");
				ret = 0;
				goto exit;
			} else {
				if (emac)
					printf("Test ETH emac loopback Failed!\n");
				else
					printf("Test ETH loopback Failed!\n");
				ret = -1;
				goto exit;
			}
		}
	}
exit:
	itcs_eth_exit(dev);
#if defined(CONFIG_C920) && \
	(defined(CONFIG_TB_RUN_DDR) || defined(CONFIG_TB_RUN_DDR1))
	if (config.id != ETH3) {
		free(rx_buf);
		free(tx_buf);
	}
#else
	free(rx_buf);
	free(tx_buf);
#endif
	return ret;
}

static int eth_test(int group, eth_speed speed, int len, bool jumbo_enable,
		    eth_interface interface, bool enable_emac, bool ext_ref_clk)
{
	eth_config config_0 = { ETH0,
				ETH_SPEED_10M,
				ETH_MODE_NORMAL,
				ETH_FULL_DUPLEX,
				ETH_JUMBO_DISABLE,
				ETH_AUTO_NEGOTIATION_DISABLE,
				ETH_RGMII,
				ETH_EMAC_DISABLE,
				PHY_LOOPBACK_DISABLE,
				RMII_INT_REF_CLK,
				PHY_WOL_DISABLE };
	eth_config config_1 = { ETH1,
				ETH_SPEED_10M,
				ETH_MODE_NORMAL,
				ETH_FULL_DUPLEX,
				ETH_JUMBO_DISABLE,
				ETH_AUTO_NEGOTIATION_DISABLE,
				ETH_RGMII,
				ETH_EMAC_DISABLE,
				PHY_LOOPBACK_DISABLE,
				RMII_INT_REF_CLK,
				PHY_WOL_DISABLE };
	eth_device *dev0;
	eth_device *dev1;
	int eth0_pass = 0;
	int eth1_pass = 0;
	unsigned char src_mac0[6] = { 0x64, 0x00, 0x01, 0x02, 0x03, 0x04 };
	unsigned char src_mac1[6] = { 0x64, 0x00, 0x01, 0x02, 0x03, 0x05 };
	int real_speed = 0;
	int ret = 0;

	unsigned char *eth0_rx_buf = NULL;
	unsigned char *eth0_tx_buf = NULL;
	unsigned char *eth1_rx_buf = NULL;
	unsigned char *eth1_tx_buf = NULL;
	unsigned char *eth0_jumbo_rx_buf = NULL;
	unsigned char *eth0_jumbo_tx_buf = NULL;
	unsigned char *eth1_jumbo_rx_buf = NULL;
	unsigned char *eth1_jumbo_tx_buf = NULL;

	if (group == 1) {
		config_0.id = ETH2;
		config_1.id = ETH3;
	}

	if (enable_emac) {
		config_0.enable_emac = ETH_EMAC_ENABLE;
		config_1.enable_emac = ETH_EMAC_ENABLE;
	}

	if (interface == ETH_RMII) {
#if defined(CONFIG_COMPILE_FPGA) || defined(CONFIG_COMPILE_ASIC)
		if (jumbo_enable) {
			printf("lan8742ai does't support jumbo frame\n");
			return -1;
		}
#endif
		config_0.interface = ETH_RMII;
		config_1.interface = ETH_RMII;
		if (ext_ref_clk) {
			config_0.ext_ref_clk = RMII_EXT_REF_CLK;
			config_1.ext_ref_clk = RMII_EXT_REF_CLK;
#if defined(CONFIG_COMPILE_RTL) || defined(CONFIG_COMPILE_ASIC)
		} else {
			if (group == 1) {
				config_0.ext_ref_clk = RMII_EXT_REF_CLK;
				config_1.ext_ref_clk = RMII_INT_REF_CLK;
			}
#endif
		}
	}

	if (speed == ETH_SPEED_10M) {
		real_speed = ETH_SPEED_10;
	} else if (speed == ETH_SPEED_100M) {
		real_speed = ETH_SPEED_100;
	} else if (speed == ETH_SPEED_1000M) {
		real_speed = ETH_SPEED_1000;
	} else {
		printf("unsupported speed!\n");
		return -1;
	}

	/* 
	 * for e906 cache mode, send and recv buffer must be allocated from malloc. Because it is uncachable.
	 * Global array like "unsigned char eth0_jumbo_rx_buf[16287] = { 0 };" should not be used.
	 */
	if (jumbo_enable) {
		eth0_jumbo_rx_buf = malloc(len);
		eth0_jumbo_tx_buf = malloc(len);
#if defined(CONFIG_C920) && \
	(defined(CONFIG_TB_RUN_DDR) || defined(CONFIG_TB_RUN_DDR1))
		if (config_1.id == ETH3) {
			eth1_jumbo_rx_buf = gmac3_mem_alloc();
			eth1_jumbo_tx_buf = gmac3_mem_alloc();
		} else {
			eth1_jumbo_rx_buf = malloc(len);
			eth1_jumbo_tx_buf = malloc(len);
		}
#else
		eth1_jumbo_rx_buf = malloc(len);
		eth1_jumbo_tx_buf = malloc(len);
#endif
		if (!eth0_jumbo_rx_buf || !eth0_jumbo_tx_buf ||
		    !eth1_jumbo_rx_buf || !eth1_jumbo_tx_buf) {
			printf("jumbo send recv buf malloc failed\n");
			return -1;
		}
#if defined(CONFIG_COMPILE_FPGA) || defined(CONFIG_COMPILE_ASIC)
		memset(eth0_jumbo_rx_buf, 0, len);
		memset(eth0_jumbo_tx_buf, 0, len);
		memset(eth1_jumbo_rx_buf, 0, len);
		memset(eth1_jumbo_tx_buf, 0, len);
#endif
		config_0.jumbo_en = ETH_JUMBO_ENABLE;
		config_1.jumbo_en = ETH_JUMBO_ENABLE;
		printf("ETH %dM DMA Jumbo Frame test\n", real_speed);
	} else {
		eth0_rx_buf = malloc(len);
		eth0_tx_buf = malloc(len);
#if defined(CONFIG_C920) && \
	(defined(CONFIG_TB_RUN_DDR) || defined(CONFIG_TB_RUN_DDR1))
		if (config_1.id == ETH3) {
			eth1_rx_buf = gmac3_mem_alloc();
			eth1_tx_buf = gmac3_mem_alloc();
		} else {
			eth1_rx_buf = malloc(len);
			eth1_tx_buf = malloc(len);
		}
#else
		eth1_rx_buf = malloc(len);
		eth1_tx_buf = malloc(len);
#endif
		if (!eth0_rx_buf || !eth0_tx_buf || !eth1_rx_buf ||
		    !eth1_tx_buf) {
			printf("send recv buf malloc failed\n");
			return -1;
		}
#if defined(CONFIG_COMPILE_FPGA) || defined(CONFIG_COMPILE_ASIC)
		memset(eth0_rx_buf, 0, len);
		memset(eth0_tx_buf, 0, len);
		memset(eth1_rx_buf, 0, len);
		memset(eth1_tx_buf, 0, len);
#endif
		if (enable_emac)
			printf("ETH emac %dM DMA test\n", real_speed);
		else
			printf("ETH %dM DMA test\n", real_speed);
	}
	printf("test len: %d\n", len);
	config_0.speed = speed;
	config_1.speed = speed;
	if (jumbo_enable) {
		make_broadcast_packet(eth0_jumbo_tx_buf, src_mac0, len);
		make_broadcast_packet(eth1_jumbo_tx_buf, src_mac1, len);
	} else {
		make_broadcast_packet(eth0_tx_buf, src_mac0, len);
		make_broadcast_packet(eth1_tx_buf, src_mac1, len);
	}

	dev0 = itcs_eth_init(&config_0);
	if (!dev0) {
		printf("eth%d init failed!\n", config_0.id);
		ret = -1;
		goto exit_eth0;
	}
	dev1 = itcs_eth_init(&config_1);
	if (!dev1) {
		printf("eth%d init failed!\n", config_1.id);
		ret = -1;
		goto exit_eth1;
	}

	itcs_eth_set_mac_addr(dev0, (mac_addr *)src_mac0);
	itcs_eth_set_mac_addr(dev1, (mac_addr *)src_mac1);

#if defined(CONFIG_COMPILE_FPGA) || defined(CONFIG_COMPILE_ASIC)
	if (itcs_eth_phy_init(dev0) == -1) {
		printf("phy1 init failed!\n");
		ret = -1;
		goto exit_all;
	}
	if (itcs_eth_phy_init(dev1) == -1) {
		printf("phy2 init failed!\n");
		ret = -1;
		goto exit_all;
	}
#endif

	if (jumbo_enable) {
		itcs_eth_recv(dev0, eth0_jumbo_rx_buf, len, NONBLOCK);
		itcs_eth_recv(dev1, eth1_jumbo_rx_buf, len, NONBLOCK);

		itcs_eth_send(dev0, eth0_jumbo_tx_buf, len, NONBLOCK);
#ifndef CONFIG_COMPILE_ASIC
		/* avoid interrupt destroying next dcache flush in rtl. */
		udelay(25);
#endif
		itcs_eth_send(dev1, eth1_jumbo_tx_buf, len, NONBLOCK);
	} else {
		itcs_eth_recv(dev0, eth0_rx_buf, len, NONBLOCK);
		itcs_eth_recv(dev1, eth1_rx_buf, len, NONBLOCK);
		itcs_eth_send(dev0, eth0_tx_buf, len, NONBLOCK);
#ifndef CONFIG_COMPILE_ASIC
		/* avoid interrupt destroying next dcache flush in rtl. */
		udelay(25);
#endif
		itcs_eth_send(dev1, eth1_tx_buf, len, NONBLOCK);
	}

	while (1) {
		if (itcs_eth_is_completed(dev0, ETH_RX_CHECK)) {
#if defined(CONFIG_COMPILE_RTL) || defined(CONFIG_COMPILE_ASIC)
			itcs_dcache_flush();
#endif
			if (!eth0_pass) {
				if (jumbo_enable) {
					if (!memcmp(eth1_jumbo_tx_buf,
						    eth0_jumbo_rx_buf, len)) {
						eth0_pass = 1;
					} else {
						printf("Test ETH phase 0 %dM DMA Mode Failed! eth%d->eth%d\n",
						       real_speed, config_1.id,
						       config_0.id);
						ret = -1;
						goto exit_all;
					}
				} else {
					if (!memcmp(eth1_tx_buf, eth0_rx_buf,
						    len)) {
						eth0_pass = 1;
					} else {
						if (enable_emac)
							printf("Test ETH emac phase 0 %dM DMA Mode Failed! eth%d->eth%d\n",
							       real_speed,
							       config_1.id,
							       config_0.id);
						else
							printf("Test ETH phase 0 %dM DMA Mode Failed! eth%d->eth%d\n",
							       real_speed,
							       config_1.id,
							       config_0.id);
						ret = -1;
						goto exit_all;
					}
				}
			}
		}
		if (itcs_eth_is_completed(dev1, ETH_RX_CHECK)) {
#if defined(CONFIG_COMPILE_RTL) || defined(CONFIG_COMPILE_ASIC)
			itcs_dcache_flush();
#endif
			if (!eth1_pass) {
				if (jumbo_enable) {
					if (!memcmp(eth0_jumbo_tx_buf,
						    eth1_jumbo_rx_buf, len)) {
						eth1_pass = 1;
					} else {
						printf("Test ETH phase 1 %dM DMA Mode Failed! eth%d->eth%d\n",
						       real_speed, config_0.id,
						       config_1.id);
						ret = -1;
						goto exit_all;
					}
				} else {
					if (!memcmp(eth0_tx_buf, eth1_rx_buf,
						    len)) {
						eth1_pass = 1;
					} else {
						if (enable_emac)
							printf("Test ETH emac phase 1 %dM DMA Mode Failed! eth%d->eth%d\n",
							       real_speed,
							       config_0.id,
							       config_1.id);
						else
							printf("Test ETH phase 1 %dM DMA Mode Failed! eth%d->eth%d\n",
							       real_speed,
							       config_0.id,
							       config_1.id);
						ret = -1;
						goto exit_all;
					}
				}
			}
		}
		if (eth0_pass && eth1_pass) {
			if (jumbo_enable) {
				printf("Test ETH Jumbo Frame Pass\n");
			} else {
				if (enable_emac)
					printf("Test ETH emac %dM DMA Mode Pass\n",
					       real_speed);
				else
					printf("Test ETH %dM DMA Mode Pass\n",
					       real_speed);
			}
			ret = 0;
			goto exit_all;
		}
	}
exit_all:
	itcs_eth_exit(dev1);
exit_eth1:
	itcs_eth_exit(dev0);
exit_eth0:
	if (jumbo_enable) {
		free(eth0_jumbo_rx_buf);
		free(eth0_jumbo_tx_buf);
	} else {
		free(eth0_rx_buf);
		free(eth0_tx_buf);
	}
#if defined(CONFIG_C920) && \
	(defined(CONFIG_TB_RUN_DDR) || defined(CONFIG_TB_RUN_DDR1))
	if (config_1.id != ETH3) {
		if (jumbo_enable) {
			free(eth1_jumbo_rx_buf);
			free(eth1_jumbo_tx_buf);
		} else {
			free(eth1_rx_buf);
			free(eth1_tx_buf);
		}
	}
#else
	if (jumbo_enable) {
		free(eth1_jumbo_rx_buf);
		free(eth1_jumbo_tx_buf);
	} else {
		free(eth1_rx_buf);
		free(eth1_tx_buf);
	}
#endif
	return ret;
}

static int filter_test(eth_id id, eth_interface interface, bool ext_ref_clk)
{
	eth_config config_0 = { ETH0,
				ETH_SPEED_100M,
				ETH_MODE_NORMAL,
				ETH_FULL_DUPLEX,
				ETH_JUMBO_DISABLE,
				ETH_AUTO_NEGOTIATION_DISABLE,
				ETH_RGMII,
				ETH_EMAC_DISABLE,
				PHY_LOOPBACK_DISABLE,
				RMII_INT_REF_CLK,
				PHY_WOL_DISABLE };
	eth_config config_1 = { ETH1,
				ETH_SPEED_100M,
				ETH_MODE_NORMAL,
				ETH_FULL_DUPLEX,
				ETH_JUMBO_DISABLE,
				ETH_AUTO_NEGOTIATION_DISABLE,
				ETH_RGMII,
				ETH_EMAC_DISABLE,
				PHY_LOOPBACK_DISABLE,
				RMII_INT_REF_CLK,
				PHY_WOL_DISABLE };
	eth_device *dev = NULL;
	eth_device *dev0 = NULL;
	eth_device *dev1 = NULL;
	int pass_0 = 0;
	int pass_1 = 0;
	unsigned char src_mac0[6] = { 0x64, 0x00, 0x01, 0x02, 0x03, 0x04 };
	unsigned char src_mac1[6] = { 0x64, 0x00, 0x01, 0x02, 0x03, 0x05 };
	unsigned char other_mac[6] = { 0x64, 0x00, 0x01, 0x02, 0x03, 0x06 };
	int ret = 0;
	unsigned char *rx_buf = NULL;
	unsigned char *tx_buf_0 = NULL;
	unsigned char *tx_buf_1 = NULL;
	int len = ETH_TEST_LEN;
	unsigned long timeouts = 0, expected_timeouts = 0;

	if (id > ETH1) {
		config_0.id = ETH2;
		config_1.id = ETH3;
	}

	if (interface == ETH_RMII) {
		config_0.speed = ETH_SPEED_10M;
		config_0.interface = ETH_RMII;
		config_1.speed = ETH_SPEED_10M;
		config_1.interface = ETH_RMII;
		if (ext_ref_clk) {
			config_0.ext_ref_clk = RMII_EXT_REF_CLK;
			config_1.ext_ref_clk = RMII_EXT_REF_CLK;
#if defined(CONFIG_COMPILE_RTL) || defined(CONFIG_COMPILE_ASIC)
		} else {
			if (id > ETH1) {
				config_0.ext_ref_clk = RMII_EXT_REF_CLK;
				config_1.ext_ref_clk = RMII_INT_REF_CLK;
			}
#endif
		}
	}

	printf("eth filter test\n");
	printf("test len: %d\n", len);

#if defined(CONFIG_C920) && \
	(defined(CONFIG_TB_RUN_DDR) || defined(CONFIG_TB_RUN_DDR1))
	if (id == ETH2) {
		rx_buf = malloc(len);
		tx_buf_0 = gmac3_mem_alloc();
		tx_buf_1 = gmac3_mem_alloc();
	} else if (id == ETH3) {
		rx_buf = gmac3_mem_alloc();
		tx_buf_0 = malloc(len);
		tx_buf_1 = malloc(len);
	} else {
		rx_buf = malloc(len);
		tx_buf_0 = malloc(len);
		tx_buf_1 = malloc(len);
	}
#else
	rx_buf = malloc(len);
	tx_buf_0 = malloc(len);
	tx_buf_1 = malloc(len);
#endif
	if (!rx_buf || !tx_buf_0 || !tx_buf_1) {
		printf("malloc failed!\n");
		return -1;
	}
#if defined(CONFIG_COMPILE_FPGA) || defined(CONFIG_COMPILE_ASIC)
	memset(rx_buf, 0, len);
	memset(tx_buf_0, 0, len);
	memset(tx_buf_1, 0, len);
#endif

	make_ptp_packet(tx_buf_0, src_mac1, src_mac0, len);
	make_ptp_packet(tx_buf_1, src_mac1, other_mac, len);

	dev0 = itcs_eth_init(&config_0);
	if (!dev0) {
		printf("eth0 init failed!\n");
		ret = -1;
		goto exit_eth0;
	}
	dev1 = itcs_eth_init(&config_1);
	if (!dev1) {
		printf("eth1 init failed!\n");
		ret = -1;
		goto exit_eth1;
	}

	itcs_eth_set_mac_addr(dev0, (mac_addr *)src_mac0);
	itcs_eth_set_mac_addr(dev1, (mac_addr *)src_mac1);

#if defined(CONFIG_COMPILE_FPGA) || defined(CONFIG_COMPILE_ASIC)
	if (itcs_eth_phy_init(dev0) == -1) {
		printf("phy1 init failed!\n");
		ret = -1;
		goto exit_all;
	}
	if (itcs_eth_phy_init(dev1) == -1) {
		printf("phy2 init failed!\n");
		ret = -1;
		goto exit_all;
	}
#endif
	if (id == ETH1 || id == ETH3) {
		dev = dev1;
		dev1 = dev0;
		dev0 = dev;
		memset(tx_buf_0, 0, len);
		memset(tx_buf_1, 0, len);
		make_ptp_packet(tx_buf_0, src_mac0, src_mac1, len);
		make_ptp_packet(tx_buf_1, src_mac0, other_mac, len);
		itcs_eth_filter_mac_addr(dev0, (mac_addr *)src_mac1,
					 ETH_FILTER_DST, ETH_FILTER_ENABLE);
	} else {
		itcs_eth_filter_mac_addr(dev0, (mac_addr *)src_mac0,
					 ETH_FILTER_DST, ETH_FILTER_ENABLE);
	}

	itcs_eth_recv(dev0, rx_buf, len, NONBLOCK);
	itcs_eth_send(dev1, tx_buf_0, len, NONBLOCK);
	while (1) {
		udelay(10);
		expected_timeouts += 10;
		if (itcs_eth_is_completed(dev0, ETH_RX_CHECK)) {
#if defined(CONFIG_COMPILE_RTL) || defined(CONFIG_COMPILE_ASIC)
			itcs_dcache_flush();
#endif
			if (!memcmp(tx_buf_0, rx_buf, len)) {
				pass_0 = 1;
				break;
			} else {
				printf("Test ETH 100M DMA filter phase 0 Failed!\n");
				ret = -1;
				goto exit_all;
			}
		}
	}

	memset(rx_buf, 0, len);
	itcs_eth_recv(dev0, rx_buf, len, NONBLOCK);
	itcs_eth_send(dev1, tx_buf_1, len, NONBLOCK);
	while (1) {
		udelay(10);
		timeouts += 10;
		if (itcs_eth_is_completed(dev0, ETH_RX_CHECK)) {
			printf("Test ETH 100M DMA filter phase 1 Failed!\n");
			ret = -1;
			goto exit_all;
		} else {
			if (timeouts >= 2 * expected_timeouts) {
				pass_1 = 1;
				break;
			}
		}
	}

	if (pass_0 && pass_1) {
		printf("Test ETH MAC %d Filter Mode Pass\n", id);
		ret = 0;
		goto exit_all;
	} else {
		printf("Test ETH MAC %d Filter Mode Failed\n", id);
	}
exit_all:
	itcs_eth_exit(dev1);
exit_eth1:
	itcs_eth_exit(dev0);
exit_eth0:

#if defined(CONFIG_C920) && \
	(defined(CONFIG_TB_RUN_DDR) || defined(CONFIG_TB_RUN_DDR1))
	if (id == ETH2) {
		free(rx_buf);
	} else if (id == ETH3) {
		free(tx_buf_0);
		free(tx_buf_1);
	} else {
		free(rx_buf);
		free(tx_buf_0);
		free(tx_buf_1);
	}
#else
	free(rx_buf);
	free(tx_buf_0);
	free(tx_buf_1);
#endif
	return ret;
}

/* find window only for 1000m. */
static int eth_interaction_test(eth_id id, eth_interface interface,
				bool find_window, bool ext_ref_clk)
{
	eth_config config = { ETH0,
			      ETH_SPEED_100M,
			      ETH_MODE_NORMAL,
			      ETH_FULL_DUPLEX,
			      ETH_JUMBO_DISABLE,
			      ETH_AUTO_NEGOTIATION_DISABLE,
			      ETH_RGMII,
			      ETH_EMAC_DISABLE,
			      PHY_LOOPBACK_DISABLE,
			      RMII_INT_REF_CLK,
			      PHY_WOL_DISABLE };
	eth_device *dev = NULL;
	unsigned char src_mac[6] = { 0x64, 0x00, 0x01, 0x02, 0x03, 0x04 };
	int ret = 0;
	unsigned char *rx_buf = NULL;
	unsigned char *tx_buf = NULL;
	int len = ETH_TEST_LEN;
	unsigned long test_cnt = 1;
	unsigned long recv_cnt = 0;
	unsigned long tmp_cnt = test_cnt;
	int frm_mac_len = 2 * 6;
#ifndef CONFIG_COMPILE_ASIC
	int times = 0;
#endif
	int max_times = MAX_PHASE_MODULATION_TIMES;
	int cur_time = 0, timeouts = 20000;
#ifdef CONFIG_COMPILE_ASIC
	int delay_interval = 0;
	int i, j;
	volatile int is_interrupted;
	int locate, cur_max_cnt;
	int history_max_cnt;
	volatile int confirm_txdly = 0;
	int tx_delay = 0, rx_delay = 0;
	volatile int tmp_rx_max_cnt = 0;
#endif

	is_inter_connect = 0;

	config.id = id;
	if (find_window) {
		config.phy_loopback = PHY_LOOPBACK_ENABLE;
#ifdef CONFIG_COMPILE_ASIC
		max_times = MAX_DLY_LINE + 1;
		len = DLY_LINE_TEST_LEN;
		if (config.speed  == ETH_SPEED_1000M) {
			timeouts = DLY_LINE_1000M_TIMEOUTS;
			delay_interval = DLY_LINE_1000M_INTERVAL;
		} else if (config.speed  == ETH_SPEED_100M) {
			timeouts = DLY_LINE_100M_TIMEOUTS;
			delay_interval = DLY_LINE_100M_INTERVAL;
		} else if (config.speed  == ETH_SPEED_10M) {
			timeouts = DLY_LINE_10M_TIMEOUTS;
			delay_interval = DLY_LINE_10M_INTERVAL;
		}
#endif
	}

	if (interface == ETH_RMII) {
		config.speed = ETH_SPEED_100M;
		config.interface = ETH_RMII;
		if (ext_ref_clk)
			config.ext_ref_clk = RMII_EXT_REF_CLK;
	}

#if defined(CONFIG_C920) && \
	(defined(CONFIG_TB_RUN_DDR) || defined(CONFIG_TB_RUN_DDR1))
	if (config.id == ETH3) {
		rx_buf = gmac3_mem_alloc();
		tx_buf = gmac3_mem_alloc();
	} else {
		rx_buf = malloc(len);
		tx_buf = malloc(len);
	}
#else
	rx_buf = malloc(len);
	tx_buf = malloc(len);
#endif
	if (!rx_buf || !tx_buf) {
		printf("malloc failed!\n");
		return -1;
	}
	memset(rx_buf, 0, len);
	memset(tx_buf, 0, len);

	printf("eth interaction test\n");
	printf("test len: %d\n", len);

	make_broadcast_packet(tx_buf, src_mac, len);

	dev = itcs_eth_init(&config);
	if (!dev) {
		printf("eth init failed!\n");
		return -1;
	}
	itcs_eth_set_mac_addr(dev, (mac_addr *)src_mac);
	if (!find_window)
		itcs_eth_filter_mac_addr(dev, (mac_addr *)src_mac,
					 ETH_FILTER_DST, ETH_FILTER_ENABLE);

#if defined(CONFIG_COMPILE_FPGA) || defined(CONFIG_COMPILE_ASIC)
	if (itcs_eth_phy_init(dev) == -1) {
		printf("phy init failed!\n");
		ret = -1;
		goto exit;
	}
#endif

	if (find_window) {
#ifdef CONFIG_COMPILE_ASIC
		for (i = 0; i < max_times; i++) {
			is_interrupted = 1;
			cur_max_cnt = 0;
			locate = 0;
			history_max_cnt = 0;
			for (j = 0; j < max_times; j++) {
				if (confirm_txdly)
					mac_find_delay_line(id, j, rx_delay);
				else
					mac_find_delay_line(id, i, j);

				memset(rx_buf, 0, len);
				itcs_eth_recv(dev, rx_buf, len, NONBLOCK);
				itcs_eth_send(dev, tx_buf, len, BLOCK);
				cur_time = 0;
				while (cur_time <= timeouts) {
					udelay(delay_interval);
					cur_time += delay_interval;
					if (itcs_eth_is_completed(dev, ETH_RX_CHECK))
						break;
				}

				if (!memcmp(rx_buf, tx_buf, len)) {
					if (is_interrupted)
						cur_max_cnt = 1;
					else
						cur_max_cnt++;

					if (cur_max_cnt > history_max_cnt) {
						history_max_cnt = cur_max_cnt;
						locate = j;
					}
					is_interrupted = 0;
				} else {
					is_interrupted = 1;
				}
			}
			locate = locate - history_max_cnt / 2;
			if (confirm_txdly) {
				tx_delay = locate;
				break;
			} else if (history_max_cnt >= RX_WINDOW_MIN_CNT) {
				rx_delay = locate;
				tmp_rx_max_cnt = history_max_cnt;
				if (i == max_times - 1)
					i = 0;
				confirm_txdly = 1;
			}
		}
		if (i == max_times) {
			i = 0;
			printf("no window, txpaddly: %d, rxdly: %d\n", tx_delay,
			       rx_delay);
		} else {
			printf("tx and rx continuous cnt: %d, %d, tx and rx: %d, %d\n",
			       history_max_cnt, tmp_rx_max_cnt, tx_delay, rx_delay);
		}
#else
		while (1) {
			mac_find_txdly_window(id, times);
			test_cnt = tmp_cnt;
			recv_cnt = 0;
			while (test_cnt--) {
				memset(rx_buf, 0, len);
				itcs_eth_recv(dev, rx_buf, len, NONBLOCK);
				itcs_eth_send(dev, tx_buf, len, BLOCK);
				cur_time = 0;
				while (cur_time <= timeouts) {
					udelay(1);
					cur_time += 1;
					if (itcs_eth_is_completed(
						    dev, ETH_RX_CHECK)) {
						if (!memcmp(tx_buf +
								    frm_mac_len,
							    rx_buf +
								    frm_mac_len,
							    len - frm_mac_len)) {
							recv_cnt++;
							break;
						} else {
							continue;
						}
					}
				}
			}
			if (recv_cnt == tmp_cnt)
				printf("modulation times %d is ok\n", times);
			else
				printf("modulation times %d is failed!\n",
				       times);

			times++;
			if (times >= max_times)
				break;
		}
#endif
	} else {
		while (test_cnt--) {
#if defined(CONFIG_COMPILE_FPGA) || defined(CONFIG_COMPILE_ASIC)
			/* avoid pc can not receive data in multi transfer. */
			udelay(200000);
#endif
			memset(rx_buf, 0, len);
			itcs_eth_recv(dev, rx_buf, len, NONBLOCK);
			itcs_eth_send(dev, tx_buf, len, BLOCK);
			while (1) {
				if (itcs_eth_is_completed(dev, ETH_RX_CHECK)) {
					if (!memcmp(tx_buf + frm_mac_len,
						    rx_buf + frm_mac_len,
						    len - frm_mac_len)) {
						recv_cnt++;
						break;
					} else {
						//printf("wrong recv data\n");
						continue;
					}
				}
			}
		}
		if (recv_cnt == tmp_cnt)
			printf("Test ETH Connection With PC Pass\n");
		else
			printf("Test ETH Connection With PC Failed!\n");
	}
#if defined(CONFIG_COMPILE_FPGA) || defined(CONFIG_COMPILE_ASIC)
exit:
#endif
	itcs_eth_exit(dev);
#if defined(CONFIG_C920) && \
	(defined(CONFIG_TB_RUN_DDR) || defined(CONFIG_TB_RUN_DDR1))
	if (config.id != ETH3) {
		free(rx_buf);
		free(tx_buf);
	}
#else
	free(rx_buf);
	free(tx_buf);
#endif
	return ret;
}

static int eth_phy_wol_test(eth_id id, eth_interface interface,
			    bool ext_ref_clk)
{
	eth_config config = { ETH0,
			      ETH_SPEED_100M,
			      ETH_MODE_NORMAL,
			      ETH_FULL_DUPLEX,
			      ETH_JUMBO_DISABLE,
			      ETH_AUTO_NEGOTIATION_DISABLE,
			      ETH_RGMII,
			      ETH_EMAC_DISABLE,
			      PHY_LOOPBACK_DISABLE,
			      RMII_INT_REF_CLK,
			      PHY_WOL_DISABLE };
	eth_device *dev = NULL;
	unsigned char src_mac[6] = { 0x64, 0x00, 0x01, 0x02, 0x03, 0x04 };
	int ret = 0;

	config.id = id;
	if (interface == ETH_RMII) {
		config.speed = ETH_SPEED_100M;
		config.interface = ETH_RMII;
		config.phy_enable_wol = PHY_WOL_ENABLE;
		if (ext_ref_clk)
			config.ext_ref_clk = RMII_EXT_REF_CLK;
	}
	printf("eth phy wol test\n");

	dev = itcs_eth_init(&config);
	if (!dev) {
		printf("eth init failed!\n");
		return -1;
	}
	itcs_eth_set_mac_addr(dev, (mac_addr *)src_mac);
	itcs_eth_filter_mac_addr(dev, (mac_addr *)src_mac, ETH_FILTER_DST,
				 ETH_FILTER_ENABLE);

#if defined(CONFIG_COMPILE_FPGA) || defined(CONFIG_COMPILE_ASIC)
	if (itcs_eth_phy_init(dev) == -1) {
		printf("phy init failed!\n");
		ret = -1;
		goto exit;
	}
#endif
	printf("please check phy wol pin level\n");

#if defined(CONFIG_COMPILE_FPGA) || defined(CONFIG_COMPILE_ASIC)
exit:
#endif
	itcs_eth_exit(dev);
	return ret;
}

static int eth_mdio_test(eth_id id, eth_interface interface, bool ext_ref_clk)
{
	eth_config config = { ETH0,
			      ETH_SPEED_1000M,
			      ETH_MODE_NORMAL,
			      ETH_FULL_DUPLEX,
			      ETH_JUMBO_DISABLE,
			      ETH_AUTO_NEGOTIATION_DISABLE,
			      ETH_RGMII,
			      ETH_EMAC_DISABLE,
			      PHY_LOOPBACK_DISABLE,
			      RMII_INT_REF_CLK,
			      PHY_WOL_DISABLE };
	eth_device *dev = NULL;
	unsigned char src_mac[6] = { 0x64, 0x00, 0x01, 0x02, 0x03, 0x04 };
	int ret = 0;

	config.id = id;
	if (interface == ETH_RMII) {
		config.speed = ETH_SPEED_100M;
		config.interface = ETH_RMII;
		if (ext_ref_clk)
			config.ext_ref_clk = RMII_EXT_REF_CLK;
	}
	printf("eth mac mdio test\n");

	enable_mdio_test = 1;

	dev = itcs_eth_init(&config);
	if (!dev) {
		printf("eth init failed!\n");
		return -1;
	}
	itcs_eth_set_mac_addr(dev, (mac_addr *)src_mac);
	itcs_eth_filter_mac_addr(dev, (mac_addr *)src_mac, ETH_FILTER_DST,
				 ETH_FILTER_ENABLE);

	if (itcs_eth_phy_init(dev) == -1) {
		printf("phy init failed!\n");
		ret = -1;
		goto exit;
	}
	printf("eth mac mdio read & write Pass\n");
	enable_mdio_test = 0;
exit:
	itcs_eth_exit(dev);
	return ret;
}

int eth_main(int argc, char *argv[])
{
	int ret;
	eth_test_case test_case = CASE_UNDEFINED;
	int eth_index = ETH0;
	int speed = 0;
	eth_interface interface = ETH_RGMII;
	bool find_window = false;
	bool ext_ref_clk = true;
	int group = 0;

	itcs_pll_set_clock(CPU, "dpll", 1500000000, false);

	if (strncmp(argv[3], "-rmii", 5) == 0) {
		interface = ETH_RMII;
		if (!strncmp(argv[4], "int", 3))
			ext_ref_clk = false;
		else if (!strncmp(argv[4], "ext", 3))
			ext_ref_clk = true;
	} else if (strncmp(argv[3], "-rgmii", 6) == 0) {
		interface = ETH_RGMII;
	} else {
		if (strncmp(argv[1], "-j", 2) != 0) {
			printf("unsupported interface\n");
			return -1;
		}
	}

	if (!strncmp(argv[1], "-w", 2))
		test_case = PHY_WOL_TEST;
	else if (!strncmp(argv[1], "-m", 2))
		test_case = MAC_MDIO_TEST;

	if (strncmp(argv[1], "-s", 2) == 0 || strncmp(argv[1], "-e", 2) == 0) {
		if (strncmp(argv[1], "-e", 2) == 0) {
			test_case = ETH_EMAC_TEST;
			if (!strncmp(argv[2], "0", 1))
				group = 0;
			else
				group = 1;
		} else {
			test_case = ETH_TEST;
			if (!strncmp(argv[2], "0", 1)) {
				speed = ETH_SPEED_10M;
				group = 0;
			} else if (!strncmp(argv[2], "1", 1)) {
				speed = ETH_SPEED_100M;
				group = 0;
			} else if (!strncmp(argv[2], "2", 1)) {
				speed = ETH_SPEED_1000M;
				group = 0;
			} else if (!strncmp(argv[2], "3", 1)) {
				speed = ETH_SPEED_10M;
				group = 1;
			} else if (!strncmp(argv[2], "4", 1)) {
				speed = ETH_SPEED_100M;
				group = 1;
			} else if (!strncmp(argv[2], "5", 1)) {
				speed = ETH_SPEED_1000M;
				group = 1;
			} else {
				printf("input error!\n");
				return -1;
			}
		}
	} else if (argc == 4 || argc == 5) {
		if (!strncmp(argv[1], "-lo", 3)) {
			test_case = LOOPBACK_TEST;
		} else if (!strncmp(argv[1], "-in", 3)) {
			test_case = INTERACTION_TEST;
			if (!strncmp(argv[4], "-phase", 6))
				find_window = 1;
			else
				find_window = 0;
		} else if (!strncmp(argv[1], "-f", 2)) {
			test_case = FILTER_MAC_TEST;
		} else if (!strncmp(argv[1], "-j", 2)) {
			test_case = JUMBO_TEST;
			if (!strncmp(argv[2], "0", 1))
				group = 0;
			else if (!strncmp(argv[2], "1", 1))
				group = 1;
		}

		if (strncmp(argv[2], "0", 1) == 0) {
			eth_index = 0;
		} else if (strncmp(argv[2], "1", 1) == 0) {
			eth_index = 1;
		} else if (strncmp(argv[2], "2", 1) == 0) {
			eth_index = 2;
		} else if (strncmp(argv[2], "3", 1) == 0) {
			eth_index = 3;
		} else {
			printf("only support eth 0, 1, 2, 3!\n");
			return -1;
		}
	} else {
		test_case = CASE_UNDEFINED;
		eth_show_usage();
		return -1;
	}

	switch (test_case) {
	case ETH_TEST:
		ret = eth_test(group, speed, ETH_TEST_LEN, ETH_JUMBO_DISABLE,
			       interface, ETH_EMAC_DISABLE, ext_ref_clk);
		break;
	case JUMBO_TEST:
		if (interface == ETH_RMII)
			ret = eth_test(group, ETH_SPEED_100M,
				       ETH_RMII_JUMBO_TEST_LEN,
				       ETH_JUMBO_ENABLE, interface,
				       ETH_EMAC_DISABLE, ext_ref_clk);
		else
			ret = eth_test(group, ETH_SPEED_1000M,
				       ETH_JUMBO_TEST_LEN, ETH_JUMBO_ENABLE,
				       interface, ETH_EMAC_DISABLE,
				       ext_ref_clk);
		break;
	case LOOPBACK_TEST:
		ret = eth_loopback_test(eth_index, interface, ETH_EMAC_DISABLE,
					ext_ref_clk);
		break;
	case INTERACTION_TEST:
		ret = eth_interaction_test(eth_index, interface, find_window,
					   ext_ref_clk);
		break;
	case FILTER_MAC_TEST:
		ret = filter_test(eth_index, interface, ext_ref_clk);
		break;
	case ETH_EMAC_TEST:
		//ret = eth_loopback_test(eth_index, interface, ETH_EMAC_ENABLE,
		//			ext_ref_clk);
		ret = eth_test(group, ETH_SPEED_1000M, ETH_TEST_LEN,
			       ETH_JUMBO_DISABLE, ETH_RGMII, ETH_EMAC_ENABLE,
			       ext_ref_clk);
		break;
	case PHY_WOL_TEST:
		ret = eth_phy_wol_test(eth_index, interface, ext_ref_clk);
		break;
	case MAC_MDIO_TEST:
		ret = eth_mdio_test(eth_index, interface, ext_ref_clk);
		break;
	default:
		eth_show_usage();
		ret = -1;
		goto err;
	}
err:
	return ret;
}

void ethernet_init(void)
{
	register_testbench("eth", eth_main, NULL);
}

testbench_init(ethernet_init);

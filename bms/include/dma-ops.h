#ifndef __DMA_OPS_H__
#define __DMA_OPS_H__

#include <linux/list.h>
#include <stdbool.h>
#include <linux/dmaengine.h>

#define DEBUG_DMA 0

//#if defined(CONFIG_CACHE_LITE)
//#define DMA_UNCACHEABLE_BASE 0x60000000
//#define DMA_UNCACHEABLE_MEM DMA_UNCACHEABLE_BASE
//#define DMA_UNCACHEABLE_LLI (DMA_UNCACHEABLE_MEM + 64 * 1024 * 1024)
//#endif

/*
 * dma0: spi1~spi3, cuart2, cuart3, i2s0, i2s1
 * dma1: spi0, cuart0, cuart1
 */

enum DMAC0_HW_HANDSHAKE {
	DMAC0_SPI1_TX,//uart11_tx
	DMAC0_SPI1_RX,//uart11_rx
	DMAC0_SPI2_TX,//uart9_tx
	DMAC0_SPI2_RX,//uart9_rx
	DMAC0_SPI3_TX,//uart10_tx
	DMAC0_SPI3_RX,//uart10_rx
	DMAC0_CUART2_TX,
	DMAC0_CUART2_RX,
	DMAC0_CUART3_TX,
	DMAC0_CUART3_RX,
	DMAC0_IIS0_TX,
	DMAC0_IIS0_RX,
	DMAC0_IIS1_TX,
	DMAC0_IIS1_RX,
	DMAC0_MI2S0_TX,
	DMAC0_MI2S0_RX
};

enum DMAC1_HW_HANDSHAKE {
	DMAC1_SPI0_TX,
	DMAC1_SPI0_RX,
	DMAC1_CUART0_TX,
	DMAC1_CUART0_RX,
	DMAC1_CUART1_TX,
	DMAC1_CUART1_RX,
	DMAC1_CUART4_TX,//pdm0
	DMAC1_CUART4_RX,//pdm1
	DMAC1_CUART5_TX,//pdm2
	DMAC1_CUART5_RX,//pdm3
	DMAC1_CUART6_TX,
	DMAC1_CUART6_RX,
	DMAC1_CUART7_TX,
	DMAC1_CUART7_RX,
	DMAC1_CUART8_TX,
	DMAC1_CUART8_RX
};

static inline bool is_slave_direction(enum dma_transfer_direction direction)
{
	return (direction == DMA_MEM_TO_DEV) || (direction == DMA_DEV_TO_MEM) ||
	       (direction == DMA_DEV_TO_DEV);
}

/*
 * In DMA_SLAVE mode, dma stop when transfer have completed;
 * In DMA_CYCLIC mode, dma do not stop until you stop it manually.
 */
enum dma_transaction_type {
	DMA_SLAVE,
	DMA_CYCLIC,
};

struct dma_info {
	char *devname;
	int src_hw_handshake_num;
	int dst_hw_handshake_num;
};

struct dma_prep_info {
	enum dma_transaction_type mode;
	enum dma_transfer_direction direction;
	dma_addr_t src;
	dma_addr_t dst;
	unsigned long period_len;
	unsigned long len;
	void (*callback)(void *arg);
	void *callback_param;
};

extern void itcs_dma_register(struct dma_device *dev);
extern struct dma_chan *itcs_dma_request_channel(struct dma_info *info);
extern void itcs_dma_release_channel(struct dma_chan *chan);
extern dma_cookie_t itcs_dma_prepare(struct dma_chan *chan,
				     struct dma_prep_info *info);
extern int itcs_dma_slave_config(struct dma_chan *chan,
				 struct dma_slave_config *cfg);
extern int itcs_dma_start(struct dma_chan *chan);
extern int itcs_dma_stop(struct dma_chan *chan);
extern enum dma_status
itcs_dma_transfer_completed(struct dma_chan *chan, dma_cookie_t cookie,
			    struct dma_tx_state *txstate);
extern int itcs_dma_init(int id);
extern bool itcs_is_dma_inited(int id);

#endif

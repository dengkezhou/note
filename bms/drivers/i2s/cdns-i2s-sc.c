#include <stdint.h>
#include <config.h>
#include <malloc.h>
#include <initcall.h>
#include <irq.h>
#include <clock.h>
#include <pads.h>
#include <i2s.h>
#include <dma-ops.h>
#include <cache.h>

#include "cdns-i2s-sc-regs.h"

/* More details are shown in "Table 28. Audio interface modes" */
#define I2S_STANDARD_MODE_MASK    (0x007FFF00UL)
#define I2S_PHILIPS_STANDRAD_MODE (I2S_CTRL_WS_MODE(1) | I2S_CTRL_DATA_WS_DEL(1))
#define I2S_LEFT_JUSTIFIED_MODE   (I2S_CTRL_WS_MODE(1))
#define I2S_RIGHT_JUSTIFIED_MODE  (I2S_CTRL_WS_MODE(1) | I2S_CTRL_DATA_ALIGN)
#define I2S_DSP_MODE              (I2S_CTRL_DATA_WS_DEL(1))
#define I2S_WS_MODE_MASK          (0Xf << 8)

#define I2S_TX_IRQ_MASK (I2S_CTRL_FIFO_AEMPTY_MASK | I2S_CTRL_FIFO_EMPTY_MASK)
#define I2S_HRX_IRQ_MASK (I2S_CTRL_FIFO_AFULL_MASK  | I2S_CTRL_FIFO_FULL_MASK)
#define I2S_FRX_IRQ_MASK (I2S_CTRL_FDX_RFIFO_AFULL_MASK | I2S_CTRL_FDX_RFIFO_FULL_MASK)

struct cdns_i2s_buf {
    uint8_t *tx_buf;
    uint8_t *rx_buf;
    uint32_t tx_len;
    uint32_t rx_len;
    uint8_t tx_done;
    uint8_t rx_done;
};

struct cdns_i2s_dma {
    struct dma_chan *tx_chan;
    struct dma_chan *rx_chan;
    dma_cookie_t tx_cookie;
    dma_cookie_t rx_cookie;
};

struct cdns_i2s {
    int id;               /* I2S controller id */
    uintptr_t base;       /* I2S controller base address */

    struct i2s_ops *ops;
    struct i2s_para para;
    struct cdns_i2s_buf buf;
    struct cdns_i2s_dma dma;

    int irq;
    char name[16];
    int64_t mod_clk;
    uint8_t data_width;

    uint32_t fifo_depth       :CDNS_I2S_SC_DEPTH + 1; /* Words */
    uint32_t aempty_threshold :CDNS_I2S_SC_DEPTH;
    uint32_t afull_threshold  :CDNS_I2S_SC_DEPTH;
    uint32_t sample_rate      :20; /* I2S_SRATE.sample_rate */
};

static struct cdns_i2s *cdns_i2s0_dev, *cdns_i2s1_dev;

static struct cdns_i2s *get_cdns_i2s_by_id(int id)
{
    switch (id) {
    case I2S0: return cdns_i2s0_dev;
    case I2S1: return cdns_i2s1_dev;
    default: break;
    }

    return NULL;
}

static void cdns_i2s_writel(struct cdns_i2s *dev, uint32_t reg, uint32_t val)
{
    writel(val, dev->base + reg);
}

static uint32_t cdns_i2s_readl(struct cdns_i2s *dev, uint32_t reg)
{
    return readl(dev->base + reg);
}

static void cdns_i2s_bit_set(struct cdns_i2s *dev, uint32_t reg, uint32_t bit)
{
    uint32_t tmp;

    tmp = readl(dev->base + reg);
    tmp |= bit;

    writel(tmp, dev->base + reg);
}

static void cdns_i2s_bit_reset(struct cdns_i2s *dev, uint32_t reg, uint32_t bit)
{
    uint32_t tmp;

    tmp = readl(dev->base + reg);
    tmp &= ~bit;

    writel(tmp, dev->base + reg);
}

static void cdns_i2s_bit_update(struct cdns_i2s *dev, uint32_t reg, uint32_t bit, uint32_t mask)
{
    uint32_t tmp;

    tmp = readl(dev->base + reg);
    tmp &= ~mask;
    tmp |= bit;

    writel(tmp, dev->base + reg);
}

#define cdns_i2s_start(dev)            cdns_i2s_bit_set(dev, I2S_CTRL, I2S_CTRL_I2S_EN)
#define cdns_i2s_stop(dev)             cdns_i2s_bit_reset(dev, I2S_CTRL, I2S_CTRL_I2S_EN)
#define cdns_i2s_sfr_reset(dev)        cdns_i2s_bit_reset(dev, I2S_CTRL, I2S_CTRL_SFT_RST)
#define cdns_i2s_fifo_reset(dev)       cdns_i2s_bit_reset(dev, I2S_CTRL, I2S_CTRL_FIFO_RST)
#define cdns_i2s_irq_en(dev)           cdns_i2s_bit_set(dev, I2S_CTRL, I2S_CTRL_INTREQ_MASK)
#define cdns_i2s_irq_disable(dev)      cdns_i2s_bit_reset(dev, I2S_CTRL, I2S_CTRL_INTREQ_MASK)

#define cdns_i2s_irq_clr(dev)          cdns_i2s_writel(dev, I2S_STAT, 0x0);

#define cdns_i2s_fdx_en(dev)           cdns_i2s_bit_set(dev, I2S_CTRL_FDX, (I2S_CTRL_FDX_FULL_DUPLEX | I2S_CTRL_FDX_I2S_FTX_EN | I2S_CTRL_FDX_I2S_FRX_EN))
#define cdns_i2s_fdx_disable(dev)      cdns_i2s_bit_reset(dev, I2S_CTRL_FDX, I2S_CTRL_FDX_FULL_DUPLEX)
#define cdns_i2s_fdx_fifo_reset(dev)   cdns_i2s_bit_reset(dev, I2S_CTRL_FDX, I2S_CTRL_FDX_FIFO_RST)


static int cdns_i2s_module_init(struct cdns_i2s *dev, uint32_t pads_index)
{
    int ret;
    char *module_name;

    if (dev->id == I2S0)
        module_name = "iis0";
    else if (dev->id == I2S1)
        module_name = "iis1";
    else
        return -1;

    ret = itcs_module_enable(CPU, module_name);
    if (ret < 0)
        return ret;

    ret = itcs_module_set_pads_by_index(module_name, pads_index);
    if (ret < 0)
        return ret;

    ret = itcs_module_set_clock(CPU, module_name, NULL, FPGA_SAP_CLK, 0);
    if (ret < 0)
        return ret;

    dev->mod_clk = itcs_module_get_clock(CPU, module_name);
    if (dev->mod_clk < 0)
        return -1;

    return 0;
}

static void cdns_i2s_end_tx(struct cdns_i2s *dev)
{
    if (dev->para.mode & I2S_XFER_INTERRUPT)
        cdns_i2s_bit_reset(dev, I2S_CTRL, I2S_TX_IRQ_MASK);

    dev->buf.tx_buf = NULL;
    dev->buf.tx_done = 1;
    // if (dev->para.mode & I2S_HALF_DUPLEX || dev->buf.rx_done)
    //     cdns_i2s_stop(dev);
}

static void cdns_i2s_end_rx(struct cdns_i2s *dev)
{
    if (dev->para.mode & I2S_XFER_INTERRUPT) {
        if (dev->para.mode & I2S_FULL_DUPLEX)
            cdns_i2s_bit_reset(dev, I2S_CTRL_FDX, I2S_FRX_IRQ_MASK);
        else
            cdns_i2s_bit_reset(dev, I2S_CTRL, I2S_HRX_IRQ_MASK);
    }
    
    dev->buf.rx_done = 1;
    dev->buf.rx_buf = NULL;
    // if (dev->para.mode & I2S_HALF_DUPLEX || dev->buf.tx_done)
    //     cdns_i2s_stop(dev);
}

static int cdns_i2s_irq_handler(int irq, void *args)
{
    struct cdns_i2s *dev = (struct cdns_i2s *)args;
    uint32_t stat;

#define I2S_TX_FIFO_FLAG     (I2S_STAT_FIFO_AEMPTY | I2S_STAT_FIFO_EMPTY)
#define I2S_RX_DONE_FLAG     (I2S_STAT_FIFO_AFULL | I2S_STAT_FIFO_FULL | I2S_STAT_RFIFO_AFULL | I2S_STAT_RFIFO_FULL)

    stat = cdns_i2s_readl(dev, I2S_STAT);
    cdns_i2s_bit_reset(dev, I2S_STAT, stat);

    cdns_i2s_irq_disable(dev);

    if ((stat & I2S_TX_FIFO_FLAG) && (dev->para.mode & (I2S_TRANSMIT | I2S_FULL_DUPLEX)) && !dev->buf.tx_done)
        dev->ops->tx(dev->id, dev->buf.tx_buf, dev->buf.tx_len);

    if ((stat & I2S_RX_DONE_FLAG) && (dev->para.mode & (I2S_RECEIVE | I2S_FULL_DUPLEX)) && !dev->buf.rx_done)
        dev->ops->rx(dev->id, dev->buf.rx_buf, dev->buf.rx_len);

    cdns_i2s_irq_en(dev);

    return 0;
}

#define I2S_TX_PADDING_SIZE (2)

static void tx_padding(struct cdns_i2s *dev)
{
    while (dev->fifo_depth - cdns_i2s_readl(dev, FIFO_LEVEL) < I2S_TX_PADDING_SIZE)
        ;
    for (int i = 0; i < I2S_TX_PADDING_SIZE; i++)
        cdns_i2s_writel(dev, I2S_TX_FIFO, 0);
}

static int __cdns_i2s_tx_int(struct cdns_i2s *dev, uint8_t *buf, uint32_t len)
{
    uint32_t xfer_len, fifo_lvl;
    uint32_t tmp;

    if (!buf)
        return -1;

    if (!len) {
        cdns_i2s_end_tx(dev);
        return 0;
    }

    if (!dev->buf.tx_len)
        len /= dev->data_width;

    fifo_lvl = cdns_i2s_readl(dev, FIFO_LEVEL);
    xfer_len = min(len, dev->fifo_depth - fifo_lvl);
    for (int i = 0; i < xfer_len; i++) {
        memcpy(&tmp, buf, dev->data_width);
        cdns_i2s_writel(dev, I2S_TX_FIFO, tmp);
        buf += dev->data_width;
    }

    if (!dev->buf.tx_len) {
        dev->buf.tx_len = len - xfer_len;
        dev->buf.tx_buf = buf; // TODO: buf maybe on the stack, may not be used in global.
        cdns_i2s_irq_clr(dev);

        if (dev->buf.tx_len)
            cdns_i2s_writel(dev, FIFO_AEMPTY, dev->aempty_threshold);
        cdns_i2s_bit_set(dev, I2S_CTRL, I2S_TX_IRQ_MASK);
        cdns_i2s_irq_en(dev);
        cdns_i2s_start(dev);
        return 0;
    }

    dev->buf.tx_len -= xfer_len;
    dev->buf.tx_buf = buf;
    if (!dev->buf.tx_len) {
        tx_padding(dev);
        cdns_i2s_bit_reset(dev, I2S_CTRL, I2S_CTRL_FIFO_AEMPTY_MASK);
    }
    return 0;
}

static int __cdns_i2s_rx_int(struct cdns_i2s *dev, uint8_t *buf, uint32_t len)
{
    uint32_t xfer_len, fifo_lvl;
    uint32_t tmp = 0;

    if (!buf)
        return -1;

    if (!len) {
        cdns_i2s_end_rx(dev);
        return 0;
    }

    if (!dev->buf.rx_len) {
        /* It means it's our first running. */
        dev->buf.rx_len = len / dev->data_width;
        dev->buf.rx_buf = buf; // TODO: buf maybe on the stack, may not be used in global.
        cdns_i2s_irq_clr(dev);

        if (dev->para.mode & I2S_HALF_DUPLEX) {
            cdns_i2s_writel(dev, FIFO_AFULL, min(dev->buf.rx_len, dev->afull_threshold));
            cdns_i2s_bit_set(dev, I2S_CTRL, I2S_HRX_IRQ_MASK);
        } else {
            cdns_i2s_writel(dev, FIFO_AFULL_FDR, min(dev->buf.rx_len, dev->afull_threshold));
            cdns_i2s_bit_set(dev, I2S_CTRL_FDX, I2S_FRX_IRQ_MASK);
        }
        cdns_i2s_irq_en(dev);
        cdns_i2s_start(dev);
        return 0;
    }

    if (dev->para.mode & I2S_HALF_DUPLEX)
        fifo_lvl = cdns_i2s_readl(dev, FIFO_LEVEL);
    else
        fifo_lvl = cdns_i2s_readl(dev, FIFO_LEVEL_FDR);

    xfer_len = min(len, fifo_lvl);
    for (int i = 0; i < xfer_len; i++) {
        tmp = cdns_i2s_readl(dev, I2S_RX_FIFO);
        memcpy(buf, (void *)&tmp, dev->data_width);
        buf += dev->data_width;
    }

    dev->buf.rx_len -= xfer_len;
    dev->buf.rx_buf = buf; // TODO: buf maybe on the stack, may not be used in global.
    if (dev->para.mode & I2S_HALF_DUPLEX)
        cdns_i2s_writel(dev, FIFO_AFULL, min(dev->buf.rx_len, dev->afull_threshold));
    else
        cdns_i2s_writel(dev, FIFO_AFULL_FDR, min(dev->buf.rx_len, dev->afull_threshold));

    return 0;
}

static int __cdns_i2s_tx_rx_int(struct cdns_i2s *dev, uint8_t *tbuf, uint8_t *rbuf, uint32_t len)
{
    uint32_t xfer_len, fifo_lvl;
    uint32_t tmp;

    if (!tbuf || !rbuf)
        return -1;

    if (!len)
        return 0;
    
    len /= dev->data_width;

    fifo_lvl = cdns_i2s_readl(dev, FIFO_LEVEL);
    xfer_len = min(len, dev->fifo_depth - fifo_lvl);

    for (int i = 0; i < xfer_len; i++) {
        memcpy(&tmp, tbuf, dev->data_width);
        cdns_i2s_writel(dev, I2S_TX_FIFO, tmp);
        tbuf += dev->data_width;
    }

    dev->buf.tx_len = len - xfer_len;
    dev->buf.rx_len = len;
    dev->buf.tx_buf = tbuf; // TODO: buf maybe on the stack, may not be used in global.
    dev->buf.rx_buf = rbuf; // TODO: buf maybe on the stack, may not be used in global.

    cdns_i2s_irq_clr(dev);

    cdns_i2s_writel(dev, FIFO_AFULL_FDR, min(dev->buf.rx_len, dev->afull_threshold));

    if (dev->buf.tx_len)
        cdns_i2s_writel(dev, FIFO_AEMPTY, dev->aempty_threshold);
    cdns_i2s_bit_set(dev, I2S_CTRL, I2S_TX_IRQ_MASK);
    cdns_i2s_bit_set(dev, I2S_CTRL_FDX, I2S_FRX_IRQ_MASK);
    cdns_i2s_irq_en(dev);
    cdns_i2s_start(dev);

    return 0;
}

static void cdns_i2s_tx_dma_cb(void *arg)
{
    struct cdns_i2s *dev = (struct cdns_i2s *)arg;


    itcs_dma_stop(dev->dma.tx_chan);
    // itcs_dma_release_channel(dev->dma.tx_chan);

    printf("DMA TX done\n");
    cdns_i2s_end_tx(dev);
}

static void cdns_i2s_rx_dma_cb(void *arg)
{
    struct cdns_i2s *dev = (struct cdns_i2s *)arg;

    itcs_dma_stop(dev->dma.rx_chan);
    // itcs_dma_release_channel(dev->dma.rx_chan);

    printf("DMA RX done\n");
    cdns_i2s_end_rx(dev);
}

static enum dma_slave_buswidth cdns_i2s_dma_slave_buswidth_map(uint32_t width)
{
    switch (width) {
    case 1: return DMA_SLAVE_BUSWIDTH_1_BYTE;
    case 3: return DMA_SLAVE_BUSWIDTH_3_BYTES;
    case 4: return DMA_SLAVE_BUSWIDTH_4_BYTES;
    default: case 2: return DMA_SLAVE_BUSWIDTH_2_BYTES;
    }
}

static int __cdns_i2s_tx_dma(struct cdns_i2s *dev, uint8_t *buf, uint32_t len)
{
    int ret;
    struct dma_prep_info prep_info;
    struct dma_slave_config cfg;
    struct dma_info info = { .devname = "dma0" };
    uint32_t xfer_len;
    uint32_t tmp;


    if (dev->id == I2S0)
        info.dst_hw_handshake_num = DMAC0_IIS0_TX;
    else
        info.dst_hw_handshake_num = DMAC0_IIS1_TX;
    
    len /= dev->data_width;

    xfer_len = min(len, 32);
    for (int i = 0; i < xfer_len; i++) {
        memcpy(&tmp, buf, dev->data_width);
        cdns_i2s_writel(dev, I2S_TX_FIFO, tmp);
        buf += dev->data_width;
    }
    len -= xfer_len;
    if (!len) {
        cdns_i2s_start(dev);
        tx_padding(dev);
        while(cdns_i2s_readl(dev, FIFO_LEVEL))
            ;
        cdns_i2s_end_tx(dev);
        return 0;
    }

    dev->dma.tx_chan = itcs_dma_request_channel(&info);
    if (!dev->dma.tx_chan)
        return -1;

    cfg.direction = DMA_MEM_TO_DEV;
    cfg.src_addr = virt_to_phys(buf);
    cfg.dst_addr = dev->base + I2S_TX_FIFO;
    cfg.src_addr_width = cdns_i2s_dma_slave_buswidth_map(dev->data_width);
    cfg.dst_addr_width = cdns_i2s_dma_slave_buswidth_map(dev->data_width);
    cfg.src_burstlen = dev->para.dma_burstlen;
    cfg.dst_burstlen = dev->para.dma_burstlen;
    cfg.device_fc = 0;
    ret = itcs_dma_slave_config(dev->dma.tx_chan, &cfg);
    if (ret < 0)
        return -1;

    prep_info.direction = DMA_MEM_TO_DEV;
    prep_info.mode = DMA_SLAVE;
    prep_info.src = virt_to_phys(buf);
    prep_info.len = len * dev->data_width;
    prep_info.callback = cdns_i2s_tx_dma_cb;
    prep_info.callback_param = dev;
    dev->dma.tx_cookie = itcs_dma_prepare(dev->dma.tx_chan, &prep_info);
    if (dev->dma.tx_cookie < 0)
        return -1;

    itcs_dcache_flush();

    if (dev->para.mode & I2S_HALF_DUPLEX) {
        cdns_i2s_start(dev);
        itcs_dma_start(dev->dma.tx_chan);
    }

    return 0;
}

static int __cdns_i2s_rx_dma(struct cdns_i2s *dev, uint8_t *buf, uint32_t len)
{
    int ret;
    struct dma_prep_info prep_info;
    struct dma_slave_config cfg;
    struct dma_info info = { .devname = "dma0" };

    if (dev->id == I2S0)
        info.src_hw_handshake_num = DMAC0_IIS0_RX;
    else
        info.src_hw_handshake_num = DMAC0_IIS1_RX;
    
    dev->dma.rx_chan = itcs_dma_request_channel(&info);
    if (!dev->dma.rx_chan)
        return -1;
    
    cfg.direction = DMA_DEV_TO_MEM;
    cfg.src_addr = dev->base + I2S_RX_FIFO;
    cfg.dst_addr = virt_to_phys(buf);
    cfg.src_addr_width = cdns_i2s_dma_slave_buswidth_map(dev->data_width);
    cfg.dst_addr_width = cdns_i2s_dma_slave_buswidth_map(dev->data_width);
    cfg.src_burstlen = dev->para.dma_burstlen;
    cfg.dst_burstlen = dev->para.dma_burstlen;
    cfg.device_fc = 0;
    ret = itcs_dma_slave_config(dev->dma.rx_chan, &cfg);
    if (ret < 0)
        return -1;

    prep_info.direction = DMA_DEV_TO_MEM;
    prep_info.mode = DMA_SLAVE;
    prep_info.dst = virt_to_phys(buf);
    prep_info.len = len;
    prep_info.callback = cdns_i2s_rx_dma_cb;
    prep_info.callback_param = dev;
    dev->dma.rx_cookie = itcs_dma_prepare(dev->dma.rx_chan, &prep_info);
    if (dev->dma.rx_cookie < 0)
        return -1;

    itcs_dcache_flush();

    if (dev->para.mode & I2S_HALF_DUPLEX) {
        cdns_i2s_start(dev);
        itcs_dma_start(dev->dma.rx_chan);
    }

    return 0;
}

static int __cdns_i2s_tx_rx_dma(struct cdns_i2s *dev, uint8_t *tbuf, uint8_t *rbuf, uint32_t len)
{
    int ret = 0;

    ret += __cdns_i2s_tx_dma(dev, tbuf, len);
    ret += __cdns_i2s_rx_dma(dev, rbuf, len);

    cdns_i2s_start(dev);

    itcs_dma_start(dev->dma.tx_chan);
    itcs_dma_start(dev->dma.rx_chan);

    return ret;
}


static int cdns_i2s_tx(int id, uint8_t *buf, uint32_t len)
{
    struct cdns_i2s *dev = get_cdns_i2s_by_id(id);

    if (!dev)
        return -1;
    
    dev->buf.tx_done = 0;

    if (dev->para.mode & I2S_XFER_BLOCKING) {
        return -1;
    } else if (dev->para.mode & I2S_XFER_DMA) {
        return __cdns_i2s_tx_dma(dev, buf, len);
    } else {
        dev->para.mode |= I2S_XFER_INTERRUPT;
        return __cdns_i2s_tx_int(dev, buf, len);
    }
}

static int cdns_i2s_rx(int id, uint8_t *buf, uint32_t len)
{
    struct cdns_i2s *dev = get_cdns_i2s_by_id(id);

    if (!dev)
        return -1;

    dev->buf.rx_done = 0;

    if (dev->para.mode & I2S_XFER_BLOCKING) {
        return -1;
    } else if (dev->para.mode & I2S_XFER_DMA) {
        return __cdns_i2s_rx_dma(dev, buf, len);
    } else {
        dev->para.mode |= I2S_XFER_INTERRUPT;
        return __cdns_i2s_rx_int(dev, buf, len);
    }
}

static int cdns_i2s_tx_rx(int id, uint8_t *tbuf, uint8_t *rbuf, uint32_t len)
{
    struct cdns_i2s *dev = get_cdns_i2s_by_id(id);

    if (!dev)
        return -1;

    dev->buf.tx_done = 0;
    dev->buf.rx_done = 0;

    if (dev->para.mode & I2S_XFER_BLOCKING) {
        return -1;
    } else if (dev->para.mode & I2S_XFER_DMA) {
        return __cdns_i2s_tx_rx_dma(dev, tbuf, rbuf, len);
    } else {
        dev->para.mode |= I2S_XFER_INTERRUPT;
        return __cdns_i2s_tx_rx_int(dev, tbuf, rbuf, len);
    }
}

static uint32_t chn_width_map(uint32_t n_sck)
{
    switch (n_sck) {
    case 8: return I2S_CTRL_CHN_WIDTH(0);
    case 12: return I2S_CTRL_CHN_WIDTH(1);
    case 16: return I2S_CTRL_CHN_WIDTH(2);
    case 18: return I2S_CTRL_CHN_WIDTH(3);
    case 20: return I2S_CTRL_CHN_WIDTH(4);
    case 28: return I2S_CTRL_CHN_WIDTH(6);
    case 32: return I2S_CTRL_CHN_WIDTH(7);
    default: case 24: return I2S_CTRL_CHN_WIDTH(5);
    }
}

static int cdns_i2s_config(int id, const struct i2s_para *para)
{
    struct cdns_i2s *dev = get_cdns_i2s_by_id(id);
    uint32_t tmp;

    if (!para || !dev)
        return -1;

    cdns_i2s_sfr_reset(dev);
    memset(&dev->buf, 0, sizeof(dev->buf));
    cdns_i2s_writel(dev, I2S_SRES, para->bitspersample - 1);
    dev->data_width = para->bitspersample >> 3;

    tmp = para->sample_freq * para->channels * para->bitspersample;
    if (!tmp)
        return -1;
    dev->sample_rate = dev->mod_clk / tmp;
    cdns_i2s_writel(dev, I2S_SRATE, dev->sample_rate);

    cdns_i2s_bit_update(dev, I2S_CTRL, chn_width_map(para->bitspersample), 7U << 5);

    if (para->mode & I2S_MASTER) {
        cdns_i2s_bit_set(dev, I2S_CTRL, I2S_CTRL_MS_CFG);
    } else if (para->mode & I2S_SLAVE) {
        cdns_i2s_bit_reset(dev, I2S_CTRL, I2S_CTRL_MS_CFG);
    } else {
        printf("Invalid mode: set master or slave\n");
        return -1;
    }

    if (para->mode & I2S_TRANSMIT) {
        cdns_i2s_bit_set(dev, I2S_CTRL, I2S_CTRL_DIR_CFG);
    } else if (para->mode & I2S_RECEIVE) {
        cdns_i2s_bit_reset(dev, I2S_CTRL, I2S_CTRL_DIR_CFG);
    }

    if (para->mode & I2S_FULL_DUPLEX) {
        cdns_i2s_fdx_en(dev);
        cdns_i2s_writel(dev, I2S_SRES_FDR, para->bitspersample - 1);
        cdns_i2s_fdx_fifo_reset(dev);
        cdns_i2s_fifo_reset(dev);
    } else if (para->mode & I2S_HALF_DUPLEX) {
        cdns_i2s_fifo_reset(dev);
    } else {
        printf("Invalid mode: half or full duplex must be specified\n");
        return -1;
    }

    switch (para->standard) {
    case SND_SOC_DAIFMT_I2S:
        tmp = I2S_PHILIPS_STANDRAD_MODE; break;
    case SND_SOC_DAIFMT_RIGHT_J:
        tmp = I2S_RIGHT_JUSTIFIED_MODE; break;
    case SND_SOC_DAIFMT_LEFT_J:
        tmp = I2S_LEFT_JUSTIFIED_MODE; break;
    case SND_SOC_DAIFMT_DSP_A:
    case SND_SOC_DAIFMT_DSP_B:
        tmp = I2S_DSP_MODE; break;
    case SND_SOC_DAIFMT_AC97:
    case SND_SOC_DAIFMT_PDM:
    default:
        tmp = I2S_PHILIPS_STANDRAD_MODE; break;     
    }
    cdns_i2s_bit_update(dev, I2S_CTRL, tmp, I2S_STANDARD_MODE_MASK);

    if(para->tdm.tdm_en == I2S_FUNC_ENABLE)
    {
        /*set tdm ctrl register*/
        tmp = I2S_TDM_EN;
        tmp |=  I2S_TDM_CHN_NO(para->channels - 1 );
        tmp |=  I2S_TDM_CHN_EN((1 << para->channels) - 1);
        cdns_i2s_writel(dev, TDM_CTRL, tmp);

        /*set ws mode*/
        tmp = para->tdm.ws_mode;
        cdns_i2s_bit_update(dev, I2S_CTRL, tmp, I2S_WS_MODE_MASK);
    }

    memcpy(&dev->para, para, sizeof(*para));
    return 0;
}


static void cdns_i2s_writel_by_id(int id, uint32_t reg, uint32_t val)
{
    struct cdns_i2s *dev = get_cdns_i2s_by_id(id);

    if (!dev)
        return;

    writel(val, dev->base + reg);
}

static uint32_t cdns_i2s_readl_by_id(int id, uint32_t reg)
{
    struct cdns_i2s *dev = get_cdns_i2s_by_id(id);

    if (!dev)
        return 0;

    return readl(dev->base + reg);
}


static int cdns_check_done(int id)
{
    struct cdns_i2s *dev = get_cdns_i2s_by_id(id);

    if (!dev)
        return 0;
    
    if (dev->para.mode & I2S_TRANSMIT)
        return dev->buf.tx_done;
    else if (dev->para.mode & I2S_RECEIVE)
        return dev->buf.rx_done;
    else
        return dev->buf.tx_done && dev->buf.rx_done;
}

static struct i2s_ops cdns_i2s_ops = {
    .tx           = cdns_i2s_tx,
    .rx           = cdns_i2s_rx,
    .tx_rx        = cdns_i2s_tx_rx,
    .config       = cdns_i2s_config,
    .__writel     = cdns_i2s_writel_by_id,
    .__readl      = cdns_i2s_readl_by_id,
    .check_done   = cdns_check_done,
};

static int cdns_i2s_probe(const struct i2s_para *para)
{
    int id;
    struct cdns_i2s *pdata;
    int ret = -1;

    pdata = malloc(sizeof(*pdata));
    if (!pdata) {
        ret = -1;
        goto err_malloc;
    }

    id = para->id;

    memset(pdata, 0, sizeof(*pdata));

    if (id == I2S0) {
        pdata->base = ITCS_C_I2S0_BASE;
        pdata->irq = C_IIS0_IRQn;
        cdns_i2s0_dev = pdata;
    } else if (id == I2S1) {
        pdata->base = ITCS_C_I2S1_BASE;
        pdata->irq = C_IIS1_IRQn;
        cdns_i2s1_dev = pdata;
    } else {
        ret = -1;
        goto err_id;
    }

    pdata->id = id;
    pdata->ops = &cdns_i2s_ops;
    pdata->fifo_depth = (1 << CDNS_I2S_SC_DEPTH);
    pdata->aempty_threshold = pdata->fifo_depth >> 1;
    pdata->afull_threshold = pdata->fifo_depth >> 1;

    ret = cdns_i2s_module_init(pdata, para->pads_index);
    if (ret < 0)
        goto err_id;

    snprintf(pdata->name, sizeof(pdata->name), "i2s-%d", pdata->id);
    ret = request_irq(pdata->irq, cdns_i2s_irq_handler, pdata->name, pdata);
    if (ret < 0)
        goto err_id;

    return 0;

err_id:
    free(pdata);
err_malloc:
    return ret;
}

int i2s_init(const struct i2s_para *para)
{
    return cdns_i2s_probe(para);
}

int i2s_get_ops(struct i2s_ops **ops)
{
    *ops = &cdns_i2s_ops;
    return 0;
}

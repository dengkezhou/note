#include <stdint.h>
#include <config.h>
#include <malloc.h>
#include <initcall.h>
#include <irq.h>
#include <clock.h>
#include <pads.h>
#include <i2s-mc.h>
#include <dma-ops.h>
#include <cache.h>

#include "cdns-i2s-mc-regs.h"

//#define DEBUG_I2S_MC

#ifdef DEBUG_I2S_MC
#define DEBUG_I2S_MC_LOG(format, ...) printf(format, ##__VA_ARGS__)
#else
#define DEBUG_I2S_MC_LOG(format, ...)
#endif



/*--------------------struct-----------------------*/
struct cdns_i2s_mc_buf {
    uint8_t *tx_buf;
    uint8_t *rx_buf;
    uint32_t tx_len;
    uint32_t rx_len;
    uint8_t tx_done;
    uint8_t rx_done;
};

struct cdns_i2s_mc_dma {
    struct dma_chan *tx_chan;
    struct dma_chan *rx_chan;
    dma_cookie_t tx_cookie;
    dma_cookie_t rx_cookie;
};

struct cdns_i2s_mc {
    int id;               /* I2S controller id */
    uintptr_t base;       /* I2S controller base address */

    struct i2s_mc_ops *ops;
    struct i2s_mc_para para;
    struct cdns_i2s_mc_buf buf;
    struct cdns_i2s_mc_dma dma;

    int irq;
    char name[16];
    int64_t mod_clk;
    uint8_t data_width;

    uint32_t fifo_depth       :CDNS_I2S_MC_DEPTH + 1; /* Words */
    uint32_t aempty_threshold :CDNS_I2S_MC_DEPTH;
    uint32_t afull_threshold  :CDNS_I2S_MC_DEPTH;
};

/*handler*/
#define CDNS_I2S_MC_DEV_NUM  1
struct cdns_i2s_mc *cdns_i2s_mc_dev[CDNS_I2S_MC_DEV_NUM] = {NULL};

static struct cdns_i2s_mc *get_mc_dev_by_id(int id)
{
    if(id >= CDNS_I2S_MC_DEV_NUM)
    {
        return NULL;
    }
    return cdns_i2s_mc_dev[id];
}

static void set_mc_dev_by_id(int id, struct cdns_i2s_mc *dev)
{
    cdns_i2s_mc_dev[id] = dev;
}

/*--------------------utils-----------------------*/
static void cdns_i2s_mc_writel(uintptr_t base, uint32_t reg, uint32_t val)
{
    writel(val, base + reg);
}

static uint32_t cdns_i2s_mc_readl(uintptr_t base, uint32_t reg)
{
    return readl(base + reg);
}

static void cdns_i2s_mc_bit_set(uintptr_t base, uint32_t reg, uint32_t bit)
{
    uint32_t tmp;

    tmp = readl(base + reg);
    tmp |= bit;

    writel(tmp, base + reg);
}

static void cdns_i2s_mc_bit_reset(uintptr_t base, uint32_t reg, uint32_t bit)
{
    uint32_t tmp;

    tmp = readl(base + reg);
    tmp &= ~bit;

    writel(tmp, base + reg);
}


static void cdns_i2s_mc_bit_update(uintptr_t base, uint32_t reg, uint32_t bit, uint32_t mask)
{
    uint32_t tmp;

    tmp = readl(base + reg);
    tmp &= ~mask;
    tmp |= bit;

    writel(tmp, base + reg);
}


/*--------------------i2s mc func ----------------------------------*/
void cdns_i2s_mc_tx_start(struct cdns_i2s_mc *dev)
{
    int tmp, mask;
    tmp = cdns_i2s_mc_readl(dev->base, I2S_MC_CTRL);
    mask = (tmp & I2S_MC_TR_CFG_ALL) >> I2S_EN_TR_CFG_OFFSET ;

    tmp |= mask | I2S_MC_TSYNC_RST;

    cdns_i2s_mc_writel(dev->base, I2S_MC_CTRL, tmp);
}

void cdns_i2s_mc_rx_start(struct cdns_i2s_mc *dev)
{
    int tmp, mask;
    tmp = cdns_i2s_mc_readl(dev->base, I2S_MC_CTRL);
    mask = (~tmp & I2S_MC_TR_CFG_ALL) >>  I2S_EN_TR_CFG_OFFSET;

    tmp |= mask | I2S_MC_RSYNC_RST;

    cdns_i2s_mc_writel(dev->base, I2S_MC_CTRL, tmp);
}

#define cdns_i2s_mc_start(dev)            cdns_i2s_mc_bit_update(dev->base, I2S_MC_CTRL, I2S_MC_I2S_EN_ALL,I2S_MC_I2S_EN_ALL)
#define cdns_i2s_mc_stop(dev)             cdns_i2s_mc_bit_update(dev->base, I2S_MC_CTRL, 0, I2S_MC_I2S_EN_ALL)
#define cdns_i2s_mc_sfr_reset(dev)        cdns_i2s_mc_bit_reset(dev->base, I2S_MC_CTRL, I2S_MC_SFT_RST)
#define cdns_i2s_mc_fifo_reset(dev)       cdns_i2s_mc_bit_reset(dev->base, I2S_MC_CTRL, I2S_MC_FIFO_RST)
#define cdns_i2s_mc_rfifo_reset(dev)      cdns_i2s_mc_bit_reset(dev->base, I2S_MC_CTRL, I2S_MC_RFIFO_RST)

#define cdns_i2s_mc_irq_en(dev)           cdns_i2s_mc_bit_set(dev->base, I2S_MC_CID_CRTL, I2S_MC_INTREQ_MASK)
#define cdns_i2s_mc_irq_disable(dev)      cdns_i2s_mc_bit_reset(dev->base, I2S_MC_CID_CRTL, I2S_MC_INTREQ_MASK)
#define cdns_i2s_mc_irq_clr(dev)          cdns_i2s_mc_writel(dev->base, I2S_MC_INTR_STAT, 0x0);

/*--------------------module enable-----------------------*/
static int cdns_i2s_mc_module_init(struct cdns_i2s_mc *dev)
{
    int ret;
    char *module_name;

    module_name = dev->name;

    ret = itcs_module_enable(CPU, module_name);
    if (ret < 0)
        return ret;

    ret = itcs_module_set_pads_by_index(module_name, 0);
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

/*--------------------operations-----------------------*/
static int cdns_i2s_mc_irq_handler(int irq, void *args)
{
    struct cdns_i2s_mc *dev = (struct cdns_i2s_mc *)args;
    uint32_t stat;

    //cdns_i2s_mc_stop(dev);

    stat = cdns_i2s_mc_readl(dev->base, I2S_MC_INTR_STAT);
    if (stat & I2S_MC_R_OVERR)
    {
        //printf("rx overrun\n");
        /*not reset the rfifo*/
        stat &= ~I2S_MC_R_OVERR;
    }

    /*set overrun bit to 0 can cause rx re_init*/
    //cdns_i2s_mc_bit_reset(dev->base, I2S_MC_INTR_STAT, stat);

    //DEBUG_I2S_MC_LOG("irq request %x\n",stat);

    cdns_i2s_mc_irq_disable(dev);

    if ((stat & I2S_MC_INTREQ_TX_STAT) && !dev->buf.tx_done)
        dev->ops->tx(dev->id, dev->buf.tx_buf, dev->buf.tx_len);

    if ((stat & I2S_MC_INTREQ_RX_STAT) && !dev->buf.rx_done)
        dev->ops->rx(dev->id, dev->buf.rx_buf, dev->buf.rx_len);

    if (!dev->buf.rx_done)
        cdns_i2s_mc_irq_en(dev);
    //cdns_i2s_mc_start(dev);

    return 0;
}

static int cdns_i2s_mc_probe(int id)
{
    int ret;
    struct cdns_i2s_mc *dev = get_mc_dev_by_id(id);

    dev->base = ITCS_C_MI2S_BASE;
    dev->irq = C_MIIS0_IRQn;
    dev->fifo_depth = (1 << CDNS_I2S_MC_DEPTH);
    dev->aempty_threshold = dev->fifo_depth >> 1;
    dev->afull_threshold = dev->fifo_depth >> 2;
    dev->id = id;

    ret = sprintf(dev->name, "mi2s%d", dev->id);
    //printf("name = %s\n",dev->name);

    ret = cdns_i2s_mc_module_init(dev);
    if (ret)
    {
        printf("cdns_i2s_mc_module_init failed, ret = %d\n",ret);
        return ret;
    }
        
    ret = request_irq(dev->irq, cdns_i2s_mc_irq_handler, dev->name, dev);
    if (ret)
    {
        printf("request_irq failed, ret = %d\n",ret);
        return ret;
    }

    return 0;  
}

static int cdns_i2s_mc_config(int id, const struct i2s_mc_para *para)
{
    int i;
    int tmp;
    unsigned int sample_rate, resolution;
    struct cdns_i2s_mc *dev;

    if (para == NULL)
    {
        printf("para = null\n");
        return -1;
    }

    dev = get_mc_dev_by_id(id);
    if (dev == NULL)
    {
        printf("i2s mc %d has not been initted\n",id);
        return -1;
    }

    memset(&dev->buf, 0, sizeof(dev->buf));
    cdns_i2s_mc_writel(dev->base, I2S_MC_CTRL, 0);
    cdns_i2s_mc_sfr_reset(dev);

    /*set ms_cfg, tr_cfg and loop back*/
    tmp = cdns_i2s_mc_readl(dev->base, I2S_MC_CTRL);
    if (para->ms_cfg == I2S_CFG_TX_MASTER){
        tmp |= I2S_MC_TX_MS;
        tmp &= ~I2S_MC_RX_MS;
    } else {
        tmp |= I2S_MC_RX_MS;
        tmp &= ~I2S_MC_TX_MS;
    }

    tmp &= ~I2S_MC_I2S_EN_ALL;
    for (i = 0; i < I2S_MC_CHANNEL_CNT; ++i)
    {
        tmp |= para->ch_tr_cfg[i] << (i + I2S_MC_TR_CFG_OFFSET);
    }

    if (para->loop_back == I2S_LOOP_BACK_MODE)
    {
        tmp |= (I2S_MC_LOOP_BACK_EN | I2S_MC_TSYNC_LOOP_BACK | I2S_MC_RSYNC_LOOP_BACK) ;
    }

    cdns_i2s_mc_writel(dev->base, I2S_MC_CTRL, tmp);

    /*set sample_rate and resolution*/
    dev->data_width = para->bitspersample >> 3;
    resolution = para->bitspersample - 1;
    tmp = para->sample_freq * 2 * para->bitspersample;
    if (!tmp)
        return -1;
    sample_rate = dev->mod_clk / tmp;

    tmp = (sample_rate << I2S_MC_T_SAMPLE_RATE_OFFSET) + (sample_rate << I2S_MC_R_SAMPLE_RATE_OFFSET);
    tmp += (resolution << I2S_MC_T_RESOLUTION_OFFSET) + (resolution << I2S_MC_R_RESOLUTION_OFFSET);
    cdns_i2s_mc_writel(dev->base, I2S_MC_SRR, tmp);

    /*set standard*/
    switch (para->standard) {
        case SND_SOC_DAIFMT_I2S:
            tmp = I2S_MC_DEV_PHILIPS_MODE; 
            break;
        case SND_SOC_DAIFMT_RIGHT_J:
            tmp = I2S_MC_DEV_R_JUSTIFIED_MODE; 
            break;
        case SND_SOC_DAIFMT_LEFT_J:
            tmp = I2S_MC_DEV_L_JUSTIFIED_MODE; 
            break;
        case SND_SOC_DAIFMT_DSP:
            tmp = I2S_MC_DEV_DSP_MODE; 
            break;
        default:
            tmp = I2S_MC_DEV_PHILIPS_MODE; 
            break;     
    }
    cdns_i2s_mc_writel(dev->base, I2S_MC_DEV_CONF, tmp);

    /**/
    memcpy(&dev->para, para, sizeof(struct i2s_mc_para));
    return 0;
}

static void cdns_i2s_mc_end_tx(struct cdns_i2s_mc *dev)
{
    if (dev->para.mode == I2S_MC_XFER_INTERRUPT)
        cdns_i2s_mc_bit_reset(dev->base, I2S_MC_CID_CRTL, I2S_MC_INTREQ_TX_MASK);

    dev->buf.tx_buf = NULL;
    dev->buf.tx_done = 1;
}

static void cdns_i2s_mc_end_rx(struct cdns_i2s_mc *dev)
{
    if (dev->para.mode == I2S_MC_XFER_INTERRUPT)
        cdns_i2s_mc_bit_reset(dev->base, I2S_MC_CID_CRTL, I2S_MC_INTREQ_RX_MASK);
    
    dev->buf.rx_done = 1;
    dev->buf.rx_buf = NULL;
}

static void cdns_i2s_mc_tx_dma_cb(void *arg)
{
    struct cdns_i2s_mc *dev = (struct cdns_i2s_mc *)arg;


    itcs_dma_stop(dev->dma.tx_chan);
    // itcs_dma_release_channel(dev->dma.tx_chan);

    printf("DMA TX done\n");
    cdns_i2s_mc_end_tx(dev);
}

static void cdns_i2s_mc_rx_dma_cb(void *arg)
{
    struct cdns_i2s_mc *dev = (struct cdns_i2s_mc *)arg;

    itcs_dma_stop(dev->dma.rx_chan);
    // itcs_dma_release_channel(dev->dma.rx_chan);

    printf("DMA RX done\n");
    cdns_i2s_mc_end_rx(dev);
}

static enum dma_slave_buswidth cdns_i2s_mc_dma_slave_buswidth_map(uint32_t width)
{
    switch (width) {
    case 1: return DMA_SLAVE_BUSWIDTH_1_BYTE;
    case 3: return DMA_SLAVE_BUSWIDTH_3_BYTES;
    case 4: return DMA_SLAVE_BUSWIDTH_4_BYTES;
    default: case 2: return DMA_SLAVE_BUSWIDTH_2_BYTES;
    }
}

static int __cdns_i2s_mc_tx_dma(struct cdns_i2s_mc *dev, uint8_t *buf, uint32_t len)
{
    int ret;
    struct dma_prep_info prep_info;
    struct dma_slave_config cfg;
    struct dma_info info = { .devname = "dma0" };
    uint32_t xfer_len;
    uint32_t tmp;
    uint32_t aempty;

    info.dst_hw_handshake_num = DMAC0_MI2S0_TX;
    
    len /= dev->data_width;

    aempty = (dev->aempty_threshold << I2S_MC_AEMPTY_OFFSET) + (0xff << I2S_MC_AFULL_OFFSET);
    cdns_i2s_mc_writel(dev->base, I2S_MC_TFIFO_CTRL, aempty);

    xfer_len = min(len, 8);
    for (int i = 0; i < xfer_len; i++) {
        memcpy(&tmp, buf, dev->data_width);
        cdns_i2s_mc_writel(dev->base, I2S_MC_TX_FIFO, tmp);
        buf += dev->data_width;
    }
    len -= xfer_len;

    if (!len) {
        cdns_i2s_mc_start(dev);
        while(cdns_i2s_mc_readl(dev->base, I2S_MC_TFIFO_STAT))
            ;
        cdns_i2s_mc_end_tx(dev);
        return 0;
    }

    dev->dma.tx_chan = itcs_dma_request_channel(&info);
    if (!dev->dma.tx_chan)
        return -1;

    cfg.direction = DMA_MEM_TO_DEV;
    cfg.src_addr = virt_to_phys(buf);
    cfg.dst_addr = dev->base + I2S_MC_TX_FIFO;
    cfg.src_addr_width = cdns_i2s_mc_dma_slave_buswidth_map(dev->data_width);
    cfg.dst_addr_width = cdns_i2s_mc_dma_slave_buswidth_map(dev->data_width);
    cfg.src_burstlen = DMA_SLAVE_BURST_TRANS_LEN_8;
    cfg.dst_burstlen = DMA_SLAVE_BURST_TRANS_LEN_8;
    cfg.device_fc = 0;
    ret = itcs_dma_slave_config(dev->dma.tx_chan, &cfg);
    if (ret < 0)
        return -1;

    prep_info.direction = DMA_MEM_TO_DEV;
    prep_info.mode = DMA_SLAVE;
    prep_info.src = virt_to_phys(buf);
    prep_info.len = len * dev->data_width;
    prep_info.callback = cdns_i2s_mc_tx_dma_cb;
    prep_info.callback_param = dev;
    dev->dma.tx_cookie = itcs_dma_prepare(dev->dma.tx_chan, &prep_info);
    if (dev->dma.tx_cookie < 0)
        return -1;

    itcs_dcache_flush();
    //itcs_dcache_clean();

    if (dev->para.ms_cfg == I2S_CFG_TX_MASTER)
    {
        cdns_i2s_mc_start(dev);
        itcs_dma_start(dev->dma.rx_chan);
        //udelay(100);  /*TOD0: dma may be recv the repetitive data*/
        itcs_dma_start(dev->dma.tx_chan);
    }else
    {
        itcs_dma_start(dev->dma.tx_chan);
    }

    return 0;
}

static int __cdns_i2s_mc_rx_dma(struct cdns_i2s_mc *dev, uint8_t *buf, uint32_t len)
{
    int ret, afull;
    struct dma_prep_info prep_info;
    struct dma_slave_config cfg;
    struct dma_info info = { .devname = "dma0" };

    afull = dev->afull_threshold << I2S_MC_AFULL_OFFSET;
    cdns_i2s_mc_writel(dev->base, I2S_MC_RFIFO_CTRL, afull);

    info.src_hw_handshake_num = DMAC0_MI2S0_RX;

    dev->dma.rx_chan = itcs_dma_request_channel(&info);
    if (!dev->dma.rx_chan)
        return -1;
    
    cfg.direction = DMA_DEV_TO_MEM;
    cfg.src_addr = dev->base + I2S_MC_RX_FIFO;
    cfg.dst_addr = virt_to_phys(buf);
    cfg.src_addr_width = cdns_i2s_mc_dma_slave_buswidth_map(dev->data_width);
    cfg.dst_addr_width = cdns_i2s_mc_dma_slave_buswidth_map(dev->data_width);
    cfg.src_burstlen = DMA_SLAVE_BURST_TRANS_LEN_8;
    cfg.dst_burstlen = DMA_SLAVE_BURST_TRANS_LEN_8;
    cfg.device_fc = 0;
    ret = itcs_dma_slave_config(dev->dma.rx_chan, &cfg);
    if (ret < 0)
        return -1;

    prep_info.direction = DMA_DEV_TO_MEM;
    prep_info.mode = DMA_SLAVE;
    prep_info.dst = virt_to_phys(buf);
    prep_info.len = len;
    prep_info.callback = cdns_i2s_mc_rx_dma_cb;
    prep_info.callback_param = dev;
    dev->dma.rx_cookie = itcs_dma_prepare(dev->dma.rx_chan, &prep_info);
    if (dev->dma.rx_cookie < 0)
        return -1;

    itcs_dcache_flush();
    //itcs_dcache_clean();

    if (dev->para.ms_cfg == I2S_CFG_RX_MASTER)
    {
        cdns_i2s_mc_start(dev);
        udelay(10);
        itcs_dma_start(dev->dma.rx_chan);
    }


    return 0;
}

static int __cdns_i2s_mc_tx_int(struct cdns_i2s_mc *dev, uint8_t *buf, uint32_t len)
{
    uint32_t xfer_len, fifo_lvl;
    uint32_t tmp;

    if (!buf)
        return -1;

    if (!len) {
        cdns_i2s_mc_end_tx(dev);
        return 0;
    }

    if (!dev->buf.tx_len)
        len /= dev->data_width;

    fifo_lvl = cdns_i2s_mc_readl(dev->base, I2S_MC_TFIFO_STAT);
    xfer_len = min(len, dev->fifo_depth - fifo_lvl);
    DEBUG_I2S_MC_LOG("tx: xfer_len = %d\n",xfer_len);
    for (int i = 0; i < xfer_len; i++) {
        memcpy(&tmp, buf, dev->data_width);
        //DEBUG_I2S_MC_LOG("tmp = %x\n", tmp);
        cdns_i2s_mc_writel(dev->base, I2S_MC_TX_FIFO, tmp);
        buf += dev->data_width;
    }

    if (!dev->buf.tx_len) {
        dev->buf.tx_len = len - xfer_len;
        dev->buf.tx_buf = buf; // TODO: buf maybe on the stack, may not be used in global.
        cdns_i2s_mc_irq_clr(dev);

        if (dev->buf.tx_len)
        {
            tmp = dev->aempty_threshold << I2S_MC_AEMPTY_OFFSET;
            cdns_i2s_mc_writel(dev->base, I2S_MC_TFIFO_CTRL, tmp);
        }
            
        cdns_i2s_mc_bit_set(dev->base, I2S_MC_INTR_STAT, I2S_MC_INTREQ_TX_MASK);
        
        //if (dev->para.ms_cfg == I2S_CFG_TX_MASTER && dev->para.loop_back == I2S_LOOP_BACK_MODE)
        if (dev->para.ms_cfg == I2S_CFG_TX_MASTER)
        {
            cdns_i2s_mc_irq_en(dev);
            cdns_i2s_mc_start(dev);
        }
        
        return 0;
    }

    dev->buf.tx_len -= xfer_len;
    dev->buf.tx_buf = buf;
    if (!dev->buf.tx_len) {
        //tx_padding(dev);
        cdns_i2s_mc_bit_reset(dev->base, I2S_MC_CID_CRTL, I2S_MC_TFIFO_AEMPTY_MASK);
    }
    return 0;
}

static int cdns_i2s_mc_tx(int id, uint8_t *buf, uint32_t len)
{
    struct cdns_i2s_mc *dev = get_mc_dev_by_id(id);

    if (!dev)
        return -1;
    
    dev->buf.tx_done = 0;

    //return __cdns_i2s_mc_tx_int(dev, buf, len);

    if (dev->para.mode == I2S_MC_XFER_INTERRUPT) {
        return __cdns_i2s_mc_tx_int(dev, buf, len);
    } else if (dev->para.mode == I2S_MC_XFER_DMA) {
        return __cdns_i2s_mc_tx_dma(dev, buf, len);
    }else{
        return -1;
    }
}

static int __cdns_i2s_mc_rx_int(struct cdns_i2s_mc *dev, uint8_t *buf, uint32_t len)
{
    uint32_t xfer_len, fifo_lvl;
    uint32_t tmp = 0;
    uint32_t afull = 0;

    if (!buf)
        return -1;

    if (!len) {
        cdns_i2s_mc_end_rx(dev);
        return 0;
    }

    if (!dev->buf.rx_len) {
        /* It means it's our first running. */
        dev->buf.rx_len = len / dev->data_width;
        dev->buf.rx_buf = buf; // TODO: buf maybe on the stack, may not be used in global.
        cdns_i2s_mc_irq_clr(dev);

        afull = dev->afull_threshold << I2S_MC_AFULL_OFFSET;
        cdns_i2s_mc_writel(dev->base, I2S_MC_RFIFO_CTRL, afull);
        cdns_i2s_mc_bit_set(dev->base, I2S_MC_CID_CRTL, I2S_MC_INTREQ_RX_MASK);
        
        if (dev->para.ms_cfg == I2S_CFG_RX_MASTER)
        {
            cdns_i2s_mc_irq_en(dev);
            cdns_i2s_mc_start(dev);
        }
        return 0;
    }


    fifo_lvl = cdns_i2s_mc_readl(dev->base, I2S_MC_RFIFO_STAT);
    if (fifo_lvl == dev->fifo_depth)
    {
        printf("rx may be timeout\n");
    }

    xfer_len = fifo_lvl;
    DEBUG_I2S_MC_LOG("rx: fifo_lvl = %d, len = %d\n",fifo_lvl, len);
    for (int i = 0; i < xfer_len; i++) {
    //while(1){
        tmp = cdns_i2s_mc_readl(dev->base, I2S_MC_RX_FIFO);
        if (tmp == 0)
        {
            continue;
        }
        DEBUG_I2S_MC_LOG("tmp = %x\n", tmp);
        memcpy(buf, (void *)&tmp, dev->data_width);
        buf += dev->data_width;
        dev->buf.rx_len --;
    }

    if ((signed int)dev->buf.rx_len < 0)
    {
        dev->buf.rx_len = 0;
    }

    //dev->buf.rx_len -= min(len, fifo_lvl);
    dev->buf.rx_buf = buf; // TODO: buf maybe on the stack, may not be used in global.
    //afull =  min(dev->buf.rx_len, dev->afull_threshold) << I2S_MC_AFULL_OFFSET;
    //cdns_i2s_mc_writel(dev->base, I2S_MC_RFIFO_CTRL, afull);

    return 0;
}

static int cdns_i2s_mc_rx(int id, uint8_t *buf, uint32_t len)
{
    struct cdns_i2s_mc *dev = get_mc_dev_by_id(id);

    if (!dev)
        return -1;

    dev->buf.rx_done = 0;
        

    if (dev->para.mode == I2S_MC_XFER_INTERRUPT) {
        return __cdns_i2s_mc_rx_int(dev, buf, len);
    } else if (dev->para.mode == I2S_MC_XFER_DMA){
        len = max(len, 480); 
        return __cdns_i2s_mc_rx_dma(dev, buf, len);
    }else{
        return -1;
    }
}


static void i2s_mc_print_buf(unsigned int *buf, int len)
{
    int i;
    while(len)
    {
        for(i = 0; i < 4; i++)
        {
            printf("%x ", *buf);
            buf++;
            len--;
        }
        printf("\n");
    }
}

extern uint32_t __lds_soc_base[];
#define CODEC_TEST_CH 8
#define CODEC_TEST_BUF ((unsigned long)__lds_soc_base + 0x10000000)
#define TEST_DATA_CODEC_SIZE (1024 * 500)

int cdns_i2s_mc_codec(int id)
{
    struct cdns_i2s_mc *dev = get_mc_dev_by_id(id);
    //volatile unsigned int tmp;
    int count = 0;
    int i, buf_loop, len;
    unsigned int *rbuf[CODEC_TEST_CH];
    unsigned int *buf_tmp;
    volatile unsigned int fifo_lvl;

    if (dev == NULL)
    {
        return -1;
    }

    for(i = 0; i < CODEC_TEST_CH; ++i)
    {
        rbuf[i] = (unsigned int*)(unsigned long)(CODEC_TEST_BUF + i * TEST_DATA_CODEC_SIZE);
    }

    memset((void*)CODEC_TEST_BUF, 0x5a, TEST_DATA_CODEC_SIZE);

    cdns_i2s_mc_rfifo_reset(dev);
    cdns_i2s_mc_start(dev);

    len = TEST_DATA_CODEC_SIZE * CODEC_TEST_CH / dev->data_width;

    while(count < len){
        fifo_lvl = cdns_i2s_mc_readl(dev->base, I2S_MC_RFIFO_STAT);
        fifo_lvl = min(fifo_lvl, len - count);
        for (i = 0; i < fifo_lvl; ++i)
        {
            buf_loop = count % CODEC_TEST_CH;
            buf_tmp = (unsigned int *)rbuf[buf_loop];
            *buf_tmp = cdns_i2s_mc_readl(dev->base, I2S_MC_RX_FIFO);
            //rbuf[buf_loop] += dev->data_width;
            rbuf[buf_loop]++;
            count ++;
        }
    }

    for(i = 0; i < CODEC_TEST_CH; ++i)
    {
        rbuf[i] = (unsigned int*)(unsigned long)(CODEC_TEST_BUF + i * TEST_DATA_CODEC_SIZE);
        printf("==========\n");
        i2s_mc_print_buf(rbuf[i], 8);
    }

    printf("i2s mc read end\n");
    dev->buf.rx_done = 1;

    return 0;
}

static int cdns_i2s_mc_check_done(int id)
{
    struct cdns_i2s_mc *dev = get_mc_dev_by_id(id);

    if (!dev)
        return 0;

    return dev->buf.rx_done;
}

static int cdns_i2s_mc_remove(int id)
{
    struct cdns_i2s_mc *dev = get_mc_dev_by_id(id);

    if (!dev)
        return 0;

    cdns_i2s_mc_writel(dev->base, I2S_MC_CTRL, 0);

    /*for test, no free*/
    return 0;

    free(dev);
    set_mc_dev_by_id(id, NULL);

    return 0;
}

static struct i2s_mc_ops cdns_i2s_mc_ops = {
    .tx           = cdns_i2s_mc_tx,
    .rx           = cdns_i2s_mc_rx,
    .config       = cdns_i2s_mc_config,
    .check_done   = cdns_i2s_mc_check_done,
    .probe        = cdns_i2s_mc_probe,
    .remove       = cdns_i2s_mc_remove,
    .codec        = cdns_i2s_mc_codec
};

int i2s_mc_init(int id)
{
    int ret;

    struct cdns_i2s_mc *dev = get_mc_dev_by_id(id);
    if (dev != NULL)
    {
        printf("the device already exist\n");
        return 0;
    }

    dev = (struct cdns_i2s_mc *)malloc(sizeof(struct cdns_i2s_mc));
    if(dev == NULL)
    {
        printf("malloc struct cdns_i2s_mc failed\n");
        return -1;
    }
    memset(dev, 0, sizeof(struct cdns_i2s_mc));

    dev->ops = &cdns_i2s_mc_ops;
    dev->id = id;
    set_mc_dev_by_id(id, dev);

    ret = dev->ops->probe(id);
    if(ret)
    {
        free(dev);
        set_mc_dev_by_id(id, NULL);
        return ret;
    }
    
    return 0;
}

int i2s_mc_get_ops(struct i2s_mc_ops **ops)
{
    *ops = &cdns_i2s_mc_ops;
    return 0;
}

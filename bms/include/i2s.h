#pragma once

//#define DEBUG_I2S

#ifdef DEBUG_I2S
#define DEBUG_I2S_LOG(format, ...) printf(format, ##__VA_ARGS__)
#else
#define DEBUG_I2S_LOG(format, ...)
#endif

#include <asm/bits.h>

#define I2S_FUNC_ENABLE     1
#define I2S_FUNC_DISABLE    0

struct i2s_tdm_para {
    uint32_t tdm_en;              /*1:tmd mode 0:stereo mode*/
    uint32_t ws_mode;             /*0-channels-1, the time for ws signal to remain high level*/
    uint32_t inactive_channels;   /*bit 0-15 for channel0-15*/
};

struct i2s_para {
    uint32_t id;
    uint32_t sample_freq;    /* sample frequence */
    uint32_t bitspersample;	 /* bits per sample */
    uint32_t channels;       /* audio channels */
    struct {
#define I2S_MASTER             BIT(0)
#define I2S_SLAVE              BIT(1)
#define I2S_TRANSMIT           BIT(2)
#define I2S_RECEIVE            BIT(3)
#define I2S_HALF_DUPLEX        BIT(4)
#define I2S_FULL_DUPLEX        BIT(5)
#define I2S_XFER_BLOCKING      BIT(6)
#define I2S_XFER_INTERRUPT     BIT(7)
#define I2S_XFER_DMA           BIT(8)
        uint32_t mode;

#define SND_SOC_DAIFMT_I2S     BIT(9)  /* I2S mode */
#define SND_SOC_DAIFMT_RIGHT_J BIT(10) /* Right Justified mode */
#define SND_SOC_DAIFMT_LEFT_J  BIT(11) /* Left Justified mode */
#define SND_SOC_DAIFMT_DSP_A   BIT(12) /* L data MSB after FRM LRC */
#define SND_SOC_DAIFMT_DSP_B   BIT(13) /* L data MSB during FRM LRC */
#define SND_SOC_DAIFMT_AC97    BIT(14) /* AC97 */
#define SND_SOC_DAIFMT_PDM     BIT(15) /* Pulse density modulation */
        uint32_t standard;
    };
    struct i2s_tdm_para tdm;
    uint32_t pads_index;
    uint32_t dma_burstlen;
};

struct i2s_ops {
    int (*tx)(int id, uint8_t *buf, uint32_t len /* Bytes */);
    int (*rx)(int id, uint8_t *buf, uint32_t len /* Bytes */);
    int (*tx_rx)(int id, uint8_t *tbuf, uint8_t *rbuf, uint32_t len /* Bytes */);

    int (*config)(int id, const struct i2s_para *para);
    int (*check_done)(int id);
    void (*__writel)(int id, uint32_t reg, uint32_t val);
    uint32_t (*__readl)(int id, uint32_t reg);
};

enum {
    I2S0,
    I2S1
};

#ifdef CONFIG_DRV_I2S
extern int i2s_get_ops(struct i2s_ops **ops);
extern int i2s_init(const struct i2s_para *para);

#else
static inline int i2s_get_ops(struct i2s_ops **ops) { return -1; }
static inline int i2s_init(const struct i2s_para *para) { return -1; }

#endif

//#define I2S_PLAY_MI2S_PCM
#ifdef I2S_PLAY_MI2S_PCM
extern int mi2s_play_channel;
#endif

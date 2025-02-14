#ifndef I2S_MC_H
#define I2S_MC_H

#include <asm/bits.h>

#define I2S_MC_CHANNEL_CNT      8

#define I2S_CFG_TX_MASTER       1
#define I2S_CFG_RX_MASTER       0

#define I2S_LOOP_BACK_MODE      1
#define I2S_NORMAL_MODE         0

enum i2s_mc_standard {
    SND_SOC_DAIFMT_I2S,         /* I2S mode */
    SND_SOC_DAIFMT_RIGHT_J,     /* Right Justified mode */
    SND_SOC_DAIFMT_LEFT_J,      /* Left Justified mode */
    SND_SOC_DAIFMT_DSP,         /* L data MSB after FRM LRC */
    SND_SOC_DAIFMT_DEFAULT      /* default: i2s mode */
};

enum i2s_mc_mode {
    I2S_MC_XFER_BLOCKING,       /*no use*/
    I2S_MC_XFER_INTERRUPT,      /*int mode*/
    I2S_MC_XFER_DMA             /*dma mode*/
};

struct i2s_mc_para {
    uint32_t ch_cnt;            /* channels count*/
    uint32_t sample_freq;       /* sample frequence */
    uint32_t bitspersample;	    /* bits per sample */
    enum i2s_mc_standard standard;
    enum i2s_mc_mode mode;
    uint32_t ms_cfg;                            /*1- tx master; 0- rx master*/
    uint32_t ch_tr_cfg[I2S_MC_CHANNEL_CNT];     /*1- tx; 0- rx*/
    uint32_t loop_back;                         /*1- loop back; 0- normal */
    uint32_t test_codec;                        /*1- codec test; 0- normal */
};

struct i2s_mc_ops {
    int (*tx)(int id, uint8_t *buf, uint32_t len /* Bytes */);
    int (*rx)(int id, uint8_t *buf, uint32_t len /* Bytes */);
    int (*config)(int id, const struct i2s_mc_para *para);
    int (*check_done)(int id);
    int (*remove)(int id);
    int (*probe)(int id);
    int (*codec)(int id);
};


extern int i2s_mc_get_ops(struct i2s_mc_ops **ops);
extern int i2s_mc_init(int id);
extern int i2s_mc_codec_probe();

#endif
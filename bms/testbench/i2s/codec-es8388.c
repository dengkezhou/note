#include <common.h>
#include <command.h>
#include <testbench.h>
#include <malloc.h>
#include <asm/io.h>
#include <i2s.h>
#include <pads.h>
#include <asm/bits.h>
#include <dma-ops.h>

extern int es8388_codec_init(void);
extern void es8388_standby(void);
extern void es8388_resume(void);
extern void es_read_all(void);

#ifndef I2S_PLAY_MI2S_PCM
static struct i2s_para es8388_i2s_para = {
  .bitspersample = 16,
  .channels = 2,
  .sample_freq = 48000,
  .standard = SND_SOC_DAIFMT_I2S,
};
#else
/* test play mi2s */
static struct i2s_para es8388_i2s_para = {
  .bitspersample = 32,
  .channels = 2,
  .sample_freq = 24000,
  .standard = SND_SOC_DAIFMT_I2S,
};

int mi2s_play_channel = 0;
extern uint32_t __lds_soc_base[];
#define MI2S_BUF_BASE_ADDR ((unsigned long)__lds_soc_base + 0x10000000)
#endif

#define ES8388_IN_BUF_LEN (1024U * 200)
static uint8_t *es8388_in_buf = NULL;
static struct i2s_ops *es8388_i2s_ops = NULL;

int es8388_test_init(void)
{
  if (es8388_codec_init() < 0)
      return -1;

  i2s_get_ops(&es8388_i2s_ops);
  if (!es8388_i2s_ops)
    return -1;

  es8388_in_buf = malloc(ES8388_IN_BUF_LEN);
  if (!es8388_in_buf) {
    printf("es8388 tb malloc buf failed, try CONFIG_TB_RUN_DDR\n");
    return -1;
  }

  return 0;
}

int es8388_play(int id)
{
  if (!es8388_i2s_ops)
    return -1;

  es8388_i2s_para.mode = I2S_MASTER | I2S_HALF_DUPLEX | I2S_TRANSMIT,
  es8388_i2s_ops->config(id, &es8388_i2s_para);

  if (es8388_i2s_para.mode & I2S_XFER_DMA) {
    if (!itcs_is_dma_inited(0))
      itcs_dma_init(0);
  }

  printf("es8388_play i2s = %d\n", id);

#ifndef I2S_PLAY_MI2S_PCM
  es8388_i2s_ops->tx(id, es8388_in_buf, ES8388_IN_BUF_LEN);
#else
  int *buf = (int *)(MI2S_BUF_BASE_ADDR + mi2s_play_channel * 1024 * 500);
  printf("===channel = %d, addr = %lx\n", mi2s_play_channel, buf);
  es8388_i2s_ops->tx(id, (void *)buf, 1024 * 500);
#endif

  return 0;
}

int es8388_record(int id)
{
  if (!es8388_i2s_ops)
    return -1;
  es8388_i2s_para.mode = I2S_MASTER | I2S_HALF_DUPLEX | I2S_RECEIVE,
  es8388_i2s_ops->config(id, &es8388_i2s_para);

  if (es8388_i2s_para.mode & I2S_XFER_DMA) {
    if (!itcs_is_dma_inited(0))
      itcs_dma_init(0);
  }

  printf("es8388_record i2s = %d\n", id);
  es8388_i2s_ops->rx(id, es8388_in_buf, ES8388_IN_BUF_LEN);
  return 0;
}

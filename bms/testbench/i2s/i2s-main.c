#include <common.h>
#include <command.h>
#include <testbench.h>
#include <malloc.h>
#include <asm/io.h>
#include <getopt.h>
#include <i2s.h>
#include <pads.h>
#include <asm/bits.h>
#include <dma-ops.h>
#include <cache.h>

#ifdef CONFIG_DRV_CODEC_ES8388
extern int es8388_test_init(void);
extern int es8388_play(int id);
extern int es8388_record(int id);
#endif


#define TEST_DATA_SIZE 4096
static uint8_t g_wbuf[TEST_DATA_SIZE];
static uint8_t g_rbuf0[TEST_DATA_SIZE];
static uint8_t g_rbuf1[TEST_DATA_SIZE];
static struct i2s_ops *i2s_ops = NULL;
static bool is_inited = false;

static int test_buf_init(void)
{
  for (uint32_t i = 0; i < ARRAY_SIZE(g_wbuf); i++)
  {
    g_wbuf[i] = (uint8_t)(i & 0xff);
    if (i % 0x100 == 0)
    {
      g_wbuf[i] = 1;
    }
  }

  memset(g_rbuf0, 0xa5, sizeof(g_rbuf0));
  memset(g_rbuf1, 0x5a, sizeof(g_rbuf1));

  return 0;
}

static void print_result(int master, const struct i2s_para *master_para,
    int slave, const struct i2s_para *slave_para, int test_len, int ret)
{
  char *s;
  
  if (master_para->standard & SND_SOC_DAIFMT_RIGHT_J)
    s = " Right Justified mode, ";
  else if (master_para->standard & SND_SOC_DAIFMT_LEFT_J)
    s =  " Left Justified mode, ";
  else if (master_para->standard & (SND_SOC_DAIFMT_DSP_A | SND_SOC_DAIFMT_DSP_B))
    s = " DSP mode, ";
  else
    s = " ";

  printf("%s Duplex,%s%s Mode, Test Size: %d Bytes, %s Master %s, pads index %d, %s Slave %s, pads index %d, %s\n",
      master_para->mode & I2S_FULL_DUPLEX ? "Full" : "Half",
      s,
      master_para->mode & I2S_XFER_DMA ? "DMA" : "Interrupt",
      test_len,
      master == I2S0 ? "I2S0" : "I2S1",
      master_para->mode & I2S_TRANSMIT ? "Transmit" : "Receive",
      master_para->pads_index,
      slave == I2S0 ? "I2S0" : "I2S1",
      slave_para->mode & I2S_TRANSMIT ? "Transmit" : "Receive",
      slave_para->pads_index,
      ret < 0 ? "Failed" : "Pass");

  if (!ret)
    return;

  printf("\ng_rbuf0:\n");
  for (uint32_t i = 0; i < test_len; i++) {
    if (i % 16 == 0)
      printf("\n");
    printf("0x%x ", g_rbuf0[i]);
  }
  printf("\n");
}

static int i2s_half_duplex_test(const struct i2s_para *master_para,
    const struct i2s_para *slave_para, int test_len)
{
  int master, slave;
  int ret = 0, retry = 2000;

  if (!master_para || !slave_para)
    return -1;

  test_buf_init();

  master = master_para->id;
  slave = slave_para->id;

  i2s_ops->config(master, master_para);
  i2s_ops->config(slave, slave_para);

  if ((master_para->mode & I2S_TRANSMIT) && (slave_para->mode & I2S_RECEIVE)) {
    i2s_ops->rx(slave, g_rbuf0, test_len);
    i2s_ops->tx(master, g_wbuf, test_len);
    printf("Waiting for I2S done...\n");
    while(!(i2s_ops->check_done(master) && i2s_ops->check_done(slave)) && retry) {
      udelay(10);
      retry--;
    }
  } else if ((master_para->mode & I2S_RECEIVE) && (slave_para->mode & I2S_TRANSMIT)) {
    i2s_ops->tx(slave, g_wbuf, test_len);
    i2s_ops->rx(master, g_rbuf0, test_len);
    printf("Waiting for I2S done...\n");
    while(!(i2s_ops->check_done(slave) && i2s_ops->check_done(master)) && retry) {
      udelay(10);
      retry--;
    }
  } else {
    printf("I2S test: Invalid mode\n");
    return -1;
  }

  if (!retry)
    printf("I2S time out\n");

  i2s_ops->__writel(master, 0, 0);

  itcs_dcache_flush();

  if (memcmp(g_rbuf0, g_wbuf, test_len * sizeof(*g_wbuf)))
    ret = -1;

  print_result(master, master_para, slave, slave_para, test_len, ret);
  return 0;
}


static int i2s_full_duplex_test(const struct i2s_para *master_para,
    const struct i2s_para *slave_para, int test_len /* Words */)
{
  int master, slave;
  int ret = 0, retry = 2000;

  if (!master_para || !slave_para)
    return -1;

  test_buf_init();

  master = master_para->id;
  slave = slave_para->id;

  i2s_ops->config(master, master_para);
  i2s_ops->config(slave, slave_para);

  i2s_ops->tx_rx(slave, g_wbuf, g_rbuf0, test_len);
  i2s_ops->tx_rx(master, g_wbuf, g_rbuf1, test_len);

  printf("Waiting for I2S done...\n");

  while(!(i2s_ops->check_done(master) && i2s_ops->check_done(slave)) && retry) {
      udelay(10);
      retry--;
  }

  if (!retry)
    printf("I2S time out\n");

  i2s_ops->__writel(master, 0, 0);

  if ((memcmp(g_rbuf1, g_wbuf, test_len * sizeof(*g_wbuf)) &&
      (memcmp(g_rbuf0, g_wbuf, test_len * sizeof(*g_wbuf)))))
    ret = -1;

  print_result(master, master_para, slave, slave_para, test_len, ret);
  return 0;
}

static void i2s_show_usage(void) {
  printf("Usage: i2s [OPTION]...\n\n");
  printf("-h \t\t\t command help\n");
  printf("-x \t\t\t Set mux in RTL test\n");
  printf("-f \t\t\t Full duplex mode\n");
  printf("-m <0|1> \t\t\t Set I2S0/I2S1 as Master, the other as Slave\n");
  printf("-o <0|1> \t\t\t Set transceiver mode\n");
  printf("-n <Size> \t\t\t Set test size\n");
  printf("-d \t\t\t Enable DMA\n");
  printf("-t <standard>\t\t\t Set I2S standard\n");
  printf("-v -c <0-16> -w<0-15> \t\t\t Set I2S TDM mode\n");
#ifdef CONFIG_DRV_CODEC_ES8388
  printf("-p\t\t\t ES8388 Play\n");
  printf("-r\t\t\t ES8388 Record\n");
#endif

}

static int atoi(char *s) {
  int i;
  int n = 0;
  for (i = 0; s[i] >= '0' && s[i] <= '9'; ++i) {
    n = 10 * n + (s[i] - '0');
  }
  return n;
}

#define I2S0_MUX_0_PADS PADSRANGE(33, 37)
#define I2S0_MUX_0_FUNC PADS_FUNC2
#define I2S1_MUX_0_PADS PADSRANGE(38, 42)
#define I2S1_MUX_0_FUNC PADS_FUNC2

#define I2S0_MUX_1_PADS PADSRANGE(49, 53)
#define I2S0_MUX_1_FUNC PADS_FUNC2
#define I2S1_MUX_1_PADS PADSRANGE(54, 58)
#define I2S1_MUX_1_FUNC PADS_FUNC2

#define I2S0_MUX_2_PADS PADSRANGE(84, 88)
#define I2S0_MUX_2_FUNC PADS_FUNC0
#define I2S1_MUX_2_PADS PADSRANGE(89, 93)
#define I2S1_MUX_2_FUNC PADS_FUNC0

static void i2s_set_mux(int mux)
{
  int range0, range1;
  uint32_t fm0, fm1;

  switch (mux) {
  case 1:
    range0 = I2S0_MUX_1_PADS;
    range1 = I2S1_MUX_1_PADS;
    fm0 = I2S0_MUX_1_FUNC;
    fm1 = I2S1_MUX_1_FUNC;
    break;
  case 2:
    range0 = I2S0_MUX_2_PADS;
    range1 = I2S1_MUX_2_PADS;
    fm0 = I2S0_MUX_2_FUNC;
    fm1 = I2S1_MUX_2_FUNC;
    break;
  case 0:
  default:
    range0 = I2S0_MUX_0_PADS;
    range1 = I2S1_MUX_0_PADS;
    fm0 = I2S0_MUX_0_FUNC;
    fm1 = I2S1_MUX_0_FUNC;
    break;
  }

  itcs_pads_set_mode(CPU, I2S0_MUX_0_PADS, PADS_MODE_IN, 1);
  itcs_pads_set_mode(CPU, I2S0_MUX_1_PADS, PADS_MODE_IN, 1);
  itcs_pads_set_mode(CPU, I2S0_MUX_2_PADS, PADS_MODE_IN, 1);
  itcs_pads_set_mode(CPU, I2S1_MUX_0_PADS, PADS_MODE_IN, 1);
  itcs_pads_set_mode(CPU, I2S1_MUX_1_PADS, PADS_MODE_IN, 1);
  itcs_pads_set_mode(CPU, I2S1_MUX_2_PADS, PADS_MODE_IN, 1);

  itcs_pads_set_mode(CPU, range0, PADS_MODE_FUNC, fm0);
  itcs_pads_set_pull(CPU, range0, 1, PADS_PULL_UP);
  itcs_pads_set_mode(CPU, range1, PADS_MODE_FUNC, fm1);
  itcs_pads_set_pull(CPU, range1, 1, PADS_PULL_UP);
}

static int i2s_test_main(int argc, char *argv[]) {
  int c, tmp;
  int test_len = TEST_DATA_SIZE;
  int option_index = 0;
  int channels_num = 2, ws_mode;
  int play = 0, record = 0;
  int dma_burstlen;

  const uint32_t standard[] = {
    SND_SOC_DAIFMT_I2S, SND_SOC_DAIFMT_RIGHT_J,
    SND_SOC_DAIFMT_LEFT_J, SND_SOC_DAIFMT_DSP_A
  };

  struct i2s_para master_para = {
    .id = I2S0,
    .mode = I2S_MASTER,
    .bitspersample = 16,
    .channels = 2,
    .sample_freq = 48000,
    .standard = SND_SOC_DAIFMT_I2S,
    .tdm.tdm_en = I2S_FUNC_DISABLE,
    .pads_index = 1,
    .dma_burstlen = 32,
  };
  struct i2s_para slave_para = {
    .id = I2S1,
    .mode = I2S_SLAVE,
    .bitspersample = 16,
    .channels = 2,
    .sample_freq = 48000,
    .standard = SND_SOC_DAIFMT_I2S,
    .tdm.tdm_en = I2S_FUNC_DISABLE,
    .pads_index = 1,
    .dma_burstlen = 32,
  };

  static const char short_options[] = "m:x:o:n:t:c:w:a:b:l:z:vfdprh";
  static const struct option long_options[] = {
        { 0, 0, 0, 0 },
    };

	while ((c = getopt_long(argc, argv, short_options, long_options,
				&option_index)) != -1) {
    switch (c) {
    case 'f':
      master_para.mode &= ~I2S_HALF_DUPLEX;
      master_para.mode |= I2S_FULL_DUPLEX;
      slave_para.mode &= ~I2S_HALF_DUPLEX;
      slave_para.mode |= I2S_FULL_DUPLEX;
      break;
    case 'x':
      i2s_set_mux(atoi(optarg));
      break;
    case 'm':
      if (atoi(optarg)) {
        master_para.id = I2S1;
        slave_para.id = I2S0;
      } else {
        master_para.id = I2S0;
        slave_para.id = I2S1;
      }
      break;

    case 'o':
      master_para.mode &= ~I2S_FULL_DUPLEX;
      slave_para.mode &= ~I2S_FULL_DUPLEX;
      if (atoi(optarg)) {
        master_para.mode |= I2S_RECEIVE | I2S_HALF_DUPLEX;
        slave_para.mode |= I2S_TRANSMIT | I2S_HALF_DUPLEX;
      } else {
        master_para.mode |= I2S_TRANSMIT | I2S_HALF_DUPLEX;
        slave_para.mode |= I2S_RECEIVE | I2S_HALF_DUPLEX; 
      }
      break;
    case 'n':
      test_len = atoi(optarg) & (~1UL);
      if (test_len > TEST_DATA_SIZE || test_len <= 0)
        test_len = TEST_DATA_SIZE;
      break;

    case 'd':
      master_para.mode |= I2S_XFER_DMA;
      slave_para.mode |= I2S_XFER_DMA;
      break;
    
    case 't':
      tmp = atoi(optarg);
      master_para.standard = slave_para.standard =
          standard[tmp >= ARRAY_SIZE(standard) ? 0 : tmp];
      break;
    
    case 'v':
      master_para.tdm.tdm_en = I2S_FUNC_ENABLE;
      slave_para.tdm.tdm_en = I2S_FUNC_ENABLE;
      master_para.sample_freq = 12000;
      master_para.sample_freq = 12000;
      break;

    case 'c':
      channels_num = atoi(optarg);
      if (channels_num <= 0 || channels_num > 16)
      {
        printf("channels_num %d is invaild\n", channels_num);
        return -1;
      }
      master_para.channels = channels_num;
      slave_para.channels = channels_num;
      break;

    case 'w':
      ws_mode = atoi(optarg) & (~1UL);
      if (ws_mode < 0 || ws_mode >= channels_num)
      {
          printf("ws_mode %d is invaild, channels_num = %d\n", ws_mode, channels_num);
          return -1;
      }
      master_para.tdm.ws_mode = ws_mode;
      slave_para.tdm.ws_mode = ws_mode;
      break;

    case 'a':
      master_para.pads_index = atoi(optarg);
      break;

    case 'b':
      slave_para.pads_index = atoi(optarg);
      break;

    case 'p':
      play = 1;
      break;

#ifdef I2S_PLAY_MI2S_PCM
    case 'z':
      mi2s_play_channel = atoi(optarg);
      break;
#endif

    case 'r':
      record = 1;
      break;

    case 'l':
      dma_burstlen = atoi(optarg);
      master_para.dma_burstlen = dma_burstlen;
      slave_para.dma_burstlen = dma_burstlen;
      break;

    case 'h':
    default:
      i2s_show_usage();
      goto exit;
    }
  }

  if (!is_inited) {
  #ifdef CONFIG_DRV_CODEC_ES8388
    if (play || record)
    {
      if (es8388_test_init() < 0)
        return -1;
    }
  #endif

    if (i2s_init(&slave_para) < 0)
      return -1;

    if (i2s_init(&master_para) < 0)
      return -1;

    is_inited = true;
  }

  i2s_get_ops(&i2s_ops);
  if (!i2s_ops)
    return -1;

  if (master_para.mode & I2S_XFER_DMA) {
    if (!itcs_is_dma_inited(0))
      itcs_dma_init(0);
  }

  if (play)
  {
#ifdef CONFIG_DRV_CODEC_ES8388
    es8388_play(master_para.id);
#endif
    goto exit;
  }

  if (record)
  {
#ifdef CONFIG_DRV_CODEC_ES8388
    es8388_record(master_para.id);
#endif
    goto exit;
  }


  if (master_para.mode & I2S_HALF_DUPLEX)
    i2s_half_duplex_test(&master_para, &slave_para, test_len);
  else
    i2s_full_duplex_test(&master_para, &slave_para, test_len);

exit:
  optind = 1;
  return 0;
}

static void i2s_test_init(void) {
  register_testbench("i2s", i2s_test_main, NULL);
}

testbench_init(i2s_test_init);

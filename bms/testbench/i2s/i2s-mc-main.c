#include <common.h>
#include <command.h>
#include <testbench.h>
#include <malloc.h>
#include <asm/io.h>
#include <getopt.h>
#include <i2s-mc.h>
#include <pads.h>
#include <asm/bits.h>
#include <dma-ops.h>
#include <cache.h>

#define TEST_DATA_SIZE 512

static uint8_t *g_wbuf = NULL;
static uint8_t *g_rbuf0 = NULL;
static uint8_t *g_rbuf1 = NULL;

static int test_buf_init(void)
{
  if(g_wbuf == NULL)
  {
    g_wbuf = (uint8_t *)malloc(TEST_DATA_SIZE);
    if(g_wbuf == NULL)
    {
      printf("malloc g_wbuf failed\n");
      return -1;
    }
  }
    
  if(g_rbuf0 == NULL)
  {
    g_rbuf0 = (uint8_t *)malloc(TEST_DATA_SIZE);
    if(g_rbuf0 == NULL)
    {
      printf("malloc g_rbuf0 failed\n");
      return -1;
    }
  }

  if(g_rbuf1 == NULL)
  {
    g_rbuf1 = (uint8_t *)malloc(TEST_DATA_SIZE);
    if(g_rbuf1 == NULL)
    {
      printf("malloc g_rbuf1 failed\n");
      return -1;
    }
  }

  for (uint32_t i = 0; i < TEST_DATA_SIZE; i++)
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

static void i2s_mc_print_result(const struct i2s_mc_para *i2s_para, int test_len, int ret)
{
  char *s;
  
  if (i2s_para->standard == SND_SOC_DAIFMT_RIGHT_J)
    s = " Right Justified mode, ";
  else if (i2s_para->standard == SND_SOC_DAIFMT_LEFT_J)
    s =  " Left Justified mode, ";
  else if (i2s_para->standard == SND_SOC_DAIFMT_DSP)
    s = " DSP mode, ";
  else
    s = " ";

  printf("%s mode,%s%s Mode, Test Size: %d Bytes, %s\n",
      i2s_para->loop_back == I2S_LOOP_BACK_MODE ? "loop back " : "normal",
      s,
      i2s_para->mode == I2S_MC_XFER_DMA ? "DMA" : "Interrupt",
      test_len,
      ret < 0 ? "Failed" : "Pass");

#ifdef I2S_TB_DEBUG
  printf("\ng_rbuf0:\n");
  for (uint32_t i = 0; i < ARRAY_SIZE(g_wbuf); i++) {
    printf("0x%x ", g_rbuf0[i]);
    if (i % 8 == 0)
      printf("\n");
  }

  printf("\ng_rbuf1:\n");
  for (uint32_t i = 0; i < ARRAY_SIZE(g_wbuf); i++) {
    printf("0x%x ", g_rbuf1[i]);
    if (i % 8 == 0)
      printf("\n");
  }
  printf("\n");
#endif
}

static void arr_remove_zero(unsigned char *buf, int len)
{
    int i, j = 0;
    int tmp;

    for(i = 0; i < len; i++){
        tmp = buf[i];
        if (tmp != 0)
        {
            buf[j] = tmp;
            j++;
        }
    }

    memset(buf + j, 0, len - j);
}


static int i2s_mc_test(int id, const struct i2s_mc_para *i2s_para, int test_len)
{
  int ret = 0, retry = 2000;
  struct i2s_mc_ops *ops = NULL;

  if (!i2s_para)
    return -1;

  test_buf_init();

  ret = i2s_mc_init(id);
  if (ret)
  {
    return ret;
  }

  i2s_mc_get_ops(&ops);
  if (!ops)
    return -1;

  ops->config(id, i2s_para);

  if (i2s_para->test_codec == 1)
  {
    ops->codec(id);
    printf("codec test over\n");
    return 0;
  }

  if (i2s_para->ms_cfg == I2S_CFG_TX_MASTER){
    ops->rx(id, g_rbuf0, test_len);
    ops->tx(id, g_wbuf, test_len);
  }else
  {
    ops->tx(id, g_wbuf, test_len);
    ops->rx(id, g_rbuf0, test_len);
  }

  printf("Waiting for I2S done...\n");
  while(!ops->check_done(id) && retry) {
    udelay(10);
    retry--;
  }

  if (!retry)
    printf("I2S time out\n");

  ops->remove(id);

  itcs_dcache_flush_range((phys_addr_t)g_rbuf0, test_len);

  if (i2s_para->mode == I2S_MC_XFER_DMA){
      arr_remove_zero(g_rbuf0, TEST_DATA_SIZE);
  }
  

  if (memcmp(g_rbuf0, g_wbuf, test_len * sizeof(*g_wbuf)))
    ret = -1;

  i2s_mc_print_result(i2s_para, test_len, ret);
  return 0;
}


static int i2s_mc_codec_init()
{
  int ret;

  /*codec init*/
    ret = i2s_mc_codec_probe();
    if(ret)
    {
      printf("codec probe failed, ret =%d\n",ret);
      return ret;
    }
    return 0;
}

static void i2s_show_usage(void) {
  printf("Usage: i2s [OPTION]...\n\n");
  printf("-h \t\t\t command help\n");
  printf("-m <0|1> \t\t\t 1- set Tx as master, 0- set rx as master\n");
  printf("-o <0|1> \t\t\t 1- set odd channels as tx, 0- set even channels as tx\n");
  printf("-n <Size> \t\t\t Set test size\n");
  printf("-d \t\t\t Enable DMA\n");
  printf("-t <standard>\t\t\t Set I2S standard\n");
  printf("-c <2|4|6|8> \t\t\t Set Channels num\n");
}

static int atoi(char *s) {
  int i;
  int n = 0;
  for (i = 0; s[i] >= '0' && s[i] <= '9'; ++i) {
    n = 10 * n + (s[i] - '0');
  }
  return n;
}

static int i2s_mc_test_main(int argc, char *argv[]) {
  int i;
  int c, tmp;
  int channels_num;
  int test_len = TEST_DATA_SIZE;
  int option_index = 0;

  int id = 0;

  struct i2s_mc_para i2s_para = {
    .ch_cnt = 8,
    .bitspersample = 32,
    .sample_freq = 48000,
    .mode = I2S_MC_XFER_INTERRUPT,
    .standard = SND_SOC_DAIFMT_DEFAULT,
    .loop_back = I2S_NORMAL_MODE,
    .test_codec = 0
  };

  static const char short_options[] = "m:x:o:n:t:c:l:dprh";
  static const struct option long_options[] = {
        { 0, 0, 0, 0 },
  };

  while ((c = getopt_long(argc, argv, short_options, long_options,
				&option_index)) != -1) {
    switch (c) {
    case 'm':
      i2s_para.ms_cfg = atoi(optarg);
      break;

    case 'o':
      tmp = atoi(optarg);
      for (i = 0; i < i2s_para.ch_cnt; ++i )
      {
          if(tmp == 2)
          {
            i2s_para.ch_tr_cfg[i] = 0; /*all rx*/
          }else
          {
            i2s_para.ch_tr_cfg[i] = (i + tmp + 1) % 2;   /*tmp = 1, then odd channel ch_tr_cfg = 1, as tx */
          }
      }
      
      break;

    case 'n':
      test_len = atoi(optarg) & (~1UL);
      if (test_len > TEST_DATA_SIZE || test_len <= 0)
        test_len = TEST_DATA_SIZE;
      break;

    case 'd':
      i2s_para.mode = I2S_MC_XFER_DMA;
      if (!itcs_is_dma_inited(0))
        itcs_dma_init(0);
      break;
    
    case 't':
      tmp = atoi(optarg);
      i2s_para.standard = tmp;
      break;

    case 'c':
      channels_num = atoi(optarg);
      if (channels_num <= 0 || channels_num > 8)
      {
        printf("channels_num %d is invaild\n", channels_num);
        return -1;
      }
      i2s_para.ch_cnt = channels_num;
      break;

    case 'l':
      i2s_para.loop_back = atoi(optarg);
      break;

    case 'r':
      /*code init*/
      i2s_mc_codec_init();
      goto exit;
    
    case 'p':
      i2s_para.test_codec = 1;
      i2s_para.sample_freq = 24000;
      break;

    case 'h':
    default:
      i2s_show_usage();
      goto exit;
    }
  }

  i2s_mc_test(id, &i2s_para, test_len);

exit:
  optind = 1;
  return 0;
}

static void i2s_mc_test_init(void) {
  register_testbench("i2s_mc", i2s_mc_test_main, NULL);
}

testbench_init(i2s_mc_test_init);

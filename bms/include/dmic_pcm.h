#include <dma-ops.h>
#define BIT(nr) (1 << nr)

#define DEBUG_DMIC
#ifdef DEBUG_DMIC
#define DEBUG_LOG(format, ...) printf(format, ##__VA_ARGS__)
#else
#define DEBUG_LOG(format, ...) 
#endif

typedef enum itcs_dmic_chan {
	DMIC_CHAN0,
	DMIC_CHAN1,
	DMIC_CHAN2,
	DMIC_CHAN3
} dmic_chan;

typedef enum itcs_dmic_mode {
	DMIC_MODE0,
	DMIC_MODE1,
	DMIC_MODE2,
	DMIC_MODE3,
	DMIC_MODE4,
	DMIC_MODE5,
	DMIC_MODE6
} dmic_mode;

typedef enum {
  DMIC_READY = 0,
  DMIC_RX_RUNNING,
  DMIC_RX_WAITING,
  DMIC_RX_COMPLETE,
  DMIC_ERROR
} DMIC_STATUS;

typedef struct itcs_dmic_cfg {
  unsigned char fifo_afull_irq_en;
  unsigned char fifo_over_irq_en;
  unsigned char fifo_under_irq_en;
  unsigned char dma_en;
  unsigned char hw_swap;
  unsigned char byte_swap;
  unsigned char bit_swap;
  unsigned char sample_mode;
  unsigned char direct_fmt;
  unsigned int fifo_dipstick;
  unsigned int clk_ratio;
} dmic_cfg_t;

struct pcm {
  uint32_t decimation;
  uint32_t lp_alfa;
  uint32_t hp_alfa;
  uint32_t vol;
};

typedef struct itcs_dmic {
	void *membase;
  char* name;
  unsigned long input_clk;
  dmic_cfg_t* cfg;
  unsigned int index;
  int irq;
  unsigned int* dst_addr;
  unsigned int len;
  unsigned int count;
  unsigned long ouput_clk;
  unsigned char rx_status;
	unsigned int mode;
  unsigned int dma;
  struct dma_chan* dma_chan;
  struct pcm* pcm;
} dmic_dev_t;

struct dma_data{
  dma_cookie_t cookie;
  struct dma_prep_info prep_info;
  struct dma_info info;
};

//ITCS_C_DMIC_BASE

/* Register offsets for the DMIC device. */
#define ITCS_DMIC_CTL_OFFSET 0x00 /* Control Register, RW */
#define ITCS_DMIC_CFG_OFFSET 0x04 /* Config Register, RW */
#define ITCS_DMIC_ISR_OFFSET 0x08 /* IRQ Status Register, RC */
#define ITCS_DMIC_FIFO_STAT_OFFSET 0x0C /* FIFO Status Register, RO */
#define ITCS_DMIC_FIFO_OFFSET 0x10 /* FIFO Register, RO */

/* Register offsets for the DMIC PCM device. */
#define ITCS_DMIC_FILTER_OFFSET  0x14
#define ITCS_DMIC_DECIMATION_OFFSET  0x18
#define ITCS_DMIC_LP_OFFSET  0x1C
#define ITCS_DMIC_HP_OFFSET  0x20
#define ITCS_DMIC_VOL_OFFSET 0x24

/* Control Register Bit mask definitions */
#define CICCOMP_OUT_EN BIT(5)
#define CIC_OUT_EN BIT(4)
#define ITCS_MCH_SYNC_EN BIT(3)
#define ITCS_PDM_CLK_EN BIT(2)
#define ITCE_FIFO_EN BIT(1)
#define ITCS_DMIC_ON BIT(0)

/* PCM Register Bit mask definitions */
#define ITCS_PCM_ON BIT(0)
#define ITCS_PCM_64 0
#define ITCS_PCM_128 BIT(0)
#define ITCS_PCM_LP(x)  x
#define ITCS_PCM_HP(x)  x
#define ITCS_PCM_VOL(x)  x

/* Config Register Bit mask definitions */
#define FIFO_AFULL_IRQ_EN BIT(30)
#define FIFO_OVER_IRQ_EN BIT(29)
#define FIFO_UNDER_IRQ_EN BIT(28)
#define DMA_EN BIT(20)
#define HW_SWAP BIT(18)
#define BYTE_SWAP BIT(17)
#define BIT_SWAP BIT(16)
#define SAMPLE_MODE(x) (x << 14)
#define DIRECT_FMT BIT(13)
#define FIFO_DIPSTICK(x) (x << 8)/*12:8*/
#define CLK_RATIO(x) (x << 0)/*7:0*/

/* Irq Status Register Bit mask definitions */
#define ITCS_INT_FIFO_AFULL BIT(2)
#define ITCS_INT_FIFO_OVER BIT(1)
#define ITCS_INT_FIFO_UNDER BIT(0)

/* FIFO Status Register Bit mask definitions */
#define ITCS_FIFO_WORD_CNT_BIT BIT(4) /*bit 9:4 is the number of data in FIFO*/
#define ITCS_FIFO_AFULL_FLAG BIT(3)
#define ITCS_FIFO_AEMPTY_FLAG BIT(2)
#define ITCS_FIFO_FULL_FLAG BIT(1)
#define ITCS_FIFO_EMPTY_FLAG BIT(0)

int itcs_dmic_is_completed(dmic_dev_t* dmic);
int itcs_dmic_read(dmic_dev_t* dmic, unsigned int *buf, unsigned int len, bool blocked);
dmic_dev_t* itcs_dmic_init(dmic_chan chan, dmic_mode mode, unsigned int dma, 
                            uint32_t decimation);
int itcs_dmic_stop(dmic_dev_t* dmic);
int itcs_dmic_sync(dmic_dev_t* dmic);

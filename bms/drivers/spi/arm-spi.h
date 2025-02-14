#ifndef __ARM_SPI_H__
#define __ARM_SPI_H__

#include <stdint.h>
#include <spi-common.h>
#include <dma-ops.h>

enum arm_spi_type {
  ARM_MOTO_SPI     = 0,
  ARM_TI_SSP       = 0x10,
  ARM_NS_MICROWIRE = 0x20,
};

struct spi_dma_st {
#define ARM_SPI_DMA_RX 0
#define ARM_SPI_DMA_TX 1
  struct dma_chan *chan[2];
  struct dma_prep_info prep_info[2];
  struct dma_slave_config cfg[2];
  struct dma_info info[2];
  dma_cookie_t cookie[2];
};

struct arm_spi_profile {
  /* User profile */
  SPI SPIx;
  domain_t domain;
  bool enable_dma;
  bool enable_ddr;
  unsigned long regs;
  uint32_t mode; /* master salve mode */
  uint32_t tmode;
  uint32_t bits_per_word; /* data size */
  int cs_mode;            /* chip select mode */
  int cs_pin;             /* chip select pin number */
  uint32_t freq_hz;       /* Default frequency */
  int bus_clk_rate;       /* APB to SPI clock rate*/
  uint32_t polarity;      /* polarity */
  uint32_t phase;         /* phase */
  struct spi_dma_st dma;  /* spi dma struct */

  /* Inner profile */
  enum arm_spi_type type; /* SPI/SSP/MicroWire */

  /* Transfer profile */
  SPI_StatusTypeDef tx_status;
  SPI_StatusTypeDef rx_status;
  SPI_ErrorTypeDef err_code;

  uint8_t *tx_buff_ptr;
  uint16_t tx_xfer_size;
  uint16_t tx_xfer_counter;

  uint8_t *rx_buff_ptr;
  uint16_t rx_xfer_size;
  uint16_t rx_xfer_counter;

  void (*tx_isr)(struct arm_spi_profile *profile);
  void (*rx_isr)(struct arm_spi_profile *profile);

  /* Callback profile */
  /* spi rx complete callback  */
  void (*rCCallback)(struct arm_spi_profile *profile);
  /* spi tx complete callback  */
  void (*tCCallback)(struct arm_spi_profile *profile);
  /* spi error callback        */
  void (*errCallback)(struct arm_spi_profile *profile);

  uint32_t fifo_len; /* depth of the FIFO buffer */
  uint32_t max_xfer; /* Maximum transfer size (in bits) */
};

void arm_spi_chipselect(struct arm_spi_profile *profile, int voltage);
struct arm_spi_profile *arm_spi_init(SPI_InitTypeDef *init);
void arm_spi_deinit(struct arm_spi_profile *profile);
int arm_spi_receive(struct arm_spi_profile *profile, uint8_t *data,
                    uint32_t size, bool isBlock);
int arm_spi_transmit(struct arm_spi_profile *profile, uint8_t *data,
                     uint32_t size, bool isBlock);
int arm_spi_transmit_receive(struct arm_spi_profile *profile, uint8_t *tx_data,
                             uint8_t *rx_data, uint32_t size, bool isBlock);
int arm_spi_get_transfer_status(struct arm_spi_profile *profile, bool tx);
#endif // __ARM_SPI_H__
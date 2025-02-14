#ifndef __DWC_SPI_H__
#define __DWC_SPI_H__

#include <stdint.h>
#include <spi-common.h>
#include <dma-ops.h>

#define DW_SPI_FIFO_DEPTH 16
#define DW_SPI_MAX_TRANS  1024

struct dw_spi_dma {
  struct dma_chan *chan;
  struct dma_prep_info *prep_info;
  struct dma_slave_config *cfg;
  struct dma_info *info;
  dma_cookie_t cookie;
};

struct dw_spi_profile {
  /* User profile */
  SPI SPIx;
  bool enable_dma;
  bool enable_ddr;
  unsigned long regs;
  uint32_t mode; /* slave or master */

  uint32_t bits_per_word; /* data size */
  int cs_mode;            /* chip select mode */
  int cs_pin;             /* chip select pin number */
  uint32_t freq_hz;       /* Default frequency */
  int bus_clk_rate;       /* APB to SPI clock rate*/
  uint32_t polarity;      /* polarity */
  uint32_t phase;         /* phase */

  /* Inner profile */
  enum spi_tmode tmode; /* TR/TO/RO/EEPROM */
  enum spi_type type;   /* SPI/SSP/MicroWire */

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

  struct dw_spi_dma rx_dma_profile;
  struct dw_spi_dma tx_dma_profile;

  void (*tx_isr)(struct dw_spi_profile *profile);
  void (*rx_isr)(struct dw_spi_profile *profile);

  /* Callback profile */
  /* spi rx complete callback  */
  void (*rCCallback)(struct dw_spi_profile *profile);
  /* spi tx complete callback  */
  void (*tCCallback)(struct dw_spi_profile *profile);
  /* spi error callback        */
  void (*errCallback)(struct dw_spi_profile *profile);

  uint32_t fifo_len; /* depth of the FIFO buffer */
  uint32_t max_xfer; /* Maximum transfer size (in bits) */
};

void dw_spi_chipselect(struct dw_spi_profile *profile, int voltage);
struct dw_spi_profile *dw_spi_init(SPI_InitTypeDef *init);
void dw_spi_deinit(struct dw_spi_profile *profile);
int dw_spi_receive(struct dw_spi_profile *profile, uint8_t *data, uint32_t size,
                   bool isBlock);
int dw_spi_transmit(struct dw_spi_profile *profile, uint8_t *data,
                    uint32_t size, bool isBlock);
int dw_spi_transmit_receive(struct dw_spi_profile *profile, uint8_t *tx_data,
                            uint8_t *rx_data, uint32_t size, bool isBlock);
int dw_spi_get_transfer_status(struct dw_spi_profile *profile, bool tx);
#endif // __DWC_SPI_H__
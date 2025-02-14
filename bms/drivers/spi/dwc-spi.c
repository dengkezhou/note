/*
 * Copyright (C) intchains Holding Limited
 */

/*******************************************************************
 * @file     dwc-spi.c
 * @brief    dwc spi Driver
 * @version  V1.0
 * @date     07.25 2022
 * @name     dwc-spi
 *
 * @author   jason.liu
 *******************************************************************/
#include "dwc-spi.h"
#include <common.h>
#include <irq.h>
#include <malloc.h>
#include <cache.h>
#include <pads.h>

/* Register offsets */
#define DW_SPI_CTRLR0  0x00
#define DW_SPI_CTRLR1  0x04
#define DW_SPI_SSIENR  0x08
#define DW_SPI_MWCR    0x0c
#define DW_SPI_SER     0x10
#define DW_SPI_BAUDR   0x14
#define DW_SPI_TXFTLR  0x18
#define DW_SPI_RXFTLR  0x1c
#define DW_SPI_TXFLR   0x20
#define DW_SPI_RXFLR   0x24
#define DW_SPI_SR      0x28
#define DW_SPI_IMR     0x2c
#define DW_SPI_ISR     0x30
#define DW_SPI_RISR    0x34
#define DW_SPI_TXOICR  0x38
#define DW_SPI_RXOICR  0x3c
#define DW_SPI_RXUICR  0x40
#define DW_SPI_MSTICR  0x44
#define DW_SPI_ICR     0x48
#define DW_SPI_DMACR   0x4c
#define DW_SPI_DMATDLR 0x50
#define DW_SPI_DMARDLR 0x54
#define DW_SPI_IDR     0x58
#define DW_SPI_VERSION 0x5c
#define DW_SPI_DR      0x60

#define DWSPI_CTRLR0_DFS_MASK   0x000f
#define DWSPI_CTRLR0_DFS32_MASK 0x1f0000
#define DWSPI_CTRLR0_FRF_MASK   0x600000
#define DWSPI_CTRLR0_SCPOL_MASK 0x0080
#define DWSPI_CTRLR0_SCPH_MASK  0x0040
#define DWSPI_CTRLR0_TMOD_MASK  0x0300
#define DWSPI_CTRLR0_SLVOE_MASK 0x0400
#define DWSPI_CTRLR0_SRL_MASK   0x0800
#define DWSPI_CTRLR0_CFS_MASK   0xf000

#define DWSPI_SR_BUSY_MASK 0x0001
#define DWSPI_SR_TFNF_MASK 0x0002
#define DWSPI_SR_TFE_MASK  0x0004
#define DWSPI_SR_RFNE_MASK 0x0008
#define DWSPI_SR_RFF_MASK  0x0010
#define DWSPI_SR_TXE_MASK  0x0020

#define DWSPI_ISR_TXEIS_MASK 0x0001
#define DWSPI_ISR_RXFIS_MASK 0x0010

#define DWSPI_IMR_TXEIM_MASK 0x0001
#define DWSPI_IMR_RXFIM_MASK 0x0010

#define DWSPI_DMACR_TDMAE_MASK 0x0002
#define DWSPI_DMACR_RDMAE_MASK 0x0001

#define check_req_irq_ret(ret)                                                 \
  do {                                                                         \
    if (ret) {                                                                 \
      return ret;                                                              \
    }                                                                          \
  } while (0)

static void dw_spi_disable(struct dw_spi_profile *profile) {
  writel(0, profile->regs + DW_SPI_SSIENR);
}

static void dw_spi_enable(struct dw_spi_profile *profile) {
  writel(1, profile->regs + DW_SPI_SSIENR);
}

static void dw_spi_clean_rx_fifo(struct dw_spi_profile *profile) {
  while (DWSPI_SR_RFNE_MASK & readl(profile->regs + DW_SPI_SR)) {
    readb(profile->regs + DW_SPI_DR);
  }
}

static void dw_spi_baudcfg(struct dw_spi_profile *profile, uint32_t speed_hz) {
  /* Divisor must be an even number */
  uint16_t div =
      (speed_hz)
          ? ((DIV_ROUND_UP(profile->bus_clk_rate, speed_hz) + 1) & 0xfffe)
          : 0xffff;
  DEBUG_SPI_LOG("dw spi clk div = %d\n", div);
  writew(div, profile->regs + DW_SPI_BAUDR);
}

static void dw_spi_slave_enable(struct dw_spi_profile *profile, bool enable) {
  if (enable) {
    writel(1 << 3, profile->regs + DW_SPI_SER);
  } else {
    writel(0, profile->regs + DW_SPI_SER);
  }
}

void dw_spi_chipselect(struct dw_spi_profile *profile, int voltage) {
  // GPIO cs select
  if (voltage == 0)
    itcs_pads_set_value(profile->cs_pin, 0);
  else
    itcs_pads_set_value(profile->cs_pin, 1);
}

static void dw_spi_it_config(SPI SPIx, uint16_t spi_it, bool state) {
  uint32_t tempReg;
  unsigned long spi_base = spi_get_base_addr(SPIx);

  if (state == false) {
    tempReg = readl(spi_base + DW_SPI_IMR);
    tempReg &= ~(uint32_t)spi_it;
    writel(tempReg, spi_base + DW_SPI_IMR);
  } else if (state == true) {
    tempReg = readl(spi_base + DW_SPI_IMR);
    tempReg |= (uint32_t)spi_it;
    writel(tempReg, spi_base + DW_SPI_IMR);
  }
}

static bool dw_spi_get_it(uint32_t isr, uint16_t spi_it) {
  if ((spi_it & isr) != 0) {
    return true;
  } else {
    return false;
  }
}

static int dw_spi_fill_tx_fifo(struct dw_spi_profile *profile) {
  uint8_t bytes_already_wrote = readb(profile->regs + DW_SPI_TXFLR);
  // DEBUG_SPI_LOG("spi fill in fifo, bytes_already_wrote=
  // %d.\n",bytes_already_wrote);
  int bytes_can_be_write = profile->fifo_len - bytes_already_wrote;
  // DEBUG_SPI_LOG("bytes_can_be_write= %d.\n",bytes_can_be_write);
  int ret = profile->tx_xfer_counter;

  /* Fill in the Tx FIFO as many bytes as possible */
  // DEBUG_SPI_LOG("tx_xfer_size = %d, tx_xfer_counter =
  // %d.\n",profile->tx_xfer_size, profile->tx_xfer_counter);
  while ((profile->tx_xfer_size > profile->tx_xfer_counter) &&
         (bytes_can_be_write > 0)) {
    // DEBUG_SPI_LOG("write data 0x%x.\n",*(profile->tx_buff_ptr +
    // profile->tx_xfer_counter));
    if (profile->bits_per_word == SPI_DATASIZE_8BIT) {
      writeb(*(profile->tx_buff_ptr + profile->tx_xfer_counter),
             profile->regs + DW_SPI_DR);
      profile->tx_xfer_counter++;
      bytes_can_be_write--;
    } else {
      writew(*(profile->tx_buff_ptr + profile->tx_xfer_counter),
             profile->regs + DW_SPI_DR);
      profile->tx_xfer_counter += 2;
      bytes_can_be_write -= 2;
    }
  }
  ret = profile->tx_xfer_counter - ret;
  // DEBUG_SPI_LOG("tx counter=%d, sr=0x%x\n",profile->tx_xfer_counter,sr);
  return ret;
}

static int dw_spi_read_rx_fifo(struct dw_spi_profile *profile) {
  uint8_t sr;
  sr      = readb(profile->regs + DW_SPI_SR);
  int ret = profile->rx_xfer_counter;

  /* Read as long as RX FIFO is not empty */
  while ((sr & DWSPI_SR_RFNE_MASK) &&
         (profile->rx_xfer_size > profile->rx_xfer_counter)) {
    int rx_level = readl(profile->regs + DW_SPI_RXFLR);
    while (rx_level-- &&
           (profile->rx_xfer_size - profile->rx_xfer_counter) > 0) {
      if (profile->bits_per_word == SPI_DATASIZE_8BIT) {
        *(profile->rx_buff_ptr + profile->rx_xfer_counter) =
            readb(profile->regs + DW_SPI_DR);
        profile->rx_xfer_counter++;
      } else {
        *(profile->rx_buff_ptr + profile->rx_xfer_counter) =
            readw(profile->regs + DW_SPI_DR);
        profile->rx_xfer_counter += 2;
      }
    }
    sr = readb(profile->regs + DW_SPI_SR);
  }
  // DEBUG_SPI_LOG("rx counter=%d, sr=0x%x\n",profile->rx_xfer_counter,sr);
  ret = profile->rx_xfer_counter - ret;
  return 0;
}

static void dw_spi_tx_isr(struct dw_spi_profile *profile) {
  if (profile->tx_xfer_counter == profile->tx_xfer_size) {
    dw_spi_chipselect(profile, 1);
    dw_spi_it_config(profile->SPIx, DWSPI_IMR_TXEIM_MASK, false);
    DEBUG_SPI_LOG("[dw_spi_tx_isr()] tx empty irq disabled.\n");
    profile->tx_status = SPI_STA_TX_COMPLETE;
    if ((profile->err_code != SPI_ERROR_NONE) && (profile->errCallback)) {
      profile->errCallback(profile);
      return;
    }
    if (profile->tCCallback) {
      profile->tCCallback(profile);
      return;
    }
    return;
  }

  dw_spi_fill_tx_fifo(profile);
}

static void dw_spi_rx_isr(struct dw_spi_profile *profile) {

  if (profile->rx_xfer_counter == profile->rx_xfer_size) {
    // Mask RXF interrupt, measns disable RXF interrupt.
    dw_spi_it_config(profile->SPIx, DWSPI_IMR_RXFIM_MASK, false);
    DEBUG_SPI_LOG("[dw_spi_rx_isr()] tx empty irq disabled.\n");
    profile->rx_status = SPI_STA_RX_COMPLETE;
    if ((profile->err_code != SPI_ERROR_NONE) && (profile->errCallback)) {
      profile->errCallback(profile);
      return;
    }
    if (profile->rCCallback) {
      profile->rCCallback(profile);
      return;
    }
  }

  if (profile->rx_buff_ptr == NULL) {
    return;
  }

  dw_spi_read_rx_fifo(profile);
}

static int dw_spi_irq_handler(int irq, void *args) {
  uint32_t isr;
  struct dw_spi_profile *profile = (struct dw_spi_profile *)args;
  isr                            = readl(profile->regs + DW_SPI_ISR);
  DEBUG_SPI_LOG("dw spi%d irq handler. isr=0x%x\n", profile->SPIx, isr);
  // error interrupt process

  // rx full
  if (dw_spi_get_it(isr, DWSPI_ISR_RXFIS_MASK)) {
    DEBUG_SPI_LOG("rx full irq.\n");

    // profile->rx_isr(profile);
  }

  // tx empty
  if (dw_spi_get_it(isr, DWSPI_ISR_TXEIS_MASK)) {
    DEBUG_SPI_LOG("tx empty irq.\n");
    profile->tx_isr(profile);
  }

  return 0;
}

static int dw_spi_register_irq(SPI SPIx, struct dw_spi_profile *profile) {
  int ret = 0;
  switch (SPIx) {
  case SPI0:
    ret =
        request_irq(SPI0_IRQn, dw_spi_irq_handler, "spi0-irq", (void *)profile);
    check_req_irq_ret(ret);
    break;
  case SPI1:
    ret =
        request_irq(SPI1_IRQn, dw_spi_irq_handler, "spi1-irq", (void *)profile);
    check_req_irq_ret(ret);
    break;
  case SPI2:
    ret =
        request_irq(SPI2_IRQn, dw_spi_irq_handler, "spi2-irq", (void *)profile);
    check_req_irq_ret(ret);
    break;
  case SPI3:
    ret =
        request_irq(SPI3_IRQn, dw_spi_irq_handler, "spi3-irq", (void *)profile);
    check_req_irq_ret(ret);
    break;

  default:
    return -1;
    break;
  }

  return 0;
}
/*
static int dw_spi_receive_it(struct dw_spi_profile *profile, uint8_t *data,
                             uint32_t size) {
  if ((data == NULL) || (size == 0)) {
     printf("spi%d receive data buff null or size <= 0.\n",(int)profile->SPIx);
    return HAL_ERROR;
  }

  if (profile->rx_status != SPI_STA_READY) {
    printf("spi%d is busy.\n",(int)profile->SPIx);
    return HAL_BUSY;
  }

  profile->rx_status       = SPI_STA_BUSY_RX;
  profile->err_code        = SPI_ERROR_NONE;
  profile->rx_buff_ptr     = data;
  profile->rx_xfer_size    = size;
  profile->rx_xfer_counter = 0;

  profile->rx_isr = dw_spi_rx_isr;

  // Unmask RXF interrupt, measns enable RXF interrupt.
  DEBUG_SPI_LOG("[dw_spi_receive_it()] rx full irq enabled.\n");
  dw_spi_it_config(profile->SPIx, DWSPI_IMR_RXFIM_MASK, false);

  return 0;
}

static int dw_spi_transmit_it(struct dw_spi_profile *profile, uint8_t *data,
                              uint32_t size) {
  if ((data == NULL) || (size == 0)) {
    printf("spi%d transmit data null or size <= 0.\n",(int)profile->SPIx);
    return HAL_ERROR;
  }

  if (profile->tx_status != SPI_STA_READY) {
    printf("spi%d is busy.\n",(int)profile->SPIx);
    return HAL_BUSY;
  }

  profile->tx_status       = SPI_STA_BUSY_TX;
  profile->err_code        = SPI_ERROR_NONE;
  profile->tx_buff_ptr     = data;
  profile->tx_xfer_size    = size;
  profile->tx_xfer_counter = 0;

  profile->tx_isr = dw_spi_tx_isr;

  dw_spi_fill_tx_fifo(profile);
  DEBUG_SPI_LOG("dw_spi_transmit_it fill tx fifo done.\n");

  //cs
  dw_spi_chipselect(profile, 0);

  //enable TXE interrupt.
  DEBUG_SPI_LOG("[dw_spi_transmit_it()] tx empty irq enabled.\n");
  dw_spi_it_config(profile->SPIx, DWSPI_IMR_TXEIM_MASK, true);

  return 0;
}

static int dw_spi_transmit_receive_it(struct dw_spi_profile *profile, uint8_t
*tx_data, uint8_t *rx_data, uint32_t size) {
  // Args check
  if ((tx_data == NULL) || (size == 0)) {
    printf("spi%d transmit data null or size <= 0.\n",(int)profile->SPIx);
    return HAL_ERROR;
  }

  if (profile->tx_status != SPI_STA_READY) {
    printf("spi%d is busy.\n",(int)profile->SPIx);
    return HAL_BUSY;
  }

  profile->tx_status       = SPI_STA_BUSY_TX_RX;
  profile->err_code        = SPI_ERROR_NONE;
  profile->tx_buff_ptr     = tx_data;
  profile->rx_buff_ptr     = rx_data;
  profile->rx_xfer_size    = size;
  profile->tx_xfer_size    = size;
  profile->rx_xfer_counter = 0;
  profile->tx_xfer_counter = 0;

  profile->tx_isr = dw_spi_tx_isr_2line;
  profile->rx_isr = dw_spi_rx_isr_2line;

  // Fill in first fifo depth bytes which need to be transmitted.
  dw_spi_fill_tx_fifo(profile);
  DEBUG_SPI_LOG("dw_spi_transmit_it fill tx fifo done.\n");

  // Chip select
  dw_spi_chipselect(profile, 0);

  // Start transmit, only dw spi using.
  dw_spi_slave_enable(profile, true);

  // Enable TXE interrupt.
  DEBUG_SPI_LOG("dw_spi_transmit_receive_it() tx empty irq enabled.\n");
  dw_spi_it_config(profile->SPIx, DWSPI_IMR_TXEIM_MASK, true);

  // Enable RXF interrupt.
  DEBUG_SPI_LOG("dw_spi_transmit_receive_it() rx full  irq enabled.\n");
  dw_spi_it_config(profile->SPIx, DWSPI_IMR_RXFIM_MASK, true);

  return 0;
}
*/
void dw_spi_tc_cb(struct dw_spi_profile *profile) {
  printf("dw spi transmit completed callback.\n");
}

void dw_spi_rc_cb(struct dw_spi_profile *profile) {
  printf("dw spi receive  completed callback.\n");
}

void dw_spi_err_cb(struct dw_spi_profile *profile) {
  printf("dw spi error callback.\n");
}

struct dw_spi_profile *dw_spi_init(SPI_InitTypeDef *init) {
  uint32_t tmp_reg_val;

  struct dw_spi_profile *profile =
      (struct dw_spi_profile *)malloc(sizeof(struct dw_spi_profile));
  if (profile == NULL) {
    printf("Malloc memory for dw_spi_profile failed!\n");
    return NULL;
  }
  DEBUG_SPI_LOG("dw ssi init start......\n");
  memset(profile, 0, sizeof(struct dw_spi_profile));

  /* Set module pads */
  spi_module_set_pads(init->SPIx);
  itcs_module_set_clock("spi-clk", 24000000);

  profile->bits_per_word = init->dataSize;
  profile->freq_hz       = init->freq_hz;
  profile->mode          = init->mode;
  profile->phase         = init->CLKPhase;
  profile->polarity      = init->CLKPolarity;
  profile->regs          = spi_get_base_addr(init->SPIx);
  profile->cs_mode       = init->cs_mode;
  profile->cs_pin        = init->cs_pin;
  profile->enable_dma    = init->enable_dma;
  profile->SPIx          = init->SPIx;

  profile->type         = SSI_MOTO_SPI;
  profile->bus_clk_rate = itcs_module_get_clock("spi-clk");
  profile->fifo_len     = DW_SPI_FIFO_DEPTH;
  profile->max_xfer     = DW_SPI_MAX_TRANS;
  profile->tmode        = SSI_TR;
  profile->tx_isr       = dw_spi_tx_isr;
  profile->rx_isr       = dw_spi_rx_isr;
  profile->enable_ddr   = false;
  profile->err_code     = SPI_ERROR_NONE;
  profile->errCallback  = dw_spi_err_cb;
  profile->rCCallback   = dw_spi_rc_cb;
  profile->tCCallback   = dw_spi_tc_cb;

  DEBUG_SPI_LOG("spi base addr=0x%x\n", profile->regs);

  // Alloc dma related memery
  if (profile->enable_dma) {
    /*
    if (!itcs_is_dma_inited(1)) {
      itcs_dma_init(1);
    }
    dw_spi_dma_init(profile, true);
    dw_spi_dma_init(profile, false);
    */
  }

  spi_module_enable(profile->SPIx, true);

  dw_spi_disable(profile);
  DEBUG_SPI_LOG("dw ssi disabled!\n");

  // Disable all interrupts
  writel(0x0, profile->regs + DW_SPI_IMR);
  DEBUG_SPI_LOG("dw ssi irq disabled!\n");

  // Set baudrate
  dw_spi_baudcfg(profile, profile->freq_hz);
  DEBUG_SPI_LOG("dw ssi baud set success!\n");

  // Set polarity and phase
  tmp_reg_val = readl(profile->regs + DW_SPI_CTRLR0);
  tmp_reg_val &= ~DWSPI_CTRLR0_SCPOL_MASK;
  tmp_reg_val |= profile->polarity;
  tmp_reg_val &= ~DWSPI_CTRLR0_SCPH_MASK;
  tmp_reg_val |= profile->phase;
  writel(tmp_reg_val, profile->regs + DW_SPI_CTRLR0);
  DEBUG_SPI_LOG("dw ssi set polarity and phase success!\n");

  // Set data size
  tmp_reg_val = readl(profile->regs + DW_SPI_CTRLR0);
  tmp_reg_val &= ~DWSPI_CTRLR0_DFS_MASK;
  tmp_reg_val |= (profile->bits_per_word) << 0;
  tmp_reg_val &= ~DWSPI_CTRLR0_DFS32_MASK;
  tmp_reg_val |= (profile->bits_per_word) << 16;
  writel(tmp_reg_val, profile->regs + DW_SPI_CTRLR0);
  DEBUG_SPI_LOG("dw ssi set data size success!\n");

  /* Set transmit & receive mode */
  tmp_reg_val = readl(profile->regs + DW_SPI_CTRLR0);
  tmp_reg_val &= ~DWSPI_CTRLR0_TMOD_MASK;
  tmp_reg_val |= (profile->tmode << 8);
  writel(tmp_reg_val, profile->regs + DW_SPI_CTRLR0);
  DEBUG_SPI_LOG("dw ssi set transmit & receive mode success!\n");

  /* Set spi type MOTO/TI/MW */
  tmp_reg_val = readl(profile->regs + DW_SPI_CTRLR0);
  tmp_reg_val &= ~DWSPI_CTRLR0_FRF_MASK;
  tmp_reg_val |= profile->type;
  writel(tmp_reg_val, profile->regs + DW_SPI_CTRLR0);
  DEBUG_SPI_LOG("dw ssi set spi mode success!\n");

  /* Set TX empty IRQ threshold */
  writel(profile->fifo_len / 2, profile->regs + DW_SPI_TXFTLR);

  /* Set RX full  IRQ threshold */
  writel(profile->fifo_len / 2, profile->regs + DW_SPI_RXFTLR);
  DEBUG_SPI_LOG("dw ssi set tx&rx threshold success!\n");

  /* Register irq */
  if (dw_spi_register_irq(init->SPIx, profile)) {
    return NULL;
  }
  DEBUG_SPI_LOG("dw ssi register irq success!\n");

  // Init chip select gpio
  itcs_pads_set_mode(profile->cs_pin, PADS_MODE_OUT, 1);
  DEBUG_SPI_LOG("dw ssi initialize chip select gpio success!\n");

  dw_spi_enable(profile);
  DEBUG_SPI_LOG("dw ssi enabled!\n");

  tmp_reg_val = readl(profile->regs + DW_SPI_CTRLR0);
  DEBUG_SPI_LOG("dw ssi register ctrl0 = 0x%x\n", tmp_reg_val);

  profile->rx_status = SPI_STA_READY;
  profile->tx_status = SPI_STA_READY;

  return profile;
}

void dw_spi_deinit(struct dw_spi_profile *profile) {
  if (profile) {
    free(profile);
    profile = NULL;
  }
  dw_spi_disable(profile);
  spi_module_enable(profile->SPIx, false);
}
/*
int dw_spi_receive(struct dw_spi_profile *profile, uint8_t *data, uint32_t size,
                   bool isBlock) {
  int ret;
  if (profile->enable_dma) {
    //ret = dw_spi_receive_dma(profile, data, size);
  } else {
    ret = dw_spi_receive_it(profile, data, size);
  }
  if (isBlock) {
    while (1) {
      ret = dw_spi_get_transfer_status(profile, false);
      if ((ret == SPI_STA_RX_COMPLETE) || (ret == SPI_STA_ERROR)) {
        profile->rx_status = SPI_STA_READY;
        return ret;
      }
    }
  }
  return ret;
}
*/
int dw_spi_transmit(struct dw_spi_profile *profile, uint8_t *data,
                    uint32_t size, bool isBlock) {
  /*
  int ret;
  if (profile->enable_dma) {
    ret = dw_spi_transmit_dma(profile, data, size);
  } else {
    ret = dw_spi_transmit_it(profile, data, size);
  }
  if (isBlock) {
    while (1) {
      ret = dw_spi_get_transfer_status(profile, true);
      if ((ret == SPI_STA_TX_COMPLETE) || (ret == SPI_STA_ERROR)) {
        profile->tx_status = SPI_STA_READY;
        return ret;
      }
    }
  }
  return ret;
  */
  // Args check
  if ((data == NULL) || (size == 0)) {
    printf("spi%d transmit data null or size <= 0.\n", (int)profile->SPIx);
    return HAL_ERROR;
  }

  profile->tx_status       = SPI_STA_BUSY_TX;
  profile->err_code        = SPI_ERROR_NONE;
  profile->tx_buff_ptr     = data;
  profile->tx_xfer_size    = size;
  profile->tx_xfer_counter = 0;

  // Start transmit, only dw spi using.
  dw_spi_slave_enable(profile, true);
  do {
    // dw_spi_slave_enable(profile, false);
    dw_spi_fill_tx_fifo(profile);
    // dw_spi_slave_enable(profile, true);
  } while (profile->tx_xfer_counter != profile->tx_xfer_size);

  // wait for transmit done.
  while (!(readl(profile->regs + DW_SPI_SR) & 0x04))
    ;

  dw_spi_slave_enable(profile, false);

  return profile->tx_xfer_counter;
}

int dw_spi_transmit_receive(struct dw_spi_profile *profile, uint8_t *tx_data,
                            uint8_t *rx_data, uint32_t size, bool isBlock) {
  // Args check
  if ((tx_data == NULL) || (rx_data == NULL) || (size == 0)) {
    printf("spi%d transmit data null or size <= 0.\n", (int)profile->SPIx);
    return HAL_ERROR;
  }

  profile->tx_status       = SPI_STA_BUSY_TX_RX;
  profile->err_code        = SPI_ERROR_NONE;
  profile->tx_buff_ptr     = tx_data;
  profile->rx_buff_ptr     = rx_data;
  profile->rx_xfer_size    = size;
  profile->tx_xfer_size    = size;
  profile->rx_xfer_counter = 0;
  profile->tx_xfer_counter = 0;

  // Start transmit, only dw spi using.

  dw_spi_clean_rx_fifo(profile);
  dw_spi_slave_enable(profile, true);
  do {
    dw_spi_fill_tx_fifo(profile);
    // dw_spi_slave_enable(profile, true);
    // udelay(10);
    dw_spi_read_rx_fifo(profile);
    // dw_spi_slave_enable(profile, false);
  } while (profile->tx_xfer_counter != profile->tx_xfer_size);

  // wait for transmit done.
  while (!(readl(profile->regs + DW_SPI_SR) & 0x04))
    ;

  dw_spi_slave_enable(profile, false);

  // Enable TXE interrupt.
  // DEBUG_SPI_LOG("dw_spi_transmit_receive_it() tx empty irq enabled.\n");
  // dw_spi_it_config(profile->SPIx, DWSPI_IMR_TXEIM_MASK, true);

  // Enable RXF interrupt.
  // DEBUG_SPI_LOG("dw_spi_transmit_receive_it() rx full  irq enabled.\n");
  // dw_spi_it_config(profile->SPIx, DWSPI_IMR_RXFIM_MASK, true);

  return profile->rx_xfer_counter;
}

int dw_spi_get_transfer_status(struct dw_spi_profile *profile, bool tx) {
  int ret;
  if (profile->enable_dma) {
    if (tx) {
      ret = itcs_dma_transfer_completed(profile->tx_dma_profile.chan,
                                        profile->tx_dma_profile.cookie, NULL);
      if (ret != DMA_IN_PROGRESS) {
        profile->tx_status = SPI_STA_TX_COMPLETE;
      }
      return profile->tx_status;
    } else {
      ret = itcs_dma_transfer_completed(profile->rx_dma_profile.chan,
                                        profile->rx_dma_profile.cookie, NULL);
      if (ret != DMA_IN_PROGRESS) {
        profile->rx_status = SPI_STA_RX_COMPLETE;
      }
      return profile->rx_status;
    }
  } else {
    if (tx) {
      return profile->tx_status;
    } else {
      return profile->rx_status;
    }
  }
}
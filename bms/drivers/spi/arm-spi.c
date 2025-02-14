/*
 * Copyright (C) intchains Holding Limited
 */

/*******************************************************************
 * @file     arm-spi.c
 * @brief    armc spi Driver
 * @version  V1.0
 * @date     11.04 2022
 * @name     arm-spi
 *
 * @author   jason.liu
 *******************************************************************/
#include "arm-spi.h"
#include <dma-ops.h>
#include <common.h>
#include <irq.h>
#include <malloc.h>
#include <cache.h>
#include <pads.h>

#define ARM_SPI_FIFO_DEPTH 64

/* Register offsets */
#define ARM_SPI_CR0        0x00
#define ARM_SPI_CR1        0x04
#define ARM_SPI_DR         0x08
#define ARM_SPI_SR         0x0C
#define ARM_SPI_CPSR       0x10
#define ARM_SPI_IMSC       0x14
#define ARM_SPI_RIS        0x18
#define ARM_SPI_MIS        0x1C
#define ARM_SPI_ICR        0x20
#define ARM_SPI_DMACR      0x24
#define ARM_SPI_FIFO_LEAVE 0x28

#define ARM_SPI_PHIDR0 0xFE0
#define ARM_SPI_PHIDR1 0xFE4
#define ARM_SPI_PHIDR2 0xFE8
#define ARM_SPI_PHIDR3 0xFEC
#define ARM_SPI_PCIDR0 0xFF0
#define ARM_SPI_PCIDR1 0xFF4
#define ARM_SPI_PCIDR2 0xFF8
#define ARM_SPI_PCIDR3 0xFFC

#define ARM_SPI_CR0_MASK_DSS (0x0FUL << 0)
#define ARM_SPI_CR0_MASK_FRF (0x3UL << 4)
#define ARM_SPI_CR0_MASK_SPO (0x1UL << 6)
#define ARM_SPI_CR0_MASK_SPH (0x1UL << 7)
#define ARM_SPI_CR0_MASK_SCR (0xFFUL << 8)

#define ARM_SPI_CR1_MASK_LBM (0x1UL << 0)
#define ARM_SPI_CR1_MASK_SSE (0x1UL << 1)
#define ARM_SPI_CR1_MASK_MS  (0x1UL << 2)
#define ARM_SPI_CR1_MASK_SOD (0x1UL << 3)

#define ARM_SPI_SR_MASK_TFE (0x1UL << 0) /* Transmit FIFO empty */
#define ARM_SPI_SR_MASK_TNF (0x1UL << 1) /* Transmit FIFO not full */
#define ARM_SPI_SR_MASK_RNE (0x1UL << 2) /* Receive FIFO not empty */
#define ARM_SPI_SR_MASK_RFF (0x1UL << 3) /* Receive FIFO full */
#define ARM_SPI_SR_MASK_BSY (0x1UL << 4) /* Busy Flag */

#define ARM_SPI_CPSR_MASK_CPSDVSR (0xFFUL << 0)

#define ARM_SPI_IMSC_MASK_RORIM                                                \
  (0x1UL << 0) /* Receive Overrun Interrupt mask */
#define ARM_SPI_IMSC_MASK_RTIM                                                 \
  (0x1UL << 1)                              /* Receive timeout Interrupt mask  \
                                             */
#define ARM_SPI_IMSC_MASK_RXIM (0x1UL << 2) /* Receive FIFO Interrupt mask */
#define ARM_SPI_IMSC_MASK_TXIM (0x1UL << 3) /* Transmit FIFO Interrupt mask */

#define ARM_SPI_RIS_MASK_RORRIS (0x1UL << 0)
#define ARM_SPI_RIS_MASK_RTRIS  (0x1UL << 1)
#define ARM_SPI_RIS_MASK_RXRIS  (0x1UL << 2)
#define ARM_SPI_RIS_MASK_TXRIS  (0x1UL << 3)

#define ARM_SPI_MIS_MASK_RORMIS (0x1UL << 0)
#define ARM_SPI_MIS_MASK_RTMIS  (0x1UL << 1)
#define ARM_SPI_MIS_MASK_RXMIS  (0x1UL << 2)
#define ARM_SPI_MIS_MASK_TXMIS  (0x1UL << 3)

#define ARM_SPI_ICR_MASK_RORIC (0x1UL << 0)
#define ARM_SPI_ICR_MASK_RTIC  (0x1UL << 1)

#define ARM_SPI_DMACR_MASK_RXDMAE (0x1UL << 0)
#define ARM_SPI_DMACR_MASK_TXDMAE (0x1UL << 1)

#define ARM_SPI_CSR_CSVALUE_MASK (0x1FUL << 0)

#define check_req_irq_ret(ret)                                                 \
  do {                                                                         \
    if (ret) {                                                                 \
      return ret;                                                              \
    }                                                                          \
  } while (0)

static domain_t arm_spi_get_domain(SPI SPIx) {
  if (SPIx == SPI0) {
    return SAP;
  } else {
    return CPU;
  }
}

static void arm_spi_disable(struct arm_spi_profile *profile) {
  uint32_t tmpReg;
  tmpReg = readl(profile->regs + ARM_SPI_CR1);
  tmpReg &= (~ARM_SPI_CR1_MASK_SSE);
  writel(tmpReg, profile->regs + ARM_SPI_CR1);
  tmpReg = readl(profile->regs + ARM_SPI_CR1);
  DEBUG_SPI_LOG("arm spi disabled, CR1=0x%x\n", tmpReg);
}

static void arm_spi_enable(struct arm_spi_profile *profile) {
  uint32_t tmpReg;
  tmpReg = readl(profile->regs + ARM_SPI_CR1);
  tmpReg |= ARM_SPI_CR1_MASK_SSE;
  writel(tmpReg, profile->regs + ARM_SPI_CR1);
  tmpReg = readl(profile->regs + ARM_SPI_CR1);
  DEBUG_SPI_LOG("arm spi enabled, CR1=0x%x\n", tmpReg);
}

static void arm_spi_clean_rx_fifo(struct arm_spi_profile *profile) {
  while (ARM_SPI_SR_MASK_RNE & readl(profile->regs + ARM_SPI_SR)) {
    readb(profile->regs + ARM_SPI_DR);
  }
  udelay(200);
}

static void arm_spi_set_pha_pol_mode(struct arm_spi_profile *profile,
                                     uint32_t pha, uint32_t pol) {
  uint32_t tmp_reg_val;
  tmp_reg_val = readl(profile->regs + ARM_SPI_CR0);
  tmp_reg_val &= ~ARM_SPI_CR0_MASK_SPO;
  tmp_reg_val |= (pol << 6) & ARM_SPI_CR0_MASK_SPO;
  tmp_reg_val &= ~ARM_SPI_CR0_MASK_SPH;
  tmp_reg_val |= (pha << 7) & ARM_SPI_CR0_MASK_SPH;

  writel(tmp_reg_val, profile->regs + ARM_SPI_CR0);
  tmp_reg_val = readl(profile->regs + ARM_SPI_CR0);
  DEBUG_SPI_LOG("arm spi%d set polarity %d and phase %d success!\n",
                (int)profile->SPIx, pha, pol);
  DEBUG_SPI_LOG("arm_spi_set_pha_pol_mode() value=%x\n", tmp_reg_val);
}

static void arm_spi_set_frame_size(struct arm_spi_profile *profile,
                                   uint32_t frame_size) {
  uint32_t tmp_reg_val;
  tmp_reg_val = readl(profile->regs + ARM_SPI_CR0);
  tmp_reg_val &= ~ARM_SPI_CR0_MASK_DSS;
  tmp_reg_val |= frame_size & ARM_SPI_CR0_MASK_DSS;
  writel(tmp_reg_val, profile->regs + ARM_SPI_CR0);
  DEBUG_SPI_LOG("arm spi%d set data size %d success!\n", (int)profile->SPIx,
                frame_size);
  tmp_reg_val = readl(profile->regs + ARM_SPI_CR0);
  DEBUG_SPI_LOG("arm_spi_set_frame_size() value=%x\n", tmp_reg_val);
}

static void arm_spi_set_spi_type(struct arm_spi_profile *profile,
                                 enum spi_type type) {
  uint32_t tmp_reg_val;
  tmp_reg_val = readl(profile->regs + ARM_SPI_CR0);
  tmp_reg_val &= ~ARM_SPI_CR0_MASK_FRF;
  if (type == SSI_MOTO_SPI) {
    writel(tmp_reg_val, profile->regs + ARM_SPI_CR0);
  } else if (type == SSI_TI_SSP) {
    tmp_reg_val |= (0x01 << 4);
    writel(tmp_reg_val, profile->regs + ARM_SPI_CR0);
  } else if (type == SSI_NS_MICROWIRE) {
    tmp_reg_val |= (0x02 << 4);
    writel(tmp_reg_val, profile->regs + ARM_SPI_CR0);
  }

  DEBUG_SPI_LOG("arm spi%d set spi mode %d success!\n", (int)profile->SPIx,
                type);
  tmp_reg_val = readl(profile->regs + ARM_SPI_CR0);
  DEBUG_SPI_LOG("arm_spi_set_spi_type() ARM_SPI_CR0=%x, value=%x\n",
                ARM_SPI_CR0, tmp_reg_val);
}

static void arm_spi_baudcfg(struct arm_spi_profile *profile,
                            uint32_t speed_hz) {
  /* Divisor must be an even number */
  uint16_t div = 2;
  uint32_t tmpReg;
  uint16_t scr = (profile->bus_clk_rate / (speed_hz * div)) - 1;

  writew(div, profile->regs + ARM_SPI_CPSR);

  tmpReg = readl(profile->regs + ARM_SPI_CR0);
  tmpReg &= (~ARM_SPI_CR0_MASK_SCR);
  tmpReg |= (scr << 8);
  writel(tmpReg, profile->regs + ARM_SPI_CR0);
  tmpReg = readl(profile->regs + ARM_SPI_CR0);
  DEBUG_SPI_LOG("arm_spi_baudcfg() value=%x\n", tmpReg);
}

static void arm_spi_slave_mode_enable(struct arm_spi_profile *profile,
                                      bool enable) {
  uint32_t tmpReg;
  tmpReg = readl(profile->regs + ARM_SPI_CR1);

  if (enable) {
    tmpReg |= ARM_SPI_CR1_MASK_MS;
  } else {
    tmpReg &= (~ARM_SPI_CR1_MASK_MS);
  }

  writel(tmpReg, profile->regs + ARM_SPI_CR1);
  tmpReg = readl(profile->regs + ARM_SPI_CR1);
}

void arm_spi_chipselect(struct arm_spi_profile *profile, int voltage) {
  if (profile->cs_mode == HW_SPI_CS_MODE) {

  } else {
    // GPIO cs select
    if (voltage == 0) {
      itcs_pads_set_value(profile->domain, profile->cs_pin, 0);
      DEBUG_SPI_LOG("arm spi cs 0\n");
    } else {
      itcs_pads_set_value(profile->domain, profile->cs_pin, 1);
      DEBUG_SPI_LOG("arm spi cs 1\n");
    }
  }
}

static void arm_spi_it_config(struct arm_spi_profile *profile, uint16_t spi_it,
                              bool state) {
  uint32_t tempReg;
  unsigned long spi_base = profile->regs;

  if (state == false) {
    tempReg = readl(spi_base + ARM_SPI_IMSC);
    tempReg &= ~(uint32_t)spi_it;
    writel(tempReg, spi_base + ARM_SPI_IMSC);
  } else if (state == true) {
    tempReg = readl(spi_base + ARM_SPI_IMSC);
    tempReg |= (uint32_t)spi_it;
    writel(tempReg, spi_base + ARM_SPI_IMSC);
  }
}

static bool arm_spi_get_it(uint32_t isr, uint16_t spi_it) {
  if ((spi_it & isr) != 0) {
    return true;
  } else {
    return false;
  }
}

static void arm_spi_clear_it(struct arm_spi_profile *profile, uint16_t spi_it) {
  uint32_t tempReg = 0;
  tempReg |= spi_it;
  writel(tempReg, profile->regs + ARM_SPI_ICR);
}

static int arm_spi_fill_tx_fifo(struct arm_spi_profile *profile) {
  uint8_t sr = readb(profile->regs + ARM_SPI_SR);

  int ret = profile->tx_xfer_counter;

  // important!
  int fill_nums = profile->fifo_len;

  /* Fill in the Tx FIFO as many bytes as posspble */
  while ((profile->tx_xfer_size > profile->tx_xfer_counter) &&
         (sr & ARM_SPI_SR_MASK_TNF) && fill_nums--) {

    if (profile->bits_per_word == SPI_DATASIZE_8BIT) {
      writeb(*(profile->tx_buff_ptr + profile->tx_xfer_counter),
             profile->regs + ARM_SPI_DR);
      // DEBUG_SPI_LOG("arm spi%d write byte: 0x%x.\n", profile->SPIx,
      //              *(profile->tx_buff_ptr + profile->tx_xfer_counter));
      profile->tx_xfer_counter++;
    } else {
      writew(*(profile->tx_buff_ptr + profile->tx_xfer_counter),
             profile->regs + ARM_SPI_DR);
      profile->tx_xfer_counter += 2;
    }
    sr = readb(profile->regs + ARM_SPI_SR);
  }
  ret = profile->tx_xfer_counter - ret;

  return ret;
}

static int arm_spi_read_rx_fifo(struct arm_spi_profile *profile) {
  uint8_t sr;
  sr      = readb(profile->regs + ARM_SPI_SR);
  int ret = profile->rx_xfer_counter;

  /* Read as long as RX FIFO is not empty */
  while ((sr & ARM_SPI_SR_MASK_RNE) &&
         (profile->rx_xfer_size > profile->rx_xfer_counter)) {

    if (profile->bits_per_word == SPI_DATASIZE_8BIT) {
      *(profile->rx_buff_ptr + profile->rx_xfer_counter) =
          readb(profile->regs + ARM_SPI_DR);
      // DEBUG_SPI_LOG("arm spi%d read byte: 0x%x.\n", profile->SPIx,
      // *(profile->rx_buff_ptr + profile->rx_xfer_counter));
      profile->rx_xfer_counter++;
    } else {
      *(profile->rx_buff_ptr + profile->rx_xfer_counter) =
          readw(profile->regs + ARM_SPI_DR);
      profile->rx_xfer_counter += 2;
    }

    sr = readb(profile->regs + ARM_SPI_SR);
  }

  ret = profile->rx_xfer_counter - ret;
  return 0;
}

static void arm_spi_tx_isr(struct arm_spi_profile *profile) {
  arm_spi_clean_rx_fifo(profile);
  DEBUG_SPI_LOG("total size = %d, transfered size = %d\n",
                profile->tx_xfer_size, profile->tx_xfer_counter);
  if (profile->tx_xfer_counter == profile->tx_xfer_size) {
    arm_spi_chipselect(profile, 1);
    arm_spi_it_config(profile, ARM_SPI_IMSC_MASK_TXIM, false);

    // DEBUG_SPI_LOG("[arm_spi_tx_isr()] tx irq disabled.\n");
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

  arm_spi_fill_tx_fifo(profile);
}

static void arm_spi_rx_isr(struct arm_spi_profile *profile) {
  DEBUG_SPI_LOG("total size = %d, received size = %d\n", profile->rx_xfer_size,
                profile->rx_xfer_counter);
  if (profile->rx_xfer_counter < profile->rx_xfer_size) {
    arm_spi_read_rx_fifo(profile);
  }
  DEBUG_SPI_LOG("total size = %d, received size = %d\n", profile->rx_xfer_size,
                profile->rx_xfer_counter);
  if (profile->rx_xfer_counter >= profile->rx_xfer_size) {
    // Mask RXF interrupt, measns disable RXF interrupt.
    arm_spi_it_config(profile, ARM_SPI_IMSC_MASK_RXIM, false);
    DEBUG_SPI_LOG("[arm_spi_rx_isr()] rx irq disabled.\n");
    profile->rx_status = SPI_STA_RX_COMPLETE;
    if ((profile->err_code != SPI_ERROR_NONE) && (profile->errCallback)) {
      profile->errCallback(profile);
      return;
    }
    if (profile->rCCallback) {
      profile->rCCallback(profile);
      return;
    }
    return;
  }

  if (profile->rx_buff_ptr == NULL) {
    return;
  }
}

static void arm_spi_rx_timeout(struct arm_spi_profile *profile) {
  DEBUG_SPI_LOG("total size = %d, received size = %d\n", profile->rx_xfer_size,
                profile->rx_xfer_counter);
  if (profile->rx_xfer_counter < profile->rx_xfer_size) {
    arm_spi_read_rx_fifo(profile);
  }
  DEBUG_SPI_LOG("total size = %d, received size = %d\n", profile->rx_xfer_size,
                profile->rx_xfer_counter);
  if (profile->rx_xfer_counter >= profile->rx_xfer_size) {
    // Mask RXF interrupt, measns disable RXF interrupt.
    arm_spi_it_config(profile, ARM_SPI_IMSC_MASK_RXIM, false);
    arm_spi_it_config(profile, ARM_SPI_IMSC_MASK_RTIM, false);
    DEBUG_SPI_LOG("[arm_spi_rx_isr()] rx irq disabled.\n");
    profile->rx_status = SPI_STA_RX_COMPLETE;
    if ((profile->err_code != SPI_ERROR_NONE) && (profile->errCallback)) {
      profile->errCallback(profile);
      return;
    }
    if (profile->rCCallback) {
      profile->rCCallback(profile);
      return;
    }
    return;
  }

  if (profile->rx_buff_ptr == NULL) {
    return;
  }
}

static void arm_spi_tx_rx_isr(struct arm_spi_profile *profile) {

  DEBUG_SPI_LOG("total size = %d, transfered size = %d\n",
                profile->tx_xfer_size, profile->tx_xfer_counter);
  // read fifo data out.
  arm_spi_read_rx_fifo(profile);

  // tx complete.
  if (profile->tx_xfer_counter >= profile->tx_xfer_size) {
    while (profile->rx_xfer_counter < profile->rx_xfer_size) {
      arm_spi_read_rx_fifo(profile);
      udelay(10);
    }
    arm_spi_chipselect(profile, 1);
    arm_spi_it_config(profile, ARM_SPI_IMSC_MASK_TXIM, false);

    // DEBUG_SPI_LOG("[arm_spi_tx_isr()] tx irq disabled.\n");
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

  // transmit next tx data.
  arm_spi_fill_tx_fifo(profile);
}

static void arm_spi_rx_tx_isr(struct arm_spi_profile *profile) {
  /*
  if (profile->rx_xfer_counter == profile->rx_xfer_size) {
    // Mask RXF interrupt, measns disable RXF interrupt.
    arm_spi_it_config(profile, ARM_SPI_IMSC_MASK_RXIM, false);
    DEBUG_SPI_LOG("[arm_spi_rx_isr()] rx irq disabled.\n");
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

  arm_spi_read_rx_fifo(profile);
  */
}

static int arm_spi_master_irq_handler(struct arm_spi_profile *profile) {
  uint32_t mis;

  mis = readl(profile->regs + ARM_SPI_MIS);

  DEBUG_SPI_LOG("arm spi%d irq handler. imsc=0x%x, mis=0x%x, ris=0x%x\n",
                profile->SPIx, readl(profile->regs + ARM_SPI_IMSC), mis,
                readl(profile->regs + ARM_SPI_RIS));

  // error interrupt process
  if (arm_spi_get_it(mis, ARM_SPI_IMSC_MASK_RORIM)) {
    arm_spi_clear_it(profile, ARM_SPI_IMSC_MASK_RORIM);
    printf("arm spi%d receive over run error.\n", profile->SPIx);
  }

  // rx timeout
  if (arm_spi_get_it(mis, ARM_SPI_IMSC_MASK_RTIM)) {
    arm_spi_clear_it(profile, ARM_SPI_IMSC_MASK_RTIM);
    printf("arm spi%d receive timeout irq.\n", profile->SPIx);
  }

  // tx empty, transmit done
  if (arm_spi_get_it(mis, ARM_SPI_IMSC_MASK_TXIM)) {
    DEBUG_SPI_LOG("tx irq.\n");
    arm_spi_clear_it(profile, ARM_SPI_IMSC_MASK_TXIM);
    profile->tx_isr(profile);
  }
  DEBUG_SPI_LOG("spi master irq exit.\n");
  return 0;
}

static int arm_spi_slave_irq_handler(struct arm_spi_profile *profile) {
  uint32_t mis;

  mis = readl(profile->regs + ARM_SPI_MIS);

  DEBUG_SPI_LOG("arm spi%d irq handler. imsc=0x%x, mis=0x%x, ris=0x%x\n",
                profile->SPIx, readl(profile->regs + ARM_SPI_IMSC), mis,
                readl(profile->regs + ARM_SPI_RIS));

  // error interrupt process
  if (arm_spi_get_it(mis, ARM_SPI_IMSC_MASK_RORIM)) {
    arm_spi_clear_it(profile, ARM_SPI_IMSC_MASK_RORIM);
    printf("arm spi%d receive over run error.\n", profile->SPIx);
  }

  // rx timeout
  if (arm_spi_get_it(mis, ARM_SPI_IMSC_MASK_RTIM)) {
    arm_spi_clear_it(profile, ARM_SPI_IMSC_MASK_RTIM);
    DEBUG_SPI_LOG("arm spi%d receive timeout irq.\n", profile->SPIx);
    arm_spi_rx_timeout(profile);
  }

  // rx full, recv done
  if (arm_spi_get_it(mis, ARM_SPI_IMSC_MASK_RXIM)) {
    arm_spi_clear_it(profile, ARM_SPI_IMSC_MASK_RXIM);
    DEBUG_SPI_LOG("rx irq.\n");
    profile->rx_isr(profile);
  }
  DEBUG_SPI_LOG("spi slave irq exit.\n");
  return 0;
}

static int arm_spi_irq_handler(int irq, void *args) {

  struct arm_spi_profile *profile = (struct arm_spi_profile *)args;

  if (profile->mode == SPI_MODE_SLAVE) {
    DEBUG_SPI_LOG("spi salve irq process.\n");
    arm_spi_slave_irq_handler(profile);
  } else {
    DEBUG_SPI_LOG("spi master irq process.\n");
    arm_spi_master_irq_handler(profile);
  }

  return 0;
}

static int arm_spi_register_irq(SPI SPIx, struct arm_spi_profile *profile) {
  int ret = 0;
  switch (SPIx) {
  case SPI0:
    ret = request_irq(S_SPI0_IRQn, arm_spi_irq_handler, "spi0-irq",
                      (void *)profile);
    check_req_irq_ret(ret);
    break;
  case SPI1:
    ret = request_irq(C_SPI1_IRQn, arm_spi_irq_handler, "spi1-irq",
                      (void *)profile);
    check_req_irq_ret(ret);
    break;
  case SPI2:
    ret = request_irq(C_SPI2_IRQn, arm_spi_irq_handler, "spi2-irq",
                      (void *)profile);
    check_req_irq_ret(ret);
    break;
  case SPI3:
    ret = request_irq(C_SPI3_IRQn, arm_spi_irq_handler, "spi3-irq",
                      (void *)profile);
    check_req_irq_ret(ret);
    break;

  default:
    return -1;
    break;
  }

  return 0;
}

static int arm_spi_receive_it(struct arm_spi_profile *profile, uint8_t *data,
                              uint32_t size) {
  if ((data == NULL) || (size == 0)) {
    printf("spi%d receive data buff null or size <= 0.\n", (int)profile->SPIx);
    return HAL_ERROR;
  }

  if (profile->rx_status != SPI_STA_READY) {
    printf("spi%d is busy.\n", (int)profile->SPIx);
    return HAL_BUSY;
  }

  profile->rx_status       = SPI_STA_BUSY_RX;
  profile->err_code        = SPI_ERROR_NONE;
  profile->rx_buff_ptr     = data;
  profile->rx_xfer_size    = size;
  profile->rx_xfer_counter = 0;

  profile->rx_isr = arm_spi_rx_isr;

  arm_spi_it_config(profile, ARM_SPI_IMSC_MASK_RXIM, true);
  arm_spi_it_config(profile, ARM_SPI_IMSC_MASK_RTIM, true);

  return 0;
}

static int arm_spi_transmit_it(struct arm_spi_profile *profile, uint8_t *data,
                               uint32_t size) {
  if ((data == NULL) || (size == 0)) {
    printf("spi%d transmit data null or size <= 0.\n", (int)profile->SPIx);
    return HAL_ERROR;
  }

  if (profile->tx_status != SPI_STA_READY) {
    printf("spi%d is busy.\n", (int)profile->SPIx);
    return HAL_BUSY;
  }

  profile->tx_status       = SPI_STA_BUSY_TX;
  profile->err_code        = SPI_ERROR_NONE;
  profile->tx_buff_ptr     = data;
  profile->tx_xfer_size    = size;
  profile->tx_xfer_counter = 0;

  profile->tx_isr = arm_spi_tx_isr;

  arm_spi_chipselect(profile, 0);
  arm_spi_fill_tx_fifo(profile);
  arm_spi_it_config(profile, ARM_SPI_IMSC_MASK_TXIM, true);
  // DEBUG_SPI_LOG("arm_spi_transmit_it fill tx fifo done.\n");

  return 0;
}

static int arm_spi_transmit_receive_it(struct arm_spi_profile *profile,
                                       uint8_t *tx_data, uint8_t *rx_data,
                                       uint32_t size) {
  // Args check
  if ((tx_data == NULL) || (size == 0)) {
    printf("spi%d transmit data null or size <= 0.\n", (int)profile->SPIx);
    return HAL_ERROR;
  }

  if (profile->tx_status != SPI_STA_READY) {
    printf("spi%d is busy.\n", (int)profile->SPIx);
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

  if (profile->mode == SPI_MODE_SLAVE) {
    profile->rx_isr = arm_spi_rx_tx_isr;
    // read cs pin, if 0 then read

  } else {
    profile->tx_isr = arm_spi_tx_rx_isr;

    // Chip select
    arm_spi_chipselect(profile, 0);

    // Fill in first fifo depth bytes which need to be transmitted.
    arm_spi_fill_tx_fifo(profile);

    // Enable TXE interrupt.
    arm_spi_it_config(profile, ARM_SPI_IMSC_MASK_TXIM, true);

    // DEBUG_SPI_LOG("arm_spi_transmit_it fill tx fifo done.\n");
    // DEBUG_SPI_LOG("arm_spi_transmit_receive_it() tx irq enabled.\n");
  }

  return 0;
}
#ifdef CONFIG_DRV_DMA

static void arm_spi_dma_rx_callback(void *param) {
  uint32_t burtst_len             = ARM_SPI_FIFO_DEPTH / 2;
  struct arm_spi_profile *profile = (struct arm_spi_profile *)param;
  profile->rx_xfer_counter =
      profile->rx_xfer_size - (profile->rx_xfer_size % burtst_len);
  DEBUG_SPI_LOG("spi%d dma rx callback\n", profile->SPIx);
}

static int arm_spi_receive_dma(struct arm_spi_profile *profile) {
  int ret;
  uint32_t burtst_len = ARM_SPI_FIFO_DEPTH / 2;

  profile->dma.cfg[ARM_SPI_DMA_RX].direction = DMA_DEV_TO_MEM;
  profile->dma.cfg[ARM_SPI_DMA_RX].src_addr  = profile->regs + ARM_SPI_DR;
  profile->dma.cfg[ARM_SPI_DMA_RX].dst_addr =
      virt_to_phys(profile->rx_buff_ptr);
  profile->dma.cfg[ARM_SPI_DMA_RX].src_addr_width = DMA_SLAVE_BUSWIDTH_1_BYTE;
  profile->dma.cfg[ARM_SPI_DMA_RX].dst_addr_width = DMA_SLAVE_BUSWIDTH_1_BYTE;
  profile->dma.cfg[ARM_SPI_DMA_RX].src_burstlen   = burtst_len;
  profile->dma.cfg[ARM_SPI_DMA_RX].dst_burstlen   = burtst_len;
  profile->dma.cfg[ARM_SPI_DMA_RX].device_fc      = 0;
  printf("---------profile->dma.cfg[ARM_SPI_DMA_RX].dst_addr=%p------\n",
         profile->dma.cfg[ARM_SPI_DMA_RX].dst_addr);
  ret = itcs_dma_slave_config(profile->dma.chan[ARM_SPI_DMA_RX],
                              &profile->dma.cfg[ARM_SPI_DMA_RX]);
  if (ret < 0) {
    printf("spi%d receive dma slave config failed!\n", profile->SPIx);
    return -1;
  }

  profile->dma.prep_info[ARM_SPI_DMA_RX].direction = DMA_DEV_TO_MEM;
  profile->dma.prep_info[ARM_SPI_DMA_RX].mode      = DMA_SLAVE;
  profile->dma.prep_info[ARM_SPI_DMA_RX].dst =
      virt_to_phys(profile->rx_buff_ptr);
  profile->dma.prep_info[ARM_SPI_DMA_RX].len =
      profile->rx_xfer_size - (profile->rx_xfer_size % burtst_len);
  profile->dma.prep_info[ARM_SPI_DMA_RX].callback = arm_spi_dma_rx_callback;
  profile->dma.prep_info[ARM_SPI_DMA_RX].callback_param = profile;

  profile->dma.cookie[ARM_SPI_DMA_RX] =
      itcs_dma_prepare(profile->dma.chan[ARM_SPI_DMA_RX],
                       &profile->dma.prep_info[ARM_SPI_DMA_RX]);
  if (profile->dma.cookie[ARM_SPI_DMA_RX] < 0) {
    printf("spi%d receive dma prepare failed!\n", profile->SPIx);
    return -1;
  }

  DEBUG_SPI_LOG("spi%d receive burtst_len=%d, prep_len=%d, rxBufSize=%d\n",
                profile->SPIx, burtst_len,
                profile->dma.prep_info[ARM_SPI_DMA_RX].len,
                profile->rx_xfer_size);

  itcs_dcache_flush();
  itcs_dma_start(profile->dma.chan[ARM_SPI_DMA_RX]);
  printf("spi%d receive dma start!\n", profile->SPIx);
  return 0;
}

static int arm_spi_transmit_dma(struct arm_spi_profile *profile) {
  int ret;
  uint32_t burtst_len = ARM_SPI_FIFO_DEPTH / 2;

  profile->dma.cfg[ARM_SPI_DMA_TX].direction = DMA_MEM_TO_DEV;
  profile->dma.cfg[ARM_SPI_DMA_TX].src_addr =
      virt_to_phys(profile->tx_buff_ptr);
  profile->dma.cfg[ARM_SPI_DMA_TX].dst_addr       = profile->regs + ARM_SPI_DR;
  profile->dma.cfg[ARM_SPI_DMA_TX].src_addr_width = DMA_SLAVE_BUSWIDTH_1_BYTE;
  profile->dma.cfg[ARM_SPI_DMA_TX].dst_addr_width = DMA_SLAVE_BUSWIDTH_1_BYTE;
  profile->dma.cfg[ARM_SPI_DMA_TX].src_burstlen   = burtst_len;
  profile->dma.cfg[ARM_SPI_DMA_TX].dst_burstlen   = burtst_len;
  profile->dma.cfg[ARM_SPI_DMA_TX].device_fc      = 0;
  ret = itcs_dma_slave_config(profile->dma.chan[ARM_SPI_DMA_TX],
                              &profile->dma.cfg[ARM_SPI_DMA_TX]);
  if (ret < 0) {
    printf("spi%d transmit dma slave config failed!\n", profile->SPIx);
    return -1;
  }

  profile->dma.prep_info[ARM_SPI_DMA_TX].direction = DMA_MEM_TO_DEV;
  profile->dma.prep_info[ARM_SPI_DMA_TX].mode      = DMA_SLAVE;
  profile->dma.prep_info[ARM_SPI_DMA_TX].src =
      virt_to_phys(profile->tx_buff_ptr);
  profile->dma.prep_info[ARM_SPI_DMA_TX].len      = profile->tx_xfer_size;
  profile->dma.prep_info[ARM_SPI_DMA_TX].callback = NULL;
  profile->dma.cookie[ARM_SPI_DMA_TX] =
      itcs_dma_prepare(profile->dma.chan[ARM_SPI_DMA_TX],
                       &profile->dma.prep_info[ARM_SPI_DMA_TX]);
  if (profile->dma.cookie[ARM_SPI_DMA_TX] < 0) {
    printf("spi%d transmit dma prepare failed!\n", profile->SPIx);
    return -1;
  }

  DEBUG_SPI_LOG("spi%d transmit burtst_len=%d, prep_len=%d, txBufSize=%d\n",
                profile->SPIx, profile->dma.cfg[ARM_SPI_DMA_TX].src_burstlen,
                profile->dma.prep_info[ARM_SPI_DMA_TX].len,
                profile->tx_xfer_size);

  itcs_dcache_flush();
  itcs_dma_start(profile->dma.chan[ARM_SPI_DMA_TX]);
  printf("spi%d transmit dma start!\n", profile->SPIx);
  return 0;
}

static bool arm_spi_dma_init(struct arm_spi_profile *profile) {
  switch (profile->SPIx) {
  case SPI0:
    profile->dma.info[ARM_SPI_DMA_RX].devname              = "dma1";
    profile->dma.info[ARM_SPI_DMA_RX].src_hw_handshake_num = DMAC1_SPI0_RX;
    profile->dma.info[ARM_SPI_DMA_TX].devname              = "dma1";
    profile->dma.info[ARM_SPI_DMA_TX].dst_hw_handshake_num = DMAC1_SPI0_TX;
    if (!itcs_is_dma_inited(1)) {
      itcs_dma_init(1);
      DEBUG_SPI_LOG("spi%d DMAC1 init successfully\n", (int)profile->SPIx);
    }

    break;
  case SPI1:
    profile->dma.info[ARM_SPI_DMA_RX].devname              = "dma0";
    profile->dma.info[ARM_SPI_DMA_RX].src_hw_handshake_num = DMAC0_SPI1_RX;
    profile->dma.info[ARM_SPI_DMA_TX].devname              = "dma0";
    profile->dma.info[ARM_SPI_DMA_TX].dst_hw_handshake_num = DMAC0_SPI1_TX;
    if (!itcs_is_dma_inited(0)) {
      itcs_dma_init(0);
      DEBUG_SPI_LOG("spi%d DMAC0 init successfully\n", (int)profile->SPIx);
    }
    break;
  case SPI2:
    profile->dma.info[ARM_SPI_DMA_RX].devname              = "dma0";
    profile->dma.info[ARM_SPI_DMA_RX].src_hw_handshake_num = DMAC0_SPI2_RX;
    profile->dma.info[ARM_SPI_DMA_TX].devname              = "dma0";
    profile->dma.info[ARM_SPI_DMA_TX].dst_hw_handshake_num = DMAC0_SPI2_TX;
    if (!itcs_is_dma_inited(0)) {
      itcs_dma_init(0);
      DEBUG_SPI_LOG("spi%d DMAC0 init successfully\n", (int)profile->SPIx);
    }
    break;
  case SPI3:
    profile->dma.info[ARM_SPI_DMA_RX].devname              = "dma0";
    profile->dma.info[ARM_SPI_DMA_RX].src_hw_handshake_num = DMAC0_SPI3_RX;
    profile->dma.info[ARM_SPI_DMA_TX].devname              = "dma0";
    profile->dma.info[ARM_SPI_DMA_TX].dst_hw_handshake_num = DMAC0_SPI3_TX;
    if (!itcs_is_dma_inited(0)) {
      itcs_dma_init(0);
      DEBUG_SPI_LOG("spi%d DMAC0 init successfully\n", (int)profile->SPIx);
    }
    break;
  default:
    break;
  }

  profile->dma.chan[ARM_SPI_DMA_RX] =
      itcs_dma_request_channel(&profile->dma.info[ARM_SPI_DMA_RX]);
  if (!profile->dma.chan[ARM_SPI_DMA_RX]) {
    DEBUG_SPI_LOG("spi%d dma chan[rx] is NULL!\n", (int)profile->SPIx);
    return false;
  }

  profile->dma.chan[ARM_SPI_DMA_TX] =
      itcs_dma_request_channel(&profile->dma.info[ARM_SPI_DMA_TX]);
  if (!profile->dma.chan[ARM_SPI_DMA_TX]) {
    DEBUG_SPI_LOG("spi%d dma chan[tx] is NULL!\n", (int)profile->SPIx);
    return false;
  }

  return true;
}
#endif

void arm_spi_tc_cb(struct arm_spi_profile *profile) {
  // printf("arm spi transmit completed callback.\n");
}

void arm_spi_rc_cb(struct arm_spi_profile *profile) {
  // printf("arm spi receive completed callback.\n");
}

void arm_spi_err_cb(struct arm_spi_profile *profile) {
  // printf("arm spi error callback.\n");
}

struct arm_spi_profile *arm_spi_init(SPI_InitTypeDef *init) {

  struct arm_spi_profile *profile =
      (struct arm_spi_profile *)malloc(sizeof(struct arm_spi_profile));
  if (profile == NULL) {
    printf("Malloc memory for arm_spi_profile failed!\n");
    return NULL;
  }
  DEBUG_SPI_LOG("arm spi%d init start......\n", (int)init->SPIx);
  memset(profile, 0, sizeof(struct arm_spi_profile));

  profile->domain = arm_spi_get_domain(init->SPIx);

  spi_module_enable(init->SPIx, true);

  /* Set module pads */
  if(init->pads == NULL){
    spi_module_set_pads(init->SPIx);
  }else{
    itcs_pads_set_mode(init->pads->sysmode, init->pads->id, PADS_MODE_FUNC, init->pads->fm);
    itcs_pads_set_pull(init->pads->sysmode, init->pads->id, 1, init->pads->pt);
  }
  
  itcs_module_set_clock(profile->domain, "spi", NULL, 24000000, false);

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
  profile->bus_clk_rate = itcs_module_get_clock(profile->domain, "spi");
  profile->fifo_len     = ARM_SPI_FIFO_DEPTH;
  profile->max_xfer     = 1024;
  profile->tmode        = SSI_TR;
  profile->tx_isr       = arm_spi_tx_isr;
  profile->rx_isr       = arm_spi_rx_isr;
  profile->enable_ddr   = false;
  profile->err_code     = SPI_ERROR_NONE;
  profile->errCallback  = arm_spi_err_cb;
  profile->rCCallback   = arm_spi_rc_cb;
  profile->tCCallback   = arm_spi_tc_cb;

  DEBUG_SPI_LOG("spi%d base addr=0x%x\n", (int)init->SPIx, profile->regs);

  // Alloc dma related memery
  if (profile->enable_dma) {
#ifdef CONFIG_DRV_DMA
    writel(0x3, profile->regs + ARM_SPI_DMACR);
    arm_spi_dma_init(profile);
#else
    printf("spi dma did not config in. change to interrupt mode\n");
    profile->enable_dma = false;
#endif
  }

  arm_spi_disable(profile);
  DEBUG_SPI_LOG("arm spi%d disabled!\n", (int)init->SPIx);

  // Disable all interrupts
  writel(0x0, profile->regs + ARM_SPI_IMSC);
  DEBUG_SPI_LOG("arm spi%d irq disabled!\n", (int)init->SPIx);

  // Set baudrate
  arm_spi_baudcfg(profile, profile->freq_hz);
  DEBUG_SPI_LOG("arm spi%d baud set success!\n", (int)init->SPIx);

  // Set polarity and phase
  arm_spi_set_pha_pol_mode(profile, profile->phase, profile->polarity);

  // Set data size
  arm_spi_set_frame_size(profile, profile->bits_per_word);

  /* Set spi type MOTO/TI/MW */
  arm_spi_set_spi_type(profile, profile->type);

  // fifo leave
  writel(0x2020, profile->regs + ARM_SPI_FIFO_LEAVE);

  /* Register irq */
  if (arm_spi_register_irq(init->SPIx, profile)) {
    return NULL;
  }
  DEBUG_SPI_LOG("arm spi%d register irq success!\n", (int)init->SPIx);

  // Init chip select gpio
  if (profile->cs_mode == GPIO_CS_MODE) {
    itcs_pads_set_mode(profile->domain, profile->cs_pin, PADS_MODE_OUT, 1);
    DEBUG_SPI_LOG("arm spi%d initialize chip select gpio success!\n",
                  (int)init->SPIx);
  }

  if (profile->mode == SPI_MODE_SLAVE) {
    arm_spi_slave_mode_enable(profile, true);
  } else {
    arm_spi_slave_mode_enable(profile, false);
  }

  arm_spi_it_config(profile, ARM_SPI_IMSC_MASK_RORIM, true);

  profile->rx_status = SPI_STA_READY;
  profile->tx_status = SPI_STA_READY;

  arm_spi_enable(profile);
  return profile;
}

void arm_spi_deinit(struct arm_spi_profile *profile) {
  if (profile) {
    free(profile);
    profile = NULL;
  }
  arm_spi_disable(profile);
  spi_module_enable(profile->SPIx, false);
}

int arm_spi_receive(struct arm_spi_profile *profile, uint8_t *data,
                    uint32_t size, bool isBlock) {
  int ret = 0;
  arm_spi_clean_rx_fifo(profile);

  if (profile->enable_dma) {
#ifdef CONFIG_DRV_DMA
    profile->rx_buff_ptr  = data;
    profile->rx_xfer_size = size;
    if (profile->rx_xfer_size % (ARM_SPI_FIFO_DEPTH / 2)) {
      arm_spi_it_config(profile, ARM_SPI_IMSC_MASK_RTIM, true);
    }

    if (profile->rx_xfer_size >= (ARM_SPI_FIFO_DEPTH / 2)) {
      ret = arm_spi_receive_dma(profile);
    }

    if (isBlock) {
      while (1) {
        ret = arm_spi_get_transfer_status(profile, false);
        if (ret == SPI_STA_RX_COMPLETE) {
          profile->rx_xfer_counter = profile->rx_xfer_size;
          return ret;
        }
      }
    }
#endif
  } else {
    ret = arm_spi_receive_it(profile, data, size);

    if (isBlock) {
      while (1) {
        ret = arm_spi_get_transfer_status(profile, false);
        if ((ret == SPI_STA_RX_COMPLETE) || (ret == SPI_STA_ERROR)) {
          profile->rx_status = SPI_STA_READY;
          return ret;
        }
      }
    }
  }
  return ret;
}

int arm_spi_transmit(struct arm_spi_profile *profile, uint8_t *data,
                     uint32_t size, bool isBlock) {

  int ret = 0;
  if (profile->enable_dma) {
#ifdef CONFIG_DRV_DMA
    profile->tx_buff_ptr  = data;
    profile->tx_xfer_size = size;
    profile->rx_buff_ptr  = (uint8_t *)malloc(size);
    profile->rx_xfer_size = size;
    ret                   = arm_spi_receive_dma(profile);
    ret                   = arm_spi_transmit_dma(profile);

    if (isBlock) {
      while (1) {
        int ret1, ret2;
        ret1 = arm_spi_get_transfer_status(profile, true);
        ret2 = arm_spi_get_transfer_status(profile, false);
        if ((ret1 == SPI_STA_TX_COMPLETE) && (ret2 == SPI_STA_RX_COMPLETE)) {
          profile->tx_xfer_counter = profile->tx_xfer_size;
          free(profile->rx_buff_ptr);
          profile->rx_buff_ptr  = NULL;
          profile->rx_xfer_size = 0;
          return ret;
        }
      }
    }
#endif
  } else {

    ret = arm_spi_transmit_it(profile, data, size);

    if (isBlock) {
      while (1) {
        ret = arm_spi_get_transfer_status(profile, true);
        if ((ret == SPI_STA_TX_COMPLETE) || (ret == SPI_STA_ERROR)) {
          profile->tx_status = SPI_STA_READY;
          return ret;
        }
      }
    }
  }
  return ret;
}

int arm_spi_transmit_receive(struct arm_spi_profile *profile, uint8_t *tx_data,
                             uint8_t *rx_data, uint32_t size, bool isBlock) {
  int ret = 0;
  if (profile->enable_dma) {
#ifdef CONFIG_DRV_DMA
    profile->tx_buff_ptr  = tx_data;
    profile->tx_xfer_size = size;
    profile->rx_buff_ptr  = rx_data;
    profile->rx_xfer_size = size;
    ret                   = arm_spi_transmit_dma(profile);
    ret                   = arm_spi_receive_dma(profile);

    if (isBlock) {
      while (1) {
        int ret1, ret2;
        ret1 = arm_spi_get_transfer_status(profile, true);
        ret2 = arm_spi_get_transfer_status(profile, false);
        if ((ret1 == SPI_STA_TX_COMPLETE) && (ret2 == SPI_STA_RX_COMPLETE)) {
          profile->tx_status       = SPI_STA_READY;
          profile->tx_xfer_counter = profile->tx_xfer_size;
          itcs_dma_stop(profile->dma.chan[ARM_SPI_DMA_TX]);
          itcs_dma_stop(profile->dma.chan[ARM_SPI_DMA_RX]);
          return ret;
        }
      }
    }
#endif
  } else {
    arm_spi_clean_rx_fifo(profile);
    ret = arm_spi_transmit_receive_it(profile, tx_data, rx_data, size);

    if (isBlock) {
      while (1) {
        ret = arm_spi_get_transfer_status(profile, true);
        if ((ret == SPI_STA_TX_COMPLETE) || (ret == SPI_STA_ERROR)) {
          profile->tx_status = SPI_STA_READY;
          return ret;
        }
      }
    }
  }
  return ret;
}

int arm_spi_get_transfer_status(struct arm_spi_profile *profile, bool tx) {

  if (profile->enable_dma) {
#ifdef CONFIG_DRV_DMA
    int ret;
    if (tx) {
      ret = itcs_dma_transfer_completed(profile->dma.chan[ARM_SPI_DMA_TX],
                                        profile->dma.cookie[ARM_SPI_DMA_TX],
                                        NULL);
      if (ret != DMA_IN_PROGRESS) {
        itcs_dma_stop(profile->dma.chan[ARM_SPI_DMA_TX]);
        DEBUG_SPI_LOG("spi%d transmit complete.\n", profile->SPIx);
        profile->tx_status = SPI_STA_READY;
        return SPI_STA_TX_COMPLETE;
      }
      return profile->tx_status;
    } else {
      if (profile->rx_status == SPI_STA_RX_COMPLETE) {
        profile->rx_status = SPI_STA_READY;
        return SPI_STA_RX_COMPLETE;
      }

      ret = itcs_dma_transfer_completed(profile->dma.chan[ARM_SPI_DMA_RX],
                                        profile->dma.cookie[ARM_SPI_DMA_RX],
                                        NULL);
      if (ret != DMA_IN_PROGRESS) {
        itcs_dma_stop(profile->dma.chan[ARM_SPI_DMA_RX]);
        profile->rx_status = SPI_STA_READY;
        DEBUG_SPI_LOG("spi%d receive complete.\n", profile->SPIx);
        return SPI_STA_RX_COMPLETE;
      }
      return profile->rx_status;
    }
#endif // CONFIG_DRV_DMA
    return SPI_STA_ERROR;
  } else {
    if (tx) {
      return profile->tx_status;
    } else {
      return profile->rx_status;
    }
  }
}

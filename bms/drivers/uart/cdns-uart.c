/*
 * Copyright (C) intchains Holding Limited
 */

/*******************************************************************
 * @file     cdns-uart.c
 * @brief    cdns uart Driver
 * @version  V1.0
 * @date     04.15 2022
 * @name     cdns-uart
 *
 * @author   jason.liu
 *******************************************************************/

#include <common.h>
#include <asm/io.h>
#include <cdns_uart.h>
#include <pads.h>
#include <cache.h>
#include <malloc.h>

#define CDNS_UART_FIFO_DEPTH 64
 #if defined(CONFIG_COMPILE_FPGA) || defined(CONFIG_COMPILE_ASIC)
static domain_t cdns_uart_get_domain(UART UARTx) {
  if (UARTx <= UART1) {
    return SAP;
  } else if (UARTx <= UART11){
    return CPU;
  } else {
    printf("uart instance number error.\n");
    return 0;
  }
}
#endif
static unsigned long cdns_get_uart_base(UART UARTx) {
  check_param(IS_UART_ALL_PERIPH(UARTx));
  switch (UARTx) {
  case UART0:
    return CDNS_UART0_BASE;
    break;
  case UART1:
    return CDNS_UART1_BASE;
    break;
  case UART2:
    return CDNS_UART2_BASE;
    break;
  case UART3:
    return CDNS_UART3_BASE;
    break;
  case UART4:
    return CDNS_UART4_BASE;
    break;
  case UART5:
    return CDNS_UART5_BASE;
    break;
  case UART6:
    return CDNS_UART6_BASE;
    break;
  case UART7:
    return CDNS_UART7_BASE;
    break;
  case UART8:
    return CDNS_UART8_BASE;
    break;
  case UART9:
    return CDNS_UART9_BASE;
    break;
  case UART10:
    return CDNS_UART10_BASE;
    break;
  case UART11:
    return CDNS_UART11_BASE;
    break;
  default:
    return CDNS_UART0_BASE; // nerver be here
  }
}


/*******************************************************************
 *@brief:  enable or disable UARTx
 *@param UARTx: Select the  UART peripheral.
 *              This parameter can be one of the following values:
 *              UART0, UART1, UART2, UART3.
 *@param state: uart status.
 *              This parameter can be ENABLE or DISABLE.
 *@return: none.
 *******************************************************************/
static void cdns_uart_cmd(UART UARTx, bool state) {
  /* Check the parameters */
  check_param(IS_UART_ALL_PERIPH(UARTx));
  uint32_t tempReg;
  unsigned long uart_base = cdns_get_uart_base(UARTx);
  tempReg                 = readl(uart_base + REG_CTRL_OFFSET);
  if (state == false) {
    // RX
    tempReg &= ~CTRL_RXEN_MASK;
    tempReg |= CTRL_RXDIS_MASK;
    // TX
    tempReg &= ~CTRL_TXEN_MASK;
    tempReg |= CTRL_TXDIS_MASK;
  } else {
    // RX
    tempReg |= CTRL_RXEN_MASK;
    tempReg &= ~CTRL_RXDIS_MASK;
    // TX
    tempReg |= CTRL_TXEN_MASK;
    tempReg &= ~CTRL_TXDIS_MASK;
  }
  writel(tempReg, uart_base + REG_CTRL_OFFSET);
  tempReg = readl(uart_base + REG_CTRL_OFFSET);
}

/*
static void cdns_uart_cmd_single(UART UARTx, uint8_t rx_tx, bool state) {
  check_param(IS_UART_ALL_PERIPH(UARTx));
  uint32_t tempReg;
  unsigned long uart_base = cdns_get_uart_base(UARTx);
  tempReg                 = readl(uart_base + REG_CTRL_OFFSET);
  if (state == false) {
    if(rx_tx == 0){
        // RX
        tempReg &= ~CTRL_RXEN_MASK;
        tempReg |= CTRL_RXDIS_MASK;
    }else{
        // TX
        tempReg &= ~CTRL_TXEN_MASK;
        tempReg |= CTRL_TXDIS_MASK;
    }
  } else {
    if(rx_tx == 0){
        // RX
        tempReg |= CTRL_RXEN_MASK;
        tempReg &= ~CTRL_RXDIS_MASK;
    }else{
        // TX
        tempReg |= CTRL_TXEN_MASK;
        tempReg &= ~CTRL_TXDIS_MASK;
    }
  }
  writel(tempReg, uart_base + REG_CTRL_OFFSET);
  tempReg = readl(uart_base + REG_CTRL_OFFSET);
}
*/

/*******************************************************************
 *@brief: set the uart flow control information
 *@param UARTx: Select the  UART peripheral.
 *              This parameter can be one of the following values:
 *              UART0, UART1, UART2, UART3.
 *@param flowControl: flow control mode.
 *              This parameter can be UART_HardwareFlowControl_None or
 *              UART_HardwareFlowControl_RTS_CTS
 *@return: none
 *******************************************************************/
static void cdns_uart_set_flowControl(UART UARTx, uint16_t flowControl) {
  check_param(IS_UART_ALL_PERIPH(UARTx));
  uint32_t tempReg;
  unsigned long uart_base = cdns_get_uart_base(UARTx);

  /*enable hardware flow control*/
  tempReg = readl(uart_base + REG_MCR_OFFSET);
  tempReg &= ~MCR_FCM_MASK;
  tempReg |= (uint32_t)flowControl;
  writel(tempReg, uart_base + REG_MCR_OFFSET);
}

/******************************************************************
 *@brief: set rx or tx trigger level in RTR or TTR
 *@param tx_rx:  0:rx, 1:tx.
 *               This parameter can be 0 or 1
 *@param trigger_level: 0-4.
 *                      This parameter can be [0-4]
 *@return: none
 *******************************************************************/
static void cdns_uart_set_trigger_level(UART UARTx, uint8_t rx_tx,
                                        uint8_t trigger_level) {
  check_param(IS_UART_ALL_PERIPH(UARTx));
  unsigned long uart_base = cdns_get_uart_base(UARTx);
  /*
  if ((rx_tx > 1) || (trigger_level > 4)) {
    printf("uart_set_trigger_level param error\n");
  }
  */
  if (rx_tx == 0) {
    writel((uint32_t)trigger_level, uart_base + REG_RTR_OFFSET);
  } else if (rx_tx == 1) {
    writel((uint32_t)trigger_level, uart_base + REG_TTR_OFFSET);
  }
} 

/*******************************************************************
 *@brief:  set the baudrate of UARTx
 *@param UARTx: Select the  UART peripheral.
 *              This parameter can be one of the following values:
 *              UART0, UART1, UART2, UART3.
 *@param baudrate: uart baudrate.
 *@return: none.
 *******************************************************************/
 #if defined(CONFIG_COMPILE_FPGA) || defined(CONFIG_COMPILE_ASIC)
static void cdns_uart_set_baudrate(UART UARTx, int baudrate) {
  check_param(IS_UART_ALL_PERIPH(UARTx));
  int clk = itcs_module_get_clock(cdns_uart_get_domain(UARTx), "uart");

  uint32_t bdiv = 0;
  uint32_t base = cdns_get_uart_base(UARTx);
  uint16_t cd = 0;
  int tmp_clk ;
  int gap_real = baudrate;
  int gap_tmp = 0;

  for(int i = 4; i <256; i++){
    tmp_clk = clk / (i + 1);
    for(int j = 1; j < 0x10000; j++)
    {
      int tmp_baud =  tmp_clk / j;
      int tmp_baud_n = tmp_clk / (j+1);
      if((tmp_baud >= baudrate) && (tmp_baud_n <= baudrate)){

        if((tmp_baud - baudrate) < (baudrate - tmp_baud_n)){
          gap_tmp = tmp_baud - baudrate;
          if(gap_tmp <= gap_real){
            bdiv = i;
            cd = j;
          }
        }else{
          gap_tmp = baudrate - tmp_baud_n;
          if(gap_tmp <= gap_real){
            bdiv = i;
            cd = j+1;
          }
        }
        gap_real = gap_tmp;
        break;

      }
    }
  }

  if(cd != 0){
    writel(bdiv, base + REG_BDIVR_OFFSET);
    writel(cd, base + REG_BRGR_OFFSET);
  }
}
#endif
static void cdns_uart_set_ir_reg(UART_HandleTypeDef *uartHandler) {
  if (uartHandler->UART_InitStruct.UART_Mode == CDNS_UART_Mode_IrDA) {
    uint32_t bdiv = readl(uartHandler->uart_base_addr + REG_BDIVR_OFFSET);
    uint32_t cd   = readl(uartHandler->uart_base_addr + REG_BRGR_OFFSET);
    uint32_t pwid, pmin;
    pwid = (3 * (bdiv + 1)) / 16;
    pmin = (3 * (bdiv + 1) * cd) / 16;
    writel(pmin, uartHandler->uart_base_addr + REG_RPWR_OFFSET);
    writel(pwid, uartHandler->uart_base_addr + REG_TPWR_OFFSET);
  }
}

/*******************************************************************
 *@brief:  enable or disable the UARTx interrupt mask.
 *@param uartHandler: uart handler pointer.
 *@param uart_it: uart interrupt mask.
 *              This parameter can be one of the following values:
 *              IxR_RTRIG_MASK,  IxR_REMPTY_MASK, IxR_RFUL_MASK,
 *              IxR_TEMPTY_MASK, IxR_TFUL_MASK,   IxR_ROVR_MASK,
 *              IxR_FRAME_MASK,  IxR_PARE_MASK,   IxR_TIMEOUT_MASK,
 *              IxR_DMSI_MASK,   IxR_TTRIG_MASK,  IxR_TNFUL_MASK,
 *              IxR_TOVR_MASK,   IxR_RBRK_MASK
 *@param state: uart status.
 *              This parameter can be SET or RESET.
 *@return: none.
 *******************************************************************/
static void cdns_uart_it_config(UART UARTx, uint16_t uart_it, BitStatus state) {
  uint32_t tempReg;
  check_param(IS_UART_ALL_PERIPH(UARTx));
  unsigned long uart_base = cdns_get_uart_base(UARTx);

  if (state == RESET) {
    tempReg = readl(uart_base + REG_IDR_OFFSET);
    tempReg |= (uint32_t)uart_it;
    writel(tempReg, uart_base + REG_IDR_OFFSET);
    tempReg = readl(uart_base + REG_IER_OFFSET);
  } else if (state == SET) {
    tempReg = readl(uart_base + REG_IER_OFFSET);
    tempReg |= (uint32_t)uart_it;
    writel(tempReg, uart_base + REG_IER_OFFSET);
    tempReg = readl(uart_base + REG_IMR_OFFSET);
  }
}

/*******************************************************************
 *@brief:  get UARTx interrupt status with mask.
 *@param uartHandler: uart handler pointer.
 *@param uart_it: uart interrupt mask.
 *              This parameter can be one of the following values:
 *              IxR_RTRIG_MASK,  IxR_REMPTY_MASK, IxR_RFUL_MASK,
 *              IxR_TEMPTY_MASK, IxR_TFUL_MASK,   IxR_ROVR_MASK,
 *              IxR_FRAME_MASK,  IxR_PARE_MASK,   IxR_TIMEOUT_MASK,
 *              IxR_DMSI_MASK,   IxR_TTRIG_MASK,  IxR_TNFUL_MASK,
 *              IxR_TOVR_MASK,   IxR_RBRK_MASK
 *@return BitStatus: SET or RESET.
 *******************************************************************/
static BitStatus cdns_uart_get_it(uint32_t imr, uint32_t cisr,
                                  uint16_t uart_it) {
  if (((uart_it & cisr) != RESET) && ((uart_it & imr) != RESET)) {
    return SET;
  } else {
    return RESET;
  }
}

static int cdns_uart_receive_it(UART_HandleTypeDef *uartHandler, int bytes) {
  uint32_t byte_wordLength_mask;
  check_param(IS_UART_HANDLER(uartHandler));
  unsigned long uart_base =
      cdns_get_uart_base(uartHandler->UART_InitStruct.UARTx);

  switch (uartHandler->UART_InitStruct.UART_WordLength) {
  case CDNS_UART_WordLength_6b:
    byte_wordLength_mask = 0x3F;
    break;
  case CDNS_UART_WordLength_7b:
    byte_wordLength_mask = 0x7F;
    break;
  case CDNS_UART_WordLength_8b:
    byte_wordLength_mask = 0xFF;
    break;
  default:
    byte_wordLength_mask = 0xFF;
    break;
  }

  // if uartHandler is prepared for receiving data
  if (uartHandler->rxStatus == UART_BUSY_RX) {
    if (uartHandler->rxCount >= uartHandler->rxBufSize) {
      DEBUG_LOG("uart%d already read %d, buffer size to small\n",
                (int)(uartHandler->UART_InitStruct.UARTx),
                uartHandler->rxCount);
      return 0;
    }
    if (uartHandler->UART_InitStruct.UART_WSIZE == CDNS_UART_WSIZE_2) {
      uint16_t data;
      int count = bytes / 2;
      DEBUG_LOG("read bytes =%d, count = %d.\n", bytes, count);
      while (count--) {
        data = readw(uart_base + REG_FIFO_OFFSET);
        *(uartHandler->rxBufPtr + uartHandler->rxCount) = data & 0xff;
        *(uartHandler->rxBufPtr + uartHandler->rxCount + 1) =
            (data >> 8) & 0xff;
        uartHandler->rxCount += 2;
        DEBUG_LOG("uart%d read:[0x%x] already read %d\n",
                  (int)(uartHandler->UART_InitStruct.UARTx), data,
                  uartHandler->rxCount);
      }
      uartHandler->rxTotal += bytes;
    } else if (uartHandler->UART_InitStruct.UART_WSIZE == CDNS_UART_WSIZE_4) {
      uint32_t data;
      int count = bytes / 4;
      while (count--) {
        data = readl(uart_base + REG_FIFO_OFFSET);
        *(uartHandler->rxBufPtr + uartHandler->rxCount) = data & 0xff;
        *(uartHandler->rxBufPtr + uartHandler->rxCount + 1) =
            (data >> 8) & 0xff;
        *(uartHandler->rxBufPtr + uartHandler->rxCount + 2) =
            (data >> 16) & 0xff;
        *(uartHandler->rxBufPtr + uartHandler->rxCount + 3) =
            (data >> 24) & 0xff;
        uartHandler->rxCount += 4;
        DEBUG_LOG("uart%d read:[0x%x] already read %d\n",
                  (int)(uartHandler->UART_InitStruct.UARTx), data,
                  uartHandler->rxCount);
      }
      uartHandler->rxTotal += bytes;
    } else {
      uint8_t data;
      while (bytes--) {
        data = readb(uart_base + REG_FIFO_OFFSET) & byte_wordLength_mask;
        *(uartHandler->rxBufPtr + uartHandler->rxCount) = data;
        uartHandler->rxCount += 1;
        DEBUG_LOG("uart%d read:[0x%x] already read %d\n",
                  (int)(uartHandler->UART_InitStruct.UARTx), data,
                  uartHandler->rxCount);
      }
      uartHandler->rxTotal += bytes;
    }

  } else {
    DEBUG_LOG("uart is not in UART_BUSY_RX,uartHandler->rxStatus = %d\n",
              uartHandler->rxStatus);
  }
  return 0;
}

static int cdns_uart_transmit_it(UART_HandleTypeDef *uartHandler) {
  int i = 0;
  uint32_t byte_wordLength_mask;
  check_param(IS_UART_HANDLER(uartHandler));

  unsigned long uart_base =
      cdns_get_uart_base(uartHandler->UART_InitStruct.UARTx);
  uint32_t byte_num = uartHandler->txBufSize - uartHandler->txCount;

  switch (uartHandler->UART_InitStruct.UART_WordLength) {
  case CDNS_UART_WordLength_6b:
    byte_wordLength_mask = 0x3F;
    break;
  case CDNS_UART_WordLength_7b:
    byte_wordLength_mask = 0x7F;
    break;
  case CDNS_UART_WordLength_8b:
    byte_wordLength_mask = 0xFF;
    break;
  default:
    byte_wordLength_mask = 0xFF;
    break;
  }

  // if uartHandler is prepared for transmitting data
  if (uartHandler->txStatus == UART_BUSY_TX) {
    if (uartHandler->UART_InitStruct.UART_WSIZE == CDNS_UART_WSIZE_2) {
      uint16_t data;
      for (i = 0; (i < (CDNS_UART_FIFO_DEPTH / 2)) && (i < (byte_num / 2));
           i++) {
        data = ((uint16_t)(*(uartHandler->txBufPtr + uartHandler->txCount + 0))
                << 0) +
               ((uint16_t)(*(uartHandler->txBufPtr + uartHandler->txCount + 1))
                << 8);
        writew(data, uart_base + REG_FIFO_OFFSET);
        uartHandler->txCount += 2;
        uartHandler->txTotal += 2;
        DEBUG_LOG("uart%d write:[0x%x] already write %d\n",
                  (int)(uartHandler->UART_InitStruct.UARTx), data,
                  uartHandler->txCount);
      }
      return 0;
    } else if (uartHandler->UART_InitStruct.UART_WSIZE == CDNS_UART_WSIZE_4) {
      uint32_t data;
      for (i = 0; (i < (CDNS_UART_FIFO_DEPTH / 4)) && (i < (byte_num / 4));
           i++) {
        data = ((uint32_t)(*(uartHandler->txBufPtr + uartHandler->txCount + 0))
                << 0) +
               ((uint32_t)(*(uartHandler->txBufPtr + uartHandler->txCount + 1))
                << 8) +
               ((uint32_t)(*(uartHandler->txBufPtr + uartHandler->txCount + 2))
                << 16) +
               ((uint32_t)(*(uartHandler->txBufPtr + uartHandler->txCount + 3))
                << 24);
        writel(data, uart_base + REG_FIFO_OFFSET);
        uartHandler->txCount += 4;
        uartHandler->txTotal += 4;
        DEBUG_LOG("uart%d write:[0x%x] already write %d\n",
                  (int)(uartHandler->UART_InitStruct.UARTx), data,
                  uartHandler->txCount);
      }
      return 0;
    } else {
      uint8_t data;
      for (i = 0; (i < CDNS_UART_FIFO_DEPTH) && (i < byte_num); i++) {
        data = *(uartHandler->txBufPtr + uartHandler->txCount);
        writeb(data & byte_wordLength_mask, uart_base + REG_FIFO_OFFSET);
        uartHandler->txCount += 1;
        uartHandler->txTotal += 1;
        DEBUG_LOG("uart%d write:[0x%x] already write %d\n",
                  (int)(uartHandler->UART_InitStruct.UARTx), data,
                  uartHandler->txCount);
      }
      return 0;
    }
  }
  return 0;
}

static void cdns_uart_irq_handle_common(UART_HandleTypeDef *uartHandler) {
  check_param(IS_UART_HANDLER(uartHandler));
  uint32_t error = 0;
  UART uartx     = uartHandler->UART_InitStruct.UARTx;

  unsigned long base_addr = cdns_get_uart_base(uartx);
  uint32_t cisr           = readl(base_addr + REG_CISR_OFFSET);
  uint32_t imr            = readl(base_addr + REG_IMR_OFFSET);

  DEBUG_LOG("uart%d irq common handler, cisr=0x%x.\n", uartx, cisr);
  // check errors
  error = (cisr & (uint32_t)(IxR_ROVR_MASK | IxR_FRAME_MASK | IxR_PARE_MASK));
  if (error != RESET) {
    DEBUG_LOG("uart%d rx error interrupt.\n", (int)uartx);
    // receive overflow error
    if (((error & IxR_ROVR_MASK) != RESET) &&
        ((imr & IxR_ROVR_MASK) != RESET)) {
      uartHandler->errorCode = UART_ERROR_ROVRE;
      DEBUG_LOG("uart%d receive overflow error.\n", (int)uartx);
      if (uartHandler->errCallback != NULL) {
        uartHandler->errCallback(uartHandler);
      }
    }
    // framing error
    if (((error & IxR_FRAME_MASK) != RESET) &&
        ((imr & IxR_FRAME_MASK) != RESET)) {
      uartHandler->errorCode = UART_ERROR_FE;
      DEBUG_LOG("uart%d receive framing error.\n", (int)uartx);
      if (uartHandler->errCallback != NULL) {
        uartHandler->errCallback(uartHandler);
      }
    }
    // parity error
    if (((error & IxR_PARE_MASK) != RESET) &&
        ((imr & IxR_PARE_MASK) != RESET)) {
      uartHandler->errorCode = UART_ERROR_PE;
      DEBUG_LOG("uart%d receive parity error.\n", (int)uartx);
      if (uartHandler->errCallback != NULL) {
        uartHandler->errCallback(uartHandler);
      }
    }
    return;
  }

  // receive trigger irq
  if (cdns_uart_get_it(imr, cisr, IxR_RTRIG_MASK) == SET) {
    DEBUG_LOG("uart%d rx trigger interrupt.\n", (int)uartx);
    cdns_uart_receive_it(uartHandler, uartHandler->rxTriggerCount);
    if (uartHandler->rxCount == uartHandler->rxBufSize) {
      uartHandler->rxStatus = UART_RX_COMPLETE;
      // receive compelete callback.
      if (uartHandler->rCCallback != NULL) {
        uartHandler->rCCallback(uartHandler);
      }
    }
  }

  // receive timeout handle
  if ((cdns_uart_get_it(imr, cisr, IxR_TIMEOUT_MASK) == SET)) {
    DEBUG_LOG("uart%d rx timeout interrupt.\n", (int)uartx);
    while ((readl(base_addr + REG_CSR_OFFSET) & 0x02) == 0 &&
           uartHandler->rxCount < uartHandler->rxBufSize) {
      if (uartHandler->UART_InitStruct.UART_WSIZE == CDNS_UART_WSIZE_1)
        cdns_uart_receive_it(uartHandler, 1);
      else if (uartHandler->UART_InitStruct.UART_WSIZE == CDNS_UART_WSIZE_2)
        cdns_uart_receive_it(uartHandler, 2);
      else if (uartHandler->UART_InitStruct.UART_WSIZE == CDNS_UART_WSIZE_4)
        cdns_uart_receive_it(uartHandler, 4);
      else {
        printf("word length is not support yet.\n");
        return;
      }
    }
    if (uartHandler->rxCount >= uartHandler->rxBufSize) {
      uartHandler->rxStatus = UART_RX_COMPLETE;
      // receive compelete callback.
      if (uartHandler->rCCallback != NULL) {
        uartHandler->rCCallback(uartHandler);
      }
    }
  }

  // transmit handle
  if (cdns_uart_get_it(imr, cisr, IxR_TEMPTY_MASK) == SET) {
    DEBUG_LOG("uart%d tx empty interrupt.\n", (int)uartx);
    if (uartHandler->txCount != uartHandler->txBufSize) {
      cdns_uart_transmit_it(uartHandler);
    } else {
      uartHandler->txStatus = UART_TX_COMPLETE;
      // transmit compelete callback.
      if (uartHandler->tCCallback != NULL) {
        uartHandler->tCCallback(uartHandler);
      }
    }
  }
}

static int CDNS_UART_IRQ_Handler(int irq, void *args) {
  UART_HandleTypeDef *uartHandler = (UART_HandleTypeDef *)args;
  cdns_uart_irq_handle_common(uartHandler);
  return 0;
}

static void cdns_uart_register_irq(UART_HandleTypeDef *uartHandler) {
  int ret;
  switch (uartHandler->UART_InitStruct.UARTx) {
  case UART0:
    ret = request_irq(S_UART0_IRQn, CDNS_UART_IRQ_Handler, "uart0",
                      (void *)uartHandler);
    if (ret) {
      replace_irq(S_UART0_IRQn, CDNS_UART_IRQ_Handler, "uart0",
                  (void *)uartHandler);
    }
    break;
  case UART1:
    ret = request_irq(S_UART1_IRQn, CDNS_UART_IRQ_Handler, "uart1",
                      (void *)uartHandler);
    if (ret) {
      replace_irq(S_UART1_IRQn, CDNS_UART_IRQ_Handler, "uart1",
                  (void *)uartHandler);
    }
    break;
  case UART2:
    ret = request_irq(C_UART2_IRQn, CDNS_UART_IRQ_Handler, "uart2",
                      (void *)uartHandler);
    if (ret) {
      replace_irq(C_UART2_IRQn, CDNS_UART_IRQ_Handler, "uart2",
                  (void *)uartHandler);
    }
    break;
  case UART3:
    ret = request_irq(C_UART3_IRQn, CDNS_UART_IRQ_Handler, "uart3",
                      (void *)uartHandler);
    if (ret) {
      replace_irq(C_UART3_IRQn, CDNS_UART_IRQ_Handler, "uart3",
                  (void *)uartHandler);
    }
    break;
  case UART4:
    ret = request_irq(C_UART4_IRQn, CDNS_UART_IRQ_Handler, "uart4",
                      (void *)uartHandler);
    if (ret) {
      replace_irq(C_UART4_IRQn, CDNS_UART_IRQ_Handler, "uart4",
                  (void *)uartHandler);
    }
    break;
  case UART5:
    ret = request_irq(C_UART5_IRQn, CDNS_UART_IRQ_Handler, "uart5",
                      (void *)uartHandler);
    if (ret) {
      replace_irq(C_UART5_IRQn, CDNS_UART_IRQ_Handler, "uart5",
                  (void *)uartHandler);
    }
    break;
  case UART6:
    ret = request_irq(C_UART6_IRQn, CDNS_UART_IRQ_Handler, "uart6",
                      (void *)uartHandler);
    if (ret) {
      replace_irq(C_UART6_IRQn, CDNS_UART_IRQ_Handler, "uart6",
                  (void *)uartHandler);
    }
    break;
  case UART7:
    ret = request_irq(C_UART7_IRQn, CDNS_UART_IRQ_Handler, "uart7",
                      (void *)uartHandler);
    if (ret) {
      replace_irq(C_UART7_IRQn, CDNS_UART_IRQ_Handler, "uart7",
                  (void *)uartHandler);
    }
    break;
  case UART8:
    ret = request_irq(C_UART8_IRQn, CDNS_UART_IRQ_Handler, "uart8",
                      (void *)uartHandler);
    if (ret) {
      replace_irq(C_UART8_IRQn, CDNS_UART_IRQ_Handler, "uart8",
                  (void *)uartHandler);
    }
    break;
  case UART9:
    ret = request_irq(C_UART9_IRQn, CDNS_UART_IRQ_Handler, "uart9",
                      (void *)uartHandler);
    if (ret) {
      replace_irq(C_UART9_IRQn, CDNS_UART_IRQ_Handler, "uart9",
                  (void *)uartHandler);
    }
    break;
  case UART10:
    ret = request_irq(C_UART10_IRQn, CDNS_UART_IRQ_Handler, "uart10",
                      (void *)uartHandler);
    if (ret) {
      replace_irq(C_UART10_IRQn, CDNS_UART_IRQ_Handler, "uart10",
                  (void *)uartHandler);
    }
    break;
  case UART11:
    ret = request_irq(C_UART11_IRQn, CDNS_UART_IRQ_Handler, "uart11",
                      (void *)uartHandler);
    if (ret) {
      replace_irq(C_UART11_IRQn, CDNS_UART_IRQ_Handler, "uart11",
                  (void *)uartHandler);
    }
    break;
  default:
    break;
  }
}

#ifdef CONFIG_DRV_DMA
static bool cdns_uart_dma_init(UART_HandleTypeDef *uartHandler) {
  if (uartHandler->UART_InitStruct.UARTx == 2 ||uartHandler->UART_InitStruct.UARTx == 3) {
    uartHandler->dma.info[UART_DMA_RX].devname              = "dma0";
    uartHandler->dma.info[UART_DMA_RX].src_hw_handshake_num = DMAC0_CUART2_RX;
    uartHandler->dma.info[UART_DMA_TX].devname              = "dma0";
    uartHandler->dma.info[UART_DMA_TX].dst_hw_handshake_num = DMAC0_CUART2_TX;
    if (!itcs_is_dma_inited(0)) {
      itcs_dma_init(0);
      DEBUG_LOG("uart%d DMAC0 init successfully\n",
                (int)uartHandler->UART_InitStruct.UARTx);
    }
  } else {
    uartHandler->dma.info[UART_DMA_RX].devname              = "dma1";
    uartHandler->dma.info[UART_DMA_RX].src_hw_handshake_num = DMAC1_CUART0_RX;
    uartHandler->dma.info[UART_DMA_TX].devname              = "dma1";
    uartHandler->dma.info[UART_DMA_TX].dst_hw_handshake_num = DMAC1_CUART0_TX;
    if (!itcs_is_dma_inited(1)) {
      itcs_dma_init(1);
      DEBUG_LOG("uart%d DMAC1 init successfully\n",
                (int)uartHandler->UART_InitStruct.UARTx);
    }    
  }
  
  switch (uartHandler->UART_InitStruct.UARTx) {
  case UART0:
    uartHandler->dma.info[UART_DMA_RX].devname              = "dma1";
    uartHandler->dma.info[UART_DMA_RX].src_hw_handshake_num = DMAC1_CUART0_RX;
    uartHandler->dma.info[UART_DMA_TX].devname              = "dma1";
    uartHandler->dma.info[UART_DMA_TX].dst_hw_handshake_num = DMAC1_CUART0_TX;
    if (!itcs_is_dma_inited(1)) {
      itcs_dma_init(1);
      DEBUG_LOG("uart%d DMAC1 init successfully\n",
                (int)uartHandler->UART_InitStruct.UARTx);
    }

    break;
  case UART1:
    uartHandler->dma.info[UART_DMA_RX].devname              = "dma1";
    uartHandler->dma.info[UART_DMA_RX].src_hw_handshake_num = DMAC1_CUART1_RX;
    uartHandler->dma.info[UART_DMA_TX].devname              = "dma1";
    uartHandler->dma.info[UART_DMA_TX].dst_hw_handshake_num = DMAC1_CUART1_TX;
    if (!itcs_is_dma_inited(1)) {
      itcs_dma_init(1);
      DEBUG_LOG("uart%d DMAC1 init successfully\n",
                (int)uartHandler->UART_InitStruct.UARTx);
    }
    break;
  case UART2:
    uartHandler->dma.info[UART_DMA_RX].devname              = "dma0";
    uartHandler->dma.info[UART_DMA_RX].src_hw_handshake_num = DMAC0_CUART2_RX;
    uartHandler->dma.info[UART_DMA_TX].devname              = "dma0";
    uartHandler->dma.info[UART_DMA_TX].dst_hw_handshake_num = DMAC0_CUART2_TX;
    if (!itcs_is_dma_inited(0)) {
      itcs_dma_init(0);
      DEBUG_LOG("uart%d DMAC0 init successfully\n",
                (int)uartHandler->UART_InitStruct.UARTx);
    }
    break;
  case UART3:
    uartHandler->dma.info[UART_DMA_RX].devname              = "dma0";
    uartHandler->dma.info[UART_DMA_RX].src_hw_handshake_num = DMAC0_CUART3_RX;
    uartHandler->dma.info[UART_DMA_TX].devname              = "dma0";
    uartHandler->dma.info[UART_DMA_TX].dst_hw_handshake_num = DMAC0_CUART3_TX;
    if (!itcs_is_dma_inited(0)) {
      itcs_dma_init(0);
      DEBUG_LOG("uart%d DMAC0 init successfully\n",
                (int)uartHandler->UART_InitStruct.UARTx);
    }
    break;
  case UART4:
    uartHandler->dma.info[UART_DMA_RX].devname              = "dma1";
    uartHandler->dma.info[UART_DMA_RX].src_hw_handshake_num = DMAC1_CUART4_RX;
    uartHandler->dma.info[UART_DMA_TX].devname              = "dma1";
    uartHandler->dma.info[UART_DMA_TX].dst_hw_handshake_num = DMAC1_CUART4_TX;
    if (!itcs_is_dma_inited(0)) {
      itcs_dma_init(0);
      DEBUG_LOG("uart%d DMAC1 init successfully\n",
                (int)uartHandler->UART_InitStruct.UARTx);
    }
    break;
  case UART5:
    uartHandler->dma.info[UART_DMA_RX].devname              = "dma1";
    uartHandler->dma.info[UART_DMA_RX].src_hw_handshake_num = DMAC1_CUART5_RX;
    uartHandler->dma.info[UART_DMA_TX].devname              = "dma1";
    uartHandler->dma.info[UART_DMA_TX].dst_hw_handshake_num = DMAC1_CUART5_TX;
    if (!itcs_is_dma_inited(0)) {
      itcs_dma_init(0);
      DEBUG_LOG("uart%d DMAC1 init successfully\n",
                (int)uartHandler->UART_InitStruct.UARTx);
    }
    break;
  case UART6:
    uartHandler->dma.info[UART_DMA_RX].devname              = "dma1";
    uartHandler->dma.info[UART_DMA_RX].src_hw_handshake_num = DMAC1_CUART6_RX;
    uartHandler->dma.info[UART_DMA_TX].devname              = "dma1";
    uartHandler->dma.info[UART_DMA_TX].dst_hw_handshake_num = DMAC1_CUART6_TX;
    if (!itcs_is_dma_inited(0)) {
      itcs_dma_init(0);
      DEBUG_LOG("uart%d DMAC1 init successfully\n",
                (int)uartHandler->UART_InitStruct.UARTx);
    }
    break;
  case UART7:
    uartHandler->dma.info[UART_DMA_RX].devname              = "dma1";
    uartHandler->dma.info[UART_DMA_RX].src_hw_handshake_num = DMAC1_CUART7_RX;
    uartHandler->dma.info[UART_DMA_TX].devname              = "dma1";
    uartHandler->dma.info[UART_DMA_TX].dst_hw_handshake_num = DMAC1_CUART7_TX;
    if (!itcs_is_dma_inited(0)) {
      itcs_dma_init(0);
      DEBUG_LOG("uart%d DMAC1 init successfully\n",
                (int)uartHandler->UART_InitStruct.UARTx);
    }
    break;
  case UART8:
    uartHandler->dma.info[UART_DMA_RX].devname              = "dma1";
    uartHandler->dma.info[UART_DMA_RX].src_hw_handshake_num = DMAC1_CUART8_RX;
    uartHandler->dma.info[UART_DMA_TX].devname              = "dma1";
    uartHandler->dma.info[UART_DMA_TX].dst_hw_handshake_num = DMAC1_CUART8_TX;
    if (!itcs_is_dma_inited(0)) {
      itcs_dma_init(0);
      DEBUG_LOG("uart%d DMAC1 init successfully\n",
                (int)uartHandler->UART_InitStruct.UARTx);
    }
    break;
  case UART9:
    uartHandler->dma.info[UART_DMA_RX].devname              = "dma0";
    uartHandler->dma.info[UART_DMA_RX].src_hw_handshake_num = DMAC0_SPI2_RX;
    uartHandler->dma.info[UART_DMA_TX].devname              = "dma0";
    uartHandler->dma.info[UART_DMA_TX].dst_hw_handshake_num = DMAC0_SPI2_TX;
    if (!itcs_is_dma_inited(0)) {
      itcs_dma_init(0);
      DEBUG_LOG("uart%d DMAC0 init successfully\n",
                (int)uartHandler->UART_InitStruct.UARTx);
    }
    break;
  case UART10:
    uartHandler->dma.info[UART_DMA_RX].devname              = "dma0";
    uartHandler->dma.info[UART_DMA_RX].src_hw_handshake_num = DMAC0_SPI3_RX;
    uartHandler->dma.info[UART_DMA_TX].devname              = "dma0";
    uartHandler->dma.info[UART_DMA_TX].dst_hw_handshake_num = DMAC0_SPI3_TX;
    if (!itcs_is_dma_inited(0)) {
      itcs_dma_init(0);
      DEBUG_LOG("uart%d DMAC0 init successfully\n",
                (int)uartHandler->UART_InitStruct.UARTx);
    }
    break;
  case UART11:
    uartHandler->dma.info[UART_DMA_RX].devname              = "dma0";
    uartHandler->dma.info[UART_DMA_RX].src_hw_handshake_num = DMAC0_SPI1_RX;
    uartHandler->dma.info[UART_DMA_TX].devname              = "dma0";
    uartHandler->dma.info[UART_DMA_TX].dst_hw_handshake_num = DMAC0_SPI1_TX;
    if (!itcs_is_dma_inited(0)) {
      itcs_dma_init(0);
      DEBUG_LOG("uart%d DMAC0 init successfully\n",
                (int)uartHandler->UART_InitStruct.UARTx);
    }
    break;
  default:
    break;
  }

  uartHandler->dma.chan[UART_DMA_RX] =
      itcs_dma_request_channel(&uartHandler->dma.info[UART_DMA_RX]);
  if (!uartHandler->dma.chan[UART_DMA_RX]) {
    DEBUG_LOG("uart%d dma chan[rx] is NULL!\n",
              (int)uartHandler->UART_InitStruct.UARTx);
    return false;
  }

  uartHandler->dma.chan[UART_DMA_TX] =
      itcs_dma_request_channel(&uartHandler->dma.info[UART_DMA_TX]);
  if (!uartHandler->dma.chan[UART_DMA_TX]) {
    DEBUG_LOG("uart%d dma chan[tx] is NULL!\n",
              (int)uartHandler->UART_InitStruct.UARTx);
    return false;
  }

  return true;
}

static int cdns_uart_receive_dma(UART_HandleTypeDef *uartHandler) {
  int ret;
  uint32_t burtst_len = CDNS_UART_FIFO_DEPTH / 2;
  /*
  cdns_uart_cmd_single(uartHandler->UART_InitStruct.UARTx, 0, false);
  if(uartHandler->rxBufSize >= burtst_len){
      burtst_len =  CDNS_UART_FIFO_DEPTH/2;
      cdns_uart_set_trigger_level(uartHandler->UART_InitStruct.UARTx, 0, 32);
  }else{
      burtst_len =  1;
      cdns_uart_set_trigger_level(uartHandler->UART_InitStruct.UARTx, 0, 1);
  }
  cdns_uart_cmd_single(uartHandler->UART_InitStruct.UARTx, 0, true);
  */

  uartHandler->dma.cfg[UART_DMA_RX].direction = DMA_DEV_TO_MEM;
  uartHandler->dma.cfg[UART_DMA_RX].src_addr =
      uartHandler->uart_base_addr + REG_FIFO_OFFSET;
  uartHandler->dma.cfg[UART_DMA_RX].dst_addr =
      virt_to_phys(uartHandler->rxBufPtr);
  uartHandler->dma.cfg[UART_DMA_RX].src_addr_width = DMA_SLAVE_BUSWIDTH_1_BYTE;
  uartHandler->dma.cfg[UART_DMA_RX].dst_addr_width = DMA_SLAVE_BUSWIDTH_1_BYTE;
  uartHandler->dma.cfg[UART_DMA_RX].src_burstlen   = burtst_len;
  uartHandler->dma.cfg[UART_DMA_RX].dst_burstlen   = burtst_len;
  uartHandler->dma.cfg[UART_DMA_RX].device_fc      = 0;
  ret = itcs_dma_slave_config(uartHandler->dma.chan[UART_DMA_RX],
                              &uartHandler->dma.cfg[UART_DMA_RX]);
  if (ret < 0) {
    printf("uart%d receive dma slave config failed!\n",
           uartHandler->UART_InitStruct.UARTx);
    return -1;
  }

  uartHandler->dma.prep_info[UART_DMA_RX].direction = DMA_DEV_TO_MEM;
  uartHandler->dma.prep_info[UART_DMA_RX].mode      = DMA_SLAVE;
  uartHandler->dma.prep_info[UART_DMA_RX].dst =
      virt_to_phys(uartHandler->rxBufPtr);
  uartHandler->dma.prep_info[UART_DMA_RX].len =
      uartHandler->rxBufSize - (uartHandler->rxBufSize % burtst_len);
  uartHandler->dma.prep_info[UART_DMA_RX].callback =
      NULL; // cdns_uart_dma_rx_callback;
  // uartHandler->dma.prep_info[UART_DMA_RX].callback_param = uartHandler;
  uartHandler->dma.cookie[UART_DMA_RX] =
      itcs_dma_prepare(uartHandler->dma.chan[UART_DMA_RX],
                       &uartHandler->dma.prep_info[UART_DMA_RX]);
  if (uartHandler->dma.cookie[UART_DMA_RX] < 0) {
    printf("uart%d receive dma prepare failed!\n",
           uartHandler->UART_InitStruct.UARTx);
    return -1;
  }

  DEBUG_LOG("uart%d receive burtst_len=%d, prep_len=%d, rxBufSize=%d\n",
            uartHandler->UART_InitStruct.UARTx, burtst_len,
            uartHandler->dma.prep_info[UART_DMA_RX].len,
            uartHandler->rxBufSize);

  itcs_dcache_flush();
  itcs_dma_start(uartHandler->dma.chan[UART_DMA_RX]);
  printf("uart%d receive dma start!\n", uartHandler->UART_InitStruct.UARTx);
  return 0;
}

static int cdns_uart_transmit_dma(UART_HandleTypeDef *uartHandler) {
  int ret;
  uint32_t burtst_len = CDNS_UART_FIFO_DEPTH / 2;

  /*
  cdns_uart_cmd_single(uartHandler->UART_InitStruct.UARTx, 1, false);

  if(uartHandler->txBufSize >= burtst_len){
      burtst_len =  CDNS_UART_FIFO_DEPTH/2;
      cdns_uart_set_trigger_level(uartHandler->UART_InitStruct.UARTx, 1, 32);
  }else{
      burtst_len =  1;
      cdns_uart_set_trigger_level(uartHandler->UART_InitStruct.UARTx, 1, 1);
  }
  cdns_uart_cmd_single(uartHandler->UART_InitStruct.UARTx, 1, true);
  */

  uartHandler->dma.cfg[UART_DMA_TX].direction = DMA_MEM_TO_DEV;
  uartHandler->dma.cfg[UART_DMA_TX].src_addr =
      virt_to_phys(uartHandler->txBufPtr);
  uartHandler->dma.cfg[UART_DMA_TX].dst_addr =
      uartHandler->uart_base_addr + REG_FIFO_OFFSET;
  uartHandler->dma.cfg[UART_DMA_TX].src_addr_width = DMA_SLAVE_BUSWIDTH_1_BYTE;
  uartHandler->dma.cfg[UART_DMA_TX].dst_addr_width = DMA_SLAVE_BUSWIDTH_1_BYTE;
  uartHandler->dma.cfg[UART_DMA_TX].src_burstlen   = burtst_len;
  uartHandler->dma.cfg[UART_DMA_TX].dst_burstlen   = burtst_len;
  uartHandler->dma.cfg[UART_DMA_TX].device_fc      = 0;
  ret = itcs_dma_slave_config(uartHandler->dma.chan[UART_DMA_TX],
                              &uartHandler->dma.cfg[UART_DMA_TX]);
  if (ret < 0) {
    printf("uart%d transmit dma slave config failed!\n",
           uartHandler->UART_InitStruct.UARTx);
    return -1;
  }

  uartHandler->dma.prep_info[UART_DMA_TX].direction = DMA_MEM_TO_DEV;
  uartHandler->dma.prep_info[UART_DMA_TX].mode      = DMA_SLAVE;
  uartHandler->dma.prep_info[UART_DMA_TX].src =
      virt_to_phys(uartHandler->txBufPtr);
  uartHandler->dma.prep_info[UART_DMA_TX].len      = uartHandler->txBufSize;
  uartHandler->dma.prep_info[UART_DMA_TX].callback = NULL;
  uartHandler->dma.cookie[UART_DMA_TX] =
      itcs_dma_prepare(uartHandler->dma.chan[UART_DMA_TX],
                       &uartHandler->dma.prep_info[UART_DMA_TX]);
  if (uartHandler->dma.cookie[UART_DMA_TX] < 0) {
    printf("uart%d transmit dma prepare failed!\n",
           uartHandler->UART_InitStruct.UARTx);
    return -1;
  }

  DEBUG_LOG("uart%d transmit burtst_len=%d, prep_len=%d, txBufSize=%d\n",
            uartHandler->UART_InitStruct.UARTx,
            uartHandler->dma.cfg[UART_DMA_TX].src_burstlen,
            uartHandler->dma.prep_info[UART_DMA_TX].len,
            uartHandler->txBufSize);

  itcs_dcache_flush();
  itcs_dma_start(uartHandler->dma.chan[UART_DMA_TX]);
  printf("uart%d transmit dma start!\n", uartHandler->UART_InitStruct.UARTx);
  return 0;
}

#endif
UART_HandleTypeDef *cdns_uart_init(UART_InitTypeDef *init) {
  check_param(IS_UART_HANDLER(init));
  unsigned long uart_base;
  uint32_t tempReg;
  UART_InitTypeDef *UART_InitStruct = init;
  UART_HandleTypeDef *uartHandler   = NULL;
  /* Check the parameters */
  check_param(IS_UART_ALL_PERIPH(UART_InitStruct->UARTx));
  check_param(IS_CDNS_UART_BAUDRATE(UART_InitStruct->UART_BaudRate));
  check_param(IS_CDNS_UART_WORD_LENGTH(UART_InitStruct->UART_WordLength));
  check_param(IS_CDNS_UART_STOPBITS(UART_InitStruct->UART_StopBits));
  check_param(IS_CDNS_UART_PARITY(UART_InitStruct->UART_Parity));
  check_param(IS_CDNS_UART_MODE(UART_InitStruct->UART_Mode));
  check_param(IS_CDNS_UART_ChannelMode(UART_InitStruct->UART_ChannelMode));
  check_param(IS_CDNS_UART_WSIZE(UART_InitStruct->UART_WSIZE));
  check_param(IS_CDNS_UART_HARDWARE_FLOW_CONTROL(
      UART_InitStruct->UART_HardwareFlowControl));

  uartHandler = (UART_HandleTypeDef *)malloc(sizeof(UART_HandleTypeDef));
  if (uartHandler == NULL) {
    return NULL;
  }
  memset(uartHandler, 0, sizeof(UART_HandleTypeDef));

  uartHandler->UART_InitStruct = *init;
  uartHandler->rxTriggerCount  = CDNS_UART_FIFO_DEPTH / 2;
  uartHandler->txTriggerCount  = CDNS_UART_FIFO_DEPTH / 2;
  uart_base                    = cdns_get_uart_base(UART_InitStruct->UARTx);
  uartHandler->uart_base_addr  = uart_base;

  /*diasble uart.*/
  cdns_uart_cmd(uartHandler->UART_InitStruct.UARTx, false);

  /* sw reset */
  writel(0x3, uart_base + REG_CTRL_OFFSET);
  while ((readl(uart_base + REG_CTRL_OFFSET) & 0x3))
    ;

  tempReg = readl(uart_base + REG_MODE_OFFSET);

  tempReg &= ~MODE_CHRL_MASK;
  tempReg |= (uint32_t)UART_InitStruct->UART_WordLength;

  tempReg &= ~MODE_PAR_MASK;
  tempReg |= (uint32_t)UART_InitStruct->UART_Parity;

  tempReg &= ~MODE_NBSTOP_MASK;
  tempReg |= (uint32_t)UART_InitStruct->UART_StopBits;

  tempReg &= ~MODE_IRMODE_MASK;
  tempReg |= (uint32_t)UART_InitStruct->UART_Mode;

  tempReg &= ~MODE_CHMODE_MASK;
  tempReg |= (uint32_t)UART_InitStruct->UART_ChannelMode;

  tempReg &= ~MODE_WSIZE_MASK;
  tempReg |= (uint32_t)UART_InitStruct->UART_WSIZE;

  writel(tempReg, uart_base + REG_MODE_OFFSET);

  /*Set flow control */
  cdns_uart_set_flowControl(uartHandler->UART_InitStruct.UARTx,
                            UART_InitStruct->UART_HardwareFlowControl);

  /*Set baud rate */
  #ifdef CONFIG_COMPILE_RTL
  writel(207, uart_base + REG_BDIVR_OFFSET);
  writel(1,uart_base + REG_BRGR_OFFSET);
  #endif
  
  #if defined(CONFIG_COMPILE_FPGA) || defined(CONFIG_COMPILE_ASIC)
  UART_InitStruct->UART_BaudRate = 115200;
  cdns_uart_set_baudrate(uartHandler->UART_InitStruct.UARTx,
                         UART_InitStruct->UART_BaudRate);
  #endif
  uartHandler->txStatus = UART_READY;
  uartHandler->rxStatus = UART_READY;

  /*Uart rx timeout value*/
  writel(0x08, uart_base + REG_RTOR_OFFSET);

  cdns_uart_set_trigger_level(uartHandler->UART_InitStruct.UARTx, 0,
                              uartHandler->rxTriggerCount);

  cdns_uart_set_ir_reg(uartHandler);
  /*Enasble uart.*/
  cdns_uart_cmd(uartHandler->UART_InitStruct.UARTx, true);

  /*Register irq*/
  cdns_uart_register_irq(uartHandler);

  /* dma config*/
  if (uartHandler->UART_InitStruct.use_dma) {
#ifdef CONFIG_DRV_DMA
    cdns_uart_dma_init(uartHandler);
    if (uartHandler->UART_InitStruct.UARTx >= 9) {
      tempReg = readl(0xc5f01420);//uart_dma_handshake
      tempReg |= 1<<(uartHandler->UART_InitStruct.UARTx - 9);
    writel(tempReg, 0xc5f01420);
  }
#else
    printf("cuart dma not support change to interrupt mode.\n");
    uartHandler->UART_InitStruct.use_dma = false;
#endif
  }

  return uartHandler;
}

void cdns_uart_deinit(UART_HandleTypeDef *uartHandler) {
  /* Check the parameters */
  check_param(IS_UART_HANDLER(uartHandler));
  check_param(IS_UART_ALL_PERIPH(uartHandler->UART_InitStruct.UARTx));

  /*diasble uart receiver and transmitter.*/
  cdns_uart_cmd(uartHandler->UART_InitStruct.UARTx, DISABLE);
}

/*******************************************************************
 *@brief:  transmit data in block or noblock mode.
 *@param uartHandler: uart handler pointer.
 *@param data: data buffer pointer.
 *@param size: data buffer size.
 *@return : > 0: transmitted bytes.
 *          <=0: error occurs.
 *******************************************************************/
int cdns_uart_transmit(UART_HandleTypeDef *uartHandler, uint8_t *data,
                       uint32_t size, BlockStatus isBlock) {
  // uint32_t tempReg;
  check_param(IS_UART_HANDLER(uartHandler));
  if (uartHandler->txStatus == UART_READY) {
    if ((data == NULL) || (size <= 0)) {
      return -1;
    }
    uartHandler->txStatus  = UART_BUSY_TX;
    uartHandler->txBufPtr  = data;
    uartHandler->txBufSize = size;
    uartHandler->txCount   = 0;
    uartHandler->errorCode = UART_ERROR_NONE;

    if (uartHandler->UART_InitStruct.use_dma) {
#ifdef CONFIG_DRV_DMA
      cdns_uart_transmit_dma(uartHandler);
      if (isBlock == BLOCK) {
        uartHandler->isTxBlock = BLOCK;
        // waiting for transmit finished.
        while (!cdns_uart_is_completed(uartHandler, UART_TX_COMPLETE))
          ;

        uartHandler->txStatus = UART_READY;
        return uartHandler->txCount;
      }
#endif
    } else {

      cdns_uart_it_config(uartHandler->UART_InitStruct.UARTx, IxR_TEMPTY_MASK,
                          SET);

      if (uartHandler->UART_InitStruct.UART_WSIZE == CDNS_UART_WSIZE_1) {

        DEBUG_LOG("uart%d write:[0x%x] already write %d\n",
                  (int)(uartHandler->UART_InitStruct.UARTx), *data, 1);
        writeb(*data, (uartHandler->uart_base_addr) + REG_FIFO_OFFSET);
        uartHandler->txCount += 1;
        uartHandler->txTotal += 1;

      } else if (uartHandler->UART_InitStruct.UART_WSIZE == CDNS_UART_WSIZE_2) {
        unsigned short dat;
        dat = ((unsigned short)(*(data + 1)) << 8) + *data;
        DEBUG_LOG("uart%d write:[0x%x] already write %d\n",
                  (int)(uartHandler->UART_InitStruct.UARTx), dat, 2);
        writew(dat, (uartHandler->uart_base_addr) + REG_FIFO_OFFSET);
        uartHandler->txCount += 2;
        uartHandler->txTotal += 2;
      } else if (uartHandler->UART_InitStruct.UART_WSIZE == CDNS_UART_WSIZE_4) {
        unsigned int dat;
        dat = ((unsigned int)(*(data + 3)) << 24) +
              ((unsigned int)(*(data + 2)) << 16) +
              ((unsigned int)(*(data + 1)) << 8) + *data;
        DEBUG_LOG("uart%d write:[0x%x] already write %d\n",
                  (int)(uartHandler->UART_InitStruct.UARTx), dat, 4);
        writel(dat, (uartHandler->uart_base_addr) + REG_FIFO_OFFSET);
        uartHandler->txCount += 4;
        uartHandler->txTotal += 4;
      }
    }
    /*block transmit mode*/
    if (isBlock == BLOCK) {
      uartHandler->isTxBlock = BLOCK;
      // waiting for transmit finished.
      while (!cdns_uart_is_completed(uartHandler, UART_TX_COMPLETE))
        ;

      uartHandler->txStatus = UART_READY;
      return uartHandler->txCount;
    }
  } else {
    printf("uart%s is not ready. txStatus = %d\n",
           (int)(uartHandler->UART_InitStruct.UARTx), uartHandler->txStatus);
    return 0;
  }
  return 0;
}

/*******************************************************************
 *@brief:  receive data in block or noblock mode and stores data to
 *         @data buffer.
 *@param uartHandler: uart handler pointer.
 *@param data: data buffer pointer.
 *@param size: data buffer size.
 *@param timeout_ms: used in block mode.
 *@return : > 0: received bytes.
 *          <=0: error occurs.
 *******************************************************************/
int cdns_uart_receive(UART_HandleTypeDef *uartHandler, uint8_t *data,
                      uint32_t size, BlockStatus isBlock) {
  check_param(IS_UART_HANDLER(uartHandler));
  check_param(IS_UART_ALL_PERIPH(uartHandler->UART_InitStruct.UARTx));

  if (uartHandler->rxStatus == UART_READY) {
    if ((data == NULL) || (size <= 0)) {
      return -1;
    }

    uartHandler->rxStatus  = UART_BUSY_RX;
    uartHandler->rxBufPtr  = data;
    uartHandler->rxBufSize = size;
    uartHandler->rxCount   = 0;
    uartHandler->errorCode = UART_ERROR_NONE;

    if (uartHandler->UART_InitStruct.use_dma) {
#ifdef CONFIG_DRV_DMA
      cdns_uart_it_config(uartHandler->UART_InitStruct.UARTx, IxR_TIMEOUT_MASK,
                          ENABLE);
      if (uartHandler->rxBufSize >= 32) {
        cdns_uart_receive_dma(uartHandler);
      }

      if (isBlock == BLOCK) {
        uartHandler->isRxBlock = BLOCK;
        // waiting for transmit finished.
        while (!cdns_uart_is_completed(uartHandler, UART_RX_COMPLETE))
          ;
        uartHandler->rxStatus = UART_READY;
        return uartHandler->rxCount;
      }
#endif
    } else {
      cdns_uart_it_config(uartHandler->UART_InitStruct.UARTx,
                          IxR_RTRIG_MASK | IxR_TIMEOUT_MASK | IxR_ROVR_MASK |
                              IxR_FRAME_MASK | IxR_PARE_MASK | IxR_RBRK_MASK,
                          ENABLE);
    }

    /*block transmit mode*/
    if (isBlock == BLOCK) {
      uartHandler->isRxBlock = BLOCK;
      while (!cdns_uart_is_completed(uartHandler, UART_RX_COMPLETE))
        ;
      uartHandler->rxStatus = UART_READY;
      return uartHandler->rxCount;
    }
    return 0;
  }
  return 0;
}

/*******************************************************************
 *@brief:  check if the receive is complete.
 *@param uartHandler: uart handler pointer.
 *@param tx_rx: should be UART_RX_COMPLETE or UART_TX_COMPLETE
 *@return: 1:  complete.
 *         0: not complete.
 *******************************************************************/
int cdns_uart_is_completed(UART_HandleTypeDef *uartHandler, int tx_rx) {
  int ret;

  check_param(IS_UART_HANDLER(uartHandler));

  if (uartHandler->UART_InitStruct.use_dma) {
#ifdef CONFIG_DRV_DMA
    if (tx_rx == UART_RX_COMPLETE) {
      if (uartHandler->rxStatus == UART_RX_COMPLETE) {
        uartHandler->rxStatus = UART_READY;
        return 0;
      }

      ret = itcs_dma_transfer_completed(uartHandler->dma.chan[UART_DMA_RX],
                                        uartHandler->dma.cookie[UART_DMA_RX],
                                        NULL);
      if (ret == DMA_COMPLETE) {
        uartHandler->rxStatus = UART_READY;
        uartHandler->rxCount  = uartHandler->rxBufSize;
        itcs_dma_stop(uartHandler->dma.chan[UART_DMA_RX]);
        DEBUG_LOG("uart%d recv %d bytes.\n",
                  (int)uartHandler->UART_InitStruct.UARTx,
                  uartHandler->rxBufSize);
        for (int i = 0; i < uartHandler->rxBufSize; i++) {
          DEBUG_LOG("0x%x\n", uartHandler->rxBufPtr[i]);
        }
        return 1;
      } else if (ret == DMA_IN_PROGRESS) {
        return 0;
      } else {
        itcs_dma_stop(uartHandler->dma.chan[UART_DMA_RX]);
        printf("DMA RX SOMETHING HAPPEN! ret = %d\n", ret);
        return 0;
      }
    } else if (tx_rx == UART_TX_COMPLETE) {
      ret = itcs_dma_transfer_completed(uartHandler->dma.chan[UART_DMA_TX],
                                        uartHandler->dma.cookie[UART_DMA_TX],
                                        NULL);
      if (ret == DMA_COMPLETE) {
        uartHandler->txStatus = UART_READY;
        uartHandler->txCount  = uartHandler->txBufSize;
        itcs_dma_stop(uartHandler->dma.chan[UART_DMA_TX]);
        DEBUG_LOG("uart%d trans %d bytes.\n",
                  (int)uartHandler->UART_InitStruct.UARTx,
                  uartHandler->txBufSize);
        for (int i = 0; i < uartHandler->txBufSize; i++) {
          DEBUG_LOG("0x%x\n", uartHandler->txBufPtr[i]);
        }
        return 1;
      } else if (ret == DMA_IN_PROGRESS) {
        return 0;
      } else {
        itcs_dma_stop(uartHandler->dma.chan[UART_DMA_TX]);
        printf("DMA TX SOMETHING HAPPEN! ret = %d\n", ret);
        return 0;
      }
    } else {
      return 0;
    }
#endif
  }

  if (tx_rx == UART_RX_COMPLETE) {
    if (uartHandler->rxStatus == UART_RX_COMPLETE) {
      uartHandler->rxStatus = UART_READY;
      /*
      cdns_uart_it_config(uartHandler->UART_InitStruct.UARTx,
                    IxR_RTRIG_MASK | IxR_TIMEOUT_MASK |
                    IxR_ROVR_MASK  | IxR_FRAME_MASK | IxR_PARE_MASK |
      IxR_RBRK_MASK, RESET);
      */
      return 1;
    } else {
      return 0;
    }
  } else if (tx_rx == UART_TX_COMPLETE) {
    if (uartHandler->txStatus == UART_TX_COMPLETE) {
      uartHandler->txStatus = UART_READY;
      // cdns_uart_it_config(uartHandler->UART_InitStruct.UARTx,
      // IxR_TEMPTY_MASK,RESET);
      return 1;
    } else {
      return 0;
    }
  } else {
    return 0;
  }
  return ret;
}

/*
 * Copyright (C) intchains Holding Limited
 */

/*******************************************************************
 * @file     dwc-uart.c
 * @brief    dwc uart Driver
 * @version  V1.0
 * @date     04.23 2022
 * @name     dwc-uart
 *
 * @author   jason.liu
 *******************************************************************/
#include <common.h>
#include <dwc_uart.h>
#include <asm/io.h>
#include <malloc.h>

#define DWC_FIFO_DEPTH 16

static uint64_t dwc_get_uart_base(UART UARTx) {
  check_param(IS_UART_ALL_PERIPH(UARTx));
  switch (UARTx) {
  case UART0:
    return DWC_UART0_BASE;
    break;
  case UART1:
    return DWC_UART1_BASE;
    break;
  case UART2:
    return DWC_UART2_BASE;
    break;
  case UART3:
    return DWC_UART3_BASE;
    break;
  default:
    return DWC_UART0_BASE; // nerver be here 
  }
}

static void dwc_uart_cmd(UART UARTx, EnableStatus state) {
  /* Check the parameters */
  check_param(IS_UART_ALL_PERIPH(UARTx));
  // do sth
}

static void dwc_uart_it_config(UART UARTx, uint16_t uart_it, BitStatus state) {
  uint32_t tempReg;
  check_param(IS_UART_ALL_PERIPH(UARTx));
  uint64_t uart_base = dwc_get_uart_base(UARTx);

  if (state == RESET) {
    tempReg = readl(uart_base + DWC_REG_IER_OFFSET);
    tempReg &= (uint32_t)(~uart_it);
    writel(tempReg, uart_base + DWC_REG_IER_OFFSET);
  } else if (state == SET) {
    tempReg = readl(uart_base + DWC_REG_IER_OFFSET);
    tempReg |= (uint32_t)uart_it;
    writel(tempReg, uart_base + DWC_REG_IER_OFFSET);
  }
}

static void dwc_set_baudrate(UART UARTx, int baudrate) {

  uint64_t reg_base = dwc_get_uart_base(UARTx);
  /*
  uint64_t uart_base = dwc_get_uart_base(UARTx);
  // uint32_t tempReg;
  uint32_t divisor_l, divisor_h, divisor;
  int pclk;
  // int min_baudRate, max_baudRate;
  check_param(IS_UART_ALL_PERIPH(UARTx));

  //pclk = itcs_module_get_clock("uart-pclk");
  pclk = itcs_module_get_clock("cpu-pclk");
  // set baud rete
  divisor   = pclk / (baudrate * 16);
  divisor_l = divisor & 0xFF;
  divisor_h = (divisor & 0xFF00) >> 8;
  writel(divisor_l, uart_base + DWC_REG_DLL_OFFSET);
  writel(divisor_h, uart_base + DWC_REG_DLH_OFFSET);
  */

  int clk = itcs_module_get_clock("cpu-pclk");
  int divisor;
  uint32_t value;

  divisor = DIV_ROUND(clk, 16 * baudrate);

  // Set DLAB 1 to LCR
  value = readl(reg_base + DWC_REG_LCR_OFFSET);
  value |= (1 << 7);
  writel(value, reg_base + DWC_REG_LCR_OFFSET);
  DEBUG_LOG("DLL = 0x%x\n", divisor & 0xff);
  DEBUG_LOG("DLH = 0x%x\n", divisor >> 8);
  writel(divisor & 0xff, reg_base + DWC_REG_DLL_OFFSET);
  writel(divisor >> 8, reg_base + DWC_REG_DLH_OFFSET);

  // Set DLAB 0 to LCR
  value = readl(reg_base + DWC_REG_LCR_OFFSET);
  value &= ~(1 << 7);
  writel(value, reg_base + DWC_REG_LCR_OFFSET);
}

static int dwc_uart_receive_dma(UART_HandleTypeDef *uartHandler) { return 0; }

static int dwc_uart_transmit_dma(UART_HandleTypeDef *uartHandler) { return 0; }

static int dwc_uart_receive_it(UART_HandleTypeDef *uartHandler) {
  check_param(IS_UART_HANDLER(uartHandler));
  unsigned long uart_base =
      dwc_get_uart_base(uartHandler->UART_InitStruct.UARTx);
  uint32_t tempReg;
  uint32_t byte_wordLength_mask;

  switch (uartHandler->UART_InitStruct.UART_WordLength) {
  case DWC_UART_WordLength_5b:
    byte_wordLength_mask = 0x1F;
    break;
  case DWC_UART_WordLength_6b:
    byte_wordLength_mask = 0x3F;
    break;
  case DWC_UART_WordLength_7b:
    byte_wordLength_mask = 0x7F;
    break;
  case DWC_UART_WordLength_8b:
    byte_wordLength_mask = 0xFF;
    break;
  default:
    byte_wordLength_mask = 0xFF;
    break;
  }

  // if uartHandler is prepared for receiving data
  if (uartHandler->rxStatus == UART_BUSY_RX) {
    int byte_num = 0;
    uint8_t data;
    while (1) {
      tempReg = readl(uart_base + DWC_REG_LSR_OFFSET);
      if (tempReg & DWC_MASK_LSR_DR) {
        data   = readb(uart_base + DWC_REG_RBR_OFFSET) & byte_wordLength_mask;
        *(uartHandler->rxBufPtr + uartHandler->rxCount) = data;
        uartHandler->rxCount += 1;
        uartHandler->rxTotal += 1;
        byte_num++;
        DEBUG_LOG("duart read: 0x%x\n", data);
        if(uartHandler->rxCount == uartHandler->rxBufSize){
            DEBUG_LOG("rx irq recv complete.\n");
            uartHandler->rxStatus = UART_RX_COMPLETE;
            return byte_num;
        }
        
      } else {
        return byte_num;
      }
    }
  }
  return 0;
}

static int dwc_uart_transmit_it(UART_HandleTypeDef *uartHandler) {
  check_param(IS_UART_HANDLER(uartHandler));
  unsigned long uart_base =
      dwc_get_uart_base(uartHandler->UART_InitStruct.UARTx);
  // uint32_t tempReg;
  uint32_t byte_wordLength_mask;

  switch (uartHandler->UART_InitStruct.UART_WordLength) {
  case DWC_UART_WordLength_5b:
    byte_wordLength_mask = 0x1F;
    break;
  case DWC_UART_WordLength_6b:
    byte_wordLength_mask = 0x3F;
    break;
  case DWC_UART_WordLength_7b:
    byte_wordLength_mask = 0x7F;
    break;
  case DWC_UART_WordLength_8b:
    byte_wordLength_mask = 0xFF;
    break;
  default:
    byte_wordLength_mask = 0xFF;
    break;
  }
  // if uartHandler is prepared for transmitting data
  if (uartHandler->txStatus == UART_BUSY_TX) {
    uint8_t data;
    for(int i = 0; (i < (uartHandler->txBufSize - uartHandler->txCount)) && (i < DWC_FIFO_DEPTH); i++ ){
      data = (*(uartHandler->txBufPtr + uartHandler->txCount)) & byte_wordLength_mask;
      writeb(data, uart_base + DWC_REG_THR_OFFSET);
      uartHandler->txCount += 1;
      uartHandler->txTotal += 1;
      DEBUG_LOG("uart write:[0x%x] already write %d\n", data,
              uartHandler->txCount);
      if(uartHandler->txCount == uartHandler->txBufSize){
        uartHandler->txStatus = UART_TX_COMPLETE;
        return 1;
      }
    }
    return 1;
  }
  return 0;
}

static void dwc_uart_irq_handle_common(UART_HandleTypeDef *uartHandler) {
  check_param(IS_UART_HANDLER(uartHandler));

  uint32_t iir = readl(uartHandler->uart_base_addr + DWC_REG_IIR_OFFSET);
  DEBUG_LOG("uart%d irq handle common, iir = 0x%x\n",
            (int)(uartHandler->UART_InitStruct.UARTx), iir);
  // line status error
  if ((iir & DWC_MASK_IIR_IID) == RECEIVER_LINE_STATUS) {
    DEBUG_LOG("line status error irq.\n");
    uint32_t lsr =
        readl(uartHandler->UART_InitStruct.UARTx + DWC_REG_LSR_OFFSET);
    // overrun error
    if (lsr & DWC_MASK_LSR_OE) {
      DEBUG_LOG("overrun error irq.\n");
      uartHandler->errorCode = UART_ERROR_ROVRE;
      if (uartHandler->errCallback != NULL) {
        uartHandler->errCallback(uartHandler);
      }
    }
    // Parity error
    if (lsr & DWC_MASK_LSR_PE) {
      DEBUG_LOG("Parity error irq.\n");
      uartHandler->errorCode = UART_ERROR_PE;
      if (uartHandler->errCallback != NULL) {
        uartHandler->errCallback(uartHandler);
      }
    }
    // Framing error
    if (lsr & DWC_MASK_LSR_FE) {
      DEBUG_LOG("Framing error irq.\n");
      uartHandler->errorCode = UART_ERROR_FE;
      if (uartHandler->errCallback != NULL) {
        uartHandler->errCallback(uartHandler);
      }
    }
    // Break interrupt
    if (lsr & DWC_MASK_LSR_BI) {
      // do sth.
      DEBUG_LOG("Break interrupt irq.\n");
    }
  }

  // received data
  if ((iir & DWC_MASK_IIR_IID) == RECEIVED_DATA_AVALIABLE) {
    dwc_uart_it_config(uartHandler->UART_InitStruct.UARTx,
                         DWC_MASK_IER_ERBFI | DWC_MASK_IER_ELSI, RESET);
    DEBUG_LOG("rx irq.\n");
    dwc_uart_receive_it(uartHandler);
    dwc_uart_it_config(uartHandler->UART_InitStruct.UARTx,
                         DWC_MASK_IER_ERBFI | DWC_MASK_IER_ELSI, SET);
    DEBUG_LOG("handler common rxCount=%d,rxBufSize=%d,rxStatus=%d\n", uartHandler->rxCount, uartHandler->rxBufSize,uartHandler->rxStatus);
  }

  // character timeout
  if ((iir & DWC_MASK_IIR_IID) == CHARACTER_TIMEOUT) {
    dwc_uart_it_config(uartHandler->UART_InitStruct.UARTx,
                         DWC_MASK_IER_ERBFI | DWC_MASK_IER_ELSI, RESET);
    DEBUG_LOG("rx timeout irq.\n");
    if (uartHandler->rxCount == uartHandler->rxBufSize){
      uartHandler->rxStatus = UART_RX_COMPLETE;
    }else{
      dwc_uart_receive_it(uartHandler);
    }
      
    // receive compelete callback.
    if (uartHandler->rCCallback != NULL) {
      uartHandler->rCCallback(uartHandler);
    }
    dwc_uart_it_config(uartHandler->UART_InitStruct.UARTx,
                         DWC_MASK_IER_ERBFI | DWC_MASK_IER_ELSI, SET);
  }

  // THR empty
  if ((iir & DWC_MASK_IIR_IID) == THR_EMPTY) {
    //dwc_uart_it_config(uartHandler->UART_InitStruct.UARTx, DWC_MASK_IER_ETBEI,RESET);
    DEBUG_LOG("tx empty irq.\n");
    DEBUG_LOG("txCount=%d, txBufSize=%d.\n",uartHandler->txCount, uartHandler->txBufSize);
    if (uartHandler->txCount < uartHandler->txBufSize) {
      dwc_uart_transmit_it(uartHandler);
    } else {
      DEBUG_LOG("uart transmit completed.\n");
      uartHandler->txStatus = UART_TX_COMPLETE;
      // transmit compelete callback.
      if (uartHandler->tCCallback != NULL) {
        uartHandler->tCCallback(uartHandler);
      }
    }
    //dwc_uart_it_config(uartHandler->UART_InitStruct.UARTx, DWC_MASK_IER_ETBEI,SET);
  }
}

static int DWC_UART_IRQ_Handler(int irq, void *args) {
  UART_HandleTypeDef *uartHandler = (UART_HandleTypeDef *)args;
  dwc_uart_irq_handle_common(uartHandler);
  return 0;
}

static void dwc_uart_register_irq(UART_HandleTypeDef *uartHandler) {
  unsigned int irq_num;
  irq_num          = DUART0_IRQn + (int)(uartHandler->UART_InitStruct.UARTx);
  switch (uartHandler->UART_InitStruct.UARTx) {
  case UART0:
    request_irq(irq_num, DWC_UART_IRQ_Handler, "duart0", (void *)uartHandler);
    break;
  case UART1:
    request_irq(irq_num, DWC_UART_IRQ_Handler, "duart1", (void *)uartHandler);
    break;
  case UART2:
    request_irq(irq_num, DWC_UART_IRQ_Handler, "duart2", (void *)uartHandler);
    break;
  case UART3:
    request_irq(irq_num, DWC_UART_IRQ_Handler, "duart3", (void *)uartHandler);
    break;
  default:
    break;
  }
}


UART_HandleTypeDef * huartHandler;

UART_HandleTypeDef *dwc_uart_init(UART_InitTypeDef *init) {
  check_param(IS_UART_HANDLER(init));
  uint64_t uart_base;
  uint32_t tempReg;
  UART_InitTypeDef *UART_InitStruct = init;
  UART_HandleTypeDef  *uartHandler   = NULL;
  /* Check the parameters */
  check_param(IS_UART_ALL_PERIPH(UART_InitStruct->UARTx));
  check_param(IS_DWC_UART_BAUDRATE(UART_InitStruct->UART_BaudRate));
  check_param(IS_DWC_UART_WORD_LENGTH(UART_InitStruct->UART_WordLength));
  check_param(IS_DWC_UART_STOPBITS(UART_InitStruct->UART_StopBits));
  check_param(IS_DWC_UART_PARITY(UART_InitStruct->UART_Parity));
  check_param(IS_DWC_UART_MODE(UART_InitStruct->UART_Mode));
  check_param(IS_DWC_UART_HARDWARE_FLOW_CONTROL(
      UART_InitStruct->UART_HardwareFlowControl));
  
  uartHandler = (UART_HandleTypeDef *)malloc(sizeof(UART_HandleTypeDef));
  if (uartHandler == NULL) {
    return NULL;
  }
  DEBUG_LOG("uartHandler addr = 0x%x\n",uartHandler);
  memset(uartHandler, 0, sizeof(UART_HandleTypeDef));
  huartHandler = uartHandler;
  
  uartHandler->UART_InitStruct = *init;
  uart_base                    = dwc_get_uart_base(UART_InitStruct->UARTx);
  uartHandler->uart_base_addr  = uart_base;

  // MCR Register setup
  /*Set mode */
  tempReg = readl(uart_base + DWC_REG_MCR_OFFSET);
  tempReg &= ~DWC_MASK_MCR_SIRE;
  tempReg |= (uint32_t)UART_InitStruct->UART_Mode;
  writel(tempReg, uart_base + DWC_REG_MCR_OFFSET);
  /*Set flow control */
  tempReg = readl(uart_base + DWC_REG_MCR_OFFSET);
  tempReg &= ~DWC_MASK_MCR_AFCE;
  tempReg |= (uint32_t)UART_InitStruct->UART_HardwareFlowControl;
  writel(tempReg, uart_base + DWC_REG_MCR_OFFSET);

  /*Set baud rate */
  dwc_set_baudrate(uartHandler->UART_InitStruct.UARTx,
                   UART_InitStruct->UART_BaudRate);

  // LCR Register setup
  /*Set character length*/
  tempReg = readl(uart_base + DWC_REG_LCR_OFFSET);
  tempReg &= ~DWC_MASK_LCR_DLS;
  tempReg |= (uint32_t)UART_InitStruct->UART_WordLength;
  writel(tempReg, uart_base + DWC_REG_LCR_OFFSET);
  /*Set parity */
  tempReg = readl(uart_base + DWC_REG_LCR_OFFSET);
  tempReg &= ~(DWC_MASK_LCR_PEN | DWC_MASK_LCR_EPS | DWC_MASK_LCR_SP);
  tempReg |= (uint32_t)UART_InitStruct->UART_Parity;
  writel(tempReg, uart_base + DWC_REG_LCR_OFFSET);
  /*Set StopBits */
  tempReg = readl(uart_base + DWC_REG_LCR_OFFSET);
  tempReg &= ~DWC_MASK_LCR_STOP;
  tempReg |= (uint32_t)UART_InitStruct->UART_StopBits;
  writel(tempReg, uart_base + DWC_REG_LCR_OFFSET);

  // FIFO
  // tx fifo trigger , fifo empty
  // rx fifo trigger , 1/2 fifo
  // DMA mode 0
  // 1000 0111
  if (uartHandler->UART_InitStruct.use_dma) {
    // do something
  } else {
    tempReg = (uint32_t)0x87;
    writel(tempReg, uart_base + DWC_REG_FCR_OFFSET);
  }

  /*enasble uart.*/
  dwc_uart_cmd(uartHandler->UART_InitStruct.UARTx, ENABLE);

  uartHandler->txStatus = UART_READY;
  uartHandler->rxStatus = UART_READY;

  /*register irq*/
  dwc_uart_register_irq(uartHandler);
  return uartHandler;
}

void dwc_uart_deinit(UART_HandleTypeDef *uartHandler) {
  check_param(IS_UART_HANDLER(uartHandler));
  check_param(IS_UART_ALL_PERIPH(uartHandler->UART_InitStruct.UARTx));
  dwc_uart_cmd(uartHandler->UART_InitStruct.UARTx, DISABLE);
  return;
}

int dwc_uart_transmit(UART_HandleTypeDef *uartHandler, uint8_t *data,
                      uint32_t size, BlockStatus isBlock) {
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
    if (uartHandler->UART_InitStruct.use_dma == DWC_USED_DMA) {
      dwc_uart_transmit_dma(uartHandler);
    } else {
      dwc_uart_it_config(uartHandler->UART_InitStruct.UARTx, DWC_MASK_IER_ETBEI,
                         SET);
    }

    /*block transmit mode*/
    if (isBlock == BLOCK) {
      uartHandler->isTxBlock = BLOCK;
      while (!dwc_uart_is_completed(uartHandler, UART_TX_COMPLETE))
        ;
      return uartHandler->txCount;
    }
  } else {
    printf("uart%s is not ready. txStatus = %d\n",
           uartHandler->UART_InitStruct.UARTx, uartHandler->txStatus);
    return 0;
  }
  return 0;
}
UART_HandleTypeDef * global_handler;
int dwc_uart_receive(UART_HandleTypeDef *uartHandler, uint8_t *data,
                     uint32_t size, BlockStatus isBlock) {
  check_param(IS_UART_HANDLER(uartHandler));
  check_param(IS_UART_ALL_PERIPH(uartHandler->UART_InitStruct.UARTx));
  global_handler = uartHandler;
  DEBUG_LOG("global_handler addr = %p\n",global_handler);
  if (uartHandler->rxStatus == UART_READY) {
    if ((data == NULL) || (size <= 0)) {
      printf("rx buffer error!\n");
      return -1;
    }
    uartHandler->rxStatus  = UART_BUSY_RX;
    uartHandler->rxBufPtr  = data;
    uartHandler->rxBufSize = size;
    uartHandler->rxCount   = 0;
    uartHandler->errorCode = UART_ERROR_NONE;
    if (uartHandler->UART_InitStruct.use_dma == DWC_USED_DMA) {
      dwc_uart_receive_dma(uartHandler);
    } else {
      dwc_uart_it_config(uartHandler->UART_InitStruct.UARTx,
                         DWC_MASK_IER_ERBFI | DWC_MASK_IER_ELSI, SET);
    }

    /*block transmit mode*/
    if (isBlock == BLOCK) {
      uartHandler->isRxBlock = BLOCK;
      int ret;
      DEBUG_LOG("before uartHandler addr = 0x%x\n",uartHandler);
      while (1){
        if(global_handler != uartHandler){
            DEBUG_LOG("global_handler addr = %p\n",global_handler);
            DEBUG_LOG("uartHandler    addr = %p\n",uartHandler);
        }
        ret = dwc_uart_is_completed(uartHandler, UART_RX_COMPLETE);
        if(ret){
            break;
        }
        if(global_handler != uartHandler){
            DEBUG_LOG("global_handler addr = %p\n",global_handler);
            DEBUG_LOG("uartHandler    addr = %p\n",uartHandler);
        }
        udelay(1000);
      }
      if(global_handler != uartHandler){
            DEBUG_LOG("global_handler addr = %p\n",global_handler);
            DEBUG_LOG("uartHandler    addr = %p\n",uartHandler);
        }
      DEBUG_LOG("uartHandler->rxCount = %d\n",uartHandler->rxCount);
      
      return uartHandler->rxCount;
    }
    DEBUG_LOG("rx non block return\n");
    return 0;
  }
  return 0;
}

int dwc_uart_is_completed(UART_HandleTypeDef *uartHandler, int tx_rx) {
  check_param(IS_UART_HANDLER(uartHandler));
  
  if (tx_rx == UART_RX_COMPLETE) {
    if (uartHandler->rxStatus == UART_RX_COMPLETE) {
      uartHandler->rxStatus = UART_READY;
      return 1;
    } else {
      return 0;
    }
  } else if (tx_rx == UART_TX_COMPLETE) {
    if (uartHandler->txStatus == UART_TX_COMPLETE) {
      dwc_uart_it_config(uartHandler->UART_InitStruct.UARTx, DWC_MASK_IER_ETBEI,
                         RESET);
      uartHandler->txStatus = UART_READY;
      return 1;
    } else {
      return 0;
    }
  } else {
    return 0;
  }
}
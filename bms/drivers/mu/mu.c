/*
 * Copyright (C) intchains Holding Limited
 */

#include <common.h>
#include <asm/io.h>
#include <mu.h>
#include <malloc.h>
#include <math.h>

#define INTERRUPT_MASK_0_REG_NEED_READ 0X01
#define INTERRUPT_MASK_0_REG_CAN_WRITE 0X02

#define MU_EN_FLAG_REG (0xd2e00000 + 0XC0)//reg from wdt

static uint32_t a_recv_data_table[] = {MU_B2A0_REG0_OFFSET, MU_B2A1_REG0_OFFSET,
                                       MU_B2A2_REG0_OFFSET,
                                       MU_B2A3_REG0_OFFSET};

static uint32_t b_recv_data_table[] = {MU_A2B0_REG0_OFFSET, MU_A2B1_REG0_OFFSET,
                                       MU_A2B2_REG0_OFFSET,
                                       MU_A2B3_REG0_OFFSET};

static void mu_clear_irq(MU_Handler *handler, int mu_side, int bitNum) {
  uint32_t data = 1 << bitNum;
  if (mu_side == MU_B_SIDE) {
    DEBUG_LOG_MU("mu clear irq data = 0x%x\n", data);
    writel(data, handler->base_addr + MU_A2B_INTSTA_OFFSET);
  } else {
    DEBUG_LOG_MU("mu clear irq data = 0x%x\n", data);
    writel(data, handler->base_addr + MU_B2A_INTSTA_OFFSET);
  }
}

static uint16_t mu_write(MU_Handler *handler, uint8_t *buf, uint16_t size) {
  int written_bytes = 0;

  if (handler->mu_can_write) {
    uint32_t data = 0;
    int group     = 0;
    DEBUG_LOG_MU("mu write, length = %d\n", handler->tx_size);
    int bytes_can_be_write = 16 < (handler->tx_size - handler->tx_counter)
                                 ? 16
                                 : handler->tx_size - handler->tx_counter;

    while (bytes_can_be_write) {
      DEBUG_LOG_MU("tx_counter=%d, tx_size=%d\n", handler->tx_counter,
                   handler->tx_size);
      if (bytes_can_be_write >= 4) {
        data = 0;
        for (int j = 0; j < 4; j++) {
          data |= (uint32_t)(handler->tx_buf[handler->tx_counter + j])
                  << (8 * j);
        }
        handler->tx_counter += 4;
        written_bytes += 4;
        bytes_can_be_write -= 4;
      } else {
        data = 0;
        for (int j = 0; j < bytes_can_be_write; j++) {
          data |= (uint32_t)(handler->tx_buf[handler->tx_counter + j])
                  << (8 * j);
        }
        written_bytes += bytes_can_be_write;
        handler->tx_counter += bytes_can_be_write;
        bytes_can_be_write = 0;
      }
      // write data to data register
      if (handler->mu_side == MU_A_SIDE) {
        DEBUG_LOG_MU("mu data register=0x%x, write=0x%x\n",
                     handler->base_addr + b_recv_data_table[group], data);
        writel(data, handler->base_addr + b_recv_data_table[group]);
      } else {
        DEBUG_LOG_MU("mu data register=0x%x, write=0x%x\n",
                     handler->base_addr + a_recv_data_table[group], data);
        writel(data, handler->base_addr + a_recv_data_table[group]);
      }
      group++;
    }

    DEBUG_LOG_MU("write done! tx_counter=%d, tx_size=%d\n", handler->tx_counter,
                 handler->tx_size);

    handler->mu_can_write = false;

    // write data length to register01 , trigger irq
    if (handler->mu_side == MU_A_SIDE) {
      if (handler->int_reg_group_can_read == MU_INT_REG_GRP_0_1) {
        DEBUG_LOG_MU("MU_A_SIDE trigger irq MU_A2B0_REG1_OFFSET. reg= 0x%x, "
                     "value=0x%x\n",
                     written_bytes, handler->base_addr + MU_A2B0_REG1_OFFSET);
        writel(written_bytes, handler->base_addr + MU_A2B0_REG1_OFFSET);
      } else {
        DEBUG_LOG_MU("MU_A_SIDE trigger irq MU_A2B2_REG1_OFFSET. reg= 0x%x, "
                     "value=0x%x\n",
                     written_bytes, handler->base_addr + MU_A2B2_REG1_OFFSET);
        writel(written_bytes, handler->base_addr + MU_A2B2_REG1_OFFSET);
      }
    } else {
      if (handler->int_reg_group_can_read == MU_INT_REG_GRP_0_1) {
        DEBUG_LOG_MU("MU_B_SIDE trigger irq MU_B2A0_REG1_OFFSET. reg= 0x%x, "
                     "value=0x%x\n",
                     written_bytes, handler->base_addr + MU_B2A0_REG1_OFFSET);
        writel(written_bytes, handler->base_addr + MU_B2A0_REG1_OFFSET);
      } else {
        DEBUG_LOG_MU("MU_B_SIDE trigger irq MU_B2A2_REG1_OFFSET. reg= 0x%x, "
                     "value=0x%x\n",
                     written_bytes, handler->base_addr + MU_B2A2_REG1_OFFSET);
        writel(written_bytes, handler->base_addr + MU_B2A2_REG1_OFFSET);
      }
    }
  }
  return written_bytes;
}

static int mu_irqhandler(int irq, void *args) {
  MU_Handler *handler = (MU_Handler *)(args);
  int bytes_num;
  uint32_t reg_val;
  uint8_t *rx_buf = handler->rx_buf;

  if (handler->mu_side == MU_A_SIDE) {
    reg_val = readl(handler->base_addr + MU_B2A_INTSTA_OFFSET);
    DEBUG_LOG_MU("mu a side irq arrive, status=0x%x\n", reg_val);
  } else {
    reg_val = readl(handler->base_addr + MU_A2B_INTSTA_OFFSET);
    DEBUG_LOG_MU("mu b side irq arrive, status=0x%x\n", reg_val);
  }

  if (handler->int_reg_group_can_read == MU_INT_REG_GRP_2_1) {
    reg_val = reg_val >> 2;
  }

  if (reg_val & INTERRUPT_MASK_0_REG_NEED_READ) {
    if (handler->int_reg_group_can_read == MU_INT_REG_GRP_0_1) {
      mu_clear_irq(handler, handler->mu_side, 0);
    } else {
      mu_clear_irq(handler, handler->mu_side, 2);
    }

    if (handler->mu_side == MU_A_SIDE) {
      if (handler->int_reg_group_can_read == MU_INT_REG_GRP_0_1) {
        bytes_num = readl(handler->base_addr + MU_B2A0_REG1_OFFSET);
      } else {
        bytes_num = readl(handler->base_addr + MU_B2A2_REG1_OFFSET);
      }
    } else {
      if (handler->int_reg_group_can_read == MU_INT_REG_GRP_0_1) {
        bytes_num = readl(handler->base_addr + MU_A2B0_REG1_OFFSET);
      } else {
        bytes_num = readl(handler->base_addr + MU_A2B2_REG1_OFFSET);
      }
    }

    if (bytes_num) {
      int i            = 0;
      int bytes_remain = bytes_num;
      DEBUG_LOG_MU("mu read %d bytes\n", bytes_remain);
      while (bytes_remain) {
        if (handler->rx_size <= handler->rx_counter) {
          break;
        }

        if (bytes_remain >= 4) {
          if (handler->mu_side == MU_A_SIDE) {
            reg_val = readl(handler->base_addr + a_recv_data_table[i]);
          } else {
            reg_val = readl(handler->base_addr + b_recv_data_table[i]);
          }

          bytes_remain -= 4;
          for (int j = 0; j < 4; j++) {
            rx_buf[handler->rx_counter] = (uint8_t)(reg_val & 0xff);
            DEBUG_LOG_MU("0x%x ", rx_buf[handler->rx_counter]);
            reg_val = reg_val >> 8;
            handler->rx_counter++;
          }
        } else {
          if (handler->mu_side == MU_A_SIDE) {
            reg_val = readl(handler->base_addr + a_recv_data_table[i]);
          } else {
            reg_val = readl(handler->base_addr + b_recv_data_table[i]);
          }
          bytes_remain = 0;
          for (int j = 0; j < bytes_remain; j++) {
            rx_buf[handler->rx_counter] = (uint8_t)(reg_val & 0xff);
            DEBUG_LOG_MU("0x%x ", rx_buf[handler->rx_counter]);
            reg_val = reg_val >> 8;
            handler->rx_counter++;
          }
        }
        i++;
      }
      DEBUG_LOG_MU("\n");
      if (handler->rx_counter == handler->rx_size) {
        handler->rx_status = MU_RX_COMPLETE;
      }
      // trigger can write irq
      if (handler->mu_side == MU_A_SIDE) {
        if (handler->int_reg_group_can_write == MU_INT_REG_GRP_1_1) {
          writel(0x01, handler->base_addr + MU_A2B1_REG1_OFFSET);
        } else {
          writel(0x01, handler->base_addr + MU_A2B3_REG1_OFFSET);
        }
      } else {
        if (handler->int_reg_group_can_write == MU_INT_REG_GRP_1_1) {
          writel(0x01, handler->base_addr + MU_B2A1_REG1_OFFSET);
        } else {
          writel(0x01, handler->base_addr + MU_B2A3_REG1_OFFSET);
        }
      }
    }
  }

  if (reg_val & INTERRUPT_MASK_0_REG_CAN_WRITE) {
    if (handler->int_reg_group_can_write == MU_INT_REG_GRP_1_1) {
      mu_clear_irq(handler, handler->mu_side, 1);
    } else {
      mu_clear_irq(handler, handler->mu_side, 3);
    }
    handler->mu_can_write = true;
    DEBUG_LOG_MU("mu you can write now.\n");
    if (handler->tx_counter < handler->tx_size) {
      mu_write(handler, handler->tx_buf + handler->tx_counter,
               16 < (handler->tx_size - handler->tx_counter)
                   ? 16
                   : handler->tx_size - handler->tx_counter);
      if (handler->tx_counter >= handler->tx_size) {
        handler->tx_status = MU_TX_COMPLETE;
      }
    }
  }

  return 0;
}

static uint32_t mu_register_irq(domain_t domain, MU_Handler *handler) {
  int res;
  if (domain == SAP) {
    if (handler->mu_side == MU_A_SIDE) {
      DEBUG_LOG_MU("MU_A_SIDE register irq S_MU_B2A_IRQn.\n");
      res = request_irq(S_MU_B2A_IRQn, mu_irqhandler, "S_MU_B2A_IRQn",
                        (void *)handler);
    } else {
      DEBUG_LOG_MU("MU_B_SIDE register irq S_MU_A2B_IRQn.\n");
      res = request_irq(S_MU_A2B_IRQn, mu_irqhandler, "S_MU_A2B_IRQn",
                        (void *)handler);
    }

    if (res) {
      printf("sap mu irq request error.\n");
      return res;
    }
  } else {
    if (handler->mu_side == MU_A_SIDE) {
      DEBUG_LOG_MU("MU_A_SIDE register irq C_MU_B2A_IRQn.\n");
      res = request_irq(C_MU_B2A_IRQn, mu_irqhandler, "C_MU_B2A_IRQn",
                        (void *)handler);
    } else {
      DEBUG_LOG_MU("MU_B_SIDE register irq C_MU_A2B_IRQn.\n");
      res = request_irq(C_MU_A2B_IRQn, mu_irqhandler, "C_MU_A2B_IRQn",
                        (void *)handler);
    }
    if (res) {
      printf("cpu mu irq request error.\n");
      return res;
    }
  }

  return 0;
}

MU_Handler *itcs_mu_init(domain_t domain, int mu_side, int irq_group) {
  MU_Handler *handler;
  uint32_t ret;

  handler = (MU_Handler *)malloc(sizeof(MU_Handler));
  if (handler == NULL) {
    return NULL;
  }

  memset(handler, 0, sizeof(MU_Handler));

  if (domain == CPU) {
    handler->base_addr = ITCS_C_MU_BASE;
  } else {
    handler->base_addr = ITCS_S_MU_BASE;
  }

  if (irq_group == 0) {
    handler->int_reg_group_can_read  = MU_INT_REG_GRP_0_1;
    handler->int_reg_group_can_write = MU_INT_REG_GRP_1_1;
  } else {
    handler->int_reg_group_can_read  = MU_INT_REG_GRP_2_1;
    handler->int_reg_group_can_write = MU_INT_REG_GRP_3_1;
  }

  // MU moudle should enable by role A.
  if (mu_side == MU_A_SIDE) {
    ret = itcs_module_enable(domain, "mu");
    if (ret) {
      return NULL;
    }
    if (domain == CPU) {
      DEBUG_LOG_MU("C_MU enable success.\n");
    } else {
      DEBUG_LOG_MU("S_MU enable success.\n");
    }
    writel(0x88, MU_EN_FLAG_REG);
    
    udelay(1);
    // enable irq
    if (handler->int_reg_group_can_read == MU_INT_REG_GRP_0_1) {
      DEBUG_LOG_MU("MU_A_SIDE write irq MU_B2A_INTEN_OFFSET = 0x03.\n");
      writel(0x03, handler->base_addr + MU_B2A_INTEN_OFFSET);
    } else {
      DEBUG_LOG_MU("MU_A_SIDE write irq MU_B2A_INTEN_OFFSET = 0x0C.\n");
      writel(0x0C, handler->base_addr + MU_B2A_INTEN_OFFSET);
    }

  } else {
    while(1){
      uint32_t value = readl(MU_EN_FLAG_REG);
      DEBUG_LOG_MU("read MU_EN_FLAG_REG value =  %d.\n", value);
      if (value != 0x88) {
        udelay(1);
      }else{
        writel(0x0, MU_EN_FLAG_REG);
        break;
      }
    }
    // enable irq
    if (handler->int_reg_group_can_read == MU_INT_REG_GRP_0_1) {
      DEBUG_LOG_MU("MU_B_SIDE write irq MU_A2B_INTEN_OFFSET = 0x03.\n");
      writel(0x03, handler->base_addr + MU_A2B_INTEN_OFFSET);
    } else {
      DEBUG_LOG_MU("MU_B_SIDE write irq MU_A2B_INTEN_OFFSET = 0x0C.\n");
      writel(0x0C, handler->base_addr + MU_A2B_INTEN_OFFSET);
    }
  }

  handler->mu_side      = mu_side;
  handler->domain       = domain;
  handler->rx_status    = MU_READY;
  handler->tx_status    = MU_READY;
  handler->mu_can_write = true;

  ret = mu_register_irq(domain, handler);
  if (ret) {
    free(handler);
    return NULL;
  }

  return handler;
}

uint16_t itcs_mu_write(MU_Handler *handler, uint8_t *buf, uint16_t size,
                       bool isBlock) {
  uint16_t ret = 0;
  if ((handler->tx_status == MU_READY) ||
      (handler->tx_status == MU_TX_COMPLETE)) {
    handler->tx_buf     = buf;
    handler->tx_counter = 0;
    handler->tx_size    = size;
    handler->tx_status  = MU_TX_RUNNING;
  }

  ret = mu_write(handler, handler->tx_buf,
                 16 < (handler->tx_size - handler->tx_counter)
                     ? 16
                     : handler->tx_size - handler->tx_counter);
  if (handler->tx_counter >= handler->tx_size) {
    handler->tx_status = MU_TX_COMPLETE;
  }

  if (isBlock) {
    while (1) {
      if (itcs_mu_get_status(handler, MU_WRITE) == MU_TX_COMPLETE) {
        handler->tx_status = MU_READY;
        break;
      }
      udelay(10);
    }
  } else {
    return ret;
  }

  return 0;
}

uint16_t itcs_mu_read(MU_Handler *handler, uint8_t *buf, uint16_t size,
                      bool isBlock) {
  if ((handler->rx_status == MU_READY) ||
      (handler->rx_status == MU_RX_COMPLETE)) {
    handler->rx_buf     = buf;
    handler->rx_counter = 0;
    handler->rx_size    = size;
    handler->rx_status  = MU_RX_RUNNING;
  } else {
    printf("rx is not ready or complete!\n");
    return -1;
  }

  if (isBlock) {
    while (1) {
      if (handler->rx_status == MU_RX_COMPLETE) {
        return handler->rx_counter;
      }
    }
  } else {
    return 0;
  }
}

uint16_t itcs_mu_get_status(MU_Handler *handler, uint8_t read_write) {
  if (read_write == MU_READ) {
    if (handler->rx_status == MU_RX_COMPLETE) {
      handler->rx_status = MU_READY;
      return MU_RX_COMPLETE;
    }
    return handler->rx_status;
  } else if (read_write == MU_WRITE) {
    if (handler->tx_status == MU_TX_COMPLETE) {
      handler->tx_status = MU_READY;
      return MU_TX_COMPLETE;
    }
    return handler->tx_status;
  } else {
    printf("param error\n");
    return MU_ERROR;
  }
}

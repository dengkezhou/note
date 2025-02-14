#ifndef __MU_H__
#define __MU_H__

#include <stdint.h>
#include <irq.h>

//#define DEBUG_MU
#ifdef DEBUG_MU
#define DEBUG_LOG_MU(format, ...) printf(format, ##__VA_ARGS__)
#else
#define DEBUG_LOG_MU(format, ...)
#endif

#define MU_A2B_INTEN_OFFSET  0x00
#define MU_A2B_INTSTA_OFFSET 0x04
#define MU_A2B0_REG0_OFFSET  0x08
#define MU_A2B0_REG1_OFFSET  0x0C
#define MU_A2B1_REG0_OFFSET  0x10
#define MU_A2B1_REG1_OFFSET  0x14
#define MU_A2B2_REG0_OFFSET  0x18
#define MU_A2B2_REG1_OFFSET  0x1C
#define MU_A2B3_REG0_OFFSET  0x20
#define MU_A2B3_REG1_OFFSET  0x24

#define MU_B2A_INTEN_OFFSET  0x28
#define MU_B2A_INTSTA_OFFSET 0x2C
#define MU_B2A0_REG0_OFFSET  0x30 // for data reg[0] , 4bytes width
#define MU_B2A0_REG1_OFFSET                                                    \
  0x34 // can read irq(write byte length to trigger irq)
#define MU_B2A1_REG0_OFFSET 0x38 // for data reg[1] , 4bytes width
#define MU_B2A1_REG1_OFFSET 0x3C // can write irq(write anything to trigger irq)
#define MU_B2A2_REG0_OFFSET 0x40 // for data reg[2] , 4bytes width
#define MU_B2A2_REG1_OFFSET 0x44 // unsed
#define MU_B2A3_REG0_OFFSET 0x48 // for data reg[3] , 4bytes width
#define MU_B2A3_REG1_OFFSET 0x4C // unsed

#define MU_ATOMIC_LOCK_BASE_OFFSET 0x50
#define MU_ATOMIC_LOCK_REG_NUM     32

#define MU_A_SIDE 0
#define MU_B_SIDE 1
#define MU_READ   0
#define MU_WRITE  1

typedef enum {
  MU_READY = 0,
  MU_RX_RUNNING,
  MU_TX_RUNNING,
  MU_RX_WAITING,
  MU_TX_WAITING,
  MU_RX_COMPLETE,
  MU_TX_COMPLETE,
  MU_ERROR
} MU_STATUS;

typedef struct mu_handler_s {
  domain_t domain;
  unsigned long base_addr;
  int mu_side;
  bool mu_can_write;
  uint8_t int_reg_group_can_read;
  uint8_t int_reg_group_can_write;
#define MU_INT_REG_GRP_0_1 0
#define MU_INT_REG_GRP_1_1 1
#define MU_INT_REG_GRP_2_1 2
#define MU_INT_REG_GRP_3_1 3

  uint8_t *tx_buf;
  uint16_t tx_size;
  uint16_t tx_counter;
  uint8_t tx_status;

  uint8_t *rx_buf;
  uint16_t rx_size;
  uint16_t rx_counter;
  uint8_t rx_status;

  void (*irq_callback)(struct mu_handler_s *handler);
} MU_Handler;

MU_Handler *itcs_mu_init(domain_t domain, int mu_side, int irq_group);
uint16_t itcs_mu_write(MU_Handler *handler, uint8_t *buf, uint16_t size,
                       bool isBlock);
uint16_t itcs_mu_read(MU_Handler *handler, uint8_t *buf, uint16_t size,
                      bool isBlock);
uint16_t itcs_mu_get_status(MU_Handler *handler, uint8_t read_write);

#endif //__MU_H__
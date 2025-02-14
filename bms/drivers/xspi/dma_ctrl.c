/***********************************************************************
 * copyright (C) 2014 Cadence Design Systems
 * All rights reserved.
 ***********************************************************************
 * @file           $RCSfile: $
 * @project        $Name:  $
 * @version        $Revision: $
 * @author         kswitala@cadence.com
 * @date           $Date: $
 * @desc           DMA controller functions
 ***********************************************************************/

#include "sw_hw_wrapper.h"
#include "dma_ctrl.h"
#include <common.h>
#include <cache.h>

void dma_write_data(uint64_t sys_mem_addr, uint64_t target_dut_addr,
                    uint32_t size) {
  /* Put your implementation of DMA write function here */

  IOWR_32(DMAC_CFG, 0x01); // DMAC_EN
  IOWR_32(CH_CFG_L, 0x00); // DST/SRC_MULTBLK_TYPE
  IOWR_32(CH_CFG_H,
          0x00); // TT_FC Transfer Type and Flow Control is Memory to Memory and
                 // Flow controller is Destination peripheral

  IOWR_32(CH_SAR_L, (sys_mem_addr & 0xffffffff));
  IOWR_32(CH_SAR_H, (sys_mem_addr >> 32));
  IOWR_32(CH_DAR_L, (target_dut_addr & 0xffffffff));
  IOWR_32(CH_DAR_H, (target_dut_addr >> 32));
  IOWR_32(CH_BLOCK_TS, (size >> 3) - 1);
  IOWR_32(CH_CTL_H,
          (0x1 << 26   // Enables CHx_IntStatusReg.BLOCK_TFR_DONE_IntStat field
           | 0x0 << 16 // AWLEN
           | 0x0 << 15 // AWLEN_EN
           | 0x0 << 7  // ARLEN
           | 0x0 << 6  // ARLEN_EN
           ));
  IOWR_32(CH_CTL_L, (0x2 << 18 // DST_MSIZE, Destination Burst Ttansaction
                               // Length: 0x2=8 Data Item read from Destination
                     | 0x2 << 14 // SRC_MSIZE, Source Burst Transfer Length:
                                 // 0x2=8 Data Item read from Source
                     | 0x3 << 11 // DST_TR_WIDTH, Destination Transfer Width.
                                 // 0x3=Transfer Width is 64bits
                     | 0x3 << 8 // SRC_TR_WIDTH, Destination Transfer Width.
                                // 0x3=Transfer Width is 64bits
                     | 0x0 << 6 // DINC, Destination Address Increment.
                     | 0x0 << 4 // SINC, Source Address Increment.
                     | 0x1 << 2 // DMS, Destination Master Select.
                     | 0x0 << 0 // SMS, Source Master Select.
                     ));

  itcs_dcache_flush();
  IOWR_32(DMAC_CHEN, 0x101);
}

void dma_read_data(uint64_t sys_mem_addr, uint64_t target_dut_addr,
                   uint32_t size) {
  /* Put your implementation of DMA read function here */

  IOWR_32(DMAC_CFG, 0x01); // DMAC_EN
  IOWR_32(CH_CFG_L, 0x00); // DST/SRC_MULTBLK_TYPE
  IOWR_32(CH_CFG_H,
          0x00); // TT_FC Transfer Type and Flow Control is Memory to Memory and
                 // Flow controller is Destination peripheral

  IOWR_32(CH_SAR_L, (target_dut_addr & 0xffffffff));
  IOWR_32(CH_SAR_H, (target_dut_addr >> 32));
  IOWR_32(CH_DAR_L, (sys_mem_addr & 0xffffffff));
  IOWR_32(CH_DAR_H, (sys_mem_addr >> 32));
  IOWR_32(CH_BLOCK_TS, (size >> 3) - 1);
  IOWR_32(CH_CTL_H,
          (0x1 << 26   // Enables CHx_IntStatusReg.BLOCK_TFR_DONE_IntStat field
           | 0x0 << 16 // AWLEN
           | 0x0 << 15 // AWLEN_EN
           | 0x0 << 7  // ARLEN
           | 0x0 << 6  // ARLEN_EN
           ));
  IOWR_32(CH_CTL_L, (0x2 << 18 // DST_MSIZE, Destination Burst Ttansaction
                               // Length: 0x2=8 Data Item read from Destination
                     | 0x2 << 14 // SRC_MSIZE, Source Burst Transfer Length:
                                 // 0x2=8 Data Item read from Source
                     | 0x3 << 11 // DST_TR_WIDTH, Destination Transfer Width.
                                 // 0x3=Transfer Width is 64bits
                     | 0x3 << 8 // SRC_TR_WIDTH, Destination Transfer Width.
                                // 0x3=Transfer Width is 64bits
                     | 0x0 << 6 // DINC, Destination Address Increment.
                     | 0x0 << 4 // SINC, Source Address Increment.
                     | 0x1 << 2 // DMS, Destination Master Select.
                     | 0x0 << 0 // SMS, Source Master Select.
                     ));

  itcs_dcache_flush();
  IOWR_32(DMAC_CHEN, 0x101);

  // for(uint64_t i=0; i<size; i=i+8){
  //    *((uint64_t *)(sys_mem_addr + i)) = *((uint64_t *)(target_dut_addr +
  //    i));
  //    //asm("sync.is");
  //}
}

void dma_wait() {
  /* Put your implementation of wait for DMA ready function */
  uint32_t _status;

  do {
    _status = IORD_32(CH_INTSTATUS);
  } while (!(_status & (1 << 0))); //[0]:CHx_IntStatusReg.BLOCK_TFR_DONE_IntStat-Block
                                   //Transfer completed
  IOWR_32(CH_INTCLEAR,
          0x1); // Clear Interrupt of CHx_IntStatusReg.BLOCK_TFR_DONE_IntStat
  IOWR_32(DMAC_CHEN, 0x000); // Disable CH1
}

void dma_config(uint8_t max_word_size) {
  /* Put your implementation of DMA configuration function */
}

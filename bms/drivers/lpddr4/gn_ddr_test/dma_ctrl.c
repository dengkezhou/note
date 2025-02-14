
#include "../lpddr4_common.h"
#include "dma_ctrl.h"

void dma_write_data_chan(uint64_t sys_mem_addr, uint64_t target_dut_addr, uint32_t size, int channel, int width)  {
  /* Put your implementation of DMA write function here */
  
  int CH_OFST   = 0x100;
  int REAL_CHAN = channel;

  MA_OUTW(DMAC_CFG, 0x01);    //DMAC_EN

  MA_OUTW(CH_CFG_L+CH_OFST*REAL_CHAN, 0x00);    //DST/SRC_MULTBLK_TYPE
  MA_OUTW(CH_CFG_H+CH_OFST*REAL_CHAN, 0x00);    //TT_FC Transfer Type and Flow Control is Memory to Memory and Flow controller is Destination peripheral

  MA_OUTW(CH_SAR_L+CH_OFST*REAL_CHAN, (sys_mem_addr & 0xffffffff));
  MA_OUTW(CH_SAR_H+CH_OFST*REAL_CHAN, (sys_mem_addr >> 32));

  MA_OUTW(CH_DAR_L+CH_OFST*REAL_CHAN, (target_dut_addr & 0xffffffff));
  MA_OUTW(CH_DAR_H+CH_OFST*REAL_CHAN, (target_dut_addr >> 32));

  MA_OUTW(CH_BLOCK_TS+CH_OFST*REAL_CHAN, (size-1) ); // (size>>3)-1

  MA_OUTW(CH_CTL_H+CH_OFST*REAL_CHAN, ( 0x1 << 26   //Enables CHx_IntStatusReg.BLOCK_TFR_DONE_IntStat field
                    | 0x0 << 16   //AWLEN
                    | 0x0 << 15   //AWLEN_EN
                    | 0x0 << 7    //ARLEN
                    | 0x0 << 6    //ARLEN_EN
                    ));
  MA_OUTW(CH_CTL_L+CH_OFST*REAL_CHAN, ( 0x2 << 18   //DST_MSIZE, Destination Burst Ttansaction Length: 0x2=8 Data Item read from Destination
                    | 0x2 << 14   //SRC_MSIZE, Source Burst Transfer Length: 0x2=8 Data Item read from Source
                    | 3 << 11   //DST_TR_WIDTH, Destination Transfer Width. 0x3=Transfer Width is 64bits
                    | 3 << 8    //SRC_TR_WIDTH, Destination Transfer Width. 0x3=Transfer Width is 64bits
                    | 0x0 << 6    //DINC, Destination Address Increment.
                    | 0x0 << 4    //SINC, Source Address Increment.
                    | 0x1 << 2    //DMS, Destination Master Select.
                    | 0x0 << 0    //SMS, Source Master Select.
                    ));

  MA_OUTW(DMAC_CHEN, 0x101 << REAL_CHAN); // soft only enable channel, cannot disable channel.
                                             // channel: 1-8

}

void dma_write_data(uint64_t sys_mem_addr, uint64_t target_dut_addr, uint32_t size)  {
  /* Put your implementation of DMA write function here */

  MA_OUTW(DMAC_CFG, 0x01);    //DMAC_EN
  MA_OUTW(CH_CFG_L, 0x00);    //DST/SRC_MULTBLK_TYPE
  MA_OUTW(CH_CFG_H, 0x00);    //TT_FC Transfer Type and Flow Control is Memory to Memory and Flow controller is Destination peripheral

  MA_OUTW(CH_SAR_L, (sys_mem_addr & 0xffffffff));
  MA_OUTW(CH_SAR_H, (sys_mem_addr >> 32));
  MA_OUTW(CH_DAR_L, (target_dut_addr & 0xffffffff));
  MA_OUTW(CH_DAR_H, (target_dut_addr >> 32));
  MA_OUTW(CH_BLOCK_TS, (size>>3)-1);
  MA_OUTW(CH_CTL_H, ( 0x1 << 26   //Enables CHx_IntStatusReg.BLOCK_TFR_DONE_IntStat field
                    | 0x0 << 16   //AWLEN
                    | 0x0 << 15   //AWLEN_EN
                    | 0x0 << 7    //ARLEN
                    | 0x0 << 6    //ARLEN_EN
                    ));
  MA_OUTW(CH_CTL_L, ( 0x3 << 18   //DST_MSIZE, Destination Burst Ttansaction Length: 0x2=8 Data Item read from Destination
                    | 0x3 << 14   //SRC_MSIZE, Source Burst Transfer Length: 0x2=8 Data Item read from Source
                    | 0x3 << 11   //DST_TR_WIDTH, Destination Transfer Width. 0x3=Transfer Width is 64bits
                    | 0x3 << 8    //SRC_TR_WIDTH, Destination Transfer Width. 0x3=Transfer Width is 64bits
                    | 0x0 << 6    //DINC, Destination Address Increment.
                    | 0x0 << 4    //SINC, Source Address Increment.
                    | 0x1 << 2    //DMS, Destination Master Select.
                    | 0x0 << 0    //SMS, Source Master Select.
                    ));

  MA_OUTW(DMAC_CHEN, 0x101);

}


void dma_read_data(uint64_t sys_mem_addr, uint64_t target_dut_addr, uint32_t size)  {
    /* Put your implementation of DMA read function here */
#if 1
    MA_OUTW(DMAC_CFG, 0x01);    //DMAC_EN
    MA_OUTW(CH_CFG_L, 0x00);    //DST/SRC_MULTBLK_TYPE
    MA_OUTW(CH_CFG_H, 0x00);    //TT_FC Transfer Type and Flow Control is Memory to Memory and Flow controller is Destination peripheral

    MA_OUTW(CH_SAR_L, (target_dut_addr & 0xffffffff));
    MA_OUTW(CH_SAR_H, (target_dut_addr >> 32));
    MA_OUTW(CH_DAR_L, (sys_mem_addr & 0xffffffff));
    MA_OUTW(CH_DAR_H, (sys_mem_addr >> 32));
    MA_OUTW(CH_BLOCK_TS, (size>>3)-1);
    MA_OUTW(CH_CTL_H, ( 0x1 << 26   //Enables CHx_IntStatusReg.BLOCK_TFR_DONE_IntStat field
                      | 0x0 << 16   //AWLEN
                      | 0x0 << 15   //AWLEN_EN
                      | 0x0 << 7    //ARLEN
                      | 0x0 << 6    //ARLEN_EN
                      ));
    MA_OUTW(CH_CTL_L, ( 0x3 << 18   //DST_MSIZE, Destination Burst Ttansaction Length: 0x2=8 Data Item read from Destination
                      | 0x3 << 14   //SRC_MSIZE, Source Burst Transfer Length: 0x2=8 Data Item read from Source
                      | 0x3 << 11   //DST_TR_WIDTH, Destination Transfer Width. 0x3=Transfer Width is 64bits
                      | 0x3 << 8    //SRC_TR_WIDTH, Destination Transfer Width. 0x3=Transfer Width is 64bits
                      | 0x0 << 6    //DINC, Destination Address Increment.
                      | 0x0 << 4    //SINC, Source Address Increment.
                      | 0x1 << 2    //DMS, Destination Master Select.
                      | 0x0 << 0    //SMS, Source Master Select.
                      ));

    MA_OUTW(DMAC_CHEN, 0x101);
#else
    for(uint64_t i=0; i<size; i=i+8){
        *((uint64_t *)(sys_mem_addr + i)) = *((uint64_t *)(target_dut_addr + i));
        //asm("sync.is");
    }
#endif
}

void dma_wait () {
  /* Put your implementation of wait for DMA ready function */
  uint32_t  _status;

  do {
    _status  = MA_INW(CH_INTSTATUS);
  } while (!(_status & (1<<0)));  //[0]:CHx_IntStatusReg.BLOCK_TFR_DONE_IntStat-Block Transfer completed
  MA_OUTW(CH_INTCLEAR, 0x1);  //Clear Interrupt of CHx_IntStatusReg.BLOCK_TFR_DONE_IntStat
  MA_OUTW(DMAC_CHEN, 0x000);  //Disable CH1
}

void dma_config (uint8_t max_word_size) {
  /* Put your implementation of DMA configuration function */
}

void dma_wait_chan (int disable_channel) {
  /* Put your implementation of wait for DMA ready function */
  uint32_t  _status;
  int CH_OFST   = 0x100;
  int REAL_CHAN = disable_channel;

  do {
    _status  = MA_INW(CH_INTSTATUS+CH_OFST*REAL_CHAN);
  } while (!(_status & (1<<0)));  //[0]:CHx_IntStatusReg.BLOCK_TFR_DONE_IntStat-Block Transfer completed
  MA_OUTW(CH_INTCLEAR+CH_OFST*REAL_CHAN, 0x1);  //Clear Interrupt of CHx_IntStatusReg.BLOCK_TFR_DONE_IntStat
  MA_OUTW(DMAC_CHEN, 0x000);  //Disable CH1
}


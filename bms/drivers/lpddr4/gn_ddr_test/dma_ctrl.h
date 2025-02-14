#ifndef _PERF_DMA_CTRL_H_
  #define _PERF_DMA_CTRL_H_

#include "../lpddr4_common.h"

#if 0
  #define DMA_BASEADDR  0x76000000

  #define DMA_REG_CTRL        (DMA_BASEADDR + 0x00)
    #define DMA_START         0
    #define DMA_STATUS        0
    #define DMA_DIR           1
  #define DMA_REG_DATA_SIZE   (DMA_BASEADDR + 0x04)
  #define DMA_REG_ADDR_FROM_L (DMA_BASEADDR + 0x08)
  #define DMA_REG_ADDR_FROM_H (DMA_BASEADDR + 0x0C)
  #define DMA_REG_ADDR_TO_L   (DMA_BASEADDR + 0x10)
  #define DMA_REG_ADDR_TO_H   (DMA_BASEADDR + 0x14)
  #define DMA_REG_CONFIG      (DMA_BASEADDR + 0x18)
  #define DMA_REG_ADDR_FROM_STRB_L (DMA_BASEADDR + 0x1C)
  #define DMA_REG_ADDR_FROM_STRB_H (DMA_BASEADDR + 0x20)
    #define DMA_MAX_WORD_SIZE 0
#else
    #define DMA_BASEADDR  0xC5500000

    #define DMAC_ID                     (DMA_BASEADDR + 0x000) /* R DMAC ID */
    #define DMAC_COMPVER                (DMA_BASEADDR + 0x008) /* R DMAC Component Version */
    #define DMAC_CFG                    (DMA_BASEADDR + 0x010) /* R/W DMAC Configuration */
    #define DMAC_CHEN                   (DMA_BASEADDR + 0x018) /* R/W DMAC Channel Enable */
    #define DMAC_CHEN_L                 (DMA_BASEADDR + 0x018) /* R/W DMAC Channel Enable 00-31 */
    #define DMAC_CHEN_H                 (DMA_BASEADDR + 0x01C) /* R/W DMAC Channel Enable 32-63 */
    #define DMAC_INTSTATUS              (DMA_BASEADDR + 0x030) /* R DMAC Interrupt Status */
    #define DMAC_COMMON_INTCLEAR        (DMA_BASEADDR + 0x038) /* W DMAC Interrupt Clear */
    #define DMAC_COMMON_INTSTATUS_ENA   (DMA_BASEADDR + 0x040) /* R DMAC Interrupt Status Enable */
    #define DMAC_COMMON_INTSIGNAL_ENA   (DMA_BASEADDR + 0x048) /* R/W DMAC Interrupt Signal Enable */
    #define DMAC_COMMON_INTSTATUS       (DMA_BASEADDR + 0x050) /* R DMAC Interrupt Status */
    #define DMAC_RESET                  (DMA_BASEADDR + 0x058) /* R DMAC Reset Register1 */

    //channel 0:
    #define DMA_CH0_BASEADDR            (DMA_BASEADDR + 0x100)
    #define CH_SAR                      (DMA_CH0_BASEADDR + 0x000) /* R/W Chan Source Address */
    #define CH_SAR_L                    (DMA_CH0_BASEADDR + 0x000) /* R/W Chan Source Address */
    #define CH_SAR_H                    (DMA_CH0_BASEADDR + 0x004) /* R/W Chan Source Address */
    #define CH_DAR                      (DMA_CH0_BASEADDR + 0x008) /* R/W Chan Destination Address */
    #define CH_DAR_L                    (DMA_CH0_BASEADDR + 0x008) /* R/W Chan Destination Address */
    #define CH_DAR_H                    (DMA_CH0_BASEADDR + 0x00C) /* R/W Chan Destination Address */
    #define CH_BLOCK_TS                 (DMA_CH0_BASEADDR + 0x010) /* R/W Chan Block Transfer Size */
    #define CH_CTL                      (DMA_CH0_BASEADDR + 0x018) /* R/W Chan Control */
    #define CH_CTL_L                    (DMA_CH0_BASEADDR + 0x018) /* R/W Chan Control 00-31 */
    #define CH_CTL_H                    (DMA_CH0_BASEADDR + 0x01C) /* R/W Chan Control 32-63 */
    #define CH_CFG                      (DMA_CH0_BASEADDR + 0x020) /* R/W Chan Configuration */
    #define CH_CFG_L                    (DMA_CH0_BASEADDR + 0x020) /* R/W Chan Configuration 00-31 */
    #define CH_CFG_H                    (DMA_CH0_BASEADDR + 0x024) /* R/W Chan Configuration 32-63 */
    #define CH_LLP                      (DMA_CH0_BASEADDR + 0x028) /* R/W Chan Linked List Pointer */
    #define CH_STATUS                   (DMA_CH0_BASEADDR + 0x030) /* R Chan Status */
    #define CH_SWHSSRC                  (DMA_CH0_BASEADDR + 0x038) /* R/W Chan SW Handshake Source */
    #define CH_SWHSDST                  (DMA_CH0_BASEADDR + 0x040) /* R/W Chan SW Handshake Destination */
    #define CH_BLK_TFR_RESUMEREQ        (DMA_CH0_BASEADDR + 0x048) /* W Chan Block Transfer Resume Req */
    #define CH_AXI_ID                   (DMA_CH0_BASEADDR + 0x050) /* R/W Chan AXI ID */
    #define CH_AXI_QOS                  (DMA_CH0_BASEADDR + 0x058) /* R/W Chan AXI QOS */
    #define CH_SSTAT                    (DMA_CH0_BASEADDR + 0x060) /* R Chan Source Status */
    #define CH_DSTAT                    (DMA_CH0_BASEADDR + 0x068) /* R Chan Destination Status */
    #define CH_SSTATAR                  (DMA_CH0_BASEADDR + 0x070) /* R/W Chan Source Status Fetch Addr */
    #define CH_DSTATAR                  (DMA_CH0_BASEADDR + 0x078) /* R/W Chan Destination Status Fetch Addr */
    #define CH_INTSTATUS_ENA            (DMA_CH0_BASEADDR + 0x080) /* R/W Chan Interrupt Status Enable */
    #define CH_INTSTATUS                (DMA_CH0_BASEADDR + 0x088) /* R/W Chan Interrupt Status */
    #define CH_INTSIGNAL_ENA            (DMA_CH0_BASEADDR + 0x090) /* R/W Chan Interrupt Signal Enable */
    #define CH_INTCLEAR                 (DMA_CH0_BASEADDR + 0x098) /* W Chan Interrupt Clear */
#endif
  void dma_write_data_chan(uint64_t sys_mem_addr, uint64_t target_dut_addr, uint32_t size, int channel, int width)  ;
  void dma_write_data(uint64_t sys_mem_addr, uint64_t target_dut_addr, uint32_t size);
  void dma_read_data(uint64_t sys_mem_addr, uint64_t target_dut_addr, uint32_t size);
  void dma_wait ();
  void dma_config (uint8_t max_word_size);
  void dma_wait_chan (int disable_channel) ;

#endif /* _PERF_DMA_CTRL_H_ */

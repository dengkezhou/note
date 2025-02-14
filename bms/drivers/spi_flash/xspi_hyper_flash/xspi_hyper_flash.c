#include <malloc.h>
#include <common.h>
#include <xspi.h>
#include "xspi_hyper_flash.h"
#include <malloc.h>

static void hyper_flash_config(XSPI_HandleTypeDef *handler){
    //XSPI_ProgramSeqP2Config p2config_w;
    //XSPI_ReadSeqP2Config    p2config_r;
    XSPI_GlobalCommandParameters g_param;
    //XSPI_StatSeqP2Config stat_config;

    g_param.seqType = XSPI_SEQUENCE_TYPE_P2_HYPER_FLASH;
    g_param.dataPerAddress = XSPI_DATA_PER_ADDRESS_2B;
    g_param.dataSwap = false;
    g_param.crcUalChunkChk = false;
    g_param.crcUalChunkEn = false;
    g_param.crcChunkSize = XSPI_CRC_CHUNK_SIZE_16B;
    g_param.crcToogleData = false;
    g_param.crcVariant = XSPI_CRC_VARIANT_CALC_ALL_PHASES;
    g_param.crcDynamicCalcEnable = false;
    g_param.pgmPageSize = XSPI_PROGRAM_PAGE_SIZE_256B;
    g_param.rdPageSize = XSPI_READ_PAGE_SIZE_256B;
    handler->drv->setGlobalCmdParameters(handler->pD ,&g_param);
    #if 0
    /** Number of latency cycles for PROFILE 2 - HR only. Setting this bit to 0 will disable latency cycles. This value should be set to 'N-1', where 'N' is the number of latency clock cycles expected by the memory device. */
    p2config_w.progSeqLatCount = 0; //only for HR 
    /** Determines command extension variant for Legacy HyperFlash and xSPI profile 2.0 instruction */
    p2config_w.progSeqExtCmdMod = false;
    /** Target space for Legacy HyperFlash and xSPI profile 2.0 instruction (in R004 field applicable only for FULL/FULL_ASF configuration, in IOT_NODLL this feature is enabled in STIG work mode only) */
    p2config_w.progSeqTarget = XSPI_TARGET_SPACE_MEMORY;
    /** Burst type for Legacy HyperFlash and xSPI profile 2.0 instruction (in R004 field applicable only for FULL/FULL_ASF configuration, in IOT_NODLL this feature is enabled in STIG work mode only) */
    p2config_w.progSeqBurstType = XSPI_BURST_TYPE_LINEAR;
    handler->drv->setProgramSeqP2Config(handler->pD ,&p2config_w);

    /** Number of latency cycles */
    p2config_r.readSeqLatencyCnt = 15;
    /** Enabled calculating read transaction crossing page boundary */
    p2config_r.readSeqHfBoundEn = true;
     /** Determines command extension variant for Legacy HyperFlash and xSPI profile 2.0 instruction */
    p2config_r.readSeqExtCmdMod = false;
    /** Burst type for Legacy HyperFlash and xSPI profile 2.0 instruction (in R004 field applicable only for FULL/FULL_ASF configuration) */
    p2config_r.readSeqBurstType = XSPI_BURST_TYPE_LINEAR;
    /** Target space for Legacy HyperFlash and xSPI profile 2.0 instruction (in R004 field applicable only for FULL/FULL_ASF configuration) */
    p2config_r.readSeqTarget = XSPI_TARGET_SPACE_MEMORY;
    handler->drv->setReadSeqP2Config(handler->pD ,&p2config_r);

    /** Number of latency cycles (0-15) between CA and STATUS reading */
    stat_config.statSeqLatencyCnt = 12;
    /** Determines xSPI profile 2.0 command extension variant */
    stat_config.statSeqExtCmdMod = false;
    handler->drv->setStatSeqP2Config(handler->pD ,&stat_config);
    #endif
}

static void hyper_flash_reset(XSPI_HandleTypeDef *handler) {
  uint32_t base = handler->reg_base + 0x1004;
  printf("reset base 0x%x\n", base);
  printf("read register before assert reset hyper. 0x%x\n", readl(base));
  printf("assert reset hyper.\n");
  writel(0x100, base);
#ifdef CONFIG_COMPILE_RTL
  udelay(10);
#else
  udelay(1000);
#endif
  printf("release reset hyper.\n");
  writel(0x101, base);
#ifdef CONFIG_COMPILE_RTL
  udelay(10);
#else
  udelay(1000*1000);
#endif
  printf("read register after release reset hyper. 0x%x\n", readl(base));

}

uint32_t hyper_flash_read(XSPI_HandleTypeDef *handler, uint8_t *pBuffer, uint32_t addr,
                  uint32_t byte_num) {
    switch (handler->work_mode) {
    case CDNS_XSPI_MODE_DIRECT: {
        XSPI_DirectCmd directCmd;
        directCmd.direction    = XSPI_DATA_TRANS_DIR_READ;
        directCmd.sysMemPtr    = (uintptr_t)pBuffer;
        directCmd.transferSize = byte_num;
        directCmd.transferAddr = addr;

        cdns_xspi_send_direct_command(handler, &directCmd);
        break;
    }
    case CDNS_XSPI_MODE_STIG: { 
        XSPI_StigCommand stigCmd = {0};
        XSPI_StigInstruction stigInstr = {0};
        XSPI_StigDataSeqLayout dataSeqInstr = {0};
        stigInstr.stigInstrType                     = XSPI_STIG_INSTR_TYPE_PROFILE_20;
        stigInstr.profile20Instr.profile20InstrType = XSPI_P20_INSTR_READ_ARRAY;
        stigInstr.profile20Instr.tCmsEn = false;
        stigInstr.profile20Instr.extCmdModEnable = false;
        stigInstr.profile20Instr.dataNoOfBytes = 0;
        stigInstr.profile20Instr.target = XSPI_TARGET_SPACE_MEMORY;
        stigInstr.profile20Instr.burstType = XSPI_BURST_TYPE_LINEAR;
        stigInstr.profile20Instr.address = addr;
        stigInstr.profile20Instr.data[0] = 0;
        stigInstr.profile20Instr.data[1] = 0;
        stigInstr.profile20Instr.rw = XSPI_DATA_TRANS_DIR_READ;

        dataSeqInstr.crcChunkSize   = 0;
        dataSeqInstr.crcInversion   = false;
        dataSeqInstr.crcOe          = false;
        dataSeqInstr.crcUalChunkEn  = false;
        dataSeqInstr.crcUalChunkChk = false;
        dataSeqInstr.dataSwap       = false;
        dataSeqInstr.dir = XSPI_DATA_TRANS_DIR_READ;

        
        if (byte_num > 2) {
            dataSeqInstr.sysMemPtr = (uintptr_t)pBuffer;
            dataSeqInstr.rdMode    = XSPI_READ_DATA_EXTENDED_MODE;
        } else {
            dataSeqInstr.sysMemPtr = 0;
            dataSeqInstr.rdMode    = XSPI_READ_DATA_SHORT_MODE;
        }


        dataSeqInstr.dataPerAddress       = XSPI_DATA_PER_ADDRESS_2B;
        dataSeqInstr.noOfDummy            = 16;
        dataSeqInstr.hfReadBoundEnable    = true;
        dataSeqInstr.dataNoOfBytes        = byte_num;
        dataSeqInstr.instrDataPhase.edge  = XSPI_DATA_EDGE_MODE_DDR;
        dataSeqInstr.instrDataPhase.ios   = XSPI_NUMBER_OF_IOS_8;

        stigCmd.instructionChain = &stigInstr;
        stigCmd.instrChainLength = 1;
        stigCmd.dataSeqInstr = &dataSeqInstr;
        stigCmd.commCrcEnable  = false;
        stigCmd.commBankSelect = 0;
        
        cdns_xspi_send_stig_command(handler, &stigCmd);
        break;
    }
    case CDNS_XSPI_MODE_ACMD_PIO:{
        XSPI_PioCommand pioCmd;
        pioCmd.params.bankSelect         = 0U;
        pioCmd.params.cmdCount           = byte_num;
        pioCmd.params.cmdType            = XSPI_ACMD_COMMAND_TYPE_READ_SEQ;
        pioCmd.params.xSpiAddr           = addr;
        pioCmd.params.sysMemPtr          = (uintptr_t)pBuffer;
        pioCmd.params.dmaSelect          = XSPI_ACMD_DMA_SELECT_MASTER;
        pioCmd.params.disXipMb           = false;
        pioCmd.params.enXipMb            = false;
        pioCmd.params.raiseCmdCompleteCb = false;
        cdns_xspi_send_acmd_pio_command(handler, &pioCmd);
        break;
    }
    case CDNS_XSPI_MODE_ACMD_CMDA:{
        XSPI_CdmaCommand cdmaCmd;
        cdmaCmd.params.bankSelect         = 0U;
        cdmaCmd.params.cmdCount           = byte_num;
        cdmaCmd.params.cmdType            = XSPI_ACMD_COMMAND_TYPE_READ_SEQ;
        cdmaCmd.params.xSpiAddr           = addr;
        cdmaCmd.params.sysMemPtr          = (uintptr_t)pBuffer;
        cdmaCmd.params.dmaSelect          = XSPI_ACMD_DMA_SELECT_MASTER;
        cdmaCmd.params.disXipMb           = false;
        cdmaCmd.params.enXipMb            = false;
        cdmaCmd.params.raiseCmdCompleteCb = false;
        cdmaCmd.ignoreXSpiAddr            = false;
        cdmaCmd.ignoreSysMemPtr           = false;
        cdns_xspi_send_acmd_cdma_command(handler, &cdmaCmd);
        break;
    }
  }



  return true;
}

bool hyper_flash_erase(XSPI_HandleTypeDef *handler, SPI_FLASH_ERASE_TYPE type,
               uint32_t addr) {
  switch (handler->work_mode) {
    case CDNS_XSPI_MODE_ACMD_PIO:{
        XSPI_PioCommand pioCmd;
        pioCmd.params.bankSelect         = 0U;
        pioCmd.params.cmdCount           = 0;
        pioCmd.params.cmdType            = XSPI_ACMD_COMMAND_TYPE_ERASE_SEC_SEQ;
        pioCmd.params.xSpiAddr           = addr;
        pioCmd.params.sysMemPtr          = (uintptr_t)0;
        pioCmd.params.dmaSelect          = XSPI_ACMD_DMA_SELECT_MASTER;
        pioCmd.params.disXipMb           = false;
        pioCmd.params.enXipMb            = false;
        pioCmd.params.raiseCmdCompleteCb = false;
        cdns_xspi_send_acmd_pio_command(handler, &pioCmd);
        break;
    }
    default:{
        XSPI_StigCommand stigCmd = {0};
        XSPI_StigInstruction stigInstr = {0};
        printf("Erasing hyper flash...\n");
        // addr means sector addr.
        stigInstr.stigInstrType                     = XSPI_STIG_INSTR_TYPE_PROFILE_20;
        stigInstr.profile20Instr.profile20InstrType = XSPI_P20_INSTR_SECTOR_ERASE;
        stigInstr.profile20Instr.tCmsEn = false;
        stigInstr.profile20Instr.extCmdModEnable = false;
        stigInstr.profile20Instr.dataNoOfBytes = 0;
        stigInstr.profile20Instr.target = XSPI_TARGET_SPACE_MEMORY;
        stigInstr.profile20Instr.burstType = XSPI_BURST_TYPE_LINEAR;
        stigInstr.profile20Instr.address = addr;
        stigInstr.profile20Instr.data[0] = 0;
        stigInstr.profile20Instr.data[1] = 0;

        stigCmd.instructionChain = &stigInstr;
        stigCmd.instrChainLength = 1;
        stigCmd.dataSeqInstr = NULL;
        stigCmd.commCrcEnable  = false;
        stigCmd.commBankSelect = 0;

        cdns_xspi_send_stig_command(handler, &stigCmd);
        printf("Ok\n");
        printf("Erasing hyper flash...Ok\n");
        break;
    }
  
  }
  
  return true;
}

uint32_t hyper_flash_write(XSPI_HandleTypeDef *handler, uint8_t *pBuffer, uint32_t addr,
                   uint32_t byte_num) {
  switch (handler->work_mode) {
    case CDNS_XSPI_MODE_DIRECT: {
        XSPI_DirectCmd directCmd;
        directCmd.direction    = XSPI_DATA_TRANS_DIR_WRITE;
        directCmd.sysMemPtr    = (uintptr_t)pBuffer;
        directCmd.transferSize = byte_num;
        directCmd.transferAddr = addr;
        cdns_xspi_send_direct_command(handler, &directCmd);
        break;
    }
    case CDNS_XSPI_MODE_STIG: { 
        XSPI_StigCommand stigCmd = {0};
        XSPI_StigInstruction stigInstr = {0};
        XSPI_StigDataSeqLayout dataSeqInstr = {0};
        stigInstr.stigInstrType                     = XSPI_STIG_INSTR_TYPE_PROFILE_20;
        stigInstr.profile20Instr.profile20InstrType = XSPI_P20_INSTR_WRITE_ARRAY;
        stigInstr.profile20Instr.tCmsEn = false;
        stigInstr.profile20Instr.extCmdModEnable = false;
        stigInstr.profile20Instr.dataNoOfBytes = 0;
        stigInstr.profile20Instr.target = XSPI_TARGET_SPACE_MEMORY;
        stigInstr.profile20Instr.burstType = XSPI_BURST_TYPE_LINEAR;
        stigInstr.profile20Instr.address = addr;
        stigInstr.profile20Instr.data[0] = 0;
        stigInstr.profile20Instr.data[1] = 0;
        stigInstr.profile20Instr.rw = XSPI_DATA_TRANS_DIR_WRITE;

        dataSeqInstr.crcChunkSize   = 0;
        dataSeqInstr.crcInversion   = false;
        dataSeqInstr.crcOe          = false;
        dataSeqInstr.crcUalChunkEn  = false;
        dataSeqInstr.crcUalChunkChk = false;
        dataSeqInstr.dataSwap       = false;
        dataSeqInstr.dir       = XSPI_DATA_TRANS_DIR_WRITE;
        
        if(byte_num == 1){
            stigInstr.profile20Instr.dataNoOfBytes = 1;
            stigInstr.profile20Instr.data[0] = *pBuffer;
            stigInstr.profile20Instr.data[1] = 0;
            dataSeqInstr.sysMemPtr = 0;
        }else if (byte_num == 2){
            stigInstr.profile20Instr.dataNoOfBytes = 2;
            stigInstr.profile20Instr.data[0] = *pBuffer;
            stigInstr.profile20Instr.data[1] = *(pBuffer+1);
            dataSeqInstr.sysMemPtr = 0;
        }else{
            dataSeqInstr.sysMemPtr = (uintptr_t)pBuffer;
        }


        dataSeqInstr.dataPerAddress       = XSPI_DATA_PER_ADDRESS_2B;
        dataSeqInstr.noOfDummy            = 0;
        dataSeqInstr.hfReadBoundEnable    = true;
        dataSeqInstr.dataNoOfBytes        = byte_num;
        dataSeqInstr.instrDataPhase.edge  = XSPI_DATA_EDGE_MODE_DDR;
        dataSeqInstr.instrDataPhase.ios   = XSPI_NUMBER_OF_IOS_8;

        stigCmd.instructionChain = &stigInstr;
        stigCmd.instrChainLength = 1;
        stigCmd.dataSeqInstr = &dataSeqInstr;
        stigCmd.commCrcEnable  = false;
        stigCmd.commBankSelect = 0;
        
        cdns_xspi_send_stig_command(handler, &stigCmd);
        printf("Ok\n");
        break;
    }
    case CDNS_XSPI_MODE_ACMD_PIO:{
        XSPI_PioCommand pioCmd;
        pioCmd.params.bankSelect         = 0U;
        pioCmd.params.cmdCount           = byte_num;
        pioCmd.params.cmdType            = XSPI_ACMD_COMMAND_TYPE_PROGRAM_SEQ;
        pioCmd.params.xSpiAddr           = addr;
        pioCmd.params.sysMemPtr          = (uintptr_t)pBuffer;
        pioCmd.params.dmaSelect          = XSPI_ACMD_DMA_SELECT_MASTER;
        pioCmd.params.disXipMb           = false;
        pioCmd.params.enXipMb            = false;
        pioCmd.params.raiseCmdCompleteCb = false;
        cdns_xspi_send_acmd_pio_command(handler, &pioCmd);
        break;
    }
    case CDNS_XSPI_MODE_ACMD_CMDA:{
        XSPI_CdmaCommand cdmaCmd;
        cdmaCmd.params.bankSelect         = 0U;
        cdmaCmd.params.cmdCount           = byte_num;
        cdmaCmd.params.cmdType            = XSPI_ACMD_COMMAND_TYPE_PROGRAM_SEQ;
        cdmaCmd.params.xSpiAddr           = addr;
        cdmaCmd.params.sysMemPtr          = (uintptr_t)pBuffer;
        cdmaCmd.params.dmaSelect          = XSPI_ACMD_DMA_SELECT_MASTER;
        cdmaCmd.params.disXipMb           = false;
        cdmaCmd.params.enXipMb            = false;
        cdmaCmd.params.raiseCmdCompleteCb = false;
        cdmaCmd.ignoreXSpiAddr            = false;
        cdmaCmd.ignoreSysMemPtr           = false;
        cdns_xspi_send_acmd_cdma_command(handler, &cdmaCmd);
        break;
    }
  }
  return 0;
}

bool hyper_flash_write_protect(XSPI_HandleTypeDef *handler, bool enable) {
    return true;
}

#if 0
static int simple_test(XSPI_HandleTypeDef *handler){
  uint8_t tx[32] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32};
  uint8_t rx[32] = { 0 };
  
  handler->work_mode = CDNS_XSPI_MODE_STIG;
  #if 1
  printf("erase start...\n");
  hyper_flash_erase(handler, SPI_FLASH_ERASE_SECTOR, 0);
  printf("erase done.\n");
  printf("write hf will be started after 5 seconds.\n");
  udelay(1000*5000);
  
  hyper_flash_write(handler, tx, 512, 32);
  printf("write done.\n");
  printf("read hf will be started after 5 seconds.\n");
  udelay(1000*5000);
  #endif

  hyper_flash_read(handler, rx, 512, 32);
  printf("read done.\n");
  printf("tx data:\n");
  for(int i = 0; i < 32; i++){
    printf("0x%x ",tx[i]);
  }
  printf("\n");

  printf("rx data:\n");
  for(int i = 0; i < 32; i++){
    printf("0x%x ",rx[i]);
  }
  printf("\n");
  while(1);
  return 0;
}
#endif
XSPI_HandleTypeDef *hyper_flash_init(XSPI_InitTypeDef *init) {
  XSPI_HandleTypeDef *handler;

  handler = itcs_xspi_init(init);
  if (handler == NULL) {
    printf("XSPI init failed, handler is NULL\n");
    return handler;
  }
  handler->work_mode = CDNS_XSPI_MODE_STIG;
  
  hyper_flash_reset(handler);
  hyper_flash_config(handler);
  

  //simple_test(handler);
  
  return handler;
}


static uint32_t hyper_flash_get_alignment(XSPI_HandleTypeDef *handler) {
    return 0;
}

struct xspi_flash_operations f_ops_xspi_hyper_flash = {
    .init          = hyper_flash_init,
    .read          = hyper_flash_read,
    .write         = hyper_flash_write,
    .erase         = hyper_flash_erase,
    .get_alignment = hyper_flash_get_alignment,
    .write_protect = hyper_flash_write_protect,
    .reset         = hyper_flash_reset};
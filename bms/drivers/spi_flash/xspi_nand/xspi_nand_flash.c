#include <malloc.h>
#include <common.h>
#include <xspi.h>
#include "xspi_nand_flash.h"
#include <malloc.h>

#define SPI_FLASH_PAGE_SIZE          (4 * 1024)
#define SPI_FLASH_PAGE_NUM_PER_BLOCK (64)
#define SPI_FLASH_SECTOR_SIZE        (0)
#define SPI_FLASH_BLOCK_SIZE                                                   \
  (SPI_FLASH_PAGE_NUM_PER_BLOCK * SPI_FLASH_PAGE_SIZE)
#define SPI_FLASH_BLOCK_NUM (1024)
#define SPI_FLASH_FULL_SIZE (SPI_FLASH_BLOCK_NUM * SPI_FLASH_BLOCK_SIZE)

#define SPI_FLASH_WRITE_ENABLE         0x06
#define SPI_FLASH_WRITE_DISABLE        0x04
#define SPI_FLASH_GET_FEATURE          0x0f
#define SPI_FLASH_SET_FEATURE          0x1f
#define SPI_FLASH_READ_ID              0x9f

#define SPI_FLASH_PAGE_READ            0x13
#define SPI_FLASH_READ_CACHE           0x03
#define SPI_FLASH_READ_CACHE_X2        0x3b
#define SPI_FLASH_READ_CACHE_X4        0x6b
#define SPI_FLASH_READ_CACHE_X8        0x8b

#define SPI_FLASH_PROGRAM_LOAD         0x02
#define SPI_FLASH_PROGRAM_LOAD4        0x32
#define SPI_FLASH_PROGRAM_LOAD8        0x82

#define SPI_FLASH_PROGRAM_EXEC         0x10
#define SPI_FLASH_BLOCK_ERASE          0xd8
#define SPI_FLASH_RESET                0xff
#define SPI_FLASH_ENABLE_POR           0x66
#define SPI_FLASH_POR                  0x99
#define SPI_FLASH_JedecDeviceID        0x9F

/*
struct nand_row_addr_st description:
    For a nand flash device, row address include 2 parts
    bit[0] to bit[5] always presents page index number in a block unit. which range is [0-64),
    bit[6] to bit[23] are not valid in every bit.,
    When a device has 1024 blocks, only bit[6] to bit[15] are valid , 2^10 represents 1024.
    When a device has 2048 blocks, only bit[6] to bit[16] are valid , 2^11 represents 2048.
*/
struct nand_row_addr_st{
    uint32_t page_idx:6 ;
    uint32_t block_idx:18 ;
    uint32_t resv:8;
};

/*
    Every nand flash has 24-bit address which called row address and 16-bit address which called column address.
    For row_addr valid bit info, refer to struct nand_row_addr_st description above.
    For column_addr only bit0-bit11 are valid
*/
struct nand_addr_st{
    union{
        uint32_t row_addr_uint32;
        struct nand_row_addr_st row_addr_st;
    }row_addr;
    uint16_t column_addr;
};

struct nand_mem_st{
    uint32_t mem_addr; //Byte index of whole nand flash, up to 32GB.
    struct nand_addr_st nand_addr;
};


static XSPI_StigCommand stigCmd;
static XSPI_StigInstruction stigInstr;
static XSPI_StigDataSeqLayout dataSeqInstr;
static bool nand_write_protect(XSPI_HandleTypeDef *handler, bool enable);
static XSPI_StigCommand *construct_stig_cmd(bool ddr, int lines, bool wr, uint8_t * buf, uint32_t len, 
                                            XSPI_Profile10AutonomicInstrType instr_type, uint8_t opcode,
                                            uint8_t dummy_bits, uint64_t addr, uint32_t addr_len)
{
  memset(&stigCmd, 0, sizeof(XSPI_StigCommand));
  memset(&stigInstr, 0, sizeof(XSPI_StigInstruction));
  memset(&dataSeqInstr, 0, sizeof(XSPI_StigDataSeqLayout));
  stigInstr.stigInstrType = XSPI_STIG_INSTR_TYPE_PROFILE_10;
  stigInstr.profile10Instr.profile10InstrType = instr_type;
  stigInstr.profile10Instr.xipEnable = false;

  stigInstr.profile10Instr.instrOpcodePhase.value = opcode;
  stigInstr.profile10Instr.instrOpcodeExt.enable = false;
  stigInstr.profile10Instr.instrOpcodeExt.value = 0;
  stigInstr.profile10Instr.instrAddrPhase.count = addr_len;

  stigInstr.profile10Instr.dataNoOfBytes = 0;
  stigInstr.profile10Instr.crcVariant = XSPI_CRC_VARIANT_CALC_ADDR_PHASE;
  stigInstr.profile10Instr.addrShift = false;
  stigInstr.profile10Instr.address = addr;
  stigInstr.profile10Instr.data[0] = 0;
  stigInstr.profile10Instr.data[1] = 0;

  dataSeqInstr.crcChunkSize = 0;
  dataSeqInstr.crcInversion = false;
  dataSeqInstr.crcOe = false;
  dataSeqInstr.crcUalChunkEn = false;
  dataSeqInstr.crcUalChunkChk = false;
  dataSeqInstr.dataSwap = false;
  if(wr){
    dataSeqInstr.dir = XSPI_DATA_TRANS_DIR_WRITE;
    dataSeqInstr.sysMemPtr = (uintptr_t)buf;
  }else{
    dataSeqInstr.dir = XSPI_DATA_TRANS_DIR_READ;
    if(len >2){
        dataSeqInstr.sysMemPtr = (uintptr_t)buf;
        dataSeqInstr.rdMode = XSPI_READ_DATA_EXTENDED_MODE;
    }else{
        dataSeqInstr.sysMemPtr = 0;
        dataSeqInstr.rdMode = XSPI_READ_DATA_SHORT_MODE;
    }
  }
    
  dataSeqInstr.dataPerAddress = XSPI_DATA_PER_ADDRESS_1B;
  dataSeqInstr.noOfDummy = dummy_bits;
  dataSeqInstr.hfReadBoundEnable = false;
  dataSeqInstr.dataNoOfBytes = len;

  if(ddr == false){
    stigInstr.profile10Instr.instrOpcodePhase.edge = XSPI_CMD_EDGE_MODE_SDR;
    stigInstr.profile10Instr.instrAddrPhase.edge = XSPI_ADDR_EDGE_MODE_SDR;
    dataSeqInstr.instrDataPhase.edge = XSPI_DATA_EDGE_MODE_SDR;
  }else{
    stigInstr.profile10Instr.instrOpcodePhase.edge = XSPI_CMD_EDGE_MODE_DDR;
    stigInstr.profile10Instr.instrAddrPhase.edge = XSPI_ADDR_EDGE_MODE_DDR;
    dataSeqInstr.instrDataPhase.edge = XSPI_DATA_EDGE_MODE_DDR;
  }
  stigInstr.profile10Instr.instrOpcodePhase.ios = XSPI_NUMBER_OF_IOS_1;
  stigInstr.profile10Instr.instrAddrPhase.ios = XSPI_NUMBER_OF_IOS_1;
  switch(lines){
    case 1:
        dataSeqInstr.instrDataPhase.ios = XSPI_NUMBER_OF_IOS_1;
    break;
    case 2:
        dataSeqInstr.instrDataPhase.ios = XSPI_NUMBER_OF_IOS_2;
    break;
    case 4:
        dataSeqInstr.instrDataPhase.ios = XSPI_NUMBER_OF_IOS_4;
    break;
    case 8:
        dataSeqInstr.instrDataPhase.ios = XSPI_NUMBER_OF_IOS_8;
    break;
    default:
        dataSeqInstr.instrDataPhase.ios = XSPI_NUMBER_OF_IOS_1;
        printf("[XSPI] Invalid line number, using 1 line mode\n");
    break;
    
  }


  stigCmd.instructionChain = &stigInstr;
  stigCmd.instrChainLength = 1;
  if(len)
    stigCmd.dataSeqInstr = &dataSeqInstr;
  else
    stigCmd.dataSeqInstr = NULL;
  stigCmd.commCrcEnable = false;
  stigCmd.commBankSelect = 0;
  return &stigCmd;
}

static void nand_wait_busy(XSPI_HandleTypeDef *handler) {
  XSPI_StigCommand* cmd;
  uint8_t sr = 0;
  uint64_t addr = 0xC0;

  do {
    cmd = construct_stig_cmd(false, 1, false, NULL, 1, XSPI_P10_INSTR_SNA_GET_FEATURES, SPI_FLASH_GET_FEATURE, 0, addr, 1);
    cdns_xspi_send_stig_command(handler, cmd);
    handler->drv->getStigStatus(handler->pD, cmd);
    sr = cmd->statusInfo.dataFromDevice[0];
    DEBUG_XSPI_LOG("[XSPI] wait busy register 0xC0 = 0x%x\n",sr);
  } while (sr & 0x01);
}

static void nand_get_features(XSPI_HandleTypeDef *handler) {
  XSPI_StigCommand* cmd;
  uint64_t addr = 0xA0;
  // Sending Write Enable.
  cmd = construct_stig_cmd(false, 1, false, NULL, 0, XSPI_P10_INSTR_WRITE_ENABLE_LATCH, SPI_FLASH_WRITE_ENABLE, 0, 0, 0);
  cdns_xspi_send_stig_command(handler, cmd);
  
  cmd = construct_stig_cmd(false, 1, false, NULL, 1, XSPI_P10_INSTR_SNA_GET_FEATURES, SPI_FLASH_GET_FEATURE, 0, addr, 1);
  cdns_xspi_send_stig_command(handler, cmd);
  handler->drv->getStigStatus(handler->pD, cmd);
  DEBUG_XSPI_LOG("[XSPI] register 0x%x = 0x%x\n",addr, cmd->statusInfo.dataFromDevice[0]);

  addr = 0xB0;
  cmd = construct_stig_cmd(false, 1, false, NULL, 1, XSPI_P10_INSTR_SNA_GET_FEATURES, SPI_FLASH_GET_FEATURE, 0, addr, 1);
  cdns_xspi_send_stig_command(handler, cmd);
  handler->drv->getStigStatus(handler->pD, cmd);
  DEBUG_XSPI_LOG("[XSPI] register 0x%x = 0x%x\n",addr, cmd->statusInfo.dataFromDevice[0]);

  addr = 0xC0;
  cmd = construct_stig_cmd(false, 1, false, NULL, 1, XSPI_P10_INSTR_SNA_GET_FEATURES, SPI_FLASH_GET_FEATURE, 0, addr, 1);
  cdns_xspi_send_stig_command(handler, cmd);
  handler->drv->getStigStatus(handler->pD, cmd);
  DEBUG_XSPI_LOG("[XSPI] register 0x%x = 0x%x\n",addr, cmd->statusInfo.dataFromDevice[0]);

  addr = 0xD0;
  cmd = construct_stig_cmd(false, 1, false, NULL, 1, XSPI_P10_INSTR_SNA_GET_FEATURES, SPI_FLASH_GET_FEATURE, 0, addr, 1);
  cdns_xspi_send_stig_command(handler, cmd);
  handler->drv->getStigStatus(handler->pD, cmd);
  DEBUG_XSPI_LOG("[XSPI] register 0x%x = 0x%x\n",addr, cmd->statusInfo.dataFromDevice[0]);

  addr = 0xF0;
  cmd = construct_stig_cmd(false, 1, false, NULL, 1, XSPI_P10_INSTR_SNA_GET_FEATURES, SPI_FLASH_GET_FEATURE, 0, addr, 1);
  cdns_xspi_send_stig_command(handler, cmd);
  handler->drv->getStigStatus(handler->pD, cmd);
  DEBUG_XSPI_LOG("[XSPI] register 0x%x = 0x%x\n",addr, cmd->statusInfo.dataFromDevice[0]);
}

static void nand_enable_ecc(XSPI_HandleTypeDef *handler, bool enable) {
  XSPI_StigCommand* cmd;
  uint8_t sr = 0;
  uint64_t addr = 0xB0;
  cmd = construct_stig_cmd(false, 1, false, NULL, 0, XSPI_P10_INSTR_WRITE_ENABLE_LATCH, SPI_FLASH_WRITE_ENABLE, 0, 0, 0);
  cdns_xspi_send_stig_command(handler, cmd);

  cmd = construct_stig_cmd(false, 1, false, NULL, 1, XSPI_P10_INSTR_SNA_GET_FEATURES, SPI_FLASH_GET_FEATURE, 0, addr, 1);
  cdns_xspi_send_stig_command(handler, cmd);
  sr = (uint8_t)(readl(handler->reg_base + 0x44) >> 16);

  if (enable)
    sr |= 0x10;
  else
    sr &= 0xef;

  
  cmd = construct_stig_cmd(false, 1, true, NULL, 0, XSPI_P10_INSTR_SNA_SET_FEATURES, SPI_FLASH_SET_FEATURE, 0, addr, 1);
  cmd->instructionChain->profile10Instr.dataNoOfBytes = 1;
  cmd->instructionChain->profile10Instr.data[0] = sr;
  cdns_xspi_send_stig_command(handler, cmd);
  #ifndef CONFIG_COMPILE_RTL
  udelay(10);
  #endif
}

static void nand_enable_quad_op(XSPI_HandleTypeDef *handler, bool enable) {
  XSPI_StigCommand* cmd;
  uint8_t sr = 0;
  uint64_t addr = 0xB0;
  cmd = construct_stig_cmd(false, 1, false, NULL, 0, XSPI_P10_INSTR_WRITE_ENABLE_LATCH, SPI_FLASH_WRITE_ENABLE, 0, 0, 0);
  cdns_xspi_send_stig_command(handler, cmd);

  cmd = construct_stig_cmd(false, 1, false, NULL, 1, XSPI_P10_INSTR_SNA_GET_FEATURES, SPI_FLASH_GET_FEATURE, 0, addr, 1);
  cdns_xspi_send_stig_command(handler, cmd);
  sr = (uint8_t)(readl(handler->reg_base + 0x44) >> 16);

  if (enable)
    sr |= 0x01;
  else
    sr &= 0xfe;
  cmd = construct_stig_cmd(false, 1, true, NULL, 0, XSPI_P10_INSTR_SNA_SET_FEATURES, SPI_FLASH_SET_FEATURE, 0, addr, 1);
  cmd->instructionChain->profile10Instr.dataNoOfBytes = 1;
  cmd->instructionChain->profile10Instr.data[0] = sr;
  cdns_xspi_send_stig_command(handler, cmd);
  #ifndef CONFIG_COMPILE_RTL
  udelay(10);
  #endif
}

static int nand_get_id(XSPI_HandleTypeDef *handler) {
  XSPI_StigCommand* cmd;
  uint8_t buf[8];
  cmd = construct_stig_cmd(false, 1, false, buf, BYTES_PER_XSPI_DMA_OP, XSPI_P10_INSTR_READ_JEDEC_ID, SPI_FLASH_JedecDeviceID, 0, 0, 0);
  DEBUG_XSPI_LOG("[XSPI] get spi flash id...");
  cdns_xspi_send_stig_command(handler, cmd);
  nand_wait_busy(handler);
  DEBUG_XSPI_LOG("ok\n");
  DEBUG_XSPI_LOG("[XSPI] Manufacturer ID = 0x%x\n", buf[1]);
  DEBUG_XSPI_LOG("[XSPI] Device ID = 0x%x\n", buf[2]);
  return 0;
}

static void nand_reset(XSPI_HandleTypeDef *handler) {
  //0x66 0x99
  XSPI_StigCommand* cmd;
  DEBUG_XSPI_LOG("[XSPI] reset spi flash...\n");
  DEBUG_XSPI_LOG("[XSPI] cmd 0xff reset...");
  cmd = construct_stig_cmd(false, 1, false, NULL, 0, XSPI_P10_INSTR_SOFT_RESET, SPI_FLASH_RESET, 0, 0, 0);
  cdns_xspi_send_stig_command(handler, cmd);
  nand_wait_busy(handler);
  DEBUG_XSPI_LOG("ok\n");

  printf("[XSPI] cmd 0x66 0x99 reset...");
  cmd = construct_stig_cmd(false, 1, false, NULL, 0, XSPI_P10_INSTR_RESET_ENABLE, SPI_FLASH_ENABLE_POR, 0, 0, 0);
  cdns_xspi_send_stig_command(handler, cmd);
  
  cmd = construct_stig_cmd(false, 1, false, NULL, 0, XSPI_P10_INSTR_SOFT_RESET, SPI_FLASH_POR, 0, 0, 0);
  cdns_xspi_send_stig_command(handler, cmd);
  DEBUG_XSPI_LOG("ok\n");
  nand_wait_busy(handler);
}
#if 0
static void nand_program_config(XSPI_HandleTypeDef *handler){
    XSPI_SpiNandGlobCmdParams nand_param;
    XSPI_GlobalCommandParameters g_param;
    XSPI_WelSeqConfig wel_config;
    XSPI_ProgramSeqP1Config p1config;
    XSPI_StatSeqP1Config stat_config;
    DEBUG_XSPI_LOG("[XSPI] set profile1.0 nand param\n");

    //0x394
    nand_param.extPageSize = 64;
    nand_param.pageCaSize = XSPI_SPI_NAND_CA_SIZE_12;
    nand_param.pagesPerBlock = 64;
    nand_param.planeCnt = XSPI_SPI_NAND_1_PLANE;
    handler->drv->setSpiNandCmdParameters(handler->pD ,&nand_param);

    //0x390
    g_param.seqType = XSPI_SEQUENCE_TYPE_P1_SPI_NAND;
    g_param.dataPerAddress = XSPI_DATA_PER_ADDRESS_1B;
    g_param.dataSwap = false;
    g_param.crcUalChunkChk = false;
    g_param.crcUalChunkEn = false;
    g_param.crcChunkSize = XSPI_CRC_CHUNK_SIZE_16B;
    g_param.crcToogleData = false;
    g_param.crcVariant = XSPI_CRC_VARIANT_CALC_ALL_PHASES;
    g_param.crcDynamicCalcEnable = false;
    g_param.pgmPageSize = XSPI_PROGRAM_PAGE_SIZE_2048B;
    g_param.rdPageSize = XSPI_READ_PAGE_SIZE_2048B;
    handler->drv->setGlobalCmdParameters(handler->pD ,&g_param);

    //0x440
    wel_config.welSeqCmd.edge = XSPI_CMD_EDGE_MODE_SDR;
    wel_config.welSeqCmd.ios = XSPI_NUMBER_OF_IOS_1;
    wel_config.welSeqCmd.value = SPI_FLASH_WRITE_ENABLE;
    handler->drv->setWelSeqConfig(handler->pD ,&wel_config);

    //0x420 0x424
    p1config.progSeqAddr.edge = XSPI_ADDR_EDGE_MODE_SDR;
    p1config.progSeqAddr.ios = XSPI_NUMBER_OF_IOS_1;
    p1config.progSeqAddr.count = 2;
    p1config.progSeqCmd.edge = XSPI_CMD_EDGE_MODE_SDR;
    p1config.progSeqCmd.ios =XSPI_NUMBER_OF_IOS_1;
    p1config.progSeqCmdExt.enable = false;
    p1config.progSeqData.edge = XSPI_DATA_EDGE_MODE_SDR;
    switch(handler->init.line_num){
        case 4:
        case 8:
            DEBUG_XSPI_LOG("write x4\n");
            p1config.progSeqCmd.value = SPI_FLASH_PROGRAM_LOAD4;
            p1config.progSeqData.ios = XSPI_NUMBER_OF_IOS_4;
        break;

        
        case 2:
        case 1:
        default:
            //DEBUG_XSPI_LOG("write x1\n");
            p1config.progSeqCmd.value = SPI_FLASH_PROGRAM_LOAD;
            p1config.progSeqData.ios = XSPI_NUMBER_OF_IOS_1;
        break;

    }
    handler->drv->setProgramSeqP1Config(handler->pD ,&p1config);

    stat_config.statSeqData.edge = XSPI_DATA_EDGE_MODE_SDR;
    stat_config.statSeqData.ios = XSPI_NUMBER_OF_IOS_1;
    stat_config.statSeqAddrEdge = XSPI_ADDR_EDGE_MODE_SDR;
    stat_config.statSeqAddrIos = XSPI_NUMBER_OF_IOS_1;
    stat_config.statSeqAddrCnt = XSPI_STAT_SEQ_ADDR_COUNT_1_ADDR_BYTE;
    stat_config.statSeqCmdExtEn = true;
    stat_config.statSeqCmdEdge = XSPI_CMD_EDGE_MODE_SDR;
    stat_config.statSeqCmdIos = XSPI_NUMBER_OF_IOS_1;
    stat_config.statSeqErsFailAddrEn = false;
    stat_config.statSeqErsFailDummyCnt = 0;
    stat_config.statSeqProgFailAddrEn = false;
    stat_config.statSeqProgFailDummyCnt = 0;
    stat_config.statSeqDevRdyAddrEn = false;
    stat_config.statSeqDevRdyDummyCnt = 0;
    stat_config.statSeqProgFailCmdVal = 0x0F;
    stat_config.statSeqErsFailCmdVal = 0x0F;
    stat_config.statSeqDevRdyCmdVal = 0x0F;
    stat_config.statSeqProgFailCmdExtVal = 0xC0;
    stat_config.statSeqErsFailCmdExtVal = 0xC0;
    stat_config.statSeqDevRdyCmdExtVal = 0xC0;
    handler->drv->setStatSeqP1Config(handler->pD ,&stat_config);
}

static void nand_read_config(XSPI_HandleTypeDef *handler){
    XSPI_SpiNandGlobCmdParams nand_param;
    XSPI_GlobalCommandParameters g_param;
    XSPI_ReadSeqP1Config p1config;
    XSPI_StatSeqP1Config stat_config;
    DEBUG_XSPI_LOG("[XSPI] set profile1.0 nand param\n");
    if(handler->work_mode == CDNS_XSPI_MODE_DIRECT)
        nand_param.extPageSize = 0;
    else
        nand_param.extPageSize = 64;
    nand_param.pageCaSize = XSPI_SPI_NAND_CA_SIZE_12;
    nand_param.pagesPerBlock = 64;
    nand_param.planeCnt = XSPI_SPI_NAND_1_PLANE;
    handler->drv->setSpiNandCmdParameters(handler->pD ,&nand_param);
    
    g_param.seqType = XSPI_SEQUENCE_TYPE_P1_SPI_NAND;
    g_param.dataPerAddress = XSPI_DATA_PER_ADDRESS_1B;
    g_param.dataSwap = false;
    g_param.crcUalChunkChk = false;
    g_param.crcUalChunkEn = false;
    g_param.crcChunkSize = XSPI_CRC_CHUNK_SIZE_16B;
    g_param.crcToogleData = false;
    g_param.crcVariant = XSPI_CRC_VARIANT_CALC_ALL_PHASES;
    g_param.crcDynamicCalcEnable = false;
    g_param.pgmPageSize = XSPI_PROGRAM_PAGE_SIZE_2048B;
    g_param.rdPageSize = XSPI_READ_PAGE_SIZE_2048B;
    handler->drv->setGlobalCmdParameters(handler->pD ,&g_param);
    
    p1config.readSeqAddr.edge = XSPI_ADDR_EDGE_MODE_SDR;
    p1config.readSeqAddr.ios = XSPI_NUMBER_OF_IOS_1;
    p1config.readSeqAddr.count = 2;
    p1config.readSeqCmd.edge = XSPI_CMD_EDGE_MODE_SDR;
    p1config.readSeqCmd.ios = XSPI_NUMBER_OF_IOS_1;
    p1config.readSeqCmdExt.enable = false;
    p1config.readSeqCmdExt.value = 0;
    p1config.readSeqData.edge = XSPI_DATA_EDGE_MODE_SDR;
    p1config.readSeqMbDummyCnt = 0;
    p1config.readSeqMbEn = false;
    p1config.cacheRandomReadEn = false;
    switch(handler->init.line_num){
        case 2:
            DEBUG_XSPI_LOG("read x2\n");
            p1config.readSeqCmd.value = SPI_FLASH_READ_CACHE_X2;
            p1config.readSeqData.ios = XSPI_NUMBER_OF_IOS_2;
            p1config.readSeqDummyCnt = 8;
        break;

        case 4:
        case 8:
            DEBUG_XSPI_LOG("read x4\n");
            p1config.readSeqCmd.value = SPI_FLASH_READ_CACHE_X4;
            p1config.readSeqData.ios = XSPI_NUMBER_OF_IOS_4;
            p1config.readSeqDummyCnt = 8;
        break;

        case 1:
        default:
            DEBUG_XSPI_LOG("read x1\n");
            p1config.readSeqCmd.value = SPI_FLASH_READ_CACHE;
            p1config.readSeqData.ios = XSPI_NUMBER_OF_IOS_1;
            p1config.readSeqDummyCnt = 8;
        break;

    }
    handler->drv->setReadSeqP1Config(handler->pD ,&p1config);

    stat_config.statSeqData.edge = XSPI_ADDR_EDGE_MODE_SDR;
    stat_config.statSeqData.ios = XSPI_NUMBER_OF_IOS_1;
    stat_config.statSeqAddrEdge = XSPI_ADDR_EDGE_MODE_SDR;
    stat_config.statSeqAddrIos = XSPI_NUMBER_OF_IOS_1;
    stat_config.statSeqAddrCnt = XSPI_STAT_SEQ_ADDR_COUNT_1_ADDR_BYTE;
    stat_config.statSeqCmdExtEn = true;
    stat_config.statSeqCmdEdge = XSPI_CMD_EDGE_MODE_SDR;
    stat_config.statSeqCmdIos = XSPI_NUMBER_OF_IOS_1;
    stat_config.statSeqErsFailAddrEn = false;
    stat_config.statSeqErsFailDummyCnt = 0;
    stat_config.statSeqProgFailAddrEn = false;
    stat_config.statSeqProgFailDummyCnt = 0;
    stat_config.statSeqDevRdyAddrEn = false;
    stat_config.statSeqDevRdyDummyCnt = 0;
    stat_config.statSeqProgFailCmdVal = 0x0F;
    stat_config.statSeqErsFailCmdVal = 0x0F;
    stat_config.statSeqDevRdyCmdVal = 0x0F;
    stat_config.statSeqProgFailCmdExtVal = 0xC0;
    stat_config.statSeqErsFailCmdExtVal = 0xC0;
    stat_config.statSeqDevRdyCmdExtVal = 0xC0;
    handler->drv->setStatSeqP1Config(handler->pD ,&stat_config);
}
#endif
static void nand_basic_config(XSPI_HandleTypeDef *handler){
    XSPI_SpiNandGlobCmdParams nand_param = {0};
    XSPI_GlobalCommandParameters g_param = {0};
    XSPI_StatSeqP1Config stat_config = {0};
    DEBUG_XSPI_LOG("[XSPI] set profile1.0 nand basic param\n");

    //0x394
    nand_param.extPageSize = 64;
    nand_param.pageCaSize = XSPI_SPI_NAND_CA_SIZE_12;
    nand_param.pagesPerBlock = 64;
    nand_param.planeCnt = XSPI_SPI_NAND_1_PLANE;
    handler->drv->setSpiNandCmdParameters(handler->pD ,&nand_param);

    //0x390
    g_param.seqType = XSPI_SEQUENCE_TYPE_P1_SPI_NAND;
    g_param.pgmPageSize = XSPI_PROGRAM_PAGE_SIZE_2048B;
    g_param.rdPageSize = XSPI_READ_PAGE_SIZE_2048B;
    handler->drv->setGlobalCmdParameters(handler->pD ,&g_param);

    stat_config.statSeqData.edge = XSPI_DATA_EDGE_MODE_SDR;
    stat_config.statSeqData.ios = XSPI_NUMBER_OF_IOS_1;
    stat_config.statSeqAddrEdge = XSPI_ADDR_EDGE_MODE_SDR;
    stat_config.statSeqAddrIos = XSPI_NUMBER_OF_IOS_1;
    stat_config.statSeqAddrCnt = XSPI_STAT_SEQ_ADDR_COUNT_1_ADDR_BYTE;
    stat_config.statSeqCmdExtEn = true;
    stat_config.statSeqCmdEdge = XSPI_CMD_EDGE_MODE_SDR;
    stat_config.statSeqCmdIos = XSPI_NUMBER_OF_IOS_1;
    stat_config.statSeqErsFailAddrEn = false;
    stat_config.statSeqErsFailDummyCnt = 0;
    stat_config.statSeqProgFailAddrEn = false;
    stat_config.statSeqProgFailDummyCnt = 0;
    stat_config.statSeqDevRdyAddrEn = false;
    stat_config.statSeqDevRdyDummyCnt = 0;
    stat_config.statSeqProgFailCmdVal = 0x0F;
    stat_config.statSeqErsFailCmdVal = 0x0F;
    stat_config.statSeqDevRdyCmdVal = 0x0F;
    stat_config.statSeqProgFailCmdExtVal = 0xC0;
    stat_config.statSeqErsFailCmdExtVal = 0xC0;
    stat_config.statSeqDevRdyCmdExtVal = 0xC0;
    handler->drv->setStatSeqP1Config(handler->pD ,&stat_config);
}

static void nand_program_config(XSPI_HandleTypeDef *handler){
    XSPI_WelSeqConfig wel_config = {0};
    XSPI_ProgramSeqP1Config p1config = {0};

    wel_config.welSeqCmd.edge = XSPI_CMD_EDGE_MODE_SDR;
    wel_config.welSeqCmd.ios = XSPI_NUMBER_OF_IOS_1;
    wel_config.welSeqCmd.value = SPI_FLASH_WRITE_ENABLE;
    handler->drv->setWelSeqConfig(handler->pD ,&wel_config);

    p1config.progSeqAddr.edge = XSPI_ADDR_EDGE_MODE_SDR;
    p1config.progSeqAddr.ios = XSPI_NUMBER_OF_IOS_1;
    p1config.progSeqAddr.count = 2;
    p1config.progSeqCmd.edge = XSPI_CMD_EDGE_MODE_SDR;
    p1config.progSeqCmd.ios =XSPI_NUMBER_OF_IOS_1;
    p1config.progSeqCmdExt.enable = false;
    p1config.progSeqData.edge = XSPI_DATA_EDGE_MODE_SDR;
    switch(handler->init.line_num){
        case 4:
            DEBUG_XSPI_LOG("write x4\n");
            p1config.progSeqCmd.value = SPI_FLASH_PROGRAM_LOAD4;
            p1config.progSeqData.ios = XSPI_NUMBER_OF_IOS_4;
            break;
        case 8:
            DEBUG_XSPI_LOG("write x8\n");
            p1config.progSeqCmd.value = SPI_FLASH_PROGRAM_LOAD8;
            p1config.progSeqData.ios = XSPI_NUMBER_OF_IOS_8;
        break;

        
        case 2:
        case 1:
        default:
            //DEBUG_XSPI_LOG("write x1\n");
            p1config.progSeqCmd.value = SPI_FLASH_PROGRAM_LOAD;
            p1config.progSeqData.ios = XSPI_NUMBER_OF_IOS_1;
        break;

    }
    handler->drv->setProgramSeqP1Config(handler->pD ,&p1config);
}

static void nand_read_config(XSPI_HandleTypeDef *handler){
  XSPI_ReadSeqP1Config p1config = {0};
  p1config.readSeqAddr.edge = XSPI_ADDR_EDGE_MODE_SDR;
  p1config.readSeqAddr.ios = XSPI_NUMBER_OF_IOS_1;
  p1config.readSeqAddr.count = 2;
  p1config.readSeqCmd.edge = XSPI_CMD_EDGE_MODE_SDR;
  p1config.readSeqCmd.ios = XSPI_NUMBER_OF_IOS_1;
  p1config.readSeqCmdExt.enable = false;
  p1config.readSeqCmdExt.value = 0;
  p1config.readSeqData.edge = XSPI_DATA_EDGE_MODE_SDR;
  p1config.readSeqMbDummyCnt = 0;
  p1config.readSeqMbEn = false;
  p1config.cacheRandomReadEn = false;
  switch(handler->init.line_num){
      case 2:
          DEBUG_XSPI_LOG("read x2\n");
          p1config.readSeqCmd.value = SPI_FLASH_READ_CACHE_X2;
          p1config.readSeqData.ios = XSPI_NUMBER_OF_IOS_2;
          p1config.readSeqDummyCnt = 8;
      break;

      case 4:
          DEBUG_XSPI_LOG("read x4\n");
          p1config.readSeqCmd.value = SPI_FLASH_READ_CACHE_X4;
          p1config.readSeqData.ios = XSPI_NUMBER_OF_IOS_4;
          p1config.readSeqDummyCnt = 8;
      break;
      case 8:
          DEBUG_XSPI_LOG("read x8\n");
          p1config.readSeqCmd.value = SPI_FLASH_READ_CACHE_X8;
          p1config.readSeqData.ios = XSPI_NUMBER_OF_IOS_8;
          p1config.readSeqDummyCnt = 8;
      break;

      case 1:
      default:
          DEBUG_XSPI_LOG("read x1\n");
          p1config.readSeqCmd.value = SPI_FLASH_READ_CACHE;
          p1config.readSeqData.ios = XSPI_NUMBER_OF_IOS_1;
          p1config.readSeqDummyCnt = 8;
      break;

  }
  handler->drv->setReadSeqP1Config(handler->pD ,&p1config);

}

static XSPI_HandleTypeDef *nand_init(XSPI_InitTypeDef *init){
  XSPI_HandleTypeDef *handler;
  handler = itcs_xspi_init(init);
  handler->init = *init;
  if(handler == NULL) {
    printf("[XSPI] XSPI init failed, handler is NULL\n");
    return handler;
  }
  nand_basic_config(handler);
  nand_program_config(handler);
  nand_read_config(handler);

  nand_reset(handler); 
  nand_get_id(handler);
  nand_enable_ecc(handler, true);
  nand_get_features(handler);
  
  if(init->line_num == 4){
    // must be enable in GD5F1G spi nand flash
    nand_enable_quad_op(handler, true);
  }

  //disable block protect
  nand_write_protect(handler, false);

  return handler;
}

static uint32_t nand_construct_addr(struct nand_mem_st* nand_mem) {
  uint32_t addr = 0;
  if (!nand_mem) {
    printf("[XSPI] nand_mem NULL!\n");
    return -1;
  }
  addr =
  nand_mem->nand_addr.row_addr.row_addr_st.block_idx * SPI_FLASH_BLOCK_SIZE +
  nand_mem->nand_addr.row_addr.row_addr_st.page_idx * SPI_FLASH_PAGE_SIZE +
  nand_mem->nand_addr.column_addr ;
  nand_mem->mem_addr = addr;

  DEBUG_XSPI_LOG("[XSPI] block index=%d, page index=%d, offset in page=%d, addr=0x%x\n", 
                nand_mem->nand_addr.row_addr.row_addr_st.block_idx,
                nand_mem->nand_addr.row_addr.row_addr_st.page_idx,
                nand_mem->nand_addr.column_addr,
                addr );
  return addr;
}

static int nand_parse_addr(uint32_t addr, struct nand_mem_st* nand_mem) {
  if (addr >= SPI_FLASH_FULL_SIZE) {
    printf("[XSPI] spi nand flash address out of range!\n");
    return -1;
  }

  nand_mem->nand_addr.row_addr.row_addr_st.block_idx = addr / (uint32_t)SPI_FLASH_BLOCK_SIZE;
  nand_mem->nand_addr.row_addr.row_addr_st.page_idx  = (addr % (uint32_t)SPI_FLASH_BLOCK_SIZE) / (uint32_t)SPI_FLASH_PAGE_SIZE;
  nand_mem->nand_addr.column_addr = addr % (uint32_t)SPI_FLASH_PAGE_SIZE;
  nand_mem->mem_addr = addr;

  DEBUG_XSPI_LOG("[XSPI] block idx=%d, page idx=%d, offset=%d\n", 
                nand_mem->nand_addr.row_addr.row_addr_st.block_idx,
                nand_mem->nand_addr.row_addr.row_addr_st.page_idx,
                nand_mem->nand_addr.column_addr );
  return 0;
}

static int nand_read_from_page(XSPI_HandleTypeDef *handler, struct nand_mem_st* nand_mem, uint8_t *pBuffer, uint32_t byte_num) {
  // Sending read to cache command & address.
  // this address is row address page_addr:[5:0], block_addr[15:6]
  uint8_t* buf = pBuffer;
  uint32_t row_addr = nand_mem->nand_addr.row_addr.row_addr_uint32;

  int padding_num = 0;
  if(byte_num % BYTES_PER_XSPI_DMA_OP){
    buf = malloc(byte_num - (byte_num % BYTES_PER_XSPI_DMA_OP) + BYTES_PER_XSPI_DMA_OP);
    padding_num = BYTES_PER_XSPI_DMA_OP - (byte_num % BYTES_PER_XSPI_DMA_OP);
  }
  
  DEBUG_XSPI_LOG("[XSPI] Read [%d byes] data from block[%d] page[%d]\n",byte_num, nand_mem->nand_addr.row_addr.row_addr_st.block_idx ,nand_mem->nand_addr.row_addr.row_addr_st.page_idx);
  switch (handler->work_mode) {
  case CDNS_XSPI_MODE_DIRECT: 
    DEBUG_XSPI_LOG("[XSPI] read data in page by direct mode.\n");
    XSPI_DirectCmd directCmd;
    directCmd.direction    = XSPI_DATA_TRANS_DIR_READ;
    directCmd.sysMemPtr    = (uintptr_t)buf;
    directCmd.transferSize = byte_num+padding_num;
    directCmd.transferAddr = row_addr;
    DEBUG_XSPI_LOG("[XSPI] direct read row_addr = 0x%x\n",row_addr);
    //nand_read_config(handler);
    cdns_xspi_send_direct_command(handler, &directCmd);
    nand_wait_busy(handler);
    if(padding_num)
        memcpy(pBuffer, buf, byte_num);
  break;
  
  case CDNS_XSPI_MODE_STIG: {
    DEBUG_XSPI_LOG("[XSPI] read data in page by stig mode.\n");
    XSPI_StigCommand* cmd;
    cmd = construct_stig_cmd(false, 1, false, NULL, 0, XSPI_P10_INSTR_SNA_READ_PAGE, SPI_FLASH_PAGE_READ, 0, row_addr, 3);
    cdns_xspi_send_stig_command(handler, cmd);
    nand_wait_busy(handler);

    DEBUG_XSPI_LOG("nand read page handler->init.line_num = %d\n",handler->init.line_num);
    switch(handler->init.line_num){
        case 1:
        DEBUG_XSPI_LOG("read x1\n");
        cmd = construct_stig_cmd(false, 1, false, buf, byte_num+padding_num, XSPI_P10_INSTR_SNA_READ_CACHE, SPI_FLASH_READ_CACHE, 8, nand_mem->nand_addr.column_addr, 2);
        break;
        case 2:
        DEBUG_XSPI_LOG("read x2\n");
        cmd = construct_stig_cmd(false, 2, false, buf, byte_num+padding_num, XSPI_P10_INSTR_SNA_READ_CACHE, SPI_FLASH_READ_CACHE_X2, 8, nand_mem->nand_addr.column_addr, 2);
        break;
        case 4:
        DEBUG_XSPI_LOG("read x4\n");
        cmd = construct_stig_cmd(false, 4, false, buf, byte_num+padding_num, XSPI_P10_INSTR_SNA_READ_CACHE, SPI_FLASH_READ_CACHE_X4, 8, nand_mem->nand_addr.column_addr, 2);
        break;
        case 8:
        DEBUG_XSPI_LOG("read x8\n");
        cmd = construct_stig_cmd(false, 8, false, buf, byte_num+padding_num, XSPI_P10_INSTR_SNA_READ_CACHE, SPI_FLASH_READ_CACHE_X8, 8, nand_mem->nand_addr.column_addr, 2);
        default:
        DEBUG_XSPI_LOG("default read x1\n");
        cmd = construct_stig_cmd(false, 1, false, buf, byte_num+padding_num, XSPI_P10_INSTR_SNA_READ_CACHE, SPI_FLASH_READ_CACHE, 8, nand_mem->nand_addr.column_addr, 2);
        break;

    }
    
    cdns_xspi_send_stig_command(handler, cmd);
    nand_wait_busy(handler);
    if(padding_num)
        memcpy(pBuffer, buf, byte_num);
  } break;
 
  case CDNS_XSPI_MODE_ACMD_PIO: {
    DEBUG_XSPI_LOG("[XSPI] read data in page by pio mode.\n");
    XSPI_PioCommand pioCmd;
    pioCmd.params.bankSelect = 0U;
    pioCmd.params.cmdCount = byte_num+padding_num;
    pioCmd.params.cmdType  = XSPI_ACMD_COMMAND_TYPE_READ_SEQ;
    pioCmd.params.xSpiAddr   = row_addr;
    pioCmd.params.sysMemPtr = (uintptr_t)buf;
    pioCmd.params.dmaSelect = XSPI_ACMD_DMA_SELECT_MASTER;
    pioCmd.params.disXipMb  = false;
    pioCmd.params.enXipMb            = false;
    pioCmd.params.raiseCmdCompleteCb = false;
    //nand_read_config(handler);
    cdns_xspi_send_acmd_pio_command(handler, &pioCmd);
    nand_wait_busy(handler);
    if(padding_num)
        memcpy(pBuffer, buf, byte_num);
  } break;

  case CDNS_XSPI_MODE_ACMD_CMDA: {
    DEBUG_XSPI_LOG("[XSPI] read data in page by cdma mode.\n");
    XSPI_CdmaCommand cdmaCmd;
    cdmaCmd.params.bankSelect = 0U;
    cdmaCmd.params.cmdCount = byte_num+padding_num;
    cdmaCmd.params.cmdType = XSPI_ACMD_COMMAND_TYPE_READ_SEQ;
    cdmaCmd.params.xSpiAddr = row_addr;
    cdmaCmd.params.sysMemPtr = (uintptr_t)buf;
    cdmaCmd.params.dmaSelect = XSPI_ACMD_DMA_SELECT_MASTER;
    cdmaCmd.params.disXipMb = false;
    cdmaCmd.params.enXipMb = false;
    cdmaCmd.params.raiseCmdCompleteCb = false;
    cdmaCmd.ignoreXSpiAddr = false;
    cdmaCmd.ignoreSysMemPtr = false;
    DEBUG_XSPI_LOG("[XSPI] disable irq\n");
    writel(0x0, (handler->reg_base  + 0x0114));
    //nand_read_config(handler);
    cdns_xspi_send_acmd_cdma_command(handler, &cdmaCmd);
    nand_wait_busy(handler);
    if(padding_num)
        memcpy(pBuffer, buf, byte_num);
  }break;

  default:
    break;
  }

  return byte_num;
}

static int nand_generate_next_page_addr(struct nand_mem_st* nand_mem){
    nand_mem->nand_addr.column_addr = 0;
    nand_mem->nand_addr.row_addr.row_addr_st.page_idx = (nand_mem->nand_addr.row_addr.row_addr_st.page_idx + 1) % 64;
    if(nand_mem->nand_addr.row_addr.row_addr_st.page_idx == 0 ){
        nand_mem->nand_addr.row_addr.row_addr_st.block_idx++;
    }

    if(nand_mem->nand_addr.row_addr.row_addr_st.block_idx >= SPI_FLASH_BLOCK_NUM){
        printf("[XSPI] Nand flash address reach to bound, stop next operation!");
        return -1;
    }

    return 0;
}

static uint32_t nand_write_whole_page(XSPI_HandleTypeDef *handler, uint32_t addr, uint8_t *pBuffer) {
  XSPI_StigCommand* cmd;
  #if 0
  for(int i = 0; i< 2048; i++){
    DEBUG_XSPI_LOG("0x%x ",pBuffer[i]);
  }
  DEBUG_XSPI_LOG("\n");
  #endif
  nand_wait_busy(handler);
  switch (handler->work_mode) {
  case CDNS_XSPI_MODE_DIRECT:
    DEBUG_XSPI_LOG("[XSPI] nand flash write in DIRECT mode\n");
    XSPI_DirectCmd directCmd;
    directCmd.direction    = XSPI_DATA_TRANS_DIR_WRITE;
    directCmd.sysMemPtr    = (uintptr_t)pBuffer;
    directCmd.transferSize = SPI_FLASH_PAGE_SIZE;
    directCmd.transferAddr = addr;
    //nand_program_config(handler);
    cmd = construct_stig_cmd(false, 1, false, NULL, 0, XSPI_P10_INSTR_WRITE_ENABLE_LATCH, SPI_FLASH_WRITE_ENABLE, 0, 0, 0);
    cdns_xspi_send_stig_command(handler, cmd);
    cdns_xspi_send_direct_command(handler, &directCmd);
    nand_wait_busy(handler);
  break;
  case CDNS_XSPI_MODE_STIG: 
    DEBUG_XSPI_LOG("[XSPI] nand flash write in STIG mode\n");
    DEBUG_XSPI_LOG("nand write page handler->init.line_num = %d\n",handler->init.line_num);
    cmd = construct_stig_cmd(false, 1, false, NULL, 0, XSPI_P10_INSTR_WRITE_ENABLE_LATCH, SPI_FLASH_WRITE_ENABLE, 0, 0, 0);
    cdns_xspi_send_stig_command(handler, cmd);
    nand_wait_busy(handler);
    switch(handler->init.line_num){
        case 1:
        case 2:
        DEBUG_XSPI_LOG("write x1\n");
        cmd = construct_stig_cmd(false, 1, true, pBuffer, SPI_FLASH_PAGE_SIZE, XSPI_P10_INSTR_SNA_PROGRAM_LOAD, SPI_FLASH_PROGRAM_LOAD, 0, addr, 2);
        break;
        case 4:
        DEBUG_XSPI_LOG("write x4\n");
        cmd = construct_stig_cmd(false, 4, true, pBuffer, SPI_FLASH_PAGE_SIZE, XSPI_P10_INSTR_SNA_PROGRAM_LOAD, SPI_FLASH_PROGRAM_LOAD4, 0, addr, 2);
        break;
        case 8:
        DEBUG_XSPI_LOG("write x8\n");
        cmd = construct_stig_cmd(false, 8, true, pBuffer, SPI_FLASH_PAGE_SIZE, XSPI_P10_INSTR_SNA_PROGRAM_LOAD, SPI_FLASH_PROGRAM_LOAD8, 0, addr, 2);
        break;
        default:
        DEBUG_XSPI_LOG("default write x1\n");
        cmd = construct_stig_cmd(false, 1, true, pBuffer, SPI_FLASH_PAGE_SIZE, XSPI_P10_INSTR_SNA_PROGRAM_LOAD, SPI_FLASH_PROGRAM_LOAD, 0, addr, 2);
        break;

    }
    cdns_xspi_send_stig_command(handler, cmd);

    // Sending Write Enable.
    cmd = construct_stig_cmd(false, 1, false, NULL, 0, XSPI_P10_INSTR_WRITE_ENABLE_LATCH, SPI_FLASH_WRITE_ENABLE, 0, 0, 0);
    cdns_xspi_send_stig_command(handler, cmd);

    cmd = construct_stig_cmd(false, 1, false, NULL, 0, XSPI_P10_INSTR_SNA_PROGRAM_EXEC, SPI_FLASH_PROGRAM_EXEC, 0, addr, 3);
    cdns_xspi_send_stig_command(handler, cmd);
    nand_wait_busy(handler);
  break;
  case CDNS_XSPI_MODE_ACMD_PIO: 
    DEBUG_XSPI_LOG("[XSPI] nand flash write in PIO mode\n");
    XSPI_PioCommand pioCmd;
    pioCmd.params.bankSelect = 0U;
    pioCmd.params.cmdCount = SPI_FLASH_PAGE_SIZE;
    pioCmd.params.cmdType  = XSPI_ACMD_COMMAND_TYPE_PROGRAM_SEQ;
    pioCmd.params.xSpiAddr   = addr;
    pioCmd.params.sysMemPtr = (uintptr_t)pBuffer;
    pioCmd.params.dmaSelect = XSPI_ACMD_DMA_SELECT_MASTER;
    pioCmd.params.disXipMb  = false;
    pioCmd.params.enXipMb            = false;
    pioCmd.params.raiseCmdCompleteCb = false;
    //nand_program_config(handler);
    cmd = construct_stig_cmd(false, 1, false, NULL, 0, XSPI_P10_INSTR_WRITE_ENABLE_LATCH, SPI_FLASH_WRITE_ENABLE, 0, 0, 0);
    cdns_xspi_send_stig_command(handler, cmd);
    cdns_xspi_send_acmd_pio_command(handler, &pioCmd);
    nand_wait_busy(handler);
  break;
  case CDNS_XSPI_MODE_ACMD_CMDA:
    DEBUG_XSPI_LOG("[XSPI] nand flash write in CDMA mode\n");
    XSPI_CdmaCommand cdmaCmd;
    cdmaCmd.params.bankSelect = 0U;
    cdmaCmd.params.cmdCount = SPI_FLASH_PAGE_SIZE;
    cdmaCmd.params.cmdType = XSPI_ACMD_COMMAND_TYPE_PROGRAM_SEQ;
    cdmaCmd.params.xSpiAddr = addr;
    cdmaCmd.params.sysMemPtr = (uintptr_t)pBuffer;
    cdmaCmd.params.dmaSelect = XSPI_ACMD_DMA_SELECT_MASTER;
    cdmaCmd.params.disXipMb = false;
    cdmaCmd.params.enXipMb = false;
    cdmaCmd.params.raiseCmdCompleteCb = false;
    cdmaCmd.ignoreXSpiAddr = false;
    cdmaCmd.ignoreSysMemPtr = false;
    //nand_program_config(handler);
    cmd = construct_stig_cmd(false, 1, false, NULL, 0, XSPI_P10_INSTR_WRITE_ENABLE_LATCH, SPI_FLASH_WRITE_ENABLE, 0, 0, 0);
    cdns_xspi_send_stig_command(handler, cmd);
    cdns_xspi_send_acmd_cdma_command(handler, &cdmaCmd);
    nand_wait_busy(handler);
  break;

  default:
    break;
  }

  return SPI_FLASH_PAGE_SIZE;
}

static uint32_t nand_write_whole_block(XSPI_HandleTypeDef *handler,
                                  uint32_t block_idx, uint8_t *pBuffer) {
  DEBUG_XSPI_LOG("[XSPI] nand flash write block[%d]\n",block_idx);
  struct nand_mem_st nand_mem;
  uint32_t  addr = 0;
  nand_mem.nand_addr.column_addr = 0;
  nand_mem.nand_addr.row_addr.row_addr_st.block_idx =  block_idx;

  for (int i = 0; i < SPI_FLASH_PAGE_NUM_PER_BLOCK; i++) {
    nand_mem.nand_addr.row_addr.row_addr_st.page_idx = i;
    addr = nand_construct_addr(&nand_mem);
    nand_write_whole_page(handler, addr ,&pBuffer[i * SPI_FLASH_PAGE_SIZE]);
  }
  
  return 0;
}


static uint32_t nand_read(XSPI_HandleTypeDef *handler, uint8_t *pBuffer,
                         uint32_t addr, uint32_t byte_num){
  int ret = 0;
  uint32_t alreay_read_nums = 0;
  uint32_t first_page_remain = 0; // first page means the page which the @addr in.
  uint32_t bytes_remain = byte_num;
  uint8_t* rx_buf = pBuffer;
  uint32_t bytes_to_read = 0;
  struct nand_mem_st nand_mem = {0};
  DEBUG_XSPI_LOG("[XSPI] nand flash read... ");

  ret = nand_parse_addr(addr, &nand_mem);
  if (ret) {
    printf("[XSPI] spi nand read failed!\n");
    return 0;
  }

  first_page_remain = SPI_FLASH_PAGE_SIZE - nand_mem.nand_addr.column_addr;

  // data can read complete in first page
  if(first_page_remain >= bytes_remain){
    nand_read_from_page(handler, &nand_mem, rx_buf, bytes_remain);
    DEBUG_XSPI_LOG("ok\n");
    return byte_num;
  }
  
  // read first page
  nand_read_from_page(handler, &nand_mem, rx_buf, first_page_remain);
  bytes_remain -= first_page_remain;
  alreay_read_nums += SPI_FLASH_PAGE_SIZE;

  // continually read from several pages
  do{
    bytes_to_read = (bytes_remain < SPI_FLASH_PAGE_SIZE) ? bytes_remain : SPI_FLASH_PAGE_SIZE;
    if(nand_generate_next_page_addr(&nand_mem)){
        return byte_num;
    }
    nand_read_from_page(handler, &nand_mem, &rx_buf[alreay_read_nums], bytes_to_read);
    alreay_read_nums += bytes_to_read;
    bytes_remain -= bytes_to_read;
  } while (bytes_remain);

  DEBUG_XSPI_LOG("ok\n");
  return byte_num;
}


static bool nand_erase(XSPI_HandleTypeDef *handler, SPI_FLASH_ERASE_TYPE type,
                      uint32_t addr) {
  struct nand_mem_st nand_mem;
  nand_parse_addr(addr, &nand_mem);
  nand_mem.nand_addr.row_addr.row_addr_st.page_idx = 0;
  if (type == SPI_FLASH_ERASE_FULL_CHIP) {
    printf("[XSPI] full chip erase is not support in gd5f1g\n");
    return false;
  } else if (type == SPI_FLASH_ERASE_SECTOR) {
    printf("[XSPI] sector erase is not support in gd5f1g\n");
    return false;
  } else if (type == SPI_FLASH_ERASE_BLOCK) {
      XSPI_StigCommand* cmd;
      DEBUG_XSPI_LOG("[XSPI] nand flash erase... ");
      nand_wait_busy(handler);
      //WEL.
      cmd = construct_stig_cmd(false, 1, false, NULL, 0, XSPI_P10_INSTR_WRITE_ENABLE_LATCH, SPI_FLASH_WRITE_ENABLE, 0, 0, 0);
      cdns_xspi_send_stig_command(handler, cmd);

      cmd = construct_stig_cmd(false, 1, false, NULL, 0, XSPI_P10_INSTR_ERASE_SECTOR, SPI_FLASH_BLOCK_ERASE, 0, nand_mem.nand_addr.row_addr.row_addr_uint32, 3);
      cdns_xspi_send_stig_command(handler, cmd);
      nand_wait_busy(handler);
      DEBUG_XSPI_LOG("ok\n");

  } else {
    printf("[XSPI] erase way is not support in nand flash\n");
    return false;
  }
 
  return true;
  
}


static uint32_t nand_write(XSPI_HandleTypeDef *handler, uint8_t *pBuffer,
                          uint32_t addr, uint32_t byte_num) {
  struct nand_mem_st nand_mem = {0};
  uint32_t block_start_addr = 0;
  uint32_t first_block_remain_bytes = 0;
  uint32_t bytes_to_write = 0;
  uint32_t already_write = 0;
  uint32_t bytes_remain = byte_num;
  uint8_t *flash_buf = (uint8_t *)malloc(SPI_FLASH_BLOCK_SIZE);
  memset(flash_buf, 0, SPI_FLASH_BLOCK_SIZE);
  
  DEBUG_XSPI_LOG("[XSPI] nand flash write\n");
  nand_parse_addr(addr, &nand_mem);
  
  first_block_remain_bytes = SPI_FLASH_BLOCK_SIZE - 
            (nand_mem.nand_addr.row_addr.row_addr_st.page_idx * SPI_FLASH_PAGE_SIZE + nand_mem.nand_addr.column_addr);
  bytes_to_write = (first_block_remain_bytes < bytes_remain) ? first_block_remain_bytes : bytes_remain;
  
  while(bytes_remain){
    
    block_start_addr = nand_mem.nand_addr.row_addr.row_addr_st.block_idx * SPI_FLASH_BLOCK_SIZE;
    if( bytes_to_write != SPI_FLASH_BLOCK_SIZE){
        nand_read(handler, flash_buf, block_start_addr, SPI_FLASH_BLOCK_SIZE);
    }
    nand_erase(handler, SPI_FLASH_ERASE_BLOCK, addr);
    memcpy(&flash_buf[(nand_mem.nand_addr.row_addr.row_addr_st.page_idx * SPI_FLASH_PAGE_SIZE) + nand_mem.nand_addr.column_addr], &pBuffer[already_write], bytes_to_write);
    DEBUG_XSPI_LOG("********************write a block[%d]*******************\n",nand_mem.nand_addr.row_addr.row_addr_st.block_idx);
    DEBUG_XSPI_LOG("********************first_block_remain_bytes=0x%x*********************\n",first_block_remain_bytes);
    DEBUG_XSPI_LOG("********************bytes_to_write=0x%x*********************\n",bytes_to_write);
    DEBUG_XSPI_LOG("********************block_start_addr=0x%x*********************\n",block_start_addr);
    nand_write_whole_block(handler, nand_mem.nand_addr.row_addr.row_addr_st.block_idx, flash_buf);
    already_write += bytes_to_write;
    bytes_remain -= bytes_to_write;
    nand_mem.nand_addr.row_addr.row_addr_st.block_idx++;
    nand_mem.nand_addr.column_addr = 0;
    nand_mem.nand_addr.row_addr.row_addr_st.page_idx = 0;
    bytes_to_write = ( SPI_FLASH_BLOCK_SIZE < bytes_remain) ? SPI_FLASH_BLOCK_SIZE : bytes_remain;
    if(nand_mem.nand_addr.row_addr.row_addr_st.block_idx >= SPI_FLASH_BLOCK_NUM){
        printf("[XSPI] nand flash address already reach to bound, write operation exit.\n");
        return already_write;
    }
  }

  free(flash_buf);
  return byte_num;
}

static bool nand_write_protect(XSPI_HandleTypeDef *handler, bool enable) {
  XSPI_StigCommand* cmd;
  XSPI_SetWriteProtect(handler->pD, enable);

  //WEL
  cmd = construct_stig_cmd(false, 1, false, NULL, 0, XSPI_P10_INSTR_WRITE_ENABLE_LATCH, SPI_FLASH_WRITE_ENABLE, 0, 0, 0);
  cdns_xspi_send_stig_command(handler, cmd);

  if (enable == true) {
    //Set feature
    cmd = construct_stig_cmd(false, 1, true, NULL, 0, XSPI_P10_INSTR_SNA_SET_FEATURES, SPI_FLASH_SET_FEATURE, 0, 0xA0, 1);
    cmd->instructionChain->profile10Instr.dataNoOfBytes = 1;
    cmd->instructionChain->profile10Instr.data[0] = 0x38;
    cdns_xspi_send_stig_command(handler, cmd);
    nand_wait_busy(handler);

  } else {
    //Set feature
    cmd = construct_stig_cmd(false, 1, true,NULL, 0, XSPI_P10_INSTR_SNA_SET_FEATURES, SPI_FLASH_SET_FEATURE, 0, 0xA0, 1);
    cmd->instructionChain->profile10Instr.dataNoOfBytes = 1;
    cmd->instructionChain->profile10Instr.data[0] = 0x00;
    cdns_xspi_send_stig_command(handler, cmd);
    nand_wait_busy(handler);
  }
  nand_get_features(handler);
  return true;
}


static uint32_t nand_get_alignment(XSPI_HandleTypeDef *handler) {
  return SPI_FLASH_PAGE_SIZE;
}


struct xspi_flash_operations f_ops_xspi_nand = {.init         = nand_init,
                                               .read          = nand_read,
                                               .write         = nand_write,
                                               .erase         = nand_erase,
                                               .get_alignment = nand_get_alignment,
                                               .write_protect = nand_write_protect,
                                               .reset         = nand_reset};

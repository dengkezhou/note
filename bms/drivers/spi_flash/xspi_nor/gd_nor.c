#include <malloc.h>
#include <common.h>
#include <xspi.h>
#include "xspi_nor_flash.h"
#include <malloc.h>
#include <cache.h>

#define SPI_FLASH_PAGE_SIZE   (256)
#define SPI_FLASH_SECTOR_SIZE (16 * SPI_FLASH_PAGE_SIZE)
#define SPI_FLASH_BLOCK_SIZE  (16 * SPI_FLASH_SECTOR_SIZE)
#define SPI_FLASH_FULL_SIZE   (512 * SPI_FLASH_BLOCK_SIZE)

#define SPI_FLASH_DummyDataByte    0x00
#define SPI_FLASH_WriteEnable      0x06
#define SPI_FLASH_WriteDisable     0x04
#define SPI_FLASH_ReadStatusReg    0x05
#define SPI_FLASH_ReadStatusReg2   0x35
#define SPI_FLASH_ReadStatusReg3   0x15
#define SPI_FLASH_WriteStatusReg   0x01
#define SPI_FLASH_WriteStatusReg2  0x31
#define SPI_FLASH_WriteStatusReg3  0x11

#define SPI_FLASH_ReadData         0x03
#define SPI_FLASH_FastReadDual     0x3B
#define SPI_FLASH_FastReadQuad     0x6B
#define SPI_FLASH_FastReadOctal    0x8B
#define SPI_FLASH_DtrReadDataQuad  0xED

#define SPI_FLASH_PageProgram      0x02
#define SPI_FLASH_PageProgramQuad  0x32
#define SPI_FLASH_PageProgramOctal 0x82

#define SPI_FLASH_BlockErase       0xD8
#define SPI_FLASH_SectorErase      0x20
#define SPI_FLASH_ChipErase        0xC7
#define SPI_FLASH_PowerDown        0xB9
#define SPI_FLASH_ReleasePowerDown 0xAB
#define SPI_FLASH_DeviceID         0xAB
#define SPI_FLASH_ManufactDeviceID 0x90
#define SPI_FLASH_JedecDeviceID    0x9F
#define SPI_FLASH_ENABLE_POR       0x66
#define SPI_FLASH_POR              0x99
#define SPI_FLASH_LOCK             0x7E
#define SPI_FLASH_UNLOCK           0x98

static XSPI_StigCommand stigCmd;
static XSPI_StigInstruction stigInstr;
static XSPI_StigDataSeqLayout dataSeqInstr;

static XSPI_StigCommand *
construct_stig_cmd(bool ddr, int lines, bool wr, uint8_t *buf, uint32_t len,
                   XSPI_Profile10AutonomicInstrType instr_type, uint8_t opcode,
                   uint8_t dummy, uint64_t addr, uint32_t addr_len) {
  stigInstr.stigInstrType                     = XSPI_STIG_INSTR_TYPE_PROFILE_10;
  stigInstr.profile10Instr.profile10InstrType = instr_type;
  stigInstr.profile10Instr.xipEnable          = false;

  stigInstr.profile10Instr.instrOpcodePhase.value = opcode;
  stigInstr.profile10Instr.instrOpcodeExt.enable  = false;
  stigInstr.profile10Instr.instrOpcodeExt.value   = 0;
  stigInstr.profile10Instr.instrAddrPhase.count   = addr_len;

  stigInstr.profile10Instr.dataNoOfBytes = 0;
  stigInstr.profile10Instr.crcVariant    = XSPI_CRC_VARIANT_CALC_ADDR_PHASE;
  stigInstr.profile10Instr.addrShift     = false;
  stigInstr.profile10Instr.address       = addr;
  stigInstr.profile10Instr.data[0]       = 0;
  stigInstr.profile10Instr.data[1]       = 0;

  dataSeqInstr.crcChunkSize   = 0;
  dataSeqInstr.crcInversion   = false;
  dataSeqInstr.crcOe          = false;
  dataSeqInstr.crcUalChunkEn  = false;
  dataSeqInstr.crcUalChunkChk = false;
  dataSeqInstr.dataSwap       = false;
  if (wr) {
    dataSeqInstr.dir       = XSPI_DATA_TRANS_DIR_WRITE;
    dataSeqInstr.sysMemPtr = (uintptr_t)buf;
  } else {
    dataSeqInstr.dir = XSPI_DATA_TRANS_DIR_READ;
    if (len > 2) {
      dataSeqInstr.sysMemPtr = (uintptr_t)buf;
      dataSeqInstr.rdMode    = XSPI_READ_DATA_EXTENDED_MODE;
    } else {
      dataSeqInstr.sysMemPtr = 0;
      dataSeqInstr.rdMode    = XSPI_READ_DATA_SHORT_MODE;
    }
  }

  dataSeqInstr.dataPerAddress    = XSPI_DATA_PER_ADDRESS_1B;
  dataSeqInstr.noOfDummy         = dummy;
  dataSeqInstr.hfReadBoundEnable = false;
  dataSeqInstr.dataNoOfBytes     = len;
  stigInstr.profile10Instr.instrOpcodePhase.edge = XSPI_CMD_EDGE_MODE_SDR;

  stigInstr.profile10Instr.instrOpcodePhase.ios = XSPI_NUMBER_OF_IOS_1;
  stigInstr.profile10Instr.instrAddrPhase.ios   = XSPI_NUMBER_OF_IOS_1;
  switch (lines) {
  case 1:
    //stigInstr.profile10Instr.instrAddrPhase.ios   = XSPI_NUMBER_OF_IOS_1;
    dataSeqInstr.instrDataPhase.ios               = XSPI_NUMBER_OF_IOS_1;
    break;
  case 2:
    //stigInstr.profile10Instr.instrAddrPhase.ios   = XSPI_NUMBER_OF_IOS_2;
    dataSeqInstr.instrDataPhase.ios               = XSPI_NUMBER_OF_IOS_2;
    break;
  case 4:
    //stigInstr.profile10Instr.instrAddrPhase.ios   = XSPI_NUMBER_OF_IOS_4;
    dataSeqInstr.instrDataPhase.ios               = XSPI_NUMBER_OF_IOS_4;
    break;
  case 8:
    //stigInstr.profile10Instr.instrAddrPhase.ios   = XSPI_NUMBER_OF_IOS_8;
    dataSeqInstr.instrDataPhase.ios               = XSPI_NUMBER_OF_IOS_8;
    break;
  default:
    printf("Invalid line number\n");
    return NULL;
    break;
  }

  if (ddr == false) {
    stigInstr.profile10Instr.instrAddrPhase.edge   = XSPI_ADDR_EDGE_MODE_SDR;
    dataSeqInstr.instrDataPhase.edge               = XSPI_DATA_EDGE_MODE_SDR;
  } else {
    stigInstr.profile10Instr.instrAddrPhase.edge   = XSPI_ADDR_EDGE_MODE_DDR;
    dataSeqInstr.instrDataPhase.edge               = XSPI_DATA_EDGE_MODE_DDR;
    stigInstr.profile10Instr.instrAddrPhase.ios   = XSPI_NUMBER_OF_IOS_4;
    dataSeqInstr.instrDataPhase.ios               = XSPI_NUMBER_OF_IOS_4;
  }

  stigCmd.instructionChain = &stigInstr;
  stigCmd.instrChainLength = 1;
  if (len)
    stigCmd.dataSeqInstr = &dataSeqInstr;
  else
    stigCmd.dataSeqInstr = NULL;
  stigCmd.commCrcEnable  = false;
  stigCmd.commBankSelect = 0;
  return &stigCmd;
}

#if 0
static void nor_program_config_direct_acmd(XSPI_HandleTypeDef *handler){
    XSPI_WelSeqConfig wel_config;
    XSPI_ProgramSeqP1Config p1config;
    XSPI_GlobalCommandParameters g_param;
    XSPI_StatSeqP1Config stat_config;

    g_param.seqType = XSPI_SEQUENCE_TYPE_P1_SPI_NOR;
    g_param.dataPerAddress = XSPI_DATA_PER_ADDRESS_1B;
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

    //0x440
    wel_config.welSeqCmd.edge = XSPI_CMD_EDGE_MODE_SDR;
    wel_config.welSeqCmd.ios = XSPI_NUMBER_OF_IOS_1;
    wel_config.welSeqCmd.value = SPI_FLASH_WriteEnable;
    wel_config.welSeqCmdExt.enable = false;
    handler->drv->setWelSeqConfig(handler->pD ,&wel_config);

    //0x430 0x434
    p1config.progSeqCmd.edge = XSPI_CMD_EDGE_MODE_SDR;
    p1config.progSeqCmd.ios =XSPI_NUMBER_OF_IOS_1;
    p1config.progSeqCmdExt.enable = false;
    p1config.progSeqAddr.edge = XSPI_ADDR_EDGE_MODE_SDR;
    p1config.progSeqAddr.ios = XSPI_NUMBER_OF_IOS_1;
    p1config.progSeqAddr.count = 3;
    p1config.progSeqData.edge = XSPI_DATA_EDGE_MODE_SDR;

    switch(handler->init.line_num){
        case 4:
            printf("write x4\n");
            p1config.progSeqCmd.value = SPI_FLASH_PageProgramQuad;
            p1config.progSeqData.ios = XSPI_NUMBER_OF_IOS_4;
        break;

        case 8:
            printf("write x8\n");
            p1config.progSeqCmd.value = SPI_FLASH_PageProgramOctal;
            p1config.progSeqData.ios = XSPI_NUMBER_OF_IOS_8;
        break;

        case 1:
        case 2:
        default:
            printf("write x1\n");
            p1config.progSeqCmd.value = SPI_FLASH_PageProgram;
            p1config.progSeqData.ios = XSPI_NUMBER_OF_IOS_1;
        break;

    }
    handler->drv->setProgramSeqP1Config(handler->pD ,&p1config);

    stat_config.statSeqData.edge = XSPI_DATA_EDGE_MODE_SDR;
    stat_config.statSeqData.ios = XSPI_NUMBER_OF_IOS_1;
    stat_config.statSeqAddrEdge = XSPI_ADDR_EDGE_MODE_SDR;
    stat_config.statSeqAddrIos = XSPI_NUMBER_OF_IOS_1;
    stat_config.statSeqAddrCnt = XSPI_STAT_SEQ_ADDR_COUNT_1_ADDR_BYTE;
    stat_config.statSeqCmdExtEn = false;
    stat_config.statSeqCmdEdge = XSPI_CMD_EDGE_MODE_SDR;
    stat_config.statSeqCmdIos = XSPI_NUMBER_OF_IOS_1;
    stat_config.statSeqErsFailAddrEn = false;
    stat_config.statSeqErsFailDummyCnt = 0;
    stat_config.statSeqProgFailAddrEn = false;
    stat_config.statSeqProgFailDummyCnt = 0;
    stat_config.statSeqDevRdyAddrEn = false;
    stat_config.statSeqDevRdyDummyCnt = 0;
    stat_config.statSeqProgFailCmdVal = 0x05;
    stat_config.statSeqErsFailCmdVal = 0x05;
    stat_config.statSeqDevRdyCmdVal = 0x05;
    stat_config.statSeqProgFailCmdExtVal = 0x00;
    stat_config.statSeqErsFailCmdExtVal = 0x00;
    stat_config.statSeqDevRdyCmdExtVal = 0x00;
    handler->drv->setStatSeqP1Config(handler->pD ,&stat_config);

}

static void nor_read_config_direct_acmd(XSPI_HandleTypeDef *handler){
    XSPI_ReadSeqP1Config p1config;
    XSPI_GlobalCommandParameters g_param;
    //XSPI_StatSeqP1Config stat_config;

    g_param.seqType = XSPI_SEQUENCE_TYPE_P1_SPI_NOR;
    g_param.dataPerAddress = XSPI_DATA_PER_ADDRESS_1B;
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
    
    p1config.readSeqCmd.edge = XSPI_CMD_EDGE_MODE_SDR;
    p1config.readSeqCmd.ios = XSPI_NUMBER_OF_IOS_1;
    p1config.readSeqCmdExt.enable = false;
    p1config.readSeqCmdExt.value = 0;
    p1config.readSeqAddr.edge = XSPI_ADDR_EDGE_MODE_SDR;
    p1config.readSeqAddr.ios = XSPI_NUMBER_OF_IOS_1;
    p1config.readSeqAddr.count = 3;
    p1config.readSeqData.edge = XSPI_DATA_EDGE_MODE_SDR;
    p1config.readSeqMbDummyCnt = 0;
    p1config.readSeqMbEn = false;
    p1config.cacheRandomReadEn = false;

    switch(handler->init.line_num){
        /*
        case 2:
            printf("read x2\n");
            p1config.readSeqCmd.value = SPI_FLASH_FastReadDual;
            p1config.readSeqData.ios = XSPI_NUMBER_OF_IOS_2;
            p1config.readSeqDummyCnt = 8;
        break;
        */
        case 4:
            printf("read x4\n");
            p1config.readSeqCmd.value = SPI_FLASH_FastReadQuad;
            p1config.readSeqData.ios = XSPI_NUMBER_OF_IOS_4;
            p1config.readSeqDummyCnt = 8;
        break;

        case 8:
            printf("read x8\n");
            p1config.readSeqCmd.value = SPI_FLASH_FastReadOctal;
            p1config.readSeqData.ios = XSPI_NUMBER_OF_IOS_8;
            p1config.readSeqDummyCnt = 8;
        break;

        case 1:
        case 2:
        default:
            printf("read x1\n");
            p1config.readSeqCmd.value = SPI_FLASH_ReadData;
            p1config.readSeqData.ios = XSPI_NUMBER_OF_IOS_1;
            p1config.readSeqDummyCnt = 0;
        break;

    }
    handler->drv->setReadSeqP1Config(handler->pD ,&p1config);
}

#endif
static void nor_basic_config(XSPI_HandleTypeDef *handler){
    XSPI_GlobalCommandParameters g_param = {0};
    XSPI_StatSeqP1Config stat_config = {0};

    g_param.seqType = XSPI_SEQUENCE_TYPE_P1_SPI_NOR;
    g_param.dataPerAddress = XSPI_DATA_PER_ADDRESS_1B;
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

    stat_config.statSeqData.edge = XSPI_DATA_EDGE_MODE_SDR;
    stat_config.statSeqData.ios = XSPI_NUMBER_OF_IOS_1;
    stat_config.statSeqAddrEdge = XSPI_ADDR_EDGE_MODE_SDR;
    stat_config.statSeqAddrIos = XSPI_NUMBER_OF_IOS_1;
    stat_config.statSeqAddrCnt = XSPI_STAT_SEQ_ADDR_COUNT_1_ADDR_BYTE;
    stat_config.statSeqCmdExtEn = false;
    stat_config.statSeqCmdEdge = XSPI_CMD_EDGE_MODE_SDR;
    stat_config.statSeqCmdIos = XSPI_NUMBER_OF_IOS_1;
    stat_config.statSeqErsFailAddrEn = false;
    stat_config.statSeqErsFailDummyCnt = 0;
    stat_config.statSeqProgFailAddrEn = false;
    stat_config.statSeqProgFailDummyCnt = 0;
    stat_config.statSeqDevRdyAddrEn = false;
    stat_config.statSeqDevRdyDummyCnt = 0;
    stat_config.statSeqProgFailCmdVal = 0x05;
    stat_config.statSeqErsFailCmdVal = 0x05;
    stat_config.statSeqDevRdyCmdVal = 0x05;
    stat_config.statSeqProgFailCmdExtVal = 0x00;
    stat_config.statSeqErsFailCmdExtVal = 0x00;
    stat_config.statSeqDevRdyCmdExtVal = 0x00;
    handler->drv->setStatSeqP1Config(handler->pD ,&stat_config);

}

static void nor_program_config(XSPI_HandleTypeDef *handler){
  XSPI_WelSeqConfig wel_config = {0};
  XSPI_ProgramSeqP1Config p1config = {0};

  wel_config.welSeqCmd.edge = XSPI_CMD_EDGE_MODE_SDR;
  wel_config.welSeqCmd.ios = XSPI_NUMBER_OF_IOS_1;
  wel_config.welSeqCmd.value = SPI_FLASH_WriteEnable;
  wel_config.welSeqCmdExt.enable = false;
  handler->drv->setWelSeqConfig(handler->pD ,&wel_config);

  p1config.progSeqCmd.edge = XSPI_CMD_EDGE_MODE_SDR;
  p1config.progSeqCmd.ios =XSPI_NUMBER_OF_IOS_1;
  p1config.progSeqCmdExt.enable = false;
  p1config.progSeqAddr.edge = XSPI_ADDR_EDGE_MODE_SDR;
  p1config.progSeqAddr.ios = XSPI_NUMBER_OF_IOS_1;
  p1config.progSeqAddr.count = 3;
  p1config.progSeqData.edge = XSPI_DATA_EDGE_MODE_SDR;

  switch(handler->init.line_num){
      case 4:
          printf("write x4\n");
          p1config.progSeqCmd.value = SPI_FLASH_PageProgramQuad;
          p1config.progSeqData.ios = XSPI_NUMBER_OF_IOS_4;
      break;

      case 8:
          printf("write x8\n");
          p1config.progSeqCmd.value = SPI_FLASH_PageProgramOctal;
          p1config.progSeqData.ios = XSPI_NUMBER_OF_IOS_8;
      break;

      case 1:
      case 2:
      default:
          //printf("write x1\n");
          p1config.progSeqCmd.value = SPI_FLASH_PageProgram;
          p1config.progSeqData.ios = XSPI_NUMBER_OF_IOS_1;
      break;

  }
  handler->drv->setProgramSeqP1Config(handler->pD ,&p1config);
}

static void nor_read_config(XSPI_HandleTypeDef *handler){
    XSPI_ReadSeqP1Config p1config;
    
    p1config.readSeqCmd.edge = XSPI_CMD_EDGE_MODE_SDR;
    p1config.readSeqCmd.ios = XSPI_NUMBER_OF_IOS_1;
    p1config.readSeqCmdExt.enable = false;
    p1config.readSeqCmdExt.value = 0;
    p1config.readSeqAddr.edge = XSPI_ADDR_EDGE_MODE_SDR;
    p1config.readSeqAddr.ios = XSPI_NUMBER_OF_IOS_1;
    p1config.readSeqAddr.count = 3;
    p1config.readSeqData.edge = XSPI_DATA_EDGE_MODE_SDR;
    p1config.readSeqMbDummyCnt = 0;
    p1config.readSeqMbEn = false;
    p1config.cacheRandomReadEn = false;

    switch(handler->init.line_num){
        case 4:
            printf("read x4\n");
            p1config.readSeqCmd.value = SPI_FLASH_FastReadQuad;
            p1config.readSeqData.ios = XSPI_NUMBER_OF_IOS_4;
            p1config.readSeqDummyCnt = 8;
        break;

        case 8:
            printf("read x8\n");
            p1config.readSeqCmd.value = SPI_FLASH_FastReadOctal;
            p1config.readSeqData.ios = XSPI_NUMBER_OF_IOS_8;
            p1config.readSeqDummyCnt = 8;
        break;

        case 1:
        case 2:
        default:
            //printf("read x1\n");
            p1config.readSeqCmd.value = SPI_FLASH_ReadData;
            p1config.readSeqData.ios = XSPI_NUMBER_OF_IOS_1;
            p1config.readSeqDummyCnt = 0;
        break;

    }
    handler->drv->setReadSeqP1Config(handler->pD ,&p1config);

}

static void wait_busy(XSPI_HandleTypeDef *handler) {
  XSPI_StigCommand *cmd;
  uint8_t sr = 0;
  cmd        = construct_stig_cmd(false, 1, false, NULL, 1,
                           XSPI_P10_INSTR_READ_MEMORY_REGISTER,
                           SPI_FLASH_ReadStatusReg, 0, 0, 0);
  if (cmd == NULL) {
    printf("construct_stig_cmd failed\n");
  }

  do {
    cdns_xspi_send_stig_command(handler, cmd);
    sr = (uint8_t)(readl(handler->reg_base + 0x44) >> 16);
    #ifndef CONFIG_COMPILE_RTL
    udelay(10);
    #endif  
  } while (sr & 0x01);
}

static int get_id(XSPI_HandleTypeDef *handler) {
  XSPI_StigCommand *cmd;
  uint8_t buf[8];
  cmd = construct_stig_cmd(false, 1, false, buf, BYTES_PER_XSPI_DMA_OP,
                           XSPI_P10_INSTR_READ_JEDEC_ID,
                           SPI_FLASH_JedecDeviceID, 0, 0, 0);
  if (cmd == NULL) {
    printf("construct_stig_cmd failed\n");
  }
  printf("get spi flash id...");
  cdns_xspi_send_stig_command(handler, cmd);
  printf("Manufacturer ID = 0x%x,", buf[0]);
  printf("Device ID = 0x%x%x\n", buf[1], buf[2]);
  wait_busy(handler);
  return 0;
}

static void nor_reset(XSPI_HandleTypeDef *handler) {
  // 0x66 0x99
  XSPI_StigCommand *cmd;
  printf("reset spi flash...");
  cmd =
      construct_stig_cmd(false, 1, false, NULL, 0, XSPI_P10_INSTR_RESET_ENABLE,
                         SPI_FLASH_ENABLE_POR, 0, 0, 0);
  if (cmd == NULL) {
    printf("construct_stig_cmd failed\n");
  }
  cdns_xspi_send_stig_command(handler, cmd);

  cmd = construct_stig_cmd(false, 1, false, NULL, 0, XSPI_P10_INSTR_SOFT_RESET,
                           SPI_FLASH_POR, 0, 0, 0);
  if (cmd == NULL) {
    printf("construct_stig_cmd failed\n");
  }
  cdns_xspi_send_stig_command(handler, cmd);
  printf("ok\n");
  wait_busy(handler);
}

#if 0

static void nor_wren(XSPI_HandleTypeDef *handler) {
  XSPI_StigCommand *cmd;

  // Sending Write Enable.
  cmd = construct_stig_cmd(false, 1, false, NULL, 0,
                             XSPI_P10_INSTR_WRITE_ENABLE_LATCH,
                             SPI_FLASH_WriteEnable, 0, 0, 0);
  cdns_xspi_send_stig_command(handler, cmd);
  wait_busy(handler);
}

static void nor_write_status(XSPI_HandleTypeDef *handler, uint8_t st_reg, uint8_t sr)
{
  XSPI_StigCommand* cmd;

  cmd = construct_stig_cmd(false, 1, true, NULL, 0, XSPI_P10_INSTR_WRITE_MEMORY_REGISTER, st_reg, 0, 0, 0);
  cmd->instructionChain->profile10Instr.dataNoOfBytes = 1;
  cmd->instructionChain->profile10Instr.data[0] = sr;
  cdns_xspi_send_stig_command(handler, cmd);
  #ifndef CONFIG_COMPILE_RTL
  udelay(10);
  #endif
}

static uint8_t nor_read_status(XSPI_HandleTypeDef *handler, uint8_t st_reg)
{
  XSPI_StigCommand* cmd;
  uint8_t sr = 0x0;

  cmd = construct_stig_cmd(false, 1, false, NULL, 1, XSPI_P10_INSTR_READ_MEMORY_REGISTER, st_reg, 0, 0, 0);
  cdns_xspi_send_stig_command(handler, cmd);
  sr = (uint8_t)(readl(handler->reg_base + 0x44) >> 16);
  printf("status register: 0x%x\n", sr);

  return sr;
}

static void nor_read_sfdp(XSPI_HandleTypeDef *handler)
{
  XSPI_StigCommand* cmd;
  uint8_t buf[256] = {0x0};

  cmd = construct_stig_cmd(false, 1, false, buf, sizeof(buf), XSPI_P10_INSTR_READ_MEMORY_REGISTER, 0x5a, 8, 0, 3);
  cdns_xspi_send_stig_command(handler, cmd);

  printf("SFDP:");
  for (int i = 0; i < 256; i++) {
    if (!(i % 16))
      printf("\n");
    printf("0x%02x ", buf[i]);
  }
  printf("\n");
}
#endif

static void nor_enable_quad_op(XSPI_HandleTypeDef *handler) {
}

static void nor_unprotect(XSPI_HandleTypeDef *handler) {
  XSPI_StigCommand* cmd;
  uint8_t sr = 0x0;
  cmd = construct_stig_cmd(false, 1, false, NULL, 1, XSPI_P10_INSTR_READ_MEMORY_REGISTER, SPI_FLASH_ReadStatusReg, 0, 0, 0);
  cdns_xspi_send_stig_command(handler, cmd);
  sr = (uint8_t)(readl(handler->reg_base + 0x44) >> 16);
  printf("status register before unprotect: 0x%x\n", sr);

  XSPI_SetWriteProtect(handler->pD, false);

  //WEL
  cmd = construct_stig_cmd(false, 1, false, NULL, 0, XSPI_P10_INSTR_WRITE_ENABLE_LATCH, SPI_FLASH_WriteEnable, 0, 0, 0);
  cdns_xspi_send_stig_command(handler, cmd);

  cmd = construct_stig_cmd(false, 1, true, NULL, 0, XSPI_P10_INSTR_WRITE_MEMORY_REGISTER, SPI_FLASH_WriteStatusReg, 0, 0, 0);
  cmd->instructionChain->profile10Instr.dataNoOfBytes = 1;
  cmd->instructionChain->profile10Instr.data[0] = sr;
  cdns_xspi_send_stig_command(handler, cmd);
  #ifndef CONFIG_COMPILE_RTL
  udelay(10);
  #endif

  //read
  cmd = construct_stig_cmd(false, 1, false, NULL, 1, XSPI_P10_INSTR_READ_MEMORY_REGISTER, SPI_FLASH_ReadStatusReg, 0, 0, 0);
  cdns_xspi_send_stig_command(handler, cmd);
  sr = (uint8_t)(readl(handler->reg_base + 0x44) >> 16);
  printf("status register after unprotect: 0x%x\n", sr);
}

static XSPI_HandleTypeDef *nor_init(XSPI_InitTypeDef *init) {
  XSPI_HandleTypeDef *handler;

  printf("%s:%s:%d\n\nStart init...\n", __FILE__, __func__, __LINE__);

  handler = itcs_xspi_init(init);
  if (handler == NULL) {
    printf("XSPI init failed, handler is NULL\n");
    return handler;
  }
  nor_basic_config(handler);
  nor_program_config(handler);
  nor_read_config(handler);
  nor_reset(handler);
  get_id(handler);

  if (init->line_num == 4)
    nor_enable_quad_op(handler);

  return handler;
}

static uint32_t nor_read(XSPI_HandleTypeDef *handler, uint8_t *pBuffer, uint32_t addr,
                  uint32_t byte_num) {
  uint8_t *buf    = pBuffer;
  int padding_num = 0;
  if (byte_num % BYTES_PER_XSPI_DMA_OP) {
    buf         = malloc(byte_num - (byte_num % BYTES_PER_XSPI_DMA_OP) +
                 BYTES_PER_XSPI_DMA_OP);
    padding_num = BYTES_PER_XSPI_DMA_OP - (byte_num % BYTES_PER_XSPI_DMA_OP);
  }

  switch (handler->work_mode) {
  case CDNS_XSPI_MODE_DIRECT: {
    XSPI_DirectCmd directCmd;
    directCmd.direction    = XSPI_DATA_TRANS_DIR_READ;
    directCmd.sysMemPtr    = (uintptr_t)buf;
    directCmd.transferSize = byte_num + padding_num;
    directCmd.transferAddr = addr;
    //nor_read_config_direct_acmd(handler);
    printf("work in DIRECT mode\n");
    cdns_xspi_send_direct_command(handler, &directCmd);
    wait_busy(handler);
    if (padding_num)
      memcpy(pBuffer, buf, byte_num);
  } break;

  case CDNS_XSPI_MODE_STIG: {
    XSPI_StigCommand *cmd;
    if(handler->init.ddr){
        printf("stig read in dtr mode\n");
        cmd = construct_stig_cmd(true, 4, false, buf, byte_num + padding_num,
                             XSPI_P10_INSTR_READ_ARRAY, SPI_FLASH_DtrReadDataQuad, 6,
                             addr, 3);
    }else{
        switch(handler->init.line_num){
            case 2:
                printf("read x2\n");
                cmd = construct_stig_cmd(false, 2, false, buf, byte_num + padding_num,
                            XSPI_P10_INSTR_READ_ARRAY, SPI_FLASH_FastReadDual, 8,
                            addr, 3);
            break;

            case 4:
                printf("read x4\n");
                cmd = construct_stig_cmd(false, 4, false, buf, byte_num + padding_num,
                            XSPI_P10_INSTR_READ_ARRAY, SPI_FLASH_FastReadQuad, 8,
                            addr, 3);
            break;

            case 8:
                printf("read x8\n");
                cmd = construct_stig_cmd(false, 8, false, buf, byte_num + padding_num,
                            XSPI_P10_INSTR_READ_ARRAY, SPI_FLASH_FastReadOctal, 8,
                            addr, 3);
            break;

            case 1:
            default:
                printf("read x1\n");
                cmd = construct_stig_cmd(false, 1, false, buf, byte_num + padding_num,
                            XSPI_P10_INSTR_READ_ARRAY, SPI_FLASH_ReadData, 0,
                            addr, 3);
            break;
        }
    }
    printf("work in STIG mode\n");
    cdns_xspi_send_stig_command(handler, cmd);
    wait_busy(handler);

    if (padding_num)
      memcpy(pBuffer, buf, byte_num);
  } break;

  case CDNS_XSPI_MODE_ACMD_PIO: {
    XSPI_PioCommand pioCmd;
    pioCmd.params.bankSelect         = 0U;
    pioCmd.params.cmdCount           = byte_num + padding_num;
    pioCmd.params.cmdType            = XSPI_ACMD_COMMAND_TYPE_READ_SEQ;
    pioCmd.params.xSpiAddr           = addr;
    pioCmd.params.sysMemPtr          = (uintptr_t)buf;
    pioCmd.params.dmaSelect          = XSPI_ACMD_DMA_SELECT_MASTER;
    pioCmd.params.disXipMb           = false;
    pioCmd.params.enXipMb            = false;
    pioCmd.params.raiseCmdCompleteCb = false;
    //nor_read_config_direct_acmd(handler);
    printf("work in PIO mode\n");
    cdns_xspi_send_acmd_pio_command(handler, &pioCmd);
    wait_busy(handler);
    if (padding_num)
      memcpy(pBuffer, buf, byte_num);
  } break;

  case CDNS_XSPI_MODE_ACMD_CMDA: {
    XSPI_CdmaCommand cdmaCmd;
    cdmaCmd.params.bankSelect         = 0U;
    cdmaCmd.params.cmdCount           = byte_num + padding_num;
    cdmaCmd.params.cmdType            = XSPI_ACMD_COMMAND_TYPE_READ_SEQ;
    cdmaCmd.params.xSpiAddr           = addr;
    cdmaCmd.params.sysMemPtr          = (uintptr_t)buf;
    cdmaCmd.params.dmaSelect          = XSPI_ACMD_DMA_SELECT_MASTER;
    cdmaCmd.params.disXipMb           = false;
    cdmaCmd.params.enXipMb            = false;
    cdmaCmd.params.raiseCmdCompleteCb = false;
    cdmaCmd.ignoreXSpiAddr            = false;
    cdmaCmd.ignoreSysMemPtr           = false;
    printf("disable irq\n");
    writel(0x0, (handler->reg_base + 0x0114));
    //nor_read_config_direct_acmd(handler);
    printf("work in CDMA mode\n");
    cdns_xspi_send_acmd_cdma_command(handler, &cdmaCmd);
    wait_busy(handler);
    if (padding_num)
      memcpy(pBuffer, buf, byte_num);
  }

  break;

  default:
    break;
  }

  free(buf);
  return byte_num;
}

static bool nor_erase(XSPI_HandleTypeDef *handler, SPI_FLASH_ERASE_TYPE type,
               uint32_t addr) {
  if (type == SPI_FLASH_ERASE_FULL_CHIP) {

  } else if (type == SPI_FLASH_ERASE_SECTOR) {
    XSPI_StigCommand *cmd;
    if (SPI_FLASH_SECTOR_SIZE == 0) {
      printf("spi flash csector erase format does not support.\n");
      return false;
    }

    // nor flash needed
    addr *= SPI_FLASH_SECTOR_SIZE;
    // Sending Write Enable.
    cmd = construct_stig_cmd(false, 1, false, NULL, 0,
                             XSPI_P10_INSTR_WRITE_ENABLE_LATCH,
                             SPI_FLASH_WriteEnable, 0, 0, 0);
    if (cmd == NULL) {
      printf("construct_stig_cmd failed\n");
    }
    cdns_xspi_send_stig_command(handler, cmd);
    wait_busy(handler);

    // Sending Erase Command.
    cmd = construct_stig_cmd(false, 1, false, NULL, 0,
                             XSPI_P10_INSTR_ERASE_SECTOR, SPI_FLASH_SectorErase,
                             0, addr, 3);
    if (cmd == NULL) {
      printf("construct_stig_cmd failed\n");
    }
    cdns_xspi_send_stig_command(handler, cmd);
    wait_busy(handler);

  } else {
    printf("erase type is not suport yet!\n");
    return false;
  }

  return true;
}

static int nor_page_program(XSPI_HandleTypeDef *handler, uint8_t *pBuffer, uint32_t addr, uint32_t byte_num)
{
  XSPI_StigCommand *cmd;
  // Sending Write Enable.
  cmd = construct_stig_cmd(false, 1, false, NULL, 0,
                             XSPI_P10_INSTR_WRITE_ENABLE_LATCH,
                             SPI_FLASH_WriteEnable, 0, 0, 0);
  cdns_xspi_send_stig_command(handler, cmd);
  wait_busy(handler);
  switch (handler->work_mode) {
  case CDNS_XSPI_MODE_DIRECT: {
    XSPI_DirectCmd directCmd;
    directCmd.direction    = XSPI_DATA_TRANS_DIR_WRITE;
    directCmd.sysMemPtr    = (uintptr_t)pBuffer;
    directCmd.transferSize = byte_num;
    directCmd.transferAddr = addr;
    //nor_program_config_direct_acmd(handler);
    DEBUG_XSPI_LOG("work in DIRECT mode\n");
    /*
    DEBUG_XSPI_LOG("pbuffer=%p, addr=0x%x, byte_num=%d\n",pBuffer, addr, byte_num);
    DEBUG_XSPI_LOG("tx data:\n");
    for(int i = 0; i < byte_num; i++) {
        DEBUG_XSPI_LOG("%x ", pBuffer[i]);
        if(i % 16 == 15)
            DEBUG_XSPI_LOG("\n");
    }
    */
    cdns_xspi_send_direct_command(handler, &directCmd);
    wait_busy(handler);
  } break;

  case CDNS_XSPI_MODE_STIG: {    
    printf("work in STIG mode\n");
    switch(handler->init.line_num){
        case 2:
        printf("write x2 is not support now, using write x1\n");
        cmd = construct_stig_cmd(false, 1, true, pBuffer, byte_num,
                             XSPI_P10_INSTR_WRITE_ARRAY, SPI_FLASH_PageProgram,
                             0, addr, 3);
        break;
        case 4:
        printf("write x4\n");
        cmd = construct_stig_cmd(false, 4, true, pBuffer, byte_num,
                             XSPI_P10_INSTR_WRITE_ARRAY, SPI_FLASH_PageProgramQuad,
                             0, addr, 3);
        break;
        case 8:
        printf("write x8\n");
        cmd = construct_stig_cmd(false, 8, true, pBuffer, byte_num,
                             XSPI_P10_INSTR_WRITE_ARRAY, SPI_FLASH_PageProgramOctal,
                             0, addr, 3);
        break;
        case 1:
        default:
        printf("write x1\n");
        cmd = construct_stig_cmd(false, 1, true, pBuffer, byte_num,
                             XSPI_P10_INSTR_WRITE_ARRAY, SPI_FLASH_PageProgram,
                             0, addr, 3);
        break;
    }
    cdns_xspi_send_stig_command(handler, cmd);
    wait_busy(handler);

  } break;

  case CDNS_XSPI_MODE_ACMD_PIO: {
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
    //nor_program_config_direct_acmd(handler);
    printf("work in PIO mode\n");
    cdns_xspi_send_acmd_pio_command(handler, &pioCmd);
    wait_busy(handler);
  } break;

  case CDNS_XSPI_MODE_ACMD_CMDA: {
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
    //nor_program_config_direct_acmd(handler);
    printf("work in CDMA mode\n");
    cdns_xspi_send_acmd_cdma_command(handler, &cdmaCmd);
    wait_busy(handler);
  }

  break;

  default:
    break;
  }
  return byte_num;
}


#if CONFIG_COMPILE_RTL
static uint32_t nor_write(XSPI_HandleTypeDef *handler, uint8_t *pBuffer, uint32_t addr,
                   uint32_t byte_num) {
  uint8_t flash_buf[SPI_FLASH_PAGE_SIZE * 2];
  
  memset(flash_buf, 0xff, sizeof(flash_buf));
  nor_erase(handler, SPI_FLASH_ERASE_SECTOR, addr / SPI_FLASH_SECTOR_SIZE);

  memcpy(flash_buf, pBuffer, byte_num < sizeof(flash_buf) ? byte_num : sizeof(flash_buf));
  itcs_dcache_clean();

  if (handler->work_mode == CDNS_XSPI_MODE_DIRECT) {
    nor_page_program(handler, flash_buf,  addr, SPI_FLASH_PAGE_SIZE * 2);
  } else {
    nor_page_program(handler, flash_buf,  addr, SPI_FLASH_PAGE_SIZE);
    nor_page_program(handler, flash_buf + SPI_FLASH_PAGE_SIZE,  addr + SPI_FLASH_PAGE_SIZE, SPI_FLASH_PAGE_SIZE);
  }

  return byte_num;
}
#else

static void write_noCheck(XSPI_HandleTypeDef *handler, uint8_t *pBuffer,
                          uint32_t addr, uint32_t byte_num) {
  uint32_t pageremain;
  pageremain =
      SPI_FLASH_PAGE_SIZE - addr % SPI_FLASH_PAGE_SIZE; //单页剩余的字节数
  if (byte_num <= pageremain) { //不大于SPI_FLASH_PAGE_SIZE个字节
    pageremain = byte_num;
  }
  while (1) {
    nor_page_program(handler, pBuffer, addr, pageremain);
    if (byte_num == pageremain) { //写入结束了
      break;
    } else {
      pBuffer += pageremain;
      addr += pageremain;

      byte_num -= pageremain; //减去已经写入了的字节数
      if (byte_num >
          SPI_FLASH_PAGE_SIZE) { //一次可以写入SPI_FLASH_PAGE_SIZE个字节
        pageremain = SPI_FLASH_PAGE_SIZE;
      } else {
        pageremain = byte_num; //不够256个字节了
      }
    }
  }
}


static uint32_t nor_write(XSPI_HandleTypeDef *handler, uint8_t *pBuffer, uint32_t addr,
                   uint32_t byte_num) {
  uint32_t secpos;
  uint16_t secoff;
  uint16_t secremain;
  uint16_t i;
  uint8_t *flash_buf = (uint8_t *)malloc(SPI_FLASH_SECTOR_SIZE);
  secpos             = addr / SPI_FLASH_SECTOR_SIZE; //起始扇区地址
  secoff             = addr % SPI_FLASH_SECTOR_SIZE; //在扇区内的偏移
  secremain = SPI_FLASH_SECTOR_SIZE - secoff;        //扇区剩余空间大小
  if (byte_num <= secremain) { //不大于SPI_FLASH_SECTOR_SIZE个字节
    secremain = byte_num;
  }
  while (1) {
    nor_read(handler, flash_buf, secpos * SPI_FLASH_SECTOR_SIZE,
             SPI_FLASH_SECTOR_SIZE);       //读出整个扇区的内容
    for (i = 0; i < secremain; i++) {      //校验数据
      if (flash_buf[secoff + i] != 0xFF) { //需要擦除
        break;
      }
    }
    if (i < secremain) {                                  //需要擦除
      nor_erase(handler, SPI_FLASH_ERASE_SECTOR, secpos); //擦除这个扇区
    }
    
    for (i = 0; i < secremain; i++) {                   //复制
        flash_buf[i + secoff] = pBuffer[i];
    }

    if(handler->work_mode == CDNS_XSPI_MODE_DIRECT){
        nor_page_program(handler, flash_buf,  secpos * SPI_FLASH_SECTOR_SIZE, SPI_FLASH_SECTOR_SIZE);
    }else{
        write_noCheck(handler, flash_buf, secpos * SPI_FLASH_SECTOR_SIZE, SPI_FLASH_SECTOR_SIZE);
    }
    
    if (byte_num == secremain) { //写入结束了
      break;
    } else {                                  //写入未结束
      secpos++;                               //扇区地址增1
      secoff = 0;                             //偏移位置为0
      pBuffer += secremain;                   //指针偏移
      addr += secremain;                      //写地址偏移
      byte_num -= secremain;                  //字节数递减
      if (byte_num > SPI_FLASH_SECTOR_SIZE) { //下一个扇区还是写不完
        secremain = SPI_FLASH_SECTOR_SIZE;
      } else { //下一个扇区可以写完了
        secremain = byte_num;
      }
    }
  }
    
  free(flash_buf);
  return byte_num;
}
#endif

static bool nor_write_protect(XSPI_HandleTypeDef *handler, bool enable) {
  
  XSPI_SetWriteProtect(handler->pD, enable);
  return true;
}

static uint32_t nor_get_alignment(XSPI_HandleTypeDef *handler) {
  return SPI_FLASH_PAGE_SIZE;
}

struct xspi_flash_operations f_ops_gd_nor = {
    .init          = nor_init,
    .read          = nor_read,
    .write         = nor_write,
    .erase         = nor_erase,
    .get_alignment = nor_get_alignment,
    .write_protect = nor_write_protect,
    .reset         = nor_reset};

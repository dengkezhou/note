#include "xspi_flash.h"
#include <malloc.h>
#include <spi_flash.h>
#define SYS_CLK_START_FREQ_kHZ  200000
#define XSPI_CLK_START_FREQ_kHZ 50000
#define INIT_RB_VALID_TIME      0x00000000
#if defined(CONFIG_COMPILE_RTL) || defined(CONFIG_COMPILE_ASIC)
#define INIT_PHY_DQ_TIMING_REG      0x80000101
#define INIT_PHY_DQS_TIMING_REG     0x00300404
#define INIT_PHY_GATE_LPBK_CTRL_REG 0x00180030
#define INIT_PHY_DLL_SLAVE_CTRL_REG 0x0000357f
#else
#define INIT_PHY_DQ_TIMING_REG      0x80000102 // phy reg 0x2000
#define INIT_PHY_DQS_TIMING_REG     0x00300404 // phy reg 0x2004
#define INIT_PHY_GATE_LPBK_CTRL_REG 0x00200030 // phy reg 0x2008
#define INIT_PHY_DLL_SLAVE_CTRL_REG 0x00003f00 // phy reg 0x2010
#endif

#define INIT_PHY_DLL_MASTER_CTRL_REG    0x00800004 // phy reg 0x200c, asic only
#define INIT_DQS_LAST_DATA_DROP_EN      0
#define INIT_SDR_EDGE_ACTIVE            0
#define INIT_WP_ENABLE                  0
#define INIT_RST_DQ3_ENABLE             0
#define INIT_SW_CTRLED_HW_RST_OPTION    0
#define DISCOVERY_INHIBIT               1
#define DISCOVERY_NUM_LINES             0
#define DISCOVERY_BANK                  0
#define DISCOVERY_CMD_TYPE              0
#define DISCOVERY_EXTOP_EN              0
#define DISCOVERY_EXTOP_VAL             0
#define DISCOVERY_DUMMY_CNT             0
#define DISCOVERY_ABNUM                 0
#define DISCOVERY_SEQ_CRC_EN            0
#define DISCOVERY_SEQ_CRC_VARIANT       0
#define DISCOVERY_SEQ_CRC_OE            0
#define DISCOVERY_SEQ_CRC_CHUNK_SIZE    0
#define DISCOVERY_SEQ_CRC_UAL_CHUNK_EN  0
#define DISCOVERY_SEQ_CRC_UAL_CHUNK_CHK 0
#define BOOT_EN                         0

#define sd_printf                       printf
#define sv_malloc                       malloc
#define sv_free                         free
#define IOWR_32(register_address, data) writel(data, register_address)
#define IORD_32(register_address)       readl(register_address)
#define sd_delay                        udelay

#define QSPI_SDMA_BASE 0x38000000 // b2m3 axi slave addr
#define OSPI_SDMA_BASE 0x30000000 // b2m0 axi slave addr

#define OSPI_REG_BASE 0xC5000000
#define QSPI_REG_BASE 0xC5300000

// GPIO READ
#define OSPI_TB_GPIO_SEL_REG                     (OSPI_REG_BASE + 0x8000)
#define OSPI_TB_GPIO_BOOT_REG                    (OSPI_REG_BASE + 0x80a0)
#define OSPI_TB_GPIO_DISCOVERY_REG               (OSPI_REG_BASE + 0x80a4)
#define OSPI_TB_GPIO_INIT_RB_REG                 (OSPI_REG_BASE + 0x80a8)
#define OSPI_TB_GPIO_INIT_PHY_DQ_REG             (OSPI_REG_BASE + 0x80ac)
#define OSPI_TB_GPIO_INIT_PHY_DQS_REG            (OSPI_REG_BASE + 0x80b0)
#define OSPI_TB_GPIO_INIT_PHY_GATE_LPBK_REG      (OSPI_REG_BASE + 0x80b4)
#define OSPI_TB_GPIO_INIT_PHY_DLL_MASTER_REG     (OSPI_REG_BASE + 0x80b8)
#define OSPI_TB_GPIO_INIT_PHY_DLL_SLAVE_REG      (OSPI_REG_BASE + 0x80bc)
#define OSPI_TB_GPIO_INIT_REG                    (OSPI_REG_BASE + 0x80c0)
#define OSPI_TB_GPIO_CTRL_REG                    (OSPI_REG_BASE + 0x80c4)


#define QSPI_TB_GPIO_BOOT_REG                    (QSPI_REG_BASE + 0x8000)
#define QSPI_TB_GPIO_DISCOVERY_REG               (QSPI_REG_BASE + 0x8004)
#define QSPI_TB_GPIO_INIT_RB_REG                 (QSPI_REG_BASE + 0x8008)
#define QSPI_TB_GPIO_INIT_PHY_DQ_REG             (QSPI_REG_BASE + 0x800c)
#define QSPI_TB_GPIO_INIT_PHY_DQS_REG            (QSPI_REG_BASE + 0x8010)
#define QSPI_TB_GPIO_INIT_PHY_GATE_LPBK_REG      (QSPI_REG_BASE + 0x8014)
#define QSPI_TB_GPIO_INIT_PHY_DLL_MASTER_REG     (QSPI_REG_BASE + 0x8018)
#define QSPI_TB_GPIO_INIT_PHY_DLL_SLAVE_REG      (QSPI_REG_BASE + 0x801c)
#define QSPI_TB_GPIO_INIT_REG                    (QSPI_REG_BASE + 0x8020)
#define QSPI_TB_GPIO_CTRL_REG                    (QSPI_REG_BASE + 0x8024)

#define TB_GPIO_INIT_COMP                   8    /* XSPI OUTPUT: init_comp */
#define TB_GPIO_INIT_FAIL                   12   /* XSPI OUTPUT: init_fail */
#define TB_GPIO_CTRL_BUSY                   0    /* XSPI OUTPUT: ctrl_busy */
#define TB_GPIO_BOOT_EN                     0    /* XSPI INPUT: boot_en */
#define TB_GPIO_BOOT_COMP                   4    /* XSPI OUTPUT: boot_comp */
#define TB_GPIO_BOOT_ERROR                  8    /* XSPI OUTPUT: boot_error */


#define OSPI_R_CMD_STATUS_PTR (OSPI_REG_BASE + 0x0040)
#define QSPI_R_CMD_STATUS_PTR (QSPI_REG_BASE + 0x0040)

#define F_THRD_STATUS_SEL     0

#define OSPI_R_CMD_STATUS (OSPI_REG_BASE + 0x0044)
#define QSPI_R_CMD_STATUS (QSPI_REG_BASE + 0x0044)
#define F_CMD_STATUS      0

#define OSPI_R_CTRL_STATUS (OSPI_REG_BASE + 0x0100)
#define QSPI_R_CTRL_STATUS (QSPI_REG_BASE + 0x0100)

#define F_INIT_COMP        16
#define F_INIT_FAIL        8
#define F_CTRL_BUSY        7
#define F_DISCOVERY_BUSY   6
#define F_GCMD_ENG_MC_BUSY 4
#define F_GCMD_ENG_BUSY    3
#define F_ACMD_ENG_BUSY    2
#define F_MDMA_BUSY        1
#define F_SDMA_BUSY        0

#define SPI_FLASH_WriteReg                  0x81
#define XSPI_R_INTR_STATUS                  (handler->reg_base + 0x0110)
#define F_DIR_DEV_ERR                       28
#define F_DIR_ECC_CORR_ERR                  27
#define F_DIR_CMD_ERR                       26
#define F_DIR_DQS_ERR                       25
#define F_DIR_CRC_ERR                       24
#define F_STIG_DONE                         23
#define F_SDMA_ERR                          22
#define F_SDMA_TRIGG                        21
#define F_CMD_IGNORED                       20
#define F_DDMA_TERR                         18
#define F_CDMA_TERR                         17
#define F_CTRL_IDLE                         16

#define INIT_PARAM                                           \
  {                                                                             \
    true, 0, NULL, QSPI, SPI_DATASIZE_8BIT, 0, 1000000, HW_SPI_CS_MODE, 0, 1,   \
        SPI_NOR_FLASH, false, false                                             \
  }

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

  if (ddr == false) {
    stigInstr.profile10Instr.instrOpcodePhase.edge = XSPI_CMD_EDGE_MODE_SDR;
    stigInstr.profile10Instr.instrAddrPhase.edge   = XSPI_ADDR_EDGE_MODE_SDR;
    dataSeqInstr.instrDataPhase.edge               = XSPI_DATA_EDGE_MODE_SDR;
  } else {
    stigInstr.profile10Instr.instrOpcodePhase.edge = XSPI_CMD_EDGE_MODE_DDR;
    stigInstr.profile10Instr.instrAddrPhase.edge   = XSPI_ADDR_EDGE_MODE_DDR;
    dataSeqInstr.instrDataPhase.edge               = XSPI_DATA_EDGE_MODE_DDR;
  }
  stigInstr.profile10Instr.instrOpcodePhase.ios = XSPI_NUMBER_OF_IOS_1;
  switch (lines) {
  case 1:
    stigInstr.profile10Instr.instrAddrPhase.ios   = XSPI_NUMBER_OF_IOS_1;
    dataSeqInstr.instrDataPhase.ios               = XSPI_NUMBER_OF_IOS_1;
    break;
  case 2:
    stigInstr.profile10Instr.instrAddrPhase.ios   = XSPI_NUMBER_OF_IOS_2;
    dataSeqInstr.instrDataPhase.ios               = XSPI_NUMBER_OF_IOS_2;
    break;
  case 4:
    stigInstr.profile10Instr.instrAddrPhase.ios   = XSPI_NUMBER_OF_IOS_4;
    dataSeqInstr.instrDataPhase.ios               = XSPI_NUMBER_OF_IOS_4;
    break;
  case 8:
    stigInstr.profile10Instr.instrAddrPhase.ios   = XSPI_NUMBER_OF_IOS_8;
    dataSeqInstr.instrDataPhase.ios               = XSPI_NUMBER_OF_IOS_8;
    break;
  default:
    printf("Invalid line number\n");
    return NULL;
    break;
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

static void xspi_boot_assert_reset(int port){
    printf("assert %s reset\r\n", (port == 0) ? "OSPI" : "QSPI" );
    if(port == 1){
        IOWR_32((0xC5f00000 + 3 * 0x400 + 0x0), (0xffffffff));   // reset b2m3
    }else{
        IOWR_32((0xC5f00000 + 0 * 0x400 + 0x0), (0xffffffff));   // reset  b2m0
    }
}

static void xspi_boot_release_reset(int port){
    sd_printf("release %s reset\r\n", (port == 0) ? "OSPI" : "QSPI" );
    if(port == 1){
        IOWR_32((0xC5f00000 + 3 * 0x400 + 0x0), (0x0));   // reset release b2m3
    }else{
        IOWR_32((0xC5f00000 + 0 * 0x400 + 0x0), (0x0));   // reset release b2m0
    }
}

bool xspi_write_image_to_flash(int port, uint8_t* head, uint64_t head_len, uint8_t* image, uint64_t img_len, uint32_t addr){
    struct spi_flash_init_s init = INIT_PARAM;
    struct spi_flash_obj *obj;
    int ret = 0;
    uint8_t *tmp = (uint8_t *)malloc(head_len+img_len);
    init.line_num     = 1;
    init.spi_instance = port;
#if defined(CONFIG_COMPILE_RTL) || defined(CONFIG_COMPILE_ASIC)
    init.compatible_name = "gd_nor";
#else
    init.compatible_name = "xspi_nor";
#endif
    init.flash_type = SPI_NOR_FLASH;

    obj = itcs_spi_flash_init(&init);
    if(obj == NULL){
        return false;
    }
    memcpy(tmp, head, head_len);
    memcpy(tmp+head_len, image, img_len);

    obj->xhandler->work_mode = CDNS_XSPI_MODE_STIG;
    ret = itcs_spi_flash_write(obj, tmp, 0, head_len+img_len);
    if (ret != head_len+img_len) {
        printf("xspi boot write to flash error! ret = %d\n", ret);
        return false;
    }
    memset(tmp, 0, head_len+img_len);
    ret = itcs_spi_flash_read(obj, tmp, 0, head_len+img_len);
    if(memcmp(tmp, head, head_len)){
        printf("xspi boot head read from flash error! ret = %d\n", ret);
        printf("read:\n");
        for(int i = 0; i <head_len+img_len; i++){
            if(i%16 == 0){
                printf("\n");
            }
            printf("0x%x ", tmp[i]);
        }
        printf("write:\n");
        for(int i = 0; i <head_len; i++){
            if(i%16 == 0){
                printf("\n");
            }
            printf("0x%x ", head[i]);
        }
        for(int i = 0; i <img_len; i++){
            if(i%16 == 0){
                printf("\n");
            }
            printf("0x%x ", image[i]);
        }
        return false;
    }
    return true;
}

static void xspi_boot_init(
    uint32_t sys_clk_freq, uint32_t xspi_clk_freq,
    uint32_t init_rb_valid_time, uint32_t init_phy_dq_timing_reg,
    uint32_t init_phy_gate_lpbk_ctrl_reg, uint32_t init_phy_dll_master_ctrl_reg,
    uint32_t init_phy_dll_slave_ctrl_reg, uint32_t init_phy_dqs_timing_reg,
    uint8_t init_wp_enable, uint8_t init_rst_dq3_enable,
    uint8_t init_sw_ctrled_hw_rst_option, uint8_t init_dqs_last_data_drop_en,
    uint8_t init_sdr_edge_active, uint8_t discovery_inhibit,
    uint8_t discovery_num_lines, uint8_t discovery_bank,
    uint8_t discovery_cmd_type, uint8_t discovery_extop_en,
    uint8_t discovery_extop_val, uint8_t discovery_dummy_cnt,
    uint8_t discovery_abnum, uint8_t discovery_seq_crc_en,
    uint8_t discovery_seq_crc_variant, uint8_t discovery_seq_crc_oe,
    uint8_t discovery_seq_crc_chunk_size,
    uint8_t discovery_seq_crc_ual_chunk_en,
    uint8_t discovery_seq_crc_ual_chunk_chk, uint8_t boot_en,
    int port) {

  char _tmp_buff[32];
  uint32_t *_tmp_word = (uint32_t *)_tmp_buff;
  uint32_t _addr;

  _tmp_word[0] = init_phy_dq_timing_reg;
  _tmp_word[1] = init_phy_gate_lpbk_ctrl_reg;
  _tmp_word[2] = init_phy_dll_master_ctrl_reg;
  _tmp_word[3] = init_phy_dll_slave_ctrl_reg;
  _tmp_word[4] = init_phy_dqs_timing_reg;
  _tmp_word[5] = init_rb_valid_time;

  _tmp_word[6] = (discovery_inhibit << 0) |               // 1bit
                 (discovery_extop_val << 1) |             // 1bit
                 (discovery_extop_en << 2) |              // 1bit
                 (discovery_dummy_cnt << 3) |             // 1bit
                 (discovery_num_lines << 4) |             // 4bit
                 (discovery_cmd_type << 8) |              // 2bit
                 (discovery_abnum << 10) |                // 1bit
                 (discovery_bank << 12) |                 // 3bit
                 (discovery_seq_crc_en << 16) |           // 1bit
                 (discovery_seq_crc_variant << 17) |      // 1bit
                 (discovery_seq_crc_oe << 18) |           // 1bit
                 (discovery_seq_crc_chunk_size << 20) |   // 3bit
                 (discovery_seq_crc_ual_chunk_en << 24) | // 1bit
                 (discovery_seq_crc_ual_chunk_chk << 25); // 1bit

  _tmp_word[7] = (init_wp_enable << 0) |               // 1bit
                 (init_sw_ctrled_hw_rst_option << 1) | // 1bit
                 (init_rst_dq3_enable << 2) |          // 1bit
                 (init_dqs_last_data_drop_en << 3) |   // 1bit
                 (init_sdr_edge_active << 4);          // 1bit
  if(port == 0){     
    _addr = OSPI_TB_GPIO_BOOT_REG;
    IOWR_32(_addr, boot_en<<TB_GPIO_BOOT_EN);  //set xspi_boot
    _addr = OSPI_TB_GPIO_DISCOVERY_REG; 
    IOWR_32(_addr, _tmp_word[6]);  //set xspi_discovery
    _addr = OSPI_TB_GPIO_INIT_RB_REG; 
    IOWR_32(_addr, _tmp_word[5]);  //set xspi_init_rb
    _addr = OSPI_TB_GPIO_INIT_PHY_DQ_REG;
    IOWR_32(_addr, _tmp_word[0]);  //set xspi_init_phy_dq_timing_reg (phy 0x2000)
    _addr = OSPI_TB_GPIO_INIT_PHY_DQS_REG; 
    IOWR_32(_addr, _tmp_word[4]);  //set xspi_init_phy_dqs_timing_reg (phy 0x2004)
    _addr = OSPI_TB_GPIO_INIT_PHY_GATE_LPBK_REG;
    IOWR_32(_addr, _tmp_word[1]);  //set xspi_init_phy_gate_lpbk_ctrl_reg (phy 0x2008)
    _addr = OSPI_TB_GPIO_INIT_PHY_DLL_MASTER_REG;
    IOWR_32(_addr, _tmp_word[2]);  //set xspi_init_dll_master_ctrl_reg (phy 0x200c)
    _addr = OSPI_TB_GPIO_INIT_PHY_DLL_SLAVE_REG; 
    IOWR_32(_addr, _tmp_word[3]);  //set xspi_init_dll_slave_ctrl_reg (phy 0x2010)
    _addr = OSPI_TB_GPIO_INIT_REG;  
    IOWR_32(_addr, _tmp_word[7]);  //set xspi_init
  }else{
    _addr = QSPI_TB_GPIO_BOOT_REG;
    IOWR_32(_addr, boot_en<<TB_GPIO_BOOT_EN);  //set xspi_boot
    _addr = QSPI_TB_GPIO_DISCOVERY_REG; 
    IOWR_32(_addr, _tmp_word[6]);  //set xspi_discovery
    _addr = QSPI_TB_GPIO_INIT_RB_REG; 
    IOWR_32(_addr, _tmp_word[5]);  //set xspi_init_rb
    _addr = QSPI_TB_GPIO_INIT_PHY_DQ_REG;
    IOWR_32(_addr, _tmp_word[0]);  //set xspi_init_phy_dq_timing_reg (phy 0x2000)
    _addr = QSPI_TB_GPIO_INIT_PHY_DQS_REG; 
    IOWR_32(_addr, _tmp_word[4]);  //set xspi_init_phy_dqs_timing_reg (phy 0x2004)
    _addr = QSPI_TB_GPIO_INIT_PHY_GATE_LPBK_REG;
    IOWR_32(_addr, _tmp_word[1]);  //set xspi_init_phy_gate_lpbk_ctrl_reg (phy 0x2008)
    _addr = QSPI_TB_GPIO_INIT_PHY_DLL_MASTER_REG;
    IOWR_32(_addr, _tmp_word[2]);  //set xspi_init_dll_master_ctrl_reg (phy 0x200c)
    _addr = QSPI_TB_GPIO_INIT_PHY_DLL_SLAVE_REG; 
    IOWR_32(_addr, _tmp_word[3]);  //set xspi_init_dll_slave_ctrl_reg (phy 0x2010)
    _addr = QSPI_TB_GPIO_INIT_REG;  
    IOWR_32(_addr, _tmp_word[7]);  //set xspi_init
  }

  xspi_boot_release_reset(port);
}

bool xspi_flash_boot(int port) {
  uint32_t _boot_status = 0;
  xspi_boot_assert_reset(port);
  xspi_boot_init(
      SYS_CLK_START_FREQ_kHZ, XSPI_CLK_START_FREQ_kHZ, 0,
      INIT_PHY_DQ_TIMING_REG, INIT_PHY_GATE_LPBK_CTRL_REG,
      INIT_PHY_DLL_MASTER_CTRL_REG, INIT_PHY_DLL_SLAVE_CTRL_REG,
      INIT_PHY_DQS_TIMING_REG, INIT_WP_ENABLE, INIT_RST_DQ3_ENABLE,
      INIT_SW_CTRLED_HW_RST_OPTION, INIT_DQS_LAST_DATA_DROP_EN,
      INIT_SDR_EDGE_ACTIVE, DISCOVERY_INHIBIT, DISCOVERY_NUM_LINES,
      DISCOVERY_BANK, DISCOVERY_CMD_TYPE, DISCOVERY_EXTOP_EN,
      DISCOVERY_EXTOP_VAL, DISCOVERY_DUMMY_CNT, DISCOVERY_ABNUM,
      DISCOVERY_SEQ_CRC_EN, DISCOVERY_SEQ_CRC_VARIANT, DISCOVERY_SEQ_CRC_OE,
      DISCOVERY_SEQ_CRC_CHUNK_SIZE, DISCOVERY_SEQ_CRC_UAL_CHUNK_EN,
      DISCOVERY_SEQ_CRC_UAL_CHUNK_CHK, 1, port);

    printf("Waiting for Boot... ");
    do {
        if(port == 0){
            _boot_status = readl(OSPI_TB_GPIO_BOOT_REG);
        }else{
            _boot_status = readl(QSPI_TB_GPIO_BOOT_REG);
        }
        
        #ifndef CONFIG_COMPILE_RTL
        udelay(1);
        #endif
    } while (!(_boot_status & (1 << TB_GPIO_BOOT_COMP)));
        printf("Ok\r\n");
    
    return true;
}

bool xspi_flash_enbale_device_discovery(XSPI_HandleTypeDef *handler,
                                        bool enable) {
  uint32_t ret;
  XSPI_DeviceDiscoveryConfig ddConfig;
  ret = XSPI_GetDeviceDiscoveryConfig(handler->pD, &ddConfig);
  if (ret != CDN_EOK) {
    return false;
  }

  if (enable == false) {
    ddConfig.reqType  = XSPI_DEV_DISC_REQ_TYPE_CONFIGURE_REGISTERS_ONLY;
    ddConfig.numLines = 0;
  } else {
    ddConfig.reqType  = XSPI_DEV_DISC_REQ_TYPE_FULL_DISCOVERY;
    ddConfig.numLines = handler->init.line_num;
  }

  ret = XSPI_SetDeviceDiscoveryConfig(handler->pD, &ddConfig);
  if (ret != CDN_EOK) {
    return false;
  }
  return true;
}

bool xspi_flash_device_discovery(XSPI_HandleTypeDef *handler, bool aut) {
  uint32_t ret;
  XSPI_DeviceDiscoveryConfig ddConfig;
  ret = XSPI_GetDeviceDiscoveryConfig(handler->pD, &ddConfig);
  if (ret != CDN_EOK) {
    return false;
  }

  ddConfig.reqType = XSPI_DEV_DISC_REQ_TYPE_FULL_DISCOVERY;
  if (aut == true) {
    ddConfig.numLines = 0;
  } else {
    ddConfig.numLines = handler->init.line_num;
  }

  ret = XSPI_SetDeviceDiscoveryConfig(handler->pD, &ddConfig);
  if (ret != CDN_EOK) {
    return false;
  }
  ret = XSPI_RunDeviceDiscovery(handler->pD);
  if (ret != CDN_EOK) {
    return false;
  }
  return true;
}

uint8_t xspi_xip_check_status(XSPI_HandleTypeDef *handler)
{
  
  uint32_t _temp = readl(XSPI_R_INTR_STATUS);
  uint8_t _return = 0;

  if (_temp & (1 << F_DIR_CMD_ERR))       {printf("<!><!><!> Direct CMD Error<!><!><!>\r\n");              writel(1 << F_DIR_CMD_ERR, XSPI_R_INTR_STATUS);      _return = -1;}
  if (_temp & (1 << F_DIR_DQS_ERR))       {printf("<!><!><!> Direct DQS Error<!><!><!>\r\n");              writel(1 << F_DIR_DQS_ERR, XSPI_R_INTR_STATUS);      _return = -1;}
  if (_temp & (1 << F_DIR_CRC_ERR))       {printf("<!><!><!> Direct CRC Error<!><!><!>\r\n");              writel(1 << F_DIR_CRC_ERR, XSPI_R_INTR_STATUS);      _return = -1;}
  if (_temp & (1 << F_DIR_ECC_CORR_ERR))  {printf("<!><!><!> Direct ECC Correctable Error<!><!><!>\r\n");  writel(1 << F_DIR_ECC_CORR_ERR, XSPI_R_INTR_STATUS); _return = -1;}
  if (_temp & (1 << F_DIR_DEV_ERR))       {printf("<!><!><!> Direct Device Error<!><!><!>\r\n");           writel(1 << F_DIR_DEV_ERR, XSPI_R_INTR_STATUS);      _return = -1;}

  return _return;

}

int xspi_nor_flash_xip(struct spi_flash_obj *obj){
    XSPI_HandleTypeDef *handler = obj->xhandler;
    int xip_size = 64;
    uint8_t* tx = (uint8_t*)malloc(xip_size);
    uint8_t* rx = (uint8_t*)malloc(xip_size);
    XSPI_StigCommand *cmd;
    XSPI_DirectCmd directCmd;
    uint32_t dd_status = 1;
    //STIG mode
    for(int i = 0; i<xip_size; i++){
        tx[i] = i;
    }
    itcs_spi_flash_write(obj, tx, 0, xip_size);
    /*
    itcs_spi_flash_read(obj, rx, 0, xip_size);
    printf("xip before read:\n");
    for(int i = 0; i<xip_size; i++){
        if(i%16 == 0){
            printf("\r\n");
        }
        printf("0x%x ",rx[i]);
    }
    printf("\n");
    */
    // Sending Write Enable.
    printf("xip send WEL\n");
    cmd = construct_stig_cmd(false, 1, false, NULL, 0,
                             XSPI_P10_INSTR_WRITE_ENABLE_LATCH,
                             0x06, 0, 0, 0);
    cdns_xspi_send_stig_command(handler, cmd);

    memset(rx, 0, xip_size);

    //0xB1 nor enable xip mode
    uint8_t data = 0xfe;
    printf("xip send nor xip reg\n");
    cmd = construct_stig_cmd(false, 1, true, NULL, 0,
                             XSPI_P10_INSTR_WRITE_MEMORY_REGISTER,
                             SPI_FLASH_WriteReg, 0, 0x06, 3);
    cmd->instructionChain->profile10Instr.dataNoOfBytes = 1;
    cmd->instructionChain->profile10Instr.data[0] = data;
    cdns_xspi_send_stig_command(handler, cmd);

    //device discovery
    printf("device discovery\n");
    if(xspi_flash_device_discovery(handler, true)){
        int cnt = 100;
        do{
            dd_status =  readl(handler->reg_base + 0x260);
            printf("xSPI Device Discovery Status = 0x%x\n", dd_status);
            if(dd_status & 0x4){
                break;
            }
            #ifndef CONFIG_COMPILE_RTL
            udelay(1000* 100);
            #endif
            cnt --;
        }while(cnt);
    }

    if(!(dd_status & 0x4)){
        printf("AutoMated Mode DD failed.\n");
        return -1;
    }else{
        printf("AutoMated Mode DD success.\n");
    }

    //DIRECT mode
    //xspi 0x0398 enter xip mode
    uint32_t _temp = 1 << 8;
    writel(_temp, handler->reg_base + 0x398);
    
    //direct read 16 data to enter xip mode
    printf("xip read 16 data enter xip\n");
    directCmd.direction    = XSPI_DATA_TRANS_DIR_READ;
    directCmd.sysMemPtr    = (uintptr_t)rx;
    directCmd.transferSize = 16;
    directCmd.transferAddr = 0;
    cdns_xspi_send_direct_command(handler, &directCmd);
    if(xspi_xip_check_status(handler)){
        return -1;
    }

    if(memcmp(tx,rx,16)){
        printf("xip read not same as expected:\n tx:\n");
        for(int i = 0; i<16; i++){
            printf("0x%x ", tx[i]);
        }
        printf("\n rx:\n");
        for(int i = 0; i<16; i++){
            printf("0x%x ", rx[i]);
        }
        printf("\n");
    }
    
    //direct read xip_size data in xip mode
    printf("xip read %d data\n", xip_size);
    directCmd.direction    = XSPI_DATA_TRANS_DIR_READ;
    directCmd.sysMemPtr    = (uintptr_t)rx;
    directCmd.transferSize = xip_size;
    directCmd.transferAddr = 0;
    cdns_xspi_send_direct_command(handler, &directCmd);
    if(xspi_xip_check_status(handler)){
        return -1;
    }

    //compare
    if(memcmp(tx,rx,xip_size)){
        printf("xip read not same as expected:\n tx:");
        for(int i = 0; i<xip_size; i++){
            if((i % 16) == 0){
                printf("\n");
            }
            printf("0x%x ", tx[i]);
        }
        printf("\n rx:");
        for(int i = 0; i<xip_size; i++){
            if((i % 16) == 0){
                printf("\n");
            }
            printf("0x%x ", rx[i]);
        }
        printf("\n");
        return -1;
    }

    //xspi 0x0398 exit xip mode
    _temp = 0;
    _temp = 1 << 9;
    writel(_temp, handler->reg_base + 0x398);
    printf("xip read 16 data exit xip\n");
    //direct read 16 data to exit xip mode
    directCmd.direction    = XSPI_DATA_TRANS_DIR_READ;
    directCmd.sysMemPtr    = (uintptr_t)rx;
    directCmd.transferSize = 16;
    directCmd.transferAddr = 0;
    cdns_xspi_send_direct_command(handler, &directCmd);
    if(xspi_xip_check_status(handler)){
        return -1;
    }

    free(rx);
    free(tx);
    return 0;
}

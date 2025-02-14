#include "xspi_init.h"
#include <common.h>

//CPU subsystem CLKGEN
#define MLCLKG_BASE         CLKGEN_BASE + 0xC0

#define CLKGEN_ARANGE       (CLKGEN_BASE + 0x00)
#define CLKGEN_ADIVR        (CLKGEN_BASE + 0x04)
#define CLKGEN_ADIVFI       (CLKGEN_BASE + 0x08)
#define CLKGEN_ADIVQ        (CLKGEN_BASE + 0x0C)
#define CLKGEN_ADIVFF       (CLKGEN_BASE + 0x10)
#define CLKGEN_ADIVQF       (CLKGEN_BASE + 0x14)
#define CLKGEN_ASSCFG       (CLKGEN_BASE + 0x18)
#define CLKGEN_ALDCFG       (CLKGEN_BASE + 0x1C)
#define CLKGEN_AEN          (CLKGEN_BASE + 0x20)
#define CLKGEN_ASEL         (CLKGEN_BASE + 0x24)
#define CLKGEN_ALOCK        (CLKGEN_BASE + 0x28)

#define CLKGEN_DRANGE       (CLKGEN_BASE + 0x30)
#define CLKGEN_DDIVR        (CLKGEN_BASE + 0x34)
#define CLKGEN_DDIVFI       (CLKGEN_BASE + 0x38)
#define CLKGEN_DDIVQ        (CLKGEN_BASE + 0x3C)
#define CLKGEN_DDIVFF       (CLKGEN_BASE + 0x40)
#define CLKGEN_DDIVQF       (CLKGEN_BASE + 0x44)
#define CLKGEN_DSSCFG       (CLKGEN_BASE + 0x48)
#define CLKGEN_DLDCFG       (CLKGEN_BASE + 0x4C)
#define CLKGEN_DEN          (CLKGEN_BASE + 0x50)
#define CLKGEN_DSEL         (CLKGEN_BASE + 0x54)
#define CLKGEN_DLOCK        (CLKGEN_BASE + 0x58)

#define CLKGEN_ERANGE       (CLKGEN_BASE + 0x60)
#define CLKGEN_EDIVR        (CLKGEN_BASE + 0x64)
#define CLKGEN_EDIVFI       (CLKGEN_BASE + 0x68)
#define CLKGEN_EDIVQ        (CLKGEN_BASE + 0x6C)
#define CLKGEN_EDIVFF       (CLKGEN_BASE + 0x70)
#define CLKGEN_EDIVQF       (CLKGEN_BASE + 0x74)
#define CLKGEN_ESSCFG       (CLKGEN_BASE + 0x78)
#define CLKGEN_ELDCFG       (CLKGEN_BASE + 0x7C)
#define CLKGEN_EEN          (CLKGEN_BASE + 0x80)
#define CLKGEN_ESEL         (CLKGEN_BASE + 0x84)
#define CLKGEN_ELOCK        (CLKGEN_BASE + 0x88)

#define CLKGEN_VRANGE       (CLKGEN_BASE + 0x90)
#define CLKGEN_VDIVR        (CLKGEN_BASE + 0x94)
#define CLKGEN_VDIVFI       (CLKGEN_BASE + 0x98)
#define CLKGEN_VDIVQ        (CLKGEN_BASE + 0x9C)
#define CLKGEN_VDIVFF       (CLKGEN_BASE + 0xA0)
#define CLKGEN_VDIVQF       (CLKGEN_BASE + 0xA4)
#define CLKGEN_VSSCFG       (CLKGEN_BASE + 0xA8)
#define CLKGEN_VLDCFG       (CLKGEN_BASE + 0xAC)
#define CLKGEN_VEN          (CLKGEN_BASE + 0xB0)
#define CLKGEN_VSEL         (CLKGEN_BASE + 0xB4)
#define CLKGEN_VLOCK        (CLKGEN_BASE + 0xB8)

#define CPUC_LOADEN         (CLKGEN_BASE + 0x380)
#define CPUC_SRCCFG         (CLKGEN_BASE + 0x384)
#define CPUC_CLKCYC         (CLKGEN_BASE + 0x388)
#define CPUC_CLKSEQ         (CLKGEN_BASE + 0x38C)
#define CPUC_BUSSEQ         (CLKGEN_BASE + 0x390)
#define CPUC_BUSEN          (CLKGEN_BASE + 0x394)

//#define CLKG_WSRC   (io, val )  (void) MA_OUTW(MLCLKG_BASE+0x0+(uint32_t)io*0x10, (uint32_t) val)
//#define CLKG_WRATIO (io, val )  (void) MA_OUTW(MLCLKG_BASE+0x4+(uint32_t)io*0x10, (uint32_t) val)
//#define CLKG_WNCO   (io, val )  (void) MA_OUTW(MLCLKG_BASE+0x8+(uint32_t)io*0x10, (uint32_t) val)
//#define CLKG_WCFG   (io, val )  (void) MA_OUTW(MLCLKG_BASE+0xC+(uint32_t)io*0x10, (uint32_t) val)

///////////////////////////////////////////////////////////
//SAP subsystem CLKGEN
#define SMLCLKG_BASE        SCLKGEN_BASE + 0xC0

#define SCLKGEN_ARANGE      (SCLKGEN_BASE + 0x00)
#define SCLKGEN_ADIVR       (SCLKGEN_BASE + 0x04)
#define SCLKGEN_ADIVFI      (SCLKGEN_BASE + 0x08)
#define SCLKGEN_ADIVQ       (SCLKGEN_BASE + 0x0C)
#define SCLKGEN_ADIVFF      (SCLKGEN_BASE + 0x10)
#define SCLKGEN_ADIVQF      (SCLKGEN_BASE + 0x14)
#define SCLKGEN_ASSCFG      (SCLKGEN_BASE + 0x18)
#define SCLKGEN_ALDCFG      (SCLKGEN_BASE + 0x1C)
#define SCLKGEN_AEN         (SCLKGEN_BASE + 0x20)
#define SCLKGEN_ASEL        (SCLKGEN_BASE + 0x24)
#define SCLKGEN_ALOCK       (SCLKGEN_BASE + 0x28)

#define CLKGEN_BASE     0xC2F08000
#define RSTM_BASE       0xC2F08400
#define DINT_BASE       0xC2F08800
#define CPUM_BASE       0xC2F08C00
#define IOM_BASE        0xC2F09000

#define SCLKGEN_BASE    0xD2F08000
#define SRSTM_BASE      0xD2F08400
#define SDINT_BASE      0xD2F08800
#define SAPM_BASE       0xD2F08C00
#define SIOM_BASE       0xD2F09000

static void xspi_init_platform(int port) {
#ifdef CONFIG_COMPILE_RTL
  uint32_t i, _addr, _rdata;
  for (i = 0; i < 99; i = i + 1) { //
    IOWR_32((IOM_BASE + i * 0x4),
            (0x1000)); // set cpad func mode & input enable
  }
  for (i = 0; i < 18; i = i + 1) { //
    IOWR_32((SIOM_BASE + i * 0x4),
            (0x1000)); // set spad func mode & input enable
  }

  // PLLOUT = REF / DIVR_VAL * 4 * DIVF_VAL / DIVQ_VAL
  // VCO    = REF / DIVR_VAL * 4 * DIVF_VAL (1200 ~ 6000 MHz)
  // APLL
  IOWR_32(CLKGEN_ARANGE, 3);       // bypass,range=3(24MHz)
  IOWR_32(CLKGEN_ADIVR, 0);        // DIVR_VAL=DIVR[5:0]+1
  IOWR_32(CLKGEN_ADIVFI, 104 / 4); // DIVF_VAL=DIVFI[8:0]
  IOWR_32(CLKGEN_ADIVQ, 0);        // DIVQ_VAL=2*(DIVQ[4:0]+1)
  IOWR_32(CLKGEN_ADIVFF, 0);       // Fractional mode
  IOWR_32(CLKGEN_ADIVQF, 0);       // PLLOUTF div=DIVQF[2:0]+1
  IOWR_32(CLKGEN_ASSCFG, 0);       // ss cfg
  IOWR_32(CLKGEN_ALDCFG, 3); // load parameter, newdiv[2], load[1], oute[0]
  IOWR_32(CLKGEN_AEN, 1);    // pll enable
  _rdata = 0;
  while (_rdata != 0x1) {
    _rdata = IORD_32(CLKGEN_ALOCK) & 0x1; // check apll lock
  }
  IOWR_32(CLKGEN_ASEL, 2); // pll source sel and output sel
  ////////////////////////////////////////

  // DPLL
  IOWR_32(CLKGEN_DRANGE, 3);       // bypass,range=3(24MHz)
  IOWR_32(CLKGEN_DDIVR, 1);        // DIVR_VAL=DIVR[5:0]+1
  IOWR_32(CLKGEN_DDIVFI, 250 / 4); // DIVF_VAL=DIVFI[8:0]
  IOWR_32(CLKGEN_DDIVQ, 0);        // DIVQ_VAL=2*(DIVQ[4:0]+1)
  IOWR_32(CLKGEN_DDIVFF, 0);       // Fractional mode
  IOWR_32(CLKGEN_DDIVQF, 0);       // PLLOUTF div=DIVQF[2:0]+1
  IOWR_32(CLKGEN_DSSCFG, 0);       // ss cfg
  IOWR_32(CLKGEN_DLDCFG, 3); // load parameter, newdiv[2], load[1], oute[0]
  IOWR_32(CLKGEN_DEN, 1);    // pll enable
  _rdata = 0;
  while (_rdata != 0x1) {
    _rdata = IORD_32(CLKGEN_DLOCK) & 0x1; // check dpll lock
  }
  IOWR_32(CLKGEN_DSEL, 2); // pll source sel and output sel

  if(port == 0){
    // b2m0
    _addr = 0xC2F08000 + 0x1A0;
    IOWR_32(_addr, 0x01); // set emmc0_clksrc to dpll
    _addr = 0xC2F08000 + 0x1A4;
    IOWR_32(_addr, 0x1D); // set emmc0_clksrc div ratio to (29+1)
  }else{
    // b2m3
    _addr = 0xC2F08000 + 0x1D0;
    IOWR_32(_addr, 0x01); // set xspi3_clksrc to dpll
    _addr = 0xC2F08000 + 0x1D4;
    IOWR_32(_addr, 0x1D); // set xspi3_clksrc div ratio to (29+1)
  }

#endif

  if(port == 0){
    //ospi
    //b2m0
    writel((0xffffffff), (0xC5f00000 + 0 * 0x400));
    writel((0xffff), (0xC5f00000 + 0 * 0x400 + 0x4)); // clkgate en
    writel((0x3), (0xC5f00000 + 0 * 0x400 + 0xc));    // bus en
    writel((0x1), (0xC5f00000 + 0 * 0x400 + 0x18));   // io in en
    writel((0x0), (OSPI_TB_GPIO_SEL_REG));            // sel_xspi
  }else{
    //qspi
    //b2m3
    writel((0xffffffff), (0xC5f00000 + 3 * 0x400));
    writel((0xffff), (0xC5f00000 + 3 * 0x400 + 0x4)); // clkgate en
    writel((0x3), (0xC5f00000 + 3 * 0x400 + 0xc));    // bus en
    writel((0x1), (0xC5f00000 + 3 * 0x400 + 0x18));   // io in en
  }
  // enable b2m5 dmac
  IOWR_32((0xC5f00000 + 5 * 0x400 + 0x4), (0xffff)); // clkgate en
  IOWR_32((0xC5f00000 + 5 * 0x400 + 0xc), (0x3));    // bus en
  IOWR_32((0xC5f00000 + 5 * 0x400 + 0x18), (0x1));   // io in en
  IOWR_32((0xC5f00000 + 5 * 0x400 + 0x0), (0x0));    // reset release

}

void xspi_release_reset(int port){
    sd_printf("release %s reset\r\n", (port == 0) ? "OSPI" : "QSPI" );
    if(port == 1){
        IOWR_32((0xC5f00000 + 3 * 0x400 + 0x0), (0x0)); // reset release b2m3
    }else{
        IOWR_32((0xC5f00000 + 0 * 0x400 + 0x0), (0x0));   // reset release b2m0
    }
}


static void xspi_init_low_level(
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
#if 0
  sd_printf("Assert system reset\r\n");
  sd_printf("Assert system reset\r\n");
  // gpio_write( 0 );                // clear all outputs

  sd_printf("----------CLOCKS and BOOTSTRAP PORTS---------------\r\n");
  sd_printf("System clock frequency:          %f (MHz) \r\n",
            sys_clk_freq / 1000.0);
  sd_printf("xSPI clock frequency:            %f (MHz) \r\n",
            xspi_clk_freq / 1000.0);
  sd_printf("init_rb_valid_time               0x%08x \r\n", init_rb_valid_time);
  sd_printf("init_phy_dq_timing_reg           0x%08x \r\n",
            init_phy_dq_timing_reg);
  sd_printf("init_phy_gate_lpbk_ctrl_reg      0x%08x \r\n",
            init_phy_gate_lpbk_ctrl_reg);
  sd_printf("init_phy_dll_master_ctrl_reg     0x%08x \r\n",
            init_phy_dll_master_ctrl_reg);
  sd_printf("init_phy_dll_slave_ctrl_reg      0x%08x \r\n",
            init_phy_dll_slave_ctrl_reg);
  sd_printf("init_phy_dqs_timing_reg          0x%08x \r\n",
            init_phy_dqs_timing_reg);
  sd_printf("init_wp_enable                   %d \r\n", init_wp_enable);
  sd_printf("init_rst_dq3_enable              %d \r\n", init_rst_dq3_enable);
  sd_printf("init_sw_ctrled_hw_rst_option     %d \r\n",
            init_sw_ctrled_hw_rst_option);
  sd_printf("init_dqs_last_data_drop_en       %d \r\n",
            init_dqs_last_data_drop_en);
  sd_printf("init_sdr_edge_active             %d \r\n", init_sdr_edge_active);
  sd_printf("discovery_inhibit                %d \r\n", discovery_inhibit);
  sd_printf("discovery_num_lines              %d \r\n", discovery_num_lines);
  sd_printf("discovery_bank                   %d \r\n", discovery_bank);
  sd_printf("discovery_abnum                  %d \r\n", discovery_abnum);
  sd_printf("discovery_dummy_cnt              %d \r\n", discovery_dummy_cnt);
  sd_printf("discovery_cmd_type               %d \r\n", discovery_cmd_type);
  sd_printf("discovery_extop_en               %d \r\n", discovery_extop_en);
  sd_printf("discovery_extop_val              %d \r\n", discovery_extop_val);
  sd_printf("discovery_seq_crc_en             %d \r\n", discovery_seq_crc_en);
  sd_printf("discovery_seq_crc_variant        %d \r\n",
            discovery_seq_crc_variant);
  sd_printf("discovery_seq_crc_oe             %d \r\n", discovery_seq_crc_oe);
  sd_printf("discovery_seq_crc_chunk_size     %d \r\n",
            discovery_seq_crc_chunk_size);
  sd_printf("discovery_seq_crc_ual_chunk_en   %d \r\n",
            discovery_seq_crc_ual_chunk_en);
  sd_printf("discovery_seq_crc_ual_chunk_chk  %d \r\n",
            discovery_seq_crc_ual_chunk_chk);
  sd_printf("boot_en                          %d \r\n", boot_en);
  sd_printf("---------------------------------------------------\r\n");
#endif
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
    //_addr = OSPI_TB_GPIO_BOOT_REG;
    // IOWR_32(_addr, boot_en<<TB_GPIO_BOOT_EN);  //set xspi_boot
    _addr = OSPI_TB_GPIO_DISCOVERY_REG;
    IOWR_32(_addr, _tmp_word[6]); // set xspi_discovery
    //_addr = OSPI_TB_GPIO_INIT_RB_REG;
    // IOWR_32(_addr, _tmp_word[5]);  //set xspi_init_rb
    //_addr = OSPI_TB_GPIO_INIT_PHY_DQ_REG;
    // IOWR_32(_addr, _tmp_word[0]);  //set xspi_init_phy_dq_timing_reg (phy
    // 0x2000) _addr = OSPI_TB_GPIO_INIT_PHY_DQS_REG; IOWR_32(_addr, _tmp_word[4]);
    // //set xspi_init_phy_dqs_timing_reg (phy 0x2004) _addr =
    //OSPI_TB_GPIO_INIT_PHY_GATE_LPBK_REG; IOWR_32(_addr, _tmp_word[1]);  //set
    // xspi_init_phy_gate_lpbk_ctrl_reg (phy 0x2008)
    _addr = OSPI_TB_GPIO_INIT_PHY_DLL_MASTER_REG;
    IOWR_32(_addr, _tmp_word[2]);  //set
    // xspi_init_dll_master_ctrl_reg (phy 0x200c)
    _addr = OSPI_TB_GPIO_INIT_PHY_DLL_SLAVE_REG;
    IOWR_32(_addr, _tmp_word[3]); // set xspi_init_dll_slave_ctrl_reg (phy 0x2010)
    //_addr = OSPI_TB_GPIO_INIT_REG;
    // IOWR_32(_addr, _tmp_word[7]);  //set xspi_init
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

  xspi_release_reset(port);
}

static int xspi_init_wait_for_status__(int port) {
  uint32_t _init_status = 0;

  printf("Waiting for initialization... ");
  int times = 1000 * 20;
  do {
    if(port == 0){
        _init_status = IORD_32(OSPI_TB_GPIO_INIT_REG);
    }else{
        _init_status = IORD_32(QSPI_TB_GPIO_INIT_REG);
    }
    udelay(5);
    times--;
    if (times <= 0)
      break;
  } while (!(_init_status & (1 << TB_GPIO_INIT_COMP)));
  
  if (times == 0) {
    return -1;
  }
  
  if(port == 0){
    times = 1000 * 20;
    _init_status = 0;
    do {
      _init_status = IORD_32(OSPI_TB_GPIO_PHY_EXT_REG);
      udelay(5);
      times--;
      if (times <= 0)
        break;
    } while (!(_init_status & (1 << TB_GPIO_PHY_EXT_COMP)));
    if (times == 0) {
      return -1;
    }
  }

  printf("Ok\r\n");
  uint32_t _addr = OSPI_TB_GPIO_PHY_EXT_REG;
  int ret = IORD_32(_addr);
  IOWR_32(_addr, ret|0x1);
  ret = IORD_32(_addr);
 
  _addr = (0xc5000000 + 0x8004);
  ret = IORD_32(_addr);

  IOWR_32(_addr, 0x16<<8);
  ret = IORD_32(_addr);
  
  _addr = OSPI_TB_GPIO_PHY_EXT_REG;
  ret = IORD_32(_addr);
  IOWR_32(_addr, ret&(0xfffffffe));

  return 0;
}

// ----------------------- End of: xspi_init_wait_for_status__
// --------------------------

// --------------------------- xspi_ini_get_status
// ------------------------------
/* This procedure returns initialization process status */
static uint32_t xspi_init_get_status__(int port) {
  sd_printf("Checking initialization status... ");
  if(port == 0){
    if (IORD_32(OSPI_TB_GPIO_INIT_REG) & (0x1 << TB_GPIO_INIT_FAIL)) {
        sd_printf("<!><!><!> Error <!><!><!>\r\n");
        return 1;
    } else {
        sd_printf("Ok\r\n");
        return 0;
    }
  }else{
    if (IORD_32(QSPI_TB_GPIO_INIT_REG) & (0x1 << TB_GPIO_INIT_FAIL)) {
        sd_printf("<!><!><!> Error <!><!><!>\r\n");
        return 1;
    } else {
        sd_printf("Ok\r\n");
        return 0;
    }
  }

}
// ----------------------- End of: xspi_init_get_status__
// --------------------------

// --------------------------- xspi_boot_wait_for_status__
// ------------------------------
/* This procedure waits for BOOT process is compelted */
#if 0
static void xspi_boot_wait_for_status__(int port) {
  uint32_t _boot_status = 0;

  sd_printf("Waiting for Boot... ");
  do {
    if(port == 0){
        _boot_status = IORD_32(OSPI_TB_GPIO_BOOT_REG);
    }else{
        _boot_status = IORD_32(QSPI_TB_GPIO_BOOT_REG);
    }
    
    sd_delay(5);
  } while (!(_boot_status & (1 << TB_GPIO_BOOT_COMP)));
  sd_printf("Ok\r\n");
}

// ----------------------- End of: xspi_boot_wait_for_status__
// --------------------------

// --------------------------- xspi_boot_get_status__
// ------------------------------
/* This procedure returns BOOT process status */
static uint32_t xspi_boot_get_status__(int port) {
  sd_printf("Checking Boot status... ");
  if(port == 0){
    if (IORD_32(OSPI_TB_GPIO_BOOT_REG) & (0x1 << TB_GPIO_BOOT_ERROR)) {
        sd_printf("<!><!><!> Error <!><!><!>\r\n");
        return 1;
    } else {
        sd_printf("Ok\r\n");
        return 0;
    }
  }else{
    if (IORD_32(QSPI_TB_GPIO_BOOT_REG) & (0x1 << TB_GPIO_BOOT_ERROR)) {
        sd_printf("<!><!><!> Error <!><!><!>\r\n");
        return 1;
    } else {
        sd_printf("Ok\r\n");
        return 0;
    }
  }

}
// ----------------------- End of: xspi_boot_get_status__
// --------------------------

// --------------------------- xspi_wait_for_idle__
// ------------------------------
/* This procedure checks if controller is in IDLE state by pooling the
 * ctrl_busy bit in ctrl_status register */
static void xspi_wait_for_idle__(int port) {
  uint32_t _status;

  do {
    if(port == 0){
        _status = IORD_32(OSPI_R_CTRL_STATUS); // get ctrl_status register
    }else{
        _status = IORD_32(QSPI_R_CTRL_STATUS); // get ctrl_status register
    }

    _status &= (1 << F_CTRL_BUSY);         // unmask ctrl_busy pin only
  } while (_status != 0);
}
#endif
static uint8_t xspi_set_params__(int port) {

  uint8_t _return = 0;

  xspi_init_low_level(
      SYS_CLK_START_FREQ_kHZ, XSPI_CLK_START_FREQ_kHZ, INIT_RB_VALID_TIME,
      INIT_PHY_DQ_TIMING_REG, INIT_PHY_GATE_LPBK_CTRL_REG,
      INIT_PHY_DLL_MASTER_CTRL_REG, INIT_PHY_DLL_SLAVE_CTRL_REG,
      INIT_PHY_DQS_TIMING_REG, INIT_WP_ENABLE, INIT_RST_DQ3_ENABLE,
      INIT_SW_CTRLED_HW_RST_OPTION, INIT_DQS_LAST_DATA_DROP_EN,
      INIT_SDR_EDGE_ACTIVE, DISCOVERY_INHIBIT, DISCOVERY_NUM_LINES,
      DISCOVERY_BANK, DISCOVERY_CMD_TYPE, DISCOVERY_EXTOP_EN,
      DISCOVERY_EXTOP_VAL, DISCOVERY_DUMMY_CNT, DISCOVERY_ABNUM,
      DISCOVERY_SEQ_CRC_EN, DISCOVERY_SEQ_CRC_VARIANT, DISCOVERY_SEQ_CRC_OE,
      DISCOVERY_SEQ_CRC_CHUNK_SIZE, DISCOVERY_SEQ_CRC_UAL_CHUNK_EN,
      DISCOVERY_SEQ_CRC_UAL_CHUNK_CHK, BOOT_EN, port);
  
  // Wait for initialization process
  xspi_init_wait_for_status__(port);

  if (xspi_init_get_status__(port) != 0)
    _return = -1;

  return _return;
}

int cdns_xspi_before_driver_init(int port) {

  xspi_init_platform(port);

  // Configure Bootstrap ports and init controller
  if (xspi_set_params__(port)) {
    sd_printf("Test failed\r\n");
    return -1;
  }
  return 0;
}

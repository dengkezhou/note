#include "../lpddr4_common.h"
#include "lpddr4_boundary_test.h"
void lpddr4_atb_test_conf(uint32_t atb_pattern,uint32_t atb_mapping){
    uint32_t reg_value = 0;
    reg_value = (reg_value&(~(0x1f<<1)))|(atb_pattern<<1);
    write_register(0x0000554c,(reg_value&(~(0x1f<<1)))|(atb_pattern<<1));
    reg_value = (reg_value&(~(0x7f<<8)))|(atb_mapping<<8);
    write_register(0x0000554c,(reg_value&(~(0x7f<<8)))|(atb_mapping<<8));
}

void lpddr4_atb_test_enable(uint32_t enable){
    uint32_t reg_value = 0;
    reg_value = read_register(0x0000554c);
    write_register(0x0000554c,(reg_value&(~(1<<0)))|(enable<<0));
}

void lpddr4_atb_test(void){
    phy_sw_master_mode();
    mc_lpi_wakeup_en();
    phy_wait_for_dfi_complete_init(0xf,1,0,0);
    // phy_disable_dly_ctrl_power_reduction();
    // mc_refresh_conf();
    // mc_dfi_auto_update_conf();
    // mc_dfi_update_count_set();
    // phy_manual_training();
    lpddr4_atb_test_enable(0);
    lpddr4_atb_test_conf(0x2,0xa);
    udelay(1);
    lpddr4_atb_test_enable(1);
}

void jtag_enable_conf(void){
    write_boundary_register(JTAG_ENABLE,0x1);
    write_boundary_register(JTAG_ENABLE_IE,0x1);
    write_boundary_register(JTAG_ENABLE_OE,0x1);
    write_boundary_register(JTAG_ENABLE_DRIVE,0x1);
    write_boundary_register(JTAG_ENABLE_TERM,0x1);
}

void jtag_dataout_address_conf(void){
    write_boundary_register(JTAG_DATAOUT_ADDRESS,0x0);
    write_boundary_register(JTAG_DATAOUT_ADDRESS_OE,0x0000007f);
    write_boundary_register(JTAG_DATAOUT_ADDR_DRIVE,0x00000801);
    write_boundary_register(JTAG_DATAOUT_ADDR_DRIVE2,0x01fe0010);
    write_boundary_register(JTAG_DATAOUT_ADDR_TERM,0x00024410);
}

void jtag_dataout_address_tsel(void){
    write_boundary_register(JTAG_DATAOUT_TSEL_ADDR_EN,0x1);
    write_boundary_register(JTAG_DATAOUT_TSEL_ADDR_SEL0,0x1);
    write_boundary_register(JTAG_DATAOUT_TSEL_ADDR_SEL1,0x1);
    write_boundary_register(JTAG_DATAOUT_TSEL_ADDR_SEL2,0x1);
    write_boundary_register(JTAG_DATAOUT_TSEL_ADDR_SEL3,0x1);
    write_boundary_register(JTAG_DATAOUT_TSEL_ADDR_SEL4,0x1);
    write_boundary_register(JTAG_DATAOUT_TSEL_ADDR_SEL5,0x1);
    write_boundary_register(JTAG_DATAOUT_TSEL_ADDR_SEL6,0x1);
    write_boundary_register(JTAG_DATAOUT_TSEL_ADDR_SEL7,0x1);
}

void jtag_dataout_ca_conf(void){
    write_boundary_register(JTAG_DATAOUT_CS_N,0x0);
    write_boundary_register(JTAG_DATAOUT_CS_N_OE,0xf);
    write_boundary_register(JTAG_DATAOUT_CKE,0x0);
    write_boundary_register(JTAG_DATAOUT_CKE_OE,0x3);
    write_boundary_register(JTAG_DATAOUT_RESET_N,0x0);
    write_boundary_register(JTAG_DATAOUT_RESET_N_OE,0x1);
}

void jtag_dataout_memclk_conf(void){
    write_boundary_register(JTAG_DATAOUT_MEM_CLK_0,0x0);
    write_boundary_register(JTAG_DATAOUT_MEM_CLK_0_OE,0x1);
    write_boundary_register(JTAG_DATAOUT_MEM_CLK_1,0x0);
    write_boundary_register(JTAG_DATAOUT_MEM_CLK_1_OE,0x1);
    write_boundary_register(JTAG_DATAOUT_CLK_DRIVE,0x000080ff);
    write_boundary_register(JTAG_DATAOUT_CLK_DRIVE2,0x00000210);
    write_boundary_register(JTAG_DATAOUT_CLK_TERM,0x00024410);
}

void jtag_dataout_data_conf(void){
    write_boundary_register(JTAG_DATAOUT_DATA,0x0);
    write_boundary_register(JTAG_DATAOUT_DATA_OE,0xffffffff);
    write_boundary_register(JTAG_DATAOUT_DATA_DRIVE,0x80);
    write_boundary_register(JTAG_DATAOUT_DATA_DRIVE2,0x0);
    write_boundary_register(JTAG_DATAOUT_DATA_TERM,0x4410);
}

void jtag_dataout_tsel(void){
    write_boundary_register(JTAG_DATAOUT_TSEL_EN,0x1);
    write_boundary_register(JTAG_DATAOUT_TSEL_WR_SEL0,0x1);
    write_boundary_register(JTAG_DATAOUT_TSEL_WR_SEL1,0x1);
    write_boundary_register(JTAG_DATAOUT_TSEL_WR_SEL2,0x1);
    write_boundary_register(JTAG_DATAOUT_TSEL_WR_SEL3,0x1);
    write_boundary_register(JTAG_DATAOUT_TSEL_WR_SEL4,0x1);
    write_boundary_register(JTAG_DATAOUT_TSEL_WR_SEL5,0x1);
    write_boundary_register(JTAG_DATAOUT_TSEL_WR_SEL6,0x1);
    write_boundary_register(JTAG_DATAOUT_TSEL_WR_SEL7,0x1);
}

void jtag_dataout_dqs_conf(void){
    write_boundary_register(JTAG_DATAOUT_DQS,0x0);
    write_boundary_register(JTAG_DATAOUT_DQS_OE,0xf);
    write_boundary_register(JTAG_DATAOUT_DQS_DRIVE,0x80);
    write_boundary_register(JTAG_DATAOUT_DQS_DRIVE2,0x0);
    write_boundary_register(JTAG_DATAOUT_DQS_TERM,0x00004410);
}

void jtag_dataout_dm_conf(void){
    write_boundary_register(JTAG_DATAOUT_DM,0x0);
    write_boundary_register(JTAG_DATAOUT_DM_OE,0xf);
}

void jtag_datain_address_conf(void){
    write_boundary_register(JTAG_DATAOUT_ADDRESS_IE,0x7f);
}

void jtag_datain_ca_conf(void){
    write_boundary_register(JTAG_DATAOUT_CS_N_IE,0xf);
    write_boundary_register(JTAG_DATAOUT_CKE_IE,0x3);
    write_boundary_register(JTAG_DATAOUT_RESET_N_IE,0x1);
}

void jtag_datain_memclk_conf(void){
    write_boundary_register(JTAG_DATAOUT_MEM_CLK_0_IE,0x1);
    write_boundary_register(JTAG_DATAOUT_MEM_CLK_1_IE,0x1);
}

void jtag_datain_data_conf(void){
    write_boundary_register(JTAG_DATAOUT_DATA_IE,0xffffffff);
    write_boundary_register(JTAG_DATAOUT_DATA_RX_IE_CAL_ALL,0x0);
    write_boundary_register(JTAG_DATAOUT_PHY_RX_CAL_CODE,0x0);
}

void jtag_datain_tsel(void){
    write_boundary_register(JTAG_DATAOUT_TSEL_RD_SEL0,0x1);
    write_boundary_register(JTAG_DATAOUT_TSEL_RD_SEL1,0x1);
    write_boundary_register(JTAG_DATAOUT_TSEL_RD_SEL2,0x1);
    write_boundary_register(JTAG_DATAOUT_TSEL_RD_SEL3,0x1);
    write_boundary_register(JTAG_DATAOUT_TSEL_RD_SEL4,0x1);
    write_boundary_register(JTAG_DATAOUT_TSEL_RD_SEL5,0x1);
    write_boundary_register(JTAG_DATAOUT_TSEL_RD_SEL6,0x1);
}

void jtag_datain_dqs_conf(void){
    write_boundary_register(JTAG_DATAOUT_DQS_IE,0xf);
    write_boundary_register(JTAG_DATAOUT_DQS_RX_IE_CAL_ALL,0x0);
}

void jtag_datain_dm_conf(void){
    write_boundary_register(JTAG_DATAOUT_DM_IE,0xf);
    write_boundary_register(JTAG_DATAOUT_DM_RX_IE_CAL_ALL,0x0);
}

void jtag_boundary_test(void){
    uint32_t jtag_datain_address = 0;
    uint32_t jtag_datain_cs_n = 0;
    uint32_t jtag_datain_cke = 0;
    uint32_t jtag_datain_reset_n = 0;
    uint32_t jtag_datain_mem_clk_0 = 0;
    uint32_t jtag_datain_mem_clk_1 = 0;
    uint32_t jtag_datain_data = 0;
    uint32_t jtag_datain_dqs = 0;
    uint32_t jtag_datain_dm = 0;

    jtag_enable_conf();
    jtag_dataout_address_conf();
    jtag_dataout_address_tsel();
    jtag_dataout_ca_conf();
    jtag_dataout_memclk_conf();
    jtag_dataout_data_conf();
    jtag_dataout_tsel();
    jtag_dataout_dqs_conf();
    jtag_dataout_dm_conf();

    jtag_datain_address_conf();
    jtag_datain_ca_conf();
    jtag_datain_memclk_conf();
    jtag_datain_data_conf();
    jtag_datain_tsel();
    jtag_datain_dqs_conf();
    jtag_datain_dm_conf();

    write_boundary_register(JTAG_DATAOUT_ADDRESS,0x0);
    write_boundary_register(JTAG_DATAOUT_CS_N,0x0);
    write_boundary_register(JTAG_DATAOUT_CKE,0x0);
    write_boundary_register(JTAG_DATAOUT_RESET_N,0x0);
    write_boundary_register(JTAG_DATAOUT_MEM_CLK_0,0x0);
    write_boundary_register(JTAG_DATAOUT_MEM_CLK_1,0x0);
    write_boundary_register(JTAG_DATAOUT_DATA,0x0);
    write_boundary_register(JTAG_DATAOUT_DQS,0x0);
    write_boundary_register(JTAG_DATAOUT_DM,0x0);

    udelay(1);
    jtag_datain_address = read_boundary_register(JTAG_DATAIN_ADDRESS);
    jtag_datain_cs_n = read_boundary_register(JTAG_DATAIN_CS_N);
    jtag_datain_cke = read_boundary_register(JTAG_DATAIN_CKE);
    jtag_datain_reset_n = read_boundary_register(JTAG_DATAIN_RESET_N);
    jtag_datain_mem_clk_0 = read_boundary_register(JTAG_DATAIN_MEM_CLK_0);
    jtag_datain_mem_clk_1 = read_boundary_register(JTAG_DATAIN_MEM_CLK_1);
    jtag_datain_data = read_boundary_register(JTAG_DATAIN_DATA);
    jtag_datain_dqs = read_boundary_register(JTAG_DATAIN_DQS);
    jtag_datain_dm = read_boundary_register(JTAG_DATAIN_DM);

    if(jtag_datain_address==0){
        printf("PASS!JTAG_DATAIN_ADDRESS is 0x0\n");
    }else{
        printf("JTAG_DATAIN_ADDRESS check fail and value is %x\n",jtag_datain_address);
    }
    if(jtag_datain_cs_n==0){
        printf("PASS!JTAG_DATAIN_CS_N is 0x0\n");
    }else{
        printf("JTAG_DATAIN_CS_N check fail and value is %x\n",jtag_datain_cs_n);
    }
    if(jtag_datain_cke==0){
        printf("PASS!JTAG_DATAIN_CKE is 0x0\n");
    }else{
        printf("PASS!JTAG_DATAIN_CKE check fail and value is %x\n",jtag_datain_cke);
    }
    if(jtag_datain_reset_n==0){
        printf("PASS!JTAG_DATAIN_RESET_N is 0x0\n");
    }else{
        printf("JTAG_DATAIN_RESET_N check fail and value is %x\n",jtag_datain_reset_n);
    }
    if(jtag_datain_mem_clk_0==0){
        printf("PASS!JTAG_DATAIN_MEM_CLK_0 is 0x0\n");
    }else{
        printf("JTAG_DATAIN_MEM_CLK_0 check fail and value is %x\n",jtag_datain_mem_clk_0);
    }
    if(jtag_datain_mem_clk_1==0){
        printf("PASS!JTAG_DATAIN_MEM_CLK_1 is 0x0\n");
    }else{
        printf("JTAG_DATAIN_MEM_CLK_1 check fail and value is %x\n",jtag_datain_mem_clk_1);
    }
    if(jtag_datain_data==0){
        printf("PASS!JTAG_DATAIN_DATA is 0x0\n");
    }else{
        printf("JTAG_DATAIN_DATA check fail and value is %x\n",jtag_datain_data);
    }
    if(jtag_datain_dqs==0){
        printf("PASS!JTAG_DATAIN_DQS is 0x0\n");
    }else{
        printf("JTAG_DATAIN_DQS check fail and value is %x\n",jtag_datain_dqs);
    }
    if(jtag_datain_dm==0){
        printf("PASS!JTAG_DATAIN_DM is 0x0\n");
    }else{
        printf("JTAG_DATAIN_DM check fail and value is %x\n",jtag_datain_dm);
    }
        


    write_boundary_register(JTAG_DATAOUT_ADDRESS,0x0000003f);
    write_boundary_register(JTAG_DATAOUT_CS_N,0xf);
    write_boundary_register(JTAG_DATAOUT_CKE,0x3);
    write_boundary_register(JTAG_DATAOUT_RESET_N,0x1);
    write_boundary_register(JTAG_DATAOUT_MEM_CLK_0,0x1);
    write_boundary_register(JTAG_DATAOUT_MEM_CLK_1,0x1);
    write_boundary_register(JTAG_DATAOUT_DATA,0xffffffff);
    write_boundary_register(JTAG_DATAOUT_DQS,0xf);
    write_boundary_register(JTAG_DATAOUT_DM,0xf);

    udelay(5);

    jtag_datain_address = read_boundary_register(JTAG_DATAIN_ADDRESS);
    jtag_datain_cs_n = read_boundary_register(JTAG_DATAIN_CS_N);
    jtag_datain_cke = read_boundary_register(JTAG_DATAIN_CKE);
    jtag_datain_reset_n = read_boundary_register(JTAG_DATAIN_RESET_N);
    jtag_datain_mem_clk_0 = read_boundary_register(JTAG_DATAIN_MEM_CLK_0);
    jtag_datain_mem_clk_1 = read_boundary_register(JTAG_DATAIN_MEM_CLK_1);
    jtag_datain_data = read_boundary_register(JTAG_DATAIN_DATA);
    jtag_datain_dqs = read_boundary_register(JTAG_DATAIN_DQS);
    jtag_datain_dm = read_boundary_register(JTAG_DATAIN_DM);

    if(jtag_datain_address==0x7f){
        printf("PASS!JTAG_DATAIN_ADDRESS is 0x7f\n");
    }else{
        printf("JTAG_DATAIN_ADDRESS check fail and value is %x\n",jtag_datain_address);
    }
    if(jtag_datain_cs_n==0xf){
        printf("PASS!JTAG_DATAIN_CS_N is 0xf\n");
    }else{
        printf("JTAG_DATAIN_CS_N check fail and value is %x\n",jtag_datain_cs_n);
    }
    if(jtag_datain_cke==0x3){
        printf("PASS!JTAG_DATAIN_CKE is 0x3\n");
    }else{
        printf("JTAG_DATAIN_CKE check fail and value is %x\n",jtag_datain_cke);
    }
    if(jtag_datain_reset_n==0x1){
        printf("PASS!JTAG_DATAIN_RESET_N is 0x1\n");
    }else{
        printf("JTAG_DATAIN_RESET_N check fail and value is %x\n",jtag_datain_reset_n);
    }
    if(jtag_datain_mem_clk_0==0x1){
        printf("PASS!JTAG_DATAIN_MEM_CLK_0 is 0x1\n");
    }else{
        printf("JTAG_DATAIN_MEM_CLK_0 check fail and value is %x\n",jtag_datain_mem_clk_0);
    }
    if(jtag_datain_mem_clk_1==0x1){
        printf("PASS!JTAG_DATAIN_MEM_CLK_1 is 0x1\n");
    }else{
        printf("JTAG_DATAIN_MEM_CLK_1 check fail and value is %x\n",jtag_datain_mem_clk_1);
    }
    if(jtag_datain_data==0xffffffff){
        printf("PASS!JTAG_DATAIN_DATA is 0xffffffff\n");
    }else{
        printf("JTAG_DATAIN_DATA check fail and value is %x\n",jtag_datain_data);
    }
    if(jtag_datain_dqs==0xf){
        printf("PASS!JTAG_DATAIN_DQS is 0xf\n");
    }else{
        printf("JTAG_DATAIN_DQS check fail and value is %x\n",jtag_datain_dqs);
    }
    if(jtag_datain_dm==0xf){
        printf("PASS!JTAG_DATAIN_DM is 0xf\n");
    }else{
        printf("JTAG_DATAIN_DM check fail and value is %x\n",jtag_datain_dm);
    }

    write_boundary_register(JTAG_DATAOUT_ADDRESS,0x0);
    write_boundary_register(JTAG_DATAOUT_CS_N,0x0);
    write_boundary_register(JTAG_DATAOUT_CKE,0x0);
    write_boundary_register(JTAG_DATAOUT_RESET_N,0x0);
    write_boundary_register(JTAG_DATAOUT_MEM_CLK_0,0x0);
    write_boundary_register(JTAG_DATAOUT_MEM_CLK_1,0x0);
    write_boundary_register(JTAG_DATAOUT_DATA,0x0);
    write_boundary_register(JTAG_DATAOUT_DQS,0x0);
    write_boundary_register(JTAG_DATAOUT_DM,0x0);
}
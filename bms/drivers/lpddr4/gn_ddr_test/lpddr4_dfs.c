#include "../lpddr4_common.h"
#ifdef CONFIG_E906
#define DDR_TEST_BASE 0x40000000
#else
#define DDR_TEST_BASE 0x100000000
#endif

void lpddr4_timing_set(uint32_t freq){
    uint32_t t_sr,t_xp,t_ccd,t_rtp,t_rcd;
    float cycle=1000/freq;//ns unit
    //trc,txsr
    t_sr = clk_max(15,3*cycle);
    t_xp = clk_max(7.5,5*cycle);
    t_ccd = 8;
    t_rtp = clk_max(7.5,8*cycle);
    t_rcd = clk_max(18,4*cycle);
    printf("t_sr: %d, t_xp: %d, t_ccd: %d, t_rtp: %d, t_rcd: %d\n",t_sr,t_xp,t_ccd,t_rtp,t_rcd);
}

void phy_freq_sel(uint32_t cntrl_freq_change_req_type){
    uint32_t freq_sel = cntrl_freq_change_req_type;
    uint32_t reg_value = 0;

    reg_value = (read_register(0x00005400)&(~(0x3)))|(freq_sel);
    write_register(0x00005400,reg_value);//phy_freq_sel
    reg_value = (read_register(0x00005404)&(~(0x3<<16)))|(freq_sel<<16);
    write_register(0x00005404,reg_value);//phy_freq_sel_index
    reg_value = read_register(0x00005404)&(~(0x1<<8));
    write_register(0x00005404,reg_value);//phy_freq_sel_multicast_en

    // for(i=0;i<3;i++){
    //     reg_value = read_register(0x00004018 + i*0x400)&(~(0x1))|(0x1);
    //     write_register(0x00004018 + i*0x400,reg_value);//phy_freq_sel
    // }
}

void phy_clk_dqs_slave_dly(void){

}

void phy_wrdq_slave_dly(uint32_t dq0_dly,uint32_t dq1_dly,uint32_t dq2_dly,uint32_t dq3_dly,
                        uint32_t dq4_dly,uint32_t dq5_dly,uint32_t dq6_dly,uint32_t dq7_dly,uint32_t dm_dly){
    uint32_t reg_value = 0;
    uint32_t offset=0;

    for(offset=0;offset <4;offset++){
        reg_value = (read_register(0x000041cc + offset*0x400)&(~(0x7ff)))|(dq0_dly);
        write_register(0x000041cc + offset*0x400,reg_value);//phy_clk_wrdq0_slave_delay_0
        reg_value = (read_register(0x000041cc + offset*0x400)&(~(0x7ff<<16)))|(dq1_dly<<16);
        write_register(0x000041cc + offset*0x400,reg_value);//phy_clk_wrdq1_slave_delay_0
        reg_value = (read_register(0x000041d0 + offset*0x400)&(~(0x7ff)))|(dq2_dly);
        write_register(0x000041d0 + offset*0x400,reg_value);//phy_clk_wrdq2_slave_delay_0
        reg_value = (read_register(0x000041d0 + offset*0x400)&(~(0x7ff<<16)))|(dq3_dly<<16);
        write_register(0x000041d0 + offset*0x400,reg_value);//phy_clk_wrdq3_slave_delay_0
        reg_value = (read_register(0x000041d4 + offset*0x400)&(~(0x7ff)))|(dq4_dly);
        write_register(0x000041d4 + offset*0x400,reg_value);//phy_clk_wrdq4_slave_delay_0
        reg_value = (read_register(0x000041d4 + offset*0x400)&(~(0x7ff<<16)))|(dq5_dly<<16);
        write_register(0x000041d4 + offset*0x400,reg_value);//phy_clk_wrdq5_slave_delay_0
        reg_value = (read_register(0x000041d8 + offset*0x400)&(~(0x7ff)))|(dq6_dly);
        write_register(0x000041d8 + offset*0x400,reg_value);//phy_clk_wrdq6_slave_delay_0
        reg_value = (read_register(0x000041d8 + offset*0x400)&(~(0x7ff<<16)))|(dq7_dly<<16);
        write_register(0x000041d8 + offset*0x400,reg_value);//phy_clk_wrdq7_slave_delay_0
        reg_value = (read_register(0x000041dc + offset*0x400)&(~(0x7ff)))|(dm_dly);
        write_register(0x000041dc + offset*0x400,reg_value);//phy_clk_wrdm_slave_delay_0
    }
}

void phy_rddq_slave_dly_dfs(void){
    uint32_t reg_value = 0;
    uint32_t offset = 0;
    reg_value = (read_register(0x00004164 + offset)&(~(0x3ff)))|(0);
    write_register(0x00004164 + offset,reg_value);//phy_rddq0_slave_delay
    reg_value = (read_register(0x00004164 + offset)&(~(0x3ff<<16)))|(0<<16);
    write_register(0x00004164 + offset,reg_value);//phy_rddq1_slave_delay
    reg_value = (read_register(0x00004168 + offset)&(~(0x3ff)))|(0);
    write_register(0x00004168 + offset,reg_value);//phy_rddq2_slave_delay
    reg_value = (read_register(0x00004168 + offset)&(~(0x3ff<<16)))|(0<<16);
    write_register(0x00004168 + offset,reg_value);//phy_rddq3_slave_delay
    reg_value = (read_register(0x0000416c + offset)&(~(0x3ff)))|(0);
    write_register(0x0000416c + offset,reg_value);//phy_rddq4_slave_delay
    reg_value = (read_register(0x0000416c + offset)&(~(0x3ff<<16)))|(0<<16);
    write_register(0x0000416c + offset,reg_value);//phy_rddq5_slave_delay
    reg_value = (read_register(0x00004170 + offset)&(~(0x3ff)))|(0);
    write_register(0x00004170 + offset,reg_value);//phy_rddq6_slave_delay
    reg_value = (read_register(0x00004170 + offset)&(~(0x3ff<<16)))|(0<<16);
    write_register(0x00004170 + offset,reg_value);//phy_rddq7_slave_delay
    reg_value = (read_register(0x00004174)&(~(0x3ff)))|(0);
    write_register(0x00004174,reg_value);//phy_rddm_slave_delay
}

void disable_update_tvrcg(void){
    uint32_t reg_value = 0;
    reg_value = read_register(0x000002fc)&(~(0x1<<16));
    write_register(0x000002fc,reg_value);//disable_update_tvrcg
}

void overwrite_mr_register(uint32_t cntrl_freq_change_req_type){
    uint32_t reg_value = 0;
    if(cntrl_freq_change_req_type==0){

    }else if(cntrl_freq_change_req_type==1){
        reg_value = (read_register(0x00000360)&(~(0xff<<8)))|(0x5d<<8);
        write_register(0x00000360,reg_value);//mr14_f1_0
        reg_value = (read_register(0x00000364)&(~(0xff)))|(0x5d);
        write_register(0x00000364,reg_value);//mr14_f1_1
    }else if(cntrl_freq_change_req_type==2){

    }
}

void override_timimg_param(uint32_t cntrl_freq_change_req_type){
    if(cntrl_freq_change_req_type==0){

    }else if(cntrl_freq_change_req_type==1){

    }else if(cntrl_freq_change_req_type==2){

    }
}

void fsp_param_conf(void){
    uint32_t reg_value = 0;
    reg_value = (read_register(0x0000037c)&(~(0x3<<24)))|(0<<24);
    write_register(0x0000037c,reg_value);//fsp0_frc

    reg_value = (read_register(0x0000037c)&(~(0x1<<8)))|(1<<8);
    write_register(0x0000037c,reg_value);//fsp0_frc_valid

    reg_value = (read_register(0x00000380)&(~(0x3)))|(1<<0);
    write_register(0x00000380,reg_value);//fsp1_frc

    reg_value = (read_register(0x0000037c)&(~(0x1<<16)))|(1<<16);
    write_register(0x0000037c,reg_value);//fsp1_frc_valid

    reg_value = (read_register(0x0000037c)&(~(0x1)))|(1<<0);
    write_register(0x0000037c,reg_value);//fsp_wr_current

    reg_value = (read_register(0x00000378)&(~(0x1<<24)))|(0<<24);
    write_register(0x00000378,reg_value);//fsp_op_current

    reg_value = (read_register(0x00000370)&(~(0x1<<24)))|(1<<24);
    write_register(0x00000370,reg_value);//mr_fsp_data_valid_f0
    
    reg_value = (read_register(0x00000374)&(~(0x1)))|(1<<0);
    write_register(0x00000374,reg_value);//mr_fsp_data_valid_f1
}

void enter_dfs(void){
    uint32_t reg_value = 0;
    uint32_t cntrl_freq_change_req_type = 0;
    uint32_t lp_ext_ack = 0;
    uint32_t lp_ext_done = 1;
    uint32_t lp_ext_resp = 1;
    
    reg_value = (read_apbmux_register(0x00000008)&(~(0x3f)))|(0x4);
    write_apbmux_register(0x00000008,reg_value);//set lp_ext_cmd
    reg_value = (read_apbmux_register(0x00000008)&(~(3<<7)))|(1<<7);
    write_apbmux_register(0x00000008,reg_value);//assert lp_fc_reg_copy
    reg_value = (read_apbmux_register(0x00000008)&(~(1<<9)))|(1<<9);
    write_apbmux_register(0x00000008,reg_value);//assert lp_ext_req
    while(!lp_ext_ack){
        lp_ext_ack = read_apbmux_register(0x00000010)&(0x1);
    }
    reg_value = read_apbmux_register(0x00000008)&(~(0x1<<6));
    write_apbmux_register(0x00000008,reg_value|(0x1<<6));//lp_ext_cmd_strb to 1
    write_apbmux_register(0x00000008,reg_value);//lp_ext_cmd_strb to 0
    while(lp_ext_done){
        lp_ext_done = (read_apbmux_register(0x00000010)>>1)&0x1;
    }
    printf("start dfs\n");
    while(1){
        cntrl_freq_change_req_type = (read_apbmux_register(0x00000014)>>23)&0x3;
        if(cntrl_freq_change_req_type==0){
            lpddr4_pll_freq(33);
            udelay(1);
            reg_value = read_apbmux_register(0x00000004)&(~0x1);
            write_apbmux_register(0x00000004,reg_value|0x1);//cntrl_freq_change_req_ack to 1
            write_apbmux_register(0x00000004,reg_value);//cntrl_freq_change_req_ack to 0
            break;
        }else if(cntrl_freq_change_req_type==1){
            lpddr4_pll_freq(533);
            udelay(1);
            reg_value = read_apbmux_register(0x00000004)&(~0x1);
            write_apbmux_register(0x00000004,reg_value|0x1);//cntrl_freq_change_req_ack to 1
            write_apbmux_register(0x00000004,reg_value);//cntrl_freq_change_req_ack to 0
            break;
        }else if(cntrl_freq_change_req_type==2){
            lpddr4_pll_freq(1066);
            udelay(1);
            reg_value = read_apbmux_register(0x00000004)&(~0x1);
            write_apbmux_register(0x00000004,reg_value|0x1);//cntrl_freq_change_req_ack to 1
            write_apbmux_register(0x00000004,reg_value);//cntrl_freq_change_req_ack to 0
            break;
        }
    }
    
    while(!lp_ext_done){
        lp_ext_done = (read_apbmux_register(0x00000010)>>1)&0x1;
    }
    printf("dfs done\n");
    lp_ext_resp = (read_apbmux_register(0x00000010)>>2)&0x1;
    if(lp_ext_resp){
        printf("dfs error\n");
    }
    reg_value = read_apbmux_register(0x00000008)&(~(1<<9));
    write_apbmux_register(0x00000008,reg_value);//deassert lp_ext_req
}

void lpddr4_dfs_test(void){
    volatile uint32_t* addr64_ptr;
    uint32_t i, rd_val;
    uint32_t freq_sel = 1;
    axi_init();
#ifndef CONFIG_COMPILE_ASIC
    sys_lpddr4_start();
#endif
    overwrite_mr_register(freq_sel);
    phy_freq_sel(freq_sel);
    phy_wrdq_slave_dly(0x500,0x500,0x500,0x500,0x500,0x500,0x500,0x500,0x500);\
    //disable_update_tvrcg();
    lp_aref_enable(0);
    fsp_param_conf();
    enter_dfs();
    udelay(1);
    //phy_rddq_slave_dly(1);
    udelay(1);
    // reset_lp_conf();
    // srefresh_exit_no_refresh(1);
    // lpi_sr_short_wakeup_fN();
    // //lpddr4_enter_srpd(ENTER_SELF_REFRESH_POWER_DOWN_LONG_WITH_MEMORY_AND_CONTROLLER_CLOCK_GATING,2);
    // lpddr4_exit_pd(2);
    lp_aref_enable(1);
    
    for(i=0; i<32; i=i+1){
        addr64_ptr=(volatile uint32_t*)(DDR_TEST_BASE+i*4);
        *(addr64_ptr) = 0x12340+i;
    }
#if defined(CONFIG_E906)
    udelay(1);
#else
    asm("sync.is");
#endif
    for(i=0; i<32; i=i+1){
        addr64_ptr=(volatile uint32_t*)(DDR_TEST_BASE+i*4);
        rd_val = *(addr64_ptr) ;
        if(rd_val != (0x12340+i))
            printf("MPU read error!\n"); 
    }
}

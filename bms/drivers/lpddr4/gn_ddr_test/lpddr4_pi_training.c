#include "../lpddr4_common.h"

extern volatile int def_march_c_test;
extern volatile int def_prbs_test;

// void phy_dq_tsel_wr_timing(void){
//     uint32_t phy_dq_tsel_wr_timing[] = {
//         0x0000417c , 0x51516051,
//         0x0000457c , 0x51516051,
//         0x0000497c , 0x51516051,
//         0x00004d7c , 0x51516051,
//         0xffffffff , 0xffffffff
//     };
//     write_register_array(phy_dq_tsel_wr_timing);
// }

// void phy_vref_training_ctrl(void){
//     uint32_t phy_vref_training_ctrl[] = {
//         0x00004148 , 0x20000025,
//         0x00004548 , 0x20000025,
//         0x00004948 , 0x20000025,
//         0x00004d48 , 0x20000025,
//         0xffffffff , 0xffffffff
//     };
//     write_register_array(phy_vref_training_ctrl);
// }

void pi_tdfi_calvl_cc(uint32_t pi_tdfi_calvl_cc_timing){
    uint32_t reg_value = 0;
    reg_value = (read_register(0x000022b8)&(~(0x3ff))) | pi_tdfi_calvl_cc_timing;
    write_register(0x000022b8 , reg_value);
    reg_value = (read_register(0x000022bc)&(~(0x3ff))) | pi_tdfi_calvl_cc_timing;
    write_register(0x000022bc , reg_value);
    reg_value = (read_register(0x000022c0)&(~(0x3ff))) | pi_tdfi_calvl_cc_timing;
    write_register(0x000022c0 , reg_value);
}

void phy_vref_training_ctrl(void){
    uint32_t phy_vref_training_ctrl[] = {
        0x0000417c , 0x51516051,
        0x00004148 , 0x20000025,
        0x0000457c , 0x51516051,
        0x00004548 , 0x20000025,
        0x0000497c , 0x51516051,
        0x00004948 , 0x20000025,
        0x00004d7c , 0x51516051,
        0x00004d48 , 0x20000025,
        0xffffffff , 0xffffffff
    };
    write_register_array(phy_vref_training_ctrl);
}

void phy_400_reg_init(void){
    uint32_t phy_400_reg_init[] = {
        0x00005404 , 0x00000000,
        0x00005404 , 0x00000000,
        0x00004210 , 0x00010000,
        0x000041b4 , 0x00000203,
        0x000041c0 , 0x00012010,
        0x00004188 , 0x00c0c001,
        0x00004190 , 0x000e020d,
        0x0000419c , 0x010c043e,
        0x0000417c , 0x51516051,
        0x00004610 , 0x00010000,
        0x000045b4 , 0x00000203,
        0x000045c0 , 0x00012010,
        0x00004588 , 0x00c0c001,
        0x00004590 , 0x000e020d,
        0x0000459c , 0x010c043e,
        0x0000457c , 0x51516051,
        0x00004a10 , 0x00010000,
        0x000049b4 , 0x00000203,
        0x000049c0 , 0x00012010,
        0x00004988 , 0x00c0c001,
        0x00004990 , 0x000e020d,
        0x0000499c , 0x010c043e,
        0x0000497c , 0x51516051,
        0x00004e10 , 0x00010000,
        0x00004db4 , 0x00000203,
        0x00004dc0 , 0x00012010,
        0x00004d88 , 0x00c0c001,
        0x00004d90 , 0x000e020d,
        0x00004d9c , 0x010c043e,
        0x00004d7c , 0x51516051,
        0x000055b0 , 0x00001342,
        0x000055b0 , 0x00011342,
        0x000054b8 , 0x07020101,
        0x00005404 , 0x00000100,
        0xffffffff , 0xffffffff
    };
    write_register_array(phy_400_reg_init);
}

void boot_cal_clk(void){
    uint32_t boot_cal_clk[] = {
        0x00005648 , 0x20040000,
        0x00005508 , 0x00000008,
        0xffffffff , 0xffffffff
    };
    write_register_array(boot_cal_clk);
}

void pi_reg_init(void){
    uint32_t pi_reg_init[] = {
        0x000021a4 , 0x00000100,
        0x00000e3c , 0x000ff800,
        0x00000e40 , 0x000ff800,
        0x00000e44 , 0x000ff800,
        0x00000e48 , 0x000ff800,
        0x00000e50 , 0x00200000,
        0x00000e60 , 0x000ff800,
        0x00000e64 , 0x000ff800,
        0x00000e68 , 0x000ff800,
        0x00000e6c , 0x000ff800,
        0x00000e74 , 0x00200000,
        0x00000e84 , 0x000ff800,
        0x00000e88 , 0x000ff800,
        0x00000e8c , 0x000ff800,
        0x00000e90 , 0x000ff800,
        0x00000e98 , 0x00200000,
        0x00002110 , 0x0204000a,
        0x00002120 , 0x00010e00,
        0x000022f0 , 0x1e1a1e01,
        0x00002110 , 0x0201000a,
        0x00002110 , 0x0101000a,
        0x000022f0 , 0x1e1a0101,
        0x0000232c , 0x1e010056,
        0x00002128 , 0x00000201,
        0x00002128 , 0x00000101,
        0x0000232c , 0x01010056,
        0x000022f0 , 0x1e010101,
        0x00002110 , 0x0101000a,
        0x00002110 , 0x0101000a,
        0x000022f0 , 0x01010101,
        0x00002338 , 0x1e010057,
        0x00002128 , 0x00000101,
        0x00002128 , 0x00000101,
        0x00002338 , 0x01010057,
        0x000022f4 , 0x01011e01,
        0x00002110 , 0x0101000a,
        0x00002110 , 0x0101000a,
        0x000022f4 , 0x01010101,
        0x00002344 , 0x1e01005b,
        0x00002128 , 0x00000101,
        0x00002128 , 0x00000101,
        0x00002344 , 0x0101005b,
        0x00004088 , 0x00071040,
        0x00004488 , 0x00071040,
        0x00004888 , 0x00071040,
        0x00004c88 , 0x00071040,
        0x00002010 , 0x00000001,
        0xffffffff , 0xffffffff
    };
    write_register_array(pi_reg_init);
}

void sw_master_mode(void){
    uint32_t sw_master_mode[] = {
        0x00004594 , 0x00000304,
        0x00004994 , 0x00000304,
        0x00004d94 , 0x00000304,
        0xffffffff , 0xffffffff
    };//mr13_conf
    write_register_array(sw_master_mode);
}

void mr_conf(void){
    write_register(0x00004194 , 0x00000304);//mr13
}

void upd_ctrlupd_timeout(void){
    uint32_t upd_ctrlupd_timeout[] = {
        0x000004f4 , 0x01010100,
        0x000001c4 , 0x00008010,
        0x000001d0 , 0x00040000,
        0x000001d8 , 0x00000000,
        0x000001c8 , 0x00050000,
        0x000001d0 , 0x00000000,
        0x000001dc , 0x00050000,
        0xffffffff , 0xffffffff
    };
    write_register_array(upd_ctrlupd_timeout);
}

void pi_dram_int_en(void){
    uint32_t pi_dram_int_en[] = {
        0x00002010 , 0x00000001,
        0x00000074 , 0x01000110,
        0x000021a4 , 0x00000100,
        0xffffffff , 0xffffffff
    };
    write_register_array(pi_dram_int_en);
}

void pi_start(void){
    write_register(0x00002000 , 0x00000b01);
}

void start(void){
    uint32_t start[] = {
        0x000004cc , 0x00000101,
        0x000004f0 , 0x00000001,
        0x00005520 , 0x01000000,
        0x00005648 , 0x20040000,
        0x00005508 , 0x00000008,
        0x000003b0 , 0x00000000,
        0x00000074 , 0x01000110,
        0x00002010 , 0x00000001,
        0x000021a4 , 0x00000100,
        0x00000000 , 0x10460b01,
        0xffffffff , 0xffffffff
    };
    write_register_array(start);
}

void pi_init_lvl_en(void){
    write_register(0x00002010 , 0x00000001);
}

void ctrlupd_req_per_aref_en_addr(void){
    write_register(0x000004f4 , 0x01010101);
}

void upd_ctrlupd_threshold_en(void){
    uint32_t upd_ctrlupd_norm_threshold_en[] = {
        0x000001c4 , 0x00038010,
        0x000001d0 , 0x00000003,
        0x000001d8 , 0x00030000,
        0xffffffff , 0xffffffff
    };
    write_register_array(upd_ctrlupd_norm_threshold_en);

    uint32_t upd_ctrlupd_high_threshold_en[] = {
        0x000001c8 , 0x00050003,
        0x000001d0 , 0x00030003,
        0x000001dc , 0x00050003,
        0xffffffff , 0xffffffff
    };
    write_register_array(upd_ctrlupd_high_threshold_en);
}

void pi_int_ack(void){
    write_register(0x00002170 , 0x00000000);
}

uint32_t pi_monitor(uint32_t monitor_source,uint32_t monitor_func){
    uint32_t monitor_result = 0;
    uint32_t reg_value = 0;
    uint32_t freq_change_req = 0;
    uint32_t freq_change_req_type = 4;
    uint32_t pll_lock = 0;
    reg_value = (read_register(0x000021cc)&(0x0))|(monitor_func<<8)|(monitor_source);
    write_register(0x000021cc,reg_value);
    while(!monitor_result){
        monitor_result = (read_register(0x000021cc)>>23)&(0x1);
        freq_change_req = (read_apbmux_register(0x0000014)>>21)&(0x1);
        if(freq_change_req){
            freq_change_req_type = (read_apbmux_register(0x00000014)>>16)&(0x1f);
            if(freq_change_req_type == 0){
                lpddr4_pll_freq(33);
                write_apbmux_register(0x00000004,0x2);
                ndelay(50);
                write_apbmux_register(0x00000004,0x0);
                while(!pll_lock){
                    pll_lock = read_register(0x000054a0)&0x1;
                }
                pll_lock = 0;
                printf("change freq to 33Mhz\n");
            }else if(freq_change_req_type == 1){
                lpddr4_pll_freq(533);
                write_apbmux_register(0x00000004,0x2);
                ndelay(50);
                write_apbmux_register(0x00000004,0x0);
                while(!pll_lock){
                    pll_lock = read_register(0x000054a0)&0x1;
                }
                pll_lock = 0;
                printf("change freq to 533Mhz\n");
            }else if(freq_change_req_type == 2){
                lpddr4_pll_freq(2133);
                write_apbmux_register(0x00000004,0x2);
                ndelay(50);
                write_apbmux_register(0x00000004,0x0);
                while(!pll_lock){
                    pll_lock = read_register(0x000054a0)&0x1;
                }
                pll_lock = 0;
                printf("change freq to 2133Mhz\n");
            }else{
                printf("freq_change_req_type err\n");
            }
        }
        // if(cnt%100000){
        //     printf("Wait for training finished\n");
        // }
        // cnt++;
    }
    //cnt = 0;
    printf("PI Initial Training Finished\n");
    return 0;
}

void addr_check(void){
    uint32_t op_done = 0;
    uint32_t pi_bist_result = 0;
    uint32_t cnt = 0;
    printf("Bist addr check start\n");
    write_register(0x0000270c , 0x00000000);//pi bist start address
    write_register(0x00002710 , 0x0000aa00);//pi_bist_init_pattern
    write_register(0x00002708 , 0x00010008);//pi bist end addr space
    write_register(0x00002714 , 0x00000000);//pi_bist_data_mask[0:31]
    write_register(0x00002718 , 0x00000000);//pi_bist_data_mask[32:63]
    write_register(0x00002708 , 0x00010008);//pi_bist_addr_check addr/pi_bist_data_check addr/pi_addr_space
    write_register(0x00002708 , 0x00010008);
    if (def_march_c_test)
	write_register(0x0000276c , 0x00000100);
    else if (def_prbs_test)
	write_register(0x0000276c , 0x00000300);
    write_register(0x00002704 , 0x00000100);//pi_bist_go
    while(!op_done){
        op_done = (read_register(0x0000216c)>>13)&0x1;
        cnt++;
        if(cnt%100000){
            printf("wait for pi_addr_bist_check\n");
        }
    }
    cnt = 0;
    write_register(0x00002170 , 0x00002000);//clear pi int
    pi_bist_result = (read_register(0x00002704)>>17)&0x1;
    if(pi_bist_result){
        printf("bist addr check pass!\n");
    }else{
        printf("bist addr check fail!\n");
        printf("Error:\n");
        printf("PI_BIST_FAIL_DATA=%x\n",read_register(0x000026f0));
        printf("PI_BIST_EXP_DATA=%x\n",read_register(0x000026e0));
        printf("PI_BIST_FAIL_ADDR=%x%x\n",read_register(0x00002704)&0x3,read_register(0x00002700));
    }
    write_register(0x00002704 , 0x00020000);//pi_bist_go_close
}

void data_check(void){
    uint32_t op_done = 0;
    uint32_t pi_bist_result = 0;
    uint32_t cnt = 0;
    printf("Bist data check start\n");
    write_register(0x0000270c , 0x00000000);
    write_register(0x00002710 , 0x0000aa00);
    write_register(0x00002708 , 0x00010008);
    write_register(0x00002714 , 0x00000000);
    write_register(0x00002718 , 0x00000000);
    write_register(0x00002708 , 0x00000008);
    write_register(0x00002708 , 0x00000108);
    if (def_march_c_test)
	write_register(0x0000276c , 0x00000100);
    else if (def_prbs_test)
	write_register(0x0000276c , 0x00000300);
    write_register(0x00002704 , 0x00000100);
    while(!op_done){
        op_done = (read_register(0x0000216c)>>13)&0x1;
        cnt++;
        if(cnt%100000){
            printf("wait for pi_data_bist_check\n");
        }
    }
    cnt = 0;
    write_register(0x00002170 , 0x00002000);//clear pi int
    pi_bist_result = (read_register(0x00002704)>>16)&0x1;
    if(pi_bist_result){
        printf("bist data check pass!\n");
    }else{
        printf("bist data check fail!\n");
        printf("Error:\n");
        printf("PI_BIST_FAIL_DATA=%x\n",read_register(0x000026f0));
        printf("PI_BIST_EXP_DATA=%x\n",read_register(0x000026e0));
        printf("PI_BIST_FAIL_ADDR=%x%x\n",read_register(0x00002704)&0x3,read_register(0x00002700));
    }
    write_register(0x00002704 , 0x00020000);//pi_bist_go_close
}

void lpddr4_bist_test(void)
{
	addr_check();
	data_check();
    printf("Bist test pass\n");
}

void lpddr4_pi_init_and_training(void){
    //phy_dq_tsel_wr_timing();
    #ifdef POST_SS_SET
        pi_tdfi_calvl_cc(0x10);
    #endif
    lpddr4_pll_freq(33);
    phy_vref_training_ctrl();
    phy_400_reg_init();
    boot_cal_clk();
    pi_reg_init();
    sw_master_mode();
    mr_conf();
    upd_ctrlupd_timeout();
    pi_dram_int_en();
    pi_start();
    start();
    pi_init_lvl_en();
    printf("start pi training\n");
    pi_monitor(0,1);
    ctrlupd_req_per_aref_en_addr();
    upd_ctrlupd_threshold_en();
    udelay(1);
    pi_int_ack();
    addr_check();
    data_check();
}

void lpddr4_training_and_dfs(void){
    //uint32_t reg_value;
    volatile unsigned int* addr64_ptr;
    uint32_t rd_val;

    lpddr4_pll_freq(33);
    phy_vref_training_ctrl();
    phy_400_reg_init();
    boot_cal_clk();
    pi_reg_init();
    sw_master_mode();
    mr_conf();
    upd_ctrlupd_timeout();
    pi_dram_int_en();
    pi_start();
    start();
    pi_init_lvl_en();
    printf("start pi training\n");
    pi_monitor(0,1);
    ctrlupd_req_per_aref_en_addr();
    upd_ctrlupd_threshold_en();
    udelay(1);
    pi_int_ack();
    //reg_value = read_register();//WL


    MA_OUTW(0xc30f0000+0x28, 0x0);       // enable e906/e920 access dram
    MA_OUTW(0xc30f0000+0x100000+0x28, 0x0);       // enable e906/e920 access dram

    //set sysmap for c920,set to un-cachable/ukn-bufferable
    MA_OUTW(0xc2f08c2c,0x10000);       	  // left-shift 3bit
    MA_OUTW(0xc2f08cb4,0x00020202);       // left-shift 3bit

    //set sysmap for e906,set to un-cachable/ukn-bufferable
    MA_OUTW(0xeffff000+0x14,0x0);       // left-shift 3bit
    MA_OUTW(0xeffff000+0x18,0x0);       // left-shift 3bit
    MA_OUTW(0xeffff000+0x1c,0x0);       // left-shift 3bit
    MA_OUTW(0xeffff000+0x24,0x0);       // left-shift 3bit

    udelay(1);

    addr64_ptr=(volatile unsigned int*)0x110000000;//bit 26
    *(addr64_ptr) = 0x8888;

    addr64_ptr=(volatile unsigned int*)0x110000000;
    rd_val = *(addr64_ptr) ;
    if(rd_val != (0x8888))
        printf("MPU read error!\n");

    addr64_ptr=(volatile unsigned int*)0x120000000;//bit 27
    *(addr64_ptr) = 0x9999;

    addr64_ptr=(volatile unsigned int*)0x120000000;
    rd_val = *(addr64_ptr) ;
    if(rd_val != (0x9999))
        printf("MPU read error!\n");

    addr64_ptr=(volatile unsigned int*)0x140000000;//bit 28
    *(addr64_ptr) = 0xaaaa;

    addr64_ptr=(volatile unsigned int*)0x140000000;
    rd_val = *(addr64_ptr) ;
    if(rd_val != (0xaaaa))
        printf("MPU read error!\n");

    addr64_ptr=(volatile unsigned int*)0x180000000;//bit 29
    *(addr64_ptr) = 0xbbbb;

    addr64_ptr=(volatile unsigned int*)0x180000000;
    rd_val = *(addr64_ptr) ;
    if(rd_val != (0xbbbb))
        printf("MPU read error!\n");

    addr64_ptr=(volatile unsigned int*)0x200000000;//bit 30
    *(addr64_ptr) = 0xcccc;

    addr64_ptr=(volatile unsigned int*)0x200000000;
    rd_val = *(addr64_ptr) ;
    if(rd_val != (0xcccc))
        printf("MPU read error!\n");

    addr64_ptr=(volatile unsigned int*)0x300000000;//bit 31
    *(addr64_ptr) = 0xcccc;

    addr64_ptr=(volatile unsigned int*)0x300000000;
    rd_val = *(addr64_ptr) ;
    if(rd_val != (0xcccc))
        printf("MPU read error!\n");
}

#include "../lpddr4_common.h"

extern void phy_vref_training_ctrl(void);
extern void phy_400_reg_init(void);
extern void boot_cal_clk(void);
extern void pi_reg_init(void);
extern void sw_master_mode(void);
extern void mr_conf(void);
extern void upd_ctrlupd_timeout(void);
extern void pi_dram_int_en(void);
extern void pi_start(void);
extern void start(void);
extern void pi_init_lvl_en(void);
extern void ctrlupd_req_per_aref_en_addr(void);
extern void upd_ctrlupd_threshold_en(void);
extern void pi_int_ack(void);
extern uint32_t pi_monitor(uint32_t monitor_source,uint32_t monitor_func);
extern void addr_check(void);
extern void data_check(void);
extern void pi_tdfi_calvl_cc(uint32_t pi_tdfi_calvl_cc_timing);

void pi_lvl_enable(pi_lvl_en_t pi_lvl_en){
    uint32_t reg_value;
    reg_value = (read_register(0x21a4)&(~(1<<8)))|(pi_lvl_en.pi_dram_init_en<<8);
    write_register(0x21a4,reg_value);
    reg_value = (read_register(0x2010)&(~(0x1)))|(pi_lvl_en.pi_init_lvl_en);
    write_register(0x2010,reg_value);

    reg_value = (read_register(0x22c4)&(~0x3))|(pi_lvl_en.pi_calvl_en_f0);
    write_register(0x22c4,reg_value);
    reg_value = (read_register(0x22c4)&(~(3<<8)))|(pi_lvl_en.pi_calvl_en_f1<<8);
    write_register(0x22c4,reg_value);
    reg_value = (read_register(0x22c4)&(~(3<<16)))|(pi_lvl_en.pi_calvl_en_f2<<16);
    write_register(0x22c4,reg_value);

    reg_value = (read_register(0x227c)&(~(3<<16)))|(pi_lvl_en.pi_wrlvl_en_f0<<16);
    write_register(0x227c,reg_value);
    reg_value = (read_register(0x227c)&(~(3<<24)))|(pi_lvl_en.pi_wrlvl_en_f1<<24);
    write_register(0x227c,reg_value);
    reg_value = (read_register(0x2280)&(~(0x3)))|(pi_lvl_en.pi_wrlvl_en_f2);
    write_register(0x2280,reg_value);

    reg_value = (read_register(0x2298)&(~(3<<24)))|(pi_lvl_en.pi_rdlvl_gate_en_f0<<24);
    write_register(0x2298,reg_value);
    reg_value = (read_register(0x229c)&(~(3<<8)))|(pi_lvl_en.pi_rdlvl_gate_en_f1<<8);
    write_register(0x229c,reg_value);
    reg_value = (read_register(0x229c)&(~(3<<24)))|(pi_lvl_en.pi_rdlvl_gate_en_f2<<24);
    write_register(0x229c,reg_value);

    reg_value = (read_register(0x2298)&(~(3<<16)))|(pi_lvl_en.pi_rdlvl_en_f0<<16);
    write_register(0x2298,reg_value);
    reg_value = (read_register(0x229c)&(~(0x3)))|(pi_lvl_en.pi_rdlvl_en_f1);
    write_register(0x229c,reg_value);
    reg_value = (read_register(0x229c)&(~(3<<16)))|(pi_lvl_en.pi_rdlvl_en_f2<<16);
    write_register(0x229c,reg_value);

    reg_value = (read_register(0x2330)&(~(3<<8)))|(pi_lvl_en.pi_wdqlvl_en_f0<<8);
    write_register(0x2330,reg_value);
    reg_value = (read_register(0x233c)&(~(3<<8)))|(pi_lvl_en.pi_wdqlvl_en_f1<<8);
    write_register(0x233c,reg_value);
    reg_value = (read_register(0x2348)&(~(3<<8)))|(pi_lvl_en.pi_wdqlvl_en_f2<<8);
    write_register(0x2348,reg_value);
}

void pi_work_freq_select(uint32_t pi_freq_map,uint32_t work_freq_select){
    uint32_t reg_value;

    reg_value = (read_register(0x2034) & (~0xffffffff)) | (pi_freq_map);//pi_freq_map
    write_register(0x2034,reg_value);

    reg_value = (read_register(0x2030) & (~0x1f<<8)) | (work_freq_select<<8);
    write_register(0x2030,reg_value);

    if(work_freq_select == 0){
        reg_value = (read_register(0x00000120) & (~0x3ff)) | (0x67);
        write_register(0x00000120,reg_value);//trfc_f0
    }else if(work_freq_select == 1){
        reg_value = (read_register(0x00000128) & (~0x3ff)) | (0x21);
        write_register(0x00000128,reg_value);//trfc_f1
    }else{
        reg_value = (read_register(0x00000130) & (~0x3ff)) | (0x1041);
        write_register(0x00000130,reg_value);//trfc_f2
    }

    if(work_freq_select == 0){
        reg_value = (read_register(0x00000124) & (~0xfffff)) | (0xcf);
        write_register(0x00000124,reg_value);//trfe_f0
    }else if(work_freq_select == 1){
        reg_value = (read_register(0x0000012c) & (~0xfffff)) | (0x48);
        write_register(0x0000012c,reg_value);//trfe_f1
    }else{
        reg_value = (read_register(0x00000134) & (~0xfffff)) | (0x2082);
        write_register(0x00000134,reg_value);//trfe_f2
    }

    if(work_freq_select == 0){
        reg_value = (read_register(0x000000fc) & (~(0xff<<16))) | (0x3<<16);
        write_register(0x000000fc,reg_value);//trcd_f0
    }else if(work_freq_select == 1){
        reg_value = (read_register(0x00000100) & (~0xff)) | (0xa);
        write_register(0x00000100,reg_value);//trcd_f1
    }else{
        reg_value = (read_register(0x00000100) & (~(0xff<<16))) | (0x3<<16);
        write_register(0x00000100,reg_value);//trcd_f2
    }
}

void lpddr4_pi_init_and_training_533(void){
    pi_lvl_en_t pi_lvl_en;

    volatile unsigned int* addr64_ptr;
    uint32_t rd_val;
    uint32_t reg_value = 0;
    printf("PI training 533MHz\n");
    reg_value = (read_register(0x000002c4) & (~0x3)) | (0x1);//init_freq_f1
    write_register(0x000002c4,reg_value);
    reg_value = (read_register(0x000002c4) & (~(0x3<<8))) | (0x1<<8);//init_boot_freq_f1
    write_register(0x000002c4,reg_value);

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
    pi_lvl_en.pi_dram_init_en       = 1;
    pi_lvl_en.pi_init_lvl_en        = 1;
    pi_lvl_en.pi_calvl_en_f0        = 1;
    pi_lvl_en.pi_calvl_en_f1        = 1;
    pi_lvl_en.pi_calvl_en_f2        = 0;
    pi_lvl_en.pi_wrlvl_en_f0        = 1;
    pi_lvl_en.pi_wrlvl_en_f1        = 1;
    pi_lvl_en.pi_wrlvl_en_f2        = 0;
    pi_lvl_en.pi_rdlvl_gate_en_f0   = 1;
    pi_lvl_en.pi_rdlvl_gate_en_f1   = 1;
    pi_lvl_en.pi_rdlvl_gate_en_f2   = 0;
    pi_lvl_en.pi_rdlvl_en_f0        = 1;
    pi_lvl_en.pi_rdlvl_en_f1        = 1;
    pi_lvl_en.pi_rdlvl_en_f2        = 0;
    pi_lvl_en.pi_wdqlvl_en_f0       = 1;
    pi_lvl_en.pi_wdqlvl_en_f1       = 1;
    pi_lvl_en.pi_wdqlvl_en_f2       = 0;
    pi_work_freq_select(0x3,0x1);
    pi_lvl_enable(pi_lvl_en);
    pi_start();
    start();
    pi_init_lvl_en();
    printf("start pi training\n");
    pi_monitor(0,1);
    ctrlupd_req_per_aref_en_addr();
    upd_ctrlupd_threshold_en();
    udelay(1);
    pi_int_ack();

    lpddr4_pll_freq(533);

    addr_check();
    data_check();

    udelay(1);

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

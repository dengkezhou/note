#include "../lpddr4_common.h"

void set_timing_tzqcal_fN(void){
    uint32_t reg_value = 0;
    reg_value = (read_register(0x00000484)&(~0xfff))|(0x37);//tzqcal_f0
    write_register(0x00000484,reg_value);
    reg_value = (read_register(0x0000048c)&(~(0xfff<<16)))|(0x190<<16);//tzqcal_f1
    write_register(0x0000048c,reg_value);
    reg_value = (read_register(0x00000498)&(~0xfff))|(0x855);//tzqcal_f2
    write_register(0x00000498,reg_value);

    reg_value = (read_register(0x00000484)&(~(0x7f<<16)))|(0x2<<16);//tzqlat_f0
    write_register(0x00000484,reg_value);
    reg_value = (read_register(0x00000490)&(~0x7f))|(0xc);//tzqlat_f1
    write_register(0x00000490,reg_value);
    reg_value = (read_register(0x00000498)&(~(0x7f<<16)))|(0x40<<16);//tzqlat_f2
    write_register(0x00000498,reg_value);
}

void manual_zq_cal(void){
    uint32_t reg_value = 0;
    uint32_t zq_req_pending = 1;
    uint32_t cnt = 0;
    reg_value = read_register(0x0000049c)&(~(0xf));//zq_req
    write_register(0x0000049c,reg_value);
    reg_value = (read_register(0x00000498)&(~(0x3<<24)))|(0x3<<24);//zq_sw_req_start_latch_map
    write_register(0x00000498,reg_value);
    reg_value = (read_register(0x0000049c)&(~(0xf)))|(0x3);//zq_req
    write_register(0x0000049c,reg_value);//start_zq
    printf("zq_start\n");
    while(zq_req_pending){
        zq_req_pending = (read_register(0x0000049c)>>8)&(0x1);
        if(cnt%100000){
            printf("wait for zq_start\n");
        }
        cnt++;
    }
    cnt = 0;
    reg_value = (read_register(0x0000049c) & (~(0xf))) | (0x5);//zq_req
    write_register(0x0000049c,reg_value);//latch_zq
     printf("zq_latch\n");
    while(zq_req_pending){
        zq_req_pending = (read_register(0x0000049c)>>8)&(0x1);
        if(cnt%100000){
            printf("wait for zq_latch\n");
        }
        cnt++;
    }
    cnt = 0;
}

void lpddr4_zq_cal(void){
    axi_init();
#ifndef CONFIG_COMPILE_ASIC
    sys_lpddr4_start();
#endif
    set_timing_tzqcal_fN();
    manual_zq_cal();
    printf("zq_cal pass\n");
}
#include "../lpddr4_common.h"
#include "lpddr4_lowpower.h"
#ifdef CONFIG_E906
#define DDR_TEST_BASE 0x40000000
#else
#define DDR_TEST_BASE 0x100000000
#endif

void reset_lp_conf(void){
    //reset auto
    write_register(0x00000294,0);
    write_register(0x00000298,0);
    write_register(0x0000029c,0);
    //reset pcpcs
    write_register(0x000002b0,0);
    write_register(0x000002b4,0);
}

void lp_aref_enable(uint32_t enable){
    uint32_t reg_value = 0;
    if(enable){
        reg_value = read_register(0x00000270) &(~(0x3));//low_power_refresh_disable
        write_register(0x00000270,reg_value);
        reg_value = (read_register(0x0000016c) &(~(0x1<<16)))|(0x1<<16);//pbr_cont_req_en
        write_register(0x0000016c,reg_value);
        reg_value = (read_register(0x00000168) &(~(0xf<<24)))|(0xf<<24);//pbr_mode_en
        write_register(0x00000168,reg_value);
        reg_value = (read_register(0x0000011c) &(~(0x1<<8)))|(0x1<<8);//tref_enable
        write_register(0x0000011c,reg_value);
    }
    else{
        reg_value = (read_register(0x00000270) &(~(0x3)))|(0x3);//low_power_refresh_disable
        write_register(0x00000270,reg_value);
        reg_value = read_register(0x0000016c) &(~(0x1<<16));//pbr_cont_req_en
        write_register(0x0000016c,reg_value);
        reg_value = read_register(0x00000168) &(~(0xf<<24));//pbr_mode_en
        write_register(0x00000168,reg_value);
        reg_value = read_register(0x0000011c) &(~(0x1<<8));//tref_enable
        write_register(0x0000011c,reg_value);
    }

}

void lpi_sr_short_wakeup_fN(void){
    uint32_t reg_value = 0;
    reg_value = (read_register(0x00000270) &(~(0xf<<24)))|(0xf<<24);
    write_register(0x00000270,reg_value);
    reg_value = (read_register(0x0000027c) &(~(0xf)))|(0xf);
    write_register(0x0000027c,reg_value);
    reg_value = (read_register(0x00000284) &(~(0xf<<8)))|(0xf<<8);
    write_register(0x00000284,reg_value);
}

void srefresh_exit_no_refresh(uint32_t enable){
    uint32_t reg_value = 0;
    reg_value = (read_register(0x000001b0)&(~(1<<24)))|(enable<<24);
    write_register(0x000001b0,reg_value);
}

void check_lp_status(uint32_t lp_status){
    switch(lp_status){
        case 0x0:
            printf("Idle\n");
            break;
        case 0x1:
            printf("Active Power-Down\n");
            break;
        case 0x2:
            printf("Active Power-Down with Memory Clock Gating\n");
            break;
        case 0x3:
            printf("Pre-Charge Power-Down\n");
            break;
        case 0x4:
            printf("Pre-Charge Power-Down with Memory Clock Gating\n");
            break;
        case 0x8:
            printf("Self-Refresh Long\n");
            break;
        case 0xb:
            printf("Self-Refresh Power-Down Short\n");
            break;
        case 0xc:
            printf("Self-Refresh Power-Down Short with Memory Clock Gating\n");
            break;
        case 0xd:
            printf("Self-Refresh Power-Down Long\n");
            break;
        case 0xe:
            printf("Self-Refresh Power-Down Long with Memory Clock Gating\n");
            break;
        case 0xf:
            printf("Self-Refresh Power-Down Long with Memory and Controller Clock Gating\n");
            break;
        default:
            printf("lp_status err\n");
            break;
    }
}

void wait_for_lp_status_change(uint32_t cs_num){
    uint32_t cnt = 0;
    uint32_t cs0_lp_status_change = 0;
    uint32_t cs1_lp_status_change = 0;
    uint32_t cs0_lp_status = 0;
    uint32_t cs1_lp_status = 0;

    printf("cs0_lp_status_change\n");
    while(!cs0_lp_status_change){
        cs0_lp_status_change = (read_register(0x00000294)>>14)&(0x1);
        if(cnt%100000){
            printf("wait for cs0_lp_status_change:%x\n",cs0_lp_status_change);
        }
        cnt++;
    }
    cs0_lp_status = (read_register(0x00000294)>>8)&(0x3f);
    check_lp_status(cs0_lp_status);
    cnt = 0;
    if(cs_num > 1){
        printf("cs1_lp_status_change\n");
        while(!cs1_lp_status_change){
            cs1_lp_status_change = (read_register(0x00000294)>>22)&(0x1);
            if(cnt%100000){
                printf("wait for cs1_lp_status_change:%x\n",cs1_lp_status_change);
            }
            cnt++;
        }
        cnt = 0;
        cs1_lp_status = (read_register(0x00000294)>>16)&(0x3f);
        check_lp_status(cs1_lp_status);
    }
} 

//enter self-refresh power donw short
void lpddr4_enter_srpd(uint32_t lp_cmd,uint32_t cs_num){
    uint32_t reg_value = 0;
    reg_value = (read_register(0x00000270) &(~(0x7f<<8)))|(lp_cmd<<8);
    write_register(0x00000270,reg_value);
    wait_for_lp_status_change(cs_num);
}

void lpddr4_exit_pd(uint32_t cs_num){
    uint32_t reg_value = 0;
    reg_value = (read_register(0x00000270) &(~(0x7f<<8)))|(0x2<<8);
    write_register(0x00000270,reg_value);
    wait_for_lp_status_change(cs_num);
}

void lpddr4_lp_srpd_test(void){
    volatile unsigned int* addr64_ptr;
    uint32_t i, rd_val;

    axi_init();
#ifndef CONFIG_COMPILE_ASIC
    sys_lpddr4_start();
#endif
    reset_lp_conf();
    srefresh_exit_no_refresh(1);
    lpi_sr_short_wakeup_fN();
    lp_aref_enable(0);
    lpddr4_enter_srpd(ENTER_SELF_REFRESH_POWER_DOWN_LONG_WITH_MEMORY_AND_CONTROLLER_CLOCK_GATING,2);
    lpddr4_exit_pd(2);
    lp_aref_enable(1);
    printf("DDR_TEST_BASE: 0x%lX\n", (unsigned long)DDR_TEST_BASE);
    for(i=0; i<32; i=i+1){
        addr64_ptr=(volatile unsigned int*)(DDR_TEST_BASE+i*4);
        *(addr64_ptr) = 0x12340+i;
    }
#if defined(CONFIG_E906)
    udelay(1);
#else
    asm("sync.is");
#endif
    for(i=0; i<32; i=i+1){
        addr64_ptr=(volatile unsigned int*)(DDR_TEST_BASE+i*4);
        rd_val = *(addr64_ptr) ;
        if(rd_val != (0x12340+i))
            printf("MPU read error!\n"); 
    }
    printf("MPU read success!\n");
}

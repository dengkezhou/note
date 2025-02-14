#include "../lpddr4_common.h"
#include "lpddr4_dll_bist.h"

void phy_select_ac_lpbk_obs_slice(Slice_num slice_num){
    if(slice_num == AC_SLICE_0){
        write_register(0x00005550 , 0x00000000);//AC_SLICE_0
    }else if(slice_num == AC_SLICE_1){
        write_register(0x00005550 , 0x00000001);//AC_SLICE_1
    }
}

void phy_select_ac_obs_source(uint32_t source_type){
    if(source_type == QTR_DLY){
        write_register(0x00005578 , 0x00000351);//QTR_DLY
    }else if(source_type == MIN_MAX_DLY){
        write_register(0x00005578 , 0x00000051);//MIN_MAX_DLY
    }else if(source_type == WHOLE_DLY){
        write_register(0x00005578 , 0x00000151);//WHOLE_DLY
    }
}

void phy_dll_bist_conf(Slice_type slice_type,uint32_t enable){
    uint32_t slice = 0;

    if(slice_type == AC){
        write_register(0x00005578 , 0x00000151);//ac_dll_conf
        write_register(0x00005574 , enable);//ac_dll_enable
    }

    if(slice_type == ADR){
        write_register(0x00005020 , 0x000000a3);//adr_dll_conf
    }

    if(slice_type == DATA){
        for(slice = 0;slice < 4;slice++){
            for(slice = 0;slice < 4;slice++){
                write_register(0x000040fc , 0x000000a3);//data_dll_conf
            }
        }
    }
}

void phy_wait_for_dll_test_done(Slice_type slice_type){
    uint32_t dll_test_done = 0;
    uint32_t timeout_cnt = 0;
    if(slice_type == AC){
        while(dll_test_done == 0){
            dll_test_done = read_register(0x00005558)&0x1;
            timeout_cnt++;
            if(timeout_cnt%10000){
                printf("wait for ac dll test done\n");
            }

            if(timeout_cnt > 3000000){
                printf("wait for ac dll test done timeout\n");
            }
        }
        printf("ac dll test done\n");
    }

    timeout_cnt = 0;
    if(slice_type == ADR){
        while(dll_test_done == 0){
            dll_test_done = read_register(0x00005028)&0x1;
            timeout_cnt++;
            if(timeout_cnt%10000){
                printf("wait for adr dll test done\n");
            }

            if(timeout_cnt > 3000000){
                printf("wait for adr dll test done timeout\n");
            }
        }
        printf("adr dll test done\n");
    }

    timeout_cnt = 0;
    if(slice_type == DATA){
        while(dll_test_done == 0){
            dll_test_done = read_register(0x00004104)&0x1;
            timeout_cnt++;
            if(timeout_cnt%10000){
                printf("wait for data dll test done\n");
            }

            if(timeout_cnt > 3000000){
                printf("wait for data dll test done timeout\n");
            }
        }
        printf("data dll test done\n");
    }
}

void phy_dll_bist_test(void){
    uint32_t phy_adr_sw_master_mode_0 = 0;
    uint32_t slice_num = 0;
    uint32_t slave_qtr_obs[2] = {0};
    uint32_t slave_whole_obs[2] = {0};
    uint32_t slave_dly_obs[2] = {0};
    uint32_t adr_obs = 0;
    uint32_t adr_mstr_obs = 0;
    uint32_t data_slice_obs[4] = {0};
    uint32_t data_mstr_obs[4] = {0};
    phy_adr_sw_master_mode_0 = (read_register(0x000050bc)>>8)&0xf;
    if((phy_adr_sw_master_mode_0 & 0x3) == 0x3){
        printf("DDL REG DOES NOT SUPPORT HALP CLOCK MODE\n");
        return;
    }else if(((phy_adr_sw_master_mode_0>>2)&0x3) == 0x3){
        printf("DDL REG BYPASS\n");
        return;
    }
    phy_input_enable();
#ifndef CONFIG_COMPILE_ASIC
    sys_lpddr4_start();
#endif
    mc_lpi_wakeup_en();
    mc_dfi_auto_update_conf();
    phy_auto_update_conf();
    mc_dfi_update_count_set();
    udelay(1);
    phy_dll_bist_conf(AC,0x7);
    phy_dll_bist_conf(ADR,0x7);
    phy_dll_bist_conf(DATA,0x7);
    udelay(1);
    phy_select_ac_lpbk_obs_slice(AC_SLICE_0);
    phy_wait_for_dll_test_done(AC);
    slave_whole_obs[0] = read_register(0x00005558);
    phy_select_ac_obs_source(QTR_DLY);
    slave_qtr_obs[0] = read_register(0x00005558);
    phy_select_ac_obs_source(MIN_MAX_DLY);
    slave_dly_obs[0] = read_register(0x00005558);
    phy_select_ac_obs_source(WHOLE_DLY);

    phy_select_ac_lpbk_obs_slice(AC_SLICE_1);
    phy_wait_for_dll_test_done(AC);
    slave_whole_obs[1] = read_register(0x00005558);
    phy_select_ac_obs_source(QTR_DLY);
    slave_qtr_obs[1] = read_register(0x00005558);
    phy_select_ac_obs_source(MIN_MAX_DLY);
    slave_dly_obs[1] = read_register(0x00005558);
    phy_select_ac_obs_source(WHOLE_DLY);
    
    phy_wait_for_dll_test_done(ADR);
    adr_obs = read_register(0x00005028);
    adr_mstr_obs = read_register(0x0000502c);

    phy_wait_for_dll_test_done(DATA);
    for(slice_num = 0;slice_num < 4;slice_num++){
        data_slice_obs[slice_num] = read_register(0x00004104 + slice_num * 0x400);
        data_mstr_obs[slice_num] = read_register(0x00004108 + slice_num * 0x400);
	printf("data_mstr_obs[%d]: 0x%lx\n", slice_num, data_mstr_obs[slice_num]);
    }
    /*check ddl test result*/
    for(slice_num = 0;slice_num < 2;slice_num++){
        if(((slave_whole_obs[slice_num]>>1)&0xf)!= 0x0){
            printf("ERROR: AC Slave %d Whole Delay FAILED, slave_whole_obs = %x\n",slice_num,slave_whole_obs[slice_num]);
        }
        if((slave_qtr_obs[slice_num]>>18)&0x1){
            if((slave_qtr_obs[slice_num]>>1)&0x7){
                printf("ERROR: AC Slave %d Quarter Delay FAILED, slave_qtr_obs = %x\n",slice_num,slave_qtr_obs[slice_num]);
            }
        }
        printf("AC Slave %d Min Delay count = %d\n", slave_dly_obs[slice_num]&0xffff);
        printf("AC Slave %d Max Delay count = %d\n", (slave_dly_obs[slice_num]>>16)&0xffff);
        if(((slave_qtr_obs[slice_num])>>1&0xffff)==0 && ((slave_whole_obs[slice_num])>>1&0xffff)==0){
            printf("AC Slave %d PASSED, slave_whole_obs = %x\n",slice_num,slave_whole_obs[slice_num]);
        }
    }

    if((adr_obs>>1&0x7f) != 0x0){
        if(adr_obs>>1&0x1){
            printf("Address Slice 0 DDL_TIMEOUT\n");
        }else if(adr_obs>>2&0x1){
            printf("Address Slice 0 Minimum Step Size Failed\n");
        }else if(adr_obs>>3&0x1){
            printf("Address Slice 0 Maximum Step Size Failed\n");
        }else if(adr_obs>>4&0x1){
            printf("Address Slice 0 Monotonic Step Size Failed\n");
        }else if(adr_obs>>5&0x1){
            printf("Address Slice 0 Minimum Quarter Step Size Failed\n");
        }else if(adr_obs>>6&0x1){
            printf("Address Slice 0 Maximum Quarter Step Size Failed\n");
        }else if(adr_obs>>7&0x1){
            printf("Address Slice 0 Monotonic Quarter Step Size Failed\n");
        }
        printf("ERROR: Address Slice 0 FAILED, adr_slice_obs = %x\n", adr_obs);
    }
    printf("Address Slice 0 Min Delay count = '%x\n", adr_mstr_obs&0xffff);
    printf("Address Slice 0 Max Delay count = '%x\n", adr_mstr_obs>>16&0xffff);
    if(adr_obs>>1&0x7f){
        printf("Address Slice 0 PASSED, adr_slice_obs = %x\n", adr_obs);
    }

    for(slice_num = 0;slice_num < 4;slice_num++){
        if((data_slice_obs[slice_num]>>1&0x7f) != 0x0){
            if(data_slice_obs[slice_num]>>1&0x1){
                printf("Data Slice %d DDL_TIMEOUT\n",slice_num);
            }else if(data_slice_obs[slice_num]>>2&0x1){
                printf("Data Slice %d Minimum Step Size Failed\n",slice_num);
            }else if(data_slice_obs[slice_num]>>3&0x1){
                printf("Data Slice %d Maximum Step Size Failed\n",slice_num);
            }else if(data_slice_obs[slice_num]>>4&0x1){
                printf("Data Slice %d Monotonic Step Size Failed\n",slice_num);
            }else if(data_slice_obs[slice_num]>>5&0x1){
                printf("Data Slice %d Minimum Quarter Step Size Failed\n",slice_num);
            }else if(data_slice_obs[slice_num]>>6&0x1){
                printf("Data Slice %d Maximum Quarter Step Size Failed\n",slice_num);
            }else if(data_slice_obs[slice_num]>>7&0x1){
                printf("Data Slice %d Monotonic Quarter Step Size Failed\n",slice_num);
            }
            printf("ERROR: Data Slice %d FAILED, data_slice_obs = %x\n",slice_num,data_slice_obs);
        }
        printf("Data Slice %d Min Delay count = '%x\n",slice_num,data_slice_obs[slice_num]&0xffff);
        printf("Data Slice %d Max Delay count = '%x\n",slice_num,data_slice_obs[slice_num]>>16&0xffff);
        if((data_slice_obs[slice_num]>>1&0x7f) == 0x0){
            printf("Data Slice %d PASSED, data_slice_obs = %x\n",slice_num,data_slice_obs[slice_num]);
        }
    }
}
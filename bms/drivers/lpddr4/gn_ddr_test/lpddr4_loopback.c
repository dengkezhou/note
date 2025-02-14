#include "../lpddr4_common.h"
#include "lpddr4_loopback.h"

extern volatile int def_low_freq;

void loopback_start_pattern(uint32_t loopback_object){
    if(loopback_object == DATA_LOOPBACK){
        uint32_t data_loopback_start_pattern[] = {
            0x00004030 , 0x10010000,
            0x00004430 , 0x10010000,
            0x00004830 , 0x10010000,
            0x00004c30 , 0x10010000,
            0xffffffff , 0xffffffff
        };
        write_register_array(data_loopback_start_pattern);
    }else if(loopback_object == AC_LOOPBACK){
        uint32_t ac_loopback_start_pattern[] = {
            0x00005554 , 0x00000010,
            0xffffffff , 0xffffffff
        };
        write_register_array(ac_loopback_start_pattern);
    }else if(loopback_object == ADR_LOOPBACK){
        uint32_t adr_loopback_start_pattern[] = {
            0x00005014 , 0x00780000,
            0xffffffff , 0xffffffff
        };
        write_register_array(adr_loopback_start_pattern);
    }
}

void loopback_start(uint32_t loopback_object,uint32_t loopback_type,
                    uint32_t pattern,uint32_t toggle){
    uint32_t reg_value = 0;
    if(loopback_object == DATA_LOOPBACK){
        uint32_t data_slice = 0;
        for(data_slice = 0;data_slice < 3;data_slice++){
            reg_value = (read_register(0x00004020)&(~(0x1ff<<16)))
                        |(loopback_type<<17)|(pattern<<18)|(toggle<<21);
            write_register(0x00004020 + 0x400*data_slice, reg_value);//conf data loopback
            reg_value = (reg_value&(~(1<<16)))|(1<<16);
            write_register(0x00004020 + 0x400*data_slice, reg_value);//enable
            reg_value = (reg_value&(~(1<<23)))|(1<<23);
            write_register(0x00004020 + 0x400*data_slice, reg_value);//go
        }
    }else if(loopback_object == AC_LOOPBACK){
        write_register(0x0000554c,0x01000000);//clear ac error
        udelay(1);
        reg_value = (read_register(0x00005550)&(~(0x1ff<<16)))
                    |(loopback_type<<16)|(pattern<<17)|(toggle<<19);
        write_register(0x00005550,reg_value);//select address/control
        reg_value = (reg_value&(~(3<<8)))|(3<<8);
        write_register(0x00005550,reg_value);//enable
        reg_value = (reg_value&(~(1<<21)))|(1<<21);
        write_register(0x00005550,reg_value);//select obs + go
    }else if(loopback_object == ADR_LOOPBACK){
        reg_value = (read_register(0x00005014)&(~(0x7f<<8)))
                    |(loopback_type<<9)|(pattern<<10)|(toggle<<12);
        write_register(0x00005014,reg_value);//select address
        reg_value = (reg_value&(~(1<<8)))|(1<<8);
        write_register(0x00005014,reg_value);//go
        reg_value = (reg_value&(~(1<<14)))|(1<<14);
        write_register(0x00005014,reg_value);//go
    }else if(loopback_object == MEMCLK_LOOPBACK){
        reg_value = (read_register(0x0000555c)&(~(0x3f<<16)))
                    |(loopback_type<<16)|(toggle<<17);
        write_register(0x0000555c,reg_value);
        reg_value = (reg_value&(~(1<<8)))|(1<<8);
        write_register(0x0000555c,reg_value);//enable
        reg_value = (reg_value&(~(1<<19)))|(1<<19);
        write_register(0x0000555c,reg_value);//go
    }
}

void loopback_end(uint32_t loopback_object){
    if(loopback_object == DATA_LOOPBACK){
        uint32_t data_loopback_end[] = {
            0x00004020 , 0x00310001,
            0x00004420 , 0x00310001,
            0x00004820 , 0x00310001,
            0x00004c20 , 0x00310001,
            0x00004020 , 0x00000001,
            0x000040b4 , 0x00000201,
            0x00004420 , 0x00000001,
            0x000044b4 , 0x00000200,
            0x00004820 , 0x00000001,
            0x000048b4 , 0x00000201,
            0x00004c20 , 0x00000001,
            0x00004cb4 , 0x00000200,
            0x000040b4 , 0x00000001,
            0x000044b4 , 0x00000000,
            0x000048b4 , 0x00000001,
            0x00004cb4 , 0x00000000,
            0xffffffff , 0xffffffff
        };
        write_register_array(data_loopback_end);
    }else if(loopback_object == AC_LOOPBACK){
        uint32_t ac_loopback_end[] = {
            0x00005550 , 0x00800300,//stop address/control
            0xffffffff , 0xffffffff
        };
        write_register_array(ac_loopback_end);
    }else if(loopback_object == ADR_LOOPBACK){
        uint32_t adr_loopback_end[] = {
            0x00005014 , 0x00000000,
            0xffffffff , 0xffffffff
        };
        write_register_array(adr_loopback_end);
    }else if(loopback_object == MEMCLK_LOOPBACK){
        uint32_t memclk_loopback_end[] = {
            0x0000555c , 0x00000100,
            0x0000554c , 0x01000000,
            0xffffffff , 0xffffffff
        };
        write_register_array(memclk_loopback_end);
    }
}

void loopback_mask(uint32_t loopback_object,uint32_t slice,uint32_t bit){
    uint32_t reg_value = 0;
    if(loopback_object == DATA_LOOPBACK){
        reg_value = (read_register(0x00004034 + slice*0x400) &(~(0xff)))|(bit);
        write_register(0x00004034 + slice*0x400,reg_value);
    }else if(loopback_object == AC_LOOPBACK){
        reg_value = (read_register(0x00005554) &(~(0xf<<8)))|(bit<<8);
        write_register(0x00005554,reg_value);
    }else if(loopback_object == ADR_LOOPBACK){
        reg_value = (read_register(0x00005014) &(~(0x1f<<24)))|(bit<<24);
        write_register(0x00005014, reg_value);
    }
}

void bit_mask(uint32_t loopback_object,uint32_t slice,uint32_t bit){
    uint32_t reg_value = 0;
    if(loopback_object == DATA_LOOPBACK){
        reg_value = (read_register(0x0000407c + slice*0x400) &(~(0xff<<8)))|(bit<<8);
        write_register(0x0000407c + slice*0x400,reg_value);
    }
    // else if(loopback_object == ADR_LOOPBACK){
    //     reg_value = read_register(0x00005014) &(~(0x1f<<24))|(bit<<24);
    //     write_register(0x00005014);
    // }
}


uint32_t loopback_obs(uint32_t loopback_object,uint32_t pattern){
    uint32_t reg_value = 0;
    uint32_t cnt = 0;
    uint32_t slice = 0;
    if(loopback_object == DATA_LOOPBACK){
        printf("check data loopback\n");
        for(slice = 0;slice < 4;slice++){
            if(pattern == PRBS7){
                cnt = 0;
                while(reg_value != 0x1){
                    reg_value = ((read_register(0x000040b8 + 0x400*slice)>>26)&0x1)
                               |((read_register(0x000040b8 + 0x400*slice)>>27)&0x1);
                    if(reg_value==1){
                        printf("data slice %d loopback test fail\n",slice);
                        if((read_register(0x000040b8 + 0x400*slice)>>20)&0x1){
                            printf("data bit 8 error\n");
                        }
                        if((read_register(0x000040b8 + 0x400*slice)>>19)&0x1){
                            printf("data bit 7 error\n");
                        }
                        if((read_register(0x000040b8 + 0x400*slice)>>18)&0x1){
                            printf("data bit 6 error\n");
                        }
                        if((read_register(0x000040b8 + 0x400*slice)>>17)&0x1){
                            printf("data bit 5 error\n");
                        }
                        if((read_register(0x000040b8 + 0x400*slice)>>16)&0x1){
                            printf("data bit 4 error\n");
                        }
                        if((read_register(0x000040b8 + 0x400*slice)>>16)&0x1){
                            printf("data bit 3 error\n");
                        }
                        if((read_register(0x000040b8 + 0x400*slice)>>16)&0x1){
                            printf("data bit 2 error\n");
                        }
                        if((read_register(0x000040b8 + 0x400*slice)>>16)&0x1){
                            printf("data bit 1 error\n");
                        }
                        if((read_register(0x000040b8 + 0x400*slice)>>16)&0x1){
                            printf("data bit 0 error\n");
                        }
                        break;
                    }
                    reg_value = (read_register(0x000040b8 + 0x400*slice)>>28)&0x1;
                    cnt++;
                    if(cnt > 30000){
                        printf("Wait for data slice %d loopback done timeout\n",slice);
                        cnt = 0;
                        break;
                    };
                }
            }else{
                cnt = 0;
                while(reg_value != 0x1){
                    reg_value = ((read_register(0x000040b8 + 0x400*slice)>>19)&0x1)
                            |((read_register(0x000040b8 + 0x400*slice)>>20)&0x1);
                    if(reg_value==1){
                        printf("data slice %d loopback test fail\n",slice);
                        break;
                    }
                    reg_value = (read_register(0x000040b8 + 0x400*slice)>>21)&0x1;
                    cnt++;
                    if(cnt > 30000){
                        printf("Wait for data slice %d loopback done timeout\n",slice);
                        cnt = 0;
                        break;
                    };
                }
            }
            if(reg_value == 0x1){
                printf("data slice %d loopback test done\n",slice);
            }
        }
    }

    if(loopback_object == AC_LOOPBACK){
            cnt = 0;
            printf("check ac loopback\n");
            while(reg_value != 0x1){
                reg_value = (read_register(0x00005558)>>4)&0x1;
                if(reg_value==1){
                    printf("ac loopback test fail\n");
                    break;
                }
                reg_value = (read_register(0x00005558)>>5)&0x1;
                cnt++;
                if(cnt > 30000){
                    printf("Wait for ac loopback done timeout\n");
                    cnt = 0;
                    break;
                };
            }
            if(reg_value == 0x1){
                printf("ac loopback test done\n");
            }
    }

    if(loopback_object == ADR_LOOPBACK){
            cnt = 0;
            printf("check adr loopback\n");
            while(reg_value != 0x1){
                if(pattern == PRBS7){
                    reg_value = ((read_register(0x00005004)>>22)&0x1)
                               |((read_register(0x00005004)>>23)&0x1);
                    if(reg_value==1){
                        printf("adr loopback test fail\n");
                        if((read_register(0x00005004)>>20)&0x1){
                            printf("address bit 5 error\n");
                        }
                        if((read_register(0x00005004)>>19)&0x1){
                            printf("address bit 4 error\n");
                        }
                        if((read_register(0x00005004)>>18)&0x1){
                            printf("address bit 3 error\n");
                        }
                        if((read_register(0x00005004)>>17)&0x1){
                            printf("address bit 2 error\n");
                        }
                        if((read_register(0x00005004)>>16)&0x1){
                            printf("address bit 1 error\n");
                        }
                        break;
                    }
                    reg_value = (read_register(0x00005004)>>24)&0x1;
                    cnt++;
                    if(cnt > 30000){
                        printf("Wait for adr loopback done timeout\n");
                        cnt = 0;
                        break;
                    };
                }else{
                    reg_value = ((read_register(0x00005004)>>11)&0x1)
                            |((read_register(0x00005004)>>12)&0x1);
                    if(reg_value==1){
                        printf("adr loopback test fail\n");
                        break;
                    }
                    reg_value = (read_register(0x00005004)>>13)&0x1;
                    cnt++;
                    if(cnt > 30000){
                        printf("Wait for adr loopback done timeout\n");
                        cnt = 0;
                        break;
                    };
                }
            }
            if(reg_value == 0x1){
                printf("adr loopback test done\n");
            }
    }

    if(loopback_object == MEMCLK_LOOPBACK){
            cnt = 0;
            printf("check memclk loopback\n");
            while(reg_value != 0x1){
                reg_value = (read_register(0x00005560)>>0)&0x1;
                if(reg_value==1){
                    printf("memclk loopback test fail\n");
                    break;
                }
                reg_value = (read_register(0x00005560)>>1)&0x1;
                cnt++;
                if(cnt > 30000){
                    printf("Wait for memclk loopback done timeout\n");
                    cnt = 0;
                    break;
                };
            }
            if(reg_value == 0x1){
                printf("memclk loopback test done\n");
            }
    }
    return 0;
}

void loopback_test(void){
    phy_cs_training_disable(0);
#ifndef CONFIG_COMPILE_ASIC
    if (def_low_freq)
        sys_lpddr4_start_1066();
    else
        sys_lpddr4_start();
#endif
    phy_sw_master_mode();
    mc_lpi_wakeup_en();
    phy_wait_for_dfi_complete_init(0xf,1,0,0);
    phy_disable_dly_ctrl_power_reduction();
    mc_refresh_conf();
    mc_dfi_auto_update_conf();
    mc_dfi_update_count_set();

    // /***********************
    //     internal loopback
    // ************************/
    loopback_phy_manual_training(INTERNAL);

    printf("begin internal loopback\n");

    loopback_start_pattern(MEMCLK_LOOPBACK);
    loopback_start(MEMCLK_LOOPBACK,INTERNAL,CLOCK_PATTERN,PULSES_1024);//no pattern

    loopback_start_pattern(AC_LOOPBACK);
    loopback_start(AC_LOOPBACK,INTERNAL,PRBS7,PULSES_1024);//00--1/2 clock frequency;01--1/4 pattern;11--PRBS7

    loopback_start_pattern(ADR_LOOPBACK);
    loopback_start(ADR_LOOPBACK,INTERNAL,PRBS7,PULSES_1024);//00--LFSR;01--Clock Pattern;11--PRBS7

    loopback_start_pattern(DATA_LOOPBACK);
    loopback_start(DATA_LOOPBACK,INTERNAL,PRBS7,PULSES_1024);//00--LFSR;01--CLOCK_PATTERN;11--PRBS7

    udelay(10);

    loopback_obs(MEMCLK_LOOPBACK,PRBS7);
    loopback_obs(AC_LOOPBACK,PRBS7);
    loopback_obs(ADR_LOOPBACK,PRBS7);
    loopback_obs(DATA_LOOPBACK,PRBS7);

    loopback_end(AC_LOOPBACK);
    loopback_end(ADR_LOOPBACK);
    loopback_end(MEMCLK_LOOPBACK);
    loopback_end(DATA_LOOPBACK);
    /***********************
        external loopback
    ************************/
    if (def_low_freq)
        loopback_phy_manual_training(EXTERNAL);
    else
        loopback_phy_manual_training(INTERNAL);

    printf("begin external loopback\n");

    loopback_start_pattern(MEMCLK_LOOPBACK);
    loopback_start(MEMCLK_LOOPBACK,EXTERNAL,CLOCK_PATTERN,PULSES_1024);//no pattern

    loopback_start_pattern(AC_LOOPBACK);
    loopback_start(AC_LOOPBACK,EXTERNAL,PRBS7,PULSES_1024);//00--1/2 clock frequency;01--1/4 pattern;11--PRBS7

    loopback_start_pattern(ADR_LOOPBACK);
    loopback_start(ADR_LOOPBACK,EXTERNAL,PRBS7,PULSES_1024);//00--LFSR;01--Clock Pattern;11--PRBS7

    loopback_start_pattern(DATA_LOOPBACK);
    loopback_start(DATA_LOOPBACK,EXTERNAL,PRBS7,PULSES_1024);//00--LFSR;01--CLOCK_PATTERN;11--PRBS7

    udelay(10);

    loopback_obs(MEMCLK_LOOPBACK,CLOCK_PATTERN);
    loopback_obs(AC_LOOPBACK,PRBS7);
    loopback_obs(ADR_LOOPBACK,PRBS7);
    loopback_obs(DATA_LOOPBACK,PRBS7);

    loopback_end(AC_LOOPBACK);
    loopback_end(ADR_LOOPBACK);
    loopback_end(MEMCLK_LOOPBACK);
    loopback_end(DATA_LOOPBACK);
}
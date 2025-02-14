#include "../lpddr4_common.h"

void phy_sw_master_mode(void){
        uint32_t phy_sw_master_mode[] = {
            0x000050bc , 0x00100003,
            0xffffffff , 0xffffffff
    };
    write_register_array(phy_sw_master_mode); 
}

void phy_input_enable(void){
    uint32_t dis_ie[] = {
        0x0000418c , 0x0e000000,//disable input
        0x0000458c , 0x0e000000,
        0x0000498c , 0x0e000000,
        0x00004d8c , 0x0e000000,
        0xffffffff , 0xffffffff
    };
    write_register_array(dis_ie); 
}

void phy_auto_update_conf(void){
    uint32_t dis_phy_update[] = {
        0x0000557c , 0x00040000,//disable phy update
        0xffffffff , 0xffffffff
    };
    write_register_array(dis_phy_update); 
}

void phy_disable_dly_ctrl_power_reduction(void){
    uint32_t disable_dly_ctrl_power_reduction[] = {
        0x00004134 , 0x00010401,
        0x00004534 , 0x00010401,
        0x00004934 , 0x00010401,
        0x00004d34 , 0x00010401,
        0x00005018 , 0x00000100,
        0x00005564 , 0x00000001,
        0xffffffff , 0xffffffff
    };
    write_register_array(disable_dly_ctrl_power_reduction); 
}

void phy_wait_for_dfi_complete_init(uint32_t data_slice_check,uint32_t acs_slice_check,uint32_t adr_slice_check,uint32_t ac_slice_check){
    uint32_t dfi_data_obs = (read_register(0x00005598)>>24) & 0xf; 
    uint32_t dfi_acs_obs = (read_register(0x00005598)>>8) & 0x1; 
    uint32_t dfi_adr_obs = (read_register(0x00005598)>>12) & 0xf;
    uint32_t dfi_ac_obs = (read_register(0x00005598)>>16) & 0x3;
    uint32_t timeout_cnt = 0;

    while(dfi_data_obs != data_slice_check){
        dfi_data_obs = (read_register(0x00005598)>>24) & 0xf; 
        if(!(timeout_cnt%1000)){
            printf("Wait for data dfi_init_complete,and data_slice_check is %x\n",data_slice_check);
        }
        timeout_cnt++;
        if(timeout_cnt > 0xffffffff){
            printf("Wait for data dfi_init_complete timeout\n");
            timeout_cnt = 0;
            break;
        }
    }
    printf("data dfi_init_complete\n");

    timeout_cnt = 0;

    if(acs_slice_check){
        while(dfi_acs_obs != acs_slice_check){
            dfi_acs_obs = (read_register(0x00005598)>>8) & 0x1; 
            if(!(timeout_cnt%1000)){
                printf("Wait for acs dfi_init_complete\n");
            }
            timeout_cnt++;
            if(timeout_cnt > 0xffffffff){
                printf("Wait for acs dfi_init_complete timeout\n");
                timeout_cnt = 0;
                break;
            }
        }
        printf("acs dfi_init_complete\n");
    }else{
        while(dfi_adr_obs != adr_slice_check){
            dfi_adr_obs = (read_register(0x00005598)>>12) & 0xf;
            if(!(timeout_cnt%100)){
                printf("Wait for adr dfi_init_complete,and adr_slice_check is %x\n",adr_slice_check);
            }
            timeout_cnt++;
            if(timeout_cnt > 0xffffffff){
                printf("Wait for adr dfi_init_complete timeout\n");
                timeout_cnt = 0;
                break;
            }
        }
        printf("adr dfi_init_complete\n");
        timeout_cnt = 0;

        while(dfi_ac_obs != ac_slice_check){
            dfi_ac_obs = (read_register(0x00005598)>>16) & 0x3;
            if(!(timeout_cnt%100)){
                printf("Wait for ac dfi_init_complete,and ac_slice_check is %x\n",ac_slice_check);
            }
            timeout_cnt++;
            if(timeout_cnt > 0xffffffff){
                printf("Wait for ac dfi_init_complete timeout\n");
                timeout_cnt = 0;
                break;
            }
        }
        printf("ac dfi_init_complete\n");
    }
}
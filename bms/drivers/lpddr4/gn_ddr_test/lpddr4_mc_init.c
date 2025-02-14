#include "../lpddr4_common.h"

void mc_lpi_wakeup_en(void){
        uint32_t lpi_wakeup_dis[] = {
            0x0000028c , 0x0001000e,
            0xffffffff , 0xffffffff
    };
    write_register_array(lpi_wakeup_dis); 
}

void mc_refresh_conf(void){
    uint32_t refresh_conf[] = {
        0x000004f4 , 0x01010100,
        0x0000011c , 0x20030000,
        0xffffffff , 0xffffffff
    };
    write_register_array(refresh_conf); 
}

void mc_dfi_auto_update_conf(void){
    uint32_t dis_auto_update[] = {
        0x000004f4 , 0x01010100,
        0xffffffff , 0xffffffff
    };

    write_register_array(dis_auto_update); 
}

void mc_dfi_update_count_set(void){
    uint32_t dfi_update_count_set[] = {
        0x000001c4 , 0x00008010,
        0x000001d0 , 0x00040000,
        0x000001d8 , 0x00000000,
        0x000001c8 , 0x00050000,
        0x000001d0 , 0x00000000,
        0x000001dc , 0x00050000,
        0xffffffff , 0xffffffff
    };
    write_register_array(dfi_update_count_set); 
}

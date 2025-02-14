
#include "../lpddr4_common.h"

uint64_t lpddr4_mrr_test(uint32_t cs,uint32_t mr){
    uint32_t reg_value;
    uint64_t mr_value;

    reg_value = read_register(0x000002f0)&(~(0x1<<24));//read_modereg clear action
    write_register(0x000002f0,reg_value);
    reg_value = (read_register(0x000002f0)&(~(0xff<<16)))|(cs<<16);//read_modereg select all chip
    write_register(0x000002f0,reg_value);
    reg_value = (read_register(0x000002f0)&(~(0xff<<8)))|(mr<<8);//read_modereg select all chip
    write_register(0x000002f0,reg_value);
    reg_value = (read_register(0x000002f0)&(~(0x1<<24)))|(0x1<<24);//read_modereg action
    write_register(0x000002f0,reg_value);

    mr_value = ((unsigned long)(read_register(0x000002f8)&(~(0xff)))<<32) | read_register(0x000002f4);
    printf("mrr: 0x%x\n", mr_value);
    return mr_value;
}

void lpddr4_mrw_test(uint32_t mr,uint32_t data){
    uint32_t reg_value;

    reg_value = (read_register(0x0000033c)&(~(0xff)))|(data);//MRSINGLE_DATA_0
    write_register(0x0000033c,reg_value);
    reg_value = (read_register(0x0000033c)&(~(0xff<<8)))|(data<<8);//MRSINGLE_DATA_1
    write_register(0x0000033c,reg_value);

    reg_value = read_register(0x000002ec)&(~(1<<25));// clear
    write_register(0x000002ec,reg_value);
    reg_value = (read_register(0x000002ec)&(~(1<<24)))|(0x1<<24);//all cs
    write_register(0x000002ec,reg_value);
    reg_value = (read_register(0x000002ec)&(~(1<<23)))|(0x1<<23);//write single MR
    write_register(0x000002ec,reg_value);
    reg_value = (read_register(0x000002ec)&(~(0xff)))|(mr);//MR register
    write_register(0x000002ec,reg_value);
    reg_value = (read_register(0x000002ec)&(~(1<<25)))|(0x1<<25);//triger
    write_register(0x000002ec,reg_value);

    printf("set MR%d:%x\n",mr,data);
}
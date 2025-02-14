#include "../lpddr4_common.h"

extern volatile int def_low_freq;

void axi_init(void){
    write_register(0x000004f0,0x00000001);
    write_register(0x000004c8,0x00010101);
}

void dfi_dly_set(void){
    uint32_t reg_value;
    reg_value = (read_register(0x00000e9c)&(~(0x7f<<24)))|(18<<24);//
    write_register(0x00000e9c,reg_value);//rddata_en
}
void address_mapping(void){
    uint32_t reg_value;
    reg_value = (read_register(0x000004d0)&(~(1<<24)))|(0<<24);//mem_dp_reduction
    write_register(0x000004d0,reg_value);

    reg_value = (read_register(0x000004c0)&(~(0x1f<<8)))|(0xb<<8);//aprebit
    write_register(0x000004c0,reg_value);

    reg_value = (read_register(0x000004a8)&(~(0x3<<16)))|(0x0<<16);//bank_diff_0
    write_register(0x000004a8,reg_value);
    reg_value = (read_register(0x000004a8)&(~(0x3<<24)))|(0x0<<24);//bank_diff_1
    write_register(0x000004a8,reg_value);

    reg_value = (read_register(0x000004ac)&(~(0xf<<16)))|(0x1<<16);//col_diff_0
    write_register(0x000004ac,reg_value);
    reg_value = (read_register(0x000004ac)&(~(0xf<<24)))|(0x1<<24);//col_diff_1
    write_register(0x000004ac,reg_value);

    reg_value = (read_register(0x000004ac)&(~(0x7)))|(0x0);//row_diff_0
    write_register(0x000004ac,reg_value);
    reg_value = (read_register(0x000004ac)&(~(0x7<<8)))|(0x0<<8);//row_diff_1
    write_register(0x000004ac,reg_value);

    reg_value = (read_register(0x000004b4)&(~(0xffff<<8)))|(0x7ff<<8);//cs_msk_0
    write_register(0x000004b4,reg_value);
    reg_value = (read_register(0x000004bc)&(~(0xffff<<8)))|(0x7ff<<8);//cs_msk_1
    write_register(0x000004bc,reg_value);

    reg_value = (read_register(0x000004b0)&(~(0xffff)))|(0x0);//cs_val_lower_0
    write_register(0x000004b0,reg_value);
    reg_value = (read_register(0x000004b8)&(~(0xffff)))|(0x4000);//cs_val_lower_1
    write_register(0x000004b8,reg_value);

    reg_value = (read_register(0x000004b0)&(~(0xffff<<16)))|(0x3fff<<16);//cs_val_upper_0
    write_register(0x000004b0,reg_value);
    reg_value = (read_register(0x000004b8)&(~(0xffff<<16)))|(0x7fff<<16);//cs_val_upper_1
    write_register(0x000004b8,reg_value);

    reg_value = (read_register(0x000004bc)&(~(0xf<<24)))|(0<<24);//programmable_address_order
    write_register(0x000004bc,reg_value);

    reg_value = (read_register(0x000004b4)&(~(0x7)))|(0);//row_start_val_0
    write_register(0x000004b4,reg_value);
    reg_value = (read_register(0x000004bc)&(~(0x7)))|(0);//row_start_val_1
    write_register(0x000004bc,reg_value);
}

void axi_base_test(void){
    volatile unsigned int* addr64_ptr;
    uint32_t rd_val;
    //uint32_t reg_value;

    // axi_init();
    //address_mapping();

    // reg_value = read_register(0x000004d0)&(~(1<<24))|(1<<24);//mem_dp_reduction
    // write_register(0x000004d0,reg_value);
#ifndef CONFIG_COMPILE_ASIC
    if (def_low_freq)
        sys_lpddr4_start_1066();
    else
    	sys_lpddr4_start();
        // phy_manual_training();
#endif
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

    // for(i=0; i<32; i=i+1){
    //     addr64_ptr=(volatile unsigned int*)(0x100000000+i*4);
    //     *(addr64_ptr) = 0x12340+i;
    // }

    // asm("sync.is");

    // for(i=0; i<32; i=i+1){
    //     addr64_ptr=(volatile unsigned int*)(0x100000000+i*4);
    //     rd_val = *(addr64_ptr) ;
    //     if(rd_val != (0x12340+i))
    //         printf("MPU read error!\n");
    // }
    #ifdef CONFIG_E906
    #define DDR_TEST_BASE 0x40000000
    addr64_ptr=(volatile unsigned int*)(DDR_TEST_BASE + 0x10000000);//bit 26
    *(addr64_ptr) = 0x8888;

    addr64_ptr=(volatile unsigned int*)(DDR_TEST_BASE + 0x10000000);
    rd_val = *(addr64_ptr) ;
    if(rd_val != (0x8888))
        printf("MPU read error!\n");

    addr64_ptr=(volatile unsigned int*)(DDR_TEST_BASE + 0x20000000);//bit 27
    *(addr64_ptr) = 0x9999;

    addr64_ptr=(volatile unsigned int*)(DDR_TEST_BASE + 0x20000000);
    rd_val = *(addr64_ptr) ;
    if(rd_val != (0x9999))
        printf("MPU read error!\n");
    printf("axi base test pass\n");
    #else
    #define DDR_TEST_BASE 0x100000000
    addr64_ptr=(volatile unsigned int*)(DDR_TEST_BASE + 0x40000000);//bit 28
    *(addr64_ptr) = 0xaaaa;

    addr64_ptr=(volatile unsigned int*)(DDR_TEST_BASE + 0x40000000);
    rd_val = *(addr64_ptr) ;
    if(rd_val != (0xaaaa))
        printf("MPU read error!\n");

    addr64_ptr=(volatile unsigned int*)(DDR_TEST_BASE + 0x80000000);//bit 29
    *(addr64_ptr) = 0xbbbb;

    addr64_ptr=(volatile unsigned int*)(DDR_TEST_BASE + 0x80000000);
    rd_val = *(addr64_ptr) ;
    if(rd_val != (0xbbbb))
        printf("MPU read error!\n");

    addr64_ptr=(volatile unsigned int*)(DDR_TEST_BASE + 0x100000000);//bit 30
    *(addr64_ptr) = 0xcccc;

    addr64_ptr=(volatile unsigned int*)(DDR_TEST_BASE + 0x100000000);
    rd_val = *(addr64_ptr) ;
    if(rd_val != (0xcccc))
        printf("MPU read error!\n");

    addr64_ptr=(volatile unsigned int*)(DDR_TEST_BASE + 0x200000000);//bit 31
    *(addr64_ptr) = 0xcccc;

    addr64_ptr=(volatile unsigned int*)(DDR_TEST_BASE + 0x200000000);
    rd_val = *(addr64_ptr) ;
    if(rd_val != (0xcccc))
        printf("MPU read error!\n");
    printf("axi base test pass\n");
    #endif
}
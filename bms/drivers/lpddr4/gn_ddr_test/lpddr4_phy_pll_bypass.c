#include "../lpddr4_common.h"

void phy_pll_bypass(void){
    write_register(0x000055ac,0x1);
}
#ifdef CONFIG_E906
#define DDR_TEST_BASE 0x40000000
#else
#define DDR_TEST_BASE 0x100000000
#endif
void lpddr4_phy_pll_bypass_test(void){
    volatile unsigned int* addr64_ptr;
    uint32_t i, rd_val;
    phy_pll_bypass();
    sys_lpddr4_start();

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
    printf("MPU read test pass!\n");
}


#include "../lpddr4_common.h"

void lpddr4_pll_init(void){
    uint32_t rd_val;

    //PLLOUT = REF / DIVR_VAL * 4 * DIVF_VAL / DIVQ_VAL
    //VCO    = REF / DIVR_VAL * 4 * DIVF_VAL (1200 ~ 6000 MHz)
    printf("CPU PLL Test!\n");
    // APLL
    MA_OUTW(CLKGEN_ALDCFG   , 3);     // load parameter, newdiv[2], load[1], oute[0]
    MA_OUTW(CLKGEN_AEN      , 1);     // pll enable
    rd_val = 0;
    while(rd_val != 0x1) {
        rd_val = MA_INW(CLKGEN_ALOCK) & 0x1;    //check apll lock
    }
    MA_OUTW(CLKGEN_ASEL, 2);     // pll source sel and output sel
    ////////////////////////////////////////

    // DPLL
    MA_OUTW(CLKGEN_DLDCFG   , 3);     // load parameter, newdiv[2], load[1], oute[0]
    MA_OUTW(CLKGEN_DEN      , 1);     // pll enable
    // EPLL
    MA_OUTW(CLKGEN_ELDCFG   , 3);     // load parameter, newdiv[2], load[1], oute[0]
    MA_OUTW(CLKGEN_EEN      , 1);     // pll enable
    //PLLOUT = REF / DIVR_VAL * 4 * DIVF_VAL / DIVQ_VAL
    //VCO    = REF / DIVR_VAL * 4 * DIVF_VAL (1200 ~ 6000 MHz)
    //mpu_clk_2x=VPLL=2133MHz (VCO=4266, 4266/24=177)

    #ifdef POST_SS_SET
        // VPLL
        MA_OUTW(CLKGEN_VRANGE   , 3);     // bypass,range=3(24MHz)
        MA_OUTW(CLKGEN_VDIVR    , 0);     // DIVR_VAL=DIVR[5:0]+1
        MA_OUTW(CLKGEN_VDIVFI   , 39);    // DIVF_VAL=DIVFI[8:0]
        MA_OUTW(CLKGEN_VDIVQ    , 0);     // DIVQ_VAL=2*(DIVQ[4:0]+1)
        MA_OUTW(CLKGEN_VDIVFF   , 0);     // Fractional mode
        MA_OUTW(CLKGEN_VDIVQF   , 0);     // PLLOUTF div=DIVQF[2:0]+1
        MA_OUTW(CLKGEN_VSSCFG   , 0);     // ss cfg
        MA_OUTW(CLKGEN_VLDCFG   , 3);     // load parameter, newdiv[2], load[1], oute[0]
        MA_OUTW(CLKGEN_VEN      , 1);     // pll enable
    #else
        MA_OUTW(CLKGEN_VLDCFG   , 3);     // load parameter, newdiv[2], load[1], oute[0]
        MA_OUTW(CLKGEN_VEN      , 1);     // pll enable
    #endif

    // SPLL
    MA_OUTW(SCLKGEN_ALDCFG  , 3);     // load parameter, newdiv[2], load[1], oute[0]
    MA_OUTW(SCLKGEN_AEN     , 1);     // pll enable

    rd_val = 0;
    while(rd_val != 0x1) {
        rd_val = MA_INW(CLKGEN_DLOCK) & 0x1;    //check dpll lock
    }
    rd_val = 0;
    while(rd_val != 0x1) {
        rd_val = MA_INW(CLKGEN_ELOCK) & 0x1;    //check epll lock
    }
    rd_val = 0;
    while(rd_val != 0x1) {
        rd_val = MA_INW(CLKGEN_VLOCK) & 0x1;    //check vpll lock
    }

    rd_val = 0;
    while(rd_val != 0x1) {
        rd_val = MA_INW(SCLKGEN_ALOCK) & 0x1;    //check sapll lock
    }
    MA_OUTW(SCLKGEN_ASEL, 2);     // pll source sel and output sel

    MA_OUTW(CLKGEN_DSEL, 2);     // pll source sel and output sel
    MA_OUTW(CLKGEN_ESEL, 2);     // pll source sel and output sel
    MA_OUTW(CLKGEN_VSEL, 2);     // pll source sel and output sel
    /////////////////////////////
    printf("MPU Test!\n");
#ifdef FPGA
    MA_OUTW(MLCLKG_BASE+0x74, 29);    // set ratio for fpga(70MHz)

    //////////////////////////////////////////
    // mpu sysm
    MA_OUTW(0xc30f0000+0x4, 0xffff);    // set clk enable
    MA_OUTW(0xc30f0000+0x0, 0xfffd);    // apb reset release


    rd_val = 0;
    while(rd_val != 0x1) {
        rd_val = MA_INW(0xc30f0000+0x20) & 0x1;    //check init calib lock
    }

    printf("MPU init calib done!\n");

    MA_OUTW(0xc30f0000+0x0, 0x0);       // reset release

    //while (1);

#else
    //2133Mbps
    MA_OUTW(MLCLKG_BASE+0x74, 0);    // set ratio, mpu_clk=mpu_clk_x2/2

    // mpu sysm
    MA_OUTW(0xc30f0000+0x4, 0xffff);    // set clk enable
    MA_OUTW(0xc30f0000+0x0, 0xfffc);    // apb/ctl/phy reset release
#endif
}

void wait_vpll_lock(void){
    uint32_t rd_val = 0;
    while(rd_val != 0x1) {
        rd_val = MA_INW(CLKGEN_VLOCK) & 0x1;    //check vpll lock
    }
}

void lpddr4_pll_freq(uint32_t freq){
    if(freq == 2133){
        MA_OUTW(MLCLKG_BASE+0x74, 0);    // set ratio, mpu_clk=mpu_clk_x2/2
    }else if(freq == 1066){
        MA_OUTW(MLCLKG_BASE+0x74, 1);    // set ratio, mpu_clk=mpu_clk_x2/2
    }else if(freq == 533){
        MA_OUTW(MLCLKG_BASE+0x74, 3);    // set ratio, mpu_clk=mpu_clk_x2/2
    }else if(freq == 266){
        MA_OUTW(MLCLKG_BASE+0x74, 7);    // set ratio, mpu_clk=mpu_clk_x2/2
    }else if(freq == 133){
        MA_OUTW(MLCLKG_BASE+0x74, 15);    // set ratio, mpu_clk=mpu_clk_x2/2
    }else if(freq == 66){
        MA_OUTW(MLCLKG_BASE+0x74, 31);    // set ratio, mpu_clk=mpu_clk_x2/2
    }else if(freq == 33){
        MA_OUTW(MLCLKG_BASE+0x74, 64);    // set ratio, mpu_clk=mpu_clk_x2/2
    }else{
        printf("lpddr4 freq set error\n");
    }
    wait_vpll_lock();
}


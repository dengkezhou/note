#include "../lpddr4_common.h"

void loopback_phy_cs_training_disable(int mpu_no){
    MA_OUTW(0xc3000000 + mpu_no*0x100000 + 0x4188,0x00c0c000);
    MA_OUTW(0xc3000000 + mpu_no*0x100000 + 0x4588,0x00c0c000);
    MA_OUTW(0xc3000000 + mpu_no*0x100000 + 0x4988,0x00c0c000);
    MA_OUTW(0xc3000000 + mpu_no*0x100000 + 0x4d88,0x00c0c000);
}

void loopback_phy_ca_slave_dly(int mpu_no,uint32_t loopback_mode){
    uint32_t reg;

    if(loopback_mode == 0){//Internal = 0,External = 1
        reg = (MA_INW(0xc3000000 + mpu_no*0x100000 + 0x50a4)&0x0000ffff)|(0x80<<16);//PHY_ADR0_CLK_WR_SLAVE_DELAY_0
        MA_OUTW(0xc3000000 + mpu_no*0x100000 + 0x50a4,reg);

        reg = (MA_INW(0xc3000000 + mpu_no*0x100000 + 0x50a8)&0xfff800ff)|(0x0<<8);//PHY_ADR1_CLK_WR_SLAVE_DELAY_0
        MA_OUTW(0xc3000000 + mpu_no*0x100000 + 0x50a8,reg);

        reg = (MA_INW(0xc3000000 + mpu_no*0x100000 + 0x50ac)&0xffff0000)|(0x0);//PHY_ADR2_CLK_WR_SLAVE_DELAY_0
        MA_OUTW(0xc3000000 + mpu_no*0x100000 + 0x50ac,reg);

        reg = (MA_INW(0xc3000000 + mpu_no*0x100000 + 0x50b0)&0xffff0000)|(0x0);//PHY_ADR3_CLK_WR_SLAVE_DELAY_0
        MA_OUTW(0xc3000000 + mpu_no*0x100000 + 0x50b0,reg);

        reg = (MA_INW(0xc3000000 + mpu_no*0x100000 + 0x50b4)&0xffff0000)|(0x0);//PHY_ADR4_CLK_WR_SLAVE_DELAY_0
        MA_OUTW(0xc3000000 + mpu_no*0x100000 + 0x50b4,reg);

        reg = (MA_INW(0xc3000000 + mpu_no*0x100000 + 0x50b8)&0xffff0000)|(0x0);//PHY_ADR5_CLK_WR_SLAVE_DELAY_0
        MA_OUTW(0xc3000000 + mpu_no*0x100000 + 0x50b8,reg);
    }else if(loopback_mode == 1){
        reg = (MA_INW(0xc3000000 + mpu_no*0x100000 + 0x50a4)&0x0000ffff)|(0x1c0<<16);//PHY_ADR0_CLK_WR_SLAVE_DELAY_0
        MA_OUTW(0xc3000000 + mpu_no*0x100000 + 0x50a4,reg);

        reg = (MA_INW(0xc3000000 + mpu_no*0x100000 + 0x50a8)&0xfff800ff)|(0x140<<8);//PHY_ADR1_CLK_WR_SLAVE_DELAY_0
        MA_OUTW(0xc3000000 + mpu_no*0x100000 + 0x50a8,reg);

        reg = (MA_INW(0xc3000000 + mpu_no*0x100000 + 0x50ac)&0xffff0000)|(0x140);//PHY_ADR2_CLK_WR_SLAVE_DELAY_0
        MA_OUTW(0xc3000000 + mpu_no*0x100000 + 0x50ac,reg);

        reg = (MA_INW(0xc3000000 + mpu_no*0x100000 + 0x50b0)&0xffff0000)|(0x140);//PHY_ADR3_CLK_WR_SLAVE_DELAY_0
        MA_OUTW(0xc3000000 + mpu_no*0x100000 + 0x50b0,reg);

        reg = (MA_INW(0xc3000000 + mpu_no*0x100000 + 0x50b4)&0xffff0000)|(0x140);//PHY_ADR4_CLK_WR_SLAVE_DELAY_0
        MA_OUTW(0xc3000000 + mpu_no*0x100000 + 0x50b4,reg);

        reg = (MA_INW(0xc3000000 + mpu_no*0x100000 + 0x50b8)&0xffff0000)|(0x140);//PHY_ADR5_CLK_WR_SLAVE_DELAY_0
        MA_OUTW(0xc3000000 + mpu_no*0x100000 + 0x50b8,reg);
    }
}

void loopback_phy_adr_slave_dly(int mpu_no){
    uint32_t reg;

    reg = (MA_INW(0xc3000000 + mpu_no*0x100000 + 0x55cc)&0xffff0000)|(0x28);//PHY_GRP0_SLAVE_DELAY_0
    MA_OUTW(0xc3000000 + mpu_no*0x100000 + 0x55cc,reg);
    reg = (MA_INW(0xc3000000 + mpu_no*0x100000 + 0x55d4)&0xffff0000)|(0x3c);//PHY_GRP0_SLAVE_DELAY_1
    MA_OUTW(0xc3000000 + mpu_no*0x100000 + 0x55d4,reg);

    reg = (MA_INW(0xc3000000 + mpu_no*0x100000 + 0x55cc)&0x0000ffff)|(0x28<<16);//PHY_GRP1_SLAVE_DELAY_0
    MA_OUTW(0xc3000000 + mpu_no*0x100000 + 0x55cc,reg);
    reg = (MA_INW(0xc3000000 + mpu_no*0x100000 + 0x55d4)&0x0000ffff)|(0x3c<<16);//PHY_GRP1_SLAVE_DELAY_1
    MA_OUTW(0xc3000000 + mpu_no*0x100000 + 0x55d4,reg);

    reg = (MA_INW(0xc3000000 + mpu_no*0x100000 + 0x55d0)&0xffff0000)|(0x28);//PHY_GRP2_SLAVE_DELAY_0
    MA_OUTW(0xc3000000 + mpu_no*0x100000 + 0x55d0,reg);
    reg = (MA_INW(0xc3000000 + mpu_no*0x100000 + 0x55d8)&0xffff0000)|(0x3c);//PHY_GRP2_SLAVE_DELAY_1
    MA_OUTW(0xc3000000 + mpu_no*0x100000 + 0x55d8,reg);

    reg = (MA_INW(0xc3000000 + mpu_no*0x100000 + 0x55d0)&0x0000ffff)|(0x28<<16);//PHY_GRP3_SLAVE_DELAY_0
    MA_OUTW(0xc3000000 + mpu_no*0x100000 + 0x55d0,reg);
    reg = (MA_INW(0xc3000000 + mpu_no*0x100000 + 0x55d8)&0x0000ffff)|(0x3c<<16);//PHY_GRP3_SLAVE_DELAY_1
    MA_OUTW(0xc3000000 + mpu_no*0x100000 + 0x55d8,reg);
}

void loopback_phy_wrdqs_slave_dly(int mpu_no){
    uint32_t reg;

    reg = (MA_INW(0xc3000000 + mpu_no*0x100000 + 0x41cc)&0xffff0000)|(0x280);//PHY_CLK_WRDQ0_SLAVE_DELAY_0
    MA_OUTW(0xc3000000 + mpu_no*0x100000 + 0x41cc,reg);
    reg = (MA_INW(0xc3000000 + mpu_no*0x100000 + 0x45cc)&0xffff0000)|(0x280);//PHY_CLK_WRDQ0_SLAVE_DELAY_1
    MA_OUTW(0xc3000000 + mpu_no*0x100000 + 0x45cc,reg);
    reg = (MA_INW(0xc3000000 + mpu_no*0x100000 + 0x49cc)&0xffff0000)|(0x280);//PHY_CLK_WRDQ0_SLAVE_DELAY_2
    MA_OUTW(0xc3000000 + mpu_no*0x100000 + 0x49cc,reg);
    reg = (MA_INW(0xc3000000 + mpu_no*0x100000 + 0x4dcc)&0xffff0000)|(0x280);//PHY_CLK_WRDQ0_SLAVE_DELAY_3
    MA_OUTW(0xc3000000 + mpu_no*0x100000 + 0x4dcc,reg);

    reg = (MA_INW(0xc3000000 + mpu_no*0x100000 + 0x41cc)&0x0000ffff)|(0x280<<16);//PHY_CLK_WRDQ1_SLAVE_DELAY_0
    MA_OUTW(0xc3000000 + mpu_no*0x100000 + 0x41cc,reg);
    reg = (MA_INW(0xc3000000 + mpu_no*0x100000 + 0x45cc)&0x0000ffff)|(0x280<<16);//PHY_CLK_WRDQ1_SLAVE_DELAY_1
    MA_OUTW(0xc3000000 + mpu_no*0x100000 + 0x45cc,reg);
    reg = (MA_INW(0xc3000000 + mpu_no*0x100000 + 0x49cc)&0x0000ffff)|(0x280<<16);//PHY_CLK_WRDQ1_SLAVE_DELAY_2
    MA_OUTW(0xc3000000 + mpu_no*0x100000 + 0x49cc,reg);
    reg = (MA_INW(0xc3000000 + mpu_no*0x100000 + 0x4dcc)&0x0000ffff)|(0x280<<16);//PHY_CLK_WRDQ1_SLAVE_DELAY_3
    MA_OUTW(0xc3000000 + mpu_no*0x100000 + 0x4dcc,reg);

    reg = (MA_INW(0xc3000000 + mpu_no*0x100000 + 0x41d0)&0xffff0000)|(0x280);//PHY_CLK_WRDQ2_SLAVE_DELAY_0
    MA_OUTW(0xc3000000 + mpu_no*0x100000 + 0x41d0,reg);
    reg = (MA_INW(0xc3000000 + mpu_no*0x100000 + 0x45d0)&0xffff0000)|(0x280);//PHY_CLK_WRDQ2_SLAVE_DELAY_1
    MA_OUTW(0xc3000000 + mpu_no*0x100000 + 0x45d0,reg);
    reg = (MA_INW(0xc3000000 + mpu_no*0x100000 + 0x49d0)&0xffff0000)|(0x280);//PHY_CLK_WRDQ2_SLAVE_DELAY_2
    MA_OUTW(0xc3000000 + mpu_no*0x100000 + 0x49d0,reg);
    reg = (MA_INW(0xc3000000 + mpu_no*0x100000 + 0x4dd0)&0xffff0000)|(0x280);//PHY_CLK_WRDQ2_SLAVE_DELAY_3
    MA_OUTW(0xc3000000 + mpu_no*0x100000 + 0x4dd0,reg);

    reg = (MA_INW(0xc3000000 + mpu_no*0x100000 + 0x41d0)&0x0000ffff)|(0x280<<16);//PHY_CLK_WRDQ3_SLAVE_DELAY_0
    MA_OUTW(0xc3000000 + mpu_no*0x100000 + 0x41d0,reg);
    reg = (MA_INW(0xc3000000 + mpu_no*0x100000 + 0x45d0)&0x0000ffff)|(0x280<<16);//PHY_CLK_WRDQ3_SLAVE_DELAY_1
    MA_OUTW(0xc3000000 + mpu_no*0x100000 + 0x45d0,reg);
    reg = (MA_INW(0xc3000000 + mpu_no*0x100000 + 0x49d0)&0x0000ffff)|(0x280<<16);//PHY_CLK_WRDQ3_SLAVE_DELAY_2
    MA_OUTW(0xc3000000 + mpu_no*0x100000 + 0x49d0,reg);
    reg = (MA_INW(0xc3000000 + mpu_no*0x100000 + 0x4dd0)&0x0000ffff)|(0x280<<16);//PHY_CLK_WRDQ3_SLAVE_DELAY_3
    MA_OUTW(0xc3000000 + mpu_no*0x100000 + 0x4dd0,reg);

    reg = (MA_INW(0xc3000000 + mpu_no*0x100000 + 0x41d4)&0xffff0000)|(0x280);//PHY_CLK_WRDQ4_SLAVE_DELAY_0
    MA_OUTW(0xc3000000 + mpu_no*0x100000 + 0x41d4,reg);
    reg = (MA_INW(0xc3000000 + mpu_no*0x100000 + 0x45d4)&0xffff0000)|(0x280);//PHY_CLK_WRDQ4_SLAVE_DELAY_1
    MA_OUTW(0xc3000000 + mpu_no*0x100000 + 0x45d4,reg);
    reg = (MA_INW(0xc3000000 + mpu_no*0x100000 + 0x49d4)&0xffff0000)|(0x280);//PHY_CLK_WRDQ4_SLAVE_DELAY_2
    MA_OUTW(0xc3000000 + mpu_no*0x100000 + 0x49d4,reg);
    reg = (MA_INW(0xc3000000 + mpu_no*0x100000 + 0x4dd4)&0xffff0000)|(0x280);//PHY_CLK_WRDQ4_SLAVE_DELAY_3
    MA_OUTW(0xc3000000 + mpu_no*0x100000 + 0x4dd4,reg);

    reg = (MA_INW(0xc3000000 + mpu_no*0x100000 + 0x41d4)&0x0000ffff)|(0x280<<16);//PHY_CLK_WRDQ5_SLAVE_DELAY_0
    MA_OUTW(0xc3000000 + mpu_no*0x100000 + 0x41d4,reg);
    reg = (MA_INW(0xc3000000 + mpu_no*0x100000 + 0x45d4)&0x0000ffff)|(0x280<<16);//PHY_CLK_WRDQ5_SLAVE_DELAY_1
    MA_OUTW(0xc3000000 + mpu_no*0x100000 + 0x45d4,reg);
    reg = (MA_INW(0xc3000000 + mpu_no*0x100000 + 0x49d4)&0x0000ffff)|(0x280<<16);//PHY_CLK_WRDQ5_SLAVE_DELAY_2
    MA_OUTW(0xc3000000 + mpu_no*0x100000 + 0x49d4,reg);
    reg = (MA_INW(0xc3000000 + mpu_no*0x100000 + 0x4dd4)&0x0000ffff)|(0x280<<16);//PHY_CLK_WRDQ5_SLAVE_DELAY_3
    MA_OUTW(0xc3000000 + mpu_no*0x100000 + 0x4dd4,reg);

    reg = (MA_INW(0xc3000000 + mpu_no*0x100000 + 0x41d8)&0xffff0000)|(0x280);//PHY_CLK_WRDQ6_SLAVE_DELAY_0
    MA_OUTW(0xc3000000 + mpu_no*0x100000 + 0x41d8,reg);
    reg = (MA_INW(0xc3000000 + mpu_no*0x100000 + 0x45d8)&0xffff0000)|(0x280);//PHY_CLK_WRDQ6_SLAVE_DELAY_1
    MA_OUTW(0xc3000000 + mpu_no*0x100000 + 0x45d8,reg);
    reg = (MA_INW(0xc3000000 + mpu_no*0x100000 + 0x49d8)&0xffff0000)|(0x280);//PHY_CLK_WRDQ6_SLAVE_DELAY_2
    MA_OUTW(0xc3000000 + mpu_no*0x100000 + 0x49d8,reg);
    reg = (MA_INW(0xc3000000 + mpu_no*0x100000 + 0x4dd8)&0xffff0000)|(0x280);//PHY_CLK_WRDQ6_SLAVE_DELAY_3
    MA_OUTW(0xc3000000 + mpu_no*0x100000 + 0x4dd8,reg);

    reg = (MA_INW(0xc3000000 + mpu_no*0x100000 + 0x41d8)&0x0000ffff)|(0x280<<16);//PHY_CLK_WRDQ7_SLAVE_DELAY_0
    MA_OUTW(0xc3000000 + mpu_no*0x100000 + 0x41d8,reg);
    reg = (MA_INW(0xc3000000 + mpu_no*0x100000 + 0x45d8)&0x0000ffff)|(0x280<<16);//PHY_CLK_WRDQ7_SLAVE_DELAY_1
    MA_OUTW(0xc3000000 + mpu_no*0x100000 + 0x45d8,reg);
    reg = (MA_INW(0xc3000000 + mpu_no*0x100000 + 0x49d8)&0x0000ffff)|(0x280<<16);//PHY_CLK_WRDQ7_SLAVE_DELAY_2
    MA_OUTW(0xc3000000 + mpu_no*0x100000 + 0x49d8,reg);
    reg = (MA_INW(0xc3000000 + mpu_no*0x100000 + 0x4dd8)&0x0000ffff)|(0x280<<16);//PHY_CLK_WRDQ7_SLAVE_DELAY_3
    MA_OUTW(0xc3000000 + mpu_no*0x100000 + 0x4dd8,reg);

    reg = (MA_INW(0xc3000000 + mpu_no*0x100000 + 0x41dc)&0xffff0000)|(0x280);//PHY_CLK_WRDM_SLAVE_DELAY_0
    MA_OUTW(0xc3000000 + mpu_no*0x100000 + 0x41dc,reg);
    reg = (MA_INW(0xc3000000 + mpu_no*0x100000 + 0x45dc)&0xffff0000)|(0x280);//PHY_CLK_WRDM_SLAVE_DELAY_1
    MA_OUTW(0xc3000000 + mpu_no*0x100000 + 0x45dc,reg);
    reg = (MA_INW(0xc3000000 + mpu_no*0x100000 + 0x49dc)&0xffff0000)|(0x280);//PHY_CLK_WRDM_SLAVE_DELAY_2
    MA_OUTW(0xc3000000 + mpu_no*0x100000 + 0x49dc,reg);
    reg = (MA_INW(0xc3000000 + mpu_no*0x100000 + 0x4ddc)&0xffff0000)|(0x280);//PHY_CLK_WRDM_SLAVE_DELAY_3
    MA_OUTW(0xc3000000 + mpu_no*0x100000 + 0x4ddc,reg);

    reg = (MA_INW(0xc3000000 + mpu_no*0x100000 + 0x41dc)&0x0000ffff)|(0x280<<16);//PHY_CLK_WRDQS_SLAVE_DELAY_0
    MA_OUTW(0xc3000000 + mpu_no*0x100000 + 0x41dc,reg);
    reg = (MA_INW(0xc3000000 + mpu_no*0x100000 + 0x45dc)&0x0000ffff)|(0x280<<16);//PHY_CLK_WRDQS_SLAVE_DELAY_1
    MA_OUTW(0xc3000000 + mpu_no*0x100000 + 0x45dc,reg);
    reg = (MA_INW(0xc3000000 + mpu_no*0x100000 + 0x49dc)&0x0000ffff)|(0x280<<16);//PHY_CLK_WRDQS_SLAVE_DELAY_2
    MA_OUTW(0xc3000000 + mpu_no*0x100000 + 0x49dc,reg);
    reg = (MA_INW(0xc3000000 + mpu_no*0x100000 + 0x4ddc)&0x0000ffff)|(0x280<<16);//PHY_CLK_WRDQS_SLAVE_DELAY_3
    MA_OUTW(0xc3000000 + mpu_no*0x100000 + 0x4ddc,reg);
}

void loopback_phy_dqs_gate_slave_dly(int mpu_no){
    uint32_t reg;

    reg = (MA_INW(0xc3000000 + mpu_no*0x100000 + 0x4208)&0xfffffff0)|(0x2);//PHY_RDDQS_LATENCY_ADJUST_0
    MA_OUTW(0xc3000000 + mpu_no*0x100000 + 0x4208,reg);
    reg = (MA_INW(0xc3000000 + mpu_no*0x100000 + 0x4608)&0xfffffff0)|(0x2);//PHY_RDDQS_LATENCY_ADJUST_1
    MA_OUTW(0xc3000000 + mpu_no*0x100000 + 0x4608,reg);
    reg = (MA_INW(0xc3000000 + mpu_no*0x100000 + 0x4a08)&0xfffffff0)|(0x2);//PHY_RDDQS_LATENCY_ADJUST_2
    MA_OUTW(0xc3000000 + mpu_no*0x100000 + 0x4a08,reg);
    reg = (MA_INW(0xc3000000 + mpu_no*0x100000 + 0x4e08)&0xfffffff0)|(0x2);//PHY_RDDQS_LATENCY_ADJUST_3
    MA_OUTW(0xc3000000 + mpu_no*0x100000 + 0x4e08,reg);

    reg = (MA_INW(0xc3000000 + mpu_no*0x100000 + 0x4180)&0xfffffff0)|(0x0);//PHY_IO_PAD_DELAY_TIMING_0
    MA_OUTW(0xc3000000 + mpu_no*0x100000 + 0x4180,reg);
    reg = (MA_INW(0xc3000000 + mpu_no*0x100000 + 0x4580)&0xfffffff0)|(0x0);//PHY_IO_PAD_DELAY_TIMING_1
    MA_OUTW(0xc3000000 + mpu_no*0x100000 + 0x4580,reg);
    reg = (MA_INW(0xc3000000 + mpu_no*0x100000 + 0x4980)&0xfffffff0)|(0x0);//PHY_IO_PAD_DELAY_TIMING_2
    MA_OUTW(0xc3000000 + mpu_no*0x100000 + 0x4980,reg);
    reg = (MA_INW(0xc3000000 + mpu_no*0x100000 + 0x4d80)&0xfffffff0)|(0x0);//PHY_IO_PAD_DELAY_TIMING_3
    MA_OUTW(0xc3000000 + mpu_no*0x100000 + 0x4d80,reg);
    
    reg = (MA_INW(0xc3000000 + mpu_no*0x100000 + 0x4004)&0xfffffff0)|(0x0);//PHY_IO_PAD_DELAY_TIMING_BYPASS_0
    MA_OUTW(0xc3000000 + mpu_no*0x100000 + 0x4004,reg);
    reg = (MA_INW(0xc3000000 + mpu_no*0x100000 + 0x4404)&0xfffffff0)|(0x0);//PHY_IO_PAD_DELAY_TIMING_BYPASS_1
    MA_OUTW(0xc3000000 + mpu_no*0x100000 + 0x4404,reg);
    reg = (MA_INW(0xc3000000 + mpu_no*0x100000 + 0x4804)&0xfffffff0)|(0x0);//PHY_IO_PAD_DELAY_TIMING_BYPASS_2
    MA_OUTW(0xc3000000 + mpu_no*0x100000 + 0x4804,reg);
    reg = (MA_INW(0xc3000000 + mpu_no*0x100000 + 0x4c04)&0xfffffff0)|(0x0);//PHY_IO_PAD_DELAY_TIMING_BYPASS_3
    MA_OUTW(0xc3000000 + mpu_no*0x100000 + 0x4c04,reg);

    reg = (MA_INW(0xc3000000 + mpu_no*0x100000 + 0x4204)&0x000003ff)|(0x1c2<<16);//PHY_RDDQS_GATE_SLAVE_DELAY_0
    MA_OUTW(0xc3000000 + mpu_no*0x100000 + 0x4204,reg);
    reg = (MA_INW(0xc3000000 + mpu_no*0x100000 + 0x4604)&0x000003ff)|(0x1c2<<16);//PHY_RDDQS_GATE_SLAVE_DELAY_1
    MA_OUTW(0xc3000000 + mpu_no*0x100000 + 0x4604,reg);
    reg = (MA_INW(0xc3000000 + mpu_no*0x100000 + 0x4a04)&0x000003ff)|(0x1c2<<16);//PHY_RDDQS_GATE_SLAVE_DELAY_2
    MA_OUTW(0xc3000000 + mpu_no*0x100000 + 0x4a04,reg);
    reg = (MA_INW(0xc3000000 + mpu_no*0x100000 + 0x4e04)&0x000003ff)|(0x1c2<<16);//PHY_RDDQS_GATE_SLAVE_DELAY_3
    MA_OUTW(0xc3000000 + mpu_no*0x100000 + 0x4e04,reg);
}

void loopback_phy_rddqs_slave_dly(int mpu_no){
    uint32_t reg;

    reg = (MA_INW(0xc3000000 + mpu_no*0x100000 + 0x41e0)&0x00ff)|(0x00<<8);//PHY_RDDQS_DQ0_RISE_SLAVE_DELAY_0
    MA_OUTW(0xc3000000 + mpu_no*0x100000 + 0x41e0,reg);
    reg = (MA_INW(0xc3000000 + mpu_no*0x100000 + 0x41e4)&0xfffffc00)|(0x00);//PHY_RDDQS_DQ0_FALL_SLAVE_DELAY_0
    MA_OUTW(0xc3000000 + mpu_no*0x100000 + 0x41e4,reg);
    reg = (MA_INW(0xc3000000 + mpu_no*0x100000 + 0x45e0)&0x00ff)|(0x00<<8);//PHY_RDDQS_DQ0_RISE_SLAVE_DELAY_1
    MA_OUTW(0xc3000000 + mpu_no*0x100000 + 0x45e0,reg);
    reg = (MA_INW(0xc3000000 + mpu_no*0x100000 + 0x45e4)&0xfffffc00)|(0x00);//PHY_RDDQS_DQ0_FALL_SLAVE_DELAY_1
    MA_OUTW(0xc3000000 + mpu_no*0x100000 + 0x45e4,reg);
    reg = (MA_INW(0xc3000000 + mpu_no*0x100000 + 0x49e0)&0x00ff)|(0x00<<8);//PHY_RDDQS_DQ0_RISE_SLAVE_DELAY_2
    MA_OUTW(0xc3000000 + mpu_no*0x100000 + 0x49e0,reg);
    reg = (MA_INW(0xc3000000 + mpu_no*0x100000 + 0x49e4)&0xfffffc00)|(0x00);//PHY_RDDQS_DQ0_FALL_SLAVE_DELAY_2
    MA_OUTW(0xc3000000 + mpu_no*0x100000 + 0x49e4,reg);
    reg = (MA_INW(0xc3000000 + mpu_no*0x100000 + 0x4de0)&0x00ff)|(0x00<<8);//PHY_RDDQS_DQ0_RISE_SLAVE_DELAY_3
    MA_OUTW(0xc3000000 + mpu_no*0x100000 + 0x4de0,reg);
    reg = (MA_INW(0xc3000000 + mpu_no*0x100000 + 0x4de4)&0xfffffc00)|(0x00);//PHY_RDDQS_DQ0_FALL_SLAVE_DELAY_3
    MA_OUTW(0xc3000000 + mpu_no*0x100000 + 0x4de4,reg);

    reg = (MA_INW(0xc3000000 + mpu_no*0x100000 + 0x41e4)&0x000003ff)|(0x00<<16);//PHY_RDDQS_DQ1_RISE_SLAVE_DELAY_0
    MA_OUTW(0xc3000000 + mpu_no*0x100000 + 0x41e4,reg);
    reg = (MA_INW(0xc3000000 + mpu_no*0x100000 + 0x41e8)&0xfffffc00)|(0x00);//PHY_RDDQS_DQ1_FALL_SLAVE_DELAY_0
    MA_OUTW(0xc3000000 + mpu_no*0x100000 + 0x41e8,reg);
    reg = (MA_INW(0xc3000000 + mpu_no*0x100000 + 0x45e4)&0x000003ff)|(0x00<<16);//PHY_RDDQS_DQ1_RISE_SLAVE_DELAY_1
    MA_OUTW(0xc3000000 + mpu_no*0x100000 + 0x45e4,reg);
    reg = (MA_INW(0xc3000000 + mpu_no*0x100000 + 0x45e8)&0xfffffc00)|(0x00);//PHY_RDDQS_DQ1_FALL_SLAVE_DELAY_1
    MA_OUTW(0xc3000000 + mpu_no*0x100000 + 0x45e8,reg);
    reg = (MA_INW(0xc3000000 + mpu_no*0x100000 + 0x49e4)&0x000003ff)|(0x00<<16);//PHY_RDDQS_DQ1_RISE_SLAVE_DELAY_2
    MA_OUTW(0xc3000000 + mpu_no*0x100000 + 0x49e4,reg);
    reg = (MA_INW(0xc3000000 + mpu_no*0x100000 + 0x49e8)&0xfffffc00)|(0x00);//PHY_RDDQS_DQ1_FALL_SLAVE_DELAY_2
    MA_OUTW(0xc3000000 + mpu_no*0x100000 + 0x49e8,reg);
    reg = (MA_INW(0xc3000000 + mpu_no*0x100000 + 0x4de4)&0x000003ff)|(0x00<<16);//PHY_RDDQS_DQ1_RISE_SLAVE_DELAY_3
    MA_OUTW(0xc3000000 + mpu_no*0x100000 + 0x4de4,reg);
    reg = (MA_INW(0xc3000000 + mpu_no*0x100000 + 0x4de8)&0xfffffc00)|(0x00);//PHY_RDDQS_DQ1_FALL_SLAVE_DELAY_3
    MA_OUTW(0xc3000000 + mpu_no*0x100000 + 0x4de8,reg);
        
    reg = (MA_INW(0xc3000000 + mpu_no*0x100000 + 0x41e8)&0x000003ff)|(0x00<<16);//PHY_RDDQS_DQ2_RISE_SLAVE_DELAY_0
    MA_OUTW(0xc3000000 + mpu_no*0x100000 + 0x41e8,reg);
    reg = (MA_INW(0xc3000000 + mpu_no*0x100000 + 0x41ec)&0xfffffc00)|(0x00);//PHY_RDDQS_DQ2_FALL_SLAVE_DELAY_0
    MA_OUTW(0xc3000000 + mpu_no*0x100000 + 0x41ec,reg);
    reg = (MA_INW(0xc3000000 + mpu_no*0x100000 + 0x45e8)&0x000003ff)|(0x00<<16);//PHY_RDDQS_DQ2_RISE_SLAVE_DELAY_1
    MA_OUTW(0xc3000000 + mpu_no*0x100000 + 0x45e8,reg);
    reg = (MA_INW(0xc3000000 + mpu_no*0x100000 + 0x45ec)&0xfffffc00)|(0x00);//PHY_RDDQS_DQ2_FALL_SLAVE_DELAY_1
    MA_OUTW(0xc3000000 + mpu_no*0x100000 + 0x45ec,reg);
    reg = (MA_INW(0xc3000000 + mpu_no*0x100000 + 0x49e8)&0x000003ff)|(0x00<<16);//PHY_RDDQS_DQ2_RISE_SLAVE_DELAY_2
    MA_OUTW(0xc3000000 + mpu_no*0x100000 + 0x49e8,reg);
    reg = (MA_INW(0xc3000000 + mpu_no*0x100000 + 0x49ec)&0xfffffc00)|(0x00);//PHY_RDDQS_DQ2_FALL_SLAVE_DELAY_2
    MA_OUTW(0xc3000000 + mpu_no*0x100000 + 0x49ec,reg);
    reg = (MA_INW(0xc3000000 + mpu_no*0x100000 + 0x4de8)&0x000003ff)|(0x00<<16);//PHY_RDDQS_DQ2_RISE_SLAVE_DELAY_3
    MA_OUTW(0xc3000000 + mpu_no*0x100000 + 0x4de8,reg);
    reg = (MA_INW(0xc3000000 + mpu_no*0x100000 + 0x4dec)&0xfffffc00)|(0x00);//PHY_RDDQS_DQ2_FALL_SLAVE_DELAY_3
    MA_OUTW(0xc3000000 + mpu_no*0x100000 + 0x4dec,reg);

    reg = (MA_INW(0xc3000000 + mpu_no*0x100000 + 0x41ec)&0x000003ff)|(0x00<<16);//PHY_RDDQS_DQ3_RISE_SLAVE_DELAY_0
    MA_OUTW(0xc3000000 + mpu_no*0x100000 + 0x41ec,reg);
    reg = (MA_INW(0xc3000000 + mpu_no*0x100000 + 0x41f0)&0xfffffc00)|(0x00);//PHY_RDDQS_DQ3_FALL_SLAVE_DELAY_0
    MA_OUTW(0xc3000000 + mpu_no*0x100000 + 0x41f0,reg);
    reg = (MA_INW(0xc3000000 + mpu_no*0x100000 + 0x45ec)&0x000003ff)|(0x00<<16);//PHY_RDDQS_DQ3_RISE_SLAVE_DELAY_1
    MA_OUTW(0xc3000000 + mpu_no*0x100000 + 0x45ec,reg);
    reg = (MA_INW(0xc3000000 + mpu_no*0x100000 + 0x45f0)&0xfffffc00)|(0x00);//PHY_RDDQS_DQ3_FALL_SLAVE_DELAY_1
    MA_OUTW(0xc3000000 + mpu_no*0x100000 + 0x45f0,reg);
    reg = (MA_INW(0xc3000000 + mpu_no*0x100000 + 0x49ec)&0x000003ff)|(0x00<<16);//PHY_RDDQS_DQ3_RISE_SLAVE_DELAY_2
    MA_OUTW(0xc3000000 + mpu_no*0x100000 + 0x49ec,reg);
    reg = (MA_INW(0xc3000000 + mpu_no*0x100000 + 0x49f0)&0xfffffc00)|(0x00);//PHY_RDDQS_DQ3_FALL_SLAVE_DELAY_2
    MA_OUTW(0xc3000000 + mpu_no*0x100000 + 0x49f0,reg);
    reg = (MA_INW(0xc3000000 + mpu_no*0x100000 + 0x4dec)&0x000003ff)|(0x00<<16);//PHY_RDDQS_DQ3_RISE_SLAVE_DELAY_3
    MA_OUTW(0xc3000000 + mpu_no*0x100000 + 0x4dec,reg);
    reg = (MA_INW(0xc3000000 + mpu_no*0x100000 + 0x4df0)&0xfffffc00)|(0x00);//PHY_RDDQS_DQ3_FALL_SLAVE_DELAY_3
    MA_OUTW(0xc3000000 + mpu_no*0x100000 + 0x4df0,reg);

    reg = (MA_INW(0xc3000000 + mpu_no*0x100000 + 0x41f0)&0x000003ff)|(0x00<<16);//PHY_RDDQS_DQ4_RISE_SLAVE_DELAY_0
    MA_OUTW(0xc3000000 + mpu_no*0x100000 + 0x41f0,reg);
    reg = (MA_INW(0xc3000000 + mpu_no*0x100000 + 0x41f4)&0xfffffc00)|(0x00);//PHY_RDDQS_DQ4_FALL_SLAVE_DELAY_0
    MA_OUTW(0xc3000000 + mpu_no*0x100000 + 0x41f4,reg);
    reg = (MA_INW(0xc3000000 + mpu_no*0x100000 + 0x45f0)&0x000003ff)|(0x00<<16);//PHY_RDDQS_DQ4_RISE_SLAVE_DELAY_1
    MA_OUTW(0xc3000000 + mpu_no*0x100000 + 0x45f0,reg);
    reg = (MA_INW(0xc3000000 + mpu_no*0x100000 + 0x45f4)&0xfffffc00)|(0x00);//PHY_RDDQS_DQ4_FALL_SLAVE_DELAY_1
    MA_OUTW(0xc3000000 + mpu_no*0x100000 + 0x45f4,reg);
    reg = (MA_INW(0xc3000000 + mpu_no*0x100000 + 0x49f0)&0x000003ff)|(0x00<<16);//PHY_RDDQS_DQ4_RISE_SLAVE_DELAY_2
    MA_OUTW(0xc3000000 + mpu_no*0x100000 + 0x49f0,reg);
    reg = (MA_INW(0xc3000000 + mpu_no*0x100000 + 0x49f4)&0xfffffc00)|(0x00);//PHY_RDDQS_DQ4_FALL_SLAVE_DELAY_2
    MA_OUTW(0xc3000000 + mpu_no*0x100000 + 0x49f4,reg);
    reg = (MA_INW(0xc3000000 + mpu_no*0x100000 + 0x4df0)&0x000003ff)|(0x00<<16);//PHY_RDDQS_DQ4_RISE_SLAVE_DELAY_3
    MA_OUTW(0xc3000000 + mpu_no*0x100000 + 0x4df0,reg);
    reg = (MA_INW(0xc3000000 + mpu_no*0x100000 + 0x4df4)&0xfffffc00)|(0x00);//PHY_RDDQS_DQ4_FALL_SLAVE_DELAY_3
    MA_OUTW(0xc3000000 + mpu_no*0x100000 + 0x4df4,reg);

    reg = (MA_INW(0xc3000000 + mpu_no*0x100000 + 0x41f4)&0x000003ff)|(0x00<<16);//PHY_RDDQS_DQ5_RISE_SLAVE_DELAY_0
    MA_OUTW(0xc3000000 + mpu_no*0x100000 + 0x41f4,reg);
    reg = (MA_INW(0xc3000000 + mpu_no*0x100000 + 0x41f8)&0xfffffc00)|(0x00);//PHY_RDDQS_DQ5_FALL_SLAVE_DELAY_0
    MA_OUTW(0xc3000000 + mpu_no*0x100000 + 0x41f8,reg);
    reg = (MA_INW(0xc3000000 + mpu_no*0x100000 + 0x45f4)&0x000003ff)|(0x00<<16);//PHY_RDDQS_DQ5_RISE_SLAVE_DELAY_1
    MA_OUTW(0xc3000000 + mpu_no*0x100000 + 0x45f4,reg);
    reg = (MA_INW(0xc3000000 + mpu_no*0x100000 + 0x45f8)&0xfffffc00)|(0x00);//PHY_RDDQS_DQ5_FALL_SLAVE_DELAY_1
    MA_OUTW(0xc3000000 + mpu_no*0x100000 + 0x45f8,reg);
    reg = (MA_INW(0xc3000000 + mpu_no*0x100000 + 0x49f4)&0x000003ff)|(0x00<<16);//PHY_RDDQS_DQ5_RISE_SLAVE_DELAY_2
    MA_OUTW(0xc3000000 + mpu_no*0x100000 + 0x49f4,reg);
    reg = (MA_INW(0xc3000000 + mpu_no*0x100000 + 0x49f8)&0xfffffc00)|(0x00);//PHY_RDDQS_DQ5_FALL_SLAVE_DELAY_2
    MA_OUTW(0xc3000000 + mpu_no*0x100000 + 0x49f8,reg);
    reg = (MA_INW(0xc3000000 + mpu_no*0x100000 + 0x4df4)&0x000003ff)|(0x00<<16);//PHY_RDDQS_DQ5_RISE_SLAVE_DELAY_3
    MA_OUTW(0xc3000000 + mpu_no*0x100000 + 0x4df4,reg);
    reg = (MA_INW(0xc3000000 + mpu_no*0x100000 + 0x4df8)&0xfffffc00)|(0x00);//PHY_RDDQS_DQ5_FALL_SLAVE_DELAY_3
    MA_OUTW(0xc3000000 + mpu_no*0x100000 + 0x4df8,reg);

    reg = (MA_INW(0xc3000000 + mpu_no*0x100000 + 0x41f8)&0x000003ff)|(0x00<<16);//PHY_RDDQS_DQ6_RISE_SLAVE_DELAY_0
    MA_OUTW(0xc3000000 + mpu_no*0x100000 + 0x41f8,reg);
    reg = (MA_INW(0xc3000000 + mpu_no*0x100000 + 0x41fc)&0xfffffc00)|(0x00);//PHY_RDDQS_DQ6_FALL_SLAVE_DELAY_0
    MA_OUTW(0xc3000000 + mpu_no*0x100000 + 0x41fc,reg);
    reg = (MA_INW(0xc3000000 + mpu_no*0x100000 + 0x45f8)&0x000003ff)|(0x00<<16);//PHY_RDDQS_DQ6_RISE_SLAVE_DELAY_1
    MA_OUTW(0xc3000000 + mpu_no*0x100000 + 0x45f8,reg);
    reg = (MA_INW(0xc3000000 + mpu_no*0x100000 + 0x45fc)&0xfffffc00)|(0x00);//PHY_RDDQS_DQ6_FALL_SLAVE_DELAY_1
    MA_OUTW(0xc3000000 + mpu_no*0x100000 + 0x45fc,reg);
    reg = (MA_INW(0xc3000000 + mpu_no*0x100000 + 0x49f8)&0x000003ff)|(0x00<<16);//PHY_RDDQS_DQ6_RISE_SLAVE_DELAY_2
    MA_OUTW(0xc3000000 + mpu_no*0x100000 + 0x49f8,reg);
    reg = (MA_INW(0xc3000000 + mpu_no*0x100000 + 0x49fc)&0xfffffc00)|(0x00);//PHY_RDDQS_DQ6_FALL_SLAVE_DELAY_2
    MA_OUTW(0xc3000000 + mpu_no*0x100000 + 0x49fc,reg);
    reg = (MA_INW(0xc3000000 + mpu_no*0x100000 + 0x4df8)&0x000003ff)|(0x00<<16);//PHY_RDDQS_DQ6_RISE_SLAVE_DELAY_3
    MA_OUTW(0xc3000000 + mpu_no*0x100000 + 0x4df8,reg);
    reg = (MA_INW(0xc3000000 + mpu_no*0x100000 + 0x4dfc)&0xfffffc00)|(0x00);//PHY_RDDQS_DQ6_FALL_SLAVE_DELAY_3
    MA_OUTW(0xc3000000 + mpu_no*0x100000 + 0x4dfc,reg);

    reg = (MA_INW(0xc3000000 + mpu_no*0x100000 + 0x41fc)&0x000003ff)|(0x00<<16);//PHY_RDDQS_DQ7_RISE_SLAVE_DELAY_0
    MA_OUTW(0xc3000000 + mpu_no*0x100000 + 0x41fc,reg);
    reg = (MA_INW(0xc3000000 + mpu_no*0x100000 + 0x4200)&0xfffffc00)|(0x00);//PHY_RDDQS_DQ7_FALL_SLAVE_DELAY_0
    MA_OUTW(0xc3000000 + mpu_no*0x100000 + 0x4200,reg);
    reg = (MA_INW(0xc3000000 + mpu_no*0x100000 + 0x45fc)&0x000003ff)|(0x00<<16);//PHY_RDDQS_DQ7_RISE_SLAVE_DELAY_1
    MA_OUTW(0xc3000000 + mpu_no*0x100000 + 0x45fc,reg);
    reg = (MA_INW(0xc3000000 + mpu_no*0x100000 + 0x4600)&0xfffffc00)|(0x00);//PHY_RDDQS_DQ7_FALL_SLAVE_DELAY_1
    MA_OUTW(0xc3000000 + mpu_no*0x100000 + 0x4600,reg);
    reg = (MA_INW(0xc3000000 + mpu_no*0x100000 + 0x49fc)&0x000003ff)|(0x00<<16);//PHY_RDDQS_DQ7_RISE_SLAVE_DELAY_2
    MA_OUTW(0xc3000000 + mpu_no*0x100000 + 0x49fc,reg);
    reg = (MA_INW(0xc3000000 + mpu_no*0x100000 + 0x4a00)&0xfffffc00)|(0x00);//PHY_RDDQS_DQ7_FALL_SLAVE_DELAY_2
    MA_OUTW(0xc3000000 + mpu_no*0x100000 + 0x4a00,reg);
    reg = (MA_INW(0xc3000000 + mpu_no*0x100000 + 0x4dfc)&0x000003ff)|(0x00<<16);//PHY_RDDQS_DQ7_RISE_SLAVE_DELAY_3
    MA_OUTW(0xc3000000 + mpu_no*0x100000 + 0x4dfc,reg);
    reg = (MA_INW(0xc3000000 + mpu_no*0x100000 + 0x4e00)&0xfffffc00)|(0x00);//PHY_RDDQS_DQ7_FALL_SLAVE_DELAY_3
    MA_OUTW(0xc3000000 + mpu_no*0x100000 + 0x4e00,reg);

    reg = (MA_INW(0xc3000000 + mpu_no*0x100000 + 0x4200)&0x000003ff)|(0x00<<16);//PHY_RDDQS_DM_RISE_SLAVE_DELAY_0
    MA_OUTW(0xc3000000 + mpu_no*0x100000 + 0x4200,reg);
    reg = (MA_INW(0xc3000000 + mpu_no*0x100000 + 0x4204)&0xfffffc00)|(0x00);//PHY_RDDQS_DM_FALL_SLAVE_DELAY_0
    MA_OUTW(0xc3000000 + mpu_no*0x100000 + 0x4204,reg);
    reg = (MA_INW(0xc3000000 + mpu_no*0x100000 + 0x4600)&0x000003ff)|(0x00<<16);//PHY_RDDQS_DM_RISE_SLAVE_DELAY_1
    MA_OUTW(0xc3000000 + mpu_no*0x100000 + 0x4600,reg);
    reg = (MA_INW(0xc3000000 + mpu_no*0x100000 + 0x4604)&0xfffffc00)|(0x00);//PHY_RDDQS_DM_FALL_SLAVE_DELAY_1
    MA_OUTW(0xc3000000 + mpu_no*0x100000 + 0x4604,reg);
    reg = (MA_INW(0xc3000000 + mpu_no*0x100000 + 0x4a00)&0x000003ff)|(0x00<<16);//PHY_RDDQS_DM_RISE_SLAVE_DELAY_2
    MA_OUTW(0xc3000000 + mpu_no*0x100000 + 0x4a00,reg);
    reg = (MA_INW(0xc3000000 + mpu_no*0x100000 + 0x4a04)&0xfffffc00)|(0x00);//PHY_RDDQS_DM_FALL_SLAVE_DELAY_2
    MA_OUTW(0xc3000000 + mpu_no*0x100000 + 0x4a04,reg);
    reg = (MA_INW(0xc3000000 + mpu_no*0x100000 + 0x4e00)&0x000003ff)|(0x00<<16);//PHY_RDDQS_DM_RISE_SLAVE_DELAY_3
    MA_OUTW(0xc3000000 + mpu_no*0x100000 + 0x4e00,reg);
    reg = (MA_INW(0xc3000000 + mpu_no*0x100000 + 0x4e04)&0xfffffc00)|(0x00);//PHY_RDDQS_DM_FALL_SLAVE_DELAY_3
    MA_OUTW(0xc3000000 + mpu_no*0x100000 + 0x4e04,reg);
}

void loopback_phy_adrctl_manual_update(int mpu_no){
    uint32_t reg;

    reg = (MA_INW(0xc3000000 + mpu_no*0x100000 + 0x554c)&0xfffeffff)|(0<<16);//PHY_ADRCTL_MANUAL_UPDATE
    MA_OUTW(0xc3000000 + mpu_no*0x100000 + 0x554c,reg);

    reg = (MA_INW(0xc3000000 + mpu_no*0x100000 + 0x554c)&0xfffeffff)|(1<<16);//PHY_ADRCTL_MANUAL_UPDATE
    MA_OUTW(0xc3000000 + mpu_no*0x100000 + 0x554c,reg);//trigger
}

void loopback_sc_phy_manual_update(int mpu_no){
    uint32_t reg;

    reg = (MA_INW(0xc3000000 + mpu_no*0x100000 + 0x541c)&0x0000ffff)|(0x400<<16);//PHY_CSLVL_START
    MA_OUTW(0xc3000000 + mpu_no*0x100000 + 0x541c,reg);

    reg = (MA_INW(0xc3000000 + mpu_no*0x100000 + 0x541c)&0xfffffffe)|(0);//SC_PHY_MANUAL_UPDATE
    MA_OUTW(0xc3000000 + mpu_no*0x100000 + 0x541c,reg);

    reg = (MA_INW(0xc3000000 + mpu_no*0x100000 + 0x541c)&0xfffffffe)|(1);//SC_PHY_MANUAL_UPDATE
    MA_OUTW(0xc3000000 + mpu_no*0x100000 + 0x541c,reg);//trigger
}

void loopback_phy_manual_training(uint32_t loopback_mode){
    loopback_phy_cs_training_disable(0);
    loopback_phy_ca_slave_dly(0,loopback_mode);
    loopback_phy_adr_slave_dly(0);
    loopback_phy_dqs_gate_slave_dly(0);
    loopback_phy_wrdqs_slave_dly(0);
    loopback_phy_rddqs_slave_dly(0);
    loopback_phy_adrctl_manual_update(0);
    loopback_sc_phy_manual_update(0);
}
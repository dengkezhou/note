#include "../lpddr4_common.h"

void lpddr4_bus_test(void){
    uint32_t i,j;
    printf("BUS Test!\n"); 
    for(i=0; i<1; i=i+1){   // sap 
        MA_OUTW((0xD0000020+i*0x100000),(0x3));       //  random lower address setting
        MA_OUTW((0xD000001c+i*0x100000),(0x7));       //  transfer len, *16, max 0x800
        MA_OUTW((0xD0000018+i*0x100000),(0x42000000+i*0x100000));   // address 
        MA_OUTW((0xD0000014+i*0x100000),(0x100));     // bus cnt 
    
        MA_OUTW((0xD0000010+i*0x100000),(0x0));       // bus stop = 1 
        MA_OUTW((0xD000000c+i*0x100000),(0x0));        // int enable
        MA_OUTW((0xD0000008+i*0x100000),(0x0));        // error write clear
        MA_OUTW((0xD0000004+i*0x100000),(0x0));        // real bus load, read only
        MA_OUTW((0xD0000000+i*0x100000),(0x40));        // bus load set, 0=stop, 128=100
    }
    for(i=0; i<6; i=i+1){//B1M0~B1M5
        MA_OUTW((0xC4000020+i*0x100000),(0x3));       //  random lower address setting
        MA_OUTW((0xC400001c+i*0x100000),(0x7));       //  transfer len, *16, max 0x800
        MA_OUTW((0xC4000018+i*0x100000),(0x10000000+i*0x100000));   // address 
        MA_OUTW((0xC4000014+i*0x100000),(0x100));     // bus cnt 
    
        MA_OUTW((0xC4000010+i*0x100000),(0x0));       // bus stop = 1 
        MA_OUTW((0xC400000c+i*0x100000),(0x0));        // int enable
        MA_OUTW((0xC4000008+i*0x100000),(0x0));        // error write clear
        MA_OUTW((0xC4000004+i*0x100000),(0x0));        // real bus load, read only
        MA_OUTW((0xC4000000+i*0x100000),(0x40));        // bus load set, 0=stop, 128=100
    }
    for(i=0; i<5; i=i+1){//B2M0~B2M4  
        MA_OUTW((0xC5000020+i*0x100000),(0x3));       //  random lower address setting
        MA_OUTW((0xC500001c+i*0x100000),(0x7));       //  transfer len, *16, max 0x800
        MA_OUTW((0xC5000018+i*0x100000),(0x20000000+i*0x100000));   // address 
        MA_OUTW((0xC5000014+i*0x100000),(0x100));     // bus cnt 
    
        MA_OUTW((0xC5000010+i*0x100000),(0x0));       // bus stop = 1 
        MA_OUTW((0xC500000c+i*0x100000),(0x0));        // int enable
        MA_OUTW((0xC5000008+i*0x100000),(0x0));        // error write clear
        MA_OUTW((0xC5000004+i*0x100000),(0x0));        // real bus load, read only
        MA_OUTW((0xC5000000+i*0x100000),(0x40));        // bus load set, 0=stop, 128=100
    }
    for(j=0; j<4; j=j+1){//B3M0~B3M5  
        for(i=0; i<1; i=i+1){  
            MA_OUTW((0xC6000020+j*0x1000000+i*0x100000),(0x3));       //  random lower address setting
            MA_OUTW((0xC600001c+j*0x1000000+i*0x100000),(0x7));       //  transfer len, *16, max 0x800
            MA_OUTW((0xC6000018+j*0x1000000+i*0x100000),(0x30000000+j*0x10000000+i*0x100000));   // address 
            MA_OUTW((0xC6000014+j*0x1000000+i*0x100000),(0x100));     // bus cnt 
        
            MA_OUTW((0xC6000010+j*0x1000000+i*0x100000),(0x0));       // bus stop = 1 
            MA_OUTW((0xC600000c+j*0x1000000+i*0x100000),(0x0));        // int enable
            MA_OUTW((0xC6000008+j*0x1000000+i*0x100000),(0x0));        // error write clear
            MA_OUTW((0xC6000004+j*0x1000000+i*0x100000),(0x0));        // real bus load, read only
            MA_OUTW((0xC6000000+j*0x1000000+i*0x100000),(0x40));        // bus load set, 0=stop, 128=100
        }
    }

    for(j=0; j<4; j=j+1){//B4M0~B4M5  
        for(i=0; i<1; i=i+1){  
            MA_OUTW((0xC7000020+j*0x1000000+i*0x100000),(0x3));       //  random lower address setting
            MA_OUTW((0xC700001c+j*0x1000000+i*0x100000),(0x7));       //  transfer len, *16, max 0x800
            MA_OUTW((0xC7000018+j*0x1000000+i*0x100000),(0x30000000+j*0x10000000+i*0x100000));   // address 
            MA_OUTW((0xC7000014+j*0x1000000+i*0x100000),(0x100));     // bus cnt 
        
            MA_OUTW((0xC7000010+j*0x1000000+i*0x100000),(0x0));       // bus stop = 1 
            MA_OUTW((0xC700000c+j*0x1000000+i*0x100000),(0x0));        // int enable
            MA_OUTW((0xC7000008+j*0x1000000+i*0x100000),(0x0));        // error write clear
            MA_OUTW((0xC7000004+j*0x1000000+i*0x100000),(0x0));        // real bus load, read only
            MA_OUTW((0xC7000000+j*0x1000000+i*0x100000),(0x40));        // bus load set, 0=stop, 128=100
        }
    }

    for(j=0; j<4; j=j+1){//B5M0~B5M5  
        for(i=0; i<1; i=i+1){  
            MA_OUTW((0xC8000020+j*0x1000000+i*0x100000),(0x3));       //  random lower address setting
            MA_OUTW((0xC800001c+j*0x1000000+i*0x100000),(0x7));       //  transfer len, *16, max 0x800
            MA_OUTW((0xC8000018+j*0x1000000+i*0x100000),(0x30000000+j*0x10000000+i*0x100000));   // address 
            MA_OUTW((0xC8000014+j*0x1000000+i*0x100000),(0x100));     // bus cnt 
        
            MA_OUTW((0xC8000010+j*0x1000000+i*0x100000),(0x0));       // bus stop = 1 
            MA_OUTW((0xC800000c+j*0x1000000+i*0x100000),(0x0));        // int enable
            MA_OUTW((0xC8000008+j*0x1000000+i*0x100000),(0x0));        // error write clear
            MA_OUTW((0xC8000004+j*0x1000000+i*0x100000),(0x0));        // real bus load, read only
            MA_OUTW((0xC8000000+j*0x1000000+i*0x100000),(0x40));        // bus load set, 0=stop, 128=100
        }
    }

    for(j=0; j<4; j=j+1){//B5M0~B5M5  
        for(i=0; i<1; i=i+1){  
            MA_OUTW((0xC9000020+j*0x1000000+i*0x100000),(0x3));       //  random lower address setting
            MA_OUTW((0xC900001c+j*0x1000000+i*0x100000),(0x7));       //  transfer len, *16, max 0x800
            MA_OUTW((0xC9000018+j*0x1000000+i*0x100000),(0x30000000+j*0x10000000+i*0x100000));   // address 
            MA_OUTW((0xC9000014+j*0x1000000+i*0x100000),(0x100));     // bus cnt 
        
            MA_OUTW((0xC9000010+j*0x1000000+i*0x100000),(0x0));       // bus stop = 1 
            MA_OUTW((0xC900000c+j*0x1000000+i*0x100000),(0x0));        // int enable
            MA_OUTW((0xC9000008+j*0x1000000+i*0x100000),(0x0));        // error write clear
            MA_OUTW((0xC9000004+j*0x1000000+i*0x100000),(0x0));        // real bus load, read only
            MA_OUTW((0xC9000000+j*0x1000000+i*0x100000),(0x40));        // bus load set, 0=stop, 128=100
        }
    }

    // for(i=5; i<7; i=i+1) {       // index of bus2 module system 
    //         MA_OUTW((0xC5f00000+i*0x400+0x8 ),(0x1));   // power up
    //         rd_val = 0;
    //         while(!rd_val) {
    //             rd_val = MA_INW(0xC5f00000+i*0x400+0x8) & 0x10; // polling power-ack 
    //         }
    //         MA_OUTW((0xC5f00000+i*0x400+0x8 ),(0x1));   // power up & iso disable
       
    //         //MA_OUTW((0xC5f00000+i*0x400+0x1c),(0x1));  // reset clock enable 

    //         MA_OUTW((0xC5f00000+i*0x400+0x4 ),(0xffff)); // clkgate en
    //         MA_OUTW((0xC5f00000+i*0x400+0xc ),(0x3));    // bus en
    //         MA_OUTW((0xC5f00000+i*0x400+0x18),(0x1));    // io in en

    //         rd_val = MA_INW((0xC5f00000+i*0x400+0xc));   // check bus enable register
    //         if(rd_val != 0x3) {
    //              printf("bus2 sysm read/write error\n");
    //         }

    //         MA_OUTW((0xC5f00000+i*0x400+0x0 ),(0x0));   // reset release 
    // }

    //dma_write_data(0x110000000, 0x125100000, 0x400);

    printf("BUS Testing!\n"); 
    // while(1) {
    //     for(i=0; i<1; i=i+1){  
    //         rd_val = MA_INW((0xD0000008+i*0x100000)); 
    //         if(rd_val) {
    //             printf("sap bus1 m%1d error!\n", i);
    //             soc_cmd(0xaa55);
    //         }
    //     }
    //     for(i=0; i<6; i=i+1){  
    //         rd_val = MA_INW((0xC4000008+i*0x100000)); 
    //         if(rd_val) {
    //             printf("bus1 m%1d error!\n", i);
    //             soc_cmd(0xaa55);
    //         }
    //     }
    //     for(i=0; i<5; i=i+1){  
    //         rd_val = MA_INW((0xC5000008+i*0x100000)); 
    //         if(rd_val) {
    //             printf("bus2 m%1d error!\n", i);
    //             soc_cmd(0xaa55);
    //         }
    //     }
    //     // for(i=0; i<4; i=i+1){  
    //     //     rd_val = MA_INW((0xC6000008+i*0x1000000)); 
    //     //     if(rd_val) {
    //     //         printf("bus%1d error!\n", i+3);
    //     //         soc_cmd(0xaa55);
    //     //     }
    //     // }
    // }
}

void bandwidth_monitor(void){
    uint32_t reg_val;
    reg_val = (read_register(0x00000e1c)>>24)&(0x7f);
    printf("axi0 bdw %d\n",reg_val);
    reg_val = (read_register(0x00000e20)>>16)&(0x7f);
    printf("axi1 bdw %d\n",reg_val);
    reg_val = (read_register(0x00000e24)>>8)&(0x7f);
    printf("axi2 bdw %d\n",reg_val);
    reg_val = (read_register(0x00000e28)>>0)&(0x7f);
    printf("axi3 bdw %d\n",reg_val);
    reg_val = (read_register(0x00000e28)>>24)&(0x7f);
    printf("axi4 bdw %d\n",reg_val);
    reg_val = (read_register(0x00000e2c)>>16)&(0x7f);
    printf("axi5 bdw %d\n",reg_val);
    reg_val = (read_register(0x00000e30)>>8)&(0x7f);
    printf("axi6 bdw %d\n",reg_val);
    reg_val = (read_register(0x00000e34)>>0)&(0x7f);
    printf("axi7 bdw %d\n",reg_val);
}

void bandwidth_allocation(
    uint32_t axi0_limit,uint32_t axi1_limit,uint32_t axi2_limit,
    uint32_t axi3_limit,uint32_t axi4_limit,uint32_t axi5_limit,
    uint32_t axi6_limit,uint32_t axi7_limit){
    uint32_t reg_val;
    reg_val = (read_register(0x00000e1c)&(~(0x7f<<8)))|(axi0_limit<<8);//axi0_bdw
    write_register(0x00000e1c,reg_val);
    printf("axi0 limit %d\n",axi0_limit);

    reg_val = (read_register(0x00000e20)&(~(0x7f)))|(axi1_limit);//axi1_bdw
    write_register(0x00000e20,reg_val);
    printf("axi1 limit %d\n",axi1_limit);

    reg_val = (read_register(0x00000e20)&(~(0x7f<<24)))|(axi2_limit<<24);//axi2_bdw
    write_register(0x00000e20,reg_val);
    printf("axi2 limit %d\n",axi2_limit);

    reg_val = (read_register(0x00000e24)&(~(0x7f<<16)))|(axi3_limit<<16);//axi3_bdw
    write_register(0x00000e24,reg_val);
    printf("axi3 limit %d\n",axi3_limit);

    reg_val = (read_register(0x00000e28)&(~(0x7f<<8)))|(axi4_limit<<8);//axi4_bdw
    write_register(0x00000e28,reg_val);
    printf("axi4 limit %d\n",axi4_limit);

    reg_val = (read_register(0x00000e2c)&(~(0x7f)))|(axi5_limit);//axi5_bdw
    write_register(0x00000e2c,reg_val);
    printf("axi5 limit %d\n",axi5_limit);

    reg_val = (read_register(0x00000e2c)&(~(0x7f<<24)))|(axi6_limit<<24);//axi6_bdw
    write_register(0x00000e2c,reg_val);
    printf("axi6 limit %d\n",axi6_limit);

    reg_val = (read_register(0x00000e30)&(~(0x7f<<16)))|(axi7_limit<<16);//axi7_bdw
    write_register(0x00000e30,reg_val);
    printf("axi7 limit %d\n",axi7_limit);
}

void axi_priority_enable(uint32_t enable){
    uint32_t reg_val,i;
    for(i=0;i<8;i++){
        reg_val = (read_register(0x000005d8 + i*0x4)&(~(1<<24)))|(enable<<24);//axi0_r_priority
        write_register(0x000005d8 + i*0x4,reg_val);
    }   
}

void axi_r_priority(
    uint32_t axi0_r_priority,uint32_t axi1_r_priority,uint32_t axi2_r_priority,
    uint32_t axi3_r_priority,uint32_t axi4_r_priority,uint32_t axi5_r_priority,
    uint32_t axi6_r_priority,uint32_t axi7_r_priority){
    uint32_t reg_val;
    reg_val = (read_register(0x000005dc)&(~(0x7)))|(axi0_r_priority);//axi0_r_priority
    write_register(0x000005dc,reg_val);
    reg_val = (read_register(0x000005e0)&(~(0x7)))|(axi1_r_priority);//axi1_r_priority
    write_register(0x000005e0,reg_val);
    reg_val = (read_register(0x000005e4)&(~(0x7)))|(axi2_r_priority);//axi2_r_priority
    write_register(0x000005e4,reg_val);
    reg_val = (read_register(0x000005e8)&(~(0x7)))|(axi3_r_priority);//axi3_r_priority
    write_register(0x000005e8,reg_val);
    reg_val = (read_register(0x000005ec)&(~(0x7)))|(axi4_r_priority);//axi4_r_priority
    write_register(0x000005ec,reg_val);
    reg_val = (read_register(0x000005f0)&(~(0x7)))|(axi5_r_priority);//axi5_r_priority
    write_register(0x000005f0,reg_val);
    reg_val = (read_register(0x000005f4)&(~(0x7)))|(axi6_r_priority);//axi6_r_priority
    write_register(0x000005f4,reg_val);
    reg_val = (read_register(0x000005f8)&(~(0x7)))|(axi7_r_priority);//axi7_r_priority
    write_register(0x000005f8,reg_val);
    printf("r_priority %d,%d,%d,%d,%d,%d,%d,%d\n",
        axi0_r_priority,axi1_r_priority,axi2_r_priority,
        axi3_r_priority,axi4_r_priority,axi5_r_priority,
        axi6_r_priority,axi7_r_priority);
}

void axi_w_priority(
    uint32_t axi0_w_priority,uint32_t axi1_w_priority,uint32_t axi2_w_priority,
    uint32_t axi3_w_priority,uint32_t axi4_w_priority,uint32_t axi5_w_priority,
    uint32_t axi6_w_priority,uint32_t axi7_w_priority){
    uint32_t reg_val;
    reg_val = (read_register(0x000005dc)&(~(0x7<<8)))|(axi0_w_priority<<8);//axi0_w_priority
    write_register(0x000005dc,reg_val);
    reg_val = (read_register(0x000005e0)&(~(0x7<<8)))|(axi1_w_priority<<8);//axi1_w_priority
    write_register(0x000005e0,reg_val);
    reg_val = (read_register(0x000005e4)&(~(0x7<<8)))|(axi2_w_priority<<8);//axi2_w_priority
    write_register(0x000005e4,reg_val);
    reg_val = (read_register(0x000005e8)&(~(0x7<<8)))|(axi3_w_priority<<8);//axi3_w_priority
    write_register(0x000005e8,reg_val);
    reg_val = (read_register(0x000005ec)&(~(0x7<<8)))|(axi4_w_priority<<8);//axi4_w_priority
    write_register(0x000005ec,reg_val);
    reg_val = (read_register(0x000005f0)&(~(0x7<<8)))|(axi5_w_priority<<8);//axi5_w_priority
    write_register(0x000005f0,reg_val);
    reg_val = (read_register(0x000005f4)&(~(0x7<<8)))|(axi6_w_priority<<8);//axi6_w_priority
    write_register(0x000005f4,reg_val);
    reg_val = (read_register(0x000005f8)&(~(0x7<<8)))|(axi7_w_priority<<8);//axi7_w_priority
    write_register(0x000005f8,reg_val);
    printf("w_priority %d,%d,%d,%d,%d,%d,%d,%d\n",
        axi0_w_priority,axi1_w_priority,axi2_w_priority,
        axi3_w_priority,axi4_w_priority,axi5_w_priority,
        axi6_w_priority,axi7_w_priority);
}

void axi_bdw_ovflow_enable(
    uint32_t axi0_ov_enable,uint32_t axi1_ov_enable,uint32_t axi2_ov_enable,
    uint32_t axi3_ov_enable,uint32_t axi4_ov_enable,uint32_t axi5_ov_enable,
    uint32_t axi6_ov_enable,uint32_t axi7_ov_enable){
    uint32_t reg_val;
    reg_val = (read_register(0x00000e1c)&(~(0x1<<16)))|(axi0_ov_enable<<16);//axi0_w_priority
    write_register(0x00000e1c,reg_val);
    reg_val = (read_register(0x00000e20)&(~(0x1<<8)))|(axi1_ov_enable<<8);//axi1_w_priority
    write_register(0x00000e20,reg_val);
    reg_val = (read_register(0x00000e24)&(~(0x1)))|(axi2_ov_enable);//axi2_w_priority
    write_register(0x00000e24,reg_val);
    reg_val = (read_register(0x00000e24)&(~(0x1<<24)))|(axi3_ov_enable<<24);//axi2_w_priority
    write_register(0x00000e24,reg_val);
    reg_val = (read_register(0x00000e28)&(~(0x1<<16)))|(axi4_ov_enable<<16);//axi3_w_priority
    write_register(0x00000e28,reg_val);
    reg_val = (read_register(0x00000e2c)&(~(0x1<<8)))|(axi5_ov_enable<<8);//axi4_w_priority
    write_register(0x00000e2c,reg_val);
    reg_val = (read_register(0x00000e30)&(~(0x1)))|(axi6_ov_enable);//axi5_w_priority
    write_register(0x00000e30,reg_val);
    reg_val = (read_register(0x00000e30)&(~(0x1<<24)))|(axi7_ov_enable<<24);//axi5_w_priority
    write_register(0x00000e30,reg_val);
    printf("ov_enable %d,%d,%d,%d,%d,%d,%d,%d\n",
        axi0_ov_enable,axi1_ov_enable,axi2_ov_enable,
        axi3_ov_enable,axi4_ov_enable,axi5_ov_enable,
        axi6_ov_enable,axi7_ov_enable);
}

void arb_cmd_q_threshold(uint32_t threshold){
    uint32_t reg_val;
    reg_val = (read_register(0x00000e1c)&(~(0x1f)))|(threshold);//axi5_w_priority
    write_register(0x00000e1c,reg_val);
}

void lpddr4_axi_priority_test(void){
    uint32_t i;
    axi_init();
#ifndef CONFIG_COMPILE_ASIC
    sys_lpddr4_start();
#endif
    lpddr4_bus_test();
    for(i=0;i<20;i++){
        bandwidth_monitor();
        printf("\n");
    }
    /*bdw_allocation*/
    bandwidth_allocation(5,5,100,5,5,5,5,5);
    udelay(10);
    for(i=0;i<20;i++){
        bandwidth_monitor();
        printf("\n");
    }
    /*end*/
    /*bdw_priority*/
    axi_priority_enable(0);
    axi_r_priority(7,0,7,7,7,7,7,7);
    axi_w_priority(7,0,7,7,7,7,7,7);
    axi_priority_enable(1);
    udelay(10);
    for(i=0;i<20;i++){
        bandwidth_monitor();
        printf("\n");
    }
    /*end*/
    /*bdw_ovflow test*/
    bandwidth_allocation(5,5,100,5,5,5,5,5);
    axi_bdw_ovflow_enable(0,1,0,0,0,0,0,0);
    axi_r_priority(7,0,7,7,7,7,7,7);
    axi_w_priority(7,0,7,7,7,7,7,7);
    udelay(10);
    for(i=0;i<20;i++){
        bandwidth_monitor();
        printf("\n");
    }
    /*end*/
}
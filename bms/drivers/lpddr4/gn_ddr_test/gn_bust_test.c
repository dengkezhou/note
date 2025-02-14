
#include "../lpddr4_common.h"
#include "dma_ctrl.h"

#ifndef BUS_TEST
#define BUS_TEST 1
#endif
#ifndef MPU_NUM
#define MPU_NUM 0
#endif
#ifndef DMA_TEST
#define DMA_TEST 0
#endif
#ifndef EXTD_MODE
#define EXTD_MODE 0
#endif
#ifndef EXTD_BYPASS
#define EXTD_BYPASS 0
#endif

int parallel_conflict_test(void)
{
	uint32_t mi, mj;
	uint32_t i, j, rd_val, halt_cnt;
	//uint32_t k, sap_base, ref_val;
	volatile unsigned int *addr64_ptr;
	volatile unsigned int *addr_ptr;
	uint64_t src_addr;
	//uint64_t dst_addr, set_value, long_sap_base;
	//uint32_t byte_len, cmd_type;
	//int set_param[2];
	uint32_t LPDDR4;

	MA_OUTW(0xc2f08c2c, 0x10001); // enable pc & sysmap SET

	rd_val = MA_INW(0xc2f08cb4);
	if ((rd_val & 0xf000000) == 0x1000000) { // c920 dram cacheable
		MA_OUTW(0xc2f08cb4,
			rd_val & 0xffffff); // set dram to uncacheable
	}

	//PLLOUT = REF / DIVR_VAL * 4 * DIVF_VAL / DIVQ_VAL
	//VCO    = REF / DIVR_VAL * 4 * DIVF_VAL (1200 ~ 6000 MHz)
	printf("CPU PLL Test!\n");
	// APLL
	MA_OUTW(CLKGEN_ALDCFG,
		3); // load parameter, newdiv[2], load[1], oute[0]
	MA_OUTW(CLKGEN_AEN, 1); // pll enable
	rd_val = 0;
	while (rd_val != 0x1) {
		rd_val = MA_INW(CLKGEN_ALOCK) & 0x1; //check apll lock
	}
	MA_OUTW(CLKGEN_ASEL, 2); // pll source sel and output sel
	////////////////////////////////////////

	// BPLL
	MA_OUTW(CLKGEN_BLDCFG,
		3); // load parameter, newdiv[2], load[1], oute[0]
	MA_OUTW(CLKGEN_BEN, 1); // pll enable
	// DPLL
	MA_OUTW(CLKGEN_DLDCFG,
		3); // load parameter, newdiv[2], load[1], oute[0]
	MA_OUTW(CLKGEN_DEN, 1); // pll enable
	// EPLL
	MA_OUTW(CLKGEN_ELDCFG,
		3); // load parameter, newdiv[2], load[1], oute[0]
	MA_OUTW(CLKGEN_EEN, 1); // pll enable
	//PLLOUT = REF / DIVR_VAL * 4 * DIVF_VAL / DIVQ_VAL
	//VCO    = REF / DIVR_VAL * 4 * DIVF_VAL (1200 ~ 6000 MHz)
	//mpu_clk_2x=VPLL=2133MHz (VCO=4266, 4266/24=177)
	MA_OUTW(CLKGEN_VLDCFG,
		3); // load parameter, newdiv[2], load[1], oute[0]
	MA_OUTW(CLKGEN_VEN, 1); // pll enable
	MA_OUTW(CLKGEN_VDIVQ, 0); // vpll divq

	// SPLL
	MA_OUTW(SCLKGEN_ALDCFG,
		3); // load parameter, newdiv[2], load[1], oute[0]
	MA_OUTW(SCLKGEN_AEN, 1); // pll enable

	rd_val = 0;
	while (rd_val != 0x1) {
		rd_val = MA_INW(CLKGEN_BLOCK) & 0x1; //check bpll lock
	}
	rd_val = 0;
	while (rd_val != 0x1) {
		rd_val = MA_INW(CLKGEN_DLOCK) & 0x1; //check dpll lock
	}
	rd_val = 0;
	while (rd_val != 0x1) {
		rd_val = MA_INW(CLKGEN_ELOCK) & 0x1; //check epll lock
	}
	rd_val = 0;
	while (rd_val != 0x1) {
		rd_val = MA_INW(CLKGEN_VLOCK) & 0x1; //check vpll lock
	}

	rd_val = 0;
	while (rd_val != 0x1) {
		rd_val = MA_INW(SCLKGEN_ALOCK) & 0x1; //check sapll lock
	}
	MA_OUTW(SCLKGEN_ASEL, 2); // pll source sel and output sel

	MA_OUTW(CLKGEN_BSEL, 2); // pll source sel and output sel
	MA_OUTW(CLKGEN_DSEL, 2); // pll source sel and output sel
	MA_OUTW(CLKGEN_ESEL, 2); // pll source sel and output sel
	MA_OUTW(CLKGEN_VSEL, 2); // pll source sel and output sel
	//////////////////////////////////////////
	rd_val = MA_INW(SAPM_BASE + 0x8); //check boot mode
	if (rd_val == 0xf) {
		LPDDR4 = 1;
		printf("LPDDR4 Init!\n");
	} else {
		LPDDR4 = 0;
		printf("MSRAM Init!\n");
	}
	/////////////////////////////
	printf("MPU Test!\n");

	if (MPU_NUM == 0) {
		mi = 0;
		mj = 1;
	} else if (MPU_NUM == 1) {
		mi = 1;
		mj = 2;
	} else {
		mi = 0;
		mj = 2;
	}

	if (LPDDR4 == 0) {
		//MA_OUTW(MLCLKG_BASE+0x74, 29);    // set ratio for fpga(70MHz)

		for (i = mi; i < mj + 1; i = i + 1) { // test mpu1 dummy flag
			// mpu sysm
			MA_OUTW(0xc30f0000 + i * 0x100000 + 0x4,
				0xffff); // set clk enable
			MA_OUTW(0xc30f0000 + i * 0x100000 + 0x0,
				0); // reset release

			rd_val = 0;
			while (rd_val != 0x1) {
				rd_val = MA_INW(0xc30f0000 + i * 0x100000 +
						0x20) &
					 0x1; //check init calib lock
			}

			MA_OUTW(0xc30f0000 + i * 0x100000 + 0x28,
				0); // enable e906/c920 access dram
			printf("MPU%1d init calib done!\n", i);

			//MA_OUTW(0xc30f0000+i*0x100000+0x0, 0x0);       // reset release
#if defined(CONFIG_E906)
			udelay(1);
#else
			asm("sync.is");
#endif
		}

		//while (1);
	} else {
		//2133Mbps
		//MA_OUTW(MLCLKG_BASE+0x74, 1);    // set ratio, mpu_clk=mpu_clk_x2/2
		//4266Mbps
		MA_OUTW(MLCLKG_BASE + 0x74,
			0); // set ratio, mpu_clk=mpu_clk_x2/2

		for (i = mi; i < mj; i = i + 1) {
			// mpu sysm
			MA_OUTW(0xc30f0000 + i * 0x100000 + 0x4,
				0xffff); // set clk enable
			MA_OUTW(0xc30f0000 + i * 0x100000 + 0x0,
				0xfffc); // apb/ctl/phy reset release
		}

		/* pi training. */
		sys_lpddr4_init_row_16();
		lpddr4_pi_init_and_training();
		printf("MPU%1d write done!\n", i - 1);

		for (i = mi; i < mj; i = i + 1) {
			rd_val = 0;
			while (rd_val != 0x1) {
				rd_val = MA_INW(0xc3008000 + i * 0x100000 +
						0x14) &
					 0x1; //check  controller_init_done
			}

			MA_OUTW(0xc30f0000 + i * 0x100000 + 0x28,
				0); // enable e906/c920 access dram

			MA_OUTW(0xc3010000 + i * 0x100000 + 0x0,
				0x1); // pmu sample enable

			MA_OUTW(0xc30f0000 + i * 0x100000 + 0x0,
				0x0); // port reset release
		}
#if defined(CONFIG_E906)
		udelay(1);
#else
		asm("sync.is");
#endif
	}
	printf("cpu test start!\n");

	for (i = 0; i < 160; i = i + 1) {
		addr_ptr = (volatile unsigned int *)((unsigned long)(0xc000000 + i * 4));
		*(addr_ptr) = 0xc0002340 + i;
	}
#if defined(CONFIG_E906)
	udelay(1);
#else
	asm("sync.is");
#endif
	for (i = 0; i < 160; i = i + 1) {
		addr_ptr = (volatile unsigned int *)((unsigned long)(0xc000000 + i * 4));
		rd_val = *(addr_ptr);
		if (rd_val != (0xc0002340 + i))
			printf("sram read error!\n");
	}

#if 0
    for(i=0; i<4; i=i+1){
        addr64_ptr=0x100000000+i*4;
        rd_val = *(addr64_ptr) ;
        printf("addr=%lx, dat=%x\n",addr64_ptr, rd_val); 
    }
    for(i=0; i<16; i=i+1){
        addr64_ptr=0x17fffffe0+i*4;
        rd_val = *(addr64_ptr) ;
        printf("addr=%lx, dat=%x\n",addr64_ptr, rd_val); 
    }

    for(i=0; i<4; i=i+1){
        addr64_ptr=0x1c8b552c0+i*4;
        rd_val = *(addr64_ptr) ;
        printf("addr=%lx, dat=%x\n",addr64_ptr, rd_val); 
    }

    soc_cmd(0xaa55);
#endif

#if 0
    // test afe module
    MA_OUTW(0xc3200030, 0x21);    //sap afe base id
    MA_OUTW(0xc3300030, 0x32);    //c920 afe base id
    MA_OUTW(0xc330002c, (EXTD_BYPASS<<6 | 1<<1));    //pass through[6], axi user pass through[2:1]

for(i=0; i<6; i=i+1){
    MA_OUTW(0xc4e0002c+i*0x1000000, (EXTD_BYPASS<<6 | 1<<1));      // pass through[6], axi user pass through[2:1] 
    MA_OUTW(0xc4e00030+i*0x1000000, 0x10+i);    // base id
}
for(i=0; i<6; i=i+1){
    rd_val=MA_INW(0xc4e00030+i*0x1000000); 
    if(rd_val != 0x10+i) printf("bus%d afe id read error\n",i+1); 
    MA_OUTW(0xc4e00030+i*0x1000000, 0);    // base id
}
    rd_val=MA_INW(0xc3200030); 
    if(rd_val != 0x21) printf("sap afe id read error\n"); 
    rd_val=MA_INW(0xc3300030); 
    if(rd_val != 0x32) printf("c920 afe id read error\n"); 

    MA_OUTW(0xc3200030, 0x0);    
    MA_OUTW(0xc3300030, 0x0);
#endif

#if 0
if(EXTD_MODE != 0 ) {
    printf("dram interleave mode %d\n", EXTD_MODE); 
    rd_val=MA_INW(0xc2f087f4); 
    MA_OUTW(0xc2f087f4, rd_val | EXTD_MODE); 

    for(i=0; i<0x40; i=i+1){
        addr64_ptr=0x100000fe0+i*4;
        *(addr64_ptr) = 0x10002340+i;
    }
    asm("sync.is");
    for(i=0; i<0x40; i=i+1){
        addr64_ptr=0x100000fe0+i*4;
        rd_val = *(addr64_ptr) ;
        if(rd_val != (0x10002340+i))
            printf("interleave read error!\n"); 
    }
    
}
else {
    if(MPU_NUM == 0 || MPU_NUM == 2) {
        for(i=0; i<160; i=i+1){
            addr64_ptr=0x100000000+i*4;
            *(addr64_ptr) = 0x10002340+i;
        }
    
        asm("sync.is");
    
        for(i=0; i<160; i=i+1){
            addr64_ptr=0x180000010+i*4;
            *(addr64_ptr) = 0x18002340+i;
        }
        asm("sync.is");
    
        for(i=0; i<160; i=i+1){
            addr64_ptr=0x100000000+i*4;
            rd_val = *(addr64_ptr) ;
            if(rd_val != (0x10002340+i))
                printf("0x10000_ read error!\n"); 
        }
        for(i=0; i<160; i=i+1){
            addr64_ptr=0x180000010+i*4;
            rd_val = *(addr64_ptr) ;
            if(rd_val != (0x18002340+i))
                printf("0x18000_ read error!\n"); 
        }
        if(LPDDR4 == 0) {   // LPDDR4 controller will cause illegal address access
            // 4GB for phony sram
            for(i=0; i<8; i=i+1){
                addr64_ptr=0x200000000+i*4;
                rd_val = *(addr64_ptr) ;
                if(rd_val != (0x10002340+i))
                    printf("0x20000_ read error!\n"); 
            }
            for(i=0; i<8; i=i+1){
                addr64_ptr=0x280000010+i*4;
                rd_val = *(addr64_ptr) ;
                if(rd_val != (0x18002340+i))
                    printf("0x28000_ read error!\n"); 
            }
            for(i=0; i<8; i=i+1){
                addr64_ptr=0x380000010+i*4;
                rd_val = *(addr64_ptr) ;
                if(rd_val != (0x18002340+i))
                    printf("0x38000_ read error!\n"); 
            }
            for(i=0; i<8; i=i+1){
                addr64_ptr=0x480000010+i*4;
                rd_val = *(addr64_ptr) ;
                if(rd_val != (0x18002340+i))
                    printf("0x48000_ read error!\n"); 
            }
        }
    }
    
    if(MPU_NUM == 1 || MPU_NUM == 2) {
        for(i=0; i<8; i=i+1){
            addr64_ptr=0x500000000+i*4;
            *(addr64_ptr) = 0x50002340+i;
        }
    
        asm("sync.is");
    
        for(i=0; i<8; i=i+1){
            addr64_ptr=0x580000010+i*4;
            *(addr64_ptr) = 0x58002340+i;
        }
        asm("sync.is");
    
        for(i=0; i<8; i=i+1){
            addr64_ptr=0x500000000+i*4;
            rd_val = *(addr64_ptr) ;
            if(rd_val != (0x50002340+i))
                printf("0x50000_ read error!\n"); 
        }
        for(i=0; i<8; i=i+1){
            addr64_ptr=0x580000010+i*4;
            rd_val = *(addr64_ptr) ;
            if(rd_val != (0x58002340+i))
                printf("0x58000_ read error!\n"); 
        }
        if(LPDDR4 == 0) {   // LPDDR4 controller will cause illegal address access
            for(i=0; i<8; i=i+1){
                addr64_ptr=0x600000000+i*4;
                rd_val = *(addr64_ptr) ;
                if(rd_val != (0x50002340+i))
                    printf("0x60000_ read error!\n"); 
            }
            for(i=0; i<8; i=i+1){
                addr64_ptr=0x680000010+i*4;
                rd_val = *(addr64_ptr) ;
                if(rd_val != (0x58002340+i))
                    printf("0x68000_ read error!\n"); 
            }
            for(i=0; i<8; i=i+1){
                addr64_ptr=0x780000010+i*4;
                rd_val = *(addr64_ptr) ;
                if(rd_val != (0x58002340+i))
                    printf("0x78000_ read error!\n"); 
            }
            for(i=0; i<8; i=i+1){
                addr64_ptr=0x880000010+i*4;
                rd_val = *(addr64_ptr) ;
                if(rd_val != (0x58002340+i))
                    printf("0x88000_ read error!\n"); 
            }
        }
    }
    
        //0x4000_0000 test
    if(LPDDR4 == 1) {   // LPDDR4 controller will cause illegal address access
        if(MPU_NUM == 1 ) {
            mi = 4;
            mj = 5;   // only test 4GB
        } else {
            mi = 0;
            mj = 1;   // only test 4GB
        }
    } else {
        mi = 0;
        mj = 4;     // 16GB 
    }
    for(k=mi; k<mj; k=k+1) {
        for(j = 0; j<4; j=j+1) {    
            sap_base = j+k*4;
            MA_OUTW(0xc2f087f8, sap_base); // sap base set
        
            for(i=0; i<8; i=i+1){
                addr64_ptr=0x40001000+i*4;
                *(addr64_ptr) = 0x40002340+i+sap_base*0x100000;
            }
        }
            asm("sync.is");
        
        for(j = 0; j<4; j=j+1) {    
            sap_base = j+k*4;
            MA_OUTW(0xc2f087f8, sap_base); // sap base set
            asm("sync.is");
        
            for(i=0; i<8; i=i+1){
                addr64_ptr=0x40001000+i*4;
                rd_val = *(addr64_ptr) ;
                ref_val = 0x40002340+i+sap_base*0x100000;
                if(rd_val != ref_val)
                    printf("sap base read error %d, %d, %0x!\n",sap_base,i,ref_val); 
            }
        }
            
        for(j = 0; j<4; j=j+1) {    
        
            long_sap_base = j+k*4;
            MA_OUTW(0xc2f087f8, sap_base); // sap base set
            for(i=0; i<8; i=i+1){
                addr64_ptr=0x100001000+i*4+long_sap_base*0x40000000;
                rd_val = *(addr64_ptr) ;
                ref_val = 0x40002340+i+long_sap_base*0x100000;
                if(rd_val != ref_val)
                    printf("sap base read-1 error %d, %d, %0x!\n",sap_base,i,ref_val); 
            }
        }
    }
}

#endif

	if (DMA_TEST == 1) {
		MA_OUTW(CLKGEN_BASE + 0xe4, 1); // bus2_aclk DPLL/3
		printf("dma test!\n");
		for (i = 5; i < 6; i = i + 1) { // index of bus2 module system
			MA_OUTW((0xC5f00000 + i * 0x400 + 0x8),
				(0x1)); // power up
			rd_val = 0;
			while (!rd_val) {
				rd_val = MA_INW(0xC5f00000 + i * 0x400 + 0x8) &
					 0x10; // polling power-ack
			}
			MA_OUTW((0xC5f00000 + i * 0x400 + 0x8),
				(0x1)); // power up & iso disable

			//MA_OUTW((0xC5f00000+i*0x400+0x1c),(0x1));  // reset clock enable

			MA_OUTW((0xC5f00000 + i * 0x400 + 0x4),
				(0xffff)); // clkgate en
			MA_OUTW((0xC5f00000 + i * 0x400 + 0xc),
				(0x3)); // bus en
			MA_OUTW((0xC5f00000 + i * 0x400 + 0x18),
				(0x1)); // io in en
			MA_OUTW((0xC5f00000 + i * 0x400 + 0x10), (0x45)); // qos

			rd_val = MA_INW((0xC5f00000 + i * 0x400 +
					 0xc)); // check bus enable register
			if (rd_val != 0x3) {
				printf("bus2 sysm read/write error\n");
			}

			MA_OUTW((0xC5f00000 + i * 0x400 + 0x0),
				(0x0)); // reset release
		}

		if (LPDDR4 ==
		    0) { // LPDDR4 controller will cause illegal address access
			for (i = 0; i < 0x100; i = i + 1) {
				addr64_ptr = (volatile unsigned int *)((unsigned long)(0x100000c00 + i * 4));
				*(addr64_ptr) = 0x12340000 + i;
			}

			dma_write_data_chan(0x100000c00, 0x200010c00, 0x400, 0,
					    3);
			dma_wait_chan(0);
			dma_write_data_chan(0x200010c00, 0x300020de0, 0x400, 1,
					    3);
			dma_wait_chan(1);
			dma_write_data_chan(0x300020de0, 0x400030dd0, 0x400, 2,
					    3);
			dma_wait_chan(2);
			for (i = 0; i < 0x20; i = i + 1) {
				addr64_ptr = (volatile unsigned int *)((unsigned long)(0x400030dd0 + i * 4));
				rd_val = *(addr64_ptr);
				if (rd_val != 0x12340000 + i)
					printf("dma read %d error!\n", i);
			}
			dma_write_data_chan(0x400030dd0, 0x500040dc0, 0x400, 3,
					    3);
			dma_wait_chan(3);
			dma_write_data_chan(0x500040dc0, 0x600050d00, 0x400, 4,
					    3);
			dma_wait_chan(4);
			dma_write_data_chan(0x600050d00, 0x700060d00, 0x400, 5,
					    3);
			dma_wait_chan(5);
			dma_write_data_chan(0x700060d00, 0x800070d00, 0x400, 6,
					    3);
			dma_wait_chan(6);
			dma_write_data_chan(0x800070d00, 0x140200d00, 0x400, 7,
					    3);
			dma_wait_chan(7);
			for (i = 0; i < 0x8; i = i + 1) {
				addr64_ptr = (volatile unsigned int *)((unsigned long)(0x140200d00 + i * 4));
				rd_val = *(addr64_ptr);
				if (rd_val != 0x12340000 + i)
					printf("dma read 0x8000 %d error!\n",
					       i);
			}

			MA_OUTW(0xc2f087f8, 2); // sap base set
			dma_write_data_chan(0x140200d00, 0x40000000, 0x400, 0,
					    3);
			dma_wait_chan(0);
			dma_write_data_chan(0x40000000, 0x41000000, 0x400, 1,
					    3);
			dma_wait_chan(1);

			for (i = 0; i < 0x8; i = i + 1) {
				addr64_ptr = (volatile unsigned int *)((unsigned long)(0x41000000 + i * 4));
				rd_val = *(addr64_ptr);
				if (rd_val != 0x12340000 + i)
					printf("dma read 0x410 %d error!\n", i);
			}

		} else { // LPDDR4
			//if(EXTD_MODE != 0 ) {

			////} else {
			if (MPU_NUM == 1) {
				src_addr = 0x500000000;
			} else {
				src_addr = 0x100000000;
			}

			for (i = 0; i < 0x100; i = i + 1) {
				addr64_ptr = (volatile unsigned int *)((unsigned long)(src_addr + 0x0c00 + i * 4));
				*(addr64_ptr) = 0x12340000 + i;
			}

			dma_write_data_chan(src_addr + 0x00c00,
					    src_addr + 0x01c00, 0x400, 0, 3);
			dma_wait_chan(0);
			dma_write_data_chan(src_addr + 0x01c00,
					    src_addr + 0x02cc0, 0x400, 1, 3);
			dma_wait_chan(1);
			dma_write_data_chan(src_addr + 0x02cc0,
					    src_addr + 0x03cd0, 0x400, 2, 3);
			dma_wait_chan(2);
			dma_write_data_chan(src_addr + 0x03cd0,
					    src_addr + 0x04ce8, 0x400, 3, 3);
			dma_wait_chan(3);
			dma_write_data_chan(src_addr + 0x04ce8,
					    src_addr + 0x05cf0, 0x400, 4, 3);
			dma_wait_chan(4);
			dma_write_data_chan(src_addr + 0x05cf0,
					    src_addr + 0x06c00, 0x400, 5, 3);
			dma_wait_chan(5);
			dma_write_data_chan(src_addr + 0x06c00,
					    src_addr + 0x07c00, 0x400, 6, 3);
			dma_wait_chan(6);
			dma_write_data_chan(src_addr + 0x07c00,
					    src_addr + 0x08cf0, 0x400, 7, 3);
			dma_wait_chan(7);

			for (i = 0; i < 0x10; i = i + 1) {
				addr64_ptr = (volatile unsigned int *)((unsigned long)(src_addr + 0x08cf0 + i * 4));
				rd_val = *(addr64_ptr);
				if (rd_val != 0x12340000 + i)
					printf("dma read %d error!\n", i);
			}
		}
		//}
	}

#if 0
    //////////// memory copy test///////
    src_addr    = 0x100000008;
    dst_addr    = 0x100000208;
    set_value   = 0;
    byte_len    = 32;
    cmd_type    = 0x10;    // memory copy with byte align

    //memory copy
    soc_cmd((( src_addr        & 0xffff) << 16) | 0xa5f0);
    soc_cmd((((src_addr >> 16) & 0xffff) << 16) | 0xa5f1);
    soc_cmd((((src_addr >> 32) & 0xffff) << 16) | 0xa5f2);
    soc_cmd((((src_addr >> 48) & 0xffff) << 16) | 0xa5f3);

    soc_cmd((( dst_addr        & 0xffff) << 16) | 0xa5f4);
    soc_cmd((((dst_addr >> 16) & 0xffff) << 16) | 0xa5f5);
    soc_cmd((((dst_addr >> 32) & 0xffff) << 16) | 0xa5f6);
    soc_cmd((((dst_addr >> 48) & 0xffff) << 16) | 0xa5f7);

    soc_cmd((( set_value        & 0xffff) << 16) | 0xa5f8);
    soc_cmd((((set_value >> 16) & 0xffff) << 16) | 0xa5f9);
    soc_cmd((((set_value >> 32) & 0xffff) << 16) | 0xa5fa);
    soc_cmd((((set_value >> 48) & 0xffff) << 16) | 0xa5fb);

    soc_cmd((( byte_len         & 0xffff) << 16) | 0xa5fc);
    soc_cmd((((byte_len  >> 16) & 0xffff) << 16) | 0xa5fd);

    soc_cmd((( cmd_type         & 0xffff) << 16) | 0xa5fe);

    for(i=0; i<32; i=i+1){
        addr64_ptr=0x100000200+i*4;
        rd_val = *(addr64_ptr) ;
    }
    asm("sync.is");
    for(i=0; i<32; i=i+1){
        addr64_ptr=0x100000200+i*4;
        *(addr64_ptr) = 0;
    }


    //////////// memory copy test///////
    src_addr    = 0x100000007;
    dst_addr    = 0x100000209;
    set_value   = 0;
    byte_len    = 32;
    cmd_type    = 0x10;    // memory copy with byte align

    //memory copy
    soc_cmd((( src_addr        & 0xffff) << 16) | 0xa5f0);
    soc_cmd((((src_addr >> 16) & 0xffff) << 16) | 0xa5f1);
    soc_cmd((((src_addr >> 32) & 0xffff) << 16) | 0xa5f2);
    soc_cmd((((src_addr >> 48) & 0xffff) << 16) | 0xa5f3);

    soc_cmd((( dst_addr        & 0xffff) << 16) | 0xa5f4);
    soc_cmd((((dst_addr >> 16) & 0xffff) << 16) | 0xa5f5);
    soc_cmd((((dst_addr >> 32) & 0xffff) << 16) | 0xa5f6);
    soc_cmd((((dst_addr >> 48) & 0xffff) << 16) | 0xa5f7);

    soc_cmd((( set_value        & 0xffff) << 16) | 0xa5f8);
    soc_cmd((((set_value >> 16) & 0xffff) << 16) | 0xa5f9);
    soc_cmd((((set_value >> 32) & 0xffff) << 16) | 0xa5fa);
    soc_cmd((((set_value >> 48) & 0xffff) << 16) | 0xa5fb);

    soc_cmd((( byte_len         & 0xffff) << 16) | 0xa5fc);
    soc_cmd((((byte_len  >> 16) & 0xffff) << 16) | 0xa5fd);

    soc_cmd((( cmd_type         & 0xffff) << 16) | 0xa5fe);

    for(i=0; i<32; i=i+1){
        addr64_ptr=0x100000200+i*4;
        rd_val = *(addr64_ptr) ;
    }
    asm("sync.is");
    for(i=0; i<32; i=i+1){
        addr64_ptr=0x100000200+i*4;
        *(addr64_ptr) = 0;
    }


    //////////// memory copy test///////
    src_addr    = 0x100000009;
    dst_addr    = 0x100000207;
    set_value   = 0;
    byte_len    = 32;
    cmd_type    = 0x10;    // memory copy with byte align

    //memory copy
    soc_cmd((( src_addr        & 0xffff) << 16) | 0xa5f0);
    soc_cmd((((src_addr >> 16) & 0xffff) << 16) | 0xa5f1);
    soc_cmd((((src_addr >> 32) & 0xffff) << 16) | 0xa5f2);
    soc_cmd((((src_addr >> 48) & 0xffff) << 16) | 0xa5f3);

    soc_cmd((( dst_addr        & 0xffff) << 16) | 0xa5f4);
    soc_cmd((((dst_addr >> 16) & 0xffff) << 16) | 0xa5f5);
    soc_cmd((((dst_addr >> 32) & 0xffff) << 16) | 0xa5f6);
    soc_cmd((((dst_addr >> 48) & 0xffff) << 16) | 0xa5f7);

    soc_cmd((( set_value        & 0xffff) << 16) | 0xa5f8);
    soc_cmd((((set_value >> 16) & 0xffff) << 16) | 0xa5f9);
    soc_cmd((((set_value >> 32) & 0xffff) << 16) | 0xa5fa);
    soc_cmd((((set_value >> 48) & 0xffff) << 16) | 0xa5fb);

    soc_cmd((( byte_len         & 0xffff) << 16) | 0xa5fc);
    soc_cmd((((byte_len  >> 16) & 0xffff) << 16) | 0xa5fd);

    soc_cmd((( cmd_type         & 0xffff) << 16) | 0xa5fe);

    for(i=0; i<32; i=i+1){
        addr64_ptr=0x100000200+i*4;
        rd_val = *(addr64_ptr) ;
    }
    asm("sync.is");
    for(i=0; i<32; i=i+1){
        addr64_ptr=0x100000200+i*4;
        *(addr64_ptr) = 0;
    }


    //////////// memory set test///////
    src_addr    = 0x100000000;
    dst_addr    = 0x100000008;
    set_value   = 0xf0001238a0001234;
    byte_len    = 32;
    cmd_type    = 3;    // memory set with 64 align

    //memory set
    soc_cmd((( dst_addr        & 0xffff) << 16) | 0xa5f4);
    soc_cmd((((dst_addr >> 16) & 0xffff) << 16) | 0xa5f5);
    soc_cmd((((dst_addr >> 32) & 0xffff) << 16) | 0xa5f6);
    soc_cmd((((dst_addr >> 48) & 0xffff) << 16) | 0xa5f7);

    soc_cmd((( set_value        & 0xffff) << 16) | 0xa5f8);
    soc_cmd((((set_value >> 16) & 0xffff) << 16) | 0xa5f9);
    soc_cmd((((set_value >> 32) & 0xffff) << 16) | 0xa5fa);
    soc_cmd((((set_value >> 48) & 0xffff) << 16) | 0xa5fb);

    soc_cmd((( byte_len         & 0xffff) << 16) | 0xa5fc);
    soc_cmd((((byte_len  >> 16) & 0xffff) << 16) | 0xa5fd);

    soc_cmd((( cmd_type         & 0xffff) << 16) | 0xa5fe);

    for(i=0; i<64; i=i+1){
        addr64_ptr=0x100000000+i*4;
        rd_val = *(addr64_ptr) ;
    }
    asm("sync.is");
    for(i=0; i<32; i=i+1){
        addr64_ptr=0x100000200+i*4;
        *(addr64_ptr) = 0;
    }


    //////////// memory set test///////
    src_addr    = 0x100000000;
    dst_addr    = 0x100000009;
    set_value   = 0xab;
    byte_len    = 16;
    cmd_type    = 0;    // memory set with byte

    //memory set
    soc_cmd((( dst_addr        & 0xffff) << 16) | 0xa5f4);
    soc_cmd((((dst_addr >> 16) & 0xffff) << 16) | 0xa5f5);
    soc_cmd((((dst_addr >> 32) & 0xffff) << 16) | 0xa5f6);
    soc_cmd((((dst_addr >> 48) & 0xffff) << 16) | 0xa5f7);

    soc_cmd((( set_value        & 0xffff) << 16) | 0xa5f8);
    soc_cmd((((set_value >> 16) & 0xffff) << 16) | 0xa5f9);
    soc_cmd((((set_value >> 32) & 0xffff) << 16) | 0xa5fa);
    soc_cmd((((set_value >> 48) & 0xffff) << 16) | 0xa5fb);

    soc_cmd((( byte_len         & 0xffff) << 16) | 0xa5fc);
    soc_cmd((((byte_len  >> 16) & 0xffff) << 16) | 0xa5fd);

    soc_cmd((( cmd_type         & 0xffff) << 16) | 0xa5fe);

    for(i=0; i<32; i=i+1){
        addr64_ptr=0x100000000+i*4;
        rd_val = *(addr64_ptr) ;
    }
    asm("sync.is");
    for(i=0; i<32; i=i+1){
        addr64_ptr=0x100000200+i*4;
        *(addr64_ptr) = 0;
    }


    //////////// memory set test///////
    src_addr    = 0x100000000;
    dst_addr    = 0x100000008;
    set_value   = 0xcd;
    byte_len    = 16;
    cmd_type    = 0;    // memory set with byte

    //memory set
    soc_cmd((( dst_addr        & 0xffff) << 16) | 0xa5f4);
    soc_cmd((((dst_addr >> 16) & 0xffff) << 16) | 0xa5f5);
    soc_cmd((((dst_addr >> 32) & 0xffff) << 16) | 0xa5f6);
    soc_cmd((((dst_addr >> 48) & 0xffff) << 16) | 0xa5f7);

    soc_cmd((( set_value        & 0xffff) << 16) | 0xa5f8);
    soc_cmd((((set_value >> 16) & 0xffff) << 16) | 0xa5f9);
    soc_cmd((((set_value >> 32) & 0xffff) << 16) | 0xa5fa);
    soc_cmd((((set_value >> 48) & 0xffff) << 16) | 0xa5fb);

    soc_cmd((( byte_len         & 0xffff) << 16) | 0xa5fc);
    soc_cmd((((byte_len  >> 16) & 0xffff) << 16) | 0xa5fd);

    soc_cmd((( cmd_type         & 0xffff) << 16) | 0xa5fe);

    for(i=0; i<32; i=i+1){
        addr64_ptr=0x100000000+i*4;
        rd_val = *(addr64_ptr) ;
    }
    asm("sync.is");
    for(i=0; i<32; i=i+1){
        addr64_ptr=0x100000200+i*4;
        *(addr64_ptr) = 0;
    }


    //////////// memory set test///////
    src_addr    = 0x100000000;
    dst_addr    = 0x100000007;
    set_value   = 0xef;
    byte_len    = 16;
    cmd_type    = 0;    // memory set with byte

    //memory set
    soc_cmd((( dst_addr        & 0xffff) << 16) | 0xa5f4);
    soc_cmd((((dst_addr >> 16) & 0xffff) << 16) | 0xa5f5);
    soc_cmd((((dst_addr >> 32) & 0xffff) << 16) | 0xa5f6);
    soc_cmd((((dst_addr >> 48) & 0xffff) << 16) | 0xa5f7);

    soc_cmd((( set_value        & 0xffff) << 16) | 0xa5f8);
    soc_cmd((((set_value >> 16) & 0xffff) << 16) | 0xa5f9);
    soc_cmd((((set_value >> 32) & 0xffff) << 16) | 0xa5fa);
    soc_cmd((((set_value >> 48) & 0xffff) << 16) | 0xa5fb);

    soc_cmd((( byte_len         & 0xffff) << 16) | 0xa5fc);
    soc_cmd((((byte_len  >> 16) & 0xffff) << 16) | 0xa5fd);

    soc_cmd((( cmd_type         & 0xffff) << 16) | 0xa5fe);

    for(i=0; i<32; i=i+1){
        addr64_ptr=0x100000000+i*4;
        rd_val = *(addr64_ptr) ;
    }
    asm("sync.is");
    for(i=0; i<32; i=i+1){
        addr64_ptr=0x100000200+i*4;
        *(addr64_ptr) = 0;
    }

    //////////// memory set test///////
    src_addr    = 0x100000000;
    dst_addr    = 0x100000004;
    set_value   = 0x93;
    byte_len    = 20;
    cmd_type    = 0;    // memory set with byte

    //memory set
    soc_cmd((( dst_addr        & 0xffff) << 16) | 0xa5f4);
    soc_cmd((((dst_addr >> 16) & 0xffff) << 16) | 0xa5f5);
    soc_cmd((((dst_addr >> 32) & 0xffff) << 16) | 0xa5f6);
    soc_cmd((((dst_addr >> 48) & 0xffff) << 16) | 0xa5f7);

    soc_cmd((( set_value        & 0xffff) << 16) | 0xa5f8);
    soc_cmd((((set_value >> 16) & 0xffff) << 16) | 0xa5f9);
    soc_cmd((((set_value >> 32) & 0xffff) << 16) | 0xa5fa);
    soc_cmd((((set_value >> 48) & 0xffff) << 16) | 0xa5fb);

    soc_cmd((( byte_len         & 0xffff) << 16) | 0xa5fc);
    soc_cmd((((byte_len  >> 16) & 0xffff) << 16) | 0xa5fd);

    soc_cmd((( cmd_type         & 0xffff) << 16) | 0xa5fe);

    for(i=0; i<32; i=i+1){
        addr64_ptr=0x100000000+i*4;
        rd_val = *(addr64_ptr) ;
    }
    asm("sync.is");
    for(i=0; i<32; i=i+1){
        addr64_ptr=0x100000200+i*4;
        *(addr64_ptr) = 0;
    }


    //////////// memory set test///////
    src_addr    = 0x100000000;
    dst_addr    = 0x10000000c;
    set_value   = 0x12345678;
    byte_len    = 16;
    cmd_type    = 2;    // memory set with word

    //memory set
    soc_cmd((( dst_addr        & 0xffff) << 16) | 0xa5f4);
    soc_cmd((((dst_addr >> 16) & 0xffff) << 16) | 0xa5f5);
    soc_cmd((((dst_addr >> 32) & 0xffff) << 16) | 0xa5f6);
    soc_cmd((((dst_addr >> 48) & 0xffff) << 16) | 0xa5f7);

    soc_cmd((( set_value        & 0xffff) << 16) | 0xa5f8);
    soc_cmd((((set_value >> 16) & 0xffff) << 16) | 0xa5f9);
    soc_cmd((((set_value >> 32) & 0xffff) << 16) | 0xa5fa);
    soc_cmd((((set_value >> 48) & 0xffff) << 16) | 0xa5fb);

    soc_cmd((( byte_len         & 0xffff) << 16) | 0xa5fc);
    soc_cmd((((byte_len  >> 16) & 0xffff) << 16) | 0xa5fd);

    soc_cmd((( cmd_type         & 0xffff) << 16) | 0xa5fe);

    for(i=0; i<32; i=i+1){
        addr64_ptr=0x100000000+i*4;
        rd_val = *(addr64_ptr) ;
    }
    asm("sync.is");
    for(i=0; i<32; i=i+1){
        addr64_ptr=0x100000200+i*4;
        *(addr64_ptr) = 0;
    }


    //////////// memory set test///////
    src_addr    = 0x100000000;
    dst_addr    = 0x100000008;
    set_value   = 0x9abcdef0;
    byte_len    = 16;
    cmd_type    = 2;    // memory set with word

    //memory set
    soc_cmd((( dst_addr        & 0xffff) << 16) | 0xa5f4);
    soc_cmd((((dst_addr >> 16) & 0xffff) << 16) | 0xa5f5);
    soc_cmd((((dst_addr >> 32) & 0xffff) << 16) | 0xa5f6);
    soc_cmd((((dst_addr >> 48) & 0xffff) << 16) | 0xa5f7);

    soc_cmd((( set_value        & 0xffff) << 16) | 0xa5f8);
    soc_cmd((((set_value >> 16) & 0xffff) << 16) | 0xa5f9);
    soc_cmd((((set_value >> 32) & 0xffff) << 16) | 0xa5fa);
    soc_cmd((((set_value >> 48) & 0xffff) << 16) | 0xa5fb);

    soc_cmd((( byte_len         & 0xffff) << 16) | 0xa5fc);
    soc_cmd((((byte_len  >> 16) & 0xffff) << 16) | 0xa5fd);

    soc_cmd((( cmd_type         & 0xffff) << 16) | 0xa5fe);

    for(i=0; i<32; i=i+1){
        addr64_ptr=0x100000000+i*4;
        rd_val = *(addr64_ptr) ;
    }
    asm("sync.is");
    for(i=0; i<32; i=i+1){
        addr64_ptr=0x100000200+i*4;
        *(addr64_ptr) = 0;
    }

#endif

	///////////// bus test /////////////
	if (BUS_TEST == 1) {
		printf("BUS Test!\n");
#if 1
		for (i = 0; i < 1; i = i + 1) { // sap
			MA_OUTW((0xD0000020 + i * 0x100000),
				(0x3)); //  random lower address setting
			MA_OUTW((0xD000001c + i * 0x100000),
				(0x7)); //  transfer len, *16, max 0x800
			MA_OUTW((0xD0000018 + i * 0x100000),
				(0x42000000 + i * 0x100000)); // address
			MA_OUTW((0xD0000014 + i * 0x100000),
				(0x100)); // bus cnt

			MA_OUTW((0xD0000010 + i * 0x100000),
				(0x0)); // bus stop = 1
			MA_OUTW((0xD000000c + i * 0x100000),
				(0x0)); // int enable
			MA_OUTW((0xD0000008 + i * 0x100000),
				(0x0)); // error write clear
			MA_OUTW((0xD0000004 + i * 0x100000),
				(0x0)); // real bus load, read only
			if (MPU_NUM == 0 || MPU_NUM == 2) {
				MA_OUTW(0xc2f087f8, 0); // sap base set
				MA_OUTW((0xD0000000 + i * 0x100000),
					(0x70)); // bus load set, 0=stop, 128=100
			} else if (MPU_NUM == 1) {
				MA_OUTW(0xc2f087f8, 16); // sap base set
				MA_OUTW((0xD0000000 + i * 0x100000),
					(0x70)); // bus load set, 0=stop, 128=100
			}
		}
#endif
#if 1
		for (i = 0; i < 6; i = i + 1) {
			MA_OUTW((0xC4000020 + i * 0x100000),
				(0x3)); //  random lower address setting
			MA_OUTW((0xC400001c + i * 0x100000),
				(0x7)); //  transfer len, *16, max 0x800
			MA_OUTW((0xC4000018 + i * 0x100000),
				(0x10000000 + i * 0x100000)); // address
			MA_OUTW((0xC4000014 + i * 0x100000),
				(0x100)); // bus cnt

			MA_OUTW((0xC4000010 + i * 0x100000),
				(0x0)); // bus stop = 1
			MA_OUTW((0xC400000c + i * 0x100000),
				(0x0)); // int enable
			MA_OUTW((0xC4000008 + i * 0x100000),
				(0x0)); // error write clear
			MA_OUTW((0xC4000004 + i * 0x100000),
				(0x0)); // real bus load, read only

			if (MPU_NUM == 0 || MPU_NUM == 2) {
				MA_OUTW((0xC4F00000 + i * 0x400 + 0x20),
					(0x4)); //  mpu0 base 0x1_0000_0000
			} else if (MPU_NUM == 1) {
				MA_OUTW((0xC4F00000 + i * 0x400 + 0x20),
					(0x5)); //  mpu1 base 0x5_0000_0000
			}

			MA_OUTW((0xC4000000 + i * 0x100000),
				(0x70)); // bus load set, 0=stop, 128=100
		}
		for (i = 0; i < 5; i = i + 1) {
			MA_OUTW((0xC5000020 + i * 0x100000),
				(0x3)); //  random lower address setting
			MA_OUTW((0xC500001c + i * 0x100000),
				(0x7)); //  transfer len, *16, max 0x800
			MA_OUTW((0xC5000018 + i * 0x100000),
				(0x20000000 + i * 0x100000)); // address
			MA_OUTW((0xC5000014 + i * 0x100000),
				(0x100)); // bus cnt

			MA_OUTW((0xC5000010 + i * 0x100000),
				(0x0)); // bus stop = 1
			MA_OUTW((0xC500000c + i * 0x100000),
				(0x0)); // int enable
			MA_OUTW((0xC5000008 + i * 0x100000),
				(0x0)); // error write clear
			MA_OUTW((0xC5000004 + i * 0x100000),
				(0x0)); // real bus load, read only

			if (MPU_NUM == 0 || MPU_NUM == 2) {
				MA_OUTW((0xC5F00000 + i * 0x400 + 0x20),
					(0x2)); //  mpu0 base 0x1_0000_0000
			} else if (MPU_NUM == 1) {
				if (LPDDR4 ==
				    0) { // LPDDR4 controller will cause illegal address access
					MA_OUTW((0xC5F00000 + i * 0x400 + 0x20),
						(0x5)); //  mpu1 base 0x5_0000_0000
				} else {
					MA_OUTW((0xC5F00000 + i * 0x400 + 0x20),
						(0x6)); //  mpu1 base 0x5_0000_0000
				}
			}

			MA_OUTW((0xC5000000 + i * 0x100000),
				(0x70)); // bus load set, 0=stop, 128=100
		}
#endif
		for (j = 0; j < 4; j = j + 1) {
			for (i = 0; i < 1; i = i + 1) {
				MA_OUTW((0xC6000020 + j * 0x1000000 +
					 i * 0x100000),
					(0x3)); //  random lower address setting
				MA_OUTW((0xC600001c + j * 0x1000000 +
					 i * 0x100000),
					(0x7)); //  transfer len, *16, max 0x800
				MA_OUTW((0xC6000018 + j * 0x1000000 +
					 i * 0x100000),
					(0x30000000 + j * 0x10000000 +
					 i * 0x100000)); // address
				MA_OUTW((0xC6000014 + j * 0x1000000 +
					 i * 0x100000),
					(0x100)); // bus cnt

				MA_OUTW((0xC6000010 + j * 0x1000000 +
					 i * 0x100000),
					(0x0)); // bus stop = 1
				MA_OUTW((0xC600000c + j * 0x1000000 +
					 i * 0x100000),
					(0x0)); // int enable
				MA_OUTW((0xC6000008 + j * 0x1000000 +
					 i * 0x100000),
					(0x0)); // error write clear
				MA_OUTW((0xC6000004 + j * 0x1000000 +
					 i * 0x100000),
					(0x0)); // real bus load, read only

				if (MPU_NUM == 0 || MPU_NUM == 2) {
					MA_OUTW((0xC6F00000 + j * 0x1000000 +
						 i * 0x400 + 0x20),
						(0x1)); //  mpu0 base 0x1_0000_0000
				} else if (MPU_NUM == 1) {
					if (LPDDR4 ==
					    0) { // LPDDR4 controller will cause illegal address access
						MA_OUTW((0xC6F00000 +
							 j * 0x1000000 +
							 i * 0x400 + 0x20),
							(0x5)); //  mpu1 base 0x5_0000_0000
					} else {
						MA_OUTW((0xC6F00000 +
							 j * 0x1000000 +
							 i * 0x400 + 0x20),
							(0x7)); //  mpu1 base 0x5_0000_0000
					}
				}

				MA_OUTW((0xC6000000 + j * 0x1000000 +
					 i * 0x100000),
					(0x70)); // bus load set, 0=stop, 128=100
			}
		}

		printf("BUS Testing!\n");
		halt_cnt = 0;
		while (1) {
			for (i = 0; i < 1; i = i + 1) {
				rd_val = MA_INW((0xD0000008 + i * 0x100000));
				if (rd_val)
					printf("sap bus1 m%1d error!\n", i);

				rd_val = MA_INW((0xD0000004 + i * 0x100000));
				if (rd_val == 0) {
					printf("sap bus1 m%1d halt!\n", i);
					halt_cnt = halt_cnt + 1;
				}
			}
			for (i = 0; i < 6; i = i + 1) {
				if (i != 3) { // disable b1m3
					rd_val = MA_INW(
						(0xC4000008 + i * 0x100000));
					if (rd_val)
						printf("bus1 m%1d error!\n", i);

					rd_val = MA_INW(
						(0xC4000004 + i * 0x100000));
					if (rd_val == 0) {
						printf("bus1 m%1d halt!\n", i);
						halt_cnt = halt_cnt + 1;
					}
				}
			}
			for (i = 0; i < 5; i = i + 1) {
				rd_val = MA_INW((0xC5000008 + i * 0x100000));
				if (rd_val)
					printf("bus2 m%1d error!\n", i);

				rd_val = MA_INW((0xC5000004 + i * 0x100000));
				if (rd_val == 0) {
					printf("bus2 m%1d halt!\n", i);
					halt_cnt = halt_cnt + 1;
				}
			}
			for (i = 0; i < 4; i = i + 1) {
				rd_val = MA_INW((0xC6000008 + i * 0x1000000));
				if (rd_val)
					printf("bus%1d error!\n", i + 3);

				rd_val = MA_INW((0xC6000004 + i * 0x1000000));
				if (rd_val == 0) {
					printf("bus%1d halt!\n", i + 3);
					halt_cnt = halt_cnt + 1;
				}
			}
			if (halt_cnt > 40)
				printf("bus halt reach set!\n");
		}

		while (1)
			;
		//
	}
	///////////// bus test /////////////
}

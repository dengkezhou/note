
#include "lpddr4_common.h"

#if 0
void lpddr4_rwcfg (void) {

uint32_t i, rd_val;

unsigned int lpddr4_1066_cl20_bl16_wcfg[] = {
    0x0000028c , 0x00012d0e,
    0x000004f0 , 0x00000001,
    0x000004cc , 0x01000001,
    0x000004c8 , 0x00010101,
    0x000004cc , 0x00000001,
    0x000004f0 , 0x00000001,
    0x00005520 , 0x01000000,
    0x00005648 , 0x20040000,
    0x00005508 , 0x00000008,
    0x000003b0 , 0x00000000,
    0x00000074 , 0x01000010,
    0x00002010 , 0x00000000,
    0x000021a4 , 0x00000000,
    0x000002c4 , 0x00000202,
    0x00005434 , 0x01002001,
    0x00000000 , 0x10460b01 
};

for(i=0; i<16; i=i+1){
    rd_val = MA_INW(0xc3000000+lpddr4_1066_cl20_bl16_wcfg[i*2]);  
    MA_OUTW(0xc3000000+lpddr4_1066_cl20_bl16_wcfg[i*2], lpddr4_1066_cl20_bl16_wcfg[i*2+1]);
}
}
#endif

int lpddr4_bus_stress_test(void)
{
	uint32_t i, j, rd_val, test_cnt = 0;
	volatile unsigned int *addr64_ptr;

	for (i = 0; i < 32; i = i + 1) {
#if defined(CONFIG_E906)
		addr64_ptr = (volatile unsigned int *)(E906_MAP_TO_DDR + i * 4);
#else
		addr64_ptr = (volatile unsigned int *)(0x100000000 + i * 4);
#endif
		*(addr64_ptr) = 0x12340 + i;
	}
#if !defined(CONFIG_E906)
	asm("sync.is");
	printf("asm OK!\n");
#else
	udelay(100);
#endif
	for (i = 0; i < 32; i = i + 1) {
#if defined(CONFIG_E906)
		addr64_ptr = (volatile unsigned int *)(E906_MAP_TO_DDR + i * 4);
#else
		addr64_ptr = (volatile unsigned int *)(0x100000000 + i * 4);
#endif
		rd_val = *(addr64_ptr);
		if (rd_val != (0x12340 + i))
			printf("MPU read error, 0x%x!\n", rd_val);
	}
	printf("MPU read OK!\n");

	///////////// bus test /////////////
	printf("BUS Test!\n");
	for (i = 0; i < 1; i = i + 1) { // sap
		MA_OUTW((0xD0000020 + i * 0x100000),
			(0x3)); //  random lower address setting
		MA_OUTW((0xD000001c + i * 0x100000),
			(0x7)); //  transfer len, *16, max 0x800
		MA_OUTW((0xD0000018 + i * 0x100000),
			(0x42000000 + i * 0x100000)); // address
		MA_OUTW((0xD0000014 + i * 0x100000), (0x100)); // bus cnt

		MA_OUTW((0xD0000010 + i * 0x100000), (0x0)); // bus stop = 1
		MA_OUTW((0xD000000c + i * 0x100000), (0x0)); // int enable
		MA_OUTW((0xD0000008 + i * 0x100000),
			(0x0)); // error write clear
		MA_OUTW((0xD0000004 + i * 0x100000),
			(0x0)); // real bus load, read only
		MA_OUTW((0xD0000000 + i * 0x100000),
			(0x40)); // bus load set, 0=stop, 128=100
	}

	for (i = 0; i < 6; i = i + 1) {
		MA_OUTW((0xC4000020 + i * 0x100000),
			(0x3)); //  random lower address setting
		MA_OUTW((0xC400001c + i * 0x100000),
			(0x7)); //  transfer len, *16, max 0x800
		MA_OUTW((0xC4000018 + i * 0x100000),
			(0x10000000 + i * 0x100000)); // address
		MA_OUTW((0xC4000014 + i * 0x100000), (0x100)); // bus cnt

		MA_OUTW((0xC4000010 + i * 0x100000), (0x0)); // bus stop = 1
		MA_OUTW((0xC400000c + i * 0x100000), (0x0)); // int enable
		MA_OUTW((0xC4000008 + i * 0x100000),
			(0x0)); // error write clear
		MA_OUTW((0xC4000004 + i * 0x100000),
			(0x0)); // real bus load, read only
		MA_OUTW((0xC4000000 + i * 0x100000),
			(0x40)); // bus load set, 0=stop, 128=100
	}

	for (i = 0; i < 5; i = i + 1) {
		MA_OUTW((0xC5000020 + i * 0x100000),
			(0x3)); //  random lower address setting
		MA_OUTW((0xC500001c + i * 0x100000),
			(0x7)); //  transfer len, *16, max 0x800
		MA_OUTW((0xC5000018 + i * 0x100000),
			(0x20000000 + i * 0x100000)); // address
		MA_OUTW((0xC5000014 + i * 0x100000), (0x100)); // bus cnt

		MA_OUTW((0xC5000010 + i * 0x100000), (0x0)); // bus stop = 1
		MA_OUTW((0xC500000c + i * 0x100000), (0x0)); // int enable
		MA_OUTW((0xC5000008 + i * 0x100000),
			(0x0)); // error write clear
		MA_OUTW((0xC5000004 + i * 0x100000),
			(0x0)); // real bus load, read only
		MA_OUTW((0xC5000000 + i * 0x100000),
			(0x40)); // bus load set, 0=stop, 128=100
	}

	for (j = 0; j < 4; j = j + 1) {
		for (i = 0; i < 1; i = i + 1) {
			MA_OUTW((0xC6000020 + j * 0x1000000 + i * 0x100000),
				(0x3)); //  random lower address setting
			MA_OUTW((0xC600001c + j * 0x1000000 + i * 0x100000),
				(0x7)); //  transfer len, *16, max 0x800
			MA_OUTW((0xC6000018 + j * 0x1000000 + i * 0x100000),
				(0x30000000 + j * 0x10000000 +
				 i * 0x100000)); // address
			MA_OUTW((0xC6000014 + j * 0x1000000 + i * 0x100000),
				(0x100)); // bus cnt

			MA_OUTW((0xC6000010 + j * 0x1000000 + i * 0x100000),
				(0x0)); // bus stop = 1
			MA_OUTW((0xC600000c + j * 0x1000000 + i * 0x100000),
				(0x0)); // int enable
			MA_OUTW((0xC6000008 + j * 0x1000000 + i * 0x100000),
				(0x0)); // error write clear
			MA_OUTW((0xC6000004 + j * 0x1000000 + i * 0x100000),
				(0x0)); // real bus load, read only
			MA_OUTW((0xC6000000 + j * 0x1000000 + i * 0x100000),
				(0x40)); // bus load set, 0=stop, 128=100
		}
	}

	for (i = 5; i < 7; i = i + 1) { // index of bus2 module system
		MA_OUTW((0xC5f00000 + i * 0x400 + 0x8), (0x1)); // power up
		rd_val = 0;
		while (!rd_val) {
			rd_val = MA_INW(0xC5f00000 + i * 0x400 + 0x8) &
				 0x10; // polling power-ack
		}
		MA_OUTW((0xC5f00000 + i * 0x400 + 0x8),
			(0x1)); // power up & iso disable

		//MA_OUTW((0xC5f00000+i*0x400+0x1c),(0x1));  // reset clock enable

		MA_OUTW((0xC5f00000 + i * 0x400 + 0x4), (0xffff)); // clkgate en
		MA_OUTW((0xC5f00000 + i * 0x400 + 0xc), (0x3)); // bus en
		MA_OUTW((0xC5f00000 + i * 0x400 + 0x18), (0x1)); // io in en

		rd_val = MA_INW((0xC5f00000 + i * 0x400 +
				 0xc)); // check bus enable register
		if (rd_val != 0x3) {
			printf("bus2 sysm read/write error\n");
		}
		MA_OUTW((0xC5f00000 + i * 0x400 + 0x0), (0x0)); // reset release
	}

	//dma_write_data(0x110000000, 0x125100000, 0x400);

	printf("BUS Testing!\n");
	while (1) {
		test_cnt++;
		if (test_cnt >= 300000) {
			printf("%d cycles\n", test_cnt);
			test_cnt = 0;
		}
		for (i = 0; i < 1; i = i + 1) {
			rd_val = MA_INW((0xD0000008 + i * 0x100000));
			if (rd_val) {
				printf("sap bus1 m%1d error!\n", i);
				return -1;
			}
		}
		for (i = 0; i < 6; i = i + 1) {
			rd_val = MA_INW((0xC4000008 + i * 0x100000));
			if (rd_val) {
				printf("bus1 m%1d error!\n", i);
				return -1;
			}
		}
		for (i = 0; i < 5; i = i + 1) {
			rd_val = MA_INW((0xC5000008 + i * 0x100000));
			if (rd_val) {
				printf("bus2 m%1d error!\n", i);
				return -1;
			}
		}
		for (i = 0; i < 4; i = i + 1) {
			rd_val = MA_INW((0xC6000008 + i * 0x1000000));
			if (rd_val) {
				printf("bus%1d error!\n", i + 3);
				return -1;
			}
		}
	}

	while (1)
		;
	//
	///////////// bus test /////////////

	return -1;
}

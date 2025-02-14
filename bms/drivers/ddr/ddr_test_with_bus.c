
#include <common.h>
#include <command.h>
#include <testbench.h>
#include <malloc.h>
#include <dma-ops.h>
#include <asm/io.h>
#include <getopt.h>
#include <cache.h>
#include <pads.h>
#ifdef CONFIG_MMU
#include <mmu_table.h>
#endif

#define CHANNEL_NUMS 2

#ifdef CONFIG_COMPILE_FPGA
#define DMA_BUFLEN (8192 * 2)
#define DEVTODEV_DMA_BUFLEN (64 * 2)
#elif defined(CONFIG_COMPILE_RTL)
#define DMA_BUFLEN (16 * 2)
#define DEVTODEV_DMA_BUFLEN (16 * 2)
#endif

#define MA_OUTW(a,b) writel((b), (a))
#define MA_INW(a) readl((a))

#define CLKGEN_BASE 0xc2f08000
#define SCLKGEN_BASE 0xd2f08000

#define CLKGEN_ALDCFG (CLKGEN_BASE + 0x1c)
#define CLKGEN_AEN (CLKGEN_BASE + 0x20)
#define CLKGEN_ASEL (CLKGEN_BASE + 0x24)
#define CLKGEN_ALOCK (CLKGEN_BASE + 0x28)

#define CLKGEN_DLDCFG (CLKGEN_BASE + 0x4c)
#define CLKGEN_DEN (CLKGEN_BASE + 0x50)
#define CLKGEN_DSEL (CLKGEN_BASE + 0x54)
#define CLKGEN_DLOCK (CLKGEN_BASE + 0x58)

#define CLKGEN_ELDCFG (CLKGEN_BASE + 0x7c)
#define CLKGEN_EEN (CLKGEN_BASE + 0x80)
#define CLKGEN_ESEL (CLKGEN_BASE + 0x84)
#define CLKGEN_ELOCK (CLKGEN_BASE + 0x88)

#define CLKGEN_VLDCFG (CLKGEN_BASE + 0xac)
#define CLKGEN_VEN (CLKGEN_BASE + 0xb0)
#define CLKGEN_VSEL (CLKGEN_BASE + 0xb4)
#define CLKGEN_VLOCK (CLKGEN_BASE + 0xb8)

#define MLCLKG_BASE (CLKGEN_BASE + 0xc0)

#define SCLKGEN_ALDCFG (SCLKGEN_BASE + 0x1c)
#define SCLKGEN_AEN (SCLKGEN_BASE + 0x20)
#define SCLKGEN_ALOCK (SCLKGEN_BASE + 0x28)
#define SCLKGEN_ASEL (SCLKGEN_BASE + 0x24)

int ddr_stress_test(void);

static int dma_memcpy_test(void)
{
	struct dma_chan *chan = NULL;
	struct dma_prep_info prep_info;
	struct dma_info info = {
		.devname = "dma0",
	};
	unsigned char *mem = NULL;
	dma_cookie_t cookie;
	int ret = 0;

	if (!itcs_is_dma_inited(0))
		itcs_dma_init(0);

	if (!itcs_is_dma_inited(1))
		itcs_dma_init(1);

	chan = itcs_dma_request_channel(&info);
	if (!chan)
		return -1;

	mem = malloc(DMA_BUFLEN);
	if (!mem)
		return -1;

	memset(mem, 0xac, DMA_BUFLEN / 2);
	memset(mem + DMA_BUFLEN / 2, 0xdb, DMA_BUFLEN / 2);

	prep_info.direction = DMA_MEM_TO_MEM;
	prep_info.mode = DMA_SLAVE;
	prep_info.src = virt_to_phys(mem);
	prep_info.dst = virt_to_phys(mem + DMA_BUFLEN / 2);
	prep_info.len = DMA_BUFLEN / 2;
	prep_info.callback = NULL;
	cookie = itcs_dma_prepare(chan, &prep_info);
	if (cookie < 0)
		return -1;

	itcs_dcache_flush();
	itcs_dma_start(chan);
	while (1) {
		ret = itcs_dma_transfer_completed(chan, cookie, NULL);
		if (ret != DMA_IN_PROGRESS)
			break;

		udelay(100);
	}
	if (ret == DMA_COMPLETE &&
	    !memcmp((char *)phys_to_virt(prep_info.src),
		    (char *)phys_to_virt(prep_info.dst),
		    prep_info.len)) {
		printf("Test DMA MemToMem Pass\n");
		ret = 0;
	} else {
		printf("Test DMA MemToMem Failed\n");
		ret = -1;
	}

	free(mem);
	itcs_dma_stop(chan);
	itcs_dma_release_channel(chan);
	return ret;
}

int ddr_stress_test(void)
{
	uint32_t i, j, rd_val;
	volatile unsigned int *addr64_ptr;
	int ret;

#if 0
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

	// SPLL
	MA_OUTW(SCLKGEN_ALDCFG,
		3); // load parameter, newdiv[2], load[1], oute[0]
	MA_OUTW(SCLKGEN_AEN, 1); // pll enable

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

	MA_OUTW(CLKGEN_DSEL, 2); // pll source sel and output sel
	MA_OUTW(CLKGEN_ESEL, 2); // pll source sel and output sel
	MA_OUTW(CLKGEN_VSEL, 2); // pll source sel and output sel
	/////////////////////////////
	printf("MPU Test!\n");

	//itcs_module_enable(CPU, "ddr");
	//2133Mbps
	//MA_OUTW(MLCLKG_BASE+0x74, 1);    // set ratio, mpu_clk=mpu_clk_x2/2
	//4266Mbps
	MA_OUTW(MLCLKG_BASE + 0x74, 0); // set ratio, mpu_clk=mpu_clk_x2/2

	// mpu sysm
	MA_OUTW(0xc30f0000 + 0x4, 0xffff); // set clk enable
	MA_OUTW(0xc30f0000 + 0x0, 0xfffc); // apb/ctl/phy reset release

	printf("MPU write done!\n");

	rd_val = 0;
	while (rd_val != 0x1) {
		rd_val = MA_INW(0xc3008000 + 0x14) &
			 0x1; //check  controller_init_done
	}

	MA_OUTW(0xc3010000 + 0x0, 0x1); // pmu sample enable

	MA_OUTW(0xc30f0000 + 0x0, 0x0); // port reset release

	//MA_OUTL(0x100000000, 0x1234);
	//rd_val = MA_INL(0x100000000) ;
#endif
	for (i = 0; i < 32; i = i + 1) {
		addr64_ptr = (volatile unsigned int *)(0x100000000 + i * 4);
		*(addr64_ptr) = 0x12340 + i;
	}

	asm("sync.is");

	for (i = 0; i < 32; i = i + 1) {
		addr64_ptr = (volatile unsigned int *)(0x100000000 + i * 4);
		rd_val = *(addr64_ptr);
		if (rd_val != (0x12340 + i))
			printf("MPU read error!\n");
	}

	///////////// bus test /////////////
	printf("BUS Test!\n");
	for (i = 0; i < 1; i = i + 1) { // sap
		MA_OUTW((0xD0000020 + i * 0x100000),
			(0x3)); //  random lower address setting
		MA_OUTW((0xD000001c + i * 0x100000),
			(0x7)); //  transfer len, *16, max 0x800
		MA_OUTW((0xD0000018 + i * 0x100000),
			(0x7f000000 + i * 0x100000)); // address + 0x100000000 - 0x40000000
			//0x42000000
			//0x50000000
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
			(0x10000000 + i * 0x100000)); // address + 0x100000000
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
	//unsigned long long cnt = 0;
	while (1) {
		//cnt++;
		//printf("cnt: %d\n", cnt);
		ret = dma_memcpy_test();
		if (ret < 0) {
			printf("dma memcpy test failed!\n");
			return -1;
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

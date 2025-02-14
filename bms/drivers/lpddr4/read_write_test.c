
#include "lpddr4_common.h"

#define LPDDR4_SIZE (100 * 1024 * 1024)

int lpddr4_rw_test(void)
{
	uint32_t i, rd_val;
	volatile unsigned int *addr64_ptr;

	printf("read and write test\n");
	for (i = 0; i < LPDDR4_SIZE; i = i + 1) {
#if defined(CONFIG_E906)
		/* mpu0 */
		addr64_ptr = (volatile unsigned int *)(E906_MAP_TO_DDR + i * 4);
#else
		/* mpu1 */
		addr64_ptr = (volatile unsigned int *)(0x500000000 + i * 4);
#endif
		*(addr64_ptr) = 0x12340 + i;
		if (i % 10000000 == 0)
			printf("cnt: %d\n", i);
	}
#if !defined(CONFIG_E906)
	asm("sync.is");
#else
	udelay(1);
#endif
	printf("write done, start read...\n");

	for (i = 0; i < LPDDR4_SIZE; i = i + 1) {
#if defined(CONFIG_E906)
		addr64_ptr = (volatile unsigned int *)(E906_MAP_TO_DDR + i * 4);
#else
		addr64_ptr = (volatile unsigned int *)(0x500000000 + i * 4);
#endif
		rd_val = *(addr64_ptr);
		//printf("---rd val: 0x%lx, 0x%x---\n", addr64_ptr, rd_val);
		if (rd_val != (0x12340 + i)) {
			printf("MPU read error!\n");
			return -1;
		}
		if (i % 10000000 == 0)
			printf("cnt: %d\n", i);
	}
	printf("MPU read & write OK!\n");
	return 0;
}

#ifndef __IDS_API__
#define __IDS_API__

#include <ids/ids.h>

enum format_type {
	IDS_PAL_BPP1,
	IDS_PAL_BPP2,
	IDS_PAL_BPP4,
	IDS_PAL_BPP8,
	IDS_RGB_BPP8_1A232,
	IDS_RGB_BPP16_565,
	IDS_RGB_BPP16_1A555,
	IDS_RGB_BPP16_I555,
	IDS_RGB_BPP18_666,
	IDS_RGB_BPP18_1A665,
	IDS_RGB_BPP19_1A666,
	IDS_RGB_BPP24_888,
	IDS_RGB_BPP24_1A887,
	IDS_RGB_BPP25_1A888,
	IDS_RGB_BPP28_4A888,
	IDS_RGB_BPP16_4A444,
	IDS_RGB_BPP32_8A888,
	IDS_YUV_420SP,
	IDS_RGB_BPP32_888A,
	IDS_RGB_BPP16_555A,
	IDS_RGB_BPP16_555I,
};

extern int ids_init(void);
extern int ids_set_format(enum format_type format);
extern void ids_set_vm_width(int width);
extern void ids_set_resolution(int hozval, int lineval);
extern int ids_set_dma_addr(uint8_t *yaddr, uint8_t *uvaddr);
extern void ids_enable(int enable);
#endif

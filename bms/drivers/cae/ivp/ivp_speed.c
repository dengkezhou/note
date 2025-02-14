#include <common.h>
#include <malloc.h>

typedef struct {
	unsigned int *context_ptr;
	volatile unsigned int ivp_cae_base_addr;
} core_desc;

extern volatile unsigned int ivp_cae_base_addr;
extern void dual_core_test_for_rtl(int enc);
extern void aes_128_gcm_dual_core(int enc);

static void core_dec_prepare(core_desc *cd)
{
if(!cd->context_ptr)
printf("cd->context_ptr malloc failed!\n");
#if defined(CONFIG_COMPILE_FPGA) || defined(CONFIG_COMPILE_ASIC)
memset(cd->context_ptr,0,64*1024);
#endif
writel(0xa7050f08&0xffffffff,cd->ivp_cae_base_addr+0x0000f000);
writel(0x8000c807&0xffffffff,cd->ivp_cae_base_addr+0x0000f400);
writel(0x00007500&0xffffffff,cd->ivp_cae_base_addr+0x00010100);
writel(0x0000f800&0xffffffff,cd->ivp_cae_base_addr+0x00010000);
writel(0x00000087&0xffffffff,cd->ivp_cae_base_addr+0x00011c00);
writel(0x00410000&0xffffffff,cd->ivp_cae_base_addr+0x00011000);
writel(0x00000225&0xffffffff,cd->ivp_cae_base_addr+0x00011008);
writel(0x80000000&0xffffffff,cd->ivp_cae_base_addr+0x0000f200);
writel(0x80000000&0xffffffff,cd->ivp_cae_base_addr+0x0000f600);
readl(cd->ivp_cae_base_addr+0x0000f200);
writel(0x40000000&0xffffffff,cd->ivp_cae_base_addr+0x0000f200);
readl(cd->ivp_cae_base_addr+0x0000f600);
writel(0x40000000&0xffffffff,cd->ivp_cae_base_addr+0x0000f600);
writel(((unsigned long)cd->context_ptr+0x00000000)&0xffffffffffffffff,cd->ivp_cae_base_addr+0x00000008);
writel((((unsigned long)cd->context_ptr+0x00000000)>>32)&(0xffffffffffffffff>>32),cd->ivp_cae_base_addr+0x00000008+0x4);
writel(((unsigned long)cd->context_ptr+0x00000000)&0xffffffffffffffff,cd->ivp_cae_base_addr+0x00000010);
writel((((unsigned long)cd->context_ptr+0x00000000)>>32)&(0xffffffffffffffff>>32),cd->ivp_cae_base_addr+0x00000010+0x4);
writel(0x00000000&0xffffffff,cd->ivp_cae_base_addr+0x00000020);
writel(0x80000000&0xffffffff,cd->ivp_cae_base_addr+0x0000002c);
writel(0x00000000&0xffffffff,cd->ivp_cae_base_addr+0x00000034);
writel(0x00000000&0xffffffff,cd->ivp_cae_base_addr+0x00000038);
writel(0x00001800&0xffffffff,cd->ivp_cae_base_addr+0x00000018);
writel(((unsigned long)cd->context_ptr+0x00000000)&0xffffffffffffffff,cd->ivp_cae_base_addr+0x00000000);
writel((((unsigned long)cd->context_ptr+0x00000000)>>32)&(0xffffffffffffffff>>32),cd->ivp_cae_base_addr+0x00000000+0x4);
writel(0x80000000&0xffffffff,cd->ivp_cae_base_addr+0x00000030);
writel(0x01000000&0xffffffff,cd->ivp_cae_base_addr+0x00000024);
writel(0x40060006&0xffffffff,cd->ivp_cae_base_addr+0x0000001c);
writel(0x0000003f&0xffffffff,cd->ivp_cae_base_addr+0x0000003c);
writel(0x00120012&0xffffffff,cd->ivp_cae_base_addr+0x00000020);
readl(cd->ivp_cae_base_addr+0x0000f010);
writel(0x0000000f&0xffffffff,cd->ivp_cae_base_addr+0x0000f010);
readl(cd->ivp_cae_base_addr+0x0000f200);
writel(0x40000001&0xffffffff,cd->ivp_cae_base_addr+0x0000f200);
writel(((unsigned long)cd->context_ptr+0x00000000)&0xffffffffffffffff,cd->ivp_cae_base_addr+0x00001008);
writel((((unsigned long)cd->context_ptr+0x00000000)>>32)&(0xffffffffffffffff>>32),cd->ivp_cae_base_addr+0x00001008+0x4);
writel(((unsigned long)cd->context_ptr+0x00000000)&0xffffffffffffffff,cd->ivp_cae_base_addr+0x00001010);
writel((((unsigned long)cd->context_ptr+0x00000000)>>32)&(0xffffffffffffffff>>32),cd->ivp_cae_base_addr+0x00001010+0x4);
writel(0x00000000&0xffffffff,cd->ivp_cae_base_addr+0x00001020);
writel(0x80000000&0xffffffff,cd->ivp_cae_base_addr+0x0000102c);
writel(0x00000000&0xffffffff,cd->ivp_cae_base_addr+0x00001034);
writel(0x00000000&0xffffffff,cd->ivp_cae_base_addr+0x00001038);
writel(0x00001800&0xffffffff,cd->ivp_cae_base_addr+0x00001018);
writel(((unsigned long)cd->context_ptr+0x00001800)&0xffffffffffffffff,cd->ivp_cae_base_addr+0x00001000);
writel((((unsigned long)cd->context_ptr+0x00001800)>>32)&(0xffffffffffffffff>>32),cd->ivp_cae_base_addr+0x00001000+0x4);
writel(0x80000000&0xffffffff,cd->ivp_cae_base_addr+0x00001030);
writel(0x01000000&0xffffffff,cd->ivp_cae_base_addr+0x00001024);
writel(0x40060006&0xffffffff,cd->ivp_cae_base_addr+0x0000101c);
writel(0x0000003f&0xffffffff,cd->ivp_cae_base_addr+0x0000103c);
writel(0x00120012&0xffffffff,cd->ivp_cae_base_addr+0x00001020);
readl(cd->ivp_cae_base_addr+0x0000f010);
writel(0x00000f0f&0xffffffff,cd->ivp_cae_base_addr+0x0000f010);
readl(cd->ivp_cae_base_addr+0x0000f200);
writel(0x40000003&0xffffffff,cd->ivp_cae_base_addr+0x0000f200);
writel(0x01000000&0xffffffff,cd->ivp_cae_base_addr+0x00000824);
writel(((unsigned long)cd->context_ptr+0x00000000)&0xffffffffffffffff,cd->ivp_cae_base_addr+0x00000808);
writel((((unsigned long)cd->context_ptr+0x00000000)>>32)&(0xffffffffffffffff>>32),cd->ivp_cae_base_addr+0x00000808+0x4);
writel(((unsigned long)cd->context_ptr+0x00003000)&0xffffffffffffffff,cd->ivp_cae_base_addr+0x00000800);
writel((((unsigned long)cd->context_ptr+0x00003000)>>32)&(0xffffffffffffffff>>32),cd->ivp_cae_base_addr+0x00000800+0x4);
writel(0x00001800&0xffffffff,cd->ivp_cae_base_addr+0x00000818);
writel(0x00060006&0xffffffff,cd->ivp_cae_base_addr+0x0000081c);
writel(0x00080018&0xffffffff,cd->ivp_cae_base_addr+0x00000820);
writel(0x80000000&0xffffffff,cd->ivp_cae_base_addr+0x0000082c);
writel(0x80000000&0xffffffff,cd->ivp_cae_base_addr+0x00000830);
writel(0x00000000&0xffffffff,cd->ivp_cae_base_addr+0x00000834);
writel(0x00000000&0xffffffff,cd->ivp_cae_base_addr+0x00000838);
writel(0x00000000&0xffffffff,cd->ivp_cae_base_addr+0x00000828);
writel(0x000000ff&0xffffffff,cd->ivp_cae_base_addr+0x0000083c);
readl(cd->ivp_cae_base_addr+0x0000f410);
writel(0x0000000f&0xffffffff,cd->ivp_cae_base_addr+0x0000f410);
readl(cd->ivp_cae_base_addr+0x0000f600);
writel(0x40000001&0xffffffff,cd->ivp_cae_base_addr+0x0000f600);
writel(0x01000000&0xffffffff,cd->ivp_cae_base_addr+0x00001824);
writel(((unsigned long)cd->context_ptr+0x00000000)&0xffffffffffffffff,cd->ivp_cae_base_addr+0x00001808);
writel((((unsigned long)cd->context_ptr+0x00000000)>>32)&(0xffffffffffffffff>>32),cd->ivp_cae_base_addr+0x00001808+0x4);
writel(((unsigned long)cd->context_ptr+0x00004800)&0xffffffffffffffff,cd->ivp_cae_base_addr+0x00001800);
writel((((unsigned long)cd->context_ptr+0x00004800)>>32)&(0xffffffffffffffff>>32),cd->ivp_cae_base_addr+0x00001800+0x4);
writel(0x00001800&0xffffffff,cd->ivp_cae_base_addr+0x00001818);
writel(0x00060006&0xffffffff,cd->ivp_cae_base_addr+0x0000181c);
writel(0x00080018&0xffffffff,cd->ivp_cae_base_addr+0x00001820);
writel(0x80000000&0xffffffff,cd->ivp_cae_base_addr+0x0000182c);
writel(0x80000000&0xffffffff,cd->ivp_cae_base_addr+0x00001830);
writel(0x00000000&0xffffffff,cd->ivp_cae_base_addr+0x00001834);
writel(0x00000000&0xffffffff,cd->ivp_cae_base_addr+0x00001838);
writel(0x00000000&0xffffffff,cd->ivp_cae_base_addr+0x00001828);
writel(0x000000ff&0xffffffff,cd->ivp_cae_base_addr+0x0000183c);
readl(cd->ivp_cae_base_addr+0x0000f410);
writel(0x00000f00&0xffffffff,cd->ivp_cae_base_addr+0x0000f410);
readl(cd->ivp_cae_base_addr+0x0000f600);
writel(0x40000003&0xffffffff,cd->ivp_cae_base_addr+0x0000f600);
*((unsigned int *)((unsigned long)cd->context_ptr+0x00006000))=0x010b0805;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00006000+4*1))=0x000001e1;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00006000+4*2))=0x16157e2b;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00006000+4*3))=0xa6d2ae28;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00006000+4*4))=0x8815f7ab;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00006000+4*5))=0x3c4fcf09;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00006000+4*6))=0x03020100;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00006000+4*7))=0x07060504;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00006000+4*8))=0x0b0a0908;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00006000+4*9))=0x0f0e0d0c;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00006028))=0x010d0a05;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00006028+4*1))=0x000001e1;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00006028+4*2))=0xf7b0738e;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00006028+4*3))=0x52640eda;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00006028+4*4))=0x2bf310c8;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00006028+4*5))=0xe5799080;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00006028+4*6))=0xd2eaf862;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00006028+4*7))=0x7b6b2c52;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00006028+4*8))=0x03020100;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00006028+4*9))=0x07060504;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00006028+4*10))=0x0b0a0908;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00006028+4*11))=0x0f0e0d0c;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00006058))=0x010f0c05;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00006058+4*1))=0x000001e1;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00006058+4*2))=0x10eb3d60;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00006058+4*3))=0xbe71ca15;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00006058+4*4))=0xf0ae732b;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00006058+4*5))=0x81777d85;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00006058+4*6))=0x072c351f;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00006058+4*7))=0xd708613b;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00006058+4*8))=0xa310982d;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00006058+4*9))=0xf4df1409;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00006058+4*10))=0x03020100;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00006058+4*11))=0x07060504;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00006058+4*12))=0x0b0a0908;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00006058+4*13))=0x0f0e0d0c;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00006090))=0x010b0805;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00006090+4*1))=0x000001e1;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00006090+4*2))=0x0d060040;
*((unsigned int *)((unsigned long)cd->context_ptr+0x0000609c))=0xacab4976;
*((unsigned int *)((unsigned long)cd->context_ptr+0x0000609c+4*1))=0x46b21981;
*((unsigned int *)((unsigned long)cd->context_ptr+0x0000609c+4*2))=0x9b8ee9ce;
*((unsigned int *)((unsigned long)cd->context_ptr+0x0000609c+4*3))=0x7d19e912;
*((unsigned int *)((unsigned long)cd->context_ptr+0x0000609c+4*4))=0x9bcb8650;
*((unsigned int *)((unsigned long)cd->context_ptr+0x0000609c+4*5))=0xee197250;
*((unsigned int *)((unsigned long)cd->context_ptr+0x0000609c+4*6))=0x3a11db95;
*((unsigned int *)((unsigned long)cd->context_ptr+0x0000609c+4*7))=0xb2787691;
*((unsigned int *)((unsigned long)cd->context_ptr+0x0000609c+4*8))=0xb8d6be73;
*((unsigned int *)((unsigned long)cd->context_ptr+0x0000609c+4*9))=0x3b74c1e3;
*((unsigned int *)((unsigned long)cd->context_ptr+0x0000609c+4*10))=0x9ee61671;
*((unsigned int *)((unsigned long)cd->context_ptr+0x0000609c+4*11))=0x16952222;
*((unsigned int *)((unsigned long)cd->context_ptr+0x0000609c+4*12))=0xa1caf13f;
*((unsigned int *)((unsigned long)cd->context_ptr+0x0000609c+4*13))=0x09ac1f68;
*((unsigned int *)((unsigned long)cd->context_ptr+0x0000609c+4*14))=0x30ca0e12;
*((unsigned int *)((unsigned long)cd->context_ptr+0x0000609c+4*15))=0xa7e18675;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00003000))=0x04c00040;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00003000+4*1))=0x000060dc;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00003000+4*2))=0x77777777;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00003000+4*3))=0x77777777;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00003000+4*4))=0x77777777;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00003000+4*5))=0x77777777;
writel(0x00000018&0xffffffff,cd->ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,cd->ivp_cae_base_addr+0x00000028);
while(1){
if((readl(cd->ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(cd->ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,cd->ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)cd->context_ptr+0x00000000))=0x03c00040;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00000000+4*1))=0x0000609c;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00000000+4*2))=0x00006090;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00000000+4*3))=0x02220040;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00000000+4*4))=0x002d4ba5;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00000000+4*5))=0x00006000+(unsigned long)cd->context_ptr;
}

static void core_dec_start(core_desc *cd)
{
writel(0x00000018&0xffffffff,cd->ivp_cae_base_addr+0x0000002c);
writel(0x00000006&0xffffffff,cd->ivp_cae_base_addr+0x00000828);
}

static void core_dec_finish(core_desc *cd)
{
while(1){
if((readl(cd->ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(cd->ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,cd->ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)cd->context_ptr+0x000060dc,"\x6b\xc1\xbe\xe2\x2e\x40\x9f\x96\xe9\x3d\x7e\x11\x73\x93\x17\x2a\xae\x2d\x8a\x57\x1e\x03\xac\x9c\x9e\xb7\x6f\xac\x45\xaf\x8e\x51\x30\xc8\x1c\x46\xa3\x5c\xe4\x11\xe5\xfb\xc1\x19\x1a\x0a\x52\xef\xf6\x9f\x24\x45\xdf\x4f\x9b\x17\xad\x2b\x41\x7b\xe6\x6c\x37\x10",64)) {
if (cd->ivp_cae_base_addr == ITCS_C_CAE0_BASE)
printf("core 0, strip: 6bc1bee22e409f96, Pass\n");
else
printf("core 1, strip: 6bc1bee22e409f96, Pass\n");
} else {
if (cd->ivp_cae_base_addr == ITCS_C_CAE0_BASE)
printf("core 0, strip: 6bc1bee22e409f96, Failed\n");
else
printf("core 1, strip: 6bc1bee22e409f96, Failed\n");
}
}

static void core_prepare(core_desc *cd)
{
if(!cd->context_ptr)
printf("cd->context_ptr malloc failed!\n");
#if defined(CONFIG_COMPILE_FPGA) || defined(CONFIG_COMPILE_ASIC)
memset(cd->context_ptr,0,64*1024);
#endif
writel(0xa7050f08&0xffffffff,cd->ivp_cae_base_addr+0x0000f000);
writel(0x8000c807&0xffffffff,cd->ivp_cae_base_addr+0x0000f400);
writel(0x00007500&0xffffffff,cd->ivp_cae_base_addr+0x00010100);
writel(0x0000f800&0xffffffff,cd->ivp_cae_base_addr+0x00010000);
writel(0x00000087&0xffffffff,cd->ivp_cae_base_addr+0x00011c00);
writel(0x00410000&0xffffffff,cd->ivp_cae_base_addr+0x00011000);
writel(0x00000225&0xffffffff,cd->ivp_cae_base_addr+0x00011008);
writel(0x80000000&0xffffffff,cd->ivp_cae_base_addr+0x0000f200);
writel(0x80000000&0xffffffff,cd->ivp_cae_base_addr+0x0000f600);
readl(cd->ivp_cae_base_addr+0x0000f200);
writel(0x40000000&0xffffffff,cd->ivp_cae_base_addr+0x0000f200);
readl(cd->ivp_cae_base_addr+0x0000f600);
writel(0x40000000&0xffffffff,cd->ivp_cae_base_addr+0x0000f600);
writel(((unsigned long)cd->context_ptr+0x00000000)&0xffffffffffffffff,cd->ivp_cae_base_addr+0x00000008);
writel((((unsigned long)cd->context_ptr+0x00000000)>>32)&(0xffffffffffffffff>>32),cd->ivp_cae_base_addr+0x00000008+0x4);
writel(((unsigned long)cd->context_ptr+0x00000000)&0xffffffffffffffff,cd->ivp_cae_base_addr+0x00000010);
writel((((unsigned long)cd->context_ptr+0x00000000)>>32)&(0xffffffffffffffff>>32),cd->ivp_cae_base_addr+0x00000010+0x4);
writel(0x00000000&0xffffffff,cd->ivp_cae_base_addr+0x00000020);
writel(0x80000000&0xffffffff,cd->ivp_cae_base_addr+0x0000002c);
writel(0x00000000&0xffffffff,cd->ivp_cae_base_addr+0x00000034);
writel(0x00000000&0xffffffff,cd->ivp_cae_base_addr+0x00000038);
writel(0x00001800&0xffffffff,cd->ivp_cae_base_addr+0x00000018);
writel(((unsigned long)cd->context_ptr+0x00000000)&0xffffffffffffffff,cd->ivp_cae_base_addr+0x00000000);
writel((((unsigned long)cd->context_ptr+0x00000000)>>32)&(0xffffffffffffffff>>32),cd->ivp_cae_base_addr+0x00000000+0x4);
writel(0x80000000&0xffffffff,cd->ivp_cae_base_addr+0x00000030);
writel(0x01000000&0xffffffff,cd->ivp_cae_base_addr+0x00000024);
writel(0x40060006&0xffffffff,cd->ivp_cae_base_addr+0x0000001c);
writel(0x0000003f&0xffffffff,cd->ivp_cae_base_addr+0x0000003c);
writel(0x00120012&0xffffffff,cd->ivp_cae_base_addr+0x00000020);
readl(cd->ivp_cae_base_addr+0x0000f010);
writel(0x0000000f&0xffffffff,cd->ivp_cae_base_addr+0x0000f010);
readl(cd->ivp_cae_base_addr+0x0000f200);
writel(0x40000001&0xffffffff,cd->ivp_cae_base_addr+0x0000f200);
writel(((unsigned long)cd->context_ptr+0x00000000)&0xffffffffffffffff,cd->ivp_cae_base_addr+0x00001008);
writel((((unsigned long)cd->context_ptr+0x00000000)>>32)&(0xffffffffffffffff>>32),cd->ivp_cae_base_addr+0x00001008+0x4);
writel(((unsigned long)cd->context_ptr+0x00000000)&0xffffffffffffffff,cd->ivp_cae_base_addr+0x00001010);
writel((((unsigned long)cd->context_ptr+0x00000000)>>32)&(0xffffffffffffffff>>32),cd->ivp_cae_base_addr+0x00001010+0x4);
writel(0x00000000&0xffffffff,cd->ivp_cae_base_addr+0x00001020);
writel(0x80000000&0xffffffff,cd->ivp_cae_base_addr+0x0000102c);
writel(0x00000000&0xffffffff,cd->ivp_cae_base_addr+0x00001034);
writel(0x00000000&0xffffffff,cd->ivp_cae_base_addr+0x00001038);
writel(0x00001800&0xffffffff,cd->ivp_cae_base_addr+0x00001018);
writel(((unsigned long)cd->context_ptr+0x00001800)&0xffffffffffffffff,cd->ivp_cae_base_addr+0x00001000);
writel((((unsigned long)cd->context_ptr+0x00001800)>>32)&(0xffffffffffffffff>>32),cd->ivp_cae_base_addr+0x00001000+0x4);
writel(0x80000000&0xffffffff,cd->ivp_cae_base_addr+0x00001030);
writel(0x01000000&0xffffffff,cd->ivp_cae_base_addr+0x00001024);
writel(0x40060006&0xffffffff,cd->ivp_cae_base_addr+0x0000101c);
writel(0x0000003f&0xffffffff,cd->ivp_cae_base_addr+0x0000103c);
writel(0x00120012&0xffffffff,cd->ivp_cae_base_addr+0x00001020);
readl(cd->ivp_cae_base_addr+0x0000f010);
writel(0x00000f0f&0xffffffff,cd->ivp_cae_base_addr+0x0000f010);
readl(cd->ivp_cae_base_addr+0x0000f200);
writel(0x40000003&0xffffffff,cd->ivp_cae_base_addr+0x0000f200);
writel(0x01000000&0xffffffff,cd->ivp_cae_base_addr+0x00000824);
writel(((unsigned long)cd->context_ptr+0x00000000)&0xffffffffffffffff,cd->ivp_cae_base_addr+0x00000808);
writel((((unsigned long)cd->context_ptr+0x00000000)>>32)&(0xffffffffffffffff>>32),cd->ivp_cae_base_addr+0x00000808+0x4);
writel(((unsigned long)cd->context_ptr+0x00003000)&0xffffffffffffffff,cd->ivp_cae_base_addr+0x00000800);
writel((((unsigned long)cd->context_ptr+0x00003000)>>32)&(0xffffffffffffffff>>32),cd->ivp_cae_base_addr+0x00000800+0x4);
writel(0x00001800&0xffffffff,cd->ivp_cae_base_addr+0x00000818);
writel(0x00060006&0xffffffff,cd->ivp_cae_base_addr+0x0000081c);
writel(0x00080018&0xffffffff,cd->ivp_cae_base_addr+0x00000820);
writel(0x80000000&0xffffffff,cd->ivp_cae_base_addr+0x0000082c);
writel(0x80000000&0xffffffff,cd->ivp_cae_base_addr+0x00000830);
writel(0x00000000&0xffffffff,cd->ivp_cae_base_addr+0x00000834);
writel(0x00000000&0xffffffff,cd->ivp_cae_base_addr+0x00000838);
writel(0x00000000&0xffffffff,cd->ivp_cae_base_addr+0x00000828);
writel(0x000000ff&0xffffffff,cd->ivp_cae_base_addr+0x0000083c);
readl(cd->ivp_cae_base_addr+0x0000f410);
writel(0x0000000f&0xffffffff,cd->ivp_cae_base_addr+0x0000f410);
readl(cd->ivp_cae_base_addr+0x0000f600);
writel(0x40000001&0xffffffff,cd->ivp_cae_base_addr+0x0000f600);
writel(0x01000000&0xffffffff,cd->ivp_cae_base_addr+0x00001824);
writel(((unsigned long)cd->context_ptr+0x00000000)&0xffffffffffffffff,cd->ivp_cae_base_addr+0x00001808);
writel((((unsigned long)cd->context_ptr+0x00000000)>>32)&(0xffffffffffffffff>>32),cd->ivp_cae_base_addr+0x00001808+0x4);
writel(((unsigned long)cd->context_ptr+0x00004800)&0xffffffffffffffff,cd->ivp_cae_base_addr+0x00001800);
writel((((unsigned long)cd->context_ptr+0x00004800)>>32)&(0xffffffffffffffff>>32),cd->ivp_cae_base_addr+0x00001800+0x4);
writel(0x00001800&0xffffffff,cd->ivp_cae_base_addr+0x00001818);
writel(0x00060006&0xffffffff,cd->ivp_cae_base_addr+0x0000181c);
writel(0x00080018&0xffffffff,cd->ivp_cae_base_addr+0x00001820);
writel(0x80000000&0xffffffff,cd->ivp_cae_base_addr+0x0000182c);
writel(0x80000000&0xffffffff,cd->ivp_cae_base_addr+0x00001830);
writel(0x00000000&0xffffffff,cd->ivp_cae_base_addr+0x00001834);
writel(0x00000000&0xffffffff,cd->ivp_cae_base_addr+0x00001838);
writel(0x00000000&0xffffffff,cd->ivp_cae_base_addr+0x00001828);
writel(0x000000ff&0xffffffff,cd->ivp_cae_base_addr+0x0000183c);
readl(cd->ivp_cae_base_addr+0x0000f410);
writel(0x00000f00&0xffffffff,cd->ivp_cae_base_addr+0x0000f410);
readl(cd->ivp_cae_base_addr+0x0000f600);
writel(0x40000003&0xffffffff,cd->ivp_cae_base_addr+0x0000f600);
*((unsigned int *)((unsigned long)cd->context_ptr+0x00006000))=0x010b0804;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00006000+4*1))=0x000001e1;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00006000+4*2))=0x16157e2b;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00006000+4*3))=0xa6d2ae28;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00006000+4*4))=0x8815f7ab;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00006000+4*5))=0x3c4fcf09;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00006000+4*6))=0x03020100;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00006000+4*7))=0x07060504;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00006000+4*8))=0x0b0a0908;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00006000+4*9))=0x0f0e0d0c;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00006028))=0x010d0a04;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00006028+4*1))=0x000001e1;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00006028+4*2))=0xf7b0738e;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00006028+4*3))=0x52640eda;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00006028+4*4))=0x2bf310c8;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00006028+4*5))=0xe5799080;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00006028+4*6))=0xd2eaf862;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00006028+4*7))=0x7b6b2c52;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00006028+4*8))=0x03020100;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00006028+4*9))=0x07060504;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00006028+4*10))=0x0b0a0908;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00006028+4*11))=0x0f0e0d0c;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00006058))=0x010f0c04;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00006058+4*1))=0x000001e1;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00006058+4*2))=0x10eb3d60;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00006058+4*3))=0xbe71ca15;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00006058+4*4))=0xf0ae732b;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00006058+4*5))=0x81777d85;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00006058+4*6))=0x072c351f;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00006058+4*7))=0xd708613b;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00006058+4*8))=0xa310982d;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00006058+4*9))=0xf4df1409;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00006058+4*10))=0x03020100;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00006058+4*11))=0x07060504;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00006058+4*12))=0x0b0a0908;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00006058+4*13))=0x0f0e0d0c;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00006090))=0x010b0804;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00006090+4*1))=0x000001e1;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00006090+4*2))=0x0d060040;
*((unsigned int *)((unsigned long)cd->context_ptr+0x0000609c))=0xe2bec16b;
*((unsigned int *)((unsigned long)cd->context_ptr+0x0000609c+4*1))=0x969f402e;
*((unsigned int *)((unsigned long)cd->context_ptr+0x0000609c+4*2))=0x117e3de9;
*((unsigned int *)((unsigned long)cd->context_ptr+0x0000609c+4*3))=0x2a179373;
*((unsigned int *)((unsigned long)cd->context_ptr+0x0000609c+4*4))=0x578a2dae;
*((unsigned int *)((unsigned long)cd->context_ptr+0x0000609c+4*5))=0x9cac031e;
*((unsigned int *)((unsigned long)cd->context_ptr+0x0000609c+4*6))=0xac6fb79e;
*((unsigned int *)((unsigned long)cd->context_ptr+0x0000609c+4*7))=0x518eaf45;
*((unsigned int *)((unsigned long)cd->context_ptr+0x0000609c+4*8))=0x461cc830;
*((unsigned int *)((unsigned long)cd->context_ptr+0x0000609c+4*9))=0x11e45ca3;
*((unsigned int *)((unsigned long)cd->context_ptr+0x0000609c+4*10))=0x19c1fbe5;
*((unsigned int *)((unsigned long)cd->context_ptr+0x0000609c+4*11))=0xef520a1a;
*((unsigned int *)((unsigned long)cd->context_ptr+0x0000609c+4*12))=0x45249ff6;
*((unsigned int *)((unsigned long)cd->context_ptr+0x0000609c+4*13))=0x179b4fdf;
*((unsigned int *)((unsigned long)cd->context_ptr+0x0000609c+4*14))=0x7b412bad;
*((unsigned int *)((unsigned long)cd->context_ptr+0x0000609c+4*15))=0x10376ce6;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00003000))=0x04c00040;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00003000+4*1))=0x000060dc;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00003000+4*2))=0x77777777;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00003000+4*3))=0x77777777;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00003000+4*4))=0x77777777;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00003000+4*5))=0x77777777;
writel(0x00000018&0xffffffff,cd->ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,cd->ivp_cae_base_addr+0x00000028);
while(1){
if((readl(cd->ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(cd->ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,cd->ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)cd->context_ptr+0x00000000))=0x03c00040;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00000000+4*1))=0x0000609c;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00000000+4*2))=0x00006090;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00000000+4*3))=0x02220040;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00000000+4*4))=0x002d4ba5;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00000000+4*5))=0x00006000+(unsigned long)cd->context_ptr;
}

static void core_start(core_desc *cd)
{
writel(0x00000018&0xffffffff,cd->ivp_cae_base_addr+0x0000002c);
writel(0x00000006&0xffffffff,cd->ivp_cae_base_addr+0x00000828);
}

static void core_finish(core_desc *cd)
{
while(1){
if((readl(cd->ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(cd->ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,cd->ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)cd->context_ptr+0x000060dc,"\x76\x49\xab\xac\x81\x19\xb2\x46\xce\xe9\x8e\x9b\x12\xe9\x19\x7d\x50\x86\xcb\x9b\x50\x72\x19\xee\x95\xdb\x11\x3a\x91\x76\x78\xb2\x73\xbe\xd6\xb8\xe3\xc1\x74\x3b\x71\x16\xe6\x9e\x22\x22\x95\x16\x3f\xf1\xca\xa1\x68\x1f\xac\x09\x12\x0e\xca\x30\x75\x86\xe1\xa7",64)) {
if (cd->ivp_cae_base_addr == ITCS_C_CAE0_BASE)
printf("core 0, strip: 7649abac8119b246, Pass\n");
else
printf("core 1, strip: 7649abac8119b246, Pass\n");
} else {
if (cd->ivp_cae_base_addr == ITCS_C_CAE0_BASE)
printf("core 0, strip: 7649abac8119b246, Failed\n");
else
printf("core 1, strip: 7649abac8119b246, Failed\n");
}
}

void cae_ivp_speed_test(int id, char *name, int enc)
{
	core_desc core_0 = { .context_ptr = (unsigned int *)0x14000000,
			     .ivp_cae_base_addr = ITCS_C_CAE0_BASE };
	core_desc core_1 = { .context_ptr = (unsigned int *)(0x14000000 + 0x100000),
			     .ivp_cae_base_addr = ITCS_C_CAE1_BASE };

	if (enc) {
		if (!strcmp(name, "dual_core")) {
			printf("dual core encryption is preparing\n");
#if defined(CONFIG_COMPILE_FPGA) || defined(CONFIG_COMPILE_ASIC)
			core_prepare(&core_0);
			core_prepare(&core_1);

			core_start(&core_0);
			core_start(&core_1);

			core_finish(&core_0);
			core_finish(&core_1);
#elif defined(CONFIG_COMPILE_RTL)
			dual_core_test_for_rtl(enc);
#endif
		} else if (!strcmp(name, "single_core")) {
			printf("core %d encryption is preparing\n", id);
			if (id == 0) {
				core_prepare(&core_0);
				core_start(&core_0);
				core_finish(&core_0);
			} else {
				core_prepare(&core_1);
				core_start(&core_1);
				core_finish(&core_1);
			}
		} else if (!strcmp(name, "dual_core_aes_128_gcm")) {
			printf("dual core aes-128-gcm encryption is preparing\n");
			aes_128_gcm_dual_core(enc);
		}
	} else {
		if (!strcmp(name, "dual_core")) {
			printf("dual core decryption is preparing\n");
#if defined(CONFIG_COMPILE_FPGA) || defined(CONFIG_COMPILE_ASIC)
			core_dec_prepare(&core_0);
			core_dec_prepare(&core_1);

			core_dec_start(&core_0);
			core_dec_start(&core_1);

			core_dec_finish(&core_0);
			core_dec_finish(&core_1);
#elif defined(CONFIG_COMPILE_RTL)
			dual_core_test_for_rtl(enc);
#endif
		} else if (!strcmp(name, "single_core")) {
			printf("core %d decryption is preparing\n", id);
			if (id == 0) {
				core_dec_prepare(&core_0);
				core_dec_start(&core_0);
				core_dec_finish(&core_0);
			} else {
				core_dec_prepare(&core_1);
				core_dec_start(&core_1);
				core_dec_finish(&core_1);
			}
		} else if (!strcmp(name, "dual_core_aes_128_gcm")) {
			printf("dual core aes-128-gcm decryption is preparing\n");
			aes_128_gcm_dual_core(enc);
		}
	}
}

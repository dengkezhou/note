#include <common.h>
#include <malloc.h>

extern volatile unsigned int ivp_cae_base_addr;

void test_macsec_in_default(void)
{
unsigned int *context_ptr=(unsigned int *)0x14000000;
printf("test_macsec_in_default\n");
if(!context_ptr)
printf("context_ptr malloc failed!\n");
#if defined(CONFIG_COMPILE_FPGA) || defined(CONFIG_COMPILE_ASIC)
memset(context_ptr,0,64*1024);
#endif
writel(0xa7050f08&0xffffffff,ivp_cae_base_addr+0x0000f000);
writel(0x8000c807&0xffffffff,ivp_cae_base_addr+0x0000f400);
writel(0x00007500&0xffffffff,ivp_cae_base_addr+0x00010100);
writel(0x0000f800&0xffffffff,ivp_cae_base_addr+0x00010000);
writel(0x00000087&0xffffffff,ivp_cae_base_addr+0x00011c00);
writel(0x00410000&0xffffffff,ivp_cae_base_addr+0x00011000);
writel(0x00000225&0xffffffff,ivp_cae_base_addr+0x00011008);
writel(0x80000000&0xffffffff,ivp_cae_base_addr+0x0000f200);
writel(0x80000000&0xffffffff,ivp_cae_base_addr+0x0000f600);
readl(ivp_cae_base_addr+0x0000f200);
writel(0x40000000&0xffffffff,ivp_cae_base_addr+0x0000f200);
readl(ivp_cae_base_addr+0x0000f600);
writel(0x40000000&0xffffffff,ivp_cae_base_addr+0x0000f600);
writel(((unsigned long)context_ptr+0x00000000)&0xffffffffffffffff,ivp_cae_base_addr+0x00000008);
writel((((unsigned long)context_ptr+0x00000000)>>32)&(0xffffffffffffffff>>32),ivp_cae_base_addr+0x00000008+0x4);
writel(((unsigned long)context_ptr+0x00000000)&0xffffffffffffffff,ivp_cae_base_addr+0x00000010);
writel((((unsigned long)context_ptr+0x00000000)>>32)&(0xffffffffffffffff>>32),ivp_cae_base_addr+0x00000010+0x4);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00000020);
writel(0x80000000&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00000034);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00000038);
writel(0x00000600&0xffffffff,ivp_cae_base_addr+0x00000018);
writel(((unsigned long)context_ptr+0x00000000)&0xffffffffffffffff,ivp_cae_base_addr+0x00000000);
writel((((unsigned long)context_ptr+0x00000000)>>32)&(0xffffffffffffffff>>32),ivp_cae_base_addr+0x00000000+0x4);
writel(0x80000000&0xffffffff,ivp_cae_base_addr+0x00000030);
writel(0x01000000&0xffffffff,ivp_cae_base_addr+0x00000024);
writel(0x40060006&0xffffffff,ivp_cae_base_addr+0x0000001c);
writel(0x0000003f&0xffffffff,ivp_cae_base_addr+0x0000003c);
writel(0x00120012&0xffffffff,ivp_cae_base_addr+0x00000020);
readl(ivp_cae_base_addr+0x0000f010);
writel(0x0000000f&0xffffffff,ivp_cae_base_addr+0x0000f010);
readl(ivp_cae_base_addr+0x0000f200);
writel(0x40000001&0xffffffff,ivp_cae_base_addr+0x0000f200);
writel(0x01000000&0xffffffff,ivp_cae_base_addr+0x00000824);
writel(((unsigned long)context_ptr+0x00000000)&0xffffffffffffffff,ivp_cae_base_addr+0x00000808);
writel((((unsigned long)context_ptr+0x00000000)>>32)&(0xffffffffffffffff>>32),ivp_cae_base_addr+0x00000808+0x4);
writel(((unsigned long)context_ptr+0x00000600)&0xffffffffffffffff,ivp_cae_base_addr+0x00000800);
writel((((unsigned long)context_ptr+0x00000600)>>32)&(0xffffffffffffffff>>32),ivp_cae_base_addr+0x00000800+0x4);
writel(0x00000600&0xffffffff,ivp_cae_base_addr+0x00000818);
writel(0x00060006&0xffffffff,ivp_cae_base_addr+0x0000081c);
writel(0x00080018&0xffffffff,ivp_cae_base_addr+0x00000820);
writel(0x80000000&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x80000000&0xffffffff,ivp_cae_base_addr+0x00000830);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00000834);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00000838);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00000828);
writel(0x000000ff&0xffffffff,ivp_cae_base_addr+0x0000083c);
readl(ivp_cae_base_addr+0x0000f410);
writel(0x0000000f&0xffffffff,ivp_cae_base_addr+0x0000f410);
readl(ivp_cae_base_addr+0x0000f600);
writel(0x40000001&0xffffffff,ivp_cae_base_addr+0x0000f600);
*((unsigned int *)((unsigned long)context_ptr+0x00000c00))=0xd24b0f0f;
*((unsigned int *)((unsigned long)context_ptr+0x00000c00+4*1))=0x4a820462;
*((unsigned int *)((unsigned long)context_ptr+0x00000c00+4*2))=0x268b6032;
*((unsigned int *)((unsigned long)context_ptr+0x00000c00+4*3))=0x6725fbfd;
*((unsigned int *)((unsigned long)context_ptr+0x00000c00+4*4))=0xea7ee0ae;
*((unsigned int *)((unsigned long)context_ptr+0x00000c00+4*5))=0xab7f7f52;
*((unsigned int *)((unsigned long)context_ptr+0x00000c00+4*6))=0x13b75384;
*((unsigned int *)((unsigned long)context_ptr+0x00000c00+4*7))=0xfe5a8063;
*((unsigned int *)((unsigned long)context_ptr+0x00000c00+4*8))=0x3f753964;
*((unsigned int *)((unsigned long)context_ptr+0x00000c00+4*9))=0x810879d4;
*((unsigned int *)((unsigned long)context_ptr+0x00000c00+4*10))=0x00004321;
*((unsigned int *)((unsigned long)context_ptr+0x00000c00+4*11))=0xffe00000;
*((unsigned int *)((unsigned long)context_ptr+0x00000c00+4*12))=0xffffffff;
*((unsigned int *)((unsigned long)context_ptr+0x00000c00+4*13))=0xffffffff;
*((unsigned int *)((unsigned long)context_ptr+0x00000c00+4*14))=0xffffffff;
*((unsigned int *)((unsigned long)context_ptr+0x00000c00+4*15))=0x35651ead;
*((unsigned int *)((unsigned long)context_ptr+0x00000c00+4*16))=0x2537f20a;
*((unsigned int *)((unsigned long)context_ptr+0x00000c44))=0xd24b0f0f;
*((unsigned int *)((unsigned long)context_ptr+0x00000c44+4*1))=0x4a820462;
*((unsigned int *)((unsigned long)context_ptr+0x00000c44+4*2))=0x0e2f153b;
*((unsigned int *)((unsigned long)context_ptr+0x00000c44+4*3))=0x9c9c2ca3;
*((unsigned int *)((unsigned long)context_ptr+0x00000c44+4*4))=0xe04883b4;
*((unsigned int *)((unsigned long)context_ptr+0x00000c44+4*5))=0x84a1755a;
*((unsigned int *)((unsigned long)context_ptr+0x00000c44+4*6))=0x62e76ae2;
*((unsigned int *)((unsigned long)context_ptr+0x00000c44+4*7))=0x0266f22b;
*((unsigned int *)((unsigned long)context_ptr+0x00000c44+4*8))=0xfb56a314;
*((unsigned int *)((unsigned long)context_ptr+0x00000c44+4*9))=0x9a7579d7;
*((unsigned int *)((unsigned long)context_ptr+0x00000c44+4*10))=0x00008765;
*((unsigned int *)((unsigned long)context_ptr+0x00000c44+4*11))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x00000c44+4*12))=0xfffffe00;
*((unsigned int *)((unsigned long)context_ptr+0x00000c44+4*13))=0xffffffff;
*((unsigned int *)((unsigned long)context_ptr+0x00000c44+4*14))=0xffffffff;
*((unsigned int *)((unsigned long)context_ptr+0x00000c44+4*15))=0x96f03238;
*((unsigned int *)((unsigned long)context_ptr+0x00000c44+4*16))=0x0000630c;
*((unsigned int *)((unsigned long)context_ptr+0x00000c88))=0x0300000c;
*((unsigned int *)((unsigned long)context_ptr+0x00000c88+4*1))=0x02000004;
*((unsigned int *)((unsigned long)context_ptr+0x00000c88+4*2))=0x42980004;
*((unsigned int *)((unsigned long)context_ptr+0x00000c88+4*3))=0x4aa00008;
*((unsigned int *)((unsigned long)context_ptr+0x00000c88+4*4))=0x90996004;
*((unsigned int *)((unsigned long)context_ptr+0x00000c88+4*5))=0xa082000c;
*((unsigned int *)((unsigned long)context_ptr+0x00000c88+4*6))=0x25000010;
*((unsigned int *)((unsigned long)context_ptr+0x00000c88+4*7))=0x0f02000c;
*((unsigned int *)((unsigned long)context_ptr+0x00000c88+4*8))=0x40e60010;
*((unsigned int *)((unsigned long)context_ptr+0x00000c88+4*9))=0xd8070010;
*((unsigned int *)((unsigned long)context_ptr+0x00000c88+4*10))=0xe12e380a;
*((unsigned int *)((unsigned long)context_ptr+0x00000cb4))=0x4fbcac33;
*((unsigned int *)((unsigned long)context_ptr+0x00000cb4+4*1))=0xb65841dc;
*((unsigned int *)((unsigned long)context_ptr+0x00000cb4+4*2))=0x7512ef0b;
*((unsigned int *)((unsigned long)context_ptr+0x00000cb4+4*3))=0x0c2ce588;
*((unsigned int *)((unsigned long)context_ptr+0x00000cb4+4*4))=0x21430000;
*((unsigned int *)((unsigned long)context_ptr+0x00000cb4+4*5))=0x35651ead;
*((unsigned int *)((unsigned long)context_ptr+0x00000cb4+4*6))=0x2537f20a;
*((unsigned int *)((unsigned long)context_ptr+0x00000cb4+4*7))=0x8c3b321b;
*((unsigned int *)((unsigned long)context_ptr+0x00000cb4+4*8))=0xa79885a5;
*((unsigned int *)((unsigned long)context_ptr+0x00000cb4+4*9))=0x4b2cf08e;
*((unsigned int *)((unsigned long)context_ptr+0x00000cb4+4*10))=0x7c631e9d;
*((unsigned int *)((unsigned long)context_ptr+0x00000cb4+4*11))=0x9b4032c1;
*((unsigned int *)((unsigned long)context_ptr+0x00000cb4+4*12))=0xde06f4ba;
*((unsigned int *)((unsigned long)context_ptr+0x00000cb4+4*13))=0xb6c80033;
*((unsigned int *)((unsigned long)context_ptr+0x00000600))=0x04c00018;
*((unsigned int *)((unsigned long)context_ptr+0x00000600+4*1))=0x00000cec;
*((unsigned int *)((unsigned long)context_ptr+0x00000600+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00000600+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00000600+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00000600+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x0000017a&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000000))=0x0bc00038;
*((unsigned int *)((unsigned long)context_ptr+0x00000000+4*1))=0x00000cb4;
*((unsigned int *)((unsigned long)context_ptr+0x00000000+4*2))=0x00000c88;
*((unsigned int *)((unsigned long)context_ptr+0x00000000+4*3))=0x00220038;
*((unsigned int *)((unsigned long)context_ptr+0x00000000+4*4))=0x00441030;
*((unsigned int *)((unsigned long)context_ptr+0x00000000+4*5))=0x00000c00+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x00000d04))=0x0300000c;
*((unsigned int *)((unsigned long)context_ptr+0x00000d04+4*1))=0x02000004;
*((unsigned int *)((unsigned long)context_ptr+0x00000d04+4*2))=0x40980004;
*((unsigned int *)((unsigned long)context_ptr+0x00000d04+4*3))=0x20000000;
*((unsigned int *)((unsigned long)context_ptr+0x00000d04+4*4))=0x9a996004;
*((unsigned int *)((unsigned long)context_ptr+0x00000d04+4*5))=0xa082000c;
*((unsigned int *)((unsigned long)context_ptr+0x00000d04+4*6))=0x25000010;
*((unsigned int *)((unsigned long)context_ptr+0x00000d04+4*7))=0x0f02000c;
*((unsigned int *)((unsigned long)context_ptr+0x00000d04+4*8))=0x40e60010;
*((unsigned int *)((unsigned long)context_ptr+0x00000d04+4*9))=0xd8070010;
*((unsigned int *)((unsigned long)context_ptr+0x00000d04+4*10))=0xe12e380a;
*((unsigned int *)((unsigned long)context_ptr+0x00000d30))=0xc81e3b42;
*((unsigned int *)((unsigned long)context_ptr+0x00000d30+4*1))=0x3238bb19;
*((unsigned int *)((unsigned long)context_ptr+0x00000d30+4*2))=0x630c96f0;
*((unsigned int *)((unsigned long)context_ptr+0x00000d30+4*3))=0x0c5ce588;
*((unsigned int *)((unsigned long)context_ptr+0x00000d30+4*4))=0x65870000;
*((unsigned int *)((unsigned long)context_ptr+0x00000d30+4*5))=0xb18031e5;
*((unsigned int *)((unsigned long)context_ptr+0x00000d30+4*6))=0xbc76c9fc;
*((unsigned int *)((unsigned long)context_ptr+0x00000d30+4*7))=0xd5b86bd1;
*((unsigned int *)((unsigned long)context_ptr+0x00000d30+4*8))=0xc27e7230;
*((unsigned int *)((unsigned long)context_ptr+0x00000d30+4*9))=0x388622a0;
*((unsigned int *)((unsigned long)context_ptr+0x00000d30+4*10))=0xf1fb29c2;
*((unsigned int *)((unsigned long)context_ptr+0x00000d30+4*11))=0xb2831839;
*((unsigned int *)((unsigned long)context_ptr+0x00000618))=0x04c00018;
*((unsigned int *)((unsigned long)context_ptr+0x00000618+4*1))=0x00000d60;
*((unsigned int *)((unsigned long)context_ptr+0x00000618+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00000618+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00000618+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00000618+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x0000017a&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000018))=0x0bc00030;
*((unsigned int *)((unsigned long)context_ptr+0x00000018+4*1))=0x00000d30;
*((unsigned int *)((unsigned long)context_ptr+0x00000018+4*2))=0x00000d04;
*((unsigned int *)((unsigned long)context_ptr+0x00000018+4*3))=0x00220030;
*((unsigned int *)((unsigned long)context_ptr+0x00000018+4*4))=0x006d4ba6;
*((unsigned int *)((unsigned long)context_ptr+0x00000018+4*5))=0x00000c44+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x00000d78))=0x0300000c;
*((unsigned int *)((unsigned long)context_ptr+0x00000d78+4*1))=0x02000004;
*((unsigned int *)((unsigned long)context_ptr+0x00000d78+4*2))=0x42980004;
*((unsigned int *)((unsigned long)context_ptr+0x00000d78+4*3))=0x4aa00008;
*((unsigned int *)((unsigned long)context_ptr+0x00000d78+4*4))=0x90996004;
*((unsigned int *)((unsigned long)context_ptr+0x00000d78+4*5))=0xa082000c;
*((unsigned int *)((unsigned long)context_ptr+0x00000d78+4*6))=0x25000010;
*((unsigned int *)((unsigned long)context_ptr+0x00000d78+4*7))=0x0f02000d;
*((unsigned int *)((unsigned long)context_ptr+0x00000d78+4*8))=0x40e60010;
*((unsigned int *)((unsigned long)context_ptr+0x00000d78+4*9))=0xd8070010;
*((unsigned int *)((unsigned long)context_ptr+0x00000d78+4*10))=0xe12e380a;
*((unsigned int *)((unsigned long)context_ptr+0x00000da4))=0xc2d0bb36;
*((unsigned int *)((unsigned long)context_ptr+0x00000da4+4*1))=0xe6a1975a;
*((unsigned int *)((unsigned long)context_ptr+0x00000da4+4*2))=0x5b86d51b;
*((unsigned int *)((unsigned long)context_ptr+0x00000da4+4*3))=0x0d2ce588;
*((unsigned int *)((unsigned long)context_ptr+0x00000da4+4*4))=0x22430000;
*((unsigned int *)((unsigned long)context_ptr+0x00000da4+4*5))=0x35651ead;
*((unsigned int *)((unsigned long)context_ptr+0x00000da4+4*6))=0x2537f20a;
*((unsigned int *)((unsigned long)context_ptr+0x00000da4+4*7))=0xcc016ec3;
*((unsigned int *)((unsigned long)context_ptr+0x00000da4+4*8))=0x241f0498;
*((unsigned int *)((unsigned long)context_ptr+0x00000da4+4*9))=0x3694c6ac;
*((unsigned int *)((unsigned long)context_ptr+0x00000da4+4*10))=0xca281935;
*((unsigned int *)((unsigned long)context_ptr+0x00000da4+4*11))=0x1f195e8b;
*((unsigned int *)((unsigned long)context_ptr+0x00000da4+4*12))=0x02c4dbef;
*((unsigned int *)((unsigned long)context_ptr+0x00000da4+4*13))=0x7a33c808;
*((unsigned int *)((unsigned long)context_ptr+0x00000da4+4*14))=0x0000007d;
*((unsigned int *)((unsigned long)context_ptr+0x00000630))=0x04c00019;
*((unsigned int *)((unsigned long)context_ptr+0x00000630+4*1))=0x00000de0;
*((unsigned int *)((unsigned long)context_ptr+0x00000630+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00000630+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00000630+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00000630+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x0000017a&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000030))=0x0bc00039;
*((unsigned int *)((unsigned long)context_ptr+0x00000030+4*1))=0x00000da4;
*((unsigned int *)((unsigned long)context_ptr+0x00000030+4*2))=0x00000d78;
*((unsigned int *)((unsigned long)context_ptr+0x00000030+4*3))=0x00220039;
*((unsigned int *)((unsigned long)context_ptr+0x00000030+4*4))=0x00b41785;
*((unsigned int *)((unsigned long)context_ptr+0x00000030+4*5))=0x00000c00+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x00000dfc))=0x0300000c;
*((unsigned int *)((unsigned long)context_ptr+0x00000dfc+4*1))=0x02000004;
*((unsigned int *)((unsigned long)context_ptr+0x00000dfc+4*2))=0x40980004;
*((unsigned int *)((unsigned long)context_ptr+0x00000dfc+4*3))=0x20000000;
*((unsigned int *)((unsigned long)context_ptr+0x00000dfc+4*4))=0x9a996004;
*((unsigned int *)((unsigned long)context_ptr+0x00000dfc+4*5))=0xa082000c;
*((unsigned int *)((unsigned long)context_ptr+0x00000dfc+4*6))=0x25000010;
*((unsigned int *)((unsigned long)context_ptr+0x00000dfc+4*7))=0x0f02000d;
*((unsigned int *)((unsigned long)context_ptr+0x00000dfc+4*8))=0x40e60010;
*((unsigned int *)((unsigned long)context_ptr+0x00000dfc+4*9))=0xd8070010;
*((unsigned int *)((unsigned long)context_ptr+0x00000dfc+4*10))=0xe12e380a;
*((unsigned int *)((unsigned long)context_ptr+0x00000e28))=0x11a7390b;
*((unsigned int *)((unsigned long)context_ptr+0x00000e28+4*1))=0x3238f80f;
*((unsigned int *)((unsigned long)context_ptr+0x00000e28+4*2))=0x630c96f0;
*((unsigned int *)((unsigned long)context_ptr+0x00000e28+4*3))=0x0d5ce588;
*((unsigned int *)((unsigned long)context_ptr+0x00000e28+4*4))=0x66870000;
*((unsigned int *)((unsigned long)context_ptr+0x00000e28+4*5))=0x5f03c420;
*((unsigned int *)((unsigned long)context_ptr+0x00000e28+4*6))=0x45febd19;
*((unsigned int *)((unsigned long)context_ptr+0x00000e28+4*7))=0x415ff9a6;
*((unsigned int *)((unsigned long)context_ptr+0x00000e28+4*8))=0x056b4e79;
*((unsigned int *)((unsigned long)context_ptr+0x00000e28+4*9))=0x3745860a;
*((unsigned int *)((unsigned long)context_ptr+0x00000e28+4*10))=0xc8f9370c;
*((unsigned int *)((unsigned long)context_ptr+0x00000e28+4*11))=0x7d9b8ad8;
*((unsigned int *)((unsigned long)context_ptr+0x00000e28+4*12))=0x00000060;
*((unsigned int *)((unsigned long)context_ptr+0x00000648))=0x04c00019;
*((unsigned int *)((unsigned long)context_ptr+0x00000648+4*1))=0x00000e5c;
*((unsigned int *)((unsigned long)context_ptr+0x00000648+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00000648+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00000648+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00000648+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x0000017a&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000048))=0x0bc00031;
*((unsigned int *)((unsigned long)context_ptr+0x00000048+4*1))=0x00000e28;
*((unsigned int *)((unsigned long)context_ptr+0x00000048+4*2))=0x00000dfc;
*((unsigned int *)((unsigned long)context_ptr+0x00000048+4*3))=0x00220031;
*((unsigned int *)((unsigned long)context_ptr+0x00000048+4*4))=0x00c90ded;
*((unsigned int *)((unsigned long)context_ptr+0x00000048+4*5))=0x00000c44+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000006&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00000cec,"\x33\xac\xbc\x4f\xdc\x41\x58\xb6\x0b\xef\x12\x75\xeb\x70\xb9\x0c\xcf\xfa\x75\x1e\x14\x19\xc3\x69",24))
printf("strip: 33acbc4fdc4158b6, Pass\n");
else
printf("strip: 33acbc4fdc4158b6, Failed\n");
writel(0x0000000c&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00000d60,"\x42\x3b\x1e\xc8\x19\xbb\x38\x32\xf0\x96\x0c\x63\xbc\x5b\x3f\x48\xbc\xa8\xbd\x83\xdb\x1f\xa5\x1e",24))
printf("strip: 423b1ec819bb3832, Pass\n");
else
printf("strip: 423b1ec819bb3832, Failed\n");
writel(0x00000012&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00000de0,"\x36\xbb\xd0\xc2\x5a\x97\xa1\xe6\x1b\xd5\x86\x5b\x9a\xb4\x74\x03\x38\xa7\xa9\x7e\xf4\x7b\x50\xd9\x42\x00\x00\x00",25))
printf("strip: 36bbd0c25a97a1e6, Pass\n");
else
printf("strip: 36bbd0c25a97a1e6, Failed\n");
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00000e5c,"\x0b\x39\xa7\x11\x0f\xf8\x38\x32\xf0\x96\x0c\x63\x43\x88\x6c\xe4\x37\x6f\x5b\x2d\x54\xfc\xbf\x61\x68\x00\x00\x00",25))
printf("strip: 0b39a7110ff83832, Pass\n");
else
printf("strip: 0b39a7110ff83832, Failed\n");
}

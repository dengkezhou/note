#include <common.h>
#include <malloc.h>

extern volatile unsigned int ivp_cae_base_addr;

void test_hmac_sha1(void)
{
unsigned int *context_ptr=(unsigned int *)0x14000000;
printf("test_hmac_sha1\n");
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
writel(0x00001800&0xffffffff,ivp_cae_base_addr+0x00000018);
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
writel(((unsigned long)context_ptr+0x00000000)&0xffffffffffffffff,ivp_cae_base_addr+0x00001008);
writel((((unsigned long)context_ptr+0x00000000)>>32)&(0xffffffffffffffff>>32),ivp_cae_base_addr+0x00001008+0x4);
writel(((unsigned long)context_ptr+0x00000000)&0xffffffffffffffff,ivp_cae_base_addr+0x00001010);
writel((((unsigned long)context_ptr+0x00000000)>>32)&(0xffffffffffffffff>>32),ivp_cae_base_addr+0x00001010+0x4);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00001020);
writel(0x80000000&0xffffffff,ivp_cae_base_addr+0x0000102c);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00001034);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00001038);
writel(0x00001800&0xffffffff,ivp_cae_base_addr+0x00001018);
writel(((unsigned long)context_ptr+0x00001800)&0xffffffffffffffff,ivp_cae_base_addr+0x00001000);
writel((((unsigned long)context_ptr+0x00001800)>>32)&(0xffffffffffffffff>>32),ivp_cae_base_addr+0x00001000+0x4);
writel(0x80000000&0xffffffff,ivp_cae_base_addr+0x00001030);
writel(0x01000000&0xffffffff,ivp_cae_base_addr+0x00001024);
writel(0x40060006&0xffffffff,ivp_cae_base_addr+0x0000101c);
writel(0x0000003f&0xffffffff,ivp_cae_base_addr+0x0000103c);
writel(0x00120012&0xffffffff,ivp_cae_base_addr+0x00001020);
readl(ivp_cae_base_addr+0x0000f010);
writel(0x00000f0f&0xffffffff,ivp_cae_base_addr+0x0000f010);
readl(ivp_cae_base_addr+0x0000f200);
writel(0x40000003&0xffffffff,ivp_cae_base_addr+0x0000f200);
writel(0x01000000&0xffffffff,ivp_cae_base_addr+0x00000824);
writel(((unsigned long)context_ptr+0x00000000)&0xffffffffffffffff,ivp_cae_base_addr+0x00000808);
writel((((unsigned long)context_ptr+0x00000000)>>32)&(0xffffffffffffffff>>32),ivp_cae_base_addr+0x00000808+0x4);
writel(((unsigned long)context_ptr+0x00003000)&0xffffffffffffffff,ivp_cae_base_addr+0x00000800);
writel((((unsigned long)context_ptr+0x00003000)>>32)&(0xffffffffffffffff>>32),ivp_cae_base_addr+0x00000800+0x4);
writel(0x00001800&0xffffffff,ivp_cae_base_addr+0x00000818);
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
writel(0x01000000&0xffffffff,ivp_cae_base_addr+0x00001824);
writel(((unsigned long)context_ptr+0x00000000)&0xffffffffffffffff,ivp_cae_base_addr+0x00001808);
writel((((unsigned long)context_ptr+0x00000000)>>32)&(0xffffffffffffffff>>32),ivp_cae_base_addr+0x00001808+0x4);
writel(((unsigned long)context_ptr+0x00004800)&0xffffffffffffffff,ivp_cae_base_addr+0x00001800);
writel((((unsigned long)context_ptr+0x00004800)>>32)&(0xffffffffffffffff>>32),ivp_cae_base_addr+0x00001800+0x4);
writel(0x00001800&0xffffffff,ivp_cae_base_addr+0x00001818);
writel(0x00060006&0xffffffff,ivp_cae_base_addr+0x0000181c);
writel(0x00080018&0xffffffff,ivp_cae_base_addr+0x00001820);
writel(0x80000000&0xffffffff,ivp_cae_base_addr+0x0000182c);
writel(0x80000000&0xffffffff,ivp_cae_base_addr+0x00001830);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00001834);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00001838);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00001828);
writel(0x000000ff&0xffffffff,ivp_cae_base_addr+0x0000183c);
readl(ivp_cae_base_addr+0x0000f410);
writel(0x00000f00&0xffffffff,ivp_cae_base_addr+0x0000f410);
readl(ivp_cae_base_addr+0x0000f600);
writel(0x40000003&0xffffffff,ivp_cae_base_addr+0x0000f600);
*((unsigned int *)((unsigned long)context_ptr+0x00006000))=0x016a0a02;
*((unsigned int *)((unsigned long)context_ptr+0x00006000+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006000+4*2))=0x763ede44;
*((unsigned int *)((unsigned long)context_ptr+0x00006000+4*3))=0xdaa586bd;
*((unsigned int *)((unsigned long)context_ptr+0x00006000+4*4))=0xcf46a7d8;
*((unsigned int *)((unsigned long)context_ptr+0x00006000+4*5))=0x8be41514;
*((unsigned int *)((unsigned long)context_ptr+0x00006000+4*6))=0x24c519c2;
*((unsigned int *)((unsigned long)context_ptr+0x00006000+4*7))=0xb0414dfc;
*((unsigned int *)((unsigned long)context_ptr+0x00006000+4*8))=0x8050dc41;
*((unsigned int *)((unsigned long)context_ptr+0x00006000+4*9))=0x7795d433;
*((unsigned int *)((unsigned long)context_ptr+0x00006000+4*10))=0xecf61b9e;
*((unsigned int *)((unsigned long)context_ptr+0x00006000+4*11))=0x76921335;
*((unsigned int *)((unsigned long)context_ptr+0x00006030))=0x016a0a02;
*((unsigned int *)((unsigned long)context_ptr+0x00006030+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006030+4*2))=0x02020001;
*((unsigned int *)((unsigned long)context_ptr+0x00006030+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x00006040))=0x00000033;
*((unsigned int *)((unsigned long)context_ptr+0x00003000))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003000+4*1))=0x00006044;
*((unsigned int *)((unsigned long)context_ptr+0x00003000+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003000+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003000+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003000+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000000))=0x04c00001;
*((unsigned int *)((unsigned long)context_ptr+0x00000000+4*1))=0x00006040;
*((unsigned int *)((unsigned long)context_ptr+0x00000000+4*2))=0x00006030;
*((unsigned int *)((unsigned long)context_ptr+0x00000000+4*3))=0x02220001;
*((unsigned int *)((unsigned long)context_ptr+0x00000000+4*4))=0x05718adb;
*((unsigned int *)((unsigned long)context_ptr+0x00000000+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x00006058))=0x016a0a02;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*2))=0x02020002;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x00006068))=0x0000c2ce;
*((unsigned int *)((unsigned long)context_ptr+0x00003018))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003018+4*1))=0x0000606c;
*((unsigned int *)((unsigned long)context_ptr+0x00003018+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003018+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003018+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003018+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000018))=0x04c00002;
*((unsigned int *)((unsigned long)context_ptr+0x00000018+4*1))=0x00006068;
*((unsigned int *)((unsigned long)context_ptr+0x00000018+4*2))=0x00006058;
*((unsigned int *)((unsigned long)context_ptr+0x00000018+4*3))=0x02220002;
*((unsigned int *)((unsigned long)context_ptr+0x00000018+4*4))=0x0e7e13ec;
*((unsigned int *)((unsigned long)context_ptr+0x00000018+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x00006080))=0x016a0a02;
*((unsigned int *)((unsigned long)context_ptr+0x00006080+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006080+4*2))=0x02020003;
*((unsigned int *)((unsigned long)context_ptr+0x00006080+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x00006090))=0x00acb7dd;
*((unsigned int *)((unsigned long)context_ptr+0x00003030))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003030+4*1))=0x00006094;
*((unsigned int *)((unsigned long)context_ptr+0x00003030+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003030+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003030+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003030+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000030))=0x04c00003;
*((unsigned int *)((unsigned long)context_ptr+0x00000030+4*1))=0x00006090;
*((unsigned int *)((unsigned long)context_ptr+0x00000030+4*2))=0x00006080;
*((unsigned int *)((unsigned long)context_ptr+0x00000030+4*3))=0x02220003;
*((unsigned int *)((unsigned long)context_ptr+0x00000030+4*4))=0x069407bd;
*((unsigned int *)((unsigned long)context_ptr+0x00000030+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x000060a8))=0x016a0a02;
*((unsigned int *)((unsigned long)context_ptr+0x000060a8+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000060a8+4*2))=0x02020004;
*((unsigned int *)((unsigned long)context_ptr+0x000060a8+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x000060b8))=0x71c830c9;
*((unsigned int *)((unsigned long)context_ptr+0x00003048))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003048+4*1))=0x000060bc;
*((unsigned int *)((unsigned long)context_ptr+0x00003048+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003048+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003048+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003048+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000048))=0x04c00004;
*((unsigned int *)((unsigned long)context_ptr+0x00000048+4*1))=0x000060b8;
*((unsigned int *)((unsigned long)context_ptr+0x00000048+4*2))=0x000060a8;
*((unsigned int *)((unsigned long)context_ptr+0x00000048+4*3))=0x02220004;
*((unsigned int *)((unsigned long)context_ptr+0x00000048+4*4))=0x0ca20854;
*((unsigned int *)((unsigned long)context_ptr+0x00000048+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x000060d0))=0x016a0a02;
*((unsigned int *)((unsigned long)context_ptr+0x000060d0+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000060d0+4*2))=0x02020005;
*((unsigned int *)((unsigned long)context_ptr+0x000060d0+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x000060e0))=0x075b1214;
*((unsigned int *)((unsigned long)context_ptr+0x000060e0+4*1))=0x00000059;
*((unsigned int *)((unsigned long)context_ptr+0x00003060))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003060+4*1))=0x000060e8;
*((unsigned int *)((unsigned long)context_ptr+0x00003060+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003060+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003060+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003060+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000060))=0x04c00005;
*((unsigned int *)((unsigned long)context_ptr+0x00000060+4*1))=0x000060e0;
*((unsigned int *)((unsigned long)context_ptr+0x00000060+4*2))=0x000060d0;
*((unsigned int *)((unsigned long)context_ptr+0x00000060+4*3))=0x02220005;
*((unsigned int *)((unsigned long)context_ptr+0x00000060+4*4))=0x0d1aa6c3;
*((unsigned int *)((unsigned long)context_ptr+0x00000060+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x000060fc))=0x016a0a02;
*((unsigned int *)((unsigned long)context_ptr+0x000060fc+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000060fc+4*2))=0x02020006;
*((unsigned int *)((unsigned long)context_ptr+0x000060fc+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x0000610c))=0x6b4ac13e;
*((unsigned int *)((unsigned long)context_ptr+0x0000610c+4*1))=0x0000210b;
*((unsigned int *)((unsigned long)context_ptr+0x00003078))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003078+4*1))=0x00006114;
*((unsigned int *)((unsigned long)context_ptr+0x00003078+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003078+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003078+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003078+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000078))=0x04c00006;
*((unsigned int *)((unsigned long)context_ptr+0x00000078+4*1))=0x0000610c;
*((unsigned int *)((unsigned long)context_ptr+0x00000078+4*2))=0x000060fc;
*((unsigned int *)((unsigned long)context_ptr+0x00000078+4*3))=0x02220006;
*((unsigned int *)((unsigned long)context_ptr+0x00000078+4*4))=0x012bdf74;
*((unsigned int *)((unsigned long)context_ptr+0x00000078+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x00006128))=0x016a0a02;
*((unsigned int *)((unsigned long)context_ptr+0x00006128+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006128+4*2))=0x02020007;
*((unsigned int *)((unsigned long)context_ptr+0x00006128+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x00006138))=0xb200347b;
*((unsigned int *)((unsigned long)context_ptr+0x00006138+4*1))=0x004c019e;
*((unsigned int *)((unsigned long)context_ptr+0x00003090))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003090+4*1))=0x00006140;
*((unsigned int *)((unsigned long)context_ptr+0x00003090+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003090+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003090+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003090+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000090))=0x04c00007;
*((unsigned int *)((unsigned long)context_ptr+0x00000090+4*1))=0x00006138;
*((unsigned int *)((unsigned long)context_ptr+0x00000090+4*2))=0x00006128;
*((unsigned int *)((unsigned long)context_ptr+0x00000090+4*3))=0x02220007;
*((unsigned int *)((unsigned long)context_ptr+0x00000090+4*4))=0x08b92c24;
*((unsigned int *)((unsigned long)context_ptr+0x00000090+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x00006154))=0x016a0a02;
*((unsigned int *)((unsigned long)context_ptr+0x00006154+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006154+4*2))=0x02020008;
*((unsigned int *)((unsigned long)context_ptr+0x00006154+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x00006164))=0x67a26988;
*((unsigned int *)((unsigned long)context_ptr+0x00006164+4*1))=0x5f4ac9c7;
*((unsigned int *)((unsigned long)context_ptr+0x000030a8))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x000030a8+4*1))=0x0000616c;
*((unsigned int *)((unsigned long)context_ptr+0x000030a8+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000030a8+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000030a8+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000030a8+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x000000a8))=0x04c00008;
*((unsigned int *)((unsigned long)context_ptr+0x000000a8+4*1))=0x00006164;
*((unsigned int *)((unsigned long)context_ptr+0x000000a8+4*2))=0x00006154;
*((unsigned int *)((unsigned long)context_ptr+0x000000a8+4*3))=0x02220008;
*((unsigned int *)((unsigned long)context_ptr+0x000000a8+4*4))=0x0b270af3;
*((unsigned int *)((unsigned long)context_ptr+0x000000a8+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x00006180))=0x016a0a02;
*((unsigned int *)((unsigned long)context_ptr+0x00006180+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006180+4*2))=0x02020009;
*((unsigned int *)((unsigned long)context_ptr+0x00006180+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x00006190))=0x2b54751a;
*((unsigned int *)((unsigned long)context_ptr+0x00006190+4*1))=0x726fe56b;
*((unsigned int *)((unsigned long)context_ptr+0x00006190+4*2))=0x000000b5;
*((unsigned int *)((unsigned long)context_ptr+0x000030c0))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x000030c0+4*1))=0x0000619c;
*((unsigned int *)((unsigned long)context_ptr+0x000030c0+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000030c0+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000030c0+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000030c0+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x000000c0))=0x04c00009;
*((unsigned int *)((unsigned long)context_ptr+0x000000c0+4*1))=0x00006190;
*((unsigned int *)((unsigned long)context_ptr+0x000000c0+4*2))=0x00006180;
*((unsigned int *)((unsigned long)context_ptr+0x000000c0+4*3))=0x02220009;
*((unsigned int *)((unsigned long)context_ptr+0x000000c0+4*4))=0x0e90f79d;
*((unsigned int *)((unsigned long)context_ptr+0x000000c0+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x000061b0))=0x016a0a02;
*((unsigned int *)((unsigned long)context_ptr+0x000061b0+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000061b0+4*2))=0x0202000a;
*((unsigned int *)((unsigned long)context_ptr+0x000061b0+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x000061c0))=0x23a70029;
*((unsigned int *)((unsigned long)context_ptr+0x000061c0+4*1))=0x65f8aec9;
*((unsigned int *)((unsigned long)context_ptr+0x000061c0+4*2))=0x000074eb;
*((unsigned int *)((unsigned long)context_ptr+0x000030d8))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x000030d8+4*1))=0x000061cc;
*((unsigned int *)((unsigned long)context_ptr+0x000030d8+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000030d8+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000030d8+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000030d8+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x000000d8))=0x04c0000a;
*((unsigned int *)((unsigned long)context_ptr+0x000000d8+4*1))=0x000061c0;
*((unsigned int *)((unsigned long)context_ptr+0x000000d8+4*2))=0x000061b0;
*((unsigned int *)((unsigned long)context_ptr+0x000000d8+4*3))=0x0222000a;
*((unsigned int *)((unsigned long)context_ptr+0x000000d8+4*4))=0x0e2014a3;
*((unsigned int *)((unsigned long)context_ptr+0x000000d8+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x000061e0))=0x016a0a02;
*((unsigned int *)((unsigned long)context_ptr+0x000061e0+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000061e0+4*2))=0x0202000b;
*((unsigned int *)((unsigned long)context_ptr+0x000061e0+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x000061f0))=0x207d2e0a;
*((unsigned int *)((unsigned long)context_ptr+0x000061f0+4*1))=0x6f51efde;
*((unsigned int *)((unsigned long)context_ptr+0x000061f0+4*2))=0x008a498e;
*((unsigned int *)((unsigned long)context_ptr+0x000030f0))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x000030f0+4*1))=0x000061fc;
*((unsigned int *)((unsigned long)context_ptr+0x000030f0+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000030f0+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000030f0+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000030f0+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x000000f0))=0x04c0000b;
*((unsigned int *)((unsigned long)context_ptr+0x000000f0+4*1))=0x000061f0;
*((unsigned int *)((unsigned long)context_ptr+0x000000f0+4*2))=0x000061e0;
*((unsigned int *)((unsigned long)context_ptr+0x000000f0+4*3))=0x0222000b;
*((unsigned int *)((unsigned long)context_ptr+0x000000f0+4*4))=0x07118bb6;
*((unsigned int *)((unsigned long)context_ptr+0x000000f0+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x00006210))=0x016a0a02;
*((unsigned int *)((unsigned long)context_ptr+0x00006210+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006210+4*2))=0x0202000c;
*((unsigned int *)((unsigned long)context_ptr+0x00006210+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x00006220))=0xc31382f9;
*((unsigned int *)((unsigned long)context_ptr+0x00006220+4*1))=0xb291c6c8;
*((unsigned int *)((unsigned long)context_ptr+0x00006220+4*2))=0xc2d0bb36;
*((unsigned int *)((unsigned long)context_ptr+0x00003108))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003108+4*1))=0x0000622c;
*((unsigned int *)((unsigned long)context_ptr+0x00003108+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003108+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003108+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003108+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000108))=0x04c0000c;
*((unsigned int *)((unsigned long)context_ptr+0x00000108+4*1))=0x00006220;
*((unsigned int *)((unsigned long)context_ptr+0x00000108+4*2))=0x00006210;
*((unsigned int *)((unsigned long)context_ptr+0x00000108+4*3))=0x0222000c;
*((unsigned int *)((unsigned long)context_ptr+0x00000108+4*4))=0x0a105724;
*((unsigned int *)((unsigned long)context_ptr+0x00000108+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x00006240))=0x016a0a02;
*((unsigned int *)((unsigned long)context_ptr+0x00006240+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006240+4*2))=0x0202000d;
*((unsigned int *)((unsigned long)context_ptr+0x00006240+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x00006250))=0x0f11a739;
*((unsigned int *)((unsigned long)context_ptr+0x00006250+4*1))=0x37e46cf8;
*((unsigned int *)((unsigned long)context_ptr+0x00006250+4*2))=0x542d5b6f;
*((unsigned int *)((unsigned long)context_ptr+0x00006250+4*3))=0x000000fc;
*((unsigned int *)((unsigned long)context_ptr+0x00003120))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003120+4*1))=0x00006260;
*((unsigned int *)((unsigned long)context_ptr+0x00003120+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003120+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003120+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003120+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000120))=0x04c0000d;
*((unsigned int *)((unsigned long)context_ptr+0x00000120+4*1))=0x00006250;
*((unsigned int *)((unsigned long)context_ptr+0x00000120+4*2))=0x00006240;
*((unsigned int *)((unsigned long)context_ptr+0x00000120+4*3))=0x0222000d;
*((unsigned int *)((unsigned long)context_ptr+0x00000120+4*4))=0x068c6dd5;
*((unsigned int *)((unsigned long)context_ptr+0x00000120+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x00006274))=0x016a0a02;
*((unsigned int *)((unsigned long)context_ptr+0x00006274+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006274+4*2))=0x0202000e;
*((unsigned int *)((unsigned long)context_ptr+0x00006274+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x00006284))=0x67bc5b3c;
*((unsigned int *)((unsigned long)context_ptr+0x00006284+4*1))=0x4f647e45;
*((unsigned int *)((unsigned long)context_ptr+0x00006284+4*2))=0xc5fa8ce6;
*((unsigned int *)((unsigned long)context_ptr+0x00006284+4*3))=0x00004392;
*((unsigned int *)((unsigned long)context_ptr+0x00003138))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003138+4*1))=0x00006294;
*((unsigned int *)((unsigned long)context_ptr+0x00003138+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003138+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003138+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003138+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000138))=0x04c0000e;
*((unsigned int *)((unsigned long)context_ptr+0x00000138+4*1))=0x00006284;
*((unsigned int *)((unsigned long)context_ptr+0x00000138+4*2))=0x00006274;
*((unsigned int *)((unsigned long)context_ptr+0x00000138+4*3))=0x0222000e;
*((unsigned int *)((unsigned long)context_ptr+0x00000138+4*4))=0x0b8acdd7;
*((unsigned int *)((unsigned long)context_ptr+0x00000138+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x000062a8))=0x016a0a02;
*((unsigned int *)((unsigned long)context_ptr+0x000062a8+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000062a8+4*2))=0x0202000f;
*((unsigned int *)((unsigned long)context_ptr+0x000062a8+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x000062b8))=0xf27af2ed;
*((unsigned int *)((unsigned long)context_ptr+0x000062b8+4*1))=0x30bfc7d1;
*((unsigned int *)((unsigned long)context_ptr+0x000062b8+4*2))=0x2cf36c8c;
*((unsigned int *)((unsigned long)context_ptr+0x000062b8+4*3))=0x0028a82b;
*((unsigned int *)((unsigned long)context_ptr+0x00003150))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003150+4*1))=0x000062c8;
*((unsigned int *)((unsigned long)context_ptr+0x00003150+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003150+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003150+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003150+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000150))=0x04c0000f;
*((unsigned int *)((unsigned long)context_ptr+0x00000150+4*1))=0x000062b8;
*((unsigned int *)((unsigned long)context_ptr+0x00000150+4*2))=0x000062a8;
*((unsigned int *)((unsigned long)context_ptr+0x00000150+4*3))=0x0222000f;
*((unsigned int *)((unsigned long)context_ptr+0x00000150+4*4))=0x0cbf1f92;
*((unsigned int *)((unsigned long)context_ptr+0x00000150+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000006&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006044,"\xe1\x6f\x1b\x44\x2d\x64\xd4\x5e\x8c\xf8\x21\x69\x04\x64\x77\x8e\x64\x3f\x2b\x51",20))
printf("strip: e16f1b442d64d45e, Pass\n");
else
printf("strip: e16f1b442d64d45e, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006030))=0x016a0a02;
*((unsigned int *)((unsigned long)context_ptr+0x00006030+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006030+4*2))=0x02020010;
*((unsigned int *)((unsigned long)context_ptr+0x00006030+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x00006040))=0xb4ce8273;
*((unsigned int *)((unsigned long)context_ptr+0x00006040+4*1))=0xedec2af5;
*((unsigned int *)((unsigned long)context_ptr+0x00006040+4*2))=0xe140f0a2;
*((unsigned int *)((unsigned long)context_ptr+0x00006040+4*3))=0x07179cc6;
*((unsigned int *)((unsigned long)context_ptr+0x00003168))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003168+4*1))=0x000062dc;
*((unsigned int *)((unsigned long)context_ptr+0x00003168+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003168+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003168+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003168+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000168))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00000168+4*1))=0x00006040;
*((unsigned int *)((unsigned long)context_ptr+0x00000168+4*2))=0x00006030;
*((unsigned int *)((unsigned long)context_ptr+0x00000168+4*3))=0x02220010;
*((unsigned int *)((unsigned long)context_ptr+0x00000168+4*4))=0x0c329870;
*((unsigned int *)((unsigned long)context_ptr+0x00000168+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000000c&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x0000606c,"\x20\xef\xec\x20\x53\x04\x8b\xbe\x01\xa9\xab\x4d\x18\x8c\x3e\x02\x17\x6d\x12\xc5",20))
printf("strip: 20efec2053048bbe, Pass\n");
else
printf("strip: 20efec2053048bbe, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006050))=0x016a0a02;
*((unsigned int *)((unsigned long)context_ptr+0x00006050+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006050+4*2))=0x02020011;
*((unsigned int *)((unsigned long)context_ptr+0x00006050+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x00006060))=0x58f3a1be;
*((unsigned int *)((unsigned long)context_ptr+0x00006060+4*1))=0xd08f1595;
*((unsigned int *)((unsigned long)context_ptr+0x00006060+4*2))=0x40b34233;
*((unsigned int *)((unsigned long)context_ptr+0x00006060+4*3))=0x27ffef42;
*((unsigned int *)((unsigned long)context_ptr+0x00006060+4*4))=0x000000e6;
*((unsigned int *)((unsigned long)context_ptr+0x00003180))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003180+4*1))=0x000062f0;
*((unsigned int *)((unsigned long)context_ptr+0x00003180+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003180+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003180+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003180+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000180))=0x04c00011;
*((unsigned int *)((unsigned long)context_ptr+0x00000180+4*1))=0x00006060;
*((unsigned int *)((unsigned long)context_ptr+0x00000180+4*2))=0x00006050;
*((unsigned int *)((unsigned long)context_ptr+0x00000180+4*3))=0x02220011;
*((unsigned int *)((unsigned long)context_ptr+0x00000180+4*4))=0x095e3817;
*((unsigned int *)((unsigned long)context_ptr+0x00000180+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000012&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006094,"\x7c\xbf\x5d\xea\xac\x6e\x48\x6a\xe4\x2a\xa6\x14\x98\x93\x25\xd4\xbc\x1b\xf7\x27",20))
printf("strip: 7cbf5deaac6e486a, Pass\n");
else
printf("strip: 7cbf5deaac6e486a, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006074))=0x016a0a02;
*((unsigned int *)((unsigned long)context_ptr+0x00006074+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006074+4*2))=0x02020012;
*((unsigned int *)((unsigned long)context_ptr+0x00006074+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x00006084))=0x90acc1e6;
*((unsigned int *)((unsigned long)context_ptr+0x00006084+4*1))=0xcd0769cd;
*((unsigned int *)((unsigned long)context_ptr+0x00006084+4*2))=0x1f5b6330;
*((unsigned int *)((unsigned long)context_ptr+0x00006084+4*3))=0xa79d2d59;
*((unsigned int *)((unsigned long)context_ptr+0x00006084+4*4))=0x00007403;
*((unsigned int *)((unsigned long)context_ptr+0x00003198))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003198+4*1))=0x00006304;
*((unsigned int *)((unsigned long)context_ptr+0x00003198+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003198+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003198+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003198+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000198))=0x04c00012;
*((unsigned int *)((unsigned long)context_ptr+0x00000198+4*1))=0x00006084;
*((unsigned int *)((unsigned long)context_ptr+0x00000198+4*2))=0x00006074;
*((unsigned int *)((unsigned long)context_ptr+0x00000198+4*3))=0x02220012;
*((unsigned int *)((unsigned long)context_ptr+0x00000198+4*4))=0x07efbe86;
*((unsigned int *)((unsigned long)context_ptr+0x00000198+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000060bc,"\xe1\x6e\xb7\x5f\xed\x46\x4f\xeb\x16\x49\x5a\x59\x69\x19\x27\x74\xa9\x73\x8b\xad",20))
printf("strip: e16eb75fed464feb, Pass\n");
else
printf("strip: e16eb75fed464feb, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006098))=0x016a0a02;
*((unsigned int *)((unsigned long)context_ptr+0x00006098+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006098+4*2))=0x02020013;
*((unsigned int *)((unsigned long)context_ptr+0x00006098+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x000060a8))=0xd204ffcd;
*((unsigned int *)((unsigned long)context_ptr+0x000060a8+4*1))=0x1cc60982;
*((unsigned int *)((unsigned long)context_ptr+0x000060a8+4*2))=0x61acc79c;
*((unsigned int *)((unsigned long)context_ptr+0x000060a8+4*3))=0x55e96f06;
*((unsigned int *)((unsigned long)context_ptr+0x000060a8+4*4))=0x0082233f;
*((unsigned int *)((unsigned long)context_ptr+0x000031b0))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x000031b0+4*1))=0x000060bc;
*((unsigned int *)((unsigned long)context_ptr+0x000031b0+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000031b0+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000031b0+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000031b0+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x000001b0))=0x04c00013;
*((unsigned int *)((unsigned long)context_ptr+0x000001b0+4*1))=0x000060a8;
*((unsigned int *)((unsigned long)context_ptr+0x000001b0+4*2))=0x00006098;
*((unsigned int *)((unsigned long)context_ptr+0x000001b0+4*3))=0x02220013;
*((unsigned int *)((unsigned long)context_ptr+0x000001b0+4*4))=0x06862dc2;
*((unsigned int *)((unsigned long)context_ptr+0x000001b0+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000001e&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000060e8,"\xac\x85\xda\x0e\x61\x68\x8d\x70\x8e\x3f\x39\xd6\xb8\x79\x51\x2c\x87\xab\x97\x1d",20))
printf("strip: ac85da0e61688d70, Pass\n");
else
printf("strip: ac85da0e61688d70, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000060d0))=0x016a0a02;
*((unsigned int *)((unsigned long)context_ptr+0x000060d0+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000060d0+4*2))=0x02020014;
*((unsigned int *)((unsigned long)context_ptr+0x000060d0+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x000060e0))=0x4b952df5;
*((unsigned int *)((unsigned long)context_ptr+0x000060e0+4*1))=0xae6e4aa2;
*((unsigned int *)((unsigned long)context_ptr+0x000060e0+4*2))=0x2158ba44;
*((unsigned int *)((unsigned long)context_ptr+0x000060e0+4*3))=0x656e2a9c;
*((unsigned int *)((unsigned long)context_ptr+0x000060e0+4*4))=0xc7aeb513;
*((unsigned int *)((unsigned long)context_ptr+0x000031c8))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x000031c8+4*1))=0x00006318;
*((unsigned int *)((unsigned long)context_ptr+0x000031c8+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000031c8+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000031c8+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000031c8+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x000001c8))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x000001c8+4*1))=0x000060e0;
*((unsigned int *)((unsigned long)context_ptr+0x000001c8+4*2))=0x000060d0;
*((unsigned int *)((unsigned long)context_ptr+0x000001c8+4*3))=0x02220014;
*((unsigned int *)((unsigned long)context_ptr+0x000001c8+4*4))=0x02b52daa;
*((unsigned int *)((unsigned long)context_ptr+0x000001c8+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000024&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006114,"\xce\xa6\x41\x57\xc4\x37\x70\xd7\xd9\x2b\x67\x5c\xdd\xe5\x3a\x47\x8f\xad\x13\x5c",20))
printf("strip: cea64157c43770d7, Pass\n");
else
printf("strip: cea64157c43770d7, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000060f4))=0x016a0a02;
*((unsigned int *)((unsigned long)context_ptr+0x000060f4+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000060f4+4*2))=0x02020015;
*((unsigned int *)((unsigned long)context_ptr+0x000060f4+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x00006104))=0x7bd1e402;
*((unsigned int *)((unsigned long)context_ptr+0x00006104+4*1))=0x4095731b;
*((unsigned int *)((unsigned long)context_ptr+0x00006104+4*2))=0x8fecc67c;
*((unsigned int *)((unsigned long)context_ptr+0x00006104+4*3))=0xebdb13d3;
*((unsigned int *)((unsigned long)context_ptr+0x00006104+4*4))=0xe0d9d32b;
*((unsigned int *)((unsigned long)context_ptr+0x00006104+4*5))=0x00000084;
*((unsigned int *)((unsigned long)context_ptr+0x000031e0))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x000031e0+4*1))=0x0000632c;
*((unsigned int *)((unsigned long)context_ptr+0x000031e0+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000031e0+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000031e0+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000031e0+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x000001e0))=0x04c00015;
*((unsigned int *)((unsigned long)context_ptr+0x000001e0+4*1))=0x00006104;
*((unsigned int *)((unsigned long)context_ptr+0x000001e0+4*2))=0x000060f4;
*((unsigned int *)((unsigned long)context_ptr+0x000001e0+4*3))=0x02220015;
*((unsigned int *)((unsigned long)context_ptr+0x000001e0+4*4))=0x0b5481be;
*((unsigned int *)((unsigned long)context_ptr+0x000001e0+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000002a&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006140,"\x14\x01\x35\xb6\x74\x43\x1b\xbc\x5b\x24\x3b\xfa\xf2\xbd\x4b\x64\x8a\xa2\xf6\x88",20))
printf("strip: 140135b674431bbc, Pass\n");
else
printf("strip: 140135b674431bbc, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x0000611c))=0x016a0a02;
*((unsigned int *)((unsigned long)context_ptr+0x0000611c+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x0000611c+4*2))=0x02020016;
*((unsigned int *)((unsigned long)context_ptr+0x0000611c+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x0000612c))=0x3a011857;
*((unsigned int *)((unsigned long)context_ptr+0x0000612c+4*1))=0x7e394fd6;
*((unsigned int *)((unsigned long)context_ptr+0x0000612c+4*2))=0x135782f2;
*((unsigned int *)((unsigned long)context_ptr+0x0000612c+4*3))=0x615e3992;
*((unsigned int *)((unsigned long)context_ptr+0x0000612c+4*4))=0xbeef3bc2;
*((unsigned int *)((unsigned long)context_ptr+0x0000612c+4*5))=0x0000e17b;
*((unsigned int *)((unsigned long)context_ptr+0x000031f8))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x000031f8+4*1))=0x00006340;
*((unsigned int *)((unsigned long)context_ptr+0x000031f8+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000031f8+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000031f8+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000031f8+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x000001f8))=0x04c00016;
*((unsigned int *)((unsigned long)context_ptr+0x000001f8+4*1))=0x0000612c;
*((unsigned int *)((unsigned long)context_ptr+0x000001f8+4*2))=0x0000611c;
*((unsigned int *)((unsigned long)context_ptr+0x000001f8+4*3))=0x02220016;
*((unsigned int *)((unsigned long)context_ptr+0x000001f8+4*4))=0x0211e55d;
*((unsigned int *)((unsigned long)context_ptr+0x000001f8+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000030&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x0000616c,"\xec\xef\x7d\xf2\x46\xc3\x3d\x72\xe2\x36\xa5\xc7\x51\x77\x3f\x25\x55\xa5\xff\x16",20))
printf("strip: ecef7df246c33d72, Pass\n");
else
printf("strip: ecef7df246c33d72, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006144))=0x016a0a02;
*((unsigned int *)((unsigned long)context_ptr+0x00006144+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006144+4*2))=0x02020017;
*((unsigned int *)((unsigned long)context_ptr+0x00006144+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x00006154))=0x9a1d0161;
*((unsigned int *)((unsigned long)context_ptr+0x00006154+4*1))=0x32bd33ef;
*((unsigned int *)((unsigned long)context_ptr+0x00006154+4*2))=0x11d8e500;
*((unsigned int *)((unsigned long)context_ptr+0x00006154+4*3))=0x61ed3b2d;
*((unsigned int *)((unsigned long)context_ptr+0x00006154+4*4))=0xc3616fce;
*((unsigned int *)((unsigned long)context_ptr+0x00006154+4*5))=0x0095449d;
*((unsigned int *)((unsigned long)context_ptr+0x00003210))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003210+4*1))=0x0000616c;
*((unsigned int *)((unsigned long)context_ptr+0x00003210+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003210+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003210+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003210+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000210))=0x04c00017;
*((unsigned int *)((unsigned long)context_ptr+0x00000210+4*1))=0x00006154;
*((unsigned int *)((unsigned long)context_ptr+0x00000210+4*2))=0x00006144;
*((unsigned int *)((unsigned long)context_ptr+0x00000210+4*3))=0x02220017;
*((unsigned int *)((unsigned long)context_ptr+0x00000210+4*4))=0x0ad5b9ba;
*((unsigned int *)((unsigned long)context_ptr+0x00000210+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000036&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x0000619c,"\x7f\x56\x6d\x2c\xcb\xd7\x4b\xd8\x36\xd5\x18\x95\x85\x02\x03\x4f\xec\x61\x92\xbc",20))
printf("strip: 7f566d2ccbd74bd8, Pass\n");
else
printf("strip: 7f566d2ccbd74bd8, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006180))=0x016a0a02;
*((unsigned int *)((unsigned long)context_ptr+0x00006180+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006180+4*2))=0x02020018;
*((unsigned int *)((unsigned long)context_ptr+0x00006180+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x00006190))=0xde0927f2;
*((unsigned int *)((unsigned long)context_ptr+0x00006190+4*1))=0xad77c4ce;
*((unsigned int *)((unsigned long)context_ptr+0x00006190+4*2))=0xc9643169;
*((unsigned int *)((unsigned long)context_ptr+0x00006190+4*3))=0xaee3f6cd;
*((unsigned int *)((unsigned long)context_ptr+0x00006190+4*4))=0xec2eb985;
*((unsigned int *)((unsigned long)context_ptr+0x00006190+4*5))=0xa26f98b6;
*((unsigned int *)((unsigned long)context_ptr+0x00003228))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003228+4*1))=0x00006354;
*((unsigned int *)((unsigned long)context_ptr+0x00003228+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003228+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003228+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003228+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000228))=0x04c00018;
*((unsigned int *)((unsigned long)context_ptr+0x00000228+4*1))=0x00006190;
*((unsigned int *)((unsigned long)context_ptr+0x00000228+4*2))=0x00006180;
*((unsigned int *)((unsigned long)context_ptr+0x00000228+4*3))=0x02220018;
*((unsigned int *)((unsigned long)context_ptr+0x00000228+4*4))=0x0921bc65;
*((unsigned int *)((unsigned long)context_ptr+0x00000228+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000003c&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000061cc,"\x02\x97\xee\xbf\x0c\x7f\xd4\x3e\x4a\x29\x73\xa7\x0d\x33\x5d\xa6\x3f\x3a\x6f\x71",20))
printf("strip: 0297eebf0c7fd43e, Pass\n");
else
printf("strip: 0297eebf0c7fd43e, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000061a8))=0x016a0a02;
*((unsigned int *)((unsigned long)context_ptr+0x000061a8+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000061a8+4*2))=0x02020019;
*((unsigned int *)((unsigned long)context_ptr+0x000061a8+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x000061b8))=0x037ef814;
*((unsigned int *)((unsigned long)context_ptr+0x000061b8+4*1))=0xbe4fc16b;
*((unsigned int *)((unsigned long)context_ptr+0x000061b8+4*2))=0x07f73dc4;
*((unsigned int *)((unsigned long)context_ptr+0x000061b8+4*3))=0x422783dd;
*((unsigned int *)((unsigned long)context_ptr+0x000061b8+4*4))=0x38d64797;
*((unsigned int *)((unsigned long)context_ptr+0x000061b8+4*5))=0xd2568162;
*((unsigned int *)((unsigned long)context_ptr+0x000061b8+4*6))=0x00000043;
*((unsigned int *)((unsigned long)context_ptr+0x00003240))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003240+4*1))=0x00006368;
*((unsigned int *)((unsigned long)context_ptr+0x00003240+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003240+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003240+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003240+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000240))=0x04c00019;
*((unsigned int *)((unsigned long)context_ptr+0x00000240+4*1))=0x000061b8;
*((unsigned int *)((unsigned long)context_ptr+0x00000240+4*2))=0x000061a8;
*((unsigned int *)((unsigned long)context_ptr+0x00000240+4*3))=0x02220019;
*((unsigned int *)((unsigned long)context_ptr+0x00000240+4*4))=0x0a07f7f4;
*((unsigned int *)((unsigned long)context_ptr+0x00000240+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000042&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000061fc,"\xbe\xe3\xc0\xd2\x5e\x03\xd1\xad\xcb\xf5\x15\x8f\xb8\xce\x65\xfc\x53\xfc\xb4\xa8",20))
printf("strip: bee3c0d25e03d1ad, Pass\n");
else
printf("strip: bee3c0d25e03d1ad, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000061d4))=0x016a0a02;
*((unsigned int *)((unsigned long)context_ptr+0x000061d4+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000061d4+4*2))=0x0202001a;
*((unsigned int *)((unsigned long)context_ptr+0x000061d4+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x000061e4))=0xff59f944;
*((unsigned int *)((unsigned long)context_ptr+0x000061e4+4*1))=0xfbd437da;
*((unsigned int *)((unsigned long)context_ptr+0x000061e4+4*2))=0x15c5aa46;
*((unsigned int *)((unsigned long)context_ptr+0x000061e4+4*3))=0xf3b44ed1;
*((unsigned int *)((unsigned long)context_ptr+0x000061e4+4*4))=0x1d4a9c08;
*((unsigned int *)((unsigned long)context_ptr+0x000061e4+4*5))=0x5883fab6;
*((unsigned int *)((unsigned long)context_ptr+0x000061e4+4*6))=0x00006a72;
*((unsigned int *)((unsigned long)context_ptr+0x00003258))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003258+4*1))=0x0000637c;
*((unsigned int *)((unsigned long)context_ptr+0x00003258+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003258+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003258+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003258+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000258))=0x04c0001a;
*((unsigned int *)((unsigned long)context_ptr+0x00000258+4*1))=0x000061e4;
*((unsigned int *)((unsigned long)context_ptr+0x00000258+4*2))=0x000061d4;
*((unsigned int *)((unsigned long)context_ptr+0x00000258+4*3))=0x0222001a;
*((unsigned int *)((unsigned long)context_ptr+0x00000258+4*4))=0x014934a3;
*((unsigned int *)((unsigned long)context_ptr+0x00000258+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000048&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x0000622c,"\x97\xb1\xd8\x39\x75\x6b\xea\xb5\xf4\x5b\xf7\x19\x68\xd2\x52\x54\x75\x2a\x47\xeb",20))
printf("strip: 97b1d839756beab5, Pass\n");
else
printf("strip: 97b1d839756beab5, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006200))=0x016a0a02;
*((unsigned int *)((unsigned long)context_ptr+0x00006200+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006200+4*2))=0x0202001b;
*((unsigned int *)((unsigned long)context_ptr+0x00006200+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x00006210))=0x8d254d38;
*((unsigned int *)((unsigned long)context_ptr+0x00006210+4*1))=0xd23b0640;
*((unsigned int *)((unsigned long)context_ptr+0x00006210+4*2))=0x3ef1e26a;
*((unsigned int *)((unsigned long)context_ptr+0x00006210+4*3))=0x2b94e18f;
*((unsigned int *)((unsigned long)context_ptr+0x00006210+4*4))=0xde4cfc3f;
*((unsigned int *)((unsigned long)context_ptr+0x00006210+4*5))=0xcab8bdcb;
*((unsigned int *)((unsigned long)context_ptr+0x00006210+4*6))=0x002a0fd8;
*((unsigned int *)((unsigned long)context_ptr+0x00003270))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003270+4*1))=0x0000622c;
*((unsigned int *)((unsigned long)context_ptr+0x00003270+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003270+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003270+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003270+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000270))=0x04c0001b;
*((unsigned int *)((unsigned long)context_ptr+0x00000270+4*1))=0x00006210;
*((unsigned int *)((unsigned long)context_ptr+0x00000270+4*2))=0x00006200;
*((unsigned int *)((unsigned long)context_ptr+0x00000270+4*3))=0x0222001b;
*((unsigned int *)((unsigned long)context_ptr+0x00000270+4*4))=0x08880f9e;
*((unsigned int *)((unsigned long)context_ptr+0x00000270+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000004e&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006260,"\xde\x49\xc7\xc5\x19\x07\x64\x5c\x41\xc1\xd9\xa3\x08\xd0\xf4\xaf\x81\xf8\xfb\x1b",20))
printf("strip: de49c7c51907645c, Pass\n");
else
printf("strip: de49c7c51907645c, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006240))=0x016a0a02;
*((unsigned int *)((unsigned long)context_ptr+0x00006240+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006240+4*2))=0x0202001c;
*((unsigned int *)((unsigned long)context_ptr+0x00006240+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x00006250))=0x30d7c1ac;
*((unsigned int *)((unsigned long)context_ptr+0x00006250+4*1))=0xce828337;
*((unsigned int *)((unsigned long)context_ptr+0x00006250+4*2))=0x81c7e684;
*((unsigned int *)((unsigned long)context_ptr+0x00006250+4*3))=0x6e5779d3;
*((unsigned int *)((unsigned long)context_ptr+0x00006250+4*4))=0xba0da674;
*((unsigned int *)((unsigned long)context_ptr+0x00006250+4*5))=0x331175f7;
*((unsigned int *)((unsigned long)context_ptr+0x00006250+4*6))=0x00cb411a;
*((unsigned int *)((unsigned long)context_ptr+0x00003288))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003288+4*1))=0x00006390;
*((unsigned int *)((unsigned long)context_ptr+0x00003288+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003288+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003288+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003288+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000288))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00000288+4*1))=0x00006250;
*((unsigned int *)((unsigned long)context_ptr+0x00000288+4*2))=0x00006240;
*((unsigned int *)((unsigned long)context_ptr+0x00000288+4*3))=0x0222001c;
*((unsigned int *)((unsigned long)context_ptr+0x00000288+4*4))=0x02f5c5cb;
*((unsigned int *)((unsigned long)context_ptr+0x00000288+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000054&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006294,"\xd9\x66\x2a\x76\x16\xf0\x69\xd0\xca\x73\x0d\xd6\x4e\xb2\xb7\xc1\x1b\x8a\xdd\x21",20))
printf("strip: d9662a7616f069d0, Pass\n");
else
printf("strip: d9662a7616f069d0, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x0000626c))=0x016a0a02;
*((unsigned int *)((unsigned long)context_ptr+0x0000626c+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x0000626c+4*2))=0x0202001d;
*((unsigned int *)((unsigned long)context_ptr+0x0000626c+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x0000627c))=0x1b28cd13;
*((unsigned int *)((unsigned long)context_ptr+0x0000627c+4*1))=0x6b9bb642;
*((unsigned int *)((unsigned long)context_ptr+0x0000627c+4*2))=0xafc4ec28;
*((unsigned int *)((unsigned long)context_ptr+0x0000627c+4*3))=0xc51cc6d0;
*((unsigned int *)((unsigned long)context_ptr+0x0000627c+4*4))=0xaf7bbfd6;
*((unsigned int *)((unsigned long)context_ptr+0x0000627c+4*5))=0xc843c319;
*((unsigned int *)((unsigned long)context_ptr+0x0000627c+4*6))=0x138982a2;
*((unsigned int *)((unsigned long)context_ptr+0x0000627c+4*7))=0x0000000a;
*((unsigned int *)((unsigned long)context_ptr+0x000032a0))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x000032a0+4*1))=0x000063a4;
*((unsigned int *)((unsigned long)context_ptr+0x000032a0+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000032a0+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000032a0+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000032a0+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x000002a0))=0x04c0001d;
*((unsigned int *)((unsigned long)context_ptr+0x000002a0+4*1))=0x0000627c;
*((unsigned int *)((unsigned long)context_ptr+0x000002a0+4*2))=0x0000626c;
*((unsigned int *)((unsigned long)context_ptr+0x000002a0+4*3))=0x0222001d;
*((unsigned int *)((unsigned long)context_ptr+0x000002a0+4*4))=0x023746dd;
*((unsigned int *)((unsigned long)context_ptr+0x000002a0+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000005a&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000062c8,"\x5d\x4c\x42\x0e\xd7\xce\x98\xe5\x93\x5f\x38\x89\x20\x2b\x13\xe4\x5f\x36\x4c\xbb",20))
printf("strip: 5d4c420ed7ce98e5, Pass\n");
else
printf("strip: 5d4c420ed7ce98e5, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x0000629c))=0x016a0a02;
*((unsigned int *)((unsigned long)context_ptr+0x0000629c+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x0000629c+4*2))=0x0202001e;
*((unsigned int *)((unsigned long)context_ptr+0x0000629c+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x000062ac))=0x62501589;
*((unsigned int *)((unsigned long)context_ptr+0x000062ac+4*1))=0x126d7a67;
*((unsigned int *)((unsigned long)context_ptr+0x000062ac+4*2))=0x82d4a438;
*((unsigned int *)((unsigned long)context_ptr+0x000062ac+4*3))=0x62271225;
*((unsigned int *)((unsigned long)context_ptr+0x000062ac+4*4))=0x9086aa90;
*((unsigned int *)((unsigned long)context_ptr+0x000062ac+4*5))=0x66baaa5a;
*((unsigned int *)((unsigned long)context_ptr+0x000062ac+4*6))=0x77e7bed0;
*((unsigned int *)((unsigned long)context_ptr+0x000062ac+4*7))=0x0000c658;
*((unsigned int *)((unsigned long)context_ptr+0x000032b8))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x000032b8+4*1))=0x000063b8;
*((unsigned int *)((unsigned long)context_ptr+0x000032b8+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000032b8+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000032b8+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000032b8+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x000002b8))=0x04c0001e;
*((unsigned int *)((unsigned long)context_ptr+0x000002b8+4*1))=0x000062ac;
*((unsigned int *)((unsigned long)context_ptr+0x000002b8+4*2))=0x0000629c;
*((unsigned int *)((unsigned long)context_ptr+0x000002b8+4*3))=0x0222001e;
*((unsigned int *)((unsigned long)context_ptr+0x000002b8+4*4))=0x0fa29557;
*((unsigned int *)((unsigned long)context_ptr+0x000002b8+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000060&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000062dc,"\x3e\x2b\xd5\x35\x3e\x6d\xc7\x02\x2a\x58\x83\x56\x4b\x10\xce\x71\x55\x34\xff\x39",20))
printf("strip: 3e2bd5353e6dc702, Pass\n");
else
printf("strip: 3e2bd5353e6dc702, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006040))=0x016a0a02;
*((unsigned int *)((unsigned long)context_ptr+0x00006040+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006040+4*2))=0x0202001f;
*((unsigned int *)((unsigned long)context_ptr+0x00006040+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x000062cc))=0xa2563cf1;
*((unsigned int *)((unsigned long)context_ptr+0x000062cc+4*1))=0x8cc22452;
*((unsigned int *)((unsigned long)context_ptr+0x000062cc+4*2))=0xec1db589;
*((unsigned int *)((unsigned long)context_ptr+0x000062cc+4*3))=0x9a99b17a;
*((unsigned int *)((unsigned long)context_ptr+0x000062cc+4*4))=0x357f16b5;
*((unsigned int *)((unsigned long)context_ptr+0x000062cc+4*5))=0x685a8363;
*((unsigned int *)((unsigned long)context_ptr+0x000062cc+4*6))=0x9af40bbb;
*((unsigned int *)((unsigned long)context_ptr+0x000062cc+4*7))=0x00148e29;
*((unsigned int *)((unsigned long)context_ptr+0x000032d0))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x000032d0+4*1))=0x000063cc;
*((unsigned int *)((unsigned long)context_ptr+0x000032d0+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000032d0+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000032d0+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000032d0+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x000002d0))=0x04c0001f;
*((unsigned int *)((unsigned long)context_ptr+0x000002d0+4*1))=0x000062cc;
*((unsigned int *)((unsigned long)context_ptr+0x000002d0+4*2))=0x00006040;
*((unsigned int *)((unsigned long)context_ptr+0x000002d0+4*3))=0x0222001f;
*((unsigned int *)((unsigned long)context_ptr+0x000002d0+4*4))=0x06b76911;
*((unsigned int *)((unsigned long)context_ptr+0x000002d0+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000066&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000062f0,"\x0f\x86\x29\xfe\xde\x31\xfa\xe8\x02\xb5\xff\xc9\xe1\x63\xf0\x64\x7d\x4c\xcf\xd0",20))
printf("strip: 0f8629fede31fae8, Pass\n");
else
printf("strip: 0f8629fede31fae8, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006030))=0x016a0a02;
*((unsigned int *)((unsigned long)context_ptr+0x00006030+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006030+4*2))=0x02020020;
*((unsigned int *)((unsigned long)context_ptr+0x00006030+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x000063e0))=0x7a8904de;
*((unsigned int *)((unsigned long)context_ptr+0x000063e0+4*1))=0xe545d020;
*((unsigned int *)((unsigned long)context_ptr+0x000063e0+4*2))=0xcadddab3;
*((unsigned int *)((unsigned long)context_ptr+0x000063e0+4*3))=0x352401bc;
*((unsigned int *)((unsigned long)context_ptr+0x000063e0+4*4))=0x7c200093;
*((unsigned int *)((unsigned long)context_ptr+0x000063e0+4*5))=0x2c38510a;
*((unsigned int *)((unsigned long)context_ptr+0x000063e0+4*6))=0xa63be151;
*((unsigned int *)((unsigned long)context_ptr+0x000063e0+4*7))=0x5930acbb;
*((unsigned int *)((unsigned long)context_ptr+0x000032e8))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x000032e8+4*1))=0x00006060;
*((unsigned int *)((unsigned long)context_ptr+0x000032e8+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000032e8+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000032e8+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000032e8+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x000002e8))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x000002e8+4*1))=0x000063e0;
*((unsigned int *)((unsigned long)context_ptr+0x000002e8+4*2))=0x00006030;
*((unsigned int *)((unsigned long)context_ptr+0x000002e8+4*3))=0x02220020;
*((unsigned int *)((unsigned long)context_ptr+0x000002e8+4*4))=0x0f812b01;
*((unsigned int *)((unsigned long)context_ptr+0x000002e8+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000006c&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006304,"\xa9\xb5\xb9\x77\x2c\x8b\xb2\xe0\xcb\x91\x7b\xf0\x40\xc5\x0e\xf2\xe7\xeb\x4c\xdb",20))
printf("strip: a9b5b9772c8bb2e0, Pass\n");
else
printf("strip: a9b5b9772c8bb2e0, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006050))=0x016a0a02;
*((unsigned int *)((unsigned long)context_ptr+0x00006050+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006050+4*2))=0x02020021;
*((unsigned int *)((unsigned long)context_ptr+0x00006050+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x000062ec))=0x079aa3cc;
*((unsigned int *)((unsigned long)context_ptr+0x000062ec+4*1))=0xa434c458;
*((unsigned int *)((unsigned long)context_ptr+0x000062ec+4*2))=0x368470f9;
*((unsigned int *)((unsigned long)context_ptr+0x000062ec+4*3))=0x9a783c01;
*((unsigned int *)((unsigned long)context_ptr+0x000062ec+4*4))=0xb8544ad5;
*((unsigned int *)((unsigned long)context_ptr+0x000062ec+4*5))=0x16e0b6aa;
*((unsigned int *)((unsigned long)context_ptr+0x000062ec+4*6))=0xa79c7f1f;
*((unsigned int *)((unsigned long)context_ptr+0x000062ec+4*7))=0x3deb223a;
*((unsigned int *)((unsigned long)context_ptr+0x000062ec+4*8))=0x00000004;
*((unsigned int *)((unsigned long)context_ptr+0x00003300))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003300+4*1))=0x00006084;
*((unsigned int *)((unsigned long)context_ptr+0x00003300+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003300+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003300+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003300+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000300))=0x04c00021;
*((unsigned int *)((unsigned long)context_ptr+0x00000300+4*1))=0x000062ec;
*((unsigned int *)((unsigned long)context_ptr+0x00000300+4*2))=0x00006050;
*((unsigned int *)((unsigned long)context_ptr+0x00000300+4*3))=0x02220021;
*((unsigned int *)((unsigned long)context_ptr+0x00000300+4*4))=0x0a2237d4;
*((unsigned int *)((unsigned long)context_ptr+0x00000300+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000072&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000060bc,"\xa8\x19\xbc\x0c\xb3\x83\x51\xd8\xac\x1c\xb2\x10\x71\xed\x7c\x81\xad\x39\x9c\x5e",20))
printf("strip: a819bc0cb38351d8, Pass\n");
else
printf("strip: a819bc0cb38351d8, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006074))=0x016a0a02;
*((unsigned int *)((unsigned long)context_ptr+0x00006074+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006074+4*2))=0x02020022;
*((unsigned int *)((unsigned long)context_ptr+0x00006074+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x000060a8))=0xd2c327a3;
*((unsigned int *)((unsigned long)context_ptr+0x000060a8+4*1))=0x4547119e;
*((unsigned int *)((unsigned long)context_ptr+0x000060a8+4*2))=0xfd94c777;
*((unsigned int *)((unsigned long)context_ptr+0x000060a8+4*3))=0x0ffa24b5;
*((unsigned int *)((unsigned long)context_ptr+0x000060a8+4*4))=0x0563a355;
*((unsigned int *)((unsigned long)context_ptr+0x000060a8+4*5))=0x97c63d4b;
*((unsigned int *)((unsigned long)context_ptr+0x000060a8+4*6))=0x5136df24;
*((unsigned int *)((unsigned long)context_ptr+0x000060a8+4*7))=0x846bc3df;
*((unsigned int *)((unsigned long)context_ptr+0x000060a8+4*8))=0x0000b5fa;
*((unsigned int *)((unsigned long)context_ptr+0x00003318))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003318+4*1))=0x00006400;
*((unsigned int *)((unsigned long)context_ptr+0x00003318+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003318+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003318+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003318+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000318))=0x04c00022;
*((unsigned int *)((unsigned long)context_ptr+0x00000318+4*1))=0x000060a8;
*((unsigned int *)((unsigned long)context_ptr+0x00000318+4*2))=0x00006074;
*((unsigned int *)((unsigned long)context_ptr+0x00000318+4*3))=0x02220022;
*((unsigned int *)((unsigned long)context_ptr+0x00000318+4*4))=0x0fcfd323;
*((unsigned int *)((unsigned long)context_ptr+0x00000318+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000078&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006318,"\x34\x5b\x68\xd7\x59\xed\x6e\x49\x5f\x4c\xad\x8c\x59\x4b\xde\x2b\x1e\x91\xae\x55",20))
printf("strip: 345b68d759ed6e49, Pass\n");
else
printf("strip: 345b68d759ed6e49, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006098))=0x016a0a02;
*((unsigned int *)((unsigned long)context_ptr+0x00006098+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006098+4*2))=0x02020023;
*((unsigned int *)((unsigned long)context_ptr+0x00006098+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x000060cc))=0x0e18a33c;
*((unsigned int *)((unsigned long)context_ptr+0x000060cc+4*1))=0x864d99d7;
*((unsigned int *)((unsigned long)context_ptr+0x000060cc+4*2))=0x2400ad8e;
*((unsigned int *)((unsigned long)context_ptr+0x000060cc+4*3))=0x3273c017;
*((unsigned int *)((unsigned long)context_ptr+0x000060cc+4*4))=0x8b76ab5f;
*((unsigned int *)((unsigned long)context_ptr+0x000060cc+4*5))=0x1b1a66f0;
*((unsigned int *)((unsigned long)context_ptr+0x000060cc+4*6))=0xc71d4fb9;
*((unsigned int *)((unsigned long)context_ptr+0x000060cc+4*7))=0xbd9d1ae3;
*((unsigned int *)((unsigned long)context_ptr+0x000060cc+4*8))=0x00afd63e;
*((unsigned int *)((unsigned long)context_ptr+0x00003330))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003330+4*1))=0x00006310;
*((unsigned int *)((unsigned long)context_ptr+0x00003330+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003330+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003330+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003330+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000330))=0x04c00023;
*((unsigned int *)((unsigned long)context_ptr+0x00000330+4*1))=0x000060cc;
*((unsigned int *)((unsigned long)context_ptr+0x00000330+4*2))=0x00006098;
*((unsigned int *)((unsigned long)context_ptr+0x00000330+4*3))=0x02220023;
*((unsigned int *)((unsigned long)context_ptr+0x00000330+4*4))=0x04201545;
*((unsigned int *)((unsigned long)context_ptr+0x00000330+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000007e&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x0000632c,"\xbb\xe9\x85\x88\xc8\x32\xc3\xde\xcb\x9d\x7d\x65\xde\x68\x42\x88\xda\xf3\xa5\xf2",20))
printf("strip: bbe98588c832c3de, Pass\n");
else
printf("strip: bbe98588c832c3de, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006324))=0x016a0a02;
*((unsigned int *)((unsigned long)context_ptr+0x00006324+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006324+4*2))=0x02020024;
*((unsigned int *)((unsigned long)context_ptr+0x00006324+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x000060f0))=0xbe7a0514;
*((unsigned int *)((unsigned long)context_ptr+0x000060f0+4*1))=0xd49d00bd;
*((unsigned int *)((unsigned long)context_ptr+0x000060f0+4*2))=0xb46bc5dd;
*((unsigned int *)((unsigned long)context_ptr+0x000060f0+4*3))=0x580910b3;
*((unsigned int *)((unsigned long)context_ptr+0x000060f0+4*4))=0xc2a561a4;
*((unsigned int *)((unsigned long)context_ptr+0x000060f0+4*5))=0x8df848c5;
*((unsigned int *)((unsigned long)context_ptr+0x000060f0+4*6))=0x27aca2a0;
*((unsigned int *)((unsigned long)context_ptr+0x000060f0+4*7))=0xb6f76eac;
*((unsigned int *)((unsigned long)context_ptr+0x000060f0+4*8))=0x96d5fdf9;
*((unsigned int *)((unsigned long)context_ptr+0x00003348))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003348+4*1))=0x00006414;
*((unsigned int *)((unsigned long)context_ptr+0x00003348+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003348+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003348+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003348+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000348))=0x04c00024;
*((unsigned int *)((unsigned long)context_ptr+0x00000348+4*1))=0x000060f0;
*((unsigned int *)((unsigned long)context_ptr+0x00000348+4*2))=0x00006324;
*((unsigned int *)((unsigned long)context_ptr+0x00000348+4*3))=0x02220024;
*((unsigned int *)((unsigned long)context_ptr+0x00000348+4*4))=0x05ea2fde;
*((unsigned int *)((unsigned long)context_ptr+0x00000348+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000084&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006340,"\x40\x93\x4d\x38\x7f\x69\x90\xbb\x5e\x64\x83\xc7\x8b\xf4\xce\x5e\xc7\x68\x0d\xf9",20))
printf("strip: 40934d387f6990bb, Pass\n");
else
printf("strip: 40934d387f6990bb, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006334))=0x016a0a02;
*((unsigned int *)((unsigned long)context_ptr+0x00006334+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006334+4*2))=0x02020025;
*((unsigned int *)((unsigned long)context_ptr+0x00006334+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x00006114))=0x13cb8ff2;
*((unsigned int *)((unsigned long)context_ptr+0x00006114+4*1))=0xd21dc610;
*((unsigned int *)((unsigned long)context_ptr+0x00006114+4*2))=0xb71d6eef;
*((unsigned int *)((unsigned long)context_ptr+0x00006114+4*3))=0x8ae38072;
*((unsigned int *)((unsigned long)context_ptr+0x00006114+4*4))=0x82d95f23;
*((unsigned int *)((unsigned long)context_ptr+0x00006114+4*5))=0xe1088114;
*((unsigned int *)((unsigned long)context_ptr+0x00006114+4*6))=0xe5feba3f;
*((unsigned int *)((unsigned long)context_ptr+0x00006114+4*7))=0x8bb25287;
*((unsigned int *)((unsigned long)context_ptr+0x00006114+4*8))=0x27b13de8;
*((unsigned int *)((unsigned long)context_ptr+0x00006114+4*9))=0x00000067;
*((unsigned int *)((unsigned long)context_ptr+0x00003360))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003360+4*1))=0x00006428;
*((unsigned int *)((unsigned long)context_ptr+0x00003360+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003360+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003360+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003360+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000360))=0x04c00025;
*((unsigned int *)((unsigned long)context_ptr+0x00000360+4*1))=0x00006114;
*((unsigned int *)((unsigned long)context_ptr+0x00000360+4*2))=0x00006334;
*((unsigned int *)((unsigned long)context_ptr+0x00000360+4*3))=0x02220025;
*((unsigned int *)((unsigned long)context_ptr+0x00000360+4*4))=0x0489b9a1;
*((unsigned int *)((unsigned long)context_ptr+0x00000360+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000008a&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x0000616c,"\xa6\xc1\xd4\x1e\x77\xf1\x4f\x8d\xc3\x83\x3b\x32\x94\x6d\xd1\x82\x51\xa1\xf1\xc7",20))
printf("strip: a6c1d41e77f14f8d, Pass\n");
else
printf("strip: a6c1d41e77f14f8d, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006344))=0x016a0a02;
*((unsigned int *)((unsigned long)context_ptr+0x00006344+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006344+4*2))=0x02020026;
*((unsigned int *)((unsigned long)context_ptr+0x00006344+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x0000613c))=0x549b0742;
*((unsigned int *)((unsigned long)context_ptr+0x0000613c+4*1))=0x328c3be3;
*((unsigned int *)((unsigned long)context_ptr+0x0000613c+4*2))=0xe4c0a4f7;
*((unsigned int *)((unsigned long)context_ptr+0x0000613c+4*3))=0x9e738b74;
*((unsigned int *)((unsigned long)context_ptr+0x0000613c+4*4))=0xc55dd255;
*((unsigned int *)((unsigned long)context_ptr+0x0000613c+4*5))=0xe67a5d04;
*((unsigned int *)((unsigned long)context_ptr+0x0000613c+4*6))=0xe6a2bbb8;
*((unsigned int *)((unsigned long)context_ptr+0x0000613c+4*7))=0xc3eba1b9;
*((unsigned int *)((unsigned long)context_ptr+0x0000613c+4*8))=0xbf30de03;
*((unsigned int *)((unsigned long)context_ptr+0x0000613c+4*9))=0x00006469;
*((unsigned int *)((unsigned long)context_ptr+0x00003378))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003378+4*1))=0x00006164;
*((unsigned int *)((unsigned long)context_ptr+0x00003378+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003378+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003378+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003378+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000378))=0x04c00026;
*((unsigned int *)((unsigned long)context_ptr+0x00000378+4*1))=0x0000613c;
*((unsigned int *)((unsigned long)context_ptr+0x00000378+4*2))=0x00006344;
*((unsigned int *)((unsigned long)context_ptr+0x00000378+4*3))=0x02220026;
*((unsigned int *)((unsigned long)context_ptr+0x00000378+4*4))=0x0ffdb8ed;
*((unsigned int *)((unsigned long)context_ptr+0x00000378+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000090&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006354,"\x4a\xf4\x78\x62\xf9\x45\x15\x8b\x75\x27\xd3\xb4\xff\x8d\x52\xb4\x33\xc4\xd7\x0f",20))
printf("strip: 4af47862f945158b, Pass\n");
else
printf("strip: 4af47862f945158b, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006354))=0x016a0a02;
*((unsigned int *)((unsigned long)context_ptr+0x00006354+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006354+4*2))=0x02020027;
*((unsigned int *)((unsigned long)context_ptr+0x00006354+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x00006178))=0x5cc6fdb9;
*((unsigned int *)((unsigned long)context_ptr+0x00006178+4*1))=0xe5886482;
*((unsigned int *)((unsigned long)context_ptr+0x00006178+4*2))=0x2581e418;
*((unsigned int *)((unsigned long)context_ptr+0x00006178+4*3))=0x780631ef;
*((unsigned int *)((unsigned long)context_ptr+0x00006178+4*4))=0x90a00c92;
*((unsigned int *)((unsigned long)context_ptr+0x00006178+4*5))=0x215b1490;
*((unsigned int *)((unsigned long)context_ptr+0x00006178+4*6))=0xe1545e77;
*((unsigned int *)((unsigned long)context_ptr+0x00006178+4*7))=0xffa81c9f;
*((unsigned int *)((unsigned long)context_ptr+0x00006178+4*8))=0x79a8c55d;
*((unsigned int *)((unsigned long)context_ptr+0x00006178+4*9))=0x006a3667;
*((unsigned int *)((unsigned long)context_ptr+0x00003390))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003390+4*1))=0x0000643c;
*((unsigned int *)((unsigned long)context_ptr+0x00003390+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003390+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003390+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003390+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000390))=0x04c00027;
*((unsigned int *)((unsigned long)context_ptr+0x00000390+4*1))=0x00006178;
*((unsigned int *)((unsigned long)context_ptr+0x00000390+4*2))=0x00006354;
*((unsigned int *)((unsigned long)context_ptr+0x00000390+4*3))=0x02220027;
*((unsigned int *)((unsigned long)context_ptr+0x00000390+4*4))=0x0ab5c312;
*((unsigned int *)((unsigned long)context_ptr+0x00000390+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000096&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006368,"\x16\x75\x21\x80\xfc\x0b\x0e\x81\x7f\xe2\x31\x85\x61\x9f\x8f\x97\xf0\x83\x95\x39",20))
printf("strip: 16752180fc0b0e81, Pass\n");
else
printf("strip: 16752180fc0b0e81, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006364))=0x016a0a02;
*((unsigned int *)((unsigned long)context_ptr+0x00006364+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006364+4*2))=0x02020028;
*((unsigned int *)((unsigned long)context_ptr+0x00006364+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x000061a0))=0xb9292de4;
*((unsigned int *)((unsigned long)context_ptr+0x000061a0+4*1))=0x5be68536;
*((unsigned int *)((unsigned long)context_ptr+0x000061a0+4*2))=0x17a8debc;
*((unsigned int *)((unsigned long)context_ptr+0x000061a0+4*3))=0x75ffcc84;
*((unsigned int *)((unsigned long)context_ptr+0x000061a0+4*4))=0xed7f590e;
*((unsigned int *)((unsigned long)context_ptr+0x000061a0+4*5))=0x1970ea10;
*((unsigned int *)((unsigned long)context_ptr+0x000061a0+4*6))=0x3c221ec0;
*((unsigned int *)((unsigned long)context_ptr+0x000061a0+4*7))=0x96dca98c;
*((unsigned int *)((unsigned long)context_ptr+0x000061a0+4*8))=0xa9817ba3;
*((unsigned int *)((unsigned long)context_ptr+0x000061a0+4*9))=0x9f9f4b45;
*((unsigned int *)((unsigned long)context_ptr+0x000033a8))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x000033a8+4*1))=0x00006450;
*((unsigned int *)((unsigned long)context_ptr+0x000033a8+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000033a8+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000033a8+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000033a8+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x000003a8))=0x04c00028;
*((unsigned int *)((unsigned long)context_ptr+0x000003a8+4*1))=0x000061a0;
*((unsigned int *)((unsigned long)context_ptr+0x000003a8+4*2))=0x00006364;
*((unsigned int *)((unsigned long)context_ptr+0x000003a8+4*3))=0x02220028;
*((unsigned int *)((unsigned long)context_ptr+0x000003a8+4*4))=0x08c66296;
*((unsigned int *)((unsigned long)context_ptr+0x000003a8+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000009c&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x0000637c,"\x33\x13\xfe\x34\x76\xb9\x3d\x21\xaf\xc6\x41\xec\x31\x1a\xa5\x5b\x1b\x92\x0e\xd0",20))
printf("strip: 3313fe3476b93d21, Pass\n");
else
printf("strip: 3313fe3476b93d21, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006374))=0x016a0a02;
*((unsigned int *)((unsigned long)context_ptr+0x00006374+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006374+4*2))=0x02020029;
*((unsigned int *)((unsigned long)context_ptr+0x00006374+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x000061c8))=0x77e836b2;
*((unsigned int *)((unsigned long)context_ptr+0x000061c8+4*1))=0xdbbd6d4c;
*((unsigned int *)((unsigned long)context_ptr+0x000061c8+4*2))=0x7af721d0;
*((unsigned int *)((unsigned long)context_ptr+0x000061c8+4*3))=0x31f02bf3;
*((unsigned int *)((unsigned long)context_ptr+0x000061c8+4*4))=0x29d745de;
*((unsigned int *)((unsigned long)context_ptr+0x000061c8+4*5))=0xef1fa9da;
*((unsigned int *)((unsigned long)context_ptr+0x000061c8+4*6))=0x0dd72f6f;
*((unsigned int *)((unsigned long)context_ptr+0x000061c8+4*7))=0xbf17bc09;
*((unsigned int *)((unsigned long)context_ptr+0x000061c8+4*8))=0x9023f018;
*((unsigned int *)((unsigned long)context_ptr+0x000061c8+4*9))=0x7d185da5;
*((unsigned int *)((unsigned long)context_ptr+0x000061c8+4*10))=0x00000055;
*((unsigned int *)((unsigned long)context_ptr+0x000033c0))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x000033c0+4*1))=0x00006464;
*((unsigned int *)((unsigned long)context_ptr+0x000033c0+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000033c0+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000033c0+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000033c0+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x000003c0))=0x04c00029;
*((unsigned int *)((unsigned long)context_ptr+0x000003c0+4*1))=0x000061c8;
*((unsigned int *)((unsigned long)context_ptr+0x000003c0+4*2))=0x00006374;
*((unsigned int *)((unsigned long)context_ptr+0x000003c0+4*3))=0x02220029;
*((unsigned int *)((unsigned long)context_ptr+0x000003c0+4*4))=0x03949937;
*((unsigned int *)((unsigned long)context_ptr+0x000003c0+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000000a2&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x0000622c,"\x1e\x60\x42\x02\xe2\xb7\x50\xc1\x64\x12\xbc\xc9\x9a\xc9\x1a\x07\xd8\x72\x83\xbc",20))
printf("strip: 1e604202e2b750c1, Pass\n");
else
printf("strip: 1e604202e2b750c1, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000061f4))=0x016a0a02;
*((unsigned int *)((unsigned long)context_ptr+0x000061f4+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000061f4+4*2))=0x0202002a;
*((unsigned int *)((unsigned long)context_ptr+0x000061f4+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x00006204))=0x23a4ecde;
*((unsigned int *)((unsigned long)context_ptr+0x00006204+4*1))=0xee21f56b;
*((unsigned int *)((unsigned long)context_ptr+0x00006204+4*2))=0x17d0975c;
*((unsigned int *)((unsigned long)context_ptr+0x00006204+4*3))=0xf8e77a1c;
*((unsigned int *)((unsigned long)context_ptr+0x00006204+4*4))=0x60cb31a7;
*((unsigned int *)((unsigned long)context_ptr+0x00006204+4*5))=0x84719743;
*((unsigned int *)((unsigned long)context_ptr+0x00006204+4*6))=0x6edf09f8;
*((unsigned int *)((unsigned long)context_ptr+0x00006204+4*7))=0x79bce0d8;
*((unsigned int *)((unsigned long)context_ptr+0x00006204+4*8))=0xb6659885;
*((unsigned int *)((unsigned long)context_ptr+0x00006204+4*9))=0x90f456da;
*((unsigned int *)((unsigned long)context_ptr+0x00006204+4*10))=0x0000294b;
*((unsigned int *)((unsigned long)context_ptr+0x000033d8))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x000033d8+4*1))=0x00006478;
*((unsigned int *)((unsigned long)context_ptr+0x000033d8+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000033d8+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000033d8+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000033d8+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x000003d8))=0x04c0002a;
*((unsigned int *)((unsigned long)context_ptr+0x000003d8+4*1))=0x00006204;
*((unsigned int *)((unsigned long)context_ptr+0x000003d8+4*2))=0x000061f4;
*((unsigned int *)((unsigned long)context_ptr+0x000003d8+4*3))=0x0222002a;
*((unsigned int *)((unsigned long)context_ptr+0x000003d8+4*4))=0x0cf130e1;
*((unsigned int *)((unsigned long)context_ptr+0x000003d8+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000000a8&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006390,"\xf3\xc3\x65\xa8\x8b\xc0\xf6\x8e\xdf\xaf\xb7\x55\x4f\x42\x59\xd9\xa7\x7f\x4f\x04",20))
printf("strip: f3c365a88bc0f68e, Pass\n");
else
printf("strip: f3c365a88bc0f68e, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006384))=0x016a0a02;
*((unsigned int *)((unsigned long)context_ptr+0x00006384+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006384+4*2))=0x0202002b;
*((unsigned int *)((unsigned long)context_ptr+0x00006384+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x00006230))=0x0b03a589;
*((unsigned int *)((unsigned long)context_ptr+0x00006230+4*1))=0xbb996417;
*((unsigned int *)((unsigned long)context_ptr+0x00006230+4*2))=0x64dd1ba6;
*((unsigned int *)((unsigned long)context_ptr+0x00006230+4*3))=0xab612bd0;
*((unsigned int *)((unsigned long)context_ptr+0x00006230+4*4))=0xcfec84a1;
*((unsigned int *)((unsigned long)context_ptr+0x00006230+4*5))=0x836aad98;
*((unsigned int *)((unsigned long)context_ptr+0x00006230+4*6))=0x7533d6a1;
*((unsigned int *)((unsigned long)context_ptr+0x00006230+4*7))=0x1e09322f;
*((unsigned int *)((unsigned long)context_ptr+0x00006230+4*8))=0x244e54c1;
*((unsigned int *)((unsigned long)context_ptr+0x00006230+4*9))=0x610e6a93;
*((unsigned int *)((unsigned long)context_ptr+0x00006230+4*10))=0x00f9c1ce;
*((unsigned int *)((unsigned long)context_ptr+0x000033f0))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x000033f0+4*1))=0x0000648c;
*((unsigned int *)((unsigned long)context_ptr+0x000033f0+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000033f0+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000033f0+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000033f0+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x000003f0))=0x04c0002b;
*((unsigned int *)((unsigned long)context_ptr+0x000003f0+4*1))=0x00006230;
*((unsigned int *)((unsigned long)context_ptr+0x000003f0+4*2))=0x00006384;
*((unsigned int *)((unsigned long)context_ptr+0x000003f0+4*3))=0x0222002b;
*((unsigned int *)((unsigned long)context_ptr+0x000003f0+4*4))=0x0cad928b;
*((unsigned int *)((unsigned long)context_ptr+0x000003f0+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000000ae&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000063a4,"\xc6\x2e\xfa\x3f\x6f\x92\xe3\xb5\xfa\xc9\xb5\x3c\x68\xa8\x28\x2d\xf4\xe9\xc9\x3d",20))
printf("strip: c62efa3f6f92e3b5, Pass\n");
else
printf("strip: c62efa3f6f92e3b5, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006394))=0x016a0a02;
*((unsigned int *)((unsigned long)context_ptr+0x00006394+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006394+4*2))=0x0202002c;
*((unsigned int *)((unsigned long)context_ptr+0x00006394+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x0000625c))=0x4bbdd849;
*((unsigned int *)((unsigned long)context_ptr+0x0000625c+4*1))=0xd9f04b7c;
*((unsigned int *)((unsigned long)context_ptr+0x0000625c+4*2))=0xcc13b089;
*((unsigned int *)((unsigned long)context_ptr+0x0000625c+4*3))=0xe353445b;
*((unsigned int *)((unsigned long)context_ptr+0x0000625c+4*4))=0xa076fc1a;
*((unsigned int *)((unsigned long)context_ptr+0x0000625c+4*5))=0x66c41081;
*((unsigned int *)((unsigned long)context_ptr+0x0000625c+4*6))=0x244fd27b;
*((unsigned int *)((unsigned long)context_ptr+0x0000625c+4*7))=0x9710b00b;
*((unsigned int *)((unsigned long)context_ptr+0x0000625c+4*8))=0x4a641c11;
*((unsigned int *)((unsigned long)context_ptr+0x0000625c+4*9))=0xf6f2f11b;
*((unsigned int *)((unsigned long)context_ptr+0x0000625c+4*10))=0x6790e8fa;
*((unsigned int *)((unsigned long)context_ptr+0x00003408))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003408+4*1))=0x000063a4;
*((unsigned int *)((unsigned long)context_ptr+0x00003408+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003408+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003408+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003408+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000408))=0x04c0002c;
*((unsigned int *)((unsigned long)context_ptr+0x00000408+4*1))=0x0000625c;
*((unsigned int *)((unsigned long)context_ptr+0x00000408+4*2))=0x00006394;
*((unsigned int *)((unsigned long)context_ptr+0x00000408+4*3))=0x0222002c;
*((unsigned int *)((unsigned long)context_ptr+0x00000408+4*4))=0x03a32621;
*((unsigned int *)((unsigned long)context_ptr+0x00000408+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000000b4&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000063b8,"\x1b\x74\x6f\x56\xa3\x88\x6f\x27\x7b\x96\x04\xe4\x2d\xdd\x40\xa5\x23\xb6\xfc\xbe",20))
printf("strip: 1b746f56a3886f27, Pass\n");
else
printf("strip: 1b746f56a3886f27, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000063b8))=0x016a0a02;
*((unsigned int *)((unsigned long)context_ptr+0x000063b8+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000063b8+4*2))=0x0202002d;
*((unsigned int *)((unsigned long)context_ptr+0x000063b8+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x00006288))=0x903ea732;
*((unsigned int *)((unsigned long)context_ptr+0x00006288+4*1))=0xa251aac3;
*((unsigned int *)((unsigned long)context_ptr+0x00006288+4*2))=0xa17505a0;
*((unsigned int *)((unsigned long)context_ptr+0x00006288+4*3))=0x02e92961;
*((unsigned int *)((unsigned long)context_ptr+0x00006288+4*4))=0xe9fd2add;
*((unsigned int *)((unsigned long)context_ptr+0x00006288+4*5))=0xddaac417;
*((unsigned int *)((unsigned long)context_ptr+0x00006288+4*6))=0xbcca4f7f;
*((unsigned int *)((unsigned long)context_ptr+0x00006288+4*7))=0x7fc4fc89;
*((unsigned int *)((unsigned long)context_ptr+0x00006288+4*8))=0x0cd781ed;
*((unsigned int *)((unsigned long)context_ptr+0x00006288+4*9))=0x233b3621;
*((unsigned int *)((unsigned long)context_ptr+0x00006288+4*10))=0xb9978f0a;
*((unsigned int *)((unsigned long)context_ptr+0x00006288+4*11))=0x0000009d;
*((unsigned int *)((unsigned long)context_ptr+0x00003420))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003420+4*1))=0x000062b8;
*((unsigned int *)((unsigned long)context_ptr+0x00003420+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003420+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003420+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003420+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000420))=0x04c0002d;
*((unsigned int *)((unsigned long)context_ptr+0x00000420+4*1))=0x00006288;
*((unsigned int *)((unsigned long)context_ptr+0x00000420+4*2))=0x000063b8;
*((unsigned int *)((unsigned long)context_ptr+0x00000420+4*3))=0x0222002d;
*((unsigned int *)((unsigned long)context_ptr+0x00000420+4*4))=0x00399a6d;
*((unsigned int *)((unsigned long)context_ptr+0x00000420+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000000ba&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000063cc,"\xa8\xa2\x66\x47\xe3\x74\xf9\xbc\x54\x0a\xab\xf6\x23\x04\x0c\xe0\xfb\x90\x12\x4f",20))
printf("strip: a8a26647e374f9bc, Pass\n");
else
printf("strip: a8a26647e374f9bc, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006040))=0x016a0a02;
*((unsigned int *)((unsigned long)context_ptr+0x00006040+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006040+4*2))=0x0202002e;
*((unsigned int *)((unsigned long)context_ptr+0x00006040+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x000064a0))=0x0d2caf15;
*((unsigned int *)((unsigned long)context_ptr+0x000064a0+4*1))=0x0e55f740;
*((unsigned int *)((unsigned long)context_ptr+0x000064a0+4*2))=0x79482cab;
*((unsigned int *)((unsigned long)context_ptr+0x000064a0+4*3))=0xc2ec4d8a;
*((unsigned int *)((unsigned long)context_ptr+0x000064a0+4*4))=0xd4d113a0;
*((unsigned int *)((unsigned long)context_ptr+0x000064a0+4*5))=0xe62cd4ce;
*((unsigned int *)((unsigned long)context_ptr+0x000064a0+4*6))=0x2800434b;
*((unsigned int *)((unsigned long)context_ptr+0x000064a0+4*7))=0x0cdf3b58;
*((unsigned int *)((unsigned long)context_ptr+0x000064a0+4*8))=0xd5dd6071;
*((unsigned int *)((unsigned long)context_ptr+0x000064a0+4*9))=0x4075ad53;
*((unsigned int *)((unsigned long)context_ptr+0x000064a0+4*10))=0xbcb277b2;
*((unsigned int *)((unsigned long)context_ptr+0x000064a0+4*11))=0x0000438f;
*((unsigned int *)((unsigned long)context_ptr+0x00003438))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003438+4*1))=0x000063c8;
*((unsigned int *)((unsigned long)context_ptr+0x00003438+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003438+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003438+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003438+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000438))=0x04c0002e;
*((unsigned int *)((unsigned long)context_ptr+0x00000438+4*1))=0x000064a0;
*((unsigned int *)((unsigned long)context_ptr+0x00000438+4*2))=0x00006040;
*((unsigned int *)((unsigned long)context_ptr+0x00000438+4*3))=0x0222002e;
*((unsigned int *)((unsigned long)context_ptr+0x00000438+4*4))=0x06c50ccc;
*((unsigned int *)((unsigned long)context_ptr+0x00000438+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000000c0&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006060,"\xc8\x2b\xec\xfb\x62\xc7\x4a\x2a\x89\xc1\xef\xfa\x84\x77\xd9\xc6\xfd\x4f\x81\x81",20))
printf("strip: c82becfb62c74a2a, Pass\n");
else
printf("strip: c82becfb62c74a2a, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006030))=0x016a0a02;
*((unsigned int *)((unsigned long)context_ptr+0x00006030+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006030+4*2))=0x0202002f;
*((unsigned int *)((unsigned long)context_ptr+0x00006030+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x000064d0))=0x2a18a095;
*((unsigned int *)((unsigned long)context_ptr+0x000064d0+4*1))=0x6b2f4341;
*((unsigned int *)((unsigned long)context_ptr+0x000064d0+4*2))=0x2ddb2618;
*((unsigned int *)((unsigned long)context_ptr+0x000064d0+4*3))=0x44cb1472;
*((unsigned int *)((unsigned long)context_ptr+0x000064d0+4*4))=0x3469d1a9;
*((unsigned int *)((unsigned long)context_ptr+0x000064d0+4*5))=0xa8987528;
*((unsigned int *)((unsigned long)context_ptr+0x000064d0+4*6))=0x22003e96;
*((unsigned int *)((unsigned long)context_ptr+0x000064d0+4*7))=0xfa91f870;
*((unsigned int *)((unsigned long)context_ptr+0x000064d0+4*8))=0xb04afed7;
*((unsigned int *)((unsigned long)context_ptr+0x000064d0+4*9))=0x679dde6e;
*((unsigned int *)((unsigned long)context_ptr+0x000064d0+4*10))=0x6c7ed7f1;
*((unsigned int *)((unsigned long)context_ptr+0x000064d0+4*11))=0x004f6767;
*((unsigned int *)((unsigned long)context_ptr+0x00003450))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003450+4*1))=0x00006060;
*((unsigned int *)((unsigned long)context_ptr+0x00003450+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003450+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003450+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003450+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000450))=0x04c0002f;
*((unsigned int *)((unsigned long)context_ptr+0x00000450+4*1))=0x000064d0;
*((unsigned int *)((unsigned long)context_ptr+0x00000450+4*2))=0x00006030;
*((unsigned int *)((unsigned long)context_ptr+0x00000450+4*3))=0x0222002f;
*((unsigned int *)((unsigned long)context_ptr+0x00000450+4*4))=0x01f32140;
*((unsigned int *)((unsigned long)context_ptr+0x00000450+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000000c6&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006084,"\x5b\x4e\xd1\xe8\x5a\x9f\xfd\x8f\x86\x8f\x8e\x90\xbc\xa1\xeb\x49\x5d\x12\xb2\x49",20))
printf("strip: 5b4ed1e85a9ffd8f, Pass\n");
else
printf("strip: 5b4ed1e85a9ffd8f, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006050))=0x016a0a02;
*((unsigned int *)((unsigned long)context_ptr+0x00006050+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006050+4*2))=0x02020030;
*((unsigned int *)((unsigned long)context_ptr+0x00006050+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x000062cc))=0xf1472f49;
*((unsigned int *)((unsigned long)context_ptr+0x000062cc+4*1))=0x9855695f;
*((unsigned int *)((unsigned long)context_ptr+0x000062cc+4*2))=0x8e1b4286;
*((unsigned int *)((unsigned long)context_ptr+0x000062cc+4*3))=0x6c570e8e;
*((unsigned int *)((unsigned long)context_ptr+0x000062cc+4*4))=0xcdab517b;
*((unsigned int *)((unsigned long)context_ptr+0x000062cc+4*5))=0x97aa6b1e;
*((unsigned int *)((unsigned long)context_ptr+0x000062cc+4*6))=0xe38bdedf;
*((unsigned int *)((unsigned long)context_ptr+0x000062cc+4*7))=0x620226ce;
*((unsigned int *)((unsigned long)context_ptr+0x000062cc+4*8))=0x84cf075d;
*((unsigned int *)((unsigned long)context_ptr+0x000062cc+4*9))=0x66ced5f9;
*((unsigned int *)((unsigned long)context_ptr+0x000062cc+4*10))=0x8d1ab6f1;
*((unsigned int *)((unsigned long)context_ptr+0x000062cc+4*11))=0x0a67a436;
*((unsigned int *)((unsigned long)context_ptr+0x00003468))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003468+4*1))=0x00006084;
*((unsigned int *)((unsigned long)context_ptr+0x00003468+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003468+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003468+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003468+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000468))=0x04c00030;
*((unsigned int *)((unsigned long)context_ptr+0x00000468+4*1))=0x000062cc;
*((unsigned int *)((unsigned long)context_ptr+0x00000468+4*2))=0x00006050;
*((unsigned int *)((unsigned long)context_ptr+0x00000468+4*3))=0x02220030;
*((unsigned int *)((unsigned long)context_ptr+0x00000468+4*4))=0x0a30047c;
*((unsigned int *)((unsigned long)context_ptr+0x00000468+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000000cc&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006400,"\x3c\xdf\xf2\xe9\xdc\xf1\xf3\xd1\xd9\x67\xe8\xdd\xf2\x16\xf8\xeb\xc4\xec\xc7\x8c",20))
printf("strip: 3cdff2e9dcf1f3d1, Pass\n");
else
printf("strip: 3cdff2e9dcf1f3d1, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006074))=0x016a0a02;
*((unsigned int *)((unsigned long)context_ptr+0x00006074+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006074+4*2))=0x02020031;
*((unsigned int *)((unsigned long)context_ptr+0x00006074+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x000063dc))=0x4e46db58;
*((unsigned int *)((unsigned long)context_ptr+0x000063dc+4*1))=0x3936fade;
*((unsigned int *)((unsigned long)context_ptr+0x000063dc+4*2))=0x6dd00694;
*((unsigned int *)((unsigned long)context_ptr+0x000063dc+4*3))=0x8ccb06bb;
*((unsigned int *)((unsigned long)context_ptr+0x000063dc+4*4))=0x9f680c05;
*((unsigned int *)((unsigned long)context_ptr+0x000063dc+4*5))=0x61e6a473;
*((unsigned int *)((unsigned long)context_ptr+0x000063dc+4*6))=0x560bcb6b;
*((unsigned int *)((unsigned long)context_ptr+0x000063dc+4*7))=0xa9aca70f;
*((unsigned int *)((unsigned long)context_ptr+0x000063dc+4*8))=0xa103be9e;
*((unsigned int *)((unsigned long)context_ptr+0x000063dc+4*9))=0x08c1d5a1;
*((unsigned int *)((unsigned long)context_ptr+0x000063dc+4*10))=0x1b476997;
*((unsigned int *)((unsigned long)context_ptr+0x000063dc+4*11))=0x7b3d271f;
*((unsigned int *)((unsigned long)context_ptr+0x000063dc+4*12))=0x0000009a;
*((unsigned int *)((unsigned long)context_ptr+0x00003480))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003480+4*1))=0x000062fc;
*((unsigned int *)((unsigned long)context_ptr+0x00003480+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003480+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003480+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003480+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000480))=0x04c00031;
*((unsigned int *)((unsigned long)context_ptr+0x00000480+4*1))=0x000063dc;
*((unsigned int *)((unsigned long)context_ptr+0x00000480+4*2))=0x00006074;
*((unsigned int *)((unsigned long)context_ptr+0x00000480+4*3))=0x02220031;
*((unsigned int *)((unsigned long)context_ptr+0x00000480+4*4))=0x085a53a4;
*((unsigned int *)((unsigned long)context_ptr+0x00000480+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000000d2&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006310,"\x46\x97\x06\x76\x75\xda\x87\x9a\x07\xee\x08\xa3\x9a\x9a\x1f\x58\x36\x53\x42\x7a",20))
printf("strip: 4697067675da879a, Pass\n");
else
printf("strip: 4697067675da879a, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006098))=0x016a0a02;
*((unsigned int *)((unsigned long)context_ptr+0x00006098+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006098+4*2))=0x02020032;
*((unsigned int *)((unsigned long)context_ptr+0x00006098+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x000060a8))=0x9d261603;
*((unsigned int *)((unsigned long)context_ptr+0x000060a8+4*1))=0x55dc2a8f;
*((unsigned int *)((unsigned long)context_ptr+0x000060a8+4*2))=0x7cc04a23;
*((unsigned int *)((unsigned long)context_ptr+0x000060a8+4*3))=0x3f9e44a3;
*((unsigned int *)((unsigned long)context_ptr+0x000060a8+4*4))=0x4d71b703;
*((unsigned int *)((unsigned long)context_ptr+0x000060a8+4*5))=0xf8ce6186;
*((unsigned int *)((unsigned long)context_ptr+0x000060a8+4*6))=0x02a709a6;
*((unsigned int *)((unsigned long)context_ptr+0x000060a8+4*7))=0x06dd1766;
*((unsigned int *)((unsigned long)context_ptr+0x000060a8+4*8))=0x428276ad;
*((unsigned int *)((unsigned long)context_ptr+0x000060a8+4*9))=0x7d736e60;
*((unsigned int *)((unsigned long)context_ptr+0x000060a8+4*10))=0x84dca1d5;
*((unsigned int *)((unsigned long)context_ptr+0x000060a8+4*11))=0xbcb6a086;
*((unsigned int *)((unsigned long)context_ptr+0x000060a8+4*12))=0x0000668f;
*((unsigned int *)((unsigned long)context_ptr+0x00003498))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003498+4*1))=0x00006310;
*((unsigned int *)((unsigned long)context_ptr+0x00003498+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003498+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003498+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003498+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000498))=0x04c00032;
*((unsigned int *)((unsigned long)context_ptr+0x00000498+4*1))=0x000060a8;
*((unsigned int *)((unsigned long)context_ptr+0x00000498+4*2))=0x00006098;
*((unsigned int *)((unsigned long)context_ptr+0x00000498+4*3))=0x02220032;
*((unsigned int *)((unsigned long)context_ptr+0x00000498+4*4))=0x00f33130;
*((unsigned int *)((unsigned long)context_ptr+0x00000498+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000000d8&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006414,"\xe6\x5a\xb5\xe4\xae\x83\x0e\xf0\x81\xb6\x3c\x82\xf2\x90\xdc\xc1\x05\x5d\xa6\x77",20))
printf("strip: e65ab5e4ae830ef0, Pass\n");
else
printf("strip: e65ab5e4ae830ef0, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006324))=0x016a0a02;
*((unsigned int *)((unsigned long)context_ptr+0x00006324+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006324+4*2))=0x02020033;
*((unsigned int *)((unsigned long)context_ptr+0x00006324+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x000060dc))=0x2281b971;
*((unsigned int *)((unsigned long)context_ptr+0x000060dc+4*1))=0x8eedb88a;
*((unsigned int *)((unsigned long)context_ptr+0x000060dc+4*2))=0x48b18343;
*((unsigned int *)((unsigned long)context_ptr+0x000060dc+4*3))=0x344c3121;
*((unsigned int *)((unsigned long)context_ptr+0x000060dc+4*4))=0xb06f0a4b;
*((unsigned int *)((unsigned long)context_ptr+0x000060dc+4*5))=0x6b1a2a02;
*((unsigned int *)((unsigned long)context_ptr+0x000060dc+4*6))=0x5a6644df;
*((unsigned int *)((unsigned long)context_ptr+0x000060dc+4*7))=0x0a371727;
*((unsigned int *)((unsigned long)context_ptr+0x000060dc+4*8))=0xfd47c264;
*((unsigned int *)((unsigned long)context_ptr+0x000060dc+4*9))=0x9191c181;
*((unsigned int *)((unsigned long)context_ptr+0x000060dc+4*10))=0x2934c8c8;
*((unsigned int *)((unsigned long)context_ptr+0x000060dc+4*11))=0x3b143b2f;
*((unsigned int *)((unsigned long)context_ptr+0x000060dc+4*12))=0x0007a165;
*((unsigned int *)((unsigned long)context_ptr+0x000034b0))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x000034b0+4*1))=0x00006410;
*((unsigned int *)((unsigned long)context_ptr+0x000034b0+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000034b0+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000034b0+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000034b0+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x000004b0))=0x04c00033;
*((unsigned int *)((unsigned long)context_ptr+0x000004b0+4*1))=0x000060dc;
*((unsigned int *)((unsigned long)context_ptr+0x000004b0+4*2))=0x00006324;
*((unsigned int *)((unsigned long)context_ptr+0x000004b0+4*3))=0x02220033;
*((unsigned int *)((unsigned long)context_ptr+0x000004b0+4*4))=0x0e439d47;
*((unsigned int *)((unsigned long)context_ptr+0x000004b0+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000000de&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006428,"\x6b\x67\xfa\x99\x2f\xb7\xaa\x9f\x49\xd3\x7f\x75\xff\x04\xb4\x42\xd7\x7a\xd9\x5e",20))
printf("strip: 6b67fa992fb7aa9f, Pass\n");
else
printf("strip: 6b67fa992fb7aa9f, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006334))=0x016a0a02;
*((unsigned int *)((unsigned long)context_ptr+0x00006334+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006334+4*2))=0x02020034;
*((unsigned int *)((unsigned long)context_ptr+0x00006334+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x00006500))=0xe6a40147;
*((unsigned int *)((unsigned long)context_ptr+0x00006500+4*1))=0x08b36f5a;
*((unsigned int *)((unsigned long)context_ptr+0x00006500+4*2))=0x0ba6c53f;
*((unsigned int *)((unsigned long)context_ptr+0x00006500+4*3))=0xf01d9860;
*((unsigned int *)((unsigned long)context_ptr+0x00006500+4*4))=0x40119b2c;
*((unsigned int *)((unsigned long)context_ptr+0x00006500+4*5))=0xe4fac325;
*((unsigned int *)((unsigned long)context_ptr+0x00006500+4*6))=0xa8e8a437;
*((unsigned int *)((unsigned long)context_ptr+0x00006500+4*7))=0xa554720f;
*((unsigned int *)((unsigned long)context_ptr+0x00006500+4*8))=0x0e0ca80f;
*((unsigned int *)((unsigned long)context_ptr+0x00006500+4*9))=0x43c4dd3a;
*((unsigned int *)((unsigned long)context_ptr+0x00006500+4*10))=0x8eee4202;
*((unsigned int *)((unsigned long)context_ptr+0x00006500+4*11))=0xd8a1b914;
*((unsigned int *)((unsigned long)context_ptr+0x00006500+4*12))=0xe0add8fa;
*((unsigned int *)((unsigned long)context_ptr+0x000034c8))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x000034c8+4*1))=0x00006424;
*((unsigned int *)((unsigned long)context_ptr+0x000034c8+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000034c8+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000034c8+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000034c8+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x000004c8))=0x04c00034;
*((unsigned int *)((unsigned long)context_ptr+0x000004c8+4*1))=0x00006500;
*((unsigned int *)((unsigned long)context_ptr+0x000004c8+4*2))=0x00006334;
*((unsigned int *)((unsigned long)context_ptr+0x000004c8+4*3))=0x02220034;
*((unsigned int *)((unsigned long)context_ptr+0x000004c8+4*4))=0x083c8e37;
*((unsigned int *)((unsigned long)context_ptr+0x000004c8+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000000e4&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006164,"\xc3\xa8\x8e\xb3\xe3\xf9\xd3\xc1\x22\x09\x41\x1f\x19\xe7\x04\x34\xe3\x86\xcc\x7c",20))
printf("strip: c3a88eb3e3f9d3c1, Pass\n");
else
printf("strip: c3a88eb3e3f9d3c1, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006344))=0x016a0a02;
*((unsigned int *)((unsigned long)context_ptr+0x00006344+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006344+4*2))=0x02020035;
*((unsigned int *)((unsigned long)context_ptr+0x00006344+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x00006110))=0x6cd0cbe6;
*((unsigned int *)((unsigned long)context_ptr+0x00006110+4*1))=0x6c50bae2;
*((unsigned int *)((unsigned long)context_ptr+0x00006110+4*2))=0x605fd93d;
*((unsigned int *)((unsigned long)context_ptr+0x00006110+4*3))=0xd1488f63;
*((unsigned int *)((unsigned long)context_ptr+0x00006110+4*4))=0x6011caab;
*((unsigned int *)((unsigned long)context_ptr+0x00006110+4*5))=0xda563135;
*((unsigned int *)((unsigned long)context_ptr+0x00006110+4*6))=0xc9d91060;
*((unsigned int *)((unsigned long)context_ptr+0x00006110+4*7))=0x5b270b8c;
*((unsigned int *)((unsigned long)context_ptr+0x00006110+4*8))=0xf7c44c6a;
*((unsigned int *)((unsigned long)context_ptr+0x00006110+4*9))=0x23732b6d;
*((unsigned int *)((unsigned long)context_ptr+0x00006110+4*10))=0x5afb6876;
*((unsigned int *)((unsigned long)context_ptr+0x00006110+4*11))=0xb2b4ee1f;
*((unsigned int *)((unsigned long)context_ptr+0x00006110+4*12))=0x4ab63453;
*((unsigned int *)((unsigned long)context_ptr+0x00006110+4*13))=0x0000009d;
*((unsigned int *)((unsigned long)context_ptr+0x000034e0))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x000034e0+4*1))=0x00006148;
*((unsigned int *)((unsigned long)context_ptr+0x000034e0+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000034e0+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000034e0+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000034e0+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x000004e0))=0x04c00035;
*((unsigned int *)((unsigned long)context_ptr+0x000004e0+4*1))=0x00006110;
*((unsigned int *)((unsigned long)context_ptr+0x000004e0+4*2))=0x00006344;
*((unsigned int *)((unsigned long)context_ptr+0x000004e0+4*3))=0x02220035;
*((unsigned int *)((unsigned long)context_ptr+0x000004e0+4*4))=0x0a2bbb49;
*((unsigned int *)((unsigned long)context_ptr+0x000004e0+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000000ea&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x0000643c,"\x40\x7e\xf6\x20\xac\x97\xe5\xea\xc9\x8d\x14\x2f\xd1\x2a\xf7\x3e\xaa\x11\x98\xea",20))
printf("strip: 407ef620ac97e5ea, Pass\n");
else
printf("strip: 407ef620ac97e5ea, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006354))=0x016a0a02;
*((unsigned int *)((unsigned long)context_ptr+0x00006354+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006354+4*2))=0x02020036;
*((unsigned int *)((unsigned long)context_ptr+0x00006354+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x0000615c))=0x6fb388c9;
*((unsigned int *)((unsigned long)context_ptr+0x0000615c+4*1))=0x41ffeaeb;
*((unsigned int *)((unsigned long)context_ptr+0x0000615c+4*2))=0x655e9d37;
*((unsigned int *)((unsigned long)context_ptr+0x0000615c+4*3))=0xcedaadc5;
*((unsigned int *)((unsigned long)context_ptr+0x0000615c+4*4))=0xca6c1a7d;
*((unsigned int *)((unsigned long)context_ptr+0x0000615c+4*5))=0xd166d75d;
*((unsigned int *)((unsigned long)context_ptr+0x0000615c+4*6))=0xec01abc2;
*((unsigned int *)((unsigned long)context_ptr+0x0000615c+4*7))=0xdc03175d;
*((unsigned int *)((unsigned long)context_ptr+0x0000615c+4*8))=0xeffc966b;
*((unsigned int *)((unsigned long)context_ptr+0x0000615c+4*9))=0x6ba4bba1;
*((unsigned int *)((unsigned long)context_ptr+0x0000615c+4*10))=0x364c351d;
*((unsigned int *)((unsigned long)context_ptr+0x0000615c+4*11))=0xb23c34ee;
*((unsigned int *)((unsigned long)context_ptr+0x0000615c+4*12))=0xd04ba3f8;
*((unsigned int *)((unsigned long)context_ptr+0x0000615c+4*13))=0x0000a628;
*((unsigned int *)((unsigned long)context_ptr+0x000034f8))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x000034f8+4*1))=0x00006438;
*((unsigned int *)((unsigned long)context_ptr+0x000034f8+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000034f8+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000034f8+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000034f8+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x000004f8))=0x04c00036;
*((unsigned int *)((unsigned long)context_ptr+0x000004f8+4*1))=0x0000615c;
*((unsigned int *)((unsigned long)context_ptr+0x000004f8+4*2))=0x00006354;
*((unsigned int *)((unsigned long)context_ptr+0x000004f8+4*3))=0x02220036;
*((unsigned int *)((unsigned long)context_ptr+0x000004f8+4*4))=0x07c63770;
*((unsigned int *)((unsigned long)context_ptr+0x000004f8+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000000f0&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006450,"\x83\xb5\xd5\x80\x22\xce\xb8\x9d\x9c\x58\xbe\x70\xb9\x22\xab\x70\x36\x32\x50\xe5",20))
printf("strip: 83b5d58022ceb89d, Pass\n");
else
printf("strip: 83b5d58022ceb89d, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006364))=0x016a0a02;
*((unsigned int *)((unsigned long)context_ptr+0x00006364+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006364+4*2))=0x02020037;
*((unsigned int *)((unsigned long)context_ptr+0x00006364+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x00006534))=0x45fefbbd;
*((unsigned int *)((unsigned long)context_ptr+0x00006534+4*1))=0x26b7eb58;
*((unsigned int *)((unsigned long)context_ptr+0x00006534+4*2))=0x9d3431c9;
*((unsigned int *)((unsigned long)context_ptr+0x00006534+4*3))=0xb0296135;
*((unsigned int *)((unsigned long)context_ptr+0x00006534+4*4))=0xfc18e89d;
*((unsigned int *)((unsigned long)context_ptr+0x00006534+4*5))=0xf259074e;
*((unsigned int *)((unsigned long)context_ptr+0x00006534+4*6))=0xad467e4a;
*((unsigned int *)((unsigned long)context_ptr+0x00006534+4*7))=0xa01bec5f;
*((unsigned int *)((unsigned long)context_ptr+0x00006534+4*8))=0xc6885efc;
*((unsigned int *)((unsigned long)context_ptr+0x00006534+4*9))=0xe1da7925;
*((unsigned int *)((unsigned long)context_ptr+0x00006534+4*10))=0xae88cc86;
*((unsigned int *)((unsigned long)context_ptr+0x00006534+4*11))=0x0b1713cf;
*((unsigned int *)((unsigned long)context_ptr+0x00006534+4*12))=0x5b8138e5;
*((unsigned int *)((unsigned long)context_ptr+0x00006534+4*13))=0x00de5963;
*((unsigned int *)((unsigned long)context_ptr+0x00003510))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003510+4*1))=0x0000644c;
*((unsigned int *)((unsigned long)context_ptr+0x00003510+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003510+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003510+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003510+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000510))=0x04c00037;
*((unsigned int *)((unsigned long)context_ptr+0x00000510+4*1))=0x00006534;
*((unsigned int *)((unsigned long)context_ptr+0x00000510+4*2))=0x00006364;
*((unsigned int *)((unsigned long)context_ptr+0x00000510+4*3))=0x02220037;
*((unsigned int *)((unsigned long)context_ptr+0x00000510+4*4))=0x080cd31c;
*((unsigned int *)((unsigned long)context_ptr+0x00000510+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000000f6&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006464,"\x1f\xa6\xdb\xb1\xeb\xca\x07\xf6\xe7\x5d\xec\xa8\xee\xd9\x94\xe5\x12\x45\xf1\xe0",20))
printf("strip: 1fa6dbb1ebca07f6, Pass\n");
else
printf("strip: 1fa6dbb1ebca07f6, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006374))=0x016a0a02;
*((unsigned int *)((unsigned long)context_ptr+0x00006374+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006374+4*2))=0x02020038;
*((unsigned int *)((unsigned long)context_ptr+0x00006374+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x00006194))=0x50c89075;
*((unsigned int *)((unsigned long)context_ptr+0x00006194+4*1))=0xc67a306d;
*((unsigned int *)((unsigned long)context_ptr+0x00006194+4*2))=0x2928d80a;
*((unsigned int *)((unsigned long)context_ptr+0x00006194+4*3))=0xd9afbd36;
*((unsigned int *)((unsigned long)context_ptr+0x00006194+4*4))=0x2929e730;
*((unsigned int *)((unsigned long)context_ptr+0x00006194+4*5))=0xacc2556b;
*((unsigned int *)((unsigned long)context_ptr+0x00006194+4*6))=0x1a861c0f;
*((unsigned int *)((unsigned long)context_ptr+0x00006194+4*7))=0x029eb78f;
*((unsigned int *)((unsigned long)context_ptr+0x00006194+4*8))=0x867541ef;
*((unsigned int *)((unsigned long)context_ptr+0x00006194+4*9))=0xd6a84ffa;
*((unsigned int *)((unsigned long)context_ptr+0x00006194+4*10))=0x21473990;
*((unsigned int *)((unsigned long)context_ptr+0x00006194+4*11))=0xeb547ebb;
*((unsigned int *)((unsigned long)context_ptr+0x00006194+4*12))=0x649e2033;
*((unsigned int *)((unsigned long)context_ptr+0x00006194+4*13))=0x049b9661;
*((unsigned int *)((unsigned long)context_ptr+0x00003528))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003528+4*1))=0x00006460;
*((unsigned int *)((unsigned long)context_ptr+0x00003528+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003528+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003528+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003528+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000528))=0x04c00038;
*((unsigned int *)((unsigned long)context_ptr+0x00000528+4*1))=0x00006194;
*((unsigned int *)((unsigned long)context_ptr+0x00000528+4*2))=0x00006374;
*((unsigned int *)((unsigned long)context_ptr+0x00000528+4*3))=0x02220038;
*((unsigned int *)((unsigned long)context_ptr+0x00000528+4*4))=0x008adb4a;
*((unsigned int *)((unsigned long)context_ptr+0x00000528+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000000fc&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006478,"\xcb\x6d\xd3\x4f\x80\x41\x29\xd5\xc2\xc9\xba\x75\xfc\xfa\xd4\x8b\xb3\x21\xd5\xfa",20))
printf("strip: cb6dd34f804129d5, Pass\n");
else
printf("strip: cb6dd34f804129d5, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006474))=0x016a0a02;
*((unsigned int *)((unsigned long)context_ptr+0x00006474+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006474+4*2))=0x02020039;
*((unsigned int *)((unsigned long)context_ptr+0x00006474+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x000061cc))=0xb2b5e99c;
*((unsigned int *)((unsigned long)context_ptr+0x000061cc+4*1))=0xdd8bb8ec;
*((unsigned int *)((unsigned long)context_ptr+0x000061cc+4*2))=0x7f39edeb;
*((unsigned int *)((unsigned long)context_ptr+0x000061cc+4*3))=0x9a690ca3;
*((unsigned int *)((unsigned long)context_ptr+0x000061cc+4*4))=0x50520ad7;
*((unsigned int *)((unsigned long)context_ptr+0x000061cc+4*5))=0x7dfd5329;
*((unsigned int *)((unsigned long)context_ptr+0x000061cc+4*6))=0xebfcc912;
*((unsigned int *)((unsigned long)context_ptr+0x000061cc+4*7))=0x92d2679c;
*((unsigned int *)((unsigned long)context_ptr+0x000061cc+4*8))=0xb279aa2d;
*((unsigned int *)((unsigned long)context_ptr+0x000061cc+4*9))=0x4a4d4a34;
*((unsigned int *)((unsigned long)context_ptr+0x000061cc+4*10))=0x03aa59b4;
*((unsigned int *)((unsigned long)context_ptr+0x000061cc+4*11))=0x0cea7706;
*((unsigned int *)((unsigned long)context_ptr+0x000061cc+4*12))=0x124fff15;
*((unsigned int *)((unsigned long)context_ptr+0x000061cc+4*13))=0x96391410;
*((unsigned int *)((unsigned long)context_ptr+0x000061cc+4*14))=0x00000008;
*((unsigned int *)((unsigned long)context_ptr+0x00003540))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003540+4*1))=0x00006208;
*((unsigned int *)((unsigned long)context_ptr+0x00003540+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003540+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003540+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003540+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000540))=0x04c00039;
*((unsigned int *)((unsigned long)context_ptr+0x00000540+4*1))=0x000061cc;
*((unsigned int *)((unsigned long)context_ptr+0x00000540+4*2))=0x00006474;
*((unsigned int *)((unsigned long)context_ptr+0x00000540+4*3))=0x02220039;
*((unsigned int *)((unsigned long)context_ptr+0x00000540+4*4))=0x0556a666;
*((unsigned int *)((unsigned long)context_ptr+0x00000540+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000102&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x0000648c,"\x18\xb7\x66\x5e\xe5\xe5\x7a\x98\xc8\xd1\xbb\x27\x25\xfd\x88\x76\x3a\x9f\x7a\x04",20))
printf("strip: 18b7665ee5e57a98, Pass\n");
else
printf("strip: 18b7665ee5e57a98, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006384))=0x016a0a02;
*((unsigned int *)((unsigned long)context_ptr+0x00006384+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006384+4*2))=0x0202003a;
*((unsigned int *)((unsigned long)context_ptr+0x00006384+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x0000621c))=0x8c8a0fe1;
*((unsigned int *)((unsigned long)context_ptr+0x0000621c+4*1))=0xaa795edd;
*((unsigned int *)((unsigned long)context_ptr+0x0000621c+4*2))=0x3d73a239;
*((unsigned int *)((unsigned long)context_ptr+0x0000621c+4*3))=0x48ad973f;
*((unsigned int *)((unsigned long)context_ptr+0x0000621c+4*4))=0x9758f762;
*((unsigned int *)((unsigned long)context_ptr+0x0000621c+4*5))=0x5f3b6a74;
*((unsigned int *)((unsigned long)context_ptr+0x0000621c+4*6))=0xf4ff74d4;
*((unsigned int *)((unsigned long)context_ptr+0x0000621c+4*7))=0x09b42142;
*((unsigned int *)((unsigned long)context_ptr+0x0000621c+4*8))=0x753c4a32;
*((unsigned int *)((unsigned long)context_ptr+0x0000621c+4*9))=0x2e527cf3;
*((unsigned int *)((unsigned long)context_ptr+0x0000621c+4*10))=0x89380080;
*((unsigned int *)((unsigned long)context_ptr+0x0000621c+4*11))=0x4f555fdd;
*((unsigned int *)((unsigned long)context_ptr+0x0000621c+4*12))=0xace683dd;
*((unsigned int *)((unsigned long)context_ptr+0x0000621c+4*13))=0x0e156341;
*((unsigned int *)((unsigned long)context_ptr+0x0000621c+4*14))=0x000095ed;
*((unsigned int *)((unsigned long)context_ptr+0x00003558))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003558+4*1))=0x00006484;
*((unsigned int *)((unsigned long)context_ptr+0x00003558+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003558+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003558+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003558+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000558))=0x04c0003a;
*((unsigned int *)((unsigned long)context_ptr+0x00000558+4*1))=0x0000621c;
*((unsigned int *)((unsigned long)context_ptr+0x00000558+4*2))=0x00006384;
*((unsigned int *)((unsigned long)context_ptr+0x00000558+4*3))=0x0222003a;
*((unsigned int *)((unsigned long)context_ptr+0x00000558+4*4))=0x08f7575d;
*((unsigned int *)((unsigned long)context_ptr+0x00000558+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000108&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000063a4,"\x9c\x96\x01\x5a\xaf\xa2\x00\xf6\xfa\xd2\x17\x80\xb8\xa2\xe8\xed\x7f\xfc\x7e\xff",20))
printf("strip: 9c96015aafa200f6, Pass\n");
else
printf("strip: 9c96015aafa200f6, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006394))=0x016a0a02;
*((unsigned int *)((unsigned long)context_ptr+0x00006394+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006394+4*2))=0x0202003b;
*((unsigned int *)((unsigned long)context_ptr+0x00006394+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x0000656c))=0x29e92046;
*((unsigned int *)((unsigned long)context_ptr+0x0000656c+4*1))=0xc1dc8057;
*((unsigned int *)((unsigned long)context_ptr+0x0000656c+4*2))=0x3183fa97;
*((unsigned int *)((unsigned long)context_ptr+0x0000656c+4*3))=0x7e655f7d;
*((unsigned int *)((unsigned long)context_ptr+0x0000656c+4*4))=0xf0b38bd2;
*((unsigned int *)((unsigned long)context_ptr+0x0000656c+4*5))=0x9fcaba1e;
*((unsigned int *)((unsigned long)context_ptr+0x0000656c+4*6))=0x261850bb;
*((unsigned int *)((unsigned long)context_ptr+0x0000656c+4*7))=0x752e7ed5;
*((unsigned int *)((unsigned long)context_ptr+0x0000656c+4*8))=0x2f067b86;
*((unsigned int *)((unsigned long)context_ptr+0x0000656c+4*9))=0x4fc65799;
*((unsigned int *)((unsigned long)context_ptr+0x0000656c+4*10))=0x4d5290c9;
*((unsigned int *)((unsigned long)context_ptr+0x0000656c+4*11))=0xebc71267;
*((unsigned int *)((unsigned long)context_ptr+0x0000656c+4*12))=0x18c996a3;
*((unsigned int *)((unsigned long)context_ptr+0x0000656c+4*13))=0x9027afbf;
*((unsigned int *)((unsigned long)context_ptr+0x0000656c+4*14))=0x00143dcd;
*((unsigned int *)((unsigned long)context_ptr+0x00003570))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003570+4*1))=0x000063a4;
*((unsigned int *)((unsigned long)context_ptr+0x00003570+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003570+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003570+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003570+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000570))=0x04c0003b;
*((unsigned int *)((unsigned long)context_ptr+0x00000570+4*1))=0x0000656c;
*((unsigned int *)((unsigned long)context_ptr+0x00000570+4*2))=0x00006394;
*((unsigned int *)((unsigned long)context_ptr+0x00000570+4*3))=0x0222003b;
*((unsigned int *)((unsigned long)context_ptr+0x00000570+4*4))=0x06252370;
*((unsigned int *)((unsigned long)context_ptr+0x00000570+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000010e&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000062b8,"\x3e\x2c\x70\xf8\x9b\x86\x3d\xd6\x1d\x8a\x80\x1f\xfb\x37\x97\x9f\x83\x37\xdc\x74",20))
printf("strip: 3e2c70f89b863dd6, Pass\n");
else
printf("strip: 3e2c70f89b863dd6, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000063b8))=0x016a0a02;
*((unsigned int *)((unsigned long)context_ptr+0x000063b8+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000063b8+4*2))=0x0202003c;
*((unsigned int *)((unsigned long)context_ptr+0x000063b8+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x00006258))=0x2731a6f5;
*((unsigned int *)((unsigned long)context_ptr+0x00006258+4*1))=0x5e688756;
*((unsigned int *)((unsigned long)context_ptr+0x00006258+4*2))=0x8263a416;
*((unsigned int *)((unsigned long)context_ptr+0x00006258+4*3))=0xb54bfe0d;
*((unsigned int *)((unsigned long)context_ptr+0x00006258+4*4))=0x5a5f2bcd;
*((unsigned int *)((unsigned long)context_ptr+0x00006258+4*5))=0xa6c1a82b;
*((unsigned int *)((unsigned long)context_ptr+0x00006258+4*6))=0x7f6a17bc;
*((unsigned int *)((unsigned long)context_ptr+0x00006258+4*7))=0x868a74f7;
*((unsigned int *)((unsigned long)context_ptr+0x00006258+4*8))=0xeee4002d;
*((unsigned int *)((unsigned long)context_ptr+0x00006258+4*9))=0x92e12704;
*((unsigned int *)((unsigned long)context_ptr+0x00006258+4*10))=0x42cd8515;
*((unsigned int *)((unsigned long)context_ptr+0x00006258+4*11))=0x0164bc6c;
*((unsigned int *)((unsigned long)context_ptr+0x00006258+4*12))=0x6ab08d48;
*((unsigned int *)((unsigned long)context_ptr+0x00006258+4*13))=0xddf9b451;
*((unsigned int *)((unsigned long)context_ptr+0x00006258+4*14))=0x35a9207e;
*((unsigned int *)((unsigned long)context_ptr+0x00003588))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003588+4*1))=0x00006294;
*((unsigned int *)((unsigned long)context_ptr+0x00003588+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003588+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003588+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003588+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000588))=0x04c0003c;
*((unsigned int *)((unsigned long)context_ptr+0x00000588+4*1))=0x00006258;
*((unsigned int *)((unsigned long)context_ptr+0x00000588+4*2))=0x000063b8;
*((unsigned int *)((unsigned long)context_ptr+0x00000588+4*3))=0x0222003c;
*((unsigned int *)((unsigned long)context_ptr+0x00000588+4*4))=0x03922c73;
*((unsigned int *)((unsigned long)context_ptr+0x00000588+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000114&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000063c8,"\x84\x46\xe1\x7d\x82\xad\x93\x91\x80\x20\xa7\x1f\x2e\xcc\x82\x8b\x5f\xab\x46\xc3",20))
printf("strip: 8446e17d82ad9391, Pass\n");
else
printf("strip: 8446e17d82ad9391, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006040))=0x016a0a02;
*((unsigned int *)((unsigned long)context_ptr+0x00006040+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006040+4*2))=0x0202003d;
*((unsigned int *)((unsigned long)context_ptr+0x00006040+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x000065a8))=0x11202762;
*((unsigned int *)((unsigned long)context_ptr+0x000065a8+4*1))=0x775dde0a;
*((unsigned int *)((unsigned long)context_ptr+0x000065a8+4*2))=0x5b66cd6f;
*((unsigned int *)((unsigned long)context_ptr+0x000065a8+4*3))=0x75a862ad;
*((unsigned int *)((unsigned long)context_ptr+0x000065a8+4*4))=0xf1406791;
*((unsigned int *)((unsigned long)context_ptr+0x000065a8+4*5))=0xa249a296;
*((unsigned int *)((unsigned long)context_ptr+0x000065a8+4*6))=0x418a948d;
*((unsigned int *)((unsigned long)context_ptr+0x000065a8+4*7))=0x4d4f14a7;
*((unsigned int *)((unsigned long)context_ptr+0x000065a8+4*8))=0xda34006f;
*((unsigned int *)((unsigned long)context_ptr+0x000065a8+4*9))=0x839b03ca;
*((unsigned int *)((unsigned long)context_ptr+0x000065a8+4*10))=0x615cbd18;
*((unsigned int *)((unsigned long)context_ptr+0x000065a8+4*11))=0xd7d59b5d;
*((unsigned int *)((unsigned long)context_ptr+0x000065a8+4*12))=0x9f0fe550;
*((unsigned int *)((unsigned long)context_ptr+0x000065a8+4*13))=0x6a6af4b3;
*((unsigned int *)((unsigned long)context_ptr+0x000065a8+4*14))=0x59f757a0;
*((unsigned int *)((unsigned long)context_ptr+0x000065a8+4*15))=0x00000025;
*((unsigned int *)((unsigned long)context_ptr+0x000035a0))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x000035a0+4*1))=0x000063c8;
*((unsigned int *)((unsigned long)context_ptr+0x000035a0+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000035a0+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000035a0+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000035a0+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x000005a0))=0x04c0003d;
*((unsigned int *)((unsigned long)context_ptr+0x000005a0+4*1))=0x000065a8;
*((unsigned int *)((unsigned long)context_ptr+0x000005a0+4*2))=0x00006040;
*((unsigned int *)((unsigned long)context_ptr+0x000005a0+4*3))=0x0222003d;
*((unsigned int *)((unsigned long)context_ptr+0x000005a0+4*4))=0x0ff9ec8a;
*((unsigned int *)((unsigned long)context_ptr+0x000005a0+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000011a&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006060,"\xe9\x3d\x83\xaf\xed\x5d\x02\x2f\xc7\x32\x5e\xe9\x32\x1c\x83\x39\x40\xb7\x38\x8f",20))
printf("strip: e93d83afed5d022f, Pass\n");
else
printf("strip: e93d83afed5d022f, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006030))=0x016a0a02;
*((unsigned int *)((unsigned long)context_ptr+0x00006030+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006030+4*2))=0x0202003e;
*((unsigned int *)((unsigned long)context_ptr+0x00006030+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x00006498))=0x6ab2fea5;
*((unsigned int *)((unsigned long)context_ptr+0x00006498+4*1))=0x91737f8a;
*((unsigned int *)((unsigned long)context_ptr+0x00006498+4*2))=0xe7f61d4f;
*((unsigned int *)((unsigned long)context_ptr+0x00006498+4*3))=0x77e370b0;
*((unsigned int *)((unsigned long)context_ptr+0x00006498+4*4))=0xc42deca4;
*((unsigned int *)((unsigned long)context_ptr+0x00006498+4*5))=0x548f69ef;
*((unsigned int *)((unsigned long)context_ptr+0x00006498+4*6))=0x643e55ee;
*((unsigned int *)((unsigned long)context_ptr+0x00006498+4*7))=0xb6182818;
*((unsigned int *)((unsigned long)context_ptr+0x00006498+4*8))=0x4cb00955;
*((unsigned int *)((unsigned long)context_ptr+0x00006498+4*9))=0xee95eacf;
*((unsigned int *)((unsigned long)context_ptr+0x00006498+4*10))=0x05b664ec;
*((unsigned int *)((unsigned long)context_ptr+0x00006498+4*11))=0x4c91f7a1;
*((unsigned int *)((unsigned long)context_ptr+0x00006498+4*12))=0x724b618a;
*((unsigned int *)((unsigned long)context_ptr+0x00006498+4*13))=0x043d7939;
*((unsigned int *)((unsigned long)context_ptr+0x00006498+4*14))=0x0a4c6c05;
*((unsigned int *)((unsigned long)context_ptr+0x00006498+4*15))=0x000019d1;
*((unsigned int *)((unsigned long)context_ptr+0x000035b8))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x000035b8+4*1))=0x00006060;
*((unsigned int *)((unsigned long)context_ptr+0x000035b8+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000035b8+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000035b8+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000035b8+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x000005b8))=0x04c0003e;
*((unsigned int *)((unsigned long)context_ptr+0x000005b8+4*1))=0x00006498;
*((unsigned int *)((unsigned long)context_ptr+0x000005b8+4*2))=0x00006030;
*((unsigned int *)((unsigned long)context_ptr+0x000005b8+4*3))=0x0222003e;
*((unsigned int *)((unsigned long)context_ptr+0x000005b8+4*4))=0x0bc309d1;
*((unsigned int *)((unsigned long)context_ptr+0x000005b8+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000120&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006084,"\x64\xf5\x92\x80\x36\x5b\xb6\x09\xfc\xd2\x50\xe0\xac\x4a\xa1\x27\x7d\x38\x9a\x34",20))
printf("strip: 64f59280365bb609, Pass\n");
else
printf("strip: 64f59280365bb609, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006050))=0x016a0a02;
*((unsigned int *)((unsigned long)context_ptr+0x00006050+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006050+4*2))=0x0202003f;
*((unsigned int *)((unsigned long)context_ptr+0x00006050+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x000062a8))=0x12e09348;
*((unsigned int *)((unsigned long)context_ptr+0x000062a8+4*1))=0xe3d3b3d3;
*((unsigned int *)((unsigned long)context_ptr+0x000062a8+4*2))=0x9218aabe;
*((unsigned int *)((unsigned long)context_ptr+0x000062a8+4*3))=0x9b156f08;
*((unsigned int *)((unsigned long)context_ptr+0x000062a8+4*4))=0x15aabc08;
*((unsigned int *)((unsigned long)context_ptr+0x000062a8+4*5))=0xe8bec521;
*((unsigned int *)((unsigned long)context_ptr+0x000062a8+4*6))=0x79f43459;
*((unsigned int *)((unsigned long)context_ptr+0x000062a8+4*7))=0x39ce1791;
*((unsigned int *)((unsigned long)context_ptr+0x000062a8+4*8))=0x9a2876f3;
*((unsigned int *)((unsigned long)context_ptr+0x000062a8+4*9))=0x817c1c3f;
*((unsigned int *)((unsigned long)context_ptr+0x000062a8+4*10))=0xd337e6b6;
*((unsigned int *)((unsigned long)context_ptr+0x000062a8+4*11))=0x62c02074;
*((unsigned int *)((unsigned long)context_ptr+0x000062a8+4*12))=0x943f008f;
*((unsigned int *)((unsigned long)context_ptr+0x000062a8+4*13))=0x38862107;
*((unsigned int *)((unsigned long)context_ptr+0x000062a8+4*14))=0x5f2ae4b4;
*((unsigned int *)((unsigned long)context_ptr+0x000062a8+4*15))=0x00b6f012;
*((unsigned int *)((unsigned long)context_ptr+0x000035d0))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x000035d0+4*1))=0x00006084;
*((unsigned int *)((unsigned long)context_ptr+0x000035d0+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000035d0+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000035d0+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000035d0+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x000005d0))=0x04c0003f;
*((unsigned int *)((unsigned long)context_ptr+0x000005d0+4*1))=0x000062a8;
*((unsigned int *)((unsigned long)context_ptr+0x000005d0+4*2))=0x00006050;
*((unsigned int *)((unsigned long)context_ptr+0x000005d0+4*3))=0x0222003f;
*((unsigned int *)((unsigned long)context_ptr+0x000005d0+4*4))=0x09d2b0c2;
*((unsigned int *)((unsigned long)context_ptr+0x000005d0+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000126&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000062fc,"\x0c\x57\x15\x2e\x3b\x7d\x47\x3f\x00\xaf\xe5\xee\x63\x61\xd3\xff\x7f\x98\x1e\x18",20))
printf("strip: 0c57152e3b7d473f, Pass\n");
else
printf("strip: 0c57152e3b7d473f, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006074))=0x016a0a02;
*((unsigned int *)((unsigned long)context_ptr+0x00006074+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006074+4*2))=0x02020040;
*((unsigned int *)((unsigned long)context_ptr+0x00006074+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x000065e8))=0xc7809b0e;
*((unsigned int *)((unsigned long)context_ptr+0x000065e8+4*1))=0xd3cd8b79;
*((unsigned int *)((unsigned long)context_ptr+0x000065e8+4*2))=0xc5e51953;
*((unsigned int *)((unsigned long)context_ptr+0x000065e8+4*3))=0x67dd0f05;
*((unsigned int *)((unsigned long)context_ptr+0x000065e8+4*4))=0xfbff9001;
*((unsigned int *)((unsigned long)context_ptr+0x000065e8+4*5))=0xd12fbc3e;
*((unsigned int *)((unsigned long)context_ptr+0x000065e8+4*6))=0xd4afd19d;
*((unsigned int *)((unsigned long)context_ptr+0x000065e8+4*7))=0x1f2f4523;
*((unsigned int *)((unsigned long)context_ptr+0x000065e8+4*8))=0x58731538;
*((unsigned int *)((unsigned long)context_ptr+0x000065e8+4*9))=0x0bb33202;
*((unsigned int *)((unsigned long)context_ptr+0x000065e8+4*10))=0x09eadb04;
*((unsigned int *)((unsigned long)context_ptr+0x000065e8+4*11))=0xa0945b42;
*((unsigned int *)((unsigned long)context_ptr+0x000065e8+4*12))=0x606645f6;
*((unsigned int *)((unsigned long)context_ptr+0x000065e8+4*13))=0xa9e831d6;
*((unsigned int *)((unsigned long)context_ptr+0x000065e8+4*14))=0x0b32b87d;
*((unsigned int *)((unsigned long)context_ptr+0x000065e8+4*15))=0x9fdf5bdd;
*((unsigned int *)((unsigned long)context_ptr+0x000035e8))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x000035e8+4*1))=0x000062e8;
*((unsigned int *)((unsigned long)context_ptr+0x000035e8+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000035e8+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000035e8+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000035e8+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x000005e8))=0x04c00040;
*((unsigned int *)((unsigned long)context_ptr+0x000005e8+4*1))=0x000065e8;
*((unsigned int *)((unsigned long)context_ptr+0x000005e8+4*2))=0x00006074;
*((unsigned int *)((unsigned long)context_ptr+0x000005e8+4*3))=0x02220040;
*((unsigned int *)((unsigned long)context_ptr+0x000005e8+4*4))=0x04dc8b45;
*((unsigned int *)((unsigned long)context_ptr+0x000005e8+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000012c&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006310,"\x7e\xaa\x58\xee\x2d\x94\xb0\x10\xbd\x51\xb3\x6e\x20\xf8\x0f\x60\x86\x6c\x6c\xb5",20))
printf("strip: 7eaa58ee2d94b010, Pass\n");
else
printf("strip: 7eaa58ee2d94b010, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006098))=0x016a0a02;
*((unsigned int *)((unsigned long)context_ptr+0x00006098+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006098+4*2))=0x02020041;
*((unsigned int *)((unsigned long)context_ptr+0x00006098+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x00006628))=0xfdc8a886;
*((unsigned int *)((unsigned long)context_ptr+0x00006628+4*1))=0x3132f146;
*((unsigned int *)((unsigned long)context_ptr+0x00006628+4*2))=0xe7e614cb;
*((unsigned int *)((unsigned long)context_ptr+0x00006628+4*3))=0x127ab2b3;
*((unsigned int *)((unsigned long)context_ptr+0x00006628+4*4))=0x4e96c258;
*((unsigned int *)((unsigned long)context_ptr+0x00006628+4*5))=0xb388352c;
*((unsigned int *)((unsigned long)context_ptr+0x00006628+4*6))=0xa2b4c7f1;
*((unsigned int *)((unsigned long)context_ptr+0x00006628+4*7))=0x66c89cff;
*((unsigned int *)((unsigned long)context_ptr+0x00006628+4*8))=0x82ca5d23;
*((unsigned int *)((unsigned long)context_ptr+0x00006628+4*9))=0xbf5c357e;
*((unsigned int *)((unsigned long)context_ptr+0x00006628+4*10))=0xeef52c6a;
*((unsigned int *)((unsigned long)context_ptr+0x00006628+4*11))=0x12fc7ddc;
*((unsigned int *)((unsigned long)context_ptr+0x00006628+4*12))=0x8f5808a7;
*((unsigned int *)((unsigned long)context_ptr+0x00006628+4*13))=0xe2ef6f7b;
*((unsigned int *)((unsigned long)context_ptr+0x00006628+4*14))=0xa933c7e3;
*((unsigned int *)((unsigned long)context_ptr+0x00006628+4*15))=0x9858e35e;
*((unsigned int *)((unsigned long)context_ptr+0x00006628+4*16))=0x000000d3;
*((unsigned int *)((unsigned long)context_ptr+0x00003600))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003600+4*1))=0x000062fc;
*((unsigned int *)((unsigned long)context_ptr+0x00003600+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003600+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003600+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003600+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000600))=0x04c00041;
*((unsigned int *)((unsigned long)context_ptr+0x00000600+4*1))=0x00006628;
*((unsigned int *)((unsigned long)context_ptr+0x00000600+4*2))=0x00006098;
*((unsigned int *)((unsigned long)context_ptr+0x00000600+4*3))=0x02220041;
*((unsigned int *)((unsigned long)context_ptr+0x00000600+4*4))=0x05b5b173;
*((unsigned int *)((unsigned long)context_ptr+0x00000600+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000132&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006410,"\xd7\xa7\x0d\x01\x27\x49\x42\x1b\x2d\x45\xd0\xcb\xf8\xf9\xa1\xb6\xdb\xe9\xbf\xa6",20))
printf("strip: d7a70d012749421b, Pass\n");
else
printf("strip: d7a70d012749421b, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006310))=0x016a0a02;
*((unsigned int *)((unsigned long)context_ptr+0x00006310+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006310+4*2))=0x02020042;
*((unsigned int *)((unsigned long)context_ptr+0x00006310+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x000063dc))=0x877b79d5;
*((unsigned int *)((unsigned long)context_ptr+0x000063dc+4*1))=0x46f579a7;
*((unsigned int *)((unsigned long)context_ptr+0x000063dc+4*2))=0x3016f809;
*((unsigned int *)((unsigned long)context_ptr+0x000063dc+4*3))=0xa750d746;
*((unsigned int *)((unsigned long)context_ptr+0x000063dc+4*4))=0x833a8bd8;
*((unsigned int *)((unsigned long)context_ptr+0x000063dc+4*5))=0x662e5d05;
*((unsigned int *)((unsigned long)context_ptr+0x000063dc+4*6))=0xceb0ab0f;
*((unsigned int *)((unsigned long)context_ptr+0x000063dc+4*7))=0xfb251f98;
*((unsigned int *)((unsigned long)context_ptr+0x000063dc+4*8))=0x527ca9b2;
*((unsigned int *)((unsigned long)context_ptr+0x000063dc+4*9))=0x583ff0d9;
*((unsigned int *)((unsigned long)context_ptr+0x000063dc+4*10))=0xbe93fc51;
*((unsigned int *)((unsigned long)context_ptr+0x000063dc+4*11))=0xd0be5355;
*((unsigned int *)((unsigned long)context_ptr+0x000063dc+4*12))=0x4da6e024;
*((unsigned int *)((unsigned long)context_ptr+0x000063dc+4*13))=0x7085f232;
*((unsigned int *)((unsigned long)context_ptr+0x000063dc+4*14))=0xe902a94e;
*((unsigned int *)((unsigned long)context_ptr+0x000063dc+4*15))=0x990f009d;
*((unsigned int *)((unsigned long)context_ptr+0x000063dc+4*16))=0x0000543d;
*((unsigned int *)((unsigned long)context_ptr+0x00003618))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003618+4*1))=0x00006320;
*((unsigned int *)((unsigned long)context_ptr+0x00003618+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003618+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003618+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003618+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000618))=0x04c00042;
*((unsigned int *)((unsigned long)context_ptr+0x00000618+4*1))=0x000063dc;
*((unsigned int *)((unsigned long)context_ptr+0x00000618+4*2))=0x00006310;
*((unsigned int *)((unsigned long)context_ptr+0x00000618+4*3))=0x02220042;
*((unsigned int *)((unsigned long)context_ptr+0x00000618+4*4))=0x083f2edd;
*((unsigned int *)((unsigned long)context_ptr+0x00000618+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000138&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006424,"\x1a\x71\x6d\x9d\x70\xeb\xe5\xde\xf4\xa6\xff\x83\x17\x3e\xf3\x57\x47\x1e\x42\x32",20))
printf("strip: 1a716d9d70ebe5de, Pass\n");
else
printf("strip: 1a716d9d70ebe5de, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006334))=0x016a0a02;
*((unsigned int *)((unsigned long)context_ptr+0x00006334+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006334+4*2))=0x02020043;
*((unsigned int *)((unsigned long)context_ptr+0x00006334+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x000064d8))=0xc845261c;
*((unsigned int *)((unsigned long)context_ptr+0x000064d8+4*1))=0x910aff20;
*((unsigned int *)((unsigned long)context_ptr+0x000064d8+4*2))=0x762a8093;
*((unsigned int *)((unsigned long)context_ptr+0x000064d8+4*3))=0x4e5e41d9;
*((unsigned int *)((unsigned long)context_ptr+0x000064d8+4*4))=0xf5859c63;
*((unsigned int *)((unsigned long)context_ptr+0x000064d8+4*5))=0x4b044d78;
*((unsigned int *)((unsigned long)context_ptr+0x000064d8+4*6))=0x7b92fed5;
*((unsigned int *)((unsigned long)context_ptr+0x000064d8+4*7))=0xcf595462;
*((unsigned int *)((unsigned long)context_ptr+0x000064d8+4*8))=0xe1249358;
*((unsigned int *)((unsigned long)context_ptr+0x000064d8+4*9))=0x2a40754e;
*((unsigned int *)((unsigned long)context_ptr+0x000064d8+4*10))=0x0aedb4f0;
*((unsigned int *)((unsigned long)context_ptr+0x000064d8+4*11))=0xb7f6998d;
*((unsigned int *)((unsigned long)context_ptr+0x000064d8+4*12))=0x97e544a2;
*((unsigned int *)((unsigned long)context_ptr+0x000064d8+4*13))=0x19dca300;
*((unsigned int *)((unsigned long)context_ptr+0x000064d8+4*14))=0x630a8b31;
*((unsigned int *)((unsigned long)context_ptr+0x000064d8+4*15))=0x19d93e93;
*((unsigned int *)((unsigned long)context_ptr+0x000064d8+4*16))=0x00d535cd;
*((unsigned int *)((unsigned long)context_ptr+0x00003630))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003630+4*1))=0x00006420;
*((unsigned int *)((unsigned long)context_ptr+0x00003630+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003630+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003630+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003630+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000630))=0x04c00043;
*((unsigned int *)((unsigned long)context_ptr+0x00000630+4*1))=0x000064d8;
*((unsigned int *)((unsigned long)context_ptr+0x00000630+4*2))=0x00006334;
*((unsigned int *)((unsigned long)context_ptr+0x00000630+4*3))=0x02220043;
*((unsigned int *)((unsigned long)context_ptr+0x00000630+4*4))=0x08501bca;
*((unsigned int *)((unsigned long)context_ptr+0x00000630+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000013e&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006148,"\x50\xe1\xf0\x5a\xa4\xa1\x13\x36\xa8\xcf\xd0\x90\xee\xe4\xd0\x98\x1d\x3e\xfe\xa0",20))
printf("strip: 50e1f05aa4a11336, Pass\n");
else
printf("strip: 50e1f05aa4a11336, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006344))=0x016a0a02;
*((unsigned int *)((unsigned long)context_ptr+0x00006344+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006344+4*2))=0x02020044;
*((unsigned int *)((unsigned long)context_ptr+0x00006344+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x000060a8))=0x6f22b50d;
*((unsigned int *)((unsigned long)context_ptr+0x000060a8+4*1))=0x8f34a3cc;
*((unsigned int *)((unsigned long)context_ptr+0x000060a8+4*2))=0x271135b7;
*((unsigned int *)((unsigned long)context_ptr+0x000060a8+4*3))=0xf4c732c7;
*((unsigned int *)((unsigned long)context_ptr+0x000060a8+4*4))=0xbbc8ceb4;
*((unsigned int *)((unsigned long)context_ptr+0x000060a8+4*5))=0x667602b1;
*((unsigned int *)((unsigned long)context_ptr+0x000060a8+4*6))=0xba70c4c8;
*((unsigned int *)((unsigned long)context_ptr+0x000060a8+4*7))=0x7612dc2c;
*((unsigned int *)((unsigned long)context_ptr+0x000060a8+4*8))=0x1e62d653;
*((unsigned int *)((unsigned long)context_ptr+0x000060a8+4*9))=0xbae92eaf;
*((unsigned int *)((unsigned long)context_ptr+0x000060a8+4*10))=0x69f44fbd;
*((unsigned int *)((unsigned long)context_ptr+0x000060a8+4*11))=0xefd3a744;
*((unsigned int *)((unsigned long)context_ptr+0x000060a8+4*12))=0xed16bd6a;
*((unsigned int *)((unsigned long)context_ptr+0x000060a8+4*13))=0x634b8a02;
*((unsigned int *)((unsigned long)context_ptr+0x000060a8+4*14))=0x7ace7e71;
*((unsigned int *)((unsigned long)context_ptr+0x000060a8+4*15))=0xd25c0681;
*((unsigned int *)((unsigned long)context_ptr+0x000060a8+4*16))=0x476ee04e;
*((unsigned int *)((unsigned long)context_ptr+0x00003648))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003648+4*1))=0x0000651c;
*((unsigned int *)((unsigned long)context_ptr+0x00003648+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003648+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003648+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003648+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000648))=0x04c00044;
*((unsigned int *)((unsigned long)context_ptr+0x00000648+4*1))=0x000060a8;
*((unsigned int *)((unsigned long)context_ptr+0x00000648+4*2))=0x00006344;
*((unsigned int *)((unsigned long)context_ptr+0x00000648+4*3))=0x02220044;
*((unsigned int *)((unsigned long)context_ptr+0x00000648+4*4))=0x09cb2914;
*((unsigned int *)((unsigned long)context_ptr+0x00000648+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000144&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006438,"\xbb\xeb\x72\x8c\x6c\x3b\x33\xd0\x57\xbe\x85\x7c\x20\xf8\x08\x1b\x5a\x2a\xee\x5d",20))
printf("strip: bbeb728c6c3b33d0, Pass\n");
else
printf("strip: bbeb728c6c3b33d0, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006354))=0x016a0a02;
*((unsigned int *)((unsigned long)context_ptr+0x00006354+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006354+4*2))=0x02020045;
*((unsigned int *)((unsigned long)context_ptr+0x00006354+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x000060ec))=0x0553a4cf;
*((unsigned int *)((unsigned long)context_ptr+0x000060ec+4*1))=0x75e18124;
*((unsigned int *)((unsigned long)context_ptr+0x000060ec+4*2))=0xcc21816b;
*((unsigned int *)((unsigned long)context_ptr+0x000060ec+4*3))=0x11e9127d;
*((unsigned int *)((unsigned long)context_ptr+0x000060ec+4*4))=0x538b0007;
*((unsigned int *)((unsigned long)context_ptr+0x000060ec+4*5))=0x12780b10;
*((unsigned int *)((unsigned long)context_ptr+0x000060ec+4*6))=0x074fbe33;
*((unsigned int *)((unsigned long)context_ptr+0x000060ec+4*7))=0xc2a3eef5;
*((unsigned int *)((unsigned long)context_ptr+0x000060ec+4*8))=0xf9a058ed;
*((unsigned int *)((unsigned long)context_ptr+0x000060ec+4*9))=0xea73dc0f;
*((unsigned int *)((unsigned long)context_ptr+0x000060ec+4*10))=0xee840b60;
*((unsigned int *)((unsigned long)context_ptr+0x000060ec+4*11))=0x8dad3d8d;
*((unsigned int *)((unsigned long)context_ptr+0x000060ec+4*12))=0x02383d8d;
*((unsigned int *)((unsigned long)context_ptr+0x000060ec+4*13))=0x73e6c0f8;
*((unsigned int *)((unsigned long)context_ptr+0x000060ec+4*14))=0xdff9793c;
*((unsigned int *)((unsigned long)context_ptr+0x000060ec+4*15))=0x926eadba;
*((unsigned int *)((unsigned long)context_ptr+0x000060ec+4*16))=0xbb113dc2;
*((unsigned int *)((unsigned long)context_ptr+0x000060ec+4*17))=0x0000007b;
*((unsigned int *)((unsigned long)context_ptr+0x00003660))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003660+4*1))=0x00006434;
*((unsigned int *)((unsigned long)context_ptr+0x00003660+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003660+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003660+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003660+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000660))=0x04c00045;
*((unsigned int *)((unsigned long)context_ptr+0x00000660+4*1))=0x000060ec;
*((unsigned int *)((unsigned long)context_ptr+0x00000660+4*2))=0x00006354;
*((unsigned int *)((unsigned long)context_ptr+0x00000660+4*3))=0x02220045;
*((unsigned int *)((unsigned long)context_ptr+0x00000660+4*4))=0x0b55cecd;
*((unsigned int *)((unsigned long)context_ptr+0x00000660+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000014a&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x0000644c,"\x53\xd4\xbf\x03\x80\xdd\x53\x9c\x1a\x3c\xbc\x31\x0f\x23\xbb\xc8\x21\xb8\xf4\x13",20))
printf("strip: 53d4bf0380dd539c, Pass\n");
else
printf("strip: 53d4bf0380dd539c, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006364))=0x016a0a02;
*((unsigned int *)((unsigned long)context_ptr+0x00006364+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006364+4*2))=0x02020046;
*((unsigned int *)((unsigned long)context_ptr+0x00006364+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x00006134))=0x0ea73164;
*((unsigned int *)((unsigned long)context_ptr+0x00006134+4*1))=0xac058692;
*((unsigned int *)((unsigned long)context_ptr+0x00006134+4*2))=0xa6893f7f;
*((unsigned int *)((unsigned long)context_ptr+0x00006134+4*3))=0xea38b59e;
*((unsigned int *)((unsigned long)context_ptr+0x00006134+4*4))=0x1698467f;
*((unsigned int *)((unsigned long)context_ptr+0x00006134+4*5))=0x1bd94104;
*((unsigned int *)((unsigned long)context_ptr+0x00006134+4*6))=0x3a93bf88;
*((unsigned int *)((unsigned long)context_ptr+0x00006134+4*7))=0x5a1e697d;
*((unsigned int *)((unsigned long)context_ptr+0x00006134+4*8))=0xd9270cfd;
*((unsigned int *)((unsigned long)context_ptr+0x00006134+4*9))=0xddd81bda;
*((unsigned int *)((unsigned long)context_ptr+0x00006134+4*10))=0x067e2c7c;
*((unsigned int *)((unsigned long)context_ptr+0x00006134+4*11))=0x965431c5;
*((unsigned int *)((unsigned long)context_ptr+0x00006134+4*12))=0x97623da7;
*((unsigned int *)((unsigned long)context_ptr+0x00006134+4*13))=0xa685db44;
*((unsigned int *)((unsigned long)context_ptr+0x00006134+4*14))=0x43d414da;
*((unsigned int *)((unsigned long)context_ptr+0x00006134+4*15))=0xc06eae35;
*((unsigned int *)((unsigned long)context_ptr+0x00006134+4*16))=0xbd7aa017;
*((unsigned int *)((unsigned long)context_ptr+0x00006134+4*17))=0x00001206;
*((unsigned int *)((unsigned long)context_ptr+0x00003678))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003678+4*1))=0x00006448;
*((unsigned int *)((unsigned long)context_ptr+0x00003678+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003678+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003678+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003678+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000678))=0x04c00046;
*((unsigned int *)((unsigned long)context_ptr+0x00000678+4*1))=0x00006134;
*((unsigned int *)((unsigned long)context_ptr+0x00000678+4*2))=0x00006364;
*((unsigned int *)((unsigned long)context_ptr+0x00000678+4*3))=0x02220046;
*((unsigned int *)((unsigned long)context_ptr+0x00000678+4*4))=0x01ce64f1;
*((unsigned int *)((unsigned long)context_ptr+0x00000678+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000150&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006460,"\x75\x3d\x38\xde\xb3\x7c\x9e\x74\x5c\xd3\x22\x0e\x43\x99\x26\x1b\x91\x4f\xc0\xab",20))
printf("strip: 753d38deb37c9e74, Pass\n");
else
printf("strip: 753d38deb37c9e74, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006374))=0x016a0a02;
*((unsigned int *)((unsigned long)context_ptr+0x00006374+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006374+4*2))=0x02020047;
*((unsigned int *)((unsigned long)context_ptr+0x00006374+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x0000617c))=0xf792d718;
*((unsigned int *)((unsigned long)context_ptr+0x0000617c+4*1))=0x12c83c34;
*((unsigned int *)((unsigned long)context_ptr+0x0000617c+4*2))=0xcaa737a8;
*((unsigned int *)((unsigned long)context_ptr+0x0000617c+4*3))=0xb489dbe7;
*((unsigned int *)((unsigned long)context_ptr+0x0000617c+4*4))=0x6f9caa59;
*((unsigned int *)((unsigned long)context_ptr+0x0000617c+4*5))=0xd2ef7b61;
*((unsigned int *)((unsigned long)context_ptr+0x0000617c+4*6))=0xfa66cd01;
*((unsigned int *)((unsigned long)context_ptr+0x0000617c+4*7))=0x447dd921;
*((unsigned int *)((unsigned long)context_ptr+0x0000617c+4*8))=0x6ac98fec;
*((unsigned int *)((unsigned long)context_ptr+0x0000617c+4*9))=0x2d6ae053;
*((unsigned int *)((unsigned long)context_ptr+0x0000617c+4*10))=0xace9bea7;
*((unsigned int *)((unsigned long)context_ptr+0x0000617c+4*11))=0xd1963151;
*((unsigned int *)((unsigned long)context_ptr+0x0000617c+4*12))=0x8fdac51b;
*((unsigned int *)((unsigned long)context_ptr+0x0000617c+4*13))=0x4cbefca0;
*((unsigned int *)((unsigned long)context_ptr+0x0000617c+4*14))=0xeb5c96cc;
*((unsigned int *)((unsigned long)context_ptr+0x0000617c+4*15))=0xe9f89756;
*((unsigned int *)((unsigned long)context_ptr+0x0000617c+4*16))=0xac3f59f3;
*((unsigned int *)((unsigned long)context_ptr+0x0000617c+4*17))=0x0053e233;
*((unsigned int *)((unsigned long)context_ptr+0x00003690))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003690+4*1))=0x0000645c;
*((unsigned int *)((unsigned long)context_ptr+0x00003690+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003690+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003690+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003690+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000690))=0x04c00047;
*((unsigned int *)((unsigned long)context_ptr+0x00000690+4*1))=0x0000617c;
*((unsigned int *)((unsigned long)context_ptr+0x00000690+4*2))=0x00006374;
*((unsigned int *)((unsigned long)context_ptr+0x00000690+4*3))=0x02220047;
*((unsigned int *)((unsigned long)context_ptr+0x00000690+4*4))=0x0f171667;
*((unsigned int *)((unsigned long)context_ptr+0x00000690+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000156&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006208,"\x67\x3b\x16\xf4\xa2\x2a\xbb\xc1\x44\xbd\x0c\xcb\xb8\x75\xde\xb0\xfa\xd3\x92\x4c",20))
printf("strip: 673b16f4a22abbc1, Pass\n");
else
printf("strip: 673b16f4a22abbc1, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006470))=0x016a0a02;
*((unsigned int *)((unsigned long)context_ptr+0x00006470+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006470+4*2))=0x02020048;
*((unsigned int *)((unsigned long)context_ptr+0x00006470+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x000061c4))=0x87156a05;
*((unsigned int *)((unsigned long)context_ptr+0x000061c4+4*1))=0x611943f3;
*((unsigned int *)((unsigned long)context_ptr+0x000061c4+4*2))=0x0372e1b5;
*((unsigned int *)((unsigned long)context_ptr+0x000061c4+4*3))=0x367f29ca;
*((unsigned int *)((unsigned long)context_ptr+0x000061c4+4*4))=0x7f25c75a;
*((unsigned int *)((unsigned long)context_ptr+0x000061c4+4*5))=0xaf532f7e;
*((unsigned int *)((unsigned long)context_ptr+0x000061c4+4*6))=0x7013d127;
*((unsigned int *)((unsigned long)context_ptr+0x000061c4+4*7))=0x72be6c88;
*((unsigned int *)((unsigned long)context_ptr+0x000061c4+4*8))=0x471bae89;
*((unsigned int *)((unsigned long)context_ptr+0x000061c4+4*9))=0x307fed94;
*((unsigned int *)((unsigned long)context_ptr+0x000061c4+4*10))=0x971f072f;
*((unsigned int *)((unsigned long)context_ptr+0x000061c4+4*11))=0x4c54281d;
*((unsigned int *)((unsigned long)context_ptr+0x000061c4+4*12))=0x578b1ce4;
*((unsigned int *)((unsigned long)context_ptr+0x000061c4+4*13))=0x5625e2a0;
*((unsigned int *)((unsigned long)context_ptr+0x000061c4+4*14))=0x01493fc5;
*((unsigned int *)((unsigned long)context_ptr+0x000061c4+4*15))=0xa39fc740;
*((unsigned int *)((unsigned long)context_ptr+0x000061c4+4*16))=0x06f4b435;
*((unsigned int *)((unsigned long)context_ptr+0x000061c4+4*17))=0xc9826773;
*((unsigned int *)((unsigned long)context_ptr+0x000036a8))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x000036a8+4*1))=0x00006530;
*((unsigned int *)((unsigned long)context_ptr+0x000036a8+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000036a8+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000036a8+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000036a8+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x000006a8))=0x04c00048;
*((unsigned int *)((unsigned long)context_ptr+0x000006a8+4*1))=0x000061c4;
*((unsigned int *)((unsigned long)context_ptr+0x000006a8+4*2))=0x00006470;
*((unsigned int *)((unsigned long)context_ptr+0x000006a8+4*3))=0x02220048;
*((unsigned int *)((unsigned long)context_ptr+0x000006a8+4*4))=0x0aba3770;
*((unsigned int *)((unsigned long)context_ptr+0x000006a8+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000015c&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006484,"\xaf\xec\xe2\xa9\x4f\xcb\xcc\x72\x19\x77\x9b\xd4\x20\x87\x56\xbf\x72\x2f\xe8\xf6",20))
printf("strip: afece2a94fcbcc72, Pass\n");
else
printf("strip: afece2a94fcbcc72, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006384))=0x016a0a02;
*((unsigned int *)((unsigned long)context_ptr+0x00006384+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006384+4*2))=0x02020049;
*((unsigned int *)((unsigned long)context_ptr+0x00006384+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x0000620c))=0x7efd976f;
*((unsigned int *)((unsigned long)context_ptr+0x0000620c+4*1))=0x9e4792d2;
*((unsigned int *)((unsigned long)context_ptr+0x0000620c+4*2))=0x07b14820;
*((unsigned int *)((unsigned long)context_ptr+0x0000620c+4*3))=0xb28cffbd;
*((unsigned int *)((unsigned long)context_ptr+0x0000620c+4*4))=0xee240e5f;
*((unsigned int *)((unsigned long)context_ptr+0x0000620c+4*5))=0x0fcc1974;
*((unsigned int *)((unsigned long)context_ptr+0x0000620c+4*6))=0x2cea613a;
*((unsigned int *)((unsigned long)context_ptr+0x0000620c+4*7))=0xf05d82c3;
*((unsigned int *)((unsigned long)context_ptr+0x0000620c+4*8))=0x7da91207;
*((unsigned int *)((unsigned long)context_ptr+0x0000620c+4*9))=0x198b19bd;
*((unsigned int *)((unsigned long)context_ptr+0x0000620c+4*10))=0x29a65c7b;
*((unsigned int *)((unsigned long)context_ptr+0x0000620c+4*11))=0x7f34e986;
*((unsigned int *)((unsigned long)context_ptr+0x0000620c+4*12))=0x770fe56d;
*((unsigned int *)((unsigned long)context_ptr+0x0000620c+4*13))=0x127cfcfe;
*((unsigned int *)((unsigned long)context_ptr+0x0000620c+4*14))=0xdf1be762;
*((unsigned int *)((unsigned long)context_ptr+0x0000620c+4*15))=0x1f4d4cc3;
*((unsigned int *)((unsigned long)context_ptr+0x0000620c+4*16))=0x61be6cb8;
*((unsigned int *)((unsigned long)context_ptr+0x0000620c+4*17))=0x0413fd23;
*((unsigned int *)((unsigned long)context_ptr+0x0000620c+4*18))=0x000000b0;
*((unsigned int *)((unsigned long)context_ptr+0x000036c0))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x000036c0+4*1))=0x00006480;
*((unsigned int *)((unsigned long)context_ptr+0x000036c0+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000036c0+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000036c0+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000036c0+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x000006c0))=0x04c00049;
*((unsigned int *)((unsigned long)context_ptr+0x000006c0+4*1))=0x0000620c;
*((unsigned int *)((unsigned long)context_ptr+0x000006c0+4*2))=0x00006384;
*((unsigned int *)((unsigned long)context_ptr+0x000006c0+4*3))=0x02220049;
*((unsigned int *)((unsigned long)context_ptr+0x000006c0+4*4))=0x02531c05;
*((unsigned int *)((unsigned long)context_ptr+0x000006c0+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000162&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000063a4,"\xac\xff\xda\x5d\x35\xe1\x8c\x62\xfb\x30\xb3\xcf\x96\x2f\x4a\xcc\x80\x72\x83\xfe",20))
printf("strip: acffda5d35e18c62, Pass\n");
else
printf("strip: acffda5d35e18c62, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006394))=0x016a0a02;
*((unsigned int *)((unsigned long)context_ptr+0x00006394+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006394+4*2))=0x0202004a;
*((unsigned int *)((unsigned long)context_ptr+0x00006394+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x00006544))=0x02ed6d2a;
*((unsigned int *)((unsigned long)context_ptr+0x00006544+4*1))=0x5ab7ab25;
*((unsigned int *)((unsigned long)context_ptr+0x00006544+4*2))=0x92105c6d;
*((unsigned int *)((unsigned long)context_ptr+0x00006544+4*3))=0x7557fe59;
*((unsigned int *)((unsigned long)context_ptr+0x00006544+4*4))=0xbeb3bdfc;
*((unsigned int *)((unsigned long)context_ptr+0x00006544+4*5))=0xbb21d69f;
*((unsigned int *)((unsigned long)context_ptr+0x00006544+4*6))=0xbfdb8e60;
*((unsigned int *)((unsigned long)context_ptr+0x00006544+4*7))=0x066cf5a7;
*((unsigned int *)((unsigned long)context_ptr+0x00006544+4*8))=0xd49b68f6;
*((unsigned int *)((unsigned long)context_ptr+0x00006544+4*9))=0xbb3236c8;
*((unsigned int *)((unsigned long)context_ptr+0x00006544+4*10))=0xadbba069;
*((unsigned int *)((unsigned long)context_ptr+0x00006544+4*11))=0xf4a154bc;
*((unsigned int *)((unsigned long)context_ptr+0x00006544+4*12))=0x475ffa00;
*((unsigned int *)((unsigned long)context_ptr+0x00006544+4*13))=0xb3383baf;
*((unsigned int *)((unsigned long)context_ptr+0x00006544+4*14))=0x04e2a696;
*((unsigned int *)((unsigned long)context_ptr+0x00006544+4*15))=0x67d64a65;
*((unsigned int *)((unsigned long)context_ptr+0x00006544+4*16))=0x1f959a5c;
*((unsigned int *)((unsigned long)context_ptr+0x00006544+4*17))=0x55c2efc9;
*((unsigned int *)((unsigned long)context_ptr+0x00006544+4*18))=0x00001855;
*((unsigned int *)((unsigned long)context_ptr+0x000036d8))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x000036d8+4*1))=0x000063a4;
*((unsigned int *)((unsigned long)context_ptr+0x000036d8+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000036d8+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000036d8+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000036d8+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x000006d8))=0x04c0004a;
*((unsigned int *)((unsigned long)context_ptr+0x000006d8+4*1))=0x00006544;
*((unsigned int *)((unsigned long)context_ptr+0x000006d8+4*2))=0x00006394;
*((unsigned int *)((unsigned long)context_ptr+0x000006d8+4*3))=0x0222004a;
*((unsigned int *)((unsigned long)context_ptr+0x000006d8+4*4))=0x030ac64c;
*((unsigned int *)((unsigned long)context_ptr+0x000006d8+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000168&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006294,"\x99\x0e\x3d\x02\xae\x81\x94\x45\xa8\x0c\x01\xa8\xa2\x6c\x07\x50\x6d\x6d\x40\xf4",20))
printf("strip: 990e3d02ae819445, Pass\n");
else
printf("strip: 990e3d02ae819445, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000063b8))=0x016a0a02;
*((unsigned int *)((unsigned long)context_ptr+0x000063b8+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000063b8+4*2))=0x0202004b;
*((unsigned int *)((unsigned long)context_ptr+0x000063b8+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x00006258))=0x7a53afee;
*((unsigned int *)((unsigned long)context_ptr+0x00006258+4*1))=0x58a4ec81;
*((unsigned int *)((unsigned long)context_ptr+0x00006258+4*2))=0x472b0be3;
*((unsigned int *)((unsigned long)context_ptr+0x00006258+4*3))=0x953ee0f4;
*((unsigned int *)((unsigned long)context_ptr+0x00006258+4*4))=0xba9fef49;
*((unsigned int *)((unsigned long)context_ptr+0x00006258+4*5))=0x26edceee;
*((unsigned int *)((unsigned long)context_ptr+0x00006258+4*6))=0xc4d8df42;
*((unsigned int *)((unsigned long)context_ptr+0x00006258+4*7))=0x1979dab8;
*((unsigned int *)((unsigned long)context_ptr+0x00006258+4*8))=0x8f9b3fba;
*((unsigned int *)((unsigned long)context_ptr+0x00006258+4*9))=0x1862a763;
*((unsigned int *)((unsigned long)context_ptr+0x00006258+4*10))=0x8f48d8dc;
*((unsigned int *)((unsigned long)context_ptr+0x00006258+4*11))=0x6274bc22;
*((unsigned int *)((unsigned long)context_ptr+0x00006258+4*12))=0xced7d3ee;
*((unsigned int *)((unsigned long)context_ptr+0x00006258+4*13))=0xeb51e7ba;
*((unsigned int *)((unsigned long)context_ptr+0x00006258+4*14))=0x7858c06a;
*((unsigned int *)((unsigned long)context_ptr+0x00006258+4*15))=0x0d521d3f;
*((unsigned int *)((unsigned long)context_ptr+0x00006258+4*16))=0x93135350;
*((unsigned int *)((unsigned long)context_ptr+0x00006258+4*17))=0x3f1a9cd7;
*((unsigned int *)((unsigned long)context_ptr+0x00006258+4*18))=0x00ba4f4b;
*((unsigned int *)((unsigned long)context_ptr+0x000036f0))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x000036f0+4*1))=0x00006590;
*((unsigned int *)((unsigned long)context_ptr+0x000036f0+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000036f0+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000036f0+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000036f0+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x000006f0))=0x04c0004b;
*((unsigned int *)((unsigned long)context_ptr+0x000006f0+4*1))=0x00006258;
*((unsigned int *)((unsigned long)context_ptr+0x000006f0+4*2))=0x000063b8;
*((unsigned int *)((unsigned long)context_ptr+0x000006f0+4*3))=0x0222004b;
*((unsigned int *)((unsigned long)context_ptr+0x000006f0+4*4))=0x0b2087db;
*((unsigned int *)((unsigned long)context_ptr+0x000006f0+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000016e&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000063c8,"\x2c\x45\x2a\x49\x7d\x34\x8f\xe3\x53\x7c\x89\x3e\x19\x3c\xcc\x5c\x69\x55\x31\xd5",20))
printf("strip: 2c452a497d348fe3, Pass\n");
else
printf("strip: 2c452a497d348fe3, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006040))=0x016a0a02;
*((unsigned int *)((unsigned long)context_ptr+0x00006040+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006040+4*2))=0x0202004c;
*((unsigned int *)((unsigned long)context_ptr+0x00006040+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x0000666c))=0xcd5811ca;
*((unsigned int *)((unsigned long)context_ptr+0x0000666c+4*1))=0x1767ae80;
*((unsigned int *)((unsigned long)context_ptr+0x0000666c+4*2))=0x099e82a7;
*((unsigned int *)((unsigned long)context_ptr+0x0000666c+4*3))=0x82e3ed07;
*((unsigned int *)((unsigned long)context_ptr+0x0000666c+4*4))=0xc8d51969;
*((unsigned int *)((unsigned long)context_ptr+0x0000666c+4*5))=0xd57ecda8;
*((unsigned int *)((unsigned long)context_ptr+0x0000666c+4*6))=0x8e8c112c;
*((unsigned int *)((unsigned long)context_ptr+0x0000666c+4*7))=0x1e643a94;
*((unsigned int *)((unsigned long)context_ptr+0x0000666c+4*8))=0xf7a6d8d0;
*((unsigned int *)((unsigned long)context_ptr+0x0000666c+4*9))=0xe5ceefa0;
*((unsigned int *)((unsigned long)context_ptr+0x0000666c+4*10))=0xa325185f;
*((unsigned int *)((unsigned long)context_ptr+0x0000666c+4*11))=0xadca71ca;
*((unsigned int *)((unsigned long)context_ptr+0x0000666c+4*12))=0x44333034;
*((unsigned int *)((unsigned long)context_ptr+0x0000666c+4*13))=0x923c8b40;
*((unsigned int *)((unsigned long)context_ptr+0x0000666c+4*14))=0xc3a9cc9f;
*((unsigned int *)((unsigned long)context_ptr+0x0000666c+4*15))=0xa054077c;
*((unsigned int *)((unsigned long)context_ptr+0x0000666c+4*16))=0x082eeb7b;
*((unsigned int *)((unsigned long)context_ptr+0x0000666c+4*17))=0x8ad83870;
*((unsigned int *)((unsigned long)context_ptr+0x0000666c+4*18))=0x673ba5b7;
*((unsigned int *)((unsigned long)context_ptr+0x00003708))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003708+4*1))=0x000063c8;
*((unsigned int *)((unsigned long)context_ptr+0x00003708+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003708+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003708+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003708+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000708))=0x04c0004c;
*((unsigned int *)((unsigned long)context_ptr+0x00000708+4*1))=0x0000666c;
*((unsigned int *)((unsigned long)context_ptr+0x00000708+4*2))=0x00006040;
*((unsigned int *)((unsigned long)context_ptr+0x00000708+4*3))=0x0222004c;
*((unsigned int *)((unsigned long)context_ptr+0x00000708+4*4))=0x0ee61156;
*((unsigned int *)((unsigned long)context_ptr+0x00000708+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000174&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006060,"\x89\xf4\x99\x32\x21\x15\xcd\xbc\xf2\x01\x00\xdf\x81\x92\xc4\xa9\xe8\x03\x85\x2e",20))
printf("strip: 89f499322115cdbc, Pass\n");
else
printf("strip: 89f499322115cdbc, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006030))=0x016a0a02;
*((unsigned int *)((unsigned long)context_ptr+0x00006030+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006030+4*2))=0x0202004d;
*((unsigned int *)((unsigned long)context_ptr+0x00006030+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x000066b8))=0x23acf9d7;
*((unsigned int *)((unsigned long)context_ptr+0x000066b8+4*1))=0x82bee2f3;
*((unsigned int *)((unsigned long)context_ptr+0x000066b8+4*2))=0x168193ad;
*((unsigned int *)((unsigned long)context_ptr+0x000066b8+4*3))=0xd3756462;
*((unsigned int *)((unsigned long)context_ptr+0x000066b8+4*4))=0x8e341b4c;
*((unsigned int *)((unsigned long)context_ptr+0x000066b8+4*5))=0x8420f867;
*((unsigned int *)((unsigned long)context_ptr+0x000066b8+4*6))=0xd3e449ce;
*((unsigned int *)((unsigned long)context_ptr+0x000066b8+4*7))=0xc86dc26b;
*((unsigned int *)((unsigned long)context_ptr+0x000066b8+4*8))=0x49689056;
*((unsigned int *)((unsigned long)context_ptr+0x000066b8+4*9))=0x3cb76a74;
*((unsigned int *)((unsigned long)context_ptr+0x000066b8+4*10))=0x65c0bff2;
*((unsigned int *)((unsigned long)context_ptr+0x000066b8+4*11))=0x79e490e5;
*((unsigned int *)((unsigned long)context_ptr+0x000066b8+4*12))=0x393544f6;
*((unsigned int *)((unsigned long)context_ptr+0x000066b8+4*13))=0x9d0bc75c;
*((unsigned int *)((unsigned long)context_ptr+0x000066b8+4*14))=0x654b7d4f;
*((unsigned int *)((unsigned long)context_ptr+0x000066b8+4*15))=0x58bd1f6b;
*((unsigned int *)((unsigned long)context_ptr+0x000066b8+4*16))=0xb937d118;
*((unsigned int *)((unsigned long)context_ptr+0x000066b8+4*17))=0xf8f20998;
*((unsigned int *)((unsigned long)context_ptr+0x000066b8+4*18))=0x31b217bb;
*((unsigned int *)((unsigned long)context_ptr+0x000066b8+4*19))=0x00000076;
*((unsigned int *)((unsigned long)context_ptr+0x00003720))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003720+4*1))=0x00006060;
*((unsigned int *)((unsigned long)context_ptr+0x00003720+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003720+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003720+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003720+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000720))=0x04c0004d;
*((unsigned int *)((unsigned long)context_ptr+0x00000720+4*1))=0x000066b8;
*((unsigned int *)((unsigned long)context_ptr+0x00000720+4*2))=0x00006030;
*((unsigned int *)((unsigned long)context_ptr+0x00000720+4*3))=0x0222004d;
*((unsigned int *)((unsigned long)context_ptr+0x00000720+4*4))=0x0d30cf4f;
*((unsigned int *)((unsigned long)context_ptr+0x00000720+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000017a&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006084,"\xf6\x90\xba\x37\xfc\x3c\x4a\x40\x67\x33\x01\x36\x74\xda\x33\x91\xa1\x2a\x4b\xce",20))
printf("strip: f690ba37fc3c4a40, Pass\n");
else
printf("strip: f690ba37fc3c4a40, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006050))=0x016a0a02;
*((unsigned int *)((unsigned long)context_ptr+0x00006050+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006050+4*2))=0x0202004e;
*((unsigned int *)((unsigned long)context_ptr+0x00006050+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x00006708))=0x2302bc91;
*((unsigned int *)((unsigned long)context_ptr+0x00006708+4*1))=0x49baabda;
*((unsigned int *)((unsigned long)context_ptr+0x00006708+4*2))=0x1f037f70;
*((unsigned int *)((unsigned long)context_ptr+0x00006708+4*3))=0x093f0c2c;
*((unsigned int *)((unsigned long)context_ptr+0x00006708+4*4))=0x49803261;
*((unsigned int *)((unsigned long)context_ptr+0x00006708+4*5))=0x9dc99b88;
*((unsigned int *)((unsigned long)context_ptr+0x00006708+4*6))=0xe7e7ae67;
*((unsigned int *)((unsigned long)context_ptr+0x00006708+4*7))=0x949c1ea6;
*((unsigned int *)((unsigned long)context_ptr+0x00006708+4*8))=0xcf1990cc;
*((unsigned int *)((unsigned long)context_ptr+0x00006708+4*9))=0x695a9475;
*((unsigned int *)((unsigned long)context_ptr+0x00006708+4*10))=0xd288810b;
*((unsigned int *)((unsigned long)context_ptr+0x00006708+4*11))=0xdcf9315c;
*((unsigned int *)((unsigned long)context_ptr+0x00006708+4*12))=0x1e26f545;
*((unsigned int *)((unsigned long)context_ptr+0x00006708+4*13))=0xf70207d0;
*((unsigned int *)((unsigned long)context_ptr+0x00006708+4*14))=0x9245bc14;
*((unsigned int *)((unsigned long)context_ptr+0x00006708+4*15))=0x9d1a247a;
*((unsigned int *)((unsigned long)context_ptr+0x00006708+4*16))=0xcd2f8d36;
*((unsigned int *)((unsigned long)context_ptr+0x00006708+4*17))=0x254ae392;
*((unsigned int *)((unsigned long)context_ptr+0x00006708+4*18))=0x36309df5;
*((unsigned int *)((unsigned long)context_ptr+0x00006708+4*19))=0x0000b22c;
*((unsigned int *)((unsigned long)context_ptr+0x00003738))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003738+4*1))=0x00006084;
*((unsigned int *)((unsigned long)context_ptr+0x00003738+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003738+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003738+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003738+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000738))=0x04c0004e;
*((unsigned int *)((unsigned long)context_ptr+0x00000738+4*1))=0x00006708;
*((unsigned int *)((unsigned long)context_ptr+0x00000738+4*2))=0x00006050;
*((unsigned int *)((unsigned long)context_ptr+0x00000738+4*3))=0x0222004e;
*((unsigned int *)((unsigned long)context_ptr+0x00000738+4*4))=0x0381768b;
*((unsigned int *)((unsigned long)context_ptr+0x00000738+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000180&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000062e8,"\xcf\xff\x02\x2c\xd2\x87\x2a\x94\xf2\x4f\x82\xf3\x30\xdf\x6c\x81\xcd\x45\x61\x0d",20))
printf("strip: cfff022cd2872a94, Pass\n");
else
printf("strip: cfff022cd2872a94, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006074))=0x016a0a02;
*((unsigned int *)((unsigned long)context_ptr+0x00006074+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006074+4*2))=0x0202004f;
*((unsigned int *)((unsigned long)context_ptr+0x00006074+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x000062a4))=0xb26bea95;
*((unsigned int *)((unsigned long)context_ptr+0x000062a4+4*1))=0x296607d9;
*((unsigned int *)((unsigned long)context_ptr+0x000062a4+4*2))=0x0ecb86e7;
*((unsigned int *)((unsigned long)context_ptr+0x000062a4+4*3))=0x4a7b2b94;
*((unsigned int *)((unsigned long)context_ptr+0x000062a4+4*4))=0x06951e8c;
*((unsigned int *)((unsigned long)context_ptr+0x000062a4+4*5))=0xc22ef39b;
*((unsigned int *)((unsigned long)context_ptr+0x000062a4+4*6))=0x98d7abca;
*((unsigned int *)((unsigned long)context_ptr+0x000062a4+4*7))=0xb6ea52b7;
*((unsigned int *)((unsigned long)context_ptr+0x000062a4+4*8))=0x9aae57a8;
*((unsigned int *)((unsigned long)context_ptr+0x000062a4+4*9))=0x6fe08e70;
*((unsigned int *)((unsigned long)context_ptr+0x000062a4+4*10))=0xd818a955;
*((unsigned int *)((unsigned long)context_ptr+0x000062a4+4*11))=0xc5deb5e5;
*((unsigned int *)((unsigned long)context_ptr+0x000062a4+4*12))=0xba8ca432;
*((unsigned int *)((unsigned long)context_ptr+0x000062a4+4*13))=0x2c5ac573;
*((unsigned int *)((unsigned long)context_ptr+0x000062a4+4*14))=0xdcc23b09;
*((unsigned int *)((unsigned long)context_ptr+0x000062a4+4*15))=0x74da56b6;
*((unsigned int *)((unsigned long)context_ptr+0x000062a4+4*16))=0x3117c5f6;
*((unsigned int *)((unsigned long)context_ptr+0x000062a4+4*17))=0x64122cf6;
*((unsigned int *)((unsigned long)context_ptr+0x000062a4+4*18))=0xca1580ba;
*((unsigned int *)((unsigned long)context_ptr+0x000062a4+4*19))=0x002995ab;
*((unsigned int *)((unsigned long)context_ptr+0x00003750))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003750+4*1))=0x00006494;
*((unsigned int *)((unsigned long)context_ptr+0x00003750+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003750+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003750+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003750+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000750))=0x04c0004f;
*((unsigned int *)((unsigned long)context_ptr+0x00000750+4*1))=0x000062a4;
*((unsigned int *)((unsigned long)context_ptr+0x00000750+4*2))=0x00006074;
*((unsigned int *)((unsigned long)context_ptr+0x00000750+4*3))=0x0222004f;
*((unsigned int *)((unsigned long)context_ptr+0x00000750+4*4))=0x02faf32c;
*((unsigned int *)((unsigned long)context_ptr+0x00000750+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000186&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000062fc,"\x18\xb9\x9d\xbc\xf9\x56\x3b\x0e\x7d\x04\x5e\x8d\x7d\x0f\x2c\x27\xb2\x94\xf8\xa6",20))
printf("strip: 18b99dbcf9563b0e, Pass\n");
else
printf("strip: 18b99dbcf9563b0e, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006098))=0x016a0a02;
*((unsigned int *)((unsigned long)context_ptr+0x00006098+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006098+4*2))=0x02020050;
*((unsigned int *)((unsigned long)context_ptr+0x00006098+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x000065a4))=0xfe12c828;
*((unsigned int *)((unsigned long)context_ptr+0x000065a4+4*1))=0x5bfe4b77;
*((unsigned int *)((unsigned long)context_ptr+0x000065a4+4*2))=0x15ba3847;
*((unsigned int *)((unsigned long)context_ptr+0x000065a4+4*3))=0x73de623c;
*((unsigned int *)((unsigned long)context_ptr+0x000065a4+4*4))=0x4dd7ca13;
*((unsigned int *)((unsigned long)context_ptr+0x000065a4+4*5))=0xbad7a28c;
*((unsigned int *)((unsigned long)context_ptr+0x000065a4+4*6))=0xbbbb7e9c;
*((unsigned int *)((unsigned long)context_ptr+0x000065a4+4*7))=0x3a2ca6c0;
*((unsigned int *)((unsigned long)context_ptr+0x000065a4+4*8))=0x51c918e5;
*((unsigned int *)((unsigned long)context_ptr+0x000065a4+4*9))=0xd46ef52b;
*((unsigned int *)((unsigned long)context_ptr+0x000065a4+4*10))=0x0ddb6527;
*((unsigned int *)((unsigned long)context_ptr+0x000065a4+4*11))=0x9f2efc86;
*((unsigned int *)((unsigned long)context_ptr+0x000065a4+4*12))=0x54f9a9b0;
*((unsigned int *)((unsigned long)context_ptr+0x000065a4+4*13))=0xe92c3b5a;
*((unsigned int *)((unsigned long)context_ptr+0x000065a4+4*14))=0x3e179bd3;
*((unsigned int *)((unsigned long)context_ptr+0x000065a4+4*15))=0xac4a8633;
*((unsigned int *)((unsigned long)context_ptr+0x000065a4+4*16))=0xbf493569;
*((unsigned int *)((unsigned long)context_ptr+0x000065a4+4*17))=0x053f2f78;
*((unsigned int *)((unsigned long)context_ptr+0x000065a4+4*18))=0x6d898ea1;
*((unsigned int *)((unsigned long)context_ptr+0x000065a4+4*19))=0x0509b846;
*((unsigned int *)((unsigned long)context_ptr+0x00003768))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003768+4*1))=0x000062f4;
*((unsigned int *)((unsigned long)context_ptr+0x00003768+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003768+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003768+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003768+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000768))=0x04c00050;
*((unsigned int *)((unsigned long)context_ptr+0x00000768+4*1))=0x000065a4;
*((unsigned int *)((unsigned long)context_ptr+0x00000768+4*2))=0x00006098;
*((unsigned int *)((unsigned long)context_ptr+0x00000768+4*3))=0x02220050;
*((unsigned int *)((unsigned long)context_ptr+0x00000768+4*4))=0x0afe0306;
*((unsigned int *)((unsigned long)context_ptr+0x00000768+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000018c&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006320,"\x89\xc7\xf3\xc9\xfe\xc0\xdd\xce\xd6\x05\xea\xee\x08\x11\x72\x5e\x97\x8e\x33\xf0",20))
printf("strip: 89c7f3c9fec0ddce, Pass\n");
else
printf("strip: 89c7f3c9fec0ddce, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006308))=0x016a0a02;
*((unsigned int *)((unsigned long)context_ptr+0x00006308+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006308+4*2))=0x02020051;
*((unsigned int *)((unsigned long)context_ptr+0x00006308+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x000065f4))=0xc301b51b;
*((unsigned int *)((unsigned long)context_ptr+0x000065f4+4*1))=0x503a2bde;
*((unsigned int *)((unsigned long)context_ptr+0x000065f4+4*2))=0x51c6f961;
*((unsigned int *)((unsigned long)context_ptr+0x000065f4+4*3))=0x075f483f;
*((unsigned int *)((unsigned long)context_ptr+0x000065f4+4*4))=0x563864cf;
*((unsigned int *)((unsigned long)context_ptr+0x000065f4+4*5))=0xea5c5d1e;
*((unsigned int *)((unsigned long)context_ptr+0x000065f4+4*6))=0x7f3e6795;
*((unsigned int *)((unsigned long)context_ptr+0x000065f4+4*7))=0xe157a80a;
*((unsigned int *)((unsigned long)context_ptr+0x000065f4+4*8))=0x195f0fe8;
*((unsigned int *)((unsigned long)context_ptr+0x000065f4+4*9))=0xb5c0d7b8;
*((unsigned int *)((unsigned long)context_ptr+0x000065f4+4*10))=0x5f35c14a;
*((unsigned int *)((unsigned long)context_ptr+0x000065f4+4*11))=0x19cedff8;
*((unsigned int *)((unsigned long)context_ptr+0x000065f4+4*12))=0x25d2aa6c;
*((unsigned int *)((unsigned long)context_ptr+0x000065f4+4*13))=0x04a2f6c9;
*((unsigned int *)((unsigned long)context_ptr+0x000065f4+4*14))=0x231344c5;
*((unsigned int *)((unsigned long)context_ptr+0x000065f4+4*15))=0x61092944;
*((unsigned int *)((unsigned long)context_ptr+0x000065f4+4*16))=0x05c56211;
*((unsigned int *)((unsigned long)context_ptr+0x000065f4+4*17))=0x92de43be;
*((unsigned int *)((unsigned long)context_ptr+0x000065f4+4*18))=0x6e19e892;
*((unsigned int *)((unsigned long)context_ptr+0x000065f4+4*19))=0xd8086135;
*((unsigned int *)((unsigned long)context_ptr+0x000065f4+4*20))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00003780))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003780+4*1))=0x00006318;
*((unsigned int *)((unsigned long)context_ptr+0x00003780+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003780+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003780+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003780+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000780))=0x04c00051;
*((unsigned int *)((unsigned long)context_ptr+0x00000780+4*1))=0x000065f4;
*((unsigned int *)((unsigned long)context_ptr+0x00000780+4*2))=0x00006308;
*((unsigned int *)((unsigned long)context_ptr+0x00000780+4*3))=0x02220051;
*((unsigned int *)((unsigned long)context_ptr+0x00000780+4*4))=0x09f49334;
*((unsigned int *)((unsigned long)context_ptr+0x00000780+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000192&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006420,"\x5c\xe6\x77\x43\xa8\x28\x5c\xe2\x6e\x87\x95\x13\xc3\x36\xa2\x7c\x8c\xcb\x12\x30",20))
printf("strip: 5ce67743a8285ce2, Pass\n");
else
printf("strip: 5ce67743a8285ce2, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x0000632c))=0x016a0a02;
*((unsigned int *)((unsigned long)context_ptr+0x0000632c+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x0000632c+4*2))=0x02020052;
*((unsigned int *)((unsigned long)context_ptr+0x0000632c+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x000063dc))=0x4b11330c;
*((unsigned int *)((unsigned long)context_ptr+0x000063dc+4*1))=0x34708277;
*((unsigned int *)((unsigned long)context_ptr+0x000063dc+4*2))=0x84206067;
*((unsigned int *)((unsigned long)context_ptr+0x000063dc+4*3))=0x637d2f61;
*((unsigned int *)((unsigned long)context_ptr+0x000063dc+4*4))=0x7b8a6840;
*((unsigned int *)((unsigned long)context_ptr+0x000063dc+4*5))=0xac81dd2d;
*((unsigned int *)((unsigned long)context_ptr+0x000063dc+4*6))=0x234d6c70;
*((unsigned int *)((unsigned long)context_ptr+0x000063dc+4*7))=0xc207ff89;
*((unsigned int *)((unsigned long)context_ptr+0x000063dc+4*8))=0x3b829784;
*((unsigned int *)((unsigned long)context_ptr+0x000063dc+4*9))=0x978b77b7;
*((unsigned int *)((unsigned long)context_ptr+0x000063dc+4*10))=0xb7c60b91;
*((unsigned int *)((unsigned long)context_ptr+0x000063dc+4*11))=0x6ead3828;
*((unsigned int *)((unsigned long)context_ptr+0x000063dc+4*12))=0xca9c09fe;
*((unsigned int *)((unsigned long)context_ptr+0x000063dc+4*13))=0x513ef34f;
*((unsigned int *)((unsigned long)context_ptr+0x000063dc+4*14))=0xb2a51267;
*((unsigned int *)((unsigned long)context_ptr+0x000063dc+4*15))=0x975316c8;
*((unsigned int *)((unsigned long)context_ptr+0x000063dc+4*16))=0xde77a788;
*((unsigned int *)((unsigned long)context_ptr+0x000063dc+4*17))=0x230cc7ec;
*((unsigned int *)((unsigned long)context_ptr+0x000063dc+4*18))=0x6500e42d;
*((unsigned int *)((unsigned long)context_ptr+0x000063dc+4*19))=0x88d1f0f6;
*((unsigned int *)((unsigned long)context_ptr+0x000063dc+4*20))=0x0000bb58;
*((unsigned int *)((unsigned long)context_ptr+0x00003798))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003798+4*1))=0x00006648;
*((unsigned int *)((unsigned long)context_ptr+0x00003798+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003798+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003798+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003798+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000798))=0x04c00052;
*((unsigned int *)((unsigned long)context_ptr+0x00000798+4*1))=0x000063dc;
*((unsigned int *)((unsigned long)context_ptr+0x00000798+4*2))=0x0000632c;
*((unsigned int *)((unsigned long)context_ptr+0x00000798+4*3))=0x02220052;
*((unsigned int *)((unsigned long)context_ptr+0x00000798+4*4))=0x090afee7;
*((unsigned int *)((unsigned long)context_ptr+0x00000798+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000198&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x0000651c,"\xf7\x99\xde\xb3\x12\x3d\x50\x71\x5b\xf7\x71\x4a\xf5\x4c\x56\x5a\x66\x01\x38\x69",20))
printf("strip: f799deb3123d5071, Pass\n");
else
printf("strip: f799deb3123d5071, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x0000665c))=0x016a0a02;
*((unsigned int *)((unsigned long)context_ptr+0x0000665c+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x0000665c+4*2))=0x02020053;
*((unsigned int *)((unsigned long)context_ptr+0x0000665c+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x000064a8))=0xd640efa1;
*((unsigned int *)((unsigned long)context_ptr+0x000064a8+4*1))=0x9eaaf478;
*((unsigned int *)((unsigned long)context_ptr+0x000064a8+4*2))=0xdce056c2;
*((unsigned int *)((unsigned long)context_ptr+0x000064a8+4*3))=0x0404b4c9;
*((unsigned int *)((unsigned long)context_ptr+0x000064a8+4*4))=0x259e3ad5;
*((unsigned int *)((unsigned long)context_ptr+0x000064a8+4*5))=0x9b577c2d;
*((unsigned int *)((unsigned long)context_ptr+0x000064a8+4*6))=0xb94d795a;
*((unsigned int *)((unsigned long)context_ptr+0x000064a8+4*7))=0x37800608;
*((unsigned int *)((unsigned long)context_ptr+0x000064a8+4*8))=0x692182a8;
*((unsigned int *)((unsigned long)context_ptr+0x000064a8+4*9))=0x27a865d0;
*((unsigned int *)((unsigned long)context_ptr+0x000064a8+4*10))=0x9f319930;
*((unsigned int *)((unsigned long)context_ptr+0x000064a8+4*11))=0xc20389d8;
*((unsigned int *)((unsigned long)context_ptr+0x000064a8+4*12))=0x28496846;
*((unsigned int *)((unsigned long)context_ptr+0x000064a8+4*13))=0x5f0abca5;
*((unsigned int *)((unsigned long)context_ptr+0x000064a8+4*14))=0x03f9d6bc;
*((unsigned int *)((unsigned long)context_ptr+0x000064a8+4*15))=0xf30e081c;
*((unsigned int *)((unsigned long)context_ptr+0x000064a8+4*16))=0x9e451539;
*((unsigned int *)((unsigned long)context_ptr+0x000064a8+4*17))=0xc4e3e2e9;
*((unsigned int *)((unsigned long)context_ptr+0x000064a8+4*18))=0x247a36ca;
*((unsigned int *)((unsigned long)context_ptr+0x000064a8+4*19))=0xa4af6f55;
*((unsigned int *)((unsigned long)context_ptr+0x000064a8+4*20))=0x00b75374;
*((unsigned int *)((unsigned long)context_ptr+0x000037b0))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x000037b0+4*1))=0x0000633c;
*((unsigned int *)((unsigned long)context_ptr+0x000037b0+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000037b0+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000037b0+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000037b0+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x000007b0))=0x04c00053;
*((unsigned int *)((unsigned long)context_ptr+0x000007b0+4*1))=0x000064a8;
*((unsigned int *)((unsigned long)context_ptr+0x000007b0+4*2))=0x0000665c;
*((unsigned int *)((unsigned long)context_ptr+0x000007b0+4*3))=0x02220053;
*((unsigned int *)((unsigned long)context_ptr+0x000007b0+4*4))=0x0035439f;
*((unsigned int *)((unsigned long)context_ptr+0x000007b0+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000019e&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006434,"\x75\x04\xa5\x57\x30\xb8\x8c\xdf\x18\xc0\x3d\x9c\xd6\x93\x1a\x8e\x12\x63\x54\x63",20))
printf("strip: 7504a55730b88cdf, Pass\n");
else
printf("strip: 7504a55730b88cdf, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006350))=0x016a0a02;
*((unsigned int *)((unsigned long)context_ptr+0x00006350+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006350+4*2))=0x02020054;
*((unsigned int *)((unsigned long)context_ptr+0x00006350+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x000060a8))=0x0263d148;
*((unsigned int *)((unsigned long)context_ptr+0x000060a8+4*1))=0x0ac47dc3;
*((unsigned int *)((unsigned long)context_ptr+0x000060a8+4*2))=0x81ea9365;
*((unsigned int *)((unsigned long)context_ptr+0x000060a8+4*3))=0x517692ee;
*((unsigned int *)((unsigned long)context_ptr+0x000060a8+4*4))=0x5405c5c1;
*((unsigned int *)((unsigned long)context_ptr+0x000060a8+4*5))=0x568c3a50;
*((unsigned int *)((unsigned long)context_ptr+0x000060a8+4*6))=0x5526c028;
*((unsigned int *)((unsigned long)context_ptr+0x000060a8+4*7))=0x6d59c6e4;
*((unsigned int *)((unsigned long)context_ptr+0x000060a8+4*8))=0xc5fab35d;
*((unsigned int *)((unsigned long)context_ptr+0x000060a8+4*9))=0xf2600a00;
*((unsigned int *)((unsigned long)context_ptr+0x000060a8+4*10))=0x83d66294;
*((unsigned int *)((unsigned long)context_ptr+0x000060a8+4*11))=0xb03d8cbf;
*((unsigned int *)((unsigned long)context_ptr+0x000060a8+4*12))=0x029c1e34;
*((unsigned int *)((unsigned long)context_ptr+0x000060a8+4*13))=0x68654376;
*((unsigned int *)((unsigned long)context_ptr+0x000060a8+4*14))=0x4387176d;
*((unsigned int *)((unsigned long)context_ptr+0x000060a8+4*15))=0x9ed917e9;
*((unsigned int *)((unsigned long)context_ptr+0x000060a8+4*16))=0x8f8a8959;
*((unsigned int *)((unsigned long)context_ptr+0x000060a8+4*17))=0xbc1190e2;
*((unsigned int *)((unsigned long)context_ptr+0x000060a8+4*18))=0x2a7fc815;
*((unsigned int *)((unsigned long)context_ptr+0x000060a8+4*19))=0x9fd6ac50;
*((unsigned int *)((unsigned long)context_ptr+0x000060a8+4*20))=0x269730c5;
*((unsigned int *)((unsigned long)context_ptr+0x000037c8))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x000037c8+4*1))=0x00006430;
*((unsigned int *)((unsigned long)context_ptr+0x000037c8+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000037c8+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000037c8+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000037c8+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x000007c8))=0x04c00054;
*((unsigned int *)((unsigned long)context_ptr+0x000007c8+4*1))=0x000060a8;
*((unsigned int *)((unsigned long)context_ptr+0x000007c8+4*2))=0x00006350;
*((unsigned int *)((unsigned long)context_ptr+0x000007c8+4*3))=0x02220054;
*((unsigned int *)((unsigned long)context_ptr+0x000007c8+4*4))=0x001422f6;
*((unsigned int *)((unsigned long)context_ptr+0x000007c8+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000001a4&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006448,"\x25\xae\x4e\x01\x71\x78\x7c\xf0\xd9\xa1\x0c\x4c\xb7\xc1\x67\x1f\xfc\x0d\xe4\x6d",20))
printf("strip: 25ae4e0171787cf0, Pass\n");
else
printf("strip: 25ae4e0171787cf0, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006360))=0x016a0a02;
*((unsigned int *)((unsigned long)context_ptr+0x00006360+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006360+4*2))=0x02020055;
*((unsigned int *)((unsigned long)context_ptr+0x00006360+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x000060fc))=0x26f63b1a;
*((unsigned int *)((unsigned long)context_ptr+0x000060fc+4*1))=0x8f6b3dc5;
*((unsigned int *)((unsigned long)context_ptr+0x000060fc+4*2))=0x6af4e66a;
*((unsigned int *)((unsigned long)context_ptr+0x000060fc+4*3))=0xfa6e9679;
*((unsigned int *)((unsigned long)context_ptr+0x000060fc+4*4))=0x152d9ca1;
*((unsigned int *)((unsigned long)context_ptr+0x000060fc+4*5))=0x4a30440c;
*((unsigned int *)((unsigned long)context_ptr+0x000060fc+4*6))=0xb4ecb397;
*((unsigned int *)((unsigned long)context_ptr+0x000060fc+4*7))=0xd2da4aa1;
*((unsigned int *)((unsigned long)context_ptr+0x000060fc+4*8))=0xcbbbbbc4;
*((unsigned int *)((unsigned long)context_ptr+0x000060fc+4*9))=0xf3494390;
*((unsigned int *)((unsigned long)context_ptr+0x000060fc+4*10))=0x8c09762a;
*((unsigned int *)((unsigned long)context_ptr+0x000060fc+4*11))=0x4d08477c;
*((unsigned int *)((unsigned long)context_ptr+0x000060fc+4*12))=0x1c07c58e;
*((unsigned int *)((unsigned long)context_ptr+0x000060fc+4*13))=0xb6cccd75;
*((unsigned int *)((unsigned long)context_ptr+0x000060fc+4*14))=0x0d9cf14f;
*((unsigned int *)((unsigned long)context_ptr+0x000060fc+4*15))=0xe50b7e46;
*((unsigned int *)((unsigned long)context_ptr+0x000060fc+4*16))=0x4106876c;
*((unsigned int *)((unsigned long)context_ptr+0x000060fc+4*17))=0xae83945d;
*((unsigned int *)((unsigned long)context_ptr+0x000060fc+4*18))=0x9a63852d;
*((unsigned int *)((unsigned long)context_ptr+0x000060fc+4*19))=0x8f5d57ba;
*((unsigned int *)((unsigned long)context_ptr+0x000060fc+4*20))=0xb8bea0d3;
*((unsigned int *)((unsigned long)context_ptr+0x000060fc+4*21))=0x00000095;
*((unsigned int *)((unsigned long)context_ptr+0x000037e0))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x000037e0+4*1))=0x00006444;
*((unsigned int *)((unsigned long)context_ptr+0x000037e0+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000037e0+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000037e0+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000037e0+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x000007e0))=0x04c00055;
*((unsigned int *)((unsigned long)context_ptr+0x000007e0+4*1))=0x000060fc;
*((unsigned int *)((unsigned long)context_ptr+0x000007e0+4*2))=0x00006360;
*((unsigned int *)((unsigned long)context_ptr+0x000007e0+4*3))=0x02220055;
*((unsigned int *)((unsigned long)context_ptr+0x000007e0+4*4))=0x09fe9ae0;
*((unsigned int *)((unsigned long)context_ptr+0x000007e0+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000001aa&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x0000645c,"\xb2\x12\x90\x5d\xec\x14\x92\xa4\x69\x55\xed\xe5\x24\xcc\x5a\x24\xe2\xe6\xd3\x32",20))
printf("strip: b212905dec1492a4, Pass\n");
else
printf("strip: b212905dec1492a4, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006370))=0x016a0a02;
*((unsigned int *)((unsigned long)context_ptr+0x00006370+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006370+4*2))=0x02020056;
*((unsigned int *)((unsigned long)context_ptr+0x00006370+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x00006154))=0x7f691595;
*((unsigned int *)((unsigned long)context_ptr+0x00006154+4*1))=0x1a47b85e;
*((unsigned int *)((unsigned long)context_ptr+0x00006154+4*2))=0xb1944e29;
*((unsigned int *)((unsigned long)context_ptr+0x00006154+4*3))=0x87ce8d02;
*((unsigned int *)((unsigned long)context_ptr+0x00006154+4*4))=0xf0edf46c;
*((unsigned int *)((unsigned long)context_ptr+0x00006154+4*5))=0xed711e9e;
*((unsigned int *)((unsigned long)context_ptr+0x00006154+4*6))=0x4ddc8cbd;
*((unsigned int *)((unsigned long)context_ptr+0x00006154+4*7))=0x9bb9b4a3;
*((unsigned int *)((unsigned long)context_ptr+0x00006154+4*8))=0x42536867;
*((unsigned int *)((unsigned long)context_ptr+0x00006154+4*9))=0x925bada0;
*((unsigned int *)((unsigned long)context_ptr+0x00006154+4*10))=0xc0f83357;
*((unsigned int *)((unsigned long)context_ptr+0x00006154+4*11))=0x5fac01b2;
*((unsigned int *)((unsigned long)context_ptr+0x00006154+4*12))=0x263fee81;
*((unsigned int *)((unsigned long)context_ptr+0x00006154+4*13))=0x661688b4;
*((unsigned int *)((unsigned long)context_ptr+0x00006154+4*14))=0x7fe265e2;
*((unsigned int *)((unsigned long)context_ptr+0x00006154+4*15))=0x46c4b3dd;
*((unsigned int *)((unsigned long)context_ptr+0x00006154+4*16))=0xd3e9fbe5;
*((unsigned int *)((unsigned long)context_ptr+0x00006154+4*17))=0xfabd1cd8;
*((unsigned int *)((unsigned long)context_ptr+0x00006154+4*18))=0xb75d2d92;
*((unsigned int *)((unsigned long)context_ptr+0x00006154+4*19))=0x128a2a99;
*((unsigned int *)((unsigned long)context_ptr+0x00006154+4*20))=0x4ad309c3;
*((unsigned int *)((unsigned long)context_ptr+0x00006154+4*21))=0x0000e9ff;
*((unsigned int *)((unsigned long)context_ptr+0x000037f8))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x000037f8+4*1))=0x00006458;
*((unsigned int *)((unsigned long)context_ptr+0x000037f8+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000037f8+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000037f8+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000037f8+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x000007f8))=0x04c00056;
*((unsigned int *)((unsigned long)context_ptr+0x000007f8+4*1))=0x00006154;
*((unsigned int *)((unsigned long)context_ptr+0x000007f8+4*2))=0x00006370;
*((unsigned int *)((unsigned long)context_ptr+0x000007f8+4*3))=0x02220056;
*((unsigned int *)((unsigned long)context_ptr+0x000007f8+4*4))=0x08aca53f;
*((unsigned int *)((unsigned long)context_ptr+0x000007f8+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000001b0&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006530,"\xf5\x36\x62\x50\xf7\xdd\x74\xea\xd3\x58\xcc\x0f\xb5\x57\xcb\xbe\x30\xd2\x8f\x44",20))
printf("strip: f5366250f7dd74ea, Pass\n");
else
printf("strip: f5366250f7dd74ea, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x0000646c))=0x016a0a02;
*((unsigned int *)((unsigned long)context_ptr+0x0000646c+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x0000646c+4*2))=0x02020057;
*((unsigned int *)((unsigned long)context_ptr+0x0000646c+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x000061ac))=0x9d2e93ca;
*((unsigned int *)((unsigned long)context_ptr+0x000061ac+4*1))=0x2b41e401;
*((unsigned int *)((unsigned long)context_ptr+0x000061ac+4*2))=0xf592c5ff;
*((unsigned int *)((unsigned long)context_ptr+0x000061ac+4*3))=0xcb2ac6dd;
*((unsigned int *)((unsigned long)context_ptr+0x000061ac+4*4))=0xdd44491d;
*((unsigned int *)((unsigned long)context_ptr+0x000061ac+4*5))=0x932135b9;
*((unsigned int *)((unsigned long)context_ptr+0x000061ac+4*6))=0x43f038af;
*((unsigned int *)((unsigned long)context_ptr+0x000061ac+4*7))=0xdb5072d5;
*((unsigned int *)((unsigned long)context_ptr+0x000061ac+4*8))=0x4e8c7af8;
*((unsigned int *)((unsigned long)context_ptr+0x000061ac+4*9))=0xe9aa409e;
*((unsigned int *)((unsigned long)context_ptr+0x000061ac+4*10))=0x0fc9e688;
*((unsigned int *)((unsigned long)context_ptr+0x000061ac+4*11))=0x7a76bde0;
*((unsigned int *)((unsigned long)context_ptr+0x000061ac+4*12))=0x934a57c7;
*((unsigned int *)((unsigned long)context_ptr+0x000061ac+4*13))=0x220c6a04;
*((unsigned int *)((unsigned long)context_ptr+0x000061ac+4*14))=0xdd349fc8;
*((unsigned int *)((unsigned long)context_ptr+0x000061ac+4*15))=0x597b418b;
*((unsigned int *)((unsigned long)context_ptr+0x000061ac+4*16))=0x6aa8ff9e;
*((unsigned int *)((unsigned long)context_ptr+0x000061ac+4*17))=0xb2af8c8f;
*((unsigned int *)((unsigned long)context_ptr+0x000061ac+4*18))=0x4193788a;
*((unsigned int *)((unsigned long)context_ptr+0x000061ac+4*19))=0xa56f1e68;
*((unsigned int *)((unsigned long)context_ptr+0x000061ac+4*20))=0x94dc8a75;
*((unsigned int *)((unsigned long)context_ptr+0x000061ac+4*21))=0x004dc904;
*((unsigned int *)((unsigned long)context_ptr+0x00003810))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003810+4*1))=0x000064fc;
*((unsigned int *)((unsigned long)context_ptr+0x00003810+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003810+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003810+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003810+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000810))=0x04c00057;
*((unsigned int *)((unsigned long)context_ptr+0x00000810+4*1))=0x000061ac;
*((unsigned int *)((unsigned long)context_ptr+0x00000810+4*2))=0x0000646c;
*((unsigned int *)((unsigned long)context_ptr+0x00000810+4*3))=0x02220057;
*((unsigned int *)((unsigned long)context_ptr+0x00000810+4*4))=0x0d84c109;
*((unsigned int *)((unsigned long)context_ptr+0x00000810+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000001b6&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006480,"\xec\xcb\xa1\xf8\xf9\x7e\x4a\x8d\x0a\xfe\x05\xd0\xe1\x94\x84\x4f\x37\x74\x42\xc6",20))
printf("strip: eccba1f8f97e4a8d, Pass\n");
else
printf("strip: eccba1f8f97e4a8d, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006380))=0x016a0a02;
*((unsigned int *)((unsigned long)context_ptr+0x00006380+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006380+4*2))=0x02020058;
*((unsigned int *)((unsigned long)context_ptr+0x00006380+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x00006758))=0x6314c44a;
*((unsigned int *)((unsigned long)context_ptr+0x00006758+4*1))=0x040df304;
*((unsigned int *)((unsigned long)context_ptr+0x00006758+4*2))=0x0c4ba0da;
*((unsigned int *)((unsigned long)context_ptr+0x00006758+4*3))=0xb0ccb939;
*((unsigned int *)((unsigned long)context_ptr+0x00006758+4*4))=0x4ed3cd0e;
*((unsigned int *)((unsigned long)context_ptr+0x00006758+4*5))=0xe45abb3f;
*((unsigned int *)((unsigned long)context_ptr+0x00006758+4*6))=0x90a37a9e;
*((unsigned int *)((unsigned long)context_ptr+0x00006758+4*7))=0x42ef74d6;
*((unsigned int *)((unsigned long)context_ptr+0x00006758+4*8))=0x8459f119;
*((unsigned int *)((unsigned long)context_ptr+0x00006758+4*9))=0x8f9c5f4a;
*((unsigned int *)((unsigned long)context_ptr+0x00006758+4*10))=0x16a09286;
*((unsigned int *)((unsigned long)context_ptr+0x00006758+4*11))=0x6b7f38d6;
*((unsigned int *)((unsigned long)context_ptr+0x00006758+4*12))=0x0b46f634;
*((unsigned int *)((unsigned long)context_ptr+0x00006758+4*13))=0x832a5b1e;
*((unsigned int *)((unsigned long)context_ptr+0x00006758+4*14))=0x08fd53f9;
*((unsigned int *)((unsigned long)context_ptr+0x00006758+4*15))=0xabeebe85;
*((unsigned int *)((unsigned long)context_ptr+0x00006758+4*16))=0xbc771ce4;
*((unsigned int *)((unsigned long)context_ptr+0x00006758+4*17))=0x98dc5389;
*((unsigned int *)((unsigned long)context_ptr+0x00006758+4*18))=0x6bc87508;
*((unsigned int *)((unsigned long)context_ptr+0x00006758+4*19))=0x3d8d7c2a;
*((unsigned int *)((unsigned long)context_ptr+0x00006758+4*20))=0x5ff484a1;
*((unsigned int *)((unsigned long)context_ptr+0x00006758+4*21))=0xb3c9e2da;
*((unsigned int *)((unsigned long)context_ptr+0x00003828))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003828+4*1))=0x0000647c;
*((unsigned int *)((unsigned long)context_ptr+0x00003828+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003828+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003828+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003828+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000828))=0x04c00058;
*((unsigned int *)((unsigned long)context_ptr+0x00000828+4*1))=0x00006758;
*((unsigned int *)((unsigned long)context_ptr+0x00000828+4*2))=0x00006380;
*((unsigned int *)((unsigned long)context_ptr+0x00000828+4*3))=0x02220058;
*((unsigned int *)((unsigned long)context_ptr+0x00000828+4*4))=0x08987322;
*((unsigned int *)((unsigned long)context_ptr+0x00000828+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000001bc&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000063a4,"\x02\xec\x93\xdb\xcc\x9e\x3a\x49\xaf\x10\x1e\x5d\x79\x0b\x8d\x6b\x22\x95\x35\xe3",20))
printf("strip: 02ec93dbcc9e3a49, Pass\n");
else
printf("strip: 02ec93dbcc9e3a49, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006390))=0x016a0a02;
*((unsigned int *)((unsigned long)context_ptr+0x00006390+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006390+4*2))=0x02020059;
*((unsigned int *)((unsigned long)context_ptr+0x00006390+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x00006510))=0xe4d9f1e8;
*((unsigned int *)((unsigned long)context_ptr+0x00006510+4*1))=0x2db8de7f;
*((unsigned int *)((unsigned long)context_ptr+0x00006510+4*2))=0xe4e34b33;
*((unsigned int *)((unsigned long)context_ptr+0x00006510+4*3))=0x1006fdc9;
*((unsigned int *)((unsigned long)context_ptr+0x00006510+4*4))=0x17d8655d;
*((unsigned int *)((unsigned long)context_ptr+0x00006510+4*5))=0x5ff6335f;
*((unsigned int *)((unsigned long)context_ptr+0x00006510+4*6))=0x5f127e39;
*((unsigned int *)((unsigned long)context_ptr+0x00006510+4*7))=0x2684705d;
*((unsigned int *)((unsigned long)context_ptr+0x00006510+4*8))=0x4f62ad19;
*((unsigned int *)((unsigned long)context_ptr+0x00006510+4*9))=0x453a815a;
*((unsigned int *)((unsigned long)context_ptr+0x00006510+4*10))=0x5bcf5df6;
*((unsigned int *)((unsigned long)context_ptr+0x00006510+4*11))=0xfd331220;
*((unsigned int *)((unsigned long)context_ptr+0x00006510+4*12))=0x9adafd6b;
*((unsigned int *)((unsigned long)context_ptr+0x00006510+4*13))=0x3ec62a2c;
*((unsigned int *)((unsigned long)context_ptr+0x00006510+4*14))=0x388e6779;
*((unsigned int *)((unsigned long)context_ptr+0x00006510+4*15))=0x3fbbf3bb;
*((unsigned int *)((unsigned long)context_ptr+0x00006510+4*16))=0x625527d8;
*((unsigned int *)((unsigned long)context_ptr+0x00006510+4*17))=0x2850598d;
*((unsigned int *)((unsigned long)context_ptr+0x00006510+4*18))=0xf9bfb063;
*((unsigned int *)((unsigned long)context_ptr+0x00006510+4*19))=0xc50c98a1;
*((unsigned int *)((unsigned long)context_ptr+0x00006510+4*20))=0x02fd3c72;
*((unsigned int *)((unsigned long)context_ptr+0x00006510+4*21))=0x3d3aed79;
*((unsigned int *)((unsigned long)context_ptr+0x00006510+4*22))=0x00000021;
*((unsigned int *)((unsigned long)context_ptr+0x00003840))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003840+4*1))=0x000063a0;
*((unsigned int *)((unsigned long)context_ptr+0x00003840+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003840+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003840+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003840+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000840))=0x04c00059;
*((unsigned int *)((unsigned long)context_ptr+0x00000840+4*1))=0x00006510;
*((unsigned int *)((unsigned long)context_ptr+0x00000840+4*2))=0x00006390;
*((unsigned int *)((unsigned long)context_ptr+0x00000840+4*3))=0x02220059;
*((unsigned int *)((unsigned long)context_ptr+0x00000840+4*4))=0x0a9df255;
*((unsigned int *)((unsigned long)context_ptr+0x00000840+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000001c2&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006590,"\xc6\xaa\x27\xa9\xb7\xa4\xc7\x5c\x21\xc5\x5d\xed\xf5\x28\x3f\xc4\xba\xea\xb0\x0c",20))
printf("strip: c6aa27a9b7a4c75c, Pass\n");
else
printf("strip: c6aa27a9b7a4c75c, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000063b4))=0x016a0a02;
*((unsigned int *)((unsigned long)context_ptr+0x000063b4+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000063b4+4*2))=0x0202005a;
*((unsigned int *)((unsigned long)context_ptr+0x000063b4+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x00006204))=0x50a755d1;
*((unsigned int *)((unsigned long)context_ptr+0x00006204+4*1))=0x5942ec17;
*((unsigned int *)((unsigned long)context_ptr+0x00006204+4*2))=0x2595dc28;
*((unsigned int *)((unsigned long)context_ptr+0x00006204+4*3))=0xaba3c6d3;
*((unsigned int *)((unsigned long)context_ptr+0x00006204+4*4))=0xdbb42769;
*((unsigned int *)((unsigned long)context_ptr+0x00006204+4*5))=0xd69e1955;
*((unsigned int *)((unsigned long)context_ptr+0x00006204+4*6))=0x0ec627fb;
*((unsigned int *)((unsigned long)context_ptr+0x00006204+4*7))=0x0f1f0184;
*((unsigned int *)((unsigned long)context_ptr+0x00006204+4*8))=0x2c99ffca;
*((unsigned int *)((unsigned long)context_ptr+0x00006204+4*9))=0x8158304b;
*((unsigned int *)((unsigned long)context_ptr+0x00006204+4*10))=0x1656589f;
*((unsigned int *)((unsigned long)context_ptr+0x00006204+4*11))=0xe0dc4b05;
*((unsigned int *)((unsigned long)context_ptr+0x00006204+4*12))=0x724380f0;
*((unsigned int *)((unsigned long)context_ptr+0x00006204+4*13))=0x234a761b;
*((unsigned int *)((unsigned long)context_ptr+0x00006204+4*14))=0x56d51556;
*((unsigned int *)((unsigned long)context_ptr+0x00006204+4*15))=0x0b912aff;
*((unsigned int *)((unsigned long)context_ptr+0x00006204+4*16))=0xfe356bd2;
*((unsigned int *)((unsigned long)context_ptr+0x00006204+4*17))=0x7635d342;
*((unsigned int *)((unsigned long)context_ptr+0x00006204+4*18))=0x0c6a50c1;
*((unsigned int *)((unsigned long)context_ptr+0x00006204+4*19))=0xa73f783a;
*((unsigned int *)((unsigned long)context_ptr+0x00006204+4*20))=0x42f9c354;
*((unsigned int *)((unsigned long)context_ptr+0x00006204+4*21))=0x604dd3f5;
*((unsigned int *)((unsigned long)context_ptr+0x00006204+4*22))=0x00001d4f;
*((unsigned int *)((unsigned long)context_ptr+0x00003858))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003858+4*1))=0x0000656c;
*((unsigned int *)((unsigned long)context_ptr+0x00003858+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003858+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003858+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003858+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000858))=0x04c0005a;
*((unsigned int *)((unsigned long)context_ptr+0x00000858+4*1))=0x00006204;
*((unsigned int *)((unsigned long)context_ptr+0x00000858+4*2))=0x000063b4;
*((unsigned int *)((unsigned long)context_ptr+0x00000858+4*3))=0x0222005a;
*((unsigned int *)((unsigned long)context_ptr+0x00000858+4*4))=0x0ff73074;
*((unsigned int *)((unsigned long)context_ptr+0x00000858+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000001c8&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000063c8,"\x60\xcb\xb7\x3a\xa5\xac\xab\x10\x07\xbb\x5d\x9e\xbd\x7f\x8c\xf0\x75\xc8\x91\x34",20))
printf("strip: 60cbb73aa5acab10, Pass\n");
else
printf("strip: 60cbb73aa5acab10, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006040))=0x016a0a02;
*((unsigned int *)((unsigned long)context_ptr+0x00006040+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006040+4*2))=0x0202005b;
*((unsigned int *)((unsigned long)context_ptr+0x00006040+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x000067b0))=0xa9496468;
*((unsigned int *)((unsigned long)context_ptr+0x000067b0+4*1))=0x2afa32bd;
*((unsigned int *)((unsigned long)context_ptr+0x000067b0+4*2))=0x2661e004;
*((unsigned int *)((unsigned long)context_ptr+0x000067b0+4*3))=0x30668837;
*((unsigned int *)((unsigned long)context_ptr+0x000067b0+4*4))=0xb4b5fe1b;
*((unsigned int *)((unsigned long)context_ptr+0x000067b0+4*5))=0x9898691e;
*((unsigned int *)((unsigned long)context_ptr+0x000067b0+4*6))=0x3b98e523;
*((unsigned int *)((unsigned long)context_ptr+0x000067b0+4*7))=0x73fd8c78;
*((unsigned int *)((unsigned long)context_ptr+0x000067b0+4*8))=0xc65f4823;
*((unsigned int *)((unsigned long)context_ptr+0x000067b0+4*9))=0x672c78a4;
*((unsigned int *)((unsigned long)context_ptr+0x000067b0+4*10))=0xd29a8ab2;
*((unsigned int *)((unsigned long)context_ptr+0x000067b0+4*11))=0x898ee91a;
*((unsigned int *)((unsigned long)context_ptr+0x000067b0+4*12))=0xf2e09f68;
*((unsigned int *)((unsigned long)context_ptr+0x000067b0+4*13))=0x9c5f357e;
*((unsigned int *)((unsigned long)context_ptr+0x000067b0+4*14))=0x0891f3ef;
*((unsigned int *)((unsigned long)context_ptr+0x000067b0+4*15))=0xb372fed9;
*((unsigned int *)((unsigned long)context_ptr+0x000067b0+4*16))=0x6bcaa098;
*((unsigned int *)((unsigned long)context_ptr+0x000067b0+4*17))=0xb42a4b44;
*((unsigned int *)((unsigned long)context_ptr+0x000067b0+4*18))=0x9a7d45c4;
*((unsigned int *)((unsigned long)context_ptr+0x000067b0+4*19))=0x3e127f91;
*((unsigned int *)((unsigned long)context_ptr+0x000067b0+4*20))=0x17587bb6;
*((unsigned int *)((unsigned long)context_ptr+0x000067b0+4*21))=0x88237b9c;
*((unsigned int *)((unsigned long)context_ptr+0x000067b0+4*22))=0x00567e90;
*((unsigned int *)((unsigned long)context_ptr+0x00003870))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003870+4*1))=0x000063c4;
*((unsigned int *)((unsigned long)context_ptr+0x00003870+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003870+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003870+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003870+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000870))=0x04c0005b;
*((unsigned int *)((unsigned long)context_ptr+0x00000870+4*1))=0x000067b0;
*((unsigned int *)((unsigned long)context_ptr+0x00000870+4*2))=0x00006040;
*((unsigned int *)((unsigned long)context_ptr+0x00000870+4*3))=0x0222005b;
*((unsigned int *)((unsigned long)context_ptr+0x00000870+4*4))=0x074d0dab;
*((unsigned int *)((unsigned long)context_ptr+0x00000870+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000001ce&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006060,"\x00\x70\x04\x71\x60\x07\xfe\xbb\x41\xa7\x19\x19\x5f\xb7\x8e\x3b\x42\x6c\xe1\x35",20))
printf("strip: 007004716007febb, Pass\n");
else
printf("strip: 007004716007febb, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006030))=0x016a0a02;
*((unsigned int *)((unsigned long)context_ptr+0x00006030+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006030+4*2))=0x0202005c;
*((unsigned int *)((unsigned long)context_ptr+0x00006030+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x0000666c))=0x8fcd5e8b;
*((unsigned int *)((unsigned long)context_ptr+0x0000666c+4*1))=0xb8ea6a0c;
*((unsigned int *)((unsigned long)context_ptr+0x0000666c+4*2))=0x9fe82090;
*((unsigned int *)((unsigned long)context_ptr+0x0000666c+4*3))=0x13ebc9bc;
*((unsigned int *)((unsigned long)context_ptr+0x0000666c+4*4))=0xf39d0c3c;
*((unsigned int *)((unsigned long)context_ptr+0x0000666c+4*5))=0x1fa77c50;
*((unsigned int *)((unsigned long)context_ptr+0x0000666c+4*6))=0x888e8ff9;
*((unsigned int *)((unsigned long)context_ptr+0x0000666c+4*7))=0xbd064507;
*((unsigned int *)((unsigned long)context_ptr+0x0000666c+4*8))=0x0e20e75b;
*((unsigned int *)((unsigned long)context_ptr+0x0000666c+4*9))=0x948f2d09;
*((unsigned int *)((unsigned long)context_ptr+0x0000666c+4*10))=0x812f74b4;
*((unsigned int *)((unsigned long)context_ptr+0x0000666c+4*11))=0xe1359134;
*((unsigned int *)((unsigned long)context_ptr+0x0000666c+4*12))=0xea34c471;
*((unsigned int *)((unsigned long)context_ptr+0x0000666c+4*13))=0xcbedac01;
*((unsigned int *)((unsigned long)context_ptr+0x0000666c+4*14))=0x05f206a0;
*((unsigned int *)((unsigned long)context_ptr+0x0000666c+4*15))=0x4ab520b3;
*((unsigned int *)((unsigned long)context_ptr+0x0000666c+4*16))=0x560ede5d;
*((unsigned int *)((unsigned long)context_ptr+0x0000666c+4*17))=0x3cfa9176;
*((unsigned int *)((unsigned long)context_ptr+0x0000666c+4*18))=0x244554b9;
*((unsigned int *)((unsigned long)context_ptr+0x0000666c+4*19))=0xbb0c0419;
*((unsigned int *)((unsigned long)context_ptr+0x0000666c+4*20))=0x9a2034f0;
*((unsigned int *)((unsigned long)context_ptr+0x0000666c+4*21))=0xef1d18c0;
*((unsigned int *)((unsigned long)context_ptr+0x0000666c+4*22))=0x4046235b;
*((unsigned int *)((unsigned long)context_ptr+0x00003888))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003888+4*1))=0x00006060;
*((unsigned int *)((unsigned long)context_ptr+0x00003888+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003888+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003888+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003888+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000888))=0x04c0005c;
*((unsigned int *)((unsigned long)context_ptr+0x00000888+4*1))=0x0000666c;
*((unsigned int *)((unsigned long)context_ptr+0x00000888+4*2))=0x00006030;
*((unsigned int *)((unsigned long)context_ptr+0x00000888+4*3))=0x0222005c;
*((unsigned int *)((unsigned long)context_ptr+0x00000888+4*4))=0x06152db7;
*((unsigned int *)((unsigned long)context_ptr+0x00000888+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000001d4&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006084,"\xa9\x34\x4f\xe4\x32\xf7\x72\xee\xa7\xe3\x3a\x3b\x3d\xc0\xf2\x05\x7d\xe7\x7d\xc9",20))
printf("strip: a9344fe432f772ee, Pass\n");
else
printf("strip: a9344fe432f772ee, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006050))=0x016a0a02;
*((unsigned int *)((unsigned long)context_ptr+0x00006050+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006050+4*2))=0x0202005d;
*((unsigned int *)((unsigned long)context_ptr+0x00006050+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x000066c8))=0xcdf14d6b;
*((unsigned int *)((unsigned long)context_ptr+0x000066c8+4*1))=0x5453530a;
*((unsigned int *)((unsigned long)context_ptr+0x000066c8+4*2))=0x292c1466;
*((unsigned int *)((unsigned long)context_ptr+0x000066c8+4*3))=0x5009ad8d;
*((unsigned int *)((unsigned long)context_ptr+0x000066c8+4*4))=0x8bb7bbf3;
*((unsigned int *)((unsigned long)context_ptr+0x000066c8+4*5))=0x8c20a402;
*((unsigned int *)((unsigned long)context_ptr+0x000066c8+4*6))=0x49a97d18;
*((unsigned int *)((unsigned long)context_ptr+0x000066c8+4*7))=0x0661f3bf;
*((unsigned int *)((unsigned long)context_ptr+0x000066c8+4*8))=0x87463c9a;
*((unsigned int *)((unsigned long)context_ptr+0x000066c8+4*9))=0x1d49de41;
*((unsigned int *)((unsigned long)context_ptr+0x000066c8+4*10))=0xb0be1ea5;
*((unsigned int *)((unsigned long)context_ptr+0x000066c8+4*11))=0xe551462a;
*((unsigned int *)((unsigned long)context_ptr+0x000066c8+4*12))=0xf93ec3f8;
*((unsigned int *)((unsigned long)context_ptr+0x000066c8+4*13))=0x0a7a3147;
*((unsigned int *)((unsigned long)context_ptr+0x000066c8+4*14))=0x1cb830e5;
*((unsigned int *)((unsigned long)context_ptr+0x000066c8+4*15))=0xc38ffe4a;
*((unsigned int *)((unsigned long)context_ptr+0x000066c8+4*16))=0x9b7e1850;
*((unsigned int *)((unsigned long)context_ptr+0x000066c8+4*17))=0xbed73d54;
*((unsigned int *)((unsigned long)context_ptr+0x000066c8+4*18))=0xc37b7c3c;
*((unsigned int *)((unsigned long)context_ptr+0x000066c8+4*19))=0x3da19785;
*((unsigned int *)((unsigned long)context_ptr+0x000066c8+4*20))=0xcf55ae0e;
*((unsigned int *)((unsigned long)context_ptr+0x000066c8+4*21))=0x0ddbb0ef;
*((unsigned int *)((unsigned long)context_ptr+0x000066c8+4*22))=0x54c5c7d7;
*((unsigned int *)((unsigned long)context_ptr+0x000066c8+4*23))=0x00000004;
*((unsigned int *)((unsigned long)context_ptr+0x000038a0))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x000038a0+4*1))=0x00006084;
*((unsigned int *)((unsigned long)context_ptr+0x000038a0+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000038a0+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000038a0+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000038a0+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x000008a0))=0x04c0005d;
*((unsigned int *)((unsigned long)context_ptr+0x000008a0+4*1))=0x000066c8;
*((unsigned int *)((unsigned long)context_ptr+0x000008a0+4*2))=0x00006050;
*((unsigned int *)((unsigned long)context_ptr+0x000008a0+4*3))=0x0222005d;
*((unsigned int *)((unsigned long)context_ptr+0x000008a0+4*4))=0x0e77ad10;
*((unsigned int *)((unsigned long)context_ptr+0x000008a0+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000001da&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006494,"\x37\x24\x06\x39\x15\x7d\x9c\x7f\x07\xfd\x3d\xb0\xe4\x71\x3b\xbc\xfc\x99\x69\x45",20))
printf("strip: 37240639157d9c7f, Pass\n");
else
printf("strip: 37240639157d9c7f, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006074))=0x016a0a02;
*((unsigned int *)((unsigned long)context_ptr+0x00006074+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006074+4*2))=0x0202005e;
*((unsigned int *)((unsigned long)context_ptr+0x00006074+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x00006260))=0x9c26c654;
*((unsigned int *)((unsigned long)context_ptr+0x00006260+4*1))=0x01079903;
*((unsigned int *)((unsigned long)context_ptr+0x00006260+4*2))=0xd63dc48b;
*((unsigned int *)((unsigned long)context_ptr+0x00006260+4*3))=0x5e2a0717;
*((unsigned int *)((unsigned long)context_ptr+0x00006260+4*4))=0x6cac4983;
*((unsigned int *)((unsigned long)context_ptr+0x00006260+4*5))=0x5116ca02;
*((unsigned int *)((unsigned long)context_ptr+0x00006260+4*6))=0xcdd1c327;
*((unsigned int *)((unsigned long)context_ptr+0x00006260+4*7))=0xb0eb1ff7;
*((unsigned int *)((unsigned long)context_ptr+0x00006260+4*8))=0x1a1cfa1e;
*((unsigned int *)((unsigned long)context_ptr+0x00006260+4*9))=0xee1c3dab;
*((unsigned int *)((unsigned long)context_ptr+0x00006260+4*10))=0x9e4f30e2;
*((unsigned int *)((unsigned long)context_ptr+0x00006260+4*11))=0x9d93de90;
*((unsigned int *)((unsigned long)context_ptr+0x00006260+4*12))=0x54042fed;
*((unsigned int *)((unsigned long)context_ptr+0x00006260+4*13))=0x1076aaed;
*((unsigned int *)((unsigned long)context_ptr+0x00006260+4*14))=0x36310874;
*((unsigned int *)((unsigned long)context_ptr+0x00006260+4*15))=0xb51dc77a;
*((unsigned int *)((unsigned long)context_ptr+0x00006260+4*16))=0xf103af82;
*((unsigned int *)((unsigned long)context_ptr+0x00006260+4*17))=0xae246517;
*((unsigned int *)((unsigned long)context_ptr+0x00006260+4*18))=0xd11e3e4a;
*((unsigned int *)((unsigned long)context_ptr+0x00006260+4*19))=0x64cc4234;
*((unsigned int *)((unsigned long)context_ptr+0x00006260+4*20))=0x88dfc8b1;
*((unsigned int *)((unsigned long)context_ptr+0x00006260+4*21))=0x8e96d139;
*((unsigned int *)((unsigned long)context_ptr+0x00006260+4*22))=0x5b999f27;
*((unsigned int *)((unsigned long)context_ptr+0x00006260+4*23))=0x000073bd;
*((unsigned int *)((unsigned long)context_ptr+0x000038b8))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x000038b8+4*1))=0x00006490;
*((unsigned int *)((unsigned long)context_ptr+0x000038b8+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000038b8+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000038b8+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000038b8+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x000008b8))=0x04c0005e;
*((unsigned int *)((unsigned long)context_ptr+0x000008b8+4*1))=0x00006260;
*((unsigned int *)((unsigned long)context_ptr+0x000008b8+4*2))=0x00006074;
*((unsigned int *)((unsigned long)context_ptr+0x000008b8+4*3))=0x0222005e;
*((unsigned int *)((unsigned long)context_ptr+0x000008b8+4*4))=0x0e890c0f;
*((unsigned int *)((unsigned long)context_ptr+0x000008b8+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000001e0&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000062f4,"\x18\xaa\xfc\xe0\x04\xc7\x67\x2a\xfe\xda\xa7\xd8\x1e\xf5\x62\x28\x20\x52\x7e\xb9",20))
printf("strip: 18aafce004c7672a, Pass\n");
else
printf("strip: 18aafce004c7672a, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006098))=0x016a0a02;
*((unsigned int *)((unsigned long)context_ptr+0x00006098+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006098+4*2))=0x0202005f;
*((unsigned int *)((unsigned long)context_ptr+0x00006098+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x00006580))=0xf8241b46;
*((unsigned int *)((unsigned long)context_ptr+0x00006580+4*1))=0x8cb1ffdc;
*((unsigned int *)((unsigned long)context_ptr+0x00006580+4*2))=0x5c34ca1c;
*((unsigned int *)((unsigned long)context_ptr+0x00006580+4*3))=0x9e41662f;
*((unsigned int *)((unsigned long)context_ptr+0x00006580+4*4))=0xacf1dc26;
*((unsigned int *)((unsigned long)context_ptr+0x00006580+4*5))=0xe1995242;
*((unsigned int *)((unsigned long)context_ptr+0x00006580+4*6))=0xcadb9db7;
*((unsigned int *)((unsigned long)context_ptr+0x00006580+4*7))=0xd87f30b3;
*((unsigned int *)((unsigned long)context_ptr+0x00006580+4*8))=0xb3161064;
*((unsigned int *)((unsigned long)context_ptr+0x00006580+4*9))=0xd43c3cb9;
*((unsigned int *)((unsigned long)context_ptr+0x00006580+4*10))=0x307630cb;
*((unsigned int *)((unsigned long)context_ptr+0x00006580+4*11))=0xf703d93a;
*((unsigned int *)((unsigned long)context_ptr+0x00006580+4*12))=0x5c6e8f29;
*((unsigned int *)((unsigned long)context_ptr+0x00006580+4*13))=0xd068aaf3;
*((unsigned int *)((unsigned long)context_ptr+0x00006580+4*14))=0x6cdb5552;
*((unsigned int *)((unsigned long)context_ptr+0x00006580+4*15))=0xdc576e5b;
*((unsigned int *)((unsigned long)context_ptr+0x00006580+4*16))=0x8a9d8a81;
*((unsigned int *)((unsigned long)context_ptr+0x00006580+4*17))=0x131f156b;
*((unsigned int *)((unsigned long)context_ptr+0x00006580+4*18))=0xf5237446;
*((unsigned int *)((unsigned long)context_ptr+0x00006580+4*19))=0x8c4e7a91;
*((unsigned int *)((unsigned long)context_ptr+0x00006580+4*20))=0xfda918b9;
*((unsigned int *)((unsigned long)context_ptr+0x00006580+4*21))=0xa2523e31;
*((unsigned int *)((unsigned long)context_ptr+0x00006580+4*22))=0x91e7faa8;
*((unsigned int *)((unsigned long)context_ptr+0x00006580+4*23))=0x00a487ce;
*((unsigned int *)((unsigned long)context_ptr+0x000038d0))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x000038d0+4*1))=0x000065e0;
*((unsigned int *)((unsigned long)context_ptr+0x000038d0+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000038d0+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000038d0+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000038d0+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x000008d0))=0x04c0005f;
*((unsigned int *)((unsigned long)context_ptr+0x000008d0+4*1))=0x00006580;
*((unsigned int *)((unsigned long)context_ptr+0x000008d0+4*2))=0x00006098;
*((unsigned int *)((unsigned long)context_ptr+0x000008d0+4*3))=0x0222005f;
*((unsigned int *)((unsigned long)context_ptr+0x000008d0+4*4))=0x021499f7;
*((unsigned int *)((unsigned long)context_ptr+0x000008d0+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000001e6&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006318,"\x7c\xd4\x38\xe0\xb8\x97\x9a\xa7\x57\xa4\x59\x9c\x84\xe7\x5f\x4a\xc7\xc9\xff\x31",20))
printf("strip: 7cd438e0b8979aa7, Pass\n");
else
printf("strip: 7cd438e0b8979aa7, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006728))=0x016a0a02;
*((unsigned int *)((unsigned long)context_ptr+0x00006728+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006728+4*2))=0x02020060;
*((unsigned int *)((unsigned long)context_ptr+0x00006728+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x000062c0))=0xee06704b;
*((unsigned int *)((unsigned long)context_ptr+0x000062c0+4*1))=0xee9f9768;
*((unsigned int *)((unsigned long)context_ptr+0x000062c0+4*2))=0xf182ba38;
*((unsigned int *)((unsigned long)context_ptr+0x000062c0+4*3))=0xf5531712;
*((unsigned int *)((unsigned long)context_ptr+0x000062c0+4*4))=0x55442258;
*((unsigned int *)((unsigned long)context_ptr+0x000062c0+4*5))=0x50142252;
*((unsigned int *)((unsigned long)context_ptr+0x000062c0+4*6))=0x7c86ab4f;
*((unsigned int *)((unsigned long)context_ptr+0x000062c0+4*7))=0xd0de945c;
*((unsigned int *)((unsigned long)context_ptr+0x000062c0+4*8))=0xb3f5f966;
*((unsigned int *)((unsigned long)context_ptr+0x000062c0+4*9))=0x4bb2e51a;
*((unsigned int *)((unsigned long)context_ptr+0x000062c0+4*10))=0x5cc704c5;
*((unsigned int *)((unsigned long)context_ptr+0x000062c0+4*11))=0x82e78e54;
*((unsigned int *)((unsigned long)context_ptr+0x000062c0+4*12))=0xc95e7539;
*((unsigned int *)((unsigned long)context_ptr+0x000062c0+4*13))=0x8fee1d06;
*((unsigned int *)((unsigned long)context_ptr+0x000062c0+4*14))=0xe917a0fe;
*((unsigned int *)((unsigned long)context_ptr+0x000062c0+4*15))=0xde65ba3a;
*((unsigned int *)((unsigned long)context_ptr+0x000062c0+4*16))=0xc1cf93d5;
*((unsigned int *)((unsigned long)context_ptr+0x000062c0+4*17))=0xdcb5fca5;
*((unsigned int *)((unsigned long)context_ptr+0x000062c0+4*18))=0xf8ddd4c8;
*((unsigned int *)((unsigned long)context_ptr+0x000062c0+4*19))=0x410a51a5;
*((unsigned int *)((unsigned long)context_ptr+0x000062c0+4*20))=0x4426c5cc;
*((unsigned int *)((unsigned long)context_ptr+0x000062c0+4*21))=0x2e0c8825;
*((unsigned int *)((unsigned long)context_ptr+0x000062c0+4*22))=0xc220fc46;
*((unsigned int *)((unsigned long)context_ptr+0x000062c0+4*23))=0x94c103cd;
*((unsigned int *)((unsigned long)context_ptr+0x000038e8))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x000038e8+4*1))=0x00006738;
*((unsigned int *)((unsigned long)context_ptr+0x000038e8+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000038e8+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000038e8+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000038e8+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x000008e8))=0x04c00060;
*((unsigned int *)((unsigned long)context_ptr+0x000008e8+4*1))=0x000062c0;
*((unsigned int *)((unsigned long)context_ptr+0x000008e8+4*2))=0x00006728;
*((unsigned int *)((unsigned long)context_ptr+0x000008e8+4*3))=0x02220060;
*((unsigned int *)((unsigned long)context_ptr+0x000008e8+4*4))=0x09699709;
*((unsigned int *)((unsigned long)context_ptr+0x000008e8+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000001ec&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006648,"\xca\x42\xcf\x32\xfb\xd6\x1d\x16\x06\xc8\x7a\x02\x1c\x14\xbb\x88\x82\xc9\x5b\xeb",20))
printf("strip: ca42cf32fbd61d16, Pass\n");
else
printf("strip: ca42cf32fbd61d16, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006320))=0x016a0a02;
*((unsigned int *)((unsigned long)context_ptr+0x00006320+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006320+4*2))=0x02020061;
*((unsigned int *)((unsigned long)context_ptr+0x00006320+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x000065f4))=0x5a43fa65;
*((unsigned int *)((unsigned long)context_ptr+0x000065f4+4*1))=0x14d8b530;
*((unsigned int *)((unsigned long)context_ptr+0x000065f4+4*2))=0x9dbfd393;
*((unsigned int *)((unsigned long)context_ptr+0x000065f4+4*3))=0x63c82121;
*((unsigned int *)((unsigned long)context_ptr+0x000065f4+4*4))=0x0fecf66d;
*((unsigned int *)((unsigned long)context_ptr+0x000065f4+4*5))=0x6bae227c;
*((unsigned int *)((unsigned long)context_ptr+0x000065f4+4*6))=0xe3929afe;
*((unsigned int *)((unsigned long)context_ptr+0x000065f4+4*7))=0xd1c33f53;
*((unsigned int *)((unsigned long)context_ptr+0x000065f4+4*8))=0xb6e009ac;
*((unsigned int *)((unsigned long)context_ptr+0x000065f4+4*9))=0x0518ef4e;
*((unsigned int *)((unsigned long)context_ptr+0x000065f4+4*10))=0xe342d6cb;
*((unsigned int *)((unsigned long)context_ptr+0x000065f4+4*11))=0x1240ab85;
*((unsigned int *)((unsigned long)context_ptr+0x000065f4+4*12))=0xfda54339;
*((unsigned int *)((unsigned long)context_ptr+0x000065f4+4*13))=0x1a866486;
*((unsigned int *)((unsigned long)context_ptr+0x000065f4+4*14))=0xa4a4a8b6;
*((unsigned int *)((unsigned long)context_ptr+0x000065f4+4*15))=0x5671ea22;
*((unsigned int *)((unsigned long)context_ptr+0x000065f4+4*16))=0x13e45159;
*((unsigned int *)((unsigned long)context_ptr+0x000065f4+4*17))=0x8719428f;
*((unsigned int *)((unsigned long)context_ptr+0x000065f4+4*18))=0xeb5c598e;
*((unsigned int *)((unsigned long)context_ptr+0x000065f4+4*19))=0xaab1cd8c;
*((unsigned int *)((unsigned long)context_ptr+0x000065f4+4*20))=0x7774beef;
*((unsigned int *)((unsigned long)context_ptr+0x000065f4+4*21))=0xc3cbd8ca;
*((unsigned int *)((unsigned long)context_ptr+0x000065f4+4*22))=0x2f0f9b55;
*((unsigned int *)((unsigned long)context_ptr+0x000065f4+4*23))=0xb00ff824;
*((unsigned int *)((unsigned long)context_ptr+0x000065f4+4*24))=0x000000d4;
*((unsigned int *)((unsigned long)context_ptr+0x00003900))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003900+4*1))=0x000063d8;
*((unsigned int *)((unsigned long)context_ptr+0x00003900+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003900+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003900+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003900+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000900))=0x04c00061;
*((unsigned int *)((unsigned long)context_ptr+0x00000900+4*1))=0x000065f4;
*((unsigned int *)((unsigned long)context_ptr+0x00000900+4*2))=0x00006320;
*((unsigned int *)((unsigned long)context_ptr+0x00000900+4*3))=0x02220061;
*((unsigned int *)((unsigned long)context_ptr+0x00000900+4*4))=0x0a660f45;
*((unsigned int *)((unsigned long)context_ptr+0x00000900+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000001f2&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x0000633c,"\x51\x30\x6f\xad\x06\x44\x9e\xea\xec\xbd\x0a\x21\x8a\x98\x8b\x0d\x39\x4f\x5a\xdf",20))
printf("strip: 51306fad06449eea, Pass\n");
else
printf("strip: 51306fad06449eea, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006658))=0x016a0a02;
*((unsigned int *)((unsigned long)context_ptr+0x00006658+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006658+4*2))=0x02020062;
*((unsigned int *)((unsigned long)context_ptr+0x00006658+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x0000680c))=0x8db831a7;
*((unsigned int *)((unsigned long)context_ptr+0x0000680c+4*1))=0x60749d35;
*((unsigned int *)((unsigned long)context_ptr+0x0000680c+4*2))=0x62c5a95a;
*((unsigned int *)((unsigned long)context_ptr+0x0000680c+4*3))=0x50dffc30;
*((unsigned int *)((unsigned long)context_ptr+0x0000680c+4*4))=0x2cd6a219;
*((unsigned int *)((unsigned long)context_ptr+0x0000680c+4*5))=0xac095dad;
*((unsigned int *)((unsigned long)context_ptr+0x0000680c+4*6))=0x2d3ccb6d;
*((unsigned int *)((unsigned long)context_ptr+0x0000680c+4*7))=0x92e1c258;
*((unsigned int *)((unsigned long)context_ptr+0x0000680c+4*8))=0x06292d9c;
*((unsigned int *)((unsigned long)context_ptr+0x0000680c+4*9))=0x32ddc73a;
*((unsigned int *)((unsigned long)context_ptr+0x0000680c+4*10))=0x94cf6522;
*((unsigned int *)((unsigned long)context_ptr+0x0000680c+4*11))=0x064112c8;
*((unsigned int *)((unsigned long)context_ptr+0x0000680c+4*12))=0x1872fa77;
*((unsigned int *)((unsigned long)context_ptr+0x0000680c+4*13))=0xfe14dc11;
*((unsigned int *)((unsigned long)context_ptr+0x0000680c+4*14))=0x12743a1b;
*((unsigned int *)((unsigned long)context_ptr+0x0000680c+4*15))=0x2847bfc2;
*((unsigned int *)((unsigned long)context_ptr+0x0000680c+4*16))=0x0163b0f1;
*((unsigned int *)((unsigned long)context_ptr+0x0000680c+4*17))=0x47867c36;
*((unsigned int *)((unsigned long)context_ptr+0x0000680c+4*18))=0xa12632ef;
*((unsigned int *)((unsigned long)context_ptr+0x0000680c+4*19))=0x77d9e94f;
*((unsigned int *)((unsigned long)context_ptr+0x0000680c+4*20))=0x5c864c7d;
*((unsigned int *)((unsigned long)context_ptr+0x0000680c+4*21))=0x751e88fb;
*((unsigned int *)((unsigned long)context_ptr+0x0000680c+4*22))=0x854a816a;
*((unsigned int *)((unsigned long)context_ptr+0x0000680c+4*23))=0xb34ed2a6;
*((unsigned int *)((unsigned long)context_ptr+0x0000680c+4*24))=0x0000cb56;
*((unsigned int *)((unsigned long)context_ptr+0x00003918))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003918+4*1))=0x00006330;
*((unsigned int *)((unsigned long)context_ptr+0x00003918+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003918+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003918+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003918+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000918))=0x04c00062;
*((unsigned int *)((unsigned long)context_ptr+0x00000918+4*1))=0x0000680c;
*((unsigned int *)((unsigned long)context_ptr+0x00000918+4*2))=0x00006658;
*((unsigned int *)((unsigned long)context_ptr+0x00000918+4*3))=0x02220062;
*((unsigned int *)((unsigned long)context_ptr+0x00000918+4*4))=0x0397c11f;
*((unsigned int *)((unsigned long)context_ptr+0x00000918+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000001f8&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006430,"\xe5\x0b\xc6\xaf\x80\xa2\x55\x13\x12\xaa\x02\xe2\x34\x57\x73\x63\x0c\xcb\x69\x8c",20))
printf("strip: e50bc6af80a25513, Pass\n");
else
printf("strip: e50bc6af80a25513, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006344))=0x016a0a02;
*((unsigned int *)((unsigned long)context_ptr+0x00006344+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006344+4*2))=0x02020063;
*((unsigned int *)((unsigned long)context_ptr+0x00006344+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x00006870))=0x8e58d3dc;
*((unsigned int *)((unsigned long)context_ptr+0x00006870+4*1))=0xc5669e6a;
*((unsigned int *)((unsigned long)context_ptr+0x00006870+4*2))=0xbaedb5b4;
*((unsigned int *)((unsigned long)context_ptr+0x00006870+4*3))=0x7e104f86;
*((unsigned int *)((unsigned long)context_ptr+0x00006870+4*4))=0x8804feb8;
*((unsigned int *)((unsigned long)context_ptr+0x00006870+4*5))=0x9a661bf0;
*((unsigned int *)((unsigned long)context_ptr+0x00006870+4*6))=0x82665eb3;
*((unsigned int *)((unsigned long)context_ptr+0x00006870+4*7))=0xab2f5c0a;
*((unsigned int *)((unsigned long)context_ptr+0x00006870+4*8))=0xcc0145a9;
*((unsigned int *)((unsigned long)context_ptr+0x00006870+4*9))=0xdf00f908;
*((unsigned int *)((unsigned long)context_ptr+0x00006870+4*10))=0xf23e3287;
*((unsigned int *)((unsigned long)context_ptr+0x00006870+4*11))=0x58875e1c;
*((unsigned int *)((unsigned long)context_ptr+0x00006870+4*12))=0x51766149;
*((unsigned int *)((unsigned long)context_ptr+0x00006870+4*13))=0xeae0b620;
*((unsigned int *)((unsigned long)context_ptr+0x00006870+4*14))=0x00b7a0a9;
*((unsigned int *)((unsigned long)context_ptr+0x00006870+4*15))=0x2fc9a24d;
*((unsigned int *)((unsigned long)context_ptr+0x00006870+4*16))=0x89869a1f;
*((unsigned int *)((unsigned long)context_ptr+0x00006870+4*17))=0x3c1cd57b;
*((unsigned int *)((unsigned long)context_ptr+0x00006870+4*18))=0x6292d397;
*((unsigned int *)((unsigned long)context_ptr+0x00006870+4*19))=0xef365a59;
*((unsigned int *)((unsigned long)context_ptr+0x00006870+4*20))=0x675ae2c6;
*((unsigned int *)((unsigned long)context_ptr+0x00006870+4*21))=0xa2770536;
*((unsigned int *)((unsigned long)context_ptr+0x00006870+4*22))=0xc53ef9f3;
*((unsigned int *)((unsigned long)context_ptr+0x00006870+4*23))=0xe091282c;
*((unsigned int *)((unsigned long)context_ptr+0x00006870+4*24))=0x00b19856;
*((unsigned int *)((unsigned long)context_ptr+0x00003930))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003930+4*1))=0x000060a8;
*((unsigned int *)((unsigned long)context_ptr+0x00003930+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003930+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003930+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003930+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000930))=0x04c00063;
*((unsigned int *)((unsigned long)context_ptr+0x00000930+4*1))=0x00006870;
*((unsigned int *)((unsigned long)context_ptr+0x00000930+4*2))=0x00006344;
*((unsigned int *)((unsigned long)context_ptr+0x00000930+4*3))=0x02220063;
*((unsigned int *)((unsigned long)context_ptr+0x00000930+4*4))=0x0945f8d1;
*((unsigned int *)((unsigned long)context_ptr+0x00000930+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000001fe&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006444,"\x65\x9c\x71\x39\x3b\xa5\x3a\x53\x25\x46\x41\xbf\x9b\xf7\xe6\xbb\xc5\xe3\x6b\xb6",20))
printf("strip: 659c71393ba53a53, Pass\n");
else
printf("strip: 659c71393ba53a53, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006354))=0x016a0a02;
*((unsigned int *)((unsigned long)context_ptr+0x00006354+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006354+4*2))=0x02020064;
*((unsigned int *)((unsigned long)context_ptr+0x00006354+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x000063ec))=0xa0a0e6ae;
*((unsigned int *)((unsigned long)context_ptr+0x000063ec+4*1))=0x04de4d52;
*((unsigned int *)((unsigned long)context_ptr+0x000063ec+4*2))=0x0ffc833a;
*((unsigned int *)((unsigned long)context_ptr+0x000063ec+4*3))=0x0577471b;
*((unsigned int *)((unsigned long)context_ptr+0x000063ec+4*4))=0x57809741;
*((unsigned int *)((unsigned long)context_ptr+0x000063ec+4*5))=0x4726219e;
*((unsigned int *)((unsigned long)context_ptr+0x000063ec+4*6))=0xbe506bf3;
*((unsigned int *)((unsigned long)context_ptr+0x000063ec+4*7))=0xd0e827d7;
*((unsigned int *)((unsigned long)context_ptr+0x000063ec+4*8))=0xd67e325e;
*((unsigned int *)((unsigned long)context_ptr+0x000063ec+4*9))=0x9acb2b35;
*((unsigned int *)((unsigned long)context_ptr+0x000063ec+4*10))=0xf64f7eba;
*((unsigned int *)((unsigned long)context_ptr+0x000063ec+4*11))=0x0351aa3d;
*((unsigned int *)((unsigned long)context_ptr+0x000063ec+4*12))=0x83d2b685;
*((unsigned int *)((unsigned long)context_ptr+0x000063ec+4*13))=0x96945302;
*((unsigned int *)((unsigned long)context_ptr+0x000063ec+4*14))=0x2ab6f5ec;
*((unsigned int *)((unsigned long)context_ptr+0x000063ec+4*15))=0x12551fbd;
*((unsigned int *)((unsigned long)context_ptr+0x000063ec+4*16))=0x09b783cf;
*((unsigned int *)((unsigned long)context_ptr+0x000063ec+4*17))=0x287d342d;
*((unsigned int *)((unsigned long)context_ptr+0x000063ec+4*18))=0xf51b8f19;
*((unsigned int *)((unsigned long)context_ptr+0x000063ec+4*19))=0x4cc4fec6;
*((unsigned int *)((unsigned long)context_ptr+0x000063ec+4*20))=0x511f33cf;
*((unsigned int *)((unsigned long)context_ptr+0x000063ec+4*21))=0x11e31eb3;
*((unsigned int *)((unsigned long)context_ptr+0x000063ec+4*22))=0xc383b0c6;
*((unsigned int *)((unsigned long)context_ptr+0x000063ec+4*23))=0x4b26b18c;
*((unsigned int *)((unsigned long)context_ptr+0x000063ec+4*24))=0xbb96a18a;
*((unsigned int *)((unsigned long)context_ptr+0x00003948))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003948+4*1))=0x000064a4;
*((unsigned int *)((unsigned long)context_ptr+0x00003948+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003948+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003948+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003948+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000948))=0x04c00064;
*((unsigned int *)((unsigned long)context_ptr+0x00000948+4*1))=0x000063ec;
*((unsigned int *)((unsigned long)context_ptr+0x00000948+4*2))=0x00006354;
*((unsigned int *)((unsigned long)context_ptr+0x00000948+4*3))=0x02220064;
*((unsigned int *)((unsigned long)context_ptr+0x00000948+4*4))=0x0f1b8bfd;
*((unsigned int *)((unsigned long)context_ptr+0x00000948+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000204&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006458,"\x9c\x9e\xba\xb4\x3d\xcb\xa1\x56\x32\xd4\x73\xc5\x41\x90\x25\xc7\x1c\x50\x9a\x48",20))
printf("strip: 9c9ebab43dcba156, Pass\n");
else
printf("strip: 9c9ebab43dcba156, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006364))=0x016a0a02;
*((unsigned int *)((unsigned long)context_ptr+0x00006364+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006364+4*2))=0x02020065;
*((unsigned int *)((unsigned long)context_ptr+0x00006364+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x000060bc))=0x9737828d;
*((unsigned int *)((unsigned long)context_ptr+0x000060bc+4*1))=0x8e007a06;
*((unsigned int *)((unsigned long)context_ptr+0x000060bc+4*2))=0x09e6d13c;
*((unsigned int *)((unsigned long)context_ptr+0x000060bc+4*3))=0x10aeeaa8;
*((unsigned int *)((unsigned long)context_ptr+0x000060bc+4*4))=0xa62710a4;
*((unsigned int *)((unsigned long)context_ptr+0x000060bc+4*5))=0xe09408ae;
*((unsigned int *)((unsigned long)context_ptr+0x000060bc+4*6))=0xa437a4a1;
*((unsigned int *)((unsigned long)context_ptr+0x000060bc+4*7))=0xd13dd526;
*((unsigned int *)((unsigned long)context_ptr+0x000060bc+4*8))=0x4d559806;
*((unsigned int *)((unsigned long)context_ptr+0x000060bc+4*9))=0x2dfa3e9c;
*((unsigned int *)((unsigned long)context_ptr+0x000060bc+4*10))=0xeb4fad8b;
*((unsigned int *)((unsigned long)context_ptr+0x000060bc+4*11))=0x8f7037c7;
*((unsigned int *)((unsigned long)context_ptr+0x000060bc+4*12))=0x4ebdc506;
*((unsigned int *)((unsigned long)context_ptr+0x000060bc+4*13))=0xdd6f6aca;
*((unsigned int *)((unsigned long)context_ptr+0x000060bc+4*14))=0x33bac74e;
*((unsigned int *)((unsigned long)context_ptr+0x000060bc+4*15))=0x409c284b;
*((unsigned int *)((unsigned long)context_ptr+0x000060bc+4*16))=0xc13e33ec;
*((unsigned int *)((unsigned long)context_ptr+0x000060bc+4*17))=0xcb006e9b;
*((unsigned int *)((unsigned long)context_ptr+0x000060bc+4*18))=0x30518855;
*((unsigned int *)((unsigned long)context_ptr+0x000060bc+4*19))=0xd3b77fe4;
*((unsigned int *)((unsigned long)context_ptr+0x000060bc+4*20))=0x0c17a467;
*((unsigned int *)((unsigned long)context_ptr+0x000060bc+4*21))=0xf6f1fb9a;
*((unsigned int *)((unsigned long)context_ptr+0x000060bc+4*22))=0x9db77395;
*((unsigned int *)((unsigned long)context_ptr+0x000060bc+4*23))=0x4eabe8dc;
*((unsigned int *)((unsigned long)context_ptr+0x000060bc+4*24))=0x14babd7f;
*((unsigned int *)((unsigned long)context_ptr+0x000060bc+4*25))=0x0000000b;
*((unsigned int *)((unsigned long)context_ptr+0x00003960))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003960+4*1))=0x00006450;
*((unsigned int *)((unsigned long)context_ptr+0x00003960+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003960+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003960+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003960+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000960))=0x04c00065;
*((unsigned int *)((unsigned long)context_ptr+0x00000960+4*1))=0x000060bc;
*((unsigned int *)((unsigned long)context_ptr+0x00000960+4*2))=0x00006364;
*((unsigned int *)((unsigned long)context_ptr+0x00000960+4*3))=0x02220065;
*((unsigned int *)((unsigned long)context_ptr+0x00000960+4*4))=0x06b9e25e;
*((unsigned int *)((unsigned long)context_ptr+0x00000960+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000020a&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000064fc,"\x15\x00\x2a\xe6\xee\x5a\x8e\xd9\x00\xa3\xa9\x0c\x04\x93\x09\x78\x61\xb7\xce\x62",20))
printf("strip: 15002ae6ee5a8ed9, Pass\n");
else
printf("strip: 15002ae6ee5a8ed9, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006464))=0x016a0a02;
*((unsigned int *)((unsigned long)context_ptr+0x00006464+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006464+4*2))=0x02020066;
*((unsigned int *)((unsigned long)context_ptr+0x00006464+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x00006124))=0x783f6161;
*((unsigned int *)((unsigned long)context_ptr+0x00006124+4*1))=0xafbd4998;
*((unsigned int *)((unsigned long)context_ptr+0x00006124+4*2))=0xa21f2b69;
*((unsigned int *)((unsigned long)context_ptr+0x00006124+4*3))=0x9faff70d;
*((unsigned int *)((unsigned long)context_ptr+0x00006124+4*4))=0x953c964d;
*((unsigned int *)((unsigned long)context_ptr+0x00006124+4*5))=0xc4f6e664;
*((unsigned int *)((unsigned long)context_ptr+0x00006124+4*6))=0x1bfac9d1;
*((unsigned int *)((unsigned long)context_ptr+0x00006124+4*7))=0xdf82e8ca;
*((unsigned int *)((unsigned long)context_ptr+0x00006124+4*8))=0x7bcd07cc;
*((unsigned int *)((unsigned long)context_ptr+0x00006124+4*9))=0x9798559b;
*((unsigned int *)((unsigned long)context_ptr+0x00006124+4*10))=0xa92e8025;
*((unsigned int *)((unsigned long)context_ptr+0x00006124+4*11))=0xf5975b0d;
*((unsigned int *)((unsigned long)context_ptr+0x00006124+4*12))=0x50652719;
*((unsigned int *)((unsigned long)context_ptr+0x00006124+4*13))=0xab21d3b5;
*((unsigned int *)((unsigned long)context_ptr+0x00006124+4*14))=0x4457e9cb;
*((unsigned int *)((unsigned long)context_ptr+0x00006124+4*15))=0xb29066bf;
*((unsigned int *)((unsigned long)context_ptr+0x00006124+4*16))=0xbbeebf4d;
*((unsigned int *)((unsigned long)context_ptr+0x00006124+4*17))=0x91ef7953;
*((unsigned int *)((unsigned long)context_ptr+0x00006124+4*18))=0xe85c801c;
*((unsigned int *)((unsigned long)context_ptr+0x00006124+4*19))=0xed092f8d;
*((unsigned int *)((unsigned long)context_ptr+0x00006124+4*20))=0x5d68a727;
*((unsigned int *)((unsigned long)context_ptr+0x00006124+4*21))=0x492f6eb8;
*((unsigned int *)((unsigned long)context_ptr+0x00006124+4*22))=0x73d19563;
*((unsigned int *)((unsigned long)context_ptr+0x00006124+4*23))=0xcc6156f1;
*((unsigned int *)((unsigned long)context_ptr+0x00006124+4*24))=0xa590ff5e;
*((unsigned int *)((unsigned long)context_ptr+0x00006124+4*25))=0x00005688;
*((unsigned int *)((unsigned long)context_ptr+0x00003978))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003978+4*1))=0x000064b8;
*((unsigned int *)((unsigned long)context_ptr+0x00003978+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003978+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003978+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003978+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000978))=0x04c00066;
*((unsigned int *)((unsigned long)context_ptr+0x00000978+4*1))=0x00006124;
*((unsigned int *)((unsigned long)context_ptr+0x00000978+4*2))=0x00006464;
*((unsigned int *)((unsigned long)context_ptr+0x00000978+4*3))=0x02220066;
*((unsigned int *)((unsigned long)context_ptr+0x00000978+4*4))=0x016793fa;
*((unsigned int *)((unsigned long)context_ptr+0x00000978+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000210&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x0000647c,"\xd7\xa4\xe2\xd1\x12\xa1\x99\xb4\xe5\x42\xc7\xee\xf2\x01\xb8\xeb\xdb\x4a\xa9\xf1",20))
printf("strip: d7a4e2d112a199b4, Pass\n");
else
printf("strip: d7a4e2d112a199b4, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006374))=0x016a0a02;
*((unsigned int *)((unsigned long)context_ptr+0x00006374+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006374+4*2))=0x02020067;
*((unsigned int *)((unsigned long)context_ptr+0x00006374+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x0000618c))=0xf8bdc660;
*((unsigned int *)((unsigned long)context_ptr+0x0000618c+4*1))=0x1205b15c;
*((unsigned int *)((unsigned long)context_ptr+0x0000618c+4*2))=0xc6600ec8;
*((unsigned int *)((unsigned long)context_ptr+0x0000618c+4*3))=0xc256d510;
*((unsigned int *)((unsigned long)context_ptr+0x0000618c+4*4))=0xe567adfd;
*((unsigned int *)((unsigned long)context_ptr+0x0000618c+4*5))=0x56783947;
*((unsigned int *)((unsigned long)context_ptr+0x0000618c+4*6))=0x93f05fe7;
*((unsigned int *)((unsigned long)context_ptr+0x0000618c+4*7))=0xa0196a0f;
*((unsigned int *)((unsigned long)context_ptr+0x0000618c+4*8))=0x28999185;
*((unsigned int *)((unsigned long)context_ptr+0x0000618c+4*9))=0xe3138470;
*((unsigned int *)((unsigned long)context_ptr+0x0000618c+4*10))=0x88ffe858;
*((unsigned int *)((unsigned long)context_ptr+0x0000618c+4*11))=0xc47a53ab;
*((unsigned int *)((unsigned long)context_ptr+0x0000618c+4*12))=0xa45ca6ef;
*((unsigned int *)((unsigned long)context_ptr+0x0000618c+4*13))=0xaf887086;
*((unsigned int *)((unsigned long)context_ptr+0x0000618c+4*14))=0x3a816526;
*((unsigned int *)((unsigned long)context_ptr+0x0000618c+4*15))=0x9e918587;
*((unsigned int *)((unsigned long)context_ptr+0x0000618c+4*16))=0x7d36bd50;
*((unsigned int *)((unsigned long)context_ptr+0x0000618c+4*17))=0xf74a42e3;
*((unsigned int *)((unsigned long)context_ptr+0x0000618c+4*18))=0x85550fd9;
*((unsigned int *)((unsigned long)context_ptr+0x0000618c+4*19))=0xa961ae3d;
*((unsigned int *)((unsigned long)context_ptr+0x0000618c+4*20))=0x59e90d91;
*((unsigned int *)((unsigned long)context_ptr+0x0000618c+4*21))=0x08ebea00;
*((unsigned int *)((unsigned long)context_ptr+0x0000618c+4*22))=0x34073ef3;
*((unsigned int *)((unsigned long)context_ptr+0x0000618c+4*23))=0xf097511e;
*((unsigned int *)((unsigned long)context_ptr+0x0000618c+4*24))=0x68b70563;
*((unsigned int *)((unsigned long)context_ptr+0x0000618c+4*25))=0x00def350;
*((unsigned int *)((unsigned long)context_ptr+0x00003990))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003990+4*1))=0x00006474;
*((unsigned int *)((unsigned long)context_ptr+0x00003990+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003990+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003990+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003990+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000990))=0x04c00067;
*((unsigned int *)((unsigned long)context_ptr+0x00000990+4*1))=0x0000618c;
*((unsigned int *)((unsigned long)context_ptr+0x00000990+4*2))=0x00006374;
*((unsigned int *)((unsigned long)context_ptr+0x00000990+4*3))=0x02220067;
*((unsigned int *)((unsigned long)context_ptr+0x00000990+4*4))=0x01f82933;
*((unsigned int *)((unsigned long)context_ptr+0x00000990+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000216&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000063a0,"\xd4\x95\xce\x41\x78\x3d\x34\x46\xa9\x3e\x77\xa7\x7b\x89\x83\xfe\x29\xd7\x44\x92",20))
printf("strip: d495ce41783d3446, Pass\n");
else
printf("strip: d495ce41783d3446, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000061f4))=0x016a0a02;
*((unsigned int *)((unsigned long)context_ptr+0x000061f4+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000061f4+4*2))=0x02020068;
*((unsigned int *)((unsigned long)context_ptr+0x000061f4+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x000064cc))=0x8bd035fc;
*((unsigned int *)((unsigned long)context_ptr+0x000064cc+4*1))=0x08462d0c;
*((unsigned int *)((unsigned long)context_ptr+0x000064cc+4*2))=0xf1dac404;
*((unsigned int *)((unsigned long)context_ptr+0x000064cc+4*3))=0x4a857fcc;
*((unsigned int *)((unsigned long)context_ptr+0x000064cc+4*4))=0xc2ebff0c;
*((unsigned int *)((unsigned long)context_ptr+0x000064cc+4*5))=0xf3bb5c45;
*((unsigned int *)((unsigned long)context_ptr+0x000064cc+4*6))=0xb17dd974;
*((unsigned int *)((unsigned long)context_ptr+0x000064cc+4*7))=0xc4afbde7;
*((unsigned int *)((unsigned long)context_ptr+0x000064cc+4*8))=0x809414d9;
*((unsigned int *)((unsigned long)context_ptr+0x000064cc+4*9))=0x98522da7;
*((unsigned int *)((unsigned long)context_ptr+0x000064cc+4*10))=0x66153cc5;
*((unsigned int *)((unsigned long)context_ptr+0x000064cc+4*11))=0x03486f86;
*((unsigned int *)((unsigned long)context_ptr+0x000064cc+4*12))=0xb00bb6b0;
*((unsigned int *)((unsigned long)context_ptr+0x000064cc+4*13))=0xbfcc1a3d;
*((unsigned int *)((unsigned long)context_ptr+0x000064cc+4*14))=0x2563798b;
*((unsigned int *)((unsigned long)context_ptr+0x000064cc+4*15))=0x1f15154c;
*((unsigned int *)((unsigned long)context_ptr+0x000064cc+4*16))=0x8fec192e;
*((unsigned int *)((unsigned long)context_ptr+0x000064cc+4*17))=0x3b82fe58;
*((unsigned int *)((unsigned long)context_ptr+0x000064cc+4*18))=0xd1e0cc87;
*((unsigned int *)((unsigned long)context_ptr+0x000064cc+4*19))=0xbcb72757;
*((unsigned int *)((unsigned long)context_ptr+0x000064cc+4*20))=0x7fa0aa98;
*((unsigned int *)((unsigned long)context_ptr+0x000064cc+4*21))=0x3452fa28;
*((unsigned int *)((unsigned long)context_ptr+0x000064cc+4*22))=0x551512ac;
*((unsigned int *)((unsigned long)context_ptr+0x000064cc+4*23))=0x3f3d63f4;
*((unsigned int *)((unsigned long)context_ptr+0x000064cc+4*24))=0x019d0e6f;
*((unsigned int *)((unsigned long)context_ptr+0x000064cc+4*25))=0x6cff9417;
*((unsigned int *)((unsigned long)context_ptr+0x000039a8))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x000039a8+4*1))=0x00006384;
*((unsigned int *)((unsigned long)context_ptr+0x000039a8+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000039a8+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000039a8+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000039a8+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x000009a8))=0x04c00068;
*((unsigned int *)((unsigned long)context_ptr+0x000009a8+4*1))=0x000064cc;
*((unsigned int *)((unsigned long)context_ptr+0x000009a8+4*2))=0x000061f4;
*((unsigned int *)((unsigned long)context_ptr+0x000009a8+4*3))=0x02220068;
*((unsigned int *)((unsigned long)context_ptr+0x000009a8+4*4))=0x0ac8822e;
*((unsigned int *)((unsigned long)context_ptr+0x000009a8+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000021c&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x0000656c,"\x8c\xf7\x6e\x4e\x50\x2b\xb8\x88\x0e\x6d\x01\x3c\xfa\x7c\xb0\x39\x12\xb9\x00\x83",20))
printf("strip: 8cf76e4e502bb888, Pass\n");
else
printf("strip: 8cf76e4e502bb888, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006398))=0x016a0a02;
*((unsigned int *)((unsigned long)context_ptr+0x00006398+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006398+4*2))=0x02020069;
*((unsigned int *)((unsigned long)context_ptr+0x00006398+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x000068d4))=0xfd63e359;
*((unsigned int *)((unsigned long)context_ptr+0x000068d4+4*1))=0x9906d8ff;
*((unsigned int *)((unsigned long)context_ptr+0x000068d4+4*2))=0x118028b6;
*((unsigned int *)((unsigned long)context_ptr+0x000068d4+4*3))=0x15d91689;
*((unsigned int *)((unsigned long)context_ptr+0x000068d4+4*4))=0x0f8821f7;
*((unsigned int *)((unsigned long)context_ptr+0x000068d4+4*5))=0x3c28d744;
*((unsigned int *)((unsigned long)context_ptr+0x000068d4+4*6))=0x223fd1ec;
*((unsigned int *)((unsigned long)context_ptr+0x000068d4+4*7))=0xbc5458ea;
*((unsigned int *)((unsigned long)context_ptr+0x000068d4+4*8))=0xe63cc87c;
*((unsigned int *)((unsigned long)context_ptr+0x000068d4+4*9))=0x03352b82;
*((unsigned int *)((unsigned long)context_ptr+0x000068d4+4*10))=0xe20fd5aa;
*((unsigned int *)((unsigned long)context_ptr+0x000068d4+4*11))=0xbb30bec6;
*((unsigned int *)((unsigned long)context_ptr+0x000068d4+4*12))=0xd5e44f5e;
*((unsigned int *)((unsigned long)context_ptr+0x000068d4+4*13))=0x3b83e703;
*((unsigned int *)((unsigned long)context_ptr+0x000068d4+4*14))=0x00e3c966;
*((unsigned int *)((unsigned long)context_ptr+0x000068d4+4*15))=0x8a2be094;
*((unsigned int *)((unsigned long)context_ptr+0x000068d4+4*16))=0x13bbdc2a;
*((unsigned int *)((unsigned long)context_ptr+0x000068d4+4*17))=0xd3cea7f4;
*((unsigned int *)((unsigned long)context_ptr+0x000068d4+4*18))=0x39e12861;
*((unsigned int *)((unsigned long)context_ptr+0x000068d4+4*19))=0x5feb27e5;
*((unsigned int *)((unsigned long)context_ptr+0x000068d4+4*20))=0x0a0dbe79;
*((unsigned int *)((unsigned long)context_ptr+0x000068d4+4*21))=0x05aa128f;
*((unsigned int *)((unsigned long)context_ptr+0x000068d4+4*22))=0x98b86e1c;
*((unsigned int *)((unsigned long)context_ptr+0x000068d4+4*23))=0x2ab5d46b;
*((unsigned int *)((unsigned long)context_ptr+0x000068d4+4*24))=0xe6751116;
*((unsigned int *)((unsigned long)context_ptr+0x000068d4+4*25))=0x0c5f65d9;
*((unsigned int *)((unsigned long)context_ptr+0x000068d4+4*26))=0x00000040;
*((unsigned int *)((unsigned long)context_ptr+0x000039c0))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x000039c0+4*1))=0x000063a8;
*((unsigned int *)((unsigned long)context_ptr+0x000039c0+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000039c0+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000039c0+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000039c0+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x000009c0))=0x04c00069;
*((unsigned int *)((unsigned long)context_ptr+0x000009c0+4*1))=0x000068d4;
*((unsigned int *)((unsigned long)context_ptr+0x000009c0+4*2))=0x00006398;
*((unsigned int *)((unsigned long)context_ptr+0x000009c0+4*3))=0x02220069;
*((unsigned int *)((unsigned long)context_ptr+0x000009c0+4*4))=0x0cbe13ef;
*((unsigned int *)((unsigned long)context_ptr+0x000009c0+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000222&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000063c4,"\xb0\x89\xbd\x60\x00\x10\x13\x9e\xb1\xc5\xa9\x9d\xcf\x86\x77\xaa\xe4\x38\x79\xa8",20))
printf("strip: b089bd600010139e, Pass\n");
else
printf("strip: b089bd600010139e, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006040))=0x016a0a02;
*((unsigned int *)((unsigned long)context_ptr+0x00006040+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006040+4*2))=0x0202006a;
*((unsigned int *)((unsigned long)context_ptr+0x00006040+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x0000674c))=0x9219b648;
*((unsigned int *)((unsigned long)context_ptr+0x0000674c+4*1))=0xe6784636;
*((unsigned int *)((unsigned long)context_ptr+0x0000674c+4*2))=0x1b400a84;
*((unsigned int *)((unsigned long)context_ptr+0x0000674c+4*3))=0xa5d958f6;
*((unsigned int *)((unsigned long)context_ptr+0x0000674c+4*4))=0x39df63e7;
*((unsigned int *)((unsigned long)context_ptr+0x0000674c+4*5))=0x1806fb9f;
*((unsigned int *)((unsigned long)context_ptr+0x0000674c+4*6))=0x8fec395e;
*((unsigned int *)((unsigned long)context_ptr+0x0000674c+4*7))=0xa6132433;
*((unsigned int *)((unsigned long)context_ptr+0x0000674c+4*8))=0x6ac70adc;
*((unsigned int *)((unsigned long)context_ptr+0x0000674c+4*9))=0xbacb2f08;
*((unsigned int *)((unsigned long)context_ptr+0x0000674c+4*10))=0x52bfb066;
*((unsigned int *)((unsigned long)context_ptr+0x0000674c+4*11))=0xb9d9f37f;
*((unsigned int *)((unsigned long)context_ptr+0x0000674c+4*12))=0x31c47899;
*((unsigned int *)((unsigned long)context_ptr+0x0000674c+4*13))=0x0f06b14a;
*((unsigned int *)((unsigned long)context_ptr+0x0000674c+4*14))=0xabb63cc9;
*((unsigned int *)((unsigned long)context_ptr+0x0000674c+4*15))=0x01c3dc01;
*((unsigned int *)((unsigned long)context_ptr+0x0000674c+4*16))=0x73e5dc05;
*((unsigned int *)((unsigned long)context_ptr+0x0000674c+4*17))=0xb06f2c27;
*((unsigned int *)((unsigned long)context_ptr+0x0000674c+4*18))=0xc310c08e;
*((unsigned int *)((unsigned long)context_ptr+0x0000674c+4*19))=0x47d2ce45;
*((unsigned int *)((unsigned long)context_ptr+0x0000674c+4*20))=0xc9f501d3;
*((unsigned int *)((unsigned long)context_ptr+0x0000674c+4*21))=0x65c6d483;
*((unsigned int *)((unsigned long)context_ptr+0x0000674c+4*22))=0xd922a088;
*((unsigned int *)((unsigned long)context_ptr+0x0000674c+4*23))=0xfced0d0e;
*((unsigned int *)((unsigned long)context_ptr+0x0000674c+4*24))=0xff01479f;
*((unsigned int *)((unsigned long)context_ptr+0x0000674c+4*25))=0x2284a32e;
*((unsigned int *)((unsigned long)context_ptr+0x0000674c+4*26))=0x00004af4;
*((unsigned int *)((unsigned long)context_ptr+0x000039d8))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x000039d8+4*1))=0x000063bc;
*((unsigned int *)((unsigned long)context_ptr+0x000039d8+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000039d8+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000039d8+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000039d8+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x000009d8))=0x04c0006a;
*((unsigned int *)((unsigned long)context_ptr+0x000009d8+4*1))=0x0000674c;
*((unsigned int *)((unsigned long)context_ptr+0x000009d8+4*2))=0x00006040;
*((unsigned int *)((unsigned long)context_ptr+0x000009d8+4*3))=0x0222006a;
*((unsigned int *)((unsigned long)context_ptr+0x000009d8+4*4))=0x0f0358a2;
*((unsigned int *)((unsigned long)context_ptr+0x000009d8+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000228&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006060,"\x48\x7b\x82\xf3\x97\xd1\x19\x50\x90\x61\x0a\x73\xde\x74\x83\x5a\x9b\x08\x3e\x42",20))
printf("strip: 487b82f397d11950, Pass\n");
else
printf("strip: 487b82f397d11950, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006030))=0x016a0a02;
*((unsigned int *)((unsigned long)context_ptr+0x00006030+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006030+4*2))=0x0202006b;
*((unsigned int *)((unsigned long)context_ptr+0x00006030+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x00006940))=0x96f3c2a7;
*((unsigned int *)((unsigned long)context_ptr+0x00006940+4*1))=0x055a56af;
*((unsigned int *)((unsigned long)context_ptr+0x00006940+4*2))=0x1b1882f9;
*((unsigned int *)((unsigned long)context_ptr+0x00006940+4*3))=0x25b89624;
*((unsigned int *)((unsigned long)context_ptr+0x00006940+4*4))=0x993ca260;
*((unsigned int *)((unsigned long)context_ptr+0x00006940+4*5))=0x8c94a455;
*((unsigned int *)((unsigned long)context_ptr+0x00006940+4*6))=0x2859dc1e;
*((unsigned int *)((unsigned long)context_ptr+0x00006940+4*7))=0x7337d8c2;
*((unsigned int *)((unsigned long)context_ptr+0x00006940+4*8))=0xa7655795;
*((unsigned int *)((unsigned long)context_ptr+0x00006940+4*9))=0x05e0a0ef;
*((unsigned int *)((unsigned long)context_ptr+0x00006940+4*10))=0x72de848a;
*((unsigned int *)((unsigned long)context_ptr+0x00006940+4*11))=0x5e7abdc0;
*((unsigned int *)((unsigned long)context_ptr+0x00006940+4*12))=0xe0816722;
*((unsigned int *)((unsigned long)context_ptr+0x00006940+4*13))=0x2f1049bd;
*((unsigned int *)((unsigned long)context_ptr+0x00006940+4*14))=0xc7d129c1;
*((unsigned int *)((unsigned long)context_ptr+0x00006940+4*15))=0x8274542d;
*((unsigned int *)((unsigned long)context_ptr+0x00006940+4*16))=0x1b1e16c4;
*((unsigned int *)((unsigned long)context_ptr+0x00006940+4*17))=0xcf1b67b4;
*((unsigned int *)((unsigned long)context_ptr+0x00006940+4*18))=0x35d1d21f;
*((unsigned int *)((unsigned long)context_ptr+0x00006940+4*19))=0xca525d9b;
*((unsigned int *)((unsigned long)context_ptr+0x00006940+4*20))=0x5e91474c;
*((unsigned int *)((unsigned long)context_ptr+0x00006940+4*21))=0xedaebd92;
*((unsigned int *)((unsigned long)context_ptr+0x00006940+4*22))=0xe8f3810c;
*((unsigned int *)((unsigned long)context_ptr+0x00006940+4*23))=0x8c542f83;
*((unsigned int *)((unsigned long)context_ptr+0x00006940+4*24))=0xd4d251bc;
*((unsigned int *)((unsigned long)context_ptr+0x00006940+4*25))=0xf58aa1f8;
*((unsigned int *)((unsigned long)context_ptr+0x00006940+4*26))=0x006528e3;
*((unsigned int *)((unsigned long)context_ptr+0x000039f0))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x000039f0+4*1))=0x00006060;
*((unsigned int *)((unsigned long)context_ptr+0x000039f0+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000039f0+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000039f0+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000039f0+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x000009f0))=0x04c0006b;
*((unsigned int *)((unsigned long)context_ptr+0x000009f0+4*1))=0x00006940;
*((unsigned int *)((unsigned long)context_ptr+0x000009f0+4*2))=0x00006030;
*((unsigned int *)((unsigned long)context_ptr+0x000009f0+4*3))=0x0222006b;
*((unsigned int *)((unsigned long)context_ptr+0x000009f0+4*4))=0x041a8dbe;
*((unsigned int *)((unsigned long)context_ptr+0x000009f0+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000022e&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006084,"\xa1\x28\xc4\x8b\xc1\xee\x31\xf8\x14\x75\xb2\x86\xe7\x3f\xf8\x37\xfa\x94\x0c\xbf",20))
printf("strip: a128c48bc1ee31f8, Pass\n");
else
printf("strip: a128c48bc1ee31f8, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006050))=0x016a0a02;
*((unsigned int *)((unsigned long)context_ptr+0x00006050+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006050+4*2))=0x0202006c;
*((unsigned int *)((unsigned long)context_ptr+0x00006050+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x00006668))=0xba3937ab;
*((unsigned int *)((unsigned long)context_ptr+0x00006668+4*1))=0x099afd4f;
*((unsigned int *)((unsigned long)context_ptr+0x00006668+4*2))=0x176b9f0c;
*((unsigned int *)((unsigned long)context_ptr+0x00006668+4*3))=0xcaecf7e6;
*((unsigned int *)((unsigned long)context_ptr+0x00006668+4*4))=0x0e6d0441;
*((unsigned int *)((unsigned long)context_ptr+0x00006668+4*5))=0xfbe2799a;
*((unsigned int *)((unsigned long)context_ptr+0x00006668+4*6))=0xac176e20;
*((unsigned int *)((unsigned long)context_ptr+0x00006668+4*7))=0xdc26f88c;
*((unsigned int *)((unsigned long)context_ptr+0x00006668+4*8))=0x71c65d7b;
*((unsigned int *)((unsigned long)context_ptr+0x00006668+4*9))=0x76f7f69b;
*((unsigned int *)((unsigned long)context_ptr+0x00006668+4*10))=0x3b946332;
*((unsigned int *)((unsigned long)context_ptr+0x00006668+4*11))=0xee461c0a;
*((unsigned int *)((unsigned long)context_ptr+0x00006668+4*12))=0x7ba1fbfe;
*((unsigned int *)((unsigned long)context_ptr+0x00006668+4*13))=0x4c8f9bce;
*((unsigned int *)((unsigned long)context_ptr+0x00006668+4*14))=0xc8fefcf4;
*((unsigned int *)((unsigned long)context_ptr+0x00006668+4*15))=0xbe668afd;
*((unsigned int *)((unsigned long)context_ptr+0x00006668+4*16))=0x86bb680a;
*((unsigned int *)((unsigned long)context_ptr+0x00006668+4*17))=0x1fdf8107;
*((unsigned int *)((unsigned long)context_ptr+0x00006668+4*18))=0xc5995c3a;
*((unsigned int *)((unsigned long)context_ptr+0x00006668+4*19))=0xb5011898;
*((unsigned int *)((unsigned long)context_ptr+0x00006668+4*20))=0x2b846429;
*((unsigned int *)((unsigned long)context_ptr+0x00006668+4*21))=0x14778fb3;
*((unsigned int *)((unsigned long)context_ptr+0x00006668+4*22))=0x00e07d7a;
*((unsigned int *)((unsigned long)context_ptr+0x00006668+4*23))=0x232040bc;
*((unsigned int *)((unsigned long)context_ptr+0x00006668+4*24))=0x4977132c;
*((unsigned int *)((unsigned long)context_ptr+0x00006668+4*25))=0x91baa04f;
*((unsigned int *)((unsigned long)context_ptr+0x00006668+4*26))=0xfed21933;
*((unsigned int *)((unsigned long)context_ptr+0x00003a08))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003a08+4*1))=0x00006084;
*((unsigned int *)((unsigned long)context_ptr+0x00003a08+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003a08+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003a08+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003a08+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000a08))=0x04c0006c;
*((unsigned int *)((unsigned long)context_ptr+0x00000a08+4*1))=0x00006668;
*((unsigned int *)((unsigned long)context_ptr+0x00000a08+4*2))=0x00006050;
*((unsigned int *)((unsigned long)context_ptr+0x00000a08+4*3))=0x0222006c;
*((unsigned int *)((unsigned long)context_ptr+0x00000a08+4*4))=0x010d8121;
*((unsigned int *)((unsigned long)context_ptr+0x00000a08+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000234&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006490,"\x64\x2c\xac\xe6\xfd\x3a\xbc\x62\x47\x65\x37\xf3\x34\x7c\x89\xbb\xe0\xfb\x3c\xb9",20))
printf("strip: 642cace6fd3abc62, Pass\n");
else
printf("strip: 642cace6fd3abc62, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006074))=0x016a0a02;
*((unsigned int *)((unsigned long)context_ptr+0x00006074+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006074+4*2))=0x0202006d;
*((unsigned int *)((unsigned long)context_ptr+0x00006074+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x00006204))=0x14d1e4e4;
*((unsigned int *)((unsigned long)context_ptr+0x00006204+4*1))=0x7a458ff3;
*((unsigned int *)((unsigned long)context_ptr+0x00006204+4*2))=0xc890bfde;
*((unsigned int *)((unsigned long)context_ptr+0x00006204+4*3))=0xcb0f6dec;
*((unsigned int *)((unsigned long)context_ptr+0x00006204+4*4))=0xe6dcad3a;
*((unsigned int *)((unsigned long)context_ptr+0x00006204+4*5))=0x5db2be0c;
*((unsigned int *)((unsigned long)context_ptr+0x00006204+4*6))=0xe1332b9a;
*((unsigned int *)((unsigned long)context_ptr+0x00006204+4*7))=0xb9afbc42;
*((unsigned int *)((unsigned long)context_ptr+0x00006204+4*8))=0x980e8a47;
*((unsigned int *)((unsigned long)context_ptr+0x00006204+4*9))=0x32b6f31d;
*((unsigned int *)((unsigned long)context_ptr+0x00006204+4*10))=0x9a10747f;
*((unsigned int *)((unsigned long)context_ptr+0x00006204+4*11))=0x22155732;
*((unsigned int *)((unsigned long)context_ptr+0x00006204+4*12))=0xaf0375a7;
*((unsigned int *)((unsigned long)context_ptr+0x00006204+4*13))=0x80c037bd;
*((unsigned int *)((unsigned long)context_ptr+0x00006204+4*14))=0x2eb81a37;
*((unsigned int *)((unsigned long)context_ptr+0x00006204+4*15))=0xe09bdeb3;
*((unsigned int *)((unsigned long)context_ptr+0x00006204+4*16))=0xfd9cd956;
*((unsigned int *)((unsigned long)context_ptr+0x00006204+4*17))=0xb36ba076;
*((unsigned int *)((unsigned long)context_ptr+0x00006204+4*18))=0x05d91b31;
*((unsigned int *)((unsigned long)context_ptr+0x00006204+4*19))=0x2a92eb59;
*((unsigned int *)((unsigned long)context_ptr+0x00006204+4*20))=0x9d73e272;
*((unsigned int *)((unsigned long)context_ptr+0x00006204+4*21))=0x47b1d068;
*((unsigned int *)((unsigned long)context_ptr+0x00006204+4*22))=0x9254934b;
*((unsigned int *)((unsigned long)context_ptr+0x00006204+4*23))=0x82dff9c3;
*((unsigned int *)((unsigned long)context_ptr+0x00006204+4*24))=0x5a6e3058;
*((unsigned int *)((unsigned long)context_ptr+0x00006204+4*25))=0xe0d2b147;
*((unsigned int *)((unsigned long)context_ptr+0x00006204+4*26))=0x7334e5f9;
*((unsigned int *)((unsigned long)context_ptr+0x00006204+4*27))=0x000000fa;
*((unsigned int *)((unsigned long)context_ptr+0x00003a20))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003a20+4*1))=0x00006488;
*((unsigned int *)((unsigned long)context_ptr+0x00003a20+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003a20+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003a20+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003a20+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000a20))=0x04c0006d;
*((unsigned int *)((unsigned long)context_ptr+0x00000a20+4*1))=0x00006204;
*((unsigned int *)((unsigned long)context_ptr+0x00000a20+4*2))=0x00006074;
*((unsigned int *)((unsigned long)context_ptr+0x00000a20+4*3))=0x0222006d;
*((unsigned int *)((unsigned long)context_ptr+0x00000a20+4*4))=0x034d757d;
*((unsigned int *)((unsigned long)context_ptr+0x00000a20+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000023a&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000065e0,"\x80\xa2\x7a\x25\x15\x6d\xa0\xc4\x37\x82\x2d\x35\xeb\xdd\x06\x8e\xff\x79\x0a\x72",20))
printf("strip: 80a27a25156da0c4, Pass\n");
else
printf("strip: 80a27a25156da0c4, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006098))=0x016a0a02;
*((unsigned int *)((unsigned long)context_ptr+0x00006098+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006098+4*2))=0x0202006e;
*((unsigned int *)((unsigned long)context_ptr+0x00006098+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x00006534))=0x8e569126;
*((unsigned int *)((unsigned long)context_ptr+0x00006534+4*1))=0x5b7c6f3d;
*((unsigned int *)((unsigned long)context_ptr+0x00006534+4*2))=0x1e84b054;
*((unsigned int *)((unsigned long)context_ptr+0x00006534+4*3))=0x1f31b45b;
*((unsigned int *)((unsigned long)context_ptr+0x00006534+4*4))=0x4105aa35;
*((unsigned int *)((unsigned long)context_ptr+0x00006534+4*5))=0x6ef4b2db;
*((unsigned int *)((unsigned long)context_ptr+0x00006534+4*6))=0xe4cebf1f;
*((unsigned int *)((unsigned long)context_ptr+0x00006534+4*7))=0x770019af;
*((unsigned int *)((unsigned long)context_ptr+0x00006534+4*8))=0xee1f29c8;
*((unsigned int *)((unsigned long)context_ptr+0x00006534+4*9))=0xe7716dbd;
*((unsigned int *)((unsigned long)context_ptr+0x00006534+4*10))=0x9b8f08be;
*((unsigned int *)((unsigned long)context_ptr+0x00006534+4*11))=0x9093b34d;
*((unsigned int *)((unsigned long)context_ptr+0x00006534+4*12))=0x054e62ae;
*((unsigned int *)((unsigned long)context_ptr+0x00006534+4*13))=0x42cddbb8;
*((unsigned int *)((unsigned long)context_ptr+0x00006534+4*14))=0xa54ceabd;
*((unsigned int *)((unsigned long)context_ptr+0x00006534+4*15))=0xc24728bf;
*((unsigned int *)((unsigned long)context_ptr+0x00006534+4*16))=0x290c2ea2;
*((unsigned int *)((unsigned long)context_ptr+0x00006534+4*17))=0xd052be32;
*((unsigned int *)((unsigned long)context_ptr+0x00006534+4*18))=0x03dd4042;
*((unsigned int *)((unsigned long)context_ptr+0x00006534+4*19))=0xac7cea4b;
*((unsigned int *)((unsigned long)context_ptr+0x00006534+4*20))=0xa3baf79a;
*((unsigned int *)((unsigned long)context_ptr+0x00006534+4*21))=0x4d9a034d;
*((unsigned int *)((unsigned long)context_ptr+0x00006534+4*22))=0xc1c0d6c2;
*((unsigned int *)((unsigned long)context_ptr+0x00006534+4*23))=0xeb77a6f3;
*((unsigned int *)((unsigned long)context_ptr+0x00006534+4*24))=0x25234784;
*((unsigned int *)((unsigned long)context_ptr+0x00006534+4*25))=0x962b2d19;
*((unsigned int *)((unsigned long)context_ptr+0x00006534+4*26))=0xa043f804;
*((unsigned int *)((unsigned long)context_ptr+0x00006534+4*27))=0x000083f0;
*((unsigned int *)((unsigned long)context_ptr+0x00003a38))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003a38+4*1))=0x00006274;
*((unsigned int *)((unsigned long)context_ptr+0x00003a38+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003a38+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003a38+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003a38+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000a38))=0x04c0006e;
*((unsigned int *)((unsigned long)context_ptr+0x00000a38+4*1))=0x00006534;
*((unsigned int *)((unsigned long)context_ptr+0x00000a38+4*2))=0x00006098;
*((unsigned int *)((unsigned long)context_ptr+0x00000a38+4*3))=0x0222006e;
*((unsigned int *)((unsigned long)context_ptr+0x00000a38+4*4))=0x0ad9e0ed;
*((unsigned int *)((unsigned long)context_ptr+0x00000a38+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000240&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006738,"\x11\x96\xe3\xf8\x39\x1a\x6b\x18\x3b\x7a\x5e\x8f\x2c\xb0\x42\x11\x5a\xea\x23\xa7",20))
printf("strip: 1196e3f8391a6b18, Pass\n");
else
printf("strip: 1196e3f8391a6b18, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000065a4))=0x016a0a02;
*((unsigned int *)((unsigned long)context_ptr+0x000065a4+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000065a4+4*2))=0x0202006f;
*((unsigned int *)((unsigned long)context_ptr+0x000065a4+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x000066d4))=0x54a24989;
*((unsigned int *)((unsigned long)context_ptr+0x000066d4+4*1))=0x8a77db66;
*((unsigned int *)((unsigned long)context_ptr+0x000066d4+4*2))=0x9d9abc00;
*((unsigned int *)((unsigned long)context_ptr+0x000066d4+4*3))=0xffdfccaf;
*((unsigned int *)((unsigned long)context_ptr+0x000066d4+4*4))=0x37238fa9;
*((unsigned int *)((unsigned long)context_ptr+0x000066d4+4*5))=0xead897fb;
*((unsigned int *)((unsigned long)context_ptr+0x000066d4+4*6))=0xad51787c;
*((unsigned int *)((unsigned long)context_ptr+0x000066d4+4*7))=0xa41cd3f1;
*((unsigned int *)((unsigned long)context_ptr+0x000066d4+4*8))=0xfa197161;
*((unsigned int *)((unsigned long)context_ptr+0x000066d4+4*9))=0xd4c56373;
*((unsigned int *)((unsigned long)context_ptr+0x000066d4+4*10))=0xa43f6aa8;
*((unsigned int *)((unsigned long)context_ptr+0x000066d4+4*11))=0xe11dae58;
*((unsigned int *)((unsigned long)context_ptr+0x000066d4+4*12))=0x5153bbe1;
*((unsigned int *)((unsigned long)context_ptr+0x000066d4+4*13))=0x71b04b96;
*((unsigned int *)((unsigned long)context_ptr+0x000066d4+4*14))=0x7edb0348;
*((unsigned int *)((unsigned long)context_ptr+0x000066d4+4*15))=0x8ac07902;
*((unsigned int *)((unsigned long)context_ptr+0x000066d4+4*16))=0xa56e6462;
*((unsigned int *)((unsigned long)context_ptr+0x000066d4+4*17))=0xee1ecefa;
*((unsigned int *)((unsigned long)context_ptr+0x000066d4+4*18))=0x95f9654b;
*((unsigned int *)((unsigned long)context_ptr+0x000066d4+4*19))=0x2eeae00b;
*((unsigned int *)((unsigned long)context_ptr+0x000066d4+4*20))=0x4cfee03f;
*((unsigned int *)((unsigned long)context_ptr+0x000066d4+4*21))=0xbcfce445;
*((unsigned int *)((unsigned long)context_ptr+0x000066d4+4*22))=0xc3f85b25;
*((unsigned int *)((unsigned long)context_ptr+0x000066d4+4*23))=0x3e6e8251;
*((unsigned int *)((unsigned long)context_ptr+0x000066d4+4*24))=0x0e6506a3;
*((unsigned int *)((unsigned long)context_ptr+0x000066d4+4*25))=0xd0f8d3f1;
*((unsigned int *)((unsigned long)context_ptr+0x000066d4+4*26))=0x187272a0;
*((unsigned int *)((unsigned long)context_ptr+0x000066d4+4*27))=0x005f4226;
*((unsigned int *)((unsigned long)context_ptr+0x00003a50))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003a50+4*1))=0x000065b4;
*((unsigned int *)((unsigned long)context_ptr+0x00003a50+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003a50+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003a50+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003a50+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000a50))=0x04c0006f;
*((unsigned int *)((unsigned long)context_ptr+0x00000a50+4*1))=0x000066d4;
*((unsigned int *)((unsigned long)context_ptr+0x00000a50+4*2))=0x000065a4;
*((unsigned int *)((unsigned long)context_ptr+0x00000a50+4*3))=0x0222006f;
*((unsigned int *)((unsigned long)context_ptr+0x00000a50+4*4))=0x0277e68c;
*((unsigned int *)((unsigned long)context_ptr+0x00000a50+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000246&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000063d8,"\x3c\x7e\xec\xec\x1b\x2c\xc3\xda\x43\x67\x10\x3e\x33\xf9\x14\x0f\xfe\xf9\x6f\x2b",20))
printf("strip: 3c7eecec1b2cc3da, Pass\n");
else
printf("strip: 3c7eecec1b2cc3da, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000063d0))=0x016a0a02;
*((unsigned int *)((unsigned long)context_ptr+0x000063d0+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000063d0+4*2))=0x02020070;
*((unsigned int *)((unsigned long)context_ptr+0x000063d0+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x000065c8))=0xfa3868cd;
*((unsigned int *)((unsigned long)context_ptr+0x000065c8+4*1))=0x4afe1856;
*((unsigned int *)((unsigned long)context_ptr+0x000065c8+4*2))=0xf32ad774;
*((unsigned int *)((unsigned long)context_ptr+0x000065c8+4*3))=0xa9fe2bb9;
*((unsigned int *)((unsigned long)context_ptr+0x000065c8+4*4))=0x6306a335;
*((unsigned int *)((unsigned long)context_ptr+0x000065c8+4*5))=0x825de32c;
*((unsigned int *)((unsigned long)context_ptr+0x000065c8+4*6))=0x8930c2f0;
*((unsigned int *)((unsigned long)context_ptr+0x000065c8+4*7))=0xeaee9f69;
*((unsigned int *)((unsigned long)context_ptr+0x000065c8+4*8))=0xab9403b2;
*((unsigned int *)((unsigned long)context_ptr+0x000065c8+4*9))=0x5a6100ca;
*((unsigned int *)((unsigned long)context_ptr+0x000065c8+4*10))=0xa22240a4;
*((unsigned int *)((unsigned long)context_ptr+0x000065c8+4*11))=0xfa11425e;
*((unsigned int *)((unsigned long)context_ptr+0x000065c8+4*12))=0x054c40a4;
*((unsigned int *)((unsigned long)context_ptr+0x000065c8+4*13))=0xe32861c9;
*((unsigned int *)((unsigned long)context_ptr+0x000065c8+4*14))=0xc3c81c33;
*((unsigned int *)((unsigned long)context_ptr+0x000065c8+4*15))=0x1ab43009;
*((unsigned int *)((unsigned long)context_ptr+0x000065c8+4*16))=0xdc54a9bb;
*((unsigned int *)((unsigned long)context_ptr+0x000065c8+4*17))=0x0cd518ea;
*((unsigned int *)((unsigned long)context_ptr+0x000065c8+4*18))=0x3a208eac;
*((unsigned int *)((unsigned long)context_ptr+0x000065c8+4*19))=0x2a3c2b10;
*((unsigned int *)((unsigned long)context_ptr+0x000065c8+4*20))=0xe58c438c;
*((unsigned int *)((unsigned long)context_ptr+0x000065c8+4*21))=0xb92132af;
*((unsigned int *)((unsigned long)context_ptr+0x000065c8+4*22))=0x9ee8d43b;
*((unsigned int *)((unsigned long)context_ptr+0x000065c8+4*23))=0x19944148;
*((unsigned int *)((unsigned long)context_ptr+0x000065c8+4*24))=0xac92d56a;
*((unsigned int *)((unsigned long)context_ptr+0x000065c8+4*25))=0x8c9a2288;
*((unsigned int *)((unsigned long)context_ptr+0x000065c8+4*26))=0xfaf783fc;
*((unsigned int *)((unsigned long)context_ptr+0x000065c8+4*27))=0xc8d58b3b;
*((unsigned int *)((unsigned long)context_ptr+0x00003a68))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003a68+4*1))=0x00006638;
*((unsigned int *)((unsigned long)context_ptr+0x00003a68+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003a68+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003a68+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003a68+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000a68))=0x04c00070;
*((unsigned int *)((unsigned long)context_ptr+0x00000a68+4*1))=0x000065c8;
*((unsigned int *)((unsigned long)context_ptr+0x00000a68+4*2))=0x000063d0;
*((unsigned int *)((unsigned long)context_ptr+0x00000a68+4*3))=0x02220070;
*((unsigned int *)((unsigned long)context_ptr+0x00000a68+4*4))=0x01feb02b;
*((unsigned int *)((unsigned long)context_ptr+0x00000a68+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000024c&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006330,"\xcb\x12\xed\x7a\xa3\x92\x90\xfa\x15\x03\x08\xd1\x9a\x71\x67\x52\x6f\x34\x85\x6e",20))
printf("strip: cb12ed7aa39290fa, Pass\n");
else
printf("strip: cb12ed7aa39290fa, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x0000664c))=0x016a0a02;
*((unsigned int *)((unsigned long)context_ptr+0x0000664c+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x0000664c+4*2))=0x02020071;
*((unsigned int *)((unsigned long)context_ptr+0x0000664c+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x000067b8))=0x53a0b61a;
*((unsigned int *)((unsigned long)context_ptr+0x000067b8+4*1))=0x94074384;
*((unsigned int *)((unsigned long)context_ptr+0x000067b8+4*2))=0x72764791;
*((unsigned int *)((unsigned long)context_ptr+0x000067b8+4*3))=0xebe354e7;
*((unsigned int *)((unsigned long)context_ptr+0x000067b8+4*4))=0x7e97ed1e;
*((unsigned int *)((unsigned long)context_ptr+0x000067b8+4*5))=0x4f075893;
*((unsigned int *)((unsigned long)context_ptr+0x000067b8+4*6))=0xdfd41397;
*((unsigned int *)((unsigned long)context_ptr+0x000067b8+4*7))=0xd4b74270;
*((unsigned int *)((unsigned long)context_ptr+0x000067b8+4*8))=0x1ec952a9;
*((unsigned int *)((unsigned long)context_ptr+0x000067b8+4*9))=0xa00b6956;
*((unsigned int *)((unsigned long)context_ptr+0x000067b8+4*10))=0xc4a069c8;
*((unsigned int *)((unsigned long)context_ptr+0x000067b8+4*11))=0xef40f5c2;
*((unsigned int *)((unsigned long)context_ptr+0x000067b8+4*12))=0xeb5bc58a;
*((unsigned int *)((unsigned long)context_ptr+0x000067b8+4*13))=0xee07ce62;
*((unsigned int *)((unsigned long)context_ptr+0x000067b8+4*14))=0x7c65d35c;
*((unsigned int *)((unsigned long)context_ptr+0x000067b8+4*15))=0xe2ed0336;
*((unsigned int *)((unsigned long)context_ptr+0x000067b8+4*16))=0x5cea9541;
*((unsigned int *)((unsigned long)context_ptr+0x000067b8+4*17))=0x9e849399;
*((unsigned int *)((unsigned long)context_ptr+0x000067b8+4*18))=0xb74b1c1d;
*((unsigned int *)((unsigned long)context_ptr+0x000067b8+4*19))=0x79cb0063;
*((unsigned int *)((unsigned long)context_ptr+0x000067b8+4*20))=0x09c9b062;
*((unsigned int *)((unsigned long)context_ptr+0x000067b8+4*21))=0x87ba2a38;
*((unsigned int *)((unsigned long)context_ptr+0x000067b8+4*22))=0x03578f2d;
*((unsigned int *)((unsigned long)context_ptr+0x000067b8+4*23))=0xb2efeeef;
*((unsigned int *)((unsigned long)context_ptr+0x000067b8+4*24))=0x10af28cd;
*((unsigned int *)((unsigned long)context_ptr+0x000067b8+4*25))=0xf582bb55;
*((unsigned int *)((unsigned long)context_ptr+0x000067b8+4*26))=0xec63ab4a;
*((unsigned int *)((unsigned long)context_ptr+0x000067b8+4*27))=0x88605584;
*((unsigned int *)((unsigned long)context_ptr+0x000067b8+4*28))=0x000000f2;
*((unsigned int *)((unsigned long)context_ptr+0x00003a80))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003a80+4*1))=0x0000682c;
*((unsigned int *)((unsigned long)context_ptr+0x00003a80+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003a80+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003a80+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003a80+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000a80))=0x04c00071;
*((unsigned int *)((unsigned long)context_ptr+0x00000a80+4*1))=0x000067b8;
*((unsigned int *)((unsigned long)context_ptr+0x00000a80+4*2))=0x0000664c;
*((unsigned int *)((unsigned long)context_ptr+0x00000a80+4*3))=0x02220071;
*((unsigned int *)((unsigned long)context_ptr+0x00000a80+4*4))=0x0702c0a1;
*((unsigned int *)((unsigned long)context_ptr+0x00000a80+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000252&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000060a8,"\x3c\x23\xca\xd7\x9e\x31\x13\x69\x76\x6f\xf9\xac\x71\x3b\xb1\xee\xb5\xe0\x40\x02",20))
printf("strip: 3c23cad79e311369, Pass\n");
else
printf("strip: 3c23cad79e311369, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000060a8))=0x016a0a02;
*((unsigned int *)((unsigned long)context_ptr+0x000060a8+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000060a8+4*2))=0x02020072;
*((unsigned int *)((unsigned long)context_ptr+0x000060a8+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x00006840))=0x21ab67d3;
*((unsigned int *)((unsigned long)context_ptr+0x00006840+4*1))=0x6d159cf9;
*((unsigned int *)((unsigned long)context_ptr+0x00006840+4*2))=0x2b4a3be4;
*((unsigned int *)((unsigned long)context_ptr+0x00006840+4*3))=0x47cb593b;
*((unsigned int *)((unsigned long)context_ptr+0x00006840+4*4))=0xe2608f68;
*((unsigned int *)((unsigned long)context_ptr+0x00006840+4*5))=0x9000ec93;
*((unsigned int *)((unsigned long)context_ptr+0x00006840+4*6))=0xc5338530;
*((unsigned int *)((unsigned long)context_ptr+0x00006840+4*7))=0x9b843721;
*((unsigned int *)((unsigned long)context_ptr+0x00006840+4*8))=0x07b508b5;
*((unsigned int *)((unsigned long)context_ptr+0x00006840+4*9))=0x61002732;
*((unsigned int *)((unsigned long)context_ptr+0x00006840+4*10))=0xa3120658;
*((unsigned int *)((unsigned long)context_ptr+0x00006840+4*11))=0x2bfbd80a;
*((unsigned int *)((unsigned long)context_ptr+0x00006840+4*12))=0x5fb94323;
*((unsigned int *)((unsigned long)context_ptr+0x00006840+4*13))=0x0a523b6e;
*((unsigned int *)((unsigned long)context_ptr+0x00006840+4*14))=0x559a46b6;
*((unsigned int *)((unsigned long)context_ptr+0x00006840+4*15))=0x204dbb92;
*((unsigned int *)((unsigned long)context_ptr+0x00006840+4*16))=0x0c3ffeba;
*((unsigned int *)((unsigned long)context_ptr+0x00006840+4*17))=0x22ea5eb4;
*((unsigned int *)((unsigned long)context_ptr+0x00006840+4*18))=0x78fa8225;
*((unsigned int *)((unsigned long)context_ptr+0x00006840+4*19))=0xffe52d68;
*((unsigned int *)((unsigned long)context_ptr+0x00006840+4*20))=0x9dcd8023;
*((unsigned int *)((unsigned long)context_ptr+0x00006840+4*21))=0x2487cf39;
*((unsigned int *)((unsigned long)context_ptr+0x00006840+4*22))=0xe0493dc6;
*((unsigned int *)((unsigned long)context_ptr+0x00006840+4*23))=0xb1e6af93;
*((unsigned int *)((unsigned long)context_ptr+0x00006840+4*24))=0x92b279d0;
*((unsigned int *)((unsigned long)context_ptr+0x00006840+4*25))=0x524523be;
*((unsigned int *)((unsigned long)context_ptr+0x00006840+4*26))=0x4d0435c8;
*((unsigned int *)((unsigned long)context_ptr+0x00006840+4*27))=0xd7dc9886;
*((unsigned int *)((unsigned long)context_ptr+0x00006840+4*28))=0x00003788;
*((unsigned int *)((unsigned long)context_ptr+0x00003a98))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003a98+4*1))=0x000068b4;
*((unsigned int *)((unsigned long)context_ptr+0x00003a98+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003a98+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003a98+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003a98+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000a98))=0x04c00072;
*((unsigned int *)((unsigned long)context_ptr+0x00000a98+4*1))=0x00006840;
*((unsigned int *)((unsigned long)context_ptr+0x00000a98+4*2))=0x000060a8;
*((unsigned int *)((unsigned long)context_ptr+0x00000a98+4*3))=0x02220072;
*((unsigned int *)((unsigned long)context_ptr+0x00000a98+4*4))=0x0aed58e3;
*((unsigned int *)((unsigned long)context_ptr+0x00000a98+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000258&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000064a4,"\x97\xcf\xd2\xd4\x8f\xb4\x58\x1a\x99\x49\x13\x9d\x16\x1a\x1e\xab\x13\x04\x15\x58",20))
printf("strip: 97cfd2d48fb4581a, Pass\n");
else
printf("strip: 97cfd2d48fb4581a, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x0000649c))=0x016a0a02;
*((unsigned int *)((unsigned long)context_ptr+0x0000649c+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x0000649c+4*2))=0x02020073;
*((unsigned int *)((unsigned long)context_ptr+0x0000649c+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x00006288))=0xf0315093;
*((unsigned int *)((unsigned long)context_ptr+0x00006288+4*1))=0x61e63a05;
*((unsigned int *)((unsigned long)context_ptr+0x00006288+4*2))=0x29e2f27d;
*((unsigned int *)((unsigned long)context_ptr+0x00006288+4*3))=0x10ffbff7;
*((unsigned int *)((unsigned long)context_ptr+0x00006288+4*4))=0x079ef2f5;
*((unsigned int *)((unsigned long)context_ptr+0x00006288+4*5))=0xe5866614;
*((unsigned int *)((unsigned long)context_ptr+0x00006288+4*6))=0x2755f119;
*((unsigned int *)((unsigned long)context_ptr+0x00006288+4*7))=0x9da99c86;
*((unsigned int *)((unsigned long)context_ptr+0x00006288+4*8))=0xf5b7c0c7;
*((unsigned int *)((unsigned long)context_ptr+0x00006288+4*9))=0x51216a43;
*((unsigned int *)((unsigned long)context_ptr+0x00006288+4*10))=0x991a4a39;
*((unsigned int *)((unsigned long)context_ptr+0x00006288+4*11))=0xaf3b8256;
*((unsigned int *)((unsigned long)context_ptr+0x00006288+4*12))=0x5f6ef8ab;
*((unsigned int *)((unsigned long)context_ptr+0x00006288+4*13))=0xdca87a08;
*((unsigned int *)((unsigned long)context_ptr+0x00006288+4*14))=0x3dbf69e7;
*((unsigned int *)((unsigned long)context_ptr+0x00006288+4*15))=0x52cc3ef9;
*((unsigned int *)((unsigned long)context_ptr+0x00006288+4*16))=0x672f4d42;
*((unsigned int *)((unsigned long)context_ptr+0x00006288+4*17))=0x0c68224a;
*((unsigned int *)((unsigned long)context_ptr+0x00006288+4*18))=0x9e21a5e4;
*((unsigned int *)((unsigned long)context_ptr+0x00006288+4*19))=0x2f085b36;
*((unsigned int *)((unsigned long)context_ptr+0x00006288+4*20))=0x12c8f800;
*((unsigned int *)((unsigned long)context_ptr+0x00006288+4*21))=0xd045cd91;
*((unsigned int *)((unsigned long)context_ptr+0x00006288+4*22))=0x8f37638b;
*((unsigned int *)((unsigned long)context_ptr+0x00006288+4*23))=0xbb3a48aa;
*((unsigned int *)((unsigned long)context_ptr+0x00006288+4*24))=0x3b02864e;
*((unsigned int *)((unsigned long)context_ptr+0x00006288+4*25))=0xf72be13d;
*((unsigned int *)((unsigned long)context_ptr+0x00006288+4*26))=0xd63a1b35;
*((unsigned int *)((unsigned long)context_ptr+0x00006288+4*27))=0xa3b02769;
*((unsigned int *)((unsigned long)context_ptr+0x00006288+4*28))=0x00afb732;
*((unsigned int *)((unsigned long)context_ptr+0x00003ab0))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003ab0+4*1))=0x000062fc;
*((unsigned int *)((unsigned long)context_ptr+0x00003ab0+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003ab0+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003ab0+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003ab0+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000ab0))=0x04c00073;
*((unsigned int *)((unsigned long)context_ptr+0x00000ab0+4*1))=0x00006288;
*((unsigned int *)((unsigned long)context_ptr+0x00000ab0+4*2))=0x0000649c;
*((unsigned int *)((unsigned long)context_ptr+0x00000ab0+4*3))=0x02220073;
*((unsigned int *)((unsigned long)context_ptr+0x00000ab0+4*4))=0x0efd68d5;
*((unsigned int *)((unsigned long)context_ptr+0x00000ab0+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000025e&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006450,"\xde\xfd\xee\x9d\x60\xde\x2b\x74\xa9\x07\x73\x16\x47\x85\xe3\xa5\x61\x72\x2f\xbe",20))
printf("strip: defdee9d60de2b74, Pass\n");
else
printf("strip: defdee9d60de2b74, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006310))=0x016a0a02;
*((unsigned int *)((unsigned long)context_ptr+0x00006310+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006310+4*2))=0x02020074;
*((unsigned int *)((unsigned long)context_ptr+0x00006310+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x000063e0))=0xe2971cff;
*((unsigned int *)((unsigned long)context_ptr+0x000063e0+4*1))=0x8b3670fa;
*((unsigned int *)((unsigned long)context_ptr+0x000063e0+4*2))=0x3e922cdd;
*((unsigned int *)((unsigned long)context_ptr+0x000063e0+4*3))=0x02f5a65a;
*((unsigned int *)((unsigned long)context_ptr+0x000063e0+4*4))=0x77a7df0e;
*((unsigned int *)((unsigned long)context_ptr+0x000063e0+4*5))=0xdd6b143e;
*((unsigned int *)((unsigned long)context_ptr+0x000063e0+4*6))=0x67a15bdc;
*((unsigned int *)((unsigned long)context_ptr+0x000063e0+4*7))=0x117e3b10;
*((unsigned int *)((unsigned long)context_ptr+0x000063e0+4*8))=0x5c96e513;
*((unsigned int *)((unsigned long)context_ptr+0x000063e0+4*9))=0xd71539f2;
*((unsigned int *)((unsigned long)context_ptr+0x000063e0+4*10))=0xdd13edc5;
*((unsigned int *)((unsigned long)context_ptr+0x000063e0+4*11))=0x547ce0f0;
*((unsigned int *)((unsigned long)context_ptr+0x000063e0+4*12))=0x4fd249d0;
*((unsigned int *)((unsigned long)context_ptr+0x000063e0+4*13))=0xb5d6de30;
*((unsigned int *)((unsigned long)context_ptr+0x000063e0+4*14))=0x9cd878e7;
*((unsigned int *)((unsigned long)context_ptr+0x000063e0+4*15))=0xc9dc7008;
*((unsigned int *)((unsigned long)context_ptr+0x000063e0+4*16))=0x41e853d7;
*((unsigned int *)((unsigned long)context_ptr+0x000063e0+4*17))=0xcf0d1730;
*((unsigned int *)((unsigned long)context_ptr+0x000063e0+4*18))=0x6a936cac;
*((unsigned int *)((unsigned long)context_ptr+0x000063e0+4*19))=0x613aa6e6;
*((unsigned int *)((unsigned long)context_ptr+0x000063e0+4*20))=0x41b793b0;
*((unsigned int *)((unsigned long)context_ptr+0x000063e0+4*21))=0x44fe370b;
*((unsigned int *)((unsigned long)context_ptr+0x000063e0+4*22))=0x2284a7e6;
*((unsigned int *)((unsigned long)context_ptr+0x000063e0+4*23))=0x2ab09992;
*((unsigned int *)((unsigned long)context_ptr+0x000063e0+4*24))=0x94d9d77d;
*((unsigned int *)((unsigned long)context_ptr+0x000063e0+4*25))=0xb4e7a35e;
*((unsigned int *)((unsigned long)context_ptr+0x000063e0+4*26))=0x0c551f87;
*((unsigned int *)((unsigned long)context_ptr+0x000063e0+4*27))=0x8547ed9f;
*((unsigned int *)((unsigned long)context_ptr+0x000063e0+4*28))=0x2505479d;
*((unsigned int *)((unsigned long)context_ptr+0x00003ac8))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003ac8+4*1))=0x00006320;
*((unsigned int *)((unsigned long)context_ptr+0x00003ac8+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003ac8+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003ac8+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003ac8+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000ac8))=0x04c00074;
*((unsigned int *)((unsigned long)context_ptr+0x00000ac8+4*1))=0x000063e0;
*((unsigned int *)((unsigned long)context_ptr+0x00000ac8+4*2))=0x00006310;
*((unsigned int *)((unsigned long)context_ptr+0x00000ac8+4*3))=0x02220074;
*((unsigned int *)((unsigned long)context_ptr+0x00000ac8+4*4))=0x03d13d82;
*((unsigned int *)((unsigned long)context_ptr+0x00000ac8+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000264&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000064b8,"\x5f\x19\x53\x75\x30\xd2\xdd\xc5\xb8\x6f\xb5\x80\x70\x85\x89\xc7\x76\x26\x83\x2c",20))
printf("strip: 5f19537530d2ddc5, Pass\n");
else
printf("strip: 5f19537530d2ddc5, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006454))=0x016a0a02;
*((unsigned int *)((unsigned long)context_ptr+0x00006454+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006454+4*2))=0x02020075;
*((unsigned int *)((unsigned long)context_ptr+0x00006454+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x000060b8))=0xfb90d11c;
*((unsigned int *)((unsigned long)context_ptr+0x000060b8+4*1))=0x9d24c9ed;
*((unsigned int *)((unsigned long)context_ptr+0x000060b8+4*2))=0x24f2af2b;
*((unsigned int *)((unsigned long)context_ptr+0x000060b8+4*3))=0xa9518e20;
*((unsigned int *)((unsigned long)context_ptr+0x000060b8+4*4))=0xfd2ab048;
*((unsigned int *)((unsigned long)context_ptr+0x000060b8+4*5))=0xdef9fa77;
*((unsigned int *)((unsigned long)context_ptr+0x000060b8+4*6))=0xae6d8568;
*((unsigned int *)((unsigned long)context_ptr+0x000060b8+4*7))=0x33e46a4e;
*((unsigned int *)((unsigned long)context_ptr+0x000060b8+4*8))=0xdf823a6c;
*((unsigned int *)((unsigned long)context_ptr+0x000060b8+4*9))=0x6008b4a1;
*((unsigned int *)((unsigned long)context_ptr+0x000060b8+4*10))=0x003d5a3c;
*((unsigned int *)((unsigned long)context_ptr+0x000060b8+4*11))=0x9945ab6f;
*((unsigned int *)((unsigned long)context_ptr+0x000060b8+4*12))=0x75b0e468;
*((unsigned int *)((unsigned long)context_ptr+0x000060b8+4*13))=0xbf8e80be;
*((unsigned int *)((unsigned long)context_ptr+0x000060b8+4*14))=0xb7c8799f;
*((unsigned int *)((unsigned long)context_ptr+0x000060b8+4*15))=0x1e021eb3;
*((unsigned int *)((unsigned long)context_ptr+0x000060b8+4*16))=0x255f74bb;
*((unsigned int *)((unsigned long)context_ptr+0x000060b8+4*17))=0x62796387;
*((unsigned int *)((unsigned long)context_ptr+0x000060b8+4*18))=0x09053681;
*((unsigned int *)((unsigned long)context_ptr+0x000060b8+4*19))=0xb4f17fd2;
*((unsigned int *)((unsigned long)context_ptr+0x000060b8+4*20))=0xd23c0597;
*((unsigned int *)((unsigned long)context_ptr+0x000060b8+4*21))=0xb799c6f0;
*((unsigned int *)((unsigned long)context_ptr+0x000060b8+4*22))=0xd03d8ce8;
*((unsigned int *)((unsigned long)context_ptr+0x000060b8+4*23))=0x5dd95db1;
*((unsigned int *)((unsigned long)context_ptr+0x000060b8+4*24))=0xcd676f57;
*((unsigned int *)((unsigned long)context_ptr+0x000060b8+4*25))=0x946cfe04;
*((unsigned int *)((unsigned long)context_ptr+0x000060b8+4*26))=0x5419d4e1;
*((unsigned int *)((unsigned long)context_ptr+0x000060b8+4*27))=0xe991245b;
*((unsigned int *)((unsigned long)context_ptr+0x000060b8+4*28))=0x4a78eadb;
*((unsigned int *)((unsigned long)context_ptr+0x000060b8+4*29))=0x00000058;
*((unsigned int *)((unsigned long)context_ptr+0x00003ae0))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003ae0+4*1))=0x000064ac;
*((unsigned int *)((unsigned long)context_ptr+0x00003ae0+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003ae0+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003ae0+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003ae0+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000ae0))=0x04c00075;
*((unsigned int *)((unsigned long)context_ptr+0x00000ae0+4*1))=0x000060b8;
*((unsigned int *)((unsigned long)context_ptr+0x00000ae0+4*2))=0x00006454;
*((unsigned int *)((unsigned long)context_ptr+0x00000ae0+4*3))=0x02220075;
*((unsigned int *)((unsigned long)context_ptr+0x00000ae0+4*4))=0x04cfecbb;
*((unsigned int *)((unsigned long)context_ptr+0x00000ae0+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000026a&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006474,"\x3d\xa8\xb6\x9a\xff\x4d\x47\x0a\x9f\x50\x93\xe0\x9e\x63\x0c\xd3\xa9\x64\x1d\xbf",20))
printf("strip: 3da8b69aff4d470a, Pass\n");
else
printf("strip: 3da8b69aff4d470a, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006464))=0x016a0a02;
*((unsigned int *)((unsigned long)context_ptr+0x00006464+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006464+4*2))=0x02020076;
*((unsigned int *)((unsigned long)context_ptr+0x00006464+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x00006130))=0x6f2573d6;
*((unsigned int *)((unsigned long)context_ptr+0x00006130+4*1))=0x9b7c7019;
*((unsigned int *)((unsigned long)context_ptr+0x00006130+4*2))=0x8edeedf2;
*((unsigned int *)((unsigned long)context_ptr+0x00006130+4*3))=0xc825c9c7;
*((unsigned int *)((unsigned long)context_ptr+0x00006130+4*4))=0xbd178865;
*((unsigned int *)((unsigned long)context_ptr+0x00006130+4*5))=0xa300585a;
*((unsigned int *)((unsigned long)context_ptr+0x00006130+4*6))=0xd091bf99;
*((unsigned int *)((unsigned long)context_ptr+0x00006130+4*7))=0xc0ce85e7;
*((unsigned int *)((unsigned long)context_ptr+0x00006130+4*8))=0x324f416a;
*((unsigned int *)((unsigned long)context_ptr+0x00006130+4*9))=0xe21bebfa;
*((unsigned int *)((unsigned long)context_ptr+0x00006130+4*10))=0x231c7eb9;
*((unsigned int *)((unsigned long)context_ptr+0x00006130+4*11))=0x430585f6;
*((unsigned int *)((unsigned long)context_ptr+0x00006130+4*12))=0xbddb640d;
*((unsigned int *)((unsigned long)context_ptr+0x00006130+4*13))=0x4f558362;
*((unsigned int *)((unsigned long)context_ptr+0x00006130+4*14))=0xb7ca8548;
*((unsigned int *)((unsigned long)context_ptr+0x00006130+4*15))=0x742a9f27;
*((unsigned int *)((unsigned long)context_ptr+0x00006130+4*16))=0x691fb8d0;
*((unsigned int *)((unsigned long)context_ptr+0x00006130+4*17))=0x5a5a8adc;
*((unsigned int *)((unsigned long)context_ptr+0x00006130+4*18))=0xcdb7216e;
*((unsigned int *)((unsigned long)context_ptr+0x00006130+4*19))=0x5de42198;
*((unsigned int *)((unsigned long)context_ptr+0x00006130+4*20))=0xb05cf8f9;
*((unsigned int *)((unsigned long)context_ptr+0x00006130+4*21))=0x922fd1e0;
*((unsigned int *)((unsigned long)context_ptr+0x00006130+4*22))=0x600dd4cb;
*((unsigned int *)((unsigned long)context_ptr+0x00006130+4*23))=0x1a1a9ca5;
*((unsigned int *)((unsigned long)context_ptr+0x00006130+4*24))=0xb641daeb;
*((unsigned int *)((unsigned long)context_ptr+0x00006130+4*25))=0x74ec2077;
*((unsigned int *)((unsigned long)context_ptr+0x00006130+4*26))=0x05f8571a;
*((unsigned int *)((unsigned long)context_ptr+0x00006130+4*27))=0x2d94a68f;
*((unsigned int *)((unsigned long)context_ptr+0x00006130+4*28))=0x6e20baf1;
*((unsigned int *)((unsigned long)context_ptr+0x00006130+4*29))=0x00009bb6;
*((unsigned int *)((unsigned long)context_ptr+0x00003af8))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003af8+4*1))=0x00006474;
*((unsigned int *)((unsigned long)context_ptr+0x00003af8+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003af8+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003af8+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003af8+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000af8))=0x04c00076;
*((unsigned int *)((unsigned long)context_ptr+0x00000af8+4*1))=0x00006130;
*((unsigned int *)((unsigned long)context_ptr+0x00000af8+4*2))=0x00006464;
*((unsigned int *)((unsigned long)context_ptr+0x00000af8+4*3))=0x02220076;
*((unsigned int *)((unsigned long)context_ptr+0x00000af8+4*4))=0x03bc8115;
*((unsigned int *)((unsigned long)context_ptr+0x00000af8+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000270&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006384,"\x0b\x8f\x6e\x4a\x14\x67\x6c\x4e\x15\x51\x7a\x5c\xe4\x79\x50\xfc\x01\x48\xec\xd2",20))
printf("strip: 0b8f6e4a14676c4e, Pass\n");
else
printf("strip: 0b8f6e4a14676c4e, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000061a8))=0x016a0a02;
*((unsigned int *)((unsigned long)context_ptr+0x000061a8+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000061a8+4*2))=0x02020077;
*((unsigned int *)((unsigned long)context_ptr+0x000061a8+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x000069ac))=0x3c5580b9;
*((unsigned int *)((unsigned long)context_ptr+0x000069ac+4*1))=0x9eba4e9e;
*((unsigned int *)((unsigned long)context_ptr+0x000069ac+4*2))=0xe62101f0;
*((unsigned int *)((unsigned long)context_ptr+0x000069ac+4*3))=0xa764bc5b;
*((unsigned int *)((unsigned long)context_ptr+0x000069ac+4*4))=0x97dc0e45;
*((unsigned int *)((unsigned long)context_ptr+0x000069ac+4*5))=0x11c44eb6;
*((unsigned int *)((unsigned long)context_ptr+0x000069ac+4*6))=0x09c2fffc;
*((unsigned int *)((unsigned long)context_ptr+0x000069ac+4*7))=0xa0641905;
*((unsigned int *)((unsigned long)context_ptr+0x000069ac+4*8))=0xbb0a7e7f;
*((unsigned int *)((unsigned long)context_ptr+0x000069ac+4*9))=0x879577a7;
*((unsigned int *)((unsigned long)context_ptr+0x000069ac+4*10))=0x61afbeb5;
*((unsigned int *)((unsigned long)context_ptr+0x000069ac+4*11))=0x0453900c;
*((unsigned int *)((unsigned long)context_ptr+0x000069ac+4*12))=0x7595206e;
*((unsigned int *)((unsigned long)context_ptr+0x000069ac+4*13))=0xe96bfcce;
*((unsigned int *)((unsigned long)context_ptr+0x000069ac+4*14))=0x8a5d82fb;
*((unsigned int *)((unsigned long)context_ptr+0x000069ac+4*15))=0x065737f9;
*((unsigned int *)((unsigned long)context_ptr+0x000069ac+4*16))=0xd7267ce5;
*((unsigned int *)((unsigned long)context_ptr+0x000069ac+4*17))=0x2241fe7d;
*((unsigned int *)((unsigned long)context_ptr+0x000069ac+4*18))=0x52c991f5;
*((unsigned int *)((unsigned long)context_ptr+0x000069ac+4*19))=0x1b8efa40;
*((unsigned int *)((unsigned long)context_ptr+0x000069ac+4*20))=0x6583b9aa;
*((unsigned int *)((unsigned long)context_ptr+0x000069ac+4*21))=0xcfc8247f;
*((unsigned int *)((unsigned long)context_ptr+0x000069ac+4*22))=0xd90e0ba5;
*((unsigned int *)((unsigned long)context_ptr+0x000069ac+4*23))=0xc31cc0ea;
*((unsigned int *)((unsigned long)context_ptr+0x000069ac+4*24))=0x638d843b;
*((unsigned int *)((unsigned long)context_ptr+0x000069ac+4*25))=0x69cc0557;
*((unsigned int *)((unsigned long)context_ptr+0x000069ac+4*26))=0x5ce7a353;
*((unsigned int *)((unsigned long)context_ptr+0x000069ac+4*27))=0xf93d39df;
*((unsigned int *)((unsigned long)context_ptr+0x000069ac+4*28))=0x379177e5;
*((unsigned int *)((unsigned long)context_ptr+0x000069ac+4*29))=0x00578dc4;
*((unsigned int *)((unsigned long)context_ptr+0x00003b10))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003b10+4*1))=0x000061b8;
*((unsigned int *)((unsigned long)context_ptr+0x00003b10+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003b10+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003b10+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003b10+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000b10))=0x04c00077;
*((unsigned int *)((unsigned long)context_ptr+0x00000b10+4*1))=0x000069ac;
*((unsigned int *)((unsigned long)context_ptr+0x00000b10+4*2))=0x000061a8;
*((unsigned int *)((unsigned long)context_ptr+0x00000b10+4*3))=0x02220077;
*((unsigned int *)((unsigned long)context_ptr+0x00000b10+4*4))=0x0e4ca4aa;
*((unsigned int *)((unsigned long)context_ptr+0x00000b10+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000276&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000063a8,"\x85\xe6\x99\x79\x3d\x95\x7a\x2c\x1b\x23\x36\xed\x95\x91\x4c\xe9\x9e\xc8\xbd\x49",20))
printf("strip: 85e699793d957a2c, Pass\n");
else
printf("strip: 85e699793d957a2c, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000061cc))=0x016a0a02;
*((unsigned int *)((unsigned long)context_ptr+0x000061cc+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000061cc+4*2))=0x02020078;
*((unsigned int *)((unsigned long)context_ptr+0x000061cc+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x000068c8))=0x3c663b8c;
*((unsigned int *)((unsigned long)context_ptr+0x000068c8+4*1))=0x2e7c46c7;
*((unsigned int *)((unsigned long)context_ptr+0x000068c8+4*2))=0xcc5bbd8f;
*((unsigned int *)((unsigned long)context_ptr+0x000068c8+4*3))=0x7435495f;
*((unsigned int *)((unsigned long)context_ptr+0x000068c8+4*4))=0xae180999;
*((unsigned int *)((unsigned long)context_ptr+0x000068c8+4*5))=0x51b5551e;
*((unsigned int *)((unsigned long)context_ptr+0x000068c8+4*6))=0x9688c451;
*((unsigned int *)((unsigned long)context_ptr+0x000068c8+4*7))=0xbe5decee;
*((unsigned int *)((unsigned long)context_ptr+0x000068c8+4*8))=0xa9012dc1;
*((unsigned int *)((unsigned long)context_ptr+0x000068c8+4*9))=0xd4cecce7;
*((unsigned int *)((unsigned long)context_ptr+0x000068c8+4*10))=0x7bd4d99c;
*((unsigned int *)((unsigned long)context_ptr+0x000068c8+4*11))=0x24a3fa21;
*((unsigned int *)((unsigned long)context_ptr+0x000068c8+4*12))=0x95d385f5;
*((unsigned int *)((unsigned long)context_ptr+0x000068c8+4*13))=0x66fec2b4;
*((unsigned int *)((unsigned long)context_ptr+0x000068c8+4*14))=0xa8e90b81;
*((unsigned int *)((unsigned long)context_ptr+0x000068c8+4*15))=0x3611e097;
*((unsigned int *)((unsigned long)context_ptr+0x000068c8+4*16))=0xd548edfc;
*((unsigned int *)((unsigned long)context_ptr+0x000068c8+4*17))=0x9dbc6236;
*((unsigned int *)((unsigned long)context_ptr+0x000068c8+4*18))=0x4f372caa;
*((unsigned int *)((unsigned long)context_ptr+0x000068c8+4*19))=0xe9564470;
*((unsigned int *)((unsigned long)context_ptr+0x000068c8+4*20))=0xf8c3fea3;
*((unsigned int *)((unsigned long)context_ptr+0x000068c8+4*21))=0x56349ebe;
*((unsigned int *)((unsigned long)context_ptr+0x000068c8+4*22))=0xd0f904de;
*((unsigned int *)((unsigned long)context_ptr+0x000068c8+4*23))=0x6918d83c;
*((unsigned int *)((unsigned long)context_ptr+0x000068c8+4*24))=0x6c10dacd;
*((unsigned int *)((unsigned long)context_ptr+0x000068c8+4*25))=0xf25f68cd;
*((unsigned int *)((unsigned long)context_ptr+0x000068c8+4*26))=0x869f3d24;
*((unsigned int *)((unsigned long)context_ptr+0x000068c8+4*27))=0xc5953159;
*((unsigned int *)((unsigned long)context_ptr+0x000068c8+4*28))=0xa57a2d0b;
*((unsigned int *)((unsigned long)context_ptr+0x000068c8+4*29))=0x2827c64e;
*((unsigned int *)((unsigned long)context_ptr+0x00003b28))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003b28+4*1))=0x000061dc;
*((unsigned int *)((unsigned long)context_ptr+0x00003b28+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003b28+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003b28+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003b28+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000b28))=0x04c00078;
*((unsigned int *)((unsigned long)context_ptr+0x00000b28+4*1))=0x000068c8;
*((unsigned int *)((unsigned long)context_ptr+0x00000b28+4*2))=0x000061cc;
*((unsigned int *)((unsigned long)context_ptr+0x00000b28+4*3))=0x02220078;
*((unsigned int *)((unsigned long)context_ptr+0x00000b28+4*4))=0x0ec9c4f4;
*((unsigned int *)((unsigned long)context_ptr+0x00000b28+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000027c&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000063bc,"\x25\x4d\xcc\x25\x96\x5e\x0b\x16\xcb\xe8\x6c\x58\xf7\x01\x16\xf4\x37\x5c\x56\x8b",20))
printf("strip: 254dcc25965e0b16, Pass\n");
else
printf("strip: 254dcc25965e0b16, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006040))=0x016a0a02;
*((unsigned int *)((unsigned long)context_ptr+0x00006040+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006040+4*2))=0x02020079;
*((unsigned int *)((unsigned long)context_ptr+0x00006040+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x00006334))=0xb08673fe;
*((unsigned int *)((unsigned long)context_ptr+0x00006334+4*1))=0xfb9088bc;
*((unsigned int *)((unsigned long)context_ptr+0x00006334+4*2))=0xc252ea90;
*((unsigned int *)((unsigned long)context_ptr+0x00006334+4*3))=0xe4066998;
*((unsigned int *)((unsigned long)context_ptr+0x00006334+4*4))=0x49d1de7d;
*((unsigned int *)((unsigned long)context_ptr+0x00006334+4*5))=0xd5acd69a;
*((unsigned int *)((unsigned long)context_ptr+0x00006334+4*6))=0xde152b74;
*((unsigned int *)((unsigned long)context_ptr+0x00006334+4*7))=0x9854a427;
*((unsigned int *)((unsigned long)context_ptr+0x00006334+4*8))=0x1a354373;
*((unsigned int *)((unsigned long)context_ptr+0x00006334+4*9))=0xcfc64b89;
*((unsigned int *)((unsigned long)context_ptr+0x00006334+4*10))=0xe4bfc260;
*((unsigned int *)((unsigned long)context_ptr+0x00006334+4*11))=0xfc2fe2b6;
*((unsigned int *)((unsigned long)context_ptr+0x00006334+4*12))=0x7dcbc749;
*((unsigned int *)((unsigned long)context_ptr+0x00006334+4*13))=0x374e0ae9;
*((unsigned int *)((unsigned long)context_ptr+0x00006334+4*14))=0x46328a09;
*((unsigned int *)((unsigned long)context_ptr+0x00006334+4*15))=0x1e1cca92;
*((unsigned int *)((unsigned long)context_ptr+0x00006334+4*16))=0x9e8407e0;
*((unsigned int *)((unsigned long)context_ptr+0x00006334+4*17))=0xbee36712;
*((unsigned int *)((unsigned long)context_ptr+0x00006334+4*18))=0x87b39cbe;
*((unsigned int *)((unsigned long)context_ptr+0x00006334+4*19))=0xbcc3f135;
*((unsigned int *)((unsigned long)context_ptr+0x00006334+4*20))=0xb19d3910;
*((unsigned int *)((unsigned long)context_ptr+0x00006334+4*21))=0xe61b9172;
*((unsigned int *)((unsigned long)context_ptr+0x00006334+4*22))=0x640f865d;
*((unsigned int *)((unsigned long)context_ptr+0x00006334+4*23))=0xc6ca2c92;
*((unsigned int *)((unsigned long)context_ptr+0x00006334+4*24))=0x633094f7;
*((unsigned int *)((unsigned long)context_ptr+0x00006334+4*25))=0xa47168c4;
*((unsigned int *)((unsigned long)context_ptr+0x00006334+4*26))=0x8997656e;
*((unsigned int *)((unsigned long)context_ptr+0x00006334+4*27))=0xee19f837;
*((unsigned int *)((unsigned long)context_ptr+0x00006334+4*28))=0x08a469e1;
*((unsigned int *)((unsigned long)context_ptr+0x00006334+4*29))=0x85bc3293;
*((unsigned int *)((unsigned long)context_ptr+0x00006334+4*30))=0x00000076;
*((unsigned int *)((unsigned long)context_ptr+0x00003b40))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003b40+4*1))=0x000061f0;
*((unsigned int *)((unsigned long)context_ptr+0x00003b40+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003b40+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003b40+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003b40+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000b40))=0x04c00079;
*((unsigned int *)((unsigned long)context_ptr+0x00000b40+4*1))=0x00006334;
*((unsigned int *)((unsigned long)context_ptr+0x00000b40+4*2))=0x00006040;
*((unsigned int *)((unsigned long)context_ptr+0x00000b40+4*3))=0x02220079;
*((unsigned int *)((unsigned long)context_ptr+0x00000b40+4*4))=0x0cbb4b8c;
*((unsigned int *)((unsigned long)context_ptr+0x00000b40+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000282&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006060,"\xed\x58\xeb\xa8\xd7\xd1\x58\x44\x8a\x2f\x7d\x9c\xfa\x17\x71\xd9\x8d\x91\x19\x32",20))
printf("strip: ed58eba8d7d15844, Pass\n");
else
printf("strip: ed58eba8d7d15844, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006030))=0x016a0a02;
*((unsigned int *)((unsigned long)context_ptr+0x00006030+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006030+4*2))=0x0202007a;
*((unsigned int *)((unsigned long)context_ptr+0x00006030+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x00006a24))=0x82f6bd79;
*((unsigned int *)((unsigned long)context_ptr+0x00006a24+4*1))=0x6287cc99;
*((unsigned int *)((unsigned long)context_ptr+0x00006a24+4*2))=0x6a23bec5;
*((unsigned int *)((unsigned long)context_ptr+0x00006a24+4*3))=0x0bfeb9be;
*((unsigned int *)((unsigned long)context_ptr+0x00006a24+4*4))=0x490d30ba;
*((unsigned int *)((unsigned long)context_ptr+0x00006a24+4*5))=0x0474e7bd;
*((unsigned int *)((unsigned long)context_ptr+0x00006a24+4*6))=0x86d9f012;
*((unsigned int *)((unsigned long)context_ptr+0x00006a24+4*7))=0x9342e832;
*((unsigned int *)((unsigned long)context_ptr+0x00006a24+4*8))=0x8f03ccb9;
*((unsigned int *)((unsigned long)context_ptr+0x00006a24+4*9))=0x0a7c9548;
*((unsigned int *)((unsigned long)context_ptr+0x00006a24+4*10))=0xecaec5ff;
*((unsigned int *)((unsigned long)context_ptr+0x00006a24+4*11))=0x0df82c97;
*((unsigned int *)((unsigned long)context_ptr+0x00006a24+4*12))=0x8c54a40e;
*((unsigned int *)((unsigned long)context_ptr+0x00006a24+4*13))=0x9eb46454;
*((unsigned int *)((unsigned long)context_ptr+0x00006a24+4*14))=0xf46b56f0;
*((unsigned int *)((unsigned long)context_ptr+0x00006a24+4*15))=0xc9ca1ce8;
*((unsigned int *)((unsigned long)context_ptr+0x00006a24+4*16))=0x35ffb541;
*((unsigned int *)((unsigned long)context_ptr+0x00006a24+4*17))=0x8334f6c4;
*((unsigned int *)((unsigned long)context_ptr+0x00006a24+4*18))=0xaf9f80fb;
*((unsigned int *)((unsigned long)context_ptr+0x00006a24+4*19))=0x1d33cc6c;
*((unsigned int *)((unsigned long)context_ptr+0x00006a24+4*20))=0x66638abb;
*((unsigned int *)((unsigned long)context_ptr+0x00006a24+4*21))=0x87f55b6a;
*((unsigned int *)((unsigned long)context_ptr+0x00006a24+4*22))=0x64254ab7;
*((unsigned int *)((unsigned long)context_ptr+0x00006a24+4*23))=0x3a9cb6ba;
*((unsigned int *)((unsigned long)context_ptr+0x00006a24+4*24))=0x4b430dba;
*((unsigned int *)((unsigned long)context_ptr+0x00006a24+4*25))=0x5197a314;
*((unsigned int *)((unsigned long)context_ptr+0x00006a24+4*26))=0x8b3decdc;
*((unsigned int *)((unsigned long)context_ptr+0x00006a24+4*27))=0xaa1937e7;
*((unsigned int *)((unsigned long)context_ptr+0x00006a24+4*28))=0xb9af1ace;
*((unsigned int *)((unsigned long)context_ptr+0x00006a24+4*29))=0x53aa4b3a;
*((unsigned int *)((unsigned long)context_ptr+0x00006a24+4*30))=0x00001e07;
*((unsigned int *)((unsigned long)context_ptr+0x00003b58))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003b58+4*1))=0x00006060;
*((unsigned int *)((unsigned long)context_ptr+0x00003b58+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003b58+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003b58+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003b58+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000b58))=0x04c0007a;
*((unsigned int *)((unsigned long)context_ptr+0x00000b58+4*1))=0x00006a24;
*((unsigned int *)((unsigned long)context_ptr+0x00000b58+4*2))=0x00006030;
*((unsigned int *)((unsigned long)context_ptr+0x00000b58+4*3))=0x0222007a;
*((unsigned int *)((unsigned long)context_ptr+0x00000b58+4*4))=0x08c5af23;
*((unsigned int *)((unsigned long)context_ptr+0x00000b58+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000288&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006084,"\x48\x7e\xcb\x36\xae\xe0\x84\xd8\xc6\xa0\x77\x60\x23\xd3\x9b\xa8\x39\x01\x49\x9d",20))
printf("strip: 487ecb36aee084d8, Pass\n");
else
printf("strip: 487ecb36aee084d8, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006050))=0x016a0a02;
*((unsigned int *)((unsigned long)context_ptr+0x00006050+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006050+4*2))=0x0202007b;
*((unsigned int *)((unsigned long)context_ptr+0x00006050+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x00006aa0))=0x447e4647;
*((unsigned int *)((unsigned long)context_ptr+0x00006aa0+4*1))=0x3aa5f73c;
*((unsigned int *)((unsigned long)context_ptr+0x00006aa0+4*2))=0x02dbaa81;
*((unsigned int *)((unsigned long)context_ptr+0x00006aa0+4*3))=0xb33e34a0;
*((unsigned int *)((unsigned long)context_ptr+0x00006aa0+4*4))=0x47b7ed20;
*((unsigned int *)((unsigned long)context_ptr+0x00006aa0+4*5))=0x3390b336;
*((unsigned int *)((unsigned long)context_ptr+0x00006aa0+4*6))=0xc85dcf1d;
*((unsigned int *)((unsigned long)context_ptr+0x00006aa0+4*7))=0xad39ec7f;
*((unsigned int *)((unsigned long)context_ptr+0x00006aa0+4*8))=0x2bec3285;
*((unsigned int *)((unsigned long)context_ptr+0x00006aa0+4*9))=0xc60ef9f2;
*((unsigned int *)((unsigned long)context_ptr+0x00006aa0+4*10))=0x96ba378a;
*((unsigned int *)((unsigned long)context_ptr+0x00006aa0+4*11))=0xc2f39a5e;
*((unsigned int *)((unsigned long)context_ptr+0x00006aa0+4*12))=0xc89b926c;
*((unsigned int *)((unsigned long)context_ptr+0x00006aa0+4*13))=0x76b443d6;
*((unsigned int *)((unsigned long)context_ptr+0x00006aa0+4*14))=0x000de5b5;
*((unsigned int *)((unsigned long)context_ptr+0x00006aa0+4*15))=0x62601678;
*((unsigned int *)((unsigned long)context_ptr+0x00006aa0+4*16))=0x7119073a;
*((unsigned int *)((unsigned long)context_ptr+0x00006aa0+4*17))=0xd2980157;
*((unsigned int *)((unsigned long)context_ptr+0x00006aa0+4*18))=0x83b7ff74;
*((unsigned int *)((unsigned long)context_ptr+0x00006aa0+4*19))=0xa25593d6;
*((unsigned int *)((unsigned long)context_ptr+0x00006aa0+4*20))=0xc13d8a8a;
*((unsigned int *)((unsigned long)context_ptr+0x00006aa0+4*21))=0xda565abd;
*((unsigned int *)((unsigned long)context_ptr+0x00006aa0+4*22))=0x91636532;
*((unsigned int *)((unsigned long)context_ptr+0x00006aa0+4*23))=0xa964e91b;
*((unsigned int *)((unsigned long)context_ptr+0x00006aa0+4*24))=0xb413d8e0;
*((unsigned int *)((unsigned long)context_ptr+0x00006aa0+4*25))=0xf73457d8;
*((unsigned int *)((unsigned long)context_ptr+0x00006aa0+4*26))=0x5281f84c;
*((unsigned int *)((unsigned long)context_ptr+0x00006aa0+4*27))=0x0256a674;
*((unsigned int *)((unsigned long)context_ptr+0x00006aa0+4*28))=0x7e6665f5;
*((unsigned int *)((unsigned long)context_ptr+0x00006aa0+4*29))=0x9778c863;
*((unsigned int *)((unsigned long)context_ptr+0x00006aa0+4*30))=0x00c827a0;
*((unsigned int *)((unsigned long)context_ptr+0x00003b70))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003b70+4*1))=0x00006084;
*((unsigned int *)((unsigned long)context_ptr+0x00003b70+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003b70+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003b70+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003b70+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000b70))=0x04c0007b;
*((unsigned int *)((unsigned long)context_ptr+0x00000b70+4*1))=0x00006aa0;
*((unsigned int *)((unsigned long)context_ptr+0x00000b70+4*2))=0x00006050;
*((unsigned int *)((unsigned long)context_ptr+0x00000b70+4*3))=0x0222007b;
*((unsigned int *)((unsigned long)context_ptr+0x00000b70+4*4))=0x06ef7371;
*((unsigned int *)((unsigned long)context_ptr+0x00000b70+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000028e&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006488,"\x74\xf0\x63\x3e\x08\x87\xc1\xb4\xd4\x9b\xb7\x06\xfc\xbe\x31\x8c\x2b\x44\x39\xbf",20))
printf("strip: 74f0633e0887c1b4, Pass\n");
else
printf("strip: 74f0633e0887c1b4, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006074))=0x016a0a02;
*((unsigned int *)((unsigned long)context_ptr+0x00006074+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006074+4*2))=0x0202007c;
*((unsigned int *)((unsigned long)context_ptr+0x00006074+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x00006b1c))=0x7dbd8831;
*((unsigned int *)((unsigned long)context_ptr+0x00006b1c+4*1))=0x03431be6;
*((unsigned int *)((unsigned long)context_ptr+0x00006b1c+4*2))=0xe14c79cc;
*((unsigned int *)((unsigned long)context_ptr+0x00006b1c+4*3))=0x6beca2db;
*((unsigned int *)((unsigned long)context_ptr+0x00006b1c+4*4))=0xbbeb6a95;
*((unsigned int *)((unsigned long)context_ptr+0x00006b1c+4*5))=0x82e51889;
*((unsigned int *)((unsigned long)context_ptr+0x00006b1c+4*6))=0x7482b456;
*((unsigned int *)((unsigned long)context_ptr+0x00006b1c+4*7))=0x82ad08b7;
*((unsigned int *)((unsigned long)context_ptr+0x00006b1c+4*8))=0x03d4f0bf;
*((unsigned int *)((unsigned long)context_ptr+0x00006b1c+4*9))=0xef505a73;
*((unsigned int *)((unsigned long)context_ptr+0x00006b1c+4*10))=0x1d0996bf;
*((unsigned int *)((unsigned long)context_ptr+0x00006b1c+4*11))=0x78e2e66e;
*((unsigned int *)((unsigned long)context_ptr+0x00006b1c+4*12))=0x0abe7e29;
*((unsigned int *)((unsigned long)context_ptr+0x00006b1c+4*13))=0xf2a7c670;
*((unsigned int *)((unsigned long)context_ptr+0x00006b1c+4*14))=0x26bab66b;
*((unsigned int *)((unsigned long)context_ptr+0x00006b1c+4*15))=0x00958d60;
*((unsigned int *)((unsigned long)context_ptr+0x00006b1c+4*16))=0x53f989a7;
*((unsigned int *)((unsigned long)context_ptr+0x00006b1c+4*17))=0x2979864e;
*((unsigned int *)((unsigned long)context_ptr+0x00006b1c+4*18))=0x95861a7c;
*((unsigned int *)((unsigned long)context_ptr+0x00006b1c+4*19))=0x30e86ac6;
*((unsigned int *)((unsigned long)context_ptr+0x00006b1c+4*20))=0x044091be;
*((unsigned int *)((unsigned long)context_ptr+0x00006b1c+4*21))=0xad7d132a;
*((unsigned int *)((unsigned long)context_ptr+0x00006b1c+4*22))=0xafb4a67e;
*((unsigned int *)((unsigned long)context_ptr+0x00006b1c+4*23))=0x20d8c607;
*((unsigned int *)((unsigned long)context_ptr+0x00006b1c+4*24))=0x0a23a72d;
*((unsigned int *)((unsigned long)context_ptr+0x00006b1c+4*25))=0xa644a2ed;
*((unsigned int *)((unsigned long)context_ptr+0x00006b1c+4*26))=0xef1b6265;
*((unsigned int *)((unsigned long)context_ptr+0x00006b1c+4*27))=0xa5ebb370;
*((unsigned int *)((unsigned long)context_ptr+0x00006b1c+4*28))=0x5317a6b4;
*((unsigned int *)((unsigned long)context_ptr+0x00006b1c+4*29))=0x5f4051e3;
*((unsigned int *)((unsigned long)context_ptr+0x00006b1c+4*30))=0x9ad96a17;
*((unsigned int *)((unsigned long)context_ptr+0x00003b88))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003b88+4*1))=0x00006488;
*((unsigned int *)((unsigned long)context_ptr+0x00003b88+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003b88+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003b88+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003b88+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000b88))=0x04c0007c;
*((unsigned int *)((unsigned long)context_ptr+0x00000b88+4*1))=0x00006b1c;
*((unsigned int *)((unsigned long)context_ptr+0x00000b88+4*2))=0x00006074;
*((unsigned int *)((unsigned long)context_ptr+0x00000b88+4*3))=0x0222007c;
*((unsigned int *)((unsigned long)context_ptr+0x00000b88+4*4))=0x09a6284c;
*((unsigned int *)((unsigned long)context_ptr+0x00000b88+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000294&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006274,"\xfc\x89\x8d\x1c\xb8\x86\xf2\x99\x7d\x63\x0f\x8f\x98\x1a\x8d\x58\x85\x64\xb6\x37",20))
printf("strip: fc898d1cb886f299, Pass\n");
else
printf("strip: fc898d1cb886f299, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006098))=0x016a0a02;
*((unsigned int *)((unsigned long)context_ptr+0x00006098+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006098+4*2))=0x0202007d;
*((unsigned int *)((unsigned long)context_ptr+0x00006098+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x00006204))=0x63e9a154;
*((unsigned int *)((unsigned long)context_ptr+0x00006204+4*1))=0x6eeb459c;
*((unsigned int *)((unsigned long)context_ptr+0x00006204+4*2))=0x14120b62;
*((unsigned int *)((unsigned long)context_ptr+0x00006204+4*3))=0x10423c4f;
*((unsigned int *)((unsigned long)context_ptr+0x00006204+4*4))=0x3013fe65;
*((unsigned int *)((unsigned long)context_ptr+0x00006204+4*5))=0xecaa9227;
*((unsigned int *)((unsigned long)context_ptr+0x00006204+4*6))=0x423ec346;
*((unsigned int *)((unsigned long)context_ptr+0x00006204+4*7))=0x9445d50c;
*((unsigned int *)((unsigned long)context_ptr+0x00006204+4*8))=0x44eb8718;
*((unsigned int *)((unsigned long)context_ptr+0x00006204+4*9))=0x55542f99;
*((unsigned int *)((unsigned long)context_ptr+0x00006204+4*10))=0x18726746;
*((unsigned int *)((unsigned long)context_ptr+0x00006204+4*11))=0xb5922d81;
*((unsigned int *)((unsigned long)context_ptr+0x00006204+4*12))=0x11eace5b;
*((unsigned int *)((unsigned long)context_ptr+0x00006204+4*13))=0x0847d670;
*((unsigned int *)((unsigned long)context_ptr+0x00006204+4*14))=0xdc1aef74;
*((unsigned int *)((unsigned long)context_ptr+0x00006204+4*15))=0xd92f8280;
*((unsigned int *)((unsigned long)context_ptr+0x00006204+4*16))=0xf592d3c5;
*((unsigned int *)((unsigned long)context_ptr+0x00006204+4*17))=0xdb642eaa;
*((unsigned int *)((unsigned long)context_ptr+0x00006204+4*18))=0x205098b4;
*((unsigned int *)((unsigned long)context_ptr+0x00006204+4*19))=0x72e844ec;
*((unsigned int *)((unsigned long)context_ptr+0x00006204+4*20))=0xa0211cb3;
*((unsigned int *)((unsigned long)context_ptr+0x00006204+4*21))=0x50a89e7f;
*((unsigned int *)((unsigned long)context_ptr+0x00006204+4*22))=0x25df0985;
*((unsigned int *)((unsigned long)context_ptr+0x00006204+4*23))=0xda03232f;
*((unsigned int *)((unsigned long)context_ptr+0x00006204+4*24))=0xa64f44c4;
*((unsigned int *)((unsigned long)context_ptr+0x00006204+4*25))=0xcfd428b3;
*((unsigned int *)((unsigned long)context_ptr+0x00006204+4*26))=0x190c08ab;
*((unsigned int *)((unsigned long)context_ptr+0x00006204+4*27))=0x6745a0b2;
*((unsigned int *)((unsigned long)context_ptr+0x00006204+4*28))=0xa7b34233;
*((unsigned int *)((unsigned long)context_ptr+0x00006204+4*29))=0xf3e32929;
*((unsigned int *)((unsigned long)context_ptr+0x00006204+4*30))=0x2c561053;
*((unsigned int *)((unsigned long)context_ptr+0x00006204+4*31))=0x00000051;
*((unsigned int *)((unsigned long)context_ptr+0x00003ba0))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003ba0+4*1))=0x000063b0;
*((unsigned int *)((unsigned long)context_ptr+0x00003ba0+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003ba0+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003ba0+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003ba0+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000ba0))=0x04c0007d;
*((unsigned int *)((unsigned long)context_ptr+0x00000ba0+4*1))=0x00006204;
*((unsigned int *)((unsigned long)context_ptr+0x00000ba0+4*2))=0x00006098;
*((unsigned int *)((unsigned long)context_ptr+0x00000ba0+4*3))=0x0222007d;
*((unsigned int *)((unsigned long)context_ptr+0x00000ba0+4*4))=0x01451ea8;
*((unsigned int *)((unsigned long)context_ptr+0x00000ba0+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000029a&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000065b4,"\xd3\x57\x85\xad\xd3\x93\x85\x99\xfa\x10\x3b\xb9\x9c\x90\x92\x7b\x2e\x7d\x46\xf8",20))
printf("strip: d35785add3938599, Pass\n");
else
printf("strip: d35785add3938599, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006940))=0x016a0a02;
*((unsigned int *)((unsigned long)context_ptr+0x00006940+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006940+4*2))=0x0202007e;
*((unsigned int *)((unsigned long)context_ptr+0x00006940+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x000064c0))=0xcb15a5a5;
*((unsigned int *)((unsigned long)context_ptr+0x000064c0+4*1))=0x0ccc9aa7;
*((unsigned int *)((unsigned long)context_ptr+0x000064c0+4*2))=0xdff789b4;
*((unsigned int *)((unsigned long)context_ptr+0x000064c0+4*3))=0xd2e01261;
*((unsigned int *)((unsigned long)context_ptr+0x000064c0+4*4))=0x65121a6b;
*((unsigned int *)((unsigned long)context_ptr+0x000064c0+4*5))=0x644dc04f;
*((unsigned int *)((unsigned long)context_ptr+0x000064c0+4*6))=0x38fb7cb4;
*((unsigned int *)((unsigned long)context_ptr+0x000064c0+4*7))=0x092145b9;
*((unsigned int *)((unsigned long)context_ptr+0x000064c0+4*8))=0xefe82262;
*((unsigned int *)((unsigned long)context_ptr+0x000064c0+4*9))=0x58856b96;
*((unsigned int *)((unsigned long)context_ptr+0x000064c0+4*10))=0x2dd59280;
*((unsigned int *)((unsigned long)context_ptr+0x000064c0+4*11))=0x46e668e2;
*((unsigned int *)((unsigned long)context_ptr+0x000064c0+4*12))=0x20c42aaf;
*((unsigned int *)((unsigned long)context_ptr+0x000064c0+4*13))=0x89fa3469;
*((unsigned int *)((unsigned long)context_ptr+0x000064c0+4*14))=0x44186a2c;
*((unsigned int *)((unsigned long)context_ptr+0x000064c0+4*15))=0x81dae11f;
*((unsigned int *)((unsigned long)context_ptr+0x000064c0+4*16))=0x330330b1;
*((unsigned int *)((unsigned long)context_ptr+0x000064c0+4*17))=0x2743a16a;
*((unsigned int *)((unsigned long)context_ptr+0x000064c0+4*18))=0xcda658ad;
*((unsigned int *)((unsigned long)context_ptr+0x000064c0+4*19))=0x39cb5444;
*((unsigned int *)((unsigned long)context_ptr+0x000064c0+4*20))=0x81da213f;
*((unsigned int *)((unsigned long)context_ptr+0x000064c0+4*21))=0x4239d3c3;
*((unsigned int *)((unsigned long)context_ptr+0x000064c0+4*22))=0xf4549957;
*((unsigned int *)((unsigned long)context_ptr+0x000064c0+4*23))=0x55fe0b62;
*((unsigned int *)((unsigned long)context_ptr+0x000064c0+4*24))=0x7b4b11a1;
*((unsigned int *)((unsigned long)context_ptr+0x000064c0+4*25))=0xebde59c0;
*((unsigned int *)((unsigned long)context_ptr+0x000064c0+4*26))=0x4d9394dd;
*((unsigned int *)((unsigned long)context_ptr+0x000064c0+4*27))=0xb657071d;
*((unsigned int *)((unsigned long)context_ptr+0x000064c0+4*28))=0x63ed7886;
*((unsigned int *)((unsigned long)context_ptr+0x000064c0+4*29))=0x3663418a;
*((unsigned int *)((unsigned long)context_ptr+0x000064c0+4*30))=0x416cb2b4;
*((unsigned int *)((unsigned long)context_ptr+0x000064c0+4*31))=0x0000e74a;
*((unsigned int *)((unsigned long)context_ptr+0x00003bb8))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003bb8+4*1))=0x00006950;
*((unsigned int *)((unsigned long)context_ptr+0x00003bb8+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003bb8+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003bb8+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003bb8+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000bb8))=0x04c0007e;
*((unsigned int *)((unsigned long)context_ptr+0x00000bb8+4*1))=0x000064c0;
*((unsigned int *)((unsigned long)context_ptr+0x00000bb8+4*2))=0x00006940;
*((unsigned int *)((unsigned long)context_ptr+0x00000bb8+4*3))=0x0222007e;
*((unsigned int *)((unsigned long)context_ptr+0x00000bb8+4*4))=0x08b62ec0;
*((unsigned int *)((unsigned long)context_ptr+0x00000bb8+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000002a0&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006638,"\x99\x65\x48\x04\x5b\x66\x1a\x43\xe9\x2c\xc7\x83\x0e\x2e\xe2\x33\xb2\x61\x9e\xc0",20))
printf("strip: 996548045b661a43, Pass\n");
else
printf("strip: 996548045b661a43, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000063c4))=0x016a0a02;
*((unsigned int *)((unsigned long)context_ptr+0x000063c4+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000063c4+4*2))=0x0202007f;
*((unsigned int *)((unsigned long)context_ptr+0x000063c4+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x00006540))=0xe79471f5;
*((unsigned int *)((unsigned long)context_ptr+0x00006540+4*1))=0x2529b530;
*((unsigned int *)((unsigned long)context_ptr+0x00006540+4*2))=0x335667ec;
*((unsigned int *)((unsigned long)context_ptr+0x00006540+4*3))=0x02998124;
*((unsigned int *)((unsigned long)context_ptr+0x00006540+4*4))=0xd3293760;
*((unsigned int *)((unsigned long)context_ptr+0x00006540+4*5))=0x9c8e65b3;
*((unsigned int *)((unsigned long)context_ptr+0x00006540+4*6))=0x8c439665;
*((unsigned int *)((unsigned long)context_ptr+0x00006540+4*7))=0x75941bb5;
*((unsigned int *)((unsigned long)context_ptr+0x00006540+4*8))=0xa2d3360b;
*((unsigned int *)((unsigned long)context_ptr+0x00006540+4*9))=0x3853cfa5;
*((unsigned int *)((unsigned long)context_ptr+0x00006540+4*10))=0x342b6bb5;
*((unsigned int *)((unsigned long)context_ptr+0x00006540+4*11))=0x191d3042;
*((unsigned int *)((unsigned long)context_ptr+0x00006540+4*12))=0xda4e75d9;
*((unsigned int *)((unsigned long)context_ptr+0x00006540+4*13))=0x7df11a5c;
*((unsigned int *)((unsigned long)context_ptr+0x00006540+4*14))=0xcecb1250;
*((unsigned int *)((unsigned long)context_ptr+0x00006540+4*15))=0x5677f1fb;
*((unsigned int *)((unsigned long)context_ptr+0x00006540+4*16))=0x602fbb5a;
*((unsigned int *)((unsigned long)context_ptr+0x00006540+4*17))=0x2bce391f;
*((unsigned int *)((unsigned long)context_ptr+0x00006540+4*18))=0x289b7a6c;
*((unsigned int *)((unsigned long)context_ptr+0x00006540+4*19))=0x91b3faaa;
*((unsigned int *)((unsigned long)context_ptr+0x00006540+4*20))=0xdaeb1083;
*((unsigned int *)((unsigned long)context_ptr+0x00006540+4*21))=0xa2ce2d06;
*((unsigned int *)((unsigned long)context_ptr+0x00006540+4*22))=0xd4a67cf2;
*((unsigned int *)((unsigned long)context_ptr+0x00006540+4*23))=0x9d303d97;
*((unsigned int *)((unsigned long)context_ptr+0x00006540+4*24))=0x5f42afcc;
*((unsigned int *)((unsigned long)context_ptr+0x00006540+4*25))=0x3a01a087;
*((unsigned int *)((unsigned long)context_ptr+0x00006540+4*26))=0xcdf2c3a7;
*((unsigned int *)((unsigned long)context_ptr+0x00006540+4*27))=0x1e963bf4;
*((unsigned int *)((unsigned long)context_ptr+0x00006540+4*28))=0xbcb03e9b;
*((unsigned int *)((unsigned long)context_ptr+0x00006540+4*29))=0x186e0b7c;
*((unsigned int *)((unsigned long)context_ptr+0x00006540+4*30))=0x23ebd68c;
*((unsigned int *)((unsigned long)context_ptr+0x00006540+4*31))=0x00df3294;
*((unsigned int *)((unsigned long)context_ptr+0x00003bd0))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003bd0+4*1))=0x00006964;
*((unsigned int *)((unsigned long)context_ptr+0x00003bd0+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003bd0+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003bd0+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003bd0+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000bd0))=0x04c0007f;
*((unsigned int *)((unsigned long)context_ptr+0x00000bd0+4*1))=0x00006540;
*((unsigned int *)((unsigned long)context_ptr+0x00000bd0+4*2))=0x000063c4;
*((unsigned int *)((unsigned long)context_ptr+0x00000bd0+4*3))=0x0222007f;
*((unsigned int *)((unsigned long)context_ptr+0x00000bd0+4*4))=0x0c67502d;
*((unsigned int *)((unsigned long)context_ptr+0x00000bd0+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000002a6&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x0000682c,"\x84\x19\x92\x0d\x8f\x36\x02\x60\x18\x85\xbd\xa3\x0f\x76\x0e\x04\xe3\xaf\x0a\xdb",20))
printf("strip: 8419920d8f360260, Pass\n");
else
printf("strip: 8419920d8f360260, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006978))=0x016a0a02;
*((unsigned int *)((unsigned long)context_ptr+0x00006978+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006978+4*2))=0x02020080;
*((unsigned int *)((unsigned long)context_ptr+0x00006978+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x000065c0))=0xc2769ba7;
*((unsigned int *)((unsigned long)context_ptr+0x000065c0+4*1))=0x4871f85e;
*((unsigned int *)((unsigned long)context_ptr+0x000065c0+4*2))=0x0eded7a4;
*((unsigned int *)((unsigned long)context_ptr+0x000065c0+4*3))=0xecf7be6e;
*((unsigned int *)((unsigned long)context_ptr+0x000065c0+4*4))=0xa0bd9905;
*((unsigned int *)((unsigned long)context_ptr+0x000065c0+4*5))=0xbcad0e9d;
*((unsigned int *)((unsigned long)context_ptr+0x000065c0+4*6))=0x7960c646;
*((unsigned int *)((unsigned long)context_ptr+0x000065c0+4*7))=0x941aa03b;
*((unsigned int *)((unsigned long)context_ptr+0x000065c0+4*8))=0x8a933b55;
*((unsigned int *)((unsigned long)context_ptr+0x000065c0+4*9))=0xdab77b3b;
*((unsigned int *)((unsigned long)context_ptr+0x000065c0+4*10))=0x506f0012;
*((unsigned int *)((unsigned long)context_ptr+0x000065c0+4*11))=0xf3d95ae6;
*((unsigned int *)((unsigned long)context_ptr+0x000065c0+4*12))=0x192d4ce4;
*((unsigned int *)((unsigned long)context_ptr+0x000065c0+4*13))=0x408be758;
*((unsigned int *)((unsigned long)context_ptr+0x000065c0+4*14))=0xea550bbe;
*((unsigned int *)((unsigned long)context_ptr+0x000065c0+4*15))=0x94a1c243;
*((unsigned int *)((unsigned long)context_ptr+0x000065c0+4*16))=0x575195c8;
*((unsigned int *)((unsigned long)context_ptr+0x000065c0+4*17))=0x3607c31e;
*((unsigned int *)((unsigned long)context_ptr+0x000065c0+4*18))=0x95eba041;
*((unsigned int *)((unsigned long)context_ptr+0x000065c0+4*19))=0x6ed1e808;
*((unsigned int *)((unsigned long)context_ptr+0x000065c0+4*20))=0x957ff50d;
*((unsigned int *)((unsigned long)context_ptr+0x000065c0+4*21))=0x2008dcab;
*((unsigned int *)((unsigned long)context_ptr+0x000065c0+4*22))=0x9e9eb4d2;
*((unsigned int *)((unsigned long)context_ptr+0x000065c0+4*23))=0xfe253220;
*((unsigned int *)((unsigned long)context_ptr+0x000065c0+4*24))=0x4a08f450;
*((unsigned int *)((unsigned long)context_ptr+0x000065c0+4*25))=0x65546477;
*((unsigned int *)((unsigned long)context_ptr+0x000065c0+4*26))=0xc33ed15c;
*((unsigned int *)((unsigned long)context_ptr+0x000065c0+4*27))=0x144413db;
*((unsigned int *)((unsigned long)context_ptr+0x000065c0+4*28))=0x966a079f;
*((unsigned int *)((unsigned long)context_ptr+0x000065c0+4*29))=0x3eb1dd03;
*((unsigned int *)((unsigned long)context_ptr+0x000065c0+4*30))=0xf05a1a4f;
*((unsigned int *)((unsigned long)context_ptr+0x000065c0+4*31))=0xf8af3cc5;
*((unsigned int *)((unsigned long)context_ptr+0x00003be8))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003be8+4*1))=0x00006988;
*((unsigned int *)((unsigned long)context_ptr+0x00003be8+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003be8+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003be8+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003be8+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000be8))=0x04c00080;
*((unsigned int *)((unsigned long)context_ptr+0x00000be8+4*1))=0x000065c0;
*((unsigned int *)((unsigned long)context_ptr+0x00000be8+4*2))=0x00006978;
*((unsigned int *)((unsigned long)context_ptr+0x00000be8+4*3))=0x02220080;
*((unsigned int *)((unsigned long)context_ptr+0x00000be8+4*4))=0x089ff509;
*((unsigned int *)((unsigned long)context_ptr+0x00000be8+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000002ac&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000068b4,"\x4d\xe1\x0b\x85\x7b\x75\x0a\xa7\x75\x7a\x97\xd4\x27\x8e\xb8\x42\xfc\xd0\x0c\x12",20))
printf("strip: 4de10b857b750aa7, Pass\n");
else
printf("strip: 4de10b857b750aa7, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x0000699c))=0x016a0a02;
*((unsigned int *)((unsigned long)context_ptr+0x0000699c+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x0000699c+4*2))=0x02020081;
*((unsigned int *)((unsigned long)context_ptr+0x0000699c+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x00006640))=0x000824df;
*((unsigned int *)((unsigned long)context_ptr+0x00006640+4*1))=0x5b8d2cfa;
*((unsigned int *)((unsigned long)context_ptr+0x00006640+4*2))=0x7625bd31;
*((unsigned int *)((unsigned long)context_ptr+0x00006640+4*3))=0x446729f1;
*((unsigned int *)((unsigned long)context_ptr+0x00006640+4*4))=0x82d8bbaf;
*((unsigned int *)((unsigned long)context_ptr+0x00006640+4*5))=0x56f861cf;
*((unsigned int *)((unsigned long)context_ptr+0x00006640+4*6))=0x57900310;
*((unsigned int *)((unsigned long)context_ptr+0x00006640+4*7))=0x5c937160;
*((unsigned int *)((unsigned long)context_ptr+0x00006640+4*8))=0x0ed1407a;
*((unsigned int *)((unsigned long)context_ptr+0x00006640+4*9))=0x492d7fe1;
*((unsigned int *)((unsigned long)context_ptr+0x00006640+4*10))=0x9ef726a6;
*((unsigned int *)((unsigned long)context_ptr+0x00006640+4*11))=0x1fe1e4dd;
*((unsigned int *)((unsigned long)context_ptr+0x00006640+4*12))=0x52b7dca0;
*((unsigned int *)((unsigned long)context_ptr+0x00006640+4*13))=0xeb9a019b;
*((unsigned int *)((unsigned long)context_ptr+0x00006640+4*14))=0x820fc664;
*((unsigned int *)((unsigned long)context_ptr+0x00006640+4*15))=0x21351906;
*((unsigned int *)((unsigned long)context_ptr+0x00006640+4*16))=0x16b60c08;
*((unsigned int *)((unsigned long)context_ptr+0x00006640+4*17))=0x287938a4;
*((unsigned int *)((unsigned long)context_ptr+0x00006640+4*18))=0x276f4bb7;
*((unsigned int *)((unsigned long)context_ptr+0x00006640+4*19))=0x0d008b05;
*((unsigned int *)((unsigned long)context_ptr+0x00006640+4*20))=0x788cff42;
*((unsigned int *)((unsigned long)context_ptr+0x00006640+4*21))=0xb1749929;
*((unsigned int *)((unsigned long)context_ptr+0x00006640+4*22))=0x07772a98;
*((unsigned int *)((unsigned long)context_ptr+0x00006640+4*23))=0x9ec21ca3;
*((unsigned int *)((unsigned long)context_ptr+0x00006640+4*24))=0x30c0f24b;
*((unsigned int *)((unsigned long)context_ptr+0x00006640+4*25))=0x2c43cc47;
*((unsigned int *)((unsigned long)context_ptr+0x00006640+4*26))=0x2e383343;
*((unsigned int *)((unsigned long)context_ptr+0x00006640+4*27))=0x5574f32f;
*((unsigned int *)((unsigned long)context_ptr+0x00006640+4*28))=0x973bce8d;
*((unsigned int *)((unsigned long)context_ptr+0x00006640+4*29))=0x99836fd6;
*((unsigned int *)((unsigned long)context_ptr+0x00006640+4*30))=0x9ecd5742;
*((unsigned int *)((unsigned long)context_ptr+0x00006640+4*31))=0x9d4e3ead;
*((unsigned int *)((unsigned long)context_ptr+0x00006640+4*32))=0x00000030;
*((unsigned int *)((unsigned long)context_ptr+0x00003c00))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003c00+4*1))=0x000066c4;
*((unsigned int *)((unsigned long)context_ptr+0x00003c00+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003c00+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003c00+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003c00+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000c00))=0x04c00081;
*((unsigned int *)((unsigned long)context_ptr+0x00000c00+4*1))=0x00006640;
*((unsigned int *)((unsigned long)context_ptr+0x00000c00+4*2))=0x0000699c;
*((unsigned int *)((unsigned long)context_ptr+0x00000c00+4*3))=0x02220081;
*((unsigned int *)((unsigned long)context_ptr+0x00000c00+4*4))=0x01e7580f;
*((unsigned int *)((unsigned long)context_ptr+0x00000c00+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000002b2&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000062fc,"\x50\x43\x74\x5e\xec\xbd\x9c\x1d\x58\x42\x85\x0a\x4f\x3b\x8c\xdc\x39\x7e\xcb\xf6",20))
printf("strip: 5043745eecbd9c1d, Pass\n");
else
printf("strip: 5043745eecbd9c1d, Failed\n");
writel(0x000002b8&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006320,"\x39\x07\x95\xee\x4c\x1d\x6b\x93\x73\xad\x13\x89\x26\x20\xe5\x6b\x85\xae\x60\x91",20))
printf("strip: 390795ee4c1d6b93, Pass\n");
else
printf("strip: 390795ee4c1d6b93, Failed\n");
writel(0x000002be&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000064ac,"\x4a\x2b\xa4\x83\x45\x0c\x16\xa1\x9c\x02\x50\x56\xc5\xd1\x95\x13\x61\xf7\x64\xa7",20))
printf("strip: 4a2ba483450c16a1, Pass\n");
else
printf("strip: 4a2ba483450c16a1, Failed\n");
writel(0x000002c4&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006474,"\x55\x33\xf0\xce\x8a\xeb\x7b\x24\xa7\xe7\xf4\x62\xc0\x53\x76\xe3\x06\xe8\x2c\xed",20))
printf("strip: 5533f0ce8aeb7b24, Pass\n");
else
printf("strip: 5533f0ce8aeb7b24, Failed\n");
writel(0x000002ca&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000061b8,"\xe9\x0e\xac\x30\xa7\x67\x17\xae\x17\x09\xfb\xbd\xb6\xfb\xb2\x6f\x39\x65\x23\x75",20))
printf("strip: e90eac30a76717ae, Pass\n");
else
printf("strip: e90eac30a76717ae, Failed\n");
writel(0x000002d0&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000061dc,"\xe6\xd1\x04\xfe\xde\x4f\x61\x3e\xa7\x0c\x96\x4c\x5a\xf3\x83\xd7\x3d\x20\x51\x4c",20))
printf("strip: e6d104fede4f613e, Pass\n");
else
printf("strip: e6d104fede4f613e, Failed\n");
writel(0x000002d6&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000061f0,"\x97\x89\x74\xb7\x28\xea\xec\x39\xb6\xb3\x71\x83\x57\x64\xbf\x76\x21\x4b\x6d\xbb",20))
printf("strip: 978974b728eaec39, Pass\n");
else
printf("strip: 978974b728eaec39, Failed\n");
writel(0x000002dc&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006060,"\x26\xd8\xbf\x98\xac\xea\x52\x30\x88\x9f\x48\xa6\xea\xd1\xd4\xa9\x0f\x91\xe9\x82",20))
printf("strip: 26d8bf98acea5230, Pass\n");
else
printf("strip: 26d8bf98acea5230, Failed\n");
writel(0x000002e2&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006084,"\x92\xd8\xe3\xca\x28\x33\xf0\xe0\xee\x0a\x48\x95\x48\x3d\xd7\xb0\xd7\x30\x1c\xb4",20))
printf("strip: 92d8e3ca2833f0e0, Pass\n");
else
printf("strip: 92d8e3ca2833f0e0, Failed\n");
writel(0x000002e8&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006488,"\x22\x05\x14\x70\x47\xff\x7c\x00\x2c\x55\xc2\xf4\xfd\x6e\xac\xc4\xc3\xf0\x5a\x74",20))
printf("strip: 2205147047ff7c00, Pass\n");
else
printf("strip: 2205147047ff7c00, Failed\n");
writel(0x000002ee&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000063b0,"\x02\x10\x93\x84\x5e\xf3\xd3\x79\xa8\x8c\xea\xc2\x3f\x5d\xac\x84\xb5\x7f\x61\x62",20))
printf("strip: 021093845ef3d379, Pass\n");
else
printf("strip: 021093845ef3d379, Failed\n");
writel(0x000002f4&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006950,"\xbd\xbb\x00\xe4\x14\x30\xea\xc6\x6b\xf6\xa0\x4b\x46\xb9\xed\xf6\x32\xd3\x6b\x2f",20))
printf("strip: bdbb00e41430eac6, Pass\n");
else
printf("strip: bdbb00e41430eac6, Failed\n");
writel(0x000002fa&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006964,"\x02\x4d\x52\x3d\x66\xd2\x40\xa3\x6d\x02\x6f\x9a\x2d\x52\x05\x41\x4f\x66\x1d\xdb",20))
printf("strip: 024d523d66d240a3, Pass\n");
else
printf("strip: 024d523d66d240a3, Failed\n");
writel(0x00000300&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
writel(0x00000c00&0xffffffff,ivp_cae_base_addr+0x00000830);
if(!memcmp((unsigned char *)context_ptr+0x00006988,"\xb0\xe4\x5c\x0b\xa5\x48\x3e\x68\x8c\x35\x5c\xcf\xdd\x49\xd8\x75\x74\xf5\x25\x89",20))
printf("strip: b0e45c0ba5483e68, Pass\n");
else
printf("strip: b0e45c0ba5483e68, Failed\n");
writel(0x00000006&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000066c4,"\xb5\xa6\x6a\x11\xe2\x6f\x2f\xaf\x1d\x4e\x17\xcd\x91\x64\x9c\x7e\x1e\x7b\x00\x15",20))
printf("strip: b5a66a11e26f2faf, Pass\n");
else
printf("strip: b5a66a11e26f2faf, Failed\n");
}

#include <common.h>
#include <malloc.h>

extern volatile unsigned int ivp_cae_base_addr;

void test_sha224(void)
{
unsigned int *context_ptr=(unsigned int *)0x14000000;
printf("test_sha224\n");
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
*((unsigned int *)((unsigned long)context_ptr+0x00006000))=0x020a0002;
*((unsigned int *)((unsigned long)context_ptr+0x00006000+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006008))=0x020a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006008+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006008+4*2))=0x02020001;
*((unsigned int *)((unsigned long)context_ptr+0x00006008+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x00006018))=0x00000095;
*((unsigned int *)((unsigned long)context_ptr+0x00003000))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003000+4*1))=0x0000601c;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000000+4*1))=0x00006018;
*((unsigned int *)((unsigned long)context_ptr+0x00000000+4*2))=0x00006008;
*((unsigned int *)((unsigned long)context_ptr+0x00000000+4*3))=0x02220001;
*((unsigned int *)((unsigned long)context_ptr+0x00000000+4*4))=0x010fce97;
*((unsigned int *)((unsigned long)context_ptr+0x00000000+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x00006038))=0x020a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006038+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006038+4*2))=0x02020002;
*((unsigned int *)((unsigned long)context_ptr+0x00006038+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x00006048))=0x0000d996;
*((unsigned int *)((unsigned long)context_ptr+0x00003018))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003018+4*1))=0x0000604c;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000018+4*1))=0x00006048;
*((unsigned int *)((unsigned long)context_ptr+0x00000018+4*2))=0x00006038;
*((unsigned int *)((unsigned long)context_ptr+0x00000018+4*3))=0x02220002;
*((unsigned int *)((unsigned long)context_ptr+0x00000018+4*4))=0x0000fc63;
*((unsigned int *)((unsigned long)context_ptr+0x00000018+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x00006068))=0x020a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006068+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006068+4*2))=0x02020003;
*((unsigned int *)((unsigned long)context_ptr+0x00006068+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x00006078))=0x001aa19e;
*((unsigned int *)((unsigned long)context_ptr+0x00003030))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003030+4*1))=0x0000607c;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000030+4*1))=0x00006078;
*((unsigned int *)((unsigned long)context_ptr+0x00000030+4*2))=0x00006068;
*((unsigned int *)((unsigned long)context_ptr+0x00000030+4*3))=0x02220003;
*((unsigned int *)((unsigned long)context_ptr+0x00000030+4*4))=0x062276cb;
*((unsigned int *)((unsigned long)context_ptr+0x00000030+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x00006098))=0x020a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006098+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006098+4*2))=0x02020004;
*((unsigned int *)((unsigned long)context_ptr+0x00006098+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x000060a8))=0x3792aaf1;
*((unsigned int *)((unsigned long)context_ptr+0x00003048))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003048+4*1))=0x000060ac;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000048+4*1))=0x000060a8;
*((unsigned int *)((unsigned long)context_ptr+0x00000048+4*2))=0x00006098;
*((unsigned int *)((unsigned long)context_ptr+0x00000048+4*3))=0x02220004;
*((unsigned int *)((unsigned long)context_ptr+0x00000048+4*4))=0x0e38690e;
*((unsigned int *)((unsigned long)context_ptr+0x00000048+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x000060c8))=0x020a0012;
*((unsigned int *)((unsigned long)context_ptr+0x000060c8+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000060c8+4*2))=0x02020005;
*((unsigned int *)((unsigned long)context_ptr+0x000060c8+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x000060d8))=0x011ff0ac;
*((unsigned int *)((unsigned long)context_ptr+0x000060d8+4*1))=0x0000005e;
*((unsigned int *)((unsigned long)context_ptr+0x00003060))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003060+4*1))=0x000060e0;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000060+4*1))=0x000060d8;
*((unsigned int *)((unsigned long)context_ptr+0x00000060+4*2))=0x000060c8;
*((unsigned int *)((unsigned long)context_ptr+0x00000060+4*3))=0x02220005;
*((unsigned int *)((unsigned long)context_ptr+0x00000060+4*4))=0x0dbf2eeb;
*((unsigned int *)((unsigned long)context_ptr+0x00000060+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x000060fc))=0x020a0012;
*((unsigned int *)((unsigned long)context_ptr+0x000060fc+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000060fc+4*2))=0x02020006;
*((unsigned int *)((unsigned long)context_ptr+0x000060fc+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x0000610c))=0x15a36c24;
*((unsigned int *)((unsigned long)context_ptr+0x0000610c+4*1))=0x00005e71;
*((unsigned int *)((unsigned long)context_ptr+0x00003078))=0x04c0001c;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000078+4*4))=0x0689bba5;
*((unsigned int *)((unsigned long)context_ptr+0x00000078+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x00006130))=0x020a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006130+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006130+4*2))=0x02020007;
*((unsigned int *)((unsigned long)context_ptr+0x00006130+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x00006140))=0x3bc2ad78;
*((unsigned int *)((unsigned long)context_ptr+0x00006140+4*1))=0x00fb47c3;
*((unsigned int *)((unsigned long)context_ptr+0x00003090))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003090+4*1))=0x00006148;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000090+4*1))=0x00006140;
*((unsigned int *)((unsigned long)context_ptr+0x00000090+4*2))=0x00006130;
*((unsigned int *)((unsigned long)context_ptr+0x00000090+4*3))=0x02220007;
*((unsigned int *)((unsigned long)context_ptr+0x00000090+4*4))=0x00a614bd;
*((unsigned int *)((unsigned long)context_ptr+0x00000090+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x00006164))=0x020a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006164+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006164+4*2))=0x02020008;
*((unsigned int *)((unsigned long)context_ptr+0x00006164+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x00006174))=0x5aab2397;
*((unsigned int *)((unsigned long)context_ptr+0x00006174+4*1))=0xb17a6a79;
*((unsigned int *)((unsigned long)context_ptr+0x000030a8))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x000030a8+4*1))=0x0000617c;
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
*((unsigned int *)((unsigned long)context_ptr+0x000000a8+4*1))=0x00006174;
*((unsigned int *)((unsigned long)context_ptr+0x000000a8+4*2))=0x00006164;
*((unsigned int *)((unsigned long)context_ptr+0x000000a8+4*3))=0x02220008;
*((unsigned int *)((unsigned long)context_ptr+0x000000a8+4*4))=0x00f6ab74;
*((unsigned int *)((unsigned long)context_ptr+0x000000a8+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x00006198))=0x020a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006198+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006198+4*2))=0x02020009;
*((unsigned int *)((unsigned long)context_ptr+0x00006198+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x000061a8))=0xce63ca71;
*((unsigned int *)((unsigned long)context_ptr+0x000061a8+4*1))=0xf0323863;
*((unsigned int *)((unsigned long)context_ptr+0x000061a8+4*2))=0x00000096;
*((unsigned int *)((unsigned long)context_ptr+0x000030c0))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x000030c0+4*1))=0x000061b4;
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
*((unsigned int *)((unsigned long)context_ptr+0x000000c0+4*1))=0x000061a8;
*((unsigned int *)((unsigned long)context_ptr+0x000000c0+4*2))=0x00006198;
*((unsigned int *)((unsigned long)context_ptr+0x000000c0+4*3))=0x02220009;
*((unsigned int *)((unsigned long)context_ptr+0x000000c0+4*4))=0x03be9577;
*((unsigned int *)((unsigned long)context_ptr+0x000000c0+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x000061d0))=0x020a0012;
*((unsigned int *)((unsigned long)context_ptr+0x000061d0+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000061d0+4*2))=0x0202000a;
*((unsigned int *)((unsigned long)context_ptr+0x000061d0+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x000061e0))=0x7452cbe2;
*((unsigned int *)((unsigned long)context_ptr+0x000061e0+4*1))=0x5e0b0753;
*((unsigned int *)((unsigned long)context_ptr+0x000061e0+4*2))=0x00008635;
*((unsigned int *)((unsigned long)context_ptr+0x000030d8))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x000030d8+4*1))=0x000061ec;
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
*((unsigned int *)((unsigned long)context_ptr+0x000000d8+4*1))=0x000061e0;
*((unsigned int *)((unsigned long)context_ptr+0x000000d8+4*2))=0x000061d0;
*((unsigned int *)((unsigned long)context_ptr+0x000000d8+4*3))=0x0222000a;
*((unsigned int *)((unsigned long)context_ptr+0x000000d8+4*4))=0x0ac33f64;
*((unsigned int *)((unsigned long)context_ptr+0x000000d8+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x00006208))=0x020a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006208+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006208+4*2))=0x0202000b;
*((unsigned int *)((unsigned long)context_ptr+0x00006208+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x00006218))=0x899a714b;
*((unsigned int *)((unsigned long)context_ptr+0x00006218+4*1))=0xc81e3b42;
*((unsigned int *)((unsigned long)context_ptr+0x00006218+4*2))=0x003fbb19;
*((unsigned int *)((unsigned long)context_ptr+0x000030f0))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x000030f0+4*1))=0x00006224;
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
*((unsigned int *)((unsigned long)context_ptr+0x000000f0+4*1))=0x00006218;
*((unsigned int *)((unsigned long)context_ptr+0x000000f0+4*2))=0x00006208;
*((unsigned int *)((unsigned long)context_ptr+0x000000f0+4*3))=0x0222000b;
*((unsigned int *)((unsigned long)context_ptr+0x000000f0+4*4))=0x0a8dce87;
*((unsigned int *)((unsigned long)context_ptr+0x000000f0+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x00006240))=0x020a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006240+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006240+4*2))=0x0202000c;
*((unsigned int *)((unsigned long)context_ptr+0x00006240+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x00006250))=0xe6a1975a;
*((unsigned int *)((unsigned long)context_ptr+0x00006250+4*1))=0x5b86d51b;
*((unsigned int *)((unsigned long)context_ptr+0x00006250+4*2))=0xa7380374;
*((unsigned int *)((unsigned long)context_ptr+0x00003108))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003108+4*1))=0x0000625c;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000108+4*1))=0x00006250;
*((unsigned int *)((unsigned long)context_ptr+0x00000108+4*2))=0x00006240;
*((unsigned int *)((unsigned long)context_ptr+0x00000108+4*3))=0x0222000c;
*((unsigned int *)((unsigned long)context_ptr+0x00000108+4*4))=0x0f40d2a2;
*((unsigned int *)((unsigned long)context_ptr+0x00000108+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x00006278))=0x020a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006278+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006278+4*2))=0x0202000d;
*((unsigned int *)((unsigned long)context_ptr+0x00006278+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x00006288))=0x6861bffc;
*((unsigned int *)((unsigned long)context_ptr+0x00006288+4*1))=0xafbc8843;
*((unsigned int *)((unsigned long)context_ptr+0x00006288+4*2))=0x68eb0a76;
*((unsigned int *)((unsigned long)context_ptr+0x00006288+4*3))=0x00000063;
*((unsigned int *)((unsigned long)context_ptr+0x00003120))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003120+4*1))=0x00006298;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000120+4*1))=0x00006288;
*((unsigned int *)((unsigned long)context_ptr+0x00000120+4*2))=0x00006278;
*((unsigned int *)((unsigned long)context_ptr+0x00000120+4*3))=0x0222000d;
*((unsigned int *)((unsigned long)context_ptr+0x00000120+4*4))=0x0de6d2d6;
*((unsigned int *)((unsigned long)context_ptr+0x00000120+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x000062b4))=0x020a0012;
*((unsigned int *)((unsigned long)context_ptr+0x000062b4+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000062b4+4*2))=0x0202000e;
*((unsigned int *)((unsigned long)context_ptr+0x000062b4+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x000062c4))=0x74af4392;
*((unsigned int *)((unsigned long)context_ptr+0x000062c4+4*1))=0x057e67b8;
*((unsigned int *)((unsigned long)context_ptr+0x000062c4+4*2))=0x94ae08bd;
*((unsigned int *)((unsigned long)context_ptr+0x000062c4+4*3))=0x00004ac6;
*((unsigned int *)((unsigned long)context_ptr+0x00003138))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003138+4*1))=0x000062d4;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000138+4*1))=0x000062c4;
*((unsigned int *)((unsigned long)context_ptr+0x00000138+4*2))=0x000062b4;
*((unsigned int *)((unsigned long)context_ptr+0x00000138+4*3))=0x0222000e;
*((unsigned int *)((unsigned long)context_ptr+0x00000138+4*4))=0x0877e5ea;
*((unsigned int *)((unsigned long)context_ptr+0x00000138+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x000062f0))=0x020a0012;
*((unsigned int *)((unsigned long)context_ptr+0x000062f0+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000062f0+4*2))=0x0202000f;
*((unsigned int *)((unsigned long)context_ptr+0x000062f0+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x00006300))=0x1c28a82b;
*((unsigned int *)((unsigned long)context_ptr+0x00006300+4*1))=0xc19acb81;
*((unsigned int *)((unsigned long)context_ptr+0x00006300+4*2))=0xfd6d4844;
*((unsigned int *)((unsigned long)context_ptr+0x00006300+4*3))=0x0089f2b7;
*((unsigned int *)((unsigned long)context_ptr+0x00003150))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003150+4*1))=0x00006310;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000150+4*1))=0x00006300;
*((unsigned int *)((unsigned long)context_ptr+0x00000150+4*2))=0x000062f0;
*((unsigned int *)((unsigned long)context_ptr+0x00000150+4*3))=0x0222000f;
*((unsigned int *)((unsigned long)context_ptr+0x00000150+4*4))=0x030a3125;
*((unsigned int *)((unsigned long)context_ptr+0x00000150+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000006&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x0000601c,"\xee\x0f\x9e\xc0\x87\x25\xd7\xbe\x58\x56\xe3\x14\x50\xf9\x99\x25\x39\x90\x23\x6f\x38\xc5\x85\x0a\xfe\x14\x09\x4a",28))
printf("strip: ee0f9ec08725d7be, Pass\n");
else
printf("strip: ee0f9ec08725d7be, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006008))=0x020a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006008+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006008+4*2))=0x02020010;
*((unsigned int *)((unsigned long)context_ptr+0x00006008+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x00006018))=0x07179cc6;
*((unsigned int *)((unsigned long)context_ptr+0x00006018+4*1))=0x62c34002;
*((unsigned int *)((unsigned long)context_ptr+0x00006018+4*2))=0xe163a0c6;
*((unsigned int *)((unsigned long)context_ptr+0x00006018+4*3))=0x20d47709;
*((unsigned int *)((unsigned long)context_ptr+0x00003168))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003168+4*1))=0x0000632c;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000168+4*1))=0x00006018;
*((unsigned int *)((unsigned long)context_ptr+0x00000168+4*2))=0x00006008;
*((unsigned int *)((unsigned long)context_ptr+0x00000168+4*3))=0x02220010;
*((unsigned int *)((unsigned long)context_ptr+0x00000168+4*4))=0x006389bc;
*((unsigned int *)((unsigned long)context_ptr+0x00000168+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000000c&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x0000604c,"\x0d\xb2\x6d\xfc\xce\xec\xdb\xda\x42\x2e\xd7\x92\x84\xb0\xe2\x6b\x7e\x0c\x54\x12\x27\x2e\x90\xbe\xc6\xff\x29\xef",28))
printf("strip: 0db26dfcceecdbda, Pass\n");
else
printf("strip: 0db26dfcceecdbda, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006028))=0x020a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006028+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006028+4*2))=0x02020011;
*((unsigned int *)((unsigned long)context_ptr+0x00006028+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x00006038))=0x27ffef42;
*((unsigned int *)((unsigned long)context_ptr+0x00006038+4*1))=0x95098de6;
*((unsigned int *)((unsigned long)context_ptr+0x00006038+4*2))=0xd1c108a4;
*((unsigned int *)((unsigned long)context_ptr+0x00006038+4*3))=0x3d74a512;
*((unsigned int *)((unsigned long)context_ptr+0x00006038+4*4))=0x00000075;
*((unsigned int *)((unsigned long)context_ptr+0x00003180))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003180+4*1))=0x0000604c;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000180+4*1))=0x00006038;
*((unsigned int *)((unsigned long)context_ptr+0x00000180+4*2))=0x00006028;
*((unsigned int *)((unsigned long)context_ptr+0x00000180+4*3))=0x02220011;
*((unsigned int *)((unsigned long)context_ptr+0x00000180+4*4))=0x0a7bbaa5;
*((unsigned int *)((unsigned long)context_ptr+0x00000180+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000012&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x0000607c,"\x08\x79\x3c\x40\x38\x85\x23\xba\x83\x07\xa4\x3c\x42\x8e\x76\xd0\x2f\xd6\x5e\xf9\xc0\x57\x04\x14\x6e\x96\x13\xe0",28))
printf("strip: 08793c40388523ba, Pass\n");
else
printf("strip: 08793c40388523ba, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006068))=0x020a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006068+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006068+4*2))=0x02020012;
*((unsigned int *)((unsigned long)context_ptr+0x00006068+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x00006078))=0xa79d2d59;
*((unsigned int *)((unsigned long)context_ptr+0x00006078+4*1))=0xdf8d7403;
*((unsigned int *)((unsigned long)context_ptr+0x00006078+4*2))=0xdc0d147e;
*((unsigned int *)((unsigned long)context_ptr+0x00006078+4*3))=0xa543dbca;
*((unsigned int *)((unsigned long)context_ptr+0x00006078+4*4))=0x0000d318;
*((unsigned int *)((unsigned long)context_ptr+0x00003198))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003198+4*1))=0x00006348;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000198+4*1))=0x00006078;
*((unsigned int *)((unsigned long)context_ptr+0x00000198+4*2))=0x00006068;
*((unsigned int *)((unsigned long)context_ptr+0x00000198+4*3))=0x02220012;
*((unsigned int *)((unsigned long)context_ptr+0x00000198+4*4))=0x078ac871;
*((unsigned int *)((unsigned long)context_ptr+0x00000198+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000060ac,"\x8b\x16\xcd\xf6\x9b\x21\x7c\x38\x54\x21\x0a\x12\xc9\x56\x39\x5d\xe2\x66\xb2\x7a\xc2\x26\xb8\xb7\x7d\x03\x92\xde",28))
printf("strip: 8b16cdf69b217c38, Pass\n");
else
printf("strip: 8b16cdf69b217c38, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x0000608c))=0x020a0012;
*((unsigned int *)((unsigned long)context_ptr+0x0000608c+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x0000608c+4*2))=0x02020013;
*((unsigned int *)((unsigned long)context_ptr+0x0000608c+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x0000609c))=0x55e96f06;
*((unsigned int *)((unsigned long)context_ptr+0x0000609c+4*1))=0x8882233f;
*((unsigned int *)((unsigned long)context_ptr+0x0000609c+4*2))=0xf7a86812;
*((unsigned int *)((unsigned long)context_ptr+0x0000609c+4*3))=0x39786f6e;
*((unsigned int *)((unsigned long)context_ptr+0x0000609c+4*4))=0x0065a565;
*((unsigned int *)((unsigned long)context_ptr+0x000031b0))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x000031b0+4*1))=0x00006364;
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
*((unsigned int *)((unsigned long)context_ptr+0x000001b0+4*1))=0x0000609c;
*((unsigned int *)((unsigned long)context_ptr+0x000001b0+4*2))=0x0000608c;
*((unsigned int *)((unsigned long)context_ptr+0x000001b0+4*3))=0x02220013;
*((unsigned int *)((unsigned long)context_ptr+0x000001b0+4*4))=0x0ff7acd7;
*((unsigned int *)((unsigned long)context_ptr+0x000001b0+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000001e&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000060e0,"\xd2\xa4\xbe\x71\xa7\xda\x53\xe0\xd1\x7a\x82\x26\x9d\x9c\x5b\xaa\xd7\x1b\xac\xbc\x97\xc7\xf6\x67\xc7\x9d\x67\xdb",28))
printf("strip: d2a4be71a7da53e0, Pass\n");
else
printf("strip: d2a4be71a7da53e0, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000060b0))=0x020a0012;
*((unsigned int *)((unsigned long)context_ptr+0x000060b0+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000060b0+4*2))=0x02020014;
*((unsigned int *)((unsigned long)context_ptr+0x000060b0+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x000060c0))=0x656e2a9c;
*((unsigned int *)((unsigned long)context_ptr+0x000060c0+4*1))=0xc7aeb513;
*((unsigned int *)((unsigned long)context_ptr+0x000060c0+4*2))=0x352b8d8b;
*((unsigned int *)((unsigned long)context_ptr+0x000060c0+4*3))=0x5bd1863a;
*((unsigned int *)((unsigned long)context_ptr+0x000060c0+4*4))=0x55b7bce1;
*((unsigned int *)((unsigned long)context_ptr+0x000031c8))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x000031c8+4*1))=0x000060d4;
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
*((unsigned int *)((unsigned long)context_ptr+0x000001c8+4*1))=0x000060c0;
*((unsigned int *)((unsigned long)context_ptr+0x000001c8+4*2))=0x000060b0;
*((unsigned int *)((unsigned long)context_ptr+0x000001c8+4*3))=0x02220014;
*((unsigned int *)((unsigned long)context_ptr+0x000001c8+4*4))=0x0dac7c32;
*((unsigned int *)((unsigned long)context_ptr+0x000001c8+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000024&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006114,"\x25\xce\x8f\xca\x34\xed\x0b\x9b\xd4\x5a\x09\x69\x55\xd6\x00\xd8\x3f\x04\xca\xbc\x62\xbf\xca\x31\xd5\x5d\x8b\xf7",28))
printf("strip: 25ce8fca34ed0b9b, Pass\n");
else
printf("strip: 25ce8fca34ed0b9b, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000060f0))=0x020a0012;
*((unsigned int *)((unsigned long)context_ptr+0x000060f0+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000060f0+4*2))=0x02020015;
*((unsigned int *)((unsigned long)context_ptr+0x000060f0+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x00006100))=0xebdb13d3;
*((unsigned int *)((unsigned long)context_ptr+0x00006100+4*1))=0xe0d9d32b;
*((unsigned int *)((unsigned long)context_ptr+0x00006100+4*2))=0xb5359b84;
*((unsigned int *)((unsigned long)context_ptr+0x00006100+4*3))=0x63220567;
*((unsigned int *)((unsigned long)context_ptr+0x00006100+4*4))=0xedea90e2;
*((unsigned int *)((unsigned long)context_ptr+0x00006100+4*5))=0x00000016;
*((unsigned int *)((unsigned long)context_ptr+0x000031e0))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x000031e0+4*1))=0x00006380;
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
*((unsigned int *)((unsigned long)context_ptr+0x000001e0+4*1))=0x00006100;
*((unsigned int *)((unsigned long)context_ptr+0x000001e0+4*2))=0x000060f0;
*((unsigned int *)((unsigned long)context_ptr+0x000001e0+4*3))=0x02220015;
*((unsigned int *)((unsigned long)context_ptr+0x000001e0+4*4))=0x081bd533;
*((unsigned int *)((unsigned long)context_ptr+0x000001e0+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000002a&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006148,"\x0e\x05\x09\xc8\xf8\xdf\xfc\x45\xb1\xaf\x57\x1e\xac\xfe\x6f\xfe\xa2\x66\xfe\xab\x22\x18\xe3\x2a\x29\x75\x95\xd3",28))
printf("strip: 0e0509c8f8dffc45, Pass\n");
else
printf("strip: 0e0509c8f8dffc45, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006118))=0x020a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006118+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006118+4*2))=0x02020016;
*((unsigned int *)((unsigned long)context_ptr+0x00006118+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x00006128))=0x615e3992;
*((unsigned int *)((unsigned long)context_ptr+0x00006128+4*1))=0xbeef3bc2;
*((unsigned int *)((unsigned long)context_ptr+0x00006128+4*2))=0x625be17b;
*((unsigned int *)((unsigned long)context_ptr+0x00006128+4*3))=0x8066c721;
*((unsigned int *)((unsigned long)context_ptr+0x00006128+4*4))=0xea5fa778;
*((unsigned int *)((unsigned long)context_ptr+0x00006128+4*5))=0x00005b6e;
*((unsigned int *)((unsigned long)context_ptr+0x000031f8))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x000031f8+4*1))=0x00006140;
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
*((unsigned int *)((unsigned long)context_ptr+0x000001f8+4*1))=0x00006128;
*((unsigned int *)((unsigned long)context_ptr+0x000001f8+4*2))=0x00006118;
*((unsigned int *)((unsigned long)context_ptr+0x000001f8+4*3))=0x02220016;
*((unsigned int *)((unsigned long)context_ptr+0x000001f8+4*4))=0x0fe38f4d;
*((unsigned int *)((unsigned long)context_ptr+0x000001f8+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000030&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x0000617c,"\xbc\x14\x91\xb0\x33\xdd\xdc\x25\x82\x6c\xc6\x39\x2e\xec\xd7\x79\xd2\xfd\x71\xcd\x58\x85\xa2\x87\xb8\xa3\x48\x55",28))
printf("strip: bc1491b033dddc25, Pass\n");
else
printf("strip: bc1491b033dddc25, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x0000615c))=0x020a0012;
*((unsigned int *)((unsigned long)context_ptr+0x0000615c+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x0000615c+4*2))=0x02020017;
*((unsigned int *)((unsigned long)context_ptr+0x0000615c+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x0000616c))=0x61ed3b2d;
*((unsigned int *)((unsigned long)context_ptr+0x0000616c+4*1))=0xc3616fce;
*((unsigned int *)((unsigned long)context_ptr+0x0000616c+4*2))=0xb495449d;
*((unsigned int *)((unsigned long)context_ptr+0x0000616c+4*3))=0x98a4add3;
*((unsigned int *)((unsigned long)context_ptr+0x0000616c+4*4))=0x45b6f117;
*((unsigned int *)((unsigned long)context_ptr+0x0000616c+4*5))=0x00a89eb1;
*((unsigned int *)((unsigned long)context_ptr+0x00003210))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003210+4*1))=0x0000639c;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000210+4*1))=0x0000616c;
*((unsigned int *)((unsigned long)context_ptr+0x00000210+4*2))=0x0000615c;
*((unsigned int *)((unsigned long)context_ptr+0x00000210+4*3))=0x02220017;
*((unsigned int *)((unsigned long)context_ptr+0x00000210+4*4))=0x0a8f78b5;
*((unsigned int *)((unsigned long)context_ptr+0x00000210+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000036&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000061b4,"\xf4\xc2\xdf\x00\xe2\x2c\xfe\x55\xa7\x83\xc6\x07\x42\x4e\x19\x68\xcc\x48\x11\x89\xd5\x33\x6d\x59\xc8\x8e\x72\x38",28))
printf("strip: f4c2df00e22cfe55, Pass\n");
else
printf("strip: f4c2df00e22cfe55, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006184))=0x020a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006184+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006184+4*2))=0x02020018;
*((unsigned int *)((unsigned long)context_ptr+0x00006184+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x00006194))=0xaee3f6cd;
*((unsigned int *)((unsigned long)context_ptr+0x00006194+4*1))=0xec2eb985;
*((unsigned int *)((unsigned long)context_ptr+0x00006194+4*2))=0xa26f98b6;
*((unsigned int *)((unsigned long)context_ptr+0x00006194+4*3))=0x3692e69e;
*((unsigned int *)((unsigned long)context_ptr+0x00006194+4*4))=0xd7e73e70;
*((unsigned int *)((unsigned long)context_ptr+0x00006194+4*5))=0x220b328e;
*((unsigned int *)((unsigned long)context_ptr+0x00003228))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003228+4*1))=0x000061ac;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000228+4*1))=0x00006194;
*((unsigned int *)((unsigned long)context_ptr+0x00000228+4*2))=0x00006184;
*((unsigned int *)((unsigned long)context_ptr+0x00000228+4*3))=0x02220018;
*((unsigned int *)((unsigned long)context_ptr+0x00000228+4*4))=0x03957f09;
*((unsigned int *)((unsigned long)context_ptr+0x00000228+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000003c&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000061ec,"\x8e\x47\xd2\xb3\xdc\xe0\x75\xac\xc2\x10\x34\xfe\xdb\x3a\x7f\x4f\xd6\x7f\x7a\x7f\xaa\xac\xde\x4a\x4b\xdd\x39\x0d",28))
printf("strip: 8e47d2b3dce075ac, Pass\n");
else
printf("strip: 8e47d2b3dce075ac, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000061c8))=0x020a0012;
*((unsigned int *)((unsigned long)context_ptr+0x000061c8+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000061c8+4*2))=0x02020019;
*((unsigned int *)((unsigned long)context_ptr+0x000061c8+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x000061d8))=0x422783dd;
*((unsigned int *)((unsigned long)context_ptr+0x000061d8+4*1))=0x38d64797;
*((unsigned int *)((unsigned long)context_ptr+0x000061d8+4*2))=0xd2568162;
*((unsigned int *)((unsigned long)context_ptr+0x000061d8+4*3))=0xa0271643;
*((unsigned int *)((unsigned long)context_ptr+0x000061d8+4*4))=0x7afe1090;
*((unsigned int *)((unsigned long)context_ptr+0x000061d8+4*5))=0x6f06ba51;
*((unsigned int *)((unsigned long)context_ptr+0x000061d8+4*6))=0x000000aa;
*((unsigned int *)((unsigned long)context_ptr+0x00003240))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003240+4*1))=0x000063b8;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000240+4*1))=0x000061d8;
*((unsigned int *)((unsigned long)context_ptr+0x00000240+4*2))=0x000061c8;
*((unsigned int *)((unsigned long)context_ptr+0x00000240+4*3))=0x02220019;
*((unsigned int *)((unsigned long)context_ptr+0x00000240+4*4))=0x0e299cb3;
*((unsigned int *)((unsigned long)context_ptr+0x00000240+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000042&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006224,"\xb6\xf5\x06\xb8\x8f\x6b\x24\x7a\x34\x5f\x8d\x4a\x07\x39\xb1\x23\x9d\x2a\x18\xc9\xa7\x5c\xea\x2f\xb3\xd0\x3d\x62",28))
printf("strip: b6f506b88f6b247a, Pass\n");
else
printf("strip: b6f506b88f6b247a, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000061f4))=0x020a0012;
*((unsigned int *)((unsigned long)context_ptr+0x000061f4+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000061f4+4*2))=0x0202001a;
*((unsigned int *)((unsigned long)context_ptr+0x000061f4+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x00006204))=0xf3b44ed1;
*((unsigned int *)((unsigned long)context_ptr+0x00006204+4*1))=0x1d4a9c08;
*((unsigned int *)((unsigned long)context_ptr+0x00006204+4*2))=0x5883fab6;
*((unsigned int *)((unsigned long)context_ptr+0x00006204+4*3))=0x68886a72;
*((unsigned int *)((unsigned long)context_ptr+0x00006204+4*4))=0x2cfffa14;
*((unsigned int *)((unsigned long)context_ptr+0x00006204+4*5))=0x08b26f3d;
*((unsigned int *)((unsigned long)context_ptr+0x00006204+4*6))=0x0000a3d5;
*((unsigned int *)((unsigned long)context_ptr+0x00003258))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003258+4*1))=0x00006220;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000258+4*1))=0x00006204;
*((unsigned int *)((unsigned long)context_ptr+0x00000258+4*2))=0x000061f4;
*((unsigned int *)((unsigned long)context_ptr+0x00000258+4*3))=0x0222001a;
*((unsigned int *)((unsigned long)context_ptr+0x00000258+4*4))=0x0a94501b;
*((unsigned int *)((unsigned long)context_ptr+0x00000258+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000048&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x0000625c,"\x72\xe0\x82\x91\xd7\x07\xf1\xd9\x14\xb1\x04\x30\x2e\xc3\x7c\x19\xce\x15\xf5\xaa\x31\x1f\x65\xed\x25\xba\x21\x52",28))
printf("strip: 72e08291d707f1d9, Pass\n");
else
printf("strip: 72e08291d707f1d9, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x0000623c))=0x020a0012;
*((unsigned int *)((unsigned long)context_ptr+0x0000623c+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x0000623c+4*2))=0x0202001b;
*((unsigned int *)((unsigned long)context_ptr+0x0000623c+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x0000624c))=0x2b94e18f;
*((unsigned int *)((unsigned long)context_ptr+0x0000624c+4*1))=0xde4cfc3f;
*((unsigned int *)((unsigned long)context_ptr+0x0000624c+4*2))=0xcab8bdcb;
*((unsigned int *)((unsigned long)context_ptr+0x0000624c+4*3))=0x812a0fd8;
*((unsigned int *)((unsigned long)context_ptr+0x0000624c+4*4))=0x207e8836;
*((unsigned int *)((unsigned long)context_ptr+0x0000624c+4*5))=0x14d30216;
*((unsigned int *)((unsigned long)context_ptr+0x0000624c+4*6))=0x00befbf6;
*((unsigned int *)((unsigned long)context_ptr+0x00003270))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003270+4*1))=0x000063d4;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000270+4*1))=0x0000624c;
*((unsigned int *)((unsigned long)context_ptr+0x00000270+4*2))=0x0000623c;
*((unsigned int *)((unsigned long)context_ptr+0x00000270+4*3))=0x0222001b;
*((unsigned int *)((unsigned long)context_ptr+0x00000270+4*4))=0x069967b5;
*((unsigned int *)((unsigned long)context_ptr+0x00000270+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000004e&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006298,"\x6b\x61\xf8\x02\x3e\x49\xf4\x9d\x30\x80\x13\xfc\x12\x9a\x68\xa2\xc1\xc0\xca\x32\xdc\xf9\x99\xee\xff\x6a\x3f\xfd",28))
printf("strip: 6b61f8023e49f49d, Pass\n");
else
printf("strip: 6b61f8023e49f49d, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006268))=0x020a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006268+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006268+4*2))=0x0202001c;
*((unsigned int *)((unsigned long)context_ptr+0x00006268+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x00006278))=0x6e5779d3;
*((unsigned int *)((unsigned long)context_ptr+0x00006278+4*1))=0xba0da674;
*((unsigned int *)((unsigned long)context_ptr+0x00006278+4*2))=0x331175f7;
*((unsigned int *)((unsigned long)context_ptr+0x00006278+4*3))=0x00cb411a;
*((unsigned int *)((unsigned long)context_ptr+0x00006278+4*4))=0x2c2ff0df;
*((unsigned int *)((unsigned long)context_ptr+0x00006278+4*5))=0x02cf5cf7;
*((unsigned int *)((unsigned long)context_ptr+0x00006278+4*6))=0xed9b04fd;
*((unsigned int *)((unsigned long)context_ptr+0x00003288))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003288+4*1))=0x00006294;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000288+4*1))=0x00006278;
*((unsigned int *)((unsigned long)context_ptr+0x00000288+4*2))=0x00006268;
*((unsigned int *)((unsigned long)context_ptr+0x00000288+4*3))=0x0222001c;
*((unsigned int *)((unsigned long)context_ptr+0x00000288+4*4))=0x0d273dc9;
*((unsigned int *)((unsigned long)context_ptr+0x00000288+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000054&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000062d4,"\x3f\xa0\x5e\x35\x75\x21\x4e\xd3\xb9\x89\xe1\x7a\xef\x9c\x3d\x6b\x84\x10\x64\x2c\x3e\x60\x7a\x51\xff\x3d\x0c\x23",28))
printf("strip: 3fa05e3575214ed3, Pass\n");
else
printf("strip: 3fa05e3575214ed3, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000062b0))=0x020a0012;
*((unsigned int *)((unsigned long)context_ptr+0x000062b0+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000062b0+4*2))=0x0202001d;
*((unsigned int *)((unsigned long)context_ptr+0x000062b0+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x000062c0))=0xc51cc6d0;
*((unsigned int *)((unsigned long)context_ptr+0x000062c0+4*1))=0xaf7bbfd6;
*((unsigned int *)((unsigned long)context_ptr+0x000062c0+4*2))=0xc843c319;
*((unsigned int *)((unsigned long)context_ptr+0x000062c0+4*3))=0x138982a2;
*((unsigned int *)((unsigned long)context_ptr+0x000062c0+4*4))=0x23c6030a;
*((unsigned int *)((unsigned long)context_ptr+0x000062c0+4*5))=0xe2fa621f;
*((unsigned int *)((unsigned long)context_ptr+0x000062c0+4*6))=0x6415d150;
*((unsigned int *)((unsigned long)context_ptr+0x000062c0+4*7))=0x00000094;
*((unsigned int *)((unsigned long)context_ptr+0x000032a0))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x000032a0+4*1))=0x000063f0;
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
*((unsigned int *)((unsigned long)context_ptr+0x000002a0+4*1))=0x000062c0;
*((unsigned int *)((unsigned long)context_ptr+0x000002a0+4*2))=0x000062b0;
*((unsigned int *)((unsigned long)context_ptr+0x000002a0+4*3))=0x0222001d;
*((unsigned int *)((unsigned long)context_ptr+0x000002a0+4*4))=0x069946c7;
*((unsigned int *)((unsigned long)context_ptr+0x000002a0+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000005a&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006310,"\x82\x41\x62\x1f\xb9\xe7\x85\x7b\xba\x5b\x67\x34\xb3\xcd\xc6\x58\x29\x45\x51\x40\xe6\x6c\xf9\x4a\x69\xad\x77\x7f",28))
printf("strip: 8241621fb9e7857b, Pass\n");
else
printf("strip: 8241621fb9e7857b, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000062e0))=0x020a0012;
*((unsigned int *)((unsigned long)context_ptr+0x000062e0+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000062e0+4*2))=0x0202001e;
*((unsigned int *)((unsigned long)context_ptr+0x000062e0+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x000062f0))=0x62271225;
*((unsigned int *)((unsigned long)context_ptr+0x000062f0+4*1))=0x9086aa90;
*((unsigned int *)((unsigned long)context_ptr+0x000062f0+4*2))=0x66baaa5a;
*((unsigned int *)((unsigned long)context_ptr+0x000062f0+4*3))=0x77e7bed0;
*((unsigned int *)((unsigned long)context_ptr+0x000062f0+4*4))=0x6209c658;
*((unsigned int *)((unsigned long)context_ptr+0x000062f0+4*5))=0x3f8357fa;
*((unsigned int *)((unsigned long)context_ptr+0x000062f0+4*6))=0x9e6f1c13;
*((unsigned int *)((unsigned long)context_ptr+0x000062f0+4*7))=0x0000848b;
*((unsigned int *)((unsigned long)context_ptr+0x000032b8))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x000032b8+4*1))=0x00006310;
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
*((unsigned int *)((unsigned long)context_ptr+0x000002b8+4*1))=0x000062f0;
*((unsigned int *)((unsigned long)context_ptr+0x000002b8+4*2))=0x000062e0;
*((unsigned int *)((unsigned long)context_ptr+0x000002b8+4*3))=0x0222001e;
*((unsigned int *)((unsigned long)context_ptr+0x000002b8+4*4))=0x05bd3837;
*((unsigned int *)((unsigned long)context_ptr+0x000002b8+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000060&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x0000632c,"\xee\xa5\x83\xf4\x0a\x5a\xd4\x1a\x79\xa2\x3e\x51\x66\x9d\x12\xe1\x10\xb8\xc4\x72\x05\x26\xbe\x95\xd4\x20\x65\x41",28))
printf("strip: eea583f40a5ad41a, Pass\n");
else
printf("strip: eea583f40a5ad41a, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006018))=0x020a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006018+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006018+4*2))=0x0202001f;
*((unsigned int *)((unsigned long)context_ptr+0x00006018+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x0000640c))=0x9a99b17a;
*((unsigned int *)((unsigned long)context_ptr+0x0000640c+4*1))=0x357f16b5;
*((unsigned int *)((unsigned long)context_ptr+0x0000640c+4*2))=0x685a8363;
*((unsigned int *)((unsigned long)context_ptr+0x0000640c+4*3))=0x9af40bbb;
*((unsigned int *)((unsigned long)context_ptr+0x0000640c+4*4))=0x80148e29;
*((unsigned int *)((unsigned long)context_ptr+0x0000640c+4*5))=0xac506bb0;
*((unsigned int *)((unsigned long)context_ptr+0x0000640c+4*6))=0xdd62dfef;
*((unsigned int *)((unsigned long)context_ptr+0x0000640c+4*7))=0x00fb0f1d;
*((unsigned int *)((unsigned long)context_ptr+0x000032d0))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x000032d0+4*1))=0x0000632c;
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
*((unsigned int *)((unsigned long)context_ptr+0x000002d0+4*1))=0x0000640c;
*((unsigned int *)((unsigned long)context_ptr+0x000002d0+4*2))=0x00006018;
*((unsigned int *)((unsigned long)context_ptr+0x000002d0+4*3))=0x0222001f;
*((unsigned int *)((unsigned long)context_ptr+0x000002d0+4*4))=0x08f0c416;
*((unsigned int *)((unsigned long)context_ptr+0x000002d0+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000066&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x0000604c,"\x8d\x59\xc9\xb2\x4d\x85\x4a\x58\x5f\x85\x13\x09\x56\x70\xc6\x2e\x7d\x4d\x53\x17\x02\xb9\xbd\x4b\x4c\xfb\x11\xfb",28))
printf("strip: 8d59c9b24d854a58, Pass\n");
else
printf("strip: 8d59c9b24d854a58, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006008))=0x020a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006008+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006008+4*2))=0x02020020;
*((unsigned int *)((unsigned long)context_ptr+0x00006008+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x00006038))=0x352401bc;
*((unsigned int *)((unsigned long)context_ptr+0x00006038+4*1))=0x7c200093;
*((unsigned int *)((unsigned long)context_ptr+0x00006038+4*2))=0x2c38510a;
*((unsigned int *)((unsigned long)context_ptr+0x00006038+4*3))=0xa63be151;
*((unsigned int *)((unsigned long)context_ptr+0x00006038+4*4))=0x5930acbb;
*((unsigned int *)((unsigned long)context_ptr+0x00006038+4*5))=0x37f88945;
*((unsigned int *)((unsigned long)context_ptr+0x00006038+4*6))=0xf460108d;
*((unsigned int *)((unsigned long)context_ptr+0x00006038+4*7))=0xb7da18e8;
*((unsigned int *)((unsigned long)context_ptr+0x000032e8))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x000032e8+4*1))=0x0000642c;
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
*((unsigned int *)((unsigned long)context_ptr+0x000002e8+4*1))=0x00006038;
*((unsigned int *)((unsigned long)context_ptr+0x000002e8+4*2))=0x00006008;
*((unsigned int *)((unsigned long)context_ptr+0x000002e8+4*3))=0x02220020;
*((unsigned int *)((unsigned long)context_ptr+0x000002e8+4*4))=0x06c2c90a;
*((unsigned int *)((unsigned long)context_ptr+0x000002e8+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000006c&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006348,"\xfd\xc7\x22\x42\xc0\x79\xb2\x2d\x82\x77\x0d\x9a\x42\x45\x01\x7b\x51\xcf\x8c\x11\xf1\x3b\x32\xc8\x3a\xea\x5e\xff",28))
printf("strip: fdc72242c079b22d, Pass\n");
else
printf("strip: fdc72242c079b22d, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006028))=0x020a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006028+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006028+4*2))=0x02020021;
*((unsigned int *)((unsigned long)context_ptr+0x00006028+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x00006058))=0x9a783c01;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*1))=0xb8544ad5;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*2))=0x16e0b6aa;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*3))=0xa79c7f1f;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*4))=0x3deb223a;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*5))=0xa2844804;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*6))=0x518225bd;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*7))=0x31cf5cb9;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*8))=0x000000fe;
*((unsigned int *)((unsigned long)context_ptr+0x00003300))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003300+4*1))=0x00006348;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000300+4*1))=0x00006058;
*((unsigned int *)((unsigned long)context_ptr+0x00000300+4*2))=0x00006028;
*((unsigned int *)((unsigned long)context_ptr+0x00000300+4*3))=0x02220021;
*((unsigned int *)((unsigned long)context_ptr+0x00000300+4*4))=0x0b9c4aba;
*((unsigned int *)((unsigned long)context_ptr+0x00000300+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000072&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006364,"\xed\x67\xd4\xc2\xba\xfc\x1f\x65\x75\x9e\x0e\x5b\x42\x7b\x87\x9d\x22\x5b\x13\x72\xa3\x48\x70\x7a\xf7\xca\x70\xa5",28))
printf("strip: ed67d4c2bafc1f65, Pass\n");
else
printf("strip: ed67d4c2bafc1f65, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006364))=0x020a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006364+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006364+4*2))=0x02020022;
*((unsigned int *)((unsigned long)context_ptr+0x00006364+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x0000607c))=0x0ffa24b5;
*((unsigned int *)((unsigned long)context_ptr+0x0000607c+4*1))=0x0563a355;
*((unsigned int *)((unsigned long)context_ptr+0x0000607c+4*2))=0x97c63d4b;
*((unsigned int *)((unsigned long)context_ptr+0x0000607c+4*3))=0x5136df24;
*((unsigned int *)((unsigned long)context_ptr+0x0000607c+4*4))=0x846bc3df;
*((unsigned int *)((unsigned long)context_ptr+0x0000607c+4*5))=0xa7b7b5fa;
*((unsigned int *)((unsigned long)context_ptr+0x0000607c+4*6))=0x714cecfc;
*((unsigned int *)((unsigned long)context_ptr+0x0000607c+4*7))=0xe7a53ca2;
*((unsigned int *)((unsigned long)context_ptr+0x0000607c+4*8))=0x00005e4e;
*((unsigned int *)((unsigned long)context_ptr+0x00003318))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003318+4*1))=0x00006448;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000318+4*1))=0x0000607c;
*((unsigned int *)((unsigned long)context_ptr+0x00000318+4*2))=0x00006364;
*((unsigned int *)((unsigned long)context_ptr+0x00000318+4*3))=0x02220022;
*((unsigned int *)((unsigned long)context_ptr+0x00000318+4*4))=0x0a4b0c72;
*((unsigned int *)((unsigned long)context_ptr+0x00000318+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000078&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000060d4,"\x99\x06\x1b\x56\xc7\x66\x7e\x79\x5c\x5d\x99\x7b\x8a\x90\x7e\xe7\xb8\xa5\x1f\x66\x84\xd4\xa4\x60\xba\x24\xdf\x71",28))
printf("strip: 99061b56c7667e79, Pass\n");
else
printf("strip: 99061b56c7667e79, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000060a0))=0x020a0012;
*((unsigned int *)((unsigned long)context_ptr+0x000060a0+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000060a0+4*2))=0x02020023;
*((unsigned int *)((unsigned long)context_ptr+0x000060a0+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x000060b0))=0x3273c017;
*((unsigned int *)((unsigned long)context_ptr+0x000060b0+4*1))=0x8b76ab5f;
*((unsigned int *)((unsigned long)context_ptr+0x000060b0+4*2))=0x1b1a66f0;
*((unsigned int *)((unsigned long)context_ptr+0x000060b0+4*3))=0xc71d4fb9;
*((unsigned int *)((unsigned long)context_ptr+0x000060b0+4*4))=0xbd9d1ae3;
*((unsigned int *)((unsigned long)context_ptr+0x000060b0+4*5))=0x71afd63e;
*((unsigned int *)((unsigned long)context_ptr+0x000060b0+4*6))=0x2ad4422a;
*((unsigned int *)((unsigned long)context_ptr+0x000060b0+4*7))=0x048f92b4;
*((unsigned int *)((unsigned long)context_ptr+0x000060b0+4*8))=0x00a14f1f;
*((unsigned int *)((unsigned long)context_ptr+0x00003330))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003330+4*1))=0x000060d4;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000330+4*1))=0x000060b0;
*((unsigned int *)((unsigned long)context_ptr+0x00000330+4*2))=0x000060a0;
*((unsigned int *)((unsigned long)context_ptr+0x00000330+4*3))=0x02220023;
*((unsigned int *)((unsigned long)context_ptr+0x00000330+4*4))=0x06243646;
*((unsigned int *)((unsigned long)context_ptr+0x00000330+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000007e&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006380,"\xa2\x6b\x92\x6b\xd6\xbb\xaa\x97\xa7\x89\x1c\xb7\x4e\x22\xc1\x85\x63\xb9\x05\xf9\xcf\x66\x32\x2e\xe6\x4b\xb3\x01",28))
printf("strip: a26b926bd6bbaa97, Pass\n");
else
printf("strip: a26b926bd6bbaa97, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000060f0))=0x020a0012;
*((unsigned int *)((unsigned long)context_ptr+0x000060f0+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000060f0+4*2))=0x02020024;
*((unsigned int *)((unsigned long)context_ptr+0x000060f0+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x00006374))=0x580910b3;
*((unsigned int *)((unsigned long)context_ptr+0x00006374+4*1))=0xc2a561a4;
*((unsigned int *)((unsigned long)context_ptr+0x00006374+4*2))=0x8df848c5;
*((unsigned int *)((unsigned long)context_ptr+0x00006374+4*3))=0x27aca2a0;
*((unsigned int *)((unsigned long)context_ptr+0x00006374+4*4))=0xb6f76eac;
*((unsigned int *)((unsigned long)context_ptr+0x00006374+4*5))=0x96d5fdf9;
*((unsigned int *)((unsigned long)context_ptr+0x00006374+4*6))=0x6b5e7899;
*((unsigned int *)((unsigned long)context_ptr+0x00006374+4*7))=0x092ba5e9;
*((unsigned int *)((unsigned long)context_ptr+0x00006374+4*8))=0x3a107070;
*((unsigned int *)((unsigned long)context_ptr+0x00003348))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003348+4*1))=0x00006464;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000348+4*1))=0x00006374;
*((unsigned int *)((unsigned long)context_ptr+0x00000348+4*2))=0x000060f0;
*((unsigned int *)((unsigned long)context_ptr+0x00000348+4*3))=0x02220024;
*((unsigned int *)((unsigned long)context_ptr+0x00000348+4*4))=0x09ff9b0e;
*((unsigned int *)((unsigned long)context_ptr+0x00000348+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000084&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006140,"\x50\x96\x5d\xc5\x0a\x63\x3e\xa4\x49\x44\x22\xdb\x34\x6f\x1e\xaf\xd2\x33\xd8\x7f\x6d\xfb\x7d\xc1\xa9\x3f\x5a\x37",28))
printf("strip: 50965dc50a633ea4, Pass\n");
else
printf("strip: 50965dc50a633ea4, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006100))=0x020a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006100+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006100+4*2))=0x02020025;
*((unsigned int *)((unsigned long)context_ptr+0x00006100+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x00006110))=0x8ae38072;
*((unsigned int *)((unsigned long)context_ptr+0x00006110+4*1))=0x82d95f23;
*((unsigned int *)((unsigned long)context_ptr+0x00006110+4*2))=0xe1088114;
*((unsigned int *)((unsigned long)context_ptr+0x00006110+4*3))=0xe5feba3f;
*((unsigned int *)((unsigned long)context_ptr+0x00006110+4*4))=0x8bb25287;
*((unsigned int *)((unsigned long)context_ptr+0x00006110+4*5))=0x27b13de8;
*((unsigned int *)((unsigned long)context_ptr+0x00006110+4*6))=0x485dc767;
*((unsigned int *)((unsigned long)context_ptr+0x00006110+4*7))=0x24025f5a;
*((unsigned int *)((unsigned long)context_ptr+0x00006110+4*8))=0x23a7b1bd;
*((unsigned int *)((unsigned long)context_ptr+0x00006110+4*9))=0x0000001d;
*((unsigned int *)((unsigned long)context_ptr+0x00003360))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003360+4*1))=0x00006138;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000360+4*1))=0x00006110;
*((unsigned int *)((unsigned long)context_ptr+0x00000360+4*2))=0x00006100;
*((unsigned int *)((unsigned long)context_ptr+0x00000360+4*3))=0x02220025;
*((unsigned int *)((unsigned long)context_ptr+0x00000360+4*4))=0x02034662;
*((unsigned int *)((unsigned long)context_ptr+0x00000360+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000008a&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x0000639c,"\xd8\x0d\x2e\x47\xa3\xc4\xbb\xef\x83\xfd\x2b\x4a\xf7\xde\xd1\xfd\x23\xdd\xdc\x56\x98\x7b\xb5\x94\xef\x5a\xdf\xfe",28))
printf("strip: d80d2e47a3c4bbef, Pass\n");
else
printf("strip: d80d2e47a3c4bbef, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006398))=0x020a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006398+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006398+4*2))=0x02020026;
*((unsigned int *)((unsigned long)context_ptr+0x00006398+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x00006154))=0x9e738b74;
*((unsigned int *)((unsigned long)context_ptr+0x00006154+4*1))=0xc55dd255;
*((unsigned int *)((unsigned long)context_ptr+0x00006154+4*2))=0xe67a5d04;
*((unsigned int *)((unsigned long)context_ptr+0x00006154+4*3))=0xe6a2bbb8;
*((unsigned int *)((unsigned long)context_ptr+0x00006154+4*4))=0xc3eba1b9;
*((unsigned int *)((unsigned long)context_ptr+0x00006154+4*5))=0xbf30de03;
*((unsigned int *)((unsigned long)context_ptr+0x00006154+4*6))=0x6d276469;
*((unsigned int *)((unsigned long)context_ptr+0x00006154+4*7))=0xa4bcd3ff;
*((unsigned int *)((unsigned long)context_ptr+0x00006154+4*8))=0xe8ee1036;
*((unsigned int *)((unsigned long)context_ptr+0x00006154+4*9))=0x0000e900;
*((unsigned int *)((unsigned long)context_ptr+0x00003378))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003378+4*1))=0x00006480;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000378+4*1))=0x00006154;
*((unsigned int *)((unsigned long)context_ptr+0x00000378+4*2))=0x00006398;
*((unsigned int *)((unsigned long)context_ptr+0x00000378+4*3))=0x02220026;
*((unsigned int *)((unsigned long)context_ptr+0x00000378+4*4))=0x0277b20a;
*((unsigned int *)((unsigned long)context_ptr+0x00000378+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000090&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000061ac,"\xe8\x0b\xec\xe4\x47\x07\x8d\x68\xa8\x99\x4e\x37\x29\xb1\xb9\x4e\xa7\x49\x9b\x86\x21\x8c\x47\x1c\xd1\x5a\x05\xc8",28))
printf("strip: e80bece447078d68, Pass\n");
else
printf("strip: e80bece447078d68, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000063a8))=0x020a0012;
*((unsigned int *)((unsigned long)context_ptr+0x000063a8+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000063a8+4*2))=0x02020027;
*((unsigned int *)((unsigned long)context_ptr+0x000063a8+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x0000617c))=0x780631ef;
*((unsigned int *)((unsigned long)context_ptr+0x0000617c+4*1))=0x90a00c92;
*((unsigned int *)((unsigned long)context_ptr+0x0000617c+4*2))=0x215b1490;
*((unsigned int *)((unsigned long)context_ptr+0x0000617c+4*3))=0xe1545e77;
*((unsigned int *)((unsigned long)context_ptr+0x0000617c+4*4))=0xffa81c9f;
*((unsigned int *)((unsigned long)context_ptr+0x0000617c+4*5))=0x79a8c55d;
*((unsigned int *)((unsigned long)context_ptr+0x0000617c+4*6))=0x446a3667;
*((unsigned int *)((unsigned long)context_ptr+0x0000617c+4*7))=0x25e3ab7c;
*((unsigned int *)((unsigned long)context_ptr+0x0000617c+4*8))=0x31a0c3cf;
*((unsigned int *)((unsigned long)context_ptr+0x0000617c+4*9))=0x00522312;
*((unsigned int *)((unsigned long)context_ptr+0x00003390))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003390+4*1))=0x000061a4;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000390+4*1))=0x0000617c;
*((unsigned int *)((unsigned long)context_ptr+0x00000390+4*2))=0x000063a8;
*((unsigned int *)((unsigned long)context_ptr+0x00000390+4*3))=0x02220027;
*((unsigned int *)((unsigned long)context_ptr+0x00000390+4*4))=0x057f599c;
*((unsigned int *)((unsigned long)context_ptr+0x00000390+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000096&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000063b8,"\xf9\x08\x78\x3d\xb3\x9d\xd7\x9d\xac\x0c\x02\xde\xa8\xa2\xeb\x0b\x42\x19\xe1\xb4\x3d\xf9\x0d\xc1\x92\x08\xca\x47",28))
printf("strip: f908783db39dd79d, Pass\n");
else
printf("strip: f908783db39dd79d, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000063b8))=0x020a0012;
*((unsigned int *)((unsigned long)context_ptr+0x000063b8+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000063b8+4*2))=0x02020028;
*((unsigned int *)((unsigned long)context_ptr+0x000063b8+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x000061c0))=0x75ffcc84;
*((unsigned int *)((unsigned long)context_ptr+0x000061c0+4*1))=0xed7f590e;
*((unsigned int *)((unsigned long)context_ptr+0x000061c0+4*2))=0x1970ea10;
*((unsigned int *)((unsigned long)context_ptr+0x000061c0+4*3))=0x3c221ec0;
*((unsigned int *)((unsigned long)context_ptr+0x000061c0+4*4))=0x96dca98c;
*((unsigned int *)((unsigned long)context_ptr+0x000061c0+4*5))=0xa9817ba3;
*((unsigned int *)((unsigned long)context_ptr+0x000061c0+4*6))=0x9f9f4b45;
*((unsigned int *)((unsigned long)context_ptr+0x000061c0+4*7))=0xd58c322e;
*((unsigned int *)((unsigned long)context_ptr+0x000061c0+4*8))=0x870c2c4f;
*((unsigned int *)((unsigned long)context_ptr+0x000061c0+4*9))=0xa88b9c87;
*((unsigned int *)((unsigned long)context_ptr+0x000033a8))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x000033a8+4*1))=0x0000649c;
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
*((unsigned int *)((unsigned long)context_ptr+0x000003a8+4*1))=0x000061c0;
*((unsigned int *)((unsigned long)context_ptr+0x000003a8+4*2))=0x000063b8;
*((unsigned int *)((unsigned long)context_ptr+0x000003a8+4*3))=0x02220028;
*((unsigned int *)((unsigned long)context_ptr+0x000003a8+4*4))=0x0cbc9685;
*((unsigned int *)((unsigned long)context_ptr+0x000003a8+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000009c&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006220,"\xf2\x03\x58\x5f\x50\xa3\x1f\x18\x1f\xdb\x55\x7e\xd7\x63\xc6\x5a\x5a\x16\xa8\xbc\xda\x1b\x89\x11\x6f\xc9\x95\x8d",28))
printf("strip: f203585f50a31f18, Pass\n");
else
printf("strip: f203585f50a31f18, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000061e8))=0x020a0012;
*((unsigned int *)((unsigned long)context_ptr+0x000061e8+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000061e8+4*2))=0x02020029;
*((unsigned int *)((unsigned long)context_ptr+0x000061e8+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x000061f8))=0x31f02bf3;
*((unsigned int *)((unsigned long)context_ptr+0x000061f8+4*1))=0x29d745de;
*((unsigned int *)((unsigned long)context_ptr+0x000061f8+4*2))=0xef1fa9da;
*((unsigned int *)((unsigned long)context_ptr+0x000061f8+4*3))=0x0dd72f6f;
*((unsigned int *)((unsigned long)context_ptr+0x000061f8+4*4))=0xbf17bc09;
*((unsigned int *)((unsigned long)context_ptr+0x000061f8+4*5))=0x9023f018;
*((unsigned int *)((unsigned long)context_ptr+0x000061f8+4*6))=0x7d185da5;
*((unsigned int *)((unsigned long)context_ptr+0x000061f8+4*7))=0x3934e455;
*((unsigned int *)((unsigned long)context_ptr+0x000061f8+4*8))=0x23497198;
*((unsigned int *)((unsigned long)context_ptr+0x000061f8+4*9))=0xf0e718d6;
*((unsigned int *)((unsigned long)context_ptr+0x000061f8+4*10))=0x00000021;
*((unsigned int *)((unsigned long)context_ptr+0x000033c0))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x000033c0+4*1))=0x000064b8;
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
*((unsigned int *)((unsigned long)context_ptr+0x000003c0+4*1))=0x000061f8;
*((unsigned int *)((unsigned long)context_ptr+0x000003c0+4*2))=0x000061e8;
*((unsigned int *)((unsigned long)context_ptr+0x000003c0+4*3))=0x02220029;
*((unsigned int *)((unsigned long)context_ptr+0x000003c0+4*4))=0x0cadf4be;
*((unsigned int *)((unsigned long)context_ptr+0x000003c0+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000000a2&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000063d4,"\xf5\x6d\x8c\x05\x0a\x2f\x79\x0c\x0c\xfd\xc2\xc9\xf6\x6b\xcf\xbf\xe9\xb9\x76\xcd\xc4\xcf\x18\xf3\x3d\x0f\x19\x5a",28))
printf("strip: f56d8c050a2f790c, Pass\n");
else
printf("strip: f56d8c050a2f790c, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000063c8))=0x020a0012;
*((unsigned int *)((unsigned long)context_ptr+0x000063c8+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000063c8+4*2))=0x0202002a;
*((unsigned int *)((unsigned long)context_ptr+0x000063c8+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x00006224))=0xf8e77a1c;
*((unsigned int *)((unsigned long)context_ptr+0x00006224+4*1))=0x60cb31a7;
*((unsigned int *)((unsigned long)context_ptr+0x00006224+4*2))=0x84719743;
*((unsigned int *)((unsigned long)context_ptr+0x00006224+4*3))=0x6edf09f8;
*((unsigned int *)((unsigned long)context_ptr+0x00006224+4*4))=0x79bce0d8;
*((unsigned int *)((unsigned long)context_ptr+0x00006224+4*5))=0xb6659885;
*((unsigned int *)((unsigned long)context_ptr+0x00006224+4*6))=0x90f456da;
*((unsigned int *)((unsigned long)context_ptr+0x00006224+4*7))=0x47b9294b;
*((unsigned int *)((unsigned long)context_ptr+0x00006224+4*8))=0x605af2cf;
*((unsigned int *)((unsigned long)context_ptr+0x00006224+4*9))=0xd3ff414d;
*((unsigned int *)((unsigned long)context_ptr+0x00006224+4*10))=0x000007dd;
*((unsigned int *)((unsigned long)context_ptr+0x000033d8))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x000033d8+4*1))=0x000064d4;
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
*((unsigned int *)((unsigned long)context_ptr+0x000003d8+4*1))=0x00006224;
*((unsigned int *)((unsigned long)context_ptr+0x000003d8+4*2))=0x000063c8;
*((unsigned int *)((unsigned long)context_ptr+0x000003d8+4*3))=0x0222002a;
*((unsigned int *)((unsigned long)context_ptr+0x000003d8+4*4))=0x0d2c1d25;
*((unsigned int *)((unsigned long)context_ptr+0x000003d8+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000000a8&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006294,"\x4e\x0e\xd8\x24\x44\xbc\xf5\x6e\x36\xc6\xd6\x2e\x23\x47\xcd\xfd\xcf\x24\xa0\x38\x72\x82\x8c\xbf\x2a\x90\x3e\x71",28))
printf("strip: 4e0ed82444bcf56e, Pass\n");
else
printf("strip: 4e0ed82444bcf56e, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000063d8))=0x020a0012;
*((unsigned int *)((unsigned long)context_ptr+0x000063d8+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000063d8+4*2))=0x0202002b;
*((unsigned int *)((unsigned long)context_ptr+0x000063d8+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x00006250))=0xab612bd0;
*((unsigned int *)((unsigned long)context_ptr+0x00006250+4*1))=0xcfec84a1;
*((unsigned int *)((unsigned long)context_ptr+0x00006250+4*2))=0x836aad98;
*((unsigned int *)((unsigned long)context_ptr+0x00006250+4*3))=0x7533d6a1;
*((unsigned int *)((unsigned long)context_ptr+0x00006250+4*4))=0x1e09322f;
*((unsigned int *)((unsigned long)context_ptr+0x00006250+4*5))=0x244e54c1;
*((unsigned int *)((unsigned long)context_ptr+0x00006250+4*6))=0x610e6a93;
*((unsigned int *)((unsigned long)context_ptr+0x00006250+4*7))=0xdbf9c1ce;
*((unsigned int *)((unsigned long)context_ptr+0x00006250+4*8))=0x68c9ca7f;
*((unsigned int *)((unsigned long)context_ptr+0x00006250+4*9))=0x9f718f63;
*((unsigned int *)((unsigned long)context_ptr+0x00006250+4*10))=0x00a4ebd0;
*((unsigned int *)((unsigned long)context_ptr+0x000033f0))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x000033f0+4*1))=0x0000627c;
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
*((unsigned int *)((unsigned long)context_ptr+0x000003f0+4*1))=0x00006250;
*((unsigned int *)((unsigned long)context_ptr+0x000003f0+4*2))=0x000063d8;
*((unsigned int *)((unsigned long)context_ptr+0x000003f0+4*3))=0x0222002b;
*((unsigned int *)((unsigned long)context_ptr+0x000003f0+4*4))=0x0664aaa2;
*((unsigned int *)((unsigned long)context_ptr+0x000003f0+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000000ae&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000063f0,"\x92\x8c\x44\xe2\x31\x23\x62\xe1\x78\x75\x0f\xf9\xb4\xa3\x03\x28\x4c\xb4\xe0\xdc\x12\xfc\x1a\xf0\x14\xa0\xa1\xa6",28))
printf("strip: 928c44e2312362e1, Pass\n");
else
printf("strip: 928c44e2312362e1, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000063e8))=0x020a0012;
*((unsigned int *)((unsigned long)context_ptr+0x000063e8+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000063e8+4*2))=0x0202002c;
*((unsigned int *)((unsigned long)context_ptr+0x000063e8+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x00006298))=0xe353445b;
*((unsigned int *)((unsigned long)context_ptr+0x00006298+4*1))=0xa076fc1a;
*((unsigned int *)((unsigned long)context_ptr+0x00006298+4*2))=0x66c41081;
*((unsigned int *)((unsigned long)context_ptr+0x00006298+4*3))=0x244fd27b;
*((unsigned int *)((unsigned long)context_ptr+0x00006298+4*4))=0x9710b00b;
*((unsigned int *)((unsigned long)context_ptr+0x00006298+4*5))=0x4a641c11;
*((unsigned int *)((unsigned long)context_ptr+0x00006298+4*6))=0xf6f2f11b;
*((unsigned int *)((unsigned long)context_ptr+0x00006298+4*7))=0x6790e8fa;
*((unsigned int *)((unsigned long)context_ptr+0x00006298+4*8))=0xc63a86bd;
*((unsigned int *)((unsigned long)context_ptr+0x00006298+4*9))=0x89f3a629;
*((unsigned int *)((unsigned long)context_ptr+0x00006298+4*10))=0x6e825b25;
*((unsigned int *)((unsigned long)context_ptr+0x00003408))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003408+4*1))=0x000062c4;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000408+4*1))=0x00006298;
*((unsigned int *)((unsigned long)context_ptr+0x00000408+4*2))=0x000063e8;
*((unsigned int *)((unsigned long)context_ptr+0x00000408+4*3))=0x0222002c;
*((unsigned int *)((unsigned long)context_ptr+0x00000408+4*4))=0x0e14880b;
*((unsigned int *)((unsigned long)context_ptr+0x00000408+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000000b4&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006310,"\xe2\x9e\x10\xd5\xe9\xa5\x10\x62\xba\x80\x24\xab\x46\xa0\x8b\xbb\x51\x30\x18\x10\xca\x40\xa8\xe2\xcf\xc9\xf0\x47",28))
printf("strip: e29e10d5e9a51062, Pass\n");
else
printf("strip: e29e10d5e9a51062, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000062e0))=0x020a0012;
*((unsigned int *)((unsigned long)context_ptr+0x000062e0+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000062e0+4*2))=0x0202002d;
*((unsigned int *)((unsigned long)context_ptr+0x000062e0+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x000062f0))=0x02e92961;
*((unsigned int *)((unsigned long)context_ptr+0x000062f0+4*1))=0xe9fd2add;
*((unsigned int *)((unsigned long)context_ptr+0x000062f0+4*2))=0xddaac417;
*((unsigned int *)((unsigned long)context_ptr+0x000062f0+4*3))=0xbcca4f7f;
*((unsigned int *)((unsigned long)context_ptr+0x000062f0+4*4))=0x7fc4fc89;
*((unsigned int *)((unsigned long)context_ptr+0x000062f0+4*5))=0x0cd781ed;
*((unsigned int *)((unsigned long)context_ptr+0x000062f0+4*6))=0x233b3621;
*((unsigned int *)((unsigned long)context_ptr+0x000062f0+4*7))=0xb9978f0a;
*((unsigned int *)((unsigned long)context_ptr+0x000062f0+4*8))=0x0373749d;
*((unsigned int *)((unsigned long)context_ptr+0x000062f0+4*9))=0xf6a0a29d;
*((unsigned int *)((unsigned long)context_ptr+0x000062f0+4*10))=0x8d9c35b4;
*((unsigned int *)((unsigned long)context_ptr+0x000062f0+4*11))=0x000000ac;
*((unsigned int *)((unsigned long)context_ptr+0x00003420))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003420+4*1))=0x000064f0;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000420+4*1))=0x000062f0;
*((unsigned int *)((unsigned long)context_ptr+0x00000420+4*2))=0x000062e0;
*((unsigned int *)((unsigned long)context_ptr+0x00000420+4*3))=0x0222002d;
*((unsigned int *)((unsigned long)context_ptr+0x00000420+4*4))=0x0754151a;
*((unsigned int *)((unsigned long)context_ptr+0x00000420+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000000ba&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x0000632c,"\x2c\x6c\x2d\xbd\x05\x8c\x5a\xf7\x52\xa2\x55\xd8\xc1\x31\xe6\xbc\xd2\xd9\x3e\x58\x59\xa0\x04\xc6\xa4\xcb\x4d\xef",28))
printf("strip: 2c6c2dbd058c5af7, Pass\n");
else
printf("strip: 2c6c2dbd058c5af7, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006018))=0x020a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006018+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006018+4*2))=0x0202002e;
*((unsigned int *)((unsigned long)context_ptr+0x00006018+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x000063f8))=0xc2ec4d8a;
*((unsigned int *)((unsigned long)context_ptr+0x000063f8+4*1))=0xd4d113a0;
*((unsigned int *)((unsigned long)context_ptr+0x000063f8+4*2))=0xe62cd4ce;
*((unsigned int *)((unsigned long)context_ptr+0x000063f8+4*3))=0x2800434b;
*((unsigned int *)((unsigned long)context_ptr+0x000063f8+4*4))=0x0cdf3b58;
*((unsigned int *)((unsigned long)context_ptr+0x000063f8+4*5))=0xd5dd6071;
*((unsigned int *)((unsigned long)context_ptr+0x000063f8+4*6))=0x4075ad53;
*((unsigned int *)((unsigned long)context_ptr+0x000063f8+4*7))=0xbcb277b2;
*((unsigned int *)((unsigned long)context_ptr+0x000063f8+4*8))=0x0223438f;
*((unsigned int *)((unsigned long)context_ptr+0x000063f8+4*9))=0x48d3a96c;
*((unsigned int *)((unsigned long)context_ptr+0x000063f8+4*10))=0x55567b11;
*((unsigned int *)((unsigned long)context_ptr+0x000063f8+4*11))=0x0000850c;
*((unsigned int *)((unsigned long)context_ptr+0x00003438))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003438+4*1))=0x00006320;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000438+4*1))=0x000063f8;
*((unsigned int *)((unsigned long)context_ptr+0x00000438+4*2))=0x00006018;
*((unsigned int *)((unsigned long)context_ptr+0x00000438+4*3))=0x0222002e;
*((unsigned int *)((unsigned long)context_ptr+0x00000438+4*4))=0x0ada375e;
*((unsigned int *)((unsigned long)context_ptr+0x00000438+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000000c0&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x0000642c,"\x81\x39\x4f\x9c\xbe\x19\x22\xe5\x6b\x92\x06\xd7\x0f\x81\x03\x02\x97\xb9\xaa\xe7\xb7\x2f\x00\x95\x0d\x17\x2c\xc7",28))
printf("strip: 81394f9cbe1922e5, Pass\n");
else
printf("strip: 81394f9cbe1922e5, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006008))=0x020a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006008+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006008+4*2))=0x0202002f;
*((unsigned int *)((unsigned long)context_ptr+0x00006008+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x0000650c))=0x44cb1472;
*((unsigned int *)((unsigned long)context_ptr+0x0000650c+4*1))=0x3469d1a9;
*((unsigned int *)((unsigned long)context_ptr+0x0000650c+4*2))=0xa8987528;
*((unsigned int *)((unsigned long)context_ptr+0x0000650c+4*3))=0x22003e96;
*((unsigned int *)((unsigned long)context_ptr+0x0000650c+4*4))=0xfa91f870;
*((unsigned int *)((unsigned long)context_ptr+0x0000650c+4*5))=0xb04afed7;
*((unsigned int *)((unsigned long)context_ptr+0x0000650c+4*6))=0x679dde6e;
*((unsigned int *)((unsigned long)context_ptr+0x0000650c+4*7))=0x6c7ed7f1;
*((unsigned int *)((unsigned long)context_ptr+0x0000650c+4*8))=0x2a4f6767;
*((unsigned int *)((unsigned long)context_ptr+0x0000650c+4*9))=0x289f1fd4;
*((unsigned int *)((unsigned long)context_ptr+0x0000650c+4*10))=0x04203ade;
*((unsigned int *)((unsigned long)context_ptr+0x0000650c+4*11))=0x0050c9e7;
*((unsigned int *)((unsigned long)context_ptr+0x00003450))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003450+4*1))=0x00006038;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000450+4*1))=0x0000650c;
*((unsigned int *)((unsigned long)context_ptr+0x00000450+4*2))=0x00006008;
*((unsigned int *)((unsigned long)context_ptr+0x00000450+4*3))=0x0222002f;
*((unsigned int *)((unsigned long)context_ptr+0x00000450+4*4))=0x038137f8;
*((unsigned int *)((unsigned long)context_ptr+0x00000450+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000000c6&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006348,"\x91\xb6\x22\x5f\x99\xb7\x87\xd2\xc5\xbd\x05\x05\x00\x5a\x23\x5c\x32\xb9\x72\x49\xe8\x3f\xd4\x5b\x53\xdf\x00\x5c",28))
printf("strip: 91b6225f99b787d2, Pass\n");
else
printf("strip: 91b6225f99b787d2, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006028))=0x020a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006028+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006028+4*2))=0x02020030;
*((unsigned int *)((unsigned long)context_ptr+0x00006028+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x0000653c))=0x6c570e8e;
*((unsigned int *)((unsigned long)context_ptr+0x0000653c+4*1))=0xcdab517b;
*((unsigned int *)((unsigned long)context_ptr+0x0000653c+4*2))=0x97aa6b1e;
*((unsigned int *)((unsigned long)context_ptr+0x0000653c+4*3))=0xe38bdedf;
*((unsigned int *)((unsigned long)context_ptr+0x0000653c+4*4))=0x620226ce;
*((unsigned int *)((unsigned long)context_ptr+0x0000653c+4*5))=0x84cf075d;
*((unsigned int *)((unsigned long)context_ptr+0x0000653c+4*6))=0x66ced5f9;
*((unsigned int *)((unsigned long)context_ptr+0x0000653c+4*7))=0x8d1ab6f1;
*((unsigned int *)((unsigned long)context_ptr+0x0000653c+4*8))=0x0a67a436;
*((unsigned int *)((unsigned long)context_ptr+0x0000653c+4*9))=0x35a3ebe6;
*((unsigned int *)((unsigned long)context_ptr+0x0000653c+4*10))=0x351db169;
*((unsigned int *)((unsigned long)context_ptr+0x0000653c+4*11))=0x23c1ef17;
*((unsigned int *)((unsigned long)context_ptr+0x00003468))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003468+4*1))=0x00006428;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000468+4*1))=0x0000653c;
*((unsigned int *)((unsigned long)context_ptr+0x00000468+4*2))=0x00006028;
*((unsigned int *)((unsigned long)context_ptr+0x00000468+4*3))=0x02220030;
*((unsigned int *)((unsigned long)context_ptr+0x00000468+4*4))=0x0f944b91;
*((unsigned int *)((unsigned long)context_ptr+0x00000468+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000000cc&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006448,"\x29\x5a\x58\x09\x50\xab\xdf\x9f\x80\x3f\x5d\x48\xe4\x0e\x50\x57\x38\xfc\x7b\xd4\x81\xbf\x47\x33\x57\xbd\xed\xcb",28))
printf("strip: 295a580950abdf9f, Pass\n");
else
printf("strip: 295a580950abdf9f, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006444))=0x020a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006444+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006444+4*2))=0x02020031;
*((unsigned int *)((unsigned long)context_ptr+0x00006444+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x0000633c))=0x8ccb06bb;
*((unsigned int *)((unsigned long)context_ptr+0x0000633c+4*1))=0x9f680c05;
*((unsigned int *)((unsigned long)context_ptr+0x0000633c+4*2))=0x61e6a473;
*((unsigned int *)((unsigned long)context_ptr+0x0000633c+4*3))=0x560bcb6b;
*((unsigned int *)((unsigned long)context_ptr+0x0000633c+4*4))=0xa9aca70f;
*((unsigned int *)((unsigned long)context_ptr+0x0000633c+4*5))=0xa103be9e;
*((unsigned int *)((unsigned long)context_ptr+0x0000633c+4*6))=0x08c1d5a1;
*((unsigned int *)((unsigned long)context_ptr+0x0000633c+4*7))=0x1b476997;
*((unsigned int *)((unsigned long)context_ptr+0x0000633c+4*8))=0x7b3d271f;
*((unsigned int *)((unsigned long)context_ptr+0x0000633c+4*9))=0x8534429a;
*((unsigned int *)((unsigned long)context_ptr+0x0000633c+4*10))=0x643a137c;
*((unsigned int *)((unsigned long)context_ptr+0x0000633c+4*11))=0xdf3f75ef;
*((unsigned int *)((unsigned long)context_ptr+0x0000633c+4*12))=0x000000ff;
*((unsigned int *)((unsigned long)context_ptr+0x00003480))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003480+4*1))=0x00006054;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000480+4*1))=0x0000633c;
*((unsigned int *)((unsigned long)context_ptr+0x00000480+4*2))=0x00006444;
*((unsigned int *)((unsigned long)context_ptr+0x00000480+4*3))=0x02220031;
*((unsigned int *)((unsigned long)context_ptr+0x00000480+4*4))=0x07da9c12;
*((unsigned int *)((unsigned long)context_ptr+0x00000480+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000000d2&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000060d4,"\x7e\x47\x26\xb7\xaf\xe5\xfb\x90\x65\xc0\x04\x8d\x0b\x45\xb7\x16\x86\x96\x51\x69\x47\x6e\x2f\x63\xcf\xf8\x9c\x1a",28))
printf("strip: 7e4726b7afe5fb90, Pass\n");
else
printf("strip: 7e4726b7afe5fb90, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006454))=0x020a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006454+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006454+4*2))=0x02020032;
*((unsigned int *)((unsigned long)context_ptr+0x00006454+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x00006070))=0x3f9e44a3;
*((unsigned int *)((unsigned long)context_ptr+0x00006070+4*1))=0x4d71b703;
*((unsigned int *)((unsigned long)context_ptr+0x00006070+4*2))=0xf8ce6186;
*((unsigned int *)((unsigned long)context_ptr+0x00006070+4*3))=0x02a709a6;
*((unsigned int *)((unsigned long)context_ptr+0x00006070+4*4))=0x06dd1766;
*((unsigned int *)((unsigned long)context_ptr+0x00006070+4*5))=0x428276ad;
*((unsigned int *)((unsigned long)context_ptr+0x00006070+4*6))=0x7d736e60;
*((unsigned int *)((unsigned long)context_ptr+0x00006070+4*7))=0x84dca1d5;
*((unsigned int *)((unsigned long)context_ptr+0x00006070+4*8))=0xbcb6a086;
*((unsigned int *)((unsigned long)context_ptr+0x00006070+4*9))=0xbc46668f;
*((unsigned int *)((unsigned long)context_ptr+0x00006070+4*10))=0xe5fdf50f;
*((unsigned int *)((unsigned long)context_ptr+0x00006070+4*11))=0xd599f5e3;
*((unsigned int *)((unsigned long)context_ptr+0x00006070+4*12))=0x0000752f;
*((unsigned int *)((unsigned long)context_ptr+0x00003498))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003498+4*1))=0x000060a4;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000498+4*1))=0x00006070;
*((unsigned int *)((unsigned long)context_ptr+0x00000498+4*2))=0x00006454;
*((unsigned int *)((unsigned long)context_ptr+0x00000498+4*3))=0x02220032;
*((unsigned int *)((unsigned long)context_ptr+0x00000498+4*4))=0x06f599e3;
*((unsigned int *)((unsigned long)context_ptr+0x00000498+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000000d8&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006464,"\x99\x44\x21\xd9\xdd\x2f\x61\x40\xee\x17\xf1\x8c\x21\x2b\xa7\xc6\x78\xb3\x3a\xce\x74\x1c\xa6\x85\xe6\x57\xcd\xb5",28))
printf("strip: 994421d9dd2f6140, Pass\n");
else
printf("strip: 994421d9dd2f6140, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006464))=0x020a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006464+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006464+4*2))=0x02020033;
*((unsigned int *)((unsigned long)context_ptr+0x00006464+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x000060c0))=0x344c3121;
*((unsigned int *)((unsigned long)context_ptr+0x000060c0+4*1))=0xb06f0a4b;
*((unsigned int *)((unsigned long)context_ptr+0x000060c0+4*2))=0x6b1a2a02;
*((unsigned int *)((unsigned long)context_ptr+0x000060c0+4*3))=0x5a6644df;
*((unsigned int *)((unsigned long)context_ptr+0x000060c0+4*4))=0x0a371727;
*((unsigned int *)((unsigned long)context_ptr+0x000060c0+4*5))=0xfd47c264;
*((unsigned int *)((unsigned long)context_ptr+0x000060c0+4*6))=0x9191c181;
*((unsigned int *)((unsigned long)context_ptr+0x000060c0+4*7))=0x2934c8c8;
*((unsigned int *)((unsigned long)context_ptr+0x000060c0+4*8))=0x3b143b2f;
*((unsigned int *)((unsigned long)context_ptr+0x000060c0+4*9))=0x9d07a165;
*((unsigned int *)((unsigned long)context_ptr+0x000060c0+4*10))=0x91a7e4b5;
*((unsigned int *)((unsigned long)context_ptr+0x000060c0+4*11))=0xcd9c614c;
*((unsigned int *)((unsigned long)context_ptr+0x000060c0+4*12))=0x005daa59;
*((unsigned int *)((unsigned long)context_ptr+0x000034b0))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x000034b0+4*1))=0x00006370;
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
*((unsigned int *)((unsigned long)context_ptr+0x000004b0+4*1))=0x000060c0;
*((unsigned int *)((unsigned long)context_ptr+0x000004b0+4*2))=0x00006464;
*((unsigned int *)((unsigned long)context_ptr+0x000004b0+4*3))=0x02220033;
*((unsigned int *)((unsigned long)context_ptr+0x000004b0+4*4))=0x019e3bfe;
*((unsigned int *)((unsigned long)context_ptr+0x000004b0+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000000de&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006138,"\xcd\x36\x05\xc3\x4e\x21\x5a\x80\x21\x86\x85\xc4\xa4\x88\x7a\xee\xe0\x1a\x89\x73\xd6\x31\x0d\xed\xc4\xb4\x64\x97",28))
printf("strip: cd3605c34e215a80, Pass\n");
else
printf("strip: cd3605c34e215a80, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000060f4))=0x020a0012;
*((unsigned int *)((unsigned long)context_ptr+0x000060f4+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000060f4+4*2))=0x02020034;
*((unsigned int *)((unsigned long)context_ptr+0x000060f4+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x00006104))=0xf01d9860;
*((unsigned int *)((unsigned long)context_ptr+0x00006104+4*1))=0x40119b2c;
*((unsigned int *)((unsigned long)context_ptr+0x00006104+4*2))=0xe4fac325;
*((unsigned int *)((unsigned long)context_ptr+0x00006104+4*3))=0xa8e8a437;
*((unsigned int *)((unsigned long)context_ptr+0x00006104+4*4))=0xa554720f;
*((unsigned int *)((unsigned long)context_ptr+0x00006104+4*5))=0x0e0ca80f;
*((unsigned int *)((unsigned long)context_ptr+0x00006104+4*6))=0x43c4dd3a;
*((unsigned int *)((unsigned long)context_ptr+0x00006104+4*7))=0x8eee4202;
*((unsigned int *)((unsigned long)context_ptr+0x00006104+4*8))=0xd8a1b914;
*((unsigned int *)((unsigned long)context_ptr+0x00006104+4*9))=0xe0add8fa;
*((unsigned int *)((unsigned long)context_ptr+0x00006104+4*10))=0x4c83369e;
*((unsigned int *)((unsigned long)context_ptr+0x00006104+4*11))=0x49112f3f;
*((unsigned int *)((unsigned long)context_ptr+0x00006104+4*12))=0x1c8782e0;
*((unsigned int *)((unsigned long)context_ptr+0x000034c8))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x000034c8+4*1))=0x00006138;
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
*((unsigned int *)((unsigned long)context_ptr+0x000004c8+4*1))=0x00006104;
*((unsigned int *)((unsigned long)context_ptr+0x000004c8+4*2))=0x000060f4;
*((unsigned int *)((unsigned long)context_ptr+0x000004c8+4*3))=0x02220034;
*((unsigned int *)((unsigned long)context_ptr+0x000004c8+4*4))=0x0f715eea;
*((unsigned int *)((unsigned long)context_ptr+0x000004c8+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000000e4&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006480,"\x2b\x84\xbb\x78\xb7\x68\xcd\xc2\xe9\x7e\x6c\x8b\xc5\x13\x6c\x87\x17\xb1\x50\xd5\x13\x13\xce\x8b\xbf\xda\x09\x89",28))
printf("strip: 2b84bb78b768cdc2, Pass\n");
else
printf("strip: 2b84bb78b768cdc2, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x0000638c))=0x020a0012;
*((unsigned int *)((unsigned long)context_ptr+0x0000638c+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x0000638c+4*2))=0x02020035;
*((unsigned int *)((unsigned long)context_ptr+0x0000638c+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x0000656c))=0xd1488f63;
*((unsigned int *)((unsigned long)context_ptr+0x0000656c+4*1))=0x6011caab;
*((unsigned int *)((unsigned long)context_ptr+0x0000656c+4*2))=0xda563135;
*((unsigned int *)((unsigned long)context_ptr+0x0000656c+4*3))=0xc9d91060;
*((unsigned int *)((unsigned long)context_ptr+0x0000656c+4*4))=0x5b270b8c;
*((unsigned int *)((unsigned long)context_ptr+0x0000656c+4*5))=0xf7c44c6a;
*((unsigned int *)((unsigned long)context_ptr+0x0000656c+4*6))=0x23732b6d;
*((unsigned int *)((unsigned long)context_ptr+0x0000656c+4*7))=0x5afb6876;
*((unsigned int *)((unsigned long)context_ptr+0x0000656c+4*8))=0xb2b4ee1f;
*((unsigned int *)((unsigned long)context_ptr+0x0000656c+4*9))=0x4ab63453;
*((unsigned int *)((unsigned long)context_ptr+0x0000656c+4*10))=0xa270189d;
*((unsigned int *)((unsigned long)context_ptr+0x0000656c+4*11))=0x743aa38c;
*((unsigned int *)((unsigned long)context_ptr+0x0000656c+4*12))=0xa5351310;
*((unsigned int *)((unsigned long)context_ptr+0x0000656c+4*13))=0x000000cb;
*((unsigned int *)((unsigned long)context_ptr+0x000034e0))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x000034e0+4*1))=0x00006154;
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
*((unsigned int *)((unsigned long)context_ptr+0x000004e0+4*1))=0x0000656c;
*((unsigned int *)((unsigned long)context_ptr+0x000004e0+4*2))=0x0000638c;
*((unsigned int *)((unsigned long)context_ptr+0x000004e0+4*3))=0x02220035;
*((unsigned int *)((unsigned long)context_ptr+0x000004e0+4*4))=0x001df380;
*((unsigned int *)((unsigned long)context_ptr+0x000004e0+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000000ea&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000061a4,"\xf2\x89\x30\x93\xa0\x95\x25\xe1\x42\x16\x3f\x0c\x18\x49\xb7\x49\xbf\x79\x92\x05\x63\x32\xc4\xef\xfe\xf2\xfd\x17",28))
printf("strip: f2893093a09525e1, Pass\n");
else
printf("strip: f2893093a09525e1, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x0000639c))=0x020a0012;
*((unsigned int *)((unsigned long)context_ptr+0x0000639c+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x0000639c+4*2))=0x02020036;
*((unsigned int *)((unsigned long)context_ptr+0x0000639c+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x00006170))=0xcedaadc5;
*((unsigned int *)((unsigned long)context_ptr+0x00006170+4*1))=0xca6c1a7d;
*((unsigned int *)((unsigned long)context_ptr+0x00006170+4*2))=0xd166d75d;
*((unsigned int *)((unsigned long)context_ptr+0x00006170+4*3))=0xec01abc2;
*((unsigned int *)((unsigned long)context_ptr+0x00006170+4*4))=0xdc03175d;
*((unsigned int *)((unsigned long)context_ptr+0x00006170+4*5))=0xeffc966b;
*((unsigned int *)((unsigned long)context_ptr+0x00006170+4*6))=0x6ba4bba1;
*((unsigned int *)((unsigned long)context_ptr+0x00006170+4*7))=0x364c351d;
*((unsigned int *)((unsigned long)context_ptr+0x00006170+4*8))=0xb23c34ee;
*((unsigned int *)((unsigned long)context_ptr+0x00006170+4*9))=0xd04ba3f8;
*((unsigned int *)((unsigned long)context_ptr+0x00006170+4*10))=0xc07ea628;
*((unsigned int *)((unsigned long)context_ptr+0x00006170+4*11))=0xd7009f7c;
*((unsigned int *)((unsigned long)context_ptr+0x00006170+4*12))=0xfdf232b9;
*((unsigned int *)((unsigned long)context_ptr+0x00006170+4*13))=0x0000d6a0;
*((unsigned int *)((unsigned long)context_ptr+0x000034f8))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x000034f8+4*1))=0x00006474;
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
*((unsigned int *)((unsigned long)context_ptr+0x000004f8+4*1))=0x00006170;
*((unsigned int *)((unsigned long)context_ptr+0x000004f8+4*2))=0x0000639c;
*((unsigned int *)((unsigned long)context_ptr+0x000004f8+4*3))=0x02220036;
*((unsigned int *)((unsigned long)context_ptr+0x000004f8+4*4))=0x02f5a141;
*((unsigned int *)((unsigned long)context_ptr+0x000004f8+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000000f0&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x0000649c,"\x14\xa8\xcc\x28\x4f\x15\xa4\x88\x60\xad\x7d\x9e\x5d\x6d\xb9\xbf\x18\xea\x5c\xaa\x15\x1e\x37\x4d\x50\xa6\x9a\xfa",28))
printf("strip: 14a8cc284f15a488, Pass\n");
else
printf("strip: 14a8cc284f15a488, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000063ac))=0x020a0012;
*((unsigned int *)((unsigned long)context_ptr+0x000063ac+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000063ac+4*2))=0x02020037;
*((unsigned int *)((unsigned long)context_ptr+0x000063ac+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x000061a8))=0xb0296135;
*((unsigned int *)((unsigned long)context_ptr+0x000061a8+4*1))=0xfc18e89d;
*((unsigned int *)((unsigned long)context_ptr+0x000061a8+4*2))=0xf259074e;
*((unsigned int *)((unsigned long)context_ptr+0x000061a8+4*3))=0xad467e4a;
*((unsigned int *)((unsigned long)context_ptr+0x000061a8+4*4))=0xa01bec5f;
*((unsigned int *)((unsigned long)context_ptr+0x000061a8+4*5))=0xc6885efc;
*((unsigned int *)((unsigned long)context_ptr+0x000061a8+4*6))=0xe1da7925;
*((unsigned int *)((unsigned long)context_ptr+0x000061a8+4*7))=0xae88cc86;
*((unsigned int *)((unsigned long)context_ptr+0x000061a8+4*8))=0x0b1713cf;
*((unsigned int *)((unsigned long)context_ptr+0x000061a8+4*9))=0x5b8138e5;
*((unsigned int *)((unsigned long)context_ptr+0x000061a8+4*10))=0x1bde5963;
*((unsigned int *)((unsigned long)context_ptr+0x000061a8+4*11))=0x789580bd;
*((unsigned int *)((unsigned long)context_ptr+0x000061a8+4*12))=0x69698bc6;
*((unsigned int *)((unsigned long)context_ptr+0x000061a8+4*13))=0x003e8d6c;
*((unsigned int *)((unsigned long)context_ptr+0x00003510))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003510+4*1))=0x00006490;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000510+4*1))=0x000061a8;
*((unsigned int *)((unsigned long)context_ptr+0x00000510+4*2))=0x000063ac;
*((unsigned int *)((unsigned long)context_ptr+0x00000510+4*3))=0x02220037;
*((unsigned int *)((unsigned long)context_ptr+0x00000510+4*4))=0x05645184;
*((unsigned int *)((unsigned long)context_ptr+0x00000510+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000000f6&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000064b8,"\xf2\x15\x8f\xc1\x30\xf7\x55\xce\xd7\xc9\x01\xfd\xe4\x07\xd2\x40\x2d\x9a\x1c\x66\x39\xd0\x4d\xdb\xfe\xb0\xe4\x41",28))
printf("strip: f2158fc130f755ce, Pass\n");
else
printf("strip: f2158fc130f755ce, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000064ac))=0x020a0012;
*((unsigned int *)((unsigned long)context_ptr+0x000064ac+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000064ac+4*2))=0x02020038;
*((unsigned int *)((unsigned long)context_ptr+0x000064ac+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x000061e0))=0xd9afbd36;
*((unsigned int *)((unsigned long)context_ptr+0x000061e0+4*1))=0x2929e730;
*((unsigned int *)((unsigned long)context_ptr+0x000061e0+4*2))=0xacc2556b;
*((unsigned int *)((unsigned long)context_ptr+0x000061e0+4*3))=0x1a861c0f;
*((unsigned int *)((unsigned long)context_ptr+0x000061e0+4*4))=0x029eb78f;
*((unsigned int *)((unsigned long)context_ptr+0x000061e0+4*5))=0x867541ef;
*((unsigned int *)((unsigned long)context_ptr+0x000061e0+4*6))=0xd6a84ffa;
*((unsigned int *)((unsigned long)context_ptr+0x000061e0+4*7))=0x21473990;
*((unsigned int *)((unsigned long)context_ptr+0x000061e0+4*8))=0xeb547ebb;
*((unsigned int *)((unsigned long)context_ptr+0x000061e0+4*9))=0x649e2033;
*((unsigned int *)((unsigned long)context_ptr+0x000061e0+4*10))=0x049b9661;
*((unsigned int *)((unsigned long)context_ptr+0x000061e0+4*11))=0x36080c19;
*((unsigned int *)((unsigned long)context_ptr+0x000061e0+4*12))=0x933113e9;
*((unsigned int *)((unsigned long)context_ptr+0x000061e0+4*13))=0xb035aa60;
*((unsigned int *)((unsigned long)context_ptr+0x00003528))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003528+4*1))=0x000065a4;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000528+4*1))=0x000061e0;
*((unsigned int *)((unsigned long)context_ptr+0x00000528+4*2))=0x000064ac;
*((unsigned int *)((unsigned long)context_ptr+0x00000528+4*3))=0x02220038;
*((unsigned int *)((unsigned long)context_ptr+0x00000528+4*4))=0x06d62a18;
*((unsigned int *)((unsigned long)context_ptr+0x00000528+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000000fc&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000064d4,"\xb0\x9a\xaf\x9f\xc0\xf1\x0c\xa1\x21\x9f\x16\x18\x9c\xdf\x74\x71\xec\x78\x40\x03\xd2\x06\x64\x37\x4a\x49\xb7\xc5",28))
printf("strip: b09aaf9fc0f10ca1, Pass\n");
else
printf("strip: b09aaf9fc0f10ca1, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000063bc))=0x020a0012;
*((unsigned int *)((unsigned long)context_ptr+0x000063bc+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000063bc+4*2))=0x02020039;
*((unsigned int *)((unsigned long)context_ptr+0x000063bc+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x000065c0))=0x9a690ca3;
*((unsigned int *)((unsigned long)context_ptr+0x000065c0+4*1))=0x50520ad7;
*((unsigned int *)((unsigned long)context_ptr+0x000065c0+4*2))=0x7dfd5329;
*((unsigned int *)((unsigned long)context_ptr+0x000065c0+4*3))=0xebfcc912;
*((unsigned int *)((unsigned long)context_ptr+0x000065c0+4*4))=0x92d2679c;
*((unsigned int *)((unsigned long)context_ptr+0x000065c0+4*5))=0xb279aa2d;
*((unsigned int *)((unsigned long)context_ptr+0x000065c0+4*6))=0x4a4d4a34;
*((unsigned int *)((unsigned long)context_ptr+0x000065c0+4*7))=0x03aa59b4;
*((unsigned int *)((unsigned long)context_ptr+0x000065c0+4*8))=0x0cea7706;
*((unsigned int *)((unsigned long)context_ptr+0x000065c0+4*9))=0x124fff15;
*((unsigned int *)((unsigned long)context_ptr+0x000065c0+4*10))=0x96391410;
*((unsigned int *)((unsigned long)context_ptr+0x000065c0+4*11))=0x55f1d708;
*((unsigned int *)((unsigned long)context_ptr+0x000065c0+4*12))=0xd4069bd4;
*((unsigned int *)((unsigned long)context_ptr+0x000065c0+4*13))=0x67babbf9;
*((unsigned int *)((unsigned long)context_ptr+0x000065c0+4*14))=0x000000da;
*((unsigned int *)((unsigned long)context_ptr+0x00003540))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003540+4*1))=0x000064bc;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000540+4*1))=0x000065c0;
*((unsigned int *)((unsigned long)context_ptr+0x00000540+4*2))=0x000063bc;
*((unsigned int *)((unsigned long)context_ptr+0x00000540+4*3))=0x02220039;
*((unsigned int *)((unsigned long)context_ptr+0x00000540+4*4))=0x0d42d603;
*((unsigned int *)((unsigned long)context_ptr+0x00000540+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000102&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x0000627c,"\xe7\x56\x25\x98\x1e\xa4\x72\x84\x6e\xc2\x54\x9f\x7c\xa5\x51\xac\xc5\xa1\x43\x01\xef\xa2\x54\xd7\xd3\xf0\x85\xcd",28))
printf("strip: e75625981ea47284, Pass\n");
else
printf("strip: e75625981ea47284, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000064d8))=0x020a0012;
*((unsigned int *)((unsigned long)context_ptr+0x000064d8+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000064d8+4*2))=0x0202003a;
*((unsigned int *)((unsigned long)context_ptr+0x000064d8+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x00006218))=0x48ad973f;
*((unsigned int *)((unsigned long)context_ptr+0x00006218+4*1))=0x9758f762;
*((unsigned int *)((unsigned long)context_ptr+0x00006218+4*2))=0x5f3b6a74;
*((unsigned int *)((unsigned long)context_ptr+0x00006218+4*3))=0xf4ff74d4;
*((unsigned int *)((unsigned long)context_ptr+0x00006218+4*4))=0x09b42142;
*((unsigned int *)((unsigned long)context_ptr+0x00006218+4*5))=0x753c4a32;
*((unsigned int *)((unsigned long)context_ptr+0x00006218+4*6))=0x2e527cf3;
*((unsigned int *)((unsigned long)context_ptr+0x00006218+4*7))=0x89380080;
*((unsigned int *)((unsigned long)context_ptr+0x00006218+4*8))=0x4f555fdd;
*((unsigned int *)((unsigned long)context_ptr+0x00006218+4*9))=0xace683dd;
*((unsigned int *)((unsigned long)context_ptr+0x00006218+4*10))=0x0e156341;
*((unsigned int *)((unsigned long)context_ptr+0x00006218+4*11))=0x3ad295ed;
*((unsigned int *)((unsigned long)context_ptr+0x00006218+4*12))=0xd0208a8f;
*((unsigned int *)((unsigned long)context_ptr+0x00006218+4*13))=0x952cebf0;
*((unsigned int *)((unsigned long)context_ptr+0x00006218+4*14))=0x0000fdf0;
*((unsigned int *)((unsigned long)context_ptr+0x00003558))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003558+4*1))=0x000063cc;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000558+4*1))=0x00006218;
*((unsigned int *)((unsigned long)context_ptr+0x00000558+4*2))=0x000064d8;
*((unsigned int *)((unsigned long)context_ptr+0x00000558+4*3))=0x0222003a;
*((unsigned int *)((unsigned long)context_ptr+0x00000558+4*4))=0x0dc97bae;
*((unsigned int *)((unsigned long)context_ptr+0x00000558+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000108&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000062c4,"\x35\x48\x50\xf3\x7a\xb6\x29\xe9\xc8\x24\x17\x20\xe1\x37\xd0\x23\xdb\xbd\x42\x50\x04\xcf\x8b\xc9\xbe\x31\xa3\xc1",28))
printf("strip: 354850f37ab629e9, Pass\n");
else
printf("strip: 354850f37ab629e9, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000063e8))=0x020a0012;
*((unsigned int *)((unsigned long)context_ptr+0x000063e8+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000063e8+4*2))=0x0202003b;
*((unsigned int *)((unsigned long)context_ptr+0x000063e8+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x00006254))=0x7e655f7d;
*((unsigned int *)((unsigned long)context_ptr+0x00006254+4*1))=0xf0b38bd2;
*((unsigned int *)((unsigned long)context_ptr+0x00006254+4*2))=0x9fcaba1e;
*((unsigned int *)((unsigned long)context_ptr+0x00006254+4*3))=0x261850bb;
*((unsigned int *)((unsigned long)context_ptr+0x00006254+4*4))=0x752e7ed5;
*((unsigned int *)((unsigned long)context_ptr+0x00006254+4*5))=0x2f067b86;
*((unsigned int *)((unsigned long)context_ptr+0x00006254+4*6))=0x4fc65799;
*((unsigned int *)((unsigned long)context_ptr+0x00006254+4*7))=0x4d5290c9;
*((unsigned int *)((unsigned long)context_ptr+0x00006254+4*8))=0xebc71267;
*((unsigned int *)((unsigned long)context_ptr+0x00006254+4*9))=0x18c996a3;
*((unsigned int *)((unsigned long)context_ptr+0x00006254+4*10))=0x9027afbf;
*((unsigned int *)((unsigned long)context_ptr+0x00006254+4*11))=0x1a143dcd;
*((unsigned int *)((unsigned long)context_ptr+0x00006254+4*12))=0x7ad5624e;
*((unsigned int *)((unsigned long)context_ptr+0x00006254+4*13))=0xf9b33cc3;
*((unsigned int *)((unsigned long)context_ptr+0x00006254+4*14))=0x000edc69;
*((unsigned int *)((unsigned long)context_ptr+0x00003570))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003570+4*1))=0x00006290;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000570+4*1))=0x00006254;
*((unsigned int *)((unsigned long)context_ptr+0x00000570+4*2))=0x000063e8;
*((unsigned int *)((unsigned long)context_ptr+0x00000570+4*3))=0x0222003b;
*((unsigned int *)((unsigned long)context_ptr+0x00000570+4*4))=0x0dc21b3e;
*((unsigned int *)((unsigned long)context_ptr+0x00000570+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000010e&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000064f0,"\x60\xf9\xf6\xbb\x9a\x89\x2a\x7a\x2c\x9f\x15\x32\x30\x18\xec\x32\x83\x98\x1a\x1b\xe6\x34\xec\x1d\xed\xa1\xaf\xc1",28))
printf("strip: 60f9f6bb9a892a7a, Pass\n");
else
printf("strip: 60f9f6bb9a892a7a, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000064e8))=0x020a0012;
*((unsigned int *)((unsigned long)context_ptr+0x000064e8+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000064e8+4*2))=0x0202003c;
*((unsigned int *)((unsigned long)context_ptr+0x000064e8+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x000062ac))=0xb54bfe0d;
*((unsigned int *)((unsigned long)context_ptr+0x000062ac+4*1))=0x5a5f2bcd;
*((unsigned int *)((unsigned long)context_ptr+0x000062ac+4*2))=0xa6c1a82b;
*((unsigned int *)((unsigned long)context_ptr+0x000062ac+4*3))=0x7f6a17bc;
*((unsigned int *)((unsigned long)context_ptr+0x000062ac+4*4))=0x868a74f7;
*((unsigned int *)((unsigned long)context_ptr+0x000062ac+4*5))=0xeee4002d;
*((unsigned int *)((unsigned long)context_ptr+0x000062ac+4*6))=0x92e12704;
*((unsigned int *)((unsigned long)context_ptr+0x000062ac+4*7))=0x42cd8515;
*((unsigned int *)((unsigned long)context_ptr+0x000062ac+4*8))=0x0164bc6c;
*((unsigned int *)((unsigned long)context_ptr+0x000062ac+4*9))=0x6ab08d48;
*((unsigned int *)((unsigned long)context_ptr+0x000062ac+4*10))=0xddf9b451;
*((unsigned int *)((unsigned long)context_ptr+0x000062ac+4*11))=0x35a9207e;
*((unsigned int *)((unsigned long)context_ptr+0x000062ac+4*12))=0xb639a03a;
*((unsigned int *)((unsigned long)context_ptr+0x000062ac+4*13))=0x76cd6e81;
*((unsigned int *)((unsigned long)context_ptr+0x000062ac+4*14))=0xe4be9eb8;
*((unsigned int *)((unsigned long)context_ptr+0x00003588))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003588+4*1))=0x000062e8;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000588+4*1))=0x000062ac;
*((unsigned int *)((unsigned long)context_ptr+0x00000588+4*2))=0x000064e8;
*((unsigned int *)((unsigned long)context_ptr+0x00000588+4*3))=0x0222003c;
*((unsigned int *)((unsigned long)context_ptr+0x00000588+4*4))=0x00123ce9;
*((unsigned int *)((unsigned long)context_ptr+0x00000588+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000114&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006320,"\xe4\xaf\x2e\xd5\x6e\xcd\x27\x76\x66\xc4\x4f\x02\xcc\x8b\x2d\x42\xfc\x10\x43\x5e\xac\xbc\x2e\xf0\xeb\x22\x7c\x12",28))
printf("strip: e4af2ed56ecd2776, Pass\n");
else
printf("strip: e4af2ed56ecd2776, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006018))=0x020a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006018+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006018+4*2))=0x0202003d;
*((unsigned int *)((unsigned long)context_ptr+0x00006018+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x000065fc))=0x75a862ad;
*((unsigned int *)((unsigned long)context_ptr+0x000065fc+4*1))=0xf1406791;
*((unsigned int *)((unsigned long)context_ptr+0x000065fc+4*2))=0xa249a296;
*((unsigned int *)((unsigned long)context_ptr+0x000065fc+4*3))=0x418a948d;
*((unsigned int *)((unsigned long)context_ptr+0x000065fc+4*4))=0x4d4f14a7;
*((unsigned int *)((unsigned long)context_ptr+0x000065fc+4*5))=0xda34006f;
*((unsigned int *)((unsigned long)context_ptr+0x000065fc+4*6))=0x839b03ca;
*((unsigned int *)((unsigned long)context_ptr+0x000065fc+4*7))=0x615cbd18;
*((unsigned int *)((unsigned long)context_ptr+0x000065fc+4*8))=0xd7d59b5d;
*((unsigned int *)((unsigned long)context_ptr+0x000065fc+4*9))=0x9f0fe550;
*((unsigned int *)((unsigned long)context_ptr+0x000065fc+4*10))=0x6a6af4b3;
*((unsigned int *)((unsigned long)context_ptr+0x000065fc+4*11))=0x59f757a0;
*((unsigned int *)((unsigned long)context_ptr+0x000065fc+4*12))=0xff415625;
*((unsigned int *)((unsigned long)context_ptr+0x000065fc+4*13))=0x4846bbe3;
*((unsigned int *)((unsigned long)context_ptr+0x000065fc+4*14))=0x1a389526;
*((unsigned int *)((unsigned long)context_ptr+0x000065fc+4*15))=0x000000e6;
*((unsigned int *)((unsigned long)context_ptr+0x000035a0))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x000035a0+4*1))=0x000063f8;
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
*((unsigned int *)((unsigned long)context_ptr+0x000005a0+4*1))=0x000065fc;
*((unsigned int *)((unsigned long)context_ptr+0x000005a0+4*2))=0x00006018;
*((unsigned int *)((unsigned long)context_ptr+0x000005a0+4*3))=0x0222003d;
*((unsigned int *)((unsigned long)context_ptr+0x000005a0+4*4))=0x0211f319;
*((unsigned int *)((unsigned long)context_ptr+0x000005a0+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000011a&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006038,"\xf0\x51\x32\x35\xc2\x4c\x08\xab\x8f\x1b\xf0\xfa\xb8\x5e\x2b\x80\x89\x02\x25\x9d\x1e\x61\xa4\xe0\xb2\x79\x4a\xfa",28))
printf("strip: f0513235c24c08ab, Pass\n");
else
printf("strip: f0513235c24c08ab, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006008))=0x020a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006008+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006008+4*2))=0x0202003e;
*((unsigned int *)((unsigned long)context_ptr+0x00006008+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x000064f8))=0x77e370b0;
*((unsigned int *)((unsigned long)context_ptr+0x000064f8+4*1))=0xc42deca4;
*((unsigned int *)((unsigned long)context_ptr+0x000064f8+4*2))=0x548f69ef;
*((unsigned int *)((unsigned long)context_ptr+0x000064f8+4*3))=0x643e55ee;
*((unsigned int *)((unsigned long)context_ptr+0x000064f8+4*4))=0xb6182818;
*((unsigned int *)((unsigned long)context_ptr+0x000064f8+4*5))=0x4cb00955;
*((unsigned int *)((unsigned long)context_ptr+0x000064f8+4*6))=0xee95eacf;
*((unsigned int *)((unsigned long)context_ptr+0x000064f8+4*7))=0x05b664ec;
*((unsigned int *)((unsigned long)context_ptr+0x000064f8+4*8))=0x4c91f7a1;
*((unsigned int *)((unsigned long)context_ptr+0x000064f8+4*9))=0x724b618a;
*((unsigned int *)((unsigned long)context_ptr+0x000064f8+4*10))=0x043d7939;
*((unsigned int *)((unsigned long)context_ptr+0x000064f8+4*11))=0x0a4c6c05;
*((unsigned int *)((unsigned long)context_ptr+0x000064f8+4*12))=0xd24e19d1;
*((unsigned int *)((unsigned long)context_ptr+0x000064f8+4*13))=0x42c46dbc;
*((unsigned int *)((unsigned long)context_ptr+0x000064f8+4*14))=0xcd4fcf6b;
*((unsigned int *)((unsigned long)context_ptr+0x000064f8+4*15))=0x0000b46f;
*((unsigned int *)((unsigned long)context_ptr+0x000035b8))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x000035b8+4*1))=0x00006038;
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
*((unsigned int *)((unsigned long)context_ptr+0x000005b8+4*1))=0x000064f8;
*((unsigned int *)((unsigned long)context_ptr+0x000005b8+4*2))=0x00006008;
*((unsigned int *)((unsigned long)context_ptr+0x000005b8+4*3))=0x0222003e;
*((unsigned int *)((unsigned long)context_ptr+0x000005b8+4*4))=0x02254aa0;
*((unsigned int *)((unsigned long)context_ptr+0x000005b8+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000120&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006428,"\x78\x7c\x4a\x00\x09\x2d\x5a\xdf\x85\x67\x11\xb9\x63\x63\x0e\xcf\x2c\xeb\x95\xb2\x52\x87\x2e\xbd\x95\xc0\x8a\x45",28))
printf("strip: 787c4a00092d5adf, Pass\n");
else
printf("strip: 787c4a00092d5adf, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006028))=0x020a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006028+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006028+4*2))=0x0202003f;
*((unsigned int *)((unsigned long)context_ptr+0x00006028+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x0000663c))=0x9b156f08;
*((unsigned int *)((unsigned long)context_ptr+0x0000663c+4*1))=0x15aabc08;
*((unsigned int *)((unsigned long)context_ptr+0x0000663c+4*2))=0xe8bec521;
*((unsigned int *)((unsigned long)context_ptr+0x0000663c+4*3))=0x79f43459;
*((unsigned int *)((unsigned long)context_ptr+0x0000663c+4*4))=0x39ce1791;
*((unsigned int *)((unsigned long)context_ptr+0x0000663c+4*5))=0x9a2876f3;
*((unsigned int *)((unsigned long)context_ptr+0x0000663c+4*6))=0x817c1c3f;
*((unsigned int *)((unsigned long)context_ptr+0x0000663c+4*7))=0xd337e6b6;
*((unsigned int *)((unsigned long)context_ptr+0x0000663c+4*8))=0x62c02074;
*((unsigned int *)((unsigned long)context_ptr+0x0000663c+4*9))=0x943f008f;
*((unsigned int *)((unsigned long)context_ptr+0x0000663c+4*10))=0x38862107;
*((unsigned int *)((unsigned long)context_ptr+0x0000663c+4*11))=0x5f2ae4b4;
*((unsigned int *)((unsigned long)context_ptr+0x0000663c+4*12))=0x24b6f012;
*((unsigned int *)((unsigned long)context_ptr+0x0000663c+4*13))=0x284c9d3b;
*((unsigned int *)((unsigned long)context_ptr+0x0000663c+4*14))=0x65b346d5;
*((unsigned int *)((unsigned long)context_ptr+0x0000663c+4*15))=0x00b4dd3d;
*((unsigned int *)((unsigned long)context_ptr+0x000035d0))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x000035d0+4*1))=0x00006414;
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
*((unsigned int *)((unsigned long)context_ptr+0x000005d0+4*1))=0x0000663c;
*((unsigned int *)((unsigned long)context_ptr+0x000005d0+4*2))=0x00006028;
*((unsigned int *)((unsigned long)context_ptr+0x000005d0+4*3))=0x0222003f;
*((unsigned int *)((unsigned long)context_ptr+0x000005d0+4*4))=0x02304dea;
*((unsigned int *)((unsigned long)context_ptr+0x000005d0+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000126&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006054,"\x34\x9e\xcc\x3a\xaf\x30\xf7\x92\x97\x0f\x21\xb4\x23\xae\x5d\x5b\x7d\xba\x0c\xb8\x7e\x88\x02\x1b\xed\x6f\x91\x3f",28))
printf("strip: 349ecc3aaf30f792, Pass\n");
else
printf("strip: 349ecc3aaf30f792, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006054))=0x020a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006054+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006054+4*2))=0x02020040;
*((unsigned int *)((unsigned long)context_ptr+0x00006054+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x00006304))=0x67dd0f05;
*((unsigned int *)((unsigned long)context_ptr+0x00006304+4*1))=0xfbff9001;
*((unsigned int *)((unsigned long)context_ptr+0x00006304+4*2))=0xd12fbc3e;
*((unsigned int *)((unsigned long)context_ptr+0x00006304+4*3))=0xd4afd19d;
*((unsigned int *)((unsigned long)context_ptr+0x00006304+4*4))=0x1f2f4523;
*((unsigned int *)((unsigned long)context_ptr+0x00006304+4*5))=0x58731538;
*((unsigned int *)((unsigned long)context_ptr+0x00006304+4*6))=0x0bb33202;
*((unsigned int *)((unsigned long)context_ptr+0x00006304+4*7))=0x09eadb04;
*((unsigned int *)((unsigned long)context_ptr+0x00006304+4*8))=0xa0945b42;
*((unsigned int *)((unsigned long)context_ptr+0x00006304+4*9))=0x606645f6;
*((unsigned int *)((unsigned long)context_ptr+0x00006304+4*10))=0xa9e831d6;
*((unsigned int *)((unsigned long)context_ptr+0x00006304+4*11))=0x0b32b87d;
*((unsigned int *)((unsigned long)context_ptr+0x00006304+4*12))=0x9fdf5bdd;
*((unsigned int *)((unsigned long)context_ptr+0x00006304+4*13))=0x624de195;
*((unsigned int *)((unsigned long)context_ptr+0x00006304+4*14))=0xebc9e8d8;
*((unsigned int *)((unsigned long)context_ptr+0x00006304+4*15))=0xe2d92c8c;
*((unsigned int *)((unsigned long)context_ptr+0x000035e8))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x000035e8+4*1))=0x00006430;
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
*((unsigned int *)((unsigned long)context_ptr+0x000005e8+4*1))=0x00006304;
*((unsigned int *)((unsigned long)context_ptr+0x000005e8+4*2))=0x00006054;
*((unsigned int *)((unsigned long)context_ptr+0x000005e8+4*3))=0x02220040;
*((unsigned int *)((unsigned long)context_ptr+0x000005e8+4*4))=0x004d071f;
*((unsigned int *)((unsigned long)context_ptr+0x000005e8+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000012c&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000060a4,"\x38\x2b\x41\xf5\xfd\xad\xdb\x75\xdd\xf0\x70\x4b\x57\x40\x42\x16\x77\xd2\x6f\x93\xea\xf9\x9e\xe2\x2e\xa1\xb9\x61",28))
printf("strip: 382b41f5fdaddb75, Pass\n");
else
printf("strip: 382b41f5fdaddb75, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x0000644c))=0x020a0012;
*((unsigned int *)((unsigned long)context_ptr+0x0000644c+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x0000644c+4*2))=0x02020041;
*((unsigned int *)((unsigned long)context_ptr+0x0000644c+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x00006064))=0x127ab2b3;
*((unsigned int *)((unsigned long)context_ptr+0x00006064+4*1))=0x4e96c258;
*((unsigned int *)((unsigned long)context_ptr+0x00006064+4*2))=0xb388352c;
*((unsigned int *)((unsigned long)context_ptr+0x00006064+4*3))=0xa2b4c7f1;
*((unsigned int *)((unsigned long)context_ptr+0x00006064+4*4))=0x66c89cff;
*((unsigned int *)((unsigned long)context_ptr+0x00006064+4*5))=0x82ca5d23;
*((unsigned int *)((unsigned long)context_ptr+0x00006064+4*6))=0xbf5c357e;
*((unsigned int *)((unsigned long)context_ptr+0x00006064+4*7))=0xeef52c6a;
*((unsigned int *)((unsigned long)context_ptr+0x00006064+4*8))=0x12fc7ddc;
*((unsigned int *)((unsigned long)context_ptr+0x00006064+4*9))=0x8f5808a7;
*((unsigned int *)((unsigned long)context_ptr+0x00006064+4*10))=0xe2ef6f7b;
*((unsigned int *)((unsigned long)context_ptr+0x00006064+4*11))=0xa933c7e3;
*((unsigned int *)((unsigned long)context_ptr+0x00006064+4*12))=0x9858e35e;
*((unsigned int *)((unsigned long)context_ptr+0x00006064+4*13))=0x5b1f54d3;
*((unsigned int *)((unsigned long)context_ptr+0x00006064+4*14))=0xdcfa5945;
*((unsigned int *)((unsigned long)context_ptr+0x00006064+4*15))=0xee81d795;
*((unsigned int *)((unsigned long)context_ptr+0x00006064+4*16))=0x00000040;
*((unsigned int *)((unsigned long)context_ptr+0x00003600))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003600+4*1))=0x00006344;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000600+4*1))=0x00006064;
*((unsigned int *)((unsigned long)context_ptr+0x00000600+4*2))=0x0000644c;
*((unsigned int *)((unsigned long)context_ptr+0x00000600+4*3))=0x02220041;
*((unsigned int *)((unsigned long)context_ptr+0x00000600+4*4))=0x01c660ea;
*((unsigned int *)((unsigned long)context_ptr+0x00000600+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000132&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006370,"\x41\xa4\xcc\x7c\x34\x8d\xab\x94\xf8\x5a\xaa\x5d\x9c\x96\x55\x49\x8c\x86\xe7\x14\x53\x90\x61\xa6\x3a\xbb\xf7\x0a",28))
printf("strip: 41a4cc7c348dab94, Pass\n");
else
printf("strip: 41a4cc7c348dab94, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x0000645c))=0x020a0012;
*((unsigned int *)((unsigned long)context_ptr+0x0000645c+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x0000645c+4*2))=0x02020042;
*((unsigned int *)((unsigned long)context_ptr+0x0000645c+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x000060a8))=0xa750d746;
*((unsigned int *)((unsigned long)context_ptr+0x000060a8+4*1))=0x833a8bd8;
*((unsigned int *)((unsigned long)context_ptr+0x000060a8+4*2))=0x662e5d05;
*((unsigned int *)((unsigned long)context_ptr+0x000060a8+4*3))=0xceb0ab0f;
*((unsigned int *)((unsigned long)context_ptr+0x000060a8+4*4))=0xfb251f98;
*((unsigned int *)((unsigned long)context_ptr+0x000060a8+4*5))=0x527ca9b2;
*((unsigned int *)((unsigned long)context_ptr+0x000060a8+4*6))=0x583ff0d9;
*((unsigned int *)((unsigned long)context_ptr+0x000060a8+4*7))=0xbe93fc51;
*((unsigned int *)((unsigned long)context_ptr+0x000060a8+4*8))=0xd0be5355;
*((unsigned int *)((unsigned long)context_ptr+0x000060a8+4*9))=0x4da6e024;
*((unsigned int *)((unsigned long)context_ptr+0x000060a8+4*10))=0x7085f232;
*((unsigned int *)((unsigned long)context_ptr+0x000060a8+4*11))=0xe902a94e;
*((unsigned int *)((unsigned long)context_ptr+0x000060a8+4*12))=0x990f009d;
*((unsigned int *)((unsigned long)context_ptr+0x000060a8+4*13))=0xc9df543d;
*((unsigned int *)((unsigned long)context_ptr+0x000060a8+4*14))=0x4794e083;
*((unsigned int *)((unsigned long)context_ptr+0x000060a8+4*15))=0xe5110ff9;
*((unsigned int *)((unsigned long)context_ptr+0x000060a8+4*16))=0x0000e08d;
*((unsigned int *)((unsigned long)context_ptr+0x00003618))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003618+4*1))=0x00006360;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000618+4*1))=0x000060a8;
*((unsigned int *)((unsigned long)context_ptr+0x00000618+4*2))=0x0000645c;
*((unsigned int *)((unsigned long)context_ptr+0x00000618+4*3))=0x02220042;
*((unsigned int *)((unsigned long)context_ptr+0x00000618+4*4))=0x0f4c0151;
*((unsigned int *)((unsigned long)context_ptr+0x00000618+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000138&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006138,"\xc0\x6d\x43\x5c\xb2\xb2\xde\x7f\x29\x87\x94\xbd\xb3\x60\xdd\x07\xe2\x88\x9c\x89\x7a\x81\x29\x5f\x78\xc4\x3e\x83",28))
printf("strip: c06d435cb2b2de7f, Pass\n");
else
printf("strip: c06d435cb2b2de7f, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x0000637c))=0x020a0012;
*((unsigned int *)((unsigned long)context_ptr+0x0000637c+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x0000637c+4*2))=0x02020043;
*((unsigned int *)((unsigned long)context_ptr+0x0000637c+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x000060ec))=0x4e5e41d9;
*((unsigned int *)((unsigned long)context_ptr+0x000060ec+4*1))=0xf5859c63;
*((unsigned int *)((unsigned long)context_ptr+0x000060ec+4*2))=0x4b044d78;
*((unsigned int *)((unsigned long)context_ptr+0x000060ec+4*3))=0x7b92fed5;
*((unsigned int *)((unsigned long)context_ptr+0x000060ec+4*4))=0xcf595462;
*((unsigned int *)((unsigned long)context_ptr+0x000060ec+4*5))=0xe1249358;
*((unsigned int *)((unsigned long)context_ptr+0x000060ec+4*6))=0x2a40754e;
*((unsigned int *)((unsigned long)context_ptr+0x000060ec+4*7))=0x0aedb4f0;
*((unsigned int *)((unsigned long)context_ptr+0x000060ec+4*8))=0xb7f6998d;
*((unsigned int *)((unsigned long)context_ptr+0x000060ec+4*9))=0x97e544a2;
*((unsigned int *)((unsigned long)context_ptr+0x000060ec+4*10))=0x19dca300;
*((unsigned int *)((unsigned long)context_ptr+0x000060ec+4*11))=0x630a8b31;
*((unsigned int *)((unsigned long)context_ptr+0x000060ec+4*12))=0x19d93e93;
*((unsigned int *)((unsigned long)context_ptr+0x000060ec+4*13))=0xa7d535cd;
*((unsigned int *)((unsigned long)context_ptr+0x000060ec+4*14))=0x29d285be;
*((unsigned int *)((unsigned long)context_ptr+0x000060ec+4*15))=0x154004c0;
*((unsigned int *)((unsigned long)context_ptr+0x000060ec+4*16))=0x00e14673;
*((unsigned int *)((unsigned long)context_ptr+0x00003630))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003630+4*1))=0x00006130;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000630+4*1))=0x000060ec;
*((unsigned int *)((unsigned long)context_ptr+0x00000630+4*2))=0x0000637c;
*((unsigned int *)((unsigned long)context_ptr+0x00000630+4*3))=0x02220043;
*((unsigned int *)((unsigned long)context_ptr+0x00000630+4*4))=0x0e086f4f;
*((unsigned int *)((unsigned long)context_ptr+0x00000630+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000013e&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006154,"\x4f\xf5\xf8\x34\x69\x92\x39\x9f\x42\x61\x71\xc4\xe7\x40\x63\x15\x4a\x52\x69\xe8\x1f\x41\x10\xe1\xdd\x7c\x6c\x0f",28))
printf("strip: 4ff5f8346992399f, Pass\n");
else
printf("strip: 4ff5f8346992399f, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x0000638c))=0x020a0012;
*((unsigned int *)((unsigned long)context_ptr+0x0000638c+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x0000638c+4*2))=0x02020044;
*((unsigned int *)((unsigned long)context_ptr+0x0000638c+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x00006538))=0xf4c732c7;
*((unsigned int *)((unsigned long)context_ptr+0x00006538+4*1))=0xbbc8ceb4;
*((unsigned int *)((unsigned long)context_ptr+0x00006538+4*2))=0x667602b1;
*((unsigned int *)((unsigned long)context_ptr+0x00006538+4*3))=0xba70c4c8;
*((unsigned int *)((unsigned long)context_ptr+0x00006538+4*4))=0x7612dc2c;
*((unsigned int *)((unsigned long)context_ptr+0x00006538+4*5))=0x1e62d653;
*((unsigned int *)((unsigned long)context_ptr+0x00006538+4*6))=0xbae92eaf;
*((unsigned int *)((unsigned long)context_ptr+0x00006538+4*7))=0x69f44fbd;
*((unsigned int *)((unsigned long)context_ptr+0x00006538+4*8))=0xefd3a744;
*((unsigned int *)((unsigned long)context_ptr+0x00006538+4*9))=0xed16bd6a;
*((unsigned int *)((unsigned long)context_ptr+0x00006538+4*10))=0x634b8a02;
*((unsigned int *)((unsigned long)context_ptr+0x00006538+4*11))=0x7ace7e71;
*((unsigned int *)((unsigned long)context_ptr+0x00006538+4*12))=0xd25c0681;
*((unsigned int *)((unsigned long)context_ptr+0x00006538+4*13))=0x476ee04e;
*((unsigned int *)((unsigned long)context_ptr+0x00006538+4*14))=0x349c3d20;
*((unsigned int *)((unsigned long)context_ptr+0x00006538+4*15))=0xf47eddf9;
*((unsigned int *)((unsigned long)context_ptr+0x00006538+4*16))=0x0b78a80e;
*((unsigned int *)((unsigned long)context_ptr+0x00003648))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003648+4*1))=0x0000614c;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000648+4*1))=0x00006538;
*((unsigned int *)((unsigned long)context_ptr+0x00000648+4*2))=0x0000638c;
*((unsigned int *)((unsigned long)context_ptr+0x00000648+4*3))=0x02220044;
*((unsigned int *)((unsigned long)context_ptr+0x00000648+4*4))=0x0afeb8e3;
*((unsigned int *)((unsigned long)context_ptr+0x00000648+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000144&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006474,"\x6a\xe0\x8f\x4f\xa7\x58\x27\x3f\x1a\xdd\x17\xc5\x9a\x77\xbe\x8f\xc0\x74\x5c\x89\x78\x73\xe3\x69\x3e\xc8\xe2\xb1",28))
printf("strip: 6ae08f4fa758273f, Pass\n");
else
printf("strip: 6ae08f4fa758273f, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x0000639c))=0x020a0012;
*((unsigned int *)((unsigned long)context_ptr+0x0000639c+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x0000639c+4*2))=0x02020045;
*((unsigned int *)((unsigned long)context_ptr+0x0000639c+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x0000667c))=0x11e9127d;
*((unsigned int *)((unsigned long)context_ptr+0x0000667c+4*1))=0x538b0007;
*((unsigned int *)((unsigned long)context_ptr+0x0000667c+4*2))=0x12780b10;
*((unsigned int *)((unsigned long)context_ptr+0x0000667c+4*3))=0x074fbe33;
*((unsigned int *)((unsigned long)context_ptr+0x0000667c+4*4))=0xc2a3eef5;
*((unsigned int *)((unsigned long)context_ptr+0x0000667c+4*5))=0xf9a058ed;
*((unsigned int *)((unsigned long)context_ptr+0x0000667c+4*6))=0xea73dc0f;
*((unsigned int *)((unsigned long)context_ptr+0x0000667c+4*7))=0xee840b60;
*((unsigned int *)((unsigned long)context_ptr+0x0000667c+4*8))=0x8dad3d8d;
*((unsigned int *)((unsigned long)context_ptr+0x0000667c+4*9))=0x02383d8d;
*((unsigned int *)((unsigned long)context_ptr+0x0000667c+4*10))=0x73e6c0f8;
*((unsigned int *)((unsigned long)context_ptr+0x0000667c+4*11))=0xdff9793c;
*((unsigned int *)((unsigned long)context_ptr+0x0000667c+4*12))=0x926eadba;
*((unsigned int *)((unsigned long)context_ptr+0x0000667c+4*13))=0xbb113dc2;
*((unsigned int *)((unsigned long)context_ptr+0x0000667c+4*14))=0xb549a97b;
*((unsigned int *)((unsigned long)context_ptr+0x0000667c+4*15))=0xd0019add;
*((unsigned int *)((unsigned long)context_ptr+0x0000667c+4*16))=0x65167739;
*((unsigned int *)((unsigned long)context_ptr+0x0000667c+4*17))=0x000000e4;
*((unsigned int *)((unsigned long)context_ptr+0x00003660))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003660+4*1))=0x0000646c;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000660+4*1))=0x0000667c;
*((unsigned int *)((unsigned long)context_ptr+0x00000660+4*2))=0x0000639c;
*((unsigned int *)((unsigned long)context_ptr+0x00000660+4*3))=0x02220045;
*((unsigned int *)((unsigned long)context_ptr+0x00000660+4*4))=0x07379f4c;
*((unsigned int *)((unsigned long)context_ptr+0x00000660+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000014a&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006490,"\x2a\x68\x3f\xd2\x56\x2f\x92\x14\xa4\xde\xad\xaf\xec\x3a\x93\xde\x98\x7f\x29\x28\x2c\xbf\x8f\x80\x6a\x32\x68\x88",28))
printf("strip: 2a683fd2562f9214, Pass\n");
else
printf("strip: 2a683fd2562f9214, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000063ac))=0x020a0012;
*((unsigned int *)((unsigned long)context_ptr+0x000063ac+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000063ac+4*2))=0x02020046;
*((unsigned int *)((unsigned long)context_ptr+0x000063ac+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x00006168))=0xea38b59e;
*((unsigned int *)((unsigned long)context_ptr+0x00006168+4*1))=0x1698467f;
*((unsigned int *)((unsigned long)context_ptr+0x00006168+4*2))=0x1bd94104;
*((unsigned int *)((unsigned long)context_ptr+0x00006168+4*3))=0x3a93bf88;
*((unsigned int *)((unsigned long)context_ptr+0x00006168+4*4))=0x5a1e697d;
*((unsigned int *)((unsigned long)context_ptr+0x00006168+4*5))=0xd9270cfd;
*((unsigned int *)((unsigned long)context_ptr+0x00006168+4*6))=0xddd81bda;
*((unsigned int *)((unsigned long)context_ptr+0x00006168+4*7))=0x067e2c7c;
*((unsigned int *)((unsigned long)context_ptr+0x00006168+4*8))=0x965431c5;
*((unsigned int *)((unsigned long)context_ptr+0x00006168+4*9))=0x97623da7;
*((unsigned int *)((unsigned long)context_ptr+0x00006168+4*10))=0xa685db44;
*((unsigned int *)((unsigned long)context_ptr+0x00006168+4*11))=0x43d414da;
*((unsigned int *)((unsigned long)context_ptr+0x00006168+4*12))=0xc06eae35;
*((unsigned int *)((unsigned long)context_ptr+0x00006168+4*13))=0xbd7aa017;
*((unsigned int *)((unsigned long)context_ptr+0x00006168+4*14))=0xfea61206;
*((unsigned int *)((unsigned long)context_ptr+0x00006168+4*15))=0xd00d401c;
*((unsigned int *)((unsigned long)context_ptr+0x00006168+4*16))=0x8860b71b;
*((unsigned int *)((unsigned long)context_ptr+0x00006168+4*17))=0x0000355f;
*((unsigned int *)((unsigned long)context_ptr+0x00003678))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003678+4*1))=0x00006488;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000678+4*1))=0x00006168;
*((unsigned int *)((unsigned long)context_ptr+0x00000678+4*2))=0x000063ac;
*((unsigned int *)((unsigned long)context_ptr+0x00000678+4*3))=0x02220046;
*((unsigned int *)((unsigned long)context_ptr+0x00000678+4*4))=0x06057b5b;
*((unsigned int *)((unsigned long)context_ptr+0x00000678+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000150&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000065a4,"\xd6\xd7\xa2\x5b\xa7\x28\x54\xda\xc0\xa2\xe0\x72\xbe\x8b\x6f\x43\xea\x54\xa0\x90\x71\xbc\x2c\x29\xda\x78\xa8\x03",28))
printf("strip: d6d7a25ba72854da, Pass\n");
else
printf("strip: d6d7a25ba72854da, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000064a4))=0x020a0012;
*((unsigned int *)((unsigned long)context_ptr+0x000064a4+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000064a4+4*2))=0x02020047;
*((unsigned int *)((unsigned long)context_ptr+0x000064a4+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x000061b0))=0xb489dbe7;
*((unsigned int *)((unsigned long)context_ptr+0x000061b0+4*1))=0x6f9caa59;
*((unsigned int *)((unsigned long)context_ptr+0x000061b0+4*2))=0xd2ef7b61;
*((unsigned int *)((unsigned long)context_ptr+0x000061b0+4*3))=0xfa66cd01;
*((unsigned int *)((unsigned long)context_ptr+0x000061b0+4*4))=0x447dd921;
*((unsigned int *)((unsigned long)context_ptr+0x000061b0+4*5))=0x6ac98fec;
*((unsigned int *)((unsigned long)context_ptr+0x000061b0+4*6))=0x2d6ae053;
*((unsigned int *)((unsigned long)context_ptr+0x000061b0+4*7))=0xace9bea7;
*((unsigned int *)((unsigned long)context_ptr+0x000061b0+4*8))=0xd1963151;
*((unsigned int *)((unsigned long)context_ptr+0x000061b0+4*9))=0x8fdac51b;
*((unsigned int *)((unsigned long)context_ptr+0x000061b0+4*10))=0x4cbefca0;
*((unsigned int *)((unsigned long)context_ptr+0x000061b0+4*11))=0xeb5c96cc;
*((unsigned int *)((unsigned long)context_ptr+0x000061b0+4*12))=0xe9f89756;
*((unsigned int *)((unsigned long)context_ptr+0x000061b0+4*13))=0xac3f59f3;
*((unsigned int *)((unsigned long)context_ptr+0x000061b0+4*14))=0xd553e233;
*((unsigned int *)((unsigned long)context_ptr+0x000061b0+4*15))=0x405ff1ef;
*((unsigned int *)((unsigned long)context_ptr+0x000061b0+4*16))=0x46fd06a1;
*((unsigned int *)((unsigned long)context_ptr+0x000061b0+4*17))=0x00ed4670;
*((unsigned int *)((unsigned long)context_ptr+0x00003690))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003690+4*1))=0x000061f8;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000690+4*1))=0x000061b0;
*((unsigned int *)((unsigned long)context_ptr+0x00000690+4*2))=0x000064a4;
*((unsigned int *)((unsigned long)context_ptr+0x00000690+4*3))=0x02220047;
*((unsigned int *)((unsigned long)context_ptr+0x00000690+4*4))=0x0983203b;
*((unsigned int *)((unsigned long)context_ptr+0x00000690+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000156&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000064bc,"\x7c\xd2\xe6\x2e\x7c\xf1\x62\x46\x6e\x59\x95\x38\x81\x20\x06\x0b\x14\x82\x4f\x70\xbd\x97\x25\xde\x17\x47\x5a\x78",28))
printf("strip: 7cd2e62e7cf16246, Pass\n");
else
printf("strip: 7cd2e62e7cf16246, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000063bc))=0x020a0012;
*((unsigned int *)((unsigned long)context_ptr+0x000063bc+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000063bc+4*2))=0x02020048;
*((unsigned int *)((unsigned long)context_ptr+0x000063bc+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x0000657c))=0x367f29ca;
*((unsigned int *)((unsigned long)context_ptr+0x0000657c+4*1))=0x7f25c75a;
*((unsigned int *)((unsigned long)context_ptr+0x0000657c+4*2))=0xaf532f7e;
*((unsigned int *)((unsigned long)context_ptr+0x0000657c+4*3))=0x7013d127;
*((unsigned int *)((unsigned long)context_ptr+0x0000657c+4*4))=0x72be6c88;
*((unsigned int *)((unsigned long)context_ptr+0x0000657c+4*5))=0x471bae89;
*((unsigned int *)((unsigned long)context_ptr+0x0000657c+4*6))=0x307fed94;
*((unsigned int *)((unsigned long)context_ptr+0x0000657c+4*7))=0x971f072f;
*((unsigned int *)((unsigned long)context_ptr+0x0000657c+4*8))=0x4c54281d;
*((unsigned int *)((unsigned long)context_ptr+0x0000657c+4*9))=0x578b1ce4;
*((unsigned int *)((unsigned long)context_ptr+0x0000657c+4*10))=0x5625e2a0;
*((unsigned int *)((unsigned long)context_ptr+0x0000657c+4*11))=0x01493fc5;
*((unsigned int *)((unsigned long)context_ptr+0x0000657c+4*12))=0xa39fc740;
*((unsigned int *)((unsigned long)context_ptr+0x0000657c+4*13))=0x06f4b435;
*((unsigned int *)((unsigned long)context_ptr+0x0000657c+4*14))=0xc9826773;
*((unsigned int *)((unsigned long)context_ptr+0x0000657c+4*15))=0xadabf9ba;
*((unsigned int *)((unsigned long)context_ptr+0x0000657c+4*16))=0x326d457b;
*((unsigned int *)((unsigned long)context_ptr+0x0000657c+4*17))=0x155914b8;
*((unsigned int *)((unsigned long)context_ptr+0x000036a8))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x000036a8+4*1))=0x000064b4;
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
*((unsigned int *)((unsigned long)context_ptr+0x000006a8+4*1))=0x0000657c;
*((unsigned int *)((unsigned long)context_ptr+0x000006a8+4*2))=0x000063bc;
*((unsigned int *)((unsigned long)context_ptr+0x000006a8+4*3))=0x02220048;
*((unsigned int *)((unsigned long)context_ptr+0x000006a8+4*4))=0x06aa0cb3;
*((unsigned int *)((unsigned long)context_ptr+0x000006a8+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000015c&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000063cc,"\x7c\x06\xff\xc1\x5a\x4f\x82\x73\x13\x5e\xe9\x97\xef\x76\xe3\x1c\xfe\x6a\x9d\x26\x74\xd5\xd5\x51\x2f\x6a\xf1\x39",28))
printf("strip: 7c06ffc15a4f8273, Pass\n");
else
printf("strip: 7c06ffc15a4f8273, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000064d0))=0x020a0012;
*((unsigned int *)((unsigned long)context_ptr+0x000064d0+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000064d0+4*2))=0x02020049;
*((unsigned int *)((unsigned long)context_ptr+0x000064d0+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x000066c4))=0xb28cffbd;
*((unsigned int *)((unsigned long)context_ptr+0x000066c4+4*1))=0xee240e5f;
*((unsigned int *)((unsigned long)context_ptr+0x000066c4+4*2))=0x0fcc1974;
*((unsigned int *)((unsigned long)context_ptr+0x000066c4+4*3))=0x2cea613a;
*((unsigned int *)((unsigned long)context_ptr+0x000066c4+4*4))=0xf05d82c3;
*((unsigned int *)((unsigned long)context_ptr+0x000066c4+4*5))=0x7da91207;
*((unsigned int *)((unsigned long)context_ptr+0x000066c4+4*6))=0x198b19bd;
*((unsigned int *)((unsigned long)context_ptr+0x000066c4+4*7))=0x29a65c7b;
*((unsigned int *)((unsigned long)context_ptr+0x000066c4+4*8))=0x7f34e986;
*((unsigned int *)((unsigned long)context_ptr+0x000066c4+4*9))=0x770fe56d;
*((unsigned int *)((unsigned long)context_ptr+0x000066c4+4*10))=0x127cfcfe;
*((unsigned int *)((unsigned long)context_ptr+0x000066c4+4*11))=0xdf1be762;
*((unsigned int *)((unsigned long)context_ptr+0x000066c4+4*12))=0x1f4d4cc3;
*((unsigned int *)((unsigned long)context_ptr+0x000066c4+4*13))=0x61be6cb8;
*((unsigned int *)((unsigned long)context_ptr+0x000066c4+4*14))=0x0413fd23;
*((unsigned int *)((unsigned long)context_ptr+0x000066c4+4*15))=0x25153ab0;
*((unsigned int *)((unsigned long)context_ptr+0x000066c4+4*16))=0x480d81ab;
*((unsigned int *)((unsigned long)context_ptr+0x000066c4+4*17))=0xde9812c4;
*((unsigned int *)((unsigned long)context_ptr+0x000066c4+4*18))=0x00000011;
*((unsigned int *)((unsigned long)context_ptr+0x000036c0))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x000036c0+4*1))=0x000063cc;
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
*((unsigned int *)((unsigned long)context_ptr+0x000006c0+4*1))=0x000066c4;
*((unsigned int *)((unsigned long)context_ptr+0x000006c0+4*2))=0x000064d0;
*((unsigned int *)((unsigned long)context_ptr+0x000006c0+4*3))=0x02220049;
*((unsigned int *)((unsigned long)context_ptr+0x000006c0+4*4))=0x0d03ce60;
*((unsigned int *)((unsigned long)context_ptr+0x000006c0+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000162&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006290,"\x05\x6b\x01\xc3\x7b\x05\xcd\xe0\x65\x25\xfb\x51\x38\x46\x86\x5e\x25\xa1\x52\xd6\x74\xe0\xe7\x5f\xed\x02\xeb\x49",28))
printf("strip: 056b01c37b05cde0, Pass\n");
else
printf("strip: 056b01c37b05cde0, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000063e8))=0x020a0012;
*((unsigned int *)((unsigned long)context_ptr+0x000063e8+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000063e8+4*2))=0x0202004a;
*((unsigned int *)((unsigned long)context_ptr+0x000063e8+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x00006214))=0x7557fe59;
*((unsigned int *)((unsigned long)context_ptr+0x00006214+4*1))=0xbeb3bdfc;
*((unsigned int *)((unsigned long)context_ptr+0x00006214+4*2))=0xbb21d69f;
*((unsigned int *)((unsigned long)context_ptr+0x00006214+4*3))=0xbfdb8e60;
*((unsigned int *)((unsigned long)context_ptr+0x00006214+4*4))=0x066cf5a7;
*((unsigned int *)((unsigned long)context_ptr+0x00006214+4*5))=0xd49b68f6;
*((unsigned int *)((unsigned long)context_ptr+0x00006214+4*6))=0xbb3236c8;
*((unsigned int *)((unsigned long)context_ptr+0x00006214+4*7))=0xadbba069;
*((unsigned int *)((unsigned long)context_ptr+0x00006214+4*8))=0xf4a154bc;
*((unsigned int *)((unsigned long)context_ptr+0x00006214+4*9))=0x475ffa00;
*((unsigned int *)((unsigned long)context_ptr+0x00006214+4*10))=0xb3383baf;
*((unsigned int *)((unsigned long)context_ptr+0x00006214+4*11))=0x04e2a696;
*((unsigned int *)((unsigned long)context_ptr+0x00006214+4*12))=0x67d64a65;
*((unsigned int *)((unsigned long)context_ptr+0x00006214+4*13))=0x1f959a5c;
*((unsigned int *)((unsigned long)context_ptr+0x00006214+4*14))=0x55c2efc9;
*((unsigned int *)((unsigned long)context_ptr+0x00006214+4*15))=0xdf2d1855;
*((unsigned int *)((unsigned long)context_ptr+0x00006214+4*16))=0xac2a7230;
*((unsigned int *)((unsigned long)context_ptr+0x00006214+4*17))=0x4e0ecc2f;
*((unsigned int *)((unsigned long)context_ptr+0x00006214+4*18))=0x00008929;
*((unsigned int *)((unsigned long)context_ptr+0x000036d8))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x000036d8+4*1))=0x000065c4;
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
*((unsigned int *)((unsigned long)context_ptr+0x000006d8+4*1))=0x00006214;
*((unsigned int *)((unsigned long)context_ptr+0x000006d8+4*2))=0x000063e8;
*((unsigned int *)((unsigned long)context_ptr+0x000006d8+4*3))=0x0222004a;
*((unsigned int *)((unsigned long)context_ptr+0x000006d8+4*4))=0x092747f8;
*((unsigned int *)((unsigned long)context_ptr+0x000006d8+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000168&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000062e8,"\x45\xe2\xbd\x6f\x4b\x90\x3f\xe8\x59\x81\x50\x03\xc8\x30\x7e\x16\xea\xd8\xd8\x8c\x01\xf4\xcc\x10\xd4\xa4\x5b\xdf",28))
printf("strip: 45e2bd6f4b903fe8, Pass\n");
else
printf("strip: 45e2bd6f4b903fe8, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000064e0))=0x020a0012;
*((unsigned int *)((unsigned long)context_ptr+0x000064e0+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000064e0+4*2))=0x0202004b;
*((unsigned int *)((unsigned long)context_ptr+0x000064e0+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x00006260))=0x953ee0f4;
*((unsigned int *)((unsigned long)context_ptr+0x00006260+4*1))=0xba9fef49;
*((unsigned int *)((unsigned long)context_ptr+0x00006260+4*2))=0x26edceee;
*((unsigned int *)((unsigned long)context_ptr+0x00006260+4*3))=0xc4d8df42;
*((unsigned int *)((unsigned long)context_ptr+0x00006260+4*4))=0x1979dab8;
*((unsigned int *)((unsigned long)context_ptr+0x00006260+4*5))=0x8f9b3fba;
*((unsigned int *)((unsigned long)context_ptr+0x00006260+4*6))=0x1862a763;
*((unsigned int *)((unsigned long)context_ptr+0x00006260+4*7))=0x8f48d8dc;
*((unsigned int *)((unsigned long)context_ptr+0x00006260+4*8))=0x6274bc22;
*((unsigned int *)((unsigned long)context_ptr+0x00006260+4*9))=0xced7d3ee;
*((unsigned int *)((unsigned long)context_ptr+0x00006260+4*10))=0xeb51e7ba;
*((unsigned int *)((unsigned long)context_ptr+0x00006260+4*11))=0x7858c06a;
*((unsigned int *)((unsigned long)context_ptr+0x00006260+4*12))=0x0d521d3f;
*((unsigned int *)((unsigned long)context_ptr+0x00006260+4*13))=0x93135350;
*((unsigned int *)((unsigned long)context_ptr+0x00006260+4*14))=0x3f1a9cd7;
*((unsigned int *)((unsigned long)context_ptr+0x00006260+4*15))=0x6bba4f4b;
*((unsigned int *)((unsigned long)context_ptr+0x00006260+4*16))=0xfd39b210;
*((unsigned int *)((unsigned long)context_ptr+0x00006260+4*17))=0x4482d105;
*((unsigned int *)((unsigned long)context_ptr+0x00006260+4*18))=0x00493427;
*((unsigned int *)((unsigned long)context_ptr+0x000036f0))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x000036f0+4*1))=0x000065e0;
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
*((unsigned int *)((unsigned long)context_ptr+0x000006f0+4*1))=0x00006260;
*((unsigned int *)((unsigned long)context_ptr+0x000006f0+4*2))=0x000064e0;
*((unsigned int *)((unsigned long)context_ptr+0x000006f0+4*3))=0x0222004b;
*((unsigned int *)((unsigned long)context_ptr+0x000006f0+4*4))=0x038d0b72;
*((unsigned int *)((unsigned long)context_ptr+0x000006f0+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000016e&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000063f8,"\x93\x17\x55\xde\x08\x49\x5f\xfb\xf5\x46\xaf\xba\xbe\x24\x0b\x6a\x7f\x28\xc0\x9f\xeb\x7f\x32\x12\x58\xad\x39\xaf",28))
printf("strip: 931755de08495ffb, Pass\n");
else
printf("strip: 931755de08495ffb, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006018))=0x020a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006018+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006018+4*2))=0x0202004c;
*((unsigned int *)((unsigned long)context_ptr+0x00006018+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x000062ac))=0x82e3ed07;
*((unsigned int *)((unsigned long)context_ptr+0x000062ac+4*1))=0xc8d51969;
*((unsigned int *)((unsigned long)context_ptr+0x000062ac+4*2))=0xd57ecda8;
*((unsigned int *)((unsigned long)context_ptr+0x000062ac+4*3))=0x8e8c112c;
*((unsigned int *)((unsigned long)context_ptr+0x000062ac+4*4))=0x1e643a94;
*((unsigned int *)((unsigned long)context_ptr+0x000062ac+4*5))=0xf7a6d8d0;
*((unsigned int *)((unsigned long)context_ptr+0x000062ac+4*6))=0xe5ceefa0;
*((unsigned int *)((unsigned long)context_ptr+0x000062ac+4*7))=0xa325185f;
*((unsigned int *)((unsigned long)context_ptr+0x000062ac+4*8))=0xadca71ca;
*((unsigned int *)((unsigned long)context_ptr+0x000062ac+4*9))=0x44333034;
*((unsigned int *)((unsigned long)context_ptr+0x000062ac+4*10))=0x923c8b40;
*((unsigned int *)((unsigned long)context_ptr+0x000062ac+4*11))=0xc3a9cc9f;
*((unsigned int *)((unsigned long)context_ptr+0x000062ac+4*12))=0xa054077c;
*((unsigned int *)((unsigned long)context_ptr+0x000062ac+4*13))=0x082eeb7b;
*((unsigned int *)((unsigned long)context_ptr+0x000062ac+4*14))=0x8ad83870;
*((unsigned int *)((unsigned long)context_ptr+0x000062ac+4*15))=0x673ba5b7;
*((unsigned int *)((unsigned long)context_ptr+0x000062ac+4*16))=0xceee3dd8;
*((unsigned int *)((unsigned long)context_ptr+0x000062ac+4*17))=0xb7828a82;
*((unsigned int *)((unsigned long)context_ptr+0x000062ac+4*18))=0xe486d0a3;
*((unsigned int *)((unsigned long)context_ptr+0x00003708))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003708+4*1))=0x000063f8;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000708+4*1))=0x000062ac;
*((unsigned int *)((unsigned long)context_ptr+0x00000708+4*2))=0x00006018;
*((unsigned int *)((unsigned long)context_ptr+0x00000708+4*3))=0x0222004c;
*((unsigned int *)((unsigned long)context_ptr+0x00000708+4*4))=0x0e165891;
*((unsigned int *)((unsigned long)context_ptr+0x00000708+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000174&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006038,"\x61\xae\x21\xc2\x31\xa8\x83\xd4\x36\x09\x70\x6e\x98\xd0\x0a\xe1\x69\xc5\x4c\x00\x5e\x18\xa7\x7c\x57\x76\xe4\xcd",28))
printf("strip: 61ae21c231a883d4, Pass\n");
else
printf("strip: 61ae21c231a883d4, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006008))=0x020a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006008+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006008+4*2))=0x0202004d;
*((unsigned int *)((unsigned long)context_ptr+0x00006008+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x00006710))=0xd3756462;
*((unsigned int *)((unsigned long)context_ptr+0x00006710+4*1))=0x8e341b4c;
*((unsigned int *)((unsigned long)context_ptr+0x00006710+4*2))=0x8420f867;
*((unsigned int *)((unsigned long)context_ptr+0x00006710+4*3))=0xd3e449ce;
*((unsigned int *)((unsigned long)context_ptr+0x00006710+4*4))=0xc86dc26b;
*((unsigned int *)((unsigned long)context_ptr+0x00006710+4*5))=0x49689056;
*((unsigned int *)((unsigned long)context_ptr+0x00006710+4*6))=0x3cb76a74;
*((unsigned int *)((unsigned long)context_ptr+0x00006710+4*7))=0x65c0bff2;
*((unsigned int *)((unsigned long)context_ptr+0x00006710+4*8))=0x79e490e5;
*((unsigned int *)((unsigned long)context_ptr+0x00006710+4*9))=0x393544f6;
*((unsigned int *)((unsigned long)context_ptr+0x00006710+4*10))=0x9d0bc75c;
*((unsigned int *)((unsigned long)context_ptr+0x00006710+4*11))=0x654b7d4f;
*((unsigned int *)((unsigned long)context_ptr+0x00006710+4*12))=0x58bd1f6b;
*((unsigned int *)((unsigned long)context_ptr+0x00006710+4*13))=0xb937d118;
*((unsigned int *)((unsigned long)context_ptr+0x00006710+4*14))=0xf8f20998;
*((unsigned int *)((unsigned long)context_ptr+0x00006710+4*15))=0x31b217bb;
*((unsigned int *)((unsigned long)context_ptr+0x00006710+4*16))=0xd3417e76;
*((unsigned int *)((unsigned long)context_ptr+0x00006710+4*17))=0xc09a7a1f;
*((unsigned int *)((unsigned long)context_ptr+0x00006710+4*18))=0x10f892dc;
*((unsigned int *)((unsigned long)context_ptr+0x00006710+4*19))=0x00000056;
*((unsigned int *)((unsigned long)context_ptr+0x00003720))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003720+4*1))=0x00006038;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000720+4*1))=0x00006710;
*((unsigned int *)((unsigned long)context_ptr+0x00000720+4*2))=0x00006008;
*((unsigned int *)((unsigned long)context_ptr+0x00000720+4*3))=0x0222004d;
*((unsigned int *)((unsigned long)context_ptr+0x00000720+4*4))=0x069b290f;
*((unsigned int *)((unsigned long)context_ptr+0x00000720+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000017a&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006414,"\x83\x19\x82\x14\xd3\x7a\xff\xaf\x8d\x35\x25\x4f\x25\xc4\x5e\x20\xd0\x9b\x50\x28\x6b\x56\x76\x7d\x6d\x89\xe9\x41",28))
printf("strip: 83198214d37affaf, Pass\n");
else
printf("strip: 83198214d37affaf, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006028))=0x020a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006028+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006028+4*2))=0x0202004e;
*((unsigned int *)((unsigned long)context_ptr+0x00006028+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x000065fc))=0x093f0c2c;
*((unsigned int *)((unsigned long)context_ptr+0x000065fc+4*1))=0x49803261;
*((unsigned int *)((unsigned long)context_ptr+0x000065fc+4*2))=0x9dc99b88;
*((unsigned int *)((unsigned long)context_ptr+0x000065fc+4*3))=0xe7e7ae67;
*((unsigned int *)((unsigned long)context_ptr+0x000065fc+4*4))=0x949c1ea6;
*((unsigned int *)((unsigned long)context_ptr+0x000065fc+4*5))=0xcf1990cc;
*((unsigned int *)((unsigned long)context_ptr+0x000065fc+4*6))=0x695a9475;
*((unsigned int *)((unsigned long)context_ptr+0x000065fc+4*7))=0xd288810b;
*((unsigned int *)((unsigned long)context_ptr+0x000065fc+4*8))=0xdcf9315c;
*((unsigned int *)((unsigned long)context_ptr+0x000065fc+4*9))=0x1e26f545;
*((unsigned int *)((unsigned long)context_ptr+0x000065fc+4*10))=0xf70207d0;
*((unsigned int *)((unsigned long)context_ptr+0x000065fc+4*11))=0x9245bc14;
*((unsigned int *)((unsigned long)context_ptr+0x000065fc+4*12))=0x9d1a247a;
*((unsigned int *)((unsigned long)context_ptr+0x000065fc+4*13))=0xcd2f8d36;
*((unsigned int *)((unsigned long)context_ptr+0x000065fc+4*14))=0x254ae392;
*((unsigned int *)((unsigned long)context_ptr+0x000065fc+4*15))=0x36309df5;
*((unsigned int *)((unsigned long)context_ptr+0x000065fc+4*16))=0x4cc4b22c;
*((unsigned int *)((unsigned long)context_ptr+0x000065fc+4*17))=0xaee12738;
*((unsigned int *)((unsigned long)context_ptr+0x000065fc+4*18))=0x1c17d706;
*((unsigned int *)((unsigned long)context_ptr+0x000065fc+4*19))=0x00008fb4;
*((unsigned int *)((unsigned long)context_ptr+0x00003738))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003738+4*1))=0x00006414;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000738+4*1))=0x000065fc;
*((unsigned int *)((unsigned long)context_ptr+0x00000738+4*2))=0x00006028;
*((unsigned int *)((unsigned long)context_ptr+0x00000738+4*3))=0x0222004e;
*((unsigned int *)((unsigned long)context_ptr+0x00000738+4*4))=0x03df32aa;
*((unsigned int *)((unsigned long)context_ptr+0x00000738+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000180&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006430,"\xf3\x8d\x0c\xf2\x04\xbe\x0e\x00\xa7\xe8\xaa\xd0\xec\xd6\xed\x4d\x14\x7a\xfe\x89\x56\x93\x62\xfd\xc6\xba\x1c\xf7",28))
printf("strip: f38d0cf204be0e00, Pass\n");
else
printf("strip: f38d0cf204be0e00, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006054))=0x020a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006054+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006054+4*2))=0x0202004f;
*((unsigned int *)((unsigned long)context_ptr+0x00006054+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x00006760))=0x4a7b2b94;
*((unsigned int *)((unsigned long)context_ptr+0x00006760+4*1))=0x06951e8c;
*((unsigned int *)((unsigned long)context_ptr+0x00006760+4*2))=0xc22ef39b;
*((unsigned int *)((unsigned long)context_ptr+0x00006760+4*3))=0x98d7abca;
*((unsigned int *)((unsigned long)context_ptr+0x00006760+4*4))=0xb6ea52b7;
*((unsigned int *)((unsigned long)context_ptr+0x00006760+4*5))=0x9aae57a8;
*((unsigned int *)((unsigned long)context_ptr+0x00006760+4*6))=0x6fe08e70;
*((unsigned int *)((unsigned long)context_ptr+0x00006760+4*7))=0xd818a955;
*((unsigned int *)((unsigned long)context_ptr+0x00006760+4*8))=0xc5deb5e5;
*((unsigned int *)((unsigned long)context_ptr+0x00006760+4*9))=0xba8ca432;
*((unsigned int *)((unsigned long)context_ptr+0x00006760+4*10))=0x2c5ac573;
*((unsigned int *)((unsigned long)context_ptr+0x00006760+4*11))=0xdcc23b09;
*((unsigned int *)((unsigned long)context_ptr+0x00006760+4*12))=0x74da56b6;
*((unsigned int *)((unsigned long)context_ptr+0x00006760+4*13))=0x3117c5f6;
*((unsigned int *)((unsigned long)context_ptr+0x00006760+4*14))=0x64122cf6;
*((unsigned int *)((unsigned long)context_ptr+0x00006760+4*15))=0xca1580ba;
*((unsigned int *)((unsigned long)context_ptr+0x00006760+4*16))=0x032995ab;
*((unsigned int *)((unsigned long)context_ptr+0x00006760+4*17))=0x922f2fd7;
*((unsigned int *)((unsigned long)context_ptr+0x00006760+4*18))=0xe82d0a9b;
*((unsigned int *)((unsigned long)context_ptr+0x00006760+4*19))=0x00b0de69;
*((unsigned int *)((unsigned long)context_ptr+0x00003750))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003750+4*1))=0x00006430;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000750+4*1))=0x00006760;
*((unsigned int *)((unsigned long)context_ptr+0x00000750+4*2))=0x00006054;
*((unsigned int *)((unsigned long)context_ptr+0x00000750+4*3))=0x0222004f;
*((unsigned int *)((unsigned long)context_ptr+0x00000750+4*4))=0x0a4784cc;
*((unsigned int *)((unsigned long)context_ptr+0x00000750+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000186&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006344,"\x62\x40\x91\x5b\xff\x89\x80\xe0\x08\x90\xe3\x5f\xee\xd8\x25\x01\x9f\xff\x83\x5e\x5b\x3b\x79\x64\x9d\x3b\x99\xea",28))
printf("strip: 6240915bff8980e0, Pass\n");
else
printf("strip: 6240915bff8980e0, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x0000644c))=0x020a0012;
*((unsigned int *)((unsigned long)context_ptr+0x0000644c+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x0000644c+4*2))=0x02020050;
*((unsigned int *)((unsigned long)context_ptr+0x0000644c+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x000062f8))=0x73de623c;
*((unsigned int *)((unsigned long)context_ptr+0x000062f8+4*1))=0x4dd7ca13;
*((unsigned int *)((unsigned long)context_ptr+0x000062f8+4*2))=0xbad7a28c;
*((unsigned int *)((unsigned long)context_ptr+0x000062f8+4*3))=0xbbbb7e9c;
*((unsigned int *)((unsigned long)context_ptr+0x000062f8+4*4))=0x3a2ca6c0;
*((unsigned int *)((unsigned long)context_ptr+0x000062f8+4*5))=0x51c918e5;
*((unsigned int *)((unsigned long)context_ptr+0x000062f8+4*6))=0xd46ef52b;
*((unsigned int *)((unsigned long)context_ptr+0x000062f8+4*7))=0x0ddb6527;
*((unsigned int *)((unsigned long)context_ptr+0x000062f8+4*8))=0x9f2efc86;
*((unsigned int *)((unsigned long)context_ptr+0x000062f8+4*9))=0x54f9a9b0;
*((unsigned int *)((unsigned long)context_ptr+0x000062f8+4*10))=0xe92c3b5a;
*((unsigned int *)((unsigned long)context_ptr+0x000062f8+4*11))=0x3e179bd3;
*((unsigned int *)((unsigned long)context_ptr+0x000062f8+4*12))=0xac4a8633;
*((unsigned int *)((unsigned long)context_ptr+0x000062f8+4*13))=0xbf493569;
*((unsigned int *)((unsigned long)context_ptr+0x000062f8+4*14))=0x053f2f78;
*((unsigned int *)((unsigned long)context_ptr+0x000062f8+4*15))=0x6d898ea1;
*((unsigned int *)((unsigned long)context_ptr+0x000062f8+4*16))=0x0509b846;
*((unsigned int *)((unsigned long)context_ptr+0x000062f8+4*17))=0xf7af7acb;
*((unsigned int *)((unsigned long)context_ptr+0x000062f8+4*18))=0x5eb638b8;
*((unsigned int *)((unsigned long)context_ptr+0x000062f8+4*19))=0x5f5d4d6a;
*((unsigned int *)((unsigned long)context_ptr+0x00003768))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003768+4*1))=0x0000664c;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000768+4*1))=0x000062f8;
*((unsigned int *)((unsigned long)context_ptr+0x00000768+4*2))=0x0000644c;
*((unsigned int *)((unsigned long)context_ptr+0x00000768+4*3))=0x02220050;
*((unsigned int *)((unsigned long)context_ptr+0x00000768+4*4))=0x0d91cedb;
*((unsigned int *)((unsigned long)context_ptr+0x00000768+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000018c&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006360,"\xbb\xf8\xa7\x2f\x36\x1c\x66\x41\x2b\xe9\x41\x2e\x31\xff\x2d\x2f\x3b\x77\xa6\xee\x3b\x3d\xce\x99\x0e\x48\x12\x68",28))
printf("strip: bbf8a72f361c6641, Pass\n");
else
printf("strip: bbf8a72f361c6641, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x0000645c))=0x020a0012;
*((unsigned int *)((unsigned long)context_ptr+0x0000645c+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x0000645c+4*2))=0x02020051;
*((unsigned int *)((unsigned long)context_ptr+0x0000645c+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x00006064))=0x075f483f;
*((unsigned int *)((unsigned long)context_ptr+0x00006064+4*1))=0x563864cf;
*((unsigned int *)((unsigned long)context_ptr+0x00006064+4*2))=0xea5c5d1e;
*((unsigned int *)((unsigned long)context_ptr+0x00006064+4*3))=0x7f3e6795;
*((unsigned int *)((unsigned long)context_ptr+0x00006064+4*4))=0xe157a80a;
*((unsigned int *)((unsigned long)context_ptr+0x00006064+4*5))=0x195f0fe8;
*((unsigned int *)((unsigned long)context_ptr+0x00006064+4*6))=0xb5c0d7b8;
*((unsigned int *)((unsigned long)context_ptr+0x00006064+4*7))=0x5f35c14a;
*((unsigned int *)((unsigned long)context_ptr+0x00006064+4*8))=0x19cedff8;
*((unsigned int *)((unsigned long)context_ptr+0x00006064+4*9))=0x25d2aa6c;
*((unsigned int *)((unsigned long)context_ptr+0x00006064+4*10))=0x04a2f6c9;
*((unsigned int *)((unsigned long)context_ptr+0x00006064+4*11))=0x231344c5;
*((unsigned int *)((unsigned long)context_ptr+0x00006064+4*12))=0x61092944;
*((unsigned int *)((unsigned long)context_ptr+0x00006064+4*13))=0x05c56211;
*((unsigned int *)((unsigned long)context_ptr+0x00006064+4*14))=0x92de43be;
*((unsigned int *)((unsigned long)context_ptr+0x00006064+4*15))=0x6e19e892;
*((unsigned int *)((unsigned long)context_ptr+0x00006064+4*16))=0xd8086135;
*((unsigned int *)((unsigned long)context_ptr+0x00006064+4*17))=0x9f81bd01;
*((unsigned int *)((unsigned long)context_ptr+0x00006064+4*18))=0xd7490202;
*((unsigned int *)((unsigned long)context_ptr+0x00006064+4*19))=0xaff14ff0;
*((unsigned int *)((unsigned long)context_ptr+0x00006064+4*20))=0x0000006c;
*((unsigned int *)((unsigned long)context_ptr+0x00003780))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003780+4*1))=0x00006348;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000780+4*1))=0x00006064;
*((unsigned int *)((unsigned long)context_ptr+0x00000780+4*2))=0x0000645c;
*((unsigned int *)((unsigned long)context_ptr+0x00000780+4*3))=0x02220051;
*((unsigned int *)((unsigned long)context_ptr+0x00000780+4*4))=0x05e0e028;
*((unsigned int *)((unsigned long)context_ptr+0x00000780+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000192&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006130,"\xab\x87\xa5\xdf\xae\xe6\xfd\x87\x99\xa1\x85\xdd\x43\xe4\xd2\x4b\xb8\xdf\xbf\x77\x12\x9f\x2c\xb1\xa0\x40\x70\x30",28))
printf("strip: ab87a5dfaee6fd87, Pass\n");
else
printf("strip: ab87a5dfaee6fd87, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006668))=0x020a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006668+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006668+4*2))=0x02020052;
*((unsigned int *)((unsigned long)context_ptr+0x00006668+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x000060b8))=0x637d2f61;
*((unsigned int *)((unsigned long)context_ptr+0x000060b8+4*1))=0x7b8a6840;
*((unsigned int *)((unsigned long)context_ptr+0x000060b8+4*2))=0xac81dd2d;
*((unsigned int *)((unsigned long)context_ptr+0x000060b8+4*3))=0x234d6c70;
*((unsigned int *)((unsigned long)context_ptr+0x000060b8+4*4))=0xc207ff89;
*((unsigned int *)((unsigned long)context_ptr+0x000060b8+4*5))=0x3b829784;
*((unsigned int *)((unsigned long)context_ptr+0x000060b8+4*6))=0x978b77b7;
*((unsigned int *)((unsigned long)context_ptr+0x000060b8+4*7))=0xb7c60b91;
*((unsigned int *)((unsigned long)context_ptr+0x000060b8+4*8))=0x6ead3828;
*((unsigned int *)((unsigned long)context_ptr+0x000060b8+4*9))=0xca9c09fe;
*((unsigned int *)((unsigned long)context_ptr+0x000060b8+4*10))=0x513ef34f;
*((unsigned int *)((unsigned long)context_ptr+0x000060b8+4*11))=0xb2a51267;
*((unsigned int *)((unsigned long)context_ptr+0x000060b8+4*12))=0x975316c8;
*((unsigned int *)((unsigned long)context_ptr+0x000060b8+4*13))=0xde77a788;
*((unsigned int *)((unsigned long)context_ptr+0x000060b8+4*14))=0x230cc7ec;
*((unsigned int *)((unsigned long)context_ptr+0x000060b8+4*15))=0x6500e42d;
*((unsigned int *)((unsigned long)context_ptr+0x000060b8+4*16))=0x88d1f0f6;
*((unsigned int *)((unsigned long)context_ptr+0x000060b8+4*17))=0xb09bbb58;
*((unsigned int *)((unsigned long)context_ptr+0x000060b8+4*18))=0xdd618090;
*((unsigned int *)((unsigned long)context_ptr+0x000060b8+4*19))=0x95a09e0f;
*((unsigned int *)((unsigned long)context_ptr+0x000060b8+4*20))=0x00006d2e;
*((unsigned int *)((unsigned long)context_ptr+0x00003798))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003798+4*1))=0x00006364;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000798+4*1))=0x000060b8;
*((unsigned int *)((unsigned long)context_ptr+0x00000798+4*2))=0x00006668;
*((unsigned int *)((unsigned long)context_ptr+0x00000798+4*3))=0x02220052;
*((unsigned int *)((unsigned long)context_ptr+0x00000798+4*4))=0x07e58c55;
*((unsigned int *)((unsigned long)context_ptr+0x00000798+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000198&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x0000614c,"\x87\x09\x8f\x1b\x5c\xe1\xa7\x22\x3a\xfa\x2b\x04\xe6\x02\x43\x87\x5b\x18\x2a\x30\x9a\x2a\xd0\x62\xc6\xba\x85\xf1",28))
printf("strip: 87098f1b5ce1a722, Pass\n");
else
printf("strip: 87098f1b5ce1a722, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006380))=0x020a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006380+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006380+4*2))=0x02020053;
*((unsigned int *)((unsigned long)context_ptr+0x00006380+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x0000610c))=0x0404b4c9;
*((unsigned int *)((unsigned long)context_ptr+0x0000610c+4*1))=0x259e3ad5;
*((unsigned int *)((unsigned long)context_ptr+0x0000610c+4*2))=0x9b577c2d;
*((unsigned int *)((unsigned long)context_ptr+0x0000610c+4*3))=0xb94d795a;
*((unsigned int *)((unsigned long)context_ptr+0x0000610c+4*4))=0x37800608;
*((unsigned int *)((unsigned long)context_ptr+0x0000610c+4*5))=0x692182a8;
*((unsigned int *)((unsigned long)context_ptr+0x0000610c+4*6))=0x27a865d0;
*((unsigned int *)((unsigned long)context_ptr+0x0000610c+4*7))=0x9f319930;
*((unsigned int *)((unsigned long)context_ptr+0x0000610c+4*8))=0xc20389d8;
*((unsigned int *)((unsigned long)context_ptr+0x0000610c+4*9))=0x28496846;
*((unsigned int *)((unsigned long)context_ptr+0x0000610c+4*10))=0x5f0abca5;
*((unsigned int *)((unsigned long)context_ptr+0x0000610c+4*11))=0x03f9d6bc;
*((unsigned int *)((unsigned long)context_ptr+0x0000610c+4*12))=0xf30e081c;
*((unsigned int *)((unsigned long)context_ptr+0x0000610c+4*13))=0x9e451539;
*((unsigned int *)((unsigned long)context_ptr+0x0000610c+4*14))=0xc4e3e2e9;
*((unsigned int *)((unsigned long)context_ptr+0x0000610c+4*15))=0x247a36ca;
*((unsigned int *)((unsigned long)context_ptr+0x0000610c+4*16))=0xa4af6f55;
*((unsigned int *)((unsigned long)context_ptr+0x0000610c+4*17))=0xb0b75374;
*((unsigned int *)((unsigned long)context_ptr+0x0000610c+4*18))=0x95e60382;
*((unsigned int *)((unsigned long)context_ptr+0x0000610c+4*19))=0x09216230;
*((unsigned int *)((unsigned long)context_ptr+0x0000610c+4*20))=0x007667c5;
*((unsigned int *)((unsigned long)context_ptr+0x000037b0))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x000037b0+4*1))=0x000064f0;
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
*((unsigned int *)((unsigned long)context_ptr+0x000007b0+4*1))=0x0000610c;
*((unsigned int *)((unsigned long)context_ptr+0x000007b0+4*2))=0x00006380;
*((unsigned int *)((unsigned long)context_ptr+0x000007b0+4*3))=0x02220053;
*((unsigned int *)((unsigned long)context_ptr+0x000007b0+4*4))=0x0718f9ab;
*((unsigned int *)((unsigned long)context_ptr+0x000007b0+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000019e&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x0000646c,"\xfb\xc0\x56\xc0\x0d\x9d\xf9\xd4\x36\xdd\x6b\xe3\xf9\x3a\xab\xac\xcc\xab\xe0\xa7\x83\x60\x3d\x2a\x5c\x68\x35\x28",28))
printf("strip: fbc056c00d9df9d4, Pass\n");
else
printf("strip: fbc056c00d9df9d4, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006390))=0x020a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006390+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006390+4*2))=0x02020054;
*((unsigned int *)((unsigned long)context_ptr+0x00006390+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x0000650c))=0x517692ee;
*((unsigned int *)((unsigned long)context_ptr+0x0000650c+4*1))=0x5405c5c1;
*((unsigned int *)((unsigned long)context_ptr+0x0000650c+4*2))=0x568c3a50;
*((unsigned int *)((unsigned long)context_ptr+0x0000650c+4*3))=0x5526c028;
*((unsigned int *)((unsigned long)context_ptr+0x0000650c+4*4))=0x6d59c6e4;
*((unsigned int *)((unsigned long)context_ptr+0x0000650c+4*5))=0xc5fab35d;
*((unsigned int *)((unsigned long)context_ptr+0x0000650c+4*6))=0xf2600a00;
*((unsigned int *)((unsigned long)context_ptr+0x0000650c+4*7))=0x83d66294;
*((unsigned int *)((unsigned long)context_ptr+0x0000650c+4*8))=0xb03d8cbf;
*((unsigned int *)((unsigned long)context_ptr+0x0000650c+4*9))=0x029c1e34;
*((unsigned int *)((unsigned long)context_ptr+0x0000650c+4*10))=0x68654376;
*((unsigned int *)((unsigned long)context_ptr+0x0000650c+4*11))=0x4387176d;
*((unsigned int *)((unsigned long)context_ptr+0x0000650c+4*12))=0x9ed917e9;
*((unsigned int *)((unsigned long)context_ptr+0x0000650c+4*13))=0x8f8a8959;
*((unsigned int *)((unsigned long)context_ptr+0x0000650c+4*14))=0xbc1190e2;
*((unsigned int *)((unsigned long)context_ptr+0x0000650c+4*15))=0x2a7fc815;
*((unsigned int *)((unsigned long)context_ptr+0x0000650c+4*16))=0x9fd6ac50;
*((unsigned int *)((unsigned long)context_ptr+0x0000650c+4*17))=0x269730c5;
*((unsigned int *)((unsigned long)context_ptr+0x0000650c+4*18))=0xaf01faea;
*((unsigned int *)((unsigned long)context_ptr+0x0000650c+4*19))=0x43b32d14;
*((unsigned int *)((unsigned long)context_ptr+0x0000650c+4*20))=0x2120d30b;
*((unsigned int *)((unsigned long)context_ptr+0x000037c8))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x000037c8+4*1))=0x0000646c;
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
*((unsigned int *)((unsigned long)context_ptr+0x000007c8+4*1))=0x0000650c;
*((unsigned int *)((unsigned long)context_ptr+0x000007c8+4*2))=0x00006390;
*((unsigned int *)((unsigned long)context_ptr+0x000007c8+4*3))=0x02220054;
*((unsigned int *)((unsigned long)context_ptr+0x000007c8+4*4))=0x0b991878;
*((unsigned int *)((unsigned long)context_ptr+0x000007c8+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000001a4&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006488,"\xa2\x0c\x64\x94\xc7\x27\x41\x00\x0a\xe1\xdd\xab\x38\xe0\x9f\x74\x96\xe5\xe1\x4f\xda\xd0\x14\xef\x66\x2b\xe9\x6d",28))
printf("strip: a20c6494c7274100, Pass\n");
else
printf("strip: a20c6494c7274100, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000063a0))=0x020a0012;
*((unsigned int *)((unsigned long)context_ptr+0x000063a0+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000063a0+4*2))=0x02020055;
*((unsigned int *)((unsigned long)context_ptr+0x000063a0+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x000067b0))=0xfa6e9679;
*((unsigned int *)((unsigned long)context_ptr+0x000067b0+4*1))=0x152d9ca1;
*((unsigned int *)((unsigned long)context_ptr+0x000067b0+4*2))=0x4a30440c;
*((unsigned int *)((unsigned long)context_ptr+0x000067b0+4*3))=0xb4ecb397;
*((unsigned int *)((unsigned long)context_ptr+0x000067b0+4*4))=0xd2da4aa1;
*((unsigned int *)((unsigned long)context_ptr+0x000067b0+4*5))=0xcbbbbbc4;
*((unsigned int *)((unsigned long)context_ptr+0x000067b0+4*6))=0xf3494390;
*((unsigned int *)((unsigned long)context_ptr+0x000067b0+4*7))=0x8c09762a;
*((unsigned int *)((unsigned long)context_ptr+0x000067b0+4*8))=0x4d08477c;
*((unsigned int *)((unsigned long)context_ptr+0x000067b0+4*9))=0x1c07c58e;
*((unsigned int *)((unsigned long)context_ptr+0x000067b0+4*10))=0xb6cccd75;
*((unsigned int *)((unsigned long)context_ptr+0x000067b0+4*11))=0x0d9cf14f;
*((unsigned int *)((unsigned long)context_ptr+0x000067b0+4*12))=0xe50b7e46;
*((unsigned int *)((unsigned long)context_ptr+0x000067b0+4*13))=0x4106876c;
*((unsigned int *)((unsigned long)context_ptr+0x000067b0+4*14))=0xae83945d;
*((unsigned int *)((unsigned long)context_ptr+0x000067b0+4*15))=0x9a63852d;
*((unsigned int *)((unsigned long)context_ptr+0x000067b0+4*16))=0x8f5d57ba;
*((unsigned int *)((unsigned long)context_ptr+0x000067b0+4*17))=0xb8bea0d3;
*((unsigned int *)((unsigned long)context_ptr+0x000067b0+4*18))=0x9f26a195;
*((unsigned int *)((unsigned long)context_ptr+0x000067b0+4*19))=0xb60010ba;
*((unsigned int *)((unsigned long)context_ptr+0x000067b0+4*20))=0xb59006d8;
*((unsigned int *)((unsigned long)context_ptr+0x000067b0+4*21))=0x000000e3;
*((unsigned int *)((unsigned long)context_ptr+0x000037e0))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x000037e0+4*1))=0x00006488;
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
*((unsigned int *)((unsigned long)context_ptr+0x000007e0+4*1))=0x000067b0;
*((unsigned int *)((unsigned long)context_ptr+0x000007e0+4*2))=0x000063a0;
*((unsigned int *)((unsigned long)context_ptr+0x000007e0+4*3))=0x02220055;
*((unsigned int *)((unsigned long)context_ptr+0x000007e0+4*4))=0x094b26c4;
*((unsigned int *)((unsigned long)context_ptr+0x000007e0+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000001aa&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000061f8,"\x06\xe7\xf1\x68\xa8\x00\x80\xb8\x04\x81\xf4\x9a\xb7\x0f\x59\x6c\x0f\x9b\x57\xae\x7a\xd5\xe9\xde\x65\x18\x98\x61",28))
printf("strip: 06e7f168a80080b8, Pass\n");
else
printf("strip: 06e7f168a80080b8, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000064a4))=0x020a0012;
*((unsigned int *)((unsigned long)context_ptr+0x000064a4+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000064a4+4*2))=0x02020056;
*((unsigned int *)((unsigned long)context_ptr+0x000064a4+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x00006160))=0x87ce8d02;
*((unsigned int *)((unsigned long)context_ptr+0x00006160+4*1))=0xf0edf46c;
*((unsigned int *)((unsigned long)context_ptr+0x00006160+4*2))=0xed711e9e;
*((unsigned int *)((unsigned long)context_ptr+0x00006160+4*3))=0x4ddc8cbd;
*((unsigned int *)((unsigned long)context_ptr+0x00006160+4*4))=0x9bb9b4a3;
*((unsigned int *)((unsigned long)context_ptr+0x00006160+4*5))=0x42536867;
*((unsigned int *)((unsigned long)context_ptr+0x00006160+4*6))=0x925bada0;
*((unsigned int *)((unsigned long)context_ptr+0x00006160+4*7))=0xc0f83357;
*((unsigned int *)((unsigned long)context_ptr+0x00006160+4*8))=0x5fac01b2;
*((unsigned int *)((unsigned long)context_ptr+0x00006160+4*9))=0x263fee81;
*((unsigned int *)((unsigned long)context_ptr+0x00006160+4*10))=0x661688b4;
*((unsigned int *)((unsigned long)context_ptr+0x00006160+4*11))=0x7fe265e2;
*((unsigned int *)((unsigned long)context_ptr+0x00006160+4*12))=0x46c4b3dd;
*((unsigned int *)((unsigned long)context_ptr+0x00006160+4*13))=0xd3e9fbe5;
*((unsigned int *)((unsigned long)context_ptr+0x00006160+4*14))=0xfabd1cd8;
*((unsigned int *)((unsigned long)context_ptr+0x00006160+4*15))=0xb75d2d92;
*((unsigned int *)((unsigned long)context_ptr+0x00006160+4*16))=0x128a2a99;
*((unsigned int *)((unsigned long)context_ptr+0x00006160+4*17))=0x4ad309c3;
*((unsigned int *)((unsigned long)context_ptr+0x00006160+4*18))=0x97fee9ff;
*((unsigned int *)((unsigned long)context_ptr+0x00006160+4*19))=0xcb17c28a;
*((unsigned int *)((unsigned long)context_ptr+0x00006160+4*20))=0x676381dc;
*((unsigned int *)((unsigned long)context_ptr+0x00006160+4*21))=0x000086bb;
*((unsigned int *)((unsigned long)context_ptr+0x000037f8))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x000037f8+4*1))=0x00006560;
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
*((unsigned int *)((unsigned long)context_ptr+0x000007f8+4*1))=0x00006160;
*((unsigned int *)((unsigned long)context_ptr+0x000007f8+4*2))=0x000064a4;
*((unsigned int *)((unsigned long)context_ptr+0x000007f8+4*3))=0x02220056;
*((unsigned int *)((unsigned long)context_ptr+0x000007f8+4*4))=0x05c51398;
*((unsigned int *)((unsigned long)context_ptr+0x000007f8+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000001b0&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000064b4,"\xe0\x30\x9b\x58\x7d\x27\x6d\xdd\x6c\xad\x51\x64\xd1\x8f\x84\xfa\x26\xd9\x2d\xed\x10\x2b\x48\x4e\xca\xf3\x4c\x17",28))
printf("strip: e0309b587d276ddd, Pass\n");
else
printf("strip: e0309b587d276ddd, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000063b0))=0x020a0012;
*((unsigned int *)((unsigned long)context_ptr+0x000063b0+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000063b0+4*2))=0x02020057;
*((unsigned int *)((unsigned long)context_ptr+0x000063b0+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x000061b8))=0xcb2ac6dd;
*((unsigned int *)((unsigned long)context_ptr+0x000061b8+4*1))=0xdd44491d;
*((unsigned int *)((unsigned long)context_ptr+0x000061b8+4*2))=0x932135b9;
*((unsigned int *)((unsigned long)context_ptr+0x000061b8+4*3))=0x43f038af;
*((unsigned int *)((unsigned long)context_ptr+0x000061b8+4*4))=0xdb5072d5;
*((unsigned int *)((unsigned long)context_ptr+0x000061b8+4*5))=0x4e8c7af8;
*((unsigned int *)((unsigned long)context_ptr+0x000061b8+4*6))=0xe9aa409e;
*((unsigned int *)((unsigned long)context_ptr+0x000061b8+4*7))=0x0fc9e688;
*((unsigned int *)((unsigned long)context_ptr+0x000061b8+4*8))=0x7a76bde0;
*((unsigned int *)((unsigned long)context_ptr+0x000061b8+4*9))=0x934a57c7;
*((unsigned int *)((unsigned long)context_ptr+0x000061b8+4*10))=0x220c6a04;
*((unsigned int *)((unsigned long)context_ptr+0x000061b8+4*11))=0xdd349fc8;
*((unsigned int *)((unsigned long)context_ptr+0x000061b8+4*12))=0x597b418b;
*((unsigned int *)((unsigned long)context_ptr+0x000061b8+4*13))=0x6aa8ff9e;
*((unsigned int *)((unsigned long)context_ptr+0x000061b8+4*14))=0xb2af8c8f;
*((unsigned int *)((unsigned long)context_ptr+0x000061b8+4*15))=0x4193788a;
*((unsigned int *)((unsigned long)context_ptr+0x000061b8+4*16))=0xa56f1e68;
*((unsigned int *)((unsigned long)context_ptr+0x000061b8+4*17))=0x94dc8a75;
*((unsigned int *)((unsigned long)context_ptr+0x000061b8+4*18))=0x624dc904;
*((unsigned int *)((unsigned long)context_ptr+0x000061b8+4*19))=0x3b4fd8f7;
*((unsigned int *)((unsigned long)context_ptr+0x000061b8+4*20))=0x11c03766;
*((unsigned int *)((unsigned long)context_ptr+0x000061b8+4*21))=0x00007000;
*((unsigned int *)((unsigned long)context_ptr+0x00003810))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003810+4*1))=0x000064b4;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000810+4*1))=0x000061b8;
*((unsigned int *)((unsigned long)context_ptr+0x00000810+4*2))=0x000063b0;
*((unsigned int *)((unsigned long)context_ptr+0x00000810+4*3))=0x02220057;
*((unsigned int *)((unsigned long)context_ptr+0x00000810+4*4))=0x00e8c46f;
*((unsigned int *)((unsigned long)context_ptr+0x00000810+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000001b6&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000063cc,"\x81\x86\xd4\x69\xe2\x3f\x1f\x36\x5a\xea\x55\xd6\x4e\x03\x5b\xbd\xa4\xc9\x6c\x48\x88\x3c\x7a\xeb\xa1\xeb\x1f\x8d",28))
printf("strip: 8186d469e23f1f36, Pass\n");
else
printf("strip: 8186d469e23f1f36, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000064d0))=0x020a0012;
*((unsigned int *)((unsigned long)context_ptr+0x000064d0+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000064d0+4*2))=0x02020058;
*((unsigned int *)((unsigned long)context_ptr+0x000064d0+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x00006678))=0xb0ccb939;
*((unsigned int *)((unsigned long)context_ptr+0x00006678+4*1))=0x4ed3cd0e;
*((unsigned int *)((unsigned long)context_ptr+0x00006678+4*2))=0xe45abb3f;
*((unsigned int *)((unsigned long)context_ptr+0x00006678+4*3))=0x90a37a9e;
*((unsigned int *)((unsigned long)context_ptr+0x00006678+4*4))=0x42ef74d6;
*((unsigned int *)((unsigned long)context_ptr+0x00006678+4*5))=0x8459f119;
*((unsigned int *)((unsigned long)context_ptr+0x00006678+4*6))=0x8f9c5f4a;
*((unsigned int *)((unsigned long)context_ptr+0x00006678+4*7))=0x16a09286;
*((unsigned int *)((unsigned long)context_ptr+0x00006678+4*8))=0x6b7f38d6;
*((unsigned int *)((unsigned long)context_ptr+0x00006678+4*9))=0x0b46f634;
*((unsigned int *)((unsigned long)context_ptr+0x00006678+4*10))=0x832a5b1e;
*((unsigned int *)((unsigned long)context_ptr+0x00006678+4*11))=0x08fd53f9;
*((unsigned int *)((unsigned long)context_ptr+0x00006678+4*12))=0xabeebe85;
*((unsigned int *)((unsigned long)context_ptr+0x00006678+4*13))=0xbc771ce4;
*((unsigned int *)((unsigned long)context_ptr+0x00006678+4*14))=0x98dc5389;
*((unsigned int *)((unsigned long)context_ptr+0x00006678+4*15))=0x6bc87508;
*((unsigned int *)((unsigned long)context_ptr+0x00006678+4*16))=0x3d8d7c2a;
*((unsigned int *)((unsigned long)context_ptr+0x00006678+4*17))=0x5ff484a1;
*((unsigned int *)((unsigned long)context_ptr+0x00006678+4*18))=0xb3c9e2da;
*((unsigned int *)((unsigned long)context_ptr+0x00006678+4*19))=0x2389118b;
*((unsigned int *)((unsigned long)context_ptr+0x00006678+4*20))=0x237e3c5d;
*((unsigned int *)((unsigned long)context_ptr+0x00006678+4*21))=0x17db15db;
*((unsigned int *)((unsigned long)context_ptr+0x00003828))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003828+4*1))=0x000063c0;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000828+4*1))=0x00006678;
*((unsigned int *)((unsigned long)context_ptr+0x00000828+4*2))=0x000064d0;
*((unsigned int *)((unsigned long)context_ptr+0x00000828+4*3))=0x02220058;
*((unsigned int *)((unsigned long)context_ptr+0x00000828+4*4))=0x003f11e4;
*((unsigned int *)((unsigned long)context_ptr+0x00000828+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000001bc&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000065c4,"\xd8\xec\x8a\x84\xec\x1e\x02\x6d\x15\xf9\x53\x5d\x61\x8c\xf5\x29\x54\x19\xa9\xba\xbf\xdb\xe6\xb2\x26\xe9\x1e\xb3",28))
printf("strip: d8ec8a84ec1e026d, Pass\n");
else
printf("strip: d8ec8a84ec1e026d, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000063dc))=0x020a0012;
*((unsigned int *)((unsigned long)context_ptr+0x000063dc+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000063dc+4*2))=0x02020059;
*((unsigned int *)((unsigned long)context_ptr+0x000063dc+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x0000657c))=0x1006fdc9;
*((unsigned int *)((unsigned long)context_ptr+0x0000657c+4*1))=0x17d8655d;
*((unsigned int *)((unsigned long)context_ptr+0x0000657c+4*2))=0x5ff6335f;
*((unsigned int *)((unsigned long)context_ptr+0x0000657c+4*3))=0x5f127e39;
*((unsigned int *)((unsigned long)context_ptr+0x0000657c+4*4))=0x2684705d;
*((unsigned int *)((unsigned long)context_ptr+0x0000657c+4*5))=0x4f62ad19;
*((unsigned int *)((unsigned long)context_ptr+0x0000657c+4*6))=0x453a815a;
*((unsigned int *)((unsigned long)context_ptr+0x0000657c+4*7))=0x5bcf5df6;
*((unsigned int *)((unsigned long)context_ptr+0x0000657c+4*8))=0xfd331220;
*((unsigned int *)((unsigned long)context_ptr+0x0000657c+4*9))=0x9adafd6b;
*((unsigned int *)((unsigned long)context_ptr+0x0000657c+4*10))=0x3ec62a2c;
*((unsigned int *)((unsigned long)context_ptr+0x0000657c+4*11))=0x388e6779;
*((unsigned int *)((unsigned long)context_ptr+0x0000657c+4*12))=0x3fbbf3bb;
*((unsigned int *)((unsigned long)context_ptr+0x0000657c+4*13))=0x625527d8;
*((unsigned int *)((unsigned long)context_ptr+0x0000657c+4*14))=0x2850598d;
*((unsigned int *)((unsigned long)context_ptr+0x0000657c+4*15))=0xf9bfb063;
*((unsigned int *)((unsigned long)context_ptr+0x0000657c+4*16))=0xc50c98a1;
*((unsigned int *)((unsigned long)context_ptr+0x0000657c+4*17))=0x02fd3c72;
*((unsigned int *)((unsigned long)context_ptr+0x0000657c+4*18))=0x3d3aed79;
*((unsigned int *)((unsigned long)context_ptr+0x0000657c+4*19))=0xa9a9b221;
*((unsigned int *)((unsigned long)context_ptr+0x0000657c+4*20))=0xec0cb2b5;
*((unsigned int *)((unsigned long)context_ptr+0x0000657c+4*21))=0xd2868db8;
*((unsigned int *)((unsigned long)context_ptr+0x0000657c+4*22))=0x00000074;
*((unsigned int *)((unsigned long)context_ptr+0x00003840))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003840+4*1))=0x000066d0;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000840+4*1))=0x0000657c;
*((unsigned int *)((unsigned long)context_ptr+0x00000840+4*2))=0x000063dc;
*((unsigned int *)((unsigned long)context_ptr+0x00000840+4*3))=0x02220059;
*((unsigned int *)((unsigned long)context_ptr+0x00000840+4*4))=0x06928362;
*((unsigned int *)((unsigned long)context_ptr+0x00000840+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000001c2&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000065e0,"\xe1\x65\xcc\x4c\x99\x36\x0d\x20\xea\x5a\x6e\x1c\x14\xc9\x67\x10\xff\x5c\x21\x1d\x44\xb2\x5c\x3e\x32\x87\x38\x34",28))
printf("strip: e165cc4c99360d20, Pass\n");
else
printf("strip: e165cc4c99360d20, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000064e0))=0x020a0012;
*((unsigned int *)((unsigned long)context_ptr+0x000064e0+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000064e0+4*2))=0x0202005a;
*((unsigned int *)((unsigned long)context_ptr+0x000064e0+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x00006210))=0xaba3c6d3;
*((unsigned int *)((unsigned long)context_ptr+0x00006210+4*1))=0xdbb42769;
*((unsigned int *)((unsigned long)context_ptr+0x00006210+4*2))=0xd69e1955;
*((unsigned int *)((unsigned long)context_ptr+0x00006210+4*3))=0x0ec627fb;
*((unsigned int *)((unsigned long)context_ptr+0x00006210+4*4))=0x0f1f0184;
*((unsigned int *)((unsigned long)context_ptr+0x00006210+4*5))=0x2c99ffca;
*((unsigned int *)((unsigned long)context_ptr+0x00006210+4*6))=0x8158304b;
*((unsigned int *)((unsigned long)context_ptr+0x00006210+4*7))=0x1656589f;
*((unsigned int *)((unsigned long)context_ptr+0x00006210+4*8))=0xe0dc4b05;
*((unsigned int *)((unsigned long)context_ptr+0x00006210+4*9))=0x724380f0;
*((unsigned int *)((unsigned long)context_ptr+0x00006210+4*10))=0x234a761b;
*((unsigned int *)((unsigned long)context_ptr+0x00006210+4*11))=0x56d51556;
*((unsigned int *)((unsigned long)context_ptr+0x00006210+4*12))=0x0b912aff;
*((unsigned int *)((unsigned long)context_ptr+0x00006210+4*13))=0xfe356bd2;
*((unsigned int *)((unsigned long)context_ptr+0x00006210+4*14))=0x7635d342;
*((unsigned int *)((unsigned long)context_ptr+0x00006210+4*15))=0x0c6a50c1;
*((unsigned int *)((unsigned long)context_ptr+0x00006210+4*16))=0xa73f783a;
*((unsigned int *)((unsigned long)context_ptr+0x00006210+4*17))=0x42f9c354;
*((unsigned int *)((unsigned long)context_ptr+0x00006210+4*18))=0x604dd3f5;
*((unsigned int *)((unsigned long)context_ptr+0x00006210+4*19))=0xc3c71d4f;
*((unsigned int *)((unsigned long)context_ptr+0x00006210+4*20))=0x80646cff;
*((unsigned int *)((unsigned long)context_ptr+0x00006210+4*21))=0x3de2e7a9;
*((unsigned int *)((unsigned long)context_ptr+0x00006210+4*22))=0x0000b454;
*((unsigned int *)((unsigned long)context_ptr+0x00003858))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003858+4*1))=0x000065d8;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000858+4*1))=0x00006210;
*((unsigned int *)((unsigned long)context_ptr+0x00000858+4*2))=0x000064e0;
*((unsigned int *)((unsigned long)context_ptr+0x00000858+4*3))=0x0222005a;
*((unsigned int *)((unsigned long)context_ptr+0x00000858+4*4))=0x0b26463b;
*((unsigned int *)((unsigned long)context_ptr+0x00000858+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000001c8&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000063f8,"\x20\x97\x41\x69\xca\x0b\xee\x12\x1e\xa0\x57\x4b\x29\xc4\xbd\x60\xc7\xad\x6a\xd9\x7a\x10\x5a\x72\xcb\x1b\x7a\x96",28))
printf("strip: 20974169ca0bee12, Pass\n");
else
printf("strip: 20974169ca0bee12, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006018))=0x020a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006018+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006018+4*2))=0x0202005b;
*((unsigned int *)((unsigned long)context_ptr+0x00006018+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x0000626c))=0x30668837;
*((unsigned int *)((unsigned long)context_ptr+0x0000626c+4*1))=0xb4b5fe1b;
*((unsigned int *)((unsigned long)context_ptr+0x0000626c+4*2))=0x9898691e;
*((unsigned int *)((unsigned long)context_ptr+0x0000626c+4*3))=0x3b98e523;
*((unsigned int *)((unsigned long)context_ptr+0x0000626c+4*4))=0x73fd8c78;
*((unsigned int *)((unsigned long)context_ptr+0x0000626c+4*5))=0xc65f4823;
*((unsigned int *)((unsigned long)context_ptr+0x0000626c+4*6))=0x672c78a4;
*((unsigned int *)((unsigned long)context_ptr+0x0000626c+4*7))=0xd29a8ab2;
*((unsigned int *)((unsigned long)context_ptr+0x0000626c+4*8))=0x898ee91a;
*((unsigned int *)((unsigned long)context_ptr+0x0000626c+4*9))=0xf2e09f68;
*((unsigned int *)((unsigned long)context_ptr+0x0000626c+4*10))=0x9c5f357e;
*((unsigned int *)((unsigned long)context_ptr+0x0000626c+4*11))=0x0891f3ef;
*((unsigned int *)((unsigned long)context_ptr+0x0000626c+4*12))=0xb372fed9;
*((unsigned int *)((unsigned long)context_ptr+0x0000626c+4*13))=0x6bcaa098;
*((unsigned int *)((unsigned long)context_ptr+0x0000626c+4*14))=0xb42a4b44;
*((unsigned int *)((unsigned long)context_ptr+0x0000626c+4*15))=0x9a7d45c4;
*((unsigned int *)((unsigned long)context_ptr+0x0000626c+4*16))=0x3e127f91;
*((unsigned int *)((unsigned long)context_ptr+0x0000626c+4*17))=0x17587bb6;
*((unsigned int *)((unsigned long)context_ptr+0x0000626c+4*18))=0x88237b9c;
*((unsigned int *)((unsigned long)context_ptr+0x0000626c+4*19))=0xa3567e90;
*((unsigned int *)((unsigned long)context_ptr+0x0000626c+4*20))=0xfa257436;
*((unsigned int *)((unsigned long)context_ptr+0x0000626c+4*21))=0x243402eb;
*((unsigned int *)((unsigned long)context_ptr+0x0000626c+4*22))=0x003b53c5;
*((unsigned int *)((unsigned long)context_ptr+0x00003870))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003870+4*1))=0x000066ec;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000870+4*1))=0x0000626c;
*((unsigned int *)((unsigned long)context_ptr+0x00000870+4*2))=0x00006018;
*((unsigned int *)((unsigned long)context_ptr+0x00000870+4*3))=0x0222005b;
*((unsigned int *)((unsigned long)context_ptr+0x00000870+4*4))=0x07949c2a;
*((unsigned int *)((unsigned long)context_ptr+0x00000870+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000001ce&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006038,"\x05\x83\xca\xdc\xd2\xf8\x1e\x71\x5f\xdb\xdc\x91\x82\x1e\x52\x09\x4f\x87\x82\xed\x0c\x01\xee\xa2\xea\xda\x96\x59",28))
printf("strip: 0583cadcd2f81e71, Pass\n");
else
printf("strip: 0583cadcd2f81e71, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006008))=0x020a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006008+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006008+4*2))=0x0202005c;
*((unsigned int *)((unsigned long)context_ptr+0x00006008+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x00006808))=0x13ebc9bc;
*((unsigned int *)((unsigned long)context_ptr+0x00006808+4*1))=0xf39d0c3c;
*((unsigned int *)((unsigned long)context_ptr+0x00006808+4*2))=0x1fa77c50;
*((unsigned int *)((unsigned long)context_ptr+0x00006808+4*3))=0x888e8ff9;
*((unsigned int *)((unsigned long)context_ptr+0x00006808+4*4))=0xbd064507;
*((unsigned int *)((unsigned long)context_ptr+0x00006808+4*5))=0x0e20e75b;
*((unsigned int *)((unsigned long)context_ptr+0x00006808+4*6))=0x948f2d09;
*((unsigned int *)((unsigned long)context_ptr+0x00006808+4*7))=0x812f74b4;
*((unsigned int *)((unsigned long)context_ptr+0x00006808+4*8))=0xe1359134;
*((unsigned int *)((unsigned long)context_ptr+0x00006808+4*9))=0xea34c471;
*((unsigned int *)((unsigned long)context_ptr+0x00006808+4*10))=0xcbedac01;
*((unsigned int *)((unsigned long)context_ptr+0x00006808+4*11))=0x05f206a0;
*((unsigned int *)((unsigned long)context_ptr+0x00006808+4*12))=0x4ab520b3;
*((unsigned int *)((unsigned long)context_ptr+0x00006808+4*13))=0x560ede5d;
*((unsigned int *)((unsigned long)context_ptr+0x00006808+4*14))=0x3cfa9176;
*((unsigned int *)((unsigned long)context_ptr+0x00006808+4*15))=0x244554b9;
*((unsigned int *)((unsigned long)context_ptr+0x00006808+4*16))=0xbb0c0419;
*((unsigned int *)((unsigned long)context_ptr+0x00006808+4*17))=0x9a2034f0;
*((unsigned int *)((unsigned long)context_ptr+0x00006808+4*18))=0xef1d18c0;
*((unsigned int *)((unsigned long)context_ptr+0x00006808+4*19))=0x4046235b;
*((unsigned int *)((unsigned long)context_ptr+0x00006808+4*20))=0xfe61daa1;
*((unsigned int *)((unsigned long)context_ptr+0x00006808+4*21))=0x802c2776;
*((unsigned int *)((unsigned long)context_ptr+0x00006808+4*22))=0x16326c80;
*((unsigned int *)((unsigned long)context_ptr+0x00003888))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003888+4*1))=0x00006038;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000888+4*1))=0x00006808;
*((unsigned int *)((unsigned long)context_ptr+0x00000888+4*2))=0x00006008;
*((unsigned int *)((unsigned long)context_ptr+0x00000888+4*3))=0x0222005c;
*((unsigned int *)((unsigned long)context_ptr+0x00000888+4*4))=0x081977da;
*((unsigned int *)((unsigned long)context_ptr+0x00000888+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000001d4&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006414,"\xcc\x32\x11\xd2\x08\xf8\x54\xff\x76\x42\x9e\xae\xc0\xde\x99\xac\x33\x22\xd4\x5d\x02\xca\x09\x12\x53\xa8\x55\x4a",28))
printf("strip: cc3211d208f854ff, Pass\n");
else
printf("strip: cc3211d208f854ff, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006028))=0x020a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006028+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006028+4*2))=0x0202005d;
*((unsigned int *)((unsigned long)context_ptr+0x00006028+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x00006864))=0x5009ad8d;
*((unsigned int *)((unsigned long)context_ptr+0x00006864+4*1))=0x8bb7bbf3;
*((unsigned int *)((unsigned long)context_ptr+0x00006864+4*2))=0x8c20a402;
*((unsigned int *)((unsigned long)context_ptr+0x00006864+4*3))=0x49a97d18;
*((unsigned int *)((unsigned long)context_ptr+0x00006864+4*4))=0x0661f3bf;
*((unsigned int *)((unsigned long)context_ptr+0x00006864+4*5))=0x87463c9a;
*((unsigned int *)((unsigned long)context_ptr+0x00006864+4*6))=0x1d49de41;
*((unsigned int *)((unsigned long)context_ptr+0x00006864+4*7))=0xb0be1ea5;
*((unsigned int *)((unsigned long)context_ptr+0x00006864+4*8))=0xe551462a;
*((unsigned int *)((unsigned long)context_ptr+0x00006864+4*9))=0xf93ec3f8;
*((unsigned int *)((unsigned long)context_ptr+0x00006864+4*10))=0x0a7a3147;
*((unsigned int *)((unsigned long)context_ptr+0x00006864+4*11))=0x1cb830e5;
*((unsigned int *)((unsigned long)context_ptr+0x00006864+4*12))=0xc38ffe4a;
*((unsigned int *)((unsigned long)context_ptr+0x00006864+4*13))=0x9b7e1850;
*((unsigned int *)((unsigned long)context_ptr+0x00006864+4*14))=0xbed73d54;
*((unsigned int *)((unsigned long)context_ptr+0x00006864+4*15))=0xc37b7c3c;
*((unsigned int *)((unsigned long)context_ptr+0x00006864+4*16))=0x3da19785;
*((unsigned int *)((unsigned long)context_ptr+0x00006864+4*17))=0xcf55ae0e;
*((unsigned int *)((unsigned long)context_ptr+0x00006864+4*18))=0x0ddbb0ef;
*((unsigned int *)((unsigned long)context_ptr+0x00006864+4*19))=0x54c5c7d7;
*((unsigned int *)((unsigned long)context_ptr+0x00006864+4*20))=0xe7887e04;
*((unsigned int *)((unsigned long)context_ptr+0x00006864+4*21))=0xdd4b816c;
*((unsigned int *)((unsigned long)context_ptr+0x00006864+4*22))=0xe69a8d04;
*((unsigned int *)((unsigned long)context_ptr+0x00006864+4*23))=0x000000ff;
*((unsigned int *)((unsigned long)context_ptr+0x000038a0))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x000038a0+4*1))=0x000062c8;
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
*((unsigned int *)((unsigned long)context_ptr+0x000008a0+4*1))=0x00006864;
*((unsigned int *)((unsigned long)context_ptr+0x000008a0+4*2))=0x00006028;
*((unsigned int *)((unsigned long)context_ptr+0x000008a0+4*3))=0x0222005d;
*((unsigned int *)((unsigned long)context_ptr+0x000008a0+4*4))=0x0da9f877;
*((unsigned int *)((unsigned long)context_ptr+0x000008a0+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000001da&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006430,"\xd2\x7b\x4f\x2e\x91\x85\x6f\x23\x7c\xe9\xfc\x47\xfb\x2d\x7e\x7c\xcd\x57\x3a\x51\x38\x9b\x6a\xc5\x3b\xe4\xb0\x45",28))
printf("strip: d27b4f2e91856f23, Pass\n");
else
printf("strip: d27b4f2e91856f23, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006054))=0x020a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006054+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006054+4*2))=0x0202005e;
*((unsigned int *)((unsigned long)context_ptr+0x00006054+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x000063ec))=0x5e2a0717;
*((unsigned int *)((unsigned long)context_ptr+0x000063ec+4*1))=0x6cac4983;
*((unsigned int *)((unsigned long)context_ptr+0x000063ec+4*2))=0x5116ca02;
*((unsigned int *)((unsigned long)context_ptr+0x000063ec+4*3))=0xcdd1c327;
*((unsigned int *)((unsigned long)context_ptr+0x000063ec+4*4))=0xb0eb1ff7;
*((unsigned int *)((unsigned long)context_ptr+0x000063ec+4*5))=0x1a1cfa1e;
*((unsigned int *)((unsigned long)context_ptr+0x000063ec+4*6))=0xee1c3dab;
*((unsigned int *)((unsigned long)context_ptr+0x000063ec+4*7))=0x9e4f30e2;
*((unsigned int *)((unsigned long)context_ptr+0x000063ec+4*8))=0x9d93de90;
*((unsigned int *)((unsigned long)context_ptr+0x000063ec+4*9))=0x54042fed;
*((unsigned int *)((unsigned long)context_ptr+0x000063ec+4*10))=0x1076aaed;
*((unsigned int *)((unsigned long)context_ptr+0x000063ec+4*11))=0x36310874;
*((unsigned int *)((unsigned long)context_ptr+0x000063ec+4*12))=0xb51dc77a;
*((unsigned int *)((unsigned long)context_ptr+0x000063ec+4*13))=0xf103af82;
*((unsigned int *)((unsigned long)context_ptr+0x000063ec+4*14))=0xae246517;
*((unsigned int *)((unsigned long)context_ptr+0x000063ec+4*15))=0xd11e3e4a;
*((unsigned int *)((unsigned long)context_ptr+0x000063ec+4*16))=0x64cc4234;
*((unsigned int *)((unsigned long)context_ptr+0x000063ec+4*17))=0x88dfc8b1;
*((unsigned int *)((unsigned long)context_ptr+0x000063ec+4*18))=0x8e96d139;
*((unsigned int *)((unsigned long)context_ptr+0x000063ec+4*19))=0x5b999f27;
*((unsigned int *)((unsigned long)context_ptr+0x000063ec+4*20))=0xae3b73bd;
*((unsigned int *)((unsigned long)context_ptr+0x000063ec+4*21))=0xc556d2e8;
*((unsigned int *)((unsigned long)context_ptr+0x000063ec+4*22))=0x602603cc;
*((unsigned int *)((unsigned long)context_ptr+0x000063ec+4*23))=0x00005cb1;
*((unsigned int *)((unsigned long)context_ptr+0x000038b8))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x000038b8+4*1))=0x000065f4;
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
*((unsigned int *)((unsigned long)context_ptr+0x000008b8+4*1))=0x000063ec;
*((unsigned int *)((unsigned long)context_ptr+0x000008b8+4*2))=0x00006054;
*((unsigned int *)((unsigned long)context_ptr+0x000008b8+4*3))=0x0222005e;
*((unsigned int *)((unsigned long)context_ptr+0x000008b8+4*4))=0x01b05ce3;
*((unsigned int *)((unsigned long)context_ptr+0x000008b8+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000001e0&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x0000664c,"\xb7\xf5\x3b\x98\xd1\xfc\x23\xb9\x7e\x4c\x7e\x4d\x7f\x52\x94\x2b\xcb\x95\x52\x8c\x8d\x88\x15\xd1\x2f\x77\x3a\xd6",28))
printf("strip: b7f53b98d1fc23b9, Pass\n");
else
printf("strip: b7f53b98d1fc23b9, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x0000644c))=0x020a0012;
*((unsigned int *)((unsigned long)context_ptr+0x0000644c+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x0000644c+4*2))=0x0202005f;
*((unsigned int *)((unsigned long)context_ptr+0x0000644c+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x000062e4))=0x9e41662f;
*((unsigned int *)((unsigned long)context_ptr+0x000062e4+4*1))=0xacf1dc26;
*((unsigned int *)((unsigned long)context_ptr+0x000062e4+4*2))=0xe1995242;
*((unsigned int *)((unsigned long)context_ptr+0x000062e4+4*3))=0xcadb9db7;
*((unsigned int *)((unsigned long)context_ptr+0x000062e4+4*4))=0xd87f30b3;
*((unsigned int *)((unsigned long)context_ptr+0x000062e4+4*5))=0xb3161064;
*((unsigned int *)((unsigned long)context_ptr+0x000062e4+4*6))=0xd43c3cb9;
*((unsigned int *)((unsigned long)context_ptr+0x000062e4+4*7))=0x307630cb;
*((unsigned int *)((unsigned long)context_ptr+0x000062e4+4*8))=0xf703d93a;
*((unsigned int *)((unsigned long)context_ptr+0x000062e4+4*9))=0x5c6e8f29;
*((unsigned int *)((unsigned long)context_ptr+0x000062e4+4*10))=0xd068aaf3;
*((unsigned int *)((unsigned long)context_ptr+0x000062e4+4*11))=0x6cdb5552;
*((unsigned int *)((unsigned long)context_ptr+0x000062e4+4*12))=0xdc576e5b;
*((unsigned int *)((unsigned long)context_ptr+0x000062e4+4*13))=0x8a9d8a81;
*((unsigned int *)((unsigned long)context_ptr+0x000062e4+4*14))=0x131f156b;
*((unsigned int *)((unsigned long)context_ptr+0x000062e4+4*15))=0xf5237446;
*((unsigned int *)((unsigned long)context_ptr+0x000062e4+4*16))=0x8c4e7a91;
*((unsigned int *)((unsigned long)context_ptr+0x000062e4+4*17))=0xfda918b9;
*((unsigned int *)((unsigned long)context_ptr+0x000062e4+4*18))=0xa2523e31;
*((unsigned int *)((unsigned long)context_ptr+0x000062e4+4*19))=0x91e7faa8;
*((unsigned int *)((unsigned long)context_ptr+0x000062e4+4*20))=0x8ba487ce;
*((unsigned int *)((unsigned long)context_ptr+0x000062e4+4*21))=0x1bd32178;
*((unsigned int *)((unsigned long)context_ptr+0x000062e4+4*22))=0xe4c71a69;
*((unsigned int *)((unsigned long)context_ptr+0x000062e4+4*23))=0x0049d553;
*((unsigned int *)((unsigned long)context_ptr+0x000038d0))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x000038d0+4*1))=0x00006610;
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
*((unsigned int *)((unsigned long)context_ptr+0x000008d0+4*1))=0x000062e4;
*((unsigned int *)((unsigned long)context_ptr+0x000008d0+4*2))=0x0000644c;
*((unsigned int *)((unsigned long)context_ptr+0x000008d0+4*3))=0x0222005f;
*((unsigned int *)((unsigned long)context_ptr+0x000008d0+4*4))=0x0dbe6741;
*((unsigned int *)((unsigned long)context_ptr+0x000008d0+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000001e6&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006348,"\x02\x56\x57\xb6\x08\x7c\x13\x9d\xd3\x9c\xef\x2f\x77\xf7\x5f\x09\x5a\x4a\xa2\x0d\x23\x7d\x6f\xfa\xd7\x36\x7d\x7d",28))
printf("strip: 025657b6087c139d, Pass\n");
else
printf("strip: 025657b6087c139d, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x0000645c))=0x020a0012;
*((unsigned int *)((unsigned long)context_ptr+0x0000645c+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x0000645c+4*2))=0x02020060;
*((unsigned int *)((unsigned long)context_ptr+0x0000645c+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x00006708))=0xf5531712;
*((unsigned int *)((unsigned long)context_ptr+0x00006708+4*1))=0x55442258;
*((unsigned int *)((unsigned long)context_ptr+0x00006708+4*2))=0x50142252;
*((unsigned int *)((unsigned long)context_ptr+0x00006708+4*3))=0x7c86ab4f;
*((unsigned int *)((unsigned long)context_ptr+0x00006708+4*4))=0xd0de945c;
*((unsigned int *)((unsigned long)context_ptr+0x00006708+4*5))=0xb3f5f966;
*((unsigned int *)((unsigned long)context_ptr+0x00006708+4*6))=0x4bb2e51a;
*((unsigned int *)((unsigned long)context_ptr+0x00006708+4*7))=0x5cc704c5;
*((unsigned int *)((unsigned long)context_ptr+0x00006708+4*8))=0x82e78e54;
*((unsigned int *)((unsigned long)context_ptr+0x00006708+4*9))=0xc95e7539;
*((unsigned int *)((unsigned long)context_ptr+0x00006708+4*10))=0x8fee1d06;
*((unsigned int *)((unsigned long)context_ptr+0x00006708+4*11))=0xe917a0fe;
*((unsigned int *)((unsigned long)context_ptr+0x00006708+4*12))=0xde65ba3a;
*((unsigned int *)((unsigned long)context_ptr+0x00006708+4*13))=0xc1cf93d5;
*((unsigned int *)((unsigned long)context_ptr+0x00006708+4*14))=0xdcb5fca5;
*((unsigned int *)((unsigned long)context_ptr+0x00006708+4*15))=0xf8ddd4c8;
*((unsigned int *)((unsigned long)context_ptr+0x00006708+4*16))=0x410a51a5;
*((unsigned int *)((unsigned long)context_ptr+0x00006708+4*17))=0x4426c5cc;
*((unsigned int *)((unsigned long)context_ptr+0x00006708+4*18))=0x2e0c8825;
*((unsigned int *)((unsigned long)context_ptr+0x00006708+4*19))=0xc220fc46;
*((unsigned int *)((unsigned long)context_ptr+0x00006708+4*20))=0x94c103cd;
*((unsigned int *)((unsigned long)context_ptr+0x00006708+4*21))=0xca969215;
*((unsigned int *)((unsigned long)context_ptr+0x00006708+4*22))=0xb9fc5e89;
*((unsigned int *)((unsigned long)context_ptr+0x00006708+4*23))=0xcfffd330;
*((unsigned int *)((unsigned long)context_ptr+0x000038e8))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x000038e8+4*1))=0x00006344;
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
*((unsigned int *)((unsigned long)context_ptr+0x000008e8+4*1))=0x00006708;
*((unsigned int *)((unsigned long)context_ptr+0x000008e8+4*2))=0x0000645c;
*((unsigned int *)((unsigned long)context_ptr+0x000008e8+4*3))=0x02220060;
*((unsigned int *)((unsigned long)context_ptr+0x000008e8+4*4))=0x0e8b5a05;
*((unsigned int *)((unsigned long)context_ptr+0x000008e8+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000001ec&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006364,"\x3a\x8b\xef\x9c\x32\x95\x0a\xb8\x75\x4f\xd6\xa0\xf0\x96\x62\x81\xaf\x19\x1f\xfe\xcf\x6f\xaf\x41\xed\x1d\x0c\x35",28))
printf("strip: 3a8bef9c32950ab8, Pass\n");
else
printf("strip: 3a8bef9c32950ab8, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006360))=0x020a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006360+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006360+4*2))=0x02020061;
*((unsigned int *)((unsigned long)context_ptr+0x00006360+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x00006064))=0x63c82121;
*((unsigned int *)((unsigned long)context_ptr+0x00006064+4*1))=0x0fecf66d;
*((unsigned int *)((unsigned long)context_ptr+0x00006064+4*2))=0x6bae227c;
*((unsigned int *)((unsigned long)context_ptr+0x00006064+4*3))=0xe3929afe;
*((unsigned int *)((unsigned long)context_ptr+0x00006064+4*4))=0xd1c33f53;
*((unsigned int *)((unsigned long)context_ptr+0x00006064+4*5))=0xb6e009ac;
*((unsigned int *)((unsigned long)context_ptr+0x00006064+4*6))=0x0518ef4e;
*((unsigned int *)((unsigned long)context_ptr+0x00006064+4*7))=0xe342d6cb;
*((unsigned int *)((unsigned long)context_ptr+0x00006064+4*8))=0x1240ab85;
*((unsigned int *)((unsigned long)context_ptr+0x00006064+4*9))=0xfda54339;
*((unsigned int *)((unsigned long)context_ptr+0x00006064+4*10))=0x1a866486;
*((unsigned int *)((unsigned long)context_ptr+0x00006064+4*11))=0xa4a4a8b6;
*((unsigned int *)((unsigned long)context_ptr+0x00006064+4*12))=0x5671ea22;
*((unsigned int *)((unsigned long)context_ptr+0x00006064+4*13))=0x13e45159;
*((unsigned int *)((unsigned long)context_ptr+0x00006064+4*14))=0x8719428f;
*((unsigned int *)((unsigned long)context_ptr+0x00006064+4*15))=0xeb5c598e;
*((unsigned int *)((unsigned long)context_ptr+0x00006064+4*16))=0xaab1cd8c;
*((unsigned int *)((unsigned long)context_ptr+0x00006064+4*17))=0x7774beef;
*((unsigned int *)((unsigned long)context_ptr+0x00006064+4*18))=0xc3cbd8ca;
*((unsigned int *)((unsigned long)context_ptr+0x00006064+4*19))=0x2f0f9b55;
*((unsigned int *)((unsigned long)context_ptr+0x00006064+4*20))=0xb00ff824;
*((unsigned int *)((unsigned long)context_ptr+0x00006064+4*21))=0xa63796d4;
*((unsigned int *)((unsigned long)context_ptr+0x00006064+4*22))=0xea4c4ec1;
*((unsigned int *)((unsigned long)context_ptr+0x00006064+4*23))=0x192c487d;
*((unsigned int *)((unsigned long)context_ptr+0x00006064+4*24))=0x00000042;
*((unsigned int *)((unsigned long)context_ptr+0x00003900))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003900+4*1))=0x000060c8;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000900+4*1))=0x00006064;
*((unsigned int *)((unsigned long)context_ptr+0x00000900+4*2))=0x00006360;
*((unsigned int *)((unsigned long)context_ptr+0x00000900+4*3))=0x02220061;
*((unsigned int *)((unsigned long)context_ptr+0x00000900+4*4))=0x0bd9cca2;
*((unsigned int *)((unsigned long)context_ptr+0x00000900+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000001f2&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000064f0,"\x26\x41\xd6\x0d\xb3\x73\xaa\xc5\x4f\x87\x0a\x1c\x21\x39\xe3\xdd\x0c\xf0\x29\xad\x12\x66\x54\x4b\x35\xa9\xdc\xc7",28))
printf("strip: 2641d60db373aac5, Pass\n");
else
printf("strip: 2641d60db373aac5, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000064f0))=0x020a0012;
*((unsigned int *)((unsigned long)context_ptr+0x000064f0+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000064f0+4*2))=0x02020062;
*((unsigned int *)((unsigned long)context_ptr+0x000064f0+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x000060e4))=0x50dffc30;
*((unsigned int *)((unsigned long)context_ptr+0x000060e4+4*1))=0x2cd6a219;
*((unsigned int *)((unsigned long)context_ptr+0x000060e4+4*2))=0xac095dad;
*((unsigned int *)((unsigned long)context_ptr+0x000060e4+4*3))=0x2d3ccb6d;
*((unsigned int *)((unsigned long)context_ptr+0x000060e4+4*4))=0x92e1c258;
*((unsigned int *)((unsigned long)context_ptr+0x000060e4+4*5))=0x06292d9c;
*((unsigned int *)((unsigned long)context_ptr+0x000060e4+4*6))=0x32ddc73a;
*((unsigned int *)((unsigned long)context_ptr+0x000060e4+4*7))=0x94cf6522;
*((unsigned int *)((unsigned long)context_ptr+0x000060e4+4*8))=0x064112c8;
*((unsigned int *)((unsigned long)context_ptr+0x000060e4+4*9))=0x1872fa77;
*((unsigned int *)((unsigned long)context_ptr+0x000060e4+4*10))=0xfe14dc11;
*((unsigned int *)((unsigned long)context_ptr+0x000060e4+4*11))=0x12743a1b;
*((unsigned int *)((unsigned long)context_ptr+0x000060e4+4*12))=0x2847bfc2;
*((unsigned int *)((unsigned long)context_ptr+0x000060e4+4*13))=0x0163b0f1;
*((unsigned int *)((unsigned long)context_ptr+0x000060e4+4*14))=0x47867c36;
*((unsigned int *)((unsigned long)context_ptr+0x000060e4+4*15))=0xa12632ef;
*((unsigned int *)((unsigned long)context_ptr+0x000060e4+4*16))=0x77d9e94f;
*((unsigned int *)((unsigned long)context_ptr+0x000060e4+4*17))=0x5c864c7d;
*((unsigned int *)((unsigned long)context_ptr+0x000060e4+4*18))=0x751e88fb;
*((unsigned int *)((unsigned long)context_ptr+0x000060e4+4*19))=0x854a816a;
*((unsigned int *)((unsigned long)context_ptr+0x000060e4+4*20))=0xb34ed2a6;
*((unsigned int *)((unsigned long)context_ptr+0x000060e4+4*21))=0x9230cb56;
*((unsigned int *)((unsigned long)context_ptr+0x000060e4+4*22))=0x8f6beb39;
*((unsigned int *)((unsigned long)context_ptr+0x000060e4+4*23))=0x3886af0b;
*((unsigned int *)((unsigned long)context_ptr+0x000060e4+4*24))=0x0000326b;
*((unsigned int *)((unsigned long)context_ptr+0x00003918))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003918+4*1))=0x00006370;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000918+4*1))=0x000060e4;
*((unsigned int *)((unsigned long)context_ptr+0x00000918+4*2))=0x000064f0;
*((unsigned int *)((unsigned long)context_ptr+0x00000918+4*3))=0x02220062;
*((unsigned int *)((unsigned long)context_ptr+0x00000918+4*4))=0x0202e46f;
*((unsigned int *)((unsigned long)context_ptr+0x00000918+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000001f8&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x0000646c,"\x91\xd2\x12\x0f\x0a\x8d\x96\x84\x28\x59\xb5\x63\x07\x3b\x68\x35\xb1\xa7\x2f\xc8\x75\xcf\xca\x85\x9d\x6b\xa5\x6f",28))
printf("strip: 91d2120f0a8d9684, Pass\n");
else
printf("strip: 91d2120f0a8d9684, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x0000638c))=0x020a0012;
*((unsigned int *)((unsigned long)context_ptr+0x0000638c+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x0000638c+4*2))=0x02020063;
*((unsigned int *)((unsigned long)context_ptr+0x0000638c+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x000068c4))=0x7e104f86;
*((unsigned int *)((unsigned long)context_ptr+0x000068c4+4*1))=0x8804feb8;
*((unsigned int *)((unsigned long)context_ptr+0x000068c4+4*2))=0x9a661bf0;
*((unsigned int *)((unsigned long)context_ptr+0x000068c4+4*3))=0x82665eb3;
*((unsigned int *)((unsigned long)context_ptr+0x000068c4+4*4))=0xab2f5c0a;
*((unsigned int *)((unsigned long)context_ptr+0x000068c4+4*5))=0xcc0145a9;
*((unsigned int *)((unsigned long)context_ptr+0x000068c4+4*6))=0xdf00f908;
*((unsigned int *)((unsigned long)context_ptr+0x000068c4+4*7))=0xf23e3287;
*((unsigned int *)((unsigned long)context_ptr+0x000068c4+4*8))=0x58875e1c;
*((unsigned int *)((unsigned long)context_ptr+0x000068c4+4*9))=0x51766149;
*((unsigned int *)((unsigned long)context_ptr+0x000068c4+4*10))=0xeae0b620;
*((unsigned int *)((unsigned long)context_ptr+0x000068c4+4*11))=0x00b7a0a9;
*((unsigned int *)((unsigned long)context_ptr+0x000068c4+4*12))=0x2fc9a24d;
*((unsigned int *)((unsigned long)context_ptr+0x000068c4+4*13))=0x89869a1f;
*((unsigned int *)((unsigned long)context_ptr+0x000068c4+4*14))=0x3c1cd57b;
*((unsigned int *)((unsigned long)context_ptr+0x000068c4+4*15))=0x6292d397;
*((unsigned int *)((unsigned long)context_ptr+0x000068c4+4*16))=0xef365a59;
*((unsigned int *)((unsigned long)context_ptr+0x000068c4+4*17))=0x675ae2c6;
*((unsigned int *)((unsigned long)context_ptr+0x000068c4+4*18))=0xa2770536;
*((unsigned int *)((unsigned long)context_ptr+0x000068c4+4*19))=0xc53ef9f3;
*((unsigned int *)((unsigned long)context_ptr+0x000068c4+4*20))=0xe091282c;
*((unsigned int *)((unsigned long)context_ptr+0x000068c4+4*21))=0x4fb19856;
*((unsigned int *)((unsigned long)context_ptr+0x000068c4+4*22))=0x92a1940b;
*((unsigned int *)((unsigned long)context_ptr+0x000068c4+4*23))=0x8e2682b8;
*((unsigned int *)((unsigned long)context_ptr+0x000068c4+4*24))=0x009cb033;
*((unsigned int *)((unsigned long)context_ptr+0x00003930))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003930+4*1))=0x0000646c;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000930+4*1))=0x000068c4;
*((unsigned int *)((unsigned long)context_ptr+0x00000930+4*2))=0x0000638c;
*((unsigned int *)((unsigned long)context_ptr+0x00000930+4*3))=0x02220063;
*((unsigned int *)((unsigned long)context_ptr+0x00000930+4*4))=0x050558dc;
*((unsigned int *)((unsigned long)context_ptr+0x00000930+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000001fe&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006488,"\xba\x07\x87\x8e\xf9\xb6\x02\x0c\x28\x3d\xcf\x17\x3c\x2d\x23\x10\x74\xb0\xbd\xd4\x4d\x52\x5c\x9a\xb0\x84\x3a\x2e",28))
printf("strip: ba07878ef9b6020c, Pass\n");
else
printf("strip: ba07878ef9b6020c, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x0000639c))=0x020a0012;
*((unsigned int *)((unsigned long)context_ptr+0x0000639c+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x0000639c+4*2))=0x02020064;
*((unsigned int *)((unsigned long)context_ptr+0x0000639c+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x00006768))=0x0577471b;
*((unsigned int *)((unsigned long)context_ptr+0x00006768+4*1))=0x57809741;
*((unsigned int *)((unsigned long)context_ptr+0x00006768+4*2))=0x4726219e;
*((unsigned int *)((unsigned long)context_ptr+0x00006768+4*3))=0xbe506bf3;
*((unsigned int *)((unsigned long)context_ptr+0x00006768+4*4))=0xd0e827d7;
*((unsigned int *)((unsigned long)context_ptr+0x00006768+4*5))=0xd67e325e;
*((unsigned int *)((unsigned long)context_ptr+0x00006768+4*6))=0x9acb2b35;
*((unsigned int *)((unsigned long)context_ptr+0x00006768+4*7))=0xf64f7eba;
*((unsigned int *)((unsigned long)context_ptr+0x00006768+4*8))=0x0351aa3d;
*((unsigned int *)((unsigned long)context_ptr+0x00006768+4*9))=0x83d2b685;
*((unsigned int *)((unsigned long)context_ptr+0x00006768+4*10))=0x96945302;
*((unsigned int *)((unsigned long)context_ptr+0x00006768+4*11))=0x2ab6f5ec;
*((unsigned int *)((unsigned long)context_ptr+0x00006768+4*12))=0x12551fbd;
*((unsigned int *)((unsigned long)context_ptr+0x00006768+4*13))=0x09b783cf;
*((unsigned int *)((unsigned long)context_ptr+0x00006768+4*14))=0x287d342d;
*((unsigned int *)((unsigned long)context_ptr+0x00006768+4*15))=0xf51b8f19;
*((unsigned int *)((unsigned long)context_ptr+0x00006768+4*16))=0x4cc4fec6;
*((unsigned int *)((unsigned long)context_ptr+0x00006768+4*17))=0x511f33cf;
*((unsigned int *)((unsigned long)context_ptr+0x00006768+4*18))=0x11e31eb3;
*((unsigned int *)((unsigned long)context_ptr+0x00006768+4*19))=0xc383b0c6;
*((unsigned int *)((unsigned long)context_ptr+0x00006768+4*20))=0x4b26b18c;
*((unsigned int *)((unsigned long)context_ptr+0x00006768+4*21))=0xbb96a18a;
*((unsigned int *)((unsigned long)context_ptr+0x00006768+4*22))=0xf3f151b1;
*((unsigned int *)((unsigned long)context_ptr+0x00006768+4*23))=0x1563754b;
*((unsigned int *)((unsigned long)context_ptr+0x00006768+4*24))=0x873cd08c;
*((unsigned int *)((unsigned long)context_ptr+0x00003948))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003948+4*1))=0x00006488;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000948+4*1))=0x00006768;
*((unsigned int *)((unsigned long)context_ptr+0x00000948+4*2))=0x0000639c;
*((unsigned int *)((unsigned long)context_ptr+0x00000948+4*3))=0x02220064;
*((unsigned int *)((unsigned long)context_ptr+0x00000948+4*4))=0x06b0d4a8;
*((unsigned int *)((unsigned long)context_ptr+0x00000948+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000204&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006560,"\x4b\xa3\x85\x85\xe1\xb2\xcd\x5d\x11\xd5\xbc\x08\xaa\x60\x9c\x38\xc4\xda\x56\x3d\xc8\xfb\xe6\x95\x45\x50\x10\xe5",28))
printf("strip: 4ba38585e1b2cd5d, Pass\n");
else
printf("strip: 4ba38585e1b2cd5d, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000064a4))=0x020a0012;
*((unsigned int *)((unsigned long)context_ptr+0x000064a4+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000064a4+4*2))=0x02020065;
*((unsigned int *)((unsigned long)context_ptr+0x000064a4+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x00006148))=0x10aeeaa8;
*((unsigned int *)((unsigned long)context_ptr+0x00006148+4*1))=0xa62710a4;
*((unsigned int *)((unsigned long)context_ptr+0x00006148+4*2))=0xe09408ae;
*((unsigned int *)((unsigned long)context_ptr+0x00006148+4*3))=0xa437a4a1;
*((unsigned int *)((unsigned long)context_ptr+0x00006148+4*4))=0xd13dd526;
*((unsigned int *)((unsigned long)context_ptr+0x00006148+4*5))=0x4d559806;
*((unsigned int *)((unsigned long)context_ptr+0x00006148+4*6))=0x2dfa3e9c;
*((unsigned int *)((unsigned long)context_ptr+0x00006148+4*7))=0xeb4fad8b;
*((unsigned int *)((unsigned long)context_ptr+0x00006148+4*8))=0x8f7037c7;
*((unsigned int *)((unsigned long)context_ptr+0x00006148+4*9))=0x4ebdc506;
*((unsigned int *)((unsigned long)context_ptr+0x00006148+4*10))=0xdd6f6aca;
*((unsigned int *)((unsigned long)context_ptr+0x00006148+4*11))=0x33bac74e;
*((unsigned int *)((unsigned long)context_ptr+0x00006148+4*12))=0x409c284b;
*((unsigned int *)((unsigned long)context_ptr+0x00006148+4*13))=0xc13e33ec;
*((unsigned int *)((unsigned long)context_ptr+0x00006148+4*14))=0xcb006e9b;
*((unsigned int *)((unsigned long)context_ptr+0x00006148+4*15))=0x30518855;
*((unsigned int *)((unsigned long)context_ptr+0x00006148+4*16))=0xd3b77fe4;
*((unsigned int *)((unsigned long)context_ptr+0x00006148+4*17))=0x0c17a467;
*((unsigned int *)((unsigned long)context_ptr+0x00006148+4*18))=0xf6f1fb9a;
*((unsigned int *)((unsigned long)context_ptr+0x00006148+4*19))=0x9db77395;
*((unsigned int *)((unsigned long)context_ptr+0x00006148+4*20))=0x4eabe8dc;
*((unsigned int *)((unsigned long)context_ptr+0x00006148+4*21))=0x14babd7f;
*((unsigned int *)((unsigned long)context_ptr+0x00006148+4*22))=0x6b32350b;
*((unsigned int *)((unsigned long)context_ptr+0x00006148+4*23))=0x214db00c;
*((unsigned int *)((unsigned long)context_ptr+0x00006148+4*24))=0xf2a1cab3;
*((unsigned int *)((unsigned long)context_ptr+0x00006148+4*25))=0x000000c5;
*((unsigned int *)((unsigned long)context_ptr+0x00003960))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003960+4*1))=0x000067cc;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000960+4*1))=0x00006148;
*((unsigned int *)((unsigned long)context_ptr+0x00000960+4*2))=0x000064a4;
*((unsigned int *)((unsigned long)context_ptr+0x00000960+4*3))=0x02220065;
*((unsigned int *)((unsigned long)context_ptr+0x00000960+4*4))=0x05862d4a;
*((unsigned int *)((unsigned long)context_ptr+0x00000960+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000020a&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000064b4,"\xd4\xf6\x57\x77\x9e\xb5\x06\xdd\xf9\x81\x2b\xe5\xeb\x9d\xee\xea\x1f\x2a\xa8\x99\x03\x4e\xc5\xa6\x29\x43\x01\x3f",28))
printf("strip: d4f657779eb506dd, Pass\n");
else
printf("strip: d4f657779eb506dd, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000063ac))=0x020a0012;
*((unsigned int *)((unsigned long)context_ptr+0x000063ac+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000063ac+4*2))=0x02020066;
*((unsigned int *)((unsigned long)context_ptr+0x000063ac+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x00006500))=0x9faff70d;
*((unsigned int *)((unsigned long)context_ptr+0x00006500+4*1))=0x953c964d;
*((unsigned int *)((unsigned long)context_ptr+0x00006500+4*2))=0xc4f6e664;
*((unsigned int *)((unsigned long)context_ptr+0x00006500+4*3))=0x1bfac9d1;
*((unsigned int *)((unsigned long)context_ptr+0x00006500+4*4))=0xdf82e8ca;
*((unsigned int *)((unsigned long)context_ptr+0x00006500+4*5))=0x7bcd07cc;
*((unsigned int *)((unsigned long)context_ptr+0x00006500+4*6))=0x9798559b;
*((unsigned int *)((unsigned long)context_ptr+0x00006500+4*7))=0xa92e8025;
*((unsigned int *)((unsigned long)context_ptr+0x00006500+4*8))=0xf5975b0d;
*((unsigned int *)((unsigned long)context_ptr+0x00006500+4*9))=0x50652719;
*((unsigned int *)((unsigned long)context_ptr+0x00006500+4*10))=0xab21d3b5;
*((unsigned int *)((unsigned long)context_ptr+0x00006500+4*11))=0x4457e9cb;
*((unsigned int *)((unsigned long)context_ptr+0x00006500+4*12))=0xb29066bf;
*((unsigned int *)((unsigned long)context_ptr+0x00006500+4*13))=0xbbeebf4d;
*((unsigned int *)((unsigned long)context_ptr+0x00006500+4*14))=0x91ef7953;
*((unsigned int *)((unsigned long)context_ptr+0x00006500+4*15))=0xe85c801c;
*((unsigned int *)((unsigned long)context_ptr+0x00006500+4*16))=0xed092f8d;
*((unsigned int *)((unsigned long)context_ptr+0x00006500+4*17))=0x5d68a727;
*((unsigned int *)((unsigned long)context_ptr+0x00006500+4*18))=0x492f6eb8;
*((unsigned int *)((unsigned long)context_ptr+0x00006500+4*19))=0x73d19563;
*((unsigned int *)((unsigned long)context_ptr+0x00006500+4*20))=0xcc6156f1;
*((unsigned int *)((unsigned long)context_ptr+0x00006500+4*21))=0xa590ff5e;
*((unsigned int *)((unsigned long)context_ptr+0x00006500+4*22))=0x59b05688;
*((unsigned int *)((unsigned long)context_ptr+0x00006500+4*23))=0xa45a2316;
*((unsigned int *)((unsigned long)context_ptr+0x00006500+4*24))=0xb2225746;
*((unsigned int *)((unsigned long)context_ptr+0x00006500+4*25))=0x0000ff0a;
*((unsigned int *)((unsigned long)context_ptr+0x00003978))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003978+4*1))=0x000064b4;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000978+4*1))=0x00006500;
*((unsigned int *)((unsigned long)context_ptr+0x00000978+4*2))=0x000063ac;
*((unsigned int *)((unsigned long)context_ptr+0x00000978+4*3))=0x02220066;
*((unsigned int *)((unsigned long)context_ptr+0x00000978+4*4))=0x0b1896ee;
*((unsigned int *)((unsigned long)context_ptr+0x00000978+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000210&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000063c0,"\x18\xda\x85\xba\x68\xed\xf2\xf6\xf5\x8a\x4b\x7b\x22\x2a\x6e\xa6\x0c\x13\x90\x8e\xcd\x91\x5e\x89\xb5\x95\xa8\xc8",28))
printf("strip: 18da85ba68edf2f6, Pass\n");
else
printf("strip: 18da85ba68edf2f6, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000064d0))=0x020a0012;
*((unsigned int *)((unsigned long)context_ptr+0x000064d0+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000064d0+4*2))=0x02020067;
*((unsigned int *)((unsigned long)context_ptr+0x000064d0+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x0000662c))=0xc256d510;
*((unsigned int *)((unsigned long)context_ptr+0x0000662c+4*1))=0xe567adfd;
*((unsigned int *)((unsigned long)context_ptr+0x0000662c+4*2))=0x56783947;
*((unsigned int *)((unsigned long)context_ptr+0x0000662c+4*3))=0x93f05fe7;
*((unsigned int *)((unsigned long)context_ptr+0x0000662c+4*4))=0xa0196a0f;
*((unsigned int *)((unsigned long)context_ptr+0x0000662c+4*5))=0x28999185;
*((unsigned int *)((unsigned long)context_ptr+0x0000662c+4*6))=0xe3138470;
*((unsigned int *)((unsigned long)context_ptr+0x0000662c+4*7))=0x88ffe858;
*((unsigned int *)((unsigned long)context_ptr+0x0000662c+4*8))=0xc47a53ab;
*((unsigned int *)((unsigned long)context_ptr+0x0000662c+4*9))=0xa45ca6ef;
*((unsigned int *)((unsigned long)context_ptr+0x0000662c+4*10))=0xaf887086;
*((unsigned int *)((unsigned long)context_ptr+0x0000662c+4*11))=0x3a816526;
*((unsigned int *)((unsigned long)context_ptr+0x0000662c+4*12))=0x9e918587;
*((unsigned int *)((unsigned long)context_ptr+0x0000662c+4*13))=0x7d36bd50;
*((unsigned int *)((unsigned long)context_ptr+0x0000662c+4*14))=0xf74a42e3;
*((unsigned int *)((unsigned long)context_ptr+0x0000662c+4*15))=0x85550fd9;
*((unsigned int *)((unsigned long)context_ptr+0x0000662c+4*16))=0xa961ae3d;
*((unsigned int *)((unsigned long)context_ptr+0x0000662c+4*17))=0x59e90d91;
*((unsigned int *)((unsigned long)context_ptr+0x0000662c+4*18))=0x08ebea00;
*((unsigned int *)((unsigned long)context_ptr+0x0000662c+4*19))=0x34073ef3;
*((unsigned int *)((unsigned long)context_ptr+0x0000662c+4*20))=0xf097511e;
*((unsigned int *)((unsigned long)context_ptr+0x0000662c+4*21))=0x68b70563;
*((unsigned int *)((unsigned long)context_ptr+0x0000662c+4*22))=0x35def350;
*((unsigned int *)((unsigned long)context_ptr+0x0000662c+4*23))=0x9ccf1f36;
*((unsigned int *)((unsigned long)context_ptr+0x0000662c+4*24))=0x784cc6ac;
*((unsigned int *)((unsigned long)context_ptr+0x0000662c+4*25))=0x003e5210;
*((unsigned int *)((unsigned long)context_ptr+0x00003990))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003990+4*1))=0x000063bc;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000990+4*1))=0x0000662c;
*((unsigned int *)((unsigned long)context_ptr+0x00000990+4*2))=0x000064d0;
*((unsigned int *)((unsigned long)context_ptr+0x00000990+4*3))=0x02220067;
*((unsigned int *)((unsigned long)context_ptr+0x00000990+4*4))=0x03d8698b;
*((unsigned int *)((unsigned long)context_ptr+0x00000990+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000216&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000066d0,"\xb3\x29\x1a\x6f\x0b\x54\x91\x25\x58\x9f\xe2\xcf\x34\x2b\xf6\x3d\xa6\x6b\x56\x19\xf9\xc8\x20\xda\xd8\xc6\xc5\x06",28))
printf("strip: b3291a6f0b549125, Pass\n");
else
printf("strip: b3291a6f0b549125, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000063d8))=0x020a0012;
*((unsigned int *)((unsigned long)context_ptr+0x000063d8+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000063d8+4*2))=0x02020068;
*((unsigned int *)((unsigned long)context_ptr+0x000063d8+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x00006568))=0x4a857fcc;
*((unsigned int *)((unsigned long)context_ptr+0x00006568+4*1))=0xc2ebff0c;
*((unsigned int *)((unsigned long)context_ptr+0x00006568+4*2))=0xf3bb5c45;
*((unsigned int *)((unsigned long)context_ptr+0x00006568+4*3))=0xb17dd974;
*((unsigned int *)((unsigned long)context_ptr+0x00006568+4*4))=0xc4afbde7;
*((unsigned int *)((unsigned long)context_ptr+0x00006568+4*5))=0x809414d9;
*((unsigned int *)((unsigned long)context_ptr+0x00006568+4*6))=0x98522da7;
*((unsigned int *)((unsigned long)context_ptr+0x00006568+4*7))=0x66153cc5;
*((unsigned int *)((unsigned long)context_ptr+0x00006568+4*8))=0x03486f86;
*((unsigned int *)((unsigned long)context_ptr+0x00006568+4*9))=0xb00bb6b0;
*((unsigned int *)((unsigned long)context_ptr+0x00006568+4*10))=0xbfcc1a3d;
*((unsigned int *)((unsigned long)context_ptr+0x00006568+4*11))=0x2563798b;
*((unsigned int *)((unsigned long)context_ptr+0x00006568+4*12))=0x1f15154c;
*((unsigned int *)((unsigned long)context_ptr+0x00006568+4*13))=0x8fec192e;
*((unsigned int *)((unsigned long)context_ptr+0x00006568+4*14))=0x3b82fe58;
*((unsigned int *)((unsigned long)context_ptr+0x00006568+4*15))=0xd1e0cc87;
*((unsigned int *)((unsigned long)context_ptr+0x00006568+4*16))=0xbcb72757;
*((unsigned int *)((unsigned long)context_ptr+0x00006568+4*17))=0x7fa0aa98;
*((unsigned int *)((unsigned long)context_ptr+0x00006568+4*18))=0x3452fa28;
*((unsigned int *)((unsigned long)context_ptr+0x00006568+4*19))=0x551512ac;
*((unsigned int *)((unsigned long)context_ptr+0x00006568+4*20))=0x3f3d63f4;
*((unsigned int *)((unsigned long)context_ptr+0x00006568+4*21))=0x019d0e6f;
*((unsigned int *)((unsigned long)context_ptr+0x00006568+4*22))=0x6cff9417;
*((unsigned int *)((unsigned long)context_ptr+0x00006568+4*23))=0xf3acf373;
*((unsigned int *)((unsigned long)context_ptr+0x00006568+4*24))=0x47906f27;
*((unsigned int *)((unsigned long)context_ptr+0x00006568+4*25))=0xa17ac71b;
*((unsigned int *)((unsigned long)context_ptr+0x000039a8))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x000039a8+4*1))=0x000067e8;
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
*((unsigned int *)((unsigned long)context_ptr+0x000009a8+4*1))=0x00006568;
*((unsigned int *)((unsigned long)context_ptr+0x000009a8+4*2))=0x000063d8;
*((unsigned int *)((unsigned long)context_ptr+0x000009a8+4*3))=0x02220068;
*((unsigned int *)((unsigned long)context_ptr+0x000009a8+4*4))=0x0e7460c9;
*((unsigned int *)((unsigned long)context_ptr+0x000009a8+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000021c&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000065d8,"\x31\x87\xad\xad\x12\xd3\x9e\xa4\xc9\x5f\x77\x5a\x0d\x46\x4f\x5c\xc2\x14\xe1\xa6\xc6\x44\x6d\x46\x3d\x76\x5c\x42",28))
printf("strip: 3187adad12d39ea4, Pass\n");
else
printf("strip: 3187adad12d39ea4, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000064e0))=0x020a0012;
*((unsigned int *)((unsigned long)context_ptr+0x000064e0+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000064e0+4*2))=0x02020069;
*((unsigned int *)((unsigned long)context_ptr+0x000064e0+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x000061b0))=0x15d91689;
*((unsigned int *)((unsigned long)context_ptr+0x000061b0+4*1))=0x0f8821f7;
*((unsigned int *)((unsigned long)context_ptr+0x000061b0+4*2))=0x3c28d744;
*((unsigned int *)((unsigned long)context_ptr+0x000061b0+4*3))=0x223fd1ec;
*((unsigned int *)((unsigned long)context_ptr+0x000061b0+4*4))=0xbc5458ea;
*((unsigned int *)((unsigned long)context_ptr+0x000061b0+4*5))=0xe63cc87c;
*((unsigned int *)((unsigned long)context_ptr+0x000061b0+4*6))=0x03352b82;
*((unsigned int *)((unsigned long)context_ptr+0x000061b0+4*7))=0xe20fd5aa;
*((unsigned int *)((unsigned long)context_ptr+0x000061b0+4*8))=0xbb30bec6;
*((unsigned int *)((unsigned long)context_ptr+0x000061b0+4*9))=0xd5e44f5e;
*((unsigned int *)((unsigned long)context_ptr+0x000061b0+4*10))=0x3b83e703;
*((unsigned int *)((unsigned long)context_ptr+0x000061b0+4*11))=0x00e3c966;
*((unsigned int *)((unsigned long)context_ptr+0x000061b0+4*12))=0x8a2be094;
*((unsigned int *)((unsigned long)context_ptr+0x000061b0+4*13))=0x13bbdc2a;
*((unsigned int *)((unsigned long)context_ptr+0x000061b0+4*14))=0xd3cea7f4;
*((unsigned int *)((unsigned long)context_ptr+0x000061b0+4*15))=0x39e12861;
*((unsigned int *)((unsigned long)context_ptr+0x000061b0+4*16))=0x5feb27e5;
*((unsigned int *)((unsigned long)context_ptr+0x000061b0+4*17))=0x0a0dbe79;
*((unsigned int *)((unsigned long)context_ptr+0x000061b0+4*18))=0x05aa128f;
*((unsigned int *)((unsigned long)context_ptr+0x000061b0+4*19))=0x98b86e1c;
*((unsigned int *)((unsigned long)context_ptr+0x000061b0+4*20))=0x2ab5d46b;
*((unsigned int *)((unsigned long)context_ptr+0x000061b0+4*21))=0xe6751116;
*((unsigned int *)((unsigned long)context_ptr+0x000061b0+4*22))=0x0c5f65d9;
*((unsigned int *)((unsigned long)context_ptr+0x000061b0+4*23))=0xcb3be340;
*((unsigned int *)((unsigned long)context_ptr+0x000061b0+4*24))=0x0df89183;
*((unsigned int *)((unsigned long)context_ptr+0x000061b0+4*25))=0xfff06e05;
*((unsigned int *)((unsigned long)context_ptr+0x000061b0+4*26))=0x00000064;
*((unsigned int *)((unsigned long)context_ptr+0x000039c0))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x000039c0+4*1))=0x000065d0;
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
*((unsigned int *)((unsigned long)context_ptr+0x000009c0+4*1))=0x000061b0;
*((unsigned int *)((unsigned long)context_ptr+0x000009c0+4*2))=0x000064e0;
*((unsigned int *)((unsigned long)context_ptr+0x000009c0+4*3))=0x02220069;
*((unsigned int *)((unsigned long)context_ptr+0x000009c0+4*4))=0x046245ef;
*((unsigned int *)((unsigned long)context_ptr+0x000009c0+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000222&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000066ec,"\x11\xea\x3b\x36\x00\x9d\x83\x3e\x39\xfc\x4d\xe5\x8d\x9f\x82\x94\x83\x97\x7c\x02\xa6\x7f\x08\xc9\xf7\x55\x5d\x1f",28))
printf("strip: 11ea3b36009d833e, Pass\n");
else
printf("strip: 11ea3b36009d833e, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006018))=0x020a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006018+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006018+4*2))=0x0202006a;
*((unsigned int *)((unsigned long)context_ptr+0x00006018+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x00006694))=0xa5d958f6;
*((unsigned int *)((unsigned long)context_ptr+0x00006694+4*1))=0x39df63e7;
*((unsigned int *)((unsigned long)context_ptr+0x00006694+4*2))=0x1806fb9f;
*((unsigned int *)((unsigned long)context_ptr+0x00006694+4*3))=0x8fec395e;
*((unsigned int *)((unsigned long)context_ptr+0x00006694+4*4))=0xa6132433;
*((unsigned int *)((unsigned long)context_ptr+0x00006694+4*5))=0x6ac70adc;
*((unsigned int *)((unsigned long)context_ptr+0x00006694+4*6))=0xbacb2f08;
*((unsigned int *)((unsigned long)context_ptr+0x00006694+4*7))=0x52bfb066;
*((unsigned int *)((unsigned long)context_ptr+0x00006694+4*8))=0xb9d9f37f;
*((unsigned int *)((unsigned long)context_ptr+0x00006694+4*9))=0x31c47899;
*((unsigned int *)((unsigned long)context_ptr+0x00006694+4*10))=0x0f06b14a;
*((unsigned int *)((unsigned long)context_ptr+0x00006694+4*11))=0xabb63cc9;
*((unsigned int *)((unsigned long)context_ptr+0x00006694+4*12))=0x01c3dc01;
*((unsigned int *)((unsigned long)context_ptr+0x00006694+4*13))=0x73e5dc05;
*((unsigned int *)((unsigned long)context_ptr+0x00006694+4*14))=0xb06f2c27;
*((unsigned int *)((unsigned long)context_ptr+0x00006694+4*15))=0xc310c08e;
*((unsigned int *)((unsigned long)context_ptr+0x00006694+4*16))=0x47d2ce45;
*((unsigned int *)((unsigned long)context_ptr+0x00006694+4*17))=0xc9f501d3;
*((unsigned int *)((unsigned long)context_ptr+0x00006694+4*18))=0x65c6d483;
*((unsigned int *)((unsigned long)context_ptr+0x00006694+4*19))=0xd922a088;
*((unsigned int *)((unsigned long)context_ptr+0x00006694+4*20))=0xfced0d0e;
*((unsigned int *)((unsigned long)context_ptr+0x00006694+4*21))=0xff01479f;
*((unsigned int *)((unsigned long)context_ptr+0x00006694+4*22))=0x2284a32e;
*((unsigned int *)((unsigned long)context_ptr+0x00006694+4*23))=0xbf854af4;
*((unsigned int *)((unsigned long)context_ptr+0x00006694+4*24))=0x8b7acaf0;
*((unsigned int *)((unsigned long)context_ptr+0x00006694+4*25))=0x59437a74;
*((unsigned int *)((unsigned long)context_ptr+0x00006694+4*26))=0x00005b42;
*((unsigned int *)((unsigned long)context_ptr+0x000039d8))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x000039d8+4*1))=0x0000621c;
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
*((unsigned int *)((unsigned long)context_ptr+0x000009d8+4*1))=0x00006694;
*((unsigned int *)((unsigned long)context_ptr+0x000009d8+4*2))=0x00006018;
*((unsigned int *)((unsigned long)context_ptr+0x000009d8+4*3))=0x0222006a;
*((unsigned int *)((unsigned long)context_ptr+0x000009d8+4*4))=0x04712c4b;
*((unsigned int *)((unsigned long)context_ptr+0x000009d8+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000228&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006038,"\xaa\x3f\x2b\x11\xdd\x58\xed\x18\xd3\x15\x21\x74\x76\xbd\x4c\x32\x4b\x8d\xbc\xd1\xf9\x31\x26\xb9\xd0\x5b\x97\xe0",28))
printf("strip: aa3f2b11dd58ed18, Pass\n");
else
printf("strip: aa3f2b11dd58ed18, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006008))=0x020a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006008+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006008+4*2))=0x0202006b;
*((unsigned int *)((unsigned long)context_ptr+0x00006008+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x00006238))=0x25b89624;
*((unsigned int *)((unsigned long)context_ptr+0x00006238+4*1))=0x993ca260;
*((unsigned int *)((unsigned long)context_ptr+0x00006238+4*2))=0x8c94a455;
*((unsigned int *)((unsigned long)context_ptr+0x00006238+4*3))=0x2859dc1e;
*((unsigned int *)((unsigned long)context_ptr+0x00006238+4*4))=0x7337d8c2;
*((unsigned int *)((unsigned long)context_ptr+0x00006238+4*5))=0xa7655795;
*((unsigned int *)((unsigned long)context_ptr+0x00006238+4*6))=0x05e0a0ef;
*((unsigned int *)((unsigned long)context_ptr+0x00006238+4*7))=0x72de848a;
*((unsigned int *)((unsigned long)context_ptr+0x00006238+4*8))=0x5e7abdc0;
*((unsigned int *)((unsigned long)context_ptr+0x00006238+4*9))=0xe0816722;
*((unsigned int *)((unsigned long)context_ptr+0x00006238+4*10))=0x2f1049bd;
*((unsigned int *)((unsigned long)context_ptr+0x00006238+4*11))=0xc7d129c1;
*((unsigned int *)((unsigned long)context_ptr+0x00006238+4*12))=0x8274542d;
*((unsigned int *)((unsigned long)context_ptr+0x00006238+4*13))=0x1b1e16c4;
*((unsigned int *)((unsigned long)context_ptr+0x00006238+4*14))=0xcf1b67b4;
*((unsigned int *)((unsigned long)context_ptr+0x00006238+4*15))=0x35d1d21f;
*((unsigned int *)((unsigned long)context_ptr+0x00006238+4*16))=0xca525d9b;
*((unsigned int *)((unsigned long)context_ptr+0x00006238+4*17))=0x5e91474c;
*((unsigned int *)((unsigned long)context_ptr+0x00006238+4*18))=0xedaebd92;
*((unsigned int *)((unsigned long)context_ptr+0x00006238+4*19))=0xe8f3810c;
*((unsigned int *)((unsigned long)context_ptr+0x00006238+4*20))=0x8c542f83;
*((unsigned int *)((unsigned long)context_ptr+0x00006238+4*21))=0xd4d251bc;
*((unsigned int *)((unsigned long)context_ptr+0x00006238+4*22))=0xf58aa1f8;
*((unsigned int *)((unsigned long)context_ptr+0x00006238+4*23))=0xf96528e3;
*((unsigned int *)((unsigned long)context_ptr+0x00006238+4*24))=0xb0884118;
*((unsigned int *)((unsigned long)context_ptr+0x00006238+4*25))=0x31e55685;
*((unsigned int *)((unsigned long)context_ptr+0x00006238+4*26))=0x00ec0c3f;
*((unsigned int *)((unsigned long)context_ptr+0x000039f0))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x000039f0+4*1))=0x00006038;
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
*((unsigned int *)((unsigned long)context_ptr+0x000009f0+4*1))=0x00006238;
*((unsigned int *)((unsigned long)context_ptr+0x000009f0+4*2))=0x00006008;
*((unsigned int *)((unsigned long)context_ptr+0x000009f0+4*3))=0x0222006b;
*((unsigned int *)((unsigned long)context_ptr+0x000009f0+4*4))=0x055e95db;
*((unsigned int *)((unsigned long)context_ptr+0x000009f0+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000022e&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000062c8,"\xf0\xca\x14\x9a\x1d\x0b\x57\x29\xf7\xbb\xe6\x5b\x2e\x71\xe6\x36\xcf\x7b\xd4\x01\x59\x4f\xc3\x37\xab\xe3\x41\xd9",28))
printf("strip: f0ca149a1d0b5729, Pass\n");
else
printf("strip: f0ca149a1d0b5729, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006028))=0x020a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006028+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006028+4*2))=0x0202006c;
*((unsigned int *)((unsigned long)context_ptr+0x00006028+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x00006804))=0xcaecf7e6;
*((unsigned int *)((unsigned long)context_ptr+0x00006804+4*1))=0x0e6d0441;
*((unsigned int *)((unsigned long)context_ptr+0x00006804+4*2))=0xfbe2799a;
*((unsigned int *)((unsigned long)context_ptr+0x00006804+4*3))=0xac176e20;
*((unsigned int *)((unsigned long)context_ptr+0x00006804+4*4))=0xdc26f88c;
*((unsigned int *)((unsigned long)context_ptr+0x00006804+4*5))=0x71c65d7b;
*((unsigned int *)((unsigned long)context_ptr+0x00006804+4*6))=0x76f7f69b;
*((unsigned int *)((unsigned long)context_ptr+0x00006804+4*7))=0x3b946332;
*((unsigned int *)((unsigned long)context_ptr+0x00006804+4*8))=0xee461c0a;
*((unsigned int *)((unsigned long)context_ptr+0x00006804+4*9))=0x7ba1fbfe;
*((unsigned int *)((unsigned long)context_ptr+0x00006804+4*10))=0x4c8f9bce;
*((unsigned int *)((unsigned long)context_ptr+0x00006804+4*11))=0xc8fefcf4;
*((unsigned int *)((unsigned long)context_ptr+0x00006804+4*12))=0xbe668afd;
*((unsigned int *)((unsigned long)context_ptr+0x00006804+4*13))=0x86bb680a;
*((unsigned int *)((unsigned long)context_ptr+0x00006804+4*14))=0x1fdf8107;
*((unsigned int *)((unsigned long)context_ptr+0x00006804+4*15))=0xc5995c3a;
*((unsigned int *)((unsigned long)context_ptr+0x00006804+4*16))=0xb5011898;
*((unsigned int *)((unsigned long)context_ptr+0x00006804+4*17))=0x2b846429;
*((unsigned int *)((unsigned long)context_ptr+0x00006804+4*18))=0x14778fb3;
*((unsigned int *)((unsigned long)context_ptr+0x00006804+4*19))=0x00e07d7a;
*((unsigned int *)((unsigned long)context_ptr+0x00006804+4*20))=0x232040bc;
*((unsigned int *)((unsigned long)context_ptr+0x00006804+4*21))=0x4977132c;
*((unsigned int *)((unsigned long)context_ptr+0x00006804+4*22))=0x91baa04f;
*((unsigned int *)((unsigned long)context_ptr+0x00006804+4*23))=0xfed21933;
*((unsigned int *)((unsigned long)context_ptr+0x00006804+4*24))=0x1510973c;
*((unsigned int *)((unsigned long)context_ptr+0x00006804+4*25))=0x62bcbe1a;
*((unsigned int *)((unsigned long)context_ptr+0x00006804+4*26))=0x65c529fc;
*((unsigned int *)((unsigned long)context_ptr+0x00003a08))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003a08+4*1))=0x000062a4;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000a08+4*1))=0x00006804;
*((unsigned int *)((unsigned long)context_ptr+0x00000a08+4*2))=0x00006028;
*((unsigned int *)((unsigned long)context_ptr+0x00000a08+4*3))=0x0222006c;
*((unsigned int *)((unsigned long)context_ptr+0x00000a08+4*4))=0x037cd694;
*((unsigned int *)((unsigned long)context_ptr+0x00000a08+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000234&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000065f4,"\x4b\x2f\x7d\xce\xeb\xfa\xae\xa6\xba\xf2\xd7\xa9\x7e\x89\x2b\x2a\x10\x20\x2c\x81\x11\x1f\x9f\xd6\x88\x79\xfa\x33",28))
printf("strip: 4b2f7dceebfaaea6, Pass\n");
else
printf("strip: 4b2f7dceebfaaea6, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006054))=0x020a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006054+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006054+4*2))=0x0202006d;
*((unsigned int *)((unsigned long)context_ptr+0x00006054+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x00006928))=0xcb0f6dec;
*((unsigned int *)((unsigned long)context_ptr+0x00006928+4*1))=0xe6dcad3a;
*((unsigned int *)((unsigned long)context_ptr+0x00006928+4*2))=0x5db2be0c;
*((unsigned int *)((unsigned long)context_ptr+0x00006928+4*3))=0xe1332b9a;
*((unsigned int *)((unsigned long)context_ptr+0x00006928+4*4))=0xb9afbc42;
*((unsigned int *)((unsigned long)context_ptr+0x00006928+4*5))=0x980e8a47;
*((unsigned int *)((unsigned long)context_ptr+0x00006928+4*6))=0x32b6f31d;
*((unsigned int *)((unsigned long)context_ptr+0x00006928+4*7))=0x9a10747f;
*((unsigned int *)((unsigned long)context_ptr+0x00006928+4*8))=0x22155732;
*((unsigned int *)((unsigned long)context_ptr+0x00006928+4*9))=0xaf0375a7;
*((unsigned int *)((unsigned long)context_ptr+0x00006928+4*10))=0x80c037bd;
*((unsigned int *)((unsigned long)context_ptr+0x00006928+4*11))=0x2eb81a37;
*((unsigned int *)((unsigned long)context_ptr+0x00006928+4*12))=0xe09bdeb3;
*((unsigned int *)((unsigned long)context_ptr+0x00006928+4*13))=0xfd9cd956;
*((unsigned int *)((unsigned long)context_ptr+0x00006928+4*14))=0xb36ba076;
*((unsigned int *)((unsigned long)context_ptr+0x00006928+4*15))=0x05d91b31;
*((unsigned int *)((unsigned long)context_ptr+0x00006928+4*16))=0x2a92eb59;
*((unsigned int *)((unsigned long)context_ptr+0x00006928+4*17))=0x9d73e272;
*((unsigned int *)((unsigned long)context_ptr+0x00006928+4*18))=0x47b1d068;
*((unsigned int *)((unsigned long)context_ptr+0x00006928+4*19))=0x9254934b;
*((unsigned int *)((unsigned long)context_ptr+0x00006928+4*20))=0x82dff9c3;
*((unsigned int *)((unsigned long)context_ptr+0x00006928+4*21))=0x5a6e3058;
*((unsigned int *)((unsigned long)context_ptr+0x00006928+4*22))=0xe0d2b147;
*((unsigned int *)((unsigned long)context_ptr+0x00006928+4*23))=0x7334e5f9;
*((unsigned int *)((unsigned long)context_ptr+0x00006928+4*24))=0x349587fa;
*((unsigned int *)((unsigned long)context_ptr+0x00006928+4*25))=0x4f0e5093;
*((unsigned int *)((unsigned long)context_ptr+0x00006928+4*26))=0x80aadcf4;
*((unsigned int *)((unsigned long)context_ptr+0x00006928+4*27))=0x000000c3;
*((unsigned int *)((unsigned long)context_ptr+0x00003a20))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003a20+4*1))=0x000062c0;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000a20+4*1))=0x00006928;
*((unsigned int *)((unsigned long)context_ptr+0x00000a20+4*2))=0x00006054;
*((unsigned int *)((unsigned long)context_ptr+0x00000a20+4*3))=0x0222006d;
*((unsigned int *)((unsigned long)context_ptr+0x00000a20+4*4))=0x07783ee7;
*((unsigned int *)((unsigned long)context_ptr+0x00000a20+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000023a&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006610,"\x45\x7e\x39\x5b\x29\x9e\x91\x47\xe5\x1f\xdb\xc9\xa7\x1d\x53\xc2\xdd\x2d\x7d\x52\xda\x7e\xb3\xff\x32\xdc\x60\xf6",28))
printf("strip: 457e395b299e9147, Pass\n");
else
printf("strip: 457e395b299e9147, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000065ec))=0x020a0012;
*((unsigned int *)((unsigned long)context_ptr+0x000065ec+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000065ec+4*2))=0x0202006e;
*((unsigned int *)((unsigned long)context_ptr+0x000065ec+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x000063e8))=0x1f31b45b;
*((unsigned int *)((unsigned long)context_ptr+0x000063e8+4*1))=0x4105aa35;
*((unsigned int *)((unsigned long)context_ptr+0x000063e8+4*2))=0x6ef4b2db;
*((unsigned int *)((unsigned long)context_ptr+0x000063e8+4*3))=0xe4cebf1f;
*((unsigned int *)((unsigned long)context_ptr+0x000063e8+4*4))=0x770019af;
*((unsigned int *)((unsigned long)context_ptr+0x000063e8+4*5))=0xee1f29c8;
*((unsigned int *)((unsigned long)context_ptr+0x000063e8+4*6))=0xe7716dbd;
*((unsigned int *)((unsigned long)context_ptr+0x000063e8+4*7))=0x9b8f08be;
*((unsigned int *)((unsigned long)context_ptr+0x000063e8+4*8))=0x9093b34d;
*((unsigned int *)((unsigned long)context_ptr+0x000063e8+4*9))=0x054e62ae;
*((unsigned int *)((unsigned long)context_ptr+0x000063e8+4*10))=0x42cddbb8;
*((unsigned int *)((unsigned long)context_ptr+0x000063e8+4*11))=0xa54ceabd;
*((unsigned int *)((unsigned long)context_ptr+0x000063e8+4*12))=0xc24728bf;
*((unsigned int *)((unsigned long)context_ptr+0x000063e8+4*13))=0x290c2ea2;
*((unsigned int *)((unsigned long)context_ptr+0x000063e8+4*14))=0xd052be32;
*((unsigned int *)((unsigned long)context_ptr+0x000063e8+4*15))=0x03dd4042;
*((unsigned int *)((unsigned long)context_ptr+0x000063e8+4*16))=0xac7cea4b;
*((unsigned int *)((unsigned long)context_ptr+0x000063e8+4*17))=0xa3baf79a;
*((unsigned int *)((unsigned long)context_ptr+0x000063e8+4*18))=0x4d9a034d;
*((unsigned int *)((unsigned long)context_ptr+0x000063e8+4*19))=0xc1c0d6c2;
*((unsigned int *)((unsigned long)context_ptr+0x000063e8+4*20))=0xeb77a6f3;
*((unsigned int *)((unsigned long)context_ptr+0x000063e8+4*21))=0x25234784;
*((unsigned int *)((unsigned long)context_ptr+0x000063e8+4*22))=0x962b2d19;
*((unsigned int *)((unsigned long)context_ptr+0x000063e8+4*23))=0xa043f804;
*((unsigned int *)((unsigned long)context_ptr+0x000063e8+4*24))=0xa7ee83f0;
*((unsigned int *)((unsigned long)context_ptr+0x000063e8+4*25))=0x4133fcad;
*((unsigned int *)((unsigned long)context_ptr+0x000063e8+4*26))=0x33189192;
*((unsigned int *)((unsigned long)context_ptr+0x000063e8+4*27))=0x0000855d;
*((unsigned int *)((unsigned long)context_ptr+0x00003a38))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003a38+4*1))=0x000065fc;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000a38+4*1))=0x000063e8;
*((unsigned int *)((unsigned long)context_ptr+0x00000a38+4*2))=0x000065ec;
*((unsigned int *)((unsigned long)context_ptr+0x00000a38+4*3))=0x0222006e;
*((unsigned int *)((unsigned long)context_ptr+0x00000a38+4*4))=0x0f1c4060;
*((unsigned int *)((unsigned long)context_ptr+0x00000a38+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000240&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006344,"\x98\xba\xae\x3a\x0b\x7c\x14\x55\x8a\x32\x3c\x26\xff\xd5\x42\x40\x63\x1f\x48\x9b\x7c\xc0\x1f\x7f\x8e\x4f\xef\xc3",28))
printf("strip: 98baae3a0b7c1455, Pass\n");
else
printf("strip: 98baae3a0b7c1455, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006458))=0x020a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006458+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006458+4*2))=0x0202006f;
*((unsigned int *)((unsigned long)context_ptr+0x00006458+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x000062dc))=0xffdfccaf;
*((unsigned int *)((unsigned long)context_ptr+0x000062dc+4*1))=0x37238fa9;
*((unsigned int *)((unsigned long)context_ptr+0x000062dc+4*2))=0xead897fb;
*((unsigned int *)((unsigned long)context_ptr+0x000062dc+4*3))=0xad51787c;
*((unsigned int *)((unsigned long)context_ptr+0x000062dc+4*4))=0xa41cd3f1;
*((unsigned int *)((unsigned long)context_ptr+0x000062dc+4*5))=0xfa197161;
*((unsigned int *)((unsigned long)context_ptr+0x000062dc+4*6))=0xd4c56373;
*((unsigned int *)((unsigned long)context_ptr+0x000062dc+4*7))=0xa43f6aa8;
*((unsigned int *)((unsigned long)context_ptr+0x000062dc+4*8))=0xe11dae58;
*((unsigned int *)((unsigned long)context_ptr+0x000062dc+4*9))=0x5153bbe1;
*((unsigned int *)((unsigned long)context_ptr+0x000062dc+4*10))=0x71b04b96;
*((unsigned int *)((unsigned long)context_ptr+0x000062dc+4*11))=0x7edb0348;
*((unsigned int *)((unsigned long)context_ptr+0x000062dc+4*12))=0x8ac07902;
*((unsigned int *)((unsigned long)context_ptr+0x000062dc+4*13))=0xa56e6462;
*((unsigned int *)((unsigned long)context_ptr+0x000062dc+4*14))=0xee1ecefa;
*((unsigned int *)((unsigned long)context_ptr+0x000062dc+4*15))=0x95f9654b;
*((unsigned int *)((unsigned long)context_ptr+0x000062dc+4*16))=0x2eeae00b;
*((unsigned int *)((unsigned long)context_ptr+0x000062dc+4*17))=0x4cfee03f;
*((unsigned int *)((unsigned long)context_ptr+0x000062dc+4*18))=0xbcfce445;
*((unsigned int *)((unsigned long)context_ptr+0x000062dc+4*19))=0xc3f85b25;
*((unsigned int *)((unsigned long)context_ptr+0x000062dc+4*20))=0x3e6e8251;
*((unsigned int *)((unsigned long)context_ptr+0x000062dc+4*21))=0x0e6506a3;
*((unsigned int *)((unsigned long)context_ptr+0x000062dc+4*22))=0xd0f8d3f1;
*((unsigned int *)((unsigned long)context_ptr+0x000062dc+4*23))=0x187272a0;
*((unsigned int *)((unsigned long)context_ptr+0x000062dc+4*24))=0xf85f4226;
*((unsigned int *)((unsigned long)context_ptr+0x000062dc+4*25))=0x4f612737;
*((unsigned int *)((unsigned long)context_ptr+0x000062dc+4*26))=0x4f18636b;
*((unsigned int *)((unsigned long)context_ptr+0x000062dc+4*27))=0x00eb1745;
*((unsigned int *)((unsigned long)context_ptr+0x00003a50))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003a50+4*1))=0x00006870;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000a50+4*1))=0x000062dc;
*((unsigned int *)((unsigned long)context_ptr+0x00000a50+4*2))=0x00006458;
*((unsigned int *)((unsigned long)context_ptr+0x00000a50+4*3))=0x0222006f;
*((unsigned int *)((unsigned long)context_ptr+0x00000a50+4*4))=0x0f596a3c;
*((unsigned int *)((unsigned long)context_ptr+0x00000a50+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000246&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000060c8,"\x40\x69\x1c\xee\xd3\x91\xb9\x4d\xa4\xf7\x72\x78\x84\x65\xea\xb0\x1d\xcd\x68\x8a\x6b\x5b\xef\xe5\x1b\x64\xb3\xc7",28))
printf("strip: 40691ceed391b94d, Pass\n");
else
printf("strip: 40691ceed391b94d, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006618))=0x020a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006618+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006618+4*2))=0x02020070;
*((unsigned int *)((unsigned long)context_ptr+0x00006618+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x00006064))=0xa9fe2bb9;
*((unsigned int *)((unsigned long)context_ptr+0x00006064+4*1))=0x6306a335;
*((unsigned int *)((unsigned long)context_ptr+0x00006064+4*2))=0x825de32c;
*((unsigned int *)((unsigned long)context_ptr+0x00006064+4*3))=0x8930c2f0;
*((unsigned int *)((unsigned long)context_ptr+0x00006064+4*4))=0xeaee9f69;
*((unsigned int *)((unsigned long)context_ptr+0x00006064+4*5))=0xab9403b2;
*((unsigned int *)((unsigned long)context_ptr+0x00006064+4*6))=0x5a6100ca;
*((unsigned int *)((unsigned long)context_ptr+0x00006064+4*7))=0xa22240a4;
*((unsigned int *)((unsigned long)context_ptr+0x00006064+4*8))=0xfa11425e;
*((unsigned int *)((unsigned long)context_ptr+0x00006064+4*9))=0x054c40a4;
*((unsigned int *)((unsigned long)context_ptr+0x00006064+4*10))=0xe32861c9;
*((unsigned int *)((unsigned long)context_ptr+0x00006064+4*11))=0xc3c81c33;
*((unsigned int *)((unsigned long)context_ptr+0x00006064+4*12))=0x1ab43009;
*((unsigned int *)((unsigned long)context_ptr+0x00006064+4*13))=0xdc54a9bb;
*((unsigned int *)((unsigned long)context_ptr+0x00006064+4*14))=0x0cd518ea;
*((unsigned int *)((unsigned long)context_ptr+0x00006064+4*15))=0x3a208eac;
*((unsigned int *)((unsigned long)context_ptr+0x00006064+4*16))=0x2a3c2b10;
*((unsigned int *)((unsigned long)context_ptr+0x00006064+4*17))=0xe58c438c;
*((unsigned int *)((unsigned long)context_ptr+0x00006064+4*18))=0xb92132af;
*((unsigned int *)((unsigned long)context_ptr+0x00006064+4*19))=0x9ee8d43b;
*((unsigned int *)((unsigned long)context_ptr+0x00006064+4*20))=0x19944148;
*((unsigned int *)((unsigned long)context_ptr+0x00006064+4*21))=0xac92d56a;
*((unsigned int *)((unsigned long)context_ptr+0x00006064+4*22))=0x8c9a2288;
*((unsigned int *)((unsigned long)context_ptr+0x00006064+4*23))=0xfaf783fc;
*((unsigned int *)((unsigned long)context_ptr+0x00006064+4*24))=0xc8d58b3b;
*((unsigned int *)((unsigned long)context_ptr+0x00006064+4*25))=0x8d1ffb6e;
*((unsigned int *)((unsigned long)context_ptr+0x00006064+4*26))=0x190a7910;
*((unsigned int *)((unsigned long)context_ptr+0x00006064+4*27))=0x1d6fec65;
*((unsigned int *)((unsigned long)context_ptr+0x00003a68))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003a68+4*1))=0x0000634c;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000a68+4*1))=0x00006064;
*((unsigned int *)((unsigned long)context_ptr+0x00000a68+4*2))=0x00006618;
*((unsigned int *)((unsigned long)context_ptr+0x00000a68+4*3))=0x02220070;
*((unsigned int *)((unsigned long)context_ptr+0x00000a68+4*4))=0x096c2053;
*((unsigned int *)((unsigned long)context_ptr+0x00000a68+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000024c&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006370,"\x08\x6a\xdc\x2c\xcc\x47\x1e\x72\xf7\xc1\xc2\x90\xee\x63\xbc\xe4\x76\x31\x75\x53\x61\x34\x24\x0e\x92\x75\xeb\x2f",28))
printf("strip: 086adc2ccc471e72, Pass\n");
else
printf("strip: 086adc2ccc471e72, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000064f0))=0x020a0012;
*((unsigned int *)((unsigned long)context_ptr+0x000064f0+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000064f0+4*2))=0x02020071;
*((unsigned int *)((unsigned long)context_ptr+0x000064f0+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x000060d4))=0xebe354e7;
*((unsigned int *)((unsigned long)context_ptr+0x000060d4+4*1))=0x7e97ed1e;
*((unsigned int *)((unsigned long)context_ptr+0x000060d4+4*2))=0x4f075893;
*((unsigned int *)((unsigned long)context_ptr+0x000060d4+4*3))=0xdfd41397;
*((unsigned int *)((unsigned long)context_ptr+0x000060d4+4*4))=0xd4b74270;
*((unsigned int *)((unsigned long)context_ptr+0x000060d4+4*5))=0x1ec952a9;
*((unsigned int *)((unsigned long)context_ptr+0x000060d4+4*6))=0xa00b6956;
*((unsigned int *)((unsigned long)context_ptr+0x000060d4+4*7))=0xc4a069c8;
*((unsigned int *)((unsigned long)context_ptr+0x000060d4+4*8))=0xef40f5c2;
*((unsigned int *)((unsigned long)context_ptr+0x000060d4+4*9))=0xeb5bc58a;
*((unsigned int *)((unsigned long)context_ptr+0x000060d4+4*10))=0xee07ce62;
*((unsigned int *)((unsigned long)context_ptr+0x000060d4+4*11))=0x7c65d35c;
*((unsigned int *)((unsigned long)context_ptr+0x000060d4+4*12))=0xe2ed0336;
*((unsigned int *)((unsigned long)context_ptr+0x000060d4+4*13))=0x5cea9541;
*((unsigned int *)((unsigned long)context_ptr+0x000060d4+4*14))=0x9e849399;
*((unsigned int *)((unsigned long)context_ptr+0x000060d4+4*15))=0xb74b1c1d;
*((unsigned int *)((unsigned long)context_ptr+0x000060d4+4*16))=0x79cb0063;
*((unsigned int *)((unsigned long)context_ptr+0x000060d4+4*17))=0x09c9b062;
*((unsigned int *)((unsigned long)context_ptr+0x000060d4+4*18))=0x87ba2a38;
*((unsigned int *)((unsigned long)context_ptr+0x000060d4+4*19))=0x03578f2d;
*((unsigned int *)((unsigned long)context_ptr+0x000060d4+4*20))=0xb2efeeef;
*((unsigned int *)((unsigned long)context_ptr+0x000060d4+4*21))=0x10af28cd;
*((unsigned int *)((unsigned long)context_ptr+0x000060d4+4*22))=0xf582bb55;
*((unsigned int *)((unsigned long)context_ptr+0x000060d4+4*23))=0xec63ab4a;
*((unsigned int *)((unsigned long)context_ptr+0x000060d4+4*24))=0x88605584;
*((unsigned int *)((unsigned long)context_ptr+0x000060d4+4*25))=0x709465f2;
*((unsigned int *)((unsigned long)context_ptr+0x000060d4+4*26))=0xbe6df191;
*((unsigned int *)((unsigned long)context_ptr+0x000060d4+4*27))=0x06862daf;
*((unsigned int *)((unsigned long)context_ptr+0x000060d4+4*28))=0x0000008f;
*((unsigned int *)((unsigned long)context_ptr+0x00003a80))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003a80+4*1))=0x00006368;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000a80+4*1))=0x000060d4;
*((unsigned int *)((unsigned long)context_ptr+0x00000a80+4*2))=0x000064f0;
*((unsigned int *)((unsigned long)context_ptr+0x00000a80+4*3))=0x02220071;
*((unsigned int *)((unsigned long)context_ptr+0x00000a80+4*4))=0x01f43f2a;
*((unsigned int *)((unsigned long)context_ptr+0x00000a80+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000252&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x0000646c,"\x41\x44\x41\x7f\xfb\xb2\x37\xf8\x3c\xec\xd9\x93\xe3\x60\x50\xac\x49\x80\xb7\x70\x1e\xcd\xf6\x7b\x37\x23\x2b\x14",28))
printf("strip: 4144417ffbb237f8, Pass\n");
else
printf("strip: 4144417ffbb237f8, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006384))=0x020a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006384+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006384+4*2))=0x02020072;
*((unsigned int *)((unsigned long)context_ptr+0x00006384+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x0000688c))=0x47cb593b;
*((unsigned int *)((unsigned long)context_ptr+0x0000688c+4*1))=0xe2608f68;
*((unsigned int *)((unsigned long)context_ptr+0x0000688c+4*2))=0x9000ec93;
*((unsigned int *)((unsigned long)context_ptr+0x0000688c+4*3))=0xc5338530;
*((unsigned int *)((unsigned long)context_ptr+0x0000688c+4*4))=0x9b843721;
*((unsigned int *)((unsigned long)context_ptr+0x0000688c+4*5))=0x07b508b5;
*((unsigned int *)((unsigned long)context_ptr+0x0000688c+4*6))=0x61002732;
*((unsigned int *)((unsigned long)context_ptr+0x0000688c+4*7))=0xa3120658;
*((unsigned int *)((unsigned long)context_ptr+0x0000688c+4*8))=0x2bfbd80a;
*((unsigned int *)((unsigned long)context_ptr+0x0000688c+4*9))=0x5fb94323;
*((unsigned int *)((unsigned long)context_ptr+0x0000688c+4*10))=0x0a523b6e;
*((unsigned int *)((unsigned long)context_ptr+0x0000688c+4*11))=0x559a46b6;
*((unsigned int *)((unsigned long)context_ptr+0x0000688c+4*12))=0x204dbb92;
*((unsigned int *)((unsigned long)context_ptr+0x0000688c+4*13))=0x0c3ffeba;
*((unsigned int *)((unsigned long)context_ptr+0x0000688c+4*14))=0x22ea5eb4;
*((unsigned int *)((unsigned long)context_ptr+0x0000688c+4*15))=0x78fa8225;
*((unsigned int *)((unsigned long)context_ptr+0x0000688c+4*16))=0xffe52d68;
*((unsigned int *)((unsigned long)context_ptr+0x0000688c+4*17))=0x9dcd8023;
*((unsigned int *)((unsigned long)context_ptr+0x0000688c+4*18))=0x2487cf39;
*((unsigned int *)((unsigned long)context_ptr+0x0000688c+4*19))=0xe0493dc6;
*((unsigned int *)((unsigned long)context_ptr+0x0000688c+4*20))=0xb1e6af93;
*((unsigned int *)((unsigned long)context_ptr+0x0000688c+4*21))=0x92b279d0;
*((unsigned int *)((unsigned long)context_ptr+0x0000688c+4*22))=0x524523be;
*((unsigned int *)((unsigned long)context_ptr+0x0000688c+4*23))=0x4d0435c8;
*((unsigned int *)((unsigned long)context_ptr+0x0000688c+4*24))=0xd7dc9886;
*((unsigned int *)((unsigned long)context_ptr+0x0000688c+4*25))=0x33573788;
*((unsigned int *)((unsigned long)context_ptr+0x0000688c+4*26))=0xe0e13cae;
*((unsigned int *)((unsigned long)context_ptr+0x0000688c+4*27))=0xf91d6b47;
*((unsigned int *)((unsigned long)context_ptr+0x0000688c+4*28))=0x00005d68;
*((unsigned int *)((unsigned long)context_ptr+0x00003a98))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003a98+4*1))=0x00006468;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000a98+4*1))=0x0000688c;
*((unsigned int *)((unsigned long)context_ptr+0x00000a98+4*2))=0x00006384;
*((unsigned int *)((unsigned long)context_ptr+0x00000a98+4*3))=0x02220072;
*((unsigned int *)((unsigned long)context_ptr+0x00000a98+4*4))=0x0fee75d9;
*((unsigned int *)((unsigned long)context_ptr+0x00000a98+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000258&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006488,"\x78\xb0\xa6\x65\x67\x2e\x6f\x05\x01\x62\xd8\x73\x1f\xe0\x3e\xa3\x22\x8b\x80\x18\xf8\x6f\x9f\x45\xaa\x11\x2c\x96",28))
printf("strip: 78b0a665672e6f05, Pass\n");
else
printf("strip: 78b0a665672e6f05, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006394))=0x020a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006394+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006394+4*2))=0x02020073;
*((unsigned int *)((unsigned long)context_ptr+0x00006394+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x00006700))=0x10ffbff7;
*((unsigned int *)((unsigned long)context_ptr+0x00006700+4*1))=0x079ef2f5;
*((unsigned int *)((unsigned long)context_ptr+0x00006700+4*2))=0xe5866614;
*((unsigned int *)((unsigned long)context_ptr+0x00006700+4*3))=0x2755f119;
*((unsigned int *)((unsigned long)context_ptr+0x00006700+4*4))=0x9da99c86;
*((unsigned int *)((unsigned long)context_ptr+0x00006700+4*5))=0xf5b7c0c7;
*((unsigned int *)((unsigned long)context_ptr+0x00006700+4*6))=0x51216a43;
*((unsigned int *)((unsigned long)context_ptr+0x00006700+4*7))=0x991a4a39;
*((unsigned int *)((unsigned long)context_ptr+0x00006700+4*8))=0xaf3b8256;
*((unsigned int *)((unsigned long)context_ptr+0x00006700+4*9))=0x5f6ef8ab;
*((unsigned int *)((unsigned long)context_ptr+0x00006700+4*10))=0xdca87a08;
*((unsigned int *)((unsigned long)context_ptr+0x00006700+4*11))=0x3dbf69e7;
*((unsigned int *)((unsigned long)context_ptr+0x00006700+4*12))=0x52cc3ef9;
*((unsigned int *)((unsigned long)context_ptr+0x00006700+4*13))=0x672f4d42;
*((unsigned int *)((unsigned long)context_ptr+0x00006700+4*14))=0x0c68224a;
*((unsigned int *)((unsigned long)context_ptr+0x00006700+4*15))=0x9e21a5e4;
*((unsigned int *)((unsigned long)context_ptr+0x00006700+4*16))=0x2f085b36;
*((unsigned int *)((unsigned long)context_ptr+0x00006700+4*17))=0x12c8f800;
*((unsigned int *)((unsigned long)context_ptr+0x00006700+4*18))=0xd045cd91;
*((unsigned int *)((unsigned long)context_ptr+0x00006700+4*19))=0x8f37638b;
*((unsigned int *)((unsigned long)context_ptr+0x00006700+4*20))=0xbb3a48aa;
*((unsigned int *)((unsigned long)context_ptr+0x00006700+4*21))=0x3b02864e;
*((unsigned int *)((unsigned long)context_ptr+0x00006700+4*22))=0xf72be13d;
*((unsigned int *)((unsigned long)context_ptr+0x00006700+4*23))=0xd63a1b35;
*((unsigned int *)((unsigned long)context_ptr+0x00006700+4*24))=0xa3b02769;
*((unsigned int *)((unsigned long)context_ptr+0x00006700+4*25))=0x67afb732;
*((unsigned int *)((unsigned long)context_ptr+0x00006700+4*26))=0xf33aef46;
*((unsigned int *)((unsigned long)context_ptr+0x00006700+4*27))=0x236e503c;
*((unsigned int *)((unsigned long)context_ptr+0x00006700+4*28))=0x000d5090;
*((unsigned int *)((unsigned long)context_ptr+0x00003ab0))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003ab0+4*1))=0x00006484;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000ab0+4*1))=0x00006700;
*((unsigned int *)((unsigned long)context_ptr+0x00000ab0+4*2))=0x00006394;
*((unsigned int *)((unsigned long)context_ptr+0x00000ab0+4*3))=0x02220073;
*((unsigned int *)((unsigned long)context_ptr+0x00000ab0+4*4))=0x0634f0b3;
*((unsigned int *)((unsigned long)context_ptr+0x00000ab0+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000025e&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000067cc,"\xa7\x36\x34\xb3\xa0\x1c\x29\xba\xa0\x43\xb4\xda\x99\x50\x79\xdc\xe9\xb6\xc0\x92\x26\xc3\x00\x8c\x41\xc9\x15\x7f",28))
printf("strip: a73634b3a01c29ba, Pass\n");
else
printf("strip: a73634b3a01c29ba, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000064a0))=0x020a0012;
*((unsigned int *)((unsigned long)context_ptr+0x000064a0+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000064a0+4*2))=0x02020074;
*((unsigned int *)((unsigned long)context_ptr+0x000064a0+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x00006774))=0x02f5a65a;
*((unsigned int *)((unsigned long)context_ptr+0x00006774+4*1))=0x77a7df0e;
*((unsigned int *)((unsigned long)context_ptr+0x00006774+4*2))=0xdd6b143e;
*((unsigned int *)((unsigned long)context_ptr+0x00006774+4*3))=0x67a15bdc;
*((unsigned int *)((unsigned long)context_ptr+0x00006774+4*4))=0x117e3b10;
*((unsigned int *)((unsigned long)context_ptr+0x00006774+4*5))=0x5c96e513;
*((unsigned int *)((unsigned long)context_ptr+0x00006774+4*6))=0xd71539f2;
*((unsigned int *)((unsigned long)context_ptr+0x00006774+4*7))=0xdd13edc5;
*((unsigned int *)((unsigned long)context_ptr+0x00006774+4*8))=0x547ce0f0;
*((unsigned int *)((unsigned long)context_ptr+0x00006774+4*9))=0x4fd249d0;
*((unsigned int *)((unsigned long)context_ptr+0x00006774+4*10))=0xb5d6de30;
*((unsigned int *)((unsigned long)context_ptr+0x00006774+4*11))=0x9cd878e7;
*((unsigned int *)((unsigned long)context_ptr+0x00006774+4*12))=0xc9dc7008;
*((unsigned int *)((unsigned long)context_ptr+0x00006774+4*13))=0x41e853d7;
*((unsigned int *)((unsigned long)context_ptr+0x00006774+4*14))=0xcf0d1730;
*((unsigned int *)((unsigned long)context_ptr+0x00006774+4*15))=0x6a936cac;
*((unsigned int *)((unsigned long)context_ptr+0x00006774+4*16))=0x613aa6e6;
*((unsigned int *)((unsigned long)context_ptr+0x00006774+4*17))=0x41b793b0;
*((unsigned int *)((unsigned long)context_ptr+0x00006774+4*18))=0x44fe370b;
*((unsigned int *)((unsigned long)context_ptr+0x00006774+4*19))=0x2284a7e6;
*((unsigned int *)((unsigned long)context_ptr+0x00006774+4*20))=0x2ab09992;
*((unsigned int *)((unsigned long)context_ptr+0x00006774+4*21))=0x94d9d77d;
*((unsigned int *)((unsigned long)context_ptr+0x00006774+4*22))=0xb4e7a35e;
*((unsigned int *)((unsigned long)context_ptr+0x00006774+4*23))=0x0c551f87;
*((unsigned int *)((unsigned long)context_ptr+0x00006774+4*24))=0x8547ed9f;
*((unsigned int *)((unsigned long)context_ptr+0x00006774+4*25))=0x2505479d;
*((unsigned int *)((unsigned long)context_ptr+0x00006774+4*26))=0xac3d1f0c;
*((unsigned int *)((unsigned long)context_ptr+0x00006774+4*27))=0x28b9eef7;
*((unsigned int *)((unsigned long)context_ptr+0x00006774+4*28))=0xfe4e9d48;
*((unsigned int *)((unsigned long)context_ptr+0x00003ac8))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003ac8+4*1))=0x00006900;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000ac8+4*1))=0x00006774;
*((unsigned int *)((unsigned long)context_ptr+0x00000ac8+4*2))=0x000064a0;
*((unsigned int *)((unsigned long)context_ptr+0x00000ac8+4*3))=0x02220074;
*((unsigned int *)((unsigned long)context_ptr+0x00000ac8+4*4))=0x0fabaa72;
*((unsigned int *)((unsigned long)context_ptr+0x00000ac8+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000264&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000064b4,"\xe4\xb3\x88\x3e\x13\x16\xc9\x41\x18\x0c\xee\x31\xfe\xef\x84\x6d\xa5\x7e\x78\x47\x28\x55\xe9\xf8\xe8\xb1\x44\x5c",28))
printf("strip: e4b3883e1316c941, Pass\n");
else
printf("strip: e4b3883e1316c941, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000063a4))=0x020a0012;
*((unsigned int *)((unsigned long)context_ptr+0x000063a4+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000063a4+4*2))=0x02020075;
*((unsigned int *)((unsigned long)context_ptr+0x000063a4+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x00006998))=0xa9518e20;
*((unsigned int *)((unsigned long)context_ptr+0x00006998+4*1))=0xfd2ab048;
*((unsigned int *)((unsigned long)context_ptr+0x00006998+4*2))=0xdef9fa77;
*((unsigned int *)((unsigned long)context_ptr+0x00006998+4*3))=0xae6d8568;
*((unsigned int *)((unsigned long)context_ptr+0x00006998+4*4))=0x33e46a4e;
*((unsigned int *)((unsigned long)context_ptr+0x00006998+4*5))=0xdf823a6c;
*((unsigned int *)((unsigned long)context_ptr+0x00006998+4*6))=0x6008b4a1;
*((unsigned int *)((unsigned long)context_ptr+0x00006998+4*7))=0x003d5a3c;
*((unsigned int *)((unsigned long)context_ptr+0x00006998+4*8))=0x9945ab6f;
*((unsigned int *)((unsigned long)context_ptr+0x00006998+4*9))=0x75b0e468;
*((unsigned int *)((unsigned long)context_ptr+0x00006998+4*10))=0xbf8e80be;
*((unsigned int *)((unsigned long)context_ptr+0x00006998+4*11))=0xb7c8799f;
*((unsigned int *)((unsigned long)context_ptr+0x00006998+4*12))=0x1e021eb3;
*((unsigned int *)((unsigned long)context_ptr+0x00006998+4*13))=0x255f74bb;
*((unsigned int *)((unsigned long)context_ptr+0x00006998+4*14))=0x62796387;
*((unsigned int *)((unsigned long)context_ptr+0x00006998+4*15))=0x09053681;
*((unsigned int *)((unsigned long)context_ptr+0x00006998+4*16))=0xb4f17fd2;
*((unsigned int *)((unsigned long)context_ptr+0x00006998+4*17))=0xd23c0597;
*((unsigned int *)((unsigned long)context_ptr+0x00006998+4*18))=0xb799c6f0;
*((unsigned int *)((unsigned long)context_ptr+0x00006998+4*19))=0xd03d8ce8;
*((unsigned int *)((unsigned long)context_ptr+0x00006998+4*20))=0x5dd95db1;
*((unsigned int *)((unsigned long)context_ptr+0x00006998+4*21))=0xcd676f57;
*((unsigned int *)((unsigned long)context_ptr+0x00006998+4*22))=0x946cfe04;
*((unsigned int *)((unsigned long)context_ptr+0x00006998+4*23))=0x5419d4e1;
*((unsigned int *)((unsigned long)context_ptr+0x00006998+4*24))=0xe991245b;
*((unsigned int *)((unsigned long)context_ptr+0x00006998+4*25))=0x4a78eadb;
*((unsigned int *)((unsigned long)context_ptr+0x00006998+4*26))=0x4c9eb058;
*((unsigned int *)((unsigned long)context_ptr+0x00006998+4*27))=0xff92d803;
*((unsigned int *)((unsigned long)context_ptr+0x00006998+4*28))=0x1adb5d7f;
*((unsigned int *)((unsigned long)context_ptr+0x00006998+4*29))=0x00000093;
*((unsigned int *)((unsigned long)context_ptr+0x00003ae0))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003ae0+4*1))=0x000064b0;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000ae0+4*1))=0x00006998;
*((unsigned int *)((unsigned long)context_ptr+0x00000ae0+4*2))=0x000063a4;
*((unsigned int *)((unsigned long)context_ptr+0x00000ae0+4*3))=0x02220075;
*((unsigned int *)((unsigned long)context_ptr+0x00000ae0+4*4))=0x001912a7;
*((unsigned int *)((unsigned long)context_ptr+0x00000ae0+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000026a&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000063bc,"\x03\xde\x1b\x68\x13\x08\x3a\x73\x82\xe1\xde\x70\xed\x08\xf8\x23\xc4\xea\x82\x41\xd4\xa5\x3c\x43\xfc\x8e\x4b\xd2",28))
printf("strip: 03de1b6813083a73, Pass\n");
else
printf("strip: 03de1b6813083a73, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000064cc))=0x020a0012;
*((unsigned int *)((unsigned long)context_ptr+0x000064cc+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000064cc+4*2))=0x02020076;
*((unsigned int *)((unsigned long)context_ptr+0x000064cc+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x00006a10))=0xc825c9c7;
*((unsigned int *)((unsigned long)context_ptr+0x00006a10+4*1))=0xbd178865;
*((unsigned int *)((unsigned long)context_ptr+0x00006a10+4*2))=0xa300585a;
*((unsigned int *)((unsigned long)context_ptr+0x00006a10+4*3))=0xd091bf99;
*((unsigned int *)((unsigned long)context_ptr+0x00006a10+4*4))=0xc0ce85e7;
*((unsigned int *)((unsigned long)context_ptr+0x00006a10+4*5))=0x324f416a;
*((unsigned int *)((unsigned long)context_ptr+0x00006a10+4*6))=0xe21bebfa;
*((unsigned int *)((unsigned long)context_ptr+0x00006a10+4*7))=0x231c7eb9;
*((unsigned int *)((unsigned long)context_ptr+0x00006a10+4*8))=0x430585f6;
*((unsigned int *)((unsigned long)context_ptr+0x00006a10+4*9))=0xbddb640d;
*((unsigned int *)((unsigned long)context_ptr+0x00006a10+4*10))=0x4f558362;
*((unsigned int *)((unsigned long)context_ptr+0x00006a10+4*11))=0xb7ca8548;
*((unsigned int *)((unsigned long)context_ptr+0x00006a10+4*12))=0x742a9f27;
*((unsigned int *)((unsigned long)context_ptr+0x00006a10+4*13))=0x691fb8d0;
*((unsigned int *)((unsigned long)context_ptr+0x00006a10+4*14))=0x5a5a8adc;
*((unsigned int *)((unsigned long)context_ptr+0x00006a10+4*15))=0xcdb7216e;
*((unsigned int *)((unsigned long)context_ptr+0x00006a10+4*16))=0x5de42198;
*((unsigned int *)((unsigned long)context_ptr+0x00006a10+4*17))=0xb05cf8f9;
*((unsigned int *)((unsigned long)context_ptr+0x00006a10+4*18))=0x922fd1e0;
*((unsigned int *)((unsigned long)context_ptr+0x00006a10+4*19))=0x600dd4cb;
*((unsigned int *)((unsigned long)context_ptr+0x00006a10+4*20))=0x1a1a9ca5;
*((unsigned int *)((unsigned long)context_ptr+0x00006a10+4*21))=0xb641daeb;
*((unsigned int *)((unsigned long)context_ptr+0x00006a10+4*22))=0x74ec2077;
*((unsigned int *)((unsigned long)context_ptr+0x00006a10+4*23))=0x05f8571a;
*((unsigned int *)((unsigned long)context_ptr+0x00006a10+4*24))=0x2d94a68f;
*((unsigned int *)((unsigned long)context_ptr+0x00006a10+4*25))=0x6e20baf1;
*((unsigned int *)((unsigned long)context_ptr+0x00006a10+4*26))=0x3a419bb6;
*((unsigned int *)((unsigned long)context_ptr+0x00006a10+4*27))=0x61d8ec3b;
*((unsigned int *)((unsigned long)context_ptr+0x00006a10+4*28))=0xba46dcf1;
*((unsigned int *)((unsigned long)context_ptr+0x00006a10+4*29))=0x00008551;
*((unsigned int *)((unsigned long)context_ptr+0x00003af8))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003af8+4*1))=0x000063b4;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000af8+4*1))=0x00006a10;
*((unsigned int *)((unsigned long)context_ptr+0x00000af8+4*2))=0x000064cc;
*((unsigned int *)((unsigned long)context_ptr+0x00000af8+4*3))=0x02220076;
*((unsigned int *)((unsigned long)context_ptr+0x00000af8+4*4))=0x06eb542e;
*((unsigned int *)((unsigned long)context_ptr+0x00000af8+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000270&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000067e8,"\x21\xf2\x65\xa9\x17\x32\x83\xc1\x23\xb0\xdd\xe5\xe2\x0d\x6b\x87\xa2\x4b\xdd\x7d\xd5\xcb\xb7\xcc\xfd\xd2\xed\xca",28))
printf("strip: 21f265a9173283c1, Pass\n");
else
printf("strip: 21f265a9173283c1, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000063d0))=0x020a0012;
*((unsigned int *)((unsigned long)context_ptr+0x000063d0+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000063d0+4*2))=0x02020077;
*((unsigned int *)((unsigned long)context_ptr+0x000063d0+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x00006500))=0xa764bc5b;
*((unsigned int *)((unsigned long)context_ptr+0x00006500+4*1))=0x97dc0e45;
*((unsigned int *)((unsigned long)context_ptr+0x00006500+4*2))=0x11c44eb6;
*((unsigned int *)((unsigned long)context_ptr+0x00006500+4*3))=0x09c2fffc;
*((unsigned int *)((unsigned long)context_ptr+0x00006500+4*4))=0xa0641905;
*((unsigned int *)((unsigned long)context_ptr+0x00006500+4*5))=0xbb0a7e7f;
*((unsigned int *)((unsigned long)context_ptr+0x00006500+4*6))=0x879577a7;
*((unsigned int *)((unsigned long)context_ptr+0x00006500+4*7))=0x61afbeb5;
*((unsigned int *)((unsigned long)context_ptr+0x00006500+4*8))=0x0453900c;
*((unsigned int *)((unsigned long)context_ptr+0x00006500+4*9))=0x7595206e;
*((unsigned int *)((unsigned long)context_ptr+0x00006500+4*10))=0xe96bfcce;
*((unsigned int *)((unsigned long)context_ptr+0x00006500+4*11))=0x8a5d82fb;
*((unsigned int *)((unsigned long)context_ptr+0x00006500+4*12))=0x065737f9;
*((unsigned int *)((unsigned long)context_ptr+0x00006500+4*13))=0xd7267ce5;
*((unsigned int *)((unsigned long)context_ptr+0x00006500+4*14))=0x2241fe7d;
*((unsigned int *)((unsigned long)context_ptr+0x00006500+4*15))=0x52c991f5;
*((unsigned int *)((unsigned long)context_ptr+0x00006500+4*16))=0x1b8efa40;
*((unsigned int *)((unsigned long)context_ptr+0x00006500+4*17))=0x6583b9aa;
*((unsigned int *)((unsigned long)context_ptr+0x00006500+4*18))=0xcfc8247f;
*((unsigned int *)((unsigned long)context_ptr+0x00006500+4*19))=0xd90e0ba5;
*((unsigned int *)((unsigned long)context_ptr+0x00006500+4*20))=0xc31cc0ea;
*((unsigned int *)((unsigned long)context_ptr+0x00006500+4*21))=0x638d843b;
*((unsigned int *)((unsigned long)context_ptr+0x00006500+4*22))=0x69cc0557;
*((unsigned int *)((unsigned long)context_ptr+0x00006500+4*23))=0x5ce7a353;
*((unsigned int *)((unsigned long)context_ptr+0x00006500+4*24))=0xf93d39df;
*((unsigned int *)((unsigned long)context_ptr+0x00006500+4*25))=0x379177e5;
*((unsigned int *)((unsigned long)context_ptr+0x00006500+4*26))=0xff578dc4;
*((unsigned int *)((unsigned long)context_ptr+0x00006500+4*27))=0x05bce404;
*((unsigned int *)((unsigned long)context_ptr+0x00006500+4*28))=0xceeaea20;
*((unsigned int *)((unsigned long)context_ptr+0x00006500+4*29))=0x00da62f4;
*((unsigned int *)((unsigned long)context_ptr+0x00003b10))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003b10+4*1))=0x000067e8;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000b10+4*1))=0x00006500;
*((unsigned int *)((unsigned long)context_ptr+0x00000b10+4*2))=0x000063d0;
*((unsigned int *)((unsigned long)context_ptr+0x00000b10+4*3))=0x02220077;
*((unsigned int *)((unsigned long)context_ptr+0x00000b10+4*4))=0x0672ac73;
*((unsigned int *)((unsigned long)context_ptr+0x00000b10+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000276&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000065d0,"\xd1\xc6\x56\xe7\x43\x42\x2e\xbc\xac\x4a\xa5\x53\x6f\xeb\xa4\xed\xca\x18\xa1\x7f\x9f\x89\xea\x0c\x4d\x0e\xc2\x96",28))
printf("strip: d1c656e743422ebc, Pass\n");
else
printf("strip: d1c656e743422ebc, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000064dc))=0x020a0012;
*((unsigned int *)((unsigned long)context_ptr+0x000064dc+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000064dc+4*2))=0x02020078;
*((unsigned int *)((unsigned long)context_ptr+0x000064dc+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x00006148))=0x7435495f;
*((unsigned int *)((unsigned long)context_ptr+0x00006148+4*1))=0xae180999;
*((unsigned int *)((unsigned long)context_ptr+0x00006148+4*2))=0x51b5551e;
*((unsigned int *)((unsigned long)context_ptr+0x00006148+4*3))=0x9688c451;
*((unsigned int *)((unsigned long)context_ptr+0x00006148+4*4))=0xbe5decee;
*((unsigned int *)((unsigned long)context_ptr+0x00006148+4*5))=0xa9012dc1;
*((unsigned int *)((unsigned long)context_ptr+0x00006148+4*6))=0xd4cecce7;
*((unsigned int *)((unsigned long)context_ptr+0x00006148+4*7))=0x7bd4d99c;
*((unsigned int *)((unsigned long)context_ptr+0x00006148+4*8))=0x24a3fa21;
*((unsigned int *)((unsigned long)context_ptr+0x00006148+4*9))=0x95d385f5;
*((unsigned int *)((unsigned long)context_ptr+0x00006148+4*10))=0x66fec2b4;
*((unsigned int *)((unsigned long)context_ptr+0x00006148+4*11))=0xa8e90b81;
*((unsigned int *)((unsigned long)context_ptr+0x00006148+4*12))=0x3611e097;
*((unsigned int *)((unsigned long)context_ptr+0x00006148+4*13))=0xd548edfc;
*((unsigned int *)((unsigned long)context_ptr+0x00006148+4*14))=0x9dbc6236;
*((unsigned int *)((unsigned long)context_ptr+0x00006148+4*15))=0x4f372caa;
*((unsigned int *)((unsigned long)context_ptr+0x00006148+4*16))=0xe9564470;
*((unsigned int *)((unsigned long)context_ptr+0x00006148+4*17))=0xf8c3fea3;
*((unsigned int *)((unsigned long)context_ptr+0x00006148+4*18))=0x56349ebe;
*((unsigned int *)((unsigned long)context_ptr+0x00006148+4*19))=0xd0f904de;
*((unsigned int *)((unsigned long)context_ptr+0x00006148+4*20))=0x6918d83c;
*((unsigned int *)((unsigned long)context_ptr+0x00006148+4*21))=0x6c10dacd;
*((unsigned int *)((unsigned long)context_ptr+0x00006148+4*22))=0xf25f68cd;
*((unsigned int *)((unsigned long)context_ptr+0x00006148+4*23))=0x869f3d24;
*((unsigned int *)((unsigned long)context_ptr+0x00006148+4*24))=0xc5953159;
*((unsigned int *)((unsigned long)context_ptr+0x00006148+4*25))=0xa57a2d0b;
*((unsigned int *)((unsigned long)context_ptr+0x00006148+4*26))=0x2827c64e;
*((unsigned int *)((unsigned long)context_ptr+0x00006148+4*27))=0x9dec7b59;
*((unsigned int *)((unsigned long)context_ptr+0x00006148+4*28))=0x7d98bec6;
*((unsigned int *)((unsigned long)context_ptr+0x00006148+4*29))=0xa9ad2176;
*((unsigned int *)((unsigned long)context_ptr+0x00003b28))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003b28+4*1))=0x000061c0;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000b28+4*1))=0x00006148;
*((unsigned int *)((unsigned long)context_ptr+0x00000b28+4*2))=0x000064dc;
*((unsigned int *)((unsigned long)context_ptr+0x00000b28+4*3))=0x02220078;
*((unsigned int *)((unsigned long)context_ptr+0x00000b28+4*4))=0x00c7da27;
*((unsigned int *)((unsigned long)context_ptr+0x00000b28+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000027c&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x0000621c,"\x8f\xfa\x05\x8c\x5d\xe6\x7e\x41\xfa\x72\xb0\xc6\x47\xa7\xa3\x34\x1c\x27\x8a\x58\xbf\x1c\x77\x03\xf9\x17\xae\xfa",28))
printf("strip: 8ffa058c5de67e41, Pass\n");
else
printf("strip: 8ffa058c5de67e41, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006018))=0x020a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006018+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006018+4*2))=0x02020079;
*((unsigned int *)((unsigned long)context_ptr+0x00006018+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x00006628))=0xe4066998;
*((unsigned int *)((unsigned long)context_ptr+0x00006628+4*1))=0x49d1de7d;
*((unsigned int *)((unsigned long)context_ptr+0x00006628+4*2))=0xd5acd69a;
*((unsigned int *)((unsigned long)context_ptr+0x00006628+4*3))=0xde152b74;
*((unsigned int *)((unsigned long)context_ptr+0x00006628+4*4))=0x9854a427;
*((unsigned int *)((unsigned long)context_ptr+0x00006628+4*5))=0x1a354373;
*((unsigned int *)((unsigned long)context_ptr+0x00006628+4*6))=0xcfc64b89;
*((unsigned int *)((unsigned long)context_ptr+0x00006628+4*7))=0xe4bfc260;
*((unsigned int *)((unsigned long)context_ptr+0x00006628+4*8))=0xfc2fe2b6;
*((unsigned int *)((unsigned long)context_ptr+0x00006628+4*9))=0x7dcbc749;
*((unsigned int *)((unsigned long)context_ptr+0x00006628+4*10))=0x374e0ae9;
*((unsigned int *)((unsigned long)context_ptr+0x00006628+4*11))=0x46328a09;
*((unsigned int *)((unsigned long)context_ptr+0x00006628+4*12))=0x1e1cca92;
*((unsigned int *)((unsigned long)context_ptr+0x00006628+4*13))=0x9e8407e0;
*((unsigned int *)((unsigned long)context_ptr+0x00006628+4*14))=0xbee36712;
*((unsigned int *)((unsigned long)context_ptr+0x00006628+4*15))=0x87b39cbe;
*((unsigned int *)((unsigned long)context_ptr+0x00006628+4*16))=0xbcc3f135;
*((unsigned int *)((unsigned long)context_ptr+0x00006628+4*17))=0xb19d3910;
*((unsigned int *)((unsigned long)context_ptr+0x00006628+4*18))=0xe61b9172;
*((unsigned int *)((unsigned long)context_ptr+0x00006628+4*19))=0x640f865d;
*((unsigned int *)((unsigned long)context_ptr+0x00006628+4*20))=0xc6ca2c92;
*((unsigned int *)((unsigned long)context_ptr+0x00006628+4*21))=0x633094f7;
*((unsigned int *)((unsigned long)context_ptr+0x00006628+4*22))=0xa47168c4;
*((unsigned int *)((unsigned long)context_ptr+0x00006628+4*23))=0x8997656e;
*((unsigned int *)((unsigned long)context_ptr+0x00006628+4*24))=0xee19f837;
*((unsigned int *)((unsigned long)context_ptr+0x00006628+4*25))=0x08a469e1;
*((unsigned int *)((unsigned long)context_ptr+0x00006628+4*26))=0x85bc3293;
*((unsigned int *)((unsigned long)context_ptr+0x00006628+4*27))=0xcbde6476;
*((unsigned int *)((unsigned long)context_ptr+0x00006628+4*28))=0x8d84adbf;
*((unsigned int *)((unsigned long)context_ptr+0x00006628+4*29))=0xc97f2e47;
*((unsigned int *)((unsigned long)context_ptr+0x00006628+4*30))=0x000000a6;
*((unsigned int *)((unsigned long)context_ptr+0x00003b40))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003b40+4*1))=0x000061dc;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000b40+4*1))=0x00006628;
*((unsigned int *)((unsigned long)context_ptr+0x00000b40+4*2))=0x00006018;
*((unsigned int *)((unsigned long)context_ptr+0x00000b40+4*3))=0x02220079;
*((unsigned int *)((unsigned long)context_ptr+0x00000b40+4*4))=0x0011b78b;
*((unsigned int *)((unsigned long)context_ptr+0x00000b40+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000282&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006038,"\x05\xb6\x7c\x06\x1b\xf1\xf5\x28\xe3\x67\x48\x5b\x7e\xc6\xb2\xea\xf2\x02\x4f\xc5\x9d\x04\x27\xa8\x88\x99\x25\x4d",28))
printf("strip: 05b67c061bf1f528, Pass\n");
else
printf("strip: 05b67c061bf1f528, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006008))=0x020a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006008+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006008+4*2))=0x0202007a;
*((unsigned int *)((unsigned long)context_ptr+0x00006008+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x000061f8))=0x0bfeb9be;
*((unsigned int *)((unsigned long)context_ptr+0x000061f8+4*1))=0x490d30ba;
*((unsigned int *)((unsigned long)context_ptr+0x000061f8+4*2))=0x0474e7bd;
*((unsigned int *)((unsigned long)context_ptr+0x000061f8+4*3))=0x86d9f012;
*((unsigned int *)((unsigned long)context_ptr+0x000061f8+4*4))=0x9342e832;
*((unsigned int *)((unsigned long)context_ptr+0x000061f8+4*5))=0x8f03ccb9;
*((unsigned int *)((unsigned long)context_ptr+0x000061f8+4*6))=0x0a7c9548;
*((unsigned int *)((unsigned long)context_ptr+0x000061f8+4*7))=0xecaec5ff;
*((unsigned int *)((unsigned long)context_ptr+0x000061f8+4*8))=0x0df82c97;
*((unsigned int *)((unsigned long)context_ptr+0x000061f8+4*9))=0x8c54a40e;
*((unsigned int *)((unsigned long)context_ptr+0x000061f8+4*10))=0x9eb46454;
*((unsigned int *)((unsigned long)context_ptr+0x000061f8+4*11))=0xf46b56f0;
*((unsigned int *)((unsigned long)context_ptr+0x000061f8+4*12))=0xc9ca1ce8;
*((unsigned int *)((unsigned long)context_ptr+0x000061f8+4*13))=0x35ffb541;
*((unsigned int *)((unsigned long)context_ptr+0x000061f8+4*14))=0x8334f6c4;
*((unsigned int *)((unsigned long)context_ptr+0x000061f8+4*15))=0xaf9f80fb;
*((unsigned int *)((unsigned long)context_ptr+0x000061f8+4*16))=0x1d33cc6c;
*((unsigned int *)((unsigned long)context_ptr+0x000061f8+4*17))=0x66638abb;
*((unsigned int *)((unsigned long)context_ptr+0x000061f8+4*18))=0x87f55b6a;
*((unsigned int *)((unsigned long)context_ptr+0x000061f8+4*19))=0x64254ab7;
*((unsigned int *)((unsigned long)context_ptr+0x000061f8+4*20))=0x3a9cb6ba;
*((unsigned int *)((unsigned long)context_ptr+0x000061f8+4*21))=0x4b430dba;
*((unsigned int *)((unsigned long)context_ptr+0x000061f8+4*22))=0x5197a314;
*((unsigned int *)((unsigned long)context_ptr+0x000061f8+4*23))=0x8b3decdc;
*((unsigned int *)((unsigned long)context_ptr+0x000061f8+4*24))=0xaa1937e7;
*((unsigned int *)((unsigned long)context_ptr+0x000061f8+4*25))=0xb9af1ace;
*((unsigned int *)((unsigned long)context_ptr+0x000061f8+4*26))=0x53aa4b3a;
*((unsigned int *)((unsigned long)context_ptr+0x000061f8+4*27))=0xc81a1e07;
*((unsigned int *)((unsigned long)context_ptr+0x000061f8+4*28))=0x954a328c;
*((unsigned int *)((unsigned long)context_ptr+0x000061f8+4*29))=0x9cac7f2a;
*((unsigned int *)((unsigned long)context_ptr+0x000061f8+4*30))=0x00003896;
*((unsigned int *)((unsigned long)context_ptr+0x00003b58))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003b58+4*1))=0x00006038;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000b58+4*1))=0x000061f8;
*((unsigned int *)((unsigned long)context_ptr+0x00000b58+4*2))=0x00006008;
*((unsigned int *)((unsigned long)context_ptr+0x00000b58+4*3))=0x0222007a;
*((unsigned int *)((unsigned long)context_ptr+0x00000b58+4*4))=0x0d91f1e0;
*((unsigned int *)((unsigned long)context_ptr+0x00000b58+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000288&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000062a4,"\x2d\xe9\x5c\xa3\x11\xdb\x9d\xef\x7c\xdf\x25\x15\x33\x5d\x57\x8c\xf0\xfb\x5f\xdf\x1d\x07\xe2\x38\x42\x45\xbc\x2e",28))
printf("strip: 2de95ca311db9def, Pass\n");
else
printf("strip: 2de95ca311db9def, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006028))=0x020a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006028+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006028+4*2))=0x0202007b;
*((unsigned int *)((unsigned long)context_ptr+0x00006028+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x00006a88))=0xb33e34a0;
*((unsigned int *)((unsigned long)context_ptr+0x00006a88+4*1))=0x47b7ed20;
*((unsigned int *)((unsigned long)context_ptr+0x00006a88+4*2))=0x3390b336;
*((unsigned int *)((unsigned long)context_ptr+0x00006a88+4*3))=0xc85dcf1d;
*((unsigned int *)((unsigned long)context_ptr+0x00006a88+4*4))=0xad39ec7f;
*((unsigned int *)((unsigned long)context_ptr+0x00006a88+4*5))=0x2bec3285;
*((unsigned int *)((unsigned long)context_ptr+0x00006a88+4*6))=0xc60ef9f2;
*((unsigned int *)((unsigned long)context_ptr+0x00006a88+4*7))=0x96ba378a;
*((unsigned int *)((unsigned long)context_ptr+0x00006a88+4*8))=0xc2f39a5e;
*((unsigned int *)((unsigned long)context_ptr+0x00006a88+4*9))=0xc89b926c;
*((unsigned int *)((unsigned long)context_ptr+0x00006a88+4*10))=0x76b443d6;
*((unsigned int *)((unsigned long)context_ptr+0x00006a88+4*11))=0x000de5b5;
*((unsigned int *)((unsigned long)context_ptr+0x00006a88+4*12))=0x62601678;
*((unsigned int *)((unsigned long)context_ptr+0x00006a88+4*13))=0x7119073a;
*((unsigned int *)((unsigned long)context_ptr+0x00006a88+4*14))=0xd2980157;
*((unsigned int *)((unsigned long)context_ptr+0x00006a88+4*15))=0x83b7ff74;
*((unsigned int *)((unsigned long)context_ptr+0x00006a88+4*16))=0xa25593d6;
*((unsigned int *)((unsigned long)context_ptr+0x00006a88+4*17))=0xc13d8a8a;
*((unsigned int *)((unsigned long)context_ptr+0x00006a88+4*18))=0xda565abd;
*((unsigned int *)((unsigned long)context_ptr+0x00006a88+4*19))=0x91636532;
*((unsigned int *)((unsigned long)context_ptr+0x00006a88+4*20))=0xa964e91b;
*((unsigned int *)((unsigned long)context_ptr+0x00006a88+4*21))=0xb413d8e0;
*((unsigned int *)((unsigned long)context_ptr+0x00006a88+4*22))=0xf73457d8;
*((unsigned int *)((unsigned long)context_ptr+0x00006a88+4*23))=0x5281f84c;
*((unsigned int *)((unsigned long)context_ptr+0x00006a88+4*24))=0x0256a674;
*((unsigned int *)((unsigned long)context_ptr+0x00006a88+4*25))=0x7e6665f5;
*((unsigned int *)((unsigned long)context_ptr+0x00006a88+4*26))=0x9778c863;
*((unsigned int *)((unsigned long)context_ptr+0x00006a88+4*27))=0xd7c827a0;
*((unsigned int *)((unsigned long)context_ptr+0x00006a88+4*28))=0xffb56e2a;
*((unsigned int *)((unsigned long)context_ptr+0x00006a88+4*29))=0x55c1e5a2;
*((unsigned int *)((unsigned long)context_ptr+0x00006a88+4*30))=0x00ca424a;
*((unsigned int *)((unsigned long)context_ptr+0x00003b70))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003b70+4*1))=0x00006274;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000b70+4*1))=0x00006a88;
*((unsigned int *)((unsigned long)context_ptr+0x00000b70+4*2))=0x00006028;
*((unsigned int *)((unsigned long)context_ptr+0x00000b70+4*3))=0x0222007b;
*((unsigned int *)((unsigned long)context_ptr+0x00000b70+4*4))=0x0c5b0b03;
*((unsigned int *)((unsigned long)context_ptr+0x00000b70+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000028e&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000062c0,"\x8d\xb7\x71\x3e\x5e\xf8\x4a\x3c\x70\x13\x9a\x9f\xa5\x9c\xd0\x5c\x6d\x1d\x9d\x49\x63\x89\xc1\x90\xb8\x27\x7a\x2f",28))
printf("strip: 8db7713e5ef84a3c, Pass\n");
else
printf("strip: 8db7713e5ef84a3c, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006054))=0x020a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006054+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006054+4*2))=0x0202007c;
*((unsigned int *)((unsigned long)context_ptr+0x00006054+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x0000691c))=0x6beca2db;
*((unsigned int *)((unsigned long)context_ptr+0x0000691c+4*1))=0xbbeb6a95;
*((unsigned int *)((unsigned long)context_ptr+0x0000691c+4*2))=0x82e51889;
*((unsigned int *)((unsigned long)context_ptr+0x0000691c+4*3))=0x7482b456;
*((unsigned int *)((unsigned long)context_ptr+0x0000691c+4*4))=0x82ad08b7;
*((unsigned int *)((unsigned long)context_ptr+0x0000691c+4*5))=0x03d4f0bf;
*((unsigned int *)((unsigned long)context_ptr+0x0000691c+4*6))=0xef505a73;
*((unsigned int *)((unsigned long)context_ptr+0x0000691c+4*7))=0x1d0996bf;
*((unsigned int *)((unsigned long)context_ptr+0x0000691c+4*8))=0x78e2e66e;
*((unsigned int *)((unsigned long)context_ptr+0x0000691c+4*9))=0x0abe7e29;
*((unsigned int *)((unsigned long)context_ptr+0x0000691c+4*10))=0xf2a7c670;
*((unsigned int *)((unsigned long)context_ptr+0x0000691c+4*11))=0x26bab66b;
*((unsigned int *)((unsigned long)context_ptr+0x0000691c+4*12))=0x00958d60;
*((unsigned int *)((unsigned long)context_ptr+0x0000691c+4*13))=0x53f989a7;
*((unsigned int *)((unsigned long)context_ptr+0x0000691c+4*14))=0x2979864e;
*((unsigned int *)((unsigned long)context_ptr+0x0000691c+4*15))=0x95861a7c;
*((unsigned int *)((unsigned long)context_ptr+0x0000691c+4*16))=0x30e86ac6;
*((unsigned int *)((unsigned long)context_ptr+0x0000691c+4*17))=0x044091be;
*((unsigned int *)((unsigned long)context_ptr+0x0000691c+4*18))=0xad7d132a;
*((unsigned int *)((unsigned long)context_ptr+0x0000691c+4*19))=0xafb4a67e;
*((unsigned int *)((unsigned long)context_ptr+0x0000691c+4*20))=0x20d8c607;
*((unsigned int *)((unsigned long)context_ptr+0x0000691c+4*21))=0x0a23a72d;
*((unsigned int *)((unsigned long)context_ptr+0x0000691c+4*22))=0xa644a2ed;
*((unsigned int *)((unsigned long)context_ptr+0x0000691c+4*23))=0xef1b6265;
*((unsigned int *)((unsigned long)context_ptr+0x0000691c+4*24))=0xa5ebb370;
*((unsigned int *)((unsigned long)context_ptr+0x0000691c+4*25))=0x5317a6b4;
*((unsigned int *)((unsigned long)context_ptr+0x0000691c+4*26))=0x5f4051e3;
*((unsigned int *)((unsigned long)context_ptr+0x0000691c+4*27))=0x9ad96a17;
*((unsigned int *)((unsigned long)context_ptr+0x0000691c+4*28))=0x4e9a7f86;
*((unsigned int *)((unsigned long)context_ptr+0x0000691c+4*29))=0x368a99ce;
*((unsigned int *)((unsigned long)context_ptr+0x0000691c+4*30))=0x4662ebc2;
*((unsigned int *)((unsigned long)context_ptr+0x00003b88))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003b88+4*1))=0x00006290;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000b88+4*1))=0x0000691c;
*((unsigned int *)((unsigned long)context_ptr+0x00000b88+4*2))=0x00006054;
*((unsigned int *)((unsigned long)context_ptr+0x00000b88+4*3))=0x0222007c;
*((unsigned int *)((unsigned long)context_ptr+0x00000b88+4*4))=0x0219221b;
*((unsigned int *)((unsigned long)context_ptr+0x00000b88+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000294&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000065fc,"\xf8\xca\xef\x7b\x16\x1e\x43\x1c\x96\xe1\xfd\xac\xd6\xbe\x64\xb0\x40\x5d\x14\x53\x18\x43\xd0\x3d\xf7\xc3\xbe\xce",28))
printf("strip: f8caef7b161e431c, Pass\n");
else
printf("strip: f8caef7b161e431c, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000062ac))=0x020a0012;
*((unsigned int *)((unsigned long)context_ptr+0x000062ac+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000062ac+4*2))=0x0202007d;
*((unsigned int *)((unsigned long)context_ptr+0x000062ac+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x00006578))=0x10423c4f;
*((unsigned int *)((unsigned long)context_ptr+0x00006578+4*1))=0x3013fe65;
*((unsigned int *)((unsigned long)context_ptr+0x00006578+4*2))=0xecaa9227;
*((unsigned int *)((unsigned long)context_ptr+0x00006578+4*3))=0x423ec346;
*((unsigned int *)((unsigned long)context_ptr+0x00006578+4*4))=0x9445d50c;
*((unsigned int *)((unsigned long)context_ptr+0x00006578+4*5))=0x44eb8718;
*((unsigned int *)((unsigned long)context_ptr+0x00006578+4*6))=0x55542f99;
*((unsigned int *)((unsigned long)context_ptr+0x00006578+4*7))=0x18726746;
*((unsigned int *)((unsigned long)context_ptr+0x00006578+4*8))=0xb5922d81;
*((unsigned int *)((unsigned long)context_ptr+0x00006578+4*9))=0x11eace5b;
*((unsigned int *)((unsigned long)context_ptr+0x00006578+4*10))=0x0847d670;
*((unsigned int *)((unsigned long)context_ptr+0x00006578+4*11))=0xdc1aef74;
*((unsigned int *)((unsigned long)context_ptr+0x00006578+4*12))=0xd92f8280;
*((unsigned int *)((unsigned long)context_ptr+0x00006578+4*13))=0xf592d3c5;
*((unsigned int *)((unsigned long)context_ptr+0x00006578+4*14))=0xdb642eaa;
*((unsigned int *)((unsigned long)context_ptr+0x00006578+4*15))=0x205098b4;
*((unsigned int *)((unsigned long)context_ptr+0x00006578+4*16))=0x72e844ec;
*((unsigned int *)((unsigned long)context_ptr+0x00006578+4*17))=0xa0211cb3;
*((unsigned int *)((unsigned long)context_ptr+0x00006578+4*18))=0x50a89e7f;
*((unsigned int *)((unsigned long)context_ptr+0x00006578+4*19))=0x25df0985;
*((unsigned int *)((unsigned long)context_ptr+0x00006578+4*20))=0xda03232f;
*((unsigned int *)((unsigned long)context_ptr+0x00006578+4*21))=0xa64f44c4;
*((unsigned int *)((unsigned long)context_ptr+0x00006578+4*22))=0xcfd428b3;
*((unsigned int *)((unsigned long)context_ptr+0x00006578+4*23))=0x190c08ab;
*((unsigned int *)((unsigned long)context_ptr+0x00006578+4*24))=0x6745a0b2;
*((unsigned int *)((unsigned long)context_ptr+0x00006578+4*25))=0xa7b34233;
*((unsigned int *)((unsigned long)context_ptr+0x00006578+4*26))=0xf3e32929;
*((unsigned int *)((unsigned long)context_ptr+0x00006578+4*27))=0x2c561053;
*((unsigned int *)((unsigned long)context_ptr+0x00006578+4*28))=0x14f97551;
*((unsigned int *)((unsigned long)context_ptr+0x00006578+4*29))=0xf77e390a;
*((unsigned int *)((unsigned long)context_ptr+0x00006578+4*30))=0xee4ccd3a;
*((unsigned int *)((unsigned long)context_ptr+0x00006578+4*31))=0x00000081;
*((unsigned int *)((unsigned long)context_ptr+0x00003ba0))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003ba0+4*1))=0x000062bc;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000ba0+4*1))=0x00006578;
*((unsigned int *)((unsigned long)context_ptr+0x00000ba0+4*2))=0x000062ac;
*((unsigned int *)((unsigned long)context_ptr+0x00000ba0+4*3))=0x0222007d;
*((unsigned int *)((unsigned long)context_ptr+0x00000ba0+4*4))=0x02e20b11;
*((unsigned int *)((unsigned long)context_ptr+0x00000ba0+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000029a&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006870,"\x2b\x7c\xc0\x2b\x73\x89\x48\x90\x61\x36\xfe\xc2\x31\x7b\x90\x4b\x8d\xd1\xa3\xc6\xbd\xef\x07\x04\x1b\x81\xc1\xd3",28))
printf("strip: 2b7cc02b73894890, Pass\n");
else
printf("strip: 2b7cc02b73894890, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000065f8))=0x020a0012;
*((unsigned int *)((unsigned long)context_ptr+0x000065f8+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000065f8+4*2))=0x0202007e;
*((unsigned int *)((unsigned long)context_ptr+0x000065f8+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x000063e0))=0xd2e01261;
*((unsigned int *)((unsigned long)context_ptr+0x000063e0+4*1))=0x65121a6b;
*((unsigned int *)((unsigned long)context_ptr+0x000063e0+4*2))=0x644dc04f;
*((unsigned int *)((unsigned long)context_ptr+0x000063e0+4*3))=0x38fb7cb4;
*((unsigned int *)((unsigned long)context_ptr+0x000063e0+4*4))=0x092145b9;
*((unsigned int *)((unsigned long)context_ptr+0x000063e0+4*5))=0xefe82262;
*((unsigned int *)((unsigned long)context_ptr+0x000063e0+4*6))=0x58856b96;
*((unsigned int *)((unsigned long)context_ptr+0x000063e0+4*7))=0x2dd59280;
*((unsigned int *)((unsigned long)context_ptr+0x000063e0+4*8))=0x46e668e2;
*((unsigned int *)((unsigned long)context_ptr+0x000063e0+4*9))=0x20c42aaf;
*((unsigned int *)((unsigned long)context_ptr+0x000063e0+4*10))=0x89fa3469;
*((unsigned int *)((unsigned long)context_ptr+0x000063e0+4*11))=0x44186a2c;
*((unsigned int *)((unsigned long)context_ptr+0x000063e0+4*12))=0x81dae11f;
*((unsigned int *)((unsigned long)context_ptr+0x000063e0+4*13))=0x330330b1;
*((unsigned int *)((unsigned long)context_ptr+0x000063e0+4*14))=0x2743a16a;
*((unsigned int *)((unsigned long)context_ptr+0x000063e0+4*15))=0xcda658ad;
*((unsigned int *)((unsigned long)context_ptr+0x000063e0+4*16))=0x39cb5444;
*((unsigned int *)((unsigned long)context_ptr+0x000063e0+4*17))=0x81da213f;
*((unsigned int *)((unsigned long)context_ptr+0x000063e0+4*18))=0x4239d3c3;
*((unsigned int *)((unsigned long)context_ptr+0x000063e0+4*19))=0xf4549957;
*((unsigned int *)((unsigned long)context_ptr+0x000063e0+4*20))=0x55fe0b62;
*((unsigned int *)((unsigned long)context_ptr+0x000063e0+4*21))=0x7b4b11a1;
*((unsigned int *)((unsigned long)context_ptr+0x000063e0+4*22))=0xebde59c0;
*((unsigned int *)((unsigned long)context_ptr+0x000063e0+4*23))=0x4d9394dd;
*((unsigned int *)((unsigned long)context_ptr+0x000063e0+4*24))=0xb657071d;
*((unsigned int *)((unsigned long)context_ptr+0x000063e0+4*25))=0x63ed7886;
*((unsigned int *)((unsigned long)context_ptr+0x000063e0+4*26))=0x3663418a;
*((unsigned int *)((unsigned long)context_ptr+0x000063e0+4*27))=0x416cb2b4;
*((unsigned int *)((unsigned long)context_ptr+0x000063e0+4*28))=0x8654e74a;
*((unsigned int *)((unsigned long)context_ptr+0x000063e0+4*29))=0x7655878b;
*((unsigned int *)((unsigned long)context_ptr+0x000063e0+4*30))=0x02c03256;
*((unsigned int *)((unsigned long)context_ptr+0x000063e0+4*31))=0x000065cb;
*((unsigned int *)((unsigned long)context_ptr+0x00003bb8))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003bb8+4*1))=0x000066a4;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000bb8+4*1))=0x000063e0;
*((unsigned int *)((unsigned long)context_ptr+0x00000bb8+4*2))=0x000065f8;
*((unsigned int *)((unsigned long)context_ptr+0x00000bb8+4*3))=0x0222007e;
*((unsigned int *)((unsigned long)context_ptr+0x00000bb8+4*4))=0x0fb96f04;
*((unsigned int *)((unsigned long)context_ptr+0x00000bb8+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000002a0&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x0000634c,"\xd4\x18\xcf\x40\x6c\xd6\xc9\x8f\xa2\x4e\xa6\xcb\xa4\x21\x92\x84\x40\x38\x85\x58\xba\x52\x76\x71\x1e\x86\xca\x3d",28))
printf("strip: d418cf406cd6c98f, Pass\n");
else
printf("strip: d418cf406cd6c98f, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006608))=0x020a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006608+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006608+4*2))=0x0202007f;
*((unsigned int *)((unsigned long)context_ptr+0x00006608+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x00006804))=0x02998124;
*((unsigned int *)((unsigned long)context_ptr+0x00006804+4*1))=0xd3293760;
*((unsigned int *)((unsigned long)context_ptr+0x00006804+4*2))=0x9c8e65b3;
*((unsigned int *)((unsigned long)context_ptr+0x00006804+4*3))=0x8c439665;
*((unsigned int *)((unsigned long)context_ptr+0x00006804+4*4))=0x75941bb5;
*((unsigned int *)((unsigned long)context_ptr+0x00006804+4*5))=0xa2d3360b;
*((unsigned int *)((unsigned long)context_ptr+0x00006804+4*6))=0x3853cfa5;
*((unsigned int *)((unsigned long)context_ptr+0x00006804+4*7))=0x342b6bb5;
*((unsigned int *)((unsigned long)context_ptr+0x00006804+4*8))=0x191d3042;
*((unsigned int *)((unsigned long)context_ptr+0x00006804+4*9))=0xda4e75d9;
*((unsigned int *)((unsigned long)context_ptr+0x00006804+4*10))=0x7df11a5c;
*((unsigned int *)((unsigned long)context_ptr+0x00006804+4*11))=0xcecb1250;
*((unsigned int *)((unsigned long)context_ptr+0x00006804+4*12))=0x5677f1fb;
*((unsigned int *)((unsigned long)context_ptr+0x00006804+4*13))=0x602fbb5a;
*((unsigned int *)((unsigned long)context_ptr+0x00006804+4*14))=0x2bce391f;
*((unsigned int *)((unsigned long)context_ptr+0x00006804+4*15))=0x289b7a6c;
*((unsigned int *)((unsigned long)context_ptr+0x00006804+4*16))=0x91b3faaa;
*((unsigned int *)((unsigned long)context_ptr+0x00006804+4*17))=0xdaeb1083;
*((unsigned int *)((unsigned long)context_ptr+0x00006804+4*18))=0xa2ce2d06;
*((unsigned int *)((unsigned long)context_ptr+0x00006804+4*19))=0xd4a67cf2;
*((unsigned int *)((unsigned long)context_ptr+0x00006804+4*20))=0x9d303d97;
*((unsigned int *)((unsigned long)context_ptr+0x00006804+4*21))=0x5f42afcc;
*((unsigned int *)((unsigned long)context_ptr+0x00006804+4*22))=0x3a01a087;
*((unsigned int *)((unsigned long)context_ptr+0x00006804+4*23))=0xcdf2c3a7;
*((unsigned int *)((unsigned long)context_ptr+0x00006804+4*24))=0x1e963bf4;
*((unsigned int *)((unsigned long)context_ptr+0x00006804+4*25))=0xbcb03e9b;
*((unsigned int *)((unsigned long)context_ptr+0x00006804+4*26))=0x186e0b7c;
*((unsigned int *)((unsigned long)context_ptr+0x00006804+4*27))=0x23ebd68c;
*((unsigned int *)((unsigned long)context_ptr+0x00006804+4*28))=0x9bdf3294;
*((unsigned int *)((unsigned long)context_ptr+0x00006804+4*29))=0x9043c615;
*((unsigned int *)((unsigned long)context_ptr+0x00006804+4*30))=0x29b5de58;
*((unsigned int *)((unsigned long)context_ptr+0x00006804+4*31))=0x00cc3334;
*((unsigned int *)((unsigned long)context_ptr+0x00003bd0))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003bd0+4*1))=0x000066c0;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000bd0+4*1))=0x00006804;
*((unsigned int *)((unsigned long)context_ptr+0x00000bd0+4*2))=0x00006608;
*((unsigned int *)((unsigned long)context_ptr+0x00000bd0+4*3))=0x0222007f;
*((unsigned int *)((unsigned long)context_ptr+0x00000bd0+4*4))=0x003b0a10;
*((unsigned int *)((unsigned long)context_ptr+0x00000bd0+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000002a6&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006368,"\x4d\x99\xa7\xb5\x30\x65\x8b\x95\x8f\x5e\x4c\x5d\x14\x5d\xf5\x6d\x5c\xcb\x05\x87\xbb\xa7\xd8\x61\xc7\x4f\xfd\xbc",28))
printf("strip: 4d99a7b530658b95, Pass\n");
else
printf("strip: 4d99a7b530658b95, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006618))=0x020a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006618+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006618+4*2))=0x02020080;
*((unsigned int *)((unsigned long)context_ptr+0x00006618+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x000062d8))=0xecf7be6e;
*((unsigned int *)((unsigned long)context_ptr+0x000062d8+4*1))=0xa0bd9905;
*((unsigned int *)((unsigned long)context_ptr+0x000062d8+4*2))=0xbcad0e9d;
*((unsigned int *)((unsigned long)context_ptr+0x000062d8+4*3))=0x7960c646;
*((unsigned int *)((unsigned long)context_ptr+0x000062d8+4*4))=0x941aa03b;
*((unsigned int *)((unsigned long)context_ptr+0x000062d8+4*5))=0x8a933b55;
*((unsigned int *)((unsigned long)context_ptr+0x000062d8+4*6))=0xdab77b3b;
*((unsigned int *)((unsigned long)context_ptr+0x000062d8+4*7))=0x506f0012;
*((unsigned int *)((unsigned long)context_ptr+0x000062d8+4*8))=0xf3d95ae6;
*((unsigned int *)((unsigned long)context_ptr+0x000062d8+4*9))=0x192d4ce4;
*((unsigned int *)((unsigned long)context_ptr+0x000062d8+4*10))=0x408be758;
*((unsigned int *)((unsigned long)context_ptr+0x000062d8+4*11))=0xea550bbe;
*((unsigned int *)((unsigned long)context_ptr+0x000062d8+4*12))=0x94a1c243;
*((unsigned int *)((unsigned long)context_ptr+0x000062d8+4*13))=0x575195c8;
*((unsigned int *)((unsigned long)context_ptr+0x000062d8+4*14))=0x3607c31e;
*((unsigned int *)((unsigned long)context_ptr+0x000062d8+4*15))=0x95eba041;
*((unsigned int *)((unsigned long)context_ptr+0x000062d8+4*16))=0x6ed1e808;
*((unsigned int *)((unsigned long)context_ptr+0x000062d8+4*17))=0x957ff50d;
*((unsigned int *)((unsigned long)context_ptr+0x000062d8+4*18))=0x2008dcab;
*((unsigned int *)((unsigned long)context_ptr+0x000062d8+4*19))=0x9e9eb4d2;
*((unsigned int *)((unsigned long)context_ptr+0x000062d8+4*20))=0xfe253220;
*((unsigned int *)((unsigned long)context_ptr+0x000062d8+4*21))=0x4a08f450;
*((unsigned int *)((unsigned long)context_ptr+0x000062d8+4*22))=0x65546477;
*((unsigned int *)((unsigned long)context_ptr+0x000062d8+4*23))=0xc33ed15c;
*((unsigned int *)((unsigned long)context_ptr+0x000062d8+4*24))=0x144413db;
*((unsigned int *)((unsigned long)context_ptr+0x000062d8+4*25))=0x966a079f;
*((unsigned int *)((unsigned long)context_ptr+0x000062d8+4*26))=0x3eb1dd03;
*((unsigned int *)((unsigned long)context_ptr+0x000062d8+4*27))=0xf05a1a4f;
*((unsigned int *)((unsigned long)context_ptr+0x000062d8+4*28))=0xf8af3cc5;
*((unsigned int *)((unsigned long)context_ptr+0x000062d8+4*29))=0xc0891f10;
*((unsigned int *)((unsigned long)context_ptr+0x000062d8+4*30))=0x9346f320;
*((unsigned int *)((unsigned long)context_ptr+0x000062d8+4*31))=0x9d87dd52;
*((unsigned int *)((unsigned long)context_ptr+0x00003be8))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003be8+4*1))=0x000066dc;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000be8+4*1))=0x000062d8;
*((unsigned int *)((unsigned long)context_ptr+0x00000be8+4*2))=0x00006618;
*((unsigned int *)((unsigned long)context_ptr+0x00000be8+4*3))=0x02220080;
*((unsigned int *)((unsigned long)context_ptr+0x00000be8+4*4))=0x01c75c75;
*((unsigned int *)((unsigned long)context_ptr+0x00000be8+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000002ac&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006468,"\x36\x00\x8a\x43\x37\x02\xa9\x95\x48\x66\x08\x78\xe5\x23\x9a\x86\xae\x24\x92\x79\x2c\xbe\x40\x37\x35\xbb\xee\x7f",28))
printf("strip: 36008a433702a995, Pass\n");
else
printf("strip: 36008a433702a995, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000064ec))=0x020a0012;
*((unsigned int *)((unsigned long)context_ptr+0x000064ec+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000064ec+4*2))=0x02020081;
*((unsigned int *)((unsigned long)context_ptr+0x000064ec+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x00006064))=0x446729f1;
*((unsigned int *)((unsigned long)context_ptr+0x00006064+4*1))=0x82d8bbaf;
*((unsigned int *)((unsigned long)context_ptr+0x00006064+4*2))=0x56f861cf;
*((unsigned int *)((unsigned long)context_ptr+0x00006064+4*3))=0x57900310;
*((unsigned int *)((unsigned long)context_ptr+0x00006064+4*4))=0x5c937160;
*((unsigned int *)((unsigned long)context_ptr+0x00006064+4*5))=0x0ed1407a;
*((unsigned int *)((unsigned long)context_ptr+0x00006064+4*6))=0x492d7fe1;
*((unsigned int *)((unsigned long)context_ptr+0x00006064+4*7))=0x9ef726a6;
*((unsigned int *)((unsigned long)context_ptr+0x00006064+4*8))=0x1fe1e4dd;
*((unsigned int *)((unsigned long)context_ptr+0x00006064+4*9))=0x52b7dca0;
*((unsigned int *)((unsigned long)context_ptr+0x00006064+4*10))=0xeb9a019b;
*((unsigned int *)((unsigned long)context_ptr+0x00006064+4*11))=0x820fc664;
*((unsigned int *)((unsigned long)context_ptr+0x00006064+4*12))=0x21351906;
*((unsigned int *)((unsigned long)context_ptr+0x00006064+4*13))=0x16b60c08;
*((unsigned int *)((unsigned long)context_ptr+0x00006064+4*14))=0x287938a4;
*((unsigned int *)((unsigned long)context_ptr+0x00006064+4*15))=0x276f4bb7;
*((unsigned int *)((unsigned long)context_ptr+0x00006064+4*16))=0x0d008b05;
*((unsigned int *)((unsigned long)context_ptr+0x00006064+4*17))=0x788cff42;
*((unsigned int *)((unsigned long)context_ptr+0x00006064+4*18))=0xb1749929;
*((unsigned int *)((unsigned long)context_ptr+0x00006064+4*19))=0x07772a98;
*((unsigned int *)((unsigned long)context_ptr+0x00006064+4*20))=0x9ec21ca3;
*((unsigned int *)((unsigned long)context_ptr+0x00006064+4*21))=0x30c0f24b;
*((unsigned int *)((unsigned long)context_ptr+0x00006064+4*22))=0x2c43cc47;
*((unsigned int *)((unsigned long)context_ptr+0x00006064+4*23))=0x2e383343;
*((unsigned int *)((unsigned long)context_ptr+0x00006064+4*24))=0x5574f32f;
*((unsigned int *)((unsigned long)context_ptr+0x00006064+4*25))=0x973bce8d;
*((unsigned int *)((unsigned long)context_ptr+0x00006064+4*26))=0x99836fd6;
*((unsigned int *)((unsigned long)context_ptr+0x00006064+4*27))=0x9ecd5742;
*((unsigned int *)((unsigned long)context_ptr+0x00006064+4*28))=0x9d4e3ead;
*((unsigned int *)((unsigned long)context_ptr+0x00006064+4*29))=0x1eefe430;
*((unsigned int *)((unsigned long)context_ptr+0x00006064+4*30))=0x194f6306;
*((unsigned int *)((unsigned long)context_ptr+0x00006064+4*31))=0xeb81eec7;
*((unsigned int *)((unsigned long)context_ptr+0x00006064+4*32))=0x000000f7;
*((unsigned int *)((unsigned long)context_ptr+0x00003c00))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003c00+4*1))=0x00006460;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000c00+4*1))=0x00006064;
*((unsigned int *)((unsigned long)context_ptr+0x00000c00+4*2))=0x000064ec;
*((unsigned int *)((unsigned long)context_ptr+0x00000c00+4*3))=0x02220081;
*((unsigned int *)((unsigned long)context_ptr+0x00000c00+4*4))=0x0a792341;
*((unsigned int *)((unsigned long)context_ptr+0x00000c00+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000002b2&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006484,"\x8f\x14\x14\xd6\x9a\xd2\x1a\x84\x6b\xbf\xc9\xcf\x5e\xec\x26\xd9\xb8\x58\x64\xc6\xb8\xb1\x6c\x9e\xb6\x00\x62\x99",28))
printf("strip: 8f1414d69ad21a84, Pass\n");
else
printf("strip: 8f1414d69ad21a84, Failed\n");
writel(0x000002b8&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006900,"\xab\x92\x9a\xf4\x27\x4a\xb4\xa8\x11\x79\x96\x08\xb5\x43\xb6\xab\x1a\x03\x67\x09\x03\xae\x96\x00\x93\xee\x59\xe3",28))
printf("strip: ab929af4274ab4a8, Pass\n");
else
printf("strip: ab929af4274ab4a8, Failed\n");
writel(0x000002be&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000064b0,"\x3c\xa4\xef\x3b\x89\xf3\x50\xa3\x8c\x0b\x72\xf7\x3c\xad\xc8\x30\x72\x06\xaa\x8c\x0e\xea\x53\xe0\x2b\x56\x20\xb5",28))
printf("strip: 3ca4ef3b89f350a3, Pass\n");
else
printf("strip: 3ca4ef3b89f350a3, Failed\n");
writel(0x000002c4&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000063b4,"\xe4\x96\x47\xbe\x66\xec\xe3\x2a\x99\x69\x3c\x69\xab\x43\x11\x28\x6a\x3a\xd0\x08\x27\x34\x57\x58\x08\x59\x4f\x38",28))
printf("strip: e49647be66ece32a, Pass\n");
else
printf("strip: e49647be66ece32a, Failed\n");
writel(0x000002ca&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000067e8,"\x87\xa8\xf4\x1c\x84\x8e\x57\x2e\x87\xfb\xa8\x2c\xee\x6f\x54\x38\x07\x00\xf6\xd0\xba\xc2\x9b\x1a\x55\x92\x1f\xb9",28))
printf("strip: 87a8f41c848e572e, Pass\n");
else
printf("strip: 87a8f41c848e572e, Failed\n");
writel(0x000002d0&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000061c0,"\xba\x0a\xd8\x54\xb9\x7b\x3c\x2f\x2f\x78\x9d\xdb\xc5\x9e\x4d\x89\x9e\x90\x5e\x8d\xd5\x28\xf9\xe5\x63\xb2\x71\xf6",28))
printf("strip: ba0ad854b97b3c2f, Pass\n");
else
printf("strip: ba0ad854b97b3c2f, Failed\n");
writel(0x000002d6&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000061dc,"\x28\xb2\xf3\xec\x02\x71\x7d\x4b\x36\x30\x2b\xab\xe7\x02\x76\xbf\xf7\x8b\x67\x2c\x73\xf2\x10\xfd\x6c\x46\xa2\x1e",28))
printf("strip: 28b2f3ec02717d4b, Pass\n");
else
printf("strip: 28b2f3ec02717d4b, Failed\n");
writel(0x000002dc&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006038,"\x35\x64\x37\x71\x78\xd7\x03\xa8\x0c\x6b\xbb\x25\xe0\xd6\x6e\x73\x39\x68\x66\xec\x94\xa9\xfa\x66\xcb\x28\x75\x38",28))
printf("strip: 3564377178d703a8, Pass\n");
else
printf("strip: 3564377178d703a8, Failed\n");
writel(0x000002e2&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006274,"\x47\xd3\xcf\x66\x9f\xd5\x0e\xe5\xe9\x7d\x44\xb2\x68\x1a\xd5\x2f\x57\x71\x18\xa9\x17\xca\x0a\xef\xce\x66\x37\xcd",28))
printf("strip: 47d3cf669fd50ee5, Pass\n");
else
printf("strip: 47d3cf669fd50ee5, Failed\n");
writel(0x000002e8&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006290,"\x75\x10\x44\x05\x25\x63\x50\xa9\x99\xfb\x46\x73\xd4\x74\x50\xae\x60\x1e\xbd\x48\x15\x31\xb5\x0f\xe1\x08\x3c\xa2",28))
printf("strip: 75104405256350a9, Pass\n");
else
printf("strip: 75104405256350a9, Failed\n");
writel(0x000002ee&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000062bc,"\xc4\x39\xb1\x6a\xe4\x29\x36\x96\xad\xc7\x78\x79\x67\x64\x87\x48\x7a\x43\x47\x77\x26\xa9\x7a\x0c\x04\x94\xb0\xc2",28))
printf("strip: c439b16ae4293696, Pass\n");
else
printf("strip: c439b16ae4293696, Failed\n");
writel(0x000002f4&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000066a4,"\x77\xc4\x22\x87\x8a\x15\xb7\x1f\xe0\x9f\x70\x03\xe4\x8e\x8c\x6a\x10\xe3\x8f\x4d\x3e\x03\x46\x43\x75\x68\x1f\xb5",28))
printf("strip: 77c422878a15b71f, Pass\n");
else
printf("strip: 77c422878a15b71f, Failed\n");
writel(0x000002fa&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000066c0,"\xe6\xe9\x43\x6e\x5f\x77\xc7\x66\x4b\x99\x9c\xf4\x31\x4d\x50\xa1\x9e\x98\x7a\xaa\x9d\x42\x35\x6d\xb7\x21\x64\x02",28))
printf("strip: e6e9436e5f77c766, Pass\n");
else
printf("strip: e6e9436e5f77c766, Failed\n");
writel(0x00000300&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
writel(0x00000c00&0xffffffff,ivp_cae_base_addr+0x00000830);
if(!memcmp((unsigned char *)context_ptr+0x000066dc,"\x12\xd7\xa3\xbd\xae\x2b\x54\x23\x30\x70\x5f\x33\x74\x1e\x3b\xef\xf4\x9b\x6f\xf8\xb0\x9f\xd2\xe7\x11\xb3\xfe\xbd",28))
printf("strip: 12d7a3bdae2b5423, Pass\n");
else
printf("strip: 12d7a3bdae2b5423, Failed\n");
writel(0x00000006&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006460,"\x54\x68\x8d\x7b\x8d\x20\x43\xca\x6d\xb3\x2e\x1f\x78\xc6\x11\x59\x94\x9d\x77\xb4\x1b\x01\x5f\x9d\x89\xd1\xb0\xf3",28))
printf("strip: 54688d7b8d2043ca, Pass\n");
else
printf("strip: 54688d7b8d2043ca, Failed\n");
}

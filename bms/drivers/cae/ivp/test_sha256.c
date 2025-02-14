#include <common.h>
#include <malloc.h>

extern volatile unsigned int ivp_cae_base_addr;

void test_sha256(void)
{
unsigned int *context_ptr=(unsigned int *)0x14000000;
printf("test_sha256\n");
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
*((unsigned int *)((unsigned long)context_ptr+0x00006000))=0x018a0002;
*((unsigned int *)((unsigned long)context_ptr+0x00006000+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006008))=0x018a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006008+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006008+4*2))=0x02020001;
*((unsigned int *)((unsigned long)context_ptr+0x00006008+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x00006018))=0x00000015;
*((unsigned int *)((unsigned long)context_ptr+0x00003000))=0x04c00020;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000000+4*4))=0x0399f8a8;
*((unsigned int *)((unsigned long)context_ptr+0x00000000+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x0000603c))=0x018a0012;
*((unsigned int *)((unsigned long)context_ptr+0x0000603c+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x0000603c+4*2))=0x02020002;
*((unsigned int *)((unsigned long)context_ptr+0x0000603c+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x0000604c))=0x00002e00;
*((unsigned int *)((unsigned long)context_ptr+0x00003018))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003018+4*1))=0x00006050;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000018+4*1))=0x0000604c;
*((unsigned int *)((unsigned long)context_ptr+0x00000018+4*2))=0x0000603c;
*((unsigned int *)((unsigned long)context_ptr+0x00000018+4*3))=0x02220002;
*((unsigned int *)((unsigned long)context_ptr+0x00000018+4*4))=0x010cc870;
*((unsigned int *)((unsigned long)context_ptr+0x00000018+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x00006070))=0x018a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006070+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006070+4*2))=0x02020003;
*((unsigned int *)((unsigned long)context_ptr+0x00006070+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x00006080))=0x00c66258;
*((unsigned int *)((unsigned long)context_ptr+0x00003030))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003030+4*1))=0x00006084;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000030+4*1))=0x00006080;
*((unsigned int *)((unsigned long)context_ptr+0x00000030+4*2))=0x00006070;
*((unsigned int *)((unsigned long)context_ptr+0x00000030+4*3))=0x02220003;
*((unsigned int *)((unsigned long)context_ptr+0x00000030+4*4))=0x09c30cea;
*((unsigned int *)((unsigned long)context_ptr+0x00000030+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x000060a4))=0x018a0012;
*((unsigned int *)((unsigned long)context_ptr+0x000060a4+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000060a4+4*2))=0x02020004;
*((unsigned int *)((unsigned long)context_ptr+0x000060a4+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x000060b4))=0xc7e3d117;
*((unsigned int *)((unsigned long)context_ptr+0x00003048))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003048+4*1))=0x000060b8;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000048+4*1))=0x000060b4;
*((unsigned int *)((unsigned long)context_ptr+0x00000048+4*2))=0x000060a4;
*((unsigned int *)((unsigned long)context_ptr+0x00000048+4*3))=0x02220004;
*((unsigned int *)((unsigned long)context_ptr+0x00000048+4*4))=0x04e28e67;
*((unsigned int *)((unsigned long)context_ptr+0x00000048+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x000060d8))=0x018a0012;
*((unsigned int *)((unsigned long)context_ptr+0x000060d8+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000060d8+4*2))=0x02020005;
*((unsigned int *)((unsigned long)context_ptr+0x000060d8+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x000060e8))=0xdb9a065e;
*((unsigned int *)((unsigned long)context_ptr+0x000060e8+4*1))=0x0000002f;
*((unsigned int *)((unsigned long)context_ptr+0x00003060))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003060+4*1))=0x000060f0;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000060+4*1))=0x000060e8;
*((unsigned int *)((unsigned long)context_ptr+0x00000060+4*2))=0x000060d8;
*((unsigned int *)((unsigned long)context_ptr+0x00000060+4*3))=0x02220005;
*((unsigned int *)((unsigned long)context_ptr+0x00000060+4*4))=0x0f58c43b;
*((unsigned int *)((unsigned long)context_ptr+0x00000060+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x00006110))=0x018a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006110+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006110+4*2))=0x02020006;
*((unsigned int *)((unsigned long)context_ptr+0x00006110+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x00006120))=0x0ef25e71;
*((unsigned int *)((unsigned long)context_ptr+0x00006120+4*1))=0x00006a68;
*((unsigned int *)((unsigned long)context_ptr+0x00003078))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003078+4*1))=0x00006128;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000078+4*1))=0x00006120;
*((unsigned int *)((unsigned long)context_ptr+0x00000078+4*2))=0x00006110;
*((unsigned int *)((unsigned long)context_ptr+0x00000078+4*3))=0x02220006;
*((unsigned int *)((unsigned long)context_ptr+0x00000078+4*4))=0x03438b4e;
*((unsigned int *)((unsigned long)context_ptr+0x00000078+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x00006148))=0x018a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006148+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006148+4*2))=0x02020007;
*((unsigned int *)((unsigned long)context_ptr+0x00006148+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x00006158))=0x1efb47c3;
*((unsigned int *)((unsigned long)context_ptr+0x00006158+4*1))=0x00410ae2;
*((unsigned int *)((unsigned long)context_ptr+0x00003090))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003090+4*1))=0x00006160;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000090+4*1))=0x00006158;
*((unsigned int *)((unsigned long)context_ptr+0x00000090+4*2))=0x00006148;
*((unsigned int *)((unsigned long)context_ptr+0x00000090+4*3))=0x02220007;
*((unsigned int *)((unsigned long)context_ptr+0x00000090+4*4))=0x0656fa7e;
*((unsigned int *)((unsigned long)context_ptr+0x00000090+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x00006180))=0x018a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006180+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006180+4*2))=0x02020008;
*((unsigned int *)((unsigned long)context_ptr+0x00006180+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x00006190))=0xb17a6a79;
*((unsigned int *)((unsigned long)context_ptr+0x00006190+4*1))=0x4c0fa651;
*((unsigned int *)((unsigned long)context_ptr+0x000030a8))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x000030a8+4*1))=0x00006198;
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
*((unsigned int *)((unsigned long)context_ptr+0x000000a8+4*1))=0x00006190;
*((unsigned int *)((unsigned long)context_ptr+0x000000a8+4*2))=0x00006180;
*((unsigned int *)((unsigned long)context_ptr+0x000000a8+4*3))=0x02220008;
*((unsigned int *)((unsigned long)context_ptr+0x000000a8+4*4))=0x09f032cb;
*((unsigned int *)((unsigned long)context_ptr+0x000000a8+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x000061b8))=0x018a0012;
*((unsigned int *)((unsigned long)context_ptr+0x000061b8+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000061b8+4*2))=0x02020009;
*((unsigned int *)((unsigned long)context_ptr+0x000061b8+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x000061c8))=0xf0323863;
*((unsigned int *)((unsigned long)context_ptr+0x000061c8+4*1))=0x3b630c96;
*((unsigned int *)((unsigned long)context_ptr+0x000061c8+4*2))=0x00000015;
*((unsigned int *)((unsigned long)context_ptr+0x000030c0))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x000030c0+4*1))=0x000061d4;
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
*((unsigned int *)((unsigned long)context_ptr+0x000000c0+4*1))=0x000061c8;
*((unsigned int *)((unsigned long)context_ptr+0x000000c0+4*2))=0x000061b8;
*((unsigned int *)((unsigned long)context_ptr+0x000000c0+4*3))=0x02220009;
*((unsigned int *)((unsigned long)context_ptr+0x000000c0+4*4))=0x0a358cb0;
*((unsigned int *)((unsigned long)context_ptr+0x000000c0+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x000061f4))=0x018a0012;
*((unsigned int *)((unsigned long)context_ptr+0x000061f4+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000061f4+4*2))=0x0202000a;
*((unsigned int *)((unsigned long)context_ptr+0x000061f4+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x00006204))=0x5e0b0753;
*((unsigned int *)((unsigned long)context_ptr+0x00006204+4*1))=0x33308635;
*((unsigned int *)((unsigned long)context_ptr+0x00006204+4*2))=0x0000bcac;
*((unsigned int *)((unsigned long)context_ptr+0x000030d8))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x000030d8+4*1))=0x00006210;
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
*((unsigned int *)((unsigned long)context_ptr+0x000000d8+4*1))=0x00006204;
*((unsigned int *)((unsigned long)context_ptr+0x000000d8+4*2))=0x000061f4;
*((unsigned int *)((unsigned long)context_ptr+0x000000d8+4*3))=0x0222000a;
*((unsigned int *)((unsigned long)context_ptr+0x000000d8+4*4))=0x04130086;
*((unsigned int *)((unsigned long)context_ptr+0x000000d8+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x00006230))=0x018a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006230+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006230+4*2))=0x0202000b;
*((unsigned int *)((unsigned long)context_ptr+0x00006230+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x00006240))=0xc81e3b42;
*((unsigned int *)((unsigned long)context_ptr+0x00006240+4*1))=0x483fbb19;
*((unsigned int *)((unsigned long)context_ptr+0x00006240+4*2))=0x00bda8bc;
*((unsigned int *)((unsigned long)context_ptr+0x000030f0))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x000030f0+4*1))=0x0000624c;
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
*((unsigned int *)((unsigned long)context_ptr+0x000000f0+4*1))=0x00006240;
*((unsigned int *)((unsigned long)context_ptr+0x000000f0+4*2))=0x00006230;
*((unsigned int *)((unsigned long)context_ptr+0x000000f0+4*3))=0x0222000b;
*((unsigned int *)((unsigned long)context_ptr+0x000000f0+4*4))=0x01f2de26;
*((unsigned int *)((unsigned long)context_ptr+0x000000f0+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x0000626c))=0x018a0012;
*((unsigned int *)((unsigned long)context_ptr+0x0000626c+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x0000626c+4*2))=0x0202000c;
*((unsigned int *)((unsigned long)context_ptr+0x0000626c+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x0000627c))=0x5b86d51b;
*((unsigned int *)((unsigned long)context_ptr+0x0000627c+4*1))=0xa7380374;
*((unsigned int *)((unsigned long)context_ptr+0x0000627c+4*2))=0x7bf47ea9;
*((unsigned int *)((unsigned long)context_ptr+0x00003108))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003108+4*1))=0x00006288;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000108+4*1))=0x0000627c;
*((unsigned int *)((unsigned long)context_ptr+0x00000108+4*2))=0x0000626c;
*((unsigned int *)((unsigned long)context_ptr+0x00000108+4*3))=0x0222000c;
*((unsigned int *)((unsigned long)context_ptr+0x00000108+4*4))=0x0425832c;
*((unsigned int *)((unsigned long)context_ptr+0x00000108+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x000062a8))=0x018a0012;
*((unsigned int *)((unsigned long)context_ptr+0x000062a8+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000062a8+4*2))=0x0202000d;
*((unsigned int *)((unsigned long)context_ptr+0x000062a8+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x000062b8))=0xafbc8843;
*((unsigned int *)((unsigned long)context_ptr+0x000062b8+4*1))=0x68eb0a76;
*((unsigned int *)((unsigned long)context_ptr+0x000062b8+4*2))=0xde230063;
*((unsigned int *)((unsigned long)context_ptr+0x000062b8+4*3))=0x00000083;
*((unsigned int *)((unsigned long)context_ptr+0x00003120))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003120+4*1))=0x000062c8;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000120+4*1))=0x000062b8;
*((unsigned int *)((unsigned long)context_ptr+0x00000120+4*2))=0x000062a8;
*((unsigned int *)((unsigned long)context_ptr+0x00000120+4*3))=0x0222000d;
*((unsigned int *)((unsigned long)context_ptr+0x00000120+4*4))=0x0547e390;
*((unsigned int *)((unsigned long)context_ptr+0x00000120+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x000062e8))=0x018a0012;
*((unsigned int *)((unsigned long)context_ptr+0x000062e8+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000062e8+4*2))=0x0202000e;
*((unsigned int *)((unsigned long)context_ptr+0x000062e8+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x000062f8))=0x057e67b8;
*((unsigned int *)((unsigned long)context_ptr+0x000062f8+4*1))=0x94ae08bd;
*((unsigned int *)((unsigned long)context_ptr+0x000062f8+4*2))=0x35af4ac6;
*((unsigned int *)((unsigned long)context_ptr+0x000062f8+4*3))=0x00005787;
*((unsigned int *)((unsigned long)context_ptr+0x00003138))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003138+4*1))=0x00006308;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000138+4*1))=0x000062f8;
*((unsigned int *)((unsigned long)context_ptr+0x00000138+4*2))=0x000062e8;
*((unsigned int *)((unsigned long)context_ptr+0x00000138+4*3))=0x0222000e;
*((unsigned int *)((unsigned long)context_ptr+0x00000138+4*4))=0x0357f0a6;
*((unsigned int *)((unsigned long)context_ptr+0x00000138+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x00006328))=0x018a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006328+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006328+4*2))=0x0202000f;
*((unsigned int *)((unsigned long)context_ptr+0x00006328+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x00006338))=0xc19acb81;
*((unsigned int *)((unsigned long)context_ptr+0x00006338+4*1))=0xfd6d4844;
*((unsigned int *)((unsigned long)context_ptr+0x00006338+4*2))=0x8d89f2b7;
*((unsigned int *)((unsigned long)context_ptr+0x00006338+4*3))=0x00c830fd;
*((unsigned int *)((unsigned long)context_ptr+0x00003150))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003150+4*1))=0x00006348;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000150+4*1))=0x00006338;
*((unsigned int *)((unsigned long)context_ptr+0x00000150+4*2))=0x00006328;
*((unsigned int *)((unsigned long)context_ptr+0x00000150+4*3))=0x0222000f;
*((unsigned int *)((unsigned long)context_ptr+0x00000150+4*4))=0x0c003744;
*((unsigned int *)((unsigned long)context_ptr+0x00000150+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000006&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x0000601c,"\x2f\x0f\xd1\xe8\x9b\x8d\xe1\xd5\x72\x92\x74\x2e\xc3\x80\xea\x47\x06\x6e\x30\x7a\xd6\x45\xf5\xbc\x3a\xda\xd8\xa0\x6f\xf5\x86\x08",32))
printf("strip: 2f0fd1e89b8de1d5, Pass\n");
else
printf("strip: 2f0fd1e89b8de1d5, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006008))=0x018a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006008+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006008+4*2))=0x02020010;
*((unsigned int *)((unsigned long)context_ptr+0x00006008+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x00006018))=0x62c34002;
*((unsigned int *)((unsigned long)context_ptr+0x00006018+4*1))=0xe163a0c6;
*((unsigned int *)((unsigned long)context_ptr+0x00006018+4*2))=0x20d47709;
*((unsigned int *)((unsigned long)context_ptr+0x00006018+4*3))=0x790653b5;
*((unsigned int *)((unsigned long)context_ptr+0x00003168))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003168+4*1))=0x00006368;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000168+4*4))=0x090e0173;
*((unsigned int *)((unsigned long)context_ptr+0x00000168+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000000c&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006050,"\x36\x39\x61\x8e\x90\x31\x4d\x0f\xeb\x7c\xe2\x89\xd9\x74\x68\x26\x3c\xa4\xaf\x99\x6f\xfc\x62\x13\x99\xd0\x92\xe1\xf1\x2a\xa1\xdd",32))
printf("strip: 3639618e90314d0f, Pass\n");
else
printf("strip: 3639618e90314d0f, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006028))=0x018a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006028+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006028+4*2))=0x02020011;
*((unsigned int *)((unsigned long)context_ptr+0x00006028+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x00006038))=0x95098de6;
*((unsigned int *)((unsigned long)context_ptr+0x00006038+4*1))=0xd1c108a4;
*((unsigned int *)((unsigned long)context_ptr+0x00006038+4*2))=0x3d74a512;
*((unsigned int *)((unsigned long)context_ptr+0x00006038+4*3))=0xa7552875;
*((unsigned int *)((unsigned long)context_ptr+0x00006038+4*4))=0x00000079;
*((unsigned int *)((unsigned long)context_ptr+0x00003180))=0x04c00020;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000180+4*4))=0x0d21276c;
*((unsigned int *)((unsigned long)context_ptr+0x00000180+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000012&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006084,"\xfc\x0d\x7e\xe8\xd4\xf2\xab\xa4\x89\xc8\x2c\x1e\xeb\x47\x16\x45\x54\xbb\x09\x16\x24\xde\x57\xe2\xac\x3c\xb0\xa0\x75\x9f\xc0\xf6",32))
printf("strip: fc0d7ee8d4f2aba4, Pass\n");
else
printf("strip: fc0d7ee8d4f2aba4, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x0000606c))=0x018a0012;
*((unsigned int *)((unsigned long)context_ptr+0x0000606c+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x0000606c+4*2))=0x02020012;
*((unsigned int *)((unsigned long)context_ptr+0x0000606c+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x0000607c))=0xdf8d7403;
*((unsigned int *)((unsigned long)context_ptr+0x0000607c+4*1))=0xdc0d147e;
*((unsigned int *)((unsigned long)context_ptr+0x0000607c+4*2))=0xa543dbca;
*((unsigned int *)((unsigned long)context_ptr+0x0000607c+4*3))=0xf455d318;
*((unsigned int *)((unsigned long)context_ptr+0x0000607c+4*4))=0x00000878;
*((unsigned int *)((unsigned long)context_ptr+0x00003198))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003198+4*1))=0x00006388;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000198+4*1))=0x0000607c;
*((unsigned int *)((unsigned long)context_ptr+0x00000198+4*2))=0x0000606c;
*((unsigned int *)((unsigned long)context_ptr+0x00000198+4*3))=0x02220012;
*((unsigned int *)((unsigned long)context_ptr+0x00000198+4*4))=0x0497e28b;
*((unsigned int *)((unsigned long)context_ptr+0x00000198+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000060b8,"\x2f\x80\x83\x1f\xcd\x76\xfd\x5a\xae\x06\x7a\xad\xa6\x3a\x32\x99\xa9\xcb\xa5\x4a\x98\x3c\xd6\x5c\x9a\x16\x51\xad\x4c\x1f\x5c\x50",32))
printf("strip: 2f80831fcd76fd5a, Pass\n");
else
printf("strip: 2f80831fcd76fd5a, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006090))=0x018a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006090+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006090+4*2))=0x02020013;
*((unsigned int *)((unsigned long)context_ptr+0x00006090+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x000060a0))=0x8882233f;
*((unsigned int *)((unsigned long)context_ptr+0x000060a0+4*1))=0xf7a86812;
*((unsigned int *)((unsigned long)context_ptr+0x000060a0+4*2))=0x39786f6e;
*((unsigned int *)((unsigned long)context_ptr+0x000060a0+4*3))=0x9465a565;
*((unsigned int *)((unsigned long)context_ptr+0x000060a0+4*4))=0x00e2ffd5;
*((unsigned int *)((unsigned long)context_ptr+0x000031b0))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x000031b0+4*1))=0x000060b4;
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
*((unsigned int *)((unsigned long)context_ptr+0x000001b0+4*1))=0x000060a0;
*((unsigned int *)((unsigned long)context_ptr+0x000001b0+4*2))=0x00006090;
*((unsigned int *)((unsigned long)context_ptr+0x000001b0+4*3))=0x02220013;
*((unsigned int *)((unsigned long)context_ptr+0x000001b0+4*4))=0x09c921e6;
*((unsigned int *)((unsigned long)context_ptr+0x000001b0+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000001e&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000060f0,"\x70\x7b\xbd\x82\x17\x07\x12\x32\x99\xb8\xca\x00\x83\xde\x3b\x3f\xce\xdc\x38\x92\x55\x4a\x33\x47\xf8\xa7\x6c\x46\x38\xd8\x51\x8f",32))
printf("strip: 707bbd8217071232, Pass\n");
else
printf("strip: 707bbd8217071232, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000060d4))=0x018a0012;
*((unsigned int *)((unsigned long)context_ptr+0x000060d4+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000060d4+4*2))=0x02020014;
*((unsigned int *)((unsigned long)context_ptr+0x000060d4+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x000060e4))=0xc7aeb513;
*((unsigned int *)((unsigned long)context_ptr+0x000060e4+4*1))=0x352b8d8b;
*((unsigned int *)((unsigned long)context_ptr+0x000060e4+4*2))=0x5bd1863a;
*((unsigned int *)((unsigned long)context_ptr+0x000060e4+4*3))=0x55b7bce1;
*((unsigned int *)((unsigned long)context_ptr+0x000060e4+4*4))=0x68daf61e;
*((unsigned int *)((unsigned long)context_ptr+0x000031c8))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x000031c8+4*1))=0x000063a8;
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
*((unsigned int *)((unsigned long)context_ptr+0x000001c8+4*1))=0x000060e4;
*((unsigned int *)((unsigned long)context_ptr+0x000001c8+4*2))=0x000060d4;
*((unsigned int *)((unsigned long)context_ptr+0x000001c8+4*3))=0x02220014;
*((unsigned int *)((unsigned long)context_ptr+0x000001c8+4*4))=0x057ac59e;
*((unsigned int *)((unsigned long)context_ptr+0x000001c8+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000024&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006128,"\x15\xfd\x68\xc7\x17\xa9\xe0\x2d\xd5\xc4\x1e\xf4\x8b\x31\x63\xde\x7f\xfe\x1d\xe0\xa4\x0b\xf9\x21\xb2\xe6\x5c\xa7\xa4\xeb\x2d\x66",32))
printf("strip: 15fd68c717a9e02d, Pass\n");
else
printf("strip: 15fd68c717a9e02d, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000060f8))=0x018a0012;
*((unsigned int *)((unsigned long)context_ptr+0x000060f8+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000060f8+4*2))=0x02020015;
*((unsigned int *)((unsigned long)context_ptr+0x000060f8+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x00006108))=0xe0d9d32b;
*((unsigned int *)((unsigned long)context_ptr+0x00006108+4*1))=0xb5359b84;
*((unsigned int *)((unsigned long)context_ptr+0x00006108+4*2))=0x63220567;
*((unsigned int *)((unsigned long)context_ptr+0x00006108+4*3))=0xedea90e2;
*((unsigned int *)((unsigned long)context_ptr+0x00006108+4*4))=0x81559616;
*((unsigned int *)((unsigned long)context_ptr+0x00006108+4*5))=0x00000074;
*((unsigned int *)((unsigned long)context_ptr+0x000031e0))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x000031e0+4*1))=0x00006120;
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
*((unsigned int *)((unsigned long)context_ptr+0x000001e0+4*1))=0x00006108;
*((unsigned int *)((unsigned long)context_ptr+0x000001e0+4*2))=0x000060f8;
*((unsigned int *)((unsigned long)context_ptr+0x000001e0+4*3))=0x02220015;
*((unsigned int *)((unsigned long)context_ptr+0x000001e0+4*4))=0x0d549faa;
*((unsigned int *)((unsigned long)context_ptr+0x000001e0+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000002a&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006160,"\xfc\x92\xda\xbb\xbd\xa0\xab\xc3\x3d\x2d\x33\x4c\xae\xb0\x82\xaf\xbb\xb4\x78\x2e\x09\x59\xaa\x1d\x70\xa9\x6e\x51\xc7\xe4\x34\xb1",32))
printf("strip: fc92dabbbda0abc3, Pass\n");
else
printf("strip: fc92dabbbda0abc3, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006140))=0x018a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006140+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006140+4*2))=0x02020016;
*((unsigned int *)((unsigned long)context_ptr+0x00006140+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x00006150))=0xbeef3bc2;
*((unsigned int *)((unsigned long)context_ptr+0x00006150+4*1))=0x625be17b;
*((unsigned int *)((unsigned long)context_ptr+0x00006150+4*2))=0x8066c721;
*((unsigned int *)((unsigned long)context_ptr+0x00006150+4*3))=0xea5fa778;
*((unsigned int *)((unsigned long)context_ptr+0x00006150+4*4))=0xc4665b6e;
*((unsigned int *)((unsigned long)context_ptr+0x00006150+4*5))=0x0000ddfe;
*((unsigned int *)((unsigned long)context_ptr+0x000031f8))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x000031f8+4*1))=0x000063c8;
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
*((unsigned int *)((unsigned long)context_ptr+0x000001f8+4*1))=0x00006150;
*((unsigned int *)((unsigned long)context_ptr+0x000001f8+4*2))=0x00006140;
*((unsigned int *)((unsigned long)context_ptr+0x000001f8+4*3))=0x02220016;
*((unsigned int *)((unsigned long)context_ptr+0x000001f8+4*4))=0x0722c351;
*((unsigned int *)((unsigned long)context_ptr+0x000001f8+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000030&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006198,"\x6b\x81\x3d\xcd\x44\x0a\x47\xb0\xb7\x08\xe1\xcb\xed\xa5\xde\xbd\xef\x16\x1d\x79\x09\x91\x19\xf3\x90\x10\x8f\x68\xd0\xfc\x00\x0f",32))
printf("strip: 6b813dcd440a47b0, Pass\n");
else
printf("strip: 6b813dcd440a47b0, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006168))=0x018a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006168+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006168+4*2))=0x02020017;
*((unsigned int *)((unsigned long)context_ptr+0x00006168+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x00006178))=0xc3616fce;
*((unsigned int *)((unsigned long)context_ptr+0x00006178+4*1))=0xb495449d;
*((unsigned int *)((unsigned long)context_ptr+0x00006178+4*2))=0x98a4add3;
*((unsigned int *)((unsigned long)context_ptr+0x00006178+4*3))=0x45b6f117;
*((unsigned int *)((unsigned long)context_ptr+0x00006178+4*4))=0x61a89eb1;
*((unsigned int *)((unsigned long)context_ptr+0x00006178+4*5))=0x0033a892;
*((unsigned int *)((unsigned long)context_ptr+0x00003210))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003210+4*1))=0x00006190;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000210+4*1))=0x00006178;
*((unsigned int *)((unsigned long)context_ptr+0x00000210+4*2))=0x00006168;
*((unsigned int *)((unsigned long)context_ptr+0x00000210+4*3))=0x02220017;
*((unsigned int *)((unsigned long)context_ptr+0x00000210+4*4))=0x01b040bf;
*((unsigned int *)((unsigned long)context_ptr+0x00000210+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000036&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000061d4,"\x58\xf6\x01\x9e\x25\x1e\x0c\xeb\x89\x71\x19\x50\xe7\xf3\x13\x48\x05\x1d\xe9\x23\x69\x90\x3b\x7d\xfb\x7c\x2c\xc4\xf8\xea\x46\x76",32))
printf("strip: 58f6019e251e0ceb, Pass\n");
else
printf("strip: 58f6019e251e0ceb, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000061b0))=0x018a0012;
*((unsigned int *)((unsigned long)context_ptr+0x000061b0+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000061b0+4*2))=0x02020018;
*((unsigned int *)((unsigned long)context_ptr+0x000061b0+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x000061c0))=0xec2eb985;
*((unsigned int *)((unsigned long)context_ptr+0x000061c0+4*1))=0xa26f98b6;
*((unsigned int *)((unsigned long)context_ptr+0x000061c0+4*2))=0x3692e69e;
*((unsigned int *)((unsigned long)context_ptr+0x000061c0+4*3))=0xd7e73e70;
*((unsigned int *)((unsigned long)context_ptr+0x000061c0+4*4))=0x220b328e;
*((unsigned int *)((unsigned long)context_ptr+0x000061c0+4*5))=0xaf39ac71;
*((unsigned int *)((unsigned long)context_ptr+0x00003228))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003228+4*1))=0x000063e8;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000228+4*1))=0x000061c0;
*((unsigned int *)((unsigned long)context_ptr+0x00000228+4*2))=0x000061b0;
*((unsigned int *)((unsigned long)context_ptr+0x00000228+4*3))=0x02220018;
*((unsigned int *)((unsigned long)context_ptr+0x00000228+4*4))=0x06cef5e5;
*((unsigned int *)((unsigned long)context_ptr+0x00000228+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000003c&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006210,"\x59\x47\x24\xcf\x19\x3f\x3b\x65\x7b\x86\x83\x66\x8c\xab\xab\xe3\x99\x56\x32\xf7\x13\x56\xa5\xe6\x87\xd8\xcb\x3c\xfc\x0e\x2c\x79",32))
printf("strip: 594724cf193f3b65, Pass\n");
else
printf("strip: 594724cf193f3b65, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000061d8))=0x018a0012;
*((unsigned int *)((unsigned long)context_ptr+0x000061d8+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000061d8+4*2))=0x02020019;
*((unsigned int *)((unsigned long)context_ptr+0x000061d8+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x000061e8))=0x38d64797;
*((unsigned int *)((unsigned long)context_ptr+0x000061e8+4*1))=0xd2568162;
*((unsigned int *)((unsigned long)context_ptr+0x000061e8+4*2))=0xa0271643;
*((unsigned int *)((unsigned long)context_ptr+0x000061e8+4*3))=0x7afe1090;
*((unsigned int *)((unsigned long)context_ptr+0x000061e8+4*4))=0x6f06ba51;
*((unsigned int *)((unsigned long)context_ptr+0x000061e8+4*5))=0xe2c2f6aa;
*((unsigned int *)((unsigned long)context_ptr+0x000061e8+4*6))=0x0000001e;
*((unsigned int *)((unsigned long)context_ptr+0x00003240))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003240+4*1))=0x00006204;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000240+4*1))=0x000061e8;
*((unsigned int *)((unsigned long)context_ptr+0x00000240+4*2))=0x000061d8;
*((unsigned int *)((unsigned long)context_ptr+0x00000240+4*3))=0x02220019;
*((unsigned int *)((unsigned long)context_ptr+0x00000240+4*4))=0x045a1696;
*((unsigned int *)((unsigned long)context_ptr+0x00000240+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000042&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x0000624c,"\xab\x99\x7d\xea\xa6\x2e\x25\xcf\x08\x85\x66\x1c\x74\xb5\xb5\xf7\x4f\xd4\xb2\x14\x1d\x96\x4e\xbd\xa6\xef\x86\x2b\x2c\x20\xf2\xb2",32))
printf("strip: ab997deaa62e25cf, Pass\n");
else
printf("strip: ab997deaa62e25cf, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006224))=0x018a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006224+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006224+4*2))=0x0202001a;
*((unsigned int *)((unsigned long)context_ptr+0x00006224+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x00006234))=0x1d4a9c08;
*((unsigned int *)((unsigned long)context_ptr+0x00006234+4*1))=0x5883fab6;
*((unsigned int *)((unsigned long)context_ptr+0x00006234+4*2))=0x68886a72;
*((unsigned int *)((unsigned long)context_ptr+0x00006234+4*3))=0x2cfffa14;
*((unsigned int *)((unsigned long)context_ptr+0x00006234+4*4))=0x08b26f3d;
*((unsigned int *)((unsigned long)context_ptr+0x00006234+4*5))=0xde44a3d5;
*((unsigned int *)((unsigned long)context_ptr+0x00006234+4*6))=0x000051a9;
*((unsigned int *)((unsigned long)context_ptr+0x00003258))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003258+4*1))=0x00006408;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000258+4*1))=0x00006234;
*((unsigned int *)((unsigned long)context_ptr+0x00000258+4*2))=0x00006224;
*((unsigned int *)((unsigned long)context_ptr+0x00000258+4*3))=0x0222001a;
*((unsigned int *)((unsigned long)context_ptr+0x00000258+4*4))=0x00c661a5;
*((unsigned int *)((unsigned long)context_ptr+0x00000258+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000048&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006288,"\x06\x67\x4d\xff\x83\x2f\xce\xc9\x1c\x6c\x34\x49\x9c\x68\xff\xdf\x2f\x9d\x0a\xbe\xee\x93\x73\xbc\x6c\x6b\x62\xcf\x0a\x34\xd6\xad",32))
printf("strip: 06674dff832fcec9, Pass\n");
else
printf("strip: 06674dff832fcec9, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006250))=0x018a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006250+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006250+4*2))=0x0202001b;
*((unsigned int *)((unsigned long)context_ptr+0x00006250+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x00006260))=0xde4cfc3f;
*((unsigned int *)((unsigned long)context_ptr+0x00006260+4*1))=0xcab8bdcb;
*((unsigned int *)((unsigned long)context_ptr+0x00006260+4*2))=0x812a0fd8;
*((unsigned int *)((unsigned long)context_ptr+0x00006260+4*3))=0x207e8836;
*((unsigned int *)((unsigned long)context_ptr+0x00006260+4*4))=0x14d30216;
*((unsigned int *)((unsigned long)context_ptr+0x00006260+4*5))=0x73befbf6;
*((unsigned int *)((unsigned long)context_ptr+0x00006260+4*6))=0x00586946;
*((unsigned int *)((unsigned long)context_ptr+0x00003270))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003270+4*1))=0x0000627c;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000270+4*1))=0x00006260;
*((unsigned int *)((unsigned long)context_ptr+0x00000270+4*2))=0x00006250;
*((unsigned int *)((unsigned long)context_ptr+0x00000270+4*3))=0x0222001b;
*((unsigned int *)((unsigned long)context_ptr+0x00000270+4*4))=0x0e47c98e;
*((unsigned int *)((unsigned long)context_ptr+0x00000270+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000004e&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000062c8,"\x27\xf1\x30\x4c\x8a\xed\x0c\x0e\xe1\x08\xc3\x03\x5d\x41\x09\x40\xda\x4b\xce\xbd\x20\x1c\x08\x32\x4a\xac\x13\x99\xf3\x70\x3c\xe8",32))
printf("strip: 27f1304c8aed0c0e, Pass\n");
else
printf("strip: 27f1304c8aed0c0e, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x0000629c))=0x018a0012;
*((unsigned int *)((unsigned long)context_ptr+0x0000629c+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x0000629c+4*2))=0x0202001c;
*((unsigned int *)((unsigned long)context_ptr+0x0000629c+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x000062ac))=0xba0da674;
*((unsigned int *)((unsigned long)context_ptr+0x000062ac+4*1))=0x331175f7;
*((unsigned int *)((unsigned long)context_ptr+0x000062ac+4*2))=0x00cb411a;
*((unsigned int *)((unsigned long)context_ptr+0x000062ac+4*3))=0x2c2ff0df;
*((unsigned int *)((unsigned long)context_ptr+0x000062ac+4*4))=0x02cf5cf7;
*((unsigned int *)((unsigned long)context_ptr+0x000062ac+4*5))=0xed9b04fd;
*((unsigned int *)((unsigned long)context_ptr+0x000062ac+4*6))=0x64d24fd4;
*((unsigned int *)((unsigned long)context_ptr+0x00003288))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003288+4*1))=0x000062c8;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000288+4*1))=0x000062ac;
*((unsigned int *)((unsigned long)context_ptr+0x00000288+4*2))=0x0000629c;
*((unsigned int *)((unsigned long)context_ptr+0x00000288+4*3))=0x0222001c;
*((unsigned int *)((unsigned long)context_ptr+0x00000288+4*4))=0x05acecd9;
*((unsigned int *)((unsigned long)context_ptr+0x00000288+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000054&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006308,"\x3f\x51\x89\xac\xe4\x9f\xda\x6f\x4e\xca\xc6\x38\x6b\xb4\x75\x5f\xc1\x3e\xcd\xed\xc1\x10\x20\xc5\x53\xad\x83\x94\x75\x12\x13\x4f",32))
printf("strip: 3f5189ace49fda6f, Pass\n");
else
printf("strip: 3f5189ace49fda6f, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000062e8))=0x018a0012;
*((unsigned int *)((unsigned long)context_ptr+0x000062e8+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000062e8+4*2))=0x0202001d;
*((unsigned int *)((unsigned long)context_ptr+0x000062e8+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x000062f8))=0xaf7bbfd6;
*((unsigned int *)((unsigned long)context_ptr+0x000062f8+4*1))=0xc843c319;
*((unsigned int *)((unsigned long)context_ptr+0x000062f8+4*2))=0x138982a2;
*((unsigned int *)((unsigned long)context_ptr+0x000062f8+4*3))=0x23c6030a;
*((unsigned int *)((unsigned long)context_ptr+0x000062f8+4*4))=0xe2fa621f;
*((unsigned int *)((unsigned long)context_ptr+0x000062f8+4*5))=0x6415d150;
*((unsigned int *)((unsigned long)context_ptr+0x000062f8+4*6))=0x690cfc94;
*((unsigned int *)((unsigned long)context_ptr+0x000062f8+4*7))=0x000000eb;
*((unsigned int *)((unsigned long)context_ptr+0x000032a0))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x000032a0+4*1))=0x00006428;
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
*((unsigned int *)((unsigned long)context_ptr+0x000002a0+4*1))=0x000062f8;
*((unsigned int *)((unsigned long)context_ptr+0x000002a0+4*2))=0x000062e8;
*((unsigned int *)((unsigned long)context_ptr+0x000002a0+4*3))=0x0222001d;
*((unsigned int *)((unsigned long)context_ptr+0x000002a0+4*4))=0x0663eab1;
*((unsigned int *)((unsigned long)context_ptr+0x000002a0+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000005a&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006348,"\x2e\xb2\x26\x30\x78\x16\x30\x3d\x53\xb9\x49\xa3\x20\x09\x77\x16\x0a\xfa\xad\x80\x68\xd5\x93\x75\x96\xb5\xbf\x3b\xed\xa5\x5c\x9b",32))
printf("strip: 2eb226307816303d, Pass\n");
else
printf("strip: 2eb226307816303d, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006318))=0x018a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006318+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006318+4*2))=0x0202001e;
*((unsigned int *)((unsigned long)context_ptr+0x00006318+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x00006328))=0x9086aa90;
*((unsigned int *)((unsigned long)context_ptr+0x00006328+4*1))=0x66baaa5a;
*((unsigned int *)((unsigned long)context_ptr+0x00006328+4*2))=0x77e7bed0;
*((unsigned int *)((unsigned long)context_ptr+0x00006328+4*3))=0x6209c658;
*((unsigned int *)((unsigned long)context_ptr+0x00006328+4*4))=0x3f8357fa;
*((unsigned int *)((unsigned long)context_ptr+0x00006328+4*5))=0x9e6f1c13;
*((unsigned int *)((unsigned long)context_ptr+0x00006328+4*6))=0x0a1c848b;
*((unsigned int *)((unsigned long)context_ptr+0x00006328+4*7))=0x0000f15b;
*((unsigned int *)((unsigned long)context_ptr+0x000032b8))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x000032b8+4*1))=0x00006348;
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
*((unsigned int *)((unsigned long)context_ptr+0x000002b8+4*1))=0x00006328;
*((unsigned int *)((unsigned long)context_ptr+0x000002b8+4*2))=0x00006318;
*((unsigned int *)((unsigned long)context_ptr+0x000002b8+4*3))=0x0222001e;
*((unsigned int *)((unsigned long)context_ptr+0x000002b8+4*4))=0x07baf205;
*((unsigned int *)((unsigned long)context_ptr+0x000002b8+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000060&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006368,"\x71\xce\xdb\x2b\xad\x02\x0d\x7a\x58\xaa\x92\xb6\xc6\x71\x7a\x02\x6c\xff\x98\x85\xa9\xee\xea\x32\xa8\x83\x4b\xb4\xd9\xca\xff\xa0",32))
printf("strip: 71cedb2bad020d7a, Pass\n");
else
printf("strip: 71cedb2bad020d7a, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006018))=0x018a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006018+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006018+4*2))=0x0202001f;
*((unsigned int *)((unsigned long)context_ptr+0x00006018+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x00006368))=0x357f16b5;
*((unsigned int *)((unsigned long)context_ptr+0x00006368+4*1))=0x685a8363;
*((unsigned int *)((unsigned long)context_ptr+0x00006368+4*2))=0x9af40bbb;
*((unsigned int *)((unsigned long)context_ptr+0x00006368+4*3))=0x80148e29;
*((unsigned int *)((unsigned long)context_ptr+0x00006368+4*4))=0xac506bb0;
*((unsigned int *)((unsigned long)context_ptr+0x00006368+4*5))=0xdd62dfef;
*((unsigned int *)((unsigned long)context_ptr+0x00006368+4*6))=0xc3fb0f1d;
*((unsigned int *)((unsigned long)context_ptr+0x00006368+4*7))=0x004f8f9d;
*((unsigned int *)((unsigned long)context_ptr+0x000032d0))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x000032d0+4*1))=0x00006448;
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
*((unsigned int *)((unsigned long)context_ptr+0x000002d0+4*1))=0x00006368;
*((unsigned int *)((unsigned long)context_ptr+0x000002d0+4*2))=0x00006018;
*((unsigned int *)((unsigned long)context_ptr+0x000002d0+4*3))=0x0222001f;
*((unsigned int *)((unsigned long)context_ptr+0x000002d0+4*4))=0x07b51aca;
*((unsigned int *)((unsigned long)context_ptr+0x000002d0+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000066&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x0000604c,"\x50\x8c\x6a\xc7\x74\xa5\x69\x54\x0d\x35\xdc\x59\x95\xfb\x5f\xf8\xbd\xbf\xdf\x87\xab\x89\x04\x74\xe1\x94\xd5\x17\xbc\x4b\x25\xc2",32))
printf("strip: 508c6ac774a56954, Pass\n");
else
printf("strip: 508c6ac774a56954, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006008))=0x018a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006008+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006008+4*2))=0x02020020;
*((unsigned int *)((unsigned long)context_ptr+0x00006008+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x00006038))=0x7c200093;
*((unsigned int *)((unsigned long)context_ptr+0x00006038+4*1))=0x2c38510a;
*((unsigned int *)((unsigned long)context_ptr+0x00006038+4*2))=0xa63be151;
*((unsigned int *)((unsigned long)context_ptr+0x00006038+4*3))=0x5930acbb;
*((unsigned int *)((unsigned long)context_ptr+0x00006038+4*4))=0x37f88945;
*((unsigned int *)((unsigned long)context_ptr+0x00006038+4*5))=0xf460108d;
*((unsigned int *)((unsigned long)context_ptr+0x00006038+4*6))=0xb7da18e8;
*((unsigned int *)((unsigned long)context_ptr+0x00006038+4*7))=0xe56c75ea;
*((unsigned int *)((unsigned long)context_ptr+0x000032e8))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x000032e8+4*1))=0x00006468;
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
*((unsigned int *)((unsigned long)context_ptr+0x000002e8+4*4))=0x02d79f3f;
*((unsigned int *)((unsigned long)context_ptr+0x000002e8+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000006c&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006388,"\x1c\xb9\x2c\x21\x05\xe5\xce\x9e\x57\x3d\x70\xc0\xa9\x56\x5a\x6f\x02\x51\x2c\xcc\x7e\x6f\x8e\x65\xee\x22\x8e\x61\x5f\x29\xa9\xe3",32))
printf("strip: 1cb92c2105e5ce9e, Pass\n");
else
printf("strip: 1cb92c2105e5ce9e, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006028))=0x018a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006028+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006028+4*2))=0x02020021;
*((unsigned int *)((unsigned long)context_ptr+0x00006028+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x00006058))=0xb8544ad5;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*1))=0x16e0b6aa;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*2))=0xa79c7f1f;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*3))=0x3deb223a;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*4))=0xa2844804;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*5))=0x518225bd;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*6))=0x31cf5cb9;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*7))=0xb96c85fe;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*8))=0x00000060;
*((unsigned int *)((unsigned long)context_ptr+0x00003300))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003300+4*1))=0x00006388;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000300+4*4))=0x049ace04;
*((unsigned int *)((unsigned long)context_ptr+0x00000300+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000072&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000060b4,"\x99\x4a\xb3\xed\xde\x4b\xd9\x24\x60\x15\x49\xe5\x39\x79\x42\x08\x03\xd7\xe6\xcc\x77\x5c\x1c\x13\x01\x41\x6e\xd2\xab\xa8\x64\x62",32))
printf("strip: 994ab3edde4bd924, Pass\n");
else
printf("strip: 994ab3edde4bd924, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x0000607c))=0x018a0012;
*((unsigned int *)((unsigned long)context_ptr+0x0000607c+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x0000607c+4*2))=0x02020022;
*((unsigned int *)((unsigned long)context_ptr+0x0000607c+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x0000608c))=0x0563a355;
*((unsigned int *)((unsigned long)context_ptr+0x0000608c+4*1))=0x97c63d4b;
*((unsigned int *)((unsigned long)context_ptr+0x0000608c+4*2))=0x5136df24;
*((unsigned int *)((unsigned long)context_ptr+0x0000608c+4*3))=0x846bc3df;
*((unsigned int *)((unsigned long)context_ptr+0x0000608c+4*4))=0xa7b7b5fa;
*((unsigned int *)((unsigned long)context_ptr+0x0000608c+4*5))=0x714cecfc;
*((unsigned int *)((unsigned long)context_ptr+0x0000608c+4*6))=0xe7a53ca2;
*((unsigned int *)((unsigned long)context_ptr+0x0000608c+4*7))=0x62735e4e;
*((unsigned int *)((unsigned long)context_ptr+0x0000608c+4*8))=0x00000da4;
*((unsigned int *)((unsigned long)context_ptr+0x00003318))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003318+4*1))=0x000060b0;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000318+4*1))=0x0000608c;
*((unsigned int *)((unsigned long)context_ptr+0x00000318+4*2))=0x0000607c;
*((unsigned int *)((unsigned long)context_ptr+0x00000318+4*3))=0x02220022;
*((unsigned int *)((unsigned long)context_ptr+0x00000318+4*4))=0x09f3bca6;
*((unsigned int *)((unsigned long)context_ptr+0x00000318+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000078&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000063a8,"\xcc\xf2\xaf\x8e\xb5\x3c\x73\x09\x03\x4e\xb5\x35\xf0\xde\x10\x8a\xf4\xc8\x76\x6f\xcc\xb4\x2e\x4f\x40\x1d\xf7\xaf\xd1\x14\x05\x1e",32))
printf("strip: ccf2af8eb53c7309, Pass\n");
else
printf("strip: ccf2af8eb53c7309, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000063a8))=0x018a0012;
*((unsigned int *)((unsigned long)context_ptr+0x000063a8+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000063a8+4*2))=0x02020023;
*((unsigned int *)((unsigned long)context_ptr+0x000063a8+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x000060d0))=0x8b76ab5f;
*((unsigned int *)((unsigned long)context_ptr+0x000060d0+4*1))=0x1b1a66f0;
*((unsigned int *)((unsigned long)context_ptr+0x000060d0+4*2))=0xc71d4fb9;
*((unsigned int *)((unsigned long)context_ptr+0x000060d0+4*3))=0xbd9d1ae3;
*((unsigned int *)((unsigned long)context_ptr+0x000060d0+4*4))=0x71afd63e;
*((unsigned int *)((unsigned long)context_ptr+0x000060d0+4*5))=0x2ad4422a;
*((unsigned int *)((unsigned long)context_ptr+0x000060d0+4*6))=0x048f92b4;
*((unsigned int *)((unsigned long)context_ptr+0x000060d0+4*7))=0x61a14f1f;
*((unsigned int *)((unsigned long)context_ptr+0x000060d0+4*8))=0x00766241;
*((unsigned int *)((unsigned long)context_ptr+0x00003330))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003330+4*1))=0x00006488;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000330+4*1))=0x000060d0;
*((unsigned int *)((unsigned long)context_ptr+0x00000330+4*2))=0x000063a8;
*((unsigned int *)((unsigned long)context_ptr+0x00000330+4*3))=0x02220023;
*((unsigned int *)((unsigned long)context_ptr+0x00000330+4*4))=0x05e366dc;
*((unsigned int *)((unsigned long)context_ptr+0x00000330+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000007e&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006120,"\xa1\x40\xcd\x63\xb6\x13\x77\xfb\x54\xca\xef\x8a\x03\x72\xf0\x7d\x30\x49\x46\xbb\xd3\x1c\xff\x8a\x85\xa2\x2e\xb9\x5d\xd9\x9d\xe0",32))
printf("strip: a140cd63b61377fb, Pass\n");
else
printf("strip: a140cd63b61377fb, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000063b8))=0x018a0012;
*((unsigned int *)((unsigned long)context_ptr+0x000063b8+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000063b8+4*2))=0x02020024;
*((unsigned int *)((unsigned long)context_ptr+0x000063b8+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x000060f4))=0xc2a561a4;
*((unsigned int *)((unsigned long)context_ptr+0x000060f4+4*1))=0x8df848c5;
*((unsigned int *)((unsigned long)context_ptr+0x000060f4+4*2))=0x27aca2a0;
*((unsigned int *)((unsigned long)context_ptr+0x000060f4+4*3))=0xb6f76eac;
*((unsigned int *)((unsigned long)context_ptr+0x000060f4+4*4))=0x96d5fdf9;
*((unsigned int *)((unsigned long)context_ptr+0x000060f4+4*5))=0x6b5e7899;
*((unsigned int *)((unsigned long)context_ptr+0x000060f4+4*6))=0x092ba5e9;
*((unsigned int *)((unsigned long)context_ptr+0x000060f4+4*7))=0x3a107070;
*((unsigned int *)((unsigned long)context_ptr+0x000060f4+4*8))=0x279f6054;
*((unsigned int *)((unsigned long)context_ptr+0x00003348))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003348+4*1))=0x00006118;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000348+4*1))=0x000060f4;
*((unsigned int *)((unsigned long)context_ptr+0x00000348+4*2))=0x000063b8;
*((unsigned int *)((unsigned long)context_ptr+0x00000348+4*3))=0x02220024;
*((unsigned int *)((unsigned long)context_ptr+0x00000348+4*4))=0x011b2333;
*((unsigned int *)((unsigned long)context_ptr+0x00000348+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000084&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000063c8,"\x72\x2b\xc1\x48\xb6\xa8\xdd\x37\x8f\x8f\x25\x91\xa2\xcd\x50\xab\x52\x72\x13\xcd\x88\x21\xed\x5f\xbe\x76\x70\xbb\x0b\x3d\x1b\xbe",32))
printf("strip: 722bc148b6a8dd37, Pass\n");
else
printf("strip: 722bc148b6a8dd37, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000063c8))=0x018a0012;
*((unsigned int *)((unsigned long)context_ptr+0x000063c8+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000063c8+4*2))=0x02020025;
*((unsigned int *)((unsigned long)context_ptr+0x000063c8+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x00006138))=0x82d95f23;
*((unsigned int *)((unsigned long)context_ptr+0x00006138+4*1))=0xe1088114;
*((unsigned int *)((unsigned long)context_ptr+0x00006138+4*2))=0xe5feba3f;
*((unsigned int *)((unsigned long)context_ptr+0x00006138+4*3))=0x8bb25287;
*((unsigned int *)((unsigned long)context_ptr+0x00006138+4*4))=0x27b13de8;
*((unsigned int *)((unsigned long)context_ptr+0x00006138+4*5))=0x485dc767;
*((unsigned int *)((unsigned long)context_ptr+0x00006138+4*6))=0x24025f5a;
*((unsigned int *)((unsigned long)context_ptr+0x00006138+4*7))=0x23a7b1bd;
*((unsigned int *)((unsigned long)context_ptr+0x00006138+4*8))=0x207b7d1d;
*((unsigned int *)((unsigned long)context_ptr+0x00006138+4*9))=0x000000f7;
*((unsigned int *)((unsigned long)context_ptr+0x00003360))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003360+4*1))=0x000064a8;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000360+4*1))=0x00006138;
*((unsigned int *)((unsigned long)context_ptr+0x00000360+4*2))=0x000063c8;
*((unsigned int *)((unsigned long)context_ptr+0x00000360+4*3))=0x02220025;
*((unsigned int *)((unsigned long)context_ptr+0x00000360+4*4))=0x02c14c69;
*((unsigned int *)((unsigned long)context_ptr+0x00000360+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000008a&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006190,"\x12\x6b\x8f\x85\x5c\xa5\xcd\x75\xd5\x50\x16\x52\x58\x9a\xb4\x0a\x50\x92\x93\x15\xcb\x87\x1f\x0a\xd9\x15\x52\x90\x3e\x6d\xf2\x2c",32))
printf("strip: 126b8f855ca5cd75, Pass\n");
else
printf("strip: 126b8f855ca5cd75, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000063d8))=0x018a0012;
*((unsigned int *)((unsigned long)context_ptr+0x000063d8+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000063d8+4*2))=0x02020026;
*((unsigned int *)((unsigned long)context_ptr+0x000063d8+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x00006160))=0xc55dd255;
*((unsigned int *)((unsigned long)context_ptr+0x00006160+4*1))=0xe67a5d04;
*((unsigned int *)((unsigned long)context_ptr+0x00006160+4*2))=0xe6a2bbb8;
*((unsigned int *)((unsigned long)context_ptr+0x00006160+4*3))=0xc3eba1b9;
*((unsigned int *)((unsigned long)context_ptr+0x00006160+4*4))=0xbf30de03;
*((unsigned int *)((unsigned long)context_ptr+0x00006160+4*5))=0x6d276469;
*((unsigned int *)((unsigned long)context_ptr+0x00006160+4*6))=0xa4bcd3ff;
*((unsigned int *)((unsigned long)context_ptr+0x00006160+4*7))=0xe8ee1036;
*((unsigned int *)((unsigned long)context_ptr+0x00006160+4*8))=0x19bfe900;
*((unsigned int *)((unsigned long)context_ptr+0x00006160+4*9))=0x00002d27;
*((unsigned int *)((unsigned long)context_ptr+0x00003378))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003378+4*1))=0x00006188;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000378+4*1))=0x00006160;
*((unsigned int *)((unsigned long)context_ptr+0x00000378+4*2))=0x000063d8;
*((unsigned int *)((unsigned long)context_ptr+0x00000378+4*3))=0x02220026;
*((unsigned int *)((unsigned long)context_ptr+0x00000378+4*4))=0x06bd2728;
*((unsigned int *)((unsigned long)context_ptr+0x00000378+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000090&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000063e8,"\x34\x50\xc8\x9f\x7c\x86\x4c\xcd\x4c\xd6\x99\x51\xae\x24\xb6\xcf\x54\x9f\x01\xa8\x2b\xc4\x61\x5c\x96\x36\x75\x65\x3b\x80\xcd\x15",32))
printf("strip: 3450c89f7c864ccd, Pass\n");
else
printf("strip: 3450c89f7c864ccd, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000063e8))=0x018a0012;
*((unsigned int *)((unsigned long)context_ptr+0x000063e8+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000063e8+4*2))=0x02020027;
*((unsigned int *)((unsigned long)context_ptr+0x000063e8+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x000061a8))=0x90a00c92;
*((unsigned int *)((unsigned long)context_ptr+0x000061a8+4*1))=0x215b1490;
*((unsigned int *)((unsigned long)context_ptr+0x000061a8+4*2))=0xe1545e77;
*((unsigned int *)((unsigned long)context_ptr+0x000061a8+4*3))=0xffa81c9f;
*((unsigned int *)((unsigned long)context_ptr+0x000061a8+4*4))=0x79a8c55d;
*((unsigned int *)((unsigned long)context_ptr+0x000061a8+4*5))=0x446a3667;
*((unsigned int *)((unsigned long)context_ptr+0x000061a8+4*6))=0x25e3ab7c;
*((unsigned int *)((unsigned long)context_ptr+0x000061a8+4*7))=0x31a0c3cf;
*((unsigned int *)((unsigned long)context_ptr+0x000061a8+4*8))=0x4a522312;
*((unsigned int *)((unsigned long)context_ptr+0x000061a8+4*9))=0x002957cf;
*((unsigned int *)((unsigned long)context_ptr+0x00003390))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003390+4*1))=0x000064c8;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000390+4*1))=0x000061a8;
*((unsigned int *)((unsigned long)context_ptr+0x00000390+4*2))=0x000063e8;
*((unsigned int *)((unsigned long)context_ptr+0x00000390+4*3))=0x02220027;
*((unsigned int *)((unsigned long)context_ptr+0x00000390+4*4))=0x0cda5a09;
*((unsigned int *)((unsigned long)context_ptr+0x00000390+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000096&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006204,"\xe8\xab\x9b\x79\xcd\xf0\x65\xfb\x6c\xa6\x34\x47\xc7\xc6\x63\x64\x48\x7a\x7e\xfe\x4d\x0e\xdd\x3a\xed\x6c\x94\xfb\x7a\x19\x77\x07",32))
printf("strip: e8ab9b79cdf065fb, Pass\n");
else
printf("strip: e8ab9b79cdf065fb, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000063f8))=0x018a0012;
*((unsigned int *)((unsigned long)context_ptr+0x000063f8+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000063f8+4*2))=0x02020028;
*((unsigned int *)((unsigned long)context_ptr+0x000063f8+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x000061d0))=0xed7f590e;
*((unsigned int *)((unsigned long)context_ptr+0x000061d0+4*1))=0x1970ea10;
*((unsigned int *)((unsigned long)context_ptr+0x000061d0+4*2))=0x3c221ec0;
*((unsigned int *)((unsigned long)context_ptr+0x000061d0+4*3))=0x96dca98c;
*((unsigned int *)((unsigned long)context_ptr+0x000061d0+4*4))=0xa9817ba3;
*((unsigned int *)((unsigned long)context_ptr+0x000061d0+4*5))=0x9f9f4b45;
*((unsigned int *)((unsigned long)context_ptr+0x000061d0+4*6))=0xd58c322e;
*((unsigned int *)((unsigned long)context_ptr+0x000061d0+4*7))=0x870c2c4f;
*((unsigned int *)((unsigned long)context_ptr+0x000061d0+4*8))=0xa88b9c87;
*((unsigned int *)((unsigned long)context_ptr+0x000061d0+4*9))=0x3acb51de;
*((unsigned int *)((unsigned long)context_ptr+0x000033a8))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x000033a8+4*1))=0x000061f8;
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
*((unsigned int *)((unsigned long)context_ptr+0x000003a8+4*1))=0x000061d0;
*((unsigned int *)((unsigned long)context_ptr+0x000003a8+4*2))=0x000063f8;
*((unsigned int *)((unsigned long)context_ptr+0x000003a8+4*3))=0x02220028;
*((unsigned int *)((unsigned long)context_ptr+0x000003a8+4*4))=0x08506b30;
*((unsigned int *)((unsigned long)context_ptr+0x000003a8+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000009c&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006408,"\x92\x60\x27\xde\x0f\x08\xa1\xad\xf7\xea\x66\xe5\xfc\x9e\x8e\xb5\x02\xfe\x60\x2f\x28\x03\xb8\xa1\xe7\xbe\xcb\xe2\xcb\x64\x98\x59",32))
printf("strip: 926027de0f08a1ad, Pass\n");
else
printf("strip: 926027de0f08a1ad, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006408))=0x018a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006408+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006408+4*2))=0x02020029;
*((unsigned int *)((unsigned long)context_ptr+0x00006408+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x00006218))=0x29d745de;
*((unsigned int *)((unsigned long)context_ptr+0x00006218+4*1))=0xef1fa9da;
*((unsigned int *)((unsigned long)context_ptr+0x00006218+4*2))=0x0dd72f6f;
*((unsigned int *)((unsigned long)context_ptr+0x00006218+4*3))=0xbf17bc09;
*((unsigned int *)((unsigned long)context_ptr+0x00006218+4*4))=0x9023f018;
*((unsigned int *)((unsigned long)context_ptr+0x00006218+4*5))=0x7d185da5;
*((unsigned int *)((unsigned long)context_ptr+0x00006218+4*6))=0x3934e455;
*((unsigned int *)((unsigned long)context_ptr+0x00006218+4*7))=0x23497198;
*((unsigned int *)((unsigned long)context_ptr+0x00006218+4*8))=0xf0e718d6;
*((unsigned int *)((unsigned long)context_ptr+0x00006218+4*9))=0xca44ec21;
*((unsigned int *)((unsigned long)context_ptr+0x00006218+4*10))=0x00000053;
*((unsigned int *)((unsigned long)context_ptr+0x000033c0))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x000033c0+4*1))=0x000064e8;
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
*((unsigned int *)((unsigned long)context_ptr+0x000003c0+4*1))=0x00006218;
*((unsigned int *)((unsigned long)context_ptr+0x000003c0+4*2))=0x00006408;
*((unsigned int *)((unsigned long)context_ptr+0x000003c0+4*3))=0x02220029;
*((unsigned int *)((unsigned long)context_ptr+0x000003c0+4*4))=0x08bd657b;
*((unsigned int *)((unsigned long)context_ptr+0x000003c0+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000000a2&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x0000627c,"\x8f\x13\x15\xa6\x2d\x97\x35\x8c\x52\xf8\x59\x92\x53\xa7\xa8\x70\xc4\xc7\x77\xbd\xb3\x6c\x03\x01\x21\xd2\x49\x04\x9b\xbc\xbb\x0f",32))
printf("strip: 8f1315a62d97358c, Pass\n");
else
printf("strip: 8f1315a62d97358c, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006418))=0x018a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006418+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006418+4*2))=0x0202002a;
*((unsigned int *)((unsigned long)context_ptr+0x00006418+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x00006244))=0x60cb31a7;
*((unsigned int *)((unsigned long)context_ptr+0x00006244+4*1))=0x84719743;
*((unsigned int *)((unsigned long)context_ptr+0x00006244+4*2))=0x6edf09f8;
*((unsigned int *)((unsigned long)context_ptr+0x00006244+4*3))=0x79bce0d8;
*((unsigned int *)((unsigned long)context_ptr+0x00006244+4*4))=0xb6659885;
*((unsigned int *)((unsigned long)context_ptr+0x00006244+4*5))=0x90f456da;
*((unsigned int *)((unsigned long)context_ptr+0x00006244+4*6))=0x47b9294b;
*((unsigned int *)((unsigned long)context_ptr+0x00006244+4*7))=0x605af2cf;
*((unsigned int *)((unsigned long)context_ptr+0x00006244+4*8))=0xd3ff414d;
*((unsigned int *)((unsigned long)context_ptr+0x00006244+4*9))=0xd2f307dd;
*((unsigned int *)((unsigned long)context_ptr+0x00006244+4*10))=0x0000edd2;
*((unsigned int *)((unsigned long)context_ptr+0x000033d8))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x000033d8+4*1))=0x00006270;
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
*((unsigned int *)((unsigned long)context_ptr+0x000003d8+4*1))=0x00006244;
*((unsigned int *)((unsigned long)context_ptr+0x000003d8+4*2))=0x00006418;
*((unsigned int *)((unsigned long)context_ptr+0x000003d8+4*3))=0x0222002a;
*((unsigned int *)((unsigned long)context_ptr+0x000003d8+4*4))=0x091c73df;
*((unsigned int *)((unsigned long)context_ptr+0x000003d8+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000000a8&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000062c8,"\x5e\xd7\x89\x2f\xe9\x69\xdc\xc6\x04\x99\x4f\x95\x09\xfb\x19\xf4\x16\x33\xb6\x33\x54\xca\xe5\x32\x02\x6a\xec\xce\xe6\x2a\xdc\x8b",32))
printf("strip: 5ed7892fe969dcc6, Pass\n");
else
printf("strip: 5ed7892fe969dcc6, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006290))=0x018a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006290+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006290+4*2))=0x0202002b;
*((unsigned int *)((unsigned long)context_ptr+0x00006290+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x000062a0))=0xcfec84a1;
*((unsigned int *)((unsigned long)context_ptr+0x000062a0+4*1))=0x836aad98;
*((unsigned int *)((unsigned long)context_ptr+0x000062a0+4*2))=0x7533d6a1;
*((unsigned int *)((unsigned long)context_ptr+0x000062a0+4*3))=0x1e09322f;
*((unsigned int *)((unsigned long)context_ptr+0x000062a0+4*4))=0x244e54c1;
*((unsigned int *)((unsigned long)context_ptr+0x000062a0+4*5))=0x610e6a93;
*((unsigned int *)((unsigned long)context_ptr+0x000062a0+4*6))=0xdbf9c1ce;
*((unsigned int *)((unsigned long)context_ptr+0x000062a0+4*7))=0x68c9ca7f;
*((unsigned int *)((unsigned long)context_ptr+0x000062a0+4*8))=0x9f718f63;
*((unsigned int *)((unsigned long)context_ptr+0x000062a0+4*9))=0x86a4ebd0;
*((unsigned int *)((unsigned long)context_ptr+0x000062a0+4*10))=0x00396637;
*((unsigned int *)((unsigned long)context_ptr+0x000033f0))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x000033f0+4*1))=0x00006508;
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
*((unsigned int *)((unsigned long)context_ptr+0x000003f0+4*1))=0x000062a0;
*((unsigned int *)((unsigned long)context_ptr+0x000003f0+4*2))=0x00006290;
*((unsigned int *)((unsigned long)context_ptr+0x000003f0+4*3))=0x0222002b;
*((unsigned int *)((unsigned long)context_ptr+0x000003f0+4*4))=0x0273dad1;
*((unsigned int *)((unsigned long)context_ptr+0x000003f0+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000000ae&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006428,"\xc6\x47\xbf\xa5\x75\x19\x19\x5c\x97\x29\x96\x66\x15\x7b\xa1\x21\x94\x61\x1a\x2b\x0b\x0f\x4c\x37\xdf\x2a\x19\xb5\x43\x35\xb9\x68",32))
printf("strip: c647bfa57519195c, Pass\n");
else
printf("strip: c647bfa57519195c, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006428))=0x018a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006428+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006428+4*2))=0x0202002c;
*((unsigned int *)((unsigned long)context_ptr+0x00006428+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x000062cc))=0xa076fc1a;
*((unsigned int *)((unsigned long)context_ptr+0x000062cc+4*1))=0x66c41081;
*((unsigned int *)((unsigned long)context_ptr+0x000062cc+4*2))=0x244fd27b;
*((unsigned int *)((unsigned long)context_ptr+0x000062cc+4*3))=0x9710b00b;
*((unsigned int *)((unsigned long)context_ptr+0x000062cc+4*4))=0x4a641c11;
*((unsigned int *)((unsigned long)context_ptr+0x000062cc+4*5))=0xf6f2f11b;
*((unsigned int *)((unsigned long)context_ptr+0x000062cc+4*6))=0x6790e8fa;
*((unsigned int *)((unsigned long)context_ptr+0x000062cc+4*7))=0xc63a86bd;
*((unsigned int *)((unsigned long)context_ptr+0x000062cc+4*8))=0x89f3a629;
*((unsigned int *)((unsigned long)context_ptr+0x000062cc+4*9))=0x6e825b25;
*((unsigned int *)((unsigned long)context_ptr+0x000062cc+4*10))=0xf8e19926;
*((unsigned int *)((unsigned long)context_ptr+0x00003408))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003408+4*1))=0x000062f8;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000408+4*1))=0x000062cc;
*((unsigned int *)((unsigned long)context_ptr+0x00000408+4*2))=0x00006428;
*((unsigned int *)((unsigned long)context_ptr+0x00000408+4*3))=0x0222002c;
*((unsigned int *)((unsigned long)context_ptr+0x00000408+4*4))=0x0059251e;
*((unsigned int *)((unsigned long)context_ptr+0x00000408+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000000b4&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006348,"\xf8\xfa\x89\x37\x52\x3b\xcb\x26\x69\x27\x6a\xa5\xa3\x9d\xe8\x45\x7e\x39\x24\xbd\xa9\x09\xf4\xce\x8b\x54\x07\xe4\xd0\x0c\x85\xfa",32))
printf("strip: f8fa8937523bcb26, Pass\n");
else
printf("strip: f8fa8937523bcb26, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006438))=0x018a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006438+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006438+4*2))=0x0202002d;
*((unsigned int *)((unsigned long)context_ptr+0x00006438+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x00006328))=0xe9fd2add;
*((unsigned int *)((unsigned long)context_ptr+0x00006328+4*1))=0xddaac417;
*((unsigned int *)((unsigned long)context_ptr+0x00006328+4*2))=0xbcca4f7f;
*((unsigned int *)((unsigned long)context_ptr+0x00006328+4*3))=0x7fc4fc89;
*((unsigned int *)((unsigned long)context_ptr+0x00006328+4*4))=0x0cd781ed;
*((unsigned int *)((unsigned long)context_ptr+0x00006328+4*5))=0x233b3621;
*((unsigned int *)((unsigned long)context_ptr+0x00006328+4*6))=0xb9978f0a;
*((unsigned int *)((unsigned long)context_ptr+0x00006328+4*7))=0x0373749d;
*((unsigned int *)((unsigned long)context_ptr+0x00006328+4*8))=0xf6a0a29d;
*((unsigned int *)((unsigned long)context_ptr+0x00006328+4*9))=0x8d9c35b4;
*((unsigned int *)((unsigned long)context_ptr+0x00006328+4*10))=0x75c198ac;
*((unsigned int *)((unsigned long)context_ptr+0x00006328+4*11))=0x00000091;
*((unsigned int *)((unsigned long)context_ptr+0x00003420))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003420+4*1))=0x00006528;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000420+4*1))=0x00006328;
*((unsigned int *)((unsigned long)context_ptr+0x00000420+4*2))=0x00006438;
*((unsigned int *)((unsigned long)context_ptr+0x00000420+4*3))=0x0222002d;
*((unsigned int *)((unsigned long)context_ptr+0x00000420+4*4))=0x0a9988bb;
*((unsigned int *)((unsigned long)context_ptr+0x00000420+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000000ba&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006448,"\x27\xc5\x9d\x71\xba\x8a\xe5\x74\x2f\xde\xc0\x96\x29\x50\x0f\x88\x2c\xc6\x50\xdb\x17\x87\x67\x62\x21\xcc\x16\x54\x1b\xad\xd6\x0c",32))
printf("strip: 27c59d71ba8ae574, Pass\n");
else
printf("strip: 27c59d71ba8ae574, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006318))=0x018a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006318+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006318+4*2))=0x0202002e;
*((unsigned int *)((unsigned long)context_ptr+0x00006318+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x00006358))=0xd4d113a0;
*((unsigned int *)((unsigned long)context_ptr+0x00006358+4*1))=0xe62cd4ce;
*((unsigned int *)((unsigned long)context_ptr+0x00006358+4*2))=0x2800434b;
*((unsigned int *)((unsigned long)context_ptr+0x00006358+4*3))=0x0cdf3b58;
*((unsigned int *)((unsigned long)context_ptr+0x00006358+4*4))=0xd5dd6071;
*((unsigned int *)((unsigned long)context_ptr+0x00006358+4*5))=0x4075ad53;
*((unsigned int *)((unsigned long)context_ptr+0x00006358+4*6))=0xbcb277b2;
*((unsigned int *)((unsigned long)context_ptr+0x00006358+4*7))=0x0223438f;
*((unsigned int *)((unsigned long)context_ptr+0x00006358+4*8))=0x48d3a96c;
*((unsigned int *)((unsigned long)context_ptr+0x00006358+4*9))=0x55567b11;
*((unsigned int *)((unsigned long)context_ptr+0x00006358+4*10))=0xb571850c;
*((unsigned int *)((unsigned long)context_ptr+0x00006358+4*11))=0x000061ad;
*((unsigned int *)((unsigned long)context_ptr+0x00003438))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003438+4*1))=0x00006448;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000438+4*1))=0x00006358;
*((unsigned int *)((unsigned long)context_ptr+0x00000438+4*2))=0x00006318;
*((unsigned int *)((unsigned long)context_ptr+0x00000438+4*3))=0x0222002e;
*((unsigned int *)((unsigned long)context_ptr+0x00000438+4*4))=0x033f4d3f;
*((unsigned int *)((unsigned long)context_ptr+0x00000438+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000000c0&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006468,"\x4d\x25\x8b\xd4\x5c\x92\x65\xaf\x9c\x9a\x2c\x57\x7b\x32\x4e\x81\xf1\x68\x32\xd9\x2c\x1f\x41\xa8\xa0\x9e\x50\x0f\x69\x01\x37\x5b",32))
printf("strip: 4d258bd45c9265af, Pass\n");
else
printf("strip: 4d258bd45c9265af, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006018))=0x018a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006018+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006018+4*2))=0x0202002f;
*((unsigned int *)((unsigned long)context_ptr+0x00006018+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x00006548))=0x3469d1a9;
*((unsigned int *)((unsigned long)context_ptr+0x00006548+4*1))=0xa8987528;
*((unsigned int *)((unsigned long)context_ptr+0x00006548+4*2))=0x22003e96;
*((unsigned int *)((unsigned long)context_ptr+0x00006548+4*3))=0xfa91f870;
*((unsigned int *)((unsigned long)context_ptr+0x00006548+4*4))=0xb04afed7;
*((unsigned int *)((unsigned long)context_ptr+0x00006548+4*5))=0x679dde6e;
*((unsigned int *)((unsigned long)context_ptr+0x00006548+4*6))=0x6c7ed7f1;
*((unsigned int *)((unsigned long)context_ptr+0x00006548+4*7))=0x2a4f6767;
*((unsigned int *)((unsigned long)context_ptr+0x00006548+4*8))=0x289f1fd4;
*((unsigned int *)((unsigned long)context_ptr+0x00006548+4*9))=0x04203ade;
*((unsigned int *)((unsigned long)context_ptr+0x00006548+4*10))=0xdd50c9e7;
*((unsigned int *)((unsigned long)context_ptr+0x00006548+4*11))=0x00913882;
*((unsigned int *)((unsigned long)context_ptr+0x00003450))=0x04c00020;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000450+4*1))=0x00006548;
*((unsigned int *)((unsigned long)context_ptr+0x00000450+4*2))=0x00006018;
*((unsigned int *)((unsigned long)context_ptr+0x00000450+4*3))=0x0222002f;
*((unsigned int *)((unsigned long)context_ptr+0x00000450+4*4))=0x04570996;
*((unsigned int *)((unsigned long)context_ptr+0x00000450+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000000c6&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006388,"\xa5\x2b\x9d\x02\x9c\xe7\x3a\x9e\xea\x56\xb9\x31\xc9\xa5\xfc\xcf\xcf\x0a\x33\x43\x02\x79\x78\x6d\x0f\x7a\xa6\x81\xd4\x2e\x44\x6e",32))
printf("strip: a52b9d029ce73a9e, Pass\n");
else
printf("strip: a52b9d029ce73a9e, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006008))=0x018a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006008+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006008+4*2))=0x02020030;
*((unsigned int *)((unsigned long)context_ptr+0x00006008+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x00006578))=0xcdab517b;
*((unsigned int *)((unsigned long)context_ptr+0x00006578+4*1))=0x97aa6b1e;
*((unsigned int *)((unsigned long)context_ptr+0x00006578+4*2))=0xe38bdedf;
*((unsigned int *)((unsigned long)context_ptr+0x00006578+4*3))=0x620226ce;
*((unsigned int *)((unsigned long)context_ptr+0x00006578+4*4))=0x84cf075d;
*((unsigned int *)((unsigned long)context_ptr+0x00006578+4*5))=0x66ced5f9;
*((unsigned int *)((unsigned long)context_ptr+0x00006578+4*6))=0x8d1ab6f1;
*((unsigned int *)((unsigned long)context_ptr+0x00006578+4*7))=0x0a67a436;
*((unsigned int *)((unsigned long)context_ptr+0x00006578+4*8))=0x35a3ebe6;
*((unsigned int *)((unsigned long)context_ptr+0x00006578+4*9))=0x351db169;
*((unsigned int *)((unsigned long)context_ptr+0x00006578+4*10))=0x23c1ef17;
*((unsigned int *)((unsigned long)context_ptr+0x00006578+4*11))=0x37f9a83c;
*((unsigned int *)((unsigned long)context_ptr+0x00003468))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003468+4*1))=0x00006388;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000468+4*1))=0x00006578;
*((unsigned int *)((unsigned long)context_ptr+0x00000468+4*2))=0x00006008;
*((unsigned int *)((unsigned long)context_ptr+0x00000468+4*3))=0x02220030;
*((unsigned int *)((unsigned long)context_ptr+0x00000468+4*4))=0x0db8309f;
*((unsigned int *)((unsigned long)context_ptr+0x00000468+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000000cc&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000060b0,"\xed\xb9\xa7\x7d\xbc\xb4\x0a\x8e\xae\xa2\x83\x22\x02\x3f\x91\xdf\x2b\xdd\x36\xb0\xdf\xc2\xcf\x07\x45\xc3\x8a\xe6\xc8\x18\x4a\x5d",32))
printf("strip: edb9a77dbcb40a8e, Pass\n");
else
printf("strip: edb9a77dbcb40a8e, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006028))=0x018a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006028+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006028+4*2))=0x02020031;
*((unsigned int *)((unsigned long)context_ptr+0x00006028+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x00006058))=0x9f680c05;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*1))=0x61e6a473;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*2))=0x560bcb6b;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*3))=0xa9aca70f;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*4))=0xa103be9e;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*5))=0x08c1d5a1;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*6))=0x1b476997;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*7))=0x7b3d271f;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*8))=0x8534429a;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*9))=0x643a137c;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*10))=0xdf3f75ef;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*11))=0x7ddf27ff;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*12))=0x00000041;
*((unsigned int *)((unsigned long)context_ptr+0x00003480))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003480+4*1))=0x00006468;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000480+4*1))=0x00006058;
*((unsigned int *)((unsigned long)context_ptr+0x00000480+4*2))=0x00006028;
*((unsigned int *)((unsigned long)context_ptr+0x00000480+4*3))=0x02220031;
*((unsigned int *)((unsigned long)context_ptr+0x00000480+4*4))=0x08d6ba9f;
*((unsigned int *)((unsigned long)context_ptr+0x00000480+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000000d2&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006488,"\x0b\xf6\x34\x03\x06\xd0\x0f\x89\x2d\x9a\xfa\xab\x29\x99\x60\x08\x3c\xe2\x0d\x6d\x81\x9f\x3b\x19\x91\x32\xc9\x53\xdc\xeb\x78\x7c",32))
printf("strip: 0bf6340306d00f89, Pass\n");
else
printf("strip: 0bf6340306d00f89, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000063a8))=0x018a0012;
*((unsigned int *)((unsigned long)context_ptr+0x000063a8+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000063a8+4*2))=0x02020032;
*((unsigned int *)((unsigned long)context_ptr+0x000063a8+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x0000608c))=0x4d71b703;
*((unsigned int *)((unsigned long)context_ptr+0x0000608c+4*1))=0xf8ce6186;
*((unsigned int *)((unsigned long)context_ptr+0x0000608c+4*2))=0x02a709a6;
*((unsigned int *)((unsigned long)context_ptr+0x0000608c+4*3))=0x06dd1766;
*((unsigned int *)((unsigned long)context_ptr+0x0000608c+4*4))=0x428276ad;
*((unsigned int *)((unsigned long)context_ptr+0x0000608c+4*5))=0x7d736e60;
*((unsigned int *)((unsigned long)context_ptr+0x0000608c+4*6))=0x84dca1d5;
*((unsigned int *)((unsigned long)context_ptr+0x0000608c+4*7))=0xbcb6a086;
*((unsigned int *)((unsigned long)context_ptr+0x0000608c+4*8))=0xbc46668f;
*((unsigned int *)((unsigned long)context_ptr+0x0000608c+4*9))=0xe5fdf50f;
*((unsigned int *)((unsigned long)context_ptr+0x0000608c+4*10))=0xd599f5e3;
*((unsigned int *)((unsigned long)context_ptr+0x0000608c+4*11))=0x5a05752f;
*((unsigned int *)((unsigned long)context_ptr+0x0000608c+4*12))=0x00002c6f;
*((unsigned int *)((unsigned long)context_ptr+0x00003498))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003498+4*1))=0x00006488;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000498+4*1))=0x0000608c;
*((unsigned int *)((unsigned long)context_ptr+0x00000498+4*2))=0x000063a8;
*((unsigned int *)((unsigned long)context_ptr+0x00000498+4*3))=0x02220032;
*((unsigned int *)((unsigned long)context_ptr+0x00000498+4*4))=0x02913688;
*((unsigned int *)((unsigned long)context_ptr+0x00000498+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000000d8&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006118,"\x07\x3e\x92\x46\x94\xb0\xb0\x71\x85\xe3\x82\x4c\x73\x54\x6f\x63\xc0\x41\x81\xa0\x18\xa1\xf7\xdf\x09\xbb\x13\xf3\x55\x23\x73\xc8",32))
printf("strip: 073e924694b0b071, Pass\n");
else
printf("strip: 073e924694b0b071, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000063b8))=0x018a0012;
*((unsigned int *)((unsigned long)context_ptr+0x000063b8+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000063b8+4*2))=0x02020033;
*((unsigned int *)((unsigned long)context_ptr+0x000063b8+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x000060c0))=0xb06f0a4b;
*((unsigned int *)((unsigned long)context_ptr+0x000060c0+4*1))=0x6b1a2a02;
*((unsigned int *)((unsigned long)context_ptr+0x000060c0+4*2))=0x5a6644df;
*((unsigned int *)((unsigned long)context_ptr+0x000060c0+4*3))=0x0a371727;
*((unsigned int *)((unsigned long)context_ptr+0x000060c0+4*4))=0xfd47c264;
*((unsigned int *)((unsigned long)context_ptr+0x000060c0+4*5))=0x9191c181;
*((unsigned int *)((unsigned long)context_ptr+0x000060c0+4*6))=0x2934c8c8;
*((unsigned int *)((unsigned long)context_ptr+0x000060c0+4*7))=0x3b143b2f;
*((unsigned int *)((unsigned long)context_ptr+0x000060c0+4*8))=0x9d07a165;
*((unsigned int *)((unsigned long)context_ptr+0x000060c0+4*9))=0x91a7e4b5;
*((unsigned int *)((unsigned long)context_ptr+0x000060c0+4*10))=0xcd9c614c;
*((unsigned int *)((unsigned long)context_ptr+0x000060c0+4*11))=0x9e5daa59;
*((unsigned int *)((unsigned long)context_ptr+0x000060c0+4*12))=0x00a8190b;
*((unsigned int *)((unsigned long)context_ptr+0x000034b0))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x000034b0+4*1))=0x000060f4;
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
*((unsigned int *)((unsigned long)context_ptr+0x000004b0+4*2))=0x000063b8;
*((unsigned int *)((unsigned long)context_ptr+0x000004b0+4*3))=0x02220033;
*((unsigned int *)((unsigned long)context_ptr+0x000004b0+4*4))=0x0bd9695b;
*((unsigned int *)((unsigned long)context_ptr+0x000004b0+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000000de&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000064a8,"\x38\x4a\xe9\xfd\x36\x8e\x17\x1d\x6a\x96\x33\xd7\xb7\xde\x0e\xf4\x1f\xce\x78\x3c\xce\x8e\xe7\x2b\x2e\x0a\xfc\x45\xba\xfb\xfc\x31",32))
printf("strip: 384ae9fd368e171d, Pass\n");
else
printf("strip: 384ae9fd368e171d, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000063c8))=0x018a0012;
*((unsigned int *)((unsigned long)context_ptr+0x000063c8+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000063c8+4*2))=0x02020034;
*((unsigned int *)((unsigned long)context_ptr+0x000063c8+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x00006114))=0x40119b2c;
*((unsigned int *)((unsigned long)context_ptr+0x00006114+4*1))=0xe4fac325;
*((unsigned int *)((unsigned long)context_ptr+0x00006114+4*2))=0xa8e8a437;
*((unsigned int *)((unsigned long)context_ptr+0x00006114+4*3))=0xa554720f;
*((unsigned int *)((unsigned long)context_ptr+0x00006114+4*4))=0x0e0ca80f;
*((unsigned int *)((unsigned long)context_ptr+0x00006114+4*5))=0x43c4dd3a;
*((unsigned int *)((unsigned long)context_ptr+0x00006114+4*6))=0x8eee4202;
*((unsigned int *)((unsigned long)context_ptr+0x00006114+4*7))=0xd8a1b914;
*((unsigned int *)((unsigned long)context_ptr+0x00006114+4*8))=0xe0add8fa;
*((unsigned int *)((unsigned long)context_ptr+0x00006114+4*9))=0x4c83369e;
*((unsigned int *)((unsigned long)context_ptr+0x00006114+4*10))=0x49112f3f;
*((unsigned int *)((unsigned long)context_ptr+0x00006114+4*11))=0x1c8782e0;
*((unsigned int *)((unsigned long)context_ptr+0x00006114+4*12))=0x2ff71ef5;
*((unsigned int *)((unsigned long)context_ptr+0x000034c8))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x000034c8+4*1))=0x000064a8;
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
*((unsigned int *)((unsigned long)context_ptr+0x000004c8+4*1))=0x00006114;
*((unsigned int *)((unsigned long)context_ptr+0x000004c8+4*2))=0x000063c8;
*((unsigned int *)((unsigned long)context_ptr+0x000004c8+4*3))=0x02220034;
*((unsigned int *)((unsigned long)context_ptr+0x000004c8+4*4))=0x007f1a41;
*((unsigned int *)((unsigned long)context_ptr+0x000004c8+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000000e4&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006188,"\x90\x60\x2a\x75\x1e\xc3\xd1\x02\xc0\x40\xa0\xb1\x3c\xb8\x5a\x3e\xd9\x73\x1b\x4c\x35\x14\x1c\x69\xb9\xf5\xfa\x58\x2b\x64\xc6\x8d",32))
printf("strip: 90602a751ec3d102, Pass\n");
else
printf("strip: 90602a751ec3d102, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000063d8))=0x018a0012;
*((unsigned int *)((unsigned long)context_ptr+0x000063d8+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000063d8+4*2))=0x02020035;
*((unsigned int *)((unsigned long)context_ptr+0x000063d8+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x00006148))=0x6011caab;
*((unsigned int *)((unsigned long)context_ptr+0x00006148+4*1))=0xda563135;
*((unsigned int *)((unsigned long)context_ptr+0x00006148+4*2))=0xc9d91060;
*((unsigned int *)((unsigned long)context_ptr+0x00006148+4*3))=0x5b270b8c;
*((unsigned int *)((unsigned long)context_ptr+0x00006148+4*4))=0xf7c44c6a;
*((unsigned int *)((unsigned long)context_ptr+0x00006148+4*5))=0x23732b6d;
*((unsigned int *)((unsigned long)context_ptr+0x00006148+4*6))=0x5afb6876;
*((unsigned int *)((unsigned long)context_ptr+0x00006148+4*7))=0xb2b4ee1f;
*((unsigned int *)((unsigned long)context_ptr+0x00006148+4*8))=0x4ab63453;
*((unsigned int *)((unsigned long)context_ptr+0x00006148+4*9))=0xa270189d;
*((unsigned int *)((unsigned long)context_ptr+0x00006148+4*10))=0x743aa38c;
*((unsigned int *)((unsigned long)context_ptr+0x00006148+4*11))=0xa5351310;
*((unsigned int *)((unsigned long)context_ptr+0x00006148+4*12))=0x015b99cb;
*((unsigned int *)((unsigned long)context_ptr+0x00006148+4*13))=0x000000b1;
*((unsigned int *)((unsigned long)context_ptr+0x000034e0))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x000034e0+4*1))=0x00006180;
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
*((unsigned int *)((unsigned long)context_ptr+0x000004e0+4*1))=0x00006148;
*((unsigned int *)((unsigned long)context_ptr+0x000004e0+4*2))=0x000063d8;
*((unsigned int *)((unsigned long)context_ptr+0x000004e0+4*3))=0x02220035;
*((unsigned int *)((unsigned long)context_ptr+0x000004e0+4*4))=0x09e051c7;
*((unsigned int *)((unsigned long)context_ptr+0x000004e0+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000000ea&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000064c8,"\x53\x3c\x4e\x57\x13\x8a\x29\x9c\x84\x4f\x5c\x5c\x2f\x32\x82\x59\x65\xb6\x5d\x96\x3b\x96\xb4\x54\xcc\x28\xce\x91\x61\x62\x44\x1f",32))
printf("strip: 533c4e57138a299c, Pass\n");
else
printf("strip: 533c4e57138a299c, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000063e8))=0x018a0012;
*((unsigned int *)((unsigned long)context_ptr+0x000063e8+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000063e8+4*2))=0x02020036;
*((unsigned int *)((unsigned long)context_ptr+0x000063e8+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x000065a8))=0xca6c1a7d;
*((unsigned int *)((unsigned long)context_ptr+0x000065a8+4*1))=0xd166d75d;
*((unsigned int *)((unsigned long)context_ptr+0x000065a8+4*2))=0xec01abc2;
*((unsigned int *)((unsigned long)context_ptr+0x000065a8+4*3))=0xdc03175d;
*((unsigned int *)((unsigned long)context_ptr+0x000065a8+4*4))=0xeffc966b;
*((unsigned int *)((unsigned long)context_ptr+0x000065a8+4*5))=0x6ba4bba1;
*((unsigned int *)((unsigned long)context_ptr+0x000065a8+4*6))=0x364c351d;
*((unsigned int *)((unsigned long)context_ptr+0x000065a8+4*7))=0xb23c34ee;
*((unsigned int *)((unsigned long)context_ptr+0x000065a8+4*8))=0xd04ba3f8;
*((unsigned int *)((unsigned long)context_ptr+0x000065a8+4*9))=0xc07ea628;
*((unsigned int *)((unsigned long)context_ptr+0x000065a8+4*10))=0xd7009f7c;
*((unsigned int *)((unsigned long)context_ptr+0x000065a8+4*11))=0xfdf232b9;
*((unsigned int *)((unsigned long)context_ptr+0x000065a8+4*12))=0x4efdd6a0;
*((unsigned int *)((unsigned long)context_ptr+0x000065a8+4*13))=0x0000522f;
*((unsigned int *)((unsigned long)context_ptr+0x000034f8))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x000034f8+4*1))=0x000064c8;
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
*((unsigned int *)((unsigned long)context_ptr+0x000004f8+4*1))=0x000065a8;
*((unsigned int *)((unsigned long)context_ptr+0x000004f8+4*2))=0x000063e8;
*((unsigned int *)((unsigned long)context_ptr+0x000004f8+4*3))=0x02220036;
*((unsigned int *)((unsigned long)context_ptr+0x000004f8+4*4))=0x073705a4;
*((unsigned int *)((unsigned long)context_ptr+0x000004f8+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000000f0&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000061f8,"\x13\xda\x57\x85\xba\xac\xe4\x04\xe3\x06\x2e\xd9\xa4\x3e\x40\x4c\x64\xc0\x6a\x52\x33\x62\xdc\x18\x35\x8e\x91\x90\x67\xdf\x17\x81",32))
printf("strip: 13da5785baace404, Pass\n");
else
printf("strip: 13da5785baace404, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000063f8))=0x018a0012;
*((unsigned int *)((unsigned long)context_ptr+0x000063f8+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000063f8+4*2))=0x02020037;
*((unsigned int *)((unsigned long)context_ptr+0x000063f8+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x000061a0))=0xfc18e89d;
*((unsigned int *)((unsigned long)context_ptr+0x000061a0+4*1))=0xf259074e;
*((unsigned int *)((unsigned long)context_ptr+0x000061a0+4*2))=0xad467e4a;
*((unsigned int *)((unsigned long)context_ptr+0x000061a0+4*3))=0xa01bec5f;
*((unsigned int *)((unsigned long)context_ptr+0x000061a0+4*4))=0xc6885efc;
*((unsigned int *)((unsigned long)context_ptr+0x000061a0+4*5))=0xe1da7925;
*((unsigned int *)((unsigned long)context_ptr+0x000061a0+4*6))=0xae88cc86;
*((unsigned int *)((unsigned long)context_ptr+0x000061a0+4*7))=0x0b1713cf;
*((unsigned int *)((unsigned long)context_ptr+0x000061a0+4*8))=0x5b8138e5;
*((unsigned int *)((unsigned long)context_ptr+0x000061a0+4*9))=0x1bde5963;
*((unsigned int *)((unsigned long)context_ptr+0x000061a0+4*10))=0x789580bd;
*((unsigned int *)((unsigned long)context_ptr+0x000061a0+4*11))=0x69698bc6;
*((unsigned int *)((unsigned long)context_ptr+0x000061a0+4*12))=0xfa3e8d6c;
*((unsigned int *)((unsigned long)context_ptr+0x000061a0+4*13))=0x008856dc;
*((unsigned int *)((unsigned long)context_ptr+0x00003510))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003510+4*1))=0x000061d8;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000510+4*1))=0x000061a0;
*((unsigned int *)((unsigned long)context_ptr+0x00000510+4*2))=0x000063f8;
*((unsigned int *)((unsigned long)context_ptr+0x00000510+4*3))=0x02220037;
*((unsigned int *)((unsigned long)context_ptr+0x00000510+4*4))=0x02c2f317;
*((unsigned int *)((unsigned long)context_ptr+0x00000510+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000000f6&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000064e8,"\x0d\xd8\xd9\x24\xb5\xff\x0d\x30\xc1\xf8\x16\xd7\xc1\x50\xa4\xf2\xaa\x77\x84\xa2\x4b\x3e\x6e\x1c\xd4\xc2\x85\x70\x2b\x58\x41\x42",32))
printf("strip: 0dd8d924b5ff0d30, Pass\n");
else
printf("strip: 0dd8d924b5ff0d30, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006408))=0x018a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006408+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006408+4*2))=0x02020038;
*((unsigned int *)((unsigned long)context_ptr+0x00006408+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x000061f8))=0x2929e730;
*((unsigned int *)((unsigned long)context_ptr+0x000061f8+4*1))=0xacc2556b;
*((unsigned int *)((unsigned long)context_ptr+0x000061f8+4*2))=0x1a861c0f;
*((unsigned int *)((unsigned long)context_ptr+0x000061f8+4*3))=0x029eb78f;
*((unsigned int *)((unsigned long)context_ptr+0x000061f8+4*4))=0x867541ef;
*((unsigned int *)((unsigned long)context_ptr+0x000061f8+4*5))=0xd6a84ffa;
*((unsigned int *)((unsigned long)context_ptr+0x000061f8+4*6))=0x21473990;
*((unsigned int *)((unsigned long)context_ptr+0x000061f8+4*7))=0xeb547ebb;
*((unsigned int *)((unsigned long)context_ptr+0x000061f8+4*8))=0x649e2033;
*((unsigned int *)((unsigned long)context_ptr+0x000061f8+4*9))=0x049b9661;
*((unsigned int *)((unsigned long)context_ptr+0x000061f8+4*10))=0x36080c19;
*((unsigned int *)((unsigned long)context_ptr+0x000061f8+4*11))=0x933113e9;
*((unsigned int *)((unsigned long)context_ptr+0x000061f8+4*12))=0xb035aa60;
*((unsigned int *)((unsigned long)context_ptr+0x000061f8+4*13))=0x9d6d5a13;
*((unsigned int *)((unsigned long)context_ptr+0x00003528))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003528+4*1))=0x000064e8;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000528+4*1))=0x000061f8;
*((unsigned int *)((unsigned long)context_ptr+0x00000528+4*2))=0x00006408;
*((unsigned int *)((unsigned long)context_ptr+0x00000528+4*3))=0x02220038;
*((unsigned int *)((unsigned long)context_ptr+0x00000528+4*4))=0x01d77c03;
*((unsigned int *)((unsigned long)context_ptr+0x00000528+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000000fc&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006270,"\xc8\x72\x49\x99\xd9\xaa\xec\xd8\x5c\xfc\x08\x55\x00\xd7\x28\xf6\x5a\x76\x59\xa1\x45\xbf\xbd\xca\x72\x26\x0a\x48\x7e\x97\x8e\xdc",32))
printf("strip: c8724999d9aaecd8, Pass\n");
else
printf("strip: c8724999d9aaecd8, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006418))=0x018a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006418+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006418+4*2))=0x02020039;
*((unsigned int *)((unsigned long)context_ptr+0x00006418+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x00006230))=0x50520ad7;
*((unsigned int *)((unsigned long)context_ptr+0x00006230+4*1))=0x7dfd5329;
*((unsigned int *)((unsigned long)context_ptr+0x00006230+4*2))=0xebfcc912;
*((unsigned int *)((unsigned long)context_ptr+0x00006230+4*3))=0x92d2679c;
*((unsigned int *)((unsigned long)context_ptr+0x00006230+4*4))=0xb279aa2d;
*((unsigned int *)((unsigned long)context_ptr+0x00006230+4*5))=0x4a4d4a34;
*((unsigned int *)((unsigned long)context_ptr+0x00006230+4*6))=0x03aa59b4;
*((unsigned int *)((unsigned long)context_ptr+0x00006230+4*7))=0x0cea7706;
*((unsigned int *)((unsigned long)context_ptr+0x00006230+4*8))=0x124fff15;
*((unsigned int *)((unsigned long)context_ptr+0x00006230+4*9))=0x96391410;
*((unsigned int *)((unsigned long)context_ptr+0x00006230+4*10))=0x55f1d708;
*((unsigned int *)((unsigned long)context_ptr+0x00006230+4*11))=0xd4069bd4;
*((unsigned int *)((unsigned long)context_ptr+0x00006230+4*12))=0x67babbf9;
*((unsigned int *)((unsigned long)context_ptr+0x00006230+4*13))=0xd45b06da;
*((unsigned int *)((unsigned long)context_ptr+0x00006230+4*14))=0x0000002b;
*((unsigned int *)((unsigned long)context_ptr+0x00003540))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003540+4*1))=0x0000626c;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000540+4*1))=0x00006230;
*((unsigned int *)((unsigned long)context_ptr+0x00000540+4*2))=0x00006418;
*((unsigned int *)((unsigned long)context_ptr+0x00000540+4*3))=0x02220039;
*((unsigned int *)((unsigned long)context_ptr+0x00000540+4*4))=0x00779c44;
*((unsigned int *)((unsigned long)context_ptr+0x00000540+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000102&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006508,"\x35\xad\xf1\x31\xdd\x8b\x31\x4b\x51\xcf\xdb\xc9\x5e\xfc\x9a\x2a\x35\xfb\xb6\x80\x8f\xc5\xd1\x71\xa6\xa3\xae\x9e\x71\x3a\x54\x1e",32))
printf("strip: 35adf131dd8b314b, Pass\n");
else
printf("strip: 35adf131dd8b314b, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006508))=0x018a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006508+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006508+4*2))=0x0202003a;
*((unsigned int *)((unsigned long)context_ptr+0x00006508+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x0000628c))=0x9758f762;
*((unsigned int *)((unsigned long)context_ptr+0x0000628c+4*1))=0x5f3b6a74;
*((unsigned int *)((unsigned long)context_ptr+0x0000628c+4*2))=0xf4ff74d4;
*((unsigned int *)((unsigned long)context_ptr+0x0000628c+4*3))=0x09b42142;
*((unsigned int *)((unsigned long)context_ptr+0x0000628c+4*4))=0x753c4a32;
*((unsigned int *)((unsigned long)context_ptr+0x0000628c+4*5))=0x2e527cf3;
*((unsigned int *)((unsigned long)context_ptr+0x0000628c+4*6))=0x89380080;
*((unsigned int *)((unsigned long)context_ptr+0x0000628c+4*7))=0x4f555fdd;
*((unsigned int *)((unsigned long)context_ptr+0x0000628c+4*8))=0xace683dd;
*((unsigned int *)((unsigned long)context_ptr+0x0000628c+4*9))=0x0e156341;
*((unsigned int *)((unsigned long)context_ptr+0x0000628c+4*10))=0x3ad295ed;
*((unsigned int *)((unsigned long)context_ptr+0x0000628c+4*11))=0xd0208a8f;
*((unsigned int *)((unsigned long)context_ptr+0x0000628c+4*12))=0x952cebf0;
*((unsigned int *)((unsigned long)context_ptr+0x0000628c+4*13))=0xe27ffdf0;
*((unsigned int *)((unsigned long)context_ptr+0x0000628c+4*14))=0x0000e0dc;
*((unsigned int *)((unsigned long)context_ptr+0x00003558))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003558+4*1))=0x000065e0;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000558+4*1))=0x0000628c;
*((unsigned int *)((unsigned long)context_ptr+0x00000558+4*2))=0x00006508;
*((unsigned int *)((unsigned long)context_ptr+0x00000558+4*3))=0x0222003a;
*((unsigned int *)((unsigned long)context_ptr+0x00000558+4*4))=0x0ae4d75a;
*((unsigned int *)((unsigned long)context_ptr+0x00000558+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000108&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000062f8,"\x3e\x5b\xc3\x94\xa4\x0b\xaa\xee\xdd\xab\xc6\x32\xee\x3c\x66\x4f\x33\x8a\x34\xdb\xd7\x3a\x64\xc7\xd2\xa8\xad\x19\x84\xcc\xe2\x41",32))
printf("strip: 3e5bc394a40baaee, Pass\n");
else
printf("strip: 3e5bc394a40baaee, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006518))=0x018a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006518+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006518+4*2))=0x0202003b;
*((unsigned int *)((unsigned long)context_ptr+0x00006518+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x000062c8))=0xf0b38bd2;
*((unsigned int *)((unsigned long)context_ptr+0x000062c8+4*1))=0x9fcaba1e;
*((unsigned int *)((unsigned long)context_ptr+0x000062c8+4*2))=0x261850bb;
*((unsigned int *)((unsigned long)context_ptr+0x000062c8+4*3))=0x752e7ed5;
*((unsigned int *)((unsigned long)context_ptr+0x000062c8+4*4))=0x2f067b86;
*((unsigned int *)((unsigned long)context_ptr+0x000062c8+4*5))=0x4fc65799;
*((unsigned int *)((unsigned long)context_ptr+0x000062c8+4*6))=0x4d5290c9;
*((unsigned int *)((unsigned long)context_ptr+0x000062c8+4*7))=0xebc71267;
*((unsigned int *)((unsigned long)context_ptr+0x000062c8+4*8))=0x18c996a3;
*((unsigned int *)((unsigned long)context_ptr+0x000062c8+4*9))=0x9027afbf;
*((unsigned int *)((unsigned long)context_ptr+0x000062c8+4*10))=0x1a143dcd;
*((unsigned int *)((unsigned long)context_ptr+0x000062c8+4*11))=0x7ad5624e;
*((unsigned int *)((unsigned long)context_ptr+0x000062c8+4*12))=0xf9b33cc3;
*((unsigned int *)((unsigned long)context_ptr+0x000062c8+4*13))=0x130edc69;
*((unsigned int *)((unsigned long)context_ptr+0x000062c8+4*14))=0x00d4dc0a;
*((unsigned int *)((unsigned long)context_ptr+0x00003570))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003570+4*1))=0x00006600;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000570+4*1))=0x000062c8;
*((unsigned int *)((unsigned long)context_ptr+0x00000570+4*2))=0x00006518;
*((unsigned int *)((unsigned long)context_ptr+0x00000570+4*3))=0x0222003b;
*((unsigned int *)((unsigned long)context_ptr+0x00000570+4*4))=0x04d5d9fc;
*((unsigned int *)((unsigned long)context_ptr+0x00000570+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000010e&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006528,"\xa8\x3c\xad\x40\x60\x10\x92\x42\x1f\x3e\xdb\xa4\x47\xd5\xde\x39\xc8\x42\x43\x3f\x28\xd6\xef\xf9\x73\x32\x5d\xcd\x1b\xa2\xcd\xa2",32))
printf("strip: a83cad4060109242, Pass\n");
else
printf("strip: a83cad4060109242, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006304))=0x018a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006304+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006304+4*2))=0x0202003c;
*((unsigned int *)((unsigned long)context_ptr+0x00006304+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x00006620))=0x5a5f2bcd;
*((unsigned int *)((unsigned long)context_ptr+0x00006620+4*1))=0xa6c1a82b;
*((unsigned int *)((unsigned long)context_ptr+0x00006620+4*2))=0x7f6a17bc;
*((unsigned int *)((unsigned long)context_ptr+0x00006620+4*3))=0x868a74f7;
*((unsigned int *)((unsigned long)context_ptr+0x00006620+4*4))=0xeee4002d;
*((unsigned int *)((unsigned long)context_ptr+0x00006620+4*5))=0x92e12704;
*((unsigned int *)((unsigned long)context_ptr+0x00006620+4*6))=0x42cd8515;
*((unsigned int *)((unsigned long)context_ptr+0x00006620+4*7))=0x0164bc6c;
*((unsigned int *)((unsigned long)context_ptr+0x00006620+4*8))=0x6ab08d48;
*((unsigned int *)((unsigned long)context_ptr+0x00006620+4*9))=0xddf9b451;
*((unsigned int *)((unsigned long)context_ptr+0x00006620+4*10))=0x35a9207e;
*((unsigned int *)((unsigned long)context_ptr+0x00006620+4*11))=0xb639a03a;
*((unsigned int *)((unsigned long)context_ptr+0x00006620+4*12))=0x76cd6e81;
*((unsigned int *)((unsigned long)context_ptr+0x00006620+4*13))=0xe4be9eb8;
*((unsigned int *)((unsigned long)context_ptr+0x00006620+4*14))=0x3701ad36;
*((unsigned int *)((unsigned long)context_ptr+0x00003588))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003588+4*1))=0x00006428;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000588+4*1))=0x00006620;
*((unsigned int *)((unsigned long)context_ptr+0x00000588+4*2))=0x00006304;
*((unsigned int *)((unsigned long)context_ptr+0x00000588+4*3))=0x0222003c;
*((unsigned int *)((unsigned long)context_ptr+0x00000588+4*4))=0x037a4b9b;
*((unsigned int *)((unsigned long)context_ptr+0x00000588+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000114&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006448,"\x3e\xbb\xfd\x54\xad\xbf\x62\xa2\x0c\xfd\xe6\xa5\x02\xe4\x92\x62\xb9\x67\xe0\xff\x7e\x72\x50\x53\x54\x08\xca\x68\x47\x4f\xe8\x9e",32))
printf("strip: 3ebbfd54adbf62a2, Pass\n");
else
printf("strip: 3ebbfd54adbf62a2, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006448))=0x018a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006448+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006448+4*2))=0x0202003d;
*((unsigned int *)((unsigned long)context_ptr+0x00006448+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x00006314))=0xf1406791;
*((unsigned int *)((unsigned long)context_ptr+0x00006314+4*1))=0xa249a296;
*((unsigned int *)((unsigned long)context_ptr+0x00006314+4*2))=0x418a948d;
*((unsigned int *)((unsigned long)context_ptr+0x00006314+4*3))=0x4d4f14a7;
*((unsigned int *)((unsigned long)context_ptr+0x00006314+4*4))=0xda34006f;
*((unsigned int *)((unsigned long)context_ptr+0x00006314+4*5))=0x839b03ca;
*((unsigned int *)((unsigned long)context_ptr+0x00006314+4*6))=0x615cbd18;
*((unsigned int *)((unsigned long)context_ptr+0x00006314+4*7))=0xd7d59b5d;
*((unsigned int *)((unsigned long)context_ptr+0x00006314+4*8))=0x9f0fe550;
*((unsigned int *)((unsigned long)context_ptr+0x00006314+4*9))=0x6a6af4b3;
*((unsigned int *)((unsigned long)context_ptr+0x00006314+4*10))=0x59f757a0;
*((unsigned int *)((unsigned long)context_ptr+0x00006314+4*11))=0xff415625;
*((unsigned int *)((unsigned long)context_ptr+0x00006314+4*12))=0x4846bbe3;
*((unsigned int *)((unsigned long)context_ptr+0x00006314+4*13))=0x1a389526;
*((unsigned int *)((unsigned long)context_ptr+0x00006314+4*14))=0x21a044e6;
*((unsigned int *)((unsigned long)context_ptr+0x00006314+4*15))=0x00000048;
*((unsigned int *)((unsigned long)context_ptr+0x000035a0))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x000035a0+4*1))=0x00006528;
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
*((unsigned int *)((unsigned long)context_ptr+0x000005a0+4*1))=0x00006314;
*((unsigned int *)((unsigned long)context_ptr+0x000005a0+4*2))=0x00006448;
*((unsigned int *)((unsigned long)context_ptr+0x000005a0+4*3))=0x0222003d;
*((unsigned int *)((unsigned long)context_ptr+0x000005a0+4*4))=0x00268416;
*((unsigned int *)((unsigned long)context_ptr+0x000005a0+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000011a&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006038,"\x97\xf7\x60\x24\x08\xd1\x3c\x59\x7e\x32\x02\x5a\x91\x6f\xe4\x32\x8e\x8f\x69\x33\x3f\x7f\xa8\x2b\xb0\x54\xbc\xc0\xbb\x66\x28\xb5",32))
printf("strip: 97f7602408d13c59, Pass\n");
else
printf("strip: 97f7602408d13c59, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006458))=0x018a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006458+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006458+4*2))=0x0202003e;
*((unsigned int *)((unsigned long)context_ptr+0x00006458+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x0000665c))=0xc42deca4;
*((unsigned int *)((unsigned long)context_ptr+0x0000665c+4*1))=0x548f69ef;
*((unsigned int *)((unsigned long)context_ptr+0x0000665c+4*2))=0x643e55ee;
*((unsigned int *)((unsigned long)context_ptr+0x0000665c+4*3))=0xb6182818;
*((unsigned int *)((unsigned long)context_ptr+0x0000665c+4*4))=0x4cb00955;
*((unsigned int *)((unsigned long)context_ptr+0x0000665c+4*5))=0xee95eacf;
*((unsigned int *)((unsigned long)context_ptr+0x0000665c+4*6))=0x05b664ec;
*((unsigned int *)((unsigned long)context_ptr+0x0000665c+4*7))=0x4c91f7a1;
*((unsigned int *)((unsigned long)context_ptr+0x0000665c+4*8))=0x724b618a;
*((unsigned int *)((unsigned long)context_ptr+0x0000665c+4*9))=0x043d7939;
*((unsigned int *)((unsigned long)context_ptr+0x0000665c+4*10))=0x0a4c6c05;
*((unsigned int *)((unsigned long)context_ptr+0x0000665c+4*11))=0xd24e19d1;
*((unsigned int *)((unsigned long)context_ptr+0x0000665c+4*12))=0x42c46dbc;
*((unsigned int *)((unsigned long)context_ptr+0x0000665c+4*13))=0xcd4fcf6b;
*((unsigned int *)((unsigned long)context_ptr+0x0000665c+4*14))=0x742db46f;
*((unsigned int *)((unsigned long)context_ptr+0x0000665c+4*15))=0x00009022;
*((unsigned int *)((unsigned long)context_ptr+0x000035b8))=0x04c00020;
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
*((unsigned int *)((unsigned long)context_ptr+0x000005b8+4*1))=0x0000665c;
*((unsigned int *)((unsigned long)context_ptr+0x000005b8+4*2))=0x00006458;
*((unsigned int *)((unsigned long)context_ptr+0x000005b8+4*3))=0x0222003e;
*((unsigned int *)((unsigned long)context_ptr+0x000005b8+4*4))=0x0ec319b1;
*((unsigned int *)((unsigned long)context_ptr+0x000005b8+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000120&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006388,"\x4c\x99\x99\x1b\x66\xda\xca\xc9\x97\x20\x7a\x1f\x82\x44\xc9\x3f\x03\x7a\x7a\xf6\x36\xc2\x59\x4b\x98\x5a\xb3\xa6\x87\x73\xed\x7d",32))
printf("strip: 4c99991b66dacac9, Pass\n");
else
printf("strip: 4c99991b66dacac9, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006018))=0x018a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006018+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006018+4*2))=0x0202003f;
*((unsigned int *)((unsigned long)context_ptr+0x00006018+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x00006354))=0x15aabc08;
*((unsigned int *)((unsigned long)context_ptr+0x00006354+4*1))=0xe8bec521;
*((unsigned int *)((unsigned long)context_ptr+0x00006354+4*2))=0x79f43459;
*((unsigned int *)((unsigned long)context_ptr+0x00006354+4*3))=0x39ce1791;
*((unsigned int *)((unsigned long)context_ptr+0x00006354+4*4))=0x9a2876f3;
*((unsigned int *)((unsigned long)context_ptr+0x00006354+4*5))=0x817c1c3f;
*((unsigned int *)((unsigned long)context_ptr+0x00006354+4*6))=0xd337e6b6;
*((unsigned int *)((unsigned long)context_ptr+0x00006354+4*7))=0x62c02074;
*((unsigned int *)((unsigned long)context_ptr+0x00006354+4*8))=0x943f008f;
*((unsigned int *)((unsigned long)context_ptr+0x00006354+4*9))=0x38862107;
*((unsigned int *)((unsigned long)context_ptr+0x00006354+4*10))=0x5f2ae4b4;
*((unsigned int *)((unsigned long)context_ptr+0x00006354+4*11))=0x24b6f012;
*((unsigned int *)((unsigned long)context_ptr+0x00006354+4*12))=0x284c9d3b;
*((unsigned int *)((unsigned long)context_ptr+0x00006354+4*13))=0x65b346d5;
*((unsigned int *)((unsigned long)context_ptr+0x00006354+4*14))=0x69b4dd3d;
*((unsigned int *)((unsigned long)context_ptr+0x00006354+4*15))=0x00f923a0;
*((unsigned int *)((unsigned long)context_ptr+0x000035d0))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x000035d0+4*1))=0x00006548;
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
*((unsigned int *)((unsigned long)context_ptr+0x000005d0+4*1))=0x00006354;
*((unsigned int *)((unsigned long)context_ptr+0x000005d0+4*2))=0x00006018;
*((unsigned int *)((unsigned long)context_ptr+0x000005d0+4*3))=0x0222003f;
*((unsigned int *)((unsigned long)context_ptr+0x000005d0+4*4))=0x034cb41e;
*((unsigned int *)((unsigned long)context_ptr+0x000005d0+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000126&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006468,"\xad\x53\xd0\xc9\xd6\xb3\x82\x27\x63\xe0\x91\x97\xa2\x3d\x10\x46\xc1\xda\xfc\xe7\xbe\x1e\x71\x42\x63\xf8\x52\x75\x6a\xaf\x7d\x85",32))
printf("strip: ad53d0c9d6b38227, Pass\n");
else
printf("strip: ad53d0c9d6b38227, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006008))=0x018a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006008+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006008+4*2))=0x02020040;
*((unsigned int *)((unsigned long)context_ptr+0x00006008+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x00006568))=0xfbff9001;
*((unsigned int *)((unsigned long)context_ptr+0x00006568+4*1))=0xd12fbc3e;
*((unsigned int *)((unsigned long)context_ptr+0x00006568+4*2))=0xd4afd19d;
*((unsigned int *)((unsigned long)context_ptr+0x00006568+4*3))=0x1f2f4523;
*((unsigned int *)((unsigned long)context_ptr+0x00006568+4*4))=0x58731538;
*((unsigned int *)((unsigned long)context_ptr+0x00006568+4*5))=0x0bb33202;
*((unsigned int *)((unsigned long)context_ptr+0x00006568+4*6))=0x09eadb04;
*((unsigned int *)((unsigned long)context_ptr+0x00006568+4*7))=0xa0945b42;
*((unsigned int *)((unsigned long)context_ptr+0x00006568+4*8))=0x606645f6;
*((unsigned int *)((unsigned long)context_ptr+0x00006568+4*9))=0xa9e831d6;
*((unsigned int *)((unsigned long)context_ptr+0x00006568+4*10))=0x0b32b87d;
*((unsigned int *)((unsigned long)context_ptr+0x00006568+4*11))=0x9fdf5bdd;
*((unsigned int *)((unsigned long)context_ptr+0x00006568+4*12))=0x624de195;
*((unsigned int *)((unsigned long)context_ptr+0x00006568+4*13))=0xebc9e8d8;
*((unsigned int *)((unsigned long)context_ptr+0x00006568+4*14))=0xe2d92c8c;
*((unsigned int *)((unsigned long)context_ptr+0x00006568+4*15))=0xed04aa4d;
*((unsigned int *)((unsigned long)context_ptr+0x000035e8))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x000035e8+4*1))=0x00006468;
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
*((unsigned int *)((unsigned long)context_ptr+0x000005e8+4*1))=0x00006568;
*((unsigned int *)((unsigned long)context_ptr+0x000005e8+4*2))=0x00006008;
*((unsigned int *)((unsigned long)context_ptr+0x000005e8+4*3))=0x02220040;
*((unsigned int *)((unsigned long)context_ptr+0x000005e8+4*4))=0x0af22cc6;
*((unsigned int *)((unsigned long)context_ptr+0x000005e8+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000012c&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006488,"\x70\xe6\x77\x01\xde\x2c\xf0\xbb\x93\xf0\x59\x4e\x7b\x40\x90\x1b\x1a\xcc\x28\xd0\xff\x10\x6c\x49\x99\x34\x36\xbe\xa7\x39\x98\xe1",32))
printf("strip: 70e67701de2cf0bb, Pass\n");
else
printf("strip: 70e67701de2cf0bb, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006028))=0x018a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006028+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006028+4*2))=0x02020041;
*((unsigned int *)((unsigned long)context_ptr+0x00006028+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x00006058))=0x4e96c258;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*1))=0xb388352c;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*2))=0xa2b4c7f1;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*3))=0x66c89cff;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*4))=0x82ca5d23;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*5))=0xbf5c357e;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*6))=0xeef52c6a;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*7))=0x12fc7ddc;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*8))=0x8f5808a7;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*9))=0xe2ef6f7b;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*10))=0xa933c7e3;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*11))=0x9858e35e;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*12))=0x5b1f54d3;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*13))=0xdcfa5945;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*14))=0xee81d795;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*15))=0x1c90e640;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*16))=0x00000079;
*((unsigned int *)((unsigned long)context_ptr+0x00003600))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003600+4*1))=0x00006488;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000600+4*1))=0x00006058;
*((unsigned int *)((unsigned long)context_ptr+0x00000600+4*2))=0x00006028;
*((unsigned int *)((unsigned long)context_ptr+0x00000600+4*3))=0x02220041;
*((unsigned int *)((unsigned long)context_ptr+0x00000600+4*4))=0x0c974a4a;
*((unsigned int *)((unsigned long)context_ptr+0x00000600+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000132&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000060f4,"\x79\x9d\x70\x45\xf1\xec\x3a\xb0\x0d\xe2\xfa\x7a\x67\xb4\xc8\x0e\x34\x4b\xa9\x81\xff\x52\x8e\x99\xbe\xeb\x7f\xfd\x0a\x9b\x93\xc6",32))
printf("strip: 799d7045f1ec3ab0, Pass\n");
else
printf("strip: 799d7045f1ec3ab0, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006394))=0x018a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006394+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006394+4*2))=0x02020042;
*((unsigned int *)((unsigned long)context_ptr+0x00006394+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x0000609c))=0x833a8bd8;
*((unsigned int *)((unsigned long)context_ptr+0x0000609c+4*1))=0x662e5d05;
*((unsigned int *)((unsigned long)context_ptr+0x0000609c+4*2))=0xceb0ab0f;
*((unsigned int *)((unsigned long)context_ptr+0x0000609c+4*3))=0xfb251f98;
*((unsigned int *)((unsigned long)context_ptr+0x0000609c+4*4))=0x527ca9b2;
*((unsigned int *)((unsigned long)context_ptr+0x0000609c+4*5))=0x583ff0d9;
*((unsigned int *)((unsigned long)context_ptr+0x0000609c+4*6))=0xbe93fc51;
*((unsigned int *)((unsigned long)context_ptr+0x0000609c+4*7))=0xd0be5355;
*((unsigned int *)((unsigned long)context_ptr+0x0000609c+4*8))=0x4da6e024;
*((unsigned int *)((unsigned long)context_ptr+0x0000609c+4*9))=0x7085f232;
*((unsigned int *)((unsigned long)context_ptr+0x0000609c+4*10))=0xe902a94e;
*((unsigned int *)((unsigned long)context_ptr+0x0000609c+4*11))=0x990f009d;
*((unsigned int *)((unsigned long)context_ptr+0x0000609c+4*12))=0xc9df543d;
*((unsigned int *)((unsigned long)context_ptr+0x0000609c+4*13))=0x4794e083;
*((unsigned int *)((unsigned long)context_ptr+0x0000609c+4*14))=0xe5110ff9;
*((unsigned int *)((unsigned long)context_ptr+0x0000609c+4*15))=0xbbcbe08d;
*((unsigned int *)((unsigned long)context_ptr+0x0000609c+4*16))=0x000058f4;
*((unsigned int *)((unsigned long)context_ptr+0x00003618))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003618+4*1))=0x000063a4;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000618+4*1))=0x0000609c;
*((unsigned int *)((unsigned long)context_ptr+0x00000618+4*2))=0x00006394;
*((unsigned int *)((unsigned long)context_ptr+0x00000618+4*3))=0x02220042;
*((unsigned int *)((unsigned long)context_ptr+0x00000618+4*4))=0x03ef8aea;
*((unsigned int *)((unsigned long)context_ptr+0x00000618+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000138&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000064a8,"\xee\x69\x24\x6d\xa8\x8d\x71\xf1\x09\xb7\x95\xdb\xf3\x71\x60\x47\x85\xaf\xc0\xbd\xdd\x36\x11\x4b\x10\xcb\xda\x25\xb8\x41\xc0\x9d",32))
printf("strip: ee69246da88d71f1, Pass\n");
else
printf("strip: ee69246da88d71f1, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000063c4))=0x018a0012;
*((unsigned int *)((unsigned long)context_ptr+0x000063c4+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000063c4+4*2))=0x02020043;
*((unsigned int *)((unsigned long)context_ptr+0x000063c4+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x000060e0))=0xf5859c63;
*((unsigned int *)((unsigned long)context_ptr+0x000060e0+4*1))=0x4b044d78;
*((unsigned int *)((unsigned long)context_ptr+0x000060e0+4*2))=0x7b92fed5;
*((unsigned int *)((unsigned long)context_ptr+0x000060e0+4*3))=0xcf595462;
*((unsigned int *)((unsigned long)context_ptr+0x000060e0+4*4))=0xe1249358;
*((unsigned int *)((unsigned long)context_ptr+0x000060e0+4*5))=0x2a40754e;
*((unsigned int *)((unsigned long)context_ptr+0x000060e0+4*6))=0x0aedb4f0;
*((unsigned int *)((unsigned long)context_ptr+0x000060e0+4*7))=0xb7f6998d;
*((unsigned int *)((unsigned long)context_ptr+0x000060e0+4*8))=0x97e544a2;
*((unsigned int *)((unsigned long)context_ptr+0x000060e0+4*9))=0x19dca300;
*((unsigned int *)((unsigned long)context_ptr+0x000060e0+4*10))=0x630a8b31;
*((unsigned int *)((unsigned long)context_ptr+0x000060e0+4*11))=0x19d93e93;
*((unsigned int *)((unsigned long)context_ptr+0x000060e0+4*12))=0xa7d535cd;
*((unsigned int *)((unsigned long)context_ptr+0x000060e0+4*13))=0x29d285be;
*((unsigned int *)((unsigned long)context_ptr+0x000060e0+4*14))=0x154004c0;
*((unsigned int *)((unsigned long)context_ptr+0x000060e0+4*15))=0x0ae14673;
*((unsigned int *)((unsigned long)context_ptr+0x000060e0+4*16))=0x009ee0c3;
*((unsigned int *)((unsigned long)context_ptr+0x00003630))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003630+4*1))=0x000064a8;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000630+4*1))=0x000060e0;
*((unsigned int *)((unsigned long)context_ptr+0x00000630+4*2))=0x000063c4;
*((unsigned int *)((unsigned long)context_ptr+0x00000630+4*3))=0x02220043;
*((unsigned int *)((unsigned long)context_ptr+0x00000630+4*4))=0x0160b3fe;
*((unsigned int *)((unsigned long)context_ptr+0x00000630+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000013e&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006180,"\xbf\x95\x4a\x63\xda\x7a\x0a\xbf\x06\x28\x25\x9a\xaa\x3d\x6a\x50\x00\xd4\xd4\x43\x3c\x6b\x34\x74\xb6\x5c\x12\xd6\x29\xd1\x71\x6f",32))
printf("strip: bf954a63da7a0abf, Pass\n");
else
printf("strip: bf954a63da7a0abf, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000063d4))=0x018a0012;
*((unsigned int *)((unsigned long)context_ptr+0x000063d4+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000063d4+4*2))=0x02020044;
*((unsigned int *)((unsigned long)context_ptr+0x000063d4+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x00006124))=0xbbc8ceb4;
*((unsigned int *)((unsigned long)context_ptr+0x00006124+4*1))=0x667602b1;
*((unsigned int *)((unsigned long)context_ptr+0x00006124+4*2))=0xba70c4c8;
*((unsigned int *)((unsigned long)context_ptr+0x00006124+4*3))=0x7612dc2c;
*((unsigned int *)((unsigned long)context_ptr+0x00006124+4*4))=0x1e62d653;
*((unsigned int *)((unsigned long)context_ptr+0x00006124+4*5))=0xbae92eaf;
*((unsigned int *)((unsigned long)context_ptr+0x00006124+4*6))=0x69f44fbd;
*((unsigned int *)((unsigned long)context_ptr+0x00006124+4*7))=0xefd3a744;
*((unsigned int *)((unsigned long)context_ptr+0x00006124+4*8))=0xed16bd6a;
*((unsigned int *)((unsigned long)context_ptr+0x00006124+4*9))=0x634b8a02;
*((unsigned int *)((unsigned long)context_ptr+0x00006124+4*10))=0x7ace7e71;
*((unsigned int *)((unsigned long)context_ptr+0x00006124+4*11))=0xd25c0681;
*((unsigned int *)((unsigned long)context_ptr+0x00006124+4*12))=0x476ee04e;
*((unsigned int *)((unsigned long)context_ptr+0x00006124+4*13))=0x349c3d20;
*((unsigned int *)((unsigned long)context_ptr+0x00006124+4*14))=0xf47eddf9;
*((unsigned int *)((unsigned long)context_ptr+0x00006124+4*15))=0x0b78a80e;
*((unsigned int *)((unsigned long)context_ptr+0x00006124+4*16))=0x3aaf9eb2;
*((unsigned int *)((unsigned long)context_ptr+0x00003648))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003648+4*1))=0x00006168;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000648+4*1))=0x00006124;
*((unsigned int *)((unsigned long)context_ptr+0x00000648+4*2))=0x000063d4;
*((unsigned int *)((unsigned long)context_ptr+0x00000648+4*3))=0x02220044;
*((unsigned int *)((unsigned long)context_ptr+0x00000648+4*4))=0x06c91062;
*((unsigned int *)((unsigned long)context_ptr+0x00000648+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000144&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000064c8,"\xd3\x99\x00\x27\xec\x9b\xeb\xa4\x8e\xd9\xa3\x7c\xd6\xc5\x8c\x0a\x7c\xa0\x6d\x2e\x42\x44\x34\x18\x69\xfd\x39\x25\x4a\xbd\xd1\xfe",32))
printf("strip: d3990027ec9beba4, Pass\n");
else
printf("strip: d3990027ec9beba4, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000063e4))=0x018a0012;
*((unsigned int *)((unsigned long)context_ptr+0x000063e4+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000063e4+4*2))=0x02020045;
*((unsigned int *)((unsigned long)context_ptr+0x000063e4+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x0000669c))=0x538b0007;
*((unsigned int *)((unsigned long)context_ptr+0x0000669c+4*1))=0x12780b10;
*((unsigned int *)((unsigned long)context_ptr+0x0000669c+4*2))=0x074fbe33;
*((unsigned int *)((unsigned long)context_ptr+0x0000669c+4*3))=0xc2a3eef5;
*((unsigned int *)((unsigned long)context_ptr+0x0000669c+4*4))=0xf9a058ed;
*((unsigned int *)((unsigned long)context_ptr+0x0000669c+4*5))=0xea73dc0f;
*((unsigned int *)((unsigned long)context_ptr+0x0000669c+4*6))=0xee840b60;
*((unsigned int *)((unsigned long)context_ptr+0x0000669c+4*7))=0x8dad3d8d;
*((unsigned int *)((unsigned long)context_ptr+0x0000669c+4*8))=0x02383d8d;
*((unsigned int *)((unsigned long)context_ptr+0x0000669c+4*9))=0x73e6c0f8;
*((unsigned int *)((unsigned long)context_ptr+0x0000669c+4*10))=0xdff9793c;
*((unsigned int *)((unsigned long)context_ptr+0x0000669c+4*11))=0x926eadba;
*((unsigned int *)((unsigned long)context_ptr+0x0000669c+4*12))=0xbb113dc2;
*((unsigned int *)((unsigned long)context_ptr+0x0000669c+4*13))=0xb549a97b;
*((unsigned int *)((unsigned long)context_ptr+0x0000669c+4*14))=0xd0019add;
*((unsigned int *)((unsigned long)context_ptr+0x0000669c+4*15))=0x65167739;
*((unsigned int *)((unsigned long)context_ptr+0x0000669c+4*16))=0x73b67fe4;
*((unsigned int *)((unsigned long)context_ptr+0x0000669c+4*17))=0x0000007e;
*((unsigned int *)((unsigned long)context_ptr+0x00003660))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003660+4*1))=0x000064c8;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000660+4*1))=0x0000669c;
*((unsigned int *)((unsigned long)context_ptr+0x00000660+4*2))=0x000063e4;
*((unsigned int *)((unsigned long)context_ptr+0x00000660+4*3))=0x02220045;
*((unsigned int *)((unsigned long)context_ptr+0x00000660+4*4))=0x033cb1b2;
*((unsigned int *)((unsigned long)context_ptr+0x00000660+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000014a&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000061d8,"\x0b\x11\xef\x32\x3e\xb6\x82\x6e\x96\x4c\x5f\x70\x05\x31\x6f\xdc\xb5\xfb\x50\xe8\xd5\x07\xa0\xf5\x59\xfb\x1c\xb0\x83\x99\xc1\xe1",32))
printf("strip: 0b11ef323eb6826e, Pass\n");
else
printf("strip: 0b11ef323eb6826e, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000063f4))=0x018a0012;
*((unsigned int *)((unsigned long)context_ptr+0x000063f4+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000063f4+4*2))=0x02020046;
*((unsigned int *)((unsigned long)context_ptr+0x000063f4+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x00006188))=0x1698467f;
*((unsigned int *)((unsigned long)context_ptr+0x00006188+4*1))=0x1bd94104;
*((unsigned int *)((unsigned long)context_ptr+0x00006188+4*2))=0x3a93bf88;
*((unsigned int *)((unsigned long)context_ptr+0x00006188+4*3))=0x5a1e697d;
*((unsigned int *)((unsigned long)context_ptr+0x00006188+4*4))=0xd9270cfd;
*((unsigned int *)((unsigned long)context_ptr+0x00006188+4*5))=0xddd81bda;
*((unsigned int *)((unsigned long)context_ptr+0x00006188+4*6))=0x067e2c7c;
*((unsigned int *)((unsigned long)context_ptr+0x00006188+4*7))=0x965431c5;
*((unsigned int *)((unsigned long)context_ptr+0x00006188+4*8))=0x97623da7;
*((unsigned int *)((unsigned long)context_ptr+0x00006188+4*9))=0xa685db44;
*((unsigned int *)((unsigned long)context_ptr+0x00006188+4*10))=0x43d414da;
*((unsigned int *)((unsigned long)context_ptr+0x00006188+4*11))=0xc06eae35;
*((unsigned int *)((unsigned long)context_ptr+0x00006188+4*12))=0xbd7aa017;
*((unsigned int *)((unsigned long)context_ptr+0x00006188+4*13))=0xfea61206;
*((unsigned int *)((unsigned long)context_ptr+0x00006188+4*14))=0xd00d401c;
*((unsigned int *)((unsigned long)context_ptr+0x00006188+4*15))=0x8860b71b;
*((unsigned int *)((unsigned long)context_ptr+0x00006188+4*16))=0x11d9355f;
*((unsigned int *)((unsigned long)context_ptr+0x00006188+4*17))=0x0000c860;
*((unsigned int *)((unsigned long)context_ptr+0x00003678))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003678+4*1))=0x000061d0;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000678+4*1))=0x00006188;
*((unsigned int *)((unsigned long)context_ptr+0x00000678+4*2))=0x000063f4;
*((unsigned int *)((unsigned long)context_ptr+0x00000678+4*3))=0x02220046;
*((unsigned int *)((unsigned long)context_ptr+0x00000678+4*4))=0x01ce06fa;
*((unsigned int *)((unsigned long)context_ptr+0x00000678+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000150&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000064e8,"\xa6\x88\x03\xf8\x34\x6a\x08\x31\x8c\x29\x2f\x98\x87\x4d\x88\x75\x35\x50\xd1\xf2\xf2\x74\x7f\xb2\x59\xdf\xcd\xd7\xf5\xe6\x60\x1b",32))
printf("strip: a68803f8346a0831, Pass\n");
else
printf("strip: a68803f8346a0831, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006404))=0x018a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006404+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006404+4*2))=0x02020047;
*((unsigned int *)((unsigned long)context_ptr+0x00006404+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x000066e4))=0x6f9caa59;
*((unsigned int *)((unsigned long)context_ptr+0x000066e4+4*1))=0xd2ef7b61;
*((unsigned int *)((unsigned long)context_ptr+0x000066e4+4*2))=0xfa66cd01;
*((unsigned int *)((unsigned long)context_ptr+0x000066e4+4*3))=0x447dd921;
*((unsigned int *)((unsigned long)context_ptr+0x000066e4+4*4))=0x6ac98fec;
*((unsigned int *)((unsigned long)context_ptr+0x000066e4+4*5))=0x2d6ae053;
*((unsigned int *)((unsigned long)context_ptr+0x000066e4+4*6))=0xace9bea7;
*((unsigned int *)((unsigned long)context_ptr+0x000066e4+4*7))=0xd1963151;
*((unsigned int *)((unsigned long)context_ptr+0x000066e4+4*8))=0x8fdac51b;
*((unsigned int *)((unsigned long)context_ptr+0x000066e4+4*9))=0x4cbefca0;
*((unsigned int *)((unsigned long)context_ptr+0x000066e4+4*10))=0xeb5c96cc;
*((unsigned int *)((unsigned long)context_ptr+0x000066e4+4*11))=0xe9f89756;
*((unsigned int *)((unsigned long)context_ptr+0x000066e4+4*12))=0xac3f59f3;
*((unsigned int *)((unsigned long)context_ptr+0x000066e4+4*13))=0xd553e233;
*((unsigned int *)((unsigned long)context_ptr+0x000066e4+4*14))=0x405ff1ef;
*((unsigned int *)((unsigned long)context_ptr+0x000066e4+4*15))=0x46fd06a1;
*((unsigned int *)((unsigned long)context_ptr+0x000066e4+4*16))=0xd7ed4670;
*((unsigned int *)((unsigned long)context_ptr+0x000066e4+4*17))=0x00f19889;
*((unsigned int *)((unsigned long)context_ptr+0x00003690))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003690+4*1))=0x000064e8;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000690+4*1))=0x000066e4;
*((unsigned int *)((unsigned long)context_ptr+0x00000690+4*2))=0x00006404;
*((unsigned int *)((unsigned long)context_ptr+0x00000690+4*3))=0x02220047;
*((unsigned int *)((unsigned long)context_ptr+0x00000690+4*4))=0x03e9a772;
*((unsigned int *)((unsigned long)context_ptr+0x00000690+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000156&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x0000626c,"\x6c\x70\x2b\xd6\x16\xa1\xe2\x71\x79\x5c\x4b\xc9\x56\x9b\x4c\xd0\x48\xfc\xba\xd5\x1b\x5a\xdc\xeb\x2f\x09\x87\x71\xeb\xe9\x5c\xc3",32))
printf("strip: 6c702bd616a1e271, Pass\n");
else
printf("strip: 6c702bd616a1e271, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006414))=0x018a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006414+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006414+4*2))=0x02020048;
*((unsigned int *)((unsigned long)context_ptr+0x00006414+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x000061f0))=0x7f25c75a;
*((unsigned int *)((unsigned long)context_ptr+0x000061f0+4*1))=0xaf532f7e;
*((unsigned int *)((unsigned long)context_ptr+0x000061f0+4*2))=0x7013d127;
*((unsigned int *)((unsigned long)context_ptr+0x000061f0+4*3))=0x72be6c88;
*((unsigned int *)((unsigned long)context_ptr+0x000061f0+4*4))=0x471bae89;
*((unsigned int *)((unsigned long)context_ptr+0x000061f0+4*5))=0x307fed94;
*((unsigned int *)((unsigned long)context_ptr+0x000061f0+4*6))=0x971f072f;
*((unsigned int *)((unsigned long)context_ptr+0x000061f0+4*7))=0x4c54281d;
*((unsigned int *)((unsigned long)context_ptr+0x000061f0+4*8))=0x578b1ce4;
*((unsigned int *)((unsigned long)context_ptr+0x000061f0+4*9))=0x5625e2a0;
*((unsigned int *)((unsigned long)context_ptr+0x000061f0+4*10))=0x01493fc5;
*((unsigned int *)((unsigned long)context_ptr+0x000061f0+4*11))=0xa39fc740;
*((unsigned int *)((unsigned long)context_ptr+0x000061f0+4*12))=0x06f4b435;
*((unsigned int *)((unsigned long)context_ptr+0x000061f0+4*13))=0xc9826773;
*((unsigned int *)((unsigned long)context_ptr+0x000061f0+4*14))=0xadabf9ba;
*((unsigned int *)((unsigned long)context_ptr+0x000061f0+4*15))=0x326d457b;
*((unsigned int *)((unsigned long)context_ptr+0x000061f0+4*16))=0x155914b8;
*((unsigned int *)((unsigned long)context_ptr+0x000061f0+4*17))=0x576adcb1;
*((unsigned int *)((unsigned long)context_ptr+0x000036a8))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x000036a8+4*1))=0x000065a8;
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
*((unsigned int *)((unsigned long)context_ptr+0x000006a8+4*1))=0x000061f0;
*((unsigned int *)((unsigned long)context_ptr+0x000006a8+4*2))=0x00006414;
*((unsigned int *)((unsigned long)context_ptr+0x000006a8+4*3))=0x02220048;
*((unsigned int *)((unsigned long)context_ptr+0x000006a8+4*4))=0x050bc0c0;
*((unsigned int *)((unsigned long)context_ptr+0x000006a8+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000015c&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000065e0,"\x5c\x35\x06\x91\xbb\xcc\x0d\x0c\xd5\x80\x56\x04\xe5\xed\x0f\x3b\x83\x3c\x77\x86\x2e\x1e\xee\x08\x45\x8f\xe9\x21\x2e\x46\xf0\xb8",32))
printf("strip: 5c350691bbcc0d0c, Pass\n");
else
printf("strip: 5c350691bbcc0d0c, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006508))=0x018a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006508+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006508+4*2))=0x02020049;
*((unsigned int *)((unsigned long)context_ptr+0x00006508+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x00006238))=0xee240e5f;
*((unsigned int *)((unsigned long)context_ptr+0x00006238+4*1))=0x0fcc1974;
*((unsigned int *)((unsigned long)context_ptr+0x00006238+4*2))=0x2cea613a;
*((unsigned int *)((unsigned long)context_ptr+0x00006238+4*3))=0xf05d82c3;
*((unsigned int *)((unsigned long)context_ptr+0x00006238+4*4))=0x7da91207;
*((unsigned int *)((unsigned long)context_ptr+0x00006238+4*5))=0x198b19bd;
*((unsigned int *)((unsigned long)context_ptr+0x00006238+4*6))=0x29a65c7b;
*((unsigned int *)((unsigned long)context_ptr+0x00006238+4*7))=0x7f34e986;
*((unsigned int *)((unsigned long)context_ptr+0x00006238+4*8))=0x770fe56d;
*((unsigned int *)((unsigned long)context_ptr+0x00006238+4*9))=0x127cfcfe;
*((unsigned int *)((unsigned long)context_ptr+0x00006238+4*10))=0xdf1be762;
*((unsigned int *)((unsigned long)context_ptr+0x00006238+4*11))=0x1f4d4cc3;
*((unsigned int *)((unsigned long)context_ptr+0x00006238+4*12))=0x61be6cb8;
*((unsigned int *)((unsigned long)context_ptr+0x00006238+4*13))=0x0413fd23;
*((unsigned int *)((unsigned long)context_ptr+0x00006238+4*14))=0x25153ab0;
*((unsigned int *)((unsigned long)context_ptr+0x00006238+4*15))=0x480d81ab;
*((unsigned int *)((unsigned long)context_ptr+0x00006238+4*16))=0xde9812c4;
*((unsigned int *)((unsigned long)context_ptr+0x00006238+4*17))=0xd08c8611;
*((unsigned int *)((unsigned long)context_ptr+0x00006238+4*18))=0x0000009d;
*((unsigned int *)((unsigned long)context_ptr+0x000036c0))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x000036c0+4*1))=0x000065c8;
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
*((unsigned int *)((unsigned long)context_ptr+0x000006c0+4*1))=0x00006238;
*((unsigned int *)((unsigned long)context_ptr+0x000006c0+4*2))=0x00006508;
*((unsigned int *)((unsigned long)context_ptr+0x000006c0+4*3))=0x02220049;
*((unsigned int *)((unsigned long)context_ptr+0x000006c0+4*4))=0x0106f4e7;
*((unsigned int *)((unsigned long)context_ptr+0x000006c0+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000162&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006600,"\xcc\xc9\x33\x67\x2f\x94\xc1\x87\x8a\x55\xf1\x47\x10\xd8\x2d\xfe\x93\x85\x12\x9d\x96\x50\xde\x3d\x27\xeb\xbc\x21\xe9\x61\xb7\xd6",32))
printf("strip: ccc933672f94c187, Pass\n");
else
printf("strip: ccc933672f94c187, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006518))=0x018a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006518+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006518+4*2))=0x0202004a;
*((unsigned int *)((unsigned long)context_ptr+0x00006518+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x00006284))=0xbeb3bdfc;
*((unsigned int *)((unsigned long)context_ptr+0x00006284+4*1))=0xbb21d69f;
*((unsigned int *)((unsigned long)context_ptr+0x00006284+4*2))=0xbfdb8e60;
*((unsigned int *)((unsigned long)context_ptr+0x00006284+4*3))=0x066cf5a7;
*((unsigned int *)((unsigned long)context_ptr+0x00006284+4*4))=0xd49b68f6;
*((unsigned int *)((unsigned long)context_ptr+0x00006284+4*5))=0xbb3236c8;
*((unsigned int *)((unsigned long)context_ptr+0x00006284+4*6))=0xadbba069;
*((unsigned int *)((unsigned long)context_ptr+0x00006284+4*7))=0xf4a154bc;
*((unsigned int *)((unsigned long)context_ptr+0x00006284+4*8))=0x475ffa00;
*((unsigned int *)((unsigned long)context_ptr+0x00006284+4*9))=0xb3383baf;
*((unsigned int *)((unsigned long)context_ptr+0x00006284+4*10))=0x04e2a696;
*((unsigned int *)((unsigned long)context_ptr+0x00006284+4*11))=0x67d64a65;
*((unsigned int *)((unsigned long)context_ptr+0x00006284+4*12))=0x1f959a5c;
*((unsigned int *)((unsigned long)context_ptr+0x00006284+4*13))=0x55c2efc9;
*((unsigned int *)((unsigned long)context_ptr+0x00006284+4*14))=0xdf2d1855;
*((unsigned int *)((unsigned long)context_ptr+0x00006284+4*15))=0xac2a7230;
*((unsigned int *)((unsigned long)context_ptr+0x00006284+4*16))=0x4e0ecc2f;
*((unsigned int *)((unsigned long)context_ptr+0x00006284+4*17))=0x9d538929;
*((unsigned int *)((unsigned long)context_ptr+0x00006284+4*18))=0x00005392;
*((unsigned int *)((unsigned long)context_ptr+0x000036d8))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x000036d8+4*1))=0x000062d0;
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
*((unsigned int *)((unsigned long)context_ptr+0x000006d8+4*1))=0x00006284;
*((unsigned int *)((unsigned long)context_ptr+0x000006d8+4*2))=0x00006518;
*((unsigned int *)((unsigned long)context_ptr+0x000006d8+4*3))=0x0222004a;
*((unsigned int *)((unsigned long)context_ptr+0x000006d8+4*4))=0x01d494ca;
*((unsigned int *)((unsigned long)context_ptr+0x000006d8+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000168&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006428,"\x60\x81\xdd\xcf\x59\xde\x87\x2f\xab\x7b\x68\x4c\x77\x5d\x3a\x48\xe8\x3d\x09\x14\xea\x05\x35\xa1\x0b\xef\x32\x27\xda\xc6\x3c\xdd",32))
printf("strip: 6081ddcf59de872f, Pass\n");
else
printf("strip: 6081ddcf59de872f, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000062f0))=0x018a0012;
*((unsigned int *)((unsigned long)context_ptr+0x000062f0+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000062f0+4*2))=0x0202004b;
*((unsigned int *)((unsigned long)context_ptr+0x000062f0+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x000065e8))=0xba9fef49;
*((unsigned int *)((unsigned long)context_ptr+0x000065e8+4*1))=0x26edceee;
*((unsigned int *)((unsigned long)context_ptr+0x000065e8+4*2))=0xc4d8df42;
*((unsigned int *)((unsigned long)context_ptr+0x000065e8+4*3))=0x1979dab8;
*((unsigned int *)((unsigned long)context_ptr+0x000065e8+4*4))=0x8f9b3fba;
*((unsigned int *)((unsigned long)context_ptr+0x000065e8+4*5))=0x1862a763;
*((unsigned int *)((unsigned long)context_ptr+0x000065e8+4*6))=0x8f48d8dc;
*((unsigned int *)((unsigned long)context_ptr+0x000065e8+4*7))=0x6274bc22;
*((unsigned int *)((unsigned long)context_ptr+0x000065e8+4*8))=0xced7d3ee;
*((unsigned int *)((unsigned long)context_ptr+0x000065e8+4*9))=0xeb51e7ba;
*((unsigned int *)((unsigned long)context_ptr+0x000065e8+4*10))=0x7858c06a;
*((unsigned int *)((unsigned long)context_ptr+0x000065e8+4*11))=0x0d521d3f;
*((unsigned int *)((unsigned long)context_ptr+0x000065e8+4*12))=0x93135350;
*((unsigned int *)((unsigned long)context_ptr+0x000065e8+4*13))=0x3f1a9cd7;
*((unsigned int *)((unsigned long)context_ptr+0x000065e8+4*14))=0x6bba4f4b;
*((unsigned int *)((unsigned long)context_ptr+0x000065e8+4*15))=0xfd39b210;
*((unsigned int *)((unsigned long)context_ptr+0x000065e8+4*16))=0x4482d105;
*((unsigned int *)((unsigned long)context_ptr+0x000065e8+4*17))=0x10493427;
*((unsigned int *)((unsigned long)context_ptr+0x000065e8+4*18))=0x001138dd;
*((unsigned int *)((unsigned long)context_ptr+0x000036f0))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x000036f0+4*1))=0x00006424;
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
*((unsigned int *)((unsigned long)context_ptr+0x000006f0+4*1))=0x000065e8;
*((unsigned int *)((unsigned long)context_ptr+0x000006f0+4*2))=0x000062f0;
*((unsigned int *)((unsigned long)context_ptr+0x000006f0+4*3))=0x0222004b;
*((unsigned int *)((unsigned long)context_ptr+0x000006f0+4*4))=0x05aa8537;
*((unsigned int *)((unsigned long)context_ptr+0x000006f0+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000016e&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006528,"\xac\x2e\x5c\x55\x05\x54\x9e\x0a\x9b\x3f\xc2\xa4\xd1\x52\x8d\x18\x27\x48\x7d\x84\x4c\x3e\xed\xc0\x71\xed\x2b\xc3\xad\x64\xbf\xc5",32))
printf("strip: ac2e5c5505549e0a, Pass\n");
else
printf("strip: ac2e5c5505549e0a, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006444))=0x018a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006444+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006444+4*2))=0x0202004c;
*((unsigned int *)((unsigned long)context_ptr+0x00006444+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x00006300))=0xc8d51969;
*((unsigned int *)((unsigned long)context_ptr+0x00006300+4*1))=0xd57ecda8;
*((unsigned int *)((unsigned long)context_ptr+0x00006300+4*2))=0x8e8c112c;
*((unsigned int *)((unsigned long)context_ptr+0x00006300+4*3))=0x1e643a94;
*((unsigned int *)((unsigned long)context_ptr+0x00006300+4*4))=0xf7a6d8d0;
*((unsigned int *)((unsigned long)context_ptr+0x00006300+4*5))=0xe5ceefa0;
*((unsigned int *)((unsigned long)context_ptr+0x00006300+4*6))=0xa325185f;
*((unsigned int *)((unsigned long)context_ptr+0x00006300+4*7))=0xadca71ca;
*((unsigned int *)((unsigned long)context_ptr+0x00006300+4*8))=0x44333034;
*((unsigned int *)((unsigned long)context_ptr+0x00006300+4*9))=0x923c8b40;
*((unsigned int *)((unsigned long)context_ptr+0x00006300+4*10))=0xc3a9cc9f;
*((unsigned int *)((unsigned long)context_ptr+0x00006300+4*11))=0xa054077c;
*((unsigned int *)((unsigned long)context_ptr+0x00006300+4*12))=0x082eeb7b;
*((unsigned int *)((unsigned long)context_ptr+0x00006300+4*13))=0x8ad83870;
*((unsigned int *)((unsigned long)context_ptr+0x00006300+4*14))=0x673ba5b7;
*((unsigned int *)((unsigned long)context_ptr+0x00006300+4*15))=0xceee3dd8;
*((unsigned int *)((unsigned long)context_ptr+0x00006300+4*16))=0xb7828a82;
*((unsigned int *)((unsigned long)context_ptr+0x00006300+4*17))=0xe486d0a3;
*((unsigned int *)((unsigned long)context_ptr+0x00006300+4*18))=0xcae1ca15;
*((unsigned int *)((unsigned long)context_ptr+0x00003708))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003708+4*1))=0x00006528;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000708+4*1))=0x00006300;
*((unsigned int *)((unsigned long)context_ptr+0x00000708+4*2))=0x00006444;
*((unsigned int *)((unsigned long)context_ptr+0x00000708+4*3))=0x0222004c;
*((unsigned int *)((unsigned long)context_ptr+0x00000708+4*4))=0x02098054;
*((unsigned int *)((unsigned long)context_ptr+0x00000708+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000174&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006038,"\x8b\xe9\x1d\x4d\xdd\x9a\x0d\xf5\x46\x80\xc7\x69\x47\x49\x9b\x0c\x95\xf3\xd2\x6b\x30\x11\xa0\xe9\x14\x71\x97\x89\x40\xf7\x18\x0f",32))
printf("strip: 8be91d4ddd9a0df5, Pass\n");
else
printf("strip: 8be91d4ddd9a0df5, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006454))=0x018a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006454+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006454+4*2))=0x0202004d;
*((unsigned int *)((unsigned long)context_ptr+0x00006454+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x00006634))=0x8e341b4c;
*((unsigned int *)((unsigned long)context_ptr+0x00006634+4*1))=0x8420f867;
*((unsigned int *)((unsigned long)context_ptr+0x00006634+4*2))=0xd3e449ce;
*((unsigned int *)((unsigned long)context_ptr+0x00006634+4*3))=0xc86dc26b;
*((unsigned int *)((unsigned long)context_ptr+0x00006634+4*4))=0x49689056;
*((unsigned int *)((unsigned long)context_ptr+0x00006634+4*5))=0x3cb76a74;
*((unsigned int *)((unsigned long)context_ptr+0x00006634+4*6))=0x65c0bff2;
*((unsigned int *)((unsigned long)context_ptr+0x00006634+4*7))=0x79e490e5;
*((unsigned int *)((unsigned long)context_ptr+0x00006634+4*8))=0x393544f6;
*((unsigned int *)((unsigned long)context_ptr+0x00006634+4*9))=0x9d0bc75c;
*((unsigned int *)((unsigned long)context_ptr+0x00006634+4*10))=0x654b7d4f;
*((unsigned int *)((unsigned long)context_ptr+0x00006634+4*11))=0x58bd1f6b;
*((unsigned int *)((unsigned long)context_ptr+0x00006634+4*12))=0xb937d118;
*((unsigned int *)((unsigned long)context_ptr+0x00006634+4*13))=0xf8f20998;
*((unsigned int *)((unsigned long)context_ptr+0x00006634+4*14))=0x31b217bb;
*((unsigned int *)((unsigned long)context_ptr+0x00006634+4*15))=0xd3417e76;
*((unsigned int *)((unsigned long)context_ptr+0x00006634+4*16))=0xc09a7a1f;
*((unsigned int *)((unsigned long)context_ptr+0x00006634+4*17))=0x10f892dc;
*((unsigned int *)((unsigned long)context_ptr+0x00006634+4*18))=0x6938ce56;
*((unsigned int *)((unsigned long)context_ptr+0x00006634+4*19))=0x0000006f;
*((unsigned int *)((unsigned long)context_ptr+0x00003720))=0x04c00020;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000720+4*1))=0x00006634;
*((unsigned int *)((unsigned long)context_ptr+0x00000720+4*2))=0x00006454;
*((unsigned int *)((unsigned long)context_ptr+0x00000720+4*3))=0x0222004d;
*((unsigned int *)((unsigned long)context_ptr+0x00000720+4*4))=0x0c2ce6c7;
*((unsigned int *)((unsigned long)context_ptr+0x00000720+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000017a&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006548,"\xad\x41\x15\x50\x9f\x0f\x02\x0f\xcd\x08\x39\xa5\xf2\xec\x57\x2d\xe8\xe9\x66\xde\x39\x3d\x4a\xb7\xac\x31\x36\x57\x18\xb0\xc1\xb1",32))
printf("strip: ad4115509f0f020f, Pass\n");
else
printf("strip: ad4115509f0f020f, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006018))=0x018a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006018+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006018+4*2))=0x0202004e;
*((unsigned int *)((unsigned long)context_ptr+0x00006018+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x0000672c))=0x49803261;
*((unsigned int *)((unsigned long)context_ptr+0x0000672c+4*1))=0x9dc99b88;
*((unsigned int *)((unsigned long)context_ptr+0x0000672c+4*2))=0xe7e7ae67;
*((unsigned int *)((unsigned long)context_ptr+0x0000672c+4*3))=0x949c1ea6;
*((unsigned int *)((unsigned long)context_ptr+0x0000672c+4*4))=0xcf1990cc;
*((unsigned int *)((unsigned long)context_ptr+0x0000672c+4*5))=0x695a9475;
*((unsigned int *)((unsigned long)context_ptr+0x0000672c+4*6))=0xd288810b;
*((unsigned int *)((unsigned long)context_ptr+0x0000672c+4*7))=0xdcf9315c;
*((unsigned int *)((unsigned long)context_ptr+0x0000672c+4*8))=0x1e26f545;
*((unsigned int *)((unsigned long)context_ptr+0x0000672c+4*9))=0xf70207d0;
*((unsigned int *)((unsigned long)context_ptr+0x0000672c+4*10))=0x9245bc14;
*((unsigned int *)((unsigned long)context_ptr+0x0000672c+4*11))=0x9d1a247a;
*((unsigned int *)((unsigned long)context_ptr+0x0000672c+4*12))=0xcd2f8d36;
*((unsigned int *)((unsigned long)context_ptr+0x0000672c+4*13))=0x254ae392;
*((unsigned int *)((unsigned long)context_ptr+0x0000672c+4*14))=0x36309df5;
*((unsigned int *)((unsigned long)context_ptr+0x0000672c+4*15))=0x4cc4b22c;
*((unsigned int *)((unsigned long)context_ptr+0x0000672c+4*16))=0xaee12738;
*((unsigned int *)((unsigned long)context_ptr+0x0000672c+4*17))=0x1c17d706;
*((unsigned int *)((unsigned long)context_ptr+0x0000672c+4*18))=0x6a0b8fb4;
*((unsigned int *)((unsigned long)context_ptr+0x0000672c+4*19))=0x0000183d;
*((unsigned int *)((unsigned long)context_ptr+0x00003738))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003738+4*1))=0x00006548;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000738+4*1))=0x0000672c;
*((unsigned int *)((unsigned long)context_ptr+0x00000738+4*2))=0x00006018;
*((unsigned int *)((unsigned long)context_ptr+0x00000738+4*3))=0x0222004e;
*((unsigned int *)((unsigned long)context_ptr+0x00000738+4*4))=0x06e40914;
*((unsigned int *)((unsigned long)context_ptr+0x00000738+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000180&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006468,"\x1b\x8b\xde\x15\x72\x8d\x62\x8f\x27\x18\x13\x9b\xa4\x57\xca\x80\x37\x02\x63\xf2\xf5\x3e\xa9\x7b\x49\x1b\x9b\x73\xea\x81\x32\x3d",32))
printf("strip: 1b8bde15728d628f, Pass\n");
else
printf("strip: 1b8bde15728d628f, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006008))=0x018a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006008+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006008+4*2))=0x0202004f;
*((unsigned int *)((unsigned long)context_ptr+0x00006008+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x0000677c))=0x06951e8c;
*((unsigned int *)((unsigned long)context_ptr+0x0000677c+4*1))=0xc22ef39b;
*((unsigned int *)((unsigned long)context_ptr+0x0000677c+4*2))=0x98d7abca;
*((unsigned int *)((unsigned long)context_ptr+0x0000677c+4*3))=0xb6ea52b7;
*((unsigned int *)((unsigned long)context_ptr+0x0000677c+4*4))=0x9aae57a8;
*((unsigned int *)((unsigned long)context_ptr+0x0000677c+4*5))=0x6fe08e70;
*((unsigned int *)((unsigned long)context_ptr+0x0000677c+4*6))=0xd818a955;
*((unsigned int *)((unsigned long)context_ptr+0x0000677c+4*7))=0xc5deb5e5;
*((unsigned int *)((unsigned long)context_ptr+0x0000677c+4*8))=0xba8ca432;
*((unsigned int *)((unsigned long)context_ptr+0x0000677c+4*9))=0x2c5ac573;
*((unsigned int *)((unsigned long)context_ptr+0x0000677c+4*10))=0xdcc23b09;
*((unsigned int *)((unsigned long)context_ptr+0x0000677c+4*11))=0x74da56b6;
*((unsigned int *)((unsigned long)context_ptr+0x0000677c+4*12))=0x3117c5f6;
*((unsigned int *)((unsigned long)context_ptr+0x0000677c+4*13))=0x64122cf6;
*((unsigned int *)((unsigned long)context_ptr+0x0000677c+4*14))=0xca1580ba;
*((unsigned int *)((unsigned long)context_ptr+0x0000677c+4*15))=0x032995ab;
*((unsigned int *)((unsigned long)context_ptr+0x0000677c+4*16))=0x922f2fd7;
*((unsigned int *)((unsigned long)context_ptr+0x0000677c+4*17))=0xe82d0a9b;
*((unsigned int *)((unsigned long)context_ptr+0x0000677c+4*18))=0xc3b0de69;
*((unsigned int *)((unsigned long)context_ptr+0x0000677c+4*19))=0x0091a42d;
*((unsigned int *)((unsigned long)context_ptr+0x00003750))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003750+4*1))=0x00006464;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000750+4*1))=0x0000677c;
*((unsigned int *)((unsigned long)context_ptr+0x00000750+4*2))=0x00006008;
*((unsigned int *)((unsigned long)context_ptr+0x00000750+4*3))=0x0222004f;
*((unsigned int *)((unsigned long)context_ptr+0x00000750+4*4))=0x02511744;
*((unsigned int *)((unsigned long)context_ptr+0x00000750+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000186&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006488,"\x05\x94\xa4\x71\x50\x32\x16\xd6\xe9\xcf\xba\xe9\x95\x8a\x4c\xed\xe2\x07\x47\x29\xee\xd9\x4f\x9d\x4b\x22\x2d\x57\x90\x9d\x85\x29",32))
printf("strip: 0594a471503216d6, Pass\n");
else
printf("strip: 0594a471503216d6, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006028))=0x018a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006028+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006028+4*2))=0x02020050;
*((unsigned int *)((unsigned long)context_ptr+0x00006028+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x000067cc))=0x4dd7ca13;
*((unsigned int *)((unsigned long)context_ptr+0x000067cc+4*1))=0xbad7a28c;
*((unsigned int *)((unsigned long)context_ptr+0x000067cc+4*2))=0xbbbb7e9c;
*((unsigned int *)((unsigned long)context_ptr+0x000067cc+4*3))=0x3a2ca6c0;
*((unsigned int *)((unsigned long)context_ptr+0x000067cc+4*4))=0x51c918e5;
*((unsigned int *)((unsigned long)context_ptr+0x000067cc+4*5))=0xd46ef52b;
*((unsigned int *)((unsigned long)context_ptr+0x000067cc+4*6))=0x0ddb6527;
*((unsigned int *)((unsigned long)context_ptr+0x000067cc+4*7))=0x9f2efc86;
*((unsigned int *)((unsigned long)context_ptr+0x000067cc+4*8))=0x54f9a9b0;
*((unsigned int *)((unsigned long)context_ptr+0x000067cc+4*9))=0xe92c3b5a;
*((unsigned int *)((unsigned long)context_ptr+0x000067cc+4*10))=0x3e179bd3;
*((unsigned int *)((unsigned long)context_ptr+0x000067cc+4*11))=0xac4a8633;
*((unsigned int *)((unsigned long)context_ptr+0x000067cc+4*12))=0xbf493569;
*((unsigned int *)((unsigned long)context_ptr+0x000067cc+4*13))=0x053f2f78;
*((unsigned int *)((unsigned long)context_ptr+0x000067cc+4*14))=0x6d898ea1;
*((unsigned int *)((unsigned long)context_ptr+0x000067cc+4*15))=0x0509b846;
*((unsigned int *)((unsigned long)context_ptr+0x000067cc+4*16))=0xf7af7acb;
*((unsigned int *)((unsigned long)context_ptr+0x000067cc+4*17))=0x5eb638b8;
*((unsigned int *)((unsigned long)context_ptr+0x000067cc+4*18))=0x5f5d4d6a;
*((unsigned int *)((unsigned long)context_ptr+0x000067cc+4*19))=0x9ad912bb;
*((unsigned int *)((unsigned long)context_ptr+0x00003768))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003768+4*1))=0x00006484;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000768+4*1))=0x000067cc;
*((unsigned int *)((unsigned long)context_ptr+0x00000768+4*2))=0x00006028;
*((unsigned int *)((unsigned long)context_ptr+0x00000768+4*3))=0x02220050;
*((unsigned int *)((unsigned long)context_ptr+0x00000768+4*4))=0x00b81f59;
*((unsigned int *)((unsigned long)context_ptr+0x00000768+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000018c&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000063a4,"\xee\xd6\xc3\x41\xe3\xdd\x21\x2d\xed\x83\x8a\x39\xdb\xd0\xf3\x7d\x13\x85\x85\xbf\xe0\xf5\xb3\x1a\xa5\x2f\x5e\xca\xb2\xab\x86\xf5",32))
printf("strip: eed6c341e3dd212d, Pass\n");
else
printf("strip: eed6c341e3dd212d, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006684))=0x018a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006684+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006684+4*2))=0x02020051;
*((unsigned int *)((unsigned long)context_ptr+0x00006684+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x0000634c))=0x563864cf;
*((unsigned int *)((unsigned long)context_ptr+0x0000634c+4*1))=0xea5c5d1e;
*((unsigned int *)((unsigned long)context_ptr+0x0000634c+4*2))=0x7f3e6795;
*((unsigned int *)((unsigned long)context_ptr+0x0000634c+4*3))=0xe157a80a;
*((unsigned int *)((unsigned long)context_ptr+0x0000634c+4*4))=0x195f0fe8;
*((unsigned int *)((unsigned long)context_ptr+0x0000634c+4*5))=0xb5c0d7b8;
*((unsigned int *)((unsigned long)context_ptr+0x0000634c+4*6))=0x5f35c14a;
*((unsigned int *)((unsigned long)context_ptr+0x0000634c+4*7))=0x19cedff8;
*((unsigned int *)((unsigned long)context_ptr+0x0000634c+4*8))=0x25d2aa6c;
*((unsigned int *)((unsigned long)context_ptr+0x0000634c+4*9))=0x04a2f6c9;
*((unsigned int *)((unsigned long)context_ptr+0x0000634c+4*10))=0x231344c5;
*((unsigned int *)((unsigned long)context_ptr+0x0000634c+4*11))=0x61092944;
*((unsigned int *)((unsigned long)context_ptr+0x0000634c+4*12))=0x05c56211;
*((unsigned int *)((unsigned long)context_ptr+0x0000634c+4*13))=0x92de43be;
*((unsigned int *)((unsigned long)context_ptr+0x0000634c+4*14))=0x6e19e892;
*((unsigned int *)((unsigned long)context_ptr+0x0000634c+4*15))=0xd8086135;
*((unsigned int *)((unsigned long)context_ptr+0x0000634c+4*16))=0x9f81bd01;
*((unsigned int *)((unsigned long)context_ptr+0x0000634c+4*17))=0xd7490202;
*((unsigned int *)((unsigned long)context_ptr+0x0000634c+4*18))=0xaff14ff0;
*((unsigned int *)((unsigned long)context_ptr+0x0000634c+4*19))=0x5e4dc46c;
*((unsigned int *)((unsigned long)context_ptr+0x0000634c+4*20))=0x000000d6;
*((unsigned int *)((unsigned long)context_ptr+0x00003780))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003780+4*1))=0x000063a0;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000780+4*1))=0x0000634c;
*((unsigned int *)((unsigned long)context_ptr+0x00000780+4*2))=0x00006684;
*((unsigned int *)((unsigned long)context_ptr+0x00000780+4*3))=0x02220051;
*((unsigned int *)((unsigned long)context_ptr+0x00000780+4*4))=0x05c00fd9;
*((unsigned int *)((unsigned long)context_ptr+0x00000780+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000192&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000064a8,"\xe2\xf0\xda\xba\x58\xda\x65\x08\x3d\x09\x0d\xae\x13\x9f\x5d\x41\xbd\x34\x46\x24\x52\xec\x19\xc7\x2e\xba\x19\xdf\xfe\x46\x19\x12",32))
printf("strip: e2f0daba58da6508, Pass\n");
else
printf("strip: e2f0daba58da6508, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000063c0))=0x018a0012;
*((unsigned int *)((unsigned long)context_ptr+0x000063c0+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000063c0+4*2))=0x02020052;
*((unsigned int *)((unsigned long)context_ptr+0x000063c0+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x00006058))=0x7b8a6840;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*1))=0xac81dd2d;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*2))=0x234d6c70;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*3))=0xc207ff89;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*4))=0x3b829784;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*5))=0x978b77b7;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*6))=0xb7c60b91;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*7))=0x6ead3828;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*8))=0xca9c09fe;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*9))=0x513ef34f;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*10))=0xb2a51267;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*11))=0x975316c8;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*12))=0xde77a788;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*13))=0x230cc7ec;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*14))=0x6500e42d;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*15))=0x88d1f0f6;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*16))=0xb09bbb58;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*17))=0xdd618090;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*18))=0x95a09e0f;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*19))=0xa77a6d2e;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*20))=0x0000177e;
*((unsigned int *)((unsigned long)context_ptr+0x00003798))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003798+4*1))=0x000064a4;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000798+4*1))=0x00006058;
*((unsigned int *)((unsigned long)context_ptr+0x00000798+4*2))=0x000063c0;
*((unsigned int *)((unsigned long)context_ptr+0x00000798+4*3))=0x02220052;
*((unsigned int *)((unsigned long)context_ptr+0x00000798+4*4))=0x0bfe50d0;
*((unsigned int *)((unsigned long)context_ptr+0x00000798+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000198&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006168,"\xcc\xfb\xf3\x68\xde\x7f\xae\x18\x71\x54\xeb\x4b\x3a\x85\x4c\xb1\x8e\x26\x22\x2e\x8d\x10\xac\xd4\x7d\x5f\xc0\x7b\xb1\x07\xf2\x00",32))
printf("strip: ccfbf368de7fae18, Pass\n");
else
printf("strip: ccfbf368de7fae18, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000063d0))=0x018a0012;
*((unsigned int *)((unsigned long)context_ptr+0x000063d0+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000063d0+4*2))=0x02020053;
*((unsigned int *)((unsigned long)context_ptr+0x000063d0+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x000060ac))=0x259e3ad5;
*((unsigned int *)((unsigned long)context_ptr+0x000060ac+4*1))=0x9b577c2d;
*((unsigned int *)((unsigned long)context_ptr+0x000060ac+4*2))=0xb94d795a;
*((unsigned int *)((unsigned long)context_ptr+0x000060ac+4*3))=0x37800608;
*((unsigned int *)((unsigned long)context_ptr+0x000060ac+4*4))=0x692182a8;
*((unsigned int *)((unsigned long)context_ptr+0x000060ac+4*5))=0x27a865d0;
*((unsigned int *)((unsigned long)context_ptr+0x000060ac+4*6))=0x9f319930;
*((unsigned int *)((unsigned long)context_ptr+0x000060ac+4*7))=0xc20389d8;
*((unsigned int *)((unsigned long)context_ptr+0x000060ac+4*8))=0x28496846;
*((unsigned int *)((unsigned long)context_ptr+0x000060ac+4*9))=0x5f0abca5;
*((unsigned int *)((unsigned long)context_ptr+0x000060ac+4*10))=0x03f9d6bc;
*((unsigned int *)((unsigned long)context_ptr+0x000060ac+4*11))=0xf30e081c;
*((unsigned int *)((unsigned long)context_ptr+0x000060ac+4*12))=0x9e451539;
*((unsigned int *)((unsigned long)context_ptr+0x000060ac+4*13))=0xc4e3e2e9;
*((unsigned int *)((unsigned long)context_ptr+0x000060ac+4*14))=0x247a36ca;
*((unsigned int *)((unsigned long)context_ptr+0x000060ac+4*15))=0xa4af6f55;
*((unsigned int *)((unsigned long)context_ptr+0x000060ac+4*16))=0xb0b75374;
*((unsigned int *)((unsigned long)context_ptr+0x000060ac+4*17))=0x95e60382;
*((unsigned int *)((unsigned long)context_ptr+0x000060ac+4*18))=0x09216230;
*((unsigned int *)((unsigned long)context_ptr+0x000060ac+4*19))=0xae7667c5;
*((unsigned int *)((unsigned long)context_ptr+0x000060ac+4*20))=0x00637169;
*((unsigned int *)((unsigned long)context_ptr+0x000037b0))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x000037b0+4*1))=0x00006568;
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
*((unsigned int *)((unsigned long)context_ptr+0x000007b0+4*1))=0x000060ac;
*((unsigned int *)((unsigned long)context_ptr+0x000007b0+4*2))=0x000063d0;
*((unsigned int *)((unsigned long)context_ptr+0x000007b0+4*3))=0x02220053;
*((unsigned int *)((unsigned long)context_ptr+0x000007b0+4*4))=0x005283e8;
*((unsigned int *)((unsigned long)context_ptr+0x000007b0+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000019e&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000064c8,"\x8c\x2f\xa0\xde\x3d\xd8\x4a\xbd\x15\xad\x07\xfa\x05\x7f\x0f\x24\x6c\xa1\xfb\x17\xe4\xc2\x2c\x02\x2c\x35\xca\xc7\xe2\x81\x39\x8f",32))
printf("strip: 8c2fa0de3dd84abd, Pass\n");
else
printf("strip: 8c2fa0de3dd84abd, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000063e0))=0x018a0012;
*((unsigned int *)((unsigned long)context_ptr+0x000063e0+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000063e0+4*2))=0x02020054;
*((unsigned int *)((unsigned long)context_ptr+0x000063e0+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x00006100))=0x5405c5c1;
*((unsigned int *)((unsigned long)context_ptr+0x00006100+4*1))=0x568c3a50;
*((unsigned int *)((unsigned long)context_ptr+0x00006100+4*2))=0x5526c028;
*((unsigned int *)((unsigned long)context_ptr+0x00006100+4*3))=0x6d59c6e4;
*((unsigned int *)((unsigned long)context_ptr+0x00006100+4*4))=0xc5fab35d;
*((unsigned int *)((unsigned long)context_ptr+0x00006100+4*5))=0xf2600a00;
*((unsigned int *)((unsigned long)context_ptr+0x00006100+4*6))=0x83d66294;
*((unsigned int *)((unsigned long)context_ptr+0x00006100+4*7))=0xb03d8cbf;
*((unsigned int *)((unsigned long)context_ptr+0x00006100+4*8))=0x029c1e34;
*((unsigned int *)((unsigned long)context_ptr+0x00006100+4*9))=0x68654376;
*((unsigned int *)((unsigned long)context_ptr+0x00006100+4*10))=0x4387176d;
*((unsigned int *)((unsigned long)context_ptr+0x00006100+4*11))=0x9ed917e9;
*((unsigned int *)((unsigned long)context_ptr+0x00006100+4*12))=0x8f8a8959;
*((unsigned int *)((unsigned long)context_ptr+0x00006100+4*13))=0xbc1190e2;
*((unsigned int *)((unsigned long)context_ptr+0x00006100+4*14))=0x2a7fc815;
*((unsigned int *)((unsigned long)context_ptr+0x00006100+4*15))=0x9fd6ac50;
*((unsigned int *)((unsigned long)context_ptr+0x00006100+4*16))=0x269730c5;
*((unsigned int *)((unsigned long)context_ptr+0x00006100+4*17))=0xaf01faea;
*((unsigned int *)((unsigned long)context_ptr+0x00006100+4*18))=0x43b32d14;
*((unsigned int *)((unsigned long)context_ptr+0x00006100+4*19))=0x2120d30b;
*((unsigned int *)((unsigned long)context_ptr+0x00006100+4*20))=0x4db9f8e2;
*((unsigned int *)((unsigned long)context_ptr+0x000037c8))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x000037c8+4*1))=0x00006588;
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
*((unsigned int *)((unsigned long)context_ptr+0x000007c8+4*1))=0x00006100;
*((unsigned int *)((unsigned long)context_ptr+0x000007c8+4*2))=0x000063e0;
*((unsigned int *)((unsigned long)context_ptr+0x000007c8+4*3))=0x02220054;
*((unsigned int *)((unsigned long)context_ptr+0x000007c8+4*4))=0x0d03cbba;
*((unsigned int *)((unsigned long)context_ptr+0x000007c8+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000001a4&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000061d0,"\x0d\xf8\x39\x5d\x3b\x92\x90\x0e\x0c\xee\x0e\xf2\x01\xfd\x57\x18\xa1\xe4\x93\xc3\x6b\x04\x55\x1c\x7f\x80\x2a\x66\xa5\x78\x99\x0a",32))
printf("strip: 0df8395d3b92900e, Pass\n");
else
printf("strip: 0df8395d3b92900e, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000063f0))=0x018a0012;
*((unsigned int *)((unsigned long)context_ptr+0x000063f0+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000063f0+4*2))=0x02020055;
*((unsigned int *)((unsigned long)context_ptr+0x000063f0+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x00006154))=0x152d9ca1;
*((unsigned int *)((unsigned long)context_ptr+0x00006154+4*1))=0x4a30440c;
*((unsigned int *)((unsigned long)context_ptr+0x00006154+4*2))=0xb4ecb397;
*((unsigned int *)((unsigned long)context_ptr+0x00006154+4*3))=0xd2da4aa1;
*((unsigned int *)((unsigned long)context_ptr+0x00006154+4*4))=0xcbbbbbc4;
*((unsigned int *)((unsigned long)context_ptr+0x00006154+4*5))=0xf3494390;
*((unsigned int *)((unsigned long)context_ptr+0x00006154+4*6))=0x8c09762a;
*((unsigned int *)((unsigned long)context_ptr+0x00006154+4*7))=0x4d08477c;
*((unsigned int *)((unsigned long)context_ptr+0x00006154+4*8))=0x1c07c58e;
*((unsigned int *)((unsigned long)context_ptr+0x00006154+4*9))=0xb6cccd75;
*((unsigned int *)((unsigned long)context_ptr+0x00006154+4*10))=0x0d9cf14f;
*((unsigned int *)((unsigned long)context_ptr+0x00006154+4*11))=0xe50b7e46;
*((unsigned int *)((unsigned long)context_ptr+0x00006154+4*12))=0x4106876c;
*((unsigned int *)((unsigned long)context_ptr+0x00006154+4*13))=0xae83945d;
*((unsigned int *)((unsigned long)context_ptr+0x00006154+4*14))=0x9a63852d;
*((unsigned int *)((unsigned long)context_ptr+0x00006154+4*15))=0x8f5d57ba;
*((unsigned int *)((unsigned long)context_ptr+0x00006154+4*16))=0xb8bea0d3;
*((unsigned int *)((unsigned long)context_ptr+0x00006154+4*17))=0x9f26a195;
*((unsigned int *)((unsigned long)context_ptr+0x00006154+4*18))=0xb60010ba;
*((unsigned int *)((unsigned long)context_ptr+0x00006154+4*19))=0xb59006d8;
*((unsigned int *)((unsigned long)context_ptr+0x00006154+4*20))=0x946562e3;
*((unsigned int *)((unsigned long)context_ptr+0x00006154+4*21))=0x000000a9;
*((unsigned int *)((unsigned long)context_ptr+0x000037e0))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x000037e0+4*1))=0x000064c4;
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
*((unsigned int *)((unsigned long)context_ptr+0x000007e0+4*1))=0x00006154;
*((unsigned int *)((unsigned long)context_ptr+0x000007e0+4*2))=0x000063f0;
*((unsigned int *)((unsigned long)context_ptr+0x000007e0+4*3))=0x02220055;
*((unsigned int *)((unsigned long)context_ptr+0x000007e0+4*4))=0x04d8c5f5;
*((unsigned int *)((unsigned long)context_ptr+0x000007e0+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000001aa&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000064e8,"\xc0\x35\x90\xc5\x0d\xd6\x71\x2e\xd0\x9c\x17\x98\xba\x25\x30\xdc\x59\xc4\xf9\xde\xf1\x3c\xec\xfd\x19\x2e\xa6\x49\x80\xa0\xc8\x60",32))
printf("strip: c03590c50dd6712e, Pass\n");
else
printf("strip: c03590c50dd6712e, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006400))=0x018a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006400+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006400+4*2))=0x02020056;
*((unsigned int *)((unsigned long)context_ptr+0x00006400+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x00006694))=0xf0edf46c;
*((unsigned int *)((unsigned long)context_ptr+0x00006694+4*1))=0xed711e9e;
*((unsigned int *)((unsigned long)context_ptr+0x00006694+4*2))=0x4ddc8cbd;
*((unsigned int *)((unsigned long)context_ptr+0x00006694+4*3))=0x9bb9b4a3;
*((unsigned int *)((unsigned long)context_ptr+0x00006694+4*4))=0x42536867;
*((unsigned int *)((unsigned long)context_ptr+0x00006694+4*5))=0x925bada0;
*((unsigned int *)((unsigned long)context_ptr+0x00006694+4*6))=0xc0f83357;
*((unsigned int *)((unsigned long)context_ptr+0x00006694+4*7))=0x5fac01b2;
*((unsigned int *)((unsigned long)context_ptr+0x00006694+4*8))=0x263fee81;
*((unsigned int *)((unsigned long)context_ptr+0x00006694+4*9))=0x661688b4;
*((unsigned int *)((unsigned long)context_ptr+0x00006694+4*10))=0x7fe265e2;
*((unsigned int *)((unsigned long)context_ptr+0x00006694+4*11))=0x46c4b3dd;
*((unsigned int *)((unsigned long)context_ptr+0x00006694+4*12))=0xd3e9fbe5;
*((unsigned int *)((unsigned long)context_ptr+0x00006694+4*13))=0xfabd1cd8;
*((unsigned int *)((unsigned long)context_ptr+0x00006694+4*14))=0xb75d2d92;
*((unsigned int *)((unsigned long)context_ptr+0x00006694+4*15))=0x128a2a99;
*((unsigned int *)((unsigned long)context_ptr+0x00006694+4*16))=0x4ad309c3;
*((unsigned int *)((unsigned long)context_ptr+0x00006694+4*17))=0x97fee9ff;
*((unsigned int *)((unsigned long)context_ptr+0x00006694+4*18))=0xcb17c28a;
*((unsigned int *)((unsigned long)context_ptr+0x00006694+4*19))=0x676381dc;
*((unsigned int *)((unsigned long)context_ptr+0x00006694+4*20))=0xd43686bb;
*((unsigned int *)((unsigned long)context_ptr+0x00006694+4*21))=0x0000065c;
*((unsigned int *)((unsigned long)context_ptr+0x000037f8))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x000037f8+4*1))=0x000064e4;
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
*((unsigned int *)((unsigned long)context_ptr+0x000007f8+4*1))=0x00006694;
*((unsigned int *)((unsigned long)context_ptr+0x000007f8+4*2))=0x00006400;
*((unsigned int *)((unsigned long)context_ptr+0x000007f8+4*3))=0x02220056;
*((unsigned int *)((unsigned long)context_ptr+0x000007f8+4*4))=0x0b01e0a8;
*((unsigned int *)((unsigned long)context_ptr+0x000007f8+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000001b0&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000065a8,"\x91\xce\x66\xab\xb4\x6c\xcf\x8d\x08\x5f\x0f\x3a\x95\x6f\x9f\x7f\xf8\xce\x5a\xc9\xb3\x05\xaf\x6d\x1d\x03\x1a\x4a\x3a\xa0\xcf\xcc",32))
printf("strip: 91ce66abb46ccf8d, Pass\n");
else
printf("strip: 91ce66abb46ccf8d, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006410))=0x018a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006410+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006410+4*2))=0x02020057;
*((unsigned int *)((unsigned long)context_ptr+0x00006410+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x000061ac))=0xdd44491d;
*((unsigned int *)((unsigned long)context_ptr+0x000061ac+4*1))=0x932135b9;
*((unsigned int *)((unsigned long)context_ptr+0x000061ac+4*2))=0x43f038af;
*((unsigned int *)((unsigned long)context_ptr+0x000061ac+4*3))=0xdb5072d5;
*((unsigned int *)((unsigned long)context_ptr+0x000061ac+4*4))=0x4e8c7af8;
*((unsigned int *)((unsigned long)context_ptr+0x000061ac+4*5))=0xe9aa409e;
*((unsigned int *)((unsigned long)context_ptr+0x000061ac+4*6))=0x0fc9e688;
*((unsigned int *)((unsigned long)context_ptr+0x000061ac+4*7))=0x7a76bde0;
*((unsigned int *)((unsigned long)context_ptr+0x000061ac+4*8))=0x934a57c7;
*((unsigned int *)((unsigned long)context_ptr+0x000061ac+4*9))=0x220c6a04;
*((unsigned int *)((unsigned long)context_ptr+0x000061ac+4*10))=0xdd349fc8;
*((unsigned int *)((unsigned long)context_ptr+0x000061ac+4*11))=0x597b418b;
*((unsigned int *)((unsigned long)context_ptr+0x000061ac+4*12))=0x6aa8ff9e;
*((unsigned int *)((unsigned long)context_ptr+0x000061ac+4*13))=0xb2af8c8f;
*((unsigned int *)((unsigned long)context_ptr+0x000061ac+4*14))=0x4193788a;
*((unsigned int *)((unsigned long)context_ptr+0x000061ac+4*15))=0xa56f1e68;
*((unsigned int *)((unsigned long)context_ptr+0x000061ac+4*16))=0x94dc8a75;
*((unsigned int *)((unsigned long)context_ptr+0x000061ac+4*17))=0x624dc904;
*((unsigned int *)((unsigned long)context_ptr+0x000061ac+4*18))=0x3b4fd8f7;
*((unsigned int *)((unsigned long)context_ptr+0x000061ac+4*19))=0x11c03766;
*((unsigned int *)((unsigned long)context_ptr+0x000061ac+4*20))=0xa4007000;
*((unsigned int *)((unsigned long)context_ptr+0x000061ac+4*21))=0x00ed0eb3;
*((unsigned int *)((unsigned long)context_ptr+0x00003810))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003810+4*1))=0x000065a8;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000810+4*2))=0x00006410;
*((unsigned int *)((unsigned long)context_ptr+0x00000810+4*3))=0x02220057;
*((unsigned int *)((unsigned long)context_ptr+0x00000810+4*4))=0x0e54d1fa;
*((unsigned int *)((unsigned long)context_ptr+0x00000810+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000001b6&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000065c8,"\x5c\x8d\xe8\x55\x66\x9a\x96\xf4\x67\x87\xea\xab\xbb\xa8\x67\x34\xd7\x68\xec\xbb\x39\xed\xf6\x32\xa0\x96\x34\xf7\x0d\x86\x3f\x24",32))
printf("strip: 5c8de855669a96f4, Pass\n");
else
printf("strip: 5c8de855669a96f4, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006504))=0x018a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006504+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006504+4*2))=0x02020058;
*((unsigned int *)((unsigned long)context_ptr+0x00006504+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x00006204))=0x4ed3cd0e;
*((unsigned int *)((unsigned long)context_ptr+0x00006204+4*1))=0xe45abb3f;
*((unsigned int *)((unsigned long)context_ptr+0x00006204+4*2))=0x90a37a9e;
*((unsigned int *)((unsigned long)context_ptr+0x00006204+4*3))=0x42ef74d6;
*((unsigned int *)((unsigned long)context_ptr+0x00006204+4*4))=0x8459f119;
*((unsigned int *)((unsigned long)context_ptr+0x00006204+4*5))=0x8f9c5f4a;
*((unsigned int *)((unsigned long)context_ptr+0x00006204+4*6))=0x16a09286;
*((unsigned int *)((unsigned long)context_ptr+0x00006204+4*7))=0x6b7f38d6;
*((unsigned int *)((unsigned long)context_ptr+0x00006204+4*8))=0x0b46f634;
*((unsigned int *)((unsigned long)context_ptr+0x00006204+4*9))=0x832a5b1e;
*((unsigned int *)((unsigned long)context_ptr+0x00006204+4*10))=0x08fd53f9;
*((unsigned int *)((unsigned long)context_ptr+0x00006204+4*11))=0xabeebe85;
*((unsigned int *)((unsigned long)context_ptr+0x00006204+4*12))=0xbc771ce4;
*((unsigned int *)((unsigned long)context_ptr+0x00006204+4*13))=0x98dc5389;
*((unsigned int *)((unsigned long)context_ptr+0x00006204+4*14))=0x6bc87508;
*((unsigned int *)((unsigned long)context_ptr+0x00006204+4*15))=0x3d8d7c2a;
*((unsigned int *)((unsigned long)context_ptr+0x00006204+4*16))=0x5ff484a1;
*((unsigned int *)((unsigned long)context_ptr+0x00006204+4*17))=0xb3c9e2da;
*((unsigned int *)((unsigned long)context_ptr+0x00006204+4*18))=0x2389118b;
*((unsigned int *)((unsigned long)context_ptr+0x00006204+4*19))=0x237e3c5d;
*((unsigned int *)((unsigned long)context_ptr+0x00006204+4*20))=0x17db15db;
*((unsigned int *)((unsigned long)context_ptr+0x00006204+4*21))=0x130389f8;
*((unsigned int *)((unsigned long)context_ptr+0x00003828))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003828+4*1))=0x000065c8;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000828+4*1))=0x00006204;
*((unsigned int *)((unsigned long)context_ptr+0x00000828+4*2))=0x00006504;
*((unsigned int *)((unsigned long)context_ptr+0x00000828+4*3))=0x02220058;
*((unsigned int *)((unsigned long)context_ptr+0x00000828+4*4))=0x0a371e88;
*((unsigned int *)((unsigned long)context_ptr+0x00000828+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000001bc&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000062d0,"\xc0\xde\xc3\xfd\x17\x90\x89\xca\x5f\xd3\xe5\x8b\x66\x0e\x5a\x6d\x2c\x0b\x13\x4f\x78\xf8\x2f\x80\x61\x55\xed\xbd\x56\x07\x18\x80",32))
printf("strip: c0dec3fd179089ca, Pass\n");
else
printf("strip: c0dec3fd179089ca, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006514))=0x018a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006514+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006514+4*2))=0x02020059;
*((unsigned int *)((unsigned long)context_ptr+0x00006514+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x0000625c))=0x17d8655d;
*((unsigned int *)((unsigned long)context_ptr+0x0000625c+4*1))=0x5ff6335f;
*((unsigned int *)((unsigned long)context_ptr+0x0000625c+4*2))=0x5f127e39;
*((unsigned int *)((unsigned long)context_ptr+0x0000625c+4*3))=0x2684705d;
*((unsigned int *)((unsigned long)context_ptr+0x0000625c+4*4))=0x4f62ad19;
*((unsigned int *)((unsigned long)context_ptr+0x0000625c+4*5))=0x453a815a;
*((unsigned int *)((unsigned long)context_ptr+0x0000625c+4*6))=0x5bcf5df6;
*((unsigned int *)((unsigned long)context_ptr+0x0000625c+4*7))=0xfd331220;
*((unsigned int *)((unsigned long)context_ptr+0x0000625c+4*8))=0x9adafd6b;
*((unsigned int *)((unsigned long)context_ptr+0x0000625c+4*9))=0x3ec62a2c;
*((unsigned int *)((unsigned long)context_ptr+0x0000625c+4*10))=0x388e6779;
*((unsigned int *)((unsigned long)context_ptr+0x0000625c+4*11))=0x3fbbf3bb;
*((unsigned int *)((unsigned long)context_ptr+0x0000625c+4*12))=0x625527d8;
*((unsigned int *)((unsigned long)context_ptr+0x0000625c+4*13))=0x2850598d;
*((unsigned int *)((unsigned long)context_ptr+0x0000625c+4*14))=0xf9bfb063;
*((unsigned int *)((unsigned long)context_ptr+0x0000625c+4*15))=0xc50c98a1;
*((unsigned int *)((unsigned long)context_ptr+0x0000625c+4*16))=0x02fd3c72;
*((unsigned int *)((unsigned long)context_ptr+0x0000625c+4*17))=0x3d3aed79;
*((unsigned int *)((unsigned long)context_ptr+0x0000625c+4*18))=0xa9a9b221;
*((unsigned int *)((unsigned long)context_ptr+0x0000625c+4*19))=0xec0cb2b5;
*((unsigned int *)((unsigned long)context_ptr+0x0000625c+4*20))=0xd2868db8;
*((unsigned int *)((unsigned long)context_ptr+0x0000625c+4*21))=0x69b2dc74;
*((unsigned int *)((unsigned long)context_ptr+0x0000625c+4*22))=0x000000b6;
*((unsigned int *)((unsigned long)context_ptr+0x00003840))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003840+4*1))=0x000062b8;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000840+4*1))=0x0000625c;
*((unsigned int *)((unsigned long)context_ptr+0x00000840+4*2))=0x00006514;
*((unsigned int *)((unsigned long)context_ptr+0x00000840+4*3))=0x02220059;
*((unsigned int *)((unsigned long)context_ptr+0x00000840+4*4))=0x09d0ca8c;
*((unsigned int *)((unsigned long)context_ptr+0x00000840+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000001c2&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006424,"\x92\x56\x11\x21\xfb\x3d\x7a\xdc\x7b\x42\xa9\x3f\x54\xed\x61\x40\xde\xc6\x50\xa7\x30\x6d\x00\xb5\xcf\xb8\xf5\xf4\x77\x4a\x92\xef",32))
printf("strip: 92561121fb3d7adc, Pass\n");
else
printf("strip: 92561121fb3d7adc, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006420))=0x018a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006420+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006420+4*2))=0x0202005a;
*((unsigned int *)((unsigned long)context_ptr+0x00006420+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x0000681c))=0xdbb42769;
*((unsigned int *)((unsigned long)context_ptr+0x0000681c+4*1))=0xd69e1955;
*((unsigned int *)((unsigned long)context_ptr+0x0000681c+4*2))=0x0ec627fb;
*((unsigned int *)((unsigned long)context_ptr+0x0000681c+4*3))=0x0f1f0184;
*((unsigned int *)((unsigned long)context_ptr+0x0000681c+4*4))=0x2c99ffca;
*((unsigned int *)((unsigned long)context_ptr+0x0000681c+4*5))=0x8158304b;
*((unsigned int *)((unsigned long)context_ptr+0x0000681c+4*6))=0x1656589f;
*((unsigned int *)((unsigned long)context_ptr+0x0000681c+4*7))=0xe0dc4b05;
*((unsigned int *)((unsigned long)context_ptr+0x0000681c+4*8))=0x724380f0;
*((unsigned int *)((unsigned long)context_ptr+0x0000681c+4*9))=0x234a761b;
*((unsigned int *)((unsigned long)context_ptr+0x0000681c+4*10))=0x56d51556;
*((unsigned int *)((unsigned long)context_ptr+0x0000681c+4*11))=0x0b912aff;
*((unsigned int *)((unsigned long)context_ptr+0x0000681c+4*12))=0xfe356bd2;
*((unsigned int *)((unsigned long)context_ptr+0x0000681c+4*13))=0x7635d342;
*((unsigned int *)((unsigned long)context_ptr+0x0000681c+4*14))=0x0c6a50c1;
*((unsigned int *)((unsigned long)context_ptr+0x0000681c+4*15))=0xa73f783a;
*((unsigned int *)((unsigned long)context_ptr+0x0000681c+4*16))=0x42f9c354;
*((unsigned int *)((unsigned long)context_ptr+0x0000681c+4*17))=0x604dd3f5;
*((unsigned int *)((unsigned long)context_ptr+0x0000681c+4*18))=0xc3c71d4f;
*((unsigned int *)((unsigned long)context_ptr+0x0000681c+4*19))=0x80646cff;
*((unsigned int *)((unsigned long)context_ptr+0x0000681c+4*20))=0x3de2e7a9;
*((unsigned int *)((unsigned long)context_ptr+0x0000681c+4*21))=0x945eb454;
*((unsigned int *)((unsigned long)context_ptr+0x0000681c+4*22))=0x00006fb2;
*((unsigned int *)((unsigned long)context_ptr+0x00003858))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003858+4*1))=0x000062d8;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000858+4*1))=0x0000681c;
*((unsigned int *)((unsigned long)context_ptr+0x00000858+4*2))=0x00006420;
*((unsigned int *)((unsigned long)context_ptr+0x00000858+4*3))=0x0222005a;
*((unsigned int *)((unsigned long)context_ptr+0x00000858+4*4))=0x074b5d63;
*((unsigned int *)((unsigned long)context_ptr+0x00000858+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000001c8&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006528,"\x4f\xc8\x9f\xf4\x3b\x6e\xb9\xd0\x36\x99\x09\x01\x44\x01\x29\xc3\x35\x4f\xea\xa7\x6b\x34\x46\x57\x42\xd6\x23\x91\x1a\xf1\x1f\x13",32))
printf("strip: 4fc89ff43b6eb9d0, Pass\n");
else
printf("strip: 4fc89ff43b6eb9d0, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006430))=0x018a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006430+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006430+4*2))=0x0202005b;
*((unsigned int *)((unsigned long)context_ptr+0x00006430+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x00006878))=0xb4b5fe1b;
*((unsigned int *)((unsigned long)context_ptr+0x00006878+4*1))=0x9898691e;
*((unsigned int *)((unsigned long)context_ptr+0x00006878+4*2))=0x3b98e523;
*((unsigned int *)((unsigned long)context_ptr+0x00006878+4*3))=0x73fd8c78;
*((unsigned int *)((unsigned long)context_ptr+0x00006878+4*4))=0xc65f4823;
*((unsigned int *)((unsigned long)context_ptr+0x00006878+4*5))=0x672c78a4;
*((unsigned int *)((unsigned long)context_ptr+0x00006878+4*6))=0xd29a8ab2;
*((unsigned int *)((unsigned long)context_ptr+0x00006878+4*7))=0x898ee91a;
*((unsigned int *)((unsigned long)context_ptr+0x00006878+4*8))=0xf2e09f68;
*((unsigned int *)((unsigned long)context_ptr+0x00006878+4*9))=0x9c5f357e;
*((unsigned int *)((unsigned long)context_ptr+0x00006878+4*10))=0x0891f3ef;
*((unsigned int *)((unsigned long)context_ptr+0x00006878+4*11))=0xb372fed9;
*((unsigned int *)((unsigned long)context_ptr+0x00006878+4*12))=0x6bcaa098;
*((unsigned int *)((unsigned long)context_ptr+0x00006878+4*13))=0xb42a4b44;
*((unsigned int *)((unsigned long)context_ptr+0x00006878+4*14))=0x9a7d45c4;
*((unsigned int *)((unsigned long)context_ptr+0x00006878+4*15))=0x3e127f91;
*((unsigned int *)((unsigned long)context_ptr+0x00006878+4*16))=0x17587bb6;
*((unsigned int *)((unsigned long)context_ptr+0x00006878+4*17))=0x88237b9c;
*((unsigned int *)((unsigned long)context_ptr+0x00006878+4*18))=0xa3567e90;
*((unsigned int *)((unsigned long)context_ptr+0x00006878+4*19))=0xfa257436;
*((unsigned int *)((unsigned long)context_ptr+0x00006878+4*20))=0x243402eb;
*((unsigned int *)((unsigned long)context_ptr+0x00006878+4*21))=0x303b53c5;
*((unsigned int *)((unsigned long)context_ptr+0x00006878+4*22))=0x00c27971;
*((unsigned int *)((unsigned long)context_ptr+0x00003870))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003870+4*1))=0x00006524;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000870+4*1))=0x00006878;
*((unsigned int *)((unsigned long)context_ptr+0x00000870+4*2))=0x00006430;
*((unsigned int *)((unsigned long)context_ptr+0x00000870+4*3))=0x0222005b;
*((unsigned int *)((unsigned long)context_ptr+0x00000870+4*4))=0x04e2dd1c;
*((unsigned int *)((unsigned long)context_ptr+0x00000870+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000001ce&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006038,"\xed\xd1\x3c\x14\x82\x93\x74\x17\xf6\xea\x1c\x8f\x97\xad\x17\x23\xa0\x9d\x5c\x94\x53\xba\xfe\x04\x64\x64\xa0\xee\x20\xd5\x5b\xc1",32))
printf("strip: edd13c1482937417, Pass\n");
else
printf("strip: edd13c1482937417, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006038))=0x018a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006038+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006038+4*2))=0x0202005c;
*((unsigned int *)((unsigned long)context_ptr+0x00006038+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x000065e8))=0xf39d0c3c;
*((unsigned int *)((unsigned long)context_ptr+0x000065e8+4*1))=0x1fa77c50;
*((unsigned int *)((unsigned long)context_ptr+0x000065e8+4*2))=0x888e8ff9;
*((unsigned int *)((unsigned long)context_ptr+0x000065e8+4*3))=0xbd064507;
*((unsigned int *)((unsigned long)context_ptr+0x000065e8+4*4))=0x0e20e75b;
*((unsigned int *)((unsigned long)context_ptr+0x000065e8+4*5))=0x948f2d09;
*((unsigned int *)((unsigned long)context_ptr+0x000065e8+4*6))=0x812f74b4;
*((unsigned int *)((unsigned long)context_ptr+0x000065e8+4*7))=0xe1359134;
*((unsigned int *)((unsigned long)context_ptr+0x000065e8+4*8))=0xea34c471;
*((unsigned int *)((unsigned long)context_ptr+0x000065e8+4*9))=0xcbedac01;
*((unsigned int *)((unsigned long)context_ptr+0x000065e8+4*10))=0x05f206a0;
*((unsigned int *)((unsigned long)context_ptr+0x000065e8+4*11))=0x4ab520b3;
*((unsigned int *)((unsigned long)context_ptr+0x000065e8+4*12))=0x560ede5d;
*((unsigned int *)((unsigned long)context_ptr+0x000065e8+4*13))=0x3cfa9176;
*((unsigned int *)((unsigned long)context_ptr+0x000065e8+4*14))=0x244554b9;
*((unsigned int *)((unsigned long)context_ptr+0x000065e8+4*15))=0xbb0c0419;
*((unsigned int *)((unsigned long)context_ptr+0x000065e8+4*16))=0x9a2034f0;
*((unsigned int *)((unsigned long)context_ptr+0x000065e8+4*17))=0xef1d18c0;
*((unsigned int *)((unsigned long)context_ptr+0x000065e8+4*18))=0x4046235b;
*((unsigned int *)((unsigned long)context_ptr+0x000065e8+4*19))=0xfe61daa1;
*((unsigned int *)((unsigned long)context_ptr+0x000065e8+4*20))=0x802c2776;
*((unsigned int *)((unsigned long)context_ptr+0x000065e8+4*21))=0x16326c80;
*((unsigned int *)((unsigned long)context_ptr+0x000065e8+4*22))=0xcf812395;
*((unsigned int *)((unsigned long)context_ptr+0x00003888))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003888+4*1))=0x00006440;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000888+4*1))=0x000065e8;
*((unsigned int *)((unsigned long)context_ptr+0x00000888+4*2))=0x00006038;
*((unsigned int *)((unsigned long)context_ptr+0x00000888+4*3))=0x0222005c;
*((unsigned int *)((unsigned long)context_ptr+0x00000888+4*4))=0x0066a1bc;
*((unsigned int *)((unsigned long)context_ptr+0x00000888+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000001d4&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006548,"\xd5\x66\xed\x08\x18\x8c\xef\xb3\x5d\x97\xa7\xe1\xa6\x7a\x0d\xfe\xc4\x74\x57\xae\x06\x68\x9b\x6d\x18\xaf\xe5\x94\xcd\x62\x02\x6b",32))
printf("strip: d566ed08188cefb3, Pass\n");
else
printf("strip: d566ed08188cefb3, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006048))=0x018a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006048+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006048+4*2))=0x0202005d;
*((unsigned int *)((unsigned long)context_ptr+0x00006048+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x000066ec))=0x8bb7bbf3;
*((unsigned int *)((unsigned long)context_ptr+0x000066ec+4*1))=0x8c20a402;
*((unsigned int *)((unsigned long)context_ptr+0x000066ec+4*2))=0x49a97d18;
*((unsigned int *)((unsigned long)context_ptr+0x000066ec+4*3))=0x0661f3bf;
*((unsigned int *)((unsigned long)context_ptr+0x000066ec+4*4))=0x87463c9a;
*((unsigned int *)((unsigned long)context_ptr+0x000066ec+4*5))=0x1d49de41;
*((unsigned int *)((unsigned long)context_ptr+0x000066ec+4*6))=0xb0be1ea5;
*((unsigned int *)((unsigned long)context_ptr+0x000066ec+4*7))=0xe551462a;
*((unsigned int *)((unsigned long)context_ptr+0x000066ec+4*8))=0xf93ec3f8;
*((unsigned int *)((unsigned long)context_ptr+0x000066ec+4*9))=0x0a7a3147;
*((unsigned int *)((unsigned long)context_ptr+0x000066ec+4*10))=0x1cb830e5;
*((unsigned int *)((unsigned long)context_ptr+0x000066ec+4*11))=0xc38ffe4a;
*((unsigned int *)((unsigned long)context_ptr+0x000066ec+4*12))=0x9b7e1850;
*((unsigned int *)((unsigned long)context_ptr+0x000066ec+4*13))=0xbed73d54;
*((unsigned int *)((unsigned long)context_ptr+0x000066ec+4*14))=0xc37b7c3c;
*((unsigned int *)((unsigned long)context_ptr+0x000066ec+4*15))=0x3da19785;
*((unsigned int *)((unsigned long)context_ptr+0x000066ec+4*16))=0xcf55ae0e;
*((unsigned int *)((unsigned long)context_ptr+0x000066ec+4*17))=0x0ddbb0ef;
*((unsigned int *)((unsigned long)context_ptr+0x000066ec+4*18))=0x54c5c7d7;
*((unsigned int *)((unsigned long)context_ptr+0x000066ec+4*19))=0xe7887e04;
*((unsigned int *)((unsigned long)context_ptr+0x000066ec+4*20))=0xdd4b816c;
*((unsigned int *)((unsigned long)context_ptr+0x000066ec+4*21))=0xe69a8d04;
*((unsigned int *)((unsigned long)context_ptr+0x000066ec+4*22))=0xda0645ff;
*((unsigned int *)((unsigned long)context_ptr+0x000066ec+4*23))=0x0000000a;
*((unsigned int *)((unsigned long)context_ptr+0x000038a0))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x000038a0+4*1))=0x00006544;
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
*((unsigned int *)((unsigned long)context_ptr+0x000008a0+4*1))=0x000066ec;
*((unsigned int *)((unsigned long)context_ptr+0x000008a0+4*2))=0x00006048;
*((unsigned int *)((unsigned long)context_ptr+0x000008a0+4*3))=0x0222005d;
*((unsigned int *)((unsigned long)context_ptr+0x000008a0+4*4))=0x0a07a2ff;
*((unsigned int *)((unsigned long)context_ptr+0x000008a0+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000001da&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006464,"\x2c\x40\x9a\x22\x1e\xed\xfe\x43\xfb\x8c\x27\x2f\x03\x45\x06\xf5\x29\x99\xa8\xce\x67\x12\xd3\xf5\x08\x75\x2d\x94\xd1\x8d\x75\xee",32))
printf("strip: 2c409a221eedfe43, Pass\n");
else
printf("strip: 2c409a221eedfe43, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006018))=0x018a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006018+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006018+4*2))=0x0202005e;
*((unsigned int *)((unsigned long)context_ptr+0x00006018+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x0000674c))=0x6cac4983;
*((unsigned int *)((unsigned long)context_ptr+0x0000674c+4*1))=0x5116ca02;
*((unsigned int *)((unsigned long)context_ptr+0x0000674c+4*2))=0xcdd1c327;
*((unsigned int *)((unsigned long)context_ptr+0x0000674c+4*3))=0xb0eb1ff7;
*((unsigned int *)((unsigned long)context_ptr+0x0000674c+4*4))=0x1a1cfa1e;
*((unsigned int *)((unsigned long)context_ptr+0x0000674c+4*5))=0xee1c3dab;
*((unsigned int *)((unsigned long)context_ptr+0x0000674c+4*6))=0x9e4f30e2;
*((unsigned int *)((unsigned long)context_ptr+0x0000674c+4*7))=0x9d93de90;
*((unsigned int *)((unsigned long)context_ptr+0x0000674c+4*8))=0x54042fed;
*((unsigned int *)((unsigned long)context_ptr+0x0000674c+4*9))=0x1076aaed;
*((unsigned int *)((unsigned long)context_ptr+0x0000674c+4*10))=0x36310874;
*((unsigned int *)((unsigned long)context_ptr+0x0000674c+4*11))=0xb51dc77a;
*((unsigned int *)((unsigned long)context_ptr+0x0000674c+4*12))=0xf103af82;
*((unsigned int *)((unsigned long)context_ptr+0x0000674c+4*13))=0xae246517;
*((unsigned int *)((unsigned long)context_ptr+0x0000674c+4*14))=0xd11e3e4a;
*((unsigned int *)((unsigned long)context_ptr+0x0000674c+4*15))=0x64cc4234;
*((unsigned int *)((unsigned long)context_ptr+0x0000674c+4*16))=0x88dfc8b1;
*((unsigned int *)((unsigned long)context_ptr+0x0000674c+4*17))=0x8e96d139;
*((unsigned int *)((unsigned long)context_ptr+0x0000674c+4*18))=0x5b999f27;
*((unsigned int *)((unsigned long)context_ptr+0x0000674c+4*19))=0xae3b73bd;
*((unsigned int *)((unsigned long)context_ptr+0x0000674c+4*20))=0xc556d2e8;
*((unsigned int *)((unsigned long)context_ptr+0x0000674c+4*21))=0x602603cc;
*((unsigned int *)((unsigned long)context_ptr+0x0000674c+4*22))=0x8b485cb1;
*((unsigned int *)((unsigned long)context_ptr+0x0000674c+4*23))=0x0000d91b;
*((unsigned int *)((unsigned long)context_ptr+0x000038b8))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x000038b8+4*1))=0x000067ac;
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
*((unsigned int *)((unsigned long)context_ptr+0x000008b8+4*1))=0x0000674c;
*((unsigned int *)((unsigned long)context_ptr+0x000008b8+4*2))=0x00006018;
*((unsigned int *)((unsigned long)context_ptr+0x000008b8+4*3))=0x0222005e;
*((unsigned int *)((unsigned long)context_ptr+0x000008b8+4*4))=0x08953d48;
*((unsigned int *)((unsigned long)context_ptr+0x000008b8+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000001e0&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006484,"\x06\x69\xc0\x79\x4d\x3e\xa8\xa3\xd3\xe3\x00\x79\xab\xf4\xbb\x7c\xa5\x10\x8d\x54\xd1\x16\x0e\xe5\x40\x28\x62\x1a\xa9\xda\x05\x80",32))
printf("strip: 0669c0794d3ea8a3, Pass\n");
else
printf("strip: 0669c0794d3ea8a3, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006008))=0x018a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006008+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006008+4*2))=0x0202005f;
*((unsigned int *)((unsigned long)context_ptr+0x00006008+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x000068d4))=0xacf1dc26;
*((unsigned int *)((unsigned long)context_ptr+0x000068d4+4*1))=0xe1995242;
*((unsigned int *)((unsigned long)context_ptr+0x000068d4+4*2))=0xcadb9db7;
*((unsigned int *)((unsigned long)context_ptr+0x000068d4+4*3))=0xd87f30b3;
*((unsigned int *)((unsigned long)context_ptr+0x000068d4+4*4))=0xb3161064;
*((unsigned int *)((unsigned long)context_ptr+0x000068d4+4*5))=0xd43c3cb9;
*((unsigned int *)((unsigned long)context_ptr+0x000068d4+4*6))=0x307630cb;
*((unsigned int *)((unsigned long)context_ptr+0x000068d4+4*7))=0xf703d93a;
*((unsigned int *)((unsigned long)context_ptr+0x000068d4+4*8))=0x5c6e8f29;
*((unsigned int *)((unsigned long)context_ptr+0x000068d4+4*9))=0xd068aaf3;
*((unsigned int *)((unsigned long)context_ptr+0x000068d4+4*10))=0x6cdb5552;
*((unsigned int *)((unsigned long)context_ptr+0x000068d4+4*11))=0xdc576e5b;
*((unsigned int *)((unsigned long)context_ptr+0x000068d4+4*12))=0x8a9d8a81;
*((unsigned int *)((unsigned long)context_ptr+0x000068d4+4*13))=0x131f156b;
*((unsigned int *)((unsigned long)context_ptr+0x000068d4+4*14))=0xf5237446;
*((unsigned int *)((unsigned long)context_ptr+0x000068d4+4*15))=0x8c4e7a91;
*((unsigned int *)((unsigned long)context_ptr+0x000068d4+4*16))=0xfda918b9;
*((unsigned int *)((unsigned long)context_ptr+0x000068d4+4*17))=0xa2523e31;
*((unsigned int *)((unsigned long)context_ptr+0x000068d4+4*18))=0x91e7faa8;
*((unsigned int *)((unsigned long)context_ptr+0x000068d4+4*19))=0x8ba487ce;
*((unsigned int *)((unsigned long)context_ptr+0x000068d4+4*20))=0x1bd32178;
*((unsigned int *)((unsigned long)context_ptr+0x000068d4+4*21))=0xe4c71a69;
*((unsigned int *)((unsigned long)context_ptr+0x000068d4+4*22))=0xe849d553;
*((unsigned int *)((unsigned long)context_ptr+0x000068d4+4*23))=0x0004dbb1;
*((unsigned int *)((unsigned long)context_ptr+0x000038d0))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x000038d0+4*1))=0x00006644;
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
*((unsigned int *)((unsigned long)context_ptr+0x000008d0+4*1))=0x000068d4;
*((unsigned int *)((unsigned long)context_ptr+0x000008d0+4*2))=0x00006008;
*((unsigned int *)((unsigned long)context_ptr+0x000008d0+4*3))=0x0222005f;
*((unsigned int *)((unsigned long)context_ptr+0x000008d0+4*4))=0x05ed4786;
*((unsigned int *)((unsigned long)context_ptr+0x000008d0+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000001e6&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000063a0,"\x3a\x32\xb8\x24\x0b\x0c\x8a\xb9\x89\x2b\x66\x41\x17\x18\x96\xfe\xe1\x29\x2f\x15\x67\x7b\x7b\x8b\x2c\x54\xb0\x0a\x57\x92\x0b\xe6",32))
printf("strip: 3a32b8240b0c8ab9, Pass\n");
else
printf("strip: 3a32b8240b0c8ab9, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006028))=0x018a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006028+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006028+4*2))=0x02020060;
*((unsigned int *)((unsigned long)context_ptr+0x00006028+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x000062f8))=0x55442258;
*((unsigned int *)((unsigned long)context_ptr+0x000062f8+4*1))=0x50142252;
*((unsigned int *)((unsigned long)context_ptr+0x000062f8+4*2))=0x7c86ab4f;
*((unsigned int *)((unsigned long)context_ptr+0x000062f8+4*3))=0xd0de945c;
*((unsigned int *)((unsigned long)context_ptr+0x000062f8+4*4))=0xb3f5f966;
*((unsigned int *)((unsigned long)context_ptr+0x000062f8+4*5))=0x4bb2e51a;
*((unsigned int *)((unsigned long)context_ptr+0x000062f8+4*6))=0x5cc704c5;
*((unsigned int *)((unsigned long)context_ptr+0x000062f8+4*7))=0x82e78e54;
*((unsigned int *)((unsigned long)context_ptr+0x000062f8+4*8))=0xc95e7539;
*((unsigned int *)((unsigned long)context_ptr+0x000062f8+4*9))=0x8fee1d06;
*((unsigned int *)((unsigned long)context_ptr+0x000062f8+4*10))=0xe917a0fe;
*((unsigned int *)((unsigned long)context_ptr+0x000062f8+4*11))=0xde65ba3a;
*((unsigned int *)((unsigned long)context_ptr+0x000062f8+4*12))=0xc1cf93d5;
*((unsigned int *)((unsigned long)context_ptr+0x000062f8+4*13))=0xdcb5fca5;
*((unsigned int *)((unsigned long)context_ptr+0x000062f8+4*14))=0xf8ddd4c8;
*((unsigned int *)((unsigned long)context_ptr+0x000062f8+4*15))=0x410a51a5;
*((unsigned int *)((unsigned long)context_ptr+0x000062f8+4*16))=0x4426c5cc;
*((unsigned int *)((unsigned long)context_ptr+0x000062f8+4*17))=0x2e0c8825;
*((unsigned int *)((unsigned long)context_ptr+0x000062f8+4*18))=0xc220fc46;
*((unsigned int *)((unsigned long)context_ptr+0x000062f8+4*19))=0x94c103cd;
*((unsigned int *)((unsigned long)context_ptr+0x000062f8+4*20))=0xca969215;
*((unsigned int *)((unsigned long)context_ptr+0x000062f8+4*21))=0xb9fc5e89;
*((unsigned int *)((unsigned long)context_ptr+0x000062f8+4*22))=0xcfffd330;
*((unsigned int *)((unsigned long)context_ptr+0x000062f8+4*23))=0xeae85f76;
*((unsigned int *)((unsigned long)context_ptr+0x000038e8))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x000038e8+4*1))=0x00006664;
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
*((unsigned int *)((unsigned long)context_ptr+0x000008e8+4*1))=0x000062f8;
*((unsigned int *)((unsigned long)context_ptr+0x000008e8+4*2))=0x00006028;
*((unsigned int *)((unsigned long)context_ptr+0x000008e8+4*3))=0x02220060;
*((unsigned int *)((unsigned long)context_ptr+0x000008e8+4*4))=0x0787e123;
*((unsigned int *)((unsigned long)context_ptr+0x000008e8+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000001ec&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000064a4,"\xf0\x85\x0c\x6c\x2e\xcd\x6b\xaf\xfb\xe5\xfd\x70\x75\x71\x2a\x39\x9c\xe5\xfc\xaf\x5e\x31\x1b\xc5\xa7\xa4\xbc\x15\xe6\x92\x3d\xf7",32))
printf("strip: f0850c6c2ecd6baf, Pass\n");
else
printf("strip: f0850c6c2ecd6baf, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006684))=0x018a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006684+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006684+4*2))=0x02020061;
*((unsigned int *)((unsigned long)context_ptr+0x00006684+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x00006460))=0x0fecf66d;
*((unsigned int *)((unsigned long)context_ptr+0x00006460+4*1))=0x6bae227c;
*((unsigned int *)((unsigned long)context_ptr+0x00006460+4*2))=0xe3929afe;
*((unsigned int *)((unsigned long)context_ptr+0x00006460+4*3))=0xd1c33f53;
*((unsigned int *)((unsigned long)context_ptr+0x00006460+4*4))=0xb6e009ac;
*((unsigned int *)((unsigned long)context_ptr+0x00006460+4*5))=0x0518ef4e;
*((unsigned int *)((unsigned long)context_ptr+0x00006460+4*6))=0xe342d6cb;
*((unsigned int *)((unsigned long)context_ptr+0x00006460+4*7))=0x1240ab85;
*((unsigned int *)((unsigned long)context_ptr+0x00006460+4*8))=0xfda54339;
*((unsigned int *)((unsigned long)context_ptr+0x00006460+4*9))=0x1a866486;
*((unsigned int *)((unsigned long)context_ptr+0x00006460+4*10))=0xa4a4a8b6;
*((unsigned int *)((unsigned long)context_ptr+0x00006460+4*11))=0x5671ea22;
*((unsigned int *)((unsigned long)context_ptr+0x00006460+4*12))=0x13e45159;
*((unsigned int *)((unsigned long)context_ptr+0x00006460+4*13))=0x8719428f;
*((unsigned int *)((unsigned long)context_ptr+0x00006460+4*14))=0xeb5c598e;
*((unsigned int *)((unsigned long)context_ptr+0x00006460+4*15))=0xaab1cd8c;
*((unsigned int *)((unsigned long)context_ptr+0x00006460+4*16))=0x7774beef;
*((unsigned int *)((unsigned long)context_ptr+0x00006460+4*17))=0xc3cbd8ca;
*((unsigned int *)((unsigned long)context_ptr+0x00006460+4*18))=0x2f0f9b55;
*((unsigned int *)((unsigned long)context_ptr+0x00006460+4*19))=0xb00ff824;
*((unsigned int *)((unsigned long)context_ptr+0x00006460+4*20))=0xa63796d4;
*((unsigned int *)((unsigned long)context_ptr+0x00006460+4*21))=0xea4c4ec1;
*((unsigned int *)((unsigned long)context_ptr+0x00006460+4*22))=0x192c487d;
*((unsigned int *)((unsigned long)context_ptr+0x00006460+4*23))=0xbd410842;
*((unsigned int *)((unsigned long)context_ptr+0x00006460+4*24))=0x00000025;
*((unsigned int *)((unsigned long)context_ptr+0x00003900))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003900+4*1))=0x000067cc;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000900+4*1))=0x00006460;
*((unsigned int *)((unsigned long)context_ptr+0x00000900+4*2))=0x00006684;
*((unsigned int *)((unsigned long)context_ptr+0x00000900+4*3))=0x02220061;
*((unsigned int *)((unsigned long)context_ptr+0x00000900+4*4))=0x0bc01d63;
*((unsigned int *)((unsigned long)context_ptr+0x00000900+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000001f2&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006568,"\x74\xfd\x56\xf4\xeb\x7b\xee\xd8\xdd\xe8\x93\x78\x91\x81\x90\x4e\x37\x1d\x15\x3a\xbc\xa4\xf1\x82\x81\xe5\xd2\x13\x8f\x5b\xee\x82",32))
printf("strip: 74fd56f4eb7beed8, Pass\n");
else
printf("strip: 74fd56f4eb7beed8, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006564))=0x018a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006564+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006564+4*2))=0x02020062;
*((unsigned int *)((unsigned long)context_ptr+0x00006564+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x00006358))=0x2cd6a219;
*((unsigned int *)((unsigned long)context_ptr+0x00006358+4*1))=0xac095dad;
*((unsigned int *)((unsigned long)context_ptr+0x00006358+4*2))=0x2d3ccb6d;
*((unsigned int *)((unsigned long)context_ptr+0x00006358+4*3))=0x92e1c258;
*((unsigned int *)((unsigned long)context_ptr+0x00006358+4*4))=0x06292d9c;
*((unsigned int *)((unsigned long)context_ptr+0x00006358+4*5))=0x32ddc73a;
*((unsigned int *)((unsigned long)context_ptr+0x00006358+4*6))=0x94cf6522;
*((unsigned int *)((unsigned long)context_ptr+0x00006358+4*7))=0x064112c8;
*((unsigned int *)((unsigned long)context_ptr+0x00006358+4*8))=0x1872fa77;
*((unsigned int *)((unsigned long)context_ptr+0x00006358+4*9))=0xfe14dc11;
*((unsigned int *)((unsigned long)context_ptr+0x00006358+4*10))=0x12743a1b;
*((unsigned int *)((unsigned long)context_ptr+0x00006358+4*11))=0x2847bfc2;
*((unsigned int *)((unsigned long)context_ptr+0x00006358+4*12))=0x0163b0f1;
*((unsigned int *)((unsigned long)context_ptr+0x00006358+4*13))=0x47867c36;
*((unsigned int *)((unsigned long)context_ptr+0x00006358+4*14))=0xa12632ef;
*((unsigned int *)((unsigned long)context_ptr+0x00006358+4*15))=0x77d9e94f;
*((unsigned int *)((unsigned long)context_ptr+0x00006358+4*16))=0x5c864c7d;
*((unsigned int *)((unsigned long)context_ptr+0x00006358+4*17))=0x751e88fb;
*((unsigned int *)((unsigned long)context_ptr+0x00006358+4*18))=0x854a816a;
*((unsigned int *)((unsigned long)context_ptr+0x00006358+4*19))=0xb34ed2a6;
*((unsigned int *)((unsigned long)context_ptr+0x00006358+4*20))=0x9230cb56;
*((unsigned int *)((unsigned long)context_ptr+0x00006358+4*21))=0x8f6beb39;
*((unsigned int *)((unsigned long)context_ptr+0x00006358+4*22))=0x3886af0b;
*((unsigned int *)((unsigned long)context_ptr+0x00006358+4*23))=0x9561326b;
*((unsigned int *)((unsigned long)context_ptr+0x00006358+4*24))=0x00008120;
*((unsigned int *)((unsigned long)context_ptr+0x00003918))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003918+4*1))=0x000063bc;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000918+4*1))=0x00006358;
*((unsigned int *)((unsigned long)context_ptr+0x00000918+4*2))=0x00006564;
*((unsigned int *)((unsigned long)context_ptr+0x00000918+4*3))=0x02220062;
*((unsigned int *)((unsigned long)context_ptr+0x00000918+4*4))=0x0d84a6da;
*((unsigned int *)((unsigned long)context_ptr+0x00000918+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000001f8&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006588,"\x59\xa3\x02\x9f\x13\xbe\x13\x73\x56\x55\x6c\x1c\x5f\x9c\x56\x57\xa3\x30\xd0\xb3\xd1\xad\x7c\x9e\x57\xf8\x39\x06\xdb\x0f\x89\xb6",32))
printf("strip: 59a3029f13be1373, Pass\n");
else
printf("strip: 59a3029f13be1373, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000063dc))=0x018a0012;
*((unsigned int *)((unsigned long)context_ptr+0x000063dc+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000063dc+4*2))=0x02020063;
*((unsigned int *)((unsigned long)context_ptr+0x000063dc+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x00006058))=0x8804feb8;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*1))=0x9a661bf0;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*2))=0x82665eb3;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*3))=0xab2f5c0a;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*4))=0xcc0145a9;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*5))=0xdf00f908;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*6))=0xf23e3287;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*7))=0x58875e1c;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*8))=0x51766149;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*9))=0xeae0b620;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*10))=0x00b7a0a9;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*11))=0x2fc9a24d;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*12))=0x89869a1f;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*13))=0x3c1cd57b;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*14))=0x6292d397;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*15))=0xef365a59;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*16))=0x675ae2c6;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*17))=0xa2770536;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*18))=0xc53ef9f3;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*19))=0xe091282c;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*20))=0x4fb19856;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*21))=0x92a1940b;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*22))=0x8e2682b8;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*23))=0x699cb033;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*24))=0x00fe50e1;
*((unsigned int *)((unsigned long)context_ptr+0x00003930))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003930+4*1))=0x000067ec;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000930+4*1))=0x00006058;
*((unsigned int *)((unsigned long)context_ptr+0x00000930+4*2))=0x000063dc;
*((unsigned int *)((unsigned long)context_ptr+0x00000930+4*3))=0x02220063;
*((unsigned int *)((unsigned long)context_ptr+0x00000930+4*4))=0x08c25d3f;
*((unsigned int *)((unsigned long)context_ptr+0x00000930+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000001fe&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000064c4,"\x40\x9b\xe9\x09\xfd\xf2\x11\xf9\x3a\x52\x06\xd7\x7a\xe5\x6c\xfa\x50\xf9\x35\x86\xac\x96\xfe\xd9\xda\x55\xd0\x36\x05\xda\x73\x81",32))
printf("strip: 409be909fdf211f9, Pass\n");
else
printf("strip: 409be909fdf211f9, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x0000680c))=0x018a0012;
*((unsigned int *)((unsigned long)context_ptr+0x0000680c+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x0000680c+4*2))=0x02020064;
*((unsigned int *)((unsigned long)context_ptr+0x0000680c+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x000060bc))=0x57809741;
*((unsigned int *)((unsigned long)context_ptr+0x000060bc+4*1))=0x4726219e;
*((unsigned int *)((unsigned long)context_ptr+0x000060bc+4*2))=0xbe506bf3;
*((unsigned int *)((unsigned long)context_ptr+0x000060bc+4*3))=0xd0e827d7;
*((unsigned int *)((unsigned long)context_ptr+0x000060bc+4*4))=0xd67e325e;
*((unsigned int *)((unsigned long)context_ptr+0x000060bc+4*5))=0x9acb2b35;
*((unsigned int *)((unsigned long)context_ptr+0x000060bc+4*6))=0xf64f7eba;
*((unsigned int *)((unsigned long)context_ptr+0x000060bc+4*7))=0x0351aa3d;
*((unsigned int *)((unsigned long)context_ptr+0x000060bc+4*8))=0x83d2b685;
*((unsigned int *)((unsigned long)context_ptr+0x000060bc+4*9))=0x96945302;
*((unsigned int *)((unsigned long)context_ptr+0x000060bc+4*10))=0x2ab6f5ec;
*((unsigned int *)((unsigned long)context_ptr+0x000060bc+4*11))=0x12551fbd;
*((unsigned int *)((unsigned long)context_ptr+0x000060bc+4*12))=0x09b783cf;
*((unsigned int *)((unsigned long)context_ptr+0x000060bc+4*13))=0x287d342d;
*((unsigned int *)((unsigned long)context_ptr+0x000060bc+4*14))=0xf51b8f19;
*((unsigned int *)((unsigned long)context_ptr+0x000060bc+4*15))=0x4cc4fec6;
*((unsigned int *)((unsigned long)context_ptr+0x000060bc+4*16))=0x511f33cf;
*((unsigned int *)((unsigned long)context_ptr+0x000060bc+4*17))=0x11e31eb3;
*((unsigned int *)((unsigned long)context_ptr+0x000060bc+4*18))=0xc383b0c6;
*((unsigned int *)((unsigned long)context_ptr+0x000060bc+4*19))=0x4b26b18c;
*((unsigned int *)((unsigned long)context_ptr+0x000060bc+4*20))=0xbb96a18a;
*((unsigned int *)((unsigned long)context_ptr+0x000060bc+4*21))=0xf3f151b1;
*((unsigned int *)((unsigned long)context_ptr+0x000060bc+4*22))=0x1563754b;
*((unsigned int *)((unsigned long)context_ptr+0x000060bc+4*23))=0x873cd08c;
*((unsigned int *)((unsigned long)context_ptr+0x000060bc+4*24))=0x1a6b1c99;
*((unsigned int *)((unsigned long)context_ptr+0x00003948))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003948+4*1))=0x000064c4;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000948+4*1))=0x000060bc;
*((unsigned int *)((unsigned long)context_ptr+0x00000948+4*2))=0x0000680c;
*((unsigned int *)((unsigned long)context_ptr+0x00000948+4*3))=0x02220064;
*((unsigned int *)((unsigned long)context_ptr+0x00000948+4*4))=0x0a8043f4;
*((unsigned int *)((unsigned long)context_ptr+0x00000948+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000204&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000064e4,"\xc7\x9b\x32\xff\x7e\x96\x05\x97\xfe\x28\x9d\xcf\xd3\x83\xd9\x5f\x0d\x21\x88\x38\xcb\xab\x34\x11\x5d\x41\xf3\x63\x89\xaf\x85\x7d",32))
printf("strip: c79b32ff7e960597, Pass\n");
else
printf("strip: c79b32ff7e960597, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000064e4))=0x018a0012;
*((unsigned int *)((unsigned long)context_ptr+0x000064e4+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000064e4+4*2))=0x02020065;
*((unsigned int *)((unsigned long)context_ptr+0x000064e4+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x00006120))=0xa62710a4;
*((unsigned int *)((unsigned long)context_ptr+0x00006120+4*1))=0xe09408ae;
*((unsigned int *)((unsigned long)context_ptr+0x00006120+4*2))=0xa437a4a1;
*((unsigned int *)((unsigned long)context_ptr+0x00006120+4*3))=0xd13dd526;
*((unsigned int *)((unsigned long)context_ptr+0x00006120+4*4))=0x4d559806;
*((unsigned int *)((unsigned long)context_ptr+0x00006120+4*5))=0x2dfa3e9c;
*((unsigned int *)((unsigned long)context_ptr+0x00006120+4*6))=0xeb4fad8b;
*((unsigned int *)((unsigned long)context_ptr+0x00006120+4*7))=0x8f7037c7;
*((unsigned int *)((unsigned long)context_ptr+0x00006120+4*8))=0x4ebdc506;
*((unsigned int *)((unsigned long)context_ptr+0x00006120+4*9))=0xdd6f6aca;
*((unsigned int *)((unsigned long)context_ptr+0x00006120+4*10))=0x33bac74e;
*((unsigned int *)((unsigned long)context_ptr+0x00006120+4*11))=0x409c284b;
*((unsigned int *)((unsigned long)context_ptr+0x00006120+4*12))=0xc13e33ec;
*((unsigned int *)((unsigned long)context_ptr+0x00006120+4*13))=0xcb006e9b;
*((unsigned int *)((unsigned long)context_ptr+0x00006120+4*14))=0x30518855;
*((unsigned int *)((unsigned long)context_ptr+0x00006120+4*15))=0xd3b77fe4;
*((unsigned int *)((unsigned long)context_ptr+0x00006120+4*16))=0x0c17a467;
*((unsigned int *)((unsigned long)context_ptr+0x00006120+4*17))=0xf6f1fb9a;
*((unsigned int *)((unsigned long)context_ptr+0x00006120+4*18))=0x9db77395;
*((unsigned int *)((unsigned long)context_ptr+0x00006120+4*19))=0x4eabe8dc;
*((unsigned int *)((unsigned long)context_ptr+0x00006120+4*20))=0x14babd7f;
*((unsigned int *)((unsigned long)context_ptr+0x00006120+4*21))=0x6b32350b;
*((unsigned int *)((unsigned long)context_ptr+0x00006120+4*22))=0x214db00c;
*((unsigned int *)((unsigned long)context_ptr+0x00006120+4*23))=0xf2a1cab3;
*((unsigned int *)((unsigned long)context_ptr+0x00006120+4*24))=0x58ba54c5;
*((unsigned int *)((unsigned long)context_ptr+0x00006120+4*25))=0x000000f9;
*((unsigned int *)((unsigned long)context_ptr+0x00003960))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003960+4*1))=0x000063ec;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000960+4*1))=0x00006120;
*((unsigned int *)((unsigned long)context_ptr+0x00000960+4*2))=0x000064e4;
*((unsigned int *)((unsigned long)context_ptr+0x00000960+4*3))=0x02220065;
*((unsigned int *)((unsigned long)context_ptr+0x00000960+4*4))=0x0a6e4a31;
*((unsigned int *)((unsigned long)context_ptr+0x00000960+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000020a&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000065a8,"\xdf\xa7\x21\x76\x77\x27\x80\xc2\x9b\xdf\xce\xd3\x7f\x3e\x18\x84\x6d\x21\x68\xef\xe5\xfe\x63\xf2\x14\xd1\xe8\x0b\xd3\xe4\x23\x84",32))
printf("strip: dfa72176772780c2, Pass\n");
else
printf("strip: dfa72176772780c2, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000064f4))=0x018a0012;
*((unsigned int *)((unsigned long)context_ptr+0x000064f4+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000064f4+4*2))=0x02020066;
*((unsigned int *)((unsigned long)context_ptr+0x000064f4+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x00006188))=0x953c964d;
*((unsigned int *)((unsigned long)context_ptr+0x00006188+4*1))=0xc4f6e664;
*((unsigned int *)((unsigned long)context_ptr+0x00006188+4*2))=0x1bfac9d1;
*((unsigned int *)((unsigned long)context_ptr+0x00006188+4*3))=0xdf82e8ca;
*((unsigned int *)((unsigned long)context_ptr+0x00006188+4*4))=0x7bcd07cc;
*((unsigned int *)((unsigned long)context_ptr+0x00006188+4*5))=0x9798559b;
*((unsigned int *)((unsigned long)context_ptr+0x00006188+4*6))=0xa92e8025;
*((unsigned int *)((unsigned long)context_ptr+0x00006188+4*7))=0xf5975b0d;
*((unsigned int *)((unsigned long)context_ptr+0x00006188+4*8))=0x50652719;
*((unsigned int *)((unsigned long)context_ptr+0x00006188+4*9))=0xab21d3b5;
*((unsigned int *)((unsigned long)context_ptr+0x00006188+4*10))=0x4457e9cb;
*((unsigned int *)((unsigned long)context_ptr+0x00006188+4*11))=0xb29066bf;
*((unsigned int *)((unsigned long)context_ptr+0x00006188+4*12))=0xbbeebf4d;
*((unsigned int *)((unsigned long)context_ptr+0x00006188+4*13))=0x91ef7953;
*((unsigned int *)((unsigned long)context_ptr+0x00006188+4*14))=0xe85c801c;
*((unsigned int *)((unsigned long)context_ptr+0x00006188+4*15))=0xed092f8d;
*((unsigned int *)((unsigned long)context_ptr+0x00006188+4*16))=0x5d68a727;
*((unsigned int *)((unsigned long)context_ptr+0x00006188+4*17))=0x492f6eb8;
*((unsigned int *)((unsigned long)context_ptr+0x00006188+4*18))=0x73d19563;
*((unsigned int *)((unsigned long)context_ptr+0x00006188+4*19))=0xcc6156f1;
*((unsigned int *)((unsigned long)context_ptr+0x00006188+4*20))=0xa590ff5e;
*((unsigned int *)((unsigned long)context_ptr+0x00006188+4*21))=0x59b05688;
*((unsigned int *)((unsigned long)context_ptr+0x00006188+4*22))=0xa45a2316;
*((unsigned int *)((unsigned long)context_ptr+0x00006188+4*23))=0xb2225746;
*((unsigned int *)((unsigned long)context_ptr+0x00006188+4*24))=0xdc47ff0a;
*((unsigned int *)((unsigned long)context_ptr+0x00006188+4*25))=0x00009db1;
*((unsigned int *)((unsigned long)context_ptr+0x00003978))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003978+4*1))=0x00006574;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000978+4*1))=0x00006188;
*((unsigned int *)((unsigned long)context_ptr+0x00000978+4*2))=0x000064f4;
*((unsigned int *)((unsigned long)context_ptr+0x00000978+4*3))=0x02220066;
*((unsigned int *)((unsigned long)context_ptr+0x00000978+4*4))=0x0d21f812;
*((unsigned int *)((unsigned long)context_ptr+0x00000978+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000210&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000065c8,"\x0d\x54\x52\x4b\x47\x07\xe4\xc8\x20\x9f\x42\x61\xc9\x13\x92\xfe\x84\xbc\x1e\xa9\x4e\x1e\x0e\x6c\xe3\x8e\x8e\x77\x4e\xa1\xa1\xba",32))
printf("strip: 0d54524b4707e4c8, Pass\n");
else
printf("strip: 0d54524b4707e4c8, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006504))=0x018a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006504+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006504+4*2))=0x02020067;
*((unsigned int *)((unsigned long)context_ptr+0x00006504+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x000061f0))=0xe567adfd;
*((unsigned int *)((unsigned long)context_ptr+0x000061f0+4*1))=0x56783947;
*((unsigned int *)((unsigned long)context_ptr+0x000061f0+4*2))=0x93f05fe7;
*((unsigned int *)((unsigned long)context_ptr+0x000061f0+4*3))=0xa0196a0f;
*((unsigned int *)((unsigned long)context_ptr+0x000061f0+4*4))=0x28999185;
*((unsigned int *)((unsigned long)context_ptr+0x000061f0+4*5))=0xe3138470;
*((unsigned int *)((unsigned long)context_ptr+0x000061f0+4*6))=0x88ffe858;
*((unsigned int *)((unsigned long)context_ptr+0x000061f0+4*7))=0xc47a53ab;
*((unsigned int *)((unsigned long)context_ptr+0x000061f0+4*8))=0xa45ca6ef;
*((unsigned int *)((unsigned long)context_ptr+0x000061f0+4*9))=0xaf887086;
*((unsigned int *)((unsigned long)context_ptr+0x000061f0+4*10))=0x3a816526;
*((unsigned int *)((unsigned long)context_ptr+0x000061f0+4*11))=0x9e918587;
*((unsigned int *)((unsigned long)context_ptr+0x000061f0+4*12))=0x7d36bd50;
*((unsigned int *)((unsigned long)context_ptr+0x000061f0+4*13))=0xf74a42e3;
*((unsigned int *)((unsigned long)context_ptr+0x000061f0+4*14))=0x85550fd9;
*((unsigned int *)((unsigned long)context_ptr+0x000061f0+4*15))=0xa961ae3d;
*((unsigned int *)((unsigned long)context_ptr+0x000061f0+4*16))=0x59e90d91;
*((unsigned int *)((unsigned long)context_ptr+0x000061f0+4*17))=0x08ebea00;
*((unsigned int *)((unsigned long)context_ptr+0x000061f0+4*18))=0x34073ef3;
*((unsigned int *)((unsigned long)context_ptr+0x000061f0+4*19))=0xf097511e;
*((unsigned int *)((unsigned long)context_ptr+0x000061f0+4*20))=0x68b70563;
*((unsigned int *)((unsigned long)context_ptr+0x000061f0+4*21))=0x35def350;
*((unsigned int *)((unsigned long)context_ptr+0x000061f0+4*22))=0x9ccf1f36;
*((unsigned int *)((unsigned long)context_ptr+0x000061f0+4*23))=0x784cc6ac;
*((unsigned int *)((unsigned long)context_ptr+0x000061f0+4*24))=0x5e3e5210;
*((unsigned int *)((unsigned long)context_ptr+0x000061f0+4*25))=0x00063d38;
*((unsigned int *)((unsigned long)context_ptr+0x00003990))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003990+4*1))=0x00006594;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000990+4*1))=0x000061f0;
*((unsigned int *)((unsigned long)context_ptr+0x00000990+4*2))=0x00006504;
*((unsigned int *)((unsigned long)context_ptr+0x00000990+4*3))=0x02220067;
*((unsigned int *)((unsigned long)context_ptr+0x00000990+4*4))=0x02557dbe;
*((unsigned int *)((unsigned long)context_ptr+0x00000990+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000216&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000062b8,"\xf2\x2e\x3e\xd7\x3a\x1d\xc9\x9f\x91\x1f\xf7\x45\x4c\xf9\x90\x37\xd3\xa3\xd8\x1f\x83\x41\x36\x06\x26\xd9\xd5\x34\x24\x21\x5c\x98",32))
printf("strip: f22e3ed73a1dc99f, Pass\n");
else
printf("strip: f22e3ed73a1dc99f, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006514))=0x018a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006514+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006514+4*2))=0x02020068;
*((unsigned int *)((unsigned long)context_ptr+0x00006514+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x00006258))=0xc2ebff0c;
*((unsigned int *)((unsigned long)context_ptr+0x00006258+4*1))=0xf3bb5c45;
*((unsigned int *)((unsigned long)context_ptr+0x00006258+4*2))=0xb17dd974;
*((unsigned int *)((unsigned long)context_ptr+0x00006258+4*3))=0xc4afbde7;
*((unsigned int *)((unsigned long)context_ptr+0x00006258+4*4))=0x809414d9;
*((unsigned int *)((unsigned long)context_ptr+0x00006258+4*5))=0x98522da7;
*((unsigned int *)((unsigned long)context_ptr+0x00006258+4*6))=0x66153cc5;
*((unsigned int *)((unsigned long)context_ptr+0x00006258+4*7))=0x03486f86;
*((unsigned int *)((unsigned long)context_ptr+0x00006258+4*8))=0xb00bb6b0;
*((unsigned int *)((unsigned long)context_ptr+0x00006258+4*9))=0xbfcc1a3d;
*((unsigned int *)((unsigned long)context_ptr+0x00006258+4*10))=0x2563798b;
*((unsigned int *)((unsigned long)context_ptr+0x00006258+4*11))=0x1f15154c;
*((unsigned int *)((unsigned long)context_ptr+0x00006258+4*12))=0x8fec192e;
*((unsigned int *)((unsigned long)context_ptr+0x00006258+4*13))=0x3b82fe58;
*((unsigned int *)((unsigned long)context_ptr+0x00006258+4*14))=0xd1e0cc87;
*((unsigned int *)((unsigned long)context_ptr+0x00006258+4*15))=0xbcb72757;
*((unsigned int *)((unsigned long)context_ptr+0x00006258+4*16))=0x7fa0aa98;
*((unsigned int *)((unsigned long)context_ptr+0x00006258+4*17))=0x3452fa28;
*((unsigned int *)((unsigned long)context_ptr+0x00006258+4*18))=0x551512ac;
*((unsigned int *)((unsigned long)context_ptr+0x00006258+4*19))=0x3f3d63f4;
*((unsigned int *)((unsigned long)context_ptr+0x00006258+4*20))=0x019d0e6f;
*((unsigned int *)((unsigned long)context_ptr+0x00006258+4*21))=0x6cff9417;
*((unsigned int *)((unsigned long)context_ptr+0x00006258+4*22))=0xf3acf373;
*((unsigned int *)((unsigned long)context_ptr+0x00006258+4*23))=0x47906f27;
*((unsigned int *)((unsigned long)context_ptr+0x00006258+4*24))=0xa17ac71b;
*((unsigned int *)((unsigned long)context_ptr+0x00006258+4*25))=0xf6e7071a;
*((unsigned int *)((unsigned long)context_ptr+0x000039a8))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x000039a8+4*1))=0x000065b4;
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
*((unsigned int *)((unsigned long)context_ptr+0x000009a8+4*1))=0x00006258;
*((unsigned int *)((unsigned long)context_ptr+0x000009a8+4*2))=0x00006514;
*((unsigned int *)((unsigned long)context_ptr+0x000009a8+4*3))=0x02220068;
*((unsigned int *)((unsigned long)context_ptr+0x000009a8+4*4))=0x06449cb2;
*((unsigned int *)((unsigned long)context_ptr+0x000009a8+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000021c&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000062d8,"\xb9\x9f\x6d\xa1\xba\x7b\xfe\x20\xbf\xc9\xc3\xe7\x54\x96\x8f\x60\x3f\x3b\x07\x30\x2a\x20\xe6\xba\xaa\x53\xe7\x3f\x5c\xd4\x00\x19",32))
printf("strip: b99f6da1ba7bfe20, Pass\n");
else
printf("strip: b99f6da1ba7bfe20, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000065d4))=0x018a0012;
*((unsigned int *)((unsigned long)context_ptr+0x000065d4+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000065d4+4*2))=0x02020069;
*((unsigned int *)((unsigned long)context_ptr+0x000065d4+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x00006934))=0x0f8821f7;
*((unsigned int *)((unsigned long)context_ptr+0x00006934+4*1))=0x3c28d744;
*((unsigned int *)((unsigned long)context_ptr+0x00006934+4*2))=0x223fd1ec;
*((unsigned int *)((unsigned long)context_ptr+0x00006934+4*3))=0xbc5458ea;
*((unsigned int *)((unsigned long)context_ptr+0x00006934+4*4))=0xe63cc87c;
*((unsigned int *)((unsigned long)context_ptr+0x00006934+4*5))=0x03352b82;
*((unsigned int *)((unsigned long)context_ptr+0x00006934+4*6))=0xe20fd5aa;
*((unsigned int *)((unsigned long)context_ptr+0x00006934+4*7))=0xbb30bec6;
*((unsigned int *)((unsigned long)context_ptr+0x00006934+4*8))=0xd5e44f5e;
*((unsigned int *)((unsigned long)context_ptr+0x00006934+4*9))=0x3b83e703;
*((unsigned int *)((unsigned long)context_ptr+0x00006934+4*10))=0x00e3c966;
*((unsigned int *)((unsigned long)context_ptr+0x00006934+4*11))=0x8a2be094;
*((unsigned int *)((unsigned long)context_ptr+0x00006934+4*12))=0x13bbdc2a;
*((unsigned int *)((unsigned long)context_ptr+0x00006934+4*13))=0xd3cea7f4;
*((unsigned int *)((unsigned long)context_ptr+0x00006934+4*14))=0x39e12861;
*((unsigned int *)((unsigned long)context_ptr+0x00006934+4*15))=0x5feb27e5;
*((unsigned int *)((unsigned long)context_ptr+0x00006934+4*16))=0x0a0dbe79;
*((unsigned int *)((unsigned long)context_ptr+0x00006934+4*17))=0x05aa128f;
*((unsigned int *)((unsigned long)context_ptr+0x00006934+4*18))=0x98b86e1c;
*((unsigned int *)((unsigned long)context_ptr+0x00006934+4*19))=0x2ab5d46b;
*((unsigned int *)((unsigned long)context_ptr+0x00006934+4*20))=0xe6751116;
*((unsigned int *)((unsigned long)context_ptr+0x00006934+4*21))=0x0c5f65d9;
*((unsigned int *)((unsigned long)context_ptr+0x00006934+4*22))=0xcb3be340;
*((unsigned int *)((unsigned long)context_ptr+0x00006934+4*23))=0x0df89183;
*((unsigned int *)((unsigned long)context_ptr+0x00006934+4*24))=0xfff06e05;
*((unsigned int *)((unsigned long)context_ptr+0x00006934+4*25))=0x4653cc64;
*((unsigned int *)((unsigned long)context_ptr+0x00006934+4*26))=0x000000fb;
*((unsigned int *)((unsigned long)context_ptr+0x000039c0))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x000039c0+4*1))=0x0000640c;
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
*((unsigned int *)((unsigned long)context_ptr+0x000009c0+4*1))=0x00006934;
*((unsigned int *)((unsigned long)context_ptr+0x000009c0+4*2))=0x000065d4;
*((unsigned int *)((unsigned long)context_ptr+0x000009c0+4*3))=0x02220069;
*((unsigned int *)((unsigned long)context_ptr+0x000009c0+4*4))=0x04b620b4;
*((unsigned int *)((unsigned long)context_ptr+0x000009c0+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000222&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006524,"\xe5\xda\xcd\xd5\x6b\x27\xb4\x1a\xd5\xa9\x32\x64\xdb\x95\xcb\x67\x59\x2a\xbd\x80\x87\xf8\x8b\x10\xdf\x45\x1e\x1c\xa2\x2a\xbf\xea",32))
printf("strip: e5dacdd56b27b41a, Pass\n");
else
printf("strip: e5dacdd56b27b41a, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x0000642c))=0x018a0012;
*((unsigned int *)((unsigned long)context_ptr+0x0000642c+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x0000642c+4*2))=0x0202006a;
*((unsigned int *)((unsigned long)context_ptr+0x0000642c+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x0000681c))=0x39df63e7;
*((unsigned int *)((unsigned long)context_ptr+0x0000681c+4*1))=0x1806fb9f;
*((unsigned int *)((unsigned long)context_ptr+0x0000681c+4*2))=0x8fec395e;
*((unsigned int *)((unsigned long)context_ptr+0x0000681c+4*3))=0xa6132433;
*((unsigned int *)((unsigned long)context_ptr+0x0000681c+4*4))=0x6ac70adc;
*((unsigned int *)((unsigned long)context_ptr+0x0000681c+4*5))=0xbacb2f08;
*((unsigned int *)((unsigned long)context_ptr+0x0000681c+4*6))=0x52bfb066;
*((unsigned int *)((unsigned long)context_ptr+0x0000681c+4*7))=0xb9d9f37f;
*((unsigned int *)((unsigned long)context_ptr+0x0000681c+4*8))=0x31c47899;
*((unsigned int *)((unsigned long)context_ptr+0x0000681c+4*9))=0x0f06b14a;
*((unsigned int *)((unsigned long)context_ptr+0x0000681c+4*10))=0xabb63cc9;
*((unsigned int *)((unsigned long)context_ptr+0x0000681c+4*11))=0x01c3dc01;
*((unsigned int *)((unsigned long)context_ptr+0x0000681c+4*12))=0x73e5dc05;
*((unsigned int *)((unsigned long)context_ptr+0x0000681c+4*13))=0xb06f2c27;
*((unsigned int *)((unsigned long)context_ptr+0x0000681c+4*14))=0xc310c08e;
*((unsigned int *)((unsigned long)context_ptr+0x0000681c+4*15))=0x47d2ce45;
*((unsigned int *)((unsigned long)context_ptr+0x0000681c+4*16))=0xc9f501d3;
*((unsigned int *)((unsigned long)context_ptr+0x0000681c+4*17))=0x65c6d483;
*((unsigned int *)((unsigned long)context_ptr+0x0000681c+4*18))=0xd922a088;
*((unsigned int *)((unsigned long)context_ptr+0x0000681c+4*19))=0xfced0d0e;
*((unsigned int *)((unsigned long)context_ptr+0x0000681c+4*20))=0xff01479f;
*((unsigned int *)((unsigned long)context_ptr+0x0000681c+4*21))=0x2284a32e;
*((unsigned int *)((unsigned long)context_ptr+0x0000681c+4*22))=0xbf854af4;
*((unsigned int *)((unsigned long)context_ptr+0x0000681c+4*23))=0x8b7acaf0;
*((unsigned int *)((unsigned long)context_ptr+0x0000681c+4*24))=0x59437a74;
*((unsigned int *)((unsigned long)context_ptr+0x0000681c+4*25))=0x4fd15b42;
*((unsigned int *)((unsigned long)context_ptr+0x0000681c+4*26))=0x00003c47;
*((unsigned int *)((unsigned long)context_ptr+0x000039d8))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x000039d8+4*1))=0x00006524;
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
*((unsigned int *)((unsigned long)context_ptr+0x000009d8+4*1))=0x0000681c;
*((unsigned int *)((unsigned long)context_ptr+0x000009d8+4*2))=0x0000642c;
*((unsigned int *)((unsigned long)context_ptr+0x000009d8+4*3))=0x0222006a;
*((unsigned int *)((unsigned long)context_ptr+0x000009d8+4*4))=0x0836c5ce;
*((unsigned int *)((unsigned long)context_ptr+0x000009d8+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000228&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006440,"\xc9\x29\x2c\x5f\xd3\xdc\xc1\x96\x36\x11\x9e\xc3\x16\x2f\xc1\x4c\x8b\xe4\xfa\xc2\x70\x03\x77\x88\x88\x9b\x3f\xa1\xa2\x18\x1e\xec",32))
printf("strip: c9292c5fd3dcc196, Pass\n");
else
printf("strip: c9292c5fd3dcc196, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006038))=0x018a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006038+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006038+4*2))=0x0202006b;
*((unsigned int *)((unsigned long)context_ptr+0x00006038+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x000069a0))=0x993ca260;
*((unsigned int *)((unsigned long)context_ptr+0x000069a0+4*1))=0x8c94a455;
*((unsigned int *)((unsigned long)context_ptr+0x000069a0+4*2))=0x2859dc1e;
*((unsigned int *)((unsigned long)context_ptr+0x000069a0+4*3))=0x7337d8c2;
*((unsigned int *)((unsigned long)context_ptr+0x000069a0+4*4))=0xa7655795;
*((unsigned int *)((unsigned long)context_ptr+0x000069a0+4*5))=0x05e0a0ef;
*((unsigned int *)((unsigned long)context_ptr+0x000069a0+4*6))=0x72de848a;
*((unsigned int *)((unsigned long)context_ptr+0x000069a0+4*7))=0x5e7abdc0;
*((unsigned int *)((unsigned long)context_ptr+0x000069a0+4*8))=0xe0816722;
*((unsigned int *)((unsigned long)context_ptr+0x000069a0+4*9))=0x2f1049bd;
*((unsigned int *)((unsigned long)context_ptr+0x000069a0+4*10))=0xc7d129c1;
*((unsigned int *)((unsigned long)context_ptr+0x000069a0+4*11))=0x8274542d;
*((unsigned int *)((unsigned long)context_ptr+0x000069a0+4*12))=0x1b1e16c4;
*((unsigned int *)((unsigned long)context_ptr+0x000069a0+4*13))=0xcf1b67b4;
*((unsigned int *)((unsigned long)context_ptr+0x000069a0+4*14))=0x35d1d21f;
*((unsigned int *)((unsigned long)context_ptr+0x000069a0+4*15))=0xca525d9b;
*((unsigned int *)((unsigned long)context_ptr+0x000069a0+4*16))=0x5e91474c;
*((unsigned int *)((unsigned long)context_ptr+0x000069a0+4*17))=0xedaebd92;
*((unsigned int *)((unsigned long)context_ptr+0x000069a0+4*18))=0xe8f3810c;
*((unsigned int *)((unsigned long)context_ptr+0x000069a0+4*19))=0x8c542f83;
*((unsigned int *)((unsigned long)context_ptr+0x000069a0+4*20))=0xd4d251bc;
*((unsigned int *)((unsigned long)context_ptr+0x000069a0+4*21))=0xf58aa1f8;
*((unsigned int *)((unsigned long)context_ptr+0x000069a0+4*22))=0xf96528e3;
*((unsigned int *)((unsigned long)context_ptr+0x000069a0+4*23))=0xb0884118;
*((unsigned int *)((unsigned long)context_ptr+0x000069a0+4*24))=0x31e55685;
*((unsigned int *)((unsigned long)context_ptr+0x000069a0+4*25))=0xc7ec0c3f;
*((unsigned int *)((unsigned long)context_ptr+0x000069a0+4*26))=0x008f5542;
*((unsigned int *)((unsigned long)context_ptr+0x000039f0))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x000039f0+4*1))=0x0000643c;
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
*((unsigned int *)((unsigned long)context_ptr+0x000009f0+4*1))=0x000069a0;
*((unsigned int *)((unsigned long)context_ptr+0x000009f0+4*2))=0x00006038;
*((unsigned int *)((unsigned long)context_ptr+0x000009f0+4*3))=0x0222006b;
*((unsigned int *)((unsigned long)context_ptr+0x000009f0+4*4))=0x0ac5a1ea;
*((unsigned int *)((unsigned long)context_ptr+0x000009f0+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000022e&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006544,"\x79\x75\x83\x5f\x8f\x25\xf0\x5f\x3e\x3b\x35\x02\x92\xdb\x01\x60\x43\xe9\x8c\xe2\x42\x25\xfa\x14\xe6\x49\x10\x96\x76\x3d\xe9\x42",32))
printf("strip: 7975835f8f25f05f, Pass\n");
else
printf("strip: 7975835f8f25f05f, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006048))=0x018a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006048+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006048+4*2))=0x0202006c;
*((unsigned int *)((unsigned long)context_ptr+0x00006048+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x00006694))=0x0e6d0441;
*((unsigned int *)((unsigned long)context_ptr+0x00006694+4*1))=0xfbe2799a;
*((unsigned int *)((unsigned long)context_ptr+0x00006694+4*2))=0xac176e20;
*((unsigned int *)((unsigned long)context_ptr+0x00006694+4*3))=0xdc26f88c;
*((unsigned int *)((unsigned long)context_ptr+0x00006694+4*4))=0x71c65d7b;
*((unsigned int *)((unsigned long)context_ptr+0x00006694+4*5))=0x76f7f69b;
*((unsigned int *)((unsigned long)context_ptr+0x00006694+4*6))=0x3b946332;
*((unsigned int *)((unsigned long)context_ptr+0x00006694+4*7))=0xee461c0a;
*((unsigned int *)((unsigned long)context_ptr+0x00006694+4*8))=0x7ba1fbfe;
*((unsigned int *)((unsigned long)context_ptr+0x00006694+4*9))=0x4c8f9bce;
*((unsigned int *)((unsigned long)context_ptr+0x00006694+4*10))=0xc8fefcf4;
*((unsigned int *)((unsigned long)context_ptr+0x00006694+4*11))=0xbe668afd;
*((unsigned int *)((unsigned long)context_ptr+0x00006694+4*12))=0x86bb680a;
*((unsigned int *)((unsigned long)context_ptr+0x00006694+4*13))=0x1fdf8107;
*((unsigned int *)((unsigned long)context_ptr+0x00006694+4*14))=0xc5995c3a;
*((unsigned int *)((unsigned long)context_ptr+0x00006694+4*15))=0xb5011898;
*((unsigned int *)((unsigned long)context_ptr+0x00006694+4*16))=0x2b846429;
*((unsigned int *)((unsigned long)context_ptr+0x00006694+4*17))=0x14778fb3;
*((unsigned int *)((unsigned long)context_ptr+0x00006694+4*18))=0x00e07d7a;
*((unsigned int *)((unsigned long)context_ptr+0x00006694+4*19))=0x232040bc;
*((unsigned int *)((unsigned long)context_ptr+0x00006694+4*20))=0x4977132c;
*((unsigned int *)((unsigned long)context_ptr+0x00006694+4*21))=0x91baa04f;
*((unsigned int *)((unsigned long)context_ptr+0x00006694+4*22))=0xfed21933;
*((unsigned int *)((unsigned long)context_ptr+0x00006694+4*23))=0x1510973c;
*((unsigned int *)((unsigned long)context_ptr+0x00006694+4*24))=0x62bcbe1a;
*((unsigned int *)((unsigned long)context_ptr+0x00006694+4*25))=0x65c529fc;
*((unsigned int *)((unsigned long)context_ptr+0x00006694+4*26))=0x8d3704be;
*((unsigned int *)((unsigned long)context_ptr+0x00003a08))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003a08+4*1))=0x00006544;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000a08+4*1))=0x00006694;
*((unsigned int *)((unsigned long)context_ptr+0x00000a08+4*2))=0x00006048;
*((unsigned int *)((unsigned long)context_ptr+0x00000a08+4*3))=0x0222006c;
*((unsigned int *)((unsigned long)context_ptr+0x00000a08+4*4))=0x03585fd7;
*((unsigned int *)((unsigned long)context_ptr+0x00000a08+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000234&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000067ac,"\xb1\xcb\xd2\x04\xb3\xdc\xfa\x39\xb3\xfa\xb6\xf1\x60\x90\x3a\x6d\x15\x6f\xa6\xcc\x6f\x13\x15\xe0\xd5\x80\xa5\x49\x7f\xd5\xc4\x88",32))
printf("strip: b1cbd204b3dcfa39, Pass\n");
else
printf("strip: b1cbd204b3dcfa39, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006018))=0x018a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006018+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006018+4*2))=0x0202006d;
*((unsigned int *)((unsigned long)context_ptr+0x00006018+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x00006700))=0xe6dcad3a;
*((unsigned int *)((unsigned long)context_ptr+0x00006700+4*1))=0x5db2be0c;
*((unsigned int *)((unsigned long)context_ptr+0x00006700+4*2))=0xe1332b9a;
*((unsigned int *)((unsigned long)context_ptr+0x00006700+4*3))=0xb9afbc42;
*((unsigned int *)((unsigned long)context_ptr+0x00006700+4*4))=0x980e8a47;
*((unsigned int *)((unsigned long)context_ptr+0x00006700+4*5))=0x32b6f31d;
*((unsigned int *)((unsigned long)context_ptr+0x00006700+4*6))=0x9a10747f;
*((unsigned int *)((unsigned long)context_ptr+0x00006700+4*7))=0x22155732;
*((unsigned int *)((unsigned long)context_ptr+0x00006700+4*8))=0xaf0375a7;
*((unsigned int *)((unsigned long)context_ptr+0x00006700+4*9))=0x80c037bd;
*((unsigned int *)((unsigned long)context_ptr+0x00006700+4*10))=0x2eb81a37;
*((unsigned int *)((unsigned long)context_ptr+0x00006700+4*11))=0xe09bdeb3;
*((unsigned int *)((unsigned long)context_ptr+0x00006700+4*12))=0xfd9cd956;
*((unsigned int *)((unsigned long)context_ptr+0x00006700+4*13))=0xb36ba076;
*((unsigned int *)((unsigned long)context_ptr+0x00006700+4*14))=0x05d91b31;
*((unsigned int *)((unsigned long)context_ptr+0x00006700+4*15))=0x2a92eb59;
*((unsigned int *)((unsigned long)context_ptr+0x00006700+4*16))=0x9d73e272;
*((unsigned int *)((unsigned long)context_ptr+0x00006700+4*17))=0x47b1d068;
*((unsigned int *)((unsigned long)context_ptr+0x00006700+4*18))=0x9254934b;
*((unsigned int *)((unsigned long)context_ptr+0x00006700+4*19))=0x82dff9c3;
*((unsigned int *)((unsigned long)context_ptr+0x00006700+4*20))=0x5a6e3058;
*((unsigned int *)((unsigned long)context_ptr+0x00006700+4*21))=0xe0d2b147;
*((unsigned int *)((unsigned long)context_ptr+0x00006700+4*22))=0x7334e5f9;
*((unsigned int *)((unsigned long)context_ptr+0x00006700+4*23))=0x349587fa;
*((unsigned int *)((unsigned long)context_ptr+0x00006700+4*24))=0x4f0e5093;
*((unsigned int *)((unsigned long)context_ptr+0x00006700+4*25))=0x80aadcf4;
*((unsigned int *)((unsigned long)context_ptr+0x00006700+4*26))=0x77415bc3;
*((unsigned int *)((unsigned long)context_ptr+0x00006700+4*27))=0x0000007a;
*((unsigned int *)((unsigned long)context_ptr+0x00003a20))=0x04c00020;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000a20+4*1))=0x00006700;
*((unsigned int *)((unsigned long)context_ptr+0x00000a20+4*2))=0x00006018;
*((unsigned int *)((unsigned long)context_ptr+0x00000a20+4*3))=0x0222006d;
*((unsigned int *)((unsigned long)context_ptr+0x00000a20+4*4))=0x0b5c9e93;
*((unsigned int *)((unsigned long)context_ptr+0x00000a20+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000023a&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006644,"\xc8\x94\x38\xa5\x37\xbe\x69\x06\x51\xa2\x11\x8c\x9a\x79\x8d\x78\x80\xef\x9d\xaa\x79\x2c\x7b\x82\x68\x9d\x75\x8c\x77\xbf\x20\xf5",32))
printf("strip: c89438a537be6906, Pass\n");
else
printf("strip: c89438a537be6906, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006008))=0x018a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006008+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006008+4*2))=0x0202006e;
*((unsigned int *)((unsigned long)context_ptr+0x00006008+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x000065e4))=0x4105aa35;
*((unsigned int *)((unsigned long)context_ptr+0x000065e4+4*1))=0x6ef4b2db;
*((unsigned int *)((unsigned long)context_ptr+0x000065e4+4*2))=0xe4cebf1f;
*((unsigned int *)((unsigned long)context_ptr+0x000065e4+4*3))=0x770019af;
*((unsigned int *)((unsigned long)context_ptr+0x000065e4+4*4))=0xee1f29c8;
*((unsigned int *)((unsigned long)context_ptr+0x000065e4+4*5))=0xe7716dbd;
*((unsigned int *)((unsigned long)context_ptr+0x000065e4+4*6))=0x9b8f08be;
*((unsigned int *)((unsigned long)context_ptr+0x000065e4+4*7))=0x9093b34d;
*((unsigned int *)((unsigned long)context_ptr+0x000065e4+4*8))=0x054e62ae;
*((unsigned int *)((unsigned long)context_ptr+0x000065e4+4*9))=0x42cddbb8;
*((unsigned int *)((unsigned long)context_ptr+0x000065e4+4*10))=0xa54ceabd;
*((unsigned int *)((unsigned long)context_ptr+0x000065e4+4*11))=0xc24728bf;
*((unsigned int *)((unsigned long)context_ptr+0x000065e4+4*12))=0x290c2ea2;
*((unsigned int *)((unsigned long)context_ptr+0x000065e4+4*13))=0xd052be32;
*((unsigned int *)((unsigned long)context_ptr+0x000065e4+4*14))=0x03dd4042;
*((unsigned int *)((unsigned long)context_ptr+0x000065e4+4*15))=0xac7cea4b;
*((unsigned int *)((unsigned long)context_ptr+0x000065e4+4*16))=0xa3baf79a;
*((unsigned int *)((unsigned long)context_ptr+0x000065e4+4*17))=0x4d9a034d;
*((unsigned int *)((unsigned long)context_ptr+0x000065e4+4*18))=0xc1c0d6c2;
*((unsigned int *)((unsigned long)context_ptr+0x000065e4+4*19))=0xeb77a6f3;
*((unsigned int *)((unsigned long)context_ptr+0x000065e4+4*20))=0x25234784;
*((unsigned int *)((unsigned long)context_ptr+0x000065e4+4*21))=0x962b2d19;
*((unsigned int *)((unsigned long)context_ptr+0x000065e4+4*22))=0xa043f804;
*((unsigned int *)((unsigned long)context_ptr+0x000065e4+4*23))=0xa7ee83f0;
*((unsigned int *)((unsigned long)context_ptr+0x000065e4+4*24))=0x4133fcad;
*((unsigned int *)((unsigned long)context_ptr+0x000065e4+4*25))=0x33189192;
*((unsigned int *)((unsigned long)context_ptr+0x000065e4+4*26))=0xff19855d;
*((unsigned int *)((unsigned long)context_ptr+0x000065e4+4*27))=0x0000cbf1;
*((unsigned int *)((unsigned long)context_ptr+0x00003a38))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003a38+4*1))=0x00006770;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000a38+4*1))=0x000065e4;
*((unsigned int *)((unsigned long)context_ptr+0x00000a38+4*2))=0x00006008;
*((unsigned int *)((unsigned long)context_ptr+0x00000a38+4*3))=0x0222006e;
*((unsigned int *)((unsigned long)context_ptr+0x00000a38+4*4))=0x0d845c44;
*((unsigned int *)((unsigned long)context_ptr+0x00000a38+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000240&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006664,"\x73\xb7\x44\xa1\x4a\x6a\x8b\x05\x87\xe0\xe9\x1c\x50\xd5\x4c\x46\x98\x25\xe1\x9c\x20\x61\xfe\xa1\x97\x4f\x49\x82\x5a\x9f\x36\x24",32))
printf("strip: 73b744a14a6a8b05, Pass\n");
else
printf("strip: 73b744a14a6a8b05, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006028))=0x018a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006028+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006028+4*2))=0x0202006f;
*((unsigned int *)((unsigned long)context_ptr+0x00006028+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x000062e0))=0x37238fa9;
*((unsigned int *)((unsigned long)context_ptr+0x000062e0+4*1))=0xead897fb;
*((unsigned int *)((unsigned long)context_ptr+0x000062e0+4*2))=0xad51787c;
*((unsigned int *)((unsigned long)context_ptr+0x000062e0+4*3))=0xa41cd3f1;
*((unsigned int *)((unsigned long)context_ptr+0x000062e0+4*4))=0xfa197161;
*((unsigned int *)((unsigned long)context_ptr+0x000062e0+4*5))=0xd4c56373;
*((unsigned int *)((unsigned long)context_ptr+0x000062e0+4*6))=0xa43f6aa8;
*((unsigned int *)((unsigned long)context_ptr+0x000062e0+4*7))=0xe11dae58;
*((unsigned int *)((unsigned long)context_ptr+0x000062e0+4*8))=0x5153bbe1;
*((unsigned int *)((unsigned long)context_ptr+0x000062e0+4*9))=0x71b04b96;
*((unsigned int *)((unsigned long)context_ptr+0x000062e0+4*10))=0x7edb0348;
*((unsigned int *)((unsigned long)context_ptr+0x000062e0+4*11))=0x8ac07902;
*((unsigned int *)((unsigned long)context_ptr+0x000062e0+4*12))=0xa56e6462;
*((unsigned int *)((unsigned long)context_ptr+0x000062e0+4*13))=0xee1ecefa;
*((unsigned int *)((unsigned long)context_ptr+0x000062e0+4*14))=0x95f9654b;
*((unsigned int *)((unsigned long)context_ptr+0x000062e0+4*15))=0x2eeae00b;
*((unsigned int *)((unsigned long)context_ptr+0x000062e0+4*16))=0x4cfee03f;
*((unsigned int *)((unsigned long)context_ptr+0x000062e0+4*17))=0xbcfce445;
*((unsigned int *)((unsigned long)context_ptr+0x000062e0+4*18))=0xc3f85b25;
*((unsigned int *)((unsigned long)context_ptr+0x000062e0+4*19))=0x3e6e8251;
*((unsigned int *)((unsigned long)context_ptr+0x000062e0+4*20))=0x0e6506a3;
*((unsigned int *)((unsigned long)context_ptr+0x000062e0+4*21))=0xd0f8d3f1;
*((unsigned int *)((unsigned long)context_ptr+0x000062e0+4*22))=0x187272a0;
*((unsigned int *)((unsigned long)context_ptr+0x000062e0+4*23))=0xf85f4226;
*((unsigned int *)((unsigned long)context_ptr+0x000062e0+4*24))=0x4f612737;
*((unsigned int *)((unsigned long)context_ptr+0x000062e0+4*25))=0x4f18636b;
*((unsigned int *)((unsigned long)context_ptr+0x000062e0+4*26))=0x4beb1745;
*((unsigned int *)((unsigned long)context_ptr+0x000062e0+4*27))=0x00b6f559;
*((unsigned int *)((unsigned long)context_ptr+0x00003a50))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003a50+4*1))=0x00006654;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000a50+4*1))=0x000062e0;
*((unsigned int *)((unsigned long)context_ptr+0x00000a50+4*2))=0x00006028;
*((unsigned int *)((unsigned long)context_ptr+0x00000a50+4*3))=0x0222006f;
*((unsigned int *)((unsigned long)context_ptr+0x00000a50+4*4))=0x03c1b88f;
*((unsigned int *)((unsigned long)context_ptr+0x00000a50+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000246&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000067cc,"\xf9\x8a\x61\xb6\xa8\xcb\x2e\x7e\x50\x63\x0f\x5c\x3a\x2d\x2e\xa3\x13\x8e\x72\x91\x9b\x98\x37\xb9\x84\x37\x19\x2e\x95\x72\x2a\x22",32))
printf("strip: f98a61b6a8cb2e7e, Pass\n");
else
printf("strip: f98a61b6a8cb2e7e, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006674))=0x018a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006674+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006674+4*2))=0x02020070;
*((unsigned int *)((unsigned long)context_ptr+0x00006674+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x00006888))=0x6306a335;
*((unsigned int *)((unsigned long)context_ptr+0x00006888+4*1))=0x825de32c;
*((unsigned int *)((unsigned long)context_ptr+0x00006888+4*2))=0x8930c2f0;
*((unsigned int *)((unsigned long)context_ptr+0x00006888+4*3))=0xeaee9f69;
*((unsigned int *)((unsigned long)context_ptr+0x00006888+4*4))=0xab9403b2;
*((unsigned int *)((unsigned long)context_ptr+0x00006888+4*5))=0x5a6100ca;
*((unsigned int *)((unsigned long)context_ptr+0x00006888+4*6))=0xa22240a4;
*((unsigned int *)((unsigned long)context_ptr+0x00006888+4*7))=0xfa11425e;
*((unsigned int *)((unsigned long)context_ptr+0x00006888+4*8))=0x054c40a4;
*((unsigned int *)((unsigned long)context_ptr+0x00006888+4*9))=0xe32861c9;
*((unsigned int *)((unsigned long)context_ptr+0x00006888+4*10))=0xc3c81c33;
*((unsigned int *)((unsigned long)context_ptr+0x00006888+4*11))=0x1ab43009;
*((unsigned int *)((unsigned long)context_ptr+0x00006888+4*12))=0xdc54a9bb;
*((unsigned int *)((unsigned long)context_ptr+0x00006888+4*13))=0x0cd518ea;
*((unsigned int *)((unsigned long)context_ptr+0x00006888+4*14))=0x3a208eac;
*((unsigned int *)((unsigned long)context_ptr+0x00006888+4*15))=0x2a3c2b10;
*((unsigned int *)((unsigned long)context_ptr+0x00006888+4*16))=0xe58c438c;
*((unsigned int *)((unsigned long)context_ptr+0x00006888+4*17))=0xb92132af;
*((unsigned int *)((unsigned long)context_ptr+0x00006888+4*18))=0x9ee8d43b;
*((unsigned int *)((unsigned long)context_ptr+0x00006888+4*19))=0x19944148;
*((unsigned int *)((unsigned long)context_ptr+0x00006888+4*20))=0xac92d56a;
*((unsigned int *)((unsigned long)context_ptr+0x00006888+4*21))=0x8c9a2288;
*((unsigned int *)((unsigned long)context_ptr+0x00006888+4*22))=0xfaf783fc;
*((unsigned int *)((unsigned long)context_ptr+0x00006888+4*23))=0xc8d58b3b;
*((unsigned int *)((unsigned long)context_ptr+0x00006888+4*24))=0x8d1ffb6e;
*((unsigned int *)((unsigned long)context_ptr+0x00006888+4*25))=0x190a7910;
*((unsigned int *)((unsigned long)context_ptr+0x00006888+4*26))=0x1d6fec65;
*((unsigned int *)((unsigned long)context_ptr+0x00006888+4*27))=0x7f96f1e6;
*((unsigned int *)((unsigned long)context_ptr+0x00003a68))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003a68+4*1))=0x000068f8;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000a68+4*1))=0x00006888;
*((unsigned int *)((unsigned long)context_ptr+0x00000a68+4*2))=0x00006674;
*((unsigned int *)((unsigned long)context_ptr+0x00000a68+4*3))=0x02220070;
*((unsigned int *)((unsigned long)context_ptr+0x00000a68+4*4))=0x03cd1d49;
*((unsigned int *)((unsigned long)context_ptr+0x00000a68+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000024c&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000063bc,"\x13\x99\xad\xdb\xf7\x55\xb8\x7d\xc0\x28\x01\xaa\xd3\x93\x96\x22\x0c\x0c\xf1\x3e\xaa\x5e\xd9\x8c\x28\x57\xf7\xc0\xe1\x23\x3d\x66",32))
printf("strip: 1399addbf755b87d, Pass\n");
else
printf("strip: 1399addbf755b87d, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006684))=0x018a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006684+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006684+4*2))=0x02020071;
*((unsigned int *)((unsigned long)context_ptr+0x00006684+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x00006350))=0x7e97ed1e;
*((unsigned int *)((unsigned long)context_ptr+0x00006350+4*1))=0x4f075893;
*((unsigned int *)((unsigned long)context_ptr+0x00006350+4*2))=0xdfd41397;
*((unsigned int *)((unsigned long)context_ptr+0x00006350+4*3))=0xd4b74270;
*((unsigned int *)((unsigned long)context_ptr+0x00006350+4*4))=0x1ec952a9;
*((unsigned int *)((unsigned long)context_ptr+0x00006350+4*5))=0xa00b6956;
*((unsigned int *)((unsigned long)context_ptr+0x00006350+4*6))=0xc4a069c8;
*((unsigned int *)((unsigned long)context_ptr+0x00006350+4*7))=0xef40f5c2;
*((unsigned int *)((unsigned long)context_ptr+0x00006350+4*8))=0xeb5bc58a;
*((unsigned int *)((unsigned long)context_ptr+0x00006350+4*9))=0xee07ce62;
*((unsigned int *)((unsigned long)context_ptr+0x00006350+4*10))=0x7c65d35c;
*((unsigned int *)((unsigned long)context_ptr+0x00006350+4*11))=0xe2ed0336;
*((unsigned int *)((unsigned long)context_ptr+0x00006350+4*12))=0x5cea9541;
*((unsigned int *)((unsigned long)context_ptr+0x00006350+4*13))=0x9e849399;
*((unsigned int *)((unsigned long)context_ptr+0x00006350+4*14))=0xb74b1c1d;
*((unsigned int *)((unsigned long)context_ptr+0x00006350+4*15))=0x79cb0063;
*((unsigned int *)((unsigned long)context_ptr+0x00006350+4*16))=0x09c9b062;
*((unsigned int *)((unsigned long)context_ptr+0x00006350+4*17))=0x87ba2a38;
*((unsigned int *)((unsigned long)context_ptr+0x00006350+4*18))=0x03578f2d;
*((unsigned int *)((unsigned long)context_ptr+0x00006350+4*19))=0xb2efeeef;
*((unsigned int *)((unsigned long)context_ptr+0x00006350+4*20))=0x10af28cd;
*((unsigned int *)((unsigned long)context_ptr+0x00006350+4*21))=0xf582bb55;
*((unsigned int *)((unsigned long)context_ptr+0x00006350+4*22))=0xec63ab4a;
*((unsigned int *)((unsigned long)context_ptr+0x00006350+4*23))=0x88605584;
*((unsigned int *)((unsigned long)context_ptr+0x00006350+4*24))=0x709465f2;
*((unsigned int *)((unsigned long)context_ptr+0x00006350+4*25))=0xbe6df191;
*((unsigned int *)((unsigned long)context_ptr+0x00006350+4*26))=0x06862daf;
*((unsigned int *)((unsigned long)context_ptr+0x00006350+4*27))=0x1f95a08f;
*((unsigned int *)((unsigned long)context_ptr+0x00006350+4*28))=0x0000008f;
*((unsigned int *)((unsigned long)context_ptr+0x00003a80))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003a80+4*1))=0x00006790;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000a80+4*1))=0x00006350;
*((unsigned int *)((unsigned long)context_ptr+0x00000a80+4*2))=0x00006684;
*((unsigned int *)((unsigned long)context_ptr+0x00000a80+4*3))=0x02220071;
*((unsigned int *)((unsigned long)context_ptr+0x00000a80+4*4))=0x01a78700;
*((unsigned int *)((unsigned long)context_ptr+0x00000a80+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000252&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000067ec,"\x2e\x71\x02\x26\xb3\x45\xe5\x8a\x37\xd3\xd5\x7e\x8d\x5c\x09\xc6\x6d\x87\x2f\x67\x59\xe1\x4e\xf5\x1d\x41\xfc\x15\xa4\x8c\xf5\xdb",32))
printf("strip: 2e710226b345e58a, Pass\n");
else
printf("strip: 2e710226b345e58a, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006564))=0x018a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006564+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006564+4*2))=0x02020072;
*((unsigned int *)((unsigned long)context_ptr+0x00006564+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x00006a0c))=0xe2608f68;
*((unsigned int *)((unsigned long)context_ptr+0x00006a0c+4*1))=0x9000ec93;
*((unsigned int *)((unsigned long)context_ptr+0x00006a0c+4*2))=0xc5338530;
*((unsigned int *)((unsigned long)context_ptr+0x00006a0c+4*3))=0x9b843721;
*((unsigned int *)((unsigned long)context_ptr+0x00006a0c+4*4))=0x07b508b5;
*((unsigned int *)((unsigned long)context_ptr+0x00006a0c+4*5))=0x61002732;
*((unsigned int *)((unsigned long)context_ptr+0x00006a0c+4*6))=0xa3120658;
*((unsigned int *)((unsigned long)context_ptr+0x00006a0c+4*7))=0x2bfbd80a;
*((unsigned int *)((unsigned long)context_ptr+0x00006a0c+4*8))=0x5fb94323;
*((unsigned int *)((unsigned long)context_ptr+0x00006a0c+4*9))=0x0a523b6e;
*((unsigned int *)((unsigned long)context_ptr+0x00006a0c+4*10))=0x559a46b6;
*((unsigned int *)((unsigned long)context_ptr+0x00006a0c+4*11))=0x204dbb92;
*((unsigned int *)((unsigned long)context_ptr+0x00006a0c+4*12))=0x0c3ffeba;
*((unsigned int *)((unsigned long)context_ptr+0x00006a0c+4*13))=0x22ea5eb4;
*((unsigned int *)((unsigned long)context_ptr+0x00006a0c+4*14))=0x78fa8225;
*((unsigned int *)((unsigned long)context_ptr+0x00006a0c+4*15))=0xffe52d68;
*((unsigned int *)((unsigned long)context_ptr+0x00006a0c+4*16))=0x9dcd8023;
*((unsigned int *)((unsigned long)context_ptr+0x00006a0c+4*17))=0x2487cf39;
*((unsigned int *)((unsigned long)context_ptr+0x00006a0c+4*18))=0xe0493dc6;
*((unsigned int *)((unsigned long)context_ptr+0x00006a0c+4*19))=0xb1e6af93;
*((unsigned int *)((unsigned long)context_ptr+0x00006a0c+4*20))=0x92b279d0;
*((unsigned int *)((unsigned long)context_ptr+0x00006a0c+4*21))=0x524523be;
*((unsigned int *)((unsigned long)context_ptr+0x00006a0c+4*22))=0x4d0435c8;
*((unsigned int *)((unsigned long)context_ptr+0x00006a0c+4*23))=0xd7dc9886;
*((unsigned int *)((unsigned long)context_ptr+0x00006a0c+4*24))=0x33573788;
*((unsigned int *)((unsigned long)context_ptr+0x00006a0c+4*25))=0xe0e13cae;
*((unsigned int *)((unsigned long)context_ptr+0x00006a0c+4*26))=0xf91d6b47;
*((unsigned int *)((unsigned long)context_ptr+0x00006a0c+4*27))=0x9e9c5d68;
*((unsigned int *)((unsigned long)context_ptr+0x00006a0c+4*28))=0x0000b7fe;
*((unsigned int *)((unsigned long)context_ptr+0x00003a98))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003a98+4*1))=0x000063c4;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000a98+4*1))=0x00006a0c;
*((unsigned int *)((unsigned long)context_ptr+0x00000a98+4*2))=0x00006564;
*((unsigned int *)((unsigned long)context_ptr+0x00000a98+4*3))=0x02220072;
*((unsigned int *)((unsigned long)context_ptr+0x00000a98+4*4))=0x0f222a0a;
*((unsigned int *)((unsigned long)context_ptr+0x00000a98+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000258&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000064c4,"\x0c\xba\x59\x6d\x88\xce\x8d\x2d\xd4\x8b\x2d\x8f\x58\x78\xf3\x00\x57\x1c\xfb\xdc\xbb\x60\xb6\x95\x89\x52\xbc\x73\x0f\xe5\xb0\xcb",32))
printf("strip: 0cba596d88ce8d2d, Pass\n");
else
printf("strip: 0cba596d88ce8d2d, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006918))=0x018a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006918+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006918+4*2))=0x02020073;
*((unsigned int *)((unsigned long)context_ptr+0x00006918+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x0000645c))=0x079ef2f5;
*((unsigned int *)((unsigned long)context_ptr+0x0000645c+4*1))=0xe5866614;
*((unsigned int *)((unsigned long)context_ptr+0x0000645c+4*2))=0x2755f119;
*((unsigned int *)((unsigned long)context_ptr+0x0000645c+4*3))=0x9da99c86;
*((unsigned int *)((unsigned long)context_ptr+0x0000645c+4*4))=0xf5b7c0c7;
*((unsigned int *)((unsigned long)context_ptr+0x0000645c+4*5))=0x51216a43;
*((unsigned int *)((unsigned long)context_ptr+0x0000645c+4*6))=0x991a4a39;
*((unsigned int *)((unsigned long)context_ptr+0x0000645c+4*7))=0xaf3b8256;
*((unsigned int *)((unsigned long)context_ptr+0x0000645c+4*8))=0x5f6ef8ab;
*((unsigned int *)((unsigned long)context_ptr+0x0000645c+4*9))=0xdca87a08;
*((unsigned int *)((unsigned long)context_ptr+0x0000645c+4*10))=0x3dbf69e7;
*((unsigned int *)((unsigned long)context_ptr+0x0000645c+4*11))=0x52cc3ef9;
*((unsigned int *)((unsigned long)context_ptr+0x0000645c+4*12))=0x672f4d42;
*((unsigned int *)((unsigned long)context_ptr+0x0000645c+4*13))=0x0c68224a;
*((unsigned int *)((unsigned long)context_ptr+0x0000645c+4*14))=0x9e21a5e4;
*((unsigned int *)((unsigned long)context_ptr+0x0000645c+4*15))=0x2f085b36;
*((unsigned int *)((unsigned long)context_ptr+0x0000645c+4*16))=0x12c8f800;
*((unsigned int *)((unsigned long)context_ptr+0x0000645c+4*17))=0xd045cd91;
*((unsigned int *)((unsigned long)context_ptr+0x0000645c+4*18))=0x8f37638b;
*((unsigned int *)((unsigned long)context_ptr+0x0000645c+4*19))=0xbb3a48aa;
*((unsigned int *)((unsigned long)context_ptr+0x0000645c+4*20))=0x3b02864e;
*((unsigned int *)((unsigned long)context_ptr+0x0000645c+4*21))=0xf72be13d;
*((unsigned int *)((unsigned long)context_ptr+0x0000645c+4*22))=0xd63a1b35;
*((unsigned int *)((unsigned long)context_ptr+0x0000645c+4*23))=0xa3b02769;
*((unsigned int *)((unsigned long)context_ptr+0x0000645c+4*24))=0x67afb732;
*((unsigned int *)((unsigned long)context_ptr+0x0000645c+4*25))=0xf33aef46;
*((unsigned int *)((unsigned long)context_ptr+0x0000645c+4*26))=0x236e503c;
*((unsigned int *)((unsigned long)context_ptr+0x0000645c+4*27))=0x0f0d5090;
*((unsigned int *)((unsigned long)context_ptr+0x0000645c+4*28))=0x00b263ef;
*((unsigned int *)((unsigned long)context_ptr+0x00003ab0))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003ab0+4*1))=0x000067b0;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000ab0+4*1))=0x0000645c;
*((unsigned int *)((unsigned long)context_ptr+0x00000ab0+4*2))=0x00006918;
*((unsigned int *)((unsigned long)context_ptr+0x00000ab0+4*3))=0x02220073;
*((unsigned int *)((unsigned long)context_ptr+0x00000ab0+4*4))=0x08f3d7b1;
*((unsigned int *)((unsigned long)context_ptr+0x00000ab0+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000025e&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000063ec,"\xf4\x43\x94\xb1\x62\x12\x15\xe8\x27\xbe\x90\x34\x68\xa1\x01\xa8\xa9\x2e\xc1\x13\x42\x74\x5e\x09\x83\xdf\x42\x5a\xee\x0a\x31\x48",32))
printf("strip: f44394b1621215e8, Pass\n");
else
printf("strip: f44394b1621215e8, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000064d0))=0x018a0012;
*((unsigned int *)((unsigned long)context_ptr+0x000064d0+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000064d0+4*2))=0x02020074;
*((unsigned int *)((unsigned long)context_ptr+0x000064d0+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x00006058))=0x77a7df0e;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*1))=0xdd6b143e;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*2))=0x67a15bdc;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*3))=0x117e3b10;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*4))=0x5c96e513;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*5))=0xd71539f2;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*6))=0xdd13edc5;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*7))=0x547ce0f0;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*8))=0x4fd249d0;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*9))=0xb5d6de30;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*10))=0x9cd878e7;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*11))=0xc9dc7008;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*12))=0x41e853d7;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*13))=0xcf0d1730;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*14))=0x6a936cac;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*15))=0x613aa6e6;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*16))=0x41b793b0;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*17))=0x44fe370b;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*18))=0x2284a7e6;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*19))=0x2ab09992;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*20))=0x94d9d77d;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*21))=0xb4e7a35e;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*22))=0x0c551f87;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*23))=0x8547ed9f;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*24))=0x2505479d;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*25))=0xac3d1f0c;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*26))=0x28b9eef7;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*27))=0xfe4e9d48;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*28))=0xfffa2cda;
*((unsigned int *)((unsigned long)context_ptr+0x00003ac8))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003ac8+4*1))=0x000063e4;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000ac8+4*1))=0x00006058;
*((unsigned int *)((unsigned long)context_ptr+0x00000ac8+4*2))=0x000064d0;
*((unsigned int *)((unsigned long)context_ptr+0x00000ac8+4*3))=0x02220074;
*((unsigned int *)((unsigned long)context_ptr+0x00000ac8+4*4))=0x04dddc0a;
*((unsigned int *)((unsigned long)context_ptr+0x00000ac8+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000264&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006574,"\x15\x3f\x10\x88\x73\x38\x5d\x7c\xa0\x09\x5f\x13\xa3\x15\x52\x36\x27\x3f\xf0\xc5\xe4\xbb\x9e\x9c\x6d\xd4\x47\x2f\xf3\x2e\xee\xac",32))
printf("strip: 153f108873385d7c, Pass\n");
else
printf("strip: 153f108873385d7c, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006574))=0x018a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006574+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006574+4*2))=0x02020075;
*((unsigned int *)((unsigned long)context_ptr+0x00006574+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x000060cc))=0xfd2ab048;
*((unsigned int *)((unsigned long)context_ptr+0x000060cc+4*1))=0xdef9fa77;
*((unsigned int *)((unsigned long)context_ptr+0x000060cc+4*2))=0xae6d8568;
*((unsigned int *)((unsigned long)context_ptr+0x000060cc+4*3))=0x33e46a4e;
*((unsigned int *)((unsigned long)context_ptr+0x000060cc+4*4))=0xdf823a6c;
*((unsigned int *)((unsigned long)context_ptr+0x000060cc+4*5))=0x6008b4a1;
*((unsigned int *)((unsigned long)context_ptr+0x000060cc+4*6))=0x003d5a3c;
*((unsigned int *)((unsigned long)context_ptr+0x000060cc+4*7))=0x9945ab6f;
*((unsigned int *)((unsigned long)context_ptr+0x000060cc+4*8))=0x75b0e468;
*((unsigned int *)((unsigned long)context_ptr+0x000060cc+4*9))=0xbf8e80be;
*((unsigned int *)((unsigned long)context_ptr+0x000060cc+4*10))=0xb7c8799f;
*((unsigned int *)((unsigned long)context_ptr+0x000060cc+4*11))=0x1e021eb3;
*((unsigned int *)((unsigned long)context_ptr+0x000060cc+4*12))=0x255f74bb;
*((unsigned int *)((unsigned long)context_ptr+0x000060cc+4*13))=0x62796387;
*((unsigned int *)((unsigned long)context_ptr+0x000060cc+4*14))=0x09053681;
*((unsigned int *)((unsigned long)context_ptr+0x000060cc+4*15))=0xb4f17fd2;
*((unsigned int *)((unsigned long)context_ptr+0x000060cc+4*16))=0xd23c0597;
*((unsigned int *)((unsigned long)context_ptr+0x000060cc+4*17))=0xb799c6f0;
*((unsigned int *)((unsigned long)context_ptr+0x000060cc+4*18))=0xd03d8ce8;
*((unsigned int *)((unsigned long)context_ptr+0x000060cc+4*19))=0x5dd95db1;
*((unsigned int *)((unsigned long)context_ptr+0x000060cc+4*20))=0xcd676f57;
*((unsigned int *)((unsigned long)context_ptr+0x000060cc+4*21))=0x946cfe04;
*((unsigned int *)((unsigned long)context_ptr+0x000060cc+4*22))=0x5419d4e1;
*((unsigned int *)((unsigned long)context_ptr+0x000060cc+4*23))=0xe991245b;
*((unsigned int *)((unsigned long)context_ptr+0x000060cc+4*24))=0x4a78eadb;
*((unsigned int *)((unsigned long)context_ptr+0x000060cc+4*25))=0x4c9eb058;
*((unsigned int *)((unsigned long)context_ptr+0x000060cc+4*26))=0xff92d803;
*((unsigned int *)((unsigned long)context_ptr+0x000060cc+4*27))=0x1adb5d7f;
*((unsigned int *)((unsigned long)context_ptr+0x000060cc+4*28))=0x01012d93;
*((unsigned int *)((unsigned long)context_ptr+0x000060cc+4*29))=0x0000007e;
*((unsigned int *)((unsigned long)context_ptr+0x00003ae0))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003ae0+4*1))=0x000064e0;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000ae0+4*1))=0x000060cc;
*((unsigned int *)((unsigned long)context_ptr+0x00000ae0+4*2))=0x00006574;
*((unsigned int *)((unsigned long)context_ptr+0x00000ae0+4*3))=0x02220075;
*((unsigned int *)((unsigned long)context_ptr+0x00000ae0+4*4))=0x00b3a3e0;
*((unsigned int *)((unsigned long)context_ptr+0x00000ae0+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000026a&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006594,"\x85\x3d\x54\x91\x91\x25\xbf\x50\xb7\x79\x93\xc2\x53\x0c\x3d\x05\x3e\x3f\x06\xad\xb9\xd8\xd4\xd2\xf4\xd4\x58\xcc\x36\xcc\x61\x83",32))
printf("strip: 853d54919125bf50, Pass\n");
else
printf("strip: 853d54919125bf50, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006500))=0x018a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006500+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006500+4*2))=0x02020076;
*((unsigned int *)((unsigned long)context_ptr+0x00006500+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x00006144))=0xbd178865;
*((unsigned int *)((unsigned long)context_ptr+0x00006144+4*1))=0xa300585a;
*((unsigned int *)((unsigned long)context_ptr+0x00006144+4*2))=0xd091bf99;
*((unsigned int *)((unsigned long)context_ptr+0x00006144+4*3))=0xc0ce85e7;
*((unsigned int *)((unsigned long)context_ptr+0x00006144+4*4))=0x324f416a;
*((unsigned int *)((unsigned long)context_ptr+0x00006144+4*5))=0xe21bebfa;
*((unsigned int *)((unsigned long)context_ptr+0x00006144+4*6))=0x231c7eb9;
*((unsigned int *)((unsigned long)context_ptr+0x00006144+4*7))=0x430585f6;
*((unsigned int *)((unsigned long)context_ptr+0x00006144+4*8))=0xbddb640d;
*((unsigned int *)((unsigned long)context_ptr+0x00006144+4*9))=0x4f558362;
*((unsigned int *)((unsigned long)context_ptr+0x00006144+4*10))=0xb7ca8548;
*((unsigned int *)((unsigned long)context_ptr+0x00006144+4*11))=0x742a9f27;
*((unsigned int *)((unsigned long)context_ptr+0x00006144+4*12))=0x691fb8d0;
*((unsigned int *)((unsigned long)context_ptr+0x00006144+4*13))=0x5a5a8adc;
*((unsigned int *)((unsigned long)context_ptr+0x00006144+4*14))=0xcdb7216e;
*((unsigned int *)((unsigned long)context_ptr+0x00006144+4*15))=0x5de42198;
*((unsigned int *)((unsigned long)context_ptr+0x00006144+4*16))=0xb05cf8f9;
*((unsigned int *)((unsigned long)context_ptr+0x00006144+4*17))=0x922fd1e0;
*((unsigned int *)((unsigned long)context_ptr+0x00006144+4*18))=0x600dd4cb;
*((unsigned int *)((unsigned long)context_ptr+0x00006144+4*19))=0x1a1a9ca5;
*((unsigned int *)((unsigned long)context_ptr+0x00006144+4*20))=0xb641daeb;
*((unsigned int *)((unsigned long)context_ptr+0x00006144+4*21))=0x74ec2077;
*((unsigned int *)((unsigned long)context_ptr+0x00006144+4*22))=0x05f8571a;
*((unsigned int *)((unsigned long)context_ptr+0x00006144+4*23))=0x2d94a68f;
*((unsigned int *)((unsigned long)context_ptr+0x00006144+4*24))=0x6e20baf1;
*((unsigned int *)((unsigned long)context_ptr+0x00006144+4*25))=0x3a419bb6;
*((unsigned int *)((unsigned long)context_ptr+0x00006144+4*26))=0x61d8ec3b;
*((unsigned int *)((unsigned long)context_ptr+0x00006144+4*27))=0xba46dcf1;
*((unsigned int *)((unsigned long)context_ptr+0x00006144+4*28))=0xbb818551;
*((unsigned int *)((unsigned long)context_ptr+0x00006144+4*29))=0x00003b6e;
*((unsigned int *)((unsigned long)context_ptr+0x00003af8))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003af8+4*1))=0x00006584;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000af8+4*1))=0x00006144;
*((unsigned int *)((unsigned long)context_ptr+0x00000af8+4*2))=0x00006500;
*((unsigned int *)((unsigned long)context_ptr+0x00000af8+4*3))=0x02220076;
*((unsigned int *)((unsigned long)context_ptr+0x00000af8+4*4))=0x01f724c8;
*((unsigned int *)((unsigned long)context_ptr+0x00000af8+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000270&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000065b4,"\x10\xd5\xdd\x3c\xfd\x6f\x1b\x9d\x0a\xc1\x05\x1a\x18\x15\x0c\xb4\x69\x9b\xd5\x96\x8e\x26\x5a\xf2\xa7\x09\x23\xaa\xc8\xb8\xe3\xb0",32))
printf("strip: 10d5dd3cfd6f1b9d, Pass\n");
else
printf("strip: 10d5dd3cfd6f1b9d, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006510))=0x018a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006510+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006510+4*2))=0x02020077;
*((unsigned int *)((unsigned long)context_ptr+0x00006510+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x000061bc))=0x97dc0e45;
*((unsigned int *)((unsigned long)context_ptr+0x000061bc+4*1))=0x11c44eb6;
*((unsigned int *)((unsigned long)context_ptr+0x000061bc+4*2))=0x09c2fffc;
*((unsigned int *)((unsigned long)context_ptr+0x000061bc+4*3))=0xa0641905;
*((unsigned int *)((unsigned long)context_ptr+0x000061bc+4*4))=0xbb0a7e7f;
*((unsigned int *)((unsigned long)context_ptr+0x000061bc+4*5))=0x879577a7;
*((unsigned int *)((unsigned long)context_ptr+0x000061bc+4*6))=0x61afbeb5;
*((unsigned int *)((unsigned long)context_ptr+0x000061bc+4*7))=0x0453900c;
*((unsigned int *)((unsigned long)context_ptr+0x000061bc+4*8))=0x7595206e;
*((unsigned int *)((unsigned long)context_ptr+0x000061bc+4*9))=0xe96bfcce;
*((unsigned int *)((unsigned long)context_ptr+0x000061bc+4*10))=0x8a5d82fb;
*((unsigned int *)((unsigned long)context_ptr+0x000061bc+4*11))=0x065737f9;
*((unsigned int *)((unsigned long)context_ptr+0x000061bc+4*12))=0xd7267ce5;
*((unsigned int *)((unsigned long)context_ptr+0x000061bc+4*13))=0x2241fe7d;
*((unsigned int *)((unsigned long)context_ptr+0x000061bc+4*14))=0x52c991f5;
*((unsigned int *)((unsigned long)context_ptr+0x000061bc+4*15))=0x1b8efa40;
*((unsigned int *)((unsigned long)context_ptr+0x000061bc+4*16))=0x6583b9aa;
*((unsigned int *)((unsigned long)context_ptr+0x000061bc+4*17))=0xcfc8247f;
*((unsigned int *)((unsigned long)context_ptr+0x000061bc+4*18))=0xd90e0ba5;
*((unsigned int *)((unsigned long)context_ptr+0x000061bc+4*19))=0xc31cc0ea;
*((unsigned int *)((unsigned long)context_ptr+0x000061bc+4*20))=0x638d843b;
*((unsigned int *)((unsigned long)context_ptr+0x000061bc+4*21))=0x69cc0557;
*((unsigned int *)((unsigned long)context_ptr+0x000061bc+4*22))=0x5ce7a353;
*((unsigned int *)((unsigned long)context_ptr+0x000061bc+4*23))=0xf93d39df;
*((unsigned int *)((unsigned long)context_ptr+0x000061bc+4*24))=0x379177e5;
*((unsigned int *)((unsigned long)context_ptr+0x000061bc+4*25))=0xff578dc4;
*((unsigned int *)((unsigned long)context_ptr+0x000061bc+4*26))=0x05bce404;
*((unsigned int *)((unsigned long)context_ptr+0x000061bc+4*27))=0xceeaea20;
*((unsigned int *)((unsigned long)context_ptr+0x000061bc+4*28))=0xf5da62f4;
*((unsigned int *)((unsigned long)context_ptr+0x000061bc+4*29))=0x00ff679f;
*((unsigned int *)((unsigned long)context_ptr+0x00003b10))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003b10+4*1))=0x000065a4;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000b10+4*1))=0x000061bc;
*((unsigned int *)((unsigned long)context_ptr+0x00000b10+4*2))=0x00006510;
*((unsigned int *)((unsigned long)context_ptr+0x00000b10+4*3))=0x02220077;
*((unsigned int *)((unsigned long)context_ptr+0x00000b10+4*4))=0x0d16172d;
*((unsigned int *)((unsigned long)context_ptr+0x00000b10+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000276&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x0000640c,"\xd8\xb0\x94\x43\x9e\xdc\xde\x9f\xd8\x15\x82\x8a\xa0\x8a\xe3\xf6\x23\xed\xe4\x60\x14\x43\x6e\x5b\x04\x3a\x6c\xfb\x71\x5b\x8a\xb8",32))
printf("strip: d8b094439edcde9f, Pass\n");
else
printf("strip: d8b094439edcde9f, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000065c4))=0x018a0012;
*((unsigned int *)((unsigned long)context_ptr+0x000065c4+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000065c4+4*2))=0x02020078;
*((unsigned int *)((unsigned long)context_ptr+0x000065c4+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x00006928))=0xae180999;
*((unsigned int *)((unsigned long)context_ptr+0x00006928+4*1))=0x51b5551e;
*((unsigned int *)((unsigned long)context_ptr+0x00006928+4*2))=0x9688c451;
*((unsigned int *)((unsigned long)context_ptr+0x00006928+4*3))=0xbe5decee;
*((unsigned int *)((unsigned long)context_ptr+0x00006928+4*4))=0xa9012dc1;
*((unsigned int *)((unsigned long)context_ptr+0x00006928+4*5))=0xd4cecce7;
*((unsigned int *)((unsigned long)context_ptr+0x00006928+4*6))=0x7bd4d99c;
*((unsigned int *)((unsigned long)context_ptr+0x00006928+4*7))=0x24a3fa21;
*((unsigned int *)((unsigned long)context_ptr+0x00006928+4*8))=0x95d385f5;
*((unsigned int *)((unsigned long)context_ptr+0x00006928+4*9))=0x66fec2b4;
*((unsigned int *)((unsigned long)context_ptr+0x00006928+4*10))=0xa8e90b81;
*((unsigned int *)((unsigned long)context_ptr+0x00006928+4*11))=0x3611e097;
*((unsigned int *)((unsigned long)context_ptr+0x00006928+4*12))=0xd548edfc;
*((unsigned int *)((unsigned long)context_ptr+0x00006928+4*13))=0x9dbc6236;
*((unsigned int *)((unsigned long)context_ptr+0x00006928+4*14))=0x4f372caa;
*((unsigned int *)((unsigned long)context_ptr+0x00006928+4*15))=0xe9564470;
*((unsigned int *)((unsigned long)context_ptr+0x00006928+4*16))=0xf8c3fea3;
*((unsigned int *)((unsigned long)context_ptr+0x00006928+4*17))=0x56349ebe;
*((unsigned int *)((unsigned long)context_ptr+0x00006928+4*18))=0xd0f904de;
*((unsigned int *)((unsigned long)context_ptr+0x00006928+4*19))=0x6918d83c;
*((unsigned int *)((unsigned long)context_ptr+0x00006928+4*20))=0x6c10dacd;
*((unsigned int *)((unsigned long)context_ptr+0x00006928+4*21))=0xf25f68cd;
*((unsigned int *)((unsigned long)context_ptr+0x00006928+4*22))=0x869f3d24;
*((unsigned int *)((unsigned long)context_ptr+0x00006928+4*23))=0xc5953159;
*((unsigned int *)((unsigned long)context_ptr+0x00006928+4*24))=0xa57a2d0b;
*((unsigned int *)((unsigned long)context_ptr+0x00006928+4*25))=0x2827c64e;
*((unsigned int *)((unsigned long)context_ptr+0x00006928+4*26))=0x9dec7b59;
*((unsigned int *)((unsigned long)context_ptr+0x00006928+4*27))=0x7d98bec6;
*((unsigned int *)((unsigned long)context_ptr+0x00006928+4*28))=0xa9ad2176;
*((unsigned int *)((unsigned long)context_ptr+0x00006928+4*29))=0x280ca7d9;
*((unsigned int *)((unsigned long)context_ptr+0x00003b28))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003b28+4*1))=0x00006404;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000b28+4*1))=0x00006928;
*((unsigned int *)((unsigned long)context_ptr+0x00000b28+4*2))=0x000065c4;
*((unsigned int *)((unsigned long)context_ptr+0x00000b28+4*3))=0x02220078;
*((unsigned int *)((unsigned long)context_ptr+0x00000b28+4*4))=0x024e14b3;
*((unsigned int *)((unsigned long)context_ptr+0x00000b28+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000027c&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006524,"\x02\xe2\xc5\x94\x80\x77\xc1\xc5\x25\x30\xe1\xac\x25\x3a\xd8\xae\x3d\x35\xba\x8c\x70\xc1\xba\x36\xea\xb1\xcb\xed\x57\x89\x75\x3c",32))
printf("strip: 02e2c5948077c1c5, Pass\n");
else
printf("strip: 02e2c5948077c1c5, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000065d4))=0x018a0012;
*((unsigned int *)((unsigned long)context_ptr+0x000065d4+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000065d4+4*2))=0x02020079;
*((unsigned int *)((unsigned long)context_ptr+0x000065d4+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x00006234))=0x49d1de7d;
*((unsigned int *)((unsigned long)context_ptr+0x00006234+4*1))=0xd5acd69a;
*((unsigned int *)((unsigned long)context_ptr+0x00006234+4*2))=0xde152b74;
*((unsigned int *)((unsigned long)context_ptr+0x00006234+4*3))=0x9854a427;
*((unsigned int *)((unsigned long)context_ptr+0x00006234+4*4))=0x1a354373;
*((unsigned int *)((unsigned long)context_ptr+0x00006234+4*5))=0xcfc64b89;
*((unsigned int *)((unsigned long)context_ptr+0x00006234+4*6))=0xe4bfc260;
*((unsigned int *)((unsigned long)context_ptr+0x00006234+4*7))=0xfc2fe2b6;
*((unsigned int *)((unsigned long)context_ptr+0x00006234+4*8))=0x7dcbc749;
*((unsigned int *)((unsigned long)context_ptr+0x00006234+4*9))=0x374e0ae9;
*((unsigned int *)((unsigned long)context_ptr+0x00006234+4*10))=0x46328a09;
*((unsigned int *)((unsigned long)context_ptr+0x00006234+4*11))=0x1e1cca92;
*((unsigned int *)((unsigned long)context_ptr+0x00006234+4*12))=0x9e8407e0;
*((unsigned int *)((unsigned long)context_ptr+0x00006234+4*13))=0xbee36712;
*((unsigned int *)((unsigned long)context_ptr+0x00006234+4*14))=0x87b39cbe;
*((unsigned int *)((unsigned long)context_ptr+0x00006234+4*15))=0xbcc3f135;
*((unsigned int *)((unsigned long)context_ptr+0x00006234+4*16))=0xb19d3910;
*((unsigned int *)((unsigned long)context_ptr+0x00006234+4*17))=0xe61b9172;
*((unsigned int *)((unsigned long)context_ptr+0x00006234+4*18))=0x640f865d;
*((unsigned int *)((unsigned long)context_ptr+0x00006234+4*19))=0xc6ca2c92;
*((unsigned int *)((unsigned long)context_ptr+0x00006234+4*20))=0x633094f7;
*((unsigned int *)((unsigned long)context_ptr+0x00006234+4*21))=0xa47168c4;
*((unsigned int *)((unsigned long)context_ptr+0x00006234+4*22))=0x8997656e;
*((unsigned int *)((unsigned long)context_ptr+0x00006234+4*23))=0xee19f837;
*((unsigned int *)((unsigned long)context_ptr+0x00006234+4*24))=0x08a469e1;
*((unsigned int *)((unsigned long)context_ptr+0x00006234+4*25))=0x85bc3293;
*((unsigned int *)((unsigned long)context_ptr+0x00006234+4*26))=0xcbde6476;
*((unsigned int *)((unsigned long)context_ptr+0x00006234+4*27))=0x8d84adbf;
*((unsigned int *)((unsigned long)context_ptr+0x00006234+4*28))=0xc97f2e47;
*((unsigned int *)((unsigned long)context_ptr+0x00006234+4*29))=0x019336a6;
*((unsigned int *)((unsigned long)context_ptr+0x00006234+4*30))=0x000000cb;
*((unsigned int *)((unsigned long)context_ptr+0x00003b40))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003b40+4*1))=0x00006520;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000b40+4*1))=0x00006234;
*((unsigned int *)((unsigned long)context_ptr+0x00000b40+4*2))=0x000065d4;
*((unsigned int *)((unsigned long)context_ptr+0x00000b40+4*3))=0x02220079;
*((unsigned int *)((unsigned long)context_ptr+0x00000b40+4*4))=0x0879f233;
*((unsigned int *)((unsigned long)context_ptr+0x00000b40+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000282&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x0000643c,"\xeb\x3c\xf6\x25\x27\x4a\xb5\x5d\xfd\x38\x30\x38\xa7\x15\x3c\xc6\x8f\x65\xa7\x2b\xd9\x22\xf5\xf5\x3f\x57\x83\xcc\xfd\x05\x78\x05",32))
printf("strip: eb3cf625274ab55d, Pass\n");
else
printf("strip: eb3cf625274ab55d, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000062b0))=0x018a0012;
*((unsigned int *)((unsigned long)context_ptr+0x000062b0+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000062b0+4*2))=0x0202007a;
*((unsigned int *)((unsigned long)context_ptr+0x000062b0+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x000067d0))=0x490d30ba;
*((unsigned int *)((unsigned long)context_ptr+0x000067d0+4*1))=0x0474e7bd;
*((unsigned int *)((unsigned long)context_ptr+0x000067d0+4*2))=0x86d9f012;
*((unsigned int *)((unsigned long)context_ptr+0x000067d0+4*3))=0x9342e832;
*((unsigned int *)((unsigned long)context_ptr+0x000067d0+4*4))=0x8f03ccb9;
*((unsigned int *)((unsigned long)context_ptr+0x000067d0+4*5))=0x0a7c9548;
*((unsigned int *)((unsigned long)context_ptr+0x000067d0+4*6))=0xecaec5ff;
*((unsigned int *)((unsigned long)context_ptr+0x000067d0+4*7))=0x0df82c97;
*((unsigned int *)((unsigned long)context_ptr+0x000067d0+4*8))=0x8c54a40e;
*((unsigned int *)((unsigned long)context_ptr+0x000067d0+4*9))=0x9eb46454;
*((unsigned int *)((unsigned long)context_ptr+0x000067d0+4*10))=0xf46b56f0;
*((unsigned int *)((unsigned long)context_ptr+0x000067d0+4*11))=0xc9ca1ce8;
*((unsigned int *)((unsigned long)context_ptr+0x000067d0+4*12))=0x35ffb541;
*((unsigned int *)((unsigned long)context_ptr+0x000067d0+4*13))=0x8334f6c4;
*((unsigned int *)((unsigned long)context_ptr+0x000067d0+4*14))=0xaf9f80fb;
*((unsigned int *)((unsigned long)context_ptr+0x000067d0+4*15))=0x1d33cc6c;
*((unsigned int *)((unsigned long)context_ptr+0x000067d0+4*16))=0x66638abb;
*((unsigned int *)((unsigned long)context_ptr+0x000067d0+4*17))=0x87f55b6a;
*((unsigned int *)((unsigned long)context_ptr+0x000067d0+4*18))=0x64254ab7;
*((unsigned int *)((unsigned long)context_ptr+0x000067d0+4*19))=0x3a9cb6ba;
*((unsigned int *)((unsigned long)context_ptr+0x000067d0+4*20))=0x4b430dba;
*((unsigned int *)((unsigned long)context_ptr+0x000067d0+4*21))=0x5197a314;
*((unsigned int *)((unsigned long)context_ptr+0x000067d0+4*22))=0x8b3decdc;
*((unsigned int *)((unsigned long)context_ptr+0x000067d0+4*23))=0xaa1937e7;
*((unsigned int *)((unsigned long)context_ptr+0x000067d0+4*24))=0xb9af1ace;
*((unsigned int *)((unsigned long)context_ptr+0x000067d0+4*25))=0x53aa4b3a;
*((unsigned int *)((unsigned long)context_ptr+0x000067d0+4*26))=0xc81a1e07;
*((unsigned int *)((unsigned long)context_ptr+0x000067d0+4*27))=0x954a328c;
*((unsigned int *)((unsigned long)context_ptr+0x000067d0+4*28))=0x9cac7f2a;
*((unsigned int *)((unsigned long)context_ptr+0x000067d0+4*29))=0x45d03896;
*((unsigned int *)((unsigned long)context_ptr+0x000067d0+4*30))=0x000036d9;
*((unsigned int *)((unsigned long)context_ptr+0x00003b58))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003b58+4*1))=0x00006424;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000b58+4*1))=0x000067d0;
*((unsigned int *)((unsigned long)context_ptr+0x00000b58+4*2))=0x000062b0;
*((unsigned int *)((unsigned long)context_ptr+0x00000b58+4*3))=0x0222007a;
*((unsigned int *)((unsigned long)context_ptr+0x00000b58+4*4))=0x0e5351ca;
*((unsigned int *)((unsigned long)context_ptr+0x00000b58+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000288&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006544,"\x38\xd5\x70\x21\x4a\x55\xa1\xaa\x03\x7b\x64\x38\xb2\x93\xb3\xa8\x11\xb5\x76\x6a\xa9\x9a\x56\x44\x3b\xaf\x11\x0f\xe4\xac\x68\x40",32))
printf("strip: 38d570214a55a1aa, Pass\n");
else
printf("strip: 38d570214a55a1aa, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006444))=0x018a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006444+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006444+4*2))=0x0202007b;
*((unsigned int *)((unsigned long)context_ptr+0x00006444+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x00006a80))=0x47b7ed20;
*((unsigned int *)((unsigned long)context_ptr+0x00006a80+4*1))=0x3390b336;
*((unsigned int *)((unsigned long)context_ptr+0x00006a80+4*2))=0xc85dcf1d;
*((unsigned int *)((unsigned long)context_ptr+0x00006a80+4*3))=0xad39ec7f;
*((unsigned int *)((unsigned long)context_ptr+0x00006a80+4*4))=0x2bec3285;
*((unsigned int *)((unsigned long)context_ptr+0x00006a80+4*5))=0xc60ef9f2;
*((unsigned int *)((unsigned long)context_ptr+0x00006a80+4*6))=0x96ba378a;
*((unsigned int *)((unsigned long)context_ptr+0x00006a80+4*7))=0xc2f39a5e;
*((unsigned int *)((unsigned long)context_ptr+0x00006a80+4*8))=0xc89b926c;
*((unsigned int *)((unsigned long)context_ptr+0x00006a80+4*9))=0x76b443d6;
*((unsigned int *)((unsigned long)context_ptr+0x00006a80+4*10))=0x000de5b5;
*((unsigned int *)((unsigned long)context_ptr+0x00006a80+4*11))=0x62601678;
*((unsigned int *)((unsigned long)context_ptr+0x00006a80+4*12))=0x7119073a;
*((unsigned int *)((unsigned long)context_ptr+0x00006a80+4*13))=0xd2980157;
*((unsigned int *)((unsigned long)context_ptr+0x00006a80+4*14))=0x83b7ff74;
*((unsigned int *)((unsigned long)context_ptr+0x00006a80+4*15))=0xa25593d6;
*((unsigned int *)((unsigned long)context_ptr+0x00006a80+4*16))=0xc13d8a8a;
*((unsigned int *)((unsigned long)context_ptr+0x00006a80+4*17))=0xda565abd;
*((unsigned int *)((unsigned long)context_ptr+0x00006a80+4*18))=0x91636532;
*((unsigned int *)((unsigned long)context_ptr+0x00006a80+4*19))=0xa964e91b;
*((unsigned int *)((unsigned long)context_ptr+0x00006a80+4*20))=0xb413d8e0;
*((unsigned int *)((unsigned long)context_ptr+0x00006a80+4*21))=0xf73457d8;
*((unsigned int *)((unsigned long)context_ptr+0x00006a80+4*22))=0x5281f84c;
*((unsigned int *)((unsigned long)context_ptr+0x00006a80+4*23))=0x0256a674;
*((unsigned int *)((unsigned long)context_ptr+0x00006a80+4*24))=0x7e6665f5;
*((unsigned int *)((unsigned long)context_ptr+0x00006a80+4*25))=0x9778c863;
*((unsigned int *)((unsigned long)context_ptr+0x00006a80+4*26))=0xd7c827a0;
*((unsigned int *)((unsigned long)context_ptr+0x00006a80+4*27))=0xffb56e2a;
*((unsigned int *)((unsigned long)context_ptr+0x00006a80+4*28))=0x55c1e5a2;
*((unsigned int *)((unsigned long)context_ptr+0x00006a80+4*29))=0x76ca424a;
*((unsigned int *)((unsigned long)context_ptr+0x00006a80+4*30))=0x0001c501;
*((unsigned int *)((unsigned long)context_ptr+0x00003b70))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003b70+4*1))=0x00006038;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000b70+4*1))=0x00006a80;
*((unsigned int *)((unsigned long)context_ptr+0x00000b70+4*2))=0x00006444;
*((unsigned int *)((unsigned long)context_ptr+0x00000b70+4*3))=0x0222007b;
*((unsigned int *)((unsigned long)context_ptr+0x00000b70+4*4))=0x0a69e499;
*((unsigned int *)((unsigned long)context_ptr+0x00000b70+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000028e&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000062c0,"\x06\x94\xe3\x32\x52\xc7\x22\x90\xc1\x7f\x20\x5a\x8f\x5a\x14\xb4\x17\x53\xda\x7b\xa3\x9e\x3e\xf7\xe4\xea\xcf\x2c\xaf\xd2\x5c\x68",32))
printf("strip: 0694e33252c72290, Pass\n");
else
printf("strip: 0694e33252c72290, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006018))=0x018a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006018+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006018+4*2))=0x0202007c;
*((unsigned int *)((unsigned long)context_ptr+0x00006018+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x00006694))=0xbbeb6a95;
*((unsigned int *)((unsigned long)context_ptr+0x00006694+4*1))=0x82e51889;
*((unsigned int *)((unsigned long)context_ptr+0x00006694+4*2))=0x7482b456;
*((unsigned int *)((unsigned long)context_ptr+0x00006694+4*3))=0x82ad08b7;
*((unsigned int *)((unsigned long)context_ptr+0x00006694+4*4))=0x03d4f0bf;
*((unsigned int *)((unsigned long)context_ptr+0x00006694+4*5))=0xef505a73;
*((unsigned int *)((unsigned long)context_ptr+0x00006694+4*6))=0x1d0996bf;
*((unsigned int *)((unsigned long)context_ptr+0x00006694+4*7))=0x78e2e66e;
*((unsigned int *)((unsigned long)context_ptr+0x00006694+4*8))=0x0abe7e29;
*((unsigned int *)((unsigned long)context_ptr+0x00006694+4*9))=0xf2a7c670;
*((unsigned int *)((unsigned long)context_ptr+0x00006694+4*10))=0x26bab66b;
*((unsigned int *)((unsigned long)context_ptr+0x00006694+4*11))=0x00958d60;
*((unsigned int *)((unsigned long)context_ptr+0x00006694+4*12))=0x53f989a7;
*((unsigned int *)((unsigned long)context_ptr+0x00006694+4*13))=0x2979864e;
*((unsigned int *)((unsigned long)context_ptr+0x00006694+4*14))=0x95861a7c;
*((unsigned int *)((unsigned long)context_ptr+0x00006694+4*15))=0x30e86ac6;
*((unsigned int *)((unsigned long)context_ptr+0x00006694+4*16))=0x044091be;
*((unsigned int *)((unsigned long)context_ptr+0x00006694+4*17))=0xad7d132a;
*((unsigned int *)((unsigned long)context_ptr+0x00006694+4*18))=0xafb4a67e;
*((unsigned int *)((unsigned long)context_ptr+0x00006694+4*19))=0x20d8c607;
*((unsigned int *)((unsigned long)context_ptr+0x00006694+4*20))=0x0a23a72d;
*((unsigned int *)((unsigned long)context_ptr+0x00006694+4*21))=0xa644a2ed;
*((unsigned int *)((unsigned long)context_ptr+0x00006694+4*22))=0xef1b6265;
*((unsigned int *)((unsigned long)context_ptr+0x00006694+4*23))=0xa5ebb370;
*((unsigned int *)((unsigned long)context_ptr+0x00006694+4*24))=0x5317a6b4;
*((unsigned int *)((unsigned long)context_ptr+0x00006694+4*25))=0x5f4051e3;
*((unsigned int *)((unsigned long)context_ptr+0x00006694+4*26))=0x9ad96a17;
*((unsigned int *)((unsigned long)context_ptr+0x00006694+4*27))=0x4e9a7f86;
*((unsigned int *)((unsigned long)context_ptr+0x00006694+4*28))=0x368a99ce;
*((unsigned int *)((unsigned long)context_ptr+0x00006694+4*29))=0x4662ebc2;
*((unsigned int *)((unsigned long)context_ptr+0x00006694+4*30))=0xeb2123bf;
*((unsigned int *)((unsigned long)context_ptr+0x00003b88))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003b88+4*1))=0x000062c0;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000b88+4*1))=0x00006694;
*((unsigned int *)((unsigned long)context_ptr+0x00000b88+4*2))=0x00006018;
*((unsigned int *)((unsigned long)context_ptr+0x00000b88+4*3))=0x0222007c;
*((unsigned int *)((unsigned long)context_ptr+0x00000b88+4*4))=0x0ecea7b0;
*((unsigned int *)((unsigned long)context_ptr+0x00000b88+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000294&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006770,"\x4f\x61\x6e\x9f\x12\x51\xc5\x9d\x79\x7d\xdd\x0b\xd7\xd2\x9d\x4f\x29\x88\xcc\x8e\x14\xfc\x3b\xdb\x89\x47\x1a\x5f\xc5\x20\xf1\x00",32))
printf("strip: 4f616e9f1251c59d, Pass\n");
else
printf("strip: 4f616e9f1251c59d, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006008))=0x018a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006008+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006008+4*2))=0x0202007d;
*((unsigned int *)((unsigned long)context_ptr+0x00006008+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x00006710))=0x3013fe65;
*((unsigned int *)((unsigned long)context_ptr+0x00006710+4*1))=0xecaa9227;
*((unsigned int *)((unsigned long)context_ptr+0x00006710+4*2))=0x423ec346;
*((unsigned int *)((unsigned long)context_ptr+0x00006710+4*3))=0x9445d50c;
*((unsigned int *)((unsigned long)context_ptr+0x00006710+4*4))=0x44eb8718;
*((unsigned int *)((unsigned long)context_ptr+0x00006710+4*5))=0x55542f99;
*((unsigned int *)((unsigned long)context_ptr+0x00006710+4*6))=0x18726746;
*((unsigned int *)((unsigned long)context_ptr+0x00006710+4*7))=0xb5922d81;
*((unsigned int *)((unsigned long)context_ptr+0x00006710+4*8))=0x11eace5b;
*((unsigned int *)((unsigned long)context_ptr+0x00006710+4*9))=0x0847d670;
*((unsigned int *)((unsigned long)context_ptr+0x00006710+4*10))=0xdc1aef74;
*((unsigned int *)((unsigned long)context_ptr+0x00006710+4*11))=0xd92f8280;
*((unsigned int *)((unsigned long)context_ptr+0x00006710+4*12))=0xf592d3c5;
*((unsigned int *)((unsigned long)context_ptr+0x00006710+4*13))=0xdb642eaa;
*((unsigned int *)((unsigned long)context_ptr+0x00006710+4*14))=0x205098b4;
*((unsigned int *)((unsigned long)context_ptr+0x00006710+4*15))=0x72e844ec;
*((unsigned int *)((unsigned long)context_ptr+0x00006710+4*16))=0xa0211cb3;
*((unsigned int *)((unsigned long)context_ptr+0x00006710+4*17))=0x50a89e7f;
*((unsigned int *)((unsigned long)context_ptr+0x00006710+4*18))=0x25df0985;
*((unsigned int *)((unsigned long)context_ptr+0x00006710+4*19))=0xda03232f;
*((unsigned int *)((unsigned long)context_ptr+0x00006710+4*20))=0xa64f44c4;
*((unsigned int *)((unsigned long)context_ptr+0x00006710+4*21))=0xcfd428b3;
*((unsigned int *)((unsigned long)context_ptr+0x00006710+4*22))=0x190c08ab;
*((unsigned int *)((unsigned long)context_ptr+0x00006710+4*23))=0x6745a0b2;
*((unsigned int *)((unsigned long)context_ptr+0x00006710+4*24))=0xa7b34233;
*((unsigned int *)((unsigned long)context_ptr+0x00006710+4*25))=0xf3e32929;
*((unsigned int *)((unsigned long)context_ptr+0x00006710+4*26))=0x2c561053;
*((unsigned int *)((unsigned long)context_ptr+0x00006710+4*27))=0x14f97551;
*((unsigned int *)((unsigned long)context_ptr+0x00006710+4*28))=0xf77e390a;
*((unsigned int *)((unsigned long)context_ptr+0x00006710+4*29))=0xee4ccd3a;
*((unsigned int *)((unsigned long)context_ptr+0x00006710+4*30))=0x2e9d9081;
*((unsigned int *)((unsigned long)context_ptr+0x00006710+4*31))=0x0000009b;
*((unsigned int *)((unsigned long)context_ptr+0x00003ba0))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003ba0+4*1))=0x00006540;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000ba0+4*1))=0x00006710;
*((unsigned int *)((unsigned long)context_ptr+0x00000ba0+4*2))=0x00006008;
*((unsigned int *)((unsigned long)context_ptr+0x00000ba0+4*3))=0x0222007d;
*((unsigned int *)((unsigned long)context_ptr+0x00000ba0+4*4))=0x04ea08ab;
*((unsigned int *)((unsigned long)context_ptr+0x00000ba0+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000029a&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006654,"\x34\x7d\x9e\x19\xb9\x0a\xf5\x82\x21\x6d\xd1\xc0\xb8\x26\x9b\x75\xd8\xa8\xe9\xf9\x55\xf0\x7b\xba\x64\xad\x5f\xae\xf1\x64\xb8\x29",32))
printf("strip: 347d9e19b90af582, Pass\n");
else
printf("strip: 347d9e19b90af582, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006028))=0x018a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006028+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006028+4*2))=0x0202007e;
*((unsigned int *)((unsigned long)context_ptr+0x00006028+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x000065e4))=0x65121a6b;
*((unsigned int *)((unsigned long)context_ptr+0x000065e4+4*1))=0x644dc04f;
*((unsigned int *)((unsigned long)context_ptr+0x000065e4+4*2))=0x38fb7cb4;
*((unsigned int *)((unsigned long)context_ptr+0x000065e4+4*3))=0x092145b9;
*((unsigned int *)((unsigned long)context_ptr+0x000065e4+4*4))=0xefe82262;
*((unsigned int *)((unsigned long)context_ptr+0x000065e4+4*5))=0x58856b96;
*((unsigned int *)((unsigned long)context_ptr+0x000065e4+4*6))=0x2dd59280;
*((unsigned int *)((unsigned long)context_ptr+0x000065e4+4*7))=0x46e668e2;
*((unsigned int *)((unsigned long)context_ptr+0x000065e4+4*8))=0x20c42aaf;
*((unsigned int *)((unsigned long)context_ptr+0x000065e4+4*9))=0x89fa3469;
*((unsigned int *)((unsigned long)context_ptr+0x000065e4+4*10))=0x44186a2c;
*((unsigned int *)((unsigned long)context_ptr+0x000065e4+4*11))=0x81dae11f;
*((unsigned int *)((unsigned long)context_ptr+0x000065e4+4*12))=0x330330b1;
*((unsigned int *)((unsigned long)context_ptr+0x000065e4+4*13))=0x2743a16a;
*((unsigned int *)((unsigned long)context_ptr+0x000065e4+4*14))=0xcda658ad;
*((unsigned int *)((unsigned long)context_ptr+0x000065e4+4*15))=0x39cb5444;
*((unsigned int *)((unsigned long)context_ptr+0x000065e4+4*16))=0x81da213f;
*((unsigned int *)((unsigned long)context_ptr+0x000065e4+4*17))=0x4239d3c3;
*((unsigned int *)((unsigned long)context_ptr+0x000065e4+4*18))=0xf4549957;
*((unsigned int *)((unsigned long)context_ptr+0x000065e4+4*19))=0x55fe0b62;
*((unsigned int *)((unsigned long)context_ptr+0x000065e4+4*20))=0x7b4b11a1;
*((unsigned int *)((unsigned long)context_ptr+0x000065e4+4*21))=0xebde59c0;
*((unsigned int *)((unsigned long)context_ptr+0x000065e4+4*22))=0x4d9394dd;
*((unsigned int *)((unsigned long)context_ptr+0x000065e4+4*23))=0xb657071d;
*((unsigned int *)((unsigned long)context_ptr+0x000065e4+4*24))=0x63ed7886;
*((unsigned int *)((unsigned long)context_ptr+0x000065e4+4*25))=0x3663418a;
*((unsigned int *)((unsigned long)context_ptr+0x000065e4+4*26))=0x416cb2b4;
*((unsigned int *)((unsigned long)context_ptr+0x000065e4+4*27))=0x8654e74a;
*((unsigned int *)((unsigned long)context_ptr+0x000065e4+4*28))=0x7655878b;
*((unsigned int *)((unsigned long)context_ptr+0x000065e4+4*29))=0x02c03256;
*((unsigned int *)((unsigned long)context_ptr+0x000065e4+4*30))=0x194c65cb;
*((unsigned int *)((unsigned long)context_ptr+0x000065e4+4*31))=0x000042fb;
*((unsigned int *)((unsigned long)context_ptr+0x00003bb8))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003bb8+4*1))=0x0000684c;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000bb8+4*1))=0x000065e4;
*((unsigned int *)((unsigned long)context_ptr+0x00000bb8+4*2))=0x00006028;
*((unsigned int *)((unsigned long)context_ptr+0x00000bb8+4*3))=0x0222007e;
*((unsigned int *)((unsigned long)context_ptr+0x00000bb8+4*4))=0x0f9ddc2e;
*((unsigned int *)((unsigned long)context_ptr+0x00000bb8+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000002a0&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000068f8,"\xbd\xf7\xfc\x68\x02\xeb\x3d\x68\xf4\x3d\x6c\x2c\xc1\x2c\xf2\x27\x7f\xb3\x31\xed\x74\x8b\xa6\x31\xc1\x77\x28\xeb\x12\xdb\x40\xf1",32))
printf("strip: bdf7fc6802eb3d68, Pass\n");
else
printf("strip: bdf7fc6802eb3d68, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006664))=0x018a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006664+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006664+4*2))=0x0202007f;
*((unsigned int *)((unsigned long)context_ptr+0x00006664+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x0000686c))=0xd3293760;
*((unsigned int *)((unsigned long)context_ptr+0x0000686c+4*1))=0x9c8e65b3;
*((unsigned int *)((unsigned long)context_ptr+0x0000686c+4*2))=0x8c439665;
*((unsigned int *)((unsigned long)context_ptr+0x0000686c+4*3))=0x75941bb5;
*((unsigned int *)((unsigned long)context_ptr+0x0000686c+4*4))=0xa2d3360b;
*((unsigned int *)((unsigned long)context_ptr+0x0000686c+4*5))=0x3853cfa5;
*((unsigned int *)((unsigned long)context_ptr+0x0000686c+4*6))=0x342b6bb5;
*((unsigned int *)((unsigned long)context_ptr+0x0000686c+4*7))=0x191d3042;
*((unsigned int *)((unsigned long)context_ptr+0x0000686c+4*8))=0xda4e75d9;
*((unsigned int *)((unsigned long)context_ptr+0x0000686c+4*9))=0x7df11a5c;
*((unsigned int *)((unsigned long)context_ptr+0x0000686c+4*10))=0xcecb1250;
*((unsigned int *)((unsigned long)context_ptr+0x0000686c+4*11))=0x5677f1fb;
*((unsigned int *)((unsigned long)context_ptr+0x0000686c+4*12))=0x602fbb5a;
*((unsigned int *)((unsigned long)context_ptr+0x0000686c+4*13))=0x2bce391f;
*((unsigned int *)((unsigned long)context_ptr+0x0000686c+4*14))=0x289b7a6c;
*((unsigned int *)((unsigned long)context_ptr+0x0000686c+4*15))=0x91b3faaa;
*((unsigned int *)((unsigned long)context_ptr+0x0000686c+4*16))=0xdaeb1083;
*((unsigned int *)((unsigned long)context_ptr+0x0000686c+4*17))=0xa2ce2d06;
*((unsigned int *)((unsigned long)context_ptr+0x0000686c+4*18))=0xd4a67cf2;
*((unsigned int *)((unsigned long)context_ptr+0x0000686c+4*19))=0x9d303d97;
*((unsigned int *)((unsigned long)context_ptr+0x0000686c+4*20))=0x5f42afcc;
*((unsigned int *)((unsigned long)context_ptr+0x0000686c+4*21))=0x3a01a087;
*((unsigned int *)((unsigned long)context_ptr+0x0000686c+4*22))=0xcdf2c3a7;
*((unsigned int *)((unsigned long)context_ptr+0x0000686c+4*23))=0x1e963bf4;
*((unsigned int *)((unsigned long)context_ptr+0x0000686c+4*24))=0xbcb03e9b;
*((unsigned int *)((unsigned long)context_ptr+0x0000686c+4*25))=0x186e0b7c;
*((unsigned int *)((unsigned long)context_ptr+0x0000686c+4*26))=0x23ebd68c;
*((unsigned int *)((unsigned long)context_ptr+0x0000686c+4*27))=0x9bdf3294;
*((unsigned int *)((unsigned long)context_ptr+0x0000686c+4*28))=0x9043c615;
*((unsigned int *)((unsigned long)context_ptr+0x0000686c+4*29))=0x29b5de58;
*((unsigned int *)((unsigned long)context_ptr+0x0000686c+4*30))=0x47cc3334;
*((unsigned int *)((unsigned long)context_ptr+0x0000686c+4*31))=0x00f30366;
*((unsigned int *)((unsigned long)context_ptr+0x00003bd0))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003bd0+4*1))=0x000068ec;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000bd0+4*1))=0x0000686c;
*((unsigned int *)((unsigned long)context_ptr+0x00000bd0+4*2))=0x00006664;
*((unsigned int *)((unsigned long)context_ptr+0x00000bd0+4*3))=0x0222007f;
*((unsigned int *)((unsigned long)context_ptr+0x00000bd0+4*4))=0x016ddbd9;
*((unsigned int *)((unsigned long)context_ptr+0x00000bd0+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000002a6&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006790,"\x78\x4d\x80\x58\x7d\x56\xda\x17\x52\x16\xd9\xb6\x05\x6d\x6b\xc2\x31\xd1\x70\x5e\x4d\x8a\xb4\x5b\x5b\x20\x0f\x1b\xa9\x25\xd7\x18",32))
printf("strip: 784d80587d56da17, Pass\n");
else
printf("strip: 784d80587d56da17, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006674))=0x018a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006674+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006674+4*2))=0x02020080;
*((unsigned int *)((unsigned long)context_ptr+0x00006674+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x000062e0))=0xa0bd9905;
*((unsigned int *)((unsigned long)context_ptr+0x000062e0+4*1))=0xbcad0e9d;
*((unsigned int *)((unsigned long)context_ptr+0x000062e0+4*2))=0x7960c646;
*((unsigned int *)((unsigned long)context_ptr+0x000062e0+4*3))=0x941aa03b;
*((unsigned int *)((unsigned long)context_ptr+0x000062e0+4*4))=0x8a933b55;
*((unsigned int *)((unsigned long)context_ptr+0x000062e0+4*5))=0xdab77b3b;
*((unsigned int *)((unsigned long)context_ptr+0x000062e0+4*6))=0x506f0012;
*((unsigned int *)((unsigned long)context_ptr+0x000062e0+4*7))=0xf3d95ae6;
*((unsigned int *)((unsigned long)context_ptr+0x000062e0+4*8))=0x192d4ce4;
*((unsigned int *)((unsigned long)context_ptr+0x000062e0+4*9))=0x408be758;
*((unsigned int *)((unsigned long)context_ptr+0x000062e0+4*10))=0xea550bbe;
*((unsigned int *)((unsigned long)context_ptr+0x000062e0+4*11))=0x94a1c243;
*((unsigned int *)((unsigned long)context_ptr+0x000062e0+4*12))=0x575195c8;
*((unsigned int *)((unsigned long)context_ptr+0x000062e0+4*13))=0x3607c31e;
*((unsigned int *)((unsigned long)context_ptr+0x000062e0+4*14))=0x95eba041;
*((unsigned int *)((unsigned long)context_ptr+0x000062e0+4*15))=0x6ed1e808;
*((unsigned int *)((unsigned long)context_ptr+0x000062e0+4*16))=0x957ff50d;
*((unsigned int *)((unsigned long)context_ptr+0x000062e0+4*17))=0x2008dcab;
*((unsigned int *)((unsigned long)context_ptr+0x000062e0+4*18))=0x9e9eb4d2;
*((unsigned int *)((unsigned long)context_ptr+0x000062e0+4*19))=0xfe253220;
*((unsigned int *)((unsigned long)context_ptr+0x000062e0+4*20))=0x4a08f450;
*((unsigned int *)((unsigned long)context_ptr+0x000062e0+4*21))=0x65546477;
*((unsigned int *)((unsigned long)context_ptr+0x000062e0+4*22))=0xc33ed15c;
*((unsigned int *)((unsigned long)context_ptr+0x000062e0+4*23))=0x144413db;
*((unsigned int *)((unsigned long)context_ptr+0x000062e0+4*24))=0x966a079f;
*((unsigned int *)((unsigned long)context_ptr+0x000062e0+4*25))=0x3eb1dd03;
*((unsigned int *)((unsigned long)context_ptr+0x000062e0+4*26))=0xf05a1a4f;
*((unsigned int *)((unsigned long)context_ptr+0x000062e0+4*27))=0xf8af3cc5;
*((unsigned int *)((unsigned long)context_ptr+0x000062e0+4*28))=0xc0891f10;
*((unsigned int *)((unsigned long)context_ptr+0x000062e0+4*29))=0x9346f320;
*((unsigned int *)((unsigned long)context_ptr+0x000062e0+4*30))=0x9d87dd52;
*((unsigned int *)((unsigned long)context_ptr+0x000062e0+4*31))=0xb81cfc2b;
*((unsigned int *)((unsigned long)context_ptr+0x00003be8))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003be8+4*1))=0x00006790;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000be8+4*1))=0x000062e0;
*((unsigned int *)((unsigned long)context_ptr+0x00000be8+4*2))=0x00006674;
*((unsigned int *)((unsigned long)context_ptr+0x00000be8+4*3))=0x02220080;
*((unsigned int *)((unsigned long)context_ptr+0x00000be8+4*4))=0x00f37d68;
*((unsigned int *)((unsigned long)context_ptr+0x00000be8+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000002ac&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000063c4,"\xe9\x82\xbf\xd0\x79\x12\x5c\x89\xc3\x11\x1c\x01\xc4\xce\x91\xfb\x6e\x82\xd4\xfc\x12\x6d\x86\xd0\x70\x6d\x40\xaa\xd7\xa9\xbb\xf3",32))
printf("strip: e982bfd079125c89, Pass\n");
else
printf("strip: e982bfd079125c89, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006684))=0x018a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006684+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006684+4*2))=0x02020081;
*((unsigned int *)((unsigned long)context_ptr+0x00006684+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x00006360))=0x82d8bbaf;
*((unsigned int *)((unsigned long)context_ptr+0x00006360+4*1))=0x56f861cf;
*((unsigned int *)((unsigned long)context_ptr+0x00006360+4*2))=0x57900310;
*((unsigned int *)((unsigned long)context_ptr+0x00006360+4*3))=0x5c937160;
*((unsigned int *)((unsigned long)context_ptr+0x00006360+4*4))=0x0ed1407a;
*((unsigned int *)((unsigned long)context_ptr+0x00006360+4*5))=0x492d7fe1;
*((unsigned int *)((unsigned long)context_ptr+0x00006360+4*6))=0x9ef726a6;
*((unsigned int *)((unsigned long)context_ptr+0x00006360+4*7))=0x1fe1e4dd;
*((unsigned int *)((unsigned long)context_ptr+0x00006360+4*8))=0x52b7dca0;
*((unsigned int *)((unsigned long)context_ptr+0x00006360+4*9))=0xeb9a019b;
*((unsigned int *)((unsigned long)context_ptr+0x00006360+4*10))=0x820fc664;
*((unsigned int *)((unsigned long)context_ptr+0x00006360+4*11))=0x21351906;
*((unsigned int *)((unsigned long)context_ptr+0x00006360+4*12))=0x16b60c08;
*((unsigned int *)((unsigned long)context_ptr+0x00006360+4*13))=0x287938a4;
*((unsigned int *)((unsigned long)context_ptr+0x00006360+4*14))=0x276f4bb7;
*((unsigned int *)((unsigned long)context_ptr+0x00006360+4*15))=0x0d008b05;
*((unsigned int *)((unsigned long)context_ptr+0x00006360+4*16))=0x788cff42;
*((unsigned int *)((unsigned long)context_ptr+0x00006360+4*17))=0xb1749929;
*((unsigned int *)((unsigned long)context_ptr+0x00006360+4*18))=0x07772a98;
*((unsigned int *)((unsigned long)context_ptr+0x00006360+4*19))=0x9ec21ca3;
*((unsigned int *)((unsigned long)context_ptr+0x00006360+4*20))=0x30c0f24b;
*((unsigned int *)((unsigned long)context_ptr+0x00006360+4*21))=0x2c43cc47;
*((unsigned int *)((unsigned long)context_ptr+0x00006360+4*22))=0x2e383343;
*((unsigned int *)((unsigned long)context_ptr+0x00006360+4*23))=0x5574f32f;
*((unsigned int *)((unsigned long)context_ptr+0x00006360+4*24))=0x973bce8d;
*((unsigned int *)((unsigned long)context_ptr+0x00006360+4*25))=0x99836fd6;
*((unsigned int *)((unsigned long)context_ptr+0x00006360+4*26))=0x9ecd5742;
*((unsigned int *)((unsigned long)context_ptr+0x00006360+4*27))=0x9d4e3ead;
*((unsigned int *)((unsigned long)context_ptr+0x00006360+4*28))=0x1eefe430;
*((unsigned int *)((unsigned long)context_ptr+0x00006360+4*29))=0x194f6306;
*((unsigned int *)((unsigned long)context_ptr+0x00006360+4*30))=0xeb81eec7;
*((unsigned int *)((unsigned long)context_ptr+0x00006360+4*31))=0xa7cd42f7;
*((unsigned int *)((unsigned long)context_ptr+0x00006360+4*32))=0x00000051;
*((unsigned int *)((unsigned long)context_ptr+0x00003c00))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003c00+4*1))=0x000069a0;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000c00+4*1))=0x00006360;
*((unsigned int *)((unsigned long)context_ptr+0x00000c00+4*2))=0x00006684;
*((unsigned int *)((unsigned long)context_ptr+0x00000c00+4*3))=0x02220081;
*((unsigned int *)((unsigned long)context_ptr+0x00000c00+4*4))=0x08b73653;
*((unsigned int *)((unsigned long)context_ptr+0x00000c00+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000002b2&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000067b0,"\x3f\x99\x28\x03\x54\xe7\x50\xae\x42\xbb\xa7\x5b\xcd\xcd\xaa\x89\x95\x3b\xe7\x01\x5e\x15\x12\x70\x65\x78\xd6\x6a\xb3\x70\xf9\x59",32))
printf("strip: 3f99280354e750ae, Pass\n");
else
printf("strip: 3f99280354e750ae, Failed\n");
writel(0x000002b8&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000063e4,"\xce\xf6\x0a\x33\x6f\x8e\xea\x0f\xeb\x6d\xbe\x8e\xaf\x20\xa7\x61\xde\x6f\x56\xe1\xa6\x22\xfe\xa4\x74\x3f\x51\x60\xe6\xff\xb1\xf4",32))
printf("strip: cef60a336f8eea0f, Pass\n");
else
printf("strip: cef60a336f8eea0f, Failed\n");
writel(0x000002be&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000064e0,"\xbe\x77\xfc\xa5\xac\x5f\x28\x05\x39\x98\x20\xdc\xfa\xe0\xf9\x33\x69\x89\x5b\x1a\x5d\x48\xfe\x06\xb3\x61\x06\xe6\x37\x95\xc4\xd0",32))
printf("strip: be77fca5ac5f2805, Pass\n");
else
printf("strip: be77fca5ac5f2805, Failed\n");
writel(0x000002c4&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006584,"\x95\x9a\x06\x64\x88\x3a\x88\x54\xca\x47\xa4\x69\x6f\x1e\x88\xb6\xf2\xea\x73\xf2\x2e\x44\x58\xde\xd1\x84\xa1\xf1\xde\x77\xb6\x85",32))
printf("strip: 959a0664883a8854, Pass\n");
else
printf("strip: 959a0664883a8854, Failed\n");
writel(0x000002ca&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000065a4,"\x03\xb0\x17\x37\xb1\x56\xe0\x49\x03\x42\x4f\xe3\xac\xa4\x37\x0f\x5d\x45\xbe\x50\x62\x42\xb1\xec\x9c\xa8\x39\x2d\x16\x54\xb9\x0c",32))
printf("strip: 03b01737b156e049, Pass\n");
else
printf("strip: 03b01737b156e049, Failed\n");
writel(0x000002d0&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006404,"\xce\x8f\x36\x0a\x95\x67\x18\x19\xce\x3e\xad\xf3\xeb\x10\x39\x27\x9d\x65\x80\xa2\xad\x4f\x16\x3a\x8f\x47\xeb\x84\x44\x0e\x9b\xe4",32))
printf("strip: ce8f360a95671819, Pass\n");
else
printf("strip: ce8f360a95671819, Failed\n");
writel(0x000002d6&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006520,"\x17\xf6\x76\xfd\xc3\x52\x15\x83\x3a\x81\xd7\x87\xbc\x1f\x56\xe7\x21\x1b\x26\xf4\xaf\x85\x02\x20\xfe\xb5\xf7\x1a\x16\x19\xf3\x48",32))
printf("strip: 17f676fdc3521583, Pass\n");
else
printf("strip: 17f676fdc3521583, Failed\n");
writel(0x000002dc&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006424,"\xe0\x93\x44\x60\xdb\x33\x32\x8c\x14\x79\xf8\x55\x0e\xae\x7f\xe7\x40\x10\xee\x11\x02\x7a\xbd\x16\xef\xe8\xae\x84\x69\x93\xbd\xb8",32))
printf("strip: e0934460db33328c, Pass\n");
else
printf("strip: e0934460db33328c, Failed\n");
writel(0x000002e2&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006038,"\x1b\xab\x31\x27\x69\x6f\x4f\x8a\x08\x97\x6c\x0c\x2d\x5f\x1f\x87\x5c\x3f\x9f\xba\x14\x99\x28\xff\x09\x69\x8e\x2b\x89\x15\xfb\xf2",32))
printf("strip: 1bab3127696f4f8a, Pass\n");
else
printf("strip: 1bab3127696f4f8a, Failed\n");
writel(0x000002e8&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000062c0,"\x74\x5a\x13\xbd\x36\xf1\xed\xaa\x78\x23\x14\x3f\xda\x2b\x6f\xe9\x0a\x71\x4e\x0f\xee\xac\x86\xc6\x93\x75\x51\x20\x03\x76\xed\x0e",32))
printf("strip: 745a13bd36f1edaa, Pass\n");
else
printf("strip: 745a13bd36f1edaa, Failed\n");
writel(0x000002ee&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006540,"\x19\x2c\x10\x05\x26\xfe\x78\xdd\x5e\x3d\xee\xd5\xa8\x09\x4d\x80\x8f\x72\xd5\x3f\x9b\x57\x12\x17\xb3\x51\x18\xb5\x82\xc5\x23\x0f",32))
printf("strip: 192c100526fe78dd, Pass\n");
else
printf("strip: 192c100526fe78dd, Failed\n");
writel(0x000002f4&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x0000684c,"\x64\x23\x8d\x3a\x55\x27\x0b\x58\x40\xff\xad\x76\xae\x4f\x70\xb6\xb1\x94\x1a\x98\xcf\xb7\x7d\x59\x50\x44\x6d\x07\x34\xb0\xc5\x00",32))
printf("strip: 64238d3a55270b58, Pass\n");
else
printf("strip: 64238d3a55270b58, Failed\n");
writel(0x000002fa&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000068ec,"\x5c\x26\xc5\x0a\x8d\xe6\xb4\x2a\x45\x64\xbe\xe8\x30\x96\x98\x11\x8a\x95\x97\x55\x6f\x97\x2c\x5e\xcb\xe4\x16\x7c\x41\x11\x0a\xf2",32))
printf("strip: 5c26c50a8de6b42a, Pass\n");
else
printf("strip: 5c26c50a8de6b42a, Failed\n");
writel(0x00000300&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
writel(0x00000c00&0xffffffff,ivp_cae_base_addr+0x00000830);
if(!memcmp((unsigned char *)context_ptr+0x00006790,"\xb8\x10\xca\xa4\xf7\xba\x96\x72\xf6\x72\xbd\x03\x02\xbb\x68\xd0\xea\xa7\x60\x63\x3d\x53\x83\x12\x79\x69\xba\xcc\x41\x83\xfb\x29",32))
printf("strip: b810caa4f7ba9672, Pass\n");
else
printf("strip: b810caa4f7ba9672, Failed\n");
writel(0x00000006&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000069a0,"\xb9\x80\x47\x96\xf0\x71\x27\x91\xd9\xf6\xa7\x4b\x55\x31\x46\x7e\x31\x1e\x59\x02\xd1\xa5\x16\x47\x38\xf5\x19\xb8\x3f\x21\xe5\xc1",32))
printf("strip: b9804796f0712791, Pass\n");
else
printf("strip: b9804796f0712791, Failed\n");
}

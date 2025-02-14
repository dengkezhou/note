#include <common.h>
#include <malloc.h>

extern volatile unsigned int ivp_cae_base_addr;

void test_bypass(void)
{
unsigned int *context_ptr=(unsigned int *)0x14000000;
printf("test_bypass\n");
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
*((unsigned int *)((unsigned long)context_ptr+0x00006000))=0x010a0000;
*((unsigned int *)((unsigned long)context_ptr+0x00006000+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006008))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x00006008+4*1))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x00006008+4*2))=0x01060001;
*((unsigned int *)((unsigned long)context_ptr+0x00006014))=0x000000fb;
*((unsigned int *)((unsigned long)context_ptr+0x00003000))=0x04c00001;
*((unsigned int *)((unsigned long)context_ptr+0x00003000+4*1))=0x00006018;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000000))=0x03c00001;
*((unsigned int *)((unsigned long)context_ptr+0x00000000+4*1))=0x00006014;
*((unsigned int *)((unsigned long)context_ptr+0x00000000+4*2))=0x00006008;
*((unsigned int *)((unsigned long)context_ptr+0x00000000+4*3))=0x02220001;
*((unsigned int *)((unsigned long)context_ptr+0x00000000+4*4))=0x00ad4ab1;
*((unsigned int *)((unsigned long)context_ptr+0x00000000+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x0000601c))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x0000601c+4*1))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x0000601c+4*2))=0x01060002;
*((unsigned int *)((unsigned long)context_ptr+0x00006028))=0x000009d1;
*((unsigned int *)((unsigned long)context_ptr+0x00003018))=0x04c00002;
*((unsigned int *)((unsigned long)context_ptr+0x00003018+4*1))=0x0000602c;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000018))=0x03c00002;
*((unsigned int *)((unsigned long)context_ptr+0x00000018+4*1))=0x00006028;
*((unsigned int *)((unsigned long)context_ptr+0x00000018+4*2))=0x0000601c;
*((unsigned int *)((unsigned long)context_ptr+0x00000018+4*3))=0x02220002;
*((unsigned int *)((unsigned long)context_ptr+0x00000018+4*4))=0x00e0ae1a;
*((unsigned int *)((unsigned long)context_ptr+0x00000018+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x00006030))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x00006030+4*1))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x00006030+4*2))=0x01060003;
*((unsigned int *)((unsigned long)context_ptr+0x0000603c))=0x00a72629;
*((unsigned int *)((unsigned long)context_ptr+0x00003030))=0x04c00003;
*((unsigned int *)((unsigned long)context_ptr+0x00003030+4*1))=0x00006040;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000030))=0x03c00003;
*((unsigned int *)((unsigned long)context_ptr+0x00000030+4*1))=0x0000603c;
*((unsigned int *)((unsigned long)context_ptr+0x00000030+4*2))=0x00006030;
*((unsigned int *)((unsigned long)context_ptr+0x00000030+4*3))=0x02220003;
*((unsigned int *)((unsigned long)context_ptr+0x00000030+4*4))=0x00d7a328;
*((unsigned int *)((unsigned long)context_ptr+0x00000030+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x00006044))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x00006044+4*1))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x00006044+4*2))=0x01060004;
*((unsigned int *)((unsigned long)context_ptr+0x00006050))=0xd99663ca;
*((unsigned int *)((unsigned long)context_ptr+0x00003048))=0x04c00004;
*((unsigned int *)((unsigned long)context_ptr+0x00003048+4*1))=0x00006054;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000048))=0x03c00004;
*((unsigned int *)((unsigned long)context_ptr+0x00000048+4*1))=0x00006050;
*((unsigned int *)((unsigned long)context_ptr+0x00000048+4*2))=0x00006044;
*((unsigned int *)((unsigned long)context_ptr+0x00000048+4*3))=0x02220004;
*((unsigned int *)((unsigned long)context_ptr+0x00000048+4*4))=0x00809f29;
*((unsigned int *)((unsigned long)context_ptr+0x00000048+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x00006058))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*1))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*2))=0x01060005;
*((unsigned int *)((unsigned long)context_ptr+0x00006064))=0x6a090ed4;
*((unsigned int *)((unsigned long)context_ptr+0x00006064+4*1))=0x0000007d;
*((unsigned int *)((unsigned long)context_ptr+0x00003060))=0x04c00005;
*((unsigned int *)((unsigned long)context_ptr+0x00003060+4*1))=0x0000606c;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000060))=0x03c00005;
*((unsigned int *)((unsigned long)context_ptr+0x00000060+4*1))=0x00006064;
*((unsigned int *)((unsigned long)context_ptr+0x00000060+4*2))=0x00006058;
*((unsigned int *)((unsigned long)context_ptr+0x00000060+4*3))=0x02220005;
*((unsigned int *)((unsigned long)context_ptr+0x00000060+4*4))=0x002e9583;
*((unsigned int *)((unsigned long)context_ptr+0x00000060+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x00006074))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x00006074+4*1))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x00006074+4*2))=0x01060006;
*((unsigned int *)((unsigned long)context_ptr+0x00006080))=0x7dc66258;
*((unsigned int *)((unsigned long)context_ptr+0x00006080+4*1))=0x00009ce1;
*((unsigned int *)((unsigned long)context_ptr+0x00003078))=0x04c00006;
*((unsigned int *)((unsigned long)context_ptr+0x00003078+4*1))=0x00006088;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000078))=0x03c00006;
*((unsigned int *)((unsigned long)context_ptr+0x00000078+4*1))=0x00006080;
*((unsigned int *)((unsigned long)context_ptr+0x00000078+4*2))=0x00006074;
*((unsigned int *)((unsigned long)context_ptr+0x00000078+4*3))=0x02220006;
*((unsigned int *)((unsigned long)context_ptr+0x00000078+4*4))=0x0026c06e;
*((unsigned int *)((unsigned long)context_ptr+0x00000078+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x00006090))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x00006090+4*1))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x00006090+4*2))=0x01060007;
*((unsigned int *)((unsigned long)context_ptr+0x0000609c))=0xc171c830;
*((unsigned int *)((unsigned long)context_ptr+0x0000609c+4*1))=0x0013ca74;
*((unsigned int *)((unsigned long)context_ptr+0x00003090))=0x04c00007;
*((unsigned int *)((unsigned long)context_ptr+0x00003090+4*1))=0x000060a4;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000090))=0x03c00007;
*((unsigned int *)((unsigned long)context_ptr+0x00000090+4*1))=0x0000609c;
*((unsigned int *)((unsigned long)context_ptr+0x00000090+4*2))=0x00006090;
*((unsigned int *)((unsigned long)context_ptr+0x00000090+4*3))=0x02220007;
*((unsigned int *)((unsigned long)context_ptr+0x00000090+4*4))=0x001fd3af;
*((unsigned int *)((unsigned long)context_ptr+0x00000090+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x000060ac))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x000060ac+4*1))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x000060ac+4*2))=0x01060008;
*((unsigned int *)((unsigned long)context_ptr+0x000060b8))=0xefec906d;
*((unsigned int *)((unsigned long)context_ptr+0x000060b8+4*1))=0xbbc6196a;
*((unsigned int *)((unsigned long)context_ptr+0x000030a8))=0x04c00008;
*((unsigned int *)((unsigned long)context_ptr+0x000030a8+4*1))=0x000060c0;
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
*((unsigned int *)((unsigned long)context_ptr+0x000000a8))=0x03c00008;
*((unsigned int *)((unsigned long)context_ptr+0x000000a8+4*1))=0x000060b8;
*((unsigned int *)((unsigned long)context_ptr+0x000000a8+4*2))=0x000060ac;
*((unsigned int *)((unsigned long)context_ptr+0x000000a8+4*3))=0x02220008;
*((unsigned int *)((unsigned long)context_ptr+0x000000a8+4*4))=0x00e6ac9d;
*((unsigned int *)((unsigned long)context_ptr+0x000000a8+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x000060c8))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x000060c8+4*1))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x000060c8+4*2))=0x01060009;
*((unsigned int *)((unsigned long)context_ptr+0x000060d4))=0xac3435e4;
*((unsigned int *)((unsigned long)context_ptr+0x000060d4+4*1))=0x5e011ff0;
*((unsigned int *)((unsigned long)context_ptr+0x000060d4+4*2))=0x00000006;
*((unsigned int *)((unsigned long)context_ptr+0x000030c0))=0x04c00009;
*((unsigned int *)((unsigned long)context_ptr+0x000030c0+4*1))=0x000060e0;
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
*((unsigned int *)((unsigned long)context_ptr+0x000000c0))=0x03c00009;
*((unsigned int *)((unsigned long)context_ptr+0x000000c0+4*1))=0x000060d4;
*((unsigned int *)((unsigned long)context_ptr+0x000000c0+4*2))=0x000060c8;
*((unsigned int *)((unsigned long)context_ptr+0x000000c0+4*3))=0x02220009;
*((unsigned int *)((unsigned long)context_ptr+0x000000c0+4*4))=0x0007b6e0;
*((unsigned int *)((unsigned long)context_ptr+0x000000c0+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x000060ec))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x000060ec+4*1))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x000060ec+4*2))=0x0106000a;
*((unsigned int *)((unsigned long)context_ptr+0x000060f8))=0xe528941a;
*((unsigned int *)((unsigned long)context_ptr+0x000060f8+4*1))=0x3e50cdf2;
*((unsigned int *)((unsigned long)context_ptr+0x000060f8+4*2))=0x00004ac1;
*((unsigned int *)((unsigned long)context_ptr+0x000030d8))=0x04c0000a;
*((unsigned int *)((unsigned long)context_ptr+0x000030d8+4*1))=0x00006104;
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
*((unsigned int *)((unsigned long)context_ptr+0x000000d8))=0x03c0000a;
*((unsigned int *)((unsigned long)context_ptr+0x000000d8+4*1))=0x000060f8;
*((unsigned int *)((unsigned long)context_ptr+0x000000d8+4*2))=0x000060ec;
*((unsigned int *)((unsigned long)context_ptr+0x000000d8+4*3))=0x0222000a;
*((unsigned int *)((unsigned long)context_ptr+0x000000d8+4*4))=0x001cc5a8;
*((unsigned int *)((unsigned long)context_ptr+0x000000d8+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x00006110))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x00006110+4*1))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x00006110+4*2))=0x0106000b;
*((unsigned int *)((unsigned long)context_ptr+0x0000611c))=0xba6a680e;
*((unsigned int *)((unsigned long)context_ptr+0x0000611c+4*1))=0x784b3452;
*((unsigned int *)((unsigned long)context_ptr+0x0000611c+4*2))=0x0046cbf3;
*((unsigned int *)((unsigned long)context_ptr+0x000030f0))=0x04c0000b;
*((unsigned int *)((unsigned long)context_ptr+0x000030f0+4*1))=0x00006128;
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
*((unsigned int *)((unsigned long)context_ptr+0x000000f0))=0x03c0000b;
*((unsigned int *)((unsigned long)context_ptr+0x000000f0+4*1))=0x0000611c;
*((unsigned int *)((unsigned long)context_ptr+0x000000f0+4*2))=0x00006110;
*((unsigned int *)((unsigned long)context_ptr+0x000000f0+4*3))=0x0222000b;
*((unsigned int *)((unsigned long)context_ptr+0x000000f0+4*4))=0x000542bd;
*((unsigned int *)((unsigned long)context_ptr+0x000000f0+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x00006134))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x00006134+4*1))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x00006134+4*2))=0x0106000c;
*((unsigned int *)((unsigned long)context_ptr+0x00006140))=0x4c019eb2;
*((unsigned int *)((unsigned long)context_ptr+0x00006140+4*1))=0x278ba1c4;
*((unsigned int *)((unsigned long)context_ptr+0x00006140+4*2))=0xc2ad78b4;
*((unsigned int *)((unsigned long)context_ptr+0x00003108))=0x04c0000c;
*((unsigned int *)((unsigned long)context_ptr+0x00003108+4*1))=0x0000614c;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000108))=0x03c0000c;
*((unsigned int *)((unsigned long)context_ptr+0x00000108+4*1))=0x00006140;
*((unsigned int *)((unsigned long)context_ptr+0x00000108+4*2))=0x00006134;
*((unsigned int *)((unsigned long)context_ptr+0x00000108+4*3))=0x0222000c;
*((unsigned int *)((unsigned long)context_ptr+0x00000108+4*4))=0x007237d4;
*((unsigned int *)((unsigned long)context_ptr+0x00000108+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x00006158))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x00006158+4*1))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x00006158+4*2))=0x0106000d;
*((unsigned int *)((unsigned long)context_ptr+0x00006164))=0x4eca0998;
*((unsigned int *)((unsigned long)context_ptr+0x00006164+4*1))=0xeb3f8757;
*((unsigned int *)((unsigned long)context_ptr+0x00006164+4*2))=0x854a6a29;
*((unsigned int *)((unsigned long)context_ptr+0x00006164+4*3))=0x00000092;
*((unsigned int *)((unsigned long)context_ptr+0x00003120))=0x04c0000d;
*((unsigned int *)((unsigned long)context_ptr+0x00003120+4*1))=0x00006174;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000120))=0x03c0000d;
*((unsigned int *)((unsigned long)context_ptr+0x00000120+4*1))=0x00006164;
*((unsigned int *)((unsigned long)context_ptr+0x00000120+4*2))=0x00006158;
*((unsigned int *)((unsigned long)context_ptr+0x00000120+4*3))=0x0222000d;
*((unsigned int *)((unsigned long)context_ptr+0x00000120+4*4))=0x00fbe86a;
*((unsigned int *)((unsigned long)context_ptr+0x00000120+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x00006184))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x00006184+4*1))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x00006184+4*2))=0x0106000e;
*((unsigned int *)((unsigned long)context_ptr+0x00006190))=0x7a6a795a;
*((unsigned int *)((unsigned long)context_ptr+0x00006190+4*1))=0x0fa651b1;
*((unsigned int *)((unsigned long)context_ptr+0x00006190+4*2))=0x9f0dbe4c;
*((unsigned int *)((unsigned long)context_ptr+0x00006190+4*3))=0x00007806;
*((unsigned int *)((unsigned long)context_ptr+0x00003138))=0x04c0000e;
*((unsigned int *)((unsigned long)context_ptr+0x00003138+4*1))=0x000061a0;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000138))=0x03c0000e;
*((unsigned int *)((unsigned long)context_ptr+0x00000138+4*1))=0x00006190;
*((unsigned int *)((unsigned long)context_ptr+0x00000138+4*2))=0x00006184;
*((unsigned int *)((unsigned long)context_ptr+0x00000138+4*3))=0x0222000e;
*((unsigned int *)((unsigned long)context_ptr+0x00000138+4*4))=0x00a274c0;
*((unsigned int *)((unsigned long)context_ptr+0x00000138+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x000061b0))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x000061b0+4*1))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x000061b0+4*2))=0x0106000f;
*((unsigned int *)((unsigned long)context_ptr+0x000061bc))=0x751a49c0;
*((unsigned int *)((unsigned long)context_ptr+0x000061bc+4*1))=0xe56b2b54;
*((unsigned int *)((unsigned long)context_ptr+0x000061bc+4*2))=0x86b5726f;
*((unsigned int *)((unsigned long)context_ptr+0x000061bc+4*3))=0x0071e921;
*((unsigned int *)((unsigned long)context_ptr+0x00003150))=0x04c0000f;
*((unsigned int *)((unsigned long)context_ptr+0x00003150+4*1))=0x000061cc;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000150))=0x03c0000f;
*((unsigned int *)((unsigned long)context_ptr+0x00000150+4*1))=0x000061bc;
*((unsigned int *)((unsigned long)context_ptr+0x00000150+4*2))=0x000061b0;
*((unsigned int *)((unsigned long)context_ptr+0x00000150+4*3))=0x0222000f;
*((unsigned int *)((unsigned long)context_ptr+0x00000150+4*4))=0x00110350;
*((unsigned int *)((unsigned long)context_ptr+0x00000150+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000006&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006018,"\xfb\x00\x00\x00",1))
printf("strip: fb000000, Pass\n");
else
printf("strip: fb000000, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006008))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x00006008+4*1))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x00006008+4*2))=0x01060010;
*((unsigned int *)((unsigned long)context_ptr+0x000061dc))=0x83b49c9c;
*((unsigned int *)((unsigned long)context_ptr+0x000061dc+4*1))=0x755ae048;
*((unsigned int *)((unsigned long)context_ptr+0x000061dc+4*2))=0xf4f484a1;
*((unsigned int *)((unsigned long)context_ptr+0x000061dc+4*3))=0x7d94efee;
*((unsigned int *)((unsigned long)context_ptr+0x00003168))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003168+4*1))=0x000061ec;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000168))=0x03c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00000168+4*1))=0x000061dc;
*((unsigned int *)((unsigned long)context_ptr+0x00000168+4*2))=0x00006008;
*((unsigned int *)((unsigned long)context_ptr+0x00000168+4*3))=0x02220010;
*((unsigned int *)((unsigned long)context_ptr+0x00000168+4*4))=0x0063b8a8;
*((unsigned int *)((unsigned long)context_ptr+0x00000168+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000000c&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x0000602c,"\xd1\x09\x00\x00",2))
printf("strip: d1090000, Pass\n");
else
printf("strip: d1090000, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006014))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x00006014+4*1))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x00006014+4*2))=0x01060011;
*((unsigned int *)((unsigned long)context_ptr+0x000061fc))=0x7452cbe2;
*((unsigned int *)((unsigned long)context_ptr+0x000061fc+4*1))=0x5e0b0753;
*((unsigned int *)((unsigned long)context_ptr+0x000061fc+4*2))=0x33308635;
*((unsigned int *)((unsigned long)context_ptr+0x000061fc+4*3))=0xdc4fbcac;
*((unsigned int *)((unsigned long)context_ptr+0x000061fc+4*4))=0x00000041;
*((unsigned int *)((unsigned long)context_ptr+0x00003180))=0x04c00011;
*((unsigned int *)((unsigned long)context_ptr+0x00003180+4*1))=0x00006210;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000180))=0x03c00011;
*((unsigned int *)((unsigned long)context_ptr+0x00000180+4*1))=0x000061fc;
*((unsigned int *)((unsigned long)context_ptr+0x00000180+4*2))=0x00006014;
*((unsigned int *)((unsigned long)context_ptr+0x00000180+4*3))=0x02220011;
*((unsigned int *)((unsigned long)context_ptr+0x00000180+4*4))=0x000b36f3;
*((unsigned int *)((unsigned long)context_ptr+0x00000180+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000012&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006040,"\x29\x26\xa7\x00",3))
printf("strip: 2926a700, Pass\n");
else
printf("strip: 2926a700, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006020))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x00006020+4*1))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x00006020+4*2))=0x01060012;
*((unsigned int *)((unsigned long)context_ptr+0x0000602c))=0x6d1370eb;
*((unsigned int *)((unsigned long)context_ptr+0x0000602c+4*1))=0x2e0ad4c1;
*((unsigned int *)((unsigned long)context_ptr+0x0000602c+4*2))=0xefde207d;
*((unsigned int *)((unsigned long)context_ptr+0x0000602c+4*3))=0x498e6f51;
*((unsigned int *)((unsigned long)context_ptr+0x0000602c+4*4))=0x0000338a;
*((unsigned int *)((unsigned long)context_ptr+0x00003198))=0x04c00012;
*((unsigned int *)((unsigned long)context_ptr+0x00003198+4*1))=0x00006224;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000198))=0x03c00012;
*((unsigned int *)((unsigned long)context_ptr+0x00000198+4*1))=0x0000602c;
*((unsigned int *)((unsigned long)context_ptr+0x00000198+4*2))=0x00006020;
*((unsigned int *)((unsigned long)context_ptr+0x00000198+4*3))=0x02220012;
*((unsigned int *)((unsigned long)context_ptr+0x00000198+4*4))=0x00ef26a5;
*((unsigned int *)((unsigned long)context_ptr+0x00000198+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006054,"\xca\x63\x96\xd9",4))
printf("strip: ca6396d9, Pass\n");
else
printf("strip: ca6396d9, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006040))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x00006040+4*1))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x00006040+4*2))=0x01060013;
*((unsigned int *)((unsigned long)context_ptr+0x00006238))=0x1ea51fdb;
*((unsigned int *)((unsigned long)context_ptr+0x00006238+4*1))=0xb4ac5bbc;
*((unsigned int *)((unsigned long)context_ptr+0x00006238+4*2))=0x3dd438a9;
*((unsigned int *)((unsigned long)context_ptr+0x00006238+4*3))=0xa03bac84;
*((unsigned int *)((unsigned long)context_ptr+0x00006238+4*4))=0x00cf2b49;
*((unsigned int *)((unsigned long)context_ptr+0x000031b0))=0x04c00013;
*((unsigned int *)((unsigned long)context_ptr+0x000031b0+4*1))=0x0000624c;
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
*((unsigned int *)((unsigned long)context_ptr+0x000001b0))=0x03c00013;
*((unsigned int *)((unsigned long)context_ptr+0x000001b0+4*1))=0x00006238;
*((unsigned int *)((unsigned long)context_ptr+0x000001b0+4*2))=0x00006040;
*((unsigned int *)((unsigned long)context_ptr+0x000001b0+4*3))=0x02220013;
*((unsigned int *)((unsigned long)context_ptr+0x000001b0+4*4))=0x0089421c;
*((unsigned int *)((unsigned long)context_ptr+0x000001b0+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000001e&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x0000606c,"\xd4\x0e\x09\x6a\x7d\x00\x00\x00",5))
printf("strip: d40e096a7d000000, Pass\n");
else
printf("strip: d40e096a7d000000, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x0000604c))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x0000604c+4*1))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x0000604c+4*2))=0x01060014;
*((unsigned int *)((unsigned long)context_ptr+0x00006058))=0x975ac2d0;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*1))=0xd51be6a1;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*2))=0x03745b86;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*3))=0x7ea9a738;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*4))=0xd9507bf4;
*((unsigned int *)((unsigned long)context_ptr+0x000031c8))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x000031c8+4*1))=0x00006260;
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
*((unsigned int *)((unsigned long)context_ptr+0x000001c8))=0x03c00014;
*((unsigned int *)((unsigned long)context_ptr+0x000001c8+4*1))=0x00006058;
*((unsigned int *)((unsigned long)context_ptr+0x000001c8+4*2))=0x0000604c;
*((unsigned int *)((unsigned long)context_ptr+0x000001c8+4*3))=0x02220014;
*((unsigned int *)((unsigned long)context_ptr+0x000001c8+4*4))=0x0006792b;
*((unsigned int *)((unsigned long)context_ptr+0x000001c8+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000024&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006088,"\x58\x62\xc6\x7d\xe1\x9c\x00\x00",6))
printf("strip: 5862c67de19c0000, Pass\n");
else
printf("strip: 5862c67de19c0000, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x0000606c))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x0000606c+4*1))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x0000606c+4*2))=0x01060015;
*((unsigned int *)((unsigned long)context_ptr+0x00006078))=0xbb8a5b4e;
*((unsigned int *)((unsigned long)context_ptr+0x00006078+4*1))=0x06a00526;
*((unsigned int *)((unsigned long)context_ptr+0x00006078+4*2))=0x11a7390b;
*((unsigned int *)((unsigned long)context_ptr+0x00006078+4*3))=0xe46cf80f;
*((unsigned int *)((unsigned long)context_ptr+0x00006078+4*4))=0x2d5b6f37;
*((unsigned int *)((unsigned long)context_ptr+0x00006078+4*5))=0x00000054;
*((unsigned int *)((unsigned long)context_ptr+0x000031e0))=0x04c00015;
*((unsigned int *)((unsigned long)context_ptr+0x000031e0+4*1))=0x00006274;
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
*((unsigned int *)((unsigned long)context_ptr+0x000001e0))=0x03c00015;
*((unsigned int *)((unsigned long)context_ptr+0x000001e0+4*1))=0x00006078;
*((unsigned int *)((unsigned long)context_ptr+0x000001e0+4*2))=0x0000606c;
*((unsigned int *)((unsigned long)context_ptr+0x000001e0+4*3))=0x02220015;
*((unsigned int *)((unsigned long)context_ptr+0x000001e0+4*4))=0x00d25ab0;
*((unsigned int *)((unsigned long)context_ptr+0x000001e0+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000002a&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000060a4,"\x30\xc8\x71\xc1\x74\xca\x13\x00",7))
printf("strip: 30c871c174ca1300, Pass\n");
else
printf("strip: 30c871c174ca1300, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006090))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x00006090+4*1))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x00006090+4*2))=0x01060016;
*((unsigned int *)((unsigned long)context_ptr+0x0000628c))=0x5425bb83;
*((unsigned int *)((unsigned long)context_ptr+0x0000628c+4*1))=0x053fd2d7;
*((unsigned int *)((unsigned long)context_ptr+0x0000628c+4*2))=0xafc92bce;
*((unsigned int *)((unsigned long)context_ptr+0x0000628c+4*3))=0x99ed142b;
*((unsigned int *)((unsigned long)context_ptr+0x0000628c+4*4))=0x9a26759e;
*((unsigned int *)((unsigned long)context_ptr+0x0000628c+4*5))=0x0000ce40;
*((unsigned int *)((unsigned long)context_ptr+0x000031f8))=0x04c00016;
*((unsigned int *)((unsigned long)context_ptr+0x000031f8+4*1))=0x000062a4;
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
*((unsigned int *)((unsigned long)context_ptr+0x000001f8))=0x03c00016;
*((unsigned int *)((unsigned long)context_ptr+0x000001f8+4*1))=0x0000628c;
*((unsigned int *)((unsigned long)context_ptr+0x000001f8+4*2))=0x00006090;
*((unsigned int *)((unsigned long)context_ptr+0x000001f8+4*3))=0x02220016;
*((unsigned int *)((unsigned long)context_ptr+0x000001f8+4*4))=0x0068c6dd;
*((unsigned int *)((unsigned long)context_ptr+0x000001f8+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000030&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000060c0,"\x6d\x90\xec\xef\x6a\x19\xc6\xbb",8))
printf("strip: 6d90ecef6a19c6bb, Pass\n");
else
printf("strip: 6d90ecef6a19c6bb, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x0000609c))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x0000609c+4*1))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x0000609c+4*2))=0x01060017;
*((unsigned int *)((unsigned long)context_ptr+0x000060a8))=0x92c5fa8c;
*((unsigned int *)((unsigned long)context_ptr+0x000060a8+4*1))=0xb874af43;
*((unsigned int *)((unsigned long)context_ptr+0x000060a8+4*2))=0xbd057e67;
*((unsigned int *)((unsigned long)context_ptr+0x000060a8+4*3))=0xc694ae08;
*((unsigned int *)((unsigned long)context_ptr+0x000060a8+4*4))=0x8735af4a;
*((unsigned int *)((unsigned long)context_ptr+0x000060a8+4*5))=0x00f8fa57;
*((unsigned int *)((unsigned long)context_ptr+0x00003210))=0x04c00017;
*((unsigned int *)((unsigned long)context_ptr+0x00003210+4*1))=0x000062bc;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000210))=0x03c00017;
*((unsigned int *)((unsigned long)context_ptr+0x00000210+4*1))=0x000060a8;
*((unsigned int *)((unsigned long)context_ptr+0x00000210+4*2))=0x0000609c;
*((unsigned int *)((unsigned long)context_ptr+0x00000210+4*3))=0x02220017;
*((unsigned int *)((unsigned long)context_ptr+0x00000210+4*4))=0x00094c02;
*((unsigned int *)((unsigned long)context_ptr+0x00000210+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000036&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000060e0,"\xe4\x35\x34\xac\xf0\x1f\x01\x5e\x06\x00\x00\x00",9))
printf("strip: e43534acf01f015e, Pass\n");
else
printf("strip: e43534acf01f015e, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000060c0))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x000060c0+4*1))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x000060c0+4*2))=0x01060018;
*((unsigned int *)((unsigned long)context_ptr+0x000060cc))=0x52a05cf3;
*((unsigned int *)((unsigned long)context_ptr+0x000060cc+4*1))=0x00fc99c8;
*((unsigned int *)((unsigned long)context_ptr+0x000060cc+4*2))=0xed200b24;
*((unsigned int *)((unsigned long)context_ptr+0x000060cc+4*3))=0xd1f27af2;
*((unsigned int *)((unsigned long)context_ptr+0x000060cc+4*4))=0x8c30bfc7;
*((unsigned int *)((unsigned long)context_ptr+0x000060cc+4*5))=0x2b2cf36c;
*((unsigned int *)((unsigned long)context_ptr+0x00003228))=0x04c00018;
*((unsigned int *)((unsigned long)context_ptr+0x00003228+4*1))=0x000062d4;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000228))=0x03c00018;
*((unsigned int *)((unsigned long)context_ptr+0x00000228+4*1))=0x000060cc;
*((unsigned int *)((unsigned long)context_ptr+0x00000228+4*2))=0x000060c0;
*((unsigned int *)((unsigned long)context_ptr+0x00000228+4*3))=0x02220018;
*((unsigned int *)((unsigned long)context_ptr+0x00000228+4*4))=0x00f7f21e;
*((unsigned int *)((unsigned long)context_ptr+0x00000228+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000003c&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006104,"\x1a\x94\x28\xe5\xf2\xcd\x50\x3e\xc1\x4a\x00\x00",10))
printf("strip: 1a9428e5f2cd503e, Pass\n");
else
printf("strip: 1a9428e5f2cd503e, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000060e4))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x000060e4+4*1))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x000060e4+4*2))=0x01060019;
*((unsigned int *)((unsigned long)context_ptr+0x000060f0))=0xd8cac830;
*((unsigned int *)((unsigned long)context_ptr+0x000060f0+4*1))=0xeca927c0;
*((unsigned int *)((unsigned long)context_ptr+0x000060f0+4*2))=0x8ff35c90;
*((unsigned int *)((unsigned long)context_ptr+0x000060f0+4*3))=0x3acd9d69;
*((unsigned int *)((unsigned long)context_ptr+0x000060f0+4*4))=0xaef08704;
*((unsigned int *)((unsigned long)context_ptr+0x000060f0+4*5))=0xbb7fa0a1;
*((unsigned int *)((unsigned long)context_ptr+0x000060f0+4*6))=0x0000003f;
*((unsigned int *)((unsigned long)context_ptr+0x00003240))=0x04c00019;
*((unsigned int *)((unsigned long)context_ptr+0x00003240+4*1))=0x000062ec;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000240))=0x03c00019;
*((unsigned int *)((unsigned long)context_ptr+0x00000240+4*1))=0x000060f0;
*((unsigned int *)((unsigned long)context_ptr+0x00000240+4*2))=0x000060e4;
*((unsigned int *)((unsigned long)context_ptr+0x00000240+4*3))=0x02220019;
*((unsigned int *)((unsigned long)context_ptr+0x00000240+4*4))=0x0081011c;
*((unsigned int *)((unsigned long)context_ptr+0x00000240+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000042&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006128,"\x0e\x68\x6a\xba\x52\x34\x4b\x78\xf3\xcb\x46\x00",11))
printf("strip: 0e686aba52344b78, Pass\n");
else
printf("strip: 0e686aba52344b78, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x0000610c))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x0000610c+4*1))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x0000610c+4*2))=0x0106001a;
*((unsigned int *)((unsigned long)context_ptr+0x00006118))=0xc6e140f0;
*((unsigned int *)((unsigned long)context_ptr+0x00006118+4*1))=0x0207179c;
*((unsigned int *)((unsigned long)context_ptr+0x00006118+4*2))=0xc662c340;
*((unsigned int *)((unsigned long)context_ptr+0x00006118+4*3))=0x09e163a0;
*((unsigned int *)((unsigned long)context_ptr+0x00006118+4*4))=0xb520d477;
*((unsigned int *)((unsigned long)context_ptr+0x00006118+4*5))=0x85790653;
*((unsigned int *)((unsigned long)context_ptr+0x00006118+4*6))=0x0000900a;
*((unsigned int *)((unsigned long)context_ptr+0x00003258))=0x04c0001a;
*((unsigned int *)((unsigned long)context_ptr+0x00003258+4*1))=0x00006308;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000258))=0x03c0001a;
*((unsigned int *)((unsigned long)context_ptr+0x00000258+4*1))=0x00006118;
*((unsigned int *)((unsigned long)context_ptr+0x00000258+4*2))=0x0000610c;
*((unsigned int *)((unsigned long)context_ptr+0x00000258+4*3))=0x0222001a;
*((unsigned int *)((unsigned long)context_ptr+0x00000258+4*4))=0x00ed2ee3;
*((unsigned int *)((unsigned long)context_ptr+0x00000258+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000048&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x0000614c,"\xb2\x9e\x01\x4c\xc4\xa1\x8b\x27\xb4\x78\xad\xc2",12))
printf("strip: b29e014cc4a18b27, Pass\n");
else
printf("strip: b29e014cc4a18b27, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006134))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x00006134+4*1))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x00006134+4*2))=0x0106001b;
*((unsigned int *)((unsigned long)context_ptr+0x00006324))=0x200f4e67;
*((unsigned int *)((unsigned long)context_ptr+0x00006324+4*1))=0xc3a47b22;
*((unsigned int *)((unsigned long)context_ptr+0x00006324+4*2))=0x8e0bd20b;
*((unsigned int *)((unsigned long)context_ptr+0x00006324+4*3))=0x58f3a1be;
*((unsigned int *)((unsigned long)context_ptr+0x00006324+4*4))=0xd08f1595;
*((unsigned int *)((unsigned long)context_ptr+0x00006324+4*5))=0x40b34233;
*((unsigned int *)((unsigned long)context_ptr+0x00006324+4*6))=0x00ffef42;
*((unsigned int *)((unsigned long)context_ptr+0x00003270))=0x04c0001b;
*((unsigned int *)((unsigned long)context_ptr+0x00003270+4*1))=0x00006340;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000270))=0x03c0001b;
*((unsigned int *)((unsigned long)context_ptr+0x00000270+4*1))=0x00006324;
*((unsigned int *)((unsigned long)context_ptr+0x00000270+4*2))=0x00006134;
*((unsigned int *)((unsigned long)context_ptr+0x00000270+4*3))=0x0222001b;
*((unsigned int *)((unsigned long)context_ptr+0x00000270+4*4))=0x001c5e16;
*((unsigned int *)((unsigned long)context_ptr+0x00000270+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000004e&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006174,"\x98\x09\xca\x4e\x57\x87\x3f\xeb\x29\x6a\x4a\x85\x92\x00\x00\x00",13))
printf("strip: 9809ca4e57873feb, Pass\n");
else
printf("strip: 9809ca4e57873feb, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006140))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x00006140+4*1))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x00006140+4*2))=0x0106001c;
*((unsigned int *)((unsigned long)context_ptr+0x0000614c))=0x8b8e79a7;
*((unsigned int *)((unsigned long)context_ptr+0x0000614c+4*1))=0x14d057d2;
*((unsigned int *)((unsigned long)context_ptr+0x0000614c+4*2))=0xd5735a6d;
*((unsigned int *)((unsigned long)context_ptr+0x0000614c+4*3))=0x1edcfc83;
*((unsigned int *)((unsigned long)context_ptr+0x0000614c+4*4))=0x04bb0551;
*((unsigned int *)((unsigned long)context_ptr+0x0000614c+4*5))=0x0f6931e2;
*((unsigned int *)((unsigned long)context_ptr+0x0000614c+4*6))=0xc40d634f;
*((unsigned int *)((unsigned long)context_ptr+0x00003288))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003288+4*1))=0x00006168;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000288))=0x03c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00000288+4*1))=0x0000614c;
*((unsigned int *)((unsigned long)context_ptr+0x00000288+4*2))=0x00006140;
*((unsigned int *)((unsigned long)context_ptr+0x00000288+4*3))=0x0222001c;
*((unsigned int *)((unsigned long)context_ptr+0x00000288+4*4))=0x0009e1c3;
*((unsigned int *)((unsigned long)context_ptr+0x00000288+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000054&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000061a0,"\x5a\x79\x6a\x7a\xb1\x51\xa6\x0f\x4c\xbe\x0d\x9f\x06\x78\x00\x00",14))
printf("strip: 5a796a7ab151a60f, Pass\n");
else
printf("strip: 5a796a7ab151a60f, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006184))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x00006184+4*1))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x00006184+4*2))=0x0106001d;
*((unsigned int *)((unsigned long)context_ptr+0x00006190))=0x2d591f5b;
*((unsigned int *)((unsigned long)context_ptr+0x00006190+4*1))=0x7403a79d;
*((unsigned int *)((unsigned long)context_ptr+0x00006190+4*2))=0x147edf8d;
*((unsigned int *)((unsigned long)context_ptr+0x00006190+4*3))=0xdbcadc0d;
*((unsigned int *)((unsigned long)context_ptr+0x00006190+4*4))=0xd318a543;
*((unsigned int *)((unsigned long)context_ptr+0x00006190+4*5))=0x0878f455;
*((unsigned int *)((unsigned long)context_ptr+0x00006190+4*6))=0x0949a0e8;
*((unsigned int *)((unsigned long)context_ptr+0x00006190+4*7))=0x00000060;
*((unsigned int *)((unsigned long)context_ptr+0x000032a0))=0x04c0001d;
*((unsigned int *)((unsigned long)context_ptr+0x000032a0+4*1))=0x0000635c;
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
*((unsigned int *)((unsigned long)context_ptr+0x000002a0))=0x03c0001d;
*((unsigned int *)((unsigned long)context_ptr+0x000002a0+4*1))=0x00006190;
*((unsigned int *)((unsigned long)context_ptr+0x000002a0+4*2))=0x00006184;
*((unsigned int *)((unsigned long)context_ptr+0x000002a0+4*3))=0x0222001d;
*((unsigned int *)((unsigned long)context_ptr+0x000002a0+4*4))=0x0013d1ea;
*((unsigned int *)((unsigned long)context_ptr+0x000002a0+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000005a&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000061cc,"\xc0\x49\x1a\x75\x54\x2b\x6b\xe5\x6f\x72\xb5\x86\x21\xe9\x71\x00",15))
printf("strip: c0491a75542b6be5, Pass\n");
else
printf("strip: c0491a75542b6be5, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000061b0))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x000061b0+4*1))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x000061b0+4*2))=0x0106001e;
*((unsigned int *)((unsigned long)context_ptr+0x000061bc))=0xe0393c2b;
*((unsigned int *)((unsigned long)context_ptr+0x000061bc+4*1))=0x9023e076;
*((unsigned int *)((unsigned long)context_ptr+0x000061bc+4*2))=0x6301ee03;
*((unsigned int *)((unsigned long)context_ptr+0x000061bc+4*3))=0xd204ffcd;
*((unsigned int *)((unsigned long)context_ptr+0x000061bc+4*4))=0x1cc60982;
*((unsigned int *)((unsigned long)context_ptr+0x000061bc+4*5))=0x61acc79c;
*((unsigned int *)((unsigned long)context_ptr+0x000061bc+4*6))=0x55e96f06;
*((unsigned int *)((unsigned long)context_ptr+0x000061bc+4*7))=0x0000233f;
*((unsigned int *)((unsigned long)context_ptr+0x000032b8))=0x04c0001e;
*((unsigned int *)((unsigned long)context_ptr+0x000032b8+4*1))=0x0000637c;
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
*((unsigned int *)((unsigned long)context_ptr+0x000002b8))=0x03c0001e;
*((unsigned int *)((unsigned long)context_ptr+0x000002b8+4*1))=0x000061bc;
*((unsigned int *)((unsigned long)context_ptr+0x000002b8+4*2))=0x000061b0;
*((unsigned int *)((unsigned long)context_ptr+0x000002b8+4*3))=0x0222001e;
*((unsigned int *)((unsigned long)context_ptr+0x000002b8+4*4))=0x002cb385;
*((unsigned int *)((unsigned long)context_ptr+0x000002b8+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000060&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000061ec,"\x9c\x9c\xb4\x83\x48\xe0\x5a\x75\xa1\x84\xf4\xf4\xee\xef\x94\x7d",16))
printf("strip: 9c9cb48348e05a75, Pass\n");
else
printf("strip: 9c9cb48348e05a75, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006008))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x00006008+4*1))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x00006008+4*2))=0x0106001f;
*((unsigned int *)((unsigned long)context_ptr+0x000061dc))=0x9c055fe2;
*((unsigned int *)((unsigned long)context_ptr+0x000061dc+4*1))=0x520a3c79;
*((unsigned int *)((unsigned long)context_ptr+0x000061dc+4*2))=0xe01bf6cc;
*((unsigned int *)((unsigned long)context_ptr+0x000061dc+4*3))=0x6b06b60c;
*((unsigned int *)((unsigned long)context_ptr+0x000061dc+4*4))=0xb6ec64de;
*((unsigned int *)((unsigned long)context_ptr+0x000061dc+4*5))=0x6957299a;
*((unsigned int *)((unsigned long)context_ptr+0x000061dc+4*6))=0x8048fe97;
*((unsigned int *)((unsigned long)context_ptr+0x000061dc+4*7))=0x00a058ee;
*((unsigned int *)((unsigned long)context_ptr+0x000032d0))=0x04c0001f;
*((unsigned int *)((unsigned long)context_ptr+0x000032d0+4*1))=0x0000639c;
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
*((unsigned int *)((unsigned long)context_ptr+0x000002d0))=0x03c0001f;
*((unsigned int *)((unsigned long)context_ptr+0x000002d0+4*1))=0x000061dc;
*((unsigned int *)((unsigned long)context_ptr+0x000002d0+4*2))=0x00006008;
*((unsigned int *)((unsigned long)context_ptr+0x000002d0+4*3))=0x0222001f;
*((unsigned int *)((unsigned long)context_ptr+0x000002d0+4*4))=0x006862dc;
*((unsigned int *)((unsigned long)context_ptr+0x000002d0+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000066&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006210,"\xe2\xcb\x52\x74\x53\x07\x0b\x5e\x35\x86\x30\x33\xac\xbc\x4f\xdc\x41\x00\x00\x00",17))
printf("strip: e2cb527453070b5e, Pass\n");
else
printf("strip: e2cb527453070b5e, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006014))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x00006014+4*1))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x00006014+4*2))=0x01060020;
*((unsigned int *)((unsigned long)context_ptr+0x000061fc))=0x656e2a9c;
*((unsigned int *)((unsigned long)context_ptr+0x000061fc+4*1))=0xc7aeb513;
*((unsigned int *)((unsigned long)context_ptr+0x000061fc+4*2))=0x352b8d8b;
*((unsigned int *)((unsigned long)context_ptr+0x000061fc+4*3))=0x5bd1863a;
*((unsigned int *)((unsigned long)context_ptr+0x000061fc+4*4))=0x55b7bce1;
*((unsigned int *)((unsigned long)context_ptr+0x000061fc+4*5))=0x68daf61e;
*((unsigned int *)((unsigned long)context_ptr+0x000061fc+4*6))=0x8057e6dc;
*((unsigned int *)((unsigned long)context_ptr+0x000061fc+4*7))=0xfce9b154;
*((unsigned int *)((unsigned long)context_ptr+0x000032e8))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x000032e8+4*1))=0x000063bc;
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
*((unsigned int *)((unsigned long)context_ptr+0x000002e8))=0x03c00020;
*((unsigned int *)((unsigned long)context_ptr+0x000002e8+4*1))=0x000061fc;
*((unsigned int *)((unsigned long)context_ptr+0x000002e8+4*2))=0x00006014;
*((unsigned int *)((unsigned long)context_ptr+0x000002e8+4*3))=0x02220020;
*((unsigned int *)((unsigned long)context_ptr+0x000002e8+4*4))=0x003218ef;
*((unsigned int *)((unsigned long)context_ptr+0x000002e8+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000006c&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006224,"\xeb\x70\x13\x6d\xc1\xd4\x0a\x2e\x7d\x20\xde\xef\x51\x6f\x8e\x49\x8a\x33\x00\x00",18))
printf("strip: eb70136dc1d40a2e, Pass\n");
else
printf("strip: eb70136dc1d40a2e, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006020))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x00006020+4*1))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x00006020+4*2))=0x01060021;
*((unsigned int *)((unsigned long)context_ptr+0x000063dc))=0x34a5b284;
*((unsigned int *)((unsigned long)context_ptr+0x000063dc+4*1))=0xb01cfba4;
*((unsigned int *)((unsigned long)context_ptr+0x000063dc+4*2))=0x02cb609d;
*((unsigned int *)((unsigned long)context_ptr+0x000063dc+4*3))=0x1b7bd1e4;
*((unsigned int *)((unsigned long)context_ptr+0x000063dc+4*4))=0x7c409573;
*((unsigned int *)((unsigned long)context_ptr+0x000063dc+4*5))=0xd38fecc6;
*((unsigned int *)((unsigned long)context_ptr+0x000063dc+4*6))=0x2bebdb13;
*((unsigned int *)((unsigned long)context_ptr+0x000063dc+4*7))=0x84e0d9d3;
*((unsigned int *)((unsigned long)context_ptr+0x000063dc+4*8))=0x0000009b;
*((unsigned int *)((unsigned long)context_ptr+0x00003300))=0x04c00021;
*((unsigned int *)((unsigned long)context_ptr+0x00003300+4*1))=0x00006400;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000300))=0x03c00021;
*((unsigned int *)((unsigned long)context_ptr+0x00000300+4*1))=0x000063dc;
*((unsigned int *)((unsigned long)context_ptr+0x00000300+4*2))=0x00006020;
*((unsigned int *)((unsigned long)context_ptr+0x00000300+4*3))=0x02220021;
*((unsigned int *)((unsigned long)context_ptr+0x00000300+4*4))=0x00fe1c51;
*((unsigned int *)((unsigned long)context_ptr+0x00000300+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000072&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x0000624c,"\xdb\x1f\xa5\x1e\xbc\x5b\xac\xb4\xa9\x38\xd4\x3d\x84\xac\x3b\xa0\x49\x2b\xcf\x00",19))
printf("strip: db1fa51ebc5bacb4, Pass\n");
else
printf("strip: db1fa51ebc5bacb4, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x0000602c))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x0000602c+4*1))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x0000602c+4*2))=0x01060022;
*((unsigned int *)((unsigned long)context_ptr+0x0000621c))=0xa57dd51a;
*((unsigned int *)((unsigned long)context_ptr+0x0000621c+4*1))=0x288a2e79;
*((unsigned int *)((unsigned long)context_ptr+0x0000621c+4*2))=0x1124d4da;
*((unsigned int *)((unsigned long)context_ptr+0x0000621c+4*3))=0x8ef36411;
*((unsigned int *)((unsigned long)context_ptr+0x0000621c+4*4))=0x241c3a43;
*((unsigned int *)((unsigned long)context_ptr+0x0000621c+4*5))=0xd2dd23cf;
*((unsigned int *)((unsigned long)context_ptr+0x0000621c+4*6))=0xdc018f23;
*((unsigned int *)((unsigned long)context_ptr+0x0000621c+4*7))=0xb07dc18e;
*((unsigned int *)((unsigned long)context_ptr+0x0000621c+4*8))=0x00008fee;
*((unsigned int *)((unsigned long)context_ptr+0x00003318))=0x04c00022;
*((unsigned int *)((unsigned long)context_ptr+0x00003318+4*1))=0x00006424;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000318))=0x03c00022;
*((unsigned int *)((unsigned long)context_ptr+0x00000318+4*1))=0x0000621c;
*((unsigned int *)((unsigned long)context_ptr+0x00000318+4*2))=0x0000602c;
*((unsigned int *)((unsigned long)context_ptr+0x00000318+4*3))=0x02220022;
*((unsigned int *)((unsigned long)context_ptr+0x00000318+4*4))=0x00056b56;
*((unsigned int *)((unsigned long)context_ptr+0x00000318+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000078&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006260,"\xd0\xc2\x5a\x97\xa1\xe6\x1b\xd5\x86\x5b\x74\x03\x38\xa7\xa9\x7e\xf4\x7b\x50\xd9",20))
printf("strip: d0c25a97a1e61bd5, Pass\n");
else
printf("strip: d0c25a97a1e61bd5, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006038))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x00006038+4*1))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x00006038+4*2))=0x01060023;
*((unsigned int *)((unsigned long)context_ptr+0x00006044))=0xef3bc261;
*((unsigned int *)((unsigned long)context_ptr+0x00006044+4*1))=0x5be17bbe;
*((unsigned int *)((unsigned long)context_ptr+0x00006044+4*2))=0x66c72162;
*((unsigned int *)((unsigned long)context_ptr+0x00006044+4*3))=0x5fa77880;
*((unsigned int *)((unsigned long)context_ptr+0x00006044+4*4))=0x665b6eea;
*((unsigned int *)((unsigned long)context_ptr+0x00006044+4*5))=0x7addfec4;
*((unsigned int *)((unsigned long)context_ptr+0x00006044+4*6))=0x3e58724a;
*((unsigned int *)((unsigned long)context_ptr+0x00006044+4*7))=0x1c7ff42f;
*((unsigned int *)((unsigned long)context_ptr+0x00006044+4*8))=0x00836362;
*((unsigned int *)((unsigned long)context_ptr+0x00003330))=0x04c00023;
*((unsigned int *)((unsigned long)context_ptr+0x00003330+4*1))=0x00006240;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000330))=0x03c00023;
*((unsigned int *)((unsigned long)context_ptr+0x00000330+4*1))=0x00006044;
*((unsigned int *)((unsigned long)context_ptr+0x00000330+4*2))=0x00006038;
*((unsigned int *)((unsigned long)context_ptr+0x00000330+4*3))=0x02220023;
*((unsigned int *)((unsigned long)context_ptr+0x00000330+4*4))=0x00015128;
*((unsigned int *)((unsigned long)context_ptr+0x00000330+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000007e&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006274,"\x4e\x5b\x8a\xbb\x26\x05\xa0\x06\x0b\x39\xa7\x11\x0f\xf8\x6c\xe4\x37\x6f\x5b\x2d\x54\x00\x00\x00",21))
printf("strip: 4e5b8abb2605a006, Pass\n");
else
printf("strip: 4e5b8abb2605a006, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006068))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x00006068+4*1))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x00006068+4*2))=0x01060024;
*((unsigned int *)((unsigned long)context_ptr+0x00006264))=0x5333170a;
*((unsigned int *)((unsigned long)context_ptr+0x00006264+4*1))=0x3b5dcc1c;
*((unsigned int *)((unsigned long)context_ptr+0x00006264+4*2))=0x1d01610b;
*((unsigned int *)((unsigned long)context_ptr+0x00006264+4*3))=0xbd33ef9a;
*((unsigned int *)((unsigned long)context_ptr+0x00006264+4*4))=0xd8e50032;
*((unsigned int *)((unsigned long)context_ptr+0x00006264+4*5))=0xed3b2d11;
*((unsigned int *)((unsigned long)context_ptr+0x00006264+4*6))=0x616fce61;
*((unsigned int *)((unsigned long)context_ptr+0x00006264+4*7))=0x95449dc3;
*((unsigned int *)((unsigned long)context_ptr+0x00006264+4*8))=0xa4add3b4;
*((unsigned int *)((unsigned long)context_ptr+0x00003348))=0x04c00024;
*((unsigned int *)((unsigned long)context_ptr+0x00003348+4*1))=0x00006448;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000348))=0x03c00024;
*((unsigned int *)((unsigned long)context_ptr+0x00000348+4*1))=0x00006264;
*((unsigned int *)((unsigned long)context_ptr+0x00000348+4*2))=0x00006068;
*((unsigned int *)((unsigned long)context_ptr+0x00000348+4*3))=0x02220024;
*((unsigned int *)((unsigned long)context_ptr+0x00000348+4*4))=0x009e3b3f;
*((unsigned int *)((unsigned long)context_ptr+0x00000348+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000084&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000062a4,"\x83\xbb\x25\x54\xd7\xd2\x3f\x05\xce\x2b\xc9\xaf\x2b\x14\xed\x99\x9e\x75\x26\x9a\x40\xce\x00\x00",22))
printf("strip: 83bb2554d7d23f05, Pass\n");
else
printf("strip: 83bb2554d7d23f05, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006074))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x00006074+4*1))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x00006074+4*2))=0x01060025;
*((unsigned int *)((unsigned long)context_ptr+0x00006288))=0x7478e41f;
*((unsigned int *)((unsigned long)context_ptr+0x00006288+4*1))=0x90606a56;
*((unsigned int *)((unsigned long)context_ptr+0x00006288+4*2))=0x3f3bd255;
*((unsigned int *)((unsigned long)context_ptr+0x00006288+4*3))=0xb906ef7b;
*((unsigned int *)((unsigned long)context_ptr+0x00006288+4*4))=0x72c36701;
*((unsigned int *)((unsigned long)context_ptr+0x00006288+4*5))=0x3a79406d;
*((unsigned int *)((unsigned long)context_ptr+0x00006288+4*6))=0xed99a748;
*((unsigned int *)((unsigned long)context_ptr+0x00006288+4*7))=0x4c1685f8;
*((unsigned int *)((unsigned long)context_ptr+0x00006288+4*8))=0x27f2ac84;
*((unsigned int *)((unsigned long)context_ptr+0x00006288+4*9))=0x00000009;
*((unsigned int *)((unsigned long)context_ptr+0x00003360))=0x04c00025;
*((unsigned int *)((unsigned long)context_ptr+0x00003360+4*1))=0x0000646c;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000360))=0x03c00025;
*((unsigned int *)((unsigned long)context_ptr+0x00000360+4*1))=0x00006288;
*((unsigned int *)((unsigned long)context_ptr+0x00000360+4*2))=0x00006074;
*((unsigned int *)((unsigned long)context_ptr+0x00000360+4*3))=0x02220025;
*((unsigned int *)((unsigned long)context_ptr+0x00000360+4*4))=0x00b6ffe1;
*((unsigned int *)((unsigned long)context_ptr+0x00000360+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000008a&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000062bc,"\x8c\xfa\xc5\x92\x43\xaf\x74\xb8\x67\x7e\x05\xbd\x08\xae\x94\xc6\x4a\xaf\x35\x87\x57\xfa\xf8\x00",23))
printf("strip: 8cfac59243af74b8, Pass\n");
else
printf("strip: 8cfac59243af74b8, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000062b0))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x000062b0+4*1))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x000062b0+4*2))=0x01060026;
*((unsigned int *)((unsigned long)context_ptr+0x00006080))=0x6f98b6ec;
*((unsigned int *)((unsigned long)context_ptr+0x00006080+4*1))=0x92e69ea2;
*((unsigned int *)((unsigned long)context_ptr+0x00006080+4*2))=0xe73e7036;
*((unsigned int *)((unsigned long)context_ptr+0x00006080+4*3))=0x0b328ed7;
*((unsigned int *)((unsigned long)context_ptr+0x00006080+4*4))=0x39ac7122;
*((unsigned int *)((unsigned long)context_ptr+0x00006080+4*5))=0x6cc1dcaf;
*((unsigned int *)((unsigned long)context_ptr+0x00006080+4*6))=0x56e2fda5;
*((unsigned int *)((unsigned long)context_ptr+0x00006080+4*7))=0x5b8e29af;
*((unsigned int *)((unsigned long)context_ptr+0x00006080+4*8))=0xd8a97070;
*((unsigned int *)((unsigned long)context_ptr+0x00006080+4*9))=0x00002577;
*((unsigned int *)((unsigned long)context_ptr+0x00003378))=0x04c00026;
*((unsigned int *)((unsigned long)context_ptr+0x00003378+4*1))=0x00006494;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000378))=0x03c00026;
*((unsigned int *)((unsigned long)context_ptr+0x00000378+4*1))=0x00006080;
*((unsigned int *)((unsigned long)context_ptr+0x00000378+4*2))=0x000062b0;
*((unsigned int *)((unsigned long)context_ptr+0x00000378+4*3))=0x02220026;
*((unsigned int *)((unsigned long)context_ptr+0x00000378+4*4))=0x0077f638;
*((unsigned int *)((unsigned long)context_ptr+0x00000378+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000090&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000062d4,"\xf3\x5c\xa0\x52\xc8\x99\xfc\x00\x24\x0b\x20\xed\xf2\x7a\xf2\xd1\xc7\xbf\x30\x8c\x6c\xf3\x2c\x2b",24))
printf("strip: f35ca052c899fc00, Pass\n");
else
printf("strip: f35ca052c899fc00, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000062bc))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x000062bc+4*1))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x000062bc+4*2))=0x01060027;
*((unsigned int *)((unsigned long)context_ptr+0x000060a8))=0x7da422fe;
*((unsigned int *)((unsigned long)context_ptr+0x000060a8+4*1))=0xf8148961;
*((unsigned int *)((unsigned long)context_ptr+0x000060a8+4*2))=0xc16b037e;
*((unsigned int *)((unsigned long)context_ptr+0x000060a8+4*3))=0x3dc4be4f;
*((unsigned int *)((unsigned long)context_ptr+0x000060a8+4*4))=0x83dd07f7;
*((unsigned int *)((unsigned long)context_ptr+0x000060a8+4*5))=0x47974227;
*((unsigned int *)((unsigned long)context_ptr+0x000060a8+4*6))=0x816238d6;
*((unsigned int *)((unsigned long)context_ptr+0x000060a8+4*7))=0x1643d256;
*((unsigned int *)((unsigned long)context_ptr+0x000060a8+4*8))=0x1090a027;
*((unsigned int *)((unsigned long)context_ptr+0x000060a8+4*9))=0x00517afe;
*((unsigned int *)((unsigned long)context_ptr+0x00003390))=0x04c00027;
*((unsigned int *)((unsigned long)context_ptr+0x00003390+4*1))=0x000064bc;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000390))=0x03c00027;
*((unsigned int *)((unsigned long)context_ptr+0x00000390+4*1))=0x000060a8;
*((unsigned int *)((unsigned long)context_ptr+0x00000390+4*2))=0x000062bc;
*((unsigned int *)((unsigned long)context_ptr+0x00000390+4*3))=0x02220027;
*((unsigned int *)((unsigned long)context_ptr+0x00000390+4*4))=0x0064e0da;
*((unsigned int *)((unsigned long)context_ptr+0x00000390+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000096&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000062ec,"\x30\xc8\xca\xd8\xc0\x27\xa9\xec\x90\x5c\xf3\x8f\x69\x9d\xcd\x3a\x04\x87\xf0\xae\xa1\xa0\x7f\xbb\x3f\x00\x00\x00",25))
printf("strip: 30c8cad8c027a9ec, Pass\n");
else
printf("strip: 30c8cad8c027a9ec, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000060d0))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x000060d0+4*1))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x000060d0+4*2))=0x01060028;
*((unsigned int *)((unsigned long)context_ptr+0x000060dc))=0x8d568ad3;
*((unsigned int *)((unsigned long)context_ptr+0x000060dc+4*1))=0xdc057e29;
*((unsigned int *)((unsigned long)context_ptr+0x000060dc+4*2))=0x9dfe5854;
*((unsigned int *)((unsigned long)context_ptr+0x000060dc+4*3))=0x9211ca6a;
*((unsigned int *)((unsigned long)context_ptr+0x000060dc+4*4))=0x7c96dc85;
*((unsigned int *)((unsigned long)context_ptr+0x000060dc+4*5))=0x8e58c885;
*((unsigned int *)((unsigned long)context_ptr+0x000060dc+4*6))=0xf6b1feb5;
*((unsigned int *)((unsigned long)context_ptr+0x000060dc+4*7))=0x59be9b66;
*((unsigned int *)((unsigned long)context_ptr+0x000060dc+4*8))=0xff59f944;
*((unsigned int *)((unsigned long)context_ptr+0x000060dc+4*9))=0xfbd437da;
*((unsigned int *)((unsigned long)context_ptr+0x000033a8))=0x04c00028;
*((unsigned int *)((unsigned long)context_ptr+0x000033a8+4*1))=0x000062c8;
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
*((unsigned int *)((unsigned long)context_ptr+0x000003a8))=0x03c00028;
*((unsigned int *)((unsigned long)context_ptr+0x000003a8+4*1))=0x000060dc;
*((unsigned int *)((unsigned long)context_ptr+0x000003a8+4*2))=0x000060d0;
*((unsigned int *)((unsigned long)context_ptr+0x000003a8+4*3))=0x02220028;
*((unsigned int *)((unsigned long)context_ptr+0x000003a8+4*4))=0x00aa1706;
*((unsigned int *)((unsigned long)context_ptr+0x000003a8+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000009c&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006308,"\xf0\x40\xe1\xc6\x9c\x17\x07\x02\x40\xc3\x62\xc6\xa0\x63\xe1\x09\x77\xd4\x20\xb5\x53\x06\x79\x85\x0a\x90\x00\x00",26))
printf("strip: f040e1c69c170702, Pass\n");
else
printf("strip: f040e1c69c170702, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006104))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x00006104+4*1))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x00006104+4*2))=0x01060029;
*((unsigned int *)((unsigned long)context_ptr+0x000062f0))=0x68886a72;
*((unsigned int *)((unsigned long)context_ptr+0x000062f0+4*1))=0x2cfffa14;
*((unsigned int *)((unsigned long)context_ptr+0x000062f0+4*2))=0x08b26f3d;
*((unsigned int *)((unsigned long)context_ptr+0x000062f0+4*3))=0xde44a3d5;
*((unsigned int *)((unsigned long)context_ptr+0x000062f0+4*4))=0xfa8c51a9;
*((unsigned int *)((unsigned long)context_ptr+0x000062f0+4*5))=0xb1d9b50c;
*((unsigned int *)((unsigned long)context_ptr+0x000062f0+4*6))=0x6bc99823;
*((unsigned int *)((unsigned long)context_ptr+0x000062f0+4*7))=0xce504095;
*((unsigned int *)((unsigned long)context_ptr+0x000062f0+4*8))=0x5f1f727d;
*((unsigned int *)((unsigned long)context_ptr+0x000062f0+4*9))=0x62ce3b85;
*((unsigned int *)((unsigned long)context_ptr+0x000062f0+4*10))=0x0000003d;
*((unsigned int *)((unsigned long)context_ptr+0x000033c0))=0x04c00029;
*((unsigned int *)((unsigned long)context_ptr+0x000033c0+4*1))=0x000064e4;
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
*((unsigned int *)((unsigned long)context_ptr+0x000003c0))=0x03c00029;
*((unsigned int *)((unsigned long)context_ptr+0x000003c0+4*1))=0x000062f0;
*((unsigned int *)((unsigned long)context_ptr+0x000003c0+4*2))=0x00006104;
*((unsigned int *)((unsigned long)context_ptr+0x000003c0+4*3))=0x02220029;
*((unsigned int *)((unsigned long)context_ptr+0x000003c0+4*4))=0x001551f8;
*((unsigned int *)((unsigned long)context_ptr+0x000003c0+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000000a2&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006340,"\x67\x4e\x0f\x20\x22\x7b\xa4\xc3\x0b\xd2\x0b\x8e\xbe\xa1\xf3\x58\x95\x15\x8f\xd0\x33\x42\xb3\x40\x42\xef\xff\x00",27))
printf("strip: 674e0f20227ba4c3, Pass\n");
else
printf("strip: 674e0f20227ba4c3, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006110))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x00006110+4*1))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x00006110+4*2))=0x0106002a;
*((unsigned int *)((unsigned long)context_ptr+0x0000631c))=0x4d383f5b;
*((unsigned int *)((unsigned long)context_ptr+0x0000631c+4*1))=0x06408d25;
*((unsigned int *)((unsigned long)context_ptr+0x0000631c+4*2))=0xe26ad23b;
*((unsigned int *)((unsigned long)context_ptr+0x0000631c+4*3))=0xe18f3ef1;
*((unsigned int *)((unsigned long)context_ptr+0x0000631c+4*4))=0xfc3f2b94;
*((unsigned int *)((unsigned long)context_ptr+0x0000631c+4*5))=0xbdcbde4c;
*((unsigned int *)((unsigned long)context_ptr+0x0000631c+4*6))=0x0fd8cab8;
*((unsigned int *)((unsigned long)context_ptr+0x0000631c+4*7))=0x8836812a;
*((unsigned int *)((unsigned long)context_ptr+0x0000631c+4*8))=0x0216207e;
*((unsigned int *)((unsigned long)context_ptr+0x0000631c+4*9))=0xfbf614d3;
*((unsigned int *)((unsigned long)context_ptr+0x0000631c+4*10))=0x000073be;
*((unsigned int *)((unsigned long)context_ptr+0x000033d8))=0x04c0002a;
*((unsigned int *)((unsigned long)context_ptr+0x000033d8+4*1))=0x00006510;
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
*((unsigned int *)((unsigned long)context_ptr+0x000003d8))=0x03c0002a;
*((unsigned int *)((unsigned long)context_ptr+0x000003d8+4*1))=0x0000631c;
*((unsigned int *)((unsigned long)context_ptr+0x000003d8+4*2))=0x00006110;
*((unsigned int *)((unsigned long)context_ptr+0x000003d8+4*3))=0x0222002a;
*((unsigned int *)((unsigned long)context_ptr+0x000003d8+4*4))=0x00f5d614;
*((unsigned int *)((unsigned long)context_ptr+0x000003d8+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000000a8&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006168,"\xa7\x79\x8e\x8b\xd2\x57\xd0\x14\x6d\x5a\x73\xd5\x83\xfc\xdc\x1e\x51\x05\xbb\x04\xe2\x31\x69\x0f\x4f\x63\x0d\xc4",28))
printf("strip: a7798e8bd257d014, Pass\n");
else
printf("strip: a7798e8bd257d014, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006348))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x00006348+4*1))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x00006348+4*2))=0x0106002b;
*((unsigned int *)((unsigned long)context_ptr+0x0000611c))=0x82a022c2;
*((unsigned int *)((unsigned long)context_ptr+0x0000611c+4*1))=0x5daa2503;
*((unsigned int *)((unsigned long)context_ptr+0x0000611c+4*2))=0x22b080f6;
*((unsigned int *)((unsigned long)context_ptr+0x0000611c+4*3))=0x33d5bb7a;
*((unsigned int *)((unsigned long)context_ptr+0x0000611c+4*4))=0x79707965;
*((unsigned int *)((unsigned long)context_ptr+0x0000611c+4*5))=0x59e9cf4b;
*((unsigned int *)((unsigned long)context_ptr+0x0000611c+4*6))=0xb29461a3;
*((unsigned int *)((unsigned long)context_ptr+0x0000611c+4*7))=0xd7c1ac80;
*((unsigned int *)((unsigned long)context_ptr+0x0000611c+4*8))=0x82833730;
*((unsigned int *)((unsigned long)context_ptr+0x0000611c+4*9))=0xc7e684ce;
*((unsigned int *)((unsigned long)context_ptr+0x0000611c+4*10))=0x0079d381;
*((unsigned int *)((unsigned long)context_ptr+0x000033f0))=0x04c0002b;
*((unsigned int *)((unsigned long)context_ptr+0x000033f0+4*1))=0x00006148;
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
*((unsigned int *)((unsigned long)context_ptr+0x000003f0))=0x03c0002b;
*((unsigned int *)((unsigned long)context_ptr+0x000003f0+4*1))=0x0000611c;
*((unsigned int *)((unsigned long)context_ptr+0x000003f0+4*2))=0x00006348;
*((unsigned int *)((unsigned long)context_ptr+0x000003f0+4*3))=0x0222002b;
*((unsigned int *)((unsigned long)context_ptr+0x000003f0+4*4))=0x00657399;
*((unsigned int *)((unsigned long)context_ptr+0x000003f0+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000000ae&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x0000635c,"\x5b\x1f\x59\x2d\x9d\xa7\x03\x74\x8d\xdf\x7e\x14\x0d\xdc\xca\xdb\x43\xa5\x18\xd3\x55\xf4\x78\x08\xe8\xa0\x49\x09\x60\x00\x00\x00",29))
printf("strip: 5b1f592d9da70374, Pass\n");
else
printf("strip: 5b1f592d9da70374, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006354))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x00006354+4*1))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x00006354+4*2))=0x0106002c;
*((unsigned int *)((unsigned long)context_ptr+0x00006174))=0x5cf72c2f;
*((unsigned int *)((unsigned long)context_ptr+0x00006174+4*1))=0x04fd02cf;
*((unsigned int *)((unsigned long)context_ptr+0x00006174+4*2))=0x4fd4ed9b;
*((unsigned int *)((unsigned long)context_ptr+0x00006174+4*3))=0x5c7f64d2;
*((unsigned int *)((unsigned long)context_ptr+0x00006174+4*4))=0xb3c8955a;
*((unsigned int *)((unsigned long)context_ptr+0x00006174+4*5))=0x5a8803c4;
*((unsigned int *)((unsigned long)context_ptr+0x00006174+4*6))=0x2f32eb35;
*((unsigned int *)((unsigned long)context_ptr+0x00006174+4*7))=0x819ca82d;
*((unsigned int *)((unsigned long)context_ptr+0x00006174+4*8))=0xe7dcf096;
*((unsigned int *)((unsigned long)context_ptr+0x00006174+4*9))=0xa508e50d;
*((unsigned int *)((unsigned long)context_ptr+0x00006174+4*10))=0x546b80ee;
*((unsigned int *)((unsigned long)context_ptr+0x00003408))=0x04c0002c;
*((unsigned int *)((unsigned long)context_ptr+0x00003408+4*1))=0x0000653c;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000408))=0x03c0002c;
*((unsigned int *)((unsigned long)context_ptr+0x00000408+4*1))=0x00006174;
*((unsigned int *)((unsigned long)context_ptr+0x00000408+4*2))=0x00006354;
*((unsigned int *)((unsigned long)context_ptr+0x00000408+4*3))=0x0222002c;
*((unsigned int *)((unsigned long)context_ptr+0x00000408+4*4))=0x00a68943;
*((unsigned int *)((unsigned long)context_ptr+0x00000408+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000000b4&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x0000637c,"\x2b\x3c\x39\xe0\x76\xe0\x23\x90\x03\xee\x01\x63\xcd\xff\x04\xd2\x82\x09\xc6\x1c\x9c\xc7\xac\x61\x06\x6f\xe9\x55\x3f\x23\x00\x00",30))
printf("strip: 2b3c39e076e02390, Pass\n");
else
printf("strip: 2b3c39e076e02390, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000061a0))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x000061a0+4*1))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x000061a0+4*2))=0x0106002d;
*((unsigned int *)((unsigned long)context_ptr+0x000061ac))=0x9bb6421b;
*((unsigned int *)((unsigned long)context_ptr+0x000061ac+4*1))=0xc4ec286b;
*((unsigned int *)((unsigned long)context_ptr+0x000061ac+4*2))=0x1cc6d0af;
*((unsigned int *)((unsigned long)context_ptr+0x000061ac+4*3))=0x7bbfd6c5;
*((unsigned int *)((unsigned long)context_ptr+0x000061ac+4*4))=0x43c319af;
*((unsigned int *)((unsigned long)context_ptr+0x000061ac+4*5))=0x8982a2c8;
*((unsigned int *)((unsigned long)context_ptr+0x000061ac+4*6))=0xc6030a13;
*((unsigned int *)((unsigned long)context_ptr+0x000061ac+4*7))=0xfa621f23;
*((unsigned int *)((unsigned long)context_ptr+0x000061ac+4*8))=0x15d150e2;
*((unsigned int *)((unsigned long)context_ptr+0x000061ac+4*9))=0x0cfc9464;
*((unsigned int *)((unsigned long)context_ptr+0x000061ac+4*10))=0x9907eb69;
*((unsigned int *)((unsigned long)context_ptr+0x000061ac+4*11))=0x00000066;
*((unsigned int *)((unsigned long)context_ptr+0x00003420))=0x04c0002d;
*((unsigned int *)((unsigned long)context_ptr+0x00003420+4*1))=0x00006360;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000420))=0x03c0002d;
*((unsigned int *)((unsigned long)context_ptr+0x00000420+4*1))=0x000061ac;
*((unsigned int *)((unsigned long)context_ptr+0x00000420+4*2))=0x000061a0;
*((unsigned int *)((unsigned long)context_ptr+0x00000420+4*3))=0x0222002d;
*((unsigned int *)((unsigned long)context_ptr+0x00000420+4*4))=0x00b6e4d1;
*((unsigned int *)((unsigned long)context_ptr+0x00000420+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000000ba&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x0000639c,"\xe2\x5f\x05\x9c\x79\x3c\x0a\x52\xcc\xf6\x1b\xe0\x0c\xb6\x06\x6b\xde\x64\xec\xb6\x9a\x29\x57\x69\x97\xfe\x48\x80\xee\x58\xa0\x00",31))
printf("strip: e25f059c793c0a52, Pass\n");
else
printf("strip: e25f059c793c0a52, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006008))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x00006008+4*1))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x00006008+4*2))=0x0106002e;
*((unsigned int *)((unsigned long)context_ptr+0x00006568))=0x02674049;
*((unsigned int *)((unsigned long)context_ptr+0x00006568+4*1))=0x11c60da2;
*((unsigned int *)((unsigned long)context_ptr+0x00006568+4*2))=0xd5c54802;
*((unsigned int *)((unsigned long)context_ptr+0x00006568+4*3))=0x551df081;
*((unsigned int *)((unsigned long)context_ptr+0x00006568+4*4))=0x942552bd;
*((unsigned int *)((unsigned long)context_ptr+0x00006568+4*5))=0x54405f10;
*((unsigned int *)((unsigned long)context_ptr+0x00006568+4*6))=0x5015897c;
*((unsigned int *)((unsigned long)context_ptr+0x00006568+4*7))=0x6d7a6762;
*((unsigned int *)((unsigned long)context_ptr+0x00006568+4*8))=0xd4a43812;
*((unsigned int *)((unsigned long)context_ptr+0x00006568+4*9))=0x27122582;
*((unsigned int *)((unsigned long)context_ptr+0x00006568+4*10))=0x86aa9062;
*((unsigned int *)((unsigned long)context_ptr+0x00006568+4*11))=0x00005a90;
*((unsigned int *)((unsigned long)context_ptr+0x00003438))=0x04c0002e;
*((unsigned int *)((unsigned long)context_ptr+0x00003438+4*1))=0x00006598;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000438))=0x03c0002e;
*((unsigned int *)((unsigned long)context_ptr+0x00000438+4*1))=0x00006568;
*((unsigned int *)((unsigned long)context_ptr+0x00000438+4*2))=0x00006008;
*((unsigned int *)((unsigned long)context_ptr+0x00000438+4*3))=0x0222002e;
*((unsigned int *)((unsigned long)context_ptr+0x00000438+4*4))=0x00e45d89;
*((unsigned int *)((unsigned long)context_ptr+0x00000438+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000000c0&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000063bc,"\x9c\x2a\x6e\x65\x13\xb5\xae\xc7\x8b\x8d\x2b\x35\x3a\x86\xd1\x5b\xe1\xbc\xb7\x55\x1e\xf6\xda\x68\xdc\xe6\x57\x80\x54\xb1\xe9\xfc",32))
printf("strip: 9c2a6e6513b5aec7, Pass\n");
else
printf("strip: 9c2a6e6513b5aec7, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006014))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x00006014+4*1))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x00006014+4*2))=0x0106002f;
*((unsigned int *)((unsigned long)context_ptr+0x000061dc))=0x8b9e6f1c;
*((unsigned int *)((unsigned long)context_ptr+0x000061dc+4*1))=0x5b0a1c84;
*((unsigned int *)((unsigned long)context_ptr+0x000061dc+4*2))=0x7b442ef1;
*((unsigned int *)((unsigned long)context_ptr+0x000061dc+4*3))=0xa500f2ea;
*((unsigned int *)((unsigned long)context_ptr+0x000061dc+4*4))=0xe3bea73c;
*((unsigned int *)((unsigned long)context_ptr+0x000061dc+4*5))=0x29c8d8ae;
*((unsigned int *)((unsigned long)context_ptr+0x000061dc+4*6))=0xff86bd0b;
*((unsigned int *)((unsigned long)context_ptr+0x000061dc+4*7))=0xe049622a;
*((unsigned int *)((unsigned long)context_ptr+0x000061dc+4*8))=0xffb5e97b;
*((unsigned int *)((unsigned long)context_ptr+0x000061dc+4*9))=0x712cf999;
*((unsigned int *)((unsigned long)context_ptr+0x000061dc+4*10))=0xdd91fa94;
*((unsigned int *)((unsigned long)context_ptr+0x000061dc+4*11))=0x006483a0;
*((unsigned int *)((unsigned long)context_ptr+0x00003450))=0x04c0002f;
*((unsigned int *)((unsigned long)context_ptr+0x00003450+4*1))=0x00006390;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000450))=0x03c0002f;
*((unsigned int *)((unsigned long)context_ptr+0x00000450+4*1))=0x000061dc;
*((unsigned int *)((unsigned long)context_ptr+0x00000450+4*2))=0x00006014;
*((unsigned int *)((unsigned long)context_ptr+0x00000450+4*3))=0x0222002f;
*((unsigned int *)((unsigned long)context_ptr+0x00000450+4*4))=0x00d09e1a;
*((unsigned int *)((unsigned long)context_ptr+0x00000450+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000000c6&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006400,"\x84\xb2\xa5\x34\xa4\xfb\x1c\xb0\x9d\x60\xcb\x02\xe4\xd1\x7b\x1b\x73\x95\x40\x7c\xc6\xec\x8f\xd3\x13\xdb\xeb\x2b\xd3\xd9\xe0\x84\x9b\x00\x00\x00",33))
printf("strip: 84b2a534a4fb1cb0, Pass\n");
else
printf("strip: 84b2a534a4fb1cb0, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006020))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x00006020+4*1))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x00006020+4*2))=0x01060030;
*((unsigned int *)((unsigned long)context_ptr+0x000063c0))=0x7aec1db5;
*((unsigned int *)((unsigned long)context_ptr+0x000063c0+4*1))=0xb59a99b1;
*((unsigned int *)((unsigned long)context_ptr+0x000063c0+4*2))=0x63357f16;
*((unsigned int *)((unsigned long)context_ptr+0x000063c0+4*3))=0xbb685a83;
*((unsigned int *)((unsigned long)context_ptr+0x000063c0+4*4))=0x299af40b;
*((unsigned int *)((unsigned long)context_ptr+0x000063c0+4*5))=0xb080148e;
*((unsigned int *)((unsigned long)context_ptr+0x000063c0+4*6))=0xefac506b;
*((unsigned int *)((unsigned long)context_ptr+0x000063c0+4*7))=0x1ddd62df;
*((unsigned int *)((unsigned long)context_ptr+0x000063c0+4*8))=0x9dc3fb0f;
*((unsigned int *)((unsigned long)context_ptr+0x000063c0+4*9))=0xdae64f8f;
*((unsigned int *)((unsigned long)context_ptr+0x000063c0+4*10))=0xb9ad387b;
*((unsigned int *)((unsigned long)context_ptr+0x000063c0+4*11))=0xfd17cafe;
*((unsigned int *)((unsigned long)context_ptr+0x00003468))=0x04c00030;
*((unsigned int *)((unsigned long)context_ptr+0x00003468+4*1))=0x000063f0;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000468))=0x03c00030;
*((unsigned int *)((unsigned long)context_ptr+0x00000468+4*1))=0x000063c0;
*((unsigned int *)((unsigned long)context_ptr+0x00000468+4*2))=0x00006020;
*((unsigned int *)((unsigned long)context_ptr+0x00000468+4*3))=0x02220030;
*((unsigned int *)((unsigned long)context_ptr+0x00000468+4*4))=0x00f66b72;
*((unsigned int *)((unsigned long)context_ptr+0x00000468+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000000cc&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006424,"\x1a\xd5\x7d\xa5\x79\x2e\x8a\x28\xda\xd4\x24\x11\x11\x64\xf3\x8e\x43\x3a\x1c\x24\xcf\x23\xdd\xd2\x23\x8f\x01\xdc\x8e\xc1\x7d\xb0\xee\x8f\x00\x00",34))
printf("strip: 1ad57da5792e8a28, Pass\n");
else
printf("strip: 1ad57da5792e8a28, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x0000602c))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x0000602c+4*1))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x0000602c+4*2))=0x01060031;
*((unsigned int *)((unsigned long)context_ptr+0x0000620c))=0xdd87ecf1;
*((unsigned int *)((unsigned long)context_ptr+0x0000620c+4*1))=0x97e84b32;
*((unsigned int *)((unsigned long)context_ptr+0x0000620c+4*2))=0x7e3a2139;
*((unsigned int *)((unsigned long)context_ptr+0x0000620c+4*3))=0x1445bc4d;
*((unsigned int *)((unsigned long)context_ptr+0x0000620c+4*4))=0x2ef9a9e5;
*((unsigned int *)((unsigned long)context_ptr+0x0000620c+4*5))=0x7a8904de;
*((unsigned int *)((unsigned long)context_ptr+0x0000620c+4*6))=0xe545d020;
*((unsigned int *)((unsigned long)context_ptr+0x0000620c+4*7))=0xcadddab3;
*((unsigned int *)((unsigned long)context_ptr+0x0000620c+4*8))=0x352401bc;
*((unsigned int *)((unsigned long)context_ptr+0x0000620c+4*9))=0x7c200093;
*((unsigned int *)((unsigned long)context_ptr+0x0000620c+4*10))=0x2c38510a;
*((unsigned int *)((unsigned long)context_ptr+0x0000620c+4*11))=0xa63be151;
*((unsigned int *)((unsigned long)context_ptr+0x0000620c+4*12))=0x000000bb;
*((unsigned int *)((unsigned long)context_ptr+0x00003480))=0x04c00031;
*((unsigned int *)((unsigned long)context_ptr+0x00003480+4*1))=0x000065c8;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000480))=0x03c00031;
*((unsigned int *)((unsigned long)context_ptr+0x00000480+4*1))=0x0000620c;
*((unsigned int *)((unsigned long)context_ptr+0x00000480+4*2))=0x0000602c;
*((unsigned int *)((unsigned long)context_ptr+0x00000480+4*3))=0x02220031;
*((unsigned int *)((unsigned long)context_ptr+0x00000480+4*4))=0x00bba126;
*((unsigned int *)((unsigned long)context_ptr+0x00000480+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000000d2&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006240,"\x61\xc2\x3b\xef\xbe\x7b\xe1\x5b\x62\x21\xc7\x66\x80\x78\xa7\x5f\xea\x6e\x5b\x66\xc4\xfe\xdd\x7a\x4a\x72\x58\x3e\x2f\xf4\x7f\x1c\x62\x63\x83\x00",35))
printf("strip: 61c23befbe7be15b, Pass\n");
else
printf("strip: 61c23befbe7be15b, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006038))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x00006038+4*1))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x00006038+4*2))=0x01060032;
*((unsigned int *)((unsigned long)context_ptr+0x000065fc))=0x89e56c75;
*((unsigned int *)((unsigned long)context_ptr+0x000065fc+4*1))=0x70112dc2;
*((unsigned int *)((unsigned long)context_ptr+0x000065fc+4*2))=0xdc588353;
*((unsigned int *)((unsigned long)context_ptr+0x000065fc+4*3))=0xb52062bc;
*((unsigned int *)((unsigned long)context_ptr+0x000065fc+4*4))=0x9d08268a;
*((unsigned int *)((unsigned long)context_ptr+0x000065fc+4*5))=0x776a9384;
*((unsigned int *)((unsigned long)context_ptr+0x000065fc+4*6))=0x1f891664;
*((unsigned int *)((unsigned long)context_ptr+0x000065fc+4*7))=0x332abfac;
*((unsigned int *)((unsigned long)context_ptr+0x000065fc+4*8))=0xe368993d;
*((unsigned int *)((unsigned long)context_ptr+0x000065fc+4*9))=0x1737868c;
*((unsigned int *)((unsigned long)context_ptr+0x000065fc+4*10))=0x312119ec;
*((unsigned int *)((unsigned long)context_ptr+0x000065fc+4*11))=0x656ea393;
*((unsigned int *)((unsigned long)context_ptr+0x000065fc+4*12))=0x000043a4;
*((unsigned int *)((unsigned long)context_ptr+0x00003498))=0x04c00032;
*((unsigned int *)((unsigned long)context_ptr+0x00003498+4*1))=0x00006630;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000498))=0x03c00032;
*((unsigned int *)((unsigned long)context_ptr+0x00000498+4*1))=0x000065fc;
*((unsigned int *)((unsigned long)context_ptr+0x00000498+4*2))=0x00006038;
*((unsigned int *)((unsigned long)context_ptr+0x00000498+4*3))=0x02220032;
*((unsigned int *)((unsigned long)context_ptr+0x00000498+4*4))=0x0045ac15;
*((unsigned int *)((unsigned long)context_ptr+0x00000498+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000000d8&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006448,"\x0a\x17\x33\x53\x1c\xcc\x5d\x3b\x0b\x61\x01\x1d\x9a\xef\x33\xbd\x32\x00\xe5\xd8\x11\x2d\x3b\xed\x61\xce\x6f\x61\xc3\x9d\x44\x95\xb4\xd3\xad\xa4",36))
printf("strip: 0a1733531ccc5d3b, Pass\n");
else
printf("strip: 0a1733531ccc5d3b, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006044))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x00006044+4*1))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x00006044+4*2))=0x01060033;
*((unsigned int *)((unsigned long)context_ptr+0x00006240))=0xb8544ad5;
*((unsigned int *)((unsigned long)context_ptr+0x00006240+4*1))=0x16e0b6aa;
*((unsigned int *)((unsigned long)context_ptr+0x00006240+4*2))=0xa79c7f1f;
*((unsigned int *)((unsigned long)context_ptr+0x00006240+4*3))=0x3deb223a;
*((unsigned int *)((unsigned long)context_ptr+0x00006240+4*4))=0xa2844804;
*((unsigned int *)((unsigned long)context_ptr+0x00006240+4*5))=0x518225bd;
*((unsigned int *)((unsigned long)context_ptr+0x00006240+4*6))=0x31cf5cb9;
*((unsigned int *)((unsigned long)context_ptr+0x00006240+4*7))=0xb96c85fe;
*((unsigned int *)((unsigned long)context_ptr+0x00006240+4*8))=0x49700960;
*((unsigned int *)((unsigned long)context_ptr+0x00006240+4*9))=0x7dd486a9;
*((unsigned int *)((unsigned long)context_ptr+0x00006240+4*10))=0x43922627;
*((unsigned int *)((unsigned long)context_ptr+0x00006240+4*11))=0xea23f136;
*((unsigned int *)((unsigned long)context_ptr+0x00006240+4*12))=0x00d6ef89;
*((unsigned int *)((unsigned long)context_ptr+0x000034b0))=0x04c00033;
*((unsigned int *)((unsigned long)context_ptr+0x000034b0+4*1))=0x00006420;
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
*((unsigned int *)((unsigned long)context_ptr+0x000004b0))=0x03c00033;
*((unsigned int *)((unsigned long)context_ptr+0x000004b0+4*1))=0x00006240;
*((unsigned int *)((unsigned long)context_ptr+0x000004b0+4*2))=0x00006044;
*((unsigned int *)((unsigned long)context_ptr+0x000004b0+4*3))=0x02220033;
*((unsigned int *)((unsigned long)context_ptr+0x000004b0+4*4))=0x00076475;
*((unsigned int *)((unsigned long)context_ptr+0x000004b0+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000000de&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x0000646c,"\x1f\xe4\x78\x74\x56\x6a\x60\x90\x55\xd2\x3b\x3f\x7b\xef\x06\xb9\x01\x67\xc3\x72\x6d\x40\x79\x3a\x48\xa7\x99\xed\xf8\x85\x16\x4c\x84\xac\xf2\x27\x09\x00\x00\x00",37))
printf("strip: 1fe47874566a6090, Pass\n");
else
printf("strip: 1fe47874566a6090, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006050))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x00006050+4*1))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x00006050+4*2))=0x01060034;
*((unsigned int *)((unsigned long)context_ptr+0x00006274))=0x94ada029;
*((unsigned int *)((unsigned long)context_ptr+0x00006274+4*1))=0xa6f484ba;
*((unsigned int *)((unsigned long)context_ptr+0x00006274+4*2))=0x992403a0;
*((unsigned int *)((unsigned long)context_ptr+0x00006274+4*3))=0x27a324c4;
*((unsigned int *)((unsigned long)context_ptr+0x00006274+4*4))=0x119ed2c3;
*((unsigned int *)((unsigned long)context_ptr+0x00006274+4*5))=0xc7774547;
*((unsigned int *)((unsigned long)context_ptr+0x00006274+4*6))=0x24b5fd94;
*((unsigned int *)((unsigned long)context_ptr+0x00006274+4*7))=0xa3550ffa;
*((unsigned int *)((unsigned long)context_ptr+0x00006274+4*8))=0x3d4b0563;
*((unsigned int *)((unsigned long)context_ptr+0x00006274+4*9))=0xdf2497c6;
*((unsigned int *)((unsigned long)context_ptr+0x00006274+4*10))=0xc3df5136;
*((unsigned int *)((unsigned long)context_ptr+0x00006274+4*11))=0xb5fa846b;
*((unsigned int *)((unsigned long)context_ptr+0x00006274+4*12))=0xecfca7b7;
*((unsigned int *)((unsigned long)context_ptr+0x000034c8))=0x04c00034;
*((unsigned int *)((unsigned long)context_ptr+0x000034c8+4*1))=0x00006454;
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
*((unsigned int *)((unsigned long)context_ptr+0x000004c8))=0x03c00034;
*((unsigned int *)((unsigned long)context_ptr+0x000004c8+4*1))=0x00006274;
*((unsigned int *)((unsigned long)context_ptr+0x000004c8+4*2))=0x00006050;
*((unsigned int *)((unsigned long)context_ptr+0x000004c8+4*3))=0x02220034;
*((unsigned int *)((unsigned long)context_ptr+0x000004c8+4*4))=0x005dde2c;
*((unsigned int *)((unsigned long)context_ptr+0x000004c8+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000000e4&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006494,"\xec\xb6\x98\x6f\xa2\x9e\xe6\x92\x36\x70\x3e\xe7\xd7\x8e\x32\x0b\x22\x71\xac\x39\xaf\xdc\xc1\x6c\xa5\xfd\xe2\x56\xaf\x29\x8e\x5b\x70\x70\xa9\xd8\x77\x25\x00\x00",38))
printf("strip: ecb6986fa29ee692, Pass\n");
else
printf("strip: ecb6986fa29ee692, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000062a8))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x000062a8+4*1))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x000062a8+4*2))=0x01060035;
*((unsigned int *)((unsigned long)context_ptr+0x0000605c))=0x2984919c;
*((unsigned int *)((unsigned long)context_ptr+0x0000605c+4*1))=0x41621b01;
*((unsigned int *)((unsigned long)context_ptr+0x0000605c+4*2))=0x2183787c;
*((unsigned int *)((unsigned long)context_ptr+0x0000605c+4*3))=0x032cf37f;
*((unsigned int *)((unsigned long)context_ptr+0x0000605c+4*4))=0x1bdcb556;
*((unsigned int *)((unsigned long)context_ptr+0x0000605c+4*5))=0xeb9f4f07;
*((unsigned int *)((unsigned long)context_ptr+0x0000605c+4*6))=0xa420c754;
*((unsigned int *)((unsigned long)context_ptr+0x0000605c+4*7))=0x71e9c23f;
*((unsigned int *)((unsigned long)context_ptr+0x0000605c+4*8))=0x68d95aaf;
*((unsigned int *)((unsigned long)context_ptr+0x0000605c+4*9))=0x738efc95;
*((unsigned int *)((unsigned long)context_ptr+0x0000605c+4*10))=0xb386f318;
*((unsigned int *)((unsigned long)context_ptr+0x0000605c+4*11))=0x18a33ca7;
*((unsigned int *)((unsigned long)context_ptr+0x0000605c+4*12))=0x4d99d70e;
*((unsigned int *)((unsigned long)context_ptr+0x0000605c+4*13))=0x00000086;
*((unsigned int *)((unsigned long)context_ptr+0x000034e0))=0x04c00035;
*((unsigned int *)((unsigned long)context_ptr+0x000034e0+4*1))=0x00006664;
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
*((unsigned int *)((unsigned long)context_ptr+0x000004e0))=0x03c00035;
*((unsigned int *)((unsigned long)context_ptr+0x000004e0+4*1))=0x0000605c;
*((unsigned int *)((unsigned long)context_ptr+0x000004e0+4*2))=0x000062a8;
*((unsigned int *)((unsigned long)context_ptr+0x000004e0+4*3))=0x02220035;
*((unsigned int *)((unsigned long)context_ptr+0x000004e0+4*4))=0x003ca581;
*((unsigned int *)((unsigned long)context_ptr+0x000004e0+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000000ea&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000064bc,"\xfe\x22\xa4\x7d\x61\x89\x14\xf8\x7e\x03\x6b\xc1\x4f\xbe\xc4\x3d\xf7\x07\xdd\x83\x27\x42\x97\x47\xd6\x38\x62\x81\x56\xd2\x43\x16\x27\xa0\x90\x10\xfe\x7a\x51\x00",39))
printf("strip: fe22a47d618914f8, Pass\n");
else
printf("strip: fe22a47d618914f8, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000062b4))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x000062b4+4*1))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x000062b4+4*2))=0x01060036;
*((unsigned int *)((unsigned long)context_ptr+0x00006094))=0xc71d4fb9;
*((unsigned int *)((unsigned long)context_ptr+0x00006094+4*1))=0xbd9d1ae3;
*((unsigned int *)((unsigned long)context_ptr+0x00006094+4*2))=0x71afd63e;
*((unsigned int *)((unsigned long)context_ptr+0x00006094+4*3))=0x2ad4422a;
*((unsigned int *)((unsigned long)context_ptr+0x00006094+4*4))=0x048f92b4;
*((unsigned int *)((unsigned long)context_ptr+0x00006094+4*5))=0x61a14f1f;
*((unsigned int *)((unsigned long)context_ptr+0x00006094+4*6))=0x98766241;
*((unsigned int *)((unsigned long)context_ptr+0x00006094+4*7))=0xce6c5e8f;
*((unsigned int *)((unsigned long)context_ptr+0x00006094+4*8))=0x489af896;
*((unsigned int *)((unsigned long)context_ptr+0x00006094+4*9))=0xbcda7983;
*((unsigned int *)((unsigned long)context_ptr+0x00006094+4*10))=0x4540b7e1;
*((unsigned int *)((unsigned long)context_ptr+0x00006094+4*11))=0x52e6e129;
*((unsigned int *)((unsigned long)context_ptr+0x00006094+4*12))=0xb3c97905;
*((unsigned int *)((unsigned long)context_ptr+0x00006094+4*13))=0x000005ac;
*((unsigned int *)((unsigned long)context_ptr+0x000034f8))=0x04c00036;
*((unsigned int *)((unsigned long)context_ptr+0x000034f8+4*1))=0x00006488;
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
*((unsigned int *)((unsigned long)context_ptr+0x000004f8))=0x03c00036;
*((unsigned int *)((unsigned long)context_ptr+0x000004f8+4*1))=0x00006094;
*((unsigned int *)((unsigned long)context_ptr+0x000004f8+4*2))=0x000062b4;
*((unsigned int *)((unsigned long)context_ptr+0x000004f8+4*3))=0x02220036;
*((unsigned int *)((unsigned long)context_ptr+0x000004f8+4*4))=0x0024fa91;
*((unsigned int *)((unsigned long)context_ptr+0x000004f8+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000000f0&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000062c8,"\xd3\x8a\x56\x8d\x29\x7e\x05\xdc\x54\x58\xfe\x9d\x6a\xca\x11\x92\x85\xdc\x96\x7c\x85\xc8\x58\x8e\xb5\xfe\xb1\xf6\x66\x9b\xbe\x59\x44\xf9\x59\xff\xda\x37\xd4\xfb",40))
printf("strip: d38a568d297e05dc, Pass\n");
else
printf("strip: d38a568d297e05dc, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000064c0))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x000064c0+4*1))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x000064c0+4*2))=0x01060037;
*((unsigned int *)((unsigned long)context_ptr+0x000060cc))=0xb1b8a8fd;
*((unsigned int *)((unsigned long)context_ptr+0x000060cc+4*1))=0x144767f0;
*((unsigned int *)((unsigned long)context_ptr+0x000060cc+4*2))=0xbdbe7a05;
*((unsigned int *)((unsigned long)context_ptr+0x000060cc+4*3))=0xddd49d00;
*((unsigned int *)((unsigned long)context_ptr+0x000060cc+4*4))=0xb3b46bc5;
*((unsigned int *)((unsigned long)context_ptr+0x000060cc+4*5))=0xa4580910;
*((unsigned int *)((unsigned long)context_ptr+0x000060cc+4*6))=0xc5c2a561;
*((unsigned int *)((unsigned long)context_ptr+0x000060cc+4*7))=0xa08df848;
*((unsigned int *)((unsigned long)context_ptr+0x000060cc+4*8))=0xac27aca2;
*((unsigned int *)((unsigned long)context_ptr+0x000060cc+4*9))=0xf9b6f76e;
*((unsigned int *)((unsigned long)context_ptr+0x000060cc+4*10))=0x9996d5fd;
*((unsigned int *)((unsigned long)context_ptr+0x000060cc+4*11))=0xe96b5e78;
*((unsigned int *)((unsigned long)context_ptr+0x000060cc+4*12))=0x70092ba5;
*((unsigned int *)((unsigned long)context_ptr+0x000060cc+4*13))=0x003a1070;
*((unsigned int *)((unsigned long)context_ptr+0x00003510))=0x04c00037;
*((unsigned int *)((unsigned long)context_ptr+0x00003510+4*1))=0x0000669c;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000510))=0x03c00037;
*((unsigned int *)((unsigned long)context_ptr+0x00000510+4*1))=0x000060cc;
*((unsigned int *)((unsigned long)context_ptr+0x00000510+4*2))=0x000064c0;
*((unsigned int *)((unsigned long)context_ptr+0x00000510+4*3))=0x02220037;
*((unsigned int *)((unsigned long)context_ptr+0x00000510+4*4))=0x002ea5ce;
*((unsigned int *)((unsigned long)context_ptr+0x00000510+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000000f6&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000064e4,"\x72\x6a\x88\x68\x14\xfa\xff\x2c\x3d\x6f\xb2\x08\xd5\xa3\x44\xde\xa9\x51\x8c\xfa\x0c\xb5\xd9\xb1\x23\x98\xc9\x6b\x95\x40\x50\xce\x7d\x72\x1f\x5f\x85\x3b\xce\x62\x3d\x00\x00\x00",41))
printf("strip: 726a886814faff2c, Pass\n");
else
printf("strip: 726a886814faff2c, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006104))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x00006104+4*1))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x00006104+4*2))=0x01060038;
*((unsigned int *)((unsigned long)context_ptr+0x000064cc))=0xf5704a6e;
*((unsigned int *)((unsigned long)context_ptr+0x000064cc+4*1))=0x1be57a09;
*((unsigned int *)((unsigned long)context_ptr+0x000064cc+4*2))=0xcc48d01d;
*((unsigned int *)((unsigned long)context_ptr+0x000064cc+4*3))=0x54d1084d;
*((unsigned int *)((unsigned long)context_ptr+0x000064cc+4*4))=0xd4a60f76;
*((unsigned int *)((unsigned long)context_ptr+0x000064cc+4*5))=0x8ca2ee38;
*((unsigned int *)((unsigned long)context_ptr+0x000064cc+4*6))=0x0a6ce034;
*((unsigned int *)((unsigned long)context_ptr+0x000064cc+4*7))=0x0e4b5eec;
*((unsigned int *)((unsigned long)context_ptr+0x000064cc+4*8))=0xdedf0b08;
*((unsigned int *)((unsigned long)context_ptr+0x000064cc+4*9))=0xf2231478;
*((unsigned int *)((unsigned long)context_ptr+0x000064cc+4*10))=0x1013cb8f;
*((unsigned int *)((unsigned long)context_ptr+0x000064cc+4*11))=0xefd21dc6;
*((unsigned int *)((unsigned long)context_ptr+0x000064cc+4*12))=0x72b71d6e;
*((unsigned int *)((unsigned long)context_ptr+0x000064cc+4*13))=0x238ae380;
*((unsigned int *)((unsigned long)context_ptr+0x00003528))=0x04c00038;
*((unsigned int *)((unsigned long)context_ptr+0x00003528+4*1))=0x000062c0;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000528))=0x03c00038;
*((unsigned int *)((unsigned long)context_ptr+0x00000528+4*1))=0x000064cc;
*((unsigned int *)((unsigned long)context_ptr+0x00000528+4*2))=0x00006104;
*((unsigned int *)((unsigned long)context_ptr+0x00000528+4*3))=0x02220038;
*((unsigned int *)((unsigned long)context_ptr+0x00000528+4*4))=0x0027ef09;
*((unsigned int *)((unsigned long)context_ptr+0x00000528+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000000fc&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006510,"\x5b\x3f\x38\x4d\x25\x8d\x40\x06\x3b\xd2\x6a\xe2\xf1\x3e\x8f\xe1\x94\x2b\x3f\xfc\x4c\xde\xcb\xbd\xb8\xca\xd8\x0f\x2a\x81\x36\x88\x7e\x20\x16\x02\xd3\x14\xf6\xfb\xbe\x73\x00\x00",42))
printf("strip: 5b3f384d258d4006, Pass\n");
else
printf("strip: 5b3f384d258d4006, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006110))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x00006110+4*1))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x00006110+4*2))=0x01060039;
*((unsigned int *)((unsigned long)context_ptr+0x000062f8))=0x6727b13d;
*((unsigned int *)((unsigned long)context_ptr+0x000062f8+4*1))=0x5a485dc7;
*((unsigned int *)((unsigned long)context_ptr+0x000062f8+4*2))=0xbd24025f;
*((unsigned int *)((unsigned long)context_ptr+0x000062f8+4*3))=0x1d23a7b1;
*((unsigned int *)((unsigned long)context_ptr+0x000062f8+4*4))=0xf7207b7d;
*((unsigned int *)((unsigned long)context_ptr+0x000062f8+4*5))=0xa82cdfd1;
*((unsigned int *)((unsigned long)context_ptr+0x000062f8+4*6))=0x18fc52d0;
*((unsigned int *)((unsigned long)context_ptr+0x000062f8+4*7))=0x304025cb;
*((unsigned int *)((unsigned long)context_ptr+0x000062f8+4*8))=0xcc3eab1d;
*((unsigned int *)((unsigned long)context_ptr+0x000062f8+4*9))=0xfdc6f5c4;
*((unsigned int *)((unsigned long)context_ptr+0x000062f8+4*10))=0x6454088e;
*((unsigned int *)((unsigned long)context_ptr+0x000062f8+4*11))=0xcc456bf7;
*((unsigned int *)((unsigned long)context_ptr+0x000062f8+4*12))=0xb9fb0beb;
*((unsigned int *)((unsigned long)context_ptr+0x000062f8+4*13))=0xad01a6fe;
*((unsigned int *)((unsigned long)context_ptr+0x000062f8+4*14))=0x0000003a;
*((unsigned int *)((unsigned long)context_ptr+0x00003540))=0x04c00039;
*((unsigned int *)((unsigned long)context_ptr+0x00003540+4*1))=0x000066d4;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000540))=0x03c00039;
*((unsigned int *)((unsigned long)context_ptr+0x00000540+4*1))=0x000062f8;
*((unsigned int *)((unsigned long)context_ptr+0x00000540+4*2))=0x00006110;
*((unsigned int *)((unsigned long)context_ptr+0x00000540+4*3))=0x02220039;
*((unsigned int *)((unsigned long)context_ptr+0x00000540+4*4))=0x0014abd4;
*((unsigned int *)((unsigned long)context_ptr+0x00000540+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000102&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006148,"\xc2\x22\xa0\x82\x03\x25\xaa\x5d\xf6\x80\xb0\x22\x7a\xbb\xd5\x33\x65\x79\x70\x79\x4b\xcf\xe9\x59\xa3\x61\x94\xb2\x80\xac\xc1\xd7\x30\x37\x83\x82\xce\x84\xe6\xc7\x81\xd3\x79\x00",43))
printf("strip: c222a0820325aa5d, Pass\n");
else
printf("strip: c222a0820325aa5d, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006334))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x00006334+4*1))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x00006334+4*2))=0x0106003a;
*((unsigned int *)((unsigned long)context_ptr+0x0000611c))=0xe3549b07;
*((unsigned int *)((unsigned long)context_ptr+0x0000611c+4*1))=0xf7328c3b;
*((unsigned int *)((unsigned long)context_ptr+0x0000611c+4*2))=0x74e4c0a4;
*((unsigned int *)((unsigned long)context_ptr+0x0000611c+4*3))=0x559e738b;
*((unsigned int *)((unsigned long)context_ptr+0x0000611c+4*4))=0x04c55dd2;
*((unsigned int *)((unsigned long)context_ptr+0x0000611c+4*5))=0xb8e67a5d;
*((unsigned int *)((unsigned long)context_ptr+0x0000611c+4*6))=0xb9e6a2bb;
*((unsigned int *)((unsigned long)context_ptr+0x0000611c+4*7))=0x03c3eba1;
*((unsigned int *)((unsigned long)context_ptr+0x0000611c+4*8))=0x69bf30de;
*((unsigned int *)((unsigned long)context_ptr+0x0000611c+4*9))=0xff6d2764;
*((unsigned int *)((unsigned long)context_ptr+0x0000611c+4*10))=0x36a4bcd3;
*((unsigned int *)((unsigned long)context_ptr+0x0000611c+4*11))=0x00e8ee10;
*((unsigned int *)((unsigned long)context_ptr+0x0000611c+4*12))=0x2719bfe9;
*((unsigned int *)((unsigned long)context_ptr+0x0000611c+4*13))=0x6be7412d;
*((unsigned int *)((unsigned long)context_ptr+0x0000611c+4*14))=0x00006c89;
*((unsigned int *)((unsigned long)context_ptr+0x00003558))=0x04c0003a;
*((unsigned int *)((unsigned long)context_ptr+0x00003558+4*1))=0x00006710;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000558))=0x03c0003a;
*((unsigned int *)((unsigned long)context_ptr+0x00000558+4*1))=0x0000611c;
*((unsigned int *)((unsigned long)context_ptr+0x00000558+4*2))=0x00006334;
*((unsigned int *)((unsigned long)context_ptr+0x00000558+4*3))=0x0222003a;
*((unsigned int *)((unsigned long)context_ptr+0x00000558+4*4))=0x00b56ac8;
*((unsigned int *)((unsigned long)context_ptr+0x00000558+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000108&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x0000653c,"\x2f\x2c\xf7\x5c\xcf\x02\xfd\x04\x9b\xed\xd4\x4f\xd2\x64\x7f\x5c\x5a\x95\xc8\xb3\xc4\x03\x88\x5a\x35\xeb\x32\x2f\x2d\xa8\x9c\x81\x96\xf0\xdc\xe7\x0d\xe5\x08\xa5\xee\x80\x6b\x54",44))
printf("strip: 2f2cf75ccf02fd04, Pass\n");
else
printf("strip: 2f2cf75ccf02fd04, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006340))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x00006340+4*1))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x00006340+4*2))=0x0106003b;
*((unsigned int *)((unsigned long)context_ptr+0x00006158))=0x06b6cc15;
*((unsigned int *)((unsigned long)context_ptr+0x00006158+4*1))=0x59f2cf7e;
*((unsigned int *)((unsigned long)context_ptr+0x00006158+4*2))=0xb4be7178;
*((unsigned int *)((unsigned long)context_ptr+0x00006158+4*3))=0x06962f79;
*((unsigned int *)((unsigned long)context_ptr+0x00006158+4*4))=0x18114e5b;
*((unsigned int *)((unsigned long)context_ptr+0x00006158+4*5))=0xef2074c9;
*((unsigned int *)((unsigned long)context_ptr+0x00006158+4*6))=0x27b17050;
*((unsigned int *)((unsigned long)context_ptr+0x00006158+4*7))=0xb57dd8c8;
*((unsigned int *)((unsigned long)context_ptr+0x00006158+4*8))=0x5cc6fdb9;
*((unsigned int *)((unsigned long)context_ptr+0x00006158+4*9))=0xe5886482;
*((unsigned int *)((unsigned long)context_ptr+0x00006158+4*10))=0x2581e418;
*((unsigned int *)((unsigned long)context_ptr+0x00006158+4*11))=0x780631ef;
*((unsigned int *)((unsigned long)context_ptr+0x00006158+4*12))=0x90a00c92;
*((unsigned int *)((unsigned long)context_ptr+0x00006158+4*13))=0x215b1490;
*((unsigned int *)((unsigned long)context_ptr+0x00006158+4*14))=0x00545e77;
*((unsigned int *)((unsigned long)context_ptr+0x00003570))=0x04c0003b;
*((unsigned int *)((unsigned long)context_ptr+0x00003570+4*1))=0x00006504;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000570))=0x03c0003b;
*((unsigned int *)((unsigned long)context_ptr+0x00000570+4*1))=0x00006158;
*((unsigned int *)((unsigned long)context_ptr+0x00000570+4*2))=0x00006340;
*((unsigned int *)((unsigned long)context_ptr+0x00000570+4*3))=0x0222003b;
*((unsigned int *)((unsigned long)context_ptr+0x00000570+4*4))=0x0040a086;
*((unsigned int *)((unsigned long)context_ptr+0x00000570+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000010e&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006360,"\x1b\x42\xb6\x9b\x6b\x28\xec\xc4\xaf\xd0\xc6\x1c\xc5\xd6\xbf\x7b\xaf\x19\xc3\x43\xc8\xa2\x82\x89\x13\x0a\x03\xc6\x23\x1f\x62\xfa\xe2\x50\xd1\x15\x64\x94\xfc\x0c\x69\xeb\x07\x99\x66\x00\x00\x00",45))
printf("strip: 1b42b69b6b28ecc4, Pass\n");
else
printf("strip: 1b42b69b6b28ecc4, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006540))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x00006540+4*1))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x00006540+4*2))=0x0106003c;
*((unsigned int *)((unsigned long)context_ptr+0x0000634c))=0xa0c3cf25;
*((unsigned int *)((unsigned long)context_ptr+0x0000634c+4*1))=0x52231231;
*((unsigned int *)((unsigned long)context_ptr+0x0000634c+4*2))=0x2957cf4a;
*((unsigned int *)((unsigned long)context_ptr+0x0000634c+4*3))=0x7fcdb4f9;
*((unsigned int *)((unsigned long)context_ptr+0x0000634c+4*4))=0x51719618;
*((unsigned int *)((unsigned long)context_ptr+0x0000634c+4*5))=0x5b455016;
*((unsigned int *)((unsigned long)context_ptr+0x0000634c+4*6))=0xc2601db6;
*((unsigned int *)((unsigned long)context_ptr+0x0000634c+4*7))=0x30dddb4f;
*((unsigned int *)((unsigned long)context_ptr+0x0000634c+4*8))=0x8e2ba3a6;
*((unsigned int *)((unsigned long)context_ptr+0x0000634c+4*9))=0xe5b63d79;
*((unsigned int *)((unsigned long)context_ptr+0x0000634c+4*10))=0x16601be5;
*((unsigned int *)((unsigned long)context_ptr+0x0000634c+4*11))=0x0eb4a976;
*((unsigned int *)((unsigned long)context_ptr+0x0000634c+4*12))=0x9bd5a11c;
*((unsigned int *)((unsigned long)context_ptr+0x0000634c+4*13))=0x37941418;
*((unsigned int *)((unsigned long)context_ptr+0x0000634c+4*14))=0xe6d34dbf;
*((unsigned int *)((unsigned long)context_ptr+0x00003588))=0x04c0003c;
*((unsigned int *)((unsigned long)context_ptr+0x00003588+4*1))=0x00006194;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000588))=0x03c0003c;
*((unsigned int *)((unsigned long)context_ptr+0x00000588+4*1))=0x0000634c;
*((unsigned int *)((unsigned long)context_ptr+0x00000588+4*2))=0x00006540;
*((unsigned int *)((unsigned long)context_ptr+0x00000588+4*3))=0x0222003c;
*((unsigned int *)((unsigned long)context_ptr+0x00000588+4*4))=0x00a8494a;
*((unsigned int *)((unsigned long)context_ptr+0x00000588+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000114&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006598,"\x49\x40\x67\x02\xa2\x0d\xc6\x11\x02\x48\xc5\xd5\x81\xf0\x1d\x55\xbd\x52\x25\x94\x10\x5f\x40\x54\x7c\x89\x15\x50\x62\x67\x7a\x6d\x12\x38\xa4\xd4\x82\x25\x12\x27\x62\x90\xaa\x86\x90\x5a\x00\x00",46))
printf("strip: 49406702a20dc611, Pass\n");
else
printf("strip: 49406702a20dc611, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000061d0))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x000061d0+4*1))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x000061d0+4*2))=0x0106003d;
*((unsigned int *)((unsigned long)context_ptr+0x0000654c))=0xcc8417a8;
*((unsigned int *)((unsigned long)context_ptr+0x0000654c+4*1))=0x590e75ff;
*((unsigned int *)((unsigned long)context_ptr+0x0000654c+4*2))=0xea10ed7f;
*((unsigned int *)((unsigned long)context_ptr+0x0000654c+4*3))=0x1ec01970;
*((unsigned int *)((unsigned long)context_ptr+0x0000654c+4*4))=0xa98c3c22;
*((unsigned int *)((unsigned long)context_ptr+0x0000654c+4*5))=0x7ba396dc;
*((unsigned int *)((unsigned long)context_ptr+0x0000654c+4*6))=0x4b45a981;
*((unsigned int *)((unsigned long)context_ptr+0x0000654c+4*7))=0x322e9f9f;
*((unsigned int *)((unsigned long)context_ptr+0x0000654c+4*8))=0x2c4fd58c;
*((unsigned int *)((unsigned long)context_ptr+0x0000654c+4*9))=0x9c87870c;
*((unsigned int *)((unsigned long)context_ptr+0x0000654c+4*10))=0x51dea88b;
*((unsigned int *)((unsigned long)context_ptr+0x0000654c+4*11))=0x7e543acb;
*((unsigned int *)((unsigned long)context_ptr+0x0000654c+4*12))=0xbd06bc85;
*((unsigned int *)((unsigned long)context_ptr+0x0000654c+4*13))=0x048f00ce;
*((unsigned int *)((unsigned long)context_ptr+0x0000654c+4*14))=0xe80edf23;
*((unsigned int *)((unsigned long)context_ptr+0x0000654c+4*15))=0x000000aa;
*((unsigned int *)((unsigned long)context_ptr+0x000035a0))=0x04c0003d;
*((unsigned int *)((unsigned long)context_ptr+0x000035a0+4*1))=0x0000674c;
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
*((unsigned int *)((unsigned long)context_ptr+0x000005a0))=0x03c0003d;
*((unsigned int *)((unsigned long)context_ptr+0x000005a0+4*1))=0x0000654c;
*((unsigned int *)((unsigned long)context_ptr+0x000005a0+4*2))=0x000061d0;
*((unsigned int *)((unsigned long)context_ptr+0x000005a0+4*3))=0x0222003d;
*((unsigned int *)((unsigned long)context_ptr+0x000005a0+4*4))=0x00a06d86;
*((unsigned int *)((unsigned long)context_ptr+0x000005a0+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000011a&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006390,"\x1c\x6f\x9e\x8b\x84\x1c\x0a\x5b\xf1\x2e\x44\x7b\xea\xf2\x00\xa5\x3c\xa7\xbe\xe3\xae\xd8\xc8\x29\x0b\xbd\x86\xff\x2a\x62\x49\xe0\x7b\xe9\xb5\xff\x99\xf9\x2c\x71\x94\xfa\x91\xdd\xa0\x83\x64\x00",47))
printf("strip: 1c6f9e8b841c0a5b, Pass\n");
else
printf("strip: 1c6f9e8b841c0a5b, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006008))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x00006008+4*1))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x00006008+4*2))=0x0106003e;
*((unsigned int *)((unsigned long)context_ptr+0x0000678c))=0xc66abce2;
*((unsigned int *)((unsigned long)context_ptr+0x0000678c+4*1))=0xe4eea210;
*((unsigned int *)((unsigned long)context_ptr+0x0000678c+4*2))=0xe24b4751;
*((unsigned int *)((unsigned long)context_ptr+0x0000678c+4*3))=0x44546957;
*((unsigned int *)((unsigned long)context_ptr+0x0000678c+4*4))=0x668871de;
*((unsigned int *)((unsigned long)context_ptr+0x0000678c+4*5))=0x47e56755;
*((unsigned int *)((unsigned long)context_ptr+0x0000678c+4*6))=0x77e836b2;
*((unsigned int *)((unsigned long)context_ptr+0x0000678c+4*7))=0xdbbd6d4c;
*((unsigned int *)((unsigned long)context_ptr+0x0000678c+4*8))=0x7af721d0;
*((unsigned int *)((unsigned long)context_ptr+0x0000678c+4*9))=0x31f02bf3;
*((unsigned int *)((unsigned long)context_ptr+0x0000678c+4*10))=0x29d745de;
*((unsigned int *)((unsigned long)context_ptr+0x0000678c+4*11))=0xef1fa9da;
*((unsigned int *)((unsigned long)context_ptr+0x0000678c+4*12))=0x0dd72f6f;
*((unsigned int *)((unsigned long)context_ptr+0x0000678c+4*13))=0xbf17bc09;
*((unsigned int *)((unsigned long)context_ptr+0x0000678c+4*14))=0x9023f018;
*((unsigned int *)((unsigned long)context_ptr+0x0000678c+4*15))=0x00005da5;
*((unsigned int *)((unsigned long)context_ptr+0x000035b8))=0x04c0003e;
*((unsigned int *)((unsigned long)context_ptr+0x000035b8+4*1))=0x000067cc;
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
*((unsigned int *)((unsigned long)context_ptr+0x000005b8))=0x03c0003e;
*((unsigned int *)((unsigned long)context_ptr+0x000005b8+4*1))=0x0000678c;
*((unsigned int *)((unsigned long)context_ptr+0x000005b8+4*2))=0x00006008;
*((unsigned int *)((unsigned long)context_ptr+0x000005b8+4*3))=0x0222003e;
*((unsigned int *)((unsigned long)context_ptr+0x000005b8+4*4))=0x00bb61ef;
*((unsigned int *)((unsigned long)context_ptr+0x000005b8+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000120&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000063f0,"\xb5\x1d\xec\x7a\xb1\x99\x9a\xb5\x16\x7f\x35\x63\x83\x5a\x68\xbb\x0b\xf4\x9a\x29\x8e\x14\x80\xb0\x6b\x50\xac\xef\xdf\x62\xdd\x1d\x0f\xfb\xc3\x9d\x8f\x4f\xe6\xda\x7b\x38\xad\xb9\xfe\xca\x17\xfd",48))
printf("strip: b51dec7ab1999ab5, Pass\n");
else
printf("strip: b51dec7ab1999ab5, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006014))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x00006014+4*1))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x00006014+4*2))=0x0106003f;
*((unsigned int *)((unsigned long)context_ptr+0x00006388))=0x7253ca44;
*((unsigned int *)((unsigned long)context_ptr+0x00006388+4*1))=0x65c18bb5;
*((unsigned int *)((unsigned long)context_ptr+0x00006388+4*2))=0xcde2570f;
*((unsigned int *)((unsigned long)context_ptr+0x00006388+4*3))=0x7b5496ed;
*((unsigned int *)((unsigned long)context_ptr+0x00006388+4*4))=0x0fdf3e7e;
*((unsigned int *)((unsigned long)context_ptr+0x00006388+4*5))=0xf18ffa54;
*((unsigned int *)((unsigned long)context_ptr+0x00006388+4*6))=0xdba0cf01;
*((unsigned int *)((unsigned long)context_ptr+0x00006388+4*7))=0xbe56ffbc;
*((unsigned int *)((unsigned long)context_ptr+0x00006388+4*8))=0xd1cab1d8;
*((unsigned int *)((unsigned long)context_ptr+0x00006388+4*9))=0x06674845;
*((unsigned int *)((unsigned long)context_ptr+0x00006388+4*10))=0xd121cfe7;
*((unsigned int *)((unsigned long)context_ptr+0x00006388+4*11))=0x717d9b54;
*((unsigned int *)((unsigned long)context_ptr+0x00006388+4*12))=0x066ae89b;
*((unsigned int *)((unsigned long)context_ptr+0x00006388+4*13))=0x28cef3d9;
*((unsigned int *)((unsigned long)context_ptr+0x00006388+4*14))=0xdeddc16b;
*((unsigned int *)((unsigned long)context_ptr+0x00006388+4*15))=0x0023a4ec;
*((unsigned int *)((unsigned long)context_ptr+0x000035d0))=0x04c0003f;
*((unsigned int *)((unsigned long)context_ptr+0x000035d0+4*1))=0x000063c8;
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
*((unsigned int *)((unsigned long)context_ptr+0x000005d0))=0x03c0003f;
*((unsigned int *)((unsigned long)context_ptr+0x000005d0+4*1))=0x00006388;
*((unsigned int *)((unsigned long)context_ptr+0x000005d0+4*2))=0x00006014;
*((unsigned int *)((unsigned long)context_ptr+0x000005d0+4*3))=0x0222003f;
*((unsigned int *)((unsigned long)context_ptr+0x000005d0+4*4))=0x00e41465;
*((unsigned int *)((unsigned long)context_ptr+0x000005d0+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000126&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000065c8,"\xf1\xec\x87\xdd\x32\x4b\xe8\x97\x39\x21\x3a\x7e\x4d\xbc\x45\x14\xe5\xa9\xf9\x2e\xde\x04\x89\x7a\x20\xd0\x45\xe5\xb3\xda\xdd\xca\xbc\x01\x24\x35\x93\x00\x20\x7c\x0a\x51\x38\x2c\x51\xe1\x3b\xa6\xbb\x00\x00\x00",49))
printf("strip: f1ec87dd324be897, Pass\n");
else
printf("strip: f1ec87dd324be897, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006020))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x00006020+4*1))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x00006020+4*2))=0x01060040;
*((unsigned int *)((unsigned long)context_ptr+0x000061dc))=0x84719743;
*((unsigned int *)((unsigned long)context_ptr+0x000061dc+4*1))=0x6edf09f8;
*((unsigned int *)((unsigned long)context_ptr+0x000061dc+4*2))=0x79bce0d8;
*((unsigned int *)((unsigned long)context_ptr+0x000061dc+4*3))=0xb6659885;
*((unsigned int *)((unsigned long)context_ptr+0x000061dc+4*4))=0x90f456da;
*((unsigned int *)((unsigned long)context_ptr+0x000061dc+4*5))=0x47b9294b;
*((unsigned int *)((unsigned long)context_ptr+0x000061dc+4*6))=0x605af2cf;
*((unsigned int *)((unsigned long)context_ptr+0x000061dc+4*7))=0xd3ff414d;
*((unsigned int *)((unsigned long)context_ptr+0x000061dc+4*8))=0xd2f307dd;
*((unsigned int *)((unsigned long)context_ptr+0x000061dc+4*9))=0x1369edd2;
*((unsigned int *)((unsigned long)context_ptr+0x000061dc+4*10))=0xbe378991;
*((unsigned int *)((unsigned long)context_ptr+0x000061dc+4*11))=0xc5cbb7fc;
*((unsigned int *)((unsigned long)context_ptr+0x000061dc+4*12))=0x9b9b28cf;
*((unsigned int *)((unsigned long)context_ptr+0x000061dc+4*13))=0x894270df;
*((unsigned int *)((unsigned long)context_ptr+0x000061dc+4*14))=0x300c047e;
*((unsigned int *)((unsigned long)context_ptr+0x000061dc+4*15))=0x9385a87e;
*((unsigned int *)((unsigned long)context_ptr+0x000035e8))=0x04c00040;
*((unsigned int *)((unsigned long)context_ptr+0x000035e8+4*1))=0x0000658c;
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
*((unsigned int *)((unsigned long)context_ptr+0x000005e8))=0x03c00040;
*((unsigned int *)((unsigned long)context_ptr+0x000005e8+4*1))=0x000061dc;
*((unsigned int *)((unsigned long)context_ptr+0x000005e8+4*2))=0x00006020;
*((unsigned int *)((unsigned long)context_ptr+0x000005e8+4*3))=0x02220040;
*((unsigned int *)((unsigned long)context_ptr+0x000005e8+4*4))=0x00eed5c0;
*((unsigned int *)((unsigned long)context_ptr+0x000005e8+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000012c&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006630,"\x75\x6c\xe5\x89\xc2\x2d\x11\x70\x53\x83\x58\xdc\xbc\x62\x20\xb5\x8a\x26\x08\x9d\x84\x93\x6a\x77\x64\x16\x89\x1f\xac\xbf\x2a\x33\x3d\x99\x68\xe3\x8c\x86\x37\x17\xec\x19\x21\x31\x93\xa3\x6e\x65\xa4\x43\x00\x00",50))
printf("strip: 756ce589c22d1170, Pass\n");
else
printf("strip: 756ce589c22d1170, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x0000602c))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x0000602c+4*1))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x0000602c+4*2))=0x01060041;
*((unsigned int *)((unsigned long)context_ptr+0x000065cc))=0x5a901958;
*((unsigned int *)((unsigned long)context_ptr+0x000065cc+4*1))=0xd198d6b9;
*((unsigned int *)((unsigned long)context_ptr+0x000065cc+4*2))=0x776e3b02;
*((unsigned int *)((unsigned long)context_ptr+0x000065cc+4*3))=0x89922cd0;
*((unsigned int *)((unsigned long)context_ptr+0x000065cc+4*4))=0x170b03a5;
*((unsigned int *)((unsigned long)context_ptr+0x000065cc+4*5))=0xa6bb9964;
*((unsigned int *)((unsigned long)context_ptr+0x000065cc+4*6))=0xd064dd1b;
*((unsigned int *)((unsigned long)context_ptr+0x000065cc+4*7))=0xa1ab612b;
*((unsigned int *)((unsigned long)context_ptr+0x000065cc+4*8))=0x98cfec84;
*((unsigned int *)((unsigned long)context_ptr+0x000065cc+4*9))=0xa1836aad;
*((unsigned int *)((unsigned long)context_ptr+0x000065cc+4*10))=0x2f7533d6;
*((unsigned int *)((unsigned long)context_ptr+0x000065cc+4*11))=0xc11e0932;
*((unsigned int *)((unsigned long)context_ptr+0x000065cc+4*12))=0x93244e54;
*((unsigned int *)((unsigned long)context_ptr+0x000065cc+4*13))=0xce610e6a;
*((unsigned int *)((unsigned long)context_ptr+0x000065cc+4*14))=0x7fdbf9c1;
*((unsigned int *)((unsigned long)context_ptr+0x000065cc+4*15))=0x6368c9ca;
*((unsigned int *)((unsigned long)context_ptr+0x00006038))=0x0000008f;
*((unsigned int *)((unsigned long)context_ptr+0x00003600))=0x04c00041;
*((unsigned int *)((unsigned long)context_ptr+0x00003600+4*1))=0x0000660c;
*((unsigned int *)((unsigned long)context_ptr+0x00003600+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003600+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003600+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003600+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005f4&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000600))=0x03800040;
*((unsigned int *)((unsigned long)context_ptr+0x00000600+4*1))=0x000065cc;
*((unsigned int *)((unsigned long)context_ptr+0x00000600+4*2))=0x0000602c;
*((unsigned int *)((unsigned long)context_ptr+0x00000600+4*3))=0x02220041;
*((unsigned int *)((unsigned long)context_ptr+0x00000600+4*4))=0x008b9d2b;
*((unsigned int *)((unsigned long)context_ptr+0x00000600+4*5))=0x00006000+(unsigned long)context_ptr;
*((unsigned int *)((unsigned long)context_ptr+0x00000618))=0x00400001;
*((unsigned int *)((unsigned long)context_ptr+0x00000618+4*1))=0x00006038;
*((unsigned int *)((unsigned long)context_ptr+0x00000618+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00000618+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00000618+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00000618+4*5))=0x77777777+(unsigned long)context_ptr;
writel(0x00000030&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000132&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006420,"\xd5\x4a\x54\xb8\xaa\xb6\xe0\x16\x1f\x7f\x9c\xa7\x3a\x22\xeb\x3d\x04\x48\x84\xa2\xbd\x25\x82\x51\xb9\x5c\xcf\x31\xfe\x85\x6c\xb9\x60\x09\x70\x49\xa9\x86\xd4\x7d\x27\x26\x92\x43\x36\xf1\x23\xea\x89\xef\xd6\x00",51))
printf("strip: d54a54b8aab6e016, Pass\n");
else
printf("strip: d54a54b8aab6e016, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x0000603c))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x0000603c+4*1))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x0000603c+4*2))=0x01060042;
*((unsigned int *)((unsigned long)context_ptr+0x00006408))=0x8bca87a3;
*((unsigned int *)((unsigned long)context_ptr+0x00006408+4*1))=0x0b5dc341;
*((unsigned int *)((unsigned long)context_ptr+0x00006408+4*2))=0xc79c7137;
*((unsigned int *)((unsigned long)context_ptr+0x00006408+4*3))=0x96c0c6dc;
*((unsigned int *)((unsigned long)context_ptr+0x00006408+4*4))=0x44b1aa31;
*((unsigned int *)((unsigned long)context_ptr+0x00006408+4*5))=0xb2fe4b5f;
*((unsigned int *)((unsigned long)context_ptr+0x00006408+4*6))=0x3d57315b;
*((unsigned int *)((unsigned long)context_ptr+0x00006408+4*7))=0x886030d4;
*((unsigned int *)((unsigned long)context_ptr+0x00006408+4*8))=0xe7f62b40;
*((unsigned int *)((unsigned long)context_ptr+0x00006408+4*9))=0x6f0b8806;
*((unsigned int *)((unsigned long)context_ptr+0x00006408+4*10))=0x4c33cd1c;
*((unsigned int *)((unsigned long)context_ptr+0x00006408+4*11))=0x6c80f715;
*((unsigned int *)((unsigned long)context_ptr+0x00006408+4*12))=0x49cc2d8d;
*((unsigned int *)((unsigned long)context_ptr+0x00006408+4*13))=0x7c4bbdd8;
*((unsigned int *)((unsigned long)context_ptr+0x00006408+4*14))=0x89d9f04b;
*((unsigned int *)((unsigned long)context_ptr+0x00006408+4*15))=0x5bcc13b0;
*((unsigned int *)((unsigned long)context_ptr+0x00006048))=0x00005344;
*((unsigned int *)((unsigned long)context_ptr+0x00003618))=0x04c00042;
*((unsigned int *)((unsigned long)context_ptr+0x00003618+4*1))=0x0000621c;
*((unsigned int *)((unsigned long)context_ptr+0x00003618+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003618+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003618+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003618+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005f4&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000630))=0x03800040;
*((unsigned int *)((unsigned long)context_ptr+0x00000630+4*1))=0x00006408;
*((unsigned int *)((unsigned long)context_ptr+0x00000630+4*2))=0x0000603c;
*((unsigned int *)((unsigned long)context_ptr+0x00000630+4*3))=0x02220042;
*((unsigned int *)((unsigned long)context_ptr+0x00000630+4*4))=0x00eb4194;
*((unsigned int *)((unsigned long)context_ptr+0x00000630+4*5))=0x00006000+(unsigned long)context_ptr;
*((unsigned int *)((unsigned long)context_ptr+0x00000648))=0x00400002;
*((unsigned int *)((unsigned long)context_ptr+0x00000648+4*1))=0x00006048;
*((unsigned int *)((unsigned long)context_ptr+0x00000648+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00000648+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00000648+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00000648+4*5))=0x77777777+(unsigned long)context_ptr;
writel(0x00000030&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000138&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006454,"\x29\xa0\xad\x94\xba\x84\xf4\xa6\xa0\x03\x24\x99\xc4\x24\xa3\x27\xc3\xd2\x9e\x11\x47\x45\x77\xc7\x94\xfd\xb5\x24\xfa\x0f\x55\xa3\x63\x05\x4b\x3d\xc6\x97\x24\xdf\x36\x51\xdf\xc3\x6b\x84\xfa\xb5\xb7\xa7\xfc\xec",52))
printf("strip: 29a0ad94ba84f4a6, Pass\n");
else
printf("strip: 29a0ad94ba84f4a6, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x0000604c))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x0000604c+4*1))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x0000604c+4*2))=0x01060043;
*((unsigned int *)((unsigned long)context_ptr+0x00006448))=0x641c1197;
*((unsigned int *)((unsigned long)context_ptr+0x00006448+4*1))=0xf2f11b4a;
*((unsigned int *)((unsigned long)context_ptr+0x00006448+4*2))=0x90e8faf6;
*((unsigned int *)((unsigned long)context_ptr+0x00006448+4*3))=0x3a86bd67;
*((unsigned int *)((unsigned long)context_ptr+0x00006448+4*4))=0xf3a629c6;
*((unsigned int *)((unsigned long)context_ptr+0x00006448+4*5))=0x825b2589;
*((unsigned int *)((unsigned long)context_ptr+0x00006448+4*6))=0xe199266e;
*((unsigned int *)((unsigned long)context_ptr+0x00006448+4*7))=0x05a82ef8;
*((unsigned int *)((unsigned long)context_ptr+0x00006448+4*8))=0x3f9b8326;
*((unsigned int *)((unsigned long)context_ptr+0x00006448+4*9))=0x1af8e4bc;
*((unsigned int *)((unsigned long)context_ptr+0x00006448+4*10))=0xeeb285ae;
*((unsigned int *)((unsigned long)context_ptr+0x00006448+4*11))=0x0a17e149;
*((unsigned int *)((unsigned long)context_ptr+0x00006448+4*12))=0x38b542ec;
*((unsigned int *)((unsigned long)context_ptr+0x00006448+4*13))=0xbeb95796;
*((unsigned int *)((unsigned long)context_ptr+0x00006448+4*14))=0x2073cde6;
*((unsigned int *)((unsigned long)context_ptr+0x00006448+4*15))=0xfcb570ab;
*((unsigned int *)((unsigned long)context_ptr+0x00006058))=0x00577155;
*((unsigned int *)((unsigned long)context_ptr+0x00003630))=0x04c00043;
*((unsigned int *)((unsigned long)context_ptr+0x00003630+4*1))=0x00006260;
*((unsigned int *)((unsigned long)context_ptr+0x00003630+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003630+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003630+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003630+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005f4&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000660))=0x03800040;
*((unsigned int *)((unsigned long)context_ptr+0x00000660+4*1))=0x00006448;
*((unsigned int *)((unsigned long)context_ptr+0x00000660+4*2))=0x0000604c;
*((unsigned int *)((unsigned long)context_ptr+0x00000660+4*3))=0x02220043;
*((unsigned int *)((unsigned long)context_ptr+0x00000660+4*4))=0x0076ad2c;
*((unsigned int *)((unsigned long)context_ptr+0x00000660+4*5))=0x00006000+(unsigned long)context_ptr;
*((unsigned int *)((unsigned long)context_ptr+0x00000678))=0x00400003;
*((unsigned int *)((unsigned long)context_ptr+0x00000678+4*1))=0x00006058;
*((unsigned int *)((unsigned long)context_ptr+0x00000678+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00000678+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00000678+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00000678+4*5))=0x77777777+(unsigned long)context_ptr;
writel(0x00000030&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000013e&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006664,"\x9c\x91\x84\x29\x01\x1b\x62\x41\x7c\x78\x83\x21\x7f\xf3\x2c\x03\x56\xb5\xdc\x1b\x07\x4f\x9f\xeb\x54\xc7\x20\xa4\x3f\xc2\xe9\x71\xaf\x5a\xd9\x68\x95\xfc\x8e\x73\x18\xf3\x86\xb3\xa7\x3c\xa3\x18\x0e\xd7\x99\x4d\x86\x00\x00\x00",53))
printf("strip: 9c918429011b6241, Pass\n");
else
printf("strip: 9c918429011b6241, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000062a4))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x000062a4+4*1))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x000062a4+4*2))=0x01060044;
*((unsigned int *)((unsigned long)context_ptr+0x00006650))=0xe90cd524;
*((unsigned int *)((unsigned long)context_ptr+0x00006650+4*1))=0x3ea7324a;
*((unsigned int *)((unsigned long)context_ptr+0x00006650+4*2))=0x51aac390;
*((unsigned int *)((unsigned long)context_ptr+0x00006650+4*3))=0x7505a0a2;
*((unsigned int *)((unsigned long)context_ptr+0x00006650+4*4))=0xe92961a1;
*((unsigned int *)((unsigned long)context_ptr+0x00006650+4*5))=0xfd2add02;
*((unsigned int *)((unsigned long)context_ptr+0x00006650+4*6))=0xaac417e9;
*((unsigned int *)((unsigned long)context_ptr+0x00006650+4*7))=0xca4f7fdd;
*((unsigned int *)((unsigned long)context_ptr+0x00006650+4*8))=0xc4fc89bc;
*((unsigned int *)((unsigned long)context_ptr+0x00006650+4*9))=0xd781ed7f;
*((unsigned int *)((unsigned long)context_ptr+0x00006650+4*10))=0x3b36210c;
*((unsigned int *)((unsigned long)context_ptr+0x00006650+4*11))=0x978f0a23;
*((unsigned int *)((unsigned long)context_ptr+0x00006650+4*12))=0x73749db9;
*((unsigned int *)((unsigned long)context_ptr+0x00006650+4*13))=0xa0a29d03;
*((unsigned int *)((unsigned long)context_ptr+0x00006650+4*14))=0x9c35b4f6;
*((unsigned int *)((unsigned long)context_ptr+0x00006650+4*15))=0xc198ac8d;
*((unsigned int *)((unsigned long)context_ptr+0x000062b0))=0x43ec9175;
*((unsigned int *)((unsigned long)context_ptr+0x00003648))=0x04c00044;
*((unsigned int *)((unsigned long)context_ptr+0x00003648+4*1))=0x0000680c;
*((unsigned int *)((unsigned long)context_ptr+0x00003648+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003648+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003648+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003648+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005f4&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000690))=0x03800040;
*((unsigned int *)((unsigned long)context_ptr+0x00000690+4*1))=0x00006650;
*((unsigned int *)((unsigned long)context_ptr+0x00000690+4*2))=0x000062a4;
*((unsigned int *)((unsigned long)context_ptr+0x00000690+4*3))=0x02220044;
*((unsigned int *)((unsigned long)context_ptr+0x00000690+4*4))=0x005cae12;
*((unsigned int *)((unsigned long)context_ptr+0x00000690+4*5))=0x00006000+(unsigned long)context_ptr;
*((unsigned int *)((unsigned long)context_ptr+0x000006a8))=0x00400004;
*((unsigned int *)((unsigned long)context_ptr+0x000006a8+4*1))=0x000062b0;
*((unsigned int *)((unsigned long)context_ptr+0x000006a8+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000006a8+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000006a8+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000006a8+4*5))=0x77777777+(unsigned long)context_ptr;
writel(0x00000030&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000144&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006488,"\xb9\x4f\x1d\xc7\xe3\x1a\x9d\xbd\x3e\xd6\xaf\x71\x2a\x42\xd4\x2a\xb4\x92\x8f\x04\x1f\x4f\xa1\x61\x41\x62\x76\x98\x8f\x5e\x6c\xce\x96\xf8\x9a\x48\x83\x79\xda\xbc\xe1\xb7\x40\x45\x29\xe1\xe6\x52\x05\x79\xc9\xb3\xac\x05\x00\x00",54))
printf("strip: b94f1dc7e31a9dbd, Pass\n");
else
printf("strip: b94f1dc7e31a9dbd, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006690))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x00006690+4*1))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x00006690+4*2))=0x01060045;
*((unsigned int *)((unsigned long)context_ptr+0x0000605c))=0x9654fed7;
*((unsigned int *)((unsigned long)context_ptr+0x0000605c+4*1))=0xefaa928e;
*((unsigned int *)((unsigned long)context_ptr+0x0000605c+4*2))=0x84764f04;
*((unsigned int *)((unsigned long)context_ptr+0x0000605c+4*3))=0xdb3c7fe8;
*((unsigned int *)((unsigned long)context_ptr+0x0000605c+4*4))=0xf143c883;
*((unsigned int *)((unsigned long)context_ptr+0x0000605c+4*5))=0x547a7266;
*((unsigned int *)((unsigned long)context_ptr+0x0000605c+4*6))=0x999a93c2;
*((unsigned int *)((unsigned long)context_ptr+0x0000605c+4*7))=0x6217574b;
*((unsigned int *)((unsigned long)context_ptr+0x0000605c+4*8))=0xaf9f5943;
*((unsigned int *)((unsigned long)context_ptr+0x0000605c+4*9))=0xf72e38bf;
*((unsigned int *)((unsigned long)context_ptr+0x0000605c+4*10))=0xaf157977;
*((unsigned int *)((unsigned long)context_ptr+0x0000605c+4*11))=0xf7400d2c;
*((unsigned int *)((unsigned long)context_ptr+0x0000605c+4*12))=0x2cab0e55;
*((unsigned int *)((unsigned long)context_ptr+0x0000605c+4*13))=0x4d8a7948;
*((unsigned int *)((unsigned long)context_ptr+0x0000605c+4*14))=0x13a0c2ec;
*((unsigned int *)((unsigned long)context_ptr+0x0000605c+4*15))=0xd4ced4d1;
*((unsigned int *)((unsigned long)context_ptr+0x000062b4))=0x434be62c;
*((unsigned int *)((unsigned long)context_ptr+0x000062b4+4*1))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x00003660))=0x04c00045;
*((unsigned int *)((unsigned long)context_ptr+0x00003660+4*1))=0x00006850;
*((unsigned int *)((unsigned long)context_ptr+0x00003660+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003660+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003660+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003660+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005f4&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x000006c0))=0x03800040;
*((unsigned int *)((unsigned long)context_ptr+0x000006c0+4*1))=0x0000605c;
*((unsigned int *)((unsigned long)context_ptr+0x000006c0+4*2))=0x00006690;
*((unsigned int *)((unsigned long)context_ptr+0x000006c0+4*3))=0x02220045;
*((unsigned int *)((unsigned long)context_ptr+0x000006c0+4*4))=0x0092c47c;
*((unsigned int *)((unsigned long)context_ptr+0x000006c0+4*5))=0x00006000+(unsigned long)context_ptr;
*((unsigned int *)((unsigned long)context_ptr+0x000006d8))=0x00400005;
*((unsigned int *)((unsigned long)context_ptr+0x000006d8+4*1))=0x000062b4;
*((unsigned int *)((unsigned long)context_ptr+0x000006d8+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000006d8+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000006d8+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000006d8+4*5))=0x77777777+(unsigned long)context_ptr;
writel(0x00000030&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000014a&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x0000669c,"\xfd\xa8\xb8\xb1\xf0\x67\x47\x14\x05\x7a\xbe\xbd\x00\x9d\xd4\xdd\xc5\x6b\xb4\xb3\x10\x09\x58\xa4\x61\xa5\xc2\xc5\x48\xf8\x8d\xa0\xa2\xac\x27\xac\x6e\xf7\xb6\xf9\xfd\xd5\x96\x99\x78\x5e\x6b\xe9\xa5\x2b\x09\x70\x70\x10\x3a\x00",55))
printf("strip: fda8b8b1f0674714, Pass\n");
else
printf("strip: fda8b8b1f0674714, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x0000669c))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x0000669c+4*1))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x0000669c+4*2))=0x01060046;
*((unsigned int *)((unsigned long)context_ptr+0x00006488))=0x23438fbc;
*((unsigned int *)((unsigned long)context_ptr+0x00006488+4*1))=0xd3a96c02;
*((unsigned int *)((unsigned long)context_ptr+0x00006488+4*2))=0x567b1148;
*((unsigned int *)((unsigned long)context_ptr+0x00006488+4*3))=0x71850c55;
*((unsigned int *)((unsigned long)context_ptr+0x00006488+4*4))=0x0a61adb5;
*((unsigned int *)((unsigned long)context_ptr+0x00006488+4*5))=0x8fbd33f8;
*((unsigned int *)((unsigned long)context_ptr+0x00006488+4*6))=0x26f8bb07;
*((unsigned int *)((unsigned long)context_ptr+0x00006488+4*7))=0x6e8a92b7;
*((unsigned int *)((unsigned long)context_ptr+0x00006488+4*8))=0xac5c2c72;
*((unsigned int *)((unsigned long)context_ptr+0x00006488+4*9))=0x3aa0bcd9;
*((unsigned int *)((unsigned long)context_ptr+0x00006488+4*10))=0xf2c4db01;
*((unsigned int *)((unsigned long)context_ptr+0x00006488+4*11))=0x9054f922;
*((unsigned int *)((unsigned long)context_ptr+0x00006488+4*12))=0xf2efcb04;
*((unsigned int *)((unsigned long)context_ptr+0x00006488+4*13))=0x688c2327;
*((unsigned int *)((unsigned long)context_ptr+0x00006488+4*14))=0xc3c74904;
*((unsigned int *)((unsigned long)context_ptr+0x00006488+4*15))=0xc55eeb3c;
*((unsigned int *)((unsigned long)context_ptr+0x000066a8))=0x5eadfc57;
*((unsigned int *)((unsigned long)context_ptr+0x000066a8+4*1))=0x00003010;
*((unsigned int *)((unsigned long)context_ptr+0x00003678))=0x04c00046;
*((unsigned int *)((unsigned long)context_ptr+0x00003678+4*1))=0x0000609c;
*((unsigned int *)((unsigned long)context_ptr+0x00003678+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003678+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003678+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003678+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005f4&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x000006f0))=0x03800040;
*((unsigned int *)((unsigned long)context_ptr+0x000006f0+4*1))=0x00006488;
*((unsigned int *)((unsigned long)context_ptr+0x000006f0+4*2))=0x0000669c;
*((unsigned int *)((unsigned long)context_ptr+0x000006f0+4*3))=0x02220046;
*((unsigned int *)((unsigned long)context_ptr+0x000006f0+4*4))=0x00dfc753;
*((unsigned int *)((unsigned long)context_ptr+0x000006f0+4*5))=0x00006000+(unsigned long)context_ptr;
*((unsigned int *)((unsigned long)context_ptr+0x00000708))=0x00400006;
*((unsigned int *)((unsigned long)context_ptr+0x00000708+4*1))=0x000066a8;
*((unsigned int *)((unsigned long)context_ptr+0x00000708+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00000708+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00000708+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00000708+4*5))=0x77777777+(unsigned long)context_ptr;
writel(0x00000030&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000150&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000062c0,"\x6e\x4a\x70\xf5\x09\x7a\xe5\x1b\x1d\xd0\x48\xcc\x4d\x08\xd1\x54\x76\x0f\xa6\xd4\x38\xee\xa2\x8c\x34\xe0\x6c\x0a\xec\x5e\x4b\x0e\x08\x0b\xdf\xde\x78\x14\x23\xf2\x8f\xcb\x13\x10\xc6\x1d\xd2\xef\x6e\x1d\xb7\x72\x80\xe3\x8a\x23",56))
printf("strip: 6e4a70f5097ae51b, Pass\n");
else
printf("strip: 6e4a70f5097ae51b, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000066b0))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x000066b0+4*1))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x000066b0+4*2))=0x01060047;
*((unsigned int *)((unsigned long)context_ptr+0x00006898))=0x26186b2f;
*((unsigned int *)((unsigned long)context_ptr+0x00006898+4*1))=0x14722ddb;
*((unsigned int *)((unsigned long)context_ptr+0x00006898+4*2))=0xd1a944cb;
*((unsigned int *)((unsigned long)context_ptr+0x00006898+4*3))=0x75283469;
*((unsigned int *)((unsigned long)context_ptr+0x00006898+4*4))=0x3e96a898;
*((unsigned int *)((unsigned long)context_ptr+0x00006898+4*5))=0xf8702200;
*((unsigned int *)((unsigned long)context_ptr+0x00006898+4*6))=0xfed7fa91;
*((unsigned int *)((unsigned long)context_ptr+0x00006898+4*7))=0xde6eb04a;
*((unsigned int *)((unsigned long)context_ptr+0x00006898+4*8))=0xd7f1679d;
*((unsigned int *)((unsigned long)context_ptr+0x00006898+4*9))=0x67676c7e;
*((unsigned int *)((unsigned long)context_ptr+0x00006898+4*10))=0x1fd42a4f;
*((unsigned int *)((unsigned long)context_ptr+0x00006898+4*11))=0x3ade289f;
*((unsigned int *)((unsigned long)context_ptr+0x00006898+4*12))=0xc9e70420;
*((unsigned int *)((unsigned long)context_ptr+0x00006898+4*13))=0x3882dd50;
*((unsigned int *)((unsigned long)context_ptr+0x00006898+4*14))=0x45b20791;
*((unsigned int *)((unsigned long)context_ptr+0x00006898+4*15))=0xf59fdc5f;
*((unsigned int *)((unsigned long)context_ptr+0x000066bc))=0x9bda013a;
*((unsigned int *)((unsigned long)context_ptr+0x000066bc+4*1))=0x00f24022;
*((unsigned int *)((unsigned long)context_ptr+0x00003690))=0x04c00047;
*((unsigned int *)((unsigned long)context_ptr+0x00003690+4*1))=0x000068d8;
*((unsigned int *)((unsigned long)context_ptr+0x00003690+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003690+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003690+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003690+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005f4&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000720))=0x03800040;
*((unsigned int *)((unsigned long)context_ptr+0x00000720+4*1))=0x00006898;
*((unsigned int *)((unsigned long)context_ptr+0x00000720+4*2))=0x000066b0;
*((unsigned int *)((unsigned long)context_ptr+0x00000720+4*3))=0x02220047;
*((unsigned int *)((unsigned long)context_ptr+0x00000720+4*4))=0x00367a12;
*((unsigned int *)((unsigned long)context_ptr+0x00000720+4*5))=0x00006000+(unsigned long)context_ptr;
*((unsigned int *)((unsigned long)context_ptr+0x00000738))=0x00400007;
*((unsigned int *)((unsigned long)context_ptr+0x00000738+4*1))=0x000066bc;
*((unsigned int *)((unsigned long)context_ptr+0x00000738+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00000738+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00000738+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00000738+4*5))=0x77777777+(unsigned long)context_ptr;
writel(0x00000030&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000156&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000066d4,"\x3d\xb1\x27\x67\xc7\x5d\x48\x5a\x5f\x02\x24\xbd\xb1\xa7\x23\x1d\x7d\x7b\x20\xf7\xd1\xdf\x2c\xa8\xd0\x52\xfc\x18\xcb\x25\x40\x30\x1d\xab\x3e\xcc\xc4\xf5\xc6\xfd\x8e\x08\x54\x64\xf7\x6b\x45\xcc\xeb\x0b\xfb\xb9\xfe\xa6\x01\xad\x3a\x00\x00\x00",57))
printf("strip: 3db12767c75d485a, Pass\n");
else
printf("strip: 3db12767c75d485a, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000060e4))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x000060e4+4*1))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x000060e4+4*2))=0x01060048;
*((unsigned int *)((unsigned long)context_ptr+0x000066c4))=0x4acc58d3;
*((unsigned int *)((unsigned long)context_ptr+0x000066c4+4*1))=0x3dff657f;
*((unsigned int *)((unsigned long)context_ptr+0x000066c4+4*2))=0xb1f2ced7;
*((unsigned int *)((unsigned long)context_ptr+0x000066c4+4*3))=0xe809f17f;
*((unsigned int *)((unsigned long)context_ptr+0x000066c4+4*4))=0xdd4a33bd;
*((unsigned int *)((unsigned long)context_ptr+0x000066c4+4*5))=0x3526451a;
*((unsigned int *)((unsigned long)context_ptr+0x000066c4+4*6))=0x97df5821;
*((unsigned int *)((unsigned long)context_ptr+0x000066c4+4*7))=0x40ff1a28;
*((unsigned int *)((unsigned long)context_ptr+0x000066c4+4*8))=0xf1472f49;
*((unsigned int *)((unsigned long)context_ptr+0x000066c4+4*9))=0x9855695f;
*((unsigned int *)((unsigned long)context_ptr+0x000066c4+4*10))=0x8e1b4286;
*((unsigned int *)((unsigned long)context_ptr+0x000066c4+4*11))=0x6c570e8e;
*((unsigned int *)((unsigned long)context_ptr+0x000066c4+4*12))=0xcdab517b;
*((unsigned int *)((unsigned long)context_ptr+0x000066c4+4*13))=0x97aa6b1e;
*((unsigned int *)((unsigned long)context_ptr+0x000066c4+4*14))=0xe38bdedf;
*((unsigned int *)((unsigned long)context_ptr+0x000066c4+4*15))=0x620226ce;
*((unsigned int *)((unsigned long)context_ptr+0x00006704))=0x84cf075d;
*((unsigned int *)((unsigned long)context_ptr+0x00006704+4*1))=0x66ced5f9;
*((unsigned int *)((unsigned long)context_ptr+0x000036a8))=0x04c00048;
*((unsigned int *)((unsigned long)context_ptr+0x000036a8+4*1))=0x000062bc;
*((unsigned int *)((unsigned long)context_ptr+0x000036a8+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000036a8+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000036a8+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000036a8+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005f4&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000750))=0x03800040;
*((unsigned int *)((unsigned long)context_ptr+0x00000750+4*1))=0x000066c4;
*((unsigned int *)((unsigned long)context_ptr+0x00000750+4*2))=0x000060e4;
*((unsigned int *)((unsigned long)context_ptr+0x00000750+4*3))=0x02220048;
*((unsigned int *)((unsigned long)context_ptr+0x00000750+4*4))=0x00e6bac2;
*((unsigned int *)((unsigned long)context_ptr+0x00000750+4*5))=0x00006000+(unsigned long)context_ptr;
*((unsigned int *)((unsigned long)context_ptr+0x00000768))=0x00400008;
*((unsigned int *)((unsigned long)context_ptr+0x00000768+4*1))=0x00006704;
*((unsigned int *)((unsigned long)context_ptr+0x00000768+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00000768+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00000768+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00000768+4*5))=0x77777777+(unsigned long)context_ptr;
writel(0x00000030&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000015c&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006710,"\x07\x9b\x54\xe3\x3b\x8c\x32\xf7\xa4\xc0\xe4\x74\x8b\x73\x9e\x55\xd2\x5d\xc5\x04\x5d\x7a\xe6\xb8\xbb\xa2\xe6\xb9\xa1\xeb\xc3\x03\xde\x30\xbf\x69\x64\x27\x6d\xff\xd3\xbc\xa4\x36\x10\xee\xe8\x00\xe9\xbf\x19\x27\x2d\x41\xe7\x6b\x89\x6c\x00\x00",58))
printf("strip: 079b54e33b8c32f7, Pass\n");
else
printf("strip: 079b54e33b8c32f7, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006304))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x00006304+4*1))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x00006304+4*2))=0x01060049;
*((unsigned int *)((unsigned long)context_ptr+0x0000670c))=0x23c1ef17;
*((unsigned int *)((unsigned long)context_ptr+0x0000670c+4*1))=0x37f9a83c;
*((unsigned int *)((unsigned long)context_ptr+0x0000670c+4*2))=0x02db6fd9;
*((unsigned int *)((unsigned long)context_ptr+0x0000670c+4*3))=0xf6c96b85;
*((unsigned int *)((unsigned long)context_ptr+0x0000670c+4*4))=0xe15cc01a;
*((unsigned int *)((unsigned long)context_ptr+0x0000670c+4*5))=0x7f82ffdd;
*((unsigned int *)((unsigned long)context_ptr+0x0000670c+4*6))=0x1be70d36;
*((unsigned int *)((unsigned long)context_ptr+0x0000670c+4*7))=0x5309196e;
*((unsigned int *)((unsigned long)context_ptr+0x0000670c+4*8))=0x3dfe481d;
*((unsigned int *)((unsigned long)context_ptr+0x0000670c+4*9))=0x6410c9c9;
*((unsigned int *)((unsigned long)context_ptr+0x0000670c+4*10))=0x23215326;
*((unsigned int *)((unsigned long)context_ptr+0x0000670c+4*11))=0x8d7a0db6;
*((unsigned int *)((unsigned long)context_ptr+0x0000670c+4*12))=0x189f3f6c;
*((unsigned int *)((unsigned long)context_ptr+0x0000670c+4*13))=0x33724b2c;
*((unsigned int *)((unsigned long)context_ptr+0x0000670c+4*14))=0xce7a43a6;
*((unsigned int *)((unsigned long)context_ptr+0x0000670c+4*15))=0x67d59aab;
*((unsigned int *)((unsigned long)context_ptr+0x00006310))=0x9821636e;
*((unsigned int *)((unsigned long)context_ptr+0x00006310+4*1))=0x589bcc7d;
*((unsigned int *)((unsigned long)context_ptr+0x00006310+4*2))=0x000000db;
*((unsigned int *)((unsigned long)context_ptr+0x000036c0))=0x04c00049;
*((unsigned int *)((unsigned long)context_ptr+0x000036c0+4*1))=0x000060f0;
*((unsigned int *)((unsigned long)context_ptr+0x000036c0+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000036c0+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000036c0+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000036c0+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005f4&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000780))=0x03800040;
*((unsigned int *)((unsigned long)context_ptr+0x00000780+4*1))=0x0000670c;
*((unsigned int *)((unsigned long)context_ptr+0x00000780+4*2))=0x00006304;
*((unsigned int *)((unsigned long)context_ptr+0x00000780+4*3))=0x02220049;
*((unsigned int *)((unsigned long)context_ptr+0x00000780+4*4))=0x008dc73e;
*((unsigned int *)((unsigned long)context_ptr+0x00000780+4*5))=0x00006000+(unsigned long)context_ptr;
*((unsigned int *)((unsigned long)context_ptr+0x00000798))=0x00400009;
*((unsigned int *)((unsigned long)context_ptr+0x00000798+4*1))=0x00006310;
*((unsigned int *)((unsigned long)context_ptr+0x00000798+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00000798+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00000798+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00000798+4*5))=0x77777777+(unsigned long)context_ptr;
writel(0x00000030&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000162&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006504,"\x15\xcc\xb6\x06\x7e\xcf\xf2\x59\x78\x71\xbe\xb4\x79\x2f\x96\x06\x5b\x4e\x11\x18\xc9\x74\x20\xef\x50\x70\xb1\x27\xc8\xd8\x7d\xb5\xb9\xfd\xc6\x5c\x82\x64\x88\xe5\x18\xe4\x81\x25\xef\x31\x06\x78\x92\x0c\xa0\x90\x90\x14\x5b\x21\x77\x5e\x54\x00",59))
printf("strip: 15ccb6067ecff259, Pass\n");
else
printf("strip: 15ccb6067ecff259, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x0000631c))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x0000631c+4*1))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x0000631c+4*2))=0x0106004a;
*((unsigned int *)((unsigned long)context_ptr+0x0000613c))=0xa4739f68;
*((unsigned int *)((unsigned long)context_ptr+0x0000613c+4*1))=0xcb6b61e6;
*((unsigned int *)((unsigned long)context_ptr+0x0000613c+4*2))=0xa70f560b;
*((unsigned int *)((unsigned long)context_ptr+0x0000613c+4*3))=0xbe9ea9ac;
*((unsigned int *)((unsigned long)context_ptr+0x0000613c+4*4))=0xd5a1a103;
*((unsigned int *)((unsigned long)context_ptr+0x0000613c+4*5))=0x699708c1;
*((unsigned int *)((unsigned long)context_ptr+0x0000613c+4*6))=0x271f1b47;
*((unsigned int *)((unsigned long)context_ptr+0x0000613c+4*7))=0x429a7b3d;
*((unsigned int *)((unsigned long)context_ptr+0x0000613c+4*8))=0x137c8534;
*((unsigned int *)((unsigned long)context_ptr+0x0000613c+4*9))=0x75ef643a;
*((unsigned int *)((unsigned long)context_ptr+0x0000613c+4*10))=0x27ffdf3f;
*((unsigned int *)((unsigned long)context_ptr+0x0000613c+4*11))=0xcf417ddf;
*((unsigned int *)((unsigned long)context_ptr+0x0000613c+4*12))=0x63b28d8c;
*((unsigned int *)((unsigned long)context_ptr+0x0000613c+4*13))=0x0ccfbdb3;
*((unsigned int *)((unsigned long)context_ptr+0x0000613c+4*14))=0x98aa954e;
*((unsigned int *)((unsigned long)context_ptr+0x0000613c+4*15))=0x88a355cd;
*((unsigned int *)((unsigned long)context_ptr+0x0000617c))=0x3c884cd7;
*((unsigned int *)((unsigned long)context_ptr+0x0000617c+4*1))=0xdc4df6ec;
*((unsigned int *)((unsigned long)context_ptr+0x0000617c+4*2))=0x00004a6f;
*((unsigned int *)((unsigned long)context_ptr+0x000036d8))=0x04c0004a;
*((unsigned int *)((unsigned long)context_ptr+0x000036d8+4*1))=0x000064c8;
*((unsigned int *)((unsigned long)context_ptr+0x000036d8+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000036d8+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000036d8+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000036d8+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005f4&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x000007b0))=0x03800040;
*((unsigned int *)((unsigned long)context_ptr+0x000007b0+4*1))=0x0000613c;
*((unsigned int *)((unsigned long)context_ptr+0x000007b0+4*2))=0x0000631c;
*((unsigned int *)((unsigned long)context_ptr+0x000007b0+4*3))=0x0222004a;
*((unsigned int *)((unsigned long)context_ptr+0x000007b0+4*4))=0x00fadc0b;
*((unsigned int *)((unsigned long)context_ptr+0x000007b0+4*5))=0x00006000+(unsigned long)context_ptr;
*((unsigned int *)((unsigned long)context_ptr+0x000007c8))=0x0040000a;
*((unsigned int *)((unsigned long)context_ptr+0x000007c8+4*1))=0x0000617c;
*((unsigned int *)((unsigned long)context_ptr+0x000007c8+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000007c8+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000007c8+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000007c8+4*5))=0x77777777+(unsigned long)context_ptr;
writel(0x00000030&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000168&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006194,"\x25\xcf\xc3\xa0\x31\x12\x23\x52\x4a\xcf\x57\x29\xf9\xb4\xcd\x7f\x18\x96\x71\x51\x16\x50\x45\x5b\xb6\x1d\x60\xc2\x4f\xdb\xdd\x30\xa6\xa3\x2b\x8e\x79\x3d\xb6\xe5\xe5\x1b\x60\x16\x76\xa9\xb4\x0e\x1c\xa1\xd5\x9b\x18\x14\x94\x37\xbf\x4d\xd3\xe6",60))
printf("strip: 25cfc3a031122352, Pass\n");
else
printf("strip: 25cfc3a031122352, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006514))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x00006514+4*1))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x00006514+4*2))=0x0106004b;
*((unsigned int *)((unsigned long)context_ptr+0x00006188))=0xad7995dc;
*((unsigned int *)((unsigned long)context_ptr+0x00006188+4*1))=0xcfcea3fc;
*((unsigned int *)((unsigned long)context_ptr+0x00006188+4*2))=0x9a326343;
*((unsigned int *)((unsigned long)context_ptr+0x00006188+4*3))=0x6d556ac9;
*((unsigned int *)((unsigned long)context_ptr+0x00006188+4*4))=0xa9ec0ab8;
*((unsigned int *)((unsigned long)context_ptr+0x00006188+4*5))=0x26160392;
*((unsigned int *)((unsigned long)context_ptr+0x00006188+4*6))=0xdc2a8f9d;
*((unsigned int *)((unsigned long)context_ptr+0x00006188+4*7))=0xc04a2355;
*((unsigned int *)((unsigned long)context_ptr+0x00006188+4*8))=0x9e44a37c;
*((unsigned int *)((unsigned long)context_ptr+0x00006188+4*9))=0x71b7033f;
*((unsigned int *)((unsigned long)context_ptr+0x00006188+4*10))=0xce61864d;
*((unsigned int *)((unsigned long)context_ptr+0x00006188+4*11))=0xa709a6f8;
*((unsigned int *)((unsigned long)context_ptr+0x00006188+4*12))=0xdd176602;
*((unsigned int *)((unsigned long)context_ptr+0x00006188+4*13))=0x8276ad06;
*((unsigned int *)((unsigned long)context_ptr+0x00006188+4*14))=0x736e6042;
*((unsigned int *)((unsigned long)context_ptr+0x00006188+4*15))=0xdca1d57d;
*((unsigned int *)((unsigned long)context_ptr+0x00006520))=0xb6a08684;
*((unsigned int *)((unsigned long)context_ptr+0x00006520+4*1))=0x46668fbc;
*((unsigned int *)((unsigned long)context_ptr+0x00006520+4*2))=0x00f50fbc;
*((unsigned int *)((unsigned long)context_ptr+0x000036f0))=0x04c0004b;
*((unsigned int *)((unsigned long)context_ptr+0x000036f0+4*1))=0x00006328;
*((unsigned int *)((unsigned long)context_ptr+0x000036f0+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000036f0+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000036f0+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000036f0+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005f4&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x000007e0))=0x03800040;
*((unsigned int *)((unsigned long)context_ptr+0x000007e0+4*1))=0x00006188;
*((unsigned int *)((unsigned long)context_ptr+0x000007e0+4*2))=0x00006514;
*((unsigned int *)((unsigned long)context_ptr+0x000007e0+4*3))=0x0222004b;
*((unsigned int *)((unsigned long)context_ptr+0x000007e0+4*4))=0x00d492a3;
*((unsigned int *)((unsigned long)context_ptr+0x000007e0+4*5))=0x00006000+(unsigned long)context_ptr;
*((unsigned int *)((unsigned long)context_ptr+0x000007f8))=0x0040000b;
*((unsigned int *)((unsigned long)context_ptr+0x000007f8+4*1))=0x00006520;
*((unsigned int *)((unsigned long)context_ptr+0x000007f8+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000007f8+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000007f8+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000007f8+4*5))=0x77777777+(unsigned long)context_ptr;
writel(0x00000030&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000016e&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x0000674c,"\xa8\x17\x84\xcc\xff\x75\x0e\x59\x7f\xed\x10\xea\x70\x19\xc0\x1e\x22\x3c\x8c\xa9\xdc\x96\xa3\x7b\x81\xa9\x45\x4b\x9f\x9f\x2e\x32\x8c\xd5\x4f\x2c\x0c\x87\x87\x9c\x8b\xa8\xde\x51\xcb\x3a\x54\x7e\x85\xbc\x06\xbd\xce\x00\x8f\x04\x23\xdf\x0e\xe8\xaa\x00\x00\x00",61))
printf("strip: a81784ccff750e59, Pass\n");
else
printf("strip: a81784ccff750e59, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000061c8))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x000061c8+4*1))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x000061c8+4*2))=0x0106004c;
*((unsigned int *)((unsigned long)context_ptr+0x0000674c))=0x32ddece8;
*((unsigned int *)((unsigned long)context_ptr+0x0000674c+4*1))=0x3a0d889a;
*((unsigned int *)((unsigned long)context_ptr+0x0000674c+4*2))=0xcfc1db92;
*((unsigned int *)((unsigned long)context_ptr+0x0000674c+4*3))=0x479cf474;
*((unsigned int *)((unsigned long)context_ptr+0x0000674c+4*4))=0xa4215f54;
*((unsigned int *)((unsigned long)context_ptr+0x0000674c+4*5))=0x2718d289;
*((unsigned int *)((unsigned long)context_ptr+0x0000674c+4*6))=0x5a403756;
*((unsigned int *)((unsigned long)context_ptr+0x0000674c+4*7))=0x85bd815a;
*((unsigned int *)((unsigned long)context_ptr+0x0000674c+4*8))=0xa9a810e4;
*((unsigned int *)((unsigned long)context_ptr+0x0000674c+4*9))=0x75b593ee;
*((unsigned int *)((unsigned long)context_ptr+0x0000674c+4*10))=0xa0741912;
*((unsigned int *)((unsigned long)context_ptr+0x0000674c+4*11))=0xf5de2f61;
*((unsigned int *)((unsigned long)context_ptr+0x0000674c+4*12))=0xf9244758;
*((unsigned int *)((unsigned long)context_ptr+0x0000674c+4*13))=0xcc508b91;
*((unsigned int *)((unsigned long)context_ptr+0x0000674c+4*14))=0xefabaa30;
*((unsigned int *)((unsigned long)context_ptr+0x0000674c+4*15))=0x81b971d5;
*((unsigned int *)((unsigned long)context_ptr+0x00006374))=0xedb88a22;
*((unsigned int *)((unsigned long)context_ptr+0x00006374+4*1))=0xb183438e;
*((unsigned int *)((unsigned long)context_ptr+0x00006374+4*2))=0x4c312148;
*((unsigned int *)((unsigned long)context_ptr+0x00003708))=0x04c0004c;
*((unsigned int *)((unsigned long)context_ptr+0x00003708+4*1))=0x0000652c;
*((unsigned int *)((unsigned long)context_ptr+0x00003708+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003708+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003708+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003708+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005f4&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000810))=0x03800040;
*((unsigned int *)((unsigned long)context_ptr+0x00000810+4*1))=0x0000674c;
*((unsigned int *)((unsigned long)context_ptr+0x00000810+4*2))=0x000061c8;
*((unsigned int *)((unsigned long)context_ptr+0x00000810+4*3))=0x0222004c;
*((unsigned int *)((unsigned long)context_ptr+0x00000810+4*4))=0x00f5111f;
*((unsigned int *)((unsigned long)context_ptr+0x00000810+4*5))=0x00006000+(unsigned long)context_ptr;
*((unsigned int *)((unsigned long)context_ptr+0x00000828))=0x0040000c;
*((unsigned int *)((unsigned long)context_ptr+0x00000828+4*1))=0x00006374;
*((unsigned int *)((unsigned long)context_ptr+0x00000828+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00000828+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00000828+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00000828+4*5))=0x77777777+(unsigned long)context_ptr;
writel(0x00000030&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000174&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000067cc,"\xe2\xbc\x6a\xc6\x10\xa2\xee\xe4\x51\x47\x4b\xe2\x57\x69\x54\x44\xde\x71\x88\x66\x55\x67\xe5\x47\xb2\x36\xe8\x77\x4c\x6d\xbd\xdb\xd0\x21\xf7\x7a\xf3\x2b\xf0\x31\xde\x45\xd7\x29\xda\xa9\x1f\xef\x6f\x2f\xd7\x0d\x09\xbc\x17\xbf\x18\xf0\x23\x90\xa5\x5d\x00\x00",62))
printf("strip: e2bc6ac610a2eee4, Pass\n");
else
printf("strip: e2bc6ac610a2eee4, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006008))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x00006008+4*1))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x00006008+4*2))=0x0106004d;
*((unsigned int *)((unsigned long)context_ptr+0x0000678c))=0x47c2640a;
*((unsigned int *)((unsigned long)context_ptr+0x0000678c+4*1))=0x91c181fd;
*((unsigned int *)((unsigned long)context_ptr+0x0000678c+4*2))=0x34c8c891;
*((unsigned int *)((unsigned long)context_ptr+0x0000678c+4*3))=0x143b2f29;
*((unsigned int *)((unsigned long)context_ptr+0x0000678c+4*4))=0x07a1653b;
*((unsigned int *)((unsigned long)context_ptr+0x0000678c+4*5))=0xa7e4b59d;
*((unsigned int *)((unsigned long)context_ptr+0x0000678c+4*6))=0x9c614c91;
*((unsigned int *)((unsigned long)context_ptr+0x0000678c+4*7))=0x5daa59cd;
*((unsigned int *)((unsigned long)context_ptr+0x0000678c+4*8))=0xa8190b9e;
*((unsigned int *)((unsigned long)context_ptr+0x0000678c+4*9))=0xc5bd4fdb;
*((unsigned int *)((unsigned long)context_ptr+0x0000678c+4*10))=0x336fab11;
*((unsigned int *)((unsigned long)context_ptr+0x0000678c+4*11))=0x67add234;
*((unsigned int *)((unsigned long)context_ptr+0x0000678c+4*12))=0x86fd2979;
*((unsigned int *)((unsigned long)context_ptr+0x0000678c+4*13))=0x51e06912;
*((unsigned int *)((unsigned long)context_ptr+0x0000678c+4*14))=0x9cc414bb;
*((unsigned int *)((unsigned long)context_ptr+0x0000678c+4*15))=0xcb7d3174;
*((unsigned int *)((unsigned long)context_ptr+0x00006578))=0x4b4a400d;
*((unsigned int *)((unsigned long)context_ptr+0x00006578+4*1))=0xa797edab;
*((unsigned int *)((unsigned long)context_ptr+0x00006578+4*2))=0xafb8787e;
*((unsigned int *)((unsigned long)context_ptr+0x00006578+4*3))=0x0000005d;
*((unsigned int *)((unsigned long)context_ptr+0x00003720))=0x04c0004d;
*((unsigned int *)((unsigned long)context_ptr+0x00003720+4*1))=0x00006920;
*((unsigned int *)((unsigned long)context_ptr+0x00003720+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003720+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003720+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003720+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005f4&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000840))=0x03800040;
*((unsigned int *)((unsigned long)context_ptr+0x00000840+4*1))=0x0000678c;
*((unsigned int *)((unsigned long)context_ptr+0x00000840+4*2))=0x00006008;
*((unsigned int *)((unsigned long)context_ptr+0x00000840+4*3))=0x0222004d;
*((unsigned int *)((unsigned long)context_ptr+0x00000840+4*4))=0x006fb3da;
*((unsigned int *)((unsigned long)context_ptr+0x00000840+4*5))=0x00006000+(unsigned long)context_ptr;
*((unsigned int *)((unsigned long)context_ptr+0x00000858))=0x0040000d;
*((unsigned int *)((unsigned long)context_ptr+0x00000858+4*1))=0x00006578;
*((unsigned int *)((unsigned long)context_ptr+0x00000858+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00000858+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00000858+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00000858+4*5))=0x77777777+(unsigned long)context_ptr;
writel(0x00000030&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000017a&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000063c8,"\x44\xca\x53\x72\xb5\x8b\xc1\x65\x0f\x57\xe2\xcd\xed\x96\x54\x7b\x7e\x3e\xdf\x0f\x54\xfa\x8f\xf1\x01\xcf\xa0\xdb\xbc\xff\x56\xbe\xd8\xb1\xca\xd1\x45\x48\x67\x06\xe7\xcf\x21\xd1\x54\x9b\x7d\x71\x9b\xe8\x6a\x06\xd9\xf3\xce\x28\x6b\xc1\xdd\xde\xec\xa4\x23\x00",63))
printf("strip: 44ca5372b58bc165, Pass\n");
else
printf("strip: 44ca5372b58bc165, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006014))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x00006014+4*1))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x00006014+4*2))=0x0106004e;
*((unsigned int *)((unsigned long)context_ptr+0x000067cc))=0x95dfba14;
*((unsigned int *)((unsigned long)context_ptr+0x000067cc+4*1))=0x7489b0c4;
*((unsigned int *)((unsigned long)context_ptr+0x000067cc+4*2))=0xa401478e;
*((unsigned int *)((unsigned long)context_ptr+0x000067cc+4*3))=0xb36f5ae6;
*((unsigned int *)((unsigned long)context_ptr+0x000067cc+4*4))=0xa6c53f08;
*((unsigned int *)((unsigned long)context_ptr+0x000067cc+4*5))=0x1d98600b;
*((unsigned int *)((unsigned long)context_ptr+0x000067cc+4*6))=0x119b2cf0;
*((unsigned int *)((unsigned long)context_ptr+0x000067cc+4*7))=0xfac32540;
*((unsigned int *)((unsigned long)context_ptr+0x000067cc+4*8))=0xe8a437e4;
*((unsigned int *)((unsigned long)context_ptr+0x000067cc+4*9))=0x54720fa8;
*((unsigned int *)((unsigned long)context_ptr+0x000067cc+4*10))=0x0ca80fa5;
*((unsigned int *)((unsigned long)context_ptr+0x000067cc+4*11))=0xc4dd3a0e;
*((unsigned int *)((unsigned long)context_ptr+0x000067cc+4*12))=0xee420243;
*((unsigned int *)((unsigned long)context_ptr+0x000067cc+4*13))=0xa1b9148e;
*((unsigned int *)((unsigned long)context_ptr+0x000067cc+4*14))=0xadd8fad8;
*((unsigned int *)((unsigned long)context_ptr+0x000067cc+4*15))=0x83369ee0;
*((unsigned int *)((unsigned long)context_ptr+0x00006380))=0x112f3f4c;
*((unsigned int *)((unsigned long)context_ptr+0x00006380+4*1))=0x8782e049;
*((unsigned int *)((unsigned long)context_ptr+0x00006380+4*2))=0xf71ef51c;
*((unsigned int *)((unsigned long)context_ptr+0x00006380+4*3))=0x00000c2f;
*((unsigned int *)((unsigned long)context_ptr+0x00003738))=0x04c0004e;
*((unsigned int *)((unsigned long)context_ptr+0x00003738+4*1))=0x00006390;
*((unsigned int *)((unsigned long)context_ptr+0x00003738+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003738+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003738+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003738+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005f4&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000870))=0x03800040;
*((unsigned int *)((unsigned long)context_ptr+0x00000870+4*1))=0x000067cc;
*((unsigned int *)((unsigned long)context_ptr+0x00000870+4*2))=0x00006014;
*((unsigned int *)((unsigned long)context_ptr+0x00000870+4*3))=0x0222004e;
*((unsigned int *)((unsigned long)context_ptr+0x00000870+4*4))=0x00c0a562;
*((unsigned int *)((unsigned long)context_ptr+0x00000870+4*5))=0x00006000+(unsigned long)context_ptr;
*((unsigned int *)((unsigned long)context_ptr+0x00000888))=0x0040000e;
*((unsigned int *)((unsigned long)context_ptr+0x00000888+4*1))=0x00006380;
*((unsigned int *)((unsigned long)context_ptr+0x00000888+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00000888+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00000888+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00000888+4*5))=0x77777777+(unsigned long)context_ptr;
writel(0x00000030&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000180&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x0000658c,"\x43\x97\x71\x84\xf8\x09\xdf\x6e\xd8\xe0\xbc\x79\x85\x98\x65\xb6\xda\x56\xf4\x90\x4b\x29\xb9\x47\xcf\xf2\x5a\x60\x4d\x41\xff\xd3\xdd\x07\xf3\xd2\xd2\xed\x69\x13\x91\x89\x37\xbe\xfc\xb7\xcb\xc5\xcf\x28\x9b\x9b\xdf\x70\x42\x89\x7e\x04\x0c\x30\x7e\xa8\x85\x93",64))
printf("strip: 43977184f809df6e, Pass\n");
else
printf("strip: 43977184f809df6e, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006020))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x00006020+4*1))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x00006020+4*2))=0x0106004f;
*((unsigned int *)((unsigned long)context_ptr+0x00006588))=0xc30e4117;
*((unsigned int *)((unsigned long)context_ptr+0x00006588+4*1))=0x97e6436c;
*((unsigned int *)((unsigned long)context_ptr+0x00006588+4*2))=0x221caef9;
*((unsigned int *)((unsigned long)context_ptr+0x00006588+4*3))=0xeac95c1e;
*((unsigned int *)((unsigned long)context_ptr+0x00006588+4*4))=0xccf1680d;
*((unsigned int *)((unsigned long)context_ptr+0x00006588+4*5))=0x5523e547;
*((unsigned int *)((unsigned long)context_ptr+0x00006588+4*6))=0x12886c34;
*((unsigned int *)((unsigned long)context_ptr+0x00006588+4*7))=0x16d79e2d;
*((unsigned int *)((unsigned long)context_ptr+0x00006588+4*8))=0x0ec680f4;
*((unsigned int *)((unsigned long)context_ptr+0x00006588+4*9))=0xf690765b;
*((unsigned int *)((unsigned long)context_ptr+0x00006588+4*10))=0xe4f7e981;
*((unsigned int *)((unsigned long)context_ptr+0x00006588+4*11))=0xb750de59;
*((unsigned int *)((unsigned long)context_ptr+0x00006588+4*12))=0xcbe69ab2;
*((unsigned int *)((unsigned long)context_ptr+0x00006588+4*13))=0xbae26cd0;
*((unsigned int *)((unsigned long)context_ptr+0x00006588+4*14))=0xd93d6c50;
*((unsigned int *)((unsigned long)context_ptr+0x00006588+4*15))=0x8f63605f;
*((unsigned int *)((unsigned long)context_ptr+0x000063e0))=0xcaabd148;
*((unsigned int *)((unsigned long)context_ptr+0x000063e0+4*1))=0x31356011;
*((unsigned int *)((unsigned long)context_ptr+0x000063e0+4*2))=0x1060da56;
*((unsigned int *)((unsigned long)context_ptr+0x000063e0+4*3))=0x008cc9d9;
*((unsigned int *)((unsigned long)context_ptr+0x00003750))=0x04c0004f;
*((unsigned int *)((unsigned long)context_ptr+0x00003750+4*1))=0x00006970;
*((unsigned int *)((unsigned long)context_ptr+0x00003750+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003750+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003750+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003750+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005f4&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x000008a0))=0x03800040;
*((unsigned int *)((unsigned long)context_ptr+0x000008a0+4*1))=0x00006588;
*((unsigned int *)((unsigned long)context_ptr+0x000008a0+4*2))=0x00006020;
*((unsigned int *)((unsigned long)context_ptr+0x000008a0+4*3))=0x0222004f;
*((unsigned int *)((unsigned long)context_ptr+0x000008a0+4*4))=0x00a8cb2f;
*((unsigned int *)((unsigned long)context_ptr+0x000008a0+4*5))=0x00006000+(unsigned long)context_ptr;
*((unsigned int *)((unsigned long)context_ptr+0x000008b8))=0x0040000f;
*((unsigned int *)((unsigned long)context_ptr+0x000008b8+4*1))=0x000063e0;
*((unsigned int *)((unsigned long)context_ptr+0x000008b8+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000008b8+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000008b8+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000008b8+4*5))=0x77777777+(unsigned long)context_ptr;
writel(0x00000030&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000186&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x0000660c,"\x58\x19\x90\x5a\xb9\xd6\x98\xd1\x02\x3b\x6e\x77\xd0\x2c\x92\x89\xa5\x03\x0b\x17\x64\x99\xbb\xa6\x1b\xdd\x64\xd0\x2b\x61\xab\xa1\x84\xec\xcf\x98\xad\x6a\x83\xa1\xd6\x33\x75\x2f\x32\x09\x1e\xc1\x54\x4e\x24\x93\x6a\x0e\x61\xce\xc1\xf9\xdb\x7f\xca\xc9\x68\x63\x8f\x00\x00\x00",65))
printf("strip: 5819905ab9d698d1, Pass\n");
else
printf("strip: 5819905ab9d698d1, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x0000602c))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x0000602c+4*1))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x0000602c+4*2))=0x01060050;
*((unsigned int *)((unsigned long)context_ptr+0x000061d4))=0x53b2b4ee;
*((unsigned int *)((unsigned long)context_ptr+0x000061d4+4*1))=0x9d4ab634;
*((unsigned int *)((unsigned long)context_ptr+0x000061d4+4*2))=0x8ca27018;
*((unsigned int *)((unsigned long)context_ptr+0x000061d4+4*3))=0x10743aa3;
*((unsigned int *)((unsigned long)context_ptr+0x000061d4+4*4))=0xcba53513;
*((unsigned int *)((unsigned long)context_ptr+0x000061d4+4*5))=0xb1015b99;
*((unsigned int *)((unsigned long)context_ptr+0x000061d4+4*6))=0x589e02d9;
*((unsigned int *)((unsigned long)context_ptr+0x000061d4+4*7))=0x8c6ebb69;
*((unsigned int *)((unsigned long)context_ptr+0x000061d4+4*8))=0x8979a8b1;
*((unsigned int *)((unsigned long)context_ptr+0x000061d4+4*9))=0x770503a5;
*((unsigned int *)((unsigned long)context_ptr+0x000061d4+4*10))=0xac86f3b5;
*((unsigned int *)((unsigned long)context_ptr+0x000061d4+4*11))=0x7a2019eb;
*((unsigned int *)((unsigned long)context_ptr+0x000061d4+4*12))=0xde624d91;
*((unsigned int *)((unsigned long)context_ptr+0x000061d4+4*13))=0x98ed9288;
*((unsigned int *)((unsigned long)context_ptr+0x000061d4+4*14))=0x81302d76;
*((unsigned int *)((unsigned long)context_ptr+0x000061d4+4*15))=0x63e1820b;
*((unsigned int *)((unsigned long)context_ptr+0x000063f0))=0x56d0c0d6;
*((unsigned int *)((unsigned long)context_ptr+0x000063f0+4*1))=0x2b19a79c;
*((unsigned int *)((unsigned long)context_ptr+0x000063f0+4*2))=0x7c0ab8ac;
*((unsigned int *)((unsigned long)context_ptr+0x000063f0+4*3))=0xf8c36c7a;
*((unsigned int *)((unsigned long)context_ptr+0x00003768))=0x04c00050;
*((unsigned int *)((unsigned long)context_ptr+0x00003768+4*1))=0x000065c8;
*((unsigned int *)((unsigned long)context_ptr+0x00003768+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003768+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003768+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003768+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005f4&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x000008d0))=0x03800040;
*((unsigned int *)((unsigned long)context_ptr+0x000008d0+4*1))=0x000061d4;
*((unsigned int *)((unsigned long)context_ptr+0x000008d0+4*2))=0x0000602c;
*((unsigned int *)((unsigned long)context_ptr+0x000008d0+4*3))=0x02220050;
*((unsigned int *)((unsigned long)context_ptr+0x000008d0+4*4))=0x006a4d85;
*((unsigned int *)((unsigned long)context_ptr+0x000008d0+4*5))=0x00006000+(unsigned long)context_ptr;
*((unsigned int *)((unsigned long)context_ptr+0x000008e8))=0x00400010;
*((unsigned int *)((unsigned long)context_ptr+0x000008e8+4*1))=0x000063f0;
*((unsigned int *)((unsigned long)context_ptr+0x000008e8+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000008e8+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000008e8+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000008e8+4*5))=0x77777777+(unsigned long)context_ptr;
writel(0x00000030&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000018c&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x0000621c,"\xa3\x87\xca\x8b\x41\xc3\x5d\x0b\x37\x71\x9c\xc7\xdc\xc6\xc0\x96\x31\xaa\xb1\x44\x5f\x4b\xfe\xb2\x5b\x31\x57\x3d\xd4\x30\x60\x88\x40\x2b\xf6\xe7\x06\x88\x0b\x6f\x1c\xcd\x33\x4c\x15\xf7\x80\x6c\x8d\x2d\xcc\x49\xd8\xbd\x4b\x7c\x4b\xf0\xd9\x89\xb0\x13\xcc\x5b\x44\x53\x00\x00",66))
printf("strip: a387ca8b41c35d0b, Pass\n");
else
printf("strip: a387ca8b41c35d0b, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006038))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x00006038+4*1))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x00006038+4*2))=0x01060051;
*((unsigned int *)((unsigned long)context_ptr+0x00006400))=0x41ffeaeb;
*((unsigned int *)((unsigned long)context_ptr+0x00006400+4*1))=0x655e9d37;
*((unsigned int *)((unsigned long)context_ptr+0x00006400+4*2))=0xcedaadc5;
*((unsigned int *)((unsigned long)context_ptr+0x00006400+4*3))=0xca6c1a7d;
*((unsigned int *)((unsigned long)context_ptr+0x00006400+4*4))=0xd166d75d;
*((unsigned int *)((unsigned long)context_ptr+0x00006400+4*5))=0xec01abc2;
*((unsigned int *)((unsigned long)context_ptr+0x00006400+4*6))=0xdc03175d;
*((unsigned int *)((unsigned long)context_ptr+0x00006400+4*7))=0xeffc966b;
*((unsigned int *)((unsigned long)context_ptr+0x00006400+4*8))=0x6ba4bba1;
*((unsigned int *)((unsigned long)context_ptr+0x00006400+4*9))=0x364c351d;
*((unsigned int *)((unsigned long)context_ptr+0x00006400+4*10))=0xb23c34ee;
*((unsigned int *)((unsigned long)context_ptr+0x00006400+4*11))=0xd04ba3f8;
*((unsigned int *)((unsigned long)context_ptr+0x00006400+4*12))=0xc07ea628;
*((unsigned int *)((unsigned long)context_ptr+0x00006400+4*13))=0xd7009f7c;
*((unsigned int *)((unsigned long)context_ptr+0x00006400+4*14))=0xfdf232b9;
*((unsigned int *)((unsigned long)context_ptr+0x00006400+4*15))=0x4efdd6a0;
*((unsigned int *)((unsigned long)context_ptr+0x00006618))=0x4bf7522f;
*((unsigned int *)((unsigned long)context_ptr+0x00006618+4*1))=0x742dd973;
*((unsigned int *)((unsigned long)context_ptr+0x00006618+4*2))=0x6ff56b43;
*((unsigned int *)((unsigned long)context_ptr+0x00006618+4*3))=0x57dbe40f;
*((unsigned int *)((unsigned long)context_ptr+0x00006618+4*4))=0x0000000c;
*((unsigned int *)((unsigned long)context_ptr+0x00003780))=0x04c00051;
*((unsigned int *)((unsigned long)context_ptr+0x00003780+4*1))=0x000069c0;
*((unsigned int *)((unsigned long)context_ptr+0x00003780+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003780+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003780+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003780+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005f4&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000900))=0x03800040;
*((unsigned int *)((unsigned long)context_ptr+0x00000900+4*1))=0x00006400;
*((unsigned int *)((unsigned long)context_ptr+0x00000900+4*2))=0x00006038;
*((unsigned int *)((unsigned long)context_ptr+0x00000900+4*3))=0x02220051;
*((unsigned int *)((unsigned long)context_ptr+0x00000900+4*4))=0x0061dbbd;
*((unsigned int *)((unsigned long)context_ptr+0x00000900+4*5))=0x00006000+(unsigned long)context_ptr;
*((unsigned int *)((unsigned long)context_ptr+0x00000918))=0x00400011;
*((unsigned int *)((unsigned long)context_ptr+0x00000918+4*1))=0x00006618;
*((unsigned int *)((unsigned long)context_ptr+0x00000918+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00000918+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00000918+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00000918+4*5))=0x77777777+(unsigned long)context_ptr;
writel(0x00000030&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000192&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006260,"\x97\x11\x1c\x64\x4a\x1b\xf1\xf2\xf6\xfa\xe8\x90\x67\xbd\x86\x3a\xc6\x29\xa6\xf3\x89\x25\x5b\x82\x6e\x26\x99\xe1\xf8\x2e\xa8\x05\x26\x83\x9b\x3f\xbc\xe4\xf8\x1a\xae\x85\xb2\xee\x49\xe1\x17\x0a\xec\x42\xb5\x38\x96\x57\xb9\xbe\xe6\xcd\x73\x20\xab\x70\xb5\xfc\x55\x71\x57\x00",67))
printf("strip: 97111c644a1bf1f2, Pass\n");
else
printf("strip: 97111c644a1bf1f2, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006044))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x00006044+4*1))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x00006044+4*2))=0x01060052;
*((unsigned int *)((unsigned long)context_ptr+0x00006440))=0xa38a0869;
*((unsigned int *)((unsigned long)context_ptr+0x00006440+4*1))=0x78f3e65a;
*((unsigned int *)((unsigned long)context_ptr+0x00006440+4*2))=0x0faf6c81;
*((unsigned int *)((unsigned long)context_ptr+0x00006440+4*3))=0x8931cc4e;
*((unsigned int *)((unsigned long)context_ptr+0x00006440+4*4))=0x8c671d37;
*((unsigned int *)((unsigned long)context_ptr+0x00006440+4*5))=0xba735643;
*((unsigned int *)((unsigned long)context_ptr+0x00006440+4*6))=0xf9999626;
*((unsigned int *)((unsigned long)context_ptr+0x00006440+4*7))=0x9d7b689b;
*((unsigned int *)((unsigned long)context_ptr+0x00006440+4*8))=0x3f4bac88;
*((unsigned int *)((unsigned long)context_ptr+0x00006440+4*9))=0xfbbdf1fa;
*((unsigned int *)((unsigned long)context_ptr+0x00006440+4*10))=0xeb5845fe;
*((unsigned int *)((unsigned long)context_ptr+0x00006440+4*11))=0x31c926b7;
*((unsigned int *)((unsigned long)context_ptr+0x00006440+4*12))=0x61359d34;
*((unsigned int *)((unsigned long)context_ptr+0x00006440+4*13))=0xe89db029;
*((unsigned int *)((unsigned long)context_ptr+0x00006440+4*14))=0x074efc18;
*((unsigned int *)((unsigned long)context_ptr+0x00006440+4*15))=0x7e4af259;
*((unsigned int *)((unsigned long)context_ptr+0x0000662c))=0xec5fad46;
*((unsigned int *)((unsigned long)context_ptr+0x0000662c+4*1))=0x5efca01b;
*((unsigned int *)((unsigned long)context_ptr+0x0000662c+4*2))=0x7925c688;
*((unsigned int *)((unsigned long)context_ptr+0x0000662c+4*3))=0xcc86e1da;
*((unsigned int *)((unsigned long)context_ptr+0x0000662c+4*4))=0x0000ae88;
*((unsigned int *)((unsigned long)context_ptr+0x00003798))=0x04c00052;
*((unsigned int *)((unsigned long)context_ptr+0x00003798+4*1))=0x00006214;
*((unsigned int *)((unsigned long)context_ptr+0x00003798+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003798+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003798+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003798+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005f4&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000930))=0x03800040;
*((unsigned int *)((unsigned long)context_ptr+0x00000930+4*1))=0x00006440;
*((unsigned int *)((unsigned long)context_ptr+0x00000930+4*2))=0x00006044;
*((unsigned int *)((unsigned long)context_ptr+0x00000930+4*3))=0x02220052;
*((unsigned int *)((unsigned long)context_ptr+0x00000930+4*4))=0x00113e7a;
*((unsigned int *)((unsigned long)context_ptr+0x00000930+4*5))=0x00006000+(unsigned long)context_ptr;
*((unsigned int *)((unsigned long)context_ptr+0x00000948))=0x00400012;
*((unsigned int *)((unsigned long)context_ptr+0x00000948+4*1))=0x0000662c;
*((unsigned int *)((unsigned long)context_ptr+0x00000948+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00000948+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00000948+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00000948+4*5))=0x77777777+(unsigned long)context_ptr;
writel(0x00000030&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000198&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x0000680c,"\x24\xd5\x0c\xe9\x4a\x32\xa7\x3e\x90\xc3\xaa\x51\xa2\xa0\x05\x75\xa1\x61\x29\xe9\x02\xdd\x2a\xfd\xe9\x17\xc4\xaa\xdd\x7f\x4f\xca\xbc\x89\xfc\xc4\x7f\xed\x81\xd7\x0c\x21\x36\x3b\x23\x0a\x8f\x97\xb9\x9d\x74\x73\x03\x9d\xa2\xa0\xf6\xb4\x35\x9c\x8d\xac\x98\xc1\x75\x91\xec\x43",68))
printf("strip: 24d50ce94a32a73e, Pass\n");
else
printf("strip: 24d50ce94a32a73e, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006050))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x00006050+4*1))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x00006050+4*2))=0x01060053;
*((unsigned int *)((unsigned long)context_ptr+0x0000680c))=0x69698bc6;
*((unsigned int *)((unsigned long)context_ptr+0x0000680c+4*1))=0xfa3e8d6c;
*((unsigned int *)((unsigned long)context_ptr+0x0000680c+4*2))=0xa68856dc;
*((unsigned int *)((unsigned long)context_ptr+0x0000680c+4*3))=0xaaa42c7e;
*((unsigned int *)((unsigned long)context_ptr+0x0000680c+4*4))=0xfa788596;
*((unsigned int *)((unsigned long)context_ptr+0x0000680c+4*5))=0xc200e219;
*((unsigned int *)((unsigned long)context_ptr+0x0000680c+4*6))=0xf40d8875;
*((unsigned int *)((unsigned long)context_ptr+0x0000680c+4*7))=0xe3fed32e;
*((unsigned int *)((unsigned long)context_ptr+0x0000680c+4*8))=0xad9726a2;
*((unsigned int *)((unsigned long)context_ptr+0x0000680c+4*9))=0x0929afed;
*((unsigned int *)((unsigned long)context_ptr+0x0000680c+4*10))=0x59555ace;
*((unsigned int *)((unsigned long)context_ptr+0x0000680c+4*11))=0x7ccad6ec;
*((unsigned int *)((unsigned long)context_ptr+0x0000680c+4*12))=0xf7e394fb;
*((unsigned int *)((unsigned long)context_ptr+0x0000680c+4*13))=0x07f6979a;
*((unsigned int *)((unsigned long)context_ptr+0x0000680c+4*14))=0xefd11e89;
*((unsigned int *)((unsigned long)context_ptr+0x0000680c+4*15))=0x1ae64c8f;
*((unsigned int *)((unsigned long)context_ptr+0x00006268))=0xc3c60ac9;
*((unsigned int *)((unsigned long)context_ptr+0x00006268+4*1))=0xd22ea9ca;
*((unsigned int *)((unsigned long)context_ptr+0x00006268+4*2))=0xd7a0d439;
*((unsigned int *)((unsigned long)context_ptr+0x00006268+4*3))=0x91ec0389;
*((unsigned int *)((unsigned long)context_ptr+0x00006268+4*4))=0x00907572;
*((unsigned int *)((unsigned long)context_ptr+0x000037b0))=0x04c00053;
*((unsigned int *)((unsigned long)context_ptr+0x000037b0+4*1))=0x00006a14;
*((unsigned int *)((unsigned long)context_ptr+0x000037b0+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000037b0+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000037b0+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000037b0+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005f4&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000960))=0x03800040;
*((unsigned int *)((unsigned long)context_ptr+0x00000960+4*1))=0x0000680c;
*((unsigned int *)((unsigned long)context_ptr+0x00000960+4*2))=0x00006050;
*((unsigned int *)((unsigned long)context_ptr+0x00000960+4*3))=0x02220053;
*((unsigned int *)((unsigned long)context_ptr+0x00000960+4*4))=0x000b7349;
*((unsigned int *)((unsigned long)context_ptr+0x00000960+4*5))=0x00006000+(unsigned long)context_ptr;
*((unsigned int *)((unsigned long)context_ptr+0x00000978))=0x00400013;
*((unsigned int *)((unsigned long)context_ptr+0x00000978+4*1))=0x00006268;
*((unsigned int *)((unsigned long)context_ptr+0x00000978+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00000978+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00000978+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00000978+4*5))=0x77777777+(unsigned long)context_ptr;
writel(0x00000030&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000019e&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006850,"\xd7\xfe\x54\x96\x8e\x92\xaa\xef\x04\x4f\x76\x84\xe8\x7f\x3c\xdb\x83\xc8\x43\xf1\x66\x72\x7a\x54\xc2\x93\x9a\x99\x4b\x57\x17\x62\x43\x59\x9f\xaf\xbf\x38\x2e\xf7\x77\x79\x15\xaf\x2c\x0d\x40\xf7\x55\x0e\xab\x2c\x48\x79\x8a\x4d\xec\xc2\xa0\x13\xd1\xd4\xce\xd4\x2c\xe6\x4b\x43\x00\x00\x00\x00",69))
printf("strip: d7fe54968e92aaef, Pass\n");
else
printf("strip: d7fe54968e92aaef, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x0000605c))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x0000605c+4*1))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x0000605c+4*2))=0x01060054;
*((unsigned int *)((unsigned long)context_ptr+0x0000627c))=0x556b2929;
*((unsigned int *)((unsigned long)context_ptr+0x0000627c+4*1))=0x1c0facc2;
*((unsigned int *)((unsigned long)context_ptr+0x0000627c+4*2))=0xb78f1a86;
*((unsigned int *)((unsigned long)context_ptr+0x0000627c+4*3))=0x41ef029e;
*((unsigned int *)((unsigned long)context_ptr+0x0000627c+4*4))=0x4ffa8675;
*((unsigned int *)((unsigned long)context_ptr+0x0000627c+4*5))=0x3990d6a8;
*((unsigned int *)((unsigned long)context_ptr+0x0000627c+4*6))=0x7ebb2147;
*((unsigned int *)((unsigned long)context_ptr+0x0000627c+4*7))=0x2033eb54;
*((unsigned int *)((unsigned long)context_ptr+0x0000627c+4*8))=0x9661649e;
*((unsigned int *)((unsigned long)context_ptr+0x0000627c+4*9))=0x0c19049b;
*((unsigned int *)((unsigned long)context_ptr+0x0000627c+4*10))=0x13e93608;
*((unsigned int *)((unsigned long)context_ptr+0x0000627c+4*11))=0xaa609331;
*((unsigned int *)((unsigned long)context_ptr+0x0000627c+4*12))=0x5a13b035;
*((unsigned int *)((unsigned long)context_ptr+0x0000627c+4*13))=0x08049d6d;
*((unsigned int *)((unsigned long)context_ptr+0x0000627c+4*14))=0xb170991d;
*((unsigned int *)((unsigned long)context_ptr+0x0000627c+4*15))=0xee3e0172;
*((unsigned int *)((unsigned long)context_ptr+0x00006068))=0xb850c0d5;
*((unsigned int *)((unsigned long)context_ptr+0x00006068+4*1))=0xb1640846;
*((unsigned int *)((unsigned long)context_ptr+0x00006068+4*2))=0x9f50fd3e;
*((unsigned int *)((unsigned long)context_ptr+0x00006068+4*3))=0x99cd161a;
*((unsigned int *)((unsigned long)context_ptr+0x00006068+4*4))=0xcda0641b;
*((unsigned int *)((unsigned long)context_ptr+0x000037c8))=0x04c00054;
*((unsigned int *)((unsigned long)context_ptr+0x000037c8+4*1))=0x00006640;
*((unsigned int *)((unsigned long)context_ptr+0x000037c8+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000037c8+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000037c8+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000037c8+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005f4&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000990))=0x03800040;
*((unsigned int *)((unsigned long)context_ptr+0x00000990+4*1))=0x0000627c;
*((unsigned int *)((unsigned long)context_ptr+0x00000990+4*2))=0x0000605c;
*((unsigned int *)((unsigned long)context_ptr+0x00000990+4*3))=0x02220054;
*((unsigned int *)((unsigned long)context_ptr+0x00000990+4*4))=0x0030c6a6;
*((unsigned int *)((unsigned long)context_ptr+0x00000990+4*5))=0x00006000+(unsigned long)context_ptr;
*((unsigned int *)((unsigned long)context_ptr+0x000009a8))=0x00400014;
*((unsigned int *)((unsigned long)context_ptr+0x000009a8+4*1))=0x00006068;
*((unsigned int *)((unsigned long)context_ptr+0x000009a8+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000009a8+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000009a8+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000009a8+4*5))=0x77777777+(unsigned long)context_ptr;
writel(0x00000030&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000001a4&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x0000609c,"\xbc\x8f\x43\x23\x02\x6c\xa9\xd3\x48\x11\x7b\x56\x55\x0c\x85\x71\xb5\xad\x61\x0a\xf8\x33\xbd\x8f\x07\xbb\xf8\x26\xb7\x92\x8a\x6e\x72\x2c\x5c\xac\xd9\xbc\xa0\x3a\x01\xdb\xc4\xf2\x22\xf9\x54\x90\x04\xcb\xef\xf2\x27\x23\x8c\x68\x04\x49\xc7\xc3\x3c\xeb\x5e\xc5\x57\xfc\xad\x5e\x10\x30\x00\x00",70))
printf("strip: bc8f4323026ca9d3, Pass\n");
else
printf("strip: bc8f4323026ca9d3, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006694))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x00006694+4*1))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x00006694+4*2))=0x01060055;
*((unsigned int *)((unsigned long)context_ptr+0x00006480))=0x4fa3ecaf;
*((unsigned int *)((unsigned long)context_ptr+0x00006480+4*1))=0x8bd0ddc8;
*((unsigned int *)((unsigned long)context_ptr+0x00006480+4*2))=0x15b4d17f;
*((unsigned int *)((unsigned long)context_ptr+0x00006480+4*3))=0x3881d1c2;
*((unsigned int *)((unsigned long)context_ptr+0x00006480+4*4))=0x7ed37f73;
*((unsigned int *)((unsigned long)context_ptr+0x00006480+4*5))=0x682d6cdd;
*((unsigned int *)((unsigned long)context_ptr+0x00006480+4*6))=0xb5e99ccc;
*((unsigned int *)((unsigned long)context_ptr+0x00006480+4*7))=0x8bb8ecb2;
*((unsigned int *)((unsigned long)context_ptr+0x00006480+4*8))=0x39edebdd;
*((unsigned int *)((unsigned long)context_ptr+0x00006480+4*9))=0x690ca37f;
*((unsigned int *)((unsigned long)context_ptr+0x00006480+4*10))=0x520ad79a;
*((unsigned int *)((unsigned long)context_ptr+0x00006480+4*11))=0xfd532950;
*((unsigned int *)((unsigned long)context_ptr+0x00006480+4*12))=0xfcc9127d;
*((unsigned int *)((unsigned long)context_ptr+0x00006480+4*13))=0xd2679ceb;
*((unsigned int *)((unsigned long)context_ptr+0x00006480+4*14))=0x79aa2d92;
*((unsigned int *)((unsigned long)context_ptr+0x00006480+4*15))=0x4d4a34b2;
*((unsigned int *)((unsigned long)context_ptr+0x0000684c))=0xaa59b44a;
*((unsigned int *)((unsigned long)context_ptr+0x0000684c+4*1))=0xea770603;
*((unsigned int *)((unsigned long)context_ptr+0x0000684c+4*2))=0x4fff150c;
*((unsigned int *)((unsigned long)context_ptr+0x0000684c+4*3))=0x39141012;
*((unsigned int *)((unsigned long)context_ptr+0x0000684c+4*4))=0xf1d70896;
*((unsigned int *)((unsigned long)context_ptr+0x0000684c+4*5))=0x00000055;
*((unsigned int *)((unsigned long)context_ptr+0x000037e0))=0x04c00055;
*((unsigned int *)((unsigned long)context_ptr+0x000037e0+4*1))=0x0000607c;
*((unsigned int *)((unsigned long)context_ptr+0x000037e0+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000037e0+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000037e0+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000037e0+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005f4&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x000009c0))=0x03800040;
*((unsigned int *)((unsigned long)context_ptr+0x000009c0+4*1))=0x00006480;
*((unsigned int *)((unsigned long)context_ptr+0x000009c0+4*2))=0x00006694;
*((unsigned int *)((unsigned long)context_ptr+0x000009c0+4*3))=0x02220055;
*((unsigned int *)((unsigned long)context_ptr+0x000009c0+4*4))=0x0096831b;
*((unsigned int *)((unsigned long)context_ptr+0x000009c0+4*5))=0x00006000+(unsigned long)context_ptr;
*((unsigned int *)((unsigned long)context_ptr+0x000009d8))=0x00400015;
*((unsigned int *)((unsigned long)context_ptr+0x000009d8+4*1))=0x0000684c;
*((unsigned int *)((unsigned long)context_ptr+0x000009d8+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000009d8+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000009d8+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000009d8+4*5))=0x77777777+(unsigned long)context_ptr;
writel(0x00000030&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000001aa&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000068d8,"\x2f\x6b\x18\x26\xdb\x2d\x72\x14\xcb\x44\xa9\xd1\x69\x34\x28\x75\x98\xa8\x96\x3e\x00\x22\x70\xf8\x91\xfa\xd7\xfe\x4a\xb0\x6e\xde\x9d\x67\xf1\xd7\x7e\x6c\x67\x67\x4f\x2a\xd4\x1f\x9f\x28\xde\x3a\x20\x04\xe7\xc9\x50\xdd\x82\x38\x91\x07\xb2\x45\x5f\xdc\x9f\xf5\x3a\x01\xda\x9b\x22\x40\xf2\x00",71))
printf("strip: 2f6b1826db2d7214, Pass\n");
else
printf("strip: 2f6b1826db2d7214, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000060d4))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x000060d4+4*1))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x000060d4+4*2))=0x01060056;
*((unsigned int *)((unsigned long)context_ptr+0x00006864))=0xd88bc5e3;
*((unsigned int *)((unsigned long)context_ptr+0x00006864+4*1))=0xd1b8fc26;
*((unsigned int *)((unsigned long)context_ptr+0x00006864+4*2))=0xbf9c0441;
*((unsigned int *)((unsigned long)context_ptr+0x00006864+4*3))=0x9c3926ed;
*((unsigned int *)((unsigned long)context_ptr+0x00006864+4*4))=0xb2644cd0;
*((unsigned int *)((unsigned long)context_ptr+0x00006864+4*5))=0x08447913;
*((unsigned int *)((unsigned long)context_ptr+0x00006864+4*6))=0x90e54c5d;
*((unsigned int *)((unsigned long)context_ptr+0x00006864+4*7))=0xfd864e3b;
*((unsigned int *)((unsigned long)context_ptr+0x00006864+4*8))=0x131c6046;
*((unsigned int *)((unsigned long)context_ptr+0x00006864+4*9))=0xd2afa632;
*((unsigned int *)((unsigned long)context_ptr+0x00006864+4*10))=0xf15f46d3;
*((unsigned int *)((unsigned long)context_ptr+0x00006864+4*11))=0xecb3a586;
*((unsigned int *)((unsigned long)context_ptr+0x00006864+4*12))=0x5771c668;
*((unsigned int *)((unsigned long)context_ptr+0x00006864+4*13))=0x964f9dbc;
*((unsigned int *)((unsigned long)context_ptr+0x00006864+4*14))=0x1208ea1a;
*((unsigned int *)((unsigned long)context_ptr+0x00006864+4*15))=0x6cefc8b2;
*((unsigned int *)((unsigned long)context_ptr+0x000066a0))=0x4b1780f0;
*((unsigned int *)((unsigned long)context_ptr+0x000066a0+4*1))=0x8a0fe17e;
*((unsigned int *)((unsigned long)context_ptr+0x000066a0+4*2))=0x795edd8c;
*((unsigned int *)((unsigned long)context_ptr+0x000066a0+4*3))=0x73a239aa;
*((unsigned int *)((unsigned long)context_ptr+0x000066a0+4*4))=0xad973f3d;
*((unsigned int *)((unsigned long)context_ptr+0x000066a0+4*5))=0x00006248;
*((unsigned int *)((unsigned long)context_ptr+0x000037f8))=0x04c00056;
*((unsigned int *)((unsigned long)context_ptr+0x000037f8+4*1))=0x000068a4;
*((unsigned int *)((unsigned long)context_ptr+0x000037f8+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000037f8+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000037f8+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000037f8+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005f4&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x000009f0))=0x03800040;
*((unsigned int *)((unsigned long)context_ptr+0x000009f0+4*1))=0x00006864;
*((unsigned int *)((unsigned long)context_ptr+0x000009f0+4*2))=0x000060d4;
*((unsigned int *)((unsigned long)context_ptr+0x000009f0+4*3))=0x02220056;
*((unsigned int *)((unsigned long)context_ptr+0x000009f0+4*4))=0x00d42003;
*((unsigned int *)((unsigned long)context_ptr+0x000009f0+4*5))=0x00006000+(unsigned long)context_ptr;
*((unsigned int *)((unsigned long)context_ptr+0x00000a08))=0x00400016;
*((unsigned int *)((unsigned long)context_ptr+0x00000a08+4*1))=0x000066a0;
*((unsigned int *)((unsigned long)context_ptr+0x00000a08+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00000a08+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00000a08+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00000a08+4*5))=0x77777777+(unsigned long)context_ptr;
writel(0x00000030&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000001b0&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000062bc,"\xd3\x58\xcc\x4a\x7f\x65\xff\x3d\xd7\xce\xf2\xb1\x7f\xf1\x09\xe8\xbd\x33\x4a\xdd\x1a\x45\x26\x35\x21\x58\xdf\x97\x28\x1a\xff\x40\x49\x2f\x47\xf1\x5f\x69\x55\x98\x86\x42\x1b\x8e\x8e\x0e\x57\x6c\x7b\x51\xab\xcd\x1e\x6b\xaa\x97\xdf\xde\x8b\xe3\xce\x26\x02\x62\x5d\x07\xcf\x84\xf9\xd5\xce\x66",72))
printf("strip: d358cc4a7f65ff3d, Pass\n");
else
printf("strip: d358cc4a7f65ff3d, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000060e0))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x000060e0+4*1))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x000060e0+4*2))=0x01060057;
*((unsigned int *)((unsigned long)context_ptr+0x000062bc))=0xf3753c4a;
*((unsigned int *)((unsigned long)context_ptr+0x000062bc+4*1))=0x802e527c;
*((unsigned int *)((unsigned long)context_ptr+0x000062bc+4*2))=0xdd893800;
*((unsigned int *)((unsigned long)context_ptr+0x000062bc+4*3))=0xdd4f555f;
*((unsigned int *)((unsigned long)context_ptr+0x000062bc+4*4))=0x41ace683;
*((unsigned int *)((unsigned long)context_ptr+0x000062bc+4*5))=0xed0e1563;
*((unsigned int *)((unsigned long)context_ptr+0x000062bc+4*6))=0x8f3ad295;
*((unsigned int *)((unsigned long)context_ptr+0x000062bc+4*7))=0xf0d0208a;
*((unsigned int *)((unsigned long)context_ptr+0x000062bc+4*8))=0xf0952ceb;
*((unsigned int *)((unsigned long)context_ptr+0x000062bc+4*9))=0xdce27ffd;
*((unsigned int *)((unsigned long)context_ptr+0x000062bc+4*10))=0xaeefade0;
*((unsigned int *)((unsigned long)context_ptr+0x000062bc+4*11))=0x2738351e;
*((unsigned int *)((unsigned long)context_ptr+0x000062bc+4*12))=0x574b4e84;
*((unsigned int *)((unsigned long)context_ptr+0x000062bc+4*13))=0x83e37a22;
*((unsigned int *)((unsigned long)context_ptr+0x000062bc+4*14))=0x59fd63c3;
*((unsigned int *)((unsigned long)context_ptr+0x000062bc+4*15))=0x60b3ad4e;
*((unsigned int *)((unsigned long)context_ptr+0x000068fc))=0x419d3668;
*((unsigned int *)((unsigned long)context_ptr+0x000068fc+4*1))=0xdd7b0c85;
*((unsigned int *)((unsigned long)context_ptr+0x000068fc+4*2))=0x032c9869;
*((unsigned int *)((unsigned long)context_ptr+0x000068fc+4*3))=0x45d12d40;
*((unsigned int *)((unsigned long)context_ptr+0x000068fc+4*4))=0x1ad8b5f7;
*((unsigned int *)((unsigned long)context_ptr+0x000068fc+4*5))=0x00345468;
*((unsigned int *)((unsigned long)context_ptr+0x00003810))=0x04c00057;
*((unsigned int *)((unsigned long)context_ptr+0x00003810+4*1))=0x00006a68;
*((unsigned int *)((unsigned long)context_ptr+0x00003810+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003810+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003810+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003810+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005f4&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000a20))=0x03800040;
*((unsigned int *)((unsigned long)context_ptr+0x00000a20+4*1))=0x000062bc;
*((unsigned int *)((unsigned long)context_ptr+0x00000a20+4*2))=0x000060e0;
*((unsigned int *)((unsigned long)context_ptr+0x00000a20+4*3))=0x02220057;
*((unsigned int *)((unsigned long)context_ptr+0x00000a20+4*4))=0x0074fb38;
*((unsigned int *)((unsigned long)context_ptr+0x00000a20+4*5))=0x00006000+(unsigned long)context_ptr;
*((unsigned int *)((unsigned long)context_ptr+0x00000a38))=0x00400017;
*((unsigned int *)((unsigned long)context_ptr+0x00000a38+4*1))=0x000068fc;
*((unsigned int *)((unsigned long)context_ptr+0x00000a38+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00000a38+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00000a38+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00000a38+4*5))=0x77777777+(unsigned long)context_ptr;
writel(0x00000030&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000001b6&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000060f0,"\x17\xef\xc1\x23\x3c\xa8\xf9\x37\xd9\x6f\xdb\x02\x85\x6b\xc9\xf6\x1a\xc0\x5c\xe1\xdd\xff\x82\x7f\x36\x0d\xe7\x1b\x6e\x19\x09\x53\x1d\x48\xfe\x3d\xc9\xc9\x10\x64\x26\x53\x21\x23\xb6\x0d\x7a\x8d\x6c\x3f\x9f\x18\x2c\x4b\x72\x33\xa6\x43\x7a\xce\xab\x9a\xd5\x67\x6e\x63\x21\x98\x7d\xcc\x9b\x58\xdb\x00\x00\x00",73))
printf("strip: 17efc1233ca8f937, Pass\n");
else
printf("strip: 17efc1233ca8f937, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006914))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x00006914+4*1))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x00006914+4*2))=0x01060058;
*((unsigned int *)((unsigned long)context_ptr+0x000060ec))=0xad57a788;
*((unsigned int *)((unsigned long)context_ptr+0x000060ec+4*1))=0x5c1155ee;
*((unsigned int *)((unsigned long)context_ptr+0x000060ec+4*2))=0x46aa2503;
*((unsigned int *)((unsigned long)context_ptr+0x000060ec+4*3))=0x5729e920;
*((unsigned int *)((unsigned long)context_ptr+0x000060ec+4*4))=0x97c1dc80;
*((unsigned int *)((unsigned long)context_ptr+0x000060ec+4*5))=0x7d3183fa;
*((unsigned int *)((unsigned long)context_ptr+0x000060ec+4*6))=0xd27e655f;
*((unsigned int *)((unsigned long)context_ptr+0x000060ec+4*7))=0x1ef0b38b;
*((unsigned int *)((unsigned long)context_ptr+0x000060ec+4*8))=0xbb9fcaba;
*((unsigned int *)((unsigned long)context_ptr+0x000060ec+4*9))=0xd5261850;
*((unsigned int *)((unsigned long)context_ptr+0x000060ec+4*10))=0x86752e7e;
*((unsigned int *)((unsigned long)context_ptr+0x000060ec+4*11))=0x992f067b;
*((unsigned int *)((unsigned long)context_ptr+0x000060ec+4*12))=0xc94fc657;
*((unsigned int *)((unsigned long)context_ptr+0x000060ec+4*13))=0x674d5290;
*((unsigned int *)((unsigned long)context_ptr+0x000060ec+4*14))=0xa3ebc712;
*((unsigned int *)((unsigned long)context_ptr+0x000060ec+4*15))=0xbf18c996;
*((unsigned int *)((unsigned long)context_ptr+0x000062fc))=0xcd9027af;
*((unsigned int *)((unsigned long)context_ptr+0x000062fc+4*1))=0x4e1a143d;
*((unsigned int *)((unsigned long)context_ptr+0x000062fc+4*2))=0xc37ad562;
*((unsigned int *)((unsigned long)context_ptr+0x000062fc+4*3))=0x69f9b33c;
*((unsigned int *)((unsigned long)context_ptr+0x000062fc+4*4))=0x0a130edc;
*((unsigned int *)((unsigned long)context_ptr+0x000062fc+4*5))=0xe1bed4dc;
*((unsigned int *)((unsigned long)context_ptr+0x00003828))=0x04c00058;
*((unsigned int *)((unsigned long)context_ptr+0x00003828+4*1))=0x000066b8;
*((unsigned int *)((unsigned long)context_ptr+0x00003828+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003828+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003828+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003828+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005f4&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000a50))=0x03800040;
*((unsigned int *)((unsigned long)context_ptr+0x00000a50+4*1))=0x000060ec;
*((unsigned int *)((unsigned long)context_ptr+0x00000a50+4*2))=0x00006914;
*((unsigned int *)((unsigned long)context_ptr+0x00000a50+4*3))=0x02220058;
*((unsigned int *)((unsigned long)context_ptr+0x00000a50+4*4))=0x009a4472;
*((unsigned int *)((unsigned long)context_ptr+0x00000a50+4*5))=0x00006000+(unsigned long)context_ptr;
*((unsigned int *)((unsigned long)context_ptr+0x00000a68))=0x00400018;
*((unsigned int *)((unsigned long)context_ptr+0x00000a68+4*1))=0x000062fc;
*((unsigned int *)((unsigned long)context_ptr+0x00000a68+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00000a68+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00000a68+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00000a68+4*5))=0x77777777+(unsigned long)context_ptr;
writel(0x00000030&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000001bc&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000064c8,"\x68\x9f\x73\xa4\xe6\x61\x6b\xcb\x0b\x56\x0f\xa7\xac\xa9\x9e\xbe\x03\xa1\xa1\xd5\xc1\x08\x97\x69\x47\x1b\x1f\x27\x3d\x7b\x9a\x42\x34\x85\x7c\x13\x3a\x64\xef\x75\x3f\xdf\xff\x27\xdf\x7d\x41\xcf\x8c\x8d\xb2\x63\xb3\xbd\xcf\x0c\x4e\x95\xaa\x98\xcd\x55\xa3\x88\xd7\x4c\x88\x3c\xec\xf6\x4d\xdc\x6f\x4a\x00\x00",74))
printf("strip: 689f73a4e6616bcb, Pass\n");
else
printf("strip: 689f73a4e6616bcb, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006314))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x00006314+4*1))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x00006314+4*2))=0x01060059;
*((unsigned int *)((unsigned long)context_ptr+0x000064c0))=0xb9b9ef43;
*((unsigned int *)((unsigned long)context_ptr+0x000064c0+4*1))=0xe14badd8;
*((unsigned int *)((unsigned long)context_ptr+0x000064c0+4*2))=0x31a5f254;
*((unsigned int *)((unsigned long)context_ptr+0x000064c0+4*3))=0xa5e1cbdb;
*((unsigned int *)((unsigned long)context_ptr+0x000064c0+4*4))=0x87211225;
*((unsigned int *)((unsigned long)context_ptr+0x000064c0+4*5))=0xb771957b;
*((unsigned int *)((unsigned long)context_ptr+0x000064c0+4*6))=0x15dba68a;
*((unsigned int *)((unsigned long)context_ptr+0x000064c0+4*7))=0x75f83cd9;
*((unsigned int *)((unsigned long)context_ptr+0x000064c0+4*8))=0x0b8ef96a;
*((unsigned int *)((unsigned long)context_ptr+0x000064c0+4*9))=0x246646e4;
*((unsigned int *)((unsigned long)context_ptr+0x000064c0+4*10))=0x9ee7a4fe;
*((unsigned int *)((unsigned long)context_ptr+0x000064c0+4*11))=0xc2f5dfdd;
*((unsigned int *)((unsigned long)context_ptr+0x000064c0+4*12))=0xecbdaaf3;
*((unsigned int *)((unsigned long)context_ptr+0x000064c0+4*13))=0x9501faf1;
*((unsigned int *)((unsigned long)context_ptr+0x000064c0+4*14))=0x2731a6f5;
*((unsigned int *)((unsigned long)context_ptr+0x000064c0+4*15))=0x5e688756;
*((unsigned int *)((unsigned long)context_ptr+0x00006710))=0x8263a416;
*((unsigned int *)((unsigned long)context_ptr+0x00006710+4*1))=0xb54bfe0d;
*((unsigned int *)((unsigned long)context_ptr+0x00006710+4*2))=0x5a5f2bcd;
*((unsigned int *)((unsigned long)context_ptr+0x00006710+4*3))=0xa6c1a82b;
*((unsigned int *)((unsigned long)context_ptr+0x00006710+4*4))=0x7f6a17bc;
*((unsigned int *)((unsigned long)context_ptr+0x00006710+4*5))=0x868a74f7;
*((unsigned int *)((unsigned long)context_ptr+0x00006710+4*6))=0x0000002d;
*((unsigned int *)((unsigned long)context_ptr+0x00003840))=0x04c00059;
*((unsigned int *)((unsigned long)context_ptr+0x00003840+4*1))=0x0000612c;
*((unsigned int *)((unsigned long)context_ptr+0x00003840+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003840+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003840+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003840+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005f4&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000a80))=0x03800040;
*((unsigned int *)((unsigned long)context_ptr+0x00000a80+4*1))=0x000064c0;
*((unsigned int *)((unsigned long)context_ptr+0x00000a80+4*2))=0x00006314;
*((unsigned int *)((unsigned long)context_ptr+0x00000a80+4*3))=0x02220059;
*((unsigned int *)((unsigned long)context_ptr+0x00000a80+4*4))=0x0099cedd;
*((unsigned int *)((unsigned long)context_ptr+0x00000a80+4*5))=0x00006000+(unsigned long)context_ptr;
*((unsigned int *)((unsigned long)context_ptr+0x00000a98))=0x00400019;
*((unsigned int *)((unsigned long)context_ptr+0x00000a98+4*1))=0x00006710;
*((unsigned int *)((unsigned long)context_ptr+0x00000a98+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00000a98+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00000a98+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00000a98+4*5))=0x77777777+(unsigned long)context_ptr;
writel(0x00000030&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000001c2&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006328,"\xdc\x95\x79\xad\xfc\xa3\xce\xcf\x43\x63\x32\x9a\xc9\x6a\x55\x6d\xb8\x0a\xec\xa9\x92\x03\x16\x26\x9d\x8f\x2a\xdc\x55\x23\x4a\xc0\x7c\xa3\x44\x9e\x3f\x03\xb7\x71\x4d\x86\x61\xce\xf8\xa6\x09\xa7\x02\x66\x17\xdd\x06\xad\x76\x82\x42\x60\x6e\x73\x7d\xd5\xa1\xdc\x84\x86\xa0\xb6\xbc\x8f\x66\x46\xbc\x0f\xf5\x00",75))
printf("strip: dc9579adfca3cecf, Pass\n");
else
printf("strip: dc9579adfca3cecf, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x0000672c))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x0000672c+4*1))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x0000672c+4*2))=0x0106005a;
*((unsigned int *)((unsigned long)context_ptr+0x00006188))=0x516ab08d;
*((unsigned int *)((unsigned long)context_ptr+0x00006188+4*1))=0x7eddf9b4;
*((unsigned int *)((unsigned long)context_ptr+0x00006188+4*2))=0x3a35a920;
*((unsigned int *)((unsigned long)context_ptr+0x00006188+4*3))=0x81b639a0;
*((unsigned int *)((unsigned long)context_ptr+0x00006188+4*4))=0xb876cd6e;
*((unsigned int *)((unsigned long)context_ptr+0x00006188+4*5))=0x36e4be9e;
*((unsigned int *)((unsigned long)context_ptr+0x00006188+4*6))=0xbd3701ad;
*((unsigned int *)((unsigned long)context_ptr+0x00006188+4*7))=0xe38e374e;
*((unsigned int *)((unsigned long)context_ptr+0x00006188+4*8))=0x214b368a;
*((unsigned int *)((unsigned long)context_ptr+0x00006188+4*9))=0x87a70c54;
*((unsigned int *)((unsigned long)context_ptr+0x00006188+4*10))=0xdc250c1c;
*((unsigned int *)((unsigned long)context_ptr+0x00006188+4*11))=0x30704ef6;
*((unsigned int *)((unsigned long)context_ptr+0x00006188+4*12))=0x3b0382ba;
*((unsigned int *)((unsigned long)context_ptr+0x00006188+4*13))=0xe1df7002;
*((unsigned int *)((unsigned long)context_ptr+0x00006188+4*14))=0x82e9f59a;
*((unsigned int *)((unsigned long)context_ptr+0x00006188+4*15))=0x8c2a5064;
*((unsigned int *)((unsigned long)context_ptr+0x00006500))=0x37080279;
*((unsigned int *)((unsigned long)context_ptr+0x00006500+4*1))=0xece67342;
*((unsigned int *)((unsigned long)context_ptr+0x00006500+4*2))=0xe68ead45;
*((unsigned int *)((unsigned long)context_ptr+0x00006500+4*3))=0x6b98714d;
*((unsigned int *)((unsigned long)context_ptr+0x00006500+4*4))=0xd0bd336b;
*((unsigned int *)((unsigned long)context_ptr+0x00006500+4*5))=0xdce190a6;
*((unsigned int *)((unsigned long)context_ptr+0x00006500+4*6))=0x0000ad05;
*((unsigned int *)((unsigned long)context_ptr+0x00003858))=0x04c0005a;
*((unsigned int *)((unsigned long)context_ptr+0x00003858+4*1))=0x00006ac0;
*((unsigned int *)((unsigned long)context_ptr+0x00003858+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003858+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003858+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003858+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005f4&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000ab0))=0x03800040;
*((unsigned int *)((unsigned long)context_ptr+0x00000ab0+4*1))=0x00006188;
*((unsigned int *)((unsigned long)context_ptr+0x00000ab0+4*2))=0x0000672c;
*((unsigned int *)((unsigned long)context_ptr+0x00000ab0+4*3))=0x0222005a;
*((unsigned int *)((unsigned long)context_ptr+0x00000ab0+4*4))=0x000476d9;
*((unsigned int *)((unsigned long)context_ptr+0x00000ab0+4*5))=0x00006000+(unsigned long)context_ptr;
*((unsigned int *)((unsigned long)context_ptr+0x00000ac8))=0x0040001a;
*((unsigned int *)((unsigned long)context_ptr+0x00000ac8+4*1))=0x00006500;
*((unsigned int *)((unsigned long)context_ptr+0x00000ac8+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00000ac8+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00000ac8+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00000ac8+4*5))=0x77777777+(unsigned long)context_ptr;
writel(0x00000030&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000001c8&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x0000652c,"\xe8\xec\xdd\x32\x9a\x88\x0d\x3a\x92\xdb\xc1\xcf\x74\xf4\x9c\x47\x54\x5f\x21\xa4\x89\xd2\x18\x27\x56\x37\x40\x5a\x5a\x81\xbd\x85\xe4\x10\xa8\xa9\xee\x93\xb5\x75\x12\x19\x74\xa0\x61\x2f\xde\xf5\x58\x47\x24\xf9\x91\x8b\x50\xcc\x30\xaa\xab\xef\xd5\x71\xb9\x81\x22\x8a\xb8\xed\x8e\x43\x83\xb1\x48\x21\x31\x4c",76))
printf("strip: e8ecdd329a880d3a, Pass\n");
else
printf("strip: e8ecdd329a880d3a, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000061c8))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x000061c8+4*1))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x000061c8+4*2))=0x0106005b;
*((unsigned int *)((unsigned long)context_ptr+0x00006738))=0x775dde0a;
*((unsigned int *)((unsigned long)context_ptr+0x00006738+4*1))=0x5b66cd6f;
*((unsigned int *)((unsigned long)context_ptr+0x00006738+4*2))=0x75a862ad;
*((unsigned int *)((unsigned long)context_ptr+0x00006738+4*3))=0xf1406791;
*((unsigned int *)((unsigned long)context_ptr+0x00006738+4*4))=0xa249a296;
*((unsigned int *)((unsigned long)context_ptr+0x00006738+4*5))=0x418a948d;
*((unsigned int *)((unsigned long)context_ptr+0x00006738+4*6))=0x4d4f14a7;
*((unsigned int *)((unsigned long)context_ptr+0x00006738+4*7))=0xda34006f;
*((unsigned int *)((unsigned long)context_ptr+0x00006738+4*8))=0x839b03ca;
*((unsigned int *)((unsigned long)context_ptr+0x00006738+4*9))=0x615cbd18;
*((unsigned int *)((unsigned long)context_ptr+0x00006738+4*10))=0xd7d59b5d;
*((unsigned int *)((unsigned long)context_ptr+0x00006738+4*11))=0x9f0fe550;
*((unsigned int *)((unsigned long)context_ptr+0x00006738+4*12))=0x6a6af4b3;
*((unsigned int *)((unsigned long)context_ptr+0x00006738+4*13))=0x59f757a0;
*((unsigned int *)((unsigned long)context_ptr+0x00006738+4*14))=0xff415625;
*((unsigned int *)((unsigned long)context_ptr+0x00006738+4*15))=0x4846bbe3;
*((unsigned int *)((unsigned long)context_ptr+0x0000651c))=0x1a389526;
*((unsigned int *)((unsigned long)context_ptr+0x0000651c+4*1))=0x21a044e6;
*((unsigned int *)((unsigned long)context_ptr+0x0000651c+4*2))=0x02462348;
*((unsigned int *)((unsigned long)context_ptr+0x0000651c+4*3))=0xf2a0f05c;
*((unsigned int *)((unsigned long)context_ptr+0x0000651c+4*4))=0x7c270f73;
*((unsigned int *)((unsigned long)context_ptr+0x0000651c+4*5))=0x7743173a;
*((unsigned int *)((unsigned long)context_ptr+0x0000651c+4*6))=0x00f0bf6b;
*((unsigned int *)((unsigned long)context_ptr+0x00003870))=0x04c0005b;
*((unsigned int *)((unsigned long)context_ptr+0x00003870+4*1))=0x00006320;
*((unsigned int *)((unsigned long)context_ptr+0x00003870+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003870+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003870+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003870+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005f4&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000ae0))=0x03800040;
*((unsigned int *)((unsigned long)context_ptr+0x00000ae0+4*1))=0x00006738;
*((unsigned int *)((unsigned long)context_ptr+0x00000ae0+4*2))=0x000061c8;
*((unsigned int *)((unsigned long)context_ptr+0x00000ae0+4*3))=0x0222005b;
*((unsigned int *)((unsigned long)context_ptr+0x00000ae0+4*4))=0x00347a56;
*((unsigned int *)((unsigned long)context_ptr+0x00000ae0+4*5))=0x00006000+(unsigned long)context_ptr;
*((unsigned int *)((unsigned long)context_ptr+0x00000af8))=0x0040001b;
*((unsigned int *)((unsigned long)context_ptr+0x00000af8+4*1))=0x0000651c;
*((unsigned int *)((unsigned long)context_ptr+0x00000af8+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00000af8+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00000af8+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00000af8+4*5))=0x77777777+(unsigned long)context_ptr;
writel(0x00000030&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000001ce&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006920,"\x0a\x64\xc2\x47\xfd\x81\xc1\x91\x91\xc8\xc8\x34\x29\x2f\x3b\x14\x3b\x65\xa1\x07\x9d\xb5\xe4\xa7\x91\x4c\x61\x9c\xcd\x59\xaa\x5d\x9e\x0b\x19\xa8\xdb\x4f\xbd\xc5\x11\xab\x6f\x33\x34\xd2\xad\x67\x79\x29\xfd\x86\x12\x69\xe0\x51\xbb\x14\xc4\x9c\x74\x31\x7d\xcb\x0d\x40\x4a\x4b\xab\xed\x97\xa7\x7e\x78\xb8\xaf\x5d\x00\x00\x00",77))
printf("strip: 0a64c247fd81c191, Pass\n");
else
printf("strip: 0a64c247fd81c191, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006008))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x00006008+4*1))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x00006008+4*2))=0x0106005c;
*((unsigned int *)((unsigned long)context_ptr+0x00006538))=0x4254d4e1;
*((unsigned int *)((unsigned long)context_ptr+0x00006538+4*1))=0x7766c719;
*((unsigned int *)((unsigned long)context_ptr+0x00006538+4*2))=0x8fd71118;
*((unsigned int *)((unsigned long)context_ptr+0x00006538+4*3))=0x445c302a;
*((unsigned int *)((unsigned long)context_ptr+0x00006538+4*4))=0x71f40122;
*((unsigned int *)((unsigned long)context_ptr+0x00006538+4*5))=0xe4b390a9;
*((unsigned int *)((unsigned long)context_ptr+0x00006538+4*6))=0x4b03a854;
*((unsigned int *)((unsigned long)context_ptr+0x00006538+4*7))=0xe4db7106;
*((unsigned int *)((unsigned long)context_ptr+0x00006538+4*8))=0x1579d8ab;
*((unsigned int *)((unsigned long)context_ptr+0x00006538+4*9))=0x2039b777;
*((unsigned int *)((unsigned long)context_ptr+0x00006538+4*10))=0xfea572fc;
*((unsigned int *)((unsigned long)context_ptr+0x00006538+4*11))=0x7f8a6ab2;
*((unsigned int *)((unsigned long)context_ptr+0x00006538+4*12))=0x1d4f9173;
*((unsigned int *)((unsigned long)context_ptr+0x00006538+4*13))=0x70b0e7f6;
*((unsigned int *)((unsigned long)context_ptr+0x00006538+4*14))=0xeca477e3;
*((unsigned int *)((unsigned long)context_ptr+0x00006538+4*15))=0x69efc42d;
*((unsigned int *)((unsigned long)context_ptr+0x00006920))=0x55ee548f;
*((unsigned int *)((unsigned long)context_ptr+0x00006920+4*1))=0x2818643e;
*((unsigned int *)((unsigned long)context_ptr+0x00006920+4*2))=0x0955b618;
*((unsigned int *)((unsigned long)context_ptr+0x00006920+4*3))=0xeacf4cb0;
*((unsigned int *)((unsigned long)context_ptr+0x00006920+4*4))=0x64ecee95;
*((unsigned int *)((unsigned long)context_ptr+0x00006920+4*5))=0xf7a105b6;
*((unsigned int *)((unsigned long)context_ptr+0x00006920+4*6))=0x618a4c91;
*((unsigned int *)((unsigned long)context_ptr+0x00003888))=0x04c0005c;
*((unsigned int *)((unsigned long)context_ptr+0x00003888+4*1))=0x00006b1c;
*((unsigned int *)((unsigned long)context_ptr+0x00003888+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003888+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003888+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003888+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005f4&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000b10))=0x03800040;
*((unsigned int *)((unsigned long)context_ptr+0x00000b10+4*1))=0x00006538;
*((unsigned int *)((unsigned long)context_ptr+0x00000b10+4*2))=0x00006008;
*((unsigned int *)((unsigned long)context_ptr+0x00000b10+4*3))=0x0222005c;
*((unsigned int *)((unsigned long)context_ptr+0x00000b10+4*4))=0x00674187;
*((unsigned int *)((unsigned long)context_ptr+0x00000b10+4*5))=0x00006000+(unsigned long)context_ptr;
*((unsigned int *)((unsigned long)context_ptr+0x00000b28))=0x0040001c;
*((unsigned int *)((unsigned long)context_ptr+0x00000b28+4*1))=0x00006920;
*((unsigned int *)((unsigned long)context_ptr+0x00000b28+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00000b28+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00000b28+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00000b28+4*5))=0x77777777+(unsigned long)context_ptr;
writel(0x00000030&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000001d4&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006390,"\x14\xba\xdf\x95\xc4\xb0\x89\x74\x8e\x47\x01\xa4\xe6\x5a\x6f\xb3\x08\x3f\xc5\xa6\x0b\x60\x98\x1d\xf0\x2c\x9b\x11\x40\x25\xc3\xfa\xe4\x37\xa4\xe8\xa8\x0f\x72\x54\xa5\x0f\xa8\x0c\x0e\x3a\xdd\xc4\x43\x02\x42\xee\x8e\x14\xb9\xa1\xd8\xfa\xd8\xad\xe0\x9e\x36\x83\x4c\x3f\x2f\x11\x49\xe0\x82\x87\x1c\xf5\x1e\xf7\x2f\x0c\x00\x00",78))
printf("strip: 14badf95c4b08974, Pass\n");
else
printf("strip: 14badf95c4b08974, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006014))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x00006014+4*1))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x00006014+4*2))=0x0106005d;
*((unsigned int *)((unsigned long)context_ptr+0x0000637c))=0xcf6b42c4;
*((unsigned int *)((unsigned long)context_ptr+0x0000637c+4*1))=0xb46fcd4f;
*((unsigned int *)((unsigned long)context_ptr+0x0000637c+4*2))=0x9022742d;
*((unsigned int *)((unsigned long)context_ptr+0x0000637c+4*3))=0x46ecf121;
*((unsigned int *)((unsigned long)context_ptr+0x0000637c+4*4))=0x93fe0151;
*((unsigned int *)((unsigned long)context_ptr+0x0000637c+4*5))=0xa644fe51;
*((unsigned int *)((unsigned long)context_ptr+0x0000637c+4*6))=0xb4411e6d;
*((unsigned int *)((unsigned long)context_ptr+0x0000637c+4*7))=0x092e503b;
*((unsigned int *)((unsigned long)context_ptr+0x0000637c+4*8))=0xaf18320d;
*((unsigned int *)((unsigned long)context_ptr+0x0000637c+4*9))=0x814e7ee2;
*((unsigned int *)((unsigned long)context_ptr+0x0000637c+4*10))=0xc528a1b7;
*((unsigned int *)((unsigned long)context_ptr+0x0000637c+4*11))=0x94b180e6;
*((unsigned int *)((unsigned long)context_ptr+0x0000637c+4*12))=0x0df6622a;
*((unsigned int *)((unsigned long)context_ptr+0x0000637c+4*13))=0x7e919ec3;
*((unsigned int *)((unsigned long)context_ptr+0x0000637c+4*14))=0x82f19c26;
*((unsigned int *)((unsigned long)context_ptr+0x0000637c+4*15))=0xd22cafd9;
*((unsigned int *)((unsigned long)context_ptr+0x000063bc))=0x6929f12b;
*((unsigned int *)((unsigned long)context_ptr+0x000063bc+4*1))=0xa99d5cd3;
*((unsigned int *)((unsigned long)context_ptr+0x000063bc+4*2))=0x8095674a;
*((unsigned int *)((unsigned long)context_ptr+0x000063bc+4*3))=0xaf15b9f0;
*((unsigned int *)((unsigned long)context_ptr+0x000063bc+4*4))=0xc6538697;
*((unsigned int *)((unsigned long)context_ptr+0x000063bc+4*5))=0xb77b53e8;
*((unsigned int *)((unsigned long)context_ptr+0x000063bc+4*6))=0xe09348c2;
*((unsigned int *)((unsigned long)context_ptr+0x000063bc+4*7))=0x00000012;
*((unsigned int *)((unsigned long)context_ptr+0x000038a0))=0x04c0005d;
*((unsigned int *)((unsigned long)context_ptr+0x000038a0+4*1))=0x00006778;
*((unsigned int *)((unsigned long)context_ptr+0x000038a0+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000038a0+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000038a0+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000038a0+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005f4&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000b40))=0x03800040;
*((unsigned int *)((unsigned long)context_ptr+0x00000b40+4*1))=0x0000637c;
*((unsigned int *)((unsigned long)context_ptr+0x00000b40+4*2))=0x00006014;
*((unsigned int *)((unsigned long)context_ptr+0x00000b40+4*3))=0x0222005d;
*((unsigned int *)((unsigned long)context_ptr+0x00000b40+4*4))=0x00795300;
*((unsigned int *)((unsigned long)context_ptr+0x00000b40+4*5))=0x00006000+(unsigned long)context_ptr;
*((unsigned int *)((unsigned long)context_ptr+0x00000b58))=0x0040001d;
*((unsigned int *)((unsigned long)context_ptr+0x00000b58+4*1))=0x000063bc;
*((unsigned int *)((unsigned long)context_ptr+0x00000b58+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00000b58+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00000b58+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00000b58+4*5))=0x77777777+(unsigned long)context_ptr;
writel(0x00000030&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000001da&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006970,"\x17\x41\x0e\xc3\x6c\x43\xe6\x97\xf9\xae\x1c\x22\x1e\x5c\xc9\xea\x0d\x68\xf1\xcc\x47\xe5\x23\x55\x34\x6c\x88\x12\x2d\x9e\xd7\x16\xf4\x80\xc6\x0e\x5b\x76\x90\xf6\x81\xe9\xf7\xe4\x59\xde\x50\xb7\xb2\x9a\xe6\xcb\xd0\x6c\xe2\xba\x50\x6c\x3d\xd9\x5f\x60\x63\x8f\x48\xd1\xab\xca\x11\x60\x35\x31\x56\xda\x60\x10\xd9\xc9\x8c\x00",79))
printf("strip: 17410ec36c43e697, Pass\n");
else
printf("strip: 17410ec36c43e697, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006020))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x00006020+4*1))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x00006020+4*2))=0x0106005e;
*((unsigned int *)((unsigned long)context_ptr+0x00006578))=0xe8bec521;
*((unsigned int *)((unsigned long)context_ptr+0x00006578+4*1))=0x79f43459;
*((unsigned int *)((unsigned long)context_ptr+0x00006578+4*2))=0x39ce1791;
*((unsigned int *)((unsigned long)context_ptr+0x00006578+4*3))=0x9a2876f3;
*((unsigned int *)((unsigned long)context_ptr+0x00006578+4*4))=0x817c1c3f;
*((unsigned int *)((unsigned long)context_ptr+0x00006578+4*5))=0xd337e6b6;
*((unsigned int *)((unsigned long)context_ptr+0x00006578+4*6))=0x62c02074;
*((unsigned int *)((unsigned long)context_ptr+0x00006578+4*7))=0x943f008f;
*((unsigned int *)((unsigned long)context_ptr+0x00006578+4*8))=0x38862107;
*((unsigned int *)((unsigned long)context_ptr+0x00006578+4*9))=0x5f2ae4b4;
*((unsigned int *)((unsigned long)context_ptr+0x00006578+4*10))=0x24b6f012;
*((unsigned int *)((unsigned long)context_ptr+0x00006578+4*11))=0x284c9d3b;
*((unsigned int *)((unsigned long)context_ptr+0x00006578+4*12))=0x65b346d5;
*((unsigned int *)((unsigned long)context_ptr+0x00006578+4*13))=0x69b4dd3d;
*((unsigned int *)((unsigned long)context_ptr+0x00006578+4*14))=0xc0f923a0;
*((unsigned int *)((unsigned long)context_ptr+0x00006578+4*15))=0x51d634d2;
*((unsigned int *)((unsigned long)context_ptr+0x000067d8))=0xaedfaa57;
*((unsigned int *)((unsigned long)context_ptr+0x000067d8+4*1))=0xf122d34a;
*((unsigned int *)((unsigned long)context_ptr+0x000067d8+4*2))=0x75358fb4;
*((unsigned int *)((unsigned long)context_ptr+0x000067d8+4*3))=0xd2c3876c;
*((unsigned int *)((unsigned long)context_ptr+0x000067d8+4*4))=0xb6d09d7b;
*((unsigned int *)((unsigned long)context_ptr+0x000067d8+4*5))=0xd40f6799;
*((unsigned int *)((unsigned long)context_ptr+0x000067d8+4*6))=0x00369133;
*((unsigned int *)((unsigned long)context_ptr+0x000067d8+4*7))=0x00008a67;
*((unsigned int *)((unsigned long)context_ptr+0x000038b8))=0x04c0005e;
*((unsigned int *)((unsigned long)context_ptr+0x000038b8+4*1))=0x0000693c;
*((unsigned int *)((unsigned long)context_ptr+0x000038b8+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000038b8+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000038b8+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000038b8+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005f4&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000b70))=0x03800040;
*((unsigned int *)((unsigned long)context_ptr+0x00000b70+4*1))=0x00006578;
*((unsigned int *)((unsigned long)context_ptr+0x00000b70+4*2))=0x00006020;
*((unsigned int *)((unsigned long)context_ptr+0x00000b70+4*3))=0x0222005e;
*((unsigned int *)((unsigned long)context_ptr+0x00000b70+4*4))=0x00e37872;
*((unsigned int *)((unsigned long)context_ptr+0x00000b70+4*5))=0x00006000+(unsigned long)context_ptr;
*((unsigned int *)((unsigned long)context_ptr+0x00000b88))=0x0040001e;
*((unsigned int *)((unsigned long)context_ptr+0x00000b88+4*1))=0x000067d8;
*((unsigned int *)((unsigned long)context_ptr+0x00000b88+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00000b88+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00000b88+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00000b88+4*5))=0x77777777+(unsigned long)context_ptr;
writel(0x00000030&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000001e0&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000065c8,"\xee\xb4\xb2\x53\x34\xb6\x4a\x9d\x18\x70\xa2\x8c\xa3\x3a\x74\x10\x13\x35\xa5\xcb\x99\x5b\x01\xb1\xd9\x02\x9e\x58\x69\xbb\x6e\x8c\xb1\xa8\x79\x89\xa5\x03\x05\x77\xb5\xf3\x86\xac\xeb\x19\x20\x7a\x91\x4d\x62\xde\x88\x92\xed\x98\x76\x2d\x30\x81\x0b\x82\xe1\x63\xd6\xc0\xd0\x56\x9c\xa7\x19\x2b\xac\xb8\x0a\x7c\x7a\x6c\xc3\xf8",80))
printf("strip: eeb4b25334b64a9d, Pass\n");
else
printf("strip: eeb4b25334b64a9d, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x0000602c))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x0000602c+4*1))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x0000602c+4*2))=0x0106005f;
*((unsigned int *)((unsigned long)context_ptr+0x000061d4))=0x1d456915;
*((unsigned int *)((unsigned long)context_ptr+0x000061d4+4*1))=0x8c8ecc3c;
*((unsigned int *)((unsigned long)context_ptr+0x000061d4+4*2))=0xd57cd33b;
*((unsigned int *)((unsigned long)context_ptr+0x000061d4+4*3))=0x9b3a0070;
*((unsigned int *)((unsigned long)context_ptr+0x000061d4+4*4))=0x64997c2a;
*((unsigned int *)((unsigned long)context_ptr+0x000061d4+4*5))=0x7ecf0f07;
*((unsigned int *)((unsigned long)context_ptr+0x000061d4+4*6))=0x0e523418;
*((unsigned int *)((unsigned long)context_ptr+0x000061d4+4*7))=0x79c7809b;
*((unsigned int *)((unsigned long)context_ptr+0x000061d4+4*8))=0x53d3cd8b;
*((unsigned int *)((unsigned long)context_ptr+0x000061d4+4*9))=0x05c5e519;
*((unsigned int *)((unsigned long)context_ptr+0x000061d4+4*10))=0x0167dd0f;
*((unsigned int *)((unsigned long)context_ptr+0x000061d4+4*11))=0x3efbff90;
*((unsigned int *)((unsigned long)context_ptr+0x000061d4+4*12))=0x9dd12fbc;
*((unsigned int *)((unsigned long)context_ptr+0x000061d4+4*13))=0x23d4afd1;
*((unsigned int *)((unsigned long)context_ptr+0x000061d4+4*14))=0x381f2f45;
*((unsigned int *)((unsigned long)context_ptr+0x000061d4+4*15))=0x02587315;
*((unsigned int *)((unsigned long)context_ptr+0x000063dc))=0x040bb332;
*((unsigned int *)((unsigned long)context_ptr+0x000063dc+4*1))=0x4209eadb;
*((unsigned int *)((unsigned long)context_ptr+0x000063dc+4*2))=0xf6a0945b;
*((unsigned int *)((unsigned long)context_ptr+0x000063dc+4*3))=0xd6606645;
*((unsigned int *)((unsigned long)context_ptr+0x000063dc+4*4))=0x7da9e831;
*((unsigned int *)((unsigned long)context_ptr+0x000063dc+4*5))=0xdd0b32b8;
*((unsigned int *)((unsigned long)context_ptr+0x000063dc+4*6))=0x959fdf5b;
*((unsigned int *)((unsigned long)context_ptr+0x000063dc+4*7))=0x00624de1;
*((unsigned int *)((unsigned long)context_ptr+0x000038d0))=0x04c0005f;
*((unsigned int *)((unsigned long)context_ptr+0x000038d0+4*1))=0x000065b8;
*((unsigned int *)((unsigned long)context_ptr+0x000038d0+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000038d0+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000038d0+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000038d0+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005f4&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000ba0))=0x03800040;
*((unsigned int *)((unsigned long)context_ptr+0x00000ba0+4*1))=0x000061d4;
*((unsigned int *)((unsigned long)context_ptr+0x00000ba0+4*2))=0x0000602c;
*((unsigned int *)((unsigned long)context_ptr+0x00000ba0+4*3))=0x0222005f;
*((unsigned int *)((unsigned long)context_ptr+0x00000ba0+4*4))=0x007bd042;
*((unsigned int *)((unsigned long)context_ptr+0x00000ba0+4*5))=0x00006000+(unsigned long)context_ptr;
*((unsigned int *)((unsigned long)context_ptr+0x00000bb8))=0x0040001f;
*((unsigned int *)((unsigned long)context_ptr+0x00000bb8+4*1))=0x000063dc;
*((unsigned int *)((unsigned long)context_ptr+0x00000bb8+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00000bb8+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00000bb8+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00000bb8+4*5))=0x77777777+(unsigned long)context_ptr;
writel(0x00000030&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000001e6&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000069c0,"\xeb\xea\xff\x41\x37\x9d\x5e\x65\xc5\xad\xda\xce\x7d\x1a\x6c\xca\x5d\xd7\x66\xd1\xc2\xab\x01\xec\x5d\x17\x03\xdc\x6b\x96\xfc\xef\xa1\xbb\xa4\x6b\x1d\x35\x4c\x36\xee\x34\x3c\xb2\xf8\xa3\x4b\xd0\x28\xa6\x7e\xc0\x7c\x9f\x00\xd7\xb9\x32\xf2\xfd\xa0\xd6\xfd\x4e\x2f\x52\xf7\x4b\x73\xd9\x2d\x74\x43\x6b\xf5\x6f\x0f\xe4\xdb\x57\x0c\x00\x00\x00",81))
printf("strip: ebeaff41379d5e65, Pass\n");
else
printf("strip: ebeaff41379d5e65, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006038))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x00006038+4*1))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x00006038+4*2))=0x01060060;
*((unsigned int *)((unsigned long)context_ptr+0x000063fc))=0x39ee53b4;
*((unsigned int *)((unsigned long)context_ptr+0x000063fc+4*1))=0x834081bf;
*((unsigned int *)((unsigned long)context_ptr+0x000063fc+4*2))=0x43358550;
*((unsigned int *)((unsigned long)context_ptr+0x000063fc+4*3))=0xdb64dc3e;
*((unsigned int *)((unsigned long)context_ptr+0x000063fc+4*4))=0x67aa5260;
*((unsigned int *)((unsigned long)context_ptr+0x000063fc+4*5))=0xf8b3a5d1;
*((unsigned int *)((unsigned long)context_ptr+0x000063fc+4*6))=0xdd7557d8;
*((unsigned int *)((unsigned long)context_ptr+0x000063fc+4*7))=0x158b89e4;
*((unsigned int *)((unsigned long)context_ptr+0x000063fc+4*8))=0x04531e36;
*((unsigned int *)((unsigned long)context_ptr+0x000063fc+4*9))=0x1a5c0081;
*((unsigned int *)((unsigned long)context_ptr+0x000063fc+4*10))=0x0143aa3e;
*((unsigned int *)((unsigned long)context_ptr+0x000063fc+4*11))=0x44e189d3;
*((unsigned int *)((unsigned long)context_ptr+0x000063fc+4*12))=0xe5810751;
*((unsigned int *)((unsigned long)context_ptr+0x000063fc+4*13))=0xaf3d9300;
*((unsigned int *)((unsigned long)context_ptr+0x000063fc+4*14))=0x62e07bec;
*((unsigned int *)((unsigned long)context_ptr+0x000063fc+4*15))=0xcda86c37;
*((unsigned int *)((unsigned long)context_ptr+0x0000699c))=0x21cb12ad;
*((unsigned int *)((unsigned long)context_ptr+0x0000699c+4*1))=0x312c361d;
*((unsigned int *)((unsigned long)context_ptr+0x0000699c+4*2))=0x86dc8933;
*((unsigned int *)((unsigned long)context_ptr+0x0000699c+4*3))=0x46fdc8a8;
*((unsigned int *)((unsigned long)context_ptr+0x0000699c+4*4))=0xcb3132f1;
*((unsigned int *)((unsigned long)context_ptr+0x0000699c+4*5))=0xb3e7e614;
*((unsigned int *)((unsigned long)context_ptr+0x0000699c+4*6))=0x58127ab2;
*((unsigned int *)((unsigned long)context_ptr+0x0000699c+4*7))=0x2c4e96c2;
*((unsigned int *)((unsigned long)context_ptr+0x000038e8))=0x04c00060;
*((unsigned int *)((unsigned long)context_ptr+0x000038e8+4*1))=0x00006b78;
*((unsigned int *)((unsigned long)context_ptr+0x000038e8+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000038e8+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000038e8+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000038e8+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005f4&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000bd0))=0x03800040;
*((unsigned int *)((unsigned long)context_ptr+0x00000bd0+4*1))=0x000063fc;
*((unsigned int *)((unsigned long)context_ptr+0x00000bd0+4*2))=0x00006038;
*((unsigned int *)((unsigned long)context_ptr+0x00000bd0+4*3))=0x02220060;
*((unsigned int *)((unsigned long)context_ptr+0x00000bd0+4*4))=0x00eb412b;
*((unsigned int *)((unsigned long)context_ptr+0x00000bd0+4*5))=0x00006000+(unsigned long)context_ptr;
*((unsigned int *)((unsigned long)context_ptr+0x00000be8))=0x00400020;
*((unsigned int *)((unsigned long)context_ptr+0x00000be8+4*1))=0x0000699c;
*((unsigned int *)((unsigned long)context_ptr+0x00000be8+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00000be8+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00000be8+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00000be8+4*5))=0x77777777+(unsigned long)context_ptr;
writel(0x00000030&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000001ec&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006214,"\x69\x08\x8a\xa3\x5a\xe6\xf3\x78\x81\x6c\xaf\x0f\x4e\xcc\x31\x89\x37\x1d\x67\x8c\x43\x56\x73\xba\x26\x96\x99\xf9\x9b\x68\x7b\x9d\x88\xac\x4b\x3f\xfa\xf1\xbd\xfb\xfe\x45\x58\xeb\xb7\x26\xc9\x31\x34\x9d\x35\x61\x29\xb0\x9d\xe8\x18\xfc\x4e\x07\x59\xf2\x4a\x7e\x46\xad\x5f\xec\x1b\xa0\xfc\x5e\x88\xc6\x25\x79\xda\xe1\x86\xcc\x88\xae\x00\x00",82))
printf("strip: 69088aa35ae6f378, Pass\n");
else
printf("strip: 69088aa35ae6f378, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006044))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x00006044+4*1))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x00006044+4*2))=0x01060061;
*((unsigned int *)((unsigned long)context_ptr+0x0000643c))=0x6abf5c35;
*((unsigned int *)((unsigned long)context_ptr+0x0000643c+4*1))=0xdceef52c;
*((unsigned int *)((unsigned long)context_ptr+0x0000643c+4*2))=0xa712fc7d;
*((unsigned int *)((unsigned long)context_ptr+0x0000643c+4*3))=0x7b8f5808;
*((unsigned int *)((unsigned long)context_ptr+0x0000643c+4*4))=0xe3e2ef6f;
*((unsigned int *)((unsigned long)context_ptr+0x0000643c+4*5))=0x5ea933c7;
*((unsigned int *)((unsigned long)context_ptr+0x0000643c+4*6))=0xd39858e3;
*((unsigned int *)((unsigned long)context_ptr+0x0000643c+4*7))=0x455b1f54;
*((unsigned int *)((unsigned long)context_ptr+0x0000643c+4*8))=0x95dcfa59;
*((unsigned int *)((unsigned long)context_ptr+0x0000643c+4*9))=0x40ee81d7;
*((unsigned int *)((unsigned long)context_ptr+0x0000643c+4*10))=0x791c90e6;
*((unsigned int *)((unsigned long)context_ptr+0x0000643c+4*11))=0x2bc93850;
*((unsigned int *)((unsigned long)context_ptr+0x0000643c+4*12))=0x2f8c8da0;
*((unsigned int *)((unsigned long)context_ptr+0x0000643c+4*13))=0xed8e79b3;
*((unsigned int *)((unsigned long)context_ptr+0x0000643c+4*14))=0xfa809cfe;
*((unsigned int *)((unsigned long)context_ptr+0x0000643c+4*15))=0x50b42a08;
*((unsigned int *)((unsigned long)context_ptr+0x00006618))=0x97679f7f;
*((unsigned int *)((unsigned long)context_ptr+0x00006618+4*1))=0x29a32851;
*((unsigned int *)((unsigned long)context_ptr+0x00006618+4*2))=0x19c6d92b;
*((unsigned int *)((unsigned long)context_ptr+0x00006618+4*3))=0x9fd3d2bc;
*((unsigned int *)((unsigned long)context_ptr+0x00006618+4*4))=0x94529c89;
*((unsigned int *)((unsigned long)context_ptr+0x00006618+4*5))=0xd61b71ca;
*((unsigned int *)((unsigned long)context_ptr+0x00006618+4*6))=0xcda8714a;
*((unsigned int *)((unsigned long)context_ptr+0x00006618+4*7))=0xf71b62a3;
*((unsigned int *)((unsigned long)context_ptr+0x00006618+4*8))=0x0000007f;
*((unsigned int *)((unsigned long)context_ptr+0x00003900))=0x04c00061;
*((unsigned int *)((unsigned long)context_ptr+0x00003900+4*1))=0x00006bd8;
*((unsigned int *)((unsigned long)context_ptr+0x00003900+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003900+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003900+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003900+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005f4&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000c00))=0x03800040;
*((unsigned int *)((unsigned long)context_ptr+0x00000c00+4*1))=0x0000643c;
*((unsigned int *)((unsigned long)context_ptr+0x00000c00+4*2))=0x00006044;
*((unsigned int *)((unsigned long)context_ptr+0x00000c00+4*3))=0x02220061;
*((unsigned int *)((unsigned long)context_ptr+0x00000c00+4*4))=0x00f1bd04;
*((unsigned int *)((unsigned long)context_ptr+0x00000c00+4*5))=0x00006000+(unsigned long)context_ptr;
*((unsigned int *)((unsigned long)context_ptr+0x00000c18))=0x00400021;
*((unsigned int *)((unsigned long)context_ptr+0x00000c18+4*1))=0x00006618;
*((unsigned int *)((unsigned long)context_ptr+0x00000c18+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00000c18+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00000c18+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00000c18+4*5))=0x77777777+(unsigned long)context_ptr;
writel(0x00000030&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000001f2&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006a14,"\xc6\x8b\x69\x69\x6c\x8d\x3e\xfa\xdc\x56\x88\xa6\x7e\x2c\xa4\xaa\x96\x85\x78\xfa\x19\xe2\x00\xc2\x75\x88\x0d\xf4\x2e\xd3\xfe\xe3\xa2\x26\x97\xad\xed\xaf\x29\x09\xce\x5a\x55\x59\xec\xd6\xca\x7c\xfb\x94\xe3\xf7\x9a\x97\xf6\x07\x89\x1e\xd1\xef\x8f\x4c\xe6\x1a\xc9\x0a\xc6\xc3\xca\xa9\x2e\xd2\x39\xd4\xa0\xd7\x89\x03\xec\x91\x72\x75\x90\x00",83))
printf("strip: c68b69696c8d3efa, Pass\n");
else
printf("strip: c68b69696c8d3efa, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006050))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x00006050+4*1))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x00006050+4*2))=0x01060062;
*((unsigned int *)((unsigned long)context_ptr+0x000067f8))=0x4a87fbf0;
*((unsigned int *)((unsigned long)context_ptr+0x000067f8+4*1))=0x0a460518;
*((unsigned int *)((unsigned long)context_ptr+0x000067f8+4*2))=0xd5d17ab7;
*((unsigned int *)((unsigned long)context_ptr+0x000067f8+4*3))=0xa7877b79;
*((unsigned int *)((unsigned long)context_ptr+0x000067f8+4*4))=0x0946f579;
*((unsigned int *)((unsigned long)context_ptr+0x000067f8+4*5))=0x463016f8;
*((unsigned int *)((unsigned long)context_ptr+0x000067f8+4*6))=0xd8a750d7;
*((unsigned int *)((unsigned long)context_ptr+0x000067f8+4*7))=0x05833a8b;
*((unsigned int *)((unsigned long)context_ptr+0x000067f8+4*8))=0x0f662e5d;
*((unsigned int *)((unsigned long)context_ptr+0x000067f8+4*9))=0x98ceb0ab;
*((unsigned int *)((unsigned long)context_ptr+0x000067f8+4*10))=0xb2fb251f;
*((unsigned int *)((unsigned long)context_ptr+0x000067f8+4*11))=0xd9527ca9;
*((unsigned int *)((unsigned long)context_ptr+0x000067f8+4*12))=0x51583ff0;
*((unsigned int *)((unsigned long)context_ptr+0x000067f8+4*13))=0x55be93fc;
*((unsigned int *)((unsigned long)context_ptr+0x000067f8+4*14))=0x24d0be53;
*((unsigned int *)((unsigned long)context_ptr+0x000067f8+4*15))=0x324da6e0;
*((unsigned int *)((unsigned long)context_ptr+0x00006214))=0x4e7085f2;
*((unsigned int *)((unsigned long)context_ptr+0x00006214+4*1))=0x9de902a9;
*((unsigned int *)((unsigned long)context_ptr+0x00006214+4*2))=0x3d990f00;
*((unsigned int *)((unsigned long)context_ptr+0x00006214+4*3))=0x83c9df54;
*((unsigned int *)((unsigned long)context_ptr+0x00006214+4*4))=0xf94794e0;
*((unsigned int *)((unsigned long)context_ptr+0x00006214+4*5))=0x8de5110f;
*((unsigned int *)((unsigned long)context_ptr+0x00006214+4*6))=0xf4bbcbe0;
*((unsigned int *)((unsigned long)context_ptr+0x00006214+4*7))=0x3ee7a058;
*((unsigned int *)((unsigned long)context_ptr+0x00006214+4*8))=0x00008b01;
*((unsigned int *)((unsigned long)context_ptr+0x00003918))=0x04c00062;
*((unsigned int *)((unsigned long)context_ptr+0x00003918+4*1))=0x000069bc;
*((unsigned int *)((unsigned long)context_ptr+0x00003918+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003918+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003918+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003918+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005f4&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000c30))=0x03800040;
*((unsigned int *)((unsigned long)context_ptr+0x00000c30+4*1))=0x000067f8;
*((unsigned int *)((unsigned long)context_ptr+0x00000c30+4*2))=0x00006050;
*((unsigned int *)((unsigned long)context_ptr+0x00000c30+4*3))=0x02220062;
*((unsigned int *)((unsigned long)context_ptr+0x00000c30+4*4))=0x00b457cb;
*((unsigned int *)((unsigned long)context_ptr+0x00000c30+4*5))=0x00006000+(unsigned long)context_ptr;
*((unsigned int *)((unsigned long)context_ptr+0x00000c48))=0x00400022;
*((unsigned int *)((unsigned long)context_ptr+0x00000c48+4*1))=0x00006214;
*((unsigned int *)((unsigned long)context_ptr+0x00000c48+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00000c48+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00000c48+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00000c48+4*5))=0x77777777+(unsigned long)context_ptr;
writel(0x00000030&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000001f8&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006640,"\x29\x29\x6b\x55\xc2\xac\x0f\x1c\x86\x1a\x8f\xb7\x9e\x02\xef\x41\x75\x86\xfa\x4f\xa8\xd6\x90\x39\x47\x21\xbb\x7e\x54\xeb\x33\x20\x9e\x64\x61\x96\x9b\x04\x19\x0c\x08\x36\xe9\x13\x31\x93\x60\xaa\x35\xb0\x13\x5a\x6d\x9d\x04\x08\x1d\x99\x70\xb1\x72\x01\x3e\xee\xd5\xc0\x50\xb8\x46\x08\x64\xb1\x3e\xfd\x50\x9f\x1a\x16\xcd\x99\x1b\x64\xa0\xcd",84))
printf("strip: 29296b55c2ac0f1c, Pass\n");
else
printf("strip: 29296b55c2ac0f1c, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x0000605c))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x0000605c+4*1))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x0000605c+4*2))=0x01060063;
*((unsigned int *)((unsigned long)context_ptr+0x00006a20))=0x0ef367d2;
*((unsigned int *)((unsigned long)context_ptr+0x00006a20+4*1))=0xfeca5a9c;
*((unsigned int *)((unsigned long)context_ptr+0x00006a20+4*2))=0x50a79d4a;
*((unsigned int *)((unsigned long)context_ptr+0x00006a20+4*3))=0x7ef2194c;
*((unsigned int *)((unsigned long)context_ptr+0x00006a20+4*4))=0x3144c9b3;
*((unsigned int *)((unsigned long)context_ptr+0x00006a20+4*5))=0x1d879c5f;
*((unsigned int *)((unsigned long)context_ptr+0x00006a20+4*6))=0x2bd9fdfb;
*((unsigned int *)((unsigned long)context_ptr+0x00006a20+4*7))=0x9dfdce6b;
*((unsigned int *)((unsigned long)context_ptr+0x00006a20+4*8))=0xd04be72d;
*((unsigned int *)((unsigned long)context_ptr+0x00006a20+4*9))=0x609b58a9;
*((unsigned int *)((unsigned long)context_ptr+0x00006a20+4*10))=0x94b7c899;
*((unsigned int *)((unsigned long)context_ptr+0x00006a20+4*11))=0x3460cdb8;
*((unsigned int *)((unsigned long)context_ptr+0x00006a20+4*12))=0xbca835b0;
*((unsigned int *)((unsigned long)context_ptr+0x00006a20+4*13))=0xf9bf3a56;
*((unsigned int *)((unsigned long)context_ptr+0x00006a20+4*14))=0x3f7adfc0;
*((unsigned int *)((unsigned long)context_ptr+0x00006a20+4*15))=0xc845261c;
*((unsigned int *)((unsigned long)context_ptr+0x0000663c))=0x910aff20;
*((unsigned int *)((unsigned long)context_ptr+0x0000663c+4*1))=0x762a8093;
*((unsigned int *)((unsigned long)context_ptr+0x0000663c+4*2))=0x4e5e41d9;
*((unsigned int *)((unsigned long)context_ptr+0x0000663c+4*3))=0xf5859c63;
*((unsigned int *)((unsigned long)context_ptr+0x0000663c+4*4))=0x4b044d78;
*((unsigned int *)((unsigned long)context_ptr+0x0000663c+4*5))=0x7b92fed5;
*((unsigned int *)((unsigned long)context_ptr+0x0000663c+4*6))=0xcf595462;
*((unsigned int *)((unsigned long)context_ptr+0x0000663c+4*7))=0xe1249358;
*((unsigned int *)((unsigned long)context_ptr+0x0000663c+4*8))=0x0040754e;
*((unsigned int *)((unsigned long)context_ptr+0x00003930))=0x04c00063;
*((unsigned int *)((unsigned long)context_ptr+0x00003930+4*1))=0x00006238;
*((unsigned int *)((unsigned long)context_ptr+0x00003930+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003930+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003930+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003930+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005f4&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000c60))=0x03800040;
*((unsigned int *)((unsigned long)context_ptr+0x00000c60+4*1))=0x00006a20;
*((unsigned int *)((unsigned long)context_ptr+0x00000c60+4*2))=0x0000605c;
*((unsigned int *)((unsigned long)context_ptr+0x00000c60+4*3))=0x02220063;
*((unsigned int *)((unsigned long)context_ptr+0x00000c60+4*4))=0x00ad100c;
*((unsigned int *)((unsigned long)context_ptr+0x00000c60+4*5))=0x00006000+(unsigned long)context_ptr;
*((unsigned int *)((unsigned long)context_ptr+0x00000c78))=0x00400023;
*((unsigned int *)((unsigned long)context_ptr+0x00000c78+4*1))=0x0000663c;
*((unsigned int *)((unsigned long)context_ptr+0x00000c78+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00000c78+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00000c78+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00000c78+4*5))=0x77777777+(unsigned long)context_ptr;
writel(0x00000030&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000001fe&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x0000607c,"\xaf\xec\xa3\x4f\xc8\xdd\xd0\x8b\x7f\xd1\xb4\x15\xc2\xd1\x81\x38\x73\x7f\xd3\x7e\xdd\x6c\x2d\x68\xcc\x9c\xe9\xb5\xb2\xec\xb8\x8b\xdd\xeb\xed\x39\x7f\xa3\x0c\x69\x9a\xd7\x0a\x52\x50\x29\x53\xfd\x7d\x12\xc9\xfc\xeb\x9c\x67\xd2\x92\x2d\xaa\x79\xb2\x34\x4a\x4d\x4a\xb4\x59\xaa\x03\x06\x77\xea\x0c\x15\xff\x4f\x12\x10\x14\x39\x96\x08\xd7\xf1\x55\x00\x00\x00",85))
printf("strip: afeca34fc8ddd08b, Pass\n");
else
printf("strip: afeca34fc8ddd08b, Failed\n");
writel(0x00000204&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000068a4,"\xe3\xc5\x8b\xd8\x26\xfc\xb8\xd1\x41\x04\x9c\xbf\xed\x26\x39\x9c\xd0\x4c\x64\xb2\x13\x79\x44\x08\x5d\x4c\xe5\x90\x3b\x4e\x86\xfd\x46\x60\x1c\x13\x32\xa6\xaf\xd2\xd3\x46\x5f\xf1\x86\xa5\xb3\xec\x68\xc6\x71\x57\xbc\x9d\x4f\x96\x1a\xea\x08\x12\xb2\xc8\xef\x6c\xf0\x80\x17\x4b\x7e\xe1\x0f\x8a\x8c\xdd\x5e\x79\xaa\x39\xa2\x73\x3d\x3f\x97\xad\x48\x62\x00\x00",86))
printf("strip: e3c58bd826fcb8d1, Pass\n");
else
printf("strip: e3c58bd826fcb8d1, Failed\n");
writel(0x0000020a&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006a68,"\x4a\x3c\x75\xf3\x7c\x52\x2e\x80\x00\x38\x89\xdd\x5f\x55\x4f\xdd\x83\xe6\xac\x41\x63\x15\x0e\xed\x95\xd2\x3a\x8f\x8a\x20\xd0\xf0\xeb\x2c\x95\xf0\xfd\x7f\xe2\xdc\xe0\xad\xef\xae\x1e\x35\x38\x27\x84\x4e\x4b\x57\x22\x7a\xe3\x83\xc3\x63\xfd\x59\x4e\xad\xb3\x60\x68\x36\x9d\x41\x85\x0c\x7b\xdd\x69\x98\x2c\x03\x40\x2d\xd1\x45\xf7\xb5\xd8\x1a\x68\x54\x34\x00",87))
printf("strip: 4a3c75f37c522e80, Pass\n");
else
printf("strip: 4a3c75f37c522e80, Failed\n");
writel(0x00000210&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000066b8,"\x88\xa7\x57\xad\xee\x55\x11\x5c\x03\x25\xaa\x46\x20\xe9\x29\x57\x80\xdc\xc1\x97\xfa\x83\x31\x7d\x5f\x65\x7e\xd2\x8b\xb3\xf0\x1e\xba\xca\x9f\xbb\x50\x18\x26\xd5\x7e\x2e\x75\x86\x7b\x06\x2f\x99\x57\xc6\x4f\xc9\x90\x52\x4d\x67\x12\xc7\xeb\xa3\x96\xc9\x18\xbf\xaf\x27\x90\xcd\x3d\x14\x1a\x4e\x62\xd5\x7a\xc3\x3c\xb3\xf9\x69\xdc\x0e\x13\x0a\xdc\xd4\xbe\xe1",88))
printf("strip: 88a757adee55115c, Pass\n");
else
printf("strip: 88a757adee55115c, Failed\n");
writel(0x00000216&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x0000612c,"\x43\xef\xb9\xb9\xd8\xad\x4b\xe1\x54\xf2\xa5\x31\xdb\xcb\xe1\xa5\x25\x12\x21\x87\x7b\x95\x71\xb7\x8a\xa6\xdb\x15\xd9\x3c\xf8\x75\x6a\xf9\x8e\x0b\xe4\x46\x66\x24\xfe\xa4\xe7\x9e\xdd\xdf\xf5\xc2\xf3\xaa\xbd\xec\xf1\xfa\x01\x95\xf5\xa6\x31\x27\x56\x87\x68\x5e\x16\xa4\x63\x82\x0d\xfe\x4b\xb5\xcd\x2b\x5f\x5a\x2b\xa8\xc1\xa6\xbc\x17\x6a\x7f\xf7\x74\x8a\x86\x2d\x00\x00\x00",89))
printf("strip: 43efb9b9d8ad4be1, Pass\n");
else
printf("strip: 43efb9b9d8ad4be1, Failed\n");
writel(0x0000021c&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006ac0,"\x8d\xb0\x6a\x51\xb4\xf9\xdd\x7e\x20\xa9\x35\x3a\xa0\x39\xb6\x81\x6e\xcd\x76\xb8\x9e\xbe\xe4\x36\xad\x01\x37\xbd\x4e\x37\x8e\xe3\x8a\x36\x4b\x21\x54\x0c\xa7\x87\x1c\x0c\x25\xdc\xf6\x4e\x70\x30\xba\x82\x03\x3b\x02\x70\xdf\xe1\x9a\xf5\xe9\x82\x64\x50\x2a\x8c\x79\x02\x08\x37\x42\x73\xe6\xec\x45\xad\x8e\xe6\x4d\x71\x98\x6b\x6b\x33\xbd\xd0\xa6\x90\xe1\xdc\x05\xad\x00\x00",90))
printf("strip: 8db06a51b4f9dd7e, Pass\n");
else
printf("strip: 8db06a51b4f9dd7e, Failed\n");
writel(0x00000222&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006320,"\x0a\xde\x5d\x77\x6f\xcd\x66\x5b\xad\x62\xa8\x75\x91\x67\x40\xf1\x96\xa2\x49\xa2\x8d\x94\x8a\x41\xa7\x14\x4f\x4d\x6f\x00\x34\xda\xca\x03\x9b\x83\x18\xbd\x5c\x61\x5d\x9b\xd5\xd7\x50\xe5\x0f\x9f\xb3\xf4\x6a\x6a\xa0\x57\xf7\x59\x25\x56\x41\xff\xe3\xbb\x46\x48\x26\x95\x38\x1a\xe6\x44\xa0\x21\x48\x23\x46\x02\x5c\xf0\xa0\xf2\x73\x0f\x27\x7c\x3a\x17\x43\x77\x6b\xbf\xf0\x00",91))
printf("strip: 0ade5d776fcd665b, Pass\n");
else
printf("strip: 0ade5d776fcd665b, Failed\n");
writel(0x00000228&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006b1c,"\xe1\xd4\x54\x42\x19\xc7\x66\x77\x18\x11\xd7\x8f\x2a\x30\x5c\x44\x22\x01\xf4\x71\xa9\x90\xb3\xe4\x54\xa8\x03\x4b\x06\x71\xdb\xe4\xab\xd8\x79\x15\x77\xb7\x39\x20\xfc\x72\xa5\xfe\xb2\x6a\x8a\x7f\x73\x91\x4f\x1d\xf6\xe7\xb0\x70\xe3\x77\xa4\xec\x2d\xc4\xef\x69\x8f\x54\xee\x55\x3e\x64\x18\x28\x18\xb6\x55\x09\xb0\x4c\xcf\xea\x95\xee\xec\x64\xb6\x05\xa1\xf7\x91\x4c\x8a\x61",92))
printf("strip: e1d4544219c76677, Pass\n");
else
printf("strip: e1d4544219c76677, Failed\n");
writel(0x0000022e&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006778,"\xc4\x42\x6b\xcf\x4f\xcd\x6f\xb4\x2d\x74\x22\x90\x21\xf1\xec\x46\x51\x01\xfe\x93\x51\xfe\x44\xa6\x6d\x1e\x41\xb4\x3b\x50\x2e\x09\x0d\x32\x18\xaf\xe2\x7e\x4e\x81\xb7\xa1\x28\xc5\xe6\x80\xb1\x94\x2a\x62\xf6\x0d\xc3\x9e\x91\x7e\x26\x9c\xf1\x82\xd9\xaf\x2c\xd2\x2b\xf1\x29\x69\xd3\x5c\x9d\xa9\x4a\x67\x95\x80\xf0\xb9\x15\xaf\x97\x86\x53\xc6\xe8\x53\x7b\xb7\xc2\x48\x93\xe0\x12\x00\x00\x00",93))
printf("strip: c4426bcf4fcd6fb4, Pass\n");
else
printf("strip: c4426bcf4fcd6fb4, Failed\n");
writel(0x00000234&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x0000693c,"\x21\xc5\xbe\xe8\x59\x34\xf4\x79\x91\x17\xce\x39\xf3\x76\x28\x9a\x3f\x1c\x7c\x81\xb6\xe6\x37\xd3\x74\x20\xc0\x62\x8f\x00\x3f\x94\x07\x21\x86\x38\xb4\xe4\x2a\x5f\x12\xf0\xb6\x24\x3b\x9d\x4c\x28\xd5\x46\xb3\x65\x3d\xdd\xb4\x69\xa0\x23\xf9\xc0\xd2\x34\xd6\x51\x57\xaa\xdf\xae\x4a\xd3\x22\xf1\xb4\x8f\x35\x75\x6c\x87\xc3\xd2\x7b\x9d\xd0\xb6\x99\x67\x0f\xd4\x33\x91\x36\x00\x67\x8a\x00\x00",94))
printf("strip: 21c5bee85934f479, Pass\n");
else
printf("strip: 21c5bee85934f479, Failed\n");
writel(0x0000023a&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000065b8,"\x15\x69\x45\x1d\x3c\xcc\x8e\x8c\x3b\xd3\x7c\xd5\x70\x00\x3a\x9b\x2a\x7c\x99\x64\x07\x0f\xcf\x7e\x18\x34\x52\x0e\x9b\x80\xc7\x79\x8b\xcd\xd3\x53\x19\xe5\xc5\x05\x0f\xdd\x67\x01\x90\xff\xfb\x3e\xbc\x2f\xd1\x9d\xd1\xaf\xd4\x23\x45\x2f\x1f\x38\x15\x73\x58\x02\x32\xb3\x0b\x04\xdb\xea\x09\x42\x5b\x94\xa0\xf6\x45\x66\x60\xd6\x31\xe8\xa9\x7d\xb8\x32\x0b\xdd\x5b\xdf\x9f\x95\xe1\x4d\x62\x00",95))
printf("strip: 1569451d3ccc8e8c, Pass\n");
else
printf("strip: 1569451d3ccc8e8c, Failed\n");
writel(0x00000240&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006b78,"\xb4\x53\xee\x39\xbf\x81\x40\x83\x50\x85\x35\x43\x3e\xdc\x64\xdb\x60\x52\xaa\x67\xd1\xa5\xb3\xf8\xd8\x57\x75\xdd\xe4\x89\x8b\x15\x36\x1e\x53\x04\x81\x00\x5c\x1a\x3e\xaa\x43\x01\xd3\x89\xe1\x44\x51\x07\x81\xe5\x00\x93\x3d\xaf\xec\x7b\xe0\x62\x37\x6c\xa8\xcd\xad\x12\xcb\x21\x1d\x36\x2c\x31\x33\x89\xdc\x86\xa8\xc8\xfd\x46\xf1\x32\x31\xcb\x14\xe6\xe7\xb3\xb2\x7a\x12\x58\xc2\x96\x4e\x2c",96))
printf("strip: b453ee39bf814083, Pass\n");
else
printf("strip: b453ee39bf814083, Failed\n");
writel(0x00000246&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006bd8,"\x35\x5c\xbf\x6a\x2c\xf5\xee\xdc\x7d\xfc\x12\xa7\x08\x58\x8f\x7b\x6f\xef\xe2\xe3\xc7\x33\xa9\x5e\xe3\x58\x98\xd3\x54\x1f\x5b\x45\x59\xfa\xdc\x95\xd7\x81\xee\x40\xe6\x90\x1c\x79\x50\x38\xc9\x2b\xa0\x8d\x8c\x2f\xb3\x79\x8e\xed\xfe\x9c\x80\xfa\x08\x2a\xb4\x50\x7f\x9f\x67\x97\x51\x28\xa3\x29\x2b\xd9\xc6\x19\xbc\xd2\xd3\x9f\x89\x9c\x52\x94\xca\x71\x1b\xd6\x4a\x71\xa8\xcd\xa3\x62\x1b\xf7\x7f\x00\x00\x00",97))
printf("strip: 355cbf6a2cf5eedc, Pass\n");
else
printf("strip: 355cbf6a2cf5eedc, Failed\n");
writel(0x0000024c&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000069bc,"\xf0\xfb\x87\x4a\x18\x05\x46\x0a\xb7\x7a\xd1\xd5\x79\x7b\x87\xa7\x79\xf5\x46\x09\xf8\x16\x30\x46\xd7\x50\xa7\xd8\x8b\x3a\x83\x05\x5d\x2e\x66\x0f\xab\xb0\xce\x98\x1f\x25\xfb\xb2\xa9\x7c\x52\xd9\xf0\x3f\x58\x51\xfc\x93\xbe\x55\x53\xbe\xd0\x24\xe0\xa6\x4d\x32\xf2\x85\x70\x4e\xa9\x02\xe9\x9d\x00\x0f\x99\x3d\x54\xdf\xc9\x83\xe0\x94\x47\xf9\x0f\x11\xe5\x8d\xe0\xcb\xbb\xf4\x58\xa0\xe7\x3e\x01\x8b\x00\x00",98))
printf("strip: f0fb874a1805460a, Pass\n");
else
printf("strip: f0fb874a1805460a, Failed\n");
writel(0x00000252&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006238,"\xd2\x67\xf3\x0e\x9c\x5a\xca\xfe\x4a\x9d\xa7\x50\x4c\x19\xf2\x7e\xb3\xc9\x44\x31\x5f\x9c\x87\x1d\xfb\xfd\xd9\x2b\x6b\xce\xfd\x9d\x2d\xe7\x4b\xd0\xa9\x58\x9b\x60\x99\xc8\xb7\x94\xb8\xcd\x60\x34\xb0\x35\xa8\xbc\x56\x3a\xbf\xf9\xc0\xdf\x7a\x3f\x1c\x26\x45\xc8\x20\xff\x0a\x91\x93\x80\x2a\x76\xd9\x41\x5e\x4e\x63\x9c\x85\xf5\x78\x4d\x04\x4b\xd5\xfe\x92\x7b\x62\x54\x59\xcf\x58\x93\x24\xe1\x4e\x75\x40\x00",99))
printf("strip: d267f30e9c5acafe, Pass\n");
else
printf("strip: d267f30e9c5acafe, Failed\n");
}

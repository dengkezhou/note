#include <common.h>
#include <malloc.h>

extern volatile unsigned int ivp_cae_base_addr;

void test_sha1(void)
{
unsigned int *context_ptr=(unsigned int *)0x14000000;
printf("test_sha1\n");
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
*((unsigned int *)((unsigned long)context_ptr+0x00006000))=0x010a0002;
*((unsigned int *)((unsigned long)context_ptr+0x00006000+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006008))=0x010a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006008+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006008+4*2))=0x02020001;
*((unsigned int *)((unsigned long)context_ptr+0x00006008+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x00006018))=0x000000f6;
*((unsigned int *)((unsigned long)context_ptr+0x00003000))=0x04c00014;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000000+4*4))=0x0091472b;
*((unsigned int *)((unsigned long)context_ptr+0x00000000+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x00006030))=0x010a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006030+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006030+4*2))=0x02020002;
*((unsigned int *)((unsigned long)context_ptr+0x00006030+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x00006040))=0x000034e7;
*((unsigned int *)((unsigned long)context_ptr+0x00003018))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003018+4*1))=0x00006044;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000018+4*1))=0x00006040;
*((unsigned int *)((unsigned long)context_ptr+0x00000018+4*2))=0x00006030;
*((unsigned int *)((unsigned long)context_ptr+0x00000018+4*3))=0x02220002;
*((unsigned int *)((unsigned long)context_ptr+0x00000018+4*4))=0x0d360da7;
*((unsigned int *)((unsigned long)context_ptr+0x00000018+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x00006058))=0x010a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*2))=0x02020003;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x00006068))=0x009c69fc;
*((unsigned int *)((unsigned long)context_ptr+0x00003030))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003030+4*1))=0x0000606c;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000030+4*1))=0x00006068;
*((unsigned int *)((unsigned long)context_ptr+0x00000030+4*2))=0x00006058;
*((unsigned int *)((unsigned long)context_ptr+0x00000030+4*3))=0x02220003;
*((unsigned int *)((unsigned long)context_ptr+0x00000030+4*4))=0x0788c31f;
*((unsigned int *)((unsigned long)context_ptr+0x00000030+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x00006080))=0x010a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006080+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006080+4*2))=0x02020004;
*((unsigned int *)((unsigned long)context_ptr+0x00006080+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x00006090))=0x13ca74c1;
*((unsigned int *)((unsigned long)context_ptr+0x00003048))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003048+4*1))=0x00006094;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000048+4*1))=0x00006090;
*((unsigned int *)((unsigned long)context_ptr+0x00000048+4*2))=0x00006080;
*((unsigned int *)((unsigned long)context_ptr+0x00000048+4*3))=0x02220004;
*((unsigned int *)((unsigned long)context_ptr+0x00000048+4*4))=0x07c7550e;
*((unsigned int *)((unsigned long)context_ptr+0x00000048+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x000060a8))=0x010a0012;
*((unsigned int *)((unsigned long)context_ptr+0x000060a8+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000060a8+4*2))=0x02020005;
*((unsigned int *)((unsigned long)context_ptr+0x000060a8+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x000060b8))=0xd1f90259;
*((unsigned int *)((unsigned long)context_ptr+0x000060b8+4*1))=0x00000012;
*((unsigned int *)((unsigned long)context_ptr+0x00003060))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003060+4*1))=0x000060c0;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000060+4*1))=0x000060b8;
*((unsigned int *)((unsigned long)context_ptr+0x00000060+4*2))=0x000060a8;
*((unsigned int *)((unsigned long)context_ptr+0x00000060+4*3))=0x02220005;
*((unsigned int *)((unsigned long)context_ptr+0x00000060+4*4))=0x0346d2b7;
*((unsigned int *)((unsigned long)context_ptr+0x00000060+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x000060d4))=0x010a0012;
*((unsigned int *)((unsigned long)context_ptr+0x000060d4+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000060d4+4*2))=0x02020006;
*((unsigned int *)((unsigned long)context_ptr+0x000060d4+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x000060e4))=0x1305210b;
*((unsigned int *)((unsigned long)context_ptr+0x000060e4+4*1))=0x00006b12;
*((unsigned int *)((unsigned long)context_ptr+0x00003078))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003078+4*1))=0x000060ec;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000078+4*1))=0x000060e4;
*((unsigned int *)((unsigned long)context_ptr+0x00000078+4*2))=0x000060d4;
*((unsigned int *)((unsigned long)context_ptr+0x00000078+4*3))=0x02220006;
*((unsigned int *)((unsigned long)context_ptr+0x00000078+4*4))=0x0246cb09;
*((unsigned int *)((unsigned long)context_ptr+0x00000078+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x00006100))=0x010a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006100+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006100+4*2))=0x02020007;
*((unsigned int *)((unsigned long)context_ptr+0x00006100+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x00006110))=0xc44c019e;
*((unsigned int *)((unsigned long)context_ptr+0x00006110+4*1))=0x00278ba1;
*((unsigned int *)((unsigned long)context_ptr+0x00003090))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003090+4*1))=0x00006118;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000090+4*1))=0x00006110;
*((unsigned int *)((unsigned long)context_ptr+0x00000090+4*2))=0x00006100;
*((unsigned int *)((unsigned long)context_ptr+0x00000090+4*3))=0x02220007;
*((unsigned int *)((unsigned long)context_ptr+0x00000090+4*4))=0x0ad9d1f4;
*((unsigned int *)((unsigned long)context_ptr+0x00000090+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x0000612c))=0x010a0012;
*((unsigned int *)((unsigned long)context_ptr+0x0000612c+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x0000612c+4*2))=0x02020008;
*((unsigned int *)((unsigned long)context_ptr+0x0000612c+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x0000613c))=0x5f4ac9c7;
*((unsigned int *)((unsigned long)context_ptr+0x0000613c+4*1))=0x61b228a0;
*((unsigned int *)((unsigned long)context_ptr+0x000030a8))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x000030a8+4*1))=0x00006144;
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
*((unsigned int *)((unsigned long)context_ptr+0x000000a8+4*1))=0x0000613c;
*((unsigned int *)((unsigned long)context_ptr+0x000000a8+4*2))=0x0000612c;
*((unsigned int *)((unsigned long)context_ptr+0x000000a8+4*3))=0x02220008;
*((unsigned int *)((unsigned long)context_ptr+0x000000a8+4*4))=0x0ab12fb3;
*((unsigned int *)((unsigned long)context_ptr+0x000000a8+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x00006158))=0x010a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006158+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006158+4*2))=0x02020009;
*((unsigned int *)((unsigned long)context_ptr+0x00006158+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x00006168))=0x726fe56b;
*((unsigned int *)((unsigned long)context_ptr+0x00006168+4*1))=0xe92186b5;
*((unsigned int *)((unsigned long)context_ptr+0x00006168+4*2))=0x00000071;
*((unsigned int *)((unsigned long)context_ptr+0x000030c0))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x000030c0+4*1))=0x00006174;
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
*((unsigned int *)((unsigned long)context_ptr+0x000000c0+4*1))=0x00006168;
*((unsigned int *)((unsigned long)context_ptr+0x000000c0+4*2))=0x00006158;
*((unsigned int *)((unsigned long)context_ptr+0x000000c0+4*3))=0x02220009;
*((unsigned int *)((unsigned long)context_ptr+0x000000c0+4*4))=0x0ce8d75e;
*((unsigned int *)((unsigned long)context_ptr+0x000000c0+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x00006188))=0x010a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006188+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006188+4*2))=0x0202000a;
*((unsigned int *)((unsigned long)context_ptr+0x00006188+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x00006198))=0x65f8aec9;
*((unsigned int *)((unsigned long)context_ptr+0x00006198+4*1))=0x1a5674eb;
*((unsigned int *)((unsigned long)context_ptr+0x00006198+4*2))=0x0000cbe2;
*((unsigned int *)((unsigned long)context_ptr+0x000030d8))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x000030d8+4*1))=0x000061a4;
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
*((unsigned int *)((unsigned long)context_ptr+0x000000d8+4*1))=0x00006198;
*((unsigned int *)((unsigned long)context_ptr+0x000000d8+4*2))=0x00006188;
*((unsigned int *)((unsigned long)context_ptr+0x000000d8+4*3))=0x0222000a;
*((unsigned int *)((unsigned long)context_ptr+0x000000d8+4*4))=0x0533c9a2;
*((unsigned int *)((unsigned long)context_ptr+0x000000d8+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x000061b8))=0x010a0012;
*((unsigned int *)((unsigned long)context_ptr+0x000061b8+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000061b8+4*2))=0x0202000b;
*((unsigned int *)((unsigned long)context_ptr+0x000061b8+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x000061c8))=0x6f51efde;
*((unsigned int *)((unsigned long)context_ptr+0x000061c8+4*1))=0x338a498e;
*((unsigned int *)((unsigned long)context_ptr+0x000061c8+4*2))=0x009a714b;
*((unsigned int *)((unsigned long)context_ptr+0x000030f0))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x000030f0+4*1))=0x000061d4;
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
*((unsigned int *)((unsigned long)context_ptr+0x000000f0+4*1))=0x000061c8;
*((unsigned int *)((unsigned long)context_ptr+0x000000f0+4*2))=0x000061b8;
*((unsigned int *)((unsigned long)context_ptr+0x000000f0+4*3))=0x0222000b;
*((unsigned int *)((unsigned long)context_ptr+0x000000f0+4*4))=0x03b56733;
*((unsigned int *)((unsigned long)context_ptr+0x000000f0+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x000061e8))=0x010a0012;
*((unsigned int *)((unsigned long)context_ptr+0x000061e8+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000061e8+4*2))=0x0202000c;
*((unsigned int *)((unsigned long)context_ptr+0x000061e8+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x000061f8))=0xb291c6c8;
*((unsigned int *)((unsigned long)context_ptr+0x000061f8+4*1))=0xc2d0bb36;
*((unsigned int *)((unsigned long)context_ptr+0x000061f8+4*2))=0xe6a1975a;
*((unsigned int *)((unsigned long)context_ptr+0x00003108))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003108+4*1))=0x00006204;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000108+4*1))=0x000061f8;
*((unsigned int *)((unsigned long)context_ptr+0x00000108+4*2))=0x000061e8;
*((unsigned int *)((unsigned long)context_ptr+0x00000108+4*3))=0x0222000c;
*((unsigned int *)((unsigned long)context_ptr+0x00000108+4*4))=0x086c47b0;
*((unsigned int *)((unsigned long)context_ptr+0x00000108+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x00006218))=0x010a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006218+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006218+4*2))=0x0202000d;
*((unsigned int *)((unsigned long)context_ptr+0x00006218+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x00006228))=0x37e46cf8;
*((unsigned int *)((unsigned long)context_ptr+0x00006228+4*1))=0x542d5b6f;
*((unsigned int *)((unsigned long)context_ptr+0x00006228+4*2))=0x6861bffc;
*((unsigned int *)((unsigned long)context_ptr+0x00006228+4*3))=0x00000043;
*((unsigned int *)((unsigned long)context_ptr+0x00003120))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003120+4*1))=0x00006238;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000120+4*1))=0x00006228;
*((unsigned int *)((unsigned long)context_ptr+0x00000120+4*2))=0x00006218;
*((unsigned int *)((unsigned long)context_ptr+0x00000120+4*3))=0x0222000d;
*((unsigned int *)((unsigned long)context_ptr+0x00000120+4*4))=0x0afc8128;
*((unsigned int *)((unsigned long)context_ptr+0x00000120+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x0000624c))=0x010a0012;
*((unsigned int *)((unsigned long)context_ptr+0x0000624c+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x0000624c+4*2))=0x0202000e;
*((unsigned int *)((unsigned long)context_ptr+0x0000624c+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x0000625c))=0x4f647e45;
*((unsigned int *)((unsigned long)context_ptr+0x0000625c+4*1))=0xc5fa8ce6;
*((unsigned int *)((unsigned long)context_ptr+0x0000625c+4*2))=0x74af4392;
*((unsigned int *)((unsigned long)context_ptr+0x0000625c+4*3))=0x000067b8;
*((unsigned int *)((unsigned long)context_ptr+0x00003138))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003138+4*1))=0x0000626c;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000138+4*1))=0x0000625c;
*((unsigned int *)((unsigned long)context_ptr+0x00000138+4*2))=0x0000624c;
*((unsigned int *)((unsigned long)context_ptr+0x00000138+4*3))=0x0222000e;
*((unsigned int *)((unsigned long)context_ptr+0x00000138+4*4))=0x0bd6deb9;
*((unsigned int *)((unsigned long)context_ptr+0x00000138+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x00006280))=0x010a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006280+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006280+4*2))=0x0202000f;
*((unsigned int *)((unsigned long)context_ptr+0x00006280+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x00006290))=0x30bfc7d1;
*((unsigned int *)((unsigned long)context_ptr+0x00006290+4*1))=0x2cf36c8c;
*((unsigned int *)((unsigned long)context_ptr+0x00006290+4*2))=0x1c28a82b;
*((unsigned int *)((unsigned long)context_ptr+0x00006290+4*3))=0x009acb81;
*((unsigned int *)((unsigned long)context_ptr+0x00003150))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003150+4*1))=0x000062a0;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000150+4*1))=0x00006290;
*((unsigned int *)((unsigned long)context_ptr+0x00000150+4*2))=0x00006280;
*((unsigned int *)((unsigned long)context_ptr+0x00000150+4*3))=0x0222000f;
*((unsigned int *)((unsigned long)context_ptr+0x00000150+4*4))=0x048f352f;
*((unsigned int *)((unsigned long)context_ptr+0x00000150+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000006&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x0000601c,"\x9b\x16\x66\x8f\x4e\x16\xc0\xe9\x93\x26\x61\x85\x5b\x7b\xcb\x5b\xad\x8b\x0f\x72",20))
printf("strip: 9b16668f4e16c0e9, Pass\n");
else
printf("strip: 9b16668f4e16c0e9, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006008))=0x010a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006008+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006008+4*2))=0x02020010;
*((unsigned int *)((unsigned long)context_ptr+0x00006008+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x00006018))=0xedec2af5;
*((unsigned int *)((unsigned long)context_ptr+0x00006018+4*1))=0xe140f0a2;
*((unsigned int *)((unsigned long)context_ptr+0x00006018+4*2))=0x07179cc6;
*((unsigned int *)((unsigned long)context_ptr+0x00006018+4*3))=0x62c34002;
*((unsigned int *)((unsigned long)context_ptr+0x00003168))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003168+4*1))=0x000062b4;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000168+4*4))=0x063a6aaf;
*((unsigned int *)((unsigned long)context_ptr+0x00000168+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000000c&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006044,"\xdd\xd1\x03\xf4\x1c\x42\xfa\x15\xf2\x22\x10\xf6\x31\xc5\x93\x7d\x65\xa3\xea\x5c",20))
printf("strip: ddd103f41c42fa15, Pass\n");
else
printf("strip: ddd103f41c42fa15, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006028))=0x010a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006028+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006028+4*2))=0x02020011;
*((unsigned int *)((unsigned long)context_ptr+0x00006028+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x00006038))=0xd08f1595;
*((unsigned int *)((unsigned long)context_ptr+0x00006038+4*1))=0x40b34233;
*((unsigned int *)((unsigned long)context_ptr+0x00006038+4*2))=0x27ffef42;
*((unsigned int *)((unsigned long)context_ptr+0x00006038+4*3))=0x95098de6;
*((unsigned int *)((unsigned long)context_ptr+0x00006038+4*4))=0x000000a4;
*((unsigned int *)((unsigned long)context_ptr+0x00003180))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003180+4*1))=0x000062c8;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000180+4*4))=0x0d15b599;
*((unsigned int *)((unsigned long)context_ptr+0x00000180+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000012&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x0000606c,"\x28\x71\xf5\x9f\x3c\x77\xf5\x4a\x89\x80\xde\x2d\xbe\x55\xf6\xe5\x26\x5d\x28\x48",20))
printf("strip: 2871f59f3c77f54a, Pass\n");
else
printf("strip: 2871f59f3c77f54a, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x0000604c))=0x010a0012;
*((unsigned int *)((unsigned long)context_ptr+0x0000604c+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x0000604c+4*2))=0x02020012;
*((unsigned int *)((unsigned long)context_ptr+0x0000604c+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x0000605c))=0xcd0769cd;
*((unsigned int *)((unsigned long)context_ptr+0x0000605c+4*1))=0x1f5b6330;
*((unsigned int *)((unsigned long)context_ptr+0x0000605c+4*2))=0xa79d2d59;
*((unsigned int *)((unsigned long)context_ptr+0x0000605c+4*3))=0xdf8d7403;
*((unsigned int *)((unsigned long)context_ptr+0x0000605c+4*4))=0x0000147e;
*((unsigned int *)((unsigned long)context_ptr+0x00003198))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003198+4*1))=0x000062dc;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000198+4*1))=0x0000605c;
*((unsigned int *)((unsigned long)context_ptr+0x00000198+4*2))=0x0000604c;
*((unsigned int *)((unsigned long)context_ptr+0x00000198+4*3))=0x02220012;
*((unsigned int *)((unsigned long)context_ptr+0x00000198+4*4))=0x0ca6d3e0;
*((unsigned int *)((unsigned long)context_ptr+0x00000198+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006094,"\x5a\x2d\xc9\x19\x0f\x3f\xc9\x75\x6d\x97\xbf\x6d\xee\x24\x3f\x85\xdb\xd3\xc5\xe2",20))
printf("strip: 5a2dc9190f3fc975, Pass\n");
else
printf("strip: 5a2dc9190f3fc975, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006070))=0x010a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006070+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006070+4*2))=0x02020013;
*((unsigned int *)((unsigned long)context_ptr+0x00006070+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x00006080))=0x1cc60982;
*((unsigned int *)((unsigned long)context_ptr+0x00006080+4*1))=0x61acc79c;
*((unsigned int *)((unsigned long)context_ptr+0x00006080+4*2))=0x55e96f06;
*((unsigned int *)((unsigned long)context_ptr+0x00006080+4*3))=0x8882233f;
*((unsigned int *)((unsigned long)context_ptr+0x00006080+4*4))=0x00a86812;
*((unsigned int *)((unsigned long)context_ptr+0x000031b0))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x000031b0+4*1))=0x00006094;
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
*((unsigned int *)((unsigned long)context_ptr+0x000001b0+4*1))=0x00006080;
*((unsigned int *)((unsigned long)context_ptr+0x000001b0+4*2))=0x00006070;
*((unsigned int *)((unsigned long)context_ptr+0x000001b0+4*3))=0x02220013;
*((unsigned int *)((unsigned long)context_ptr+0x000001b0+4*4))=0x06fa0030;
*((unsigned int *)((unsigned long)context_ptr+0x000001b0+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000001e&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000060c0,"\xfd\x11\xc5\x2e\x03\x58\xf6\xdc\xc1\x90\xe2\x96\x76\x73\x9d\xd7\x4e\x73\x70\x4d",20))
printf("strip: fd11c52e0358f6dc, Pass\n");
else
printf("strip: fd11c52e0358f6dc, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000060a8))=0x010a0012;
*((unsigned int *)((unsigned long)context_ptr+0x000060a8+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000060a8+4*2))=0x02020014;
*((unsigned int *)((unsigned long)context_ptr+0x000060a8+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x000060b8))=0xae6e4aa2;
*((unsigned int *)((unsigned long)context_ptr+0x000060b8+4*1))=0x2158ba44;
*((unsigned int *)((unsigned long)context_ptr+0x000060b8+4*2))=0x656e2a9c;
*((unsigned int *)((unsigned long)context_ptr+0x000060b8+4*3))=0xc7aeb513;
*((unsigned int *)((unsigned long)context_ptr+0x000060b8+4*4))=0x352b8d8b;
*((unsigned int *)((unsigned long)context_ptr+0x000031c8))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x000031c8+4*1))=0x000062f0;
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
*((unsigned int *)((unsigned long)context_ptr+0x000001c8+4*1))=0x000060b8;
*((unsigned int *)((unsigned long)context_ptr+0x000001c8+4*2))=0x000060a8;
*((unsigned int *)((unsigned long)context_ptr+0x000001c8+4*3))=0x02220014;
*((unsigned int *)((unsigned long)context_ptr+0x000001c8+4*4))=0x0d1a8d7a;
*((unsigned int *)((unsigned long)context_ptr+0x000001c8+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000024&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000060ec,"\x6d\xf8\xe0\xb3\xc4\xb9\x5f\xd9\x6e\x64\x03\xd6\x1f\x10\x27\xdd\x47\x50\x66\x82",20))
printf("strip: 6df8e0b3c4b95fd9, Pass\n");
else
printf("strip: 6df8e0b3c4b95fd9, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000060cc))=0x010a0012;
*((unsigned int *)((unsigned long)context_ptr+0x000060cc+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000060cc+4*2))=0x02020015;
*((unsigned int *)((unsigned long)context_ptr+0x000060cc+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x000060dc))=0x4095731b;
*((unsigned int *)((unsigned long)context_ptr+0x000060dc+4*1))=0x8fecc67c;
*((unsigned int *)((unsigned long)context_ptr+0x000060dc+4*2))=0xebdb13d3;
*((unsigned int *)((unsigned long)context_ptr+0x000060dc+4*3))=0xe0d9d32b;
*((unsigned int *)((unsigned long)context_ptr+0x000060dc+4*4))=0xb5359b84;
*((unsigned int *)((unsigned long)context_ptr+0x000060dc+4*5))=0x00000067;
*((unsigned int *)((unsigned long)context_ptr+0x000031e0))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x000031e0+4*1))=0x00006304;
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
*((unsigned int *)((unsigned long)context_ptr+0x000001e0+4*1))=0x000060dc;
*((unsigned int *)((unsigned long)context_ptr+0x000001e0+4*2))=0x000060cc;
*((unsigned int *)((unsigned long)context_ptr+0x000001e0+4*3))=0x02220015;
*((unsigned int *)((unsigned long)context_ptr+0x000001e0+4*4))=0x0636241b;
*((unsigned int *)((unsigned long)context_ptr+0x000001e0+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000002a&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006118,"\x36\x74\x84\x83\x41\x8c\xcf\xd5\x3b\xf1\xeb\xd7\x15\xee\x30\xea\x87\x18\x59\x94",20))
printf("strip: 36748483418ccfd5, Pass\n");
else
printf("strip: 36748483418ccfd5, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000060f4))=0x010a0012;
*((unsigned int *)((unsigned long)context_ptr+0x000060f4+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000060f4+4*2))=0x02020016;
*((unsigned int *)((unsigned long)context_ptr+0x000060f4+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x00006104))=0x7e394fd6;
*((unsigned int *)((unsigned long)context_ptr+0x00006104+4*1))=0x135782f2;
*((unsigned int *)((unsigned long)context_ptr+0x00006104+4*2))=0x615e3992;
*((unsigned int *)((unsigned long)context_ptr+0x00006104+4*3))=0xbeef3bc2;
*((unsigned int *)((unsigned long)context_ptr+0x00006104+4*4))=0x625be17b;
*((unsigned int *)((unsigned long)context_ptr+0x00006104+4*5))=0x0000c721;
*((unsigned int *)((unsigned long)context_ptr+0x000031f8))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x000031f8+4*1))=0x00006318;
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
*((unsigned int *)((unsigned long)context_ptr+0x000001f8+4*1))=0x00006104;
*((unsigned int *)((unsigned long)context_ptr+0x000001f8+4*2))=0x000060f4;
*((unsigned int *)((unsigned long)context_ptr+0x000001f8+4*3))=0x02220016;
*((unsigned int *)((unsigned long)context_ptr+0x000001f8+4*4))=0x0789166f;
*((unsigned int *)((unsigned long)context_ptr+0x000001f8+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000030&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006144,"\x65\xda\x83\xbc\xfa\x64\x9e\x81\xc7\x81\xd4\x9a\xc9\x8f\x12\xf7\xe3\xcb\x45\x0f",20))
printf("strip: 65da83bcfa649e81, Pass\n");
else
printf("strip: 65da83bcfa649e81, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x0000611c))=0x010a0012;
*((unsigned int *)((unsigned long)context_ptr+0x0000611c+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x0000611c+4*2))=0x02020017;
*((unsigned int *)((unsigned long)context_ptr+0x0000611c+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x0000612c))=0x32bd33ef;
*((unsigned int *)((unsigned long)context_ptr+0x0000612c+4*1))=0x11d8e500;
*((unsigned int *)((unsigned long)context_ptr+0x0000612c+4*2))=0x61ed3b2d;
*((unsigned int *)((unsigned long)context_ptr+0x0000612c+4*3))=0xc3616fce;
*((unsigned int *)((unsigned long)context_ptr+0x0000612c+4*4))=0xb495449d;
*((unsigned int *)((unsigned long)context_ptr+0x0000612c+4*5))=0x00a4add3;
*((unsigned int *)((unsigned long)context_ptr+0x00003210))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003210+4*1))=0x00006144;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000210+4*1))=0x0000612c;
*((unsigned int *)((unsigned long)context_ptr+0x00000210+4*2))=0x0000611c;
*((unsigned int *)((unsigned long)context_ptr+0x00000210+4*3))=0x02220017;
*((unsigned int *)((unsigned long)context_ptr+0x00000210+4*4))=0x0f1f7e8f;
*((unsigned int *)((unsigned long)context_ptr+0x00000210+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000036&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006174,"\x13\x3e\xae\x07\x44\x83\xf7\xc1\xf0\xb8\x28\x45\x24\x42\xcc\xf6\x06\x15\x60\x72",20))
printf("strip: 133eae074483f7c1, Pass\n");
else
printf("strip: 133eae074483f7c1, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006158))=0x010a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006158+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006158+4*2))=0x02020018;
*((unsigned int *)((unsigned long)context_ptr+0x00006158+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x00006168))=0xad77c4ce;
*((unsigned int *)((unsigned long)context_ptr+0x00006168+4*1))=0xc9643169;
*((unsigned int *)((unsigned long)context_ptr+0x00006168+4*2))=0xaee3f6cd;
*((unsigned int *)((unsigned long)context_ptr+0x00006168+4*3))=0xec2eb985;
*((unsigned int *)((unsigned long)context_ptr+0x00006168+4*4))=0xa26f98b6;
*((unsigned int *)((unsigned long)context_ptr+0x00006168+4*5))=0x3692e69e;
*((unsigned int *)((unsigned long)context_ptr+0x00003228))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003228+4*1))=0x0000632c;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000228+4*1))=0x00006168;
*((unsigned int *)((unsigned long)context_ptr+0x00000228+4*2))=0x00006158;
*((unsigned int *)((unsigned long)context_ptr+0x00000228+4*3))=0x02220018;
*((unsigned int *)((unsigned long)context_ptr+0x00000228+4*4))=0x0e7aad06;
*((unsigned int *)((unsigned long)context_ptr+0x00000228+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000003c&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000061a4,"\x14\x35\x67\x04\xe8\xa3\x06\xe8\x98\x96\xb5\x17\x07\xbe\x89\x1f\xaa\x44\x9a\x64",20))
printf("strip: 14356704e8a306e8, Pass\n");
else
printf("strip: 14356704e8a306e8, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006180))=0x010a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006180+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006180+4*2))=0x02020019;
*((unsigned int *)((unsigned long)context_ptr+0x00006180+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x00006190))=0xbe4fc16b;
*((unsigned int *)((unsigned long)context_ptr+0x00006190+4*1))=0x07f73dc4;
*((unsigned int *)((unsigned long)context_ptr+0x00006190+4*2))=0x422783dd;
*((unsigned int *)((unsigned long)context_ptr+0x00006190+4*3))=0x38d64797;
*((unsigned int *)((unsigned long)context_ptr+0x00006190+4*4))=0xd2568162;
*((unsigned int *)((unsigned long)context_ptr+0x00006190+4*5))=0xa0271643;
*((unsigned int *)((unsigned long)context_ptr+0x00006190+4*6))=0x00000090;
*((unsigned int *)((unsigned long)context_ptr+0x00003240))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003240+4*1))=0x00006340;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000240+4*1))=0x00006190;
*((unsigned int *)((unsigned long)context_ptr+0x00000240+4*2))=0x00006180;
*((unsigned int *)((unsigned long)context_ptr+0x00000240+4*3))=0x02220019;
*((unsigned int *)((unsigned long)context_ptr+0x00000240+4*4))=0x07abc9f0;
*((unsigned int *)((unsigned long)context_ptr+0x00000240+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000042&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000061d4,"\x50\xf2\xcd\xe0\x5b\x71\x30\x1a\x3e\x80\xd1\xa6\xc3\x5b\xb3\xa3\x99\x3a\xe4\x7d",20))
printf("strip: 50f2cde05b71301a, Pass\n");
else
printf("strip: 50f2cde05b71301a, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000061ac))=0x010a0012;
*((unsigned int *)((unsigned long)context_ptr+0x000061ac+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000061ac+4*2))=0x0202001a;
*((unsigned int *)((unsigned long)context_ptr+0x000061ac+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x000061bc))=0xfbd437da;
*((unsigned int *)((unsigned long)context_ptr+0x000061bc+4*1))=0x15c5aa46;
*((unsigned int *)((unsigned long)context_ptr+0x000061bc+4*2))=0xf3b44ed1;
*((unsigned int *)((unsigned long)context_ptr+0x000061bc+4*3))=0x1d4a9c08;
*((unsigned int *)((unsigned long)context_ptr+0x000061bc+4*4))=0x5883fab6;
*((unsigned int *)((unsigned long)context_ptr+0x000061bc+4*5))=0x68886a72;
*((unsigned int *)((unsigned long)context_ptr+0x000061bc+4*6))=0x0000fa14;
*((unsigned int *)((unsigned long)context_ptr+0x00003258))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003258+4*1))=0x00006354;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000258+4*1))=0x000061bc;
*((unsigned int *)((unsigned long)context_ptr+0x00000258+4*2))=0x000061ac;
*((unsigned int *)((unsigned long)context_ptr+0x00000258+4*3))=0x0222001a;
*((unsigned int *)((unsigned long)context_ptr+0x00000258+4*4))=0x03db4cb9;
*((unsigned int *)((unsigned long)context_ptr+0x00000258+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000048&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006204,"\xe1\x4e\xd6\xbb\xdc\xec\x89\x3d\xbf\x4f\x50\x21\x34\x13\xac\x1a\xc9\x80\x50\xb1",20))
printf("strip: e14ed6bbdcec893d, Pass\n");
else
printf("strip: e14ed6bbdcec893d, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000061d8))=0x010a0012;
*((unsigned int *)((unsigned long)context_ptr+0x000061d8+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000061d8+4*2))=0x0202001b;
*((unsigned int *)((unsigned long)context_ptr+0x000061d8+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x000061e8))=0xd23b0640;
*((unsigned int *)((unsigned long)context_ptr+0x000061e8+4*1))=0x3ef1e26a;
*((unsigned int *)((unsigned long)context_ptr+0x000061e8+4*2))=0x2b94e18f;
*((unsigned int *)((unsigned long)context_ptr+0x000061e8+4*3))=0xde4cfc3f;
*((unsigned int *)((unsigned long)context_ptr+0x000061e8+4*4))=0xcab8bdcb;
*((unsigned int *)((unsigned long)context_ptr+0x000061e8+4*5))=0x812a0fd8;
*((unsigned int *)((unsigned long)context_ptr+0x000061e8+4*6))=0x007e8836;
*((unsigned int *)((unsigned long)context_ptr+0x00003270))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003270+4*1))=0x00006204;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000270+4*1))=0x000061e8;
*((unsigned int *)((unsigned long)context_ptr+0x00000270+4*2))=0x000061d8;
*((unsigned int *)((unsigned long)context_ptr+0x00000270+4*3))=0x0222001b;
*((unsigned int *)((unsigned long)context_ptr+0x00000270+4*4))=0x002fbad7;
*((unsigned int *)((unsigned long)context_ptr+0x00000270+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000004e&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006238,"\xe6\x85\xc7\x95\x87\x5e\xb0\x43\xf2\xbb\xb4\xff\x9d\xf6\x92\x2e\xe3\x13\x2b\x35",20))
printf("strip: e685c795875eb043, Pass\n");
else
printf("strip: e685c795875eb043, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006218))=0x010a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006218+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006218+4*2))=0x0202001c;
*((unsigned int *)((unsigned long)context_ptr+0x00006218+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x00006228))=0xce828337;
*((unsigned int *)((unsigned long)context_ptr+0x00006228+4*1))=0x81c7e684;
*((unsigned int *)((unsigned long)context_ptr+0x00006228+4*2))=0x6e5779d3;
*((unsigned int *)((unsigned long)context_ptr+0x00006228+4*3))=0xba0da674;
*((unsigned int *)((unsigned long)context_ptr+0x00006228+4*4))=0x331175f7;
*((unsigned int *)((unsigned long)context_ptr+0x00006228+4*5))=0x00cb411a;
*((unsigned int *)((unsigned long)context_ptr+0x00006228+4*6))=0x2c2ff0df;
*((unsigned int *)((unsigned long)context_ptr+0x00003288))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003288+4*1))=0x00006368;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000288+4*1))=0x00006228;
*((unsigned int *)((unsigned long)context_ptr+0x00000288+4*2))=0x00006218;
*((unsigned int *)((unsigned long)context_ptr+0x00000288+4*3))=0x0222001c;
*((unsigned int *)((unsigned long)context_ptr+0x00000288+4*4))=0x0cfd0925;
*((unsigned int *)((unsigned long)context_ptr+0x00000288+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000054&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x0000626c,"\x10\x3e\x63\xda\xd8\x82\x49\xad\x6d\x92\x45\x58\xf3\xbf\x93\x51\x4e\x68\x52\x55",20))
printf("strip: 103e63dad88249ad, Pass\n");
else
printf("strip: 103e63dad88249ad, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006244))=0x010a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006244+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006244+4*2))=0x0202001d;
*((unsigned int *)((unsigned long)context_ptr+0x00006244+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x00006254))=0x6b9bb642;
*((unsigned int *)((unsigned long)context_ptr+0x00006254+4*1))=0xafc4ec28;
*((unsigned int *)((unsigned long)context_ptr+0x00006254+4*2))=0xc51cc6d0;
*((unsigned int *)((unsigned long)context_ptr+0x00006254+4*3))=0xaf7bbfd6;
*((unsigned int *)((unsigned long)context_ptr+0x00006254+4*4))=0xc843c319;
*((unsigned int *)((unsigned long)context_ptr+0x00006254+4*5))=0x138982a2;
*((unsigned int *)((unsigned long)context_ptr+0x00006254+4*6))=0x23c6030a;
*((unsigned int *)((unsigned long)context_ptr+0x00006254+4*7))=0x0000001f;
*((unsigned int *)((unsigned long)context_ptr+0x000032a0))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x000032a0+4*1))=0x0000637c;
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
*((unsigned int *)((unsigned long)context_ptr+0x000002a0+4*1))=0x00006254;
*((unsigned int *)((unsigned long)context_ptr+0x000002a0+4*2))=0x00006244;
*((unsigned int *)((unsigned long)context_ptr+0x000002a0+4*3))=0x0222001d;
*((unsigned int *)((unsigned long)context_ptr+0x000002a0+4*4))=0x0e2cbef3;
*((unsigned int *)((unsigned long)context_ptr+0x000002a0+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000005a&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000062a0,"\x38\xcb\x09\xcb\x98\xcb\xec\x04\x68\x73\xc0\xfb\xf0\x13\xdb\x22\xe6\x69\x58\xe8",20))
printf("strip: 38cb09cb98cbec04, Pass\n");
else
printf("strip: 38cb09cb98cbec04, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006274))=0x010a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006274+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006274+4*2))=0x0202001e;
*((unsigned int *)((unsigned long)context_ptr+0x00006274+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x00006284))=0x126d7a67;
*((unsigned int *)((unsigned long)context_ptr+0x00006284+4*1))=0x82d4a438;
*((unsigned int *)((unsigned long)context_ptr+0x00006284+4*2))=0x62271225;
*((unsigned int *)((unsigned long)context_ptr+0x00006284+4*3))=0x9086aa90;
*((unsigned int *)((unsigned long)context_ptr+0x00006284+4*4))=0x66baaa5a;
*((unsigned int *)((unsigned long)context_ptr+0x00006284+4*5))=0x77e7bed0;
*((unsigned int *)((unsigned long)context_ptr+0x00006284+4*6))=0x6209c658;
*((unsigned int *)((unsigned long)context_ptr+0x00006284+4*7))=0x000057fa;
*((unsigned int *)((unsigned long)context_ptr+0x000032b8))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x000032b8+4*1))=0x00006390;
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
*((unsigned int *)((unsigned long)context_ptr+0x000002b8+4*1))=0x00006284;
*((unsigned int *)((unsigned long)context_ptr+0x000002b8+4*2))=0x00006274;
*((unsigned int *)((unsigned long)context_ptr+0x000002b8+4*3))=0x0222001e;
*((unsigned int *)((unsigned long)context_ptr+0x000002b8+4*4))=0x013b2cc0;
*((unsigned int *)((unsigned long)context_ptr+0x000002b8+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000060&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000062b4,"\xa1\x16\x16\xfc\x6c\xcc\x9d\xff\x32\x25\x01\xf2\x89\xc2\xac\xe8\xdf\xd3\xd8\x11",20))
printf("strip: a11616fc6ccc9dff, Pass\n");
else
printf("strip: a11616fc6ccc9dff, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006018))=0x010a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006018+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006018+4*2))=0x0202001f;
*((unsigned int *)((unsigned long)context_ptr+0x00006018+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x000062a4))=0x8cc22452;
*((unsigned int *)((unsigned long)context_ptr+0x000062a4+4*1))=0xec1db589;
*((unsigned int *)((unsigned long)context_ptr+0x000062a4+4*2))=0x9a99b17a;
*((unsigned int *)((unsigned long)context_ptr+0x000062a4+4*3))=0x357f16b5;
*((unsigned int *)((unsigned long)context_ptr+0x000062a4+4*4))=0x685a8363;
*((unsigned int *)((unsigned long)context_ptr+0x000062a4+4*5))=0x9af40bbb;
*((unsigned int *)((unsigned long)context_ptr+0x000062a4+4*6))=0x80148e29;
*((unsigned int *)((unsigned long)context_ptr+0x000062a4+4*7))=0x00506bb0;
*((unsigned int *)((unsigned long)context_ptr+0x000032d0))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x000032d0+4*1))=0x000063a4;
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
*((unsigned int *)((unsigned long)context_ptr+0x000002d0+4*1))=0x000062a4;
*((unsigned int *)((unsigned long)context_ptr+0x000002d0+4*2))=0x00006018;
*((unsigned int *)((unsigned long)context_ptr+0x000002d0+4*3))=0x0222001f;
*((unsigned int *)((unsigned long)context_ptr+0x000002d0+4*4))=0x0dfa6992;
*((unsigned int *)((unsigned long)context_ptr+0x000002d0+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000066&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000062c8,"\xbb\x1d\x83\xc9\x33\x71\xa2\x92\xbf\xf6\xea\x5a\x65\xc7\xaf\x25\xf8\xa2\xb6\x69",20))
printf("strip: bb1d83c93371a292, Pass\n");
else
printf("strip: bb1d83c93371a292, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006008))=0x010a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006008+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006008+4*2))=0x02020020;
*((unsigned int *)((unsigned long)context_ptr+0x00006008+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x000063b8))=0xe545d020;
*((unsigned int *)((unsigned long)context_ptr+0x000063b8+4*1))=0xcadddab3;
*((unsigned int *)((unsigned long)context_ptr+0x000063b8+4*2))=0x352401bc;
*((unsigned int *)((unsigned long)context_ptr+0x000063b8+4*3))=0x7c200093;
*((unsigned int *)((unsigned long)context_ptr+0x000063b8+4*4))=0x2c38510a;
*((unsigned int *)((unsigned long)context_ptr+0x000063b8+4*5))=0xa63be151;
*((unsigned int *)((unsigned long)context_ptr+0x000063b8+4*6))=0x5930acbb;
*((unsigned int *)((unsigned long)context_ptr+0x000063b8+4*7))=0x37f88945;
*((unsigned int *)((unsigned long)context_ptr+0x000032e8))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x000032e8+4*1))=0x00006038;
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
*((unsigned int *)((unsigned long)context_ptr+0x000002e8+4*1))=0x000063b8;
*((unsigned int *)((unsigned long)context_ptr+0x000002e8+4*2))=0x00006008;
*((unsigned int *)((unsigned long)context_ptr+0x000002e8+4*3))=0x02220020;
*((unsigned int *)((unsigned long)context_ptr+0x000002e8+4*4))=0x060252b7;
*((unsigned int *)((unsigned long)context_ptr+0x000002e8+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000006c&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000062dc,"\xe0\x14\xdb\x73\x4e\xf2\x31\xfd\xce\x67\x59\x55\xb0\x97\xa8\x64\x0f\xc2\x3e\xf6",20))
printf("strip: e014db734ef231fd, Pass\n");
else
printf("strip: e014db734ef231fd, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006028))=0x010a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006028+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006028+4*2))=0x02020021;
*((unsigned int *)((unsigned long)context_ptr+0x00006028+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x000062c4))=0xa434c458;
*((unsigned int *)((unsigned long)context_ptr+0x000062c4+4*1))=0x368470f9;
*((unsigned int *)((unsigned long)context_ptr+0x000062c4+4*2))=0x9a783c01;
*((unsigned int *)((unsigned long)context_ptr+0x000062c4+4*3))=0xb8544ad5;
*((unsigned int *)((unsigned long)context_ptr+0x000062c4+4*4))=0x16e0b6aa;
*((unsigned int *)((unsigned long)context_ptr+0x000062c4+4*5))=0xa79c7f1f;
*((unsigned int *)((unsigned long)context_ptr+0x000062c4+4*6))=0x3deb223a;
*((unsigned int *)((unsigned long)context_ptr+0x000062c4+4*7))=0xa2844804;
*((unsigned int *)((unsigned long)context_ptr+0x000062c4+4*8))=0x000000bd;
*((unsigned int *)((unsigned long)context_ptr+0x00003300))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003300+4*1))=0x0000605c;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000300+4*1))=0x000062c4;
*((unsigned int *)((unsigned long)context_ptr+0x00000300+4*2))=0x00006028;
*((unsigned int *)((unsigned long)context_ptr+0x00000300+4*3))=0x02220021;
*((unsigned int *)((unsigned long)context_ptr+0x00000300+4*4))=0x051f83e5;
*((unsigned int *)((unsigned long)context_ptr+0x00000300+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000072&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006094,"\x85\xd3\x33\x90\xae\x22\xfc\x02\x61\x95\x85\x26\xe5\xcc\xda\x6a\xf7\x92\x28\x38",20))
printf("strip: 85d33390ae22fc02, Pass\n");
else
printf("strip: 85d33390ae22fc02, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x0000604c))=0x010a0012;
*((unsigned int *)((unsigned long)context_ptr+0x0000604c+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x0000604c+4*2))=0x02020022;
*((unsigned int *)((unsigned long)context_ptr+0x0000604c+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x00006080))=0x4547119e;
*((unsigned int *)((unsigned long)context_ptr+0x00006080+4*1))=0xfd94c777;
*((unsigned int *)((unsigned long)context_ptr+0x00006080+4*2))=0x0ffa24b5;
*((unsigned int *)((unsigned long)context_ptr+0x00006080+4*3))=0x0563a355;
*((unsigned int *)((unsigned long)context_ptr+0x00006080+4*4))=0x97c63d4b;
*((unsigned int *)((unsigned long)context_ptr+0x00006080+4*5))=0x5136df24;
*((unsigned int *)((unsigned long)context_ptr+0x00006080+4*6))=0x846bc3df;
*((unsigned int *)((unsigned long)context_ptr+0x00006080+4*7))=0xa7b7b5fa;
*((unsigned int *)((unsigned long)context_ptr+0x00006080+4*8))=0x0000ecfc;
*((unsigned int *)((unsigned long)context_ptr+0x00003318))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003318+4*1))=0x000063d8;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000318+4*1))=0x00006080;
*((unsigned int *)((unsigned long)context_ptr+0x00000318+4*2))=0x0000604c;
*((unsigned int *)((unsigned long)context_ptr+0x00000318+4*3))=0x02220022;
*((unsigned int *)((unsigned long)context_ptr+0x00000318+4*4))=0x0a2bc533;
*((unsigned int *)((unsigned long)context_ptr+0x00000318+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000078&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000062f0,"\xa7\x27\x1c\xc9\x9e\x9a\x0c\xb9\x58\xa4\x50\x16\x2f\xbd\x44\x05\x5f\xf1\x65\xf7",20))
printf("strip: a7271cc99e9a0cb9, Pass\n");
else
printf("strip: a7271cc99e9a0cb9, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006070))=0x010a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006070+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006070+4*2))=0x02020023;
*((unsigned int *)((unsigned long)context_ptr+0x00006070+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x000060a4))=0x864d99d7;
*((unsigned int *)((unsigned long)context_ptr+0x000060a4+4*1))=0x2400ad8e;
*((unsigned int *)((unsigned long)context_ptr+0x000060a4+4*2))=0x3273c017;
*((unsigned int *)((unsigned long)context_ptr+0x000060a4+4*3))=0x8b76ab5f;
*((unsigned int *)((unsigned long)context_ptr+0x000060a4+4*4))=0x1b1a66f0;
*((unsigned int *)((unsigned long)context_ptr+0x000060a4+4*5))=0xc71d4fb9;
*((unsigned int *)((unsigned long)context_ptr+0x000060a4+4*6))=0xbd9d1ae3;
*((unsigned int *)((unsigned long)context_ptr+0x000060a4+4*7))=0x71afd63e;
*((unsigned int *)((unsigned long)context_ptr+0x000060a4+4*8))=0x00d4422a;
*((unsigned int *)((unsigned long)context_ptr+0x00003330))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003330+4*1))=0x000062e8;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000330+4*1))=0x000060a4;
*((unsigned int *)((unsigned long)context_ptr+0x00000330+4*2))=0x00006070;
*((unsigned int *)((unsigned long)context_ptr+0x00000330+4*3))=0x02220023;
*((unsigned int *)((unsigned long)context_ptr+0x00000330+4*4))=0x092294af;
*((unsigned int *)((unsigned long)context_ptr+0x00000330+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000007e&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006304,"\xf0\x09\xea\x28\x3d\xdb\x87\x65\xde\xd0\x24\x52\xcb\xe4\x4a\xe3\x34\xce\xd7\x60",20))
printf("strip: f009ea283ddb8765, Pass\n");
else
printf("strip: f009ea283ddb8765, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000062fc))=0x010a0012;
*((unsigned int *)((unsigned long)context_ptr+0x000062fc+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000062fc+4*2))=0x02020024;
*((unsigned int *)((unsigned long)context_ptr+0x000062fc+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x000060c8))=0xd49d00bd;
*((unsigned int *)((unsigned long)context_ptr+0x000060c8+4*1))=0xb46bc5dd;
*((unsigned int *)((unsigned long)context_ptr+0x000060c8+4*2))=0x580910b3;
*((unsigned int *)((unsigned long)context_ptr+0x000060c8+4*3))=0xc2a561a4;
*((unsigned int *)((unsigned long)context_ptr+0x000060c8+4*4))=0x8df848c5;
*((unsigned int *)((unsigned long)context_ptr+0x000060c8+4*5))=0x27aca2a0;
*((unsigned int *)((unsigned long)context_ptr+0x000060c8+4*6))=0xb6f76eac;
*((unsigned int *)((unsigned long)context_ptr+0x000060c8+4*7))=0x96d5fdf9;
*((unsigned int *)((unsigned long)context_ptr+0x000060c8+4*8))=0x6b5e7899;
*((unsigned int *)((unsigned long)context_ptr+0x00003348))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003348+4*1))=0x000063ec;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000348+4*1))=0x000060c8;
*((unsigned int *)((unsigned long)context_ptr+0x00000348+4*2))=0x000062fc;
*((unsigned int *)((unsigned long)context_ptr+0x00000348+4*3))=0x02220024;
*((unsigned int *)((unsigned long)context_ptr+0x00000348+4*4))=0x02b8059c;
*((unsigned int *)((unsigned long)context_ptr+0x00000348+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000084&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006318,"\x01\xc4\xc9\xe7\x5d\x6d\xfd\x89\x57\xeb\xd9\xc3\x14\xb3\x75\xc0\xdc\xba\x56\xe7",20))
printf("strip: 01c4c9e75d6dfd89, Pass\n");
else
printf("strip: 01c4c9e75d6dfd89, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x0000630c))=0x010a0012;
*((unsigned int *)((unsigned long)context_ptr+0x0000630c+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x0000630c+4*2))=0x02020025;
*((unsigned int *)((unsigned long)context_ptr+0x0000630c+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x000060ec))=0xd21dc610;
*((unsigned int *)((unsigned long)context_ptr+0x000060ec+4*1))=0xb71d6eef;
*((unsigned int *)((unsigned long)context_ptr+0x000060ec+4*2))=0x8ae38072;
*((unsigned int *)((unsigned long)context_ptr+0x000060ec+4*3))=0x82d95f23;
*((unsigned int *)((unsigned long)context_ptr+0x000060ec+4*4))=0xe1088114;
*((unsigned int *)((unsigned long)context_ptr+0x000060ec+4*5))=0xe5feba3f;
*((unsigned int *)((unsigned long)context_ptr+0x000060ec+4*6))=0x8bb25287;
*((unsigned int *)((unsigned long)context_ptr+0x000060ec+4*7))=0x27b13de8;
*((unsigned int *)((unsigned long)context_ptr+0x000060ec+4*8))=0x485dc767;
*((unsigned int *)((unsigned long)context_ptr+0x000060ec+4*9))=0x0000005a;
*((unsigned int *)((unsigned long)context_ptr+0x00003360))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003360+4*1))=0x00006400;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000360+4*1))=0x000060ec;
*((unsigned int *)((unsigned long)context_ptr+0x00000360+4*2))=0x0000630c;
*((unsigned int *)((unsigned long)context_ptr+0x00000360+4*3))=0x02220025;
*((unsigned int *)((unsigned long)context_ptr+0x00000360+4*4))=0x024a3b62;
*((unsigned int *)((unsigned long)context_ptr+0x00000360+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000008a&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006144,"\x97\x22\x8b\xb0\xd2\x19\x9c\x1c\x81\xf3\xe7\x01\xb1\xe4\x45\x93\x1d\x1e\x15\x47",20))
printf("strip: 97228bb0d2199c1c, Pass\n");
else
printf("strip: 97228bb0d2199c1c, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x0000631c))=0x010a0012;
*((unsigned int *)((unsigned long)context_ptr+0x0000631c+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x0000631c+4*2))=0x02020026;
*((unsigned int *)((unsigned long)context_ptr+0x0000631c+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x00006114))=0x328c3be3;
*((unsigned int *)((unsigned long)context_ptr+0x00006114+4*1))=0xe4c0a4f7;
*((unsigned int *)((unsigned long)context_ptr+0x00006114+4*2))=0x9e738b74;
*((unsigned int *)((unsigned long)context_ptr+0x00006114+4*3))=0xc55dd255;
*((unsigned int *)((unsigned long)context_ptr+0x00006114+4*4))=0xe67a5d04;
*((unsigned int *)((unsigned long)context_ptr+0x00006114+4*5))=0xe6a2bbb8;
*((unsigned int *)((unsigned long)context_ptr+0x00006114+4*6))=0xc3eba1b9;
*((unsigned int *)((unsigned long)context_ptr+0x00006114+4*7))=0xbf30de03;
*((unsigned int *)((unsigned long)context_ptr+0x00006114+4*8))=0x6d276469;
*((unsigned int *)((unsigned long)context_ptr+0x00006114+4*9))=0x0000d3ff;
*((unsigned int *)((unsigned long)context_ptr+0x00003378))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003378+4*1))=0x0000613c;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000378+4*1))=0x00006114;
*((unsigned int *)((unsigned long)context_ptr+0x00000378+4*2))=0x0000631c;
*((unsigned int *)((unsigned long)context_ptr+0x00000378+4*3))=0x02220026;
*((unsigned int *)((unsigned long)context_ptr+0x00000378+4*4))=0x036f4fc4;
*((unsigned int *)((unsigned long)context_ptr+0x00000378+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000090&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x0000632c,"\x96\x49\xd8\x1f\xbf\xe8\xb3\x57\xe6\x1e\xa5\x58\x74\xdf\x09\x47\xc7\x46\xdf\x28",20))
printf("strip: 9649d81fbfe8b357, Pass\n");
else
printf("strip: 9649d81fbfe8b357, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x0000632c))=0x010a0012;
*((unsigned int *)((unsigned long)context_ptr+0x0000632c+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x0000632c+4*2))=0x02020027;
*((unsigned int *)((unsigned long)context_ptr+0x0000632c+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x00006150))=0xe5886482;
*((unsigned int *)((unsigned long)context_ptr+0x00006150+4*1))=0x2581e418;
*((unsigned int *)((unsigned long)context_ptr+0x00006150+4*2))=0x780631ef;
*((unsigned int *)((unsigned long)context_ptr+0x00006150+4*3))=0x90a00c92;
*((unsigned int *)((unsigned long)context_ptr+0x00006150+4*4))=0x215b1490;
*((unsigned int *)((unsigned long)context_ptr+0x00006150+4*5))=0xe1545e77;
*((unsigned int *)((unsigned long)context_ptr+0x00006150+4*6))=0xffa81c9f;
*((unsigned int *)((unsigned long)context_ptr+0x00006150+4*7))=0x79a8c55d;
*((unsigned int *)((unsigned long)context_ptr+0x00006150+4*8))=0x446a3667;
*((unsigned int *)((unsigned long)context_ptr+0x00006150+4*9))=0x00e3ab7c;
*((unsigned int *)((unsigned long)context_ptr+0x00003390))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003390+4*1))=0x00006414;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000390+4*1))=0x00006150;
*((unsigned int *)((unsigned long)context_ptr+0x00000390+4*2))=0x0000632c;
*((unsigned int *)((unsigned long)context_ptr+0x00000390+4*3))=0x02220027;
*((unsigned int *)((unsigned long)context_ptr+0x00000390+4*4))=0x0c30fe1c;
*((unsigned int *)((unsigned long)context_ptr+0x00000390+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000096&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006340,"\x12\xba\x97\x89\xca\x59\x15\x6b\x5a\x4f\x99\x0c\x64\xb3\xc1\xb2\x27\x4f\xc1\xf6",20))
printf("strip: 12ba9789ca59156b, Pass\n");
else
printf("strip: 12ba9789ca59156b, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x0000633c))=0x010a0012;
*((unsigned int *)((unsigned long)context_ptr+0x0000633c+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x0000633c+4*2))=0x02020028;
*((unsigned int *)((unsigned long)context_ptr+0x0000633c+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x00006178))=0x5be68536;
*((unsigned int *)((unsigned long)context_ptr+0x00006178+4*1))=0x17a8debc;
*((unsigned int *)((unsigned long)context_ptr+0x00006178+4*2))=0x75ffcc84;
*((unsigned int *)((unsigned long)context_ptr+0x00006178+4*3))=0xed7f590e;
*((unsigned int *)((unsigned long)context_ptr+0x00006178+4*4))=0x1970ea10;
*((unsigned int *)((unsigned long)context_ptr+0x00006178+4*5))=0x3c221ec0;
*((unsigned int *)((unsigned long)context_ptr+0x00006178+4*6))=0x96dca98c;
*((unsigned int *)((unsigned long)context_ptr+0x00006178+4*7))=0xa9817ba3;
*((unsigned int *)((unsigned long)context_ptr+0x00006178+4*8))=0x9f9f4b45;
*((unsigned int *)((unsigned long)context_ptr+0x00006178+4*9))=0xd58c322e;
*((unsigned int *)((unsigned long)context_ptr+0x000033a8))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x000033a8+4*1))=0x00006428;
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
*((unsigned int *)((unsigned long)context_ptr+0x000003a8+4*1))=0x00006178;
*((unsigned int *)((unsigned long)context_ptr+0x000003a8+4*2))=0x0000633c;
*((unsigned int *)((unsigned long)context_ptr+0x000003a8+4*3))=0x02220028;
*((unsigned int *)((unsigned long)context_ptr+0x000003a8+4*4))=0x00c6d93a;
*((unsigned int *)((unsigned long)context_ptr+0x000003a8+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000009c&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006354,"\x7e\xd9\x69\x9b\xde\x9c\x59\xa0\x8e\x38\x38\xe0\x10\x3a\x67\x9d\x07\x0b\x8b\x9d",20))
printf("strip: 7ed9699bde9c59a0, Pass\n");
else
printf("strip: 7ed9699bde9c59a0, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x0000634c))=0x010a0012;
*((unsigned int *)((unsigned long)context_ptr+0x0000634c+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x0000634c+4*2))=0x02020029;
*((unsigned int *)((unsigned long)context_ptr+0x0000634c+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x000061a0))=0xdbbd6d4c;
*((unsigned int *)((unsigned long)context_ptr+0x000061a0+4*1))=0x7af721d0;
*((unsigned int *)((unsigned long)context_ptr+0x000061a0+4*2))=0x31f02bf3;
*((unsigned int *)((unsigned long)context_ptr+0x000061a0+4*3))=0x29d745de;
*((unsigned int *)((unsigned long)context_ptr+0x000061a0+4*4))=0xef1fa9da;
*((unsigned int *)((unsigned long)context_ptr+0x000061a0+4*5))=0x0dd72f6f;
*((unsigned int *)((unsigned long)context_ptr+0x000061a0+4*6))=0xbf17bc09;
*((unsigned int *)((unsigned long)context_ptr+0x000061a0+4*7))=0x9023f018;
*((unsigned int *)((unsigned long)context_ptr+0x000061a0+4*8))=0x7d185da5;
*((unsigned int *)((unsigned long)context_ptr+0x000061a0+4*9))=0x3934e455;
*((unsigned int *)((unsigned long)context_ptr+0x000061a0+4*10))=0x00000098;
*((unsigned int *)((unsigned long)context_ptr+0x000033c0))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x000033c0+4*1))=0x0000643c;
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
*((unsigned int *)((unsigned long)context_ptr+0x000003c0+4*1))=0x000061a0;
*((unsigned int *)((unsigned long)context_ptr+0x000003c0+4*2))=0x0000634c;
*((unsigned int *)((unsigned long)context_ptr+0x000003c0+4*3))=0x02220029;
*((unsigned int *)((unsigned long)context_ptr+0x000003c0+4*4))=0x023ed6d6;
*((unsigned int *)((unsigned long)context_ptr+0x000003c0+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000000a2&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006204,"\x6a\xce\x93\xb9\xc5\x18\xde\x44\x85\x03\xf2\x61\xb7\x36\x6c\x3a\x24\x7d\x4e\x5f",20))
printf("strip: 6ace93b9c518de44, Pass\n");
else
printf("strip: 6ace93b9c518de44, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000061cc))=0x010a0012;
*((unsigned int *)((unsigned long)context_ptr+0x000061cc+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000061cc+4*2))=0x0202002a;
*((unsigned int *)((unsigned long)context_ptr+0x000061cc+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x000061dc))=0xee21f56b;
*((unsigned int *)((unsigned long)context_ptr+0x000061dc+4*1))=0x17d0975c;
*((unsigned int *)((unsigned long)context_ptr+0x000061dc+4*2))=0xf8e77a1c;
*((unsigned int *)((unsigned long)context_ptr+0x000061dc+4*3))=0x60cb31a7;
*((unsigned int *)((unsigned long)context_ptr+0x000061dc+4*4))=0x84719743;
*((unsigned int *)((unsigned long)context_ptr+0x000061dc+4*5))=0x6edf09f8;
*((unsigned int *)((unsigned long)context_ptr+0x000061dc+4*6))=0x79bce0d8;
*((unsigned int *)((unsigned long)context_ptr+0x000061dc+4*7))=0xb6659885;
*((unsigned int *)((unsigned long)context_ptr+0x000061dc+4*8))=0x90f456da;
*((unsigned int *)((unsigned long)context_ptr+0x000061dc+4*9))=0x47b9294b;
*((unsigned int *)((unsigned long)context_ptr+0x000061dc+4*10))=0x0000f2cf;
*((unsigned int *)((unsigned long)context_ptr+0x000033d8))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x000033d8+4*1))=0x00006450;
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
*((unsigned int *)((unsigned long)context_ptr+0x000003d8+4*1))=0x000061dc;
*((unsigned int *)((unsigned long)context_ptr+0x000003d8+4*2))=0x000061cc;
*((unsigned int *)((unsigned long)context_ptr+0x000003d8+4*3))=0x0222002a;
*((unsigned int *)((unsigned long)context_ptr+0x000003d8+4*4))=0x04d42c15;
*((unsigned int *)((unsigned long)context_ptr+0x000003d8+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000000a8&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006368,"\x32\xc8\x55\xda\xa1\xda\x2b\x2f\x39\x11\x86\xb8\x5a\x61\xc7\x35\x7d\xba\x89\x9b",20))
printf("strip: 32c855daa1da2b2f, Pass\n");
else
printf("strip: 32c855daa1da2b2f, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x0000635c))=0x010a0012;
*((unsigned int *)((unsigned long)context_ptr+0x0000635c+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x0000635c+4*2))=0x0202002b;
*((unsigned int *)((unsigned long)context_ptr+0x0000635c+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x00006208))=0xbb996417;
*((unsigned int *)((unsigned long)context_ptr+0x00006208+4*1))=0x64dd1ba6;
*((unsigned int *)((unsigned long)context_ptr+0x00006208+4*2))=0xab612bd0;
*((unsigned int *)((unsigned long)context_ptr+0x00006208+4*3))=0xcfec84a1;
*((unsigned int *)((unsigned long)context_ptr+0x00006208+4*4))=0x836aad98;
*((unsigned int *)((unsigned long)context_ptr+0x00006208+4*5))=0x7533d6a1;
*((unsigned int *)((unsigned long)context_ptr+0x00006208+4*6))=0x1e09322f;
*((unsigned int *)((unsigned long)context_ptr+0x00006208+4*7))=0x244e54c1;
*((unsigned int *)((unsigned long)context_ptr+0x00006208+4*8))=0x610e6a93;
*((unsigned int *)((unsigned long)context_ptr+0x00006208+4*9))=0xdbf9c1ce;
*((unsigned int *)((unsigned long)context_ptr+0x00006208+4*10))=0x00c9ca7f;
*((unsigned int *)((unsigned long)context_ptr+0x000033f0))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x000033f0+4*1))=0x00006464;
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
*((unsigned int *)((unsigned long)context_ptr+0x000003f0+4*1))=0x00006208;
*((unsigned int *)((unsigned long)context_ptr+0x000003f0+4*2))=0x0000635c;
*((unsigned int *)((unsigned long)context_ptr+0x000003f0+4*3))=0x0222002b;
*((unsigned int *)((unsigned long)context_ptr+0x000003f0+4*4))=0x08f6262c;
*((unsigned int *)((unsigned long)context_ptr+0x000003f0+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000000ae&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x0000637c,"\x7e\x42\x76\xc2\xaf\xdb\x3e\xe2\x74\x08\x9a\xd6\x57\x3f\x2a\xf5\x06\x1c\x86\x19",20))
printf("strip: 7e4276c2afdb3ee2, Pass\n");
else
printf("strip: 7e4276c2afdb3ee2, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x0000636c))=0x010a0012;
*((unsigned int *)((unsigned long)context_ptr+0x0000636c+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x0000636c+4*2))=0x0202002c;
*((unsigned int *)((unsigned long)context_ptr+0x0000636c+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x00006234))=0xd9f04b7c;
*((unsigned int *)((unsigned long)context_ptr+0x00006234+4*1))=0xcc13b089;
*((unsigned int *)((unsigned long)context_ptr+0x00006234+4*2))=0xe353445b;
*((unsigned int *)((unsigned long)context_ptr+0x00006234+4*3))=0xa076fc1a;
*((unsigned int *)((unsigned long)context_ptr+0x00006234+4*4))=0x66c41081;
*((unsigned int *)((unsigned long)context_ptr+0x00006234+4*5))=0x244fd27b;
*((unsigned int *)((unsigned long)context_ptr+0x00006234+4*6))=0x9710b00b;
*((unsigned int *)((unsigned long)context_ptr+0x00006234+4*7))=0x4a641c11;
*((unsigned int *)((unsigned long)context_ptr+0x00006234+4*8))=0xf6f2f11b;
*((unsigned int *)((unsigned long)context_ptr+0x00006234+4*9))=0x6790e8fa;
*((unsigned int *)((unsigned long)context_ptr+0x00006234+4*10))=0xc63a86bd;
*((unsigned int *)((unsigned long)context_ptr+0x00003408))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003408+4*1))=0x0000637c;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000408+4*1))=0x00006234;
*((unsigned int *)((unsigned long)context_ptr+0x00000408+4*2))=0x0000636c;
*((unsigned int *)((unsigned long)context_ptr+0x00000408+4*3))=0x0222002c;
*((unsigned int *)((unsigned long)context_ptr+0x00000408+4*4))=0x0f323e41;
*((unsigned int *)((unsigned long)context_ptr+0x00000408+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000000b4&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006390,"\xd4\xc1\x8b\x71\xcc\xd8\x78\x09\x58\xf0\x5f\xb6\xbb\xc7\x53\xa2\x1b\x5e\xd7\x16",20))
printf("strip: d4c18b71ccd87809, Pass\n");
else
printf("strip: d4c18b71ccd87809, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006390))=0x010a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006390+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006390+4*2))=0x0202002d;
*((unsigned int *)((unsigned long)context_ptr+0x00006390+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x00006260))=0xa251aac3;
*((unsigned int *)((unsigned long)context_ptr+0x00006260+4*1))=0xa17505a0;
*((unsigned int *)((unsigned long)context_ptr+0x00006260+4*2))=0x02e92961;
*((unsigned int *)((unsigned long)context_ptr+0x00006260+4*3))=0xe9fd2add;
*((unsigned int *)((unsigned long)context_ptr+0x00006260+4*4))=0xddaac417;
*((unsigned int *)((unsigned long)context_ptr+0x00006260+4*5))=0xbcca4f7f;
*((unsigned int *)((unsigned long)context_ptr+0x00006260+4*6))=0x7fc4fc89;
*((unsigned int *)((unsigned long)context_ptr+0x00006260+4*7))=0x0cd781ed;
*((unsigned int *)((unsigned long)context_ptr+0x00006260+4*8))=0x233b3621;
*((unsigned int *)((unsigned long)context_ptr+0x00006260+4*9))=0xb9978f0a;
*((unsigned int *)((unsigned long)context_ptr+0x00006260+4*10))=0x0373749d;
*((unsigned int *)((unsigned long)context_ptr+0x00006260+4*11))=0x0000009d;
*((unsigned int *)((unsigned long)context_ptr+0x00003420))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003420+4*1))=0x00006290;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000420+4*1))=0x00006260;
*((unsigned int *)((unsigned long)context_ptr+0x00000420+4*2))=0x00006390;
*((unsigned int *)((unsigned long)context_ptr+0x00000420+4*3))=0x0222002d;
*((unsigned int *)((unsigned long)context_ptr+0x00000420+4*4))=0x0f631dad;
*((unsigned int *)((unsigned long)context_ptr+0x00000420+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000000ba&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000063a4,"\x63\xa5\x30\xc7\xdd\xff\x13\x45\x98\xe8\x33\x69\x42\x37\xad\x85\x79\xc0\x09\x00",20))
printf("strip: 63a530c7ddff1345, Pass\n");
else
printf("strip: 63a530c7ddff1345, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006018))=0x010a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006018+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006018+4*2))=0x0202002e;
*((unsigned int *)((unsigned long)context_ptr+0x00006018+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x00006478))=0x0e55f740;
*((unsigned int *)((unsigned long)context_ptr+0x00006478+4*1))=0x79482cab;
*((unsigned int *)((unsigned long)context_ptr+0x00006478+4*2))=0xc2ec4d8a;
*((unsigned int *)((unsigned long)context_ptr+0x00006478+4*3))=0xd4d113a0;
*((unsigned int *)((unsigned long)context_ptr+0x00006478+4*4))=0xe62cd4ce;
*((unsigned int *)((unsigned long)context_ptr+0x00006478+4*5))=0x2800434b;
*((unsigned int *)((unsigned long)context_ptr+0x00006478+4*6))=0x0cdf3b58;
*((unsigned int *)((unsigned long)context_ptr+0x00006478+4*7))=0xd5dd6071;
*((unsigned int *)((unsigned long)context_ptr+0x00006478+4*8))=0x4075ad53;
*((unsigned int *)((unsigned long)context_ptr+0x00006478+4*9))=0xbcb277b2;
*((unsigned int *)((unsigned long)context_ptr+0x00006478+4*10))=0x0223438f;
*((unsigned int *)((unsigned long)context_ptr+0x00006478+4*11))=0x0000a96c;
*((unsigned int *)((unsigned long)context_ptr+0x00003438))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003438+4*1))=0x000063a0;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000438+4*1))=0x00006478;
*((unsigned int *)((unsigned long)context_ptr+0x00000438+4*2))=0x00006018;
*((unsigned int *)((unsigned long)context_ptr+0x00000438+4*3))=0x0222002e;
*((unsigned int *)((unsigned long)context_ptr+0x00000438+4*4))=0x01177fc2;
*((unsigned int *)((unsigned long)context_ptr+0x00000438+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000000c0&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006038,"\xf0\x76\x40\x60\xcc\x8f\x3d\xbc\xaf\xd8\x72\x4a\xa8\xa8\x7a\xe6\x02\x91\x07\x0f",20))
printf("strip: f0764060cc8f3dbc, Pass\n");
else
printf("strip: f0764060cc8f3dbc, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006008))=0x010a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006008+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006008+4*2))=0x0202002f;
*((unsigned int *)((unsigned long)context_ptr+0x00006008+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x000064a8))=0x6b2f4341;
*((unsigned int *)((unsigned long)context_ptr+0x000064a8+4*1))=0x2ddb2618;
*((unsigned int *)((unsigned long)context_ptr+0x000064a8+4*2))=0x44cb1472;
*((unsigned int *)((unsigned long)context_ptr+0x000064a8+4*3))=0x3469d1a9;
*((unsigned int *)((unsigned long)context_ptr+0x000064a8+4*4))=0xa8987528;
*((unsigned int *)((unsigned long)context_ptr+0x000064a8+4*5))=0x22003e96;
*((unsigned int *)((unsigned long)context_ptr+0x000064a8+4*6))=0xfa91f870;
*((unsigned int *)((unsigned long)context_ptr+0x000064a8+4*7))=0xb04afed7;
*((unsigned int *)((unsigned long)context_ptr+0x000064a8+4*8))=0x679dde6e;
*((unsigned int *)((unsigned long)context_ptr+0x000064a8+4*9))=0x6c7ed7f1;
*((unsigned int *)((unsigned long)context_ptr+0x000064a8+4*10))=0x2a4f6767;
*((unsigned int *)((unsigned long)context_ptr+0x000064a8+4*11))=0x009f1fd4;
*((unsigned int *)((unsigned long)context_ptr+0x00003450))=0x04c00014;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000450+4*1))=0x000064a8;
*((unsigned int *)((unsigned long)context_ptr+0x00000450+4*2))=0x00006008;
*((unsigned int *)((unsigned long)context_ptr+0x00000450+4*3))=0x0222002f;
*((unsigned int *)((unsigned long)context_ptr+0x00000450+4*4))=0x03a51b13;
*((unsigned int *)((unsigned long)context_ptr+0x00000450+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000000c6&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x0000605c,"\x53\x81\x6c\x80\x94\x36\x57\x2d\xae\x25\x0c\x42\x3e\x5d\x6b\x70\x7d\x81\xc1\x7e",20))
printf("strip: 53816c809436572d, Pass\n");
else
printf("strip: 53816c809436572d, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006028))=0x010a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006028+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006028+4*2))=0x02020030;
*((unsigned int *)((unsigned long)context_ptr+0x00006028+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x000062a4))=0x9855695f;
*((unsigned int *)((unsigned long)context_ptr+0x000062a4+4*1))=0x8e1b4286;
*((unsigned int *)((unsigned long)context_ptr+0x000062a4+4*2))=0x6c570e8e;
*((unsigned int *)((unsigned long)context_ptr+0x000062a4+4*3))=0xcdab517b;
*((unsigned int *)((unsigned long)context_ptr+0x000062a4+4*4))=0x97aa6b1e;
*((unsigned int *)((unsigned long)context_ptr+0x000062a4+4*5))=0xe38bdedf;
*((unsigned int *)((unsigned long)context_ptr+0x000062a4+4*6))=0x620226ce;
*((unsigned int *)((unsigned long)context_ptr+0x000062a4+4*7))=0x84cf075d;
*((unsigned int *)((unsigned long)context_ptr+0x000062a4+4*8))=0x66ced5f9;
*((unsigned int *)((unsigned long)context_ptr+0x000062a4+4*9))=0x8d1ab6f1;
*((unsigned int *)((unsigned long)context_ptr+0x000062a4+4*10))=0x0a67a436;
*((unsigned int *)((unsigned long)context_ptr+0x000062a4+4*11))=0x35a3ebe6;
*((unsigned int *)((unsigned long)context_ptr+0x00003468))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003468+4*1))=0x0000605c;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000468+4*1))=0x000062a4;
*((unsigned int *)((unsigned long)context_ptr+0x00000468+4*2))=0x00006028;
*((unsigned int *)((unsigned long)context_ptr+0x00000468+4*3))=0x02220030;
*((unsigned int *)((unsigned long)context_ptr+0x00000468+4*4))=0x01da8f42;
*((unsigned int *)((unsigned long)context_ptr+0x00000468+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000000cc&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000063d8,"\xc5\xd5\x7a\x07\xd4\xf4\xdb\x5a\xf5\x6c\x40\xf2\x1d\x0f\x89\x32\x12\x87\xcf\x59",20))
printf("strip: c5d57a07d4f4db5a, Pass\n");
else
printf("strip: c5d57a07d4f4db5a, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x0000604c))=0x010a0012;
*((unsigned int *)((unsigned long)context_ptr+0x0000604c+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x0000604c+4*2))=0x02020031;
*((unsigned int *)((unsigned long)context_ptr+0x0000604c+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x000063b4))=0x3936fade;
*((unsigned int *)((unsigned long)context_ptr+0x000063b4+4*1))=0x6dd00694;
*((unsigned int *)((unsigned long)context_ptr+0x000063b4+4*2))=0x8ccb06bb;
*((unsigned int *)((unsigned long)context_ptr+0x000063b4+4*3))=0x9f680c05;
*((unsigned int *)((unsigned long)context_ptr+0x000063b4+4*4))=0x61e6a473;
*((unsigned int *)((unsigned long)context_ptr+0x000063b4+4*5))=0x560bcb6b;
*((unsigned int *)((unsigned long)context_ptr+0x000063b4+4*6))=0xa9aca70f;
*((unsigned int *)((unsigned long)context_ptr+0x000063b4+4*7))=0xa103be9e;
*((unsigned int *)((unsigned long)context_ptr+0x000063b4+4*8))=0x08c1d5a1;
*((unsigned int *)((unsigned long)context_ptr+0x000063b4+4*9))=0x1b476997;
*((unsigned int *)((unsigned long)context_ptr+0x000063b4+4*10))=0x7b3d271f;
*((unsigned int *)((unsigned long)context_ptr+0x000063b4+4*11))=0x8534429a;
*((unsigned int *)((unsigned long)context_ptr+0x000063b4+4*12))=0x0000007c;
*((unsigned int *)((unsigned long)context_ptr+0x00003480))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003480+4*1))=0x000062d4;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000480+4*1))=0x000063b4;
*((unsigned int *)((unsigned long)context_ptr+0x00000480+4*2))=0x0000604c;
*((unsigned int *)((unsigned long)context_ptr+0x00000480+4*3))=0x02220031;
*((unsigned int *)((unsigned long)context_ptr+0x00000480+4*4))=0x064d1376;
*((unsigned int *)((unsigned long)context_ptr+0x00000480+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000000d2&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000062e8,"\xe6\x1e\xdb\xb0\xd1\xd1\x8c\x56\x98\x6d\xd0\x6f\xfb\x53\xc1\x7a\xf1\x4e\xfd\xb6",20))
printf("strip: e61edbb0d1d18c56, Pass\n");
else
printf("strip: e61edbb0d1d18c56, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006070))=0x010a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006070+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006070+4*2))=0x02020032;
*((unsigned int *)((unsigned long)context_ptr+0x00006070+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x00006080))=0x55dc2a8f;
*((unsigned int *)((unsigned long)context_ptr+0x00006080+4*1))=0x7cc04a23;
*((unsigned int *)((unsigned long)context_ptr+0x00006080+4*2))=0x3f9e44a3;
*((unsigned int *)((unsigned long)context_ptr+0x00006080+4*3))=0x4d71b703;
*((unsigned int *)((unsigned long)context_ptr+0x00006080+4*4))=0xf8ce6186;
*((unsigned int *)((unsigned long)context_ptr+0x00006080+4*5))=0x02a709a6;
*((unsigned int *)((unsigned long)context_ptr+0x00006080+4*6))=0x06dd1766;
*((unsigned int *)((unsigned long)context_ptr+0x00006080+4*7))=0x428276ad;
*((unsigned int *)((unsigned long)context_ptr+0x00006080+4*8))=0x7d736e60;
*((unsigned int *)((unsigned long)context_ptr+0x00006080+4*9))=0x84dca1d5;
*((unsigned int *)((unsigned long)context_ptr+0x00006080+4*10))=0xbcb6a086;
*((unsigned int *)((unsigned long)context_ptr+0x00006080+4*11))=0xbc46668f;
*((unsigned int *)((unsigned long)context_ptr+0x00006080+4*12))=0x0000f50f;
*((unsigned int *)((unsigned long)context_ptr+0x00003498))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003498+4*1))=0x000062e8;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000498+4*1))=0x00006080;
*((unsigned int *)((unsigned long)context_ptr+0x00000498+4*2))=0x00006070;
*((unsigned int *)((unsigned long)context_ptr+0x00000498+4*3))=0x02220032;
*((unsigned int *)((unsigned long)context_ptr+0x00000498+4*4))=0x0e321094;
*((unsigned int *)((unsigned long)context_ptr+0x00000498+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000000d8&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000063ec,"\x56\x8b\xcf\x1f\x2c\xf4\x43\x0f\x44\x53\xf4\x79\x37\x7b\x60\x8c\x5b\x5c\x1c\xbf",20))
printf("strip: 568bcf1f2cf4430f, Pass\n");
else
printf("strip: 568bcf1f2cf4430f, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000062fc))=0x010a0012;
*((unsigned int *)((unsigned long)context_ptr+0x000062fc+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000062fc+4*2))=0x02020033;
*((unsigned int *)((unsigned long)context_ptr+0x000062fc+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x000060b4))=0x8eedb88a;
*((unsigned int *)((unsigned long)context_ptr+0x000060b4+4*1))=0x48b18343;
*((unsigned int *)((unsigned long)context_ptr+0x000060b4+4*2))=0x344c3121;
*((unsigned int *)((unsigned long)context_ptr+0x000060b4+4*3))=0xb06f0a4b;
*((unsigned int *)((unsigned long)context_ptr+0x000060b4+4*4))=0x6b1a2a02;
*((unsigned int *)((unsigned long)context_ptr+0x000060b4+4*5))=0x5a6644df;
*((unsigned int *)((unsigned long)context_ptr+0x000060b4+4*6))=0x0a371727;
*((unsigned int *)((unsigned long)context_ptr+0x000060b4+4*7))=0xfd47c264;
*((unsigned int *)((unsigned long)context_ptr+0x000060b4+4*8))=0x9191c181;
*((unsigned int *)((unsigned long)context_ptr+0x000060b4+4*9))=0x2934c8c8;
*((unsigned int *)((unsigned long)context_ptr+0x000060b4+4*10))=0x3b143b2f;
*((unsigned int *)((unsigned long)context_ptr+0x000060b4+4*11))=0x9d07a165;
*((unsigned int *)((unsigned long)context_ptr+0x000060b4+4*12))=0x00a7e4b5;
*((unsigned int *)((unsigned long)context_ptr+0x000034b0))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x000034b0+4*1))=0x000063e8;
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
*((unsigned int *)((unsigned long)context_ptr+0x000004b0+4*1))=0x000060b4;
*((unsigned int *)((unsigned long)context_ptr+0x000004b0+4*2))=0x000062fc;
*((unsigned int *)((unsigned long)context_ptr+0x000004b0+4*3))=0x02220033;
*((unsigned int *)((unsigned long)context_ptr+0x000004b0+4*4))=0x061d944d;
*((unsigned int *)((unsigned long)context_ptr+0x000004b0+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000000de&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006400,"\x53\x8c\x91\xd6\x4f\x4e\x7c\x7f\xa8\x10\x86\xe3\xc8\xbd\x77\xf4\x12\x26\x7c\xd0",20))
printf("strip: 538c91d64f4e7c7f, Pass\n");
else
printf("strip: 538c91d64f4e7c7f, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x0000630c))=0x010a0012;
*((unsigned int *)((unsigned long)context_ptr+0x0000630c+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x0000630c+4*2))=0x02020034;
*((unsigned int *)((unsigned long)context_ptr+0x0000630c+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x000064d8))=0x08b36f5a;
*((unsigned int *)((unsigned long)context_ptr+0x000064d8+4*1))=0x0ba6c53f;
*((unsigned int *)((unsigned long)context_ptr+0x000064d8+4*2))=0xf01d9860;
*((unsigned int *)((unsigned long)context_ptr+0x000064d8+4*3))=0x40119b2c;
*((unsigned int *)((unsigned long)context_ptr+0x000064d8+4*4))=0xe4fac325;
*((unsigned int *)((unsigned long)context_ptr+0x000064d8+4*5))=0xa8e8a437;
*((unsigned int *)((unsigned long)context_ptr+0x000064d8+4*6))=0xa554720f;
*((unsigned int *)((unsigned long)context_ptr+0x000064d8+4*7))=0x0e0ca80f;
*((unsigned int *)((unsigned long)context_ptr+0x000064d8+4*8))=0x43c4dd3a;
*((unsigned int *)((unsigned long)context_ptr+0x000064d8+4*9))=0x8eee4202;
*((unsigned int *)((unsigned long)context_ptr+0x000064d8+4*10))=0xd8a1b914;
*((unsigned int *)((unsigned long)context_ptr+0x000064d8+4*11))=0xe0add8fa;
*((unsigned int *)((unsigned long)context_ptr+0x000064d8+4*12))=0x4c83369e;
*((unsigned int *)((unsigned long)context_ptr+0x000034c8))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x000034c8+4*1))=0x000063fc;
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
*((unsigned int *)((unsigned long)context_ptr+0x000004c8+4*1))=0x000064d8;
*((unsigned int *)((unsigned long)context_ptr+0x000004c8+4*2))=0x0000630c;
*((unsigned int *)((unsigned long)context_ptr+0x000004c8+4*3))=0x02220034;
*((unsigned int *)((unsigned long)context_ptr+0x000004c8+4*4))=0x0113ed68;
*((unsigned int *)((unsigned long)context_ptr+0x000004c8+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000000e4&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x0000613c,"\xb6\xee\x9a\x60\x67\x10\xfe\x4a\x62\x83\xe1\x49\xcf\xdd\xa5\xe2\xf2\xa7\x28\x65",20))
printf("strip: b6ee9a606710fe4a, Pass\n");
else
printf("strip: b6ee9a606710fe4a, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x0000631c))=0x010a0012;
*((unsigned int *)((unsigned long)context_ptr+0x0000631c+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x0000631c+4*2))=0x02020035;
*((unsigned int *)((unsigned long)context_ptr+0x0000631c+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x000060e8))=0x6c50bae2;
*((unsigned int *)((unsigned long)context_ptr+0x000060e8+4*1))=0x605fd93d;
*((unsigned int *)((unsigned long)context_ptr+0x000060e8+4*2))=0xd1488f63;
*((unsigned int *)((unsigned long)context_ptr+0x000060e8+4*3))=0x6011caab;
*((unsigned int *)((unsigned long)context_ptr+0x000060e8+4*4))=0xda563135;
*((unsigned int *)((unsigned long)context_ptr+0x000060e8+4*5))=0xc9d91060;
*((unsigned int *)((unsigned long)context_ptr+0x000060e8+4*6))=0x5b270b8c;
*((unsigned int *)((unsigned long)context_ptr+0x000060e8+4*7))=0xf7c44c6a;
*((unsigned int *)((unsigned long)context_ptr+0x000060e8+4*8))=0x23732b6d;
*((unsigned int *)((unsigned long)context_ptr+0x000060e8+4*9))=0x5afb6876;
*((unsigned int *)((unsigned long)context_ptr+0x000060e8+4*10))=0xb2b4ee1f;
*((unsigned int *)((unsigned long)context_ptr+0x000060e8+4*11))=0x4ab63453;
*((unsigned int *)((unsigned long)context_ptr+0x000060e8+4*12))=0xa270189d;
*((unsigned int *)((unsigned long)context_ptr+0x000060e8+4*13))=0x0000008c;
*((unsigned int *)((unsigned long)context_ptr+0x000034e0))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x000034e0+4*1))=0x00006120;
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
*((unsigned int *)((unsigned long)context_ptr+0x000004e0+4*1))=0x000060e8;
*((unsigned int *)((unsigned long)context_ptr+0x000004e0+4*2))=0x0000631c;
*((unsigned int *)((unsigned long)context_ptr+0x000004e0+4*3))=0x02220035;
*((unsigned int *)((unsigned long)context_ptr+0x000004e0+4*4))=0x074784fc;
*((unsigned int *)((unsigned long)context_ptr+0x000004e0+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000000ea&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006414,"\xf1\x6a\xc0\x53\xcb\x6d\xd8\xba\xf7\xb9\x84\x15\x79\x06\xcf\x2d\x9f\xea\x75\x15",20))
printf("strip: f16ac053cb6dd8ba, Pass\n");
else
printf("strip: f16ac053cb6dd8ba, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x0000632c))=0x010a0012;
*((unsigned int *)((unsigned long)context_ptr+0x0000632c+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x0000632c+4*2))=0x02020036;
*((unsigned int *)((unsigned long)context_ptr+0x0000632c+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x00006134))=0x41ffeaeb;
*((unsigned int *)((unsigned long)context_ptr+0x00006134+4*1))=0x655e9d37;
*((unsigned int *)((unsigned long)context_ptr+0x00006134+4*2))=0xcedaadc5;
*((unsigned int *)((unsigned long)context_ptr+0x00006134+4*3))=0xca6c1a7d;
*((unsigned int *)((unsigned long)context_ptr+0x00006134+4*4))=0xd166d75d;
*((unsigned int *)((unsigned long)context_ptr+0x00006134+4*5))=0xec01abc2;
*((unsigned int *)((unsigned long)context_ptr+0x00006134+4*6))=0xdc03175d;
*((unsigned int *)((unsigned long)context_ptr+0x00006134+4*7))=0xeffc966b;
*((unsigned int *)((unsigned long)context_ptr+0x00006134+4*8))=0x6ba4bba1;
*((unsigned int *)((unsigned long)context_ptr+0x00006134+4*9))=0x364c351d;
*((unsigned int *)((unsigned long)context_ptr+0x00006134+4*10))=0xb23c34ee;
*((unsigned int *)((unsigned long)context_ptr+0x00006134+4*11))=0xd04ba3f8;
*((unsigned int *)((unsigned long)context_ptr+0x00006134+4*12))=0xc07ea628;
*((unsigned int *)((unsigned long)context_ptr+0x00006134+4*13))=0x00009f7c;
*((unsigned int *)((unsigned long)context_ptr+0x000034f8))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x000034f8+4*1))=0x00006410;
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
*((unsigned int *)((unsigned long)context_ptr+0x000004f8+4*1))=0x00006134;
*((unsigned int *)((unsigned long)context_ptr+0x000004f8+4*2))=0x0000632c;
*((unsigned int *)((unsigned long)context_ptr+0x000004f8+4*3))=0x02220036;
*((unsigned int *)((unsigned long)context_ptr+0x000004f8+4*4))=0x0b982a17;
*((unsigned int *)((unsigned long)context_ptr+0x000004f8+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000000f0&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006428,"\x89\xab\xc5\xdf\x0b\x58\x0d\xe9\xc2\xd0\xb1\x14\xaf\x81\xb0\x8a\xb9\x49\xa4\xdb",20))
printf("strip: 89abc5df0b580de9, Pass\n");
else
printf("strip: 89abc5df0b580de9, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x0000633c))=0x010a0012;
*((unsigned int *)((unsigned long)context_ptr+0x0000633c+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x0000633c+4*2))=0x02020037;
*((unsigned int *)((unsigned long)context_ptr+0x0000633c+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x0000650c))=0x26b7eb58;
*((unsigned int *)((unsigned long)context_ptr+0x0000650c+4*1))=0x9d3431c9;
*((unsigned int *)((unsigned long)context_ptr+0x0000650c+4*2))=0xb0296135;
*((unsigned int *)((unsigned long)context_ptr+0x0000650c+4*3))=0xfc18e89d;
*((unsigned int *)((unsigned long)context_ptr+0x0000650c+4*4))=0xf259074e;
*((unsigned int *)((unsigned long)context_ptr+0x0000650c+4*5))=0xad467e4a;
*((unsigned int *)((unsigned long)context_ptr+0x0000650c+4*6))=0xa01bec5f;
*((unsigned int *)((unsigned long)context_ptr+0x0000650c+4*7))=0xc6885efc;
*((unsigned int *)((unsigned long)context_ptr+0x0000650c+4*8))=0xe1da7925;
*((unsigned int *)((unsigned long)context_ptr+0x0000650c+4*9))=0xae88cc86;
*((unsigned int *)((unsigned long)context_ptr+0x0000650c+4*10))=0x0b1713cf;
*((unsigned int *)((unsigned long)context_ptr+0x0000650c+4*11))=0x5b8138e5;
*((unsigned int *)((unsigned long)context_ptr+0x0000650c+4*12))=0x1bde5963;
*((unsigned int *)((unsigned long)context_ptr+0x0000650c+4*13))=0x009580bd;
*((unsigned int *)((unsigned long)context_ptr+0x00003510))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003510+4*1))=0x00006424;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000510+4*1))=0x0000650c;
*((unsigned int *)((unsigned long)context_ptr+0x00000510+4*2))=0x0000633c;
*((unsigned int *)((unsigned long)context_ptr+0x00000510+4*3))=0x02220037;
*((unsigned int *)((unsigned long)context_ptr+0x00000510+4*4))=0x08b04fdf;
*((unsigned int *)((unsigned long)context_ptr+0x00000510+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000000f6&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x0000643c,"\x33\x5e\xd8\xe3\x55\xb3\x2a\x45\x8d\xa8\xc9\x28\x40\x16\x53\x44\xea\x1f\x56\x60",20))
printf("strip: 335ed8e355b32a45, Pass\n");
else
printf("strip: 335ed8e355b32a45, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x0000634c))=0x010a0012;
*((unsigned int *)((unsigned long)context_ptr+0x0000634c+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x0000634c+4*2))=0x02020038;
*((unsigned int *)((unsigned long)context_ptr+0x0000634c+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x0000616c))=0xc67a306d;
*((unsigned int *)((unsigned long)context_ptr+0x0000616c+4*1))=0x2928d80a;
*((unsigned int *)((unsigned long)context_ptr+0x0000616c+4*2))=0xd9afbd36;
*((unsigned int *)((unsigned long)context_ptr+0x0000616c+4*3))=0x2929e730;
*((unsigned int *)((unsigned long)context_ptr+0x0000616c+4*4))=0xacc2556b;
*((unsigned int *)((unsigned long)context_ptr+0x0000616c+4*5))=0x1a861c0f;
*((unsigned int *)((unsigned long)context_ptr+0x0000616c+4*6))=0x029eb78f;
*((unsigned int *)((unsigned long)context_ptr+0x0000616c+4*7))=0x867541ef;
*((unsigned int *)((unsigned long)context_ptr+0x0000616c+4*8))=0xd6a84ffa;
*((unsigned int *)((unsigned long)context_ptr+0x0000616c+4*9))=0x21473990;
*((unsigned int *)((unsigned long)context_ptr+0x0000616c+4*10))=0xeb547ebb;
*((unsigned int *)((unsigned long)context_ptr+0x0000616c+4*11))=0x649e2033;
*((unsigned int *)((unsigned long)context_ptr+0x0000616c+4*12))=0x049b9661;
*((unsigned int *)((unsigned long)context_ptr+0x0000616c+4*13))=0x36080c19;
*((unsigned int *)((unsigned long)context_ptr+0x00003528))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003528+4*1))=0x00006438;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000528+4*1))=0x0000616c;
*((unsigned int *)((unsigned long)context_ptr+0x00000528+4*2))=0x0000634c;
*((unsigned int *)((unsigned long)context_ptr+0x00000528+4*3))=0x02220038;
*((unsigned int *)((unsigned long)context_ptr+0x00000528+4*4))=0x0317bf35;
*((unsigned int *)((unsigned long)context_ptr+0x00000528+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000000fc&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006450,"\xf1\x67\x30\xa7\xe4\xf4\xcb\xd8\x08\x28\x7b\x3e\x88\x19\x09\x1b\x64\x55\x88\x62",20))
printf("strip: f16730a7e4f4cbd8, Pass\n");
else
printf("strip: f16730a7e4f4cbd8, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x0000644c))=0x010a0012;
*((unsigned int *)((unsigned long)context_ptr+0x0000644c+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x0000644c+4*2))=0x02020039;
*((unsigned int *)((unsigned long)context_ptr+0x0000644c+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x000061a4))=0xdd8bb8ec;
*((unsigned int *)((unsigned long)context_ptr+0x000061a4+4*1))=0x7f39edeb;
*((unsigned int *)((unsigned long)context_ptr+0x000061a4+4*2))=0x9a690ca3;
*((unsigned int *)((unsigned long)context_ptr+0x000061a4+4*3))=0x50520ad7;
*((unsigned int *)((unsigned long)context_ptr+0x000061a4+4*4))=0x7dfd5329;
*((unsigned int *)((unsigned long)context_ptr+0x000061a4+4*5))=0xebfcc912;
*((unsigned int *)((unsigned long)context_ptr+0x000061a4+4*6))=0x92d2679c;
*((unsigned int *)((unsigned long)context_ptr+0x000061a4+4*7))=0xb279aa2d;
*((unsigned int *)((unsigned long)context_ptr+0x000061a4+4*8))=0x4a4d4a34;
*((unsigned int *)((unsigned long)context_ptr+0x000061a4+4*9))=0x03aa59b4;
*((unsigned int *)((unsigned long)context_ptr+0x000061a4+4*10))=0x0cea7706;
*((unsigned int *)((unsigned long)context_ptr+0x000061a4+4*11))=0x124fff15;
*((unsigned int *)((unsigned long)context_ptr+0x000061a4+4*12))=0x96391410;
*((unsigned int *)((unsigned long)context_ptr+0x000061a4+4*13))=0x55f1d708;
*((unsigned int *)((unsigned long)context_ptr+0x000061a4+4*14))=0x000000d4;
*((unsigned int *)((unsigned long)context_ptr+0x00003540))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003540+4*1))=0x000061e0;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000540+4*1))=0x000061a4;
*((unsigned int *)((unsigned long)context_ptr+0x00000540+4*2))=0x0000644c;
*((unsigned int *)((unsigned long)context_ptr+0x00000540+4*3))=0x02220039;
*((unsigned int *)((unsigned long)context_ptr+0x00000540+4*4))=0x0d420032;
*((unsigned int *)((unsigned long)context_ptr+0x00000540+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000102&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006464,"\x05\x1a\x26\x1e\x56\xca\x7f\xc8\xd4\x16\x43\x9f\x62\x74\xdc\xb8\x8f\xe6\x02\x6d",20))
printf("strip: 051a261e56ca7fc8, Pass\n");
else
printf("strip: 051a261e56ca7fc8, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x0000635c))=0x010a0012;
*((unsigned int *)((unsigned long)context_ptr+0x0000635c+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x0000635c+4*2))=0x0202003a;
*((unsigned int *)((unsigned long)context_ptr+0x0000635c+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x000061f4))=0xaa795edd;
*((unsigned int *)((unsigned long)context_ptr+0x000061f4+4*1))=0x3d73a239;
*((unsigned int *)((unsigned long)context_ptr+0x000061f4+4*2))=0x48ad973f;
*((unsigned int *)((unsigned long)context_ptr+0x000061f4+4*3))=0x9758f762;
*((unsigned int *)((unsigned long)context_ptr+0x000061f4+4*4))=0x5f3b6a74;
*((unsigned int *)((unsigned long)context_ptr+0x000061f4+4*5))=0xf4ff74d4;
*((unsigned int *)((unsigned long)context_ptr+0x000061f4+4*6))=0x09b42142;
*((unsigned int *)((unsigned long)context_ptr+0x000061f4+4*7))=0x753c4a32;
*((unsigned int *)((unsigned long)context_ptr+0x000061f4+4*8))=0x2e527cf3;
*((unsigned int *)((unsigned long)context_ptr+0x000061f4+4*9))=0x89380080;
*((unsigned int *)((unsigned long)context_ptr+0x000061f4+4*10))=0x4f555fdd;
*((unsigned int *)((unsigned long)context_ptr+0x000061f4+4*11))=0xace683dd;
*((unsigned int *)((unsigned long)context_ptr+0x000061f4+4*12))=0x0e156341;
*((unsigned int *)((unsigned long)context_ptr+0x000061f4+4*13))=0x3ad295ed;
*((unsigned int *)((unsigned long)context_ptr+0x000061f4+4*14))=0x00008a8f;
*((unsigned int *)((unsigned long)context_ptr+0x00003558))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003558+4*1))=0x0000645c;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000558+4*1))=0x000061f4;
*((unsigned int *)((unsigned long)context_ptr+0x00000558+4*2))=0x0000635c;
*((unsigned int *)((unsigned long)context_ptr+0x00000558+4*3))=0x0222003a;
*((unsigned int *)((unsigned long)context_ptr+0x00000558+4*4))=0x0f0bed3d;
*((unsigned int *)((unsigned long)context_ptr+0x00000558+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000108&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x0000637c,"\x90\xe2\x12\xd9\xb2\x48\xa2\xab\xeb\x9b\xc5\x2b\x8c\xe7\xa6\x6d\xf1\xc6\x2f\x6b",20))
printf("strip: 90e212d9b248a2ab, Pass\n");
else
printf("strip: 90e212d9b248a2ab, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x0000636c))=0x010a0012;
*((unsigned int *)((unsigned long)context_ptr+0x0000636c+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x0000636c+4*2))=0x0202003b;
*((unsigned int *)((unsigned long)context_ptr+0x0000636c+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x00006544))=0xc1dc8057;
*((unsigned int *)((unsigned long)context_ptr+0x00006544+4*1))=0x3183fa97;
*((unsigned int *)((unsigned long)context_ptr+0x00006544+4*2))=0x7e655f7d;
*((unsigned int *)((unsigned long)context_ptr+0x00006544+4*3))=0xf0b38bd2;
*((unsigned int *)((unsigned long)context_ptr+0x00006544+4*4))=0x9fcaba1e;
*((unsigned int *)((unsigned long)context_ptr+0x00006544+4*5))=0x261850bb;
*((unsigned int *)((unsigned long)context_ptr+0x00006544+4*6))=0x752e7ed5;
*((unsigned int *)((unsigned long)context_ptr+0x00006544+4*7))=0x2f067b86;
*((unsigned int *)((unsigned long)context_ptr+0x00006544+4*8))=0x4fc65799;
*((unsigned int *)((unsigned long)context_ptr+0x00006544+4*9))=0x4d5290c9;
*((unsigned int *)((unsigned long)context_ptr+0x00006544+4*10))=0xebc71267;
*((unsigned int *)((unsigned long)context_ptr+0x00006544+4*11))=0x18c996a3;
*((unsigned int *)((unsigned long)context_ptr+0x00006544+4*12))=0x9027afbf;
*((unsigned int *)((unsigned long)context_ptr+0x00006544+4*13))=0x1a143dcd;
*((unsigned int *)((unsigned long)context_ptr+0x00006544+4*14))=0x00d5624e;
*((unsigned int *)((unsigned long)context_ptr+0x00003570))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003570+4*1))=0x0000637c;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000570+4*1))=0x00006544;
*((unsigned int *)((unsigned long)context_ptr+0x00000570+4*2))=0x0000636c;
*((unsigned int *)((unsigned long)context_ptr+0x00000570+4*3))=0x0222003b;
*((unsigned int *)((unsigned long)context_ptr+0x00000570+4*4))=0x03c5a74e;
*((unsigned int *)((unsigned long)context_ptr+0x00000570+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000010e&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006290,"\xb0\x89\x01\x5d\x1f\x55\xee\x84\x6b\x4f\xf1\xd1\x7c\x60\x12\x2d\xe9\xf2\x6d\x1c",20))
printf("strip: b089015d1f55ee84, Pass\n");
else
printf("strip: b089015d1f55ee84, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006390))=0x010a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006390+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006390+4*2))=0x0202003c;
*((unsigned int *)((unsigned long)context_ptr+0x00006390+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x00006230))=0x5e688756;
*((unsigned int *)((unsigned long)context_ptr+0x00006230+4*1))=0x8263a416;
*((unsigned int *)((unsigned long)context_ptr+0x00006230+4*2))=0xb54bfe0d;
*((unsigned int *)((unsigned long)context_ptr+0x00006230+4*3))=0x5a5f2bcd;
*((unsigned int *)((unsigned long)context_ptr+0x00006230+4*4))=0xa6c1a82b;
*((unsigned int *)((unsigned long)context_ptr+0x00006230+4*5))=0x7f6a17bc;
*((unsigned int *)((unsigned long)context_ptr+0x00006230+4*6))=0x868a74f7;
*((unsigned int *)((unsigned long)context_ptr+0x00006230+4*7))=0xeee4002d;
*((unsigned int *)((unsigned long)context_ptr+0x00006230+4*8))=0x92e12704;
*((unsigned int *)((unsigned long)context_ptr+0x00006230+4*9))=0x42cd8515;
*((unsigned int *)((unsigned long)context_ptr+0x00006230+4*10))=0x0164bc6c;
*((unsigned int *)((unsigned long)context_ptr+0x00006230+4*11))=0x6ab08d48;
*((unsigned int *)((unsigned long)context_ptr+0x00006230+4*12))=0xddf9b451;
*((unsigned int *)((unsigned long)context_ptr+0x00006230+4*13))=0x35a9207e;
*((unsigned int *)((unsigned long)context_ptr+0x00006230+4*14))=0xb639a03a;
*((unsigned int *)((unsigned long)context_ptr+0x00003588))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003588+4*1))=0x0000626c;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000588+4*1))=0x00006230;
*((unsigned int *)((unsigned long)context_ptr+0x00000588+4*2))=0x00006390;
*((unsigned int *)((unsigned long)context_ptr+0x00000588+4*3))=0x0222003c;
*((unsigned int *)((unsigned long)context_ptr+0x00000588+4*4))=0x0cdbfa82;
*((unsigned int *)((unsigned long)context_ptr+0x00000588+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000114&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000063a0,"\xb1\x79\xce\x16\x94\xc0\x9d\xb3\x89\xb0\x69\xc0\x38\x0d\xfc\x0e\x91\xb9\xca\x29",20))
printf("strip: b179ce1694c09db3, Pass\n");
else
printf("strip: b179ce1694c09db3, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006018))=0x010a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006018+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006018+4*2))=0x0202003d;
*((unsigned int *)((unsigned long)context_ptr+0x00006018+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x00006580))=0x775dde0a;
*((unsigned int *)((unsigned long)context_ptr+0x00006580+4*1))=0x5b66cd6f;
*((unsigned int *)((unsigned long)context_ptr+0x00006580+4*2))=0x75a862ad;
*((unsigned int *)((unsigned long)context_ptr+0x00006580+4*3))=0xf1406791;
*((unsigned int *)((unsigned long)context_ptr+0x00006580+4*4))=0xa249a296;
*((unsigned int *)((unsigned long)context_ptr+0x00006580+4*5))=0x418a948d;
*((unsigned int *)((unsigned long)context_ptr+0x00006580+4*6))=0x4d4f14a7;
*((unsigned int *)((unsigned long)context_ptr+0x00006580+4*7))=0xda34006f;
*((unsigned int *)((unsigned long)context_ptr+0x00006580+4*8))=0x839b03ca;
*((unsigned int *)((unsigned long)context_ptr+0x00006580+4*9))=0x615cbd18;
*((unsigned int *)((unsigned long)context_ptr+0x00006580+4*10))=0xd7d59b5d;
*((unsigned int *)((unsigned long)context_ptr+0x00006580+4*11))=0x9f0fe550;
*((unsigned int *)((unsigned long)context_ptr+0x00006580+4*12))=0x6a6af4b3;
*((unsigned int *)((unsigned long)context_ptr+0x00006580+4*13))=0x59f757a0;
*((unsigned int *)((unsigned long)context_ptr+0x00006580+4*14))=0xff415625;
*((unsigned int *)((unsigned long)context_ptr+0x00006580+4*15))=0x000000e3;
*((unsigned int *)((unsigned long)context_ptr+0x000035a0))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x000035a0+4*1))=0x000063a0;
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
*((unsigned int *)((unsigned long)context_ptr+0x000005a0+4*1))=0x00006580;
*((unsigned int *)((unsigned long)context_ptr+0x000005a0+4*2))=0x00006018;
*((unsigned int *)((unsigned long)context_ptr+0x000005a0+4*3))=0x0222003d;
*((unsigned int *)((unsigned long)context_ptr+0x000005a0+4*4))=0x0481c3e1;
*((unsigned int *)((unsigned long)context_ptr+0x000005a0+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000011a&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006038,"\x3d\x69\x95\x89\x7b\x81\x8e\x0d\x61\x09\x63\x65\x5d\x95\x14\x74\x91\x88\x63\xa0",20))
printf("strip: 3d6995897b818e0d, Pass\n");
else
printf("strip: 3d6995897b818e0d, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006008))=0x010a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006008+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006008+4*2))=0x0202003e;
*((unsigned int *)((unsigned long)context_ptr+0x00006008+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x00006470))=0x91737f8a;
*((unsigned int *)((unsigned long)context_ptr+0x00006470+4*1))=0xe7f61d4f;
*((unsigned int *)((unsigned long)context_ptr+0x00006470+4*2))=0x77e370b0;
*((unsigned int *)((unsigned long)context_ptr+0x00006470+4*3))=0xc42deca4;
*((unsigned int *)((unsigned long)context_ptr+0x00006470+4*4))=0x548f69ef;
*((unsigned int *)((unsigned long)context_ptr+0x00006470+4*5))=0x643e55ee;
*((unsigned int *)((unsigned long)context_ptr+0x00006470+4*6))=0xb6182818;
*((unsigned int *)((unsigned long)context_ptr+0x00006470+4*7))=0x4cb00955;
*((unsigned int *)((unsigned long)context_ptr+0x00006470+4*8))=0xee95eacf;
*((unsigned int *)((unsigned long)context_ptr+0x00006470+4*9))=0x05b664ec;
*((unsigned int *)((unsigned long)context_ptr+0x00006470+4*10))=0x4c91f7a1;
*((unsigned int *)((unsigned long)context_ptr+0x00006470+4*11))=0x724b618a;
*((unsigned int *)((unsigned long)context_ptr+0x00006470+4*12))=0x043d7939;
*((unsigned int *)((unsigned long)context_ptr+0x00006470+4*13))=0x0a4c6c05;
*((unsigned int *)((unsigned long)context_ptr+0x00006470+4*14))=0xd24e19d1;
*((unsigned int *)((unsigned long)context_ptr+0x00006470+4*15))=0x00006dbc;
*((unsigned int *)((unsigned long)context_ptr+0x000035b8))=0x04c00014;
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
*((unsigned int *)((unsigned long)context_ptr+0x000005b8+4*1))=0x00006470;
*((unsigned int *)((unsigned long)context_ptr+0x000005b8+4*2))=0x00006008;
*((unsigned int *)((unsigned long)context_ptr+0x000005b8+4*3))=0x0222003e;
*((unsigned int *)((unsigned long)context_ptr+0x000005b8+4*4))=0x06bfee0c;
*((unsigned int *)((unsigned long)context_ptr+0x000005b8+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000120&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x0000605c,"\xae\x3c\x84\x12\x59\x16\x88\xd9\x33\x58\xa8\x7d\xac\x07\xe0\x02\x0d\x82\xd9\x87",20))
printf("strip: ae3c8412591688d9, Pass\n");
else
printf("strip: ae3c8412591688d9, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006028))=0x010a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006028+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006028+4*2))=0x0202003f;
*((unsigned int *)((unsigned long)context_ptr+0x00006028+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x00006280))=0xe3d3b3d3;
*((unsigned int *)((unsigned long)context_ptr+0x00006280+4*1))=0x9218aabe;
*((unsigned int *)((unsigned long)context_ptr+0x00006280+4*2))=0x9b156f08;
*((unsigned int *)((unsigned long)context_ptr+0x00006280+4*3))=0x15aabc08;
*((unsigned int *)((unsigned long)context_ptr+0x00006280+4*4))=0xe8bec521;
*((unsigned int *)((unsigned long)context_ptr+0x00006280+4*5))=0x79f43459;
*((unsigned int *)((unsigned long)context_ptr+0x00006280+4*6))=0x39ce1791;
*((unsigned int *)((unsigned long)context_ptr+0x00006280+4*7))=0x9a2876f3;
*((unsigned int *)((unsigned long)context_ptr+0x00006280+4*8))=0x817c1c3f;
*((unsigned int *)((unsigned long)context_ptr+0x00006280+4*9))=0xd337e6b6;
*((unsigned int *)((unsigned long)context_ptr+0x00006280+4*10))=0x62c02074;
*((unsigned int *)((unsigned long)context_ptr+0x00006280+4*11))=0x943f008f;
*((unsigned int *)((unsigned long)context_ptr+0x00006280+4*12))=0x38862107;
*((unsigned int *)((unsigned long)context_ptr+0x00006280+4*13))=0x5f2ae4b4;
*((unsigned int *)((unsigned long)context_ptr+0x00006280+4*14))=0x24b6f012;
*((unsigned int *)((unsigned long)context_ptr+0x00006280+4*15))=0x004c9d3b;
*((unsigned int *)((unsigned long)context_ptr+0x000035d0))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x000035d0+4*1))=0x0000605c;
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
*((unsigned int *)((unsigned long)context_ptr+0x000005d0+4*1))=0x00006280;
*((unsigned int *)((unsigned long)context_ptr+0x000005d0+4*2))=0x00006028;
*((unsigned int *)((unsigned long)context_ptr+0x000005d0+4*3))=0x0222003f;
*((unsigned int *)((unsigned long)context_ptr+0x000005d0+4*4))=0x046a1fae;
*((unsigned int *)((unsigned long)context_ptr+0x000005d0+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000126&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000062d4,"\x9e\x80\xbe\x32\xef\x80\xca\xc2\x72\x25\xaf\x91\x01\xb8\x9f\x0c\x59\xe7\x5e\xe2",20))
printf("strip: 9e80be32ef80cac2, Pass\n");
else
printf("strip: 9e80be32ef80cac2, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x0000604c))=0x010a0012;
*((unsigned int *)((unsigned long)context_ptr+0x0000604c+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x0000604c+4*2))=0x02020040;
*((unsigned int *)((unsigned long)context_ptr+0x0000604c+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x000065c0))=0xd3cd8b79;
*((unsigned int *)((unsigned long)context_ptr+0x000065c0+4*1))=0xc5e51953;
*((unsigned int *)((unsigned long)context_ptr+0x000065c0+4*2))=0x67dd0f05;
*((unsigned int *)((unsigned long)context_ptr+0x000065c0+4*3))=0xfbff9001;
*((unsigned int *)((unsigned long)context_ptr+0x000065c0+4*4))=0xd12fbc3e;
*((unsigned int *)((unsigned long)context_ptr+0x000065c0+4*5))=0xd4afd19d;
*((unsigned int *)((unsigned long)context_ptr+0x000065c0+4*6))=0x1f2f4523;
*((unsigned int *)((unsigned long)context_ptr+0x000065c0+4*7))=0x58731538;
*((unsigned int *)((unsigned long)context_ptr+0x000065c0+4*8))=0x0bb33202;
*((unsigned int *)((unsigned long)context_ptr+0x000065c0+4*9))=0x09eadb04;
*((unsigned int *)((unsigned long)context_ptr+0x000065c0+4*10))=0xa0945b42;
*((unsigned int *)((unsigned long)context_ptr+0x000065c0+4*11))=0x606645f6;
*((unsigned int *)((unsigned long)context_ptr+0x000065c0+4*12))=0xa9e831d6;
*((unsigned int *)((unsigned long)context_ptr+0x000065c0+4*13))=0x0b32b87d;
*((unsigned int *)((unsigned long)context_ptr+0x000065c0+4*14))=0x9fdf5bdd;
*((unsigned int *)((unsigned long)context_ptr+0x000065c0+4*15))=0x624de195;
*((unsigned int *)((unsigned long)context_ptr+0x000035e8))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x000035e8+4*1))=0x000062c0;
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
*((unsigned int *)((unsigned long)context_ptr+0x000005e8+4*1))=0x000065c0;
*((unsigned int *)((unsigned long)context_ptr+0x000005e8+4*2))=0x0000604c;
*((unsigned int *)((unsigned long)context_ptr+0x000005e8+4*3))=0x02220040;
*((unsigned int *)((unsigned long)context_ptr+0x000005e8+4*4))=0x0c9294ff;
*((unsigned int *)((unsigned long)context_ptr+0x000005e8+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000012c&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000062e8,"\xc8\x38\x5f\xc3\x3f\xd6\x8c\x9c\xc3\x28\x64\xe6\x2f\x35\x13\xa3\xf7\x67\xd3\x34",20))
printf("strip: c8385fc33fd68c9c, Pass\n");
else
printf("strip: c8385fc33fd68c9c, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006070))=0x010a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006070+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006070+4*2))=0x02020041;
*((unsigned int *)((unsigned long)context_ptr+0x00006070+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x00006600))=0x3132f146;
*((unsigned int *)((unsigned long)context_ptr+0x00006600+4*1))=0xe7e614cb;
*((unsigned int *)((unsigned long)context_ptr+0x00006600+4*2))=0x127ab2b3;
*((unsigned int *)((unsigned long)context_ptr+0x00006600+4*3))=0x4e96c258;
*((unsigned int *)((unsigned long)context_ptr+0x00006600+4*4))=0xb388352c;
*((unsigned int *)((unsigned long)context_ptr+0x00006600+4*5))=0xa2b4c7f1;
*((unsigned int *)((unsigned long)context_ptr+0x00006600+4*6))=0x66c89cff;
*((unsigned int *)((unsigned long)context_ptr+0x00006600+4*7))=0x82ca5d23;
*((unsigned int *)((unsigned long)context_ptr+0x00006600+4*8))=0xbf5c357e;
*((unsigned int *)((unsigned long)context_ptr+0x00006600+4*9))=0xeef52c6a;
*((unsigned int *)((unsigned long)context_ptr+0x00006600+4*10))=0x12fc7ddc;
*((unsigned int *)((unsigned long)context_ptr+0x00006600+4*11))=0x8f5808a7;
*((unsigned int *)((unsigned long)context_ptr+0x00006600+4*12))=0xe2ef6f7b;
*((unsigned int *)((unsigned long)context_ptr+0x00006600+4*13))=0xa933c7e3;
*((unsigned int *)((unsigned long)context_ptr+0x00006600+4*14))=0x9858e35e;
*((unsigned int *)((unsigned long)context_ptr+0x00006600+4*15))=0x5b1f54d3;
*((unsigned int *)((unsigned long)context_ptr+0x00006600+4*16))=0x00000045;
*((unsigned int *)((unsigned long)context_ptr+0x00003600))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003600+4*1))=0x000062d4;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000600+4*1))=0x00006600;
*((unsigned int *)((unsigned long)context_ptr+0x00000600+4*2))=0x00006070;
*((unsigned int *)((unsigned long)context_ptr+0x00000600+4*3))=0x02220041;
*((unsigned int *)((unsigned long)context_ptr+0x00000600+4*4))=0x0dc07f79;
*((unsigned int *)((unsigned long)context_ptr+0x00000600+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000132&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000063e8,"\x58\xde\x92\x77\xb0\x4d\x68\x1f\x5c\xb7\x98\x85\xb5\xcd\xb1\x4c\xf9\xa3\x42\x6c",20))
printf("strip: 58de9277b04d681f, Pass\n");
else
printf("strip: 58de9277b04d681f, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000062e8))=0x010a0012;
*((unsigned int *)((unsigned long)context_ptr+0x000062e8+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000062e8+4*2))=0x02020042;
*((unsigned int *)((unsigned long)context_ptr+0x000062e8+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x000063b4))=0x46f579a7;
*((unsigned int *)((unsigned long)context_ptr+0x000063b4+4*1))=0x3016f809;
*((unsigned int *)((unsigned long)context_ptr+0x000063b4+4*2))=0xa750d746;
*((unsigned int *)((unsigned long)context_ptr+0x000063b4+4*3))=0x833a8bd8;
*((unsigned int *)((unsigned long)context_ptr+0x000063b4+4*4))=0x662e5d05;
*((unsigned int *)((unsigned long)context_ptr+0x000063b4+4*5))=0xceb0ab0f;
*((unsigned int *)((unsigned long)context_ptr+0x000063b4+4*6))=0xfb251f98;
*((unsigned int *)((unsigned long)context_ptr+0x000063b4+4*7))=0x527ca9b2;
*((unsigned int *)((unsigned long)context_ptr+0x000063b4+4*8))=0x583ff0d9;
*((unsigned int *)((unsigned long)context_ptr+0x000063b4+4*9))=0xbe93fc51;
*((unsigned int *)((unsigned long)context_ptr+0x000063b4+4*10))=0xd0be5355;
*((unsigned int *)((unsigned long)context_ptr+0x000063b4+4*11))=0x4da6e024;
*((unsigned int *)((unsigned long)context_ptr+0x000063b4+4*12))=0x7085f232;
*((unsigned int *)((unsigned long)context_ptr+0x000063b4+4*13))=0xe902a94e;
*((unsigned int *)((unsigned long)context_ptr+0x000063b4+4*14))=0x990f009d;
*((unsigned int *)((unsigned long)context_ptr+0x000063b4+4*15))=0xc9df543d;
*((unsigned int *)((unsigned long)context_ptr+0x000063b4+4*16))=0x0000e083;
*((unsigned int *)((unsigned long)context_ptr+0x00003618))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003618+4*1))=0x000062f8;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000618+4*1))=0x000063b4;
*((unsigned int *)((unsigned long)context_ptr+0x00000618+4*2))=0x000062e8;
*((unsigned int *)((unsigned long)context_ptr+0x00000618+4*3))=0x02220042;
*((unsigned int *)((unsigned long)context_ptr+0x00000618+4*4))=0x0f9ddecf;
*((unsigned int *)((unsigned long)context_ptr+0x00000618+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000138&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000063fc,"\x1e\x85\x17\x22\x8b\x06\x2e\x96\x2a\x94\xe1\xdb\xdd\x5b\x12\x16\xe5\x9f\x7d\x3e",20))
printf("strip: 1e8517228b062e96, Pass\n");
else
printf("strip: 1e8517228b062e96, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x0000630c))=0x010a0012;
*((unsigned int *)((unsigned long)context_ptr+0x0000630c+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x0000630c+4*2))=0x02020043;
*((unsigned int *)((unsigned long)context_ptr+0x0000630c+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x000064b0))=0x910aff20;
*((unsigned int *)((unsigned long)context_ptr+0x000064b0+4*1))=0x762a8093;
*((unsigned int *)((unsigned long)context_ptr+0x000064b0+4*2))=0x4e5e41d9;
*((unsigned int *)((unsigned long)context_ptr+0x000064b0+4*3))=0xf5859c63;
*((unsigned int *)((unsigned long)context_ptr+0x000064b0+4*4))=0x4b044d78;
*((unsigned int *)((unsigned long)context_ptr+0x000064b0+4*5))=0x7b92fed5;
*((unsigned int *)((unsigned long)context_ptr+0x000064b0+4*6))=0xcf595462;
*((unsigned int *)((unsigned long)context_ptr+0x000064b0+4*7))=0xe1249358;
*((unsigned int *)((unsigned long)context_ptr+0x000064b0+4*8))=0x2a40754e;
*((unsigned int *)((unsigned long)context_ptr+0x000064b0+4*9))=0x0aedb4f0;
*((unsigned int *)((unsigned long)context_ptr+0x000064b0+4*10))=0xb7f6998d;
*((unsigned int *)((unsigned long)context_ptr+0x000064b0+4*11))=0x97e544a2;
*((unsigned int *)((unsigned long)context_ptr+0x000064b0+4*12))=0x19dca300;
*((unsigned int *)((unsigned long)context_ptr+0x000064b0+4*13))=0x630a8b31;
*((unsigned int *)((unsigned long)context_ptr+0x000064b0+4*14))=0x19d93e93;
*((unsigned int *)((unsigned long)context_ptr+0x000064b0+4*15))=0xa7d535cd;
*((unsigned int *)((unsigned long)context_ptr+0x000064b0+4*16))=0x00d285be;
*((unsigned int *)((unsigned long)context_ptr+0x00003630))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003630+4*1))=0x000063f8;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000630+4*1))=0x000064b0;
*((unsigned int *)((unsigned long)context_ptr+0x00000630+4*2))=0x0000630c;
*((unsigned int *)((unsigned long)context_ptr+0x00000630+4*3))=0x02220043;
*((unsigned int *)((unsigned long)context_ptr+0x00000630+4*4))=0x004f896c;
*((unsigned int *)((unsigned long)context_ptr+0x00000630+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000013e&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006120,"\xec\x78\x45\x79\x4a\x7f\x29\xf1\x35\x0c\x57\xeb\xaa\x75\x2c\xe9\x91\x26\x2d\x8c",20))
printf("strip: ec7845794a7f29f1, Pass\n");
else
printf("strip: ec7845794a7f29f1, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x0000631c))=0x010a0012;
*((unsigned int *)((unsigned long)context_ptr+0x0000631c+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x0000631c+4*2))=0x02020044;
*((unsigned int *)((unsigned long)context_ptr+0x0000631c+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x00006080))=0x8f34a3cc;
*((unsigned int *)((unsigned long)context_ptr+0x00006080+4*1))=0x271135b7;
*((unsigned int *)((unsigned long)context_ptr+0x00006080+4*2))=0xf4c732c7;
*((unsigned int *)((unsigned long)context_ptr+0x00006080+4*3))=0xbbc8ceb4;
*((unsigned int *)((unsigned long)context_ptr+0x00006080+4*4))=0x667602b1;
*((unsigned int *)((unsigned long)context_ptr+0x00006080+4*5))=0xba70c4c8;
*((unsigned int *)((unsigned long)context_ptr+0x00006080+4*6))=0x7612dc2c;
*((unsigned int *)((unsigned long)context_ptr+0x00006080+4*7))=0x1e62d653;
*((unsigned int *)((unsigned long)context_ptr+0x00006080+4*8))=0xbae92eaf;
*((unsigned int *)((unsigned long)context_ptr+0x00006080+4*9))=0x69f44fbd;
*((unsigned int *)((unsigned long)context_ptr+0x00006080+4*10))=0xefd3a744;
*((unsigned int *)((unsigned long)context_ptr+0x00006080+4*11))=0xed16bd6a;
*((unsigned int *)((unsigned long)context_ptr+0x00006080+4*12))=0x634b8a02;
*((unsigned int *)((unsigned long)context_ptr+0x00006080+4*13))=0x7ace7e71;
*((unsigned int *)((unsigned long)context_ptr+0x00006080+4*14))=0xd25c0681;
*((unsigned int *)((unsigned long)context_ptr+0x00006080+4*15))=0x476ee04e;
*((unsigned int *)((unsigned long)context_ptr+0x00006080+4*16))=0x349c3d20;
*((unsigned int *)((unsigned long)context_ptr+0x00003648))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003648+4*1))=0x000064f4;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000648+4*1))=0x00006080;
*((unsigned int *)((unsigned long)context_ptr+0x00000648+4*2))=0x0000631c;
*((unsigned int *)((unsigned long)context_ptr+0x00000648+4*3))=0x02220044;
*((unsigned int *)((unsigned long)context_ptr+0x00000648+4*4))=0x07eb873b;
*((unsigned int *)((unsigned long)context_ptr+0x00000648+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000144&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006410,"\xee\x99\x5e\xed\x5e\x4f\x79\xbe\xa9\x80\xaf\x48\xb3\x0b\xf2\x50\xdf\xbc\x16\x28",20))
printf("strip: ee995eed5e4f79be, Pass\n");
else
printf("strip: ee995eed5e4f79be, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x0000632c))=0x010a0012;
*((unsigned int *)((unsigned long)context_ptr+0x0000632c+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x0000632c+4*2))=0x02020045;
*((unsigned int *)((unsigned long)context_ptr+0x0000632c+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x000060c4))=0x75e18124;
*((unsigned int *)((unsigned long)context_ptr+0x000060c4+4*1))=0xcc21816b;
*((unsigned int *)((unsigned long)context_ptr+0x000060c4+4*2))=0x11e9127d;
*((unsigned int *)((unsigned long)context_ptr+0x000060c4+4*3))=0x538b0007;
*((unsigned int *)((unsigned long)context_ptr+0x000060c4+4*4))=0x12780b10;
*((unsigned int *)((unsigned long)context_ptr+0x000060c4+4*5))=0x074fbe33;
*((unsigned int *)((unsigned long)context_ptr+0x000060c4+4*6))=0xc2a3eef5;
*((unsigned int *)((unsigned long)context_ptr+0x000060c4+4*7))=0xf9a058ed;
*((unsigned int *)((unsigned long)context_ptr+0x000060c4+4*8))=0xea73dc0f;
*((unsigned int *)((unsigned long)context_ptr+0x000060c4+4*9))=0xee840b60;
*((unsigned int *)((unsigned long)context_ptr+0x000060c4+4*10))=0x8dad3d8d;
*((unsigned int *)((unsigned long)context_ptr+0x000060c4+4*11))=0x02383d8d;
*((unsigned int *)((unsigned long)context_ptr+0x000060c4+4*12))=0x73e6c0f8;
*((unsigned int *)((unsigned long)context_ptr+0x000060c4+4*13))=0xdff9793c;
*((unsigned int *)((unsigned long)context_ptr+0x000060c4+4*14))=0x926eadba;
*((unsigned int *)((unsigned long)context_ptr+0x000060c4+4*15))=0xbb113dc2;
*((unsigned int *)((unsigned long)context_ptr+0x000060c4+4*16))=0xb549a97b;
*((unsigned int *)((unsigned long)context_ptr+0x000060c4+4*17))=0x000000dd;
*((unsigned int *)((unsigned long)context_ptr+0x00003660))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003660+4*1))=0x0000640c;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000660+4*1))=0x000060c4;
*((unsigned int *)((unsigned long)context_ptr+0x00000660+4*2))=0x0000632c;
*((unsigned int *)((unsigned long)context_ptr+0x00000660+4*3))=0x02220045;
*((unsigned int *)((unsigned long)context_ptr+0x00000660+4*4))=0x0d0af524;
*((unsigned int *)((unsigned long)context_ptr+0x00000660+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000014a&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006424,"\x5c\xbf\xba\x73\x04\xba\x0a\x71\x47\xb5\xd9\x19\xe5\xe8\xd1\x58\x69\x20\x75\xc8",20))
printf("strip: 5cbfba7304ba0a71, Pass\n");
else
printf("strip: 5cbfba7304ba0a71, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x0000633c))=0x010a0012;
*((unsigned int *)((unsigned long)context_ptr+0x0000633c+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x0000633c+4*2))=0x02020046;
*((unsigned int *)((unsigned long)context_ptr+0x0000633c+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x0000610c))=0xac058692;
*((unsigned int *)((unsigned long)context_ptr+0x0000610c+4*1))=0xa6893f7f;
*((unsigned int *)((unsigned long)context_ptr+0x0000610c+4*2))=0xea38b59e;
*((unsigned int *)((unsigned long)context_ptr+0x0000610c+4*3))=0x1698467f;
*((unsigned int *)((unsigned long)context_ptr+0x0000610c+4*4))=0x1bd94104;
*((unsigned int *)((unsigned long)context_ptr+0x0000610c+4*5))=0x3a93bf88;
*((unsigned int *)((unsigned long)context_ptr+0x0000610c+4*6))=0x5a1e697d;
*((unsigned int *)((unsigned long)context_ptr+0x0000610c+4*7))=0xd9270cfd;
*((unsigned int *)((unsigned long)context_ptr+0x0000610c+4*8))=0xddd81bda;
*((unsigned int *)((unsigned long)context_ptr+0x0000610c+4*9))=0x067e2c7c;
*((unsigned int *)((unsigned long)context_ptr+0x0000610c+4*10))=0x965431c5;
*((unsigned int *)((unsigned long)context_ptr+0x0000610c+4*11))=0x97623da7;
*((unsigned int *)((unsigned long)context_ptr+0x0000610c+4*12))=0xa685db44;
*((unsigned int *)((unsigned long)context_ptr+0x0000610c+4*13))=0x43d414da;
*((unsigned int *)((unsigned long)context_ptr+0x0000610c+4*14))=0xc06eae35;
*((unsigned int *)((unsigned long)context_ptr+0x0000610c+4*15))=0xbd7aa017;
*((unsigned int *)((unsigned long)context_ptr+0x0000610c+4*16))=0xfea61206;
*((unsigned int *)((unsigned long)context_ptr+0x0000610c+4*17))=0x0000401c;
*((unsigned int *)((unsigned long)context_ptr+0x00003678))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003678+4*1))=0x00006420;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000678+4*1))=0x0000610c;
*((unsigned int *)((unsigned long)context_ptr+0x00000678+4*2))=0x0000633c;
*((unsigned int *)((unsigned long)context_ptr+0x00000678+4*3))=0x02220046;
*((unsigned int *)((unsigned long)context_ptr+0x00000678+4*4))=0x01b40af7;
*((unsigned int *)((unsigned long)context_ptr+0x00000678+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000150&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006438,"\x20\x8d\x80\xe5\xdf\x9a\x2b\x59\xe1\x58\x43\x1d\x79\xb0\x45\x49\x23\x40\xdc\x5b",20))
printf("strip: 208d80e5df9a2b59, Pass\n");
else
printf("strip: 208d80e5df9a2b59, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x0000634c))=0x010a0012;
*((unsigned int *)((unsigned long)context_ptr+0x0000634c+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x0000634c+4*2))=0x02020047;
*((unsigned int *)((unsigned long)context_ptr+0x0000634c+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x00006154))=0x12c83c34;
*((unsigned int *)((unsigned long)context_ptr+0x00006154+4*1))=0xcaa737a8;
*((unsigned int *)((unsigned long)context_ptr+0x00006154+4*2))=0xb489dbe7;
*((unsigned int *)((unsigned long)context_ptr+0x00006154+4*3))=0x6f9caa59;
*((unsigned int *)((unsigned long)context_ptr+0x00006154+4*4))=0xd2ef7b61;
*((unsigned int *)((unsigned long)context_ptr+0x00006154+4*5))=0xfa66cd01;
*((unsigned int *)((unsigned long)context_ptr+0x00006154+4*6))=0x447dd921;
*((unsigned int *)((unsigned long)context_ptr+0x00006154+4*7))=0x6ac98fec;
*((unsigned int *)((unsigned long)context_ptr+0x00006154+4*8))=0x2d6ae053;
*((unsigned int *)((unsigned long)context_ptr+0x00006154+4*9))=0xace9bea7;
*((unsigned int *)((unsigned long)context_ptr+0x00006154+4*10))=0xd1963151;
*((unsigned int *)((unsigned long)context_ptr+0x00006154+4*11))=0x8fdac51b;
*((unsigned int *)((unsigned long)context_ptr+0x00006154+4*12))=0x4cbefca0;
*((unsigned int *)((unsigned long)context_ptr+0x00006154+4*13))=0xeb5c96cc;
*((unsigned int *)((unsigned long)context_ptr+0x00006154+4*14))=0xe9f89756;
*((unsigned int *)((unsigned long)context_ptr+0x00006154+4*15))=0xac3f59f3;
*((unsigned int *)((unsigned long)context_ptr+0x00006154+4*16))=0xd553e233;
*((unsigned int *)((unsigned long)context_ptr+0x00006154+4*17))=0x005ff1ef;
*((unsigned int *)((unsigned long)context_ptr+0x00003690))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003690+4*1))=0x00006434;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000690+4*1))=0x00006154;
*((unsigned int *)((unsigned long)context_ptr+0x00000690+4*2))=0x0000634c;
*((unsigned int *)((unsigned long)context_ptr+0x00000690+4*3))=0x02220047;
*((unsigned int *)((unsigned long)context_ptr+0x00000690+4*4))=0x0062384e;
*((unsigned int *)((unsigned long)context_ptr+0x00000690+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000156&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000061e0,"\xb3\x14\x05\x0a\x75\x64\x93\x03\xe9\x5d\x80\x76\x4c\x95\x91\xdb\x04\x61\xc0\x41",20))
printf("strip: b314050a75649303, Pass\n");
else
printf("strip: b314050a75649303, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006448))=0x010a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006448+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006448+4*2))=0x02020048;
*((unsigned int *)((unsigned long)context_ptr+0x00006448+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x0000619c))=0x611943f3;
*((unsigned int *)((unsigned long)context_ptr+0x0000619c+4*1))=0x0372e1b5;
*((unsigned int *)((unsigned long)context_ptr+0x0000619c+4*2))=0x367f29ca;
*((unsigned int *)((unsigned long)context_ptr+0x0000619c+4*3))=0x7f25c75a;
*((unsigned int *)((unsigned long)context_ptr+0x0000619c+4*4))=0xaf532f7e;
*((unsigned int *)((unsigned long)context_ptr+0x0000619c+4*5))=0x7013d127;
*((unsigned int *)((unsigned long)context_ptr+0x0000619c+4*6))=0x72be6c88;
*((unsigned int *)((unsigned long)context_ptr+0x0000619c+4*7))=0x471bae89;
*((unsigned int *)((unsigned long)context_ptr+0x0000619c+4*8))=0x307fed94;
*((unsigned int *)((unsigned long)context_ptr+0x0000619c+4*9))=0x971f072f;
*((unsigned int *)((unsigned long)context_ptr+0x0000619c+4*10))=0x4c54281d;
*((unsigned int *)((unsigned long)context_ptr+0x0000619c+4*11))=0x578b1ce4;
*((unsigned int *)((unsigned long)context_ptr+0x0000619c+4*12))=0x5625e2a0;
*((unsigned int *)((unsigned long)context_ptr+0x0000619c+4*13))=0x01493fc5;
*((unsigned int *)((unsigned long)context_ptr+0x0000619c+4*14))=0xa39fc740;
*((unsigned int *)((unsigned long)context_ptr+0x0000619c+4*15))=0x06f4b435;
*((unsigned int *)((unsigned long)context_ptr+0x0000619c+4*16))=0xc9826773;
*((unsigned int *)((unsigned long)context_ptr+0x0000619c+4*17))=0xadabf9ba;
*((unsigned int *)((unsigned long)context_ptr+0x000036a8))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x000036a8+4*1))=0x00006508;
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
*((unsigned int *)((unsigned long)context_ptr+0x000006a8+4*1))=0x0000619c;
*((unsigned int *)((unsigned long)context_ptr+0x000006a8+4*2))=0x00006448;
*((unsigned int *)((unsigned long)context_ptr+0x000006a8+4*3))=0x02220048;
*((unsigned int *)((unsigned long)context_ptr+0x000006a8+4*4))=0x06db7d4e;
*((unsigned int *)((unsigned long)context_ptr+0x000006a8+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000015c&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x0000645c,"\x63\xf6\x4f\xa8\x63\x2c\x39\x2a\x54\x29\xeb\xba\x5b\xc1\x6c\x0f\xe6\xf6\x19\x0b",20))
printf("strip: 63f64fa8632c392a, Pass\n");
else
printf("strip: 63f64fa8632c392a, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x0000635c))=0x010a0012;
*((unsigned int *)((unsigned long)context_ptr+0x0000635c+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x0000635c+4*2))=0x02020049;
*((unsigned int *)((unsigned long)context_ptr+0x0000635c+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x000061e4))=0x9e4792d2;
*((unsigned int *)((unsigned long)context_ptr+0x000061e4+4*1))=0x07b14820;
*((unsigned int *)((unsigned long)context_ptr+0x000061e4+4*2))=0xb28cffbd;
*((unsigned int *)((unsigned long)context_ptr+0x000061e4+4*3))=0xee240e5f;
*((unsigned int *)((unsigned long)context_ptr+0x000061e4+4*4))=0x0fcc1974;
*((unsigned int *)((unsigned long)context_ptr+0x000061e4+4*5))=0x2cea613a;
*((unsigned int *)((unsigned long)context_ptr+0x000061e4+4*6))=0xf05d82c3;
*((unsigned int *)((unsigned long)context_ptr+0x000061e4+4*7))=0x7da91207;
*((unsigned int *)((unsigned long)context_ptr+0x000061e4+4*8))=0x198b19bd;
*((unsigned int *)((unsigned long)context_ptr+0x000061e4+4*9))=0x29a65c7b;
*((unsigned int *)((unsigned long)context_ptr+0x000061e4+4*10))=0x7f34e986;
*((unsigned int *)((unsigned long)context_ptr+0x000061e4+4*11))=0x770fe56d;
*((unsigned int *)((unsigned long)context_ptr+0x000061e4+4*12))=0x127cfcfe;
*((unsigned int *)((unsigned long)context_ptr+0x000061e4+4*13))=0xdf1be762;
*((unsigned int *)((unsigned long)context_ptr+0x000061e4+4*14))=0x1f4d4cc3;
*((unsigned int *)((unsigned long)context_ptr+0x000061e4+4*15))=0x61be6cb8;
*((unsigned int *)((unsigned long)context_ptr+0x000061e4+4*16))=0x0413fd23;
*((unsigned int *)((unsigned long)context_ptr+0x000061e4+4*17))=0x25153ab0;
*((unsigned int *)((unsigned long)context_ptr+0x000061e4+4*18))=0x000000ab;
*((unsigned int *)((unsigned long)context_ptr+0x000036c0))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x000036c0+4*1))=0x00006458;
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
*((unsigned int *)((unsigned long)context_ptr+0x000006c0+4*1))=0x000061e4;
*((unsigned int *)((unsigned long)context_ptr+0x000006c0+4*2))=0x0000635c;
*((unsigned int *)((unsigned long)context_ptr+0x000006c0+4*3))=0x02220049;
*((unsigned int *)((unsigned long)context_ptr+0x000006c0+4*4))=0x0483837b;
*((unsigned int *)((unsigned long)context_ptr+0x000006c0+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000162&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x0000637c,"\x5f\xad\x1b\xa8\x12\xc4\x24\x6f\x88\x77\x54\xa4\x54\x20\x0d\xf6\xb8\xcc\x86\xcb",20))
printf("strip: 5fad1ba812c4246f, Pass\n");
else
printf("strip: 5fad1ba812c4246f, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x0000636c))=0x010a0012;
*((unsigned int *)((unsigned long)context_ptr+0x0000636c+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x0000636c+4*2))=0x0202004a;
*((unsigned int *)((unsigned long)context_ptr+0x0000636c+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x0000651c))=0x5ab7ab25;
*((unsigned int *)((unsigned long)context_ptr+0x0000651c+4*1))=0x92105c6d;
*((unsigned int *)((unsigned long)context_ptr+0x0000651c+4*2))=0x7557fe59;
*((unsigned int *)((unsigned long)context_ptr+0x0000651c+4*3))=0xbeb3bdfc;
*((unsigned int *)((unsigned long)context_ptr+0x0000651c+4*4))=0xbb21d69f;
*((unsigned int *)((unsigned long)context_ptr+0x0000651c+4*5))=0xbfdb8e60;
*((unsigned int *)((unsigned long)context_ptr+0x0000651c+4*6))=0x066cf5a7;
*((unsigned int *)((unsigned long)context_ptr+0x0000651c+4*7))=0xd49b68f6;
*((unsigned int *)((unsigned long)context_ptr+0x0000651c+4*8))=0xbb3236c8;
*((unsigned int *)((unsigned long)context_ptr+0x0000651c+4*9))=0xadbba069;
*((unsigned int *)((unsigned long)context_ptr+0x0000651c+4*10))=0xf4a154bc;
*((unsigned int *)((unsigned long)context_ptr+0x0000651c+4*11))=0x475ffa00;
*((unsigned int *)((unsigned long)context_ptr+0x0000651c+4*12))=0xb3383baf;
*((unsigned int *)((unsigned long)context_ptr+0x0000651c+4*13))=0x04e2a696;
*((unsigned int *)((unsigned long)context_ptr+0x0000651c+4*14))=0x67d64a65;
*((unsigned int *)((unsigned long)context_ptr+0x0000651c+4*15))=0x1f959a5c;
*((unsigned int *)((unsigned long)context_ptr+0x0000651c+4*16))=0x55c2efc9;
*((unsigned int *)((unsigned long)context_ptr+0x0000651c+4*17))=0xdf2d1855;
*((unsigned int *)((unsigned long)context_ptr+0x0000651c+4*18))=0x00007230;
*((unsigned int *)((unsigned long)context_ptr+0x000036d8))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x000036d8+4*1))=0x0000637c;
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
*((unsigned int *)((unsigned long)context_ptr+0x000006d8+4*1))=0x0000651c;
*((unsigned int *)((unsigned long)context_ptr+0x000006d8+4*2))=0x0000636c;
*((unsigned int *)((unsigned long)context_ptr+0x000006d8+4*3))=0x0222004a;
*((unsigned int *)((unsigned long)context_ptr+0x000006d8+4*4))=0x02f7acf2;
*((unsigned int *)((unsigned long)context_ptr+0x000006d8+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000168&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x0000626c,"\x86\x67\x3a\x79\x1e\x9c\xf2\x82\xf8\x7b\x89\x63\xf3\x55\x9d\x85\x48\x7f\x95\xb4",20))
printf("strip: 86673a791e9cf282, Pass\n");
else
printf("strip: 86673a791e9cf282, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006390))=0x010a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006390+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006390+4*2))=0x0202004b;
*((unsigned int *)((unsigned long)context_ptr+0x00006390+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x00006230))=0x58a4ec81;
*((unsigned int *)((unsigned long)context_ptr+0x00006230+4*1))=0x472b0be3;
*((unsigned int *)((unsigned long)context_ptr+0x00006230+4*2))=0x953ee0f4;
*((unsigned int *)((unsigned long)context_ptr+0x00006230+4*3))=0xba9fef49;
*((unsigned int *)((unsigned long)context_ptr+0x00006230+4*4))=0x26edceee;
*((unsigned int *)((unsigned long)context_ptr+0x00006230+4*5))=0xc4d8df42;
*((unsigned int *)((unsigned long)context_ptr+0x00006230+4*6))=0x1979dab8;
*((unsigned int *)((unsigned long)context_ptr+0x00006230+4*7))=0x8f9b3fba;
*((unsigned int *)((unsigned long)context_ptr+0x00006230+4*8))=0x1862a763;
*((unsigned int *)((unsigned long)context_ptr+0x00006230+4*9))=0x8f48d8dc;
*((unsigned int *)((unsigned long)context_ptr+0x00006230+4*10))=0x6274bc22;
*((unsigned int *)((unsigned long)context_ptr+0x00006230+4*11))=0xced7d3ee;
*((unsigned int *)((unsigned long)context_ptr+0x00006230+4*12))=0xeb51e7ba;
*((unsigned int *)((unsigned long)context_ptr+0x00006230+4*13))=0x7858c06a;
*((unsigned int *)((unsigned long)context_ptr+0x00006230+4*14))=0x0d521d3f;
*((unsigned int *)((unsigned long)context_ptr+0x00006230+4*15))=0x93135350;
*((unsigned int *)((unsigned long)context_ptr+0x00006230+4*16))=0x3f1a9cd7;
*((unsigned int *)((unsigned long)context_ptr+0x00006230+4*17))=0x6bba4f4b;
*((unsigned int *)((unsigned long)context_ptr+0x00006230+4*18))=0x0039b210;
*((unsigned int *)((unsigned long)context_ptr+0x000036f0))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x000036f0+4*1))=0x00006568;
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
*((unsigned int *)((unsigned long)context_ptr+0x000006f0+4*1))=0x00006230;
*((unsigned int *)((unsigned long)context_ptr+0x000006f0+4*2))=0x00006390;
*((unsigned int *)((unsigned long)context_ptr+0x000006f0+4*3))=0x0222004b;
*((unsigned int *)((unsigned long)context_ptr+0x000006f0+4*4))=0x0d1e16ba;
*((unsigned int *)((unsigned long)context_ptr+0x000006f0+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000016e&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000063a0,"\xb6\x0e\x70\xe8\x76\x33\x3d\x06\xa8\x1a\xae\x1e\x75\x5b\x2a\xe5\x9e\x00\xed\xb5",20))
printf("strip: b60e70e876333d06, Pass\n");
else
printf("strip: b60e70e876333d06, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006018))=0x010a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006018+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006018+4*2))=0x0202004c;
*((unsigned int *)((unsigned long)context_ptr+0x00006018+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x00006644))=0x1767ae80;
*((unsigned int *)((unsigned long)context_ptr+0x00006644+4*1))=0x099e82a7;
*((unsigned int *)((unsigned long)context_ptr+0x00006644+4*2))=0x82e3ed07;
*((unsigned int *)((unsigned long)context_ptr+0x00006644+4*3))=0xc8d51969;
*((unsigned int *)((unsigned long)context_ptr+0x00006644+4*4))=0xd57ecda8;
*((unsigned int *)((unsigned long)context_ptr+0x00006644+4*5))=0x8e8c112c;
*((unsigned int *)((unsigned long)context_ptr+0x00006644+4*6))=0x1e643a94;
*((unsigned int *)((unsigned long)context_ptr+0x00006644+4*7))=0xf7a6d8d0;
*((unsigned int *)((unsigned long)context_ptr+0x00006644+4*8))=0xe5ceefa0;
*((unsigned int *)((unsigned long)context_ptr+0x00006644+4*9))=0xa325185f;
*((unsigned int *)((unsigned long)context_ptr+0x00006644+4*10))=0xadca71ca;
*((unsigned int *)((unsigned long)context_ptr+0x00006644+4*11))=0x44333034;
*((unsigned int *)((unsigned long)context_ptr+0x00006644+4*12))=0x923c8b40;
*((unsigned int *)((unsigned long)context_ptr+0x00006644+4*13))=0xc3a9cc9f;
*((unsigned int *)((unsigned long)context_ptr+0x00006644+4*14))=0xa054077c;
*((unsigned int *)((unsigned long)context_ptr+0x00006644+4*15))=0x082eeb7b;
*((unsigned int *)((unsigned long)context_ptr+0x00006644+4*16))=0x8ad83870;
*((unsigned int *)((unsigned long)context_ptr+0x00006644+4*17))=0x673ba5b7;
*((unsigned int *)((unsigned long)context_ptr+0x00006644+4*18))=0xceee3dd8;
*((unsigned int *)((unsigned long)context_ptr+0x00003708))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003708+4*1))=0x000063a0;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000708+4*1))=0x00006644;
*((unsigned int *)((unsigned long)context_ptr+0x00000708+4*2))=0x00006018;
*((unsigned int *)((unsigned long)context_ptr+0x00000708+4*3))=0x0222004c;
*((unsigned int *)((unsigned long)context_ptr+0x00000708+4*4))=0x082e0282;
*((unsigned int *)((unsigned long)context_ptr+0x00000708+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000174&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006038,"\x74\x60\x85\xfa\xd9\x52\xac\x89\xdb\x45\xec\x0d\x60\xe1\xc5\xfc\x1f\x59\xe8\x73",20))
printf("strip: 746085fad952ac89, Pass\n");
else
printf("strip: 746085fad952ac89, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006008))=0x010a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006008+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006008+4*2))=0x0202004d;
*((unsigned int *)((unsigned long)context_ptr+0x00006008+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x00006690))=0x82bee2f3;
*((unsigned int *)((unsigned long)context_ptr+0x00006690+4*1))=0x168193ad;
*((unsigned int *)((unsigned long)context_ptr+0x00006690+4*2))=0xd3756462;
*((unsigned int *)((unsigned long)context_ptr+0x00006690+4*3))=0x8e341b4c;
*((unsigned int *)((unsigned long)context_ptr+0x00006690+4*4))=0x8420f867;
*((unsigned int *)((unsigned long)context_ptr+0x00006690+4*5))=0xd3e449ce;
*((unsigned int *)((unsigned long)context_ptr+0x00006690+4*6))=0xc86dc26b;
*((unsigned int *)((unsigned long)context_ptr+0x00006690+4*7))=0x49689056;
*((unsigned int *)((unsigned long)context_ptr+0x00006690+4*8))=0x3cb76a74;
*((unsigned int *)((unsigned long)context_ptr+0x00006690+4*9))=0x65c0bff2;
*((unsigned int *)((unsigned long)context_ptr+0x00006690+4*10))=0x79e490e5;
*((unsigned int *)((unsigned long)context_ptr+0x00006690+4*11))=0x393544f6;
*((unsigned int *)((unsigned long)context_ptr+0x00006690+4*12))=0x9d0bc75c;
*((unsigned int *)((unsigned long)context_ptr+0x00006690+4*13))=0x654b7d4f;
*((unsigned int *)((unsigned long)context_ptr+0x00006690+4*14))=0x58bd1f6b;
*((unsigned int *)((unsigned long)context_ptr+0x00006690+4*15))=0xb937d118;
*((unsigned int *)((unsigned long)context_ptr+0x00006690+4*16))=0xf8f20998;
*((unsigned int *)((unsigned long)context_ptr+0x00006690+4*17))=0x31b217bb;
*((unsigned int *)((unsigned long)context_ptr+0x00006690+4*18))=0xd3417e76;
*((unsigned int *)((unsigned long)context_ptr+0x00006690+4*19))=0x0000001f;
*((unsigned int *)((unsigned long)context_ptr+0x00003720))=0x04c00014;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000720+4*1))=0x00006690;
*((unsigned int *)((unsigned long)context_ptr+0x00000720+4*2))=0x00006008;
*((unsigned int *)((unsigned long)context_ptr+0x00000720+4*3))=0x0222004d;
*((unsigned int *)((unsigned long)context_ptr+0x00000720+4*4))=0x0c0f7d98;
*((unsigned int *)((unsigned long)context_ptr+0x00000720+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000017a&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x0000605c,"\xa3\xeb\x6a\x0e\x7f\x33\xeb\xc4\xf0\xed\xf4\xe7\x93\x9e\x18\xe8\x3e\xe6\x27\x02",20))
printf("strip: a3eb6a0e7f33ebc4, Pass\n");
else
printf("strip: a3eb6a0e7f33ebc4, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006028))=0x010a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006028+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006028+4*2))=0x0202004e;
*((unsigned int *)((unsigned long)context_ptr+0x00006028+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x000066e0))=0x49baabda;
*((unsigned int *)((unsigned long)context_ptr+0x000066e0+4*1))=0x1f037f70;
*((unsigned int *)((unsigned long)context_ptr+0x000066e0+4*2))=0x093f0c2c;
*((unsigned int *)((unsigned long)context_ptr+0x000066e0+4*3))=0x49803261;
*((unsigned int *)((unsigned long)context_ptr+0x000066e0+4*4))=0x9dc99b88;
*((unsigned int *)((unsigned long)context_ptr+0x000066e0+4*5))=0xe7e7ae67;
*((unsigned int *)((unsigned long)context_ptr+0x000066e0+4*6))=0x949c1ea6;
*((unsigned int *)((unsigned long)context_ptr+0x000066e0+4*7))=0xcf1990cc;
*((unsigned int *)((unsigned long)context_ptr+0x000066e0+4*8))=0x695a9475;
*((unsigned int *)((unsigned long)context_ptr+0x000066e0+4*9))=0xd288810b;
*((unsigned int *)((unsigned long)context_ptr+0x000066e0+4*10))=0xdcf9315c;
*((unsigned int *)((unsigned long)context_ptr+0x000066e0+4*11))=0x1e26f545;
*((unsigned int *)((unsigned long)context_ptr+0x000066e0+4*12))=0xf70207d0;
*((unsigned int *)((unsigned long)context_ptr+0x000066e0+4*13))=0x9245bc14;
*((unsigned int *)((unsigned long)context_ptr+0x000066e0+4*14))=0x9d1a247a;
*((unsigned int *)((unsigned long)context_ptr+0x000066e0+4*15))=0xcd2f8d36;
*((unsigned int *)((unsigned long)context_ptr+0x000066e0+4*16))=0x254ae392;
*((unsigned int *)((unsigned long)context_ptr+0x000066e0+4*17))=0x36309df5;
*((unsigned int *)((unsigned long)context_ptr+0x000066e0+4*18))=0x4cc4b22c;
*((unsigned int *)((unsigned long)context_ptr+0x000066e0+4*19))=0x00002738;
*((unsigned int *)((unsigned long)context_ptr+0x00003738))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003738+4*1))=0x0000605c;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000738+4*1))=0x000066e0;
*((unsigned int *)((unsigned long)context_ptr+0x00000738+4*2))=0x00006028;
*((unsigned int *)((unsigned long)context_ptr+0x00000738+4*3))=0x0222004e;
*((unsigned int *)((unsigned long)context_ptr+0x00000738+4*4))=0x006bad45;
*((unsigned int *)((unsigned long)context_ptr+0x00000738+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000180&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000062c0,"\x90\x8f\xba\xd9\xaa\x44\x66\x93\x75\xbe\xe7\x2a\xea\xdf\x8d\x87\xc6\xf3\xd4\x48",20))
printf("strip: 908fbad9aa446693, Pass\n");
else
printf("strip: 908fbad9aa446693, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x0000604c))=0x010a0012;
*((unsigned int *)((unsigned long)context_ptr+0x0000604c+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x0000604c+4*2))=0x0202004f;
*((unsigned int *)((unsigned long)context_ptr+0x0000604c+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x0000627c))=0x296607d9;
*((unsigned int *)((unsigned long)context_ptr+0x0000627c+4*1))=0x0ecb86e7;
*((unsigned int *)((unsigned long)context_ptr+0x0000627c+4*2))=0x4a7b2b94;
*((unsigned int *)((unsigned long)context_ptr+0x0000627c+4*3))=0x06951e8c;
*((unsigned int *)((unsigned long)context_ptr+0x0000627c+4*4))=0xc22ef39b;
*((unsigned int *)((unsigned long)context_ptr+0x0000627c+4*5))=0x98d7abca;
*((unsigned int *)((unsigned long)context_ptr+0x0000627c+4*6))=0xb6ea52b7;
*((unsigned int *)((unsigned long)context_ptr+0x0000627c+4*7))=0x9aae57a8;
*((unsigned int *)((unsigned long)context_ptr+0x0000627c+4*8))=0x6fe08e70;
*((unsigned int *)((unsigned long)context_ptr+0x0000627c+4*9))=0xd818a955;
*((unsigned int *)((unsigned long)context_ptr+0x0000627c+4*10))=0xc5deb5e5;
*((unsigned int *)((unsigned long)context_ptr+0x0000627c+4*11))=0xba8ca432;
*((unsigned int *)((unsigned long)context_ptr+0x0000627c+4*12))=0x2c5ac573;
*((unsigned int *)((unsigned long)context_ptr+0x0000627c+4*13))=0xdcc23b09;
*((unsigned int *)((unsigned long)context_ptr+0x0000627c+4*14))=0x74da56b6;
*((unsigned int *)((unsigned long)context_ptr+0x0000627c+4*15))=0x3117c5f6;
*((unsigned int *)((unsigned long)context_ptr+0x0000627c+4*16))=0x64122cf6;
*((unsigned int *)((unsigned long)context_ptr+0x0000627c+4*17))=0xca1580ba;
*((unsigned int *)((unsigned long)context_ptr+0x0000627c+4*18))=0x032995ab;
*((unsigned int *)((unsigned long)context_ptr+0x0000627c+4*19))=0x002f2fd7;
*((unsigned int *)((unsigned long)context_ptr+0x00003750))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003750+4*1))=0x0000646c;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000750+4*1))=0x0000627c;
*((unsigned int *)((unsigned long)context_ptr+0x00000750+4*2))=0x0000604c;
*((unsigned int *)((unsigned long)context_ptr+0x00000750+4*3))=0x0222004f;
*((unsigned int *)((unsigned long)context_ptr+0x00000750+4*4))=0x00a6acd3;
*((unsigned int *)((unsigned long)context_ptr+0x00000750+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000186&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000062d4,"\x9c\x32\x73\x5a\x01\xc5\xfb\x9e\xdf\x17\x57\xfa\xe3\x69\x01\xb6\x00\xf9\x00\x6e",20))
printf("strip: 9c32735a01c5fb9e, Pass\n");
else
printf("strip: 9c32735a01c5fb9e, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006070))=0x010a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006070+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006070+4*2))=0x02020050;
*((unsigned int *)((unsigned long)context_ptr+0x00006070+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x0000657c))=0x5bfe4b77;
*((unsigned int *)((unsigned long)context_ptr+0x0000657c+4*1))=0x15ba3847;
*((unsigned int *)((unsigned long)context_ptr+0x0000657c+4*2))=0x73de623c;
*((unsigned int *)((unsigned long)context_ptr+0x0000657c+4*3))=0x4dd7ca13;
*((unsigned int *)((unsigned long)context_ptr+0x0000657c+4*4))=0xbad7a28c;
*((unsigned int *)((unsigned long)context_ptr+0x0000657c+4*5))=0xbbbb7e9c;
*((unsigned int *)((unsigned long)context_ptr+0x0000657c+4*6))=0x3a2ca6c0;
*((unsigned int *)((unsigned long)context_ptr+0x0000657c+4*7))=0x51c918e5;
*((unsigned int *)((unsigned long)context_ptr+0x0000657c+4*8))=0xd46ef52b;
*((unsigned int *)((unsigned long)context_ptr+0x0000657c+4*9))=0x0ddb6527;
*((unsigned int *)((unsigned long)context_ptr+0x0000657c+4*10))=0x9f2efc86;
*((unsigned int *)((unsigned long)context_ptr+0x0000657c+4*11))=0x54f9a9b0;
*((unsigned int *)((unsigned long)context_ptr+0x0000657c+4*12))=0xe92c3b5a;
*((unsigned int *)((unsigned long)context_ptr+0x0000657c+4*13))=0x3e179bd3;
*((unsigned int *)((unsigned long)context_ptr+0x0000657c+4*14))=0xac4a8633;
*((unsigned int *)((unsigned long)context_ptr+0x0000657c+4*15))=0xbf493569;
*((unsigned int *)((unsigned long)context_ptr+0x0000657c+4*16))=0x053f2f78;
*((unsigned int *)((unsigned long)context_ptr+0x0000657c+4*17))=0x6d898ea1;
*((unsigned int *)((unsigned long)context_ptr+0x0000657c+4*18))=0x0509b846;
*((unsigned int *)((unsigned long)context_ptr+0x0000657c+4*19))=0xf7af7acb;
*((unsigned int *)((unsigned long)context_ptr+0x00003768))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003768+4*1))=0x000062cc;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000768+4*1))=0x0000657c;
*((unsigned int *)((unsigned long)context_ptr+0x00000768+4*2))=0x00006070;
*((unsigned int *)((unsigned long)context_ptr+0x00000768+4*3))=0x02220050;
*((unsigned int *)((unsigned long)context_ptr+0x00000768+4*4))=0x0b65642e;
*((unsigned int *)((unsigned long)context_ptr+0x00000768+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000018c&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000062f8,"\x25\x77\x26\x4e\x01\x77\xda\x28\xd2\xc7\x9a\x83\x75\xf1\xac\xb8\x49\x7c\x51\x3d",20))
printf("strip: 2577264e0177da28, Pass\n");
else
printf("strip: 2577264e0177da28, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000062e0))=0x010a0012;
*((unsigned int *)((unsigned long)context_ptr+0x000062e0+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000062e0+4*2))=0x02020051;
*((unsigned int *)((unsigned long)context_ptr+0x000062e0+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x000065cc))=0x503a2bde;
*((unsigned int *)((unsigned long)context_ptr+0x000065cc+4*1))=0x51c6f961;
*((unsigned int *)((unsigned long)context_ptr+0x000065cc+4*2))=0x075f483f;
*((unsigned int *)((unsigned long)context_ptr+0x000065cc+4*3))=0x563864cf;
*((unsigned int *)((unsigned long)context_ptr+0x000065cc+4*4))=0xea5c5d1e;
*((unsigned int *)((unsigned long)context_ptr+0x000065cc+4*5))=0x7f3e6795;
*((unsigned int *)((unsigned long)context_ptr+0x000065cc+4*6))=0xe157a80a;
*((unsigned int *)((unsigned long)context_ptr+0x000065cc+4*7))=0x195f0fe8;
*((unsigned int *)((unsigned long)context_ptr+0x000065cc+4*8))=0xb5c0d7b8;
*((unsigned int *)((unsigned long)context_ptr+0x000065cc+4*9))=0x5f35c14a;
*((unsigned int *)((unsigned long)context_ptr+0x000065cc+4*10))=0x19cedff8;
*((unsigned int *)((unsigned long)context_ptr+0x000065cc+4*11))=0x25d2aa6c;
*((unsigned int *)((unsigned long)context_ptr+0x000065cc+4*12))=0x04a2f6c9;
*((unsigned int *)((unsigned long)context_ptr+0x000065cc+4*13))=0x231344c5;
*((unsigned int *)((unsigned long)context_ptr+0x000065cc+4*14))=0x61092944;
*((unsigned int *)((unsigned long)context_ptr+0x000065cc+4*15))=0x05c56211;
*((unsigned int *)((unsigned long)context_ptr+0x000065cc+4*16))=0x92de43be;
*((unsigned int *)((unsigned long)context_ptr+0x000065cc+4*17))=0x6e19e892;
*((unsigned int *)((unsigned long)context_ptr+0x000065cc+4*18))=0xd8086135;
*((unsigned int *)((unsigned long)context_ptr+0x000065cc+4*19))=0x9f81bd01;
*((unsigned int *)((unsigned long)context_ptr+0x000065cc+4*20))=0x00000002;
*((unsigned int *)((unsigned long)context_ptr+0x00003780))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003780+4*1))=0x000062f0;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000780+4*1))=0x000065cc;
*((unsigned int *)((unsigned long)context_ptr+0x00000780+4*2))=0x000062e0;
*((unsigned int *)((unsigned long)context_ptr+0x00000780+4*3))=0x02220051;
*((unsigned int *)((unsigned long)context_ptr+0x00000780+4*4))=0x0d73d4df;
*((unsigned int *)((unsigned long)context_ptr+0x00000780+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000192&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000063f8,"\xed\xac\x54\x6e\xb0\xb5\x69\xf8\xe0\x47\x7d\x34\xda\x4a\x18\x4e\xc1\xe6\x33\x37",20))
printf("strip: edac546eb0b569f8, Pass\n");
else
printf("strip: edac546eb0b569f8, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006304))=0x010a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006304+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006304+4*2))=0x02020052;
*((unsigned int *)((unsigned long)context_ptr+0x00006304+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x000063b4))=0x34708277;
*((unsigned int *)((unsigned long)context_ptr+0x000063b4+4*1))=0x84206067;
*((unsigned int *)((unsigned long)context_ptr+0x000063b4+4*2))=0x637d2f61;
*((unsigned int *)((unsigned long)context_ptr+0x000063b4+4*3))=0x7b8a6840;
*((unsigned int *)((unsigned long)context_ptr+0x000063b4+4*4))=0xac81dd2d;
*((unsigned int *)((unsigned long)context_ptr+0x000063b4+4*5))=0x234d6c70;
*((unsigned int *)((unsigned long)context_ptr+0x000063b4+4*6))=0xc207ff89;
*((unsigned int *)((unsigned long)context_ptr+0x000063b4+4*7))=0x3b829784;
*((unsigned int *)((unsigned long)context_ptr+0x000063b4+4*8))=0x978b77b7;
*((unsigned int *)((unsigned long)context_ptr+0x000063b4+4*9))=0xb7c60b91;
*((unsigned int *)((unsigned long)context_ptr+0x000063b4+4*10))=0x6ead3828;
*((unsigned int *)((unsigned long)context_ptr+0x000063b4+4*11))=0xca9c09fe;
*((unsigned int *)((unsigned long)context_ptr+0x000063b4+4*12))=0x513ef34f;
*((unsigned int *)((unsigned long)context_ptr+0x000063b4+4*13))=0xb2a51267;
*((unsigned int *)((unsigned long)context_ptr+0x000063b4+4*14))=0x975316c8;
*((unsigned int *)((unsigned long)context_ptr+0x000063b4+4*15))=0xde77a788;
*((unsigned int *)((unsigned long)context_ptr+0x000063b4+4*16))=0x230cc7ec;
*((unsigned int *)((unsigned long)context_ptr+0x000063b4+4*17))=0x6500e42d;
*((unsigned int *)((unsigned long)context_ptr+0x000063b4+4*18))=0x88d1f0f6;
*((unsigned int *)((unsigned long)context_ptr+0x000063b4+4*19))=0xb09bbb58;
*((unsigned int *)((unsigned long)context_ptr+0x000063b4+4*20))=0x00008090;
*((unsigned int *)((unsigned long)context_ptr+0x00003798))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003798+4*1))=0x00006620;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000798+4*1))=0x000063b4;
*((unsigned int *)((unsigned long)context_ptr+0x00000798+4*2))=0x00006304;
*((unsigned int *)((unsigned long)context_ptr+0x00000798+4*3))=0x02220052;
*((unsigned int *)((unsigned long)context_ptr+0x00000798+4*4))=0x00f82e01;
*((unsigned int *)((unsigned long)context_ptr+0x00000798+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000198&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000064f4,"\x69\xbb\x71\xbf\x23\x46\xa2\x10\xbf\xef\x3b\xf5\xd2\x76\xb6\x15\xf5\x49\xd2\x1c",20))
printf("strip: 69bb71bf2346a210, Pass\n");
else
printf("strip: 69bb71bf2346a210, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006634))=0x010a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006634+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006634+4*2))=0x02020053;
*((unsigned int *)((unsigned long)context_ptr+0x00006634+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x00006480))=0x9eaaf478;
*((unsigned int *)((unsigned long)context_ptr+0x00006480+4*1))=0xdce056c2;
*((unsigned int *)((unsigned long)context_ptr+0x00006480+4*2))=0x0404b4c9;
*((unsigned int *)((unsigned long)context_ptr+0x00006480+4*3))=0x259e3ad5;
*((unsigned int *)((unsigned long)context_ptr+0x00006480+4*4))=0x9b577c2d;
*((unsigned int *)((unsigned long)context_ptr+0x00006480+4*5))=0xb94d795a;
*((unsigned int *)((unsigned long)context_ptr+0x00006480+4*6))=0x37800608;
*((unsigned int *)((unsigned long)context_ptr+0x00006480+4*7))=0x692182a8;
*((unsigned int *)((unsigned long)context_ptr+0x00006480+4*8))=0x27a865d0;
*((unsigned int *)((unsigned long)context_ptr+0x00006480+4*9))=0x9f319930;
*((unsigned int *)((unsigned long)context_ptr+0x00006480+4*10))=0xc20389d8;
*((unsigned int *)((unsigned long)context_ptr+0x00006480+4*11))=0x28496846;
*((unsigned int *)((unsigned long)context_ptr+0x00006480+4*12))=0x5f0abca5;
*((unsigned int *)((unsigned long)context_ptr+0x00006480+4*13))=0x03f9d6bc;
*((unsigned int *)((unsigned long)context_ptr+0x00006480+4*14))=0xf30e081c;
*((unsigned int *)((unsigned long)context_ptr+0x00006480+4*15))=0x9e451539;
*((unsigned int *)((unsigned long)context_ptr+0x00006480+4*16))=0xc4e3e2e9;
*((unsigned int *)((unsigned long)context_ptr+0x00006480+4*17))=0x247a36ca;
*((unsigned int *)((unsigned long)context_ptr+0x00006480+4*18))=0xa4af6f55;
*((unsigned int *)((unsigned long)context_ptr+0x00006480+4*19))=0xb0b75374;
*((unsigned int *)((unsigned long)context_ptr+0x00006480+4*20))=0x00e60382;
*((unsigned int *)((unsigned long)context_ptr+0x000037b0))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x000037b0+4*1))=0x00006314;
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
*((unsigned int *)((unsigned long)context_ptr+0x000007b0+4*1))=0x00006480;
*((unsigned int *)((unsigned long)context_ptr+0x000007b0+4*2))=0x00006634;
*((unsigned int *)((unsigned long)context_ptr+0x000007b0+4*3))=0x02220053;
*((unsigned int *)((unsigned long)context_ptr+0x000007b0+4*4))=0x06266285;
*((unsigned int *)((unsigned long)context_ptr+0x000007b0+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000019e&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x0000640c,"\xdb\xb9\x74\x7e\x1d\xfa\xf1\x3a\x09\xfb\x03\x3f\xa8\x3c\xb8\x3a\x72\x34\xf6\xce",20))
printf("strip: dbb9747e1dfaf13a, Pass\n");
else
printf("strip: dbb9747e1dfaf13a, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006328))=0x010a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006328+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006328+4*2))=0x02020054;
*((unsigned int *)((unsigned long)context_ptr+0x00006328+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x00006080))=0x0ac47dc3;
*((unsigned int *)((unsigned long)context_ptr+0x00006080+4*1))=0x81ea9365;
*((unsigned int *)((unsigned long)context_ptr+0x00006080+4*2))=0x517692ee;
*((unsigned int *)((unsigned long)context_ptr+0x00006080+4*3))=0x5405c5c1;
*((unsigned int *)((unsigned long)context_ptr+0x00006080+4*4))=0x568c3a50;
*((unsigned int *)((unsigned long)context_ptr+0x00006080+4*5))=0x5526c028;
*((unsigned int *)((unsigned long)context_ptr+0x00006080+4*6))=0x6d59c6e4;
*((unsigned int *)((unsigned long)context_ptr+0x00006080+4*7))=0xc5fab35d;
*((unsigned int *)((unsigned long)context_ptr+0x00006080+4*8))=0xf2600a00;
*((unsigned int *)((unsigned long)context_ptr+0x00006080+4*9))=0x83d66294;
*((unsigned int *)((unsigned long)context_ptr+0x00006080+4*10))=0xb03d8cbf;
*((unsigned int *)((unsigned long)context_ptr+0x00006080+4*11))=0x029c1e34;
*((unsigned int *)((unsigned long)context_ptr+0x00006080+4*12))=0x68654376;
*((unsigned int *)((unsigned long)context_ptr+0x00006080+4*13))=0x4387176d;
*((unsigned int *)((unsigned long)context_ptr+0x00006080+4*14))=0x9ed917e9;
*((unsigned int *)((unsigned long)context_ptr+0x00006080+4*15))=0x8f8a8959;
*((unsigned int *)((unsigned long)context_ptr+0x00006080+4*16))=0xbc1190e2;
*((unsigned int *)((unsigned long)context_ptr+0x00006080+4*17))=0x2a7fc815;
*((unsigned int *)((unsigned long)context_ptr+0x00006080+4*18))=0x9fd6ac50;
*((unsigned int *)((unsigned long)context_ptr+0x00006080+4*19))=0x269730c5;
*((unsigned int *)((unsigned long)context_ptr+0x00006080+4*20))=0xaf01faea;
*((unsigned int *)((unsigned long)context_ptr+0x000037c8))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x000037c8+4*1))=0x00006408;
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
*((unsigned int *)((unsigned long)context_ptr+0x000007c8+4*1))=0x00006080;
*((unsigned int *)((unsigned long)context_ptr+0x000007c8+4*2))=0x00006328;
*((unsigned int *)((unsigned long)context_ptr+0x000007c8+4*3))=0x02220054;
*((unsigned int *)((unsigned long)context_ptr+0x000007c8+4*4))=0x0b38d72c;
*((unsigned int *)((unsigned long)context_ptr+0x000007c8+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000001a4&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006420,"\x1e\x3e\x96\x2a\x28\x14\xbb\x91\x19\x0b\xd5\xb7\x7f\x16\x01\xb8\x12\xb8\xff\x92",20))
printf("strip: 1e3e962a2814bb91, Pass\n");
else
printf("strip: 1e3e962a2814bb91, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006338))=0x010a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006338+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006338+4*2))=0x02020055;
*((unsigned int *)((unsigned long)context_ptr+0x00006338+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x000060d4))=0x8f6b3dc5;
*((unsigned int *)((unsigned long)context_ptr+0x000060d4+4*1))=0x6af4e66a;
*((unsigned int *)((unsigned long)context_ptr+0x000060d4+4*2))=0xfa6e9679;
*((unsigned int *)((unsigned long)context_ptr+0x000060d4+4*3))=0x152d9ca1;
*((unsigned int *)((unsigned long)context_ptr+0x000060d4+4*4))=0x4a30440c;
*((unsigned int *)((unsigned long)context_ptr+0x000060d4+4*5))=0xb4ecb397;
*((unsigned int *)((unsigned long)context_ptr+0x000060d4+4*6))=0xd2da4aa1;
*((unsigned int *)((unsigned long)context_ptr+0x000060d4+4*7))=0xcbbbbbc4;
*((unsigned int *)((unsigned long)context_ptr+0x000060d4+4*8))=0xf3494390;
*((unsigned int *)((unsigned long)context_ptr+0x000060d4+4*9))=0x8c09762a;
*((unsigned int *)((unsigned long)context_ptr+0x000060d4+4*10))=0x4d08477c;
*((unsigned int *)((unsigned long)context_ptr+0x000060d4+4*11))=0x1c07c58e;
*((unsigned int *)((unsigned long)context_ptr+0x000060d4+4*12))=0xb6cccd75;
*((unsigned int *)((unsigned long)context_ptr+0x000060d4+4*13))=0x0d9cf14f;
*((unsigned int *)((unsigned long)context_ptr+0x000060d4+4*14))=0xe50b7e46;
*((unsigned int *)((unsigned long)context_ptr+0x000060d4+4*15))=0x4106876c;
*((unsigned int *)((unsigned long)context_ptr+0x000060d4+4*16))=0xae83945d;
*((unsigned int *)((unsigned long)context_ptr+0x000060d4+4*17))=0x9a63852d;
*((unsigned int *)((unsigned long)context_ptr+0x000060d4+4*18))=0x8f5d57ba;
*((unsigned int *)((unsigned long)context_ptr+0x000060d4+4*19))=0xb8bea0d3;
*((unsigned int *)((unsigned long)context_ptr+0x000060d4+4*20))=0x9f26a195;
*((unsigned int *)((unsigned long)context_ptr+0x000060d4+4*21))=0x000000ba;
*((unsigned int *)((unsigned long)context_ptr+0x000037e0))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x000037e0+4*1))=0x0000641c;
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
*((unsigned int *)((unsigned long)context_ptr+0x000007e0+4*1))=0x000060d4;
*((unsigned int *)((unsigned long)context_ptr+0x000007e0+4*2))=0x00006338;
*((unsigned int *)((unsigned long)context_ptr+0x000007e0+4*3))=0x02220055;
*((unsigned int *)((unsigned long)context_ptr+0x000007e0+4*4))=0x0b6aa914;
*((unsigned int *)((unsigned long)context_ptr+0x000007e0+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000001aa&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006434,"\x59\x7c\xb5\xe0\x96\x73\x5b\x18\x66\x71\x8f\x94\xc8\x86\xc3\x9d\x00\x5a\xa2\xe7",20))
printf("strip: 597cb5e096735b18, Pass\n");
else
printf("strip: 597cb5e096735b18, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006348))=0x010a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006348+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006348+4*2))=0x02020056;
*((unsigned int *)((unsigned long)context_ptr+0x00006348+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x0000612c))=0x1a47b85e;
*((unsigned int *)((unsigned long)context_ptr+0x0000612c+4*1))=0xb1944e29;
*((unsigned int *)((unsigned long)context_ptr+0x0000612c+4*2))=0x87ce8d02;
*((unsigned int *)((unsigned long)context_ptr+0x0000612c+4*3))=0xf0edf46c;
*((unsigned int *)((unsigned long)context_ptr+0x0000612c+4*4))=0xed711e9e;
*((unsigned int *)((unsigned long)context_ptr+0x0000612c+4*5))=0x4ddc8cbd;
*((unsigned int *)((unsigned long)context_ptr+0x0000612c+4*6))=0x9bb9b4a3;
*((unsigned int *)((unsigned long)context_ptr+0x0000612c+4*7))=0x42536867;
*((unsigned int *)((unsigned long)context_ptr+0x0000612c+4*8))=0x925bada0;
*((unsigned int *)((unsigned long)context_ptr+0x0000612c+4*9))=0xc0f83357;
*((unsigned int *)((unsigned long)context_ptr+0x0000612c+4*10))=0x5fac01b2;
*((unsigned int *)((unsigned long)context_ptr+0x0000612c+4*11))=0x263fee81;
*((unsigned int *)((unsigned long)context_ptr+0x0000612c+4*12))=0x661688b4;
*((unsigned int *)((unsigned long)context_ptr+0x0000612c+4*13))=0x7fe265e2;
*((unsigned int *)((unsigned long)context_ptr+0x0000612c+4*14))=0x46c4b3dd;
*((unsigned int *)((unsigned long)context_ptr+0x0000612c+4*15))=0xd3e9fbe5;
*((unsigned int *)((unsigned long)context_ptr+0x0000612c+4*16))=0xfabd1cd8;
*((unsigned int *)((unsigned long)context_ptr+0x0000612c+4*17))=0xb75d2d92;
*((unsigned int *)((unsigned long)context_ptr+0x0000612c+4*18))=0x128a2a99;
*((unsigned int *)((unsigned long)context_ptr+0x0000612c+4*19))=0x4ad309c3;
*((unsigned int *)((unsigned long)context_ptr+0x0000612c+4*20))=0x97fee9ff;
*((unsigned int *)((unsigned long)context_ptr+0x0000612c+4*21))=0x0000c28a;
*((unsigned int *)((unsigned long)context_ptr+0x000037f8))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x000037f8+4*1))=0x00006430;
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
*((unsigned int *)((unsigned long)context_ptr+0x000007f8+4*1))=0x0000612c;
*((unsigned int *)((unsigned long)context_ptr+0x000007f8+4*2))=0x00006348;
*((unsigned int *)((unsigned long)context_ptr+0x000007f8+4*3))=0x02220056;
*((unsigned int *)((unsigned long)context_ptr+0x000007f8+4*4))=0x0dc00afd;
*((unsigned int *)((unsigned long)context_ptr+0x000007f8+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000001b0&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006508,"\xe3\x63\x2b\x4f\x71\x24\xd2\x21\x69\x21\x82\x79\x09\x0c\x40\xf0\x5c\xa2\xf6\x86",20))
printf("strip: e3632b4f7124d221, Pass\n");
else
printf("strip: e3632b4f7124d221, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006444))=0x010a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006444+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006444+4*2))=0x02020057;
*((unsigned int *)((unsigned long)context_ptr+0x00006444+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x00006184))=0x2b41e401;
*((unsigned int *)((unsigned long)context_ptr+0x00006184+4*1))=0xf592c5ff;
*((unsigned int *)((unsigned long)context_ptr+0x00006184+4*2))=0xcb2ac6dd;
*((unsigned int *)((unsigned long)context_ptr+0x00006184+4*3))=0xdd44491d;
*((unsigned int *)((unsigned long)context_ptr+0x00006184+4*4))=0x932135b9;
*((unsigned int *)((unsigned long)context_ptr+0x00006184+4*5))=0x43f038af;
*((unsigned int *)((unsigned long)context_ptr+0x00006184+4*6))=0xdb5072d5;
*((unsigned int *)((unsigned long)context_ptr+0x00006184+4*7))=0x4e8c7af8;
*((unsigned int *)((unsigned long)context_ptr+0x00006184+4*8))=0xe9aa409e;
*((unsigned int *)((unsigned long)context_ptr+0x00006184+4*9))=0x0fc9e688;
*((unsigned int *)((unsigned long)context_ptr+0x00006184+4*10))=0x7a76bde0;
*((unsigned int *)((unsigned long)context_ptr+0x00006184+4*11))=0x934a57c7;
*((unsigned int *)((unsigned long)context_ptr+0x00006184+4*12))=0x220c6a04;
*((unsigned int *)((unsigned long)context_ptr+0x00006184+4*13))=0xdd349fc8;
*((unsigned int *)((unsigned long)context_ptr+0x00006184+4*14))=0x597b418b;
*((unsigned int *)((unsigned long)context_ptr+0x00006184+4*15))=0x6aa8ff9e;
*((unsigned int *)((unsigned long)context_ptr+0x00006184+4*16))=0xb2af8c8f;
*((unsigned int *)((unsigned long)context_ptr+0x00006184+4*17))=0x4193788a;
*((unsigned int *)((unsigned long)context_ptr+0x00006184+4*18))=0xa56f1e68;
*((unsigned int *)((unsigned long)context_ptr+0x00006184+4*19))=0x94dc8a75;
*((unsigned int *)((unsigned long)context_ptr+0x00006184+4*20))=0x624dc904;
*((unsigned int *)((unsigned long)context_ptr+0x00006184+4*21))=0x004fd8f7;
*((unsigned int *)((unsigned long)context_ptr+0x00003810))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003810+4*1))=0x000064d4;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000810+4*1))=0x00006184;
*((unsigned int *)((unsigned long)context_ptr+0x00000810+4*2))=0x00006444;
*((unsigned int *)((unsigned long)context_ptr+0x00000810+4*3))=0x02220057;
*((unsigned int *)((unsigned long)context_ptr+0x00000810+4*4))=0x03731b45;
*((unsigned int *)((unsigned long)context_ptr+0x00000810+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000001b6&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006458,"\x14\xa2\x56\xe8\x95\x74\x80\xad\x57\x36\xc0\x13\x10\x3b\xd4\xf4\x6d\xfe\x1d\xdf",20))
printf("strip: 14a256e8957480ad, Pass\n");
else
printf("strip: 14a256e8957480ad, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006358))=0x010a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006358+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006358+4*2))=0x02020058;
*((unsigned int *)((unsigned long)context_ptr+0x00006358+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x00006730))=0x040df304;
*((unsigned int *)((unsigned long)context_ptr+0x00006730+4*1))=0x0c4ba0da;
*((unsigned int *)((unsigned long)context_ptr+0x00006730+4*2))=0xb0ccb939;
*((unsigned int *)((unsigned long)context_ptr+0x00006730+4*3))=0x4ed3cd0e;
*((unsigned int *)((unsigned long)context_ptr+0x00006730+4*4))=0xe45abb3f;
*((unsigned int *)((unsigned long)context_ptr+0x00006730+4*5))=0x90a37a9e;
*((unsigned int *)((unsigned long)context_ptr+0x00006730+4*6))=0x42ef74d6;
*((unsigned int *)((unsigned long)context_ptr+0x00006730+4*7))=0x8459f119;
*((unsigned int *)((unsigned long)context_ptr+0x00006730+4*8))=0x8f9c5f4a;
*((unsigned int *)((unsigned long)context_ptr+0x00006730+4*9))=0x16a09286;
*((unsigned int *)((unsigned long)context_ptr+0x00006730+4*10))=0x6b7f38d6;
*((unsigned int *)((unsigned long)context_ptr+0x00006730+4*11))=0x0b46f634;
*((unsigned int *)((unsigned long)context_ptr+0x00006730+4*12))=0x832a5b1e;
*((unsigned int *)((unsigned long)context_ptr+0x00006730+4*13))=0x08fd53f9;
*((unsigned int *)((unsigned long)context_ptr+0x00006730+4*14))=0xabeebe85;
*((unsigned int *)((unsigned long)context_ptr+0x00006730+4*15))=0xbc771ce4;
*((unsigned int *)((unsigned long)context_ptr+0x00006730+4*16))=0x98dc5389;
*((unsigned int *)((unsigned long)context_ptr+0x00006730+4*17))=0x6bc87508;
*((unsigned int *)((unsigned long)context_ptr+0x00006730+4*18))=0x3d8d7c2a;
*((unsigned int *)((unsigned long)context_ptr+0x00006730+4*19))=0x5ff484a1;
*((unsigned int *)((unsigned long)context_ptr+0x00006730+4*20))=0xb3c9e2da;
*((unsigned int *)((unsigned long)context_ptr+0x00006730+4*21))=0x2389118b;
*((unsigned int *)((unsigned long)context_ptr+0x00003828))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003828+4*1))=0x00006454;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000828+4*1))=0x00006730;
*((unsigned int *)((unsigned long)context_ptr+0x00000828+4*2))=0x00006358;
*((unsigned int *)((unsigned long)context_ptr+0x00000828+4*3))=0x02220058;
*((unsigned int *)((unsigned long)context_ptr+0x00000828+4*4))=0x07ec93bc;
*((unsigned int *)((unsigned long)context_ptr+0x00000828+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000001bc&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x0000637c,"\x84\xbf\xcd\xc6\xaa\x99\x6c\xb1\x64\x38\xc9\x74\x5d\x2a\x2e\x7a\x75\xea\xe8\x6e",20))
printf("strip: 84bfcdc6aa996cb1, Pass\n");
else
printf("strip: 84bfcdc6aa996cb1, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006368))=0x010a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006368+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006368+4*2))=0x02020059;
*((unsigned int *)((unsigned long)context_ptr+0x00006368+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x000064e8))=0x2db8de7f;
*((unsigned int *)((unsigned long)context_ptr+0x000064e8+4*1))=0xe4e34b33;
*((unsigned int *)((unsigned long)context_ptr+0x000064e8+4*2))=0x1006fdc9;
*((unsigned int *)((unsigned long)context_ptr+0x000064e8+4*3))=0x17d8655d;
*((unsigned int *)((unsigned long)context_ptr+0x000064e8+4*4))=0x5ff6335f;
*((unsigned int *)((unsigned long)context_ptr+0x000064e8+4*5))=0x5f127e39;
*((unsigned int *)((unsigned long)context_ptr+0x000064e8+4*6))=0x2684705d;
*((unsigned int *)((unsigned long)context_ptr+0x000064e8+4*7))=0x4f62ad19;
*((unsigned int *)((unsigned long)context_ptr+0x000064e8+4*8))=0x453a815a;
*((unsigned int *)((unsigned long)context_ptr+0x000064e8+4*9))=0x5bcf5df6;
*((unsigned int *)((unsigned long)context_ptr+0x000064e8+4*10))=0xfd331220;
*((unsigned int *)((unsigned long)context_ptr+0x000064e8+4*11))=0x9adafd6b;
*((unsigned int *)((unsigned long)context_ptr+0x000064e8+4*12))=0x3ec62a2c;
*((unsigned int *)((unsigned long)context_ptr+0x000064e8+4*13))=0x388e6779;
*((unsigned int *)((unsigned long)context_ptr+0x000064e8+4*14))=0x3fbbf3bb;
*((unsigned int *)((unsigned long)context_ptr+0x000064e8+4*15))=0x625527d8;
*((unsigned int *)((unsigned long)context_ptr+0x000064e8+4*16))=0x2850598d;
*((unsigned int *)((unsigned long)context_ptr+0x000064e8+4*17))=0xf9bfb063;
*((unsigned int *)((unsigned long)context_ptr+0x000064e8+4*18))=0xc50c98a1;
*((unsigned int *)((unsigned long)context_ptr+0x000064e8+4*19))=0x02fd3c72;
*((unsigned int *)((unsigned long)context_ptr+0x000064e8+4*20))=0x3d3aed79;
*((unsigned int *)((unsigned long)context_ptr+0x000064e8+4*21))=0xa9a9b221;
*((unsigned int *)((unsigned long)context_ptr+0x000064e8+4*22))=0x000000b5;
*((unsigned int *)((unsigned long)context_ptr+0x00003840))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003840+4*1))=0x00006378;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000840+4*1))=0x000064e8;
*((unsigned int *)((unsigned long)context_ptr+0x00000840+4*2))=0x00006368;
*((unsigned int *)((unsigned long)context_ptr+0x00000840+4*3))=0x02220059;
*((unsigned int *)((unsigned long)context_ptr+0x00000840+4*4))=0x0ecf5b4d;
*((unsigned int *)((unsigned long)context_ptr+0x00000840+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000001c2&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006568,"\xc0\xaa\x5e\x68\x03\x13\xb7\x31\x63\xba\x22\x35\x2d\xeb\xae\x39\xa4\x4f\x79\x02",20))
printf("strip: c0aa5e680313b731, Pass\n");
else
printf("strip: c0aa5e680313b731, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x0000638c))=0x010a0012;
*((unsigned int *)((unsigned long)context_ptr+0x0000638c+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x0000638c+4*2))=0x0202005a;
*((unsigned int *)((unsigned long)context_ptr+0x0000638c+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x000061dc))=0x5942ec17;
*((unsigned int *)((unsigned long)context_ptr+0x000061dc+4*1))=0x2595dc28;
*((unsigned int *)((unsigned long)context_ptr+0x000061dc+4*2))=0xaba3c6d3;
*((unsigned int *)((unsigned long)context_ptr+0x000061dc+4*3))=0xdbb42769;
*((unsigned int *)((unsigned long)context_ptr+0x000061dc+4*4))=0xd69e1955;
*((unsigned int *)((unsigned long)context_ptr+0x000061dc+4*5))=0x0ec627fb;
*((unsigned int *)((unsigned long)context_ptr+0x000061dc+4*6))=0x0f1f0184;
*((unsigned int *)((unsigned long)context_ptr+0x000061dc+4*7))=0x2c99ffca;
*((unsigned int *)((unsigned long)context_ptr+0x000061dc+4*8))=0x8158304b;
*((unsigned int *)((unsigned long)context_ptr+0x000061dc+4*9))=0x1656589f;
*((unsigned int *)((unsigned long)context_ptr+0x000061dc+4*10))=0xe0dc4b05;
*((unsigned int *)((unsigned long)context_ptr+0x000061dc+4*11))=0x724380f0;
*((unsigned int *)((unsigned long)context_ptr+0x000061dc+4*12))=0x234a761b;
*((unsigned int *)((unsigned long)context_ptr+0x000061dc+4*13))=0x56d51556;
*((unsigned int *)((unsigned long)context_ptr+0x000061dc+4*14))=0x0b912aff;
*((unsigned int *)((unsigned long)context_ptr+0x000061dc+4*15))=0xfe356bd2;
*((unsigned int *)((unsigned long)context_ptr+0x000061dc+4*16))=0x7635d342;
*((unsigned int *)((unsigned long)context_ptr+0x000061dc+4*17))=0x0c6a50c1;
*((unsigned int *)((unsigned long)context_ptr+0x000061dc+4*18))=0xa73f783a;
*((unsigned int *)((unsigned long)context_ptr+0x000061dc+4*19))=0x42f9c354;
*((unsigned int *)((unsigned long)context_ptr+0x000061dc+4*20))=0x604dd3f5;
*((unsigned int *)((unsigned long)context_ptr+0x000061dc+4*21))=0xc3c71d4f;
*((unsigned int *)((unsigned long)context_ptr+0x000061dc+4*22))=0x00006cff;
*((unsigned int *)((unsigned long)context_ptr+0x00003858))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003858+4*1))=0x00006544;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000858+4*1))=0x000061dc;
*((unsigned int *)((unsigned long)context_ptr+0x00000858+4*2))=0x0000638c;
*((unsigned int *)((unsigned long)context_ptr+0x00000858+4*3))=0x0222005a;
*((unsigned int *)((unsigned long)context_ptr+0x00000858+4*4))=0x0a904a5d;
*((unsigned int *)((unsigned long)context_ptr+0x00000858+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000001c8&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000063a0,"\x3e\xef\x6f\x70\xaa\x30\x5c\xb8\x0d\x22\x21\x9c\xe6\xeb\xb1\x43\x3e\x86\xcc\x01",20))
printf("strip: 3eef6f70aa305cb8, Pass\n");
else
printf("strip: 3eef6f70aa305cb8, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006018))=0x010a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006018+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006018+4*2))=0x0202005b;
*((unsigned int *)((unsigned long)context_ptr+0x00006018+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x00006788))=0x2afa32bd;
*((unsigned int *)((unsigned long)context_ptr+0x00006788+4*1))=0x2661e004;
*((unsigned int *)((unsigned long)context_ptr+0x00006788+4*2))=0x30668837;
*((unsigned int *)((unsigned long)context_ptr+0x00006788+4*3))=0xb4b5fe1b;
*((unsigned int *)((unsigned long)context_ptr+0x00006788+4*4))=0x9898691e;
*((unsigned int *)((unsigned long)context_ptr+0x00006788+4*5))=0x3b98e523;
*((unsigned int *)((unsigned long)context_ptr+0x00006788+4*6))=0x73fd8c78;
*((unsigned int *)((unsigned long)context_ptr+0x00006788+4*7))=0xc65f4823;
*((unsigned int *)((unsigned long)context_ptr+0x00006788+4*8))=0x672c78a4;
*((unsigned int *)((unsigned long)context_ptr+0x00006788+4*9))=0xd29a8ab2;
*((unsigned int *)((unsigned long)context_ptr+0x00006788+4*10))=0x898ee91a;
*((unsigned int *)((unsigned long)context_ptr+0x00006788+4*11))=0xf2e09f68;
*((unsigned int *)((unsigned long)context_ptr+0x00006788+4*12))=0x9c5f357e;
*((unsigned int *)((unsigned long)context_ptr+0x00006788+4*13))=0x0891f3ef;
*((unsigned int *)((unsigned long)context_ptr+0x00006788+4*14))=0xb372fed9;
*((unsigned int *)((unsigned long)context_ptr+0x00006788+4*15))=0x6bcaa098;
*((unsigned int *)((unsigned long)context_ptr+0x00006788+4*16))=0xb42a4b44;
*((unsigned int *)((unsigned long)context_ptr+0x00006788+4*17))=0x9a7d45c4;
*((unsigned int *)((unsigned long)context_ptr+0x00006788+4*18))=0x3e127f91;
*((unsigned int *)((unsigned long)context_ptr+0x00006788+4*19))=0x17587bb6;
*((unsigned int *)((unsigned long)context_ptr+0x00006788+4*20))=0x88237b9c;
*((unsigned int *)((unsigned long)context_ptr+0x00006788+4*21))=0xa3567e90;
*((unsigned int *)((unsigned long)context_ptr+0x00006788+4*22))=0x00257436;
*((unsigned int *)((unsigned long)context_ptr+0x00003870))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003870+4*1))=0x0000639c;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000870+4*1))=0x00006788;
*((unsigned int *)((unsigned long)context_ptr+0x00000870+4*2))=0x00006018;
*((unsigned int *)((unsigned long)context_ptr+0x00000870+4*3))=0x0222005b;
*((unsigned int *)((unsigned long)context_ptr+0x00000870+4*4))=0x002b44ec;
*((unsigned int *)((unsigned long)context_ptr+0x00000870+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000001ce&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006038,"\x9e\xef\xac\xad\x23\xbd\x3e\x9e\x47\x8f\xc5\xc0\x45\xdf\xd9\xa6\xac\x11\x6a\x15",20))
printf("strip: 9eefacad23bd3e9e, Pass\n");
else
printf("strip: 9eefacad23bd3e9e, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006008))=0x010a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006008+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006008+4*2))=0x0202005c;
*((unsigned int *)((unsigned long)context_ptr+0x00006008+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x00006644))=0xb8ea6a0c;
*((unsigned int *)((unsigned long)context_ptr+0x00006644+4*1))=0x9fe82090;
*((unsigned int *)((unsigned long)context_ptr+0x00006644+4*2))=0x13ebc9bc;
*((unsigned int *)((unsigned long)context_ptr+0x00006644+4*3))=0xf39d0c3c;
*((unsigned int *)((unsigned long)context_ptr+0x00006644+4*4))=0x1fa77c50;
*((unsigned int *)((unsigned long)context_ptr+0x00006644+4*5))=0x888e8ff9;
*((unsigned int *)((unsigned long)context_ptr+0x00006644+4*6))=0xbd064507;
*((unsigned int *)((unsigned long)context_ptr+0x00006644+4*7))=0x0e20e75b;
*((unsigned int *)((unsigned long)context_ptr+0x00006644+4*8))=0x948f2d09;
*((unsigned int *)((unsigned long)context_ptr+0x00006644+4*9))=0x812f74b4;
*((unsigned int *)((unsigned long)context_ptr+0x00006644+4*10))=0xe1359134;
*((unsigned int *)((unsigned long)context_ptr+0x00006644+4*11))=0xea34c471;
*((unsigned int *)((unsigned long)context_ptr+0x00006644+4*12))=0xcbedac01;
*((unsigned int *)((unsigned long)context_ptr+0x00006644+4*13))=0x05f206a0;
*((unsigned int *)((unsigned long)context_ptr+0x00006644+4*14))=0x4ab520b3;
*((unsigned int *)((unsigned long)context_ptr+0x00006644+4*15))=0x560ede5d;
*((unsigned int *)((unsigned long)context_ptr+0x00006644+4*16))=0x3cfa9176;
*((unsigned int *)((unsigned long)context_ptr+0x00006644+4*17))=0x244554b9;
*((unsigned int *)((unsigned long)context_ptr+0x00006644+4*18))=0xbb0c0419;
*((unsigned int *)((unsigned long)context_ptr+0x00006644+4*19))=0x9a2034f0;
*((unsigned int *)((unsigned long)context_ptr+0x00006644+4*20))=0xef1d18c0;
*((unsigned int *)((unsigned long)context_ptr+0x00006644+4*21))=0x4046235b;
*((unsigned int *)((unsigned long)context_ptr+0x00006644+4*22))=0xfe61daa1;
*((unsigned int *)((unsigned long)context_ptr+0x00003888))=0x04c00014;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000888+4*1))=0x00006644;
*((unsigned int *)((unsigned long)context_ptr+0x00000888+4*2))=0x00006008;
*((unsigned int *)((unsigned long)context_ptr+0x00000888+4*3))=0x0222005c;
*((unsigned int *)((unsigned long)context_ptr+0x00000888+4*4))=0x02cada9f;
*((unsigned int *)((unsigned long)context_ptr+0x00000888+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000001d4&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x0000605c,"\x47\x2b\xa7\x1b\x7e\x65\x4f\xd2\x0b\xa4\x98\x9b\xa5\x8e\xa2\x16\x9e\x50\x94\xad",20))
printf("strip: 472ba71b7e654fd2, Pass\n");
else
printf("strip: 472ba71b7e654fd2, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006028))=0x010a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006028+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006028+4*2))=0x0202005d;
*((unsigned int *)((unsigned long)context_ptr+0x00006028+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x000066a0))=0x5453530a;
*((unsigned int *)((unsigned long)context_ptr+0x000066a0+4*1))=0x292c1466;
*((unsigned int *)((unsigned long)context_ptr+0x000066a0+4*2))=0x5009ad8d;
*((unsigned int *)((unsigned long)context_ptr+0x000066a0+4*3))=0x8bb7bbf3;
*((unsigned int *)((unsigned long)context_ptr+0x000066a0+4*4))=0x8c20a402;
*((unsigned int *)((unsigned long)context_ptr+0x000066a0+4*5))=0x49a97d18;
*((unsigned int *)((unsigned long)context_ptr+0x000066a0+4*6))=0x0661f3bf;
*((unsigned int *)((unsigned long)context_ptr+0x000066a0+4*7))=0x87463c9a;
*((unsigned int *)((unsigned long)context_ptr+0x000066a0+4*8))=0x1d49de41;
*((unsigned int *)((unsigned long)context_ptr+0x000066a0+4*9))=0xb0be1ea5;
*((unsigned int *)((unsigned long)context_ptr+0x000066a0+4*10))=0xe551462a;
*((unsigned int *)((unsigned long)context_ptr+0x000066a0+4*11))=0xf93ec3f8;
*((unsigned int *)((unsigned long)context_ptr+0x000066a0+4*12))=0x0a7a3147;
*((unsigned int *)((unsigned long)context_ptr+0x000066a0+4*13))=0x1cb830e5;
*((unsigned int *)((unsigned long)context_ptr+0x000066a0+4*14))=0xc38ffe4a;
*((unsigned int *)((unsigned long)context_ptr+0x000066a0+4*15))=0x9b7e1850;
*((unsigned int *)((unsigned long)context_ptr+0x000066a0+4*16))=0xbed73d54;
*((unsigned int *)((unsigned long)context_ptr+0x000066a0+4*17))=0xc37b7c3c;
*((unsigned int *)((unsigned long)context_ptr+0x000066a0+4*18))=0x3da19785;
*((unsigned int *)((unsigned long)context_ptr+0x000066a0+4*19))=0xcf55ae0e;
*((unsigned int *)((unsigned long)context_ptr+0x000066a0+4*20))=0x0ddbb0ef;
*((unsigned int *)((unsigned long)context_ptr+0x000066a0+4*21))=0x54c5c7d7;
*((unsigned int *)((unsigned long)context_ptr+0x000066a0+4*22))=0xe7887e04;
*((unsigned int *)((unsigned long)context_ptr+0x000066a0+4*23))=0x0000006c;
*((unsigned int *)((unsigned long)context_ptr+0x000038a0))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x000038a0+4*1))=0x0000605c;
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
*((unsigned int *)((unsigned long)context_ptr+0x000008a0+4*1))=0x000066a0;
*((unsigned int *)((unsigned long)context_ptr+0x000008a0+4*2))=0x00006028;
*((unsigned int *)((unsigned long)context_ptr+0x000008a0+4*3))=0x0222005d;
*((unsigned int *)((unsigned long)context_ptr+0x000008a0+4*4))=0x0dd8b768;
*((unsigned int *)((unsigned long)context_ptr+0x000008a0+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000001da&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x0000646c,"\x7c\x68\xed\xa8\xd3\xc9\x4a\xe5\x67\x11\x53\x42\x05\x03\x89\xe3\xd0\xce\xd0\x5c",20))
printf("strip: 7c68eda8d3c94ae5, Pass\n");
else
printf("strip: 7c68eda8d3c94ae5, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x0000604c))=0x010a0012;
*((unsigned int *)((unsigned long)context_ptr+0x0000604c+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x0000604c+4*2))=0x0202005e;
*((unsigned int *)((unsigned long)context_ptr+0x0000604c+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x00006238))=0x01079903;
*((unsigned int *)((unsigned long)context_ptr+0x00006238+4*1))=0xd63dc48b;
*((unsigned int *)((unsigned long)context_ptr+0x00006238+4*2))=0x5e2a0717;
*((unsigned int *)((unsigned long)context_ptr+0x00006238+4*3))=0x6cac4983;
*((unsigned int *)((unsigned long)context_ptr+0x00006238+4*4))=0x5116ca02;
*((unsigned int *)((unsigned long)context_ptr+0x00006238+4*5))=0xcdd1c327;
*((unsigned int *)((unsigned long)context_ptr+0x00006238+4*6))=0xb0eb1ff7;
*((unsigned int *)((unsigned long)context_ptr+0x00006238+4*7))=0x1a1cfa1e;
*((unsigned int *)((unsigned long)context_ptr+0x00006238+4*8))=0xee1c3dab;
*((unsigned int *)((unsigned long)context_ptr+0x00006238+4*9))=0x9e4f30e2;
*((unsigned int *)((unsigned long)context_ptr+0x00006238+4*10))=0x9d93de90;
*((unsigned int *)((unsigned long)context_ptr+0x00006238+4*11))=0x54042fed;
*((unsigned int *)((unsigned long)context_ptr+0x00006238+4*12))=0x1076aaed;
*((unsigned int *)((unsigned long)context_ptr+0x00006238+4*13))=0x36310874;
*((unsigned int *)((unsigned long)context_ptr+0x00006238+4*14))=0xb51dc77a;
*((unsigned int *)((unsigned long)context_ptr+0x00006238+4*15))=0xf103af82;
*((unsigned int *)((unsigned long)context_ptr+0x00006238+4*16))=0xae246517;
*((unsigned int *)((unsigned long)context_ptr+0x00006238+4*17))=0xd11e3e4a;
*((unsigned int *)((unsigned long)context_ptr+0x00006238+4*18))=0x64cc4234;
*((unsigned int *)((unsigned long)context_ptr+0x00006238+4*19))=0x88dfc8b1;
*((unsigned int *)((unsigned long)context_ptr+0x00006238+4*20))=0x8e96d139;
*((unsigned int *)((unsigned long)context_ptr+0x00006238+4*21))=0x5b999f27;
*((unsigned int *)((unsigned long)context_ptr+0x00006238+4*22))=0xae3b73bd;
*((unsigned int *)((unsigned long)context_ptr+0x00006238+4*23))=0x0000d2e8;
*((unsigned int *)((unsigned long)context_ptr+0x000038b8))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x000038b8+4*1))=0x00006468;
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
*((unsigned int *)((unsigned long)context_ptr+0x000008b8+4*1))=0x00006238;
*((unsigned int *)((unsigned long)context_ptr+0x000008b8+4*2))=0x0000604c;
*((unsigned int *)((unsigned long)context_ptr+0x000008b8+4*3))=0x0222005e;
*((unsigned int *)((unsigned long)context_ptr+0x000008b8+4*4))=0x0cc59a23;
*((unsigned int *)((unsigned long)context_ptr+0x000008b8+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000001e0&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000062cc,"\x56\xd4\x49\x1b\xac\xe3\x0e\x25\x35\x1b\x66\x20\xe2\x7c\xdf\xfb\xfa\x82\x67\x5a",20))
printf("strip: 56d4491bace30e25, Pass\n");
else
printf("strip: 56d4491bace30e25, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006070))=0x010a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006070+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006070+4*2))=0x0202005f;
*((unsigned int *)((unsigned long)context_ptr+0x00006070+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x00006558))=0x8cb1ffdc;
*((unsigned int *)((unsigned long)context_ptr+0x00006558+4*1))=0x5c34ca1c;
*((unsigned int *)((unsigned long)context_ptr+0x00006558+4*2))=0x9e41662f;
*((unsigned int *)((unsigned long)context_ptr+0x00006558+4*3))=0xacf1dc26;
*((unsigned int *)((unsigned long)context_ptr+0x00006558+4*4))=0xe1995242;
*((unsigned int *)((unsigned long)context_ptr+0x00006558+4*5))=0xcadb9db7;
*((unsigned int *)((unsigned long)context_ptr+0x00006558+4*6))=0xd87f30b3;
*((unsigned int *)((unsigned long)context_ptr+0x00006558+4*7))=0xb3161064;
*((unsigned int *)((unsigned long)context_ptr+0x00006558+4*8))=0xd43c3cb9;
*((unsigned int *)((unsigned long)context_ptr+0x00006558+4*9))=0x307630cb;
*((unsigned int *)((unsigned long)context_ptr+0x00006558+4*10))=0xf703d93a;
*((unsigned int *)((unsigned long)context_ptr+0x00006558+4*11))=0x5c6e8f29;
*((unsigned int *)((unsigned long)context_ptr+0x00006558+4*12))=0xd068aaf3;
*((unsigned int *)((unsigned long)context_ptr+0x00006558+4*13))=0x6cdb5552;
*((unsigned int *)((unsigned long)context_ptr+0x00006558+4*14))=0xdc576e5b;
*((unsigned int *)((unsigned long)context_ptr+0x00006558+4*15))=0x8a9d8a81;
*((unsigned int *)((unsigned long)context_ptr+0x00006558+4*16))=0x131f156b;
*((unsigned int *)((unsigned long)context_ptr+0x00006558+4*17))=0xf5237446;
*((unsigned int *)((unsigned long)context_ptr+0x00006558+4*18))=0x8c4e7a91;
*((unsigned int *)((unsigned long)context_ptr+0x00006558+4*19))=0xfda918b9;
*((unsigned int *)((unsigned long)context_ptr+0x00006558+4*20))=0xa2523e31;
*((unsigned int *)((unsigned long)context_ptr+0x00006558+4*21))=0x91e7faa8;
*((unsigned int *)((unsigned long)context_ptr+0x00006558+4*22))=0x8ba487ce;
*((unsigned int *)((unsigned long)context_ptr+0x00006558+4*23))=0x00d32178;
*((unsigned int *)((unsigned long)context_ptr+0x000038d0))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x000038d0+4*1))=0x000065b8;
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
*((unsigned int *)((unsigned long)context_ptr+0x000008d0+4*1))=0x00006558;
*((unsigned int *)((unsigned long)context_ptr+0x000008d0+4*2))=0x00006070;
*((unsigned int *)((unsigned long)context_ptr+0x000008d0+4*3))=0x0222005f;
*((unsigned int *)((unsigned long)context_ptr+0x000008d0+4*4))=0x01a839f4;
*((unsigned int *)((unsigned long)context_ptr+0x000008d0+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000001e6&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000062f0,"\xdd\xf3\x52\x98\x3d\x0b\x03\x60\x6d\x6f\xff\x31\x6c\x03\x92\x58\x81\x0e\x24\xc9",20))
printf("strip: ddf352983d0b0360, Pass\n");
else
printf("strip: ddf352983d0b0360, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006700))=0x010a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006700+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006700+4*2))=0x02020060;
*((unsigned int *)((unsigned long)context_ptr+0x00006700+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x00006298))=0xee9f9768;
*((unsigned int *)((unsigned long)context_ptr+0x00006298+4*1))=0xf182ba38;
*((unsigned int *)((unsigned long)context_ptr+0x00006298+4*2))=0xf5531712;
*((unsigned int *)((unsigned long)context_ptr+0x00006298+4*3))=0x55442258;
*((unsigned int *)((unsigned long)context_ptr+0x00006298+4*4))=0x50142252;
*((unsigned int *)((unsigned long)context_ptr+0x00006298+4*5))=0x7c86ab4f;
*((unsigned int *)((unsigned long)context_ptr+0x00006298+4*6))=0xd0de945c;
*((unsigned int *)((unsigned long)context_ptr+0x00006298+4*7))=0xb3f5f966;
*((unsigned int *)((unsigned long)context_ptr+0x00006298+4*8))=0x4bb2e51a;
*((unsigned int *)((unsigned long)context_ptr+0x00006298+4*9))=0x5cc704c5;
*((unsigned int *)((unsigned long)context_ptr+0x00006298+4*10))=0x82e78e54;
*((unsigned int *)((unsigned long)context_ptr+0x00006298+4*11))=0xc95e7539;
*((unsigned int *)((unsigned long)context_ptr+0x00006298+4*12))=0x8fee1d06;
*((unsigned int *)((unsigned long)context_ptr+0x00006298+4*13))=0xe917a0fe;
*((unsigned int *)((unsigned long)context_ptr+0x00006298+4*14))=0xde65ba3a;
*((unsigned int *)((unsigned long)context_ptr+0x00006298+4*15))=0xc1cf93d5;
*((unsigned int *)((unsigned long)context_ptr+0x00006298+4*16))=0xdcb5fca5;
*((unsigned int *)((unsigned long)context_ptr+0x00006298+4*17))=0xf8ddd4c8;
*((unsigned int *)((unsigned long)context_ptr+0x00006298+4*18))=0x410a51a5;
*((unsigned int *)((unsigned long)context_ptr+0x00006298+4*19))=0x4426c5cc;
*((unsigned int *)((unsigned long)context_ptr+0x00006298+4*20))=0x2e0c8825;
*((unsigned int *)((unsigned long)context_ptr+0x00006298+4*21))=0xc220fc46;
*((unsigned int *)((unsigned long)context_ptr+0x00006298+4*22))=0x94c103cd;
*((unsigned int *)((unsigned long)context_ptr+0x00006298+4*23))=0xca969215;
*((unsigned int *)((unsigned long)context_ptr+0x000038e8))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x000038e8+4*1))=0x00006710;
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
*((unsigned int *)((unsigned long)context_ptr+0x000008e8+4*1))=0x00006298;
*((unsigned int *)((unsigned long)context_ptr+0x000008e8+4*2))=0x00006700;
*((unsigned int *)((unsigned long)context_ptr+0x000008e8+4*3))=0x02220060;
*((unsigned int *)((unsigned long)context_ptr+0x000008e8+4*4))=0x0fc11c19;
*((unsigned int *)((unsigned long)context_ptr+0x000008e8+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000001ec&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006620,"\x53\x71\xd1\x90\x39\x84\xb0\x9b\x1a\xe3\x1e\x65\x65\x59\x54\xd1\xa3\xbe\xf6\x4e",20))
printf("strip: 5371d1903984b09b, Pass\n");
else
printf("strip: 5371d1903984b09b, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000062f8))=0x010a0012;
*((unsigned int *)((unsigned long)context_ptr+0x000062f8+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000062f8+4*2))=0x02020061;
*((unsigned int *)((unsigned long)context_ptr+0x000062f8+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x000065cc))=0x14d8b530;
*((unsigned int *)((unsigned long)context_ptr+0x000065cc+4*1))=0x9dbfd393;
*((unsigned int *)((unsigned long)context_ptr+0x000065cc+4*2))=0x63c82121;
*((unsigned int *)((unsigned long)context_ptr+0x000065cc+4*3))=0x0fecf66d;
*((unsigned int *)((unsigned long)context_ptr+0x000065cc+4*4))=0x6bae227c;
*((unsigned int *)((unsigned long)context_ptr+0x000065cc+4*5))=0xe3929afe;
*((unsigned int *)((unsigned long)context_ptr+0x000065cc+4*6))=0xd1c33f53;
*((unsigned int *)((unsigned long)context_ptr+0x000065cc+4*7))=0xb6e009ac;
*((unsigned int *)((unsigned long)context_ptr+0x000065cc+4*8))=0x0518ef4e;
*((unsigned int *)((unsigned long)context_ptr+0x000065cc+4*9))=0xe342d6cb;
*((unsigned int *)((unsigned long)context_ptr+0x000065cc+4*10))=0x1240ab85;
*((unsigned int *)((unsigned long)context_ptr+0x000065cc+4*11))=0xfda54339;
*((unsigned int *)((unsigned long)context_ptr+0x000065cc+4*12))=0x1a866486;
*((unsigned int *)((unsigned long)context_ptr+0x000065cc+4*13))=0xa4a4a8b6;
*((unsigned int *)((unsigned long)context_ptr+0x000065cc+4*14))=0x5671ea22;
*((unsigned int *)((unsigned long)context_ptr+0x000065cc+4*15))=0x13e45159;
*((unsigned int *)((unsigned long)context_ptr+0x000065cc+4*16))=0x8719428f;
*((unsigned int *)((unsigned long)context_ptr+0x000065cc+4*17))=0xeb5c598e;
*((unsigned int *)((unsigned long)context_ptr+0x000065cc+4*18))=0xaab1cd8c;
*((unsigned int *)((unsigned long)context_ptr+0x000065cc+4*19))=0x7774beef;
*((unsigned int *)((unsigned long)context_ptr+0x000065cc+4*20))=0xc3cbd8ca;
*((unsigned int *)((unsigned long)context_ptr+0x000065cc+4*21))=0x2f0f9b55;
*((unsigned int *)((unsigned long)context_ptr+0x000065cc+4*22))=0xb00ff824;
*((unsigned int *)((unsigned long)context_ptr+0x000065cc+4*23))=0xa63796d4;
*((unsigned int *)((unsigned long)context_ptr+0x000065cc+4*24))=0x000000c1;
*((unsigned int *)((unsigned long)context_ptr+0x00003900))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003900+4*1))=0x000063b0;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000900+4*1))=0x000065cc;
*((unsigned int *)((unsigned long)context_ptr+0x00000900+4*2))=0x000062f8;
*((unsigned int *)((unsigned long)context_ptr+0x00000900+4*3))=0x02220061;
*((unsigned int *)((unsigned long)context_ptr+0x00000900+4*4))=0x0ead0ab3;
*((unsigned int *)((unsigned long)context_ptr+0x00000900+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000001f2&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006314,"\xce\x30\xd4\x36\x8c\x05\xcd\xf0\xd9\x88\xd2\xee\xe9\xe0\x2f\x87\x00\xc6\x50\xfb",20))
printf("strip: ce30d4368c05cdf0, Pass\n");
else
printf("strip: ce30d4368c05cdf0, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006630))=0x010a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006630+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006630+4*2))=0x02020062;
*((unsigned int *)((unsigned long)context_ptr+0x00006630+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x000067e4))=0x60749d35;
*((unsigned int *)((unsigned long)context_ptr+0x000067e4+4*1))=0x62c5a95a;
*((unsigned int *)((unsigned long)context_ptr+0x000067e4+4*2))=0x50dffc30;
*((unsigned int *)((unsigned long)context_ptr+0x000067e4+4*3))=0x2cd6a219;
*((unsigned int *)((unsigned long)context_ptr+0x000067e4+4*4))=0xac095dad;
*((unsigned int *)((unsigned long)context_ptr+0x000067e4+4*5))=0x2d3ccb6d;
*((unsigned int *)((unsigned long)context_ptr+0x000067e4+4*6))=0x92e1c258;
*((unsigned int *)((unsigned long)context_ptr+0x000067e4+4*7))=0x06292d9c;
*((unsigned int *)((unsigned long)context_ptr+0x000067e4+4*8))=0x32ddc73a;
*((unsigned int *)((unsigned long)context_ptr+0x000067e4+4*9))=0x94cf6522;
*((unsigned int *)((unsigned long)context_ptr+0x000067e4+4*10))=0x064112c8;
*((unsigned int *)((unsigned long)context_ptr+0x000067e4+4*11))=0x1872fa77;
*((unsigned int *)((unsigned long)context_ptr+0x000067e4+4*12))=0xfe14dc11;
*((unsigned int *)((unsigned long)context_ptr+0x000067e4+4*13))=0x12743a1b;
*((unsigned int *)((unsigned long)context_ptr+0x000067e4+4*14))=0x2847bfc2;
*((unsigned int *)((unsigned long)context_ptr+0x000067e4+4*15))=0x0163b0f1;
*((unsigned int *)((unsigned long)context_ptr+0x000067e4+4*16))=0x47867c36;
*((unsigned int *)((unsigned long)context_ptr+0x000067e4+4*17))=0xa12632ef;
*((unsigned int *)((unsigned long)context_ptr+0x000067e4+4*18))=0x77d9e94f;
*((unsigned int *)((unsigned long)context_ptr+0x000067e4+4*19))=0x5c864c7d;
*((unsigned int *)((unsigned long)context_ptr+0x000067e4+4*20))=0x751e88fb;
*((unsigned int *)((unsigned long)context_ptr+0x000067e4+4*21))=0x854a816a;
*((unsigned int *)((unsigned long)context_ptr+0x000067e4+4*22))=0xb34ed2a6;
*((unsigned int *)((unsigned long)context_ptr+0x000067e4+4*23))=0x9230cb56;
*((unsigned int *)((unsigned long)context_ptr+0x000067e4+4*24))=0x0000eb39;
*((unsigned int *)((unsigned long)context_ptr+0x00003918))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003918+4*1))=0x00006308;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000918+4*1))=0x000067e4;
*((unsigned int *)((unsigned long)context_ptr+0x00000918+4*2))=0x00006630;
*((unsigned int *)((unsigned long)context_ptr+0x00000918+4*3))=0x02220062;
*((unsigned int *)((unsigned long)context_ptr+0x00000918+4*4))=0x00b096dc;
*((unsigned int *)((unsigned long)context_ptr+0x00000918+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000001f8&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006408,"\x63\x54\xcb\x01\x61\xdb\x74\xd2\xc9\xca\x56\x9f\x9a\x58\xb7\x5a\xd6\xe8\x36\x13",20))
printf("strip: 6354cb0161db74d2, Pass\n");
else
printf("strip: 6354cb0161db74d2, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x0000631c))=0x010a0012;
*((unsigned int *)((unsigned long)context_ptr+0x0000631c+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x0000631c+4*2))=0x02020063;
*((unsigned int *)((unsigned long)context_ptr+0x0000631c+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x00006848))=0xc5669e6a;
*((unsigned int *)((unsigned long)context_ptr+0x00006848+4*1))=0xbaedb5b4;
*((unsigned int *)((unsigned long)context_ptr+0x00006848+4*2))=0x7e104f86;
*((unsigned int *)((unsigned long)context_ptr+0x00006848+4*3))=0x8804feb8;
*((unsigned int *)((unsigned long)context_ptr+0x00006848+4*4))=0x9a661bf0;
*((unsigned int *)((unsigned long)context_ptr+0x00006848+4*5))=0x82665eb3;
*((unsigned int *)((unsigned long)context_ptr+0x00006848+4*6))=0xab2f5c0a;
*((unsigned int *)((unsigned long)context_ptr+0x00006848+4*7))=0xcc0145a9;
*((unsigned int *)((unsigned long)context_ptr+0x00006848+4*8))=0xdf00f908;
*((unsigned int *)((unsigned long)context_ptr+0x00006848+4*9))=0xf23e3287;
*((unsigned int *)((unsigned long)context_ptr+0x00006848+4*10))=0x58875e1c;
*((unsigned int *)((unsigned long)context_ptr+0x00006848+4*11))=0x51766149;
*((unsigned int *)((unsigned long)context_ptr+0x00006848+4*12))=0xeae0b620;
*((unsigned int *)((unsigned long)context_ptr+0x00006848+4*13))=0x00b7a0a9;
*((unsigned int *)((unsigned long)context_ptr+0x00006848+4*14))=0x2fc9a24d;
*((unsigned int *)((unsigned long)context_ptr+0x00006848+4*15))=0x89869a1f;
*((unsigned int *)((unsigned long)context_ptr+0x00006848+4*16))=0x3c1cd57b;
*((unsigned int *)((unsigned long)context_ptr+0x00006848+4*17))=0x6292d397;
*((unsigned int *)((unsigned long)context_ptr+0x00006848+4*18))=0xef365a59;
*((unsigned int *)((unsigned long)context_ptr+0x00006848+4*19))=0x675ae2c6;
*((unsigned int *)((unsigned long)context_ptr+0x00006848+4*20))=0xa2770536;
*((unsigned int *)((unsigned long)context_ptr+0x00006848+4*21))=0xc53ef9f3;
*((unsigned int *)((unsigned long)context_ptr+0x00006848+4*22))=0xe091282c;
*((unsigned int *)((unsigned long)context_ptr+0x00006848+4*23))=0x4fb19856;
*((unsigned int *)((unsigned long)context_ptr+0x00006848+4*24))=0x00a1940b;
*((unsigned int *)((unsigned long)context_ptr+0x00003930))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003930+4*1))=0x00006080;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000930+4*1))=0x00006848;
*((unsigned int *)((unsigned long)context_ptr+0x00000930+4*2))=0x0000631c;
*((unsigned int *)((unsigned long)context_ptr+0x00000930+4*3))=0x02220063;
*((unsigned int *)((unsigned long)context_ptr+0x00000930+4*4))=0x082f39b2;
*((unsigned int *)((unsigned long)context_ptr+0x00000930+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000001fe&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x0000641c,"\xcc\x5f\x56\xf8\xa1\xb1\xb5\x23\x9f\x77\xbc\xba\xd2\x43\x1f\xd0\x8a\x9b\xd9\x1d",20))
printf("strip: cc5f56f8a1b1b523, Pass\n");
else
printf("strip: cc5f56f8a1b1b523, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x0000632c))=0x010a0012;
*((unsigned int *)((unsigned long)context_ptr+0x0000632c+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x0000632c+4*2))=0x02020064;
*((unsigned int *)((unsigned long)context_ptr+0x0000632c+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x000063c4))=0x04de4d52;
*((unsigned int *)((unsigned long)context_ptr+0x000063c4+4*1))=0x0ffc833a;
*((unsigned int *)((unsigned long)context_ptr+0x000063c4+4*2))=0x0577471b;
*((unsigned int *)((unsigned long)context_ptr+0x000063c4+4*3))=0x57809741;
*((unsigned int *)((unsigned long)context_ptr+0x000063c4+4*4))=0x4726219e;
*((unsigned int *)((unsigned long)context_ptr+0x000063c4+4*5))=0xbe506bf3;
*((unsigned int *)((unsigned long)context_ptr+0x000063c4+4*6))=0xd0e827d7;
*((unsigned int *)((unsigned long)context_ptr+0x000063c4+4*7))=0xd67e325e;
*((unsigned int *)((unsigned long)context_ptr+0x000063c4+4*8))=0x9acb2b35;
*((unsigned int *)((unsigned long)context_ptr+0x000063c4+4*9))=0xf64f7eba;
*((unsigned int *)((unsigned long)context_ptr+0x000063c4+4*10))=0x0351aa3d;
*((unsigned int *)((unsigned long)context_ptr+0x000063c4+4*11))=0x83d2b685;
*((unsigned int *)((unsigned long)context_ptr+0x000063c4+4*12))=0x96945302;
*((unsigned int *)((unsigned long)context_ptr+0x000063c4+4*13))=0x2ab6f5ec;
*((unsigned int *)((unsigned long)context_ptr+0x000063c4+4*14))=0x12551fbd;
*((unsigned int *)((unsigned long)context_ptr+0x000063c4+4*15))=0x09b783cf;
*((unsigned int *)((unsigned long)context_ptr+0x000063c4+4*16))=0x287d342d;
*((unsigned int *)((unsigned long)context_ptr+0x000063c4+4*17))=0xf51b8f19;
*((unsigned int *)((unsigned long)context_ptr+0x000063c4+4*18))=0x4cc4fec6;
*((unsigned int *)((unsigned long)context_ptr+0x000063c4+4*19))=0x511f33cf;
*((unsigned int *)((unsigned long)context_ptr+0x000063c4+4*20))=0x11e31eb3;
*((unsigned int *)((unsigned long)context_ptr+0x000063c4+4*21))=0xc383b0c6;
*((unsigned int *)((unsigned long)context_ptr+0x000063c4+4*22))=0x4b26b18c;
*((unsigned int *)((unsigned long)context_ptr+0x000063c4+4*23))=0xbb96a18a;
*((unsigned int *)((unsigned long)context_ptr+0x000063c4+4*24))=0xf3f151b1;
*((unsigned int *)((unsigned long)context_ptr+0x00003948))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003948+4*1))=0x0000647c;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000948+4*1))=0x000063c4;
*((unsigned int *)((unsigned long)context_ptr+0x00000948+4*2))=0x0000632c;
*((unsigned int *)((unsigned long)context_ptr+0x00000948+4*3))=0x02220064;
*((unsigned int *)((unsigned long)context_ptr+0x00000948+4*4))=0x0631432d;
*((unsigned int *)((unsigned long)context_ptr+0x00000948+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000204&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006430,"\x38\x1b\x63\xbc\x4b\xcb\x22\xb6\xdb\x73\x9f\x7e\x73\xfb\xd3\xf9\xcb\x3a\xc7\x33",20))
printf("strip: 381b63bc4bcb22b6, Pass\n");
else
printf("strip: 381b63bc4bcb22b6, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x0000633c))=0x010a0012;
*((unsigned int *)((unsigned long)context_ptr+0x0000633c+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x0000633c+4*2))=0x02020065;
*((unsigned int *)((unsigned long)context_ptr+0x0000633c+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x00006094))=0x8e007a06;
*((unsigned int *)((unsigned long)context_ptr+0x00006094+4*1))=0x09e6d13c;
*((unsigned int *)((unsigned long)context_ptr+0x00006094+4*2))=0x10aeeaa8;
*((unsigned int *)((unsigned long)context_ptr+0x00006094+4*3))=0xa62710a4;
*((unsigned int *)((unsigned long)context_ptr+0x00006094+4*4))=0xe09408ae;
*((unsigned int *)((unsigned long)context_ptr+0x00006094+4*5))=0xa437a4a1;
*((unsigned int *)((unsigned long)context_ptr+0x00006094+4*6))=0xd13dd526;
*((unsigned int *)((unsigned long)context_ptr+0x00006094+4*7))=0x4d559806;
*((unsigned int *)((unsigned long)context_ptr+0x00006094+4*8))=0x2dfa3e9c;
*((unsigned int *)((unsigned long)context_ptr+0x00006094+4*9))=0xeb4fad8b;
*((unsigned int *)((unsigned long)context_ptr+0x00006094+4*10))=0x8f7037c7;
*((unsigned int *)((unsigned long)context_ptr+0x00006094+4*11))=0x4ebdc506;
*((unsigned int *)((unsigned long)context_ptr+0x00006094+4*12))=0xdd6f6aca;
*((unsigned int *)((unsigned long)context_ptr+0x00006094+4*13))=0x33bac74e;
*((unsigned int *)((unsigned long)context_ptr+0x00006094+4*14))=0x409c284b;
*((unsigned int *)((unsigned long)context_ptr+0x00006094+4*15))=0xc13e33ec;
*((unsigned int *)((unsigned long)context_ptr+0x00006094+4*16))=0xcb006e9b;
*((unsigned int *)((unsigned long)context_ptr+0x00006094+4*17))=0x30518855;
*((unsigned int *)((unsigned long)context_ptr+0x00006094+4*18))=0xd3b77fe4;
*((unsigned int *)((unsigned long)context_ptr+0x00006094+4*19))=0x0c17a467;
*((unsigned int *)((unsigned long)context_ptr+0x00006094+4*20))=0xf6f1fb9a;
*((unsigned int *)((unsigned long)context_ptr+0x00006094+4*21))=0x9db77395;
*((unsigned int *)((unsigned long)context_ptr+0x00006094+4*22))=0x4eabe8dc;
*((unsigned int *)((unsigned long)context_ptr+0x00006094+4*23))=0x14babd7f;
*((unsigned int *)((unsigned long)context_ptr+0x00006094+4*24))=0x6b32350b;
*((unsigned int *)((unsigned long)context_ptr+0x00006094+4*25))=0x0000000c;
*((unsigned int *)((unsigned long)context_ptr+0x00003960))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003960+4*1))=0x00006428;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000960+4*1))=0x00006094;
*((unsigned int *)((unsigned long)context_ptr+0x00000960+4*2))=0x0000633c;
*((unsigned int *)((unsigned long)context_ptr+0x00000960+4*3))=0x02220065;
*((unsigned int *)((unsigned long)context_ptr+0x00000960+4*4))=0x021aaa7a;
*((unsigned int *)((unsigned long)context_ptr+0x00000960+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000020a&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000064d4,"\x76\x99\xcd\xaf\x1b\x55\xa0\x7d\x78\x8a\x8c\xd9\xde\x97\x3b\xbd\x2c\x5e\x74\x43",20))
printf("strip: 7699cdaf1b55a07d, Pass\n");
else
printf("strip: 7699cdaf1b55a07d, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x0000643c))=0x010a0012;
*((unsigned int *)((unsigned long)context_ptr+0x0000643c+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x0000643c+4*2))=0x02020066;
*((unsigned int *)((unsigned long)context_ptr+0x0000643c+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x000060fc))=0xafbd4998;
*((unsigned int *)((unsigned long)context_ptr+0x000060fc+4*1))=0xa21f2b69;
*((unsigned int *)((unsigned long)context_ptr+0x000060fc+4*2))=0x9faff70d;
*((unsigned int *)((unsigned long)context_ptr+0x000060fc+4*3))=0x953c964d;
*((unsigned int *)((unsigned long)context_ptr+0x000060fc+4*4))=0xc4f6e664;
*((unsigned int *)((unsigned long)context_ptr+0x000060fc+4*5))=0x1bfac9d1;
*((unsigned int *)((unsigned long)context_ptr+0x000060fc+4*6))=0xdf82e8ca;
*((unsigned int *)((unsigned long)context_ptr+0x000060fc+4*7))=0x7bcd07cc;
*((unsigned int *)((unsigned long)context_ptr+0x000060fc+4*8))=0x9798559b;
*((unsigned int *)((unsigned long)context_ptr+0x000060fc+4*9))=0xa92e8025;
*((unsigned int *)((unsigned long)context_ptr+0x000060fc+4*10))=0xf5975b0d;
*((unsigned int *)((unsigned long)context_ptr+0x000060fc+4*11))=0x50652719;
*((unsigned int *)((unsigned long)context_ptr+0x000060fc+4*12))=0xab21d3b5;
*((unsigned int *)((unsigned long)context_ptr+0x000060fc+4*13))=0x4457e9cb;
*((unsigned int *)((unsigned long)context_ptr+0x000060fc+4*14))=0xb29066bf;
*((unsigned int *)((unsigned long)context_ptr+0x000060fc+4*15))=0xbbeebf4d;
*((unsigned int *)((unsigned long)context_ptr+0x000060fc+4*16))=0x91ef7953;
*((unsigned int *)((unsigned long)context_ptr+0x000060fc+4*17))=0xe85c801c;
*((unsigned int *)((unsigned long)context_ptr+0x000060fc+4*18))=0xed092f8d;
*((unsigned int *)((unsigned long)context_ptr+0x000060fc+4*19))=0x5d68a727;
*((unsigned int *)((unsigned long)context_ptr+0x000060fc+4*20))=0x492f6eb8;
*((unsigned int *)((unsigned long)context_ptr+0x000060fc+4*21))=0x73d19563;
*((unsigned int *)((unsigned long)context_ptr+0x000060fc+4*22))=0xcc6156f1;
*((unsigned int *)((unsigned long)context_ptr+0x000060fc+4*23))=0xa590ff5e;
*((unsigned int *)((unsigned long)context_ptr+0x000060fc+4*24))=0x59b05688;
*((unsigned int *)((unsigned long)context_ptr+0x000060fc+4*25))=0x00002316;
*((unsigned int *)((unsigned long)context_ptr+0x00003978))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003978+4*1))=0x00006490;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000978+4*1))=0x000060fc;
*((unsigned int *)((unsigned long)context_ptr+0x00000978+4*2))=0x0000643c;
*((unsigned int *)((unsigned long)context_ptr+0x00000978+4*3))=0x02220066;
*((unsigned int *)((unsigned long)context_ptr+0x00000978+4*4))=0x046f54b7;
*((unsigned int *)((unsigned long)context_ptr+0x00000978+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000210&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006454,"\x1c\x30\xed\xb0\x3c\x61\x1a\x48\xa7\xbe\x9a\xcb\xf8\x6b\x56\xa3\x16\x12\xa1\xba",20))
printf("strip: 1c30edb03c611a48, Pass\n");
else
printf("strip: 1c30edb03c611a48, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x0000634c))=0x010a0012;
*((unsigned int *)((unsigned long)context_ptr+0x0000634c+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x0000634c+4*2))=0x02020067;
*((unsigned int *)((unsigned long)context_ptr+0x0000634c+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x00006164))=0x1205b15c;
*((unsigned int *)((unsigned long)context_ptr+0x00006164+4*1))=0xc6600ec8;
*((unsigned int *)((unsigned long)context_ptr+0x00006164+4*2))=0xc256d510;
*((unsigned int *)((unsigned long)context_ptr+0x00006164+4*3))=0xe567adfd;
*((unsigned int *)((unsigned long)context_ptr+0x00006164+4*4))=0x56783947;
*((unsigned int *)((unsigned long)context_ptr+0x00006164+4*5))=0x93f05fe7;
*((unsigned int *)((unsigned long)context_ptr+0x00006164+4*6))=0xa0196a0f;
*((unsigned int *)((unsigned long)context_ptr+0x00006164+4*7))=0x28999185;
*((unsigned int *)((unsigned long)context_ptr+0x00006164+4*8))=0xe3138470;
*((unsigned int *)((unsigned long)context_ptr+0x00006164+4*9))=0x88ffe858;
*((unsigned int *)((unsigned long)context_ptr+0x00006164+4*10))=0xc47a53ab;
*((unsigned int *)((unsigned long)context_ptr+0x00006164+4*11))=0xa45ca6ef;
*((unsigned int *)((unsigned long)context_ptr+0x00006164+4*12))=0xaf887086;
*((unsigned int *)((unsigned long)context_ptr+0x00006164+4*13))=0x3a816526;
*((unsigned int *)((unsigned long)context_ptr+0x00006164+4*14))=0x9e918587;
*((unsigned int *)((unsigned long)context_ptr+0x00006164+4*15))=0x7d36bd50;
*((unsigned int *)((unsigned long)context_ptr+0x00006164+4*16))=0xf74a42e3;
*((unsigned int *)((unsigned long)context_ptr+0x00006164+4*17))=0x85550fd9;
*((unsigned int *)((unsigned long)context_ptr+0x00006164+4*18))=0xa961ae3d;
*((unsigned int *)((unsigned long)context_ptr+0x00006164+4*19))=0x59e90d91;
*((unsigned int *)((unsigned long)context_ptr+0x00006164+4*20))=0x08ebea00;
*((unsigned int *)((unsigned long)context_ptr+0x00006164+4*21))=0x34073ef3;
*((unsigned int *)((unsigned long)context_ptr+0x00006164+4*22))=0xf097511e;
*((unsigned int *)((unsigned long)context_ptr+0x00006164+4*23))=0x68b70563;
*((unsigned int *)((unsigned long)context_ptr+0x00006164+4*24))=0x35def350;
*((unsigned int *)((unsigned long)context_ptr+0x00006164+4*25))=0x00cf1f36;
*((unsigned int *)((unsigned long)context_ptr+0x00003990))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003990+4*1))=0x0000644c;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000990+4*1))=0x00006164;
*((unsigned int *)((unsigned long)context_ptr+0x00000990+4*2))=0x0000634c;
*((unsigned int *)((unsigned long)context_ptr+0x00000990+4*3))=0x02220067;
*((unsigned int *)((unsigned long)context_ptr+0x00000990+4*4))=0x0c69e37a;
*((unsigned int *)((unsigned long)context_ptr+0x00000990+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000216&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006378,"\xe5\x08\x2d\x3d\x71\xaf\x43\xf6\xeb\x3c\x5f\x73\xc8\x08\x5f\x57\x0e\x27\x13\xb0",20))
printf("strip: e5082d3d71af43f6, Pass\n");
else
printf("strip: e5082d3d71af43f6, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000061cc))=0x010a0012;
*((unsigned int *)((unsigned long)context_ptr+0x000061cc+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000061cc+4*2))=0x02020068;
*((unsigned int *)((unsigned long)context_ptr+0x000061cc+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x000064a4))=0x08462d0c;
*((unsigned int *)((unsigned long)context_ptr+0x000064a4+4*1))=0xf1dac404;
*((unsigned int *)((unsigned long)context_ptr+0x000064a4+4*2))=0x4a857fcc;
*((unsigned int *)((unsigned long)context_ptr+0x000064a4+4*3))=0xc2ebff0c;
*((unsigned int *)((unsigned long)context_ptr+0x000064a4+4*4))=0xf3bb5c45;
*((unsigned int *)((unsigned long)context_ptr+0x000064a4+4*5))=0xb17dd974;
*((unsigned int *)((unsigned long)context_ptr+0x000064a4+4*6))=0xc4afbde7;
*((unsigned int *)((unsigned long)context_ptr+0x000064a4+4*7))=0x809414d9;
*((unsigned int *)((unsigned long)context_ptr+0x000064a4+4*8))=0x98522da7;
*((unsigned int *)((unsigned long)context_ptr+0x000064a4+4*9))=0x66153cc5;
*((unsigned int *)((unsigned long)context_ptr+0x000064a4+4*10))=0x03486f86;
*((unsigned int *)((unsigned long)context_ptr+0x000064a4+4*11))=0xb00bb6b0;
*((unsigned int *)((unsigned long)context_ptr+0x000064a4+4*12))=0xbfcc1a3d;
*((unsigned int *)((unsigned long)context_ptr+0x000064a4+4*13))=0x2563798b;
*((unsigned int *)((unsigned long)context_ptr+0x000064a4+4*14))=0x1f15154c;
*((unsigned int *)((unsigned long)context_ptr+0x000064a4+4*15))=0x8fec192e;
*((unsigned int *)((unsigned long)context_ptr+0x000064a4+4*16))=0x3b82fe58;
*((unsigned int *)((unsigned long)context_ptr+0x000064a4+4*17))=0xd1e0cc87;
*((unsigned int *)((unsigned long)context_ptr+0x000064a4+4*18))=0xbcb72757;
*((unsigned int *)((unsigned long)context_ptr+0x000064a4+4*19))=0x7fa0aa98;
*((unsigned int *)((unsigned long)context_ptr+0x000064a4+4*20))=0x3452fa28;
*((unsigned int *)((unsigned long)context_ptr+0x000064a4+4*21))=0x551512ac;
*((unsigned int *)((unsigned long)context_ptr+0x000064a4+4*22))=0x3f3d63f4;
*((unsigned int *)((unsigned long)context_ptr+0x000064a4+4*23))=0x019d0e6f;
*((unsigned int *)((unsigned long)context_ptr+0x000064a4+4*24))=0x6cff9417;
*((unsigned int *)((unsigned long)context_ptr+0x000064a4+4*25))=0xf3acf373;
*((unsigned int *)((unsigned long)context_ptr+0x000039a8))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x000039a8+4*1))=0x0000635c;
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
*((unsigned int *)((unsigned long)context_ptr+0x000009a8+4*1))=0x000064a4;
*((unsigned int *)((unsigned long)context_ptr+0x000009a8+4*2))=0x000061cc;
*((unsigned int *)((unsigned long)context_ptr+0x000009a8+4*3))=0x02220068;
*((unsigned int *)((unsigned long)context_ptr+0x000009a8+4*4))=0x090d9633;
*((unsigned int *)((unsigned long)context_ptr+0x000009a8+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000021c&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006544,"\xa5\x0b\xec\x0d\xc9\x2a\x37\x18\xb7\xd2\xd0\x26\x87\x2a\xe4\x26\x01\x36\xfc\x4c",20))
printf("strip: a50bec0dc92a3718, Pass\n");
else
printf("strip: a50bec0dc92a3718, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006370))=0x010a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006370+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006370+4*2))=0x02020069;
*((unsigned int *)((unsigned long)context_ptr+0x00006370+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x000068ac))=0x9906d8ff;
*((unsigned int *)((unsigned long)context_ptr+0x000068ac+4*1))=0x118028b6;
*((unsigned int *)((unsigned long)context_ptr+0x000068ac+4*2))=0x15d91689;
*((unsigned int *)((unsigned long)context_ptr+0x000068ac+4*3))=0x0f8821f7;
*((unsigned int *)((unsigned long)context_ptr+0x000068ac+4*4))=0x3c28d744;
*((unsigned int *)((unsigned long)context_ptr+0x000068ac+4*5))=0x223fd1ec;
*((unsigned int *)((unsigned long)context_ptr+0x000068ac+4*6))=0xbc5458ea;
*((unsigned int *)((unsigned long)context_ptr+0x000068ac+4*7))=0xe63cc87c;
*((unsigned int *)((unsigned long)context_ptr+0x000068ac+4*8))=0x03352b82;
*((unsigned int *)((unsigned long)context_ptr+0x000068ac+4*9))=0xe20fd5aa;
*((unsigned int *)((unsigned long)context_ptr+0x000068ac+4*10))=0xbb30bec6;
*((unsigned int *)((unsigned long)context_ptr+0x000068ac+4*11))=0xd5e44f5e;
*((unsigned int *)((unsigned long)context_ptr+0x000068ac+4*12))=0x3b83e703;
*((unsigned int *)((unsigned long)context_ptr+0x000068ac+4*13))=0x00e3c966;
*((unsigned int *)((unsigned long)context_ptr+0x000068ac+4*14))=0x8a2be094;
*((unsigned int *)((unsigned long)context_ptr+0x000068ac+4*15))=0x13bbdc2a;
*((unsigned int *)((unsigned long)context_ptr+0x000068ac+4*16))=0xd3cea7f4;
*((unsigned int *)((unsigned long)context_ptr+0x000068ac+4*17))=0x39e12861;
*((unsigned int *)((unsigned long)context_ptr+0x000068ac+4*18))=0x5feb27e5;
*((unsigned int *)((unsigned long)context_ptr+0x000068ac+4*19))=0x0a0dbe79;
*((unsigned int *)((unsigned long)context_ptr+0x000068ac+4*20))=0x05aa128f;
*((unsigned int *)((unsigned long)context_ptr+0x000068ac+4*21))=0x98b86e1c;
*((unsigned int *)((unsigned long)context_ptr+0x000068ac+4*22))=0x2ab5d46b;
*((unsigned int *)((unsigned long)context_ptr+0x000068ac+4*23))=0xe6751116;
*((unsigned int *)((unsigned long)context_ptr+0x000068ac+4*24))=0x0c5f65d9;
*((unsigned int *)((unsigned long)context_ptr+0x000068ac+4*25))=0xcb3be340;
*((unsigned int *)((unsigned long)context_ptr+0x000068ac+4*26))=0x00000083;
*((unsigned int *)((unsigned long)context_ptr+0x000039c0))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x000039c0+4*1))=0x00006380;
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
*((unsigned int *)((unsigned long)context_ptr+0x000009c0+4*1))=0x000068ac;
*((unsigned int *)((unsigned long)context_ptr+0x000009c0+4*2))=0x00006370;
*((unsigned int *)((unsigned long)context_ptr+0x000009c0+4*3))=0x02220069;
*((unsigned int *)((unsigned long)context_ptr+0x000009c0+4*4))=0x00dbab82;
*((unsigned int *)((unsigned long)context_ptr+0x000009c0+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000222&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x0000639c,"\xde\x0d\xc2\xc1\x4f\x61\xac\x24\xa9\x5a\x39\xb0\x21\x9e\xdc\xbb\x36\x7a\xcc\xd0",20))
printf("strip: de0dc2c14f61ac24, Pass\n");
else
printf("strip: de0dc2c14f61ac24, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006018))=0x010a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006018+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006018+4*2))=0x0202006a;
*((unsigned int *)((unsigned long)context_ptr+0x00006018+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x00006724))=0xe6784636;
*((unsigned int *)((unsigned long)context_ptr+0x00006724+4*1))=0x1b400a84;
*((unsigned int *)((unsigned long)context_ptr+0x00006724+4*2))=0xa5d958f6;
*((unsigned int *)((unsigned long)context_ptr+0x00006724+4*3))=0x39df63e7;
*((unsigned int *)((unsigned long)context_ptr+0x00006724+4*4))=0x1806fb9f;
*((unsigned int *)((unsigned long)context_ptr+0x00006724+4*5))=0x8fec395e;
*((unsigned int *)((unsigned long)context_ptr+0x00006724+4*6))=0xa6132433;
*((unsigned int *)((unsigned long)context_ptr+0x00006724+4*7))=0x6ac70adc;
*((unsigned int *)((unsigned long)context_ptr+0x00006724+4*8))=0xbacb2f08;
*((unsigned int *)((unsigned long)context_ptr+0x00006724+4*9))=0x52bfb066;
*((unsigned int *)((unsigned long)context_ptr+0x00006724+4*10))=0xb9d9f37f;
*((unsigned int *)((unsigned long)context_ptr+0x00006724+4*11))=0x31c47899;
*((unsigned int *)((unsigned long)context_ptr+0x00006724+4*12))=0x0f06b14a;
*((unsigned int *)((unsigned long)context_ptr+0x00006724+4*13))=0xabb63cc9;
*((unsigned int *)((unsigned long)context_ptr+0x00006724+4*14))=0x01c3dc01;
*((unsigned int *)((unsigned long)context_ptr+0x00006724+4*15))=0x73e5dc05;
*((unsigned int *)((unsigned long)context_ptr+0x00006724+4*16))=0xb06f2c27;
*((unsigned int *)((unsigned long)context_ptr+0x00006724+4*17))=0xc310c08e;
*((unsigned int *)((unsigned long)context_ptr+0x00006724+4*18))=0x47d2ce45;
*((unsigned int *)((unsigned long)context_ptr+0x00006724+4*19))=0xc9f501d3;
*((unsigned int *)((unsigned long)context_ptr+0x00006724+4*20))=0x65c6d483;
*((unsigned int *)((unsigned long)context_ptr+0x00006724+4*21))=0xd922a088;
*((unsigned int *)((unsigned long)context_ptr+0x00006724+4*22))=0xfced0d0e;
*((unsigned int *)((unsigned long)context_ptr+0x00006724+4*23))=0xff01479f;
*((unsigned int *)((unsigned long)context_ptr+0x00006724+4*24))=0x2284a32e;
*((unsigned int *)((unsigned long)context_ptr+0x00006724+4*25))=0xbf854af4;
*((unsigned int *)((unsigned long)context_ptr+0x00006724+4*26))=0x0000caf0;
*((unsigned int *)((unsigned long)context_ptr+0x000039d8))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x000039d8+4*1))=0x00006394;
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
*((unsigned int *)((unsigned long)context_ptr+0x000009d8+4*1))=0x00006724;
*((unsigned int *)((unsigned long)context_ptr+0x000009d8+4*2))=0x00006018;
*((unsigned int *)((unsigned long)context_ptr+0x000009d8+4*3))=0x0222006a;
*((unsigned int *)((unsigned long)context_ptr+0x000009d8+4*4))=0x074fb709;
*((unsigned int *)((unsigned long)context_ptr+0x000009d8+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000228&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006038,"\x8a\xd4\xc8\x7e\x23\x31\x94\xa5\x52\xa2\x83\x87\x7a\x11\x6f\x94\x90\x66\x70\xf2",20))
printf("strip: 8ad4c87e233194a5, Pass\n");
else
printf("strip: 8ad4c87e233194a5, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006008))=0x010a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006008+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006008+4*2))=0x0202006b;
*((unsigned int *)((unsigned long)context_ptr+0x00006008+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x00006918))=0x055a56af;
*((unsigned int *)((unsigned long)context_ptr+0x00006918+4*1))=0x1b1882f9;
*((unsigned int *)((unsigned long)context_ptr+0x00006918+4*2))=0x25b89624;
*((unsigned int *)((unsigned long)context_ptr+0x00006918+4*3))=0x993ca260;
*((unsigned int *)((unsigned long)context_ptr+0x00006918+4*4))=0x8c94a455;
*((unsigned int *)((unsigned long)context_ptr+0x00006918+4*5))=0x2859dc1e;
*((unsigned int *)((unsigned long)context_ptr+0x00006918+4*6))=0x7337d8c2;
*((unsigned int *)((unsigned long)context_ptr+0x00006918+4*7))=0xa7655795;
*((unsigned int *)((unsigned long)context_ptr+0x00006918+4*8))=0x05e0a0ef;
*((unsigned int *)((unsigned long)context_ptr+0x00006918+4*9))=0x72de848a;
*((unsigned int *)((unsigned long)context_ptr+0x00006918+4*10))=0x5e7abdc0;
*((unsigned int *)((unsigned long)context_ptr+0x00006918+4*11))=0xe0816722;
*((unsigned int *)((unsigned long)context_ptr+0x00006918+4*12))=0x2f1049bd;
*((unsigned int *)((unsigned long)context_ptr+0x00006918+4*13))=0xc7d129c1;
*((unsigned int *)((unsigned long)context_ptr+0x00006918+4*14))=0x8274542d;
*((unsigned int *)((unsigned long)context_ptr+0x00006918+4*15))=0x1b1e16c4;
*((unsigned int *)((unsigned long)context_ptr+0x00006918+4*16))=0xcf1b67b4;
*((unsigned int *)((unsigned long)context_ptr+0x00006918+4*17))=0x35d1d21f;
*((unsigned int *)((unsigned long)context_ptr+0x00006918+4*18))=0xca525d9b;
*((unsigned int *)((unsigned long)context_ptr+0x00006918+4*19))=0x5e91474c;
*((unsigned int *)((unsigned long)context_ptr+0x00006918+4*20))=0xedaebd92;
*((unsigned int *)((unsigned long)context_ptr+0x00006918+4*21))=0xe8f3810c;
*((unsigned int *)((unsigned long)context_ptr+0x00006918+4*22))=0x8c542f83;
*((unsigned int *)((unsigned long)context_ptr+0x00006918+4*23))=0xd4d251bc;
*((unsigned int *)((unsigned long)context_ptr+0x00006918+4*24))=0xf58aa1f8;
*((unsigned int *)((unsigned long)context_ptr+0x00006918+4*25))=0xf96528e3;
*((unsigned int *)((unsigned long)context_ptr+0x00006918+4*26))=0x00884118;
*((unsigned int *)((unsigned long)context_ptr+0x000039f0))=0x04c00014;
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
*((unsigned int *)((unsigned long)context_ptr+0x000009f0+4*1))=0x00006918;
*((unsigned int *)((unsigned long)context_ptr+0x000009f0+4*2))=0x00006008;
*((unsigned int *)((unsigned long)context_ptr+0x000009f0+4*3))=0x0222006b;
*((unsigned int *)((unsigned long)context_ptr+0x000009f0+4*4))=0x056f0f2f;
*((unsigned int *)((unsigned long)context_ptr+0x000009f0+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000022e&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x0000605c,"\x68\xe1\xd6\x68\xae\xbd\x1a\xb0\xc9\x6b\x08\xe5\x35\x63\x73\xbc\xf8\x30\xe9\x04",20))
printf("strip: 68e1d668aebd1ab0, Pass\n");
else
printf("strip: 68e1d668aebd1ab0, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006028))=0x010a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006028+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006028+4*2))=0x0202006c;
*((unsigned int *)((unsigned long)context_ptr+0x00006028+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x00006640))=0x099afd4f;
*((unsigned int *)((unsigned long)context_ptr+0x00006640+4*1))=0x176b9f0c;
*((unsigned int *)((unsigned long)context_ptr+0x00006640+4*2))=0xcaecf7e6;
*((unsigned int *)((unsigned long)context_ptr+0x00006640+4*3))=0x0e6d0441;
*((unsigned int *)((unsigned long)context_ptr+0x00006640+4*4))=0xfbe2799a;
*((unsigned int *)((unsigned long)context_ptr+0x00006640+4*5))=0xac176e20;
*((unsigned int *)((unsigned long)context_ptr+0x00006640+4*6))=0xdc26f88c;
*((unsigned int *)((unsigned long)context_ptr+0x00006640+4*7))=0x71c65d7b;
*((unsigned int *)((unsigned long)context_ptr+0x00006640+4*8))=0x76f7f69b;
*((unsigned int *)((unsigned long)context_ptr+0x00006640+4*9))=0x3b946332;
*((unsigned int *)((unsigned long)context_ptr+0x00006640+4*10))=0xee461c0a;
*((unsigned int *)((unsigned long)context_ptr+0x00006640+4*11))=0x7ba1fbfe;
*((unsigned int *)((unsigned long)context_ptr+0x00006640+4*12))=0x4c8f9bce;
*((unsigned int *)((unsigned long)context_ptr+0x00006640+4*13))=0xc8fefcf4;
*((unsigned int *)((unsigned long)context_ptr+0x00006640+4*14))=0xbe668afd;
*((unsigned int *)((unsigned long)context_ptr+0x00006640+4*15))=0x86bb680a;
*((unsigned int *)((unsigned long)context_ptr+0x00006640+4*16))=0x1fdf8107;
*((unsigned int *)((unsigned long)context_ptr+0x00006640+4*17))=0xc5995c3a;
*((unsigned int *)((unsigned long)context_ptr+0x00006640+4*18))=0xb5011898;
*((unsigned int *)((unsigned long)context_ptr+0x00006640+4*19))=0x2b846429;
*((unsigned int *)((unsigned long)context_ptr+0x00006640+4*20))=0x14778fb3;
*((unsigned int *)((unsigned long)context_ptr+0x00006640+4*21))=0x00e07d7a;
*((unsigned int *)((unsigned long)context_ptr+0x00006640+4*22))=0x232040bc;
*((unsigned int *)((unsigned long)context_ptr+0x00006640+4*23))=0x4977132c;
*((unsigned int *)((unsigned long)context_ptr+0x00006640+4*24))=0x91baa04f;
*((unsigned int *)((unsigned long)context_ptr+0x00006640+4*25))=0xfed21933;
*((unsigned int *)((unsigned long)context_ptr+0x00006640+4*26))=0x1510973c;
*((unsigned int *)((unsigned long)context_ptr+0x00003a08))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003a08+4*1))=0x0000605c;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000a08+4*1))=0x00006640;
*((unsigned int *)((unsigned long)context_ptr+0x00000a08+4*2))=0x00006028;
*((unsigned int *)((unsigned long)context_ptr+0x00000a08+4*3))=0x0222006c;
*((unsigned int *)((unsigned long)context_ptr+0x00000a08+4*4))=0x0bca27aa;
*((unsigned int *)((unsigned long)context_ptr+0x00000a08+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000234&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006468,"\xf9\xfd\xad\x8a\xed\xaa\xfc\xcd\xbb\x03\x91\x21\x9e\x72\x8e\x62\xaa\x56\x9b\x37",20))
printf("strip: f9fdad8aedaafccd, Pass\n");
else
printf("strip: f9fdad8aedaafccd, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x0000604c))=0x010a0012;
*((unsigned int *)((unsigned long)context_ptr+0x0000604c+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x0000604c+4*2))=0x0202006d;
*((unsigned int *)((unsigned long)context_ptr+0x0000604c+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x000061dc))=0x7a458ff3;
*((unsigned int *)((unsigned long)context_ptr+0x000061dc+4*1))=0xc890bfde;
*((unsigned int *)((unsigned long)context_ptr+0x000061dc+4*2))=0xcb0f6dec;
*((unsigned int *)((unsigned long)context_ptr+0x000061dc+4*3))=0xe6dcad3a;
*((unsigned int *)((unsigned long)context_ptr+0x000061dc+4*4))=0x5db2be0c;
*((unsigned int *)((unsigned long)context_ptr+0x000061dc+4*5))=0xe1332b9a;
*((unsigned int *)((unsigned long)context_ptr+0x000061dc+4*6))=0xb9afbc42;
*((unsigned int *)((unsigned long)context_ptr+0x000061dc+4*7))=0x980e8a47;
*((unsigned int *)((unsigned long)context_ptr+0x000061dc+4*8))=0x32b6f31d;
*((unsigned int *)((unsigned long)context_ptr+0x000061dc+4*9))=0x9a10747f;
*((unsigned int *)((unsigned long)context_ptr+0x000061dc+4*10))=0x22155732;
*((unsigned int *)((unsigned long)context_ptr+0x000061dc+4*11))=0xaf0375a7;
*((unsigned int *)((unsigned long)context_ptr+0x000061dc+4*12))=0x80c037bd;
*((unsigned int *)((unsigned long)context_ptr+0x000061dc+4*13))=0x2eb81a37;
*((unsigned int *)((unsigned long)context_ptr+0x000061dc+4*14))=0xe09bdeb3;
*((unsigned int *)((unsigned long)context_ptr+0x000061dc+4*15))=0xfd9cd956;
*((unsigned int *)((unsigned long)context_ptr+0x000061dc+4*16))=0xb36ba076;
*((unsigned int *)((unsigned long)context_ptr+0x000061dc+4*17))=0x05d91b31;
*((unsigned int *)((unsigned long)context_ptr+0x000061dc+4*18))=0x2a92eb59;
*((unsigned int *)((unsigned long)context_ptr+0x000061dc+4*19))=0x9d73e272;
*((unsigned int *)((unsigned long)context_ptr+0x000061dc+4*20))=0x47b1d068;
*((unsigned int *)((unsigned long)context_ptr+0x000061dc+4*21))=0x9254934b;
*((unsigned int *)((unsigned long)context_ptr+0x000061dc+4*22))=0x82dff9c3;
*((unsigned int *)((unsigned long)context_ptr+0x000061dc+4*23))=0x5a6e3058;
*((unsigned int *)((unsigned long)context_ptr+0x000061dc+4*24))=0xe0d2b147;
*((unsigned int *)((unsigned long)context_ptr+0x000061dc+4*25))=0x7334e5f9;
*((unsigned int *)((unsigned long)context_ptr+0x000061dc+4*26))=0x349587fa;
*((unsigned int *)((unsigned long)context_ptr+0x000061dc+4*27))=0x00000093;
*((unsigned int *)((unsigned long)context_ptr+0x00003a20))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003a20+4*1))=0x00006460;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000a20+4*1))=0x000061dc;
*((unsigned int *)((unsigned long)context_ptr+0x00000a20+4*2))=0x0000604c;
*((unsigned int *)((unsigned long)context_ptr+0x00000a20+4*3))=0x0222006d;
*((unsigned int *)((unsigned long)context_ptr+0x00000a20+4*4))=0x04f04714;
*((unsigned int *)((unsigned long)context_ptr+0x00000a20+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000023a&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000065b8,"\xfd\x0b\x56\xac\x76\xbf\xd6\x18\x7e\xf7\x05\x90\x90\x3c\x17\xfa\x97\xe7\x88\xc1",20))
printf("strip: fd0b56ac76bfd618, Pass\n");
else
printf("strip: fd0b56ac76bfd618, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006070))=0x010a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006070+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006070+4*2))=0x0202006e;
*((unsigned int *)((unsigned long)context_ptr+0x00006070+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x0000650c))=0x5b7c6f3d;
*((unsigned int *)((unsigned long)context_ptr+0x0000650c+4*1))=0x1e84b054;
*((unsigned int *)((unsigned long)context_ptr+0x0000650c+4*2))=0x1f31b45b;
*((unsigned int *)((unsigned long)context_ptr+0x0000650c+4*3))=0x4105aa35;
*((unsigned int *)((unsigned long)context_ptr+0x0000650c+4*4))=0x6ef4b2db;
*((unsigned int *)((unsigned long)context_ptr+0x0000650c+4*5))=0xe4cebf1f;
*((unsigned int *)((unsigned long)context_ptr+0x0000650c+4*6))=0x770019af;
*((unsigned int *)((unsigned long)context_ptr+0x0000650c+4*7))=0xee1f29c8;
*((unsigned int *)((unsigned long)context_ptr+0x0000650c+4*8))=0xe7716dbd;
*((unsigned int *)((unsigned long)context_ptr+0x0000650c+4*9))=0x9b8f08be;
*((unsigned int *)((unsigned long)context_ptr+0x0000650c+4*10))=0x9093b34d;
*((unsigned int *)((unsigned long)context_ptr+0x0000650c+4*11))=0x054e62ae;
*((unsigned int *)((unsigned long)context_ptr+0x0000650c+4*12))=0x42cddbb8;
*((unsigned int *)((unsigned long)context_ptr+0x0000650c+4*13))=0xa54ceabd;
*((unsigned int *)((unsigned long)context_ptr+0x0000650c+4*14))=0xc24728bf;
*((unsigned int *)((unsigned long)context_ptr+0x0000650c+4*15))=0x290c2ea2;
*((unsigned int *)((unsigned long)context_ptr+0x0000650c+4*16))=0xd052be32;
*((unsigned int *)((unsigned long)context_ptr+0x0000650c+4*17))=0x03dd4042;
*((unsigned int *)((unsigned long)context_ptr+0x0000650c+4*18))=0xac7cea4b;
*((unsigned int *)((unsigned long)context_ptr+0x0000650c+4*19))=0xa3baf79a;
*((unsigned int *)((unsigned long)context_ptr+0x0000650c+4*20))=0x4d9a034d;
*((unsigned int *)((unsigned long)context_ptr+0x0000650c+4*21))=0xc1c0d6c2;
*((unsigned int *)((unsigned long)context_ptr+0x0000650c+4*22))=0xeb77a6f3;
*((unsigned int *)((unsigned long)context_ptr+0x0000650c+4*23))=0x25234784;
*((unsigned int *)((unsigned long)context_ptr+0x0000650c+4*24))=0x962b2d19;
*((unsigned int *)((unsigned long)context_ptr+0x0000650c+4*25))=0xa043f804;
*((unsigned int *)((unsigned long)context_ptr+0x0000650c+4*26))=0xa7ee83f0;
*((unsigned int *)((unsigned long)context_ptr+0x0000650c+4*27))=0x0000fcad;
*((unsigned int *)((unsigned long)context_ptr+0x00003a38))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003a38+4*1))=0x0000624c;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000a38+4*1))=0x0000650c;
*((unsigned int *)((unsigned long)context_ptr+0x00000a38+4*2))=0x00006070;
*((unsigned int *)((unsigned long)context_ptr+0x00000a38+4*3))=0x0222006e;
*((unsigned int *)((unsigned long)context_ptr+0x00000a38+4*4))=0x0927df48;
*((unsigned int *)((unsigned long)context_ptr+0x00000a38+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000240&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006710,"\x38\x97\xa5\x20\x8c\x87\x96\x23\x16\xcd\x3b\x25\x10\x7f\xa5\x87\xf4\x1a\xea\xbc",20))
printf("strip: 3897a5208c879623, Pass\n");
else
printf("strip: 3897a5208c879623, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x0000657c))=0x010a0012;
*((unsigned int *)((unsigned long)context_ptr+0x0000657c+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x0000657c+4*2))=0x0202006f;
*((unsigned int *)((unsigned long)context_ptr+0x0000657c+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x000066ac))=0x8a77db66;
*((unsigned int *)((unsigned long)context_ptr+0x000066ac+4*1))=0x9d9abc00;
*((unsigned int *)((unsigned long)context_ptr+0x000066ac+4*2))=0xffdfccaf;
*((unsigned int *)((unsigned long)context_ptr+0x000066ac+4*3))=0x37238fa9;
*((unsigned int *)((unsigned long)context_ptr+0x000066ac+4*4))=0xead897fb;
*((unsigned int *)((unsigned long)context_ptr+0x000066ac+4*5))=0xad51787c;
*((unsigned int *)((unsigned long)context_ptr+0x000066ac+4*6))=0xa41cd3f1;
*((unsigned int *)((unsigned long)context_ptr+0x000066ac+4*7))=0xfa197161;
*((unsigned int *)((unsigned long)context_ptr+0x000066ac+4*8))=0xd4c56373;
*((unsigned int *)((unsigned long)context_ptr+0x000066ac+4*9))=0xa43f6aa8;
*((unsigned int *)((unsigned long)context_ptr+0x000066ac+4*10))=0xe11dae58;
*((unsigned int *)((unsigned long)context_ptr+0x000066ac+4*11))=0x5153bbe1;
*((unsigned int *)((unsigned long)context_ptr+0x000066ac+4*12))=0x71b04b96;
*((unsigned int *)((unsigned long)context_ptr+0x000066ac+4*13))=0x7edb0348;
*((unsigned int *)((unsigned long)context_ptr+0x000066ac+4*14))=0x8ac07902;
*((unsigned int *)((unsigned long)context_ptr+0x000066ac+4*15))=0xa56e6462;
*((unsigned int *)((unsigned long)context_ptr+0x000066ac+4*16))=0xee1ecefa;
*((unsigned int *)((unsigned long)context_ptr+0x000066ac+4*17))=0x95f9654b;
*((unsigned int *)((unsigned long)context_ptr+0x000066ac+4*18))=0x2eeae00b;
*((unsigned int *)((unsigned long)context_ptr+0x000066ac+4*19))=0x4cfee03f;
*((unsigned int *)((unsigned long)context_ptr+0x000066ac+4*20))=0xbcfce445;
*((unsigned int *)((unsigned long)context_ptr+0x000066ac+4*21))=0xc3f85b25;
*((unsigned int *)((unsigned long)context_ptr+0x000066ac+4*22))=0x3e6e8251;
*((unsigned int *)((unsigned long)context_ptr+0x000066ac+4*23))=0x0e6506a3;
*((unsigned int *)((unsigned long)context_ptr+0x000066ac+4*24))=0xd0f8d3f1;
*((unsigned int *)((unsigned long)context_ptr+0x000066ac+4*25))=0x187272a0;
*((unsigned int *)((unsigned long)context_ptr+0x000066ac+4*26))=0xf85f4226;
*((unsigned int *)((unsigned long)context_ptr+0x000066ac+4*27))=0x00612737;
*((unsigned int *)((unsigned long)context_ptr+0x00003a50))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003a50+4*1))=0x0000658c;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000a50+4*1))=0x000066ac;
*((unsigned int *)((unsigned long)context_ptr+0x00000a50+4*2))=0x0000657c;
*((unsigned int *)((unsigned long)context_ptr+0x00000a50+4*3))=0x0222006f;
*((unsigned int *)((unsigned long)context_ptr+0x00000a50+4*4))=0x0634d133;
*((unsigned int *)((unsigned long)context_ptr+0x00000a50+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000246&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000063b0,"\x45\xd8\xdc\x65\x73\x62\x9e\xed\xbd\xfe\xeb\x9d\x5f\x52\x5a\xb9\x60\x8b\x3d\x42",20))
printf("strip: 45d8dc6573629eed, Pass\n");
else
printf("strip: 45d8dc6573629eed, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000063a8))=0x010a0012;
*((unsigned int *)((unsigned long)context_ptr+0x000063a8+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000063a8+4*2))=0x02020070;
*((unsigned int *)((unsigned long)context_ptr+0x000063a8+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x000065a0))=0x4afe1856;
*((unsigned int *)((unsigned long)context_ptr+0x000065a0+4*1))=0xf32ad774;
*((unsigned int *)((unsigned long)context_ptr+0x000065a0+4*2))=0xa9fe2bb9;
*((unsigned int *)((unsigned long)context_ptr+0x000065a0+4*3))=0x6306a335;
*((unsigned int *)((unsigned long)context_ptr+0x000065a0+4*4))=0x825de32c;
*((unsigned int *)((unsigned long)context_ptr+0x000065a0+4*5))=0x8930c2f0;
*((unsigned int *)((unsigned long)context_ptr+0x000065a0+4*6))=0xeaee9f69;
*((unsigned int *)((unsigned long)context_ptr+0x000065a0+4*7))=0xab9403b2;
*((unsigned int *)((unsigned long)context_ptr+0x000065a0+4*8))=0x5a6100ca;
*((unsigned int *)((unsigned long)context_ptr+0x000065a0+4*9))=0xa22240a4;
*((unsigned int *)((unsigned long)context_ptr+0x000065a0+4*10))=0xfa11425e;
*((unsigned int *)((unsigned long)context_ptr+0x000065a0+4*11))=0x054c40a4;
*((unsigned int *)((unsigned long)context_ptr+0x000065a0+4*12))=0xe32861c9;
*((unsigned int *)((unsigned long)context_ptr+0x000065a0+4*13))=0xc3c81c33;
*((unsigned int *)((unsigned long)context_ptr+0x000065a0+4*14))=0x1ab43009;
*((unsigned int *)((unsigned long)context_ptr+0x000065a0+4*15))=0xdc54a9bb;
*((unsigned int *)((unsigned long)context_ptr+0x000065a0+4*16))=0x0cd518ea;
*((unsigned int *)((unsigned long)context_ptr+0x000065a0+4*17))=0x3a208eac;
*((unsigned int *)((unsigned long)context_ptr+0x000065a0+4*18))=0x2a3c2b10;
*((unsigned int *)((unsigned long)context_ptr+0x000065a0+4*19))=0xe58c438c;
*((unsigned int *)((unsigned long)context_ptr+0x000065a0+4*20))=0xb92132af;
*((unsigned int *)((unsigned long)context_ptr+0x000065a0+4*21))=0x9ee8d43b;
*((unsigned int *)((unsigned long)context_ptr+0x000065a0+4*22))=0x19944148;
*((unsigned int *)((unsigned long)context_ptr+0x000065a0+4*23))=0xac92d56a;
*((unsigned int *)((unsigned long)context_ptr+0x000065a0+4*24))=0x8c9a2288;
*((unsigned int *)((unsigned long)context_ptr+0x000065a0+4*25))=0xfaf783fc;
*((unsigned int *)((unsigned long)context_ptr+0x000065a0+4*26))=0xc8d58b3b;
*((unsigned int *)((unsigned long)context_ptr+0x000065a0+4*27))=0x8d1ffb6e;
*((unsigned int *)((unsigned long)context_ptr+0x00003a68))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003a68+4*1))=0x00006610;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000a68+4*1))=0x000065a0;
*((unsigned int *)((unsigned long)context_ptr+0x00000a68+4*2))=0x000063a8;
*((unsigned int *)((unsigned long)context_ptr+0x00000a68+4*3))=0x02220070;
*((unsigned int *)((unsigned long)context_ptr+0x00000a68+4*4))=0x00ad8dc0;
*((unsigned int *)((unsigned long)context_ptr+0x00000a68+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000024c&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006308,"\x61\x27\x4f\x98\x20\xa8\x37\x2b\x6a\x5e\xe5\xd0\x38\x4d\x87\x44\xa6\x26\xdc\xfd",20))
printf("strip: 61274f9820a8372b, Pass\n");
else
printf("strip: 61274f9820a8372b, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006624))=0x010a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006624+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006624+4*2))=0x02020071;
*((unsigned int *)((unsigned long)context_ptr+0x00006624+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x00006790))=0x94074384;
*((unsigned int *)((unsigned long)context_ptr+0x00006790+4*1))=0x72764791;
*((unsigned int *)((unsigned long)context_ptr+0x00006790+4*2))=0xebe354e7;
*((unsigned int *)((unsigned long)context_ptr+0x00006790+4*3))=0x7e97ed1e;
*((unsigned int *)((unsigned long)context_ptr+0x00006790+4*4))=0x4f075893;
*((unsigned int *)((unsigned long)context_ptr+0x00006790+4*5))=0xdfd41397;
*((unsigned int *)((unsigned long)context_ptr+0x00006790+4*6))=0xd4b74270;
*((unsigned int *)((unsigned long)context_ptr+0x00006790+4*7))=0x1ec952a9;
*((unsigned int *)((unsigned long)context_ptr+0x00006790+4*8))=0xa00b6956;
*((unsigned int *)((unsigned long)context_ptr+0x00006790+4*9))=0xc4a069c8;
*((unsigned int *)((unsigned long)context_ptr+0x00006790+4*10))=0xef40f5c2;
*((unsigned int *)((unsigned long)context_ptr+0x00006790+4*11))=0xeb5bc58a;
*((unsigned int *)((unsigned long)context_ptr+0x00006790+4*12))=0xee07ce62;
*((unsigned int *)((unsigned long)context_ptr+0x00006790+4*13))=0x7c65d35c;
*((unsigned int *)((unsigned long)context_ptr+0x00006790+4*14))=0xe2ed0336;
*((unsigned int *)((unsigned long)context_ptr+0x00006790+4*15))=0x5cea9541;
*((unsigned int *)((unsigned long)context_ptr+0x00006790+4*16))=0x9e849399;
*((unsigned int *)((unsigned long)context_ptr+0x00006790+4*17))=0xb74b1c1d;
*((unsigned int *)((unsigned long)context_ptr+0x00006790+4*18))=0x79cb0063;
*((unsigned int *)((unsigned long)context_ptr+0x00006790+4*19))=0x09c9b062;
*((unsigned int *)((unsigned long)context_ptr+0x00006790+4*20))=0x87ba2a38;
*((unsigned int *)((unsigned long)context_ptr+0x00006790+4*21))=0x03578f2d;
*((unsigned int *)((unsigned long)context_ptr+0x00006790+4*22))=0xb2efeeef;
*((unsigned int *)((unsigned long)context_ptr+0x00006790+4*23))=0x10af28cd;
*((unsigned int *)((unsigned long)context_ptr+0x00006790+4*24))=0xf582bb55;
*((unsigned int *)((unsigned long)context_ptr+0x00006790+4*25))=0xec63ab4a;
*((unsigned int *)((unsigned long)context_ptr+0x00006790+4*26))=0x88605584;
*((unsigned int *)((unsigned long)context_ptr+0x00006790+4*27))=0x709465f2;
*((unsigned int *)((unsigned long)context_ptr+0x00006790+4*28))=0x00000091;
*((unsigned int *)((unsigned long)context_ptr+0x00003a80))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003a80+4*1))=0x00006804;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000a80+4*1))=0x00006790;
*((unsigned int *)((unsigned long)context_ptr+0x00000a80+4*2))=0x00006624;
*((unsigned int *)((unsigned long)context_ptr+0x00000a80+4*3))=0x02220071;
*((unsigned int *)((unsigned long)context_ptr+0x00000a80+4*4))=0x0bef9b34;
*((unsigned int *)((unsigned long)context_ptr+0x00000a80+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000252&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006080,"\x1d\x52\xd2\x7e\x98\x2d\xf3\xff\x32\x56\x4c\xf9\xb4\xa8\xbc\x31\x02\xa6\xfb\x80",20))
printf("strip: 1d52d27e982df3ff, Pass\n");
else
printf("strip: 1d52d27e982df3ff, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006080))=0x010a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006080+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006080+4*2))=0x02020072;
*((unsigned int *)((unsigned long)context_ptr+0x00006080+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x00006818))=0x6d159cf9;
*((unsigned int *)((unsigned long)context_ptr+0x00006818+4*1))=0x2b4a3be4;
*((unsigned int *)((unsigned long)context_ptr+0x00006818+4*2))=0x47cb593b;
*((unsigned int *)((unsigned long)context_ptr+0x00006818+4*3))=0xe2608f68;
*((unsigned int *)((unsigned long)context_ptr+0x00006818+4*4))=0x9000ec93;
*((unsigned int *)((unsigned long)context_ptr+0x00006818+4*5))=0xc5338530;
*((unsigned int *)((unsigned long)context_ptr+0x00006818+4*6))=0x9b843721;
*((unsigned int *)((unsigned long)context_ptr+0x00006818+4*7))=0x07b508b5;
*((unsigned int *)((unsigned long)context_ptr+0x00006818+4*8))=0x61002732;
*((unsigned int *)((unsigned long)context_ptr+0x00006818+4*9))=0xa3120658;
*((unsigned int *)((unsigned long)context_ptr+0x00006818+4*10))=0x2bfbd80a;
*((unsigned int *)((unsigned long)context_ptr+0x00006818+4*11))=0x5fb94323;
*((unsigned int *)((unsigned long)context_ptr+0x00006818+4*12))=0x0a523b6e;
*((unsigned int *)((unsigned long)context_ptr+0x00006818+4*13))=0x559a46b6;
*((unsigned int *)((unsigned long)context_ptr+0x00006818+4*14))=0x204dbb92;
*((unsigned int *)((unsigned long)context_ptr+0x00006818+4*15))=0x0c3ffeba;
*((unsigned int *)((unsigned long)context_ptr+0x00006818+4*16))=0x22ea5eb4;
*((unsigned int *)((unsigned long)context_ptr+0x00006818+4*17))=0x78fa8225;
*((unsigned int *)((unsigned long)context_ptr+0x00006818+4*18))=0xffe52d68;
*((unsigned int *)((unsigned long)context_ptr+0x00006818+4*19))=0x9dcd8023;
*((unsigned int *)((unsigned long)context_ptr+0x00006818+4*20))=0x2487cf39;
*((unsigned int *)((unsigned long)context_ptr+0x00006818+4*21))=0xe0493dc6;
*((unsigned int *)((unsigned long)context_ptr+0x00006818+4*22))=0xb1e6af93;
*((unsigned int *)((unsigned long)context_ptr+0x00006818+4*23))=0x92b279d0;
*((unsigned int *)((unsigned long)context_ptr+0x00006818+4*24))=0x524523be;
*((unsigned int *)((unsigned long)context_ptr+0x00006818+4*25))=0x4d0435c8;
*((unsigned int *)((unsigned long)context_ptr+0x00006818+4*26))=0xd7dc9886;
*((unsigned int *)((unsigned long)context_ptr+0x00006818+4*27))=0x33573788;
*((unsigned int *)((unsigned long)context_ptr+0x00006818+4*28))=0x00003cae;
*((unsigned int *)((unsigned long)context_ptr+0x00003a98))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003a98+4*1))=0x0000688c;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000a98+4*1))=0x00006818;
*((unsigned int *)((unsigned long)context_ptr+0x00000a98+4*2))=0x00006080;
*((unsigned int *)((unsigned long)context_ptr+0x00000a98+4*3))=0x02220072;
*((unsigned int *)((unsigned long)context_ptr+0x00000a98+4*4))=0x047faf14;
*((unsigned int *)((unsigned long)context_ptr+0x00000a98+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000258&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x0000647c,"\xfe\xa7\x91\xaa\xc7\xff\xda\x1a\x3f\xb5\xe7\xbe\x81\xd6\xb0\x3b\xdd\x6f\x38\xe1",20))
printf("strip: fea791aac7ffda1a, Pass\n");
else
printf("strip: fea791aac7ffda1a, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006474))=0x010a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006474+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006474+4*2))=0x02020073;
*((unsigned int *)((unsigned long)context_ptr+0x00006474+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x00006260))=0x61e63a05;
*((unsigned int *)((unsigned long)context_ptr+0x00006260+4*1))=0x29e2f27d;
*((unsigned int *)((unsigned long)context_ptr+0x00006260+4*2))=0x10ffbff7;
*((unsigned int *)((unsigned long)context_ptr+0x00006260+4*3))=0x079ef2f5;
*((unsigned int *)((unsigned long)context_ptr+0x00006260+4*4))=0xe5866614;
*((unsigned int *)((unsigned long)context_ptr+0x00006260+4*5))=0x2755f119;
*((unsigned int *)((unsigned long)context_ptr+0x00006260+4*6))=0x9da99c86;
*((unsigned int *)((unsigned long)context_ptr+0x00006260+4*7))=0xf5b7c0c7;
*((unsigned int *)((unsigned long)context_ptr+0x00006260+4*8))=0x51216a43;
*((unsigned int *)((unsigned long)context_ptr+0x00006260+4*9))=0x991a4a39;
*((unsigned int *)((unsigned long)context_ptr+0x00006260+4*10))=0xaf3b8256;
*((unsigned int *)((unsigned long)context_ptr+0x00006260+4*11))=0x5f6ef8ab;
*((unsigned int *)((unsigned long)context_ptr+0x00006260+4*12))=0xdca87a08;
*((unsigned int *)((unsigned long)context_ptr+0x00006260+4*13))=0x3dbf69e7;
*((unsigned int *)((unsigned long)context_ptr+0x00006260+4*14))=0x52cc3ef9;
*((unsigned int *)((unsigned long)context_ptr+0x00006260+4*15))=0x672f4d42;
*((unsigned int *)((unsigned long)context_ptr+0x00006260+4*16))=0x0c68224a;
*((unsigned int *)((unsigned long)context_ptr+0x00006260+4*17))=0x9e21a5e4;
*((unsigned int *)((unsigned long)context_ptr+0x00006260+4*18))=0x2f085b36;
*((unsigned int *)((unsigned long)context_ptr+0x00006260+4*19))=0x12c8f800;
*((unsigned int *)((unsigned long)context_ptr+0x00006260+4*20))=0xd045cd91;
*((unsigned int *)((unsigned long)context_ptr+0x00006260+4*21))=0x8f37638b;
*((unsigned int *)((unsigned long)context_ptr+0x00006260+4*22))=0xbb3a48aa;
*((unsigned int *)((unsigned long)context_ptr+0x00006260+4*23))=0x3b02864e;
*((unsigned int *)((unsigned long)context_ptr+0x00006260+4*24))=0xf72be13d;
*((unsigned int *)((unsigned long)context_ptr+0x00006260+4*25))=0xd63a1b35;
*((unsigned int *)((unsigned long)context_ptr+0x00006260+4*26))=0xa3b02769;
*((unsigned int *)((unsigned long)context_ptr+0x00006260+4*27))=0x67afb732;
*((unsigned int *)((unsigned long)context_ptr+0x00006260+4*28))=0x003aef46;
*((unsigned int *)((unsigned long)context_ptr+0x00003ab0))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003ab0+4*1))=0x000062d4;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000ab0+4*1))=0x00006260;
*((unsigned int *)((unsigned long)context_ptr+0x00000ab0+4*2))=0x00006474;
*((unsigned int *)((unsigned long)context_ptr+0x00000ab0+4*3))=0x02220073;
*((unsigned int *)((unsigned long)context_ptr+0x00000ab0+4*4))=0x05034e9e;
*((unsigned int *)((unsigned long)context_ptr+0x00000ab0+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000025e&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006428,"\xea\x1f\xdd\xa7\xb4\x9b\x67\xac\x98\xa8\x58\xca\x78\x56\x7c\xf4\xac\xc7\x7d\x22",20))
printf("strip: ea1fdda7b49b67ac, Pass\n");
else
printf("strip: ea1fdda7b49b67ac, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000062e8))=0x010a0012;
*((unsigned int *)((unsigned long)context_ptr+0x000062e8+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000062e8+4*2))=0x02020074;
*((unsigned int *)((unsigned long)context_ptr+0x000062e8+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x000063b8))=0x8b3670fa;
*((unsigned int *)((unsigned long)context_ptr+0x000063b8+4*1))=0x3e922cdd;
*((unsigned int *)((unsigned long)context_ptr+0x000063b8+4*2))=0x02f5a65a;
*((unsigned int *)((unsigned long)context_ptr+0x000063b8+4*3))=0x77a7df0e;
*((unsigned int *)((unsigned long)context_ptr+0x000063b8+4*4))=0xdd6b143e;
*((unsigned int *)((unsigned long)context_ptr+0x000063b8+4*5))=0x67a15bdc;
*((unsigned int *)((unsigned long)context_ptr+0x000063b8+4*6))=0x117e3b10;
*((unsigned int *)((unsigned long)context_ptr+0x000063b8+4*7))=0x5c96e513;
*((unsigned int *)((unsigned long)context_ptr+0x000063b8+4*8))=0xd71539f2;
*((unsigned int *)((unsigned long)context_ptr+0x000063b8+4*9))=0xdd13edc5;
*((unsigned int *)((unsigned long)context_ptr+0x000063b8+4*10))=0x547ce0f0;
*((unsigned int *)((unsigned long)context_ptr+0x000063b8+4*11))=0x4fd249d0;
*((unsigned int *)((unsigned long)context_ptr+0x000063b8+4*12))=0xb5d6de30;
*((unsigned int *)((unsigned long)context_ptr+0x000063b8+4*13))=0x9cd878e7;
*((unsigned int *)((unsigned long)context_ptr+0x000063b8+4*14))=0xc9dc7008;
*((unsigned int *)((unsigned long)context_ptr+0x000063b8+4*15))=0x41e853d7;
*((unsigned int *)((unsigned long)context_ptr+0x000063b8+4*16))=0xcf0d1730;
*((unsigned int *)((unsigned long)context_ptr+0x000063b8+4*17))=0x6a936cac;
*((unsigned int *)((unsigned long)context_ptr+0x000063b8+4*18))=0x613aa6e6;
*((unsigned int *)((unsigned long)context_ptr+0x000063b8+4*19))=0x41b793b0;
*((unsigned int *)((unsigned long)context_ptr+0x000063b8+4*20))=0x44fe370b;
*((unsigned int *)((unsigned long)context_ptr+0x000063b8+4*21))=0x2284a7e6;
*((unsigned int *)((unsigned long)context_ptr+0x000063b8+4*22))=0x2ab09992;
*((unsigned int *)((unsigned long)context_ptr+0x000063b8+4*23))=0x94d9d77d;
*((unsigned int *)((unsigned long)context_ptr+0x000063b8+4*24))=0xb4e7a35e;
*((unsigned int *)((unsigned long)context_ptr+0x000063b8+4*25))=0x0c551f87;
*((unsigned int *)((unsigned long)context_ptr+0x000063b8+4*26))=0x8547ed9f;
*((unsigned int *)((unsigned long)context_ptr+0x000063b8+4*27))=0x2505479d;
*((unsigned int *)((unsigned long)context_ptr+0x000063b8+4*28))=0xac3d1f0c;
*((unsigned int *)((unsigned long)context_ptr+0x00003ac8))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003ac8+4*1))=0x000062f8;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000ac8+4*1))=0x000063b8;
*((unsigned int *)((unsigned long)context_ptr+0x00000ac8+4*2))=0x000062e8;
*((unsigned int *)((unsigned long)context_ptr+0x00000ac8+4*3))=0x02220074;
*((unsigned int *)((unsigned long)context_ptr+0x00000ac8+4*4))=0x0b9641b1;
*((unsigned int *)((unsigned long)context_ptr+0x00000ac8+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000264&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006490,"\xba\x3b\x78\xa3\x1c\x70\xe5\x80\xa0\x8f\x94\x82\xb9\x54\x7f\x54\x67\xd9\x87\xe1",20))
printf("strip: ba3b78a31c70e580, Pass\n");
else
printf("strip: ba3b78a31c70e580, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x0000642c))=0x010a0012;
*((unsigned int *)((unsigned long)context_ptr+0x0000642c+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x0000642c+4*2))=0x02020075;
*((unsigned int *)((unsigned long)context_ptr+0x0000642c+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x00006090))=0x9d24c9ed;
*((unsigned int *)((unsigned long)context_ptr+0x00006090+4*1))=0x24f2af2b;
*((unsigned int *)((unsigned long)context_ptr+0x00006090+4*2))=0xa9518e20;
*((unsigned int *)((unsigned long)context_ptr+0x00006090+4*3))=0xfd2ab048;
*((unsigned int *)((unsigned long)context_ptr+0x00006090+4*4))=0xdef9fa77;
*((unsigned int *)((unsigned long)context_ptr+0x00006090+4*5))=0xae6d8568;
*((unsigned int *)((unsigned long)context_ptr+0x00006090+4*6))=0x33e46a4e;
*((unsigned int *)((unsigned long)context_ptr+0x00006090+4*7))=0xdf823a6c;
*((unsigned int *)((unsigned long)context_ptr+0x00006090+4*8))=0x6008b4a1;
*((unsigned int *)((unsigned long)context_ptr+0x00006090+4*9))=0x003d5a3c;
*((unsigned int *)((unsigned long)context_ptr+0x00006090+4*10))=0x9945ab6f;
*((unsigned int *)((unsigned long)context_ptr+0x00006090+4*11))=0x75b0e468;
*((unsigned int *)((unsigned long)context_ptr+0x00006090+4*12))=0xbf8e80be;
*((unsigned int *)((unsigned long)context_ptr+0x00006090+4*13))=0xb7c8799f;
*((unsigned int *)((unsigned long)context_ptr+0x00006090+4*14))=0x1e021eb3;
*((unsigned int *)((unsigned long)context_ptr+0x00006090+4*15))=0x255f74bb;
*((unsigned int *)((unsigned long)context_ptr+0x00006090+4*16))=0x62796387;
*((unsigned int *)((unsigned long)context_ptr+0x00006090+4*17))=0x09053681;
*((unsigned int *)((unsigned long)context_ptr+0x00006090+4*18))=0xb4f17fd2;
*((unsigned int *)((unsigned long)context_ptr+0x00006090+4*19))=0xd23c0597;
*((unsigned int *)((unsigned long)context_ptr+0x00006090+4*20))=0xb799c6f0;
*((unsigned int *)((unsigned long)context_ptr+0x00006090+4*21))=0xd03d8ce8;
*((unsigned int *)((unsigned long)context_ptr+0x00006090+4*22))=0x5dd95db1;
*((unsigned int *)((unsigned long)context_ptr+0x00006090+4*23))=0xcd676f57;
*((unsigned int *)((unsigned long)context_ptr+0x00006090+4*24))=0x946cfe04;
*((unsigned int *)((unsigned long)context_ptr+0x00006090+4*25))=0x5419d4e1;
*((unsigned int *)((unsigned long)context_ptr+0x00006090+4*26))=0xe991245b;
*((unsigned int *)((unsigned long)context_ptr+0x00006090+4*27))=0x4a78eadb;
*((unsigned int *)((unsigned long)context_ptr+0x00006090+4*28))=0x4c9eb058;
*((unsigned int *)((unsigned long)context_ptr+0x00006090+4*29))=0x00000003;
*((unsigned int *)((unsigned long)context_ptr+0x00003ae0))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003ae0+4*1))=0x00006484;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000ae0+4*1))=0x00006090;
*((unsigned int *)((unsigned long)context_ptr+0x00000ae0+4*2))=0x0000642c;
*((unsigned int *)((unsigned long)context_ptr+0x00000ae0+4*3))=0x02220075;
*((unsigned int *)((unsigned long)context_ptr+0x00000ae0+4*4))=0x0fff4540;
*((unsigned int *)((unsigned long)context_ptr+0x00000ae0+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000026a&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x0000644c,"\xa9\x2f\x87\x81\x24\x96\x8f\xd6\x87\x9c\x7f\x8a\xa3\xf0\xff\x11\xb3\x7b\x89\xec",20))
printf("strip: a92f878124968fd6, Pass\n");
else
printf("strip: a92f878124968fd6, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x0000643c))=0x010a0012;
*((unsigned int *)((unsigned long)context_ptr+0x0000643c+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x0000643c+4*2))=0x02020076;
*((unsigned int *)((unsigned long)context_ptr+0x0000643c+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x00006108))=0x9b7c7019;
*((unsigned int *)((unsigned long)context_ptr+0x00006108+4*1))=0x8edeedf2;
*((unsigned int *)((unsigned long)context_ptr+0x00006108+4*2))=0xc825c9c7;
*((unsigned int *)((unsigned long)context_ptr+0x00006108+4*3))=0xbd178865;
*((unsigned int *)((unsigned long)context_ptr+0x00006108+4*4))=0xa300585a;
*((unsigned int *)((unsigned long)context_ptr+0x00006108+4*5))=0xd091bf99;
*((unsigned int *)((unsigned long)context_ptr+0x00006108+4*6))=0xc0ce85e7;
*((unsigned int *)((unsigned long)context_ptr+0x00006108+4*7))=0x324f416a;
*((unsigned int *)((unsigned long)context_ptr+0x00006108+4*8))=0xe21bebfa;
*((unsigned int *)((unsigned long)context_ptr+0x00006108+4*9))=0x231c7eb9;
*((unsigned int *)((unsigned long)context_ptr+0x00006108+4*10))=0x430585f6;
*((unsigned int *)((unsigned long)context_ptr+0x00006108+4*11))=0xbddb640d;
*((unsigned int *)((unsigned long)context_ptr+0x00006108+4*12))=0x4f558362;
*((unsigned int *)((unsigned long)context_ptr+0x00006108+4*13))=0xb7ca8548;
*((unsigned int *)((unsigned long)context_ptr+0x00006108+4*14))=0x742a9f27;
*((unsigned int *)((unsigned long)context_ptr+0x00006108+4*15))=0x691fb8d0;
*((unsigned int *)((unsigned long)context_ptr+0x00006108+4*16))=0x5a5a8adc;
*((unsigned int *)((unsigned long)context_ptr+0x00006108+4*17))=0xcdb7216e;
*((unsigned int *)((unsigned long)context_ptr+0x00006108+4*18))=0x5de42198;
*((unsigned int *)((unsigned long)context_ptr+0x00006108+4*19))=0xb05cf8f9;
*((unsigned int *)((unsigned long)context_ptr+0x00006108+4*20))=0x922fd1e0;
*((unsigned int *)((unsigned long)context_ptr+0x00006108+4*21))=0x600dd4cb;
*((unsigned int *)((unsigned long)context_ptr+0x00006108+4*22))=0x1a1a9ca5;
*((unsigned int *)((unsigned long)context_ptr+0x00006108+4*23))=0xb641daeb;
*((unsigned int *)((unsigned long)context_ptr+0x00006108+4*24))=0x74ec2077;
*((unsigned int *)((unsigned long)context_ptr+0x00006108+4*25))=0x05f8571a;
*((unsigned int *)((unsigned long)context_ptr+0x00006108+4*26))=0x2d94a68f;
*((unsigned int *)((unsigned long)context_ptr+0x00006108+4*27))=0x6e20baf1;
*((unsigned int *)((unsigned long)context_ptr+0x00006108+4*28))=0x3a419bb6;
*((unsigned int *)((unsigned long)context_ptr+0x00006108+4*29))=0x0000ec3b;
*((unsigned int *)((unsigned long)context_ptr+0x00003af8))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003af8+4*1))=0x0000644c;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000af8+4*1))=0x00006108;
*((unsigned int *)((unsigned long)context_ptr+0x00000af8+4*2))=0x0000643c;
*((unsigned int *)((unsigned long)context_ptr+0x00000af8+4*3))=0x02220076;
*((unsigned int *)((unsigned long)context_ptr+0x00000af8+4*4))=0x0f17ca75;
*((unsigned int *)((unsigned long)context_ptr+0x00000af8+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000270&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x0000635c,"\x09\x42\x55\x16\xa6\xa5\x5b\xbf\x0d\xf6\x82\x16\x59\x94\xde\x1f\xa3\x67\xc7\xa8",20))
printf("strip: 09425516a6a55bbf, Pass\n");
else
printf("strip: 09425516a6a55bbf, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006180))=0x010a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006180+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006180+4*2))=0x02020077;
*((unsigned int *)((unsigned long)context_ptr+0x00006180+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x00006984))=0x9eba4e9e;
*((unsigned int *)((unsigned long)context_ptr+0x00006984+4*1))=0xe62101f0;
*((unsigned int *)((unsigned long)context_ptr+0x00006984+4*2))=0xa764bc5b;
*((unsigned int *)((unsigned long)context_ptr+0x00006984+4*3))=0x97dc0e45;
*((unsigned int *)((unsigned long)context_ptr+0x00006984+4*4))=0x11c44eb6;
*((unsigned int *)((unsigned long)context_ptr+0x00006984+4*5))=0x09c2fffc;
*((unsigned int *)((unsigned long)context_ptr+0x00006984+4*6))=0xa0641905;
*((unsigned int *)((unsigned long)context_ptr+0x00006984+4*7))=0xbb0a7e7f;
*((unsigned int *)((unsigned long)context_ptr+0x00006984+4*8))=0x879577a7;
*((unsigned int *)((unsigned long)context_ptr+0x00006984+4*9))=0x61afbeb5;
*((unsigned int *)((unsigned long)context_ptr+0x00006984+4*10))=0x0453900c;
*((unsigned int *)((unsigned long)context_ptr+0x00006984+4*11))=0x7595206e;
*((unsigned int *)((unsigned long)context_ptr+0x00006984+4*12))=0xe96bfcce;
*((unsigned int *)((unsigned long)context_ptr+0x00006984+4*13))=0x8a5d82fb;
*((unsigned int *)((unsigned long)context_ptr+0x00006984+4*14))=0x065737f9;
*((unsigned int *)((unsigned long)context_ptr+0x00006984+4*15))=0xd7267ce5;
*((unsigned int *)((unsigned long)context_ptr+0x00006984+4*16))=0x2241fe7d;
*((unsigned int *)((unsigned long)context_ptr+0x00006984+4*17))=0x52c991f5;
*((unsigned int *)((unsigned long)context_ptr+0x00006984+4*18))=0x1b8efa40;
*((unsigned int *)((unsigned long)context_ptr+0x00006984+4*19))=0x6583b9aa;
*((unsigned int *)((unsigned long)context_ptr+0x00006984+4*20))=0xcfc8247f;
*((unsigned int *)((unsigned long)context_ptr+0x00006984+4*21))=0xd90e0ba5;
*((unsigned int *)((unsigned long)context_ptr+0x00006984+4*22))=0xc31cc0ea;
*((unsigned int *)((unsigned long)context_ptr+0x00006984+4*23))=0x638d843b;
*((unsigned int *)((unsigned long)context_ptr+0x00006984+4*24))=0x69cc0557;
*((unsigned int *)((unsigned long)context_ptr+0x00006984+4*25))=0x5ce7a353;
*((unsigned int *)((unsigned long)context_ptr+0x00006984+4*26))=0xf93d39df;
*((unsigned int *)((unsigned long)context_ptr+0x00006984+4*27))=0x379177e5;
*((unsigned int *)((unsigned long)context_ptr+0x00006984+4*28))=0xff578dc4;
*((unsigned int *)((unsigned long)context_ptr+0x00006984+4*29))=0x00bce404;
*((unsigned int *)((unsigned long)context_ptr+0x00003b10))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003b10+4*1))=0x00006190;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000b10+4*1))=0x00006984;
*((unsigned int *)((unsigned long)context_ptr+0x00000b10+4*2))=0x00006180;
*((unsigned int *)((unsigned long)context_ptr+0x00000b10+4*3))=0x02220077;
*((unsigned int *)((unsigned long)context_ptr+0x00000b10+4*4))=0x0ea1e773;
*((unsigned int *)((unsigned long)context_ptr+0x00000b10+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000276&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006380,"\xee\x66\x35\xfb\xe9\x74\xd7\x8a\x82\x50\x14\xf5\xdd\x8b\xba\x38\x05\x07\xae\x75",20))
printf("strip: ee6635fbe974d78a, Pass\n");
else
printf("strip: ee6635fbe974d78a, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000061a4))=0x010a0012;
*((unsigned int *)((unsigned long)context_ptr+0x000061a4+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000061a4+4*2))=0x02020078;
*((unsigned int *)((unsigned long)context_ptr+0x000061a4+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x000068a0))=0x2e7c46c7;
*((unsigned int *)((unsigned long)context_ptr+0x000068a0+4*1))=0xcc5bbd8f;
*((unsigned int *)((unsigned long)context_ptr+0x000068a0+4*2))=0x7435495f;
*((unsigned int *)((unsigned long)context_ptr+0x000068a0+4*3))=0xae180999;
*((unsigned int *)((unsigned long)context_ptr+0x000068a0+4*4))=0x51b5551e;
*((unsigned int *)((unsigned long)context_ptr+0x000068a0+4*5))=0x9688c451;
*((unsigned int *)((unsigned long)context_ptr+0x000068a0+4*6))=0xbe5decee;
*((unsigned int *)((unsigned long)context_ptr+0x000068a0+4*7))=0xa9012dc1;
*((unsigned int *)((unsigned long)context_ptr+0x000068a0+4*8))=0xd4cecce7;
*((unsigned int *)((unsigned long)context_ptr+0x000068a0+4*9))=0x7bd4d99c;
*((unsigned int *)((unsigned long)context_ptr+0x000068a0+4*10))=0x24a3fa21;
*((unsigned int *)((unsigned long)context_ptr+0x000068a0+4*11))=0x95d385f5;
*((unsigned int *)((unsigned long)context_ptr+0x000068a0+4*12))=0x66fec2b4;
*((unsigned int *)((unsigned long)context_ptr+0x000068a0+4*13))=0xa8e90b81;
*((unsigned int *)((unsigned long)context_ptr+0x000068a0+4*14))=0x3611e097;
*((unsigned int *)((unsigned long)context_ptr+0x000068a0+4*15))=0xd548edfc;
*((unsigned int *)((unsigned long)context_ptr+0x000068a0+4*16))=0x9dbc6236;
*((unsigned int *)((unsigned long)context_ptr+0x000068a0+4*17))=0x4f372caa;
*((unsigned int *)((unsigned long)context_ptr+0x000068a0+4*18))=0xe9564470;
*((unsigned int *)((unsigned long)context_ptr+0x000068a0+4*19))=0xf8c3fea3;
*((unsigned int *)((unsigned long)context_ptr+0x000068a0+4*20))=0x56349ebe;
*((unsigned int *)((unsigned long)context_ptr+0x000068a0+4*21))=0xd0f904de;
*((unsigned int *)((unsigned long)context_ptr+0x000068a0+4*22))=0x6918d83c;
*((unsigned int *)((unsigned long)context_ptr+0x000068a0+4*23))=0x6c10dacd;
*((unsigned int *)((unsigned long)context_ptr+0x000068a0+4*24))=0xf25f68cd;
*((unsigned int *)((unsigned long)context_ptr+0x000068a0+4*25))=0x869f3d24;
*((unsigned int *)((unsigned long)context_ptr+0x000068a0+4*26))=0xc5953159;
*((unsigned int *)((unsigned long)context_ptr+0x000068a0+4*27))=0xa57a2d0b;
*((unsigned int *)((unsigned long)context_ptr+0x000068a0+4*28))=0x2827c64e;
*((unsigned int *)((unsigned long)context_ptr+0x000068a0+4*29))=0x9dec7b59;
*((unsigned int *)((unsigned long)context_ptr+0x00003b28))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003b28+4*1))=0x000061b4;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000b28+4*1))=0x000068a0;
*((unsigned int *)((unsigned long)context_ptr+0x00000b28+4*2))=0x000061a4;
*((unsigned int *)((unsigned long)context_ptr+0x00000b28+4*3))=0x02220078;
*((unsigned int *)((unsigned long)context_ptr+0x00000b28+4*4))=0x098153b0;
*((unsigned int *)((unsigned long)context_ptr+0x00000b28+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000027c&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006394,"\x6f\x32\xe7\xb0\x96\x09\xbd\x1a\x4b\x7e\x17\x32\xc6\xb6\x8d\x49\x48\x48\x32\x50",20))
printf("strip: 6f32e7b09609bd1a, Pass\n");
else
printf("strip: 6f32e7b09609bd1a, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006018))=0x010a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006018+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006018+4*2))=0x02020079;
*((unsigned int *)((unsigned long)context_ptr+0x00006018+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x0000630c))=0xfb9088bc;
*((unsigned int *)((unsigned long)context_ptr+0x0000630c+4*1))=0xc252ea90;
*((unsigned int *)((unsigned long)context_ptr+0x0000630c+4*2))=0xe4066998;
*((unsigned int *)((unsigned long)context_ptr+0x0000630c+4*3))=0x49d1de7d;
*((unsigned int *)((unsigned long)context_ptr+0x0000630c+4*4))=0xd5acd69a;
*((unsigned int *)((unsigned long)context_ptr+0x0000630c+4*5))=0xde152b74;
*((unsigned int *)((unsigned long)context_ptr+0x0000630c+4*6))=0x9854a427;
*((unsigned int *)((unsigned long)context_ptr+0x0000630c+4*7))=0x1a354373;
*((unsigned int *)((unsigned long)context_ptr+0x0000630c+4*8))=0xcfc64b89;
*((unsigned int *)((unsigned long)context_ptr+0x0000630c+4*9))=0xe4bfc260;
*((unsigned int *)((unsigned long)context_ptr+0x0000630c+4*10))=0xfc2fe2b6;
*((unsigned int *)((unsigned long)context_ptr+0x0000630c+4*11))=0x7dcbc749;
*((unsigned int *)((unsigned long)context_ptr+0x0000630c+4*12))=0x374e0ae9;
*((unsigned int *)((unsigned long)context_ptr+0x0000630c+4*13))=0x46328a09;
*((unsigned int *)((unsigned long)context_ptr+0x0000630c+4*14))=0x1e1cca92;
*((unsigned int *)((unsigned long)context_ptr+0x0000630c+4*15))=0x9e8407e0;
*((unsigned int *)((unsigned long)context_ptr+0x0000630c+4*16))=0xbee36712;
*((unsigned int *)((unsigned long)context_ptr+0x0000630c+4*17))=0x87b39cbe;
*((unsigned int *)((unsigned long)context_ptr+0x0000630c+4*18))=0xbcc3f135;
*((unsigned int *)((unsigned long)context_ptr+0x0000630c+4*19))=0xb19d3910;
*((unsigned int *)((unsigned long)context_ptr+0x0000630c+4*20))=0xe61b9172;
*((unsigned int *)((unsigned long)context_ptr+0x0000630c+4*21))=0x640f865d;
*((unsigned int *)((unsigned long)context_ptr+0x0000630c+4*22))=0xc6ca2c92;
*((unsigned int *)((unsigned long)context_ptr+0x0000630c+4*23))=0x633094f7;
*((unsigned int *)((unsigned long)context_ptr+0x0000630c+4*24))=0xa47168c4;
*((unsigned int *)((unsigned long)context_ptr+0x0000630c+4*25))=0x8997656e;
*((unsigned int *)((unsigned long)context_ptr+0x0000630c+4*26))=0xee19f837;
*((unsigned int *)((unsigned long)context_ptr+0x0000630c+4*27))=0x08a469e1;
*((unsigned int *)((unsigned long)context_ptr+0x0000630c+4*28))=0x85bc3293;
*((unsigned int *)((unsigned long)context_ptr+0x0000630c+4*29))=0xcbde6476;
*((unsigned int *)((unsigned long)context_ptr+0x0000630c+4*30))=0x000000bf;
*((unsigned int *)((unsigned long)context_ptr+0x00003b40))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003b40+4*1))=0x000061c8;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000b40+4*1))=0x0000630c;
*((unsigned int *)((unsigned long)context_ptr+0x00000b40+4*2))=0x00006018;
*((unsigned int *)((unsigned long)context_ptr+0x00000b40+4*3))=0x02220079;
*((unsigned int *)((unsigned long)context_ptr+0x00000b40+4*4))=0x08d02db3;
*((unsigned int *)((unsigned long)context_ptr+0x00000b40+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000282&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006038,"\x91\xa6\x63\x8e\xd8\xb0\xa7\xbb\x3a\x2b\x4c\x68\xff\xf8\x4e\x10\x52\xba\xe4\xfd",20))
printf("strip: 91a6638ed8b0a7bb, Pass\n");
else
printf("strip: 91a6638ed8b0a7bb, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006008))=0x010a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006008+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006008+4*2))=0x0202007a;
*((unsigned int *)((unsigned long)context_ptr+0x00006008+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x000069fc))=0x6287cc99;
*((unsigned int *)((unsigned long)context_ptr+0x000069fc+4*1))=0x6a23bec5;
*((unsigned int *)((unsigned long)context_ptr+0x000069fc+4*2))=0x0bfeb9be;
*((unsigned int *)((unsigned long)context_ptr+0x000069fc+4*3))=0x490d30ba;
*((unsigned int *)((unsigned long)context_ptr+0x000069fc+4*4))=0x0474e7bd;
*((unsigned int *)((unsigned long)context_ptr+0x000069fc+4*5))=0x86d9f012;
*((unsigned int *)((unsigned long)context_ptr+0x000069fc+4*6))=0x9342e832;
*((unsigned int *)((unsigned long)context_ptr+0x000069fc+4*7))=0x8f03ccb9;
*((unsigned int *)((unsigned long)context_ptr+0x000069fc+4*8))=0x0a7c9548;
*((unsigned int *)((unsigned long)context_ptr+0x000069fc+4*9))=0xecaec5ff;
*((unsigned int *)((unsigned long)context_ptr+0x000069fc+4*10))=0x0df82c97;
*((unsigned int *)((unsigned long)context_ptr+0x000069fc+4*11))=0x8c54a40e;
*((unsigned int *)((unsigned long)context_ptr+0x000069fc+4*12))=0x9eb46454;
*((unsigned int *)((unsigned long)context_ptr+0x000069fc+4*13))=0xf46b56f0;
*((unsigned int *)((unsigned long)context_ptr+0x000069fc+4*14))=0xc9ca1ce8;
*((unsigned int *)((unsigned long)context_ptr+0x000069fc+4*15))=0x35ffb541;
*((unsigned int *)((unsigned long)context_ptr+0x000069fc+4*16))=0x8334f6c4;
*((unsigned int *)((unsigned long)context_ptr+0x000069fc+4*17))=0xaf9f80fb;
*((unsigned int *)((unsigned long)context_ptr+0x000069fc+4*18))=0x1d33cc6c;
*((unsigned int *)((unsigned long)context_ptr+0x000069fc+4*19))=0x66638abb;
*((unsigned int *)((unsigned long)context_ptr+0x000069fc+4*20))=0x87f55b6a;
*((unsigned int *)((unsigned long)context_ptr+0x000069fc+4*21))=0x64254ab7;
*((unsigned int *)((unsigned long)context_ptr+0x000069fc+4*22))=0x3a9cb6ba;
*((unsigned int *)((unsigned long)context_ptr+0x000069fc+4*23))=0x4b430dba;
*((unsigned int *)((unsigned long)context_ptr+0x000069fc+4*24))=0x5197a314;
*((unsigned int *)((unsigned long)context_ptr+0x000069fc+4*25))=0x8b3decdc;
*((unsigned int *)((unsigned long)context_ptr+0x000069fc+4*26))=0xaa1937e7;
*((unsigned int *)((unsigned long)context_ptr+0x000069fc+4*27))=0xb9af1ace;
*((unsigned int *)((unsigned long)context_ptr+0x000069fc+4*28))=0x53aa4b3a;
*((unsigned int *)((unsigned long)context_ptr+0x000069fc+4*29))=0xc81a1e07;
*((unsigned int *)((unsigned long)context_ptr+0x000069fc+4*30))=0x0000328c;
*((unsigned int *)((unsigned long)context_ptr+0x00003b58))=0x04c00014;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000b58+4*1))=0x000069fc;
*((unsigned int *)((unsigned long)context_ptr+0x00000b58+4*2))=0x00006008;
*((unsigned int *)((unsigned long)context_ptr+0x00000b58+4*3))=0x0222007a;
*((unsigned int *)((unsigned long)context_ptr+0x00000b58+4*4))=0x02ae8cb9;
*((unsigned int *)((unsigned long)context_ptr+0x00000b58+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000288&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x0000605c,"\xfd\x52\x05\x7a\x61\x4e\x40\x27\xcb\x91\x82\xeb\x90\xc5\x64\x07\x9d\x13\x9e\x7b",20))
printf("strip: fd52057a614e4027, Pass\n");
else
printf("strip: fd52057a614e4027, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006028))=0x010a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006028+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006028+4*2))=0x0202007b;
*((unsigned int *)((unsigned long)context_ptr+0x00006028+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x00006a78))=0x3aa5f73c;
*((unsigned int *)((unsigned long)context_ptr+0x00006a78+4*1))=0x02dbaa81;
*((unsigned int *)((unsigned long)context_ptr+0x00006a78+4*2))=0xb33e34a0;
*((unsigned int *)((unsigned long)context_ptr+0x00006a78+4*3))=0x47b7ed20;
*((unsigned int *)((unsigned long)context_ptr+0x00006a78+4*4))=0x3390b336;
*((unsigned int *)((unsigned long)context_ptr+0x00006a78+4*5))=0xc85dcf1d;
*((unsigned int *)((unsigned long)context_ptr+0x00006a78+4*6))=0xad39ec7f;
*((unsigned int *)((unsigned long)context_ptr+0x00006a78+4*7))=0x2bec3285;
*((unsigned int *)((unsigned long)context_ptr+0x00006a78+4*8))=0xc60ef9f2;
*((unsigned int *)((unsigned long)context_ptr+0x00006a78+4*9))=0x96ba378a;
*((unsigned int *)((unsigned long)context_ptr+0x00006a78+4*10))=0xc2f39a5e;
*((unsigned int *)((unsigned long)context_ptr+0x00006a78+4*11))=0xc89b926c;
*((unsigned int *)((unsigned long)context_ptr+0x00006a78+4*12))=0x76b443d6;
*((unsigned int *)((unsigned long)context_ptr+0x00006a78+4*13))=0x000de5b5;
*((unsigned int *)((unsigned long)context_ptr+0x00006a78+4*14))=0x62601678;
*((unsigned int *)((unsigned long)context_ptr+0x00006a78+4*15))=0x7119073a;
*((unsigned int *)((unsigned long)context_ptr+0x00006a78+4*16))=0xd2980157;
*((unsigned int *)((unsigned long)context_ptr+0x00006a78+4*17))=0x83b7ff74;
*((unsigned int *)((unsigned long)context_ptr+0x00006a78+4*18))=0xa25593d6;
*((unsigned int *)((unsigned long)context_ptr+0x00006a78+4*19))=0xc13d8a8a;
*((unsigned int *)((unsigned long)context_ptr+0x00006a78+4*20))=0xda565abd;
*((unsigned int *)((unsigned long)context_ptr+0x00006a78+4*21))=0x91636532;
*((unsigned int *)((unsigned long)context_ptr+0x00006a78+4*22))=0xa964e91b;
*((unsigned int *)((unsigned long)context_ptr+0x00006a78+4*23))=0xb413d8e0;
*((unsigned int *)((unsigned long)context_ptr+0x00006a78+4*24))=0xf73457d8;
*((unsigned int *)((unsigned long)context_ptr+0x00006a78+4*25))=0x5281f84c;
*((unsigned int *)((unsigned long)context_ptr+0x00006a78+4*26))=0x0256a674;
*((unsigned int *)((unsigned long)context_ptr+0x00006a78+4*27))=0x7e6665f5;
*((unsigned int *)((unsigned long)context_ptr+0x00006a78+4*28))=0x9778c863;
*((unsigned int *)((unsigned long)context_ptr+0x00006a78+4*29))=0xd7c827a0;
*((unsigned int *)((unsigned long)context_ptr+0x00006a78+4*30))=0x00b56e2a;
*((unsigned int *)((unsigned long)context_ptr+0x00003b70))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003b70+4*1))=0x0000605c;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000b70+4*1))=0x00006a78;
*((unsigned int *)((unsigned long)context_ptr+0x00000b70+4*2))=0x00006028;
*((unsigned int *)((unsigned long)context_ptr+0x00000b70+4*3))=0x0222007b;
*((unsigned int *)((unsigned long)context_ptr+0x00000b70+4*4))=0x0e5d151b;
*((unsigned int *)((unsigned long)context_ptr+0x00000b70+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000028e&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006460,"\xa9\x4e\x6c\x42\xcc\x40\xd4\x50\x64\x42\x04\x86\xa5\x63\x1a\x7c\x72\x64\xcc\x83",20))
printf("strip: a94e6c42cc40d450, Pass\n");
else
printf("strip: a94e6c42cc40d450, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x0000604c))=0x010a0012;
*((unsigned int *)((unsigned long)context_ptr+0x0000604c+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x0000604c+4*2))=0x0202007c;
*((unsigned int *)((unsigned long)context_ptr+0x0000604c+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x00006af4))=0x03431be6;
*((unsigned int *)((unsigned long)context_ptr+0x00006af4+4*1))=0xe14c79cc;
*((unsigned int *)((unsigned long)context_ptr+0x00006af4+4*2))=0x6beca2db;
*((unsigned int *)((unsigned long)context_ptr+0x00006af4+4*3))=0xbbeb6a95;
*((unsigned int *)((unsigned long)context_ptr+0x00006af4+4*4))=0x82e51889;
*((unsigned int *)((unsigned long)context_ptr+0x00006af4+4*5))=0x7482b456;
*((unsigned int *)((unsigned long)context_ptr+0x00006af4+4*6))=0x82ad08b7;
*((unsigned int *)((unsigned long)context_ptr+0x00006af4+4*7))=0x03d4f0bf;
*((unsigned int *)((unsigned long)context_ptr+0x00006af4+4*8))=0xef505a73;
*((unsigned int *)((unsigned long)context_ptr+0x00006af4+4*9))=0x1d0996bf;
*((unsigned int *)((unsigned long)context_ptr+0x00006af4+4*10))=0x78e2e66e;
*((unsigned int *)((unsigned long)context_ptr+0x00006af4+4*11))=0x0abe7e29;
*((unsigned int *)((unsigned long)context_ptr+0x00006af4+4*12))=0xf2a7c670;
*((unsigned int *)((unsigned long)context_ptr+0x00006af4+4*13))=0x26bab66b;
*((unsigned int *)((unsigned long)context_ptr+0x00006af4+4*14))=0x00958d60;
*((unsigned int *)((unsigned long)context_ptr+0x00006af4+4*15))=0x53f989a7;
*((unsigned int *)((unsigned long)context_ptr+0x00006af4+4*16))=0x2979864e;
*((unsigned int *)((unsigned long)context_ptr+0x00006af4+4*17))=0x95861a7c;
*((unsigned int *)((unsigned long)context_ptr+0x00006af4+4*18))=0x30e86ac6;
*((unsigned int *)((unsigned long)context_ptr+0x00006af4+4*19))=0x044091be;
*((unsigned int *)((unsigned long)context_ptr+0x00006af4+4*20))=0xad7d132a;
*((unsigned int *)((unsigned long)context_ptr+0x00006af4+4*21))=0xafb4a67e;
*((unsigned int *)((unsigned long)context_ptr+0x00006af4+4*22))=0x20d8c607;
*((unsigned int *)((unsigned long)context_ptr+0x00006af4+4*23))=0x0a23a72d;
*((unsigned int *)((unsigned long)context_ptr+0x00006af4+4*24))=0xa644a2ed;
*((unsigned int *)((unsigned long)context_ptr+0x00006af4+4*25))=0xef1b6265;
*((unsigned int *)((unsigned long)context_ptr+0x00006af4+4*26))=0xa5ebb370;
*((unsigned int *)((unsigned long)context_ptr+0x00006af4+4*27))=0x5317a6b4;
*((unsigned int *)((unsigned long)context_ptr+0x00006af4+4*28))=0x5f4051e3;
*((unsigned int *)((unsigned long)context_ptr+0x00006af4+4*29))=0x9ad96a17;
*((unsigned int *)((unsigned long)context_ptr+0x00006af4+4*30))=0x4e9a7f86;
*((unsigned int *)((unsigned long)context_ptr+0x00003b88))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003b88+4*1))=0x00006460;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000b88+4*1))=0x00006af4;
*((unsigned int *)((unsigned long)context_ptr+0x00000b88+4*2))=0x0000604c;
*((unsigned int *)((unsigned long)context_ptr+0x00000b88+4*3))=0x0222007c;
*((unsigned int *)((unsigned long)context_ptr+0x00000b88+4*4))=0x08ae17b8;
*((unsigned int *)((unsigned long)context_ptr+0x00000b88+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000294&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x0000624c,"\x5c\x80\xb2\xf9\x08\xa3\x21\x03\x12\xaf\x5a\x3e\x26\x30\xde\xdc\xae\xf0\x20\x8d",20))
printf("strip: 5c80b2f908a32103, Pass\n");
else
printf("strip: 5c80b2f908a32103, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006070))=0x010a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006070+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006070+4*2))=0x0202007d;
*((unsigned int *)((unsigned long)context_ptr+0x00006070+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x000061dc))=0x6eeb459c;
*((unsigned int *)((unsigned long)context_ptr+0x000061dc+4*1))=0x14120b62;
*((unsigned int *)((unsigned long)context_ptr+0x000061dc+4*2))=0x10423c4f;
*((unsigned int *)((unsigned long)context_ptr+0x000061dc+4*3))=0x3013fe65;
*((unsigned int *)((unsigned long)context_ptr+0x000061dc+4*4))=0xecaa9227;
*((unsigned int *)((unsigned long)context_ptr+0x000061dc+4*5))=0x423ec346;
*((unsigned int *)((unsigned long)context_ptr+0x000061dc+4*6))=0x9445d50c;
*((unsigned int *)((unsigned long)context_ptr+0x000061dc+4*7))=0x44eb8718;
*((unsigned int *)((unsigned long)context_ptr+0x000061dc+4*8))=0x55542f99;
*((unsigned int *)((unsigned long)context_ptr+0x000061dc+4*9))=0x18726746;
*((unsigned int *)((unsigned long)context_ptr+0x000061dc+4*10))=0xb5922d81;
*((unsigned int *)((unsigned long)context_ptr+0x000061dc+4*11))=0x11eace5b;
*((unsigned int *)((unsigned long)context_ptr+0x000061dc+4*12))=0x0847d670;
*((unsigned int *)((unsigned long)context_ptr+0x000061dc+4*13))=0xdc1aef74;
*((unsigned int *)((unsigned long)context_ptr+0x000061dc+4*14))=0xd92f8280;
*((unsigned int *)((unsigned long)context_ptr+0x000061dc+4*15))=0xf592d3c5;
*((unsigned int *)((unsigned long)context_ptr+0x000061dc+4*16))=0xdb642eaa;
*((unsigned int *)((unsigned long)context_ptr+0x000061dc+4*17))=0x205098b4;
*((unsigned int *)((unsigned long)context_ptr+0x000061dc+4*18))=0x72e844ec;
*((unsigned int *)((unsigned long)context_ptr+0x000061dc+4*19))=0xa0211cb3;
*((unsigned int *)((unsigned long)context_ptr+0x000061dc+4*20))=0x50a89e7f;
*((unsigned int *)((unsigned long)context_ptr+0x000061dc+4*21))=0x25df0985;
*((unsigned int *)((unsigned long)context_ptr+0x000061dc+4*22))=0xda03232f;
*((unsigned int *)((unsigned long)context_ptr+0x000061dc+4*23))=0xa64f44c4;
*((unsigned int *)((unsigned long)context_ptr+0x000061dc+4*24))=0xcfd428b3;
*((unsigned int *)((unsigned long)context_ptr+0x000061dc+4*25))=0x190c08ab;
*((unsigned int *)((unsigned long)context_ptr+0x000061dc+4*26))=0x6745a0b2;
*((unsigned int *)((unsigned long)context_ptr+0x000061dc+4*27))=0xa7b34233;
*((unsigned int *)((unsigned long)context_ptr+0x000061dc+4*28))=0xf3e32929;
*((unsigned int *)((unsigned long)context_ptr+0x000061dc+4*29))=0x2c561053;
*((unsigned int *)((unsigned long)context_ptr+0x000061dc+4*30))=0x14f97551;
*((unsigned int *)((unsigned long)context_ptr+0x000061dc+4*31))=0x0000000a;
*((unsigned int *)((unsigned long)context_ptr+0x00003ba0))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003ba0+4*1))=0x00006388;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000ba0+4*1))=0x000061dc;
*((unsigned int *)((unsigned long)context_ptr+0x00000ba0+4*2))=0x00006070;
*((unsigned int *)((unsigned long)context_ptr+0x00000ba0+4*3))=0x0222007d;
*((unsigned int *)((unsigned long)context_ptr+0x00000ba0+4*4))=0x0f74f31a;
*((unsigned int *)((unsigned long)context_ptr+0x00000ba0+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000029a&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x0000658c,"\x07\xac\xe5\x8c\xee\x0b\x2e\x62\xc7\x36\x2c\x82\x1f\x34\x14\x9a\xe1\x20\x2a\x79",20))
printf("strip: 07ace58cee0b2e62, Pass\n");
else
printf("strip: 07ace58cee0b2e62, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006918))=0x010a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006918+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006918+4*2))=0x0202007e;
*((unsigned int *)((unsigned long)context_ptr+0x00006918+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x00006498))=0x0ccc9aa7;
*((unsigned int *)((unsigned long)context_ptr+0x00006498+4*1))=0xdff789b4;
*((unsigned int *)((unsigned long)context_ptr+0x00006498+4*2))=0xd2e01261;
*((unsigned int *)((unsigned long)context_ptr+0x00006498+4*3))=0x65121a6b;
*((unsigned int *)((unsigned long)context_ptr+0x00006498+4*4))=0x644dc04f;
*((unsigned int *)((unsigned long)context_ptr+0x00006498+4*5))=0x38fb7cb4;
*((unsigned int *)((unsigned long)context_ptr+0x00006498+4*6))=0x092145b9;
*((unsigned int *)((unsigned long)context_ptr+0x00006498+4*7))=0xefe82262;
*((unsigned int *)((unsigned long)context_ptr+0x00006498+4*8))=0x58856b96;
*((unsigned int *)((unsigned long)context_ptr+0x00006498+4*9))=0x2dd59280;
*((unsigned int *)((unsigned long)context_ptr+0x00006498+4*10))=0x46e668e2;
*((unsigned int *)((unsigned long)context_ptr+0x00006498+4*11))=0x20c42aaf;
*((unsigned int *)((unsigned long)context_ptr+0x00006498+4*12))=0x89fa3469;
*((unsigned int *)((unsigned long)context_ptr+0x00006498+4*13))=0x44186a2c;
*((unsigned int *)((unsigned long)context_ptr+0x00006498+4*14))=0x81dae11f;
*((unsigned int *)((unsigned long)context_ptr+0x00006498+4*15))=0x330330b1;
*((unsigned int *)((unsigned long)context_ptr+0x00006498+4*16))=0x2743a16a;
*((unsigned int *)((unsigned long)context_ptr+0x00006498+4*17))=0xcda658ad;
*((unsigned int *)((unsigned long)context_ptr+0x00006498+4*18))=0x39cb5444;
*((unsigned int *)((unsigned long)context_ptr+0x00006498+4*19))=0x81da213f;
*((unsigned int *)((unsigned long)context_ptr+0x00006498+4*20))=0x4239d3c3;
*((unsigned int *)((unsigned long)context_ptr+0x00006498+4*21))=0xf4549957;
*((unsigned int *)((unsigned long)context_ptr+0x00006498+4*22))=0x55fe0b62;
*((unsigned int *)((unsigned long)context_ptr+0x00006498+4*23))=0x7b4b11a1;
*((unsigned int *)((unsigned long)context_ptr+0x00006498+4*24))=0xebde59c0;
*((unsigned int *)((unsigned long)context_ptr+0x00006498+4*25))=0x4d9394dd;
*((unsigned int *)((unsigned long)context_ptr+0x00006498+4*26))=0xb657071d;
*((unsigned int *)((unsigned long)context_ptr+0x00006498+4*27))=0x63ed7886;
*((unsigned int *)((unsigned long)context_ptr+0x00006498+4*28))=0x3663418a;
*((unsigned int *)((unsigned long)context_ptr+0x00006498+4*29))=0x416cb2b4;
*((unsigned int *)((unsigned long)context_ptr+0x00006498+4*30))=0x8654e74a;
*((unsigned int *)((unsigned long)context_ptr+0x00006498+4*31))=0x0000878b;
*((unsigned int *)((unsigned long)context_ptr+0x00003bb8))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003bb8+4*1))=0x00006928;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000bb8+4*1))=0x00006498;
*((unsigned int *)((unsigned long)context_ptr+0x00000bb8+4*2))=0x00006918;
*((unsigned int *)((unsigned long)context_ptr+0x00000bb8+4*3))=0x0222007e;
*((unsigned int *)((unsigned long)context_ptr+0x00000bb8+4*4))=0x0568c1fa;
*((unsigned int *)((unsigned long)context_ptr+0x00000bb8+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000002a0&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006610,"\x77\x58\x29\x87\x8d\xd6\xca\xf7\xb2\x41\x9f\xf1\x94\x5e\x1e\xe8\x0e\xbc\x6c\x5f",20))
printf("strip: 775829878dd6caf7, Pass\n");
else
printf("strip: 775829878dd6caf7, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x0000639c))=0x010a0012;
*((unsigned int *)((unsigned long)context_ptr+0x0000639c+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x0000639c+4*2))=0x0202007f;
*((unsigned int *)((unsigned long)context_ptr+0x0000639c+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x00006518))=0x2529b530;
*((unsigned int *)((unsigned long)context_ptr+0x00006518+4*1))=0x335667ec;
*((unsigned int *)((unsigned long)context_ptr+0x00006518+4*2))=0x02998124;
*((unsigned int *)((unsigned long)context_ptr+0x00006518+4*3))=0xd3293760;
*((unsigned int *)((unsigned long)context_ptr+0x00006518+4*4))=0x9c8e65b3;
*((unsigned int *)((unsigned long)context_ptr+0x00006518+4*5))=0x8c439665;
*((unsigned int *)((unsigned long)context_ptr+0x00006518+4*6))=0x75941bb5;
*((unsigned int *)((unsigned long)context_ptr+0x00006518+4*7))=0xa2d3360b;
*((unsigned int *)((unsigned long)context_ptr+0x00006518+4*8))=0x3853cfa5;
*((unsigned int *)((unsigned long)context_ptr+0x00006518+4*9))=0x342b6bb5;
*((unsigned int *)((unsigned long)context_ptr+0x00006518+4*10))=0x191d3042;
*((unsigned int *)((unsigned long)context_ptr+0x00006518+4*11))=0xda4e75d9;
*((unsigned int *)((unsigned long)context_ptr+0x00006518+4*12))=0x7df11a5c;
*((unsigned int *)((unsigned long)context_ptr+0x00006518+4*13))=0xcecb1250;
*((unsigned int *)((unsigned long)context_ptr+0x00006518+4*14))=0x5677f1fb;
*((unsigned int *)((unsigned long)context_ptr+0x00006518+4*15))=0x602fbb5a;
*((unsigned int *)((unsigned long)context_ptr+0x00006518+4*16))=0x2bce391f;
*((unsigned int *)((unsigned long)context_ptr+0x00006518+4*17))=0x289b7a6c;
*((unsigned int *)((unsigned long)context_ptr+0x00006518+4*18))=0x91b3faaa;
*((unsigned int *)((unsigned long)context_ptr+0x00006518+4*19))=0xdaeb1083;
*((unsigned int *)((unsigned long)context_ptr+0x00006518+4*20))=0xa2ce2d06;
*((unsigned int *)((unsigned long)context_ptr+0x00006518+4*21))=0xd4a67cf2;
*((unsigned int *)((unsigned long)context_ptr+0x00006518+4*22))=0x9d303d97;
*((unsigned int *)((unsigned long)context_ptr+0x00006518+4*23))=0x5f42afcc;
*((unsigned int *)((unsigned long)context_ptr+0x00006518+4*24))=0x3a01a087;
*((unsigned int *)((unsigned long)context_ptr+0x00006518+4*25))=0xcdf2c3a7;
*((unsigned int *)((unsigned long)context_ptr+0x00006518+4*26))=0x1e963bf4;
*((unsigned int *)((unsigned long)context_ptr+0x00006518+4*27))=0xbcb03e9b;
*((unsigned int *)((unsigned long)context_ptr+0x00006518+4*28))=0x186e0b7c;
*((unsigned int *)((unsigned long)context_ptr+0x00006518+4*29))=0x23ebd68c;
*((unsigned int *)((unsigned long)context_ptr+0x00006518+4*30))=0x9bdf3294;
*((unsigned int *)((unsigned long)context_ptr+0x00006518+4*31))=0x0043c615;
*((unsigned int *)((unsigned long)context_ptr+0x00003bd0))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003bd0+4*1))=0x0000693c;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000bd0+4*1))=0x00006518;
*((unsigned int *)((unsigned long)context_ptr+0x00000bd0+4*2))=0x0000639c;
*((unsigned int *)((unsigned long)context_ptr+0x00000bd0+4*3))=0x0222007f;
*((unsigned int *)((unsigned long)context_ptr+0x00000bd0+4*4))=0x0dede5c4;
*((unsigned int *)((unsigned long)context_ptr+0x00000bd0+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000002a6&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006804,"\x30\x21\xd3\xcc\x12\x51\x04\x3a\xa6\x31\x11\xa3\xef\x92\x5b\x3d\xa1\x58\xb7\xe4",20))
printf("strip: 3021d3cc1251043a, Pass\n");
else
printf("strip: 3021d3cc1251043a, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006950))=0x010a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006950+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006950+4*2))=0x02020080;
*((unsigned int *)((unsigned long)context_ptr+0x00006950+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x00006598))=0x4871f85e;
*((unsigned int *)((unsigned long)context_ptr+0x00006598+4*1))=0x0eded7a4;
*((unsigned int *)((unsigned long)context_ptr+0x00006598+4*2))=0xecf7be6e;
*((unsigned int *)((unsigned long)context_ptr+0x00006598+4*3))=0xa0bd9905;
*((unsigned int *)((unsigned long)context_ptr+0x00006598+4*4))=0xbcad0e9d;
*((unsigned int *)((unsigned long)context_ptr+0x00006598+4*5))=0x7960c646;
*((unsigned int *)((unsigned long)context_ptr+0x00006598+4*6))=0x941aa03b;
*((unsigned int *)((unsigned long)context_ptr+0x00006598+4*7))=0x8a933b55;
*((unsigned int *)((unsigned long)context_ptr+0x00006598+4*8))=0xdab77b3b;
*((unsigned int *)((unsigned long)context_ptr+0x00006598+4*9))=0x506f0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006598+4*10))=0xf3d95ae6;
*((unsigned int *)((unsigned long)context_ptr+0x00006598+4*11))=0x192d4ce4;
*((unsigned int *)((unsigned long)context_ptr+0x00006598+4*12))=0x408be758;
*((unsigned int *)((unsigned long)context_ptr+0x00006598+4*13))=0xea550bbe;
*((unsigned int *)((unsigned long)context_ptr+0x00006598+4*14))=0x94a1c243;
*((unsigned int *)((unsigned long)context_ptr+0x00006598+4*15))=0x575195c8;
*((unsigned int *)((unsigned long)context_ptr+0x00006598+4*16))=0x3607c31e;
*((unsigned int *)((unsigned long)context_ptr+0x00006598+4*17))=0x95eba041;
*((unsigned int *)((unsigned long)context_ptr+0x00006598+4*18))=0x6ed1e808;
*((unsigned int *)((unsigned long)context_ptr+0x00006598+4*19))=0x957ff50d;
*((unsigned int *)((unsigned long)context_ptr+0x00006598+4*20))=0x2008dcab;
*((unsigned int *)((unsigned long)context_ptr+0x00006598+4*21))=0x9e9eb4d2;
*((unsigned int *)((unsigned long)context_ptr+0x00006598+4*22))=0xfe253220;
*((unsigned int *)((unsigned long)context_ptr+0x00006598+4*23))=0x4a08f450;
*((unsigned int *)((unsigned long)context_ptr+0x00006598+4*24))=0x65546477;
*((unsigned int *)((unsigned long)context_ptr+0x00006598+4*25))=0xc33ed15c;
*((unsigned int *)((unsigned long)context_ptr+0x00006598+4*26))=0x144413db;
*((unsigned int *)((unsigned long)context_ptr+0x00006598+4*27))=0x966a079f;
*((unsigned int *)((unsigned long)context_ptr+0x00006598+4*28))=0x3eb1dd03;
*((unsigned int *)((unsigned long)context_ptr+0x00006598+4*29))=0xf05a1a4f;
*((unsigned int *)((unsigned long)context_ptr+0x00006598+4*30))=0xf8af3cc5;
*((unsigned int *)((unsigned long)context_ptr+0x00006598+4*31))=0xc0891f10;
*((unsigned int *)((unsigned long)context_ptr+0x00003be8))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003be8+4*1))=0x00006960;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000be8+4*1))=0x00006598;
*((unsigned int *)((unsigned long)context_ptr+0x00000be8+4*2))=0x00006950;
*((unsigned int *)((unsigned long)context_ptr+0x00000be8+4*3))=0x02220080;
*((unsigned int *)((unsigned long)context_ptr+0x00000be8+4*4))=0x046e3592;
*((unsigned int *)((unsigned long)context_ptr+0x00000be8+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000002ac&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x0000688c,"\xb3\x3f\xc8\xb2\xe4\x31\xf4\x41\x84\xba\xb2\x94\xaa\xb3\x85\x15\x51\xa1\xd8\x21",20))
printf("strip: b33fc8b2e431f441, Pass\n");
else
printf("strip: b33fc8b2e431f441, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006974))=0x010a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006974+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006974+4*2))=0x02020081;
*((unsigned int *)((unsigned long)context_ptr+0x00006974+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x00006618))=0x5b8d2cfa;
*((unsigned int *)((unsigned long)context_ptr+0x00006618+4*1))=0x7625bd31;
*((unsigned int *)((unsigned long)context_ptr+0x00006618+4*2))=0x446729f1;
*((unsigned int *)((unsigned long)context_ptr+0x00006618+4*3))=0x82d8bbaf;
*((unsigned int *)((unsigned long)context_ptr+0x00006618+4*4))=0x56f861cf;
*((unsigned int *)((unsigned long)context_ptr+0x00006618+4*5))=0x57900310;
*((unsigned int *)((unsigned long)context_ptr+0x00006618+4*6))=0x5c937160;
*((unsigned int *)((unsigned long)context_ptr+0x00006618+4*7))=0x0ed1407a;
*((unsigned int *)((unsigned long)context_ptr+0x00006618+4*8))=0x492d7fe1;
*((unsigned int *)((unsigned long)context_ptr+0x00006618+4*9))=0x9ef726a6;
*((unsigned int *)((unsigned long)context_ptr+0x00006618+4*10))=0x1fe1e4dd;
*((unsigned int *)((unsigned long)context_ptr+0x00006618+4*11))=0x52b7dca0;
*((unsigned int *)((unsigned long)context_ptr+0x00006618+4*12))=0xeb9a019b;
*((unsigned int *)((unsigned long)context_ptr+0x00006618+4*13))=0x820fc664;
*((unsigned int *)((unsigned long)context_ptr+0x00006618+4*14))=0x21351906;
*((unsigned int *)((unsigned long)context_ptr+0x00006618+4*15))=0x16b60c08;
*((unsigned int *)((unsigned long)context_ptr+0x00006618+4*16))=0x287938a4;
*((unsigned int *)((unsigned long)context_ptr+0x00006618+4*17))=0x276f4bb7;
*((unsigned int *)((unsigned long)context_ptr+0x00006618+4*18))=0x0d008b05;
*((unsigned int *)((unsigned long)context_ptr+0x00006618+4*19))=0x788cff42;
*((unsigned int *)((unsigned long)context_ptr+0x00006618+4*20))=0xb1749929;
*((unsigned int *)((unsigned long)context_ptr+0x00006618+4*21))=0x07772a98;
*((unsigned int *)((unsigned long)context_ptr+0x00006618+4*22))=0x9ec21ca3;
*((unsigned int *)((unsigned long)context_ptr+0x00006618+4*23))=0x30c0f24b;
*((unsigned int *)((unsigned long)context_ptr+0x00006618+4*24))=0x2c43cc47;
*((unsigned int *)((unsigned long)context_ptr+0x00006618+4*25))=0x2e383343;
*((unsigned int *)((unsigned long)context_ptr+0x00006618+4*26))=0x5574f32f;
*((unsigned int *)((unsigned long)context_ptr+0x00006618+4*27))=0x973bce8d;
*((unsigned int *)((unsigned long)context_ptr+0x00006618+4*28))=0x99836fd6;
*((unsigned int *)((unsigned long)context_ptr+0x00006618+4*29))=0x9ecd5742;
*((unsigned int *)((unsigned long)context_ptr+0x00006618+4*30))=0x9d4e3ead;
*((unsigned int *)((unsigned long)context_ptr+0x00006618+4*31))=0x1eefe430;
*((unsigned int *)((unsigned long)context_ptr+0x00006618+4*32))=0x00000006;
*((unsigned int *)((unsigned long)context_ptr+0x00003c00))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003c00+4*1))=0x0000669c;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000c00+4*1))=0x00006618;
*((unsigned int *)((unsigned long)context_ptr+0x00000c00+4*2))=0x00006974;
*((unsigned int *)((unsigned long)context_ptr+0x00000c00+4*3))=0x02220081;
*((unsigned int *)((unsigned long)context_ptr+0x00000c00+4*4))=0x01997436;
*((unsigned int *)((unsigned long)context_ptr+0x00000c00+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000002b2&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000062d4,"\xc9\xfa\x23\x00\x92\x05\x22\xd4\x82\x52\xc4\x52\xa6\x8e\xa6\xff\xe6\x5f\x53\x4b",20))
printf("strip: c9fa2300920522d4, Pass\n");
else
printf("strip: c9fa2300920522d4, Failed\n");
writel(0x000002b8&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000062f8,"\x23\x33\xad\x8b\x03\x1c\x96\x91\x32\xd0\x47\xec\x2e\x52\xcc\xf0\xb0\x44\x7c\x63",20))
printf("strip: 2333ad8b031c9691, Pass\n");
else
printf("strip: 2333ad8b031c9691, Failed\n");
writel(0x000002be&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006484,"\xf5\x96\x0e\x0c\x12\xe3\xdc\x75\x0f\xbd\xcc\x29\x43\x40\xe8\x28\x95\x0e\x28\x74",20))
printf("strip: f5960e0c12e3dc75, Pass\n");
else
printf("strip: f5960e0c12e3dc75, Failed\n");
writel(0x000002c4&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x0000644c,"\x1a\x60\x4f\x17\x9a\xb5\x84\xb3\x30\x9d\x92\x04\x6c\x7c\x59\xb3\x1c\x1b\xb8\x37",20))
printf("strip: 1a604f179ab584b3, Pass\n");
else
printf("strip: 1a604f179ab584b3, Failed\n");
writel(0x000002ca&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006190,"\xb6\xcd\x4a\x06\x3f\x73\x7c\xd2\xe2\x40\x33\x4e\x81\x77\x3c\xc0\x3d\x12\x30\x7f",20))
printf("strip: b6cd4a063f737cd2, Pass\n");
else
printf("strip: b6cd4a063f737cd2, Failed\n");
writel(0x000002d0&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000061b4,"\x34\x39\xc5\x79\x63\xd3\x1a\x6a\x56\x06\x13\x47\xeb\xfe\xf2\xb0\x77\x85\x86\x5f",20))
printf("strip: 3439c57963d31a6a, Pass\n");
else
printf("strip: 3439c57963d31a6a, Failed\n");
writel(0x000002d6&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000061c8,"\xc1\xe3\x8d\xa3\x21\xd8\x58\xf0\x5f\x03\xe4\x79\x3b\xe7\x17\x22\xab\xb1\xe5\xba",20))
printf("strip: c1e38da321d858f0, Pass\n");
else
printf("strip: c1e38da321d858f0, Failed\n");
writel(0x000002dc&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006038,"\x29\xd6\x32\xb9\x9d\xad\xb9\xc5\x9e\x57\x9f\xd9\x8f\x2d\xd9\x2e\xf0\xdb\xf7\x3d",20))
printf("strip: 29d632b99dadb9c5, Pass\n");
else
printf("strip: 29d632b99dadb9c5, Failed\n");
writel(0x000002e2&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x0000605c,"\xea\xa5\xe8\x49\x6d\x3a\x80\xe3\x00\xb6\x59\xd6\x99\x08\x25\x6d\x98\x95\x72\x90",20))
printf("strip: eaa5e8496d3a80e3, Pass\n");
else
printf("strip: eaa5e8496d3a80e3, Failed\n");
writel(0x000002e8&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006460,"\x5b\xaa\x21\xa6\x3e\x8c\x65\x2e\xa5\x46\xd9\x7b\x15\xea\xe3\xb9\xd4\xb3\x86\x3f",20))
printf("strip: 5baa21a63e8c652e, Pass\n");
else
printf("strip: 5baa21a63e8c652e, Failed\n");
writel(0x000002ee&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006388,"\x2c\x01\x57\xd4\xb2\xfa\x1f\x1c\x57\x31\x99\x12\xb7\x09\x3e\xe1\xd6\x22\x1f\x66",20))
printf("strip: 2c0157d4b2fa1f1c, Pass\n");
else
printf("strip: 2c0157d4b2fa1f1c, Failed\n");
writel(0x000002f4&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006928,"\xaa\x72\x8b\x6f\x97\x39\xa8\xd7\x25\xb3\xb8\x18\xe6\x02\xa3\x50\xa6\x36\x61\x42",20))
printf("strip: aa728b6f9739a8d7, Pass\n");
else
printf("strip: aa728b6f9739a8d7, Failed\n");
writel(0x000002fa&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x0000693c,"\x3b\x28\x50\x7f\x8e\x14\xeb\x70\xdb\x72\xe2\x29\xb9\x5d\x65\xc0\xe2\x4b\xab\x16",20))
printf("strip: 3b28507f8e14eb70, Pass\n");
else
printf("strip: 3b28507f8e14eb70, Failed\n");
writel(0x00000300&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
writel(0x00000c00&0xffffffff,ivp_cae_base_addr+0x00000830);
if(!memcmp((unsigned char *)context_ptr+0x00006960,"\xb2\x14\xce\x9a\x2a\x0a\x65\x9d\x33\x88\x9c\x2e\x0a\x78\x7b\x9d\x2e\x17\x2f\xd7",20))
printf("strip: b214ce9a2a0a659d, Pass\n");
else
printf("strip: b214ce9a2a0a659d, Failed\n");
writel(0x00000006&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x0000669c,"\x14\xfd\x36\x44\x1b\xad\x7e\x83\x03\x67\x98\x14\x41\x68\x42\xb0\x9a\x07\x6c\x26",20))
printf("strip: 14fd36441bad7e83, Pass\n");
else
printf("strip: 14fd36441bad7e83, Failed\n");
}

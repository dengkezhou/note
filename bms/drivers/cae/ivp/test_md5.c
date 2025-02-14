#include <common.h>
#include <malloc.h>

extern volatile unsigned int ivp_cae_base_addr;

void test_md5(void)
{
unsigned int *context_ptr=(unsigned int *)0x14000000;
printf("test_md5\n");
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
*((unsigned int *)((unsigned long)context_ptr+0x00006000))=0x000a0002;
*((unsigned int *)((unsigned long)context_ptr+0x00006000+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006008))=0x000a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006008+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006008+4*2))=0x02020001;
*((unsigned int *)((unsigned long)context_ptr+0x00006008+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x00006018))=0x00000033;
*((unsigned int *)((unsigned long)context_ptr+0x00003000))=0x04c00010;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000000+4*4))=0x05718adb;
*((unsigned int *)((unsigned long)context_ptr+0x00000000+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x0000602c))=0x000a0012;
*((unsigned int *)((unsigned long)context_ptr+0x0000602c+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x0000602c+4*2))=0x02020002;
*((unsigned int *)((unsigned long)context_ptr+0x0000602c+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x0000603c))=0x0000c2ce;
*((unsigned int *)((unsigned long)context_ptr+0x00003018))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003018+4*1))=0x00006040;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000018+4*1))=0x0000603c;
*((unsigned int *)((unsigned long)context_ptr+0x00000018+4*2))=0x0000602c;
*((unsigned int *)((unsigned long)context_ptr+0x00000018+4*3))=0x02220002;
*((unsigned int *)((unsigned long)context_ptr+0x00000018+4*4))=0x0e7e13ec;
*((unsigned int *)((unsigned long)context_ptr+0x00000018+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x00006050))=0x000a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006050+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006050+4*2))=0x02020003;
*((unsigned int *)((unsigned long)context_ptr+0x00006050+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x00006060))=0x00acb7dd;
*((unsigned int *)((unsigned long)context_ptr+0x00003030))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003030+4*1))=0x00006064;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000030+4*1))=0x00006060;
*((unsigned int *)((unsigned long)context_ptr+0x00000030+4*2))=0x00006050;
*((unsigned int *)((unsigned long)context_ptr+0x00000030+4*3))=0x02220003;
*((unsigned int *)((unsigned long)context_ptr+0x00000030+4*4))=0x069407bd;
*((unsigned int *)((unsigned long)context_ptr+0x00000030+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x00006074))=0x000a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006074+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006074+4*2))=0x02020004;
*((unsigned int *)((unsigned long)context_ptr+0x00006074+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x00006084))=0x71c830c9;
*((unsigned int *)((unsigned long)context_ptr+0x00003048))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003048+4*1))=0x00006088;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000048+4*1))=0x00006084;
*((unsigned int *)((unsigned long)context_ptr+0x00000048+4*2))=0x00006074;
*((unsigned int *)((unsigned long)context_ptr+0x00000048+4*3))=0x02220004;
*((unsigned int *)((unsigned long)context_ptr+0x00000048+4*4))=0x0ca20854;
*((unsigned int *)((unsigned long)context_ptr+0x00000048+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x00006098))=0x000a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006098+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006098+4*2))=0x02020005;
*((unsigned int *)((unsigned long)context_ptr+0x00006098+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x000060a8))=0x075b1214;
*((unsigned int *)((unsigned long)context_ptr+0x000060a8+4*1))=0x00000059;
*((unsigned int *)((unsigned long)context_ptr+0x00003060))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003060+4*1))=0x000060b0;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000060+4*1))=0x000060a8;
*((unsigned int *)((unsigned long)context_ptr+0x00000060+4*2))=0x00006098;
*((unsigned int *)((unsigned long)context_ptr+0x00000060+4*3))=0x02220005;
*((unsigned int *)((unsigned long)context_ptr+0x00000060+4*4))=0x0d1aa6c3;
*((unsigned int *)((unsigned long)context_ptr+0x00000060+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x000060c0))=0x000a0012;
*((unsigned int *)((unsigned long)context_ptr+0x000060c0+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000060c0+4*2))=0x02020006;
*((unsigned int *)((unsigned long)context_ptr+0x000060c0+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x000060d0))=0x6b4ac13e;
*((unsigned int *)((unsigned long)context_ptr+0x000060d0+4*1))=0x0000210b;
*((unsigned int *)((unsigned long)context_ptr+0x00003078))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003078+4*1))=0x000060d8;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000078+4*1))=0x000060d0;
*((unsigned int *)((unsigned long)context_ptr+0x00000078+4*2))=0x000060c0;
*((unsigned int *)((unsigned long)context_ptr+0x00000078+4*3))=0x02220006;
*((unsigned int *)((unsigned long)context_ptr+0x00000078+4*4))=0x012bdf74;
*((unsigned int *)((unsigned long)context_ptr+0x00000078+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x000060e8))=0x000a0012;
*((unsigned int *)((unsigned long)context_ptr+0x000060e8+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000060e8+4*2))=0x02020007;
*((unsigned int *)((unsigned long)context_ptr+0x000060e8+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x000060f8))=0xb200347b;
*((unsigned int *)((unsigned long)context_ptr+0x000060f8+4*1))=0x004c019e;
*((unsigned int *)((unsigned long)context_ptr+0x00003090))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003090+4*1))=0x00006100;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000090+4*1))=0x000060f8;
*((unsigned int *)((unsigned long)context_ptr+0x00000090+4*2))=0x000060e8;
*((unsigned int *)((unsigned long)context_ptr+0x00000090+4*3))=0x02220007;
*((unsigned int *)((unsigned long)context_ptr+0x00000090+4*4))=0x08b92c24;
*((unsigned int *)((unsigned long)context_ptr+0x00000090+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x00006110))=0x000a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006110+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006110+4*2))=0x02020008;
*((unsigned int *)((unsigned long)context_ptr+0x00006110+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x00006120))=0x67a26988;
*((unsigned int *)((unsigned long)context_ptr+0x00006120+4*1))=0x5f4ac9c7;
*((unsigned int *)((unsigned long)context_ptr+0x000030a8))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x000030a8+4*1))=0x00006128;
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
*((unsigned int *)((unsigned long)context_ptr+0x000000a8+4*1))=0x00006120;
*((unsigned int *)((unsigned long)context_ptr+0x000000a8+4*2))=0x00006110;
*((unsigned int *)((unsigned long)context_ptr+0x000000a8+4*3))=0x02220008;
*((unsigned int *)((unsigned long)context_ptr+0x000000a8+4*4))=0x0b270af3;
*((unsigned int *)((unsigned long)context_ptr+0x000000a8+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x00006138))=0x000a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006138+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006138+4*2))=0x02020009;
*((unsigned int *)((unsigned long)context_ptr+0x00006138+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x00006148))=0x2b54751a;
*((unsigned int *)((unsigned long)context_ptr+0x00006148+4*1))=0x726fe56b;
*((unsigned int *)((unsigned long)context_ptr+0x00006148+4*2))=0x000000b5;
*((unsigned int *)((unsigned long)context_ptr+0x000030c0))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x000030c0+4*1))=0x00006154;
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
*((unsigned int *)((unsigned long)context_ptr+0x000000c0+4*1))=0x00006148;
*((unsigned int *)((unsigned long)context_ptr+0x000000c0+4*2))=0x00006138;
*((unsigned int *)((unsigned long)context_ptr+0x000000c0+4*3))=0x02220009;
*((unsigned int *)((unsigned long)context_ptr+0x000000c0+4*4))=0x0e90f79d;
*((unsigned int *)((unsigned long)context_ptr+0x000000c0+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x00006164))=0x000a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006164+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006164+4*2))=0x0202000a;
*((unsigned int *)((unsigned long)context_ptr+0x00006164+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x00006174))=0x23a70029;
*((unsigned int *)((unsigned long)context_ptr+0x00006174+4*1))=0x65f8aec9;
*((unsigned int *)((unsigned long)context_ptr+0x00006174+4*2))=0x000074eb;
*((unsigned int *)((unsigned long)context_ptr+0x000030d8))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x000030d8+4*1))=0x00006180;
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
*((unsigned int *)((unsigned long)context_ptr+0x000000d8+4*1))=0x00006174;
*((unsigned int *)((unsigned long)context_ptr+0x000000d8+4*2))=0x00006164;
*((unsigned int *)((unsigned long)context_ptr+0x000000d8+4*3))=0x0222000a;
*((unsigned int *)((unsigned long)context_ptr+0x000000d8+4*4))=0x0e2014a3;
*((unsigned int *)((unsigned long)context_ptr+0x000000d8+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x00006190))=0x000a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006190+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006190+4*2))=0x0202000b;
*((unsigned int *)((unsigned long)context_ptr+0x00006190+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x000061a0))=0x207d2e0a;
*((unsigned int *)((unsigned long)context_ptr+0x000061a0+4*1))=0x6f51efde;
*((unsigned int *)((unsigned long)context_ptr+0x000061a0+4*2))=0x008a498e;
*((unsigned int *)((unsigned long)context_ptr+0x000030f0))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x000030f0+4*1))=0x000061ac;
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
*((unsigned int *)((unsigned long)context_ptr+0x000000f0+4*1))=0x000061a0;
*((unsigned int *)((unsigned long)context_ptr+0x000000f0+4*2))=0x00006190;
*((unsigned int *)((unsigned long)context_ptr+0x000000f0+4*3))=0x0222000b;
*((unsigned int *)((unsigned long)context_ptr+0x000000f0+4*4))=0x07118bb6;
*((unsigned int *)((unsigned long)context_ptr+0x000000f0+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x000061bc))=0x000a0012;
*((unsigned int *)((unsigned long)context_ptr+0x000061bc+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000061bc+4*2))=0x0202000c;
*((unsigned int *)((unsigned long)context_ptr+0x000061bc+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x000061cc))=0xc31382f9;
*((unsigned int *)((unsigned long)context_ptr+0x000061cc+4*1))=0xb291c6c8;
*((unsigned int *)((unsigned long)context_ptr+0x000061cc+4*2))=0xc2d0bb36;
*((unsigned int *)((unsigned long)context_ptr+0x00003108))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003108+4*1))=0x000061d8;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000108+4*1))=0x000061cc;
*((unsigned int *)((unsigned long)context_ptr+0x00000108+4*2))=0x000061bc;
*((unsigned int *)((unsigned long)context_ptr+0x00000108+4*3))=0x0222000c;
*((unsigned int *)((unsigned long)context_ptr+0x00000108+4*4))=0x0a105724;
*((unsigned int *)((unsigned long)context_ptr+0x00000108+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x000061e8))=0x000a0012;
*((unsigned int *)((unsigned long)context_ptr+0x000061e8+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000061e8+4*2))=0x0202000d;
*((unsigned int *)((unsigned long)context_ptr+0x000061e8+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x000061f8))=0x0f11a739;
*((unsigned int *)((unsigned long)context_ptr+0x000061f8+4*1))=0x37e46cf8;
*((unsigned int *)((unsigned long)context_ptr+0x000061f8+4*2))=0x542d5b6f;
*((unsigned int *)((unsigned long)context_ptr+0x000061f8+4*3))=0x000000fc;
*((unsigned int *)((unsigned long)context_ptr+0x00003120))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003120+4*1))=0x00006208;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000120+4*1))=0x000061f8;
*((unsigned int *)((unsigned long)context_ptr+0x00000120+4*2))=0x000061e8;
*((unsigned int *)((unsigned long)context_ptr+0x00000120+4*3))=0x0222000d;
*((unsigned int *)((unsigned long)context_ptr+0x00000120+4*4))=0x068c6dd5;
*((unsigned int *)((unsigned long)context_ptr+0x00000120+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x00006218))=0x000a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006218+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006218+4*2))=0x0202000e;
*((unsigned int *)((unsigned long)context_ptr+0x00006218+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x00006228))=0x67bc5b3c;
*((unsigned int *)((unsigned long)context_ptr+0x00006228+4*1))=0x4f647e45;
*((unsigned int *)((unsigned long)context_ptr+0x00006228+4*2))=0xc5fa8ce6;
*((unsigned int *)((unsigned long)context_ptr+0x00006228+4*3))=0x00004392;
*((unsigned int *)((unsigned long)context_ptr+0x00003138))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003138+4*1))=0x00006238;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000138+4*1))=0x00006228;
*((unsigned int *)((unsigned long)context_ptr+0x00000138+4*2))=0x00006218;
*((unsigned int *)((unsigned long)context_ptr+0x00000138+4*3))=0x0222000e;
*((unsigned int *)((unsigned long)context_ptr+0x00000138+4*4))=0x0b8acdd7;
*((unsigned int *)((unsigned long)context_ptr+0x00000138+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x00006248))=0x000a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006248+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006248+4*2))=0x0202000f;
*((unsigned int *)((unsigned long)context_ptr+0x00006248+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x00006258))=0xf27af2ed;
*((unsigned int *)((unsigned long)context_ptr+0x00006258+4*1))=0x30bfc7d1;
*((unsigned int *)((unsigned long)context_ptr+0x00006258+4*2))=0x2cf36c8c;
*((unsigned int *)((unsigned long)context_ptr+0x00006258+4*3))=0x0028a82b;
*((unsigned int *)((unsigned long)context_ptr+0x00003150))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003150+4*1))=0x00006268;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000150+4*1))=0x00006258;
*((unsigned int *)((unsigned long)context_ptr+0x00000150+4*2))=0x00006248;
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
if(!memcmp((unsigned char *)context_ptr+0x0000601c,"\xec\xcb\xc8\x7e\x4b\x5c\xe2\xfe\x28\x30\x8f\xd9\xf2\xa7\xba\xf3",16))
printf("strip: eccbc87e4b5ce2fe, Pass\n");
else
printf("strip: eccbc87e4b5ce2fe, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006008))=0x000a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006008+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006008+4*2))=0x02020010;
*((unsigned int *)((unsigned long)context_ptr+0x00006008+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x00006018))=0xb4ce8273;
*((unsigned int *)((unsigned long)context_ptr+0x00006018+4*1))=0xedec2af5;
*((unsigned int *)((unsigned long)context_ptr+0x00006018+4*2))=0xe140f0a2;
*((unsigned int *)((unsigned long)context_ptr+0x00006018+4*3))=0x07179cc6;
*((unsigned int *)((unsigned long)context_ptr+0x00003168))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003168+4*1))=0x00006278;
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
if(!memcmp((unsigned char *)context_ptr+0x00006040,"\x71\x06\x5f\xf4\x7d\xba\x68\x0a\x70\x04\x50\xd7\xe0\x68\x71\x86",16))
printf("strip: 71065ff47dba680a, Pass\n");
else
printf("strip: 71065ff47dba680a, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006028))=0x000a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006028+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006028+4*2))=0x02020011;
*((unsigned int *)((unsigned long)context_ptr+0x00006028+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x00006038))=0x58f3a1be;
*((unsigned int *)((unsigned long)context_ptr+0x00006038+4*1))=0xd08f1595;
*((unsigned int *)((unsigned long)context_ptr+0x00006038+4*2))=0x40b34233;
*((unsigned int *)((unsigned long)context_ptr+0x00006038+4*3))=0x27ffef42;
*((unsigned int *)((unsigned long)context_ptr+0x00006038+4*4))=0x000000e6;
*((unsigned int *)((unsigned long)context_ptr+0x00003180))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003180+4*1))=0x00006288;
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
if(!memcmp((unsigned char *)context_ptr+0x00006064,"\x6c\x7e\x3c\x2d\xad\x3e\x93\xee\x3d\x6d\xe0\xe8\xc8\xf8\xd0\x34",16))
printf("strip: 6c7e3c2dad3e93ee, Pass\n");
else
printf("strip: 6c7e3c2dad3e93ee, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x0000604c))=0x000a0012;
*((unsigned int *)((unsigned long)context_ptr+0x0000604c+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x0000604c+4*2))=0x02020012;
*((unsigned int *)((unsigned long)context_ptr+0x0000604c+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x0000605c))=0x90acc1e6;
*((unsigned int *)((unsigned long)context_ptr+0x0000605c+4*1))=0xcd0769cd;
*((unsigned int *)((unsigned long)context_ptr+0x0000605c+4*2))=0x1f5b6330;
*((unsigned int *)((unsigned long)context_ptr+0x0000605c+4*3))=0xa79d2d59;
*((unsigned int *)((unsigned long)context_ptr+0x0000605c+4*4))=0x00007403;
*((unsigned int *)((unsigned long)context_ptr+0x00003198))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003198+4*1))=0x00006298;
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
if(!memcmp((unsigned char *)context_ptr+0x00006088,"\xe3\xaa\xd5\x48\xe8\xa2\x2b\x2a\xca\xc0\xdd\xb4\xcf\xdd\x90\x80",16))
printf("strip: e3aad548e8a22b2a, Pass\n");
else
printf("strip: e3aad548e8a22b2a, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006070))=0x000a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006070+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006070+4*2))=0x02020013;
*((unsigned int *)((unsigned long)context_ptr+0x00006070+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x00006080))=0xd204ffcd;
*((unsigned int *)((unsigned long)context_ptr+0x00006080+4*1))=0x1cc60982;
*((unsigned int *)((unsigned long)context_ptr+0x00006080+4*2))=0x61acc79c;
*((unsigned int *)((unsigned long)context_ptr+0x00006080+4*3))=0x55e96f06;
*((unsigned int *)((unsigned long)context_ptr+0x00006080+4*4))=0x0082233f;
*((unsigned int *)((unsigned long)context_ptr+0x000031b0))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x000031b0+4*1))=0x000062a8;
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
if(!memcmp((unsigned char *)context_ptr+0x000060b0,"\x3c\xc1\x6c\x45\xd5\x52\xea\x06\x87\xdf\x63\x8d\x36\x9a\xb6\xe6",16))
printf("strip: 3cc16c45d552ea06, Pass\n");
else
printf("strip: 3cc16c45d552ea06, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006094))=0x000a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006094+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006094+4*2))=0x02020014;
*((unsigned int *)((unsigned long)context_ptr+0x00006094+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x000060a4))=0x4b952df5;
*((unsigned int *)((unsigned long)context_ptr+0x000060a4+4*1))=0xae6e4aa2;
*((unsigned int *)((unsigned long)context_ptr+0x000060a4+4*2))=0x2158ba44;
*((unsigned int *)((unsigned long)context_ptr+0x000060a4+4*3))=0x656e2a9c;
*((unsigned int *)((unsigned long)context_ptr+0x000060a4+4*4))=0xc7aeb513;
*((unsigned int *)((unsigned long)context_ptr+0x000031c8))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x000031c8+4*1))=0x000062b8;
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
*((unsigned int *)((unsigned long)context_ptr+0x000001c8+4*1))=0x000060a4;
*((unsigned int *)((unsigned long)context_ptr+0x000001c8+4*2))=0x00006094;
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
if(!memcmp((unsigned char *)context_ptr+0x000060d8,"\xb9\x42\x0e\xce\x41\x36\x17\x6a\x33\xb5\xc5\xda\xb8\xf6\xa2\xa4",16))
printf("strip: b9420ece4136176a, Pass\n");
else
printf("strip: b9420ece4136176a, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000060b8))=0x000a0012;
*((unsigned int *)((unsigned long)context_ptr+0x000060b8+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000060b8+4*2))=0x02020015;
*((unsigned int *)((unsigned long)context_ptr+0x000060b8+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x000060c8))=0x7bd1e402;
*((unsigned int *)((unsigned long)context_ptr+0x000060c8+4*1))=0x4095731b;
*((unsigned int *)((unsigned long)context_ptr+0x000060c8+4*2))=0x8fecc67c;
*((unsigned int *)((unsigned long)context_ptr+0x000060c8+4*3))=0xebdb13d3;
*((unsigned int *)((unsigned long)context_ptr+0x000060c8+4*4))=0xe0d9d32b;
*((unsigned int *)((unsigned long)context_ptr+0x000060c8+4*5))=0x00000084;
*((unsigned int *)((unsigned long)context_ptr+0x000031e0))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x000031e0+4*1))=0x000062c8;
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
*((unsigned int *)((unsigned long)context_ptr+0x000001e0+4*1))=0x000060c8;
*((unsigned int *)((unsigned long)context_ptr+0x000001e0+4*2))=0x000060b8;
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
if(!memcmp((unsigned char *)context_ptr+0x00006100,"\xac\xe0\x32\x1d\xba\x9e\x0f\x39\xe1\x15\x86\xb7\x26\xfb\x60\x42",16))
printf("strip: ace0321dba9e0f39, Pass\n");
else
printf("strip: ace0321dba9e0f39, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000060e0))=0x000a0012;
*((unsigned int *)((unsigned long)context_ptr+0x000060e0+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000060e0+4*2))=0x02020016;
*((unsigned int *)((unsigned long)context_ptr+0x000060e0+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x000060f0))=0x3a011857;
*((unsigned int *)((unsigned long)context_ptr+0x000060f0+4*1))=0x7e394fd6;
*((unsigned int *)((unsigned long)context_ptr+0x000060f0+4*2))=0x135782f2;
*((unsigned int *)((unsigned long)context_ptr+0x000060f0+4*3))=0x615e3992;
*((unsigned int *)((unsigned long)context_ptr+0x000060f0+4*4))=0xbeef3bc2;
*((unsigned int *)((unsigned long)context_ptr+0x000060f0+4*5))=0x0000e17b;
*((unsigned int *)((unsigned long)context_ptr+0x000031f8))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x000031f8+4*1))=0x000062d8;
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
*((unsigned int *)((unsigned long)context_ptr+0x000001f8+4*1))=0x000060f0;
*((unsigned int *)((unsigned long)context_ptr+0x000001f8+4*2))=0x000060e0;
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
if(!memcmp((unsigned char *)context_ptr+0x00006128,"\xca\xb0\xfd\x93\x44\xe0\x5c\xdc\x88\x60\x2b\xb7\x7b\xdc\x47\x27",16))
printf("strip: cab0fd9344e05cdc, Pass\n");
else
printf("strip: cab0fd9344e05cdc, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006108))=0x000a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006108+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006108+4*2))=0x02020017;
*((unsigned int *)((unsigned long)context_ptr+0x00006108+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x00006118))=0x9a1d0161;
*((unsigned int *)((unsigned long)context_ptr+0x00006118+4*1))=0x32bd33ef;
*((unsigned int *)((unsigned long)context_ptr+0x00006118+4*2))=0x11d8e500;
*((unsigned int *)((unsigned long)context_ptr+0x00006118+4*3))=0x61ed3b2d;
*((unsigned int *)((unsigned long)context_ptr+0x00006118+4*4))=0xc3616fce;
*((unsigned int *)((unsigned long)context_ptr+0x00006118+4*5))=0x0095449d;
*((unsigned int *)((unsigned long)context_ptr+0x00003210))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003210+4*1))=0x000062e8;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000210+4*1))=0x00006118;
*((unsigned int *)((unsigned long)context_ptr+0x00000210+4*2))=0x00006108;
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
if(!memcmp((unsigned char *)context_ptr+0x00006154,"\xa4\xe0\x4e\x2d\xd6\x96\xf9\x34\xd3\x04\xc3\x11\xcc\x06\x34\x96",16))
printf("strip: a4e04e2dd696f934, Pass\n");
else
printf("strip: a4e04e2dd696f934, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006130))=0x000a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006130+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006130+4*2))=0x02020018;
*((unsigned int *)((unsigned long)context_ptr+0x00006130+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x00006140))=0xde0927f2;
*((unsigned int *)((unsigned long)context_ptr+0x00006140+4*1))=0xad77c4ce;
*((unsigned int *)((unsigned long)context_ptr+0x00006140+4*2))=0xc9643169;
*((unsigned int *)((unsigned long)context_ptr+0x00006140+4*3))=0xaee3f6cd;
*((unsigned int *)((unsigned long)context_ptr+0x00006140+4*4))=0xec2eb985;
*((unsigned int *)((unsigned long)context_ptr+0x00006140+4*5))=0xa26f98b6;
*((unsigned int *)((unsigned long)context_ptr+0x00003228))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003228+4*1))=0x000062f8;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000228+4*1))=0x00006140;
*((unsigned int *)((unsigned long)context_ptr+0x00000228+4*2))=0x00006130;
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
if(!memcmp((unsigned char *)context_ptr+0x00006180,"\xe8\xb9\xad\xac\x06\xbb\x55\x56\xab\x24\x8d\x30\x8f\x5e\x58\x8a",16))
printf("strip: e8b9adac06bb5556, Pass\n");
else
printf("strip: e8b9adac06bb5556, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006158))=0x000a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006158+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006158+4*2))=0x02020019;
*((unsigned int *)((unsigned long)context_ptr+0x00006158+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x00006168))=0x037ef814;
*((unsigned int *)((unsigned long)context_ptr+0x00006168+4*1))=0xbe4fc16b;
*((unsigned int *)((unsigned long)context_ptr+0x00006168+4*2))=0x07f73dc4;
*((unsigned int *)((unsigned long)context_ptr+0x00006168+4*3))=0x422783dd;
*((unsigned int *)((unsigned long)context_ptr+0x00006168+4*4))=0x38d64797;
*((unsigned int *)((unsigned long)context_ptr+0x00006168+4*5))=0xd2568162;
*((unsigned int *)((unsigned long)context_ptr+0x00006168+4*6))=0x00000043;
*((unsigned int *)((unsigned long)context_ptr+0x00003240))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003240+4*1))=0x00006308;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000240+4*1))=0x00006168;
*((unsigned int *)((unsigned long)context_ptr+0x00000240+4*2))=0x00006158;
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
if(!memcmp((unsigned char *)context_ptr+0x000061ac,"\x5b\xfc\x51\x93\x49\x65\x62\x2c\x7d\xe7\xb7\x9c\x33\xbf\x04\x3e",16))
printf("strip: 5bfc51934965622c, Pass\n");
else
printf("strip: 5bfc51934965622c, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006184))=0x000a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006184+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006184+4*2))=0x0202001a;
*((unsigned int *)((unsigned long)context_ptr+0x00006184+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x00006194))=0xff59f944;
*((unsigned int *)((unsigned long)context_ptr+0x00006194+4*1))=0xfbd437da;
*((unsigned int *)((unsigned long)context_ptr+0x00006194+4*2))=0x15c5aa46;
*((unsigned int *)((unsigned long)context_ptr+0x00006194+4*3))=0xf3b44ed1;
*((unsigned int *)((unsigned long)context_ptr+0x00006194+4*4))=0x1d4a9c08;
*((unsigned int *)((unsigned long)context_ptr+0x00006194+4*5))=0x5883fab6;
*((unsigned int *)((unsigned long)context_ptr+0x00006194+4*6))=0x00006a72;
*((unsigned int *)((unsigned long)context_ptr+0x00003258))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003258+4*1))=0x00006318;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000258+4*1))=0x00006194;
*((unsigned int *)((unsigned long)context_ptr+0x00000258+4*2))=0x00006184;
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
if(!memcmp((unsigned char *)context_ptr+0x000061d8,"\x27\xee\x3c\x69\xd2\x09\x64\x69\x8d\x88\x69\x2c\x1b\x68\x5b\x20",16))
printf("strip: 27ee3c69d2096469, Pass\n");
else
printf("strip: 27ee3c69d2096469, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000061b0))=0x000a0012;
*((unsigned int *)((unsigned long)context_ptr+0x000061b0+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000061b0+4*2))=0x0202001b;
*((unsigned int *)((unsigned long)context_ptr+0x000061b0+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x000061c0))=0x8d254d38;
*((unsigned int *)((unsigned long)context_ptr+0x000061c0+4*1))=0xd23b0640;
*((unsigned int *)((unsigned long)context_ptr+0x000061c0+4*2))=0x3ef1e26a;
*((unsigned int *)((unsigned long)context_ptr+0x000061c0+4*3))=0x2b94e18f;
*((unsigned int *)((unsigned long)context_ptr+0x000061c0+4*4))=0xde4cfc3f;
*((unsigned int *)((unsigned long)context_ptr+0x000061c0+4*5))=0xcab8bdcb;
*((unsigned int *)((unsigned long)context_ptr+0x000061c0+4*6))=0x002a0fd8;
*((unsigned int *)((unsigned long)context_ptr+0x00003270))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003270+4*1))=0x00006328;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000270+4*1))=0x000061c0;
*((unsigned int *)((unsigned long)context_ptr+0x00000270+4*2))=0x000061b0;
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
if(!memcmp((unsigned char *)context_ptr+0x00006208,"\xc9\x93\x0c\x31\xb5\x53\x63\x2e\x66\x42\xf7\xbb\xbf\xac\xed\xd3",16))
printf("strip: c9930c31b553632e, Pass\n");
else
printf("strip: c9930c31b553632e, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000061dc))=0x000a0012;
*((unsigned int *)((unsigned long)context_ptr+0x000061dc+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000061dc+4*2))=0x0202001c;
*((unsigned int *)((unsigned long)context_ptr+0x000061dc+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x000061ec))=0x30d7c1ac;
*((unsigned int *)((unsigned long)context_ptr+0x000061ec+4*1))=0xce828337;
*((unsigned int *)((unsigned long)context_ptr+0x000061ec+4*2))=0x81c7e684;
*((unsigned int *)((unsigned long)context_ptr+0x000061ec+4*3))=0x6e5779d3;
*((unsigned int *)((unsigned long)context_ptr+0x000061ec+4*4))=0xba0da674;
*((unsigned int *)((unsigned long)context_ptr+0x000061ec+4*5))=0x331175f7;
*((unsigned int *)((unsigned long)context_ptr+0x000061ec+4*6))=0x00cb411a;
*((unsigned int *)((unsigned long)context_ptr+0x00003288))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003288+4*1))=0x00006208;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000288+4*1))=0x000061ec;
*((unsigned int *)((unsigned long)context_ptr+0x00000288+4*2))=0x000061dc;
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
if(!memcmp((unsigned char *)context_ptr+0x00006238,"\xd9\x30\x0d\x0d\x97\x72\x8b\xfd\x35\x51\x80\x83\x14\x2f\xd7\x0c",16))
printf("strip: d9300d0d97728bfd, Pass\n");
else
printf("strip: d9300d0d97728bfd, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006218))=0x000a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006218+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006218+4*2))=0x0202001d;
*((unsigned int *)((unsigned long)context_ptr+0x00006218+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x00006228))=0x1b28cd13;
*((unsigned int *)((unsigned long)context_ptr+0x00006228+4*1))=0x6b9bb642;
*((unsigned int *)((unsigned long)context_ptr+0x00006228+4*2))=0xafc4ec28;
*((unsigned int *)((unsigned long)context_ptr+0x00006228+4*3))=0xc51cc6d0;
*((unsigned int *)((unsigned long)context_ptr+0x00006228+4*4))=0xaf7bbfd6;
*((unsigned int *)((unsigned long)context_ptr+0x00006228+4*5))=0xc843c319;
*((unsigned int *)((unsigned long)context_ptr+0x00006228+4*6))=0x138982a2;
*((unsigned int *)((unsigned long)context_ptr+0x00006228+4*7))=0x0000000a;
*((unsigned int *)((unsigned long)context_ptr+0x000032a0))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x000032a0+4*1))=0x00006338;
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
*((unsigned int *)((unsigned long)context_ptr+0x000002a0+4*1))=0x00006228;
*((unsigned int *)((unsigned long)context_ptr+0x000002a0+4*2))=0x00006218;
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
if(!memcmp((unsigned char *)context_ptr+0x00006268,"\x99\xf5\x6a\x2c\x83\xa0\xcd\xca\x80\xed\xf4\x17\x4e\x6f\x0a\xc6",16))
printf("strip: 99f56a2c83a0cdca, Pass\n");
else
printf("strip: 99f56a2c83a0cdca, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006248))=0x000a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006248+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006248+4*2))=0x0202001e;
*((unsigned int *)((unsigned long)context_ptr+0x00006248+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x00006258))=0x62501589;
*((unsigned int *)((unsigned long)context_ptr+0x00006258+4*1))=0x126d7a67;
*((unsigned int *)((unsigned long)context_ptr+0x00006258+4*2))=0x82d4a438;
*((unsigned int *)((unsigned long)context_ptr+0x00006258+4*3))=0x62271225;
*((unsigned int *)((unsigned long)context_ptr+0x00006258+4*4))=0x9086aa90;
*((unsigned int *)((unsigned long)context_ptr+0x00006258+4*5))=0x66baaa5a;
*((unsigned int *)((unsigned long)context_ptr+0x00006258+4*6))=0x77e7bed0;
*((unsigned int *)((unsigned long)context_ptr+0x00006258+4*7))=0x0000c658;
*((unsigned int *)((unsigned long)context_ptr+0x000032b8))=0x04c00010;
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
*((unsigned int *)((unsigned long)context_ptr+0x000002b8+4*1))=0x00006258;
*((unsigned int *)((unsigned long)context_ptr+0x000002b8+4*2))=0x00006248;
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
if(!memcmp((unsigned char *)context_ptr+0x00006278,"\xb2\x35\xd0\xd6\x9d\xc4\xf0\xe5\x40\x08\x8b\x50\xb6\x01\x41\x0a",16))
printf("strip: b235d0d69dc4f0e5, Pass\n");
else
printf("strip: b235d0d69dc4f0e5, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006018))=0x000a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006018+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006018+4*2))=0x0202001f;
*((unsigned int *)((unsigned long)context_ptr+0x00006018+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x00006358))=0xa2563cf1;
*((unsigned int *)((unsigned long)context_ptr+0x00006358+4*1))=0x8cc22452;
*((unsigned int *)((unsigned long)context_ptr+0x00006358+4*2))=0xec1db589;
*((unsigned int *)((unsigned long)context_ptr+0x00006358+4*3))=0x9a99b17a;
*((unsigned int *)((unsigned long)context_ptr+0x00006358+4*4))=0x357f16b5;
*((unsigned int *)((unsigned long)context_ptr+0x00006358+4*5))=0x685a8363;
*((unsigned int *)((unsigned long)context_ptr+0x00006358+4*6))=0x9af40bbb;
*((unsigned int *)((unsigned long)context_ptr+0x00006358+4*7))=0x00148e29;
*((unsigned int *)((unsigned long)context_ptr+0x000032d0))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x000032d0+4*1))=0x00006278;
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
*((unsigned int *)((unsigned long)context_ptr+0x000002d0+4*1))=0x00006358;
*((unsigned int *)((unsigned long)context_ptr+0x000002d0+4*2))=0x00006018;
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
if(!memcmp((unsigned char *)context_ptr+0x00006288,"\x2e\x18\x45\x1b\xf6\x60\xa4\x92\xd6\xf0\xb2\x47\xe4\xeb\xf7\x01",16))
printf("strip: 2e18451bf660a492, Pass\n");
else
printf("strip: 2e18451bf660a492, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006008))=0x000a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006008+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006008+4*2))=0x02020020;
*((unsigned int *)((unsigned long)context_ptr+0x00006008+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x00006378))=0x7a8904de;
*((unsigned int *)((unsigned long)context_ptr+0x00006378+4*1))=0xe545d020;
*((unsigned int *)((unsigned long)context_ptr+0x00006378+4*2))=0xcadddab3;
*((unsigned int *)((unsigned long)context_ptr+0x00006378+4*3))=0x352401bc;
*((unsigned int *)((unsigned long)context_ptr+0x00006378+4*4))=0x7c200093;
*((unsigned int *)((unsigned long)context_ptr+0x00006378+4*5))=0x2c38510a;
*((unsigned int *)((unsigned long)context_ptr+0x00006378+4*6))=0xa63be151;
*((unsigned int *)((unsigned long)context_ptr+0x00006378+4*7))=0x5930acbb;
*((unsigned int *)((unsigned long)context_ptr+0x000032e8))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x000032e8+4*1))=0x00006288;
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
*((unsigned int *)((unsigned long)context_ptr+0x000002e8+4*1))=0x00006378;
*((unsigned int *)((unsigned long)context_ptr+0x000002e8+4*2))=0x00006008;
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
if(!memcmp((unsigned char *)context_ptr+0x00006298,"\x72\xb3\x47\x97\x84\x91\x4e\x35\xf4\x1d\xd1\x4b\x01\xeb\x15\x8c",16))
printf("strip: 72b3479784914e35, Pass\n");
else
printf("strip: 72b3479784914e35, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006298))=0x000a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006298+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006298+4*2))=0x02020021;
*((unsigned int *)((unsigned long)context_ptr+0x00006298+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x00006028))=0x079aa3cc;
*((unsigned int *)((unsigned long)context_ptr+0x00006028+4*1))=0xa434c458;
*((unsigned int *)((unsigned long)context_ptr+0x00006028+4*2))=0x368470f9;
*((unsigned int *)((unsigned long)context_ptr+0x00006028+4*3))=0x9a783c01;
*((unsigned int *)((unsigned long)context_ptr+0x00006028+4*4))=0xb8544ad5;
*((unsigned int *)((unsigned long)context_ptr+0x00006028+4*5))=0x16e0b6aa;
*((unsigned int *)((unsigned long)context_ptr+0x00006028+4*6))=0xa79c7f1f;
*((unsigned int *)((unsigned long)context_ptr+0x00006028+4*7))=0x3deb223a;
*((unsigned int *)((unsigned long)context_ptr+0x00006028+4*8))=0x00000004;
*((unsigned int *)((unsigned long)context_ptr+0x00003300))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003300+4*1))=0x0000604c;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000300+4*1))=0x00006028;
*((unsigned int *)((unsigned long)context_ptr+0x00000300+4*2))=0x00006298;
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
if(!memcmp((unsigned char *)context_ptr+0x000062a8,"\x54\xc4\xed\xd0\xc2\x4c\x5a\xde\xc2\xb8\x15\xd8\x9b\x69\x78\x28",16))
printf("strip: 54c4edd0c24c5ade, Pass\n");
else
printf("strip: 54c4edd0c24c5ade, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000062a8))=0x000a0012;
*((unsigned int *)((unsigned long)context_ptr+0x000062a8+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000062a8+4*2))=0x02020022;
*((unsigned int *)((unsigned long)context_ptr+0x000062a8+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x0000605c))=0xd2c327a3;
*((unsigned int *)((unsigned long)context_ptr+0x0000605c+4*1))=0x4547119e;
*((unsigned int *)((unsigned long)context_ptr+0x0000605c+4*2))=0xfd94c777;
*((unsigned int *)((unsigned long)context_ptr+0x0000605c+4*3))=0x0ffa24b5;
*((unsigned int *)((unsigned long)context_ptr+0x0000605c+4*4))=0x0563a355;
*((unsigned int *)((unsigned long)context_ptr+0x0000605c+4*5))=0x97c63d4b;
*((unsigned int *)((unsigned long)context_ptr+0x0000605c+4*6))=0x5136df24;
*((unsigned int *)((unsigned long)context_ptr+0x0000605c+4*7))=0x846bc3df;
*((unsigned int *)((unsigned long)context_ptr+0x0000605c+4*8))=0x0000b5fa;
*((unsigned int *)((unsigned long)context_ptr+0x00003318))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003318+4*1))=0x00006080;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000318+4*1))=0x0000605c;
*((unsigned int *)((unsigned long)context_ptr+0x00000318+4*2))=0x000062a8;
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
if(!memcmp((unsigned char *)context_ptr+0x000062b8,"\x57\xfb\x92\xed\x3c\x8e\xd8\x03\x53\x44\x2f\xcc\xa8\xf1\x33\xb4",16))
printf("strip: 57fb92ed3c8ed803, Pass\n");
else
printf("strip: 57fb92ed3c8ed803, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000062b8))=0x000a0012;
*((unsigned int *)((unsigned long)context_ptr+0x000062b8+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000062b8+4*2))=0x02020023;
*((unsigned int *)((unsigned long)context_ptr+0x000062b8+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x00006090))=0x0e18a33c;
*((unsigned int *)((unsigned long)context_ptr+0x00006090+4*1))=0x864d99d7;
*((unsigned int *)((unsigned long)context_ptr+0x00006090+4*2))=0x2400ad8e;
*((unsigned int *)((unsigned long)context_ptr+0x00006090+4*3))=0x3273c017;
*((unsigned int *)((unsigned long)context_ptr+0x00006090+4*4))=0x8b76ab5f;
*((unsigned int *)((unsigned long)context_ptr+0x00006090+4*5))=0x1b1a66f0;
*((unsigned int *)((unsigned long)context_ptr+0x00006090+4*6))=0xc71d4fb9;
*((unsigned int *)((unsigned long)context_ptr+0x00006090+4*7))=0xbd9d1ae3;
*((unsigned int *)((unsigned long)context_ptr+0x00006090+4*8))=0x00afd63e;
*((unsigned int *)((unsigned long)context_ptr+0x00003330))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003330+4*1))=0x00006398;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000330+4*1))=0x00006090;
*((unsigned int *)((unsigned long)context_ptr+0x00000330+4*2))=0x000062b8;
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
if(!memcmp((unsigned char *)context_ptr+0x000062c8,"\x42\xf4\x6a\x99\x4c\x4b\x60\x8f\xfa\x31\xbd\x03\x0e\x64\x2a\xb7",16))
printf("strip: 42f46a994c4b608f, Pass\n");
else
printf("strip: 42f46a994c4b608f, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000062c8))=0x000a0012;
*((unsigned int *)((unsigned long)context_ptr+0x000062c8+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000062c8+4*2))=0x02020024;
*((unsigned int *)((unsigned long)context_ptr+0x000062c8+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x000060b4))=0xbe7a0514;
*((unsigned int *)((unsigned long)context_ptr+0x000060b4+4*1))=0xd49d00bd;
*((unsigned int *)((unsigned long)context_ptr+0x000060b4+4*2))=0xb46bc5dd;
*((unsigned int *)((unsigned long)context_ptr+0x000060b4+4*3))=0x580910b3;
*((unsigned int *)((unsigned long)context_ptr+0x000060b4+4*4))=0xc2a561a4;
*((unsigned int *)((unsigned long)context_ptr+0x000060b4+4*5))=0x8df848c5;
*((unsigned int *)((unsigned long)context_ptr+0x000060b4+4*6))=0x27aca2a0;
*((unsigned int *)((unsigned long)context_ptr+0x000060b4+4*7))=0xb6f76eac;
*((unsigned int *)((unsigned long)context_ptr+0x000060b4+4*8))=0x96d5fdf9;
*((unsigned int *)((unsigned long)context_ptr+0x00003348))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003348+4*1))=0x000063a8;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000348+4*1))=0x000060b4;
*((unsigned int *)((unsigned long)context_ptr+0x00000348+4*2))=0x000062c8;
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
if(!memcmp((unsigned char *)context_ptr+0x000062d8,"\x7e\x84\x51\xee\x3e\x31\x65\xae\x83\x0f\xb8\x4a\x2e\x61\x1f\x6c",16))
printf("strip: 7e8451ee3e3165ae, Pass\n");
else
printf("strip: 7e8451ee3e3165ae, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000062d8))=0x000a0012;
*((unsigned int *)((unsigned long)context_ptr+0x000062d8+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000062d8+4*2))=0x02020025;
*((unsigned int *)((unsigned long)context_ptr+0x000062d8+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x000060d8))=0x13cb8ff2;
*((unsigned int *)((unsigned long)context_ptr+0x000060d8+4*1))=0xd21dc610;
*((unsigned int *)((unsigned long)context_ptr+0x000060d8+4*2))=0xb71d6eef;
*((unsigned int *)((unsigned long)context_ptr+0x000060d8+4*3))=0x8ae38072;
*((unsigned int *)((unsigned long)context_ptr+0x000060d8+4*4))=0x82d95f23;
*((unsigned int *)((unsigned long)context_ptr+0x000060d8+4*5))=0xe1088114;
*((unsigned int *)((unsigned long)context_ptr+0x000060d8+4*6))=0xe5feba3f;
*((unsigned int *)((unsigned long)context_ptr+0x000060d8+4*7))=0x8bb25287;
*((unsigned int *)((unsigned long)context_ptr+0x000060d8+4*8))=0x27b13de8;
*((unsigned int *)((unsigned long)context_ptr+0x000060d8+4*9))=0x00000067;
*((unsigned int *)((unsigned long)context_ptr+0x00003360))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003360+4*1))=0x000063b8;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000360+4*1))=0x000060d8;
*((unsigned int *)((unsigned long)context_ptr+0x00000360+4*2))=0x000062d8;
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
if(!memcmp((unsigned char *)context_ptr+0x000062e8,"\x63\x3c\xeb\xe2\xab\xe8\x79\xaa\x8b\xe9\xce\x6b\xe0\xb3\x4b\x73",16))
printf("strip: 633cebe2abe879aa, Pass\n");
else
printf("strip: 633cebe2abe879aa, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000062e8))=0x000a0012;
*((unsigned int *)((unsigned long)context_ptr+0x000062e8+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000062e8+4*2))=0x02020026;
*((unsigned int *)((unsigned long)context_ptr+0x000062e8+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x00006100))=0x549b0742;
*((unsigned int *)((unsigned long)context_ptr+0x00006100+4*1))=0x328c3be3;
*((unsigned int *)((unsigned long)context_ptr+0x00006100+4*2))=0xe4c0a4f7;
*((unsigned int *)((unsigned long)context_ptr+0x00006100+4*3))=0x9e738b74;
*((unsigned int *)((unsigned long)context_ptr+0x00006100+4*4))=0xc55dd255;
*((unsigned int *)((unsigned long)context_ptr+0x00006100+4*5))=0xe67a5d04;
*((unsigned int *)((unsigned long)context_ptr+0x00006100+4*6))=0xe6a2bbb8;
*((unsigned int *)((unsigned long)context_ptr+0x00006100+4*7))=0xc3eba1b9;
*((unsigned int *)((unsigned long)context_ptr+0x00006100+4*8))=0xbf30de03;
*((unsigned int *)((unsigned long)context_ptr+0x00006100+4*9))=0x00006469;
*((unsigned int *)((unsigned long)context_ptr+0x00003378))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003378+4*1))=0x000063c8;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000378+4*1))=0x00006100;
*((unsigned int *)((unsigned long)context_ptr+0x00000378+4*2))=0x000062e8;
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
if(!memcmp((unsigned char *)context_ptr+0x000062f8,"\x45\x47\x7b\xda\x38\xfb\xb1\x8e\x89\x86\xeb\xd6\x97\xe1\xdd\x7f",16))
printf("strip: 45477bda38fbb18e, Pass\n");
else
printf("strip: 45477bda38fbb18e, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000062f8))=0x000a0012;
*((unsigned int *)((unsigned long)context_ptr+0x000062f8+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000062f8+4*2))=0x02020027;
*((unsigned int *)((unsigned long)context_ptr+0x000062f8+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x00006128))=0x5cc6fdb9;
*((unsigned int *)((unsigned long)context_ptr+0x00006128+4*1))=0xe5886482;
*((unsigned int *)((unsigned long)context_ptr+0x00006128+4*2))=0x2581e418;
*((unsigned int *)((unsigned long)context_ptr+0x00006128+4*3))=0x780631ef;
*((unsigned int *)((unsigned long)context_ptr+0x00006128+4*4))=0x90a00c92;
*((unsigned int *)((unsigned long)context_ptr+0x00006128+4*5))=0x215b1490;
*((unsigned int *)((unsigned long)context_ptr+0x00006128+4*6))=0xe1545e77;
*((unsigned int *)((unsigned long)context_ptr+0x00006128+4*7))=0xffa81c9f;
*((unsigned int *)((unsigned long)context_ptr+0x00006128+4*8))=0x79a8c55d;
*((unsigned int *)((unsigned long)context_ptr+0x00006128+4*9))=0x006a3667;
*((unsigned int *)((unsigned long)context_ptr+0x00003390))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003390+4*1))=0x000063d8;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000390+4*1))=0x00006128;
*((unsigned int *)((unsigned long)context_ptr+0x00000390+4*2))=0x000062f8;
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
if(!memcmp((unsigned char *)context_ptr+0x00006308,"\xff\xae\x9b\xa3\x16\x95\xe1\xd4\xbb\xda\x79\x21\xe5\xf9\x13\x6d",16))
printf("strip: ffae9ba31695e1d4, Pass\n");
else
printf("strip: ffae9ba31695e1d4, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006308))=0x000a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006308+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006308+4*2))=0x02020028;
*((unsigned int *)((unsigned long)context_ptr+0x00006308+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x00006150))=0xb9292de4;
*((unsigned int *)((unsigned long)context_ptr+0x00006150+4*1))=0x5be68536;
*((unsigned int *)((unsigned long)context_ptr+0x00006150+4*2))=0x17a8debc;
*((unsigned int *)((unsigned long)context_ptr+0x00006150+4*3))=0x75ffcc84;
*((unsigned int *)((unsigned long)context_ptr+0x00006150+4*4))=0xed7f590e;
*((unsigned int *)((unsigned long)context_ptr+0x00006150+4*5))=0x1970ea10;
*((unsigned int *)((unsigned long)context_ptr+0x00006150+4*6))=0x3c221ec0;
*((unsigned int *)((unsigned long)context_ptr+0x00006150+4*7))=0x96dca98c;
*((unsigned int *)((unsigned long)context_ptr+0x00006150+4*8))=0xa9817ba3;
*((unsigned int *)((unsigned long)context_ptr+0x00006150+4*9))=0x9f9f4b45;
*((unsigned int *)((unsigned long)context_ptr+0x000033a8))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x000033a8+4*1))=0x000063e8;
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
*((unsigned int *)((unsigned long)context_ptr+0x000003a8+4*1))=0x00006150;
*((unsigned int *)((unsigned long)context_ptr+0x000003a8+4*2))=0x00006308;
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
if(!memcmp((unsigned char *)context_ptr+0x00006318,"\x37\xe1\xcb\xc6\x08\x0d\x9e\xf9\x69\x1d\x7a\x40\xba\x29\xaa\xe0",16))
printf("strip: 37e1cbc6080d9ef9, Pass\n");
else
printf("strip: 37e1cbc6080d9ef9, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006318))=0x000a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006318+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006318+4*2))=0x02020029;
*((unsigned int *)((unsigned long)context_ptr+0x00006318+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x00006178))=0x77e836b2;
*((unsigned int *)((unsigned long)context_ptr+0x00006178+4*1))=0xdbbd6d4c;
*((unsigned int *)((unsigned long)context_ptr+0x00006178+4*2))=0x7af721d0;
*((unsigned int *)((unsigned long)context_ptr+0x00006178+4*3))=0x31f02bf3;
*((unsigned int *)((unsigned long)context_ptr+0x00006178+4*4))=0x29d745de;
*((unsigned int *)((unsigned long)context_ptr+0x00006178+4*5))=0xef1fa9da;
*((unsigned int *)((unsigned long)context_ptr+0x00006178+4*6))=0x0dd72f6f;
*((unsigned int *)((unsigned long)context_ptr+0x00006178+4*7))=0xbf17bc09;
*((unsigned int *)((unsigned long)context_ptr+0x00006178+4*8))=0x9023f018;
*((unsigned int *)((unsigned long)context_ptr+0x00006178+4*9))=0x7d185da5;
*((unsigned int *)((unsigned long)context_ptr+0x00006178+4*10))=0x00000055;
*((unsigned int *)((unsigned long)context_ptr+0x000033c0))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x000033c0+4*1))=0x000063f8;
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
*((unsigned int *)((unsigned long)context_ptr+0x000003c0+4*1))=0x00006178;
*((unsigned int *)((unsigned long)context_ptr+0x000003c0+4*2))=0x00006318;
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
if(!memcmp((unsigned char *)context_ptr+0x00006328,"\x95\xc7\x14\xd1\x4d\xa8\xae\xd1\x91\x47\x98\xde\x4f\x2e\x78\x6b",16))
printf("strip: 95c714d14da8aed1, Pass\n");
else
printf("strip: 95c714d14da8aed1, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006328))=0x000a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006328+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006328+4*2))=0x0202002a;
*((unsigned int *)((unsigned long)context_ptr+0x00006328+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x000061a4))=0x23a4ecde;
*((unsigned int *)((unsigned long)context_ptr+0x000061a4+4*1))=0xee21f56b;
*((unsigned int *)((unsigned long)context_ptr+0x000061a4+4*2))=0x17d0975c;
*((unsigned int *)((unsigned long)context_ptr+0x000061a4+4*3))=0xf8e77a1c;
*((unsigned int *)((unsigned long)context_ptr+0x000061a4+4*4))=0x60cb31a7;
*((unsigned int *)((unsigned long)context_ptr+0x000061a4+4*5))=0x84719743;
*((unsigned int *)((unsigned long)context_ptr+0x000061a4+4*6))=0x6edf09f8;
*((unsigned int *)((unsigned long)context_ptr+0x000061a4+4*7))=0x79bce0d8;
*((unsigned int *)((unsigned long)context_ptr+0x000061a4+4*8))=0xb6659885;
*((unsigned int *)((unsigned long)context_ptr+0x000061a4+4*9))=0x90f456da;
*((unsigned int *)((unsigned long)context_ptr+0x000061a4+4*10))=0x0000294b;
*((unsigned int *)((unsigned long)context_ptr+0x000033d8))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x000033d8+4*1))=0x00006408;
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
*((unsigned int *)((unsigned long)context_ptr+0x000003d8+4*1))=0x000061a4;
*((unsigned int *)((unsigned long)context_ptr+0x000003d8+4*2))=0x00006328;
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
if(!memcmp((unsigned char *)context_ptr+0x00006208,"\x72\x92\x40\x1c\x1f\x77\xca\xe4\x35\x11\x12\x53\x9d\x7e\xaa\xd7",16))
printf("strip: 7292401c1f77cae4, Pass\n");
else
printf("strip: 7292401c1f77cae4, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000061d0))=0x000a0012;
*((unsigned int *)((unsigned long)context_ptr+0x000061d0+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000061d0+4*2))=0x0202002b;
*((unsigned int *)((unsigned long)context_ptr+0x000061d0+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x000061e0))=0x0b03a589;
*((unsigned int *)((unsigned long)context_ptr+0x000061e0+4*1))=0xbb996417;
*((unsigned int *)((unsigned long)context_ptr+0x000061e0+4*2))=0x64dd1ba6;
*((unsigned int *)((unsigned long)context_ptr+0x000061e0+4*3))=0xab612bd0;
*((unsigned int *)((unsigned long)context_ptr+0x000061e0+4*4))=0xcfec84a1;
*((unsigned int *)((unsigned long)context_ptr+0x000061e0+4*5))=0x836aad98;
*((unsigned int *)((unsigned long)context_ptr+0x000061e0+4*6))=0x7533d6a1;
*((unsigned int *)((unsigned long)context_ptr+0x000061e0+4*7))=0x1e09322f;
*((unsigned int *)((unsigned long)context_ptr+0x000061e0+4*8))=0x244e54c1;
*((unsigned int *)((unsigned long)context_ptr+0x000061e0+4*9))=0x610e6a93;
*((unsigned int *)((unsigned long)context_ptr+0x000061e0+4*10))=0x00f9c1ce;
*((unsigned int *)((unsigned long)context_ptr+0x000033f0))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x000033f0+4*1))=0x00006418;
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
*((unsigned int *)((unsigned long)context_ptr+0x000003f0+4*1))=0x000061e0;
*((unsigned int *)((unsigned long)context_ptr+0x000003f0+4*2))=0x000061d0;
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
if(!memcmp((unsigned char *)context_ptr+0x00006338,"\xb0\xb5\xae\x3e\xe5\xbf\x75\x09\xc3\x29\x77\xa4\x8b\x31\xad\xb7",16))
printf("strip: b0b5ae3ee5bf7509, Pass\n");
else
printf("strip: b0b5ae3ee5bf7509, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006338))=0x000a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006338+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006338+4*2))=0x0202002c;
*((unsigned int *)((unsigned long)context_ptr+0x00006338+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x0000620c))=0x4bbdd849;
*((unsigned int *)((unsigned long)context_ptr+0x0000620c+4*1))=0xd9f04b7c;
*((unsigned int *)((unsigned long)context_ptr+0x0000620c+4*2))=0xcc13b089;
*((unsigned int *)((unsigned long)context_ptr+0x0000620c+4*3))=0xe353445b;
*((unsigned int *)((unsigned long)context_ptr+0x0000620c+4*4))=0xa076fc1a;
*((unsigned int *)((unsigned long)context_ptr+0x0000620c+4*5))=0x66c41081;
*((unsigned int *)((unsigned long)context_ptr+0x0000620c+4*6))=0x244fd27b;
*((unsigned int *)((unsigned long)context_ptr+0x0000620c+4*7))=0x9710b00b;
*((unsigned int *)((unsigned long)context_ptr+0x0000620c+4*8))=0x4a641c11;
*((unsigned int *)((unsigned long)context_ptr+0x0000620c+4*9))=0xf6f2f11b;
*((unsigned int *)((unsigned long)context_ptr+0x0000620c+4*10))=0x6790e8fa;
*((unsigned int *)((unsigned long)context_ptr+0x00003408))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003408+4*1))=0x00006238;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000408+4*1))=0x0000620c;
*((unsigned int *)((unsigned long)context_ptr+0x00000408+4*2))=0x00006338;
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
if(!memcmp((unsigned char *)context_ptr+0x00006348,"\x10\xa3\xd1\xf1\x8f\xad\x01\x2a\xdc\x80\x51\xb5\xc7\x4b\xc9\xe4",16))
printf("strip: 10a3d1f18fad012a, Pass\n");
else
printf("strip: 10a3d1f18fad012a, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006348))=0x000a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006348+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006348+4*2))=0x0202002d;
*((unsigned int *)((unsigned long)context_ptr+0x00006348+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x00006428))=0x903ea732;
*((unsigned int *)((unsigned long)context_ptr+0x00006428+4*1))=0xa251aac3;
*((unsigned int *)((unsigned long)context_ptr+0x00006428+4*2))=0xa17505a0;
*((unsigned int *)((unsigned long)context_ptr+0x00006428+4*3))=0x02e92961;
*((unsigned int *)((unsigned long)context_ptr+0x00006428+4*4))=0xe9fd2add;
*((unsigned int *)((unsigned long)context_ptr+0x00006428+4*5))=0xddaac417;
*((unsigned int *)((unsigned long)context_ptr+0x00006428+4*6))=0xbcca4f7f;
*((unsigned int *)((unsigned long)context_ptr+0x00006428+4*7))=0x7fc4fc89;
*((unsigned int *)((unsigned long)context_ptr+0x00006428+4*8))=0x0cd781ed;
*((unsigned int *)((unsigned long)context_ptr+0x00006428+4*9))=0x233b3621;
*((unsigned int *)((unsigned long)context_ptr+0x00006428+4*10))=0xb9978f0a;
*((unsigned int *)((unsigned long)context_ptr+0x00006428+4*11))=0x0000009d;
*((unsigned int *)((unsigned long)context_ptr+0x00003420))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003420+4*1))=0x00006248;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000420+4*1))=0x00006428;
*((unsigned int *)((unsigned long)context_ptr+0x00000420+4*2))=0x00006348;
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
if(!memcmp((unsigned char *)context_ptr+0x00006278,"\xb5\x08\x72\x72\xfc\xfe\x65\xa7\xc4\x71\x43\x66\xc9\x9d\x1b\xe0",16))
printf("strip: b5087272fcfe65a7, Pass\n");
else
printf("strip: b5087272fcfe65a7, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006018))=0x000a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006018+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006018+4*2))=0x0202002e;
*((unsigned int *)((unsigned long)context_ptr+0x00006018+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x00006258))=0x0d2caf15;
*((unsigned int *)((unsigned long)context_ptr+0x00006258+4*1))=0x0e55f740;
*((unsigned int *)((unsigned long)context_ptr+0x00006258+4*2))=0x79482cab;
*((unsigned int *)((unsigned long)context_ptr+0x00006258+4*3))=0xc2ec4d8a;
*((unsigned int *)((unsigned long)context_ptr+0x00006258+4*4))=0xd4d113a0;
*((unsigned int *)((unsigned long)context_ptr+0x00006258+4*5))=0xe62cd4ce;
*((unsigned int *)((unsigned long)context_ptr+0x00006258+4*6))=0x2800434b;
*((unsigned int *)((unsigned long)context_ptr+0x00006258+4*7))=0x0cdf3b58;
*((unsigned int *)((unsigned long)context_ptr+0x00006258+4*8))=0xd5dd6071;
*((unsigned int *)((unsigned long)context_ptr+0x00006258+4*9))=0x4075ad53;
*((unsigned int *)((unsigned long)context_ptr+0x00006258+4*10))=0xbcb277b2;
*((unsigned int *)((unsigned long)context_ptr+0x00006258+4*11))=0x0000438f;
*((unsigned int *)((unsigned long)context_ptr+0x00003438))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003438+4*1))=0x00006358;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000438+4*1))=0x00006258;
*((unsigned int *)((unsigned long)context_ptr+0x00000438+4*2))=0x00006018;
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
if(!memcmp((unsigned char *)context_ptr+0x00006288,"\x78\x97\x40\x04\xb3\x30\xef\x67\x98\x21\x49\x40\x43\x03\x0a\x9f",16))
printf("strip: 78974004b330ef67, Pass\n");
else
printf("strip: 78974004b330ef67, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006288))=0x000a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006288+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006288+4*2))=0x0202002f;
*((unsigned int *)((unsigned long)context_ptr+0x00006288+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x00006368))=0x2a18a095;
*((unsigned int *)((unsigned long)context_ptr+0x00006368+4*1))=0x6b2f4341;
*((unsigned int *)((unsigned long)context_ptr+0x00006368+4*2))=0x2ddb2618;
*((unsigned int *)((unsigned long)context_ptr+0x00006368+4*3))=0x44cb1472;
*((unsigned int *)((unsigned long)context_ptr+0x00006368+4*4))=0x3469d1a9;
*((unsigned int *)((unsigned long)context_ptr+0x00006368+4*5))=0xa8987528;
*((unsigned int *)((unsigned long)context_ptr+0x00006368+4*6))=0x22003e96;
*((unsigned int *)((unsigned long)context_ptr+0x00006368+4*7))=0xfa91f870;
*((unsigned int *)((unsigned long)context_ptr+0x00006368+4*8))=0xb04afed7;
*((unsigned int *)((unsigned long)context_ptr+0x00006368+4*9))=0x679dde6e;
*((unsigned int *)((unsigned long)context_ptr+0x00006368+4*10))=0x6c7ed7f1;
*((unsigned int *)((unsigned long)context_ptr+0x00006368+4*11))=0x004f6767;
*((unsigned int *)((unsigned long)context_ptr+0x00003450))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003450+4*1))=0x00006008;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000450+4*1))=0x00006368;
*((unsigned int *)((unsigned long)context_ptr+0x00000450+4*2))=0x00006288;
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
if(!memcmp((unsigned char *)context_ptr+0x0000604c,"\xef\x49\x94\x9d\xe1\x9f\x64\x89\x55\x0f\xca\xce\xb6\xa2\x96\x0b",16))
printf("strip: ef49949de19f6489, Pass\n");
else
printf("strip: ef49949de19f6489, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006298))=0x000a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006298+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006298+4*2))=0x02020030;
*((unsigned int *)((unsigned long)context_ptr+0x00006298+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x00006028))=0xf1472f49;
*((unsigned int *)((unsigned long)context_ptr+0x00006028+4*1))=0x9855695f;
*((unsigned int *)((unsigned long)context_ptr+0x00006028+4*2))=0x8e1b4286;
*((unsigned int *)((unsigned long)context_ptr+0x00006028+4*3))=0x6c570e8e;
*((unsigned int *)((unsigned long)context_ptr+0x00006028+4*4))=0xcdab517b;
*((unsigned int *)((unsigned long)context_ptr+0x00006028+4*5))=0x97aa6b1e;
*((unsigned int *)((unsigned long)context_ptr+0x00006028+4*6))=0xe38bdedf;
*((unsigned int *)((unsigned long)context_ptr+0x00006028+4*7))=0x620226ce;
*((unsigned int *)((unsigned long)context_ptr+0x00006028+4*8))=0x84cf075d;
*((unsigned int *)((unsigned long)context_ptr+0x00006028+4*9))=0x66ced5f9;
*((unsigned int *)((unsigned long)context_ptr+0x00006028+4*10))=0x8d1ab6f1;
*((unsigned int *)((unsigned long)context_ptr+0x00006028+4*11))=0x0a67a436;
*((unsigned int *)((unsigned long)context_ptr+0x00003468))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003468+4*1))=0x00006458;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000468+4*1))=0x00006028;
*((unsigned int *)((unsigned long)context_ptr+0x00000468+4*2))=0x00006298;
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
if(!memcmp((unsigned char *)context_ptr+0x00006080,"\x86\x38\x4e\xf1\xae\xf4\x6a\x21\xab\x62\xe9\x7c\xb5\xd1\x0e\x59",16))
printf("strip: 86384ef1aef46a21, Pass\n");
else
printf("strip: 86384ef1aef46a21, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000062a8))=0x000a0012;
*((unsigned int *)((unsigned long)context_ptr+0x000062a8+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000062a8+4*2))=0x02020031;
*((unsigned int *)((unsigned long)context_ptr+0x000062a8+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x00006058))=0x4e46db58;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*1))=0x3936fade;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*2))=0x6dd00694;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*3))=0x8ccb06bb;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*4))=0x9f680c05;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*5))=0x61e6a473;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*6))=0x560bcb6b;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*7))=0xa9aca70f;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*8))=0xa103be9e;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*9))=0x08c1d5a1;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*10))=0x1b476997;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*11))=0x7b3d271f;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*12))=0x0000009a;
*((unsigned int *)((unsigned long)context_ptr+0x00003480))=0x04c00010;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000480+4*2))=0x000062a8;
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
if(!memcmp((unsigned char *)context_ptr+0x00006398,"\xde\x60\xad\x56\xa9\x13\xa7\x6f\x90\x57\x1c\xa7\xb8\xe3\xc4\x94",16))
printf("strip: de60ad56a913a76f, Pass\n");
else
printf("strip: de60ad56a913a76f, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006398))=0x000a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006398+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006398+4*2))=0x02020032;
*((unsigned int *)((unsigned long)context_ptr+0x00006398+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x00006478))=0x9d261603;
*((unsigned int *)((unsigned long)context_ptr+0x00006478+4*1))=0x55dc2a8f;
*((unsigned int *)((unsigned long)context_ptr+0x00006478+4*2))=0x7cc04a23;
*((unsigned int *)((unsigned long)context_ptr+0x00006478+4*3))=0x3f9e44a3;
*((unsigned int *)((unsigned long)context_ptr+0x00006478+4*4))=0x4d71b703;
*((unsigned int *)((unsigned long)context_ptr+0x00006478+4*5))=0xf8ce6186;
*((unsigned int *)((unsigned long)context_ptr+0x00006478+4*6))=0x02a709a6;
*((unsigned int *)((unsigned long)context_ptr+0x00006478+4*7))=0x06dd1766;
*((unsigned int *)((unsigned long)context_ptr+0x00006478+4*8))=0x428276ad;
*((unsigned int *)((unsigned long)context_ptr+0x00006478+4*9))=0x7d736e60;
*((unsigned int *)((unsigned long)context_ptr+0x00006478+4*10))=0x84dca1d5;
*((unsigned int *)((unsigned long)context_ptr+0x00006478+4*11))=0xbcb6a086;
*((unsigned int *)((unsigned long)context_ptr+0x00006478+4*12))=0x0000668f;
*((unsigned int *)((unsigned long)context_ptr+0x00003498))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003498+4*1))=0x000062b8;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000498+4*1))=0x00006478;
*((unsigned int *)((unsigned long)context_ptr+0x00000498+4*2))=0x00006398;
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
if(!memcmp((unsigned char *)context_ptr+0x000063a8,"\xf0\xc7\xba\x75\x07\xc3\x43\xa9\x0b\x8f\xc1\x37\x11\xa8\xf0\x32",16))
printf("strip: f0c7ba7507c343a9, Pass\n");
else
printf("strip: f0c7ba7507c343a9, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000063a8))=0x000a0012;
*((unsigned int *)((unsigned long)context_ptr+0x000063a8+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000063a8+4*2))=0x02020033;
*((unsigned int *)((unsigned long)context_ptr+0x000063a8+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x0000608c))=0x2281b971;
*((unsigned int *)((unsigned long)context_ptr+0x0000608c+4*1))=0x8eedb88a;
*((unsigned int *)((unsigned long)context_ptr+0x0000608c+4*2))=0x48b18343;
*((unsigned int *)((unsigned long)context_ptr+0x0000608c+4*3))=0x344c3121;
*((unsigned int *)((unsigned long)context_ptr+0x0000608c+4*4))=0xb06f0a4b;
*((unsigned int *)((unsigned long)context_ptr+0x0000608c+4*5))=0x6b1a2a02;
*((unsigned int *)((unsigned long)context_ptr+0x0000608c+4*6))=0x5a6644df;
*((unsigned int *)((unsigned long)context_ptr+0x0000608c+4*7))=0x0a371727;
*((unsigned int *)((unsigned long)context_ptr+0x0000608c+4*8))=0xfd47c264;
*((unsigned int *)((unsigned long)context_ptr+0x0000608c+4*9))=0x9191c181;
*((unsigned int *)((unsigned long)context_ptr+0x0000608c+4*10))=0x2934c8c8;
*((unsigned int *)((unsigned long)context_ptr+0x0000608c+4*11))=0x3b143b2f;
*((unsigned int *)((unsigned long)context_ptr+0x0000608c+4*12))=0x0007a165;
*((unsigned int *)((unsigned long)context_ptr+0x000034b0))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x000034b0+4*1))=0x000062c8;
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
*((unsigned int *)((unsigned long)context_ptr+0x000004b0+4*1))=0x0000608c;
*((unsigned int *)((unsigned long)context_ptr+0x000004b0+4*2))=0x000063a8;
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
if(!memcmp((unsigned char *)context_ptr+0x000063b8,"\xcb\x0a\x4e\xf9\xfa\x5a\x10\x06\xc7\x7b\xd5\x71\x0b\x92\xab\x4c",16))
printf("strip: cb0a4ef9fa5a1006, Pass\n");
else
printf("strip: cb0a4ef9fa5a1006, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000063b8))=0x000a0012;
*((unsigned int *)((unsigned long)context_ptr+0x000063b8+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000063b8+4*2))=0x02020034;
*((unsigned int *)((unsigned long)context_ptr+0x000063b8+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x000060c0))=0xe6a40147;
*((unsigned int *)((unsigned long)context_ptr+0x000060c0+4*1))=0x08b36f5a;
*((unsigned int *)((unsigned long)context_ptr+0x000060c0+4*2))=0x0ba6c53f;
*((unsigned int *)((unsigned long)context_ptr+0x000060c0+4*3))=0xf01d9860;
*((unsigned int *)((unsigned long)context_ptr+0x000060c0+4*4))=0x40119b2c;
*((unsigned int *)((unsigned long)context_ptr+0x000060c0+4*5))=0xe4fac325;
*((unsigned int *)((unsigned long)context_ptr+0x000060c0+4*6))=0xa8e8a437;
*((unsigned int *)((unsigned long)context_ptr+0x000060c0+4*7))=0xa554720f;
*((unsigned int *)((unsigned long)context_ptr+0x000060c0+4*8))=0x0e0ca80f;
*((unsigned int *)((unsigned long)context_ptr+0x000060c0+4*9))=0x43c4dd3a;
*((unsigned int *)((unsigned long)context_ptr+0x000060c0+4*10))=0x8eee4202;
*((unsigned int *)((unsigned long)context_ptr+0x000060c0+4*11))=0xd8a1b914;
*((unsigned int *)((unsigned long)context_ptr+0x000060c0+4*12))=0xe0add8fa;
*((unsigned int *)((unsigned long)context_ptr+0x000034c8))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x000034c8+4*1))=0x000062d8;
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
*((unsigned int *)((unsigned long)context_ptr+0x000004c8+4*1))=0x000060c0;
*((unsigned int *)((unsigned long)context_ptr+0x000004c8+4*2))=0x000063b8;
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
if(!memcmp((unsigned char *)context_ptr+0x000063c8,"\x40\x39\xe5\xb1\xc7\xc9\x66\x37\xbf\x02\x9e\xca\x80\x1f\xac\x20",16))
printf("strip: 4039e5b1c7c96637, Pass\n");
else
printf("strip: 4039e5b1c7c96637, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000063c8))=0x000a0012;
*((unsigned int *)((unsigned long)context_ptr+0x000063c8+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000063c8+4*2))=0x02020035;
*((unsigned int *)((unsigned long)context_ptr+0x000063c8+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x000064ac))=0x6cd0cbe6;
*((unsigned int *)((unsigned long)context_ptr+0x000064ac+4*1))=0x6c50bae2;
*((unsigned int *)((unsigned long)context_ptr+0x000064ac+4*2))=0x605fd93d;
*((unsigned int *)((unsigned long)context_ptr+0x000064ac+4*3))=0xd1488f63;
*((unsigned int *)((unsigned long)context_ptr+0x000064ac+4*4))=0x6011caab;
*((unsigned int *)((unsigned long)context_ptr+0x000064ac+4*5))=0xda563135;
*((unsigned int *)((unsigned long)context_ptr+0x000064ac+4*6))=0xc9d91060;
*((unsigned int *)((unsigned long)context_ptr+0x000064ac+4*7))=0x5b270b8c;
*((unsigned int *)((unsigned long)context_ptr+0x000064ac+4*8))=0xf7c44c6a;
*((unsigned int *)((unsigned long)context_ptr+0x000064ac+4*9))=0x23732b6d;
*((unsigned int *)((unsigned long)context_ptr+0x000064ac+4*10))=0x5afb6876;
*((unsigned int *)((unsigned long)context_ptr+0x000064ac+4*11))=0xb2b4ee1f;
*((unsigned int *)((unsigned long)context_ptr+0x000064ac+4*12))=0x4ab63453;
*((unsigned int *)((unsigned long)context_ptr+0x000064ac+4*13))=0x0000009d;
*((unsigned int *)((unsigned long)context_ptr+0x000034e0))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x000034e0+4*1))=0x000062e8;
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
*((unsigned int *)((unsigned long)context_ptr+0x000004e0+4*1))=0x000064ac;
*((unsigned int *)((unsigned long)context_ptr+0x000004e0+4*2))=0x000063c8;
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
if(!memcmp((unsigned char *)context_ptr+0x000063d8,"\x82\x0c\x6b\xd5\x03\x69\xaa\xa8\x14\xf1\xce\xc3\x0b\x1b\x55\xcd",16))
printf("strip: 820c6bd50369aaa8, Pass\n");
else
printf("strip: 820c6bd50369aaa8, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000063d8))=0x000a0012;
*((unsigned int *)((unsigned long)context_ptr+0x000063d8+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000063d8+4*2))=0x02020036;
*((unsigned int *)((unsigned long)context_ptr+0x000063d8+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x000060f4))=0x6fb388c9;
*((unsigned int *)((unsigned long)context_ptr+0x000060f4+4*1))=0x41ffeaeb;
*((unsigned int *)((unsigned long)context_ptr+0x000060f4+4*2))=0x655e9d37;
*((unsigned int *)((unsigned long)context_ptr+0x000060f4+4*3))=0xcedaadc5;
*((unsigned int *)((unsigned long)context_ptr+0x000060f4+4*4))=0xca6c1a7d;
*((unsigned int *)((unsigned long)context_ptr+0x000060f4+4*5))=0xd166d75d;
*((unsigned int *)((unsigned long)context_ptr+0x000060f4+4*6))=0xec01abc2;
*((unsigned int *)((unsigned long)context_ptr+0x000060f4+4*7))=0xdc03175d;
*((unsigned int *)((unsigned long)context_ptr+0x000060f4+4*8))=0xeffc966b;
*((unsigned int *)((unsigned long)context_ptr+0x000060f4+4*9))=0x6ba4bba1;
*((unsigned int *)((unsigned long)context_ptr+0x000060f4+4*10))=0x364c351d;
*((unsigned int *)((unsigned long)context_ptr+0x000060f4+4*11))=0xb23c34ee;
*((unsigned int *)((unsigned long)context_ptr+0x000060f4+4*12))=0xd04ba3f8;
*((unsigned int *)((unsigned long)context_ptr+0x000060f4+4*13))=0x0000a628;
*((unsigned int *)((unsigned long)context_ptr+0x000034f8))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x000034f8+4*1))=0x000062f8;
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
*((unsigned int *)((unsigned long)context_ptr+0x000004f8+4*1))=0x000060f4;
*((unsigned int *)((unsigned long)context_ptr+0x000004f8+4*2))=0x000063d8;
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
if(!memcmp((unsigned char *)context_ptr+0x000063e8,"\xda\x7b\x15\xc5\xa3\x89\x04\xe1\xee\x52\xd8\xf6\x3e\xf6\x6c\x0f",16))
printf("strip: da7b15c5a38904e1, Pass\n");
else
printf("strip: da7b15c5a38904e1, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000063e8))=0x000a0012;
*((unsigned int *)((unsigned long)context_ptr+0x000063e8+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000063e8+4*2))=0x02020037;
*((unsigned int *)((unsigned long)context_ptr+0x000063e8+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x0000612c))=0x45fefbbd;
*((unsigned int *)((unsigned long)context_ptr+0x0000612c+4*1))=0x26b7eb58;
*((unsigned int *)((unsigned long)context_ptr+0x0000612c+4*2))=0x9d3431c9;
*((unsigned int *)((unsigned long)context_ptr+0x0000612c+4*3))=0xb0296135;
*((unsigned int *)((unsigned long)context_ptr+0x0000612c+4*4))=0xfc18e89d;
*((unsigned int *)((unsigned long)context_ptr+0x0000612c+4*5))=0xf259074e;
*((unsigned int *)((unsigned long)context_ptr+0x0000612c+4*6))=0xad467e4a;
*((unsigned int *)((unsigned long)context_ptr+0x0000612c+4*7))=0xa01bec5f;
*((unsigned int *)((unsigned long)context_ptr+0x0000612c+4*8))=0xc6885efc;
*((unsigned int *)((unsigned long)context_ptr+0x0000612c+4*9))=0xe1da7925;
*((unsigned int *)((unsigned long)context_ptr+0x0000612c+4*10))=0xae88cc86;
*((unsigned int *)((unsigned long)context_ptr+0x0000612c+4*11))=0x0b1713cf;
*((unsigned int *)((unsigned long)context_ptr+0x0000612c+4*12))=0x5b8138e5;
*((unsigned int *)((unsigned long)context_ptr+0x0000612c+4*13))=0x00de5963;
*((unsigned int *)((unsigned long)context_ptr+0x00003510))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003510+4*1))=0x00006308;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000510+4*1))=0x0000612c;
*((unsigned int *)((unsigned long)context_ptr+0x00000510+4*2))=0x000063e8;
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
if(!memcmp((unsigned char *)context_ptr+0x000063f8,"\x0c\xe4\x78\xce\xac\xff\x1d\x8c\xe6\xff\xb1\xa8\x1e\xba\x65\x0d",16))
printf("strip: 0ce478ceacff1d8c, Pass\n");
else
printf("strip: 0ce478ceacff1d8c, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000063f8))=0x000a0012;
*((unsigned int *)((unsigned long)context_ptr+0x000063f8+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000063f8+4*2))=0x02020038;
*((unsigned int *)((unsigned long)context_ptr+0x000063f8+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x00006164))=0x50c89075;
*((unsigned int *)((unsigned long)context_ptr+0x00006164+4*1))=0xc67a306d;
*((unsigned int *)((unsigned long)context_ptr+0x00006164+4*2))=0x2928d80a;
*((unsigned int *)((unsigned long)context_ptr+0x00006164+4*3))=0xd9afbd36;
*((unsigned int *)((unsigned long)context_ptr+0x00006164+4*4))=0x2929e730;
*((unsigned int *)((unsigned long)context_ptr+0x00006164+4*5))=0xacc2556b;
*((unsigned int *)((unsigned long)context_ptr+0x00006164+4*6))=0x1a861c0f;
*((unsigned int *)((unsigned long)context_ptr+0x00006164+4*7))=0x029eb78f;
*((unsigned int *)((unsigned long)context_ptr+0x00006164+4*8))=0x867541ef;
*((unsigned int *)((unsigned long)context_ptr+0x00006164+4*9))=0xd6a84ffa;
*((unsigned int *)((unsigned long)context_ptr+0x00006164+4*10))=0x21473990;
*((unsigned int *)((unsigned long)context_ptr+0x00006164+4*11))=0xeb547ebb;
*((unsigned int *)((unsigned long)context_ptr+0x00006164+4*12))=0x649e2033;
*((unsigned int *)((unsigned long)context_ptr+0x00006164+4*13))=0x049b9661;
*((unsigned int *)((unsigned long)context_ptr+0x00003528))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003528+4*1))=0x00006318;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000528+4*1))=0x00006164;
*((unsigned int *)((unsigned long)context_ptr+0x00000528+4*2))=0x000063f8;
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
if(!memcmp((unsigned char *)context_ptr+0x00006408,"\x4e\xb6\xdf\x18\xfb\xc8\x4c\x2a\xc1\x83\x4d\x29\xf7\xff\x58\xb1",16))
printf("strip: 4eb6df18fbc84c2a, Pass\n");
else
printf("strip: 4eb6df18fbc84c2a, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006408))=0x000a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006408+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006408+4*2))=0x02020039;
*((unsigned int *)((unsigned long)context_ptr+0x00006408+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x000064e4))=0xb2b5e99c;
*((unsigned int *)((unsigned long)context_ptr+0x000064e4+4*1))=0xdd8bb8ec;
*((unsigned int *)((unsigned long)context_ptr+0x000064e4+4*2))=0x7f39edeb;
*((unsigned int *)((unsigned long)context_ptr+0x000064e4+4*3))=0x9a690ca3;
*((unsigned int *)((unsigned long)context_ptr+0x000064e4+4*4))=0x50520ad7;
*((unsigned int *)((unsigned long)context_ptr+0x000064e4+4*5))=0x7dfd5329;
*((unsigned int *)((unsigned long)context_ptr+0x000064e4+4*6))=0xebfcc912;
*((unsigned int *)((unsigned long)context_ptr+0x000064e4+4*7))=0x92d2679c;
*((unsigned int *)((unsigned long)context_ptr+0x000064e4+4*8))=0xb279aa2d;
*((unsigned int *)((unsigned long)context_ptr+0x000064e4+4*9))=0x4a4d4a34;
*((unsigned int *)((unsigned long)context_ptr+0x000064e4+4*10))=0x03aa59b4;
*((unsigned int *)((unsigned long)context_ptr+0x000064e4+4*11))=0x0cea7706;
*((unsigned int *)((unsigned long)context_ptr+0x000064e4+4*12))=0x124fff15;
*((unsigned int *)((unsigned long)context_ptr+0x000064e4+4*13))=0x96391410;
*((unsigned int *)((unsigned long)context_ptr+0x000064e4+4*14))=0x00000008;
*((unsigned int *)((unsigned long)context_ptr+0x00003540))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003540+4*1))=0x00006328;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000540+4*1))=0x000064e4;
*((unsigned int *)((unsigned long)context_ptr+0x00000540+4*2))=0x00006408;
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
if(!memcmp((unsigned char *)context_ptr+0x00006418,"\xa9\x78\xc3\x94\xcb\xd9\x86\xac\x05\x25\x4c\xeb\xb4\xc5\x57\x39",16))
printf("strip: a978c394cbd986ac, Pass\n");
else
printf("strip: a978c394cbd986ac, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006418))=0x000a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006418+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006418+4*2))=0x0202003a;
*((unsigned int *)((unsigned long)context_ptr+0x00006418+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x0000619c))=0x8c8a0fe1;
*((unsigned int *)((unsigned long)context_ptr+0x0000619c+4*1))=0xaa795edd;
*((unsigned int *)((unsigned long)context_ptr+0x0000619c+4*2))=0x3d73a239;
*((unsigned int *)((unsigned long)context_ptr+0x0000619c+4*3))=0x48ad973f;
*((unsigned int *)((unsigned long)context_ptr+0x0000619c+4*4))=0x9758f762;
*((unsigned int *)((unsigned long)context_ptr+0x0000619c+4*5))=0x5f3b6a74;
*((unsigned int *)((unsigned long)context_ptr+0x0000619c+4*6))=0xf4ff74d4;
*((unsigned int *)((unsigned long)context_ptr+0x0000619c+4*7))=0x09b42142;
*((unsigned int *)((unsigned long)context_ptr+0x0000619c+4*8))=0x753c4a32;
*((unsigned int *)((unsigned long)context_ptr+0x0000619c+4*9))=0x2e527cf3;
*((unsigned int *)((unsigned long)context_ptr+0x0000619c+4*10))=0x89380080;
*((unsigned int *)((unsigned long)context_ptr+0x0000619c+4*11))=0x4f555fdd;
*((unsigned int *)((unsigned long)context_ptr+0x0000619c+4*12))=0xace683dd;
*((unsigned int *)((unsigned long)context_ptr+0x0000619c+4*13))=0x0e156341;
*((unsigned int *)((unsigned long)context_ptr+0x0000619c+4*14))=0x000095ed;
*((unsigned int *)((unsigned long)context_ptr+0x00003558))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003558+4*1))=0x000061d8;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000558+4*1))=0x0000619c;
*((unsigned int *)((unsigned long)context_ptr+0x00000558+4*2))=0x00006418;
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
if(!memcmp((unsigned char *)context_ptr+0x00006238,"\xe7\xcd\x29\xb9\xff\x02\xbb\xb5\x51\x84\xd6\x60\x90\xcc\x5e\x6d",16))
printf("strip: e7cd29b9ff02bbb5, Pass\n");
else
printf("strip: e7cd29b9ff02bbb5, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006338))=0x000a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006338+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006338+4*2))=0x0202003b;
*((unsigned int *)((unsigned long)context_ptr+0x00006338+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x000061e8))=0x29e92046;
*((unsigned int *)((unsigned long)context_ptr+0x000061e8+4*1))=0xc1dc8057;
*((unsigned int *)((unsigned long)context_ptr+0x000061e8+4*2))=0x3183fa97;
*((unsigned int *)((unsigned long)context_ptr+0x000061e8+4*3))=0x7e655f7d;
*((unsigned int *)((unsigned long)context_ptr+0x000061e8+4*4))=0xf0b38bd2;
*((unsigned int *)((unsigned long)context_ptr+0x000061e8+4*5))=0x9fcaba1e;
*((unsigned int *)((unsigned long)context_ptr+0x000061e8+4*6))=0x261850bb;
*((unsigned int *)((unsigned long)context_ptr+0x000061e8+4*7))=0x752e7ed5;
*((unsigned int *)((unsigned long)context_ptr+0x000061e8+4*8))=0x2f067b86;
*((unsigned int *)((unsigned long)context_ptr+0x000061e8+4*9))=0x4fc65799;
*((unsigned int *)((unsigned long)context_ptr+0x000061e8+4*10))=0x4d5290c9;
*((unsigned int *)((unsigned long)context_ptr+0x000061e8+4*11))=0xebc71267;
*((unsigned int *)((unsigned long)context_ptr+0x000061e8+4*12))=0x18c996a3;
*((unsigned int *)((unsigned long)context_ptr+0x000061e8+4*13))=0x9027afbf;
*((unsigned int *)((unsigned long)context_ptr+0x000061e8+4*14))=0x00143dcd;
*((unsigned int *)((unsigned long)context_ptr+0x00003570))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003570+4*1))=0x00006224;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000570+4*1))=0x000061e8;
*((unsigned int *)((unsigned long)context_ptr+0x00000570+4*2))=0x00006338;
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
if(!memcmp((unsigned char *)context_ptr+0x00006248,"\x75\xa0\x47\x7b\x79\xc7\x99\xbd\x33\xa1\xcb\x45\x31\xdd\xdc\xcf",16))
printf("strip: 75a0477b79c799bd, Pass\n");
else
printf("strip: 75a0477b79c799bd, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006348))=0x000a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006348+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006348+4*2))=0x0202003c;
*((unsigned int *)((unsigned long)context_ptr+0x00006348+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x00006520))=0x2731a6f5;
*((unsigned int *)((unsigned long)context_ptr+0x00006520+4*1))=0x5e688756;
*((unsigned int *)((unsigned long)context_ptr+0x00006520+4*2))=0x8263a416;
*((unsigned int *)((unsigned long)context_ptr+0x00006520+4*3))=0xb54bfe0d;
*((unsigned int *)((unsigned long)context_ptr+0x00006520+4*4))=0x5a5f2bcd;
*((unsigned int *)((unsigned long)context_ptr+0x00006520+4*5))=0xa6c1a82b;
*((unsigned int *)((unsigned long)context_ptr+0x00006520+4*6))=0x7f6a17bc;
*((unsigned int *)((unsigned long)context_ptr+0x00006520+4*7))=0x868a74f7;
*((unsigned int *)((unsigned long)context_ptr+0x00006520+4*8))=0xeee4002d;
*((unsigned int *)((unsigned long)context_ptr+0x00006520+4*9))=0x92e12704;
*((unsigned int *)((unsigned long)context_ptr+0x00006520+4*10))=0x42cd8515;
*((unsigned int *)((unsigned long)context_ptr+0x00006520+4*11))=0x0164bc6c;
*((unsigned int *)((unsigned long)context_ptr+0x00006520+4*12))=0x6ab08d48;
*((unsigned int *)((unsigned long)context_ptr+0x00006520+4*13))=0xddf9b451;
*((unsigned int *)((unsigned long)context_ptr+0x00006520+4*14))=0x35a9207e;
*((unsigned int *)((unsigned long)context_ptr+0x00003588))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003588+4*1))=0x00006234;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000588+4*1))=0x00006520;
*((unsigned int *)((unsigned long)context_ptr+0x00000588+4*2))=0x00006348;
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
if(!memcmp((unsigned char *)context_ptr+0x00006358,"\xf1\x71\xb0\x39\x25\x3f\xb7\xa0\xc8\x4f\x7b\xa5\x64\xf9\x66\xc9",16))
printf("strip: f171b039253fb7a0, Pass\n");
else
printf("strip: f171b039253fb7a0, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006358))=0x000a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006358+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006358+4*2))=0x0202003d;
*((unsigned int *)((unsigned long)context_ptr+0x00006358+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x00006244))=0x11202762;
*((unsigned int *)((unsigned long)context_ptr+0x00006244+4*1))=0x775dde0a;
*((unsigned int *)((unsigned long)context_ptr+0x00006244+4*2))=0x5b66cd6f;
*((unsigned int *)((unsigned long)context_ptr+0x00006244+4*3))=0x75a862ad;
*((unsigned int *)((unsigned long)context_ptr+0x00006244+4*4))=0xf1406791;
*((unsigned int *)((unsigned long)context_ptr+0x00006244+4*5))=0xa249a296;
*((unsigned int *)((unsigned long)context_ptr+0x00006244+4*6))=0x418a948d;
*((unsigned int *)((unsigned long)context_ptr+0x00006244+4*7))=0x4d4f14a7;
*((unsigned int *)((unsigned long)context_ptr+0x00006244+4*8))=0xda34006f;
*((unsigned int *)((unsigned long)context_ptr+0x00006244+4*9))=0x839b03ca;
*((unsigned int *)((unsigned long)context_ptr+0x00006244+4*10))=0x615cbd18;
*((unsigned int *)((unsigned long)context_ptr+0x00006244+4*11))=0xd7d59b5d;
*((unsigned int *)((unsigned long)context_ptr+0x00006244+4*12))=0x9f0fe550;
*((unsigned int *)((unsigned long)context_ptr+0x00006244+4*13))=0x6a6af4b3;
*((unsigned int *)((unsigned long)context_ptr+0x00006244+4*14))=0x59f757a0;
*((unsigned int *)((unsigned long)context_ptr+0x00006244+4*15))=0x00000025;
*((unsigned int *)((unsigned long)context_ptr+0x000035a0))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x000035a0+4*1))=0x00006018;
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
*((unsigned int *)((unsigned long)context_ptr+0x000005a0+4*1))=0x00006244;
*((unsigned int *)((unsigned long)context_ptr+0x000005a0+4*2))=0x00006358;
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
if(!memcmp((unsigned char *)context_ptr+0x00006008,"\xfe\x64\xb2\x4b\xb9\x5a\x8b\xdd\x5c\x25\x4c\xad\x6c\x55\x9d\x1b",16))
printf("strip: fe64b24bb95a8bdd, Pass\n");
else
printf("strip: fe64b24bb95a8bdd, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006008))=0x000a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006008+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006008+4*2))=0x0202003e;
*((unsigned int *)((unsigned long)context_ptr+0x00006008+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x0000655c))=0x6ab2fea5;
*((unsigned int *)((unsigned long)context_ptr+0x0000655c+4*1))=0x91737f8a;
*((unsigned int *)((unsigned long)context_ptr+0x0000655c+4*2))=0xe7f61d4f;
*((unsigned int *)((unsigned long)context_ptr+0x0000655c+4*3))=0x77e370b0;
*((unsigned int *)((unsigned long)context_ptr+0x0000655c+4*4))=0xc42deca4;
*((unsigned int *)((unsigned long)context_ptr+0x0000655c+4*5))=0x548f69ef;
*((unsigned int *)((unsigned long)context_ptr+0x0000655c+4*6))=0x643e55ee;
*((unsigned int *)((unsigned long)context_ptr+0x0000655c+4*7))=0xb6182818;
*((unsigned int *)((unsigned long)context_ptr+0x0000655c+4*8))=0x4cb00955;
*((unsigned int *)((unsigned long)context_ptr+0x0000655c+4*9))=0xee95eacf;
*((unsigned int *)((unsigned long)context_ptr+0x0000655c+4*10))=0x05b664ec;
*((unsigned int *)((unsigned long)context_ptr+0x0000655c+4*11))=0x4c91f7a1;
*((unsigned int *)((unsigned long)context_ptr+0x0000655c+4*12))=0x724b618a;
*((unsigned int *)((unsigned long)context_ptr+0x0000655c+4*13))=0x043d7939;
*((unsigned int *)((unsigned long)context_ptr+0x0000655c+4*14))=0x0a4c6c05;
*((unsigned int *)((unsigned long)context_ptr+0x0000655c+4*15))=0x000019d1;
*((unsigned int *)((unsigned long)context_ptr+0x000035b8))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x000035b8+4*1))=0x00006284;
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
*((unsigned int *)((unsigned long)context_ptr+0x000005b8+4*1))=0x0000655c;
*((unsigned int *)((unsigned long)context_ptr+0x000005b8+4*2))=0x00006008;
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
if(!memcmp((unsigned char *)context_ptr+0x00006458,"\xa9\x01\x2c\xf2\xae\x39\xc1\x4c\xea\x05\x5f\x46\xec\x0c\x2f\x7e",16))
printf("strip: a9012cf2ae39c14c, Pass\n");
else
printf("strip: a9012cf2ae39c14c, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006294))=0x000a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006294+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006294+4*2))=0x0202003f;
*((unsigned int *)((unsigned long)context_ptr+0x00006294+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x00006428))=0x12e09348;
*((unsigned int *)((unsigned long)context_ptr+0x00006428+4*1))=0xe3d3b3d3;
*((unsigned int *)((unsigned long)context_ptr+0x00006428+4*2))=0x9218aabe;
*((unsigned int *)((unsigned long)context_ptr+0x00006428+4*3))=0x9b156f08;
*((unsigned int *)((unsigned long)context_ptr+0x00006428+4*4))=0x15aabc08;
*((unsigned int *)((unsigned long)context_ptr+0x00006428+4*5))=0xe8bec521;
*((unsigned int *)((unsigned long)context_ptr+0x00006428+4*6))=0x79f43459;
*((unsigned int *)((unsigned long)context_ptr+0x00006428+4*7))=0x39ce1791;
*((unsigned int *)((unsigned long)context_ptr+0x00006428+4*8))=0x9a2876f3;
*((unsigned int *)((unsigned long)context_ptr+0x00006428+4*9))=0x817c1c3f;
*((unsigned int *)((unsigned long)context_ptr+0x00006428+4*10))=0xd337e6b6;
*((unsigned int *)((unsigned long)context_ptr+0x00006428+4*11))=0x62c02074;
*((unsigned int *)((unsigned long)context_ptr+0x00006428+4*12))=0x943f008f;
*((unsigned int *)((unsigned long)context_ptr+0x00006428+4*13))=0x38862107;
*((unsigned int *)((unsigned long)context_ptr+0x00006428+4*14))=0x5f2ae4b4;
*((unsigned int *)((unsigned long)context_ptr+0x00006428+4*15))=0x00b6f012;
*((unsigned int *)((unsigned long)context_ptr+0x000035d0))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x000035d0+4*1))=0x00006028;
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
*((unsigned int *)((unsigned long)context_ptr+0x000005d0+4*1))=0x00006428;
*((unsigned int *)((unsigned long)context_ptr+0x000005d0+4*2))=0x00006294;
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
if(!memcmp((unsigned char *)context_ptr+0x00006468,"\xbb\x0f\x96\x27\x20\x5b\x63\x77\x08\xdd\x6a\xe0\x38\x6f\xed\x1b",16))
printf("strip: bb0f9627205b6377, Pass\n");
else
printf("strip: bb0f9627205b6377, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006468))=0x000a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006468+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006468+4*2))=0x02020040;
*((unsigned int *)((unsigned long)context_ptr+0x00006468+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x00006038))=0xc7809b0e;
*((unsigned int *)((unsigned long)context_ptr+0x00006038+4*1))=0xd3cd8b79;
*((unsigned int *)((unsigned long)context_ptr+0x00006038+4*2))=0xc5e51953;
*((unsigned int *)((unsigned long)context_ptr+0x00006038+4*3))=0x67dd0f05;
*((unsigned int *)((unsigned long)context_ptr+0x00006038+4*4))=0xfbff9001;
*((unsigned int *)((unsigned long)context_ptr+0x00006038+4*5))=0xd12fbc3e;
*((unsigned int *)((unsigned long)context_ptr+0x00006038+4*6))=0xd4afd19d;
*((unsigned int *)((unsigned long)context_ptr+0x00006038+4*7))=0x1f2f4523;
*((unsigned int *)((unsigned long)context_ptr+0x00006038+4*8))=0x58731538;
*((unsigned int *)((unsigned long)context_ptr+0x00006038+4*9))=0x0bb33202;
*((unsigned int *)((unsigned long)context_ptr+0x00006038+4*10))=0x09eadb04;
*((unsigned int *)((unsigned long)context_ptr+0x00006038+4*11))=0xa0945b42;
*((unsigned int *)((unsigned long)context_ptr+0x00006038+4*12))=0x606645f6;
*((unsigned int *)((unsigned long)context_ptr+0x00006038+4*13))=0xa9e831d6;
*((unsigned int *)((unsigned long)context_ptr+0x00006038+4*14))=0x0b32b87d;
*((unsigned int *)((unsigned long)context_ptr+0x00006038+4*15))=0x9fdf5bdd;
*((unsigned int *)((unsigned long)context_ptr+0x000035e8))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x000035e8+4*1))=0x000062a4;
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
*((unsigned int *)((unsigned long)context_ptr+0x000005e8+4*1))=0x00006038;
*((unsigned int *)((unsigned long)context_ptr+0x000005e8+4*2))=0x00006468;
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
if(!memcmp((unsigned char *)context_ptr+0x000062b8,"\x00\x45\x29\x01\x70\xac\xea\xcd\x9e\x63\xfb\x23\x87\x1e\xc4\x4e",16))
printf("strip: 0045290170aceacd, Pass\n");
else
printf("strip: 0045290170aceacd, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006078))=0x000a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006078+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006078+4*2))=0x02020041;
*((unsigned int *)((unsigned long)context_ptr+0x00006078+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x0000659c))=0xfdc8a886;
*((unsigned int *)((unsigned long)context_ptr+0x0000659c+4*1))=0x3132f146;
*((unsigned int *)((unsigned long)context_ptr+0x0000659c+4*2))=0xe7e614cb;
*((unsigned int *)((unsigned long)context_ptr+0x0000659c+4*3))=0x127ab2b3;
*((unsigned int *)((unsigned long)context_ptr+0x0000659c+4*4))=0x4e96c258;
*((unsigned int *)((unsigned long)context_ptr+0x0000659c+4*5))=0xb388352c;
*((unsigned int *)((unsigned long)context_ptr+0x0000659c+4*6))=0xa2b4c7f1;
*((unsigned int *)((unsigned long)context_ptr+0x0000659c+4*7))=0x66c89cff;
*((unsigned int *)((unsigned long)context_ptr+0x0000659c+4*8))=0x82ca5d23;
*((unsigned int *)((unsigned long)context_ptr+0x0000659c+4*9))=0xbf5c357e;
*((unsigned int *)((unsigned long)context_ptr+0x0000659c+4*10))=0xeef52c6a;
*((unsigned int *)((unsigned long)context_ptr+0x0000659c+4*11))=0x12fc7ddc;
*((unsigned int *)((unsigned long)context_ptr+0x0000659c+4*12))=0x8f5808a7;
*((unsigned int *)((unsigned long)context_ptr+0x0000659c+4*13))=0xe2ef6f7b;
*((unsigned int *)((unsigned long)context_ptr+0x0000659c+4*14))=0xa933c7e3;
*((unsigned int *)((unsigned long)context_ptr+0x0000659c+4*15))=0x9858e35e;
*((unsigned int *)((unsigned long)context_ptr+0x0000659c+4*16))=0x000000d3;
*((unsigned int *)((unsigned long)context_ptr+0x00003600))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003600+4*1))=0x000062b4;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000600+4*1))=0x0000659c;
*((unsigned int *)((unsigned long)context_ptr+0x00000600+4*2))=0x00006078;
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
if(!memcmp((unsigned char *)context_ptr+0x000062c8,"\x3a\xcf\x68\x2a\x43\xe5\x2d\x90\xc7\xa1\x09\x61\xa0\x39\x57\xa5",16))
printf("strip: 3acf682a43e52d90, Pass\n");
else
printf("strip: 3acf682a43e52d90, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000062c4))=0x000a0012;
*((unsigned int *)((unsigned long)context_ptr+0x000062c4+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000062c4+4*2))=0x02020042;
*((unsigned int *)((unsigned long)context_ptr+0x000062c4+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x00006368))=0x877b79d5;
*((unsigned int *)((unsigned long)context_ptr+0x00006368+4*1))=0x46f579a7;
*((unsigned int *)((unsigned long)context_ptr+0x00006368+4*2))=0x3016f809;
*((unsigned int *)((unsigned long)context_ptr+0x00006368+4*3))=0xa750d746;
*((unsigned int *)((unsigned long)context_ptr+0x00006368+4*4))=0x833a8bd8;
*((unsigned int *)((unsigned long)context_ptr+0x00006368+4*5))=0x662e5d05;
*((unsigned int *)((unsigned long)context_ptr+0x00006368+4*6))=0xceb0ab0f;
*((unsigned int *)((unsigned long)context_ptr+0x00006368+4*7))=0xfb251f98;
*((unsigned int *)((unsigned long)context_ptr+0x00006368+4*8))=0x527ca9b2;
*((unsigned int *)((unsigned long)context_ptr+0x00006368+4*9))=0x583ff0d9;
*((unsigned int *)((unsigned long)context_ptr+0x00006368+4*10))=0xbe93fc51;
*((unsigned int *)((unsigned long)context_ptr+0x00006368+4*11))=0xd0be5355;
*((unsigned int *)((unsigned long)context_ptr+0x00006368+4*12))=0x4da6e024;
*((unsigned int *)((unsigned long)context_ptr+0x00006368+4*13))=0x7085f232;
*((unsigned int *)((unsigned long)context_ptr+0x00006368+4*14))=0xe902a94e;
*((unsigned int *)((unsigned long)context_ptr+0x00006368+4*15))=0x990f009d;
*((unsigned int *)((unsigned long)context_ptr+0x00006368+4*16))=0x0000543d;
*((unsigned int *)((unsigned long)context_ptr+0x00003618))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003618+4*1))=0x00006478;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000618+4*1))=0x00006368;
*((unsigned int *)((unsigned long)context_ptr+0x00000618+4*2))=0x000062c4;
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
if(!memcmp((unsigned char *)context_ptr+0x000062d8,"\x7d\x44\x54\x0f\x19\xfb\x81\xee\x14\x6e\x20\xcf\x72\xd1\x3a\x97",16))
printf("strip: 7d44540f19fb81ee, Pass\n");
else
printf("strip: 7d44540f19fb81ee, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000062d4))=0x000a0012;
*((unsigned int *)((unsigned long)context_ptr+0x000062d4+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000062d4+4*2))=0x02020043;
*((unsigned int *)((unsigned long)context_ptr+0x000062d4+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x00006088))=0xc845261c;
*((unsigned int *)((unsigned long)context_ptr+0x00006088+4*1))=0x910aff20;
*((unsigned int *)((unsigned long)context_ptr+0x00006088+4*2))=0x762a8093;
*((unsigned int *)((unsigned long)context_ptr+0x00006088+4*3))=0x4e5e41d9;
*((unsigned int *)((unsigned long)context_ptr+0x00006088+4*4))=0xf5859c63;
*((unsigned int *)((unsigned long)context_ptr+0x00006088+4*5))=0x4b044d78;
*((unsigned int *)((unsigned long)context_ptr+0x00006088+4*6))=0x7b92fed5;
*((unsigned int *)((unsigned long)context_ptr+0x00006088+4*7))=0xcf595462;
*((unsigned int *)((unsigned long)context_ptr+0x00006088+4*8))=0xe1249358;
*((unsigned int *)((unsigned long)context_ptr+0x00006088+4*9))=0x2a40754e;
*((unsigned int *)((unsigned long)context_ptr+0x00006088+4*10))=0x0aedb4f0;
*((unsigned int *)((unsigned long)context_ptr+0x00006088+4*11))=0xb7f6998d;
*((unsigned int *)((unsigned long)context_ptr+0x00006088+4*12))=0x97e544a2;
*((unsigned int *)((unsigned long)context_ptr+0x00006088+4*13))=0x19dca300;
*((unsigned int *)((unsigned long)context_ptr+0x00006088+4*14))=0x630a8b31;
*((unsigned int *)((unsigned long)context_ptr+0x00006088+4*15))=0x19d93e93;
*((unsigned int *)((unsigned long)context_ptr+0x00006088+4*16))=0x00d535cd;
*((unsigned int *)((unsigned long)context_ptr+0x00003630))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003630+4*1))=0x000063ac;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000630+4*1))=0x00006088;
*((unsigned int *)((unsigned long)context_ptr+0x00000630+4*2))=0x000062d4;
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
if(!memcmp((unsigned char *)context_ptr+0x000062e8,"\xb3\xb3\xe5\x74\xaa\x72\x04\xc8\x37\x9b\x07\x3c\x2f\x5a\x12\xe8",16))
printf("strip: b3b3e574aa7204c8, Pass\n");
else
printf("strip: b3b3e574aa7204c8, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000062e4))=0x000a0012;
*((unsigned int *)((unsigned long)context_ptr+0x000062e4+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000062e4+4*2))=0x02020044;
*((unsigned int *)((unsigned long)context_ptr+0x000062e4+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x00006488))=0x6f22b50d;
*((unsigned int *)((unsigned long)context_ptr+0x00006488+4*1))=0x8f34a3cc;
*((unsigned int *)((unsigned long)context_ptr+0x00006488+4*2))=0x271135b7;
*((unsigned int *)((unsigned long)context_ptr+0x00006488+4*3))=0xf4c732c7;
*((unsigned int *)((unsigned long)context_ptr+0x00006488+4*4))=0xbbc8ceb4;
*((unsigned int *)((unsigned long)context_ptr+0x00006488+4*5))=0x667602b1;
*((unsigned int *)((unsigned long)context_ptr+0x00006488+4*6))=0xba70c4c8;
*((unsigned int *)((unsigned long)context_ptr+0x00006488+4*7))=0x7612dc2c;
*((unsigned int *)((unsigned long)context_ptr+0x00006488+4*8))=0x1e62d653;
*((unsigned int *)((unsigned long)context_ptr+0x00006488+4*9))=0xbae92eaf;
*((unsigned int *)((unsigned long)context_ptr+0x00006488+4*10))=0x69f44fbd;
*((unsigned int *)((unsigned long)context_ptr+0x00006488+4*11))=0xefd3a744;
*((unsigned int *)((unsigned long)context_ptr+0x00006488+4*12))=0xed16bd6a;
*((unsigned int *)((unsigned long)context_ptr+0x00006488+4*13))=0x634b8a02;
*((unsigned int *)((unsigned long)context_ptr+0x00006488+4*14))=0x7ace7e71;
*((unsigned int *)((unsigned long)context_ptr+0x00006488+4*15))=0xd25c0681;
*((unsigned int *)((unsigned long)context_ptr+0x00006488+4*16))=0x476ee04e;
*((unsigned int *)((unsigned long)context_ptr+0x00003648))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003648+4*1))=0x000064cc;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000648+4*1))=0x00006488;
*((unsigned int *)((unsigned long)context_ptr+0x00000648+4*2))=0x000062e4;
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
if(!memcmp((unsigned char *)context_ptr+0x000062f8,"\x5d\x73\x46\x06\x89\x8f\x07\x92\x32\x4b\xbd\x95\x34\xfb\x0b\x15",16))
printf("strip: 5d734606898f0792, Pass\n");
else
printf("strip: 5d734606898f0792, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000062f4))=0x000a0012;
*((unsigned int *)((unsigned long)context_ptr+0x000062f4+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000062f4+4*2))=0x02020045;
*((unsigned int *)((unsigned long)context_ptr+0x000062f4+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x000060cc))=0x0553a4cf;
*((unsigned int *)((unsigned long)context_ptr+0x000060cc+4*1))=0x75e18124;
*((unsigned int *)((unsigned long)context_ptr+0x000060cc+4*2))=0xcc21816b;
*((unsigned int *)((unsigned long)context_ptr+0x000060cc+4*3))=0x11e9127d;
*((unsigned int *)((unsigned long)context_ptr+0x000060cc+4*4))=0x538b0007;
*((unsigned int *)((unsigned long)context_ptr+0x000060cc+4*5))=0x12780b10;
*((unsigned int *)((unsigned long)context_ptr+0x000060cc+4*6))=0x074fbe33;
*((unsigned int *)((unsigned long)context_ptr+0x000060cc+4*7))=0xc2a3eef5;
*((unsigned int *)((unsigned long)context_ptr+0x000060cc+4*8))=0xf9a058ed;
*((unsigned int *)((unsigned long)context_ptr+0x000060cc+4*9))=0xea73dc0f;
*((unsigned int *)((unsigned long)context_ptr+0x000060cc+4*10))=0xee840b60;
*((unsigned int *)((unsigned long)context_ptr+0x000060cc+4*11))=0x8dad3d8d;
*((unsigned int *)((unsigned long)context_ptr+0x000060cc+4*12))=0x02383d8d;
*((unsigned int *)((unsigned long)context_ptr+0x000060cc+4*13))=0x73e6c0f8;
*((unsigned int *)((unsigned long)context_ptr+0x000060cc+4*14))=0xdff9793c;
*((unsigned int *)((unsigned long)context_ptr+0x000060cc+4*15))=0x926eadba;
*((unsigned int *)((unsigned long)context_ptr+0x000060cc+4*16))=0xbb113dc2;
*((unsigned int *)((unsigned long)context_ptr+0x000060cc+4*17))=0x0000007b;
*((unsigned int *)((unsigned long)context_ptr+0x00003660))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003660+4*1))=0x00006114;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000660+4*1))=0x000060cc;
*((unsigned int *)((unsigned long)context_ptr+0x00000660+4*2))=0x000062f4;
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
if(!memcmp((unsigned char *)context_ptr+0x00006308,"\x54\x5d\xae\x1f\x3b\x81\x65\x67\x8b\xd3\x24\xca\x3d\x83\xe2\x8f",16))
printf("strip: 545dae1f3b816567, Pass\n");
else
printf("strip: 545dae1f3b816567, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006304))=0x000a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006304+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006304+4*2))=0x02020046;
*((unsigned int *)((unsigned long)context_ptr+0x00006304+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x000065e0))=0x0ea73164;
*((unsigned int *)((unsigned long)context_ptr+0x000065e0+4*1))=0xac058692;
*((unsigned int *)((unsigned long)context_ptr+0x000065e0+4*2))=0xa6893f7f;
*((unsigned int *)((unsigned long)context_ptr+0x000065e0+4*3))=0xea38b59e;
*((unsigned int *)((unsigned long)context_ptr+0x000065e0+4*4))=0x1698467f;
*((unsigned int *)((unsigned long)context_ptr+0x000065e0+4*5))=0x1bd94104;
*((unsigned int *)((unsigned long)context_ptr+0x000065e0+4*6))=0x3a93bf88;
*((unsigned int *)((unsigned long)context_ptr+0x000065e0+4*7))=0x5a1e697d;
*((unsigned int *)((unsigned long)context_ptr+0x000065e0+4*8))=0xd9270cfd;
*((unsigned int *)((unsigned long)context_ptr+0x000065e0+4*9))=0xddd81bda;
*((unsigned int *)((unsigned long)context_ptr+0x000065e0+4*10))=0x067e2c7c;
*((unsigned int *)((unsigned long)context_ptr+0x000065e0+4*11))=0x965431c5;
*((unsigned int *)((unsigned long)context_ptr+0x000065e0+4*12))=0x97623da7;
*((unsigned int *)((unsigned long)context_ptr+0x000065e0+4*13))=0xa685db44;
*((unsigned int *)((unsigned long)context_ptr+0x000065e0+4*14))=0x43d414da;
*((unsigned int *)((unsigned long)context_ptr+0x000065e0+4*15))=0xc06eae35;
*((unsigned int *)((unsigned long)context_ptr+0x000065e0+4*16))=0xbd7aa017;
*((unsigned int *)((unsigned long)context_ptr+0x000065e0+4*17))=0x00001206;
*((unsigned int *)((unsigned long)context_ptr+0x00003678))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003678+4*1))=0x000063bc;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000678+4*1))=0x000065e0;
*((unsigned int *)((unsigned long)context_ptr+0x00000678+4*2))=0x00006304;
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
if(!memcmp((unsigned char *)context_ptr+0x00006318,"\x22\x03\x6e\xb4\xf7\x21\x3d\x7a\x48\xf0\xb1\xb9\x80\x7b\x58\x72",16))
printf("strip: 22036eb4f7213d7a, Pass\n");
else
printf("strip: 22036eb4f7213d7a, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006314))=0x000a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006314+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006314+4*2))=0x02020047;
*((unsigned int *)((unsigned long)context_ptr+0x00006314+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x00006124))=0xf792d718;
*((unsigned int *)((unsigned long)context_ptr+0x00006124+4*1))=0x12c83c34;
*((unsigned int *)((unsigned long)context_ptr+0x00006124+4*2))=0xcaa737a8;
*((unsigned int *)((unsigned long)context_ptr+0x00006124+4*3))=0xb489dbe7;
*((unsigned int *)((unsigned long)context_ptr+0x00006124+4*4))=0x6f9caa59;
*((unsigned int *)((unsigned long)context_ptr+0x00006124+4*5))=0xd2ef7b61;
*((unsigned int *)((unsigned long)context_ptr+0x00006124+4*6))=0xfa66cd01;
*((unsigned int *)((unsigned long)context_ptr+0x00006124+4*7))=0x447dd921;
*((unsigned int *)((unsigned long)context_ptr+0x00006124+4*8))=0x6ac98fec;
*((unsigned int *)((unsigned long)context_ptr+0x00006124+4*9))=0x2d6ae053;
*((unsigned int *)((unsigned long)context_ptr+0x00006124+4*10))=0xace9bea7;
*((unsigned int *)((unsigned long)context_ptr+0x00006124+4*11))=0xd1963151;
*((unsigned int *)((unsigned long)context_ptr+0x00006124+4*12))=0x8fdac51b;
*((unsigned int *)((unsigned long)context_ptr+0x00006124+4*13))=0x4cbefca0;
*((unsigned int *)((unsigned long)context_ptr+0x00006124+4*14))=0xeb5c96cc;
*((unsigned int *)((unsigned long)context_ptr+0x00006124+4*15))=0xe9f89756;
*((unsigned int *)((unsigned long)context_ptr+0x00006124+4*16))=0xac3f59f3;
*((unsigned int *)((unsigned long)context_ptr+0x00006124+4*17))=0x0053e233;
*((unsigned int *)((unsigned long)context_ptr+0x00003690))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003690+4*1))=0x0000616c;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000690+4*1))=0x00006124;
*((unsigned int *)((unsigned long)context_ptr+0x00000690+4*2))=0x00006314;
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
if(!memcmp((unsigned char *)context_ptr+0x00006328,"\x68\x4f\xc4\x6b\x7d\xc1\xa8\xea\x41\x85\x9c\x43\xee\x4b\x0d\x76",16))
printf("strip: 684fc46b7dc1a8ea, Pass\n");
else
printf("strip: 684fc46b7dc1a8ea, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006324))=0x000a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006324+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006324+4*2))=0x02020048;
*((unsigned int *)((unsigned long)context_ptr+0x00006324+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x000063cc))=0x87156a05;
*((unsigned int *)((unsigned long)context_ptr+0x000063cc+4*1))=0x611943f3;
*((unsigned int *)((unsigned long)context_ptr+0x000063cc+4*2))=0x0372e1b5;
*((unsigned int *)((unsigned long)context_ptr+0x000063cc+4*3))=0x367f29ca;
*((unsigned int *)((unsigned long)context_ptr+0x000063cc+4*4))=0x7f25c75a;
*((unsigned int *)((unsigned long)context_ptr+0x000063cc+4*5))=0xaf532f7e;
*((unsigned int *)((unsigned long)context_ptr+0x000063cc+4*6))=0x7013d127;
*((unsigned int *)((unsigned long)context_ptr+0x000063cc+4*7))=0x72be6c88;
*((unsigned int *)((unsigned long)context_ptr+0x000063cc+4*8))=0x471bae89;
*((unsigned int *)((unsigned long)context_ptr+0x000063cc+4*9))=0x307fed94;
*((unsigned int *)((unsigned long)context_ptr+0x000063cc+4*10))=0x971f072f;
*((unsigned int *)((unsigned long)context_ptr+0x000063cc+4*11))=0x4c54281d;
*((unsigned int *)((unsigned long)context_ptr+0x000063cc+4*12))=0x578b1ce4;
*((unsigned int *)((unsigned long)context_ptr+0x000063cc+4*13))=0x5625e2a0;
*((unsigned int *)((unsigned long)context_ptr+0x000063cc+4*14))=0x01493fc5;
*((unsigned int *)((unsigned long)context_ptr+0x000063cc+4*15))=0xa39fc740;
*((unsigned int *)((unsigned long)context_ptr+0x000063cc+4*16))=0x06f4b435;
*((unsigned int *)((unsigned long)context_ptr+0x000063cc+4*17))=0xc9826773;
*((unsigned int *)((unsigned long)context_ptr+0x000036a8))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x000036a8+4*1))=0x0000617c;
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
*((unsigned int *)((unsigned long)context_ptr+0x000006a8+4*1))=0x000063cc;
*((unsigned int *)((unsigned long)context_ptr+0x000006a8+4*2))=0x00006324;
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
if(!memcmp((unsigned char *)context_ptr+0x000061d8,"\xa0\xcf\xfa\x3e\xd1\x99\xc4\xfe\x5c\xd8\x91\xa4\xd9\x0a\x60\xb0",16))
printf("strip: a0cffa3ed199c4fe, Pass\n");
else
printf("strip: a0cffa3ed199c4fe, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006414))=0x000a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006414+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006414+4*2))=0x02020049;
*((unsigned int *)((unsigned long)context_ptr+0x00006414+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x0000618c))=0x7efd976f;
*((unsigned int *)((unsigned long)context_ptr+0x0000618c+4*1))=0x9e4792d2;
*((unsigned int *)((unsigned long)context_ptr+0x0000618c+4*2))=0x07b14820;
*((unsigned int *)((unsigned long)context_ptr+0x0000618c+4*3))=0xb28cffbd;
*((unsigned int *)((unsigned long)context_ptr+0x0000618c+4*4))=0xee240e5f;
*((unsigned int *)((unsigned long)context_ptr+0x0000618c+4*5))=0x0fcc1974;
*((unsigned int *)((unsigned long)context_ptr+0x0000618c+4*6))=0x2cea613a;
*((unsigned int *)((unsigned long)context_ptr+0x0000618c+4*7))=0xf05d82c3;
*((unsigned int *)((unsigned long)context_ptr+0x0000618c+4*8))=0x7da91207;
*((unsigned int *)((unsigned long)context_ptr+0x0000618c+4*9))=0x198b19bd;
*((unsigned int *)((unsigned long)context_ptr+0x0000618c+4*10))=0x29a65c7b;
*((unsigned int *)((unsigned long)context_ptr+0x0000618c+4*11))=0x7f34e986;
*((unsigned int *)((unsigned long)context_ptr+0x0000618c+4*12))=0x770fe56d;
*((unsigned int *)((unsigned long)context_ptr+0x0000618c+4*13))=0x127cfcfe;
*((unsigned int *)((unsigned long)context_ptr+0x0000618c+4*14))=0xdf1be762;
*((unsigned int *)((unsigned long)context_ptr+0x0000618c+4*15))=0x1f4d4cc3;
*((unsigned int *)((unsigned long)context_ptr+0x0000618c+4*16))=0x61be6cb8;
*((unsigned int *)((unsigned long)context_ptr+0x0000618c+4*17))=0x0413fd23;
*((unsigned int *)((unsigned long)context_ptr+0x0000618c+4*18))=0x000000b0;
*((unsigned int *)((unsigned long)context_ptr+0x000036c0))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x000036c0+4*1))=0x000061d8;
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
*((unsigned int *)((unsigned long)context_ptr+0x000006c0+4*1))=0x0000618c;
*((unsigned int *)((unsigned long)context_ptr+0x000006c0+4*2))=0x00006414;
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
if(!memcmp((unsigned char *)context_ptr+0x00006224,"\x85\xb6\x59\x13\xe5\x40\x93\x2c\xa9\x7f\xe7\xea\xb8\x19\xe1\xdd",16))
printf("strip: 85b65913e540932c, Pass\n");
else
printf("strip: 85b65913e540932c, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006334))=0x000a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006334+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006334+4*2))=0x0202004a;
*((unsigned int *)((unsigned long)context_ptr+0x00006334+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x000061e8))=0x02ed6d2a;
*((unsigned int *)((unsigned long)context_ptr+0x000061e8+4*1))=0x5ab7ab25;
*((unsigned int *)((unsigned long)context_ptr+0x000061e8+4*2))=0x92105c6d;
*((unsigned int *)((unsigned long)context_ptr+0x000061e8+4*3))=0x7557fe59;
*((unsigned int *)((unsigned long)context_ptr+0x000061e8+4*4))=0xbeb3bdfc;
*((unsigned int *)((unsigned long)context_ptr+0x000061e8+4*5))=0xbb21d69f;
*((unsigned int *)((unsigned long)context_ptr+0x000061e8+4*6))=0xbfdb8e60;
*((unsigned int *)((unsigned long)context_ptr+0x000061e8+4*7))=0x066cf5a7;
*((unsigned int *)((unsigned long)context_ptr+0x000061e8+4*8))=0xd49b68f6;
*((unsigned int *)((unsigned long)context_ptr+0x000061e8+4*9))=0xbb3236c8;
*((unsigned int *)((unsigned long)context_ptr+0x000061e8+4*10))=0xadbba069;
*((unsigned int *)((unsigned long)context_ptr+0x000061e8+4*11))=0xf4a154bc;
*((unsigned int *)((unsigned long)context_ptr+0x000061e8+4*12))=0x475ffa00;
*((unsigned int *)((unsigned long)context_ptr+0x000061e8+4*13))=0xb3383baf;
*((unsigned int *)((unsigned long)context_ptr+0x000061e8+4*14))=0x04e2a696;
*((unsigned int *)((unsigned long)context_ptr+0x000061e8+4*15))=0x67d64a65;
*((unsigned int *)((unsigned long)context_ptr+0x000061e8+4*16))=0x1f959a5c;
*((unsigned int *)((unsigned long)context_ptr+0x000061e8+4*17))=0x55c2efc9;
*((unsigned int *)((unsigned long)context_ptr+0x000061e8+4*18))=0x00001855;
*((unsigned int *)((unsigned long)context_ptr+0x000036d8))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x000036d8+4*1))=0x000064dc;
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
*((unsigned int *)((unsigned long)context_ptr+0x000006d8+4*1))=0x000061e8;
*((unsigned int *)((unsigned long)context_ptr+0x000006d8+4*2))=0x00006334;
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
if(!memcmp((unsigned char *)context_ptr+0x00006234,"\x51\x65\xb6\x05\x20\x02\x36\xb0\xb8\x3a\x84\xdd\xa5\xf8\xe1\x61",16))
printf("strip: 5165b605200236b0, Pass\n");
else
printf("strip: 5165b605200236b0, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006234))=0x000a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006234+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006234+4*2))=0x0202004b;
*((unsigned int *)((unsigned long)context_ptr+0x00006234+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x000064ec))=0x7a53afee;
*((unsigned int *)((unsigned long)context_ptr+0x000064ec+4*1))=0x58a4ec81;
*((unsigned int *)((unsigned long)context_ptr+0x000064ec+4*2))=0x472b0be3;
*((unsigned int *)((unsigned long)context_ptr+0x000064ec+4*3))=0x953ee0f4;
*((unsigned int *)((unsigned long)context_ptr+0x000064ec+4*4))=0xba9fef49;
*((unsigned int *)((unsigned long)context_ptr+0x000064ec+4*5))=0x26edceee;
*((unsigned int *)((unsigned long)context_ptr+0x000064ec+4*6))=0xc4d8df42;
*((unsigned int *)((unsigned long)context_ptr+0x000064ec+4*7))=0x1979dab8;
*((unsigned int *)((unsigned long)context_ptr+0x000064ec+4*8))=0x8f9b3fba;
*((unsigned int *)((unsigned long)context_ptr+0x000064ec+4*9))=0x1862a763;
*((unsigned int *)((unsigned long)context_ptr+0x000064ec+4*10))=0x8f48d8dc;
*((unsigned int *)((unsigned long)context_ptr+0x000064ec+4*11))=0x6274bc22;
*((unsigned int *)((unsigned long)context_ptr+0x000064ec+4*12))=0xced7d3ee;
*((unsigned int *)((unsigned long)context_ptr+0x000064ec+4*13))=0xeb51e7ba;
*((unsigned int *)((unsigned long)context_ptr+0x000064ec+4*14))=0x7858c06a;
*((unsigned int *)((unsigned long)context_ptr+0x000064ec+4*15))=0x0d521d3f;
*((unsigned int *)((unsigned long)context_ptr+0x000064ec+4*16))=0x93135350;
*((unsigned int *)((unsigned long)context_ptr+0x000064ec+4*17))=0x3f1a9cd7;
*((unsigned int *)((unsigned long)context_ptr+0x000064ec+4*18))=0x00ba4f4b;
*((unsigned int *)((unsigned long)context_ptr+0x000036f0))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x000036f0+4*1))=0x00006344;
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
*((unsigned int *)((unsigned long)context_ptr+0x000006f0+4*1))=0x000064ec;
*((unsigned int *)((unsigned long)context_ptr+0x000006f0+4*2))=0x00006234;
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
if(!memcmp((unsigned char *)context_ptr+0x00006018,"\x83\xa6\xa1\xfe\xd2\x80\xac\xf4\xfc\xff\xd7\x41\x9f\xdf\xf5\x09",16))
printf("strip: 83a6a1fed280acf4, Pass\n");
else
printf("strip: 83a6a1fed280acf4, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006018))=0x000a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006018+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006018+4*2))=0x0202004c;
*((unsigned int *)((unsigned long)context_ptr+0x00006018+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x00006628))=0xcd5811ca;
*((unsigned int *)((unsigned long)context_ptr+0x00006628+4*1))=0x1767ae80;
*((unsigned int *)((unsigned long)context_ptr+0x00006628+4*2))=0x099e82a7;
*((unsigned int *)((unsigned long)context_ptr+0x00006628+4*3))=0x82e3ed07;
*((unsigned int *)((unsigned long)context_ptr+0x00006628+4*4))=0xc8d51969;
*((unsigned int *)((unsigned long)context_ptr+0x00006628+4*5))=0xd57ecda8;
*((unsigned int *)((unsigned long)context_ptr+0x00006628+4*6))=0x8e8c112c;
*((unsigned int *)((unsigned long)context_ptr+0x00006628+4*7))=0x1e643a94;
*((unsigned int *)((unsigned long)context_ptr+0x00006628+4*8))=0xf7a6d8d0;
*((unsigned int *)((unsigned long)context_ptr+0x00006628+4*9))=0xe5ceefa0;
*((unsigned int *)((unsigned long)context_ptr+0x00006628+4*10))=0xa325185f;
*((unsigned int *)((unsigned long)context_ptr+0x00006628+4*11))=0xadca71ca;
*((unsigned int *)((unsigned long)context_ptr+0x00006628+4*12))=0x44333034;
*((unsigned int *)((unsigned long)context_ptr+0x00006628+4*13))=0x923c8b40;
*((unsigned int *)((unsigned long)context_ptr+0x00006628+4*14))=0xc3a9cc9f;
*((unsigned int *)((unsigned long)context_ptr+0x00006628+4*15))=0xa054077c;
*((unsigned int *)((unsigned long)context_ptr+0x00006628+4*16))=0x082eeb7b;
*((unsigned int *)((unsigned long)context_ptr+0x00006628+4*17))=0x8ad83870;
*((unsigned int *)((unsigned long)context_ptr+0x00006628+4*18))=0x673ba5b7;
*((unsigned int *)((unsigned long)context_ptr+0x00003708))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003708+4*1))=0x00006354;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000708+4*1))=0x00006628;
*((unsigned int *)((unsigned long)context_ptr+0x00000708+4*2))=0x00006018;
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
if(!memcmp((unsigned char *)context_ptr+0x00006284,"\xbb\xa8\x34\xd1\x4d\x80\x3f\x38\xbb\x25\x80\x17\x61\x29\x74\xb2",16))
printf("strip: bba834d14d803f38, Pass\n");
else
printf("strip: bba834d14d803f38, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006008))=0x000a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006008+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006008+4*2))=0x0202004d;
*((unsigned int *)((unsigned long)context_ptr+0x00006008+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x00006244))=0x23acf9d7;
*((unsigned int *)((unsigned long)context_ptr+0x00006244+4*1))=0x82bee2f3;
*((unsigned int *)((unsigned long)context_ptr+0x00006244+4*2))=0x168193ad;
*((unsigned int *)((unsigned long)context_ptr+0x00006244+4*3))=0xd3756462;
*((unsigned int *)((unsigned long)context_ptr+0x00006244+4*4))=0x8e341b4c;
*((unsigned int *)((unsigned long)context_ptr+0x00006244+4*5))=0x8420f867;
*((unsigned int *)((unsigned long)context_ptr+0x00006244+4*6))=0xd3e449ce;
*((unsigned int *)((unsigned long)context_ptr+0x00006244+4*7))=0xc86dc26b;
*((unsigned int *)((unsigned long)context_ptr+0x00006244+4*8))=0x49689056;
*((unsigned int *)((unsigned long)context_ptr+0x00006244+4*9))=0x3cb76a74;
*((unsigned int *)((unsigned long)context_ptr+0x00006244+4*10))=0x65c0bff2;
*((unsigned int *)((unsigned long)context_ptr+0x00006244+4*11))=0x79e490e5;
*((unsigned int *)((unsigned long)context_ptr+0x00006244+4*12))=0x393544f6;
*((unsigned int *)((unsigned long)context_ptr+0x00006244+4*13))=0x9d0bc75c;
*((unsigned int *)((unsigned long)context_ptr+0x00006244+4*14))=0x654b7d4f;
*((unsigned int *)((unsigned long)context_ptr+0x00006244+4*15))=0x58bd1f6b;
*((unsigned int *)((unsigned long)context_ptr+0x00006244+4*16))=0xb937d118;
*((unsigned int *)((unsigned long)context_ptr+0x00006244+4*17))=0xf8f20998;
*((unsigned int *)((unsigned long)context_ptr+0x00006244+4*18))=0x31b217bb;
*((unsigned int *)((unsigned long)context_ptr+0x00006244+4*19))=0x00000076;
*((unsigned int *)((unsigned long)context_ptr+0x00003720))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003720+4*1))=0x00006538;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000720+4*1))=0x00006244;
*((unsigned int *)((unsigned long)context_ptr+0x00000720+4*2))=0x00006008;
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
if(!memcmp((unsigned char *)context_ptr+0x00006028,"\xb4\xa9\xec\xe8\xe4\xf2\xa6\xda\x90\x12\xb8\xc5\x6e\xc0\x47\xc2",16))
printf("strip: b4a9ece8e4f2a6da, Pass\n");
else
printf("strip: b4a9ece8e4f2a6da, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006028))=0x000a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006028+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006028+4*2))=0x0202004e;
*((unsigned int *)((unsigned long)context_ptr+0x00006028+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x00006548))=0x2302bc91;
*((unsigned int *)((unsigned long)context_ptr+0x00006548+4*1))=0x49baabda;
*((unsigned int *)((unsigned long)context_ptr+0x00006548+4*2))=0x1f037f70;
*((unsigned int *)((unsigned long)context_ptr+0x00006548+4*3))=0x093f0c2c;
*((unsigned int *)((unsigned long)context_ptr+0x00006548+4*4))=0x49803261;
*((unsigned int *)((unsigned long)context_ptr+0x00006548+4*5))=0x9dc99b88;
*((unsigned int *)((unsigned long)context_ptr+0x00006548+4*6))=0xe7e7ae67;
*((unsigned int *)((unsigned long)context_ptr+0x00006548+4*7))=0x949c1ea6;
*((unsigned int *)((unsigned long)context_ptr+0x00006548+4*8))=0xcf1990cc;
*((unsigned int *)((unsigned long)context_ptr+0x00006548+4*9))=0x695a9475;
*((unsigned int *)((unsigned long)context_ptr+0x00006548+4*10))=0xd288810b;
*((unsigned int *)((unsigned long)context_ptr+0x00006548+4*11))=0xdcf9315c;
*((unsigned int *)((unsigned long)context_ptr+0x00006548+4*12))=0x1e26f545;
*((unsigned int *)((unsigned long)context_ptr+0x00006548+4*13))=0xf70207d0;
*((unsigned int *)((unsigned long)context_ptr+0x00006548+4*14))=0x9245bc14;
*((unsigned int *)((unsigned long)context_ptr+0x00006548+4*15))=0x9d1a247a;
*((unsigned int *)((unsigned long)context_ptr+0x00006548+4*16))=0xcd2f8d36;
*((unsigned int *)((unsigned long)context_ptr+0x00006548+4*17))=0x254ae392;
*((unsigned int *)((unsigned long)context_ptr+0x00006548+4*18))=0x36309df5;
*((unsigned int *)((unsigned long)context_ptr+0x00006548+4*19))=0x0000b22c;
*((unsigned int *)((unsigned long)context_ptr+0x00003738))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003738+4*1))=0x00006294;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000738+4*1))=0x00006548;
*((unsigned int *)((unsigned long)context_ptr+0x00000738+4*2))=0x00006028;
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
if(!memcmp((unsigned char *)context_ptr+0x000062a4,"\x95\xd4\x2f\x4c\x24\xe5\x07\x1f\x43\x58\x84\x88\x9a\x42\x56\xf5",16))
printf("strip: 95d42f4c24e5071f, Pass\n");
else
printf("strip: 95d42f4c24e5071f, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000062a4))=0x000a0012;
*((unsigned int *)((unsigned long)context_ptr+0x000062a4+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000062a4+4*2))=0x0202004f;
*((unsigned int *)((unsigned long)context_ptr+0x000062a4+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x00006424))=0xb26bea95;
*((unsigned int *)((unsigned long)context_ptr+0x00006424+4*1))=0x296607d9;
*((unsigned int *)((unsigned long)context_ptr+0x00006424+4*2))=0x0ecb86e7;
*((unsigned int *)((unsigned long)context_ptr+0x00006424+4*3))=0x4a7b2b94;
*((unsigned int *)((unsigned long)context_ptr+0x00006424+4*4))=0x06951e8c;
*((unsigned int *)((unsigned long)context_ptr+0x00006424+4*5))=0xc22ef39b;
*((unsigned int *)((unsigned long)context_ptr+0x00006424+4*6))=0x98d7abca;
*((unsigned int *)((unsigned long)context_ptr+0x00006424+4*7))=0xb6ea52b7;
*((unsigned int *)((unsigned long)context_ptr+0x00006424+4*8))=0x9aae57a8;
*((unsigned int *)((unsigned long)context_ptr+0x00006424+4*9))=0x6fe08e70;
*((unsigned int *)((unsigned long)context_ptr+0x00006424+4*10))=0xd818a955;
*((unsigned int *)((unsigned long)context_ptr+0x00006424+4*11))=0xc5deb5e5;
*((unsigned int *)((unsigned long)context_ptr+0x00006424+4*12))=0xba8ca432;
*((unsigned int *)((unsigned long)context_ptr+0x00006424+4*13))=0x2c5ac573;
*((unsigned int *)((unsigned long)context_ptr+0x00006424+4*14))=0xdcc23b09;
*((unsigned int *)((unsigned long)context_ptr+0x00006424+4*15))=0x74da56b6;
*((unsigned int *)((unsigned long)context_ptr+0x00006424+4*16))=0x3117c5f6;
*((unsigned int *)((unsigned long)context_ptr+0x00006424+4*17))=0x64122cf6;
*((unsigned int *)((unsigned long)context_ptr+0x00006424+4*18))=0xca1580ba;
*((unsigned int *)((unsigned long)context_ptr+0x00006424+4*19))=0x002995ab;
*((unsigned int *)((unsigned long)context_ptr+0x00003750))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003750+4*1))=0x00006038;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000750+4*1))=0x00006424;
*((unsigned int *)((unsigned long)context_ptr+0x00000750+4*2))=0x000062a4;
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
if(!memcmp((unsigned char *)context_ptr+0x000062b4,"\xf3\x91\x7b\x6d\xb6\x5d\x08\x39\x44\xce\xb4\x7e\x99\xb9\x4c\xf8",16))
printf("strip: f3917b6db65d0839, Pass\n");
else
printf("strip: f3917b6db65d0839, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000062b4))=0x000a0012;
*((unsigned int *)((unsigned long)context_ptr+0x000062b4+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000062b4+4*2))=0x02020050;
*((unsigned int *)((unsigned long)context_ptr+0x000062b4+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x00006674))=0xfe12c828;
*((unsigned int *)((unsigned long)context_ptr+0x00006674+4*1))=0x5bfe4b77;
*((unsigned int *)((unsigned long)context_ptr+0x00006674+4*2))=0x15ba3847;
*((unsigned int *)((unsigned long)context_ptr+0x00006674+4*3))=0x73de623c;
*((unsigned int *)((unsigned long)context_ptr+0x00006674+4*4))=0x4dd7ca13;
*((unsigned int *)((unsigned long)context_ptr+0x00006674+4*5))=0xbad7a28c;
*((unsigned int *)((unsigned long)context_ptr+0x00006674+4*6))=0xbbbb7e9c;
*((unsigned int *)((unsigned long)context_ptr+0x00006674+4*7))=0x3a2ca6c0;
*((unsigned int *)((unsigned long)context_ptr+0x00006674+4*8))=0x51c918e5;
*((unsigned int *)((unsigned long)context_ptr+0x00006674+4*9))=0xd46ef52b;
*((unsigned int *)((unsigned long)context_ptr+0x00006674+4*10))=0x0ddb6527;
*((unsigned int *)((unsigned long)context_ptr+0x00006674+4*11))=0x9f2efc86;
*((unsigned int *)((unsigned long)context_ptr+0x00006674+4*12))=0x54f9a9b0;
*((unsigned int *)((unsigned long)context_ptr+0x00006674+4*13))=0xe92c3b5a;
*((unsigned int *)((unsigned long)context_ptr+0x00006674+4*14))=0x3e179bd3;
*((unsigned int *)((unsigned long)context_ptr+0x00006674+4*15))=0xac4a8633;
*((unsigned int *)((unsigned long)context_ptr+0x00006674+4*16))=0xbf493569;
*((unsigned int *)((unsigned long)context_ptr+0x00006674+4*17))=0x053f2f78;
*((unsigned int *)((unsigned long)context_ptr+0x00006674+4*18))=0x6d898ea1;
*((unsigned int *)((unsigned long)context_ptr+0x00006674+4*19))=0x0509b846;
*((unsigned int *)((unsigned long)context_ptr+0x00003768))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003768+4*1))=0x00006048;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000768+4*1))=0x00006674;
*((unsigned int *)((unsigned long)context_ptr+0x00000768+4*2))=0x000062b4;
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
if(!memcmp((unsigned char *)context_ptr+0x00006478,"\x18\x3a\x5a\xa8\x82\xca\x1b\x4f\xc6\x0e\x4a\xb9\x4f\x12\xb3\x24",16))
printf("strip: 183a5aa882ca1b4f, Pass\n");
else
printf("strip: 183a5aa882ca1b4f, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000062c4))=0x000a0012;
*((unsigned int *)((unsigned long)context_ptr+0x000062c4+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000062c4+4*2))=0x02020051;
*((unsigned int *)((unsigned long)context_ptr+0x000062c4+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x000066c4))=0xc301b51b;
*((unsigned int *)((unsigned long)context_ptr+0x000066c4+4*1))=0x503a2bde;
*((unsigned int *)((unsigned long)context_ptr+0x000066c4+4*2))=0x51c6f961;
*((unsigned int *)((unsigned long)context_ptr+0x000066c4+4*3))=0x075f483f;
*((unsigned int *)((unsigned long)context_ptr+0x000066c4+4*4))=0x563864cf;
*((unsigned int *)((unsigned long)context_ptr+0x000066c4+4*5))=0xea5c5d1e;
*((unsigned int *)((unsigned long)context_ptr+0x000066c4+4*6))=0x7f3e6795;
*((unsigned int *)((unsigned long)context_ptr+0x000066c4+4*7))=0xe157a80a;
*((unsigned int *)((unsigned long)context_ptr+0x000066c4+4*8))=0x195f0fe8;
*((unsigned int *)((unsigned long)context_ptr+0x000066c4+4*9))=0xb5c0d7b8;
*((unsigned int *)((unsigned long)context_ptr+0x000066c4+4*10))=0x5f35c14a;
*((unsigned int *)((unsigned long)context_ptr+0x000066c4+4*11))=0x19cedff8;
*((unsigned int *)((unsigned long)context_ptr+0x000066c4+4*12))=0x25d2aa6c;
*((unsigned int *)((unsigned long)context_ptr+0x000066c4+4*13))=0x04a2f6c9;
*((unsigned int *)((unsigned long)context_ptr+0x000066c4+4*14))=0x231344c5;
*((unsigned int *)((unsigned long)context_ptr+0x000066c4+4*15))=0x61092944;
*((unsigned int *)((unsigned long)context_ptr+0x000066c4+4*16))=0x05c56211;
*((unsigned int *)((unsigned long)context_ptr+0x000066c4+4*17))=0x92de43be;
*((unsigned int *)((unsigned long)context_ptr+0x000066c4+4*18))=0x6e19e892;
*((unsigned int *)((unsigned long)context_ptr+0x000066c4+4*19))=0xd8086135;
*((unsigned int *)((unsigned long)context_ptr+0x000066c4+4*20))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00003780))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003780+4*1))=0x00006474;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000780+4*1))=0x000066c4;
*((unsigned int *)((unsigned long)context_ptr+0x00000780+4*2))=0x000062c4;
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
if(!memcmp((unsigned char *)context_ptr+0x000063ac,"\x53\x8f\x37\x84\xcd\x35\x75\x99\xe3\x0d\x99\xbe\x1a\xaf\xdd\x17",16))
printf("strip: 538f3784cd357599, Pass\n");
else
printf("strip: 538f3784cd357599, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000062d4))=0x000a0012;
*((unsigned int *)((unsigned long)context_ptr+0x000062d4+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000062d4+4*2))=0x02020052;
*((unsigned int *)((unsigned long)context_ptr+0x000062d4+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x00006364))=0x4b11330c;
*((unsigned int *)((unsigned long)context_ptr+0x00006364+4*1))=0x34708277;
*((unsigned int *)((unsigned long)context_ptr+0x00006364+4*2))=0x84206067;
*((unsigned int *)((unsigned long)context_ptr+0x00006364+4*3))=0x637d2f61;
*((unsigned int *)((unsigned long)context_ptr+0x00006364+4*4))=0x7b8a6840;
*((unsigned int *)((unsigned long)context_ptr+0x00006364+4*5))=0xac81dd2d;
*((unsigned int *)((unsigned long)context_ptr+0x00006364+4*6))=0x234d6c70;
*((unsigned int *)((unsigned long)context_ptr+0x00006364+4*7))=0xc207ff89;
*((unsigned int *)((unsigned long)context_ptr+0x00006364+4*8))=0x3b829784;
*((unsigned int *)((unsigned long)context_ptr+0x00006364+4*9))=0x978b77b7;
*((unsigned int *)((unsigned long)context_ptr+0x00006364+4*10))=0xb7c60b91;
*((unsigned int *)((unsigned long)context_ptr+0x00006364+4*11))=0x6ead3828;
*((unsigned int *)((unsigned long)context_ptr+0x00006364+4*12))=0xca9c09fe;
*((unsigned int *)((unsigned long)context_ptr+0x00006364+4*13))=0x513ef34f;
*((unsigned int *)((unsigned long)context_ptr+0x00006364+4*14))=0xb2a51267;
*((unsigned int *)((unsigned long)context_ptr+0x00006364+4*15))=0x975316c8;
*((unsigned int *)((unsigned long)context_ptr+0x00006364+4*16))=0xde77a788;
*((unsigned int *)((unsigned long)context_ptr+0x00006364+4*17))=0x230cc7ec;
*((unsigned int *)((unsigned long)context_ptr+0x00006364+4*18))=0x6500e42d;
*((unsigned int *)((unsigned long)context_ptr+0x00006364+4*19))=0x88d1f0f6;
*((unsigned int *)((unsigned long)context_ptr+0x00006364+4*20))=0x0000bb58;
*((unsigned int *)((unsigned long)context_ptr+0x00003798))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003798+4*1))=0x00006598;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000798+4*1))=0x00006364;
*((unsigned int *)((unsigned long)context_ptr+0x00000798+4*2))=0x000062d4;
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
if(!memcmp((unsigned char *)context_ptr+0x000064cc,"\x4d\xab\xd0\x93\xaf\xda\x70\xc9\xad\x04\x33\x3a\x10\x37\x7c\x12",16))
printf("strip: 4dabd093afda70c9, Pass\n");
else
printf("strip: 4dabd093afda70c9, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000062e4))=0x000a0012;
*((unsigned int *)((unsigned long)context_ptr+0x000062e4+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000062e4+4*2))=0x02020053;
*((unsigned int *)((unsigned long)context_ptr+0x000062e4+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x00006484))=0xd640efa1;
*((unsigned int *)((unsigned long)context_ptr+0x00006484+4*1))=0x9eaaf478;
*((unsigned int *)((unsigned long)context_ptr+0x00006484+4*2))=0xdce056c2;
*((unsigned int *)((unsigned long)context_ptr+0x00006484+4*3))=0x0404b4c9;
*((unsigned int *)((unsigned long)context_ptr+0x00006484+4*4))=0x259e3ad5;
*((unsigned int *)((unsigned long)context_ptr+0x00006484+4*5))=0x9b577c2d;
*((unsigned int *)((unsigned long)context_ptr+0x00006484+4*6))=0xb94d795a;
*((unsigned int *)((unsigned long)context_ptr+0x00006484+4*7))=0x37800608;
*((unsigned int *)((unsigned long)context_ptr+0x00006484+4*8))=0x692182a8;
*((unsigned int *)((unsigned long)context_ptr+0x00006484+4*9))=0x27a865d0;
*((unsigned int *)((unsigned long)context_ptr+0x00006484+4*10))=0x9f319930;
*((unsigned int *)((unsigned long)context_ptr+0x00006484+4*11))=0xc20389d8;
*((unsigned int *)((unsigned long)context_ptr+0x00006484+4*12))=0x28496846;
*((unsigned int *)((unsigned long)context_ptr+0x00006484+4*13))=0x5f0abca5;
*((unsigned int *)((unsigned long)context_ptr+0x00006484+4*14))=0x03f9d6bc;
*((unsigned int *)((unsigned long)context_ptr+0x00006484+4*15))=0xf30e081c;
*((unsigned int *)((unsigned long)context_ptr+0x00006484+4*16))=0x9e451539;
*((unsigned int *)((unsigned long)context_ptr+0x00006484+4*17))=0xc4e3e2e9;
*((unsigned int *)((unsigned long)context_ptr+0x00006484+4*18))=0x247a36ca;
*((unsigned int *)((unsigned long)context_ptr+0x00006484+4*19))=0xa4af6f55;
*((unsigned int *)((unsigned long)context_ptr+0x00006484+4*20))=0x00b75374;
*((unsigned int *)((unsigned long)context_ptr+0x000037b0))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x000037b0+4*1))=0x000065a8;
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
*((unsigned int *)((unsigned long)context_ptr+0x000007b0+4*1))=0x00006484;
*((unsigned int *)((unsigned long)context_ptr+0x000007b0+4*2))=0x000062e4;
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
if(!memcmp((unsigned char *)context_ptr+0x00006114,"\xca\x6f\x38\x9a\xc8\x6f\x8d\x3d\xfc\x17\xfd\xa0\x13\xa4\x28\x88",16))
printf("strip: ca6f389ac86f8d3d, Pass\n");
else
printf("strip: ca6f389ac86f8d3d, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000062f4))=0x000a0012;
*((unsigned int *)((unsigned long)context_ptr+0x000062f4+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000062f4+4*2))=0x02020054;
*((unsigned int *)((unsigned long)context_ptr+0x000062f4+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x00006058))=0x0263d148;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*1))=0x0ac47dc3;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*2))=0x81ea9365;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*3))=0x517692ee;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*4))=0x5405c5c1;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*5))=0x568c3a50;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*6))=0x5526c028;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*7))=0x6d59c6e4;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*8))=0xc5fab35d;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*9))=0xf2600a00;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*10))=0x83d66294;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*11))=0xb03d8cbf;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*12))=0x029c1e34;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*13))=0x68654376;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*14))=0x4387176d;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*15))=0x9ed917e9;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*16))=0x8f8a8959;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*17))=0xbc1190e2;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*18))=0x2a7fc815;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*19))=0x9fd6ac50;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*20))=0x269730c5;
*((unsigned int *)((unsigned long)context_ptr+0x000037c8))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x000037c8+4*1))=0x000065b8;
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
*((unsigned int *)((unsigned long)context_ptr+0x000007c8+4*1))=0x00006058;
*((unsigned int *)((unsigned long)context_ptr+0x000007c8+4*2))=0x000062f4;
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
if(!memcmp((unsigned char *)context_ptr+0x000063bc,"\x40\x6b\x3b\x27\xe6\x0a\x37\xb4\xc0\xf5\xbd\xbd\x6d\xbc\x58\xac",16))
printf("strip: 406b3b27e60a37b4, Pass\n");
else
printf("strip: 406b3b27e60a37b4, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006304))=0x000a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006304+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006304+4*2))=0x02020055;
*((unsigned int *)((unsigned long)context_ptr+0x00006304+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x000065c8))=0x26f63b1a;
*((unsigned int *)((unsigned long)context_ptr+0x000065c8+4*1))=0x8f6b3dc5;
*((unsigned int *)((unsigned long)context_ptr+0x000065c8+4*2))=0x6af4e66a;
*((unsigned int *)((unsigned long)context_ptr+0x000065c8+4*3))=0xfa6e9679;
*((unsigned int *)((unsigned long)context_ptr+0x000065c8+4*4))=0x152d9ca1;
*((unsigned int *)((unsigned long)context_ptr+0x000065c8+4*5))=0x4a30440c;
*((unsigned int *)((unsigned long)context_ptr+0x000065c8+4*6))=0xb4ecb397;
*((unsigned int *)((unsigned long)context_ptr+0x000065c8+4*7))=0xd2da4aa1;
*((unsigned int *)((unsigned long)context_ptr+0x000065c8+4*8))=0xcbbbbbc4;
*((unsigned int *)((unsigned long)context_ptr+0x000065c8+4*9))=0xf3494390;
*((unsigned int *)((unsigned long)context_ptr+0x000065c8+4*10))=0x8c09762a;
*((unsigned int *)((unsigned long)context_ptr+0x000065c8+4*11))=0x4d08477c;
*((unsigned int *)((unsigned long)context_ptr+0x000065c8+4*12))=0x1c07c58e;
*((unsigned int *)((unsigned long)context_ptr+0x000065c8+4*13))=0xb6cccd75;
*((unsigned int *)((unsigned long)context_ptr+0x000065c8+4*14))=0x0d9cf14f;
*((unsigned int *)((unsigned long)context_ptr+0x000065c8+4*15))=0xe50b7e46;
*((unsigned int *)((unsigned long)context_ptr+0x000065c8+4*16))=0x4106876c;
*((unsigned int *)((unsigned long)context_ptr+0x000065c8+4*17))=0xae83945d;
*((unsigned int *)((unsigned long)context_ptr+0x000065c8+4*18))=0x9a63852d;
*((unsigned int *)((unsigned long)context_ptr+0x000065c8+4*19))=0x8f5d57ba;
*((unsigned int *)((unsigned long)context_ptr+0x000065c8+4*20))=0xb8bea0d3;
*((unsigned int *)((unsigned long)context_ptr+0x000065c8+4*21))=0x00000095;
*((unsigned int *)((unsigned long)context_ptr+0x000037e0))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x000037e0+4*1))=0x000063b8;
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
*((unsigned int *)((unsigned long)context_ptr+0x000007e0+4*1))=0x000065c8;
*((unsigned int *)((unsigned long)context_ptr+0x000007e0+4*2))=0x00006304;
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
if(!memcmp((unsigned char *)context_ptr+0x0000616c,"\xce\x27\x68\x0f\x78\x67\x50\x23\x0e\xb6\xa0\x1e\xd4\x2f\xb3\x61",16))
printf("strip: ce27680f78675023, Pass\n");
else
printf("strip: ce27680f78675023, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006314))=0x000a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006314+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006314+4*2))=0x02020056;
*((unsigned int *)((unsigned long)context_ptr+0x00006314+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x000060ac))=0x7f691595;
*((unsigned int *)((unsigned long)context_ptr+0x000060ac+4*1))=0x1a47b85e;
*((unsigned int *)((unsigned long)context_ptr+0x000060ac+4*2))=0xb1944e29;
*((unsigned int *)((unsigned long)context_ptr+0x000060ac+4*3))=0x87ce8d02;
*((unsigned int *)((unsigned long)context_ptr+0x000060ac+4*4))=0xf0edf46c;
*((unsigned int *)((unsigned long)context_ptr+0x000060ac+4*5))=0xed711e9e;
*((unsigned int *)((unsigned long)context_ptr+0x000060ac+4*6))=0x4ddc8cbd;
*((unsigned int *)((unsigned long)context_ptr+0x000060ac+4*7))=0x9bb9b4a3;
*((unsigned int *)((unsigned long)context_ptr+0x000060ac+4*8))=0x42536867;
*((unsigned int *)((unsigned long)context_ptr+0x000060ac+4*9))=0x925bada0;
*((unsigned int *)((unsigned long)context_ptr+0x000060ac+4*10))=0xc0f83357;
*((unsigned int *)((unsigned long)context_ptr+0x000060ac+4*11))=0x5fac01b2;
*((unsigned int *)((unsigned long)context_ptr+0x000060ac+4*12))=0x263fee81;
*((unsigned int *)((unsigned long)context_ptr+0x000060ac+4*13))=0x661688b4;
*((unsigned int *)((unsigned long)context_ptr+0x000060ac+4*14))=0x7fe265e2;
*((unsigned int *)((unsigned long)context_ptr+0x000060ac+4*15))=0x46c4b3dd;
*((unsigned int *)((unsigned long)context_ptr+0x000060ac+4*16))=0xd3e9fbe5;
*((unsigned int *)((unsigned long)context_ptr+0x000060ac+4*17))=0xfabd1cd8;
*((unsigned int *)((unsigned long)context_ptr+0x000060ac+4*18))=0xb75d2d92;
*((unsigned int *)((unsigned long)context_ptr+0x000060ac+4*19))=0x128a2a99;
*((unsigned int *)((unsigned long)context_ptr+0x000060ac+4*20))=0x4ad309c3;
*((unsigned int *)((unsigned long)context_ptr+0x000060ac+4*21))=0x0000e9ff;
*((unsigned int *)((unsigned long)context_ptr+0x000037f8))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x000037f8+4*1))=0x00006104;
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
*((unsigned int *)((unsigned long)context_ptr+0x000007f8+4*1))=0x000060ac;
*((unsigned int *)((unsigned long)context_ptr+0x000007f8+4*2))=0x00006314;
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
if(!memcmp((unsigned char *)context_ptr+0x0000617c,"\xec\xd8\x93\x43\x32\x07\x47\x9e\x32\xa9\x73\x25\x88\xd5\x1b\xde",16))
printf("strip: ecd893433207479e, Pass\n");
else
printf("strip: ecd893433207479e, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006324))=0x000a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006324+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006324+4*2))=0x02020057;
*((unsigned int *)((unsigned long)context_ptr+0x00006324+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x00006114))=0x9d2e93ca;
*((unsigned int *)((unsigned long)context_ptr+0x00006114+4*1))=0x2b41e401;
*((unsigned int *)((unsigned long)context_ptr+0x00006114+4*2))=0xf592c5ff;
*((unsigned int *)((unsigned long)context_ptr+0x00006114+4*3))=0xcb2ac6dd;
*((unsigned int *)((unsigned long)context_ptr+0x00006114+4*4))=0xdd44491d;
*((unsigned int *)((unsigned long)context_ptr+0x00006114+4*5))=0x932135b9;
*((unsigned int *)((unsigned long)context_ptr+0x00006114+4*6))=0x43f038af;
*((unsigned int *)((unsigned long)context_ptr+0x00006114+4*7))=0xdb5072d5;
*((unsigned int *)((unsigned long)context_ptr+0x00006114+4*8))=0x4e8c7af8;
*((unsigned int *)((unsigned long)context_ptr+0x00006114+4*9))=0xe9aa409e;
*((unsigned int *)((unsigned long)context_ptr+0x00006114+4*10))=0x0fc9e688;
*((unsigned int *)((unsigned long)context_ptr+0x00006114+4*11))=0x7a76bde0;
*((unsigned int *)((unsigned long)context_ptr+0x00006114+4*12))=0x934a57c7;
*((unsigned int *)((unsigned long)context_ptr+0x00006114+4*13))=0x220c6a04;
*((unsigned int *)((unsigned long)context_ptr+0x00006114+4*14))=0xdd349fc8;
*((unsigned int *)((unsigned long)context_ptr+0x00006114+4*15))=0x597b418b;
*((unsigned int *)((unsigned long)context_ptr+0x00006114+4*16))=0x6aa8ff9e;
*((unsigned int *)((unsigned long)context_ptr+0x00006114+4*17))=0xb2af8c8f;
*((unsigned int *)((unsigned long)context_ptr+0x00006114+4*18))=0x4193788a;
*((unsigned int *)((unsigned long)context_ptr+0x00006114+4*19))=0xa56f1e68;
*((unsigned int *)((unsigned long)context_ptr+0x00006114+4*20))=0x94dc8a75;
*((unsigned int *)((unsigned long)context_ptr+0x00006114+4*21))=0x004dc904;
*((unsigned int *)((unsigned long)context_ptr+0x00003810))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003810+4*1))=0x0000616c;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000810+4*1))=0x00006114;
*((unsigned int *)((unsigned long)context_ptr+0x00000810+4*2))=0x00006324;
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
if(!memcmp((unsigned char *)context_ptr+0x000061d8,"\x5e\x63\x7d\x4a\x80\xfd\x19\x2d\xb6\x3a\xe5\x8d\x66\x80\x51\xcb",16))
printf("strip: 5e637d4a80fd192d, Pass\n");
else
printf("strip: 5e637d4a80fd192d, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000063c8))=0x000a0012;
*((unsigned int *)((unsigned long)context_ptr+0x000063c8+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000063c8+4*2))=0x02020058;
*((unsigned int *)((unsigned long)context_ptr+0x000063c8+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x0000617c))=0x6314c44a;
*((unsigned int *)((unsigned long)context_ptr+0x0000617c+4*1))=0x040df304;
*((unsigned int *)((unsigned long)context_ptr+0x0000617c+4*2))=0x0c4ba0da;
*((unsigned int *)((unsigned long)context_ptr+0x0000617c+4*3))=0xb0ccb939;
*((unsigned int *)((unsigned long)context_ptr+0x0000617c+4*4))=0x4ed3cd0e;
*((unsigned int *)((unsigned long)context_ptr+0x0000617c+4*5))=0xe45abb3f;
*((unsigned int *)((unsigned long)context_ptr+0x0000617c+4*6))=0x90a37a9e;
*((unsigned int *)((unsigned long)context_ptr+0x0000617c+4*7))=0x42ef74d6;
*((unsigned int *)((unsigned long)context_ptr+0x0000617c+4*8))=0x8459f119;
*((unsigned int *)((unsigned long)context_ptr+0x0000617c+4*9))=0x8f9c5f4a;
*((unsigned int *)((unsigned long)context_ptr+0x0000617c+4*10))=0x16a09286;
*((unsigned int *)((unsigned long)context_ptr+0x0000617c+4*11))=0x6b7f38d6;
*((unsigned int *)((unsigned long)context_ptr+0x0000617c+4*12))=0x0b46f634;
*((unsigned int *)((unsigned long)context_ptr+0x0000617c+4*13))=0x832a5b1e;
*((unsigned int *)((unsigned long)context_ptr+0x0000617c+4*14))=0x08fd53f9;
*((unsigned int *)((unsigned long)context_ptr+0x0000617c+4*15))=0xabeebe85;
*((unsigned int *)((unsigned long)context_ptr+0x0000617c+4*16))=0xbc771ce4;
*((unsigned int *)((unsigned long)context_ptr+0x0000617c+4*17))=0x98dc5389;
*((unsigned int *)((unsigned long)context_ptr+0x0000617c+4*18))=0x6bc87508;
*((unsigned int *)((unsigned long)context_ptr+0x0000617c+4*19))=0x3d8d7c2a;
*((unsigned int *)((unsigned long)context_ptr+0x0000617c+4*20))=0x5ff484a1;
*((unsigned int *)((unsigned long)context_ptr+0x0000617c+4*21))=0xb3c9e2da;
*((unsigned int *)((unsigned long)context_ptr+0x00003828))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003828+4*1))=0x000061d4;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000828+4*1))=0x0000617c;
*((unsigned int *)((unsigned long)context_ptr+0x00000828+4*2))=0x000063c8;
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
if(!memcmp((unsigned char *)context_ptr+0x000064dc,"\x1d\x45\x7e\xd6\xa4\x85\x09\x5a\xda\xfa\x37\x6a\xa8\xe2\x74\x6a",16))
printf("strip: 1d457ed6a485095a, Pass\n");
else
printf("strip: 1d457ed6a485095a, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006334))=0x000a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006334+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006334+4*2))=0x02020059;
*((unsigned int *)((unsigned long)context_ptr+0x00006334+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x00006718))=0xe4d9f1e8;
*((unsigned int *)((unsigned long)context_ptr+0x00006718+4*1))=0x2db8de7f;
*((unsigned int *)((unsigned long)context_ptr+0x00006718+4*2))=0xe4e34b33;
*((unsigned int *)((unsigned long)context_ptr+0x00006718+4*3))=0x1006fdc9;
*((unsigned int *)((unsigned long)context_ptr+0x00006718+4*4))=0x17d8655d;
*((unsigned int *)((unsigned long)context_ptr+0x00006718+4*5))=0x5ff6335f;
*((unsigned int *)((unsigned long)context_ptr+0x00006718+4*6))=0x5f127e39;
*((unsigned int *)((unsigned long)context_ptr+0x00006718+4*7))=0x2684705d;
*((unsigned int *)((unsigned long)context_ptr+0x00006718+4*8))=0x4f62ad19;
*((unsigned int *)((unsigned long)context_ptr+0x00006718+4*9))=0x453a815a;
*((unsigned int *)((unsigned long)context_ptr+0x00006718+4*10))=0x5bcf5df6;
*((unsigned int *)((unsigned long)context_ptr+0x00006718+4*11))=0xfd331220;
*((unsigned int *)((unsigned long)context_ptr+0x00006718+4*12))=0x9adafd6b;
*((unsigned int *)((unsigned long)context_ptr+0x00006718+4*13))=0x3ec62a2c;
*((unsigned int *)((unsigned long)context_ptr+0x00006718+4*14))=0x388e6779;
*((unsigned int *)((unsigned long)context_ptr+0x00006718+4*15))=0x3fbbf3bb;
*((unsigned int *)((unsigned long)context_ptr+0x00006718+4*16))=0x625527d8;
*((unsigned int *)((unsigned long)context_ptr+0x00006718+4*17))=0x2850598d;
*((unsigned int *)((unsigned long)context_ptr+0x00006718+4*18))=0xf9bfb063;
*((unsigned int *)((unsigned long)context_ptr+0x00006718+4*19))=0xc50c98a1;
*((unsigned int *)((unsigned long)context_ptr+0x00006718+4*20))=0x02fd3c72;
*((unsigned int *)((unsigned long)context_ptr+0x00006718+4*21))=0x3d3aed79;
*((unsigned int *)((unsigned long)context_ptr+0x00006718+4*22))=0x00000021;
*((unsigned int *)((unsigned long)context_ptr+0x00003840))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003840+4*1))=0x000064d8;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000840+4*1))=0x00006718;
*((unsigned int *)((unsigned long)context_ptr+0x00000840+4*2))=0x00006334;
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
if(!memcmp((unsigned char *)context_ptr+0x00006344,"\xd7\x88\xa9\x7a\xed\x60\x6f\x42\x32\x8e\x2f\x97\x72\x8f\xc2\xd6",16))
printf("strip: d788a97aed606f42, Pass\n");
else
printf("strip: d788a97aed606f42, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006344))=0x000a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006344+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006344+4*2))=0x0202005a;
*((unsigned int *)((unsigned long)context_ptr+0x00006344+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x000061e4))=0x50a755d1;
*((unsigned int *)((unsigned long)context_ptr+0x000061e4+4*1))=0x5942ec17;
*((unsigned int *)((unsigned long)context_ptr+0x000061e4+4*2))=0x2595dc28;
*((unsigned int *)((unsigned long)context_ptr+0x000061e4+4*3))=0xaba3c6d3;
*((unsigned int *)((unsigned long)context_ptr+0x000061e4+4*4))=0xdbb42769;
*((unsigned int *)((unsigned long)context_ptr+0x000061e4+4*5))=0xd69e1955;
*((unsigned int *)((unsigned long)context_ptr+0x000061e4+4*6))=0x0ec627fb;
*((unsigned int *)((unsigned long)context_ptr+0x000061e4+4*7))=0x0f1f0184;
*((unsigned int *)((unsigned long)context_ptr+0x000061e4+4*8))=0x2c99ffca;
*((unsigned int *)((unsigned long)context_ptr+0x000061e4+4*9))=0x8158304b;
*((unsigned int *)((unsigned long)context_ptr+0x000061e4+4*10))=0x1656589f;
*((unsigned int *)((unsigned long)context_ptr+0x000061e4+4*11))=0xe0dc4b05;
*((unsigned int *)((unsigned long)context_ptr+0x000061e4+4*12))=0x724380f0;
*((unsigned int *)((unsigned long)context_ptr+0x000061e4+4*13))=0x234a761b;
*((unsigned int *)((unsigned long)context_ptr+0x000061e4+4*14))=0x56d51556;
*((unsigned int *)((unsigned long)context_ptr+0x000061e4+4*15))=0x0b912aff;
*((unsigned int *)((unsigned long)context_ptr+0x000061e4+4*16))=0xfe356bd2;
*((unsigned int *)((unsigned long)context_ptr+0x000061e4+4*17))=0x7635d342;
*((unsigned int *)((unsigned long)context_ptr+0x000061e4+4*18))=0x0c6a50c1;
*((unsigned int *)((unsigned long)context_ptr+0x000061e4+4*19))=0xa73f783a;
*((unsigned int *)((unsigned long)context_ptr+0x000061e4+4*20))=0x42f9c354;
*((unsigned int *)((unsigned long)context_ptr+0x000061e4+4*21))=0x604dd3f5;
*((unsigned int *)((unsigned long)context_ptr+0x000061e4+4*22))=0x00001d4f;
*((unsigned int *)((unsigned long)context_ptr+0x00003858))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003858+4*1))=0x000063d8;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000858+4*1))=0x000061e4;
*((unsigned int *)((unsigned long)context_ptr+0x00000858+4*2))=0x00006344;
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
if(!memcmp((unsigned char *)context_ptr+0x00006354,"\x14\xba\x93\x57\x6e\x33\xe5\xb9\x59\xe4\x1d\x78\xc9\x3b\x46\x8d",16))
printf("strip: 14ba93576e33e5b9, Pass\n");
else
printf("strip: 14ba93576e33e5b9, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006354))=0x000a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006354+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006354+4*2))=0x0202005b;
*((unsigned int *)((unsigned long)context_ptr+0x00006354+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x00006774))=0xa9496468;
*((unsigned int *)((unsigned long)context_ptr+0x00006774+4*1))=0x2afa32bd;
*((unsigned int *)((unsigned long)context_ptr+0x00006774+4*2))=0x2661e004;
*((unsigned int *)((unsigned long)context_ptr+0x00006774+4*3))=0x30668837;
*((unsigned int *)((unsigned long)context_ptr+0x00006774+4*4))=0xb4b5fe1b;
*((unsigned int *)((unsigned long)context_ptr+0x00006774+4*5))=0x9898691e;
*((unsigned int *)((unsigned long)context_ptr+0x00006774+4*6))=0x3b98e523;
*((unsigned int *)((unsigned long)context_ptr+0x00006774+4*7))=0x73fd8c78;
*((unsigned int *)((unsigned long)context_ptr+0x00006774+4*8))=0xc65f4823;
*((unsigned int *)((unsigned long)context_ptr+0x00006774+4*9))=0x672c78a4;
*((unsigned int *)((unsigned long)context_ptr+0x00006774+4*10))=0xd29a8ab2;
*((unsigned int *)((unsigned long)context_ptr+0x00006774+4*11))=0x898ee91a;
*((unsigned int *)((unsigned long)context_ptr+0x00006774+4*12))=0xf2e09f68;
*((unsigned int *)((unsigned long)context_ptr+0x00006774+4*13))=0x9c5f357e;
*((unsigned int *)((unsigned long)context_ptr+0x00006774+4*14))=0x0891f3ef;
*((unsigned int *)((unsigned long)context_ptr+0x00006774+4*15))=0xb372fed9;
*((unsigned int *)((unsigned long)context_ptr+0x00006774+4*16))=0x6bcaa098;
*((unsigned int *)((unsigned long)context_ptr+0x00006774+4*17))=0xb42a4b44;
*((unsigned int *)((unsigned long)context_ptr+0x00006774+4*18))=0x9a7d45c4;
*((unsigned int *)((unsigned long)context_ptr+0x00006774+4*19))=0x3e127f91;
*((unsigned int *)((unsigned long)context_ptr+0x00006774+4*20))=0x17587bb6;
*((unsigned int *)((unsigned long)context_ptr+0x00006774+4*21))=0x88237b9c;
*((unsigned int *)((unsigned long)context_ptr+0x00006774+4*22))=0x00567e90;
*((unsigned int *)((unsigned long)context_ptr+0x00003870))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003870+4*1))=0x00006018;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000870+4*1))=0x00006774;
*((unsigned int *)((unsigned long)context_ptr+0x00000870+4*2))=0x00006354;
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
if(!memcmp((unsigned char *)context_ptr+0x00006538,"\x67\x15\xf9\xed\xe6\x8b\xee\xc5\xc1\xa6\x6f\x1b\xde\x70\x7d\x56",16))
printf("strip: 6715f9ede68beec5, Pass\n");
else
printf("strip: 6715f9ede68beec5, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006008))=0x000a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006008+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006008+4*2))=0x0202005c;
*((unsigned int *)((unsigned long)context_ptr+0x00006008+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x000064e8))=0x8fcd5e8b;
*((unsigned int *)((unsigned long)context_ptr+0x000064e8+4*1))=0xb8ea6a0c;
*((unsigned int *)((unsigned long)context_ptr+0x000064e8+4*2))=0x9fe82090;
*((unsigned int *)((unsigned long)context_ptr+0x000064e8+4*3))=0x13ebc9bc;
*((unsigned int *)((unsigned long)context_ptr+0x000064e8+4*4))=0xf39d0c3c;
*((unsigned int *)((unsigned long)context_ptr+0x000064e8+4*5))=0x1fa77c50;
*((unsigned int *)((unsigned long)context_ptr+0x000064e8+4*6))=0x888e8ff9;
*((unsigned int *)((unsigned long)context_ptr+0x000064e8+4*7))=0xbd064507;
*((unsigned int *)((unsigned long)context_ptr+0x000064e8+4*8))=0x0e20e75b;
*((unsigned int *)((unsigned long)context_ptr+0x000064e8+4*9))=0x948f2d09;
*((unsigned int *)((unsigned long)context_ptr+0x000064e8+4*10))=0x812f74b4;
*((unsigned int *)((unsigned long)context_ptr+0x000064e8+4*11))=0xe1359134;
*((unsigned int *)((unsigned long)context_ptr+0x000064e8+4*12))=0xea34c471;
*((unsigned int *)((unsigned long)context_ptr+0x000064e8+4*13))=0xcbedac01;
*((unsigned int *)((unsigned long)context_ptr+0x000064e8+4*14))=0x05f206a0;
*((unsigned int *)((unsigned long)context_ptr+0x000064e8+4*15))=0x4ab520b3;
*((unsigned int *)((unsigned long)context_ptr+0x000064e8+4*16))=0x560ede5d;
*((unsigned int *)((unsigned long)context_ptr+0x000064e8+4*17))=0x3cfa9176;
*((unsigned int *)((unsigned long)context_ptr+0x000064e8+4*18))=0x244554b9;
*((unsigned int *)((unsigned long)context_ptr+0x000064e8+4*19))=0xbb0c0419;
*((unsigned int *)((unsigned long)context_ptr+0x000064e8+4*20))=0x9a2034f0;
*((unsigned int *)((unsigned long)context_ptr+0x000064e8+4*21))=0xef1d18c0;
*((unsigned int *)((unsigned long)context_ptr+0x000064e8+4*22))=0x4046235b;
*((unsigned int *)((unsigned long)context_ptr+0x00003888))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003888+4*1))=0x000063e8;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000888+4*1))=0x000064e8;
*((unsigned int *)((unsigned long)context_ptr+0x00000888+4*2))=0x00006008;
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
if(!memcmp((unsigned char *)context_ptr+0x00006294,"\x22\xde\x2b\x91\xac\x4b\xc9\xf9\x53\xff\xd6\x8e\xb9\x71\xf3\xaf",16))
printf("strip: 22de2b91ac4bc9f9, Pass\n");
else
printf("strip: 22de2b91ac4bc9f9, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006028))=0x000a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006028+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006028+4*2))=0x0202005d;
*((unsigned int *)((unsigned long)context_ptr+0x00006028+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x00006240))=0xcdf14d6b;
*((unsigned int *)((unsigned long)context_ptr+0x00006240+4*1))=0x5453530a;
*((unsigned int *)((unsigned long)context_ptr+0x00006240+4*2))=0x292c1466;
*((unsigned int *)((unsigned long)context_ptr+0x00006240+4*3))=0x5009ad8d;
*((unsigned int *)((unsigned long)context_ptr+0x00006240+4*4))=0x8bb7bbf3;
*((unsigned int *)((unsigned long)context_ptr+0x00006240+4*5))=0x8c20a402;
*((unsigned int *)((unsigned long)context_ptr+0x00006240+4*6))=0x49a97d18;
*((unsigned int *)((unsigned long)context_ptr+0x00006240+4*7))=0x0661f3bf;
*((unsigned int *)((unsigned long)context_ptr+0x00006240+4*8))=0x87463c9a;
*((unsigned int *)((unsigned long)context_ptr+0x00006240+4*9))=0x1d49de41;
*((unsigned int *)((unsigned long)context_ptr+0x00006240+4*10))=0xb0be1ea5;
*((unsigned int *)((unsigned long)context_ptr+0x00006240+4*11))=0xe551462a;
*((unsigned int *)((unsigned long)context_ptr+0x00006240+4*12))=0xf93ec3f8;
*((unsigned int *)((unsigned long)context_ptr+0x00006240+4*13))=0x0a7a3147;
*((unsigned int *)((unsigned long)context_ptr+0x00006240+4*14))=0x1cb830e5;
*((unsigned int *)((unsigned long)context_ptr+0x00006240+4*15))=0xc38ffe4a;
*((unsigned int *)((unsigned long)context_ptr+0x00006240+4*16))=0x9b7e1850;
*((unsigned int *)((unsigned long)context_ptr+0x00006240+4*17))=0xbed73d54;
*((unsigned int *)((unsigned long)context_ptr+0x00006240+4*18))=0xc37b7c3c;
*((unsigned int *)((unsigned long)context_ptr+0x00006240+4*19))=0x3da19785;
*((unsigned int *)((unsigned long)context_ptr+0x00006240+4*20))=0xcf55ae0e;
*((unsigned int *)((unsigned long)context_ptr+0x00006240+4*21))=0x0ddbb0ef;
*((unsigned int *)((unsigned long)context_ptr+0x00006240+4*22))=0x54c5c7d7;
*((unsigned int *)((unsigned long)context_ptr+0x00006240+4*23))=0x00000004;
*((unsigned int *)((unsigned long)context_ptr+0x000038a0))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x000038a0+4*1))=0x000063f8;
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
*((unsigned int *)((unsigned long)context_ptr+0x000008a0+4*1))=0x00006240;
*((unsigned int *)((unsigned long)context_ptr+0x000008a0+4*2))=0x00006028;
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
if(!memcmp((unsigned char *)context_ptr+0x00006038,"\x64\xa6\x13\xb8\xa7\x32\x46\x5e\x0e\x21\x16\x08\xd3\x06\x2e\x67",16))
printf("strip: 64a613b8a732465e, Pass\n");
else
printf("strip: 64a613b8a732465e, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006038))=0x000a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006038+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006038+4*2))=0x0202005e;
*((unsigned int *)((unsigned long)context_ptr+0x00006038+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x00006408))=0x9c26c654;
*((unsigned int *)((unsigned long)context_ptr+0x00006408+4*1))=0x01079903;
*((unsigned int *)((unsigned long)context_ptr+0x00006408+4*2))=0xd63dc48b;
*((unsigned int *)((unsigned long)context_ptr+0x00006408+4*3))=0x5e2a0717;
*((unsigned int *)((unsigned long)context_ptr+0x00006408+4*4))=0x6cac4983;
*((unsigned int *)((unsigned long)context_ptr+0x00006408+4*5))=0x5116ca02;
*((unsigned int *)((unsigned long)context_ptr+0x00006408+4*6))=0xcdd1c327;
*((unsigned int *)((unsigned long)context_ptr+0x00006408+4*7))=0xb0eb1ff7;
*((unsigned int *)((unsigned long)context_ptr+0x00006408+4*8))=0x1a1cfa1e;
*((unsigned int *)((unsigned long)context_ptr+0x00006408+4*9))=0xee1c3dab;
*((unsigned int *)((unsigned long)context_ptr+0x00006408+4*10))=0x9e4f30e2;
*((unsigned int *)((unsigned long)context_ptr+0x00006408+4*11))=0x9d93de90;
*((unsigned int *)((unsigned long)context_ptr+0x00006408+4*12))=0x54042fed;
*((unsigned int *)((unsigned long)context_ptr+0x00006408+4*13))=0x1076aaed;
*((unsigned int *)((unsigned long)context_ptr+0x00006408+4*14))=0x36310874;
*((unsigned int *)((unsigned long)context_ptr+0x00006408+4*15))=0xb51dc77a;
*((unsigned int *)((unsigned long)context_ptr+0x00006408+4*16))=0xf103af82;
*((unsigned int *)((unsigned long)context_ptr+0x00006408+4*17))=0xae246517;
*((unsigned int *)((unsigned long)context_ptr+0x00006408+4*18))=0xd11e3e4a;
*((unsigned int *)((unsigned long)context_ptr+0x00006408+4*19))=0x64cc4234;
*((unsigned int *)((unsigned long)context_ptr+0x00006408+4*20))=0x88dfc8b1;
*((unsigned int *)((unsigned long)context_ptr+0x00006408+4*21))=0x8e96d139;
*((unsigned int *)((unsigned long)context_ptr+0x00006408+4*22))=0x5b999f27;
*((unsigned int *)((unsigned long)context_ptr+0x00006408+4*23))=0x000073bd;
*((unsigned int *)((unsigned long)context_ptr+0x000038b8))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x000038b8+4*1))=0x000062a0;
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
*((unsigned int *)((unsigned long)context_ptr+0x000008b8+4*1))=0x00006408;
*((unsigned int *)((unsigned long)context_ptr+0x000008b8+4*2))=0x00006038;
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
if(!memcmp((unsigned char *)context_ptr+0x00006048,"\x02\x5a\x6f\x20\x42\x3a\x43\x87\xe6\xf9\xba\xca\x44\xd0\xe8\x82",16))
printf("strip: 025a6f20423a4387, Pass\n");
else
printf("strip: 025a6f20423a4387, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006048))=0x000a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006048+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006048+4*2))=0x0202005f;
*((unsigned int *)((unsigned long)context_ptr+0x00006048+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x00006620))=0xf8241b46;
*((unsigned int *)((unsigned long)context_ptr+0x00006620+4*1))=0x8cb1ffdc;
*((unsigned int *)((unsigned long)context_ptr+0x00006620+4*2))=0x5c34ca1c;
*((unsigned int *)((unsigned long)context_ptr+0x00006620+4*3))=0x9e41662f;
*((unsigned int *)((unsigned long)context_ptr+0x00006620+4*4))=0xacf1dc26;
*((unsigned int *)((unsigned long)context_ptr+0x00006620+4*5))=0xe1995242;
*((unsigned int *)((unsigned long)context_ptr+0x00006620+4*6))=0xcadb9db7;
*((unsigned int *)((unsigned long)context_ptr+0x00006620+4*7))=0xd87f30b3;
*((unsigned int *)((unsigned long)context_ptr+0x00006620+4*8))=0xb3161064;
*((unsigned int *)((unsigned long)context_ptr+0x00006620+4*9))=0xd43c3cb9;
*((unsigned int *)((unsigned long)context_ptr+0x00006620+4*10))=0x307630cb;
*((unsigned int *)((unsigned long)context_ptr+0x00006620+4*11))=0xf703d93a;
*((unsigned int *)((unsigned long)context_ptr+0x00006620+4*12))=0x5c6e8f29;
*((unsigned int *)((unsigned long)context_ptr+0x00006620+4*13))=0xd068aaf3;
*((unsigned int *)((unsigned long)context_ptr+0x00006620+4*14))=0x6cdb5552;
*((unsigned int *)((unsigned long)context_ptr+0x00006620+4*15))=0xdc576e5b;
*((unsigned int *)((unsigned long)context_ptr+0x00006620+4*16))=0x8a9d8a81;
*((unsigned int *)((unsigned long)context_ptr+0x00006620+4*17))=0x131f156b;
*((unsigned int *)((unsigned long)context_ptr+0x00006620+4*18))=0xf5237446;
*((unsigned int *)((unsigned long)context_ptr+0x00006620+4*19))=0x8c4e7a91;
*((unsigned int *)((unsigned long)context_ptr+0x00006620+4*20))=0xfda918b9;
*((unsigned int *)((unsigned long)context_ptr+0x00006620+4*21))=0xa2523e31;
*((unsigned int *)((unsigned long)context_ptr+0x00006620+4*22))=0x91e7faa8;
*((unsigned int *)((unsigned long)context_ptr+0x00006620+4*23))=0x00a487ce;
*((unsigned int *)((unsigned long)context_ptr+0x000038d0))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x000038d0+4*1))=0x000062b0;
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
*((unsigned int *)((unsigned long)context_ptr+0x000008d0+4*1))=0x00006620;
*((unsigned int *)((unsigned long)context_ptr+0x000008d0+4*2))=0x00006048;
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
if(!memcmp((unsigned char *)context_ptr+0x00006474,"\x7d\x5d\xc9\x74\x14\xdb\x5a\x2f\x64\xbc\xe6\x06\x41\xba\x38\x5e",16))
printf("strip: 7d5dc97414db5a2f, Pass\n");
else
printf("strip: 7d5dc97414db5a2f, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000062c0))=0x000a0012;
*((unsigned int *)((unsigned long)context_ptr+0x000062c0+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000062c0+4*2))=0x02020060;
*((unsigned int *)((unsigned long)context_ptr+0x000062c0+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x00006680))=0xee06704b;
*((unsigned int *)((unsigned long)context_ptr+0x00006680+4*1))=0xee9f9768;
*((unsigned int *)((unsigned long)context_ptr+0x00006680+4*2))=0xf182ba38;
*((unsigned int *)((unsigned long)context_ptr+0x00006680+4*3))=0xf5531712;
*((unsigned int *)((unsigned long)context_ptr+0x00006680+4*4))=0x55442258;
*((unsigned int *)((unsigned long)context_ptr+0x00006680+4*5))=0x50142252;
*((unsigned int *)((unsigned long)context_ptr+0x00006680+4*6))=0x7c86ab4f;
*((unsigned int *)((unsigned long)context_ptr+0x00006680+4*7))=0xd0de945c;
*((unsigned int *)((unsigned long)context_ptr+0x00006680+4*8))=0xb3f5f966;
*((unsigned int *)((unsigned long)context_ptr+0x00006680+4*9))=0x4bb2e51a;
*((unsigned int *)((unsigned long)context_ptr+0x00006680+4*10))=0x5cc704c5;
*((unsigned int *)((unsigned long)context_ptr+0x00006680+4*11))=0x82e78e54;
*((unsigned int *)((unsigned long)context_ptr+0x00006680+4*12))=0xc95e7539;
*((unsigned int *)((unsigned long)context_ptr+0x00006680+4*13))=0x8fee1d06;
*((unsigned int *)((unsigned long)context_ptr+0x00006680+4*14))=0xe917a0fe;
*((unsigned int *)((unsigned long)context_ptr+0x00006680+4*15))=0xde65ba3a;
*((unsigned int *)((unsigned long)context_ptr+0x00006680+4*16))=0xc1cf93d5;
*((unsigned int *)((unsigned long)context_ptr+0x00006680+4*17))=0xdcb5fca5;
*((unsigned int *)((unsigned long)context_ptr+0x00006680+4*18))=0xf8ddd4c8;
*((unsigned int *)((unsigned long)context_ptr+0x00006680+4*19))=0x410a51a5;
*((unsigned int *)((unsigned long)context_ptr+0x00006680+4*20))=0x4426c5cc;
*((unsigned int *)((unsigned long)context_ptr+0x00006680+4*21))=0x2e0c8825;
*((unsigned int *)((unsigned long)context_ptr+0x00006680+4*22))=0xc220fc46;
*((unsigned int *)((unsigned long)context_ptr+0x00006680+4*23))=0x94c103cd;
*((unsigned int *)((unsigned long)context_ptr+0x000038e8))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x000038e8+4*1))=0x00006468;
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
*((unsigned int *)((unsigned long)context_ptr+0x000008e8+4*1))=0x00006680;
*((unsigned int *)((unsigned long)context_ptr+0x000008e8+4*2))=0x000062c0;
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
if(!memcmp((unsigned char *)context_ptr+0x00006598,"\x3a\x41\xa2\x0d\x43\x96\xf7\x78\xb3\x7b\xed\xb7\x36\x42\x39\x61",16))
printf("strip: 3a41a20d4396f778, Pass\n");
else
printf("strip: 3a41a20d4396f778, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000062d0))=0x000a0012;
*((unsigned int *)((unsigned long)context_ptr+0x000062d0+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000062d0+4*2))=0x02020061;
*((unsigned int *)((unsigned long)context_ptr+0x000062d0+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x00006544))=0x5a43fa65;
*((unsigned int *)((unsigned long)context_ptr+0x00006544+4*1))=0x14d8b530;
*((unsigned int *)((unsigned long)context_ptr+0x00006544+4*2))=0x9dbfd393;
*((unsigned int *)((unsigned long)context_ptr+0x00006544+4*3))=0x63c82121;
*((unsigned int *)((unsigned long)context_ptr+0x00006544+4*4))=0x0fecf66d;
*((unsigned int *)((unsigned long)context_ptr+0x00006544+4*5))=0x6bae227c;
*((unsigned int *)((unsigned long)context_ptr+0x00006544+4*6))=0xe3929afe;
*((unsigned int *)((unsigned long)context_ptr+0x00006544+4*7))=0xd1c33f53;
*((unsigned int *)((unsigned long)context_ptr+0x00006544+4*8))=0xb6e009ac;
*((unsigned int *)((unsigned long)context_ptr+0x00006544+4*9))=0x0518ef4e;
*((unsigned int *)((unsigned long)context_ptr+0x00006544+4*10))=0xe342d6cb;
*((unsigned int *)((unsigned long)context_ptr+0x00006544+4*11))=0x1240ab85;
*((unsigned int *)((unsigned long)context_ptr+0x00006544+4*12))=0xfda54339;
*((unsigned int *)((unsigned long)context_ptr+0x00006544+4*13))=0x1a866486;
*((unsigned int *)((unsigned long)context_ptr+0x00006544+4*14))=0xa4a4a8b6;
*((unsigned int *)((unsigned long)context_ptr+0x00006544+4*15))=0x5671ea22;
*((unsigned int *)((unsigned long)context_ptr+0x00006544+4*16))=0x13e45159;
*((unsigned int *)((unsigned long)context_ptr+0x00006544+4*17))=0x8719428f;
*((unsigned int *)((unsigned long)context_ptr+0x00006544+4*18))=0xeb5c598e;
*((unsigned int *)((unsigned long)context_ptr+0x00006544+4*19))=0xaab1cd8c;
*((unsigned int *)((unsigned long)context_ptr+0x00006544+4*20))=0x7774beef;
*((unsigned int *)((unsigned long)context_ptr+0x00006544+4*21))=0xc3cbd8ca;
*((unsigned int *)((unsigned long)context_ptr+0x00006544+4*22))=0x2f0f9b55;
*((unsigned int *)((unsigned long)context_ptr+0x00006544+4*23))=0xb00ff824;
*((unsigned int *)((unsigned long)context_ptr+0x00006544+4*24))=0x000000d4;
*((unsigned int *)((unsigned long)context_ptr+0x00003900))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003900+4*1))=0x000066e0;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000900+4*1))=0x00006544;
*((unsigned int *)((unsigned long)context_ptr+0x00000900+4*2))=0x000062d0;
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
if(!memcmp((unsigned char *)context_ptr+0x000065a8,"\xa7\x20\xac\x75\xcc\xcb\x4a\xbb\x1b\x13\x62\x0b\xac\x03\x1d\xcb",16))
printf("strip: a720ac75cccb4abb, Pass\n");
else
printf("strip: a720ac75cccb4abb, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000065a8))=0x000a0012;
*((unsigned int *)((unsigned long)context_ptr+0x000065a8+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000065a8+4*2))=0x02020062;
*((unsigned int *)((unsigned long)context_ptr+0x000065a8+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x000067d0))=0x8db831a7;
*((unsigned int *)((unsigned long)context_ptr+0x000067d0+4*1))=0x60749d35;
*((unsigned int *)((unsigned long)context_ptr+0x000067d0+4*2))=0x62c5a95a;
*((unsigned int *)((unsigned long)context_ptr+0x000067d0+4*3))=0x50dffc30;
*((unsigned int *)((unsigned long)context_ptr+0x000067d0+4*4))=0x2cd6a219;
*((unsigned int *)((unsigned long)context_ptr+0x000067d0+4*5))=0xac095dad;
*((unsigned int *)((unsigned long)context_ptr+0x000067d0+4*6))=0x2d3ccb6d;
*((unsigned int *)((unsigned long)context_ptr+0x000067d0+4*7))=0x92e1c258;
*((unsigned int *)((unsigned long)context_ptr+0x000067d0+4*8))=0x06292d9c;
*((unsigned int *)((unsigned long)context_ptr+0x000067d0+4*9))=0x32ddc73a;
*((unsigned int *)((unsigned long)context_ptr+0x000067d0+4*10))=0x94cf6522;
*((unsigned int *)((unsigned long)context_ptr+0x000067d0+4*11))=0x064112c8;
*((unsigned int *)((unsigned long)context_ptr+0x000067d0+4*12))=0x1872fa77;
*((unsigned int *)((unsigned long)context_ptr+0x000067d0+4*13))=0xfe14dc11;
*((unsigned int *)((unsigned long)context_ptr+0x000067d0+4*14))=0x12743a1b;
*((unsigned int *)((unsigned long)context_ptr+0x000067d0+4*15))=0x2847bfc2;
*((unsigned int *)((unsigned long)context_ptr+0x000067d0+4*16))=0x0163b0f1;
*((unsigned int *)((unsigned long)context_ptr+0x000067d0+4*17))=0x47867c36;
*((unsigned int *)((unsigned long)context_ptr+0x000067d0+4*18))=0xa12632ef;
*((unsigned int *)((unsigned long)context_ptr+0x000067d0+4*19))=0x77d9e94f;
*((unsigned int *)((unsigned long)context_ptr+0x000067d0+4*20))=0x5c864c7d;
*((unsigned int *)((unsigned long)context_ptr+0x000067d0+4*21))=0x751e88fb;
*((unsigned int *)((unsigned long)context_ptr+0x000067d0+4*22))=0x854a816a;
*((unsigned int *)((unsigned long)context_ptr+0x000067d0+4*23))=0xb34ed2a6;
*((unsigned int *)((unsigned long)context_ptr+0x000067d0+4*24))=0x0000cb56;
*((unsigned int *)((unsigned long)context_ptr+0x00003918))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003918+4*1))=0x000062e0;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000918+4*1))=0x000067d0;
*((unsigned int *)((unsigned long)context_ptr+0x00000918+4*2))=0x000065a8;
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
if(!memcmp((unsigned char *)context_ptr+0x000065b8,"\x78\x61\x9b\x1e\xe9\x48\x47\x20\x7e\x7d\xa1\xab\x8f\x68\xdb\x55",16))
printf("strip: 78619b1ee9484720, Pass\n");
else
printf("strip: 78619b1ee9484720, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000065b8))=0x000a0012;
*((unsigned int *)((unsigned long)context_ptr+0x000065b8+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000065b8+4*2))=0x02020063;
*((unsigned int *)((unsigned long)context_ptr+0x000065b8+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x00006834))=0x8e58d3dc;
*((unsigned int *)((unsigned long)context_ptr+0x00006834+4*1))=0xc5669e6a;
*((unsigned int *)((unsigned long)context_ptr+0x00006834+4*2))=0xbaedb5b4;
*((unsigned int *)((unsigned long)context_ptr+0x00006834+4*3))=0x7e104f86;
*((unsigned int *)((unsigned long)context_ptr+0x00006834+4*4))=0x8804feb8;
*((unsigned int *)((unsigned long)context_ptr+0x00006834+4*5))=0x9a661bf0;
*((unsigned int *)((unsigned long)context_ptr+0x00006834+4*6))=0x82665eb3;
*((unsigned int *)((unsigned long)context_ptr+0x00006834+4*7))=0xab2f5c0a;
*((unsigned int *)((unsigned long)context_ptr+0x00006834+4*8))=0xcc0145a9;
*((unsigned int *)((unsigned long)context_ptr+0x00006834+4*9))=0xdf00f908;
*((unsigned int *)((unsigned long)context_ptr+0x00006834+4*10))=0xf23e3287;
*((unsigned int *)((unsigned long)context_ptr+0x00006834+4*11))=0x58875e1c;
*((unsigned int *)((unsigned long)context_ptr+0x00006834+4*12))=0x51766149;
*((unsigned int *)((unsigned long)context_ptr+0x00006834+4*13))=0xeae0b620;
*((unsigned int *)((unsigned long)context_ptr+0x00006834+4*14))=0x00b7a0a9;
*((unsigned int *)((unsigned long)context_ptr+0x00006834+4*15))=0x2fc9a24d;
*((unsigned int *)((unsigned long)context_ptr+0x00006834+4*16))=0x89869a1f;
*((unsigned int *)((unsigned long)context_ptr+0x00006834+4*17))=0x3c1cd57b;
*((unsigned int *)((unsigned long)context_ptr+0x00006834+4*18))=0x6292d397;
*((unsigned int *)((unsigned long)context_ptr+0x00006834+4*19))=0xef365a59;
*((unsigned int *)((unsigned long)context_ptr+0x00006834+4*20))=0x675ae2c6;
*((unsigned int *)((unsigned long)context_ptr+0x00006834+4*21))=0xa2770536;
*((unsigned int *)((unsigned long)context_ptr+0x00006834+4*22))=0xc53ef9f3;
*((unsigned int *)((unsigned long)context_ptr+0x00006834+4*23))=0xe091282c;
*((unsigned int *)((unsigned long)context_ptr+0x00006834+4*24))=0x00b19856;
*((unsigned int *)((unsigned long)context_ptr+0x00003930))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003930+4*1))=0x000062f0;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000930+4*1))=0x00006834;
*((unsigned int *)((unsigned long)context_ptr+0x00000930+4*2))=0x000065b8;
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
if(!memcmp((unsigned char *)context_ptr+0x000063b8,"\x99\x84\x06\x18\x52\xc5\xcc\xd8\x64\x3d\x94\x68\x5b\x4d\x5f\x59",16))
printf("strip: 9984061852c5ccd8, Pass\n");
else
printf("strip: 9984061852c5ccd8, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006300))=0x000a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006300+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006300+4*2))=0x02020064;
*((unsigned int *)((unsigned long)context_ptr+0x00006300+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x00006364))=0xa0a0e6ae;
*((unsigned int *)((unsigned long)context_ptr+0x00006364+4*1))=0x04de4d52;
*((unsigned int *)((unsigned long)context_ptr+0x00006364+4*2))=0x0ffc833a;
*((unsigned int *)((unsigned long)context_ptr+0x00006364+4*3))=0x0577471b;
*((unsigned int *)((unsigned long)context_ptr+0x00006364+4*4))=0x57809741;
*((unsigned int *)((unsigned long)context_ptr+0x00006364+4*5))=0x4726219e;
*((unsigned int *)((unsigned long)context_ptr+0x00006364+4*6))=0xbe506bf3;
*((unsigned int *)((unsigned long)context_ptr+0x00006364+4*7))=0xd0e827d7;
*((unsigned int *)((unsigned long)context_ptr+0x00006364+4*8))=0xd67e325e;
*((unsigned int *)((unsigned long)context_ptr+0x00006364+4*9))=0x9acb2b35;
*((unsigned int *)((unsigned long)context_ptr+0x00006364+4*10))=0xf64f7eba;
*((unsigned int *)((unsigned long)context_ptr+0x00006364+4*11))=0x0351aa3d;
*((unsigned int *)((unsigned long)context_ptr+0x00006364+4*12))=0x83d2b685;
*((unsigned int *)((unsigned long)context_ptr+0x00006364+4*13))=0x96945302;
*((unsigned int *)((unsigned long)context_ptr+0x00006364+4*14))=0x2ab6f5ec;
*((unsigned int *)((unsigned long)context_ptr+0x00006364+4*15))=0x12551fbd;
*((unsigned int *)((unsigned long)context_ptr+0x00006364+4*16))=0x09b783cf;
*((unsigned int *)((unsigned long)context_ptr+0x00006364+4*17))=0x287d342d;
*((unsigned int *)((unsigned long)context_ptr+0x00006364+4*18))=0xf51b8f19;
*((unsigned int *)((unsigned long)context_ptr+0x00006364+4*19))=0x4cc4fec6;
*((unsigned int *)((unsigned long)context_ptr+0x00006364+4*20))=0x511f33cf;
*((unsigned int *)((unsigned long)context_ptr+0x00006364+4*21))=0x11e31eb3;
*((unsigned int *)((unsigned long)context_ptr+0x00006364+4*22))=0xc383b0c6;
*((unsigned int *)((unsigned long)context_ptr+0x00006364+4*23))=0x4b26b18c;
*((unsigned int *)((unsigned long)context_ptr+0x00006364+4*24))=0xbb96a18a;
*((unsigned int *)((unsigned long)context_ptr+0x00003948))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003948+4*1))=0x000066f0;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000948+4*1))=0x00006364;
*((unsigned int *)((unsigned long)context_ptr+0x00000948+4*2))=0x00006300;
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
if(!memcmp((unsigned char *)context_ptr+0x00006104,"\x7d\xf0\x94\xcf\x51\xdb\xfb\x0b\x94\x79\x2e\x78\x55\x74\xd8\x80",16))
printf("strip: 7df094cf51dbfb0b, Pass\n");
else
printf("strip: 7df094cf51dbfb0b, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006310))=0x000a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006310+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006310+4*2))=0x02020065;
*((unsigned int *)((unsigned long)context_ptr+0x00006310+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x00006058))=0x9737828d;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*1))=0x8e007a06;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*2))=0x09e6d13c;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*3))=0x10aeeaa8;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*4))=0xa62710a4;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*5))=0xe09408ae;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*6))=0xa437a4a1;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*7))=0xd13dd526;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*8))=0x4d559806;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*9))=0x2dfa3e9c;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*10))=0xeb4fad8b;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*11))=0x8f7037c7;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*12))=0x4ebdc506;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*13))=0xdd6f6aca;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*14))=0x33bac74e;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*15))=0x409c284b;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*16))=0xc13e33ec;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*17))=0xcb006e9b;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*18))=0x30518855;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*19))=0xd3b77fe4;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*20))=0x0c17a467;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*21))=0xf6f1fb9a;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*22))=0x9db77395;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*23))=0x4eabe8dc;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*24))=0x14babd7f;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*25))=0x0000000b;
*((unsigned int *)((unsigned long)context_ptr+0x00003960))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003960+4*1))=0x00006700;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000960+4*1))=0x00006058;
*((unsigned int *)((unsigned long)context_ptr+0x00000960+4*2))=0x00006310;
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
if(!memcmp((unsigned char *)context_ptr+0x0000616c,"\x57\x73\x78\x1f\xa8\x67\xd8\xfc\xde\xda\x26\xf9\x6f\xc6\x8a\x24",16))
printf("strip: 5773781fa867d8fc, Pass\n");
else
printf("strip: 5773781fa867d8fc, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006320))=0x000a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006320+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006320+4*2))=0x02020066;
*((unsigned int *)((unsigned long)context_ptr+0x00006320+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x000060c0))=0x783f6161;
*((unsigned int *)((unsigned long)context_ptr+0x000060c0+4*1))=0xafbd4998;
*((unsigned int *)((unsigned long)context_ptr+0x000060c0+4*2))=0xa21f2b69;
*((unsigned int *)((unsigned long)context_ptr+0x000060c0+4*3))=0x9faff70d;
*((unsigned int *)((unsigned long)context_ptr+0x000060c0+4*4))=0x953c964d;
*((unsigned int *)((unsigned long)context_ptr+0x000060c0+4*5))=0xc4f6e664;
*((unsigned int *)((unsigned long)context_ptr+0x000060c0+4*6))=0x1bfac9d1;
*((unsigned int *)((unsigned long)context_ptr+0x000060c0+4*7))=0xdf82e8ca;
*((unsigned int *)((unsigned long)context_ptr+0x000060c0+4*8))=0x7bcd07cc;
*((unsigned int *)((unsigned long)context_ptr+0x000060c0+4*9))=0x9798559b;
*((unsigned int *)((unsigned long)context_ptr+0x000060c0+4*10))=0xa92e8025;
*((unsigned int *)((unsigned long)context_ptr+0x000060c0+4*11))=0xf5975b0d;
*((unsigned int *)((unsigned long)context_ptr+0x000060c0+4*12))=0x50652719;
*((unsigned int *)((unsigned long)context_ptr+0x000060c0+4*13))=0xab21d3b5;
*((unsigned int *)((unsigned long)context_ptr+0x000060c0+4*14))=0x4457e9cb;
*((unsigned int *)((unsigned long)context_ptr+0x000060c0+4*15))=0xb29066bf;
*((unsigned int *)((unsigned long)context_ptr+0x000060c0+4*16))=0xbbeebf4d;
*((unsigned int *)((unsigned long)context_ptr+0x000060c0+4*17))=0x91ef7953;
*((unsigned int *)((unsigned long)context_ptr+0x000060c0+4*18))=0xe85c801c;
*((unsigned int *)((unsigned long)context_ptr+0x000060c0+4*19))=0xed092f8d;
*((unsigned int *)((unsigned long)context_ptr+0x000060c0+4*20))=0x5d68a727;
*((unsigned int *)((unsigned long)context_ptr+0x000060c0+4*21))=0x492f6eb8;
*((unsigned int *)((unsigned long)context_ptr+0x000060c0+4*22))=0x73d19563;
*((unsigned int *)((unsigned long)context_ptr+0x000060c0+4*23))=0xcc6156f1;
*((unsigned int *)((unsigned long)context_ptr+0x000060c0+4*24))=0xa590ff5e;
*((unsigned int *)((unsigned long)context_ptr+0x000060c0+4*25))=0x00005688;
*((unsigned int *)((unsigned long)context_ptr+0x00003978))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003978+4*1))=0x00006128;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000978+4*1))=0x000060c0;
*((unsigned int *)((unsigned long)context_ptr+0x00000978+4*2))=0x00006320;
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
if(!memcmp((unsigned char *)context_ptr+0x000061d4,"\x8d\xdf\xe3\x6f\x84\x27\x85\x95\x87\x6a\x21\xb7\x25\x3b\xcf\xdf",16))
printf("strip: 8ddfe36f84278595, Pass\n");
else
printf("strip: 8ddfe36f84278595, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000063c8))=0x000a0012;
*((unsigned int *)((unsigned long)context_ptr+0x000063c8+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000063c8+4*2))=0x02020067;
*((unsigned int *)((unsigned long)context_ptr+0x000063c8+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x00006138))=0xf8bdc660;
*((unsigned int *)((unsigned long)context_ptr+0x00006138+4*1))=0x1205b15c;
*((unsigned int *)((unsigned long)context_ptr+0x00006138+4*2))=0xc6600ec8;
*((unsigned int *)((unsigned long)context_ptr+0x00006138+4*3))=0xc256d510;
*((unsigned int *)((unsigned long)context_ptr+0x00006138+4*4))=0xe567adfd;
*((unsigned int *)((unsigned long)context_ptr+0x00006138+4*5))=0x56783947;
*((unsigned int *)((unsigned long)context_ptr+0x00006138+4*6))=0x93f05fe7;
*((unsigned int *)((unsigned long)context_ptr+0x00006138+4*7))=0xa0196a0f;
*((unsigned int *)((unsigned long)context_ptr+0x00006138+4*8))=0x28999185;
*((unsigned int *)((unsigned long)context_ptr+0x00006138+4*9))=0xe3138470;
*((unsigned int *)((unsigned long)context_ptr+0x00006138+4*10))=0x88ffe858;
*((unsigned int *)((unsigned long)context_ptr+0x00006138+4*11))=0xc47a53ab;
*((unsigned int *)((unsigned long)context_ptr+0x00006138+4*12))=0xa45ca6ef;
*((unsigned int *)((unsigned long)context_ptr+0x00006138+4*13))=0xaf887086;
*((unsigned int *)((unsigned long)context_ptr+0x00006138+4*14))=0x3a816526;
*((unsigned int *)((unsigned long)context_ptr+0x00006138+4*15))=0x9e918587;
*((unsigned int *)((unsigned long)context_ptr+0x00006138+4*16))=0x7d36bd50;
*((unsigned int *)((unsigned long)context_ptr+0x00006138+4*17))=0xf74a42e3;
*((unsigned int *)((unsigned long)context_ptr+0x00006138+4*18))=0x85550fd9;
*((unsigned int *)((unsigned long)context_ptr+0x00006138+4*19))=0xa961ae3d;
*((unsigned int *)((unsigned long)context_ptr+0x00006138+4*20))=0x59e90d91;
*((unsigned int *)((unsigned long)context_ptr+0x00006138+4*21))=0x08ebea00;
*((unsigned int *)((unsigned long)context_ptr+0x00006138+4*22))=0x34073ef3;
*((unsigned int *)((unsigned long)context_ptr+0x00006138+4*23))=0xf097511e;
*((unsigned int *)((unsigned long)context_ptr+0x00006138+4*24))=0x68b70563;
*((unsigned int *)((unsigned long)context_ptr+0x00006138+4*25))=0x00def350;
*((unsigned int *)((unsigned long)context_ptr+0x00003990))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003990+4*1))=0x000061a0;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000990+4*1))=0x00006138;
*((unsigned int *)((unsigned long)context_ptr+0x00000990+4*2))=0x000063c8;
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
if(!memcmp((unsigned char *)context_ptr+0x000064d8,"\xb2\x06\x52\x7d\xf4\x16\x00\xea\x20\x7c\x73\x6b\x98\x75\x35\xa3",16))
printf("strip: b206527df41600ea, Pass\n");
else
printf("strip: b206527df41600ea, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006330))=0x000a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006330+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006330+4*2))=0x02020068;
*((unsigned int *)((unsigned long)context_ptr+0x00006330+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x00006478))=0x8bd035fc;
*((unsigned int *)((unsigned long)context_ptr+0x00006478+4*1))=0x08462d0c;
*((unsigned int *)((unsigned long)context_ptr+0x00006478+4*2))=0xf1dac404;
*((unsigned int *)((unsigned long)context_ptr+0x00006478+4*3))=0x4a857fcc;
*((unsigned int *)((unsigned long)context_ptr+0x00006478+4*4))=0xc2ebff0c;
*((unsigned int *)((unsigned long)context_ptr+0x00006478+4*5))=0xf3bb5c45;
*((unsigned int *)((unsigned long)context_ptr+0x00006478+4*6))=0xb17dd974;
*((unsigned int *)((unsigned long)context_ptr+0x00006478+4*7))=0xc4afbde7;
*((unsigned int *)((unsigned long)context_ptr+0x00006478+4*8))=0x809414d9;
*((unsigned int *)((unsigned long)context_ptr+0x00006478+4*9))=0x98522da7;
*((unsigned int *)((unsigned long)context_ptr+0x00006478+4*10))=0x66153cc5;
*((unsigned int *)((unsigned long)context_ptr+0x00006478+4*11))=0x03486f86;
*((unsigned int *)((unsigned long)context_ptr+0x00006478+4*12))=0xb00bb6b0;
*((unsigned int *)((unsigned long)context_ptr+0x00006478+4*13))=0xbfcc1a3d;
*((unsigned int *)((unsigned long)context_ptr+0x00006478+4*14))=0x2563798b;
*((unsigned int *)((unsigned long)context_ptr+0x00006478+4*15))=0x1f15154c;
*((unsigned int *)((unsigned long)context_ptr+0x00006478+4*16))=0x8fec192e;
*((unsigned int *)((unsigned long)context_ptr+0x00006478+4*17))=0x3b82fe58;
*((unsigned int *)((unsigned long)context_ptr+0x00006478+4*18))=0xd1e0cc87;
*((unsigned int *)((unsigned long)context_ptr+0x00006478+4*19))=0xbcb72757;
*((unsigned int *)((unsigned long)context_ptr+0x00006478+4*20))=0x7fa0aa98;
*((unsigned int *)((unsigned long)context_ptr+0x00006478+4*21))=0x3452fa28;
*((unsigned int *)((unsigned long)context_ptr+0x00006478+4*22))=0x551512ac;
*((unsigned int *)((unsigned long)context_ptr+0x00006478+4*23))=0x3f3d63f4;
*((unsigned int *)((unsigned long)context_ptr+0x00006478+4*24))=0x019d0e6f;
*((unsigned int *)((unsigned long)context_ptr+0x00006478+4*25))=0x6cff9417;
*((unsigned int *)((unsigned long)context_ptr+0x000039a8))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x000039a8+4*1))=0x000061b0;
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
*((unsigned int *)((unsigned long)context_ptr+0x000009a8+4*1))=0x00006478;
*((unsigned int *)((unsigned long)context_ptr+0x000009a8+4*2))=0x00006330;
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
if(!memcmp((unsigned char *)context_ptr+0x000063d8,"\x63\xf9\x7f\x35\xf9\x2a\x16\x90\x73\x7b\x68\xfd\xaf\x9b\x74\x78",16))
printf("strip: 63f97f35f92a1690, Pass\n");
else
printf("strip: 63f97f35f92a1690, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000063d8))=0x000a0012;
*((unsigned int *)((unsigned long)context_ptr+0x000063d8+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000063d8+4*2))=0x02020069;
*((unsigned int *)((unsigned long)context_ptr+0x000063d8+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x000061c0))=0xfd63e359;
*((unsigned int *)((unsigned long)context_ptr+0x000061c0+4*1))=0x9906d8ff;
*((unsigned int *)((unsigned long)context_ptr+0x000061c0+4*2))=0x118028b6;
*((unsigned int *)((unsigned long)context_ptr+0x000061c0+4*3))=0x15d91689;
*((unsigned int *)((unsigned long)context_ptr+0x000061c0+4*4))=0x0f8821f7;
*((unsigned int *)((unsigned long)context_ptr+0x000061c0+4*5))=0x3c28d744;
*((unsigned int *)((unsigned long)context_ptr+0x000061c0+4*6))=0x223fd1ec;
*((unsigned int *)((unsigned long)context_ptr+0x000061c0+4*7))=0xbc5458ea;
*((unsigned int *)((unsigned long)context_ptr+0x000061c0+4*8))=0xe63cc87c;
*((unsigned int *)((unsigned long)context_ptr+0x000061c0+4*9))=0x03352b82;
*((unsigned int *)((unsigned long)context_ptr+0x000061c0+4*10))=0xe20fd5aa;
*((unsigned int *)((unsigned long)context_ptr+0x000061c0+4*11))=0xbb30bec6;
*((unsigned int *)((unsigned long)context_ptr+0x000061c0+4*12))=0xd5e44f5e;
*((unsigned int *)((unsigned long)context_ptr+0x000061c0+4*13))=0x3b83e703;
*((unsigned int *)((unsigned long)context_ptr+0x000061c0+4*14))=0x00e3c966;
*((unsigned int *)((unsigned long)context_ptr+0x000061c0+4*15))=0x8a2be094;
*((unsigned int *)((unsigned long)context_ptr+0x000061c0+4*16))=0x13bbdc2a;
*((unsigned int *)((unsigned long)context_ptr+0x000061c0+4*17))=0xd3cea7f4;
*((unsigned int *)((unsigned long)context_ptr+0x000061c0+4*18))=0x39e12861;
*((unsigned int *)((unsigned long)context_ptr+0x000061c0+4*19))=0x5feb27e5;
*((unsigned int *)((unsigned long)context_ptr+0x000061c0+4*20))=0x0a0dbe79;
*((unsigned int *)((unsigned long)context_ptr+0x000061c0+4*21))=0x05aa128f;
*((unsigned int *)((unsigned long)context_ptr+0x000061c0+4*22))=0x98b86e1c;
*((unsigned int *)((unsigned long)context_ptr+0x000061c0+4*23))=0x2ab5d46b;
*((unsigned int *)((unsigned long)context_ptr+0x000061c0+4*24))=0xe6751116;
*((unsigned int *)((unsigned long)context_ptr+0x000061c0+4*25))=0x0c5f65d9;
*((unsigned int *)((unsigned long)context_ptr+0x000061c0+4*26))=0x00000040;
*((unsigned int *)((unsigned long)context_ptr+0x000039c0))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x000039c0+4*1))=0x00006340;
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
*((unsigned int *)((unsigned long)context_ptr+0x000009c0+4*1))=0x000061c0;
*((unsigned int *)((unsigned long)context_ptr+0x000009c0+4*2))=0x000063d8;
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
if(!memcmp((unsigned char *)context_ptr+0x00006018,"\x8d\x6e\x23\x66\x36\xf0\x61\xf4\x61\x76\xb7\x7e\xc6\x7b\xfc\x0f",16))
printf("strip: 8d6e236636f061f4, Pass\n");
else
printf("strip: 8d6e236636f061f4, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006018))=0x000a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006018+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006018+4*2))=0x0202006a;
*((unsigned int *)((unsigned long)context_ptr+0x00006018+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x00006710))=0x9219b648;
*((unsigned int *)((unsigned long)context_ptr+0x00006710+4*1))=0xe6784636;
*((unsigned int *)((unsigned long)context_ptr+0x00006710+4*2))=0x1b400a84;
*((unsigned int *)((unsigned long)context_ptr+0x00006710+4*3))=0xa5d958f6;
*((unsigned int *)((unsigned long)context_ptr+0x00006710+4*4))=0x39df63e7;
*((unsigned int *)((unsigned long)context_ptr+0x00006710+4*5))=0x1806fb9f;
*((unsigned int *)((unsigned long)context_ptr+0x00006710+4*6))=0x8fec395e;
*((unsigned int *)((unsigned long)context_ptr+0x00006710+4*7))=0xa6132433;
*((unsigned int *)((unsigned long)context_ptr+0x00006710+4*8))=0x6ac70adc;
*((unsigned int *)((unsigned long)context_ptr+0x00006710+4*9))=0xbacb2f08;
*((unsigned int *)((unsigned long)context_ptr+0x00006710+4*10))=0x52bfb066;
*((unsigned int *)((unsigned long)context_ptr+0x00006710+4*11))=0xb9d9f37f;
*((unsigned int *)((unsigned long)context_ptr+0x00006710+4*12))=0x31c47899;
*((unsigned int *)((unsigned long)context_ptr+0x00006710+4*13))=0x0f06b14a;
*((unsigned int *)((unsigned long)context_ptr+0x00006710+4*14))=0xabb63cc9;
*((unsigned int *)((unsigned long)context_ptr+0x00006710+4*15))=0x01c3dc01;
*((unsigned int *)((unsigned long)context_ptr+0x00006710+4*16))=0x73e5dc05;
*((unsigned int *)((unsigned long)context_ptr+0x00006710+4*17))=0xb06f2c27;
*((unsigned int *)((unsigned long)context_ptr+0x00006710+4*18))=0xc310c08e;
*((unsigned int *)((unsigned long)context_ptr+0x00006710+4*19))=0x47d2ce45;
*((unsigned int *)((unsigned long)context_ptr+0x00006710+4*20))=0xc9f501d3;
*((unsigned int *)((unsigned long)context_ptr+0x00006710+4*21))=0x65c6d483;
*((unsigned int *)((unsigned long)context_ptr+0x00006710+4*22))=0xd922a088;
*((unsigned int *)((unsigned long)context_ptr+0x00006710+4*23))=0xfced0d0e;
*((unsigned int *)((unsigned long)context_ptr+0x00006710+4*24))=0xff01479f;
*((unsigned int *)((unsigned long)context_ptr+0x00006710+4*25))=0x2284a32e;
*((unsigned int *)((unsigned long)context_ptr+0x00006710+4*26))=0x00004af4;
*((unsigned int *)((unsigned long)context_ptr+0x000039d8))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x000039d8+4*1))=0x0000622c;
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
*((unsigned int *)((unsigned long)context_ptr+0x000009d8+4*1))=0x00006710;
*((unsigned int *)((unsigned long)context_ptr+0x000009d8+4*2))=0x00006018;
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
if(!memcmp((unsigned char *)context_ptr+0x000063e8,"\xd3\x92\x1f\xe1\xe3\xc8\xa9\xbc\x1a\xe2\x8c\x4f\x0f\xab\xca\x74",16))
printf("strip: d3921fe1e3c8a9bc, Pass\n");
else
printf("strip: d3921fe1e3c8a9bc, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000063e8))=0x000a0012;
*((unsigned int *)((unsigned long)context_ptr+0x000063e8+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000063e8+4*2))=0x0202006b;
*((unsigned int *)((unsigned long)context_ptr+0x000063e8+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x00006898))=0x96f3c2a7;
*((unsigned int *)((unsigned long)context_ptr+0x00006898+4*1))=0x055a56af;
*((unsigned int *)((unsigned long)context_ptr+0x00006898+4*2))=0x1b1882f9;
*((unsigned int *)((unsigned long)context_ptr+0x00006898+4*3))=0x25b89624;
*((unsigned int *)((unsigned long)context_ptr+0x00006898+4*4))=0x993ca260;
*((unsigned int *)((unsigned long)context_ptr+0x00006898+4*5))=0x8c94a455;
*((unsigned int *)((unsigned long)context_ptr+0x00006898+4*6))=0x2859dc1e;
*((unsigned int *)((unsigned long)context_ptr+0x00006898+4*7))=0x7337d8c2;
*((unsigned int *)((unsigned long)context_ptr+0x00006898+4*8))=0xa7655795;
*((unsigned int *)((unsigned long)context_ptr+0x00006898+4*9))=0x05e0a0ef;
*((unsigned int *)((unsigned long)context_ptr+0x00006898+4*10))=0x72de848a;
*((unsigned int *)((unsigned long)context_ptr+0x00006898+4*11))=0x5e7abdc0;
*((unsigned int *)((unsigned long)context_ptr+0x00006898+4*12))=0xe0816722;
*((unsigned int *)((unsigned long)context_ptr+0x00006898+4*13))=0x2f1049bd;
*((unsigned int *)((unsigned long)context_ptr+0x00006898+4*14))=0xc7d129c1;
*((unsigned int *)((unsigned long)context_ptr+0x00006898+4*15))=0x8274542d;
*((unsigned int *)((unsigned long)context_ptr+0x00006898+4*16))=0x1b1e16c4;
*((unsigned int *)((unsigned long)context_ptr+0x00006898+4*17))=0xcf1b67b4;
*((unsigned int *)((unsigned long)context_ptr+0x00006898+4*18))=0x35d1d21f;
*((unsigned int *)((unsigned long)context_ptr+0x00006898+4*19))=0xca525d9b;
*((unsigned int *)((unsigned long)context_ptr+0x00006898+4*20))=0x5e91474c;
*((unsigned int *)((unsigned long)context_ptr+0x00006898+4*21))=0xedaebd92;
*((unsigned int *)((unsigned long)context_ptr+0x00006898+4*22))=0xe8f3810c;
*((unsigned int *)((unsigned long)context_ptr+0x00006898+4*23))=0x8c542f83;
*((unsigned int *)((unsigned long)context_ptr+0x00006898+4*24))=0xd4d251bc;
*((unsigned int *)((unsigned long)context_ptr+0x00006898+4*25))=0xf58aa1f8;
*((unsigned int *)((unsigned long)context_ptr+0x00006898+4*26))=0x006528e3;
*((unsigned int *)((unsigned long)context_ptr+0x000039f0))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x000039f0+4*1))=0x00006008;
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
*((unsigned int *)((unsigned long)context_ptr+0x000009f0+4*1))=0x00006898;
*((unsigned int *)((unsigned long)context_ptr+0x000009f0+4*2))=0x000063e8;
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
if(!memcmp((unsigned char *)context_ptr+0x000063f8,"\x32\x89\x31\x5c\x98\xdf\x38\x13\x1d\x4e\x67\x82\x9b\xca\x2d\x07",16))
printf("strip: 3289315c98df3813, Pass\n");
else
printf("strip: 3289315c98df3813, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000063f8))=0x000a0012;
*((unsigned int *)((unsigned long)context_ptr+0x000063f8+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000063f8+4*2))=0x0202006c;
*((unsigned int *)((unsigned long)context_ptr+0x000063f8+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x00006904))=0xba3937ab;
*((unsigned int *)((unsigned long)context_ptr+0x00006904+4*1))=0x099afd4f;
*((unsigned int *)((unsigned long)context_ptr+0x00006904+4*2))=0x176b9f0c;
*((unsigned int *)((unsigned long)context_ptr+0x00006904+4*3))=0xcaecf7e6;
*((unsigned int *)((unsigned long)context_ptr+0x00006904+4*4))=0x0e6d0441;
*((unsigned int *)((unsigned long)context_ptr+0x00006904+4*5))=0xfbe2799a;
*((unsigned int *)((unsigned long)context_ptr+0x00006904+4*6))=0xac176e20;
*((unsigned int *)((unsigned long)context_ptr+0x00006904+4*7))=0xdc26f88c;
*((unsigned int *)((unsigned long)context_ptr+0x00006904+4*8))=0x71c65d7b;
*((unsigned int *)((unsigned long)context_ptr+0x00006904+4*9))=0x76f7f69b;
*((unsigned int *)((unsigned long)context_ptr+0x00006904+4*10))=0x3b946332;
*((unsigned int *)((unsigned long)context_ptr+0x00006904+4*11))=0xee461c0a;
*((unsigned int *)((unsigned long)context_ptr+0x00006904+4*12))=0x7ba1fbfe;
*((unsigned int *)((unsigned long)context_ptr+0x00006904+4*13))=0x4c8f9bce;
*((unsigned int *)((unsigned long)context_ptr+0x00006904+4*14))=0xc8fefcf4;
*((unsigned int *)((unsigned long)context_ptr+0x00006904+4*15))=0xbe668afd;
*((unsigned int *)((unsigned long)context_ptr+0x00006904+4*16))=0x86bb680a;
*((unsigned int *)((unsigned long)context_ptr+0x00006904+4*17))=0x1fdf8107;
*((unsigned int *)((unsigned long)context_ptr+0x00006904+4*18))=0xc5995c3a;
*((unsigned int *)((unsigned long)context_ptr+0x00006904+4*19))=0xb5011898;
*((unsigned int *)((unsigned long)context_ptr+0x00006904+4*20))=0x2b846429;
*((unsigned int *)((unsigned long)context_ptr+0x00006904+4*21))=0x14778fb3;
*((unsigned int *)((unsigned long)context_ptr+0x00006904+4*22))=0x00e07d7a;
*((unsigned int *)((unsigned long)context_ptr+0x00006904+4*23))=0x232040bc;
*((unsigned int *)((unsigned long)context_ptr+0x00006904+4*24))=0x4977132c;
*((unsigned int *)((unsigned long)context_ptr+0x00006904+4*25))=0x91baa04f;
*((unsigned int *)((unsigned long)context_ptr+0x00006904+4*26))=0xfed21933;
*((unsigned int *)((unsigned long)context_ptr+0x00003a08))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003a08+4*1))=0x00006028;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000a08+4*1))=0x00006904;
*((unsigned int *)((unsigned long)context_ptr+0x00000a08+4*2))=0x000063f8;
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
if(!memcmp((unsigned char *)context_ptr+0x000062a0,"\x7e\xf5\x2b\x49\x83\xe3\x0c\x03\x97\x52\xb9\x5a\xa6\x55\x2d\x1d",16))
printf("strip: 7ef52b4983e30c03, Pass\n");
else
printf("strip: 7ef52b4983e30c03, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006038))=0x000a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006038+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006038+4*2))=0x0202006d;
*((unsigned int *)((unsigned long)context_ptr+0x00006038+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x0000623c))=0x14d1e4e4;
*((unsigned int *)((unsigned long)context_ptr+0x0000623c+4*1))=0x7a458ff3;
*((unsigned int *)((unsigned long)context_ptr+0x0000623c+4*2))=0xc890bfde;
*((unsigned int *)((unsigned long)context_ptr+0x0000623c+4*3))=0xcb0f6dec;
*((unsigned int *)((unsigned long)context_ptr+0x0000623c+4*4))=0xe6dcad3a;
*((unsigned int *)((unsigned long)context_ptr+0x0000623c+4*5))=0x5db2be0c;
*((unsigned int *)((unsigned long)context_ptr+0x0000623c+4*6))=0xe1332b9a;
*((unsigned int *)((unsigned long)context_ptr+0x0000623c+4*7))=0xb9afbc42;
*((unsigned int *)((unsigned long)context_ptr+0x0000623c+4*8))=0x980e8a47;
*((unsigned int *)((unsigned long)context_ptr+0x0000623c+4*9))=0x32b6f31d;
*((unsigned int *)((unsigned long)context_ptr+0x0000623c+4*10))=0x9a10747f;
*((unsigned int *)((unsigned long)context_ptr+0x0000623c+4*11))=0x22155732;
*((unsigned int *)((unsigned long)context_ptr+0x0000623c+4*12))=0xaf0375a7;
*((unsigned int *)((unsigned long)context_ptr+0x0000623c+4*13))=0x80c037bd;
*((unsigned int *)((unsigned long)context_ptr+0x0000623c+4*14))=0x2eb81a37;
*((unsigned int *)((unsigned long)context_ptr+0x0000623c+4*15))=0xe09bdeb3;
*((unsigned int *)((unsigned long)context_ptr+0x0000623c+4*16))=0xfd9cd956;
*((unsigned int *)((unsigned long)context_ptr+0x0000623c+4*17))=0xb36ba076;
*((unsigned int *)((unsigned long)context_ptr+0x0000623c+4*18))=0x05d91b31;
*((unsigned int *)((unsigned long)context_ptr+0x0000623c+4*19))=0x2a92eb59;
*((unsigned int *)((unsigned long)context_ptr+0x0000623c+4*20))=0x9d73e272;
*((unsigned int *)((unsigned long)context_ptr+0x0000623c+4*21))=0x47b1d068;
*((unsigned int *)((unsigned long)context_ptr+0x0000623c+4*22))=0x9254934b;
*((unsigned int *)((unsigned long)context_ptr+0x0000623c+4*23))=0x82dff9c3;
*((unsigned int *)((unsigned long)context_ptr+0x0000623c+4*24))=0x5a6e3058;
*((unsigned int *)((unsigned long)context_ptr+0x0000623c+4*25))=0xe0d2b147;
*((unsigned int *)((unsigned long)context_ptr+0x0000623c+4*26))=0x7334e5f9;
*((unsigned int *)((unsigned long)context_ptr+0x0000623c+4*27))=0x000000fa;
*((unsigned int *)((unsigned long)context_ptr+0x00003a20))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003a20+4*1))=0x00006350;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000a20+4*1))=0x0000623c;
*((unsigned int *)((unsigned long)context_ptr+0x00000a20+4*2))=0x00006038;
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
if(!memcmp((unsigned char *)context_ptr+0x000062b0,"\x4a\x73\xa3\x7a\x52\xea\x22\x4d\x58\x95\x9d\x28\x99\xf0\x5f\x2d",16))
printf("strip: 4a73a37a52ea224d, Pass\n");
else
printf("strip: 4a73a37a52ea224d, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006048))=0x000a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006048+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006048+4*2))=0x0202006e;
*((unsigned int *)((unsigned long)context_ptr+0x00006048+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x000065c8))=0x8e569126;
*((unsigned int *)((unsigned long)context_ptr+0x000065c8+4*1))=0x5b7c6f3d;
*((unsigned int *)((unsigned long)context_ptr+0x000065c8+4*2))=0x1e84b054;
*((unsigned int *)((unsigned long)context_ptr+0x000065c8+4*3))=0x1f31b45b;
*((unsigned int *)((unsigned long)context_ptr+0x000065c8+4*4))=0x4105aa35;
*((unsigned int *)((unsigned long)context_ptr+0x000065c8+4*5))=0x6ef4b2db;
*((unsigned int *)((unsigned long)context_ptr+0x000065c8+4*6))=0xe4cebf1f;
*((unsigned int *)((unsigned long)context_ptr+0x000065c8+4*7))=0x770019af;
*((unsigned int *)((unsigned long)context_ptr+0x000065c8+4*8))=0xee1f29c8;
*((unsigned int *)((unsigned long)context_ptr+0x000065c8+4*9))=0xe7716dbd;
*((unsigned int *)((unsigned long)context_ptr+0x000065c8+4*10))=0x9b8f08be;
*((unsigned int *)((unsigned long)context_ptr+0x000065c8+4*11))=0x9093b34d;
*((unsigned int *)((unsigned long)context_ptr+0x000065c8+4*12))=0x054e62ae;
*((unsigned int *)((unsigned long)context_ptr+0x000065c8+4*13))=0x42cddbb8;
*((unsigned int *)((unsigned long)context_ptr+0x000065c8+4*14))=0xa54ceabd;
*((unsigned int *)((unsigned long)context_ptr+0x000065c8+4*15))=0xc24728bf;
*((unsigned int *)((unsigned long)context_ptr+0x000065c8+4*16))=0x290c2ea2;
*((unsigned int *)((unsigned long)context_ptr+0x000065c8+4*17))=0xd052be32;
*((unsigned int *)((unsigned long)context_ptr+0x000065c8+4*18))=0x03dd4042;
*((unsigned int *)((unsigned long)context_ptr+0x000065c8+4*19))=0xac7cea4b;
*((unsigned int *)((unsigned long)context_ptr+0x000065c8+4*20))=0xa3baf79a;
*((unsigned int *)((unsigned long)context_ptr+0x000065c8+4*21))=0x4d9a034d;
*((unsigned int *)((unsigned long)context_ptr+0x000065c8+4*22))=0xc1c0d6c2;
*((unsigned int *)((unsigned long)context_ptr+0x000065c8+4*23))=0xeb77a6f3;
*((unsigned int *)((unsigned long)context_ptr+0x000065c8+4*24))=0x25234784;
*((unsigned int *)((unsigned long)context_ptr+0x000065c8+4*25))=0x962b2d19;
*((unsigned int *)((unsigned long)context_ptr+0x000065c8+4*26))=0xa043f804;
*((unsigned int *)((unsigned long)context_ptr+0x000065c8+4*27))=0x000083f0;
*((unsigned int *)((unsigned long)context_ptr+0x00003a38))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003a38+4*1))=0x000062ac;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000a38+4*1))=0x000065c8;
*((unsigned int *)((unsigned long)context_ptr+0x00000a38+4*2))=0x00006048;
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
if(!memcmp((unsigned char *)context_ptr+0x00006468,"\x83\xf5\x8e\xba\xe3\xde\x01\x43\x91\x66\xc6\xce\x88\xb6\xa0\x5f",16))
printf("strip: 83f58ebae3de0143, Pass\n");
else
printf("strip: 83f58ebae3de0143, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000062bc))=0x000a0012;
*((unsigned int *)((unsigned long)context_ptr+0x000062bc+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000062bc+4*2))=0x0202006f;
*((unsigned int *)((unsigned long)context_ptr+0x000062bc+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x00006408))=0x54a24989;
*((unsigned int *)((unsigned long)context_ptr+0x00006408+4*1))=0x8a77db66;
*((unsigned int *)((unsigned long)context_ptr+0x00006408+4*2))=0x9d9abc00;
*((unsigned int *)((unsigned long)context_ptr+0x00006408+4*3))=0xffdfccaf;
*((unsigned int *)((unsigned long)context_ptr+0x00006408+4*4))=0x37238fa9;
*((unsigned int *)((unsigned long)context_ptr+0x00006408+4*5))=0xead897fb;
*((unsigned int *)((unsigned long)context_ptr+0x00006408+4*6))=0xad51787c;
*((unsigned int *)((unsigned long)context_ptr+0x00006408+4*7))=0xa41cd3f1;
*((unsigned int *)((unsigned long)context_ptr+0x00006408+4*8))=0xfa197161;
*((unsigned int *)((unsigned long)context_ptr+0x00006408+4*9))=0xd4c56373;
*((unsigned int *)((unsigned long)context_ptr+0x00006408+4*10))=0xa43f6aa8;
*((unsigned int *)((unsigned long)context_ptr+0x00006408+4*11))=0xe11dae58;
*((unsigned int *)((unsigned long)context_ptr+0x00006408+4*12))=0x5153bbe1;
*((unsigned int *)((unsigned long)context_ptr+0x00006408+4*13))=0x71b04b96;
*((unsigned int *)((unsigned long)context_ptr+0x00006408+4*14))=0x7edb0348;
*((unsigned int *)((unsigned long)context_ptr+0x00006408+4*15))=0x8ac07902;
*((unsigned int *)((unsigned long)context_ptr+0x00006408+4*16))=0xa56e6462;
*((unsigned int *)((unsigned long)context_ptr+0x00006408+4*17))=0xee1ecefa;
*((unsigned int *)((unsigned long)context_ptr+0x00006408+4*18))=0x95f9654b;
*((unsigned int *)((unsigned long)context_ptr+0x00006408+4*19))=0x2eeae00b;
*((unsigned int *)((unsigned long)context_ptr+0x00006408+4*20))=0x4cfee03f;
*((unsigned int *)((unsigned long)context_ptr+0x00006408+4*21))=0xbcfce445;
*((unsigned int *)((unsigned long)context_ptr+0x00006408+4*22))=0xc3f85b25;
*((unsigned int *)((unsigned long)context_ptr+0x00006408+4*23))=0x3e6e8251;
*((unsigned int *)((unsigned long)context_ptr+0x00006408+4*24))=0x0e6506a3;
*((unsigned int *)((unsigned long)context_ptr+0x00006408+4*25))=0xd0f8d3f1;
*((unsigned int *)((unsigned long)context_ptr+0x00006408+4*26))=0x187272a0;
*((unsigned int *)((unsigned long)context_ptr+0x00006408+4*27))=0x005f4226;
*((unsigned int *)((unsigned long)context_ptr+0x00003a50))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003a50+4*1))=0x0000677c;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000a50+4*1))=0x00006408;
*((unsigned int *)((unsigned long)context_ptr+0x00000a50+4*2))=0x000062bc;
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
if(!memcmp((unsigned char *)context_ptr+0x000066e0,"\x57\x47\x8c\xd1\xee\x7f\x96\x90\x09\xbc\xc0\xf8\x48\x30\xcf\x5f",16))
printf("strip: 57478cd1ee7f9690, Pass\n");
else
printf("strip: 57478cd1ee7f9690, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000062cc))=0x000a0012;
*((unsigned int *)((unsigned long)context_ptr+0x000062cc+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000062cc+4*2))=0x02020070;
*((unsigned int *)((unsigned long)context_ptr+0x000062cc+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x00006638))=0xfa3868cd;
*((unsigned int *)((unsigned long)context_ptr+0x00006638+4*1))=0x4afe1856;
*((unsigned int *)((unsigned long)context_ptr+0x00006638+4*2))=0xf32ad774;
*((unsigned int *)((unsigned long)context_ptr+0x00006638+4*3))=0xa9fe2bb9;
*((unsigned int *)((unsigned long)context_ptr+0x00006638+4*4))=0x6306a335;
*((unsigned int *)((unsigned long)context_ptr+0x00006638+4*5))=0x825de32c;
*((unsigned int *)((unsigned long)context_ptr+0x00006638+4*6))=0x8930c2f0;
*((unsigned int *)((unsigned long)context_ptr+0x00006638+4*7))=0xeaee9f69;
*((unsigned int *)((unsigned long)context_ptr+0x00006638+4*8))=0xab9403b2;
*((unsigned int *)((unsigned long)context_ptr+0x00006638+4*9))=0x5a6100ca;
*((unsigned int *)((unsigned long)context_ptr+0x00006638+4*10))=0xa22240a4;
*((unsigned int *)((unsigned long)context_ptr+0x00006638+4*11))=0xfa11425e;
*((unsigned int *)((unsigned long)context_ptr+0x00006638+4*12))=0x054c40a4;
*((unsigned int *)((unsigned long)context_ptr+0x00006638+4*13))=0xe32861c9;
*((unsigned int *)((unsigned long)context_ptr+0x00006638+4*14))=0xc3c81c33;
*((unsigned int *)((unsigned long)context_ptr+0x00006638+4*15))=0x1ab43009;
*((unsigned int *)((unsigned long)context_ptr+0x00006638+4*16))=0xdc54a9bb;
*((unsigned int *)((unsigned long)context_ptr+0x00006638+4*17))=0x0cd518ea;
*((unsigned int *)((unsigned long)context_ptr+0x00006638+4*18))=0x3a208eac;
*((unsigned int *)((unsigned long)context_ptr+0x00006638+4*19))=0x2a3c2b10;
*((unsigned int *)((unsigned long)context_ptr+0x00006638+4*20))=0xe58c438c;
*((unsigned int *)((unsigned long)context_ptr+0x00006638+4*21))=0xb92132af;
*((unsigned int *)((unsigned long)context_ptr+0x00006638+4*22))=0x9ee8d43b;
*((unsigned int *)((unsigned long)context_ptr+0x00006638+4*23))=0x19944148;
*((unsigned int *)((unsigned long)context_ptr+0x00006638+4*24))=0xac92d56a;
*((unsigned int *)((unsigned long)context_ptr+0x00006638+4*25))=0x8c9a2288;
*((unsigned int *)((unsigned long)context_ptr+0x00006638+4*26))=0xfaf783fc;
*((unsigned int *)((unsigned long)context_ptr+0x00006638+4*27))=0xc8d58b3b;
*((unsigned int *)((unsigned long)context_ptr+0x00003a68))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003a68+4*1))=0x0000678c;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000a68+4*1))=0x00006638;
*((unsigned int *)((unsigned long)context_ptr+0x00000a68+4*2))=0x000062cc;
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
if(!memcmp((unsigned char *)context_ptr+0x000062e0,"\xcb\x44\x35\x1f\xb1\x0f\xff\x7d\x44\x47\x46\x86\x76\x5e\x6c\x4c",16))
printf("strip: cb44351fb10fff7d, Pass\n");
else
printf("strip: cb44351fb10fff7d, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000062dc))=0x000a0012;
*((unsigned int *)((unsigned long)context_ptr+0x000062dc+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000062dc+4*2))=0x02020071;
*((unsigned int *)((unsigned long)context_ptr+0x000062dc+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x0000679c))=0x53a0b61a;
*((unsigned int *)((unsigned long)context_ptr+0x0000679c+4*1))=0x94074384;
*((unsigned int *)((unsigned long)context_ptr+0x0000679c+4*2))=0x72764791;
*((unsigned int *)((unsigned long)context_ptr+0x0000679c+4*3))=0xebe354e7;
*((unsigned int *)((unsigned long)context_ptr+0x0000679c+4*4))=0x7e97ed1e;
*((unsigned int *)((unsigned long)context_ptr+0x0000679c+4*5))=0x4f075893;
*((unsigned int *)((unsigned long)context_ptr+0x0000679c+4*6))=0xdfd41397;
*((unsigned int *)((unsigned long)context_ptr+0x0000679c+4*7))=0xd4b74270;
*((unsigned int *)((unsigned long)context_ptr+0x0000679c+4*8))=0x1ec952a9;
*((unsigned int *)((unsigned long)context_ptr+0x0000679c+4*9))=0xa00b6956;
*((unsigned int *)((unsigned long)context_ptr+0x0000679c+4*10))=0xc4a069c8;
*((unsigned int *)((unsigned long)context_ptr+0x0000679c+4*11))=0xef40f5c2;
*((unsigned int *)((unsigned long)context_ptr+0x0000679c+4*12))=0xeb5bc58a;
*((unsigned int *)((unsigned long)context_ptr+0x0000679c+4*13))=0xee07ce62;
*((unsigned int *)((unsigned long)context_ptr+0x0000679c+4*14))=0x7c65d35c;
*((unsigned int *)((unsigned long)context_ptr+0x0000679c+4*15))=0xe2ed0336;
*((unsigned int *)((unsigned long)context_ptr+0x0000679c+4*16))=0x5cea9541;
*((unsigned int *)((unsigned long)context_ptr+0x0000679c+4*17))=0x9e849399;
*((unsigned int *)((unsigned long)context_ptr+0x0000679c+4*18))=0xb74b1c1d;
*((unsigned int *)((unsigned long)context_ptr+0x0000679c+4*19))=0x79cb0063;
*((unsigned int *)((unsigned long)context_ptr+0x0000679c+4*20))=0x09c9b062;
*((unsigned int *)((unsigned long)context_ptr+0x0000679c+4*21))=0x87ba2a38;
*((unsigned int *)((unsigned long)context_ptr+0x0000679c+4*22))=0x03578f2d;
*((unsigned int *)((unsigned long)context_ptr+0x0000679c+4*23))=0xb2efeeef;
*((unsigned int *)((unsigned long)context_ptr+0x0000679c+4*24))=0x10af28cd;
*((unsigned int *)((unsigned long)context_ptr+0x0000679c+4*25))=0xf582bb55;
*((unsigned int *)((unsigned long)context_ptr+0x0000679c+4*26))=0xec63ab4a;
*((unsigned int *)((unsigned long)context_ptr+0x0000679c+4*27))=0x88605584;
*((unsigned int *)((unsigned long)context_ptr+0x0000679c+4*28))=0x000000f2;
*((unsigned int *)((unsigned long)context_ptr+0x00003a80))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003a80+4*1))=0x00006810;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000a80+4*1))=0x0000679c;
*((unsigned int *)((unsigned long)context_ptr+0x00000a80+4*2))=0x000062dc;
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
if(!memcmp((unsigned char *)context_ptr+0x000062f0,"\x4b\x93\x5f\x45\x04\xb8\xe2\x13\x22\xc2\x94\xfb\xb0\x6c\xbd\x31",16))
printf("strip: 4b935f4504b8e213, Pass\n");
else
printf("strip: 4b935f4504b8e213, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000062ec))=0x000a0012;
*((unsigned int *)((unsigned long)context_ptr+0x000062ec+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000062ec+4*2))=0x02020072;
*((unsigned int *)((unsigned long)context_ptr+0x000062ec+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x00006820))=0x21ab67d3;
*((unsigned int *)((unsigned long)context_ptr+0x00006820+4*1))=0x6d159cf9;
*((unsigned int *)((unsigned long)context_ptr+0x00006820+4*2))=0x2b4a3be4;
*((unsigned int *)((unsigned long)context_ptr+0x00006820+4*3))=0x47cb593b;
*((unsigned int *)((unsigned long)context_ptr+0x00006820+4*4))=0xe2608f68;
*((unsigned int *)((unsigned long)context_ptr+0x00006820+4*5))=0x9000ec93;
*((unsigned int *)((unsigned long)context_ptr+0x00006820+4*6))=0xc5338530;
*((unsigned int *)((unsigned long)context_ptr+0x00006820+4*7))=0x9b843721;
*((unsigned int *)((unsigned long)context_ptr+0x00006820+4*8))=0x07b508b5;
*((unsigned int *)((unsigned long)context_ptr+0x00006820+4*9))=0x61002732;
*((unsigned int *)((unsigned long)context_ptr+0x00006820+4*10))=0xa3120658;
*((unsigned int *)((unsigned long)context_ptr+0x00006820+4*11))=0x2bfbd80a;
*((unsigned int *)((unsigned long)context_ptr+0x00006820+4*12))=0x5fb94323;
*((unsigned int *)((unsigned long)context_ptr+0x00006820+4*13))=0x0a523b6e;
*((unsigned int *)((unsigned long)context_ptr+0x00006820+4*14))=0x559a46b6;
*((unsigned int *)((unsigned long)context_ptr+0x00006820+4*15))=0x204dbb92;
*((unsigned int *)((unsigned long)context_ptr+0x00006820+4*16))=0x0c3ffeba;
*((unsigned int *)((unsigned long)context_ptr+0x00006820+4*17))=0x22ea5eb4;
*((unsigned int *)((unsigned long)context_ptr+0x00006820+4*18))=0x78fa8225;
*((unsigned int *)((unsigned long)context_ptr+0x00006820+4*19))=0xffe52d68;
*((unsigned int *)((unsigned long)context_ptr+0x00006820+4*20))=0x9dcd8023;
*((unsigned int *)((unsigned long)context_ptr+0x00006820+4*21))=0x2487cf39;
*((unsigned int *)((unsigned long)context_ptr+0x00006820+4*22))=0xe0493dc6;
*((unsigned int *)((unsigned long)context_ptr+0x00006820+4*23))=0xb1e6af93;
*((unsigned int *)((unsigned long)context_ptr+0x00006820+4*24))=0x92b279d0;
*((unsigned int *)((unsigned long)context_ptr+0x00006820+4*25))=0x524523be;
*((unsigned int *)((unsigned long)context_ptr+0x00006820+4*26))=0x4d0435c8;
*((unsigned int *)((unsigned long)context_ptr+0x00006820+4*27))=0xd7dc9886;
*((unsigned int *)((unsigned long)context_ptr+0x00006820+4*28))=0x00003788;
*((unsigned int *)((unsigned long)context_ptr+0x00003a98))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003a98+4*1))=0x000066a8;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000a98+4*1))=0x00006820;
*((unsigned int *)((unsigned long)context_ptr+0x00000a98+4*2))=0x000062ec;
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
if(!memcmp((unsigned char *)context_ptr+0x000066f0,"\x4e\x3a\x33\x10\xf4\x9b\x69\x14\x88\x08\xc8\xcb\x5b\xb1\xa9\x9d",16))
printf("strip: 4e3a3310f49b6914, Pass\n");
else
printf("strip: 4e3a3310f49b6914, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000062fc))=0x000a0012;
*((unsigned int *)((unsigned long)context_ptr+0x000062fc+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000062fc+4*2))=0x02020073;
*((unsigned int *)((unsigned long)context_ptr+0x000062fc+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x000064e0))=0xf0315093;
*((unsigned int *)((unsigned long)context_ptr+0x000064e0+4*1))=0x61e63a05;
*((unsigned int *)((unsigned long)context_ptr+0x000064e0+4*2))=0x29e2f27d;
*((unsigned int *)((unsigned long)context_ptr+0x000064e0+4*3))=0x10ffbff7;
*((unsigned int *)((unsigned long)context_ptr+0x000064e0+4*4))=0x079ef2f5;
*((unsigned int *)((unsigned long)context_ptr+0x000064e0+4*5))=0xe5866614;
*((unsigned int *)((unsigned long)context_ptr+0x000064e0+4*6))=0x2755f119;
*((unsigned int *)((unsigned long)context_ptr+0x000064e0+4*7))=0x9da99c86;
*((unsigned int *)((unsigned long)context_ptr+0x000064e0+4*8))=0xf5b7c0c7;
*((unsigned int *)((unsigned long)context_ptr+0x000064e0+4*9))=0x51216a43;
*((unsigned int *)((unsigned long)context_ptr+0x000064e0+4*10))=0x991a4a39;
*((unsigned int *)((unsigned long)context_ptr+0x000064e0+4*11))=0xaf3b8256;
*((unsigned int *)((unsigned long)context_ptr+0x000064e0+4*12))=0x5f6ef8ab;
*((unsigned int *)((unsigned long)context_ptr+0x000064e0+4*13))=0xdca87a08;
*((unsigned int *)((unsigned long)context_ptr+0x000064e0+4*14))=0x3dbf69e7;
*((unsigned int *)((unsigned long)context_ptr+0x000064e0+4*15))=0x52cc3ef9;
*((unsigned int *)((unsigned long)context_ptr+0x000064e0+4*16))=0x672f4d42;
*((unsigned int *)((unsigned long)context_ptr+0x000064e0+4*17))=0x0c68224a;
*((unsigned int *)((unsigned long)context_ptr+0x000064e0+4*18))=0x9e21a5e4;
*((unsigned int *)((unsigned long)context_ptr+0x000064e0+4*19))=0x2f085b36;
*((unsigned int *)((unsigned long)context_ptr+0x000064e0+4*20))=0x12c8f800;
*((unsigned int *)((unsigned long)context_ptr+0x000064e0+4*21))=0xd045cd91;
*((unsigned int *)((unsigned long)context_ptr+0x000064e0+4*22))=0x8f37638b;
*((unsigned int *)((unsigned long)context_ptr+0x000064e0+4*23))=0xbb3a48aa;
*((unsigned int *)((unsigned long)context_ptr+0x000064e0+4*24))=0x3b02864e;
*((unsigned int *)((unsigned long)context_ptr+0x000064e0+4*25))=0xf72be13d;
*((unsigned int *)((unsigned long)context_ptr+0x000064e0+4*26))=0xd63a1b35;
*((unsigned int *)((unsigned long)context_ptr+0x000064e0+4*27))=0xa3b02769;
*((unsigned int *)((unsigned long)context_ptr+0x000064e0+4*28))=0x00afb732;
*((unsigned int *)((unsigned long)context_ptr+0x00003ab0))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003ab0+4*1))=0x000066b8;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000ab0+4*1))=0x000064e0;
*((unsigned int *)((unsigned long)context_ptr+0x00000ab0+4*2))=0x000062fc;
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
if(!memcmp((unsigned char *)context_ptr+0x00006700,"\x00\xd0\xe4\x0f\xc1\x96\xb9\xb5\xd3\x51\x92\xce\x55\xc3\x99\xb7",16))
printf("strip: 00d0e40fc196b9b5, Pass\n");
else
printf("strip: 00d0e40fc196b9b5, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x0000630c))=0x000a0012;
*((unsigned int *)((unsigned long)context_ptr+0x0000630c+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x0000630c+4*2))=0x02020074;
*((unsigned int *)((unsigned long)context_ptr+0x0000630c+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x00006554))=0xe2971cff;
*((unsigned int *)((unsigned long)context_ptr+0x00006554+4*1))=0x8b3670fa;
*((unsigned int *)((unsigned long)context_ptr+0x00006554+4*2))=0x3e922cdd;
*((unsigned int *)((unsigned long)context_ptr+0x00006554+4*3))=0x02f5a65a;
*((unsigned int *)((unsigned long)context_ptr+0x00006554+4*4))=0x77a7df0e;
*((unsigned int *)((unsigned long)context_ptr+0x00006554+4*5))=0xdd6b143e;
*((unsigned int *)((unsigned long)context_ptr+0x00006554+4*6))=0x67a15bdc;
*((unsigned int *)((unsigned long)context_ptr+0x00006554+4*7))=0x117e3b10;
*((unsigned int *)((unsigned long)context_ptr+0x00006554+4*8))=0x5c96e513;
*((unsigned int *)((unsigned long)context_ptr+0x00006554+4*9))=0xd71539f2;
*((unsigned int *)((unsigned long)context_ptr+0x00006554+4*10))=0xdd13edc5;
*((unsigned int *)((unsigned long)context_ptr+0x00006554+4*11))=0x547ce0f0;
*((unsigned int *)((unsigned long)context_ptr+0x00006554+4*12))=0x4fd249d0;
*((unsigned int *)((unsigned long)context_ptr+0x00006554+4*13))=0xb5d6de30;
*((unsigned int *)((unsigned long)context_ptr+0x00006554+4*14))=0x9cd878e7;
*((unsigned int *)((unsigned long)context_ptr+0x00006554+4*15))=0xc9dc7008;
*((unsigned int *)((unsigned long)context_ptr+0x00006554+4*16))=0x41e853d7;
*((unsigned int *)((unsigned long)context_ptr+0x00006554+4*17))=0xcf0d1730;
*((unsigned int *)((unsigned long)context_ptr+0x00006554+4*18))=0x6a936cac;
*((unsigned int *)((unsigned long)context_ptr+0x00006554+4*19))=0x613aa6e6;
*((unsigned int *)((unsigned long)context_ptr+0x00006554+4*20))=0x41b793b0;
*((unsigned int *)((unsigned long)context_ptr+0x00006554+4*21))=0x44fe370b;
*((unsigned int *)((unsigned long)context_ptr+0x00006554+4*22))=0x2284a7e6;
*((unsigned int *)((unsigned long)context_ptr+0x00006554+4*23))=0x2ab09992;
*((unsigned int *)((unsigned long)context_ptr+0x00006554+4*24))=0x94d9d77d;
*((unsigned int *)((unsigned long)context_ptr+0x00006554+4*25))=0xb4e7a35e;
*((unsigned int *)((unsigned long)context_ptr+0x00006554+4*26))=0x0c551f87;
*((unsigned int *)((unsigned long)context_ptr+0x00006554+4*27))=0x8547ed9f;
*((unsigned int *)((unsigned long)context_ptr+0x00006554+4*28))=0x2505479d;
*((unsigned int *)((unsigned long)context_ptr+0x00003ac8))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003ac8+4*1))=0x000066c8;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000ac8+4*1))=0x00006554;
*((unsigned int *)((unsigned long)context_ptr+0x00000ac8+4*2))=0x0000630c;
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
if(!memcmp((unsigned char *)context_ptr+0x00006128,"\x76\xf1\xa5\x50\xb9\x1a\x59\xb3\xc8\xac\xcf\x44\xb2\x9c\x0a\x7b",16))
printf("strip: 76f1a550b91a59b3, Pass\n");
else
printf("strip: 76f1a550b91a59b3, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x0000631c))=0x000a0012;
*((unsigned int *)((unsigned long)context_ptr+0x0000631c+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x0000631c+4*2))=0x02020075;
*((unsigned int *)((unsigned long)context_ptr+0x0000631c+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x00006058))=0xfb90d11c;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*1))=0x9d24c9ed;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*2))=0x24f2af2b;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*3))=0xa9518e20;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*4))=0xfd2ab048;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*5))=0xdef9fa77;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*6))=0xae6d8568;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*7))=0x33e46a4e;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*8))=0xdf823a6c;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*9))=0x6008b4a1;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*10))=0x003d5a3c;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*11))=0x9945ab6f;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*12))=0x75b0e468;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*13))=0xbf8e80be;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*14))=0xb7c8799f;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*15))=0x1e021eb3;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*16))=0x255f74bb;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*17))=0x62796387;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*18))=0x09053681;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*19))=0xb4f17fd2;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*20))=0xd23c0597;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*21))=0xb799c6f0;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*22))=0xd03d8ce8;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*23))=0x5dd95db1;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*24))=0xcd676f57;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*25))=0x946cfe04;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*26))=0x5419d4e1;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*27))=0xe991245b;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*28))=0x4a78eadb;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*29))=0x00000058;
*((unsigned int *)((unsigned long)context_ptr+0x00003ae0))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003ae0+4*1))=0x000066d8;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000ae0+4*1))=0x00006058;
*((unsigned int *)((unsigned long)context_ptr+0x00000ae0+4*2))=0x0000631c;
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
if(!memcmp((unsigned char *)context_ptr+0x000061a0,"\x68\xdb\x0f\x35\xcf\x9f\xef\xb9\x51\x38\x90\xfc\xe1\xee\x1a\xcc",16))
printf("strip: 68db0f35cf9fefb9, Pass\n");
else
printf("strip: 68db0f35cf9fefb9, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000066e8))=0x000a0012;
*((unsigned int *)((unsigned long)context_ptr+0x000066e8+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000066e8+4*2))=0x02020076;
*((unsigned int *)((unsigned long)context_ptr+0x000066e8+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x00006360))=0x6f2573d6;
*((unsigned int *)((unsigned long)context_ptr+0x00006360+4*1))=0x9b7c7019;
*((unsigned int *)((unsigned long)context_ptr+0x00006360+4*2))=0x8edeedf2;
*((unsigned int *)((unsigned long)context_ptr+0x00006360+4*3))=0xc825c9c7;
*((unsigned int *)((unsigned long)context_ptr+0x00006360+4*4))=0xbd178865;
*((unsigned int *)((unsigned long)context_ptr+0x00006360+4*5))=0xa300585a;
*((unsigned int *)((unsigned long)context_ptr+0x00006360+4*6))=0xd091bf99;
*((unsigned int *)((unsigned long)context_ptr+0x00006360+4*7))=0xc0ce85e7;
*((unsigned int *)((unsigned long)context_ptr+0x00006360+4*8))=0x324f416a;
*((unsigned int *)((unsigned long)context_ptr+0x00006360+4*9))=0xe21bebfa;
*((unsigned int *)((unsigned long)context_ptr+0x00006360+4*10))=0x231c7eb9;
*((unsigned int *)((unsigned long)context_ptr+0x00006360+4*11))=0x430585f6;
*((unsigned int *)((unsigned long)context_ptr+0x00006360+4*12))=0xbddb640d;
*((unsigned int *)((unsigned long)context_ptr+0x00006360+4*13))=0x4f558362;
*((unsigned int *)((unsigned long)context_ptr+0x00006360+4*14))=0xb7ca8548;
*((unsigned int *)((unsigned long)context_ptr+0x00006360+4*15))=0x742a9f27;
*((unsigned int *)((unsigned long)context_ptr+0x00006360+4*16))=0x691fb8d0;
*((unsigned int *)((unsigned long)context_ptr+0x00006360+4*17))=0x5a5a8adc;
*((unsigned int *)((unsigned long)context_ptr+0x00006360+4*18))=0xcdb7216e;
*((unsigned int *)((unsigned long)context_ptr+0x00006360+4*19))=0x5de42198;
*((unsigned int *)((unsigned long)context_ptr+0x00006360+4*20))=0xb05cf8f9;
*((unsigned int *)((unsigned long)context_ptr+0x00006360+4*21))=0x922fd1e0;
*((unsigned int *)((unsigned long)context_ptr+0x00006360+4*22))=0x600dd4cb;
*((unsigned int *)((unsigned long)context_ptr+0x00006360+4*23))=0x1a1a9ca5;
*((unsigned int *)((unsigned long)context_ptr+0x00006360+4*24))=0xb641daeb;
*((unsigned int *)((unsigned long)context_ptr+0x00006360+4*25))=0x74ec2077;
*((unsigned int *)((unsigned long)context_ptr+0x00006360+4*26))=0x05f8571a;
*((unsigned int *)((unsigned long)context_ptr+0x00006360+4*27))=0x2d94a68f;
*((unsigned int *)((unsigned long)context_ptr+0x00006360+4*28))=0x6e20baf1;
*((unsigned int *)((unsigned long)context_ptr+0x00006360+4*29))=0x00009bb6;
*((unsigned int *)((unsigned long)context_ptr+0x00003af8))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003af8+4*1))=0x000066f8;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000af8+4*1))=0x00006360;
*((unsigned int *)((unsigned long)context_ptr+0x00000af8+4*2))=0x000066e8;
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
if(!memcmp((unsigned char *)context_ptr+0x000061b0,"\x21\x35\xed\xde\xec\xef\x15\x35\xa8\x1f\xe0\xab\x22\xf0\xc6\x9e",16))
printf("strip: 2135eddeecef1535, Pass\n");
else
printf("strip: 2135eddeecef1535, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x0000632c))=0x000a0012;
*((unsigned int *)((unsigned long)context_ptr+0x0000632c+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x0000632c+4*2))=0x02020077;
*((unsigned int *)((unsigned long)context_ptr+0x0000632c+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x000060d0))=0x3c5580b9;
*((unsigned int *)((unsigned long)context_ptr+0x000060d0+4*1))=0x9eba4e9e;
*((unsigned int *)((unsigned long)context_ptr+0x000060d0+4*2))=0xe62101f0;
*((unsigned int *)((unsigned long)context_ptr+0x000060d0+4*3))=0xa764bc5b;
*((unsigned int *)((unsigned long)context_ptr+0x000060d0+4*4))=0x97dc0e45;
*((unsigned int *)((unsigned long)context_ptr+0x000060d0+4*5))=0x11c44eb6;
*((unsigned int *)((unsigned long)context_ptr+0x000060d0+4*6))=0x09c2fffc;
*((unsigned int *)((unsigned long)context_ptr+0x000060d0+4*7))=0xa0641905;
*((unsigned int *)((unsigned long)context_ptr+0x000060d0+4*8))=0xbb0a7e7f;
*((unsigned int *)((unsigned long)context_ptr+0x000060d0+4*9))=0x879577a7;
*((unsigned int *)((unsigned long)context_ptr+0x000060d0+4*10))=0x61afbeb5;
*((unsigned int *)((unsigned long)context_ptr+0x000060d0+4*11))=0x0453900c;
*((unsigned int *)((unsigned long)context_ptr+0x000060d0+4*12))=0x7595206e;
*((unsigned int *)((unsigned long)context_ptr+0x000060d0+4*13))=0xe96bfcce;
*((unsigned int *)((unsigned long)context_ptr+0x000060d0+4*14))=0x8a5d82fb;
*((unsigned int *)((unsigned long)context_ptr+0x000060d0+4*15))=0x065737f9;
*((unsigned int *)((unsigned long)context_ptr+0x000060d0+4*16))=0xd7267ce5;
*((unsigned int *)((unsigned long)context_ptr+0x000060d0+4*17))=0x2241fe7d;
*((unsigned int *)((unsigned long)context_ptr+0x000060d0+4*18))=0x52c991f5;
*((unsigned int *)((unsigned long)context_ptr+0x000060d0+4*19))=0x1b8efa40;
*((unsigned int *)((unsigned long)context_ptr+0x000060d0+4*20))=0x6583b9aa;
*((unsigned int *)((unsigned long)context_ptr+0x000060d0+4*21))=0xcfc8247f;
*((unsigned int *)((unsigned long)context_ptr+0x000060d0+4*22))=0xd90e0ba5;
*((unsigned int *)((unsigned long)context_ptr+0x000060d0+4*23))=0xc31cc0ea;
*((unsigned int *)((unsigned long)context_ptr+0x000060d0+4*24))=0x638d843b;
*((unsigned int *)((unsigned long)context_ptr+0x000060d0+4*25))=0x69cc0557;
*((unsigned int *)((unsigned long)context_ptr+0x000060d0+4*26))=0x5ce7a353;
*((unsigned int *)((unsigned long)context_ptr+0x000060d0+4*27))=0xf93d39df;
*((unsigned int *)((unsigned long)context_ptr+0x000060d0+4*28))=0x379177e5;
*((unsigned int *)((unsigned long)context_ptr+0x000060d0+4*29))=0x00578dc4;
*((unsigned int *)((unsigned long)context_ptr+0x00003b10))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003b10+4*1))=0x00006478;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000b10+4*1))=0x000060d0;
*((unsigned int *)((unsigned long)context_ptr+0x00000b10+4*2))=0x0000632c;
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
if(!memcmp((unsigned char *)context_ptr+0x00006340,"\xa9\x72\xc5\xed\x8e\x94\xb8\xca\x0c\x90\x6b\xbd\x0c\xc3\x7b\x2a",16))
printf("strip: a972c5ed8e94b8ca, Pass\n");
else
printf("strip: a972c5ed8e94b8ca, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000063d8))=0x000a0012;
*((unsigned int *)((unsigned long)context_ptr+0x000063d8+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000063d8+4*2))=0x02020078;
*((unsigned int *)((unsigned long)context_ptr+0x000063d8+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x00006148))=0x3c663b8c;
*((unsigned int *)((unsigned long)context_ptr+0x00006148+4*1))=0x2e7c46c7;
*((unsigned int *)((unsigned long)context_ptr+0x00006148+4*2))=0xcc5bbd8f;
*((unsigned int *)((unsigned long)context_ptr+0x00006148+4*3))=0x7435495f;
*((unsigned int *)((unsigned long)context_ptr+0x00006148+4*4))=0xae180999;
*((unsigned int *)((unsigned long)context_ptr+0x00006148+4*5))=0x51b5551e;
*((unsigned int *)((unsigned long)context_ptr+0x00006148+4*6))=0x9688c451;
*((unsigned int *)((unsigned long)context_ptr+0x00006148+4*7))=0xbe5decee;
*((unsigned int *)((unsigned long)context_ptr+0x00006148+4*8))=0xa9012dc1;
*((unsigned int *)((unsigned long)context_ptr+0x00006148+4*9))=0xd4cecce7;
*((unsigned int *)((unsigned long)context_ptr+0x00006148+4*10))=0x7bd4d99c;
*((unsigned int *)((unsigned long)context_ptr+0x00006148+4*11))=0x24a3fa21;
*((unsigned int *)((unsigned long)context_ptr+0x00006148+4*12))=0x95d385f5;
*((unsigned int *)((unsigned long)context_ptr+0x00006148+4*13))=0x66fec2b4;
*((unsigned int *)((unsigned long)context_ptr+0x00006148+4*14))=0xa8e90b81;
*((unsigned int *)((unsigned long)context_ptr+0x00006148+4*15))=0x3611e097;
*((unsigned int *)((unsigned long)context_ptr+0x00006148+4*16))=0xd548edfc;
*((unsigned int *)((unsigned long)context_ptr+0x00006148+4*17))=0x9dbc6236;
*((unsigned int *)((unsigned long)context_ptr+0x00006148+4*18))=0x4f372caa;
*((unsigned int *)((unsigned long)context_ptr+0x00006148+4*19))=0xe9564470;
*((unsigned int *)((unsigned long)context_ptr+0x00006148+4*20))=0xf8c3fea3;
*((unsigned int *)((unsigned long)context_ptr+0x00006148+4*21))=0x56349ebe;
*((unsigned int *)((unsigned long)context_ptr+0x00006148+4*22))=0xd0f904de;
*((unsigned int *)((unsigned long)context_ptr+0x00006148+4*23))=0x6918d83c;
*((unsigned int *)((unsigned long)context_ptr+0x00006148+4*24))=0x6c10dacd;
*((unsigned int *)((unsigned long)context_ptr+0x00006148+4*25))=0xf25f68cd;
*((unsigned int *)((unsigned long)context_ptr+0x00006148+4*26))=0x869f3d24;
*((unsigned int *)((unsigned long)context_ptr+0x00006148+4*27))=0xc5953159;
*((unsigned int *)((unsigned long)context_ptr+0x00006148+4*28))=0xa57a2d0b;
*((unsigned int *)((unsigned long)context_ptr+0x00006148+4*29))=0x2827c64e;
*((unsigned int *)((unsigned long)context_ptr+0x00003b28))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003b28+4*1))=0x0000633c;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000b28+4*2))=0x000063d8;
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
if(!memcmp((unsigned char *)context_ptr+0x0000622c,"\x06\x8f\x53\xbf\x0d\x1b\x19\xf0\xf5\x40\xb5\x24\x03\x2f\x08\xed",16))
printf("strip: 068f53bf0d1b19f0, Pass\n");
else
printf("strip: 068f53bf0d1b19f0, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006018))=0x000a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006018+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006018+4*2))=0x02020079;
*((unsigned int *)((unsigned long)context_ptr+0x00006018+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x000061c0))=0xb08673fe;
*((unsigned int *)((unsigned long)context_ptr+0x000061c0+4*1))=0xfb9088bc;
*((unsigned int *)((unsigned long)context_ptr+0x000061c0+4*2))=0xc252ea90;
*((unsigned int *)((unsigned long)context_ptr+0x000061c0+4*3))=0xe4066998;
*((unsigned int *)((unsigned long)context_ptr+0x000061c0+4*4))=0x49d1de7d;
*((unsigned int *)((unsigned long)context_ptr+0x000061c0+4*5))=0xd5acd69a;
*((unsigned int *)((unsigned long)context_ptr+0x000061c0+4*6))=0xde152b74;
*((unsigned int *)((unsigned long)context_ptr+0x000061c0+4*7))=0x9854a427;
*((unsigned int *)((unsigned long)context_ptr+0x000061c0+4*8))=0x1a354373;
*((unsigned int *)((unsigned long)context_ptr+0x000061c0+4*9))=0xcfc64b89;
*((unsigned int *)((unsigned long)context_ptr+0x000061c0+4*10))=0xe4bfc260;
*((unsigned int *)((unsigned long)context_ptr+0x000061c0+4*11))=0xfc2fe2b6;
*((unsigned int *)((unsigned long)context_ptr+0x000061c0+4*12))=0x7dcbc749;
*((unsigned int *)((unsigned long)context_ptr+0x000061c0+4*13))=0x374e0ae9;
*((unsigned int *)((unsigned long)context_ptr+0x000061c0+4*14))=0x46328a09;
*((unsigned int *)((unsigned long)context_ptr+0x000061c0+4*15))=0x1e1cca92;
*((unsigned int *)((unsigned long)context_ptr+0x000061c0+4*16))=0x9e8407e0;
*((unsigned int *)((unsigned long)context_ptr+0x000061c0+4*17))=0xbee36712;
*((unsigned int *)((unsigned long)context_ptr+0x000061c0+4*18))=0x87b39cbe;
*((unsigned int *)((unsigned long)context_ptr+0x000061c0+4*19))=0xbcc3f135;
*((unsigned int *)((unsigned long)context_ptr+0x000061c0+4*20))=0xb19d3910;
*((unsigned int *)((unsigned long)context_ptr+0x000061c0+4*21))=0xe61b9172;
*((unsigned int *)((unsigned long)context_ptr+0x000061c0+4*22))=0x640f865d;
*((unsigned int *)((unsigned long)context_ptr+0x000061c0+4*23))=0xc6ca2c92;
*((unsigned int *)((unsigned long)context_ptr+0x000061c0+4*24))=0x633094f7;
*((unsigned int *)((unsigned long)context_ptr+0x000061c0+4*25))=0xa47168c4;
*((unsigned int *)((unsigned long)context_ptr+0x000061c0+4*26))=0x8997656e;
*((unsigned int *)((unsigned long)context_ptr+0x000061c0+4*27))=0xee19f837;
*((unsigned int *)((unsigned long)context_ptr+0x000061c0+4*28))=0x08a469e1;
*((unsigned int *)((unsigned long)context_ptr+0x000061c0+4*29))=0x85bc3293;
*((unsigned int *)((unsigned long)context_ptr+0x000061c0+4*30))=0x00000076;
*((unsigned int *)((unsigned long)context_ptr+0x00003b40))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003b40+4*1))=0x00006488;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000b40+4*1))=0x000061c0;
*((unsigned int *)((unsigned long)context_ptr+0x00000b40+4*2))=0x00006018;
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
if(!memcmp((unsigned char *)context_ptr+0x00006008,"\xcf\x87\x29\xdb\x1b\x01\xfa\xac\xa4\x3a\x2a\x3d\xc1\xa9\xc3\x9a",16))
printf("strip: cf8729db1b01faac, Pass\n");
else
printf("strip: cf8729db1b01faac, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006008))=0x000a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006008+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006008+4*2))=0x0202007a;
*((unsigned int *)((unsigned long)context_ptr+0x00006008+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x00006970))=0x82f6bd79;
*((unsigned int *)((unsigned long)context_ptr+0x00006970+4*1))=0x6287cc99;
*((unsigned int *)((unsigned long)context_ptr+0x00006970+4*2))=0x6a23bec5;
*((unsigned int *)((unsigned long)context_ptr+0x00006970+4*3))=0x0bfeb9be;
*((unsigned int *)((unsigned long)context_ptr+0x00006970+4*4))=0x490d30ba;
*((unsigned int *)((unsigned long)context_ptr+0x00006970+4*5))=0x0474e7bd;
*((unsigned int *)((unsigned long)context_ptr+0x00006970+4*6))=0x86d9f012;
*((unsigned int *)((unsigned long)context_ptr+0x00006970+4*7))=0x9342e832;
*((unsigned int *)((unsigned long)context_ptr+0x00006970+4*8))=0x8f03ccb9;
*((unsigned int *)((unsigned long)context_ptr+0x00006970+4*9))=0x0a7c9548;
*((unsigned int *)((unsigned long)context_ptr+0x00006970+4*10))=0xecaec5ff;
*((unsigned int *)((unsigned long)context_ptr+0x00006970+4*11))=0x0df82c97;
*((unsigned int *)((unsigned long)context_ptr+0x00006970+4*12))=0x8c54a40e;
*((unsigned int *)((unsigned long)context_ptr+0x00006970+4*13))=0x9eb46454;
*((unsigned int *)((unsigned long)context_ptr+0x00006970+4*14))=0xf46b56f0;
*((unsigned int *)((unsigned long)context_ptr+0x00006970+4*15))=0xc9ca1ce8;
*((unsigned int *)((unsigned long)context_ptr+0x00006970+4*16))=0x35ffb541;
*((unsigned int *)((unsigned long)context_ptr+0x00006970+4*17))=0x8334f6c4;
*((unsigned int *)((unsigned long)context_ptr+0x00006970+4*18))=0xaf9f80fb;
*((unsigned int *)((unsigned long)context_ptr+0x00006970+4*19))=0x1d33cc6c;
*((unsigned int *)((unsigned long)context_ptr+0x00006970+4*20))=0x66638abb;
*((unsigned int *)((unsigned long)context_ptr+0x00006970+4*21))=0x87f55b6a;
*((unsigned int *)((unsigned long)context_ptr+0x00006970+4*22))=0x64254ab7;
*((unsigned int *)((unsigned long)context_ptr+0x00006970+4*23))=0x3a9cb6ba;
*((unsigned int *)((unsigned long)context_ptr+0x00006970+4*24))=0x4b430dba;
*((unsigned int *)((unsigned long)context_ptr+0x00006970+4*25))=0x5197a314;
*((unsigned int *)((unsigned long)context_ptr+0x00006970+4*26))=0x8b3decdc;
*((unsigned int *)((unsigned long)context_ptr+0x00006970+4*27))=0xaa1937e7;
*((unsigned int *)((unsigned long)context_ptr+0x00006970+4*28))=0xb9af1ace;
*((unsigned int *)((unsigned long)context_ptr+0x00006970+4*29))=0x53aa4b3a;
*((unsigned int *)((unsigned long)context_ptr+0x00006970+4*30))=0x00001e07;
*((unsigned int *)((unsigned long)context_ptr+0x00003b58))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003b58+4*1))=0x000063e8;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000b58+4*1))=0x00006970;
*((unsigned int *)((unsigned long)context_ptr+0x00000b58+4*2))=0x00006008;
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
if(!memcmp((unsigned char *)context_ptr+0x00006028,"\xd3\xa9\x6e\xbc\x57\xcc\x7b\xe9\xae\x98\xb7\xcf\xca\x4e\x07\xe3",16))
printf("strip: d3a96ebc57cc7be9, Pass\n");
else
printf("strip: d3a96ebc57cc7be9, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006028))=0x000a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006028+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006028+4*2))=0x0202007b;
*((unsigned int *)((unsigned long)context_ptr+0x00006028+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x00006894))=0x447e4647;
*((unsigned int *)((unsigned long)context_ptr+0x00006894+4*1))=0x3aa5f73c;
*((unsigned int *)((unsigned long)context_ptr+0x00006894+4*2))=0x02dbaa81;
*((unsigned int *)((unsigned long)context_ptr+0x00006894+4*3))=0xb33e34a0;
*((unsigned int *)((unsigned long)context_ptr+0x00006894+4*4))=0x47b7ed20;
*((unsigned int *)((unsigned long)context_ptr+0x00006894+4*5))=0x3390b336;
*((unsigned int *)((unsigned long)context_ptr+0x00006894+4*6))=0xc85dcf1d;
*((unsigned int *)((unsigned long)context_ptr+0x00006894+4*7))=0xad39ec7f;
*((unsigned int *)((unsigned long)context_ptr+0x00006894+4*8))=0x2bec3285;
*((unsigned int *)((unsigned long)context_ptr+0x00006894+4*9))=0xc60ef9f2;
*((unsigned int *)((unsigned long)context_ptr+0x00006894+4*10))=0x96ba378a;
*((unsigned int *)((unsigned long)context_ptr+0x00006894+4*11))=0xc2f39a5e;
*((unsigned int *)((unsigned long)context_ptr+0x00006894+4*12))=0xc89b926c;
*((unsigned int *)((unsigned long)context_ptr+0x00006894+4*13))=0x76b443d6;
*((unsigned int *)((unsigned long)context_ptr+0x00006894+4*14))=0x000de5b5;
*((unsigned int *)((unsigned long)context_ptr+0x00006894+4*15))=0x62601678;
*((unsigned int *)((unsigned long)context_ptr+0x00006894+4*16))=0x7119073a;
*((unsigned int *)((unsigned long)context_ptr+0x00006894+4*17))=0xd2980157;
*((unsigned int *)((unsigned long)context_ptr+0x00006894+4*18))=0x83b7ff74;
*((unsigned int *)((unsigned long)context_ptr+0x00006894+4*19))=0xa25593d6;
*((unsigned int *)((unsigned long)context_ptr+0x00006894+4*20))=0xc13d8a8a;
*((unsigned int *)((unsigned long)context_ptr+0x00006894+4*21))=0xda565abd;
*((unsigned int *)((unsigned long)context_ptr+0x00006894+4*22))=0x91636532;
*((unsigned int *)((unsigned long)context_ptr+0x00006894+4*23))=0xa964e91b;
*((unsigned int *)((unsigned long)context_ptr+0x00006894+4*24))=0xb413d8e0;
*((unsigned int *)((unsigned long)context_ptr+0x00006894+4*25))=0xf73457d8;
*((unsigned int *)((unsigned long)context_ptr+0x00006894+4*26))=0x5281f84c;
*((unsigned int *)((unsigned long)context_ptr+0x00006894+4*27))=0x0256a674;
*((unsigned int *)((unsigned long)context_ptr+0x00006894+4*28))=0x7e6665f5;
*((unsigned int *)((unsigned long)context_ptr+0x00006894+4*29))=0x9778c863;
*((unsigned int *)((unsigned long)context_ptr+0x00006894+4*30))=0x00c827a0;
*((unsigned int *)((unsigned long)context_ptr+0x00003b70))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003b70+4*1))=0x000063f8;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000b70+4*1))=0x00006894;
*((unsigned int *)((unsigned long)context_ptr+0x00000b70+4*2))=0x00006028;
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
if(!memcmp((unsigned char *)context_ptr+0x00006350,"\xe2\xb9\x31\x4a\x53\x34\xdf\x64\x68\xc3\xe0\x2e\xce\xae\x53\x21",16))
printf("strip: e2b9314a5334df64, Pass\n");
else
printf("strip: e2b9314a5334df64, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006038))=0x000a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006038+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006038+4*2))=0x0202007c;
*((unsigned int *)((unsigned long)context_ptr+0x00006038+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x000069ec))=0x7dbd8831;
*((unsigned int *)((unsigned long)context_ptr+0x000069ec+4*1))=0x03431be6;
*((unsigned int *)((unsigned long)context_ptr+0x000069ec+4*2))=0xe14c79cc;
*((unsigned int *)((unsigned long)context_ptr+0x000069ec+4*3))=0x6beca2db;
*((unsigned int *)((unsigned long)context_ptr+0x000069ec+4*4))=0xbbeb6a95;
*((unsigned int *)((unsigned long)context_ptr+0x000069ec+4*5))=0x82e51889;
*((unsigned int *)((unsigned long)context_ptr+0x000069ec+4*6))=0x7482b456;
*((unsigned int *)((unsigned long)context_ptr+0x000069ec+4*7))=0x82ad08b7;
*((unsigned int *)((unsigned long)context_ptr+0x000069ec+4*8))=0x03d4f0bf;
*((unsigned int *)((unsigned long)context_ptr+0x000069ec+4*9))=0xef505a73;
*((unsigned int *)((unsigned long)context_ptr+0x000069ec+4*10))=0x1d0996bf;
*((unsigned int *)((unsigned long)context_ptr+0x000069ec+4*11))=0x78e2e66e;
*((unsigned int *)((unsigned long)context_ptr+0x000069ec+4*12))=0x0abe7e29;
*((unsigned int *)((unsigned long)context_ptr+0x000069ec+4*13))=0xf2a7c670;
*((unsigned int *)((unsigned long)context_ptr+0x000069ec+4*14))=0x26bab66b;
*((unsigned int *)((unsigned long)context_ptr+0x000069ec+4*15))=0x00958d60;
*((unsigned int *)((unsigned long)context_ptr+0x000069ec+4*16))=0x53f989a7;
*((unsigned int *)((unsigned long)context_ptr+0x000069ec+4*17))=0x2979864e;
*((unsigned int *)((unsigned long)context_ptr+0x000069ec+4*18))=0x95861a7c;
*((unsigned int *)((unsigned long)context_ptr+0x000069ec+4*19))=0x30e86ac6;
*((unsigned int *)((unsigned long)context_ptr+0x000069ec+4*20))=0x044091be;
*((unsigned int *)((unsigned long)context_ptr+0x000069ec+4*21))=0xad7d132a;
*((unsigned int *)((unsigned long)context_ptr+0x000069ec+4*22))=0xafb4a67e;
*((unsigned int *)((unsigned long)context_ptr+0x000069ec+4*23))=0x20d8c607;
*((unsigned int *)((unsigned long)context_ptr+0x000069ec+4*24))=0x0a23a72d;
*((unsigned int *)((unsigned long)context_ptr+0x000069ec+4*25))=0xa644a2ed;
*((unsigned int *)((unsigned long)context_ptr+0x000069ec+4*26))=0xef1b6265;
*((unsigned int *)((unsigned long)context_ptr+0x000069ec+4*27))=0xa5ebb370;
*((unsigned int *)((unsigned long)context_ptr+0x000069ec+4*28))=0x5317a6b4;
*((unsigned int *)((unsigned long)context_ptr+0x000069ec+4*29))=0x5f4051e3;
*((unsigned int *)((unsigned long)context_ptr+0x000069ec+4*30))=0x9ad96a17;
*((unsigned int *)((unsigned long)context_ptr+0x00003b88))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003b88+4*1))=0x0000634c;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000b88+4*1))=0x000069ec;
*((unsigned int *)((unsigned long)context_ptr+0x00000b88+4*2))=0x00006038;
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
if(!memcmp((unsigned char *)context_ptr+0x000062ac,"\x16\xe5\xd1\xf5\xac\x38\xdc\xd3\xed\x52\x83\x43\x7a\x78\x29\x73",16))
printf("strip: 16e5d1f5ac38dcd3, Pass\n");
else
printf("strip: 16e5d1f5ac38dcd3, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006048))=0x000a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006048+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006048+4*2))=0x0202007d;
*((unsigned int *)((unsigned long)context_ptr+0x00006048+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x0000623c))=0x63e9a154;
*((unsigned int *)((unsigned long)context_ptr+0x0000623c+4*1))=0x6eeb459c;
*((unsigned int *)((unsigned long)context_ptr+0x0000623c+4*2))=0x14120b62;
*((unsigned int *)((unsigned long)context_ptr+0x0000623c+4*3))=0x10423c4f;
*((unsigned int *)((unsigned long)context_ptr+0x0000623c+4*4))=0x3013fe65;
*((unsigned int *)((unsigned long)context_ptr+0x0000623c+4*5))=0xecaa9227;
*((unsigned int *)((unsigned long)context_ptr+0x0000623c+4*6))=0x423ec346;
*((unsigned int *)((unsigned long)context_ptr+0x0000623c+4*7))=0x9445d50c;
*((unsigned int *)((unsigned long)context_ptr+0x0000623c+4*8))=0x44eb8718;
*((unsigned int *)((unsigned long)context_ptr+0x0000623c+4*9))=0x55542f99;
*((unsigned int *)((unsigned long)context_ptr+0x0000623c+4*10))=0x18726746;
*((unsigned int *)((unsigned long)context_ptr+0x0000623c+4*11))=0xb5922d81;
*((unsigned int *)((unsigned long)context_ptr+0x0000623c+4*12))=0x11eace5b;
*((unsigned int *)((unsigned long)context_ptr+0x0000623c+4*13))=0x0847d670;
*((unsigned int *)((unsigned long)context_ptr+0x0000623c+4*14))=0xdc1aef74;
*((unsigned int *)((unsigned long)context_ptr+0x0000623c+4*15))=0xd92f8280;
*((unsigned int *)((unsigned long)context_ptr+0x0000623c+4*16))=0xf592d3c5;
*((unsigned int *)((unsigned long)context_ptr+0x0000623c+4*17))=0xdb642eaa;
*((unsigned int *)((unsigned long)context_ptr+0x0000623c+4*18))=0x205098b4;
*((unsigned int *)((unsigned long)context_ptr+0x0000623c+4*19))=0x72e844ec;
*((unsigned int *)((unsigned long)context_ptr+0x0000623c+4*20))=0xa0211cb3;
*((unsigned int *)((unsigned long)context_ptr+0x0000623c+4*21))=0x50a89e7f;
*((unsigned int *)((unsigned long)context_ptr+0x0000623c+4*22))=0x25df0985;
*((unsigned int *)((unsigned long)context_ptr+0x0000623c+4*23))=0xda03232f;
*((unsigned int *)((unsigned long)context_ptr+0x0000623c+4*24))=0xa64f44c4;
*((unsigned int *)((unsigned long)context_ptr+0x0000623c+4*25))=0xcfd428b3;
*((unsigned int *)((unsigned long)context_ptr+0x0000623c+4*26))=0x190c08ab;
*((unsigned int *)((unsigned long)context_ptr+0x0000623c+4*27))=0x6745a0b2;
*((unsigned int *)((unsigned long)context_ptr+0x0000623c+4*28))=0xa7b34233;
*((unsigned int *)((unsigned long)context_ptr+0x0000623c+4*29))=0xf3e32929;
*((unsigned int *)((unsigned long)context_ptr+0x0000623c+4*30))=0x2c561053;
*((unsigned int *)((unsigned long)context_ptr+0x0000623c+4*31))=0x00000051;
*((unsigned int *)((unsigned long)context_ptr+0x00003ba0))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003ba0+4*1))=0x00006498;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000ba0+4*1))=0x0000623c;
*((unsigned int *)((unsigned long)context_ptr+0x00000ba0+4*2))=0x00006048;
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
if(!memcmp((unsigned char *)context_ptr+0x0000677c,"\x86\x59\x7b\x4c\xc2\xe0\x2e\x0c\xd9\x97\x44\x58\x84\x0b\xda\xaa",16))
printf("strip: 86597b4cc2e02e0c, Pass\n");
else
printf("strip: 86597b4cc2e02e0c, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000062bc))=0x000a0012;
*((unsigned int *)((unsigned long)context_ptr+0x000062bc+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000062bc+4*2))=0x0202007e;
*((unsigned int *)((unsigned long)context_ptr+0x000062bc+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x00006708))=0xcb15a5a5;
*((unsigned int *)((unsigned long)context_ptr+0x00006708+4*1))=0x0ccc9aa7;
*((unsigned int *)((unsigned long)context_ptr+0x00006708+4*2))=0xdff789b4;
*((unsigned int *)((unsigned long)context_ptr+0x00006708+4*3))=0xd2e01261;
*((unsigned int *)((unsigned long)context_ptr+0x00006708+4*4))=0x65121a6b;
*((unsigned int *)((unsigned long)context_ptr+0x00006708+4*5))=0x644dc04f;
*((unsigned int *)((unsigned long)context_ptr+0x00006708+4*6))=0x38fb7cb4;
*((unsigned int *)((unsigned long)context_ptr+0x00006708+4*7))=0x092145b9;
*((unsigned int *)((unsigned long)context_ptr+0x00006708+4*8))=0xefe82262;
*((unsigned int *)((unsigned long)context_ptr+0x00006708+4*9))=0x58856b96;
*((unsigned int *)((unsigned long)context_ptr+0x00006708+4*10))=0x2dd59280;
*((unsigned int *)((unsigned long)context_ptr+0x00006708+4*11))=0x46e668e2;
*((unsigned int *)((unsigned long)context_ptr+0x00006708+4*12))=0x20c42aaf;
*((unsigned int *)((unsigned long)context_ptr+0x00006708+4*13))=0x89fa3469;
*((unsigned int *)((unsigned long)context_ptr+0x00006708+4*14))=0x44186a2c;
*((unsigned int *)((unsigned long)context_ptr+0x00006708+4*15))=0x81dae11f;
*((unsigned int *)((unsigned long)context_ptr+0x00006708+4*16))=0x330330b1;
*((unsigned int *)((unsigned long)context_ptr+0x00006708+4*17))=0x2743a16a;
*((unsigned int *)((unsigned long)context_ptr+0x00006708+4*18))=0xcda658ad;
*((unsigned int *)((unsigned long)context_ptr+0x00006708+4*19))=0x39cb5444;
*((unsigned int *)((unsigned long)context_ptr+0x00006708+4*20))=0x81da213f;
*((unsigned int *)((unsigned long)context_ptr+0x00006708+4*21))=0x4239d3c3;
*((unsigned int *)((unsigned long)context_ptr+0x00006708+4*22))=0xf4549957;
*((unsigned int *)((unsigned long)context_ptr+0x00006708+4*23))=0x55fe0b62;
*((unsigned int *)((unsigned long)context_ptr+0x00006708+4*24))=0x7b4b11a1;
*((unsigned int *)((unsigned long)context_ptr+0x00006708+4*25))=0xebde59c0;
*((unsigned int *)((unsigned long)context_ptr+0x00006708+4*26))=0x4d9394dd;
*((unsigned int *)((unsigned long)context_ptr+0x00006708+4*27))=0xb657071d;
*((unsigned int *)((unsigned long)context_ptr+0x00006708+4*28))=0x63ed7886;
*((unsigned int *)((unsigned long)context_ptr+0x00006708+4*29))=0x3663418a;
*((unsigned int *)((unsigned long)context_ptr+0x00006708+4*30))=0x416cb2b4;
*((unsigned int *)((unsigned long)context_ptr+0x00006708+4*31))=0x0000e74a;
*((unsigned int *)((unsigned long)context_ptr+0x00003bb8))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003bb8+4*1))=0x000064a8;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000bb8+4*1))=0x00006708;
*((unsigned int *)((unsigned long)context_ptr+0x00000bb8+4*2))=0x000062bc;
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
if(!memcmp((unsigned char *)context_ptr+0x0000678c,"\x5e\x3f\x58\x1f\x22\x51\x91\x52\xcc\x57\x11\x7c\x3a\xe1\x1f\xee",16))
printf("strip: 5e3f581f22519152, Pass\n");
else
printf("strip: 5e3f581f22519152, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000062cc))=0x000a0012;
*((unsigned int *)((unsigned long)context_ptr+0x000062cc+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000062cc+4*2))=0x0202007f;
*((unsigned int *)((unsigned long)context_ptr+0x000062cc+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x000065c8))=0xe79471f5;
*((unsigned int *)((unsigned long)context_ptr+0x000065c8+4*1))=0x2529b530;
*((unsigned int *)((unsigned long)context_ptr+0x000065c8+4*2))=0x335667ec;
*((unsigned int *)((unsigned long)context_ptr+0x000065c8+4*3))=0x02998124;
*((unsigned int *)((unsigned long)context_ptr+0x000065c8+4*4))=0xd3293760;
*((unsigned int *)((unsigned long)context_ptr+0x000065c8+4*5))=0x9c8e65b3;
*((unsigned int *)((unsigned long)context_ptr+0x000065c8+4*6))=0x8c439665;
*((unsigned int *)((unsigned long)context_ptr+0x000065c8+4*7))=0x75941bb5;
*((unsigned int *)((unsigned long)context_ptr+0x000065c8+4*8))=0xa2d3360b;
*((unsigned int *)((unsigned long)context_ptr+0x000065c8+4*9))=0x3853cfa5;
*((unsigned int *)((unsigned long)context_ptr+0x000065c8+4*10))=0x342b6bb5;
*((unsigned int *)((unsigned long)context_ptr+0x000065c8+4*11))=0x191d3042;
*((unsigned int *)((unsigned long)context_ptr+0x000065c8+4*12))=0xda4e75d9;
*((unsigned int *)((unsigned long)context_ptr+0x000065c8+4*13))=0x7df11a5c;
*((unsigned int *)((unsigned long)context_ptr+0x000065c8+4*14))=0xcecb1250;
*((unsigned int *)((unsigned long)context_ptr+0x000065c8+4*15))=0x5677f1fb;
*((unsigned int *)((unsigned long)context_ptr+0x000065c8+4*16))=0x602fbb5a;
*((unsigned int *)((unsigned long)context_ptr+0x000065c8+4*17))=0x2bce391f;
*((unsigned int *)((unsigned long)context_ptr+0x000065c8+4*18))=0x289b7a6c;
*((unsigned int *)((unsigned long)context_ptr+0x000065c8+4*19))=0x91b3faaa;
*((unsigned int *)((unsigned long)context_ptr+0x000065c8+4*20))=0xdaeb1083;
*((unsigned int *)((unsigned long)context_ptr+0x000065c8+4*21))=0xa2ce2d06;
*((unsigned int *)((unsigned long)context_ptr+0x000065c8+4*22))=0xd4a67cf2;
*((unsigned int *)((unsigned long)context_ptr+0x000065c8+4*23))=0x9d303d97;
*((unsigned int *)((unsigned long)context_ptr+0x000065c8+4*24))=0x5f42afcc;
*((unsigned int *)((unsigned long)context_ptr+0x000065c8+4*25))=0x3a01a087;
*((unsigned int *)((unsigned long)context_ptr+0x000065c8+4*26))=0xcdf2c3a7;
*((unsigned int *)((unsigned long)context_ptr+0x000065c8+4*27))=0x1e963bf4;
*((unsigned int *)((unsigned long)context_ptr+0x000065c8+4*28))=0xbcb03e9b;
*((unsigned int *)((unsigned long)context_ptr+0x000065c8+4*29))=0x186e0b7c;
*((unsigned int *)((unsigned long)context_ptr+0x000065c8+4*30))=0x23ebd68c;
*((unsigned int *)((unsigned long)context_ptr+0x000065c8+4*31))=0x00df3294;
*((unsigned int *)((unsigned long)context_ptr+0x00003bd0))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003bd0+4*1))=0x00006788;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000bd0+4*1))=0x000065c8;
*((unsigned int *)((unsigned long)context_ptr+0x00000bd0+4*2))=0x000062cc;
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
if(!memcmp((unsigned char *)context_ptr+0x00006810,"\x66\xd2\xa7\x7c\xdf\xc6\x22\xa6\x47\x1c\x79\x26\xe0\x84\xb6\xc2",16))
printf("strip: 66d2a77cdfc622a6, Pass\n");
else
printf("strip: 66d2a77cdfc622a6, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000062dc))=0x000a0012;
*((unsigned int *)((unsigned long)context_ptr+0x000062dc+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000062dc+4*2))=0x02020080;
*((unsigned int *)((unsigned long)context_ptr+0x000062dc+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x00006798))=0xc2769ba7;
*((unsigned int *)((unsigned long)context_ptr+0x00006798+4*1))=0x4871f85e;
*((unsigned int *)((unsigned long)context_ptr+0x00006798+4*2))=0x0eded7a4;
*((unsigned int *)((unsigned long)context_ptr+0x00006798+4*3))=0xecf7be6e;
*((unsigned int *)((unsigned long)context_ptr+0x00006798+4*4))=0xa0bd9905;
*((unsigned int *)((unsigned long)context_ptr+0x00006798+4*5))=0xbcad0e9d;
*((unsigned int *)((unsigned long)context_ptr+0x00006798+4*6))=0x7960c646;
*((unsigned int *)((unsigned long)context_ptr+0x00006798+4*7))=0x941aa03b;
*((unsigned int *)((unsigned long)context_ptr+0x00006798+4*8))=0x8a933b55;
*((unsigned int *)((unsigned long)context_ptr+0x00006798+4*9))=0xdab77b3b;
*((unsigned int *)((unsigned long)context_ptr+0x00006798+4*10))=0x506f0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006798+4*11))=0xf3d95ae6;
*((unsigned int *)((unsigned long)context_ptr+0x00006798+4*12))=0x192d4ce4;
*((unsigned int *)((unsigned long)context_ptr+0x00006798+4*13))=0x408be758;
*((unsigned int *)((unsigned long)context_ptr+0x00006798+4*14))=0xea550bbe;
*((unsigned int *)((unsigned long)context_ptr+0x00006798+4*15))=0x94a1c243;
*((unsigned int *)((unsigned long)context_ptr+0x00006798+4*16))=0x575195c8;
*((unsigned int *)((unsigned long)context_ptr+0x00006798+4*17))=0x3607c31e;
*((unsigned int *)((unsigned long)context_ptr+0x00006798+4*18))=0x95eba041;
*((unsigned int *)((unsigned long)context_ptr+0x00006798+4*19))=0x6ed1e808;
*((unsigned int *)((unsigned long)context_ptr+0x00006798+4*20))=0x957ff50d;
*((unsigned int *)((unsigned long)context_ptr+0x00006798+4*21))=0x2008dcab;
*((unsigned int *)((unsigned long)context_ptr+0x00006798+4*22))=0x9e9eb4d2;
*((unsigned int *)((unsigned long)context_ptr+0x00006798+4*23))=0xfe253220;
*((unsigned int *)((unsigned long)context_ptr+0x00006798+4*24))=0x4a08f450;
*((unsigned int *)((unsigned long)context_ptr+0x00006798+4*25))=0x65546477;
*((unsigned int *)((unsigned long)context_ptr+0x00006798+4*26))=0xc33ed15c;
*((unsigned int *)((unsigned long)context_ptr+0x00006798+4*27))=0x144413db;
*((unsigned int *)((unsigned long)context_ptr+0x00006798+4*28))=0x966a079f;
*((unsigned int *)((unsigned long)context_ptr+0x00006798+4*29))=0x3eb1dd03;
*((unsigned int *)((unsigned long)context_ptr+0x00006798+4*30))=0xf05a1a4f;
*((unsigned int *)((unsigned long)context_ptr+0x00006798+4*31))=0xf8af3cc5;
*((unsigned int *)((unsigned long)context_ptr+0x00003be8))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003be8+4*1))=0x000064b8;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000be8+4*1))=0x00006798;
*((unsigned int *)((unsigned long)context_ptr+0x00000be8+4*2))=0x000062dc;
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
if(!memcmp((unsigned char *)context_ptr+0x000066a8,"\x70\x30\x98\xa9\xaf\x4b\x8b\xb8\xb3\xe4\x23\x16\x79\xef\x0f\x55",16))
printf("strip: 703098a9af4b8bb8, Pass\n");
else
printf("strip: 703098a9af4b8bb8, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000062ec))=0x000a0012;
*((unsigned int *)((unsigned long)context_ptr+0x000062ec+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000062ec+4*2))=0x02020081;
*((unsigned int *)((unsigned long)context_ptr+0x000062ec+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x00006a68))=0x000824df;
*((unsigned int *)((unsigned long)context_ptr+0x00006a68+4*1))=0x5b8d2cfa;
*((unsigned int *)((unsigned long)context_ptr+0x00006a68+4*2))=0x7625bd31;
*((unsigned int *)((unsigned long)context_ptr+0x00006a68+4*3))=0x446729f1;
*((unsigned int *)((unsigned long)context_ptr+0x00006a68+4*4))=0x82d8bbaf;
*((unsigned int *)((unsigned long)context_ptr+0x00006a68+4*5))=0x56f861cf;
*((unsigned int *)((unsigned long)context_ptr+0x00006a68+4*6))=0x57900310;
*((unsigned int *)((unsigned long)context_ptr+0x00006a68+4*7))=0x5c937160;
*((unsigned int *)((unsigned long)context_ptr+0x00006a68+4*8))=0x0ed1407a;
*((unsigned int *)((unsigned long)context_ptr+0x00006a68+4*9))=0x492d7fe1;
*((unsigned int *)((unsigned long)context_ptr+0x00006a68+4*10))=0x9ef726a6;
*((unsigned int *)((unsigned long)context_ptr+0x00006a68+4*11))=0x1fe1e4dd;
*((unsigned int *)((unsigned long)context_ptr+0x00006a68+4*12))=0x52b7dca0;
*((unsigned int *)((unsigned long)context_ptr+0x00006a68+4*13))=0xeb9a019b;
*((unsigned int *)((unsigned long)context_ptr+0x00006a68+4*14))=0x820fc664;
*((unsigned int *)((unsigned long)context_ptr+0x00006a68+4*15))=0x21351906;
*((unsigned int *)((unsigned long)context_ptr+0x00006a68+4*16))=0x16b60c08;
*((unsigned int *)((unsigned long)context_ptr+0x00006a68+4*17))=0x287938a4;
*((unsigned int *)((unsigned long)context_ptr+0x00006a68+4*18))=0x276f4bb7;
*((unsigned int *)((unsigned long)context_ptr+0x00006a68+4*19))=0x0d008b05;
*((unsigned int *)((unsigned long)context_ptr+0x00006a68+4*20))=0x788cff42;
*((unsigned int *)((unsigned long)context_ptr+0x00006a68+4*21))=0xb1749929;
*((unsigned int *)((unsigned long)context_ptr+0x00006a68+4*22))=0x07772a98;
*((unsigned int *)((unsigned long)context_ptr+0x00006a68+4*23))=0x9ec21ca3;
*((unsigned int *)((unsigned long)context_ptr+0x00006a68+4*24))=0x30c0f24b;
*((unsigned int *)((unsigned long)context_ptr+0x00006a68+4*25))=0x2c43cc47;
*((unsigned int *)((unsigned long)context_ptr+0x00006a68+4*26))=0x2e383343;
*((unsigned int *)((unsigned long)context_ptr+0x00006a68+4*27))=0x5574f32f;
*((unsigned int *)((unsigned long)context_ptr+0x00006a68+4*28))=0x973bce8d;
*((unsigned int *)((unsigned long)context_ptr+0x00006a68+4*29))=0x99836fd6;
*((unsigned int *)((unsigned long)context_ptr+0x00006a68+4*30))=0x9ecd5742;
*((unsigned int *)((unsigned long)context_ptr+0x00006a68+4*31))=0x9d4e3ead;
*((unsigned int *)((unsigned long)context_ptr+0x00006a68+4*32))=0x00000030;
*((unsigned int *)((unsigned long)context_ptr+0x00003c00))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003c00+4*1))=0x000064c8;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000c00+4*1))=0x00006a68;
*((unsigned int *)((unsigned long)context_ptr+0x00000c00+4*2))=0x000062ec;
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
if(!memcmp((unsigned char *)context_ptr+0x000066b8,"\x5d\xb5\x64\x20\xf8\x6a\xb8\xcf\xe7\xff\x4a\x14\xb6\x58\xcd\x6e",16))
printf("strip: 5db56420f86ab8cf, Pass\n");
else
printf("strip: 5db56420f86ab8cf, Failed\n");
writel(0x000002b8&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000066c8,"\xdb\xeb\x01\xd3\x3f\xd3\x89\x5f\x28\x77\xd1\x83\x68\xdb\x36\xd5",16))
printf("strip: dbeb01d33fd3895f, Pass\n");
else
printf("strip: dbeb01d33fd3895f, Failed\n");
writel(0x000002be&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000066d8,"\x79\x81\x96\x0f\x62\xf5\x60\xa6\x4f\xbc\x5f\xff\xe8\x3b\x70\xbc",16))
printf("strip: 7981960f62f560a6, Pass\n");
else
printf("strip: 7981960f62f560a6, Failed\n");
writel(0x000002c4&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000066f8,"\x2d\xe1\xfe\xff\xfc\x5f\x08\xb9\x34\x35\xb2\xfd\x32\xb4\xe6\xe4",16))
printf("strip: 2de1fefffc5f08b9, Pass\n");
else
printf("strip: 2de1fefffc5f08b9, Failed\n");
writel(0x000002ca&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006478,"\x26\x4e\x85\x7a\xe0\xc4\x85\xe3\xa8\x04\xa6\x27\x83\xc9\xc1\xf0",16))
printf("strip: 264e857ae0c485e3, Pass\n");
else
printf("strip: 264e857ae0c485e3, Failed\n");
writel(0x000002d0&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x0000633c,"\x11\x32\x3b\x23\xc9\x44\xe9\x17\xff\x59\x3a\x68\x6e\x5c\x0d\x96",16))
printf("strip: 11323b23c944e917, Pass\n");
else
printf("strip: 11323b23c944e917, Failed\n");
writel(0x000002d6&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006488,"\xe5\x25\x93\xe4\x83\x5b\xc5\x28\x9d\xe7\x90\x13\x0c\xcc\xb0\x5c",16))
printf("strip: e52593e4835bc528, Pass\n");
else
printf("strip: e52593e4835bc528, Failed\n");
writel(0x000002dc&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000063e8,"\xef\x43\xe0\x85\x36\x16\x6e\x20\xb6\x33\x71\xbb\x21\x7d\x91\x36",16))
printf("strip: ef43e08536166e20, Pass\n");
else
printf("strip: ef43e08536166e20, Failed\n");
writel(0x000002e2&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000063f8,"\x6c\x01\x16\xf1\x5b\x8a\xfb\x54\x1b\x08\x1f\xe6\x78\xf8\x55\x9e",16))
printf("strip: 6c0116f15b8afb54, Pass\n");
else
printf("strip: 6c0116f15b8afb54, Failed\n");
writel(0x000002e8&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x0000634c,"\x4c\xbc\xc8\xdf\x89\x56\x49\x5c\xb7\x06\x48\xf6\x94\x9c\x77\x24",16))
printf("strip: 4cbcc8df8956495c, Pass\n");
else
printf("strip: 4cbcc8df8956495c, Failed\n");
writel(0x000002ee&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006498,"\xcb\x10\xe8\x4d\x12\x38\x2e\x14\x22\xdc\x74\x6e\x7a\x8f\x78\xfe",16))
printf("strip: cb10e84d12382e14, Pass\n");
else
printf("strip: cb10e84d12382e14, Failed\n");
writel(0x000002f4&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000064a8,"\xa4\x76\x14\x2b\x61\xd8\x6f\x75\xbb\x82\x16\x22\x32\x09\x26\x3b",16))
printf("strip: a476142b61d86f75, Pass\n");
else
printf("strip: a476142b61d86f75, Failed\n");
writel(0x000002fa&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006788,"\xe6\x65\x70\xb5\xe8\x60\xfe\xa6\x65\x4e\xf0\xfc\x83\x54\xbc\x9b",16))
printf("strip: e66570b5e860fea6, Pass\n");
else
printf("strip: e66570b5e860fea6, Failed\n");
writel(0x00000300&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
writel(0x00000c00&0xffffffff,ivp_cae_base_addr+0x00000830);
if(!memcmp((unsigned char *)context_ptr+0x000064b8,"\xae\xe1\xef\xc6\xbd\x30\xaa\x68\x3e\xbb\x31\x9a\x30\x57\x1a\x4b",16))
printf("strip: aee1efc6bd30aa68, Pass\n");
else
printf("strip: aee1efc6bd30aa68, Failed\n");
writel(0x00000006&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000064c8,"\x1c\x8a\x8c\xec\x78\xca\xe5\xe1\x5f\x78\x92\x41\x41\xf2\x8d\xb4",16))
printf("strip: 1c8a8cec78cae5e1, Pass\n");
else
printf("strip: 1c8a8cec78cae5e1, Failed\n");
}

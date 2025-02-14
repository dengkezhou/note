#include <common.h>
#include <malloc.h>

extern volatile unsigned int ivp_cae_base_addr;

void test_hmac_md5(void)
{
unsigned int *context_ptr=(unsigned int *)0x14000000;
printf("test_hmac_md5\n");
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
*((unsigned int *)((unsigned long)context_ptr+0x00006000))=0x006a0802;
*((unsigned int *)((unsigned long)context_ptr+0x00006000+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006000+4*2))=0xadfe44d8;
*((unsigned int *)((unsigned long)context_ptr+0x00006000+4*3))=0x661a87bf;
*((unsigned int *)((unsigned long)context_ptr+0x00006000+4*4))=0x4c157396;
*((unsigned int *)((unsigned long)context_ptr+0x00006000+4*5))=0x4a936c28;
*((unsigned int *)((unsigned long)context_ptr+0x00006000+4*6))=0xbaa9b166;
*((unsigned int *)((unsigned long)context_ptr+0x00006000+4*7))=0x308eb6e6;
*((unsigned int *)((unsigned long)context_ptr+0x00006000+4*8))=0x12bd6327;
*((unsigned int *)((unsigned long)context_ptr+0x00006000+4*9))=0xa44e9188;
*((unsigned int *)((unsigned long)context_ptr+0x00006028))=0x006a0802;
*((unsigned int *)((unsigned long)context_ptr+0x00006028+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006028+4*2))=0x02020001;
*((unsigned int *)((unsigned long)context_ptr+0x00006028+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x00006038))=0x000000ae;
*((unsigned int *)((unsigned long)context_ptr+0x00003000))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003000+4*1))=0x0000603c;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000000+4*1))=0x00006038;
*((unsigned int *)((unsigned long)context_ptr+0x00000000+4*2))=0x00006028;
*((unsigned int *)((unsigned long)context_ptr+0x00000000+4*3))=0x02220001;
*((unsigned int *)((unsigned long)context_ptr+0x00000000+4*4))=0x0eac3920;
*((unsigned int *)((unsigned long)context_ptr+0x00000000+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x0000604c))=0x006a0802;
*((unsigned int *)((unsigned long)context_ptr+0x0000604c+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x0000604c+4*2))=0x02020002;
*((unsigned int *)((unsigned long)context_ptr+0x0000604c+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x0000605c))=0x0000a726;
*((unsigned int *)((unsigned long)context_ptr+0x00003018))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003018+4*1))=0x00006060;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000018+4*1))=0x0000605c;
*((unsigned int *)((unsigned long)context_ptr+0x00000018+4*2))=0x0000604c;
*((unsigned int *)((unsigned long)context_ptr+0x00000018+4*3))=0x02220002;
*((unsigned int *)((unsigned long)context_ptr+0x00000018+4*4))=0x0e6addd8;
*((unsigned int *)((unsigned long)context_ptr+0x00000018+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x00006070))=0x006a0802;
*((unsigned int *)((unsigned long)context_ptr+0x00006070+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006070+4*2))=0x02020003;
*((unsigned int *)((unsigned long)context_ptr+0x00006070+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x00006080))=0x004920a4;
*((unsigned int *)((unsigned long)context_ptr+0x00003030))=0x04c00010;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000030+4*4))=0x00932f5a;
*((unsigned int *)((unsigned long)context_ptr+0x00000030+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x00006094))=0x006a0802;
*((unsigned int *)((unsigned long)context_ptr+0x00006094+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006094+4*2))=0x02020004;
*((unsigned int *)((unsigned long)context_ptr+0x00006094+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x000060a4))=0xeacce920;
*((unsigned int *)((unsigned long)context_ptr+0x00003048))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003048+4*1))=0x000060a8;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000048+4*1))=0x000060a4;
*((unsigned int *)((unsigned long)context_ptr+0x00000048+4*2))=0x00006094;
*((unsigned int *)((unsigned long)context_ptr+0x00000048+4*3))=0x02220004;
*((unsigned int *)((unsigned long)context_ptr+0x00000048+4*4))=0x0cf6c997;
*((unsigned int *)((unsigned long)context_ptr+0x00000048+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x000060b8))=0x006a0802;
*((unsigned int *)((unsigned long)context_ptr+0x000060b8+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000060b8+4*2))=0x02020005;
*((unsigned int *)((unsigned long)context_ptr+0x000060b8+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x000060c8))=0xaf7207bb;
*((unsigned int *)((unsigned long)context_ptr+0x000060c8+4*1))=0x00000007;
*((unsigned int *)((unsigned long)context_ptr+0x00003060))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003060+4*1))=0x000060d0;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000060+4*1))=0x000060c8;
*((unsigned int *)((unsigned long)context_ptr+0x00000060+4*2))=0x000060b8;
*((unsigned int *)((unsigned long)context_ptr+0x00000060+4*3))=0x02220005;
*((unsigned int *)((unsigned long)context_ptr+0x00000060+4*4))=0x0b8f8901;
*((unsigned int *)((unsigned long)context_ptr+0x00000060+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x000060e0))=0x006a0802;
*((unsigned int *)((unsigned long)context_ptr+0x000060e0+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000060e0+4*2))=0x02020006;
*((unsigned int *)((unsigned long)context_ptr+0x000060e0+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x000060f0))=0x28941afe;
*((unsigned int *)((unsigned long)context_ptr+0x000060f0+4*1))=0x0000f2e5;
*((unsigned int *)((unsigned long)context_ptr+0x00003078))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003078+4*1))=0x000060f8;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000078+4*1))=0x000060f0;
*((unsigned int *)((unsigned long)context_ptr+0x00000078+4*2))=0x000060e0;
*((unsigned int *)((unsigned long)context_ptr+0x00000078+4*3))=0x02220006;
*((unsigned int *)((unsigned long)context_ptr+0x00000078+4*4))=0x03e2aad2;
*((unsigned int *)((unsigned long)context_ptr+0x00000078+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x00006108))=0x006a0802;
*((unsigned int *)((unsigned long)context_ptr+0x00006108+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006108+4*2))=0x02020007;
*((unsigned int *)((unsigned long)context_ptr+0x00006108+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x00006118))=0x743f6ec4;
*((unsigned int *)((unsigned long)context_ptr+0x00006118+4*1))=0x007624ef;
*((unsigned int *)((unsigned long)context_ptr+0x00003090))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003090+4*1))=0x00006120;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000090+4*1))=0x00006118;
*((unsigned int *)((unsigned long)context_ptr+0x00000090+4*2))=0x00006108;
*((unsigned int *)((unsigned long)context_ptr+0x00000090+4*3))=0x02220007;
*((unsigned int *)((unsigned long)context_ptr+0x00000090+4*4))=0x03421bea;
*((unsigned int *)((unsigned long)context_ptr+0x00000090+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x00006130))=0x006a0802;
*((unsigned int *)((unsigned long)context_ptr+0x00006130+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006130+4*2))=0x02020008;
*((unsigned int *)((unsigned long)context_ptr+0x00006130+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x00006140))=0x6a29eb3f;
*((unsigned int *)((unsigned long)context_ptr+0x00006140+4*1))=0xa092854a;
*((unsigned int *)((unsigned long)context_ptr+0x000030a8))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x000030a8+4*1))=0x00006148;
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
*((unsigned int *)((unsigned long)context_ptr+0x000000a8+4*1))=0x00006140;
*((unsigned int *)((unsigned long)context_ptr+0x000000a8+4*2))=0x00006130;
*((unsigned int *)((unsigned long)context_ptr+0x000000a8+4*3))=0x02220008;
*((unsigned int *)((unsigned long)context_ptr+0x000000a8+4*4))=0x0a274c0c;
*((unsigned int *)((unsigned long)context_ptr+0x000000a8+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x00006158))=0x006a0802;
*((unsigned int *)((unsigned long)context_ptr+0x00006158+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006158+4*2))=0x02020009;
*((unsigned int *)((unsigned long)context_ptr+0x00006158+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x00006168))=0xb3dfff9e;
*((unsigned int *)((unsigned long)context_ptr+0x00006168+4*1))=0x49c03aba;
*((unsigned int *)((unsigned long)context_ptr+0x00006168+4*2))=0x0000001a;
*((unsigned int *)((unsigned long)context_ptr+0x000030c0))=0x04c00010;
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
*((unsigned int *)((unsigned long)context_ptr+0x000000c0+4*4))=0x02b12c92;
*((unsigned int *)((unsigned long)context_ptr+0x000000c0+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x00006184))=0x006a0802;
*((unsigned int *)((unsigned long)context_ptr+0x00006184+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006184+4*2))=0x0202000a;
*((unsigned int *)((unsigned long)context_ptr+0x00006184+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x00006194))=0x7d94efee;
*((unsigned int *)((unsigned long)context_ptr+0x00006194+4*1))=0x0b4437b4;
*((unsigned int *)((unsigned long)context_ptr+0x00006194+4*2))=0x00000029;
*((unsigned int *)((unsigned long)context_ptr+0x000030d8))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x000030d8+4*1))=0x000061a0;
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
*((unsigned int *)((unsigned long)context_ptr+0x000000d8+4*1))=0x00006194;
*((unsigned int *)((unsigned long)context_ptr+0x000000d8+4*2))=0x00006184;
*((unsigned int *)((unsigned long)context_ptr+0x000000d8+4*3))=0x0222000a;
*((unsigned int *)((unsigned long)context_ptr+0x000000d8+4*4))=0x0c963d14;
*((unsigned int *)((unsigned long)context_ptr+0x000000d8+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x000061b0))=0x006a0802;
*((unsigned int *)((unsigned long)context_ptr+0x000061b0+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000061b0+4*2))=0x0202000b;
*((unsigned int *)((unsigned long)context_ptr+0x000061b0+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x000061c0))=0x70eb69c3;
*((unsigned int *)((unsigned long)context_ptr+0x000061c0+4*1))=0xd4c16d13;
*((unsigned int *)((unsigned long)context_ptr+0x000061c0+4*2))=0x007d2e0a;
*((unsigned int *)((unsigned long)context_ptr+0x000030f0))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x000030f0+4*1))=0x000061cc;
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
*((unsigned int *)((unsigned long)context_ptr+0x000000f0+4*1))=0x000061c0;
*((unsigned int *)((unsigned long)context_ptr+0x000000f0+4*2))=0x000061b0;
*((unsigned int *)((unsigned long)context_ptr+0x000000f0+4*3))=0x0222000b;
*((unsigned int *)((unsigned long)context_ptr+0x000000f0+4*4))=0x0ef38d41;
*((unsigned int *)((unsigned long)context_ptr+0x000000f0+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x000061dc))=0x006a0802;
*((unsigned int *)((unsigned long)context_ptr+0x000061dc+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000061dc+4*2))=0x0202000c;
*((unsigned int *)((unsigned long)context_ptr+0x000061dc+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x000061ec))=0x538dcf2b;
*((unsigned int *)((unsigned long)context_ptr+0x000061ec+4*1))=0x65210695;
*((unsigned int *)((unsigned long)context_ptr+0x000061ec+4*2))=0xc31382f9;
*((unsigned int *)((unsigned long)context_ptr+0x00003108))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003108+4*1))=0x000061f8;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000108+4*1))=0x000061ec;
*((unsigned int *)((unsigned long)context_ptr+0x00000108+4*2))=0x000061dc;
*((unsigned int *)((unsigned long)context_ptr+0x00000108+4*3))=0x0222000c;
*((unsigned int *)((unsigned long)context_ptr+0x00000108+4*4))=0x091ca9f8;
*((unsigned int *)((unsigned long)context_ptr+0x00000108+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x00006208))=0x006a0802;
*((unsigned int *)((unsigned long)context_ptr+0x00006208+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006208+4*2))=0x0202000d;
*((unsigned int *)((unsigned long)context_ptr+0x00006208+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x00006218))=0x26bb8a5b;
*((unsigned int *)((unsigned long)context_ptr+0x00006218+4*1))=0x0b06a005;
*((unsigned int *)((unsigned long)context_ptr+0x00006218+4*2))=0x0f11a739;
*((unsigned int *)((unsigned long)context_ptr+0x00006218+4*3))=0x000000f8;
*((unsigned int *)((unsigned long)context_ptr+0x00003120))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003120+4*1))=0x00006228;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000120+4*1))=0x00006218;
*((unsigned int *)((unsigned long)context_ptr+0x00000120+4*2))=0x00006208;
*((unsigned int *)((unsigned long)context_ptr+0x00000120+4*3))=0x0222000d;
*((unsigned int *)((unsigned long)context_ptr+0x00000120+4*4))=0x0376e22a;
*((unsigned int *)((unsigned long)context_ptr+0x00000120+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x00006238))=0x006a0802;
*((unsigned int *)((unsigned long)context_ptr+0x00006238+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006238+4*2))=0x0202000e;
*((unsigned int *)((unsigned long)context_ptr+0x00006238+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x00006248))=0xee06bbce;
*((unsigned int *)((unsigned long)context_ptr+0x00006248+4*1))=0x264a1609;
*((unsigned int *)((unsigned long)context_ptr+0x00006248+4*2))=0x67bc5b3c;
*((unsigned int *)((unsigned long)context_ptr+0x00006248+4*3))=0x00007e45;
*((unsigned int *)((unsigned long)context_ptr+0x00003138))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003138+4*1))=0x00006258;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000138+4*1))=0x00006248;
*((unsigned int *)((unsigned long)context_ptr+0x00000138+4*2))=0x00006238;
*((unsigned int *)((unsigned long)context_ptr+0x00000138+4*3))=0x0222000e;
*((unsigned int *)((unsigned long)context_ptr+0x00000138+4*4))=0x0e689e5d;
*((unsigned int *)((unsigned long)context_ptr+0x00000138+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x00006268))=0x006a0802;
*((unsigned int *)((unsigned long)context_ptr+0x00006268+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006268+4*2))=0x0202000f;
*((unsigned int *)((unsigned long)context_ptr+0x00006268+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x00006278))=0xfc99c852;
*((unsigned int *)((unsigned long)context_ptr+0x00006278+4*1))=0x200b2400;
*((unsigned int *)((unsigned long)context_ptr+0x00006278+4*2))=0xf27af2ed;
*((unsigned int *)((unsigned long)context_ptr+0x00006278+4*3))=0x00bfc7d1;
*((unsigned int *)((unsigned long)context_ptr+0x00003150))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003150+4*1))=0x00006288;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000150+4*1))=0x00006278;
*((unsigned int *)((unsigned long)context_ptr+0x00000150+4*2))=0x00006268;
*((unsigned int *)((unsigned long)context_ptr+0x00000150+4*3))=0x0222000f;
*((unsigned int *)((unsigned long)context_ptr+0x00000150+4*4))=0x06c83596;
*((unsigned int *)((unsigned long)context_ptr+0x00000150+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000006&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x0000603c,"\x41\xc8\x89\xd9\xcd\x5a\xb2\x64\x1b\x29\x53\xa9\x5a\xaa\xd7\x24",16))
printf("strip: 41c889d9cd5ab264, Pass\n");
else
printf("strip: 41c889d9cd5ab264, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006028))=0x006a0802;
*((unsigned int *)((unsigned long)context_ptr+0x00006028+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006028+4*2))=0x02020010;
*((unsigned int *)((unsigned long)context_ptr+0x00006028+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x00006038))=0xf146e43f;
*((unsigned int *)((unsigned long)context_ptr+0x00006038+4*1))=0xbe7213ed;
*((unsigned int *)((unsigned long)context_ptr+0x00006038+4*2))=0xb4ce8273;
*((unsigned int *)((unsigned long)context_ptr+0x00006038+4*3))=0xedec2af5;
*((unsigned int *)((unsigned long)context_ptr+0x00003168))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003168+4*1))=0x00006298;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000168+4*1))=0x00006038;
*((unsigned int *)((unsigned long)context_ptr+0x00000168+4*2))=0x00006028;
*((unsigned int *)((unsigned long)context_ptr+0x00000168+4*3))=0x02220010;
*((unsigned int *)((unsigned long)context_ptr+0x00000168+4*4))=0x040b000a;
*((unsigned int *)((unsigned long)context_ptr+0x00000168+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000000c&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006060,"\x93\x48\x80\x97\x50\x77\xab\x8f\x64\x5e\xed\x54\xeb\x6b\x5e\x52",16))
printf("strip: 934880975077ab8f, Pass\n");
else
printf("strip: 934880975077ab8f, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006048))=0x006a0802;
*((unsigned int *)((unsigned long)context_ptr+0x00006048+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006048+4*2))=0x02020011;
*((unsigned int *)((unsigned long)context_ptr+0x00006048+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x00006058))=0xc3a47b22;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*1))=0x8e0bd20b;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*2))=0x58f3a1be;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*3))=0xd08f1595;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*4))=0x00000033;
*((unsigned int *)((unsigned long)context_ptr+0x00003180))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003180+4*1))=0x000062a8;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000180+4*1))=0x00006058;
*((unsigned int *)((unsigned long)context_ptr+0x00000180+4*2))=0x00006048;
*((unsigned int *)((unsigned long)context_ptr+0x00000180+4*3))=0x02220011;
*((unsigned int *)((unsigned long)context_ptr+0x00000180+4*4))=0x040fe689;
*((unsigned int *)((unsigned long)context_ptr+0x00000180+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000012&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006084,"\x4c\x30\xd6\x00\xa5\x45\x9f\x40\x80\x9f\x0f\x21\xd7\x06\xf2\xee",16))
printf("strip: 4c30d600a5459f40, Pass\n");
else
printf("strip: 4c30d600a5459f40, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x0000606c))=0x006a0802;
*((unsigned int *)((unsigned long)context_ptr+0x0000606c+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x0000606c+4*2))=0x02020012;
*((unsigned int *)((unsigned long)context_ptr+0x0000606c+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x0000607c))=0x5bb6c40d;
*((unsigned int *)((unsigned long)context_ptr+0x0000607c+4*1))=0x5a0d13d5;
*((unsigned int *)((unsigned long)context_ptr+0x0000607c+4*2))=0x90acc1e6;
*((unsigned int *)((unsigned long)context_ptr+0x0000607c+4*3))=0xcd0769cd;
*((unsigned int *)((unsigned long)context_ptr+0x0000607c+4*4))=0x00006330;
*((unsigned int *)((unsigned long)context_ptr+0x00003198))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003198+4*1))=0x000062b8;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000198+4*4))=0x059cd011;
*((unsigned int *)((unsigned long)context_ptr+0x00000198+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000060a8,"\xc9\x32\xca\x92\x16\xa4\x5d\xe9\x6d\xf9\xf1\xec\x47\x99\x24\xdc",16))
printf("strip: c932ca9216a45de9, Pass\n");
else
printf("strip: c932ca9216a45de9, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006090))=0x006a0802;
*((unsigned int *)((unsigned long)context_ptr+0x00006090+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006090+4*2))=0x02020013;
*((unsigned int *)((unsigned long)context_ptr+0x00006090+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x000060a0))=0x9023e076;
*((unsigned int *)((unsigned long)context_ptr+0x000060a0+4*1))=0x6301ee03;
*((unsigned int *)((unsigned long)context_ptr+0x000060a0+4*2))=0xd204ffcd;
*((unsigned int *)((unsigned long)context_ptr+0x000060a0+4*3))=0x1cc60982;
*((unsigned int *)((unsigned long)context_ptr+0x000060a0+4*4))=0x00acc79c;
*((unsigned int *)((unsigned long)context_ptr+0x000031b0))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x000031b0+4*1))=0x000062c8;
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
*((unsigned int *)((unsigned long)context_ptr+0x000001b0+4*4))=0x06faefec;
*((unsigned int *)((unsigned long)context_ptr+0x000001b0+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000001e&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000060d0,"\x53\xc2\xb4\x0a\xf6\x14\xce\x21\x3a\x87\x20\xd7\xef\xbd\x93\x65",16))
printf("strip: 53c2b40af614ce21, Pass\n");
else
printf("strip: 53c2b40af614ce21, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000060b4))=0x006a0802;
*((unsigned int *)((unsigned long)context_ptr+0x000060b4+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000060b4+4*2))=0x02020014;
*((unsigned int *)((unsigned long)context_ptr+0x000060b4+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x000060c4))=0xa058ee80;
*((unsigned int *)((unsigned long)context_ptr+0x000060c4+4*1))=0x32c0a1c4;
*((unsigned int *)((unsigned long)context_ptr+0x000060c4+4*2))=0x4b952df5;
*((unsigned int *)((unsigned long)context_ptr+0x000060c4+4*3))=0xae6e4aa2;
*((unsigned int *)((unsigned long)context_ptr+0x000060c4+4*4))=0x2158ba44;
*((unsigned int *)((unsigned long)context_ptr+0x000031c8))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x000031c8+4*1))=0x000062d8;
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
*((unsigned int *)((unsigned long)context_ptr+0x000001c8+4*1))=0x000060c4;
*((unsigned int *)((unsigned long)context_ptr+0x000001c8+4*2))=0x000060b4;
*((unsigned int *)((unsigned long)context_ptr+0x000001c8+4*3))=0x02220014;
*((unsigned int *)((unsigned long)context_ptr+0x000001c8+4*4))=0x06e3a52c;
*((unsigned int *)((unsigned long)context_ptr+0x000001c8+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000024&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000060f8,"\xad\x5e\x46\x92\xc7\xf5\x73\x8c\xf9\xaa\xda\xce\x67\x5f\x46\xec",16))
printf("strip: ad5e4692c7f5738c, Pass\n");
else
printf("strip: ad5e4692c7f5738c, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000060d8))=0x006a0802;
*((unsigned int *)((unsigned long)context_ptr+0x000060d8+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000060d8+4*2))=0x02020015;
*((unsigned int *)((unsigned long)context_ptr+0x000060d8+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x000060e8))=0x1cfba434;
*((unsigned int *)((unsigned long)context_ptr+0x000060e8+4*1))=0xcb609db0;
*((unsigned int *)((unsigned long)context_ptr+0x000060e8+4*2))=0x7bd1e402;
*((unsigned int *)((unsigned long)context_ptr+0x000060e8+4*3))=0x4095731b;
*((unsigned int *)((unsigned long)context_ptr+0x000060e8+4*4))=0x8fecc67c;
*((unsigned int *)((unsigned long)context_ptr+0x000060e8+4*5))=0x000000d3;
*((unsigned int *)((unsigned long)context_ptr+0x000031e0))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x000031e0+4*1))=0x000062e8;
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
*((unsigned int *)((unsigned long)context_ptr+0x000001e0+4*1))=0x000060e8;
*((unsigned int *)((unsigned long)context_ptr+0x000001e0+4*2))=0x000060d8;
*((unsigned int *)((unsigned long)context_ptr+0x000001e0+4*3))=0x02220015;
*((unsigned int *)((unsigned long)context_ptr+0x000001e0+4*4))=0x0ebba80c;
*((unsigned int *)((unsigned long)context_ptr+0x000001e0+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000002a&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006120,"\x95\xf7\xd1\xfa\x6e\xe5\x98\x28\xa5\x1c\x75\xa7\x47\x3d\x1d\xef",16))
printf("strip: 95f7d1fa6ee59828, Pass\n");
else
printf("strip: 95f7d1fa6ee59828, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006100))=0x006a0802;
*((unsigned int *)((unsigned long)context_ptr+0x00006100+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006100+4*2))=0x02020016;
*((unsigned int *)((unsigned long)context_ptr+0x00006100+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x00006110))=0x7dc18edc;
*((unsigned int *)((unsigned long)context_ptr+0x00006110+4*1))=0xdf8feeb0;
*((unsigned int *)((unsigned long)context_ptr+0x00006110+4*2))=0x3a011857;
*((unsigned int *)((unsigned long)context_ptr+0x00006110+4*3))=0x7e394fd6;
*((unsigned int *)((unsigned long)context_ptr+0x00006110+4*4))=0x135782f2;
*((unsigned int *)((unsigned long)context_ptr+0x00006110+4*5))=0x00003992;
*((unsigned int *)((unsigned long)context_ptr+0x000031f8))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x000031f8+4*1))=0x000062f8;
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
*((unsigned int *)((unsigned long)context_ptr+0x000001f8+4*1))=0x00006110;
*((unsigned int *)((unsigned long)context_ptr+0x000001f8+4*2))=0x00006100;
*((unsigned int *)((unsigned long)context_ptr+0x000001f8+4*3))=0x02220016;
*((unsigned int *)((unsigned long)context_ptr+0x000001f8+4*4))=0x0c2185e5;
*((unsigned int *)((unsigned long)context_ptr+0x000001f8+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000030&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006148,"\xaf\x71\xc0\x3b\xb8\xdb\x59\xa0\xf2\x4b\x16\x19\x50\x28\x74\xe1",16))
printf("strip: af71c03bb8db59a0, Pass\n");
else
printf("strip: af71c03bb8db59a0, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006128))=0x006a0802;
*((unsigned int *)((unsigned long)context_ptr+0x00006128+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006128+4*2))=0x02020017;
*((unsigned int *)((unsigned long)context_ptr+0x00006128+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x00006138))=0x1c533317;
*((unsigned int *)((unsigned long)context_ptr+0x00006138+4*1))=0x0b3b5dcc;
*((unsigned int *)((unsigned long)context_ptr+0x00006138+4*2))=0x9a1d0161;
*((unsigned int *)((unsigned long)context_ptr+0x00006138+4*3))=0x32bd33ef;
*((unsigned int *)((unsigned long)context_ptr+0x00006138+4*4))=0x11d8e500;
*((unsigned int *)((unsigned long)context_ptr+0x00006138+4*5))=0x00ed3b2d;
*((unsigned int *)((unsigned long)context_ptr+0x00003210))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003210+4*1))=0x00006308;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000210+4*1))=0x00006138;
*((unsigned int *)((unsigned long)context_ptr+0x00000210+4*2))=0x00006128;
*((unsigned int *)((unsigned long)context_ptr+0x00000210+4*3))=0x02220017;
*((unsigned int *)((unsigned long)context_ptr+0x00000210+4*4))=0x06f9179b;
*((unsigned int *)((unsigned long)context_ptr+0x00000210+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000036&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006174,"\xc1\x1a\xb0\xfd\x0a\xe5\x76\x24\xda\xad\xcb\x6f\x5f\xf0\x23\x9f",16))
printf("strip: c11ab0fd0ae57624, Pass\n");
else
printf("strip: c11ab0fd0ae57624, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006150))=0x006a0802;
*((unsigned int *)((unsigned long)context_ptr+0x00006150+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006150+4*2))=0x02020018;
*((unsigned int *)((unsigned long)context_ptr+0x00006150+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x00006160))=0x85f8ed99;
*((unsigned int *)((unsigned long)context_ptr+0x00006160+4*1))=0xac844c16;
*((unsigned int *)((unsigned long)context_ptr+0x00006160+4*2))=0xde0927f2;
*((unsigned int *)((unsigned long)context_ptr+0x00006160+4*3))=0xad77c4ce;
*((unsigned int *)((unsigned long)context_ptr+0x00006160+4*4))=0xc9643169;
*((unsigned int *)((unsigned long)context_ptr+0x00006160+4*5))=0xaee3f6cd;
*((unsigned int *)((unsigned long)context_ptr+0x00003228))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003228+4*1))=0x00006318;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000228+4*1))=0x00006160;
*((unsigned int *)((unsigned long)context_ptr+0x00000228+4*2))=0x00006150;
*((unsigned int *)((unsigned long)context_ptr+0x00000228+4*3))=0x02220018;
*((unsigned int *)((unsigned long)context_ptr+0x00000228+4*4))=0x02ee66e2;
*((unsigned int *)((unsigned long)context_ptr+0x00000228+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000003c&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000061a0,"\x3b\xbc\x77\xb2\x64\x65\x43\x51\x22\x26\xd7\xb2\xcb\x4a\x47\x64",16))
printf("strip: 3bbc77b264654351, Pass\n");
else
printf("strip: 3bbc77b264654351, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006178))=0x006a0802;
*((unsigned int *)((unsigned long)context_ptr+0x00006178+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006178+4*2))=0x02020019;
*((unsigned int *)((unsigned long)context_ptr+0x00006178+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x00006188))=0x22fe0135;
*((unsigned int *)((unsigned long)context_ptr+0x00006188+4*1))=0x89617da4;
*((unsigned int *)((unsigned long)context_ptr+0x00006188+4*2))=0x037ef814;
*((unsigned int *)((unsigned long)context_ptr+0x00006188+4*3))=0xbe4fc16b;
*((unsigned int *)((unsigned long)context_ptr+0x00006188+4*4))=0x07f73dc4;
*((unsigned int *)((unsigned long)context_ptr+0x00006188+4*5))=0x422783dd;
*((unsigned int *)((unsigned long)context_ptr+0x00006188+4*6))=0x00000097;
*((unsigned int *)((unsigned long)context_ptr+0x00003240))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003240+4*1))=0x00006328;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000240+4*1))=0x00006188;
*((unsigned int *)((unsigned long)context_ptr+0x00000240+4*2))=0x00006178;
*((unsigned int *)((unsigned long)context_ptr+0x00000240+4*3))=0x02220019;
*((unsigned int *)((unsigned long)context_ptr+0x00000240+4*4))=0x03833054;
*((unsigned int *)((unsigned long)context_ptr+0x00000240+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000042&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000061cc,"\x56\xbd\xa2\x4b\x62\xd5\x4c\x09\x0b\x92\x3d\x58\x3f\x09\xf1\xc1",16))
printf("strip: 56bda24b62d54c09, Pass\n");
else
printf("strip: 56bda24b62d54c09, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000061a4))=0x006a0802;
*((unsigned int *)((unsigned long)context_ptr+0x000061a4+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000061a4+4*2))=0x0202001a;
*((unsigned int *)((unsigned long)context_ptr+0x000061a4+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x000061b4))=0xf6b1feb5;
*((unsigned int *)((unsigned long)context_ptr+0x000061b4+4*1))=0x59be9b66;
*((unsigned int *)((unsigned long)context_ptr+0x000061b4+4*2))=0xff59f944;
*((unsigned int *)((unsigned long)context_ptr+0x000061b4+4*3))=0xfbd437da;
*((unsigned int *)((unsigned long)context_ptr+0x000061b4+4*4))=0x15c5aa46;
*((unsigned int *)((unsigned long)context_ptr+0x000061b4+4*5))=0xf3b44ed1;
*((unsigned int *)((unsigned long)context_ptr+0x000061b4+4*6))=0x00009c08;
*((unsigned int *)((unsigned long)context_ptr+0x00003258))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003258+4*1))=0x00006338;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000258+4*1))=0x000061b4;
*((unsigned int *)((unsigned long)context_ptr+0x00000258+4*2))=0x000061a4;
*((unsigned int *)((unsigned long)context_ptr+0x00000258+4*3))=0x0222001a;
*((unsigned int *)((unsigned long)context_ptr+0x00000258+4*4))=0x0b63c1db;
*((unsigned int *)((unsigned long)context_ptr+0x00000258+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000048&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000061f8,"\x79\xc6\xaf\x20\x54\xc6\x77\x94\xc5\x3b\x5f\x90\x76\x5e\xbb\x86",16))
printf("strip: 79c6af2054c67794, Pass\n");
else
printf("strip: 79c6af2054c67794, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000061d0))=0x006a0802;
*((unsigned int *)((unsigned long)context_ptr+0x000061d0+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000061d0+4*2))=0x0202001b;
*((unsigned int *)((unsigned long)context_ptr+0x000061d0+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x000061e0))=0x0eef7867;
*((unsigned int *)((unsigned long)context_ptr+0x000061e0+4*1))=0x3f5bdab5;
*((unsigned int *)((unsigned long)context_ptr+0x000061e0+4*2))=0x8d254d38;
*((unsigned int *)((unsigned long)context_ptr+0x000061e0+4*3))=0xd23b0640;
*((unsigned int *)((unsigned long)context_ptr+0x000061e0+4*4))=0x3ef1e26a;
*((unsigned int *)((unsigned long)context_ptr+0x000061e0+4*5))=0x2b94e18f;
*((unsigned int *)((unsigned long)context_ptr+0x000061e0+4*6))=0x004cfc3f;
*((unsigned int *)((unsigned long)context_ptr+0x00003270))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003270+4*1))=0x00006348;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000270+4*1))=0x000061e0;
*((unsigned int *)((unsigned long)context_ptr+0x00000270+4*2))=0x000061d0;
*((unsigned int *)((unsigned long)context_ptr+0x00000270+4*3))=0x0222001b;
*((unsigned int *)((unsigned long)context_ptr+0x00000270+4*4))=0x0bdf2b59;
*((unsigned int *)((unsigned long)context_ptr+0x00000270+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000004e&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006228,"\x5d\xfd\x05\x9c\x0e\xf2\xb5\xd5\x5a\x12\x93\x50\x5d\xe8\xbd\x53",16))
printf("strip: 5dfd059c0ef2b5d5, Pass\n");
else
printf("strip: 5dfd059c0ef2b5d5, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000061fc))=0x006a0802;
*((unsigned int *)((unsigned long)context_ptr+0x000061fc+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000061fc+4*2))=0x0202001c;
*((unsigned int *)((unsigned long)context_ptr+0x000061fc+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x0000620c))=0xa359e9cf;
*((unsigned int *)((unsigned long)context_ptr+0x0000620c+4*1))=0x80b29461;
*((unsigned int *)((unsigned long)context_ptr+0x0000620c+4*2))=0x30d7c1ac;
*((unsigned int *)((unsigned long)context_ptr+0x0000620c+4*3))=0xce828337;
*((unsigned int *)((unsigned long)context_ptr+0x0000620c+4*4))=0x81c7e684;
*((unsigned int *)((unsigned long)context_ptr+0x0000620c+4*5))=0x6e5779d3;
*((unsigned int *)((unsigned long)context_ptr+0x0000620c+4*6))=0xba0da674;
*((unsigned int *)((unsigned long)context_ptr+0x00003288))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003288+4*1))=0x00006228;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000288+4*1))=0x0000620c;
*((unsigned int *)((unsigned long)context_ptr+0x00000288+4*2))=0x000061fc;
*((unsigned int *)((unsigned long)context_ptr+0x00000288+4*3))=0x0222001c;
*((unsigned int *)((unsigned long)context_ptr+0x00000288+4*4))=0x0119b0f9;
*((unsigned int *)((unsigned long)context_ptr+0x00000288+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000054&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006258,"\x6b\x5e\x28\x17\x69\xab\x5c\x07\x16\x1c\x0e\xdf\x2f\x32\xb5\x28",16))
printf("strip: 6b5e281769ab5c07, Pass\n");
else
printf("strip: 6b5e281769ab5c07, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006238))=0x006a0802;
*((unsigned int *)((unsigned long)context_ptr+0x00006238+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006238+4*2))=0x0202001d;
*((unsigned int *)((unsigned long)context_ptr+0x00006238+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x00006248))=0x46a8fa23;
*((unsigned int *)((unsigned long)context_ptr+0x00006248+4*1))=0xe5549bfa;
*((unsigned int *)((unsigned long)context_ptr+0x00006248+4*2))=0x1b28cd13;
*((unsigned int *)((unsigned long)context_ptr+0x00006248+4*3))=0x6b9bb642;
*((unsigned int *)((unsigned long)context_ptr+0x00006248+4*4))=0xafc4ec28;
*((unsigned int *)((unsigned long)context_ptr+0x00006248+4*5))=0xc51cc6d0;
*((unsigned int *)((unsigned long)context_ptr+0x00006248+4*6))=0xaf7bbfd6;
*((unsigned int *)((unsigned long)context_ptr+0x00006248+4*7))=0x00000019;
*((unsigned int *)((unsigned long)context_ptr+0x000032a0))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x000032a0+4*1))=0x00006358;
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
*((unsigned int *)((unsigned long)context_ptr+0x000002a0+4*1))=0x00006248;
*((unsigned int *)((unsigned long)context_ptr+0x000002a0+4*2))=0x00006238;
*((unsigned int *)((unsigned long)context_ptr+0x000002a0+4*3))=0x0222001d;
*((unsigned int *)((unsigned long)context_ptr+0x000002a0+4*4))=0x0c8fe0b1;
*((unsigned int *)((unsigned long)context_ptr+0x000002a0+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000005a&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006288,"\x0d\x2f\xee\xb1\xeb\x27\x02\x99\x22\xa4\xce\x4d\x17\xa9\x5f\x61",16))
printf("strip: 0d2feeb1eb270299, Pass\n");
else
printf("strip: 0d2feeb1eb270299, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006268))=0x006a0802;
*((unsigned int *)((unsigned long)context_ptr+0x00006268+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006268+4*2))=0x0202001e;
*((unsigned int *)((unsigned long)context_ptr+0x00006268+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x00006278))=0x10942552;
*((unsigned int *)((unsigned long)context_ptr+0x00006278+4*1))=0x7c54405f;
*((unsigned int *)((unsigned long)context_ptr+0x00006278+4*2))=0x62501589;
*((unsigned int *)((unsigned long)context_ptr+0x00006278+4*3))=0x126d7a67;
*((unsigned int *)((unsigned long)context_ptr+0x00006278+4*4))=0x82d4a438;
*((unsigned int *)((unsigned long)context_ptr+0x00006278+4*5))=0x62271225;
*((unsigned int *)((unsigned long)context_ptr+0x00006278+4*6))=0x9086aa90;
*((unsigned int *)((unsigned long)context_ptr+0x00006278+4*7))=0x0000aa5a;
*((unsigned int *)((unsigned long)context_ptr+0x000032b8))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x000032b8+4*1))=0x00006368;
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
*((unsigned int *)((unsigned long)context_ptr+0x000002b8+4*1))=0x00006278;
*((unsigned int *)((unsigned long)context_ptr+0x000002b8+4*2))=0x00006268;
*((unsigned int *)((unsigned long)context_ptr+0x000002b8+4*3))=0x0222001e;
*((unsigned int *)((unsigned long)context_ptr+0x000002b8+4*4))=0x0d09e1a9;
*((unsigned int *)((unsigned long)context_ptr+0x000002b8+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000060&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006298,"\xaf\x39\xfd\x1b\x9d\x11\xf9\xc8\xfd\xf1\x5a\x97\x8f\xff\x9c\xbb",16))
printf("strip: af39fd1b9d11f9c8, Pass\n");
else
printf("strip: af39fd1b9d11f9c8, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006038))=0x006a0802;
*((unsigned int *)((unsigned long)context_ptr+0x00006038+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006038+4*2))=0x0202001f;
*((unsigned int *)((unsigned long)context_ptr+0x00006038+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x00006378))=0x364b5e64;
*((unsigned int *)((unsigned long)context_ptr+0x00006378+4*1))=0xe2dd89f6;
*((unsigned int *)((unsigned long)context_ptr+0x00006378+4*2))=0xa2563cf1;
*((unsigned int *)((unsigned long)context_ptr+0x00006378+4*3))=0x8cc22452;
*((unsigned int *)((unsigned long)context_ptr+0x00006378+4*4))=0xec1db589;
*((unsigned int *)((unsigned long)context_ptr+0x00006378+4*5))=0x9a99b17a;
*((unsigned int *)((unsigned long)context_ptr+0x00006378+4*6))=0x357f16b5;
*((unsigned int *)((unsigned long)context_ptr+0x00006378+4*7))=0x005a8363;
*((unsigned int *)((unsigned long)context_ptr+0x000032d0))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x000032d0+4*1))=0x00006298;
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
*((unsigned int *)((unsigned long)context_ptr+0x000002d0+4*1))=0x00006378;
*((unsigned int *)((unsigned long)context_ptr+0x000002d0+4*2))=0x00006038;
*((unsigned int *)((unsigned long)context_ptr+0x000002d0+4*3))=0x0222001f;
*((unsigned int *)((unsigned long)context_ptr+0x000002d0+4*4))=0x00b177ee;
*((unsigned int *)((unsigned long)context_ptr+0x000002d0+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000066&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000062a8,"\x6f\xb9\x1d\x0b\x7c\x5d\xc8\x54\x5d\x99\x40\xc0\xf8\x4d\x92\x61",16))
printf("strip: 6fb91d0b7c5dc854, Pass\n");
else
printf("strip: 6fb91d0b7c5dc854, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006028))=0x006a0802;
*((unsigned int *)((unsigned long)context_ptr+0x00006028+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006028+4*2))=0x02020020;
*((unsigned int *)((unsigned long)context_ptr+0x00006028+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x00006398))=0x1445bc4d;
*((unsigned int *)((unsigned long)context_ptr+0x00006398+4*1))=0x2ef9a9e5;
*((unsigned int *)((unsigned long)context_ptr+0x00006398+4*2))=0x7a8904de;
*((unsigned int *)((unsigned long)context_ptr+0x00006398+4*3))=0xe545d020;
*((unsigned int *)((unsigned long)context_ptr+0x00006398+4*4))=0xcadddab3;
*((unsigned int *)((unsigned long)context_ptr+0x00006398+4*5))=0x352401bc;
*((unsigned int *)((unsigned long)context_ptr+0x00006398+4*6))=0x7c200093;
*((unsigned int *)((unsigned long)context_ptr+0x00006398+4*7))=0x2c38510a;
*((unsigned int *)((unsigned long)context_ptr+0x000032e8))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x000032e8+4*1))=0x000062a8;
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
*((unsigned int *)((unsigned long)context_ptr+0x000002e8+4*1))=0x00006398;
*((unsigned int *)((unsigned long)context_ptr+0x000002e8+4*2))=0x00006028;
*((unsigned int *)((unsigned long)context_ptr+0x000002e8+4*3))=0x02220020;
*((unsigned int *)((unsigned long)context_ptr+0x000002e8+4*4))=0x03b3fd37;
*((unsigned int *)((unsigned long)context_ptr+0x000002e8+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000006c&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000062b8,"\x18\x81\x6b\xa0\x13\x78\xca\x50\x0c\x8b\x37\x66\x81\xfd\x99\x3c",16))
printf("strip: 18816ba01378ca50, Pass\n");
else
printf("strip: 18816ba01378ca50, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000062b8))=0x006a0802;
*((unsigned int *)((unsigned long)context_ptr+0x000062b8+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000062b8+4*2))=0x02020021;
*((unsigned int *)((unsigned long)context_ptr+0x000062b8+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x00006048))=0xa3933121;
*((unsigned int *)((unsigned long)context_ptr+0x00006048+4*1))=0x43a4656e;
*((unsigned int *)((unsigned long)context_ptr+0x00006048+4*2))=0x079aa3cc;
*((unsigned int *)((unsigned long)context_ptr+0x00006048+4*3))=0xa434c458;
*((unsigned int *)((unsigned long)context_ptr+0x00006048+4*4))=0x368470f9;
*((unsigned int *)((unsigned long)context_ptr+0x00006048+4*5))=0x9a783c01;
*((unsigned int *)((unsigned long)context_ptr+0x00006048+4*6))=0xb8544ad5;
*((unsigned int *)((unsigned long)context_ptr+0x00006048+4*7))=0x16e0b6aa;
*((unsigned int *)((unsigned long)context_ptr+0x00006048+4*8))=0x0000001f;
*((unsigned int *)((unsigned long)context_ptr+0x00003300))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003300+4*1))=0x0000606c;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000300+4*1))=0x00006048;
*((unsigned int *)((unsigned long)context_ptr+0x00000300+4*2))=0x000062b8;
*((unsigned int *)((unsigned long)context_ptr+0x00000300+4*3))=0x02220021;
*((unsigned int *)((unsigned long)context_ptr+0x00000300+4*4))=0x0a7713b1;
*((unsigned int *)((unsigned long)context_ptr+0x00000300+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000072&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000062c8,"\xfc\x6c\x15\xcc\x73\x13\x7f\x68\xb4\x4f\xf1\x9a\x8b\x7e\x90\xdf",16))
printf("strip: fc6c15cc73137f68, Pass\n");
else
printf("strip: fc6c15cc73137f68, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000062c8))=0x006a0802;
*((unsigned int *)((unsigned long)context_ptr+0x000062c8+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000062c8+4*2))=0x02020022;
*((unsigned int *)((unsigned long)context_ptr+0x000062c8+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x0000607c))=0x03a0a6f4;
*((unsigned int *)((unsigned long)context_ptr+0x0000607c+4*1))=0x24c49924;
*((unsigned int *)((unsigned long)context_ptr+0x0000607c+4*2))=0xd2c327a3;
*((unsigned int *)((unsigned long)context_ptr+0x0000607c+4*3))=0x4547119e;
*((unsigned int *)((unsigned long)context_ptr+0x0000607c+4*4))=0xfd94c777;
*((unsigned int *)((unsigned long)context_ptr+0x0000607c+4*5))=0x0ffa24b5;
*((unsigned int *)((unsigned long)context_ptr+0x0000607c+4*6))=0x0563a355;
*((unsigned int *)((unsigned long)context_ptr+0x0000607c+4*7))=0x97c63d4b;
*((unsigned int *)((unsigned long)context_ptr+0x0000607c+4*8))=0x0000df24;
*((unsigned int *)((unsigned long)context_ptr+0x00003318))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003318+4*1))=0x000060a0;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000318+4*2))=0x000062c8;
*((unsigned int *)((unsigned long)context_ptr+0x00000318+4*3))=0x02220022;
*((unsigned int *)((unsigned long)context_ptr+0x00000318+4*4))=0x0dfeddf5;
*((unsigned int *)((unsigned long)context_ptr+0x00000318+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000078&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000062d8,"\x29\x16\xf1\x33\x93\x40\xa9\x00\x7a\x12\x50\x5e\x57\xb9\xc0\xb3",16))
printf("strip: 2916f1339340a900, Pass\n");
else
printf("strip: 2916f1339340a900, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000062d8))=0x006a0802;
*((unsigned int *)((unsigned long)context_ptr+0x000062d8+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000062d8+4*2))=0x02020023;
*((unsigned int *)((unsigned long)context_ptr+0x000062d8+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x000060b0))=0x18738efc;
*((unsigned int *)((unsigned long)context_ptr+0x000060b0+4*1))=0xa7b386f3;
*((unsigned int *)((unsigned long)context_ptr+0x000060b0+4*2))=0x0e18a33c;
*((unsigned int *)((unsigned long)context_ptr+0x000060b0+4*3))=0x864d99d7;
*((unsigned int *)((unsigned long)context_ptr+0x000060b0+4*4))=0x2400ad8e;
*((unsigned int *)((unsigned long)context_ptr+0x000060b0+4*5))=0x3273c017;
*((unsigned int *)((unsigned long)context_ptr+0x000060b0+4*6))=0x8b76ab5f;
*((unsigned int *)((unsigned long)context_ptr+0x000060b0+4*7))=0x1b1a66f0;
*((unsigned int *)((unsigned long)context_ptr+0x000060b0+4*8))=0x001d4fb9;
*((unsigned int *)((unsigned long)context_ptr+0x00003330))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003330+4*1))=0x000063b8;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000330+4*2))=0x000062d8;
*((unsigned int *)((unsigned long)context_ptr+0x00000330+4*3))=0x02220023;
*((unsigned int *)((unsigned long)context_ptr+0x00000330+4*4))=0x01a340ec;
*((unsigned int *)((unsigned long)context_ptr+0x00000330+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000007e&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000062e8,"\x5a\xf5\x2e\xae\x19\xf0\xb2\x03\x7d\xda\x87\xdb\x8f\x4d\xaa\x52",16))
printf("strip: 5af52eae19f0b203, Pass\n");
else
printf("strip: 5af52eae19f0b203, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000062e8))=0x006a0802;
*((unsigned int *)((unsigned long)context_ptr+0x000062e8+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000062e8+4*2))=0x02020024;
*((unsigned int *)((unsigned long)context_ptr+0x000062e8+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x000060d4))=0xb8a8fd11;
*((unsigned int *)((unsigned long)context_ptr+0x000060d4+4*1))=0x4767f0b1;
*((unsigned int *)((unsigned long)context_ptr+0x000060d4+4*2))=0xbe7a0514;
*((unsigned int *)((unsigned long)context_ptr+0x000060d4+4*3))=0xd49d00bd;
*((unsigned int *)((unsigned long)context_ptr+0x000060d4+4*4))=0xb46bc5dd;
*((unsigned int *)((unsigned long)context_ptr+0x000060d4+4*5))=0x580910b3;
*((unsigned int *)((unsigned long)context_ptr+0x000060d4+4*6))=0xc2a561a4;
*((unsigned int *)((unsigned long)context_ptr+0x000060d4+4*7))=0x8df848c5;
*((unsigned int *)((unsigned long)context_ptr+0x000060d4+4*8))=0x27aca2a0;
*((unsigned int *)((unsigned long)context_ptr+0x00003348))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003348+4*1))=0x000063c8;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000348+4*1))=0x000060d4;
*((unsigned int *)((unsigned long)context_ptr+0x00000348+4*2))=0x000062e8;
*((unsigned int *)((unsigned long)context_ptr+0x00000348+4*3))=0x02220024;
*((unsigned int *)((unsigned long)context_ptr+0x00000348+4*4))=0x0f7fc0bb;
*((unsigned int *)((unsigned long)context_ptr+0x00000348+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000084&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000062f8,"\xbe\xec\xdc\x76\xed\xf0\xad\xb2\x15\xd0\x5f\x3e\x15\xcf\xe7\xc3",16))
printf("strip: beecdc76edf0adb2, Pass\n");
else
printf("strip: beecdc76edf0adb2, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000062f8))=0x006a0802;
*((unsigned int *)((unsigned long)context_ptr+0x000062f8+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000062f8+4*2))=0x02020025;
*((unsigned int *)((unsigned long)context_ptr+0x000062f8+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x000060f8))=0xdf0b080e;
*((unsigned int *)((unsigned long)context_ptr+0x000060f8+4*1))=0x231478de;
*((unsigned int *)((unsigned long)context_ptr+0x000060f8+4*2))=0x13cb8ff2;
*((unsigned int *)((unsigned long)context_ptr+0x000060f8+4*3))=0xd21dc610;
*((unsigned int *)((unsigned long)context_ptr+0x000060f8+4*4))=0xb71d6eef;
*((unsigned int *)((unsigned long)context_ptr+0x000060f8+4*5))=0x8ae38072;
*((unsigned int *)((unsigned long)context_ptr+0x000060f8+4*6))=0x82d95f23;
*((unsigned int *)((unsigned long)context_ptr+0x000060f8+4*7))=0xe1088114;
*((unsigned int *)((unsigned long)context_ptr+0x000060f8+4*8))=0xe5feba3f;
*((unsigned int *)((unsigned long)context_ptr+0x000060f8+4*9))=0x00000087;
*((unsigned int *)((unsigned long)context_ptr+0x00003360))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003360+4*1))=0x000063d8;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000360+4*1))=0x000060f8;
*((unsigned int *)((unsigned long)context_ptr+0x00000360+4*2))=0x000062f8;
*((unsigned int *)((unsigned long)context_ptr+0x00000360+4*3))=0x02220025;
*((unsigned int *)((unsigned long)context_ptr+0x00000360+4*4))=0x08beeb82;
*((unsigned int *)((unsigned long)context_ptr+0x00000360+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000008a&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006308,"\x52\x49\x5c\x79\x15\x4c\xb6\x25\xea\x32\x5d\x47\x73\x6e\x37\xd2",16))
printf("strip: 52495c79154cb625, Pass\n");
else
printf("strip: 52495c79154cb625, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006308))=0x006a0802;
*((unsigned int *)((unsigned long)context_ptr+0x00006308+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006308+4*2))=0x02020026;
*((unsigned int *)((unsigned long)context_ptr+0x00006308+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x00006120))=0x91332ba2;
*((unsigned int *)((unsigned long)context_ptr+0x00006120+4*1))=0xadd06897;
*((unsigned int *)((unsigned long)context_ptr+0x00006120+4*2))=0x549b0742;
*((unsigned int *)((unsigned long)context_ptr+0x00006120+4*3))=0x328c3be3;
*((unsigned int *)((unsigned long)context_ptr+0x00006120+4*4))=0xe4c0a4f7;
*((unsigned int *)((unsigned long)context_ptr+0x00006120+4*5))=0x9e738b74;
*((unsigned int *)((unsigned long)context_ptr+0x00006120+4*6))=0xc55dd255;
*((unsigned int *)((unsigned long)context_ptr+0x00006120+4*7))=0xe67a5d04;
*((unsigned int *)((unsigned long)context_ptr+0x00006120+4*8))=0xe6a2bbb8;
*((unsigned int *)((unsigned long)context_ptr+0x00006120+4*9))=0x0000a1b9;
*((unsigned int *)((unsigned long)context_ptr+0x00003378))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003378+4*1))=0x000063e8;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000378+4*1))=0x00006120;
*((unsigned int *)((unsigned long)context_ptr+0x00000378+4*2))=0x00006308;
*((unsigned int *)((unsigned long)context_ptr+0x00000378+4*3))=0x02220026;
*((unsigned int *)((unsigned long)context_ptr+0x00000378+4*4))=0x003c92eb;
*((unsigned int *)((unsigned long)context_ptr+0x00000378+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000090&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006318,"\xab\x99\xf0\xf7\x1e\x3e\x2c\xa2\x2d\xc5\xf7\x26\x71\x1e\xe0\x2c",16))
printf("strip: ab99f0f71e3e2ca2, Pass\n");
else
printf("strip: ab99f0f71e3e2ca2, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006318))=0x006a0802;
*((unsigned int *)((unsigned long)context_ptr+0x00006318+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006318+4*2))=0x02020027;
*((unsigned int *)((unsigned long)context_ptr+0x00006318+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x00006148))=0x27b17050;
*((unsigned int *)((unsigned long)context_ptr+0x00006148+4*1))=0xb57dd8c8;
*((unsigned int *)((unsigned long)context_ptr+0x00006148+4*2))=0x5cc6fdb9;
*((unsigned int *)((unsigned long)context_ptr+0x00006148+4*3))=0xe5886482;
*((unsigned int *)((unsigned long)context_ptr+0x00006148+4*4))=0x2581e418;
*((unsigned int *)((unsigned long)context_ptr+0x00006148+4*5))=0x780631ef;
*((unsigned int *)((unsigned long)context_ptr+0x00006148+4*6))=0x90a00c92;
*((unsigned int *)((unsigned long)context_ptr+0x00006148+4*7))=0x215b1490;
*((unsigned int *)((unsigned long)context_ptr+0x00006148+4*8))=0xe1545e77;
*((unsigned int *)((unsigned long)context_ptr+0x00006148+4*9))=0x00a81c9f;
*((unsigned int *)((unsigned long)context_ptr+0x00003390))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003390+4*1))=0x000063f8;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000390+4*1))=0x00006148;
*((unsigned int *)((unsigned long)context_ptr+0x00000390+4*2))=0x00006318;
*((unsigned int *)((unsigned long)context_ptr+0x00000390+4*3))=0x02220027;
*((unsigned int *)((unsigned long)context_ptr+0x00000390+4*4))=0x0c541015;
*((unsigned int *)((unsigned long)context_ptr+0x00000390+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000096&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006328,"\x1c\x30\x7a\xf4\x3e\xb1\x30\x70\xc8\x63\x0f\x1f\xa5\xb6\xb6\xbe",16))
printf("strip: 1c307af43eb13070, Pass\n");
else
printf("strip: 1c307af43eb13070, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006328))=0x006a0802;
*((unsigned int *)((unsigned long)context_ptr+0x00006328+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006328+4*2))=0x02020028;
*((unsigned int *)((unsigned long)context_ptr+0x00006328+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x00006170))=0xb387e6d3;
*((unsigned int *)((unsigned long)context_ptr+0x00006170+4*1))=0x67a5a0c3;
*((unsigned int *)((unsigned long)context_ptr+0x00006170+4*2))=0xb9292de4;
*((unsigned int *)((unsigned long)context_ptr+0x00006170+4*3))=0x5be68536;
*((unsigned int *)((unsigned long)context_ptr+0x00006170+4*4))=0x17a8debc;
*((unsigned int *)((unsigned long)context_ptr+0x00006170+4*5))=0x75ffcc84;
*((unsigned int *)((unsigned long)context_ptr+0x00006170+4*6))=0xed7f590e;
*((unsigned int *)((unsigned long)context_ptr+0x00006170+4*7))=0x1970ea10;
*((unsigned int *)((unsigned long)context_ptr+0x00006170+4*8))=0x3c221ec0;
*((unsigned int *)((unsigned long)context_ptr+0x00006170+4*9))=0x96dca98c;
*((unsigned int *)((unsigned long)context_ptr+0x000033a8))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x000033a8+4*1))=0x00006408;
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
*((unsigned int *)((unsigned long)context_ptr+0x000003a8+4*1))=0x00006170;
*((unsigned int *)((unsigned long)context_ptr+0x000003a8+4*2))=0x00006328;
*((unsigned int *)((unsigned long)context_ptr+0x000003a8+4*3))=0x02220028;
*((unsigned int *)((unsigned long)context_ptr+0x000003a8+4*4))=0x0811a1a7;
*((unsigned int *)((unsigned long)context_ptr+0x000003a8+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000009c&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006338,"\xc9\x15\xaa\x85\x66\x29\xd1\x2c\xa1\x71\xed\x86\xa4\xef\x64\xbe",16))
printf("strip: c915aa856629d12c, Pass\n");
else
printf("strip: c915aa856629d12c, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006338))=0x006a0802;
*((unsigned int *)((unsigned long)context_ptr+0x00006338+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006338+4*2))=0x02020029;
*((unsigned int *)((unsigned long)context_ptr+0x00006338+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x00006198))=0x668871de;
*((unsigned int *)((unsigned long)context_ptr+0x00006198+4*1))=0x47e56755;
*((unsigned int *)((unsigned long)context_ptr+0x00006198+4*2))=0x77e836b2;
*((unsigned int *)((unsigned long)context_ptr+0x00006198+4*3))=0xdbbd6d4c;
*((unsigned int *)((unsigned long)context_ptr+0x00006198+4*4))=0x7af721d0;
*((unsigned int *)((unsigned long)context_ptr+0x00006198+4*5))=0x31f02bf3;
*((unsigned int *)((unsigned long)context_ptr+0x00006198+4*6))=0x29d745de;
*((unsigned int *)((unsigned long)context_ptr+0x00006198+4*7))=0xef1fa9da;
*((unsigned int *)((unsigned long)context_ptr+0x00006198+4*8))=0x0dd72f6f;
*((unsigned int *)((unsigned long)context_ptr+0x00006198+4*9))=0xbf17bc09;
*((unsigned int *)((unsigned long)context_ptr+0x00006198+4*10))=0x00000018;
*((unsigned int *)((unsigned long)context_ptr+0x000033c0))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x000033c0+4*1))=0x00006418;
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
*((unsigned int *)((unsigned long)context_ptr+0x000003c0+4*1))=0x00006198;
*((unsigned int *)((unsigned long)context_ptr+0x000003c0+4*2))=0x00006338;
*((unsigned int *)((unsigned long)context_ptr+0x000003c0+4*3))=0x02220029;
*((unsigned int *)((unsigned long)context_ptr+0x000003c0+4*4))=0x0901d167;
*((unsigned int *)((unsigned long)context_ptr+0x000003c0+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000000a2&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006348,"\xdd\xab\xa3\x06\xe5\x34\xf7\x04\x80\x54\x49\xf0\xa3\xc3\xf4\x74",16))
printf("strip: ddaba306e534f704, Pass\n");
else
printf("strip: ddaba306e534f704, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006348))=0x006a0802;
*((unsigned int *)((unsigned long)context_ptr+0x00006348+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006348+4*2))=0x0202002a;
*((unsigned int *)((unsigned long)context_ptr+0x00006348+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x000061c4))=0xcef3d906;
*((unsigned int *)((unsigned long)context_ptr+0x000061c4+4*1))=0xddc16b28;
*((unsigned int *)((unsigned long)context_ptr+0x000061c4+4*2))=0x23a4ecde;
*((unsigned int *)((unsigned long)context_ptr+0x000061c4+4*3))=0xee21f56b;
*((unsigned int *)((unsigned long)context_ptr+0x000061c4+4*4))=0x17d0975c;
*((unsigned int *)((unsigned long)context_ptr+0x000061c4+4*5))=0xf8e77a1c;
*((unsigned int *)((unsigned long)context_ptr+0x000061c4+4*6))=0x60cb31a7;
*((unsigned int *)((unsigned long)context_ptr+0x000061c4+4*7))=0x84719743;
*((unsigned int *)((unsigned long)context_ptr+0x000061c4+4*8))=0x6edf09f8;
*((unsigned int *)((unsigned long)context_ptr+0x000061c4+4*9))=0x79bce0d8;
*((unsigned int *)((unsigned long)context_ptr+0x000061c4+4*10))=0x00009885;
*((unsigned int *)((unsigned long)context_ptr+0x000033d8))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x000033d8+4*1))=0x00006428;
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
*((unsigned int *)((unsigned long)context_ptr+0x000003d8+4*1))=0x000061c4;
*((unsigned int *)((unsigned long)context_ptr+0x000003d8+4*2))=0x00006348;
*((unsigned int *)((unsigned long)context_ptr+0x000003d8+4*3))=0x0222002a;
*((unsigned int *)((unsigned long)context_ptr+0x000003d8+4*4))=0x0dad107c;
*((unsigned int *)((unsigned long)context_ptr+0x000003d8+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000000a8&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006228,"\x7a\x3a\x00\xaa\x56\x3b\x10\x5b\xa5\xc4\x94\xc5\x5f\xab\xe6\x59",16))
printf("strip: 7a3a00aa563b105b, Pass\n");
else
printf("strip: 7a3a00aa563b105b, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000061f0))=0x006a0802;
*((unsigned int *)((unsigned long)context_ptr+0x000061f0+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000061f0+4*2))=0x0202002b;
*((unsigned int *)((unsigned long)context_ptr+0x000061f0+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x00006200))=0x6e3b02d1;
*((unsigned int *)((unsigned long)context_ptr+0x00006200+4*1))=0x922cd077;
*((unsigned int *)((unsigned long)context_ptr+0x00006200+4*2))=0x0b03a589;
*((unsigned int *)((unsigned long)context_ptr+0x00006200+4*3))=0xbb996417;
*((unsigned int *)((unsigned long)context_ptr+0x00006200+4*4))=0x64dd1ba6;
*((unsigned int *)((unsigned long)context_ptr+0x00006200+4*5))=0xab612bd0;
*((unsigned int *)((unsigned long)context_ptr+0x00006200+4*6))=0xcfec84a1;
*((unsigned int *)((unsigned long)context_ptr+0x00006200+4*7))=0x836aad98;
*((unsigned int *)((unsigned long)context_ptr+0x00006200+4*8))=0x7533d6a1;
*((unsigned int *)((unsigned long)context_ptr+0x00006200+4*9))=0x1e09322f;
*((unsigned int *)((unsigned long)context_ptr+0x00006200+4*10))=0x004e54c1;
*((unsigned int *)((unsigned long)context_ptr+0x000033f0))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x000033f0+4*1))=0x00006438;
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
*((unsigned int *)((unsigned long)context_ptr+0x000003f0+4*1))=0x00006200;
*((unsigned int *)((unsigned long)context_ptr+0x000003f0+4*2))=0x000061f0;
*((unsigned int *)((unsigned long)context_ptr+0x000003f0+4*3))=0x0222002b;
*((unsigned int *)((unsigned long)context_ptr+0x000003f0+4*4))=0x06a430fc;
*((unsigned int *)((unsigned long)context_ptr+0x000003f0+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000000ae&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006358,"\xc7\x1c\x2e\x44\x6c\xf2\xc7\x13\x3f\x1f\xab\x5c\xc4\xff\x4d\x1a",16))
printf("strip: c71c2e446cf2c713, Pass\n");
else
printf("strip: c71c2e446cf2c713, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006358))=0x006a0802;
*((unsigned int *)((unsigned long)context_ptr+0x00006358+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006358+4*2))=0x0202002c;
*((unsigned int *)((unsigned long)context_ptr+0x00006358+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x0000622c))=0x80f7154c;
*((unsigned int *)((unsigned long)context_ptr+0x0000622c+4*1))=0xcc2d8d6c;
*((unsigned int *)((unsigned long)context_ptr+0x0000622c+4*2))=0x4bbdd849;
*((unsigned int *)((unsigned long)context_ptr+0x0000622c+4*3))=0xd9f04b7c;
*((unsigned int *)((unsigned long)context_ptr+0x0000622c+4*4))=0xcc13b089;
*((unsigned int *)((unsigned long)context_ptr+0x0000622c+4*5))=0xe353445b;
*((unsigned int *)((unsigned long)context_ptr+0x0000622c+4*6))=0xa076fc1a;
*((unsigned int *)((unsigned long)context_ptr+0x0000622c+4*7))=0x66c41081;
*((unsigned int *)((unsigned long)context_ptr+0x0000622c+4*8))=0x244fd27b;
*((unsigned int *)((unsigned long)context_ptr+0x0000622c+4*9))=0x9710b00b;
*((unsigned int *)((unsigned long)context_ptr+0x0000622c+4*10))=0x4a641c11;
*((unsigned int *)((unsigned long)context_ptr+0x00003408))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003408+4*1))=0x00006258;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000408+4*1))=0x0000622c;
*((unsigned int *)((unsigned long)context_ptr+0x00000408+4*2))=0x00006358;
*((unsigned int *)((unsigned long)context_ptr+0x00000408+4*3))=0x0222002c;
*((unsigned int *)((unsigned long)context_ptr+0x00000408+4*4))=0x0f24bfd6;
*((unsigned int *)((unsigned long)context_ptr+0x00000408+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000000b4&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006368,"\x25\x76\xbe\x78\x9e\xe0\x71\x7a\x7a\x2d\x29\x18\x5d\x89\x6c\xdb",16))
printf("strip: 2576be789ee0717a, Pass\n");
else
printf("strip: 2576be789ee0717a, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006368))=0x006a0802;
*((unsigned int *)((unsigned long)context_ptr+0x00006368+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006368+4*2))=0x0202002d;
*((unsigned int *)((unsigned long)context_ptr+0x00006368+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x00006448))=0x24061eda;
*((unsigned int *)((unsigned long)context_ptr+0x00006448+4*1))=0x4ae90cd5;
*((unsigned int *)((unsigned long)context_ptr+0x00006448+4*2))=0x903ea732;
*((unsigned int *)((unsigned long)context_ptr+0x00006448+4*3))=0xa251aac3;
*((unsigned int *)((unsigned long)context_ptr+0x00006448+4*4))=0xa17505a0;
*((unsigned int *)((unsigned long)context_ptr+0x00006448+4*5))=0x02e92961;
*((unsigned int *)((unsigned long)context_ptr+0x00006448+4*6))=0xe9fd2add;
*((unsigned int *)((unsigned long)context_ptr+0x00006448+4*7))=0xddaac417;
*((unsigned int *)((unsigned long)context_ptr+0x00006448+4*8))=0xbcca4f7f;
*((unsigned int *)((unsigned long)context_ptr+0x00006448+4*9))=0x7fc4fc89;
*((unsigned int *)((unsigned long)context_ptr+0x00006448+4*10))=0x0cd781ed;
*((unsigned int *)((unsigned long)context_ptr+0x00006448+4*11))=0x00000021;
*((unsigned int *)((unsigned long)context_ptr+0x00003420))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003420+4*1))=0x00006268;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000420+4*1))=0x00006448;
*((unsigned int *)((unsigned long)context_ptr+0x00000420+4*2))=0x00006368;
*((unsigned int *)((unsigned long)context_ptr+0x00000420+4*3))=0x0222002d;
*((unsigned int *)((unsigned long)context_ptr+0x00000420+4*4))=0x023f33d4;
*((unsigned int *)((unsigned long)context_ptr+0x00000420+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000000ba&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006298,"\xed\x73\x13\x5d\xe4\x47\x20\x69\x17\x4c\x99\x16\xa6\xb3\xdb\x0e",16))
printf("strip: ed73135de4472069, Pass\n");
else
printf("strip: ed73135de4472069, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006038))=0x006a0802;
*((unsigned int *)((unsigned long)context_ptr+0x00006038+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006038+4*2))=0x0202002e;
*((unsigned int *)((unsigned long)context_ptr+0x00006038+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x00006278))=0x38bfaf9f;
*((unsigned int *)((unsigned long)context_ptr+0x00006278+4*1))=0x7977f72e;
*((unsigned int *)((unsigned long)context_ptr+0x00006278+4*2))=0x0d2caf15;
*((unsigned int *)((unsigned long)context_ptr+0x00006278+4*3))=0x0e55f740;
*((unsigned int *)((unsigned long)context_ptr+0x00006278+4*4))=0x79482cab;
*((unsigned int *)((unsigned long)context_ptr+0x00006278+4*5))=0xc2ec4d8a;
*((unsigned int *)((unsigned long)context_ptr+0x00006278+4*6))=0xd4d113a0;
*((unsigned int *)((unsigned long)context_ptr+0x00006278+4*7))=0xe62cd4ce;
*((unsigned int *)((unsigned long)context_ptr+0x00006278+4*8))=0x2800434b;
*((unsigned int *)((unsigned long)context_ptr+0x00006278+4*9))=0x0cdf3b58;
*((unsigned int *)((unsigned long)context_ptr+0x00006278+4*10))=0xd5dd6071;
*((unsigned int *)((unsigned long)context_ptr+0x00006278+4*11))=0x0000ad53;
*((unsigned int *)((unsigned long)context_ptr+0x00003438))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003438+4*1))=0x00006378;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000438+4*1))=0x00006278;
*((unsigned int *)((unsigned long)context_ptr+0x00000438+4*2))=0x00006038;
*((unsigned int *)((unsigned long)context_ptr+0x00000438+4*3))=0x0222002e;
*((unsigned int *)((unsigned long)context_ptr+0x00000438+4*4))=0x0b253a61;
*((unsigned int *)((unsigned long)context_ptr+0x00000438+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000000c0&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000062a8,"\xad\x6a\xff\xbd\x1e\xe5\x54\x8f\xe1\x21\xf3\x33\x80\xec\x3f\xa1",16))
printf("strip: ad6affbd1ee5548f, Pass\n");
else
printf("strip: ad6affbd1ee5548f, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000062a8))=0x006a0802;
*((unsigned int *)((unsigned long)context_ptr+0x000062a8+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000062a8+4*2))=0x0202002f;
*((unsigned int *)((unsigned long)context_ptr+0x000062a8+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x00006388))=0x998636cc;
*((unsigned int *)((unsigned long)context_ptr+0x00006388+4*1))=0x51ec81f0;
*((unsigned int *)((unsigned long)context_ptr+0x00006388+4*2))=0x2a18a095;
*((unsigned int *)((unsigned long)context_ptr+0x00006388+4*3))=0x6b2f4341;
*((unsigned int *)((unsigned long)context_ptr+0x00006388+4*4))=0x2ddb2618;
*((unsigned int *)((unsigned long)context_ptr+0x00006388+4*5))=0x44cb1472;
*((unsigned int *)((unsigned long)context_ptr+0x00006388+4*6))=0x3469d1a9;
*((unsigned int *)((unsigned long)context_ptr+0x00006388+4*7))=0xa8987528;
*((unsigned int *)((unsigned long)context_ptr+0x00006388+4*8))=0x22003e96;
*((unsigned int *)((unsigned long)context_ptr+0x00006388+4*9))=0xfa91f870;
*((unsigned int *)((unsigned long)context_ptr+0x00006388+4*10))=0xb04afed7;
*((unsigned int *)((unsigned long)context_ptr+0x00006388+4*11))=0x009dde6e;
*((unsigned int *)((unsigned long)context_ptr+0x00003450))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003450+4*1))=0x00006028;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000450+4*1))=0x00006388;
*((unsigned int *)((unsigned long)context_ptr+0x00000450+4*2))=0x000062a8;
*((unsigned int *)((unsigned long)context_ptr+0x00000450+4*3))=0x0222002f;
*((unsigned int *)((unsigned long)context_ptr+0x00000450+4*4))=0x0d756df5;
*((unsigned int *)((unsigned long)context_ptr+0x00000450+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000000c6&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x0000606c,"\x0b\xfc\x30\x44\xc2\x98\x05\x70\x2f\x65\xe7\x00\x37\x46\x03\xd9",16))
printf("strip: 0bfc3044c2980570, Pass\n");
else
printf("strip: 0bfc3044c2980570, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000062b8))=0x006a0802;
*((unsigned int *)((unsigned long)context_ptr+0x000062b8+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000062b8+4*2))=0x02020030;
*((unsigned int *)((unsigned long)context_ptr+0x000062b8+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x00006048))=0x97df5821;
*((unsigned int *)((unsigned long)context_ptr+0x00006048+4*1))=0x40ff1a28;
*((unsigned int *)((unsigned long)context_ptr+0x00006048+4*2))=0xf1472f49;
*((unsigned int *)((unsigned long)context_ptr+0x00006048+4*3))=0x9855695f;
*((unsigned int *)((unsigned long)context_ptr+0x00006048+4*4))=0x8e1b4286;
*((unsigned int *)((unsigned long)context_ptr+0x00006048+4*5))=0x6c570e8e;
*((unsigned int *)((unsigned long)context_ptr+0x00006048+4*6))=0xcdab517b;
*((unsigned int *)((unsigned long)context_ptr+0x00006048+4*7))=0x97aa6b1e;
*((unsigned int *)((unsigned long)context_ptr+0x00006048+4*8))=0xe38bdedf;
*((unsigned int *)((unsigned long)context_ptr+0x00006048+4*9))=0x620226ce;
*((unsigned int *)((unsigned long)context_ptr+0x00006048+4*10))=0x84cf075d;
*((unsigned int *)((unsigned long)context_ptr+0x00006048+4*11))=0x66ced5f9;
*((unsigned int *)((unsigned long)context_ptr+0x00003468))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003468+4*1))=0x00006478;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000468+4*1))=0x00006048;
*((unsigned int *)((unsigned long)context_ptr+0x00000468+4*2))=0x000062b8;
*((unsigned int *)((unsigned long)context_ptr+0x00000468+4*3))=0x02220030;
*((unsigned int *)((unsigned long)context_ptr+0x00000468+4*4))=0x01ae3b63;
*((unsigned int *)((unsigned long)context_ptr+0x00000468+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000000cc&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000060a0,"\x93\x17\x2c\xfc\xe5\x2d\xb5\x8d\x4b\x66\x20\xda\x78\xc8\x67\xfc",16))
printf("strip: 93172cfce52db58d, Pass\n");
else
printf("strip: 93172cfce52db58d, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000062c8))=0x006a0802;
*((unsigned int *)((unsigned long)context_ptr+0x000062c8+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000062c8+4*2))=0x02020031;
*((unsigned int *)((unsigned long)context_ptr+0x000062c8+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x00006078))=0x21636e67;
*((unsigned int *)((unsigned long)context_ptr+0x00006078+4*1))=0x9bcc7d98;
*((unsigned int *)((unsigned long)context_ptr+0x00006078+4*2))=0x4e46db58;
*((unsigned int *)((unsigned long)context_ptr+0x00006078+4*3))=0x3936fade;
*((unsigned int *)((unsigned long)context_ptr+0x00006078+4*4))=0x6dd00694;
*((unsigned int *)((unsigned long)context_ptr+0x00006078+4*5))=0x8ccb06bb;
*((unsigned int *)((unsigned long)context_ptr+0x00006078+4*6))=0x9f680c05;
*((unsigned int *)((unsigned long)context_ptr+0x00006078+4*7))=0x61e6a473;
*((unsigned int *)((unsigned long)context_ptr+0x00006078+4*8))=0x560bcb6b;
*((unsigned int *)((unsigned long)context_ptr+0x00006078+4*9))=0xa9aca70f;
*((unsigned int *)((unsigned long)context_ptr+0x00006078+4*10))=0xa103be9e;
*((unsigned int *)((unsigned long)context_ptr+0x00006078+4*11))=0x08c1d5a1;
*((unsigned int *)((unsigned long)context_ptr+0x00006078+4*12))=0x00000097;
*((unsigned int *)((unsigned long)context_ptr+0x00003480))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003480+4*1))=0x00006488;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000480+4*1))=0x00006078;
*((unsigned int *)((unsigned long)context_ptr+0x00000480+4*2))=0x000062c8;
*((unsigned int *)((unsigned long)context_ptr+0x00000480+4*3))=0x02220031;
*((unsigned int *)((unsigned long)context_ptr+0x00000480+4*4))=0x01bb9966;
*((unsigned int *)((unsigned long)context_ptr+0x00000480+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000000d2&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000063b8,"\x96\x40\x45\x4c\x01\xb7\x6e\x93\xcf\xeb\x5e\x1a\xb2\x24\xf7\x45",16))
printf("strip: 9640454c01b76e93, Pass\n");
else
printf("strip: 9640454c01b76e93, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000063b8))=0x006a0802;
*((unsigned int *)((unsigned long)context_ptr+0x000063b8+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000063b8+4*2))=0x02020032;
*((unsigned int *)((unsigned long)context_ptr+0x000063b8+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x00006498))=0xb86d556a;
*((unsigned int *)((unsigned long)context_ptr+0x00006498+4*1))=0x92a9ec0a;
*((unsigned int *)((unsigned long)context_ptr+0x00006498+4*2))=0x9d261603;
*((unsigned int *)((unsigned long)context_ptr+0x00006498+4*3))=0x55dc2a8f;
*((unsigned int *)((unsigned long)context_ptr+0x00006498+4*4))=0x7cc04a23;
*((unsigned int *)((unsigned long)context_ptr+0x00006498+4*5))=0x3f9e44a3;
*((unsigned int *)((unsigned long)context_ptr+0x00006498+4*6))=0x4d71b703;
*((unsigned int *)((unsigned long)context_ptr+0x00006498+4*7))=0xf8ce6186;
*((unsigned int *)((unsigned long)context_ptr+0x00006498+4*8))=0x02a709a6;
*((unsigned int *)((unsigned long)context_ptr+0x00006498+4*9))=0x06dd1766;
*((unsigned int *)((unsigned long)context_ptr+0x00006498+4*10))=0x428276ad;
*((unsigned int *)((unsigned long)context_ptr+0x00006498+4*11))=0x7d736e60;
*((unsigned int *)((unsigned long)context_ptr+0x00006498+4*12))=0x0000a1d5;
*((unsigned int *)((unsigned long)context_ptr+0x00003498))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003498+4*1))=0x000062d8;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000498+4*1))=0x00006498;
*((unsigned int *)((unsigned long)context_ptr+0x00000498+4*2))=0x000063b8;
*((unsigned int *)((unsigned long)context_ptr+0x00000498+4*3))=0x02220032;
*((unsigned int *)((unsigned long)context_ptr+0x00000498+4*4))=0x08609a63;
*((unsigned int *)((unsigned long)context_ptr+0x00000498+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000000d8&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000063c8,"\x3c\xb6\x0b\x30\xb6\xcf\x57\x33\x64\xf8\x60\xb3\x30\x71\xc1\xc0",16))
printf("strip: 3cb60b30b6cf5733, Pass\n");
else
printf("strip: 3cb60b30b6cf5733, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000063c8))=0x006a0802;
*((unsigned int *)((unsigned long)context_ptr+0x000063c8+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000063c8+4*2))=0x02020033;
*((unsigned int *)((unsigned long)context_ptr+0x000063c8+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x000060ac))=0x30cc508b;
*((unsigned int *)((unsigned long)context_ptr+0x000060ac+4*1))=0xd5efabaa;
*((unsigned int *)((unsigned long)context_ptr+0x000060ac+4*2))=0x2281b971;
*((unsigned int *)((unsigned long)context_ptr+0x000060ac+4*3))=0x8eedb88a;
*((unsigned int *)((unsigned long)context_ptr+0x000060ac+4*4))=0x48b18343;
*((unsigned int *)((unsigned long)context_ptr+0x000060ac+4*5))=0x344c3121;
*((unsigned int *)((unsigned long)context_ptr+0x000060ac+4*6))=0xb06f0a4b;
*((unsigned int *)((unsigned long)context_ptr+0x000060ac+4*7))=0x6b1a2a02;
*((unsigned int *)((unsigned long)context_ptr+0x000060ac+4*8))=0x5a6644df;
*((unsigned int *)((unsigned long)context_ptr+0x000060ac+4*9))=0x0a371727;
*((unsigned int *)((unsigned long)context_ptr+0x000060ac+4*10))=0xfd47c264;
*((unsigned int *)((unsigned long)context_ptr+0x000060ac+4*11))=0x9191c181;
*((unsigned int *)((unsigned long)context_ptr+0x000060ac+4*12))=0x0034c8c8;
*((unsigned int *)((unsigned long)context_ptr+0x000034b0))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x000034b0+4*1))=0x000062e8;
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
*((unsigned int *)((unsigned long)context_ptr+0x000004b0+4*1))=0x000060ac;
*((unsigned int *)((unsigned long)context_ptr+0x000004b0+4*2))=0x000063c8;
*((unsigned int *)((unsigned long)context_ptr+0x000004b0+4*3))=0x02220033;
*((unsigned int *)((unsigned long)context_ptr+0x000004b0+4*4))=0x03b4590b;
*((unsigned int *)((unsigned long)context_ptr+0x000004b0+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000000de&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000063d8,"\x0d\x71\x72\xac\xfc\x3b\xe9\x5f\xef\x7d\xc1\xcc\x40\x17\x31\xf0",16))
printf("strip: 0d7172acfc3be95f, Pass\n");
else
printf("strip: 0d7172acfc3be95f, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000063d8))=0x006a0802;
*((unsigned int *)((unsigned long)context_ptr+0x000063d8+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000063d8+4*2))=0x02020034;
*((unsigned int *)((unsigned long)context_ptr+0x000063d8+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x000060e0))=0xc495dfba;
*((unsigned int *)((unsigned long)context_ptr+0x000060e0+4*1))=0x8e7489b0;
*((unsigned int *)((unsigned long)context_ptr+0x000060e0+4*2))=0xe6a40147;
*((unsigned int *)((unsigned long)context_ptr+0x000060e0+4*3))=0x08b36f5a;
*((unsigned int *)((unsigned long)context_ptr+0x000060e0+4*4))=0x0ba6c53f;
*((unsigned int *)((unsigned long)context_ptr+0x000060e0+4*5))=0xf01d9860;
*((unsigned int *)((unsigned long)context_ptr+0x000060e0+4*6))=0x40119b2c;
*((unsigned int *)((unsigned long)context_ptr+0x000060e0+4*7))=0xe4fac325;
*((unsigned int *)((unsigned long)context_ptr+0x000060e0+4*8))=0xa8e8a437;
*((unsigned int *)((unsigned long)context_ptr+0x000060e0+4*9))=0xa554720f;
*((unsigned int *)((unsigned long)context_ptr+0x000060e0+4*10))=0x0e0ca80f;
*((unsigned int *)((unsigned long)context_ptr+0x000060e0+4*11))=0x43c4dd3a;
*((unsigned int *)((unsigned long)context_ptr+0x000060e0+4*12))=0x8eee4202;
*((unsigned int *)((unsigned long)context_ptr+0x000034c8))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x000034c8+4*1))=0x000062f8;
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
*((unsigned int *)((unsigned long)context_ptr+0x000004c8+4*1))=0x000060e0;
*((unsigned int *)((unsigned long)context_ptr+0x000004c8+4*2))=0x000063d8;
*((unsigned int *)((unsigned long)context_ptr+0x000004c8+4*3))=0x02220034;
*((unsigned int *)((unsigned long)context_ptr+0x000004c8+4*4))=0x0a100ba8;
*((unsigned int *)((unsigned long)context_ptr+0x000004c8+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000000e4&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000063e8,"\x89\x19\x7e\xd8\x4b\x3c\xb3\x11\x9a\x21\x0b\x35\x4c\x35\x94\x45",16))
printf("strip: 89197ed84b3cb311, Pass\n");
else
printf("strip: 89197ed84b3cb311, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000063e8))=0x006a0802;
*((unsigned int *)((unsigned long)context_ptr+0x000063e8+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000063e8+4*2))=0x02020035;
*((unsigned int *)((unsigned long)context_ptr+0x000063e8+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x000064cc))=0xde59e4f7;
*((unsigned int *)((unsigned long)context_ptr+0x000064cc+4*1))=0x9ab2b750;
*((unsigned int *)((unsigned long)context_ptr+0x000064cc+4*2))=0x6cd0cbe6;
*((unsigned int *)((unsigned long)context_ptr+0x000064cc+4*3))=0x6c50bae2;
*((unsigned int *)((unsigned long)context_ptr+0x000064cc+4*4))=0x605fd93d;
*((unsigned int *)((unsigned long)context_ptr+0x000064cc+4*5))=0xd1488f63;
*((unsigned int *)((unsigned long)context_ptr+0x000064cc+4*6))=0x6011caab;
*((unsigned int *)((unsigned long)context_ptr+0x000064cc+4*7))=0xda563135;
*((unsigned int *)((unsigned long)context_ptr+0x000064cc+4*8))=0xc9d91060;
*((unsigned int *)((unsigned long)context_ptr+0x000064cc+4*9))=0x5b270b8c;
*((unsigned int *)((unsigned long)context_ptr+0x000064cc+4*10))=0xf7c44c6a;
*((unsigned int *)((unsigned long)context_ptr+0x000064cc+4*11))=0x23732b6d;
*((unsigned int *)((unsigned long)context_ptr+0x000064cc+4*12))=0x5afb6876;
*((unsigned int *)((unsigned long)context_ptr+0x000064cc+4*13))=0x0000001f;
*((unsigned int *)((unsigned long)context_ptr+0x000034e0))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x000034e0+4*1))=0x00006308;
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
*((unsigned int *)((unsigned long)context_ptr+0x000004e0+4*1))=0x000064cc;
*((unsigned int *)((unsigned long)context_ptr+0x000004e0+4*2))=0x000063e8;
*((unsigned int *)((unsigned long)context_ptr+0x000004e0+4*3))=0x02220035;
*((unsigned int *)((unsigned long)context_ptr+0x000004e0+4*4))=0x0b2396f8;
*((unsigned int *)((unsigned long)context_ptr+0x000004e0+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000000ea&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000063f8,"\x42\xc3\x17\xbb\xb8\xfe\x18\x67\x23\x3e\x21\x9c\x44\x51\xd4\xb5",16))
printf("strip: 42c317bbb8fe1867, Pass\n");
else
printf("strip: 42c317bbb8fe1867, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000063f8))=0x006a0802;
*((unsigned int *)((unsigned long)context_ptr+0x000063f8+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000063f8+4*2))=0x02020036;
*((unsigned int *)((unsigned long)context_ptr+0x000063f8+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x00006114))=0xf288963c;
*((unsigned int *)((unsigned long)context_ptr+0x00006114+4*1))=0xb1e0c7f9;
*((unsigned int *)((unsigned long)context_ptr+0x00006114+4*2))=0x6fb388c9;
*((unsigned int *)((unsigned long)context_ptr+0x00006114+4*3))=0x41ffeaeb;
*((unsigned int *)((unsigned long)context_ptr+0x00006114+4*4))=0x655e9d37;
*((unsigned int *)((unsigned long)context_ptr+0x00006114+4*5))=0xcedaadc5;
*((unsigned int *)((unsigned long)context_ptr+0x00006114+4*6))=0xca6c1a7d;
*((unsigned int *)((unsigned long)context_ptr+0x00006114+4*7))=0xd166d75d;
*((unsigned int *)((unsigned long)context_ptr+0x00006114+4*8))=0xec01abc2;
*((unsigned int *)((unsigned long)context_ptr+0x00006114+4*9))=0xdc03175d;
*((unsigned int *)((unsigned long)context_ptr+0x00006114+4*10))=0xeffc966b;
*((unsigned int *)((unsigned long)context_ptr+0x00006114+4*11))=0x6ba4bba1;
*((unsigned int *)((unsigned long)context_ptr+0x00006114+4*12))=0x364c351d;
*((unsigned int *)((unsigned long)context_ptr+0x00006114+4*13))=0x000034ee;
*((unsigned int *)((unsigned long)context_ptr+0x000034f8))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x000034f8+4*1))=0x00006318;
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
*((unsigned int *)((unsigned long)context_ptr+0x000004f8+4*1))=0x00006114;
*((unsigned int *)((unsigned long)context_ptr+0x000004f8+4*2))=0x000063f8;
*((unsigned int *)((unsigned long)context_ptr+0x000004f8+4*3))=0x02220036;
*((unsigned int *)((unsigned long)context_ptr+0x000004f8+4*4))=0x0f883d4d;
*((unsigned int *)((unsigned long)context_ptr+0x000004f8+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000000f0&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006408,"\x49\xac\xf3\x73\x7a\xfe\x2c\x65\x4b\x57\xae\xca\x1f\xc8\xe6\xc4",16))
printf("strip: 49acf3737afe2c65, Pass\n");
else
printf("strip: 49acf3737afe2c65, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006408))=0x006a0802;
*((unsigned int *)((unsigned long)context_ptr+0x00006408+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006408+4*2))=0x02020037;
*((unsigned int *)((unsigned long)context_ptr+0x00006408+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x0000614c))=0xac889d7b;
*((unsigned int *)((unsigned long)context_ptr+0x0000614c+4*1))=0xf1fa3f4b;
*((unsigned int *)((unsigned long)context_ptr+0x0000614c+4*2))=0x45fefbbd;
*((unsigned int *)((unsigned long)context_ptr+0x0000614c+4*3))=0x26b7eb58;
*((unsigned int *)((unsigned long)context_ptr+0x0000614c+4*4))=0x9d3431c9;
*((unsigned int *)((unsigned long)context_ptr+0x0000614c+4*5))=0xb0296135;
*((unsigned int *)((unsigned long)context_ptr+0x0000614c+4*6))=0xfc18e89d;
*((unsigned int *)((unsigned long)context_ptr+0x0000614c+4*7))=0xf259074e;
*((unsigned int *)((unsigned long)context_ptr+0x0000614c+4*8))=0xad467e4a;
*((unsigned int *)((unsigned long)context_ptr+0x0000614c+4*9))=0xa01bec5f;
*((unsigned int *)((unsigned long)context_ptr+0x0000614c+4*10))=0xc6885efc;
*((unsigned int *)((unsigned long)context_ptr+0x0000614c+4*11))=0xe1da7925;
*((unsigned int *)((unsigned long)context_ptr+0x0000614c+4*12))=0xae88cc86;
*((unsigned int *)((unsigned long)context_ptr+0x0000614c+4*13))=0x001713cf;
*((unsigned int *)((unsigned long)context_ptr+0x00003510))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003510+4*1))=0x00006328;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000510+4*1))=0x0000614c;
*((unsigned int *)((unsigned long)context_ptr+0x00000510+4*2))=0x00006408;
*((unsigned int *)((unsigned long)context_ptr+0x00000510+4*3))=0x02220037;
*((unsigned int *)((unsigned long)context_ptr+0x00000510+4*4))=0x038411ff;
*((unsigned int *)((unsigned long)context_ptr+0x00000510+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000000f6&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006418,"\x2f\x06\xff\xad\x60\x6d\x46\xf9\xcd\x55\x87\xbd\x65\x5d\xac\x13",16))
printf("strip: 2f06ffad606d46f9, Pass\n");
else
printf("strip: 2f06ffad606d46f9, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006418))=0x006a0802;
*((unsigned int *)((unsigned long)context_ptr+0x00006418+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006418+4*2))=0x02020038;
*((unsigned int *)((unsigned long)context_ptr+0x00006418+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x00006184))=0x89d7a0d4;
*((unsigned int *)((unsigned long)context_ptr+0x00006184+4*1))=0x7291ec03;
*((unsigned int *)((unsigned long)context_ptr+0x00006184+4*2))=0x50c89075;
*((unsigned int *)((unsigned long)context_ptr+0x00006184+4*3))=0xc67a306d;
*((unsigned int *)((unsigned long)context_ptr+0x00006184+4*4))=0x2928d80a;
*((unsigned int *)((unsigned long)context_ptr+0x00006184+4*5))=0xd9afbd36;
*((unsigned int *)((unsigned long)context_ptr+0x00006184+4*6))=0x2929e730;
*((unsigned int *)((unsigned long)context_ptr+0x00006184+4*7))=0xacc2556b;
*((unsigned int *)((unsigned long)context_ptr+0x00006184+4*8))=0x1a861c0f;
*((unsigned int *)((unsigned long)context_ptr+0x00006184+4*9))=0x029eb78f;
*((unsigned int *)((unsigned long)context_ptr+0x00006184+4*10))=0x867541ef;
*((unsigned int *)((unsigned long)context_ptr+0x00006184+4*11))=0xd6a84ffa;
*((unsigned int *)((unsigned long)context_ptr+0x00006184+4*12))=0x21473990;
*((unsigned int *)((unsigned long)context_ptr+0x00006184+4*13))=0xeb547ebb;
*((unsigned int *)((unsigned long)context_ptr+0x00003528))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003528+4*1))=0x00006338;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000528+4*1))=0x00006184;
*((unsigned int *)((unsigned long)context_ptr+0x00000528+4*2))=0x00006418;
*((unsigned int *)((unsigned long)context_ptr+0x00000528+4*3))=0x02220038;
*((unsigned int *)((unsigned long)context_ptr+0x00000528+4*4))=0x09edcf3b;
*((unsigned int *)((unsigned long)context_ptr+0x00000528+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000000fc&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006428,"\xb2\x0a\x1a\x8e\xda\x3b\xd3\x03\x5a\x78\x32\x40\x97\xf7\x00\x1e",16))
printf("strip: b20a1a8eda3bd303, Pass\n");
else
printf("strip: b20a1a8eda3bd303, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006428))=0x006a0802;
*((unsigned int *)((unsigned long)context_ptr+0x00006428+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006428+4*2))=0x02020039;
*((unsigned int *)((unsigned long)context_ptr+0x00006428+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x00006504))=0xdd7ed37f;
*((unsigned int *)((unsigned long)context_ptr+0x00006504+4*1))=0xcc682d6c;
*((unsigned int *)((unsigned long)context_ptr+0x00006504+4*2))=0xb2b5e99c;
*((unsigned int *)((unsigned long)context_ptr+0x00006504+4*3))=0xdd8bb8ec;
*((unsigned int *)((unsigned long)context_ptr+0x00006504+4*4))=0x7f39edeb;
*((unsigned int *)((unsigned long)context_ptr+0x00006504+4*5))=0x9a690ca3;
*((unsigned int *)((unsigned long)context_ptr+0x00006504+4*6))=0x50520ad7;
*((unsigned int *)((unsigned long)context_ptr+0x00006504+4*7))=0x7dfd5329;
*((unsigned int *)((unsigned long)context_ptr+0x00006504+4*8))=0xebfcc912;
*((unsigned int *)((unsigned long)context_ptr+0x00006504+4*9))=0x92d2679c;
*((unsigned int *)((unsigned long)context_ptr+0x00006504+4*10))=0xb279aa2d;
*((unsigned int *)((unsigned long)context_ptr+0x00006504+4*11))=0x4a4d4a34;
*((unsigned int *)((unsigned long)context_ptr+0x00006504+4*12))=0x03aa59b4;
*((unsigned int *)((unsigned long)context_ptr+0x00006504+4*13))=0x0cea7706;
*((unsigned int *)((unsigned long)context_ptr+0x00006504+4*14))=0x00000015;
*((unsigned int *)((unsigned long)context_ptr+0x00003540))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003540+4*1))=0x00006348;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000540+4*1))=0x00006504;
*((unsigned int *)((unsigned long)context_ptr+0x00000540+4*2))=0x00006428;
*((unsigned int *)((unsigned long)context_ptr+0x00000540+4*3))=0x02220039;
*((unsigned int *)((unsigned long)context_ptr+0x00000540+4*4))=0x012ee1df;
*((unsigned int *)((unsigned long)context_ptr+0x00000540+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000102&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006438,"\x7b\xd4\x37\xa8\x46\xb2\x31\xf6\x8b\x0f\xd5\xfe\x96\x76\x26\x9c",16))
printf("strip: 7bd437a846b231f6, Pass\n");
else
printf("strip: 7bd437a846b231f6, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006438))=0x006a0802;
*((unsigned int *)((unsigned long)context_ptr+0x00006438+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006438+4*2))=0x0202003a;
*((unsigned int *)((unsigned long)context_ptr+0x00006438+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x000061bc))=0xf06cefc8;
*((unsigned int *)((unsigned long)context_ptr+0x000061bc+4*1))=0x7e4b1780;
*((unsigned int *)((unsigned long)context_ptr+0x000061bc+4*2))=0x8c8a0fe1;
*((unsigned int *)((unsigned long)context_ptr+0x000061bc+4*3))=0xaa795edd;
*((unsigned int *)((unsigned long)context_ptr+0x000061bc+4*4))=0x3d73a239;
*((unsigned int *)((unsigned long)context_ptr+0x000061bc+4*5))=0x48ad973f;
*((unsigned int *)((unsigned long)context_ptr+0x000061bc+4*6))=0x9758f762;
*((unsigned int *)((unsigned long)context_ptr+0x000061bc+4*7))=0x5f3b6a74;
*((unsigned int *)((unsigned long)context_ptr+0x000061bc+4*8))=0xf4ff74d4;
*((unsigned int *)((unsigned long)context_ptr+0x000061bc+4*9))=0x09b42142;
*((unsigned int *)((unsigned long)context_ptr+0x000061bc+4*10))=0x753c4a32;
*((unsigned int *)((unsigned long)context_ptr+0x000061bc+4*11))=0x2e527cf3;
*((unsigned int *)((unsigned long)context_ptr+0x000061bc+4*12))=0x89380080;
*((unsigned int *)((unsigned long)context_ptr+0x000061bc+4*13))=0x4f555fdd;
*((unsigned int *)((unsigned long)context_ptr+0x000061bc+4*14))=0x000083dd;
*((unsigned int *)((unsigned long)context_ptr+0x00003558))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003558+4*1))=0x000061f8;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000558+4*1))=0x000061bc;
*((unsigned int *)((unsigned long)context_ptr+0x00000558+4*2))=0x00006438;
*((unsigned int *)((unsigned long)context_ptr+0x00000558+4*3))=0x0222003a;
*((unsigned int *)((unsigned long)context_ptr+0x00000558+4*4))=0x041b1ea6;
*((unsigned int *)((unsigned long)context_ptr+0x00000558+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000108&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006258,"\x14\x61\x7b\xc7\xdd\x2f\x32\x57\x66\xa3\xac\x1a\xca\xdb\x0c\x84",16))
printf("strip: 14617bc7dd2f3257, Pass\n");
else
printf("strip: 14617bc7dd2f3257, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006358))=0x006a0802;
*((unsigned int *)((unsigned long)context_ptr+0x00006358+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006358+4*2))=0x0202003b;
*((unsigned int *)((unsigned long)context_ptr+0x00006358+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x00006208))=0x1155eead;
*((unsigned int *)((unsigned long)context_ptr+0x00006208+4*1))=0xaa25035c;
*((unsigned int *)((unsigned long)context_ptr+0x00006208+4*2))=0x29e92046;
*((unsigned int *)((unsigned long)context_ptr+0x00006208+4*3))=0xc1dc8057;
*((unsigned int *)((unsigned long)context_ptr+0x00006208+4*4))=0x3183fa97;
*((unsigned int *)((unsigned long)context_ptr+0x00006208+4*5))=0x7e655f7d;
*((unsigned int *)((unsigned long)context_ptr+0x00006208+4*6))=0xf0b38bd2;
*((unsigned int *)((unsigned long)context_ptr+0x00006208+4*7))=0x9fcaba1e;
*((unsigned int *)((unsigned long)context_ptr+0x00006208+4*8))=0x261850bb;
*((unsigned int *)((unsigned long)context_ptr+0x00006208+4*9))=0x752e7ed5;
*((unsigned int *)((unsigned long)context_ptr+0x00006208+4*10))=0x2f067b86;
*((unsigned int *)((unsigned long)context_ptr+0x00006208+4*11))=0x4fc65799;
*((unsigned int *)((unsigned long)context_ptr+0x00006208+4*12))=0x4d5290c9;
*((unsigned int *)((unsigned long)context_ptr+0x00006208+4*13))=0xebc71267;
*((unsigned int *)((unsigned long)context_ptr+0x00006208+4*14))=0x00c996a3;
*((unsigned int *)((unsigned long)context_ptr+0x00003570))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003570+4*1))=0x00006244;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000570+4*1))=0x00006208;
*((unsigned int *)((unsigned long)context_ptr+0x00000570+4*2))=0x00006358;
*((unsigned int *)((unsigned long)context_ptr+0x00000570+4*3))=0x0222003b;
*((unsigned int *)((unsigned long)context_ptr+0x00000570+4*4))=0x0afad62f;
*((unsigned int *)((unsigned long)context_ptr+0x00000570+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000010e&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006268,"\xca\xc4\x0a\xfe\xcf\x61\x2b\x39\x25\x24\x38\x02\x5e\x81\x2c\xbb",16))
printf("strip: cac40afecf612b39, Pass\n");
else
printf("strip: cac40afecf612b39, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006368))=0x006a0802;
*((unsigned int *)((unsigned long)context_ptr+0x00006368+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006368+4*2))=0x0202003c;
*((unsigned int *)((unsigned long)context_ptr+0x00006368+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x00006540))=0xecbdaaf3;
*((unsigned int *)((unsigned long)context_ptr+0x00006540+4*1))=0x9501faf1;
*((unsigned int *)((unsigned long)context_ptr+0x00006540+4*2))=0x2731a6f5;
*((unsigned int *)((unsigned long)context_ptr+0x00006540+4*3))=0x5e688756;
*((unsigned int *)((unsigned long)context_ptr+0x00006540+4*4))=0x8263a416;
*((unsigned int *)((unsigned long)context_ptr+0x00006540+4*5))=0xb54bfe0d;
*((unsigned int *)((unsigned long)context_ptr+0x00006540+4*6))=0x5a5f2bcd;
*((unsigned int *)((unsigned long)context_ptr+0x00006540+4*7))=0xa6c1a82b;
*((unsigned int *)((unsigned long)context_ptr+0x00006540+4*8))=0x7f6a17bc;
*((unsigned int *)((unsigned long)context_ptr+0x00006540+4*9))=0x868a74f7;
*((unsigned int *)((unsigned long)context_ptr+0x00006540+4*10))=0xeee4002d;
*((unsigned int *)((unsigned long)context_ptr+0x00006540+4*11))=0x92e12704;
*((unsigned int *)((unsigned long)context_ptr+0x00006540+4*12))=0x42cd8515;
*((unsigned int *)((unsigned long)context_ptr+0x00006540+4*13))=0x0164bc6c;
*((unsigned int *)((unsigned long)context_ptr+0x00006540+4*14))=0x6ab08d48;
*((unsigned int *)((unsigned long)context_ptr+0x00003588))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003588+4*1))=0x00006254;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000588+4*1))=0x00006540;
*((unsigned int *)((unsigned long)context_ptr+0x00000588+4*2))=0x00006368;
*((unsigned int *)((unsigned long)context_ptr+0x00000588+4*3))=0x0222003c;
*((unsigned int *)((unsigned long)context_ptr+0x00000588+4*4))=0x0f9a847d;
*((unsigned int *)((unsigned long)context_ptr+0x00000588+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000114&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006378,"\x53\xca\xab\x02\x60\xb4\x7b\xad\x76\x1b\x4d\xf6\x81\x6c\x9d\xcf",16))
printf("strip: 53caab0260b47bad, Pass\n");
else
printf("strip: 53caab0260b47bad, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006378))=0x006a0802;
*((unsigned int *)((unsigned long)context_ptr+0x00006378+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006378+4*2))=0x0202003d;
*((unsigned int *)((unsigned long)context_ptr+0x00006378+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x00006264))=0x7db90b6f;
*((unsigned int *)((unsigned long)context_ptr+0x00006264+4*1))=0xf6f745df;
*((unsigned int *)((unsigned long)context_ptr+0x00006264+4*2))=0x11202762;
*((unsigned int *)((unsigned long)context_ptr+0x00006264+4*3))=0x775dde0a;
*((unsigned int *)((unsigned long)context_ptr+0x00006264+4*4))=0x5b66cd6f;
*((unsigned int *)((unsigned long)context_ptr+0x00006264+4*5))=0x75a862ad;
*((unsigned int *)((unsigned long)context_ptr+0x00006264+4*6))=0xf1406791;
*((unsigned int *)((unsigned long)context_ptr+0x00006264+4*7))=0xa249a296;
*((unsigned int *)((unsigned long)context_ptr+0x00006264+4*8))=0x418a948d;
*((unsigned int *)((unsigned long)context_ptr+0x00006264+4*9))=0x4d4f14a7;
*((unsigned int *)((unsigned long)context_ptr+0x00006264+4*10))=0xda34006f;
*((unsigned int *)((unsigned long)context_ptr+0x00006264+4*11))=0x839b03ca;
*((unsigned int *)((unsigned long)context_ptr+0x00006264+4*12))=0x615cbd18;
*((unsigned int *)((unsigned long)context_ptr+0x00006264+4*13))=0xd7d59b5d;
*((unsigned int *)((unsigned long)context_ptr+0x00006264+4*14))=0x9f0fe550;
*((unsigned int *)((unsigned long)context_ptr+0x00006264+4*15))=0x000000b3;
*((unsigned int *)((unsigned long)context_ptr+0x000035a0))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x000035a0+4*1))=0x00006038;
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
*((unsigned int *)((unsigned long)context_ptr+0x000005a0+4*1))=0x00006264;
*((unsigned int *)((unsigned long)context_ptr+0x000005a0+4*2))=0x00006378;
*((unsigned int *)((unsigned long)context_ptr+0x000005a0+4*3))=0x0222003d;
*((unsigned int *)((unsigned long)context_ptr+0x000005a0+4*4))=0x06a2496c;
*((unsigned int *)((unsigned long)context_ptr+0x000005a0+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000011a&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006028,"\xab\x2c\x5a\x98\x39\x5d\x69\x7e\xb7\xd6\xda\xc4\x8d\xe4\x59\x6c",16))
printf("strip: ab2c5a98395d697e, Pass\n");
else
printf("strip: ab2c5a98395d697e, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006028))=0x006a0802;
*((unsigned int *)((unsigned long)context_ptr+0x00006028+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006028+4*2))=0x0202003e;
*((unsigned int *)((unsigned long)context_ptr+0x00006028+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x0000657c))=0xb7771579;
*((unsigned int *)((unsigned long)context_ptr+0x0000657c+4*1))=0x72fc2039;
*((unsigned int *)((unsigned long)context_ptr+0x0000657c+4*2))=0x6ab2fea5;
*((unsigned int *)((unsigned long)context_ptr+0x0000657c+4*3))=0x91737f8a;
*((unsigned int *)((unsigned long)context_ptr+0x0000657c+4*4))=0xe7f61d4f;
*((unsigned int *)((unsigned long)context_ptr+0x0000657c+4*5))=0x77e370b0;
*((unsigned int *)((unsigned long)context_ptr+0x0000657c+4*6))=0xc42deca4;
*((unsigned int *)((unsigned long)context_ptr+0x0000657c+4*7))=0x548f69ef;
*((unsigned int *)((unsigned long)context_ptr+0x0000657c+4*8))=0x643e55ee;
*((unsigned int *)((unsigned long)context_ptr+0x0000657c+4*9))=0xb6182818;
*((unsigned int *)((unsigned long)context_ptr+0x0000657c+4*10))=0x4cb00955;
*((unsigned int *)((unsigned long)context_ptr+0x0000657c+4*11))=0xee95eacf;
*((unsigned int *)((unsigned long)context_ptr+0x0000657c+4*12))=0x05b664ec;
*((unsigned int *)((unsigned long)context_ptr+0x0000657c+4*13))=0x4c91f7a1;
*((unsigned int *)((unsigned long)context_ptr+0x0000657c+4*14))=0x724b618a;
*((unsigned int *)((unsigned long)context_ptr+0x0000657c+4*15))=0x00007939;
*((unsigned int *)((unsigned long)context_ptr+0x000035b8))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x000035b8+4*1))=0x000062a4;
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
*((unsigned int *)((unsigned long)context_ptr+0x000005b8+4*1))=0x0000657c;
*((unsigned int *)((unsigned long)context_ptr+0x000005b8+4*2))=0x00006028;
*((unsigned int *)((unsigned long)context_ptr+0x000005b8+4*3))=0x0222003e;
*((unsigned int *)((unsigned long)context_ptr+0x000005b8+4*4))=0x005b03a2;
*((unsigned int *)((unsigned long)context_ptr+0x000005b8+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000120&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006478,"\x72\x3a\x67\xd8\x06\x16\x08\x83\xe6\x38\x45\xde\x95\x3e\x88\xed",16))
printf("strip: 723a67d806160883, Pass\n");
else
printf("strip: 723a67d806160883, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000062b4))=0x006a0802;
*((unsigned int *)((unsigned long)context_ptr+0x000062b4+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000062b4+4*2))=0x0202003f;
*((unsigned int *)((unsigned long)context_ptr+0x000062b4+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x00006448))=0xe8c65386;
*((unsigned int *)((unsigned long)context_ptr+0x00006448+4*1))=0xc2b77b53;
*((unsigned int *)((unsigned long)context_ptr+0x00006448+4*2))=0x12e09348;
*((unsigned int *)((unsigned long)context_ptr+0x00006448+4*3))=0xe3d3b3d3;
*((unsigned int *)((unsigned long)context_ptr+0x00006448+4*4))=0x9218aabe;
*((unsigned int *)((unsigned long)context_ptr+0x00006448+4*5))=0x9b156f08;
*((unsigned int *)((unsigned long)context_ptr+0x00006448+4*6))=0x15aabc08;
*((unsigned int *)((unsigned long)context_ptr+0x00006448+4*7))=0xe8bec521;
*((unsigned int *)((unsigned long)context_ptr+0x00006448+4*8))=0x79f43459;
*((unsigned int *)((unsigned long)context_ptr+0x00006448+4*9))=0x39ce1791;
*((unsigned int *)((unsigned long)context_ptr+0x00006448+4*10))=0x9a2876f3;
*((unsigned int *)((unsigned long)context_ptr+0x00006448+4*11))=0x817c1c3f;
*((unsigned int *)((unsigned long)context_ptr+0x00006448+4*12))=0xd337e6b6;
*((unsigned int *)((unsigned long)context_ptr+0x00006448+4*13))=0x62c02074;
*((unsigned int *)((unsigned long)context_ptr+0x00006448+4*14))=0x943f008f;
*((unsigned int *)((unsigned long)context_ptr+0x00006448+4*15))=0x00862107;
*((unsigned int *)((unsigned long)context_ptr+0x000035d0))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x000035d0+4*1))=0x00006048;
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
*((unsigned int *)((unsigned long)context_ptr+0x000005d0+4*1))=0x00006448;
*((unsigned int *)((unsigned long)context_ptr+0x000005d0+4*2))=0x000062b4;
*((unsigned int *)((unsigned long)context_ptr+0x000005d0+4*3))=0x0222003f;
*((unsigned int *)((unsigned long)context_ptr+0x000005d0+4*4))=0x0e484a49;
*((unsigned int *)((unsigned long)context_ptr+0x000005d0+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000126&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006488,"\x87\x7a\x06\xc3\xac\xc3\x47\xa2\xe8\x85\xd1\xe8\x8b\x63\xa8\x4d",16))
printf("strip: 877a06c3acc347a2, Pass\n");
else
printf("strip: 877a06c3acc347a2, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006488))=0x006a0802;
*((unsigned int *)((unsigned long)context_ptr+0x00006488+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006488+4*2))=0x02020040;
*((unsigned int *)((unsigned long)context_ptr+0x00006488+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x00006058))=0xcf0f0764;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*1))=0x5234187e;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*2))=0xc7809b0e;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*3))=0xd3cd8b79;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*4))=0xc5e51953;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*5))=0x67dd0f05;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*6))=0xfbff9001;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*7))=0xd12fbc3e;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*8))=0xd4afd19d;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*9))=0x1f2f4523;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*10))=0x58731538;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*11))=0x0bb33202;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*12))=0x09eadb04;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*13))=0xa0945b42;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*14))=0x606645f6;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*15))=0xa9e831d6;
*((unsigned int *)((unsigned long)context_ptr+0x000035e8))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x000035e8+4*1))=0x000062c4;
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
*((unsigned int *)((unsigned long)context_ptr+0x000005e8+4*1))=0x00006058;
*((unsigned int *)((unsigned long)context_ptr+0x000005e8+4*2))=0x00006488;
*((unsigned int *)((unsigned long)context_ptr+0x000005e8+4*3))=0x02220040;
*((unsigned int *)((unsigned long)context_ptr+0x000005e8+4*4))=0x0325c181;
*((unsigned int *)((unsigned long)context_ptr+0x000005e8+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000012c&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000062d8,"\x9e\x66\xc7\x92\xf4\x0e\x8b\x58\xb3\x92\xc6\x54\x72\xa5\x89\xed",16))
printf("strip: 9e66c792f40e8b58, Pass\n");
else
printf("strip: 9e66c792f40e8b58, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006098))=0x006a0802;
*((unsigned int *)((unsigned long)context_ptr+0x00006098+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006098+4*2))=0x02020041;
*((unsigned int *)((unsigned long)context_ptr+0x00006098+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x000065bc))=0x2c361d21;
*((unsigned int *)((unsigned long)context_ptr+0x000065bc+4*1))=0xdc893331;
*((unsigned int *)((unsigned long)context_ptr+0x000065bc+4*2))=0xfdc8a886;
*((unsigned int *)((unsigned long)context_ptr+0x000065bc+4*3))=0x3132f146;
*((unsigned int *)((unsigned long)context_ptr+0x000065bc+4*4))=0xe7e614cb;
*((unsigned int *)((unsigned long)context_ptr+0x000065bc+4*5))=0x127ab2b3;
*((unsigned int *)((unsigned long)context_ptr+0x000065bc+4*6))=0x4e96c258;
*((unsigned int *)((unsigned long)context_ptr+0x000065bc+4*7))=0xb388352c;
*((unsigned int *)((unsigned long)context_ptr+0x000065bc+4*8))=0xa2b4c7f1;
*((unsigned int *)((unsigned long)context_ptr+0x000065bc+4*9))=0x66c89cff;
*((unsigned int *)((unsigned long)context_ptr+0x000065bc+4*10))=0x82ca5d23;
*((unsigned int *)((unsigned long)context_ptr+0x000065bc+4*11))=0xbf5c357e;
*((unsigned int *)((unsigned long)context_ptr+0x000065bc+4*12))=0xeef52c6a;
*((unsigned int *)((unsigned long)context_ptr+0x000065bc+4*13))=0x12fc7ddc;
*((unsigned int *)((unsigned long)context_ptr+0x000065bc+4*14))=0x8f5808a7;
*((unsigned int *)((unsigned long)context_ptr+0x000065bc+4*15))=0xe2ef6f7b;
*((unsigned int *)((unsigned long)context_ptr+0x000065bc+4*16))=0x000000e3;
*((unsigned int *)((unsigned long)context_ptr+0x00003600))=0x04c00010;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000600+4*1))=0x000065bc;
*((unsigned int *)((unsigned long)context_ptr+0x00000600+4*2))=0x00006098;
*((unsigned int *)((unsigned long)context_ptr+0x00000600+4*3))=0x02220041;
*((unsigned int *)((unsigned long)context_ptr+0x00000600+4*4))=0x0a94709f;
*((unsigned int *)((unsigned long)context_ptr+0x00000600+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000132&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000062e8,"\xec\xd2\xf4\xd3\x38\xa4\x15\x6b\xf0\x5b\xbb\x23\xf0\x30\x9b\x6a",16))
printf("strip: ecd2f4d338a4156b, Pass\n");
else
printf("strip: ecd2f4d338a4156b, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000062e4))=0x006a0802;
*((unsigned int *)((unsigned long)context_ptr+0x000062e4+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000062e4+4*2))=0x02020042;
*((unsigned int *)((unsigned long)context_ptr+0x000062e4+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x00006388))=0x4605184a;
*((unsigned int *)((unsigned long)context_ptr+0x00006388+4*1))=0xd17ab70a;
*((unsigned int *)((unsigned long)context_ptr+0x00006388+4*2))=0x877b79d5;
*((unsigned int *)((unsigned long)context_ptr+0x00006388+4*3))=0x46f579a7;
*((unsigned int *)((unsigned long)context_ptr+0x00006388+4*4))=0x3016f809;
*((unsigned int *)((unsigned long)context_ptr+0x00006388+4*5))=0xa750d746;
*((unsigned int *)((unsigned long)context_ptr+0x00006388+4*6))=0x833a8bd8;
*((unsigned int *)((unsigned long)context_ptr+0x00006388+4*7))=0x662e5d05;
*((unsigned int *)((unsigned long)context_ptr+0x00006388+4*8))=0xceb0ab0f;
*((unsigned int *)((unsigned long)context_ptr+0x00006388+4*9))=0xfb251f98;
*((unsigned int *)((unsigned long)context_ptr+0x00006388+4*10))=0x527ca9b2;
*((unsigned int *)((unsigned long)context_ptr+0x00006388+4*11))=0x583ff0d9;
*((unsigned int *)((unsigned long)context_ptr+0x00006388+4*12))=0xbe93fc51;
*((unsigned int *)((unsigned long)context_ptr+0x00006388+4*13))=0xd0be5355;
*((unsigned int *)((unsigned long)context_ptr+0x00006388+4*14))=0x4da6e024;
*((unsigned int *)((unsigned long)context_ptr+0x00006388+4*15))=0x7085f232;
*((unsigned int *)((unsigned long)context_ptr+0x00006388+4*16))=0x0000a94e;
*((unsigned int *)((unsigned long)context_ptr+0x00003618))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003618+4*1))=0x00006498;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000618+4*1))=0x00006388;
*((unsigned int *)((unsigned long)context_ptr+0x00000618+4*2))=0x000062e4;
*((unsigned int *)((unsigned long)context_ptr+0x00000618+4*3))=0x02220042;
*((unsigned int *)((unsigned long)context_ptr+0x00000618+4*4))=0x09dc0a99;
*((unsigned int *)((unsigned long)context_ptr+0x00000618+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000138&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000062f8,"\xa8\xe9\x6b\x09\xb7\x68\x9b\xb5\xf3\x05\xd4\xcd\xb5\xaf\xc2\xd2",16))
printf("strip: a8e96b09b7689bb5, Pass\n");
else
printf("strip: a8e96b09b7689bb5, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000062f4))=0x006a0802;
*((unsigned int *)((unsigned long)context_ptr+0x000062f4+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000062f4+4*2))=0x02020043;
*((unsigned int *)((unsigned long)context_ptr+0x000062f4+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x000060a8))=0xf9bf3a56;
*((unsigned int *)((unsigned long)context_ptr+0x000060a8+4*1))=0x3f7adfc0;
*((unsigned int *)((unsigned long)context_ptr+0x000060a8+4*2))=0xc845261c;
*((unsigned int *)((unsigned long)context_ptr+0x000060a8+4*3))=0x910aff20;
*((unsigned int *)((unsigned long)context_ptr+0x000060a8+4*4))=0x762a8093;
*((unsigned int *)((unsigned long)context_ptr+0x000060a8+4*5))=0x4e5e41d9;
*((unsigned int *)((unsigned long)context_ptr+0x000060a8+4*6))=0xf5859c63;
*((unsigned int *)((unsigned long)context_ptr+0x000060a8+4*7))=0x4b044d78;
*((unsigned int *)((unsigned long)context_ptr+0x000060a8+4*8))=0x7b92fed5;
*((unsigned int *)((unsigned long)context_ptr+0x000060a8+4*9))=0xcf595462;
*((unsigned int *)((unsigned long)context_ptr+0x000060a8+4*10))=0xe1249358;
*((unsigned int *)((unsigned long)context_ptr+0x000060a8+4*11))=0x2a40754e;
*((unsigned int *)((unsigned long)context_ptr+0x000060a8+4*12))=0x0aedb4f0;
*((unsigned int *)((unsigned long)context_ptr+0x000060a8+4*13))=0xb7f6998d;
*((unsigned int *)((unsigned long)context_ptr+0x000060a8+4*14))=0x97e544a2;
*((unsigned int *)((unsigned long)context_ptr+0x000060a8+4*15))=0x19dca300;
*((unsigned int *)((unsigned long)context_ptr+0x000060a8+4*16))=0x000a8b31;
*((unsigned int *)((unsigned long)context_ptr+0x00003630))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003630+4*1))=0x000063cc;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000630+4*1))=0x000060a8;
*((unsigned int *)((unsigned long)context_ptr+0x00000630+4*2))=0x000062f4;
*((unsigned int *)((unsigned long)context_ptr+0x00000630+4*3))=0x02220043;
*((unsigned int *)((unsigned long)context_ptr+0x00000630+4*4))=0x03ef096e;
*((unsigned int *)((unsigned long)context_ptr+0x00000630+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000013e&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006308,"\xbc\xcb\x3d\x12\x4e\x39\xb6\x49\x03\x4e\x75\xf7\xdf\x79\xf8\xf4",16))
printf("strip: bccb3d124e39b649, Pass\n");
else
printf("strip: bccb3d124e39b649, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006304))=0x006a0802;
*((unsigned int *)((unsigned long)context_ptr+0x00006304+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006304+4*2))=0x02020044;
*((unsigned int *)((unsigned long)context_ptr+0x00006304+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x000064a8))=0x7e1babfd;
*((unsigned int *)((unsigned long)context_ptr+0x000064a8+4*1))=0xa52704a2;
*((unsigned int *)((unsigned long)context_ptr+0x000064a8+4*2))=0x6f22b50d;
*((unsigned int *)((unsigned long)context_ptr+0x000064a8+4*3))=0x8f34a3cc;
*((unsigned int *)((unsigned long)context_ptr+0x000064a8+4*4))=0x271135b7;
*((unsigned int *)((unsigned long)context_ptr+0x000064a8+4*5))=0xf4c732c7;
*((unsigned int *)((unsigned long)context_ptr+0x000064a8+4*6))=0xbbc8ceb4;
*((unsigned int *)((unsigned long)context_ptr+0x000064a8+4*7))=0x667602b1;
*((unsigned int *)((unsigned long)context_ptr+0x000064a8+4*8))=0xba70c4c8;
*((unsigned int *)((unsigned long)context_ptr+0x000064a8+4*9))=0x7612dc2c;
*((unsigned int *)((unsigned long)context_ptr+0x000064a8+4*10))=0x1e62d653;
*((unsigned int *)((unsigned long)context_ptr+0x000064a8+4*11))=0xbae92eaf;
*((unsigned int *)((unsigned long)context_ptr+0x000064a8+4*12))=0x69f44fbd;
*((unsigned int *)((unsigned long)context_ptr+0x000064a8+4*13))=0xefd3a744;
*((unsigned int *)((unsigned long)context_ptr+0x000064a8+4*14))=0xed16bd6a;
*((unsigned int *)((unsigned long)context_ptr+0x000064a8+4*15))=0x634b8a02;
*((unsigned int *)((unsigned long)context_ptr+0x000064a8+4*16))=0x7ace7e71;
*((unsigned int *)((unsigned long)context_ptr+0x00003648))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003648+4*1))=0x000064ec;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000648+4*1))=0x000064a8;
*((unsigned int *)((unsigned long)context_ptr+0x00000648+4*2))=0x00006304;
*((unsigned int *)((unsigned long)context_ptr+0x00000648+4*3))=0x02220044;
*((unsigned int *)((unsigned long)context_ptr+0x00000648+4*4))=0x05cd509a;
*((unsigned int *)((unsigned long)context_ptr+0x00000648+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000144&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006318,"\x9d\x56\x68\xba\x60\xc1\x35\xad\xdb\x6c\x93\x7a\x2c\x95\x67\x34",16))
printf("strip: 9d5668ba60c135ad, Pass\n");
else
printf("strip: 9d5668ba60c135ad, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006314))=0x006a0802;
*((unsigned int *)((unsigned long)context_ptr+0x00006314+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006314+4*2))=0x02020045;
*((unsigned int *)((unsigned long)context_ptr+0x00006314+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x000060ec))=0x64337f1d;
*((unsigned int *)((unsigned long)context_ptr+0x000060ec+4*1))=0x76616f0b;
*((unsigned int *)((unsigned long)context_ptr+0x000060ec+4*2))=0x0553a4cf;
*((unsigned int *)((unsigned long)context_ptr+0x000060ec+4*3))=0x75e18124;
*((unsigned int *)((unsigned long)context_ptr+0x000060ec+4*4))=0xcc21816b;
*((unsigned int *)((unsigned long)context_ptr+0x000060ec+4*5))=0x11e9127d;
*((unsigned int *)((unsigned long)context_ptr+0x000060ec+4*6))=0x538b0007;
*((unsigned int *)((unsigned long)context_ptr+0x000060ec+4*7))=0x12780b10;
*((unsigned int *)((unsigned long)context_ptr+0x000060ec+4*8))=0x074fbe33;
*((unsigned int *)((unsigned long)context_ptr+0x000060ec+4*9))=0xc2a3eef5;
*((unsigned int *)((unsigned long)context_ptr+0x000060ec+4*10))=0xf9a058ed;
*((unsigned int *)((unsigned long)context_ptr+0x000060ec+4*11))=0xea73dc0f;
*((unsigned int *)((unsigned long)context_ptr+0x000060ec+4*12))=0xee840b60;
*((unsigned int *)((unsigned long)context_ptr+0x000060ec+4*13))=0x8dad3d8d;
*((unsigned int *)((unsigned long)context_ptr+0x000060ec+4*14))=0x02383d8d;
*((unsigned int *)((unsigned long)context_ptr+0x000060ec+4*15))=0x73e6c0f8;
*((unsigned int *)((unsigned long)context_ptr+0x000060ec+4*16))=0xdff9793c;
*((unsigned int *)((unsigned long)context_ptr+0x000060ec+4*17))=0x000000ba;
*((unsigned int *)((unsigned long)context_ptr+0x00003660))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003660+4*1))=0x00006134;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000660+4*2))=0x00006314;
*((unsigned int *)((unsigned long)context_ptr+0x00000660+4*3))=0x02220045;
*((unsigned int *)((unsigned long)context_ptr+0x00000660+4*4))=0x09298fe2;
*((unsigned int *)((unsigned long)context_ptr+0x00000660+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000014a&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006328,"\x2a\x5c\x48\x66\x9f\xe1\x68\x7e\x33\x3b\x81\xe3\x70\x13\x2e\x8a",16))
printf("strip: 2a5c48669fe1687e, Pass\n");
else
printf("strip: 2a5c48669fe1687e, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006324))=0x006a0802;
*((unsigned int *)((unsigned long)context_ptr+0x00006324+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006324+4*2))=0x02020046;
*((unsigned int *)((unsigned long)context_ptr+0x00006324+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x00006600))=0xbd9a48f2;
*((unsigned int *)((unsigned long)context_ptr+0x00006600+4*1))=0xa663c00c;
*((unsigned int *)((unsigned long)context_ptr+0x00006600+4*2))=0x0ea73164;
*((unsigned int *)((unsigned long)context_ptr+0x00006600+4*3))=0xac058692;
*((unsigned int *)((unsigned long)context_ptr+0x00006600+4*4))=0xa6893f7f;
*((unsigned int *)((unsigned long)context_ptr+0x00006600+4*5))=0xea38b59e;
*((unsigned int *)((unsigned long)context_ptr+0x00006600+4*6))=0x1698467f;
*((unsigned int *)((unsigned long)context_ptr+0x00006600+4*7))=0x1bd94104;
*((unsigned int *)((unsigned long)context_ptr+0x00006600+4*8))=0x3a93bf88;
*((unsigned int *)((unsigned long)context_ptr+0x00006600+4*9))=0x5a1e697d;
*((unsigned int *)((unsigned long)context_ptr+0x00006600+4*10))=0xd9270cfd;
*((unsigned int *)((unsigned long)context_ptr+0x00006600+4*11))=0xddd81bda;
*((unsigned int *)((unsigned long)context_ptr+0x00006600+4*12))=0x067e2c7c;
*((unsigned int *)((unsigned long)context_ptr+0x00006600+4*13))=0x965431c5;
*((unsigned int *)((unsigned long)context_ptr+0x00006600+4*14))=0x97623da7;
*((unsigned int *)((unsigned long)context_ptr+0x00006600+4*15))=0xa685db44;
*((unsigned int *)((unsigned long)context_ptr+0x00006600+4*16))=0x43d414da;
*((unsigned int *)((unsigned long)context_ptr+0x00006600+4*17))=0x0000ae35;
*((unsigned int *)((unsigned long)context_ptr+0x00003678))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003678+4*1))=0x000063dc;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000678+4*1))=0x00006600;
*((unsigned int *)((unsigned long)context_ptr+0x00000678+4*2))=0x00006324;
*((unsigned int *)((unsigned long)context_ptr+0x00000678+4*3))=0x02220046;
*((unsigned int *)((unsigned long)context_ptr+0x00000678+4*4))=0x0178ca75;
*((unsigned int *)((unsigned long)context_ptr+0x00000678+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000150&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006338,"\xee\xd3\xdb\x03\xdd\xc4\x07\xd3\x13\x6d\x48\xee\x73\x00\x14\x64",16))
printf("strip: eed3db03ddc407d3, Pass\n");
else
printf("strip: eed3db03ddc407d3, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006334))=0x006a0802;
*((unsigned int *)((unsigned long)context_ptr+0x00006334+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006334+4*2))=0x02020047;
*((unsigned int *)((unsigned long)context_ptr+0x00006334+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x00006144))=0xf60b051c;
*((unsigned int *)((unsigned long)context_ptr+0x00006144+4*1))=0x248ff5f1;
*((unsigned int *)((unsigned long)context_ptr+0x00006144+4*2))=0xf792d718;
*((unsigned int *)((unsigned long)context_ptr+0x00006144+4*3))=0x12c83c34;
*((unsigned int *)((unsigned long)context_ptr+0x00006144+4*4))=0xcaa737a8;
*((unsigned int *)((unsigned long)context_ptr+0x00006144+4*5))=0xb489dbe7;
*((unsigned int *)((unsigned long)context_ptr+0x00006144+4*6))=0x6f9caa59;
*((unsigned int *)((unsigned long)context_ptr+0x00006144+4*7))=0xd2ef7b61;
*((unsigned int *)((unsigned long)context_ptr+0x00006144+4*8))=0xfa66cd01;
*((unsigned int *)((unsigned long)context_ptr+0x00006144+4*9))=0x447dd921;
*((unsigned int *)((unsigned long)context_ptr+0x00006144+4*10))=0x6ac98fec;
*((unsigned int *)((unsigned long)context_ptr+0x00006144+4*11))=0x2d6ae053;
*((unsigned int *)((unsigned long)context_ptr+0x00006144+4*12))=0xace9bea7;
*((unsigned int *)((unsigned long)context_ptr+0x00006144+4*13))=0xd1963151;
*((unsigned int *)((unsigned long)context_ptr+0x00006144+4*14))=0x8fdac51b;
*((unsigned int *)((unsigned long)context_ptr+0x00006144+4*15))=0x4cbefca0;
*((unsigned int *)((unsigned long)context_ptr+0x00006144+4*16))=0xeb5c96cc;
*((unsigned int *)((unsigned long)context_ptr+0x00006144+4*17))=0x00f89756;
*((unsigned int *)((unsigned long)context_ptr+0x00003690))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003690+4*1))=0x0000618c;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000690+4*1))=0x00006144;
*((unsigned int *)((unsigned long)context_ptr+0x00000690+4*2))=0x00006334;
*((unsigned int *)((unsigned long)context_ptr+0x00000690+4*3))=0x02220047;
*((unsigned int *)((unsigned long)context_ptr+0x00000690+4*4))=0x05948f61;
*((unsigned int *)((unsigned long)context_ptr+0x00000690+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000156&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006348,"\x67\x9b\x37\x47\x63\x00\xc9\x62\x9c\xbb\x83\x87\xf4\x73\x10\x38",16))
printf("strip: 679b37476300c962, Pass\n");
else
printf("strip: 679b37476300c962, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006344))=0x006a0802;
*((unsigned int *)((unsigned long)context_ptr+0x00006344+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006344+4*2))=0x02020048;
*((unsigned int *)((unsigned long)context_ptr+0x00006344+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x000063ec))=0xb1316d48;
*((unsigned int *)((unsigned long)context_ptr+0x000063ec+4*1))=0x39f9a53d;
*((unsigned int *)((unsigned long)context_ptr+0x000063ec+4*2))=0x87156a05;
*((unsigned int *)((unsigned long)context_ptr+0x000063ec+4*3))=0x611943f3;
*((unsigned int *)((unsigned long)context_ptr+0x000063ec+4*4))=0x0372e1b5;
*((unsigned int *)((unsigned long)context_ptr+0x000063ec+4*5))=0x367f29ca;
*((unsigned int *)((unsigned long)context_ptr+0x000063ec+4*6))=0x7f25c75a;
*((unsigned int *)((unsigned long)context_ptr+0x000063ec+4*7))=0xaf532f7e;
*((unsigned int *)((unsigned long)context_ptr+0x000063ec+4*8))=0x7013d127;
*((unsigned int *)((unsigned long)context_ptr+0x000063ec+4*9))=0x72be6c88;
*((unsigned int *)((unsigned long)context_ptr+0x000063ec+4*10))=0x471bae89;
*((unsigned int *)((unsigned long)context_ptr+0x000063ec+4*11))=0x307fed94;
*((unsigned int *)((unsigned long)context_ptr+0x000063ec+4*12))=0x971f072f;
*((unsigned int *)((unsigned long)context_ptr+0x000063ec+4*13))=0x4c54281d;
*((unsigned int *)((unsigned long)context_ptr+0x000063ec+4*14))=0x578b1ce4;
*((unsigned int *)((unsigned long)context_ptr+0x000063ec+4*15))=0x5625e2a0;
*((unsigned int *)((unsigned long)context_ptr+0x000063ec+4*16))=0x01493fc5;
*((unsigned int *)((unsigned long)context_ptr+0x000063ec+4*17))=0xa39fc740;
*((unsigned int *)((unsigned long)context_ptr+0x000036a8))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x000036a8+4*1))=0x0000619c;
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
*((unsigned int *)((unsigned long)context_ptr+0x000006a8+4*1))=0x000063ec;
*((unsigned int *)((unsigned long)context_ptr+0x000006a8+4*2))=0x00006344;
*((unsigned int *)((unsigned long)context_ptr+0x000006a8+4*3))=0x02220048;
*((unsigned int *)((unsigned long)context_ptr+0x000006a8+4*4))=0x0f4d7d55;
*((unsigned int *)((unsigned long)context_ptr+0x000006a8+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000015c&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000061f8,"\x83\xe3\xb2\x59\xa1\xb6\x5f\x23\x33\xa5\x76\x53\xea\xa5\x49\x68",16))
printf("strip: 83e3b259a1b65f23, Pass\n");
else
printf("strip: 83e3b259a1b65f23, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006434))=0x006a0802;
*((unsigned int *)((unsigned long)context_ptr+0x00006434+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006434+4*2))=0x02020049;
*((unsigned int *)((unsigned long)context_ptr+0x00006434+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x000061ac))=0x9a0ed498;
*((unsigned int *)((unsigned long)context_ptr+0x000061ac+4*1))=0x5234e768;
*((unsigned int *)((unsigned long)context_ptr+0x000061ac+4*2))=0x7efd976f;
*((unsigned int *)((unsigned long)context_ptr+0x000061ac+4*3))=0x9e4792d2;
*((unsigned int *)((unsigned long)context_ptr+0x000061ac+4*4))=0x07b14820;
*((unsigned int *)((unsigned long)context_ptr+0x000061ac+4*5))=0xb28cffbd;
*((unsigned int *)((unsigned long)context_ptr+0x000061ac+4*6))=0xee240e5f;
*((unsigned int *)((unsigned long)context_ptr+0x000061ac+4*7))=0x0fcc1974;
*((unsigned int *)((unsigned long)context_ptr+0x000061ac+4*8))=0x2cea613a;
*((unsigned int *)((unsigned long)context_ptr+0x000061ac+4*9))=0xf05d82c3;
*((unsigned int *)((unsigned long)context_ptr+0x000061ac+4*10))=0x7da91207;
*((unsigned int *)((unsigned long)context_ptr+0x000061ac+4*11))=0x198b19bd;
*((unsigned int *)((unsigned long)context_ptr+0x000061ac+4*12))=0x29a65c7b;
*((unsigned int *)((unsigned long)context_ptr+0x000061ac+4*13))=0x7f34e986;
*((unsigned int *)((unsigned long)context_ptr+0x000061ac+4*14))=0x770fe56d;
*((unsigned int *)((unsigned long)context_ptr+0x000061ac+4*15))=0x127cfcfe;
*((unsigned int *)((unsigned long)context_ptr+0x000061ac+4*16))=0xdf1be762;
*((unsigned int *)((unsigned long)context_ptr+0x000061ac+4*17))=0x1f4d4cc3;
*((unsigned int *)((unsigned long)context_ptr+0x000061ac+4*18))=0x000000b8;
*((unsigned int *)((unsigned long)context_ptr+0x000036c0))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x000036c0+4*1))=0x000061f8;
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
*((unsigned int *)((unsigned long)context_ptr+0x000006c0+4*1))=0x000061ac;
*((unsigned int *)((unsigned long)context_ptr+0x000006c0+4*2))=0x00006434;
*((unsigned int *)((unsigned long)context_ptr+0x000006c0+4*3))=0x02220049;
*((unsigned int *)((unsigned long)context_ptr+0x000006c0+4*4))=0x06138cf8;
*((unsigned int *)((unsigned long)context_ptr+0x000006c0+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000162&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006244,"\x7b\xf6\x44\x55\x93\x56\x02\x15\x21\x93\xc2\x36\x80\x8f\xe7\x48",16))
printf("strip: 7bf6445593560215, Pass\n");
else
printf("strip: 7bf6445593560215, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006354))=0x006a0802;
*((unsigned int *)((unsigned long)context_ptr+0x00006354+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006354+4*2))=0x0202004a;
*((unsigned int *)((unsigned long)context_ptr+0x00006354+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x00006208))=0x93a3ebed;
*((unsigned int *)((unsigned long)context_ptr+0x00006208+4*1))=0x5246b1bf;
*((unsigned int *)((unsigned long)context_ptr+0x00006208+4*2))=0x02ed6d2a;
*((unsigned int *)((unsigned long)context_ptr+0x00006208+4*3))=0x5ab7ab25;
*((unsigned int *)((unsigned long)context_ptr+0x00006208+4*4))=0x92105c6d;
*((unsigned int *)((unsigned long)context_ptr+0x00006208+4*5))=0x7557fe59;
*((unsigned int *)((unsigned long)context_ptr+0x00006208+4*6))=0xbeb3bdfc;
*((unsigned int *)((unsigned long)context_ptr+0x00006208+4*7))=0xbb21d69f;
*((unsigned int *)((unsigned long)context_ptr+0x00006208+4*8))=0xbfdb8e60;
*((unsigned int *)((unsigned long)context_ptr+0x00006208+4*9))=0x066cf5a7;
*((unsigned int *)((unsigned long)context_ptr+0x00006208+4*10))=0xd49b68f6;
*((unsigned int *)((unsigned long)context_ptr+0x00006208+4*11))=0xbb3236c8;
*((unsigned int *)((unsigned long)context_ptr+0x00006208+4*12))=0xadbba069;
*((unsigned int *)((unsigned long)context_ptr+0x00006208+4*13))=0xf4a154bc;
*((unsigned int *)((unsigned long)context_ptr+0x00006208+4*14))=0x475ffa00;
*((unsigned int *)((unsigned long)context_ptr+0x00006208+4*15))=0xb3383baf;
*((unsigned int *)((unsigned long)context_ptr+0x00006208+4*16))=0x04e2a696;
*((unsigned int *)((unsigned long)context_ptr+0x00006208+4*17))=0x67d64a65;
*((unsigned int *)((unsigned long)context_ptr+0x00006208+4*18))=0x00009a5c;
*((unsigned int *)((unsigned long)context_ptr+0x000036d8))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x000036d8+4*1))=0x000064fc;
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
*((unsigned int *)((unsigned long)context_ptr+0x000006d8+4*1))=0x00006208;
*((unsigned int *)((unsigned long)context_ptr+0x000006d8+4*2))=0x00006354;
*((unsigned int *)((unsigned long)context_ptr+0x000006d8+4*3))=0x0222004a;
*((unsigned int *)((unsigned long)context_ptr+0x000006d8+4*4))=0x0c984fec;
*((unsigned int *)((unsigned long)context_ptr+0x000006d8+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000168&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006254,"\xfe\x0a\xe8\x98\x57\x74\x18\xe4\x93\xac\x2f\x24\x66\xd3\x06\xa5",16))
printf("strip: fe0ae898577418e4, Pass\n");
else
printf("strip: fe0ae898577418e4, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006254))=0x006a0802;
*((unsigned int *)((unsigned long)context_ptr+0x00006254+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006254+4*2))=0x0202004b;
*((unsigned int *)((unsigned long)context_ptr+0x00006254+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x0000650c))=0x9651505d;
*((unsigned int *)((unsigned long)context_ptr+0x0000650c+4*1))=0x947d860c;
*((unsigned int *)((unsigned long)context_ptr+0x0000650c+4*2))=0x7a53afee;
*((unsigned int *)((unsigned long)context_ptr+0x0000650c+4*3))=0x58a4ec81;
*((unsigned int *)((unsigned long)context_ptr+0x0000650c+4*4))=0x472b0be3;
*((unsigned int *)((unsigned long)context_ptr+0x0000650c+4*5))=0x953ee0f4;
*((unsigned int *)((unsigned long)context_ptr+0x0000650c+4*6))=0xba9fef49;
*((unsigned int *)((unsigned long)context_ptr+0x0000650c+4*7))=0x26edceee;
*((unsigned int *)((unsigned long)context_ptr+0x0000650c+4*8))=0xc4d8df42;
*((unsigned int *)((unsigned long)context_ptr+0x0000650c+4*9))=0x1979dab8;
*((unsigned int *)((unsigned long)context_ptr+0x0000650c+4*10))=0x8f9b3fba;
*((unsigned int *)((unsigned long)context_ptr+0x0000650c+4*11))=0x1862a763;
*((unsigned int *)((unsigned long)context_ptr+0x0000650c+4*12))=0x8f48d8dc;
*((unsigned int *)((unsigned long)context_ptr+0x0000650c+4*13))=0x6274bc22;
*((unsigned int *)((unsigned long)context_ptr+0x0000650c+4*14))=0xced7d3ee;
*((unsigned int *)((unsigned long)context_ptr+0x0000650c+4*15))=0xeb51e7ba;
*((unsigned int *)((unsigned long)context_ptr+0x0000650c+4*16))=0x7858c06a;
*((unsigned int *)((unsigned long)context_ptr+0x0000650c+4*17))=0x0d521d3f;
*((unsigned int *)((unsigned long)context_ptr+0x0000650c+4*18))=0x00135350;
*((unsigned int *)((unsigned long)context_ptr+0x000036f0))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x000036f0+4*1))=0x00006364;
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
*((unsigned int *)((unsigned long)context_ptr+0x000006f0+4*1))=0x0000650c;
*((unsigned int *)((unsigned long)context_ptr+0x000006f0+4*2))=0x00006254;
*((unsigned int *)((unsigned long)context_ptr+0x000006f0+4*3))=0x0222004b;
*((unsigned int *)((unsigned long)context_ptr+0x000006f0+4*4))=0x09c49814;
*((unsigned int *)((unsigned long)context_ptr+0x000006f0+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000016e&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006038,"\xd5\x18\x6b\xe9\x60\x54\x4a\x62\x7e\x7a\xa4\x60\x36\x69\xa3\xa7",16))
printf("strip: d5186be960544a62, Pass\n");
else
printf("strip: d5186be960544a62, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006038))=0x006a0802;
*((unsigned int *)((unsigned long)context_ptr+0x00006038+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006038+4*2))=0x0202004c;
*((unsigned int *)((unsigned long)context_ptr+0x00006038+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x00006648))=0xc5f44468;
*((unsigned int *)((unsigned long)context_ptr+0x00006648+4*1))=0x5a168b82;
*((unsigned int *)((unsigned long)context_ptr+0x00006648+4*2))=0xcd5811ca;
*((unsigned int *)((unsigned long)context_ptr+0x00006648+4*3))=0x1767ae80;
*((unsigned int *)((unsigned long)context_ptr+0x00006648+4*4))=0x099e82a7;
*((unsigned int *)((unsigned long)context_ptr+0x00006648+4*5))=0x82e3ed07;
*((unsigned int *)((unsigned long)context_ptr+0x00006648+4*6))=0xc8d51969;
*((unsigned int *)((unsigned long)context_ptr+0x00006648+4*7))=0xd57ecda8;
*((unsigned int *)((unsigned long)context_ptr+0x00006648+4*8))=0x8e8c112c;
*((unsigned int *)((unsigned long)context_ptr+0x00006648+4*9))=0x1e643a94;
*((unsigned int *)((unsigned long)context_ptr+0x00006648+4*10))=0xf7a6d8d0;
*((unsigned int *)((unsigned long)context_ptr+0x00006648+4*11))=0xe5ceefa0;
*((unsigned int *)((unsigned long)context_ptr+0x00006648+4*12))=0xa325185f;
*((unsigned int *)((unsigned long)context_ptr+0x00006648+4*13))=0xadca71ca;
*((unsigned int *)((unsigned long)context_ptr+0x00006648+4*14))=0x44333034;
*((unsigned int *)((unsigned long)context_ptr+0x00006648+4*15))=0x923c8b40;
*((unsigned int *)((unsigned long)context_ptr+0x00006648+4*16))=0xc3a9cc9f;
*((unsigned int *)((unsigned long)context_ptr+0x00006648+4*17))=0xa054077c;
*((unsigned int *)((unsigned long)context_ptr+0x00006648+4*18))=0x082eeb7b;
*((unsigned int *)((unsigned long)context_ptr+0x00003708))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003708+4*1))=0x00006374;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000708+4*1))=0x00006648;
*((unsigned int *)((unsigned long)context_ptr+0x00000708+4*2))=0x00006038;
*((unsigned int *)((unsigned long)context_ptr+0x00000708+4*3))=0x0222004c;
*((unsigned int *)((unsigned long)context_ptr+0x00000708+4*4))=0x0d8470ea;
*((unsigned int *)((unsigned long)context_ptr+0x00000708+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000174&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000062a4,"\x1a\x1b\x3a\x1e\xe6\x6f\x60\x46\x5d\x3d\xad\x33\x87\xa0\x5d\x36",16))
printf("strip: 1a1b3a1ee66f6046, Pass\n");
else
printf("strip: 1a1b3a1ee66f6046, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006028))=0x006a0802;
*((unsigned int *)((unsigned long)context_ptr+0x00006028+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006028+4*2))=0x0202004d;
*((unsigned int *)((unsigned long)context_ptr+0x00006028+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x00006264))=0x473a9753;
*((unsigned int *)((unsigned long)context_ptr+0x00006264+4*1))=0xd000e3c1;
*((unsigned int *)((unsigned long)context_ptr+0x00006264+4*2))=0x23acf9d7;
*((unsigned int *)((unsigned long)context_ptr+0x00006264+4*3))=0x82bee2f3;
*((unsigned int *)((unsigned long)context_ptr+0x00006264+4*4))=0x168193ad;
*((unsigned int *)((unsigned long)context_ptr+0x00006264+4*5))=0xd3756462;
*((unsigned int *)((unsigned long)context_ptr+0x00006264+4*6))=0x8e341b4c;
*((unsigned int *)((unsigned long)context_ptr+0x00006264+4*7))=0x8420f867;
*((unsigned int *)((unsigned long)context_ptr+0x00006264+4*8))=0xd3e449ce;
*((unsigned int *)((unsigned long)context_ptr+0x00006264+4*9))=0xc86dc26b;
*((unsigned int *)((unsigned long)context_ptr+0x00006264+4*10))=0x49689056;
*((unsigned int *)((unsigned long)context_ptr+0x00006264+4*11))=0x3cb76a74;
*((unsigned int *)((unsigned long)context_ptr+0x00006264+4*12))=0x65c0bff2;
*((unsigned int *)((unsigned long)context_ptr+0x00006264+4*13))=0x79e490e5;
*((unsigned int *)((unsigned long)context_ptr+0x00006264+4*14))=0x393544f6;
*((unsigned int *)((unsigned long)context_ptr+0x00006264+4*15))=0x9d0bc75c;
*((unsigned int *)((unsigned long)context_ptr+0x00006264+4*16))=0x654b7d4f;
*((unsigned int *)((unsigned long)context_ptr+0x00006264+4*17))=0x58bd1f6b;
*((unsigned int *)((unsigned long)context_ptr+0x00006264+4*18))=0xb937d118;
*((unsigned int *)((unsigned long)context_ptr+0x00006264+4*19))=0x00000098;
*((unsigned int *)((unsigned long)context_ptr+0x00003720))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003720+4*1))=0x00006558;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000720+4*1))=0x00006264;
*((unsigned int *)((unsigned long)context_ptr+0x00000720+4*2))=0x00006028;
*((unsigned int *)((unsigned long)context_ptr+0x00000720+4*3))=0x0222004d;
*((unsigned int *)((unsigned long)context_ptr+0x00000720+4*4))=0x0f869a17;
*((unsigned int *)((unsigned long)context_ptr+0x00000720+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000017a&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006048,"\xd5\x73\x6b\x8e\x22\x98\x39\x90\x35\x31\x18\xf8\x4b\x8c\x22\x2b",16))
printf("strip: d5736b8e22983990, Pass\n");
else
printf("strip: d5736b8e22983990, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006048))=0x006a0802;
*((unsigned int *)((unsigned long)context_ptr+0x00006048+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006048+4*2))=0x0202004e;
*((unsigned int *)((unsigned long)context_ptr+0x00006048+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x00006568))=0x820a818b;
*((unsigned int *)((unsigned long)context_ptr+0x00006568+4*1))=0x46be91c4;
*((unsigned int *)((unsigned long)context_ptr+0x00006568+4*2))=0x2302bc91;
*((unsigned int *)((unsigned long)context_ptr+0x00006568+4*3))=0x49baabda;
*((unsigned int *)((unsigned long)context_ptr+0x00006568+4*4))=0x1f037f70;
*((unsigned int *)((unsigned long)context_ptr+0x00006568+4*5))=0x093f0c2c;
*((unsigned int *)((unsigned long)context_ptr+0x00006568+4*6))=0x49803261;
*((unsigned int *)((unsigned long)context_ptr+0x00006568+4*7))=0x9dc99b88;
*((unsigned int *)((unsigned long)context_ptr+0x00006568+4*8))=0xe7e7ae67;
*((unsigned int *)((unsigned long)context_ptr+0x00006568+4*9))=0x949c1ea6;
*((unsigned int *)((unsigned long)context_ptr+0x00006568+4*10))=0xcf1990cc;
*((unsigned int *)((unsigned long)context_ptr+0x00006568+4*11))=0x695a9475;
*((unsigned int *)((unsigned long)context_ptr+0x00006568+4*12))=0xd288810b;
*((unsigned int *)((unsigned long)context_ptr+0x00006568+4*13))=0xdcf9315c;
*((unsigned int *)((unsigned long)context_ptr+0x00006568+4*14))=0x1e26f545;
*((unsigned int *)((unsigned long)context_ptr+0x00006568+4*15))=0xf70207d0;
*((unsigned int *)((unsigned long)context_ptr+0x00006568+4*16))=0x9245bc14;
*((unsigned int *)((unsigned long)context_ptr+0x00006568+4*17))=0x9d1a247a;
*((unsigned int *)((unsigned long)context_ptr+0x00006568+4*18))=0xcd2f8d36;
*((unsigned int *)((unsigned long)context_ptr+0x00006568+4*19))=0x0000e392;
*((unsigned int *)((unsigned long)context_ptr+0x00003738))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003738+4*1))=0x000062b4;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000738+4*1))=0x00006568;
*((unsigned int *)((unsigned long)context_ptr+0x00000738+4*2))=0x00006048;
*((unsigned int *)((unsigned long)context_ptr+0x00000738+4*3))=0x0222004e;
*((unsigned int *)((unsigned long)context_ptr+0x00000738+4*4))=0x0f5d2e1e;
*((unsigned int *)((unsigned long)context_ptr+0x00000738+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000180&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000062c4,"\xc9\xa9\x03\x9e\xc5\xec\xca\x27\xcf\xfc\xfe\x89\x9e\x40\xf5\x6c",16))
printf("strip: c9a9039ec5ecca27, Pass\n");
else
printf("strip: c9a9039ec5ecca27, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000062c4))=0x006a0802;
*((unsigned int *)((unsigned long)context_ptr+0x000062c4+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000062c4+4*2))=0x0202004f;
*((unsigned int *)((unsigned long)context_ptr+0x000062c4+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x00006444))=0xbacd2988;
*((unsigned int *)((unsigned long)context_ptr+0x00006444+4*1))=0xa2c77a06;
*((unsigned int *)((unsigned long)context_ptr+0x00006444+4*2))=0xb26bea95;
*((unsigned int *)((unsigned long)context_ptr+0x00006444+4*3))=0x296607d9;
*((unsigned int *)((unsigned long)context_ptr+0x00006444+4*4))=0x0ecb86e7;
*((unsigned int *)((unsigned long)context_ptr+0x00006444+4*5))=0x4a7b2b94;
*((unsigned int *)((unsigned long)context_ptr+0x00006444+4*6))=0x06951e8c;
*((unsigned int *)((unsigned long)context_ptr+0x00006444+4*7))=0xc22ef39b;
*((unsigned int *)((unsigned long)context_ptr+0x00006444+4*8))=0x98d7abca;
*((unsigned int *)((unsigned long)context_ptr+0x00006444+4*9))=0xb6ea52b7;
*((unsigned int *)((unsigned long)context_ptr+0x00006444+4*10))=0x9aae57a8;
*((unsigned int *)((unsigned long)context_ptr+0x00006444+4*11))=0x6fe08e70;
*((unsigned int *)((unsigned long)context_ptr+0x00006444+4*12))=0xd818a955;
*((unsigned int *)((unsigned long)context_ptr+0x00006444+4*13))=0xc5deb5e5;
*((unsigned int *)((unsigned long)context_ptr+0x00006444+4*14))=0xba8ca432;
*((unsigned int *)((unsigned long)context_ptr+0x00006444+4*15))=0x2c5ac573;
*((unsigned int *)((unsigned long)context_ptr+0x00006444+4*16))=0xdcc23b09;
*((unsigned int *)((unsigned long)context_ptr+0x00006444+4*17))=0x74da56b6;
*((unsigned int *)((unsigned long)context_ptr+0x00006444+4*18))=0x3117c5f6;
*((unsigned int *)((unsigned long)context_ptr+0x00006444+4*19))=0x00122cf6;
*((unsigned int *)((unsigned long)context_ptr+0x00003750))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003750+4*1))=0x00006058;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000750+4*1))=0x00006444;
*((unsigned int *)((unsigned long)context_ptr+0x00000750+4*2))=0x000062c4;
*((unsigned int *)((unsigned long)context_ptr+0x00000750+4*3))=0x0222004f;
*((unsigned int *)((unsigned long)context_ptr+0x00000750+4*4))=0x080e1396;
*((unsigned int *)((unsigned long)context_ptr+0x00000750+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000186&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000062d4,"\xfe\x37\x1e\xee\x48\xe0\xee\xe6\x9a\x60\x50\x5f\x7c\x4a\xa5\x34",16))
printf("strip: fe371eee48e0eee6, Pass\n");
else
printf("strip: fe371eee48e0eee6, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000062d4))=0x006a0802;
*((unsigned int *)((unsigned long)context_ptr+0x000062d4+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000062d4+4*2))=0x02020050;
*((unsigned int *)((unsigned long)context_ptr+0x000062d4+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x00006694))=0xa4a82b0e;
*((unsigned int *)((unsigned long)context_ptr+0x00006694+4*1))=0x44305e1f;
*((unsigned int *)((unsigned long)context_ptr+0x00006694+4*2))=0xfe12c828;
*((unsigned int *)((unsigned long)context_ptr+0x00006694+4*3))=0x5bfe4b77;
*((unsigned int *)((unsigned long)context_ptr+0x00006694+4*4))=0x15ba3847;
*((unsigned int *)((unsigned long)context_ptr+0x00006694+4*5))=0x73de623c;
*((unsigned int *)((unsigned long)context_ptr+0x00006694+4*6))=0x4dd7ca13;
*((unsigned int *)((unsigned long)context_ptr+0x00006694+4*7))=0xbad7a28c;
*((unsigned int *)((unsigned long)context_ptr+0x00006694+4*8))=0xbbbb7e9c;
*((unsigned int *)((unsigned long)context_ptr+0x00006694+4*9))=0x3a2ca6c0;
*((unsigned int *)((unsigned long)context_ptr+0x00006694+4*10))=0x51c918e5;
*((unsigned int *)((unsigned long)context_ptr+0x00006694+4*11))=0xd46ef52b;
*((unsigned int *)((unsigned long)context_ptr+0x00006694+4*12))=0x0ddb6527;
*((unsigned int *)((unsigned long)context_ptr+0x00006694+4*13))=0x9f2efc86;
*((unsigned int *)((unsigned long)context_ptr+0x00006694+4*14))=0x54f9a9b0;
*((unsigned int *)((unsigned long)context_ptr+0x00006694+4*15))=0xe92c3b5a;
*((unsigned int *)((unsigned long)context_ptr+0x00006694+4*16))=0x3e179bd3;
*((unsigned int *)((unsigned long)context_ptr+0x00006694+4*17))=0xac4a8633;
*((unsigned int *)((unsigned long)context_ptr+0x00006694+4*18))=0xbf493569;
*((unsigned int *)((unsigned long)context_ptr+0x00006694+4*19))=0x053f2f78;
*((unsigned int *)((unsigned long)context_ptr+0x00003768))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003768+4*1))=0x00006068;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000768+4*1))=0x00006694;
*((unsigned int *)((unsigned long)context_ptr+0x00000768+4*2))=0x000062d4;
*((unsigned int *)((unsigned long)context_ptr+0x00000768+4*3))=0x02220050;
*((unsigned int *)((unsigned long)context_ptr+0x00000768+4*4))=0x089cd470;
*((unsigned int *)((unsigned long)context_ptr+0x00000768+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000018c&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006498,"\xdf\xb1\x8a\x56\x25\xcd\x7e\x9e\x66\xd7\x85\x0a\xbe\x5f\x0d\xad",16))
printf("strip: dfb18a5625cd7e9e, Pass\n");
else
printf("strip: dfb18a5625cd7e9e, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000062e4))=0x006a0802;
*((unsigned int *)((unsigned long)context_ptr+0x000062e4+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000062e4+4*2))=0x02020051;
*((unsigned int *)((unsigned long)context_ptr+0x000062e4+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x000066e4))=0x05f8af83;
*((unsigned int *)((unsigned long)context_ptr+0x000066e4+4*1))=0x42b4c3c5;
*((unsigned int *)((unsigned long)context_ptr+0x000066e4+4*2))=0xc301b51b;
*((unsigned int *)((unsigned long)context_ptr+0x000066e4+4*3))=0x503a2bde;
*((unsigned int *)((unsigned long)context_ptr+0x000066e4+4*4))=0x51c6f961;
*((unsigned int *)((unsigned long)context_ptr+0x000066e4+4*5))=0x075f483f;
*((unsigned int *)((unsigned long)context_ptr+0x000066e4+4*6))=0x563864cf;
*((unsigned int *)((unsigned long)context_ptr+0x000066e4+4*7))=0xea5c5d1e;
*((unsigned int *)((unsigned long)context_ptr+0x000066e4+4*8))=0x7f3e6795;
*((unsigned int *)((unsigned long)context_ptr+0x000066e4+4*9))=0xe157a80a;
*((unsigned int *)((unsigned long)context_ptr+0x000066e4+4*10))=0x195f0fe8;
*((unsigned int *)((unsigned long)context_ptr+0x000066e4+4*11))=0xb5c0d7b8;
*((unsigned int *)((unsigned long)context_ptr+0x000066e4+4*12))=0x5f35c14a;
*((unsigned int *)((unsigned long)context_ptr+0x000066e4+4*13))=0x19cedff8;
*((unsigned int *)((unsigned long)context_ptr+0x000066e4+4*14))=0x25d2aa6c;
*((unsigned int *)((unsigned long)context_ptr+0x000066e4+4*15))=0x04a2f6c9;
*((unsigned int *)((unsigned long)context_ptr+0x000066e4+4*16))=0x231344c5;
*((unsigned int *)((unsigned long)context_ptr+0x000066e4+4*17))=0x61092944;
*((unsigned int *)((unsigned long)context_ptr+0x000066e4+4*18))=0x05c56211;
*((unsigned int *)((unsigned long)context_ptr+0x000066e4+4*19))=0x92de43be;
*((unsigned int *)((unsigned long)context_ptr+0x000066e4+4*20))=0x00000092;
*((unsigned int *)((unsigned long)context_ptr+0x00003780))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003780+4*1))=0x00006494;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000780+4*1))=0x000066e4;
*((unsigned int *)((unsigned long)context_ptr+0x00000780+4*2))=0x000062e4;
*((unsigned int *)((unsigned long)context_ptr+0x00000780+4*3))=0x02220051;
*((unsigned int *)((unsigned long)context_ptr+0x00000780+4*4))=0x06ee4fa2;
*((unsigned int *)((unsigned long)context_ptr+0x00000780+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000192&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000063cc,"\x4e\x0c\x6d\x2a\xd3\xf0\x1c\x94\xc8\x5b\xe7\x94\x7b\x47\x1a\x07",16))
printf("strip: 4e0c6d2ad3f01c94, Pass\n");
else
printf("strip: 4e0c6d2ad3f01c94, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000062f4))=0x006a0802;
*((unsigned int *)((unsigned long)context_ptr+0x000062f4+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000062f4+4*2))=0x02020052;
*((unsigned int *)((unsigned long)context_ptr+0x000062f4+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x00006384))=0xbce02c79;
*((unsigned int *)((unsigned long)context_ptr+0x00006384+4*1))=0xa227d963;
*((unsigned int *)((unsigned long)context_ptr+0x00006384+4*2))=0x4b11330c;
*((unsigned int *)((unsigned long)context_ptr+0x00006384+4*3))=0x34708277;
*((unsigned int *)((unsigned long)context_ptr+0x00006384+4*4))=0x84206067;
*((unsigned int *)((unsigned long)context_ptr+0x00006384+4*5))=0x637d2f61;
*((unsigned int *)((unsigned long)context_ptr+0x00006384+4*6))=0x7b8a6840;
*((unsigned int *)((unsigned long)context_ptr+0x00006384+4*7))=0xac81dd2d;
*((unsigned int *)((unsigned long)context_ptr+0x00006384+4*8))=0x234d6c70;
*((unsigned int *)((unsigned long)context_ptr+0x00006384+4*9))=0xc207ff89;
*((unsigned int *)((unsigned long)context_ptr+0x00006384+4*10))=0x3b829784;
*((unsigned int *)((unsigned long)context_ptr+0x00006384+4*11))=0x978b77b7;
*((unsigned int *)((unsigned long)context_ptr+0x00006384+4*12))=0xb7c60b91;
*((unsigned int *)((unsigned long)context_ptr+0x00006384+4*13))=0x6ead3828;
*((unsigned int *)((unsigned long)context_ptr+0x00006384+4*14))=0xca9c09fe;
*((unsigned int *)((unsigned long)context_ptr+0x00006384+4*15))=0x513ef34f;
*((unsigned int *)((unsigned long)context_ptr+0x00006384+4*16))=0xb2a51267;
*((unsigned int *)((unsigned long)context_ptr+0x00006384+4*17))=0x975316c8;
*((unsigned int *)((unsigned long)context_ptr+0x00006384+4*18))=0xde77a788;
*((unsigned int *)((unsigned long)context_ptr+0x00006384+4*19))=0x230cc7ec;
*((unsigned int *)((unsigned long)context_ptr+0x00006384+4*20))=0x0000e42d;
*((unsigned int *)((unsigned long)context_ptr+0x00003798))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003798+4*1))=0x000065b8;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000798+4*1))=0x00006384;
*((unsigned int *)((unsigned long)context_ptr+0x00000798+4*2))=0x000062f4;
*((unsigned int *)((unsigned long)context_ptr+0x00000798+4*3))=0x02220052;
*((unsigned int *)((unsigned long)context_ptr+0x00000798+4*4))=0x0f691239;
*((unsigned int *)((unsigned long)context_ptr+0x00000798+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000198&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000064ec,"\xfe\x26\x55\xa8\xb6\x3a\x36\x6a\xd5\x01\xd5\xd7\x03\xb2\xbb\xcf",16))
printf("strip: fe2655a8b63a366a, Pass\n");
else
printf("strip: fe2655a8b63a366a, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006304))=0x006a0802;
*((unsigned int *)((unsigned long)context_ptr+0x00006304+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006304+4*2))=0x02020053;
*((unsigned int *)((unsigned long)context_ptr+0x00006304+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x000064a4))=0x2e710f98;
*((unsigned int *)((unsigned long)context_ptr+0x000064a4+4*1))=0xadcd433f;
*((unsigned int *)((unsigned long)context_ptr+0x000064a4+4*2))=0xd640efa1;
*((unsigned int *)((unsigned long)context_ptr+0x000064a4+4*3))=0x9eaaf478;
*((unsigned int *)((unsigned long)context_ptr+0x000064a4+4*4))=0xdce056c2;
*((unsigned int *)((unsigned long)context_ptr+0x000064a4+4*5))=0x0404b4c9;
*((unsigned int *)((unsigned long)context_ptr+0x000064a4+4*6))=0x259e3ad5;
*((unsigned int *)((unsigned long)context_ptr+0x000064a4+4*7))=0x9b577c2d;
*((unsigned int *)((unsigned long)context_ptr+0x000064a4+4*8))=0xb94d795a;
*((unsigned int *)((unsigned long)context_ptr+0x000064a4+4*9))=0x37800608;
*((unsigned int *)((unsigned long)context_ptr+0x000064a4+4*10))=0x692182a8;
*((unsigned int *)((unsigned long)context_ptr+0x000064a4+4*11))=0x27a865d0;
*((unsigned int *)((unsigned long)context_ptr+0x000064a4+4*12))=0x9f319930;
*((unsigned int *)((unsigned long)context_ptr+0x000064a4+4*13))=0xc20389d8;
*((unsigned int *)((unsigned long)context_ptr+0x000064a4+4*14))=0x28496846;
*((unsigned int *)((unsigned long)context_ptr+0x000064a4+4*15))=0x5f0abca5;
*((unsigned int *)((unsigned long)context_ptr+0x000064a4+4*16))=0x03f9d6bc;
*((unsigned int *)((unsigned long)context_ptr+0x000064a4+4*17))=0xf30e081c;
*((unsigned int *)((unsigned long)context_ptr+0x000064a4+4*18))=0x9e451539;
*((unsigned int *)((unsigned long)context_ptr+0x000064a4+4*19))=0xc4e3e2e9;
*((unsigned int *)((unsigned long)context_ptr+0x000064a4+4*20))=0x007a36ca;
*((unsigned int *)((unsigned long)context_ptr+0x000037b0))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x000037b0+4*1))=0x000065c8;
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
*((unsigned int *)((unsigned long)context_ptr+0x000007b0+4*1))=0x000064a4;
*((unsigned int *)((unsigned long)context_ptr+0x000007b0+4*2))=0x00006304;
*((unsigned int *)((unsigned long)context_ptr+0x000007b0+4*3))=0x02220053;
*((unsigned int *)((unsigned long)context_ptr+0x000007b0+4*4))=0x06fc6d18;
*((unsigned int *)((unsigned long)context_ptr+0x000007b0+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000019e&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006134,"\xd9\x7d\x29\xd7\x56\xc4\x0f\x16\x06\x20\xe0\x16\x20\x56\xdb\x8d",16))
printf("strip: d97d29d756c40f16, Pass\n");
else
printf("strip: d97d29d756c40f16, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006314))=0x006a0802;
*((unsigned int *)((unsigned long)context_ptr+0x00006314+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006314+4*2))=0x02020054;
*((unsigned int *)((unsigned long)context_ptr+0x00006314+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x00006078))=0x32ff05f3;
*((unsigned int *)((unsigned long)context_ptr+0x00006078+4*1))=0xbc794f40;
*((unsigned int *)((unsigned long)context_ptr+0x00006078+4*2))=0x0263d148;
*((unsigned int *)((unsigned long)context_ptr+0x00006078+4*3))=0x0ac47dc3;
*((unsigned int *)((unsigned long)context_ptr+0x00006078+4*4))=0x81ea9365;
*((unsigned int *)((unsigned long)context_ptr+0x00006078+4*5))=0x517692ee;
*((unsigned int *)((unsigned long)context_ptr+0x00006078+4*6))=0x5405c5c1;
*((unsigned int *)((unsigned long)context_ptr+0x00006078+4*7))=0x568c3a50;
*((unsigned int *)((unsigned long)context_ptr+0x00006078+4*8))=0x5526c028;
*((unsigned int *)((unsigned long)context_ptr+0x00006078+4*9))=0x6d59c6e4;
*((unsigned int *)((unsigned long)context_ptr+0x00006078+4*10))=0xc5fab35d;
*((unsigned int *)((unsigned long)context_ptr+0x00006078+4*11))=0xf2600a00;
*((unsigned int *)((unsigned long)context_ptr+0x00006078+4*12))=0x83d66294;
*((unsigned int *)((unsigned long)context_ptr+0x00006078+4*13))=0xb03d8cbf;
*((unsigned int *)((unsigned long)context_ptr+0x00006078+4*14))=0x029c1e34;
*((unsigned int *)((unsigned long)context_ptr+0x00006078+4*15))=0x68654376;
*((unsigned int *)((unsigned long)context_ptr+0x00006078+4*16))=0x4387176d;
*((unsigned int *)((unsigned long)context_ptr+0x00006078+4*17))=0x9ed917e9;
*((unsigned int *)((unsigned long)context_ptr+0x00006078+4*18))=0x8f8a8959;
*((unsigned int *)((unsigned long)context_ptr+0x00006078+4*19))=0xbc1190e2;
*((unsigned int *)((unsigned long)context_ptr+0x00006078+4*20))=0x2a7fc815;
*((unsigned int *)((unsigned long)context_ptr+0x000037c8))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x000037c8+4*1))=0x000065d8;
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
*((unsigned int *)((unsigned long)context_ptr+0x000007c8+4*1))=0x00006078;
*((unsigned int *)((unsigned long)context_ptr+0x000007c8+4*2))=0x00006314;
*((unsigned int *)((unsigned long)context_ptr+0x000007c8+4*3))=0x02220054;
*((unsigned int *)((unsigned long)context_ptr+0x000007c8+4*4))=0x0d62ccc2;
*((unsigned int *)((unsigned long)context_ptr+0x000007c8+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000001a4&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000063dc,"\x31\xe3\x3a\x4b\x16\x35\x0b\x56\xa5\x31\x18\x04\xa4\x95\x49\x9d",16))
printf("strip: 31e33a4b16350b56, Pass\n");
else
printf("strip: 31e33a4b16350b56, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006324))=0x006a0802;
*((unsigned int *)((unsigned long)context_ptr+0x00006324+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006324+4*2))=0x02020055;
*((unsigned int *)((unsigned long)context_ptr+0x00006324+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x000065e8))=0xbad4e26f;
*((unsigned int *)((unsigned long)context_ptr+0x000065e8+4*1))=0x319da6b2;
*((unsigned int *)((unsigned long)context_ptr+0x000065e8+4*2))=0x26f63b1a;
*((unsigned int *)((unsigned long)context_ptr+0x000065e8+4*3))=0x8f6b3dc5;
*((unsigned int *)((unsigned long)context_ptr+0x000065e8+4*4))=0x6af4e66a;
*((unsigned int *)((unsigned long)context_ptr+0x000065e8+4*5))=0xfa6e9679;
*((unsigned int *)((unsigned long)context_ptr+0x000065e8+4*6))=0x152d9ca1;
*((unsigned int *)((unsigned long)context_ptr+0x000065e8+4*7))=0x4a30440c;
*((unsigned int *)((unsigned long)context_ptr+0x000065e8+4*8))=0xb4ecb397;
*((unsigned int *)((unsigned long)context_ptr+0x000065e8+4*9))=0xd2da4aa1;
*((unsigned int *)((unsigned long)context_ptr+0x000065e8+4*10))=0xcbbbbbc4;
*((unsigned int *)((unsigned long)context_ptr+0x000065e8+4*11))=0xf3494390;
*((unsigned int *)((unsigned long)context_ptr+0x000065e8+4*12))=0x8c09762a;
*((unsigned int *)((unsigned long)context_ptr+0x000065e8+4*13))=0x4d08477c;
*((unsigned int *)((unsigned long)context_ptr+0x000065e8+4*14))=0x1c07c58e;
*((unsigned int *)((unsigned long)context_ptr+0x000065e8+4*15))=0xb6cccd75;
*((unsigned int *)((unsigned long)context_ptr+0x000065e8+4*16))=0x0d9cf14f;
*((unsigned int *)((unsigned long)context_ptr+0x000065e8+4*17))=0xe50b7e46;
*((unsigned int *)((unsigned long)context_ptr+0x000065e8+4*18))=0x4106876c;
*((unsigned int *)((unsigned long)context_ptr+0x000065e8+4*19))=0xae83945d;
*((unsigned int *)((unsigned long)context_ptr+0x000065e8+4*20))=0x9a63852d;
*((unsigned int *)((unsigned long)context_ptr+0x000065e8+4*21))=0x000000ba;
*((unsigned int *)((unsigned long)context_ptr+0x000037e0))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x000037e0+4*1))=0x000063d8;
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
*((unsigned int *)((unsigned long)context_ptr+0x000007e0+4*1))=0x000065e8;
*((unsigned int *)((unsigned long)context_ptr+0x000007e0+4*2))=0x00006324;
*((unsigned int *)((unsigned long)context_ptr+0x000007e0+4*3))=0x02220055;
*((unsigned int *)((unsigned long)context_ptr+0x000007e0+4*4))=0x08faa952;
*((unsigned int *)((unsigned long)context_ptr+0x000007e0+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000001aa&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x0000618c,"\x79\x72\x95\xc3\xc8\x99\xc3\xdb\xf6\x15\x57\x9f\x6d\x35\x71\x20",16))
printf("strip: 797295c3c899c3db, Pass\n");
else
printf("strip: 797295c3c899c3db, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006334))=0x006a0802;
*((unsigned int *)((unsigned long)context_ptr+0x00006334+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006334+4*2))=0x02020056;
*((unsigned int *)((unsigned long)context_ptr+0x00006334+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x000060cc))=0x470f49a8;
*((unsigned int *)((unsigned long)context_ptr+0x000060cc+4*1))=0xe490d0f6;
*((unsigned int *)((unsigned long)context_ptr+0x000060cc+4*2))=0x7f691595;
*((unsigned int *)((unsigned long)context_ptr+0x000060cc+4*3))=0x1a47b85e;
*((unsigned int *)((unsigned long)context_ptr+0x000060cc+4*4))=0xb1944e29;
*((unsigned int *)((unsigned long)context_ptr+0x000060cc+4*5))=0x87ce8d02;
*((unsigned int *)((unsigned long)context_ptr+0x000060cc+4*6))=0xf0edf46c;
*((unsigned int *)((unsigned long)context_ptr+0x000060cc+4*7))=0xed711e9e;
*((unsigned int *)((unsigned long)context_ptr+0x000060cc+4*8))=0x4ddc8cbd;
*((unsigned int *)((unsigned long)context_ptr+0x000060cc+4*9))=0x9bb9b4a3;
*((unsigned int *)((unsigned long)context_ptr+0x000060cc+4*10))=0x42536867;
*((unsigned int *)((unsigned long)context_ptr+0x000060cc+4*11))=0x925bada0;
*((unsigned int *)((unsigned long)context_ptr+0x000060cc+4*12))=0xc0f83357;
*((unsigned int *)((unsigned long)context_ptr+0x000060cc+4*13))=0x5fac01b2;
*((unsigned int *)((unsigned long)context_ptr+0x000060cc+4*14))=0x263fee81;
*((unsigned int *)((unsigned long)context_ptr+0x000060cc+4*15))=0x661688b4;
*((unsigned int *)((unsigned long)context_ptr+0x000060cc+4*16))=0x7fe265e2;
*((unsigned int *)((unsigned long)context_ptr+0x000060cc+4*17))=0x46c4b3dd;
*((unsigned int *)((unsigned long)context_ptr+0x000060cc+4*18))=0xd3e9fbe5;
*((unsigned int *)((unsigned long)context_ptr+0x000060cc+4*19))=0xfabd1cd8;
*((unsigned int *)((unsigned long)context_ptr+0x000060cc+4*20))=0xb75d2d92;
*((unsigned int *)((unsigned long)context_ptr+0x000060cc+4*21))=0x00002a99;
*((unsigned int *)((unsigned long)context_ptr+0x000037f8))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x000037f8+4*1))=0x00006124;
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
*((unsigned int *)((unsigned long)context_ptr+0x000007f8+4*1))=0x000060cc;
*((unsigned int *)((unsigned long)context_ptr+0x000007f8+4*2))=0x00006334;
*((unsigned int *)((unsigned long)context_ptr+0x000007f8+4*3))=0x02220056;
*((unsigned int *)((unsigned long)context_ptr+0x000007f8+4*4))=0x0c39a51d;
*((unsigned int *)((unsigned long)context_ptr+0x000007f8+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000001b0&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x0000619c,"\x92\x2c\x89\x50\x4a\x70\x17\x41\x53\x38\xbc\x70\x99\xa5\x15\x62",16))
printf("strip: 922c89504a701741, Pass\n");
else
printf("strip: 922c89504a701741, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006344))=0x006a0802;
*((unsigned int *)((unsigned long)context_ptr+0x00006344+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006344+4*2))=0x02020057;
*((unsigned int *)((unsigned long)context_ptr+0x00006344+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x00006134))=0xc8635955;
*((unsigned int *)((unsigned long)context_ptr+0x00006134+4*1))=0x7dffe545;
*((unsigned int *)((unsigned long)context_ptr+0x00006134+4*2))=0x9d2e93ca;
*((unsigned int *)((unsigned long)context_ptr+0x00006134+4*3))=0x2b41e401;
*((unsigned int *)((unsigned long)context_ptr+0x00006134+4*4))=0xf592c5ff;
*((unsigned int *)((unsigned long)context_ptr+0x00006134+4*5))=0xcb2ac6dd;
*((unsigned int *)((unsigned long)context_ptr+0x00006134+4*6))=0xdd44491d;
*((unsigned int *)((unsigned long)context_ptr+0x00006134+4*7))=0x932135b9;
*((unsigned int *)((unsigned long)context_ptr+0x00006134+4*8))=0x43f038af;
*((unsigned int *)((unsigned long)context_ptr+0x00006134+4*9))=0xdb5072d5;
*((unsigned int *)((unsigned long)context_ptr+0x00006134+4*10))=0x4e8c7af8;
*((unsigned int *)((unsigned long)context_ptr+0x00006134+4*11))=0xe9aa409e;
*((unsigned int *)((unsigned long)context_ptr+0x00006134+4*12))=0x0fc9e688;
*((unsigned int *)((unsigned long)context_ptr+0x00006134+4*13))=0x7a76bde0;
*((unsigned int *)((unsigned long)context_ptr+0x00006134+4*14))=0x934a57c7;
*((unsigned int *)((unsigned long)context_ptr+0x00006134+4*15))=0x220c6a04;
*((unsigned int *)((unsigned long)context_ptr+0x00006134+4*16))=0xdd349fc8;
*((unsigned int *)((unsigned long)context_ptr+0x00006134+4*17))=0x597b418b;
*((unsigned int *)((unsigned long)context_ptr+0x00006134+4*18))=0x6aa8ff9e;
*((unsigned int *)((unsigned long)context_ptr+0x00006134+4*19))=0xb2af8c8f;
*((unsigned int *)((unsigned long)context_ptr+0x00006134+4*20))=0x4193788a;
*((unsigned int *)((unsigned long)context_ptr+0x00006134+4*21))=0x006f1e68;
*((unsigned int *)((unsigned long)context_ptr+0x00003810))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003810+4*1))=0x0000618c;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000810+4*1))=0x00006134;
*((unsigned int *)((unsigned long)context_ptr+0x00000810+4*2))=0x00006344;
*((unsigned int *)((unsigned long)context_ptr+0x00000810+4*3))=0x02220057;
*((unsigned int *)((unsigned long)context_ptr+0x00000810+4*4))=0x08a40c09;
*((unsigned int *)((unsigned long)context_ptr+0x00000810+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000001b6&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000061f8,"\xf4\x67\x12\x5c\x11\x27\xb5\x39\x82\xd0\x66\x9c\x17\x8a\xeb\x79",16))
printf("strip: f467125c1127b539, Pass\n");
else
printf("strip: f467125c1127b539, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000063e8))=0x006a0802;
*((unsigned int *)((unsigned long)context_ptr+0x000063e8+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000063e8+4*2))=0x02020058;
*((unsigned int *)((unsigned long)context_ptr+0x000063e8+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x0000619c))=0x7ff37fa8;
*((unsigned int *)((unsigned long)context_ptr+0x0000619c+4*1))=0x326b8f86;
*((unsigned int *)((unsigned long)context_ptr+0x0000619c+4*2))=0x6314c44a;
*((unsigned int *)((unsigned long)context_ptr+0x0000619c+4*3))=0x040df304;
*((unsigned int *)((unsigned long)context_ptr+0x0000619c+4*4))=0x0c4ba0da;
*((unsigned int *)((unsigned long)context_ptr+0x0000619c+4*5))=0xb0ccb939;
*((unsigned int *)((unsigned long)context_ptr+0x0000619c+4*6))=0x4ed3cd0e;
*((unsigned int *)((unsigned long)context_ptr+0x0000619c+4*7))=0xe45abb3f;
*((unsigned int *)((unsigned long)context_ptr+0x0000619c+4*8))=0x90a37a9e;
*((unsigned int *)((unsigned long)context_ptr+0x0000619c+4*9))=0x42ef74d6;
*((unsigned int *)((unsigned long)context_ptr+0x0000619c+4*10))=0x8459f119;
*((unsigned int *)((unsigned long)context_ptr+0x0000619c+4*11))=0x8f9c5f4a;
*((unsigned int *)((unsigned long)context_ptr+0x0000619c+4*12))=0x16a09286;
*((unsigned int *)((unsigned long)context_ptr+0x0000619c+4*13))=0x6b7f38d6;
*((unsigned int *)((unsigned long)context_ptr+0x0000619c+4*14))=0x0b46f634;
*((unsigned int *)((unsigned long)context_ptr+0x0000619c+4*15))=0x832a5b1e;
*((unsigned int *)((unsigned long)context_ptr+0x0000619c+4*16))=0x08fd53f9;
*((unsigned int *)((unsigned long)context_ptr+0x0000619c+4*17))=0xabeebe85;
*((unsigned int *)((unsigned long)context_ptr+0x0000619c+4*18))=0xbc771ce4;
*((unsigned int *)((unsigned long)context_ptr+0x0000619c+4*19))=0x98dc5389;
*((unsigned int *)((unsigned long)context_ptr+0x0000619c+4*20))=0x6bc87508;
*((unsigned int *)((unsigned long)context_ptr+0x0000619c+4*21))=0x3d8d7c2a;
*((unsigned int *)((unsigned long)context_ptr+0x00003828))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003828+4*1))=0x000061f4;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000828+4*1))=0x0000619c;
*((unsigned int *)((unsigned long)context_ptr+0x00000828+4*2))=0x000063e8;
*((unsigned int *)((unsigned long)context_ptr+0x00000828+4*3))=0x02220058;
*((unsigned int *)((unsigned long)context_ptr+0x00000828+4*4))=0x0f409ec6;
*((unsigned int *)((unsigned long)context_ptr+0x00000828+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000001bc&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000064fc,"\xce\xbe\x89\x69\xab\xe9\xf1\x28\x8f\x57\x15\xbe\xb4\xb3\x48\x0b",16))
printf("strip: cebe8969abe9f128, Pass\n");
else
printf("strip: cebe8969abe9f128, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006354))=0x006a0802;
*((unsigned int *)((unsigned long)context_ptr+0x00006354+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006354+4*2))=0x02020059;
*((unsigned int *)((unsigned long)context_ptr+0x00006354+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x00006738))=0xf71dec64;
*((unsigned int *)((unsigned long)context_ptr+0x00006738+4*1))=0xf5ae43a7;
*((unsigned int *)((unsigned long)context_ptr+0x00006738+4*2))=0xe4d9f1e8;
*((unsigned int *)((unsigned long)context_ptr+0x00006738+4*3))=0x2db8de7f;
*((unsigned int *)((unsigned long)context_ptr+0x00006738+4*4))=0xe4e34b33;
*((unsigned int *)((unsigned long)context_ptr+0x00006738+4*5))=0x1006fdc9;
*((unsigned int *)((unsigned long)context_ptr+0x00006738+4*6))=0x17d8655d;
*((unsigned int *)((unsigned long)context_ptr+0x00006738+4*7))=0x5ff6335f;
*((unsigned int *)((unsigned long)context_ptr+0x00006738+4*8))=0x5f127e39;
*((unsigned int *)((unsigned long)context_ptr+0x00006738+4*9))=0x2684705d;
*((unsigned int *)((unsigned long)context_ptr+0x00006738+4*10))=0x4f62ad19;
*((unsigned int *)((unsigned long)context_ptr+0x00006738+4*11))=0x453a815a;
*((unsigned int *)((unsigned long)context_ptr+0x00006738+4*12))=0x5bcf5df6;
*((unsigned int *)((unsigned long)context_ptr+0x00006738+4*13))=0xfd331220;
*((unsigned int *)((unsigned long)context_ptr+0x00006738+4*14))=0x9adafd6b;
*((unsigned int *)((unsigned long)context_ptr+0x00006738+4*15))=0x3ec62a2c;
*((unsigned int *)((unsigned long)context_ptr+0x00006738+4*16))=0x388e6779;
*((unsigned int *)((unsigned long)context_ptr+0x00006738+4*17))=0x3fbbf3bb;
*((unsigned int *)((unsigned long)context_ptr+0x00006738+4*18))=0x625527d8;
*((unsigned int *)((unsigned long)context_ptr+0x00006738+4*19))=0x2850598d;
*((unsigned int *)((unsigned long)context_ptr+0x00006738+4*20))=0xf9bfb063;
*((unsigned int *)((unsigned long)context_ptr+0x00006738+4*21))=0xc50c98a1;
*((unsigned int *)((unsigned long)context_ptr+0x00006738+4*22))=0x00000072;
*((unsigned int *)((unsigned long)context_ptr+0x00003840))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003840+4*1))=0x000064f8;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000840+4*1))=0x00006738;
*((unsigned int *)((unsigned long)context_ptr+0x00000840+4*2))=0x00006354;
*((unsigned int *)((unsigned long)context_ptr+0x00000840+4*3))=0x02220059;
*((unsigned int *)((unsigned long)context_ptr+0x00000840+4*4))=0x0029729f;
*((unsigned int *)((unsigned long)context_ptr+0x00000840+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000001c2&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006364,"\x2d\x01\x5f\x05\x45\x8d\x4b\xbb\x3f\x21\x47\xe6\x85\x5b\x15\x2b",16))
printf("strip: 2d015f05458d4bbb, Pass\n");
else
printf("strip: 2d015f05458d4bbb, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006364))=0x006a0802;
*((unsigned int *)((unsigned long)context_ptr+0x00006364+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006364+4*2))=0x0202005a;
*((unsigned int *)((unsigned long)context_ptr+0x00006364+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x00006204))=0x24892916;
*((unsigned int *)((unsigned long)context_ptr+0x00006204+4*1))=0xdbac0168;
*((unsigned int *)((unsigned long)context_ptr+0x00006204+4*2))=0x50a755d1;
*((unsigned int *)((unsigned long)context_ptr+0x00006204+4*3))=0x5942ec17;
*((unsigned int *)((unsigned long)context_ptr+0x00006204+4*4))=0x2595dc28;
*((unsigned int *)((unsigned long)context_ptr+0x00006204+4*5))=0xaba3c6d3;
*((unsigned int *)((unsigned long)context_ptr+0x00006204+4*6))=0xdbb42769;
*((unsigned int *)((unsigned long)context_ptr+0x00006204+4*7))=0xd69e1955;
*((unsigned int *)((unsigned long)context_ptr+0x00006204+4*8))=0x0ec627fb;
*((unsigned int *)((unsigned long)context_ptr+0x00006204+4*9))=0x0f1f0184;
*((unsigned int *)((unsigned long)context_ptr+0x00006204+4*10))=0x2c99ffca;
*((unsigned int *)((unsigned long)context_ptr+0x00006204+4*11))=0x8158304b;
*((unsigned int *)((unsigned long)context_ptr+0x00006204+4*12))=0x1656589f;
*((unsigned int *)((unsigned long)context_ptr+0x00006204+4*13))=0xe0dc4b05;
*((unsigned int *)((unsigned long)context_ptr+0x00006204+4*14))=0x724380f0;
*((unsigned int *)((unsigned long)context_ptr+0x00006204+4*15))=0x234a761b;
*((unsigned int *)((unsigned long)context_ptr+0x00006204+4*16))=0x56d51556;
*((unsigned int *)((unsigned long)context_ptr+0x00006204+4*17))=0x0b912aff;
*((unsigned int *)((unsigned long)context_ptr+0x00006204+4*18))=0xfe356bd2;
*((unsigned int *)((unsigned long)context_ptr+0x00006204+4*19))=0x7635d342;
*((unsigned int *)((unsigned long)context_ptr+0x00006204+4*20))=0x0c6a50c1;
*((unsigned int *)((unsigned long)context_ptr+0x00006204+4*21))=0xa73f783a;
*((unsigned int *)((unsigned long)context_ptr+0x00006204+4*22))=0x0000c354;
*((unsigned int *)((unsigned long)context_ptr+0x00003858))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003858+4*1))=0x000063f8;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000858+4*2))=0x00006364;
*((unsigned int *)((unsigned long)context_ptr+0x00000858+4*3))=0x0222005a;
*((unsigned int *)((unsigned long)context_ptr+0x00000858+4*4))=0x0f521c4e;
*((unsigned int *)((unsigned long)context_ptr+0x00000858+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000001c8&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006374,"\x1b\xfb\xe8\x12\xc6\xc2\x59\x14\x5c\xb4\x9a\x3f\x0f\xcd\xc4\x0d",16))
printf("strip: 1bfbe812c6c25914, Pass\n");
else
printf("strip: 1bfbe812c6c25914, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006374))=0x006a0802;
*((unsigned int *)((unsigned long)context_ptr+0x00006374+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006374+4*2))=0x0202005b;
*((unsigned int *)((unsigned long)context_ptr+0x00006374+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x00006794))=0x6091c338;
*((unsigned int *)((unsigned long)context_ptr+0x00006794+4*1))=0x64455461;
*((unsigned int *)((unsigned long)context_ptr+0x00006794+4*2))=0xa9496468;
*((unsigned int *)((unsigned long)context_ptr+0x00006794+4*3))=0x2afa32bd;
*((unsigned int *)((unsigned long)context_ptr+0x00006794+4*4))=0x2661e004;
*((unsigned int *)((unsigned long)context_ptr+0x00006794+4*5))=0x30668837;
*((unsigned int *)((unsigned long)context_ptr+0x00006794+4*6))=0xb4b5fe1b;
*((unsigned int *)((unsigned long)context_ptr+0x00006794+4*7))=0x9898691e;
*((unsigned int *)((unsigned long)context_ptr+0x00006794+4*8))=0x3b98e523;
*((unsigned int *)((unsigned long)context_ptr+0x00006794+4*9))=0x73fd8c78;
*((unsigned int *)((unsigned long)context_ptr+0x00006794+4*10))=0xc65f4823;
*((unsigned int *)((unsigned long)context_ptr+0x00006794+4*11))=0x672c78a4;
*((unsigned int *)((unsigned long)context_ptr+0x00006794+4*12))=0xd29a8ab2;
*((unsigned int *)((unsigned long)context_ptr+0x00006794+4*13))=0x898ee91a;
*((unsigned int *)((unsigned long)context_ptr+0x00006794+4*14))=0xf2e09f68;
*((unsigned int *)((unsigned long)context_ptr+0x00006794+4*15))=0x9c5f357e;
*((unsigned int *)((unsigned long)context_ptr+0x00006794+4*16))=0x0891f3ef;
*((unsigned int *)((unsigned long)context_ptr+0x00006794+4*17))=0xb372fed9;
*((unsigned int *)((unsigned long)context_ptr+0x00006794+4*18))=0x6bcaa098;
*((unsigned int *)((unsigned long)context_ptr+0x00006794+4*19))=0xb42a4b44;
*((unsigned int *)((unsigned long)context_ptr+0x00006794+4*20))=0x9a7d45c4;
*((unsigned int *)((unsigned long)context_ptr+0x00006794+4*21))=0x3e127f91;
*((unsigned int *)((unsigned long)context_ptr+0x00006794+4*22))=0x00587bb6;
*((unsigned int *)((unsigned long)context_ptr+0x00003870))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003870+4*1))=0x00006038;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000870+4*1))=0x00006794;
*((unsigned int *)((unsigned long)context_ptr+0x00000870+4*2))=0x00006374;
*((unsigned int *)((unsigned long)context_ptr+0x00000870+4*3))=0x0222005b;
*((unsigned int *)((unsigned long)context_ptr+0x00000870+4*4))=0x07b301b7;
*((unsigned int *)((unsigned long)context_ptr+0x00000870+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000001ce&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006558,"\x8f\x8e\xc2\x0d\x72\xc0\x86\x2b\x1c\xb4\x00\xd1\x74\x94\x01\xe5",16))
printf("strip: 8f8ec20d72c0862b, Pass\n");
else
printf("strip: 8f8ec20d72c0862b, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006028))=0x006a0802;
*((unsigned int *)((unsigned long)context_ptr+0x00006028+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006028+4*2))=0x0202005c;
*((unsigned int *)((unsigned long)context_ptr+0x00006028+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x00006508))=0x3ee793d2;
*((unsigned int *)((unsigned long)context_ptr+0x00006508+4*1))=0x02775046;
*((unsigned int *)((unsigned long)context_ptr+0x00006508+4*2))=0x8fcd5e8b;
*((unsigned int *)((unsigned long)context_ptr+0x00006508+4*3))=0xb8ea6a0c;
*((unsigned int *)((unsigned long)context_ptr+0x00006508+4*4))=0x9fe82090;
*((unsigned int *)((unsigned long)context_ptr+0x00006508+4*5))=0x13ebc9bc;
*((unsigned int *)((unsigned long)context_ptr+0x00006508+4*6))=0xf39d0c3c;
*((unsigned int *)((unsigned long)context_ptr+0x00006508+4*7))=0x1fa77c50;
*((unsigned int *)((unsigned long)context_ptr+0x00006508+4*8))=0x888e8ff9;
*((unsigned int *)((unsigned long)context_ptr+0x00006508+4*9))=0xbd064507;
*((unsigned int *)((unsigned long)context_ptr+0x00006508+4*10))=0x0e20e75b;
*((unsigned int *)((unsigned long)context_ptr+0x00006508+4*11))=0x948f2d09;
*((unsigned int *)((unsigned long)context_ptr+0x00006508+4*12))=0x812f74b4;
*((unsigned int *)((unsigned long)context_ptr+0x00006508+4*13))=0xe1359134;
*((unsigned int *)((unsigned long)context_ptr+0x00006508+4*14))=0xea34c471;
*((unsigned int *)((unsigned long)context_ptr+0x00006508+4*15))=0xcbedac01;
*((unsigned int *)((unsigned long)context_ptr+0x00006508+4*16))=0x05f206a0;
*((unsigned int *)((unsigned long)context_ptr+0x00006508+4*17))=0x4ab520b3;
*((unsigned int *)((unsigned long)context_ptr+0x00006508+4*18))=0x560ede5d;
*((unsigned int *)((unsigned long)context_ptr+0x00006508+4*19))=0x3cfa9176;
*((unsigned int *)((unsigned long)context_ptr+0x00006508+4*20))=0x244554b9;
*((unsigned int *)((unsigned long)context_ptr+0x00006508+4*21))=0xbb0c0419;
*((unsigned int *)((unsigned long)context_ptr+0x00006508+4*22))=0x9a2034f0;
*((unsigned int *)((unsigned long)context_ptr+0x00003888))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003888+4*1))=0x00006408;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000888+4*1))=0x00006508;
*((unsigned int *)((unsigned long)context_ptr+0x00000888+4*2))=0x00006028;
*((unsigned int *)((unsigned long)context_ptr+0x00000888+4*3))=0x0222005c;
*((unsigned int *)((unsigned long)context_ptr+0x00000888+4*4))=0x01dfe89b;
*((unsigned int *)((unsigned long)context_ptr+0x00000888+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000001d4&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000062b4,"\xef\x3e\x1c\x0e\x5f\x32\x98\xda\xab\x13\xd0\x70\x1b\xac\x29\x3e",16))
printf("strip: ef3e1c0e5f3298da, Pass\n");
else
printf("strip: ef3e1c0e5f3298da, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006048))=0x006a0802;
*((unsigned int *)((unsigned long)context_ptr+0x00006048+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006048+4*2))=0x0202005d;
*((unsigned int *)((unsigned long)context_ptr+0x00006048+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x00006260))=0xb28efe17;
*((unsigned int *)((unsigned long)context_ptr+0x00006260+4*1))=0xa2848e19;
*((unsigned int *)((unsigned long)context_ptr+0x00006260+4*2))=0xcdf14d6b;
*((unsigned int *)((unsigned long)context_ptr+0x00006260+4*3))=0x5453530a;
*((unsigned int *)((unsigned long)context_ptr+0x00006260+4*4))=0x292c1466;
*((unsigned int *)((unsigned long)context_ptr+0x00006260+4*5))=0x5009ad8d;
*((unsigned int *)((unsigned long)context_ptr+0x00006260+4*6))=0x8bb7bbf3;
*((unsigned int *)((unsigned long)context_ptr+0x00006260+4*7))=0x8c20a402;
*((unsigned int *)((unsigned long)context_ptr+0x00006260+4*8))=0x49a97d18;
*((unsigned int *)((unsigned long)context_ptr+0x00006260+4*9))=0x0661f3bf;
*((unsigned int *)((unsigned long)context_ptr+0x00006260+4*10))=0x87463c9a;
*((unsigned int *)((unsigned long)context_ptr+0x00006260+4*11))=0x1d49de41;
*((unsigned int *)((unsigned long)context_ptr+0x00006260+4*12))=0xb0be1ea5;
*((unsigned int *)((unsigned long)context_ptr+0x00006260+4*13))=0xe551462a;
*((unsigned int *)((unsigned long)context_ptr+0x00006260+4*14))=0xf93ec3f8;
*((unsigned int *)((unsigned long)context_ptr+0x00006260+4*15))=0x0a7a3147;
*((unsigned int *)((unsigned long)context_ptr+0x00006260+4*16))=0x1cb830e5;
*((unsigned int *)((unsigned long)context_ptr+0x00006260+4*17))=0xc38ffe4a;
*((unsigned int *)((unsigned long)context_ptr+0x00006260+4*18))=0x9b7e1850;
*((unsigned int *)((unsigned long)context_ptr+0x00006260+4*19))=0xbed73d54;
*((unsigned int *)((unsigned long)context_ptr+0x00006260+4*20))=0xc37b7c3c;
*((unsigned int *)((unsigned long)context_ptr+0x00006260+4*21))=0x3da19785;
*((unsigned int *)((unsigned long)context_ptr+0x00006260+4*22))=0xcf55ae0e;
*((unsigned int *)((unsigned long)context_ptr+0x00006260+4*23))=0x000000ef;
*((unsigned int *)((unsigned long)context_ptr+0x000038a0))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x000038a0+4*1))=0x00006418;
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
*((unsigned int *)((unsigned long)context_ptr+0x000008a0+4*1))=0x00006260;
*((unsigned int *)((unsigned long)context_ptr+0x000008a0+4*2))=0x00006048;
*((unsigned int *)((unsigned long)context_ptr+0x000008a0+4*3))=0x0222005d;
*((unsigned int *)((unsigned long)context_ptr+0x000008a0+4*4))=0x00dcba93;
*((unsigned int *)((unsigned long)context_ptr+0x000008a0+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000001da&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006058,"\x62\x11\xf8\x3a\x9b\x70\x5e\x13\xb9\xd5\x2f\xca\x87\x0f\x87\x13",16))
printf("strip: 6211f83a9b705e13, Pass\n");
else
printf("strip: 6211f83a9b705e13, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006058))=0x006a0802;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*2))=0x0202005e;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x00006428))=0x4d9825ee;
*((unsigned int *)((unsigned long)context_ptr+0x00006428+4*1))=0x6b33bc2b;
*((unsigned int *)((unsigned long)context_ptr+0x00006428+4*2))=0x9c26c654;
*((unsigned int *)((unsigned long)context_ptr+0x00006428+4*3))=0x01079903;
*((unsigned int *)((unsigned long)context_ptr+0x00006428+4*4))=0xd63dc48b;
*((unsigned int *)((unsigned long)context_ptr+0x00006428+4*5))=0x5e2a0717;
*((unsigned int *)((unsigned long)context_ptr+0x00006428+4*6))=0x6cac4983;
*((unsigned int *)((unsigned long)context_ptr+0x00006428+4*7))=0x5116ca02;
*((unsigned int *)((unsigned long)context_ptr+0x00006428+4*8))=0xcdd1c327;
*((unsigned int *)((unsigned long)context_ptr+0x00006428+4*9))=0xb0eb1ff7;
*((unsigned int *)((unsigned long)context_ptr+0x00006428+4*10))=0x1a1cfa1e;
*((unsigned int *)((unsigned long)context_ptr+0x00006428+4*11))=0xee1c3dab;
*((unsigned int *)((unsigned long)context_ptr+0x00006428+4*12))=0x9e4f30e2;
*((unsigned int *)((unsigned long)context_ptr+0x00006428+4*13))=0x9d93de90;
*((unsigned int *)((unsigned long)context_ptr+0x00006428+4*14))=0x54042fed;
*((unsigned int *)((unsigned long)context_ptr+0x00006428+4*15))=0x1076aaed;
*((unsigned int *)((unsigned long)context_ptr+0x00006428+4*16))=0x36310874;
*((unsigned int *)((unsigned long)context_ptr+0x00006428+4*17))=0xb51dc77a;
*((unsigned int *)((unsigned long)context_ptr+0x00006428+4*18))=0xf103af82;
*((unsigned int *)((unsigned long)context_ptr+0x00006428+4*19))=0xae246517;
*((unsigned int *)((unsigned long)context_ptr+0x00006428+4*20))=0xd11e3e4a;
*((unsigned int *)((unsigned long)context_ptr+0x00006428+4*21))=0x64cc4234;
*((unsigned int *)((unsigned long)context_ptr+0x00006428+4*22))=0x88dfc8b1;
*((unsigned int *)((unsigned long)context_ptr+0x00006428+4*23))=0x0000d139;
*((unsigned int *)((unsigned long)context_ptr+0x000038b8))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x000038b8+4*1))=0x000062c0;
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
*((unsigned int *)((unsigned long)context_ptr+0x000008b8+4*1))=0x00006428;
*((unsigned int *)((unsigned long)context_ptr+0x000008b8+4*2))=0x00006058;
*((unsigned int *)((unsigned long)context_ptr+0x000008b8+4*3))=0x0222005e;
*((unsigned int *)((unsigned long)context_ptr+0x000008b8+4*4))=0x027afb1a;
*((unsigned int *)((unsigned long)context_ptr+0x000008b8+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000001e0&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006068,"\xdb\xf8\x15\x0a\xfe\xa2\x4c\xd5\xb9\xa0\x9c\x6a\xf2\x8e\xcf\xaa",16))
printf("strip: dbf8150afea24cd5, Pass\n");
else
printf("strip: dbf8150afea24cd5, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006068))=0x006a0802;
*((unsigned int *)((unsigned long)context_ptr+0x00006068+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006068+4*2))=0x0202005f;
*((unsigned int *)((unsigned long)context_ptr+0x00006068+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x00006640))=0x951299d5;
*((unsigned int *)((unsigned long)context_ptr+0x00006640+4*1))=0x25346c3b;
*((unsigned int *)((unsigned long)context_ptr+0x00006640+4*2))=0xf8241b46;
*((unsigned int *)((unsigned long)context_ptr+0x00006640+4*3))=0x8cb1ffdc;
*((unsigned int *)((unsigned long)context_ptr+0x00006640+4*4))=0x5c34ca1c;
*((unsigned int *)((unsigned long)context_ptr+0x00006640+4*5))=0x9e41662f;
*((unsigned int *)((unsigned long)context_ptr+0x00006640+4*6))=0xacf1dc26;
*((unsigned int *)((unsigned long)context_ptr+0x00006640+4*7))=0xe1995242;
*((unsigned int *)((unsigned long)context_ptr+0x00006640+4*8))=0xcadb9db7;
*((unsigned int *)((unsigned long)context_ptr+0x00006640+4*9))=0xd87f30b3;
*((unsigned int *)((unsigned long)context_ptr+0x00006640+4*10))=0xb3161064;
*((unsigned int *)((unsigned long)context_ptr+0x00006640+4*11))=0xd43c3cb9;
*((unsigned int *)((unsigned long)context_ptr+0x00006640+4*12))=0x307630cb;
*((unsigned int *)((unsigned long)context_ptr+0x00006640+4*13))=0xf703d93a;
*((unsigned int *)((unsigned long)context_ptr+0x00006640+4*14))=0x5c6e8f29;
*((unsigned int *)((unsigned long)context_ptr+0x00006640+4*15))=0xd068aaf3;
*((unsigned int *)((unsigned long)context_ptr+0x00006640+4*16))=0x6cdb5552;
*((unsigned int *)((unsigned long)context_ptr+0x00006640+4*17))=0xdc576e5b;
*((unsigned int *)((unsigned long)context_ptr+0x00006640+4*18))=0x8a9d8a81;
*((unsigned int *)((unsigned long)context_ptr+0x00006640+4*19))=0x131f156b;
*((unsigned int *)((unsigned long)context_ptr+0x00006640+4*20))=0xf5237446;
*((unsigned int *)((unsigned long)context_ptr+0x00006640+4*21))=0x8c4e7a91;
*((unsigned int *)((unsigned long)context_ptr+0x00006640+4*22))=0xfda918b9;
*((unsigned int *)((unsigned long)context_ptr+0x00006640+4*23))=0x00523e31;
*((unsigned int *)((unsigned long)context_ptr+0x000038d0))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x000038d0+4*1))=0x000062d0;
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
*((unsigned int *)((unsigned long)context_ptr+0x000008d0+4*1))=0x00006640;
*((unsigned int *)((unsigned long)context_ptr+0x000008d0+4*2))=0x00006068;
*((unsigned int *)((unsigned long)context_ptr+0x000008d0+4*3))=0x0222005f;
*((unsigned int *)((unsigned long)context_ptr+0x000008d0+4*4))=0x0fa55465;
*((unsigned int *)((unsigned long)context_ptr+0x000008d0+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000001e6&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006494,"\x04\xa4\x9f\x41\x26\xe8\xcf\x1f\xef\xe3\xc5\x58\x26\x8b\x50\x64",16))
printf("strip: 04a49f4126e8cf1f, Pass\n");
else
printf("strip: 04a49f4126e8cf1f, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000062e0))=0x006a0802;
*((unsigned int *)((unsigned long)context_ptr+0x000062e0+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000062e0+4*2))=0x02020060;
*((unsigned int *)((unsigned long)context_ptr+0x000062e0+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x000066a0))=0xb9cae3e4;
*((unsigned int *)((unsigned long)context_ptr+0x000066a0+4*1))=0x28d945bf;
*((unsigned int *)((unsigned long)context_ptr+0x000066a0+4*2))=0xee06704b;
*((unsigned int *)((unsigned long)context_ptr+0x000066a0+4*3))=0xee9f9768;
*((unsigned int *)((unsigned long)context_ptr+0x000066a0+4*4))=0xf182ba38;
*((unsigned int *)((unsigned long)context_ptr+0x000066a0+4*5))=0xf5531712;
*((unsigned int *)((unsigned long)context_ptr+0x000066a0+4*6))=0x55442258;
*((unsigned int *)((unsigned long)context_ptr+0x000066a0+4*7))=0x50142252;
*((unsigned int *)((unsigned long)context_ptr+0x000066a0+4*8))=0x7c86ab4f;
*((unsigned int *)((unsigned long)context_ptr+0x000066a0+4*9))=0xd0de945c;
*((unsigned int *)((unsigned long)context_ptr+0x000066a0+4*10))=0xb3f5f966;
*((unsigned int *)((unsigned long)context_ptr+0x000066a0+4*11))=0x4bb2e51a;
*((unsigned int *)((unsigned long)context_ptr+0x000066a0+4*12))=0x5cc704c5;
*((unsigned int *)((unsigned long)context_ptr+0x000066a0+4*13))=0x82e78e54;
*((unsigned int *)((unsigned long)context_ptr+0x000066a0+4*14))=0xc95e7539;
*((unsigned int *)((unsigned long)context_ptr+0x000066a0+4*15))=0x8fee1d06;
*((unsigned int *)((unsigned long)context_ptr+0x000066a0+4*16))=0xe917a0fe;
*((unsigned int *)((unsigned long)context_ptr+0x000066a0+4*17))=0xde65ba3a;
*((unsigned int *)((unsigned long)context_ptr+0x000066a0+4*18))=0xc1cf93d5;
*((unsigned int *)((unsigned long)context_ptr+0x000066a0+4*19))=0xdcb5fca5;
*((unsigned int *)((unsigned long)context_ptr+0x000066a0+4*20))=0xf8ddd4c8;
*((unsigned int *)((unsigned long)context_ptr+0x000066a0+4*21))=0x410a51a5;
*((unsigned int *)((unsigned long)context_ptr+0x000066a0+4*22))=0x4426c5cc;
*((unsigned int *)((unsigned long)context_ptr+0x000066a0+4*23))=0x2e0c8825;
*((unsigned int *)((unsigned long)context_ptr+0x000038e8))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x000038e8+4*1))=0x00006488;
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
*((unsigned int *)((unsigned long)context_ptr+0x000008e8+4*1))=0x000066a0;
*((unsigned int *)((unsigned long)context_ptr+0x000008e8+4*2))=0x000062e0;
*((unsigned int *)((unsigned long)context_ptr+0x000008e8+4*3))=0x02220060;
*((unsigned int *)((unsigned long)context_ptr+0x000008e8+4*4))=0x0209298d;
*((unsigned int *)((unsigned long)context_ptr+0x000008e8+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000001ec&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000065b8,"\x5c\x96\x87\x5d\xf4\x35\x99\x7a\x2a\x9a\xd5\xaa\x22\x36\x5a\x57",16))
printf("strip: 5c96875df435997a, Pass\n");
else
printf("strip: 5c96875df435997a, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000062f0))=0x006a0802;
*((unsigned int *)((unsigned long)context_ptr+0x000062f0+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000062f0+4*2))=0x02020061;
*((unsigned int *)((unsigned long)context_ptr+0x000062f0+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x00006564))=0x857d55c8;
*((unsigned int *)((unsigned long)context_ptr+0x00006564+4*1))=0x893aec29;
*((unsigned int *)((unsigned long)context_ptr+0x00006564+4*2))=0x5a43fa65;
*((unsigned int *)((unsigned long)context_ptr+0x00006564+4*3))=0x14d8b530;
*((unsigned int *)((unsigned long)context_ptr+0x00006564+4*4))=0x9dbfd393;
*((unsigned int *)((unsigned long)context_ptr+0x00006564+4*5))=0x63c82121;
*((unsigned int *)((unsigned long)context_ptr+0x00006564+4*6))=0x0fecf66d;
*((unsigned int *)((unsigned long)context_ptr+0x00006564+4*7))=0x6bae227c;
*((unsigned int *)((unsigned long)context_ptr+0x00006564+4*8))=0xe3929afe;
*((unsigned int *)((unsigned long)context_ptr+0x00006564+4*9))=0xd1c33f53;
*((unsigned int *)((unsigned long)context_ptr+0x00006564+4*10))=0xb6e009ac;
*((unsigned int *)((unsigned long)context_ptr+0x00006564+4*11))=0x0518ef4e;
*((unsigned int *)((unsigned long)context_ptr+0x00006564+4*12))=0xe342d6cb;
*((unsigned int *)((unsigned long)context_ptr+0x00006564+4*13))=0x1240ab85;
*((unsigned int *)((unsigned long)context_ptr+0x00006564+4*14))=0xfda54339;
*((unsigned int *)((unsigned long)context_ptr+0x00006564+4*15))=0x1a866486;
*((unsigned int *)((unsigned long)context_ptr+0x00006564+4*16))=0xa4a4a8b6;
*((unsigned int *)((unsigned long)context_ptr+0x00006564+4*17))=0x5671ea22;
*((unsigned int *)((unsigned long)context_ptr+0x00006564+4*18))=0x13e45159;
*((unsigned int *)((unsigned long)context_ptr+0x00006564+4*19))=0x8719428f;
*((unsigned int *)((unsigned long)context_ptr+0x00006564+4*20))=0xeb5c598e;
*((unsigned int *)((unsigned long)context_ptr+0x00006564+4*21))=0xaab1cd8c;
*((unsigned int *)((unsigned long)context_ptr+0x00006564+4*22))=0x7774beef;
*((unsigned int *)((unsigned long)context_ptr+0x00006564+4*23))=0xc3cbd8ca;
*((unsigned int *)((unsigned long)context_ptr+0x00006564+4*24))=0x00000055;
*((unsigned int *)((unsigned long)context_ptr+0x00003900))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003900+4*1))=0x00006700;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000900+4*1))=0x00006564;
*((unsigned int *)((unsigned long)context_ptr+0x00000900+4*2))=0x000062f0;
*((unsigned int *)((unsigned long)context_ptr+0x00000900+4*3))=0x02220061;
*((unsigned int *)((unsigned long)context_ptr+0x00000900+4*4))=0x02f3e6d6;
*((unsigned int *)((unsigned long)context_ptr+0x00000900+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000001f2&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000065c8,"\x3d\x5f\x89\x75\xcf\x30\xc9\x23\xf9\xeb\xc6\x6d\xde\x46\x00\x9a",16))
printf("strip: 3d5f8975cf30c923, Pass\n");
else
printf("strip: 3d5f8975cf30c923, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000065c8))=0x006a0802;
*((unsigned int *)((unsigned long)context_ptr+0x000065c8+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000065c8+4*2))=0x02020062;
*((unsigned int *)((unsigned long)context_ptr+0x000065c8+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x000067f0))=0x1ba4f475;
*((unsigned int *)((unsigned long)context_ptr+0x000067f0+4*1))=0xba6d90a7;
*((unsigned int *)((unsigned long)context_ptr+0x000067f0+4*2))=0x8db831a7;
*((unsigned int *)((unsigned long)context_ptr+0x000067f0+4*3))=0x60749d35;
*((unsigned int *)((unsigned long)context_ptr+0x000067f0+4*4))=0x62c5a95a;
*((unsigned int *)((unsigned long)context_ptr+0x000067f0+4*5))=0x50dffc30;
*((unsigned int *)((unsigned long)context_ptr+0x000067f0+4*6))=0x2cd6a219;
*((unsigned int *)((unsigned long)context_ptr+0x000067f0+4*7))=0xac095dad;
*((unsigned int *)((unsigned long)context_ptr+0x000067f0+4*8))=0x2d3ccb6d;
*((unsigned int *)((unsigned long)context_ptr+0x000067f0+4*9))=0x92e1c258;
*((unsigned int *)((unsigned long)context_ptr+0x000067f0+4*10))=0x06292d9c;
*((unsigned int *)((unsigned long)context_ptr+0x000067f0+4*11))=0x32ddc73a;
*((unsigned int *)((unsigned long)context_ptr+0x000067f0+4*12))=0x94cf6522;
*((unsigned int *)((unsigned long)context_ptr+0x000067f0+4*13))=0x064112c8;
*((unsigned int *)((unsigned long)context_ptr+0x000067f0+4*14))=0x1872fa77;
*((unsigned int *)((unsigned long)context_ptr+0x000067f0+4*15))=0xfe14dc11;
*((unsigned int *)((unsigned long)context_ptr+0x000067f0+4*16))=0x12743a1b;
*((unsigned int *)((unsigned long)context_ptr+0x000067f0+4*17))=0x2847bfc2;
*((unsigned int *)((unsigned long)context_ptr+0x000067f0+4*18))=0x0163b0f1;
*((unsigned int *)((unsigned long)context_ptr+0x000067f0+4*19))=0x47867c36;
*((unsigned int *)((unsigned long)context_ptr+0x000067f0+4*20))=0xa12632ef;
*((unsigned int *)((unsigned long)context_ptr+0x000067f0+4*21))=0x77d9e94f;
*((unsigned int *)((unsigned long)context_ptr+0x000067f0+4*22))=0x5c864c7d;
*((unsigned int *)((unsigned long)context_ptr+0x000067f0+4*23))=0x751e88fb;
*((unsigned int *)((unsigned long)context_ptr+0x000067f0+4*24))=0x0000816a;
*((unsigned int *)((unsigned long)context_ptr+0x00003918))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003918+4*1))=0x00006300;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000918+4*1))=0x000067f0;
*((unsigned int *)((unsigned long)context_ptr+0x00000918+4*2))=0x000065c8;
*((unsigned int *)((unsigned long)context_ptr+0x00000918+4*3))=0x02220062;
*((unsigned int *)((unsigned long)context_ptr+0x00000918+4*4))=0x0a65c2fd;
*((unsigned int *)((unsigned long)context_ptr+0x00000918+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000001f8&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000065d8,"\x05\xaf\x06\xe0\xa7\x6a\x57\x46\x87\xf3\x3d\x9a\xb2\x3b\xc1\xb1",16))
printf("strip: 05af06e0a76a5746, Pass\n");
else
printf("strip: 05af06e0a76a5746, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000065d8))=0x006a0802;
*((unsigned int *)((unsigned long)context_ptr+0x000065d8+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000065d8+4*2))=0x02020063;
*((unsigned int *)((unsigned long)context_ptr+0x000065d8+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x00006854))=0x5543b764;
*((unsigned int *)((unsigned long)context_ptr+0x00006854+4*1))=0xe1a494a8;
*((unsigned int *)((unsigned long)context_ptr+0x00006854+4*2))=0x8e58d3dc;
*((unsigned int *)((unsigned long)context_ptr+0x00006854+4*3))=0xc5669e6a;
*((unsigned int *)((unsigned long)context_ptr+0x00006854+4*4))=0xbaedb5b4;
*((unsigned int *)((unsigned long)context_ptr+0x00006854+4*5))=0x7e104f86;
*((unsigned int *)((unsigned long)context_ptr+0x00006854+4*6))=0x8804feb8;
*((unsigned int *)((unsigned long)context_ptr+0x00006854+4*7))=0x9a661bf0;
*((unsigned int *)((unsigned long)context_ptr+0x00006854+4*8))=0x82665eb3;
*((unsigned int *)((unsigned long)context_ptr+0x00006854+4*9))=0xab2f5c0a;
*((unsigned int *)((unsigned long)context_ptr+0x00006854+4*10))=0xcc0145a9;
*((unsigned int *)((unsigned long)context_ptr+0x00006854+4*11))=0xdf00f908;
*((unsigned int *)((unsigned long)context_ptr+0x00006854+4*12))=0xf23e3287;
*((unsigned int *)((unsigned long)context_ptr+0x00006854+4*13))=0x58875e1c;
*((unsigned int *)((unsigned long)context_ptr+0x00006854+4*14))=0x51766149;
*((unsigned int *)((unsigned long)context_ptr+0x00006854+4*15))=0xeae0b620;
*((unsigned int *)((unsigned long)context_ptr+0x00006854+4*16))=0x00b7a0a9;
*((unsigned int *)((unsigned long)context_ptr+0x00006854+4*17))=0x2fc9a24d;
*((unsigned int *)((unsigned long)context_ptr+0x00006854+4*18))=0x89869a1f;
*((unsigned int *)((unsigned long)context_ptr+0x00006854+4*19))=0x3c1cd57b;
*((unsigned int *)((unsigned long)context_ptr+0x00006854+4*20))=0x6292d397;
*((unsigned int *)((unsigned long)context_ptr+0x00006854+4*21))=0xef365a59;
*((unsigned int *)((unsigned long)context_ptr+0x00006854+4*22))=0x675ae2c6;
*((unsigned int *)((unsigned long)context_ptr+0x00006854+4*23))=0xa2770536;
*((unsigned int *)((unsigned long)context_ptr+0x00006854+4*24))=0x003ef9f3;
*((unsigned int *)((unsigned long)context_ptr+0x00003930))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003930+4*1))=0x00006310;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000930+4*1))=0x00006854;
*((unsigned int *)((unsigned long)context_ptr+0x00000930+4*2))=0x000065d8;
*((unsigned int *)((unsigned long)context_ptr+0x00000930+4*3))=0x02220063;
*((unsigned int *)((unsigned long)context_ptr+0x00000930+4*4))=0x028e119e;
*((unsigned int *)((unsigned long)context_ptr+0x00000930+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000001fe&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000063d8,"\x10\x36\xf6\xb5\x23\xa8\xae\x1e\x33\x3c\xa6\x47\x7a\xc8\x13\xdf",16))
printf("strip: 1036f6b523a8ae1e, Pass\n");
else
printf("strip: 1036f6b523a8ae1e, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006320))=0x006a0802;
*((unsigned int *)((unsigned long)context_ptr+0x00006320+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006320+4*2))=0x02020064;
*((unsigned int *)((unsigned long)context_ptr+0x00006320+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x00006384))=0x83b8bc3a;
*((unsigned int *)((unsigned long)context_ptr+0x00006384+4*1))=0x3761040b;
*((unsigned int *)((unsigned long)context_ptr+0x00006384+4*2))=0xa0a0e6ae;
*((unsigned int *)((unsigned long)context_ptr+0x00006384+4*3))=0x04de4d52;
*((unsigned int *)((unsigned long)context_ptr+0x00006384+4*4))=0x0ffc833a;
*((unsigned int *)((unsigned long)context_ptr+0x00006384+4*5))=0x0577471b;
*((unsigned int *)((unsigned long)context_ptr+0x00006384+4*6))=0x57809741;
*((unsigned int *)((unsigned long)context_ptr+0x00006384+4*7))=0x4726219e;
*((unsigned int *)((unsigned long)context_ptr+0x00006384+4*8))=0xbe506bf3;
*((unsigned int *)((unsigned long)context_ptr+0x00006384+4*9))=0xd0e827d7;
*((unsigned int *)((unsigned long)context_ptr+0x00006384+4*10))=0xd67e325e;
*((unsigned int *)((unsigned long)context_ptr+0x00006384+4*11))=0x9acb2b35;
*((unsigned int *)((unsigned long)context_ptr+0x00006384+4*12))=0xf64f7eba;
*((unsigned int *)((unsigned long)context_ptr+0x00006384+4*13))=0x0351aa3d;
*((unsigned int *)((unsigned long)context_ptr+0x00006384+4*14))=0x83d2b685;
*((unsigned int *)((unsigned long)context_ptr+0x00006384+4*15))=0x96945302;
*((unsigned int *)((unsigned long)context_ptr+0x00006384+4*16))=0x2ab6f5ec;
*((unsigned int *)((unsigned long)context_ptr+0x00006384+4*17))=0x12551fbd;
*((unsigned int *)((unsigned long)context_ptr+0x00006384+4*18))=0x09b783cf;
*((unsigned int *)((unsigned long)context_ptr+0x00006384+4*19))=0x287d342d;
*((unsigned int *)((unsigned long)context_ptr+0x00006384+4*20))=0xf51b8f19;
*((unsigned int *)((unsigned long)context_ptr+0x00006384+4*21))=0x4cc4fec6;
*((unsigned int *)((unsigned long)context_ptr+0x00006384+4*22))=0x511f33cf;
*((unsigned int *)((unsigned long)context_ptr+0x00006384+4*23))=0x11e31eb3;
*((unsigned int *)((unsigned long)context_ptr+0x00006384+4*24))=0xc383b0c6;
*((unsigned int *)((unsigned long)context_ptr+0x00003948))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003948+4*1))=0x00006710;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000948+4*1))=0x00006384;
*((unsigned int *)((unsigned long)context_ptr+0x00000948+4*2))=0x00006320;
*((unsigned int *)((unsigned long)context_ptr+0x00000948+4*3))=0x02220064;
*((unsigned int *)((unsigned long)context_ptr+0x00000948+4*4))=0x026553bc;
*((unsigned int *)((unsigned long)context_ptr+0x00000948+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000204&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006124,"\xc4\xd3\x4a\x4e\x65\x0d\xe2\x27\x45\x79\x0d\x5c\xbc\x60\x1e\x5b",16))
printf("strip: c4d34a4e650de227, Pass\n");
else
printf("strip: c4d34a4e650de227, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006330))=0x006a0802;
*((unsigned int *)((unsigned long)context_ptr+0x00006330+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006330+4*2))=0x02020065;
*((unsigned int *)((unsigned long)context_ptr+0x00006330+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x00006078))=0xd50935a7;
*((unsigned int *)((unsigned long)context_ptr+0x00006078+4*1))=0x87a9204d;
*((unsigned int *)((unsigned long)context_ptr+0x00006078+4*2))=0x9737828d;
*((unsigned int *)((unsigned long)context_ptr+0x00006078+4*3))=0x8e007a06;
*((unsigned int *)((unsigned long)context_ptr+0x00006078+4*4))=0x09e6d13c;
*((unsigned int *)((unsigned long)context_ptr+0x00006078+4*5))=0x10aeeaa8;
*((unsigned int *)((unsigned long)context_ptr+0x00006078+4*6))=0xa62710a4;
*((unsigned int *)((unsigned long)context_ptr+0x00006078+4*7))=0xe09408ae;
*((unsigned int *)((unsigned long)context_ptr+0x00006078+4*8))=0xa437a4a1;
*((unsigned int *)((unsigned long)context_ptr+0x00006078+4*9))=0xd13dd526;
*((unsigned int *)((unsigned long)context_ptr+0x00006078+4*10))=0x4d559806;
*((unsigned int *)((unsigned long)context_ptr+0x00006078+4*11))=0x2dfa3e9c;
*((unsigned int *)((unsigned long)context_ptr+0x00006078+4*12))=0xeb4fad8b;
*((unsigned int *)((unsigned long)context_ptr+0x00006078+4*13))=0x8f7037c7;
*((unsigned int *)((unsigned long)context_ptr+0x00006078+4*14))=0x4ebdc506;
*((unsigned int *)((unsigned long)context_ptr+0x00006078+4*15))=0xdd6f6aca;
*((unsigned int *)((unsigned long)context_ptr+0x00006078+4*16))=0x33bac74e;
*((unsigned int *)((unsigned long)context_ptr+0x00006078+4*17))=0x409c284b;
*((unsigned int *)((unsigned long)context_ptr+0x00006078+4*18))=0xc13e33ec;
*((unsigned int *)((unsigned long)context_ptr+0x00006078+4*19))=0xcb006e9b;
*((unsigned int *)((unsigned long)context_ptr+0x00006078+4*20))=0x30518855;
*((unsigned int *)((unsigned long)context_ptr+0x00006078+4*21))=0xd3b77fe4;
*((unsigned int *)((unsigned long)context_ptr+0x00006078+4*22))=0x0c17a467;
*((unsigned int *)((unsigned long)context_ptr+0x00006078+4*23))=0xf6f1fb9a;
*((unsigned int *)((unsigned long)context_ptr+0x00006078+4*24))=0x9db77395;
*((unsigned int *)((unsigned long)context_ptr+0x00006078+4*25))=0x000000dc;
*((unsigned int *)((unsigned long)context_ptr+0x00003960))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003960+4*1))=0x00006720;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000960+4*1))=0x00006078;
*((unsigned int *)((unsigned long)context_ptr+0x00000960+4*2))=0x00006330;
*((unsigned int *)((unsigned long)context_ptr+0x00000960+4*3))=0x02220065;
*((unsigned int *)((unsigned long)context_ptr+0x00000960+4*4))=0x04ecfb57;
*((unsigned int *)((unsigned long)context_ptr+0x00000960+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000020a&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x0000618c,"\xda\xfe\xf1\xec\x8f\x1c\xf5\xfb\x5a\x81\x39\xfc\x21\x58\x18\xb9",16))
printf("strip: dafef1ec8f1cf5fb, Pass\n");
else
printf("strip: dafef1ec8f1cf5fb, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006340))=0x006a0802;
*((unsigned int *)((unsigned long)context_ptr+0x00006340+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006340+4*2))=0x02020066;
*((unsigned int *)((unsigned long)context_ptr+0x00006340+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x000060e0))=0x75f7861f;
*((unsigned int *)((unsigned long)context_ptr+0x000060e0+4*1))=0x59610a4f;
*((unsigned int *)((unsigned long)context_ptr+0x000060e0+4*2))=0x783f6161;
*((unsigned int *)((unsigned long)context_ptr+0x000060e0+4*3))=0xafbd4998;
*((unsigned int *)((unsigned long)context_ptr+0x000060e0+4*4))=0xa21f2b69;
*((unsigned int *)((unsigned long)context_ptr+0x000060e0+4*5))=0x9faff70d;
*((unsigned int *)((unsigned long)context_ptr+0x000060e0+4*6))=0x953c964d;
*((unsigned int *)((unsigned long)context_ptr+0x000060e0+4*7))=0xc4f6e664;
*((unsigned int *)((unsigned long)context_ptr+0x000060e0+4*8))=0x1bfac9d1;
*((unsigned int *)((unsigned long)context_ptr+0x000060e0+4*9))=0xdf82e8ca;
*((unsigned int *)((unsigned long)context_ptr+0x000060e0+4*10))=0x7bcd07cc;
*((unsigned int *)((unsigned long)context_ptr+0x000060e0+4*11))=0x9798559b;
*((unsigned int *)((unsigned long)context_ptr+0x000060e0+4*12))=0xa92e8025;
*((unsigned int *)((unsigned long)context_ptr+0x000060e0+4*13))=0xf5975b0d;
*((unsigned int *)((unsigned long)context_ptr+0x000060e0+4*14))=0x50652719;
*((unsigned int *)((unsigned long)context_ptr+0x000060e0+4*15))=0xab21d3b5;
*((unsigned int *)((unsigned long)context_ptr+0x000060e0+4*16))=0x4457e9cb;
*((unsigned int *)((unsigned long)context_ptr+0x000060e0+4*17))=0xb29066bf;
*((unsigned int *)((unsigned long)context_ptr+0x000060e0+4*18))=0xbbeebf4d;
*((unsigned int *)((unsigned long)context_ptr+0x000060e0+4*19))=0x91ef7953;
*((unsigned int *)((unsigned long)context_ptr+0x000060e0+4*20))=0xe85c801c;
*((unsigned int *)((unsigned long)context_ptr+0x000060e0+4*21))=0xed092f8d;
*((unsigned int *)((unsigned long)context_ptr+0x000060e0+4*22))=0x5d68a727;
*((unsigned int *)((unsigned long)context_ptr+0x000060e0+4*23))=0x492f6eb8;
*((unsigned int *)((unsigned long)context_ptr+0x000060e0+4*24))=0x73d19563;
*((unsigned int *)((unsigned long)context_ptr+0x000060e0+4*25))=0x000056f1;
*((unsigned int *)((unsigned long)context_ptr+0x00003978))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003978+4*1))=0x00006148;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000978+4*1))=0x000060e0;
*((unsigned int *)((unsigned long)context_ptr+0x00000978+4*2))=0x00006340;
*((unsigned int *)((unsigned long)context_ptr+0x00000978+4*3))=0x02220066;
*((unsigned int *)((unsigned long)context_ptr+0x00000978+4*4))=0x05e79a79;
*((unsigned int *)((unsigned long)context_ptr+0x00000978+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000210&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000061f4,"\x55\xbf\x22\xb7\x0b\x88\x42\xfd\x0c\x50\x63\x0f\xf8\x64\xe1\x8e",16))
printf("strip: 55bf22b70b8842fd, Pass\n");
else
printf("strip: 55bf22b70b8842fd, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000063e8))=0x006a0802;
*((unsigned int *)((unsigned long)context_ptr+0x000063e8+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000063e8+4*2))=0x02020067;
*((unsigned int *)((unsigned long)context_ptr+0x000063e8+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x00006158))=0xfc4ad41f;
*((unsigned int *)((unsigned long)context_ptr+0x00006158+4*1))=0x9d3d0ddf;
*((unsigned int *)((unsigned long)context_ptr+0x00006158+4*2))=0xf8bdc660;
*((unsigned int *)((unsigned long)context_ptr+0x00006158+4*3))=0x1205b15c;
*((unsigned int *)((unsigned long)context_ptr+0x00006158+4*4))=0xc6600ec8;
*((unsigned int *)((unsigned long)context_ptr+0x00006158+4*5))=0xc256d510;
*((unsigned int *)((unsigned long)context_ptr+0x00006158+4*6))=0xe567adfd;
*((unsigned int *)((unsigned long)context_ptr+0x00006158+4*7))=0x56783947;
*((unsigned int *)((unsigned long)context_ptr+0x00006158+4*8))=0x93f05fe7;
*((unsigned int *)((unsigned long)context_ptr+0x00006158+4*9))=0xa0196a0f;
*((unsigned int *)((unsigned long)context_ptr+0x00006158+4*10))=0x28999185;
*((unsigned int *)((unsigned long)context_ptr+0x00006158+4*11))=0xe3138470;
*((unsigned int *)((unsigned long)context_ptr+0x00006158+4*12))=0x88ffe858;
*((unsigned int *)((unsigned long)context_ptr+0x00006158+4*13))=0xc47a53ab;
*((unsigned int *)((unsigned long)context_ptr+0x00006158+4*14))=0xa45ca6ef;
*((unsigned int *)((unsigned long)context_ptr+0x00006158+4*15))=0xaf887086;
*((unsigned int *)((unsigned long)context_ptr+0x00006158+4*16))=0x3a816526;
*((unsigned int *)((unsigned long)context_ptr+0x00006158+4*17))=0x9e918587;
*((unsigned int *)((unsigned long)context_ptr+0x00006158+4*18))=0x7d36bd50;
*((unsigned int *)((unsigned long)context_ptr+0x00006158+4*19))=0xf74a42e3;
*((unsigned int *)((unsigned long)context_ptr+0x00006158+4*20))=0x85550fd9;
*((unsigned int *)((unsigned long)context_ptr+0x00006158+4*21))=0xa961ae3d;
*((unsigned int *)((unsigned long)context_ptr+0x00006158+4*22))=0x59e90d91;
*((unsigned int *)((unsigned long)context_ptr+0x00006158+4*23))=0x08ebea00;
*((unsigned int *)((unsigned long)context_ptr+0x00006158+4*24))=0x34073ef3;
*((unsigned int *)((unsigned long)context_ptr+0x00006158+4*25))=0x0097511e;
*((unsigned int *)((unsigned long)context_ptr+0x00003990))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003990+4*1))=0x000061c0;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000990+4*1))=0x00006158;
*((unsigned int *)((unsigned long)context_ptr+0x00000990+4*2))=0x000063e8;
*((unsigned int *)((unsigned long)context_ptr+0x00000990+4*3))=0x02220067;
*((unsigned int *)((unsigned long)context_ptr+0x00000990+4*4))=0x0058ee19;
*((unsigned int *)((unsigned long)context_ptr+0x00000990+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000216&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000064f8,"\x88\xde\xe0\x24\x38\xef\xb7\x79\xe1\xfa\x48\x92\xf1\x4e\x29\xe7",16))
printf("strip: 88dee02438efb779, Pass\n");
else
printf("strip: 88dee02438efb779, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006350))=0x006a0802;
*((unsigned int *)((unsigned long)context_ptr+0x00006350+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006350+4*2))=0x02020068;
*((unsigned int *)((unsigned long)context_ptr+0x00006350+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x00006498))=0xde340301;
*((unsigned int *)((unsigned long)context_ptr+0x00006498+4*1))=0xf4cb9e9e;
*((unsigned int *)((unsigned long)context_ptr+0x00006498+4*2))=0x8bd035fc;
*((unsigned int *)((unsigned long)context_ptr+0x00006498+4*3))=0x08462d0c;
*((unsigned int *)((unsigned long)context_ptr+0x00006498+4*4))=0xf1dac404;
*((unsigned int *)((unsigned long)context_ptr+0x00006498+4*5))=0x4a857fcc;
*((unsigned int *)((unsigned long)context_ptr+0x00006498+4*6))=0xc2ebff0c;
*((unsigned int *)((unsigned long)context_ptr+0x00006498+4*7))=0xf3bb5c45;
*((unsigned int *)((unsigned long)context_ptr+0x00006498+4*8))=0xb17dd974;
*((unsigned int *)((unsigned long)context_ptr+0x00006498+4*9))=0xc4afbde7;
*((unsigned int *)((unsigned long)context_ptr+0x00006498+4*10))=0x809414d9;
*((unsigned int *)((unsigned long)context_ptr+0x00006498+4*11))=0x98522da7;
*((unsigned int *)((unsigned long)context_ptr+0x00006498+4*12))=0x66153cc5;
*((unsigned int *)((unsigned long)context_ptr+0x00006498+4*13))=0x03486f86;
*((unsigned int *)((unsigned long)context_ptr+0x00006498+4*14))=0xb00bb6b0;
*((unsigned int *)((unsigned long)context_ptr+0x00006498+4*15))=0xbfcc1a3d;
*((unsigned int *)((unsigned long)context_ptr+0x00006498+4*16))=0x2563798b;
*((unsigned int *)((unsigned long)context_ptr+0x00006498+4*17))=0x1f15154c;
*((unsigned int *)((unsigned long)context_ptr+0x00006498+4*18))=0x8fec192e;
*((unsigned int *)((unsigned long)context_ptr+0x00006498+4*19))=0x3b82fe58;
*((unsigned int *)((unsigned long)context_ptr+0x00006498+4*20))=0xd1e0cc87;
*((unsigned int *)((unsigned long)context_ptr+0x00006498+4*21))=0xbcb72757;
*((unsigned int *)((unsigned long)context_ptr+0x00006498+4*22))=0x7fa0aa98;
*((unsigned int *)((unsigned long)context_ptr+0x00006498+4*23))=0x3452fa28;
*((unsigned int *)((unsigned long)context_ptr+0x00006498+4*24))=0x551512ac;
*((unsigned int *)((unsigned long)context_ptr+0x00006498+4*25))=0x3f3d63f4;
*((unsigned int *)((unsigned long)context_ptr+0x000039a8))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x000039a8+4*1))=0x000061d0;
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
*((unsigned int *)((unsigned long)context_ptr+0x000009a8+4*1))=0x00006498;
*((unsigned int *)((unsigned long)context_ptr+0x000009a8+4*2))=0x00006350;
*((unsigned int *)((unsigned long)context_ptr+0x000009a8+4*3))=0x02220068;
*((unsigned int *)((unsigned long)context_ptr+0x000009a8+4*4))=0x09d8b612;
*((unsigned int *)((unsigned long)context_ptr+0x000009a8+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000021c&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000063f8,"\xc7\x67\xb4\xa9\xc7\x75\x0a\x3c\xda\x3c\xed\xcf\x23\x7e\x0e\x6b",16))
printf("strip: c767b4a9c7750a3c, Pass\n");
else
printf("strip: c767b4a9c7750a3c, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000063f8))=0x006a0802;
*((unsigned int *)((unsigned long)context_ptr+0x000063f8+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000063f8+4*2))=0x02020069;
*((unsigned int *)((unsigned long)context_ptr+0x000063f8+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x000061e0))=0x4e371b7e;
*((unsigned int *)((unsigned long)context_ptr+0x000061e0+4*1))=0x0972304f;
*((unsigned int *)((unsigned long)context_ptr+0x000061e0+4*2))=0xfd63e359;
*((unsigned int *)((unsigned long)context_ptr+0x000061e0+4*3))=0x9906d8ff;
*((unsigned int *)((unsigned long)context_ptr+0x000061e0+4*4))=0x118028b6;
*((unsigned int *)((unsigned long)context_ptr+0x000061e0+4*5))=0x15d91689;
*((unsigned int *)((unsigned long)context_ptr+0x000061e0+4*6))=0x0f8821f7;
*((unsigned int *)((unsigned long)context_ptr+0x000061e0+4*7))=0x3c28d744;
*((unsigned int *)((unsigned long)context_ptr+0x000061e0+4*8))=0x223fd1ec;
*((unsigned int *)((unsigned long)context_ptr+0x000061e0+4*9))=0xbc5458ea;
*((unsigned int *)((unsigned long)context_ptr+0x000061e0+4*10))=0xe63cc87c;
*((unsigned int *)((unsigned long)context_ptr+0x000061e0+4*11))=0x03352b82;
*((unsigned int *)((unsigned long)context_ptr+0x000061e0+4*12))=0xe20fd5aa;
*((unsigned int *)((unsigned long)context_ptr+0x000061e0+4*13))=0xbb30bec6;
*((unsigned int *)((unsigned long)context_ptr+0x000061e0+4*14))=0xd5e44f5e;
*((unsigned int *)((unsigned long)context_ptr+0x000061e0+4*15))=0x3b83e703;
*((unsigned int *)((unsigned long)context_ptr+0x000061e0+4*16))=0x00e3c966;
*((unsigned int *)((unsigned long)context_ptr+0x000061e0+4*17))=0x8a2be094;
*((unsigned int *)((unsigned long)context_ptr+0x000061e0+4*18))=0x13bbdc2a;
*((unsigned int *)((unsigned long)context_ptr+0x000061e0+4*19))=0xd3cea7f4;
*((unsigned int *)((unsigned long)context_ptr+0x000061e0+4*20))=0x39e12861;
*((unsigned int *)((unsigned long)context_ptr+0x000061e0+4*21))=0x5feb27e5;
*((unsigned int *)((unsigned long)context_ptr+0x000061e0+4*22))=0x0a0dbe79;
*((unsigned int *)((unsigned long)context_ptr+0x000061e0+4*23))=0x05aa128f;
*((unsigned int *)((unsigned long)context_ptr+0x000061e0+4*24))=0x98b86e1c;
*((unsigned int *)((unsigned long)context_ptr+0x000061e0+4*25))=0x2ab5d46b;
*((unsigned int *)((unsigned long)context_ptr+0x000061e0+4*26))=0x00000016;
*((unsigned int *)((unsigned long)context_ptr+0x000039c0))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x000039c0+4*1))=0x00006360;
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
*((unsigned int *)((unsigned long)context_ptr+0x000009c0+4*1))=0x000061e0;
*((unsigned int *)((unsigned long)context_ptr+0x000009c0+4*2))=0x000063f8;
*((unsigned int *)((unsigned long)context_ptr+0x000009c0+4*3))=0x02220069;
*((unsigned int *)((unsigned long)context_ptr+0x000009c0+4*4))=0x0e60f68f;
*((unsigned int *)((unsigned long)context_ptr+0x000009c0+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000222&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006038,"\xc7\x83\xc3\x67\x2e\xbd\x58\x94\xd0\xe7\x1c\x62\x95\xcb\x34\xe3",16))
printf("strip: c783c3672ebd5894, Pass\n");
else
printf("strip: c783c3672ebd5894, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006038))=0x006a0802;
*((unsigned int *)((unsigned long)context_ptr+0x00006038+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006038+4*2))=0x0202006a;
*((unsigned int *)((unsigned long)context_ptr+0x00006038+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x00006730))=0xc6b45e44;
*((unsigned int *)((unsigned long)context_ptr+0x00006730+4*1))=0x5a0f37de;
*((unsigned int *)((unsigned long)context_ptr+0x00006730+4*2))=0x9219b648;
*((unsigned int *)((unsigned long)context_ptr+0x00006730+4*3))=0xe6784636;
*((unsigned int *)((unsigned long)context_ptr+0x00006730+4*4))=0x1b400a84;
*((unsigned int *)((unsigned long)context_ptr+0x00006730+4*5))=0xa5d958f6;
*((unsigned int *)((unsigned long)context_ptr+0x00006730+4*6))=0x39df63e7;
*((unsigned int *)((unsigned long)context_ptr+0x00006730+4*7))=0x1806fb9f;
*((unsigned int *)((unsigned long)context_ptr+0x00006730+4*8))=0x8fec395e;
*((unsigned int *)((unsigned long)context_ptr+0x00006730+4*9))=0xa6132433;
*((unsigned int *)((unsigned long)context_ptr+0x00006730+4*10))=0x6ac70adc;
*((unsigned int *)((unsigned long)context_ptr+0x00006730+4*11))=0xbacb2f08;
*((unsigned int *)((unsigned long)context_ptr+0x00006730+4*12))=0x52bfb066;
*((unsigned int *)((unsigned long)context_ptr+0x00006730+4*13))=0xb9d9f37f;
*((unsigned int *)((unsigned long)context_ptr+0x00006730+4*14))=0x31c47899;
*((unsigned int *)((unsigned long)context_ptr+0x00006730+4*15))=0x0f06b14a;
*((unsigned int *)((unsigned long)context_ptr+0x00006730+4*16))=0xabb63cc9;
*((unsigned int *)((unsigned long)context_ptr+0x00006730+4*17))=0x01c3dc01;
*((unsigned int *)((unsigned long)context_ptr+0x00006730+4*18))=0x73e5dc05;
*((unsigned int *)((unsigned long)context_ptr+0x00006730+4*19))=0xb06f2c27;
*((unsigned int *)((unsigned long)context_ptr+0x00006730+4*20))=0xc310c08e;
*((unsigned int *)((unsigned long)context_ptr+0x00006730+4*21))=0x47d2ce45;
*((unsigned int *)((unsigned long)context_ptr+0x00006730+4*22))=0xc9f501d3;
*((unsigned int *)((unsigned long)context_ptr+0x00006730+4*23))=0x65c6d483;
*((unsigned int *)((unsigned long)context_ptr+0x00006730+4*24))=0xd922a088;
*((unsigned int *)((unsigned long)context_ptr+0x00006730+4*25))=0xfced0d0e;
*((unsigned int *)((unsigned long)context_ptr+0x00006730+4*26))=0x0000479f;
*((unsigned int *)((unsigned long)context_ptr+0x000039d8))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x000039d8+4*1))=0x0000624c;
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
*((unsigned int *)((unsigned long)context_ptr+0x000009d8+4*1))=0x00006730;
*((unsigned int *)((unsigned long)context_ptr+0x000009d8+4*2))=0x00006038;
*((unsigned int *)((unsigned long)context_ptr+0x000009d8+4*3))=0x0222006a;
*((unsigned int *)((unsigned long)context_ptr+0x000009d8+4*4))=0x02e00499;
*((unsigned int *)((unsigned long)context_ptr+0x000009d8+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000228&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006408,"\x55\xbd\xec\x44\x03\x28\xf0\xf9\x9d\x9f\x68\xf3\xbf\xb8\xa7\x20",16))
printf("strip: 55bdec440328f0f9, Pass\n");
else
printf("strip: 55bdec440328f0f9, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006408))=0x006a0802;
*((unsigned int *)((unsigned long)context_ptr+0x00006408+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006408+4*2))=0x0202006b;
*((unsigned int *)((unsigned long)context_ptr+0x00006408+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x000068b8))=0x5a3a3989;
*((unsigned int *)((unsigned long)context_ptr+0x000068b8+4*1))=0x8f0f0bd4;
*((unsigned int *)((unsigned long)context_ptr+0x000068b8+4*2))=0x96f3c2a7;
*((unsigned int *)((unsigned long)context_ptr+0x000068b8+4*3))=0x055a56af;
*((unsigned int *)((unsigned long)context_ptr+0x000068b8+4*4))=0x1b1882f9;
*((unsigned int *)((unsigned long)context_ptr+0x000068b8+4*5))=0x25b89624;
*((unsigned int *)((unsigned long)context_ptr+0x000068b8+4*6))=0x993ca260;
*((unsigned int *)((unsigned long)context_ptr+0x000068b8+4*7))=0x8c94a455;
*((unsigned int *)((unsigned long)context_ptr+0x000068b8+4*8))=0x2859dc1e;
*((unsigned int *)((unsigned long)context_ptr+0x000068b8+4*9))=0x7337d8c2;
*((unsigned int *)((unsigned long)context_ptr+0x000068b8+4*10))=0xa7655795;
*((unsigned int *)((unsigned long)context_ptr+0x000068b8+4*11))=0x05e0a0ef;
*((unsigned int *)((unsigned long)context_ptr+0x000068b8+4*12))=0x72de848a;
*((unsigned int *)((unsigned long)context_ptr+0x000068b8+4*13))=0x5e7abdc0;
*((unsigned int *)((unsigned long)context_ptr+0x000068b8+4*14))=0xe0816722;
*((unsigned int *)((unsigned long)context_ptr+0x000068b8+4*15))=0x2f1049bd;
*((unsigned int *)((unsigned long)context_ptr+0x000068b8+4*16))=0xc7d129c1;
*((unsigned int *)((unsigned long)context_ptr+0x000068b8+4*17))=0x8274542d;
*((unsigned int *)((unsigned long)context_ptr+0x000068b8+4*18))=0x1b1e16c4;
*((unsigned int *)((unsigned long)context_ptr+0x000068b8+4*19))=0xcf1b67b4;
*((unsigned int *)((unsigned long)context_ptr+0x000068b8+4*20))=0x35d1d21f;
*((unsigned int *)((unsigned long)context_ptr+0x000068b8+4*21))=0xca525d9b;
*((unsigned int *)((unsigned long)context_ptr+0x000068b8+4*22))=0x5e91474c;
*((unsigned int *)((unsigned long)context_ptr+0x000068b8+4*23))=0xedaebd92;
*((unsigned int *)((unsigned long)context_ptr+0x000068b8+4*24))=0xe8f3810c;
*((unsigned int *)((unsigned long)context_ptr+0x000068b8+4*25))=0x8c542f83;
*((unsigned int *)((unsigned long)context_ptr+0x000068b8+4*26))=0x00d251bc;
*((unsigned int *)((unsigned long)context_ptr+0x000039f0))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x000039f0+4*1))=0x00006028;
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
*((unsigned int *)((unsigned long)context_ptr+0x000009f0+4*1))=0x000068b8;
*((unsigned int *)((unsigned long)context_ptr+0x000009f0+4*2))=0x00006408;
*((unsigned int *)((unsigned long)context_ptr+0x000009f0+4*3))=0x0222006b;
*((unsigned int *)((unsigned long)context_ptr+0x000009f0+4*4))=0x0a1b0bc0;
*((unsigned int *)((unsigned long)context_ptr+0x000009f0+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000022e&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006418,"\xf2\x53\x7d\xae\xcd\x39\xac\xe0\xe6\x14\xc6\xdd\x84\xfa\xc0\x6e",16))
printf("strip: f2537daecd39ace0, Pass\n");
else
printf("strip: f2537daecd39ace0, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006418))=0x006a0802;
*((unsigned int *)((unsigned long)context_ptr+0x00006418+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006418+4*2))=0x0202006c;
*((unsigned int *)((unsigned long)context_ptr+0x00006418+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x00006924))=0x021e6a0c;
*((unsigned int *)((unsigned long)context_ptr+0x00006924+4*1))=0x8029f730;
*((unsigned int *)((unsigned long)context_ptr+0x00006924+4*2))=0xba3937ab;
*((unsigned int *)((unsigned long)context_ptr+0x00006924+4*3))=0x099afd4f;
*((unsigned int *)((unsigned long)context_ptr+0x00006924+4*4))=0x176b9f0c;
*((unsigned int *)((unsigned long)context_ptr+0x00006924+4*5))=0xcaecf7e6;
*((unsigned int *)((unsigned long)context_ptr+0x00006924+4*6))=0x0e6d0441;
*((unsigned int *)((unsigned long)context_ptr+0x00006924+4*7))=0xfbe2799a;
*((unsigned int *)((unsigned long)context_ptr+0x00006924+4*8))=0xac176e20;
*((unsigned int *)((unsigned long)context_ptr+0x00006924+4*9))=0xdc26f88c;
*((unsigned int *)((unsigned long)context_ptr+0x00006924+4*10))=0x71c65d7b;
*((unsigned int *)((unsigned long)context_ptr+0x00006924+4*11))=0x76f7f69b;
*((unsigned int *)((unsigned long)context_ptr+0x00006924+4*12))=0x3b946332;
*((unsigned int *)((unsigned long)context_ptr+0x00006924+4*13))=0xee461c0a;
*((unsigned int *)((unsigned long)context_ptr+0x00006924+4*14))=0x7ba1fbfe;
*((unsigned int *)((unsigned long)context_ptr+0x00006924+4*15))=0x4c8f9bce;
*((unsigned int *)((unsigned long)context_ptr+0x00006924+4*16))=0xc8fefcf4;
*((unsigned int *)((unsigned long)context_ptr+0x00006924+4*17))=0xbe668afd;
*((unsigned int *)((unsigned long)context_ptr+0x00006924+4*18))=0x86bb680a;
*((unsigned int *)((unsigned long)context_ptr+0x00006924+4*19))=0x1fdf8107;
*((unsigned int *)((unsigned long)context_ptr+0x00006924+4*20))=0xc5995c3a;
*((unsigned int *)((unsigned long)context_ptr+0x00006924+4*21))=0xb5011898;
*((unsigned int *)((unsigned long)context_ptr+0x00006924+4*22))=0x2b846429;
*((unsigned int *)((unsigned long)context_ptr+0x00006924+4*23))=0x14778fb3;
*((unsigned int *)((unsigned long)context_ptr+0x00006924+4*24))=0x00e07d7a;
*((unsigned int *)((unsigned long)context_ptr+0x00006924+4*25))=0x232040bc;
*((unsigned int *)((unsigned long)context_ptr+0x00006924+4*26))=0x4977132c;
*((unsigned int *)((unsigned long)context_ptr+0x00003a08))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003a08+4*1))=0x00006048;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000a08+4*1))=0x00006924;
*((unsigned int *)((unsigned long)context_ptr+0x00000a08+4*2))=0x00006418;
*((unsigned int *)((unsigned long)context_ptr+0x00000a08+4*3))=0x0222006c;
*((unsigned int *)((unsigned long)context_ptr+0x00000a08+4*4))=0x0ba03b42;
*((unsigned int *)((unsigned long)context_ptr+0x00000a08+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000234&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000062c0,"\x85\x7f\x28\x2e\xcf\x25\x5e\x83\x79\x49\x4c\xaa\x61\xea\xbe\x6f",16))
printf("strip: 857f282ecf255e83, Pass\n");
else
printf("strip: 857f282ecf255e83, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006058))=0x006a0802;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*2))=0x0202006d;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x0000625c))=0xedabf803;
*((unsigned int *)((unsigned long)context_ptr+0x0000625c+4*1))=0xc044e22a;
*((unsigned int *)((unsigned long)context_ptr+0x0000625c+4*2))=0x14d1e4e4;
*((unsigned int *)((unsigned long)context_ptr+0x0000625c+4*3))=0x7a458ff3;
*((unsigned int *)((unsigned long)context_ptr+0x0000625c+4*4))=0xc890bfde;
*((unsigned int *)((unsigned long)context_ptr+0x0000625c+4*5))=0xcb0f6dec;
*((unsigned int *)((unsigned long)context_ptr+0x0000625c+4*6))=0xe6dcad3a;
*((unsigned int *)((unsigned long)context_ptr+0x0000625c+4*7))=0x5db2be0c;
*((unsigned int *)((unsigned long)context_ptr+0x0000625c+4*8))=0xe1332b9a;
*((unsigned int *)((unsigned long)context_ptr+0x0000625c+4*9))=0xb9afbc42;
*((unsigned int *)((unsigned long)context_ptr+0x0000625c+4*10))=0x980e8a47;
*((unsigned int *)((unsigned long)context_ptr+0x0000625c+4*11))=0x32b6f31d;
*((unsigned int *)((unsigned long)context_ptr+0x0000625c+4*12))=0x9a10747f;
*((unsigned int *)((unsigned long)context_ptr+0x0000625c+4*13))=0x22155732;
*((unsigned int *)((unsigned long)context_ptr+0x0000625c+4*14))=0xaf0375a7;
*((unsigned int *)((unsigned long)context_ptr+0x0000625c+4*15))=0x80c037bd;
*((unsigned int *)((unsigned long)context_ptr+0x0000625c+4*16))=0x2eb81a37;
*((unsigned int *)((unsigned long)context_ptr+0x0000625c+4*17))=0xe09bdeb3;
*((unsigned int *)((unsigned long)context_ptr+0x0000625c+4*18))=0xfd9cd956;
*((unsigned int *)((unsigned long)context_ptr+0x0000625c+4*19))=0xb36ba076;
*((unsigned int *)((unsigned long)context_ptr+0x0000625c+4*20))=0x05d91b31;
*((unsigned int *)((unsigned long)context_ptr+0x0000625c+4*21))=0x2a92eb59;
*((unsigned int *)((unsigned long)context_ptr+0x0000625c+4*22))=0x9d73e272;
*((unsigned int *)((unsigned long)context_ptr+0x0000625c+4*23))=0x47b1d068;
*((unsigned int *)((unsigned long)context_ptr+0x0000625c+4*24))=0x9254934b;
*((unsigned int *)((unsigned long)context_ptr+0x0000625c+4*25))=0x82dff9c3;
*((unsigned int *)((unsigned long)context_ptr+0x0000625c+4*26))=0x5a6e3058;
*((unsigned int *)((unsigned long)context_ptr+0x0000625c+4*27))=0x00000047;
*((unsigned int *)((unsigned long)context_ptr+0x00003a20))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003a20+4*1))=0x00006370;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000a20+4*1))=0x0000625c;
*((unsigned int *)((unsigned long)context_ptr+0x00000a20+4*2))=0x00006058;
*((unsigned int *)((unsigned long)context_ptr+0x00000a20+4*3))=0x0222006d;
*((unsigned int *)((unsigned long)context_ptr+0x00000a20+4*4))=0x0e00db30;
*((unsigned int *)((unsigned long)context_ptr+0x00000a20+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000023a&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000062d0,"\x70\x2a\x4a\xe9\x08\xd2\xa8\xe1\xbd\x18\x99\x58\xac\xa8\xdc\xbd",16))
printf("strip: 702a4ae908d2a8e1, Pass\n");
else
printf("strip: 702a4ae908d2a8e1, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006068))=0x006a0802;
*((unsigned int *)((unsigned long)context_ptr+0x00006068+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006068+4*2))=0x0202006e;
*((unsigned int *)((unsigned long)context_ptr+0x00006068+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x000065e8))=0xc42d0f40;
*((unsigned int *)((unsigned long)context_ptr+0x000065e8+4*1))=0x71595ed7;
*((unsigned int *)((unsigned long)context_ptr+0x000065e8+4*2))=0x8e569126;
*((unsigned int *)((unsigned long)context_ptr+0x000065e8+4*3))=0x5b7c6f3d;
*((unsigned int *)((unsigned long)context_ptr+0x000065e8+4*4))=0x1e84b054;
*((unsigned int *)((unsigned long)context_ptr+0x000065e8+4*5))=0x1f31b45b;
*((unsigned int *)((unsigned long)context_ptr+0x000065e8+4*6))=0x4105aa35;
*((unsigned int *)((unsigned long)context_ptr+0x000065e8+4*7))=0x6ef4b2db;
*((unsigned int *)((unsigned long)context_ptr+0x000065e8+4*8))=0xe4cebf1f;
*((unsigned int *)((unsigned long)context_ptr+0x000065e8+4*9))=0x770019af;
*((unsigned int *)((unsigned long)context_ptr+0x000065e8+4*10))=0xee1f29c8;
*((unsigned int *)((unsigned long)context_ptr+0x000065e8+4*11))=0xe7716dbd;
*((unsigned int *)((unsigned long)context_ptr+0x000065e8+4*12))=0x9b8f08be;
*((unsigned int *)((unsigned long)context_ptr+0x000065e8+4*13))=0x9093b34d;
*((unsigned int *)((unsigned long)context_ptr+0x000065e8+4*14))=0x054e62ae;
*((unsigned int *)((unsigned long)context_ptr+0x000065e8+4*15))=0x42cddbb8;
*((unsigned int *)((unsigned long)context_ptr+0x000065e8+4*16))=0xa54ceabd;
*((unsigned int *)((unsigned long)context_ptr+0x000065e8+4*17))=0xc24728bf;
*((unsigned int *)((unsigned long)context_ptr+0x000065e8+4*18))=0x290c2ea2;
*((unsigned int *)((unsigned long)context_ptr+0x000065e8+4*19))=0xd052be32;
*((unsigned int *)((unsigned long)context_ptr+0x000065e8+4*20))=0x03dd4042;
*((unsigned int *)((unsigned long)context_ptr+0x000065e8+4*21))=0xac7cea4b;
*((unsigned int *)((unsigned long)context_ptr+0x000065e8+4*22))=0xa3baf79a;
*((unsigned int *)((unsigned long)context_ptr+0x000065e8+4*23))=0x4d9a034d;
*((unsigned int *)((unsigned long)context_ptr+0x000065e8+4*24))=0xc1c0d6c2;
*((unsigned int *)((unsigned long)context_ptr+0x000065e8+4*25))=0xeb77a6f3;
*((unsigned int *)((unsigned long)context_ptr+0x000065e8+4*26))=0x25234784;
*((unsigned int *)((unsigned long)context_ptr+0x000065e8+4*27))=0x00002d19;
*((unsigned int *)((unsigned long)context_ptr+0x00003a38))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003a38+4*1))=0x000062cc;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000a38+4*1))=0x000065e8;
*((unsigned int *)((unsigned long)context_ptr+0x00000a38+4*2))=0x00006068;
*((unsigned int *)((unsigned long)context_ptr+0x00000a38+4*3))=0x0222006e;
*((unsigned int *)((unsigned long)context_ptr+0x00000a38+4*4))=0x004920c6;
*((unsigned int *)((unsigned long)context_ptr+0x00000a38+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000240&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006488,"\x8e\xb0\xac\xfb\x19\xb6\x9d\x9e\xa5\xb5\xe1\x02\xdb\xe6\xcd\x1a",16))
printf("strip: 8eb0acfb19b69d9e, Pass\n");
else
printf("strip: 8eb0acfb19b69d9e, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000062dc))=0x006a0802;
*((unsigned int *)((unsigned long)context_ptr+0x000062dc+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000062dc+4*2))=0x0202006f;
*((unsigned int *)((unsigned long)context_ptr+0x000062dc+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x00006428))=0x4be945ff;
*((unsigned int *)((unsigned long)context_ptr+0x00006428+4*1))=0x2d4cb604;
*((unsigned int *)((unsigned long)context_ptr+0x00006428+4*2))=0x54a24989;
*((unsigned int *)((unsigned long)context_ptr+0x00006428+4*3))=0x8a77db66;
*((unsigned int *)((unsigned long)context_ptr+0x00006428+4*4))=0x9d9abc00;
*((unsigned int *)((unsigned long)context_ptr+0x00006428+4*5))=0xffdfccaf;
*((unsigned int *)((unsigned long)context_ptr+0x00006428+4*6))=0x37238fa9;
*((unsigned int *)((unsigned long)context_ptr+0x00006428+4*7))=0xead897fb;
*((unsigned int *)((unsigned long)context_ptr+0x00006428+4*8))=0xad51787c;
*((unsigned int *)((unsigned long)context_ptr+0x00006428+4*9))=0xa41cd3f1;
*((unsigned int *)((unsigned long)context_ptr+0x00006428+4*10))=0xfa197161;
*((unsigned int *)((unsigned long)context_ptr+0x00006428+4*11))=0xd4c56373;
*((unsigned int *)((unsigned long)context_ptr+0x00006428+4*12))=0xa43f6aa8;
*((unsigned int *)((unsigned long)context_ptr+0x00006428+4*13))=0xe11dae58;
*((unsigned int *)((unsigned long)context_ptr+0x00006428+4*14))=0x5153bbe1;
*((unsigned int *)((unsigned long)context_ptr+0x00006428+4*15))=0x71b04b96;
*((unsigned int *)((unsigned long)context_ptr+0x00006428+4*16))=0x7edb0348;
*((unsigned int *)((unsigned long)context_ptr+0x00006428+4*17))=0x8ac07902;
*((unsigned int *)((unsigned long)context_ptr+0x00006428+4*18))=0xa56e6462;
*((unsigned int *)((unsigned long)context_ptr+0x00006428+4*19))=0xee1ecefa;
*((unsigned int *)((unsigned long)context_ptr+0x00006428+4*20))=0x95f9654b;
*((unsigned int *)((unsigned long)context_ptr+0x00006428+4*21))=0x2eeae00b;
*((unsigned int *)((unsigned long)context_ptr+0x00006428+4*22))=0x4cfee03f;
*((unsigned int *)((unsigned long)context_ptr+0x00006428+4*23))=0xbcfce445;
*((unsigned int *)((unsigned long)context_ptr+0x00006428+4*24))=0xc3f85b25;
*((unsigned int *)((unsigned long)context_ptr+0x00006428+4*25))=0x3e6e8251;
*((unsigned int *)((unsigned long)context_ptr+0x00006428+4*26))=0x0e6506a3;
*((unsigned int *)((unsigned long)context_ptr+0x00006428+4*27))=0x00f8d3f1;
*((unsigned int *)((unsigned long)context_ptr+0x00003a50))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003a50+4*1))=0x0000679c;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000a50+4*1))=0x00006428;
*((unsigned int *)((unsigned long)context_ptr+0x00000a50+4*2))=0x000062dc;
*((unsigned int *)((unsigned long)context_ptr+0x00000a50+4*3))=0x0222006f;
*((unsigned int *)((unsigned long)context_ptr+0x00000a50+4*4))=0x0720a059;
*((unsigned int *)((unsigned long)context_ptr+0x00000a50+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000246&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006700,"\xbb\xc2\xf8\xec\x36\x08\xa6\x8b\x4c\x2b\xfd\xa1\x8c\xa1\xc4\x72",16))
printf("strip: bbc2f8ec3608a68b, Pass\n");
else
printf("strip: bbc2f8ec3608a68b, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000062ec))=0x006a0802;
*((unsigned int *)((unsigned long)context_ptr+0x000062ec+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000062ec+4*2))=0x02020070;
*((unsigned int *)((unsigned long)context_ptr+0x000062ec+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x00006658))=0x73e0e0c9;
*((unsigned int *)((unsigned long)context_ptr+0x00006658+4*1))=0xf279ee3e;
*((unsigned int *)((unsigned long)context_ptr+0x00006658+4*2))=0xfa3868cd;
*((unsigned int *)((unsigned long)context_ptr+0x00006658+4*3))=0x4afe1856;
*((unsigned int *)((unsigned long)context_ptr+0x00006658+4*4))=0xf32ad774;
*((unsigned int *)((unsigned long)context_ptr+0x00006658+4*5))=0xa9fe2bb9;
*((unsigned int *)((unsigned long)context_ptr+0x00006658+4*6))=0x6306a335;
*((unsigned int *)((unsigned long)context_ptr+0x00006658+4*7))=0x825de32c;
*((unsigned int *)((unsigned long)context_ptr+0x00006658+4*8))=0x8930c2f0;
*((unsigned int *)((unsigned long)context_ptr+0x00006658+4*9))=0xeaee9f69;
*((unsigned int *)((unsigned long)context_ptr+0x00006658+4*10))=0xab9403b2;
*((unsigned int *)((unsigned long)context_ptr+0x00006658+4*11))=0x5a6100ca;
*((unsigned int *)((unsigned long)context_ptr+0x00006658+4*12))=0xa22240a4;
*((unsigned int *)((unsigned long)context_ptr+0x00006658+4*13))=0xfa11425e;
*((unsigned int *)((unsigned long)context_ptr+0x00006658+4*14))=0x054c40a4;
*((unsigned int *)((unsigned long)context_ptr+0x00006658+4*15))=0xe32861c9;
*((unsigned int *)((unsigned long)context_ptr+0x00006658+4*16))=0xc3c81c33;
*((unsigned int *)((unsigned long)context_ptr+0x00006658+4*17))=0x1ab43009;
*((unsigned int *)((unsigned long)context_ptr+0x00006658+4*18))=0xdc54a9bb;
*((unsigned int *)((unsigned long)context_ptr+0x00006658+4*19))=0x0cd518ea;
*((unsigned int *)((unsigned long)context_ptr+0x00006658+4*20))=0x3a208eac;
*((unsigned int *)((unsigned long)context_ptr+0x00006658+4*21))=0x2a3c2b10;
*((unsigned int *)((unsigned long)context_ptr+0x00006658+4*22))=0xe58c438c;
*((unsigned int *)((unsigned long)context_ptr+0x00006658+4*23))=0xb92132af;
*((unsigned int *)((unsigned long)context_ptr+0x00006658+4*24))=0x9ee8d43b;
*((unsigned int *)((unsigned long)context_ptr+0x00006658+4*25))=0x19944148;
*((unsigned int *)((unsigned long)context_ptr+0x00006658+4*26))=0xac92d56a;
*((unsigned int *)((unsigned long)context_ptr+0x00006658+4*27))=0x8c9a2288;
*((unsigned int *)((unsigned long)context_ptr+0x00003a68))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003a68+4*1))=0x000067ac;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000a68+4*1))=0x00006658;
*((unsigned int *)((unsigned long)context_ptr+0x00000a68+4*2))=0x000062ec;
*((unsigned int *)((unsigned long)context_ptr+0x00000a68+4*3))=0x02220070;
*((unsigned int *)((unsigned long)context_ptr+0x00000a68+4*4))=0x0f718370;
*((unsigned int *)((unsigned long)context_ptr+0x00000a68+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000024c&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006300,"\x48\xb4\x05\x4b\xae\x5f\xad\xa4\x36\x83\x4f\x5f\x8f\xe8\xb4\xe0",16))
printf("strip: 48b4054bae5fada4, Pass\n");
else
printf("strip: 48b4054bae5fada4, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000062fc))=0x006a0802;
*((unsigned int *)((unsigned long)context_ptr+0x000062fc+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000062fc+4*2))=0x02020071;
*((unsigned int *)((unsigned long)context_ptr+0x000062fc+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x000067bc))=0xf6f4f839;
*((unsigned int *)((unsigned long)context_ptr+0x000067bc+4*1))=0x523e12b3;
*((unsigned int *)((unsigned long)context_ptr+0x000067bc+4*2))=0x53a0b61a;
*((unsigned int *)((unsigned long)context_ptr+0x000067bc+4*3))=0x94074384;
*((unsigned int *)((unsigned long)context_ptr+0x000067bc+4*4))=0x72764791;
*((unsigned int *)((unsigned long)context_ptr+0x000067bc+4*5))=0xebe354e7;
*((unsigned int *)((unsigned long)context_ptr+0x000067bc+4*6))=0x7e97ed1e;
*((unsigned int *)((unsigned long)context_ptr+0x000067bc+4*7))=0x4f075893;
*((unsigned int *)((unsigned long)context_ptr+0x000067bc+4*8))=0xdfd41397;
*((unsigned int *)((unsigned long)context_ptr+0x000067bc+4*9))=0xd4b74270;
*((unsigned int *)((unsigned long)context_ptr+0x000067bc+4*10))=0x1ec952a9;
*((unsigned int *)((unsigned long)context_ptr+0x000067bc+4*11))=0xa00b6956;
*((unsigned int *)((unsigned long)context_ptr+0x000067bc+4*12))=0xc4a069c8;
*((unsigned int *)((unsigned long)context_ptr+0x000067bc+4*13))=0xef40f5c2;
*((unsigned int *)((unsigned long)context_ptr+0x000067bc+4*14))=0xeb5bc58a;
*((unsigned int *)((unsigned long)context_ptr+0x000067bc+4*15))=0xee07ce62;
*((unsigned int *)((unsigned long)context_ptr+0x000067bc+4*16))=0x7c65d35c;
*((unsigned int *)((unsigned long)context_ptr+0x000067bc+4*17))=0xe2ed0336;
*((unsigned int *)((unsigned long)context_ptr+0x000067bc+4*18))=0x5cea9541;
*((unsigned int *)((unsigned long)context_ptr+0x000067bc+4*19))=0x9e849399;
*((unsigned int *)((unsigned long)context_ptr+0x000067bc+4*20))=0xb74b1c1d;
*((unsigned int *)((unsigned long)context_ptr+0x000067bc+4*21))=0x79cb0063;
*((unsigned int *)((unsigned long)context_ptr+0x000067bc+4*22))=0x09c9b062;
*((unsigned int *)((unsigned long)context_ptr+0x000067bc+4*23))=0x87ba2a38;
*((unsigned int *)((unsigned long)context_ptr+0x000067bc+4*24))=0x03578f2d;
*((unsigned int *)((unsigned long)context_ptr+0x000067bc+4*25))=0xb2efeeef;
*((unsigned int *)((unsigned long)context_ptr+0x000067bc+4*26))=0x10af28cd;
*((unsigned int *)((unsigned long)context_ptr+0x000067bc+4*27))=0xf582bb55;
*((unsigned int *)((unsigned long)context_ptr+0x000067bc+4*28))=0x0000004a;
*((unsigned int *)((unsigned long)context_ptr+0x00003a80))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003a80+4*1))=0x00006830;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000a80+4*1))=0x000067bc;
*((unsigned int *)((unsigned long)context_ptr+0x00000a80+4*2))=0x000062fc;
*((unsigned int *)((unsigned long)context_ptr+0x00000a80+4*3))=0x02220071;
*((unsigned int *)((unsigned long)context_ptr+0x00000a80+4*4))=0x0ec58cdb;
*((unsigned int *)((unsigned long)context_ptr+0x00000a80+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000252&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006310,"\x91\x8a\x49\x0c\x3c\x2b\xb7\x39\x45\xab\x18\xc9\x25\xe6\x3c\x4f",16))
printf("strip: 918a490c3c2bb739, Pass\n");
else
printf("strip: 918a490c3c2bb739, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x0000630c))=0x006a0802;
*((unsigned int *)((unsigned long)context_ptr+0x0000630c+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x0000630c+4*2))=0x02020072;
*((unsigned int *)((unsigned long)context_ptr+0x0000630c+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x00006840))=0x21ce44c6;
*((unsigned int *)((unsigned long)context_ptr+0x00006840+4*1))=0x5a3ba199;
*((unsigned int *)((unsigned long)context_ptr+0x00006840+4*2))=0x21ab67d3;
*((unsigned int *)((unsigned long)context_ptr+0x00006840+4*3))=0x6d159cf9;
*((unsigned int *)((unsigned long)context_ptr+0x00006840+4*4))=0x2b4a3be4;
*((unsigned int *)((unsigned long)context_ptr+0x00006840+4*5))=0x47cb593b;
*((unsigned int *)((unsigned long)context_ptr+0x00006840+4*6))=0xe2608f68;
*((unsigned int *)((unsigned long)context_ptr+0x00006840+4*7))=0x9000ec93;
*((unsigned int *)((unsigned long)context_ptr+0x00006840+4*8))=0xc5338530;
*((unsigned int *)((unsigned long)context_ptr+0x00006840+4*9))=0x9b843721;
*((unsigned int *)((unsigned long)context_ptr+0x00006840+4*10))=0x07b508b5;
*((unsigned int *)((unsigned long)context_ptr+0x00006840+4*11))=0x61002732;
*((unsigned int *)((unsigned long)context_ptr+0x00006840+4*12))=0xa3120658;
*((unsigned int *)((unsigned long)context_ptr+0x00006840+4*13))=0x2bfbd80a;
*((unsigned int *)((unsigned long)context_ptr+0x00006840+4*14))=0x5fb94323;
*((unsigned int *)((unsigned long)context_ptr+0x00006840+4*15))=0x0a523b6e;
*((unsigned int *)((unsigned long)context_ptr+0x00006840+4*16))=0x559a46b6;
*((unsigned int *)((unsigned long)context_ptr+0x00006840+4*17))=0x204dbb92;
*((unsigned int *)((unsigned long)context_ptr+0x00006840+4*18))=0x0c3ffeba;
*((unsigned int *)((unsigned long)context_ptr+0x00006840+4*19))=0x22ea5eb4;
*((unsigned int *)((unsigned long)context_ptr+0x00006840+4*20))=0x78fa8225;
*((unsigned int *)((unsigned long)context_ptr+0x00006840+4*21))=0xffe52d68;
*((unsigned int *)((unsigned long)context_ptr+0x00006840+4*22))=0x9dcd8023;
*((unsigned int *)((unsigned long)context_ptr+0x00006840+4*23))=0x2487cf39;
*((unsigned int *)((unsigned long)context_ptr+0x00006840+4*24))=0xe0493dc6;
*((unsigned int *)((unsigned long)context_ptr+0x00006840+4*25))=0xb1e6af93;
*((unsigned int *)((unsigned long)context_ptr+0x00006840+4*26))=0x92b279d0;
*((unsigned int *)((unsigned long)context_ptr+0x00006840+4*27))=0x524523be;
*((unsigned int *)((unsigned long)context_ptr+0x00006840+4*28))=0x000035c8;
*((unsigned int *)((unsigned long)context_ptr+0x00003a98))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003a98+4*1))=0x000066c8;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000a98+4*2))=0x0000630c;
*((unsigned int *)((unsigned long)context_ptr+0x00000a98+4*3))=0x02220072;
*((unsigned int *)((unsigned long)context_ptr+0x00000a98+4*4))=0x08601de3;
*((unsigned int *)((unsigned long)context_ptr+0x00000a98+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000258&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006710,"\xb7\x03\xcf\x41\xce\xbf\xcf\x9a\x18\xf1\xcf\x3c\x17\x6e\x0d\xec",16))
printf("strip: b703cf41cebfcf9a, Pass\n");
else
printf("strip: b703cf41cebfcf9a, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x0000631c))=0x006a0802;
*((unsigned int *)((unsigned long)context_ptr+0x0000631c+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x0000631c+4*2))=0x02020073;
*((unsigned int *)((unsigned long)context_ptr+0x0000631c+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x00006500))=0xc1672deb;
*((unsigned int *)((unsigned long)context_ptr+0x00006500+4*1))=0x517e5113;
*((unsigned int *)((unsigned long)context_ptr+0x00006500+4*2))=0xf0315093;
*((unsigned int *)((unsigned long)context_ptr+0x00006500+4*3))=0x61e63a05;
*((unsigned int *)((unsigned long)context_ptr+0x00006500+4*4))=0x29e2f27d;
*((unsigned int *)((unsigned long)context_ptr+0x00006500+4*5))=0x10ffbff7;
*((unsigned int *)((unsigned long)context_ptr+0x00006500+4*6))=0x079ef2f5;
*((unsigned int *)((unsigned long)context_ptr+0x00006500+4*7))=0xe5866614;
*((unsigned int *)((unsigned long)context_ptr+0x00006500+4*8))=0x2755f119;
*((unsigned int *)((unsigned long)context_ptr+0x00006500+4*9))=0x9da99c86;
*((unsigned int *)((unsigned long)context_ptr+0x00006500+4*10))=0xf5b7c0c7;
*((unsigned int *)((unsigned long)context_ptr+0x00006500+4*11))=0x51216a43;
*((unsigned int *)((unsigned long)context_ptr+0x00006500+4*12))=0x991a4a39;
*((unsigned int *)((unsigned long)context_ptr+0x00006500+4*13))=0xaf3b8256;
*((unsigned int *)((unsigned long)context_ptr+0x00006500+4*14))=0x5f6ef8ab;
*((unsigned int *)((unsigned long)context_ptr+0x00006500+4*15))=0xdca87a08;
*((unsigned int *)((unsigned long)context_ptr+0x00006500+4*16))=0x3dbf69e7;
*((unsigned int *)((unsigned long)context_ptr+0x00006500+4*17))=0x52cc3ef9;
*((unsigned int *)((unsigned long)context_ptr+0x00006500+4*18))=0x672f4d42;
*((unsigned int *)((unsigned long)context_ptr+0x00006500+4*19))=0x0c68224a;
*((unsigned int *)((unsigned long)context_ptr+0x00006500+4*20))=0x9e21a5e4;
*((unsigned int *)((unsigned long)context_ptr+0x00006500+4*21))=0x2f085b36;
*((unsigned int *)((unsigned long)context_ptr+0x00006500+4*22))=0x12c8f800;
*((unsigned int *)((unsigned long)context_ptr+0x00006500+4*23))=0xd045cd91;
*((unsigned int *)((unsigned long)context_ptr+0x00006500+4*24))=0x8f37638b;
*((unsigned int *)((unsigned long)context_ptr+0x00006500+4*25))=0xbb3a48aa;
*((unsigned int *)((unsigned long)context_ptr+0x00006500+4*26))=0x3b02864e;
*((unsigned int *)((unsigned long)context_ptr+0x00006500+4*27))=0xf72be13d;
*((unsigned int *)((unsigned long)context_ptr+0x00006500+4*28))=0x003a1b35;
*((unsigned int *)((unsigned long)context_ptr+0x00003ab0))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003ab0+4*1))=0x000066d8;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000ab0+4*1))=0x00006500;
*((unsigned int *)((unsigned long)context_ptr+0x00000ab0+4*2))=0x0000631c;
*((unsigned int *)((unsigned long)context_ptr+0x00000ab0+4*3))=0x02220073;
*((unsigned int *)((unsigned long)context_ptr+0x00000ab0+4*4))=0x027b69e7;
*((unsigned int *)((unsigned long)context_ptr+0x00000ab0+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000025e&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006720,"\xc0\x7f\x66\x66\xad\xef\x89\x59\x1b\xaf\x80\x84\xb3\x29\x18\x76",16))
printf("strip: c07f6666adef8959, Pass\n");
else
printf("strip: c07f6666adef8959, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x0000632c))=0x006a0802;
*((unsigned int *)((unsigned long)context_ptr+0x0000632c+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x0000632c+4*2))=0x02020074;
*((unsigned int *)((unsigned long)context_ptr+0x0000632c+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x00006574))=0x40b46645;
*((unsigned int *)((unsigned long)context_ptr+0x00006574+4*1))=0x3a755a47;
*((unsigned int *)((unsigned long)context_ptr+0x00006574+4*2))=0xe2971cff;
*((unsigned int *)((unsigned long)context_ptr+0x00006574+4*3))=0x8b3670fa;
*((unsigned int *)((unsigned long)context_ptr+0x00006574+4*4))=0x3e922cdd;
*((unsigned int *)((unsigned long)context_ptr+0x00006574+4*5))=0x02f5a65a;
*((unsigned int *)((unsigned long)context_ptr+0x00006574+4*6))=0x77a7df0e;
*((unsigned int *)((unsigned long)context_ptr+0x00006574+4*7))=0xdd6b143e;
*((unsigned int *)((unsigned long)context_ptr+0x00006574+4*8))=0x67a15bdc;
*((unsigned int *)((unsigned long)context_ptr+0x00006574+4*9))=0x117e3b10;
*((unsigned int *)((unsigned long)context_ptr+0x00006574+4*10))=0x5c96e513;
*((unsigned int *)((unsigned long)context_ptr+0x00006574+4*11))=0xd71539f2;
*((unsigned int *)((unsigned long)context_ptr+0x00006574+4*12))=0xdd13edc5;
*((unsigned int *)((unsigned long)context_ptr+0x00006574+4*13))=0x547ce0f0;
*((unsigned int *)((unsigned long)context_ptr+0x00006574+4*14))=0x4fd249d0;
*((unsigned int *)((unsigned long)context_ptr+0x00006574+4*15))=0xb5d6de30;
*((unsigned int *)((unsigned long)context_ptr+0x00006574+4*16))=0x9cd878e7;
*((unsigned int *)((unsigned long)context_ptr+0x00006574+4*17))=0xc9dc7008;
*((unsigned int *)((unsigned long)context_ptr+0x00006574+4*18))=0x41e853d7;
*((unsigned int *)((unsigned long)context_ptr+0x00006574+4*19))=0xcf0d1730;
*((unsigned int *)((unsigned long)context_ptr+0x00006574+4*20))=0x6a936cac;
*((unsigned int *)((unsigned long)context_ptr+0x00006574+4*21))=0x613aa6e6;
*((unsigned int *)((unsigned long)context_ptr+0x00006574+4*22))=0x41b793b0;
*((unsigned int *)((unsigned long)context_ptr+0x00006574+4*23))=0x44fe370b;
*((unsigned int *)((unsigned long)context_ptr+0x00006574+4*24))=0x2284a7e6;
*((unsigned int *)((unsigned long)context_ptr+0x00006574+4*25))=0x2ab09992;
*((unsigned int *)((unsigned long)context_ptr+0x00006574+4*26))=0x94d9d77d;
*((unsigned int *)((unsigned long)context_ptr+0x00006574+4*27))=0xb4e7a35e;
*((unsigned int *)((unsigned long)context_ptr+0x00006574+4*28))=0x0c551f87;
*((unsigned int *)((unsigned long)context_ptr+0x00003ac8))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003ac8+4*1))=0x000066e8;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000ac8+4*1))=0x00006574;
*((unsigned int *)((unsigned long)context_ptr+0x00000ac8+4*2))=0x0000632c;
*((unsigned int *)((unsigned long)context_ptr+0x00000ac8+4*3))=0x02220074;
*((unsigned int *)((unsigned long)context_ptr+0x00000ac8+4*4))=0x04791460;
*((unsigned int *)((unsigned long)context_ptr+0x00000ac8+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000264&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006148,"\x0b\xbc\x69\x26\x2d\xc1\x7a\xfd\x3a\xe0\xb0\xe3\xcd\x0f\x4f\xf1",16))
printf("strip: 0bbc69262dc17afd, Pass\n");
else
printf("strip: 0bbc69262dc17afd, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x0000633c))=0x006a0802;
*((unsigned int *)((unsigned long)context_ptr+0x0000633c+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x0000633c+4*2))=0x02020075;
*((unsigned int *)((unsigned long)context_ptr+0x0000633c+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x00006078))=0x35ce52e9;
*((unsigned int *)((unsigned long)context_ptr+0x00006078+4*1))=0xa2457cc0;
*((unsigned int *)((unsigned long)context_ptr+0x00006078+4*2))=0xfb90d11c;
*((unsigned int *)((unsigned long)context_ptr+0x00006078+4*3))=0x9d24c9ed;
*((unsigned int *)((unsigned long)context_ptr+0x00006078+4*4))=0x24f2af2b;
*((unsigned int *)((unsigned long)context_ptr+0x00006078+4*5))=0xa9518e20;
*((unsigned int *)((unsigned long)context_ptr+0x00006078+4*6))=0xfd2ab048;
*((unsigned int *)((unsigned long)context_ptr+0x00006078+4*7))=0xdef9fa77;
*((unsigned int *)((unsigned long)context_ptr+0x00006078+4*8))=0xae6d8568;
*((unsigned int *)((unsigned long)context_ptr+0x00006078+4*9))=0x33e46a4e;
*((unsigned int *)((unsigned long)context_ptr+0x00006078+4*10))=0xdf823a6c;
*((unsigned int *)((unsigned long)context_ptr+0x00006078+4*11))=0x6008b4a1;
*((unsigned int *)((unsigned long)context_ptr+0x00006078+4*12))=0x003d5a3c;
*((unsigned int *)((unsigned long)context_ptr+0x00006078+4*13))=0x9945ab6f;
*((unsigned int *)((unsigned long)context_ptr+0x00006078+4*14))=0x75b0e468;
*((unsigned int *)((unsigned long)context_ptr+0x00006078+4*15))=0xbf8e80be;
*((unsigned int *)((unsigned long)context_ptr+0x00006078+4*16))=0xb7c8799f;
*((unsigned int *)((unsigned long)context_ptr+0x00006078+4*17))=0x1e021eb3;
*((unsigned int *)((unsigned long)context_ptr+0x00006078+4*18))=0x255f74bb;
*((unsigned int *)((unsigned long)context_ptr+0x00006078+4*19))=0x62796387;
*((unsigned int *)((unsigned long)context_ptr+0x00006078+4*20))=0x09053681;
*((unsigned int *)((unsigned long)context_ptr+0x00006078+4*21))=0xb4f17fd2;
*((unsigned int *)((unsigned long)context_ptr+0x00006078+4*22))=0xd23c0597;
*((unsigned int *)((unsigned long)context_ptr+0x00006078+4*23))=0xb799c6f0;
*((unsigned int *)((unsigned long)context_ptr+0x00006078+4*24))=0xd03d8ce8;
*((unsigned int *)((unsigned long)context_ptr+0x00006078+4*25))=0x5dd95db1;
*((unsigned int *)((unsigned long)context_ptr+0x00006078+4*26))=0xcd676f57;
*((unsigned int *)((unsigned long)context_ptr+0x00006078+4*27))=0x946cfe04;
*((unsigned int *)((unsigned long)context_ptr+0x00006078+4*28))=0x5419d4e1;
*((unsigned int *)((unsigned long)context_ptr+0x00006078+4*29))=0x0000005b;
*((unsigned int *)((unsigned long)context_ptr+0x00003ae0))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003ae0+4*1))=0x000066f8;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000ae0+4*1))=0x00006078;
*((unsigned int *)((unsigned long)context_ptr+0x00000ae0+4*2))=0x0000633c;
*((unsigned int *)((unsigned long)context_ptr+0x00000ae0+4*3))=0x02220075;
*((unsigned int *)((unsigned long)context_ptr+0x00000ae0+4*4))=0x0e9f9cb9;
*((unsigned int *)((unsigned long)context_ptr+0x00000ae0+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000026a&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000061c0,"\x35\xe2\x2e\x36\x46\x5e\x32\x3d\x4d\x4e\xf1\x15\x9d\xf0\xcf\xc7",16))
printf("strip: 35e22e36465e323d, Pass\n");
else
printf("strip: 35e22e36465e323d, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006708))=0x006a0802;
*((unsigned int *)((unsigned long)context_ptr+0x00006708+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006708+4*2))=0x02020076;
*((unsigned int *)((unsigned long)context_ptr+0x00006708+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x00006380))=0xfa926a0c;
*((unsigned int *)((unsigned long)context_ptr+0x00006380+4*1))=0xdce9c0be;
*((unsigned int *)((unsigned long)context_ptr+0x00006380+4*2))=0x6f2573d6;
*((unsigned int *)((unsigned long)context_ptr+0x00006380+4*3))=0x9b7c7019;
*((unsigned int *)((unsigned long)context_ptr+0x00006380+4*4))=0x8edeedf2;
*((unsigned int *)((unsigned long)context_ptr+0x00006380+4*5))=0xc825c9c7;
*((unsigned int *)((unsigned long)context_ptr+0x00006380+4*6))=0xbd178865;
*((unsigned int *)((unsigned long)context_ptr+0x00006380+4*7))=0xa300585a;
*((unsigned int *)((unsigned long)context_ptr+0x00006380+4*8))=0xd091bf99;
*((unsigned int *)((unsigned long)context_ptr+0x00006380+4*9))=0xc0ce85e7;
*((unsigned int *)((unsigned long)context_ptr+0x00006380+4*10))=0x324f416a;
*((unsigned int *)((unsigned long)context_ptr+0x00006380+4*11))=0xe21bebfa;
*((unsigned int *)((unsigned long)context_ptr+0x00006380+4*12))=0x231c7eb9;
*((unsigned int *)((unsigned long)context_ptr+0x00006380+4*13))=0x430585f6;
*((unsigned int *)((unsigned long)context_ptr+0x00006380+4*14))=0xbddb640d;
*((unsigned int *)((unsigned long)context_ptr+0x00006380+4*15))=0x4f558362;
*((unsigned int *)((unsigned long)context_ptr+0x00006380+4*16))=0xb7ca8548;
*((unsigned int *)((unsigned long)context_ptr+0x00006380+4*17))=0x742a9f27;
*((unsigned int *)((unsigned long)context_ptr+0x00006380+4*18))=0x691fb8d0;
*((unsigned int *)((unsigned long)context_ptr+0x00006380+4*19))=0x5a5a8adc;
*((unsigned int *)((unsigned long)context_ptr+0x00006380+4*20))=0xcdb7216e;
*((unsigned int *)((unsigned long)context_ptr+0x00006380+4*21))=0x5de42198;
*((unsigned int *)((unsigned long)context_ptr+0x00006380+4*22))=0xb05cf8f9;
*((unsigned int *)((unsigned long)context_ptr+0x00006380+4*23))=0x922fd1e0;
*((unsigned int *)((unsigned long)context_ptr+0x00006380+4*24))=0x600dd4cb;
*((unsigned int *)((unsigned long)context_ptr+0x00006380+4*25))=0x1a1a9ca5;
*((unsigned int *)((unsigned long)context_ptr+0x00006380+4*26))=0xb641daeb;
*((unsigned int *)((unsigned long)context_ptr+0x00006380+4*27))=0x74ec2077;
*((unsigned int *)((unsigned long)context_ptr+0x00006380+4*28))=0x05f8571a;
*((unsigned int *)((unsigned long)context_ptr+0x00006380+4*29))=0x0000a68f;
*((unsigned int *)((unsigned long)context_ptr+0x00003af8))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003af8+4*1))=0x00006718;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000af8+4*1))=0x00006380;
*((unsigned int *)((unsigned long)context_ptr+0x00000af8+4*2))=0x00006708;
*((unsigned int *)((unsigned long)context_ptr+0x00000af8+4*3))=0x02220076;
*((unsigned int *)((unsigned long)context_ptr+0x00000af8+4*4))=0x0f12cc34;
*((unsigned int *)((unsigned long)context_ptr+0x00000af8+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000270&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000061d0,"\xc7\xb4\xa8\xfb\x96\x0b\x25\xdc\x36\x1a\xda\x43\xb8\x8b\x91\x9c",16))
printf("strip: c7b4a8fb960b25dc, Pass\n");
else
printf("strip: c7b4a8fb960b25dc, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x0000634c))=0x006a0802;
*((unsigned int *)((unsigned long)context_ptr+0x0000634c+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x0000634c+4*2))=0x02020077;
*((unsigned int *)((unsigned long)context_ptr+0x0000634c+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x000060f0))=0xb4fa0503;
*((unsigned int *)((unsigned long)context_ptr+0x000060f0+4*1))=0xef525b2e;
*((unsigned int *)((unsigned long)context_ptr+0x000060f0+4*2))=0x3c5580b9;
*((unsigned int *)((unsigned long)context_ptr+0x000060f0+4*3))=0x9eba4e9e;
*((unsigned int *)((unsigned long)context_ptr+0x000060f0+4*4))=0xe62101f0;
*((unsigned int *)((unsigned long)context_ptr+0x000060f0+4*5))=0xa764bc5b;
*((unsigned int *)((unsigned long)context_ptr+0x000060f0+4*6))=0x97dc0e45;
*((unsigned int *)((unsigned long)context_ptr+0x000060f0+4*7))=0x11c44eb6;
*((unsigned int *)((unsigned long)context_ptr+0x000060f0+4*8))=0x09c2fffc;
*((unsigned int *)((unsigned long)context_ptr+0x000060f0+4*9))=0xa0641905;
*((unsigned int *)((unsigned long)context_ptr+0x000060f0+4*10))=0xbb0a7e7f;
*((unsigned int *)((unsigned long)context_ptr+0x000060f0+4*11))=0x879577a7;
*((unsigned int *)((unsigned long)context_ptr+0x000060f0+4*12))=0x61afbeb5;
*((unsigned int *)((unsigned long)context_ptr+0x000060f0+4*13))=0x0453900c;
*((unsigned int *)((unsigned long)context_ptr+0x000060f0+4*14))=0x7595206e;
*((unsigned int *)((unsigned long)context_ptr+0x000060f0+4*15))=0xe96bfcce;
*((unsigned int *)((unsigned long)context_ptr+0x000060f0+4*16))=0x8a5d82fb;
*((unsigned int *)((unsigned long)context_ptr+0x000060f0+4*17))=0x065737f9;
*((unsigned int *)((unsigned long)context_ptr+0x000060f0+4*18))=0xd7267ce5;
*((unsigned int *)((unsigned long)context_ptr+0x000060f0+4*19))=0x2241fe7d;
*((unsigned int *)((unsigned long)context_ptr+0x000060f0+4*20))=0x52c991f5;
*((unsigned int *)((unsigned long)context_ptr+0x000060f0+4*21))=0x1b8efa40;
*((unsigned int *)((unsigned long)context_ptr+0x000060f0+4*22))=0x6583b9aa;
*((unsigned int *)((unsigned long)context_ptr+0x000060f0+4*23))=0xcfc8247f;
*((unsigned int *)((unsigned long)context_ptr+0x000060f0+4*24))=0xd90e0ba5;
*((unsigned int *)((unsigned long)context_ptr+0x000060f0+4*25))=0xc31cc0ea;
*((unsigned int *)((unsigned long)context_ptr+0x000060f0+4*26))=0x638d843b;
*((unsigned int *)((unsigned long)context_ptr+0x000060f0+4*27))=0x69cc0557;
*((unsigned int *)((unsigned long)context_ptr+0x000060f0+4*28))=0x5ce7a353;
*((unsigned int *)((unsigned long)context_ptr+0x000060f0+4*29))=0x003d39df;
*((unsigned int *)((unsigned long)context_ptr+0x00003b10))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003b10+4*1))=0x00006498;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000b10+4*1))=0x000060f0;
*((unsigned int *)((unsigned long)context_ptr+0x00000b10+4*2))=0x0000634c;
*((unsigned int *)((unsigned long)context_ptr+0x00000b10+4*3))=0x02220077;
*((unsigned int *)((unsigned long)context_ptr+0x00000b10+4*4))=0x07714d47;
*((unsigned int *)((unsigned long)context_ptr+0x00000b10+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000276&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006360,"\x3c\xea\x87\x79\x52\x12\xcf\xaa\x6d\x07\x98\xba\x6b\xa4\x0a\xd8",16))
printf("strip: 3cea87795212cfaa, Pass\n");
else
printf("strip: 3cea87795212cfaa, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000063f8))=0x006a0802;
*((unsigned int *)((unsigned long)context_ptr+0x000063f8+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000063f8+4*2))=0x02020078;
*((unsigned int *)((unsigned long)context_ptr+0x000063f8+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x00006168))=0x9fa4ce29;
*((unsigned int *)((unsigned long)context_ptr+0x00006168+4*1))=0x6f118fcf;
*((unsigned int *)((unsigned long)context_ptr+0x00006168+4*2))=0x3c663b8c;
*((unsigned int *)((unsigned long)context_ptr+0x00006168+4*3))=0x2e7c46c7;
*((unsigned int *)((unsigned long)context_ptr+0x00006168+4*4))=0xcc5bbd8f;
*((unsigned int *)((unsigned long)context_ptr+0x00006168+4*5))=0x7435495f;
*((unsigned int *)((unsigned long)context_ptr+0x00006168+4*6))=0xae180999;
*((unsigned int *)((unsigned long)context_ptr+0x00006168+4*7))=0x51b5551e;
*((unsigned int *)((unsigned long)context_ptr+0x00006168+4*8))=0x9688c451;
*((unsigned int *)((unsigned long)context_ptr+0x00006168+4*9))=0xbe5decee;
*((unsigned int *)((unsigned long)context_ptr+0x00006168+4*10))=0xa9012dc1;
*((unsigned int *)((unsigned long)context_ptr+0x00006168+4*11))=0xd4cecce7;
*((unsigned int *)((unsigned long)context_ptr+0x00006168+4*12))=0x7bd4d99c;
*((unsigned int *)((unsigned long)context_ptr+0x00006168+4*13))=0x24a3fa21;
*((unsigned int *)((unsigned long)context_ptr+0x00006168+4*14))=0x95d385f5;
*((unsigned int *)((unsigned long)context_ptr+0x00006168+4*15))=0x66fec2b4;
*((unsigned int *)((unsigned long)context_ptr+0x00006168+4*16))=0xa8e90b81;
*((unsigned int *)((unsigned long)context_ptr+0x00006168+4*17))=0x3611e097;
*((unsigned int *)((unsigned long)context_ptr+0x00006168+4*18))=0xd548edfc;
*((unsigned int *)((unsigned long)context_ptr+0x00006168+4*19))=0x9dbc6236;
*((unsigned int *)((unsigned long)context_ptr+0x00006168+4*20))=0x4f372caa;
*((unsigned int *)((unsigned long)context_ptr+0x00006168+4*21))=0xe9564470;
*((unsigned int *)((unsigned long)context_ptr+0x00006168+4*22))=0xf8c3fea3;
*((unsigned int *)((unsigned long)context_ptr+0x00006168+4*23))=0x56349ebe;
*((unsigned int *)((unsigned long)context_ptr+0x00006168+4*24))=0xd0f904de;
*((unsigned int *)((unsigned long)context_ptr+0x00006168+4*25))=0x6918d83c;
*((unsigned int *)((unsigned long)context_ptr+0x00006168+4*26))=0x6c10dacd;
*((unsigned int *)((unsigned long)context_ptr+0x00006168+4*27))=0xf25f68cd;
*((unsigned int *)((unsigned long)context_ptr+0x00006168+4*28))=0x869f3d24;
*((unsigned int *)((unsigned long)context_ptr+0x00006168+4*29))=0xc5953159;
*((unsigned int *)((unsigned long)context_ptr+0x00003b28))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003b28+4*1))=0x0000635c;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000b28+4*1))=0x00006168;
*((unsigned int *)((unsigned long)context_ptr+0x00000b28+4*2))=0x000063f8;
*((unsigned int *)((unsigned long)context_ptr+0x00000b28+4*3))=0x02220078;
*((unsigned int *)((unsigned long)context_ptr+0x00000b28+4*4))=0x07a30e5f;
*((unsigned int *)((unsigned long)context_ptr+0x00000b28+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000027c&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x0000624c,"\xbf\x9e\x82\xe3\xc4\x54\x7a\x24\xc6\xbe\x31\x05\x49\x29\x4e\x83",16))
printf("strip: bf9e82e3c4547a24, Pass\n");
else
printf("strip: bf9e82e3c4547a24, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006038))=0x006a0802;
*((unsigned int *)((unsigned long)context_ptr+0x00006038+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006038+4*2))=0x02020079;
*((unsigned int *)((unsigned long)context_ptr+0x00006038+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x000061e0))=0x815644db;
*((unsigned int *)((unsigned long)context_ptr+0x000061e0+4*1))=0x94f04ad2;
*((unsigned int *)((unsigned long)context_ptr+0x000061e0+4*2))=0xb08673fe;
*((unsigned int *)((unsigned long)context_ptr+0x000061e0+4*3))=0xfb9088bc;
*((unsigned int *)((unsigned long)context_ptr+0x000061e0+4*4))=0xc252ea90;
*((unsigned int *)((unsigned long)context_ptr+0x000061e0+4*5))=0xe4066998;
*((unsigned int *)((unsigned long)context_ptr+0x000061e0+4*6))=0x49d1de7d;
*((unsigned int *)((unsigned long)context_ptr+0x000061e0+4*7))=0xd5acd69a;
*((unsigned int *)((unsigned long)context_ptr+0x000061e0+4*8))=0xde152b74;
*((unsigned int *)((unsigned long)context_ptr+0x000061e0+4*9))=0x9854a427;
*((unsigned int *)((unsigned long)context_ptr+0x000061e0+4*10))=0x1a354373;
*((unsigned int *)((unsigned long)context_ptr+0x000061e0+4*11))=0xcfc64b89;
*((unsigned int *)((unsigned long)context_ptr+0x000061e0+4*12))=0xe4bfc260;
*((unsigned int *)((unsigned long)context_ptr+0x000061e0+4*13))=0xfc2fe2b6;
*((unsigned int *)((unsigned long)context_ptr+0x000061e0+4*14))=0x7dcbc749;
*((unsigned int *)((unsigned long)context_ptr+0x000061e0+4*15))=0x374e0ae9;
*((unsigned int *)((unsigned long)context_ptr+0x000061e0+4*16))=0x46328a09;
*((unsigned int *)((unsigned long)context_ptr+0x000061e0+4*17))=0x1e1cca92;
*((unsigned int *)((unsigned long)context_ptr+0x000061e0+4*18))=0x9e8407e0;
*((unsigned int *)((unsigned long)context_ptr+0x000061e0+4*19))=0xbee36712;
*((unsigned int *)((unsigned long)context_ptr+0x000061e0+4*20))=0x87b39cbe;
*((unsigned int *)((unsigned long)context_ptr+0x000061e0+4*21))=0xbcc3f135;
*((unsigned int *)((unsigned long)context_ptr+0x000061e0+4*22))=0xb19d3910;
*((unsigned int *)((unsigned long)context_ptr+0x000061e0+4*23))=0xe61b9172;
*((unsigned int *)((unsigned long)context_ptr+0x000061e0+4*24))=0x640f865d;
*((unsigned int *)((unsigned long)context_ptr+0x000061e0+4*25))=0xc6ca2c92;
*((unsigned int *)((unsigned long)context_ptr+0x000061e0+4*26))=0x633094f7;
*((unsigned int *)((unsigned long)context_ptr+0x000061e0+4*27))=0xa47168c4;
*((unsigned int *)((unsigned long)context_ptr+0x000061e0+4*28))=0x8997656e;
*((unsigned int *)((unsigned long)context_ptr+0x000061e0+4*29))=0xee19f837;
*((unsigned int *)((unsigned long)context_ptr+0x000061e0+4*30))=0x000000e1;
*((unsigned int *)((unsigned long)context_ptr+0x00003b40))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003b40+4*1))=0x000064a8;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000b40+4*1))=0x000061e0;
*((unsigned int *)((unsigned long)context_ptr+0x00000b40+4*2))=0x00006038;
*((unsigned int *)((unsigned long)context_ptr+0x00000b40+4*3))=0x02220079;
*((unsigned int *)((unsigned long)context_ptr+0x00000b40+4*4))=0x008311b7;
*((unsigned int *)((unsigned long)context_ptr+0x00000b40+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000282&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006028,"\xcc\xda\x83\xb5\x2a\x3b\xdc\x31\xf5\xd6\x11\x16\xd4\x90\xa5\x3b",16))
printf("strip: ccda83b52a3bdc31, Pass\n");
else
printf("strip: ccda83b52a3bdc31, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006028))=0x006a0802;
*((unsigned int *)((unsigned long)context_ptr+0x00006028+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006028+4*2))=0x0202007a;
*((unsigned int *)((unsigned long)context_ptr+0x00006028+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x00006990))=0xeef7434c;
*((unsigned int *)((unsigned long)context_ptr+0x00006990+4*1))=0x955bdcb1;
*((unsigned int *)((unsigned long)context_ptr+0x00006990+4*2))=0x82f6bd79;
*((unsigned int *)((unsigned long)context_ptr+0x00006990+4*3))=0x6287cc99;
*((unsigned int *)((unsigned long)context_ptr+0x00006990+4*4))=0x6a23bec5;
*((unsigned int *)((unsigned long)context_ptr+0x00006990+4*5))=0x0bfeb9be;
*((unsigned int *)((unsigned long)context_ptr+0x00006990+4*6))=0x490d30ba;
*((unsigned int *)((unsigned long)context_ptr+0x00006990+4*7))=0x0474e7bd;
*((unsigned int *)((unsigned long)context_ptr+0x00006990+4*8))=0x86d9f012;
*((unsigned int *)((unsigned long)context_ptr+0x00006990+4*9))=0x9342e832;
*((unsigned int *)((unsigned long)context_ptr+0x00006990+4*10))=0x8f03ccb9;
*((unsigned int *)((unsigned long)context_ptr+0x00006990+4*11))=0x0a7c9548;
*((unsigned int *)((unsigned long)context_ptr+0x00006990+4*12))=0xecaec5ff;
*((unsigned int *)((unsigned long)context_ptr+0x00006990+4*13))=0x0df82c97;
*((unsigned int *)((unsigned long)context_ptr+0x00006990+4*14))=0x8c54a40e;
*((unsigned int *)((unsigned long)context_ptr+0x00006990+4*15))=0x9eb46454;
*((unsigned int *)((unsigned long)context_ptr+0x00006990+4*16))=0xf46b56f0;
*((unsigned int *)((unsigned long)context_ptr+0x00006990+4*17))=0xc9ca1ce8;
*((unsigned int *)((unsigned long)context_ptr+0x00006990+4*18))=0x35ffb541;
*((unsigned int *)((unsigned long)context_ptr+0x00006990+4*19))=0x8334f6c4;
*((unsigned int *)((unsigned long)context_ptr+0x00006990+4*20))=0xaf9f80fb;
*((unsigned int *)((unsigned long)context_ptr+0x00006990+4*21))=0x1d33cc6c;
*((unsigned int *)((unsigned long)context_ptr+0x00006990+4*22))=0x66638abb;
*((unsigned int *)((unsigned long)context_ptr+0x00006990+4*23))=0x87f55b6a;
*((unsigned int *)((unsigned long)context_ptr+0x00006990+4*24))=0x64254ab7;
*((unsigned int *)((unsigned long)context_ptr+0x00006990+4*25))=0x3a9cb6ba;
*((unsigned int *)((unsigned long)context_ptr+0x00006990+4*26))=0x4b430dba;
*((unsigned int *)((unsigned long)context_ptr+0x00006990+4*27))=0x5197a314;
*((unsigned int *)((unsigned long)context_ptr+0x00006990+4*28))=0x8b3decdc;
*((unsigned int *)((unsigned long)context_ptr+0x00006990+4*29))=0xaa1937e7;
*((unsigned int *)((unsigned long)context_ptr+0x00006990+4*30))=0x00001ace;
*((unsigned int *)((unsigned long)context_ptr+0x00003b58))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003b58+4*1))=0x00006408;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000b58+4*1))=0x00006990;
*((unsigned int *)((unsigned long)context_ptr+0x00000b58+4*2))=0x00006028;
*((unsigned int *)((unsigned long)context_ptr+0x00000b58+4*3))=0x0222007a;
*((unsigned int *)((unsigned long)context_ptr+0x00000b58+4*4))=0x03ae688c;
*((unsigned int *)((unsigned long)context_ptr+0x00000b58+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000288&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006048,"\xd6\xde\x48\xee\x76\x95\xdc\x70\x04\x91\x20\x2b\x90\x22\x79\x16",16))
printf("strip: d6de48ee7695dc70, Pass\n");
else
printf("strip: d6de48ee7695dc70, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006048))=0x006a0802;
*((unsigned int *)((unsigned long)context_ptr+0x00006048+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006048+4*2))=0x0202007b;
*((unsigned int *)((unsigned long)context_ptr+0x00006048+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x000068b4))=0xc96001e2;
*((unsigned int *)((unsigned long)context_ptr+0x000068b4+4*1))=0x09390a3e;
*((unsigned int *)((unsigned long)context_ptr+0x000068b4+4*2))=0x447e4647;
*((unsigned int *)((unsigned long)context_ptr+0x000068b4+4*3))=0x3aa5f73c;
*((unsigned int *)((unsigned long)context_ptr+0x000068b4+4*4))=0x02dbaa81;
*((unsigned int *)((unsigned long)context_ptr+0x000068b4+4*5))=0xb33e34a0;
*((unsigned int *)((unsigned long)context_ptr+0x000068b4+4*6))=0x47b7ed20;
*((unsigned int *)((unsigned long)context_ptr+0x000068b4+4*7))=0x3390b336;
*((unsigned int *)((unsigned long)context_ptr+0x000068b4+4*8))=0xc85dcf1d;
*((unsigned int *)((unsigned long)context_ptr+0x000068b4+4*9))=0xad39ec7f;
*((unsigned int *)((unsigned long)context_ptr+0x000068b4+4*10))=0x2bec3285;
*((unsigned int *)((unsigned long)context_ptr+0x000068b4+4*11))=0xc60ef9f2;
*((unsigned int *)((unsigned long)context_ptr+0x000068b4+4*12))=0x96ba378a;
*((unsigned int *)((unsigned long)context_ptr+0x000068b4+4*13))=0xc2f39a5e;
*((unsigned int *)((unsigned long)context_ptr+0x000068b4+4*14))=0xc89b926c;
*((unsigned int *)((unsigned long)context_ptr+0x000068b4+4*15))=0x76b443d6;
*((unsigned int *)((unsigned long)context_ptr+0x000068b4+4*16))=0x000de5b5;
*((unsigned int *)((unsigned long)context_ptr+0x000068b4+4*17))=0x62601678;
*((unsigned int *)((unsigned long)context_ptr+0x000068b4+4*18))=0x7119073a;
*((unsigned int *)((unsigned long)context_ptr+0x000068b4+4*19))=0xd2980157;
*((unsigned int *)((unsigned long)context_ptr+0x000068b4+4*20))=0x83b7ff74;
*((unsigned int *)((unsigned long)context_ptr+0x000068b4+4*21))=0xa25593d6;
*((unsigned int *)((unsigned long)context_ptr+0x000068b4+4*22))=0xc13d8a8a;
*((unsigned int *)((unsigned long)context_ptr+0x000068b4+4*23))=0xda565abd;
*((unsigned int *)((unsigned long)context_ptr+0x000068b4+4*24))=0x91636532;
*((unsigned int *)((unsigned long)context_ptr+0x000068b4+4*25))=0xa964e91b;
*((unsigned int *)((unsigned long)context_ptr+0x000068b4+4*26))=0xb413d8e0;
*((unsigned int *)((unsigned long)context_ptr+0x000068b4+4*27))=0xf73457d8;
*((unsigned int *)((unsigned long)context_ptr+0x000068b4+4*28))=0x5281f84c;
*((unsigned int *)((unsigned long)context_ptr+0x000068b4+4*29))=0x0256a674;
*((unsigned int *)((unsigned long)context_ptr+0x000068b4+4*30))=0x006665f5;
*((unsigned int *)((unsigned long)context_ptr+0x00003b70))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003b70+4*1))=0x00006418;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000b70+4*1))=0x000068b4;
*((unsigned int *)((unsigned long)context_ptr+0x00000b70+4*2))=0x00006048;
*((unsigned int *)((unsigned long)context_ptr+0x00000b70+4*3))=0x0222007b;
*((unsigned int *)((unsigned long)context_ptr+0x00000b70+4*4))=0x0c8166c5;
*((unsigned int *)((unsigned long)context_ptr+0x00000b70+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000028e&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006370,"\xd1\x2c\x32\x7e\xc7\x71\x62\xe3\xfd\x22\xa0\xe7\xfa\x0a\xb6\xdd",16))
printf("strip: d12c327ec77162e3, Pass\n");
else
printf("strip: d12c327ec77162e3, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006058))=0x006a0802;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*2))=0x0202007c;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x00006a0c))=0x0e44a6bc;
*((unsigned int *)((unsigned long)context_ptr+0x00006a0c+4*1))=0x6bb79a89;
*((unsigned int *)((unsigned long)context_ptr+0x00006a0c+4*2))=0x7dbd8831;
*((unsigned int *)((unsigned long)context_ptr+0x00006a0c+4*3))=0x03431be6;
*((unsigned int *)((unsigned long)context_ptr+0x00006a0c+4*4))=0xe14c79cc;
*((unsigned int *)((unsigned long)context_ptr+0x00006a0c+4*5))=0x6beca2db;
*((unsigned int *)((unsigned long)context_ptr+0x00006a0c+4*6))=0xbbeb6a95;
*((unsigned int *)((unsigned long)context_ptr+0x00006a0c+4*7))=0x82e51889;
*((unsigned int *)((unsigned long)context_ptr+0x00006a0c+4*8))=0x7482b456;
*((unsigned int *)((unsigned long)context_ptr+0x00006a0c+4*9))=0x82ad08b7;
*((unsigned int *)((unsigned long)context_ptr+0x00006a0c+4*10))=0x03d4f0bf;
*((unsigned int *)((unsigned long)context_ptr+0x00006a0c+4*11))=0xef505a73;
*((unsigned int *)((unsigned long)context_ptr+0x00006a0c+4*12))=0x1d0996bf;
*((unsigned int *)((unsigned long)context_ptr+0x00006a0c+4*13))=0x78e2e66e;
*((unsigned int *)((unsigned long)context_ptr+0x00006a0c+4*14))=0x0abe7e29;
*((unsigned int *)((unsigned long)context_ptr+0x00006a0c+4*15))=0xf2a7c670;
*((unsigned int *)((unsigned long)context_ptr+0x00006a0c+4*16))=0x26bab66b;
*((unsigned int *)((unsigned long)context_ptr+0x00006a0c+4*17))=0x00958d60;
*((unsigned int *)((unsigned long)context_ptr+0x00006a0c+4*18))=0x53f989a7;
*((unsigned int *)((unsigned long)context_ptr+0x00006a0c+4*19))=0x2979864e;
*((unsigned int *)((unsigned long)context_ptr+0x00006a0c+4*20))=0x95861a7c;
*((unsigned int *)((unsigned long)context_ptr+0x00006a0c+4*21))=0x30e86ac6;
*((unsigned int *)((unsigned long)context_ptr+0x00006a0c+4*22))=0x044091be;
*((unsigned int *)((unsigned long)context_ptr+0x00006a0c+4*23))=0xad7d132a;
*((unsigned int *)((unsigned long)context_ptr+0x00006a0c+4*24))=0xafb4a67e;
*((unsigned int *)((unsigned long)context_ptr+0x00006a0c+4*25))=0x20d8c607;
*((unsigned int *)((unsigned long)context_ptr+0x00006a0c+4*26))=0x0a23a72d;
*((unsigned int *)((unsigned long)context_ptr+0x00006a0c+4*27))=0xa644a2ed;
*((unsigned int *)((unsigned long)context_ptr+0x00006a0c+4*28))=0xef1b6265;
*((unsigned int *)((unsigned long)context_ptr+0x00006a0c+4*29))=0xa5ebb370;
*((unsigned int *)((unsigned long)context_ptr+0x00006a0c+4*30))=0x5317a6b4;
*((unsigned int *)((unsigned long)context_ptr+0x00003b88))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003b88+4*1))=0x0000636c;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000b88+4*1))=0x00006a0c;
*((unsigned int *)((unsigned long)context_ptr+0x00000b88+4*2))=0x00006058;
*((unsigned int *)((unsigned long)context_ptr+0x00000b88+4*3))=0x0222007c;
*((unsigned int *)((unsigned long)context_ptr+0x00000b88+4*4))=0x040b60ff;
*((unsigned int *)((unsigned long)context_ptr+0x00000b88+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000294&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000062cc,"\x70\x25\xb1\x8b\xa5\x16\x9a\x85\xf0\xd3\x9d\xf5\x74\x22\xe0\xb7",16))
printf("strip: 7025b18ba5169a85, Pass\n");
else
printf("strip: 7025b18ba5169a85, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006068))=0x006a0802;
*((unsigned int *)((unsigned long)context_ptr+0x00006068+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006068+4*2))=0x0202007d;
*((unsigned int *)((unsigned long)context_ptr+0x00006068+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x0000625c))=0x01cc8026;
*((unsigned int *)((unsigned long)context_ptr+0x0000625c+4*1))=0x4240934d;
*((unsigned int *)((unsigned long)context_ptr+0x0000625c+4*2))=0x63e9a154;
*((unsigned int *)((unsigned long)context_ptr+0x0000625c+4*3))=0x6eeb459c;
*((unsigned int *)((unsigned long)context_ptr+0x0000625c+4*4))=0x14120b62;
*((unsigned int *)((unsigned long)context_ptr+0x0000625c+4*5))=0x10423c4f;
*((unsigned int *)((unsigned long)context_ptr+0x0000625c+4*6))=0x3013fe65;
*((unsigned int *)((unsigned long)context_ptr+0x0000625c+4*7))=0xecaa9227;
*((unsigned int *)((unsigned long)context_ptr+0x0000625c+4*8))=0x423ec346;
*((unsigned int *)((unsigned long)context_ptr+0x0000625c+4*9))=0x9445d50c;
*((unsigned int *)((unsigned long)context_ptr+0x0000625c+4*10))=0x44eb8718;
*((unsigned int *)((unsigned long)context_ptr+0x0000625c+4*11))=0x55542f99;
*((unsigned int *)((unsigned long)context_ptr+0x0000625c+4*12))=0x18726746;
*((unsigned int *)((unsigned long)context_ptr+0x0000625c+4*13))=0xb5922d81;
*((unsigned int *)((unsigned long)context_ptr+0x0000625c+4*14))=0x11eace5b;
*((unsigned int *)((unsigned long)context_ptr+0x0000625c+4*15))=0x0847d670;
*((unsigned int *)((unsigned long)context_ptr+0x0000625c+4*16))=0xdc1aef74;
*((unsigned int *)((unsigned long)context_ptr+0x0000625c+4*17))=0xd92f8280;
*((unsigned int *)((unsigned long)context_ptr+0x0000625c+4*18))=0xf592d3c5;
*((unsigned int *)((unsigned long)context_ptr+0x0000625c+4*19))=0xdb642eaa;
*((unsigned int *)((unsigned long)context_ptr+0x0000625c+4*20))=0x205098b4;
*((unsigned int *)((unsigned long)context_ptr+0x0000625c+4*21))=0x72e844ec;
*((unsigned int *)((unsigned long)context_ptr+0x0000625c+4*22))=0xa0211cb3;
*((unsigned int *)((unsigned long)context_ptr+0x0000625c+4*23))=0x50a89e7f;
*((unsigned int *)((unsigned long)context_ptr+0x0000625c+4*24))=0x25df0985;
*((unsigned int *)((unsigned long)context_ptr+0x0000625c+4*25))=0xda03232f;
*((unsigned int *)((unsigned long)context_ptr+0x0000625c+4*26))=0xa64f44c4;
*((unsigned int *)((unsigned long)context_ptr+0x0000625c+4*27))=0xcfd428b3;
*((unsigned int *)((unsigned long)context_ptr+0x0000625c+4*28))=0x190c08ab;
*((unsigned int *)((unsigned long)context_ptr+0x0000625c+4*29))=0x6745a0b2;
*((unsigned int *)((unsigned long)context_ptr+0x0000625c+4*30))=0xa7b34233;
*((unsigned int *)((unsigned long)context_ptr+0x0000625c+4*31))=0x00000029;
*((unsigned int *)((unsigned long)context_ptr+0x00003ba0))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003ba0+4*1))=0x000064b8;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000ba0+4*1))=0x0000625c;
*((unsigned int *)((unsigned long)context_ptr+0x00000ba0+4*2))=0x00006068;
*((unsigned int *)((unsigned long)context_ptr+0x00000ba0+4*3))=0x0222007d;
*((unsigned int *)((unsigned long)context_ptr+0x00000ba0+4*4))=0x0f3d986f;
*((unsigned int *)((unsigned long)context_ptr+0x00000ba0+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000029a&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x0000679c,"\xf8\xf9\x26\xc2\x1d\xbe\x4e\x7e\xb8\x9d\xec\x8b\x23\xae\x9f\xf2",16))
printf("strip: f8f926c21dbe4e7e, Pass\n");
else
printf("strip: f8f926c21dbe4e7e, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000062dc))=0x006a0802;
*((unsigned int *)((unsigned long)context_ptr+0x000062dc+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000062dc+4*2))=0x0202007e;
*((unsigned int *)((unsigned long)context_ptr+0x000062dc+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x00006728))=0x1e0aebbe;
*((unsigned int *)((unsigned long)context_ptr+0x00006728+4*1))=0x5cd43c5c;
*((unsigned int *)((unsigned long)context_ptr+0x00006728+4*2))=0xcb15a5a5;
*((unsigned int *)((unsigned long)context_ptr+0x00006728+4*3))=0x0ccc9aa7;
*((unsigned int *)((unsigned long)context_ptr+0x00006728+4*4))=0xdff789b4;
*((unsigned int *)((unsigned long)context_ptr+0x00006728+4*5))=0xd2e01261;
*((unsigned int *)((unsigned long)context_ptr+0x00006728+4*6))=0x65121a6b;
*((unsigned int *)((unsigned long)context_ptr+0x00006728+4*7))=0x644dc04f;
*((unsigned int *)((unsigned long)context_ptr+0x00006728+4*8))=0x38fb7cb4;
*((unsigned int *)((unsigned long)context_ptr+0x00006728+4*9))=0x092145b9;
*((unsigned int *)((unsigned long)context_ptr+0x00006728+4*10))=0xefe82262;
*((unsigned int *)((unsigned long)context_ptr+0x00006728+4*11))=0x58856b96;
*((unsigned int *)((unsigned long)context_ptr+0x00006728+4*12))=0x2dd59280;
*((unsigned int *)((unsigned long)context_ptr+0x00006728+4*13))=0x46e668e2;
*((unsigned int *)((unsigned long)context_ptr+0x00006728+4*14))=0x20c42aaf;
*((unsigned int *)((unsigned long)context_ptr+0x00006728+4*15))=0x89fa3469;
*((unsigned int *)((unsigned long)context_ptr+0x00006728+4*16))=0x44186a2c;
*((unsigned int *)((unsigned long)context_ptr+0x00006728+4*17))=0x81dae11f;
*((unsigned int *)((unsigned long)context_ptr+0x00006728+4*18))=0x330330b1;
*((unsigned int *)((unsigned long)context_ptr+0x00006728+4*19))=0x2743a16a;
*((unsigned int *)((unsigned long)context_ptr+0x00006728+4*20))=0xcda658ad;
*((unsigned int *)((unsigned long)context_ptr+0x00006728+4*21))=0x39cb5444;
*((unsigned int *)((unsigned long)context_ptr+0x00006728+4*22))=0x81da213f;
*((unsigned int *)((unsigned long)context_ptr+0x00006728+4*23))=0x4239d3c3;
*((unsigned int *)((unsigned long)context_ptr+0x00006728+4*24))=0xf4549957;
*((unsigned int *)((unsigned long)context_ptr+0x00006728+4*25))=0x55fe0b62;
*((unsigned int *)((unsigned long)context_ptr+0x00006728+4*26))=0x7b4b11a1;
*((unsigned int *)((unsigned long)context_ptr+0x00006728+4*27))=0xebde59c0;
*((unsigned int *)((unsigned long)context_ptr+0x00006728+4*28))=0x4d9394dd;
*((unsigned int *)((unsigned long)context_ptr+0x00006728+4*29))=0xb657071d;
*((unsigned int *)((unsigned long)context_ptr+0x00006728+4*30))=0x63ed7886;
*((unsigned int *)((unsigned long)context_ptr+0x00006728+4*31))=0x0000418a;
*((unsigned int *)((unsigned long)context_ptr+0x00003bb8))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003bb8+4*1))=0x000064c8;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000bb8+4*1))=0x00006728;
*((unsigned int *)((unsigned long)context_ptr+0x00000bb8+4*2))=0x000062dc;
*((unsigned int *)((unsigned long)context_ptr+0x00000bb8+4*3))=0x0222007e;
*((unsigned int *)((unsigned long)context_ptr+0x00000bb8+4*4))=0x0b409e72;
*((unsigned int *)((unsigned long)context_ptr+0x00000bb8+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000002a0&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000067ac,"\xf8\xf8\xaa\xf4\x03\x40\xd9\x2b\xaa\xe1\x54\xb8\x22\xd9\x84\x06",16))
printf("strip: f8f8aaf40340d92b, Pass\n");
else
printf("strip: f8f8aaf40340d92b, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000062ec))=0x006a0802;
*((unsigned int *)((unsigned long)context_ptr+0x000062ec+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000062ec+4*2))=0x0202007f;
*((unsigned int *)((unsigned long)context_ptr+0x000062ec+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x000065e8))=0x33a3e5f0;
*((unsigned int *)((unsigned long)context_ptr+0x000065e8+4*1))=0x266d49fb;
*((unsigned int *)((unsigned long)context_ptr+0x000065e8+4*2))=0xe79471f5;
*((unsigned int *)((unsigned long)context_ptr+0x000065e8+4*3))=0x2529b530;
*((unsigned int *)((unsigned long)context_ptr+0x000065e8+4*4))=0x335667ec;
*((unsigned int *)((unsigned long)context_ptr+0x000065e8+4*5))=0x02998124;
*((unsigned int *)((unsigned long)context_ptr+0x000065e8+4*6))=0xd3293760;
*((unsigned int *)((unsigned long)context_ptr+0x000065e8+4*7))=0x9c8e65b3;
*((unsigned int *)((unsigned long)context_ptr+0x000065e8+4*8))=0x8c439665;
*((unsigned int *)((unsigned long)context_ptr+0x000065e8+4*9))=0x75941bb5;
*((unsigned int *)((unsigned long)context_ptr+0x000065e8+4*10))=0xa2d3360b;
*((unsigned int *)((unsigned long)context_ptr+0x000065e8+4*11))=0x3853cfa5;
*((unsigned int *)((unsigned long)context_ptr+0x000065e8+4*12))=0x342b6bb5;
*((unsigned int *)((unsigned long)context_ptr+0x000065e8+4*13))=0x191d3042;
*((unsigned int *)((unsigned long)context_ptr+0x000065e8+4*14))=0xda4e75d9;
*((unsigned int *)((unsigned long)context_ptr+0x000065e8+4*15))=0x7df11a5c;
*((unsigned int *)((unsigned long)context_ptr+0x000065e8+4*16))=0xcecb1250;
*((unsigned int *)((unsigned long)context_ptr+0x000065e8+4*17))=0x5677f1fb;
*((unsigned int *)((unsigned long)context_ptr+0x000065e8+4*18))=0x602fbb5a;
*((unsigned int *)((unsigned long)context_ptr+0x000065e8+4*19))=0x2bce391f;
*((unsigned int *)((unsigned long)context_ptr+0x000065e8+4*20))=0x289b7a6c;
*((unsigned int *)((unsigned long)context_ptr+0x000065e8+4*21))=0x91b3faaa;
*((unsigned int *)((unsigned long)context_ptr+0x000065e8+4*22))=0xdaeb1083;
*((unsigned int *)((unsigned long)context_ptr+0x000065e8+4*23))=0xa2ce2d06;
*((unsigned int *)((unsigned long)context_ptr+0x000065e8+4*24))=0xd4a67cf2;
*((unsigned int *)((unsigned long)context_ptr+0x000065e8+4*25))=0x9d303d97;
*((unsigned int *)((unsigned long)context_ptr+0x000065e8+4*26))=0x5f42afcc;
*((unsigned int *)((unsigned long)context_ptr+0x000065e8+4*27))=0x3a01a087;
*((unsigned int *)((unsigned long)context_ptr+0x000065e8+4*28))=0xcdf2c3a7;
*((unsigned int *)((unsigned long)context_ptr+0x000065e8+4*29))=0x1e963bf4;
*((unsigned int *)((unsigned long)context_ptr+0x000065e8+4*30))=0xbcb03e9b;
*((unsigned int *)((unsigned long)context_ptr+0x000065e8+4*31))=0x006e0b7c;
*((unsigned int *)((unsigned long)context_ptr+0x00003bd0))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003bd0+4*1))=0x000067a8;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000bd0+4*1))=0x000065e8;
*((unsigned int *)((unsigned long)context_ptr+0x00000bd0+4*2))=0x000062ec;
*((unsigned int *)((unsigned long)context_ptr+0x00000bd0+4*3))=0x0222007f;
*((unsigned int *)((unsigned long)context_ptr+0x00000bd0+4*4))=0x0d64caef;
*((unsigned int *)((unsigned long)context_ptr+0x00000bd0+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000002a6&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006830,"\x0e\x32\x9e\xcd\xff\x19\x85\x4c\xbb\x61\x1e\x2b\x05\xdd\xc3\xb0",16))
printf("strip: 0e329ecdff19854c, Pass\n");
else
printf("strip: 0e329ecdff19854c, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000062fc))=0x006a0802;
*((unsigned int *)((unsigned long)context_ptr+0x000062fc+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000062fc+4*2))=0x02020080;
*((unsigned int *)((unsigned long)context_ptr+0x000062fc+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x000067b8))=0x9d68610e;
*((unsigned int *)((unsigned long)context_ptr+0x000067b8+4*1))=0x8674be16;
*((unsigned int *)((unsigned long)context_ptr+0x000067b8+4*2))=0xc2769ba7;
*((unsigned int *)((unsigned long)context_ptr+0x000067b8+4*3))=0x4871f85e;
*((unsigned int *)((unsigned long)context_ptr+0x000067b8+4*4))=0x0eded7a4;
*((unsigned int *)((unsigned long)context_ptr+0x000067b8+4*5))=0xecf7be6e;
*((unsigned int *)((unsigned long)context_ptr+0x000067b8+4*6))=0xa0bd9905;
*((unsigned int *)((unsigned long)context_ptr+0x000067b8+4*7))=0xbcad0e9d;
*((unsigned int *)((unsigned long)context_ptr+0x000067b8+4*8))=0x7960c646;
*((unsigned int *)((unsigned long)context_ptr+0x000067b8+4*9))=0x941aa03b;
*((unsigned int *)((unsigned long)context_ptr+0x000067b8+4*10))=0x8a933b55;
*((unsigned int *)((unsigned long)context_ptr+0x000067b8+4*11))=0xdab77b3b;
*((unsigned int *)((unsigned long)context_ptr+0x000067b8+4*12))=0x506f0012;
*((unsigned int *)((unsigned long)context_ptr+0x000067b8+4*13))=0xf3d95ae6;
*((unsigned int *)((unsigned long)context_ptr+0x000067b8+4*14))=0x192d4ce4;
*((unsigned int *)((unsigned long)context_ptr+0x000067b8+4*15))=0x408be758;
*((unsigned int *)((unsigned long)context_ptr+0x000067b8+4*16))=0xea550bbe;
*((unsigned int *)((unsigned long)context_ptr+0x000067b8+4*17))=0x94a1c243;
*((unsigned int *)((unsigned long)context_ptr+0x000067b8+4*18))=0x575195c8;
*((unsigned int *)((unsigned long)context_ptr+0x000067b8+4*19))=0x3607c31e;
*((unsigned int *)((unsigned long)context_ptr+0x000067b8+4*20))=0x95eba041;
*((unsigned int *)((unsigned long)context_ptr+0x000067b8+4*21))=0x6ed1e808;
*((unsigned int *)((unsigned long)context_ptr+0x000067b8+4*22))=0x957ff50d;
*((unsigned int *)((unsigned long)context_ptr+0x000067b8+4*23))=0x2008dcab;
*((unsigned int *)((unsigned long)context_ptr+0x000067b8+4*24))=0x9e9eb4d2;
*((unsigned int *)((unsigned long)context_ptr+0x000067b8+4*25))=0xfe253220;
*((unsigned int *)((unsigned long)context_ptr+0x000067b8+4*26))=0x4a08f450;
*((unsigned int *)((unsigned long)context_ptr+0x000067b8+4*27))=0x65546477;
*((unsigned int *)((unsigned long)context_ptr+0x000067b8+4*28))=0xc33ed15c;
*((unsigned int *)((unsigned long)context_ptr+0x000067b8+4*29))=0x144413db;
*((unsigned int *)((unsigned long)context_ptr+0x000067b8+4*30))=0x966a079f;
*((unsigned int *)((unsigned long)context_ptr+0x000067b8+4*31))=0x3eb1dd03;
*((unsigned int *)((unsigned long)context_ptr+0x00003be8))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003be8+4*1))=0x000064d8;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000be8+4*1))=0x000067b8;
*((unsigned int *)((unsigned long)context_ptr+0x00000be8+4*2))=0x000062fc;
*((unsigned int *)((unsigned long)context_ptr+0x00000be8+4*3))=0x02220080;
*((unsigned int *)((unsigned long)context_ptr+0x00000be8+4*4))=0x05afbc28;
*((unsigned int *)((unsigned long)context_ptr+0x00000be8+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000002ac&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000066c8,"\x55\xdc\x2f\x31\x36\x48\xea\x97\xdf\x69\x74\xfd\x59\xad\xf0\xa0",16))
printf("strip: 55dc2f313648ea97, Pass\n");
else
printf("strip: 55dc2f313648ea97, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x0000630c))=0x006a0802;
*((unsigned int *)((unsigned long)context_ptr+0x0000630c+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x0000630c+4*2))=0x02020081;
*((unsigned int *)((unsigned long)context_ptr+0x0000630c+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x00006a88))=0x997f14d1;
*((unsigned int *)((unsigned long)context_ptr+0x00006a88+4*1))=0x9148120c;
*((unsigned int *)((unsigned long)context_ptr+0x00006a88+4*2))=0x000824df;
*((unsigned int *)((unsigned long)context_ptr+0x00006a88+4*3))=0x5b8d2cfa;
*((unsigned int *)((unsigned long)context_ptr+0x00006a88+4*4))=0x7625bd31;
*((unsigned int *)((unsigned long)context_ptr+0x00006a88+4*5))=0x446729f1;
*((unsigned int *)((unsigned long)context_ptr+0x00006a88+4*6))=0x82d8bbaf;
*((unsigned int *)((unsigned long)context_ptr+0x00006a88+4*7))=0x56f861cf;
*((unsigned int *)((unsigned long)context_ptr+0x00006a88+4*8))=0x57900310;
*((unsigned int *)((unsigned long)context_ptr+0x00006a88+4*9))=0x5c937160;
*((unsigned int *)((unsigned long)context_ptr+0x00006a88+4*10))=0x0ed1407a;
*((unsigned int *)((unsigned long)context_ptr+0x00006a88+4*11))=0x492d7fe1;
*((unsigned int *)((unsigned long)context_ptr+0x00006a88+4*12))=0x9ef726a6;
*((unsigned int *)((unsigned long)context_ptr+0x00006a88+4*13))=0x1fe1e4dd;
*((unsigned int *)((unsigned long)context_ptr+0x00006a88+4*14))=0x52b7dca0;
*((unsigned int *)((unsigned long)context_ptr+0x00006a88+4*15))=0xeb9a019b;
*((unsigned int *)((unsigned long)context_ptr+0x00006a88+4*16))=0x820fc664;
*((unsigned int *)((unsigned long)context_ptr+0x00006a88+4*17))=0x21351906;
*((unsigned int *)((unsigned long)context_ptr+0x00006a88+4*18))=0x16b60c08;
*((unsigned int *)((unsigned long)context_ptr+0x00006a88+4*19))=0x287938a4;
*((unsigned int *)((unsigned long)context_ptr+0x00006a88+4*20))=0x276f4bb7;
*((unsigned int *)((unsigned long)context_ptr+0x00006a88+4*21))=0x0d008b05;
*((unsigned int *)((unsigned long)context_ptr+0x00006a88+4*22))=0x788cff42;
*((unsigned int *)((unsigned long)context_ptr+0x00006a88+4*23))=0xb1749929;
*((unsigned int *)((unsigned long)context_ptr+0x00006a88+4*24))=0x07772a98;
*((unsigned int *)((unsigned long)context_ptr+0x00006a88+4*25))=0x9ec21ca3;
*((unsigned int *)((unsigned long)context_ptr+0x00006a88+4*26))=0x30c0f24b;
*((unsigned int *)((unsigned long)context_ptr+0x00006a88+4*27))=0x2c43cc47;
*((unsigned int *)((unsigned long)context_ptr+0x00006a88+4*28))=0x2e383343;
*((unsigned int *)((unsigned long)context_ptr+0x00006a88+4*29))=0x5574f32f;
*((unsigned int *)((unsigned long)context_ptr+0x00006a88+4*30))=0x973bce8d;
*((unsigned int *)((unsigned long)context_ptr+0x00006a88+4*31))=0x99836fd6;
*((unsigned int *)((unsigned long)context_ptr+0x00006a88+4*32))=0x00000042;
*((unsigned int *)((unsigned long)context_ptr+0x00003c00))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003c00+4*1))=0x000064e8;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000c00+4*1))=0x00006a88;
*((unsigned int *)((unsigned long)context_ptr+0x00000c00+4*2))=0x0000630c;
*((unsigned int *)((unsigned long)context_ptr+0x00000c00+4*3))=0x02220081;
*((unsigned int *)((unsigned long)context_ptr+0x00000c00+4*4))=0x09ec39af;
*((unsigned int *)((unsigned long)context_ptr+0x00000c00+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000002b2&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000066d8,"\x75\xe8\x3c\x64\x1d\xe1\xb2\xb9\x8f\xc5\x5e\x04\x46\xc8\xf6\x6e",16))
printf("strip: 75e83c641de1b2b9, Pass\n");
else
printf("strip: 75e83c641de1b2b9, Failed\n");
writel(0x000002b8&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000066e8,"\x63\x5d\xca\x18\x69\x36\x06\x43\xcb\x20\x73\x02\x60\x72\xac\x48",16))
printf("strip: 635dca1869360643, Pass\n");
else
printf("strip: 635dca1869360643, Failed\n");
writel(0x000002be&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000066f8,"\x55\xef\x58\xfb\xbf\x30\x87\x9a\xee\xa4\xbe\x4b\x36\x9a\xc7\x7b",16))
printf("strip: 55ef58fbbf30879a, Pass\n");
else
printf("strip: 55ef58fbbf30879a, Failed\n");
writel(0x000002c4&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006718,"\x76\xce\x19\xb5\x42\x05\x7b\x5f\x79\xa2\x46\x6a\x47\xa1\x43\xc5",16))
printf("strip: 76ce19b542057b5f, Pass\n");
else
printf("strip: 76ce19b542057b5f, Failed\n");
writel(0x000002ca&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006498,"\x8a\x75\x14\xda\xe2\x51\xee\xbf\x8d\x35\xbf\x28\xff\xa3\xf3\x74",16))
printf("strip: 8a7514dae251eebf, Pass\n");
else
printf("strip: 8a7514dae251eebf, Failed\n");
writel(0x000002d0&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x0000635c,"\x4a\x61\x44\x65\xae\x36\xd2\x5d\xff\x09\xb3\x58\x07\xf8\x3c\x96",16))
printf("strip: 4a614465ae36d25d, Pass\n");
else
printf("strip: 4a614465ae36d25d, Failed\n");
writel(0x000002d6&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000064a8,"\x58\x55\xf9\xb5\x71\xc8\x69\x30\x2f\xba\x58\x0a\xc7\xfc\x9a\x7d",16))
printf("strip: 5855f9b571c86930, Pass\n");
else
printf("strip: 5855f9b571c86930, Failed\n");
writel(0x000002dc&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006408,"\x55\x26\xae\xd2\xd8\x50\x5e\x83\x98\xf0\xaf\x21\x84\x0f\x23\xc2",16))
printf("strip: 5526aed2d8505e83, Pass\n");
else
printf("strip: 5526aed2d8505e83, Failed\n");
writel(0x000002e2&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006418,"\x8b\x57\x1e\x26\x07\x44\xfa\x00\xe1\x68\x2b\x62\xc9\xa0\x0f\x91",16))
printf("strip: 8b571e260744fa00, Pass\n");
else
printf("strip: 8b571e260744fa00, Failed\n");
writel(0x000002e8&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x0000636c,"\xae\xfa\xd1\xb9\x88\x39\x24\x47\x57\x83\xb8\xd3\x3b\xd5\xdc\xd3",16))
printf("strip: aefad1b988392447, Pass\n");
else
printf("strip: aefad1b988392447, Failed\n");
writel(0x000002ee&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000064b8,"\x84\x4f\xf1\x40\x08\xdd\x8a\x3f\xa0\xb3\x9a\x2d\x4b\x81\x5e\x17",16))
printf("strip: 844ff14008dd8a3f, Pass\n");
else
printf("strip: 844ff14008dd8a3f, Failed\n");
writel(0x000002f4&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000064c8,"\x1d\x0a\x73\x91\x6a\x34\xd0\xf6\x48\xbc\x1f\x34\x5e\xe5\x88\x14",16))
printf("strip: 1d0a73916a34d0f6, Pass\n");
else
printf("strip: 1d0a73916a34d0f6, Failed\n");
writel(0x000002fa&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000067a8,"\x42\x6f\x1a\xae\x34\xf1\x5e\x11\xc6\x7b\xa2\xed\x65\xe1\x2a\x53",16))
printf("strip: 426f1aae34f15e11, Pass\n");
else
printf("strip: 426f1aae34f15e11, Failed\n");
writel(0x00000300&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
writel(0x00000c00&0xffffffff,ivp_cae_base_addr+0x00000830);
if(!memcmp((unsigned char *)context_ptr+0x000064d8,"\x36\x68\x5f\x29\xcc\xc5\x60\x85\x1c\xcf\x31\xfb\xea\x5c\xbd\x67",16))
printf("strip: 36685f29ccc56085, Pass\n");
else
printf("strip: 36685f29ccc56085, Failed\n");
writel(0x00000006&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000064e8,"\xe7\xd6\xde\x61\xf6\x77\x1f\x9b\x08\xd4\x8a\x70\x07\xe9\xf6\x6d",16))
printf("strip: e7d6de61f6771f9b, Pass\n");
else
printf("strip: e7d6de61f6771f9b, Failed\n");
}

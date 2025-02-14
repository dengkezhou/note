#include <common.h>
#include <malloc.h>

extern volatile unsigned int ivp_cae_base_addr;

void test_hmac_sha256(void)
{
unsigned int *context_ptr=(unsigned int *)0x14000000;
printf("test_hmac_sha256\n");
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
*((unsigned int *)((unsigned long)context_ptr+0x00006000))=0x01ea1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006000+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006000+4*2))=0x25014320;
*((unsigned int *)((unsigned long)context_ptr+0x00006000+4*3))=0x84d0073a;
*((unsigned int *)((unsigned long)context_ptr+0x00006000+4*4))=0x19cb100a;
*((unsigned int *)((unsigned long)context_ptr+0x00006000+4*5))=0xfb8baf72;
*((unsigned int *)((unsigned long)context_ptr+0x00006000+4*6))=0xa958f0e8;
*((unsigned int *)((unsigned long)context_ptr+0x00006000+4*7))=0xa570d0d4;
*((unsigned int *)((unsigned long)context_ptr+0x00006000+4*8))=0xede4bbbc;
*((unsigned int *)((unsigned long)context_ptr+0x00006000+4*9))=0x6ba50d97;
*((unsigned int *)((unsigned long)context_ptr+0x00006000+4*10))=0xa203c324;
*((unsigned int *)((unsigned long)context_ptr+0x00006000+4*11))=0x01ddedd9;
*((unsigned int *)((unsigned long)context_ptr+0x00006000+4*12))=0xacf66bbc;
*((unsigned int *)((unsigned long)context_ptr+0x00006000+4*13))=0xbe2936c4;
*((unsigned int *)((unsigned long)context_ptr+0x00006000+4*14))=0x22f3f196;
*((unsigned int *)((unsigned long)context_ptr+0x00006000+4*15))=0x06e53681;
*((unsigned int *)((unsigned long)context_ptr+0x00006000+4*16))=0x4b4a909b;
*((unsigned int *)((unsigned long)context_ptr+0x00006000+4*17))=0x4a7e5f2f;
*((unsigned int *)((unsigned long)context_ptr+0x00006048))=0x01ea1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006048+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006048+4*2))=0x02020001;
*((unsigned int *)((unsigned long)context_ptr+0x00006048+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x00006058))=0x00000015;
*((unsigned int *)((unsigned long)context_ptr+0x00003000))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003000+4*1))=0x0000605c;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000000+4*1))=0x00006058;
*((unsigned int *)((unsigned long)context_ptr+0x00000000+4*2))=0x00006048;
*((unsigned int *)((unsigned long)context_ptr+0x00000000+4*3))=0x02220001;
*((unsigned int *)((unsigned long)context_ptr+0x00000000+4*4))=0x0399f8a8;
*((unsigned int *)((unsigned long)context_ptr+0x00000000+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x0000607c))=0x01ea1002;
*((unsigned int *)((unsigned long)context_ptr+0x0000607c+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x0000607c+4*2))=0x02020002;
*((unsigned int *)((unsigned long)context_ptr+0x0000607c+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x0000608c))=0x00002e00;
*((unsigned int *)((unsigned long)context_ptr+0x00003018))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003018+4*1))=0x00006090;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000018+4*1))=0x0000608c;
*((unsigned int *)((unsigned long)context_ptr+0x00000018+4*2))=0x0000607c;
*((unsigned int *)((unsigned long)context_ptr+0x00000018+4*3))=0x02220002;
*((unsigned int *)((unsigned long)context_ptr+0x00000018+4*4))=0x010cc870;
*((unsigned int *)((unsigned long)context_ptr+0x00000018+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x000060b0))=0x01ea1002;
*((unsigned int *)((unsigned long)context_ptr+0x000060b0+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000060b0+4*2))=0x02020003;
*((unsigned int *)((unsigned long)context_ptr+0x000060b0+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x000060c0))=0x00c66258;
*((unsigned int *)((unsigned long)context_ptr+0x00003030))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003030+4*1))=0x000060c4;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000030+4*1))=0x000060c0;
*((unsigned int *)((unsigned long)context_ptr+0x00000030+4*2))=0x000060b0;
*((unsigned int *)((unsigned long)context_ptr+0x00000030+4*3))=0x02220003;
*((unsigned int *)((unsigned long)context_ptr+0x00000030+4*4))=0x09c30cea;
*((unsigned int *)((unsigned long)context_ptr+0x00000030+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x000060e4))=0x01ea1002;
*((unsigned int *)((unsigned long)context_ptr+0x000060e4+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000060e4+4*2))=0x02020004;
*((unsigned int *)((unsigned long)context_ptr+0x000060e4+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x000060f4))=0xc7e3d117;
*((unsigned int *)((unsigned long)context_ptr+0x00003048))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003048+4*1))=0x000060f8;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000048+4*1))=0x000060f4;
*((unsigned int *)((unsigned long)context_ptr+0x00000048+4*2))=0x000060e4;
*((unsigned int *)((unsigned long)context_ptr+0x00000048+4*3))=0x02220004;
*((unsigned int *)((unsigned long)context_ptr+0x00000048+4*4))=0x04e28e67;
*((unsigned int *)((unsigned long)context_ptr+0x00000048+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x00006118))=0x01ea1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006118+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006118+4*2))=0x02020005;
*((unsigned int *)((unsigned long)context_ptr+0x00006118+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x00006128))=0xdb9a065e;
*((unsigned int *)((unsigned long)context_ptr+0x00006128+4*1))=0x0000002f;
*((unsigned int *)((unsigned long)context_ptr+0x00003060))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003060+4*1))=0x00006130;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000060+4*1))=0x00006128;
*((unsigned int *)((unsigned long)context_ptr+0x00000060+4*2))=0x00006118;
*((unsigned int *)((unsigned long)context_ptr+0x00000060+4*3))=0x02220005;
*((unsigned int *)((unsigned long)context_ptr+0x00000060+4*4))=0x0f58c43b;
*((unsigned int *)((unsigned long)context_ptr+0x00000060+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x00006150))=0x01ea1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006150+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006150+4*2))=0x02020006;
*((unsigned int *)((unsigned long)context_ptr+0x00006150+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x00006160))=0x0ef25e71;
*((unsigned int *)((unsigned long)context_ptr+0x00006160+4*1))=0x00006a68;
*((unsigned int *)((unsigned long)context_ptr+0x00003078))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003078+4*1))=0x00006168;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000078+4*1))=0x00006160;
*((unsigned int *)((unsigned long)context_ptr+0x00000078+4*2))=0x00006150;
*((unsigned int *)((unsigned long)context_ptr+0x00000078+4*3))=0x02220006;
*((unsigned int *)((unsigned long)context_ptr+0x00000078+4*4))=0x03438b4e;
*((unsigned int *)((unsigned long)context_ptr+0x00000078+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x00006188))=0x01ea1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006188+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006188+4*2))=0x02020007;
*((unsigned int *)((unsigned long)context_ptr+0x00006188+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x00006198))=0x1efb47c3;
*((unsigned int *)((unsigned long)context_ptr+0x00006198+4*1))=0x00410ae2;
*((unsigned int *)((unsigned long)context_ptr+0x00003090))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003090+4*1))=0x000061a0;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000090+4*1))=0x00006198;
*((unsigned int *)((unsigned long)context_ptr+0x00000090+4*2))=0x00006188;
*((unsigned int *)((unsigned long)context_ptr+0x00000090+4*3))=0x02220007;
*((unsigned int *)((unsigned long)context_ptr+0x00000090+4*4))=0x0656fa7e;
*((unsigned int *)((unsigned long)context_ptr+0x00000090+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x000061c0))=0x01ea1002;
*((unsigned int *)((unsigned long)context_ptr+0x000061c0+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000061c0+4*2))=0x02020008;
*((unsigned int *)((unsigned long)context_ptr+0x000061c0+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x000061d0))=0xb17a6a79;
*((unsigned int *)((unsigned long)context_ptr+0x000061d0+4*1))=0x4c0fa651;
*((unsigned int *)((unsigned long)context_ptr+0x000030a8))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x000030a8+4*1))=0x000061d8;
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
*((unsigned int *)((unsigned long)context_ptr+0x000000a8+4*1))=0x000061d0;
*((unsigned int *)((unsigned long)context_ptr+0x000000a8+4*2))=0x000061c0;
*((unsigned int *)((unsigned long)context_ptr+0x000000a8+4*3))=0x02220008;
*((unsigned int *)((unsigned long)context_ptr+0x000000a8+4*4))=0x09f032cb;
*((unsigned int *)((unsigned long)context_ptr+0x000000a8+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x000061f8))=0x01ea1002;
*((unsigned int *)((unsigned long)context_ptr+0x000061f8+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000061f8+4*2))=0x02020009;
*((unsigned int *)((unsigned long)context_ptr+0x000061f8+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x00006208))=0xf0323863;
*((unsigned int *)((unsigned long)context_ptr+0x00006208+4*1))=0x3b630c96;
*((unsigned int *)((unsigned long)context_ptr+0x00006208+4*2))=0x00000015;
*((unsigned int *)((unsigned long)context_ptr+0x000030c0))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x000030c0+4*1))=0x00006214;
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
*((unsigned int *)((unsigned long)context_ptr+0x000000c0+4*1))=0x00006208;
*((unsigned int *)((unsigned long)context_ptr+0x000000c0+4*2))=0x000061f8;
*((unsigned int *)((unsigned long)context_ptr+0x000000c0+4*3))=0x02220009;
*((unsigned int *)((unsigned long)context_ptr+0x000000c0+4*4))=0x0a358cb0;
*((unsigned int *)((unsigned long)context_ptr+0x000000c0+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x00006234))=0x01ea1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006234+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006234+4*2))=0x0202000a;
*((unsigned int *)((unsigned long)context_ptr+0x00006234+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x00006244))=0x5e0b0753;
*((unsigned int *)((unsigned long)context_ptr+0x00006244+4*1))=0x33308635;
*((unsigned int *)((unsigned long)context_ptr+0x00006244+4*2))=0x0000bcac;
*((unsigned int *)((unsigned long)context_ptr+0x000030d8))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x000030d8+4*1))=0x00006250;
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
*((unsigned int *)((unsigned long)context_ptr+0x000000d8+4*1))=0x00006244;
*((unsigned int *)((unsigned long)context_ptr+0x000000d8+4*2))=0x00006234;
*((unsigned int *)((unsigned long)context_ptr+0x000000d8+4*3))=0x0222000a;
*((unsigned int *)((unsigned long)context_ptr+0x000000d8+4*4))=0x04130086;
*((unsigned int *)((unsigned long)context_ptr+0x000000d8+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x00006270))=0x01ea1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006270+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006270+4*2))=0x0202000b;
*((unsigned int *)((unsigned long)context_ptr+0x00006270+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x00006280))=0xc81e3b42;
*((unsigned int *)((unsigned long)context_ptr+0x00006280+4*1))=0x483fbb19;
*((unsigned int *)((unsigned long)context_ptr+0x00006280+4*2))=0x00bda8bc;
*((unsigned int *)((unsigned long)context_ptr+0x000030f0))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x000030f0+4*1))=0x0000628c;
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
*((unsigned int *)((unsigned long)context_ptr+0x000000f0+4*1))=0x00006280;
*((unsigned int *)((unsigned long)context_ptr+0x000000f0+4*2))=0x00006270;
*((unsigned int *)((unsigned long)context_ptr+0x000000f0+4*3))=0x0222000b;
*((unsigned int *)((unsigned long)context_ptr+0x000000f0+4*4))=0x01f2de26;
*((unsigned int *)((unsigned long)context_ptr+0x000000f0+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x000062ac))=0x01ea1002;
*((unsigned int *)((unsigned long)context_ptr+0x000062ac+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000062ac+4*2))=0x0202000c;
*((unsigned int *)((unsigned long)context_ptr+0x000062ac+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x000062bc))=0x5b86d51b;
*((unsigned int *)((unsigned long)context_ptr+0x000062bc+4*1))=0xa7380374;
*((unsigned int *)((unsigned long)context_ptr+0x000062bc+4*2))=0x7bf47ea9;
*((unsigned int *)((unsigned long)context_ptr+0x00003108))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003108+4*1))=0x000062c8;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000108+4*1))=0x000062bc;
*((unsigned int *)((unsigned long)context_ptr+0x00000108+4*2))=0x000062ac;
*((unsigned int *)((unsigned long)context_ptr+0x00000108+4*3))=0x0222000c;
*((unsigned int *)((unsigned long)context_ptr+0x00000108+4*4))=0x0425832c;
*((unsigned int *)((unsigned long)context_ptr+0x00000108+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x000062e8))=0x01ea1002;
*((unsigned int *)((unsigned long)context_ptr+0x000062e8+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000062e8+4*2))=0x0202000d;
*((unsigned int *)((unsigned long)context_ptr+0x000062e8+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x000062f8))=0xafbc8843;
*((unsigned int *)((unsigned long)context_ptr+0x000062f8+4*1))=0x68eb0a76;
*((unsigned int *)((unsigned long)context_ptr+0x000062f8+4*2))=0xde230063;
*((unsigned int *)((unsigned long)context_ptr+0x000062f8+4*3))=0x00000083;
*((unsigned int *)((unsigned long)context_ptr+0x00003120))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003120+4*1))=0x00006308;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000120+4*1))=0x000062f8;
*((unsigned int *)((unsigned long)context_ptr+0x00000120+4*2))=0x000062e8;
*((unsigned int *)((unsigned long)context_ptr+0x00000120+4*3))=0x0222000d;
*((unsigned int *)((unsigned long)context_ptr+0x00000120+4*4))=0x0547e390;
*((unsigned int *)((unsigned long)context_ptr+0x00000120+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x00006328))=0x01ea1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006328+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006328+4*2))=0x0202000e;
*((unsigned int *)((unsigned long)context_ptr+0x00006328+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x00006338))=0x057e67b8;
*((unsigned int *)((unsigned long)context_ptr+0x00006338+4*1))=0x94ae08bd;
*((unsigned int *)((unsigned long)context_ptr+0x00006338+4*2))=0x35af4ac6;
*((unsigned int *)((unsigned long)context_ptr+0x00006338+4*3))=0x00005787;
*((unsigned int *)((unsigned long)context_ptr+0x00003138))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003138+4*1))=0x00006348;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000138+4*1))=0x00006338;
*((unsigned int *)((unsigned long)context_ptr+0x00000138+4*2))=0x00006328;
*((unsigned int *)((unsigned long)context_ptr+0x00000138+4*3))=0x0222000e;
*((unsigned int *)((unsigned long)context_ptr+0x00000138+4*4))=0x0357f0a6;
*((unsigned int *)((unsigned long)context_ptr+0x00000138+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x00006368))=0x01ea1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006368+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006368+4*2))=0x0202000f;
*((unsigned int *)((unsigned long)context_ptr+0x00006368+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x00006378))=0xc19acb81;
*((unsigned int *)((unsigned long)context_ptr+0x00006378+4*1))=0xfd6d4844;
*((unsigned int *)((unsigned long)context_ptr+0x00006378+4*2))=0x8d89f2b7;
*((unsigned int *)((unsigned long)context_ptr+0x00006378+4*3))=0x00c830fd;
*((unsigned int *)((unsigned long)context_ptr+0x00003150))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003150+4*1))=0x00006388;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000150+4*1))=0x00006378;
*((unsigned int *)((unsigned long)context_ptr+0x00000150+4*2))=0x00006368;
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
if(!memcmp((unsigned char *)context_ptr+0x0000605c,"\x8d\xf8\xf3\xfe\xfe\x8e\x88\x02\xcf\xb3\xa4\xc8\x8e\x27\xbb\x73\xac\xf0\xb2\x3f\xe7\x9b\x34\xf1\x66\x59\x15\x59\xd1\x07\x5d\x4e",32))
printf("strip: 8df8f3fefe8e8802, Pass\n");
else
printf("strip: 8df8f3fefe8e8802, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006048))=0x01ea1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006048+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006048+4*2))=0x02020010;
*((unsigned int *)((unsigned long)context_ptr+0x00006048+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x00006058))=0x62c34002;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*1))=0xe163a0c6;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*2))=0x20d47709;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*3))=0x790653b5;
*((unsigned int *)((unsigned long)context_ptr+0x00003168))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003168+4*1))=0x000063a8;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000168+4*1))=0x00006058;
*((unsigned int *)((unsigned long)context_ptr+0x00000168+4*2))=0x00006048;
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
if(!memcmp((unsigned char *)context_ptr+0x00006090,"\x2e\x76\x8b\x3f\xc7\x03\x0c\xa1\xdc\x57\xb1\xc6\x97\x5b\x3b\xfd\x82\x72\x00\x1b\x4d\x82\xf9\xf2\x43\x56\xe8\x73\x9e\x89\x81\x89",32))
printf("strip: 2e768b3fc7030ca1, Pass\n");
else
printf("strip: 2e768b3fc7030ca1, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006068))=0x01ea1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006068+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006068+4*2))=0x02020011;
*((unsigned int *)((unsigned long)context_ptr+0x00006068+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x00006078))=0x95098de6;
*((unsigned int *)((unsigned long)context_ptr+0x00006078+4*1))=0xd1c108a4;
*((unsigned int *)((unsigned long)context_ptr+0x00006078+4*2))=0x3d74a512;
*((unsigned int *)((unsigned long)context_ptr+0x00006078+4*3))=0xa7552875;
*((unsigned int *)((unsigned long)context_ptr+0x00006078+4*4))=0x00000079;
*((unsigned int *)((unsigned long)context_ptr+0x00003180))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003180+4*1))=0x0000608c;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000180+4*1))=0x00006078;
*((unsigned int *)((unsigned long)context_ptr+0x00000180+4*2))=0x00006068;
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
if(!memcmp((unsigned char *)context_ptr+0x000060c4,"\xfa\x37\x51\xa9\xc0\x2b\x96\x61\xfe\xd3\x88\xfb\xdf\xa7\x1e\xca\xe9\x22\xf0\x2f\xa2\x4d\x2f\x98\x8b\x3d\xb1\xd1\x59\x83\x6f\x68",32))
printf("strip: fa3751a9c02b9661, Pass\n");
else
printf("strip: fa3751a9c02b9661, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000060ac))=0x01ea1002;
*((unsigned int *)((unsigned long)context_ptr+0x000060ac+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000060ac+4*2))=0x02020012;
*((unsigned int *)((unsigned long)context_ptr+0x000060ac+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x000060bc))=0xdf8d7403;
*((unsigned int *)((unsigned long)context_ptr+0x000060bc+4*1))=0xdc0d147e;
*((unsigned int *)((unsigned long)context_ptr+0x000060bc+4*2))=0xa543dbca;
*((unsigned int *)((unsigned long)context_ptr+0x000060bc+4*3))=0xf455d318;
*((unsigned int *)((unsigned long)context_ptr+0x000060bc+4*4))=0x00000878;
*((unsigned int *)((unsigned long)context_ptr+0x00003198))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003198+4*1))=0x000063c8;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000198+4*1))=0x000060bc;
*((unsigned int *)((unsigned long)context_ptr+0x00000198+4*2))=0x000060ac;
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
if(!memcmp((unsigned char *)context_ptr+0x000060f8,"\x22\xa5\x1d\xe7\xbb\xb1\x7b\xd2\xcd\xbf\x5a\x57\xda\xb2\xa5\x34\xab\xce\xc9\x2b\xc0\xa1\x32\xc2\x1b\x4e\xa2\xf9\x08\x03\x48\xdc",32))
printf("strip: 22a51de7bbb17bd2, Pass\n");
else
printf("strip: 22a51de7bbb17bd2, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000060d0))=0x01ea1002;
*((unsigned int *)((unsigned long)context_ptr+0x000060d0+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000060d0+4*2))=0x02020013;
*((unsigned int *)((unsigned long)context_ptr+0x000060d0+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x000060e0))=0x8882233f;
*((unsigned int *)((unsigned long)context_ptr+0x000060e0+4*1))=0xf7a86812;
*((unsigned int *)((unsigned long)context_ptr+0x000060e0+4*2))=0x39786f6e;
*((unsigned int *)((unsigned long)context_ptr+0x000060e0+4*3))=0x9465a565;
*((unsigned int *)((unsigned long)context_ptr+0x000060e0+4*4))=0x00e2ffd5;
*((unsigned int *)((unsigned long)context_ptr+0x000031b0))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x000031b0+4*1))=0x000060f4;
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
*((unsigned int *)((unsigned long)context_ptr+0x000001b0+4*1))=0x000060e0;
*((unsigned int *)((unsigned long)context_ptr+0x000001b0+4*2))=0x000060d0;
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
if(!memcmp((unsigned char *)context_ptr+0x00006130,"\x1c\xe0\x8d\x51\x64\xa2\xf9\x64\xb3\x7c\xd2\x5b\x63\x69\xc5\x36\x52\x2e\x5e\x7d\xeb\x4b\x6f\x25\x19\x81\x24\xc1\xf8\xfe\x44\x19",32))
printf("strip: 1ce08d5164a2f964, Pass\n");
else
printf("strip: 1ce08d5164a2f964, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006114))=0x01ea1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006114+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006114+4*2))=0x02020014;
*((unsigned int *)((unsigned long)context_ptr+0x00006114+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x00006124))=0xc7aeb513;
*((unsigned int *)((unsigned long)context_ptr+0x00006124+4*1))=0x352b8d8b;
*((unsigned int *)((unsigned long)context_ptr+0x00006124+4*2))=0x5bd1863a;
*((unsigned int *)((unsigned long)context_ptr+0x00006124+4*3))=0x55b7bce1;
*((unsigned int *)((unsigned long)context_ptr+0x00006124+4*4))=0x68daf61e;
*((unsigned int *)((unsigned long)context_ptr+0x000031c8))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x000031c8+4*1))=0x000063e8;
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
*((unsigned int *)((unsigned long)context_ptr+0x000001c8+4*1))=0x00006124;
*((unsigned int *)((unsigned long)context_ptr+0x000001c8+4*2))=0x00006114;
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
if(!memcmp((unsigned char *)context_ptr+0x00006168,"\xbe\x64\x46\xe2\x77\x47\xdb\xa3\x82\x39\x3d\x43\xd0\x8f\x04\xb3\xd6\x78\xd7\x3c\x2b\x37\x8c\x23\xc2\xd3\x4f\xcf\x98\xc8\xeb\xf9",32))
printf("strip: be6446e27747dba3, Pass\n");
else
printf("strip: be6446e27747dba3, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006138))=0x01ea1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006138+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006138+4*2))=0x02020015;
*((unsigned int *)((unsigned long)context_ptr+0x00006138+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x00006148))=0xe0d9d32b;
*((unsigned int *)((unsigned long)context_ptr+0x00006148+4*1))=0xb5359b84;
*((unsigned int *)((unsigned long)context_ptr+0x00006148+4*2))=0x63220567;
*((unsigned int *)((unsigned long)context_ptr+0x00006148+4*3))=0xedea90e2;
*((unsigned int *)((unsigned long)context_ptr+0x00006148+4*4))=0x81559616;
*((unsigned int *)((unsigned long)context_ptr+0x00006148+4*5))=0x00000074;
*((unsigned int *)((unsigned long)context_ptr+0x000031e0))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x000031e0+4*1))=0x00006160;
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
*((unsigned int *)((unsigned long)context_ptr+0x000001e0+4*1))=0x00006148;
*((unsigned int *)((unsigned long)context_ptr+0x000001e0+4*2))=0x00006138;
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
if(!memcmp((unsigned char *)context_ptr+0x000061a0,"\x3d\xe5\x45\x1a\x60\x90\x38\xca\xf4\xf4\x62\xb7\x3d\x7c\x64\xe1\x14\x6b\x58\x2b\xcc\xe7\x9d\x41\xc3\xd2\xe5\xd8\xfb\xb4\xdd\x37",32))
printf("strip: 3de5451a609038ca, Pass\n");
else
printf("strip: 3de5451a609038ca, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006180))=0x01ea1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006180+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006180+4*2))=0x02020016;
*((unsigned int *)((unsigned long)context_ptr+0x00006180+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x00006190))=0xbeef3bc2;
*((unsigned int *)((unsigned long)context_ptr+0x00006190+4*1))=0x625be17b;
*((unsigned int *)((unsigned long)context_ptr+0x00006190+4*2))=0x8066c721;
*((unsigned int *)((unsigned long)context_ptr+0x00006190+4*3))=0xea5fa778;
*((unsigned int *)((unsigned long)context_ptr+0x00006190+4*4))=0xc4665b6e;
*((unsigned int *)((unsigned long)context_ptr+0x00006190+4*5))=0x0000ddfe;
*((unsigned int *)((unsigned long)context_ptr+0x000031f8))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x000031f8+4*1))=0x00006408;
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
*((unsigned int *)((unsigned long)context_ptr+0x000001f8+4*1))=0x00006190;
*((unsigned int *)((unsigned long)context_ptr+0x000001f8+4*2))=0x00006180;
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
if(!memcmp((unsigned char *)context_ptr+0x000061d8,"\xb2\x97\x1d\x68\x77\x19\x72\xe6\x23\xc2\x1b\x58\xf8\x05\x71\x02\xf6\x3d\x5f\x84\x82\xaa\xed\x19\xc9\x81\x1f\x15\x88\x63\x61\x7a",32))
printf("strip: b2971d68771972e6, Pass\n");
else
printf("strip: b2971d68771972e6, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000061a8))=0x01ea1002;
*((unsigned int *)((unsigned long)context_ptr+0x000061a8+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000061a8+4*2))=0x02020017;
*((unsigned int *)((unsigned long)context_ptr+0x000061a8+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x000061b8))=0xc3616fce;
*((unsigned int *)((unsigned long)context_ptr+0x000061b8+4*1))=0xb495449d;
*((unsigned int *)((unsigned long)context_ptr+0x000061b8+4*2))=0x98a4add3;
*((unsigned int *)((unsigned long)context_ptr+0x000061b8+4*3))=0x45b6f117;
*((unsigned int *)((unsigned long)context_ptr+0x000061b8+4*4))=0x61a89eb1;
*((unsigned int *)((unsigned long)context_ptr+0x000061b8+4*5))=0x0033a892;
*((unsigned int *)((unsigned long)context_ptr+0x00003210))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003210+4*1))=0x000061d0;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000210+4*1))=0x000061b8;
*((unsigned int *)((unsigned long)context_ptr+0x00000210+4*2))=0x000061a8;
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
if(!memcmp((unsigned char *)context_ptr+0x00006214,"\xa1\xa8\xbb\x0c\xc0\x30\xd7\x4f\x4e\x23\xc3\x7d\xed\x1f\x59\x2c\x83\xad\xf6\xd8\x2d\x6a\x9d\xd8\xbb\xb8\x85\x82\x68\x89\x60\x9a",32))
printf("strip: a1a8bb0cc030d74f, Pass\n");
else
printf("strip: a1a8bb0cc030d74f, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000061f0))=0x01ea1002;
*((unsigned int *)((unsigned long)context_ptr+0x000061f0+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000061f0+4*2))=0x02020018;
*((unsigned int *)((unsigned long)context_ptr+0x000061f0+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x00006200))=0xec2eb985;
*((unsigned int *)((unsigned long)context_ptr+0x00006200+4*1))=0xa26f98b6;
*((unsigned int *)((unsigned long)context_ptr+0x00006200+4*2))=0x3692e69e;
*((unsigned int *)((unsigned long)context_ptr+0x00006200+4*3))=0xd7e73e70;
*((unsigned int *)((unsigned long)context_ptr+0x00006200+4*4))=0x220b328e;
*((unsigned int *)((unsigned long)context_ptr+0x00006200+4*5))=0xaf39ac71;
*((unsigned int *)((unsigned long)context_ptr+0x00003228))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003228+4*1))=0x00006428;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000228+4*1))=0x00006200;
*((unsigned int *)((unsigned long)context_ptr+0x00000228+4*2))=0x000061f0;
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
if(!memcmp((unsigned char *)context_ptr+0x00006250,"\x65\x41\x7e\x34\x2e\xc6\x4d\xf9\x29\x98\xe3\xd7\x70\xfb\x01\xfa\x8e\xd0\xa8\x99\xcf\x5d\x71\x8a\x66\x4b\xac\xfb\x19\x96\x13\xac",32))
printf("strip: 65417e342ec64df9, Pass\n");
else
printf("strip: 65417e342ec64df9, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006218))=0x01ea1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006218+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006218+4*2))=0x02020019;
*((unsigned int *)((unsigned long)context_ptr+0x00006218+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x00006228))=0x38d64797;
*((unsigned int *)((unsigned long)context_ptr+0x00006228+4*1))=0xd2568162;
*((unsigned int *)((unsigned long)context_ptr+0x00006228+4*2))=0xa0271643;
*((unsigned int *)((unsigned long)context_ptr+0x00006228+4*3))=0x7afe1090;
*((unsigned int *)((unsigned long)context_ptr+0x00006228+4*4))=0x6f06ba51;
*((unsigned int *)((unsigned long)context_ptr+0x00006228+4*5))=0xe2c2f6aa;
*((unsigned int *)((unsigned long)context_ptr+0x00006228+4*6))=0x0000001e;
*((unsigned int *)((unsigned long)context_ptr+0x00003240))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003240+4*1))=0x00006244;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000240+4*1))=0x00006228;
*((unsigned int *)((unsigned long)context_ptr+0x00000240+4*2))=0x00006218;
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
if(!memcmp((unsigned char *)context_ptr+0x0000628c,"\x15\xa3\x7b\x6e\xa0\xf8\x20\xad\x19\x64\x19\x8a\xc9\xae\x74\xa2\x96\xe8\xb6\xd0\x7f\xc8\xac\xd5\x36\x25\xdc\xd8\x26\xa5\x00\xf4",32))
printf("strip: 15a37b6ea0f820ad, Pass\n");
else
printf("strip: 15a37b6ea0f820ad, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006264))=0x01ea1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006264+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006264+4*2))=0x0202001a;
*((unsigned int *)((unsigned long)context_ptr+0x00006264+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x00006274))=0x1d4a9c08;
*((unsigned int *)((unsigned long)context_ptr+0x00006274+4*1))=0x5883fab6;
*((unsigned int *)((unsigned long)context_ptr+0x00006274+4*2))=0x68886a72;
*((unsigned int *)((unsigned long)context_ptr+0x00006274+4*3))=0x2cfffa14;
*((unsigned int *)((unsigned long)context_ptr+0x00006274+4*4))=0x08b26f3d;
*((unsigned int *)((unsigned long)context_ptr+0x00006274+4*5))=0xde44a3d5;
*((unsigned int *)((unsigned long)context_ptr+0x00006274+4*6))=0x000051a9;
*((unsigned int *)((unsigned long)context_ptr+0x00003258))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003258+4*1))=0x00006448;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000258+4*1))=0x00006274;
*((unsigned int *)((unsigned long)context_ptr+0x00000258+4*2))=0x00006264;
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
if(!memcmp((unsigned char *)context_ptr+0x000062c8,"\x24\xd3\x63\xc0\x91\x22\x01\x49\x82\x89\xb6\xdd\xdc\x39\x73\xf7\x06\xdb\xcc\x43\x97\x31\x7f\x78\x79\x34\x0d\x59\x59\xcd\x52\xd9",32))
printf("strip: 24d363c091220149, Pass\n");
else
printf("strip: 24d363c091220149, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006290))=0x01ea1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006290+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006290+4*2))=0x0202001b;
*((unsigned int *)((unsigned long)context_ptr+0x00006290+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x000062a0))=0xde4cfc3f;
*((unsigned int *)((unsigned long)context_ptr+0x000062a0+4*1))=0xcab8bdcb;
*((unsigned int *)((unsigned long)context_ptr+0x000062a0+4*2))=0x812a0fd8;
*((unsigned int *)((unsigned long)context_ptr+0x000062a0+4*3))=0x207e8836;
*((unsigned int *)((unsigned long)context_ptr+0x000062a0+4*4))=0x14d30216;
*((unsigned int *)((unsigned long)context_ptr+0x000062a0+4*5))=0x73befbf6;
*((unsigned int *)((unsigned long)context_ptr+0x000062a0+4*6))=0x00586946;
*((unsigned int *)((unsigned long)context_ptr+0x00003270))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003270+4*1))=0x000062bc;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000270+4*1))=0x000062a0;
*((unsigned int *)((unsigned long)context_ptr+0x00000270+4*2))=0x00006290;
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
if(!memcmp((unsigned char *)context_ptr+0x00006308,"\x90\x14\x25\x1a\x51\xac\x41\x0b\x01\x8b\xa5\xcb\x9e\xb8\x76\x29\xd5\xa9\x87\x16\xd6\xb7\x20\x46\x53\xd9\xb7\xa6\x19\x64\x06\xce",32))
printf("strip: 9014251a51ac410b, Pass\n");
else
printf("strip: 9014251a51ac410b, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000062dc))=0x01ea1002;
*((unsigned int *)((unsigned long)context_ptr+0x000062dc+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000062dc+4*2))=0x0202001c;
*((unsigned int *)((unsigned long)context_ptr+0x000062dc+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x000062ec))=0xba0da674;
*((unsigned int *)((unsigned long)context_ptr+0x000062ec+4*1))=0x331175f7;
*((unsigned int *)((unsigned long)context_ptr+0x000062ec+4*2))=0x00cb411a;
*((unsigned int *)((unsigned long)context_ptr+0x000062ec+4*3))=0x2c2ff0df;
*((unsigned int *)((unsigned long)context_ptr+0x000062ec+4*4))=0x02cf5cf7;
*((unsigned int *)((unsigned long)context_ptr+0x000062ec+4*5))=0xed9b04fd;
*((unsigned int *)((unsigned long)context_ptr+0x000062ec+4*6))=0x64d24fd4;
*((unsigned int *)((unsigned long)context_ptr+0x00003288))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003288+4*1))=0x00006308;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000288+4*1))=0x000062ec;
*((unsigned int *)((unsigned long)context_ptr+0x00000288+4*2))=0x000062dc;
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
if(!memcmp((unsigned char *)context_ptr+0x00006348,"\xc5\x84\x6c\x1e\x57\x7b\xbe\x72\xd2\x36\x74\x09\x5c\x45\x18\x28\xef\x2f\xce\x9e\x1d\xd8\x6b\x1d\x23\x32\x25\x2a\xf4\x58\xe8\x09",32))
printf("strip: c5846c1e577bbe72, Pass\n");
else
printf("strip: c5846c1e577bbe72, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006328))=0x01ea1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006328+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006328+4*2))=0x0202001d;
*((unsigned int *)((unsigned long)context_ptr+0x00006328+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x00006338))=0xaf7bbfd6;
*((unsigned int *)((unsigned long)context_ptr+0x00006338+4*1))=0xc843c319;
*((unsigned int *)((unsigned long)context_ptr+0x00006338+4*2))=0x138982a2;
*((unsigned int *)((unsigned long)context_ptr+0x00006338+4*3))=0x23c6030a;
*((unsigned int *)((unsigned long)context_ptr+0x00006338+4*4))=0xe2fa621f;
*((unsigned int *)((unsigned long)context_ptr+0x00006338+4*5))=0x6415d150;
*((unsigned int *)((unsigned long)context_ptr+0x00006338+4*6))=0x690cfc94;
*((unsigned int *)((unsigned long)context_ptr+0x00006338+4*7))=0x000000eb;
*((unsigned int *)((unsigned long)context_ptr+0x000032a0))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x000032a0+4*1))=0x00006468;
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
*((unsigned int *)((unsigned long)context_ptr+0x000002a0+4*1))=0x00006338;
*((unsigned int *)((unsigned long)context_ptr+0x000002a0+4*2))=0x00006328;
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
if(!memcmp((unsigned char *)context_ptr+0x00006388,"\x53\xf1\xf6\xcb\x37\xfd\xa9\x45\x42\x41\xc1\xe3\xad\x23\xce\x79\x13\x62\x72\x6a\xe0\x3d\x92\xdb\x1e\x11\x72\x84\x00\x40\x02\x89",32))
printf("strip: 53f1f6cb37fda945, Pass\n");
else
printf("strip: 53f1f6cb37fda945, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006358))=0x01ea1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006358+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006358+4*2))=0x0202001e;
*((unsigned int *)((unsigned long)context_ptr+0x00006358+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x00006368))=0x9086aa90;
*((unsigned int *)((unsigned long)context_ptr+0x00006368+4*1))=0x66baaa5a;
*((unsigned int *)((unsigned long)context_ptr+0x00006368+4*2))=0x77e7bed0;
*((unsigned int *)((unsigned long)context_ptr+0x00006368+4*3))=0x6209c658;
*((unsigned int *)((unsigned long)context_ptr+0x00006368+4*4))=0x3f8357fa;
*((unsigned int *)((unsigned long)context_ptr+0x00006368+4*5))=0x9e6f1c13;
*((unsigned int *)((unsigned long)context_ptr+0x00006368+4*6))=0x0a1c848b;
*((unsigned int *)((unsigned long)context_ptr+0x00006368+4*7))=0x0000f15b;
*((unsigned int *)((unsigned long)context_ptr+0x000032b8))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x000032b8+4*1))=0x00006388;
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
*((unsigned int *)((unsigned long)context_ptr+0x000002b8+4*1))=0x00006368;
*((unsigned int *)((unsigned long)context_ptr+0x000002b8+4*2))=0x00006358;
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
if(!memcmp((unsigned char *)context_ptr+0x000063a8,"\xa1\x05\x07\x67\x46\x82\xe2\x11\x30\x5e\x5e\xc0\xc1\x8b\x22\xf9\x95\x81\xef\x00\xbd\x1a\xfa\xf8\xed\x49\x39\x52\x7c\xf2\x46\xff",32))
printf("strip: a10507674682e211, Pass\n");
else
printf("strip: a10507674682e211, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006058))=0x01ea1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*2))=0x0202001f;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x000063a8))=0x357f16b5;
*((unsigned int *)((unsigned long)context_ptr+0x000063a8+4*1))=0x685a8363;
*((unsigned int *)((unsigned long)context_ptr+0x000063a8+4*2))=0x9af40bbb;
*((unsigned int *)((unsigned long)context_ptr+0x000063a8+4*3))=0x80148e29;
*((unsigned int *)((unsigned long)context_ptr+0x000063a8+4*4))=0xac506bb0;
*((unsigned int *)((unsigned long)context_ptr+0x000063a8+4*5))=0xdd62dfef;
*((unsigned int *)((unsigned long)context_ptr+0x000063a8+4*6))=0xc3fb0f1d;
*((unsigned int *)((unsigned long)context_ptr+0x000063a8+4*7))=0x004f8f9d;
*((unsigned int *)((unsigned long)context_ptr+0x000032d0))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x000032d0+4*1))=0x00006488;
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
*((unsigned int *)((unsigned long)context_ptr+0x000002d0+4*1))=0x000063a8;
*((unsigned int *)((unsigned long)context_ptr+0x000002d0+4*2))=0x00006058;
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
if(!memcmp((unsigned char *)context_ptr+0x0000608c,"\xcb\xbc\x7d\xc4\x47\xdd\x34\x7c\xdc\x28\x90\xe8\xb9\xd8\x55\xa1\x70\x9a\xad\x1c\xb9\x5f\xd8\x0b\xdd\xf5\xb9\xdf\x00\x4d\x5d\x61",32))
printf("strip: cbbc7dc447dd347c, Pass\n");
else
printf("strip: cbbc7dc447dd347c, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006048))=0x01ea1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006048+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006048+4*2))=0x02020020;
*((unsigned int *)((unsigned long)context_ptr+0x00006048+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x00006078))=0x7c200093;
*((unsigned int *)((unsigned long)context_ptr+0x00006078+4*1))=0x2c38510a;
*((unsigned int *)((unsigned long)context_ptr+0x00006078+4*2))=0xa63be151;
*((unsigned int *)((unsigned long)context_ptr+0x00006078+4*3))=0x5930acbb;
*((unsigned int *)((unsigned long)context_ptr+0x00006078+4*4))=0x37f88945;
*((unsigned int *)((unsigned long)context_ptr+0x00006078+4*5))=0xf460108d;
*((unsigned int *)((unsigned long)context_ptr+0x00006078+4*6))=0xb7da18e8;
*((unsigned int *)((unsigned long)context_ptr+0x00006078+4*7))=0xe56c75ea;
*((unsigned int *)((unsigned long)context_ptr+0x000032e8))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x000032e8+4*1))=0x000064a8;
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
*((unsigned int *)((unsigned long)context_ptr+0x000002e8+4*1))=0x00006078;
*((unsigned int *)((unsigned long)context_ptr+0x000002e8+4*2))=0x00006048;
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
if(!memcmp((unsigned char *)context_ptr+0x000063c8,"\x57\x6a\x44\x25\xdb\x72\x58\x70\xf1\x1e\x0a\x1a\x73\xe3\xe3\x07\x68\x2e\x4a\x20\xfd\xcf\x6f\x7d\x86\x50\x4b\x81\x6c\x52\x9c\xff",32))
printf("strip: 576a4425db725870, Pass\n");
else
printf("strip: 576a4425db725870, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006068))=0x01ea1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006068+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006068+4*2))=0x02020021;
*((unsigned int *)((unsigned long)context_ptr+0x00006068+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x00006098))=0xb8544ad5;
*((unsigned int *)((unsigned long)context_ptr+0x00006098+4*1))=0x16e0b6aa;
*((unsigned int *)((unsigned long)context_ptr+0x00006098+4*2))=0xa79c7f1f;
*((unsigned int *)((unsigned long)context_ptr+0x00006098+4*3))=0x3deb223a;
*((unsigned int *)((unsigned long)context_ptr+0x00006098+4*4))=0xa2844804;
*((unsigned int *)((unsigned long)context_ptr+0x00006098+4*5))=0x518225bd;
*((unsigned int *)((unsigned long)context_ptr+0x00006098+4*6))=0x31cf5cb9;
*((unsigned int *)((unsigned long)context_ptr+0x00006098+4*7))=0xb96c85fe;
*((unsigned int *)((unsigned long)context_ptr+0x00006098+4*8))=0x00000060;
*((unsigned int *)((unsigned long)context_ptr+0x00003300))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003300+4*1))=0x000063c8;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000300+4*1))=0x00006098;
*((unsigned int *)((unsigned long)context_ptr+0x00000300+4*2))=0x00006068;
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
if(!memcmp((unsigned char *)context_ptr+0x000060f4,"\xe0\x1a\x6d\x08\xb5\x79\xda\xc7\x46\xc0\x34\xe3\xb4\xc3\xd2\x31\x50\xa1\x87\xdb\xbd\x4d\xd0\x51\xc5\x9d\x5b\x2d\x8e\xdb\x09\x33",32))
printf("strip: e01a6d08b579dac7, Pass\n");
else
printf("strip: e01a6d08b579dac7, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000060bc))=0x01ea1002;
*((unsigned int *)((unsigned long)context_ptr+0x000060bc+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000060bc+4*2))=0x02020022;
*((unsigned int *)((unsigned long)context_ptr+0x000060bc+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x000060cc))=0x0563a355;
*((unsigned int *)((unsigned long)context_ptr+0x000060cc+4*1))=0x97c63d4b;
*((unsigned int *)((unsigned long)context_ptr+0x000060cc+4*2))=0x5136df24;
*((unsigned int *)((unsigned long)context_ptr+0x000060cc+4*3))=0x846bc3df;
*((unsigned int *)((unsigned long)context_ptr+0x000060cc+4*4))=0xa7b7b5fa;
*((unsigned int *)((unsigned long)context_ptr+0x000060cc+4*5))=0x714cecfc;
*((unsigned int *)((unsigned long)context_ptr+0x000060cc+4*6))=0xe7a53ca2;
*((unsigned int *)((unsigned long)context_ptr+0x000060cc+4*7))=0x62735e4e;
*((unsigned int *)((unsigned long)context_ptr+0x000060cc+4*8))=0x00000da4;
*((unsigned int *)((unsigned long)context_ptr+0x00003318))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003318+4*1))=0x000060f0;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000318+4*1))=0x000060cc;
*((unsigned int *)((unsigned long)context_ptr+0x00000318+4*2))=0x000060bc;
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
if(!memcmp((unsigned char *)context_ptr+0x000063e8,"\xdd\x7c\x14\x10\x2b\x23\x01\xda\xc8\x2c\xca\xf5\xb1\x73\xd2\x71\x55\x7e\xdb\xcc\x3f\xc6\x1e\x00\x4f\x59\x9b\x9a\x1f\x32\xf9\x2d",32))
printf("strip: dd7c14102b2301da, Pass\n");
else
printf("strip: dd7c14102b2301da, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000063e8))=0x01ea1002;
*((unsigned int *)((unsigned long)context_ptr+0x000063e8+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000063e8+4*2))=0x02020023;
*((unsigned int *)((unsigned long)context_ptr+0x000063e8+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x00006110))=0x8b76ab5f;
*((unsigned int *)((unsigned long)context_ptr+0x00006110+4*1))=0x1b1a66f0;
*((unsigned int *)((unsigned long)context_ptr+0x00006110+4*2))=0xc71d4fb9;
*((unsigned int *)((unsigned long)context_ptr+0x00006110+4*3))=0xbd9d1ae3;
*((unsigned int *)((unsigned long)context_ptr+0x00006110+4*4))=0x71afd63e;
*((unsigned int *)((unsigned long)context_ptr+0x00006110+4*5))=0x2ad4422a;
*((unsigned int *)((unsigned long)context_ptr+0x00006110+4*6))=0x048f92b4;
*((unsigned int *)((unsigned long)context_ptr+0x00006110+4*7))=0x61a14f1f;
*((unsigned int *)((unsigned long)context_ptr+0x00006110+4*8))=0x00766241;
*((unsigned int *)((unsigned long)context_ptr+0x00003330))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003330+4*1))=0x000064c8;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000330+4*1))=0x00006110;
*((unsigned int *)((unsigned long)context_ptr+0x00000330+4*2))=0x000063e8;
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
if(!memcmp((unsigned char *)context_ptr+0x00006160,"\x95\x1a\xdd\x44\x04\xa1\x55\xc5\x76\x3e\x38\xda\xb2\x99\xa0\x00\xbe\x9c\xa0\x7e\xcb\x14\x91\x5e\xb5\x8c\x35\xb7\x3e\xd7\x6c\x69",32))
printf("strip: 951add4404a155c5, Pass\n");
else
printf("strip: 951add4404a155c5, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000063f8))=0x01ea1002;
*((unsigned int *)((unsigned long)context_ptr+0x000063f8+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000063f8+4*2))=0x02020024;
*((unsigned int *)((unsigned long)context_ptr+0x000063f8+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x00006134))=0xc2a561a4;
*((unsigned int *)((unsigned long)context_ptr+0x00006134+4*1))=0x8df848c5;
*((unsigned int *)((unsigned long)context_ptr+0x00006134+4*2))=0x27aca2a0;
*((unsigned int *)((unsigned long)context_ptr+0x00006134+4*3))=0xb6f76eac;
*((unsigned int *)((unsigned long)context_ptr+0x00006134+4*4))=0x96d5fdf9;
*((unsigned int *)((unsigned long)context_ptr+0x00006134+4*5))=0x6b5e7899;
*((unsigned int *)((unsigned long)context_ptr+0x00006134+4*6))=0x092ba5e9;
*((unsigned int *)((unsigned long)context_ptr+0x00006134+4*7))=0x3a107070;
*((unsigned int *)((unsigned long)context_ptr+0x00006134+4*8))=0x279f6054;
*((unsigned int *)((unsigned long)context_ptr+0x00003348))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003348+4*1))=0x00006158;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000348+4*1))=0x00006134;
*((unsigned int *)((unsigned long)context_ptr+0x00000348+4*2))=0x000063f8;
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
if(!memcmp((unsigned char *)context_ptr+0x00006408,"\x98\x88\x6b\xa6\xa9\xa6\x9a\x21\x05\x79\xd2\xf5\xfa\xca\x96\x70\x24\x91\x1e\x62\x38\x15\xfd\x76\x52\x77\x35\xd3\x82\x2b\xeb\x75",32))
printf("strip: 98886ba6a9a69a21, Pass\n");
else
printf("strip: 98886ba6a9a69a21, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006408))=0x01ea1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006408+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006408+4*2))=0x02020025;
*((unsigned int *)((unsigned long)context_ptr+0x00006408+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x00006178))=0x82d95f23;
*((unsigned int *)((unsigned long)context_ptr+0x00006178+4*1))=0xe1088114;
*((unsigned int *)((unsigned long)context_ptr+0x00006178+4*2))=0xe5feba3f;
*((unsigned int *)((unsigned long)context_ptr+0x00006178+4*3))=0x8bb25287;
*((unsigned int *)((unsigned long)context_ptr+0x00006178+4*4))=0x27b13de8;
*((unsigned int *)((unsigned long)context_ptr+0x00006178+4*5))=0x485dc767;
*((unsigned int *)((unsigned long)context_ptr+0x00006178+4*6))=0x24025f5a;
*((unsigned int *)((unsigned long)context_ptr+0x00006178+4*7))=0x23a7b1bd;
*((unsigned int *)((unsigned long)context_ptr+0x00006178+4*8))=0x207b7d1d;
*((unsigned int *)((unsigned long)context_ptr+0x00006178+4*9))=0x000000f7;
*((unsigned int *)((unsigned long)context_ptr+0x00003360))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003360+4*1))=0x000064e8;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000360+4*1))=0x00006178;
*((unsigned int *)((unsigned long)context_ptr+0x00000360+4*2))=0x00006408;
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
if(!memcmp((unsigned char *)context_ptr+0x000061d0,"\x71\x81\x8b\x93\x91\x1a\x0b\x5c\xfa\x4b\x79\x24\x0f\x1c\x5d\x8a\x14\x55\xfd\x5e\x4b\x54\x09\x10\x3c\xe5\x5d\x94\xdc\xfc\xf7\xbe",32))
printf("strip: 71818b93911a0b5c, Pass\n");
else
printf("strip: 71818b93911a0b5c, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006418))=0x01ea1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006418+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006418+4*2))=0x02020026;
*((unsigned int *)((unsigned long)context_ptr+0x00006418+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x000061a0))=0xc55dd255;
*((unsigned int *)((unsigned long)context_ptr+0x000061a0+4*1))=0xe67a5d04;
*((unsigned int *)((unsigned long)context_ptr+0x000061a0+4*2))=0xe6a2bbb8;
*((unsigned int *)((unsigned long)context_ptr+0x000061a0+4*3))=0xc3eba1b9;
*((unsigned int *)((unsigned long)context_ptr+0x000061a0+4*4))=0xbf30de03;
*((unsigned int *)((unsigned long)context_ptr+0x000061a0+4*5))=0x6d276469;
*((unsigned int *)((unsigned long)context_ptr+0x000061a0+4*6))=0xa4bcd3ff;
*((unsigned int *)((unsigned long)context_ptr+0x000061a0+4*7))=0xe8ee1036;
*((unsigned int *)((unsigned long)context_ptr+0x000061a0+4*8))=0x19bfe900;
*((unsigned int *)((unsigned long)context_ptr+0x000061a0+4*9))=0x00002d27;
*((unsigned int *)((unsigned long)context_ptr+0x00003378))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003378+4*1))=0x000061c8;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000378+4*1))=0x000061a0;
*((unsigned int *)((unsigned long)context_ptr+0x00000378+4*2))=0x00006418;
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
if(!memcmp((unsigned char *)context_ptr+0x00006428,"\x57\x6d\xa7\x4e\x88\x68\x3e\xb2\x00\x01\xab\x47\xd3\xc4\xc0\xe2\x40\xc3\x9a\xfa\x3c\x63\x7d\x05\xa2\x40\xa8\xee\x9e\x66\x44\x03",32))
printf("strip: 576da74e88683eb2, Pass\n");
else
printf("strip: 576da74e88683eb2, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006428))=0x01ea1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006428+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006428+4*2))=0x02020027;
*((unsigned int *)((unsigned long)context_ptr+0x00006428+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x000061e8))=0x90a00c92;
*((unsigned int *)((unsigned long)context_ptr+0x000061e8+4*1))=0x215b1490;
*((unsigned int *)((unsigned long)context_ptr+0x000061e8+4*2))=0xe1545e77;
*((unsigned int *)((unsigned long)context_ptr+0x000061e8+4*3))=0xffa81c9f;
*((unsigned int *)((unsigned long)context_ptr+0x000061e8+4*4))=0x79a8c55d;
*((unsigned int *)((unsigned long)context_ptr+0x000061e8+4*5))=0x446a3667;
*((unsigned int *)((unsigned long)context_ptr+0x000061e8+4*6))=0x25e3ab7c;
*((unsigned int *)((unsigned long)context_ptr+0x000061e8+4*7))=0x31a0c3cf;
*((unsigned int *)((unsigned long)context_ptr+0x000061e8+4*8))=0x4a522312;
*((unsigned int *)((unsigned long)context_ptr+0x000061e8+4*9))=0x002957cf;
*((unsigned int *)((unsigned long)context_ptr+0x00003390))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003390+4*1))=0x00006508;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000390+4*1))=0x000061e8;
*((unsigned int *)((unsigned long)context_ptr+0x00000390+4*2))=0x00006428;
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
if(!memcmp((unsigned char *)context_ptr+0x00006244,"\x78\xd7\xd3\x88\xec\x28\x31\xd9\x4d\xa8\x53\x3e\x74\x91\x2b\x9c\x1a\x67\x7d\x79\x0f\xb0\xc3\x70\x8b\x8d\xe5\x89\x96\xb8\x4c\x09",32))
printf("strip: 78d7d388ec2831d9, Pass\n");
else
printf("strip: 78d7d388ec2831d9, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006438))=0x01ea1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006438+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006438+4*2))=0x02020028;
*((unsigned int *)((unsigned long)context_ptr+0x00006438+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x00006210))=0xed7f590e;
*((unsigned int *)((unsigned long)context_ptr+0x00006210+4*1))=0x1970ea10;
*((unsigned int *)((unsigned long)context_ptr+0x00006210+4*2))=0x3c221ec0;
*((unsigned int *)((unsigned long)context_ptr+0x00006210+4*3))=0x96dca98c;
*((unsigned int *)((unsigned long)context_ptr+0x00006210+4*4))=0xa9817ba3;
*((unsigned int *)((unsigned long)context_ptr+0x00006210+4*5))=0x9f9f4b45;
*((unsigned int *)((unsigned long)context_ptr+0x00006210+4*6))=0xd58c322e;
*((unsigned int *)((unsigned long)context_ptr+0x00006210+4*7))=0x870c2c4f;
*((unsigned int *)((unsigned long)context_ptr+0x00006210+4*8))=0xa88b9c87;
*((unsigned int *)((unsigned long)context_ptr+0x00006210+4*9))=0x3acb51de;
*((unsigned int *)((unsigned long)context_ptr+0x000033a8))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x000033a8+4*1))=0x00006238;
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
*((unsigned int *)((unsigned long)context_ptr+0x000003a8+4*1))=0x00006210;
*((unsigned int *)((unsigned long)context_ptr+0x000003a8+4*2))=0x00006438;
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
if(!memcmp((unsigned char *)context_ptr+0x00006448,"\xad\xd5\x31\xf7\x88\xed\xd8\x36\xc7\xe9\x0d\x93\x79\xa9\x4d\xeb\xa1\xf9\xe8\x49\xa2\xbb\x8c\x61\x28\x68\xfc\xae\xd2\x2f\xa0\x40",32))
printf("strip: add531f788edd836, Pass\n");
else
printf("strip: add531f788edd836, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006448))=0x01ea1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006448+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006448+4*2))=0x02020029;
*((unsigned int *)((unsigned long)context_ptr+0x00006448+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x00006258))=0x29d745de;
*((unsigned int *)((unsigned long)context_ptr+0x00006258+4*1))=0xef1fa9da;
*((unsigned int *)((unsigned long)context_ptr+0x00006258+4*2))=0x0dd72f6f;
*((unsigned int *)((unsigned long)context_ptr+0x00006258+4*3))=0xbf17bc09;
*((unsigned int *)((unsigned long)context_ptr+0x00006258+4*4))=0x9023f018;
*((unsigned int *)((unsigned long)context_ptr+0x00006258+4*5))=0x7d185da5;
*((unsigned int *)((unsigned long)context_ptr+0x00006258+4*6))=0x3934e455;
*((unsigned int *)((unsigned long)context_ptr+0x00006258+4*7))=0x23497198;
*((unsigned int *)((unsigned long)context_ptr+0x00006258+4*8))=0xf0e718d6;
*((unsigned int *)((unsigned long)context_ptr+0x00006258+4*9))=0xca44ec21;
*((unsigned int *)((unsigned long)context_ptr+0x00006258+4*10))=0x00000053;
*((unsigned int *)((unsigned long)context_ptr+0x000033c0))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x000033c0+4*1))=0x00006528;
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
*((unsigned int *)((unsigned long)context_ptr+0x000003c0+4*1))=0x00006258;
*((unsigned int *)((unsigned long)context_ptr+0x000003c0+4*2))=0x00006448;
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
if(!memcmp((unsigned char *)context_ptr+0x000062bc,"\x31\x47\x25\x94\xdb\x1a\x0d\x3e\xff\x86\x9e\xc0\x54\xf6\xcb\xd0\x8d\x3b\x87\x53\x97\xdb\x8d\x2c\xca\x6f\x1e\x4c\xbe\xcb\x46\xd0",32))
printf("strip: 31472594db1a0d3e, Pass\n");
else
printf("strip: 31472594db1a0d3e, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006458))=0x01ea1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006458+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006458+4*2))=0x0202002a;
*((unsigned int *)((unsigned long)context_ptr+0x00006458+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x00006284))=0x60cb31a7;
*((unsigned int *)((unsigned long)context_ptr+0x00006284+4*1))=0x84719743;
*((unsigned int *)((unsigned long)context_ptr+0x00006284+4*2))=0x6edf09f8;
*((unsigned int *)((unsigned long)context_ptr+0x00006284+4*3))=0x79bce0d8;
*((unsigned int *)((unsigned long)context_ptr+0x00006284+4*4))=0xb6659885;
*((unsigned int *)((unsigned long)context_ptr+0x00006284+4*5))=0x90f456da;
*((unsigned int *)((unsigned long)context_ptr+0x00006284+4*6))=0x47b9294b;
*((unsigned int *)((unsigned long)context_ptr+0x00006284+4*7))=0x605af2cf;
*((unsigned int *)((unsigned long)context_ptr+0x00006284+4*8))=0xd3ff414d;
*((unsigned int *)((unsigned long)context_ptr+0x00006284+4*9))=0xd2f307dd;
*((unsigned int *)((unsigned long)context_ptr+0x00006284+4*10))=0x0000edd2;
*((unsigned int *)((unsigned long)context_ptr+0x000033d8))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x000033d8+4*1))=0x000062b0;
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
*((unsigned int *)((unsigned long)context_ptr+0x000003d8+4*1))=0x00006284;
*((unsigned int *)((unsigned long)context_ptr+0x000003d8+4*2))=0x00006458;
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
if(!memcmp((unsigned char *)context_ptr+0x00006308,"\x8c\x7a\xed\x44\x24\xc1\x3e\x35\x97\xf8\x83\x6a\xeb\x16\x21\x6f\x03\xb3\x67\xc2\xb0\x73\xd8\x87\x8d\x62\x6d\x9f\x86\x7b\x8b\x7c",32))
printf("strip: 8c7aed4424c13e35, Pass\n");
else
printf("strip: 8c7aed4424c13e35, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000062d0))=0x01ea1002;
*((unsigned int *)((unsigned long)context_ptr+0x000062d0+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000062d0+4*2))=0x0202002b;
*((unsigned int *)((unsigned long)context_ptr+0x000062d0+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x000062e0))=0xcfec84a1;
*((unsigned int *)((unsigned long)context_ptr+0x000062e0+4*1))=0x836aad98;
*((unsigned int *)((unsigned long)context_ptr+0x000062e0+4*2))=0x7533d6a1;
*((unsigned int *)((unsigned long)context_ptr+0x000062e0+4*3))=0x1e09322f;
*((unsigned int *)((unsigned long)context_ptr+0x000062e0+4*4))=0x244e54c1;
*((unsigned int *)((unsigned long)context_ptr+0x000062e0+4*5))=0x610e6a93;
*((unsigned int *)((unsigned long)context_ptr+0x000062e0+4*6))=0xdbf9c1ce;
*((unsigned int *)((unsigned long)context_ptr+0x000062e0+4*7))=0x68c9ca7f;
*((unsigned int *)((unsigned long)context_ptr+0x000062e0+4*8))=0x9f718f63;
*((unsigned int *)((unsigned long)context_ptr+0x000062e0+4*9))=0x86a4ebd0;
*((unsigned int *)((unsigned long)context_ptr+0x000062e0+4*10))=0x00396637;
*((unsigned int *)((unsigned long)context_ptr+0x000033f0))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x000033f0+4*1))=0x00006548;
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
*((unsigned int *)((unsigned long)context_ptr+0x000003f0+4*1))=0x000062e0;
*((unsigned int *)((unsigned long)context_ptr+0x000003f0+4*2))=0x000062d0;
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
if(!memcmp((unsigned char *)context_ptr+0x00006468,"\x15\x50\xb1\x04\x9f\xbd\x1c\xa6\x1b\x98\xac\xd2\xe4\xec\x61\xbb\x31\x86\xef\x5a\xcd\x2d\x83\xf1\xbe\x84\xc7\x80\x75\xa2\x4f\x83",32))
printf("strip: 1550b1049fbd1ca6, Pass\n");
else
printf("strip: 1550b1049fbd1ca6, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006468))=0x01ea1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006468+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006468+4*2))=0x0202002c;
*((unsigned int *)((unsigned long)context_ptr+0x00006468+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x0000630c))=0xa076fc1a;
*((unsigned int *)((unsigned long)context_ptr+0x0000630c+4*1))=0x66c41081;
*((unsigned int *)((unsigned long)context_ptr+0x0000630c+4*2))=0x244fd27b;
*((unsigned int *)((unsigned long)context_ptr+0x0000630c+4*3))=0x9710b00b;
*((unsigned int *)((unsigned long)context_ptr+0x0000630c+4*4))=0x4a641c11;
*((unsigned int *)((unsigned long)context_ptr+0x0000630c+4*5))=0xf6f2f11b;
*((unsigned int *)((unsigned long)context_ptr+0x0000630c+4*6))=0x6790e8fa;
*((unsigned int *)((unsigned long)context_ptr+0x0000630c+4*7))=0xc63a86bd;
*((unsigned int *)((unsigned long)context_ptr+0x0000630c+4*8))=0x89f3a629;
*((unsigned int *)((unsigned long)context_ptr+0x0000630c+4*9))=0x6e825b25;
*((unsigned int *)((unsigned long)context_ptr+0x0000630c+4*10))=0xf8e19926;
*((unsigned int *)((unsigned long)context_ptr+0x00003408))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003408+4*1))=0x00006338;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000408+4*1))=0x0000630c;
*((unsigned int *)((unsigned long)context_ptr+0x00000408+4*2))=0x00006468;
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
if(!memcmp((unsigned char *)context_ptr+0x00006388,"\x24\xa3\xe9\xe0\x61\xd6\x42\xd2\xac\xbd\xfa\x8b\xfc\x31\xfe\x3a\x0f\xb6\xf8\xf5\x5c\x95\x6c\x81\x3a\xd0\x24\x22\xc1\x1a\xeb\x96",32))
printf("strip: 24a3e9e061d642d2, Pass\n");
else
printf("strip: 24a3e9e061d642d2, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006478))=0x01ea1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006478+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006478+4*2))=0x0202002d;
*((unsigned int *)((unsigned long)context_ptr+0x00006478+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x00006368))=0xe9fd2add;
*((unsigned int *)((unsigned long)context_ptr+0x00006368+4*1))=0xddaac417;
*((unsigned int *)((unsigned long)context_ptr+0x00006368+4*2))=0xbcca4f7f;
*((unsigned int *)((unsigned long)context_ptr+0x00006368+4*3))=0x7fc4fc89;
*((unsigned int *)((unsigned long)context_ptr+0x00006368+4*4))=0x0cd781ed;
*((unsigned int *)((unsigned long)context_ptr+0x00006368+4*5))=0x233b3621;
*((unsigned int *)((unsigned long)context_ptr+0x00006368+4*6))=0xb9978f0a;
*((unsigned int *)((unsigned long)context_ptr+0x00006368+4*7))=0x0373749d;
*((unsigned int *)((unsigned long)context_ptr+0x00006368+4*8))=0xf6a0a29d;
*((unsigned int *)((unsigned long)context_ptr+0x00006368+4*9))=0x8d9c35b4;
*((unsigned int *)((unsigned long)context_ptr+0x00006368+4*10))=0x75c198ac;
*((unsigned int *)((unsigned long)context_ptr+0x00006368+4*11))=0x00000091;
*((unsigned int *)((unsigned long)context_ptr+0x00003420))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003420+4*1))=0x00006568;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000420+4*1))=0x00006368;
*((unsigned int *)((unsigned long)context_ptr+0x00000420+4*2))=0x00006478;
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
if(!memcmp((unsigned char *)context_ptr+0x00006488,"\x87\xe1\xe7\xb4\x6d\x23\xfd\x25\xb0\x40\x4f\x9e\x01\x2e\x25\x7f\x0e\x01\xd6\x5e\x31\x91\x18\x4e\xaf\x91\x73\x5e\x71\x46\xd1\xa9",32))
printf("strip: 87e1e7b46d23fd25, Pass\n");
else
printf("strip: 87e1e7b46d23fd25, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006358))=0x01ea1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006358+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006358+4*2))=0x0202002e;
*((unsigned int *)((unsigned long)context_ptr+0x00006358+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x00006398))=0xd4d113a0;
*((unsigned int *)((unsigned long)context_ptr+0x00006398+4*1))=0xe62cd4ce;
*((unsigned int *)((unsigned long)context_ptr+0x00006398+4*2))=0x2800434b;
*((unsigned int *)((unsigned long)context_ptr+0x00006398+4*3))=0x0cdf3b58;
*((unsigned int *)((unsigned long)context_ptr+0x00006398+4*4))=0xd5dd6071;
*((unsigned int *)((unsigned long)context_ptr+0x00006398+4*5))=0x4075ad53;
*((unsigned int *)((unsigned long)context_ptr+0x00006398+4*6))=0xbcb277b2;
*((unsigned int *)((unsigned long)context_ptr+0x00006398+4*7))=0x0223438f;
*((unsigned int *)((unsigned long)context_ptr+0x00006398+4*8))=0x48d3a96c;
*((unsigned int *)((unsigned long)context_ptr+0x00006398+4*9))=0x55567b11;
*((unsigned int *)((unsigned long)context_ptr+0x00006398+4*10))=0xb571850c;
*((unsigned int *)((unsigned long)context_ptr+0x00006398+4*11))=0x000061ad;
*((unsigned int *)((unsigned long)context_ptr+0x00003438))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003438+4*1))=0x00006488;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000438+4*1))=0x00006398;
*((unsigned int *)((unsigned long)context_ptr+0x00000438+4*2))=0x00006358;
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
if(!memcmp((unsigned char *)context_ptr+0x000064a8,"\xac\x92\x82\xd1\x0d\x9e\x06\x0c\xbc\x07\xab\x1e\x19\x51\xeb\xe8\x84\xf4\x4a\xd9\x21\x0c\x58\x4f\x70\xab\x37\x82\xfb\x60\xe7\xab",32))
printf("strip: ac9282d10d9e060c, Pass\n");
else
printf("strip: ac9282d10d9e060c, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006058))=0x01ea1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*2))=0x0202002f;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x00006588))=0x3469d1a9;
*((unsigned int *)((unsigned long)context_ptr+0x00006588+4*1))=0xa8987528;
*((unsigned int *)((unsigned long)context_ptr+0x00006588+4*2))=0x22003e96;
*((unsigned int *)((unsigned long)context_ptr+0x00006588+4*3))=0xfa91f870;
*((unsigned int *)((unsigned long)context_ptr+0x00006588+4*4))=0xb04afed7;
*((unsigned int *)((unsigned long)context_ptr+0x00006588+4*5))=0x679dde6e;
*((unsigned int *)((unsigned long)context_ptr+0x00006588+4*6))=0x6c7ed7f1;
*((unsigned int *)((unsigned long)context_ptr+0x00006588+4*7))=0x2a4f6767;
*((unsigned int *)((unsigned long)context_ptr+0x00006588+4*8))=0x289f1fd4;
*((unsigned int *)((unsigned long)context_ptr+0x00006588+4*9))=0x04203ade;
*((unsigned int *)((unsigned long)context_ptr+0x00006588+4*10))=0xdd50c9e7;
*((unsigned int *)((unsigned long)context_ptr+0x00006588+4*11))=0x00913882;
*((unsigned int *)((unsigned long)context_ptr+0x00003450))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003450+4*1))=0x00006078;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000450+4*1))=0x00006588;
*((unsigned int *)((unsigned long)context_ptr+0x00000450+4*2))=0x00006058;
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
if(!memcmp((unsigned char *)context_ptr+0x000063c8,"\xeb\xc8\x6f\x47\x6a\xcd\xfe\x05\x58\x21\x06\x6b\xc0\xb2\xc0\x8d\xa4\xd5\x17\x1f\xc0\x81\x56\x6f\x4e\x52\x51\x8c\x06\x98\xd1\x06",32))
printf("strip: ebc86f476acdfe05, Pass\n");
else
printf("strip: ebc86f476acdfe05, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006048))=0x01ea1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006048+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006048+4*2))=0x02020030;
*((unsigned int *)((unsigned long)context_ptr+0x00006048+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x000065b8))=0xcdab517b;
*((unsigned int *)((unsigned long)context_ptr+0x000065b8+4*1))=0x97aa6b1e;
*((unsigned int *)((unsigned long)context_ptr+0x000065b8+4*2))=0xe38bdedf;
*((unsigned int *)((unsigned long)context_ptr+0x000065b8+4*3))=0x620226ce;
*((unsigned int *)((unsigned long)context_ptr+0x000065b8+4*4))=0x84cf075d;
*((unsigned int *)((unsigned long)context_ptr+0x000065b8+4*5))=0x66ced5f9;
*((unsigned int *)((unsigned long)context_ptr+0x000065b8+4*6))=0x8d1ab6f1;
*((unsigned int *)((unsigned long)context_ptr+0x000065b8+4*7))=0x0a67a436;
*((unsigned int *)((unsigned long)context_ptr+0x000065b8+4*8))=0x35a3ebe6;
*((unsigned int *)((unsigned long)context_ptr+0x000065b8+4*9))=0x351db169;
*((unsigned int *)((unsigned long)context_ptr+0x000065b8+4*10))=0x23c1ef17;
*((unsigned int *)((unsigned long)context_ptr+0x000065b8+4*11))=0x37f9a83c;
*((unsigned int *)((unsigned long)context_ptr+0x00003468))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003468+4*1))=0x000063c8;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000468+4*1))=0x000065b8;
*((unsigned int *)((unsigned long)context_ptr+0x00000468+4*2))=0x00006048;
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
if(!memcmp((unsigned char *)context_ptr+0x000060f0,"\xd5\x46\xd3\x43\xbd\x35\x1d\x75\x1e\x84\x03\xfd\xa8\xe2\x41\x5d\xa4\xbf\xc6\x77\xe4\xb2\xc3\x9d\xb0\xba\x18\x68\x6b\xe1\x40\x7f",32))
printf("strip: d546d343bd351d75, Pass\n");
else
printf("strip: d546d343bd351d75, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006068))=0x01ea1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006068+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006068+4*2))=0x02020031;
*((unsigned int *)((unsigned long)context_ptr+0x00006068+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x00006098))=0x9f680c05;
*((unsigned int *)((unsigned long)context_ptr+0x00006098+4*1))=0x61e6a473;
*((unsigned int *)((unsigned long)context_ptr+0x00006098+4*2))=0x560bcb6b;
*((unsigned int *)((unsigned long)context_ptr+0x00006098+4*3))=0xa9aca70f;
*((unsigned int *)((unsigned long)context_ptr+0x00006098+4*4))=0xa103be9e;
*((unsigned int *)((unsigned long)context_ptr+0x00006098+4*5))=0x08c1d5a1;
*((unsigned int *)((unsigned long)context_ptr+0x00006098+4*6))=0x1b476997;
*((unsigned int *)((unsigned long)context_ptr+0x00006098+4*7))=0x7b3d271f;
*((unsigned int *)((unsigned long)context_ptr+0x00006098+4*8))=0x8534429a;
*((unsigned int *)((unsigned long)context_ptr+0x00006098+4*9))=0x643a137c;
*((unsigned int *)((unsigned long)context_ptr+0x00006098+4*10))=0xdf3f75ef;
*((unsigned int *)((unsigned long)context_ptr+0x00006098+4*11))=0x7ddf27ff;
*((unsigned int *)((unsigned long)context_ptr+0x00006098+4*12))=0x00000041;
*((unsigned int *)((unsigned long)context_ptr+0x00003480))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003480+4*1))=0x000064a8;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000480+4*1))=0x00006098;
*((unsigned int *)((unsigned long)context_ptr+0x00000480+4*2))=0x00006068;
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
if(!memcmp((unsigned char *)context_ptr+0x000064c8,"\x63\x93\x8f\xc2\x66\x97\xce\x70\x32\x51\xcb\x3a\x1f\xac\x78\x7e\x25\xc2\xc7\x33\x5e\xa8\x8c\x4d\x29\x51\x83\xa8\x4a\x23\xc3\xfb",32))
printf("strip: 63938fc26697ce70, Pass\n");
else
printf("strip: 63938fc26697ce70, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000063e8))=0x01ea1002;
*((unsigned int *)((unsigned long)context_ptr+0x000063e8+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000063e8+4*2))=0x02020032;
*((unsigned int *)((unsigned long)context_ptr+0x000063e8+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x000060cc))=0x4d71b703;
*((unsigned int *)((unsigned long)context_ptr+0x000060cc+4*1))=0xf8ce6186;
*((unsigned int *)((unsigned long)context_ptr+0x000060cc+4*2))=0x02a709a6;
*((unsigned int *)((unsigned long)context_ptr+0x000060cc+4*3))=0x06dd1766;
*((unsigned int *)((unsigned long)context_ptr+0x000060cc+4*4))=0x428276ad;
*((unsigned int *)((unsigned long)context_ptr+0x000060cc+4*5))=0x7d736e60;
*((unsigned int *)((unsigned long)context_ptr+0x000060cc+4*6))=0x84dca1d5;
*((unsigned int *)((unsigned long)context_ptr+0x000060cc+4*7))=0xbcb6a086;
*((unsigned int *)((unsigned long)context_ptr+0x000060cc+4*8))=0xbc46668f;
*((unsigned int *)((unsigned long)context_ptr+0x000060cc+4*9))=0xe5fdf50f;
*((unsigned int *)((unsigned long)context_ptr+0x000060cc+4*10))=0xd599f5e3;
*((unsigned int *)((unsigned long)context_ptr+0x000060cc+4*11))=0x5a05752f;
*((unsigned int *)((unsigned long)context_ptr+0x000060cc+4*12))=0x00002c6f;
*((unsigned int *)((unsigned long)context_ptr+0x00003498))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003498+4*1))=0x000064c8;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000498+4*1))=0x000060cc;
*((unsigned int *)((unsigned long)context_ptr+0x00000498+4*2))=0x000063e8;
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
if(!memcmp((unsigned char *)context_ptr+0x00006158,"\x3a\x4e\x6b\x02\xe0\xeb\xdf\xa3\x6f\x47\x64\x57\x54\xab\x64\xf6\x96\x2d\x71\xe7\x19\x19\x0a\x75\xce\x18\x5a\x32\x06\x96\xbe\xa0",32))
printf("strip: 3a4e6b02e0ebdfa3, Pass\n");
else
printf("strip: 3a4e6b02e0ebdfa3, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000063f8))=0x01ea1002;
*((unsigned int *)((unsigned long)context_ptr+0x000063f8+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000063f8+4*2))=0x02020033;
*((unsigned int *)((unsigned long)context_ptr+0x000063f8+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x00006100))=0xb06f0a4b;
*((unsigned int *)((unsigned long)context_ptr+0x00006100+4*1))=0x6b1a2a02;
*((unsigned int *)((unsigned long)context_ptr+0x00006100+4*2))=0x5a6644df;
*((unsigned int *)((unsigned long)context_ptr+0x00006100+4*3))=0x0a371727;
*((unsigned int *)((unsigned long)context_ptr+0x00006100+4*4))=0xfd47c264;
*((unsigned int *)((unsigned long)context_ptr+0x00006100+4*5))=0x9191c181;
*((unsigned int *)((unsigned long)context_ptr+0x00006100+4*6))=0x2934c8c8;
*((unsigned int *)((unsigned long)context_ptr+0x00006100+4*7))=0x3b143b2f;
*((unsigned int *)((unsigned long)context_ptr+0x00006100+4*8))=0x9d07a165;
*((unsigned int *)((unsigned long)context_ptr+0x00006100+4*9))=0x91a7e4b5;
*((unsigned int *)((unsigned long)context_ptr+0x00006100+4*10))=0xcd9c614c;
*((unsigned int *)((unsigned long)context_ptr+0x00006100+4*11))=0x9e5daa59;
*((unsigned int *)((unsigned long)context_ptr+0x00006100+4*12))=0x00a8190b;
*((unsigned int *)((unsigned long)context_ptr+0x000034b0))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x000034b0+4*1))=0x00006134;
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
*((unsigned int *)((unsigned long)context_ptr+0x000004b0+4*1))=0x00006100;
*((unsigned int *)((unsigned long)context_ptr+0x000004b0+4*2))=0x000063f8;
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
if(!memcmp((unsigned char *)context_ptr+0x000064e8,"\xe2\x2d\x8a\xdf\x77\xc1\xab\xb4\x39\x20\x99\xfa\xb8\xa1\x6b\x26\xcf\x79\xd2\x52\x42\x33\x7f\x46\x3e\xdf\xe9\xfd\xfc\xfa\x8b\xa2",32))
printf("strip: e22d8adf77c1abb4, Pass\n");
else
printf("strip: e22d8adf77c1abb4, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006408))=0x01ea1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006408+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006408+4*2))=0x02020034;
*((unsigned int *)((unsigned long)context_ptr+0x00006408+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x00006154))=0x40119b2c;
*((unsigned int *)((unsigned long)context_ptr+0x00006154+4*1))=0xe4fac325;
*((unsigned int *)((unsigned long)context_ptr+0x00006154+4*2))=0xa8e8a437;
*((unsigned int *)((unsigned long)context_ptr+0x00006154+4*3))=0xa554720f;
*((unsigned int *)((unsigned long)context_ptr+0x00006154+4*4))=0x0e0ca80f;
*((unsigned int *)((unsigned long)context_ptr+0x00006154+4*5))=0x43c4dd3a;
*((unsigned int *)((unsigned long)context_ptr+0x00006154+4*6))=0x8eee4202;
*((unsigned int *)((unsigned long)context_ptr+0x00006154+4*7))=0xd8a1b914;
*((unsigned int *)((unsigned long)context_ptr+0x00006154+4*8))=0xe0add8fa;
*((unsigned int *)((unsigned long)context_ptr+0x00006154+4*9))=0x4c83369e;
*((unsigned int *)((unsigned long)context_ptr+0x00006154+4*10))=0x49112f3f;
*((unsigned int *)((unsigned long)context_ptr+0x00006154+4*11))=0x1c8782e0;
*((unsigned int *)((unsigned long)context_ptr+0x00006154+4*12))=0x2ff71ef5;
*((unsigned int *)((unsigned long)context_ptr+0x000034c8))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x000034c8+4*1))=0x000064e8;
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
*((unsigned int *)((unsigned long)context_ptr+0x000004c8+4*1))=0x00006154;
*((unsigned int *)((unsigned long)context_ptr+0x000004c8+4*2))=0x00006408;
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
if(!memcmp((unsigned char *)context_ptr+0x000061c8,"\x49\x30\xca\x31\x12\xc8\x25\xe7\xfc\x27\x09\x46\x32\xad\x3a\x39\xca\x95\xa3\x40\x24\xfa\xa5\xb6\xf5\x26\x2d\xc2\x81\x50\x75\xfe",32))
printf("strip: 4930ca3112c825e7, Pass\n");
else
printf("strip: 4930ca3112c825e7, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006418))=0x01ea1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006418+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006418+4*2))=0x02020035;
*((unsigned int *)((unsigned long)context_ptr+0x00006418+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x00006188))=0x6011caab;
*((unsigned int *)((unsigned long)context_ptr+0x00006188+4*1))=0xda563135;
*((unsigned int *)((unsigned long)context_ptr+0x00006188+4*2))=0xc9d91060;
*((unsigned int *)((unsigned long)context_ptr+0x00006188+4*3))=0x5b270b8c;
*((unsigned int *)((unsigned long)context_ptr+0x00006188+4*4))=0xf7c44c6a;
*((unsigned int *)((unsigned long)context_ptr+0x00006188+4*5))=0x23732b6d;
*((unsigned int *)((unsigned long)context_ptr+0x00006188+4*6))=0x5afb6876;
*((unsigned int *)((unsigned long)context_ptr+0x00006188+4*7))=0xb2b4ee1f;
*((unsigned int *)((unsigned long)context_ptr+0x00006188+4*8))=0x4ab63453;
*((unsigned int *)((unsigned long)context_ptr+0x00006188+4*9))=0xa270189d;
*((unsigned int *)((unsigned long)context_ptr+0x00006188+4*10))=0x743aa38c;
*((unsigned int *)((unsigned long)context_ptr+0x00006188+4*11))=0xa5351310;
*((unsigned int *)((unsigned long)context_ptr+0x00006188+4*12))=0x015b99cb;
*((unsigned int *)((unsigned long)context_ptr+0x00006188+4*13))=0x000000b1;
*((unsigned int *)((unsigned long)context_ptr+0x000034e0))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x000034e0+4*1))=0x000061c0;
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
*((unsigned int *)((unsigned long)context_ptr+0x000004e0+4*1))=0x00006188;
*((unsigned int *)((unsigned long)context_ptr+0x000004e0+4*2))=0x00006418;
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
if(!memcmp((unsigned char *)context_ptr+0x00006508,"\xd2\x64\xa4\x7a\x80\x88\xb6\xda\x1e\xf2\xbc\xd6\xe5\xe4\xc4\xcf\xd2\xa6\xfa\x9c\x99\xff\x31\x95\x61\xb4\x59\x06\x38\x38\x60\x15",32))
printf("strip: d264a47a8088b6da, Pass\n");
else
printf("strip: d264a47a8088b6da, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006428))=0x01ea1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006428+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006428+4*2))=0x02020036;
*((unsigned int *)((unsigned long)context_ptr+0x00006428+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x000065e8))=0xca6c1a7d;
*((unsigned int *)((unsigned long)context_ptr+0x000065e8+4*1))=0xd166d75d;
*((unsigned int *)((unsigned long)context_ptr+0x000065e8+4*2))=0xec01abc2;
*((unsigned int *)((unsigned long)context_ptr+0x000065e8+4*3))=0xdc03175d;
*((unsigned int *)((unsigned long)context_ptr+0x000065e8+4*4))=0xeffc966b;
*((unsigned int *)((unsigned long)context_ptr+0x000065e8+4*5))=0x6ba4bba1;
*((unsigned int *)((unsigned long)context_ptr+0x000065e8+4*6))=0x364c351d;
*((unsigned int *)((unsigned long)context_ptr+0x000065e8+4*7))=0xb23c34ee;
*((unsigned int *)((unsigned long)context_ptr+0x000065e8+4*8))=0xd04ba3f8;
*((unsigned int *)((unsigned long)context_ptr+0x000065e8+4*9))=0xc07ea628;
*((unsigned int *)((unsigned long)context_ptr+0x000065e8+4*10))=0xd7009f7c;
*((unsigned int *)((unsigned long)context_ptr+0x000065e8+4*11))=0xfdf232b9;
*((unsigned int *)((unsigned long)context_ptr+0x000065e8+4*12))=0x4efdd6a0;
*((unsigned int *)((unsigned long)context_ptr+0x000065e8+4*13))=0x0000522f;
*((unsigned int *)((unsigned long)context_ptr+0x000034f8))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x000034f8+4*1))=0x00006508;
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
*((unsigned int *)((unsigned long)context_ptr+0x000004f8+4*1))=0x000065e8;
*((unsigned int *)((unsigned long)context_ptr+0x000004f8+4*2))=0x00006428;
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
if(!memcmp((unsigned char *)context_ptr+0x00006238,"\x4b\x47\x95\x15\x11\xb6\x6d\x8b\x34\xf3\x2b\x10\x38\xfd\x88\x03\x6e\x95\xd2\x03\xdc\x42\xcd\x4d\x01\x19\x51\xdb\xf1\xaf\xd4\x1e",32))
printf("strip: 4b47951511b66d8b, Pass\n");
else
printf("strip: 4b47951511b66d8b, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006438))=0x01ea1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006438+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006438+4*2))=0x02020037;
*((unsigned int *)((unsigned long)context_ptr+0x00006438+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x000061e0))=0xfc18e89d;
*((unsigned int *)((unsigned long)context_ptr+0x000061e0+4*1))=0xf259074e;
*((unsigned int *)((unsigned long)context_ptr+0x000061e0+4*2))=0xad467e4a;
*((unsigned int *)((unsigned long)context_ptr+0x000061e0+4*3))=0xa01bec5f;
*((unsigned int *)((unsigned long)context_ptr+0x000061e0+4*4))=0xc6885efc;
*((unsigned int *)((unsigned long)context_ptr+0x000061e0+4*5))=0xe1da7925;
*((unsigned int *)((unsigned long)context_ptr+0x000061e0+4*6))=0xae88cc86;
*((unsigned int *)((unsigned long)context_ptr+0x000061e0+4*7))=0x0b1713cf;
*((unsigned int *)((unsigned long)context_ptr+0x000061e0+4*8))=0x5b8138e5;
*((unsigned int *)((unsigned long)context_ptr+0x000061e0+4*9))=0x1bde5963;
*((unsigned int *)((unsigned long)context_ptr+0x000061e0+4*10))=0x789580bd;
*((unsigned int *)((unsigned long)context_ptr+0x000061e0+4*11))=0x69698bc6;
*((unsigned int *)((unsigned long)context_ptr+0x000061e0+4*12))=0xfa3e8d6c;
*((unsigned int *)((unsigned long)context_ptr+0x000061e0+4*13))=0x008856dc;
*((unsigned int *)((unsigned long)context_ptr+0x00003510))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003510+4*1))=0x00006218;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000510+4*1))=0x000061e0;
*((unsigned int *)((unsigned long)context_ptr+0x00000510+4*2))=0x00006438;
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
if(!memcmp((unsigned char *)context_ptr+0x00006528,"\xe4\xbb\xde\x68\x18\xd9\x9e\x38\x9d\x94\x9d\x6e\xe2\xa1\x64\x76\xab\xb7\x30\x6a\x64\x7f\xd3\x2e\xae\xb2\x26\xed\x71\xa0\x59\x42",32))
printf("strip: e4bbde6818d99e38, Pass\n");
else
printf("strip: e4bbde6818d99e38, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006448))=0x01ea1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006448+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006448+4*2))=0x02020038;
*((unsigned int *)((unsigned long)context_ptr+0x00006448+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x00006238))=0x2929e730;
*((unsigned int *)((unsigned long)context_ptr+0x00006238+4*1))=0xacc2556b;
*((unsigned int *)((unsigned long)context_ptr+0x00006238+4*2))=0x1a861c0f;
*((unsigned int *)((unsigned long)context_ptr+0x00006238+4*3))=0x029eb78f;
*((unsigned int *)((unsigned long)context_ptr+0x00006238+4*4))=0x867541ef;
*((unsigned int *)((unsigned long)context_ptr+0x00006238+4*5))=0xd6a84ffa;
*((unsigned int *)((unsigned long)context_ptr+0x00006238+4*6))=0x21473990;
*((unsigned int *)((unsigned long)context_ptr+0x00006238+4*7))=0xeb547ebb;
*((unsigned int *)((unsigned long)context_ptr+0x00006238+4*8))=0x649e2033;
*((unsigned int *)((unsigned long)context_ptr+0x00006238+4*9))=0x049b9661;
*((unsigned int *)((unsigned long)context_ptr+0x00006238+4*10))=0x36080c19;
*((unsigned int *)((unsigned long)context_ptr+0x00006238+4*11))=0x933113e9;
*((unsigned int *)((unsigned long)context_ptr+0x00006238+4*12))=0xb035aa60;
*((unsigned int *)((unsigned long)context_ptr+0x00006238+4*13))=0x9d6d5a13;
*((unsigned int *)((unsigned long)context_ptr+0x00003528))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003528+4*1))=0x00006528;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000528+4*1))=0x00006238;
*((unsigned int *)((unsigned long)context_ptr+0x00000528+4*2))=0x00006448;
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
if(!memcmp((unsigned char *)context_ptr+0x000062b0,"\xf9\x15\x8d\x9f\x40\xef\x25\x7e\x70\xa4\xa0\xaf\x48\x63\x7a\xcf\x54\x08\xde\xec\x5b\xc4\x26\x76\x36\x3f\x7f\x69\x6c\x00\xb5\x2d",32))
printf("strip: f9158d9f40ef257e, Pass\n");
else
printf("strip: f9158d9f40ef257e, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006458))=0x01ea1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006458+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006458+4*2))=0x02020039;
*((unsigned int *)((unsigned long)context_ptr+0x00006458+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x00006270))=0x50520ad7;
*((unsigned int *)((unsigned long)context_ptr+0x00006270+4*1))=0x7dfd5329;
*((unsigned int *)((unsigned long)context_ptr+0x00006270+4*2))=0xebfcc912;
*((unsigned int *)((unsigned long)context_ptr+0x00006270+4*3))=0x92d2679c;
*((unsigned int *)((unsigned long)context_ptr+0x00006270+4*4))=0xb279aa2d;
*((unsigned int *)((unsigned long)context_ptr+0x00006270+4*5))=0x4a4d4a34;
*((unsigned int *)((unsigned long)context_ptr+0x00006270+4*6))=0x03aa59b4;
*((unsigned int *)((unsigned long)context_ptr+0x00006270+4*7))=0x0cea7706;
*((unsigned int *)((unsigned long)context_ptr+0x00006270+4*8))=0x124fff15;
*((unsigned int *)((unsigned long)context_ptr+0x00006270+4*9))=0x96391410;
*((unsigned int *)((unsigned long)context_ptr+0x00006270+4*10))=0x55f1d708;
*((unsigned int *)((unsigned long)context_ptr+0x00006270+4*11))=0xd4069bd4;
*((unsigned int *)((unsigned long)context_ptr+0x00006270+4*12))=0x67babbf9;
*((unsigned int *)((unsigned long)context_ptr+0x00006270+4*13))=0xd45b06da;
*((unsigned int *)((unsigned long)context_ptr+0x00006270+4*14))=0x0000002b;
*((unsigned int *)((unsigned long)context_ptr+0x00003540))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003540+4*1))=0x000062ac;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000540+4*1))=0x00006270;
*((unsigned int *)((unsigned long)context_ptr+0x00000540+4*2))=0x00006458;
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
if(!memcmp((unsigned char *)context_ptr+0x00006548,"\x84\x83\xf0\x8b\x35\x1b\xc4\xb7\x03\x92\x1a\xad\xc4\x07\xfe\x17\xf3\xe6\xd4\x80\x0d\x8f\xcd\xe0\x31\xcd\x4f\x54\x26\x2e\xee\xd4",32))
printf("strip: 8483f08b351bc4b7, Pass\n");
else
printf("strip: 8483f08b351bc4b7, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006548))=0x01ea1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006548+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006548+4*2))=0x0202003a;
*((unsigned int *)((unsigned long)context_ptr+0x00006548+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x000062cc))=0x9758f762;
*((unsigned int *)((unsigned long)context_ptr+0x000062cc+4*1))=0x5f3b6a74;
*((unsigned int *)((unsigned long)context_ptr+0x000062cc+4*2))=0xf4ff74d4;
*((unsigned int *)((unsigned long)context_ptr+0x000062cc+4*3))=0x09b42142;
*((unsigned int *)((unsigned long)context_ptr+0x000062cc+4*4))=0x753c4a32;
*((unsigned int *)((unsigned long)context_ptr+0x000062cc+4*5))=0x2e527cf3;
*((unsigned int *)((unsigned long)context_ptr+0x000062cc+4*6))=0x89380080;
*((unsigned int *)((unsigned long)context_ptr+0x000062cc+4*7))=0x4f555fdd;
*((unsigned int *)((unsigned long)context_ptr+0x000062cc+4*8))=0xace683dd;
*((unsigned int *)((unsigned long)context_ptr+0x000062cc+4*9))=0x0e156341;
*((unsigned int *)((unsigned long)context_ptr+0x000062cc+4*10))=0x3ad295ed;
*((unsigned int *)((unsigned long)context_ptr+0x000062cc+4*11))=0xd0208a8f;
*((unsigned int *)((unsigned long)context_ptr+0x000062cc+4*12))=0x952cebf0;
*((unsigned int *)((unsigned long)context_ptr+0x000062cc+4*13))=0xe27ffdf0;
*((unsigned int *)((unsigned long)context_ptr+0x000062cc+4*14))=0x0000e0dc;
*((unsigned int *)((unsigned long)context_ptr+0x00003558))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003558+4*1))=0x00006620;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000558+4*1))=0x000062cc;
*((unsigned int *)((unsigned long)context_ptr+0x00000558+4*2))=0x00006548;
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
if(!memcmp((unsigned char *)context_ptr+0x00006338,"\x35\xb7\x24\xaa\x77\x52\x3b\xb7\x2b\xd2\xea\x14\x1f\xb1\x37\x28\x64\x81\xf6\xef\x5a\x19\x15\x16\xe5\x3d\x70\xcb\xa2\x17\x42\x0b",32))
printf("strip: 35b724aa77523bb7, Pass\n");
else
printf("strip: 35b724aa77523bb7, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006558))=0x01ea1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006558+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006558+4*2))=0x0202003b;
*((unsigned int *)((unsigned long)context_ptr+0x00006558+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x00006308))=0xf0b38bd2;
*((unsigned int *)((unsigned long)context_ptr+0x00006308+4*1))=0x9fcaba1e;
*((unsigned int *)((unsigned long)context_ptr+0x00006308+4*2))=0x261850bb;
*((unsigned int *)((unsigned long)context_ptr+0x00006308+4*3))=0x752e7ed5;
*((unsigned int *)((unsigned long)context_ptr+0x00006308+4*4))=0x2f067b86;
*((unsigned int *)((unsigned long)context_ptr+0x00006308+4*5))=0x4fc65799;
*((unsigned int *)((unsigned long)context_ptr+0x00006308+4*6))=0x4d5290c9;
*((unsigned int *)((unsigned long)context_ptr+0x00006308+4*7))=0xebc71267;
*((unsigned int *)((unsigned long)context_ptr+0x00006308+4*8))=0x18c996a3;
*((unsigned int *)((unsigned long)context_ptr+0x00006308+4*9))=0x9027afbf;
*((unsigned int *)((unsigned long)context_ptr+0x00006308+4*10))=0x1a143dcd;
*((unsigned int *)((unsigned long)context_ptr+0x00006308+4*11))=0x7ad5624e;
*((unsigned int *)((unsigned long)context_ptr+0x00006308+4*12))=0xf9b33cc3;
*((unsigned int *)((unsigned long)context_ptr+0x00006308+4*13))=0x130edc69;
*((unsigned int *)((unsigned long)context_ptr+0x00006308+4*14))=0x00d4dc0a;
*((unsigned int *)((unsigned long)context_ptr+0x00003570))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003570+4*1))=0x00006640;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000570+4*1))=0x00006308;
*((unsigned int *)((unsigned long)context_ptr+0x00000570+4*2))=0x00006558;
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
if(!memcmp((unsigned char *)context_ptr+0x00006568,"\x2d\x09\x24\x20\x4e\x10\x91\x66\x02\xc7\x2e\x4a\xf3\x74\x0b\x22\x3d\xfc\xd9\x73\xf4\xd2\x98\xa9\x37\x15\xc5\xb7\x03\x8e\x3d\xed",32))
printf("strip: 2d0924204e109166, Pass\n");
else
printf("strip: 2d0924204e109166, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006344))=0x01ea1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006344+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006344+4*2))=0x0202003c;
*((unsigned int *)((unsigned long)context_ptr+0x00006344+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x00006660))=0x5a5f2bcd;
*((unsigned int *)((unsigned long)context_ptr+0x00006660+4*1))=0xa6c1a82b;
*((unsigned int *)((unsigned long)context_ptr+0x00006660+4*2))=0x7f6a17bc;
*((unsigned int *)((unsigned long)context_ptr+0x00006660+4*3))=0x868a74f7;
*((unsigned int *)((unsigned long)context_ptr+0x00006660+4*4))=0xeee4002d;
*((unsigned int *)((unsigned long)context_ptr+0x00006660+4*5))=0x92e12704;
*((unsigned int *)((unsigned long)context_ptr+0x00006660+4*6))=0x42cd8515;
*((unsigned int *)((unsigned long)context_ptr+0x00006660+4*7))=0x0164bc6c;
*((unsigned int *)((unsigned long)context_ptr+0x00006660+4*8))=0x6ab08d48;
*((unsigned int *)((unsigned long)context_ptr+0x00006660+4*9))=0xddf9b451;
*((unsigned int *)((unsigned long)context_ptr+0x00006660+4*10))=0x35a9207e;
*((unsigned int *)((unsigned long)context_ptr+0x00006660+4*11))=0xb639a03a;
*((unsigned int *)((unsigned long)context_ptr+0x00006660+4*12))=0x76cd6e81;
*((unsigned int *)((unsigned long)context_ptr+0x00006660+4*13))=0xe4be9eb8;
*((unsigned int *)((unsigned long)context_ptr+0x00006660+4*14))=0x3701ad36;
*((unsigned int *)((unsigned long)context_ptr+0x00003588))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003588+4*1))=0x00006468;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000588+4*1))=0x00006660;
*((unsigned int *)((unsigned long)context_ptr+0x00000588+4*2))=0x00006344;
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
if(!memcmp((unsigned char *)context_ptr+0x00006488,"\xd0\xac\x23\xe6\x35\x5e\x85\x41\xc2\xe2\x5a\x4e\xfe\xb7\x26\x68\x01\x20\xd4\x7f\xc2\xfd\x03\xae\x32\xff\xb4\x91\x9a\x97\x04\x84",32))
printf("strip: d0ac23e6355e8541, Pass\n");
else
printf("strip: d0ac23e6355e8541, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006488))=0x01ea1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006488+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006488+4*2))=0x0202003d;
*((unsigned int *)((unsigned long)context_ptr+0x00006488+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x00006354))=0xf1406791;
*((unsigned int *)((unsigned long)context_ptr+0x00006354+4*1))=0xa249a296;
*((unsigned int *)((unsigned long)context_ptr+0x00006354+4*2))=0x418a948d;
*((unsigned int *)((unsigned long)context_ptr+0x00006354+4*3))=0x4d4f14a7;
*((unsigned int *)((unsigned long)context_ptr+0x00006354+4*4))=0xda34006f;
*((unsigned int *)((unsigned long)context_ptr+0x00006354+4*5))=0x839b03ca;
*((unsigned int *)((unsigned long)context_ptr+0x00006354+4*6))=0x615cbd18;
*((unsigned int *)((unsigned long)context_ptr+0x00006354+4*7))=0xd7d59b5d;
*((unsigned int *)((unsigned long)context_ptr+0x00006354+4*8))=0x9f0fe550;
*((unsigned int *)((unsigned long)context_ptr+0x00006354+4*9))=0x6a6af4b3;
*((unsigned int *)((unsigned long)context_ptr+0x00006354+4*10))=0x59f757a0;
*((unsigned int *)((unsigned long)context_ptr+0x00006354+4*11))=0xff415625;
*((unsigned int *)((unsigned long)context_ptr+0x00006354+4*12))=0x4846bbe3;
*((unsigned int *)((unsigned long)context_ptr+0x00006354+4*13))=0x1a389526;
*((unsigned int *)((unsigned long)context_ptr+0x00006354+4*14))=0x21a044e6;
*((unsigned int *)((unsigned long)context_ptr+0x00006354+4*15))=0x00000048;
*((unsigned int *)((unsigned long)context_ptr+0x000035a0))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x000035a0+4*1))=0x00006568;
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
*((unsigned int *)((unsigned long)context_ptr+0x000005a0+4*1))=0x00006354;
*((unsigned int *)((unsigned long)context_ptr+0x000005a0+4*2))=0x00006488;
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
if(!memcmp((unsigned char *)context_ptr+0x00006078,"\x9c\x8b\x65\xfc\x1d\x28\xb9\x82\x43\x24\x8b\x5a\xbc\x78\x5f\xbf\x27\xba\x7e\x3e\x7c\xc6\x77\xb8\x40\xdb\xd2\xf5\x24\xf8\x2b\xac",32))
printf("strip: 9c8b65fc1d28b982, Pass\n");
else
printf("strip: 9c8b65fc1d28b982, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006498))=0x01ea1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006498+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006498+4*2))=0x0202003e;
*((unsigned int *)((unsigned long)context_ptr+0x00006498+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x0000669c))=0xc42deca4;
*((unsigned int *)((unsigned long)context_ptr+0x0000669c+4*1))=0x548f69ef;
*((unsigned int *)((unsigned long)context_ptr+0x0000669c+4*2))=0x643e55ee;
*((unsigned int *)((unsigned long)context_ptr+0x0000669c+4*3))=0xb6182818;
*((unsigned int *)((unsigned long)context_ptr+0x0000669c+4*4))=0x4cb00955;
*((unsigned int *)((unsigned long)context_ptr+0x0000669c+4*5))=0xee95eacf;
*((unsigned int *)((unsigned long)context_ptr+0x0000669c+4*6))=0x05b664ec;
*((unsigned int *)((unsigned long)context_ptr+0x0000669c+4*7))=0x4c91f7a1;
*((unsigned int *)((unsigned long)context_ptr+0x0000669c+4*8))=0x724b618a;
*((unsigned int *)((unsigned long)context_ptr+0x0000669c+4*9))=0x043d7939;
*((unsigned int *)((unsigned long)context_ptr+0x0000669c+4*10))=0x0a4c6c05;
*((unsigned int *)((unsigned long)context_ptr+0x0000669c+4*11))=0xd24e19d1;
*((unsigned int *)((unsigned long)context_ptr+0x0000669c+4*12))=0x42c46dbc;
*((unsigned int *)((unsigned long)context_ptr+0x0000669c+4*13))=0xcd4fcf6b;
*((unsigned int *)((unsigned long)context_ptr+0x0000669c+4*14))=0x742db46f;
*((unsigned int *)((unsigned long)context_ptr+0x0000669c+4*15))=0x00009022;
*((unsigned int *)((unsigned long)context_ptr+0x000035b8))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x000035b8+4*1))=0x00006078;
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
*((unsigned int *)((unsigned long)context_ptr+0x000005b8+4*1))=0x0000669c;
*((unsigned int *)((unsigned long)context_ptr+0x000005b8+4*2))=0x00006498;
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
if(!memcmp((unsigned char *)context_ptr+0x000063c8,"\x92\xd4\x20\x99\x9e\xde\x75\x84\xbc\x8d\x2b\xc9\xc0\x34\x32\xe7\x56\xc0\x05\xd5\xaa\xac\xf6\x90\x65\x1e\xc7\x8d\x21\x6a\x85\x69",32))
printf("strip: 92d420999ede7584, Pass\n");
else
printf("strip: 92d420999ede7584, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006058))=0x01ea1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*2))=0x0202003f;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x00006394))=0x15aabc08;
*((unsigned int *)((unsigned long)context_ptr+0x00006394+4*1))=0xe8bec521;
*((unsigned int *)((unsigned long)context_ptr+0x00006394+4*2))=0x79f43459;
*((unsigned int *)((unsigned long)context_ptr+0x00006394+4*3))=0x39ce1791;
*((unsigned int *)((unsigned long)context_ptr+0x00006394+4*4))=0x9a2876f3;
*((unsigned int *)((unsigned long)context_ptr+0x00006394+4*5))=0x817c1c3f;
*((unsigned int *)((unsigned long)context_ptr+0x00006394+4*6))=0xd337e6b6;
*((unsigned int *)((unsigned long)context_ptr+0x00006394+4*7))=0x62c02074;
*((unsigned int *)((unsigned long)context_ptr+0x00006394+4*8))=0x943f008f;
*((unsigned int *)((unsigned long)context_ptr+0x00006394+4*9))=0x38862107;
*((unsigned int *)((unsigned long)context_ptr+0x00006394+4*10))=0x5f2ae4b4;
*((unsigned int *)((unsigned long)context_ptr+0x00006394+4*11))=0x24b6f012;
*((unsigned int *)((unsigned long)context_ptr+0x00006394+4*12))=0x284c9d3b;
*((unsigned int *)((unsigned long)context_ptr+0x00006394+4*13))=0x65b346d5;
*((unsigned int *)((unsigned long)context_ptr+0x00006394+4*14))=0x69b4dd3d;
*((unsigned int *)((unsigned long)context_ptr+0x00006394+4*15))=0x00f923a0;
*((unsigned int *)((unsigned long)context_ptr+0x000035d0))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x000035d0+4*1))=0x00006588;
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
*((unsigned int *)((unsigned long)context_ptr+0x000005d0+4*1))=0x00006394;
*((unsigned int *)((unsigned long)context_ptr+0x000005d0+4*2))=0x00006058;
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
if(!memcmp((unsigned char *)context_ptr+0x000064a8,"\x17\xa5\x87\xef\x7a\xc9\x2d\x20\xb1\x4c\xb6\x40\xf1\xdd\x3c\xa9\x13\x06\xab\xab\xbe\xeb\xc2\xd3\xa3\x09\xa9\x76\x24\x51\x1a\xe8",32))
printf("strip: 17a587ef7ac92d20, Pass\n");
else
printf("strip: 17a587ef7ac92d20, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006048))=0x01ea1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006048+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006048+4*2))=0x02020040;
*((unsigned int *)((unsigned long)context_ptr+0x00006048+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x000065a8))=0xfbff9001;
*((unsigned int *)((unsigned long)context_ptr+0x000065a8+4*1))=0xd12fbc3e;
*((unsigned int *)((unsigned long)context_ptr+0x000065a8+4*2))=0xd4afd19d;
*((unsigned int *)((unsigned long)context_ptr+0x000065a8+4*3))=0x1f2f4523;
*((unsigned int *)((unsigned long)context_ptr+0x000065a8+4*4))=0x58731538;
*((unsigned int *)((unsigned long)context_ptr+0x000065a8+4*5))=0x0bb33202;
*((unsigned int *)((unsigned long)context_ptr+0x000065a8+4*6))=0x09eadb04;
*((unsigned int *)((unsigned long)context_ptr+0x000065a8+4*7))=0xa0945b42;
*((unsigned int *)((unsigned long)context_ptr+0x000065a8+4*8))=0x606645f6;
*((unsigned int *)((unsigned long)context_ptr+0x000065a8+4*9))=0xa9e831d6;
*((unsigned int *)((unsigned long)context_ptr+0x000065a8+4*10))=0x0b32b87d;
*((unsigned int *)((unsigned long)context_ptr+0x000065a8+4*11))=0x9fdf5bdd;
*((unsigned int *)((unsigned long)context_ptr+0x000065a8+4*12))=0x624de195;
*((unsigned int *)((unsigned long)context_ptr+0x000065a8+4*13))=0xebc9e8d8;
*((unsigned int *)((unsigned long)context_ptr+0x000065a8+4*14))=0xe2d92c8c;
*((unsigned int *)((unsigned long)context_ptr+0x000065a8+4*15))=0xed04aa4d;
*((unsigned int *)((unsigned long)context_ptr+0x000035e8))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x000035e8+4*1))=0x000064a8;
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
*((unsigned int *)((unsigned long)context_ptr+0x000005e8+4*1))=0x000065a8;
*((unsigned int *)((unsigned long)context_ptr+0x000005e8+4*2))=0x00006048;
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
if(!memcmp((unsigned char *)context_ptr+0x000064c8,"\x0b\xe8\xad\x85\xef\x1e\x1d\x84\xd3\x02\x72\x27\xe8\xf3\x1c\xca\x50\x59\x53\x72\xb5\x03\x46\x39\xad\xd6\xb5\x81\xc1\x70\x96\x0e",32))
printf("strip: 0be8ad85ef1e1d84, Pass\n");
else
printf("strip: 0be8ad85ef1e1d84, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006068))=0x01ea1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006068+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006068+4*2))=0x02020041;
*((unsigned int *)((unsigned long)context_ptr+0x00006068+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x00006098))=0x4e96c258;
*((unsigned int *)((unsigned long)context_ptr+0x00006098+4*1))=0xb388352c;
*((unsigned int *)((unsigned long)context_ptr+0x00006098+4*2))=0xa2b4c7f1;
*((unsigned int *)((unsigned long)context_ptr+0x00006098+4*3))=0x66c89cff;
*((unsigned int *)((unsigned long)context_ptr+0x00006098+4*4))=0x82ca5d23;
*((unsigned int *)((unsigned long)context_ptr+0x00006098+4*5))=0xbf5c357e;
*((unsigned int *)((unsigned long)context_ptr+0x00006098+4*6))=0xeef52c6a;
*((unsigned int *)((unsigned long)context_ptr+0x00006098+4*7))=0x12fc7ddc;
*((unsigned int *)((unsigned long)context_ptr+0x00006098+4*8))=0x8f5808a7;
*((unsigned int *)((unsigned long)context_ptr+0x00006098+4*9))=0xe2ef6f7b;
*((unsigned int *)((unsigned long)context_ptr+0x00006098+4*10))=0xa933c7e3;
*((unsigned int *)((unsigned long)context_ptr+0x00006098+4*11))=0x9858e35e;
*((unsigned int *)((unsigned long)context_ptr+0x00006098+4*12))=0x5b1f54d3;
*((unsigned int *)((unsigned long)context_ptr+0x00006098+4*13))=0xdcfa5945;
*((unsigned int *)((unsigned long)context_ptr+0x00006098+4*14))=0xee81d795;
*((unsigned int *)((unsigned long)context_ptr+0x00006098+4*15))=0x1c90e640;
*((unsigned int *)((unsigned long)context_ptr+0x00006098+4*16))=0x00000079;
*((unsigned int *)((unsigned long)context_ptr+0x00003600))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003600+4*1))=0x000064c8;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000600+4*1))=0x00006098;
*((unsigned int *)((unsigned long)context_ptr+0x00000600+4*2))=0x00006068;
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
if(!memcmp((unsigned char *)context_ptr+0x00006134,"\xbd\xfb\xe3\x54\x51\xe0\x91\xdb\x1f\xa2\x4a\xaa\x51\x3e\x57\x7e\xf1\x1b\x6c\x5c\xc1\x66\x06\xab\x5d\x51\xe7\x60\x74\xd5\xd0\xb9",32))
printf("strip: bdfbe35451e091db, Pass\n");
else
printf("strip: bdfbe35451e091db, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000063d4))=0x01ea1002;
*((unsigned int *)((unsigned long)context_ptr+0x000063d4+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000063d4+4*2))=0x02020042;
*((unsigned int *)((unsigned long)context_ptr+0x000063d4+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x000060dc))=0x833a8bd8;
*((unsigned int *)((unsigned long)context_ptr+0x000060dc+4*1))=0x662e5d05;
*((unsigned int *)((unsigned long)context_ptr+0x000060dc+4*2))=0xceb0ab0f;
*((unsigned int *)((unsigned long)context_ptr+0x000060dc+4*3))=0xfb251f98;
*((unsigned int *)((unsigned long)context_ptr+0x000060dc+4*4))=0x527ca9b2;
*((unsigned int *)((unsigned long)context_ptr+0x000060dc+4*5))=0x583ff0d9;
*((unsigned int *)((unsigned long)context_ptr+0x000060dc+4*6))=0xbe93fc51;
*((unsigned int *)((unsigned long)context_ptr+0x000060dc+4*7))=0xd0be5355;
*((unsigned int *)((unsigned long)context_ptr+0x000060dc+4*8))=0x4da6e024;
*((unsigned int *)((unsigned long)context_ptr+0x000060dc+4*9))=0x7085f232;
*((unsigned int *)((unsigned long)context_ptr+0x000060dc+4*10))=0xe902a94e;
*((unsigned int *)((unsigned long)context_ptr+0x000060dc+4*11))=0x990f009d;
*((unsigned int *)((unsigned long)context_ptr+0x000060dc+4*12))=0xc9df543d;
*((unsigned int *)((unsigned long)context_ptr+0x000060dc+4*13))=0x4794e083;
*((unsigned int *)((unsigned long)context_ptr+0x000060dc+4*14))=0xe5110ff9;
*((unsigned int *)((unsigned long)context_ptr+0x000060dc+4*15))=0xbbcbe08d;
*((unsigned int *)((unsigned long)context_ptr+0x000060dc+4*16))=0x000058f4;
*((unsigned int *)((unsigned long)context_ptr+0x00003618))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003618+4*1))=0x000063e4;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000618+4*1))=0x000060dc;
*((unsigned int *)((unsigned long)context_ptr+0x00000618+4*2))=0x000063d4;
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
if(!memcmp((unsigned char *)context_ptr+0x000064e8,"\x66\x7b\x46\xc5\x95\x23\xb2\xb8\x5a\x87\xb7\xc6\xf3\x03\xdd\x75\x98\x0f\xe9\xaf\x9e\xb6\xc2\xb3\xf8\xd4\xa1\x17\xae\xd5\x7a\x5b",32))
printf("strip: 667b46c59523b2b8, Pass\n");
else
printf("strip: 667b46c59523b2b8, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006404))=0x01ea1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006404+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006404+4*2))=0x02020043;
*((unsigned int *)((unsigned long)context_ptr+0x00006404+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x00006120))=0xf5859c63;
*((unsigned int *)((unsigned long)context_ptr+0x00006120+4*1))=0x4b044d78;
*((unsigned int *)((unsigned long)context_ptr+0x00006120+4*2))=0x7b92fed5;
*((unsigned int *)((unsigned long)context_ptr+0x00006120+4*3))=0xcf595462;
*((unsigned int *)((unsigned long)context_ptr+0x00006120+4*4))=0xe1249358;
*((unsigned int *)((unsigned long)context_ptr+0x00006120+4*5))=0x2a40754e;
*((unsigned int *)((unsigned long)context_ptr+0x00006120+4*6))=0x0aedb4f0;
*((unsigned int *)((unsigned long)context_ptr+0x00006120+4*7))=0xb7f6998d;
*((unsigned int *)((unsigned long)context_ptr+0x00006120+4*8))=0x97e544a2;
*((unsigned int *)((unsigned long)context_ptr+0x00006120+4*9))=0x19dca300;
*((unsigned int *)((unsigned long)context_ptr+0x00006120+4*10))=0x630a8b31;
*((unsigned int *)((unsigned long)context_ptr+0x00006120+4*11))=0x19d93e93;
*((unsigned int *)((unsigned long)context_ptr+0x00006120+4*12))=0xa7d535cd;
*((unsigned int *)((unsigned long)context_ptr+0x00006120+4*13))=0x29d285be;
*((unsigned int *)((unsigned long)context_ptr+0x00006120+4*14))=0x154004c0;
*((unsigned int *)((unsigned long)context_ptr+0x00006120+4*15))=0x0ae14673;
*((unsigned int *)((unsigned long)context_ptr+0x00006120+4*16))=0x009ee0c3;
*((unsigned int *)((unsigned long)context_ptr+0x00003630))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003630+4*1))=0x000064e8;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000630+4*1))=0x00006120;
*((unsigned int *)((unsigned long)context_ptr+0x00000630+4*2))=0x00006404;
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
if(!memcmp((unsigned char *)context_ptr+0x000061c0,"\x59\x0a\xef\x29\x4d\xb2\x9a\x8c\xf1\xde\x07\xc7\x12\x7a\x06\x38\x57\xbd\x80\x9b\x1a\x4c\x69\x8b\x27\xfa\x8c\x28\x17\x54\x1a\xb7",32))
printf("strip: 590aef294db29a8c, Pass\n");
else
printf("strip: 590aef294db29a8c, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006414))=0x01ea1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006414+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006414+4*2))=0x02020044;
*((unsigned int *)((unsigned long)context_ptr+0x00006414+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x00006164))=0xbbc8ceb4;
*((unsigned int *)((unsigned long)context_ptr+0x00006164+4*1))=0x667602b1;
*((unsigned int *)((unsigned long)context_ptr+0x00006164+4*2))=0xba70c4c8;
*((unsigned int *)((unsigned long)context_ptr+0x00006164+4*3))=0x7612dc2c;
*((unsigned int *)((unsigned long)context_ptr+0x00006164+4*4))=0x1e62d653;
*((unsigned int *)((unsigned long)context_ptr+0x00006164+4*5))=0xbae92eaf;
*((unsigned int *)((unsigned long)context_ptr+0x00006164+4*6))=0x69f44fbd;
*((unsigned int *)((unsigned long)context_ptr+0x00006164+4*7))=0xefd3a744;
*((unsigned int *)((unsigned long)context_ptr+0x00006164+4*8))=0xed16bd6a;
*((unsigned int *)((unsigned long)context_ptr+0x00006164+4*9))=0x634b8a02;
*((unsigned int *)((unsigned long)context_ptr+0x00006164+4*10))=0x7ace7e71;
*((unsigned int *)((unsigned long)context_ptr+0x00006164+4*11))=0xd25c0681;
*((unsigned int *)((unsigned long)context_ptr+0x00006164+4*12))=0x476ee04e;
*((unsigned int *)((unsigned long)context_ptr+0x00006164+4*13))=0x349c3d20;
*((unsigned int *)((unsigned long)context_ptr+0x00006164+4*14))=0xf47eddf9;
*((unsigned int *)((unsigned long)context_ptr+0x00006164+4*15))=0x0b78a80e;
*((unsigned int *)((unsigned long)context_ptr+0x00006164+4*16))=0x3aaf9eb2;
*((unsigned int *)((unsigned long)context_ptr+0x00003648))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003648+4*1))=0x000061a8;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000648+4*1))=0x00006164;
*((unsigned int *)((unsigned long)context_ptr+0x00000648+4*2))=0x00006414;
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
if(!memcmp((unsigned char *)context_ptr+0x00006508,"\xc2\x69\x95\x73\xb0\xfd\xf7\xc6\x94\x72\xf7\xde\xf0\xef\x20\x14\x2f\x36\xd0\x40\x2f\x28\x4f\x17\xde\x4e\x71\xd2\x67\xf9\x52\x27",32))
printf("strip: c2699573b0fdf7c6, Pass\n");
else
printf("strip: c2699573b0fdf7c6, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006424))=0x01ea1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006424+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006424+4*2))=0x02020045;
*((unsigned int *)((unsigned long)context_ptr+0x00006424+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x000066dc))=0x538b0007;
*((unsigned int *)((unsigned long)context_ptr+0x000066dc+4*1))=0x12780b10;
*((unsigned int *)((unsigned long)context_ptr+0x000066dc+4*2))=0x074fbe33;
*((unsigned int *)((unsigned long)context_ptr+0x000066dc+4*3))=0xc2a3eef5;
*((unsigned int *)((unsigned long)context_ptr+0x000066dc+4*4))=0xf9a058ed;
*((unsigned int *)((unsigned long)context_ptr+0x000066dc+4*5))=0xea73dc0f;
*((unsigned int *)((unsigned long)context_ptr+0x000066dc+4*6))=0xee840b60;
*((unsigned int *)((unsigned long)context_ptr+0x000066dc+4*7))=0x8dad3d8d;
*((unsigned int *)((unsigned long)context_ptr+0x000066dc+4*8))=0x02383d8d;
*((unsigned int *)((unsigned long)context_ptr+0x000066dc+4*9))=0x73e6c0f8;
*((unsigned int *)((unsigned long)context_ptr+0x000066dc+4*10))=0xdff9793c;
*((unsigned int *)((unsigned long)context_ptr+0x000066dc+4*11))=0x926eadba;
*((unsigned int *)((unsigned long)context_ptr+0x000066dc+4*12))=0xbb113dc2;
*((unsigned int *)((unsigned long)context_ptr+0x000066dc+4*13))=0xb549a97b;
*((unsigned int *)((unsigned long)context_ptr+0x000066dc+4*14))=0xd0019add;
*((unsigned int *)((unsigned long)context_ptr+0x000066dc+4*15))=0x65167739;
*((unsigned int *)((unsigned long)context_ptr+0x000066dc+4*16))=0x73b67fe4;
*((unsigned int *)((unsigned long)context_ptr+0x000066dc+4*17))=0x0000007e;
*((unsigned int *)((unsigned long)context_ptr+0x00003660))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003660+4*1))=0x00006508;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000660+4*1))=0x000066dc;
*((unsigned int *)((unsigned long)context_ptr+0x00000660+4*2))=0x00006424;
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
if(!memcmp((unsigned char *)context_ptr+0x00006218,"\x04\x63\x86\x6f\x8d\x8b\x0c\xf7\x4b\xaa\x2d\xc6\xec\x39\xca\xf6\xed\xb3\xaa\x45\x77\x56\xbc\x09\x69\x78\x39\xe9\xc6\x8f\xd3\xf5",32))
printf("strip: 0463866f8d8b0cf7, Pass\n");
else
printf("strip: 0463866f8d8b0cf7, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006434))=0x01ea1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006434+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006434+4*2))=0x02020046;
*((unsigned int *)((unsigned long)context_ptr+0x00006434+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x000061c8))=0x1698467f;
*((unsigned int *)((unsigned long)context_ptr+0x000061c8+4*1))=0x1bd94104;
*((unsigned int *)((unsigned long)context_ptr+0x000061c8+4*2))=0x3a93bf88;
*((unsigned int *)((unsigned long)context_ptr+0x000061c8+4*3))=0x5a1e697d;
*((unsigned int *)((unsigned long)context_ptr+0x000061c8+4*4))=0xd9270cfd;
*((unsigned int *)((unsigned long)context_ptr+0x000061c8+4*5))=0xddd81bda;
*((unsigned int *)((unsigned long)context_ptr+0x000061c8+4*6))=0x067e2c7c;
*((unsigned int *)((unsigned long)context_ptr+0x000061c8+4*7))=0x965431c5;
*((unsigned int *)((unsigned long)context_ptr+0x000061c8+4*8))=0x97623da7;
*((unsigned int *)((unsigned long)context_ptr+0x000061c8+4*9))=0xa685db44;
*((unsigned int *)((unsigned long)context_ptr+0x000061c8+4*10))=0x43d414da;
*((unsigned int *)((unsigned long)context_ptr+0x000061c8+4*11))=0xc06eae35;
*((unsigned int *)((unsigned long)context_ptr+0x000061c8+4*12))=0xbd7aa017;
*((unsigned int *)((unsigned long)context_ptr+0x000061c8+4*13))=0xfea61206;
*((unsigned int *)((unsigned long)context_ptr+0x000061c8+4*14))=0xd00d401c;
*((unsigned int *)((unsigned long)context_ptr+0x000061c8+4*15))=0x8860b71b;
*((unsigned int *)((unsigned long)context_ptr+0x000061c8+4*16))=0x11d9355f;
*((unsigned int *)((unsigned long)context_ptr+0x000061c8+4*17))=0x0000c860;
*((unsigned int *)((unsigned long)context_ptr+0x00003678))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003678+4*1))=0x00006210;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000678+4*1))=0x000061c8;
*((unsigned int *)((unsigned long)context_ptr+0x00000678+4*2))=0x00006434;
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
if(!memcmp((unsigned char *)context_ptr+0x00006528,"\x1f\x1e\x12\xc9\x9a\x25\x96\xb2\xf7\xe4\x8a\xd2\x28\x8f\xd8\xfe\xb2\xcd\x60\xde\x3e\x36\xc1\x1e\x3d\x94\xef\xe1\x67\x05\x38\xb0",32))
printf("strip: 1f1e12c99a2596b2, Pass\n");
else
printf("strip: 1f1e12c99a2596b2, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006444))=0x01ea1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006444+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006444+4*2))=0x02020047;
*((unsigned int *)((unsigned long)context_ptr+0x00006444+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x00006724))=0x6f9caa59;
*((unsigned int *)((unsigned long)context_ptr+0x00006724+4*1))=0xd2ef7b61;
*((unsigned int *)((unsigned long)context_ptr+0x00006724+4*2))=0xfa66cd01;
*((unsigned int *)((unsigned long)context_ptr+0x00006724+4*3))=0x447dd921;
*((unsigned int *)((unsigned long)context_ptr+0x00006724+4*4))=0x6ac98fec;
*((unsigned int *)((unsigned long)context_ptr+0x00006724+4*5))=0x2d6ae053;
*((unsigned int *)((unsigned long)context_ptr+0x00006724+4*6))=0xace9bea7;
*((unsigned int *)((unsigned long)context_ptr+0x00006724+4*7))=0xd1963151;
*((unsigned int *)((unsigned long)context_ptr+0x00006724+4*8))=0x8fdac51b;
*((unsigned int *)((unsigned long)context_ptr+0x00006724+4*9))=0x4cbefca0;
*((unsigned int *)((unsigned long)context_ptr+0x00006724+4*10))=0xeb5c96cc;
*((unsigned int *)((unsigned long)context_ptr+0x00006724+4*11))=0xe9f89756;
*((unsigned int *)((unsigned long)context_ptr+0x00006724+4*12))=0xac3f59f3;
*((unsigned int *)((unsigned long)context_ptr+0x00006724+4*13))=0xd553e233;
*((unsigned int *)((unsigned long)context_ptr+0x00006724+4*14))=0x405ff1ef;
*((unsigned int *)((unsigned long)context_ptr+0x00006724+4*15))=0x46fd06a1;
*((unsigned int *)((unsigned long)context_ptr+0x00006724+4*16))=0xd7ed4670;
*((unsigned int *)((unsigned long)context_ptr+0x00006724+4*17))=0x00f19889;
*((unsigned int *)((unsigned long)context_ptr+0x00003690))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003690+4*1))=0x00006528;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000690+4*1))=0x00006724;
*((unsigned int *)((unsigned long)context_ptr+0x00000690+4*2))=0x00006444;
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
if(!memcmp((unsigned char *)context_ptr+0x000062ac,"\x2b\x11\x10\x03\x75\x6d\xe1\x9b\x72\xf4\x6d\x0e\x8b\xbf\xc0\x56\x33\xa8\x8e\x2a\xba\x43\xf1\x22\x61\xa3\xf7\xb5\x5a\x6b\x6d\x12",32))
printf("strip: 2b111003756de19b, Pass\n");
else
printf("strip: 2b111003756de19b, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006454))=0x01ea1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006454+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006454+4*2))=0x02020048;
*((unsigned int *)((unsigned long)context_ptr+0x00006454+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x00006230))=0x7f25c75a;
*((unsigned int *)((unsigned long)context_ptr+0x00006230+4*1))=0xaf532f7e;
*((unsigned int *)((unsigned long)context_ptr+0x00006230+4*2))=0x7013d127;
*((unsigned int *)((unsigned long)context_ptr+0x00006230+4*3))=0x72be6c88;
*((unsigned int *)((unsigned long)context_ptr+0x00006230+4*4))=0x471bae89;
*((unsigned int *)((unsigned long)context_ptr+0x00006230+4*5))=0x307fed94;
*((unsigned int *)((unsigned long)context_ptr+0x00006230+4*6))=0x971f072f;
*((unsigned int *)((unsigned long)context_ptr+0x00006230+4*7))=0x4c54281d;
*((unsigned int *)((unsigned long)context_ptr+0x00006230+4*8))=0x578b1ce4;
*((unsigned int *)((unsigned long)context_ptr+0x00006230+4*9))=0x5625e2a0;
*((unsigned int *)((unsigned long)context_ptr+0x00006230+4*10))=0x01493fc5;
*((unsigned int *)((unsigned long)context_ptr+0x00006230+4*11))=0xa39fc740;
*((unsigned int *)((unsigned long)context_ptr+0x00006230+4*12))=0x06f4b435;
*((unsigned int *)((unsigned long)context_ptr+0x00006230+4*13))=0xc9826773;
*((unsigned int *)((unsigned long)context_ptr+0x00006230+4*14))=0xadabf9ba;
*((unsigned int *)((unsigned long)context_ptr+0x00006230+4*15))=0x326d457b;
*((unsigned int *)((unsigned long)context_ptr+0x00006230+4*16))=0x155914b8;
*((unsigned int *)((unsigned long)context_ptr+0x00006230+4*17))=0x576adcb1;
*((unsigned int *)((unsigned long)context_ptr+0x000036a8))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x000036a8+4*1))=0x000065e8;
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
*((unsigned int *)((unsigned long)context_ptr+0x000006a8+4*1))=0x00006230;
*((unsigned int *)((unsigned long)context_ptr+0x000006a8+4*2))=0x00006454;
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
if(!memcmp((unsigned char *)context_ptr+0x00006620,"\xd3\x5e\xfd\xda\xa1\xa9\x18\xed\x44\x9d\x44\x76\xd6\x90\x65\x69\x5d\xb4\x76\xc0\x61\x4a\x14\x9d\xc0\xc2\x03\xeb\x17\xff\xb2\x3b",32))
printf("strip: d35efddaa1a918ed, Pass\n");
else
printf("strip: d35efddaa1a918ed, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006548))=0x01ea1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006548+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006548+4*2))=0x02020049;
*((unsigned int *)((unsigned long)context_ptr+0x00006548+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x00006278))=0xee240e5f;
*((unsigned int *)((unsigned long)context_ptr+0x00006278+4*1))=0x0fcc1974;
*((unsigned int *)((unsigned long)context_ptr+0x00006278+4*2))=0x2cea613a;
*((unsigned int *)((unsigned long)context_ptr+0x00006278+4*3))=0xf05d82c3;
*((unsigned int *)((unsigned long)context_ptr+0x00006278+4*4))=0x7da91207;
*((unsigned int *)((unsigned long)context_ptr+0x00006278+4*5))=0x198b19bd;
*((unsigned int *)((unsigned long)context_ptr+0x00006278+4*6))=0x29a65c7b;
*((unsigned int *)((unsigned long)context_ptr+0x00006278+4*7))=0x7f34e986;
*((unsigned int *)((unsigned long)context_ptr+0x00006278+4*8))=0x770fe56d;
*((unsigned int *)((unsigned long)context_ptr+0x00006278+4*9))=0x127cfcfe;
*((unsigned int *)((unsigned long)context_ptr+0x00006278+4*10))=0xdf1be762;
*((unsigned int *)((unsigned long)context_ptr+0x00006278+4*11))=0x1f4d4cc3;
*((unsigned int *)((unsigned long)context_ptr+0x00006278+4*12))=0x61be6cb8;
*((unsigned int *)((unsigned long)context_ptr+0x00006278+4*13))=0x0413fd23;
*((unsigned int *)((unsigned long)context_ptr+0x00006278+4*14))=0x25153ab0;
*((unsigned int *)((unsigned long)context_ptr+0x00006278+4*15))=0x480d81ab;
*((unsigned int *)((unsigned long)context_ptr+0x00006278+4*16))=0xde9812c4;
*((unsigned int *)((unsigned long)context_ptr+0x00006278+4*17))=0xd08c8611;
*((unsigned int *)((unsigned long)context_ptr+0x00006278+4*18))=0x0000009d;
*((unsigned int *)((unsigned long)context_ptr+0x000036c0))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x000036c0+4*1))=0x00006608;
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
*((unsigned int *)((unsigned long)context_ptr+0x000006c0+4*1))=0x00006278;
*((unsigned int *)((unsigned long)context_ptr+0x000006c0+4*2))=0x00006548;
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
if(!memcmp((unsigned char *)context_ptr+0x00006640,"\xce\x9e\x0d\xcd\x0b\x0b\x78\x32\xce\x68\xf1\xe6\xad\x4d\xd1\xad\xf0\xf8\x06\x48\x29\xe9\x6c\x7c\x9b\x47\x0f\x98\x15\x4b\xcd\xe6",32))
printf("strip: ce9e0dcd0b0b7832, Pass\n");
else
printf("strip: ce9e0dcd0b0b7832, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006558))=0x01ea1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006558+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006558+4*2))=0x0202004a;
*((unsigned int *)((unsigned long)context_ptr+0x00006558+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x000062c4))=0xbeb3bdfc;
*((unsigned int *)((unsigned long)context_ptr+0x000062c4+4*1))=0xbb21d69f;
*((unsigned int *)((unsigned long)context_ptr+0x000062c4+4*2))=0xbfdb8e60;
*((unsigned int *)((unsigned long)context_ptr+0x000062c4+4*3))=0x066cf5a7;
*((unsigned int *)((unsigned long)context_ptr+0x000062c4+4*4))=0xd49b68f6;
*((unsigned int *)((unsigned long)context_ptr+0x000062c4+4*5))=0xbb3236c8;
*((unsigned int *)((unsigned long)context_ptr+0x000062c4+4*6))=0xadbba069;
*((unsigned int *)((unsigned long)context_ptr+0x000062c4+4*7))=0xf4a154bc;
*((unsigned int *)((unsigned long)context_ptr+0x000062c4+4*8))=0x475ffa00;
*((unsigned int *)((unsigned long)context_ptr+0x000062c4+4*9))=0xb3383baf;
*((unsigned int *)((unsigned long)context_ptr+0x000062c4+4*10))=0x04e2a696;
*((unsigned int *)((unsigned long)context_ptr+0x000062c4+4*11))=0x67d64a65;
*((unsigned int *)((unsigned long)context_ptr+0x000062c4+4*12))=0x1f959a5c;
*((unsigned int *)((unsigned long)context_ptr+0x000062c4+4*13))=0x55c2efc9;
*((unsigned int *)((unsigned long)context_ptr+0x000062c4+4*14))=0xdf2d1855;
*((unsigned int *)((unsigned long)context_ptr+0x000062c4+4*15))=0xac2a7230;
*((unsigned int *)((unsigned long)context_ptr+0x000062c4+4*16))=0x4e0ecc2f;
*((unsigned int *)((unsigned long)context_ptr+0x000062c4+4*17))=0x9d538929;
*((unsigned int *)((unsigned long)context_ptr+0x000062c4+4*18))=0x00005392;
*((unsigned int *)((unsigned long)context_ptr+0x000036d8))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x000036d8+4*1))=0x00006310;
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
*((unsigned int *)((unsigned long)context_ptr+0x000006d8+4*1))=0x000062c4;
*((unsigned int *)((unsigned long)context_ptr+0x000006d8+4*2))=0x00006558;
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
if(!memcmp((unsigned char *)context_ptr+0x00006468,"\x2a\xd6\xb4\x03\xbc\x12\xa5\xec\x2a\xb1\x01\xcb\x23\x6f\xa5\x7f\x00\x45\x95\x36\x3b\xfa\x20\x55\x1a\xc3\x31\x32\x96\xca\x4c\x76",32))
printf("strip: 2ad6b403bc12a5ec, Pass\n");
else
printf("strip: 2ad6b403bc12a5ec, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006330))=0x01ea1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006330+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006330+4*2))=0x0202004b;
*((unsigned int *)((unsigned long)context_ptr+0x00006330+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x00006628))=0xba9fef49;
*((unsigned int *)((unsigned long)context_ptr+0x00006628+4*1))=0x26edceee;
*((unsigned int *)((unsigned long)context_ptr+0x00006628+4*2))=0xc4d8df42;
*((unsigned int *)((unsigned long)context_ptr+0x00006628+4*3))=0x1979dab8;
*((unsigned int *)((unsigned long)context_ptr+0x00006628+4*4))=0x8f9b3fba;
*((unsigned int *)((unsigned long)context_ptr+0x00006628+4*5))=0x1862a763;
*((unsigned int *)((unsigned long)context_ptr+0x00006628+4*6))=0x8f48d8dc;
*((unsigned int *)((unsigned long)context_ptr+0x00006628+4*7))=0x6274bc22;
*((unsigned int *)((unsigned long)context_ptr+0x00006628+4*8))=0xced7d3ee;
*((unsigned int *)((unsigned long)context_ptr+0x00006628+4*9))=0xeb51e7ba;
*((unsigned int *)((unsigned long)context_ptr+0x00006628+4*10))=0x7858c06a;
*((unsigned int *)((unsigned long)context_ptr+0x00006628+4*11))=0x0d521d3f;
*((unsigned int *)((unsigned long)context_ptr+0x00006628+4*12))=0x93135350;
*((unsigned int *)((unsigned long)context_ptr+0x00006628+4*13))=0x3f1a9cd7;
*((unsigned int *)((unsigned long)context_ptr+0x00006628+4*14))=0x6bba4f4b;
*((unsigned int *)((unsigned long)context_ptr+0x00006628+4*15))=0xfd39b210;
*((unsigned int *)((unsigned long)context_ptr+0x00006628+4*16))=0x4482d105;
*((unsigned int *)((unsigned long)context_ptr+0x00006628+4*17))=0x10493427;
*((unsigned int *)((unsigned long)context_ptr+0x00006628+4*18))=0x001138dd;
*((unsigned int *)((unsigned long)context_ptr+0x000036f0))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x000036f0+4*1))=0x00006464;
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
*((unsigned int *)((unsigned long)context_ptr+0x000006f0+4*1))=0x00006628;
*((unsigned int *)((unsigned long)context_ptr+0x000006f0+4*2))=0x00006330;
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
if(!memcmp((unsigned char *)context_ptr+0x00006568,"\x86\xf9\x58\x7e\x0a\xf1\x74\x6a\x29\xb4\x0c\x3b\x94\x34\x74\xcb\x47\xb3\xde\xd0\x0c\xe2\xff\x06\x56\xe3\x31\x8a\xd9\x4c\x7b\xaf",32))
printf("strip: 86f9587e0af1746a, Pass\n");
else
printf("strip: 86f9587e0af1746a, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006484))=0x01ea1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006484+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006484+4*2))=0x0202004c;
*((unsigned int *)((unsigned long)context_ptr+0x00006484+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x00006340))=0xc8d51969;
*((unsigned int *)((unsigned long)context_ptr+0x00006340+4*1))=0xd57ecda8;
*((unsigned int *)((unsigned long)context_ptr+0x00006340+4*2))=0x8e8c112c;
*((unsigned int *)((unsigned long)context_ptr+0x00006340+4*3))=0x1e643a94;
*((unsigned int *)((unsigned long)context_ptr+0x00006340+4*4))=0xf7a6d8d0;
*((unsigned int *)((unsigned long)context_ptr+0x00006340+4*5))=0xe5ceefa0;
*((unsigned int *)((unsigned long)context_ptr+0x00006340+4*6))=0xa325185f;
*((unsigned int *)((unsigned long)context_ptr+0x00006340+4*7))=0xadca71ca;
*((unsigned int *)((unsigned long)context_ptr+0x00006340+4*8))=0x44333034;
*((unsigned int *)((unsigned long)context_ptr+0x00006340+4*9))=0x923c8b40;
*((unsigned int *)((unsigned long)context_ptr+0x00006340+4*10))=0xc3a9cc9f;
*((unsigned int *)((unsigned long)context_ptr+0x00006340+4*11))=0xa054077c;
*((unsigned int *)((unsigned long)context_ptr+0x00006340+4*12))=0x082eeb7b;
*((unsigned int *)((unsigned long)context_ptr+0x00006340+4*13))=0x8ad83870;
*((unsigned int *)((unsigned long)context_ptr+0x00006340+4*14))=0x673ba5b7;
*((unsigned int *)((unsigned long)context_ptr+0x00006340+4*15))=0xceee3dd8;
*((unsigned int *)((unsigned long)context_ptr+0x00006340+4*16))=0xb7828a82;
*((unsigned int *)((unsigned long)context_ptr+0x00006340+4*17))=0xe486d0a3;
*((unsigned int *)((unsigned long)context_ptr+0x00006340+4*18))=0xcae1ca15;
*((unsigned int *)((unsigned long)context_ptr+0x00003708))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003708+4*1))=0x00006568;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000708+4*1))=0x00006340;
*((unsigned int *)((unsigned long)context_ptr+0x00000708+4*2))=0x00006484;
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
if(!memcmp((unsigned char *)context_ptr+0x00006078,"\x53\xad\xe2\xb1\xe9\x93\x62\xbd\xc1\x3e\x14\x9f\xc1\xe0\x93\x80\xa8\x51\xae\xa5\x60\xf1\xfc\x5f\x4b\x79\xe7\xfc\x53\xdb\x10\x9c",32))
printf("strip: 53ade2b1e99362bd, Pass\n");
else
printf("strip: 53ade2b1e99362bd, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006494))=0x01ea1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006494+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006494+4*2))=0x0202004d;
*((unsigned int *)((unsigned long)context_ptr+0x00006494+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x00006674))=0x8e341b4c;
*((unsigned int *)((unsigned long)context_ptr+0x00006674+4*1))=0x8420f867;
*((unsigned int *)((unsigned long)context_ptr+0x00006674+4*2))=0xd3e449ce;
*((unsigned int *)((unsigned long)context_ptr+0x00006674+4*3))=0xc86dc26b;
*((unsigned int *)((unsigned long)context_ptr+0x00006674+4*4))=0x49689056;
*((unsigned int *)((unsigned long)context_ptr+0x00006674+4*5))=0x3cb76a74;
*((unsigned int *)((unsigned long)context_ptr+0x00006674+4*6))=0x65c0bff2;
*((unsigned int *)((unsigned long)context_ptr+0x00006674+4*7))=0x79e490e5;
*((unsigned int *)((unsigned long)context_ptr+0x00006674+4*8))=0x393544f6;
*((unsigned int *)((unsigned long)context_ptr+0x00006674+4*9))=0x9d0bc75c;
*((unsigned int *)((unsigned long)context_ptr+0x00006674+4*10))=0x654b7d4f;
*((unsigned int *)((unsigned long)context_ptr+0x00006674+4*11))=0x58bd1f6b;
*((unsigned int *)((unsigned long)context_ptr+0x00006674+4*12))=0xb937d118;
*((unsigned int *)((unsigned long)context_ptr+0x00006674+4*13))=0xf8f20998;
*((unsigned int *)((unsigned long)context_ptr+0x00006674+4*14))=0x31b217bb;
*((unsigned int *)((unsigned long)context_ptr+0x00006674+4*15))=0xd3417e76;
*((unsigned int *)((unsigned long)context_ptr+0x00006674+4*16))=0xc09a7a1f;
*((unsigned int *)((unsigned long)context_ptr+0x00006674+4*17))=0x10f892dc;
*((unsigned int *)((unsigned long)context_ptr+0x00006674+4*18))=0x6938ce56;
*((unsigned int *)((unsigned long)context_ptr+0x00006674+4*19))=0x0000006f;
*((unsigned int *)((unsigned long)context_ptr+0x00003720))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003720+4*1))=0x00006078;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000720+4*1))=0x00006674;
*((unsigned int *)((unsigned long)context_ptr+0x00000720+4*2))=0x00006494;
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
if(!memcmp((unsigned char *)context_ptr+0x00006588,"\xd5\x71\x8b\x97\x9a\x49\x5c\x9d\x5e\xe9\xd3\x36\x63\x7b\xea\x44\xc4\x05\xf5\x20\x43\x33\x99\xd4\x11\xac\xad\xe6\x42\x94\xf6\xae",32))
printf("strip: d5718b979a495c9d, Pass\n");
else
printf("strip: d5718b979a495c9d, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006058))=0x01ea1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*2))=0x0202004e;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x0000676c))=0x49803261;
*((unsigned int *)((unsigned long)context_ptr+0x0000676c+4*1))=0x9dc99b88;
*((unsigned int *)((unsigned long)context_ptr+0x0000676c+4*2))=0xe7e7ae67;
*((unsigned int *)((unsigned long)context_ptr+0x0000676c+4*3))=0x949c1ea6;
*((unsigned int *)((unsigned long)context_ptr+0x0000676c+4*4))=0xcf1990cc;
*((unsigned int *)((unsigned long)context_ptr+0x0000676c+4*5))=0x695a9475;
*((unsigned int *)((unsigned long)context_ptr+0x0000676c+4*6))=0xd288810b;
*((unsigned int *)((unsigned long)context_ptr+0x0000676c+4*7))=0xdcf9315c;
*((unsigned int *)((unsigned long)context_ptr+0x0000676c+4*8))=0x1e26f545;
*((unsigned int *)((unsigned long)context_ptr+0x0000676c+4*9))=0xf70207d0;
*((unsigned int *)((unsigned long)context_ptr+0x0000676c+4*10))=0x9245bc14;
*((unsigned int *)((unsigned long)context_ptr+0x0000676c+4*11))=0x9d1a247a;
*((unsigned int *)((unsigned long)context_ptr+0x0000676c+4*12))=0xcd2f8d36;
*((unsigned int *)((unsigned long)context_ptr+0x0000676c+4*13))=0x254ae392;
*((unsigned int *)((unsigned long)context_ptr+0x0000676c+4*14))=0x36309df5;
*((unsigned int *)((unsigned long)context_ptr+0x0000676c+4*15))=0x4cc4b22c;
*((unsigned int *)((unsigned long)context_ptr+0x0000676c+4*16))=0xaee12738;
*((unsigned int *)((unsigned long)context_ptr+0x0000676c+4*17))=0x1c17d706;
*((unsigned int *)((unsigned long)context_ptr+0x0000676c+4*18))=0x6a0b8fb4;
*((unsigned int *)((unsigned long)context_ptr+0x0000676c+4*19))=0x0000183d;
*((unsigned int *)((unsigned long)context_ptr+0x00003738))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003738+4*1))=0x00006588;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000738+4*1))=0x0000676c;
*((unsigned int *)((unsigned long)context_ptr+0x00000738+4*2))=0x00006058;
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
if(!memcmp((unsigned char *)context_ptr+0x000064a8,"\x57\x9c\xe2\xf2\xa0\xed\x36\x53\x6b\x85\xfa\x23\x1c\x95\xf4\x50\x1a\xdc\xe7\xde\x70\x35\xdb\x62\x0f\x4c\x5a\x99\x69\x34\x95\xd9",32))
printf("strip: 579ce2f2a0ed3653, Pass\n");
else
printf("strip: 579ce2f2a0ed3653, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006048))=0x01ea1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006048+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006048+4*2))=0x0202004f;
*((unsigned int *)((unsigned long)context_ptr+0x00006048+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x000067bc))=0x06951e8c;
*((unsigned int *)((unsigned long)context_ptr+0x000067bc+4*1))=0xc22ef39b;
*((unsigned int *)((unsigned long)context_ptr+0x000067bc+4*2))=0x98d7abca;
*((unsigned int *)((unsigned long)context_ptr+0x000067bc+4*3))=0xb6ea52b7;
*((unsigned int *)((unsigned long)context_ptr+0x000067bc+4*4))=0x9aae57a8;
*((unsigned int *)((unsigned long)context_ptr+0x000067bc+4*5))=0x6fe08e70;
*((unsigned int *)((unsigned long)context_ptr+0x000067bc+4*6))=0xd818a955;
*((unsigned int *)((unsigned long)context_ptr+0x000067bc+4*7))=0xc5deb5e5;
*((unsigned int *)((unsigned long)context_ptr+0x000067bc+4*8))=0xba8ca432;
*((unsigned int *)((unsigned long)context_ptr+0x000067bc+4*9))=0x2c5ac573;
*((unsigned int *)((unsigned long)context_ptr+0x000067bc+4*10))=0xdcc23b09;
*((unsigned int *)((unsigned long)context_ptr+0x000067bc+4*11))=0x74da56b6;
*((unsigned int *)((unsigned long)context_ptr+0x000067bc+4*12))=0x3117c5f6;
*((unsigned int *)((unsigned long)context_ptr+0x000067bc+4*13))=0x64122cf6;
*((unsigned int *)((unsigned long)context_ptr+0x000067bc+4*14))=0xca1580ba;
*((unsigned int *)((unsigned long)context_ptr+0x000067bc+4*15))=0x032995ab;
*((unsigned int *)((unsigned long)context_ptr+0x000067bc+4*16))=0x922f2fd7;
*((unsigned int *)((unsigned long)context_ptr+0x000067bc+4*17))=0xe82d0a9b;
*((unsigned int *)((unsigned long)context_ptr+0x000067bc+4*18))=0xc3b0de69;
*((unsigned int *)((unsigned long)context_ptr+0x000067bc+4*19))=0x0091a42d;
*((unsigned int *)((unsigned long)context_ptr+0x00003750))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003750+4*1))=0x000064a4;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000750+4*1))=0x000067bc;
*((unsigned int *)((unsigned long)context_ptr+0x00000750+4*2))=0x00006048;
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
if(!memcmp((unsigned char *)context_ptr+0x000064c8,"\x60\x38\xa1\x59\x91\xeb\x3f\x00\xfb\x0f\x10\x5b\xad\x9e\xdf\xf0\xe5\xec\xc9\xac\xba\xb5\x0e\x90\xb6\x87\xae\xeb\xdb\xc7\xc0\x8c",32))
printf("strip: 6038a15991eb3f00, Pass\n");
else
printf("strip: 6038a15991eb3f00, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006068))=0x01ea1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006068+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006068+4*2))=0x02020050;
*((unsigned int *)((unsigned long)context_ptr+0x00006068+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x0000680c))=0x4dd7ca13;
*((unsigned int *)((unsigned long)context_ptr+0x0000680c+4*1))=0xbad7a28c;
*((unsigned int *)((unsigned long)context_ptr+0x0000680c+4*2))=0xbbbb7e9c;
*((unsigned int *)((unsigned long)context_ptr+0x0000680c+4*3))=0x3a2ca6c0;
*((unsigned int *)((unsigned long)context_ptr+0x0000680c+4*4))=0x51c918e5;
*((unsigned int *)((unsigned long)context_ptr+0x0000680c+4*5))=0xd46ef52b;
*((unsigned int *)((unsigned long)context_ptr+0x0000680c+4*6))=0x0ddb6527;
*((unsigned int *)((unsigned long)context_ptr+0x0000680c+4*7))=0x9f2efc86;
*((unsigned int *)((unsigned long)context_ptr+0x0000680c+4*8))=0x54f9a9b0;
*((unsigned int *)((unsigned long)context_ptr+0x0000680c+4*9))=0xe92c3b5a;
*((unsigned int *)((unsigned long)context_ptr+0x0000680c+4*10))=0x3e179bd3;
*((unsigned int *)((unsigned long)context_ptr+0x0000680c+4*11))=0xac4a8633;
*((unsigned int *)((unsigned long)context_ptr+0x0000680c+4*12))=0xbf493569;
*((unsigned int *)((unsigned long)context_ptr+0x0000680c+4*13))=0x053f2f78;
*((unsigned int *)((unsigned long)context_ptr+0x0000680c+4*14))=0x6d898ea1;
*((unsigned int *)((unsigned long)context_ptr+0x0000680c+4*15))=0x0509b846;
*((unsigned int *)((unsigned long)context_ptr+0x0000680c+4*16))=0xf7af7acb;
*((unsigned int *)((unsigned long)context_ptr+0x0000680c+4*17))=0x5eb638b8;
*((unsigned int *)((unsigned long)context_ptr+0x0000680c+4*18))=0x5f5d4d6a;
*((unsigned int *)((unsigned long)context_ptr+0x0000680c+4*19))=0x9ad912bb;
*((unsigned int *)((unsigned long)context_ptr+0x00003768))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003768+4*1))=0x000064c4;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000768+4*1))=0x0000680c;
*((unsigned int *)((unsigned long)context_ptr+0x00000768+4*2))=0x00006068;
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
if(!memcmp((unsigned char *)context_ptr+0x000063e4,"\xf8\xab\xf1\x06\x90\x76\x75\xe5\xf9\x99\xa9\xe8\xbd\xb1\x08\x99\x38\xea\x26\x76\x9a\xc4\x0f\x48\x2c\x86\x57\x6c\xf5\x8e\xf8\x1f",32))
printf("strip: f8abf106907675e5, Pass\n");
else
printf("strip: f8abf106907675e5, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000066c4))=0x01ea1002;
*((unsigned int *)((unsigned long)context_ptr+0x000066c4+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000066c4+4*2))=0x02020051;
*((unsigned int *)((unsigned long)context_ptr+0x000066c4+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x0000638c))=0x563864cf;
*((unsigned int *)((unsigned long)context_ptr+0x0000638c+4*1))=0xea5c5d1e;
*((unsigned int *)((unsigned long)context_ptr+0x0000638c+4*2))=0x7f3e6795;
*((unsigned int *)((unsigned long)context_ptr+0x0000638c+4*3))=0xe157a80a;
*((unsigned int *)((unsigned long)context_ptr+0x0000638c+4*4))=0x195f0fe8;
*((unsigned int *)((unsigned long)context_ptr+0x0000638c+4*5))=0xb5c0d7b8;
*((unsigned int *)((unsigned long)context_ptr+0x0000638c+4*6))=0x5f35c14a;
*((unsigned int *)((unsigned long)context_ptr+0x0000638c+4*7))=0x19cedff8;
*((unsigned int *)((unsigned long)context_ptr+0x0000638c+4*8))=0x25d2aa6c;
*((unsigned int *)((unsigned long)context_ptr+0x0000638c+4*9))=0x04a2f6c9;
*((unsigned int *)((unsigned long)context_ptr+0x0000638c+4*10))=0x231344c5;
*((unsigned int *)((unsigned long)context_ptr+0x0000638c+4*11))=0x61092944;
*((unsigned int *)((unsigned long)context_ptr+0x0000638c+4*12))=0x05c56211;
*((unsigned int *)((unsigned long)context_ptr+0x0000638c+4*13))=0x92de43be;
*((unsigned int *)((unsigned long)context_ptr+0x0000638c+4*14))=0x6e19e892;
*((unsigned int *)((unsigned long)context_ptr+0x0000638c+4*15))=0xd8086135;
*((unsigned int *)((unsigned long)context_ptr+0x0000638c+4*16))=0x9f81bd01;
*((unsigned int *)((unsigned long)context_ptr+0x0000638c+4*17))=0xd7490202;
*((unsigned int *)((unsigned long)context_ptr+0x0000638c+4*18))=0xaff14ff0;
*((unsigned int *)((unsigned long)context_ptr+0x0000638c+4*19))=0x5e4dc46c;
*((unsigned int *)((unsigned long)context_ptr+0x0000638c+4*20))=0x000000d6;
*((unsigned int *)((unsigned long)context_ptr+0x00003780))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003780+4*1))=0x000063e0;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000780+4*1))=0x0000638c;
*((unsigned int *)((unsigned long)context_ptr+0x00000780+4*2))=0x000066c4;
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
if(!memcmp((unsigned char *)context_ptr+0x000064e8,"\x07\x16\x91\xb6\xa8\x3f\x9e\x2c\x5d\x52\xf3\xec\x52\x41\xf9\x5e\x37\x5b\x0f\x54\x7c\x98\xdb\xdb\xe9\xbe\x8b\xe5\x26\xe2\x4d\x05",32))
printf("strip: 071691b6a83f9e2c, Pass\n");
else
printf("strip: 071691b6a83f9e2c, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006400))=0x01ea1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006400+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006400+4*2))=0x02020052;
*((unsigned int *)((unsigned long)context_ptr+0x00006400+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x00006098))=0x7b8a6840;
*((unsigned int *)((unsigned long)context_ptr+0x00006098+4*1))=0xac81dd2d;
*((unsigned int *)((unsigned long)context_ptr+0x00006098+4*2))=0x234d6c70;
*((unsigned int *)((unsigned long)context_ptr+0x00006098+4*3))=0xc207ff89;
*((unsigned int *)((unsigned long)context_ptr+0x00006098+4*4))=0x3b829784;
*((unsigned int *)((unsigned long)context_ptr+0x00006098+4*5))=0x978b77b7;
*((unsigned int *)((unsigned long)context_ptr+0x00006098+4*6))=0xb7c60b91;
*((unsigned int *)((unsigned long)context_ptr+0x00006098+4*7))=0x6ead3828;
*((unsigned int *)((unsigned long)context_ptr+0x00006098+4*8))=0xca9c09fe;
*((unsigned int *)((unsigned long)context_ptr+0x00006098+4*9))=0x513ef34f;
*((unsigned int *)((unsigned long)context_ptr+0x00006098+4*10))=0xb2a51267;
*((unsigned int *)((unsigned long)context_ptr+0x00006098+4*11))=0x975316c8;
*((unsigned int *)((unsigned long)context_ptr+0x00006098+4*12))=0xde77a788;
*((unsigned int *)((unsigned long)context_ptr+0x00006098+4*13))=0x230cc7ec;
*((unsigned int *)((unsigned long)context_ptr+0x00006098+4*14))=0x6500e42d;
*((unsigned int *)((unsigned long)context_ptr+0x00006098+4*15))=0x88d1f0f6;
*((unsigned int *)((unsigned long)context_ptr+0x00006098+4*16))=0xb09bbb58;
*((unsigned int *)((unsigned long)context_ptr+0x00006098+4*17))=0xdd618090;
*((unsigned int *)((unsigned long)context_ptr+0x00006098+4*18))=0x95a09e0f;
*((unsigned int *)((unsigned long)context_ptr+0x00006098+4*19))=0xa77a6d2e;
*((unsigned int *)((unsigned long)context_ptr+0x00006098+4*20))=0x0000177e;
*((unsigned int *)((unsigned long)context_ptr+0x00003798))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003798+4*1))=0x000064e4;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000798+4*1))=0x00006098;
*((unsigned int *)((unsigned long)context_ptr+0x00000798+4*2))=0x00006400;
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
if(!memcmp((unsigned char *)context_ptr+0x000061a8,"\x6a\x36\x88\x87\x54\x54\x1e\xae\x91\xde\x5d\x0d\xf2\x8d\xfa\x84\xec\x08\xdb\xd5\xd5\xf3\xd1\x23\x3b\x75\x56\x6e\xea\x9f\xdc\x7b",32))
printf("strip: 6a36888754541eae, Pass\n");
else
printf("strip: 6a36888754541eae, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006410))=0x01ea1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006410+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006410+4*2))=0x02020053;
*((unsigned int *)((unsigned long)context_ptr+0x00006410+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x000060ec))=0x259e3ad5;
*((unsigned int *)((unsigned long)context_ptr+0x000060ec+4*1))=0x9b577c2d;
*((unsigned int *)((unsigned long)context_ptr+0x000060ec+4*2))=0xb94d795a;
*((unsigned int *)((unsigned long)context_ptr+0x000060ec+4*3))=0x37800608;
*((unsigned int *)((unsigned long)context_ptr+0x000060ec+4*4))=0x692182a8;
*((unsigned int *)((unsigned long)context_ptr+0x000060ec+4*5))=0x27a865d0;
*((unsigned int *)((unsigned long)context_ptr+0x000060ec+4*6))=0x9f319930;
*((unsigned int *)((unsigned long)context_ptr+0x000060ec+4*7))=0xc20389d8;
*((unsigned int *)((unsigned long)context_ptr+0x000060ec+4*8))=0x28496846;
*((unsigned int *)((unsigned long)context_ptr+0x000060ec+4*9))=0x5f0abca5;
*((unsigned int *)((unsigned long)context_ptr+0x000060ec+4*10))=0x03f9d6bc;
*((unsigned int *)((unsigned long)context_ptr+0x000060ec+4*11))=0xf30e081c;
*((unsigned int *)((unsigned long)context_ptr+0x000060ec+4*12))=0x9e451539;
*((unsigned int *)((unsigned long)context_ptr+0x000060ec+4*13))=0xc4e3e2e9;
*((unsigned int *)((unsigned long)context_ptr+0x000060ec+4*14))=0x247a36ca;
*((unsigned int *)((unsigned long)context_ptr+0x000060ec+4*15))=0xa4af6f55;
*((unsigned int *)((unsigned long)context_ptr+0x000060ec+4*16))=0xb0b75374;
*((unsigned int *)((unsigned long)context_ptr+0x000060ec+4*17))=0x95e60382;
*((unsigned int *)((unsigned long)context_ptr+0x000060ec+4*18))=0x09216230;
*((unsigned int *)((unsigned long)context_ptr+0x000060ec+4*19))=0xae7667c5;
*((unsigned int *)((unsigned long)context_ptr+0x000060ec+4*20))=0x00637169;
*((unsigned int *)((unsigned long)context_ptr+0x000037b0))=0x04c00020;
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
*((unsigned int *)((unsigned long)context_ptr+0x000007b0+4*1))=0x000060ec;
*((unsigned int *)((unsigned long)context_ptr+0x000007b0+4*2))=0x00006410;
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
if(!memcmp((unsigned char *)context_ptr+0x00006508,"\x63\x23\xa1\x09\x74\x13\xfb\xf1\xc8\xe7\x95\x8a\x19\x87\x9d\x07\xe7\xce\xfd\x28\x22\xdb\x49\xcf\xc1\x1a\x4d\xb2\x85\xde\x88\x88",32))
printf("strip: 6323a1097413fbf1, Pass\n");
else
printf("strip: 6323a1097413fbf1, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006420))=0x01ea1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006420+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006420+4*2))=0x02020054;
*((unsigned int *)((unsigned long)context_ptr+0x00006420+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x00006140))=0x5405c5c1;
*((unsigned int *)((unsigned long)context_ptr+0x00006140+4*1))=0x568c3a50;
*((unsigned int *)((unsigned long)context_ptr+0x00006140+4*2))=0x5526c028;
*((unsigned int *)((unsigned long)context_ptr+0x00006140+4*3))=0x6d59c6e4;
*((unsigned int *)((unsigned long)context_ptr+0x00006140+4*4))=0xc5fab35d;
*((unsigned int *)((unsigned long)context_ptr+0x00006140+4*5))=0xf2600a00;
*((unsigned int *)((unsigned long)context_ptr+0x00006140+4*6))=0x83d66294;
*((unsigned int *)((unsigned long)context_ptr+0x00006140+4*7))=0xb03d8cbf;
*((unsigned int *)((unsigned long)context_ptr+0x00006140+4*8))=0x029c1e34;
*((unsigned int *)((unsigned long)context_ptr+0x00006140+4*9))=0x68654376;
*((unsigned int *)((unsigned long)context_ptr+0x00006140+4*10))=0x4387176d;
*((unsigned int *)((unsigned long)context_ptr+0x00006140+4*11))=0x9ed917e9;
*((unsigned int *)((unsigned long)context_ptr+0x00006140+4*12))=0x8f8a8959;
*((unsigned int *)((unsigned long)context_ptr+0x00006140+4*13))=0xbc1190e2;
*((unsigned int *)((unsigned long)context_ptr+0x00006140+4*14))=0x2a7fc815;
*((unsigned int *)((unsigned long)context_ptr+0x00006140+4*15))=0x9fd6ac50;
*((unsigned int *)((unsigned long)context_ptr+0x00006140+4*16))=0x269730c5;
*((unsigned int *)((unsigned long)context_ptr+0x00006140+4*17))=0xaf01faea;
*((unsigned int *)((unsigned long)context_ptr+0x00006140+4*18))=0x43b32d14;
*((unsigned int *)((unsigned long)context_ptr+0x00006140+4*19))=0x2120d30b;
*((unsigned int *)((unsigned long)context_ptr+0x00006140+4*20))=0x4db9f8e2;
*((unsigned int *)((unsigned long)context_ptr+0x000037c8))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x000037c8+4*1))=0x000065c8;
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
*((unsigned int *)((unsigned long)context_ptr+0x000007c8+4*1))=0x00006140;
*((unsigned int *)((unsigned long)context_ptr+0x000007c8+4*2))=0x00006420;
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
if(!memcmp((unsigned char *)context_ptr+0x00006210,"\x77\x9e\x94\x54\xbb\x91\x65\x57\x7c\x62\xf5\x6c\x78\x70\x7d\x53\xf7\x2b\x42\x79\x0d\xdc\x93\x69\x1e\xe0\x17\xb3\xa3\x2f\x7c\xe3",32))
printf("strip: 779e9454bb916557, Pass\n");
else
printf("strip: 779e9454bb916557, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006430))=0x01ea1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006430+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006430+4*2))=0x02020055;
*((unsigned int *)((unsigned long)context_ptr+0x00006430+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x00006194))=0x152d9ca1;
*((unsigned int *)((unsigned long)context_ptr+0x00006194+4*1))=0x4a30440c;
*((unsigned int *)((unsigned long)context_ptr+0x00006194+4*2))=0xb4ecb397;
*((unsigned int *)((unsigned long)context_ptr+0x00006194+4*3))=0xd2da4aa1;
*((unsigned int *)((unsigned long)context_ptr+0x00006194+4*4))=0xcbbbbbc4;
*((unsigned int *)((unsigned long)context_ptr+0x00006194+4*5))=0xf3494390;
*((unsigned int *)((unsigned long)context_ptr+0x00006194+4*6))=0x8c09762a;
*((unsigned int *)((unsigned long)context_ptr+0x00006194+4*7))=0x4d08477c;
*((unsigned int *)((unsigned long)context_ptr+0x00006194+4*8))=0x1c07c58e;
*((unsigned int *)((unsigned long)context_ptr+0x00006194+4*9))=0xb6cccd75;
*((unsigned int *)((unsigned long)context_ptr+0x00006194+4*10))=0x0d9cf14f;
*((unsigned int *)((unsigned long)context_ptr+0x00006194+4*11))=0xe50b7e46;
*((unsigned int *)((unsigned long)context_ptr+0x00006194+4*12))=0x4106876c;
*((unsigned int *)((unsigned long)context_ptr+0x00006194+4*13))=0xae83945d;
*((unsigned int *)((unsigned long)context_ptr+0x00006194+4*14))=0x9a63852d;
*((unsigned int *)((unsigned long)context_ptr+0x00006194+4*15))=0x8f5d57ba;
*((unsigned int *)((unsigned long)context_ptr+0x00006194+4*16))=0xb8bea0d3;
*((unsigned int *)((unsigned long)context_ptr+0x00006194+4*17))=0x9f26a195;
*((unsigned int *)((unsigned long)context_ptr+0x00006194+4*18))=0xb60010ba;
*((unsigned int *)((unsigned long)context_ptr+0x00006194+4*19))=0xb59006d8;
*((unsigned int *)((unsigned long)context_ptr+0x00006194+4*20))=0x946562e3;
*((unsigned int *)((unsigned long)context_ptr+0x00006194+4*21))=0x000000a9;
*((unsigned int *)((unsigned long)context_ptr+0x000037e0))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x000037e0+4*1))=0x00006504;
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
*((unsigned int *)((unsigned long)context_ptr+0x000007e0+4*1))=0x00006194;
*((unsigned int *)((unsigned long)context_ptr+0x000007e0+4*2))=0x00006430;
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
if(!memcmp((unsigned char *)context_ptr+0x00006528,"\x7d\x67\x41\xff\xa0\xbc\xf3\x62\xf0\x17\x34\x1f\xdf\x6e\x88\xbd\x49\x11\x89\xd2\xd1\x36\x2a\xc2\x17\x3c\xeb\x16\x8e\xae\x41\x9e",32))
printf("strip: 7d6741ffa0bcf362, Pass\n");
else
printf("strip: 7d6741ffa0bcf362, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006440))=0x01ea1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006440+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006440+4*2))=0x02020056;
*((unsigned int *)((unsigned long)context_ptr+0x00006440+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x000066d4))=0xf0edf46c;
*((unsigned int *)((unsigned long)context_ptr+0x000066d4+4*1))=0xed711e9e;
*((unsigned int *)((unsigned long)context_ptr+0x000066d4+4*2))=0x4ddc8cbd;
*((unsigned int *)((unsigned long)context_ptr+0x000066d4+4*3))=0x9bb9b4a3;
*((unsigned int *)((unsigned long)context_ptr+0x000066d4+4*4))=0x42536867;
*((unsigned int *)((unsigned long)context_ptr+0x000066d4+4*5))=0x925bada0;
*((unsigned int *)((unsigned long)context_ptr+0x000066d4+4*6))=0xc0f83357;
*((unsigned int *)((unsigned long)context_ptr+0x000066d4+4*7))=0x5fac01b2;
*((unsigned int *)((unsigned long)context_ptr+0x000066d4+4*8))=0x263fee81;
*((unsigned int *)((unsigned long)context_ptr+0x000066d4+4*9))=0x661688b4;
*((unsigned int *)((unsigned long)context_ptr+0x000066d4+4*10))=0x7fe265e2;
*((unsigned int *)((unsigned long)context_ptr+0x000066d4+4*11))=0x46c4b3dd;
*((unsigned int *)((unsigned long)context_ptr+0x000066d4+4*12))=0xd3e9fbe5;
*((unsigned int *)((unsigned long)context_ptr+0x000066d4+4*13))=0xfabd1cd8;
*((unsigned int *)((unsigned long)context_ptr+0x000066d4+4*14))=0xb75d2d92;
*((unsigned int *)((unsigned long)context_ptr+0x000066d4+4*15))=0x128a2a99;
*((unsigned int *)((unsigned long)context_ptr+0x000066d4+4*16))=0x4ad309c3;
*((unsigned int *)((unsigned long)context_ptr+0x000066d4+4*17))=0x97fee9ff;
*((unsigned int *)((unsigned long)context_ptr+0x000066d4+4*18))=0xcb17c28a;
*((unsigned int *)((unsigned long)context_ptr+0x000066d4+4*19))=0x676381dc;
*((unsigned int *)((unsigned long)context_ptr+0x000066d4+4*20))=0xd43686bb;
*((unsigned int *)((unsigned long)context_ptr+0x000066d4+4*21))=0x0000065c;
*((unsigned int *)((unsigned long)context_ptr+0x000037f8))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x000037f8+4*1))=0x00006524;
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
*((unsigned int *)((unsigned long)context_ptr+0x000007f8+4*1))=0x000066d4;
*((unsigned int *)((unsigned long)context_ptr+0x000007f8+4*2))=0x00006440;
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
if(!memcmp((unsigned char *)context_ptr+0x000065e8,"\xb9\x32\x60\x73\xb1\x31\x36\xaf\x81\xcc\x6d\xb7\x97\xf0\x6f\x7d\xa8\xf5\x7d\x33\x7c\xc0\xb1\x92\x0d\xc7\x04\xc6\x94\xc9\xec\x10",32))
printf("strip: b9326073b13136af, Pass\n");
else
printf("strip: b9326073b13136af, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006450))=0x01ea1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006450+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006450+4*2))=0x02020057;
*((unsigned int *)((unsigned long)context_ptr+0x00006450+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x000061ec))=0xdd44491d;
*((unsigned int *)((unsigned long)context_ptr+0x000061ec+4*1))=0x932135b9;
*((unsigned int *)((unsigned long)context_ptr+0x000061ec+4*2))=0x43f038af;
*((unsigned int *)((unsigned long)context_ptr+0x000061ec+4*3))=0xdb5072d5;
*((unsigned int *)((unsigned long)context_ptr+0x000061ec+4*4))=0x4e8c7af8;
*((unsigned int *)((unsigned long)context_ptr+0x000061ec+4*5))=0xe9aa409e;
*((unsigned int *)((unsigned long)context_ptr+0x000061ec+4*6))=0x0fc9e688;
*((unsigned int *)((unsigned long)context_ptr+0x000061ec+4*7))=0x7a76bde0;
*((unsigned int *)((unsigned long)context_ptr+0x000061ec+4*8))=0x934a57c7;
*((unsigned int *)((unsigned long)context_ptr+0x000061ec+4*9))=0x220c6a04;
*((unsigned int *)((unsigned long)context_ptr+0x000061ec+4*10))=0xdd349fc8;
*((unsigned int *)((unsigned long)context_ptr+0x000061ec+4*11))=0x597b418b;
*((unsigned int *)((unsigned long)context_ptr+0x000061ec+4*12))=0x6aa8ff9e;
*((unsigned int *)((unsigned long)context_ptr+0x000061ec+4*13))=0xb2af8c8f;
*((unsigned int *)((unsigned long)context_ptr+0x000061ec+4*14))=0x4193788a;
*((unsigned int *)((unsigned long)context_ptr+0x000061ec+4*15))=0xa56f1e68;
*((unsigned int *)((unsigned long)context_ptr+0x000061ec+4*16))=0x94dc8a75;
*((unsigned int *)((unsigned long)context_ptr+0x000061ec+4*17))=0x624dc904;
*((unsigned int *)((unsigned long)context_ptr+0x000061ec+4*18))=0x3b4fd8f7;
*((unsigned int *)((unsigned long)context_ptr+0x000061ec+4*19))=0x11c03766;
*((unsigned int *)((unsigned long)context_ptr+0x000061ec+4*20))=0xa4007000;
*((unsigned int *)((unsigned long)context_ptr+0x000061ec+4*21))=0x00ed0eb3;
*((unsigned int *)((unsigned long)context_ptr+0x00003810))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003810+4*1))=0x000065e8;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000810+4*1))=0x000061ec;
*((unsigned int *)((unsigned long)context_ptr+0x00000810+4*2))=0x00006450;
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
if(!memcmp((unsigned char *)context_ptr+0x00006608,"\x4e\x5f\x9b\x4f\x15\xbd\x77\x98\x4a\x2d\x63\x31\xbe\x1f\x53\xa7\x5a\x9d\x40\x64\x9a\xc5\x7c\xa7\x35\xd5\x23\x5e\xe2\x03\x7e\xe4",32))
printf("strip: 4e5f9b4f15bd7798, Pass\n");
else
printf("strip: 4e5f9b4f15bd7798, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006544))=0x01ea1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006544+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006544+4*2))=0x02020058;
*((unsigned int *)((unsigned long)context_ptr+0x00006544+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x00006244))=0x4ed3cd0e;
*((unsigned int *)((unsigned long)context_ptr+0x00006244+4*1))=0xe45abb3f;
*((unsigned int *)((unsigned long)context_ptr+0x00006244+4*2))=0x90a37a9e;
*((unsigned int *)((unsigned long)context_ptr+0x00006244+4*3))=0x42ef74d6;
*((unsigned int *)((unsigned long)context_ptr+0x00006244+4*4))=0x8459f119;
*((unsigned int *)((unsigned long)context_ptr+0x00006244+4*5))=0x8f9c5f4a;
*((unsigned int *)((unsigned long)context_ptr+0x00006244+4*6))=0x16a09286;
*((unsigned int *)((unsigned long)context_ptr+0x00006244+4*7))=0x6b7f38d6;
*((unsigned int *)((unsigned long)context_ptr+0x00006244+4*8))=0x0b46f634;
*((unsigned int *)((unsigned long)context_ptr+0x00006244+4*9))=0x832a5b1e;
*((unsigned int *)((unsigned long)context_ptr+0x00006244+4*10))=0x08fd53f9;
*((unsigned int *)((unsigned long)context_ptr+0x00006244+4*11))=0xabeebe85;
*((unsigned int *)((unsigned long)context_ptr+0x00006244+4*12))=0xbc771ce4;
*((unsigned int *)((unsigned long)context_ptr+0x00006244+4*13))=0x98dc5389;
*((unsigned int *)((unsigned long)context_ptr+0x00006244+4*14))=0x6bc87508;
*((unsigned int *)((unsigned long)context_ptr+0x00006244+4*15))=0x3d8d7c2a;
*((unsigned int *)((unsigned long)context_ptr+0x00006244+4*16))=0x5ff484a1;
*((unsigned int *)((unsigned long)context_ptr+0x00006244+4*17))=0xb3c9e2da;
*((unsigned int *)((unsigned long)context_ptr+0x00006244+4*18))=0x2389118b;
*((unsigned int *)((unsigned long)context_ptr+0x00006244+4*19))=0x237e3c5d;
*((unsigned int *)((unsigned long)context_ptr+0x00006244+4*20))=0x17db15db;
*((unsigned int *)((unsigned long)context_ptr+0x00006244+4*21))=0x130389f8;
*((unsigned int *)((unsigned long)context_ptr+0x00003828))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003828+4*1))=0x00006608;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000828+4*1))=0x00006244;
*((unsigned int *)((unsigned long)context_ptr+0x00000828+4*2))=0x00006544;
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
if(!memcmp((unsigned char *)context_ptr+0x00006310,"\x09\xd8\x9c\xcf\x8c\x56\x3d\x5d\x73\xe6\x54\x70\xdd\x08\xa3\x7b\x91\x08\x3a\x9f\x0c\x56\x84\x5d\x37\x86\xd8\x77\x86\xc4\x5a\x50",32))
printf("strip: 09d89ccf8c563d5d, Pass\n");
else
printf("strip: 09d89ccf8c563d5d, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006554))=0x01ea1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006554+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006554+4*2))=0x02020059;
*((unsigned int *)((unsigned long)context_ptr+0x00006554+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x0000629c))=0x17d8655d;
*((unsigned int *)((unsigned long)context_ptr+0x0000629c+4*1))=0x5ff6335f;
*((unsigned int *)((unsigned long)context_ptr+0x0000629c+4*2))=0x5f127e39;
*((unsigned int *)((unsigned long)context_ptr+0x0000629c+4*3))=0x2684705d;
*((unsigned int *)((unsigned long)context_ptr+0x0000629c+4*4))=0x4f62ad19;
*((unsigned int *)((unsigned long)context_ptr+0x0000629c+4*5))=0x453a815a;
*((unsigned int *)((unsigned long)context_ptr+0x0000629c+4*6))=0x5bcf5df6;
*((unsigned int *)((unsigned long)context_ptr+0x0000629c+4*7))=0xfd331220;
*((unsigned int *)((unsigned long)context_ptr+0x0000629c+4*8))=0x9adafd6b;
*((unsigned int *)((unsigned long)context_ptr+0x0000629c+4*9))=0x3ec62a2c;
*((unsigned int *)((unsigned long)context_ptr+0x0000629c+4*10))=0x388e6779;
*((unsigned int *)((unsigned long)context_ptr+0x0000629c+4*11))=0x3fbbf3bb;
*((unsigned int *)((unsigned long)context_ptr+0x0000629c+4*12))=0x625527d8;
*((unsigned int *)((unsigned long)context_ptr+0x0000629c+4*13))=0x2850598d;
*((unsigned int *)((unsigned long)context_ptr+0x0000629c+4*14))=0xf9bfb063;
*((unsigned int *)((unsigned long)context_ptr+0x0000629c+4*15))=0xc50c98a1;
*((unsigned int *)((unsigned long)context_ptr+0x0000629c+4*16))=0x02fd3c72;
*((unsigned int *)((unsigned long)context_ptr+0x0000629c+4*17))=0x3d3aed79;
*((unsigned int *)((unsigned long)context_ptr+0x0000629c+4*18))=0xa9a9b221;
*((unsigned int *)((unsigned long)context_ptr+0x0000629c+4*19))=0xec0cb2b5;
*((unsigned int *)((unsigned long)context_ptr+0x0000629c+4*20))=0xd2868db8;
*((unsigned int *)((unsigned long)context_ptr+0x0000629c+4*21))=0x69b2dc74;
*((unsigned int *)((unsigned long)context_ptr+0x0000629c+4*22))=0x000000b6;
*((unsigned int *)((unsigned long)context_ptr+0x00003840))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003840+4*1))=0x000062f8;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000840+4*1))=0x0000629c;
*((unsigned int *)((unsigned long)context_ptr+0x00000840+4*2))=0x00006554;
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
if(!memcmp((unsigned char *)context_ptr+0x00006464,"\x88\x58\x3f\x1a\x1e\x39\x6c\x97\x5e\x35\x55\xfa\x7b\x01\xc0\xf4\x8b\xf5\xdc\x64\x14\x60\x6d\xf5\xff\xff\x40\x8c\x02\x95\x13\xda",32))
printf("strip: 88583f1a1e396c97, Pass\n");
else
printf("strip: 88583f1a1e396c97, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006460))=0x01ea1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006460+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006460+4*2))=0x0202005a;
*((unsigned int *)((unsigned long)context_ptr+0x00006460+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x0000685c))=0xdbb42769;
*((unsigned int *)((unsigned long)context_ptr+0x0000685c+4*1))=0xd69e1955;
*((unsigned int *)((unsigned long)context_ptr+0x0000685c+4*2))=0x0ec627fb;
*((unsigned int *)((unsigned long)context_ptr+0x0000685c+4*3))=0x0f1f0184;
*((unsigned int *)((unsigned long)context_ptr+0x0000685c+4*4))=0x2c99ffca;
*((unsigned int *)((unsigned long)context_ptr+0x0000685c+4*5))=0x8158304b;
*((unsigned int *)((unsigned long)context_ptr+0x0000685c+4*6))=0x1656589f;
*((unsigned int *)((unsigned long)context_ptr+0x0000685c+4*7))=0xe0dc4b05;
*((unsigned int *)((unsigned long)context_ptr+0x0000685c+4*8))=0x724380f0;
*((unsigned int *)((unsigned long)context_ptr+0x0000685c+4*9))=0x234a761b;
*((unsigned int *)((unsigned long)context_ptr+0x0000685c+4*10))=0x56d51556;
*((unsigned int *)((unsigned long)context_ptr+0x0000685c+4*11))=0x0b912aff;
*((unsigned int *)((unsigned long)context_ptr+0x0000685c+4*12))=0xfe356bd2;
*((unsigned int *)((unsigned long)context_ptr+0x0000685c+4*13))=0x7635d342;
*((unsigned int *)((unsigned long)context_ptr+0x0000685c+4*14))=0x0c6a50c1;
*((unsigned int *)((unsigned long)context_ptr+0x0000685c+4*15))=0xa73f783a;
*((unsigned int *)((unsigned long)context_ptr+0x0000685c+4*16))=0x42f9c354;
*((unsigned int *)((unsigned long)context_ptr+0x0000685c+4*17))=0x604dd3f5;
*((unsigned int *)((unsigned long)context_ptr+0x0000685c+4*18))=0xc3c71d4f;
*((unsigned int *)((unsigned long)context_ptr+0x0000685c+4*19))=0x80646cff;
*((unsigned int *)((unsigned long)context_ptr+0x0000685c+4*20))=0x3de2e7a9;
*((unsigned int *)((unsigned long)context_ptr+0x0000685c+4*21))=0x945eb454;
*((unsigned int *)((unsigned long)context_ptr+0x0000685c+4*22))=0x00006fb2;
*((unsigned int *)((unsigned long)context_ptr+0x00003858))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003858+4*1))=0x00006318;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000858+4*1))=0x0000685c;
*((unsigned int *)((unsigned long)context_ptr+0x00000858+4*2))=0x00006460;
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
if(!memcmp((unsigned char *)context_ptr+0x00006568,"\xfa\xd2\x04\x52\x45\x88\x4c\xc7\xd4\xa9\x37\x94\xcf\xe8\xd7\xd7\xcd\x31\xfa\x77\x1a\x18\x53\x6d\x14\x20\x97\xc8\x10\x17\xcc\xe4",32))
printf("strip: fad2045245884cc7, Pass\n");
else
printf("strip: fad2045245884cc7, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006470))=0x01ea1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006470+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006470+4*2))=0x0202005b;
*((unsigned int *)((unsigned long)context_ptr+0x00006470+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x000068b8))=0xb4b5fe1b;
*((unsigned int *)((unsigned long)context_ptr+0x000068b8+4*1))=0x9898691e;
*((unsigned int *)((unsigned long)context_ptr+0x000068b8+4*2))=0x3b98e523;
*((unsigned int *)((unsigned long)context_ptr+0x000068b8+4*3))=0x73fd8c78;
*((unsigned int *)((unsigned long)context_ptr+0x000068b8+4*4))=0xc65f4823;
*((unsigned int *)((unsigned long)context_ptr+0x000068b8+4*5))=0x672c78a4;
*((unsigned int *)((unsigned long)context_ptr+0x000068b8+4*6))=0xd29a8ab2;
*((unsigned int *)((unsigned long)context_ptr+0x000068b8+4*7))=0x898ee91a;
*((unsigned int *)((unsigned long)context_ptr+0x000068b8+4*8))=0xf2e09f68;
*((unsigned int *)((unsigned long)context_ptr+0x000068b8+4*9))=0x9c5f357e;
*((unsigned int *)((unsigned long)context_ptr+0x000068b8+4*10))=0x0891f3ef;
*((unsigned int *)((unsigned long)context_ptr+0x000068b8+4*11))=0xb372fed9;
*((unsigned int *)((unsigned long)context_ptr+0x000068b8+4*12))=0x6bcaa098;
*((unsigned int *)((unsigned long)context_ptr+0x000068b8+4*13))=0xb42a4b44;
*((unsigned int *)((unsigned long)context_ptr+0x000068b8+4*14))=0x9a7d45c4;
*((unsigned int *)((unsigned long)context_ptr+0x000068b8+4*15))=0x3e127f91;
*((unsigned int *)((unsigned long)context_ptr+0x000068b8+4*16))=0x17587bb6;
*((unsigned int *)((unsigned long)context_ptr+0x000068b8+4*17))=0x88237b9c;
*((unsigned int *)((unsigned long)context_ptr+0x000068b8+4*18))=0xa3567e90;
*((unsigned int *)((unsigned long)context_ptr+0x000068b8+4*19))=0xfa257436;
*((unsigned int *)((unsigned long)context_ptr+0x000068b8+4*20))=0x243402eb;
*((unsigned int *)((unsigned long)context_ptr+0x000068b8+4*21))=0x303b53c5;
*((unsigned int *)((unsigned long)context_ptr+0x000068b8+4*22))=0x00c27971;
*((unsigned int *)((unsigned long)context_ptr+0x00003870))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003870+4*1))=0x00006564;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000870+4*1))=0x000068b8;
*((unsigned int *)((unsigned long)context_ptr+0x00000870+4*2))=0x00006470;
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
if(!memcmp((unsigned char *)context_ptr+0x00006078,"\xca\x69\x57\xcc\xbe\x62\x11\xc1\xbb\xa4\xd0\xe4\x7d\xd1\xad\x67\x5b\x64\x55\x07\x4f\xbc\xad\xbf\x5f\x06\xc5\xdc\x38\x1b\x17\xc0",32))
printf("strip: ca6957ccbe6211c1, Pass\n");
else
printf("strip: ca6957ccbe6211c1, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006078))=0x01ea1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006078+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006078+4*2))=0x0202005c;
*((unsigned int *)((unsigned long)context_ptr+0x00006078+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x00006628))=0xf39d0c3c;
*((unsigned int *)((unsigned long)context_ptr+0x00006628+4*1))=0x1fa77c50;
*((unsigned int *)((unsigned long)context_ptr+0x00006628+4*2))=0x888e8ff9;
*((unsigned int *)((unsigned long)context_ptr+0x00006628+4*3))=0xbd064507;
*((unsigned int *)((unsigned long)context_ptr+0x00006628+4*4))=0x0e20e75b;
*((unsigned int *)((unsigned long)context_ptr+0x00006628+4*5))=0x948f2d09;
*((unsigned int *)((unsigned long)context_ptr+0x00006628+4*6))=0x812f74b4;
*((unsigned int *)((unsigned long)context_ptr+0x00006628+4*7))=0xe1359134;
*((unsigned int *)((unsigned long)context_ptr+0x00006628+4*8))=0xea34c471;
*((unsigned int *)((unsigned long)context_ptr+0x00006628+4*9))=0xcbedac01;
*((unsigned int *)((unsigned long)context_ptr+0x00006628+4*10))=0x05f206a0;
*((unsigned int *)((unsigned long)context_ptr+0x00006628+4*11))=0x4ab520b3;
*((unsigned int *)((unsigned long)context_ptr+0x00006628+4*12))=0x560ede5d;
*((unsigned int *)((unsigned long)context_ptr+0x00006628+4*13))=0x3cfa9176;
*((unsigned int *)((unsigned long)context_ptr+0x00006628+4*14))=0x244554b9;
*((unsigned int *)((unsigned long)context_ptr+0x00006628+4*15))=0xbb0c0419;
*((unsigned int *)((unsigned long)context_ptr+0x00006628+4*16))=0x9a2034f0;
*((unsigned int *)((unsigned long)context_ptr+0x00006628+4*17))=0xef1d18c0;
*((unsigned int *)((unsigned long)context_ptr+0x00006628+4*18))=0x4046235b;
*((unsigned int *)((unsigned long)context_ptr+0x00006628+4*19))=0xfe61daa1;
*((unsigned int *)((unsigned long)context_ptr+0x00006628+4*20))=0x802c2776;
*((unsigned int *)((unsigned long)context_ptr+0x00006628+4*21))=0x16326c80;
*((unsigned int *)((unsigned long)context_ptr+0x00006628+4*22))=0xcf812395;
*((unsigned int *)((unsigned long)context_ptr+0x00003888))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003888+4*1))=0x00006480;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000888+4*1))=0x00006628;
*((unsigned int *)((unsigned long)context_ptr+0x00000888+4*2))=0x00006078;
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
if(!memcmp((unsigned char *)context_ptr+0x00006588,"\x91\xc8\x2f\xc4\xaa\x6a\xd0\xc4\x86\x29\xef\xcc\xbe\x42\x1a\x3c\x82\x85\xa6\x45\x9d\xa2\x4f\x15\xee\x4e\x58\x70\x48\x7b\xd3\x56",32))
printf("strip: 91c82fc4aa6ad0c4, Pass\n");
else
printf("strip: 91c82fc4aa6ad0c4, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006088))=0x01ea1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006088+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006088+4*2))=0x0202005d;
*((unsigned int *)((unsigned long)context_ptr+0x00006088+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x0000672c))=0x8bb7bbf3;
*((unsigned int *)((unsigned long)context_ptr+0x0000672c+4*1))=0x8c20a402;
*((unsigned int *)((unsigned long)context_ptr+0x0000672c+4*2))=0x49a97d18;
*((unsigned int *)((unsigned long)context_ptr+0x0000672c+4*3))=0x0661f3bf;
*((unsigned int *)((unsigned long)context_ptr+0x0000672c+4*4))=0x87463c9a;
*((unsigned int *)((unsigned long)context_ptr+0x0000672c+4*5))=0x1d49de41;
*((unsigned int *)((unsigned long)context_ptr+0x0000672c+4*6))=0xb0be1ea5;
*((unsigned int *)((unsigned long)context_ptr+0x0000672c+4*7))=0xe551462a;
*((unsigned int *)((unsigned long)context_ptr+0x0000672c+4*8))=0xf93ec3f8;
*((unsigned int *)((unsigned long)context_ptr+0x0000672c+4*9))=0x0a7a3147;
*((unsigned int *)((unsigned long)context_ptr+0x0000672c+4*10))=0x1cb830e5;
*((unsigned int *)((unsigned long)context_ptr+0x0000672c+4*11))=0xc38ffe4a;
*((unsigned int *)((unsigned long)context_ptr+0x0000672c+4*12))=0x9b7e1850;
*((unsigned int *)((unsigned long)context_ptr+0x0000672c+4*13))=0xbed73d54;
*((unsigned int *)((unsigned long)context_ptr+0x0000672c+4*14))=0xc37b7c3c;
*((unsigned int *)((unsigned long)context_ptr+0x0000672c+4*15))=0x3da19785;
*((unsigned int *)((unsigned long)context_ptr+0x0000672c+4*16))=0xcf55ae0e;
*((unsigned int *)((unsigned long)context_ptr+0x0000672c+4*17))=0x0ddbb0ef;
*((unsigned int *)((unsigned long)context_ptr+0x0000672c+4*18))=0x54c5c7d7;
*((unsigned int *)((unsigned long)context_ptr+0x0000672c+4*19))=0xe7887e04;
*((unsigned int *)((unsigned long)context_ptr+0x0000672c+4*20))=0xdd4b816c;
*((unsigned int *)((unsigned long)context_ptr+0x0000672c+4*21))=0xe69a8d04;
*((unsigned int *)((unsigned long)context_ptr+0x0000672c+4*22))=0xda0645ff;
*((unsigned int *)((unsigned long)context_ptr+0x0000672c+4*23))=0x0000000a;
*((unsigned int *)((unsigned long)context_ptr+0x000038a0))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x000038a0+4*1))=0x00006584;
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
*((unsigned int *)((unsigned long)context_ptr+0x000008a0+4*1))=0x0000672c;
*((unsigned int *)((unsigned long)context_ptr+0x000008a0+4*2))=0x00006088;
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
if(!memcmp((unsigned char *)context_ptr+0x000064a4,"\xf4\xb9\xed\x84\x0d\x5e\xc4\x1d\x33\x21\x10\x1e\xe7\xab\x5e\xda\xef\x1b\x23\x8d\xc0\xb8\xd5\x0e\xe0\x00\xd2\x90\xb9\xd0\x3a\xba",32))
printf("strip: f4b9ed840d5ec41d, Pass\n");
else
printf("strip: f4b9ed840d5ec41d, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006058))=0x01ea1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*2))=0x0202005e;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x0000678c))=0x6cac4983;
*((unsigned int *)((unsigned long)context_ptr+0x0000678c+4*1))=0x5116ca02;
*((unsigned int *)((unsigned long)context_ptr+0x0000678c+4*2))=0xcdd1c327;
*((unsigned int *)((unsigned long)context_ptr+0x0000678c+4*3))=0xb0eb1ff7;
*((unsigned int *)((unsigned long)context_ptr+0x0000678c+4*4))=0x1a1cfa1e;
*((unsigned int *)((unsigned long)context_ptr+0x0000678c+4*5))=0xee1c3dab;
*((unsigned int *)((unsigned long)context_ptr+0x0000678c+4*6))=0x9e4f30e2;
*((unsigned int *)((unsigned long)context_ptr+0x0000678c+4*7))=0x9d93de90;
*((unsigned int *)((unsigned long)context_ptr+0x0000678c+4*8))=0x54042fed;
*((unsigned int *)((unsigned long)context_ptr+0x0000678c+4*9))=0x1076aaed;
*((unsigned int *)((unsigned long)context_ptr+0x0000678c+4*10))=0x36310874;
*((unsigned int *)((unsigned long)context_ptr+0x0000678c+4*11))=0xb51dc77a;
*((unsigned int *)((unsigned long)context_ptr+0x0000678c+4*12))=0xf103af82;
*((unsigned int *)((unsigned long)context_ptr+0x0000678c+4*13))=0xae246517;
*((unsigned int *)((unsigned long)context_ptr+0x0000678c+4*14))=0xd11e3e4a;
*((unsigned int *)((unsigned long)context_ptr+0x0000678c+4*15))=0x64cc4234;
*((unsigned int *)((unsigned long)context_ptr+0x0000678c+4*16))=0x88dfc8b1;
*((unsigned int *)((unsigned long)context_ptr+0x0000678c+4*17))=0x8e96d139;
*((unsigned int *)((unsigned long)context_ptr+0x0000678c+4*18))=0x5b999f27;
*((unsigned int *)((unsigned long)context_ptr+0x0000678c+4*19))=0xae3b73bd;
*((unsigned int *)((unsigned long)context_ptr+0x0000678c+4*20))=0xc556d2e8;
*((unsigned int *)((unsigned long)context_ptr+0x0000678c+4*21))=0x602603cc;
*((unsigned int *)((unsigned long)context_ptr+0x0000678c+4*22))=0x8b485cb1;
*((unsigned int *)((unsigned long)context_ptr+0x0000678c+4*23))=0x0000d91b;
*((unsigned int *)((unsigned long)context_ptr+0x000038b8))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x000038b8+4*1))=0x000067ec;
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
*((unsigned int *)((unsigned long)context_ptr+0x000008b8+4*1))=0x0000678c;
*((unsigned int *)((unsigned long)context_ptr+0x000008b8+4*2))=0x00006058;
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
if(!memcmp((unsigned char *)context_ptr+0x000064c4,"\x55\x17\x3f\xd3\x8a\x76\x92\x24\x35\x69\x4b\x6d\x98\x43\xdc\x2b\x56\x4a\xc1\x5c\xf4\x97\x7e\x38\xfa\xe8\x45\xa2\x4e\xba\x85\xc5",32))
printf("strip: 55173fd38a769224, Pass\n");
else
printf("strip: 55173fd38a769224, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006048))=0x01ea1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006048+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006048+4*2))=0x0202005f;
*((unsigned int *)((unsigned long)context_ptr+0x00006048+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x00006914))=0xacf1dc26;
*((unsigned int *)((unsigned long)context_ptr+0x00006914+4*1))=0xe1995242;
*((unsigned int *)((unsigned long)context_ptr+0x00006914+4*2))=0xcadb9db7;
*((unsigned int *)((unsigned long)context_ptr+0x00006914+4*3))=0xd87f30b3;
*((unsigned int *)((unsigned long)context_ptr+0x00006914+4*4))=0xb3161064;
*((unsigned int *)((unsigned long)context_ptr+0x00006914+4*5))=0xd43c3cb9;
*((unsigned int *)((unsigned long)context_ptr+0x00006914+4*6))=0x307630cb;
*((unsigned int *)((unsigned long)context_ptr+0x00006914+4*7))=0xf703d93a;
*((unsigned int *)((unsigned long)context_ptr+0x00006914+4*8))=0x5c6e8f29;
*((unsigned int *)((unsigned long)context_ptr+0x00006914+4*9))=0xd068aaf3;
*((unsigned int *)((unsigned long)context_ptr+0x00006914+4*10))=0x6cdb5552;
*((unsigned int *)((unsigned long)context_ptr+0x00006914+4*11))=0xdc576e5b;
*((unsigned int *)((unsigned long)context_ptr+0x00006914+4*12))=0x8a9d8a81;
*((unsigned int *)((unsigned long)context_ptr+0x00006914+4*13))=0x131f156b;
*((unsigned int *)((unsigned long)context_ptr+0x00006914+4*14))=0xf5237446;
*((unsigned int *)((unsigned long)context_ptr+0x00006914+4*15))=0x8c4e7a91;
*((unsigned int *)((unsigned long)context_ptr+0x00006914+4*16))=0xfda918b9;
*((unsigned int *)((unsigned long)context_ptr+0x00006914+4*17))=0xa2523e31;
*((unsigned int *)((unsigned long)context_ptr+0x00006914+4*18))=0x91e7faa8;
*((unsigned int *)((unsigned long)context_ptr+0x00006914+4*19))=0x8ba487ce;
*((unsigned int *)((unsigned long)context_ptr+0x00006914+4*20))=0x1bd32178;
*((unsigned int *)((unsigned long)context_ptr+0x00006914+4*21))=0xe4c71a69;
*((unsigned int *)((unsigned long)context_ptr+0x00006914+4*22))=0xe849d553;
*((unsigned int *)((unsigned long)context_ptr+0x00006914+4*23))=0x0004dbb1;
*((unsigned int *)((unsigned long)context_ptr+0x000038d0))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x000038d0+4*1))=0x00006684;
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
*((unsigned int *)((unsigned long)context_ptr+0x000008d0+4*1))=0x00006914;
*((unsigned int *)((unsigned long)context_ptr+0x000008d0+4*2))=0x00006048;
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
if(!memcmp((unsigned char *)context_ptr+0x000063e0,"\x02\x59\x90\xc9\xc0\x15\xb0\x03\x40\x6a\x47\x5c\x40\x37\x3c\x7c\x70\x04\xc5\x96\x76\xdf\xf5\x32\xb3\xb1\xcf\x3a\xa0\x0e\xb2\x04",32))
printf("strip: 025990c9c015b003, Pass\n");
else
printf("strip: 025990c9c015b003, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006068))=0x01ea1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006068+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006068+4*2))=0x02020060;
*((unsigned int *)((unsigned long)context_ptr+0x00006068+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x00006338))=0x55442258;
*((unsigned int *)((unsigned long)context_ptr+0x00006338+4*1))=0x50142252;
*((unsigned int *)((unsigned long)context_ptr+0x00006338+4*2))=0x7c86ab4f;
*((unsigned int *)((unsigned long)context_ptr+0x00006338+4*3))=0xd0de945c;
*((unsigned int *)((unsigned long)context_ptr+0x00006338+4*4))=0xb3f5f966;
*((unsigned int *)((unsigned long)context_ptr+0x00006338+4*5))=0x4bb2e51a;
*((unsigned int *)((unsigned long)context_ptr+0x00006338+4*6))=0x5cc704c5;
*((unsigned int *)((unsigned long)context_ptr+0x00006338+4*7))=0x82e78e54;
*((unsigned int *)((unsigned long)context_ptr+0x00006338+4*8))=0xc95e7539;
*((unsigned int *)((unsigned long)context_ptr+0x00006338+4*9))=0x8fee1d06;
*((unsigned int *)((unsigned long)context_ptr+0x00006338+4*10))=0xe917a0fe;
*((unsigned int *)((unsigned long)context_ptr+0x00006338+4*11))=0xde65ba3a;
*((unsigned int *)((unsigned long)context_ptr+0x00006338+4*12))=0xc1cf93d5;
*((unsigned int *)((unsigned long)context_ptr+0x00006338+4*13))=0xdcb5fca5;
*((unsigned int *)((unsigned long)context_ptr+0x00006338+4*14))=0xf8ddd4c8;
*((unsigned int *)((unsigned long)context_ptr+0x00006338+4*15))=0x410a51a5;
*((unsigned int *)((unsigned long)context_ptr+0x00006338+4*16))=0x4426c5cc;
*((unsigned int *)((unsigned long)context_ptr+0x00006338+4*17))=0x2e0c8825;
*((unsigned int *)((unsigned long)context_ptr+0x00006338+4*18))=0xc220fc46;
*((unsigned int *)((unsigned long)context_ptr+0x00006338+4*19))=0x94c103cd;
*((unsigned int *)((unsigned long)context_ptr+0x00006338+4*20))=0xca969215;
*((unsigned int *)((unsigned long)context_ptr+0x00006338+4*21))=0xb9fc5e89;
*((unsigned int *)((unsigned long)context_ptr+0x00006338+4*22))=0xcfffd330;
*((unsigned int *)((unsigned long)context_ptr+0x00006338+4*23))=0xeae85f76;
*((unsigned int *)((unsigned long)context_ptr+0x000038e8))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x000038e8+4*1))=0x000066a4;
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
*((unsigned int *)((unsigned long)context_ptr+0x000008e8+4*1))=0x00006338;
*((unsigned int *)((unsigned long)context_ptr+0x000008e8+4*2))=0x00006068;
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
if(!memcmp((unsigned char *)context_ptr+0x000064e4,"\x82\xbf\x9a\x30\x52\x80\x1a\xd1\xe7\x86\x96\xc7\xbc\xf2\xb6\x23\xe1\x3e\xc3\x64\x40\xdd\x57\xef\x51\xd1\x38\xb2\x32\x89\x57\xc1",32))
printf("strip: 82bf9a3052801ad1, Pass\n");
else
printf("strip: 82bf9a3052801ad1, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000066c4))=0x01ea1002;
*((unsigned int *)((unsigned long)context_ptr+0x000066c4+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000066c4+4*2))=0x02020061;
*((unsigned int *)((unsigned long)context_ptr+0x000066c4+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x000064a0))=0x0fecf66d;
*((unsigned int *)((unsigned long)context_ptr+0x000064a0+4*1))=0x6bae227c;
*((unsigned int *)((unsigned long)context_ptr+0x000064a0+4*2))=0xe3929afe;
*((unsigned int *)((unsigned long)context_ptr+0x000064a0+4*3))=0xd1c33f53;
*((unsigned int *)((unsigned long)context_ptr+0x000064a0+4*4))=0xb6e009ac;
*((unsigned int *)((unsigned long)context_ptr+0x000064a0+4*5))=0x0518ef4e;
*((unsigned int *)((unsigned long)context_ptr+0x000064a0+4*6))=0xe342d6cb;
*((unsigned int *)((unsigned long)context_ptr+0x000064a0+4*7))=0x1240ab85;
*((unsigned int *)((unsigned long)context_ptr+0x000064a0+4*8))=0xfda54339;
*((unsigned int *)((unsigned long)context_ptr+0x000064a0+4*9))=0x1a866486;
*((unsigned int *)((unsigned long)context_ptr+0x000064a0+4*10))=0xa4a4a8b6;
*((unsigned int *)((unsigned long)context_ptr+0x000064a0+4*11))=0x5671ea22;
*((unsigned int *)((unsigned long)context_ptr+0x000064a0+4*12))=0x13e45159;
*((unsigned int *)((unsigned long)context_ptr+0x000064a0+4*13))=0x8719428f;
*((unsigned int *)((unsigned long)context_ptr+0x000064a0+4*14))=0xeb5c598e;
*((unsigned int *)((unsigned long)context_ptr+0x000064a0+4*15))=0xaab1cd8c;
*((unsigned int *)((unsigned long)context_ptr+0x000064a0+4*16))=0x7774beef;
*((unsigned int *)((unsigned long)context_ptr+0x000064a0+4*17))=0xc3cbd8ca;
*((unsigned int *)((unsigned long)context_ptr+0x000064a0+4*18))=0x2f0f9b55;
*((unsigned int *)((unsigned long)context_ptr+0x000064a0+4*19))=0xb00ff824;
*((unsigned int *)((unsigned long)context_ptr+0x000064a0+4*20))=0xa63796d4;
*((unsigned int *)((unsigned long)context_ptr+0x000064a0+4*21))=0xea4c4ec1;
*((unsigned int *)((unsigned long)context_ptr+0x000064a0+4*22))=0x192c487d;
*((unsigned int *)((unsigned long)context_ptr+0x000064a0+4*23))=0xbd410842;
*((unsigned int *)((unsigned long)context_ptr+0x000064a0+4*24))=0x00000025;
*((unsigned int *)((unsigned long)context_ptr+0x00003900))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003900+4*1))=0x0000680c;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000900+4*1))=0x000064a0;
*((unsigned int *)((unsigned long)context_ptr+0x00000900+4*2))=0x000066c4;
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
if(!memcmp((unsigned char *)context_ptr+0x000065a8,"\xf7\x3a\x91\x39\x91\x28\xc6\x39\x9c\x33\x14\x5b\xcb\x5d\xbe\x85\x5f\x9d\x48\x88\x0c\xcf\xe2\xd9\x9d\xa9\xe7\x13\xcf\xa5\x13\x8b",32))
printf("strip: f73a91399128c639, Pass\n");
else
printf("strip: f73a91399128c639, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000065a4))=0x01ea1002;
*((unsigned int *)((unsigned long)context_ptr+0x000065a4+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000065a4+4*2))=0x02020062;
*((unsigned int *)((unsigned long)context_ptr+0x000065a4+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x00006398))=0x2cd6a219;
*((unsigned int *)((unsigned long)context_ptr+0x00006398+4*1))=0xac095dad;
*((unsigned int *)((unsigned long)context_ptr+0x00006398+4*2))=0x2d3ccb6d;
*((unsigned int *)((unsigned long)context_ptr+0x00006398+4*3))=0x92e1c258;
*((unsigned int *)((unsigned long)context_ptr+0x00006398+4*4))=0x06292d9c;
*((unsigned int *)((unsigned long)context_ptr+0x00006398+4*5))=0x32ddc73a;
*((unsigned int *)((unsigned long)context_ptr+0x00006398+4*6))=0x94cf6522;
*((unsigned int *)((unsigned long)context_ptr+0x00006398+4*7))=0x064112c8;
*((unsigned int *)((unsigned long)context_ptr+0x00006398+4*8))=0x1872fa77;
*((unsigned int *)((unsigned long)context_ptr+0x00006398+4*9))=0xfe14dc11;
*((unsigned int *)((unsigned long)context_ptr+0x00006398+4*10))=0x12743a1b;
*((unsigned int *)((unsigned long)context_ptr+0x00006398+4*11))=0x2847bfc2;
*((unsigned int *)((unsigned long)context_ptr+0x00006398+4*12))=0x0163b0f1;
*((unsigned int *)((unsigned long)context_ptr+0x00006398+4*13))=0x47867c36;
*((unsigned int *)((unsigned long)context_ptr+0x00006398+4*14))=0xa12632ef;
*((unsigned int *)((unsigned long)context_ptr+0x00006398+4*15))=0x77d9e94f;
*((unsigned int *)((unsigned long)context_ptr+0x00006398+4*16))=0x5c864c7d;
*((unsigned int *)((unsigned long)context_ptr+0x00006398+4*17))=0x751e88fb;
*((unsigned int *)((unsigned long)context_ptr+0x00006398+4*18))=0x854a816a;
*((unsigned int *)((unsigned long)context_ptr+0x00006398+4*19))=0xb34ed2a6;
*((unsigned int *)((unsigned long)context_ptr+0x00006398+4*20))=0x9230cb56;
*((unsigned int *)((unsigned long)context_ptr+0x00006398+4*21))=0x8f6beb39;
*((unsigned int *)((unsigned long)context_ptr+0x00006398+4*22))=0x3886af0b;
*((unsigned int *)((unsigned long)context_ptr+0x00006398+4*23))=0x9561326b;
*((unsigned int *)((unsigned long)context_ptr+0x00006398+4*24))=0x00008120;
*((unsigned int *)((unsigned long)context_ptr+0x00003918))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003918+4*1))=0x000063fc;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000918+4*1))=0x00006398;
*((unsigned int *)((unsigned long)context_ptr+0x00000918+4*2))=0x000065a4;
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
if(!memcmp((unsigned char *)context_ptr+0x000065c8,"\x60\xfa\xa5\xce\x81\xad\x06\x80\xfe\x87\x95\xbc\x2e\x8a\x9b\xee\xe3\x72\x95\xdf\xfb\x13\x55\x9e\x44\x73\x23\x38\x98\x0a\xd6\x2b",32))
printf("strip: 60faa5ce81ad0680, Pass\n");
else
printf("strip: 60faa5ce81ad0680, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x0000641c))=0x01ea1002;
*((unsigned int *)((unsigned long)context_ptr+0x0000641c+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x0000641c+4*2))=0x02020063;
*((unsigned int *)((unsigned long)context_ptr+0x0000641c+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x00006098))=0x8804feb8;
*((unsigned int *)((unsigned long)context_ptr+0x00006098+4*1))=0x9a661bf0;
*((unsigned int *)((unsigned long)context_ptr+0x00006098+4*2))=0x82665eb3;
*((unsigned int *)((unsigned long)context_ptr+0x00006098+4*3))=0xab2f5c0a;
*((unsigned int *)((unsigned long)context_ptr+0x00006098+4*4))=0xcc0145a9;
*((unsigned int *)((unsigned long)context_ptr+0x00006098+4*5))=0xdf00f908;
*((unsigned int *)((unsigned long)context_ptr+0x00006098+4*6))=0xf23e3287;
*((unsigned int *)((unsigned long)context_ptr+0x00006098+4*7))=0x58875e1c;
*((unsigned int *)((unsigned long)context_ptr+0x00006098+4*8))=0x51766149;
*((unsigned int *)((unsigned long)context_ptr+0x00006098+4*9))=0xeae0b620;
*((unsigned int *)((unsigned long)context_ptr+0x00006098+4*10))=0x00b7a0a9;
*((unsigned int *)((unsigned long)context_ptr+0x00006098+4*11))=0x2fc9a24d;
*((unsigned int *)((unsigned long)context_ptr+0x00006098+4*12))=0x89869a1f;
*((unsigned int *)((unsigned long)context_ptr+0x00006098+4*13))=0x3c1cd57b;
*((unsigned int *)((unsigned long)context_ptr+0x00006098+4*14))=0x6292d397;
*((unsigned int *)((unsigned long)context_ptr+0x00006098+4*15))=0xef365a59;
*((unsigned int *)((unsigned long)context_ptr+0x00006098+4*16))=0x675ae2c6;
*((unsigned int *)((unsigned long)context_ptr+0x00006098+4*17))=0xa2770536;
*((unsigned int *)((unsigned long)context_ptr+0x00006098+4*18))=0xc53ef9f3;
*((unsigned int *)((unsigned long)context_ptr+0x00006098+4*19))=0xe091282c;
*((unsigned int *)((unsigned long)context_ptr+0x00006098+4*20))=0x4fb19856;
*((unsigned int *)((unsigned long)context_ptr+0x00006098+4*21))=0x92a1940b;
*((unsigned int *)((unsigned long)context_ptr+0x00006098+4*22))=0x8e2682b8;
*((unsigned int *)((unsigned long)context_ptr+0x00006098+4*23))=0x699cb033;
*((unsigned int *)((unsigned long)context_ptr+0x00006098+4*24))=0x00fe50e1;
*((unsigned int *)((unsigned long)context_ptr+0x00003930))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003930+4*1))=0x0000682c;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000930+4*1))=0x00006098;
*((unsigned int *)((unsigned long)context_ptr+0x00000930+4*2))=0x0000641c;
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
if(!memcmp((unsigned char *)context_ptr+0x00006504,"\x5b\x82\x9b\x45\xe9\x2f\xe1\xab\xa0\x51\xb1\xdf\xb0\x22\x5e\x4d\x54\x15\x0d\xcb\x0c\x1e\x0a\xdd\x7e\x7c\xde\x59\x1a\xd5\xe6\x2f",32))
printf("strip: 5b829b45e92fe1ab, Pass\n");
else
printf("strip: 5b829b45e92fe1ab, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x0000684c))=0x01ea1002;
*((unsigned int *)((unsigned long)context_ptr+0x0000684c+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x0000684c+4*2))=0x02020064;
*((unsigned int *)((unsigned long)context_ptr+0x0000684c+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x000060fc))=0x57809741;
*((unsigned int *)((unsigned long)context_ptr+0x000060fc+4*1))=0x4726219e;
*((unsigned int *)((unsigned long)context_ptr+0x000060fc+4*2))=0xbe506bf3;
*((unsigned int *)((unsigned long)context_ptr+0x000060fc+4*3))=0xd0e827d7;
*((unsigned int *)((unsigned long)context_ptr+0x000060fc+4*4))=0xd67e325e;
*((unsigned int *)((unsigned long)context_ptr+0x000060fc+4*5))=0x9acb2b35;
*((unsigned int *)((unsigned long)context_ptr+0x000060fc+4*6))=0xf64f7eba;
*((unsigned int *)((unsigned long)context_ptr+0x000060fc+4*7))=0x0351aa3d;
*((unsigned int *)((unsigned long)context_ptr+0x000060fc+4*8))=0x83d2b685;
*((unsigned int *)((unsigned long)context_ptr+0x000060fc+4*9))=0x96945302;
*((unsigned int *)((unsigned long)context_ptr+0x000060fc+4*10))=0x2ab6f5ec;
*((unsigned int *)((unsigned long)context_ptr+0x000060fc+4*11))=0x12551fbd;
*((unsigned int *)((unsigned long)context_ptr+0x000060fc+4*12))=0x09b783cf;
*((unsigned int *)((unsigned long)context_ptr+0x000060fc+4*13))=0x287d342d;
*((unsigned int *)((unsigned long)context_ptr+0x000060fc+4*14))=0xf51b8f19;
*((unsigned int *)((unsigned long)context_ptr+0x000060fc+4*15))=0x4cc4fec6;
*((unsigned int *)((unsigned long)context_ptr+0x000060fc+4*16))=0x511f33cf;
*((unsigned int *)((unsigned long)context_ptr+0x000060fc+4*17))=0x11e31eb3;
*((unsigned int *)((unsigned long)context_ptr+0x000060fc+4*18))=0xc383b0c6;
*((unsigned int *)((unsigned long)context_ptr+0x000060fc+4*19))=0x4b26b18c;
*((unsigned int *)((unsigned long)context_ptr+0x000060fc+4*20))=0xbb96a18a;
*((unsigned int *)((unsigned long)context_ptr+0x000060fc+4*21))=0xf3f151b1;
*((unsigned int *)((unsigned long)context_ptr+0x000060fc+4*22))=0x1563754b;
*((unsigned int *)((unsigned long)context_ptr+0x000060fc+4*23))=0x873cd08c;
*((unsigned int *)((unsigned long)context_ptr+0x000060fc+4*24))=0x1a6b1c99;
*((unsigned int *)((unsigned long)context_ptr+0x00003948))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003948+4*1))=0x00006504;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000948+4*1))=0x000060fc;
*((unsigned int *)((unsigned long)context_ptr+0x00000948+4*2))=0x0000684c;
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
if(!memcmp((unsigned char *)context_ptr+0x00006524,"\x98\x6e\xcc\x05\x76\x7a\xc7\xb7\x16\x06\x4c\xa8\x9a\x5b\xb1\x39\x04\x3e\x48\xeb\xbc\x80\x78\xe1\x8e\xaa\x28\xa1\x57\x2e\xf8\xcc",32))
printf("strip: 986ecc05767ac7b7, Pass\n");
else
printf("strip: 986ecc05767ac7b7, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006524))=0x01ea1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006524+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006524+4*2))=0x02020065;
*((unsigned int *)((unsigned long)context_ptr+0x00006524+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x00006160))=0xa62710a4;
*((unsigned int *)((unsigned long)context_ptr+0x00006160+4*1))=0xe09408ae;
*((unsigned int *)((unsigned long)context_ptr+0x00006160+4*2))=0xa437a4a1;
*((unsigned int *)((unsigned long)context_ptr+0x00006160+4*3))=0xd13dd526;
*((unsigned int *)((unsigned long)context_ptr+0x00006160+4*4))=0x4d559806;
*((unsigned int *)((unsigned long)context_ptr+0x00006160+4*5))=0x2dfa3e9c;
*((unsigned int *)((unsigned long)context_ptr+0x00006160+4*6))=0xeb4fad8b;
*((unsigned int *)((unsigned long)context_ptr+0x00006160+4*7))=0x8f7037c7;
*((unsigned int *)((unsigned long)context_ptr+0x00006160+4*8))=0x4ebdc506;
*((unsigned int *)((unsigned long)context_ptr+0x00006160+4*9))=0xdd6f6aca;
*((unsigned int *)((unsigned long)context_ptr+0x00006160+4*10))=0x33bac74e;
*((unsigned int *)((unsigned long)context_ptr+0x00006160+4*11))=0x409c284b;
*((unsigned int *)((unsigned long)context_ptr+0x00006160+4*12))=0xc13e33ec;
*((unsigned int *)((unsigned long)context_ptr+0x00006160+4*13))=0xcb006e9b;
*((unsigned int *)((unsigned long)context_ptr+0x00006160+4*14))=0x30518855;
*((unsigned int *)((unsigned long)context_ptr+0x00006160+4*15))=0xd3b77fe4;
*((unsigned int *)((unsigned long)context_ptr+0x00006160+4*16))=0x0c17a467;
*((unsigned int *)((unsigned long)context_ptr+0x00006160+4*17))=0xf6f1fb9a;
*((unsigned int *)((unsigned long)context_ptr+0x00006160+4*18))=0x9db77395;
*((unsigned int *)((unsigned long)context_ptr+0x00006160+4*19))=0x4eabe8dc;
*((unsigned int *)((unsigned long)context_ptr+0x00006160+4*20))=0x14babd7f;
*((unsigned int *)((unsigned long)context_ptr+0x00006160+4*21))=0x6b32350b;
*((unsigned int *)((unsigned long)context_ptr+0x00006160+4*22))=0x214db00c;
*((unsigned int *)((unsigned long)context_ptr+0x00006160+4*23))=0xf2a1cab3;
*((unsigned int *)((unsigned long)context_ptr+0x00006160+4*24))=0x58ba54c5;
*((unsigned int *)((unsigned long)context_ptr+0x00006160+4*25))=0x000000f9;
*((unsigned int *)((unsigned long)context_ptr+0x00003960))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003960+4*1))=0x0000642c;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000960+4*1))=0x00006160;
*((unsigned int *)((unsigned long)context_ptr+0x00000960+4*2))=0x00006524;
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
if(!memcmp((unsigned char *)context_ptr+0x000065e8,"\x73\x2b\x60\x2f\x8f\xd4\x11\x07\x0d\xa2\xfe\x86\x64\xa1\x38\x61\x7e\x2c\xab\xe5\x9a\xdf\xcc\x76\xe0\x13\xc6\xce\x82\xdf\x5f\x27",32))
printf("strip: 732b602f8fd41107, Pass\n");
else
printf("strip: 732b602f8fd41107, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006534))=0x01ea1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006534+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006534+4*2))=0x02020066;
*((unsigned int *)((unsigned long)context_ptr+0x00006534+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x000061c8))=0x953c964d;
*((unsigned int *)((unsigned long)context_ptr+0x000061c8+4*1))=0xc4f6e664;
*((unsigned int *)((unsigned long)context_ptr+0x000061c8+4*2))=0x1bfac9d1;
*((unsigned int *)((unsigned long)context_ptr+0x000061c8+4*3))=0xdf82e8ca;
*((unsigned int *)((unsigned long)context_ptr+0x000061c8+4*4))=0x7bcd07cc;
*((unsigned int *)((unsigned long)context_ptr+0x000061c8+4*5))=0x9798559b;
*((unsigned int *)((unsigned long)context_ptr+0x000061c8+4*6))=0xa92e8025;
*((unsigned int *)((unsigned long)context_ptr+0x000061c8+4*7))=0xf5975b0d;
*((unsigned int *)((unsigned long)context_ptr+0x000061c8+4*8))=0x50652719;
*((unsigned int *)((unsigned long)context_ptr+0x000061c8+4*9))=0xab21d3b5;
*((unsigned int *)((unsigned long)context_ptr+0x000061c8+4*10))=0x4457e9cb;
*((unsigned int *)((unsigned long)context_ptr+0x000061c8+4*11))=0xb29066bf;
*((unsigned int *)((unsigned long)context_ptr+0x000061c8+4*12))=0xbbeebf4d;
*((unsigned int *)((unsigned long)context_ptr+0x000061c8+4*13))=0x91ef7953;
*((unsigned int *)((unsigned long)context_ptr+0x000061c8+4*14))=0xe85c801c;
*((unsigned int *)((unsigned long)context_ptr+0x000061c8+4*15))=0xed092f8d;
*((unsigned int *)((unsigned long)context_ptr+0x000061c8+4*16))=0x5d68a727;
*((unsigned int *)((unsigned long)context_ptr+0x000061c8+4*17))=0x492f6eb8;
*((unsigned int *)((unsigned long)context_ptr+0x000061c8+4*18))=0x73d19563;
*((unsigned int *)((unsigned long)context_ptr+0x000061c8+4*19))=0xcc6156f1;
*((unsigned int *)((unsigned long)context_ptr+0x000061c8+4*20))=0xa590ff5e;
*((unsigned int *)((unsigned long)context_ptr+0x000061c8+4*21))=0x59b05688;
*((unsigned int *)((unsigned long)context_ptr+0x000061c8+4*22))=0xa45a2316;
*((unsigned int *)((unsigned long)context_ptr+0x000061c8+4*23))=0xb2225746;
*((unsigned int *)((unsigned long)context_ptr+0x000061c8+4*24))=0xdc47ff0a;
*((unsigned int *)((unsigned long)context_ptr+0x000061c8+4*25))=0x00009db1;
*((unsigned int *)((unsigned long)context_ptr+0x00003978))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003978+4*1))=0x000065b4;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000978+4*1))=0x000061c8;
*((unsigned int *)((unsigned long)context_ptr+0x00000978+4*2))=0x00006534;
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
if(!memcmp((unsigned char *)context_ptr+0x00006608,"\xe0\xfe\x47\xbe\xea\xa1\x52\xf2\xcc\xff\x37\xec\x0f\x19\x22\x41\xb1\x89\x38\x17\x1e\x7d\xef\x64\x68\x57\x95\xdc\xf3\x44\x6b\x63",32))
printf("strip: e0fe47beeaa152f2, Pass\n");
else
printf("strip: e0fe47beeaa152f2, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006544))=0x01ea1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006544+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006544+4*2))=0x02020067;
*((unsigned int *)((unsigned long)context_ptr+0x00006544+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x00006230))=0xe567adfd;
*((unsigned int *)((unsigned long)context_ptr+0x00006230+4*1))=0x56783947;
*((unsigned int *)((unsigned long)context_ptr+0x00006230+4*2))=0x93f05fe7;
*((unsigned int *)((unsigned long)context_ptr+0x00006230+4*3))=0xa0196a0f;
*((unsigned int *)((unsigned long)context_ptr+0x00006230+4*4))=0x28999185;
*((unsigned int *)((unsigned long)context_ptr+0x00006230+4*5))=0xe3138470;
*((unsigned int *)((unsigned long)context_ptr+0x00006230+4*6))=0x88ffe858;
*((unsigned int *)((unsigned long)context_ptr+0x00006230+4*7))=0xc47a53ab;
*((unsigned int *)((unsigned long)context_ptr+0x00006230+4*8))=0xa45ca6ef;
*((unsigned int *)((unsigned long)context_ptr+0x00006230+4*9))=0xaf887086;
*((unsigned int *)((unsigned long)context_ptr+0x00006230+4*10))=0x3a816526;
*((unsigned int *)((unsigned long)context_ptr+0x00006230+4*11))=0x9e918587;
*((unsigned int *)((unsigned long)context_ptr+0x00006230+4*12))=0x7d36bd50;
*((unsigned int *)((unsigned long)context_ptr+0x00006230+4*13))=0xf74a42e3;
*((unsigned int *)((unsigned long)context_ptr+0x00006230+4*14))=0x85550fd9;
*((unsigned int *)((unsigned long)context_ptr+0x00006230+4*15))=0xa961ae3d;
*((unsigned int *)((unsigned long)context_ptr+0x00006230+4*16))=0x59e90d91;
*((unsigned int *)((unsigned long)context_ptr+0x00006230+4*17))=0x08ebea00;
*((unsigned int *)((unsigned long)context_ptr+0x00006230+4*18))=0x34073ef3;
*((unsigned int *)((unsigned long)context_ptr+0x00006230+4*19))=0xf097511e;
*((unsigned int *)((unsigned long)context_ptr+0x00006230+4*20))=0x68b70563;
*((unsigned int *)((unsigned long)context_ptr+0x00006230+4*21))=0x35def350;
*((unsigned int *)((unsigned long)context_ptr+0x00006230+4*22))=0x9ccf1f36;
*((unsigned int *)((unsigned long)context_ptr+0x00006230+4*23))=0x784cc6ac;
*((unsigned int *)((unsigned long)context_ptr+0x00006230+4*24))=0x5e3e5210;
*((unsigned int *)((unsigned long)context_ptr+0x00006230+4*25))=0x00063d38;
*((unsigned int *)((unsigned long)context_ptr+0x00003990))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003990+4*1))=0x000065d4;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000990+4*1))=0x00006230;
*((unsigned int *)((unsigned long)context_ptr+0x00000990+4*2))=0x00006544;
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
if(!memcmp((unsigned char *)context_ptr+0x000062f8,"\xf7\x0a\x3a\xd4\x03\x93\x0f\x9b\x63\x30\xa5\x3f\x98\x59\xbd\x64\xee\x21\x5f\x5c\x14\x8b\x09\x1a\xae\xc0\xbc\x5d\x22\x8d\x85\xc1",32))
printf("strip: f70a3ad403930f9b, Pass\n");
else
printf("strip: f70a3ad403930f9b, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006554))=0x01ea1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006554+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006554+4*2))=0x02020068;
*((unsigned int *)((unsigned long)context_ptr+0x00006554+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x00006298))=0xc2ebff0c;
*((unsigned int *)((unsigned long)context_ptr+0x00006298+4*1))=0xf3bb5c45;
*((unsigned int *)((unsigned long)context_ptr+0x00006298+4*2))=0xb17dd974;
*((unsigned int *)((unsigned long)context_ptr+0x00006298+4*3))=0xc4afbde7;
*((unsigned int *)((unsigned long)context_ptr+0x00006298+4*4))=0x809414d9;
*((unsigned int *)((unsigned long)context_ptr+0x00006298+4*5))=0x98522da7;
*((unsigned int *)((unsigned long)context_ptr+0x00006298+4*6))=0x66153cc5;
*((unsigned int *)((unsigned long)context_ptr+0x00006298+4*7))=0x03486f86;
*((unsigned int *)((unsigned long)context_ptr+0x00006298+4*8))=0xb00bb6b0;
*((unsigned int *)((unsigned long)context_ptr+0x00006298+4*9))=0xbfcc1a3d;
*((unsigned int *)((unsigned long)context_ptr+0x00006298+4*10))=0x2563798b;
*((unsigned int *)((unsigned long)context_ptr+0x00006298+4*11))=0x1f15154c;
*((unsigned int *)((unsigned long)context_ptr+0x00006298+4*12))=0x8fec192e;
*((unsigned int *)((unsigned long)context_ptr+0x00006298+4*13))=0x3b82fe58;
*((unsigned int *)((unsigned long)context_ptr+0x00006298+4*14))=0xd1e0cc87;
*((unsigned int *)((unsigned long)context_ptr+0x00006298+4*15))=0xbcb72757;
*((unsigned int *)((unsigned long)context_ptr+0x00006298+4*16))=0x7fa0aa98;
*((unsigned int *)((unsigned long)context_ptr+0x00006298+4*17))=0x3452fa28;
*((unsigned int *)((unsigned long)context_ptr+0x00006298+4*18))=0x551512ac;
*((unsigned int *)((unsigned long)context_ptr+0x00006298+4*19))=0x3f3d63f4;
*((unsigned int *)((unsigned long)context_ptr+0x00006298+4*20))=0x019d0e6f;
*((unsigned int *)((unsigned long)context_ptr+0x00006298+4*21))=0x6cff9417;
*((unsigned int *)((unsigned long)context_ptr+0x00006298+4*22))=0xf3acf373;
*((unsigned int *)((unsigned long)context_ptr+0x00006298+4*23))=0x47906f27;
*((unsigned int *)((unsigned long)context_ptr+0x00006298+4*24))=0xa17ac71b;
*((unsigned int *)((unsigned long)context_ptr+0x00006298+4*25))=0xf6e7071a;
*((unsigned int *)((unsigned long)context_ptr+0x000039a8))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x000039a8+4*1))=0x000065f4;
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
*((unsigned int *)((unsigned long)context_ptr+0x000009a8+4*1))=0x00006298;
*((unsigned int *)((unsigned long)context_ptr+0x000009a8+4*2))=0x00006554;
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
if(!memcmp((unsigned char *)context_ptr+0x00006318,"\xec\x0c\x54\xef\x9d\xcd\xea\x32\xcd\xb5\xcd\x45\xd2\x97\x89\x44\x5b\x82\x61\xd3\x28\x35\x96\x93\xa0\xc0\x8a\xf5\x4d\x4e\x20\xc1",32))
printf("strip: ec0c54ef9dcdea32, Pass\n");
else
printf("strip: ec0c54ef9dcdea32, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006614))=0x01ea1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006614+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006614+4*2))=0x02020069;
*((unsigned int *)((unsigned long)context_ptr+0x00006614+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x00006974))=0x0f8821f7;
*((unsigned int *)((unsigned long)context_ptr+0x00006974+4*1))=0x3c28d744;
*((unsigned int *)((unsigned long)context_ptr+0x00006974+4*2))=0x223fd1ec;
*((unsigned int *)((unsigned long)context_ptr+0x00006974+4*3))=0xbc5458ea;
*((unsigned int *)((unsigned long)context_ptr+0x00006974+4*4))=0xe63cc87c;
*((unsigned int *)((unsigned long)context_ptr+0x00006974+4*5))=0x03352b82;
*((unsigned int *)((unsigned long)context_ptr+0x00006974+4*6))=0xe20fd5aa;
*((unsigned int *)((unsigned long)context_ptr+0x00006974+4*7))=0xbb30bec6;
*((unsigned int *)((unsigned long)context_ptr+0x00006974+4*8))=0xd5e44f5e;
*((unsigned int *)((unsigned long)context_ptr+0x00006974+4*9))=0x3b83e703;
*((unsigned int *)((unsigned long)context_ptr+0x00006974+4*10))=0x00e3c966;
*((unsigned int *)((unsigned long)context_ptr+0x00006974+4*11))=0x8a2be094;
*((unsigned int *)((unsigned long)context_ptr+0x00006974+4*12))=0x13bbdc2a;
*((unsigned int *)((unsigned long)context_ptr+0x00006974+4*13))=0xd3cea7f4;
*((unsigned int *)((unsigned long)context_ptr+0x00006974+4*14))=0x39e12861;
*((unsigned int *)((unsigned long)context_ptr+0x00006974+4*15))=0x5feb27e5;
*((unsigned int *)((unsigned long)context_ptr+0x00006974+4*16))=0x0a0dbe79;
*((unsigned int *)((unsigned long)context_ptr+0x00006974+4*17))=0x05aa128f;
*((unsigned int *)((unsigned long)context_ptr+0x00006974+4*18))=0x98b86e1c;
*((unsigned int *)((unsigned long)context_ptr+0x00006974+4*19))=0x2ab5d46b;
*((unsigned int *)((unsigned long)context_ptr+0x00006974+4*20))=0xe6751116;
*((unsigned int *)((unsigned long)context_ptr+0x00006974+4*21))=0x0c5f65d9;
*((unsigned int *)((unsigned long)context_ptr+0x00006974+4*22))=0xcb3be340;
*((unsigned int *)((unsigned long)context_ptr+0x00006974+4*23))=0x0df89183;
*((unsigned int *)((unsigned long)context_ptr+0x00006974+4*24))=0xfff06e05;
*((unsigned int *)((unsigned long)context_ptr+0x00006974+4*25))=0x4653cc64;
*((unsigned int *)((unsigned long)context_ptr+0x00006974+4*26))=0x000000fb;
*((unsigned int *)((unsigned long)context_ptr+0x000039c0))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x000039c0+4*1))=0x0000644c;
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
*((unsigned int *)((unsigned long)context_ptr+0x000009c0+4*1))=0x00006974;
*((unsigned int *)((unsigned long)context_ptr+0x000009c0+4*2))=0x00006614;
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
if(!memcmp((unsigned char *)context_ptr+0x00006564,"\xe3\x17\x3a\x54\xb3\x7f\x81\xdf\xd2\x84\xa4\x18\x9f\x1c\xb8\x5f\xfe\x03\xa7\x5b\x89\x77\x4f\x1f\x75\xa5\x2b\xe2\x32\x31\x00\x52",32))
printf("strip: e3173a54b37f81df, Pass\n");
else
printf("strip: e3173a54b37f81df, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x0000646c))=0x01ea1002;
*((unsigned int *)((unsigned long)context_ptr+0x0000646c+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x0000646c+4*2))=0x0202006a;
*((unsigned int *)((unsigned long)context_ptr+0x0000646c+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x0000685c))=0x39df63e7;
*((unsigned int *)((unsigned long)context_ptr+0x0000685c+4*1))=0x1806fb9f;
*((unsigned int *)((unsigned long)context_ptr+0x0000685c+4*2))=0x8fec395e;
*((unsigned int *)((unsigned long)context_ptr+0x0000685c+4*3))=0xa6132433;
*((unsigned int *)((unsigned long)context_ptr+0x0000685c+4*4))=0x6ac70adc;
*((unsigned int *)((unsigned long)context_ptr+0x0000685c+4*5))=0xbacb2f08;
*((unsigned int *)((unsigned long)context_ptr+0x0000685c+4*6))=0x52bfb066;
*((unsigned int *)((unsigned long)context_ptr+0x0000685c+4*7))=0xb9d9f37f;
*((unsigned int *)((unsigned long)context_ptr+0x0000685c+4*8))=0x31c47899;
*((unsigned int *)((unsigned long)context_ptr+0x0000685c+4*9))=0x0f06b14a;
*((unsigned int *)((unsigned long)context_ptr+0x0000685c+4*10))=0xabb63cc9;
*((unsigned int *)((unsigned long)context_ptr+0x0000685c+4*11))=0x01c3dc01;
*((unsigned int *)((unsigned long)context_ptr+0x0000685c+4*12))=0x73e5dc05;
*((unsigned int *)((unsigned long)context_ptr+0x0000685c+4*13))=0xb06f2c27;
*((unsigned int *)((unsigned long)context_ptr+0x0000685c+4*14))=0xc310c08e;
*((unsigned int *)((unsigned long)context_ptr+0x0000685c+4*15))=0x47d2ce45;
*((unsigned int *)((unsigned long)context_ptr+0x0000685c+4*16))=0xc9f501d3;
*((unsigned int *)((unsigned long)context_ptr+0x0000685c+4*17))=0x65c6d483;
*((unsigned int *)((unsigned long)context_ptr+0x0000685c+4*18))=0xd922a088;
*((unsigned int *)((unsigned long)context_ptr+0x0000685c+4*19))=0xfced0d0e;
*((unsigned int *)((unsigned long)context_ptr+0x0000685c+4*20))=0xff01479f;
*((unsigned int *)((unsigned long)context_ptr+0x0000685c+4*21))=0x2284a32e;
*((unsigned int *)((unsigned long)context_ptr+0x0000685c+4*22))=0xbf854af4;
*((unsigned int *)((unsigned long)context_ptr+0x0000685c+4*23))=0x8b7acaf0;
*((unsigned int *)((unsigned long)context_ptr+0x0000685c+4*24))=0x59437a74;
*((unsigned int *)((unsigned long)context_ptr+0x0000685c+4*25))=0x4fd15b42;
*((unsigned int *)((unsigned long)context_ptr+0x0000685c+4*26))=0x00003c47;
*((unsigned int *)((unsigned long)context_ptr+0x000039d8))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x000039d8+4*1))=0x00006564;
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
*((unsigned int *)((unsigned long)context_ptr+0x000009d8+4*1))=0x0000685c;
*((unsigned int *)((unsigned long)context_ptr+0x000009d8+4*2))=0x0000646c;
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
if(!memcmp((unsigned char *)context_ptr+0x00006480,"\xf2\x34\x08\x3c\x41\x86\x69\x75\xd9\x6a\x67\xa9\x21\x67\xf0\xd4\x0d\xc5\xfc\xb8\x5e\x4f\xab\x53\x36\x9d\x93\x37\xcf\x60\xf5\x81",32))
printf("strip: f234083c41866975, Pass\n");
else
printf("strip: f234083c41866975, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006078))=0x01ea1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006078+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006078+4*2))=0x0202006b;
*((unsigned int *)((unsigned long)context_ptr+0x00006078+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x000069e0))=0x993ca260;
*((unsigned int *)((unsigned long)context_ptr+0x000069e0+4*1))=0x8c94a455;
*((unsigned int *)((unsigned long)context_ptr+0x000069e0+4*2))=0x2859dc1e;
*((unsigned int *)((unsigned long)context_ptr+0x000069e0+4*3))=0x7337d8c2;
*((unsigned int *)((unsigned long)context_ptr+0x000069e0+4*4))=0xa7655795;
*((unsigned int *)((unsigned long)context_ptr+0x000069e0+4*5))=0x05e0a0ef;
*((unsigned int *)((unsigned long)context_ptr+0x000069e0+4*6))=0x72de848a;
*((unsigned int *)((unsigned long)context_ptr+0x000069e0+4*7))=0x5e7abdc0;
*((unsigned int *)((unsigned long)context_ptr+0x000069e0+4*8))=0xe0816722;
*((unsigned int *)((unsigned long)context_ptr+0x000069e0+4*9))=0x2f1049bd;
*((unsigned int *)((unsigned long)context_ptr+0x000069e0+4*10))=0xc7d129c1;
*((unsigned int *)((unsigned long)context_ptr+0x000069e0+4*11))=0x8274542d;
*((unsigned int *)((unsigned long)context_ptr+0x000069e0+4*12))=0x1b1e16c4;
*((unsigned int *)((unsigned long)context_ptr+0x000069e0+4*13))=0xcf1b67b4;
*((unsigned int *)((unsigned long)context_ptr+0x000069e0+4*14))=0x35d1d21f;
*((unsigned int *)((unsigned long)context_ptr+0x000069e0+4*15))=0xca525d9b;
*((unsigned int *)((unsigned long)context_ptr+0x000069e0+4*16))=0x5e91474c;
*((unsigned int *)((unsigned long)context_ptr+0x000069e0+4*17))=0xedaebd92;
*((unsigned int *)((unsigned long)context_ptr+0x000069e0+4*18))=0xe8f3810c;
*((unsigned int *)((unsigned long)context_ptr+0x000069e0+4*19))=0x8c542f83;
*((unsigned int *)((unsigned long)context_ptr+0x000069e0+4*20))=0xd4d251bc;
*((unsigned int *)((unsigned long)context_ptr+0x000069e0+4*21))=0xf58aa1f8;
*((unsigned int *)((unsigned long)context_ptr+0x000069e0+4*22))=0xf96528e3;
*((unsigned int *)((unsigned long)context_ptr+0x000069e0+4*23))=0xb0884118;
*((unsigned int *)((unsigned long)context_ptr+0x000069e0+4*24))=0x31e55685;
*((unsigned int *)((unsigned long)context_ptr+0x000069e0+4*25))=0xc7ec0c3f;
*((unsigned int *)((unsigned long)context_ptr+0x000069e0+4*26))=0x008f5542;
*((unsigned int *)((unsigned long)context_ptr+0x000039f0))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x000039f0+4*1))=0x0000647c;
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
*((unsigned int *)((unsigned long)context_ptr+0x000009f0+4*1))=0x000069e0;
*((unsigned int *)((unsigned long)context_ptr+0x000009f0+4*2))=0x00006078;
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
if(!memcmp((unsigned char *)context_ptr+0x00006584,"\x4a\x09\x4c\x60\xfe\x68\xc3\x21\xa2\x4d\x1a\x0b\x2c\xf0\x89\xd4\x7b\x25\x71\xc8\x99\xe6\x9c\xf2\xcd\x58\xf8\xe9\x73\x35\xe6\x49",32))
printf("strip: 4a094c60fe68c321, Pass\n");
else
printf("strip: 4a094c60fe68c321, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006088))=0x01ea1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006088+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006088+4*2))=0x0202006c;
*((unsigned int *)((unsigned long)context_ptr+0x00006088+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x000066d4))=0x0e6d0441;
*((unsigned int *)((unsigned long)context_ptr+0x000066d4+4*1))=0xfbe2799a;
*((unsigned int *)((unsigned long)context_ptr+0x000066d4+4*2))=0xac176e20;
*((unsigned int *)((unsigned long)context_ptr+0x000066d4+4*3))=0xdc26f88c;
*((unsigned int *)((unsigned long)context_ptr+0x000066d4+4*4))=0x71c65d7b;
*((unsigned int *)((unsigned long)context_ptr+0x000066d4+4*5))=0x76f7f69b;
*((unsigned int *)((unsigned long)context_ptr+0x000066d4+4*6))=0x3b946332;
*((unsigned int *)((unsigned long)context_ptr+0x000066d4+4*7))=0xee461c0a;
*((unsigned int *)((unsigned long)context_ptr+0x000066d4+4*8))=0x7ba1fbfe;
*((unsigned int *)((unsigned long)context_ptr+0x000066d4+4*9))=0x4c8f9bce;
*((unsigned int *)((unsigned long)context_ptr+0x000066d4+4*10))=0xc8fefcf4;
*((unsigned int *)((unsigned long)context_ptr+0x000066d4+4*11))=0xbe668afd;
*((unsigned int *)((unsigned long)context_ptr+0x000066d4+4*12))=0x86bb680a;
*((unsigned int *)((unsigned long)context_ptr+0x000066d4+4*13))=0x1fdf8107;
*((unsigned int *)((unsigned long)context_ptr+0x000066d4+4*14))=0xc5995c3a;
*((unsigned int *)((unsigned long)context_ptr+0x000066d4+4*15))=0xb5011898;
*((unsigned int *)((unsigned long)context_ptr+0x000066d4+4*16))=0x2b846429;
*((unsigned int *)((unsigned long)context_ptr+0x000066d4+4*17))=0x14778fb3;
*((unsigned int *)((unsigned long)context_ptr+0x000066d4+4*18))=0x00e07d7a;
*((unsigned int *)((unsigned long)context_ptr+0x000066d4+4*19))=0x232040bc;
*((unsigned int *)((unsigned long)context_ptr+0x000066d4+4*20))=0x4977132c;
*((unsigned int *)((unsigned long)context_ptr+0x000066d4+4*21))=0x91baa04f;
*((unsigned int *)((unsigned long)context_ptr+0x000066d4+4*22))=0xfed21933;
*((unsigned int *)((unsigned long)context_ptr+0x000066d4+4*23))=0x1510973c;
*((unsigned int *)((unsigned long)context_ptr+0x000066d4+4*24))=0x62bcbe1a;
*((unsigned int *)((unsigned long)context_ptr+0x000066d4+4*25))=0x65c529fc;
*((unsigned int *)((unsigned long)context_ptr+0x000066d4+4*26))=0x8d3704be;
*((unsigned int *)((unsigned long)context_ptr+0x00003a08))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003a08+4*1))=0x00006584;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000a08+4*1))=0x000066d4;
*((unsigned int *)((unsigned long)context_ptr+0x00000a08+4*2))=0x00006088;
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
if(!memcmp((unsigned char *)context_ptr+0x000067ec,"\x66\x18\x3b\x7a\x78\x99\xaf\x3f\xfb\x86\x20\x7d\x53\xed\xd2\x68\x84\xf7\x12\x14\xc8\x1f\xfa\xe7\xdd\x2c\x02\x57\x06\x7a\x04\x6c",32))
printf("strip: 66183b7a7899af3f, Pass\n");
else
printf("strip: 66183b7a7899af3f, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006058))=0x01ea1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*2))=0x0202006d;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x00006740))=0xe6dcad3a;
*((unsigned int *)((unsigned long)context_ptr+0x00006740+4*1))=0x5db2be0c;
*((unsigned int *)((unsigned long)context_ptr+0x00006740+4*2))=0xe1332b9a;
*((unsigned int *)((unsigned long)context_ptr+0x00006740+4*3))=0xb9afbc42;
*((unsigned int *)((unsigned long)context_ptr+0x00006740+4*4))=0x980e8a47;
*((unsigned int *)((unsigned long)context_ptr+0x00006740+4*5))=0x32b6f31d;
*((unsigned int *)((unsigned long)context_ptr+0x00006740+4*6))=0x9a10747f;
*((unsigned int *)((unsigned long)context_ptr+0x00006740+4*7))=0x22155732;
*((unsigned int *)((unsigned long)context_ptr+0x00006740+4*8))=0xaf0375a7;
*((unsigned int *)((unsigned long)context_ptr+0x00006740+4*9))=0x80c037bd;
*((unsigned int *)((unsigned long)context_ptr+0x00006740+4*10))=0x2eb81a37;
*((unsigned int *)((unsigned long)context_ptr+0x00006740+4*11))=0xe09bdeb3;
*((unsigned int *)((unsigned long)context_ptr+0x00006740+4*12))=0xfd9cd956;
*((unsigned int *)((unsigned long)context_ptr+0x00006740+4*13))=0xb36ba076;
*((unsigned int *)((unsigned long)context_ptr+0x00006740+4*14))=0x05d91b31;
*((unsigned int *)((unsigned long)context_ptr+0x00006740+4*15))=0x2a92eb59;
*((unsigned int *)((unsigned long)context_ptr+0x00006740+4*16))=0x9d73e272;
*((unsigned int *)((unsigned long)context_ptr+0x00006740+4*17))=0x47b1d068;
*((unsigned int *)((unsigned long)context_ptr+0x00006740+4*18))=0x9254934b;
*((unsigned int *)((unsigned long)context_ptr+0x00006740+4*19))=0x82dff9c3;
*((unsigned int *)((unsigned long)context_ptr+0x00006740+4*20))=0x5a6e3058;
*((unsigned int *)((unsigned long)context_ptr+0x00006740+4*21))=0xe0d2b147;
*((unsigned int *)((unsigned long)context_ptr+0x00006740+4*22))=0x7334e5f9;
*((unsigned int *)((unsigned long)context_ptr+0x00006740+4*23))=0x349587fa;
*((unsigned int *)((unsigned long)context_ptr+0x00006740+4*24))=0x4f0e5093;
*((unsigned int *)((unsigned long)context_ptr+0x00006740+4*25))=0x80aadcf4;
*((unsigned int *)((unsigned long)context_ptr+0x00006740+4*26))=0x77415bc3;
*((unsigned int *)((unsigned long)context_ptr+0x00006740+4*27))=0x0000007a;
*((unsigned int *)((unsigned long)context_ptr+0x00003a20))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003a20+4*1))=0x00006300;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000a20+4*1))=0x00006740;
*((unsigned int *)((unsigned long)context_ptr+0x00000a20+4*2))=0x00006058;
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
if(!memcmp((unsigned char *)context_ptr+0x00006684,"\xfe\xe4\x49\x4d\x9b\x7e\x99\xeb\xd2\x61\x5b\x5b\xc6\x71\x58\xab\x59\xa8\xf3\x0e\x25\xb3\x49\xb3\x3b\xeb\xd2\x63\xbe\x3c\xd3\xf5",32))
printf("strip: fee4494d9b7e99eb, Pass\n");
else
printf("strip: fee4494d9b7e99eb, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006048))=0x01ea1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006048+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006048+4*2))=0x0202006e;
*((unsigned int *)((unsigned long)context_ptr+0x00006048+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x00006624))=0x4105aa35;
*((unsigned int *)((unsigned long)context_ptr+0x00006624+4*1))=0x6ef4b2db;
*((unsigned int *)((unsigned long)context_ptr+0x00006624+4*2))=0xe4cebf1f;
*((unsigned int *)((unsigned long)context_ptr+0x00006624+4*3))=0x770019af;
*((unsigned int *)((unsigned long)context_ptr+0x00006624+4*4))=0xee1f29c8;
*((unsigned int *)((unsigned long)context_ptr+0x00006624+4*5))=0xe7716dbd;
*((unsigned int *)((unsigned long)context_ptr+0x00006624+4*6))=0x9b8f08be;
*((unsigned int *)((unsigned long)context_ptr+0x00006624+4*7))=0x9093b34d;
*((unsigned int *)((unsigned long)context_ptr+0x00006624+4*8))=0x054e62ae;
*((unsigned int *)((unsigned long)context_ptr+0x00006624+4*9))=0x42cddbb8;
*((unsigned int *)((unsigned long)context_ptr+0x00006624+4*10))=0xa54ceabd;
*((unsigned int *)((unsigned long)context_ptr+0x00006624+4*11))=0xc24728bf;
*((unsigned int *)((unsigned long)context_ptr+0x00006624+4*12))=0x290c2ea2;
*((unsigned int *)((unsigned long)context_ptr+0x00006624+4*13))=0xd052be32;
*((unsigned int *)((unsigned long)context_ptr+0x00006624+4*14))=0x03dd4042;
*((unsigned int *)((unsigned long)context_ptr+0x00006624+4*15))=0xac7cea4b;
*((unsigned int *)((unsigned long)context_ptr+0x00006624+4*16))=0xa3baf79a;
*((unsigned int *)((unsigned long)context_ptr+0x00006624+4*17))=0x4d9a034d;
*((unsigned int *)((unsigned long)context_ptr+0x00006624+4*18))=0xc1c0d6c2;
*((unsigned int *)((unsigned long)context_ptr+0x00006624+4*19))=0xeb77a6f3;
*((unsigned int *)((unsigned long)context_ptr+0x00006624+4*20))=0x25234784;
*((unsigned int *)((unsigned long)context_ptr+0x00006624+4*21))=0x962b2d19;
*((unsigned int *)((unsigned long)context_ptr+0x00006624+4*22))=0xa043f804;
*((unsigned int *)((unsigned long)context_ptr+0x00006624+4*23))=0xa7ee83f0;
*((unsigned int *)((unsigned long)context_ptr+0x00006624+4*24))=0x4133fcad;
*((unsigned int *)((unsigned long)context_ptr+0x00006624+4*25))=0x33189192;
*((unsigned int *)((unsigned long)context_ptr+0x00006624+4*26))=0xff19855d;
*((unsigned int *)((unsigned long)context_ptr+0x00006624+4*27))=0x0000cbf1;
*((unsigned int *)((unsigned long)context_ptr+0x00003a38))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003a38+4*1))=0x000067b0;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000a38+4*1))=0x00006624;
*((unsigned int *)((unsigned long)context_ptr+0x00000a38+4*2))=0x00006048;
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
if(!memcmp((unsigned char *)context_ptr+0x000066a4,"\xe6\xa0\x3d\x0a\xb1\x6e\x5e\x41\xc7\x2f\x31\xa1\x5f\xf2\x2f\x87\x3c\xc9\x84\x23\x3e\xb9\x7a\x7c\xbb\x7e\x40\x5f\xe0\xbc\x13\x10",32))
printf("strip: e6a03d0ab16e5e41, Pass\n");
else
printf("strip: e6a03d0ab16e5e41, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006068))=0x01ea1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006068+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006068+4*2))=0x0202006f;
*((unsigned int *)((unsigned long)context_ptr+0x00006068+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x00006320))=0x37238fa9;
*((unsigned int *)((unsigned long)context_ptr+0x00006320+4*1))=0xead897fb;
*((unsigned int *)((unsigned long)context_ptr+0x00006320+4*2))=0xad51787c;
*((unsigned int *)((unsigned long)context_ptr+0x00006320+4*3))=0xa41cd3f1;
*((unsigned int *)((unsigned long)context_ptr+0x00006320+4*4))=0xfa197161;
*((unsigned int *)((unsigned long)context_ptr+0x00006320+4*5))=0xd4c56373;
*((unsigned int *)((unsigned long)context_ptr+0x00006320+4*6))=0xa43f6aa8;
*((unsigned int *)((unsigned long)context_ptr+0x00006320+4*7))=0xe11dae58;
*((unsigned int *)((unsigned long)context_ptr+0x00006320+4*8))=0x5153bbe1;
*((unsigned int *)((unsigned long)context_ptr+0x00006320+4*9))=0x71b04b96;
*((unsigned int *)((unsigned long)context_ptr+0x00006320+4*10))=0x7edb0348;
*((unsigned int *)((unsigned long)context_ptr+0x00006320+4*11))=0x8ac07902;
*((unsigned int *)((unsigned long)context_ptr+0x00006320+4*12))=0xa56e6462;
*((unsigned int *)((unsigned long)context_ptr+0x00006320+4*13))=0xee1ecefa;
*((unsigned int *)((unsigned long)context_ptr+0x00006320+4*14))=0x95f9654b;
*((unsigned int *)((unsigned long)context_ptr+0x00006320+4*15))=0x2eeae00b;
*((unsigned int *)((unsigned long)context_ptr+0x00006320+4*16))=0x4cfee03f;
*((unsigned int *)((unsigned long)context_ptr+0x00006320+4*17))=0xbcfce445;
*((unsigned int *)((unsigned long)context_ptr+0x00006320+4*18))=0xc3f85b25;
*((unsigned int *)((unsigned long)context_ptr+0x00006320+4*19))=0x3e6e8251;
*((unsigned int *)((unsigned long)context_ptr+0x00006320+4*20))=0x0e6506a3;
*((unsigned int *)((unsigned long)context_ptr+0x00006320+4*21))=0xd0f8d3f1;
*((unsigned int *)((unsigned long)context_ptr+0x00006320+4*22))=0x187272a0;
*((unsigned int *)((unsigned long)context_ptr+0x00006320+4*23))=0xf85f4226;
*((unsigned int *)((unsigned long)context_ptr+0x00006320+4*24))=0x4f612737;
*((unsigned int *)((unsigned long)context_ptr+0x00006320+4*25))=0x4f18636b;
*((unsigned int *)((unsigned long)context_ptr+0x00006320+4*26))=0x4beb1745;
*((unsigned int *)((unsigned long)context_ptr+0x00006320+4*27))=0x00b6f559;
*((unsigned int *)((unsigned long)context_ptr+0x00003a50))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003a50+4*1))=0x00006694;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000a50+4*1))=0x00006320;
*((unsigned int *)((unsigned long)context_ptr+0x00000a50+4*2))=0x00006068;
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
if(!memcmp((unsigned char *)context_ptr+0x0000680c,"\x65\x8a\x9d\xf8\x89\x48\xf3\x92\xa3\xed\x30\x9a\xd8\x4a\x03\x83\xbc\xc0\xa0\x47\x33\xf0\x11\xe3\xc4\xde\xbe\x2f\xdc\xea\xd1\x92",32))
printf("strip: 658a9df88948f392, Pass\n");
else
printf("strip: 658a9df88948f392, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000066b4))=0x01ea1002;
*((unsigned int *)((unsigned long)context_ptr+0x000066b4+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000066b4+4*2))=0x02020070;
*((unsigned int *)((unsigned long)context_ptr+0x000066b4+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x000068c8))=0x6306a335;
*((unsigned int *)((unsigned long)context_ptr+0x000068c8+4*1))=0x825de32c;
*((unsigned int *)((unsigned long)context_ptr+0x000068c8+4*2))=0x8930c2f0;
*((unsigned int *)((unsigned long)context_ptr+0x000068c8+4*3))=0xeaee9f69;
*((unsigned int *)((unsigned long)context_ptr+0x000068c8+4*4))=0xab9403b2;
*((unsigned int *)((unsigned long)context_ptr+0x000068c8+4*5))=0x5a6100ca;
*((unsigned int *)((unsigned long)context_ptr+0x000068c8+4*6))=0xa22240a4;
*((unsigned int *)((unsigned long)context_ptr+0x000068c8+4*7))=0xfa11425e;
*((unsigned int *)((unsigned long)context_ptr+0x000068c8+4*8))=0x054c40a4;
*((unsigned int *)((unsigned long)context_ptr+0x000068c8+4*9))=0xe32861c9;
*((unsigned int *)((unsigned long)context_ptr+0x000068c8+4*10))=0xc3c81c33;
*((unsigned int *)((unsigned long)context_ptr+0x000068c8+4*11))=0x1ab43009;
*((unsigned int *)((unsigned long)context_ptr+0x000068c8+4*12))=0xdc54a9bb;
*((unsigned int *)((unsigned long)context_ptr+0x000068c8+4*13))=0x0cd518ea;
*((unsigned int *)((unsigned long)context_ptr+0x000068c8+4*14))=0x3a208eac;
*((unsigned int *)((unsigned long)context_ptr+0x000068c8+4*15))=0x2a3c2b10;
*((unsigned int *)((unsigned long)context_ptr+0x000068c8+4*16))=0xe58c438c;
*((unsigned int *)((unsigned long)context_ptr+0x000068c8+4*17))=0xb92132af;
*((unsigned int *)((unsigned long)context_ptr+0x000068c8+4*18))=0x9ee8d43b;
*((unsigned int *)((unsigned long)context_ptr+0x000068c8+4*19))=0x19944148;
*((unsigned int *)((unsigned long)context_ptr+0x000068c8+4*20))=0xac92d56a;
*((unsigned int *)((unsigned long)context_ptr+0x000068c8+4*21))=0x8c9a2288;
*((unsigned int *)((unsigned long)context_ptr+0x000068c8+4*22))=0xfaf783fc;
*((unsigned int *)((unsigned long)context_ptr+0x000068c8+4*23))=0xc8d58b3b;
*((unsigned int *)((unsigned long)context_ptr+0x000068c8+4*24))=0x8d1ffb6e;
*((unsigned int *)((unsigned long)context_ptr+0x000068c8+4*25))=0x190a7910;
*((unsigned int *)((unsigned long)context_ptr+0x000068c8+4*26))=0x1d6fec65;
*((unsigned int *)((unsigned long)context_ptr+0x000068c8+4*27))=0x7f96f1e6;
*((unsigned int *)((unsigned long)context_ptr+0x00003a68))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003a68+4*1))=0x00006938;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000a68+4*1))=0x000068c8;
*((unsigned int *)((unsigned long)context_ptr+0x00000a68+4*2))=0x000066b4;
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
if(!memcmp((unsigned char *)context_ptr+0x000063fc,"\x5a\x6e\xf6\x16\x6a\x22\xbd\xa1\x40\x2d\x97\x35\xe4\xbf\x3a\x64\x14\x9b\xcb\x54\x80\xbc\x30\xc5\x0f\x3d\xbf\x12\x0e\x8b\x05\x1b",32))
printf("strip: 5a6ef6166a22bda1, Pass\n");
else
printf("strip: 5a6ef6166a22bda1, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000066c4))=0x01ea1002;
*((unsigned int *)((unsigned long)context_ptr+0x000066c4+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000066c4+4*2))=0x02020071;
*((unsigned int *)((unsigned long)context_ptr+0x000066c4+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x00006390))=0x7e97ed1e;
*((unsigned int *)((unsigned long)context_ptr+0x00006390+4*1))=0x4f075893;
*((unsigned int *)((unsigned long)context_ptr+0x00006390+4*2))=0xdfd41397;
*((unsigned int *)((unsigned long)context_ptr+0x00006390+4*3))=0xd4b74270;
*((unsigned int *)((unsigned long)context_ptr+0x00006390+4*4))=0x1ec952a9;
*((unsigned int *)((unsigned long)context_ptr+0x00006390+4*5))=0xa00b6956;
*((unsigned int *)((unsigned long)context_ptr+0x00006390+4*6))=0xc4a069c8;
*((unsigned int *)((unsigned long)context_ptr+0x00006390+4*7))=0xef40f5c2;
*((unsigned int *)((unsigned long)context_ptr+0x00006390+4*8))=0xeb5bc58a;
*((unsigned int *)((unsigned long)context_ptr+0x00006390+4*9))=0xee07ce62;
*((unsigned int *)((unsigned long)context_ptr+0x00006390+4*10))=0x7c65d35c;
*((unsigned int *)((unsigned long)context_ptr+0x00006390+4*11))=0xe2ed0336;
*((unsigned int *)((unsigned long)context_ptr+0x00006390+4*12))=0x5cea9541;
*((unsigned int *)((unsigned long)context_ptr+0x00006390+4*13))=0x9e849399;
*((unsigned int *)((unsigned long)context_ptr+0x00006390+4*14))=0xb74b1c1d;
*((unsigned int *)((unsigned long)context_ptr+0x00006390+4*15))=0x79cb0063;
*((unsigned int *)((unsigned long)context_ptr+0x00006390+4*16))=0x09c9b062;
*((unsigned int *)((unsigned long)context_ptr+0x00006390+4*17))=0x87ba2a38;
*((unsigned int *)((unsigned long)context_ptr+0x00006390+4*18))=0x03578f2d;
*((unsigned int *)((unsigned long)context_ptr+0x00006390+4*19))=0xb2efeeef;
*((unsigned int *)((unsigned long)context_ptr+0x00006390+4*20))=0x10af28cd;
*((unsigned int *)((unsigned long)context_ptr+0x00006390+4*21))=0xf582bb55;
*((unsigned int *)((unsigned long)context_ptr+0x00006390+4*22))=0xec63ab4a;
*((unsigned int *)((unsigned long)context_ptr+0x00006390+4*23))=0x88605584;
*((unsigned int *)((unsigned long)context_ptr+0x00006390+4*24))=0x709465f2;
*((unsigned int *)((unsigned long)context_ptr+0x00006390+4*25))=0xbe6df191;
*((unsigned int *)((unsigned long)context_ptr+0x00006390+4*26))=0x06862daf;
*((unsigned int *)((unsigned long)context_ptr+0x00006390+4*27))=0x1f95a08f;
*((unsigned int *)((unsigned long)context_ptr+0x00006390+4*28))=0x0000008f;
*((unsigned int *)((unsigned long)context_ptr+0x00003a80))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003a80+4*1))=0x000067d0;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000a80+4*1))=0x00006390;
*((unsigned int *)((unsigned long)context_ptr+0x00000a80+4*2))=0x000066c4;
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
if(!memcmp((unsigned char *)context_ptr+0x0000682c,"\x91\x61\x81\xa0\x44\x32\xb2\xbe\x97\xbb\x51\x58\x65\xf2\x97\x61\xc1\x11\x09\xd1\x43\x2c\xc8\x5b\x96\x29\xd2\xb2\x79\xbd\xe9\xf8",32))
printf("strip: 916181a04432b2be, Pass\n");
else
printf("strip: 916181a04432b2be, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000065a4))=0x01ea1002;
*((unsigned int *)((unsigned long)context_ptr+0x000065a4+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000065a4+4*2))=0x02020072;
*((unsigned int *)((unsigned long)context_ptr+0x000065a4+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x00006a4c))=0xe2608f68;
*((unsigned int *)((unsigned long)context_ptr+0x00006a4c+4*1))=0x9000ec93;
*((unsigned int *)((unsigned long)context_ptr+0x00006a4c+4*2))=0xc5338530;
*((unsigned int *)((unsigned long)context_ptr+0x00006a4c+4*3))=0x9b843721;
*((unsigned int *)((unsigned long)context_ptr+0x00006a4c+4*4))=0x07b508b5;
*((unsigned int *)((unsigned long)context_ptr+0x00006a4c+4*5))=0x61002732;
*((unsigned int *)((unsigned long)context_ptr+0x00006a4c+4*6))=0xa3120658;
*((unsigned int *)((unsigned long)context_ptr+0x00006a4c+4*7))=0x2bfbd80a;
*((unsigned int *)((unsigned long)context_ptr+0x00006a4c+4*8))=0x5fb94323;
*((unsigned int *)((unsigned long)context_ptr+0x00006a4c+4*9))=0x0a523b6e;
*((unsigned int *)((unsigned long)context_ptr+0x00006a4c+4*10))=0x559a46b6;
*((unsigned int *)((unsigned long)context_ptr+0x00006a4c+4*11))=0x204dbb92;
*((unsigned int *)((unsigned long)context_ptr+0x00006a4c+4*12))=0x0c3ffeba;
*((unsigned int *)((unsigned long)context_ptr+0x00006a4c+4*13))=0x22ea5eb4;
*((unsigned int *)((unsigned long)context_ptr+0x00006a4c+4*14))=0x78fa8225;
*((unsigned int *)((unsigned long)context_ptr+0x00006a4c+4*15))=0xffe52d68;
*((unsigned int *)((unsigned long)context_ptr+0x00006a4c+4*16))=0x9dcd8023;
*((unsigned int *)((unsigned long)context_ptr+0x00006a4c+4*17))=0x2487cf39;
*((unsigned int *)((unsigned long)context_ptr+0x00006a4c+4*18))=0xe0493dc6;
*((unsigned int *)((unsigned long)context_ptr+0x00006a4c+4*19))=0xb1e6af93;
*((unsigned int *)((unsigned long)context_ptr+0x00006a4c+4*20))=0x92b279d0;
*((unsigned int *)((unsigned long)context_ptr+0x00006a4c+4*21))=0x524523be;
*((unsigned int *)((unsigned long)context_ptr+0x00006a4c+4*22))=0x4d0435c8;
*((unsigned int *)((unsigned long)context_ptr+0x00006a4c+4*23))=0xd7dc9886;
*((unsigned int *)((unsigned long)context_ptr+0x00006a4c+4*24))=0x33573788;
*((unsigned int *)((unsigned long)context_ptr+0x00006a4c+4*25))=0xe0e13cae;
*((unsigned int *)((unsigned long)context_ptr+0x00006a4c+4*26))=0xf91d6b47;
*((unsigned int *)((unsigned long)context_ptr+0x00006a4c+4*27))=0x9e9c5d68;
*((unsigned int *)((unsigned long)context_ptr+0x00006a4c+4*28))=0x0000b7fe;
*((unsigned int *)((unsigned long)context_ptr+0x00003a98))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003a98+4*1))=0x00006404;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000a98+4*1))=0x00006a4c;
*((unsigned int *)((unsigned long)context_ptr+0x00000a98+4*2))=0x000065a4;
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
if(!memcmp((unsigned char *)context_ptr+0x00006504,"\xd8\xbd\x02\x9a\x74\x14\x12\x6a\x65\x6e\xe0\xfd\xe1\x89\x86\xba\xe2\x0a\x27\xdc\x18\x24\xb7\xf9\x3e\xa0\xdf\xd9\xba\xd9\xf5\x27",32))
printf("strip: d8bd029a7414126a, Pass\n");
else
printf("strip: d8bd029a7414126a, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006958))=0x01ea1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006958+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006958+4*2))=0x02020073;
*((unsigned int *)((unsigned long)context_ptr+0x00006958+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x0000649c))=0x079ef2f5;
*((unsigned int *)((unsigned long)context_ptr+0x0000649c+4*1))=0xe5866614;
*((unsigned int *)((unsigned long)context_ptr+0x0000649c+4*2))=0x2755f119;
*((unsigned int *)((unsigned long)context_ptr+0x0000649c+4*3))=0x9da99c86;
*((unsigned int *)((unsigned long)context_ptr+0x0000649c+4*4))=0xf5b7c0c7;
*((unsigned int *)((unsigned long)context_ptr+0x0000649c+4*5))=0x51216a43;
*((unsigned int *)((unsigned long)context_ptr+0x0000649c+4*6))=0x991a4a39;
*((unsigned int *)((unsigned long)context_ptr+0x0000649c+4*7))=0xaf3b8256;
*((unsigned int *)((unsigned long)context_ptr+0x0000649c+4*8))=0x5f6ef8ab;
*((unsigned int *)((unsigned long)context_ptr+0x0000649c+4*9))=0xdca87a08;
*((unsigned int *)((unsigned long)context_ptr+0x0000649c+4*10))=0x3dbf69e7;
*((unsigned int *)((unsigned long)context_ptr+0x0000649c+4*11))=0x52cc3ef9;
*((unsigned int *)((unsigned long)context_ptr+0x0000649c+4*12))=0x672f4d42;
*((unsigned int *)((unsigned long)context_ptr+0x0000649c+4*13))=0x0c68224a;
*((unsigned int *)((unsigned long)context_ptr+0x0000649c+4*14))=0x9e21a5e4;
*((unsigned int *)((unsigned long)context_ptr+0x0000649c+4*15))=0x2f085b36;
*((unsigned int *)((unsigned long)context_ptr+0x0000649c+4*16))=0x12c8f800;
*((unsigned int *)((unsigned long)context_ptr+0x0000649c+4*17))=0xd045cd91;
*((unsigned int *)((unsigned long)context_ptr+0x0000649c+4*18))=0x8f37638b;
*((unsigned int *)((unsigned long)context_ptr+0x0000649c+4*19))=0xbb3a48aa;
*((unsigned int *)((unsigned long)context_ptr+0x0000649c+4*20))=0x3b02864e;
*((unsigned int *)((unsigned long)context_ptr+0x0000649c+4*21))=0xf72be13d;
*((unsigned int *)((unsigned long)context_ptr+0x0000649c+4*22))=0xd63a1b35;
*((unsigned int *)((unsigned long)context_ptr+0x0000649c+4*23))=0xa3b02769;
*((unsigned int *)((unsigned long)context_ptr+0x0000649c+4*24))=0x67afb732;
*((unsigned int *)((unsigned long)context_ptr+0x0000649c+4*25))=0xf33aef46;
*((unsigned int *)((unsigned long)context_ptr+0x0000649c+4*26))=0x236e503c;
*((unsigned int *)((unsigned long)context_ptr+0x0000649c+4*27))=0x0f0d5090;
*((unsigned int *)((unsigned long)context_ptr+0x0000649c+4*28))=0x00b263ef;
*((unsigned int *)((unsigned long)context_ptr+0x00003ab0))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003ab0+4*1))=0x000067f0;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000ab0+4*1))=0x0000649c;
*((unsigned int *)((unsigned long)context_ptr+0x00000ab0+4*2))=0x00006958;
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
if(!memcmp((unsigned char *)context_ptr+0x0000642c,"\x8e\x38\x5e\xc8\x2f\x20\x66\x39\x25\x2d\x09\xb5\xd1\x52\xfb\x3c\x45\x5b\xfe\x2d\xa7\x35\xc8\x19\xc7\xbf\x7c\x32\xa0\x4a\xa5\xe5",32))
printf("strip: 8e385ec82f206639, Pass\n");
else
printf("strip: 8e385ec82f206639, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006510))=0x01ea1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006510+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006510+4*2))=0x02020074;
*((unsigned int *)((unsigned long)context_ptr+0x00006510+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x00006098))=0x77a7df0e;
*((unsigned int *)((unsigned long)context_ptr+0x00006098+4*1))=0xdd6b143e;
*((unsigned int *)((unsigned long)context_ptr+0x00006098+4*2))=0x67a15bdc;
*((unsigned int *)((unsigned long)context_ptr+0x00006098+4*3))=0x117e3b10;
*((unsigned int *)((unsigned long)context_ptr+0x00006098+4*4))=0x5c96e513;
*((unsigned int *)((unsigned long)context_ptr+0x00006098+4*5))=0xd71539f2;
*((unsigned int *)((unsigned long)context_ptr+0x00006098+4*6))=0xdd13edc5;
*((unsigned int *)((unsigned long)context_ptr+0x00006098+4*7))=0x547ce0f0;
*((unsigned int *)((unsigned long)context_ptr+0x00006098+4*8))=0x4fd249d0;
*((unsigned int *)((unsigned long)context_ptr+0x00006098+4*9))=0xb5d6de30;
*((unsigned int *)((unsigned long)context_ptr+0x00006098+4*10))=0x9cd878e7;
*((unsigned int *)((unsigned long)context_ptr+0x00006098+4*11))=0xc9dc7008;
*((unsigned int *)((unsigned long)context_ptr+0x00006098+4*12))=0x41e853d7;
*((unsigned int *)((unsigned long)context_ptr+0x00006098+4*13))=0xcf0d1730;
*((unsigned int *)((unsigned long)context_ptr+0x00006098+4*14))=0x6a936cac;
*((unsigned int *)((unsigned long)context_ptr+0x00006098+4*15))=0x613aa6e6;
*((unsigned int *)((unsigned long)context_ptr+0x00006098+4*16))=0x41b793b0;
*((unsigned int *)((unsigned long)context_ptr+0x00006098+4*17))=0x44fe370b;
*((unsigned int *)((unsigned long)context_ptr+0x00006098+4*18))=0x2284a7e6;
*((unsigned int *)((unsigned long)context_ptr+0x00006098+4*19))=0x2ab09992;
*((unsigned int *)((unsigned long)context_ptr+0x00006098+4*20))=0x94d9d77d;
*((unsigned int *)((unsigned long)context_ptr+0x00006098+4*21))=0xb4e7a35e;
*((unsigned int *)((unsigned long)context_ptr+0x00006098+4*22))=0x0c551f87;
*((unsigned int *)((unsigned long)context_ptr+0x00006098+4*23))=0x8547ed9f;
*((unsigned int *)((unsigned long)context_ptr+0x00006098+4*24))=0x2505479d;
*((unsigned int *)((unsigned long)context_ptr+0x00006098+4*25))=0xac3d1f0c;
*((unsigned int *)((unsigned long)context_ptr+0x00006098+4*26))=0x28b9eef7;
*((unsigned int *)((unsigned long)context_ptr+0x00006098+4*27))=0xfe4e9d48;
*((unsigned int *)((unsigned long)context_ptr+0x00006098+4*28))=0xfffa2cda;
*((unsigned int *)((unsigned long)context_ptr+0x00003ac8))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003ac8+4*1))=0x00006424;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000ac8+4*1))=0x00006098;
*((unsigned int *)((unsigned long)context_ptr+0x00000ac8+4*2))=0x00006510;
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
if(!memcmp((unsigned char *)context_ptr+0x000065b4,"\xdb\x44\xe3\xdf\xe7\x8f\x5c\x5f\x08\xe5\xde\x38\x42\x82\x0f\x44\x6e\x1f\x4f\x81\x16\x91\x71\x58\x15\xe1\x3a\xad\x84\xb4\xbd\x7d",32))
printf("strip: db44e3dfe78f5c5f, Pass\n");
else
printf("strip: db44e3dfe78f5c5f, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000065b4))=0x01ea1002;
*((unsigned int *)((unsigned long)context_ptr+0x000065b4+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000065b4+4*2))=0x02020075;
*((unsigned int *)((unsigned long)context_ptr+0x000065b4+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x0000610c))=0xfd2ab048;
*((unsigned int *)((unsigned long)context_ptr+0x0000610c+4*1))=0xdef9fa77;
*((unsigned int *)((unsigned long)context_ptr+0x0000610c+4*2))=0xae6d8568;
*((unsigned int *)((unsigned long)context_ptr+0x0000610c+4*3))=0x33e46a4e;
*((unsigned int *)((unsigned long)context_ptr+0x0000610c+4*4))=0xdf823a6c;
*((unsigned int *)((unsigned long)context_ptr+0x0000610c+4*5))=0x6008b4a1;
*((unsigned int *)((unsigned long)context_ptr+0x0000610c+4*6))=0x003d5a3c;
*((unsigned int *)((unsigned long)context_ptr+0x0000610c+4*7))=0x9945ab6f;
*((unsigned int *)((unsigned long)context_ptr+0x0000610c+4*8))=0x75b0e468;
*((unsigned int *)((unsigned long)context_ptr+0x0000610c+4*9))=0xbf8e80be;
*((unsigned int *)((unsigned long)context_ptr+0x0000610c+4*10))=0xb7c8799f;
*((unsigned int *)((unsigned long)context_ptr+0x0000610c+4*11))=0x1e021eb3;
*((unsigned int *)((unsigned long)context_ptr+0x0000610c+4*12))=0x255f74bb;
*((unsigned int *)((unsigned long)context_ptr+0x0000610c+4*13))=0x62796387;
*((unsigned int *)((unsigned long)context_ptr+0x0000610c+4*14))=0x09053681;
*((unsigned int *)((unsigned long)context_ptr+0x0000610c+4*15))=0xb4f17fd2;
*((unsigned int *)((unsigned long)context_ptr+0x0000610c+4*16))=0xd23c0597;
*((unsigned int *)((unsigned long)context_ptr+0x0000610c+4*17))=0xb799c6f0;
*((unsigned int *)((unsigned long)context_ptr+0x0000610c+4*18))=0xd03d8ce8;
*((unsigned int *)((unsigned long)context_ptr+0x0000610c+4*19))=0x5dd95db1;
*((unsigned int *)((unsigned long)context_ptr+0x0000610c+4*20))=0xcd676f57;
*((unsigned int *)((unsigned long)context_ptr+0x0000610c+4*21))=0x946cfe04;
*((unsigned int *)((unsigned long)context_ptr+0x0000610c+4*22))=0x5419d4e1;
*((unsigned int *)((unsigned long)context_ptr+0x0000610c+4*23))=0xe991245b;
*((unsigned int *)((unsigned long)context_ptr+0x0000610c+4*24))=0x4a78eadb;
*((unsigned int *)((unsigned long)context_ptr+0x0000610c+4*25))=0x4c9eb058;
*((unsigned int *)((unsigned long)context_ptr+0x0000610c+4*26))=0xff92d803;
*((unsigned int *)((unsigned long)context_ptr+0x0000610c+4*27))=0x1adb5d7f;
*((unsigned int *)((unsigned long)context_ptr+0x0000610c+4*28))=0x01012d93;
*((unsigned int *)((unsigned long)context_ptr+0x0000610c+4*29))=0x0000007e;
*((unsigned int *)((unsigned long)context_ptr+0x00003ae0))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003ae0+4*1))=0x00006520;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000ae0+4*1))=0x0000610c;
*((unsigned int *)((unsigned long)context_ptr+0x00000ae0+4*2))=0x000065b4;
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
if(!memcmp((unsigned char *)context_ptr+0x000065d4,"\x04\xa7\x4a\x41\x64\x96\x66\xe4\xe0\xe9\xbe\x29\x7d\xb6\x83\x79\x50\xbb\xbb\x84\xf8\x36\x0a\xd5\xad\x90\x2b\x7e\xac\x1a\x08\xf5",32))
printf("strip: 04a74a41649666e4, Pass\n");
else
printf("strip: 04a74a41649666e4, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006540))=0x01ea1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006540+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006540+4*2))=0x02020076;
*((unsigned int *)((unsigned long)context_ptr+0x00006540+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x00006184))=0xbd178865;
*((unsigned int *)((unsigned long)context_ptr+0x00006184+4*1))=0xa300585a;
*((unsigned int *)((unsigned long)context_ptr+0x00006184+4*2))=0xd091bf99;
*((unsigned int *)((unsigned long)context_ptr+0x00006184+4*3))=0xc0ce85e7;
*((unsigned int *)((unsigned long)context_ptr+0x00006184+4*4))=0x324f416a;
*((unsigned int *)((unsigned long)context_ptr+0x00006184+4*5))=0xe21bebfa;
*((unsigned int *)((unsigned long)context_ptr+0x00006184+4*6))=0x231c7eb9;
*((unsigned int *)((unsigned long)context_ptr+0x00006184+4*7))=0x430585f6;
*((unsigned int *)((unsigned long)context_ptr+0x00006184+4*8))=0xbddb640d;
*((unsigned int *)((unsigned long)context_ptr+0x00006184+4*9))=0x4f558362;
*((unsigned int *)((unsigned long)context_ptr+0x00006184+4*10))=0xb7ca8548;
*((unsigned int *)((unsigned long)context_ptr+0x00006184+4*11))=0x742a9f27;
*((unsigned int *)((unsigned long)context_ptr+0x00006184+4*12))=0x691fb8d0;
*((unsigned int *)((unsigned long)context_ptr+0x00006184+4*13))=0x5a5a8adc;
*((unsigned int *)((unsigned long)context_ptr+0x00006184+4*14))=0xcdb7216e;
*((unsigned int *)((unsigned long)context_ptr+0x00006184+4*15))=0x5de42198;
*((unsigned int *)((unsigned long)context_ptr+0x00006184+4*16))=0xb05cf8f9;
*((unsigned int *)((unsigned long)context_ptr+0x00006184+4*17))=0x922fd1e0;
*((unsigned int *)((unsigned long)context_ptr+0x00006184+4*18))=0x600dd4cb;
*((unsigned int *)((unsigned long)context_ptr+0x00006184+4*19))=0x1a1a9ca5;
*((unsigned int *)((unsigned long)context_ptr+0x00006184+4*20))=0xb641daeb;
*((unsigned int *)((unsigned long)context_ptr+0x00006184+4*21))=0x74ec2077;
*((unsigned int *)((unsigned long)context_ptr+0x00006184+4*22))=0x05f8571a;
*((unsigned int *)((unsigned long)context_ptr+0x00006184+4*23))=0x2d94a68f;
*((unsigned int *)((unsigned long)context_ptr+0x00006184+4*24))=0x6e20baf1;
*((unsigned int *)((unsigned long)context_ptr+0x00006184+4*25))=0x3a419bb6;
*((unsigned int *)((unsigned long)context_ptr+0x00006184+4*26))=0x61d8ec3b;
*((unsigned int *)((unsigned long)context_ptr+0x00006184+4*27))=0xba46dcf1;
*((unsigned int *)((unsigned long)context_ptr+0x00006184+4*28))=0xbb818551;
*((unsigned int *)((unsigned long)context_ptr+0x00006184+4*29))=0x00003b6e;
*((unsigned int *)((unsigned long)context_ptr+0x00003af8))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003af8+4*1))=0x000065c4;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000af8+4*1))=0x00006184;
*((unsigned int *)((unsigned long)context_ptr+0x00000af8+4*2))=0x00006540;
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
if(!memcmp((unsigned char *)context_ptr+0x000065f4,"\xf7\xab\x38\x8e\x8e\x64\x31\x9d\xef\x3e\x77\x90\xef\x3e\x12\xc6\xec\x7c\xb6\x83\x98\x0d\x5e\xdc\xa7\x0f\x50\x8e\x68\x6c\xb4\xfe",32))
printf("strip: f7ab388e8e64319d, Pass\n");
else
printf("strip: f7ab388e8e64319d, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006550))=0x01ea1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006550+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006550+4*2))=0x02020077;
*((unsigned int *)((unsigned long)context_ptr+0x00006550+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x000061fc))=0x97dc0e45;
*((unsigned int *)((unsigned long)context_ptr+0x000061fc+4*1))=0x11c44eb6;
*((unsigned int *)((unsigned long)context_ptr+0x000061fc+4*2))=0x09c2fffc;
*((unsigned int *)((unsigned long)context_ptr+0x000061fc+4*3))=0xa0641905;
*((unsigned int *)((unsigned long)context_ptr+0x000061fc+4*4))=0xbb0a7e7f;
*((unsigned int *)((unsigned long)context_ptr+0x000061fc+4*5))=0x879577a7;
*((unsigned int *)((unsigned long)context_ptr+0x000061fc+4*6))=0x61afbeb5;
*((unsigned int *)((unsigned long)context_ptr+0x000061fc+4*7))=0x0453900c;
*((unsigned int *)((unsigned long)context_ptr+0x000061fc+4*8))=0x7595206e;
*((unsigned int *)((unsigned long)context_ptr+0x000061fc+4*9))=0xe96bfcce;
*((unsigned int *)((unsigned long)context_ptr+0x000061fc+4*10))=0x8a5d82fb;
*((unsigned int *)((unsigned long)context_ptr+0x000061fc+4*11))=0x065737f9;
*((unsigned int *)((unsigned long)context_ptr+0x000061fc+4*12))=0xd7267ce5;
*((unsigned int *)((unsigned long)context_ptr+0x000061fc+4*13))=0x2241fe7d;
*((unsigned int *)((unsigned long)context_ptr+0x000061fc+4*14))=0x52c991f5;
*((unsigned int *)((unsigned long)context_ptr+0x000061fc+4*15))=0x1b8efa40;
*((unsigned int *)((unsigned long)context_ptr+0x000061fc+4*16))=0x6583b9aa;
*((unsigned int *)((unsigned long)context_ptr+0x000061fc+4*17))=0xcfc8247f;
*((unsigned int *)((unsigned long)context_ptr+0x000061fc+4*18))=0xd90e0ba5;
*((unsigned int *)((unsigned long)context_ptr+0x000061fc+4*19))=0xc31cc0ea;
*((unsigned int *)((unsigned long)context_ptr+0x000061fc+4*20))=0x638d843b;
*((unsigned int *)((unsigned long)context_ptr+0x000061fc+4*21))=0x69cc0557;
*((unsigned int *)((unsigned long)context_ptr+0x000061fc+4*22))=0x5ce7a353;
*((unsigned int *)((unsigned long)context_ptr+0x000061fc+4*23))=0xf93d39df;
*((unsigned int *)((unsigned long)context_ptr+0x000061fc+4*24))=0x379177e5;
*((unsigned int *)((unsigned long)context_ptr+0x000061fc+4*25))=0xff578dc4;
*((unsigned int *)((unsigned long)context_ptr+0x000061fc+4*26))=0x05bce404;
*((unsigned int *)((unsigned long)context_ptr+0x000061fc+4*27))=0xceeaea20;
*((unsigned int *)((unsigned long)context_ptr+0x000061fc+4*28))=0xf5da62f4;
*((unsigned int *)((unsigned long)context_ptr+0x000061fc+4*29))=0x00ff679f;
*((unsigned int *)((unsigned long)context_ptr+0x00003b10))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003b10+4*1))=0x000065e4;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000b10+4*1))=0x000061fc;
*((unsigned int *)((unsigned long)context_ptr+0x00000b10+4*2))=0x00006550;
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
if(!memcmp((unsigned char *)context_ptr+0x0000644c,"\x6f\x77\xbf\x61\x7d\xba\x96\x30\x78\x9d\xf8\xa8\x97\x9e\xe9\x1f\xdb\xa8\x4d\x89\x3f\x39\xe1\x92\xf1\x69\x1f\xc2\x9d\xfb\xed\x0b",32))
printf("strip: 6f77bf617dba9630, Pass\n");
else
printf("strip: 6f77bf617dba9630, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006604))=0x01ea1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006604+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006604+4*2))=0x02020078;
*((unsigned int *)((unsigned long)context_ptr+0x00006604+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x00006968))=0xae180999;
*((unsigned int *)((unsigned long)context_ptr+0x00006968+4*1))=0x51b5551e;
*((unsigned int *)((unsigned long)context_ptr+0x00006968+4*2))=0x9688c451;
*((unsigned int *)((unsigned long)context_ptr+0x00006968+4*3))=0xbe5decee;
*((unsigned int *)((unsigned long)context_ptr+0x00006968+4*4))=0xa9012dc1;
*((unsigned int *)((unsigned long)context_ptr+0x00006968+4*5))=0xd4cecce7;
*((unsigned int *)((unsigned long)context_ptr+0x00006968+4*6))=0x7bd4d99c;
*((unsigned int *)((unsigned long)context_ptr+0x00006968+4*7))=0x24a3fa21;
*((unsigned int *)((unsigned long)context_ptr+0x00006968+4*8))=0x95d385f5;
*((unsigned int *)((unsigned long)context_ptr+0x00006968+4*9))=0x66fec2b4;
*((unsigned int *)((unsigned long)context_ptr+0x00006968+4*10))=0xa8e90b81;
*((unsigned int *)((unsigned long)context_ptr+0x00006968+4*11))=0x3611e097;
*((unsigned int *)((unsigned long)context_ptr+0x00006968+4*12))=0xd548edfc;
*((unsigned int *)((unsigned long)context_ptr+0x00006968+4*13))=0x9dbc6236;
*((unsigned int *)((unsigned long)context_ptr+0x00006968+4*14))=0x4f372caa;
*((unsigned int *)((unsigned long)context_ptr+0x00006968+4*15))=0xe9564470;
*((unsigned int *)((unsigned long)context_ptr+0x00006968+4*16))=0xf8c3fea3;
*((unsigned int *)((unsigned long)context_ptr+0x00006968+4*17))=0x56349ebe;
*((unsigned int *)((unsigned long)context_ptr+0x00006968+4*18))=0xd0f904de;
*((unsigned int *)((unsigned long)context_ptr+0x00006968+4*19))=0x6918d83c;
*((unsigned int *)((unsigned long)context_ptr+0x00006968+4*20))=0x6c10dacd;
*((unsigned int *)((unsigned long)context_ptr+0x00006968+4*21))=0xf25f68cd;
*((unsigned int *)((unsigned long)context_ptr+0x00006968+4*22))=0x869f3d24;
*((unsigned int *)((unsigned long)context_ptr+0x00006968+4*23))=0xc5953159;
*((unsigned int *)((unsigned long)context_ptr+0x00006968+4*24))=0xa57a2d0b;
*((unsigned int *)((unsigned long)context_ptr+0x00006968+4*25))=0x2827c64e;
*((unsigned int *)((unsigned long)context_ptr+0x00006968+4*26))=0x9dec7b59;
*((unsigned int *)((unsigned long)context_ptr+0x00006968+4*27))=0x7d98bec6;
*((unsigned int *)((unsigned long)context_ptr+0x00006968+4*28))=0xa9ad2176;
*((unsigned int *)((unsigned long)context_ptr+0x00006968+4*29))=0x280ca7d9;
*((unsigned int *)((unsigned long)context_ptr+0x00003b28))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003b28+4*1))=0x00006444;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000b28+4*1))=0x00006968;
*((unsigned int *)((unsigned long)context_ptr+0x00000b28+4*2))=0x00006604;
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
if(!memcmp((unsigned char *)context_ptr+0x00006564,"\x6c\x25\xb7\xaa\x81\xcf\x44\x27\x5f\xbc\x07\xbc\xd1\x29\xfd\x82\x2c\x61\xc7\xb3\xca\x0b\x57\x4d\x6f\x0a\x95\x6e\xe4\xe3\x03\x8e",32))
printf("strip: 6c25b7aa81cf4427, Pass\n");
else
printf("strip: 6c25b7aa81cf4427, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006614))=0x01ea1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006614+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006614+4*2))=0x02020079;
*((unsigned int *)((unsigned long)context_ptr+0x00006614+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x00006274))=0x49d1de7d;
*((unsigned int *)((unsigned long)context_ptr+0x00006274+4*1))=0xd5acd69a;
*((unsigned int *)((unsigned long)context_ptr+0x00006274+4*2))=0xde152b74;
*((unsigned int *)((unsigned long)context_ptr+0x00006274+4*3))=0x9854a427;
*((unsigned int *)((unsigned long)context_ptr+0x00006274+4*4))=0x1a354373;
*((unsigned int *)((unsigned long)context_ptr+0x00006274+4*5))=0xcfc64b89;
*((unsigned int *)((unsigned long)context_ptr+0x00006274+4*6))=0xe4bfc260;
*((unsigned int *)((unsigned long)context_ptr+0x00006274+4*7))=0xfc2fe2b6;
*((unsigned int *)((unsigned long)context_ptr+0x00006274+4*8))=0x7dcbc749;
*((unsigned int *)((unsigned long)context_ptr+0x00006274+4*9))=0x374e0ae9;
*((unsigned int *)((unsigned long)context_ptr+0x00006274+4*10))=0x46328a09;
*((unsigned int *)((unsigned long)context_ptr+0x00006274+4*11))=0x1e1cca92;
*((unsigned int *)((unsigned long)context_ptr+0x00006274+4*12))=0x9e8407e0;
*((unsigned int *)((unsigned long)context_ptr+0x00006274+4*13))=0xbee36712;
*((unsigned int *)((unsigned long)context_ptr+0x00006274+4*14))=0x87b39cbe;
*((unsigned int *)((unsigned long)context_ptr+0x00006274+4*15))=0xbcc3f135;
*((unsigned int *)((unsigned long)context_ptr+0x00006274+4*16))=0xb19d3910;
*((unsigned int *)((unsigned long)context_ptr+0x00006274+4*17))=0xe61b9172;
*((unsigned int *)((unsigned long)context_ptr+0x00006274+4*18))=0x640f865d;
*((unsigned int *)((unsigned long)context_ptr+0x00006274+4*19))=0xc6ca2c92;
*((unsigned int *)((unsigned long)context_ptr+0x00006274+4*20))=0x633094f7;
*((unsigned int *)((unsigned long)context_ptr+0x00006274+4*21))=0xa47168c4;
*((unsigned int *)((unsigned long)context_ptr+0x00006274+4*22))=0x8997656e;
*((unsigned int *)((unsigned long)context_ptr+0x00006274+4*23))=0xee19f837;
*((unsigned int *)((unsigned long)context_ptr+0x00006274+4*24))=0x08a469e1;
*((unsigned int *)((unsigned long)context_ptr+0x00006274+4*25))=0x85bc3293;
*((unsigned int *)((unsigned long)context_ptr+0x00006274+4*26))=0xcbde6476;
*((unsigned int *)((unsigned long)context_ptr+0x00006274+4*27))=0x8d84adbf;
*((unsigned int *)((unsigned long)context_ptr+0x00006274+4*28))=0xc97f2e47;
*((unsigned int *)((unsigned long)context_ptr+0x00006274+4*29))=0x019336a6;
*((unsigned int *)((unsigned long)context_ptr+0x00006274+4*30))=0x000000cb;
*((unsigned int *)((unsigned long)context_ptr+0x00003b40))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003b40+4*1))=0x00006560;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000b40+4*1))=0x00006274;
*((unsigned int *)((unsigned long)context_ptr+0x00000b40+4*2))=0x00006614;
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
if(!memcmp((unsigned char *)context_ptr+0x0000647c,"\x43\x1f\x9e\x8a\xe9\xcf\x18\x4a\x0d\x87\x4c\x77\xbf\x3d\x21\x89\xb7\x25\x41\x29\x30\x1f\xaf\x9f\x30\x22\xf9\xee\x6d\x81\x3a\x36",32))
printf("strip: 431f9e8ae9cf184a, Pass\n");
else
printf("strip: 431f9e8ae9cf184a, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000062f0))=0x01ea1002;
*((unsigned int *)((unsigned long)context_ptr+0x000062f0+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000062f0+4*2))=0x0202007a;
*((unsigned int *)((unsigned long)context_ptr+0x000062f0+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x00006810))=0x490d30ba;
*((unsigned int *)((unsigned long)context_ptr+0x00006810+4*1))=0x0474e7bd;
*((unsigned int *)((unsigned long)context_ptr+0x00006810+4*2))=0x86d9f012;
*((unsigned int *)((unsigned long)context_ptr+0x00006810+4*3))=0x9342e832;
*((unsigned int *)((unsigned long)context_ptr+0x00006810+4*4))=0x8f03ccb9;
*((unsigned int *)((unsigned long)context_ptr+0x00006810+4*5))=0x0a7c9548;
*((unsigned int *)((unsigned long)context_ptr+0x00006810+4*6))=0xecaec5ff;
*((unsigned int *)((unsigned long)context_ptr+0x00006810+4*7))=0x0df82c97;
*((unsigned int *)((unsigned long)context_ptr+0x00006810+4*8))=0x8c54a40e;
*((unsigned int *)((unsigned long)context_ptr+0x00006810+4*9))=0x9eb46454;
*((unsigned int *)((unsigned long)context_ptr+0x00006810+4*10))=0xf46b56f0;
*((unsigned int *)((unsigned long)context_ptr+0x00006810+4*11))=0xc9ca1ce8;
*((unsigned int *)((unsigned long)context_ptr+0x00006810+4*12))=0x35ffb541;
*((unsigned int *)((unsigned long)context_ptr+0x00006810+4*13))=0x8334f6c4;
*((unsigned int *)((unsigned long)context_ptr+0x00006810+4*14))=0xaf9f80fb;
*((unsigned int *)((unsigned long)context_ptr+0x00006810+4*15))=0x1d33cc6c;
*((unsigned int *)((unsigned long)context_ptr+0x00006810+4*16))=0x66638abb;
*((unsigned int *)((unsigned long)context_ptr+0x00006810+4*17))=0x87f55b6a;
*((unsigned int *)((unsigned long)context_ptr+0x00006810+4*18))=0x64254ab7;
*((unsigned int *)((unsigned long)context_ptr+0x00006810+4*19))=0x3a9cb6ba;
*((unsigned int *)((unsigned long)context_ptr+0x00006810+4*20))=0x4b430dba;
*((unsigned int *)((unsigned long)context_ptr+0x00006810+4*21))=0x5197a314;
*((unsigned int *)((unsigned long)context_ptr+0x00006810+4*22))=0x8b3decdc;
*((unsigned int *)((unsigned long)context_ptr+0x00006810+4*23))=0xaa1937e7;
*((unsigned int *)((unsigned long)context_ptr+0x00006810+4*24))=0xb9af1ace;
*((unsigned int *)((unsigned long)context_ptr+0x00006810+4*25))=0x53aa4b3a;
*((unsigned int *)((unsigned long)context_ptr+0x00006810+4*26))=0xc81a1e07;
*((unsigned int *)((unsigned long)context_ptr+0x00006810+4*27))=0x954a328c;
*((unsigned int *)((unsigned long)context_ptr+0x00006810+4*28))=0x9cac7f2a;
*((unsigned int *)((unsigned long)context_ptr+0x00006810+4*29))=0x45d03896;
*((unsigned int *)((unsigned long)context_ptr+0x00006810+4*30))=0x000036d9;
*((unsigned int *)((unsigned long)context_ptr+0x00003b58))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003b58+4*1))=0x00006464;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000b58+4*1))=0x00006810;
*((unsigned int *)((unsigned long)context_ptr+0x00000b58+4*2))=0x000062f0;
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
if(!memcmp((unsigned char *)context_ptr+0x00006584,"\x00\x46\x0d\xa2\xad\x54\x39\x6d\x9f\x81\x22\xf1\x4c\xa5\xc4\x0e\x0a\x64\x53\xdb\xc5\x82\x32\xd5\x9f\xa5\x5b\x0b\x3f\x5a\x36\xee",32))
printf("strip: 00460da2ad54396d, Pass\n");
else
printf("strip: 00460da2ad54396d, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006484))=0x01ea1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006484+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006484+4*2))=0x0202007b;
*((unsigned int *)((unsigned long)context_ptr+0x00006484+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x00006ac0))=0x47b7ed20;
*((unsigned int *)((unsigned long)context_ptr+0x00006ac0+4*1))=0x3390b336;
*((unsigned int *)((unsigned long)context_ptr+0x00006ac0+4*2))=0xc85dcf1d;
*((unsigned int *)((unsigned long)context_ptr+0x00006ac0+4*3))=0xad39ec7f;
*((unsigned int *)((unsigned long)context_ptr+0x00006ac0+4*4))=0x2bec3285;
*((unsigned int *)((unsigned long)context_ptr+0x00006ac0+4*5))=0xc60ef9f2;
*((unsigned int *)((unsigned long)context_ptr+0x00006ac0+4*6))=0x96ba378a;
*((unsigned int *)((unsigned long)context_ptr+0x00006ac0+4*7))=0xc2f39a5e;
*((unsigned int *)((unsigned long)context_ptr+0x00006ac0+4*8))=0xc89b926c;
*((unsigned int *)((unsigned long)context_ptr+0x00006ac0+4*9))=0x76b443d6;
*((unsigned int *)((unsigned long)context_ptr+0x00006ac0+4*10))=0x000de5b5;
*((unsigned int *)((unsigned long)context_ptr+0x00006ac0+4*11))=0x62601678;
*((unsigned int *)((unsigned long)context_ptr+0x00006ac0+4*12))=0x7119073a;
*((unsigned int *)((unsigned long)context_ptr+0x00006ac0+4*13))=0xd2980157;
*((unsigned int *)((unsigned long)context_ptr+0x00006ac0+4*14))=0x83b7ff74;
*((unsigned int *)((unsigned long)context_ptr+0x00006ac0+4*15))=0xa25593d6;
*((unsigned int *)((unsigned long)context_ptr+0x00006ac0+4*16))=0xc13d8a8a;
*((unsigned int *)((unsigned long)context_ptr+0x00006ac0+4*17))=0xda565abd;
*((unsigned int *)((unsigned long)context_ptr+0x00006ac0+4*18))=0x91636532;
*((unsigned int *)((unsigned long)context_ptr+0x00006ac0+4*19))=0xa964e91b;
*((unsigned int *)((unsigned long)context_ptr+0x00006ac0+4*20))=0xb413d8e0;
*((unsigned int *)((unsigned long)context_ptr+0x00006ac0+4*21))=0xf73457d8;
*((unsigned int *)((unsigned long)context_ptr+0x00006ac0+4*22))=0x5281f84c;
*((unsigned int *)((unsigned long)context_ptr+0x00006ac0+4*23))=0x0256a674;
*((unsigned int *)((unsigned long)context_ptr+0x00006ac0+4*24))=0x7e6665f5;
*((unsigned int *)((unsigned long)context_ptr+0x00006ac0+4*25))=0x9778c863;
*((unsigned int *)((unsigned long)context_ptr+0x00006ac0+4*26))=0xd7c827a0;
*((unsigned int *)((unsigned long)context_ptr+0x00006ac0+4*27))=0xffb56e2a;
*((unsigned int *)((unsigned long)context_ptr+0x00006ac0+4*28))=0x55c1e5a2;
*((unsigned int *)((unsigned long)context_ptr+0x00006ac0+4*29))=0x76ca424a;
*((unsigned int *)((unsigned long)context_ptr+0x00006ac0+4*30))=0x0001c501;
*((unsigned int *)((unsigned long)context_ptr+0x00003b70))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003b70+4*1))=0x00006078;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000b70+4*1))=0x00006ac0;
*((unsigned int *)((unsigned long)context_ptr+0x00000b70+4*2))=0x00006484;
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
if(!memcmp((unsigned char *)context_ptr+0x00006300,"\x70\x42\xaf\xa6\xe0\x90\xac\x10\x92\xa2\x09\x74\x72\xa6\x0a\xfc\xdd\xbd\x1f\x3b\x01\x02\xcf\xcd\x6b\xd4\x58\x4a\x06\xf6\xb0\xc8",32))
printf("strip: 7042afa6e090ac10, Pass\n");
else
printf("strip: 7042afa6e090ac10, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006058))=0x01ea1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*2))=0x0202007c;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x000066d4))=0xbbeb6a95;
*((unsigned int *)((unsigned long)context_ptr+0x000066d4+4*1))=0x82e51889;
*((unsigned int *)((unsigned long)context_ptr+0x000066d4+4*2))=0x7482b456;
*((unsigned int *)((unsigned long)context_ptr+0x000066d4+4*3))=0x82ad08b7;
*((unsigned int *)((unsigned long)context_ptr+0x000066d4+4*4))=0x03d4f0bf;
*((unsigned int *)((unsigned long)context_ptr+0x000066d4+4*5))=0xef505a73;
*((unsigned int *)((unsigned long)context_ptr+0x000066d4+4*6))=0x1d0996bf;
*((unsigned int *)((unsigned long)context_ptr+0x000066d4+4*7))=0x78e2e66e;
*((unsigned int *)((unsigned long)context_ptr+0x000066d4+4*8))=0x0abe7e29;
*((unsigned int *)((unsigned long)context_ptr+0x000066d4+4*9))=0xf2a7c670;
*((unsigned int *)((unsigned long)context_ptr+0x000066d4+4*10))=0x26bab66b;
*((unsigned int *)((unsigned long)context_ptr+0x000066d4+4*11))=0x00958d60;
*((unsigned int *)((unsigned long)context_ptr+0x000066d4+4*12))=0x53f989a7;
*((unsigned int *)((unsigned long)context_ptr+0x000066d4+4*13))=0x2979864e;
*((unsigned int *)((unsigned long)context_ptr+0x000066d4+4*14))=0x95861a7c;
*((unsigned int *)((unsigned long)context_ptr+0x000066d4+4*15))=0x30e86ac6;
*((unsigned int *)((unsigned long)context_ptr+0x000066d4+4*16))=0x044091be;
*((unsigned int *)((unsigned long)context_ptr+0x000066d4+4*17))=0xad7d132a;
*((unsigned int *)((unsigned long)context_ptr+0x000066d4+4*18))=0xafb4a67e;
*((unsigned int *)((unsigned long)context_ptr+0x000066d4+4*19))=0x20d8c607;
*((unsigned int *)((unsigned long)context_ptr+0x000066d4+4*20))=0x0a23a72d;
*((unsigned int *)((unsigned long)context_ptr+0x000066d4+4*21))=0xa644a2ed;
*((unsigned int *)((unsigned long)context_ptr+0x000066d4+4*22))=0xef1b6265;
*((unsigned int *)((unsigned long)context_ptr+0x000066d4+4*23))=0xa5ebb370;
*((unsigned int *)((unsigned long)context_ptr+0x000066d4+4*24))=0x5317a6b4;
*((unsigned int *)((unsigned long)context_ptr+0x000066d4+4*25))=0x5f4051e3;
*((unsigned int *)((unsigned long)context_ptr+0x000066d4+4*26))=0x9ad96a17;
*((unsigned int *)((unsigned long)context_ptr+0x000066d4+4*27))=0x4e9a7f86;
*((unsigned int *)((unsigned long)context_ptr+0x000066d4+4*28))=0x368a99ce;
*((unsigned int *)((unsigned long)context_ptr+0x000066d4+4*29))=0x4662ebc2;
*((unsigned int *)((unsigned long)context_ptr+0x000066d4+4*30))=0xeb2123bf;
*((unsigned int *)((unsigned long)context_ptr+0x00003b88))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003b88+4*1))=0x00006300;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000b88+4*1))=0x000066d4;
*((unsigned int *)((unsigned long)context_ptr+0x00000b88+4*2))=0x00006058;
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
if(!memcmp((unsigned char *)context_ptr+0x000067b0,"\x14\xc8\x7e\x29\x42\x0c\x0f\x29\x2b\x1d\xea\x66\xbb\x59\xfd\x54\x5d\xcc\x29\xc1\x71\x61\xc0\x74\x0b\xa3\xe4\x1f\xcd\xa7\x51\x9f",32))
printf("strip: 14c87e29420c0f29, Pass\n");
else
printf("strip: 14c87e29420c0f29, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006048))=0x01ea1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006048+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006048+4*2))=0x0202007d;
*((unsigned int *)((unsigned long)context_ptr+0x00006048+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x00006750))=0x3013fe65;
*((unsigned int *)((unsigned long)context_ptr+0x00006750+4*1))=0xecaa9227;
*((unsigned int *)((unsigned long)context_ptr+0x00006750+4*2))=0x423ec346;
*((unsigned int *)((unsigned long)context_ptr+0x00006750+4*3))=0x9445d50c;
*((unsigned int *)((unsigned long)context_ptr+0x00006750+4*4))=0x44eb8718;
*((unsigned int *)((unsigned long)context_ptr+0x00006750+4*5))=0x55542f99;
*((unsigned int *)((unsigned long)context_ptr+0x00006750+4*6))=0x18726746;
*((unsigned int *)((unsigned long)context_ptr+0x00006750+4*7))=0xb5922d81;
*((unsigned int *)((unsigned long)context_ptr+0x00006750+4*8))=0x11eace5b;
*((unsigned int *)((unsigned long)context_ptr+0x00006750+4*9))=0x0847d670;
*((unsigned int *)((unsigned long)context_ptr+0x00006750+4*10))=0xdc1aef74;
*((unsigned int *)((unsigned long)context_ptr+0x00006750+4*11))=0xd92f8280;
*((unsigned int *)((unsigned long)context_ptr+0x00006750+4*12))=0xf592d3c5;
*((unsigned int *)((unsigned long)context_ptr+0x00006750+4*13))=0xdb642eaa;
*((unsigned int *)((unsigned long)context_ptr+0x00006750+4*14))=0x205098b4;
*((unsigned int *)((unsigned long)context_ptr+0x00006750+4*15))=0x72e844ec;
*((unsigned int *)((unsigned long)context_ptr+0x00006750+4*16))=0xa0211cb3;
*((unsigned int *)((unsigned long)context_ptr+0x00006750+4*17))=0x50a89e7f;
*((unsigned int *)((unsigned long)context_ptr+0x00006750+4*18))=0x25df0985;
*((unsigned int *)((unsigned long)context_ptr+0x00006750+4*19))=0xda03232f;
*((unsigned int *)((unsigned long)context_ptr+0x00006750+4*20))=0xa64f44c4;
*((unsigned int *)((unsigned long)context_ptr+0x00006750+4*21))=0xcfd428b3;
*((unsigned int *)((unsigned long)context_ptr+0x00006750+4*22))=0x190c08ab;
*((unsigned int *)((unsigned long)context_ptr+0x00006750+4*23))=0x6745a0b2;
*((unsigned int *)((unsigned long)context_ptr+0x00006750+4*24))=0xa7b34233;
*((unsigned int *)((unsigned long)context_ptr+0x00006750+4*25))=0xf3e32929;
*((unsigned int *)((unsigned long)context_ptr+0x00006750+4*26))=0x2c561053;
*((unsigned int *)((unsigned long)context_ptr+0x00006750+4*27))=0x14f97551;
*((unsigned int *)((unsigned long)context_ptr+0x00006750+4*28))=0xf77e390a;
*((unsigned int *)((unsigned long)context_ptr+0x00006750+4*29))=0xee4ccd3a;
*((unsigned int *)((unsigned long)context_ptr+0x00006750+4*30))=0x2e9d9081;
*((unsigned int *)((unsigned long)context_ptr+0x00006750+4*31))=0x0000009b;
*((unsigned int *)((unsigned long)context_ptr+0x00003ba0))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003ba0+4*1))=0x00006580;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000ba0+4*1))=0x00006750;
*((unsigned int *)((unsigned long)context_ptr+0x00000ba0+4*2))=0x00006048;
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
if(!memcmp((unsigned char *)context_ptr+0x00006694,"\xaa\xcf\xee\x46\xb6\x6e\x81\xe6\x36\xba\x0f\x99\x4f\xd7\x32\x5c\xd8\x13\xeb\x92\xd9\x5f\xdb\x20\x65\x06\xf0\x32\x10\x3b\x01\x7d",32))
printf("strip: aacfee46b66e81e6, Pass\n");
else
printf("strip: aacfee46b66e81e6, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006068))=0x01ea1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006068+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006068+4*2))=0x0202007e;
*((unsigned int *)((unsigned long)context_ptr+0x00006068+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x00006624))=0x65121a6b;
*((unsigned int *)((unsigned long)context_ptr+0x00006624+4*1))=0x644dc04f;
*((unsigned int *)((unsigned long)context_ptr+0x00006624+4*2))=0x38fb7cb4;
*((unsigned int *)((unsigned long)context_ptr+0x00006624+4*3))=0x092145b9;
*((unsigned int *)((unsigned long)context_ptr+0x00006624+4*4))=0xefe82262;
*((unsigned int *)((unsigned long)context_ptr+0x00006624+4*5))=0x58856b96;
*((unsigned int *)((unsigned long)context_ptr+0x00006624+4*6))=0x2dd59280;
*((unsigned int *)((unsigned long)context_ptr+0x00006624+4*7))=0x46e668e2;
*((unsigned int *)((unsigned long)context_ptr+0x00006624+4*8))=0x20c42aaf;
*((unsigned int *)((unsigned long)context_ptr+0x00006624+4*9))=0x89fa3469;
*((unsigned int *)((unsigned long)context_ptr+0x00006624+4*10))=0x44186a2c;
*((unsigned int *)((unsigned long)context_ptr+0x00006624+4*11))=0x81dae11f;
*((unsigned int *)((unsigned long)context_ptr+0x00006624+4*12))=0x330330b1;
*((unsigned int *)((unsigned long)context_ptr+0x00006624+4*13))=0x2743a16a;
*((unsigned int *)((unsigned long)context_ptr+0x00006624+4*14))=0xcda658ad;
*((unsigned int *)((unsigned long)context_ptr+0x00006624+4*15))=0x39cb5444;
*((unsigned int *)((unsigned long)context_ptr+0x00006624+4*16))=0x81da213f;
*((unsigned int *)((unsigned long)context_ptr+0x00006624+4*17))=0x4239d3c3;
*((unsigned int *)((unsigned long)context_ptr+0x00006624+4*18))=0xf4549957;
*((unsigned int *)((unsigned long)context_ptr+0x00006624+4*19))=0x55fe0b62;
*((unsigned int *)((unsigned long)context_ptr+0x00006624+4*20))=0x7b4b11a1;
*((unsigned int *)((unsigned long)context_ptr+0x00006624+4*21))=0xebde59c0;
*((unsigned int *)((unsigned long)context_ptr+0x00006624+4*22))=0x4d9394dd;
*((unsigned int *)((unsigned long)context_ptr+0x00006624+4*23))=0xb657071d;
*((unsigned int *)((unsigned long)context_ptr+0x00006624+4*24))=0x63ed7886;
*((unsigned int *)((unsigned long)context_ptr+0x00006624+4*25))=0x3663418a;
*((unsigned int *)((unsigned long)context_ptr+0x00006624+4*26))=0x416cb2b4;
*((unsigned int *)((unsigned long)context_ptr+0x00006624+4*27))=0x8654e74a;
*((unsigned int *)((unsigned long)context_ptr+0x00006624+4*28))=0x7655878b;
*((unsigned int *)((unsigned long)context_ptr+0x00006624+4*29))=0x02c03256;
*((unsigned int *)((unsigned long)context_ptr+0x00006624+4*30))=0x194c65cb;
*((unsigned int *)((unsigned long)context_ptr+0x00006624+4*31))=0x000042fb;
*((unsigned int *)((unsigned long)context_ptr+0x00003bb8))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003bb8+4*1))=0x0000688c;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000bb8+4*1))=0x00006624;
*((unsigned int *)((unsigned long)context_ptr+0x00000bb8+4*2))=0x00006068;
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
if(!memcmp((unsigned char *)context_ptr+0x00006938,"\xd8\x36\xa5\xc7\x91\x7a\x96\x2d\xab\xed\xc5\xaa\xc4\xf6\x55\xcd\xbb\x0b\x20\x49\x08\x43\xd1\xa1\x4d\x6a\xa6\xcd\x8e\xa0\x5e\x76",32))
printf("strip: d836a5c7917a962d, Pass\n");
else
printf("strip: d836a5c7917a962d, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000066a4))=0x01ea1002;
*((unsigned int *)((unsigned long)context_ptr+0x000066a4+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000066a4+4*2))=0x0202007f;
*((unsigned int *)((unsigned long)context_ptr+0x000066a4+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x000068ac))=0xd3293760;
*((unsigned int *)((unsigned long)context_ptr+0x000068ac+4*1))=0x9c8e65b3;
*((unsigned int *)((unsigned long)context_ptr+0x000068ac+4*2))=0x8c439665;
*((unsigned int *)((unsigned long)context_ptr+0x000068ac+4*3))=0x75941bb5;
*((unsigned int *)((unsigned long)context_ptr+0x000068ac+4*4))=0xa2d3360b;
*((unsigned int *)((unsigned long)context_ptr+0x000068ac+4*5))=0x3853cfa5;
*((unsigned int *)((unsigned long)context_ptr+0x000068ac+4*6))=0x342b6bb5;
*((unsigned int *)((unsigned long)context_ptr+0x000068ac+4*7))=0x191d3042;
*((unsigned int *)((unsigned long)context_ptr+0x000068ac+4*8))=0xda4e75d9;
*((unsigned int *)((unsigned long)context_ptr+0x000068ac+4*9))=0x7df11a5c;
*((unsigned int *)((unsigned long)context_ptr+0x000068ac+4*10))=0xcecb1250;
*((unsigned int *)((unsigned long)context_ptr+0x000068ac+4*11))=0x5677f1fb;
*((unsigned int *)((unsigned long)context_ptr+0x000068ac+4*12))=0x602fbb5a;
*((unsigned int *)((unsigned long)context_ptr+0x000068ac+4*13))=0x2bce391f;
*((unsigned int *)((unsigned long)context_ptr+0x000068ac+4*14))=0x289b7a6c;
*((unsigned int *)((unsigned long)context_ptr+0x000068ac+4*15))=0x91b3faaa;
*((unsigned int *)((unsigned long)context_ptr+0x000068ac+4*16))=0xdaeb1083;
*((unsigned int *)((unsigned long)context_ptr+0x000068ac+4*17))=0xa2ce2d06;
*((unsigned int *)((unsigned long)context_ptr+0x000068ac+4*18))=0xd4a67cf2;
*((unsigned int *)((unsigned long)context_ptr+0x000068ac+4*19))=0x9d303d97;
*((unsigned int *)((unsigned long)context_ptr+0x000068ac+4*20))=0x5f42afcc;
*((unsigned int *)((unsigned long)context_ptr+0x000068ac+4*21))=0x3a01a087;
*((unsigned int *)((unsigned long)context_ptr+0x000068ac+4*22))=0xcdf2c3a7;
*((unsigned int *)((unsigned long)context_ptr+0x000068ac+4*23))=0x1e963bf4;
*((unsigned int *)((unsigned long)context_ptr+0x000068ac+4*24))=0xbcb03e9b;
*((unsigned int *)((unsigned long)context_ptr+0x000068ac+4*25))=0x186e0b7c;
*((unsigned int *)((unsigned long)context_ptr+0x000068ac+4*26))=0x23ebd68c;
*((unsigned int *)((unsigned long)context_ptr+0x000068ac+4*27))=0x9bdf3294;
*((unsigned int *)((unsigned long)context_ptr+0x000068ac+4*28))=0x9043c615;
*((unsigned int *)((unsigned long)context_ptr+0x000068ac+4*29))=0x29b5de58;
*((unsigned int *)((unsigned long)context_ptr+0x000068ac+4*30))=0x47cc3334;
*((unsigned int *)((unsigned long)context_ptr+0x000068ac+4*31))=0x00f30366;
*((unsigned int *)((unsigned long)context_ptr+0x00003bd0))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003bd0+4*1))=0x0000692c;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000bd0+4*1))=0x000068ac;
*((unsigned int *)((unsigned long)context_ptr+0x00000bd0+4*2))=0x000066a4;
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
if(!memcmp((unsigned char *)context_ptr+0x000067d0,"\x9d\xa0\x26\xeb\x80\xd3\xfb\xbb\xc5\xfc\x2b\xfb\x97\x73\xa5\x88\x19\xdc\x0e\xc7\xee\xd6\xfc\x53\xd6\xd9\x2b\x78\xbd\x2e\xaa\xfa",32))
printf("strip: 9da026eb80d3fbbb, Pass\n");
else
printf("strip: 9da026eb80d3fbbb, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000066b4))=0x01ea1002;
*((unsigned int *)((unsigned long)context_ptr+0x000066b4+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000066b4+4*2))=0x02020080;
*((unsigned int *)((unsigned long)context_ptr+0x000066b4+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x00006320))=0xa0bd9905;
*((unsigned int *)((unsigned long)context_ptr+0x00006320+4*1))=0xbcad0e9d;
*((unsigned int *)((unsigned long)context_ptr+0x00006320+4*2))=0x7960c646;
*((unsigned int *)((unsigned long)context_ptr+0x00006320+4*3))=0x941aa03b;
*((unsigned int *)((unsigned long)context_ptr+0x00006320+4*4))=0x8a933b55;
*((unsigned int *)((unsigned long)context_ptr+0x00006320+4*5))=0xdab77b3b;
*((unsigned int *)((unsigned long)context_ptr+0x00006320+4*6))=0x506f0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006320+4*7))=0xf3d95ae6;
*((unsigned int *)((unsigned long)context_ptr+0x00006320+4*8))=0x192d4ce4;
*((unsigned int *)((unsigned long)context_ptr+0x00006320+4*9))=0x408be758;
*((unsigned int *)((unsigned long)context_ptr+0x00006320+4*10))=0xea550bbe;
*((unsigned int *)((unsigned long)context_ptr+0x00006320+4*11))=0x94a1c243;
*((unsigned int *)((unsigned long)context_ptr+0x00006320+4*12))=0x575195c8;
*((unsigned int *)((unsigned long)context_ptr+0x00006320+4*13))=0x3607c31e;
*((unsigned int *)((unsigned long)context_ptr+0x00006320+4*14))=0x95eba041;
*((unsigned int *)((unsigned long)context_ptr+0x00006320+4*15))=0x6ed1e808;
*((unsigned int *)((unsigned long)context_ptr+0x00006320+4*16))=0x957ff50d;
*((unsigned int *)((unsigned long)context_ptr+0x00006320+4*17))=0x2008dcab;
*((unsigned int *)((unsigned long)context_ptr+0x00006320+4*18))=0x9e9eb4d2;
*((unsigned int *)((unsigned long)context_ptr+0x00006320+4*19))=0xfe253220;
*((unsigned int *)((unsigned long)context_ptr+0x00006320+4*20))=0x4a08f450;
*((unsigned int *)((unsigned long)context_ptr+0x00006320+4*21))=0x65546477;
*((unsigned int *)((unsigned long)context_ptr+0x00006320+4*22))=0xc33ed15c;
*((unsigned int *)((unsigned long)context_ptr+0x00006320+4*23))=0x144413db;
*((unsigned int *)((unsigned long)context_ptr+0x00006320+4*24))=0x966a079f;
*((unsigned int *)((unsigned long)context_ptr+0x00006320+4*25))=0x3eb1dd03;
*((unsigned int *)((unsigned long)context_ptr+0x00006320+4*26))=0xf05a1a4f;
*((unsigned int *)((unsigned long)context_ptr+0x00006320+4*27))=0xf8af3cc5;
*((unsigned int *)((unsigned long)context_ptr+0x00006320+4*28))=0xc0891f10;
*((unsigned int *)((unsigned long)context_ptr+0x00006320+4*29))=0x9346f320;
*((unsigned int *)((unsigned long)context_ptr+0x00006320+4*30))=0x9d87dd52;
*((unsigned int *)((unsigned long)context_ptr+0x00006320+4*31))=0xb81cfc2b;
*((unsigned int *)((unsigned long)context_ptr+0x00003be8))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003be8+4*1))=0x000067d0;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000be8+4*1))=0x00006320;
*((unsigned int *)((unsigned long)context_ptr+0x00000be8+4*2))=0x000066b4;
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
if(!memcmp((unsigned char *)context_ptr+0x00006404,"\xa2\xdc\x27\x79\x8a\x82\x7c\x48\x2c\x13\x71\x40\xa3\xd3\x18\xde\x73\x2b\x3b\xc5\xd0\xaf\x5e\x29\x8a\x99\xcb\xce\x4f\xca\x20\x32",32))
printf("strip: a2dc27798a827c48, Pass\n");
else
printf("strip: a2dc27798a827c48, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000066c4))=0x01ea1002;
*((unsigned int *)((unsigned long)context_ptr+0x000066c4+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000066c4+4*2))=0x02020081;
*((unsigned int *)((unsigned long)context_ptr+0x000066c4+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x000063a0))=0x82d8bbaf;
*((unsigned int *)((unsigned long)context_ptr+0x000063a0+4*1))=0x56f861cf;
*((unsigned int *)((unsigned long)context_ptr+0x000063a0+4*2))=0x57900310;
*((unsigned int *)((unsigned long)context_ptr+0x000063a0+4*3))=0x5c937160;
*((unsigned int *)((unsigned long)context_ptr+0x000063a0+4*4))=0x0ed1407a;
*((unsigned int *)((unsigned long)context_ptr+0x000063a0+4*5))=0x492d7fe1;
*((unsigned int *)((unsigned long)context_ptr+0x000063a0+4*6))=0x9ef726a6;
*((unsigned int *)((unsigned long)context_ptr+0x000063a0+4*7))=0x1fe1e4dd;
*((unsigned int *)((unsigned long)context_ptr+0x000063a0+4*8))=0x52b7dca0;
*((unsigned int *)((unsigned long)context_ptr+0x000063a0+4*9))=0xeb9a019b;
*((unsigned int *)((unsigned long)context_ptr+0x000063a0+4*10))=0x820fc664;
*((unsigned int *)((unsigned long)context_ptr+0x000063a0+4*11))=0x21351906;
*((unsigned int *)((unsigned long)context_ptr+0x000063a0+4*12))=0x16b60c08;
*((unsigned int *)((unsigned long)context_ptr+0x000063a0+4*13))=0x287938a4;
*((unsigned int *)((unsigned long)context_ptr+0x000063a0+4*14))=0x276f4bb7;
*((unsigned int *)((unsigned long)context_ptr+0x000063a0+4*15))=0x0d008b05;
*((unsigned int *)((unsigned long)context_ptr+0x000063a0+4*16))=0x788cff42;
*((unsigned int *)((unsigned long)context_ptr+0x000063a0+4*17))=0xb1749929;
*((unsigned int *)((unsigned long)context_ptr+0x000063a0+4*18))=0x07772a98;
*((unsigned int *)((unsigned long)context_ptr+0x000063a0+4*19))=0x9ec21ca3;
*((unsigned int *)((unsigned long)context_ptr+0x000063a0+4*20))=0x30c0f24b;
*((unsigned int *)((unsigned long)context_ptr+0x000063a0+4*21))=0x2c43cc47;
*((unsigned int *)((unsigned long)context_ptr+0x000063a0+4*22))=0x2e383343;
*((unsigned int *)((unsigned long)context_ptr+0x000063a0+4*23))=0x5574f32f;
*((unsigned int *)((unsigned long)context_ptr+0x000063a0+4*24))=0x973bce8d;
*((unsigned int *)((unsigned long)context_ptr+0x000063a0+4*25))=0x99836fd6;
*((unsigned int *)((unsigned long)context_ptr+0x000063a0+4*26))=0x9ecd5742;
*((unsigned int *)((unsigned long)context_ptr+0x000063a0+4*27))=0x9d4e3ead;
*((unsigned int *)((unsigned long)context_ptr+0x000063a0+4*28))=0x1eefe430;
*((unsigned int *)((unsigned long)context_ptr+0x000063a0+4*29))=0x194f6306;
*((unsigned int *)((unsigned long)context_ptr+0x000063a0+4*30))=0xeb81eec7;
*((unsigned int *)((unsigned long)context_ptr+0x000063a0+4*31))=0xa7cd42f7;
*((unsigned int *)((unsigned long)context_ptr+0x000063a0+4*32))=0x00000051;
*((unsigned int *)((unsigned long)context_ptr+0x00003c00))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003c00+4*1))=0x000069e0;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000c00+4*1))=0x000063a0;
*((unsigned int *)((unsigned long)context_ptr+0x00000c00+4*2))=0x000066c4;
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
if(!memcmp((unsigned char *)context_ptr+0x000067f0,"\x43\xa0\x58\xee\x0f\x59\xec\x42\x7c\x25\x1d\xa6\xc2\x94\xb2\xd8\xdd\x6f\xbd\x83\x38\xd5\xa1\x80\xf9\xbf\x4b\xf3\x82\xc9\xc0\x9f",32))
printf("strip: 43a058ee0f59ec42, Pass\n");
else
printf("strip: 43a058ee0f59ec42, Failed\n");
writel(0x000002b8&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006424,"\xbe\x45\x9f\xc1\x43\x82\x69\x14\xc6\x46\x93\x35\x7b\xac\xad\x0c\x1e\x47\xac\xef\x08\x66\xa8\xaf\x1a\x22\x79\x20\xda\x94\x84\x4a",32))
printf("strip: be459fc143826914, Pass\n");
else
printf("strip: be459fc143826914, Failed\n");
writel(0x000002be&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006520,"\xee\xea\x1e\x37\x78\x54\x2e\x77\x76\x33\x84\x80\x78\xd4\x51\x0c\x93\x53\x1a\x8c\xfe\x5d\x32\xd7\xdb\x05\x74\xd4\x60\x55\x9e\xd8",32))
printf("strip: eeea1e3778542e77, Pass\n");
else
printf("strip: eeea1e3778542e77, Failed\n");
writel(0x000002c4&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000065c4,"\x6f\x58\x43\x90\x19\x1b\x15\x62\xdc\x7e\xcd\x50\x3b\x80\x5a\xd6\x50\x92\x4b\xb0\x60\x9c\x27\x1a\x12\xfa\xe5\x9c\xe2\x3f\x8d\x41",32))
printf("strip: 6f584390191b1562, Pass\n");
else
printf("strip: 6f584390191b1562, Failed\n");
writel(0x000002ca&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000065e4,"\xec\x21\xd0\x66\x22\x06\x05\x12\x20\xe8\x58\x92\xf3\xb6\xa7\x9d\xf6\x3f\x44\xbe\x01\x5c\xbe\x7c\x56\xac\xc6\x1e\x7a\x9d\x25\xc1",32))
printf("strip: ec21d06622060512, Pass\n");
else
printf("strip: ec21d06622060512, Failed\n");
writel(0x000002d0&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006444,"\x00\x45\x74\x2a\x10\xda\xb9\x13\x9c\x9d\x6b\x7e\x33\x08\xb3\xad\x2b\x21\x8e\x6c\xb7\x78\x83\x6a\xc2\x23\x04\xd6\x46\x97\x2a\xbb",32))
printf("strip: 0045742a10dab913, Pass\n");
else
printf("strip: 0045742a10dab913, Failed\n");
writel(0x000002d6&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006560,"\xfe\xf8\x68\xc9\x58\x8e\xa1\x0d\x59\x20\x28\x19\xfd\xab\xe2\x1a\x31\x7e\x79\x53\xb1\x94\x99\x36\xc7\x42\xe3\x7f\xd2\x6b\x02\x1f",32))
printf("strip: fef868c9588ea10d, Pass\n");
else
printf("strip: fef868c9588ea10d, Failed\n");
writel(0x000002dc&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006464,"\x9c\xfb\x99\xa3\x22\xd4\xd9\x0c\x3a\x1a\x56\x27\x8a\x72\xde\x51\x8e\xe9\x28\x57\xe4\x1a\x0e\x6b\xd3\x15\xca\x3b\x64\xf4\x1e\x95",32))
printf("strip: 9cfb99a322d4d90c, Pass\n");
else
printf("strip: 9cfb99a322d4d90c, Failed\n");
writel(0x000002e2&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006078,"\x43\xb9\x5b\x25\x38\xf6\xff\xf7\x6b\xf1\xb6\xbf\x8d\xb9\x51\x71\xc9\x96\xe0\x3f\x32\x93\x99\x2b\x17\xf0\x7e\x0f\xfd\xd4\xe6\x05",32))
printf("strip: 43b95b2538f6fff7, Pass\n");
else
printf("strip: 43b95b2538f6fff7, Failed\n");
writel(0x000002e8&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006300,"\x1e\x12\x71\xa5\xee\x7f\x8d\xd8\x6e\x57\x13\xd2\x4a\x24\xd9\x2a\x2e\x09\x2a\x22\x86\x25\x35\x33\x8d\x9f\xf9\x1f\x2a\x29\xaf\x1a",32))
printf("strip: 1e1271a5ee7f8dd8, Pass\n");
else
printf("strip: 1e1271a5ee7f8dd8, Failed\n");
writel(0x000002ee&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006580,"\x3b\xf5\x31\xde\x6c\xc7\x1e\x8a\xb6\x2d\xea\x4a\x1e\x19\x34\x22\x67\x7d\x27\xb8\x3f\x1c\x0a\xa7\x56\xd6\xca\xa0\x54\x32\xb5\xc0",32))
printf("strip: 3bf531de6cc71e8a, Pass\n");
else
printf("strip: 3bf531de6cc71e8a, Failed\n");
writel(0x000002f4&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x0000688c,"\xf9\xeb\xba\x44\x07\x5f\xef\xf0\xa6\xd6\xc2\x62\xe0\xd2\x06\x16\x0c\x9c\x54\x2d\x5d\xce\xf0\xb1\x14\x87\x80\x4f\x0d\xbe\x63\x0a",32))
printf("strip: f9ebba44075feff0, Pass\n");
else
printf("strip: f9ebba44075feff0, Failed\n");
writel(0x000002fa&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x0000692c,"\x2a\x38\xe9\x64\xfa\xc4\x2a\xd6\xb7\x22\x6f\xb4\x38\xd4\x6d\xfa\x27\xe6\xa0\x62\xb0\x59\xa2\x60\x29\x13\xe4\x46\x7d\x73\xf8\x63",32))
printf("strip: 2a38e964fac42ad6, Pass\n");
else
printf("strip: 2a38e964fac42ad6, Failed\n");
writel(0x00000300&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
writel(0x00000c00&0xffffffff,ivp_cae_base_addr+0x00000830);
if(!memcmp((unsigned char *)context_ptr+0x000067d0,"\x7b\x2c\x42\xa4\x7e\x8f\xae\xc0\x81\x5c\xfe\x69\x97\xa4\x2f\x7a\xcd\x7c\x46\x73\xab\xd7\xd5\xda\xda\x53\x91\xd5\x86\x48\x79\x86",32))
printf("strip: 7b2c42a47e8faec0, Pass\n");
else
printf("strip: 7b2c42a47e8faec0, Failed\n");
writel(0x00000006&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000069e0,"\xb4\x4f\x63\x0a\x83\xed\xe0\x93\x3a\x2c\x21\x1f\x96\x78\xb0\x6d\x8f\x78\x3f\x61\x2c\x71\xe2\xc2\x4c\x71\xd4\x36\x1e\x79\x48\xfe",32))
printf("strip: b44f630a83ede093, Pass\n");
else
printf("strip: b44f630a83ede093, Failed\n");
}

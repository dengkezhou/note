#include <common.h>
#include <malloc.h>

extern volatile unsigned int ivp_cae_base_addr;

void test_hmac_sha224_fips(void)
{
unsigned int *context_ptr=(unsigned int *)0x14000000;
printf("test_hmac_sha224_fips\n");
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
*((unsigned int *)((unsigned long)context_ptr+0x00006000))=0x026a1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006000+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006000+4*2))=0x07c0c4fe;
*((unsigned int *)((unsigned long)context_ptr+0x00006000+4*3))=0xa59f475d;
*((unsigned int *)((unsigned long)context_ptr+0x00006000+4*4))=0xbbe956c4;
*((unsigned int *)((unsigned long)context_ptr+0x00006000+4*5))=0x45d538b4;
*((unsigned int *)((unsigned long)context_ptr+0x00006000+4*6))=0x8f2ad900;
*((unsigned int *)((unsigned long)context_ptr+0x00006000+4*7))=0xba3603c5;
*((unsigned int *)((unsigned long)context_ptr+0x00006000+4*8))=0xc01584a4;
*((unsigned int *)((unsigned long)context_ptr+0x00006000+4*9))=0x039bc763;
*((unsigned int *)((unsigned long)context_ptr+0x00006000+4*10))=0x42351b40;
*((unsigned int *)((unsigned long)context_ptr+0x00006000+4*11))=0x9b8204e5;
*((unsigned int *)((unsigned long)context_ptr+0x00006000+4*12))=0xcd9fffa6;
*((unsigned int *)((unsigned long)context_ptr+0x00006000+4*13))=0x331fe6bb;
*((unsigned int *)((unsigned long)context_ptr+0x00006000+4*14))=0x8d4e07f1;
*((unsigned int *)((unsigned long)context_ptr+0x00006000+4*15))=0x887ab7ba;
*((unsigned int *)((unsigned long)context_ptr+0x00006000+4*16))=0xb18ba43c;
*((unsigned int *)((unsigned long)context_ptr+0x00006000+4*17))=0x629aee12;
*((unsigned int *)((unsigned long)context_ptr+0x00006048))=0x026a1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006048+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006048+4*2))=0x4ebc1624;
*((unsigned int *)((unsigned long)context_ptr+0x00006048+4*3))=0x072f1b89;
*((unsigned int *)((unsigned long)context_ptr+0x00006048+4*4))=0xbb08835a;
*((unsigned int *)((unsigned long)context_ptr+0x00006048+4*5))=0x5b3270f0;
*((unsigned int *)((unsigned long)context_ptr+0x00006048+4*6))=0x5649a457;
*((unsigned int *)((unsigned long)context_ptr+0x00006048+4*7))=0x518ad81a;
*((unsigned int *)((unsigned long)context_ptr+0x00006048+4*8))=0x0df4b211;
*((unsigned int *)((unsigned long)context_ptr+0x00006048+4*9))=0xc36df308;
*((unsigned int *)((unsigned long)context_ptr+0x00006048+4*10))=0xb2cd1518;
*((unsigned int *)((unsigned long)context_ptr+0x00006048+4*11))=0x33e6daf5;
*((unsigned int *)((unsigned long)context_ptr+0x00006048+4*12))=0x2944a7fc;
*((unsigned int *)((unsigned long)context_ptr+0x00006048+4*13))=0x4963f2cb;
*((unsigned int *)((unsigned long)context_ptr+0x00006048+4*14))=0xdabb1bce;
*((unsigned int *)((unsigned long)context_ptr+0x00006048+4*15))=0xba80fa75;
*((unsigned int *)((unsigned long)context_ptr+0x00006048+4*16))=0xd5cf313b;
*((unsigned int *)((unsigned long)context_ptr+0x00006048+4*17))=0x9337ba0c;
*((unsigned int *)((unsigned long)context_ptr+0x00006090))=0x026a1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006090+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006090+4*2))=0x5dcbb833;
*((unsigned int *)((unsigned long)context_ptr+0x00006090+4*3))=0xc54f0c3f;
*((unsigned int *)((unsigned long)context_ptr+0x00006090+4*4))=0x290b4a45;
*((unsigned int *)((unsigned long)context_ptr+0x00006090+4*5))=0x8fb3aca7;
*((unsigned int *)((unsigned long)context_ptr+0x00006090+4*6))=0x7636012b;
*((unsigned int *)((unsigned long)context_ptr+0x00006090+4*7))=0x91f73640;
*((unsigned int *)((unsigned long)context_ptr+0x00006090+4*8))=0xfe7805e7;
*((unsigned int *)((unsigned long)context_ptr+0x00006090+4*9))=0x216feef6;
*((unsigned int *)((unsigned long)context_ptr+0x00006090+4*10))=0xdc06f5d9;
*((unsigned int *)((unsigned long)context_ptr+0x00006090+4*11))=0xaf35997b;
*((unsigned int *)((unsigned long)context_ptr+0x00006090+4*12))=0x73dfffe1;
*((unsigned int *)((unsigned long)context_ptr+0x00006090+4*13))=0x829e7dbf;
*((unsigned int *)((unsigned long)context_ptr+0x00006090+4*14))=0x59acdd5b;
*((unsigned int *)((unsigned long)context_ptr+0x00006090+4*15))=0xa5173cdf;
*((unsigned int *)((unsigned long)context_ptr+0x00006090+4*16))=0x7a5bddd4;
*((unsigned int *)((unsigned long)context_ptr+0x00006090+4*17))=0xb2b56d15;
*((unsigned int *)((unsigned long)context_ptr+0x000060d8))=0x026a1002;
*((unsigned int *)((unsigned long)context_ptr+0x000060d8+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000060d8+4*2))=0x946fd46b;
*((unsigned int *)((unsigned long)context_ptr+0x000060d8+4*3))=0x89f231a7;
*((unsigned int *)((unsigned long)context_ptr+0x000060d8+4*4))=0xcead4890;
*((unsigned int *)((unsigned long)context_ptr+0x000060d8+4*5))=0xd2e66547;
*((unsigned int *)((unsigned long)context_ptr+0x000060d8+4*6))=0xb703b7e1;
*((unsigned int *)((unsigned long)context_ptr+0x000060d8+4*7))=0x4d1fb13c;
*((unsigned int *)((unsigned long)context_ptr+0x000060d8+4*8))=0x90b280da;
*((unsigned int *)((unsigned long)context_ptr+0x000060d8+4*9))=0x65abcae8;
*((unsigned int *)((unsigned long)context_ptr+0x000060d8+4*10))=0xfaa4d25e;
*((unsigned int *)((unsigned long)context_ptr+0x000060d8+4*11))=0x6eb68dae;
*((unsigned int *)((unsigned long)context_ptr+0x000060d8+4*12))=0x01b7e0ec;
*((unsigned int *)((unsigned long)context_ptr+0x000060d8+4*13))=0x68b24af4;
*((unsigned int *)((unsigned long)context_ptr+0x000060d8+4*14))=0x69b45ff8;
*((unsigned int *)((unsigned long)context_ptr+0x000060d8+4*15))=0xa3c34c47;
*((unsigned int *)((unsigned long)context_ptr+0x000060d8+4*16))=0x814cc382;
*((unsigned int *)((unsigned long)context_ptr+0x000060d8+4*17))=0x2194c60c;
*((unsigned int *)((unsigned long)context_ptr+0x00006120))=0x026a1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006120+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006120+4*2))=0x1daf285e;
*((unsigned int *)((unsigned long)context_ptr+0x00006120+4*3))=0x60d7cb96;
*((unsigned int *)((unsigned long)context_ptr+0x00006120+4*4))=0x0eacbd25;
*((unsigned int *)((unsigned long)context_ptr+0x00006120+4*5))=0xebbb986d;
*((unsigned int *)((unsigned long)context_ptr+0x00006120+4*6))=0xec42fa00;
*((unsigned int *)((unsigned long)context_ptr+0x00006120+4*7))=0xeeed0027;
*((unsigned int *)((unsigned long)context_ptr+0x00006120+4*8))=0x079e5324;
*((unsigned int *)((unsigned long)context_ptr+0x00006120+4*9))=0x3af6fd07;
*((unsigned int *)((unsigned long)context_ptr+0x00006120+4*10))=0x349801f7;
*((unsigned int *)((unsigned long)context_ptr+0x00006120+4*11))=0xe12fb9b0;
*((unsigned int *)((unsigned long)context_ptr+0x00006120+4*12))=0xea262eb7;
*((unsigned int *)((unsigned long)context_ptr+0x00006120+4*13))=0x18e13125;
*((unsigned int *)((unsigned long)context_ptr+0x00006120+4*14))=0xf6f83223;
*((unsigned int *)((unsigned long)context_ptr+0x00006120+4*15))=0x3b2e91ab;
*((unsigned int *)((unsigned long)context_ptr+0x00006120+4*16))=0xb3418e2d;
*((unsigned int *)((unsigned long)context_ptr+0x00006120+4*17))=0xa22afa0d;
*((unsigned int *)((unsigned long)context_ptr+0x00006168))=0x026a1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006168+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006168+4*2))=0x05edc3c7;
*((unsigned int *)((unsigned long)context_ptr+0x00006168+4*3))=0x761c7486;
*((unsigned int *)((unsigned long)context_ptr+0x00006168+4*4))=0xb597eac7;
*((unsigned int *)((unsigned long)context_ptr+0x00006168+4*5))=0xff5d82d7;
*((unsigned int *)((unsigned long)context_ptr+0x00006168+4*6))=0xe5227afa;
*((unsigned int *)((unsigned long)context_ptr+0x00006168+4*7))=0x6f7607f0;
*((unsigned int *)((unsigned long)context_ptr+0x00006168+4*8))=0x86109998;
*((unsigned int *)((unsigned long)context_ptr+0x00006168+4*9))=0x1dc27dd9;
*((unsigned int *)((unsigned long)context_ptr+0x00006168+4*10))=0x8221e4d9;
*((unsigned int *)((unsigned long)context_ptr+0x00006168+4*11))=0x8d92cfa7;
*((unsigned int *)((unsigned long)context_ptr+0x00006168+4*12))=0x68260420;
*((unsigned int *)((unsigned long)context_ptr+0x00006168+4*13))=0xb9524261;
*((unsigned int *)((unsigned long)context_ptr+0x00006168+4*14))=0x7377ca23;
*((unsigned int *)((unsigned long)context_ptr+0x00006168+4*15))=0xb4f8e4fa;
*((unsigned int *)((unsigned long)context_ptr+0x00006168+4*16))=0xf77bb744;
*((unsigned int *)((unsigned long)context_ptr+0x00006168+4*17))=0x1a02334a;
*((unsigned int *)((unsigned long)context_ptr+0x000061b0))=0x026a1002;
*((unsigned int *)((unsigned long)context_ptr+0x000061b0+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000061b0+4*2))=0x05edc3c7;
*((unsigned int *)((unsigned long)context_ptr+0x000061b0+4*3))=0x761c7486;
*((unsigned int *)((unsigned long)context_ptr+0x000061b0+4*4))=0xb597eac7;
*((unsigned int *)((unsigned long)context_ptr+0x000061b0+4*5))=0xff5d82d7;
*((unsigned int *)((unsigned long)context_ptr+0x000061b0+4*6))=0xe5227afa;
*((unsigned int *)((unsigned long)context_ptr+0x000061b0+4*7))=0x6f7607f0;
*((unsigned int *)((unsigned long)context_ptr+0x000061b0+4*8))=0x86109998;
*((unsigned int *)((unsigned long)context_ptr+0x000061b0+4*9))=0x1dc27dd9;
*((unsigned int *)((unsigned long)context_ptr+0x000061b0+4*10))=0x8221e4d9;
*((unsigned int *)((unsigned long)context_ptr+0x000061b0+4*11))=0x8d92cfa7;
*((unsigned int *)((unsigned long)context_ptr+0x000061b0+4*12))=0x68260420;
*((unsigned int *)((unsigned long)context_ptr+0x000061b0+4*13))=0xb9524261;
*((unsigned int *)((unsigned long)context_ptr+0x000061b0+4*14))=0x7377ca23;
*((unsigned int *)((unsigned long)context_ptr+0x000061b0+4*15))=0xb4f8e4fa;
*((unsigned int *)((unsigned long)context_ptr+0x000061b0+4*16))=0xf77bb744;
*((unsigned int *)((unsigned long)context_ptr+0x000061b0+4*17))=0x1a02334a;
*((unsigned int *)((unsigned long)context_ptr+0x000061f8))=0x026a1002;
*((unsigned int *)((unsigned long)context_ptr+0x000061f8+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000061f8+4*2))=0x02020008;
*((unsigned int *)((unsigned long)context_ptr+0x000061f8+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x00006208))=0x54206948;
*((unsigned int *)((unsigned long)context_ptr+0x00006208+4*1))=0x65726568;
*((unsigned int *)((unsigned long)context_ptr+0x00003000))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003000+4*1))=0x00006210;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000000))=0x04c00008;
*((unsigned int *)((unsigned long)context_ptr+0x00000000+4*1))=0x00006208;
*((unsigned int *)((unsigned long)context_ptr+0x00000000+4*2))=0x000061f8;
*((unsigned int *)((unsigned long)context_ptr+0x00000000+4*3))=0x02220008;
*((unsigned int *)((unsigned long)context_ptr+0x00000000+4*4))=0x0ffb1c2c;
*((unsigned int *)((unsigned long)context_ptr+0x00000000+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x0000622c))=0x026a1002;
*((unsigned int *)((unsigned long)context_ptr+0x0000622c+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x0000622c+4*2))=0x0202001c;
*((unsigned int *)((unsigned long)context_ptr+0x0000622c+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x0000623c))=0x74616877;
*((unsigned int *)((unsigned long)context_ptr+0x0000623c+4*1))=0x206f6420;
*((unsigned int *)((unsigned long)context_ptr+0x0000623c+4*2))=0x77206179;
*((unsigned int *)((unsigned long)context_ptr+0x0000623c+4*3))=0x20746e61;
*((unsigned int *)((unsigned long)context_ptr+0x0000623c+4*4))=0x20726f66;
*((unsigned int *)((unsigned long)context_ptr+0x0000623c+4*5))=0x68746f6e;
*((unsigned int *)((unsigned long)context_ptr+0x0000623c+4*6))=0x3f676e69;
*((unsigned int *)((unsigned long)context_ptr+0x00003018))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003018+4*1))=0x00006258;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000018))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00000018+4*1))=0x0000623c;
*((unsigned int *)((unsigned long)context_ptr+0x00000018+4*2))=0x0000622c;
*((unsigned int *)((unsigned long)context_ptr+0x00000018+4*3))=0x0222001c;
*((unsigned int *)((unsigned long)context_ptr+0x00000018+4*4))=0x0b11bb2b;
*((unsigned int *)((unsigned long)context_ptr+0x00000018+4*5))=0x00006048+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x00006274))=0x026a1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006274+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006274+4*2))=0x02020032;
*((unsigned int *)((unsigned long)context_ptr+0x00006274+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x00006284))=0xdddddddd;
*((unsigned int *)((unsigned long)context_ptr+0x00006284+4*1))=0xdddddddd;
*((unsigned int *)((unsigned long)context_ptr+0x00006284+4*2))=0xdddddddd;
*((unsigned int *)((unsigned long)context_ptr+0x00006284+4*3))=0xdddddddd;
*((unsigned int *)((unsigned long)context_ptr+0x00006284+4*4))=0xdddddddd;
*((unsigned int *)((unsigned long)context_ptr+0x00006284+4*5))=0xdddddddd;
*((unsigned int *)((unsigned long)context_ptr+0x00006284+4*6))=0xdddddddd;
*((unsigned int *)((unsigned long)context_ptr+0x00006284+4*7))=0xdddddddd;
*((unsigned int *)((unsigned long)context_ptr+0x00006284+4*8))=0xdddddddd;
*((unsigned int *)((unsigned long)context_ptr+0x00006284+4*9))=0xdddddddd;
*((unsigned int *)((unsigned long)context_ptr+0x00006284+4*10))=0xdddddddd;
*((unsigned int *)((unsigned long)context_ptr+0x00006284+4*11))=0xdddddddd;
*((unsigned int *)((unsigned long)context_ptr+0x00006284+4*12))=0x0000dddd;
*((unsigned int *)((unsigned long)context_ptr+0x00003030))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003030+4*1))=0x000062b8;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000030))=0x04c00032;
*((unsigned int *)((unsigned long)context_ptr+0x00000030+4*1))=0x00006284;
*((unsigned int *)((unsigned long)context_ptr+0x00000030+4*2))=0x00006274;
*((unsigned int *)((unsigned long)context_ptr+0x00000030+4*3))=0x02220032;
*((unsigned int *)((unsigned long)context_ptr+0x00000030+4*4))=0x08f0c416;
*((unsigned int *)((unsigned long)context_ptr+0x00000030+4*5))=0x00006090+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x000062d4))=0x026a1002;
*((unsigned int *)((unsigned long)context_ptr+0x000062d4+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000062d4+4*2))=0x02020032;
*((unsigned int *)((unsigned long)context_ptr+0x000062d4+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x000062e4))=0xcdcdcdcd;
*((unsigned int *)((unsigned long)context_ptr+0x000062e4+4*1))=0xcdcdcdcd;
*((unsigned int *)((unsigned long)context_ptr+0x000062e4+4*2))=0xcdcdcdcd;
*((unsigned int *)((unsigned long)context_ptr+0x000062e4+4*3))=0xcdcdcdcd;
*((unsigned int *)((unsigned long)context_ptr+0x000062e4+4*4))=0xcdcdcdcd;
*((unsigned int *)((unsigned long)context_ptr+0x000062e4+4*5))=0xcdcdcdcd;
*((unsigned int *)((unsigned long)context_ptr+0x000062e4+4*6))=0xcdcdcdcd;
*((unsigned int *)((unsigned long)context_ptr+0x000062e4+4*7))=0xcdcdcdcd;
*((unsigned int *)((unsigned long)context_ptr+0x000062e4+4*8))=0xcdcdcdcd;
*((unsigned int *)((unsigned long)context_ptr+0x000062e4+4*9))=0xcdcdcdcd;
*((unsigned int *)((unsigned long)context_ptr+0x000062e4+4*10))=0xcdcdcdcd;
*((unsigned int *)((unsigned long)context_ptr+0x000062e4+4*11))=0xcdcdcdcd;
*((unsigned int *)((unsigned long)context_ptr+0x000062e4+4*12))=0x0000cdcd;
*((unsigned int *)((unsigned long)context_ptr+0x00003048))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003048+4*1))=0x00006318;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000048))=0x04c00032;
*((unsigned int *)((unsigned long)context_ptr+0x00000048+4*1))=0x000062e4;
*((unsigned int *)((unsigned long)context_ptr+0x00000048+4*2))=0x000062d4;
*((unsigned int *)((unsigned long)context_ptr+0x00000048+4*3))=0x02220032;
*((unsigned int *)((unsigned long)context_ptr+0x00000048+4*4))=0x032a564e;
*((unsigned int *)((unsigned long)context_ptr+0x00000048+4*5))=0x000060d8+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x00006334))=0x026a1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006334+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006334+4*2))=0x02020014;
*((unsigned int *)((unsigned long)context_ptr+0x00006334+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x00006344))=0x74736554;
*((unsigned int *)((unsigned long)context_ptr+0x00006344+4*1))=0x74695720;
*((unsigned int *)((unsigned long)context_ptr+0x00006344+4*2))=0x72542068;
*((unsigned int *)((unsigned long)context_ptr+0x00006344+4*3))=0x61636e75;
*((unsigned int *)((unsigned long)context_ptr+0x00006344+4*4))=0x6e6f6974;
*((unsigned int *)((unsigned long)context_ptr+0x00003060))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003060+4*1))=0x00006358;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000060))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00000060+4*1))=0x00006344;
*((unsigned int *)((unsigned long)context_ptr+0x00000060+4*2))=0x00006334;
*((unsigned int *)((unsigned long)context_ptr+0x00000060+4*3))=0x02220014;
*((unsigned int *)((unsigned long)context_ptr+0x00000060+4*4))=0x093d5e32;
*((unsigned int *)((unsigned long)context_ptr+0x00000060+4*5))=0x00006120+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x00006368))=0x026a1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006368+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006368+4*2))=0x02020036;
*((unsigned int *)((unsigned long)context_ptr+0x00006368+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x00006378))=0x74736554;
*((unsigned int *)((unsigned long)context_ptr+0x00006378+4*1))=0x69735520;
*((unsigned int *)((unsigned long)context_ptr+0x00006378+4*2))=0x4c20676e;
*((unsigned int *)((unsigned long)context_ptr+0x00006378+4*3))=0x65677261;
*((unsigned int *)((unsigned long)context_ptr+0x00006378+4*4))=0x68542072;
*((unsigned int *)((unsigned long)context_ptr+0x00006378+4*5))=0x42206e61;
*((unsigned int *)((unsigned long)context_ptr+0x00006378+4*6))=0x6b636f6c;
*((unsigned int *)((unsigned long)context_ptr+0x00006378+4*7))=0x7a69532d;
*((unsigned int *)((unsigned long)context_ptr+0x00006378+4*8))=0x654b2065;
*((unsigned int *)((unsigned long)context_ptr+0x00006378+4*9))=0x202d2079;
*((unsigned int *)((unsigned long)context_ptr+0x00006378+4*10))=0x68736148;
*((unsigned int *)((unsigned long)context_ptr+0x00006378+4*11))=0x79654b20;
*((unsigned int *)((unsigned long)context_ptr+0x00006378+4*12))=0x72694620;
*((unsigned int *)((unsigned long)context_ptr+0x00006378+4*13))=0x00007473;
*((unsigned int *)((unsigned long)context_ptr+0x00003078))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003078+4*1))=0x000063b0;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000078))=0x04c00036;
*((unsigned int *)((unsigned long)context_ptr+0x00000078+4*1))=0x00006378;
*((unsigned int *)((unsigned long)context_ptr+0x00000078+4*2))=0x00006368;
*((unsigned int *)((unsigned long)context_ptr+0x00000078+4*3))=0x02220036;
*((unsigned int *)((unsigned long)context_ptr+0x00000078+4*4))=0x089419af;
*((unsigned int *)((unsigned long)context_ptr+0x00000078+4*5))=0x00006168+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x000063cc))=0x026a1002;
*((unsigned int *)((unsigned long)context_ptr+0x000063cc+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000063cc+4*2))=0x02020098;
*((unsigned int *)((unsigned long)context_ptr+0x000063cc+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x000063dc))=0x73696854;
*((unsigned int *)((unsigned long)context_ptr+0x000063dc+4*1))=0x20736920;
*((unsigned int *)((unsigned long)context_ptr+0x000063dc+4*2))=0x65742061;
*((unsigned int *)((unsigned long)context_ptr+0x000063dc+4*3))=0x75207473;
*((unsigned int *)((unsigned long)context_ptr+0x000063dc+4*4))=0x676e6973;
*((unsigned int *)((unsigned long)context_ptr+0x000063dc+4*5))=0x6c206120;
*((unsigned int *)((unsigned long)context_ptr+0x000063dc+4*6))=0x65677261;
*((unsigned int *)((unsigned long)context_ptr+0x000063dc+4*7))=0x68742072;
*((unsigned int *)((unsigned long)context_ptr+0x000063dc+4*8))=0x62206e61;
*((unsigned int *)((unsigned long)context_ptr+0x000063dc+4*9))=0x6b636f6c;
*((unsigned int *)((unsigned long)context_ptr+0x000063dc+4*10))=0x7a69732d;
*((unsigned int *)((unsigned long)context_ptr+0x000063dc+4*11))=0x656b2065;
*((unsigned int *)((unsigned long)context_ptr+0x000063dc+4*12))=0x6e612079;
*((unsigned int *)((unsigned long)context_ptr+0x000063dc+4*13))=0x20612064;
*((unsigned int *)((unsigned long)context_ptr+0x000063dc+4*14))=0x6772616c;
*((unsigned int *)((unsigned long)context_ptr+0x000063dc+4*15))=0x74207265;
*((unsigned int *)((unsigned long)context_ptr+0x000063dc+4*16))=0x206e6168;
*((unsigned int *)((unsigned long)context_ptr+0x000063dc+4*17))=0x636f6c62;
*((unsigned int *)((unsigned long)context_ptr+0x000063dc+4*18))=0x69732d6b;
*((unsigned int *)((unsigned long)context_ptr+0x000063dc+4*19))=0x6420657a;
*((unsigned int *)((unsigned long)context_ptr+0x000063dc+4*20))=0x2e617461;
*((unsigned int *)((unsigned long)context_ptr+0x000063dc+4*21))=0x65685420;
*((unsigned int *)((unsigned long)context_ptr+0x000063dc+4*22))=0x79656b20;
*((unsigned int *)((unsigned long)context_ptr+0x000063dc+4*23))=0x65656e20;
*((unsigned int *)((unsigned long)context_ptr+0x000063dc+4*24))=0x74207364;
*((unsigned int *)((unsigned long)context_ptr+0x000063dc+4*25))=0x6562206f;
*((unsigned int *)((unsigned long)context_ptr+0x000063dc+4*26))=0x73616820;
*((unsigned int *)((unsigned long)context_ptr+0x000063dc+4*27))=0x20646568;
*((unsigned int *)((unsigned long)context_ptr+0x000063dc+4*28))=0x6f666562;
*((unsigned int *)((unsigned long)context_ptr+0x000063dc+4*29))=0x62206572;
*((unsigned int *)((unsigned long)context_ptr+0x000063dc+4*30))=0x676e6965;
*((unsigned int *)((unsigned long)context_ptr+0x000063dc+4*31))=0x65737520;
*((unsigned int *)((unsigned long)context_ptr+0x000063dc+4*32))=0x79622064;
*((unsigned int *)((unsigned long)context_ptr+0x000063dc+4*33))=0x65687420;
*((unsigned int *)((unsigned long)context_ptr+0x000063dc+4*34))=0x414d4820;
*((unsigned int *)((unsigned long)context_ptr+0x000063dc+4*35))=0x6c612043;
*((unsigned int *)((unsigned long)context_ptr+0x000063dc+4*36))=0x69726f67;
*((unsigned int *)((unsigned long)context_ptr+0x000063dc+4*37))=0x2e6d6874;
*((unsigned int *)((unsigned long)context_ptr+0x00003090))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003090+4*1))=0x00006474;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000090))=0x04c00098;
*((unsigned int *)((unsigned long)context_ptr+0x00000090+4*1))=0x000063dc;
*((unsigned int *)((unsigned long)context_ptr+0x00000090+4*2))=0x000063cc;
*((unsigned int *)((unsigned long)context_ptr+0x00000090+4*3))=0x02220098;
*((unsigned int *)((unsigned long)context_ptr+0x00000090+4*4))=0x0e3352f8;
*((unsigned int *)((unsigned long)context_ptr+0x00000090+4*5))=0x000061b0+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000006&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006210,"\x89\x6f\xb1\x12\x8a\xbb\xdf\x19\x68\x32\x10\x7c\xd4\x9d\xf3\x3f\x47\xb4\xb1\x16\x99\x12\xba\x4f\x53\x68\x4b\x22",28))
printf("strip: 896fb1128abbdf19, Pass\n");
else
printf("strip: 896fb1128abbdf19, Failed\n");
writel(0x0000000c&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006258,"\xa3\x0e\x01\x09\x8b\xc6\xdb\xbf\x45\x69\x0f\x3a\x7e\x9e\x6d\x0f\x8b\xbe\xa2\xa3\x9e\x61\x48\x00\x8f\xd0\x5e\x44",28))
printf("strip: a30e01098bc6dbbf, Pass\n");
else
printf("strip: a30e01098bc6dbbf, Failed\n");
writel(0x00000012&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000062b8,"\x7f\xb3\xcb\x35\x88\xc6\xc1\xf6\xff\xa9\x69\x4d\x7d\x6a\xd2\x64\x93\x65\xb0\xc1\xf6\x5d\x69\xd1\xec\x83\x33\xea",28))
printf("strip: 7fb3cb3588c6c1f6, Pass\n");
else
printf("strip: 7fb3cb3588c6c1f6, Failed\n");
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006318,"\x6c\x11\x50\x68\x74\x01\x3c\xac\x6a\x2a\xbc\x1b\xb3\x82\x62\x7c\xec\x6a\x90\xd8\x6e\xfc\x01\x2d\xe7\xaf\xec\x5a",28))
printf("strip: 6c11506874013cac, Pass\n");
else
printf("strip: 6c11506874013cac, Failed\n");
writel(0x0000001e&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006358,"\x0e\x2a\xea\x68\xa9\x0c\x8d\x37\xc9\x88\xbc\xdb\x9f\xca\x6f\xa8",16))
printf("strip: 0e2aea68a90c8d37, Pass\n");
else
printf("strip: 0e2aea68a90c8d37, Failed\n");
writel(0x00000024&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000063b0,"\x95\xe9\xa0\xdb\x96\x20\x95\xad\xae\xbe\x9b\x2d\x6f\x0d\xbc\xe2\xd4\x99\xf1\x12\xf2\xd2\xb7\x27\x3f\xa6\x87\x0e",28))
printf("strip: 95e9a0db962095ad, Pass\n");
else
printf("strip: 95e9a0db962095ad, Failed\n");
writel(0x0000002a&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006474,"\x3a\x85\x41\x66\xac\x5d\x9f\x02\x3f\x54\xd5\x17\xd0\xb3\x9d\xbd\x94\x67\x70\xdb\x9c\x2b\x95\xc9\xf6\xf5\x65\xd1",28))
printf("strip: 3a854166ac5d9f02, Pass\n");
else
printf("strip: 3a854166ac5d9f02, Failed\n");
}

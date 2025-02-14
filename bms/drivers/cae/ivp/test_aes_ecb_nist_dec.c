#include <common.h>
#include <malloc.h>

extern volatile unsigned int ivp_cae_base_addr;

void test_aes_ecb_nist_dec(void)
{
unsigned int *context_ptr=(unsigned int *)0x14000000;
printf("test_aes_ecb_nist_dec\n");
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
*((unsigned int *)((unsigned long)context_ptr+0x00006000))=0x010b0405;
*((unsigned int *)((unsigned long)context_ptr+0x00006000+4*1))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x00006000+4*2))=0x16157e2b;
*((unsigned int *)((unsigned long)context_ptr+0x00006000+4*3))=0xa6d2ae28;
*((unsigned int *)((unsigned long)context_ptr+0x00006000+4*4))=0x8815f7ab;
*((unsigned int *)((unsigned long)context_ptr+0x00006000+4*5))=0x3c4fcf09;
*((unsigned int *)((unsigned long)context_ptr+0x00006018))=0x010d0605;
*((unsigned int *)((unsigned long)context_ptr+0x00006018+4*1))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x00006018+4*2))=0xf7b0738e;
*((unsigned int *)((unsigned long)context_ptr+0x00006018+4*3))=0x52640eda;
*((unsigned int *)((unsigned long)context_ptr+0x00006018+4*4))=0x2bf310c8;
*((unsigned int *)((unsigned long)context_ptr+0x00006018+4*5))=0xe5799080;
*((unsigned int *)((unsigned long)context_ptr+0x00006018+4*6))=0xd2eaf862;
*((unsigned int *)((unsigned long)context_ptr+0x00006018+4*7))=0x7b6b2c52;
*((unsigned int *)((unsigned long)context_ptr+0x00006038))=0x010f0805;
*((unsigned int *)((unsigned long)context_ptr+0x00006038+4*1))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x00006038+4*2))=0x10eb3d60;
*((unsigned int *)((unsigned long)context_ptr+0x00006038+4*3))=0xbe71ca15;
*((unsigned int *)((unsigned long)context_ptr+0x00006038+4*4))=0xf0ae732b;
*((unsigned int *)((unsigned long)context_ptr+0x00006038+4*5))=0x81777d85;
*((unsigned int *)((unsigned long)context_ptr+0x00006038+4*6))=0x072c351f;
*((unsigned int *)((unsigned long)context_ptr+0x00006038+4*7))=0xd708613b;
*((unsigned int *)((unsigned long)context_ptr+0x00006038+4*8))=0xa310982d;
*((unsigned int *)((unsigned long)context_ptr+0x00006038+4*9))=0xf4df1409;
*((unsigned int *)((unsigned long)context_ptr+0x00006060))=0x010b0405;
*((unsigned int *)((unsigned long)context_ptr+0x00006060+4*1))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x00006060+4*2))=0x0d060040;
*((unsigned int *)((unsigned long)context_ptr+0x0000606c))=0xb47bd73a;
*((unsigned int *)((unsigned long)context_ptr+0x0000606c+4*1))=0x60367a0d;
*((unsigned int *)((unsigned long)context_ptr+0x0000606c+4*2))=0xf3ca9ea8;
*((unsigned int *)((unsigned long)context_ptr+0x0000606c+4*3))=0x97ef6624;
*((unsigned int *)((unsigned long)context_ptr+0x0000606c+4*4))=0x85d5d3f5;
*((unsigned int *)((unsigned long)context_ptr+0x0000606c+4*5))=0x9d69b903;
*((unsigned int *)((unsigned long)context_ptr+0x0000606c+4*6))=0x5a8985e7;
*((unsigned int *)((unsigned long)context_ptr+0x0000606c+4*7))=0xafbafd96;
*((unsigned int *)((unsigned long)context_ptr+0x0000606c+4*8))=0x7fcdb143;
*((unsigned int *)((unsigned long)context_ptr+0x0000606c+4*9))=0x23ce8e59;
*((unsigned int *)((unsigned long)context_ptr+0x0000606c+4*10))=0xe3001b88;
*((unsigned int *)((unsigned long)context_ptr+0x0000606c+4*11))=0x880603ed;
*((unsigned int *)((unsigned long)context_ptr+0x0000606c+4*12))=0x5e780c7b;
*((unsigned int *)((unsigned long)context_ptr+0x0000606c+4*13))=0x3fade827;
*((unsigned int *)((unsigned long)context_ptr+0x0000606c+4*14))=0x71202382;
*((unsigned int *)((unsigned long)context_ptr+0x0000606c+4*15))=0xd45d7204;
*((unsigned int *)((unsigned long)context_ptr+0x00003000))=0x04c00040;
*((unsigned int *)((unsigned long)context_ptr+0x00003000+4*1))=0x000060ac;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000000))=0x03c00040;
*((unsigned int *)((unsigned long)context_ptr+0x00000000+4*1))=0x0000606c;
*((unsigned int *)((unsigned long)context_ptr+0x00000000+4*2))=0x00006060;
*((unsigned int *)((unsigned long)context_ptr+0x00000000+4*3))=0x02220040;
*((unsigned int *)((unsigned long)context_ptr+0x00000000+4*4))=0x005b1654;
*((unsigned int *)((unsigned long)context_ptr+0x00000000+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x000060ec))=0x010d0605;
*((unsigned int *)((unsigned long)context_ptr+0x000060ec+4*1))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x000060ec+4*2))=0x0d060040;
*((unsigned int *)((unsigned long)context_ptr+0x000060f8))=0x1d4f33bd;
*((unsigned int *)((unsigned long)context_ptr+0x000060f8+4*1))=0x5ff2456e;
*((unsigned int *)((unsigned long)context_ptr+0x000060f8+4*2))=0x14a212f7;
*((unsigned int *)((unsigned long)context_ptr+0x000060f8+4*3))=0xcca51f57;
*((unsigned int *)((unsigned long)context_ptr+0x000060f8+4*4))=0x84044197;
*((unsigned int *)((unsigned long)context_ptr+0x000060f8+4*5))=0xadd30a6d;
*((unsigned int *)((unsigned long)context_ptr+0x000060f8+4*6))=0xb3ec3477;
*((unsigned int *)((unsigned long)context_ptr+0x000060f8+4*7))=0xef4eeeec;
*((unsigned int *)((unsigned long)context_ptr+0x000060f8+4*8))=0x22fd7aef;
*((unsigned int *)((unsigned long)context_ptr+0x000060f8+4*9))=0x0ae6e270;
*((unsigned int *)((unsigned long)context_ptr+0x000060f8+4*10))=0x2fbae0dc;
*((unsigned int *)((unsigned long)context_ptr+0x000060f8+4*11))=0x4e44e6ac;
*((unsigned int *)((unsigned long)context_ptr+0x000060f8+4*12))=0xba414b9a;
*((unsigned int *)((unsigned long)context_ptr+0x000060f8+4*13))=0x726c8d73;
*((unsigned int *)((unsigned long)context_ptr+0x000060f8+4*14))=0x166916fb;
*((unsigned int *)((unsigned long)context_ptr+0x000060f8+4*15))=0x0e8ec103;
*((unsigned int *)((unsigned long)context_ptr+0x00003018))=0x04c00040;
*((unsigned int *)((unsigned long)context_ptr+0x00003018+4*1))=0x00006138;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000018))=0x03c00040;
*((unsigned int *)((unsigned long)context_ptr+0x00000018+4*1))=0x000060f8;
*((unsigned int *)((unsigned long)context_ptr+0x00000018+4*2))=0x000060ec;
*((unsigned int *)((unsigned long)context_ptr+0x00000018+4*3))=0x02220040;
*((unsigned int *)((unsigned long)context_ptr+0x00000018+4*4))=0x0090e7e1;
*((unsigned int *)((unsigned long)context_ptr+0x00000018+4*5))=0x00006018+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x00006178))=0x010f0805;
*((unsigned int *)((unsigned long)context_ptr+0x00006178+4*1))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x00006178+4*2))=0x0d060040;
*((unsigned int *)((unsigned long)context_ptr+0x00006184))=0xbdd1eef3;
*((unsigned int *)((unsigned long)context_ptr+0x00006184+4*1))=0x3ca0d2b5;
*((unsigned int *)((unsigned long)context_ptr+0x00006184+4*2))=0x7e5a4b06;
*((unsigned int *)((unsigned long)context_ptr+0x00006184+4*3))=0xf881b13d;
*((unsigned int *)((unsigned long)context_ptr+0x00006184+4*4))=0x10cb1c59;
*((unsigned int *)((unsigned long)context_ptr+0x00006184+4*5))=0x26ed10d4;
*((unsigned int *)((unsigned long)context_ptr+0x00006184+4*6))=0x4aa75bdc;
*((unsigned int *)((unsigned long)context_ptr+0x00006184+4*7))=0x70283631;
*((unsigned int *)((unsigned long)context_ptr+0x00006184+4*8))=0xb921edb6;
*((unsigned int *)((unsigned long)context_ptr+0x00006184+4*9))=0xf9f4a69c;
*((unsigned int *)((unsigned long)context_ptr+0x00006184+4*10))=0xb1e753f1;
*((unsigned int *)((unsigned long)context_ptr+0x00006184+4*11))=0x1dedafbe;
*((unsigned int *)((unsigned long)context_ptr+0x00006184+4*12))=0x7a4b3023;
*((unsigned int *)((unsigned long)context_ptr+0x00006184+4*13))=0xfff3f939;
*((unsigned int *)((unsigned long)context_ptr+0x00006184+4*14))=0x8f8d7d06;
*((unsigned int *)((unsigned long)context_ptr+0x00006184+4*15))=0xc7ec249e;
*((unsigned int *)((unsigned long)context_ptr+0x00003030))=0x04c00040;
*((unsigned int *)((unsigned long)context_ptr+0x00003030+4*1))=0x000061c4;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000030))=0x03c00040;
*((unsigned int *)((unsigned long)context_ptr+0x00000030+4*1))=0x00006184;
*((unsigned int *)((unsigned long)context_ptr+0x00000030+4*2))=0x00006178;
*((unsigned int *)((unsigned long)context_ptr+0x00000030+4*3))=0x02220040;
*((unsigned int *)((unsigned long)context_ptr+0x00000030+4*4))=0x00bf4dde;
*((unsigned int *)((unsigned long)context_ptr+0x00000030+4*5))=0x00006038+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000006&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000060ac,"\x6b\xc1\xbe\xe2\x2e\x40\x9f\x96\xe9\x3d\x7e\x11\x73\x93\x17\x2a\xae\x2d\x8a\x57\x1e\x03\xac\x9c\x9e\xb7\x6f\xac\x45\xaf\x8e\x51\x30\xc8\x1c\x46\xa3\x5c\xe4\x11\xe5\xfb\xc1\x19\x1a\x0a\x52\xef\xf6\x9f\x24\x45\xdf\x4f\x9b\x17\xad\x2b\x41\x7b\xe6\x6c\x37\x10",64))
printf("strip: 6bc1bee22e409f96, Pass\n");
else
printf("strip: 6bc1bee22e409f96, Failed\n");
writel(0x0000000c&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006138,"\x6b\xc1\xbe\xe2\x2e\x40\x9f\x96\xe9\x3d\x7e\x11\x73\x93\x17\x2a\xae\x2d\x8a\x57\x1e\x03\xac\x9c\x9e\xb7\x6f\xac\x45\xaf\x8e\x51\x30\xc8\x1c\x46\xa3\x5c\xe4\x11\xe5\xfb\xc1\x19\x1a\x0a\x52\xef\xf6\x9f\x24\x45\xdf\x4f\x9b\x17\xad\x2b\x41\x7b\xe6\x6c\x37\x10",64))
printf("strip: 6bc1bee22e409f96, Pass\n");
else
printf("strip: 6bc1bee22e409f96, Failed\n");
writel(0x00000012&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000061c4,"\x6b\xc1\xbe\xe2\x2e\x40\x9f\x96\xe9\x3d\x7e\x11\x73\x93\x17\x2a\xae\x2d\x8a\x57\x1e\x03\xac\x9c\x9e\xb7\x6f\xac\x45\xaf\x8e\x51\x30\xc8\x1c\x46\xa3\x5c\xe4\x11\xe5\xfb\xc1\x19\x1a\x0a\x52\xef\xf6\x9f\x24\x45\xdf\x4f\x9b\x17\xad\x2b\x41\x7b\xe6\x6c\x37\x10",64))
printf("strip: 6bc1bee22e409f96, Pass\n");
else
printf("strip: 6bc1bee22e409f96, Failed\n");
}

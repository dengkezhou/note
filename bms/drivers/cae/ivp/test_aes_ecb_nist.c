#include <common.h>
#include <malloc.h>

extern volatile unsigned int ivp_cae_base_addr;

void test_aes_ecb_nist(void)
{
unsigned int *context_ptr=(unsigned int *)0x14000000;
printf("test_aes_ecb_nist\n");
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
*((unsigned int *)((unsigned long)context_ptr+0x00006000))=0x010b0404;
*((unsigned int *)((unsigned long)context_ptr+0x00006000+4*1))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x00006000+4*2))=0x16157e2b;
*((unsigned int *)((unsigned long)context_ptr+0x00006000+4*3))=0xa6d2ae28;
*((unsigned int *)((unsigned long)context_ptr+0x00006000+4*4))=0x8815f7ab;
*((unsigned int *)((unsigned long)context_ptr+0x00006000+4*5))=0x3c4fcf09;
*((unsigned int *)((unsigned long)context_ptr+0x00006018))=0x010d0604;
*((unsigned int *)((unsigned long)context_ptr+0x00006018+4*1))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x00006018+4*2))=0xf7b0738e;
*((unsigned int *)((unsigned long)context_ptr+0x00006018+4*3))=0x52640eda;
*((unsigned int *)((unsigned long)context_ptr+0x00006018+4*4))=0x2bf310c8;
*((unsigned int *)((unsigned long)context_ptr+0x00006018+4*5))=0xe5799080;
*((unsigned int *)((unsigned long)context_ptr+0x00006018+4*6))=0xd2eaf862;
*((unsigned int *)((unsigned long)context_ptr+0x00006018+4*7))=0x7b6b2c52;
*((unsigned int *)((unsigned long)context_ptr+0x00006038))=0x010f0804;
*((unsigned int *)((unsigned long)context_ptr+0x00006038+4*1))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x00006038+4*2))=0x10eb3d60;
*((unsigned int *)((unsigned long)context_ptr+0x00006038+4*3))=0xbe71ca15;
*((unsigned int *)((unsigned long)context_ptr+0x00006038+4*4))=0xf0ae732b;
*((unsigned int *)((unsigned long)context_ptr+0x00006038+4*5))=0x81777d85;
*((unsigned int *)((unsigned long)context_ptr+0x00006038+4*6))=0x072c351f;
*((unsigned int *)((unsigned long)context_ptr+0x00006038+4*7))=0xd708613b;
*((unsigned int *)((unsigned long)context_ptr+0x00006038+4*8))=0xa310982d;
*((unsigned int *)((unsigned long)context_ptr+0x00006038+4*9))=0xf4df1409;
*((unsigned int *)((unsigned long)context_ptr+0x00006060))=0x010b0404;
*((unsigned int *)((unsigned long)context_ptr+0x00006060+4*1))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x00006060+4*2))=0x0d060040;
*((unsigned int *)((unsigned long)context_ptr+0x0000606c))=0xe2bec16b;
*((unsigned int *)((unsigned long)context_ptr+0x0000606c+4*1))=0x969f402e;
*((unsigned int *)((unsigned long)context_ptr+0x0000606c+4*2))=0x117e3de9;
*((unsigned int *)((unsigned long)context_ptr+0x0000606c+4*3))=0x2a179373;
*((unsigned int *)((unsigned long)context_ptr+0x0000606c+4*4))=0x578a2dae;
*((unsigned int *)((unsigned long)context_ptr+0x0000606c+4*5))=0x9cac031e;
*((unsigned int *)((unsigned long)context_ptr+0x0000606c+4*6))=0xac6fb79e;
*((unsigned int *)((unsigned long)context_ptr+0x0000606c+4*7))=0x518eaf45;
*((unsigned int *)((unsigned long)context_ptr+0x0000606c+4*8))=0x461cc830;
*((unsigned int *)((unsigned long)context_ptr+0x0000606c+4*9))=0x11e45ca3;
*((unsigned int *)((unsigned long)context_ptr+0x0000606c+4*10))=0x19c1fbe5;
*((unsigned int *)((unsigned long)context_ptr+0x0000606c+4*11))=0xef520a1a;
*((unsigned int *)((unsigned long)context_ptr+0x0000606c+4*12))=0x45249ff6;
*((unsigned int *)((unsigned long)context_ptr+0x0000606c+4*13))=0x179b4fdf;
*((unsigned int *)((unsigned long)context_ptr+0x0000606c+4*14))=0x7b412bad;
*((unsigned int *)((unsigned long)context_ptr+0x0000606c+4*15))=0x10376ce6;
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
*((unsigned int *)((unsigned long)context_ptr+0x000060ec))=0x010d0604;
*((unsigned int *)((unsigned long)context_ptr+0x000060ec+4*1))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x000060ec+4*2))=0x0d060040;
*((unsigned int *)((unsigned long)context_ptr+0x000060f8))=0xe2bec16b;
*((unsigned int *)((unsigned long)context_ptr+0x000060f8+4*1))=0x969f402e;
*((unsigned int *)((unsigned long)context_ptr+0x000060f8+4*2))=0x117e3de9;
*((unsigned int *)((unsigned long)context_ptr+0x000060f8+4*3))=0x2a179373;
*((unsigned int *)((unsigned long)context_ptr+0x000060f8+4*4))=0x578a2dae;
*((unsigned int *)((unsigned long)context_ptr+0x000060f8+4*5))=0x9cac031e;
*((unsigned int *)((unsigned long)context_ptr+0x000060f8+4*6))=0xac6fb79e;
*((unsigned int *)((unsigned long)context_ptr+0x000060f8+4*7))=0x518eaf45;
*((unsigned int *)((unsigned long)context_ptr+0x000060f8+4*8))=0x461cc830;
*((unsigned int *)((unsigned long)context_ptr+0x000060f8+4*9))=0x11e45ca3;
*((unsigned int *)((unsigned long)context_ptr+0x000060f8+4*10))=0x19c1fbe5;
*((unsigned int *)((unsigned long)context_ptr+0x000060f8+4*11))=0xef520a1a;
*((unsigned int *)((unsigned long)context_ptr+0x000060f8+4*12))=0x45249ff6;
*((unsigned int *)((unsigned long)context_ptr+0x000060f8+4*13))=0x179b4fdf;
*((unsigned int *)((unsigned long)context_ptr+0x000060f8+4*14))=0x7b412bad;
*((unsigned int *)((unsigned long)context_ptr+0x000060f8+4*15))=0x10376ce6;
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
*((unsigned int *)((unsigned long)context_ptr+0x00006178))=0x010f0804;
*((unsigned int *)((unsigned long)context_ptr+0x00006178+4*1))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x00006178+4*2))=0x0d060040;
*((unsigned int *)((unsigned long)context_ptr+0x00006184))=0xe2bec16b;
*((unsigned int *)((unsigned long)context_ptr+0x00006184+4*1))=0x969f402e;
*((unsigned int *)((unsigned long)context_ptr+0x00006184+4*2))=0x117e3de9;
*((unsigned int *)((unsigned long)context_ptr+0x00006184+4*3))=0x2a179373;
*((unsigned int *)((unsigned long)context_ptr+0x00006184+4*4))=0x578a2dae;
*((unsigned int *)((unsigned long)context_ptr+0x00006184+4*5))=0x9cac031e;
*((unsigned int *)((unsigned long)context_ptr+0x00006184+4*6))=0xac6fb79e;
*((unsigned int *)((unsigned long)context_ptr+0x00006184+4*7))=0x518eaf45;
*((unsigned int *)((unsigned long)context_ptr+0x00006184+4*8))=0x461cc830;
*((unsigned int *)((unsigned long)context_ptr+0x00006184+4*9))=0x11e45ca3;
*((unsigned int *)((unsigned long)context_ptr+0x00006184+4*10))=0x19c1fbe5;
*((unsigned int *)((unsigned long)context_ptr+0x00006184+4*11))=0xef520a1a;
*((unsigned int *)((unsigned long)context_ptr+0x00006184+4*12))=0x45249ff6;
*((unsigned int *)((unsigned long)context_ptr+0x00006184+4*13))=0x179b4fdf;
*((unsigned int *)((unsigned long)context_ptr+0x00006184+4*14))=0x7b412bad;
*((unsigned int *)((unsigned long)context_ptr+0x00006184+4*15))=0x10376ce6;
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
if(!memcmp((unsigned char *)context_ptr+0x000060ac,"\x3a\xd7\x7b\xb4\x0d\x7a\x36\x60\xa8\x9e\xca\xf3\x24\x66\xef\x97\xf5\xd3\xd5\x85\x03\xb9\x69\x9d\xe7\x85\x89\x5a\x96\xfd\xba\xaf\x43\xb1\xcd\x7f\x59\x8e\xce\x23\x88\x1b\x00\xe3\xed\x03\x06\x88\x7b\x0c\x78\x5e\x27\xe8\xad\x3f\x82\x23\x20\x71\x04\x72\x5d\xd4",64))
printf("strip: 3ad77bb40d7a3660, Pass\n");
else
printf("strip: 3ad77bb40d7a3660, Failed\n");
writel(0x0000000c&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006138,"\xbd\x33\x4f\x1d\x6e\x45\xf2\x5f\xf7\x12\xa2\x14\x57\x1f\xa5\xcc\x97\x41\x04\x84\x6d\x0a\xd3\xad\x77\x34\xec\xb3\xec\xee\x4e\xef\xef\x7a\xfd\x22\x70\xe2\xe6\x0a\xdc\xe0\xba\x2f\xac\xe6\x44\x4e\x9a\x4b\x41\xba\x73\x8d\x6c\x72\xfb\x16\x69\x16\x03\xc1\x8e\x0e",64))
printf("strip: bd334f1d6e45f25f, Pass\n");
else
printf("strip: bd334f1d6e45f25f, Failed\n");
writel(0x00000012&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000061c4,"\xf3\xee\xd1\xbd\xb5\xd2\xa0\x3c\x06\x4b\x5a\x7e\x3d\xb1\x81\xf8\x59\x1c\xcb\x10\xd4\x10\xed\x26\xdc\x5b\xa7\x4a\x31\x36\x28\x70\xb6\xed\x21\xb9\x9c\xa6\xf4\xf9\xf1\x53\xe7\xb1\xbe\xaf\xed\x1d\x23\x30\x4b\x7a\x39\xf9\xf3\xff\x06\x7d\x8d\x8f\x9e\x24\xec\xc7",64))
printf("strip: f3eed1bdb5d2a03c, Pass\n");
else
printf("strip: f3eed1bdb5d2a03c, Failed\n");
}

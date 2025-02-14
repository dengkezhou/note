#include <common.h>
#include <malloc.h>

extern volatile unsigned int ivp_cae_base_addr;

void test_aes_cbc_nist(void)
{
unsigned int *context_ptr=(unsigned int *)0x14000000;
printf("test_aes_cbc_nist\n");
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
*((unsigned int *)((unsigned long)context_ptr+0x00006000))=0x010b0804;
*((unsigned int *)((unsigned long)context_ptr+0x00006000+4*1))=0x000001e1;
*((unsigned int *)((unsigned long)context_ptr+0x00006000+4*2))=0x16157e2b;
*((unsigned int *)((unsigned long)context_ptr+0x00006000+4*3))=0xa6d2ae28;
*((unsigned int *)((unsigned long)context_ptr+0x00006000+4*4))=0x8815f7ab;
*((unsigned int *)((unsigned long)context_ptr+0x00006000+4*5))=0x3c4fcf09;
*((unsigned int *)((unsigned long)context_ptr+0x00006000+4*6))=0x03020100;
*((unsigned int *)((unsigned long)context_ptr+0x00006000+4*7))=0x07060504;
*((unsigned int *)((unsigned long)context_ptr+0x00006000+4*8))=0x0b0a0908;
*((unsigned int *)((unsigned long)context_ptr+0x00006000+4*9))=0x0f0e0d0c;
*((unsigned int *)((unsigned long)context_ptr+0x00006028))=0x010d0a04;
*((unsigned int *)((unsigned long)context_ptr+0x00006028+4*1))=0x000001e1;
*((unsigned int *)((unsigned long)context_ptr+0x00006028+4*2))=0xf7b0738e;
*((unsigned int *)((unsigned long)context_ptr+0x00006028+4*3))=0x52640eda;
*((unsigned int *)((unsigned long)context_ptr+0x00006028+4*4))=0x2bf310c8;
*((unsigned int *)((unsigned long)context_ptr+0x00006028+4*5))=0xe5799080;
*((unsigned int *)((unsigned long)context_ptr+0x00006028+4*6))=0xd2eaf862;
*((unsigned int *)((unsigned long)context_ptr+0x00006028+4*7))=0x7b6b2c52;
*((unsigned int *)((unsigned long)context_ptr+0x00006028+4*8))=0x03020100;
*((unsigned int *)((unsigned long)context_ptr+0x00006028+4*9))=0x07060504;
*((unsigned int *)((unsigned long)context_ptr+0x00006028+4*10))=0x0b0a0908;
*((unsigned int *)((unsigned long)context_ptr+0x00006028+4*11))=0x0f0e0d0c;
*((unsigned int *)((unsigned long)context_ptr+0x00006058))=0x010f0c04;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*1))=0x000001e1;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*2))=0x10eb3d60;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*3))=0xbe71ca15;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*4))=0xf0ae732b;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*5))=0x81777d85;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*6))=0x072c351f;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*7))=0xd708613b;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*8))=0xa310982d;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*9))=0xf4df1409;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*10))=0x03020100;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*11))=0x07060504;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*12))=0x0b0a0908;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*13))=0x0f0e0d0c;
*((unsigned int *)((unsigned long)context_ptr+0x00006090))=0x010b0804;
*((unsigned int *)((unsigned long)context_ptr+0x00006090+4*1))=0x000001e1;
*((unsigned int *)((unsigned long)context_ptr+0x00006090+4*2))=0x0d060040;
*((unsigned int *)((unsigned long)context_ptr+0x0000609c))=0xe2bec16b;
*((unsigned int *)((unsigned long)context_ptr+0x0000609c+4*1))=0x969f402e;
*((unsigned int *)((unsigned long)context_ptr+0x0000609c+4*2))=0x117e3de9;
*((unsigned int *)((unsigned long)context_ptr+0x0000609c+4*3))=0x2a179373;
*((unsigned int *)((unsigned long)context_ptr+0x0000609c+4*4))=0x578a2dae;
*((unsigned int *)((unsigned long)context_ptr+0x0000609c+4*5))=0x9cac031e;
*((unsigned int *)((unsigned long)context_ptr+0x0000609c+4*6))=0xac6fb79e;
*((unsigned int *)((unsigned long)context_ptr+0x0000609c+4*7))=0x518eaf45;
*((unsigned int *)((unsigned long)context_ptr+0x0000609c+4*8))=0x461cc830;
*((unsigned int *)((unsigned long)context_ptr+0x0000609c+4*9))=0x11e45ca3;
*((unsigned int *)((unsigned long)context_ptr+0x0000609c+4*10))=0x19c1fbe5;
*((unsigned int *)((unsigned long)context_ptr+0x0000609c+4*11))=0xef520a1a;
*((unsigned int *)((unsigned long)context_ptr+0x0000609c+4*12))=0x45249ff6;
*((unsigned int *)((unsigned long)context_ptr+0x0000609c+4*13))=0x179b4fdf;
*((unsigned int *)((unsigned long)context_ptr+0x0000609c+4*14))=0x7b412bad;
*((unsigned int *)((unsigned long)context_ptr+0x0000609c+4*15))=0x10376ce6;
*((unsigned int *)((unsigned long)context_ptr+0x00003000))=0x04c00040;
*((unsigned int *)((unsigned long)context_ptr+0x00003000+4*1))=0x000060dc;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000000+4*1))=0x0000609c;
*((unsigned int *)((unsigned long)context_ptr+0x00000000+4*2))=0x00006090;
*((unsigned int *)((unsigned long)context_ptr+0x00000000+4*3))=0x02220040;
*((unsigned int *)((unsigned long)context_ptr+0x00000000+4*4))=0x002d4ba5;
*((unsigned int *)((unsigned long)context_ptr+0x00000000+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x0000611c))=0x010d0a04;
*((unsigned int *)((unsigned long)context_ptr+0x0000611c+4*1))=0x000001e1;
*((unsigned int *)((unsigned long)context_ptr+0x0000611c+4*2))=0x0d060040;
*((unsigned int *)((unsigned long)context_ptr+0x00006128))=0xe2bec16b;
*((unsigned int *)((unsigned long)context_ptr+0x00006128+4*1))=0x969f402e;
*((unsigned int *)((unsigned long)context_ptr+0x00006128+4*2))=0x117e3de9;
*((unsigned int *)((unsigned long)context_ptr+0x00006128+4*3))=0x2a179373;
*((unsigned int *)((unsigned long)context_ptr+0x00006128+4*4))=0x578a2dae;
*((unsigned int *)((unsigned long)context_ptr+0x00006128+4*5))=0x9cac031e;
*((unsigned int *)((unsigned long)context_ptr+0x00006128+4*6))=0xac6fb79e;
*((unsigned int *)((unsigned long)context_ptr+0x00006128+4*7))=0x518eaf45;
*((unsigned int *)((unsigned long)context_ptr+0x00006128+4*8))=0x461cc830;
*((unsigned int *)((unsigned long)context_ptr+0x00006128+4*9))=0x11e45ca3;
*((unsigned int *)((unsigned long)context_ptr+0x00006128+4*10))=0x19c1fbe5;
*((unsigned int *)((unsigned long)context_ptr+0x00006128+4*11))=0xef520a1a;
*((unsigned int *)((unsigned long)context_ptr+0x00006128+4*12))=0x45249ff6;
*((unsigned int *)((unsigned long)context_ptr+0x00006128+4*13))=0x179b4fdf;
*((unsigned int *)((unsigned long)context_ptr+0x00006128+4*14))=0x7b412bad;
*((unsigned int *)((unsigned long)context_ptr+0x00006128+4*15))=0x10376ce6;
*((unsigned int *)((unsigned long)context_ptr+0x00003018))=0x04c00040;
*((unsigned int *)((unsigned long)context_ptr+0x00003018+4*1))=0x00006168;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000018+4*1))=0x00006128;
*((unsigned int *)((unsigned long)context_ptr+0x00000018+4*2))=0x0000611c;
*((unsigned int *)((unsigned long)context_ptr+0x00000018+4*3))=0x02220040;
*((unsigned int *)((unsigned long)context_ptr+0x00000018+4*4))=0x00ed7a6e;
*((unsigned int *)((unsigned long)context_ptr+0x00000018+4*5))=0x00006028+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x000061a8))=0x010f0c04;
*((unsigned int *)((unsigned long)context_ptr+0x000061a8+4*1))=0x000001e1;
*((unsigned int *)((unsigned long)context_ptr+0x000061a8+4*2))=0x0d060040;
*((unsigned int *)((unsigned long)context_ptr+0x000061b4))=0xe2bec16b;
*((unsigned int *)((unsigned long)context_ptr+0x000061b4+4*1))=0x969f402e;
*((unsigned int *)((unsigned long)context_ptr+0x000061b4+4*2))=0x117e3de9;
*((unsigned int *)((unsigned long)context_ptr+0x000061b4+4*3))=0x2a179373;
*((unsigned int *)((unsigned long)context_ptr+0x000061b4+4*4))=0x578a2dae;
*((unsigned int *)((unsigned long)context_ptr+0x000061b4+4*5))=0x9cac031e;
*((unsigned int *)((unsigned long)context_ptr+0x000061b4+4*6))=0xac6fb79e;
*((unsigned int *)((unsigned long)context_ptr+0x000061b4+4*7))=0x518eaf45;
*((unsigned int *)((unsigned long)context_ptr+0x000061b4+4*8))=0x461cc830;
*((unsigned int *)((unsigned long)context_ptr+0x000061b4+4*9))=0x11e45ca3;
*((unsigned int *)((unsigned long)context_ptr+0x000061b4+4*10))=0x19c1fbe5;
*((unsigned int *)((unsigned long)context_ptr+0x000061b4+4*11))=0xef520a1a;
*((unsigned int *)((unsigned long)context_ptr+0x000061b4+4*12))=0x45249ff6;
*((unsigned int *)((unsigned long)context_ptr+0x000061b4+4*13))=0x179b4fdf;
*((unsigned int *)((unsigned long)context_ptr+0x000061b4+4*14))=0x7b412bad;
*((unsigned int *)((unsigned long)context_ptr+0x000061b4+4*15))=0x10376ce6;
*((unsigned int *)((unsigned long)context_ptr+0x00003030))=0x04c00040;
*((unsigned int *)((unsigned long)context_ptr+0x00003030+4*1))=0x000061f4;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000030+4*1))=0x000061b4;
*((unsigned int *)((unsigned long)context_ptr+0x00000030+4*2))=0x000061a8;
*((unsigned int *)((unsigned long)context_ptr+0x00000030+4*3))=0x02220040;
*((unsigned int *)((unsigned long)context_ptr+0x00000030+4*4))=0x00675e0c;
*((unsigned int *)((unsigned long)context_ptr+0x00000030+4*5))=0x00006058+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000006&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000060dc,"\x76\x49\xab\xac\x81\x19\xb2\x46\xce\xe9\x8e\x9b\x12\xe9\x19\x7d\x50\x86\xcb\x9b\x50\x72\x19\xee\x95\xdb\x11\x3a\x91\x76\x78\xb2\x73\xbe\xd6\xb8\xe3\xc1\x74\x3b\x71\x16\xe6\x9e\x22\x22\x95\x16\x3f\xf1\xca\xa1\x68\x1f\xac\x09\x12\x0e\xca\x30\x75\x86\xe1\xa7",64))
printf("strip: 7649abac8119b246, Pass\n");
else
printf("strip: 7649abac8119b246, Failed\n");
writel(0x0000000c&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006168,"\x4f\x02\x1d\xb2\x43\xbc\x63\x3d\x71\x78\x18\x3a\x9f\xa0\x71\xe8\xb4\xd9\xad\xa9\xad\x7d\xed\xf4\xe5\xe7\x38\x76\x3f\x69\x14\x5a\x57\x1b\x24\x20\x12\xfb\x7a\xe0\x7f\xa9\xba\xac\x3d\xf1\x02\xe0\x08\xb0\xe2\x79\x88\x59\x88\x81\xd9\x20\xa9\xe6\x4f\x56\x15\xcd",64))
printf("strip: 4f021db243bc633d, Pass\n");
else
printf("strip: 4f021db243bc633d, Failed\n");
writel(0x00000012&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000061f4,"\xf5\x8c\x4c\x04\xd6\xe5\xf1\xba\x77\x9e\xab\xfb\x5f\x7b\xfb\xd6\x9c\xfc\x4e\x96\x7e\xdb\x80\x8d\x67\x9f\x77\x7b\xc6\x70\x2c\x7d\x39\xf2\x33\x69\xa9\xd9\xba\xcf\xa5\x30\xe2\x63\x04\x23\x14\x61\xb2\xeb\x05\xe2\xc3\x9b\xe9\xfc\xda\x6c\x19\x07\x8c\x6a\x9d\x1b",64))
printf("strip: f58c4c04d6e5f1ba, Pass\n");
else
printf("strip: f58c4c04d6e5f1ba, Failed\n");
}

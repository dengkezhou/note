#include <common.h>
#include <malloc.h>

extern volatile unsigned int ivp_cae_base_addr;

void test_aes_ctr_nist(void)
{
unsigned int *context_ptr=(unsigned int *)0x14000000;
printf("test_aes_ctr_nist\n");
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
*((unsigned int *)((unsigned long)context_ptr+0x00006000+4*1))=0x000001e6;
*((unsigned int *)((unsigned long)context_ptr+0x00006000+4*2))=0x16157e2b;
*((unsigned int *)((unsigned long)context_ptr+0x00006000+4*3))=0xa6d2ae28;
*((unsigned int *)((unsigned long)context_ptr+0x00006000+4*4))=0x8815f7ab;
*((unsigned int *)((unsigned long)context_ptr+0x00006000+4*5))=0x3c4fcf09;
*((unsigned int *)((unsigned long)context_ptr+0x00006000+4*6))=0xf3f2f1f0;
*((unsigned int *)((unsigned long)context_ptr+0x00006000+4*7))=0xf7f6f5f4;
*((unsigned int *)((unsigned long)context_ptr+0x00006000+4*8))=0xfbfaf9f8;
*((unsigned int *)((unsigned long)context_ptr+0x00006000+4*9))=0xfffefdfc;
*((unsigned int *)((unsigned long)context_ptr+0x00006028))=0x010d0a04;
*((unsigned int *)((unsigned long)context_ptr+0x00006028+4*1))=0x000001e6;
*((unsigned int *)((unsigned long)context_ptr+0x00006028+4*2))=0xf7b0738e;
*((unsigned int *)((unsigned long)context_ptr+0x00006028+4*3))=0x52640eda;
*((unsigned int *)((unsigned long)context_ptr+0x00006028+4*4))=0x2bf310c8;
*((unsigned int *)((unsigned long)context_ptr+0x00006028+4*5))=0xe5799080;
*((unsigned int *)((unsigned long)context_ptr+0x00006028+4*6))=0xd2eaf862;
*((unsigned int *)((unsigned long)context_ptr+0x00006028+4*7))=0x7b6b2c52;
*((unsigned int *)((unsigned long)context_ptr+0x00006028+4*8))=0xf3f2f1f0;
*((unsigned int *)((unsigned long)context_ptr+0x00006028+4*9))=0xf7f6f5f4;
*((unsigned int *)((unsigned long)context_ptr+0x00006028+4*10))=0xfbfaf9f8;
*((unsigned int *)((unsigned long)context_ptr+0x00006028+4*11))=0xfffefdfc;
*((unsigned int *)((unsigned long)context_ptr+0x00006058))=0x010f0c04;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*1))=0x000001e6;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*2))=0x10eb3d60;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*3))=0xbe71ca15;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*4))=0xf0ae732b;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*5))=0x81777d85;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*6))=0x072c351f;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*7))=0xd708613b;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*8))=0xa310982d;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*9))=0xf4df1409;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*10))=0xf3f2f1f0;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*11))=0xf7f6f5f4;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*12))=0xfbfaf9f8;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*13))=0xfffefdfc;
*((unsigned int *)((unsigned long)context_ptr+0x00006090))=0x010b0804;
*((unsigned int *)((unsigned long)context_ptr+0x00006090+4*1))=0x000001e6;
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
*((unsigned int *)((unsigned long)context_ptr+0x0000611c+4*1))=0x000001e6;
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
*((unsigned int *)((unsigned long)context_ptr+0x000061a8+4*1))=0x000001e6;
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
if(!memcmp((unsigned char *)context_ptr+0x000060dc,"\x87\x4d\x61\x91\xb6\x20\xe3\x26\x1b\xef\x68\x64\x99\x0d\xb6\xce\x98\x06\xf6\x6b\x79\x70\xfd\xff\x86\x17\x18\x7b\xb9\xff\xfd\xff\x5a\xe4\xdf\x3e\xdb\xd5\xd3\x5e\x5b\x4f\x09\x02\x0d\xb0\x3e\xab\x1e\x03\x1d\xda\x2f\xbe\x03\xd1\x79\x21\x70\xa0\xf3\x00\x9c\xee",64))
printf("strip: 874d6191b620e326, Pass\n");
else
printf("strip: 874d6191b620e326, Failed\n");
writel(0x0000000c&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006168,"\x1a\xbc\x93\x24\x17\x52\x1c\xa2\x4f\x2b\x04\x59\xfe\x7e\x6e\x0b\x09\x03\x39\xec\x0a\xa6\xfa\xef\xd5\xcc\xc2\xc6\xf4\xce\x8e\x94\x1e\x36\xb2\x6b\xd1\xeb\xc6\x70\xd1\xbd\x1d\x66\x56\x20\xab\xf7\x4f\x78\xa7\xf6\xd2\x98\x09\x58\x5a\x97\xda\xec\x58\xc6\xb0\x50",64))
printf("strip: 1abc932417521ca2, Pass\n");
else
printf("strip: 1abc932417521ca2, Failed\n");
writel(0x00000012&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000061f4,"\x60\x1e\xc3\x13\x77\x57\x89\xa5\xb7\xa7\xf5\x04\xbb\xf3\xd2\x28\xf4\x43\xe3\xca\x4d\x62\xb5\x9a\xca\x84\xe9\x90\xca\xca\xf5\xc5\x2b\x09\x30\xda\xa2\x3d\xe9\x4c\xe8\x70\x17\xba\x2d\x84\x98\x8d\xdf\xc9\xc5\x8d\xb6\x7a\xad\xa6\x13\xc2\xdd\x08\x45\x79\x41\xa6",64))
printf("strip: 601ec313775789a5, Pass\n");
else
printf("strip: 601ec313775789a5, Failed\n");
}

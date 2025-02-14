#include <common.h>
#include <malloc.h>

extern volatile unsigned int ivp_cae_base_addr;

void test_aes_ctr_nist_dec(void)
{
unsigned int *context_ptr=(unsigned int *)0x14000000;
printf("test_aes_ctr_nist_dec\n");
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
*((unsigned int *)((unsigned long)context_ptr+0x00006000))=0x010b0805;
*((unsigned int *)((unsigned long)context_ptr+0x00006000+4*1))=0x000001e6;
*((unsigned int *)((unsigned long)context_ptr+0x00006000+4*2))=0x16157e2b;
*((unsigned int *)((unsigned long)context_ptr+0x00006000+4*3))=0xa6d2ae28;
*((unsigned int *)((unsigned long)context_ptr+0x00006000+4*4))=0x8815f7ab;
*((unsigned int *)((unsigned long)context_ptr+0x00006000+4*5))=0x3c4fcf09;
*((unsigned int *)((unsigned long)context_ptr+0x00006000+4*6))=0xf3f2f1f0;
*((unsigned int *)((unsigned long)context_ptr+0x00006000+4*7))=0xf7f6f5f4;
*((unsigned int *)((unsigned long)context_ptr+0x00006000+4*8))=0xfbfaf9f8;
*((unsigned int *)((unsigned long)context_ptr+0x00006000+4*9))=0xfffefdfc;
*((unsigned int *)((unsigned long)context_ptr+0x00006028))=0x010d0a05;
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
*((unsigned int *)((unsigned long)context_ptr+0x00006058))=0x010f0c05;
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
*((unsigned int *)((unsigned long)context_ptr+0x00006090))=0x010b0805;
*((unsigned int *)((unsigned long)context_ptr+0x00006090+4*1))=0x000001e6;
*((unsigned int *)((unsigned long)context_ptr+0x00006090+4*2))=0x0d060040;
*((unsigned int *)((unsigned long)context_ptr+0x0000609c))=0x91614d87;
*((unsigned int *)((unsigned long)context_ptr+0x0000609c+4*1))=0x26e320b6;
*((unsigned int *)((unsigned long)context_ptr+0x0000609c+4*2))=0x6468ef1b;
*((unsigned int *)((unsigned long)context_ptr+0x0000609c+4*3))=0xceb60d99;
*((unsigned int *)((unsigned long)context_ptr+0x0000609c+4*4))=0x6bf60698;
*((unsigned int *)((unsigned long)context_ptr+0x0000609c+4*5))=0xfffd7079;
*((unsigned int *)((unsigned long)context_ptr+0x0000609c+4*6))=0x7b181786;
*((unsigned int *)((unsigned long)context_ptr+0x0000609c+4*7))=0xfffdffb9;
*((unsigned int *)((unsigned long)context_ptr+0x0000609c+4*8))=0x3edfe45a;
*((unsigned int *)((unsigned long)context_ptr+0x0000609c+4*9))=0x5ed3d5db;
*((unsigned int *)((unsigned long)context_ptr+0x0000609c+4*10))=0x02094f5b;
*((unsigned int *)((unsigned long)context_ptr+0x0000609c+4*11))=0xab3eb00d;
*((unsigned int *)((unsigned long)context_ptr+0x0000609c+4*12))=0xda1d031e;
*((unsigned int *)((unsigned long)context_ptr+0x0000609c+4*13))=0xd103be2f;
*((unsigned int *)((unsigned long)context_ptr+0x0000609c+4*14))=0xa0702179;
*((unsigned int *)((unsigned long)context_ptr+0x0000609c+4*15))=0xee9c00f3;
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
*((unsigned int *)((unsigned long)context_ptr+0x0000611c))=0x010d0a05;
*((unsigned int *)((unsigned long)context_ptr+0x0000611c+4*1))=0x000001e6;
*((unsigned int *)((unsigned long)context_ptr+0x0000611c+4*2))=0x0d060040;
*((unsigned int *)((unsigned long)context_ptr+0x00006128))=0x2493bc1a;
*((unsigned int *)((unsigned long)context_ptr+0x00006128+4*1))=0xa21c5217;
*((unsigned int *)((unsigned long)context_ptr+0x00006128+4*2))=0x59042b4f;
*((unsigned int *)((unsigned long)context_ptr+0x00006128+4*3))=0x0b6e7efe;
*((unsigned int *)((unsigned long)context_ptr+0x00006128+4*4))=0xec390309;
*((unsigned int *)((unsigned long)context_ptr+0x00006128+4*5))=0xeffaa60a;
*((unsigned int *)((unsigned long)context_ptr+0x00006128+4*6))=0xc6c2ccd5;
*((unsigned int *)((unsigned long)context_ptr+0x00006128+4*7))=0x948ecef4;
*((unsigned int *)((unsigned long)context_ptr+0x00006128+4*8))=0x6bb2361e;
*((unsigned int *)((unsigned long)context_ptr+0x00006128+4*9))=0x70c6ebd1;
*((unsigned int *)((unsigned long)context_ptr+0x00006128+4*10))=0x661dbdd1;
*((unsigned int *)((unsigned long)context_ptr+0x00006128+4*11))=0xf7ab2056;
*((unsigned int *)((unsigned long)context_ptr+0x00006128+4*12))=0xf6a7784f;
*((unsigned int *)((unsigned long)context_ptr+0x00006128+4*13))=0x580998d2;
*((unsigned int *)((unsigned long)context_ptr+0x00006128+4*14))=0xecda975a;
*((unsigned int *)((unsigned long)context_ptr+0x00006128+4*15))=0x50b0c658;
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
*((unsigned int *)((unsigned long)context_ptr+0x000061a8))=0x010f0c05;
*((unsigned int *)((unsigned long)context_ptr+0x000061a8+4*1))=0x000001e6;
*((unsigned int *)((unsigned long)context_ptr+0x000061a8+4*2))=0x0d060040;
*((unsigned int *)((unsigned long)context_ptr+0x000061b4))=0x13c31e60;
*((unsigned int *)((unsigned long)context_ptr+0x000061b4+4*1))=0xa5895777;
*((unsigned int *)((unsigned long)context_ptr+0x000061b4+4*2))=0x04f5a7b7;
*((unsigned int *)((unsigned long)context_ptr+0x000061b4+4*3))=0x28d2f3bb;
*((unsigned int *)((unsigned long)context_ptr+0x000061b4+4*4))=0xcae343f4;
*((unsigned int *)((unsigned long)context_ptr+0x000061b4+4*5))=0x9ab5624d;
*((unsigned int *)((unsigned long)context_ptr+0x000061b4+4*6))=0x90e984ca;
*((unsigned int *)((unsigned long)context_ptr+0x000061b4+4*7))=0xc5f5caca;
*((unsigned int *)((unsigned long)context_ptr+0x000061b4+4*8))=0xda30092b;
*((unsigned int *)((unsigned long)context_ptr+0x000061b4+4*9))=0x4ce93da2;
*((unsigned int *)((unsigned long)context_ptr+0x000061b4+4*10))=0xba1770e8;
*((unsigned int *)((unsigned long)context_ptr+0x000061b4+4*11))=0x8d98842d;
*((unsigned int *)((unsigned long)context_ptr+0x000061b4+4*12))=0x8dc5c9df;
*((unsigned int *)((unsigned long)context_ptr+0x000061b4+4*13))=0xa6ad7ab6;
*((unsigned int *)((unsigned long)context_ptr+0x000061b4+4*14))=0x08ddc213;
*((unsigned int *)((unsigned long)context_ptr+0x000061b4+4*15))=0xa6417945;
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
if(!memcmp((unsigned char *)context_ptr+0x000060dc,"\x6b\xc1\xbe\xe2\x2e\x40\x9f\x96\xe9\x3d\x7e\x11\x73\x93\x17\x2a\xae\x2d\x8a\x57\x1e\x03\xac\x9c\x9e\xb7\x6f\xac\x45\xaf\x8e\x51\x30\xc8\x1c\x46\xa3\x5c\xe4\x11\xe5\xfb\xc1\x19\x1a\x0a\x52\xef\xf6\x9f\x24\x45\xdf\x4f\x9b\x17\xad\x2b\x41\x7b\xe6\x6c\x37\x10",64))
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
if(!memcmp((unsigned char *)context_ptr+0x00006168,"\x6b\xc1\xbe\xe2\x2e\x40\x9f\x96\xe9\x3d\x7e\x11\x73\x93\x17\x2a\xae\x2d\x8a\x57\x1e\x03\xac\x9c\x9e\xb7\x6f\xac\x45\xaf\x8e\x51\x30\xc8\x1c\x46\xa3\x5c\xe4\x11\xe5\xfb\xc1\x19\x1a\x0a\x52\xef\xf6\x9f\x24\x45\xdf\x4f\x9b\x17\xad\x2b\x41\x7b\xe6\x6c\x37\x10",64))
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
if(!memcmp((unsigned char *)context_ptr+0x000061f4,"\x6b\xc1\xbe\xe2\x2e\x40\x9f\x96\xe9\x3d\x7e\x11\x73\x93\x17\x2a\xae\x2d\x8a\x57\x1e\x03\xac\x9c\x9e\xb7\x6f\xac\x45\xaf\x8e\x51\x30\xc8\x1c\x46\xa3\x5c\xe4\x11\xe5\xfb\xc1\x19\x1a\x0a\x52\xef\xf6\x9f\x24\x45\xdf\x4f\x9b\x17\xad\x2b\x41\x7b\xe6\x6c\x37\x10",64))
printf("strip: 6bc1bee22e409f96, Pass\n");
else
printf("strip: 6bc1bee22e409f96, Failed\n");
}

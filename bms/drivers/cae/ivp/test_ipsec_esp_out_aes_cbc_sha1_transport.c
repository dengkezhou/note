#include <common.h>
#include <malloc.h>

extern volatile unsigned int ivp_cae_base_addr;

void test_ipsec_esp_out_aes_cbc_sha1_transport(void)
{
unsigned int *context_ptr=(unsigned int *)0x14000000;
printf("test_ipsec_esp_out_aes_cbc_sha1_transport\n");
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
writel(0x00000600&0xffffffff,ivp_cae_base_addr+0x00000018);
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
writel(0x01000000&0xffffffff,ivp_cae_base_addr+0x00000824);
writel(((unsigned long)context_ptr+0x00000000)&0xffffffffffffffff,ivp_cae_base_addr+0x00000808);
writel((((unsigned long)context_ptr+0x00000000)>>32)&(0xffffffffffffffff>>32),ivp_cae_base_addr+0x00000808+0x4);
writel(((unsigned long)context_ptr+0x00000600)&0xffffffffffffffff,ivp_cae_base_addr+0x00000800);
writel((((unsigned long)context_ptr+0x00000600)>>32)&(0xffffffffffffffff>>32),ivp_cae_base_addr+0x00000800+0x4);
writel(0x00000600&0xffffffff,ivp_cae_base_addr+0x00000818);
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
*((unsigned int *)((unsigned long)context_ptr+0x00000c00))=0x196b1006;
*((unsigned int *)((unsigned long)context_ptr+0x00000c00+4*1))=0x51000001;
*((unsigned int *)((unsigned long)context_ptr+0x00000c00+4*2))=0x426bc2d8;
*((unsigned int *)((unsigned long)context_ptr+0x00000c00+4*3))=0x4dc86782;
*((unsigned int *)((unsigned long)context_ptr+0x00000c00+4*4))=0x81e8957a;
*((unsigned int *)((unsigned long)context_ptr+0x00000c00+4*5))=0x409ec148;
*((unsigned int *)((unsigned long)context_ptr+0x00000c00+4*6))=0xd66e890f;
*((unsigned int *)((unsigned long)context_ptr+0x00000c00+4*7))=0xca60dfa5;
*((unsigned int *)((unsigned long)context_ptr+0x00000c00+4*8))=0x5b48e12a;
*((unsigned int *)((unsigned long)context_ptr+0x00000c00+4*9))=0x9a0b4f52;
*((unsigned int *)((unsigned long)context_ptr+0x00000c00+4*10))=0xa068b01d;
*((unsigned int *)((unsigned long)context_ptr+0x00000c00+4*11))=0x726dc6be;
*((unsigned int *)((unsigned long)context_ptr+0x00000c00+4*12))=0xd3aab56b;
*((unsigned int *)((unsigned long)context_ptr+0x00000c00+4*13))=0x45c6247b;
*((unsigned int *)((unsigned long)context_ptr+0x00000c00+4*14))=0x8d504ea7;
*((unsigned int *)((unsigned long)context_ptr+0x00000c00+4*15))=0x765d00f2;
*((unsigned int *)((unsigned long)context_ptr+0x00000c00+4*16))=0x00008765;
*((unsigned int *)((unsigned long)context_ptr+0x00000c00+4*17))=0x00000050;
*((unsigned int *)((unsigned long)context_ptr+0x00000c48))=0x196b1006;
*((unsigned int *)((unsigned long)context_ptr+0x00000c48+4*1))=0x51000001;
*((unsigned int *)((unsigned long)context_ptr+0x00000c48+4*2))=0x390ade15;
*((unsigned int *)((unsigned long)context_ptr+0x00000c48+4*3))=0x54d8030a;
*((unsigned int *)((unsigned long)context_ptr+0x00000c48+4*4))=0xf7a72629;
*((unsigned int *)((unsigned long)context_ptr+0x00000c48+4*5))=0x9280e681;
*((unsigned int *)((unsigned long)context_ptr+0x00000c48+4*6))=0xd66e890f;
*((unsigned int *)((unsigned long)context_ptr+0x00000c48+4*7))=0xca60dfa5;
*((unsigned int *)((unsigned long)context_ptr+0x00000c48+4*8))=0x5b48e12a;
*((unsigned int *)((unsigned long)context_ptr+0x00000c48+4*9))=0x9a0b4f52;
*((unsigned int *)((unsigned long)context_ptr+0x00000c48+4*10))=0xa068b01d;
*((unsigned int *)((unsigned long)context_ptr+0x00000c48+4*11))=0x726dc6be;
*((unsigned int *)((unsigned long)context_ptr+0x00000c48+4*12))=0xd3aab56b;
*((unsigned int *)((unsigned long)context_ptr+0x00000c48+4*13))=0x45c6247b;
*((unsigned int *)((unsigned long)context_ptr+0x00000c48+4*14))=0x8d504ea7;
*((unsigned int *)((unsigned long)context_ptr+0x00000c48+4*15))=0x765d00f2;
*((unsigned int *)((unsigned long)context_ptr+0x00000c48+4*16))=0x00004321;
*((unsigned int *)((unsigned long)context_ptr+0x00000c48+4*17))=0x00003300;
*((unsigned int *)((unsigned long)context_ptr+0x00000c90))=0x37b47d94;
*((unsigned int *)((unsigned long)context_ptr+0x00000c90+4*1))=0x00290b44;
*((unsigned int *)((unsigned long)context_ptr+0x00000c90+4*2))=0xaec923a7;
*((unsigned int *)((unsigned long)context_ptr+0x00000c90+4*3))=0x74eb65f8;
*((unsigned int *)((unsigned long)context_ptr+0x00000c90+4*4))=0x61320048;
*((unsigned int *)((unsigned long)context_ptr+0x00000c90+4*5))=0x01000008;
*((unsigned int *)((unsigned long)context_ptr+0x00000c90+4*6))=0x23900018;
*((unsigned int *)((unsigned long)context_ptr+0x00000c90+4*7))=0x0700000a;
*((unsigned int *)((unsigned long)context_ptr+0x00000c90+4*8))=0x2f23ea06;
*((unsigned int *)((unsigned long)context_ptr+0x00000c90+4*9))=0x21e6000c;
*((unsigned int *)((unsigned long)context_ptr+0x00000c90+4*10))=0xe1561811;
*((unsigned int *)((unsigned long)context_ptr+0x00000cbc))=0x1e000045;
*((unsigned int *)((unsigned long)context_ptr+0x00000cbc+4*1))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x00000cbc+4*2))=0x9131f580;
*((unsigned int *)((unsigned long)context_ptr+0x00000cbc+4*3))=0x71e92186;
*((unsigned int *)((unsigned long)context_ptr+0x00000cbc+4*4))=0x63ce63ca;
*((unsigned int *)((unsigned long)context_ptr+0x00000cbc+4*5))=0xcbc765d6;
*((unsigned int *)((unsigned long)context_ptr+0x00000cbc+4*6))=0xc45633e8;
*((unsigned int *)((unsigned long)context_ptr+0x00000cbc+4*7))=0x00008d47;
*((unsigned int *)((unsigned long)context_ptr+0x00000600))=0x04c00048;
*((unsigned int *)((unsigned long)context_ptr+0x00000600+4*1))=0x00000cdc;
*((unsigned int *)((unsigned long)context_ptr+0x00000600+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00000600+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00000600+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00000600+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x0000017a&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000000))=0x0bc0001e;
*((unsigned int *)((unsigned long)context_ptr+0x00000000+4*1))=0x00000cbc;
*((unsigned int *)((unsigned long)context_ptr+0x00000000+4*2))=0x00000c90;
*((unsigned int *)((unsigned long)context_ptr+0x00000000+4*3))=0x1c22001e;
*((unsigned int *)((unsigned long)context_ptr+0x00000000+4*4))=0x00385c5f;
*((unsigned int *)((unsigned long)context_ptr+0x00000000+4*5))=0x00000c48+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x00000d24))=0x1e75facf;
*((unsigned int *)((unsigned long)context_ptr+0x00000d24+4*1))=0x69c31914;
*((unsigned int *)((unsigned long)context_ptr+0x00000d24+4*2))=0x6d1370eb;
*((unsigned int *)((unsigned long)context_ptr+0x00000d24+4*3))=0x2e0ad4c1;
*((unsigned int *)((unsigned long)context_ptr+0x00000d24+4*4))=0x81320034;
*((unsigned int *)((unsigned long)context_ptr+0x00000d24+4*5))=0x01000020;
*((unsigned int *)((unsigned long)context_ptr+0x00000d24+4*6))=0x23900018;
*((unsigned int *)((unsigned long)context_ptr+0x00000d24+4*7))=0x0700000a;
*((unsigned int *)((unsigned long)context_ptr+0x00000d24+4*8))=0x2f232406;
*((unsigned int *)((unsigned long)context_ptr+0x00000d24+4*9))=0x21e6000c;
*((unsigned int *)((unsigned long)context_ptr+0x00000d24+4*10))=0xe1561811;
*((unsigned int *)((unsigned long)context_ptr+0x00000d50))=0x00000060;
*((unsigned int *)((unsigned long)context_ptr+0x00000d50+4*1))=0x54920a00;
*((unsigned int *)((unsigned long)context_ptr+0x00000d50+4*2))=0x268b6032;
*((unsigned int *)((unsigned long)context_ptr+0x00000d50+4*3))=0x6725fbfd;
*((unsigned int *)((unsigned long)context_ptr+0x00000d50+4*4))=0xea7ee0ae;
*((unsigned int *)((unsigned long)context_ptr+0x00000d50+4*5))=0xab7f7f52;
*((unsigned int *)((unsigned long)context_ptr+0x00000d50+4*6))=0x57389c33;
*((unsigned int *)((unsigned long)context_ptr+0x00000d50+4*7))=0x09d1e6f6;
*((unsigned int *)((unsigned long)context_ptr+0x00000d50+4*8))=0xd7c84125;
*((unsigned int *)((unsigned long)context_ptr+0x00000d50+4*9))=0x10ceb795;
*((unsigned int *)((unsigned long)context_ptr+0x00000d50+4*10))=0x835da07a;
*((unsigned int *)((unsigned long)context_ptr+0x00000d50+4*11))=0xb7a2e9f2;
*((unsigned int *)((unsigned long)context_ptr+0x00000d50+4*12))=0x00009b24;
*((unsigned int *)((unsigned long)context_ptr+0x00000618))=0x04c0005c;
*((unsigned int *)((unsigned long)context_ptr+0x00000618+4*1))=0x00000d84;
*((unsigned int *)((unsigned long)context_ptr+0x00000618+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00000618+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00000618+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00000618+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x0000017a&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000018))=0x0bc00032;
*((unsigned int *)((unsigned long)context_ptr+0x00000018+4*1))=0x00000d50;
*((unsigned int *)((unsigned long)context_ptr+0x00000018+4*2))=0x00000d24;
*((unsigned int *)((unsigned long)context_ptr+0x00000018+4*3))=0x1c220032;
*((unsigned int *)((unsigned long)context_ptr+0x00000018+4*4))=0x001a32e1;
*((unsigned int *)((unsigned long)context_ptr+0x00000018+4*5))=0x00000c00+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x00000de0))=0x5bbc1ea5;
*((unsigned int *)((unsigned long)context_ptr+0x00000de0+4*1))=0x38a9b4ac;
*((unsigned int *)((unsigned long)context_ptr+0x00000de0+4*2))=0xac843dd4;
*((unsigned int *)((unsigned long)context_ptr+0x00000de0+4*3))=0x2b49a03b;
*((unsigned int *)((unsigned long)context_ptr+0x00000de0+4*4))=0x61320048;
*((unsigned int *)((unsigned long)context_ptr+0x00000de0+4*5))=0x01000008;
*((unsigned int *)((unsigned long)context_ptr+0x00000de0+4*6))=0x23900018;
*((unsigned int *)((unsigned long)context_ptr+0x00000de0+4*7))=0x0700000b;
*((unsigned int *)((unsigned long)context_ptr+0x00000de0+4*8))=0x2f233405;
*((unsigned int *)((unsigned long)context_ptr+0x00000de0+4*9))=0x21e6000c;
*((unsigned int *)((unsigned long)context_ptr+0x00000de0+4*10))=0xe1561811;
*((unsigned int *)((unsigned long)context_ptr+0x00000e0c))=0x1f000045;
*((unsigned int *)((unsigned long)context_ptr+0x00000e0c+4*1))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x00000e0c+4*2))=0xeb319a80;
*((unsigned int *)((unsigned long)context_ptr+0x00000e0c+4*3))=0x71e92186;
*((unsigned int *)((unsigned long)context_ptr+0x00000e0c+4*4))=0x63ce63ca;
*((unsigned int *)((unsigned long)context_ptr+0x00000e0c+4*5))=0xcd233e05;
*((unsigned int *)((unsigned long)context_ptr+0x00000e0c+4*6))=0x1c216628;
*((unsigned int *)((unsigned long)context_ptr+0x00000e0c+4*7))=0x008338fe;
*((unsigned int *)((unsigned long)context_ptr+0x00000630))=0x04c00048;
*((unsigned int *)((unsigned long)context_ptr+0x00000630+4*1))=0x00000e2c;
*((unsigned int *)((unsigned long)context_ptr+0x00000630+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00000630+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00000630+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00000630+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x0000017a&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000030))=0x0bc0001f;
*((unsigned int *)((unsigned long)context_ptr+0x00000030+4*1))=0x00000e0c;
*((unsigned int *)((unsigned long)context_ptr+0x00000030+4*2))=0x00000de0;
*((unsigned int *)((unsigned long)context_ptr+0x00000030+4*3))=0x1c22001f;
*((unsigned int *)((unsigned long)context_ptr+0x00000030+4*4))=0x0020ca35;
*((unsigned int *)((unsigned long)context_ptr+0x00000030+4*5))=0x00000c48+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x00000e74))=0xa9a73803;
*((unsigned int *)((unsigned long)context_ptr+0x00000e74+4*1))=0x507bf47e;
*((unsigned int *)((unsigned long)context_ptr+0x00000e74+4*2))=0xb49a42d9;
*((unsigned int *)((unsigned long)context_ptr+0x00000e74+4*3))=0x0f62c9d2;
*((unsigned int *)((unsigned long)context_ptr+0x00000e74+4*4))=0x81320034;
*((unsigned int *)((unsigned long)context_ptr+0x00000e74+4*5))=0x01000020;
*((unsigned int *)((unsigned long)context_ptr+0x00000e74+4*6))=0x23900018;
*((unsigned int *)((unsigned long)context_ptr+0x00000e74+4*7))=0x0700000b;
*((unsigned int *)((unsigned long)context_ptr+0x00000e74+4*8))=0x2f238005;
*((unsigned int *)((unsigned long)context_ptr+0x00000e74+4*9))=0x21e6000c;
*((unsigned int *)((unsigned long)context_ptr+0x00000e74+4*10))=0xe1561811;
*((unsigned int *)((unsigned long)context_ptr+0x00000ea0))=0x00000060;
*((unsigned int *)((unsigned long)context_ptr+0x00000ea0+4*1))=0x54c00b00;
*((unsigned int *)((unsigned long)context_ptr+0x00000ea0+4*2))=0x268b6032;
*((unsigned int *)((unsigned long)context_ptr+0x00000ea0+4*3))=0x6725fbfd;
*((unsigned int *)((unsigned long)context_ptr+0x00000ea0+4*4))=0xea7ee0ae;
*((unsigned int *)((unsigned long)context_ptr+0x00000ea0+4*5))=0xab7f7f52;
*((unsigned int *)((unsigned long)context_ptr+0x00000ea0+4*6))=0x57389c33;
*((unsigned int *)((unsigned long)context_ptr+0x00000ea0+4*7))=0x09d1e6f6;
*((unsigned int *)((unsigned long)context_ptr+0x00000ea0+4*8))=0xd7c84125;
*((unsigned int *)((unsigned long)context_ptr+0x00000ea0+4*9))=0x10ceb795;
*((unsigned int *)((unsigned long)context_ptr+0x00000ea0+4*10))=0xa24c9cd6;
*((unsigned int *)((unsigned long)context_ptr+0x00000ea0+4*11))=0x4bf87e86;
*((unsigned int *)((unsigned long)context_ptr+0x00000ea0+4*12))=0x00c486c4;
*((unsigned int *)((unsigned long)context_ptr+0x00000648))=0x04c0005c;
*((unsigned int *)((unsigned long)context_ptr+0x00000648+4*1))=0x00000ed4;
*((unsigned int *)((unsigned long)context_ptr+0x00000648+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00000648+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00000648+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00000648+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x0000017a&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000048))=0x0bc00033;
*((unsigned int *)((unsigned long)context_ptr+0x00000048+4*1))=0x00000ea0;
*((unsigned int *)((unsigned long)context_ptr+0x00000048+4*2))=0x00000e74;
*((unsigned int *)((unsigned long)context_ptr+0x00000048+4*3))=0x1c220033;
*((unsigned int *)((unsigned long)context_ptr+0x00000048+4*4))=0x008d9974;
*((unsigned int *)((unsigned long)context_ptr+0x00000048+4*5))=0x00000c00+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000006&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00000cdc,"\x45\x00\x00\x48\x00\x00\x00\x00\x80\x32\x32\x2a\x86\x21\xe9\x71\xca\x63\xce\x63\x00\x00\x43\x21\x00\x00\x33\x01\x94\x7d\xb4\x37\x44\x0b\x29\x00\xa7\x23\xc9\xae\xf8\x65\xeb\x74\xf0\xeb\x4b\x4d\xaf\x85\x70\xd7\x47\x1c\xf2\xdd\x3f\xd5\xeb\xf7\x92\xd6\x8b\x8f\x37\xc9\xd0\x94\xef\x11\xcc\x36",72))
printf("strip: 4500004800000000, Pass\n");
else
printf("strip: 4500004800000000, Failed\n");
writel(0x0000000c&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00000d84,"\x60\x00\x00\x00\x00\x34\x32\x54\x32\x60\x8b\x26\xfd\xfb\x25\x67\xae\xe0\x7e\xea\x52\x7f\x7f\xab\x33\x9c\x38\x57\xf6\xe6\xd1\x09\x25\x41\xc8\xd7\x95\xb7\xce\x10\x00\x00\x87\x65\x00\x00\x00\x51\xcf\xfa\x75\x1e\x14\x19\xc3\x69\xeb\x70\x13\x6d\xc1\xd4\x0a\x2e\xdb\x21\x11\xb7\x76\xab\xfb\x2a\x6c\xe0\xd0\x2f\x26\x7f\x5f\xe4\xf8\xa2\x3e\x30\x3b\xdd\xca\x2c\x31\x1f\x7a\x8e",92))
printf("strip: 6000000000343254, Pass\n");
else
printf("strip: 6000000000343254, Failed\n");
writel(0x00000012&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00000e2c,"\x45\x00\x00\x48\x00\x00\x00\x00\x80\x32\x32\x2a\x86\x21\xe9\x71\xca\x63\xce\x63\x00\x00\x43\x21\x00\x00\x33\x02\xa5\x1e\xbc\x5b\xac\xb4\xa9\x38\xd4\x3d\x84\xac\x3b\xa0\x49\x2b\xf7\x34\x71\x30\x77\x6d\x5b\x15\x92\x4f\x73\x5c\x1f\x33\xc8\x82\x44\xc2\x58\x40\xcf\x06\x90\x19\x33\xa3\xa8\x69",72))
printf("strip: 4500004800000000, Pass\n");
else
printf("strip: 4500004800000000, Failed\n");
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00000ed4,"\x60\x00\x00\x00\x00\x34\x32\x54\x32\x60\x8b\x26\xfd\xfb\x25\x67\xae\xe0\x7e\xea\x52\x7f\x7f\xab\x33\x9c\x38\x57\xf6\xe6\xd1\x09\x25\x41\xc8\xd7\x95\xb7\xce\x10\x00\x00\x87\x65\x00\x00\x00\x52\x03\x38\xa7\xa9\x7e\xf4\x7b\x50\xd9\x42\x9a\xb4\xd2\xc9\x62\x0f\x48\xde\x74\x50\x0f\x4b\x7c\x38\x02\x59\x0e\x2e\x60\x94\xa0\x25\x4e\x90\x41\xf8\x90\x68\xa9\x58\xdd\xe8\x17\x10",92))
printf("strip: 6000000000343254, Pass\n");
else
printf("strip: 6000000000343254, Failed\n");
}

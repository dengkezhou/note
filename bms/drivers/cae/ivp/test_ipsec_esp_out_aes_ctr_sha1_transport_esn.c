#include <common.h>
#include <malloc.h>

extern volatile unsigned int ivp_cae_base_addr;

void test_ipsec_esp_out_aes_ctr_sha1_transport_esn(void)
{
unsigned int *context_ptr=(unsigned int *)0x14000000;
printf("test_ipsec_esp_out_aes_ctr_sha1_transport_esn\n");
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
*((unsigned int *)((unsigned long)context_ptr+0x00000c00))=0x396b1206;
*((unsigned int *)((unsigned long)context_ptr+0x00000c00+4*1))=0x51000422;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000c00+4*18))=0x00005678;
*((unsigned int *)((unsigned long)context_ptr+0x00000c00+4*19))=0x44332211;
*((unsigned int *)((unsigned long)context_ptr+0x00000c50))=0x396b1206;
*((unsigned int *)((unsigned long)context_ptr+0x00000c50+4*1))=0x51000422;
*((unsigned int *)((unsigned long)context_ptr+0x00000c50+4*2))=0x390ade15;
*((unsigned int *)((unsigned long)context_ptr+0x00000c50+4*3))=0x54d8030a;
*((unsigned int *)((unsigned long)context_ptr+0x00000c50+4*4))=0xf7a72629;
*((unsigned int *)((unsigned long)context_ptr+0x00000c50+4*5))=0x9280e681;
*((unsigned int *)((unsigned long)context_ptr+0x00000c50+4*6))=0xd66e890f;
*((unsigned int *)((unsigned long)context_ptr+0x00000c50+4*7))=0xca60dfa5;
*((unsigned int *)((unsigned long)context_ptr+0x00000c50+4*8))=0x5b48e12a;
*((unsigned int *)((unsigned long)context_ptr+0x00000c50+4*9))=0x9a0b4f52;
*((unsigned int *)((unsigned long)context_ptr+0x00000c50+4*10))=0xa068b01d;
*((unsigned int *)((unsigned long)context_ptr+0x00000c50+4*11))=0x726dc6be;
*((unsigned int *)((unsigned long)context_ptr+0x00000c50+4*12))=0xd3aab56b;
*((unsigned int *)((unsigned long)context_ptr+0x00000c50+4*13))=0x45c6247b;
*((unsigned int *)((unsigned long)context_ptr+0x00000c50+4*14))=0x8d504ea7;
*((unsigned int *)((unsigned long)context_ptr+0x00000c50+4*15))=0x765d00f2;
*((unsigned int *)((unsigned long)context_ptr+0x00000c50+4*16))=0x00004321;
*((unsigned int *)((unsigned long)context_ptr+0x00000c50+4*17))=0x00000080;
*((unsigned int *)((unsigned long)context_ptr+0x00000c50+4*18))=0x00001234;
*((unsigned int *)((unsigned long)context_ptr+0x00000c50+4*19))=0x44332211;
*((unsigned int *)((unsigned long)context_ptr+0x00000ca0))=0x6132003c;
*((unsigned int *)((unsigned long)context_ptr+0x00000ca0+4*1))=0x01000008;
*((unsigned int *)((unsigned long)context_ptr+0x00000ca0+4*2))=0x23900008;
*((unsigned int *)((unsigned long)context_ptr+0x00000ca0+4*3))=0x93415008;
*((unsigned int *)((unsigned long)context_ptr+0x00000ca0+4*4))=0x0700000a;
*((unsigned int *)((unsigned long)context_ptr+0x00000ca0+4*5))=0x2f21ea02;
*((unsigned int *)((unsigned long)context_ptr+0x00000ca0+4*6))=0x224a0004;
*((unsigned int *)((unsigned long)context_ptr+0x00000ca0+4*7))=0x21e6000c;
*((unsigned int *)((unsigned long)context_ptr+0x00000ca0+4*8))=0xe2561811;
*((unsigned int *)((unsigned long)context_ptr+0x00000cc4))=0x1e000045;
*((unsigned int *)((unsigned long)context_ptr+0x00000cc4+4*1))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x00000cc4+4*2))=0x9131f580;
*((unsigned int *)((unsigned long)context_ptr+0x00000cc4+4*3))=0x71e92186;
*((unsigned int *)((unsigned long)context_ptr+0x00000cc4+4*4))=0x63ce63ca;
*((unsigned int *)((unsigned long)context_ptr+0x00000cc4+4*5))=0xcbc765d6;
*((unsigned int *)((unsigned long)context_ptr+0x00000cc4+4*6))=0xc45633e8;
*((unsigned int *)((unsigned long)context_ptr+0x00000cc4+4*7))=0x00008d47;
*((unsigned int *)((unsigned long)context_ptr+0x00000600))=0x04c0003c;
*((unsigned int *)((unsigned long)context_ptr+0x00000600+4*1))=0x00000ce4;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000000))=0x09c0001e;
*((unsigned int *)((unsigned long)context_ptr+0x00000000+4*1))=0x00000cc4;
*((unsigned int *)((unsigned long)context_ptr+0x00000000+4*2))=0x00000ca0;
*((unsigned int *)((unsigned long)context_ptr+0x00000000+4*3))=0x0022001e;
*((unsigned int *)((unsigned long)context_ptr+0x00000000+4*4))=0x00385c5f;
*((unsigned int *)((unsigned long)context_ptr+0x00000000+4*5))=0x00000c50+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x00000d20))=0x81320028;
*((unsigned int *)((unsigned long)context_ptr+0x00000d20+4*1))=0x01000020;
*((unsigned int *)((unsigned long)context_ptr+0x00000d20+4*2))=0x23900008;
*((unsigned int *)((unsigned long)context_ptr+0x00000d20+4*3))=0x93415008;
*((unsigned int *)((unsigned long)context_ptr+0x00000d20+4*4))=0x0700000a;
*((unsigned int *)((unsigned long)context_ptr+0x00000d20+4*5))=0x2f212402;
*((unsigned int *)((unsigned long)context_ptr+0x00000d20+4*6))=0x224a0004;
*((unsigned int *)((unsigned long)context_ptr+0x00000d20+4*7))=0x21e6000c;
*((unsigned int *)((unsigned long)context_ptr+0x00000d20+4*8))=0xe2561811;
*((unsigned int *)((unsigned long)context_ptr+0x00000d44))=0x00000060;
*((unsigned int *)((unsigned long)context_ptr+0x00000d44+4*1))=0x54920a00;
*((unsigned int *)((unsigned long)context_ptr+0x00000d44+4*2))=0x268b6032;
*((unsigned int *)((unsigned long)context_ptr+0x00000d44+4*3))=0x6725fbfd;
*((unsigned int *)((unsigned long)context_ptr+0x00000d44+4*4))=0xea7ee0ae;
*((unsigned int *)((unsigned long)context_ptr+0x00000d44+4*5))=0xab7f7f52;
*((unsigned int *)((unsigned long)context_ptr+0x00000d44+4*6))=0x57389c33;
*((unsigned int *)((unsigned long)context_ptr+0x00000d44+4*7))=0x09d1e6f6;
*((unsigned int *)((unsigned long)context_ptr+0x00000d44+4*8))=0xd7c84125;
*((unsigned int *)((unsigned long)context_ptr+0x00000d44+4*9))=0x10ceb795;
*((unsigned int *)((unsigned long)context_ptr+0x00000d44+4*10))=0x835da07a;
*((unsigned int *)((unsigned long)context_ptr+0x00000d44+4*11))=0xb7a2e9f2;
*((unsigned int *)((unsigned long)context_ptr+0x00000d44+4*12))=0x00009b24;
*((unsigned int *)((unsigned long)context_ptr+0x00000618))=0x04c00050;
*((unsigned int *)((unsigned long)context_ptr+0x00000618+4*1))=0x00000d78;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000018))=0x09c00032;
*((unsigned int *)((unsigned long)context_ptr+0x00000018+4*1))=0x00000d44;
*((unsigned int *)((unsigned long)context_ptr+0x00000018+4*2))=0x00000d20;
*((unsigned int *)((unsigned long)context_ptr+0x00000018+4*3))=0x00220032;
*((unsigned int *)((unsigned long)context_ptr+0x00000018+4*4))=0x001a32e1;
*((unsigned int *)((unsigned long)context_ptr+0x00000018+4*5))=0x00000c00+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x00000dc8))=0x6132003c;
*((unsigned int *)((unsigned long)context_ptr+0x00000dc8+4*1))=0x01000008;
*((unsigned int *)((unsigned long)context_ptr+0x00000dc8+4*2))=0x23900008;
*((unsigned int *)((unsigned long)context_ptr+0x00000dc8+4*3))=0x93415008;
*((unsigned int *)((unsigned long)context_ptr+0x00000dc8+4*4))=0x0700000a;
*((unsigned int *)((unsigned long)context_ptr+0x00000dc8+4*5))=0x2f21da02;
*((unsigned int *)((unsigned long)context_ptr+0x00000dc8+4*6))=0x224a0004;
*((unsigned int *)((unsigned long)context_ptr+0x00000dc8+4*7))=0x21e6000c;
*((unsigned int *)((unsigned long)context_ptr+0x00000dc8+4*8))=0xe2561811;
*((unsigned int *)((unsigned long)context_ptr+0x00000dec))=0x1e000045;
*((unsigned int *)((unsigned long)context_ptr+0x00000dec+4*1))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x00000dec+4*2))=0x9931ed80;
*((unsigned int *)((unsigned long)context_ptr+0x00000dec+4*3))=0x71e92186;
*((unsigned int *)((unsigned long)context_ptr+0x00000dec+4*4))=0x63ce63ca;
*((unsigned int *)((unsigned long)context_ptr+0x00000dec+4*5))=0xcd233e05;
*((unsigned int *)((unsigned long)context_ptr+0x00000dec+4*6))=0x1c216628;
*((unsigned int *)((unsigned long)context_ptr+0x00000dec+4*7))=0x000038fe;
*((unsigned int *)((unsigned long)context_ptr+0x00000630))=0x04c0003c;
*((unsigned int *)((unsigned long)context_ptr+0x00000630+4*1))=0x00000e0c;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000030))=0x09c0001e;
*((unsigned int *)((unsigned long)context_ptr+0x00000030+4*1))=0x00000dec;
*((unsigned int *)((unsigned long)context_ptr+0x00000030+4*2))=0x00000dc8;
*((unsigned int *)((unsigned long)context_ptr+0x00000030+4*3))=0x0022001e;
*((unsigned int *)((unsigned long)context_ptr+0x00000030+4*4))=0x0020ca35;
*((unsigned int *)((unsigned long)context_ptr+0x00000030+4*5))=0x00000c50+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x00000e48))=0x81320028;
*((unsigned int *)((unsigned long)context_ptr+0x00000e48+4*1))=0x01000020;
*((unsigned int *)((unsigned long)context_ptr+0x00000e48+4*2))=0x23900008;
*((unsigned int *)((unsigned long)context_ptr+0x00000e48+4*3))=0x93415008;
*((unsigned int *)((unsigned long)context_ptr+0x00000e48+4*4))=0x0700000a;
*((unsigned int *)((unsigned long)context_ptr+0x00000e48+4*5))=0x2f218e02;
*((unsigned int *)((unsigned long)context_ptr+0x00000e48+4*6))=0x224a0004;
*((unsigned int *)((unsigned long)context_ptr+0x00000e48+4*7))=0x21e6000c;
*((unsigned int *)((unsigned long)context_ptr+0x00000e48+4*8))=0xe2561811;
*((unsigned int *)((unsigned long)context_ptr+0x00000e6c))=0x00000060;
*((unsigned int *)((unsigned long)context_ptr+0x00000e6c+4*1))=0x54c70a00;
*((unsigned int *)((unsigned long)context_ptr+0x00000e6c+4*2))=0x268b6032;
*((unsigned int *)((unsigned long)context_ptr+0x00000e6c+4*3))=0x6725fbfd;
*((unsigned int *)((unsigned long)context_ptr+0x00000e6c+4*4))=0xea7ee0ae;
*((unsigned int *)((unsigned long)context_ptr+0x00000e6c+4*5))=0xab7f7f52;
*((unsigned int *)((unsigned long)context_ptr+0x00000e6c+4*6))=0x57389c33;
*((unsigned int *)((unsigned long)context_ptr+0x00000e6c+4*7))=0x09d1e6f6;
*((unsigned int *)((unsigned long)context_ptr+0x00000e6c+4*8))=0xd7c84125;
*((unsigned int *)((unsigned long)context_ptr+0x00000e6c+4*9))=0x10ceb795;
*((unsigned int *)((unsigned long)context_ptr+0x00000e6c+4*10))=0x4c9cd683;
*((unsigned int *)((unsigned long)context_ptr+0x00000e6c+4*11))=0xf87e86a2;
*((unsigned int *)((unsigned long)context_ptr+0x00000e6c+4*12))=0x0000c44b;
*((unsigned int *)((unsigned long)context_ptr+0x00000648))=0x04c00050;
*((unsigned int *)((unsigned long)context_ptr+0x00000648+4*1))=0x00000ea0;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000048))=0x09c00032;
*((unsigned int *)((unsigned long)context_ptr+0x00000048+4*1))=0x00000e6c;
*((unsigned int *)((unsigned long)context_ptr+0x00000048+4*2))=0x00000e48;
*((unsigned int *)((unsigned long)context_ptr+0x00000048+4*3))=0x00220032;
*((unsigned int *)((unsigned long)context_ptr+0x00000048+4*4))=0x00cf4bb3;
*((unsigned int *)((unsigned long)context_ptr+0x00000048+4*5))=0x00000c00+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000006&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00000ce4,"\x45\x00\x00\x3c\x00\x00\x00\x00\x80\x32\x32\x36\x86\x21\xe9\x71\xca\x63\xce\x63\x00\x00\x43\x21\x00\x00\x00\x81\x00\x00\x00\x81\x00\x00\x12\x34\x3e\xc0\x98\xdb\x1c\xab\x62\x21\x40\x16\xf0\x87\x87\xe6\x48\x90\x30\x89\xf3\x11\xbb\xc8\xba\x6f",60))
printf("strip: 4500003c00000000, Pass\n");
else
printf("strip: 4500003c00000000, Failed\n");
writel(0x0000000c&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00000d78,"\x60\x00\x00\x00\x00\x28\x32\x54\x32\x60\x8b\x26\xfd\xfb\x25\x67\xae\xe0\x7e\xea\x52\x7f\x7f\xab\x33\x9c\x38\x57\xf6\xe6\xd1\x09\x25\x41\xc8\xd7\x95\xb7\xce\x10\x00\x00\x87\x65\x00\x00\x00\x51\x00\x00\x00\x51\x00\x00\x56\x78\xd2\x9e\xcc\x32\x99\xff\x38\xba\xa6\x95\xc6\x61\x4e\x7d\x25\xdb\x9a\x3e\x17\x8c\x4c\x16\xc3\xee",80))
printf("strip: 6000000000283254, Pass\n");
else
printf("strip: 6000000000283254, Failed\n");
writel(0x00000012&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00000e0c,"\x45\x00\x00\x3c\x00\x00\x00\x00\x80\x32\x32\x36\x86\x21\xe9\x71\xca\x63\xce\x63\x00\x00\x43\x21\x00\x00\x00\x82\x00\x00\x00\x82\x00\x00\x12\x34\x0d\x73\xf6\x2b\x7e\xfe\x25\x44\x6a\x89\x74\x38\x7d\x9c\xef\x30\x0e\xec\x7f\x71\xd5\x9f\x01\x56",60))
printf("strip: 4500003c00000000, Pass\n");
else
printf("strip: 4500003c00000000, Failed\n");
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00000ea0,"\x60\x00\x00\x00\x00\x28\x32\x54\x32\x60\x8b\x26\xfd\xfb\x25\x67\xae\xe0\x7e\xea\x52\x7f\x7f\xab\x33\x9c\x38\x57\xf6\xe6\xd1\x09\x25\x41\xc8\xd7\x95\xb7\xce\x10\x00\x00\x87\x65\x00\x00\x00\x52\x00\x00\x00\x52\x00\x00\x56\x78\x31\xbc\x84\xe7\x7c\xac\x4a\xd8\x2b\x10\x22\x6c\x29\x6a\x7b\x9f\x4f\x94\x18\x51\x02\x77\xac\x21",80))
printf("strip: 6000000000283254, Pass\n");
else
printf("strip: 6000000000283254, Failed\n");
}

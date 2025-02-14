#include <common.h>
#include <malloc.h>

extern volatile unsigned int ivp_cae_base_addr;

void test_ipsec_esp_out_aes_ctr_sha2_transport(void)
{
unsigned int *context_ptr=(unsigned int *)0x14000000;
printf("test_ipsec_esp_out_aes_ctr_sha2_transport\n");
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
*((unsigned int *)((unsigned long)context_ptr+0x00000c00))=0x19eb1706;
*((unsigned int *)((unsigned long)context_ptr+0x00000c00+4*1))=0x57000422;
*((unsigned int *)((unsigned long)context_ptr+0x00000c00+4*2))=0x426bc2d8;
*((unsigned int *)((unsigned long)context_ptr+0x00000c00+4*3))=0x4dc86782;
*((unsigned int *)((unsigned long)context_ptr+0x00000c00+4*4))=0x81e8957a;
*((unsigned int *)((unsigned long)context_ptr+0x00000c00+4*5))=0x409ec148;
*((unsigned int *)((unsigned long)context_ptr+0x00000c00+4*6))=0x35a54447;
*((unsigned int *)((unsigned long)context_ptr+0x00000c00+4*7))=0x34646ec0;
*((unsigned int *)((unsigned long)context_ptr+0x00000c00+4*8))=0x6a876519;
*((unsigned int *)((unsigned long)context_ptr+0x00000c00+4*9))=0x2411d1ea;
*((unsigned int *)((unsigned long)context_ptr+0x00000c00+4*10))=0x426dada4;
*((unsigned int *)((unsigned long)context_ptr+0x00000c00+4*11))=0x9ce0a723;
*((unsigned int *)((unsigned long)context_ptr+0x00000c00+4*12))=0x405a0da0;
*((unsigned int *)((unsigned long)context_ptr+0x00000c00+4*13))=0x3a8a37d1;
*((unsigned int *)((unsigned long)context_ptr+0x00000c00+4*14))=0x8903c1af;
*((unsigned int *)((unsigned long)context_ptr+0x00000c00+4*15))=0x883c33dc;
*((unsigned int *)((unsigned long)context_ptr+0x00000c00+4*16))=0x12173f87;
*((unsigned int *)((unsigned long)context_ptr+0x00000c00+4*17))=0x72c2ae69;
*((unsigned int *)((unsigned long)context_ptr+0x00000c00+4*18))=0xafe09da0;
*((unsigned int *)((unsigned long)context_ptr+0x00000c00+4*19))=0x5e132b36;
*((unsigned int *)((unsigned long)context_ptr+0x00000c00+4*20))=0x4ed31622;
*((unsigned int *)((unsigned long)context_ptr+0x00000c00+4*21))=0x13a7711f;
*((unsigned int *)((unsigned long)context_ptr+0x00000c00+4*22))=0x00008765;
*((unsigned int *)((unsigned long)context_ptr+0x00000c00+4*23))=0x00000050;
*((unsigned int *)((unsigned long)context_ptr+0x00000c00+4*24))=0x44332211;
*((unsigned int *)((unsigned long)context_ptr+0x00000c64))=0x19eb1706;
*((unsigned int *)((unsigned long)context_ptr+0x00000c64+4*1))=0x57000422;
*((unsigned int *)((unsigned long)context_ptr+0x00000c64+4*2))=0x390ade15;
*((unsigned int *)((unsigned long)context_ptr+0x00000c64+4*3))=0x54d8030a;
*((unsigned int *)((unsigned long)context_ptr+0x00000c64+4*4))=0xf7a72629;
*((unsigned int *)((unsigned long)context_ptr+0x00000c64+4*5))=0x9280e681;
*((unsigned int *)((unsigned long)context_ptr+0x00000c64+4*6))=0x35a54447;
*((unsigned int *)((unsigned long)context_ptr+0x00000c64+4*7))=0x34646ec0;
*((unsigned int *)((unsigned long)context_ptr+0x00000c64+4*8))=0x6a876519;
*((unsigned int *)((unsigned long)context_ptr+0x00000c64+4*9))=0x2411d1ea;
*((unsigned int *)((unsigned long)context_ptr+0x00000c64+4*10))=0x426dada4;
*((unsigned int *)((unsigned long)context_ptr+0x00000c64+4*11))=0x9ce0a723;
*((unsigned int *)((unsigned long)context_ptr+0x00000c64+4*12))=0x405a0da0;
*((unsigned int *)((unsigned long)context_ptr+0x00000c64+4*13))=0x3a8a37d1;
*((unsigned int *)((unsigned long)context_ptr+0x00000c64+4*14))=0x8903c1af;
*((unsigned int *)((unsigned long)context_ptr+0x00000c64+4*15))=0x883c33dc;
*((unsigned int *)((unsigned long)context_ptr+0x00000c64+4*16))=0x12173f87;
*((unsigned int *)((unsigned long)context_ptr+0x00000c64+4*17))=0x72c2ae69;
*((unsigned int *)((unsigned long)context_ptr+0x00000c64+4*18))=0xafe09da0;
*((unsigned int *)((unsigned long)context_ptr+0x00000c64+4*19))=0x5e132b36;
*((unsigned int *)((unsigned long)context_ptr+0x00000c64+4*20))=0x4ed31622;
*((unsigned int *)((unsigned long)context_ptr+0x00000c64+4*21))=0x13a7711f;
*((unsigned int *)((unsigned long)context_ptr+0x00000c64+4*22))=0x00004321;
*((unsigned int *)((unsigned long)context_ptr+0x00000c64+4*23))=0x00003300;
*((unsigned int *)((unsigned long)context_ptr+0x00000c64+4*24))=0x44332211;
*((unsigned int *)((unsigned long)context_ptr+0x00000cc8))=0x61320040;
*((unsigned int *)((unsigned long)context_ptr+0x00000cc8+4*1))=0x01000008;
*((unsigned int *)((unsigned long)context_ptr+0x00000cc8+4*2))=0x23900008;
*((unsigned int *)((unsigned long)context_ptr+0x00000cc8+4*3))=0x93415008;
*((unsigned int *)((unsigned long)context_ptr+0x00000cc8+4*4))=0x0700000a;
*((unsigned int *)((unsigned long)context_ptr+0x00000cc8+4*5))=0x2f23ea02;
*((unsigned int *)((unsigned long)context_ptr+0x00000cc8+4*6))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x00000cc8+4*7))=0xe1561817;
*((unsigned int *)((unsigned long)context_ptr+0x00000ce8))=0x1e000045;
*((unsigned int *)((unsigned long)context_ptr+0x00000ce8+4*1))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x00000ce8+4*2))=0x9131f580;
*((unsigned int *)((unsigned long)context_ptr+0x00000ce8+4*3))=0x71e92186;
*((unsigned int *)((unsigned long)context_ptr+0x00000ce8+4*4))=0x63ce63ca;
*((unsigned int *)((unsigned long)context_ptr+0x00000ce8+4*5))=0xcbc765d6;
*((unsigned int *)((unsigned long)context_ptr+0x00000ce8+4*6))=0xc45633e8;
*((unsigned int *)((unsigned long)context_ptr+0x00000ce8+4*7))=0x00008d47;
*((unsigned int *)((unsigned long)context_ptr+0x00000600))=0x04c00040;
*((unsigned int *)((unsigned long)context_ptr+0x00000600+4*1))=0x00000d08;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000000))=0x08c0001e;
*((unsigned int *)((unsigned long)context_ptr+0x00000000+4*1))=0x00000ce8;
*((unsigned int *)((unsigned long)context_ptr+0x00000000+4*2))=0x00000cc8;
*((unsigned int *)((unsigned long)context_ptr+0x00000000+4*3))=0x0022001e;
*((unsigned int *)((unsigned long)context_ptr+0x00000000+4*4))=0x00385c5f;
*((unsigned int *)((unsigned long)context_ptr+0x00000000+4*5))=0x00000c64+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x00000d48))=0x8132002c;
*((unsigned int *)((unsigned long)context_ptr+0x00000d48+4*1))=0x01000020;
*((unsigned int *)((unsigned long)context_ptr+0x00000d48+4*2))=0x23900008;
*((unsigned int *)((unsigned long)context_ptr+0x00000d48+4*3))=0x93415008;
*((unsigned int *)((unsigned long)context_ptr+0x00000d48+4*4))=0x0700000a;
*((unsigned int *)((unsigned long)context_ptr+0x00000d48+4*5))=0x2f232402;
*((unsigned int *)((unsigned long)context_ptr+0x00000d48+4*6))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x00000d48+4*7))=0xe1561817;
*((unsigned int *)((unsigned long)context_ptr+0x00000d68))=0x00000060;
*((unsigned int *)((unsigned long)context_ptr+0x00000d68+4*1))=0x54920a00;
*((unsigned int *)((unsigned long)context_ptr+0x00000d68+4*2))=0x268b6032;
*((unsigned int *)((unsigned long)context_ptr+0x00000d68+4*3))=0x6725fbfd;
*((unsigned int *)((unsigned long)context_ptr+0x00000d68+4*4))=0xea7ee0ae;
*((unsigned int *)((unsigned long)context_ptr+0x00000d68+4*5))=0xab7f7f52;
*((unsigned int *)((unsigned long)context_ptr+0x00000d68+4*6))=0x57389c33;
*((unsigned int *)((unsigned long)context_ptr+0x00000d68+4*7))=0x09d1e6f6;
*((unsigned int *)((unsigned long)context_ptr+0x00000d68+4*8))=0xd7c84125;
*((unsigned int *)((unsigned long)context_ptr+0x00000d68+4*9))=0x10ceb795;
*((unsigned int *)((unsigned long)context_ptr+0x00000d68+4*10))=0x835da07a;
*((unsigned int *)((unsigned long)context_ptr+0x00000d68+4*11))=0xb7a2e9f2;
*((unsigned int *)((unsigned long)context_ptr+0x00000d68+4*12))=0x00009b24;
*((unsigned int *)((unsigned long)context_ptr+0x00000618))=0x04c00054;
*((unsigned int *)((unsigned long)context_ptr+0x00000618+4*1))=0x00000d9c;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000018))=0x08c00032;
*((unsigned int *)((unsigned long)context_ptr+0x00000018+4*1))=0x00000d68;
*((unsigned int *)((unsigned long)context_ptr+0x00000018+4*2))=0x00000d48;
*((unsigned int *)((unsigned long)context_ptr+0x00000018+4*3))=0x00220032;
*((unsigned int *)((unsigned long)context_ptr+0x00000018+4*4))=0x001a32e1;
*((unsigned int *)((unsigned long)context_ptr+0x00000018+4*5))=0x00000c00+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x00000df0))=0x61320044;
*((unsigned int *)((unsigned long)context_ptr+0x00000df0+4*1))=0x01000008;
*((unsigned int *)((unsigned long)context_ptr+0x00000df0+4*2))=0x23900008;
*((unsigned int *)((unsigned long)context_ptr+0x00000df0+4*3))=0x93415008;
*((unsigned int *)((unsigned long)context_ptr+0x00000df0+4*4))=0x0700000b;
*((unsigned int *)((unsigned long)context_ptr+0x00000df0+4*5))=0x2f233405;
*((unsigned int *)((unsigned long)context_ptr+0x00000df0+4*6))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x00000df0+4*7))=0xe1561817;
*((unsigned int *)((unsigned long)context_ptr+0x00000e10))=0x1f000045;
*((unsigned int *)((unsigned long)context_ptr+0x00000e10+4*1))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x00000e10+4*2))=0xeb319a80;
*((unsigned int *)((unsigned long)context_ptr+0x00000e10+4*3))=0x71e92186;
*((unsigned int *)((unsigned long)context_ptr+0x00000e10+4*4))=0x63ce63ca;
*((unsigned int *)((unsigned long)context_ptr+0x00000e10+4*5))=0xcd233e05;
*((unsigned int *)((unsigned long)context_ptr+0x00000e10+4*6))=0x1c216628;
*((unsigned int *)((unsigned long)context_ptr+0x00000e10+4*7))=0x008338fe;
*((unsigned int *)((unsigned long)context_ptr+0x00000630))=0x04c00044;
*((unsigned int *)((unsigned long)context_ptr+0x00000630+4*1))=0x00000e30;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000030))=0x08c0001f;
*((unsigned int *)((unsigned long)context_ptr+0x00000030+4*1))=0x00000e10;
*((unsigned int *)((unsigned long)context_ptr+0x00000030+4*2))=0x00000df0;
*((unsigned int *)((unsigned long)context_ptr+0x00000030+4*3))=0x0022001f;
*((unsigned int *)((unsigned long)context_ptr+0x00000030+4*4))=0x0020ca35;
*((unsigned int *)((unsigned long)context_ptr+0x00000030+4*5))=0x00000c64+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x00000e74))=0x81320030;
*((unsigned int *)((unsigned long)context_ptr+0x00000e74+4*1))=0x01000020;
*((unsigned int *)((unsigned long)context_ptr+0x00000e74+4*2))=0x23900008;
*((unsigned int *)((unsigned long)context_ptr+0x00000e74+4*3))=0x93415008;
*((unsigned int *)((unsigned long)context_ptr+0x00000e74+4*4))=0x0700000b;
*((unsigned int *)((unsigned long)context_ptr+0x00000e74+4*5))=0x2f238005;
*((unsigned int *)((unsigned long)context_ptr+0x00000e74+4*6))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x00000e74+4*7))=0xe1561817;
*((unsigned int *)((unsigned long)context_ptr+0x00000e94))=0x00000060;
*((unsigned int *)((unsigned long)context_ptr+0x00000e94+4*1))=0x54c00b00;
*((unsigned int *)((unsigned long)context_ptr+0x00000e94+4*2))=0x268b6032;
*((unsigned int *)((unsigned long)context_ptr+0x00000e94+4*3))=0x6725fbfd;
*((unsigned int *)((unsigned long)context_ptr+0x00000e94+4*4))=0xea7ee0ae;
*((unsigned int *)((unsigned long)context_ptr+0x00000e94+4*5))=0xab7f7f52;
*((unsigned int *)((unsigned long)context_ptr+0x00000e94+4*6))=0x57389c33;
*((unsigned int *)((unsigned long)context_ptr+0x00000e94+4*7))=0x09d1e6f6;
*((unsigned int *)((unsigned long)context_ptr+0x00000e94+4*8))=0xd7c84125;
*((unsigned int *)((unsigned long)context_ptr+0x00000e94+4*9))=0x10ceb795;
*((unsigned int *)((unsigned long)context_ptr+0x00000e94+4*10))=0xa24c9cd6;
*((unsigned int *)((unsigned long)context_ptr+0x00000e94+4*11))=0x4bf87e86;
*((unsigned int *)((unsigned long)context_ptr+0x00000e94+4*12))=0x00c486c4;
*((unsigned int *)((unsigned long)context_ptr+0x00000648))=0x04c00058;
*((unsigned int *)((unsigned long)context_ptr+0x00000648+4*1))=0x00000ec8;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000048))=0x08c00033;
*((unsigned int *)((unsigned long)context_ptr+0x00000048+4*1))=0x00000e94;
*((unsigned int *)((unsigned long)context_ptr+0x00000048+4*2))=0x00000e74;
*((unsigned int *)((unsigned long)context_ptr+0x00000048+4*3))=0x00220033;
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
if(!memcmp((unsigned char *)context_ptr+0x00000d08,"\x45\x00\x00\x40\x00\x00\x00\x00\x80\x32\x32\x32\x86\x21\xe9\x71\xca\x63\xce\x63\x00\x00\x43\x21\x00\x00\x33\x01\x00\x00\x33\x01\x00\x00\x00\x00\x3c\xd9\x2b\x17\x82\x8b\x50\xa7\x75\xcf\xed\x6f\xd6\xdc\x67\x11\x29\x5d\xe0\x73\x60\x1b\x96\xf9\x7b\x2b\x8f\xcc",64))
printf("strip: 4500004000000000, Pass\n");
else
printf("strip: 4500004000000000, Failed\n");
writel(0x0000000c&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00000d9c,"\x60\x00\x00\x00\x00\x2c\x32\x54\x32\x60\x8b\x26\xfd\xfb\x25\x67\xae\xe0\x7e\xea\x52\x7f\x7f\xab\x33\x9c\x38\x57\xf6\xe6\xd1\x09\x25\x41\xc8\xd7\x95\xb7\xce\x10\x00\x00\x87\x65\x00\x00\x00\x51\x00\x00\x00\x51\x00\x00\x00\x00\xdf\x6e\x68\xfe\x1a\x6e\xfd\x30\x43\xb6\xf3\x76\xb9\x1e\x10\x63\x53\x7e\xf4\x0f\x81\xdf\x20\x7e\x4f\x9a\xed\x81",84))
printf("strip: 60000000002c3254, Pass\n");
else
printf("strip: 60000000002c3254, Failed\n");
writel(0x00000012&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00000e30,"\x45\x00\x00\x44\x00\x00\x00\x00\x80\x32\x32\x2e\x86\x21\xe9\x71\xca\x63\xce\x63\x00\x00\x43\x21\x00\x00\x33\x02\x00\x00\x33\x02\x00\x00\x00\x00\x58\xdb\x6f\xe1\xbb\xea\x31\xf8\xdf\x79\x77\x9d\xfb\xbb\x8b\xd8\xa5\xf1\x86\x8f\x65\xc1\xc3\x72\xd4\xc3\x72\xd6\xd7\xc9\x74\x69",68))
printf("strip: 4500004400000000, Pass\n");
else
printf("strip: 4500004400000000, Failed\n");
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00000ec8,"\x60\x00\x00\x00\x00\x30\x32\x54\x32\x60\x8b\x26\xfd\xfb\x25\x67\xae\xe0\x7e\xea\x52\x7f\x7f\xab\x33\x9c\x38\x57\xf6\xe6\xd1\x09\x25\x41\xc8\xd7\x95\xb7\xce\x10\x00\x00\x87\x65\x00\x00\x00\x52\x00\x00\x00\x52\x00\x00\x00\x00\x7b\x6a\x3d\x62\x70\x1b\xd3\xcd\x0a\xf8\x2e\xc8\xd4\x79\xdb\x6f\x96\x44\xaa\x47\xd8\x07\xfe\x18\x29\x7a\xab\xd4\x89\xca\x0d\x52",88))
printf("strip: 6000000000303254, Pass\n");
else
printf("strip: 6000000000303254, Failed\n");
}

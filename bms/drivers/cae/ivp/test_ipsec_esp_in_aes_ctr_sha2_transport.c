#include <common.h>
#include <malloc.h>

extern volatile unsigned int ivp_cae_base_addr;

void test_ipsec_esp_in_aes_ctr_sha2_transport(void)
{
unsigned int *context_ptr=(unsigned int *)0x14000000;
printf("test_ipsec_esp_in_aes_ctr_sha2_transport\n");
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
*((unsigned int *)((unsigned long)context_ptr+0x00000c00))=0x59eb190f;
*((unsigned int *)((unsigned long)context_ptr+0x00000c00+4*1))=0x57010422;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000c00+4*24))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00000c00+4*25))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x00000c00+4*26))=0x44332211;
*((unsigned int *)((unsigned long)context_ptr+0x00000c6c))=0x59eb190f;
*((unsigned int *)((unsigned long)context_ptr+0x00000c6c+4*1))=0x57010422;
*((unsigned int *)((unsigned long)context_ptr+0x00000c6c+4*2))=0x390ade15;
*((unsigned int *)((unsigned long)context_ptr+0x00000c6c+4*3))=0x54d8030a;
*((unsigned int *)((unsigned long)context_ptr+0x00000c6c+4*4))=0xf7a72629;
*((unsigned int *)((unsigned long)context_ptr+0x00000c6c+4*5))=0x9280e681;
*((unsigned int *)((unsigned long)context_ptr+0x00000c6c+4*6))=0x35a54447;
*((unsigned int *)((unsigned long)context_ptr+0x00000c6c+4*7))=0x34646ec0;
*((unsigned int *)((unsigned long)context_ptr+0x00000c6c+4*8))=0x6a876519;
*((unsigned int *)((unsigned long)context_ptr+0x00000c6c+4*9))=0x2411d1ea;
*((unsigned int *)((unsigned long)context_ptr+0x00000c6c+4*10))=0x426dada4;
*((unsigned int *)((unsigned long)context_ptr+0x00000c6c+4*11))=0x9ce0a723;
*((unsigned int *)((unsigned long)context_ptr+0x00000c6c+4*12))=0x405a0da0;
*((unsigned int *)((unsigned long)context_ptr+0x00000c6c+4*13))=0x3a8a37d1;
*((unsigned int *)((unsigned long)context_ptr+0x00000c6c+4*14))=0x8903c1af;
*((unsigned int *)((unsigned long)context_ptr+0x00000c6c+4*15))=0x883c33dc;
*((unsigned int *)((unsigned long)context_ptr+0x00000c6c+4*16))=0x12173f87;
*((unsigned int *)((unsigned long)context_ptr+0x00000c6c+4*17))=0x72c2ae69;
*((unsigned int *)((unsigned long)context_ptr+0x00000c6c+4*18))=0xafe09da0;
*((unsigned int *)((unsigned long)context_ptr+0x00000c6c+4*19))=0x5e132b36;
*((unsigned int *)((unsigned long)context_ptr+0x00000c6c+4*20))=0x4ed31622;
*((unsigned int *)((unsigned long)context_ptr+0x00000c6c+4*21))=0x13a7711f;
*((unsigned int *)((unsigned long)context_ptr+0x00000c6c+4*22))=0x00004321;
*((unsigned int *)((unsigned long)context_ptr+0x00000c6c+4*23))=0x00003300;
*((unsigned int *)((unsigned long)context_ptr+0x00000c6c+4*24))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00000c6c+4*25))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x00000c6c+4*26))=0x44332211;
*((unsigned int *)((unsigned long)context_ptr+0x00000cd8))=0x61000000;
*((unsigned int *)((unsigned long)context_ptr+0x00000cd8+4*1))=0x01000008;
*((unsigned int *)((unsigned long)context_ptr+0x00000cd8+4*2))=0x42900008;
*((unsigned int *)((unsigned long)context_ptr+0x00000cd8+4*3))=0x42a80008;
*((unsigned int *)((unsigned long)context_ptr+0x00000cd8+4*4))=0x0f02000c;
*((unsigned int *)((unsigned long)context_ptr+0x00000cd8+4*5))=0x40e60010;
*((unsigned int *)((unsigned long)context_ptr+0x00000cd8+4*6))=0xae3dfffe;
*((unsigned int *)((unsigned long)context_ptr+0x00000cd8+4*7))=0xdd070010;
*((unsigned int *)((unsigned long)context_ptr+0x00000cd8+4*8))=0xe32e1817;
*((unsigned int *)((unsigned long)context_ptr+0x00000cfc))=0x40000045;
*((unsigned int *)((unsigned long)context_ptr+0x00000cfc+4*1))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x00000cfc+4*2))=0x32323280;
*((unsigned int *)((unsigned long)context_ptr+0x00000cfc+4*3))=0x71e92186;
*((unsigned int *)((unsigned long)context_ptr+0x00000cfc+4*4))=0x63ce63ca;
*((unsigned int *)((unsigned long)context_ptr+0x00000cfc+4*5))=0x21430000;
*((unsigned int *)((unsigned long)context_ptr+0x00000cfc+4*6))=0x01330000;
*((unsigned int *)((unsigned long)context_ptr+0x00000cfc+4*7))=0x01330000;
*((unsigned int *)((unsigned long)context_ptr+0x00000cfc+4*8))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x00000cfc+4*9))=0x172bd93c;
*((unsigned int *)((unsigned long)context_ptr+0x00000cfc+4*10))=0xa7508b82;
*((unsigned int *)((unsigned long)context_ptr+0x00000cfc+4*11))=0x6fedcf75;
*((unsigned int *)((unsigned long)context_ptr+0x00000cfc+4*12))=0x1167dcd6;
*((unsigned int *)((unsigned long)context_ptr+0x00000cfc+4*13))=0x73e05d29;
*((unsigned int *)((unsigned long)context_ptr+0x00000cfc+4*14))=0xf9961b60;
*((unsigned int *)((unsigned long)context_ptr+0x00000cfc+4*15))=0xcc8f2b7b;
*((unsigned int *)((unsigned long)context_ptr+0x00000600))=0x04c0002c;
*((unsigned int *)((unsigned long)context_ptr+0x00000600+4*1))=0x00000d3c;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000000))=0x09c00040;
*((unsigned int *)((unsigned long)context_ptr+0x00000000+4*1))=0x00000cfc;
*((unsigned int *)((unsigned long)context_ptr+0x00000000+4*2))=0x00000cd8;
*((unsigned int *)((unsigned long)context_ptr+0x00000000+4*3))=0x01e20040;
*((unsigned int *)((unsigned long)context_ptr+0x00000000+4*4))=0x00385c5f;
*((unsigned int *)((unsigned long)context_ptr+0x00000000+4*5))=0x00000c6c+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x00000d68))=0x81000000;
*((unsigned int *)((unsigned long)context_ptr+0x00000d68+4*1))=0x01000020;
*((unsigned int *)((unsigned long)context_ptr+0x00000d68+4*2))=0x42900008;
*((unsigned int *)((unsigned long)context_ptr+0x00000d68+4*3))=0x42a80008;
*((unsigned int *)((unsigned long)context_ptr+0x00000d68+4*4))=0x0f02000c;
*((unsigned int *)((unsigned long)context_ptr+0x00000d68+4*5))=0x40e60010;
*((unsigned int *)((unsigned long)context_ptr+0x00000d68+4*6))=0xad47fffe;
*((unsigned int *)((unsigned long)context_ptr+0x00000d68+4*7))=0xdd070010;
*((unsigned int *)((unsigned long)context_ptr+0x00000d68+4*8))=0xe32e1817;
*((unsigned int *)((unsigned long)context_ptr+0x00000d8c))=0x00000060;
*((unsigned int *)((unsigned long)context_ptr+0x00000d8c+4*1))=0x54322c00;
*((unsigned int *)((unsigned long)context_ptr+0x00000d8c+4*2))=0x268b6032;
*((unsigned int *)((unsigned long)context_ptr+0x00000d8c+4*3))=0x6725fbfd;
*((unsigned int *)((unsigned long)context_ptr+0x00000d8c+4*4))=0xea7ee0ae;
*((unsigned int *)((unsigned long)context_ptr+0x00000d8c+4*5))=0xab7f7f52;
*((unsigned int *)((unsigned long)context_ptr+0x00000d8c+4*6))=0x57389c33;
*((unsigned int *)((unsigned long)context_ptr+0x00000d8c+4*7))=0x09d1e6f6;
*((unsigned int *)((unsigned long)context_ptr+0x00000d8c+4*8))=0xd7c84125;
*((unsigned int *)((unsigned long)context_ptr+0x00000d8c+4*9))=0x10ceb795;
*((unsigned int *)((unsigned long)context_ptr+0x00000d8c+4*10))=0x65870000;
*((unsigned int *)((unsigned long)context_ptr+0x00000d8c+4*11))=0x51000000;
*((unsigned int *)((unsigned long)context_ptr+0x00000d8c+4*12))=0x51000000;
*((unsigned int *)((unsigned long)context_ptr+0x00000d8c+4*13))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x00000d8c+4*14))=0xfe686edf;
*((unsigned int *)((unsigned long)context_ptr+0x00000d8c+4*15))=0x30fd6e1a;
*((unsigned int *)((unsigned long)context_ptr+0x00000d8c+4*16))=0x76f3b643;
*((unsigned int *)((unsigned long)context_ptr+0x00000d8c+4*17))=0x63101eb9;
*((unsigned int *)((unsigned long)context_ptr+0x00000d8c+4*18))=0x0ff47e53;
*((unsigned int *)((unsigned long)context_ptr+0x00000d8c+4*19))=0x7e20df81;
*((unsigned int *)((unsigned long)context_ptr+0x00000d8c+4*20))=0x81ed9a4f;
*((unsigned int *)((unsigned long)context_ptr+0x00000618))=0x04c0003c;
*((unsigned int *)((unsigned long)context_ptr+0x00000618+4*1))=0x00000de0;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000018))=0x09c00054;
*((unsigned int *)((unsigned long)context_ptr+0x00000018+4*1))=0x00000d8c;
*((unsigned int *)((unsigned long)context_ptr+0x00000018+4*2))=0x00000d68;
*((unsigned int *)((unsigned long)context_ptr+0x00000018+4*3))=0x01e20054;
*((unsigned int *)((unsigned long)context_ptr+0x00000018+4*4))=0x001a32e1;
*((unsigned int *)((unsigned long)context_ptr+0x00000018+4*5))=0x00000c00+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x00000e1c))=0x61000000;
*((unsigned int *)((unsigned long)context_ptr+0x00000e1c+4*1))=0x01000008;
*((unsigned int *)((unsigned long)context_ptr+0x00000e1c+4*2))=0x42900008;
*((unsigned int *)((unsigned long)context_ptr+0x00000e1c+4*3))=0x42a80008;
*((unsigned int *)((unsigned long)context_ptr+0x00000e1c+4*4))=0x0f020010;
*((unsigned int *)((unsigned long)context_ptr+0x00000e1c+4*5))=0x40e60010;
*((unsigned int *)((unsigned long)context_ptr+0x00000e1c+4*6))=0xae3dfffe;
*((unsigned int *)((unsigned long)context_ptr+0x00000e1c+4*7))=0xdd070010;
*((unsigned int *)((unsigned long)context_ptr+0x00000e1c+4*8))=0xe32e1817;
*((unsigned int *)((unsigned long)context_ptr+0x00000e40))=0x44000045;
*((unsigned int *)((unsigned long)context_ptr+0x00000e40+4*1))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x00000e40+4*2))=0x2e323280;
*((unsigned int *)((unsigned long)context_ptr+0x00000e40+4*3))=0x71e92186;
*((unsigned int *)((unsigned long)context_ptr+0x00000e40+4*4))=0x63ce63ca;
*((unsigned int *)((unsigned long)context_ptr+0x00000e40+4*5))=0x21430000;
*((unsigned int *)((unsigned long)context_ptr+0x00000e40+4*6))=0x02330000;
*((unsigned int *)((unsigned long)context_ptr+0x00000e40+4*7))=0x02330000;
*((unsigned int *)((unsigned long)context_ptr+0x00000e40+4*8))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x00000e40+4*9))=0xe16fdb58;
*((unsigned int *)((unsigned long)context_ptr+0x00000e40+4*10))=0xf831eabb;
*((unsigned int *)((unsigned long)context_ptr+0x00000e40+4*11))=0x9d7779df;
*((unsigned int *)((unsigned long)context_ptr+0x00000e40+4*12))=0xd88bbbfb;
*((unsigned int *)((unsigned long)context_ptr+0x00000e40+4*13))=0x8f86f1a5;
*((unsigned int *)((unsigned long)context_ptr+0x00000e40+4*14))=0x72c3c165;
*((unsigned int *)((unsigned long)context_ptr+0x00000e40+4*15))=0xd672c3d4;
*((unsigned int *)((unsigned long)context_ptr+0x00000e40+4*16))=0x6974c9d7;
*((unsigned int *)((unsigned long)context_ptr+0x00000630))=0x04c0002c;
*((unsigned int *)((unsigned long)context_ptr+0x00000630+4*1))=0x00000e84;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000030))=0x09c00044;
*((unsigned int *)((unsigned long)context_ptr+0x00000030+4*1))=0x00000e40;
*((unsigned int *)((unsigned long)context_ptr+0x00000030+4*2))=0x00000e1c;
*((unsigned int *)((unsigned long)context_ptr+0x00000030+4*3))=0x01e20044;
*((unsigned int *)((unsigned long)context_ptr+0x00000030+4*4))=0x0020ca35;
*((unsigned int *)((unsigned long)context_ptr+0x00000030+4*5))=0x00000c6c+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x00000eb0))=0x81000000;
*((unsigned int *)((unsigned long)context_ptr+0x00000eb0+4*1))=0x01000020;
*((unsigned int *)((unsigned long)context_ptr+0x00000eb0+4*2))=0x42900008;
*((unsigned int *)((unsigned long)context_ptr+0x00000eb0+4*3))=0x42a80008;
*((unsigned int *)((unsigned long)context_ptr+0x00000eb0+4*4))=0x0f020010;
*((unsigned int *)((unsigned long)context_ptr+0x00000eb0+4*5))=0x40e60010;
*((unsigned int *)((unsigned long)context_ptr+0x00000eb0+4*6))=0xad47fffe;
*((unsigned int *)((unsigned long)context_ptr+0x00000eb0+4*7))=0xdd070010;
*((unsigned int *)((unsigned long)context_ptr+0x00000eb0+4*8))=0xe32e1817;
*((unsigned int *)((unsigned long)context_ptr+0x00000ed4))=0x00000060;
*((unsigned int *)((unsigned long)context_ptr+0x00000ed4+4*1))=0x54323000;
*((unsigned int *)((unsigned long)context_ptr+0x00000ed4+4*2))=0x268b6032;
*((unsigned int *)((unsigned long)context_ptr+0x00000ed4+4*3))=0x6725fbfd;
*((unsigned int *)((unsigned long)context_ptr+0x00000ed4+4*4))=0xea7ee0ae;
*((unsigned int *)((unsigned long)context_ptr+0x00000ed4+4*5))=0xab7f7f52;
*((unsigned int *)((unsigned long)context_ptr+0x00000ed4+4*6))=0x57389c33;
*((unsigned int *)((unsigned long)context_ptr+0x00000ed4+4*7))=0x09d1e6f6;
*((unsigned int *)((unsigned long)context_ptr+0x00000ed4+4*8))=0xd7c84125;
*((unsigned int *)((unsigned long)context_ptr+0x00000ed4+4*9))=0x10ceb795;
*((unsigned int *)((unsigned long)context_ptr+0x00000ed4+4*10))=0x65870000;
*((unsigned int *)((unsigned long)context_ptr+0x00000ed4+4*11))=0x52000000;
*((unsigned int *)((unsigned long)context_ptr+0x00000ed4+4*12))=0x52000000;
*((unsigned int *)((unsigned long)context_ptr+0x00000ed4+4*13))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x00000ed4+4*14))=0x623d6a7b;
*((unsigned int *)((unsigned long)context_ptr+0x00000ed4+4*15))=0xcdd31b70;
*((unsigned int *)((unsigned long)context_ptr+0x00000ed4+4*16))=0xc82ef80a;
*((unsigned int *)((unsigned long)context_ptr+0x00000ed4+4*17))=0x6fdb79d4;
*((unsigned int *)((unsigned long)context_ptr+0x00000ed4+4*18))=0x47aa4496;
*((unsigned int *)((unsigned long)context_ptr+0x00000ed4+4*19))=0x18fe07d8;
*((unsigned int *)((unsigned long)context_ptr+0x00000ed4+4*20))=0xd4ab7a29;
*((unsigned int *)((unsigned long)context_ptr+0x00000ed4+4*21))=0x520dca89;
*((unsigned int *)((unsigned long)context_ptr+0x00000648))=0x04c0003c;
*((unsigned int *)((unsigned long)context_ptr+0x00000648+4*1))=0x00000f2c;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000048))=0x09c00058;
*((unsigned int *)((unsigned long)context_ptr+0x00000048+4*1))=0x00000ed4;
*((unsigned int *)((unsigned long)context_ptr+0x00000048+4*2))=0x00000eb0;
*((unsigned int *)((unsigned long)context_ptr+0x00000048+4*3))=0x01e20058;
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
if(!memcmp((unsigned char *)context_ptr+0x00000d3c,"\x45\x00\x00\x00\x00\x00\x00\x00\x80\x00\x32\xa4\x86\x21\xe9\x71\xca\x63\xce\x63\xd6\x65\xc7\xcb\xe8\x33\x56\xc4\x47\x8d\x00\xf5\x00\x1e\x00\x00\x00\xf5\x00\x00\x31\x91\x00\x00",44))
printf("strip: 4500000000000000, Pass\n");
else
printf("strip: 4500000000000000, Failed\n");
writel(0x0000000c&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00000de0,"\x60\x00\x00\x00\x00\x00\x00\x54\x32\x60\x8b\x26\xfd\xfb\x25\x67\xae\xe0\x7e\xea\x52\x7f\x7f\xab\x33\x9c\x38\x57\xf6\xe6\xd1\x09\x25\x41\xc8\xd7\x95\xb7\xce\x10\x7a\xa0\x5d\x83\xf2\xe9\xa2\xb7\x24\x9b\x00\x92\x00\x0a\x00\x00\x92\x00\x00\x00",60))
printf("strip: 6000000000000054, Pass\n");
else
printf("strip: 6000000000000054, Failed\n");
writel(0x00000012&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00000e84,"\x45\x00\x00\x00\x00\x00\x00\x00\x80\x00\x32\xa4\x86\x21\xe9\x71\xca\x63\xce\x63\x05\x3e\x23\xcd\x28\x66\x21\x1c\xfe\x38\x83\x01\x00\x1f\x00\x00\x00\x9a\x00\x00\x31\xeb\x00\x00",44))
printf("strip: 4500000000000000, Pass\n");
else
printf("strip: 4500000000000000, Failed\n");
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00000f2c,"\x60\x00\x00\x00\x00\x00\x00\x54\x32\x60\x8b\x26\xfd\xfb\x25\x67\xae\xe0\x7e\xea\x52\x7f\x7f\xab\x33\x9c\x38\x57\xf6\xe6\xd1\x09\x25\x41\xc8\xd7\x95\xb7\xce\x10\xd6\x9c\x4c\xa2\x86\x7e\xf8\x4b\xc4\x86\xc4\x01\x00\x0b\x00\x00\xc0\x00\x00\x00",60))
printf("strip: 6000000000000054, Pass\n");
else
printf("strip: 6000000000000054, Failed\n");
}

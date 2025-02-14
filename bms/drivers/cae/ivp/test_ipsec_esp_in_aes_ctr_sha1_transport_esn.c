#include <common.h>
#include <malloc.h>

extern volatile unsigned int ivp_cae_base_addr;

void test_ipsec_esp_in_aes_ctr_sha1_transport_esn(void)
{
unsigned int *context_ptr=(unsigned int *)0x14000000;
printf("test_ipsec_esp_in_aes_ctr_sha1_transport_esn\n");
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
*((unsigned int *)((unsigned long)context_ptr+0x00000c00))=0xd96b150f;
*((unsigned int *)((unsigned long)context_ptr+0x00000c00+4*1))=0x51010422;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000c00+4*18))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00000c00+4*19))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x00000c00+4*20))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x00000c00+4*21))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x00000c00+4*22))=0x44332211;
*((unsigned int *)((unsigned long)context_ptr+0x00000c5c))=0xd96b150f;
*((unsigned int *)((unsigned long)context_ptr+0x00000c5c+4*1))=0x51010422;
*((unsigned int *)((unsigned long)context_ptr+0x00000c5c+4*2))=0x390ade15;
*((unsigned int *)((unsigned long)context_ptr+0x00000c5c+4*3))=0x54d8030a;
*((unsigned int *)((unsigned long)context_ptr+0x00000c5c+4*4))=0xf7a72629;
*((unsigned int *)((unsigned long)context_ptr+0x00000c5c+4*5))=0x9280e681;
*((unsigned int *)((unsigned long)context_ptr+0x00000c5c+4*6))=0xd66e890f;
*((unsigned int *)((unsigned long)context_ptr+0x00000c5c+4*7))=0xca60dfa5;
*((unsigned int *)((unsigned long)context_ptr+0x00000c5c+4*8))=0x5b48e12a;
*((unsigned int *)((unsigned long)context_ptr+0x00000c5c+4*9))=0x9a0b4f52;
*((unsigned int *)((unsigned long)context_ptr+0x00000c5c+4*10))=0xa068b01d;
*((unsigned int *)((unsigned long)context_ptr+0x00000c5c+4*11))=0x726dc6be;
*((unsigned int *)((unsigned long)context_ptr+0x00000c5c+4*12))=0xd3aab56b;
*((unsigned int *)((unsigned long)context_ptr+0x00000c5c+4*13))=0x45c6247b;
*((unsigned int *)((unsigned long)context_ptr+0x00000c5c+4*14))=0x8d504ea7;
*((unsigned int *)((unsigned long)context_ptr+0x00000c5c+4*15))=0x765d00f2;
*((unsigned int *)((unsigned long)context_ptr+0x00000c5c+4*16))=0x00004321;
*((unsigned int *)((unsigned long)context_ptr+0x00000c5c+4*17))=0x00000080;
*((unsigned int *)((unsigned long)context_ptr+0x00000c5c+4*18))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00000c5c+4*19))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x00000c5c+4*20))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x00000c5c+4*21))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x00000c5c+4*22))=0x44332211;
*((unsigned int *)((unsigned long)context_ptr+0x00000cb8))=0x61000000;
*((unsigned int *)((unsigned long)context_ptr+0x00000cb8+4*1))=0x01000008;
*((unsigned int *)((unsigned long)context_ptr+0x00000cb8+4*2))=0x42900008;
*((unsigned int *)((unsigned long)context_ptr+0x00000cb8+4*3))=0x42a80008;
*((unsigned int *)((unsigned long)context_ptr+0x00000cb8+4*4))=0x0f02000c;
*((unsigned int *)((unsigned long)context_ptr+0x00000cb8+4*5))=0x40e6000c;
*((unsigned int *)((unsigned long)context_ptr+0x00000cb8+4*6))=0xae3dfffe;
*((unsigned int *)((unsigned long)context_ptr+0x00000cb8+4*7))=0xdd07000c;
*((unsigned int *)((unsigned long)context_ptr+0x00000cb8+4*8))=0xe52e1811;
*((unsigned int *)((unsigned long)context_ptr+0x00000cdc))=0x3c000045;
*((unsigned int *)((unsigned long)context_ptr+0x00000cdc+4*1))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x00000cdc+4*2))=0x36323280;
*((unsigned int *)((unsigned long)context_ptr+0x00000cdc+4*3))=0x71e92186;
*((unsigned int *)((unsigned long)context_ptr+0x00000cdc+4*4))=0x63ce63ca;
*((unsigned int *)((unsigned long)context_ptr+0x00000cdc+4*5))=0x21430000;
*((unsigned int *)((unsigned long)context_ptr+0x00000cdc+4*6))=0x81000000;
*((unsigned int *)((unsigned long)context_ptr+0x00000cdc+4*7))=0x81000000;
*((unsigned int *)((unsigned long)context_ptr+0x00000cdc+4*8))=0x34120000;
*((unsigned int *)((unsigned long)context_ptr+0x00000cdc+4*9))=0xdb98c03e;
*((unsigned int *)((unsigned long)context_ptr+0x00000cdc+4*10))=0x2162ab1c;
*((unsigned int *)((unsigned long)context_ptr+0x00000cdc+4*11))=0x87f01640;
*((unsigned int *)((unsigned long)context_ptr+0x00000cdc+4*12))=0x7f046d99;
*((unsigned int *)((unsigned long)context_ptr+0x00000cdc+4*13))=0x10fd009b;
*((unsigned int *)((unsigned long)context_ptr+0x00000cdc+4*14))=0xbab9f04c;
*((unsigned int *)((unsigned long)context_ptr+0x00000600))=0x04c0002c;
*((unsigned int *)((unsigned long)context_ptr+0x00000600+4*1))=0x00000d18;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000000))=0x09c0003c;
*((unsigned int *)((unsigned long)context_ptr+0x00000000+4*1))=0x00000cdc;
*((unsigned int *)((unsigned long)context_ptr+0x00000000+4*2))=0x00000cb8;
*((unsigned int *)((unsigned long)context_ptr+0x00000000+4*3))=0x01e2003c;
*((unsigned int *)((unsigned long)context_ptr+0x00000000+4*4))=0x00385c5f;
*((unsigned int *)((unsigned long)context_ptr+0x00000000+4*5))=0x00000c5c+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x00000d44))=0x81000000;
*((unsigned int *)((unsigned long)context_ptr+0x00000d44+4*1))=0x01000020;
*((unsigned int *)((unsigned long)context_ptr+0x00000d44+4*2))=0x42900008;
*((unsigned int *)((unsigned long)context_ptr+0x00000d44+4*3))=0x42a80008;
*((unsigned int *)((unsigned long)context_ptr+0x00000d44+4*4))=0x0f02000c;
*((unsigned int *)((unsigned long)context_ptr+0x00000d44+4*5))=0x40e6000c;
*((unsigned int *)((unsigned long)context_ptr+0x00000d44+4*6))=0xad47fffe;
*((unsigned int *)((unsigned long)context_ptr+0x00000d44+4*7))=0xdd07000c;
*((unsigned int *)((unsigned long)context_ptr+0x00000d44+4*8))=0xe52e1811;
*((unsigned int *)((unsigned long)context_ptr+0x00000d68))=0x00000060;
*((unsigned int *)((unsigned long)context_ptr+0x00000d68+4*1))=0x54322800;
*((unsigned int *)((unsigned long)context_ptr+0x00000d68+4*2))=0x268b6032;
*((unsigned int *)((unsigned long)context_ptr+0x00000d68+4*3))=0x6725fbfd;
*((unsigned int *)((unsigned long)context_ptr+0x00000d68+4*4))=0xea7ee0ae;
*((unsigned int *)((unsigned long)context_ptr+0x00000d68+4*5))=0xab7f7f52;
*((unsigned int *)((unsigned long)context_ptr+0x00000d68+4*6))=0x57389c33;
*((unsigned int *)((unsigned long)context_ptr+0x00000d68+4*7))=0x09d1e6f6;
*((unsigned int *)((unsigned long)context_ptr+0x00000d68+4*8))=0xd7c84125;
*((unsigned int *)((unsigned long)context_ptr+0x00000d68+4*9))=0x10ceb795;
*((unsigned int *)((unsigned long)context_ptr+0x00000d68+4*10))=0x65870000;
*((unsigned int *)((unsigned long)context_ptr+0x00000d68+4*11))=0x51000000;
*((unsigned int *)((unsigned long)context_ptr+0x00000d68+4*12))=0x51000000;
*((unsigned int *)((unsigned long)context_ptr+0x00000d68+4*13))=0x78560000;
*((unsigned int *)((unsigned long)context_ptr+0x00000d68+4*14))=0x32cc9ed2;
*((unsigned int *)((unsigned long)context_ptr+0x00000d68+4*15))=0xba38ff99;
*((unsigned int *)((unsigned long)context_ptr+0x00000d68+4*16))=0x61c695a6;
*((unsigned int *)((unsigned long)context_ptr+0x00000d68+4*17))=0x343221a5;
*((unsigned int *)((unsigned long)context_ptr+0x00000d68+4*18))=0x4345cc65;
*((unsigned int *)((unsigned long)context_ptr+0x00000d68+4*19))=0x558d6b28;
*((unsigned int *)((unsigned long)context_ptr+0x00000618))=0x04c0003c;
*((unsigned int *)((unsigned long)context_ptr+0x00000618+4*1))=0x00000db8;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000018))=0x09c00050;
*((unsigned int *)((unsigned long)context_ptr+0x00000018+4*1))=0x00000d68;
*((unsigned int *)((unsigned long)context_ptr+0x00000018+4*2))=0x00000d44;
*((unsigned int *)((unsigned long)context_ptr+0x00000018+4*3))=0x01e20050;
*((unsigned int *)((unsigned long)context_ptr+0x00000018+4*4))=0x001a32e1;
*((unsigned int *)((unsigned long)context_ptr+0x00000018+4*5))=0x00000c00+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x00000df4))=0x61000000;
*((unsigned int *)((unsigned long)context_ptr+0x00000df4+4*1))=0x01000008;
*((unsigned int *)((unsigned long)context_ptr+0x00000df4+4*2))=0x42900008;
*((unsigned int *)((unsigned long)context_ptr+0x00000df4+4*3))=0x42a80008;
*((unsigned int *)((unsigned long)context_ptr+0x00000df4+4*4))=0x0f020010;
*((unsigned int *)((unsigned long)context_ptr+0x00000df4+4*5))=0x40e6000c;
*((unsigned int *)((unsigned long)context_ptr+0x00000df4+4*6))=0xae3dfffe;
*((unsigned int *)((unsigned long)context_ptr+0x00000df4+4*7))=0xdd07000c;
*((unsigned int *)((unsigned long)context_ptr+0x00000df4+4*8))=0xe52e1811;
*((unsigned int *)((unsigned long)context_ptr+0x00000e18))=0x40000045;
*((unsigned int *)((unsigned long)context_ptr+0x00000e18+4*1))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x00000e18+4*2))=0x32323280;
*((unsigned int *)((unsigned long)context_ptr+0x00000e18+4*3))=0x71e92186;
*((unsigned int *)((unsigned long)context_ptr+0x00000e18+4*4))=0x63ce63ca;
*((unsigned int *)((unsigned long)context_ptr+0x00000e18+4*5))=0x21430000;
*((unsigned int *)((unsigned long)context_ptr+0x00000e18+4*6))=0x82000000;
*((unsigned int *)((unsigned long)context_ptr+0x00000e18+4*7))=0x82000000;
*((unsigned int *)((unsigned long)context_ptr+0x00000e18+4*8))=0x34120000;
*((unsigned int *)((unsigned long)context_ptr+0x00000e18+4*9))=0x2bf6730d;
*((unsigned int *)((unsigned long)context_ptr+0x00000e18+4*10))=0x4425fe7e;
*((unsigned int *)((unsigned long)context_ptr+0x00000e18+4*11))=0xd4f7896a;
*((unsigned int *)((unsigned long)context_ptr+0x00000e18+4*12))=0x313d23da;
*((unsigned int *)((unsigned long)context_ptr+0x00000e18+4*13))=0xb28e45c4;
*((unsigned int *)((unsigned long)context_ptr+0x00000e18+4*14))=0xa472d851;
*((unsigned int *)((unsigned long)context_ptr+0x00000e18+4*15))=0x6cca64e1;
*((unsigned int *)((unsigned long)context_ptr+0x00000630))=0x04c0002c;
*((unsigned int *)((unsigned long)context_ptr+0x00000630+4*1))=0x00000e58;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000030))=0x09c00040;
*((unsigned int *)((unsigned long)context_ptr+0x00000030+4*1))=0x00000e18;
*((unsigned int *)((unsigned long)context_ptr+0x00000030+4*2))=0x00000df4;
*((unsigned int *)((unsigned long)context_ptr+0x00000030+4*3))=0x01e20040;
*((unsigned int *)((unsigned long)context_ptr+0x00000030+4*4))=0x0020ca35;
*((unsigned int *)((unsigned long)context_ptr+0x00000030+4*5))=0x00000c5c+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x00000e84))=0x81000000;
*((unsigned int *)((unsigned long)context_ptr+0x00000e84+4*1))=0x01000020;
*((unsigned int *)((unsigned long)context_ptr+0x00000e84+4*2))=0x42900008;
*((unsigned int *)((unsigned long)context_ptr+0x00000e84+4*3))=0x42a80008;
*((unsigned int *)((unsigned long)context_ptr+0x00000e84+4*4))=0x0f020010;
*((unsigned int *)((unsigned long)context_ptr+0x00000e84+4*5))=0x40e6000c;
*((unsigned int *)((unsigned long)context_ptr+0x00000e84+4*6))=0xad47fffe;
*((unsigned int *)((unsigned long)context_ptr+0x00000e84+4*7))=0xdd07000c;
*((unsigned int *)((unsigned long)context_ptr+0x00000e84+4*8))=0xe52e1811;
*((unsigned int *)((unsigned long)context_ptr+0x00000ea8))=0x00000060;
*((unsigned int *)((unsigned long)context_ptr+0x00000ea8+4*1))=0x54322c00;
*((unsigned int *)((unsigned long)context_ptr+0x00000ea8+4*2))=0x268b6032;
*((unsigned int *)((unsigned long)context_ptr+0x00000ea8+4*3))=0x6725fbfd;
*((unsigned int *)((unsigned long)context_ptr+0x00000ea8+4*4))=0xea7ee0ae;
*((unsigned int *)((unsigned long)context_ptr+0x00000ea8+4*5))=0xab7f7f52;
*((unsigned int *)((unsigned long)context_ptr+0x00000ea8+4*6))=0x57389c33;
*((unsigned int *)((unsigned long)context_ptr+0x00000ea8+4*7))=0x09d1e6f6;
*((unsigned int *)((unsigned long)context_ptr+0x00000ea8+4*8))=0xd7c84125;
*((unsigned int *)((unsigned long)context_ptr+0x00000ea8+4*9))=0x10ceb795;
*((unsigned int *)((unsigned long)context_ptr+0x00000ea8+4*10))=0x65870000;
*((unsigned int *)((unsigned long)context_ptr+0x00000ea8+4*11))=0x52000000;
*((unsigned int *)((unsigned long)context_ptr+0x00000ea8+4*12))=0x52000000;
*((unsigned int *)((unsigned long)context_ptr+0x00000ea8+4*13))=0x78560000;
*((unsigned int *)((unsigned long)context_ptr+0x00000ea8+4*14))=0x0954f664;
*((unsigned int *)((unsigned long)context_ptr+0x00000ea8+4*15))=0x6bcc5458;
*((unsigned int *)((unsigned long)context_ptr+0x00000ea8+4*16))=0xaae652a4;
*((unsigned int *)((unsigned long)context_ptr+0x00000ea8+4*17))=0xa269edf9;
*((unsigned int *)((unsigned long)context_ptr+0x00000ea8+4*18))=0x820941dd;
*((unsigned int *)((unsigned long)context_ptr+0x00000ea8+4*19))=0x88e01c3b;
*((unsigned int *)((unsigned long)context_ptr+0x00000ea8+4*20))=0xf8c64815;
*((unsigned int *)((unsigned long)context_ptr+0x00000648))=0x04c0003c;
*((unsigned int *)((unsigned long)context_ptr+0x00000648+4*1))=0x00000efc;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000048))=0x09c00054;
*((unsigned int *)((unsigned long)context_ptr+0x00000048+4*1))=0x00000ea8;
*((unsigned int *)((unsigned long)context_ptr+0x00000048+4*2))=0x00000e84;
*((unsigned int *)((unsigned long)context_ptr+0x00000048+4*3))=0x01e20054;
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
if(!memcmp((unsigned char *)context_ptr+0x00000d18,"\x45\x00\x00\x00\x00\x00\x00\x00\x80\x00\x32\xa4\x86\x21\xe9\x71\xca\x63\xce\x63\xd6\x65\xc7\xcb\xe8\x33\x56\xc4\x47\x8d\x00\xf5\x00\x1e\x00\x00\x00\xf5\x00\x00\x31\x91\x00\x00",44))
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
if(!memcmp((unsigned char *)context_ptr+0x00000db8,"\x60\x00\x00\x00\x00\x00\x00\x54\x32\x60\x8b\x26\xfd\xfb\x25\x67\xae\xe0\x7e\xea\x52\x7f\x7f\xab\x33\x9c\x38\x57\xf6\xe6\xd1\x09\x25\x41\xc8\xd7\x95\xb7\xce\x10\x7a\xa0\x5d\x83\xf2\xe9\xa2\xb7\x24\x9b\x00\x92\x00\x0a\x00\x00\x92\x00\x00\x00",60))
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
if(!memcmp((unsigned char *)context_ptr+0x00000e58,"\x45\x00\x00\x00\x00\x00\x00\x00\x80\x00\x32\xa4\x86\x21\xe9\x71\xca\x63\xce\x63\x05\x3e\x23\xcd\x28\x66\x21\x1c\xfe\x38\x83\x01\x00\x1f\x00\x00\x00\x9a\x00\x00\x31\xeb\x00\x00",44))
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
if(!memcmp((unsigned char *)context_ptr+0x00000efc,"\x60\x00\x00\x00\x00\x00\x00\x54\x32\x60\x8b\x26\xfd\xfb\x25\x67\xae\xe0\x7e\xea\x52\x7f\x7f\xab\x33\x9c\x38\x57\xf6\xe6\xd1\x09\x25\x41\xc8\xd7\x95\xb7\xce\x10\xd6\x9c\x4c\xa2\x86\x7e\xf8\x4b\xc4\x86\xc4\x01\x00\x0b\x00\x00\xc0\x00\x00\x00",60))
printf("strip: 6000000000000054, Pass\n");
else
printf("strip: 6000000000000054, Failed\n");
}

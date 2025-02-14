#include <common.h>
#include <malloc.h>

extern volatile unsigned int ivp_cae_base_addr;

void test_hmac_sha1_fips(void)
{
unsigned int *context_ptr=(unsigned int *)0x14000000;
printf("test_hmac_sha1_fips\n");
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
*((unsigned int *)((unsigned long)context_ptr+0x00006000))=0x016a0a02;
*((unsigned int *)((unsigned long)context_ptr+0x00006000+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006000+4*2))=0x2a664c06;
*((unsigned int *)((unsigned long)context_ptr+0x00006000+4*3))=0xb0d16ecc;
*((unsigned int *)((unsigned long)context_ptr+0x00006000+4*4))=0xb09afa6c;
*((unsigned int *)((unsigned long)context_ptr+0x00006000+4*5))=0x7f132f04;
*((unsigned int *)((unsigned long)context_ptr+0x00006000+4*6))=0xeb70a5ce;
*((unsigned int *)((unsigned long)context_ptr+0x00006000+4*7))=0xcccc2ad6;
*((unsigned int *)((unsigned long)context_ptr+0x00006000+4*8))=0xb3986a7e;
*((unsigned int *)((unsigned long)context_ptr+0x00006000+4*9))=0x025b01df;
*((unsigned int *)((unsigned long)context_ptr+0x00006000+4*10))=0xe0c385d8;
*((unsigned int *)((unsigned long)context_ptr+0x00006000+4*11))=0xcb84d19b;
*((unsigned int *)((unsigned long)context_ptr+0x00006030))=0x016a0a02;
*((unsigned int *)((unsigned long)context_ptr+0x00006030+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006030+4*2))=0xa78e4d62;
*((unsigned int *)((unsigned long)context_ptr+0x00006030+4*3))=0x03182b3f;
*((unsigned int *)((unsigned long)context_ptr+0x00006030+4*4))=0xe4b95495;
*((unsigned int *)((unsigned long)context_ptr+0x00006030+4*5))=0xf565c028;
*((unsigned int *)((unsigned long)context_ptr+0x00006030+4*6))=0x8eb9fca9;
*((unsigned int *)((unsigned long)context_ptr+0x00006030+4*7))=0x2a378820;
*((unsigned int *)((unsigned long)context_ptr+0x00006030+4*8))=0xa11006f5;
*((unsigned int *)((unsigned long)context_ptr+0x00006030+4*9))=0x058b2ff8;
*((unsigned int *)((unsigned long)context_ptr+0x00006030+4*10))=0x32fe4b8e;
*((unsigned int *)((unsigned long)context_ptr+0x00006030+4*11))=0x354e0b28;
*((unsigned int *)((unsigned long)context_ptr+0x00006060))=0x016a0a02;
*((unsigned int *)((unsigned long)context_ptr+0x00006060+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006060+4*2))=0x7f81a2f8;
*((unsigned int *)((unsigned long)context_ptr+0x00006060+4*3))=0xa65a78b5;
*((unsigned int *)((unsigned long)context_ptr+0x00006060+4*4))=0x287415d5;
*((unsigned int *)((unsigned long)context_ptr+0x00006060+4*5))=0xed914e53;
*((unsigned int *)((unsigned long)context_ptr+0x00006060+4*6))=0x76646201;
*((unsigned int *)((unsigned long)context_ptr+0x00006060+4*7))=0x5212998f;
*((unsigned int *)((unsigned long)context_ptr+0x00006060+4*8))=0x5a17602c;
*((unsigned int *)((unsigned long)context_ptr+0x00006060+4*9))=0x15087fcd;
*((unsigned int *)((unsigned long)context_ptr+0x00006060+4*10))=0x5ddc078a;
*((unsigned int *)((unsigned long)context_ptr+0x00006060+4*11))=0xe53de0c7;
*((unsigned int *)((unsigned long)context_ptr+0x00006090))=0x016a0a02;
*((unsigned int *)((unsigned long)context_ptr+0x00006090+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006090+4*2))=0x0db8cc49;
*((unsigned int *)((unsigned long)context_ptr+0x00006090+4*3))=0x34e7cb82;
*((unsigned int *)((unsigned long)context_ptr+0x00006090+4*4))=0x1b156a09;
*((unsigned int *)((unsigned long)context_ptr+0x00006090+4*5))=0x40f59210;
*((unsigned int *)((unsigned long)context_ptr+0x00006090+4*6))=0x69e0ca5d;
*((unsigned int *)((unsigned long)context_ptr+0x00006090+4*7))=0x949058eb;
*((unsigned int *)((unsigned long)context_ptr+0x00006090+4*8))=0x07c3837b;
*((unsigned int *)((unsigned long)context_ptr+0x00006090+4*9))=0x13d49816;
*((unsigned int *)((unsigned long)context_ptr+0x00006090+4*10))=0x8364acb7;
*((unsigned int *)((unsigned long)context_ptr+0x00006090+4*11))=0xe1248c03;
*((unsigned int *)((unsigned long)context_ptr+0x000060c0))=0x016a0a02;
*((unsigned int *)((unsigned long)context_ptr+0x000060c0+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000060c0+4*2))=0x0e480f18;
*((unsigned int *)((unsigned long)context_ptr+0x000060c0+4*3))=0xd068bdbb;
*((unsigned int *)((unsigned long)context_ptr+0x000060c0+4*4))=0x1f42fe2d;
*((unsigned int *)((unsigned long)context_ptr+0x000060c0+4*5))=0x948feac1;
*((unsigned int *)((unsigned long)context_ptr+0x000060c0+4*6))=0xf8bffe84;
*((unsigned int *)((unsigned long)context_ptr+0x000060c0+4*7))=0x79ea70a6;
*((unsigned int *)((unsigned long)context_ptr+0x000060c0+4*8))=0x96f88029;
*((unsigned int *)((unsigned long)context_ptr+0x000060c0+4*9))=0xd35ee394;
*((unsigned int *)((unsigned long)context_ptr+0x000060c0+4*10))=0xf25a096d;
*((unsigned int *)((unsigned long)context_ptr+0x000060c0+4*11))=0x2c0ffbd4;
*((unsigned int *)((unsigned long)context_ptr+0x000060f0))=0x016a0a02;
*((unsigned int *)((unsigned long)context_ptr+0x000060f0+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000060f0+4*2))=0xe6cd4629;
*((unsigned int *)((unsigned long)context_ptr+0x000060f0+4*3))=0x6cb5b18e;
*((unsigned int *)((unsigned long)context_ptr+0x000060f0+4*4))=0x325a986a;
*((unsigned int *)((unsigned long)context_ptr+0x000060f0+4*5))=0x1a74212c;
*((unsigned int *)((unsigned long)context_ptr+0x000060f0+4*6))=0xc3884743;
*((unsigned int *)((unsigned long)context_ptr+0x000060f0+4*7))=0x9e07fd6f;
*((unsigned int *)((unsigned long)context_ptr+0x000060f0+4*8))=0x4c38886f;
*((unsigned int *)((unsigned long)context_ptr+0x000060f0+4*9))=0x45f1121d;
*((unsigned int *)((unsigned long)context_ptr+0x000060f0+4*10))=0x9c8fd907;
*((unsigned int *)((unsigned long)context_ptr+0x000060f0+4*11))=0xe69d5275;
*((unsigned int *)((unsigned long)context_ptr+0x00006120))=0x016a0a02;
*((unsigned int *)((unsigned long)context_ptr+0x00006120+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006120+4*2))=0xe6cd4629;
*((unsigned int *)((unsigned long)context_ptr+0x00006120+4*3))=0x6cb5b18e;
*((unsigned int *)((unsigned long)context_ptr+0x00006120+4*4))=0x325a986a;
*((unsigned int *)((unsigned long)context_ptr+0x00006120+4*5))=0x1a74212c;
*((unsigned int *)((unsigned long)context_ptr+0x00006120+4*6))=0xc3884743;
*((unsigned int *)((unsigned long)context_ptr+0x00006120+4*7))=0x9e07fd6f;
*((unsigned int *)((unsigned long)context_ptr+0x00006120+4*8))=0x4c38886f;
*((unsigned int *)((unsigned long)context_ptr+0x00006120+4*9))=0x45f1121d;
*((unsigned int *)((unsigned long)context_ptr+0x00006120+4*10))=0x9c8fd907;
*((unsigned int *)((unsigned long)context_ptr+0x00006120+4*11))=0xe69d5275;
*((unsigned int *)((unsigned long)context_ptr+0x00006150))=0x016a0a02;
*((unsigned int *)((unsigned long)context_ptr+0x00006150+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006150+4*2))=0x36e3462f;
*((unsigned int *)((unsigned long)context_ptr+0x00006150+4*3))=0x298db062;
*((unsigned int *)((unsigned long)context_ptr+0x00006150+4*4))=0xc5469ef8;
*((unsigned int *)((unsigned long)context_ptr+0x00006150+4*5))=0xd81dbc27;
*((unsigned int *)((unsigned long)context_ptr+0x00006150+4*6))=0x314e9c4b;
*((unsigned int *)((unsigned long)context_ptr+0x00006150+4*7))=0x8e25a8da;
*((unsigned int *)((unsigned long)context_ptr+0x00006150+4*8))=0x93fd1351;
*((unsigned int *)((unsigned long)context_ptr+0x00006150+4*9))=0xbb3a946a;
*((unsigned int *)((unsigned long)context_ptr+0x00006150+4*10))=0x4e54235c;
*((unsigned int *)((unsigned long)context_ptr+0x00006150+4*11))=0xd4b02150;
*((unsigned int *)((unsigned long)context_ptr+0x00006180))=0x016a0a02;
*((unsigned int *)((unsigned long)context_ptr+0x00006180+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006180+4*2))=0xa4d5d48c;
*((unsigned int *)((unsigned long)context_ptr+0x00006180+4*3))=0x0c95c41a;
*((unsigned int *)((unsigned long)context_ptr+0x00006180+4*4))=0xd6bc5f01;
*((unsigned int *)((unsigned long)context_ptr+0x00006180+4*5))=0x2871330f;
*((unsigned int *)((unsigned long)context_ptr+0x00006180+4*6))=0x36d00d39;
*((unsigned int *)((unsigned long)context_ptr+0x00006180+4*7))=0x1b502c9b;
*((unsigned int *)((unsigned long)context_ptr+0x00006180+4*8))=0xc12d2653;
*((unsigned int *)((unsigned long)context_ptr+0x00006180+4*9))=0x4841061a;
*((unsigned int *)((unsigned long)context_ptr+0x00006180+4*10))=0x2e425944;
*((unsigned int *)((unsigned long)context_ptr+0x00006180+4*11))=0x2e68b285;
*((unsigned int *)((unsigned long)context_ptr+0x000061b0))=0x016a0a02;
*((unsigned int *)((unsigned long)context_ptr+0x000061b0+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000061b0+4*2))=0x6f1b2aa2;
*((unsigned int *)((unsigned long)context_ptr+0x000061b0+4*3))=0x136f5cec;
*((unsigned int *)((unsigned long)context_ptr+0x000061b0+4*4))=0x3328de1f;
*((unsigned int *)((unsigned long)context_ptr+0x000061b0+4*5))=0xf9b1d47d;
*((unsigned int *)((unsigned long)context_ptr+0x000061b0+4*6))=0x8ad8ff75;
*((unsigned int *)((unsigned long)context_ptr+0x000061b0+4*7))=0x174affe5;
*((unsigned int *)((unsigned long)context_ptr+0x000061b0+4*8))=0x4a2fd4c9;
*((unsigned int *)((unsigned long)context_ptr+0x000061b0+4*9))=0xab003312;
*((unsigned int *)((unsigned long)context_ptr+0x000061b0+4*10))=0xa0081343;
*((unsigned int *)((unsigned long)context_ptr+0x000061b0+4*11))=0xd0bb5538;
*((unsigned int *)((unsigned long)context_ptr+0x000061e0))=0x016a0a02;
*((unsigned int *)((unsigned long)context_ptr+0x000061e0+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000061e0+4*2))=0x6148fa2a;
*((unsigned int *)((unsigned long)context_ptr+0x000061e0+4*3))=0xf6247c8a;
*((unsigned int *)((unsigned long)context_ptr+0x000061e0+4*4))=0xc0db3703;
*((unsigned int *)((unsigned long)context_ptr+0x000061e0+4*5))=0x3cc6b367;
*((unsigned int *)((unsigned long)context_ptr+0x000061e0+4*6))=0x6abd8bd9;
*((unsigned int *)((unsigned long)context_ptr+0x000061e0+4*7))=0x4082a77e;
*((unsigned int *)((unsigned long)context_ptr+0x000061e0+4*8))=0x925948a6;
*((unsigned int *)((unsigned long)context_ptr+0x000061e0+4*9))=0x18ba91f8;
*((unsigned int *)((unsigned long)context_ptr+0x000061e0+4*10))=0xfe1bac74;
*((unsigned int *)((unsigned long)context_ptr+0x000061e0+4*11))=0xc8c2a7f5;
*((unsigned int *)((unsigned long)context_ptr+0x00006210))=0x016a0a02;
*((unsigned int *)((unsigned long)context_ptr+0x00006210+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006210+4*2))=0x02020008;
*((unsigned int *)((unsigned long)context_ptr+0x00006210+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x00006220))=0x54206948;
*((unsigned int *)((unsigned long)context_ptr+0x00006220+4*1))=0x65726568;
*((unsigned int *)((unsigned long)context_ptr+0x00003000))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003000+4*1))=0x00006228;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000000))=0x04c00008;
*((unsigned int *)((unsigned long)context_ptr+0x00000000+4*1))=0x00006220;
*((unsigned int *)((unsigned long)context_ptr+0x00000000+4*2))=0x00006210;
*((unsigned int *)((unsigned long)context_ptr+0x00000000+4*3))=0x02220008;
*((unsigned int *)((unsigned long)context_ptr+0x00000000+4*4))=0x0fdf3aec;
*((unsigned int *)((unsigned long)context_ptr+0x00000000+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x0000623c))=0x016a0a02;
*((unsigned int *)((unsigned long)context_ptr+0x0000623c+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x0000623c+4*2))=0x0202001c;
*((unsigned int *)((unsigned long)context_ptr+0x0000623c+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x0000624c))=0x74616877;
*((unsigned int *)((unsigned long)context_ptr+0x0000624c+4*1))=0x206f6420;
*((unsigned int *)((unsigned long)context_ptr+0x0000624c+4*2))=0x77206179;
*((unsigned int *)((unsigned long)context_ptr+0x0000624c+4*3))=0x20746e61;
*((unsigned int *)((unsigned long)context_ptr+0x0000624c+4*4))=0x20726f66;
*((unsigned int *)((unsigned long)context_ptr+0x0000624c+4*5))=0x68746f6e;
*((unsigned int *)((unsigned long)context_ptr+0x0000624c+4*6))=0x3f676e69;
*((unsigned int *)((unsigned long)context_ptr+0x00003018))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003018+4*1))=0x00006268;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000018))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00000018+4*1))=0x0000624c;
*((unsigned int *)((unsigned long)context_ptr+0x00000018+4*2))=0x0000623c;
*((unsigned int *)((unsigned long)context_ptr+0x00000018+4*3))=0x0222001c;
*((unsigned int *)((unsigned long)context_ptr+0x00000018+4*4))=0x0a5dc21c;
*((unsigned int *)((unsigned long)context_ptr+0x00000018+4*5))=0x00006030+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x0000627c))=0x016a0a02;
*((unsigned int *)((unsigned long)context_ptr+0x0000627c+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x0000627c+4*2))=0x02020032;
*((unsigned int *)((unsigned long)context_ptr+0x0000627c+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x0000628c))=0xdddddddd;
*((unsigned int *)((unsigned long)context_ptr+0x0000628c+4*1))=0xdddddddd;
*((unsigned int *)((unsigned long)context_ptr+0x0000628c+4*2))=0xdddddddd;
*((unsigned int *)((unsigned long)context_ptr+0x0000628c+4*3))=0xdddddddd;
*((unsigned int *)((unsigned long)context_ptr+0x0000628c+4*4))=0xdddddddd;
*((unsigned int *)((unsigned long)context_ptr+0x0000628c+4*5))=0xdddddddd;
*((unsigned int *)((unsigned long)context_ptr+0x0000628c+4*6))=0xdddddddd;
*((unsigned int *)((unsigned long)context_ptr+0x0000628c+4*7))=0xdddddddd;
*((unsigned int *)((unsigned long)context_ptr+0x0000628c+4*8))=0xdddddddd;
*((unsigned int *)((unsigned long)context_ptr+0x0000628c+4*9))=0xdddddddd;
*((unsigned int *)((unsigned long)context_ptr+0x0000628c+4*10))=0xdddddddd;
*((unsigned int *)((unsigned long)context_ptr+0x0000628c+4*11))=0xdddddddd;
*((unsigned int *)((unsigned long)context_ptr+0x0000628c+4*12))=0x0000dddd;
*((unsigned int *)((unsigned long)context_ptr+0x00003030))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003030+4*1))=0x000062c0;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000030))=0x04c00032;
*((unsigned int *)((unsigned long)context_ptr+0x00000030+4*1))=0x0000628c;
*((unsigned int *)((unsigned long)context_ptr+0x00000030+4*2))=0x0000627c;
*((unsigned int *)((unsigned long)context_ptr+0x00000030+4*3))=0x02220032;
*((unsigned int *)((unsigned long)context_ptr+0x00000030+4*4))=0x05477afd;
*((unsigned int *)((unsigned long)context_ptr+0x00000030+4*5))=0x00006060+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x000062d4))=0x016a0a02;
*((unsigned int *)((unsigned long)context_ptr+0x000062d4+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000062d4+4*2))=0x02020032;
*((unsigned int *)((unsigned long)context_ptr+0x000062d4+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x000062e4))=0xcdcdcdcd;
*((unsigned int *)((unsigned long)context_ptr+0x000062e4+4*1))=0xcdcdcdcd;
*((unsigned int *)((unsigned long)context_ptr+0x000062e4+4*2))=0xcdcdcdcd;
*((unsigned int *)((unsigned long)context_ptr+0x000062e4+4*3))=0xcdcdcdcd;
*((unsigned int *)((unsigned long)context_ptr+0x000062e4+4*4))=0xcdcdcdcd;
*((unsigned int *)((unsigned long)context_ptr+0x000062e4+4*5))=0xcdcdcdcd;
*((unsigned int *)((unsigned long)context_ptr+0x000062e4+4*6))=0xcdcdcdcd;
*((unsigned int *)((unsigned long)context_ptr+0x000062e4+4*7))=0xcdcdcdcd;
*((unsigned int *)((unsigned long)context_ptr+0x000062e4+4*8))=0xcdcdcdcd;
*((unsigned int *)((unsigned long)context_ptr+0x000062e4+4*9))=0xcdcdcdcd;
*((unsigned int *)((unsigned long)context_ptr+0x000062e4+4*10))=0xcdcdcdcd;
*((unsigned int *)((unsigned long)context_ptr+0x000062e4+4*11))=0xcdcdcdcd;
*((unsigned int *)((unsigned long)context_ptr+0x000062e4+4*12))=0x0000cdcd;
*((unsigned int *)((unsigned long)context_ptr+0x00003048))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003048+4*1))=0x00006318;
*((unsigned int *)((unsigned long)context_ptr+0x00003048+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003048+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003048+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003048+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000048))=0x04c00032;
*((unsigned int *)((unsigned long)context_ptr+0x00000048+4*1))=0x000062e4;
*((unsigned int *)((unsigned long)context_ptr+0x00000048+4*2))=0x000062d4;
*((unsigned int *)((unsigned long)context_ptr+0x00000048+4*3))=0x02220032;
*((unsigned int *)((unsigned long)context_ptr+0x00000048+4*4))=0x09e81d11;
*((unsigned int *)((unsigned long)context_ptr+0x00000048+4*5))=0x00006090+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x0000632c))=0x016a0a02;
*((unsigned int *)((unsigned long)context_ptr+0x0000632c+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x0000632c+4*2))=0x02020014;
*((unsigned int *)((unsigned long)context_ptr+0x0000632c+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x0000633c))=0x74736554;
*((unsigned int *)((unsigned long)context_ptr+0x0000633c+4*1))=0x74695720;
*((unsigned int *)((unsigned long)context_ptr+0x0000633c+4*2))=0x72542068;
*((unsigned int *)((unsigned long)context_ptr+0x0000633c+4*3))=0x61636e75;
*((unsigned int *)((unsigned long)context_ptr+0x0000633c+4*4))=0x6e6f6974;
*((unsigned int *)((unsigned long)context_ptr+0x00003060))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003060+4*1))=0x00006350;
*((unsigned int *)((unsigned long)context_ptr+0x00003060+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003060+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003060+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003060+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000060))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00000060+4*1))=0x0000633c;
*((unsigned int *)((unsigned long)context_ptr+0x00000060+4*2))=0x0000632c;
*((unsigned int *)((unsigned long)context_ptr+0x00000060+4*3))=0x02220014;
*((unsigned int *)((unsigned long)context_ptr+0x00000060+4*4))=0x088f1559;
*((unsigned int *)((unsigned long)context_ptr+0x00000060+4*5))=0x000060c0+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x00006364))=0x016a0a02;
*((unsigned int *)((unsigned long)context_ptr+0x00006364+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006364+4*2))=0x02020036;
*((unsigned int *)((unsigned long)context_ptr+0x00006364+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x00006374))=0x74736554;
*((unsigned int *)((unsigned long)context_ptr+0x00006374+4*1))=0x69735520;
*((unsigned int *)((unsigned long)context_ptr+0x00006374+4*2))=0x4c20676e;
*((unsigned int *)((unsigned long)context_ptr+0x00006374+4*3))=0x65677261;
*((unsigned int *)((unsigned long)context_ptr+0x00006374+4*4))=0x68542072;
*((unsigned int *)((unsigned long)context_ptr+0x00006374+4*5))=0x42206e61;
*((unsigned int *)((unsigned long)context_ptr+0x00006374+4*6))=0x6b636f6c;
*((unsigned int *)((unsigned long)context_ptr+0x00006374+4*7))=0x7a69532d;
*((unsigned int *)((unsigned long)context_ptr+0x00006374+4*8))=0x654b2065;
*((unsigned int *)((unsigned long)context_ptr+0x00006374+4*9))=0x202d2079;
*((unsigned int *)((unsigned long)context_ptr+0x00006374+4*10))=0x68736148;
*((unsigned int *)((unsigned long)context_ptr+0x00006374+4*11))=0x79654b20;
*((unsigned int *)((unsigned long)context_ptr+0x00006374+4*12))=0x72694620;
*((unsigned int *)((unsigned long)context_ptr+0x00006374+4*13))=0x00007473;
*((unsigned int *)((unsigned long)context_ptr+0x00003078))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003078+4*1))=0x000063ac;
*((unsigned int *)((unsigned long)context_ptr+0x00003078+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003078+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003078+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003078+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000078))=0x04c00036;
*((unsigned int *)((unsigned long)context_ptr+0x00000078+4*1))=0x00006374;
*((unsigned int *)((unsigned long)context_ptr+0x00000078+4*2))=0x00006364;
*((unsigned int *)((unsigned long)context_ptr+0x00000078+4*3))=0x02220036;
*((unsigned int *)((unsigned long)context_ptr+0x00000078+4*4))=0x05bb955e;
*((unsigned int *)((unsigned long)context_ptr+0x00000078+4*5))=0x000060f0+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x000063c0))=0x016a0a02;
*((unsigned int *)((unsigned long)context_ptr+0x000063c0+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000063c0+4*2))=0x02020049;
*((unsigned int *)((unsigned long)context_ptr+0x000063c0+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x000063d0))=0x74736554;
*((unsigned int *)((unsigned long)context_ptr+0x000063d0+4*1))=0x69735520;
*((unsigned int *)((unsigned long)context_ptr+0x000063d0+4*2))=0x4c20676e;
*((unsigned int *)((unsigned long)context_ptr+0x000063d0+4*3))=0x65677261;
*((unsigned int *)((unsigned long)context_ptr+0x000063d0+4*4))=0x68542072;
*((unsigned int *)((unsigned long)context_ptr+0x000063d0+4*5))=0x42206e61;
*((unsigned int *)((unsigned long)context_ptr+0x000063d0+4*6))=0x6b636f6c;
*((unsigned int *)((unsigned long)context_ptr+0x000063d0+4*7))=0x7a69532d;
*((unsigned int *)((unsigned long)context_ptr+0x000063d0+4*8))=0x654b2065;
*((unsigned int *)((unsigned long)context_ptr+0x000063d0+4*9))=0x6e612079;
*((unsigned int *)((unsigned long)context_ptr+0x000063d0+4*10))=0x614c2064;
*((unsigned int *)((unsigned long)context_ptr+0x000063d0+4*11))=0x72656772;
*((unsigned int *)((unsigned long)context_ptr+0x000063d0+4*12))=0x61685420;
*((unsigned int *)((unsigned long)context_ptr+0x000063d0+4*13))=0x6e4f206e;
*((unsigned int *)((unsigned long)context_ptr+0x000063d0+4*14))=0x6c422065;
*((unsigned int *)((unsigned long)context_ptr+0x000063d0+4*15))=0x2d6b636f;
*((unsigned int *)((unsigned long)context_ptr+0x000063d0+4*16))=0x657a6953;
*((unsigned int *)((unsigned long)context_ptr+0x000063d0+4*17))=0x74614420;
*((unsigned int *)((unsigned long)context_ptr+0x000063d0+4*18))=0x00000061;
*((unsigned int *)((unsigned long)context_ptr+0x00003090))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003090+4*1))=0x0000641c;
*((unsigned int *)((unsigned long)context_ptr+0x00003090+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003090+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003090+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003090+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000090))=0x04c00049;
*((unsigned int *)((unsigned long)context_ptr+0x00000090+4*1))=0x000063d0;
*((unsigned int *)((unsigned long)context_ptr+0x00000090+4*2))=0x000063c0;
*((unsigned int *)((unsigned long)context_ptr+0x00000090+4*3))=0x02220049;
*((unsigned int *)((unsigned long)context_ptr+0x00000090+4*4))=0x0bde8228;
*((unsigned int *)((unsigned long)context_ptr+0x00000090+4*5))=0x00006120+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x00006430))=0x016a0a02;
*((unsigned int *)((unsigned long)context_ptr+0x00006430+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006430+4*2))=0x02020009;
*((unsigned int *)((unsigned long)context_ptr+0x00006430+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x00006440))=0x706d6153;
*((unsigned int *)((unsigned long)context_ptr+0x00006440+4*1))=0x2320656c;
*((unsigned int *)((unsigned long)context_ptr+0x00006440+4*2))=0x00000031;
*((unsigned int *)((unsigned long)context_ptr+0x000030a8))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x000030a8+4*1))=0x0000644c;
*((unsigned int *)((unsigned long)context_ptr+0x000030a8+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000030a8+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000030a8+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000030a8+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x000000a8))=0x04c00009;
*((unsigned int *)((unsigned long)context_ptr+0x000000a8+4*1))=0x00006440;
*((unsigned int *)((unsigned long)context_ptr+0x000000a8+4*2))=0x00006430;
*((unsigned int *)((unsigned long)context_ptr+0x000000a8+4*3))=0x02220009;
*((unsigned int *)((unsigned long)context_ptr+0x000000a8+4*4))=0x0e19dad4;
*((unsigned int *)((unsigned long)context_ptr+0x000000a8+4*5))=0x00006150+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x00006460))=0x016a0a02;
*((unsigned int *)((unsigned long)context_ptr+0x00006460+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006460+4*2))=0x02020009;
*((unsigned int *)((unsigned long)context_ptr+0x00006460+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x00006470))=0x706d6153;
*((unsigned int *)((unsigned long)context_ptr+0x00006470+4*1))=0x2320656c;
*((unsigned int *)((unsigned long)context_ptr+0x00006470+4*2))=0x00000032;
*((unsigned int *)((unsigned long)context_ptr+0x000030c0))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x000030c0+4*1))=0x0000647c;
*((unsigned int *)((unsigned long)context_ptr+0x000030c0+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000030c0+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000030c0+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000030c0+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x000000c0))=0x04c00009;
*((unsigned int *)((unsigned long)context_ptr+0x000000c0+4*1))=0x00006470;
*((unsigned int *)((unsigned long)context_ptr+0x000000c0+4*2))=0x00006460;
*((unsigned int *)((unsigned long)context_ptr+0x000000c0+4*3))=0x02220009;
*((unsigned int *)((unsigned long)context_ptr+0x000000c0+4*4))=0x04ee6436;
*((unsigned int *)((unsigned long)context_ptr+0x000000c0+4*5))=0x00006180+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x00006490))=0x016a0a02;
*((unsigned int *)((unsigned long)context_ptr+0x00006490+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006490+4*2))=0x02020009;
*((unsigned int *)((unsigned long)context_ptr+0x00006490+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x000064a0))=0x706d6153;
*((unsigned int *)((unsigned long)context_ptr+0x000064a0+4*1))=0x2320656c;
*((unsigned int *)((unsigned long)context_ptr+0x000064a0+4*2))=0x00000033;
*((unsigned int *)((unsigned long)context_ptr+0x000030d8))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x000030d8+4*1))=0x000064ac;
*((unsigned int *)((unsigned long)context_ptr+0x000030d8+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000030d8+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000030d8+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000030d8+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x000000d8))=0x04c00009;
*((unsigned int *)((unsigned long)context_ptr+0x000000d8+4*1))=0x000064a0;
*((unsigned int *)((unsigned long)context_ptr+0x000000d8+4*2))=0x00006490;
*((unsigned int *)((unsigned long)context_ptr+0x000000d8+4*3))=0x02220009;
*((unsigned int *)((unsigned long)context_ptr+0x000000d8+4*4))=0x0c48417f;
*((unsigned int *)((unsigned long)context_ptr+0x000000d8+4*5))=0x000061b0+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x000064c0))=0x016a0a02;
*((unsigned int *)((unsigned long)context_ptr+0x000064c0+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000064c0+4*2))=0x02020009;
*((unsigned int *)((unsigned long)context_ptr+0x000064c0+4*3))=0x21e6000c;
*((unsigned int *)((unsigned long)context_ptr+0x000064d0))=0x706d6153;
*((unsigned int *)((unsigned long)context_ptr+0x000064d0+4*1))=0x2320656c;
*((unsigned int *)((unsigned long)context_ptr+0x000064d0+4*2))=0x00000034;
*((unsigned int *)((unsigned long)context_ptr+0x000030f0))=0x04c0000c;
*((unsigned int *)((unsigned long)context_ptr+0x000030f0+4*1))=0x000064dc;
*((unsigned int *)((unsigned long)context_ptr+0x000030f0+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000030f0+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000030f0+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000030f0+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x000000f0))=0x04c00009;
*((unsigned int *)((unsigned long)context_ptr+0x000000f0+4*1))=0x000064d0;
*((unsigned int *)((unsigned long)context_ptr+0x000000f0+4*2))=0x000064c0;
*((unsigned int *)((unsigned long)context_ptr+0x000000f0+4*3))=0x02220009;
*((unsigned int *)((unsigned long)context_ptr+0x000000f0+4*4))=0x035f295e;
*((unsigned int *)((unsigned long)context_ptr+0x000000f0+4*5))=0x000061e0+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000006&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006228,"\xb6\x17\x31\x86\x55\x05\x72\x64\xe2\x8b\xc0\xb6\xfb\x37\x8c\x8e\xf1\x46\xbe\x00",20))
printf("strip: b617318655057264, Pass\n");
else
printf("strip: b617318655057264, Failed\n");
writel(0x0000000c&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006268,"\xef\xfc\xdf\x6a\xe5\xeb\x2f\xa2\xd2\x74\x16\xd5\xf1\x84\xdf\x9c\x25\x9a\x7c\x79",20))
printf("strip: effcdf6ae5eb2fa2, Pass\n");
else
printf("strip: effcdf6ae5eb2fa2, Failed\n");
writel(0x00000012&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000062c0,"\x12\x5d\x73\x42\xb9\xac\x11\xcd\x91\xa3\x9a\xf4\x8a\xa1\x7b\x4f\x63\xf1\x75\xd3",20))
printf("strip: 125d7342b9ac11cd, Pass\n");
else
printf("strip: 125d7342b9ac11cd, Failed\n");
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006318,"\x4c\x90\x07\xf4\x02\x62\x50\xc6\xbc\x84\x14\xf9\xbf\x50\xc8\x6c\x2d\x72\x35\xda",20))
printf("strip: 4c9007f4026250c6, Pass\n");
else
printf("strip: 4c9007f4026250c6, Failed\n");
writel(0x0000001e&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006350,"\x4c\x1a\x03\x42\x4b\x55\xe0\x7f\xe7\xf2\x7b\xe1\xd5\x8b\xb9\x32\x4a\x9a\x5a\x04",20))
printf("strip: 4c1a03424b55e07f, Pass\n");
else
printf("strip: 4c1a03424b55e07f, Failed\n");
writel(0x00000024&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000063ac,"\xaa\x4a\xe5\xe1\x52\x72\xd0\x0e\x95\x70\x56\x37\xce\x8a\x3b\x55\xed\x40\x21\x12",20))
printf("strip: aa4ae5e15272d00e, Pass\n");
else
printf("strip: aa4ae5e15272d00e, Failed\n");
writel(0x0000002a&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x0000641c,"\xe8\xe9\x9d\x0f\x45\x23\x7d\x78\x6d\x6b\xba\xa7\x96\x5c\x78\x08\xbb\xff\x1a\x91",20))
printf("strip: e8e99d0f45237d78, Pass\n");
else
printf("strip: e8e99d0f45237d78, Failed\n");
writel(0x00000030&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x0000644c,"\x4f\x4c\xa3\xd5\xd6\x8b\xa7\xcc\x0a\x12\x08\xc9\xc6\x1e\x9c\x5d\xa0\x40\x3c\x0a",20))
printf("strip: 4f4ca3d5d68ba7cc, Pass\n");
else
printf("strip: 4f4ca3d5d68ba7cc, Failed\n");
writel(0x00000036&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x0000647c,"\x09\x22\xd3\x40\x5f\xaa\x3d\x19\x4f\x82\xa4\x58\x30\x73\x7d\x5c\xc6\xc7\x5d\x24",20))
printf("strip: 0922d3405faa3d19, Pass\n");
else
printf("strip: 0922d3405faa3d19, Failed\n");
writel(0x0000003c&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000064ac,"\xbc\xf4\x1e\xab\x8b\xb2\xd8\x02\xf3\xd0\x5c\xaf\x7c\xb0\x92\xec\xf8\xd1\xa3\xaa",20))
printf("strip: bcf41eab8bb2d802, Pass\n");
else
printf("strip: bcf41eab8bb2d802, Failed\n");
writel(0x00000042&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000064dc,"\x9e\xa8\x86\xef\xe2\x68\xdb\xec\xce\x42\x0c\x75",12))
printf("strip: 9ea886efe268dbec, Pass\n");
else
printf("strip: 9ea886efe268dbec, Failed\n");
}

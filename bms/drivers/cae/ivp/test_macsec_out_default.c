#include <common.h>
#include <malloc.h>

extern volatile unsigned int ivp_cae_base_addr;

void test_macsec_out_default(void)
{
unsigned int *context_ptr=(unsigned int *)0x14000000;
printf("test_macsec_out_default\n");
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
*((unsigned int *)((unsigned long)context_ptr+0x00000c00))=0x124b0b06;
*((unsigned int *)((unsigned long)context_ptr+0x00000c00+4*1))=0x4a020462;
*((unsigned int *)((unsigned long)context_ptr+0x00000c00+4*2))=0x268b6032;
*((unsigned int *)((unsigned long)context_ptr+0x00000c00+4*3))=0x6725fbfd;
*((unsigned int *)((unsigned long)context_ptr+0x00000c00+4*4))=0xea7ee0ae;
*((unsigned int *)((unsigned long)context_ptr+0x00000c00+4*5))=0xab7f7f52;
*((unsigned int *)((unsigned long)context_ptr+0x00000c00+4*6))=0x13b75384;
*((unsigned int *)((unsigned long)context_ptr+0x00000c00+4*7))=0xfe5a8063;
*((unsigned int *)((unsigned long)context_ptr+0x00000c00+4*8))=0x3f753964;
*((unsigned int *)((unsigned long)context_ptr+0x00000c00+4*9))=0x810879d4;
*((unsigned int *)((unsigned long)context_ptr+0x00000c00+4*10))=0x00004320;
*((unsigned int *)((unsigned long)context_ptr+0x00000c00+4*11))=0x35651ead;
*((unsigned int *)((unsigned long)context_ptr+0x00000c00+4*12))=0x2537f20a;
*((unsigned int *)((unsigned long)context_ptr+0x00000c34))=0x124b0b06;
*((unsigned int *)((unsigned long)context_ptr+0x00000c34+4*1))=0x4a020462;
*((unsigned int *)((unsigned long)context_ptr+0x00000c34+4*2))=0x0e2f153b;
*((unsigned int *)((unsigned long)context_ptr+0x00000c34+4*3))=0x9c9c2ca3;
*((unsigned int *)((unsigned long)context_ptr+0x00000c34+4*4))=0xe04883b4;
*((unsigned int *)((unsigned long)context_ptr+0x00000c34+4*5))=0x84a1755a;
*((unsigned int *)((unsigned long)context_ptr+0x00000c34+4*6))=0x62e76ae2;
*((unsigned int *)((unsigned long)context_ptr+0x00000c34+4*7))=0x0266f22b;
*((unsigned int *)((unsigned long)context_ptr+0x00000c34+4*8))=0xfb56a314;
*((unsigned int *)((unsigned long)context_ptr+0x00000c34+4*9))=0x9a7579d7;
*((unsigned int *)((unsigned long)context_ptr+0x00000c34+4*10))=0x00008764;
*((unsigned int *)((unsigned long)context_ptr+0x00000c34+4*11))=0x96f03238;
*((unsigned int *)((unsigned long)context_ptr+0x00000c34+4*12))=0x0000630c;
*((unsigned int *)((unsigned long)context_ptr+0x00000c68))=0x0300000c;
*((unsigned int *)((unsigned long)context_ptr+0x00000c68+4*1))=0x23d80004;
*((unsigned int *)((unsigned long)context_ptr+0x00000c68+4*2))=0x0c2ce588;
*((unsigned int *)((unsigned long)context_ptr+0x00000c68+4*3))=0x93996004;
*((unsigned int *)((unsigned long)context_ptr+0x00000c68+4*4))=0x9bd94008;
*((unsigned int *)((unsigned long)context_ptr+0x00000c68+4*5))=0x35651ead;
*((unsigned int *)((unsigned long)context_ptr+0x00000c68+4*6))=0x2537f20a;
*((unsigned int *)((unsigned long)context_ptr+0x00000c68+4*7))=0xa082001c;
*((unsigned int *)((unsigned long)context_ptr+0x00000c68+4*8))=0x25000010;
*((unsigned int *)((unsigned long)context_ptr+0x00000c68+4*9))=0x0f02000c;
*((unsigned int *)((unsigned long)context_ptr+0x00000c68+4*10))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x00000c68+4*11))=0xe12e180a;
*((unsigned int *)((unsigned long)context_ptr+0x00000c98))=0x4fbcac33;
*((unsigned int *)((unsigned long)context_ptr+0x00000c98+4*1))=0xb65841dc;
*((unsigned int *)((unsigned long)context_ptr+0x00000c98+4*2))=0x7512ef0b;
*((unsigned int *)((unsigned long)context_ptr+0x00000c98+4*3))=0x0cb970eb;
*((unsigned int *)((unsigned long)context_ptr+0x00000c98+4*4))=0x1e75facf;
*((unsigned int *)((unsigned long)context_ptr+0x00000c98+4*5))=0x69c31914;
*((unsigned int *)((unsigned long)context_ptr+0x00000600))=0x04c00038;
*((unsigned int *)((unsigned long)context_ptr+0x00000600+4*1))=0x00000cb0;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000000))=0x0cc00018;
*((unsigned int *)((unsigned long)context_ptr+0x00000000+4*1))=0x00000c98;
*((unsigned int *)((unsigned long)context_ptr+0x00000000+4*2))=0x00000c68;
*((unsigned int *)((unsigned long)context_ptr+0x00000000+4*3))=0x00220018;
*((unsigned int *)((unsigned long)context_ptr+0x00000000+4*4))=0x00441030;
*((unsigned int *)((unsigned long)context_ptr+0x00000000+4*5))=0x00000c00+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x00000ce8))=0x0300000c;
*((unsigned int *)((unsigned long)context_ptr+0x00000ce8+4*1))=0x23d80004;
*((unsigned int *)((unsigned long)context_ptr+0x00000ce8+4*2))=0x0c5ce588;
*((unsigned int *)((unsigned long)context_ptr+0x00000ce8+4*3))=0x9b996004;
*((unsigned int *)((unsigned long)context_ptr+0x00000ce8+4*4))=0x90d94008;
*((unsigned int *)((unsigned long)context_ptr+0x00000ce8+4*5))=0x96f03238;
*((unsigned int *)((unsigned long)context_ptr+0x00000ce8+4*6))=0x0000630c;
*((unsigned int *)((unsigned long)context_ptr+0x00000ce8+4*7))=0xa0820014;
*((unsigned int *)((unsigned long)context_ptr+0x00000ce8+4*8))=0x25000010;
*((unsigned int *)((unsigned long)context_ptr+0x00000ce8+4*9))=0x0f02000c;
*((unsigned int *)((unsigned long)context_ptr+0x00000ce8+4*10))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x00000ce8+4*11))=0xe12e180a;
*((unsigned int *)((unsigned long)context_ptr+0x00000d18))=0xc81e3b42;
*((unsigned int *)((unsigned long)context_ptr+0x00000d18+4*1))=0x3238bb19;
*((unsigned int *)((unsigned long)context_ptr+0x00000d18+4*2))=0x630c96f0;
*((unsigned int *)((unsigned long)context_ptr+0x00000d18+4*3))=0x483f5bbc;
*((unsigned int *)((unsigned long)context_ptr+0x00000d18+4*4))=0x83bda8bc;
*((unsigned int *)((unsigned long)context_ptr+0x00000d18+4*5))=0x1ea51fdb;
*((unsigned int *)((unsigned long)context_ptr+0x00000618))=0x04c00030;
*((unsigned int *)((unsigned long)context_ptr+0x00000618+4*1))=0x00000d30;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000018))=0x0cc00018;
*((unsigned int *)((unsigned long)context_ptr+0x00000018+4*1))=0x00000d18;
*((unsigned int *)((unsigned long)context_ptr+0x00000018+4*2))=0x00000ce8;
*((unsigned int *)((unsigned long)context_ptr+0x00000018+4*3))=0x00220018;
*((unsigned int *)((unsigned long)context_ptr+0x00000018+4*4))=0x006d4ba6;
*((unsigned int *)((unsigned long)context_ptr+0x00000018+4*5))=0x00000c34+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x00000d60))=0x0300000c;
*((unsigned int *)((unsigned long)context_ptr+0x00000d60+4*1))=0x23d80004;
*((unsigned int *)((unsigned long)context_ptr+0x00000d60+4*2))=0x0d2ce588;
*((unsigned int *)((unsigned long)context_ptr+0x00000d60+4*3))=0x93996004;
*((unsigned int *)((unsigned long)context_ptr+0x00000d60+4*4))=0x9bd94008;
*((unsigned int *)((unsigned long)context_ptr+0x00000d60+4*5))=0x35651ead;
*((unsigned int *)((unsigned long)context_ptr+0x00000d60+4*6))=0x2537f20a;
*((unsigned int *)((unsigned long)context_ptr+0x00000d60+4*7))=0xa082001c;
*((unsigned int *)((unsigned long)context_ptr+0x00000d60+4*8))=0x25000010;
*((unsigned int *)((unsigned long)context_ptr+0x00000d60+4*9))=0x0f02000d;
*((unsigned int *)((unsigned long)context_ptr+0x00000d60+4*10))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x00000d60+4*11))=0xe12e180a;
*((unsigned int *)((unsigned long)context_ptr+0x00000d90))=0xc2d0bb36;
*((unsigned int *)((unsigned long)context_ptr+0x00000d90+4*1))=0xe6a1975a;
*((unsigned int *)((unsigned long)context_ptr+0x00000d90+4*2))=0x5b86d51b;
*((unsigned int *)((unsigned long)context_ptr+0x00000d90+4*3))=0x0374b49a;
*((unsigned int *)((unsigned long)context_ptr+0x00000d90+4*4))=0x7ea9a738;
*((unsigned int *)((unsigned long)context_ptr+0x00000d90+4*5))=0xd9507bf4;
*((unsigned int *)((unsigned long)context_ptr+0x00000d90+4*6))=0x00000042;
*((unsigned int *)((unsigned long)context_ptr+0x00000630))=0x04c00039;
*((unsigned int *)((unsigned long)context_ptr+0x00000630+4*1))=0x00000dac;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000030))=0x0cc00019;
*((unsigned int *)((unsigned long)context_ptr+0x00000030+4*1))=0x00000d90;
*((unsigned int *)((unsigned long)context_ptr+0x00000030+4*2))=0x00000d60;
*((unsigned int *)((unsigned long)context_ptr+0x00000030+4*3))=0x00220019;
*((unsigned int *)((unsigned long)context_ptr+0x00000030+4*4))=0x00b41785;
*((unsigned int *)((unsigned long)context_ptr+0x00000030+4*5))=0x00000c00+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x00000de8))=0x0300000c;
*((unsigned int *)((unsigned long)context_ptr+0x00000de8+4*1))=0x23d80004;
*((unsigned int *)((unsigned long)context_ptr+0x00000de8+4*2))=0x0d5ce588;
*((unsigned int *)((unsigned long)context_ptr+0x00000de8+4*3))=0x9b996004;
*((unsigned int *)((unsigned long)context_ptr+0x00000de8+4*4))=0x90d94008;
*((unsigned int *)((unsigned long)context_ptr+0x00000de8+4*5))=0x96f03238;
*((unsigned int *)((unsigned long)context_ptr+0x00000de8+4*6))=0x0000630c;
*((unsigned int *)((unsigned long)context_ptr+0x00000de8+4*7))=0xa0820014;
*((unsigned int *)((unsigned long)context_ptr+0x00000de8+4*8))=0x25000010;
*((unsigned int *)((unsigned long)context_ptr+0x00000de8+4*9))=0x0f02000d;
*((unsigned int *)((unsigned long)context_ptr+0x00000de8+4*10))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x00000de8+4*11))=0xe12e180a;
*((unsigned int *)((unsigned long)context_ptr+0x00000e18))=0x11a7390b;
*((unsigned int *)((unsigned long)context_ptr+0x00000e18+4*1))=0x3238f80f;
*((unsigned int *)((unsigned long)context_ptr+0x00000e18+4*2))=0x630c96f0;
*((unsigned int *)((unsigned long)context_ptr+0x00000e18+4*3))=0xe46c8843;
*((unsigned int *)((unsigned long)context_ptr+0x00000e18+4*4))=0x2d5b6f37;
*((unsigned int *)((unsigned long)context_ptr+0x00000e18+4*5))=0x61bffc54;
*((unsigned int *)((unsigned long)context_ptr+0x00000e18+4*6))=0x00000068;
*((unsigned int *)((unsigned long)context_ptr+0x00000648))=0x04c00031;
*((unsigned int *)((unsigned long)context_ptr+0x00000648+4*1))=0x00000e34;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000048))=0x0cc00019;
*((unsigned int *)((unsigned long)context_ptr+0x00000048+4*1))=0x00000e18;
*((unsigned int *)((unsigned long)context_ptr+0x00000048+4*2))=0x00000de8;
*((unsigned int *)((unsigned long)context_ptr+0x00000048+4*3))=0x00220019;
*((unsigned int *)((unsigned long)context_ptr+0x00000048+4*4))=0x00c90ded;
*((unsigned int *)((unsigned long)context_ptr+0x00000048+4*5))=0x00000c34+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000006&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00000cb0,"\x33\xac\xbc\x4f\xdc\x41\x58\xb6\x0b\xef\x12\x75\x88\xe5\x2c\x0c\x00\x00\x43\x21\xad\x1e\x65\x35\x0a\xf2\x37\x25\x1b\x32\x3b\x8c\xa5\x85\x98\xa7\x8e\xf0\x2c\x4b\x9d\x1e\x63\x7c\xc1\x32\x40\x9b\xba\xf4\x06\xde\x33\x00\xc8\xb6",56))
printf("strip: 33acbc4fdc4158b6, Pass\n");
else
printf("strip: 33acbc4fdc4158b6, Failed\n");
writel(0x0000000c&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00000d30,"\x42\x3b\x1e\xc8\x19\xbb\x38\x32\xf0\x96\x0c\x63\x88\xe5\x5c\x0c\x00\x00\x87\x65\xe5\x31\x80\xb1\xfc\xc9\x76\xbc\xd1\x6b\xb8\xd5\x30\x72\x7e\xc2\xa0\x22\x86\x38\xc2\x29\xfb\xf1\x39\x18\x83\xb2",48))
printf("strip: 423b1ec819bb3832, Pass\n");
else
printf("strip: 423b1ec819bb3832, Failed\n");
writel(0x00000012&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00000dac,"\x36\xbb\xd0\xc2\x5a\x97\xa1\xe6\x1b\xd5\x86\x5b\x88\xe5\x2c\x0d\x00\x00\x43\x22\xad\x1e\x65\x35\x0a\xf2\x37\x25\xc3\x6e\x01\xcc\x98\x04\x1f\x24\xac\xc6\x94\x36\x35\x19\x28\xca\x8b\x5e\x19\x1f\xef\xdb\xc4\x02\x08\xc8\x33\x7a\x7d\x00\x00\x00",57))
printf("strip: 36bbd0c25a97a1e6, Pass\n");
else
printf("strip: 36bbd0c25a97a1e6, Failed\n");
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00000e34,"\x0b\x39\xa7\x11\x0f\xf8\x38\x32\xf0\x96\x0c\x63\x88\xe5\x5c\x0d\x00\x00\x87\x66\x20\xc4\x03\x5f\x19\xbd\xfe\x45\xa6\xf9\x5f\x41\x79\x4e\x6b\x05\x0a\x86\x45\x37\x0c\x37\xf9\xc8\xd8\x8a\x9b\x7d\x60\x00\x00\x00",49))
printf("strip: 0b39a7110ff83832, Pass\n");
else
printf("strip: 0b39a7110ff83832, Failed\n");
}

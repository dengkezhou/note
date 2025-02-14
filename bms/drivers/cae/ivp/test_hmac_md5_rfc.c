#include <common.h>
#include <malloc.h>

extern volatile unsigned int ivp_cae_base_addr;

void test_hmac_md5_rfc(void)
{
unsigned int *context_ptr=(unsigned int *)0x14000000;
printf("test_hmac_md5_rfc\n");
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
*((unsigned int *)((unsigned long)context_ptr+0x00006000))=0x006a0802;
*((unsigned int *)((unsigned long)context_ptr+0x00006000+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006000+4*2))=0x038733be;
*((unsigned int *)((unsigned long)context_ptr+0x00006000+4*3))=0x290c39ed;
*((unsigned int *)((unsigned long)context_ptr+0x00006000+4*4))=0x65703e6f;
*((unsigned int *)((unsigned long)context_ptr+0x00006000+4*5))=0x8d4c823e;
*((unsigned int *)((unsigned long)context_ptr+0x00006000+4*6))=0xd82b3cf5;
*((unsigned int *)((unsigned long)context_ptr+0x00006000+4*7))=0x26ab9142;
*((unsigned int *)((unsigned long)context_ptr+0x00006000+4*8))=0xe7acdd55;
*((unsigned int *)((unsigned long)context_ptr+0x00006000+4*9))=0x451307db;
*((unsigned int *)((unsigned long)context_ptr+0x00006028))=0x006a0802;
*((unsigned int *)((unsigned long)context_ptr+0x00006028+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006028+4*2))=0xcb6180e8;
*((unsigned int *)((unsigned long)context_ptr+0x00006028+4*3))=0x2fa83ea8;
*((unsigned int *)((unsigned long)context_ptr+0x00006028+4*4))=0x43278d6c;
*((unsigned int *)((unsigned long)context_ptr+0x00006028+4*5))=0xb9526934;
*((unsigned int *)((unsigned long)context_ptr+0x00006028+4*6))=0x53f5670c;
*((unsigned int *)((unsigned long)context_ptr+0x00006028+4*7))=0x4d4ca5e3;
*((unsigned int *)((unsigned long)context_ptr+0x00006028+4*8))=0x0f66faca;
*((unsigned int *)((unsigned long)context_ptr+0x00006028+4*9))=0x781f2ab7;
*((unsigned int *)((unsigned long)context_ptr+0x00006050))=0x006a0802;
*((unsigned int *)((unsigned long)context_ptr+0x00006050+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006050+4*2))=0xb5aaf52d;
*((unsigned int *)((unsigned long)context_ptr+0x00006050+4*3))=0x46403fd0;
*((unsigned int *)((unsigned long)context_ptr+0x00006050+4*4))=0xeafd5688;
*((unsigned int *)((unsigned long)context_ptr+0x00006050+4*5))=0xf833f6fa;
*((unsigned int *)((unsigned long)context_ptr+0x00006050+4*6))=0x521df4c9;
*((unsigned int *)((unsigned long)context_ptr+0x00006050+4*7))=0x711fd598;
*((unsigned int *)((unsigned long)context_ptr+0x00006050+4*8))=0x748e25d2;
*((unsigned int *)((unsigned long)context_ptr+0x00006050+4*9))=0x3cca394a;
*((unsigned int *)((unsigned long)context_ptr+0x00006078))=0x006a0802;
*((unsigned int *)((unsigned long)context_ptr+0x00006078+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006078+4*2))=0x9c065fcd;
*((unsigned int *)((unsigned long)context_ptr+0x00006078+4*3))=0x09cee70a;
*((unsigned int *)((unsigned long)context_ptr+0x00006078+4*4))=0xe4e22e94;
*((unsigned int *)((unsigned long)context_ptr+0x00006078+4*5))=0x4d7f1733;
*((unsigned int *)((unsigned long)context_ptr+0x00006078+4*6))=0xba632c29;
*((unsigned int *)((unsigned long)context_ptr+0x00006078+4*7))=0xe83f0c78;
*((unsigned int *)((unsigned long)context_ptr+0x00006078+4*8))=0x1d7854c7;
*((unsigned int *)((unsigned long)context_ptr+0x00006078+4*9))=0x5a768e5d;
*((unsigned int *)((unsigned long)context_ptr+0x000060a0))=0x006a0802;
*((unsigned int *)((unsigned long)context_ptr+0x000060a0+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000060a0+4*2))=0x6dcaeabf;
*((unsigned int *)((unsigned long)context_ptr+0x000060a0+4*3))=0x2f7419ba;
*((unsigned int *)((unsigned long)context_ptr+0x000060a0+4*4))=0x78301f96;
*((unsigned int *)((unsigned long)context_ptr+0x000060a0+4*5))=0x0bc8e999;
*((unsigned int *)((unsigned long)context_ptr+0x000060a0+4*6))=0x8262f776;
*((unsigned int *)((unsigned long)context_ptr+0x000060a0+4*7))=0x8e26493b;
*((unsigned int *)((unsigned long)context_ptr+0x000060a0+4*8))=0x68975582;
*((unsigned int *)((unsigned long)context_ptr+0x000060a0+4*9))=0x3f474e10;
*((unsigned int *)((unsigned long)context_ptr+0x000060c8))=0x006a0802;
*((unsigned int *)((unsigned long)context_ptr+0x000060c8+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000060c8+4*2))=0x3d640508;
*((unsigned int *)((unsigned long)context_ptr+0x000060c8+4*3))=0xb894145a;
*((unsigned int *)((unsigned long)context_ptr+0x000060c8+4*4))=0x74fb04aa;
*((unsigned int *)((unsigned long)context_ptr+0x000060c8+4*5))=0x9cc27773;
*((unsigned int *)((unsigned long)context_ptr+0x000060c8+4*6))=0x6b8a94f0;
*((unsigned int *)((unsigned long)context_ptr+0x000060c8+4*7))=0xcc2581ae;
*((unsigned int *)((unsigned long)context_ptr+0x000060c8+4*8))=0xede24d3e;
*((unsigned int *)((unsigned long)context_ptr+0x000060c8+4*9))=0x548c4ba4;
*((unsigned int *)((unsigned long)context_ptr+0x000060f0))=0x006a0802;
*((unsigned int *)((unsigned long)context_ptr+0x000060f0+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000060f0+4*2))=0x3d640508;
*((unsigned int *)((unsigned long)context_ptr+0x000060f0+4*3))=0xb894145a;
*((unsigned int *)((unsigned long)context_ptr+0x000060f0+4*4))=0x74fb04aa;
*((unsigned int *)((unsigned long)context_ptr+0x000060f0+4*5))=0x9cc27773;
*((unsigned int *)((unsigned long)context_ptr+0x000060f0+4*6))=0x6b8a94f0;
*((unsigned int *)((unsigned long)context_ptr+0x000060f0+4*7))=0xcc2581ae;
*((unsigned int *)((unsigned long)context_ptr+0x000060f0+4*8))=0xede24d3e;
*((unsigned int *)((unsigned long)context_ptr+0x000060f0+4*9))=0x548c4ba4;
*((unsigned int *)((unsigned long)context_ptr+0x00006118))=0x006a0802;
*((unsigned int *)((unsigned long)context_ptr+0x00006118+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006118+4*2))=0x02020008;
*((unsigned int *)((unsigned long)context_ptr+0x00006118+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x00006128))=0x54206948;
*((unsigned int *)((unsigned long)context_ptr+0x00006128+4*1))=0x65726568;
*((unsigned int *)((unsigned long)context_ptr+0x00003000))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003000+4*1))=0x00006130;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000000+4*1))=0x00006128;
*((unsigned int *)((unsigned long)context_ptr+0x00000000+4*2))=0x00006118;
*((unsigned int *)((unsigned long)context_ptr+0x00000000+4*3))=0x02220008;
*((unsigned int *)((unsigned long)context_ptr+0x00000000+4*4))=0x0ffb1c2c;
*((unsigned int *)((unsigned long)context_ptr+0x00000000+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x00006140))=0x006a0802;
*((unsigned int *)((unsigned long)context_ptr+0x00006140+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006140+4*2))=0x0202001c;
*((unsigned int *)((unsigned long)context_ptr+0x00006140+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x00006150))=0x74616877;
*((unsigned int *)((unsigned long)context_ptr+0x00006150+4*1))=0x206f6420;
*((unsigned int *)((unsigned long)context_ptr+0x00006150+4*2))=0x77206179;
*((unsigned int *)((unsigned long)context_ptr+0x00006150+4*3))=0x20746e61;
*((unsigned int *)((unsigned long)context_ptr+0x00006150+4*4))=0x20726f66;
*((unsigned int *)((unsigned long)context_ptr+0x00006150+4*5))=0x68746f6e;
*((unsigned int *)((unsigned long)context_ptr+0x00006150+4*6))=0x3f676e69;
*((unsigned int *)((unsigned long)context_ptr+0x00003018))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003018+4*1))=0x0000616c;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000018+4*1))=0x00006150;
*((unsigned int *)((unsigned long)context_ptr+0x00000018+4*2))=0x00006140;
*((unsigned int *)((unsigned long)context_ptr+0x00000018+4*3))=0x0222001c;
*((unsigned int *)((unsigned long)context_ptr+0x00000018+4*4))=0x0b11bb2b;
*((unsigned int *)((unsigned long)context_ptr+0x00000018+4*5))=0x00006028+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x0000617c))=0x006a0802;
*((unsigned int *)((unsigned long)context_ptr+0x0000617c+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x0000617c+4*2))=0x02020032;
*((unsigned int *)((unsigned long)context_ptr+0x0000617c+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x0000618c))=0xdddddddd;
*((unsigned int *)((unsigned long)context_ptr+0x0000618c+4*1))=0xdddddddd;
*((unsigned int *)((unsigned long)context_ptr+0x0000618c+4*2))=0xdddddddd;
*((unsigned int *)((unsigned long)context_ptr+0x0000618c+4*3))=0xdddddddd;
*((unsigned int *)((unsigned long)context_ptr+0x0000618c+4*4))=0xdddddddd;
*((unsigned int *)((unsigned long)context_ptr+0x0000618c+4*5))=0xdddddddd;
*((unsigned int *)((unsigned long)context_ptr+0x0000618c+4*6))=0xdddddddd;
*((unsigned int *)((unsigned long)context_ptr+0x0000618c+4*7))=0xdddddddd;
*((unsigned int *)((unsigned long)context_ptr+0x0000618c+4*8))=0xdddddddd;
*((unsigned int *)((unsigned long)context_ptr+0x0000618c+4*9))=0xdddddddd;
*((unsigned int *)((unsigned long)context_ptr+0x0000618c+4*10))=0xdddddddd;
*((unsigned int *)((unsigned long)context_ptr+0x0000618c+4*11))=0xdddddddd;
*((unsigned int *)((unsigned long)context_ptr+0x0000618c+4*12))=0x0000dddd;
*((unsigned int *)((unsigned long)context_ptr+0x00003030))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003030+4*1))=0x000061c0;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000030+4*1))=0x0000618c;
*((unsigned int *)((unsigned long)context_ptr+0x00000030+4*2))=0x0000617c;
*((unsigned int *)((unsigned long)context_ptr+0x00000030+4*3))=0x02220032;
*((unsigned int *)((unsigned long)context_ptr+0x00000030+4*4))=0x08f0c416;
*((unsigned int *)((unsigned long)context_ptr+0x00000030+4*5))=0x00006050+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x000061d0))=0x006a0802;
*((unsigned int *)((unsigned long)context_ptr+0x000061d0+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000061d0+4*2))=0x02020032;
*((unsigned int *)((unsigned long)context_ptr+0x000061d0+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x000061e0))=0xcdcdcdcd;
*((unsigned int *)((unsigned long)context_ptr+0x000061e0+4*1))=0xcdcdcdcd;
*((unsigned int *)((unsigned long)context_ptr+0x000061e0+4*2))=0xcdcdcdcd;
*((unsigned int *)((unsigned long)context_ptr+0x000061e0+4*3))=0xcdcdcdcd;
*((unsigned int *)((unsigned long)context_ptr+0x000061e0+4*4))=0xcdcdcdcd;
*((unsigned int *)((unsigned long)context_ptr+0x000061e0+4*5))=0xcdcdcdcd;
*((unsigned int *)((unsigned long)context_ptr+0x000061e0+4*6))=0xcdcdcdcd;
*((unsigned int *)((unsigned long)context_ptr+0x000061e0+4*7))=0xcdcdcdcd;
*((unsigned int *)((unsigned long)context_ptr+0x000061e0+4*8))=0xcdcdcdcd;
*((unsigned int *)((unsigned long)context_ptr+0x000061e0+4*9))=0xcdcdcdcd;
*((unsigned int *)((unsigned long)context_ptr+0x000061e0+4*10))=0xcdcdcdcd;
*((unsigned int *)((unsigned long)context_ptr+0x000061e0+4*11))=0xcdcdcdcd;
*((unsigned int *)((unsigned long)context_ptr+0x000061e0+4*12))=0x0000cdcd;
*((unsigned int *)((unsigned long)context_ptr+0x00003048))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003048+4*1))=0x00006214;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000048+4*1))=0x000061e0;
*((unsigned int *)((unsigned long)context_ptr+0x00000048+4*2))=0x000061d0;
*((unsigned int *)((unsigned long)context_ptr+0x00000048+4*3))=0x02220032;
*((unsigned int *)((unsigned long)context_ptr+0x00000048+4*4))=0x032a564e;
*((unsigned int *)((unsigned long)context_ptr+0x00000048+4*5))=0x00006078+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x00006224))=0x006a0802;
*((unsigned int *)((unsigned long)context_ptr+0x00006224+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006224+4*2))=0x02020014;
*((unsigned int *)((unsigned long)context_ptr+0x00006224+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x00006234))=0x74736554;
*((unsigned int *)((unsigned long)context_ptr+0x00006234+4*1))=0x74695720;
*((unsigned int *)((unsigned long)context_ptr+0x00006234+4*2))=0x72542068;
*((unsigned int *)((unsigned long)context_ptr+0x00006234+4*3))=0x61636e75;
*((unsigned int *)((unsigned long)context_ptr+0x00006234+4*4))=0x6e6f6974;
*((unsigned int *)((unsigned long)context_ptr+0x00003060))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003060+4*1))=0x00006248;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000060+4*1))=0x00006234;
*((unsigned int *)((unsigned long)context_ptr+0x00000060+4*2))=0x00006224;
*((unsigned int *)((unsigned long)context_ptr+0x00000060+4*3))=0x02220014;
*((unsigned int *)((unsigned long)context_ptr+0x00000060+4*4))=0x093d5e32;
*((unsigned int *)((unsigned long)context_ptr+0x00000060+4*5))=0x000060a0+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x00006258))=0x006a0802;
*((unsigned int *)((unsigned long)context_ptr+0x00006258+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006258+4*2))=0x02020036;
*((unsigned int *)((unsigned long)context_ptr+0x00006258+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x00006268))=0x74736554;
*((unsigned int *)((unsigned long)context_ptr+0x00006268+4*1))=0x69735520;
*((unsigned int *)((unsigned long)context_ptr+0x00006268+4*2))=0x4c20676e;
*((unsigned int *)((unsigned long)context_ptr+0x00006268+4*3))=0x65677261;
*((unsigned int *)((unsigned long)context_ptr+0x00006268+4*4))=0x68542072;
*((unsigned int *)((unsigned long)context_ptr+0x00006268+4*5))=0x42206e61;
*((unsigned int *)((unsigned long)context_ptr+0x00006268+4*6))=0x6b636f6c;
*((unsigned int *)((unsigned long)context_ptr+0x00006268+4*7))=0x7a69532d;
*((unsigned int *)((unsigned long)context_ptr+0x00006268+4*8))=0x654b2065;
*((unsigned int *)((unsigned long)context_ptr+0x00006268+4*9))=0x202d2079;
*((unsigned int *)((unsigned long)context_ptr+0x00006268+4*10))=0x68736148;
*((unsigned int *)((unsigned long)context_ptr+0x00006268+4*11))=0x79654b20;
*((unsigned int *)((unsigned long)context_ptr+0x00006268+4*12))=0x72694620;
*((unsigned int *)((unsigned long)context_ptr+0x00006268+4*13))=0x00007473;
*((unsigned int *)((unsigned long)context_ptr+0x00003078))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003078+4*1))=0x000062a0;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000078+4*1))=0x00006268;
*((unsigned int *)((unsigned long)context_ptr+0x00000078+4*2))=0x00006258;
*((unsigned int *)((unsigned long)context_ptr+0x00000078+4*3))=0x02220036;
*((unsigned int *)((unsigned long)context_ptr+0x00000078+4*4))=0x089419af;
*((unsigned int *)((unsigned long)context_ptr+0x00000078+4*5))=0x000060c8+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x000062b0))=0x006a0802;
*((unsigned int *)((unsigned long)context_ptr+0x000062b0+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000062b0+4*2))=0x02020049;
*((unsigned int *)((unsigned long)context_ptr+0x000062b0+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x000062c0))=0x74736554;
*((unsigned int *)((unsigned long)context_ptr+0x000062c0+4*1))=0x69735520;
*((unsigned int *)((unsigned long)context_ptr+0x000062c0+4*2))=0x4c20676e;
*((unsigned int *)((unsigned long)context_ptr+0x000062c0+4*3))=0x65677261;
*((unsigned int *)((unsigned long)context_ptr+0x000062c0+4*4))=0x68542072;
*((unsigned int *)((unsigned long)context_ptr+0x000062c0+4*5))=0x42206e61;
*((unsigned int *)((unsigned long)context_ptr+0x000062c0+4*6))=0x6b636f6c;
*((unsigned int *)((unsigned long)context_ptr+0x000062c0+4*7))=0x7a69532d;
*((unsigned int *)((unsigned long)context_ptr+0x000062c0+4*8))=0x654b2065;
*((unsigned int *)((unsigned long)context_ptr+0x000062c0+4*9))=0x6e612079;
*((unsigned int *)((unsigned long)context_ptr+0x000062c0+4*10))=0x614c2064;
*((unsigned int *)((unsigned long)context_ptr+0x000062c0+4*11))=0x72656772;
*((unsigned int *)((unsigned long)context_ptr+0x000062c0+4*12))=0x61685420;
*((unsigned int *)((unsigned long)context_ptr+0x000062c0+4*13))=0x6e4f206e;
*((unsigned int *)((unsigned long)context_ptr+0x000062c0+4*14))=0x6c422065;
*((unsigned int *)((unsigned long)context_ptr+0x000062c0+4*15))=0x2d6b636f;
*((unsigned int *)((unsigned long)context_ptr+0x000062c0+4*16))=0x657a6953;
*((unsigned int *)((unsigned long)context_ptr+0x000062c0+4*17))=0x74614420;
*((unsigned int *)((unsigned long)context_ptr+0x000062c0+4*18))=0x00000061;
*((unsigned int *)((unsigned long)context_ptr+0x00003090))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003090+4*1))=0x0000630c;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000090+4*1))=0x000062c0;
*((unsigned int *)((unsigned long)context_ptr+0x00000090+4*2))=0x000062b0;
*((unsigned int *)((unsigned long)context_ptr+0x00000090+4*3))=0x02220049;
*((unsigned int *)((unsigned long)context_ptr+0x00000090+4*4))=0x0e3352f8;
*((unsigned int *)((unsigned long)context_ptr+0x00000090+4*5))=0x000060f0+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000006&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006130,"\x92\x94\x72\x7a\x36\x38\xbb\x1c\x13\xf4\x8e\xf8\x15\x8b\xfc\x9d",16))
printf("strip: 9294727a3638bb1c, Pass\n");
else
printf("strip: 9294727a3638bb1c, Failed\n");
writel(0x0000000c&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x0000616c,"\x75\x0c\x78\x3e\x6a\xb0\xb5\x03\xea\xa8\x6e\x31\x0a\x5d\xb7\x38",16))
printf("strip: 750c783e6ab0b503, Pass\n");
else
printf("strip: 750c783e6ab0b503, Failed\n");
writel(0x00000012&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000061c0,"\x56\xbe\x34\x52\x1d\x14\x4c\x88\xdb\xb8\xc7\x33\xf0\xe8\xb3\xf6",16))
printf("strip: 56be34521d144c88, Pass\n");
else
printf("strip: 56be34521d144c88, Failed\n");
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006214,"\x69\x7e\xaf\x0a\xca\x3a\x3a\xea\x3a\x75\x16\x47\x46\xff\xaa\x79",16))
printf("strip: 697eaf0aca3a3aea, Pass\n");
else
printf("strip: 697eaf0aca3a3aea, Failed\n");
writel(0x0000001e&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006248,"\x56\x46\x1e\xf2\x34\x2e\xdc\x00\xf9\xba\xb9\x95\x69\x0e\xfd\x4c",16))
printf("strip: 56461ef2342edc00, Pass\n");
else
printf("strip: 56461ef2342edc00, Failed\n");
writel(0x00000024&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000062a0,"\x6b\x1a\xb7\xfe\x4b\xd7\xbf\x8f\x0b\x62\xe6\xce\x61\xb9\xd0\xcd",16))
printf("strip: 6b1ab7fe4bd7bf8f, Pass\n");
else
printf("strip: 6b1ab7fe4bd7bf8f, Failed\n");
writel(0x0000002a&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x0000630c,"\x6f\x63\x0f\xad\x67\xcd\xa0\xee\x1f\xb1\xf5\x62\xdb\x3a\xa5\x3e",16))
printf("strip: 6f630fad67cda0ee, Pass\n");
else
printf("strip: 6f630fad67cda0ee, Failed\n");
}

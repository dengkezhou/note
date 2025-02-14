#include <common.h>
#include <malloc.h>

extern volatile unsigned int ivp_cae_base_addr;

void test_sha384_fips(void)
{
unsigned int *context_ptr=(unsigned int *)0x14000000;
printf("test_sha384_fips\n");
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
*((unsigned int *)((unsigned long)context_ptr+0x00006000))=0x030a0002;
*((unsigned int *)((unsigned long)context_ptr+0x00006000+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006008))=0x030a0002;
*((unsigned int *)((unsigned long)context_ptr+0x00006008+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006010))=0x030a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006010+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006010+4*2))=0x02020003;
*((unsigned int *)((unsigned long)context_ptr+0x00006010+4*3))=0x21e60030;
*((unsigned int *)((unsigned long)context_ptr+0x00006020))=0x00636261;
*((unsigned int *)((unsigned long)context_ptr+0x00003000))=0x04c00030;
*((unsigned int *)((unsigned long)context_ptr+0x00003000+4*1))=0x00006024;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000000))=0x04c00003;
*((unsigned int *)((unsigned long)context_ptr+0x00000000+4*1))=0x00006020;
*((unsigned int *)((unsigned long)context_ptr+0x00000000+4*2))=0x00006010;
*((unsigned int *)((unsigned long)context_ptr+0x00000000+4*3))=0x02220003;
*((unsigned int *)((unsigned long)context_ptr+0x00000000+4*4))=0x0339d78e;
*((unsigned int *)((unsigned long)context_ptr+0x00000000+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x00006054))=0x030a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006054+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006054+4*2))=0x02020070;
*((unsigned int *)((unsigned long)context_ptr+0x00006054+4*3))=0x21e60030;
*((unsigned int *)((unsigned long)context_ptr+0x00006064))=0x64636261;
*((unsigned int *)((unsigned long)context_ptr+0x00006064+4*1))=0x68676665;
*((unsigned int *)((unsigned long)context_ptr+0x00006064+4*2))=0x65646362;
*((unsigned int *)((unsigned long)context_ptr+0x00006064+4*3))=0x69686766;
*((unsigned int *)((unsigned long)context_ptr+0x00006064+4*4))=0x66656463;
*((unsigned int *)((unsigned long)context_ptr+0x00006064+4*5))=0x6a696867;
*((unsigned int *)((unsigned long)context_ptr+0x00006064+4*6))=0x67666564;
*((unsigned int *)((unsigned long)context_ptr+0x00006064+4*7))=0x6b6a6968;
*((unsigned int *)((unsigned long)context_ptr+0x00006064+4*8))=0x68676665;
*((unsigned int *)((unsigned long)context_ptr+0x00006064+4*9))=0x6c6b6a69;
*((unsigned int *)((unsigned long)context_ptr+0x00006064+4*10))=0x69686766;
*((unsigned int *)((unsigned long)context_ptr+0x00006064+4*11))=0x6d6c6b6a;
*((unsigned int *)((unsigned long)context_ptr+0x00006064+4*12))=0x6a696867;
*((unsigned int *)((unsigned long)context_ptr+0x00006064+4*13))=0x6e6d6c6b;
*((unsigned int *)((unsigned long)context_ptr+0x00006064+4*14))=0x6b6a6968;
*((unsigned int *)((unsigned long)context_ptr+0x00006064+4*15))=0x6f6e6d6c;
*((unsigned int *)((unsigned long)context_ptr+0x00006064+4*16))=0x6c6b6a69;
*((unsigned int *)((unsigned long)context_ptr+0x00006064+4*17))=0x706f6e6d;
*((unsigned int *)((unsigned long)context_ptr+0x00006064+4*18))=0x6d6c6b6a;
*((unsigned int *)((unsigned long)context_ptr+0x00006064+4*19))=0x71706f6e;
*((unsigned int *)((unsigned long)context_ptr+0x00006064+4*20))=0x6e6d6c6b;
*((unsigned int *)((unsigned long)context_ptr+0x00006064+4*21))=0x7271706f;
*((unsigned int *)((unsigned long)context_ptr+0x00006064+4*22))=0x6f6e6d6c;
*((unsigned int *)((unsigned long)context_ptr+0x00006064+4*23))=0x73727170;
*((unsigned int *)((unsigned long)context_ptr+0x00006064+4*24))=0x706f6e6d;
*((unsigned int *)((unsigned long)context_ptr+0x00006064+4*25))=0x74737271;
*((unsigned int *)((unsigned long)context_ptr+0x00006064+4*26))=0x71706f6e;
*((unsigned int *)((unsigned long)context_ptr+0x00006064+4*27))=0x75747372;
*((unsigned int *)((unsigned long)context_ptr+0x00003018))=0x04c00030;
*((unsigned int *)((unsigned long)context_ptr+0x00003018+4*1))=0x000060d4;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000018))=0x04c00070;
*((unsigned int *)((unsigned long)context_ptr+0x00000018+4*1))=0x00006064;
*((unsigned int *)((unsigned long)context_ptr+0x00000018+4*2))=0x00006054;
*((unsigned int *)((unsigned long)context_ptr+0x00000018+4*3))=0x02220070;
*((unsigned int *)((unsigned long)context_ptr+0x00000018+4*4))=0x0deffed5;
*((unsigned int *)((unsigned long)context_ptr+0x00000018+4*5))=0x00006008+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000006&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006024,"\xcb\x00\x75\x3f\x45\xa3\x5e\x8b\xb5\xa0\x3d\x69\x9a\xc6\x50\x07\x27\x2c\x32\xab\x0e\xde\xd1\x63\x1a\x8b\x60\x5a\x43\xff\x5b\xed\x80\x86\x07\x2b\xa1\xe7\xcc\x23\x58\xba\xec\xa1\x34\xc8\x25\xa7",48))
printf("strip: cb00753f45a35e8b, Pass\n");
else
printf("strip: cb00753f45a35e8b, Failed\n");
writel(0x0000000c&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000060d4,"\x09\x33\x0c\x33\xf7\x11\x47\xe8\x3d\x19\x2f\xc7\x82\xcd\x1b\x47\x53\x11\x1b\x17\x3b\x3b\x05\xd2\x2f\xa0\x80\x86\xe3\xb0\xf7\x12\xfc\xc7\xc7\x1a\x55\x7e\x2d\xb9\x66\xc3\xe9\xfa\x91\x74\x60\x39",48))
printf("strip: 09330c33f71147e8, Pass\n");
else
printf("strip: 09330c33f71147e8, Failed\n");
}

#include <common.h>
#include <malloc.h>

extern volatile unsigned int ivp_cae_base_addr;

void test_sha1_save_hash(void)
{
unsigned int *context_ptr=(unsigned int *)0x14000000;
printf("test_sha1_save_hash\n");
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
*((unsigned int *)((unsigned long)context_ptr+0x00006000))=0x010a0502;
*((unsigned int *)((unsigned long)context_ptr+0x00006000+4*1))=0x00080001;
*((unsigned int *)((unsigned long)context_ptr+0x00006000+4*2))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x00006000+4*3))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x00006000+4*4))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x00006000+4*5))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x00006000+4*6))=0x00000000;
*((unsigned int *)((unsigned long)context_ptr+0x0000601c))=0x010a0512;
*((unsigned int *)((unsigned long)context_ptr+0x0000601c+4*1))=0x00080001;
*((unsigned int *)((unsigned long)context_ptr+0x0000601c+4*2))=0x02020078;
*((unsigned int *)((unsigned long)context_ptr+0x0000601c+4*3))=0x21e60014;
*((unsigned int *)((unsigned long)context_ptr+0x0000601c+4*4))=0xe5e61802;
*((unsigned int *)((unsigned long)context_ptr+0x00006030))=0x6bb2c7e3;
*((unsigned int *)((unsigned long)context_ptr+0x00006030+4*1))=0x906d1d4e;
*((unsigned int *)((unsigned long)context_ptr+0x00006030+4*2))=0x196aefec;
*((unsigned int *)((unsigned long)context_ptr+0x00006030+4*3))=0x7207bbc6;
*((unsigned int *)((unsigned long)context_ptr+0x00006030+4*4))=0xf6eb07af;
*((unsigned int *)((unsigned long)context_ptr+0x00006030+4*5))=0x5b1214b8;
*((unsigned int *)((unsigned long)context_ptr+0x00006030+4*6))=0xf9025907;
*((unsigned int *)((unsigned long)context_ptr+0x00006030+4*7))=0x35e412d1;
*((unsigned int *)((unsigned long)context_ptr+0x00006030+4*8))=0x1ff0ac34;
*((unsigned int *)((unsigned long)context_ptr+0x00006030+4*9))=0x9a065e01;
*((unsigned int *)((unsigned long)context_ptr+0x00006030+4*10))=0x581c2fdb;
*((unsigned int *)((unsigned long)context_ptr+0x00006030+4*11))=0x5cf721f5;
*((unsigned int *)((unsigned long)context_ptr+0x00006030+4*12))=0xf5ef4a79;
*((unsigned int *)((unsigned long)context_ptr+0x00006030+4*13))=0x1afe2fa2;
*((unsigned int *)((unsigned long)context_ptr+0x00006030+4*14))=0xf2e52894;
*((unsigned int *)((unsigned long)context_ptr+0x00006030+4*15))=0xc13e50cd;
*((unsigned int *)((unsigned long)context_ptr+0x00006030+4*16))=0x210b6b4a;
*((unsigned int *)((unsigned long)context_ptr+0x00006030+4*17))=0x6b121305;
*((unsigned int *)((unsigned long)context_ptr+0x00006030+4*18))=0x6c24bd8c;
*((unsigned int *)((unsigned long)context_ptr+0x00006030+4*19))=0x5e7115a3;
*((unsigned int *)((unsigned long)context_ptr+0x00006030+4*20))=0x6a680ef2;
*((unsigned int *)((unsigned long)context_ptr+0x00006030+4*21))=0x4b3452ba;
*((unsigned int *)((unsigned long)context_ptr+0x00006030+4*22))=0x46cbf378;
*((unsigned int *)((unsigned long)context_ptr+0x00006030+4*23))=0x72cbb08e;
*((unsigned int *)((unsigned long)context_ptr+0x00006030+4*24))=0x3f6ec466;
*((unsigned int *)((unsigned long)context_ptr+0x00006030+4*25))=0x7624ef74;
*((unsigned int *)((unsigned long)context_ptr+0x00006030+4*26))=0x00347ba3;
*((unsigned int *)((unsigned long)context_ptr+0x00006030+4*27))=0x4c019eb2;
*((unsigned int *)((unsigned long)context_ptr+0x00006030+4*28))=0x278ba1c4;
*((unsigned int *)((unsigned long)context_ptr+0x00006030+4*29))=0xc2ad78b4;
*((unsigned int *)((unsigned long)context_ptr+0x00003000))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00003000+4*1))=0x000060a8;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000000))=0x05c00078;
*((unsigned int *)((unsigned long)context_ptr+0x00000000+4*1))=0x00006030;
*((unsigned int *)((unsigned long)context_ptr+0x00000000+4*2))=0x0000601c;
*((unsigned int *)((unsigned long)context_ptr+0x00000000+4*3))=0x02220078;
*((unsigned int *)((unsigned long)context_ptr+0x00000000+4*4))=0x047b3df4;
*((unsigned int *)((unsigned long)context_ptr+0x00000000+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000006&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000060a8,"\xe7\x91\x07\x38\xad\xfa\x31\xc2\xf4\x51\x0b\xe6\xbb\xf5\xcb\x66\x98\x26\xec\xa2",20))
printf("strip: e7910738adfa31c2, Pass\n");
else
printf("strip: e7910738adfa31c2, Failed\n");
}

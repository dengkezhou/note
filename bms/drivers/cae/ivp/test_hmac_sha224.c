#include <common.h>
#include <malloc.h>

extern volatile unsigned int ivp_cae_base_addr;

void test_hmac_sha224(void)
{
unsigned int *context_ptr=(unsigned int *)0x14000000;
printf("test_hmac_sha224\n");
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
*((unsigned int *)((unsigned long)context_ptr+0x00006000))=0x026a1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006000+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006000+4*2))=0xaf17c90f;
*((unsigned int *)((unsigned long)context_ptr+0x00006000+4*3))=0x2ffd3d63;
*((unsigned int *)((unsigned long)context_ptr+0x00006000+4*4))=0x0219d528;
*((unsigned int *)((unsigned long)context_ptr+0x00006000+4*5))=0xec5354fb;
*((unsigned int *)((unsigned long)context_ptr+0x00006000+4*6))=0x4ef79a26;
*((unsigned int *)((unsigned long)context_ptr+0x00006000+4*7))=0x5de9dc0a;
*((unsigned int *)((unsigned long)context_ptr+0x00006000+4*8))=0x36623159;
*((unsigned int *)((unsigned long)context_ptr+0x00006000+4*9))=0xd0af730b;
*((unsigned int *)((unsigned long)context_ptr+0x00006000+4*10))=0x68c8171d;
*((unsigned int *)((unsigned long)context_ptr+0x00006000+4*11))=0x1f6c146d;
*((unsigned int *)((unsigned long)context_ptr+0x00006000+4*12))=0xa0c1996c;
*((unsigned int *)((unsigned long)context_ptr+0x00006000+4*13))=0xa11cae31;
*((unsigned int *)((unsigned long)context_ptr+0x00006000+4*14))=0x86f5c4eb;
*((unsigned int *)((unsigned long)context_ptr+0x00006000+4*15))=0xe7530ab4;
*((unsigned int *)((unsigned long)context_ptr+0x00006000+4*16))=0x3e503460;
*((unsigned int *)((unsigned long)context_ptr+0x00006000+4*17))=0x629cf2e4;
*((unsigned int *)((unsigned long)context_ptr+0x00006048))=0x026a1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006048+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006048+4*2))=0x02020001;
*((unsigned int *)((unsigned long)context_ptr+0x00006048+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x00006058))=0x00000025;
*((unsigned int *)((unsigned long)context_ptr+0x00003000))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003000+4*1))=0x0000605c;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000000))=0x04c00001;
*((unsigned int *)((unsigned long)context_ptr+0x00000000+4*1))=0x00006058;
*((unsigned int *)((unsigned long)context_ptr+0x00000000+4*2))=0x00006048;
*((unsigned int *)((unsigned long)context_ptr+0x00000000+4*3))=0x02220001;
*((unsigned int *)((unsigned long)context_ptr+0x00000000+4*4))=0x0d7a3281;
*((unsigned int *)((unsigned long)context_ptr+0x00000000+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x00006078))=0x026a1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006078+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006078+4*2))=0x02020002;
*((unsigned int *)((unsigned long)context_ptr+0x00006078+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x00006088))=0x00007bd3;
*((unsigned int *)((unsigned long)context_ptr+0x00003018))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003018+4*1))=0x0000608c;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000018))=0x04c00002;
*((unsigned int *)((unsigned long)context_ptr+0x00000018+4*1))=0x00006088;
*((unsigned int *)((unsigned long)context_ptr+0x00000018+4*2))=0x00006078;
*((unsigned int *)((unsigned long)context_ptr+0x00000018+4*3))=0x02220002;
*((unsigned int *)((unsigned long)context_ptr+0x00000018+4*4))=0x0961d8db;
*((unsigned int *)((unsigned long)context_ptr+0x00000018+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x000060a8))=0x026a1002;
*((unsigned int *)((unsigned long)context_ptr+0x000060a8+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000060a8+4*2))=0x02020003;
*((unsigned int *)((unsigned long)context_ptr+0x000060a8+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x000060b8))=0x0026780c;
*((unsigned int *)((unsigned long)context_ptr+0x00003030))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003030+4*1))=0x000060bc;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000030))=0x04c00003;
*((unsigned int *)((unsigned long)context_ptr+0x00000030+4*1))=0x000060b8;
*((unsigned int *)((unsigned long)context_ptr+0x00000030+4*2))=0x000060a8;
*((unsigned int *)((unsigned long)context_ptr+0x00000030+4*3))=0x02220003;
*((unsigned int *)((unsigned long)context_ptr+0x00000030+4*4))=0x0a145788;
*((unsigned int *)((unsigned long)context_ptr+0x00000030+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x000060d8))=0x026a1002;
*((unsigned int *)((unsigned long)context_ptr+0x000060d8+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000060d8+4*2))=0x02020004;
*((unsigned int *)((unsigned long)context_ptr+0x000060d8+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x000060e8))=0xe67cef0b;
*((unsigned int *)((unsigned long)context_ptr+0x00003048))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003048+4*1))=0x000060ec;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000048))=0x04c00004;
*((unsigned int *)((unsigned long)context_ptr+0x00000048+4*1))=0x000060e8;
*((unsigned int *)((unsigned long)context_ptr+0x00000048+4*2))=0x000060d8;
*((unsigned int *)((unsigned long)context_ptr+0x00000048+4*3))=0x02220004;
*((unsigned int *)((unsigned long)context_ptr+0x00000048+4*4))=0x0926146d;
*((unsigned int *)((unsigned long)context_ptr+0x00000048+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x00006108))=0x026a1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006108+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006108+4*2))=0x02020005;
*((unsigned int *)((unsigned long)context_ptr+0x00006108+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x00006118))=0x3435e412;
*((unsigned int *)((unsigned long)context_ptr+0x00006118+4*1))=0x000000ac;
*((unsigned int *)((unsigned long)context_ptr+0x00003060))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003060+4*1))=0x00006120;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000060))=0x04c00005;
*((unsigned int *)((unsigned long)context_ptr+0x00000060+4*1))=0x00006118;
*((unsigned int *)((unsigned long)context_ptr+0x00000060+4*2))=0x00006108;
*((unsigned int *)((unsigned long)context_ptr+0x00000060+4*3))=0x02220005;
*((unsigned int *)((unsigned long)context_ptr+0x00000060+4*4))=0x001d6d90;
*((unsigned int *)((unsigned long)context_ptr+0x00000060+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x0000613c))=0x026a1002;
*((unsigned int *)((unsigned long)context_ptr+0x0000613c+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x0000613c+4*2))=0x02020006;
*((unsigned int *)((unsigned long)context_ptr+0x0000613c+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x0000614c))=0xbd8c6b12;
*((unsigned int *)((unsigned long)context_ptr+0x0000614c+4*1))=0x00006c24;
*((unsigned int *)((unsigned long)context_ptr+0x00003078))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003078+4*1))=0x00006154;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000078))=0x04c00006;
*((unsigned int *)((unsigned long)context_ptr+0x00000078+4*1))=0x0000614c;
*((unsigned int *)((unsigned long)context_ptr+0x00000078+4*2))=0x0000613c;
*((unsigned int *)((unsigned long)context_ptr+0x00000078+4*3))=0x02220006;
*((unsigned int *)((unsigned long)context_ptr+0x00000078+4*4))=0x071df24c;
*((unsigned int *)((unsigned long)context_ptr+0x00000078+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x00006170))=0x026a1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006170+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006170+4*2))=0x02020007;
*((unsigned int *)((unsigned long)context_ptr+0x00006170+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x00006180))=0xb4278ba1;
*((unsigned int *)((unsigned long)context_ptr+0x00006180+4*1))=0x00c2ad78;
*((unsigned int *)((unsigned long)context_ptr+0x00003090))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003090+4*1))=0x00006188;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000090))=0x04c00007;
*((unsigned int *)((unsigned long)context_ptr+0x00000090+4*1))=0x00006180;
*((unsigned int *)((unsigned long)context_ptr+0x00000090+4*2))=0x00006170;
*((unsigned int *)((unsigned long)context_ptr+0x00000090+4*3))=0x02220007;
*((unsigned int *)((unsigned long)context_ptr+0x00000090+4*4))=0x047b3df4;
*((unsigned int *)((unsigned long)context_ptr+0x00000090+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x000061a4))=0x026a1002;
*((unsigned int *)((unsigned long)context_ptr+0x000061a4+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000061a4+4*2))=0x02020008;
*((unsigned int *)((unsigned long)context_ptr+0x000061a4+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x000061b4))=0x61b228a0;
*((unsigned int *)((unsigned long)context_ptr+0x000061b4+4*1))=0x5aab2397;
*((unsigned int *)((unsigned long)context_ptr+0x000030a8))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x000030a8+4*1))=0x000061bc;
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
*((unsigned int *)((unsigned long)context_ptr+0x000000a8))=0x04c00008;
*((unsigned int *)((unsigned long)context_ptr+0x000000a8+4*1))=0x000061b4;
*((unsigned int *)((unsigned long)context_ptr+0x000000a8+4*2))=0x000061a4;
*((unsigned int *)((unsigned long)context_ptr+0x000000a8+4*3))=0x02220008;
*((unsigned int *)((unsigned long)context_ptr+0x000000a8+4*4))=0x07a0a02a;
*((unsigned int *)((unsigned long)context_ptr+0x000000a8+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x000061d8))=0x026a1002;
*((unsigned int *)((unsigned long)context_ptr+0x000061d8+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000061d8+4*2))=0x02020009;
*((unsigned int *)((unsigned long)context_ptr+0x000061d8+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x000061e8))=0xe92186b5;
*((unsigned int *)((unsigned long)context_ptr+0x000061e8+4*1))=0xce63ca71;
*((unsigned int *)((unsigned long)context_ptr+0x000061e8+4*2))=0x00000063;
*((unsigned int *)((unsigned long)context_ptr+0x000030c0))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x000030c0+4*1))=0x000061f4;
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
*((unsigned int *)((unsigned long)context_ptr+0x000000c0+4*1))=0x000061e8;
*((unsigned int *)((unsigned long)context_ptr+0x000000c0+4*2))=0x000061d8;
*((unsigned int *)((unsigned long)context_ptr+0x000000c0+4*3))=0x02220009;
*((unsigned int *)((unsigned long)context_ptr+0x000000c0+4*4))=0x0f0a61c3;
*((unsigned int *)((unsigned long)context_ptr+0x000000c0+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x00006210))=0x026a1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006210+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006210+4*2))=0x0202000a;
*((unsigned int *)((unsigned long)context_ptr+0x00006210+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x00006220))=0x1a5674eb;
*((unsigned int *)((unsigned long)context_ptr+0x00006220+4*1))=0x7452cbe2;
*((unsigned int *)((unsigned long)context_ptr+0x00006220+4*2))=0x00000753;
*((unsigned int *)((unsigned long)context_ptr+0x000030d8))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x000030d8+4*1))=0x0000622c;
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
*((unsigned int *)((unsigned long)context_ptr+0x000000d8))=0x04c0000a;
*((unsigned int *)((unsigned long)context_ptr+0x000000d8+4*1))=0x00006220;
*((unsigned int *)((unsigned long)context_ptr+0x000000d8+4*2))=0x00006210;
*((unsigned int *)((unsigned long)context_ptr+0x000000d8+4*3))=0x0222000a;
*((unsigned int *)((unsigned long)context_ptr+0x000000d8+4*4))=0x035a7c6f;
*((unsigned int *)((unsigned long)context_ptr+0x000000d8+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x00006248))=0x026a1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006248+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006248+4*2))=0x0202000b;
*((unsigned int *)((unsigned long)context_ptr+0x00006248+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x00006258))=0x338a498e;
*((unsigned int *)((unsigned long)context_ptr+0x00006258+4*1))=0x899a714b;
*((unsigned int *)((unsigned long)context_ptr+0x00006258+4*2))=0x001e3b42;
*((unsigned int *)((unsigned long)context_ptr+0x000030f0))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x000030f0+4*1))=0x00006264;
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
*((unsigned int *)((unsigned long)context_ptr+0x000000f0))=0x04c0000b;
*((unsigned int *)((unsigned long)context_ptr+0x000000f0+4*1))=0x00006258;
*((unsigned int *)((unsigned long)context_ptr+0x000000f0+4*2))=0x00006248;
*((unsigned int *)((unsigned long)context_ptr+0x000000f0+4*3))=0x0222000b;
*((unsigned int *)((unsigned long)context_ptr+0x000000f0+4*4))=0x0bb9e5a0;
*((unsigned int *)((unsigned long)context_ptr+0x000000f0+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x00006280))=0x026a1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006280+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006280+4*2))=0x0202000c;
*((unsigned int *)((unsigned long)context_ptr+0x00006280+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x00006290))=0xc2d0bb36;
*((unsigned int *)((unsigned long)context_ptr+0x00006290+4*1))=0xe6a1975a;
*((unsigned int *)((unsigned long)context_ptr+0x00006290+4*2))=0x5b86d51b;
*((unsigned int *)((unsigned long)context_ptr+0x00003108))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003108+4*1))=0x0000629c;
*((unsigned int *)((unsigned long)context_ptr+0x00003108+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003108+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003108+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003108+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000108))=0x04c0000c;
*((unsigned int *)((unsigned long)context_ptr+0x00000108+4*1))=0x00006290;
*((unsigned int *)((unsigned long)context_ptr+0x00000108+4*2))=0x00006280;
*((unsigned int *)((unsigned long)context_ptr+0x00000108+4*3))=0x0222000c;
*((unsigned int *)((unsigned long)context_ptr+0x00000108+4*4))=0x03856be2;
*((unsigned int *)((unsigned long)context_ptr+0x00000108+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x000062b8))=0x026a1002;
*((unsigned int *)((unsigned long)context_ptr+0x000062b8+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000062b8+4*2))=0x0202000d;
*((unsigned int *)((unsigned long)context_ptr+0x000062b8+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x000062c8))=0x542d5b6f;
*((unsigned int *)((unsigned long)context_ptr+0x000062c8+4*1))=0x6861bffc;
*((unsigned int *)((unsigned long)context_ptr+0x000062c8+4*2))=0xafbc8843;
*((unsigned int *)((unsigned long)context_ptr+0x000062c8+4*3))=0x00000076;
*((unsigned int *)((unsigned long)context_ptr+0x00003120))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003120+4*1))=0x000062d8;
*((unsigned int *)((unsigned long)context_ptr+0x00003120+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003120+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003120+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003120+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000120))=0x04c0000d;
*((unsigned int *)((unsigned long)context_ptr+0x00000120+4*1))=0x000062c8;
*((unsigned int *)((unsigned long)context_ptr+0x00000120+4*2))=0x000062b8;
*((unsigned int *)((unsigned long)context_ptr+0x00000120+4*3))=0x0222000d;
*((unsigned int *)((unsigned long)context_ptr+0x00000120+4*4))=0x068afe2b;
*((unsigned int *)((unsigned long)context_ptr+0x00000120+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x000062f4))=0x026a1002;
*((unsigned int *)((unsigned long)context_ptr+0x000062f4+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000062f4+4*2))=0x0202000e;
*((unsigned int *)((unsigned long)context_ptr+0x000062f4+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x00006304))=0xc5fa8ce6;
*((unsigned int *)((unsigned long)context_ptr+0x00006304+4*1))=0x74af4392;
*((unsigned int *)((unsigned long)context_ptr+0x00006304+4*2))=0x057e67b8;
*((unsigned int *)((unsigned long)context_ptr+0x00006304+4*3))=0x000008bd;
*((unsigned int *)((unsigned long)context_ptr+0x00003138))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003138+4*1))=0x00006314;
*((unsigned int *)((unsigned long)context_ptr+0x00003138+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003138+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003138+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003138+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000138))=0x04c0000e;
*((unsigned int *)((unsigned long)context_ptr+0x00000138+4*1))=0x00006304;
*((unsigned int *)((unsigned long)context_ptr+0x00000138+4*2))=0x000062f4;
*((unsigned int *)((unsigned long)context_ptr+0x00000138+4*3))=0x0222000e;
*((unsigned int *)((unsigned long)context_ptr+0x00000138+4*4))=0x0c6a2895;
*((unsigned int *)((unsigned long)context_ptr+0x00000138+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x00006330))=0x026a1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006330+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006330+4*2))=0x0202000f;
*((unsigned int *)((unsigned long)context_ptr+0x00006330+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x00006340))=0x2cf36c8c;
*((unsigned int *)((unsigned long)context_ptr+0x00006340+4*1))=0x1c28a82b;
*((unsigned int *)((unsigned long)context_ptr+0x00006340+4*2))=0xc19acb81;
*((unsigned int *)((unsigned long)context_ptr+0x00006340+4*3))=0x006d4844;
*((unsigned int *)((unsigned long)context_ptr+0x00003150))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003150+4*1))=0x00006350;
*((unsigned int *)((unsigned long)context_ptr+0x00003150+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003150+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003150+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003150+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000150))=0x04c0000f;
*((unsigned int *)((unsigned long)context_ptr+0x00000150+4*1))=0x00006340;
*((unsigned int *)((unsigned long)context_ptr+0x00000150+4*2))=0x00006330;
*((unsigned int *)((unsigned long)context_ptr+0x00000150+4*3))=0x0222000f;
*((unsigned int *)((unsigned long)context_ptr+0x00000150+4*4))=0x0f23db2f;
*((unsigned int *)((unsigned long)context_ptr+0x00000150+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000006&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x0000605c,"\xac\x02\x8d\x7a\x9b\xaa\xa8\x23\xf1\x0e\x51\x65\xa3\xdb\x57\x72\xa8\x0f\xa0\x2c\xa4\x52\xeb\xc1\xe6\xf6\xa5\xec",28))
printf("strip: ac028d7a9baaa823, Pass\n");
else
printf("strip: ac028d7a9baaa823, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006048))=0x026a1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006048+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006048+4*2))=0x02020010;
*((unsigned int *)((unsigned long)context_ptr+0x00006048+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x00006058))=0xe140f0a2;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*1))=0x07179cc6;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*2))=0x62c34002;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*3))=0xe163a0c6;
*((unsigned int *)((unsigned long)context_ptr+0x00003168))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003168+4*1))=0x0000636c;
*((unsigned int *)((unsigned long)context_ptr+0x00003168+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003168+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003168+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003168+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000168))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00000168+4*1))=0x00006058;
*((unsigned int *)((unsigned long)context_ptr+0x00000168+4*2))=0x00006048;
*((unsigned int *)((unsigned long)context_ptr+0x00000168+4*3))=0x02220010;
*((unsigned int *)((unsigned long)context_ptr+0x00000168+4*4))=0x0d47133e;
*((unsigned int *)((unsigned long)context_ptr+0x00000168+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000000c&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x0000608c,"\x47\xbf\xff\x21\xe3\x3b\x7c\x2a\x3e\xc7\x7c\x87\x42\xbc\xa7\x49\x96\x17\x52\xbc\xb8\xda\xfe\xd8\x5c\x1c\xf0\xd2",28))
printf("strip: 47bfff21e33b7c2a, Pass\n");
else
printf("strip: 47bfff21e33b7c2a, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006068))=0x026a1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006068+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006068+4*2))=0x02020011;
*((unsigned int *)((unsigned long)context_ptr+0x00006068+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x00006078))=0x40b34233;
*((unsigned int *)((unsigned long)context_ptr+0x00006078+4*1))=0x27ffef42;
*((unsigned int *)((unsigned long)context_ptr+0x00006078+4*2))=0x95098de6;
*((unsigned int *)((unsigned long)context_ptr+0x00006078+4*3))=0xd1c108a4;
*((unsigned int *)((unsigned long)context_ptr+0x00006078+4*4))=0x00000012;
*((unsigned int *)((unsigned long)context_ptr+0x00003180))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003180+4*1))=0x0000608c;
*((unsigned int *)((unsigned long)context_ptr+0x00003180+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003180+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003180+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003180+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000180))=0x04c00011;
*((unsigned int *)((unsigned long)context_ptr+0x00000180+4*1))=0x00006078;
*((unsigned int *)((unsigned long)context_ptr+0x00000180+4*2))=0x00006068;
*((unsigned int *)((unsigned long)context_ptr+0x00000180+4*3))=0x02220011;
*((unsigned int *)((unsigned long)context_ptr+0x00000180+4*4))=0x03d1cd69;
*((unsigned int *)((unsigned long)context_ptr+0x00000180+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000012&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000060bc,"\x93\xe3\x20\xde\xba\x38\x9f\x5f\x7c\xae\xa6\xad\xf5\x75\x97\x51\xb4\x51\xfb\xaa\xb7\x61\x26\xab\xbb\x24\x5b\xfa",28))
printf("strip: 93e320deba389f5f, Pass\n");
else
printf("strip: 93e320deba389f5f, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000060a8))=0x026a1002;
*((unsigned int *)((unsigned long)context_ptr+0x000060a8+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000060a8+4*2))=0x02020012;
*((unsigned int *)((unsigned long)context_ptr+0x000060a8+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x000060b8))=0x1f5b6330;
*((unsigned int *)((unsigned long)context_ptr+0x000060b8+4*1))=0xa79d2d59;
*((unsigned int *)((unsigned long)context_ptr+0x000060b8+4*2))=0xdf8d7403;
*((unsigned int *)((unsigned long)context_ptr+0x000060b8+4*3))=0xdc0d147e;
*((unsigned int *)((unsigned long)context_ptr+0x000060b8+4*4))=0x0000dbca;
*((unsigned int *)((unsigned long)context_ptr+0x00003198))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003198+4*1))=0x00006388;
*((unsigned int *)((unsigned long)context_ptr+0x00003198+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003198+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003198+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003198+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000198))=0x04c00012;
*((unsigned int *)((unsigned long)context_ptr+0x00000198+4*1))=0x000060b8;
*((unsigned int *)((unsigned long)context_ptr+0x00000198+4*2))=0x000060a8;
*((unsigned int *)((unsigned long)context_ptr+0x00000198+4*3))=0x02220012;
*((unsigned int *)((unsigned long)context_ptr+0x00000198+4*4))=0x01880fa5;
*((unsigned int *)((unsigned long)context_ptr+0x00000198+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000060ec,"\xf4\xe6\xb3\x71\xaf\xd8\x33\x60\x29\x10\xa7\x4d\x5e\x26\x56\x9e\x4a\x73\x50\x04\x72\xcc\xb8\xe5\xa2\xaf\x6e\xd8",28))
printf("strip: f4e6b371afd83360, Pass\n");
else
printf("strip: f4e6b371afd83360, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000060cc))=0x026a1002;
*((unsigned int *)((unsigned long)context_ptr+0x000060cc+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000060cc+4*2))=0x02020013;
*((unsigned int *)((unsigned long)context_ptr+0x000060cc+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x000060dc))=0x61acc79c;
*((unsigned int *)((unsigned long)context_ptr+0x000060dc+4*1))=0x55e96f06;
*((unsigned int *)((unsigned long)context_ptr+0x000060dc+4*2))=0x8882233f;
*((unsigned int *)((unsigned long)context_ptr+0x000060dc+4*3))=0xf7a86812;
*((unsigned int *)((unsigned long)context_ptr+0x000060dc+4*4))=0x00786f6e;
*((unsigned int *)((unsigned long)context_ptr+0x000031b0))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x000031b0+4*1))=0x000063a4;
*((unsigned int *)((unsigned long)context_ptr+0x000031b0+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000031b0+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000031b0+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000031b0+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x000001b0))=0x04c00013;
*((unsigned int *)((unsigned long)context_ptr+0x000001b0+4*1))=0x000060dc;
*((unsigned int *)((unsigned long)context_ptr+0x000001b0+4*2))=0x000060cc;
*((unsigned int *)((unsigned long)context_ptr+0x000001b0+4*3))=0x02220013;
*((unsigned int *)((unsigned long)context_ptr+0x000001b0+4*4))=0x0a53011a;
*((unsigned int *)((unsigned long)context_ptr+0x000001b0+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000001e&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006120,"\xc3\xc6\xb0\x3f\x3a\xda\x0c\x5a\x2c\x0c\x35\x58\x0a\x7b\x18\xfc\xaa\xa9\x52\x6e\x87\x73\x13\x5c\xac\xfb\xf2\xb4",28))
printf("strip: c3c6b03f3ada0c5a, Pass\n");
else
printf("strip: c3c6b03f3ada0c5a, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000060f0))=0x026a1002;
*((unsigned int *)((unsigned long)context_ptr+0x000060f0+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000060f0+4*2))=0x02020014;
*((unsigned int *)((unsigned long)context_ptr+0x000060f0+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x00006100))=0x2158ba44;
*((unsigned int *)((unsigned long)context_ptr+0x00006100+4*1))=0x656e2a9c;
*((unsigned int *)((unsigned long)context_ptr+0x00006100+4*2))=0xc7aeb513;
*((unsigned int *)((unsigned long)context_ptr+0x00006100+4*3))=0x352b8d8b;
*((unsigned int *)((unsigned long)context_ptr+0x00006100+4*4))=0x5bd1863a;
*((unsigned int *)((unsigned long)context_ptr+0x000031c8))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x000031c8+4*1))=0x00006114;
*((unsigned int *)((unsigned long)context_ptr+0x000031c8+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000031c8+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000031c8+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000031c8+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x000001c8))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x000001c8+4*1))=0x00006100;
*((unsigned int *)((unsigned long)context_ptr+0x000001c8+4*2))=0x000060f0;
*((unsigned int *)((unsigned long)context_ptr+0x000001c8+4*3))=0x02220014;
*((unsigned int *)((unsigned long)context_ptr+0x000001c8+4*4))=0x0b769146;
*((unsigned int *)((unsigned long)context_ptr+0x000001c8+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000024&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006154,"\x99\x78\xf1\x22\xed\x2d\x4a\x4d\xb2\x21\x2c\xdd\x03\xbd\x96\x77\x51\x45\xc5\x68\x52\xf7\x5c\xdc\xdf\xd2\x4d\xbd",28))
printf("strip: 9978f122ed2d4a4d, Pass\n");
else
printf("strip: 9978f122ed2d4a4d, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006130))=0x026a1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006130+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006130+4*2))=0x02020015;
*((unsigned int *)((unsigned long)context_ptr+0x00006130+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x00006140))=0x8fecc67c;
*((unsigned int *)((unsigned long)context_ptr+0x00006140+4*1))=0xebdb13d3;
*((unsigned int *)((unsigned long)context_ptr+0x00006140+4*2))=0xe0d9d32b;
*((unsigned int *)((unsigned long)context_ptr+0x00006140+4*3))=0xb5359b84;
*((unsigned int *)((unsigned long)context_ptr+0x00006140+4*4))=0x63220567;
*((unsigned int *)((unsigned long)context_ptr+0x00006140+4*5))=0x000000e2;
*((unsigned int *)((unsigned long)context_ptr+0x000031e0))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x000031e0+4*1))=0x000063c0;
*((unsigned int *)((unsigned long)context_ptr+0x000031e0+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000031e0+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000031e0+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000031e0+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x000001e0))=0x04c00015;
*((unsigned int *)((unsigned long)context_ptr+0x000001e0+4*1))=0x00006140;
*((unsigned int *)((unsigned long)context_ptr+0x000001e0+4*2))=0x00006130;
*((unsigned int *)((unsigned long)context_ptr+0x000001e0+4*3))=0x02220015;
*((unsigned int *)((unsigned long)context_ptr+0x000001e0+4*4))=0x0edf2a72;
*((unsigned int *)((unsigned long)context_ptr+0x000001e0+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000002a&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006188,"\xf0\xef\x49\x65\x30\x4b\x01\xe3\x2a\xb8\x8c\x9d\x67\x65\x8f\x07\x6f\x83\x67\xa3\x59\xb3\x88\xfb\x39\x87\x09\x3c",28))
printf("strip: f0ef4965304b01e3, Pass\n");
else
printf("strip: f0ef4965304b01e3, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006158))=0x026a1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006158+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006158+4*2))=0x02020016;
*((unsigned int *)((unsigned long)context_ptr+0x00006158+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x00006168))=0x135782f2;
*((unsigned int *)((unsigned long)context_ptr+0x00006168+4*1))=0x615e3992;
*((unsigned int *)((unsigned long)context_ptr+0x00006168+4*2))=0xbeef3bc2;
*((unsigned int *)((unsigned long)context_ptr+0x00006168+4*3))=0x625be17b;
*((unsigned int *)((unsigned long)context_ptr+0x00006168+4*4))=0x8066c721;
*((unsigned int *)((unsigned long)context_ptr+0x00006168+4*5))=0x0000a778;
*((unsigned int *)((unsigned long)context_ptr+0x000031f8))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x000031f8+4*1))=0x00006180;
*((unsigned int *)((unsigned long)context_ptr+0x000031f8+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000031f8+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000031f8+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000031f8+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x000001f8))=0x04c00016;
*((unsigned int *)((unsigned long)context_ptr+0x000001f8+4*1))=0x00006168;
*((unsigned int *)((unsigned long)context_ptr+0x000001f8+4*2))=0x00006158;
*((unsigned int *)((unsigned long)context_ptr+0x000001f8+4*3))=0x02220016;
*((unsigned int *)((unsigned long)context_ptr+0x000001f8+4*4))=0x06e92750;
*((unsigned int *)((unsigned long)context_ptr+0x000001f8+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000030&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000061bc,"\xed\x1f\x0a\xe6\x93\x3f\x33\x3b\x13\x9f\xae\xda\x65\x59\x94\xc3\x2d\x6a\x3f\xb8\x46\x74\x4d\x8c\x52\x5c\xdc\x11",28))
printf("strip: ed1f0ae6933f333b, Pass\n");
else
printf("strip: ed1f0ae6933f333b, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x0000619c))=0x026a1002;
*((unsigned int *)((unsigned long)context_ptr+0x0000619c+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x0000619c+4*2))=0x02020017;
*((unsigned int *)((unsigned long)context_ptr+0x0000619c+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x000061ac))=0x11d8e500;
*((unsigned int *)((unsigned long)context_ptr+0x000061ac+4*1))=0x61ed3b2d;
*((unsigned int *)((unsigned long)context_ptr+0x000061ac+4*2))=0xc3616fce;
*((unsigned int *)((unsigned long)context_ptr+0x000061ac+4*3))=0xb495449d;
*((unsigned int *)((unsigned long)context_ptr+0x000061ac+4*4))=0x98a4add3;
*((unsigned int *)((unsigned long)context_ptr+0x000061ac+4*5))=0x00b6f117;
*((unsigned int *)((unsigned long)context_ptr+0x00003210))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003210+4*1))=0x000063dc;
*((unsigned int *)((unsigned long)context_ptr+0x00003210+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003210+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003210+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003210+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000210))=0x04c00017;
*((unsigned int *)((unsigned long)context_ptr+0x00000210+4*1))=0x000061ac;
*((unsigned int *)((unsigned long)context_ptr+0x00000210+4*2))=0x0000619c;
*((unsigned int *)((unsigned long)context_ptr+0x00000210+4*3))=0x02220017;
*((unsigned int *)((unsigned long)context_ptr+0x00000210+4*4))=0x09eede42;
*((unsigned int *)((unsigned long)context_ptr+0x00000210+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000036&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000061f4,"\xad\xf4\x58\xea\xa4\x75\x0e\xb9\xd4\x2d\x30\xf3\x9f\xdf\xd9\x8a\x29\x58\x56\x82\xc6\x88\x5a\x4a\x3d\x39\xbf\x9f",28))
printf("strip: adf458eaa4750eb9, Pass\n");
else
printf("strip: adf458eaa4750eb9, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000061c4))=0x026a1002;
*((unsigned int *)((unsigned long)context_ptr+0x000061c4+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000061c4+4*2))=0x02020018;
*((unsigned int *)((unsigned long)context_ptr+0x000061c4+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x000061d4))=0xc9643169;
*((unsigned int *)((unsigned long)context_ptr+0x000061d4+4*1))=0xaee3f6cd;
*((unsigned int *)((unsigned long)context_ptr+0x000061d4+4*2))=0xec2eb985;
*((unsigned int *)((unsigned long)context_ptr+0x000061d4+4*3))=0xa26f98b6;
*((unsigned int *)((unsigned long)context_ptr+0x000061d4+4*4))=0x3692e69e;
*((unsigned int *)((unsigned long)context_ptr+0x000061d4+4*5))=0xd7e73e70;
*((unsigned int *)((unsigned long)context_ptr+0x00003228))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003228+4*1))=0x000061ec;
*((unsigned int *)((unsigned long)context_ptr+0x00003228+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003228+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003228+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003228+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000228))=0x04c00018;
*((unsigned int *)((unsigned long)context_ptr+0x00000228+4*1))=0x000061d4;
*((unsigned int *)((unsigned long)context_ptr+0x00000228+4*2))=0x000061c4;
*((unsigned int *)((unsigned long)context_ptr+0x00000228+4*3))=0x02220018;
*((unsigned int *)((unsigned long)context_ptr+0x00000228+4*4))=0x00b2591c;
*((unsigned int *)((unsigned long)context_ptr+0x00000228+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000003c&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x0000622c,"\xf8\xfb\x83\x38\x95\xf2\x42\xcd\x0a\xd4\x40\x33\x1d\xf2\xde\x3d\x74\x96\x5b\xe1\xb4\x15\x1b\x24\x27\xa9\xa6\xde",28))
printf("strip: f8fb833895f242cd, Pass\n");
else
printf("strip: f8fb833895f242cd, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006208))=0x026a1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006208+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006208+4*2))=0x02020019;
*((unsigned int *)((unsigned long)context_ptr+0x00006208+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x00006218))=0x07f73dc4;
*((unsigned int *)((unsigned long)context_ptr+0x00006218+4*1))=0x422783dd;
*((unsigned int *)((unsigned long)context_ptr+0x00006218+4*2))=0x38d64797;
*((unsigned int *)((unsigned long)context_ptr+0x00006218+4*3))=0xd2568162;
*((unsigned int *)((unsigned long)context_ptr+0x00006218+4*4))=0xa0271643;
*((unsigned int *)((unsigned long)context_ptr+0x00006218+4*5))=0x7afe1090;
*((unsigned int *)((unsigned long)context_ptr+0x00006218+4*6))=0x00000051;
*((unsigned int *)((unsigned long)context_ptr+0x00003240))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003240+4*1))=0x000063f8;
*((unsigned int *)((unsigned long)context_ptr+0x00003240+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003240+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003240+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003240+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000240))=0x04c00019;
*((unsigned int *)((unsigned long)context_ptr+0x00000240+4*1))=0x00006218;
*((unsigned int *)((unsigned long)context_ptr+0x00000240+4*2))=0x00006208;
*((unsigned int *)((unsigned long)context_ptr+0x00000240+4*3))=0x02220019;
*((unsigned int *)((unsigned long)context_ptr+0x00000240+4*4))=0x06f2af3a;
*((unsigned int *)((unsigned long)context_ptr+0x00000240+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000042&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006264,"\xd1\x4a\x26\xab\xc4\x0a\xef\x43\x6e\x82\x36\xad\x1e\x61\x49\xaa\xb2\xb8\x66\xe2\xea\xb9\xa2\x28\x8d\x9b\x13\x5b",28))
printf("strip: d14a26abc40aef43, Pass\n");
else
printf("strip: d14a26abc40aef43, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006234))=0x026a1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006234+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006234+4*2))=0x0202001a;
*((unsigned int *)((unsigned long)context_ptr+0x00006234+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x00006244))=0x15c5aa46;
*((unsigned int *)((unsigned long)context_ptr+0x00006244+4*1))=0xf3b44ed1;
*((unsigned int *)((unsigned long)context_ptr+0x00006244+4*2))=0x1d4a9c08;
*((unsigned int *)((unsigned long)context_ptr+0x00006244+4*3))=0x5883fab6;
*((unsigned int *)((unsigned long)context_ptr+0x00006244+4*4))=0x68886a72;
*((unsigned int *)((unsigned long)context_ptr+0x00006244+4*5))=0x2cfffa14;
*((unsigned int *)((unsigned long)context_ptr+0x00006244+4*6))=0x00006f3d;
*((unsigned int *)((unsigned long)context_ptr+0x00003258))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003258+4*1))=0x00006260;
*((unsigned int *)((unsigned long)context_ptr+0x00003258+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003258+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003258+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003258+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000258))=0x04c0001a;
*((unsigned int *)((unsigned long)context_ptr+0x00000258+4*1))=0x00006244;
*((unsigned int *)((unsigned long)context_ptr+0x00000258+4*2))=0x00006234;
*((unsigned int *)((unsigned long)context_ptr+0x00000258+4*3))=0x0222001a;
*((unsigned int *)((unsigned long)context_ptr+0x00000258+4*4))=0x0d5e32ad;
*((unsigned int *)((unsigned long)context_ptr+0x00000258+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000048&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x0000629c,"\xc0\x6c\xbd\x6d\xf4\xc3\x6d\x9a\xe1\xd2\x81\x01\x5f\xb7\xf2\x80\xba\x9f\xa9\x92\xd5\x2b\x3f\xd9\x4f\x62\xe4\x15",28))
printf("strip: c06cbd6df4c36d9a, Pass\n");
else
printf("strip: c06cbd6df4c36d9a, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x0000627c))=0x026a1002;
*((unsigned int *)((unsigned long)context_ptr+0x0000627c+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x0000627c+4*2))=0x0202001b;
*((unsigned int *)((unsigned long)context_ptr+0x0000627c+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x0000628c))=0x3ef1e26a;
*((unsigned int *)((unsigned long)context_ptr+0x0000628c+4*1))=0x2b94e18f;
*((unsigned int *)((unsigned long)context_ptr+0x0000628c+4*2))=0xde4cfc3f;
*((unsigned int *)((unsigned long)context_ptr+0x0000628c+4*3))=0xcab8bdcb;
*((unsigned int *)((unsigned long)context_ptr+0x0000628c+4*4))=0x812a0fd8;
*((unsigned int *)((unsigned long)context_ptr+0x0000628c+4*5))=0x207e8836;
*((unsigned int *)((unsigned long)context_ptr+0x0000628c+4*6))=0x00d30216;
*((unsigned int *)((unsigned long)context_ptr+0x00003270))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003270+4*1))=0x00006414;
*((unsigned int *)((unsigned long)context_ptr+0x00003270+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003270+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003270+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003270+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000270))=0x04c0001b;
*((unsigned int *)((unsigned long)context_ptr+0x00000270+4*1))=0x0000628c;
*((unsigned int *)((unsigned long)context_ptr+0x00000270+4*2))=0x0000627c;
*((unsigned int *)((unsigned long)context_ptr+0x00000270+4*3))=0x0222001b;
*((unsigned int *)((unsigned long)context_ptr+0x00000270+4*4))=0x0fbdc677;
*((unsigned int *)((unsigned long)context_ptr+0x00000270+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000004e&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000062d8,"\xe8\x71\x36\x35\xb8\x67\x1a\x64\x0a\x16\xd7\x09\x41\xa5\xa5\x62\xf2\x1e\x26\xbd\xf7\xad\xad\x11\x24\x66\x2a\xbe",28))
printf("strip: e8713635b8671a64, Pass\n");
else
printf("strip: e8713635b8671a64, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000062a8))=0x026a1002;
*((unsigned int *)((unsigned long)context_ptr+0x000062a8+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000062a8+4*2))=0x0202001c;
*((unsigned int *)((unsigned long)context_ptr+0x000062a8+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x000062b8))=0x81c7e684;
*((unsigned int *)((unsigned long)context_ptr+0x000062b8+4*1))=0x6e5779d3;
*((unsigned int *)((unsigned long)context_ptr+0x000062b8+4*2))=0xba0da674;
*((unsigned int *)((unsigned long)context_ptr+0x000062b8+4*3))=0x331175f7;
*((unsigned int *)((unsigned long)context_ptr+0x000062b8+4*4))=0x00cb411a;
*((unsigned int *)((unsigned long)context_ptr+0x000062b8+4*5))=0x2c2ff0df;
*((unsigned int *)((unsigned long)context_ptr+0x000062b8+4*6))=0x02cf5cf7;
*((unsigned int *)((unsigned long)context_ptr+0x00003288))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003288+4*1))=0x000062d4;
*((unsigned int *)((unsigned long)context_ptr+0x00003288+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003288+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003288+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003288+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000288))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00000288+4*1))=0x000062b8;
*((unsigned int *)((unsigned long)context_ptr+0x00000288+4*2))=0x000062a8;
*((unsigned int *)((unsigned long)context_ptr+0x00000288+4*3))=0x0222001c;
*((unsigned int *)((unsigned long)context_ptr+0x00000288+4*4))=0x09b89bf1;
*((unsigned int *)((unsigned long)context_ptr+0x00000288+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000054&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006314,"\x42\x09\x85\x71\x13\x02\x26\x6d\x15\x64\xcc\x37\x46\xcc\x29\x3f\xdd\xf9\x31\x55\xbb\xf2\x2b\x5c\xe1\x05\x87\x7a",28))
printf("strip: 420985711302266d, Pass\n");
else
printf("strip: 420985711302266d, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000062f0))=0x026a1002;
*((unsigned int *)((unsigned long)context_ptr+0x000062f0+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000062f0+4*2))=0x0202001d;
*((unsigned int *)((unsigned long)context_ptr+0x000062f0+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x00006300))=0xafc4ec28;
*((unsigned int *)((unsigned long)context_ptr+0x00006300+4*1))=0xc51cc6d0;
*((unsigned int *)((unsigned long)context_ptr+0x00006300+4*2))=0xaf7bbfd6;
*((unsigned int *)((unsigned long)context_ptr+0x00006300+4*3))=0xc843c319;
*((unsigned int *)((unsigned long)context_ptr+0x00006300+4*4))=0x138982a2;
*((unsigned int *)((unsigned long)context_ptr+0x00006300+4*5))=0x23c6030a;
*((unsigned int *)((unsigned long)context_ptr+0x00006300+4*6))=0xe2fa621f;
*((unsigned int *)((unsigned long)context_ptr+0x00006300+4*7))=0x00000050;
*((unsigned int *)((unsigned long)context_ptr+0x000032a0))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x000032a0+4*1))=0x00006430;
*((unsigned int *)((unsigned long)context_ptr+0x000032a0+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000032a0+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000032a0+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000032a0+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x000002a0))=0x04c0001d;
*((unsigned int *)((unsigned long)context_ptr+0x000002a0+4*1))=0x00006300;
*((unsigned int *)((unsigned long)context_ptr+0x000002a0+4*2))=0x000062f0;
*((unsigned int *)((unsigned long)context_ptr+0x000002a0+4*3))=0x0222001d;
*((unsigned int *)((unsigned long)context_ptr+0x000002a0+4*4))=0x0645cc16;
*((unsigned int *)((unsigned long)context_ptr+0x000002a0+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000005a&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006350,"\xc4\xd6\xbd\x69\x55\x3b\xa1\x79\x9e\xd4\x9a\xcc\xf4\xd4\xd2\x84\x6b\x5f\x3d\xf7\xd8\xb1\x06\x39\x7a\xbb\xe8\xe1",28))
printf("strip: c4d6bd69553ba179, Pass\n");
else
printf("strip: c4d6bd69553ba179, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006320))=0x026a1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006320+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006320+4*2))=0x0202001e;
*((unsigned int *)((unsigned long)context_ptr+0x00006320+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x00006330))=0x82d4a438;
*((unsigned int *)((unsigned long)context_ptr+0x00006330+4*1))=0x62271225;
*((unsigned int *)((unsigned long)context_ptr+0x00006330+4*2))=0x9086aa90;
*((unsigned int *)((unsigned long)context_ptr+0x00006330+4*3))=0x66baaa5a;
*((unsigned int *)((unsigned long)context_ptr+0x00006330+4*4))=0x77e7bed0;
*((unsigned int *)((unsigned long)context_ptr+0x00006330+4*5))=0x6209c658;
*((unsigned int *)((unsigned long)context_ptr+0x00006330+4*6))=0x3f8357fa;
*((unsigned int *)((unsigned long)context_ptr+0x00006330+4*7))=0x00001c13;
*((unsigned int *)((unsigned long)context_ptr+0x000032b8))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x000032b8+4*1))=0x00006350;
*((unsigned int *)((unsigned long)context_ptr+0x000032b8+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000032b8+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000032b8+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000032b8+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x000002b8))=0x04c0001e;
*((unsigned int *)((unsigned long)context_ptr+0x000002b8+4*1))=0x00006330;
*((unsigned int *)((unsigned long)context_ptr+0x000002b8+4*2))=0x00006320;
*((unsigned int *)((unsigned long)context_ptr+0x000002b8+4*3))=0x0222001e;
*((unsigned int *)((unsigned long)context_ptr+0x000002b8+4*4))=0x08bb62ad;
*((unsigned int *)((unsigned long)context_ptr+0x000002b8+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000060&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x0000636c,"\x47\x25\xce\x20\xda\xce\x4b\x4f\xb4\x67\x24\x6f\x16\x56\x4d\xfd\x6e\x64\x4d\x28\xf9\x98\xac\xe9\xbe\x7b\x85\xf4",28))
printf("strip: 4725ce20dace4b4f, Pass\n");
else
printf("strip: 4725ce20dace4b4f, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006058))=0x026a1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*2))=0x0202001f;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x0000644c))=0xec1db589;
*((unsigned int *)((unsigned long)context_ptr+0x0000644c+4*1))=0x9a99b17a;
*((unsigned int *)((unsigned long)context_ptr+0x0000644c+4*2))=0x357f16b5;
*((unsigned int *)((unsigned long)context_ptr+0x0000644c+4*3))=0x685a8363;
*((unsigned int *)((unsigned long)context_ptr+0x0000644c+4*4))=0x9af40bbb;
*((unsigned int *)((unsigned long)context_ptr+0x0000644c+4*5))=0x80148e29;
*((unsigned int *)((unsigned long)context_ptr+0x0000644c+4*6))=0xac506bb0;
*((unsigned int *)((unsigned long)context_ptr+0x0000644c+4*7))=0x0062dfef;
*((unsigned int *)((unsigned long)context_ptr+0x000032d0))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x000032d0+4*1))=0x0000636c;
*((unsigned int *)((unsigned long)context_ptr+0x000032d0+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000032d0+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000032d0+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000032d0+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x000002d0))=0x04c0001f;
*((unsigned int *)((unsigned long)context_ptr+0x000002d0+4*1))=0x0000644c;
*((unsigned int *)((unsigned long)context_ptr+0x000002d0+4*2))=0x00006058;
*((unsigned int *)((unsigned long)context_ptr+0x000002d0+4*3))=0x0222001f;
*((unsigned int *)((unsigned long)context_ptr+0x000002d0+4*4))=0x00f08502;
*((unsigned int *)((unsigned long)context_ptr+0x000002d0+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000066&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x0000608c,"\x81\xd9\x20\xa1\xd7\x8d\xe2\x63\xc4\x95\xb8\xc2\x82\x75\x3a\x80\x44\xc5\x0e\xec\x93\xa9\x48\x2b\xfb\xf5\xa6\x14",28))
printf("strip: 81d920a1d78de263, Pass\n");
else
printf("strip: 81d920a1d78de263, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006048))=0x026a1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006048+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006048+4*2))=0x02020020;
*((unsigned int *)((unsigned long)context_ptr+0x00006048+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x00006078))=0xcadddab3;
*((unsigned int *)((unsigned long)context_ptr+0x00006078+4*1))=0x352401bc;
*((unsigned int *)((unsigned long)context_ptr+0x00006078+4*2))=0x7c200093;
*((unsigned int *)((unsigned long)context_ptr+0x00006078+4*3))=0x2c38510a;
*((unsigned int *)((unsigned long)context_ptr+0x00006078+4*4))=0xa63be151;
*((unsigned int *)((unsigned long)context_ptr+0x00006078+4*5))=0x5930acbb;
*((unsigned int *)((unsigned long)context_ptr+0x00006078+4*6))=0x37f88945;
*((unsigned int *)((unsigned long)context_ptr+0x00006078+4*7))=0xf460108d;
*((unsigned int *)((unsigned long)context_ptr+0x000032e8))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x000032e8+4*1))=0x0000646c;
*((unsigned int *)((unsigned long)context_ptr+0x000032e8+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000032e8+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000032e8+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000032e8+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x000002e8))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x000002e8+4*1))=0x00006078;
*((unsigned int *)((unsigned long)context_ptr+0x000002e8+4*2))=0x00006048;
*((unsigned int *)((unsigned long)context_ptr+0x000002e8+4*3))=0x02220020;
*((unsigned int *)((unsigned long)context_ptr+0x000002e8+4*4))=0x0da3f22b;
*((unsigned int *)((unsigned long)context_ptr+0x000002e8+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000006c&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006388,"\x02\xe3\xcf\x1d\x8f\xa1\xef\x95\x67\xd0\xcb\xdd\xce\x39\xa7\x82\x69\x45\x8e\xe1\xce\x60\x4d\xdb\x33\xe9\x5b\xb2",28))
printf("strip: 02e3cf1d8fa1ef95, Pass\n");
else
printf("strip: 02e3cf1d8fa1ef95, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006068))=0x026a1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006068+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006068+4*2))=0x02020021;
*((unsigned int *)((unsigned long)context_ptr+0x00006068+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x00006098))=0x368470f9;
*((unsigned int *)((unsigned long)context_ptr+0x00006098+4*1))=0x9a783c01;
*((unsigned int *)((unsigned long)context_ptr+0x00006098+4*2))=0xb8544ad5;
*((unsigned int *)((unsigned long)context_ptr+0x00006098+4*3))=0x16e0b6aa;
*((unsigned int *)((unsigned long)context_ptr+0x00006098+4*4))=0xa79c7f1f;
*((unsigned int *)((unsigned long)context_ptr+0x00006098+4*5))=0x3deb223a;
*((unsigned int *)((unsigned long)context_ptr+0x00006098+4*6))=0xa2844804;
*((unsigned int *)((unsigned long)context_ptr+0x00006098+4*7))=0x518225bd;
*((unsigned int *)((unsigned long)context_ptr+0x00006098+4*8))=0x000000b9;
*((unsigned int *)((unsigned long)context_ptr+0x00003300))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003300+4*1))=0x00006388;
*((unsigned int *)((unsigned long)context_ptr+0x00003300+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003300+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003300+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003300+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000300))=0x04c00021;
*((unsigned int *)((unsigned long)context_ptr+0x00000300+4*1))=0x00006098;
*((unsigned int *)((unsigned long)context_ptr+0x00000300+4*2))=0x00006068;
*((unsigned int *)((unsigned long)context_ptr+0x00000300+4*3))=0x02220021;
*((unsigned int *)((unsigned long)context_ptr+0x00000300+4*4))=0x0310dfbe;
*((unsigned int *)((unsigned long)context_ptr+0x00000300+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000072&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000063a4,"\x50\x36\xff\x68\xd4\x49\x80\x3f\xbe\x09\xb7\xf6\xb9\x40\x09\x4d\xeb\x53\x9b\x88\x1c\x84\xfc\x43\xcf\x5d\x5e\x4c",28))
printf("strip: 5036ff68d449803f, Pass\n");
else
printf("strip: 5036ff68d449803f, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000063a4))=0x026a1002;
*((unsigned int *)((unsigned long)context_ptr+0x000063a4+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000063a4+4*2))=0x02020022;
*((unsigned int *)((unsigned long)context_ptr+0x000063a4+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x000060bc))=0xfd94c777;
*((unsigned int *)((unsigned long)context_ptr+0x000060bc+4*1))=0x0ffa24b5;
*((unsigned int *)((unsigned long)context_ptr+0x000060bc+4*2))=0x0563a355;
*((unsigned int *)((unsigned long)context_ptr+0x000060bc+4*3))=0x97c63d4b;
*((unsigned int *)((unsigned long)context_ptr+0x000060bc+4*4))=0x5136df24;
*((unsigned int *)((unsigned long)context_ptr+0x000060bc+4*5))=0x846bc3df;
*((unsigned int *)((unsigned long)context_ptr+0x000060bc+4*6))=0xa7b7b5fa;
*((unsigned int *)((unsigned long)context_ptr+0x000060bc+4*7))=0x714cecfc;
*((unsigned int *)((unsigned long)context_ptr+0x000060bc+4*8))=0x00003ca2;
*((unsigned int *)((unsigned long)context_ptr+0x00003318))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003318+4*1))=0x00006488;
*((unsigned int *)((unsigned long)context_ptr+0x00003318+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003318+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003318+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003318+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000318))=0x04c00022;
*((unsigned int *)((unsigned long)context_ptr+0x00000318+4*1))=0x000060bc;
*((unsigned int *)((unsigned long)context_ptr+0x00000318+4*2))=0x000063a4;
*((unsigned int *)((unsigned long)context_ptr+0x00000318+4*3))=0x02220022;
*((unsigned int *)((unsigned long)context_ptr+0x00000318+4*4))=0x04e68155;
*((unsigned int *)((unsigned long)context_ptr+0x00000318+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000078&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006114,"\x71\x77\x22\xa7\xe0\x6d\x3b\x9f\x4d\x43\xe8\x81\x3c\x16\x46\xcf\x95\xcc\x9a\x37\x28\x7f\x23\xf2\xd3\x5c\x43\x9b",28))
printf("strip: 717722a7e06d3b9f, Pass\n");
else
printf("strip: 717722a7e06d3b9f, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000060e0))=0x026a1002;
*((unsigned int *)((unsigned long)context_ptr+0x000060e0+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000060e0+4*2))=0x02020023;
*((unsigned int *)((unsigned long)context_ptr+0x000060e0+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x000060f0))=0x2400ad8e;
*((unsigned int *)((unsigned long)context_ptr+0x000060f0+4*1))=0x3273c017;
*((unsigned int *)((unsigned long)context_ptr+0x000060f0+4*2))=0x8b76ab5f;
*((unsigned int *)((unsigned long)context_ptr+0x000060f0+4*3))=0x1b1a66f0;
*((unsigned int *)((unsigned long)context_ptr+0x000060f0+4*4))=0xc71d4fb9;
*((unsigned int *)((unsigned long)context_ptr+0x000060f0+4*5))=0xbd9d1ae3;
*((unsigned int *)((unsigned long)context_ptr+0x000060f0+4*6))=0x71afd63e;
*((unsigned int *)((unsigned long)context_ptr+0x000060f0+4*7))=0x2ad4422a;
*((unsigned int *)((unsigned long)context_ptr+0x000060f0+4*8))=0x008f92b4;
*((unsigned int *)((unsigned long)context_ptr+0x00003330))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003330+4*1))=0x00006114;
*((unsigned int *)((unsigned long)context_ptr+0x00003330+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003330+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003330+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003330+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000330))=0x04c00023;
*((unsigned int *)((unsigned long)context_ptr+0x00000330+4*1))=0x000060f0;
*((unsigned int *)((unsigned long)context_ptr+0x00000330+4*2))=0x000060e0;
*((unsigned int *)((unsigned long)context_ptr+0x00000330+4*3))=0x02220023;
*((unsigned int *)((unsigned long)context_ptr+0x00000330+4*4))=0x04f4f5a1;
*((unsigned int *)((unsigned long)context_ptr+0x00000330+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000007e&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000063c0,"\xd6\x35\x94\x36\xe5\x1a\xd4\x76\x0e\xfb\x25\x17\x66\x19\x18\xeb\x46\xbe\x39\x09\x4c\xc6\xc0\x13\x4d\x96\x0e\xba",28))
printf("strip: d6359436e51ad476, Pass\n");
else
printf("strip: d6359436e51ad476, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006130))=0x026a1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006130+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006130+4*2))=0x02020024;
*((unsigned int *)((unsigned long)context_ptr+0x00006130+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x000063b4))=0xb46bc5dd;
*((unsigned int *)((unsigned long)context_ptr+0x000063b4+4*1))=0x580910b3;
*((unsigned int *)((unsigned long)context_ptr+0x000063b4+4*2))=0xc2a561a4;
*((unsigned int *)((unsigned long)context_ptr+0x000063b4+4*3))=0x8df848c5;
*((unsigned int *)((unsigned long)context_ptr+0x000063b4+4*4))=0x27aca2a0;
*((unsigned int *)((unsigned long)context_ptr+0x000063b4+4*5))=0xb6f76eac;
*((unsigned int *)((unsigned long)context_ptr+0x000063b4+4*6))=0x96d5fdf9;
*((unsigned int *)((unsigned long)context_ptr+0x000063b4+4*7))=0x6b5e7899;
*((unsigned int *)((unsigned long)context_ptr+0x000063b4+4*8))=0x092ba5e9;
*((unsigned int *)((unsigned long)context_ptr+0x00003348))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003348+4*1))=0x000064a4;
*((unsigned int *)((unsigned long)context_ptr+0x00003348+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003348+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003348+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003348+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000348))=0x04c00024;
*((unsigned int *)((unsigned long)context_ptr+0x00000348+4*1))=0x000063b4;
*((unsigned int *)((unsigned long)context_ptr+0x00000348+4*2))=0x00006130;
*((unsigned int *)((unsigned long)context_ptr+0x00000348+4*3))=0x02220024;
*((unsigned int *)((unsigned long)context_ptr+0x00000348+4*4))=0x010d9e39;
*((unsigned int *)((unsigned long)context_ptr+0x00000348+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000084&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006180,"\x68\x4d\xea\x17\x7d\x3b\x43\x7a\xa3\x18\x97\xe3\x56\x65\x50\x4e\x49\xf2\x62\xd5\x49\xd9\xb1\x67\x71\xb6\x49\xec",28))
printf("strip: 684dea177d3b437a, Pass\n");
else
printf("strip: 684dea177d3b437a, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006140))=0x026a1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006140+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006140+4*2))=0x02020025;
*((unsigned int *)((unsigned long)context_ptr+0x00006140+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x00006150))=0xb71d6eef;
*((unsigned int *)((unsigned long)context_ptr+0x00006150+4*1))=0x8ae38072;
*((unsigned int *)((unsigned long)context_ptr+0x00006150+4*2))=0x82d95f23;
*((unsigned int *)((unsigned long)context_ptr+0x00006150+4*3))=0xe1088114;
*((unsigned int *)((unsigned long)context_ptr+0x00006150+4*4))=0xe5feba3f;
*((unsigned int *)((unsigned long)context_ptr+0x00006150+4*5))=0x8bb25287;
*((unsigned int *)((unsigned long)context_ptr+0x00006150+4*6))=0x27b13de8;
*((unsigned int *)((unsigned long)context_ptr+0x00006150+4*7))=0x485dc767;
*((unsigned int *)((unsigned long)context_ptr+0x00006150+4*8))=0x24025f5a;
*((unsigned int *)((unsigned long)context_ptr+0x00006150+4*9))=0x000000bd;
*((unsigned int *)((unsigned long)context_ptr+0x00003360))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003360+4*1))=0x00006178;
*((unsigned int *)((unsigned long)context_ptr+0x00003360+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003360+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003360+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003360+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000360))=0x04c00025;
*((unsigned int *)((unsigned long)context_ptr+0x00000360+4*1))=0x00006150;
*((unsigned int *)((unsigned long)context_ptr+0x00000360+4*2))=0x00006140;
*((unsigned int *)((unsigned long)context_ptr+0x00000360+4*3))=0x02220025;
*((unsigned int *)((unsigned long)context_ptr+0x00000360+4*4))=0x02308d4e;
*((unsigned int *)((unsigned long)context_ptr+0x00000360+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000008a&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000063dc,"\xf0\xb3\x53\x95\xe8\x68\xe4\x23\xcc\xcf\xb2\x30\x33\xc6\x21\x76\x5c\x8e\xf4\x23\xe4\x14\xff\x65\xd3\x6e\x28\xb1",28))
printf("strip: f0b35395e868e423, Pass\n");
else
printf("strip: f0b35395e868e423, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000063d8))=0x026a1002;
*((unsigned int *)((unsigned long)context_ptr+0x000063d8+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000063d8+4*2))=0x02020026;
*((unsigned int *)((unsigned long)context_ptr+0x000063d8+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x00006194))=0xe4c0a4f7;
*((unsigned int *)((unsigned long)context_ptr+0x00006194+4*1))=0x9e738b74;
*((unsigned int *)((unsigned long)context_ptr+0x00006194+4*2))=0xc55dd255;
*((unsigned int *)((unsigned long)context_ptr+0x00006194+4*3))=0xe67a5d04;
*((unsigned int *)((unsigned long)context_ptr+0x00006194+4*4))=0xe6a2bbb8;
*((unsigned int *)((unsigned long)context_ptr+0x00006194+4*5))=0xc3eba1b9;
*((unsigned int *)((unsigned long)context_ptr+0x00006194+4*6))=0xbf30de03;
*((unsigned int *)((unsigned long)context_ptr+0x00006194+4*7))=0x6d276469;
*((unsigned int *)((unsigned long)context_ptr+0x00006194+4*8))=0xa4bcd3ff;
*((unsigned int *)((unsigned long)context_ptr+0x00006194+4*9))=0x00001036;
*((unsigned int *)((unsigned long)context_ptr+0x00003378))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003378+4*1))=0x000064c0;
*((unsigned int *)((unsigned long)context_ptr+0x00003378+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003378+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003378+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003378+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000378))=0x04c00026;
*((unsigned int *)((unsigned long)context_ptr+0x00000378+4*1))=0x00006194;
*((unsigned int *)((unsigned long)context_ptr+0x00000378+4*2))=0x000063d8;
*((unsigned int *)((unsigned long)context_ptr+0x00000378+4*3))=0x02220026;
*((unsigned int *)((unsigned long)context_ptr+0x00000378+4*4))=0x000916b2;
*((unsigned int *)((unsigned long)context_ptr+0x00000378+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000090&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000061ec,"\x14\x6e\xf6\x6e\x8e\x91\xfd\xe9\x6e\xbc\x87\x05\x42\x55\xe3\x98\x13\x7a\xcc\x3a\xa8\xf8\x3a\x67\x22\xbd\x1b\x81",28))
printf("strip: 146ef66e8e91fde9, Pass\n");
else
printf("strip: 146ef66e8e91fde9, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000063e8))=0x026a1002;
*((unsigned int *)((unsigned long)context_ptr+0x000063e8+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000063e8+4*2))=0x02020027;
*((unsigned int *)((unsigned long)context_ptr+0x000063e8+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x000061bc))=0x2581e418;
*((unsigned int *)((unsigned long)context_ptr+0x000061bc+4*1))=0x780631ef;
*((unsigned int *)((unsigned long)context_ptr+0x000061bc+4*2))=0x90a00c92;
*((unsigned int *)((unsigned long)context_ptr+0x000061bc+4*3))=0x215b1490;
*((unsigned int *)((unsigned long)context_ptr+0x000061bc+4*4))=0xe1545e77;
*((unsigned int *)((unsigned long)context_ptr+0x000061bc+4*5))=0xffa81c9f;
*((unsigned int *)((unsigned long)context_ptr+0x000061bc+4*6))=0x79a8c55d;
*((unsigned int *)((unsigned long)context_ptr+0x000061bc+4*7))=0x446a3667;
*((unsigned int *)((unsigned long)context_ptr+0x000061bc+4*8))=0x25e3ab7c;
*((unsigned int *)((unsigned long)context_ptr+0x000061bc+4*9))=0x00a0c3cf;
*((unsigned int *)((unsigned long)context_ptr+0x00003390))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003390+4*1))=0x000061e4;
*((unsigned int *)((unsigned long)context_ptr+0x00003390+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003390+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003390+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003390+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000390))=0x04c00027;
*((unsigned int *)((unsigned long)context_ptr+0x00000390+4*1))=0x000061bc;
*((unsigned int *)((unsigned long)context_ptr+0x00000390+4*2))=0x000063e8;
*((unsigned int *)((unsigned long)context_ptr+0x00000390+4*3))=0x02220027;
*((unsigned int *)((unsigned long)context_ptr+0x00000390+4*4))=0x02308b50;
*((unsigned int *)((unsigned long)context_ptr+0x00000390+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000096&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000063f8,"\x5a\xc5\xae\x40\x8a\xb8\x37\x98\xfb\xb5\x6f\x34\x95\xaa\x01\x11\x98\x87\x87\x3e\x15\xe7\x2d\x56\xea\xb6\x0d\xa0",28))
printf("strip: 5ac5ae408ab83798, Pass\n");
else
printf("strip: 5ac5ae408ab83798, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000063f8))=0x026a1002;
*((unsigned int *)((unsigned long)context_ptr+0x000063f8+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000063f8+4*2))=0x02020028;
*((unsigned int *)((unsigned long)context_ptr+0x000063f8+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x00006200))=0x17a8debc;
*((unsigned int *)((unsigned long)context_ptr+0x00006200+4*1))=0x75ffcc84;
*((unsigned int *)((unsigned long)context_ptr+0x00006200+4*2))=0xed7f590e;
*((unsigned int *)((unsigned long)context_ptr+0x00006200+4*3))=0x1970ea10;
*((unsigned int *)((unsigned long)context_ptr+0x00006200+4*4))=0x3c221ec0;
*((unsigned int *)((unsigned long)context_ptr+0x00006200+4*5))=0x96dca98c;
*((unsigned int *)((unsigned long)context_ptr+0x00006200+4*6))=0xa9817ba3;
*((unsigned int *)((unsigned long)context_ptr+0x00006200+4*7))=0x9f9f4b45;
*((unsigned int *)((unsigned long)context_ptr+0x00006200+4*8))=0xd58c322e;
*((unsigned int *)((unsigned long)context_ptr+0x00006200+4*9))=0x870c2c4f;
*((unsigned int *)((unsigned long)context_ptr+0x000033a8))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x000033a8+4*1))=0x000064dc;
*((unsigned int *)((unsigned long)context_ptr+0x000033a8+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000033a8+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000033a8+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000033a8+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x000003a8))=0x04c00028;
*((unsigned int *)((unsigned long)context_ptr+0x000003a8+4*1))=0x00006200;
*((unsigned int *)((unsigned long)context_ptr+0x000003a8+4*2))=0x000063f8;
*((unsigned int *)((unsigned long)context_ptr+0x000003a8+4*3))=0x02220028;
*((unsigned int *)((unsigned long)context_ptr+0x000003a8+4*4))=0x08bebbe4;
*((unsigned int *)((unsigned long)context_ptr+0x000003a8+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000009c&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006260,"\xdd\xc9\xd5\x37\x4f\x25\x22\x0c\x4f\xa9\x95\x32\x1a\xd0\x03\xc4\xa0\xdb\x50\x00\xc4\xe4\xa2\xaa\x21\xea\x86\x6e",28))
printf("strip: ddc9d5374f25220c, Pass\n");
else
printf("strip: ddc9d5374f25220c, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006228))=0x026a1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006228+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006228+4*2))=0x02020029;
*((unsigned int *)((unsigned long)context_ptr+0x00006228+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x00006238))=0x7af721d0;
*((unsigned int *)((unsigned long)context_ptr+0x00006238+4*1))=0x31f02bf3;
*((unsigned int *)((unsigned long)context_ptr+0x00006238+4*2))=0x29d745de;
*((unsigned int *)((unsigned long)context_ptr+0x00006238+4*3))=0xef1fa9da;
*((unsigned int *)((unsigned long)context_ptr+0x00006238+4*4))=0x0dd72f6f;
*((unsigned int *)((unsigned long)context_ptr+0x00006238+4*5))=0xbf17bc09;
*((unsigned int *)((unsigned long)context_ptr+0x00006238+4*6))=0x9023f018;
*((unsigned int *)((unsigned long)context_ptr+0x00006238+4*7))=0x7d185da5;
*((unsigned int *)((unsigned long)context_ptr+0x00006238+4*8))=0x3934e455;
*((unsigned int *)((unsigned long)context_ptr+0x00006238+4*9))=0x23497198;
*((unsigned int *)((unsigned long)context_ptr+0x00006238+4*10))=0x000000d6;
*((unsigned int *)((unsigned long)context_ptr+0x000033c0))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x000033c0+4*1))=0x000064f8;
*((unsigned int *)((unsigned long)context_ptr+0x000033c0+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000033c0+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000033c0+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000033c0+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x000003c0))=0x04c00029;
*((unsigned int *)((unsigned long)context_ptr+0x000003c0+4*1))=0x00006238;
*((unsigned int *)((unsigned long)context_ptr+0x000003c0+4*2))=0x00006228;
*((unsigned int *)((unsigned long)context_ptr+0x000003c0+4*3))=0x02220029;
*((unsigned int *)((unsigned long)context_ptr+0x000003c0+4*4))=0x0f0c0dc2;
*((unsigned int *)((unsigned long)context_ptr+0x000003c0+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000000a2&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006414,"\x15\x1b\x96\x44\x06\x41\x58\x46\x32\xb6\x86\xa8\xda\xbd\xf2\xff\xe1\x84\xff\x20\x47\x7a\xfe\xe2\x3b\xcb\x82\xcb",28))
printf("strip: 151b964406415846, Pass\n");
else
printf("strip: 151b964406415846, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006408))=0x026a1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006408+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006408+4*2))=0x0202002a;
*((unsigned int *)((unsigned long)context_ptr+0x00006408+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x00006264))=0x17d0975c;
*((unsigned int *)((unsigned long)context_ptr+0x00006264+4*1))=0xf8e77a1c;
*((unsigned int *)((unsigned long)context_ptr+0x00006264+4*2))=0x60cb31a7;
*((unsigned int *)((unsigned long)context_ptr+0x00006264+4*3))=0x84719743;
*((unsigned int *)((unsigned long)context_ptr+0x00006264+4*4))=0x6edf09f8;
*((unsigned int *)((unsigned long)context_ptr+0x00006264+4*5))=0x79bce0d8;
*((unsigned int *)((unsigned long)context_ptr+0x00006264+4*6))=0xb6659885;
*((unsigned int *)((unsigned long)context_ptr+0x00006264+4*7))=0x90f456da;
*((unsigned int *)((unsigned long)context_ptr+0x00006264+4*8))=0x47b9294b;
*((unsigned int *)((unsigned long)context_ptr+0x00006264+4*9))=0x605af2cf;
*((unsigned int *)((unsigned long)context_ptr+0x00006264+4*10))=0x0000414d;
*((unsigned int *)((unsigned long)context_ptr+0x000033d8))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x000033d8+4*1))=0x00006514;
*((unsigned int *)((unsigned long)context_ptr+0x000033d8+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000033d8+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000033d8+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000033d8+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x000003d8))=0x04c0002a;
*((unsigned int *)((unsigned long)context_ptr+0x000003d8+4*1))=0x00006264;
*((unsigned int *)((unsigned long)context_ptr+0x000003d8+4*2))=0x00006408;
*((unsigned int *)((unsigned long)context_ptr+0x000003d8+4*3))=0x0222002a;
*((unsigned int *)((unsigned long)context_ptr+0x000003d8+4*4))=0x0dd761ad;
*((unsigned int *)((unsigned long)context_ptr+0x000003d8+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000000a8&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000062d4,"\xaf\xd2\xd8\x1b\x74\x9a\x82\xc3\x91\xd2\x85\x87\x1e\x99\xf3\x13\xd2\xa9\x45\xd8\x4d\xb6\xd2\x4c\x99\x4f\xe6\x7c",28))
printf("strip: afd2d81b749a82c3, Pass\n");
else
printf("strip: afd2d81b749a82c3, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006418))=0x026a1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006418+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006418+4*2))=0x0202002b;
*((unsigned int *)((unsigned long)context_ptr+0x00006418+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x00006290))=0x64dd1ba6;
*((unsigned int *)((unsigned long)context_ptr+0x00006290+4*1))=0xab612bd0;
*((unsigned int *)((unsigned long)context_ptr+0x00006290+4*2))=0xcfec84a1;
*((unsigned int *)((unsigned long)context_ptr+0x00006290+4*3))=0x836aad98;
*((unsigned int *)((unsigned long)context_ptr+0x00006290+4*4))=0x7533d6a1;
*((unsigned int *)((unsigned long)context_ptr+0x00006290+4*5))=0x1e09322f;
*((unsigned int *)((unsigned long)context_ptr+0x00006290+4*6))=0x244e54c1;
*((unsigned int *)((unsigned long)context_ptr+0x00006290+4*7))=0x610e6a93;
*((unsigned int *)((unsigned long)context_ptr+0x00006290+4*8))=0xdbf9c1ce;
*((unsigned int *)((unsigned long)context_ptr+0x00006290+4*9))=0x68c9ca7f;
*((unsigned int *)((unsigned long)context_ptr+0x00006290+4*10))=0x00718f63;
*((unsigned int *)((unsigned long)context_ptr+0x000033f0))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x000033f0+4*1))=0x000062bc;
*((unsigned int *)((unsigned long)context_ptr+0x000033f0+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000033f0+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000033f0+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000033f0+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x000003f0))=0x04c0002b;
*((unsigned int *)((unsigned long)context_ptr+0x000003f0+4*1))=0x00006290;
*((unsigned int *)((unsigned long)context_ptr+0x000003f0+4*2))=0x00006418;
*((unsigned int *)((unsigned long)context_ptr+0x000003f0+4*3))=0x0222002b;
*((unsigned int *)((unsigned long)context_ptr+0x000003f0+4*4))=0x0eb41949;
*((unsigned int *)((unsigned long)context_ptr+0x000003f0+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000000ae&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006430,"\x79\x66\x8e\x95\xae\x82\x15\x3b\x13\xcf\x5d\xcf\x32\xec\xe8\x3e\x63\x9c\x46\x6b\x5f\xa8\xf2\x01\x48\x4a\x9d\x02",28))
printf("strip: 79668e95ae82153b, Pass\n");
else
printf("strip: 79668e95ae82153b, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006428))=0x026a1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006428+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006428+4*2))=0x0202002c;
*((unsigned int *)((unsigned long)context_ptr+0x00006428+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x000062d8))=0xcc13b089;
*((unsigned int *)((unsigned long)context_ptr+0x000062d8+4*1))=0xe353445b;
*((unsigned int *)((unsigned long)context_ptr+0x000062d8+4*2))=0xa076fc1a;
*((unsigned int *)((unsigned long)context_ptr+0x000062d8+4*3))=0x66c41081;
*((unsigned int *)((unsigned long)context_ptr+0x000062d8+4*4))=0x244fd27b;
*((unsigned int *)((unsigned long)context_ptr+0x000062d8+4*5))=0x9710b00b;
*((unsigned int *)((unsigned long)context_ptr+0x000062d8+4*6))=0x4a641c11;
*((unsigned int *)((unsigned long)context_ptr+0x000062d8+4*7))=0xf6f2f11b;
*((unsigned int *)((unsigned long)context_ptr+0x000062d8+4*8))=0x6790e8fa;
*((unsigned int *)((unsigned long)context_ptr+0x000062d8+4*9))=0xc63a86bd;
*((unsigned int *)((unsigned long)context_ptr+0x000062d8+4*10))=0x89f3a629;
*((unsigned int *)((unsigned long)context_ptr+0x00003408))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003408+4*1))=0x00006304;
*((unsigned int *)((unsigned long)context_ptr+0x00003408+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003408+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003408+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003408+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000408))=0x04c0002c;
*((unsigned int *)((unsigned long)context_ptr+0x00000408+4*1))=0x000062d8;
*((unsigned int *)((unsigned long)context_ptr+0x00000408+4*2))=0x00006428;
*((unsigned int *)((unsigned long)context_ptr+0x00000408+4*3))=0x0222002c;
*((unsigned int *)((unsigned long)context_ptr+0x00000408+4*4))=0x082c15d7;
*((unsigned int *)((unsigned long)context_ptr+0x00000408+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000000b4&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006350,"\xdf\x43\x79\x18\xf2\x3d\xbc\x25\x6a\xb8\xd5\x49\x62\x65\x98\x22\x94\x4a\x3c\x44\xc5\xa3\xb5\x70\xee\x31\xdf\x8d",28))
printf("strip: df437918f23dbc25, Pass\n");
else
printf("strip: df437918f23dbc25, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006320))=0x026a1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006320+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006320+4*2))=0x0202002d;
*((unsigned int *)((unsigned long)context_ptr+0x00006320+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x00006330))=0xa17505a0;
*((unsigned int *)((unsigned long)context_ptr+0x00006330+4*1))=0x02e92961;
*((unsigned int *)((unsigned long)context_ptr+0x00006330+4*2))=0xe9fd2add;
*((unsigned int *)((unsigned long)context_ptr+0x00006330+4*3))=0xddaac417;
*((unsigned int *)((unsigned long)context_ptr+0x00006330+4*4))=0xbcca4f7f;
*((unsigned int *)((unsigned long)context_ptr+0x00006330+4*5))=0x7fc4fc89;
*((unsigned int *)((unsigned long)context_ptr+0x00006330+4*6))=0x0cd781ed;
*((unsigned int *)((unsigned long)context_ptr+0x00006330+4*7))=0x233b3621;
*((unsigned int *)((unsigned long)context_ptr+0x00006330+4*8))=0xb9978f0a;
*((unsigned int *)((unsigned long)context_ptr+0x00006330+4*9))=0x0373749d;
*((unsigned int *)((unsigned long)context_ptr+0x00006330+4*10))=0xf6a0a29d;
*((unsigned int *)((unsigned long)context_ptr+0x00006330+4*11))=0x000000b4;
*((unsigned int *)((unsigned long)context_ptr+0x00003420))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003420+4*1))=0x00006530;
*((unsigned int *)((unsigned long)context_ptr+0x00003420+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003420+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003420+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003420+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000420))=0x04c0002d;
*((unsigned int *)((unsigned long)context_ptr+0x00000420+4*1))=0x00006330;
*((unsigned int *)((unsigned long)context_ptr+0x00000420+4*2))=0x00006320;
*((unsigned int *)((unsigned long)context_ptr+0x00000420+4*3))=0x0222002d;
*((unsigned int *)((unsigned long)context_ptr+0x00000420+4*4))=0x08dcdfa8;
*((unsigned int *)((unsigned long)context_ptr+0x00000420+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000000ba&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x0000636c,"\xb9\x71\xa3\x11\x1a\x17\x4f\xce\x52\x4d\x25\x59\xb3\x83\x08\xd7\x74\x35\xfc\x30\x3a\x60\xa6\x60\xbf\x59\xfb\x25",28))
printf("strip: b971a3111a174fce, Pass\n");
else
printf("strip: b971a3111a174fce, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006058))=0x026a1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*2))=0x0202002e;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x00006438))=0x79482cab;
*((unsigned int *)((unsigned long)context_ptr+0x00006438+4*1))=0xc2ec4d8a;
*((unsigned int *)((unsigned long)context_ptr+0x00006438+4*2))=0xd4d113a0;
*((unsigned int *)((unsigned long)context_ptr+0x00006438+4*3))=0xe62cd4ce;
*((unsigned int *)((unsigned long)context_ptr+0x00006438+4*4))=0x2800434b;
*((unsigned int *)((unsigned long)context_ptr+0x00006438+4*5))=0x0cdf3b58;
*((unsigned int *)((unsigned long)context_ptr+0x00006438+4*6))=0xd5dd6071;
*((unsigned int *)((unsigned long)context_ptr+0x00006438+4*7))=0x4075ad53;
*((unsigned int *)((unsigned long)context_ptr+0x00006438+4*8))=0xbcb277b2;
*((unsigned int *)((unsigned long)context_ptr+0x00006438+4*9))=0x0223438f;
*((unsigned int *)((unsigned long)context_ptr+0x00006438+4*10))=0x48d3a96c;
*((unsigned int *)((unsigned long)context_ptr+0x00006438+4*11))=0x00007b11;
*((unsigned int *)((unsigned long)context_ptr+0x00003438))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003438+4*1))=0x00006360;
*((unsigned int *)((unsigned long)context_ptr+0x00003438+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003438+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003438+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003438+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000438))=0x04c0002e;
*((unsigned int *)((unsigned long)context_ptr+0x00000438+4*1))=0x00006438;
*((unsigned int *)((unsigned long)context_ptr+0x00000438+4*2))=0x00006058;
*((unsigned int *)((unsigned long)context_ptr+0x00000438+4*3))=0x0222002e;
*((unsigned int *)((unsigned long)context_ptr+0x00000438+4*4))=0x00c1aa8d;
*((unsigned int *)((unsigned long)context_ptr+0x00000438+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000000c0&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x0000646c,"\xc4\xeb\xb6\x05\x10\xe1\x68\x6a\x04\x23\xa0\xd6\xec\xb6\x87\xdd\xf1\xa9\xcf\xb8\x67\x0c\x12\x85\x2d\x75\x67\x48",28))
printf("strip: c4ebb60510e1686a, Pass\n");
else
printf("strip: c4ebb60510e1686a, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006048))=0x026a1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006048+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006048+4*2))=0x0202002f;
*((unsigned int *)((unsigned long)context_ptr+0x00006048+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x0000654c))=0x2ddb2618;
*((unsigned int *)((unsigned long)context_ptr+0x0000654c+4*1))=0x44cb1472;
*((unsigned int *)((unsigned long)context_ptr+0x0000654c+4*2))=0x3469d1a9;
*((unsigned int *)((unsigned long)context_ptr+0x0000654c+4*3))=0xa8987528;
*((unsigned int *)((unsigned long)context_ptr+0x0000654c+4*4))=0x22003e96;
*((unsigned int *)((unsigned long)context_ptr+0x0000654c+4*5))=0xfa91f870;
*((unsigned int *)((unsigned long)context_ptr+0x0000654c+4*6))=0xb04afed7;
*((unsigned int *)((unsigned long)context_ptr+0x0000654c+4*7))=0x679dde6e;
*((unsigned int *)((unsigned long)context_ptr+0x0000654c+4*8))=0x6c7ed7f1;
*((unsigned int *)((unsigned long)context_ptr+0x0000654c+4*9))=0x2a4f6767;
*((unsigned int *)((unsigned long)context_ptr+0x0000654c+4*10))=0x289f1fd4;
*((unsigned int *)((unsigned long)context_ptr+0x0000654c+4*11))=0x00203ade;
*((unsigned int *)((unsigned long)context_ptr+0x00003450))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003450+4*1))=0x00006078;
*((unsigned int *)((unsigned long)context_ptr+0x00003450+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003450+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003450+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003450+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000450))=0x04c0002f;
*((unsigned int *)((unsigned long)context_ptr+0x00000450+4*1))=0x0000654c;
*((unsigned int *)((unsigned long)context_ptr+0x00000450+4*2))=0x00006048;
*((unsigned int *)((unsigned long)context_ptr+0x00000450+4*3))=0x0222002f;
*((unsigned int *)((unsigned long)context_ptr+0x00000450+4*4))=0x0c9e6358;
*((unsigned int *)((unsigned long)context_ptr+0x00000450+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000000c6&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006388,"\x29\x69\xca\x4c\x3e\xf9\x7d\x56\x81\x49\x68\x5c\x86\x41\xb7\xe1\x17\x45\xdc\xd8\x8a\xb0\x00\x1a\x07\x14\x29\xb2",28))
printf("strip: 2969ca4c3ef97d56, Pass\n");
else
printf("strip: 2969ca4c3ef97d56, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006068))=0x026a1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006068+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006068+4*2))=0x02020030;
*((unsigned int *)((unsigned long)context_ptr+0x00006068+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x0000657c))=0x8e1b4286;
*((unsigned int *)((unsigned long)context_ptr+0x0000657c+4*1))=0x6c570e8e;
*((unsigned int *)((unsigned long)context_ptr+0x0000657c+4*2))=0xcdab517b;
*((unsigned int *)((unsigned long)context_ptr+0x0000657c+4*3))=0x97aa6b1e;
*((unsigned int *)((unsigned long)context_ptr+0x0000657c+4*4))=0xe38bdedf;
*((unsigned int *)((unsigned long)context_ptr+0x0000657c+4*5))=0x620226ce;
*((unsigned int *)((unsigned long)context_ptr+0x0000657c+4*6))=0x84cf075d;
*((unsigned int *)((unsigned long)context_ptr+0x0000657c+4*7))=0x66ced5f9;
*((unsigned int *)((unsigned long)context_ptr+0x0000657c+4*8))=0x8d1ab6f1;
*((unsigned int *)((unsigned long)context_ptr+0x0000657c+4*9))=0x0a67a436;
*((unsigned int *)((unsigned long)context_ptr+0x0000657c+4*10))=0x35a3ebe6;
*((unsigned int *)((unsigned long)context_ptr+0x0000657c+4*11))=0x351db169;
*((unsigned int *)((unsigned long)context_ptr+0x00003468))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003468+4*1))=0x00006468;
*((unsigned int *)((unsigned long)context_ptr+0x00003468+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003468+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003468+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003468+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000468))=0x04c00030;
*((unsigned int *)((unsigned long)context_ptr+0x00000468+4*1))=0x0000657c;
*((unsigned int *)((unsigned long)context_ptr+0x00000468+4*2))=0x00006068;
*((unsigned int *)((unsigned long)context_ptr+0x00000468+4*3))=0x02220030;
*((unsigned int *)((unsigned long)context_ptr+0x00000468+4*4))=0x0c142562;
*((unsigned int *)((unsigned long)context_ptr+0x00000468+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000000cc&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006488,"\x5c\xb6\xf6\xb6\xd5\xa1\x45\x13\x6e\xc6\xc1\xf1\xa5\x5f\xa4\x01\x46\x94\xdf\x57\xfa\x35\xd4\x27\xcf\xd3\x1b\xd7",28))
printf("strip: 5cb6f6b6d5a14513, Pass\n");
else
printf("strip: 5cb6f6b6d5a14513, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006484))=0x026a1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006484+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006484+4*2))=0x02020031;
*((unsigned int *)((unsigned long)context_ptr+0x00006484+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x0000637c))=0x6dd00694;
*((unsigned int *)((unsigned long)context_ptr+0x0000637c+4*1))=0x8ccb06bb;
*((unsigned int *)((unsigned long)context_ptr+0x0000637c+4*2))=0x9f680c05;
*((unsigned int *)((unsigned long)context_ptr+0x0000637c+4*3))=0x61e6a473;
*((unsigned int *)((unsigned long)context_ptr+0x0000637c+4*4))=0x560bcb6b;
*((unsigned int *)((unsigned long)context_ptr+0x0000637c+4*5))=0xa9aca70f;
*((unsigned int *)((unsigned long)context_ptr+0x0000637c+4*6))=0xa103be9e;
*((unsigned int *)((unsigned long)context_ptr+0x0000637c+4*7))=0x08c1d5a1;
*((unsigned int *)((unsigned long)context_ptr+0x0000637c+4*8))=0x1b476997;
*((unsigned int *)((unsigned long)context_ptr+0x0000637c+4*9))=0x7b3d271f;
*((unsigned int *)((unsigned long)context_ptr+0x0000637c+4*10))=0x8534429a;
*((unsigned int *)((unsigned long)context_ptr+0x0000637c+4*11))=0x643a137c;
*((unsigned int *)((unsigned long)context_ptr+0x0000637c+4*12))=0x000000ef;
*((unsigned int *)((unsigned long)context_ptr+0x00003480))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003480+4*1))=0x00006094;
*((unsigned int *)((unsigned long)context_ptr+0x00003480+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003480+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003480+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003480+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000480))=0x04c00031;
*((unsigned int *)((unsigned long)context_ptr+0x00000480+4*1))=0x0000637c;
*((unsigned int *)((unsigned long)context_ptr+0x00000480+4*2))=0x00006484;
*((unsigned int *)((unsigned long)context_ptr+0x00000480+4*3))=0x02220031;
*((unsigned int *)((unsigned long)context_ptr+0x00000480+4*4))=0x0dfaec0a;
*((unsigned int *)((unsigned long)context_ptr+0x00000480+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000000d2&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006114,"\xb8\xe4\x6b\x59\x2e\x63\xac\xbf\x2d\xb8\x21\xf2\x77\x24\xa7\xa8\xbf\x51\x17\x97\xf5\xfa\xac\xf9\x1a\x49\x25\x74",28))
printf("strip: b8e46b592e63acbf, Pass\n");
else
printf("strip: b8e46b592e63acbf, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006494))=0x026a1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006494+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006494+4*2))=0x02020032;
*((unsigned int *)((unsigned long)context_ptr+0x00006494+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x000060b0))=0x7cc04a23;
*((unsigned int *)((unsigned long)context_ptr+0x000060b0+4*1))=0x3f9e44a3;
*((unsigned int *)((unsigned long)context_ptr+0x000060b0+4*2))=0x4d71b703;
*((unsigned int *)((unsigned long)context_ptr+0x000060b0+4*3))=0xf8ce6186;
*((unsigned int *)((unsigned long)context_ptr+0x000060b0+4*4))=0x02a709a6;
*((unsigned int *)((unsigned long)context_ptr+0x000060b0+4*5))=0x06dd1766;
*((unsigned int *)((unsigned long)context_ptr+0x000060b0+4*6))=0x428276ad;
*((unsigned int *)((unsigned long)context_ptr+0x000060b0+4*7))=0x7d736e60;
*((unsigned int *)((unsigned long)context_ptr+0x000060b0+4*8))=0x84dca1d5;
*((unsigned int *)((unsigned long)context_ptr+0x000060b0+4*9))=0xbcb6a086;
*((unsigned int *)((unsigned long)context_ptr+0x000060b0+4*10))=0xbc46668f;
*((unsigned int *)((unsigned long)context_ptr+0x000060b0+4*11))=0xe5fdf50f;
*((unsigned int *)((unsigned long)context_ptr+0x000060b0+4*12))=0x0000f5e3;
*((unsigned int *)((unsigned long)context_ptr+0x00003498))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003498+4*1))=0x000060e4;
*((unsigned int *)((unsigned long)context_ptr+0x00003498+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003498+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003498+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003498+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000498))=0x04c00032;
*((unsigned int *)((unsigned long)context_ptr+0x00000498+4*1))=0x000060b0;
*((unsigned int *)((unsigned long)context_ptr+0x00000498+4*2))=0x00006494;
*((unsigned int *)((unsigned long)context_ptr+0x00000498+4*3))=0x02220032;
*((unsigned int *)((unsigned long)context_ptr+0x00000498+4*4))=0x02f7bfb8;
*((unsigned int *)((unsigned long)context_ptr+0x00000498+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000000d8&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000064a4,"\xf5\x40\xd6\xc9\x6d\x7e\x81\x92\x5e\x40\x2f\x1a\xea\x91\x6e\x8a\x1d\xc5\xff\x9f\x11\x9e\x45\x19\xe8\x9b\x9f\xac",28))
printf("strip: f540d6c96d7e8192, Pass\n");
else
printf("strip: f540d6c96d7e8192, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000064a4))=0x026a1002;
*((unsigned int *)((unsigned long)context_ptr+0x000064a4+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000064a4+4*2))=0x02020033;
*((unsigned int *)((unsigned long)context_ptr+0x000064a4+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x00006100))=0x48b18343;
*((unsigned int *)((unsigned long)context_ptr+0x00006100+4*1))=0x344c3121;
*((unsigned int *)((unsigned long)context_ptr+0x00006100+4*2))=0xb06f0a4b;
*((unsigned int *)((unsigned long)context_ptr+0x00006100+4*3))=0x6b1a2a02;
*((unsigned int *)((unsigned long)context_ptr+0x00006100+4*4))=0x5a6644df;
*((unsigned int *)((unsigned long)context_ptr+0x00006100+4*5))=0x0a371727;
*((unsigned int *)((unsigned long)context_ptr+0x00006100+4*6))=0xfd47c264;
*((unsigned int *)((unsigned long)context_ptr+0x00006100+4*7))=0x9191c181;
*((unsigned int *)((unsigned long)context_ptr+0x00006100+4*8))=0x2934c8c8;
*((unsigned int *)((unsigned long)context_ptr+0x00006100+4*9))=0x3b143b2f;
*((unsigned int *)((unsigned long)context_ptr+0x00006100+4*10))=0x9d07a165;
*((unsigned int *)((unsigned long)context_ptr+0x00006100+4*11))=0x91a7e4b5;
*((unsigned int *)((unsigned long)context_ptr+0x00006100+4*12))=0x009c614c;
*((unsigned int *)((unsigned long)context_ptr+0x000034b0))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x000034b0+4*1))=0x000063b0;
*((unsigned int *)((unsigned long)context_ptr+0x000034b0+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000034b0+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000034b0+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000034b0+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x000004b0))=0x04c00033;
*((unsigned int *)((unsigned long)context_ptr+0x000004b0+4*1))=0x00006100;
*((unsigned int *)((unsigned long)context_ptr+0x000004b0+4*2))=0x000064a4;
*((unsigned int *)((unsigned long)context_ptr+0x000004b0+4*3))=0x02220033;
*((unsigned int *)((unsigned long)context_ptr+0x000004b0+4*4))=0x0aa757aa;
*((unsigned int *)((unsigned long)context_ptr+0x000004b0+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000000de&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006178,"\xb7\x91\xb9\xe0\x9c\x6c\x02\xa4\x11\xd8\xf5\xfb\xcd\x8c\x82\x45\x9b\x1c\x4f\x68\x87\x20\x7a\xca\xd8\x93\x80\x1f",28))
printf("strip: b791b9e09c6c02a4, Pass\n");
else
printf("strip: b791b9e09c6c02a4, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006134))=0x026a1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006134+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006134+4*2))=0x02020034;
*((unsigned int *)((unsigned long)context_ptr+0x00006134+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x00006144))=0x0ba6c53f;
*((unsigned int *)((unsigned long)context_ptr+0x00006144+4*1))=0xf01d9860;
*((unsigned int *)((unsigned long)context_ptr+0x00006144+4*2))=0x40119b2c;
*((unsigned int *)((unsigned long)context_ptr+0x00006144+4*3))=0xe4fac325;
*((unsigned int *)((unsigned long)context_ptr+0x00006144+4*4))=0xa8e8a437;
*((unsigned int *)((unsigned long)context_ptr+0x00006144+4*5))=0xa554720f;
*((unsigned int *)((unsigned long)context_ptr+0x00006144+4*6))=0x0e0ca80f;
*((unsigned int *)((unsigned long)context_ptr+0x00006144+4*7))=0x43c4dd3a;
*((unsigned int *)((unsigned long)context_ptr+0x00006144+4*8))=0x8eee4202;
*((unsigned int *)((unsigned long)context_ptr+0x00006144+4*9))=0xd8a1b914;
*((unsigned int *)((unsigned long)context_ptr+0x00006144+4*10))=0xe0add8fa;
*((unsigned int *)((unsigned long)context_ptr+0x00006144+4*11))=0x4c83369e;
*((unsigned int *)((unsigned long)context_ptr+0x00006144+4*12))=0x49112f3f;
*((unsigned int *)((unsigned long)context_ptr+0x000034c8))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x000034c8+4*1))=0x00006178;
*((unsigned int *)((unsigned long)context_ptr+0x000034c8+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000034c8+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000034c8+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000034c8+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x000004c8))=0x04c00034;
*((unsigned int *)((unsigned long)context_ptr+0x000004c8+4*1))=0x00006144;
*((unsigned int *)((unsigned long)context_ptr+0x000004c8+4*2))=0x00006134;
*((unsigned int *)((unsigned long)context_ptr+0x000004c8+4*3))=0x02220034;
*((unsigned int *)((unsigned long)context_ptr+0x000004c8+4*4))=0x087a60c5;
*((unsigned int *)((unsigned long)context_ptr+0x000004c8+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000000e4&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000064c0,"\x6a\x23\x59\x15\x81\x21\xfe\xe4\xb6\x61\xe0\x30\x18\x4f\x67\x18\x94\x46\xf8\xf0\xa6\x1b\x48\x71\x04\x28\xe6\xac",28))
printf("strip: 6a2359158121fee4, Pass\n");
else
printf("strip: 6a2359158121fee4, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000063cc))=0x026a1002;
*((unsigned int *)((unsigned long)context_ptr+0x000063cc+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000063cc+4*2))=0x02020035;
*((unsigned int *)((unsigned long)context_ptr+0x000063cc+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x000065ac))=0x605fd93d;
*((unsigned int *)((unsigned long)context_ptr+0x000065ac+4*1))=0xd1488f63;
*((unsigned int *)((unsigned long)context_ptr+0x000065ac+4*2))=0x6011caab;
*((unsigned int *)((unsigned long)context_ptr+0x000065ac+4*3))=0xda563135;
*((unsigned int *)((unsigned long)context_ptr+0x000065ac+4*4))=0xc9d91060;
*((unsigned int *)((unsigned long)context_ptr+0x000065ac+4*5))=0x5b270b8c;
*((unsigned int *)((unsigned long)context_ptr+0x000065ac+4*6))=0xf7c44c6a;
*((unsigned int *)((unsigned long)context_ptr+0x000065ac+4*7))=0x23732b6d;
*((unsigned int *)((unsigned long)context_ptr+0x000065ac+4*8))=0x5afb6876;
*((unsigned int *)((unsigned long)context_ptr+0x000065ac+4*9))=0xb2b4ee1f;
*((unsigned int *)((unsigned long)context_ptr+0x000065ac+4*10))=0x4ab63453;
*((unsigned int *)((unsigned long)context_ptr+0x000065ac+4*11))=0xa270189d;
*((unsigned int *)((unsigned long)context_ptr+0x000065ac+4*12))=0x743aa38c;
*((unsigned int *)((unsigned long)context_ptr+0x000065ac+4*13))=0x00000010;
*((unsigned int *)((unsigned long)context_ptr+0x000034e0))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x000034e0+4*1))=0x00006194;
*((unsigned int *)((unsigned long)context_ptr+0x000034e0+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000034e0+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000034e0+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000034e0+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x000004e0))=0x04c00035;
*((unsigned int *)((unsigned long)context_ptr+0x000004e0+4*1))=0x000065ac;
*((unsigned int *)((unsigned long)context_ptr+0x000004e0+4*2))=0x000063cc;
*((unsigned int *)((unsigned long)context_ptr+0x000004e0+4*3))=0x02220035;
*((unsigned int *)((unsigned long)context_ptr+0x000004e0+4*4))=0x0a5cecdf;
*((unsigned int *)((unsigned long)context_ptr+0x000004e0+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000000ea&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000061e4,"\x0e\x97\x0e\x9e\x44\x1c\x80\x33\x84\xf6\xf8\x8c\xf4\xc1\xbf\xf5\x34\x4f\x50\x07\x0c\xe8\xec\x3c\x9b\x6f\x86\x86",28))
printf("strip: 0e970e9e441c8033, Pass\n");
else
printf("strip: 0e970e9e441c8033, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000063dc))=0x026a1002;
*((unsigned int *)((unsigned long)context_ptr+0x000063dc+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000063dc+4*2))=0x02020036;
*((unsigned int *)((unsigned long)context_ptr+0x000063dc+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x000061b0))=0x655e9d37;
*((unsigned int *)((unsigned long)context_ptr+0x000061b0+4*1))=0xcedaadc5;
*((unsigned int *)((unsigned long)context_ptr+0x000061b0+4*2))=0xca6c1a7d;
*((unsigned int *)((unsigned long)context_ptr+0x000061b0+4*3))=0xd166d75d;
*((unsigned int *)((unsigned long)context_ptr+0x000061b0+4*4))=0xec01abc2;
*((unsigned int *)((unsigned long)context_ptr+0x000061b0+4*5))=0xdc03175d;
*((unsigned int *)((unsigned long)context_ptr+0x000061b0+4*6))=0xeffc966b;
*((unsigned int *)((unsigned long)context_ptr+0x000061b0+4*7))=0x6ba4bba1;
*((unsigned int *)((unsigned long)context_ptr+0x000061b0+4*8))=0x364c351d;
*((unsigned int *)((unsigned long)context_ptr+0x000061b0+4*9))=0xb23c34ee;
*((unsigned int *)((unsigned long)context_ptr+0x000061b0+4*10))=0xd04ba3f8;
*((unsigned int *)((unsigned long)context_ptr+0x000061b0+4*11))=0xc07ea628;
*((unsigned int *)((unsigned long)context_ptr+0x000061b0+4*12))=0xd7009f7c;
*((unsigned int *)((unsigned long)context_ptr+0x000061b0+4*13))=0x000032b9;
*((unsigned int *)((unsigned long)context_ptr+0x000034f8))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x000034f8+4*1))=0x000064b4;
*((unsigned int *)((unsigned long)context_ptr+0x000034f8+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000034f8+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000034f8+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000034f8+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x000004f8))=0x04c00036;
*((unsigned int *)((unsigned long)context_ptr+0x000004f8+4*1))=0x000061b0;
*((unsigned int *)((unsigned long)context_ptr+0x000004f8+4*2))=0x000063dc;
*((unsigned int *)((unsigned long)context_ptr+0x000004f8+4*3))=0x02220036;
*((unsigned int *)((unsigned long)context_ptr+0x000004f8+4*4))=0x0a0db0eb;
*((unsigned int *)((unsigned long)context_ptr+0x000004f8+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000000f0&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000064dc,"\x8e\x0e\x18\x5b\xbb\xb3\x18\x9c\x62\x17\x50\xe9\x2d\x67\xbf\x53\x5d\xf0\x11\xa2\x22\x8c\x69\x85\xa4\x6c\xe8\x70",28))
printf("strip: 8e0e185bbbb3189c, Pass\n");
else
printf("strip: 8e0e185bbbb3189c, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000063ec))=0x026a1002;
*((unsigned int *)((unsigned long)context_ptr+0x000063ec+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000063ec+4*2))=0x02020037;
*((unsigned int *)((unsigned long)context_ptr+0x000063ec+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x000061e8))=0x9d3431c9;
*((unsigned int *)((unsigned long)context_ptr+0x000061e8+4*1))=0xb0296135;
*((unsigned int *)((unsigned long)context_ptr+0x000061e8+4*2))=0xfc18e89d;
*((unsigned int *)((unsigned long)context_ptr+0x000061e8+4*3))=0xf259074e;
*((unsigned int *)((unsigned long)context_ptr+0x000061e8+4*4))=0xad467e4a;
*((unsigned int *)((unsigned long)context_ptr+0x000061e8+4*5))=0xa01bec5f;
*((unsigned int *)((unsigned long)context_ptr+0x000061e8+4*6))=0xc6885efc;
*((unsigned int *)((unsigned long)context_ptr+0x000061e8+4*7))=0xe1da7925;
*((unsigned int *)((unsigned long)context_ptr+0x000061e8+4*8))=0xae88cc86;
*((unsigned int *)((unsigned long)context_ptr+0x000061e8+4*9))=0x0b1713cf;
*((unsigned int *)((unsigned long)context_ptr+0x000061e8+4*10))=0x5b8138e5;
*((unsigned int *)((unsigned long)context_ptr+0x000061e8+4*11))=0x1bde5963;
*((unsigned int *)((unsigned long)context_ptr+0x000061e8+4*12))=0x789580bd;
*((unsigned int *)((unsigned long)context_ptr+0x000061e8+4*13))=0x00698bc6;
*((unsigned int *)((unsigned long)context_ptr+0x00003510))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003510+4*1))=0x000064d0;
*((unsigned int *)((unsigned long)context_ptr+0x00003510+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003510+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003510+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003510+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000510))=0x04c00037;
*((unsigned int *)((unsigned long)context_ptr+0x00000510+4*1))=0x000061e8;
*((unsigned int *)((unsigned long)context_ptr+0x00000510+4*2))=0x000063ec;
*((unsigned int *)((unsigned long)context_ptr+0x00000510+4*3))=0x02220037;
*((unsigned int *)((unsigned long)context_ptr+0x00000510+4*4))=0x08d6dde2;
*((unsigned int *)((unsigned long)context_ptr+0x00000510+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000000f6&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000064f8,"\x45\x20\xf9\xc3\x8e\x8b\x3c\x71\x41\xd3\x19\xdc\xb4\x48\x36\x11\x65\x8c\x13\x8e\x7c\x5d\xec\xfe\x32\xd3\x12\x08",28))
printf("strip: 4520f9c38e8b3c71, Pass\n");
else
printf("strip: 4520f9c38e8b3c71, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000064ec))=0x026a1002;
*((unsigned int *)((unsigned long)context_ptr+0x000064ec+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000064ec+4*2))=0x02020038;
*((unsigned int *)((unsigned long)context_ptr+0x000064ec+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x00006220))=0x2928d80a;
*((unsigned int *)((unsigned long)context_ptr+0x00006220+4*1))=0xd9afbd36;
*((unsigned int *)((unsigned long)context_ptr+0x00006220+4*2))=0x2929e730;
*((unsigned int *)((unsigned long)context_ptr+0x00006220+4*3))=0xacc2556b;
*((unsigned int *)((unsigned long)context_ptr+0x00006220+4*4))=0x1a861c0f;
*((unsigned int *)((unsigned long)context_ptr+0x00006220+4*5))=0x029eb78f;
*((unsigned int *)((unsigned long)context_ptr+0x00006220+4*6))=0x867541ef;
*((unsigned int *)((unsigned long)context_ptr+0x00006220+4*7))=0xd6a84ffa;
*((unsigned int *)((unsigned long)context_ptr+0x00006220+4*8))=0x21473990;
*((unsigned int *)((unsigned long)context_ptr+0x00006220+4*9))=0xeb547ebb;
*((unsigned int *)((unsigned long)context_ptr+0x00006220+4*10))=0x649e2033;
*((unsigned int *)((unsigned long)context_ptr+0x00006220+4*11))=0x049b9661;
*((unsigned int *)((unsigned long)context_ptr+0x00006220+4*12))=0x36080c19;
*((unsigned int *)((unsigned long)context_ptr+0x00006220+4*13))=0x933113e9;
*((unsigned int *)((unsigned long)context_ptr+0x00003528))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003528+4*1))=0x000065e4;
*((unsigned int *)((unsigned long)context_ptr+0x00003528+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003528+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003528+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003528+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000528))=0x04c00038;
*((unsigned int *)((unsigned long)context_ptr+0x00000528+4*1))=0x00006220;
*((unsigned int *)((unsigned long)context_ptr+0x00000528+4*2))=0x000064ec;
*((unsigned int *)((unsigned long)context_ptr+0x00000528+4*3))=0x02220038;
*((unsigned int *)((unsigned long)context_ptr+0x00000528+4*4))=0x03500002;
*((unsigned int *)((unsigned long)context_ptr+0x00000528+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000000fc&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006514,"\x88\x51\x5e\xc5\xec\x3f\x66\x4a\xa3\xf8\xd6\xcb\x0f\x68\xdf\xe5\xf4\xd8\xf5\xf8\x4c\xe7\xb0\xd6\x57\x54\x5d\xa9",28))
printf("strip: 88515ec5ec3f664a, Pass\n");
else
printf("strip: 88515ec5ec3f664a, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000063fc))=0x026a1002;
*((unsigned int *)((unsigned long)context_ptr+0x000063fc+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000063fc+4*2))=0x02020039;
*((unsigned int *)((unsigned long)context_ptr+0x000063fc+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x00006600))=0x7f39edeb;
*((unsigned int *)((unsigned long)context_ptr+0x00006600+4*1))=0x9a690ca3;
*((unsigned int *)((unsigned long)context_ptr+0x00006600+4*2))=0x50520ad7;
*((unsigned int *)((unsigned long)context_ptr+0x00006600+4*3))=0x7dfd5329;
*((unsigned int *)((unsigned long)context_ptr+0x00006600+4*4))=0xebfcc912;
*((unsigned int *)((unsigned long)context_ptr+0x00006600+4*5))=0x92d2679c;
*((unsigned int *)((unsigned long)context_ptr+0x00006600+4*6))=0xb279aa2d;
*((unsigned int *)((unsigned long)context_ptr+0x00006600+4*7))=0x4a4d4a34;
*((unsigned int *)((unsigned long)context_ptr+0x00006600+4*8))=0x03aa59b4;
*((unsigned int *)((unsigned long)context_ptr+0x00006600+4*9))=0x0cea7706;
*((unsigned int *)((unsigned long)context_ptr+0x00006600+4*10))=0x124fff15;
*((unsigned int *)((unsigned long)context_ptr+0x00006600+4*11))=0x96391410;
*((unsigned int *)((unsigned long)context_ptr+0x00006600+4*12))=0x55f1d708;
*((unsigned int *)((unsigned long)context_ptr+0x00006600+4*13))=0xd4069bd4;
*((unsigned int *)((unsigned long)context_ptr+0x00006600+4*14))=0x000000f9;
*((unsigned int *)((unsigned long)context_ptr+0x00003540))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003540+4*1))=0x000064fc;
*((unsigned int *)((unsigned long)context_ptr+0x00003540+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003540+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003540+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003540+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000540))=0x04c00039;
*((unsigned int *)((unsigned long)context_ptr+0x00000540+4*1))=0x00006600;
*((unsigned int *)((unsigned long)context_ptr+0x00000540+4*2))=0x000063fc;
*((unsigned int *)((unsigned long)context_ptr+0x00000540+4*3))=0x02220039;
*((unsigned int *)((unsigned long)context_ptr+0x00000540+4*4))=0x06776ede;
*((unsigned int *)((unsigned long)context_ptr+0x00000540+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000102&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000062bc,"\xa2\xcc\xb9\xb5\x2e\xb1\x17\xd5\xad\x30\x6d\xba\x1c\x6e\xa2\xe4\xdb\xb5\x1d\x3b\x7e\xe5\xb5\x87\x71\x6d\xd7\xdb",28))
printf("strip: a2ccb9b52eb117d5, Pass\n");
else
printf("strip: a2ccb9b52eb117d5, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006518))=0x026a1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006518+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006518+4*2))=0x0202003a;
*((unsigned int *)((unsigned long)context_ptr+0x00006518+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x00006258))=0x3d73a239;
*((unsigned int *)((unsigned long)context_ptr+0x00006258+4*1))=0x48ad973f;
*((unsigned int *)((unsigned long)context_ptr+0x00006258+4*2))=0x9758f762;
*((unsigned int *)((unsigned long)context_ptr+0x00006258+4*3))=0x5f3b6a74;
*((unsigned int *)((unsigned long)context_ptr+0x00006258+4*4))=0xf4ff74d4;
*((unsigned int *)((unsigned long)context_ptr+0x00006258+4*5))=0x09b42142;
*((unsigned int *)((unsigned long)context_ptr+0x00006258+4*6))=0x753c4a32;
*((unsigned int *)((unsigned long)context_ptr+0x00006258+4*7))=0x2e527cf3;
*((unsigned int *)((unsigned long)context_ptr+0x00006258+4*8))=0x89380080;
*((unsigned int *)((unsigned long)context_ptr+0x00006258+4*9))=0x4f555fdd;
*((unsigned int *)((unsigned long)context_ptr+0x00006258+4*10))=0xace683dd;
*((unsigned int *)((unsigned long)context_ptr+0x00006258+4*11))=0x0e156341;
*((unsigned int *)((unsigned long)context_ptr+0x00006258+4*12))=0x3ad295ed;
*((unsigned int *)((unsigned long)context_ptr+0x00006258+4*13))=0xd0208a8f;
*((unsigned int *)((unsigned long)context_ptr+0x00006258+4*14))=0x0000ebf0;
*((unsigned int *)((unsigned long)context_ptr+0x00003558))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003558+4*1))=0x0000640c;
*((unsigned int *)((unsigned long)context_ptr+0x00003558+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003558+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003558+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003558+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000558))=0x04c0003a;
*((unsigned int *)((unsigned long)context_ptr+0x00000558+4*1))=0x00006258;
*((unsigned int *)((unsigned long)context_ptr+0x00000558+4*2))=0x00006518;
*((unsigned int *)((unsigned long)context_ptr+0x00000558+4*3))=0x0222003a;
*((unsigned int *)((unsigned long)context_ptr+0x00000558+4*4))=0x0f0924e9;
*((unsigned int *)((unsigned long)context_ptr+0x00000558+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000108&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006304,"\x25\x0e\x6c\x68\xbc\x48\x7c\x9b\x67\x98\x51\xef\x0a\x91\x8b\x39\x19\x8b\x4d\xd3\xa3\x82\xd9\x5b\x82\x20\xa7\x72",28))
printf("strip: 250e6c68bc487c9b, Pass\n");
else
printf("strip: 250e6c68bc487c9b, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006428))=0x026a1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006428+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006428+4*2))=0x0202003b;
*((unsigned int *)((unsigned long)context_ptr+0x00006428+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x00006294))=0x3183fa97;
*((unsigned int *)((unsigned long)context_ptr+0x00006294+4*1))=0x7e655f7d;
*((unsigned int *)((unsigned long)context_ptr+0x00006294+4*2))=0xf0b38bd2;
*((unsigned int *)((unsigned long)context_ptr+0x00006294+4*3))=0x9fcaba1e;
*((unsigned int *)((unsigned long)context_ptr+0x00006294+4*4))=0x261850bb;
*((unsigned int *)((unsigned long)context_ptr+0x00006294+4*5))=0x752e7ed5;
*((unsigned int *)((unsigned long)context_ptr+0x00006294+4*6))=0x2f067b86;
*((unsigned int *)((unsigned long)context_ptr+0x00006294+4*7))=0x4fc65799;
*((unsigned int *)((unsigned long)context_ptr+0x00006294+4*8))=0x4d5290c9;
*((unsigned int *)((unsigned long)context_ptr+0x00006294+4*9))=0xebc71267;
*((unsigned int *)((unsigned long)context_ptr+0x00006294+4*10))=0x18c996a3;
*((unsigned int *)((unsigned long)context_ptr+0x00006294+4*11))=0x9027afbf;
*((unsigned int *)((unsigned long)context_ptr+0x00006294+4*12))=0x1a143dcd;
*((unsigned int *)((unsigned long)context_ptr+0x00006294+4*13))=0x7ad5624e;
*((unsigned int *)((unsigned long)context_ptr+0x00006294+4*14))=0x00b33cc3;
*((unsigned int *)((unsigned long)context_ptr+0x00003570))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003570+4*1))=0x000062d0;
*((unsigned int *)((unsigned long)context_ptr+0x00003570+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003570+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003570+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003570+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000570))=0x04c0003b;
*((unsigned int *)((unsigned long)context_ptr+0x00000570+4*1))=0x00006294;
*((unsigned int *)((unsigned long)context_ptr+0x00000570+4*2))=0x00006428;
*((unsigned int *)((unsigned long)context_ptr+0x00000570+4*3))=0x0222003b;
*((unsigned int *)((unsigned long)context_ptr+0x00000570+4*4))=0x0dcb204b;
*((unsigned int *)((unsigned long)context_ptr+0x00000570+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000010e&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006530,"\x1d\x37\x28\xbb\xa6\x61\x39\x59\x2f\xc9\xe0\xd7\x08\x04\x74\x7d\x48\x47\x83\x3d\x9c\x81\x9c\x0b\xae\xc6\x8b\xda",28))
printf("strip: 1d3728bba6613959, Pass\n");
else
printf("strip: 1d3728bba6613959, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006528))=0x026a1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006528+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006528+4*2))=0x0202003c;
*((unsigned int *)((unsigned long)context_ptr+0x00006528+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x000062ec))=0x8263a416;
*((unsigned int *)((unsigned long)context_ptr+0x000062ec+4*1))=0xb54bfe0d;
*((unsigned int *)((unsigned long)context_ptr+0x000062ec+4*2))=0x5a5f2bcd;
*((unsigned int *)((unsigned long)context_ptr+0x000062ec+4*3))=0xa6c1a82b;
*((unsigned int *)((unsigned long)context_ptr+0x000062ec+4*4))=0x7f6a17bc;
*((unsigned int *)((unsigned long)context_ptr+0x000062ec+4*5))=0x868a74f7;
*((unsigned int *)((unsigned long)context_ptr+0x000062ec+4*6))=0xeee4002d;
*((unsigned int *)((unsigned long)context_ptr+0x000062ec+4*7))=0x92e12704;
*((unsigned int *)((unsigned long)context_ptr+0x000062ec+4*8))=0x42cd8515;
*((unsigned int *)((unsigned long)context_ptr+0x000062ec+4*9))=0x0164bc6c;
*((unsigned int *)((unsigned long)context_ptr+0x000062ec+4*10))=0x6ab08d48;
*((unsigned int *)((unsigned long)context_ptr+0x000062ec+4*11))=0xddf9b451;
*((unsigned int *)((unsigned long)context_ptr+0x000062ec+4*12))=0x35a9207e;
*((unsigned int *)((unsigned long)context_ptr+0x000062ec+4*13))=0xb639a03a;
*((unsigned int *)((unsigned long)context_ptr+0x000062ec+4*14))=0x76cd6e81;
*((unsigned int *)((unsigned long)context_ptr+0x00003588))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003588+4*1))=0x00006328;
*((unsigned int *)((unsigned long)context_ptr+0x00003588+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003588+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003588+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003588+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000588))=0x04c0003c;
*((unsigned int *)((unsigned long)context_ptr+0x00000588+4*1))=0x000062ec;
*((unsigned int *)((unsigned long)context_ptr+0x00000588+4*2))=0x00006528;
*((unsigned int *)((unsigned long)context_ptr+0x00000588+4*3))=0x0222003c;
*((unsigned int *)((unsigned long)context_ptr+0x00000588+4*4))=0x0be8b0f6;
*((unsigned int *)((unsigned long)context_ptr+0x00000588+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000114&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006360,"\x7f\x75\x0e\x5b\x48\x2e\x54\x9e\x6a\x54\x03\xeb\x63\x2f\x44\x50\x97\xbe\x5a\x20\xd4\xf6\xa5\xe2\x3a\xe0\x60\x74",28))
printf("strip: 7f750e5b482e549e, Pass\n");
else
printf("strip: 7f750e5b482e549e, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006058))=0x026a1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*2))=0x0202003d;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x0000663c))=0x5b66cd6f;
*((unsigned int *)((unsigned long)context_ptr+0x0000663c+4*1))=0x75a862ad;
*((unsigned int *)((unsigned long)context_ptr+0x0000663c+4*2))=0xf1406791;
*((unsigned int *)((unsigned long)context_ptr+0x0000663c+4*3))=0xa249a296;
*((unsigned int *)((unsigned long)context_ptr+0x0000663c+4*4))=0x418a948d;
*((unsigned int *)((unsigned long)context_ptr+0x0000663c+4*5))=0x4d4f14a7;
*((unsigned int *)((unsigned long)context_ptr+0x0000663c+4*6))=0xda34006f;
*((unsigned int *)((unsigned long)context_ptr+0x0000663c+4*7))=0x839b03ca;
*((unsigned int *)((unsigned long)context_ptr+0x0000663c+4*8))=0x615cbd18;
*((unsigned int *)((unsigned long)context_ptr+0x0000663c+4*9))=0xd7d59b5d;
*((unsigned int *)((unsigned long)context_ptr+0x0000663c+4*10))=0x9f0fe550;
*((unsigned int *)((unsigned long)context_ptr+0x0000663c+4*11))=0x6a6af4b3;
*((unsigned int *)((unsigned long)context_ptr+0x0000663c+4*12))=0x59f757a0;
*((unsigned int *)((unsigned long)context_ptr+0x0000663c+4*13))=0xff415625;
*((unsigned int *)((unsigned long)context_ptr+0x0000663c+4*14))=0x4846bbe3;
*((unsigned int *)((unsigned long)context_ptr+0x0000663c+4*15))=0x00000026;
*((unsigned int *)((unsigned long)context_ptr+0x000035a0))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x000035a0+4*1))=0x00006438;
*((unsigned int *)((unsigned long)context_ptr+0x000035a0+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000035a0+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000035a0+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000035a0+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x000005a0))=0x04c0003d;
*((unsigned int *)((unsigned long)context_ptr+0x000005a0+4*1))=0x0000663c;
*((unsigned int *)((unsigned long)context_ptr+0x000005a0+4*2))=0x00006058;
*((unsigned int *)((unsigned long)context_ptr+0x000005a0+4*3))=0x0222003d;
*((unsigned int *)((unsigned long)context_ptr+0x000005a0+4*4))=0x01ac45ec;
*((unsigned int *)((unsigned long)context_ptr+0x000005a0+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000011a&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006078,"\xe1\x43\x64\xa6\x65\x82\x95\x79\xbc\x31\xdc\xa8\x86\x4d\xde\x0b\x77\x3e\xb3\x8d\xe0\x99\x0c\xf2\x45\x80\x69\x26",28))
printf("strip: e14364a665829579, Pass\n");
else
printf("strip: e14364a665829579, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006048))=0x026a1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006048+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006048+4*2))=0x0202003e;
*((unsigned int *)((unsigned long)context_ptr+0x00006048+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x00006538))=0xe7f61d4f;
*((unsigned int *)((unsigned long)context_ptr+0x00006538+4*1))=0x77e370b0;
*((unsigned int *)((unsigned long)context_ptr+0x00006538+4*2))=0xc42deca4;
*((unsigned int *)((unsigned long)context_ptr+0x00006538+4*3))=0x548f69ef;
*((unsigned int *)((unsigned long)context_ptr+0x00006538+4*4))=0x643e55ee;
*((unsigned int *)((unsigned long)context_ptr+0x00006538+4*5))=0xb6182818;
*((unsigned int *)((unsigned long)context_ptr+0x00006538+4*6))=0x4cb00955;
*((unsigned int *)((unsigned long)context_ptr+0x00006538+4*7))=0xee95eacf;
*((unsigned int *)((unsigned long)context_ptr+0x00006538+4*8))=0x05b664ec;
*((unsigned int *)((unsigned long)context_ptr+0x00006538+4*9))=0x4c91f7a1;
*((unsigned int *)((unsigned long)context_ptr+0x00006538+4*10))=0x724b618a;
*((unsigned int *)((unsigned long)context_ptr+0x00006538+4*11))=0x043d7939;
*((unsigned int *)((unsigned long)context_ptr+0x00006538+4*12))=0x0a4c6c05;
*((unsigned int *)((unsigned long)context_ptr+0x00006538+4*13))=0xd24e19d1;
*((unsigned int *)((unsigned long)context_ptr+0x00006538+4*14))=0x42c46dbc;
*((unsigned int *)((unsigned long)context_ptr+0x00006538+4*15))=0x0000cf6b;
*((unsigned int *)((unsigned long)context_ptr+0x000035b8))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x000035b8+4*1))=0x00006078;
*((unsigned int *)((unsigned long)context_ptr+0x000035b8+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000035b8+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000035b8+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000035b8+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x000005b8))=0x04c0003e;
*((unsigned int *)((unsigned long)context_ptr+0x000005b8+4*1))=0x00006538;
*((unsigned int *)((unsigned long)context_ptr+0x000005b8+4*2))=0x00006048;
*((unsigned int *)((unsigned long)context_ptr+0x000005b8+4*3))=0x0222003e;
*((unsigned int *)((unsigned long)context_ptr+0x000005b8+4*4))=0x06fda1a8;
*((unsigned int *)((unsigned long)context_ptr+0x000005b8+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000120&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006468,"\xda\x7b\x42\xab\x34\xc3\x5d\x7e\x86\x0c\x2d\x27\x03\xed\xcb\xbe\xee\xea\x93\x6c\x99\x16\x2e\xfd\xbb\xaf\x9e\x02",28))
printf("strip: da7b42ab34c35d7e, Pass\n");
else
printf("strip: da7b42ab34c35d7e, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006068))=0x026a1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006068+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006068+4*2))=0x0202003f;
*((unsigned int *)((unsigned long)context_ptr+0x00006068+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x0000667c))=0x9218aabe;
*((unsigned int *)((unsigned long)context_ptr+0x0000667c+4*1))=0x9b156f08;
*((unsigned int *)((unsigned long)context_ptr+0x0000667c+4*2))=0x15aabc08;
*((unsigned int *)((unsigned long)context_ptr+0x0000667c+4*3))=0xe8bec521;
*((unsigned int *)((unsigned long)context_ptr+0x0000667c+4*4))=0x79f43459;
*((unsigned int *)((unsigned long)context_ptr+0x0000667c+4*5))=0x39ce1791;
*((unsigned int *)((unsigned long)context_ptr+0x0000667c+4*6))=0x9a2876f3;
*((unsigned int *)((unsigned long)context_ptr+0x0000667c+4*7))=0x817c1c3f;
*((unsigned int *)((unsigned long)context_ptr+0x0000667c+4*8))=0xd337e6b6;
*((unsigned int *)((unsigned long)context_ptr+0x0000667c+4*9))=0x62c02074;
*((unsigned int *)((unsigned long)context_ptr+0x0000667c+4*10))=0x943f008f;
*((unsigned int *)((unsigned long)context_ptr+0x0000667c+4*11))=0x38862107;
*((unsigned int *)((unsigned long)context_ptr+0x0000667c+4*12))=0x5f2ae4b4;
*((unsigned int *)((unsigned long)context_ptr+0x0000667c+4*13))=0x24b6f012;
*((unsigned int *)((unsigned long)context_ptr+0x0000667c+4*14))=0x284c9d3b;
*((unsigned int *)((unsigned long)context_ptr+0x0000667c+4*15))=0x00b346d5;
*((unsigned int *)((unsigned long)context_ptr+0x000035d0))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x000035d0+4*1))=0x00006454;
*((unsigned int *)((unsigned long)context_ptr+0x000035d0+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000035d0+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000035d0+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000035d0+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x000005d0))=0x04c0003f;
*((unsigned int *)((unsigned long)context_ptr+0x000005d0+4*1))=0x0000667c;
*((unsigned int *)((unsigned long)context_ptr+0x000005d0+4*2))=0x00006068;
*((unsigned int *)((unsigned long)context_ptr+0x000005d0+4*3))=0x0222003f;
*((unsigned int *)((unsigned long)context_ptr+0x000005d0+4*4))=0x0dd61881;
*((unsigned int *)((unsigned long)context_ptr+0x000005d0+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000126&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006094,"\x67\xd6\x36\x4f\x74\x89\xd7\xa3\x2a\x94\xb1\xf1\xbb\xce\x9e\x84\xfe\xda\xdc\x77\x42\xc0\xc9\xab\x8a\xcc\x2f\xcc",28))
printf("strip: 67d6364f7489d7a3, Pass\n");
else
printf("strip: 67d6364f7489d7a3, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006094))=0x026a1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006094+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006094+4*2))=0x02020040;
*((unsigned int *)((unsigned long)context_ptr+0x00006094+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x00006344))=0xc5e51953;
*((unsigned int *)((unsigned long)context_ptr+0x00006344+4*1))=0x67dd0f05;
*((unsigned int *)((unsigned long)context_ptr+0x00006344+4*2))=0xfbff9001;
*((unsigned int *)((unsigned long)context_ptr+0x00006344+4*3))=0xd12fbc3e;
*((unsigned int *)((unsigned long)context_ptr+0x00006344+4*4))=0xd4afd19d;
*((unsigned int *)((unsigned long)context_ptr+0x00006344+4*5))=0x1f2f4523;
*((unsigned int *)((unsigned long)context_ptr+0x00006344+4*6))=0x58731538;
*((unsigned int *)((unsigned long)context_ptr+0x00006344+4*7))=0x0bb33202;
*((unsigned int *)((unsigned long)context_ptr+0x00006344+4*8))=0x09eadb04;
*((unsigned int *)((unsigned long)context_ptr+0x00006344+4*9))=0xa0945b42;
*((unsigned int *)((unsigned long)context_ptr+0x00006344+4*10))=0x606645f6;
*((unsigned int *)((unsigned long)context_ptr+0x00006344+4*11))=0xa9e831d6;
*((unsigned int *)((unsigned long)context_ptr+0x00006344+4*12))=0x0b32b87d;
*((unsigned int *)((unsigned long)context_ptr+0x00006344+4*13))=0x9fdf5bdd;
*((unsigned int *)((unsigned long)context_ptr+0x00006344+4*14))=0x624de195;
*((unsigned int *)((unsigned long)context_ptr+0x00006344+4*15))=0xebc9e8d8;
*((unsigned int *)((unsigned long)context_ptr+0x000035e8))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x000035e8+4*1))=0x00006470;
*((unsigned int *)((unsigned long)context_ptr+0x000035e8+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000035e8+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000035e8+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000035e8+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x000005e8))=0x04c00040;
*((unsigned int *)((unsigned long)context_ptr+0x000005e8+4*1))=0x00006344;
*((unsigned int *)((unsigned long)context_ptr+0x000005e8+4*2))=0x00006094;
*((unsigned int *)((unsigned long)context_ptr+0x000005e8+4*3))=0x02220040;
*((unsigned int *)((unsigned long)context_ptr+0x000005e8+4*4))=0x0d925f55;
*((unsigned int *)((unsigned long)context_ptr+0x000005e8+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000012c&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000060e4,"\x7b\x24\xe2\x5c\xda\x4b\x53\xd1\x01\x9c\xaf\x69\x36\xdf\xba\xce\x73\x36\x6f\x50\xd0\x46\x59\xbe\x06\x20\xea\x2e",28))
printf("strip: 7b24e25cda4b53d1, Pass\n");
else
printf("strip: 7b24e25cda4b53d1, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x0000648c))=0x026a1002;
*((unsigned int *)((unsigned long)context_ptr+0x0000648c+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x0000648c+4*2))=0x02020041;
*((unsigned int *)((unsigned long)context_ptr+0x0000648c+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x000060a4))=0xe7e614cb;
*((unsigned int *)((unsigned long)context_ptr+0x000060a4+4*1))=0x127ab2b3;
*((unsigned int *)((unsigned long)context_ptr+0x000060a4+4*2))=0x4e96c258;
*((unsigned int *)((unsigned long)context_ptr+0x000060a4+4*3))=0xb388352c;
*((unsigned int *)((unsigned long)context_ptr+0x000060a4+4*4))=0xa2b4c7f1;
*((unsigned int *)((unsigned long)context_ptr+0x000060a4+4*5))=0x66c89cff;
*((unsigned int *)((unsigned long)context_ptr+0x000060a4+4*6))=0x82ca5d23;
*((unsigned int *)((unsigned long)context_ptr+0x000060a4+4*7))=0xbf5c357e;
*((unsigned int *)((unsigned long)context_ptr+0x000060a4+4*8))=0xeef52c6a;
*((unsigned int *)((unsigned long)context_ptr+0x000060a4+4*9))=0x12fc7ddc;
*((unsigned int *)((unsigned long)context_ptr+0x000060a4+4*10))=0x8f5808a7;
*((unsigned int *)((unsigned long)context_ptr+0x000060a4+4*11))=0xe2ef6f7b;
*((unsigned int *)((unsigned long)context_ptr+0x000060a4+4*12))=0xa933c7e3;
*((unsigned int *)((unsigned long)context_ptr+0x000060a4+4*13))=0x9858e35e;
*((unsigned int *)((unsigned long)context_ptr+0x000060a4+4*14))=0x5b1f54d3;
*((unsigned int *)((unsigned long)context_ptr+0x000060a4+4*15))=0xdcfa5945;
*((unsigned int *)((unsigned long)context_ptr+0x000060a4+4*16))=0x00000095;
*((unsigned int *)((unsigned long)context_ptr+0x00003600))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003600+4*1))=0x00006384;
*((unsigned int *)((unsigned long)context_ptr+0x00003600+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003600+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003600+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003600+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000600))=0x04c00041;
*((unsigned int *)((unsigned long)context_ptr+0x00000600+4*1))=0x000060a4;
*((unsigned int *)((unsigned long)context_ptr+0x00000600+4*2))=0x0000648c;
*((unsigned int *)((unsigned long)context_ptr+0x00000600+4*3))=0x02220041;
*((unsigned int *)((unsigned long)context_ptr+0x00000600+4*4))=0x0ee663bc;
*((unsigned int *)((unsigned long)context_ptr+0x00000600+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000132&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000063b0,"\xe6\x78\xa8\x00\xf1\x5a\x46\x9c\x26\x09\x60\xfc\x81\x24\xac\xb6\xff\x3e\x51\x55\x48\x2c\xc0\x27\xf4\x71\xdb\xfb",28))
printf("strip: e678a800f15a469c, Pass\n");
else
printf("strip: e678a800f15a469c, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x0000649c))=0x026a1002;
*((unsigned int *)((unsigned long)context_ptr+0x0000649c+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x0000649c+4*2))=0x02020042;
*((unsigned int *)((unsigned long)context_ptr+0x0000649c+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x000060e8))=0x3016f809;
*((unsigned int *)((unsigned long)context_ptr+0x000060e8+4*1))=0xa750d746;
*((unsigned int *)((unsigned long)context_ptr+0x000060e8+4*2))=0x833a8bd8;
*((unsigned int *)((unsigned long)context_ptr+0x000060e8+4*3))=0x662e5d05;
*((unsigned int *)((unsigned long)context_ptr+0x000060e8+4*4))=0xceb0ab0f;
*((unsigned int *)((unsigned long)context_ptr+0x000060e8+4*5))=0xfb251f98;
*((unsigned int *)((unsigned long)context_ptr+0x000060e8+4*6))=0x527ca9b2;
*((unsigned int *)((unsigned long)context_ptr+0x000060e8+4*7))=0x583ff0d9;
*((unsigned int *)((unsigned long)context_ptr+0x000060e8+4*8))=0xbe93fc51;
*((unsigned int *)((unsigned long)context_ptr+0x000060e8+4*9))=0xd0be5355;
*((unsigned int *)((unsigned long)context_ptr+0x000060e8+4*10))=0x4da6e024;
*((unsigned int *)((unsigned long)context_ptr+0x000060e8+4*11))=0x7085f232;
*((unsigned int *)((unsigned long)context_ptr+0x000060e8+4*12))=0xe902a94e;
*((unsigned int *)((unsigned long)context_ptr+0x000060e8+4*13))=0x990f009d;
*((unsigned int *)((unsigned long)context_ptr+0x000060e8+4*14))=0xc9df543d;
*((unsigned int *)((unsigned long)context_ptr+0x000060e8+4*15))=0x4794e083;
*((unsigned int *)((unsigned long)context_ptr+0x000060e8+4*16))=0x00000ff9;
*((unsigned int *)((unsigned long)context_ptr+0x00003618))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003618+4*1))=0x000063a0;
*((unsigned int *)((unsigned long)context_ptr+0x00003618+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003618+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003618+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003618+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000618))=0x04c00042;
*((unsigned int *)((unsigned long)context_ptr+0x00000618+4*1))=0x000060e8;
*((unsigned int *)((unsigned long)context_ptr+0x00000618+4*2))=0x0000649c;
*((unsigned int *)((unsigned long)context_ptr+0x00000618+4*3))=0x02220042;
*((unsigned int *)((unsigned long)context_ptr+0x00000618+4*4))=0x08d05f9c;
*((unsigned int *)((unsigned long)context_ptr+0x00000618+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000138&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006178,"\x3f\x9b\x58\xbe\x2e\x3b\x60\x12\xf7\x19\x2c\x64\x92\x77\x1e\x52\xb6\x73\xe0\x31\x3d\x32\xd4\x54\x11\x01\x0f\x5c",28))
printf("strip: 3f9b58be2e3b6012, Pass\n");
else
printf("strip: 3f9b58be2e3b6012, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000063bc))=0x026a1002;
*((unsigned int *)((unsigned long)context_ptr+0x000063bc+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000063bc+4*2))=0x02020043;
*((unsigned int *)((unsigned long)context_ptr+0x000063bc+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x0000612c))=0x762a8093;
*((unsigned int *)((unsigned long)context_ptr+0x0000612c+4*1))=0x4e5e41d9;
*((unsigned int *)((unsigned long)context_ptr+0x0000612c+4*2))=0xf5859c63;
*((unsigned int *)((unsigned long)context_ptr+0x0000612c+4*3))=0x4b044d78;
*((unsigned int *)((unsigned long)context_ptr+0x0000612c+4*4))=0x7b92fed5;
*((unsigned int *)((unsigned long)context_ptr+0x0000612c+4*5))=0xcf595462;
*((unsigned int *)((unsigned long)context_ptr+0x0000612c+4*6))=0xe1249358;
*((unsigned int *)((unsigned long)context_ptr+0x0000612c+4*7))=0x2a40754e;
*((unsigned int *)((unsigned long)context_ptr+0x0000612c+4*8))=0x0aedb4f0;
*((unsigned int *)((unsigned long)context_ptr+0x0000612c+4*9))=0xb7f6998d;
*((unsigned int *)((unsigned long)context_ptr+0x0000612c+4*10))=0x97e544a2;
*((unsigned int *)((unsigned long)context_ptr+0x0000612c+4*11))=0x19dca300;
*((unsigned int *)((unsigned long)context_ptr+0x0000612c+4*12))=0x630a8b31;
*((unsigned int *)((unsigned long)context_ptr+0x0000612c+4*13))=0x19d93e93;
*((unsigned int *)((unsigned long)context_ptr+0x0000612c+4*14))=0xa7d535cd;
*((unsigned int *)((unsigned long)context_ptr+0x0000612c+4*15))=0x29d285be;
*((unsigned int *)((unsigned long)context_ptr+0x0000612c+4*16))=0x004004c0;
*((unsigned int *)((unsigned long)context_ptr+0x00003630))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003630+4*1))=0x00006170;
*((unsigned int *)((unsigned long)context_ptr+0x00003630+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003630+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003630+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003630+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000630))=0x04c00043;
*((unsigned int *)((unsigned long)context_ptr+0x00000630+4*1))=0x0000612c;
*((unsigned int *)((unsigned long)context_ptr+0x00000630+4*2))=0x000063bc;
*((unsigned int *)((unsigned long)context_ptr+0x00000630+4*3))=0x02220043;
*((unsigned int *)((unsigned long)context_ptr+0x00000630+4*4))=0x046b8203;
*((unsigned int *)((unsigned long)context_ptr+0x00000630+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000013e&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006194,"\xb6\xcb\x30\x3c\xe7\x11\x5f\x6b\xf6\x56\x80\xa8\x34\x3e\x22\x3a\xeb\xfd\x6c\x8f\x49\x58\xf2\x3b\xf1\x66\xc6\x95",28))
printf("strip: b6cb303ce7115f6b, Pass\n");
else
printf("strip: b6cb303ce7115f6b, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000063cc))=0x026a1002;
*((unsigned int *)((unsigned long)context_ptr+0x000063cc+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000063cc+4*2))=0x02020044;
*((unsigned int *)((unsigned long)context_ptr+0x000063cc+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x00006578))=0x271135b7;
*((unsigned int *)((unsigned long)context_ptr+0x00006578+4*1))=0xf4c732c7;
*((unsigned int *)((unsigned long)context_ptr+0x00006578+4*2))=0xbbc8ceb4;
*((unsigned int *)((unsigned long)context_ptr+0x00006578+4*3))=0x667602b1;
*((unsigned int *)((unsigned long)context_ptr+0x00006578+4*4))=0xba70c4c8;
*((unsigned int *)((unsigned long)context_ptr+0x00006578+4*5))=0x7612dc2c;
*((unsigned int *)((unsigned long)context_ptr+0x00006578+4*6))=0x1e62d653;
*((unsigned int *)((unsigned long)context_ptr+0x00006578+4*7))=0xbae92eaf;
*((unsigned int *)((unsigned long)context_ptr+0x00006578+4*8))=0x69f44fbd;
*((unsigned int *)((unsigned long)context_ptr+0x00006578+4*9))=0xefd3a744;
*((unsigned int *)((unsigned long)context_ptr+0x00006578+4*10))=0xed16bd6a;
*((unsigned int *)((unsigned long)context_ptr+0x00006578+4*11))=0x634b8a02;
*((unsigned int *)((unsigned long)context_ptr+0x00006578+4*12))=0x7ace7e71;
*((unsigned int *)((unsigned long)context_ptr+0x00006578+4*13))=0xd25c0681;
*((unsigned int *)((unsigned long)context_ptr+0x00006578+4*14))=0x476ee04e;
*((unsigned int *)((unsigned long)context_ptr+0x00006578+4*15))=0x349c3d20;
*((unsigned int *)((unsigned long)context_ptr+0x00006578+4*16))=0xf47eddf9;
*((unsigned int *)((unsigned long)context_ptr+0x00003648))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003648+4*1))=0x0000618c;
*((unsigned int *)((unsigned long)context_ptr+0x00003648+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003648+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003648+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003648+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000648))=0x04c00044;
*((unsigned int *)((unsigned long)context_ptr+0x00000648+4*1))=0x00006578;
*((unsigned int *)((unsigned long)context_ptr+0x00000648+4*2))=0x000063cc;
*((unsigned int *)((unsigned long)context_ptr+0x00000648+4*3))=0x02220044;
*((unsigned int *)((unsigned long)context_ptr+0x00000648+4*4))=0x078c0aef;
*((unsigned int *)((unsigned long)context_ptr+0x00000648+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000144&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000064b4,"\x70\xea\xb3\x76\x65\x7e\x1d\xe2\x1d\x6d\x12\x96\xc4\xc3\x67\x39\xb2\xc9\x6b\x2d\x6b\x1c\x05\xf7\x7e\x87\x2d\x64",28))
printf("strip: 70eab376657e1de2, Pass\n");
else
printf("strip: 70eab376657e1de2, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000063dc))=0x026a1002;
*((unsigned int *)((unsigned long)context_ptr+0x000063dc+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000063dc+4*2))=0x02020045;
*((unsigned int *)((unsigned long)context_ptr+0x000063dc+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x000066bc))=0xcc21816b;
*((unsigned int *)((unsigned long)context_ptr+0x000066bc+4*1))=0x11e9127d;
*((unsigned int *)((unsigned long)context_ptr+0x000066bc+4*2))=0x538b0007;
*((unsigned int *)((unsigned long)context_ptr+0x000066bc+4*3))=0x12780b10;
*((unsigned int *)((unsigned long)context_ptr+0x000066bc+4*4))=0x074fbe33;
*((unsigned int *)((unsigned long)context_ptr+0x000066bc+4*5))=0xc2a3eef5;
*((unsigned int *)((unsigned long)context_ptr+0x000066bc+4*6))=0xf9a058ed;
*((unsigned int *)((unsigned long)context_ptr+0x000066bc+4*7))=0xea73dc0f;
*((unsigned int *)((unsigned long)context_ptr+0x000066bc+4*8))=0xee840b60;
*((unsigned int *)((unsigned long)context_ptr+0x000066bc+4*9))=0x8dad3d8d;
*((unsigned int *)((unsigned long)context_ptr+0x000066bc+4*10))=0x02383d8d;
*((unsigned int *)((unsigned long)context_ptr+0x000066bc+4*11))=0x73e6c0f8;
*((unsigned int *)((unsigned long)context_ptr+0x000066bc+4*12))=0xdff9793c;
*((unsigned int *)((unsigned long)context_ptr+0x000066bc+4*13))=0x926eadba;
*((unsigned int *)((unsigned long)context_ptr+0x000066bc+4*14))=0xbb113dc2;
*((unsigned int *)((unsigned long)context_ptr+0x000066bc+4*15))=0xb549a97b;
*((unsigned int *)((unsigned long)context_ptr+0x000066bc+4*16))=0xd0019add;
*((unsigned int *)((unsigned long)context_ptr+0x000066bc+4*17))=0x00000039;
*((unsigned int *)((unsigned long)context_ptr+0x00003660))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003660+4*1))=0x000064ac;
*((unsigned int *)((unsigned long)context_ptr+0x00003660+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003660+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003660+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003660+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000660))=0x04c00045;
*((unsigned int *)((unsigned long)context_ptr+0x00000660+4*1))=0x000066bc;
*((unsigned int *)((unsigned long)context_ptr+0x00000660+4*2))=0x000063dc;
*((unsigned int *)((unsigned long)context_ptr+0x00000660+4*3))=0x02220045;
*((unsigned int *)((unsigned long)context_ptr+0x00000660+4*4))=0x0658df18;
*((unsigned int *)((unsigned long)context_ptr+0x00000660+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000014a&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000064d0,"\xda\xd5\xd8\x6c\x74\x3b\xd0\x21\x99\x73\xd6\x48\xf7\x73\xd7\xd3\x25\x33\xb4\xfa\x5e\x7b\x37\xc3\x13\x39\xce\xba",28))
printf("strip: dad5d86c743bd021, Pass\n");
else
printf("strip: dad5d86c743bd021, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000063ec))=0x026a1002;
*((unsigned int *)((unsigned long)context_ptr+0x000063ec+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000063ec+4*2))=0x02020046;
*((unsigned int *)((unsigned long)context_ptr+0x000063ec+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x000061a8))=0xa6893f7f;
*((unsigned int *)((unsigned long)context_ptr+0x000061a8+4*1))=0xea38b59e;
*((unsigned int *)((unsigned long)context_ptr+0x000061a8+4*2))=0x1698467f;
*((unsigned int *)((unsigned long)context_ptr+0x000061a8+4*3))=0x1bd94104;
*((unsigned int *)((unsigned long)context_ptr+0x000061a8+4*4))=0x3a93bf88;
*((unsigned int *)((unsigned long)context_ptr+0x000061a8+4*5))=0x5a1e697d;
*((unsigned int *)((unsigned long)context_ptr+0x000061a8+4*6))=0xd9270cfd;
*((unsigned int *)((unsigned long)context_ptr+0x000061a8+4*7))=0xddd81bda;
*((unsigned int *)((unsigned long)context_ptr+0x000061a8+4*8))=0x067e2c7c;
*((unsigned int *)((unsigned long)context_ptr+0x000061a8+4*9))=0x965431c5;
*((unsigned int *)((unsigned long)context_ptr+0x000061a8+4*10))=0x97623da7;
*((unsigned int *)((unsigned long)context_ptr+0x000061a8+4*11))=0xa685db44;
*((unsigned int *)((unsigned long)context_ptr+0x000061a8+4*12))=0x43d414da;
*((unsigned int *)((unsigned long)context_ptr+0x000061a8+4*13))=0xc06eae35;
*((unsigned int *)((unsigned long)context_ptr+0x000061a8+4*14))=0xbd7aa017;
*((unsigned int *)((unsigned long)context_ptr+0x000061a8+4*15))=0xfea61206;
*((unsigned int *)((unsigned long)context_ptr+0x000061a8+4*16))=0xd00d401c;
*((unsigned int *)((unsigned long)context_ptr+0x000061a8+4*17))=0x0000b71b;
*((unsigned int *)((unsigned long)context_ptr+0x00003678))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003678+4*1))=0x000064c8;
*((unsigned int *)((unsigned long)context_ptr+0x00003678+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003678+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003678+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003678+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000678))=0x04c00046;
*((unsigned int *)((unsigned long)context_ptr+0x00000678+4*1))=0x000061a8;
*((unsigned int *)((unsigned long)context_ptr+0x00000678+4*2))=0x000063ec;
*((unsigned int *)((unsigned long)context_ptr+0x00000678+4*3))=0x02220046;
*((unsigned int *)((unsigned long)context_ptr+0x00000678+4*4))=0x05fb786f;
*((unsigned int *)((unsigned long)context_ptr+0x00000678+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000150&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000065e4,"\xb8\x23\x23\x0e\xd8\xc7\x61\xf0\xf1\x83\x48\x15\xaa\xfc\xaa\x06\x64\x8c\x2e\x77\x0b\x0a\x78\x30\xc9\xd3\xfc\x60",28))
printf("strip: b823230ed8c761f0, Pass\n");
else
printf("strip: b823230ed8c761f0, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000064e4))=0x026a1002;
*((unsigned int *)((unsigned long)context_ptr+0x000064e4+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000064e4+4*2))=0x02020047;
*((unsigned int *)((unsigned long)context_ptr+0x000064e4+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x000061f0))=0xcaa737a8;
*((unsigned int *)((unsigned long)context_ptr+0x000061f0+4*1))=0xb489dbe7;
*((unsigned int *)((unsigned long)context_ptr+0x000061f0+4*2))=0x6f9caa59;
*((unsigned int *)((unsigned long)context_ptr+0x000061f0+4*3))=0xd2ef7b61;
*((unsigned int *)((unsigned long)context_ptr+0x000061f0+4*4))=0xfa66cd01;
*((unsigned int *)((unsigned long)context_ptr+0x000061f0+4*5))=0x447dd921;
*((unsigned int *)((unsigned long)context_ptr+0x000061f0+4*6))=0x6ac98fec;
*((unsigned int *)((unsigned long)context_ptr+0x000061f0+4*7))=0x2d6ae053;
*((unsigned int *)((unsigned long)context_ptr+0x000061f0+4*8))=0xace9bea7;
*((unsigned int *)((unsigned long)context_ptr+0x000061f0+4*9))=0xd1963151;
*((unsigned int *)((unsigned long)context_ptr+0x000061f0+4*10))=0x8fdac51b;
*((unsigned int *)((unsigned long)context_ptr+0x000061f0+4*11))=0x4cbefca0;
*((unsigned int *)((unsigned long)context_ptr+0x000061f0+4*12))=0xeb5c96cc;
*((unsigned int *)((unsigned long)context_ptr+0x000061f0+4*13))=0xe9f89756;
*((unsigned int *)((unsigned long)context_ptr+0x000061f0+4*14))=0xac3f59f3;
*((unsigned int *)((unsigned long)context_ptr+0x000061f0+4*15))=0xd553e233;
*((unsigned int *)((unsigned long)context_ptr+0x000061f0+4*16))=0x405ff1ef;
*((unsigned int *)((unsigned long)context_ptr+0x000061f0+4*17))=0x00fd06a1;
*((unsigned int *)((unsigned long)context_ptr+0x00003690))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003690+4*1))=0x00006238;
*((unsigned int *)((unsigned long)context_ptr+0x00003690+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003690+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003690+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003690+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000690))=0x04c00047;
*((unsigned int *)((unsigned long)context_ptr+0x00000690+4*1))=0x000061f0;
*((unsigned int *)((unsigned long)context_ptr+0x00000690+4*2))=0x000064e4;
*((unsigned int *)((unsigned long)context_ptr+0x00000690+4*3))=0x02220047;
*((unsigned int *)((unsigned long)context_ptr+0x00000690+4*4))=0x046a5525;
*((unsigned int *)((unsigned long)context_ptr+0x00000690+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000156&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000064fc,"\x61\x01\xbe\x38\x9b\xb9\xa5\xf4\x4f\x26\x20\x1b\x9a\x5a\xee\x69\xb0\x84\x93\xac\xd0\xa0\x16\x88\x78\x50\x61\x0a",28))
printf("strip: 6101be389bb9a5f4, Pass\n");
else
printf("strip: 6101be389bb9a5f4, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000063fc))=0x026a1002;
*((unsigned int *)((unsigned long)context_ptr+0x000063fc+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000063fc+4*2))=0x02020048;
*((unsigned int *)((unsigned long)context_ptr+0x000063fc+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x000065bc))=0x0372e1b5;
*((unsigned int *)((unsigned long)context_ptr+0x000065bc+4*1))=0x367f29ca;
*((unsigned int *)((unsigned long)context_ptr+0x000065bc+4*2))=0x7f25c75a;
*((unsigned int *)((unsigned long)context_ptr+0x000065bc+4*3))=0xaf532f7e;
*((unsigned int *)((unsigned long)context_ptr+0x000065bc+4*4))=0x7013d127;
*((unsigned int *)((unsigned long)context_ptr+0x000065bc+4*5))=0x72be6c88;
*((unsigned int *)((unsigned long)context_ptr+0x000065bc+4*6))=0x471bae89;
*((unsigned int *)((unsigned long)context_ptr+0x000065bc+4*7))=0x307fed94;
*((unsigned int *)((unsigned long)context_ptr+0x000065bc+4*8))=0x971f072f;
*((unsigned int *)((unsigned long)context_ptr+0x000065bc+4*9))=0x4c54281d;
*((unsigned int *)((unsigned long)context_ptr+0x000065bc+4*10))=0x578b1ce4;
*((unsigned int *)((unsigned long)context_ptr+0x000065bc+4*11))=0x5625e2a0;
*((unsigned int *)((unsigned long)context_ptr+0x000065bc+4*12))=0x01493fc5;
*((unsigned int *)((unsigned long)context_ptr+0x000065bc+4*13))=0xa39fc740;
*((unsigned int *)((unsigned long)context_ptr+0x000065bc+4*14))=0x06f4b435;
*((unsigned int *)((unsigned long)context_ptr+0x000065bc+4*15))=0xc9826773;
*((unsigned int *)((unsigned long)context_ptr+0x000065bc+4*16))=0xadabf9ba;
*((unsigned int *)((unsigned long)context_ptr+0x000065bc+4*17))=0x326d457b;
*((unsigned int *)((unsigned long)context_ptr+0x000036a8))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x000036a8+4*1))=0x000064f4;
*((unsigned int *)((unsigned long)context_ptr+0x000036a8+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000036a8+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000036a8+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000036a8+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x000006a8))=0x04c00048;
*((unsigned int *)((unsigned long)context_ptr+0x000006a8+4*1))=0x000065bc;
*((unsigned int *)((unsigned long)context_ptr+0x000006a8+4*2))=0x000063fc;
*((unsigned int *)((unsigned long)context_ptr+0x000006a8+4*3))=0x02220048;
*((unsigned int *)((unsigned long)context_ptr+0x000006a8+4*4))=0x0599691d;
*((unsigned int *)((unsigned long)context_ptr+0x000006a8+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000015c&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x0000640c,"\xff\x5b\x19\x27\x3c\xfb\x4d\x49\x09\x57\xbc\x1e\x3c\x59\x76\x97\x20\xe5\xad\x5f\xd6\x21\x73\xd1\x9d\x13\x1a\xe3",28))
printf("strip: ff5b19273cfb4d49, Pass\n");
else
printf("strip: ff5b19273cfb4d49, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006510))=0x026a1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006510+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006510+4*2))=0x02020049;
*((unsigned int *)((unsigned long)context_ptr+0x00006510+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x00006704))=0x07b14820;
*((unsigned int *)((unsigned long)context_ptr+0x00006704+4*1))=0xb28cffbd;
*((unsigned int *)((unsigned long)context_ptr+0x00006704+4*2))=0xee240e5f;
*((unsigned int *)((unsigned long)context_ptr+0x00006704+4*3))=0x0fcc1974;
*((unsigned int *)((unsigned long)context_ptr+0x00006704+4*4))=0x2cea613a;
*((unsigned int *)((unsigned long)context_ptr+0x00006704+4*5))=0xf05d82c3;
*((unsigned int *)((unsigned long)context_ptr+0x00006704+4*6))=0x7da91207;
*((unsigned int *)((unsigned long)context_ptr+0x00006704+4*7))=0x198b19bd;
*((unsigned int *)((unsigned long)context_ptr+0x00006704+4*8))=0x29a65c7b;
*((unsigned int *)((unsigned long)context_ptr+0x00006704+4*9))=0x7f34e986;
*((unsigned int *)((unsigned long)context_ptr+0x00006704+4*10))=0x770fe56d;
*((unsigned int *)((unsigned long)context_ptr+0x00006704+4*11))=0x127cfcfe;
*((unsigned int *)((unsigned long)context_ptr+0x00006704+4*12))=0xdf1be762;
*((unsigned int *)((unsigned long)context_ptr+0x00006704+4*13))=0x1f4d4cc3;
*((unsigned int *)((unsigned long)context_ptr+0x00006704+4*14))=0x61be6cb8;
*((unsigned int *)((unsigned long)context_ptr+0x00006704+4*15))=0x0413fd23;
*((unsigned int *)((unsigned long)context_ptr+0x00006704+4*16))=0x25153ab0;
*((unsigned int *)((unsigned long)context_ptr+0x00006704+4*17))=0x480d81ab;
*((unsigned int *)((unsigned long)context_ptr+0x00006704+4*18))=0x000000c4;
*((unsigned int *)((unsigned long)context_ptr+0x000036c0))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x000036c0+4*1))=0x0000640c;
*((unsigned int *)((unsigned long)context_ptr+0x000036c0+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000036c0+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000036c0+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000036c0+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x000006c0))=0x04c00049;
*((unsigned int *)((unsigned long)context_ptr+0x000006c0+4*1))=0x00006704;
*((unsigned int *)((unsigned long)context_ptr+0x000006c0+4*2))=0x00006510;
*((unsigned int *)((unsigned long)context_ptr+0x000006c0+4*3))=0x02220049;
*((unsigned int *)((unsigned long)context_ptr+0x000006c0+4*4))=0x0de9f568;
*((unsigned int *)((unsigned long)context_ptr+0x000006c0+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000162&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000062d0,"\x19\x09\x25\x65\x05\x59\x1c\xba\x8e\x25\x22\xb6\x14\xc6\x59\x8d\xf0\xe4\xa6\xf4\x10\x38\x47\x8e\xe5\xa5\x9e\xad",28))
printf("strip: 1909256505591cba, Pass\n");
else
printf("strip: 1909256505591cba, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006428))=0x026a1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006428+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006428+4*2))=0x0202004a;
*((unsigned int *)((unsigned long)context_ptr+0x00006428+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x00006254))=0x92105c6d;
*((unsigned int *)((unsigned long)context_ptr+0x00006254+4*1))=0x7557fe59;
*((unsigned int *)((unsigned long)context_ptr+0x00006254+4*2))=0xbeb3bdfc;
*((unsigned int *)((unsigned long)context_ptr+0x00006254+4*3))=0xbb21d69f;
*((unsigned int *)((unsigned long)context_ptr+0x00006254+4*4))=0xbfdb8e60;
*((unsigned int *)((unsigned long)context_ptr+0x00006254+4*5))=0x066cf5a7;
*((unsigned int *)((unsigned long)context_ptr+0x00006254+4*6))=0xd49b68f6;
*((unsigned int *)((unsigned long)context_ptr+0x00006254+4*7))=0xbb3236c8;
*((unsigned int *)((unsigned long)context_ptr+0x00006254+4*8))=0xadbba069;
*((unsigned int *)((unsigned long)context_ptr+0x00006254+4*9))=0xf4a154bc;
*((unsigned int *)((unsigned long)context_ptr+0x00006254+4*10))=0x475ffa00;
*((unsigned int *)((unsigned long)context_ptr+0x00006254+4*11))=0xb3383baf;
*((unsigned int *)((unsigned long)context_ptr+0x00006254+4*12))=0x04e2a696;
*((unsigned int *)((unsigned long)context_ptr+0x00006254+4*13))=0x67d64a65;
*((unsigned int *)((unsigned long)context_ptr+0x00006254+4*14))=0x1f959a5c;
*((unsigned int *)((unsigned long)context_ptr+0x00006254+4*15))=0x55c2efc9;
*((unsigned int *)((unsigned long)context_ptr+0x00006254+4*16))=0xdf2d1855;
*((unsigned int *)((unsigned long)context_ptr+0x00006254+4*17))=0xac2a7230;
*((unsigned int *)((unsigned long)context_ptr+0x00006254+4*18))=0x0000cc2f;
*((unsigned int *)((unsigned long)context_ptr+0x000036d8))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x000036d8+4*1))=0x00006604;
*((unsigned int *)((unsigned long)context_ptr+0x000036d8+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000036d8+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000036d8+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000036d8+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x000006d8))=0x04c0004a;
*((unsigned int *)((unsigned long)context_ptr+0x000006d8+4*1))=0x00006254;
*((unsigned int *)((unsigned long)context_ptr+0x000006d8+4*2))=0x00006428;
*((unsigned int *)((unsigned long)context_ptr+0x000006d8+4*3))=0x0222004a;
*((unsigned int *)((unsigned long)context_ptr+0x000006d8+4*4))=0x0295f904;
*((unsigned int *)((unsigned long)context_ptr+0x000006d8+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000168&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006328,"\x48\x95\x40\x8f\x5f\x97\x27\xc0\x9c\xad\x65\xe1\x5e\x67\xed\x25\x11\x6d\x54\xef\xe4\xd1\x85\x32\x29\x86\xe0\x06",28))
printf("strip: 4895408f5f9727c0, Pass\n");
else
printf("strip: 4895408f5f9727c0, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006520))=0x026a1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006520+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006520+4*2))=0x0202004b;
*((unsigned int *)((unsigned long)context_ptr+0x00006520+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x000062a0))=0x472b0be3;
*((unsigned int *)((unsigned long)context_ptr+0x000062a0+4*1))=0x953ee0f4;
*((unsigned int *)((unsigned long)context_ptr+0x000062a0+4*2))=0xba9fef49;
*((unsigned int *)((unsigned long)context_ptr+0x000062a0+4*3))=0x26edceee;
*((unsigned int *)((unsigned long)context_ptr+0x000062a0+4*4))=0xc4d8df42;
*((unsigned int *)((unsigned long)context_ptr+0x000062a0+4*5))=0x1979dab8;
*((unsigned int *)((unsigned long)context_ptr+0x000062a0+4*6))=0x8f9b3fba;
*((unsigned int *)((unsigned long)context_ptr+0x000062a0+4*7))=0x1862a763;
*((unsigned int *)((unsigned long)context_ptr+0x000062a0+4*8))=0x8f48d8dc;
*((unsigned int *)((unsigned long)context_ptr+0x000062a0+4*9))=0x6274bc22;
*((unsigned int *)((unsigned long)context_ptr+0x000062a0+4*10))=0xced7d3ee;
*((unsigned int *)((unsigned long)context_ptr+0x000062a0+4*11))=0xeb51e7ba;
*((unsigned int *)((unsigned long)context_ptr+0x000062a0+4*12))=0x7858c06a;
*((unsigned int *)((unsigned long)context_ptr+0x000062a0+4*13))=0x0d521d3f;
*((unsigned int *)((unsigned long)context_ptr+0x000062a0+4*14))=0x93135350;
*((unsigned int *)((unsigned long)context_ptr+0x000062a0+4*15))=0x3f1a9cd7;
*((unsigned int *)((unsigned long)context_ptr+0x000062a0+4*16))=0x6bba4f4b;
*((unsigned int *)((unsigned long)context_ptr+0x000062a0+4*17))=0xfd39b210;
*((unsigned int *)((unsigned long)context_ptr+0x000062a0+4*18))=0x0082d105;
*((unsigned int *)((unsigned long)context_ptr+0x000036f0))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x000036f0+4*1))=0x00006620;
*((unsigned int *)((unsigned long)context_ptr+0x000036f0+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000036f0+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000036f0+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000036f0+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x000006f0))=0x04c0004b;
*((unsigned int *)((unsigned long)context_ptr+0x000006f0+4*1))=0x000062a0;
*((unsigned int *)((unsigned long)context_ptr+0x000006f0+4*2))=0x00006520;
*((unsigned int *)((unsigned long)context_ptr+0x000006f0+4*3))=0x0222004b;
*((unsigned int *)((unsigned long)context_ptr+0x000006f0+4*4))=0x03420824;
*((unsigned int *)((unsigned long)context_ptr+0x000006f0+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000016e&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006438,"\x03\x0b\x95\x80\xa9\xc6\xb0\x53\xe0\xce\xe5\x61\x39\x76\x52\xc1\x46\x6b\x71\xe7\xe5\x74\x15\xad\x0d\x3a\xc0\x81",28))
printf("strip: 030b9580a9c6b053, Pass\n");
else
printf("strip: 030b9580a9c6b053, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006058))=0x026a1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*2))=0x0202004c;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x000062ec))=0x099e82a7;
*((unsigned int *)((unsigned long)context_ptr+0x000062ec+4*1))=0x82e3ed07;
*((unsigned int *)((unsigned long)context_ptr+0x000062ec+4*2))=0xc8d51969;
*((unsigned int *)((unsigned long)context_ptr+0x000062ec+4*3))=0xd57ecda8;
*((unsigned int *)((unsigned long)context_ptr+0x000062ec+4*4))=0x8e8c112c;
*((unsigned int *)((unsigned long)context_ptr+0x000062ec+4*5))=0x1e643a94;
*((unsigned int *)((unsigned long)context_ptr+0x000062ec+4*6))=0xf7a6d8d0;
*((unsigned int *)((unsigned long)context_ptr+0x000062ec+4*7))=0xe5ceefa0;
*((unsigned int *)((unsigned long)context_ptr+0x000062ec+4*8))=0xa325185f;
*((unsigned int *)((unsigned long)context_ptr+0x000062ec+4*9))=0xadca71ca;
*((unsigned int *)((unsigned long)context_ptr+0x000062ec+4*10))=0x44333034;
*((unsigned int *)((unsigned long)context_ptr+0x000062ec+4*11))=0x923c8b40;
*((unsigned int *)((unsigned long)context_ptr+0x000062ec+4*12))=0xc3a9cc9f;
*((unsigned int *)((unsigned long)context_ptr+0x000062ec+4*13))=0xa054077c;
*((unsigned int *)((unsigned long)context_ptr+0x000062ec+4*14))=0x082eeb7b;
*((unsigned int *)((unsigned long)context_ptr+0x000062ec+4*15))=0x8ad83870;
*((unsigned int *)((unsigned long)context_ptr+0x000062ec+4*16))=0x673ba5b7;
*((unsigned int *)((unsigned long)context_ptr+0x000062ec+4*17))=0xceee3dd8;
*((unsigned int *)((unsigned long)context_ptr+0x000062ec+4*18))=0xb7828a82;
*((unsigned int *)((unsigned long)context_ptr+0x00003708))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003708+4*1))=0x00006438;
*((unsigned int *)((unsigned long)context_ptr+0x00003708+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003708+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003708+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003708+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000708))=0x04c0004c;
*((unsigned int *)((unsigned long)context_ptr+0x00000708+4*1))=0x000062ec;
*((unsigned int *)((unsigned long)context_ptr+0x00000708+4*2))=0x00006058;
*((unsigned int *)((unsigned long)context_ptr+0x00000708+4*3))=0x0222004c;
*((unsigned int *)((unsigned long)context_ptr+0x00000708+4*4))=0x08684f88;
*((unsigned int *)((unsigned long)context_ptr+0x00000708+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000174&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006078,"\xdf\xcb\x39\x7e\x0b\x18\xea\x24\x39\xc6\x43\x6f\x44\xd1\xd2\xc8\x7f\xe0\x6f\x96\xa3\x91\xa6\x64\xa3\xed\xb3\x0d",28))
printf("strip: dfcb397e0b18ea24, Pass\n");
else
printf("strip: dfcb397e0b18ea24, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006048))=0x026a1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006048+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006048+4*2))=0x0202004d;
*((unsigned int *)((unsigned long)context_ptr+0x00006048+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x00006750))=0x168193ad;
*((unsigned int *)((unsigned long)context_ptr+0x00006750+4*1))=0xd3756462;
*((unsigned int *)((unsigned long)context_ptr+0x00006750+4*2))=0x8e341b4c;
*((unsigned int *)((unsigned long)context_ptr+0x00006750+4*3))=0x8420f867;
*((unsigned int *)((unsigned long)context_ptr+0x00006750+4*4))=0xd3e449ce;
*((unsigned int *)((unsigned long)context_ptr+0x00006750+4*5))=0xc86dc26b;
*((unsigned int *)((unsigned long)context_ptr+0x00006750+4*6))=0x49689056;
*((unsigned int *)((unsigned long)context_ptr+0x00006750+4*7))=0x3cb76a74;
*((unsigned int *)((unsigned long)context_ptr+0x00006750+4*8))=0x65c0bff2;
*((unsigned int *)((unsigned long)context_ptr+0x00006750+4*9))=0x79e490e5;
*((unsigned int *)((unsigned long)context_ptr+0x00006750+4*10))=0x393544f6;
*((unsigned int *)((unsigned long)context_ptr+0x00006750+4*11))=0x9d0bc75c;
*((unsigned int *)((unsigned long)context_ptr+0x00006750+4*12))=0x654b7d4f;
*((unsigned int *)((unsigned long)context_ptr+0x00006750+4*13))=0x58bd1f6b;
*((unsigned int *)((unsigned long)context_ptr+0x00006750+4*14))=0xb937d118;
*((unsigned int *)((unsigned long)context_ptr+0x00006750+4*15))=0xf8f20998;
*((unsigned int *)((unsigned long)context_ptr+0x00006750+4*16))=0x31b217bb;
*((unsigned int *)((unsigned long)context_ptr+0x00006750+4*17))=0xd3417e76;
*((unsigned int *)((unsigned long)context_ptr+0x00006750+4*18))=0xc09a7a1f;
*((unsigned int *)((unsigned long)context_ptr+0x00006750+4*19))=0x000000dc;
*((unsigned int *)((unsigned long)context_ptr+0x00003720))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003720+4*1))=0x00006078;
*((unsigned int *)((unsigned long)context_ptr+0x00003720+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003720+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003720+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003720+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000720))=0x04c0004d;
*((unsigned int *)((unsigned long)context_ptr+0x00000720+4*1))=0x00006750;
*((unsigned int *)((unsigned long)context_ptr+0x00000720+4*2))=0x00006048;
*((unsigned int *)((unsigned long)context_ptr+0x00000720+4*3))=0x0222004d;
*((unsigned int *)((unsigned long)context_ptr+0x00000720+4*4))=0x0101ad1e;
*((unsigned int *)((unsigned long)context_ptr+0x00000720+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000017a&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006454,"\x36\xb5\x92\x38\xdb\xd6\x8d\x20\x9d\x6a\xab\x83\xd1\xff\x99\x78\x6a\xd9\xb2\x7c\x39\xc5\x30\xdc\x39\x2c\x94\x7e",28))
printf("strip: 36b59238dbd68d20, Pass\n");
else
printf("strip: 36b59238dbd68d20, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006068))=0x026a1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006068+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006068+4*2))=0x0202004e;
*((unsigned int *)((unsigned long)context_ptr+0x00006068+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x0000663c))=0x1f037f70;
*((unsigned int *)((unsigned long)context_ptr+0x0000663c+4*1))=0x093f0c2c;
*((unsigned int *)((unsigned long)context_ptr+0x0000663c+4*2))=0x49803261;
*((unsigned int *)((unsigned long)context_ptr+0x0000663c+4*3))=0x9dc99b88;
*((unsigned int *)((unsigned long)context_ptr+0x0000663c+4*4))=0xe7e7ae67;
*((unsigned int *)((unsigned long)context_ptr+0x0000663c+4*5))=0x949c1ea6;
*((unsigned int *)((unsigned long)context_ptr+0x0000663c+4*6))=0xcf1990cc;
*((unsigned int *)((unsigned long)context_ptr+0x0000663c+4*7))=0x695a9475;
*((unsigned int *)((unsigned long)context_ptr+0x0000663c+4*8))=0xd288810b;
*((unsigned int *)((unsigned long)context_ptr+0x0000663c+4*9))=0xdcf9315c;
*((unsigned int *)((unsigned long)context_ptr+0x0000663c+4*10))=0x1e26f545;
*((unsigned int *)((unsigned long)context_ptr+0x0000663c+4*11))=0xf70207d0;
*((unsigned int *)((unsigned long)context_ptr+0x0000663c+4*12))=0x9245bc14;
*((unsigned int *)((unsigned long)context_ptr+0x0000663c+4*13))=0x9d1a247a;
*((unsigned int *)((unsigned long)context_ptr+0x0000663c+4*14))=0xcd2f8d36;
*((unsigned int *)((unsigned long)context_ptr+0x0000663c+4*15))=0x254ae392;
*((unsigned int *)((unsigned long)context_ptr+0x0000663c+4*16))=0x36309df5;
*((unsigned int *)((unsigned long)context_ptr+0x0000663c+4*17))=0x4cc4b22c;
*((unsigned int *)((unsigned long)context_ptr+0x0000663c+4*18))=0xaee12738;
*((unsigned int *)((unsigned long)context_ptr+0x0000663c+4*19))=0x0000d706;
*((unsigned int *)((unsigned long)context_ptr+0x00003738))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003738+4*1))=0x00006454;
*((unsigned int *)((unsigned long)context_ptr+0x00003738+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003738+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003738+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003738+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000738))=0x04c0004e;
*((unsigned int *)((unsigned long)context_ptr+0x00000738+4*1))=0x0000663c;
*((unsigned int *)((unsigned long)context_ptr+0x00000738+4*2))=0x00006068;
*((unsigned int *)((unsigned long)context_ptr+0x00000738+4*3))=0x0222004e;
*((unsigned int *)((unsigned long)context_ptr+0x00000738+4*4))=0x0b4d7d27;
*((unsigned int *)((unsigned long)context_ptr+0x00000738+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000180&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006470,"\x25\x6a\xaa\xcf\x1a\x8b\x27\x46\x86\xdb\x9d\x8e\xa9\x20\xad\x11\x40\x20\xe9\x82\xee\xba\x20\x08\x4b\x47\x92\xb2",28))
printf("strip: 256aaacf1a8b2746, Pass\n");
else
printf("strip: 256aaacf1a8b2746, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006094))=0x026a1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006094+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006094+4*2))=0x0202004f;
*((unsigned int *)((unsigned long)context_ptr+0x00006094+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x000067a0))=0x0ecb86e7;
*((unsigned int *)((unsigned long)context_ptr+0x000067a0+4*1))=0x4a7b2b94;
*((unsigned int *)((unsigned long)context_ptr+0x000067a0+4*2))=0x06951e8c;
*((unsigned int *)((unsigned long)context_ptr+0x000067a0+4*3))=0xc22ef39b;
*((unsigned int *)((unsigned long)context_ptr+0x000067a0+4*4))=0x98d7abca;
*((unsigned int *)((unsigned long)context_ptr+0x000067a0+4*5))=0xb6ea52b7;
*((unsigned int *)((unsigned long)context_ptr+0x000067a0+4*6))=0x9aae57a8;
*((unsigned int *)((unsigned long)context_ptr+0x000067a0+4*7))=0x6fe08e70;
*((unsigned int *)((unsigned long)context_ptr+0x000067a0+4*8))=0xd818a955;
*((unsigned int *)((unsigned long)context_ptr+0x000067a0+4*9))=0xc5deb5e5;
*((unsigned int *)((unsigned long)context_ptr+0x000067a0+4*10))=0xba8ca432;
*((unsigned int *)((unsigned long)context_ptr+0x000067a0+4*11))=0x2c5ac573;
*((unsigned int *)((unsigned long)context_ptr+0x000067a0+4*12))=0xdcc23b09;
*((unsigned int *)((unsigned long)context_ptr+0x000067a0+4*13))=0x74da56b6;
*((unsigned int *)((unsigned long)context_ptr+0x000067a0+4*14))=0x3117c5f6;
*((unsigned int *)((unsigned long)context_ptr+0x000067a0+4*15))=0x64122cf6;
*((unsigned int *)((unsigned long)context_ptr+0x000067a0+4*16))=0xca1580ba;
*((unsigned int *)((unsigned long)context_ptr+0x000067a0+4*17))=0x032995ab;
*((unsigned int *)((unsigned long)context_ptr+0x000067a0+4*18))=0x922f2fd7;
*((unsigned int *)((unsigned long)context_ptr+0x000067a0+4*19))=0x002d0a9b;
*((unsigned int *)((unsigned long)context_ptr+0x00003750))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003750+4*1))=0x00006470;
*((unsigned int *)((unsigned long)context_ptr+0x00003750+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003750+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003750+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003750+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000750))=0x04c0004f;
*((unsigned int *)((unsigned long)context_ptr+0x00000750+4*1))=0x000067a0;
*((unsigned int *)((unsigned long)context_ptr+0x00000750+4*2))=0x00006094;
*((unsigned int *)((unsigned long)context_ptr+0x00000750+4*3))=0x0222004f;
*((unsigned int *)((unsigned long)context_ptr+0x00000750+4*4))=0x0deecbce;
*((unsigned int *)((unsigned long)context_ptr+0x00000750+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000186&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006384,"\xf4\x49\xbb\xa8\x29\xb5\xd4\x7b\xe0\xd8\x71\x17\xa1\x29\x76\x7a\x61\xe3\x4e\x9b\x36\xe9\xdc\x7a\x4c\x0d\xdf\x5f",28))
printf("strip: f449bba829b5d47b, Pass\n");
else
printf("strip: f449bba829b5d47b, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x0000648c))=0x026a1002;
*((unsigned int *)((unsigned long)context_ptr+0x0000648c+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x0000648c+4*2))=0x02020050;
*((unsigned int *)((unsigned long)context_ptr+0x0000648c+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x00006338))=0x15ba3847;
*((unsigned int *)((unsigned long)context_ptr+0x00006338+4*1))=0x73de623c;
*((unsigned int *)((unsigned long)context_ptr+0x00006338+4*2))=0x4dd7ca13;
*((unsigned int *)((unsigned long)context_ptr+0x00006338+4*3))=0xbad7a28c;
*((unsigned int *)((unsigned long)context_ptr+0x00006338+4*4))=0xbbbb7e9c;
*((unsigned int *)((unsigned long)context_ptr+0x00006338+4*5))=0x3a2ca6c0;
*((unsigned int *)((unsigned long)context_ptr+0x00006338+4*6))=0x51c918e5;
*((unsigned int *)((unsigned long)context_ptr+0x00006338+4*7))=0xd46ef52b;
*((unsigned int *)((unsigned long)context_ptr+0x00006338+4*8))=0x0ddb6527;
*((unsigned int *)((unsigned long)context_ptr+0x00006338+4*9))=0x9f2efc86;
*((unsigned int *)((unsigned long)context_ptr+0x00006338+4*10))=0x54f9a9b0;
*((unsigned int *)((unsigned long)context_ptr+0x00006338+4*11))=0xe92c3b5a;
*((unsigned int *)((unsigned long)context_ptr+0x00006338+4*12))=0x3e179bd3;
*((unsigned int *)((unsigned long)context_ptr+0x00006338+4*13))=0xac4a8633;
*((unsigned int *)((unsigned long)context_ptr+0x00006338+4*14))=0xbf493569;
*((unsigned int *)((unsigned long)context_ptr+0x00006338+4*15))=0x053f2f78;
*((unsigned int *)((unsigned long)context_ptr+0x00006338+4*16))=0x6d898ea1;
*((unsigned int *)((unsigned long)context_ptr+0x00006338+4*17))=0x0509b846;
*((unsigned int *)((unsigned long)context_ptr+0x00006338+4*18))=0xf7af7acb;
*((unsigned int *)((unsigned long)context_ptr+0x00006338+4*19))=0x5eb638b8;
*((unsigned int *)((unsigned long)context_ptr+0x00003768))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003768+4*1))=0x0000668c;
*((unsigned int *)((unsigned long)context_ptr+0x00003768+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003768+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003768+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003768+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000768))=0x04c00050;
*((unsigned int *)((unsigned long)context_ptr+0x00000768+4*1))=0x00006338;
*((unsigned int *)((unsigned long)context_ptr+0x00000768+4*2))=0x0000648c;
*((unsigned int *)((unsigned long)context_ptr+0x00000768+4*3))=0x02220050;
*((unsigned int *)((unsigned long)context_ptr+0x00000768+4*4))=0x05dbcc6d;
*((unsigned int *)((unsigned long)context_ptr+0x00000768+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000018c&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000063a0,"\x61\x91\x2d\xce\x01\xc2\x03\x21\xff\xec\xcd\x11\xb2\x62\xb7\xd0\xc2\xbe\xee\xaf\xfc\x16\x0a\x8e\x02\x9a\x0d\x41",28))
printf("strip: 61912dce01c20321, Pass\n");
else
printf("strip: 61912dce01c20321, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x0000649c))=0x026a1002;
*((unsigned int *)((unsigned long)context_ptr+0x0000649c+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x0000649c+4*2))=0x02020051;
*((unsigned int *)((unsigned long)context_ptr+0x0000649c+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x000060a4))=0x51c6f961;
*((unsigned int *)((unsigned long)context_ptr+0x000060a4+4*1))=0x075f483f;
*((unsigned int *)((unsigned long)context_ptr+0x000060a4+4*2))=0x563864cf;
*((unsigned int *)((unsigned long)context_ptr+0x000060a4+4*3))=0xea5c5d1e;
*((unsigned int *)((unsigned long)context_ptr+0x000060a4+4*4))=0x7f3e6795;
*((unsigned int *)((unsigned long)context_ptr+0x000060a4+4*5))=0xe157a80a;
*((unsigned int *)((unsigned long)context_ptr+0x000060a4+4*6))=0x195f0fe8;
*((unsigned int *)((unsigned long)context_ptr+0x000060a4+4*7))=0xb5c0d7b8;
*((unsigned int *)((unsigned long)context_ptr+0x000060a4+4*8))=0x5f35c14a;
*((unsigned int *)((unsigned long)context_ptr+0x000060a4+4*9))=0x19cedff8;
*((unsigned int *)((unsigned long)context_ptr+0x000060a4+4*10))=0x25d2aa6c;
*((unsigned int *)((unsigned long)context_ptr+0x000060a4+4*11))=0x04a2f6c9;
*((unsigned int *)((unsigned long)context_ptr+0x000060a4+4*12))=0x231344c5;
*((unsigned int *)((unsigned long)context_ptr+0x000060a4+4*13))=0x61092944;
*((unsigned int *)((unsigned long)context_ptr+0x000060a4+4*14))=0x05c56211;
*((unsigned int *)((unsigned long)context_ptr+0x000060a4+4*15))=0x92de43be;
*((unsigned int *)((unsigned long)context_ptr+0x000060a4+4*16))=0x6e19e892;
*((unsigned int *)((unsigned long)context_ptr+0x000060a4+4*17))=0xd8086135;
*((unsigned int *)((unsigned long)context_ptr+0x000060a4+4*18))=0x9f81bd01;
*((unsigned int *)((unsigned long)context_ptr+0x000060a4+4*19))=0xd7490202;
*((unsigned int *)((unsigned long)context_ptr+0x000060a4+4*20))=0x000000f0;
*((unsigned int *)((unsigned long)context_ptr+0x00003780))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003780+4*1))=0x00006388;
*((unsigned int *)((unsigned long)context_ptr+0x00003780+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003780+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003780+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003780+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000780))=0x04c00051;
*((unsigned int *)((unsigned long)context_ptr+0x00000780+4*1))=0x000060a4;
*((unsigned int *)((unsigned long)context_ptr+0x00000780+4*2))=0x0000649c;
*((unsigned int *)((unsigned long)context_ptr+0x00000780+4*3))=0x02220051;
*((unsigned int *)((unsigned long)context_ptr+0x00000780+4*4))=0x0af1b0ef;
*((unsigned int *)((unsigned long)context_ptr+0x00000780+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000192&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006170,"\x12\x97\x37\x3b\x9f\x7c\x93\xc2\xb3\x81\x98\x34\xc3\xe3\x3b\x12\x21\xb9\xed\xd7\x7e\x11\xcc\x07\xb0\x1a\x2b\x17",28))
printf("strip: 1297373b9f7c93c2, Pass\n");
else
printf("strip: 1297373b9f7c93c2, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000066a8))=0x026a1002;
*((unsigned int *)((unsigned long)context_ptr+0x000066a8+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000066a8+4*2))=0x02020052;
*((unsigned int *)((unsigned long)context_ptr+0x000066a8+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x000060f8))=0x84206067;
*((unsigned int *)((unsigned long)context_ptr+0x000060f8+4*1))=0x637d2f61;
*((unsigned int *)((unsigned long)context_ptr+0x000060f8+4*2))=0x7b8a6840;
*((unsigned int *)((unsigned long)context_ptr+0x000060f8+4*3))=0xac81dd2d;
*((unsigned int *)((unsigned long)context_ptr+0x000060f8+4*4))=0x234d6c70;
*((unsigned int *)((unsigned long)context_ptr+0x000060f8+4*5))=0xc207ff89;
*((unsigned int *)((unsigned long)context_ptr+0x000060f8+4*6))=0x3b829784;
*((unsigned int *)((unsigned long)context_ptr+0x000060f8+4*7))=0x978b77b7;
*((unsigned int *)((unsigned long)context_ptr+0x000060f8+4*8))=0xb7c60b91;
*((unsigned int *)((unsigned long)context_ptr+0x000060f8+4*9))=0x6ead3828;
*((unsigned int *)((unsigned long)context_ptr+0x000060f8+4*10))=0xca9c09fe;
*((unsigned int *)((unsigned long)context_ptr+0x000060f8+4*11))=0x513ef34f;
*((unsigned int *)((unsigned long)context_ptr+0x000060f8+4*12))=0xb2a51267;
*((unsigned int *)((unsigned long)context_ptr+0x000060f8+4*13))=0x975316c8;
*((unsigned int *)((unsigned long)context_ptr+0x000060f8+4*14))=0xde77a788;
*((unsigned int *)((unsigned long)context_ptr+0x000060f8+4*15))=0x230cc7ec;
*((unsigned int *)((unsigned long)context_ptr+0x000060f8+4*16))=0x6500e42d;
*((unsigned int *)((unsigned long)context_ptr+0x000060f8+4*17))=0x88d1f0f6;
*((unsigned int *)((unsigned long)context_ptr+0x000060f8+4*18))=0xb09bbb58;
*((unsigned int *)((unsigned long)context_ptr+0x000060f8+4*19))=0xdd618090;
*((unsigned int *)((unsigned long)context_ptr+0x000060f8+4*20))=0x00009e0f;
*((unsigned int *)((unsigned long)context_ptr+0x00003798))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003798+4*1))=0x000063a4;
*((unsigned int *)((unsigned long)context_ptr+0x00003798+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003798+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003798+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003798+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000798))=0x04c00052;
*((unsigned int *)((unsigned long)context_ptr+0x00000798+4*1))=0x000060f8;
*((unsigned int *)((unsigned long)context_ptr+0x00000798+4*2))=0x000066a8;
*((unsigned int *)((unsigned long)context_ptr+0x00000798+4*3))=0x02220052;
*((unsigned int *)((unsigned long)context_ptr+0x00000798+4*4))=0x02e70b41;
*((unsigned int *)((unsigned long)context_ptr+0x00000798+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000198&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x0000618c,"\x50\xef\xad\x33\x87\x47\x91\xd9\x9b\x4b\x8f\x35\x2f\xb2\xe2\x46\x5e\xbc\x83\xe5\xb7\xc6\xac\x37\xd1\x40\x0c\x1f",28))
printf("strip: 50efad33874791d9, Pass\n");
else
printf("strip: 50efad33874791d9, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000063c0))=0x026a1002;
*((unsigned int *)((unsigned long)context_ptr+0x000063c0+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000063c0+4*2))=0x02020053;
*((unsigned int *)((unsigned long)context_ptr+0x000063c0+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x0000614c))=0xdce056c2;
*((unsigned int *)((unsigned long)context_ptr+0x0000614c+4*1))=0x0404b4c9;
*((unsigned int *)((unsigned long)context_ptr+0x0000614c+4*2))=0x259e3ad5;
*((unsigned int *)((unsigned long)context_ptr+0x0000614c+4*3))=0x9b577c2d;
*((unsigned int *)((unsigned long)context_ptr+0x0000614c+4*4))=0xb94d795a;
*((unsigned int *)((unsigned long)context_ptr+0x0000614c+4*5))=0x37800608;
*((unsigned int *)((unsigned long)context_ptr+0x0000614c+4*6))=0x692182a8;
*((unsigned int *)((unsigned long)context_ptr+0x0000614c+4*7))=0x27a865d0;
*((unsigned int *)((unsigned long)context_ptr+0x0000614c+4*8))=0x9f319930;
*((unsigned int *)((unsigned long)context_ptr+0x0000614c+4*9))=0xc20389d8;
*((unsigned int *)((unsigned long)context_ptr+0x0000614c+4*10))=0x28496846;
*((unsigned int *)((unsigned long)context_ptr+0x0000614c+4*11))=0x5f0abca5;
*((unsigned int *)((unsigned long)context_ptr+0x0000614c+4*12))=0x03f9d6bc;
*((unsigned int *)((unsigned long)context_ptr+0x0000614c+4*13))=0xf30e081c;
*((unsigned int *)((unsigned long)context_ptr+0x0000614c+4*14))=0x9e451539;
*((unsigned int *)((unsigned long)context_ptr+0x0000614c+4*15))=0xc4e3e2e9;
*((unsigned int *)((unsigned long)context_ptr+0x0000614c+4*16))=0x247a36ca;
*((unsigned int *)((unsigned long)context_ptr+0x0000614c+4*17))=0xa4af6f55;
*((unsigned int *)((unsigned long)context_ptr+0x0000614c+4*18))=0xb0b75374;
*((unsigned int *)((unsigned long)context_ptr+0x0000614c+4*19))=0x95e60382;
*((unsigned int *)((unsigned long)context_ptr+0x0000614c+4*20))=0x00216230;
*((unsigned int *)((unsigned long)context_ptr+0x000037b0))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x000037b0+4*1))=0x00006530;
*((unsigned int *)((unsigned long)context_ptr+0x000037b0+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000037b0+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000037b0+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000037b0+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x000007b0))=0x04c00053;
*((unsigned int *)((unsigned long)context_ptr+0x000007b0+4*1))=0x0000614c;
*((unsigned int *)((unsigned long)context_ptr+0x000007b0+4*2))=0x000063c0;
*((unsigned int *)((unsigned long)context_ptr+0x000007b0+4*3))=0x02220053;
*((unsigned int *)((unsigned long)context_ptr+0x000007b0+4*4))=0x067e0896;
*((unsigned int *)((unsigned long)context_ptr+0x000007b0+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000019e&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000064ac,"\x57\x96\x40\x38\xb3\x42\x8a\x83\x23\x8c\xbc\x63\xab\xe3\x5e\x9c\x2c\xc9\xd5\xd3\xdb\xbb\x99\xe9\x8e\xa0\xd9\xd4",28))
printf("strip: 57964038b3428a83, Pass\n");
else
printf("strip: 57964038b3428a83, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000063d0))=0x026a1002;
*((unsigned int *)((unsigned long)context_ptr+0x000063d0+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000063d0+4*2))=0x02020054;
*((unsigned int *)((unsigned long)context_ptr+0x000063d0+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x0000654c))=0x81ea9365;
*((unsigned int *)((unsigned long)context_ptr+0x0000654c+4*1))=0x517692ee;
*((unsigned int *)((unsigned long)context_ptr+0x0000654c+4*2))=0x5405c5c1;
*((unsigned int *)((unsigned long)context_ptr+0x0000654c+4*3))=0x568c3a50;
*((unsigned int *)((unsigned long)context_ptr+0x0000654c+4*4))=0x5526c028;
*((unsigned int *)((unsigned long)context_ptr+0x0000654c+4*5))=0x6d59c6e4;
*((unsigned int *)((unsigned long)context_ptr+0x0000654c+4*6))=0xc5fab35d;
*((unsigned int *)((unsigned long)context_ptr+0x0000654c+4*7))=0xf2600a00;
*((unsigned int *)((unsigned long)context_ptr+0x0000654c+4*8))=0x83d66294;
*((unsigned int *)((unsigned long)context_ptr+0x0000654c+4*9))=0xb03d8cbf;
*((unsigned int *)((unsigned long)context_ptr+0x0000654c+4*10))=0x029c1e34;
*((unsigned int *)((unsigned long)context_ptr+0x0000654c+4*11))=0x68654376;
*((unsigned int *)((unsigned long)context_ptr+0x0000654c+4*12))=0x4387176d;
*((unsigned int *)((unsigned long)context_ptr+0x0000654c+4*13))=0x9ed917e9;
*((unsigned int *)((unsigned long)context_ptr+0x0000654c+4*14))=0x8f8a8959;
*((unsigned int *)((unsigned long)context_ptr+0x0000654c+4*15))=0xbc1190e2;
*((unsigned int *)((unsigned long)context_ptr+0x0000654c+4*16))=0x2a7fc815;
*((unsigned int *)((unsigned long)context_ptr+0x0000654c+4*17))=0x9fd6ac50;
*((unsigned int *)((unsigned long)context_ptr+0x0000654c+4*18))=0x269730c5;
*((unsigned int *)((unsigned long)context_ptr+0x0000654c+4*19))=0xaf01faea;
*((unsigned int *)((unsigned long)context_ptr+0x0000654c+4*20))=0x43b32d14;
*((unsigned int *)((unsigned long)context_ptr+0x000037c8))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x000037c8+4*1))=0x000064ac;
*((unsigned int *)((unsigned long)context_ptr+0x000037c8+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000037c8+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000037c8+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000037c8+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x000007c8))=0x04c00054;
*((unsigned int *)((unsigned long)context_ptr+0x000007c8+4*1))=0x0000654c;
*((unsigned int *)((unsigned long)context_ptr+0x000007c8+4*2))=0x000063d0;
*((unsigned int *)((unsigned long)context_ptr+0x000007c8+4*3))=0x02220054;
*((unsigned int *)((unsigned long)context_ptr+0x000007c8+4*4))=0x02028332;
*((unsigned int *)((unsigned long)context_ptr+0x000007c8+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000001a4&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000064c8,"\x22\x06\x10\xcc\x16\x82\xb3\xa4\x37\x64\x09\x3b\xa0\x9e\xdc\x29\x48\x1a\xf0\xad\xc5\x4c\xbf\xa0\xad\xe9\xe6\x99",28))
printf("strip: 220610cc1682b3a4, Pass\n");
else
printf("strip: 220610cc1682b3a4, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000063e0))=0x026a1002;
*((unsigned int *)((unsigned long)context_ptr+0x000063e0+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000063e0+4*2))=0x02020055;
*((unsigned int *)((unsigned long)context_ptr+0x000063e0+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x000067f0))=0x6af4e66a;
*((unsigned int *)((unsigned long)context_ptr+0x000067f0+4*1))=0xfa6e9679;
*((unsigned int *)((unsigned long)context_ptr+0x000067f0+4*2))=0x152d9ca1;
*((unsigned int *)((unsigned long)context_ptr+0x000067f0+4*3))=0x4a30440c;
*((unsigned int *)((unsigned long)context_ptr+0x000067f0+4*4))=0xb4ecb397;
*((unsigned int *)((unsigned long)context_ptr+0x000067f0+4*5))=0xd2da4aa1;
*((unsigned int *)((unsigned long)context_ptr+0x000067f0+4*6))=0xcbbbbbc4;
*((unsigned int *)((unsigned long)context_ptr+0x000067f0+4*7))=0xf3494390;
*((unsigned int *)((unsigned long)context_ptr+0x000067f0+4*8))=0x8c09762a;
*((unsigned int *)((unsigned long)context_ptr+0x000067f0+4*9))=0x4d08477c;
*((unsigned int *)((unsigned long)context_ptr+0x000067f0+4*10))=0x1c07c58e;
*((unsigned int *)((unsigned long)context_ptr+0x000067f0+4*11))=0xb6cccd75;
*((unsigned int *)((unsigned long)context_ptr+0x000067f0+4*12))=0x0d9cf14f;
*((unsigned int *)((unsigned long)context_ptr+0x000067f0+4*13))=0xe50b7e46;
*((unsigned int *)((unsigned long)context_ptr+0x000067f0+4*14))=0x4106876c;
*((unsigned int *)((unsigned long)context_ptr+0x000067f0+4*15))=0xae83945d;
*((unsigned int *)((unsigned long)context_ptr+0x000067f0+4*16))=0x9a63852d;
*((unsigned int *)((unsigned long)context_ptr+0x000067f0+4*17))=0x8f5d57ba;
*((unsigned int *)((unsigned long)context_ptr+0x000067f0+4*18))=0xb8bea0d3;
*((unsigned int *)((unsigned long)context_ptr+0x000067f0+4*19))=0x9f26a195;
*((unsigned int *)((unsigned long)context_ptr+0x000067f0+4*20))=0xb60010ba;
*((unsigned int *)((unsigned long)context_ptr+0x000067f0+4*21))=0x000000d8;
*((unsigned int *)((unsigned long)context_ptr+0x000037e0))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x000037e0+4*1))=0x000064c8;
*((unsigned int *)((unsigned long)context_ptr+0x000037e0+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000037e0+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000037e0+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000037e0+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x000007e0))=0x04c00055;
*((unsigned int *)((unsigned long)context_ptr+0x000007e0+4*1))=0x000067f0;
*((unsigned int *)((unsigned long)context_ptr+0x000007e0+4*2))=0x000063e0;
*((unsigned int *)((unsigned long)context_ptr+0x000007e0+4*3))=0x02220055;
*((unsigned int *)((unsigned long)context_ptr+0x000007e0+4*4))=0x0b52d196;
*((unsigned int *)((unsigned long)context_ptr+0x000007e0+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000001aa&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006238,"\xbe\x41\xf9\x9d\xae\xad\x31\x62\x95\x0e\xfd\x0b\xc8\xa9\x48\xd8\x2e\x29\x39\x14\x0f\x9e\xc2\xa6\x1d\x16\x9b\x70",28))
printf("strip: be41f99daead3162, Pass\n");
else
printf("strip: be41f99daead3162, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000064e4))=0x026a1002;
*((unsigned int *)((unsigned long)context_ptr+0x000064e4+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000064e4+4*2))=0x02020056;
*((unsigned int *)((unsigned long)context_ptr+0x000064e4+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x000061a0))=0xb1944e29;
*((unsigned int *)((unsigned long)context_ptr+0x000061a0+4*1))=0x87ce8d02;
*((unsigned int *)((unsigned long)context_ptr+0x000061a0+4*2))=0xf0edf46c;
*((unsigned int *)((unsigned long)context_ptr+0x000061a0+4*3))=0xed711e9e;
*((unsigned int *)((unsigned long)context_ptr+0x000061a0+4*4))=0x4ddc8cbd;
*((unsigned int *)((unsigned long)context_ptr+0x000061a0+4*5))=0x9bb9b4a3;
*((unsigned int *)((unsigned long)context_ptr+0x000061a0+4*6))=0x42536867;
*((unsigned int *)((unsigned long)context_ptr+0x000061a0+4*7))=0x925bada0;
*((unsigned int *)((unsigned long)context_ptr+0x000061a0+4*8))=0xc0f83357;
*((unsigned int *)((unsigned long)context_ptr+0x000061a0+4*9))=0x5fac01b2;
*((unsigned int *)((unsigned long)context_ptr+0x000061a0+4*10))=0x263fee81;
*((unsigned int *)((unsigned long)context_ptr+0x000061a0+4*11))=0x661688b4;
*((unsigned int *)((unsigned long)context_ptr+0x000061a0+4*12))=0x7fe265e2;
*((unsigned int *)((unsigned long)context_ptr+0x000061a0+4*13))=0x46c4b3dd;
*((unsigned int *)((unsigned long)context_ptr+0x000061a0+4*14))=0xd3e9fbe5;
*((unsigned int *)((unsigned long)context_ptr+0x000061a0+4*15))=0xfabd1cd8;
*((unsigned int *)((unsigned long)context_ptr+0x000061a0+4*16))=0xb75d2d92;
*((unsigned int *)((unsigned long)context_ptr+0x000061a0+4*17))=0x128a2a99;
*((unsigned int *)((unsigned long)context_ptr+0x000061a0+4*18))=0x4ad309c3;
*((unsigned int *)((unsigned long)context_ptr+0x000061a0+4*19))=0x97fee9ff;
*((unsigned int *)((unsigned long)context_ptr+0x000061a0+4*20))=0xcb17c28a;
*((unsigned int *)((unsigned long)context_ptr+0x000061a0+4*21))=0x000081dc;
*((unsigned int *)((unsigned long)context_ptr+0x000037f8))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x000037f8+4*1))=0x000065a0;
*((unsigned int *)((unsigned long)context_ptr+0x000037f8+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000037f8+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000037f8+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000037f8+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x000007f8))=0x04c00056;
*((unsigned int *)((unsigned long)context_ptr+0x000007f8+4*1))=0x000061a0;
*((unsigned int *)((unsigned long)context_ptr+0x000007f8+4*2))=0x000064e4;
*((unsigned int *)((unsigned long)context_ptr+0x000007f8+4*3))=0x02220056;
*((unsigned int *)((unsigned long)context_ptr+0x000007f8+4*4))=0x0bbd5ba6;
*((unsigned int *)((unsigned long)context_ptr+0x000007f8+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000001b0&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000064f4,"\x0c\x4f\xd3\xd3\x85\xe1\x69\x6d\xfb\xd9\x5d\xfa\x0c\x67\x25\x57\x10\x0c\x3a\x70\x16\xb8\x38\xf9\x0d\x77\x34\xf1",28))
printf("strip: 0c4fd3d385e1696d, Pass\n");
else
printf("strip: 0c4fd3d385e1696d, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000063f0))=0x026a1002;
*((unsigned int *)((unsigned long)context_ptr+0x000063f0+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000063f0+4*2))=0x02020057;
*((unsigned int *)((unsigned long)context_ptr+0x000063f0+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x000061f8))=0xf592c5ff;
*((unsigned int *)((unsigned long)context_ptr+0x000061f8+4*1))=0xcb2ac6dd;
*((unsigned int *)((unsigned long)context_ptr+0x000061f8+4*2))=0xdd44491d;
*((unsigned int *)((unsigned long)context_ptr+0x000061f8+4*3))=0x932135b9;
*((unsigned int *)((unsigned long)context_ptr+0x000061f8+4*4))=0x43f038af;
*((unsigned int *)((unsigned long)context_ptr+0x000061f8+4*5))=0xdb5072d5;
*((unsigned int *)((unsigned long)context_ptr+0x000061f8+4*6))=0x4e8c7af8;
*((unsigned int *)((unsigned long)context_ptr+0x000061f8+4*7))=0xe9aa409e;
*((unsigned int *)((unsigned long)context_ptr+0x000061f8+4*8))=0x0fc9e688;
*((unsigned int *)((unsigned long)context_ptr+0x000061f8+4*9))=0x7a76bde0;
*((unsigned int *)((unsigned long)context_ptr+0x000061f8+4*10))=0x934a57c7;
*((unsigned int *)((unsigned long)context_ptr+0x000061f8+4*11))=0x220c6a04;
*((unsigned int *)((unsigned long)context_ptr+0x000061f8+4*12))=0xdd349fc8;
*((unsigned int *)((unsigned long)context_ptr+0x000061f8+4*13))=0x597b418b;
*((unsigned int *)((unsigned long)context_ptr+0x000061f8+4*14))=0x6aa8ff9e;
*((unsigned int *)((unsigned long)context_ptr+0x000061f8+4*15))=0xb2af8c8f;
*((unsigned int *)((unsigned long)context_ptr+0x000061f8+4*16))=0x4193788a;
*((unsigned int *)((unsigned long)context_ptr+0x000061f8+4*17))=0xa56f1e68;
*((unsigned int *)((unsigned long)context_ptr+0x000061f8+4*18))=0x94dc8a75;
*((unsigned int *)((unsigned long)context_ptr+0x000061f8+4*19))=0x624dc904;
*((unsigned int *)((unsigned long)context_ptr+0x000061f8+4*20))=0x3b4fd8f7;
*((unsigned int *)((unsigned long)context_ptr+0x000061f8+4*21))=0x00c03766;
*((unsigned int *)((unsigned long)context_ptr+0x00003810))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003810+4*1))=0x000064f4;
*((unsigned int *)((unsigned long)context_ptr+0x00003810+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003810+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003810+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003810+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000810))=0x04c00057;
*((unsigned int *)((unsigned long)context_ptr+0x00000810+4*1))=0x000061f8;
*((unsigned int *)((unsigned long)context_ptr+0x00000810+4*2))=0x000063f0;
*((unsigned int *)((unsigned long)context_ptr+0x00000810+4*3))=0x02220057;
*((unsigned int *)((unsigned long)context_ptr+0x00000810+4*4))=0x070487b6;
*((unsigned int *)((unsigned long)context_ptr+0x00000810+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000001b6&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x0000640c,"\xec\x33\x79\xa8\xcd\xdb\x21\xe5\xa3\xb9\x5b\xca\x38\x09\x38\xde\x6e\xbc\x14\x7a\xe2\x7d\x91\xab\x5b\x72\x19\xe2",28))
printf("strip: ec3379a8cddb21e5, Pass\n");
else
printf("strip: ec3379a8cddb21e5, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006510))=0x026a1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006510+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006510+4*2))=0x02020058;
*((unsigned int *)((unsigned long)context_ptr+0x00006510+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x000066b8))=0x0c4ba0da;
*((unsigned int *)((unsigned long)context_ptr+0x000066b8+4*1))=0xb0ccb939;
*((unsigned int *)((unsigned long)context_ptr+0x000066b8+4*2))=0x4ed3cd0e;
*((unsigned int *)((unsigned long)context_ptr+0x000066b8+4*3))=0xe45abb3f;
*((unsigned int *)((unsigned long)context_ptr+0x000066b8+4*4))=0x90a37a9e;
*((unsigned int *)((unsigned long)context_ptr+0x000066b8+4*5))=0x42ef74d6;
*((unsigned int *)((unsigned long)context_ptr+0x000066b8+4*6))=0x8459f119;
*((unsigned int *)((unsigned long)context_ptr+0x000066b8+4*7))=0x8f9c5f4a;
*((unsigned int *)((unsigned long)context_ptr+0x000066b8+4*8))=0x16a09286;
*((unsigned int *)((unsigned long)context_ptr+0x000066b8+4*9))=0x6b7f38d6;
*((unsigned int *)((unsigned long)context_ptr+0x000066b8+4*10))=0x0b46f634;
*((unsigned int *)((unsigned long)context_ptr+0x000066b8+4*11))=0x832a5b1e;
*((unsigned int *)((unsigned long)context_ptr+0x000066b8+4*12))=0x08fd53f9;
*((unsigned int *)((unsigned long)context_ptr+0x000066b8+4*13))=0xabeebe85;
*((unsigned int *)((unsigned long)context_ptr+0x000066b8+4*14))=0xbc771ce4;
*((unsigned int *)((unsigned long)context_ptr+0x000066b8+4*15))=0x98dc5389;
*((unsigned int *)((unsigned long)context_ptr+0x000066b8+4*16))=0x6bc87508;
*((unsigned int *)((unsigned long)context_ptr+0x000066b8+4*17))=0x3d8d7c2a;
*((unsigned int *)((unsigned long)context_ptr+0x000066b8+4*18))=0x5ff484a1;
*((unsigned int *)((unsigned long)context_ptr+0x000066b8+4*19))=0xb3c9e2da;
*((unsigned int *)((unsigned long)context_ptr+0x000066b8+4*20))=0x2389118b;
*((unsigned int *)((unsigned long)context_ptr+0x000066b8+4*21))=0x237e3c5d;
*((unsigned int *)((unsigned long)context_ptr+0x00003828))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003828+4*1))=0x00006400;
*((unsigned int *)((unsigned long)context_ptr+0x00003828+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003828+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003828+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003828+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000828))=0x04c00058;
*((unsigned int *)((unsigned long)context_ptr+0x00000828+4*1))=0x000066b8;
*((unsigned int *)((unsigned long)context_ptr+0x00000828+4*2))=0x00006510;
*((unsigned int *)((unsigned long)context_ptr+0x00000828+4*3))=0x02220058;
*((unsigned int *)((unsigned long)context_ptr+0x00000828+4*4))=0x0dbdb23f;
*((unsigned int *)((unsigned long)context_ptr+0x00000828+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000001bc&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006604,"\x81\x29\xac\xd5\x6a\x05\x3e\xf2\xec\xd6\x11\xe6\xcf\x0a\x51\xa5\x2b\x19\xde\x5e\xad\x23\x90\x9c\x00\x45\xbd\x0c",28))
printf("strip: 8129acd56a053ef2, Pass\n");
else
printf("strip: 8129acd56a053ef2, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x0000641c))=0x026a1002;
*((unsigned int *)((unsigned long)context_ptr+0x0000641c+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x0000641c+4*2))=0x02020059;
*((unsigned int *)((unsigned long)context_ptr+0x0000641c+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x000065bc))=0xe4e34b33;
*((unsigned int *)((unsigned long)context_ptr+0x000065bc+4*1))=0x1006fdc9;
*((unsigned int *)((unsigned long)context_ptr+0x000065bc+4*2))=0x17d8655d;
*((unsigned int *)((unsigned long)context_ptr+0x000065bc+4*3))=0x5ff6335f;
*((unsigned int *)((unsigned long)context_ptr+0x000065bc+4*4))=0x5f127e39;
*((unsigned int *)((unsigned long)context_ptr+0x000065bc+4*5))=0x2684705d;
*((unsigned int *)((unsigned long)context_ptr+0x000065bc+4*6))=0x4f62ad19;
*((unsigned int *)((unsigned long)context_ptr+0x000065bc+4*7))=0x453a815a;
*((unsigned int *)((unsigned long)context_ptr+0x000065bc+4*8))=0x5bcf5df6;
*((unsigned int *)((unsigned long)context_ptr+0x000065bc+4*9))=0xfd331220;
*((unsigned int *)((unsigned long)context_ptr+0x000065bc+4*10))=0x9adafd6b;
*((unsigned int *)((unsigned long)context_ptr+0x000065bc+4*11))=0x3ec62a2c;
*((unsigned int *)((unsigned long)context_ptr+0x000065bc+4*12))=0x388e6779;
*((unsigned int *)((unsigned long)context_ptr+0x000065bc+4*13))=0x3fbbf3bb;
*((unsigned int *)((unsigned long)context_ptr+0x000065bc+4*14))=0x625527d8;
*((unsigned int *)((unsigned long)context_ptr+0x000065bc+4*15))=0x2850598d;
*((unsigned int *)((unsigned long)context_ptr+0x000065bc+4*16))=0xf9bfb063;
*((unsigned int *)((unsigned long)context_ptr+0x000065bc+4*17))=0xc50c98a1;
*((unsigned int *)((unsigned long)context_ptr+0x000065bc+4*18))=0x02fd3c72;
*((unsigned int *)((unsigned long)context_ptr+0x000065bc+4*19))=0x3d3aed79;
*((unsigned int *)((unsigned long)context_ptr+0x000065bc+4*20))=0xa9a9b221;
*((unsigned int *)((unsigned long)context_ptr+0x000065bc+4*21))=0xec0cb2b5;
*((unsigned int *)((unsigned long)context_ptr+0x000065bc+4*22))=0x000000b8;
*((unsigned int *)((unsigned long)context_ptr+0x00003840))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003840+4*1))=0x00006710;
*((unsigned int *)((unsigned long)context_ptr+0x00003840+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003840+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003840+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003840+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000840))=0x04c00059;
*((unsigned int *)((unsigned long)context_ptr+0x00000840+4*1))=0x000065bc;
*((unsigned int *)((unsigned long)context_ptr+0x00000840+4*2))=0x0000641c;
*((unsigned int *)((unsigned long)context_ptr+0x00000840+4*3))=0x02220059;
*((unsigned int *)((unsigned long)context_ptr+0x00000840+4*4))=0x0d20dc30;
*((unsigned int *)((unsigned long)context_ptr+0x00000840+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000001c2&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006620,"\xb7\x24\x7b\x7d\xa4\x05\x64\x62\x74\xdc\xd0\xae\x5e\x51\x1c\x87\xf9\x6e\xa7\xb7\x59\x4c\x0a\xbc\x70\xe7\x24\x85",28))
printf("strip: b7247b7da4056462, Pass\n");
else
printf("strip: b7247b7da4056462, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006520))=0x026a1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006520+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006520+4*2))=0x0202005a;
*((unsigned int *)((unsigned long)context_ptr+0x00006520+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x00006250))=0x2595dc28;
*((unsigned int *)((unsigned long)context_ptr+0x00006250+4*1))=0xaba3c6d3;
*((unsigned int *)((unsigned long)context_ptr+0x00006250+4*2))=0xdbb42769;
*((unsigned int *)((unsigned long)context_ptr+0x00006250+4*3))=0xd69e1955;
*((unsigned int *)((unsigned long)context_ptr+0x00006250+4*4))=0x0ec627fb;
*((unsigned int *)((unsigned long)context_ptr+0x00006250+4*5))=0x0f1f0184;
*((unsigned int *)((unsigned long)context_ptr+0x00006250+4*6))=0x2c99ffca;
*((unsigned int *)((unsigned long)context_ptr+0x00006250+4*7))=0x8158304b;
*((unsigned int *)((unsigned long)context_ptr+0x00006250+4*8))=0x1656589f;
*((unsigned int *)((unsigned long)context_ptr+0x00006250+4*9))=0xe0dc4b05;
*((unsigned int *)((unsigned long)context_ptr+0x00006250+4*10))=0x724380f0;
*((unsigned int *)((unsigned long)context_ptr+0x00006250+4*11))=0x234a761b;
*((unsigned int *)((unsigned long)context_ptr+0x00006250+4*12))=0x56d51556;
*((unsigned int *)((unsigned long)context_ptr+0x00006250+4*13))=0x0b912aff;
*((unsigned int *)((unsigned long)context_ptr+0x00006250+4*14))=0xfe356bd2;
*((unsigned int *)((unsigned long)context_ptr+0x00006250+4*15))=0x7635d342;
*((unsigned int *)((unsigned long)context_ptr+0x00006250+4*16))=0x0c6a50c1;
*((unsigned int *)((unsigned long)context_ptr+0x00006250+4*17))=0xa73f783a;
*((unsigned int *)((unsigned long)context_ptr+0x00006250+4*18))=0x42f9c354;
*((unsigned int *)((unsigned long)context_ptr+0x00006250+4*19))=0x604dd3f5;
*((unsigned int *)((unsigned long)context_ptr+0x00006250+4*20))=0xc3c71d4f;
*((unsigned int *)((unsigned long)context_ptr+0x00006250+4*21))=0x80646cff;
*((unsigned int *)((unsigned long)context_ptr+0x00006250+4*22))=0x0000e7a9;
*((unsigned int *)((unsigned long)context_ptr+0x00003858))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003858+4*1))=0x00006618;
*((unsigned int *)((unsigned long)context_ptr+0x00003858+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003858+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003858+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003858+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000858))=0x04c0005a;
*((unsigned int *)((unsigned long)context_ptr+0x00000858+4*1))=0x00006250;
*((unsigned int *)((unsigned long)context_ptr+0x00000858+4*2))=0x00006520;
*((unsigned int *)((unsigned long)context_ptr+0x00000858+4*3))=0x0222005a;
*((unsigned int *)((unsigned long)context_ptr+0x00000858+4*4))=0x0545875f;
*((unsigned int *)((unsigned long)context_ptr+0x00000858+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000001c8&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006438,"\x44\x30\xf3\x57\x3e\x9e\xfe\x42\xd5\xd3\xce\x6b\x1b\xac\x02\x2b\xa9\xc5\xce\xfe\xce\x89\xec\x8d\x76\x8a\x39\xcc",28))
printf("strip: 4430f3573e9efe42, Pass\n");
else
printf("strip: 4430f3573e9efe42, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006058))=0x026a1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*2))=0x0202005b;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x000062ac))=0x2661e004;
*((unsigned int *)((unsigned long)context_ptr+0x000062ac+4*1))=0x30668837;
*((unsigned int *)((unsigned long)context_ptr+0x000062ac+4*2))=0xb4b5fe1b;
*((unsigned int *)((unsigned long)context_ptr+0x000062ac+4*3))=0x9898691e;
*((unsigned int *)((unsigned long)context_ptr+0x000062ac+4*4))=0x3b98e523;
*((unsigned int *)((unsigned long)context_ptr+0x000062ac+4*5))=0x73fd8c78;
*((unsigned int *)((unsigned long)context_ptr+0x000062ac+4*6))=0xc65f4823;
*((unsigned int *)((unsigned long)context_ptr+0x000062ac+4*7))=0x672c78a4;
*((unsigned int *)((unsigned long)context_ptr+0x000062ac+4*8))=0xd29a8ab2;
*((unsigned int *)((unsigned long)context_ptr+0x000062ac+4*9))=0x898ee91a;
*((unsigned int *)((unsigned long)context_ptr+0x000062ac+4*10))=0xf2e09f68;
*((unsigned int *)((unsigned long)context_ptr+0x000062ac+4*11))=0x9c5f357e;
*((unsigned int *)((unsigned long)context_ptr+0x000062ac+4*12))=0x0891f3ef;
*((unsigned int *)((unsigned long)context_ptr+0x000062ac+4*13))=0xb372fed9;
*((unsigned int *)((unsigned long)context_ptr+0x000062ac+4*14))=0x6bcaa098;
*((unsigned int *)((unsigned long)context_ptr+0x000062ac+4*15))=0xb42a4b44;
*((unsigned int *)((unsigned long)context_ptr+0x000062ac+4*16))=0x9a7d45c4;
*((unsigned int *)((unsigned long)context_ptr+0x000062ac+4*17))=0x3e127f91;
*((unsigned int *)((unsigned long)context_ptr+0x000062ac+4*18))=0x17587bb6;
*((unsigned int *)((unsigned long)context_ptr+0x000062ac+4*19))=0x88237b9c;
*((unsigned int *)((unsigned long)context_ptr+0x000062ac+4*20))=0xa3567e90;
*((unsigned int *)((unsigned long)context_ptr+0x000062ac+4*21))=0xfa257436;
*((unsigned int *)((unsigned long)context_ptr+0x000062ac+4*22))=0x003402eb;
*((unsigned int *)((unsigned long)context_ptr+0x00003870))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003870+4*1))=0x0000672c;
*((unsigned int *)((unsigned long)context_ptr+0x00003870+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003870+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003870+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003870+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000870))=0x04c0005b;
*((unsigned int *)((unsigned long)context_ptr+0x00000870+4*1))=0x000062ac;
*((unsigned int *)((unsigned long)context_ptr+0x00000870+4*2))=0x00006058;
*((unsigned int *)((unsigned long)context_ptr+0x00000870+4*3))=0x0222005b;
*((unsigned int *)((unsigned long)context_ptr+0x00000870+4*4))=0x0535cc06;
*((unsigned int *)((unsigned long)context_ptr+0x00000870+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000001ce&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006078,"\x96\x2e\xaf\x9e\x60\x65\xdc\x1e\x0d\x2c\x94\x79\xd5\xc2\xdd\x23\x4b\xee\xe7\x00\x55\xc9\x73\xcd\xdc\x6b\x9c\x35",28))
printf("strip: 962eaf9e6065dc1e, Pass\n");
else
printf("strip: 962eaf9e6065dc1e, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006048))=0x026a1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006048+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006048+4*2))=0x0202005c;
*((unsigned int *)((unsigned long)context_ptr+0x00006048+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x00006848))=0x9fe82090;
*((unsigned int *)((unsigned long)context_ptr+0x00006848+4*1))=0x13ebc9bc;
*((unsigned int *)((unsigned long)context_ptr+0x00006848+4*2))=0xf39d0c3c;
*((unsigned int *)((unsigned long)context_ptr+0x00006848+4*3))=0x1fa77c50;
*((unsigned int *)((unsigned long)context_ptr+0x00006848+4*4))=0x888e8ff9;
*((unsigned int *)((unsigned long)context_ptr+0x00006848+4*5))=0xbd064507;
*((unsigned int *)((unsigned long)context_ptr+0x00006848+4*6))=0x0e20e75b;
*((unsigned int *)((unsigned long)context_ptr+0x00006848+4*7))=0x948f2d09;
*((unsigned int *)((unsigned long)context_ptr+0x00006848+4*8))=0x812f74b4;
*((unsigned int *)((unsigned long)context_ptr+0x00006848+4*9))=0xe1359134;
*((unsigned int *)((unsigned long)context_ptr+0x00006848+4*10))=0xea34c471;
*((unsigned int *)((unsigned long)context_ptr+0x00006848+4*11))=0xcbedac01;
*((unsigned int *)((unsigned long)context_ptr+0x00006848+4*12))=0x05f206a0;
*((unsigned int *)((unsigned long)context_ptr+0x00006848+4*13))=0x4ab520b3;
*((unsigned int *)((unsigned long)context_ptr+0x00006848+4*14))=0x560ede5d;
*((unsigned int *)((unsigned long)context_ptr+0x00006848+4*15))=0x3cfa9176;
*((unsigned int *)((unsigned long)context_ptr+0x00006848+4*16))=0x244554b9;
*((unsigned int *)((unsigned long)context_ptr+0x00006848+4*17))=0xbb0c0419;
*((unsigned int *)((unsigned long)context_ptr+0x00006848+4*18))=0x9a2034f0;
*((unsigned int *)((unsigned long)context_ptr+0x00006848+4*19))=0xef1d18c0;
*((unsigned int *)((unsigned long)context_ptr+0x00006848+4*20))=0x4046235b;
*((unsigned int *)((unsigned long)context_ptr+0x00006848+4*21))=0xfe61daa1;
*((unsigned int *)((unsigned long)context_ptr+0x00006848+4*22))=0x802c2776;
*((unsigned int *)((unsigned long)context_ptr+0x00003888))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003888+4*1))=0x00006078;
*((unsigned int *)((unsigned long)context_ptr+0x00003888+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003888+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003888+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003888+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000888))=0x04c0005c;
*((unsigned int *)((unsigned long)context_ptr+0x00000888+4*1))=0x00006848;
*((unsigned int *)((unsigned long)context_ptr+0x00000888+4*2))=0x00006048;
*((unsigned int *)((unsigned long)context_ptr+0x00000888+4*3))=0x0222005c;
*((unsigned int *)((unsigned long)context_ptr+0x00000888+4*4))=0x032636ee;
*((unsigned int *)((unsigned long)context_ptr+0x00000888+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000001d4&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006454,"\x21\x95\xd9\x47\x98\x9e\x56\xf5\x5a\x16\xf3\x72\x58\x4e\xa2\x77\xae\x65\xe5\x34\x80\xac\x0f\x38\x5c\xfd\xf8\x10",28))
printf("strip: 2195d947989e56f5, Pass\n");
else
printf("strip: 2195d947989e56f5, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006068))=0x026a1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006068+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006068+4*2))=0x0202005d;
*((unsigned int *)((unsigned long)context_ptr+0x00006068+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x000068a4))=0x292c1466;
*((unsigned int *)((unsigned long)context_ptr+0x000068a4+4*1))=0x5009ad8d;
*((unsigned int *)((unsigned long)context_ptr+0x000068a4+4*2))=0x8bb7bbf3;
*((unsigned int *)((unsigned long)context_ptr+0x000068a4+4*3))=0x8c20a402;
*((unsigned int *)((unsigned long)context_ptr+0x000068a4+4*4))=0x49a97d18;
*((unsigned int *)((unsigned long)context_ptr+0x000068a4+4*5))=0x0661f3bf;
*((unsigned int *)((unsigned long)context_ptr+0x000068a4+4*6))=0x87463c9a;
*((unsigned int *)((unsigned long)context_ptr+0x000068a4+4*7))=0x1d49de41;
*((unsigned int *)((unsigned long)context_ptr+0x000068a4+4*8))=0xb0be1ea5;
*((unsigned int *)((unsigned long)context_ptr+0x000068a4+4*9))=0xe551462a;
*((unsigned int *)((unsigned long)context_ptr+0x000068a4+4*10))=0xf93ec3f8;
*((unsigned int *)((unsigned long)context_ptr+0x000068a4+4*11))=0x0a7a3147;
*((unsigned int *)((unsigned long)context_ptr+0x000068a4+4*12))=0x1cb830e5;
*((unsigned int *)((unsigned long)context_ptr+0x000068a4+4*13))=0xc38ffe4a;
*((unsigned int *)((unsigned long)context_ptr+0x000068a4+4*14))=0x9b7e1850;
*((unsigned int *)((unsigned long)context_ptr+0x000068a4+4*15))=0xbed73d54;
*((unsigned int *)((unsigned long)context_ptr+0x000068a4+4*16))=0xc37b7c3c;
*((unsigned int *)((unsigned long)context_ptr+0x000068a4+4*17))=0x3da19785;
*((unsigned int *)((unsigned long)context_ptr+0x000068a4+4*18))=0xcf55ae0e;
*((unsigned int *)((unsigned long)context_ptr+0x000068a4+4*19))=0x0ddbb0ef;
*((unsigned int *)((unsigned long)context_ptr+0x000068a4+4*20))=0x54c5c7d7;
*((unsigned int *)((unsigned long)context_ptr+0x000068a4+4*21))=0xe7887e04;
*((unsigned int *)((unsigned long)context_ptr+0x000068a4+4*22))=0xdd4b816c;
*((unsigned int *)((unsigned long)context_ptr+0x000068a4+4*23))=0x00000004;
*((unsigned int *)((unsigned long)context_ptr+0x000038a0))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x000038a0+4*1))=0x00006308;
*((unsigned int *)((unsigned long)context_ptr+0x000038a0+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000038a0+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000038a0+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000038a0+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x000008a0))=0x04c0005d;
*((unsigned int *)((unsigned long)context_ptr+0x000008a0+4*1))=0x000068a4;
*((unsigned int *)((unsigned long)context_ptr+0x000008a0+4*2))=0x00006068;
*((unsigned int *)((unsigned long)context_ptr+0x000008a0+4*3))=0x0222005d;
*((unsigned int *)((unsigned long)context_ptr+0x000008a0+4*4))=0x0e61c4bb;
*((unsigned int *)((unsigned long)context_ptr+0x000008a0+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000001da&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006470,"\x60\xde\x6d\xe2\x72\x7d\x3b\x0d\xfa\x93\x5d\xcd\x8b\x5f\x8d\x96\xd0\x3a\x0d\xe6\x57\x56\x43\x1f\x32\x01\x91\xa3",28))
printf("strip: 60de6de2727d3b0d, Pass\n");
else
printf("strip: 60de6de2727d3b0d, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006094))=0x026a1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006094+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006094+4*2))=0x0202005e;
*((unsigned int *)((unsigned long)context_ptr+0x00006094+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x0000642c))=0xd63dc48b;
*((unsigned int *)((unsigned long)context_ptr+0x0000642c+4*1))=0x5e2a0717;
*((unsigned int *)((unsigned long)context_ptr+0x0000642c+4*2))=0x6cac4983;
*((unsigned int *)((unsigned long)context_ptr+0x0000642c+4*3))=0x5116ca02;
*((unsigned int *)((unsigned long)context_ptr+0x0000642c+4*4))=0xcdd1c327;
*((unsigned int *)((unsigned long)context_ptr+0x0000642c+4*5))=0xb0eb1ff7;
*((unsigned int *)((unsigned long)context_ptr+0x0000642c+4*6))=0x1a1cfa1e;
*((unsigned int *)((unsigned long)context_ptr+0x0000642c+4*7))=0xee1c3dab;
*((unsigned int *)((unsigned long)context_ptr+0x0000642c+4*8))=0x9e4f30e2;
*((unsigned int *)((unsigned long)context_ptr+0x0000642c+4*9))=0x9d93de90;
*((unsigned int *)((unsigned long)context_ptr+0x0000642c+4*10))=0x54042fed;
*((unsigned int *)((unsigned long)context_ptr+0x0000642c+4*11))=0x1076aaed;
*((unsigned int *)((unsigned long)context_ptr+0x0000642c+4*12))=0x36310874;
*((unsigned int *)((unsigned long)context_ptr+0x0000642c+4*13))=0xb51dc77a;
*((unsigned int *)((unsigned long)context_ptr+0x0000642c+4*14))=0xf103af82;
*((unsigned int *)((unsigned long)context_ptr+0x0000642c+4*15))=0xae246517;
*((unsigned int *)((unsigned long)context_ptr+0x0000642c+4*16))=0xd11e3e4a;
*((unsigned int *)((unsigned long)context_ptr+0x0000642c+4*17))=0x64cc4234;
*((unsigned int *)((unsigned long)context_ptr+0x0000642c+4*18))=0x88dfc8b1;
*((unsigned int *)((unsigned long)context_ptr+0x0000642c+4*19))=0x8e96d139;
*((unsigned int *)((unsigned long)context_ptr+0x0000642c+4*20))=0x5b999f27;
*((unsigned int *)((unsigned long)context_ptr+0x0000642c+4*21))=0xae3b73bd;
*((unsigned int *)((unsigned long)context_ptr+0x0000642c+4*22))=0xc556d2e8;
*((unsigned int *)((unsigned long)context_ptr+0x0000642c+4*23))=0x000003cc;
*((unsigned int *)((unsigned long)context_ptr+0x000038b8))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x000038b8+4*1))=0x00006634;
*((unsigned int *)((unsigned long)context_ptr+0x000038b8+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000038b8+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000038b8+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000038b8+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x000008b8))=0x04c0005e;
*((unsigned int *)((unsigned long)context_ptr+0x000008b8+4*1))=0x0000642c;
*((unsigned int *)((unsigned long)context_ptr+0x000008b8+4*2))=0x00006094;
*((unsigned int *)((unsigned long)context_ptr+0x000008b8+4*3))=0x0222005e;
*((unsigned int *)((unsigned long)context_ptr+0x000008b8+4*4))=0x0b1d5f84;
*((unsigned int *)((unsigned long)context_ptr+0x000008b8+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000001e0&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x0000668c,"\x8a\x46\x68\xab\x52\x57\x76\x1b\xd9\x38\xcb\xaa\x48\x14\xba\x53\xfa\x96\x2f\xd6\x3d\xb0\x99\x5f\xeb\xe8\xb5\xb7",28))
printf("strip: 8a4668ab5257761b, Pass\n");
else
printf("strip: 8a4668ab5257761b, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x0000648c))=0x026a1002;
*((unsigned int *)((unsigned long)context_ptr+0x0000648c+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x0000648c+4*2))=0x0202005f;
*((unsigned int *)((unsigned long)context_ptr+0x0000648c+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x00006324))=0x5c34ca1c;
*((unsigned int *)((unsigned long)context_ptr+0x00006324+4*1))=0x9e41662f;
*((unsigned int *)((unsigned long)context_ptr+0x00006324+4*2))=0xacf1dc26;
*((unsigned int *)((unsigned long)context_ptr+0x00006324+4*3))=0xe1995242;
*((unsigned int *)((unsigned long)context_ptr+0x00006324+4*4))=0xcadb9db7;
*((unsigned int *)((unsigned long)context_ptr+0x00006324+4*5))=0xd87f30b3;
*((unsigned int *)((unsigned long)context_ptr+0x00006324+4*6))=0xb3161064;
*((unsigned int *)((unsigned long)context_ptr+0x00006324+4*7))=0xd43c3cb9;
*((unsigned int *)((unsigned long)context_ptr+0x00006324+4*8))=0x307630cb;
*((unsigned int *)((unsigned long)context_ptr+0x00006324+4*9))=0xf703d93a;
*((unsigned int *)((unsigned long)context_ptr+0x00006324+4*10))=0x5c6e8f29;
*((unsigned int *)((unsigned long)context_ptr+0x00006324+4*11))=0xd068aaf3;
*((unsigned int *)((unsigned long)context_ptr+0x00006324+4*12))=0x6cdb5552;
*((unsigned int *)((unsigned long)context_ptr+0x00006324+4*13))=0xdc576e5b;
*((unsigned int *)((unsigned long)context_ptr+0x00006324+4*14))=0x8a9d8a81;
*((unsigned int *)((unsigned long)context_ptr+0x00006324+4*15))=0x131f156b;
*((unsigned int *)((unsigned long)context_ptr+0x00006324+4*16))=0xf5237446;
*((unsigned int *)((unsigned long)context_ptr+0x00006324+4*17))=0x8c4e7a91;
*((unsigned int *)((unsigned long)context_ptr+0x00006324+4*18))=0xfda918b9;
*((unsigned int *)((unsigned long)context_ptr+0x00006324+4*19))=0xa2523e31;
*((unsigned int *)((unsigned long)context_ptr+0x00006324+4*20))=0x91e7faa8;
*((unsigned int *)((unsigned long)context_ptr+0x00006324+4*21))=0x8ba487ce;
*((unsigned int *)((unsigned long)context_ptr+0x00006324+4*22))=0x1bd32178;
*((unsigned int *)((unsigned long)context_ptr+0x00006324+4*23))=0x00c71a69;
*((unsigned int *)((unsigned long)context_ptr+0x000038d0))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x000038d0+4*1))=0x00006650;
*((unsigned int *)((unsigned long)context_ptr+0x000038d0+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000038d0+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000038d0+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000038d0+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x000008d0))=0x04c0005f;
*((unsigned int *)((unsigned long)context_ptr+0x000008d0+4*1))=0x00006324;
*((unsigned int *)((unsigned long)context_ptr+0x000008d0+4*2))=0x0000648c;
*((unsigned int *)((unsigned long)context_ptr+0x000008d0+4*3))=0x0222005f;
*((unsigned int *)((unsigned long)context_ptr+0x000008d0+4*4))=0x0d56fe9a;
*((unsigned int *)((unsigned long)context_ptr+0x000008d0+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000001e6&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006388,"\xeb\x0f\xc4\x32\x5c\x88\x88\xf8\x8f\x69\x9d\x5f\xe2\x44\x64\x7f\x3d\x91\x3a\x44\x51\x93\x18\xa1\x91\x21\xf0\x83",28))
printf("strip: eb0fc4325c8888f8, Pass\n");
else
printf("strip: eb0fc4325c8888f8, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x0000649c))=0x026a1002;
*((unsigned int *)((unsigned long)context_ptr+0x0000649c+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x0000649c+4*2))=0x02020060;
*((unsigned int *)((unsigned long)context_ptr+0x0000649c+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x00006748))=0xf182ba38;
*((unsigned int *)((unsigned long)context_ptr+0x00006748+4*1))=0xf5531712;
*((unsigned int *)((unsigned long)context_ptr+0x00006748+4*2))=0x55442258;
*((unsigned int *)((unsigned long)context_ptr+0x00006748+4*3))=0x50142252;
*((unsigned int *)((unsigned long)context_ptr+0x00006748+4*4))=0x7c86ab4f;
*((unsigned int *)((unsigned long)context_ptr+0x00006748+4*5))=0xd0de945c;
*((unsigned int *)((unsigned long)context_ptr+0x00006748+4*6))=0xb3f5f966;
*((unsigned int *)((unsigned long)context_ptr+0x00006748+4*7))=0x4bb2e51a;
*((unsigned int *)((unsigned long)context_ptr+0x00006748+4*8))=0x5cc704c5;
*((unsigned int *)((unsigned long)context_ptr+0x00006748+4*9))=0x82e78e54;
*((unsigned int *)((unsigned long)context_ptr+0x00006748+4*10))=0xc95e7539;
*((unsigned int *)((unsigned long)context_ptr+0x00006748+4*11))=0x8fee1d06;
*((unsigned int *)((unsigned long)context_ptr+0x00006748+4*12))=0xe917a0fe;
*((unsigned int *)((unsigned long)context_ptr+0x00006748+4*13))=0xde65ba3a;
*((unsigned int *)((unsigned long)context_ptr+0x00006748+4*14))=0xc1cf93d5;
*((unsigned int *)((unsigned long)context_ptr+0x00006748+4*15))=0xdcb5fca5;
*((unsigned int *)((unsigned long)context_ptr+0x00006748+4*16))=0xf8ddd4c8;
*((unsigned int *)((unsigned long)context_ptr+0x00006748+4*17))=0x410a51a5;
*((unsigned int *)((unsigned long)context_ptr+0x00006748+4*18))=0x4426c5cc;
*((unsigned int *)((unsigned long)context_ptr+0x00006748+4*19))=0x2e0c8825;
*((unsigned int *)((unsigned long)context_ptr+0x00006748+4*20))=0xc220fc46;
*((unsigned int *)((unsigned long)context_ptr+0x00006748+4*21))=0x94c103cd;
*((unsigned int *)((unsigned long)context_ptr+0x00006748+4*22))=0xca969215;
*((unsigned int *)((unsigned long)context_ptr+0x00006748+4*23))=0xb9fc5e89;
*((unsigned int *)((unsigned long)context_ptr+0x000038e8))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x000038e8+4*1))=0x00006384;
*((unsigned int *)((unsigned long)context_ptr+0x000038e8+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000038e8+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000038e8+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000038e8+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x000008e8))=0x04c00060;
*((unsigned int *)((unsigned long)context_ptr+0x000008e8+4*1))=0x00006748;
*((unsigned int *)((unsigned long)context_ptr+0x000008e8+4*2))=0x0000649c;
*((unsigned int *)((unsigned long)context_ptr+0x000008e8+4*3))=0x02220060;
*((unsigned int *)((unsigned long)context_ptr+0x000008e8+4*4))=0x0ffeec84;
*((unsigned int *)((unsigned long)context_ptr+0x000008e8+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000001ec&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000063a4,"\x4d\x00\xed\xca\x47\xda\xfb\xb7\xeb\x4b\x94\xbc\x74\x3c\x69\xbe\x78\x32\xd9\x2e\xe6\x97\x06\xdc\xf0\x7b\x61\x06",28))
printf("strip: 4d00edca47dafbb7, Pass\n");
else
printf("strip: 4d00edca47dafbb7, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000063a0))=0x026a1002;
*((unsigned int *)((unsigned long)context_ptr+0x000063a0+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000063a0+4*2))=0x02020061;
*((unsigned int *)((unsigned long)context_ptr+0x000063a0+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x000060a4))=0x9dbfd393;
*((unsigned int *)((unsigned long)context_ptr+0x000060a4+4*1))=0x63c82121;
*((unsigned int *)((unsigned long)context_ptr+0x000060a4+4*2))=0x0fecf66d;
*((unsigned int *)((unsigned long)context_ptr+0x000060a4+4*3))=0x6bae227c;
*((unsigned int *)((unsigned long)context_ptr+0x000060a4+4*4))=0xe3929afe;
*((unsigned int *)((unsigned long)context_ptr+0x000060a4+4*5))=0xd1c33f53;
*((unsigned int *)((unsigned long)context_ptr+0x000060a4+4*6))=0xb6e009ac;
*((unsigned int *)((unsigned long)context_ptr+0x000060a4+4*7))=0x0518ef4e;
*((unsigned int *)((unsigned long)context_ptr+0x000060a4+4*8))=0xe342d6cb;
*((unsigned int *)((unsigned long)context_ptr+0x000060a4+4*9))=0x1240ab85;
*((unsigned int *)((unsigned long)context_ptr+0x000060a4+4*10))=0xfda54339;
*((unsigned int *)((unsigned long)context_ptr+0x000060a4+4*11))=0x1a866486;
*((unsigned int *)((unsigned long)context_ptr+0x000060a4+4*12))=0xa4a4a8b6;
*((unsigned int *)((unsigned long)context_ptr+0x000060a4+4*13))=0x5671ea22;
*((unsigned int *)((unsigned long)context_ptr+0x000060a4+4*14))=0x13e45159;
*((unsigned int *)((unsigned long)context_ptr+0x000060a4+4*15))=0x8719428f;
*((unsigned int *)((unsigned long)context_ptr+0x000060a4+4*16))=0xeb5c598e;
*((unsigned int *)((unsigned long)context_ptr+0x000060a4+4*17))=0xaab1cd8c;
*((unsigned int *)((unsigned long)context_ptr+0x000060a4+4*18))=0x7774beef;
*((unsigned int *)((unsigned long)context_ptr+0x000060a4+4*19))=0xc3cbd8ca;
*((unsigned int *)((unsigned long)context_ptr+0x000060a4+4*20))=0x2f0f9b55;
*((unsigned int *)((unsigned long)context_ptr+0x000060a4+4*21))=0xb00ff824;
*((unsigned int *)((unsigned long)context_ptr+0x000060a4+4*22))=0xa63796d4;
*((unsigned int *)((unsigned long)context_ptr+0x000060a4+4*23))=0xea4c4ec1;
*((unsigned int *)((unsigned long)context_ptr+0x000060a4+4*24))=0x0000007d;
*((unsigned int *)((unsigned long)context_ptr+0x00003900))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003900+4*1))=0x00006108;
*((unsigned int *)((unsigned long)context_ptr+0x00003900+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003900+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003900+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003900+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000900))=0x04c00061;
*((unsigned int *)((unsigned long)context_ptr+0x00000900+4*1))=0x000060a4;
*((unsigned int *)((unsigned long)context_ptr+0x00000900+4*2))=0x000063a0;
*((unsigned int *)((unsigned long)context_ptr+0x00000900+4*3))=0x02220061;
*((unsigned int *)((unsigned long)context_ptr+0x00000900+4*4))=0x019cc9ad;
*((unsigned int *)((unsigned long)context_ptr+0x00000900+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000001f2&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006530,"\x68\x63\x6f\x27\x7c\xe9\x40\xfc\xe1\x96\x3c\x27\xa8\xec\x90\x42\x4a\x7f\x6e\x3c\x46\x9b\xff\x7e\xf5\x41\x2d\xaa",28))
printf("strip: 68636f277ce940fc, Pass\n");
else
printf("strip: 68636f277ce940fc, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006530))=0x026a1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006530+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006530+4*2))=0x02020062;
*((unsigned int *)((unsigned long)context_ptr+0x00006530+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x00006124))=0x62c5a95a;
*((unsigned int *)((unsigned long)context_ptr+0x00006124+4*1))=0x50dffc30;
*((unsigned int *)((unsigned long)context_ptr+0x00006124+4*2))=0x2cd6a219;
*((unsigned int *)((unsigned long)context_ptr+0x00006124+4*3))=0xac095dad;
*((unsigned int *)((unsigned long)context_ptr+0x00006124+4*4))=0x2d3ccb6d;
*((unsigned int *)((unsigned long)context_ptr+0x00006124+4*5))=0x92e1c258;
*((unsigned int *)((unsigned long)context_ptr+0x00006124+4*6))=0x06292d9c;
*((unsigned int *)((unsigned long)context_ptr+0x00006124+4*7))=0x32ddc73a;
*((unsigned int *)((unsigned long)context_ptr+0x00006124+4*8))=0x94cf6522;
*((unsigned int *)((unsigned long)context_ptr+0x00006124+4*9))=0x064112c8;
*((unsigned int *)((unsigned long)context_ptr+0x00006124+4*10))=0x1872fa77;
*((unsigned int *)((unsigned long)context_ptr+0x00006124+4*11))=0xfe14dc11;
*((unsigned int *)((unsigned long)context_ptr+0x00006124+4*12))=0x12743a1b;
*((unsigned int *)((unsigned long)context_ptr+0x00006124+4*13))=0x2847bfc2;
*((unsigned int *)((unsigned long)context_ptr+0x00006124+4*14))=0x0163b0f1;
*((unsigned int *)((unsigned long)context_ptr+0x00006124+4*15))=0x47867c36;
*((unsigned int *)((unsigned long)context_ptr+0x00006124+4*16))=0xa12632ef;
*((unsigned int *)((unsigned long)context_ptr+0x00006124+4*17))=0x77d9e94f;
*((unsigned int *)((unsigned long)context_ptr+0x00006124+4*18))=0x5c864c7d;
*((unsigned int *)((unsigned long)context_ptr+0x00006124+4*19))=0x751e88fb;
*((unsigned int *)((unsigned long)context_ptr+0x00006124+4*20))=0x854a816a;
*((unsigned int *)((unsigned long)context_ptr+0x00006124+4*21))=0xb34ed2a6;
*((unsigned int *)((unsigned long)context_ptr+0x00006124+4*22))=0x9230cb56;
*((unsigned int *)((unsigned long)context_ptr+0x00006124+4*23))=0x8f6beb39;
*((unsigned int *)((unsigned long)context_ptr+0x00006124+4*24))=0x0000af0b;
*((unsigned int *)((unsigned long)context_ptr+0x00003918))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003918+4*1))=0x000063b0;
*((unsigned int *)((unsigned long)context_ptr+0x00003918+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003918+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003918+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003918+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000918))=0x04c00062;
*((unsigned int *)((unsigned long)context_ptr+0x00000918+4*1))=0x00006124;
*((unsigned int *)((unsigned long)context_ptr+0x00000918+4*2))=0x00006530;
*((unsigned int *)((unsigned long)context_ptr+0x00000918+4*3))=0x02220062;
*((unsigned int *)((unsigned long)context_ptr+0x00000918+4*4))=0x06bb35fd;
*((unsigned int *)((unsigned long)context_ptr+0x00000918+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000001f8&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000064ac,"\x3a\x7c\x85\x0b\x9a\xfe\xcf\xb8\x8a\x51\x48\x44\x1f\x3c\x3d\x0e\x96\x53\x89\xb5\x59\xd8\x16\x3d\xef\x07\x38\x20",28))
printf("strip: 3a7c850b9afecfb8, Pass\n");
else
printf("strip: 3a7c850b9afecfb8, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000063cc))=0x026a1002;
*((unsigned int *)((unsigned long)context_ptr+0x000063cc+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000063cc+4*2))=0x02020063;
*((unsigned int *)((unsigned long)context_ptr+0x000063cc+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x00006904))=0xbaedb5b4;
*((unsigned int *)((unsigned long)context_ptr+0x00006904+4*1))=0x7e104f86;
*((unsigned int *)((unsigned long)context_ptr+0x00006904+4*2))=0x8804feb8;
*((unsigned int *)((unsigned long)context_ptr+0x00006904+4*3))=0x9a661bf0;
*((unsigned int *)((unsigned long)context_ptr+0x00006904+4*4))=0x82665eb3;
*((unsigned int *)((unsigned long)context_ptr+0x00006904+4*5))=0xab2f5c0a;
*((unsigned int *)((unsigned long)context_ptr+0x00006904+4*6))=0xcc0145a9;
*((unsigned int *)((unsigned long)context_ptr+0x00006904+4*7))=0xdf00f908;
*((unsigned int *)((unsigned long)context_ptr+0x00006904+4*8))=0xf23e3287;
*((unsigned int *)((unsigned long)context_ptr+0x00006904+4*9))=0x58875e1c;
*((unsigned int *)((unsigned long)context_ptr+0x00006904+4*10))=0x51766149;
*((unsigned int *)((unsigned long)context_ptr+0x00006904+4*11))=0xeae0b620;
*((unsigned int *)((unsigned long)context_ptr+0x00006904+4*12))=0x00b7a0a9;
*((unsigned int *)((unsigned long)context_ptr+0x00006904+4*13))=0x2fc9a24d;
*((unsigned int *)((unsigned long)context_ptr+0x00006904+4*14))=0x89869a1f;
*((unsigned int *)((unsigned long)context_ptr+0x00006904+4*15))=0x3c1cd57b;
*((unsigned int *)((unsigned long)context_ptr+0x00006904+4*16))=0x6292d397;
*((unsigned int *)((unsigned long)context_ptr+0x00006904+4*17))=0xef365a59;
*((unsigned int *)((unsigned long)context_ptr+0x00006904+4*18))=0x675ae2c6;
*((unsigned int *)((unsigned long)context_ptr+0x00006904+4*19))=0xa2770536;
*((unsigned int *)((unsigned long)context_ptr+0x00006904+4*20))=0xc53ef9f3;
*((unsigned int *)((unsigned long)context_ptr+0x00006904+4*21))=0xe091282c;
*((unsigned int *)((unsigned long)context_ptr+0x00006904+4*22))=0x4fb19856;
*((unsigned int *)((unsigned long)context_ptr+0x00006904+4*23))=0x92a1940b;
*((unsigned int *)((unsigned long)context_ptr+0x00006904+4*24))=0x002682b8;
*((unsigned int *)((unsigned long)context_ptr+0x00003930))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003930+4*1))=0x000064ac;
*((unsigned int *)((unsigned long)context_ptr+0x00003930+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003930+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003930+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003930+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000930))=0x04c00063;
*((unsigned int *)((unsigned long)context_ptr+0x00000930+4*1))=0x00006904;
*((unsigned int *)((unsigned long)context_ptr+0x00000930+4*2))=0x000063cc;
*((unsigned int *)((unsigned long)context_ptr+0x00000930+4*3))=0x02220063;
*((unsigned int *)((unsigned long)context_ptr+0x00000930+4*4))=0x0b04c645;
*((unsigned int *)((unsigned long)context_ptr+0x00000930+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000001fe&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000064c8,"\x9e\xef\xc0\x22\xc1\x15\xf9\x32\xb8\x14\xad\xd4\x4b\xc5\x8b\x86\xfb\x2e\xd7\x31\xbc\xa0\x76\x0f\xf4\xfa\xcd\x35",28))
printf("strip: 9eefc022c115f932, Pass\n");
else
printf("strip: 9eefc022c115f932, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000063dc))=0x026a1002;
*((unsigned int *)((unsigned long)context_ptr+0x000063dc+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000063dc+4*2))=0x02020064;
*((unsigned int *)((unsigned long)context_ptr+0x000063dc+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x000067a8))=0x0ffc833a;
*((unsigned int *)((unsigned long)context_ptr+0x000067a8+4*1))=0x0577471b;
*((unsigned int *)((unsigned long)context_ptr+0x000067a8+4*2))=0x57809741;
*((unsigned int *)((unsigned long)context_ptr+0x000067a8+4*3))=0x4726219e;
*((unsigned int *)((unsigned long)context_ptr+0x000067a8+4*4))=0xbe506bf3;
*((unsigned int *)((unsigned long)context_ptr+0x000067a8+4*5))=0xd0e827d7;
*((unsigned int *)((unsigned long)context_ptr+0x000067a8+4*6))=0xd67e325e;
*((unsigned int *)((unsigned long)context_ptr+0x000067a8+4*7))=0x9acb2b35;
*((unsigned int *)((unsigned long)context_ptr+0x000067a8+4*8))=0xf64f7eba;
*((unsigned int *)((unsigned long)context_ptr+0x000067a8+4*9))=0x0351aa3d;
*((unsigned int *)((unsigned long)context_ptr+0x000067a8+4*10))=0x83d2b685;
*((unsigned int *)((unsigned long)context_ptr+0x000067a8+4*11))=0x96945302;
*((unsigned int *)((unsigned long)context_ptr+0x000067a8+4*12))=0x2ab6f5ec;
*((unsigned int *)((unsigned long)context_ptr+0x000067a8+4*13))=0x12551fbd;
*((unsigned int *)((unsigned long)context_ptr+0x000067a8+4*14))=0x09b783cf;
*((unsigned int *)((unsigned long)context_ptr+0x000067a8+4*15))=0x287d342d;
*((unsigned int *)((unsigned long)context_ptr+0x000067a8+4*16))=0xf51b8f19;
*((unsigned int *)((unsigned long)context_ptr+0x000067a8+4*17))=0x4cc4fec6;
*((unsigned int *)((unsigned long)context_ptr+0x000067a8+4*18))=0x511f33cf;
*((unsigned int *)((unsigned long)context_ptr+0x000067a8+4*19))=0x11e31eb3;
*((unsigned int *)((unsigned long)context_ptr+0x000067a8+4*20))=0xc383b0c6;
*((unsigned int *)((unsigned long)context_ptr+0x000067a8+4*21))=0x4b26b18c;
*((unsigned int *)((unsigned long)context_ptr+0x000067a8+4*22))=0xbb96a18a;
*((unsigned int *)((unsigned long)context_ptr+0x000067a8+4*23))=0xf3f151b1;
*((unsigned int *)((unsigned long)context_ptr+0x000067a8+4*24))=0x1563754b;
*((unsigned int *)((unsigned long)context_ptr+0x00003948))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003948+4*1))=0x000064c8;
*((unsigned int *)((unsigned long)context_ptr+0x00003948+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003948+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003948+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003948+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000948))=0x04c00064;
*((unsigned int *)((unsigned long)context_ptr+0x00000948+4*1))=0x000067a8;
*((unsigned int *)((unsigned long)context_ptr+0x00000948+4*2))=0x000063dc;
*((unsigned int *)((unsigned long)context_ptr+0x00000948+4*3))=0x02220064;
*((unsigned int *)((unsigned long)context_ptr+0x00000948+4*4))=0x03c22bd9;
*((unsigned int *)((unsigned long)context_ptr+0x00000948+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000204&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000065a0,"\x6b\xc8\x13\xbc\xe6\x05\x9f\x78\x7d\x8b\xf9\xea\xaa\xca\x20\xed\x09\x98\x4c\xbf\xb3\x1c\x14\x6e\x37\x63\xba\x11",28))
printf("strip: 6bc813bce6059f78, Pass\n");
else
printf("strip: 6bc813bce6059f78, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000064e4))=0x026a1002;
*((unsigned int *)((unsigned long)context_ptr+0x000064e4+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000064e4+4*2))=0x02020065;
*((unsigned int *)((unsigned long)context_ptr+0x000064e4+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x00006188))=0x09e6d13c;
*((unsigned int *)((unsigned long)context_ptr+0x00006188+4*1))=0x10aeeaa8;
*((unsigned int *)((unsigned long)context_ptr+0x00006188+4*2))=0xa62710a4;
*((unsigned int *)((unsigned long)context_ptr+0x00006188+4*3))=0xe09408ae;
*((unsigned int *)((unsigned long)context_ptr+0x00006188+4*4))=0xa437a4a1;
*((unsigned int *)((unsigned long)context_ptr+0x00006188+4*5))=0xd13dd526;
*((unsigned int *)((unsigned long)context_ptr+0x00006188+4*6))=0x4d559806;
*((unsigned int *)((unsigned long)context_ptr+0x00006188+4*7))=0x2dfa3e9c;
*((unsigned int *)((unsigned long)context_ptr+0x00006188+4*8))=0xeb4fad8b;
*((unsigned int *)((unsigned long)context_ptr+0x00006188+4*9))=0x8f7037c7;
*((unsigned int *)((unsigned long)context_ptr+0x00006188+4*10))=0x4ebdc506;
*((unsigned int *)((unsigned long)context_ptr+0x00006188+4*11))=0xdd6f6aca;
*((unsigned int *)((unsigned long)context_ptr+0x00006188+4*12))=0x33bac74e;
*((unsigned int *)((unsigned long)context_ptr+0x00006188+4*13))=0x409c284b;
*((unsigned int *)((unsigned long)context_ptr+0x00006188+4*14))=0xc13e33ec;
*((unsigned int *)((unsigned long)context_ptr+0x00006188+4*15))=0xcb006e9b;
*((unsigned int *)((unsigned long)context_ptr+0x00006188+4*16))=0x30518855;
*((unsigned int *)((unsigned long)context_ptr+0x00006188+4*17))=0xd3b77fe4;
*((unsigned int *)((unsigned long)context_ptr+0x00006188+4*18))=0x0c17a467;
*((unsigned int *)((unsigned long)context_ptr+0x00006188+4*19))=0xf6f1fb9a;
*((unsigned int *)((unsigned long)context_ptr+0x00006188+4*20))=0x9db77395;
*((unsigned int *)((unsigned long)context_ptr+0x00006188+4*21))=0x4eabe8dc;
*((unsigned int *)((unsigned long)context_ptr+0x00006188+4*22))=0x14babd7f;
*((unsigned int *)((unsigned long)context_ptr+0x00006188+4*23))=0x6b32350b;
*((unsigned int *)((unsigned long)context_ptr+0x00006188+4*24))=0x214db00c;
*((unsigned int *)((unsigned long)context_ptr+0x00006188+4*25))=0x000000b3;
*((unsigned int *)((unsigned long)context_ptr+0x00003960))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003960+4*1))=0x0000680c;
*((unsigned int *)((unsigned long)context_ptr+0x00003960+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003960+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003960+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003960+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000960))=0x04c00065;
*((unsigned int *)((unsigned long)context_ptr+0x00000960+4*1))=0x00006188;
*((unsigned int *)((unsigned long)context_ptr+0x00000960+4*2))=0x000064e4;
*((unsigned int *)((unsigned long)context_ptr+0x00000960+4*3))=0x02220065;
*((unsigned int *)((unsigned long)context_ptr+0x00000960+4*4))=0x0f2032b3;
*((unsigned int *)((unsigned long)context_ptr+0x00000960+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000020a&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000064f4,"\xb3\x2e\x77\xec\x26\x62\x22\x87\x27\xe7\x51\x54\x37\xaf\x16\xe6\xbd\xc4\x9e\x35\x14\x09\x24\x22\xcb\x49\x57\xcf",28))
printf("strip: b32e77ec26622287, Pass\n");
else
printf("strip: b32e77ec26622287, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000063ec))=0x026a1002;
*((unsigned int *)((unsigned long)context_ptr+0x000063ec+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000063ec+4*2))=0x02020066;
*((unsigned int *)((unsigned long)context_ptr+0x000063ec+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x00006540))=0xa21f2b69;
*((unsigned int *)((unsigned long)context_ptr+0x00006540+4*1))=0x9faff70d;
*((unsigned int *)((unsigned long)context_ptr+0x00006540+4*2))=0x953c964d;
*((unsigned int *)((unsigned long)context_ptr+0x00006540+4*3))=0xc4f6e664;
*((unsigned int *)((unsigned long)context_ptr+0x00006540+4*4))=0x1bfac9d1;
*((unsigned int *)((unsigned long)context_ptr+0x00006540+4*5))=0xdf82e8ca;
*((unsigned int *)((unsigned long)context_ptr+0x00006540+4*6))=0x7bcd07cc;
*((unsigned int *)((unsigned long)context_ptr+0x00006540+4*7))=0x9798559b;
*((unsigned int *)((unsigned long)context_ptr+0x00006540+4*8))=0xa92e8025;
*((unsigned int *)((unsigned long)context_ptr+0x00006540+4*9))=0xf5975b0d;
*((unsigned int *)((unsigned long)context_ptr+0x00006540+4*10))=0x50652719;
*((unsigned int *)((unsigned long)context_ptr+0x00006540+4*11))=0xab21d3b5;
*((unsigned int *)((unsigned long)context_ptr+0x00006540+4*12))=0x4457e9cb;
*((unsigned int *)((unsigned long)context_ptr+0x00006540+4*13))=0xb29066bf;
*((unsigned int *)((unsigned long)context_ptr+0x00006540+4*14))=0xbbeebf4d;
*((unsigned int *)((unsigned long)context_ptr+0x00006540+4*15))=0x91ef7953;
*((unsigned int *)((unsigned long)context_ptr+0x00006540+4*16))=0xe85c801c;
*((unsigned int *)((unsigned long)context_ptr+0x00006540+4*17))=0xed092f8d;
*((unsigned int *)((unsigned long)context_ptr+0x00006540+4*18))=0x5d68a727;
*((unsigned int *)((unsigned long)context_ptr+0x00006540+4*19))=0x492f6eb8;
*((unsigned int *)((unsigned long)context_ptr+0x00006540+4*20))=0x73d19563;
*((unsigned int *)((unsigned long)context_ptr+0x00006540+4*21))=0xcc6156f1;
*((unsigned int *)((unsigned long)context_ptr+0x00006540+4*22))=0xa590ff5e;
*((unsigned int *)((unsigned long)context_ptr+0x00006540+4*23))=0x59b05688;
*((unsigned int *)((unsigned long)context_ptr+0x00006540+4*24))=0xa45a2316;
*((unsigned int *)((unsigned long)context_ptr+0x00006540+4*25))=0x00005746;
*((unsigned int *)((unsigned long)context_ptr+0x00003978))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003978+4*1))=0x000064f4;
*((unsigned int *)((unsigned long)context_ptr+0x00003978+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003978+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003978+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003978+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000978))=0x04c00066;
*((unsigned int *)((unsigned long)context_ptr+0x00000978+4*1))=0x00006540;
*((unsigned int *)((unsigned long)context_ptr+0x00000978+4*2))=0x000063ec;
*((unsigned int *)((unsigned long)context_ptr+0x00000978+4*3))=0x02220066;
*((unsigned int *)((unsigned long)context_ptr+0x00000978+4*4))=0x00a6a9be;
*((unsigned int *)((unsigned long)context_ptr+0x00000978+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000210&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006400,"\x7c\x99\x01\x94\x0b\x67\x4b\xb9\xac\xb8\xd9\xa5\x9a\x30\xdc\xd6\xe9\x8a\x73\xe4\xfe\x23\x0b\xd6\x0f\xf8\x29\x62",28))
printf("strip: 7c9901940b674bb9, Pass\n");
else
printf("strip: 7c9901940b674bb9, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006510))=0x026a1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006510+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006510+4*2))=0x02020067;
*((unsigned int *)((unsigned long)context_ptr+0x00006510+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x0000666c))=0xc6600ec8;
*((unsigned int *)((unsigned long)context_ptr+0x0000666c+4*1))=0xc256d510;
*((unsigned int *)((unsigned long)context_ptr+0x0000666c+4*2))=0xe567adfd;
*((unsigned int *)((unsigned long)context_ptr+0x0000666c+4*3))=0x56783947;
*((unsigned int *)((unsigned long)context_ptr+0x0000666c+4*4))=0x93f05fe7;
*((unsigned int *)((unsigned long)context_ptr+0x0000666c+4*5))=0xa0196a0f;
*((unsigned int *)((unsigned long)context_ptr+0x0000666c+4*6))=0x28999185;
*((unsigned int *)((unsigned long)context_ptr+0x0000666c+4*7))=0xe3138470;
*((unsigned int *)((unsigned long)context_ptr+0x0000666c+4*8))=0x88ffe858;
*((unsigned int *)((unsigned long)context_ptr+0x0000666c+4*9))=0xc47a53ab;
*((unsigned int *)((unsigned long)context_ptr+0x0000666c+4*10))=0xa45ca6ef;
*((unsigned int *)((unsigned long)context_ptr+0x0000666c+4*11))=0xaf887086;
*((unsigned int *)((unsigned long)context_ptr+0x0000666c+4*12))=0x3a816526;
*((unsigned int *)((unsigned long)context_ptr+0x0000666c+4*13))=0x9e918587;
*((unsigned int *)((unsigned long)context_ptr+0x0000666c+4*14))=0x7d36bd50;
*((unsigned int *)((unsigned long)context_ptr+0x0000666c+4*15))=0xf74a42e3;
*((unsigned int *)((unsigned long)context_ptr+0x0000666c+4*16))=0x85550fd9;
*((unsigned int *)((unsigned long)context_ptr+0x0000666c+4*17))=0xa961ae3d;
*((unsigned int *)((unsigned long)context_ptr+0x0000666c+4*18))=0x59e90d91;
*((unsigned int *)((unsigned long)context_ptr+0x0000666c+4*19))=0x08ebea00;
*((unsigned int *)((unsigned long)context_ptr+0x0000666c+4*20))=0x34073ef3;
*((unsigned int *)((unsigned long)context_ptr+0x0000666c+4*21))=0xf097511e;
*((unsigned int *)((unsigned long)context_ptr+0x0000666c+4*22))=0x68b70563;
*((unsigned int *)((unsigned long)context_ptr+0x0000666c+4*23))=0x35def350;
*((unsigned int *)((unsigned long)context_ptr+0x0000666c+4*24))=0x9ccf1f36;
*((unsigned int *)((unsigned long)context_ptr+0x0000666c+4*25))=0x004cc6ac;
*((unsigned int *)((unsigned long)context_ptr+0x00003990))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003990+4*1))=0x000063fc;
*((unsigned int *)((unsigned long)context_ptr+0x00003990+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003990+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003990+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003990+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000990))=0x04c00067;
*((unsigned int *)((unsigned long)context_ptr+0x00000990+4*1))=0x0000666c;
*((unsigned int *)((unsigned long)context_ptr+0x00000990+4*2))=0x00006510;
*((unsigned int *)((unsigned long)context_ptr+0x00000990+4*3))=0x02220067;
*((unsigned int *)((unsigned long)context_ptr+0x00000990+4*4))=0x05299e13;
*((unsigned int *)((unsigned long)context_ptr+0x00000990+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000216&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006710,"\xb6\xc1\x49\xe7\xde\x08\xb2\x90\x11\x13\x12\xc5\x1c\xb3\x18\x71\xa9\xa3\xf2\x4e\x9d\x39\x87\xa7\xb1\xf1\xea\x0a",28))
printf("strip: b6c149e7de08b290, Pass\n");
else
printf("strip: b6c149e7de08b290, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006418))=0x026a1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006418+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006418+4*2))=0x02020068;
*((unsigned int *)((unsigned long)context_ptr+0x00006418+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x000065a8))=0xf1dac404;
*((unsigned int *)((unsigned long)context_ptr+0x000065a8+4*1))=0x4a857fcc;
*((unsigned int *)((unsigned long)context_ptr+0x000065a8+4*2))=0xc2ebff0c;
*((unsigned int *)((unsigned long)context_ptr+0x000065a8+4*3))=0xf3bb5c45;
*((unsigned int *)((unsigned long)context_ptr+0x000065a8+4*4))=0xb17dd974;
*((unsigned int *)((unsigned long)context_ptr+0x000065a8+4*5))=0xc4afbde7;
*((unsigned int *)((unsigned long)context_ptr+0x000065a8+4*6))=0x809414d9;
*((unsigned int *)((unsigned long)context_ptr+0x000065a8+4*7))=0x98522da7;
*((unsigned int *)((unsigned long)context_ptr+0x000065a8+4*8))=0x66153cc5;
*((unsigned int *)((unsigned long)context_ptr+0x000065a8+4*9))=0x03486f86;
*((unsigned int *)((unsigned long)context_ptr+0x000065a8+4*10))=0xb00bb6b0;
*((unsigned int *)((unsigned long)context_ptr+0x000065a8+4*11))=0xbfcc1a3d;
*((unsigned int *)((unsigned long)context_ptr+0x000065a8+4*12))=0x2563798b;
*((unsigned int *)((unsigned long)context_ptr+0x000065a8+4*13))=0x1f15154c;
*((unsigned int *)((unsigned long)context_ptr+0x000065a8+4*14))=0x8fec192e;
*((unsigned int *)((unsigned long)context_ptr+0x000065a8+4*15))=0x3b82fe58;
*((unsigned int *)((unsigned long)context_ptr+0x000065a8+4*16))=0xd1e0cc87;
*((unsigned int *)((unsigned long)context_ptr+0x000065a8+4*17))=0xbcb72757;
*((unsigned int *)((unsigned long)context_ptr+0x000065a8+4*18))=0x7fa0aa98;
*((unsigned int *)((unsigned long)context_ptr+0x000065a8+4*19))=0x3452fa28;
*((unsigned int *)((unsigned long)context_ptr+0x000065a8+4*20))=0x551512ac;
*((unsigned int *)((unsigned long)context_ptr+0x000065a8+4*21))=0x3f3d63f4;
*((unsigned int *)((unsigned long)context_ptr+0x000065a8+4*22))=0x019d0e6f;
*((unsigned int *)((unsigned long)context_ptr+0x000065a8+4*23))=0x6cff9417;
*((unsigned int *)((unsigned long)context_ptr+0x000065a8+4*24))=0xf3acf373;
*((unsigned int *)((unsigned long)context_ptr+0x000065a8+4*25))=0x47906f27;
*((unsigned int *)((unsigned long)context_ptr+0x000039a8))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x000039a8+4*1))=0x00006828;
*((unsigned int *)((unsigned long)context_ptr+0x000039a8+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000039a8+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000039a8+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000039a8+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x000009a8))=0x04c00068;
*((unsigned int *)((unsigned long)context_ptr+0x000009a8+4*1))=0x000065a8;
*((unsigned int *)((unsigned long)context_ptr+0x000009a8+4*2))=0x00006418;
*((unsigned int *)((unsigned long)context_ptr+0x000009a8+4*3))=0x02220068;
*((unsigned int *)((unsigned long)context_ptr+0x000009a8+4*4))=0x07abb826;
*((unsigned int *)((unsigned long)context_ptr+0x000009a8+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000021c&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006618,"\x5c\xb3\x08\x0f\x45\x26\xca\x57\x48\x5d\x7c\xa6\x1d\xc4\x3b\xd1\x09\xaa\xdd\xa8\xf6\xf0\x3f\x86\x6b\x7f\xe9\x99",28))
printf("strip: 5cb3080f4526ca57, Pass\n");
else
printf("strip: 5cb3080f4526ca57, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006520))=0x026a1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006520+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006520+4*2))=0x02020069;
*((unsigned int *)((unsigned long)context_ptr+0x00006520+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x000061f0))=0x118028b6;
*((unsigned int *)((unsigned long)context_ptr+0x000061f0+4*1))=0x15d91689;
*((unsigned int *)((unsigned long)context_ptr+0x000061f0+4*2))=0x0f8821f7;
*((unsigned int *)((unsigned long)context_ptr+0x000061f0+4*3))=0x3c28d744;
*((unsigned int *)((unsigned long)context_ptr+0x000061f0+4*4))=0x223fd1ec;
*((unsigned int *)((unsigned long)context_ptr+0x000061f0+4*5))=0xbc5458ea;
*((unsigned int *)((unsigned long)context_ptr+0x000061f0+4*6))=0xe63cc87c;
*((unsigned int *)((unsigned long)context_ptr+0x000061f0+4*7))=0x03352b82;
*((unsigned int *)((unsigned long)context_ptr+0x000061f0+4*8))=0xe20fd5aa;
*((unsigned int *)((unsigned long)context_ptr+0x000061f0+4*9))=0xbb30bec6;
*((unsigned int *)((unsigned long)context_ptr+0x000061f0+4*10))=0xd5e44f5e;
*((unsigned int *)((unsigned long)context_ptr+0x000061f0+4*11))=0x3b83e703;
*((unsigned int *)((unsigned long)context_ptr+0x000061f0+4*12))=0x00e3c966;
*((unsigned int *)((unsigned long)context_ptr+0x000061f0+4*13))=0x8a2be094;
*((unsigned int *)((unsigned long)context_ptr+0x000061f0+4*14))=0x13bbdc2a;
*((unsigned int *)((unsigned long)context_ptr+0x000061f0+4*15))=0xd3cea7f4;
*((unsigned int *)((unsigned long)context_ptr+0x000061f0+4*16))=0x39e12861;
*((unsigned int *)((unsigned long)context_ptr+0x000061f0+4*17))=0x5feb27e5;
*((unsigned int *)((unsigned long)context_ptr+0x000061f0+4*18))=0x0a0dbe79;
*((unsigned int *)((unsigned long)context_ptr+0x000061f0+4*19))=0x05aa128f;
*((unsigned int *)((unsigned long)context_ptr+0x000061f0+4*20))=0x98b86e1c;
*((unsigned int *)((unsigned long)context_ptr+0x000061f0+4*21))=0x2ab5d46b;
*((unsigned int *)((unsigned long)context_ptr+0x000061f0+4*22))=0xe6751116;
*((unsigned int *)((unsigned long)context_ptr+0x000061f0+4*23))=0x0c5f65d9;
*((unsigned int *)((unsigned long)context_ptr+0x000061f0+4*24))=0xcb3be340;
*((unsigned int *)((unsigned long)context_ptr+0x000061f0+4*25))=0x0df89183;
*((unsigned int *)((unsigned long)context_ptr+0x000061f0+4*26))=0x00000005;
*((unsigned int *)((unsigned long)context_ptr+0x000039c0))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x000039c0+4*1))=0x00006610;
*((unsigned int *)((unsigned long)context_ptr+0x000039c0+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000039c0+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000039c0+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000039c0+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x000009c0))=0x04c00069;
*((unsigned int *)((unsigned long)context_ptr+0x000009c0+4*1))=0x000061f0;
*((unsigned int *)((unsigned long)context_ptr+0x000009c0+4*2))=0x00006520;
*((unsigned int *)((unsigned long)context_ptr+0x000009c0+4*3))=0x02220069;
*((unsigned int *)((unsigned long)context_ptr+0x000009c0+4*4))=0x0ffbff0d;
*((unsigned int *)((unsigned long)context_ptr+0x000009c0+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000222&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x0000672c,"\xf7\xff\x62\x0e\x7b\x72\xe6\xc8\xa8\x25\x51\xe3\x63\xf5\x73\xa0\x84\x77\xbf\xd1\x65\x6c\xca\xc8\x68\x9e\xe3\x5d",28))
printf("strip: f7ff620e7b72e6c8, Pass\n");
else
printf("strip: f7ff620e7b72e6c8, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006058))=0x026a1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*2))=0x0202006a;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x000066d4))=0x1b400a84;
*((unsigned int *)((unsigned long)context_ptr+0x000066d4+4*1))=0xa5d958f6;
*((unsigned int *)((unsigned long)context_ptr+0x000066d4+4*2))=0x39df63e7;
*((unsigned int *)((unsigned long)context_ptr+0x000066d4+4*3))=0x1806fb9f;
*((unsigned int *)((unsigned long)context_ptr+0x000066d4+4*4))=0x8fec395e;
*((unsigned int *)((unsigned long)context_ptr+0x000066d4+4*5))=0xa6132433;
*((unsigned int *)((unsigned long)context_ptr+0x000066d4+4*6))=0x6ac70adc;
*((unsigned int *)((unsigned long)context_ptr+0x000066d4+4*7))=0xbacb2f08;
*((unsigned int *)((unsigned long)context_ptr+0x000066d4+4*8))=0x52bfb066;
*((unsigned int *)((unsigned long)context_ptr+0x000066d4+4*9))=0xb9d9f37f;
*((unsigned int *)((unsigned long)context_ptr+0x000066d4+4*10))=0x31c47899;
*((unsigned int *)((unsigned long)context_ptr+0x000066d4+4*11))=0x0f06b14a;
*((unsigned int *)((unsigned long)context_ptr+0x000066d4+4*12))=0xabb63cc9;
*((unsigned int *)((unsigned long)context_ptr+0x000066d4+4*13))=0x01c3dc01;
*((unsigned int *)((unsigned long)context_ptr+0x000066d4+4*14))=0x73e5dc05;
*((unsigned int *)((unsigned long)context_ptr+0x000066d4+4*15))=0xb06f2c27;
*((unsigned int *)((unsigned long)context_ptr+0x000066d4+4*16))=0xc310c08e;
*((unsigned int *)((unsigned long)context_ptr+0x000066d4+4*17))=0x47d2ce45;
*((unsigned int *)((unsigned long)context_ptr+0x000066d4+4*18))=0xc9f501d3;
*((unsigned int *)((unsigned long)context_ptr+0x000066d4+4*19))=0x65c6d483;
*((unsigned int *)((unsigned long)context_ptr+0x000066d4+4*20))=0xd922a088;
*((unsigned int *)((unsigned long)context_ptr+0x000066d4+4*21))=0xfced0d0e;
*((unsigned int *)((unsigned long)context_ptr+0x000066d4+4*22))=0xff01479f;
*((unsigned int *)((unsigned long)context_ptr+0x000066d4+4*23))=0x2284a32e;
*((unsigned int *)((unsigned long)context_ptr+0x000066d4+4*24))=0xbf854af4;
*((unsigned int *)((unsigned long)context_ptr+0x000066d4+4*25))=0x8b7acaf0;
*((unsigned int *)((unsigned long)context_ptr+0x000066d4+4*26))=0x00007a74;
*((unsigned int *)((unsigned long)context_ptr+0x000039d8))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x000039d8+4*1))=0x0000625c;
*((unsigned int *)((unsigned long)context_ptr+0x000039d8+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000039d8+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000039d8+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000039d8+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x000009d8))=0x04c0006a;
*((unsigned int *)((unsigned long)context_ptr+0x000009d8+4*1))=0x000066d4;
*((unsigned int *)((unsigned long)context_ptr+0x000009d8+4*2))=0x00006058;
*((unsigned int *)((unsigned long)context_ptr+0x000009d8+4*3))=0x0222006a;
*((unsigned int *)((unsigned long)context_ptr+0x000009d8+4*4))=0x04254b31;
*((unsigned int *)((unsigned long)context_ptr+0x000009d8+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000228&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006078,"\xc9\x40\xf7\x62\x8f\xda\xe8\xed\xa5\xe8\x61\x79\x41\x60\x23\xf9\x8f\x9b\x64\x49\xd7\x0a\x9d\x87\xda\x55\x98\x8e",28))
printf("strip: c940f7628fdae8ed, Pass\n");
else
printf("strip: c940f7628fdae8ed, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006048))=0x026a1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006048+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006048+4*2))=0x0202006b;
*((unsigned int *)((unsigned long)context_ptr+0x00006048+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x00006278))=0x1b1882f9;
*((unsigned int *)((unsigned long)context_ptr+0x00006278+4*1))=0x25b89624;
*((unsigned int *)((unsigned long)context_ptr+0x00006278+4*2))=0x993ca260;
*((unsigned int *)((unsigned long)context_ptr+0x00006278+4*3))=0x8c94a455;
*((unsigned int *)((unsigned long)context_ptr+0x00006278+4*4))=0x2859dc1e;
*((unsigned int *)((unsigned long)context_ptr+0x00006278+4*5))=0x7337d8c2;
*((unsigned int *)((unsigned long)context_ptr+0x00006278+4*6))=0xa7655795;
*((unsigned int *)((unsigned long)context_ptr+0x00006278+4*7))=0x05e0a0ef;
*((unsigned int *)((unsigned long)context_ptr+0x00006278+4*8))=0x72de848a;
*((unsigned int *)((unsigned long)context_ptr+0x00006278+4*9))=0x5e7abdc0;
*((unsigned int *)((unsigned long)context_ptr+0x00006278+4*10))=0xe0816722;
*((unsigned int *)((unsigned long)context_ptr+0x00006278+4*11))=0x2f1049bd;
*((unsigned int *)((unsigned long)context_ptr+0x00006278+4*12))=0xc7d129c1;
*((unsigned int *)((unsigned long)context_ptr+0x00006278+4*13))=0x8274542d;
*((unsigned int *)((unsigned long)context_ptr+0x00006278+4*14))=0x1b1e16c4;
*((unsigned int *)((unsigned long)context_ptr+0x00006278+4*15))=0xcf1b67b4;
*((unsigned int *)((unsigned long)context_ptr+0x00006278+4*16))=0x35d1d21f;
*((unsigned int *)((unsigned long)context_ptr+0x00006278+4*17))=0xca525d9b;
*((unsigned int *)((unsigned long)context_ptr+0x00006278+4*18))=0x5e91474c;
*((unsigned int *)((unsigned long)context_ptr+0x00006278+4*19))=0xedaebd92;
*((unsigned int *)((unsigned long)context_ptr+0x00006278+4*20))=0xe8f3810c;
*((unsigned int *)((unsigned long)context_ptr+0x00006278+4*21))=0x8c542f83;
*((unsigned int *)((unsigned long)context_ptr+0x00006278+4*22))=0xd4d251bc;
*((unsigned int *)((unsigned long)context_ptr+0x00006278+4*23))=0xf58aa1f8;
*((unsigned int *)((unsigned long)context_ptr+0x00006278+4*24))=0xf96528e3;
*((unsigned int *)((unsigned long)context_ptr+0x00006278+4*25))=0xb0884118;
*((unsigned int *)((unsigned long)context_ptr+0x00006278+4*26))=0x00e55685;
*((unsigned int *)((unsigned long)context_ptr+0x000039f0))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x000039f0+4*1))=0x00006078;
*((unsigned int *)((unsigned long)context_ptr+0x000039f0+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000039f0+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000039f0+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x000039f0+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x000009f0))=0x04c0006b;
*((unsigned int *)((unsigned long)context_ptr+0x000009f0+4*1))=0x00006278;
*((unsigned int *)((unsigned long)context_ptr+0x000009f0+4*2))=0x00006048;
*((unsigned int *)((unsigned long)context_ptr+0x000009f0+4*3))=0x0222006b;
*((unsigned int *)((unsigned long)context_ptr+0x000009f0+4*4))=0x00cdb399;
*((unsigned int *)((unsigned long)context_ptr+0x000009f0+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000022e&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006308,"\x12\x54\xc3\xd8\xa5\x4e\x5c\xb0\x81\xec\xa7\xcf\xea\xf3\xee\x7b\x01\x89\x22\x38\xcb\x76\xed\x99\xa5\x6f\x5a\x9d",28))
printf("strip: 1254c3d8a54e5cb0, Pass\n");
else
printf("strip: 1254c3d8a54e5cb0, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006068))=0x026a1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006068+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006068+4*2))=0x0202006c;
*((unsigned int *)((unsigned long)context_ptr+0x00006068+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x00006844))=0x176b9f0c;
*((unsigned int *)((unsigned long)context_ptr+0x00006844+4*1))=0xcaecf7e6;
*((unsigned int *)((unsigned long)context_ptr+0x00006844+4*2))=0x0e6d0441;
*((unsigned int *)((unsigned long)context_ptr+0x00006844+4*3))=0xfbe2799a;
*((unsigned int *)((unsigned long)context_ptr+0x00006844+4*4))=0xac176e20;
*((unsigned int *)((unsigned long)context_ptr+0x00006844+4*5))=0xdc26f88c;
*((unsigned int *)((unsigned long)context_ptr+0x00006844+4*6))=0x71c65d7b;
*((unsigned int *)((unsigned long)context_ptr+0x00006844+4*7))=0x76f7f69b;
*((unsigned int *)((unsigned long)context_ptr+0x00006844+4*8))=0x3b946332;
*((unsigned int *)((unsigned long)context_ptr+0x00006844+4*9))=0xee461c0a;
*((unsigned int *)((unsigned long)context_ptr+0x00006844+4*10))=0x7ba1fbfe;
*((unsigned int *)((unsigned long)context_ptr+0x00006844+4*11))=0x4c8f9bce;
*((unsigned int *)((unsigned long)context_ptr+0x00006844+4*12))=0xc8fefcf4;
*((unsigned int *)((unsigned long)context_ptr+0x00006844+4*13))=0xbe668afd;
*((unsigned int *)((unsigned long)context_ptr+0x00006844+4*14))=0x86bb680a;
*((unsigned int *)((unsigned long)context_ptr+0x00006844+4*15))=0x1fdf8107;
*((unsigned int *)((unsigned long)context_ptr+0x00006844+4*16))=0xc5995c3a;
*((unsigned int *)((unsigned long)context_ptr+0x00006844+4*17))=0xb5011898;
*((unsigned int *)((unsigned long)context_ptr+0x00006844+4*18))=0x2b846429;
*((unsigned int *)((unsigned long)context_ptr+0x00006844+4*19))=0x14778fb3;
*((unsigned int *)((unsigned long)context_ptr+0x00006844+4*20))=0x00e07d7a;
*((unsigned int *)((unsigned long)context_ptr+0x00006844+4*21))=0x232040bc;
*((unsigned int *)((unsigned long)context_ptr+0x00006844+4*22))=0x4977132c;
*((unsigned int *)((unsigned long)context_ptr+0x00006844+4*23))=0x91baa04f;
*((unsigned int *)((unsigned long)context_ptr+0x00006844+4*24))=0xfed21933;
*((unsigned int *)((unsigned long)context_ptr+0x00006844+4*25))=0x1510973c;
*((unsigned int *)((unsigned long)context_ptr+0x00006844+4*26))=0x62bcbe1a;
*((unsigned int *)((unsigned long)context_ptr+0x00003a08))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003a08+4*1))=0x000062e4;
*((unsigned int *)((unsigned long)context_ptr+0x00003a08+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003a08+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003a08+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003a08+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000a08))=0x04c0006c;
*((unsigned int *)((unsigned long)context_ptr+0x00000a08+4*1))=0x00006844;
*((unsigned int *)((unsigned long)context_ptr+0x00000a08+4*2))=0x00006068;
*((unsigned int *)((unsigned long)context_ptr+0x00000a08+4*3))=0x0222006c;
*((unsigned int *)((unsigned long)context_ptr+0x00000a08+4*4))=0x0c535820;
*((unsigned int *)((unsigned long)context_ptr+0x00000a08+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000234&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006634,"\xe2\xa3\x2c\xd9\x57\x79\xb4\x89\xde\xc2\xd9\xbe\xc7\x7b\xde\x3c\xd3\x57\xb1\x3b\x58\xf9\xe3\xb7\xd1\xd1\x1a\xe7",28))
printf("strip: e2a32cd95779b489, Pass\n");
else
printf("strip: e2a32cd95779b489, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006094))=0x026a1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006094+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006094+4*2))=0x0202006d;
*((unsigned int *)((unsigned long)context_ptr+0x00006094+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x00006968))=0xc890bfde;
*((unsigned int *)((unsigned long)context_ptr+0x00006968+4*1))=0xcb0f6dec;
*((unsigned int *)((unsigned long)context_ptr+0x00006968+4*2))=0xe6dcad3a;
*((unsigned int *)((unsigned long)context_ptr+0x00006968+4*3))=0x5db2be0c;
*((unsigned int *)((unsigned long)context_ptr+0x00006968+4*4))=0xe1332b9a;
*((unsigned int *)((unsigned long)context_ptr+0x00006968+4*5))=0xb9afbc42;
*((unsigned int *)((unsigned long)context_ptr+0x00006968+4*6))=0x980e8a47;
*((unsigned int *)((unsigned long)context_ptr+0x00006968+4*7))=0x32b6f31d;
*((unsigned int *)((unsigned long)context_ptr+0x00006968+4*8))=0x9a10747f;
*((unsigned int *)((unsigned long)context_ptr+0x00006968+4*9))=0x22155732;
*((unsigned int *)((unsigned long)context_ptr+0x00006968+4*10))=0xaf0375a7;
*((unsigned int *)((unsigned long)context_ptr+0x00006968+4*11))=0x80c037bd;
*((unsigned int *)((unsigned long)context_ptr+0x00006968+4*12))=0x2eb81a37;
*((unsigned int *)((unsigned long)context_ptr+0x00006968+4*13))=0xe09bdeb3;
*((unsigned int *)((unsigned long)context_ptr+0x00006968+4*14))=0xfd9cd956;
*((unsigned int *)((unsigned long)context_ptr+0x00006968+4*15))=0xb36ba076;
*((unsigned int *)((unsigned long)context_ptr+0x00006968+4*16))=0x05d91b31;
*((unsigned int *)((unsigned long)context_ptr+0x00006968+4*17))=0x2a92eb59;
*((unsigned int *)((unsigned long)context_ptr+0x00006968+4*18))=0x9d73e272;
*((unsigned int *)((unsigned long)context_ptr+0x00006968+4*19))=0x47b1d068;
*((unsigned int *)((unsigned long)context_ptr+0x00006968+4*20))=0x9254934b;
*((unsigned int *)((unsigned long)context_ptr+0x00006968+4*21))=0x82dff9c3;
*((unsigned int *)((unsigned long)context_ptr+0x00006968+4*22))=0x5a6e3058;
*((unsigned int *)((unsigned long)context_ptr+0x00006968+4*23))=0xe0d2b147;
*((unsigned int *)((unsigned long)context_ptr+0x00006968+4*24))=0x7334e5f9;
*((unsigned int *)((unsigned long)context_ptr+0x00006968+4*25))=0x349587fa;
*((unsigned int *)((unsigned long)context_ptr+0x00006968+4*26))=0x4f0e5093;
*((unsigned int *)((unsigned long)context_ptr+0x00006968+4*27))=0x000000f4;
*((unsigned int *)((unsigned long)context_ptr+0x00003a20))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003a20+4*1))=0x00006300;
*((unsigned int *)((unsigned long)context_ptr+0x00003a20+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003a20+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003a20+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003a20+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000a20))=0x04c0006d;
*((unsigned int *)((unsigned long)context_ptr+0x00000a20+4*1))=0x00006968;
*((unsigned int *)((unsigned long)context_ptr+0x00000a20+4*2))=0x00006094;
*((unsigned int *)((unsigned long)context_ptr+0x00000a20+4*3))=0x0222006d;
*((unsigned int *)((unsigned long)context_ptr+0x00000a20+4*4))=0x0800088a;
*((unsigned int *)((unsigned long)context_ptr+0x00000a20+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000023a&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006650,"\xf9\xb2\x09\x6c\x3d\xe8\x95\x60\x4e\x5e\xa1\x82\x75\xb0\x36\x9e\x6c\x85\x51\xb5\x78\x0a\xcd\xac\xc0\x74\x19\x5d",28))
printf("strip: f9b2096c3de89560, Pass\n");
else
printf("strip: f9b2096c3de89560, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x0000662c))=0x026a1002;
*((unsigned int *)((unsigned long)context_ptr+0x0000662c+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x0000662c+4*2))=0x0202006e;
*((unsigned int *)((unsigned long)context_ptr+0x0000662c+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x00006428))=0x1e84b054;
*((unsigned int *)((unsigned long)context_ptr+0x00006428+4*1))=0x1f31b45b;
*((unsigned int *)((unsigned long)context_ptr+0x00006428+4*2))=0x4105aa35;
*((unsigned int *)((unsigned long)context_ptr+0x00006428+4*3))=0x6ef4b2db;
*((unsigned int *)((unsigned long)context_ptr+0x00006428+4*4))=0xe4cebf1f;
*((unsigned int *)((unsigned long)context_ptr+0x00006428+4*5))=0x770019af;
*((unsigned int *)((unsigned long)context_ptr+0x00006428+4*6))=0xee1f29c8;
*((unsigned int *)((unsigned long)context_ptr+0x00006428+4*7))=0xe7716dbd;
*((unsigned int *)((unsigned long)context_ptr+0x00006428+4*8))=0x9b8f08be;
*((unsigned int *)((unsigned long)context_ptr+0x00006428+4*9))=0x9093b34d;
*((unsigned int *)((unsigned long)context_ptr+0x00006428+4*10))=0x054e62ae;
*((unsigned int *)((unsigned long)context_ptr+0x00006428+4*11))=0x42cddbb8;
*((unsigned int *)((unsigned long)context_ptr+0x00006428+4*12))=0xa54ceabd;
*((unsigned int *)((unsigned long)context_ptr+0x00006428+4*13))=0xc24728bf;
*((unsigned int *)((unsigned long)context_ptr+0x00006428+4*14))=0x290c2ea2;
*((unsigned int *)((unsigned long)context_ptr+0x00006428+4*15))=0xd052be32;
*((unsigned int *)((unsigned long)context_ptr+0x00006428+4*16))=0x03dd4042;
*((unsigned int *)((unsigned long)context_ptr+0x00006428+4*17))=0xac7cea4b;
*((unsigned int *)((unsigned long)context_ptr+0x00006428+4*18))=0xa3baf79a;
*((unsigned int *)((unsigned long)context_ptr+0x00006428+4*19))=0x4d9a034d;
*((unsigned int *)((unsigned long)context_ptr+0x00006428+4*20))=0xc1c0d6c2;
*((unsigned int *)((unsigned long)context_ptr+0x00006428+4*21))=0xeb77a6f3;
*((unsigned int *)((unsigned long)context_ptr+0x00006428+4*22))=0x25234784;
*((unsigned int *)((unsigned long)context_ptr+0x00006428+4*23))=0x962b2d19;
*((unsigned int *)((unsigned long)context_ptr+0x00006428+4*24))=0xa043f804;
*((unsigned int *)((unsigned long)context_ptr+0x00006428+4*25))=0xa7ee83f0;
*((unsigned int *)((unsigned long)context_ptr+0x00006428+4*26))=0x4133fcad;
*((unsigned int *)((unsigned long)context_ptr+0x00006428+4*27))=0x00009192;
*((unsigned int *)((unsigned long)context_ptr+0x00003a38))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003a38+4*1))=0x0000663c;
*((unsigned int *)((unsigned long)context_ptr+0x00003a38+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003a38+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003a38+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003a38+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000a38))=0x04c0006e;
*((unsigned int *)((unsigned long)context_ptr+0x00000a38+4*1))=0x00006428;
*((unsigned int *)((unsigned long)context_ptr+0x00000a38+4*2))=0x0000662c;
*((unsigned int *)((unsigned long)context_ptr+0x00000a38+4*3))=0x0222006e;
*((unsigned int *)((unsigned long)context_ptr+0x00000a38+4*4))=0x05dece5a;
*((unsigned int *)((unsigned long)context_ptr+0x00000a38+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000240&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006384,"\x7c\x5e\xdd\x1d\xb1\xe0\x43\xa7\xf3\x21\x50\x83\x1d\xb9\x06\x84\xf2\x27\x1b\xd7\x50\x01\x12\x4a\x27\xe8\x87\x76",28))
printf("strip: 7c5edd1db1e043a7, Pass\n");
else
printf("strip: 7c5edd1db1e043a7, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006498))=0x026a1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006498+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006498+4*2))=0x0202006f;
*((unsigned int *)((unsigned long)context_ptr+0x00006498+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x0000631c))=0x9d9abc00;
*((unsigned int *)((unsigned long)context_ptr+0x0000631c+4*1))=0xffdfccaf;
*((unsigned int *)((unsigned long)context_ptr+0x0000631c+4*2))=0x37238fa9;
*((unsigned int *)((unsigned long)context_ptr+0x0000631c+4*3))=0xead897fb;
*((unsigned int *)((unsigned long)context_ptr+0x0000631c+4*4))=0xad51787c;
*((unsigned int *)((unsigned long)context_ptr+0x0000631c+4*5))=0xa41cd3f1;
*((unsigned int *)((unsigned long)context_ptr+0x0000631c+4*6))=0xfa197161;
*((unsigned int *)((unsigned long)context_ptr+0x0000631c+4*7))=0xd4c56373;
*((unsigned int *)((unsigned long)context_ptr+0x0000631c+4*8))=0xa43f6aa8;
*((unsigned int *)((unsigned long)context_ptr+0x0000631c+4*9))=0xe11dae58;
*((unsigned int *)((unsigned long)context_ptr+0x0000631c+4*10))=0x5153bbe1;
*((unsigned int *)((unsigned long)context_ptr+0x0000631c+4*11))=0x71b04b96;
*((unsigned int *)((unsigned long)context_ptr+0x0000631c+4*12))=0x7edb0348;
*((unsigned int *)((unsigned long)context_ptr+0x0000631c+4*13))=0x8ac07902;
*((unsigned int *)((unsigned long)context_ptr+0x0000631c+4*14))=0xa56e6462;
*((unsigned int *)((unsigned long)context_ptr+0x0000631c+4*15))=0xee1ecefa;
*((unsigned int *)((unsigned long)context_ptr+0x0000631c+4*16))=0x95f9654b;
*((unsigned int *)((unsigned long)context_ptr+0x0000631c+4*17))=0x2eeae00b;
*((unsigned int *)((unsigned long)context_ptr+0x0000631c+4*18))=0x4cfee03f;
*((unsigned int *)((unsigned long)context_ptr+0x0000631c+4*19))=0xbcfce445;
*((unsigned int *)((unsigned long)context_ptr+0x0000631c+4*20))=0xc3f85b25;
*((unsigned int *)((unsigned long)context_ptr+0x0000631c+4*21))=0x3e6e8251;
*((unsigned int *)((unsigned long)context_ptr+0x0000631c+4*22))=0x0e6506a3;
*((unsigned int *)((unsigned long)context_ptr+0x0000631c+4*23))=0xd0f8d3f1;
*((unsigned int *)((unsigned long)context_ptr+0x0000631c+4*24))=0x187272a0;
*((unsigned int *)((unsigned long)context_ptr+0x0000631c+4*25))=0xf85f4226;
*((unsigned int *)((unsigned long)context_ptr+0x0000631c+4*26))=0x4f612737;
*((unsigned int *)((unsigned long)context_ptr+0x0000631c+4*27))=0x0018636b;
*((unsigned int *)((unsigned long)context_ptr+0x00003a50))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003a50+4*1))=0x000068b0;
*((unsigned int *)((unsigned long)context_ptr+0x00003a50+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003a50+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003a50+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003a50+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000a50))=0x04c0006f;
*((unsigned int *)((unsigned long)context_ptr+0x00000a50+4*1))=0x0000631c;
*((unsigned int *)((unsigned long)context_ptr+0x00000a50+4*2))=0x00006498;
*((unsigned int *)((unsigned long)context_ptr+0x00000a50+4*3))=0x0222006f;
*((unsigned int *)((unsigned long)context_ptr+0x00000a50+4*4))=0x017ebc82;
*((unsigned int *)((unsigned long)context_ptr+0x00000a50+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000246&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006108,"\x7f\xe9\x7a\x7e\xe8\x87\xf5\x19\x0d\x3b\xc9\x22\x17\x21\x18\xc6\x89\xd1\x86\x68\xec\xdd\x31\xaa\xcb\xa1\xc7\xf1",28))
printf("strip: 7fe97a7ee887f519, Pass\n");
else
printf("strip: 7fe97a7ee887f519, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006658))=0x026a1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006658+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006658+4*2))=0x02020070;
*((unsigned int *)((unsigned long)context_ptr+0x00006658+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x000060a4))=0xf32ad774;
*((unsigned int *)((unsigned long)context_ptr+0x000060a4+4*1))=0xa9fe2bb9;
*((unsigned int *)((unsigned long)context_ptr+0x000060a4+4*2))=0x6306a335;
*((unsigned int *)((unsigned long)context_ptr+0x000060a4+4*3))=0x825de32c;
*((unsigned int *)((unsigned long)context_ptr+0x000060a4+4*4))=0x8930c2f0;
*((unsigned int *)((unsigned long)context_ptr+0x000060a4+4*5))=0xeaee9f69;
*((unsigned int *)((unsigned long)context_ptr+0x000060a4+4*6))=0xab9403b2;
*((unsigned int *)((unsigned long)context_ptr+0x000060a4+4*7))=0x5a6100ca;
*((unsigned int *)((unsigned long)context_ptr+0x000060a4+4*8))=0xa22240a4;
*((unsigned int *)((unsigned long)context_ptr+0x000060a4+4*9))=0xfa11425e;
*((unsigned int *)((unsigned long)context_ptr+0x000060a4+4*10))=0x054c40a4;
*((unsigned int *)((unsigned long)context_ptr+0x000060a4+4*11))=0xe32861c9;
*((unsigned int *)((unsigned long)context_ptr+0x000060a4+4*12))=0xc3c81c33;
*((unsigned int *)((unsigned long)context_ptr+0x000060a4+4*13))=0x1ab43009;
*((unsigned int *)((unsigned long)context_ptr+0x000060a4+4*14))=0xdc54a9bb;
*((unsigned int *)((unsigned long)context_ptr+0x000060a4+4*15))=0x0cd518ea;
*((unsigned int *)((unsigned long)context_ptr+0x000060a4+4*16))=0x3a208eac;
*((unsigned int *)((unsigned long)context_ptr+0x000060a4+4*17))=0x2a3c2b10;
*((unsigned int *)((unsigned long)context_ptr+0x000060a4+4*18))=0xe58c438c;
*((unsigned int *)((unsigned long)context_ptr+0x000060a4+4*19))=0xb92132af;
*((unsigned int *)((unsigned long)context_ptr+0x000060a4+4*20))=0x9ee8d43b;
*((unsigned int *)((unsigned long)context_ptr+0x000060a4+4*21))=0x19944148;
*((unsigned int *)((unsigned long)context_ptr+0x000060a4+4*22))=0xac92d56a;
*((unsigned int *)((unsigned long)context_ptr+0x000060a4+4*23))=0x8c9a2288;
*((unsigned int *)((unsigned long)context_ptr+0x000060a4+4*24))=0xfaf783fc;
*((unsigned int *)((unsigned long)context_ptr+0x000060a4+4*25))=0xc8d58b3b;
*((unsigned int *)((unsigned long)context_ptr+0x000060a4+4*26))=0x8d1ffb6e;
*((unsigned int *)((unsigned long)context_ptr+0x000060a4+4*27))=0x190a7910;
*((unsigned int *)((unsigned long)context_ptr+0x00003a68))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003a68+4*1))=0x0000638c;
*((unsigned int *)((unsigned long)context_ptr+0x00003a68+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003a68+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003a68+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003a68+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000a68))=0x04c00070;
*((unsigned int *)((unsigned long)context_ptr+0x00000a68+4*1))=0x000060a4;
*((unsigned int *)((unsigned long)context_ptr+0x00000a68+4*2))=0x00006658;
*((unsigned int *)((unsigned long)context_ptr+0x00000a68+4*3))=0x02220070;
*((unsigned int *)((unsigned long)context_ptr+0x00000a68+4*4))=0x06f2462c;
*((unsigned int *)((unsigned long)context_ptr+0x00000a68+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000024c&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000063b0,"\x20\xd5\x16\xbd\x02\xd9\x03\x22\x4e\xa2\x35\xd9\x23\xd5\x6c\x3a\xba\x30\xe4\x5f\x7d\xd7\xa1\x8f\x56\x02\xdb\x9a",28))
printf("strip: 20d516bd02d90322, Pass\n");
else
printf("strip: 20d516bd02d90322, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006530))=0x026a1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006530+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006530+4*2))=0x02020071;
*((unsigned int *)((unsigned long)context_ptr+0x00006530+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x00006114))=0x72764791;
*((unsigned int *)((unsigned long)context_ptr+0x00006114+4*1))=0xebe354e7;
*((unsigned int *)((unsigned long)context_ptr+0x00006114+4*2))=0x7e97ed1e;
*((unsigned int *)((unsigned long)context_ptr+0x00006114+4*3))=0x4f075893;
*((unsigned int *)((unsigned long)context_ptr+0x00006114+4*4))=0xdfd41397;
*((unsigned int *)((unsigned long)context_ptr+0x00006114+4*5))=0xd4b74270;
*((unsigned int *)((unsigned long)context_ptr+0x00006114+4*6))=0x1ec952a9;
*((unsigned int *)((unsigned long)context_ptr+0x00006114+4*7))=0xa00b6956;
*((unsigned int *)((unsigned long)context_ptr+0x00006114+4*8))=0xc4a069c8;
*((unsigned int *)((unsigned long)context_ptr+0x00006114+4*9))=0xef40f5c2;
*((unsigned int *)((unsigned long)context_ptr+0x00006114+4*10))=0xeb5bc58a;
*((unsigned int *)((unsigned long)context_ptr+0x00006114+4*11))=0xee07ce62;
*((unsigned int *)((unsigned long)context_ptr+0x00006114+4*12))=0x7c65d35c;
*((unsigned int *)((unsigned long)context_ptr+0x00006114+4*13))=0xe2ed0336;
*((unsigned int *)((unsigned long)context_ptr+0x00006114+4*14))=0x5cea9541;
*((unsigned int *)((unsigned long)context_ptr+0x00006114+4*15))=0x9e849399;
*((unsigned int *)((unsigned long)context_ptr+0x00006114+4*16))=0xb74b1c1d;
*((unsigned int *)((unsigned long)context_ptr+0x00006114+4*17))=0x79cb0063;
*((unsigned int *)((unsigned long)context_ptr+0x00006114+4*18))=0x09c9b062;
*((unsigned int *)((unsigned long)context_ptr+0x00006114+4*19))=0x87ba2a38;
*((unsigned int *)((unsigned long)context_ptr+0x00006114+4*20))=0x03578f2d;
*((unsigned int *)((unsigned long)context_ptr+0x00006114+4*21))=0xb2efeeef;
*((unsigned int *)((unsigned long)context_ptr+0x00006114+4*22))=0x10af28cd;
*((unsigned int *)((unsigned long)context_ptr+0x00006114+4*23))=0xf582bb55;
*((unsigned int *)((unsigned long)context_ptr+0x00006114+4*24))=0xec63ab4a;
*((unsigned int *)((unsigned long)context_ptr+0x00006114+4*25))=0x88605584;
*((unsigned int *)((unsigned long)context_ptr+0x00006114+4*26))=0x709465f2;
*((unsigned int *)((unsigned long)context_ptr+0x00006114+4*27))=0xbe6df191;
*((unsigned int *)((unsigned long)context_ptr+0x00006114+4*28))=0x000000af;
*((unsigned int *)((unsigned long)context_ptr+0x00003a80))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003a80+4*1))=0x000063a8;
*((unsigned int *)((unsigned long)context_ptr+0x00003a80+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003a80+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003a80+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003a80+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000a80))=0x04c00071;
*((unsigned int *)((unsigned long)context_ptr+0x00000a80+4*1))=0x00006114;
*((unsigned int *)((unsigned long)context_ptr+0x00000a80+4*2))=0x00006530;
*((unsigned int *)((unsigned long)context_ptr+0x00000a80+4*3))=0x02220071;
*((unsigned int *)((unsigned long)context_ptr+0x00000a80+4*4))=0x00672a43;
*((unsigned int *)((unsigned long)context_ptr+0x00000a80+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000252&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000064ac,"\x2b\xf4\xb1\x09\x76\xa2\xa3\xd8\xb3\xea\x8c\x3c\x75\x3b\x5a\x2a\x86\x93\xa9\x7c\x6a\x09\xe8\x1b\x0e\xc9\xc7\xdd",28))
printf("strip: 2bf4b10976a2a3d8, Pass\n");
else
printf("strip: 2bf4b10976a2a3d8, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000063c4))=0x026a1002;
*((unsigned int *)((unsigned long)context_ptr+0x000063c4+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000063c4+4*2))=0x02020072;
*((unsigned int *)((unsigned long)context_ptr+0x000063c4+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x000068cc))=0x2b4a3be4;
*((unsigned int *)((unsigned long)context_ptr+0x000068cc+4*1))=0x47cb593b;
*((unsigned int *)((unsigned long)context_ptr+0x000068cc+4*2))=0xe2608f68;
*((unsigned int *)((unsigned long)context_ptr+0x000068cc+4*3))=0x9000ec93;
*((unsigned int *)((unsigned long)context_ptr+0x000068cc+4*4))=0xc5338530;
*((unsigned int *)((unsigned long)context_ptr+0x000068cc+4*5))=0x9b843721;
*((unsigned int *)((unsigned long)context_ptr+0x000068cc+4*6))=0x07b508b5;
*((unsigned int *)((unsigned long)context_ptr+0x000068cc+4*7))=0x61002732;
*((unsigned int *)((unsigned long)context_ptr+0x000068cc+4*8))=0xa3120658;
*((unsigned int *)((unsigned long)context_ptr+0x000068cc+4*9))=0x2bfbd80a;
*((unsigned int *)((unsigned long)context_ptr+0x000068cc+4*10))=0x5fb94323;
*((unsigned int *)((unsigned long)context_ptr+0x000068cc+4*11))=0x0a523b6e;
*((unsigned int *)((unsigned long)context_ptr+0x000068cc+4*12))=0x559a46b6;
*((unsigned int *)((unsigned long)context_ptr+0x000068cc+4*13))=0x204dbb92;
*((unsigned int *)((unsigned long)context_ptr+0x000068cc+4*14))=0x0c3ffeba;
*((unsigned int *)((unsigned long)context_ptr+0x000068cc+4*15))=0x22ea5eb4;
*((unsigned int *)((unsigned long)context_ptr+0x000068cc+4*16))=0x78fa8225;
*((unsigned int *)((unsigned long)context_ptr+0x000068cc+4*17))=0xffe52d68;
*((unsigned int *)((unsigned long)context_ptr+0x000068cc+4*18))=0x9dcd8023;
*((unsigned int *)((unsigned long)context_ptr+0x000068cc+4*19))=0x2487cf39;
*((unsigned int *)((unsigned long)context_ptr+0x000068cc+4*20))=0xe0493dc6;
*((unsigned int *)((unsigned long)context_ptr+0x000068cc+4*21))=0xb1e6af93;
*((unsigned int *)((unsigned long)context_ptr+0x000068cc+4*22))=0x92b279d0;
*((unsigned int *)((unsigned long)context_ptr+0x000068cc+4*23))=0x524523be;
*((unsigned int *)((unsigned long)context_ptr+0x000068cc+4*24))=0x4d0435c8;
*((unsigned int *)((unsigned long)context_ptr+0x000068cc+4*25))=0xd7dc9886;
*((unsigned int *)((unsigned long)context_ptr+0x000068cc+4*26))=0x33573788;
*((unsigned int *)((unsigned long)context_ptr+0x000068cc+4*27))=0xe0e13cae;
*((unsigned int *)((unsigned long)context_ptr+0x000068cc+4*28))=0x00006b47;
*((unsigned int *)((unsigned long)context_ptr+0x00003a98))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003a98+4*1))=0x000064a8;
*((unsigned int *)((unsigned long)context_ptr+0x00003a98+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003a98+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003a98+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003a98+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000a98))=0x04c00072;
*((unsigned int *)((unsigned long)context_ptr+0x00000a98+4*1))=0x000068cc;
*((unsigned int *)((unsigned long)context_ptr+0x00000a98+4*2))=0x000063c4;
*((unsigned int *)((unsigned long)context_ptr+0x00000a98+4*3))=0x02220072;
*((unsigned int *)((unsigned long)context_ptr+0x00000a98+4*4))=0x0681ad50;
*((unsigned int *)((unsigned long)context_ptr+0x00000a98+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000258&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000064c8,"\xdc\xbc\x4c\xd4\x89\xbf\x0e\xcf\xcf\xff\x29\x57\x0c\x7d\x28\x58\xb6\x7b\x38\x3d\x45\xa6\x1c\x25\x67\x9c\xf3\x60",28))
printf("strip: dcbc4cd489bf0ecf, Pass\n");
else
printf("strip: dcbc4cd489bf0ecf, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000063d4))=0x026a1002;
*((unsigned int *)((unsigned long)context_ptr+0x000063d4+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000063d4+4*2))=0x02020073;
*((unsigned int *)((unsigned long)context_ptr+0x000063d4+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x00006740))=0x29e2f27d;
*((unsigned int *)((unsigned long)context_ptr+0x00006740+4*1))=0x10ffbff7;
*((unsigned int *)((unsigned long)context_ptr+0x00006740+4*2))=0x079ef2f5;
*((unsigned int *)((unsigned long)context_ptr+0x00006740+4*3))=0xe5866614;
*((unsigned int *)((unsigned long)context_ptr+0x00006740+4*4))=0x2755f119;
*((unsigned int *)((unsigned long)context_ptr+0x00006740+4*5))=0x9da99c86;
*((unsigned int *)((unsigned long)context_ptr+0x00006740+4*6))=0xf5b7c0c7;
*((unsigned int *)((unsigned long)context_ptr+0x00006740+4*7))=0x51216a43;
*((unsigned int *)((unsigned long)context_ptr+0x00006740+4*8))=0x991a4a39;
*((unsigned int *)((unsigned long)context_ptr+0x00006740+4*9))=0xaf3b8256;
*((unsigned int *)((unsigned long)context_ptr+0x00006740+4*10))=0x5f6ef8ab;
*((unsigned int *)((unsigned long)context_ptr+0x00006740+4*11))=0xdca87a08;
*((unsigned int *)((unsigned long)context_ptr+0x00006740+4*12))=0x3dbf69e7;
*((unsigned int *)((unsigned long)context_ptr+0x00006740+4*13))=0x52cc3ef9;
*((unsigned int *)((unsigned long)context_ptr+0x00006740+4*14))=0x672f4d42;
*((unsigned int *)((unsigned long)context_ptr+0x00006740+4*15))=0x0c68224a;
*((unsigned int *)((unsigned long)context_ptr+0x00006740+4*16))=0x9e21a5e4;
*((unsigned int *)((unsigned long)context_ptr+0x00006740+4*17))=0x2f085b36;
*((unsigned int *)((unsigned long)context_ptr+0x00006740+4*18))=0x12c8f800;
*((unsigned int *)((unsigned long)context_ptr+0x00006740+4*19))=0xd045cd91;
*((unsigned int *)((unsigned long)context_ptr+0x00006740+4*20))=0x8f37638b;
*((unsigned int *)((unsigned long)context_ptr+0x00006740+4*21))=0xbb3a48aa;
*((unsigned int *)((unsigned long)context_ptr+0x00006740+4*22))=0x3b02864e;
*((unsigned int *)((unsigned long)context_ptr+0x00006740+4*23))=0xf72be13d;
*((unsigned int *)((unsigned long)context_ptr+0x00006740+4*24))=0xd63a1b35;
*((unsigned int *)((unsigned long)context_ptr+0x00006740+4*25))=0xa3b02769;
*((unsigned int *)((unsigned long)context_ptr+0x00006740+4*26))=0x67afb732;
*((unsigned int *)((unsigned long)context_ptr+0x00006740+4*27))=0xf33aef46;
*((unsigned int *)((unsigned long)context_ptr+0x00006740+4*28))=0x006e503c;
*((unsigned int *)((unsigned long)context_ptr+0x00003ab0))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003ab0+4*1))=0x000064c4;
*((unsigned int *)((unsigned long)context_ptr+0x00003ab0+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003ab0+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003ab0+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003ab0+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000ab0))=0x04c00073;
*((unsigned int *)((unsigned long)context_ptr+0x00000ab0+4*1))=0x00006740;
*((unsigned int *)((unsigned long)context_ptr+0x00000ab0+4*2))=0x000063d4;
*((unsigned int *)((unsigned long)context_ptr+0x00000ab0+4*3))=0x02220073;
*((unsigned int *)((unsigned long)context_ptr+0x00000ab0+4*4))=0x0505f365;
*((unsigned int *)((unsigned long)context_ptr+0x00000ab0+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000025e&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x0000680c,"\x0c\x45\x4a\x6a\x2a\xcf\x1f\xc7\xcb\xff\x34\x95\x3c\x79\x4e\xa6\x8c\xcd\x79\xe8\x53\xf8\xf6\xea\xfa\xb4\x1e\x9c",28))
printf("strip: 0c454a6a2acf1fc7, Pass\n");
else
printf("strip: 0c454a6a2acf1fc7, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000064e0))=0x026a1002;
*((unsigned int *)((unsigned long)context_ptr+0x000064e0+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000064e0+4*2))=0x02020074;
*((unsigned int *)((unsigned long)context_ptr+0x000064e0+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x000067b4))=0x3e922cdd;
*((unsigned int *)((unsigned long)context_ptr+0x000067b4+4*1))=0x02f5a65a;
*((unsigned int *)((unsigned long)context_ptr+0x000067b4+4*2))=0x77a7df0e;
*((unsigned int *)((unsigned long)context_ptr+0x000067b4+4*3))=0xdd6b143e;
*((unsigned int *)((unsigned long)context_ptr+0x000067b4+4*4))=0x67a15bdc;
*((unsigned int *)((unsigned long)context_ptr+0x000067b4+4*5))=0x117e3b10;
*((unsigned int *)((unsigned long)context_ptr+0x000067b4+4*6))=0x5c96e513;
*((unsigned int *)((unsigned long)context_ptr+0x000067b4+4*7))=0xd71539f2;
*((unsigned int *)((unsigned long)context_ptr+0x000067b4+4*8))=0xdd13edc5;
*((unsigned int *)((unsigned long)context_ptr+0x000067b4+4*9))=0x547ce0f0;
*((unsigned int *)((unsigned long)context_ptr+0x000067b4+4*10))=0x4fd249d0;
*((unsigned int *)((unsigned long)context_ptr+0x000067b4+4*11))=0xb5d6de30;
*((unsigned int *)((unsigned long)context_ptr+0x000067b4+4*12))=0x9cd878e7;
*((unsigned int *)((unsigned long)context_ptr+0x000067b4+4*13))=0xc9dc7008;
*((unsigned int *)((unsigned long)context_ptr+0x000067b4+4*14))=0x41e853d7;
*((unsigned int *)((unsigned long)context_ptr+0x000067b4+4*15))=0xcf0d1730;
*((unsigned int *)((unsigned long)context_ptr+0x000067b4+4*16))=0x6a936cac;
*((unsigned int *)((unsigned long)context_ptr+0x000067b4+4*17))=0x613aa6e6;
*((unsigned int *)((unsigned long)context_ptr+0x000067b4+4*18))=0x41b793b0;
*((unsigned int *)((unsigned long)context_ptr+0x000067b4+4*19))=0x44fe370b;
*((unsigned int *)((unsigned long)context_ptr+0x000067b4+4*20))=0x2284a7e6;
*((unsigned int *)((unsigned long)context_ptr+0x000067b4+4*21))=0x2ab09992;
*((unsigned int *)((unsigned long)context_ptr+0x000067b4+4*22))=0x94d9d77d;
*((unsigned int *)((unsigned long)context_ptr+0x000067b4+4*23))=0xb4e7a35e;
*((unsigned int *)((unsigned long)context_ptr+0x000067b4+4*24))=0x0c551f87;
*((unsigned int *)((unsigned long)context_ptr+0x000067b4+4*25))=0x8547ed9f;
*((unsigned int *)((unsigned long)context_ptr+0x000067b4+4*26))=0x2505479d;
*((unsigned int *)((unsigned long)context_ptr+0x000067b4+4*27))=0xac3d1f0c;
*((unsigned int *)((unsigned long)context_ptr+0x000067b4+4*28))=0x28b9eef7;
*((unsigned int *)((unsigned long)context_ptr+0x00003ac8))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003ac8+4*1))=0x00006940;
*((unsigned int *)((unsigned long)context_ptr+0x00003ac8+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003ac8+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003ac8+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003ac8+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000ac8))=0x04c00074;
*((unsigned int *)((unsigned long)context_ptr+0x00000ac8+4*1))=0x000067b4;
*((unsigned int *)((unsigned long)context_ptr+0x00000ac8+4*2))=0x000064e0;
*((unsigned int *)((unsigned long)context_ptr+0x00000ac8+4*3))=0x02220074;
*((unsigned int *)((unsigned long)context_ptr+0x00000ac8+4*4))=0x04e2cb48;
*((unsigned int *)((unsigned long)context_ptr+0x00000ac8+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000264&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000064f4,"\x38\x94\x31\x94\x79\x50\xbe\x68\x9a\xbe\xcd\x01\x78\x66\x3d\x9e\x66\x3a\x14\x87\x01\x5d\xc3\x2d\xa5\xd4\x2e\x74",28))
printf("strip: 389431947950be68, Pass\n");
else
printf("strip: 389431947950be68, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000063e4))=0x026a1002;
*((unsigned int *)((unsigned long)context_ptr+0x000063e4+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000063e4+4*2))=0x02020075;
*((unsigned int *)((unsigned long)context_ptr+0x000063e4+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x000069d8))=0x24f2af2b;
*((unsigned int *)((unsigned long)context_ptr+0x000069d8+4*1))=0xa9518e20;
*((unsigned int *)((unsigned long)context_ptr+0x000069d8+4*2))=0xfd2ab048;
*((unsigned int *)((unsigned long)context_ptr+0x000069d8+4*3))=0xdef9fa77;
*((unsigned int *)((unsigned long)context_ptr+0x000069d8+4*4))=0xae6d8568;
*((unsigned int *)((unsigned long)context_ptr+0x000069d8+4*5))=0x33e46a4e;
*((unsigned int *)((unsigned long)context_ptr+0x000069d8+4*6))=0xdf823a6c;
*((unsigned int *)((unsigned long)context_ptr+0x000069d8+4*7))=0x6008b4a1;
*((unsigned int *)((unsigned long)context_ptr+0x000069d8+4*8))=0x003d5a3c;
*((unsigned int *)((unsigned long)context_ptr+0x000069d8+4*9))=0x9945ab6f;
*((unsigned int *)((unsigned long)context_ptr+0x000069d8+4*10))=0x75b0e468;
*((unsigned int *)((unsigned long)context_ptr+0x000069d8+4*11))=0xbf8e80be;
*((unsigned int *)((unsigned long)context_ptr+0x000069d8+4*12))=0xb7c8799f;
*((unsigned int *)((unsigned long)context_ptr+0x000069d8+4*13))=0x1e021eb3;
*((unsigned int *)((unsigned long)context_ptr+0x000069d8+4*14))=0x255f74bb;
*((unsigned int *)((unsigned long)context_ptr+0x000069d8+4*15))=0x62796387;
*((unsigned int *)((unsigned long)context_ptr+0x000069d8+4*16))=0x09053681;
*((unsigned int *)((unsigned long)context_ptr+0x000069d8+4*17))=0xb4f17fd2;
*((unsigned int *)((unsigned long)context_ptr+0x000069d8+4*18))=0xd23c0597;
*((unsigned int *)((unsigned long)context_ptr+0x000069d8+4*19))=0xb799c6f0;
*((unsigned int *)((unsigned long)context_ptr+0x000069d8+4*20))=0xd03d8ce8;
*((unsigned int *)((unsigned long)context_ptr+0x000069d8+4*21))=0x5dd95db1;
*((unsigned int *)((unsigned long)context_ptr+0x000069d8+4*22))=0xcd676f57;
*((unsigned int *)((unsigned long)context_ptr+0x000069d8+4*23))=0x946cfe04;
*((unsigned int *)((unsigned long)context_ptr+0x000069d8+4*24))=0x5419d4e1;
*((unsigned int *)((unsigned long)context_ptr+0x000069d8+4*25))=0xe991245b;
*((unsigned int *)((unsigned long)context_ptr+0x000069d8+4*26))=0x4a78eadb;
*((unsigned int *)((unsigned long)context_ptr+0x000069d8+4*27))=0x4c9eb058;
*((unsigned int *)((unsigned long)context_ptr+0x000069d8+4*28))=0xff92d803;
*((unsigned int *)((unsigned long)context_ptr+0x000069d8+4*29))=0x0000007f;
*((unsigned int *)((unsigned long)context_ptr+0x00003ae0))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003ae0+4*1))=0x000064f0;
*((unsigned int *)((unsigned long)context_ptr+0x00003ae0+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003ae0+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003ae0+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003ae0+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000ae0))=0x04c00075;
*((unsigned int *)((unsigned long)context_ptr+0x00000ae0+4*1))=0x000069d8;
*((unsigned int *)((unsigned long)context_ptr+0x00000ae0+4*2))=0x000063e4;
*((unsigned int *)((unsigned long)context_ptr+0x00000ae0+4*3))=0x02220075;
*((unsigned int *)((unsigned long)context_ptr+0x00000ae0+4*4))=0x01aaa01e;
*((unsigned int *)((unsigned long)context_ptr+0x00000ae0+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000026a&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000063fc,"\x61\x63\xe2\x82\x10\xc6\xd3\xf7\x43\x7d\x15\xa6\xad\x0e\x92\xbe\x00\x41\x67\x08\xb2\x77\xb1\x01\x2e\x3c\x97\x7b",28))
printf("strip: 6163e28210c6d3f7, Pass\n");
else
printf("strip: 6163e28210c6d3f7, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x0000650c))=0x026a1002;
*((unsigned int *)((unsigned long)context_ptr+0x0000650c+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x0000650c+4*2))=0x02020076;
*((unsigned int *)((unsigned long)context_ptr+0x0000650c+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x00006a50))=0x8edeedf2;
*((unsigned int *)((unsigned long)context_ptr+0x00006a50+4*1))=0xc825c9c7;
*((unsigned int *)((unsigned long)context_ptr+0x00006a50+4*2))=0xbd178865;
*((unsigned int *)((unsigned long)context_ptr+0x00006a50+4*3))=0xa300585a;
*((unsigned int *)((unsigned long)context_ptr+0x00006a50+4*4))=0xd091bf99;
*((unsigned int *)((unsigned long)context_ptr+0x00006a50+4*5))=0xc0ce85e7;
*((unsigned int *)((unsigned long)context_ptr+0x00006a50+4*6))=0x324f416a;
*((unsigned int *)((unsigned long)context_ptr+0x00006a50+4*7))=0xe21bebfa;
*((unsigned int *)((unsigned long)context_ptr+0x00006a50+4*8))=0x231c7eb9;
*((unsigned int *)((unsigned long)context_ptr+0x00006a50+4*9))=0x430585f6;
*((unsigned int *)((unsigned long)context_ptr+0x00006a50+4*10))=0xbddb640d;
*((unsigned int *)((unsigned long)context_ptr+0x00006a50+4*11))=0x4f558362;
*((unsigned int *)((unsigned long)context_ptr+0x00006a50+4*12))=0xb7ca8548;
*((unsigned int *)((unsigned long)context_ptr+0x00006a50+4*13))=0x742a9f27;
*((unsigned int *)((unsigned long)context_ptr+0x00006a50+4*14))=0x691fb8d0;
*((unsigned int *)((unsigned long)context_ptr+0x00006a50+4*15))=0x5a5a8adc;
*((unsigned int *)((unsigned long)context_ptr+0x00006a50+4*16))=0xcdb7216e;
*((unsigned int *)((unsigned long)context_ptr+0x00006a50+4*17))=0x5de42198;
*((unsigned int *)((unsigned long)context_ptr+0x00006a50+4*18))=0xb05cf8f9;
*((unsigned int *)((unsigned long)context_ptr+0x00006a50+4*19))=0x922fd1e0;
*((unsigned int *)((unsigned long)context_ptr+0x00006a50+4*20))=0x600dd4cb;
*((unsigned int *)((unsigned long)context_ptr+0x00006a50+4*21))=0x1a1a9ca5;
*((unsigned int *)((unsigned long)context_ptr+0x00006a50+4*22))=0xb641daeb;
*((unsigned int *)((unsigned long)context_ptr+0x00006a50+4*23))=0x74ec2077;
*((unsigned int *)((unsigned long)context_ptr+0x00006a50+4*24))=0x05f8571a;
*((unsigned int *)((unsigned long)context_ptr+0x00006a50+4*25))=0x2d94a68f;
*((unsigned int *)((unsigned long)context_ptr+0x00006a50+4*26))=0x6e20baf1;
*((unsigned int *)((unsigned long)context_ptr+0x00006a50+4*27))=0x3a419bb6;
*((unsigned int *)((unsigned long)context_ptr+0x00006a50+4*28))=0x61d8ec3b;
*((unsigned int *)((unsigned long)context_ptr+0x00006a50+4*29))=0x0000dcf1;
*((unsigned int *)((unsigned long)context_ptr+0x00003af8))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003af8+4*1))=0x000063f4;
*((unsigned int *)((unsigned long)context_ptr+0x00003af8+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003af8+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003af8+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003af8+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000af8))=0x04c00076;
*((unsigned int *)((unsigned long)context_ptr+0x00000af8+4*1))=0x00006a50;
*((unsigned int *)((unsigned long)context_ptr+0x00000af8+4*2))=0x0000650c;
*((unsigned int *)((unsigned long)context_ptr+0x00000af8+4*3))=0x02220076;
*((unsigned int *)((unsigned long)context_ptr+0x00000af8+4*4))=0x051e3b3e;
*((unsigned int *)((unsigned long)context_ptr+0x00000af8+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000270&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006828,"\xba\xda\x26\xd3\x72\xfd\xdc\xb9\xe3\xf6\x0b\xae\x1c\x27\xb1\x51\x74\x1e\xc4\x48\xf3\xd6\x89\x3f\xc1\xd0\x5c\xd1",28))
printf("strip: bada26d372fddcb9, Pass\n");
else
printf("strip: bada26d372fddcb9, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006410))=0x026a1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006410+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006410+4*2))=0x02020077;
*((unsigned int *)((unsigned long)context_ptr+0x00006410+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x00006540))=0xe62101f0;
*((unsigned int *)((unsigned long)context_ptr+0x00006540+4*1))=0xa764bc5b;
*((unsigned int *)((unsigned long)context_ptr+0x00006540+4*2))=0x97dc0e45;
*((unsigned int *)((unsigned long)context_ptr+0x00006540+4*3))=0x11c44eb6;
*((unsigned int *)((unsigned long)context_ptr+0x00006540+4*4))=0x09c2fffc;
*((unsigned int *)((unsigned long)context_ptr+0x00006540+4*5))=0xa0641905;
*((unsigned int *)((unsigned long)context_ptr+0x00006540+4*6))=0xbb0a7e7f;
*((unsigned int *)((unsigned long)context_ptr+0x00006540+4*7))=0x879577a7;
*((unsigned int *)((unsigned long)context_ptr+0x00006540+4*8))=0x61afbeb5;
*((unsigned int *)((unsigned long)context_ptr+0x00006540+4*9))=0x0453900c;
*((unsigned int *)((unsigned long)context_ptr+0x00006540+4*10))=0x7595206e;
*((unsigned int *)((unsigned long)context_ptr+0x00006540+4*11))=0xe96bfcce;
*((unsigned int *)((unsigned long)context_ptr+0x00006540+4*12))=0x8a5d82fb;
*((unsigned int *)((unsigned long)context_ptr+0x00006540+4*13))=0x065737f9;
*((unsigned int *)((unsigned long)context_ptr+0x00006540+4*14))=0xd7267ce5;
*((unsigned int *)((unsigned long)context_ptr+0x00006540+4*15))=0x2241fe7d;
*((unsigned int *)((unsigned long)context_ptr+0x00006540+4*16))=0x52c991f5;
*((unsigned int *)((unsigned long)context_ptr+0x00006540+4*17))=0x1b8efa40;
*((unsigned int *)((unsigned long)context_ptr+0x00006540+4*18))=0x6583b9aa;
*((unsigned int *)((unsigned long)context_ptr+0x00006540+4*19))=0xcfc8247f;
*((unsigned int *)((unsigned long)context_ptr+0x00006540+4*20))=0xd90e0ba5;
*((unsigned int *)((unsigned long)context_ptr+0x00006540+4*21))=0xc31cc0ea;
*((unsigned int *)((unsigned long)context_ptr+0x00006540+4*22))=0x638d843b;
*((unsigned int *)((unsigned long)context_ptr+0x00006540+4*23))=0x69cc0557;
*((unsigned int *)((unsigned long)context_ptr+0x00006540+4*24))=0x5ce7a353;
*((unsigned int *)((unsigned long)context_ptr+0x00006540+4*25))=0xf93d39df;
*((unsigned int *)((unsigned long)context_ptr+0x00006540+4*26))=0x379177e5;
*((unsigned int *)((unsigned long)context_ptr+0x00006540+4*27))=0xff578dc4;
*((unsigned int *)((unsigned long)context_ptr+0x00006540+4*28))=0x05bce404;
*((unsigned int *)((unsigned long)context_ptr+0x00006540+4*29))=0x00eaea20;
*((unsigned int *)((unsigned long)context_ptr+0x00003b10))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003b10+4*1))=0x00006828;
*((unsigned int *)((unsigned long)context_ptr+0x00003b10+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003b10+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003b10+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003b10+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000b10))=0x04c00077;
*((unsigned int *)((unsigned long)context_ptr+0x00000b10+4*1))=0x00006540;
*((unsigned int *)((unsigned long)context_ptr+0x00000b10+4*2))=0x00006410;
*((unsigned int *)((unsigned long)context_ptr+0x00000b10+4*3))=0x02220077;
*((unsigned int *)((unsigned long)context_ptr+0x00000b10+4*4))=0x062fd780;
*((unsigned int *)((unsigned long)context_ptr+0x00000b10+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000276&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006610,"\x98\x5f\x8d\x66\xce\xbb\x9b\xff\x98\x44\xed\x44\xf4\x07\x06\x4d\x21\xf6\x1a\x8c\x0a\xcf\xad\x1e\x8d\x79\x42\x99",28))
printf("strip: 985f8d66cebb9bff, Pass\n");
else
printf("strip: 985f8d66cebb9bff, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x0000651c))=0x026a1002;
*((unsigned int *)((unsigned long)context_ptr+0x0000651c+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x0000651c+4*2))=0x02020078;
*((unsigned int *)((unsigned long)context_ptr+0x0000651c+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x00006188))=0xcc5bbd8f;
*((unsigned int *)((unsigned long)context_ptr+0x00006188+4*1))=0x7435495f;
*((unsigned int *)((unsigned long)context_ptr+0x00006188+4*2))=0xae180999;
*((unsigned int *)((unsigned long)context_ptr+0x00006188+4*3))=0x51b5551e;
*((unsigned int *)((unsigned long)context_ptr+0x00006188+4*4))=0x9688c451;
*((unsigned int *)((unsigned long)context_ptr+0x00006188+4*5))=0xbe5decee;
*((unsigned int *)((unsigned long)context_ptr+0x00006188+4*6))=0xa9012dc1;
*((unsigned int *)((unsigned long)context_ptr+0x00006188+4*7))=0xd4cecce7;
*((unsigned int *)((unsigned long)context_ptr+0x00006188+4*8))=0x7bd4d99c;
*((unsigned int *)((unsigned long)context_ptr+0x00006188+4*9))=0x24a3fa21;
*((unsigned int *)((unsigned long)context_ptr+0x00006188+4*10))=0x95d385f5;
*((unsigned int *)((unsigned long)context_ptr+0x00006188+4*11))=0x66fec2b4;
*((unsigned int *)((unsigned long)context_ptr+0x00006188+4*12))=0xa8e90b81;
*((unsigned int *)((unsigned long)context_ptr+0x00006188+4*13))=0x3611e097;
*((unsigned int *)((unsigned long)context_ptr+0x00006188+4*14))=0xd548edfc;
*((unsigned int *)((unsigned long)context_ptr+0x00006188+4*15))=0x9dbc6236;
*((unsigned int *)((unsigned long)context_ptr+0x00006188+4*16))=0x4f372caa;
*((unsigned int *)((unsigned long)context_ptr+0x00006188+4*17))=0xe9564470;
*((unsigned int *)((unsigned long)context_ptr+0x00006188+4*18))=0xf8c3fea3;
*((unsigned int *)((unsigned long)context_ptr+0x00006188+4*19))=0x56349ebe;
*((unsigned int *)((unsigned long)context_ptr+0x00006188+4*20))=0xd0f904de;
*((unsigned int *)((unsigned long)context_ptr+0x00006188+4*21))=0x6918d83c;
*((unsigned int *)((unsigned long)context_ptr+0x00006188+4*22))=0x6c10dacd;
*((unsigned int *)((unsigned long)context_ptr+0x00006188+4*23))=0xf25f68cd;
*((unsigned int *)((unsigned long)context_ptr+0x00006188+4*24))=0x869f3d24;
*((unsigned int *)((unsigned long)context_ptr+0x00006188+4*25))=0xc5953159;
*((unsigned int *)((unsigned long)context_ptr+0x00006188+4*26))=0xa57a2d0b;
*((unsigned int *)((unsigned long)context_ptr+0x00006188+4*27))=0x2827c64e;
*((unsigned int *)((unsigned long)context_ptr+0x00006188+4*28))=0x9dec7b59;
*((unsigned int *)((unsigned long)context_ptr+0x00006188+4*29))=0x7d98bec6;
*((unsigned int *)((unsigned long)context_ptr+0x00003b28))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003b28+4*1))=0x00006200;
*((unsigned int *)((unsigned long)context_ptr+0x00003b28+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003b28+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003b28+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003b28+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000b28))=0x04c00078;
*((unsigned int *)((unsigned long)context_ptr+0x00000b28+4*1))=0x00006188;
*((unsigned int *)((unsigned long)context_ptr+0x00000b28+4*2))=0x0000651c;
*((unsigned int *)((unsigned long)context_ptr+0x00000b28+4*3))=0x02220078;
*((unsigned int *)((unsigned long)context_ptr+0x00000b28+4*4))=0x0adc0156;
*((unsigned int *)((unsigned long)context_ptr+0x00000b28+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000027c&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x0000625c,"\xca\xf3\x8d\x60\xd3\xc8\x3b\x83\x37\x89\xd7\xc7\xc8\xbf\x01\x8e\x16\x8e\x36\x63\x66\x6c\x0e\x8c\x6c\x10\xff\x56",28))
printf("strip: caf38d60d3c83b83, Pass\n");
else
printf("strip: caf38d60d3c83b83, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006058))=0x026a1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*2))=0x02020079;
*((unsigned int *)((unsigned long)context_ptr+0x00006058+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x00006668))=0xc252ea90;
*((unsigned int *)((unsigned long)context_ptr+0x00006668+4*1))=0xe4066998;
*((unsigned int *)((unsigned long)context_ptr+0x00006668+4*2))=0x49d1de7d;
*((unsigned int *)((unsigned long)context_ptr+0x00006668+4*3))=0xd5acd69a;
*((unsigned int *)((unsigned long)context_ptr+0x00006668+4*4))=0xde152b74;
*((unsigned int *)((unsigned long)context_ptr+0x00006668+4*5))=0x9854a427;
*((unsigned int *)((unsigned long)context_ptr+0x00006668+4*6))=0x1a354373;
*((unsigned int *)((unsigned long)context_ptr+0x00006668+4*7))=0xcfc64b89;
*((unsigned int *)((unsigned long)context_ptr+0x00006668+4*8))=0xe4bfc260;
*((unsigned int *)((unsigned long)context_ptr+0x00006668+4*9))=0xfc2fe2b6;
*((unsigned int *)((unsigned long)context_ptr+0x00006668+4*10))=0x7dcbc749;
*((unsigned int *)((unsigned long)context_ptr+0x00006668+4*11))=0x374e0ae9;
*((unsigned int *)((unsigned long)context_ptr+0x00006668+4*12))=0x46328a09;
*((unsigned int *)((unsigned long)context_ptr+0x00006668+4*13))=0x1e1cca92;
*((unsigned int *)((unsigned long)context_ptr+0x00006668+4*14))=0x9e8407e0;
*((unsigned int *)((unsigned long)context_ptr+0x00006668+4*15))=0xbee36712;
*((unsigned int *)((unsigned long)context_ptr+0x00006668+4*16))=0x87b39cbe;
*((unsigned int *)((unsigned long)context_ptr+0x00006668+4*17))=0xbcc3f135;
*((unsigned int *)((unsigned long)context_ptr+0x00006668+4*18))=0xb19d3910;
*((unsigned int *)((unsigned long)context_ptr+0x00006668+4*19))=0xe61b9172;
*((unsigned int *)((unsigned long)context_ptr+0x00006668+4*20))=0x640f865d;
*((unsigned int *)((unsigned long)context_ptr+0x00006668+4*21))=0xc6ca2c92;
*((unsigned int *)((unsigned long)context_ptr+0x00006668+4*22))=0x633094f7;
*((unsigned int *)((unsigned long)context_ptr+0x00006668+4*23))=0xa47168c4;
*((unsigned int *)((unsigned long)context_ptr+0x00006668+4*24))=0x8997656e;
*((unsigned int *)((unsigned long)context_ptr+0x00006668+4*25))=0xee19f837;
*((unsigned int *)((unsigned long)context_ptr+0x00006668+4*26))=0x08a469e1;
*((unsigned int *)((unsigned long)context_ptr+0x00006668+4*27))=0x85bc3293;
*((unsigned int *)((unsigned long)context_ptr+0x00006668+4*28))=0xcbde6476;
*((unsigned int *)((unsigned long)context_ptr+0x00006668+4*29))=0x8d84adbf;
*((unsigned int *)((unsigned long)context_ptr+0x00006668+4*30))=0x00000047;
*((unsigned int *)((unsigned long)context_ptr+0x00003b40))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003b40+4*1))=0x0000621c;
*((unsigned int *)((unsigned long)context_ptr+0x00003b40+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003b40+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003b40+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003b40+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000b40))=0x04c00079;
*((unsigned int *)((unsigned long)context_ptr+0x00000b40+4*1))=0x00006668;
*((unsigned int *)((unsigned long)context_ptr+0x00000b40+4*2))=0x00006058;
*((unsigned int *)((unsigned long)context_ptr+0x00000b40+4*3))=0x02220079;
*((unsigned int *)((unsigned long)context_ptr+0x00000b40+4*4))=0x0c9576f9;
*((unsigned int *)((unsigned long)context_ptr+0x00000b40+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000282&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006078,"\x33\xa3\x6c\xa0\xa4\x2d\x60\xf3\xdc\x2b\x5a\xad\xc8\xba\x88\xcd\x44\xca\xfb\x9c\xcf\x88\x27\xd5\x89\xbb\xfe\x54",28))
printf("strip: 33a36ca0a42d60f3, Pass\n");
else
printf("strip: 33a36ca0a42d60f3, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006048))=0x026a1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006048+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006048+4*2))=0x0202007a;
*((unsigned int *)((unsigned long)context_ptr+0x00006048+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x00006238))=0x6a23bec5;
*((unsigned int *)((unsigned long)context_ptr+0x00006238+4*1))=0x0bfeb9be;
*((unsigned int *)((unsigned long)context_ptr+0x00006238+4*2))=0x490d30ba;
*((unsigned int *)((unsigned long)context_ptr+0x00006238+4*3))=0x0474e7bd;
*((unsigned int *)((unsigned long)context_ptr+0x00006238+4*4))=0x86d9f012;
*((unsigned int *)((unsigned long)context_ptr+0x00006238+4*5))=0x9342e832;
*((unsigned int *)((unsigned long)context_ptr+0x00006238+4*6))=0x8f03ccb9;
*((unsigned int *)((unsigned long)context_ptr+0x00006238+4*7))=0x0a7c9548;
*((unsigned int *)((unsigned long)context_ptr+0x00006238+4*8))=0xecaec5ff;
*((unsigned int *)((unsigned long)context_ptr+0x00006238+4*9))=0x0df82c97;
*((unsigned int *)((unsigned long)context_ptr+0x00006238+4*10))=0x8c54a40e;
*((unsigned int *)((unsigned long)context_ptr+0x00006238+4*11))=0x9eb46454;
*((unsigned int *)((unsigned long)context_ptr+0x00006238+4*12))=0xf46b56f0;
*((unsigned int *)((unsigned long)context_ptr+0x00006238+4*13))=0xc9ca1ce8;
*((unsigned int *)((unsigned long)context_ptr+0x00006238+4*14))=0x35ffb541;
*((unsigned int *)((unsigned long)context_ptr+0x00006238+4*15))=0x8334f6c4;
*((unsigned int *)((unsigned long)context_ptr+0x00006238+4*16))=0xaf9f80fb;
*((unsigned int *)((unsigned long)context_ptr+0x00006238+4*17))=0x1d33cc6c;
*((unsigned int *)((unsigned long)context_ptr+0x00006238+4*18))=0x66638abb;
*((unsigned int *)((unsigned long)context_ptr+0x00006238+4*19))=0x87f55b6a;
*((unsigned int *)((unsigned long)context_ptr+0x00006238+4*20))=0x64254ab7;
*((unsigned int *)((unsigned long)context_ptr+0x00006238+4*21))=0x3a9cb6ba;
*((unsigned int *)((unsigned long)context_ptr+0x00006238+4*22))=0x4b430dba;
*((unsigned int *)((unsigned long)context_ptr+0x00006238+4*23))=0x5197a314;
*((unsigned int *)((unsigned long)context_ptr+0x00006238+4*24))=0x8b3decdc;
*((unsigned int *)((unsigned long)context_ptr+0x00006238+4*25))=0xaa1937e7;
*((unsigned int *)((unsigned long)context_ptr+0x00006238+4*26))=0xb9af1ace;
*((unsigned int *)((unsigned long)context_ptr+0x00006238+4*27))=0x53aa4b3a;
*((unsigned int *)((unsigned long)context_ptr+0x00006238+4*28))=0xc81a1e07;
*((unsigned int *)((unsigned long)context_ptr+0x00006238+4*29))=0x954a328c;
*((unsigned int *)((unsigned long)context_ptr+0x00006238+4*30))=0x00007f2a;
*((unsigned int *)((unsigned long)context_ptr+0x00003b58))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003b58+4*1))=0x00006078;
*((unsigned int *)((unsigned long)context_ptr+0x00003b58+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003b58+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003b58+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003b58+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000b58))=0x04c0007a;
*((unsigned int *)((unsigned long)context_ptr+0x00000b58+4*1))=0x00006238;
*((unsigned int *)((unsigned long)context_ptr+0x00000b58+4*2))=0x00006048;
*((unsigned int *)((unsigned long)context_ptr+0x00000b58+4*3))=0x0222007a;
*((unsigned int *)((unsigned long)context_ptr+0x00000b58+4*4))=0x096897c1;
*((unsigned int *)((unsigned long)context_ptr+0x00000b58+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000288&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000062e4,"\xce\x96\x42\x65\xee\xe1\x07\xee\xc4\xe4\x74\x3d\x98\x45\x3b\x28\x61\xfa\xf2\x8c\xe5\xf6\x31\xde\x70\x02\xeb\x74",28))
printf("strip: ce964265eee107ee, Pass\n");
else
printf("strip: ce964265eee107ee, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006068))=0x026a1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006068+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006068+4*2))=0x0202007b;
*((unsigned int *)((unsigned long)context_ptr+0x00006068+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x00006ac8))=0x02dbaa81;
*((unsigned int *)((unsigned long)context_ptr+0x00006ac8+4*1))=0xb33e34a0;
*((unsigned int *)((unsigned long)context_ptr+0x00006ac8+4*2))=0x47b7ed20;
*((unsigned int *)((unsigned long)context_ptr+0x00006ac8+4*3))=0x3390b336;
*((unsigned int *)((unsigned long)context_ptr+0x00006ac8+4*4))=0xc85dcf1d;
*((unsigned int *)((unsigned long)context_ptr+0x00006ac8+4*5))=0xad39ec7f;
*((unsigned int *)((unsigned long)context_ptr+0x00006ac8+4*6))=0x2bec3285;
*((unsigned int *)((unsigned long)context_ptr+0x00006ac8+4*7))=0xc60ef9f2;
*((unsigned int *)((unsigned long)context_ptr+0x00006ac8+4*8))=0x96ba378a;
*((unsigned int *)((unsigned long)context_ptr+0x00006ac8+4*9))=0xc2f39a5e;
*((unsigned int *)((unsigned long)context_ptr+0x00006ac8+4*10))=0xc89b926c;
*((unsigned int *)((unsigned long)context_ptr+0x00006ac8+4*11))=0x76b443d6;
*((unsigned int *)((unsigned long)context_ptr+0x00006ac8+4*12))=0x000de5b5;
*((unsigned int *)((unsigned long)context_ptr+0x00006ac8+4*13))=0x62601678;
*((unsigned int *)((unsigned long)context_ptr+0x00006ac8+4*14))=0x7119073a;
*((unsigned int *)((unsigned long)context_ptr+0x00006ac8+4*15))=0xd2980157;
*((unsigned int *)((unsigned long)context_ptr+0x00006ac8+4*16))=0x83b7ff74;
*((unsigned int *)((unsigned long)context_ptr+0x00006ac8+4*17))=0xa25593d6;
*((unsigned int *)((unsigned long)context_ptr+0x00006ac8+4*18))=0xc13d8a8a;
*((unsigned int *)((unsigned long)context_ptr+0x00006ac8+4*19))=0xda565abd;
*((unsigned int *)((unsigned long)context_ptr+0x00006ac8+4*20))=0x91636532;
*((unsigned int *)((unsigned long)context_ptr+0x00006ac8+4*21))=0xa964e91b;
*((unsigned int *)((unsigned long)context_ptr+0x00006ac8+4*22))=0xb413d8e0;
*((unsigned int *)((unsigned long)context_ptr+0x00006ac8+4*23))=0xf73457d8;
*((unsigned int *)((unsigned long)context_ptr+0x00006ac8+4*24))=0x5281f84c;
*((unsigned int *)((unsigned long)context_ptr+0x00006ac8+4*25))=0x0256a674;
*((unsigned int *)((unsigned long)context_ptr+0x00006ac8+4*26))=0x7e6665f5;
*((unsigned int *)((unsigned long)context_ptr+0x00006ac8+4*27))=0x9778c863;
*((unsigned int *)((unsigned long)context_ptr+0x00006ac8+4*28))=0xd7c827a0;
*((unsigned int *)((unsigned long)context_ptr+0x00006ac8+4*29))=0xffb56e2a;
*((unsigned int *)((unsigned long)context_ptr+0x00006ac8+4*30))=0x00c1e5a2;
*((unsigned int *)((unsigned long)context_ptr+0x00003b70))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003b70+4*1))=0x000062b4;
*((unsigned int *)((unsigned long)context_ptr+0x00003b70+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003b70+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003b70+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003b70+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000b70))=0x04c0007b;
*((unsigned int *)((unsigned long)context_ptr+0x00000b70+4*1))=0x00006ac8;
*((unsigned int *)((unsigned long)context_ptr+0x00000b70+4*2))=0x00006068;
*((unsigned int *)((unsigned long)context_ptr+0x00000b70+4*3))=0x0222007b;
*((unsigned int *)((unsigned long)context_ptr+0x00000b70+4*4))=0x042d7779;
*((unsigned int *)((unsigned long)context_ptr+0x00000b70+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000028e&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006300,"\xf4\xcc\x57\x21\xeb\xb2\x07\x9b\x01\xa7\x3e\x05\x54\x79\xab\xe2\x56\xdb\xc4\x36\xc1\xa2\x5d\x4a\x4a\x21\x03\x25",28))
printf("strip: f4cc5721ebb2079b, Pass\n");
else
printf("strip: f4cc5721ebb2079b, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006094))=0x026a1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006094+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006094+4*2))=0x0202007c;
*((unsigned int *)((unsigned long)context_ptr+0x00006094+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x0000695c))=0xe14c79cc;
*((unsigned int *)((unsigned long)context_ptr+0x0000695c+4*1))=0x6beca2db;
*((unsigned int *)((unsigned long)context_ptr+0x0000695c+4*2))=0xbbeb6a95;
*((unsigned int *)((unsigned long)context_ptr+0x0000695c+4*3))=0x82e51889;
*((unsigned int *)((unsigned long)context_ptr+0x0000695c+4*4))=0x7482b456;
*((unsigned int *)((unsigned long)context_ptr+0x0000695c+4*5))=0x82ad08b7;
*((unsigned int *)((unsigned long)context_ptr+0x0000695c+4*6))=0x03d4f0bf;
*((unsigned int *)((unsigned long)context_ptr+0x0000695c+4*7))=0xef505a73;
*((unsigned int *)((unsigned long)context_ptr+0x0000695c+4*8))=0x1d0996bf;
*((unsigned int *)((unsigned long)context_ptr+0x0000695c+4*9))=0x78e2e66e;
*((unsigned int *)((unsigned long)context_ptr+0x0000695c+4*10))=0x0abe7e29;
*((unsigned int *)((unsigned long)context_ptr+0x0000695c+4*11))=0xf2a7c670;
*((unsigned int *)((unsigned long)context_ptr+0x0000695c+4*12))=0x26bab66b;
*((unsigned int *)((unsigned long)context_ptr+0x0000695c+4*13))=0x00958d60;
*((unsigned int *)((unsigned long)context_ptr+0x0000695c+4*14))=0x53f989a7;
*((unsigned int *)((unsigned long)context_ptr+0x0000695c+4*15))=0x2979864e;
*((unsigned int *)((unsigned long)context_ptr+0x0000695c+4*16))=0x95861a7c;
*((unsigned int *)((unsigned long)context_ptr+0x0000695c+4*17))=0x30e86ac6;
*((unsigned int *)((unsigned long)context_ptr+0x0000695c+4*18))=0x044091be;
*((unsigned int *)((unsigned long)context_ptr+0x0000695c+4*19))=0xad7d132a;
*((unsigned int *)((unsigned long)context_ptr+0x0000695c+4*20))=0xafb4a67e;
*((unsigned int *)((unsigned long)context_ptr+0x0000695c+4*21))=0x20d8c607;
*((unsigned int *)((unsigned long)context_ptr+0x0000695c+4*22))=0x0a23a72d;
*((unsigned int *)((unsigned long)context_ptr+0x0000695c+4*23))=0xa644a2ed;
*((unsigned int *)((unsigned long)context_ptr+0x0000695c+4*24))=0xef1b6265;
*((unsigned int *)((unsigned long)context_ptr+0x0000695c+4*25))=0xa5ebb370;
*((unsigned int *)((unsigned long)context_ptr+0x0000695c+4*26))=0x5317a6b4;
*((unsigned int *)((unsigned long)context_ptr+0x0000695c+4*27))=0x5f4051e3;
*((unsigned int *)((unsigned long)context_ptr+0x0000695c+4*28))=0x9ad96a17;
*((unsigned int *)((unsigned long)context_ptr+0x0000695c+4*29))=0x4e9a7f86;
*((unsigned int *)((unsigned long)context_ptr+0x0000695c+4*30))=0x368a99ce;
*((unsigned int *)((unsigned long)context_ptr+0x00003b88))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003b88+4*1))=0x000062d0;
*((unsigned int *)((unsigned long)context_ptr+0x00003b88+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003b88+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003b88+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003b88+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000b88))=0x04c0007c;
*((unsigned int *)((unsigned long)context_ptr+0x00000b88+4*1))=0x0000695c;
*((unsigned int *)((unsigned long)context_ptr+0x00000b88+4*2))=0x00006094;
*((unsigned int *)((unsigned long)context_ptr+0x00000b88+4*3))=0x0222007c;
*((unsigned int *)((unsigned long)context_ptr+0x00000b88+4*4))=0x06250239;
*((unsigned int *)((unsigned long)context_ptr+0x00000b88+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000294&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x0000663c,"\xa2\xf5\x13\x3c\xf4\xa6\x65\x59\xc1\x4f\x95\x68\x57\xfe\x55\xda\x3d\x7a\x1e\xfb\x75\xba\xe0\xb4\x68\xf8\xd7\x63",28))
printf("strip: a2f5133cf4a66559, Pass\n");
else
printf("strip: a2f5133cf4a66559, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x000062ec))=0x026a1002;
*((unsigned int *)((unsigned long)context_ptr+0x000062ec+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000062ec+4*2))=0x0202007d;
*((unsigned int *)((unsigned long)context_ptr+0x000062ec+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x000065b8))=0x14120b62;
*((unsigned int *)((unsigned long)context_ptr+0x000065b8+4*1))=0x10423c4f;
*((unsigned int *)((unsigned long)context_ptr+0x000065b8+4*2))=0x3013fe65;
*((unsigned int *)((unsigned long)context_ptr+0x000065b8+4*3))=0xecaa9227;
*((unsigned int *)((unsigned long)context_ptr+0x000065b8+4*4))=0x423ec346;
*((unsigned int *)((unsigned long)context_ptr+0x000065b8+4*5))=0x9445d50c;
*((unsigned int *)((unsigned long)context_ptr+0x000065b8+4*6))=0x44eb8718;
*((unsigned int *)((unsigned long)context_ptr+0x000065b8+4*7))=0x55542f99;
*((unsigned int *)((unsigned long)context_ptr+0x000065b8+4*8))=0x18726746;
*((unsigned int *)((unsigned long)context_ptr+0x000065b8+4*9))=0xb5922d81;
*((unsigned int *)((unsigned long)context_ptr+0x000065b8+4*10))=0x11eace5b;
*((unsigned int *)((unsigned long)context_ptr+0x000065b8+4*11))=0x0847d670;
*((unsigned int *)((unsigned long)context_ptr+0x000065b8+4*12))=0xdc1aef74;
*((unsigned int *)((unsigned long)context_ptr+0x000065b8+4*13))=0xd92f8280;
*((unsigned int *)((unsigned long)context_ptr+0x000065b8+4*14))=0xf592d3c5;
*((unsigned int *)((unsigned long)context_ptr+0x000065b8+4*15))=0xdb642eaa;
*((unsigned int *)((unsigned long)context_ptr+0x000065b8+4*16))=0x205098b4;
*((unsigned int *)((unsigned long)context_ptr+0x000065b8+4*17))=0x72e844ec;
*((unsigned int *)((unsigned long)context_ptr+0x000065b8+4*18))=0xa0211cb3;
*((unsigned int *)((unsigned long)context_ptr+0x000065b8+4*19))=0x50a89e7f;
*((unsigned int *)((unsigned long)context_ptr+0x000065b8+4*20))=0x25df0985;
*((unsigned int *)((unsigned long)context_ptr+0x000065b8+4*21))=0xda03232f;
*((unsigned int *)((unsigned long)context_ptr+0x000065b8+4*22))=0xa64f44c4;
*((unsigned int *)((unsigned long)context_ptr+0x000065b8+4*23))=0xcfd428b3;
*((unsigned int *)((unsigned long)context_ptr+0x000065b8+4*24))=0x190c08ab;
*((unsigned int *)((unsigned long)context_ptr+0x000065b8+4*25))=0x6745a0b2;
*((unsigned int *)((unsigned long)context_ptr+0x000065b8+4*26))=0xa7b34233;
*((unsigned int *)((unsigned long)context_ptr+0x000065b8+4*27))=0xf3e32929;
*((unsigned int *)((unsigned long)context_ptr+0x000065b8+4*28))=0x2c561053;
*((unsigned int *)((unsigned long)context_ptr+0x000065b8+4*29))=0x14f97551;
*((unsigned int *)((unsigned long)context_ptr+0x000065b8+4*30))=0xf77e390a;
*((unsigned int *)((unsigned long)context_ptr+0x000065b8+4*31))=0x0000003a;
*((unsigned int *)((unsigned long)context_ptr+0x00003ba0))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003ba0+4*1))=0x000062fc;
*((unsigned int *)((unsigned long)context_ptr+0x00003ba0+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003ba0+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003ba0+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003ba0+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000ba0))=0x04c0007d;
*((unsigned int *)((unsigned long)context_ptr+0x00000ba0+4*1))=0x000065b8;
*((unsigned int *)((unsigned long)context_ptr+0x00000ba0+4*2))=0x000062ec;
*((unsigned int *)((unsigned long)context_ptr+0x00000ba0+4*3))=0x0222007d;
*((unsigned int *)((unsigned long)context_ptr+0x00000ba0+4*4))=0x0eeaa4f8;
*((unsigned int *)((unsigned long)context_ptr+0x00000ba0+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000029a&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000068b0,"\x21\xd2\x95\x30\x8d\xb6\x3b\x8a\x06\xf6\x28\x1c\x15\x28\x7c\xed\xe0\xb5\x1a\x50\x4b\xfd\x91\x3f\x4c\xf3\x96\x94",28))
printf("strip: 21d295308db63b8a, Pass\n");
else
printf("strip: 21d295308db63b8a, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006638))=0x026a1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006638+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006638+4*2))=0x0202007e;
*((unsigned int *)((unsigned long)context_ptr+0x00006638+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x00006420))=0xdff789b4;
*((unsigned int *)((unsigned long)context_ptr+0x00006420+4*1))=0xd2e01261;
*((unsigned int *)((unsigned long)context_ptr+0x00006420+4*2))=0x65121a6b;
*((unsigned int *)((unsigned long)context_ptr+0x00006420+4*3))=0x644dc04f;
*((unsigned int *)((unsigned long)context_ptr+0x00006420+4*4))=0x38fb7cb4;
*((unsigned int *)((unsigned long)context_ptr+0x00006420+4*5))=0x092145b9;
*((unsigned int *)((unsigned long)context_ptr+0x00006420+4*6))=0xefe82262;
*((unsigned int *)((unsigned long)context_ptr+0x00006420+4*7))=0x58856b96;
*((unsigned int *)((unsigned long)context_ptr+0x00006420+4*8))=0x2dd59280;
*((unsigned int *)((unsigned long)context_ptr+0x00006420+4*9))=0x46e668e2;
*((unsigned int *)((unsigned long)context_ptr+0x00006420+4*10))=0x20c42aaf;
*((unsigned int *)((unsigned long)context_ptr+0x00006420+4*11))=0x89fa3469;
*((unsigned int *)((unsigned long)context_ptr+0x00006420+4*12))=0x44186a2c;
*((unsigned int *)((unsigned long)context_ptr+0x00006420+4*13))=0x81dae11f;
*((unsigned int *)((unsigned long)context_ptr+0x00006420+4*14))=0x330330b1;
*((unsigned int *)((unsigned long)context_ptr+0x00006420+4*15))=0x2743a16a;
*((unsigned int *)((unsigned long)context_ptr+0x00006420+4*16))=0xcda658ad;
*((unsigned int *)((unsigned long)context_ptr+0x00006420+4*17))=0x39cb5444;
*((unsigned int *)((unsigned long)context_ptr+0x00006420+4*18))=0x81da213f;
*((unsigned int *)((unsigned long)context_ptr+0x00006420+4*19))=0x4239d3c3;
*((unsigned int *)((unsigned long)context_ptr+0x00006420+4*20))=0xf4549957;
*((unsigned int *)((unsigned long)context_ptr+0x00006420+4*21))=0x55fe0b62;
*((unsigned int *)((unsigned long)context_ptr+0x00006420+4*22))=0x7b4b11a1;
*((unsigned int *)((unsigned long)context_ptr+0x00006420+4*23))=0xebde59c0;
*((unsigned int *)((unsigned long)context_ptr+0x00006420+4*24))=0x4d9394dd;
*((unsigned int *)((unsigned long)context_ptr+0x00006420+4*25))=0xb657071d;
*((unsigned int *)((unsigned long)context_ptr+0x00006420+4*26))=0x63ed7886;
*((unsigned int *)((unsigned long)context_ptr+0x00006420+4*27))=0x3663418a;
*((unsigned int *)((unsigned long)context_ptr+0x00006420+4*28))=0x416cb2b4;
*((unsigned int *)((unsigned long)context_ptr+0x00006420+4*29))=0x8654e74a;
*((unsigned int *)((unsigned long)context_ptr+0x00006420+4*30))=0x7655878b;
*((unsigned int *)((unsigned long)context_ptr+0x00006420+4*31))=0x00003256;
*((unsigned int *)((unsigned long)context_ptr+0x00003bb8))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003bb8+4*1))=0x000066e4;
*((unsigned int *)((unsigned long)context_ptr+0x00003bb8+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003bb8+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003bb8+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003bb8+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000bb8))=0x04c0007e;
*((unsigned int *)((unsigned long)context_ptr+0x00000bb8+4*1))=0x00006420;
*((unsigned int *)((unsigned long)context_ptr+0x00000bb8+4*2))=0x00006638;
*((unsigned int *)((unsigned long)context_ptr+0x00000bb8+4*3))=0x0222007e;
*((unsigned int *)((unsigned long)context_ptr+0x00000bb8+4*4))=0x0cbec388;
*((unsigned int *)((unsigned long)context_ptr+0x00000bb8+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000002a0&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x0000638c,"\x67\xdc\x83\x64\x65\xc6\xa6\x18\xa6\x50\xa1\xbc\x00\x65\x55\xb2\xba\x03\xcb\x13\xe2\x1b\x45\xef\xcc\x3e\x2f\x65",28))
printf("strip: 67dc836465c6a618, Pass\n");
else
printf("strip: 67dc836465c6a618, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006648))=0x026a1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006648+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006648+4*2))=0x0202007f;
*((unsigned int *)((unsigned long)context_ptr+0x00006648+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x00006844))=0x335667ec;
*((unsigned int *)((unsigned long)context_ptr+0x00006844+4*1))=0x02998124;
*((unsigned int *)((unsigned long)context_ptr+0x00006844+4*2))=0xd3293760;
*((unsigned int *)((unsigned long)context_ptr+0x00006844+4*3))=0x9c8e65b3;
*((unsigned int *)((unsigned long)context_ptr+0x00006844+4*4))=0x8c439665;
*((unsigned int *)((unsigned long)context_ptr+0x00006844+4*5))=0x75941bb5;
*((unsigned int *)((unsigned long)context_ptr+0x00006844+4*6))=0xa2d3360b;
*((unsigned int *)((unsigned long)context_ptr+0x00006844+4*7))=0x3853cfa5;
*((unsigned int *)((unsigned long)context_ptr+0x00006844+4*8))=0x342b6bb5;
*((unsigned int *)((unsigned long)context_ptr+0x00006844+4*9))=0x191d3042;
*((unsigned int *)((unsigned long)context_ptr+0x00006844+4*10))=0xda4e75d9;
*((unsigned int *)((unsigned long)context_ptr+0x00006844+4*11))=0x7df11a5c;
*((unsigned int *)((unsigned long)context_ptr+0x00006844+4*12))=0xcecb1250;
*((unsigned int *)((unsigned long)context_ptr+0x00006844+4*13))=0x5677f1fb;
*((unsigned int *)((unsigned long)context_ptr+0x00006844+4*14))=0x602fbb5a;
*((unsigned int *)((unsigned long)context_ptr+0x00006844+4*15))=0x2bce391f;
*((unsigned int *)((unsigned long)context_ptr+0x00006844+4*16))=0x289b7a6c;
*((unsigned int *)((unsigned long)context_ptr+0x00006844+4*17))=0x91b3faaa;
*((unsigned int *)((unsigned long)context_ptr+0x00006844+4*18))=0xdaeb1083;
*((unsigned int *)((unsigned long)context_ptr+0x00006844+4*19))=0xa2ce2d06;
*((unsigned int *)((unsigned long)context_ptr+0x00006844+4*20))=0xd4a67cf2;
*((unsigned int *)((unsigned long)context_ptr+0x00006844+4*21))=0x9d303d97;
*((unsigned int *)((unsigned long)context_ptr+0x00006844+4*22))=0x5f42afcc;
*((unsigned int *)((unsigned long)context_ptr+0x00006844+4*23))=0x3a01a087;
*((unsigned int *)((unsigned long)context_ptr+0x00006844+4*24))=0xcdf2c3a7;
*((unsigned int *)((unsigned long)context_ptr+0x00006844+4*25))=0x1e963bf4;
*((unsigned int *)((unsigned long)context_ptr+0x00006844+4*26))=0xbcb03e9b;
*((unsigned int *)((unsigned long)context_ptr+0x00006844+4*27))=0x186e0b7c;
*((unsigned int *)((unsigned long)context_ptr+0x00006844+4*28))=0x23ebd68c;
*((unsigned int *)((unsigned long)context_ptr+0x00006844+4*29))=0x9bdf3294;
*((unsigned int *)((unsigned long)context_ptr+0x00006844+4*30))=0x9043c615;
*((unsigned int *)((unsigned long)context_ptr+0x00006844+4*31))=0x00b5de58;
*((unsigned int *)((unsigned long)context_ptr+0x00003bd0))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003bd0+4*1))=0x00006700;
*((unsigned int *)((unsigned long)context_ptr+0x00003bd0+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003bd0+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003bd0+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003bd0+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000bd0))=0x04c0007f;
*((unsigned int *)((unsigned long)context_ptr+0x00000bd0+4*1))=0x00006844;
*((unsigned int *)((unsigned long)context_ptr+0x00000bd0+4*2))=0x00006648;
*((unsigned int *)((unsigned long)context_ptr+0x00000bd0+4*3))=0x0222007f;
*((unsigned int *)((unsigned long)context_ptr+0x00000bd0+4*4))=0x033f683e;
*((unsigned int *)((unsigned long)context_ptr+0x00000bd0+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000002a6&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000063a8,"\x6e\x38\x97\xcf\xe4\xcc\x19\xd1\x2a\x92\xed\xfe\x34\x97\x02\x81\x41\x35\x6b\x8c\x7d\x60\xac\xa4\x07\x08\x6b\xe4",28))
printf("strip: 6e3897cfe4cc19d1, Pass\n");
else
printf("strip: 6e3897cfe4cc19d1, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006658))=0x026a1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006658+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006658+4*2))=0x02020080;
*((unsigned int *)((unsigned long)context_ptr+0x00006658+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x00006318))=0x0eded7a4;
*((unsigned int *)((unsigned long)context_ptr+0x00006318+4*1))=0xecf7be6e;
*((unsigned int *)((unsigned long)context_ptr+0x00006318+4*2))=0xa0bd9905;
*((unsigned int *)((unsigned long)context_ptr+0x00006318+4*3))=0xbcad0e9d;
*((unsigned int *)((unsigned long)context_ptr+0x00006318+4*4))=0x7960c646;
*((unsigned int *)((unsigned long)context_ptr+0x00006318+4*5))=0x941aa03b;
*((unsigned int *)((unsigned long)context_ptr+0x00006318+4*6))=0x8a933b55;
*((unsigned int *)((unsigned long)context_ptr+0x00006318+4*7))=0xdab77b3b;
*((unsigned int *)((unsigned long)context_ptr+0x00006318+4*8))=0x506f0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006318+4*9))=0xf3d95ae6;
*((unsigned int *)((unsigned long)context_ptr+0x00006318+4*10))=0x192d4ce4;
*((unsigned int *)((unsigned long)context_ptr+0x00006318+4*11))=0x408be758;
*((unsigned int *)((unsigned long)context_ptr+0x00006318+4*12))=0xea550bbe;
*((unsigned int *)((unsigned long)context_ptr+0x00006318+4*13))=0x94a1c243;
*((unsigned int *)((unsigned long)context_ptr+0x00006318+4*14))=0x575195c8;
*((unsigned int *)((unsigned long)context_ptr+0x00006318+4*15))=0x3607c31e;
*((unsigned int *)((unsigned long)context_ptr+0x00006318+4*16))=0x95eba041;
*((unsigned int *)((unsigned long)context_ptr+0x00006318+4*17))=0x6ed1e808;
*((unsigned int *)((unsigned long)context_ptr+0x00006318+4*18))=0x957ff50d;
*((unsigned int *)((unsigned long)context_ptr+0x00006318+4*19))=0x2008dcab;
*((unsigned int *)((unsigned long)context_ptr+0x00006318+4*20))=0x9e9eb4d2;
*((unsigned int *)((unsigned long)context_ptr+0x00006318+4*21))=0xfe253220;
*((unsigned int *)((unsigned long)context_ptr+0x00006318+4*22))=0x4a08f450;
*((unsigned int *)((unsigned long)context_ptr+0x00006318+4*23))=0x65546477;
*((unsigned int *)((unsigned long)context_ptr+0x00006318+4*24))=0xc33ed15c;
*((unsigned int *)((unsigned long)context_ptr+0x00006318+4*25))=0x144413db;
*((unsigned int *)((unsigned long)context_ptr+0x00006318+4*26))=0x966a079f;
*((unsigned int *)((unsigned long)context_ptr+0x00006318+4*27))=0x3eb1dd03;
*((unsigned int *)((unsigned long)context_ptr+0x00006318+4*28))=0xf05a1a4f;
*((unsigned int *)((unsigned long)context_ptr+0x00006318+4*29))=0xf8af3cc5;
*((unsigned int *)((unsigned long)context_ptr+0x00006318+4*30))=0xc0891f10;
*((unsigned int *)((unsigned long)context_ptr+0x00006318+4*31))=0x9346f320;
*((unsigned int *)((unsigned long)context_ptr+0x00003be8))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003be8+4*1))=0x0000671c;
*((unsigned int *)((unsigned long)context_ptr+0x00003be8+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003be8+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003be8+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003be8+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000be8))=0x04c00080;
*((unsigned int *)((unsigned long)context_ptr+0x00000be8+4*1))=0x00006318;
*((unsigned int *)((unsigned long)context_ptr+0x00000be8+4*2))=0x00006658;
*((unsigned int *)((unsigned long)context_ptr+0x00000be8+4*3))=0x02220080;
*((unsigned int *)((unsigned long)context_ptr+0x00000be8+4*4))=0x0878e8a4;
*((unsigned int *)((unsigned long)context_ptr+0x00000be8+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000002ac&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000064a8,"\x72\x06\x16\xab\xa3\x29\xe7\xf1\x82\x7f\xc4\x7f\xe3\x6d\xab\x2d\x7b\x96\x12\xce\x6a\x0e\x82\xbd\x59\x8b\x0e\x88",28))
printf("strip: 720616aba329e7f1, Pass\n");
else
printf("strip: 720616aba329e7f1, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x0000652c))=0x026a1002;
*((unsigned int *)((unsigned long)context_ptr+0x0000652c+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x0000652c+4*2))=0x02020081;
*((unsigned int *)((unsigned long)context_ptr+0x0000652c+4*3))=0x21e6001c;
*((unsigned int *)((unsigned long)context_ptr+0x000060a4))=0x7625bd31;
*((unsigned int *)((unsigned long)context_ptr+0x000060a4+4*1))=0x446729f1;
*((unsigned int *)((unsigned long)context_ptr+0x000060a4+4*2))=0x82d8bbaf;
*((unsigned int *)((unsigned long)context_ptr+0x000060a4+4*3))=0x56f861cf;
*((unsigned int *)((unsigned long)context_ptr+0x000060a4+4*4))=0x57900310;
*((unsigned int *)((unsigned long)context_ptr+0x000060a4+4*5))=0x5c937160;
*((unsigned int *)((unsigned long)context_ptr+0x000060a4+4*6))=0x0ed1407a;
*((unsigned int *)((unsigned long)context_ptr+0x000060a4+4*7))=0x492d7fe1;
*((unsigned int *)((unsigned long)context_ptr+0x000060a4+4*8))=0x9ef726a6;
*((unsigned int *)((unsigned long)context_ptr+0x000060a4+4*9))=0x1fe1e4dd;
*((unsigned int *)((unsigned long)context_ptr+0x000060a4+4*10))=0x52b7dca0;
*((unsigned int *)((unsigned long)context_ptr+0x000060a4+4*11))=0xeb9a019b;
*((unsigned int *)((unsigned long)context_ptr+0x000060a4+4*12))=0x820fc664;
*((unsigned int *)((unsigned long)context_ptr+0x000060a4+4*13))=0x21351906;
*((unsigned int *)((unsigned long)context_ptr+0x000060a4+4*14))=0x16b60c08;
*((unsigned int *)((unsigned long)context_ptr+0x000060a4+4*15))=0x287938a4;
*((unsigned int *)((unsigned long)context_ptr+0x000060a4+4*16))=0x276f4bb7;
*((unsigned int *)((unsigned long)context_ptr+0x000060a4+4*17))=0x0d008b05;
*((unsigned int *)((unsigned long)context_ptr+0x000060a4+4*18))=0x788cff42;
*((unsigned int *)((unsigned long)context_ptr+0x000060a4+4*19))=0xb1749929;
*((unsigned int *)((unsigned long)context_ptr+0x000060a4+4*20))=0x07772a98;
*((unsigned int *)((unsigned long)context_ptr+0x000060a4+4*21))=0x9ec21ca3;
*((unsigned int *)((unsigned long)context_ptr+0x000060a4+4*22))=0x30c0f24b;
*((unsigned int *)((unsigned long)context_ptr+0x000060a4+4*23))=0x2c43cc47;
*((unsigned int *)((unsigned long)context_ptr+0x000060a4+4*24))=0x2e383343;
*((unsigned int *)((unsigned long)context_ptr+0x000060a4+4*25))=0x5574f32f;
*((unsigned int *)((unsigned long)context_ptr+0x000060a4+4*26))=0x973bce8d;
*((unsigned int *)((unsigned long)context_ptr+0x000060a4+4*27))=0x99836fd6;
*((unsigned int *)((unsigned long)context_ptr+0x000060a4+4*28))=0x9ecd5742;
*((unsigned int *)((unsigned long)context_ptr+0x000060a4+4*29))=0x9d4e3ead;
*((unsigned int *)((unsigned long)context_ptr+0x000060a4+4*30))=0x1eefe430;
*((unsigned int *)((unsigned long)context_ptr+0x000060a4+4*31))=0x194f6306;
*((unsigned int *)((unsigned long)context_ptr+0x000060a4+4*32))=0x000000c7;
*((unsigned int *)((unsigned long)context_ptr+0x00003c00))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00003c00+4*1))=0x000064a0;
*((unsigned int *)((unsigned long)context_ptr+0x00003c00+4*2))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003c00+4*3))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003c00+4*4))=0x77777777;
*((unsigned int *)((unsigned long)context_ptr+0x00003c00+4*5))=0x77777777;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x000005fa&0xffffffff,ivp_cae_base_addr+0x00000028);
while(1){
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)context_ptr+0x00000c00))=0x04c00081;
*((unsigned int *)((unsigned long)context_ptr+0x00000c00+4*1))=0x000060a4;
*((unsigned int *)((unsigned long)context_ptr+0x00000c00+4*2))=0x0000652c;
*((unsigned int *)((unsigned long)context_ptr+0x00000c00+4*3))=0x02220081;
*((unsigned int *)((unsigned long)context_ptr+0x00000c00+4*4))=0x0ebacbfc;
*((unsigned int *)((unsigned long)context_ptr+0x00000c00+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x000002b2&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000064c4,"\x2f\x1c\x9f\x16\x7a\xd8\x9a\x7a\xf0\x49\xab\x34\x8e\xdf\xa1\x94\xce\x15\x71\x7c\xef\xff\x81\xc1\x99\x0d\xda\x37",28))
printf("strip: 2f1c9f167ad89a7a, Pass\n");
else
printf("strip: 2f1c9f167ad89a7a, Failed\n");
writel(0x000002b8&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006940,"\x73\x18\xd5\x1b\x22\x46\x8f\x9a\x38\x70\xc6\x91\x87\xc1\x2f\xa8\x99\x3f\x8c\x39\x5a\x32\xb8\x78\xc8\xca\x83\x7f",28))
printf("strip: 7318d51b22468f9a, Pass\n");
else
printf("strip: 7318d51b22468f9a, Failed\n");
writel(0x000002be&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000064f0,"\xb2\x63\xa1\x31\x19\xbc\x4b\xcb\x65\x6d\x26\x0f\xf6\x95\x12\xc6\x48\xb5\xf0\x48\x58\x60\x8f\x2a\x51\x89\x58\x40",28))
printf("strip: b263a13119bc4bcb, Pass\n");
else
printf("strip: b263a13119bc4bcb, Failed\n");
writel(0x000002c4&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000063f4,"\x55\x31\x74\xdc\x56\xbd\x66\x28\x96\xae\x29\x61\x5f\x72\x62\x8f\x87\x66\x84\xc6\x06\x5b\xfd\x0d\xf8\x53\xce\xb5",28))
printf("strip: 553174dc56bd6628, Pass\n");
else
printf("strip: 553174dc56bd6628, Failed\n");
writel(0x000002ca&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006828,"\x09\x8d\xb0\x29\xce\xad\x29\x60\xc0\xd1\xa7\x87\x6f\x5b\xf1\x53\xd6\x30\xae\x16\x73\x03\xbc\xe8\x3c\x91\x32\x65",28))
printf("strip: 098db029cead2960, Pass\n");
else
printf("strip: 098db029cead2960, Failed\n");
writel(0x000002d0&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006200,"\xfc\xa0\xcc\x09\xfe\xf5\x1f\xb7\x15\x47\xf6\x4e\x6d\x5e\x4d\x14\xe4\x99\xc9\x19\x79\x54\x92\xc5\xc6\xed\xc5\xb1",28))
printf("strip: fca0cc09fef51fb7, Pass\n");
else
printf("strip: fca0cc09fef51fb7, Failed\n");
writel(0x000002d6&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x0000621c,"\x6f\x42\xfe\x9b\x7a\x43\x89\x19\xbf\x0e\xd5\x12\x4d\x6b\x12\x9a\xfb\x4b\x2b\x23\x6a\x6a\xee\xf3\x70\xa9\x4a\xfb",28))
printf("strip: 6f42fe9b7a438919, Pass\n");
else
printf("strip: 6f42fe9b7a438919, Failed\n");
writel(0x000002dc&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006078,"\xb0\x2f\x41\xc3\xd0\x5e\x07\xd7\x31\x7f\x3f\xeb\x4e\x28\x1d\x9a\x78\x1c\x62\x7c\x8d\x61\xef\xa8\x4d\xcb\x3e\xdf",28))
printf("strip: b02f41c3d05e07d7, Pass\n");
else
printf("strip: b02f41c3d05e07d7, Failed\n");
writel(0x000002e2&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000062b4,"\xb0\x06\x2b\xf6\x30\x15\xfe\xca\x19\x9b\x8f\xce\x66\x84\xa5\x10\x3f\xd6\xef\x23\xc8\xa2\x12\x74\xc8\xa8\x9a\xa7",28))
printf("strip: b0062bf63015feca, Pass\n");
else
printf("strip: b0062bf63015feca, Failed\n");
writel(0x000002e8&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000062d0,"\x02\xf4\xf7\x16\xfb\x61\x25\xf8\x19\xcb\xc7\xbd\x18\xec\x8f\x4e\xdf\x9e\x39\xb7\xbf\x18\x1d\xa5\x7d\xfb\x36\x78",28))
printf("strip: 02f4f716fb6125f8, Pass\n");
else
printf("strip: 02f4f716fb6125f8, Failed\n");
writel(0x000002ee&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000062fc,"\x24\xf8\x5b\x82\xed\xad\x51\x02\xcc\x5b\xbf\xb6\x47\x6d\x06\x19\x77\x18\x13\x0c\xb3\x8c\x06\x82\xc2\x9b\x54\x0e",28))
printf("strip: 24f85b82edad5102, Pass\n");
else
printf("strip: 24f85b82edad5102, Failed\n");
writel(0x000002f4&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000066e4,"\x2c\xcd\x81\x88\xbf\xa0\xfd\x07\xd9\x75\xf4\x92\x39\x23\x08\x90\x2a\xfa\x44\x1c\xb0\xab\xa8\xa5\x58\x1e\xe5\x13",28))
printf("strip: 2ccd8188bfa0fd07, Pass\n");
else
printf("strip: 2ccd8188bfa0fd07, Failed\n");
writel(0x000002fa&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006700,"\xbc\x9e\x45\x76\xd0\xbe\xf7\xa7\x8d\x28\x86\xf3\x32\x05\x32\xd0\xf9\x2a\x2d\x5d\x9a\x69\x5f\x1f\xb0\x4e\x67\x57",28))
printf("strip: bc9e4576d0bef7a7, Pass\n");
else
printf("strip: bc9e4576d0bef7a7, Failed\n");
writel(0x00000300&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
writel(0x00000c00&0xffffffff,ivp_cae_base_addr+0x00000830);
if(!memcmp((unsigned char *)context_ptr+0x0000671c,"\x66\x1b\x06\x56\x05\x00\xe8\x18\xb1\xcc\x5b\x26\xe4\x96\x2e\xd7\xb9\x73\xbc\xed\x2f\x2c\xbc\xeb\x50\x04\x49\x96",28))
printf("strip: 661b06560500e818, Pass\n");
else
printf("strip: 661b06560500e818, Failed\n");
writel(0x00000006&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000064a0,"\xb4\xb0\x6c\xcc\xfa\xeb\x52\x97\xf2\x36\xe0\x58\xd9\xc2\x04\x9d\x6a\xd5\x59\xf2\x23\xe7\x05\x75\x63\xf7\xee\x46",28))
printf("strip: b4b06cccfaeb5297, Pass\n");
else
printf("strip: b4b06cccfaeb5297, Failed\n");
}

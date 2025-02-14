#include <common.h>
#include <malloc.h>

extern volatile unsigned int ivp_cae_base_addr;

void test_md5_rfc(void)
{
unsigned int *context_ptr=(unsigned int *)0x14000000;
printf("test_md5_rfc\n");
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
*((unsigned int *)((unsigned long)context_ptr+0x00006000))=0x000a0002;
*((unsigned int *)((unsigned long)context_ptr+0x00006000+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006008))=0x000a0002;
*((unsigned int *)((unsigned long)context_ptr+0x00006008+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006010))=0x000a0002;
*((unsigned int *)((unsigned long)context_ptr+0x00006010+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006018))=0x000a0002;
*((unsigned int *)((unsigned long)context_ptr+0x00006018+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006020))=0x000a0002;
*((unsigned int *)((unsigned long)context_ptr+0x00006020+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006028))=0x000a0002;
*((unsigned int *)((unsigned long)context_ptr+0x00006028+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006030))=0x000a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006030+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006030+4*2))=0x02020001;
*((unsigned int *)((unsigned long)context_ptr+0x00006030+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x00006040))=0x00000061;
*((unsigned int *)((unsigned long)context_ptr+0x00003000))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003000+4*1))=0x00006044;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000000+4*1))=0x00006040;
*((unsigned int *)((unsigned long)context_ptr+0x00000000+4*2))=0x00006030;
*((unsigned int *)((unsigned long)context_ptr+0x00000000+4*3))=0x02220001;
*((unsigned int *)((unsigned long)context_ptr+0x00000000+4*4))=0x0024e861;
*((unsigned int *)((unsigned long)context_ptr+0x00000000+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x00006054))=0x000a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006054+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006054+4*2))=0x02020003;
*((unsigned int *)((unsigned long)context_ptr+0x00006054+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x00006064))=0x00636261;
*((unsigned int *)((unsigned long)context_ptr+0x00003018))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003018+4*1))=0x00006068;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000018))=0x04c00003;
*((unsigned int *)((unsigned long)context_ptr+0x00000018+4*1))=0x00006064;
*((unsigned int *)((unsigned long)context_ptr+0x00000018+4*2))=0x00006054;
*((unsigned int *)((unsigned long)context_ptr+0x00000018+4*3))=0x02220003;
*((unsigned int *)((unsigned long)context_ptr+0x00000018+4*4))=0x0e5bcd7e;
*((unsigned int *)((unsigned long)context_ptr+0x00000018+4*5))=0x00006008+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x00006078))=0x000a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006078+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006078+4*2))=0x0202000e;
*((unsigned int *)((unsigned long)context_ptr+0x00006078+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x00006088))=0x7373656d;
*((unsigned int *)((unsigned long)context_ptr+0x00006088+4*1))=0x20656761;
*((unsigned int *)((unsigned long)context_ptr+0x00006088+4*2))=0x65676964;
*((unsigned int *)((unsigned long)context_ptr+0x00006088+4*3))=0x00007473;
*((unsigned int *)((unsigned long)context_ptr+0x00003030))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003030+4*1))=0x00006098;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000030))=0x04c0000e;
*((unsigned int *)((unsigned long)context_ptr+0x00000030+4*1))=0x00006088;
*((unsigned int *)((unsigned long)context_ptr+0x00000030+4*2))=0x00006078;
*((unsigned int *)((unsigned long)context_ptr+0x00000030+4*3))=0x0222000e;
*((unsigned int *)((unsigned long)context_ptr+0x00000030+4*4))=0x0d01acef;
*((unsigned int *)((unsigned long)context_ptr+0x00000030+4*5))=0x00006010+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x000060a8))=0x000a0012;
*((unsigned int *)((unsigned long)context_ptr+0x000060a8+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000060a8+4*2))=0x0202001a;
*((unsigned int *)((unsigned long)context_ptr+0x000060a8+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x000060b8))=0x64636261;
*((unsigned int *)((unsigned long)context_ptr+0x000060b8+4*1))=0x68676665;
*((unsigned int *)((unsigned long)context_ptr+0x000060b8+4*2))=0x6c6b6a69;
*((unsigned int *)((unsigned long)context_ptr+0x000060b8+4*3))=0x706f6e6d;
*((unsigned int *)((unsigned long)context_ptr+0x000060b8+4*4))=0x74737271;
*((unsigned int *)((unsigned long)context_ptr+0x000060b8+4*5))=0x78777675;
*((unsigned int *)((unsigned long)context_ptr+0x000060b8+4*6))=0x00007a79;
*((unsigned int *)((unsigned long)context_ptr+0x00003048))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003048+4*1))=0x000060d4;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000048))=0x04c0001a;
*((unsigned int *)((unsigned long)context_ptr+0x00000048+4*1))=0x000060b8;
*((unsigned int *)((unsigned long)context_ptr+0x00000048+4*2))=0x000060a8;
*((unsigned int *)((unsigned long)context_ptr+0x00000048+4*3))=0x0222001a;
*((unsigned int *)((unsigned long)context_ptr+0x00000048+4*4))=0x0eb6b96e;
*((unsigned int *)((unsigned long)context_ptr+0x00000048+4*5))=0x00006018+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x000060e4))=0x000a0012;
*((unsigned int *)((unsigned long)context_ptr+0x000060e4+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000060e4+4*2))=0x0202003e;
*((unsigned int *)((unsigned long)context_ptr+0x000060e4+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x000060f4))=0x44434241;
*((unsigned int *)((unsigned long)context_ptr+0x000060f4+4*1))=0x48474645;
*((unsigned int *)((unsigned long)context_ptr+0x000060f4+4*2))=0x4c4b4a49;
*((unsigned int *)((unsigned long)context_ptr+0x000060f4+4*3))=0x504f4e4d;
*((unsigned int *)((unsigned long)context_ptr+0x000060f4+4*4))=0x54535251;
*((unsigned int *)((unsigned long)context_ptr+0x000060f4+4*5))=0x58575655;
*((unsigned int *)((unsigned long)context_ptr+0x000060f4+4*6))=0x62615a59;
*((unsigned int *)((unsigned long)context_ptr+0x000060f4+4*7))=0x66656463;
*((unsigned int *)((unsigned long)context_ptr+0x000060f4+4*8))=0x6a696867;
*((unsigned int *)((unsigned long)context_ptr+0x000060f4+4*9))=0x6e6d6c6b;
*((unsigned int *)((unsigned long)context_ptr+0x000060f4+4*10))=0x7271706f;
*((unsigned int *)((unsigned long)context_ptr+0x000060f4+4*11))=0x76757473;
*((unsigned int *)((unsigned long)context_ptr+0x000060f4+4*12))=0x7a797877;
*((unsigned int *)((unsigned long)context_ptr+0x000060f4+4*13))=0x33323130;
*((unsigned int *)((unsigned long)context_ptr+0x000060f4+4*14))=0x37363534;
*((unsigned int *)((unsigned long)context_ptr+0x000060f4+4*15))=0x00003938;
*((unsigned int *)((unsigned long)context_ptr+0x00003060))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003060+4*1))=0x00006134;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000060))=0x04c0003e;
*((unsigned int *)((unsigned long)context_ptr+0x00000060+4*1))=0x000060f4;
*((unsigned int *)((unsigned long)context_ptr+0x00000060+4*2))=0x000060e4;
*((unsigned int *)((unsigned long)context_ptr+0x00000060+4*3))=0x0222003e;
*((unsigned int *)((unsigned long)context_ptr+0x00000060+4*4))=0x081de97f;
*((unsigned int *)((unsigned long)context_ptr+0x00000060+4*5))=0x00006020+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x00006144))=0x000a0012;
*((unsigned int *)((unsigned long)context_ptr+0x00006144+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006144+4*2))=0x02020050;
*((unsigned int *)((unsigned long)context_ptr+0x00006144+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x00006154))=0x34333231;
*((unsigned int *)((unsigned long)context_ptr+0x00006154+4*1))=0x38373635;
*((unsigned int *)((unsigned long)context_ptr+0x00006154+4*2))=0x32313039;
*((unsigned int *)((unsigned long)context_ptr+0x00006154+4*3))=0x36353433;
*((unsigned int *)((unsigned long)context_ptr+0x00006154+4*4))=0x30393837;
*((unsigned int *)((unsigned long)context_ptr+0x00006154+4*5))=0x34333231;
*((unsigned int *)((unsigned long)context_ptr+0x00006154+4*6))=0x38373635;
*((unsigned int *)((unsigned long)context_ptr+0x00006154+4*7))=0x32313039;
*((unsigned int *)((unsigned long)context_ptr+0x00006154+4*8))=0x36353433;
*((unsigned int *)((unsigned long)context_ptr+0x00006154+4*9))=0x30393837;
*((unsigned int *)((unsigned long)context_ptr+0x00006154+4*10))=0x34333231;
*((unsigned int *)((unsigned long)context_ptr+0x00006154+4*11))=0x38373635;
*((unsigned int *)((unsigned long)context_ptr+0x00006154+4*12))=0x32313039;
*((unsigned int *)((unsigned long)context_ptr+0x00006154+4*13))=0x36353433;
*((unsigned int *)((unsigned long)context_ptr+0x00006154+4*14))=0x30393837;
*((unsigned int *)((unsigned long)context_ptr+0x00006154+4*15))=0x34333231;
*((unsigned int *)((unsigned long)context_ptr+0x00006154+4*16))=0x38373635;
*((unsigned int *)((unsigned long)context_ptr+0x00006154+4*17))=0x32313039;
*((unsigned int *)((unsigned long)context_ptr+0x00006154+4*18))=0x36353433;
*((unsigned int *)((unsigned long)context_ptr+0x00006154+4*19))=0x30393837;
*((unsigned int *)((unsigned long)context_ptr+0x00003078))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003078+4*1))=0x000061a4;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000078))=0x04c00050;
*((unsigned int *)((unsigned long)context_ptr+0x00000078+4*1))=0x00006154;
*((unsigned int *)((unsigned long)context_ptr+0x00000078+4*2))=0x00006144;
*((unsigned int *)((unsigned long)context_ptr+0x00000078+4*3))=0x02220050;
*((unsigned int *)((unsigned long)context_ptr+0x00000078+4*4))=0x090b6e38;
*((unsigned int *)((unsigned long)context_ptr+0x00000078+4*5))=0x00006028+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000006&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006044,"\x0c\xc1\x75\xb9\xc0\xf1\xb6\xa8\x31\xc3\x99\xe2\x69\x77\x26\x61",16))
printf("strip: 0cc175b9c0f1b6a8, Pass\n");
else
printf("strip: 0cc175b9c0f1b6a8, Failed\n");
writel(0x0000000c&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006068,"\x90\x01\x50\x98\x3c\xd2\x4f\xb0\xd6\x96\x3f\x7d\x28\xe1\x7f\x72",16))
printf("strip: 900150983cd24fb0, Pass\n");
else
printf("strip: 900150983cd24fb0, Failed\n");
writel(0x00000012&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006098,"\xf9\x6b\x69\x7d\x7c\xb7\x93\x8d\x52\x5a\x2f\x31\xaa\xf1\x61\xd0",16))
printf("strip: f96b697d7cb7938d, Pass\n");
else
printf("strip: f96b697d7cb7938d, Failed\n");
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000060d4,"\xc3\xfc\xd3\xd7\x61\x92\xe4\x00\x7d\xfb\x49\x6c\xca\x67\xe1\x3b",16))
printf("strip: c3fcd3d76192e400, Pass\n");
else
printf("strip: c3fcd3d76192e400, Failed\n");
writel(0x0000001e&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006134,"\xd1\x74\xab\x98\xd2\x77\xd9\xf5\xa5\x61\x1c\x2c\x9f\x41\x9d\x9f",16))
printf("strip: d174ab98d277d9f5, Pass\n");
else
printf("strip: d174ab98d277d9f5, Failed\n");
writel(0x00000024&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000061a4,"\x57\xed\xf4\xa2\x2b\xe3\xc9\x55\xac\x49\xda\x2e\x21\x07\xb6\x7a",16))
printf("strip: 57edf4a22be3c955, Pass\n");
else
printf("strip: 57edf4a22be3c955, Failed\n");
}

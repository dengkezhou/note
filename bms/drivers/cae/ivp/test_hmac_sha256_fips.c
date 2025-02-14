#include <common.h>
#include <malloc.h>

extern volatile unsigned int ivp_cae_base_addr;

void test_hmac_sha256_fips(void)
{
unsigned int *context_ptr=(unsigned int *)0x14000000;
printf("test_hmac_sha256_fips\n");
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
*((unsigned int *)((unsigned long)context_ptr+0x00006000))=0x01ea1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006000+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006000+4*2))=0x606e1a0e;
*((unsigned int *)((unsigned long)context_ptr+0x00006000+4*3))=0x691c0f22;
*((unsigned int *)((unsigned long)context_ptr+0x00006000+4*4))=0x3707cbed;
*((unsigned int *)((unsigned long)context_ptr+0x00006000+4*5))=0x4a408896;
*((unsigned int *)((unsigned long)context_ptr+0x00006000+4*6))=0x6fe722b4;
*((unsigned int *)((unsigned long)context_ptr+0x00006000+4*7))=0x4eb8fd1d;
*((unsigned int *)((unsigned long)context_ptr+0x00006000+4*8))=0x3f2fb1b2;
*((unsigned int *)((unsigned long)context_ptr+0x00006000+4*9))=0x5b7bc584;
*((unsigned int *)((unsigned long)context_ptr+0x00006000+4*10))=0x54dc2cea;
*((unsigned int *)((unsigned long)context_ptr+0x00006000+4*11))=0x76a976a8;
*((unsigned int *)((unsigned long)context_ptr+0x00006000+4*12))=0x2fbd9b45;
*((unsigned int *)((unsigned long)context_ptr+0x00006000+4*13))=0x7c969aac;
*((unsigned int *)((unsigned long)context_ptr+0x00006000+4*14))=0xe2612c90;
*((unsigned int *)((unsigned long)context_ptr+0x00006000+4*15))=0x32c1e1ee;
*((unsigned int *)((unsigned long)context_ptr+0x00006000+4*16))=0x1a604135;
*((unsigned int *)((unsigned long)context_ptr+0x00006000+4*17))=0x43b0ff5e;
*((unsigned int *)((unsigned long)context_ptr+0x00006048))=0x01ea1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006048+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006048+4*2))=0x606e1a0e;
*((unsigned int *)((unsigned long)context_ptr+0x00006048+4*3))=0x691c0f22;
*((unsigned int *)((unsigned long)context_ptr+0x00006048+4*4))=0x3707cbed;
*((unsigned int *)((unsigned long)context_ptr+0x00006048+4*5))=0x4a408896;
*((unsigned int *)((unsigned long)context_ptr+0x00006048+4*6))=0x6fe722b4;
*((unsigned int *)((unsigned long)context_ptr+0x00006048+4*7))=0x4eb8fd1d;
*((unsigned int *)((unsigned long)context_ptr+0x00006048+4*8))=0x3f2fb1b2;
*((unsigned int *)((unsigned long)context_ptr+0x00006048+4*9))=0x5b7bc584;
*((unsigned int *)((unsigned long)context_ptr+0x00006048+4*10))=0x54dc2cea;
*((unsigned int *)((unsigned long)context_ptr+0x00006048+4*11))=0x76a976a8;
*((unsigned int *)((unsigned long)context_ptr+0x00006048+4*12))=0x2fbd9b45;
*((unsigned int *)((unsigned long)context_ptr+0x00006048+4*13))=0x7c969aac;
*((unsigned int *)((unsigned long)context_ptr+0x00006048+4*14))=0xe2612c90;
*((unsigned int *)((unsigned long)context_ptr+0x00006048+4*15))=0x32c1e1ee;
*((unsigned int *)((unsigned long)context_ptr+0x00006048+4*16))=0x1a604135;
*((unsigned int *)((unsigned long)context_ptr+0x00006048+4*17))=0x43b0ff5e;
*((unsigned int *)((unsigned long)context_ptr+0x00006090))=0x01ea1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006090+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006090+4*2))=0x606e1a0e;
*((unsigned int *)((unsigned long)context_ptr+0x00006090+4*3))=0x691c0f22;
*((unsigned int *)((unsigned long)context_ptr+0x00006090+4*4))=0x3707cbed;
*((unsigned int *)((unsigned long)context_ptr+0x00006090+4*5))=0x4a408896;
*((unsigned int *)((unsigned long)context_ptr+0x00006090+4*6))=0x6fe722b4;
*((unsigned int *)((unsigned long)context_ptr+0x00006090+4*7))=0x4eb8fd1d;
*((unsigned int *)((unsigned long)context_ptr+0x00006090+4*8))=0x3f2fb1b2;
*((unsigned int *)((unsigned long)context_ptr+0x00006090+4*9))=0x5b7bc584;
*((unsigned int *)((unsigned long)context_ptr+0x00006090+4*10))=0x54dc2cea;
*((unsigned int *)((unsigned long)context_ptr+0x00006090+4*11))=0x76a976a8;
*((unsigned int *)((unsigned long)context_ptr+0x00006090+4*12))=0x2fbd9b45;
*((unsigned int *)((unsigned long)context_ptr+0x00006090+4*13))=0x7c969aac;
*((unsigned int *)((unsigned long)context_ptr+0x00006090+4*14))=0xe2612c90;
*((unsigned int *)((unsigned long)context_ptr+0x00006090+4*15))=0x32c1e1ee;
*((unsigned int *)((unsigned long)context_ptr+0x00006090+4*16))=0x1a604135;
*((unsigned int *)((unsigned long)context_ptr+0x00006090+4*17))=0x43b0ff5e;
*((unsigned int *)((unsigned long)context_ptr+0x000060d8))=0x01ea1002;
*((unsigned int *)((unsigned long)context_ptr+0x000060d8+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000060d8+4*2))=0x338623d1;
*((unsigned int *)((unsigned long)context_ptr+0x000060d8+4*3))=0x7c49e929;
*((unsigned int *)((unsigned long)context_ptr+0x000060d8+4*4))=0xfa86262e;
*((unsigned int *)((unsigned long)context_ptr+0x000060d8+4*5))=0xd15b1cac;
*((unsigned int *)((unsigned long)context_ptr+0x000060d8+4*6))=0x59cf067b;
*((unsigned int *)((unsigned long)context_ptr+0x000060d8+4*7))=0xab213750;
*((unsigned int *)((unsigned long)context_ptr+0x000060d8+4*8))=0x32d18b13;
*((unsigned int *)((unsigned long)context_ptr+0x000060d8+4*9))=0x74b619f6;
*((unsigned int *)((unsigned long)context_ptr+0x000060d8+4*10))=0xaa54754a;
*((unsigned int *)((unsigned long)context_ptr+0x000060d8+4*11))=0x7e7a0c24;
*((unsigned int *)((unsigned long)context_ptr+0x000060d8+4*12))=0x9d35f06b;
*((unsigned int *)((unsigned long)context_ptr+0x000060d8+4*13))=0x5c6d449f;
*((unsigned int *)((unsigned long)context_ptr+0x000060d8+4*14))=0x89049c79;
*((unsigned int *)((unsigned long)context_ptr+0x000060d8+4*15))=0xb98fae63;
*((unsigned int *)((unsigned long)context_ptr+0x000060d8+4*16))=0x50a7dc6f;
*((unsigned int *)((unsigned long)context_ptr+0x000060d8+4*17))=0x161f1f72;
*((unsigned int *)((unsigned long)context_ptr+0x00006120))=0x01ea1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006120+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006120+4*2))=0x0418b22b;
*((unsigned int *)((unsigned long)context_ptr+0x00006120+4*3))=0xf95bb923;
*((unsigned int *)((unsigned long)context_ptr+0x00006120+4*4))=0x8c25e8b4;
*((unsigned int *)((unsigned long)context_ptr+0x00006120+4*5))=0x54e6b5fa;
*((unsigned int *)((unsigned long)context_ptr+0x00006120+4*6))=0x1e92f211;
*((unsigned int *)((unsigned long)context_ptr+0x00006120+4*7))=0xee78eb4f;
*((unsigned int *)((unsigned long)context_ptr+0x00006120+4*8))=0xfee59098;
*((unsigned int *)((unsigned long)context_ptr+0x00006120+4*9))=0x3680b764;
*((unsigned int *)((unsigned long)context_ptr+0x00006120+4*10))=0x9f73e727;
*((unsigned int *)((unsigned long)context_ptr+0x00006120+4*11))=0x832556d9;
*((unsigned int *)((unsigned long)context_ptr+0x00006120+4*12))=0xe266d656;
*((unsigned int *)((unsigned long)context_ptr+0x00006120+4*13))=0xe80d815f;
*((unsigned int *)((unsigned long)context_ptr+0x00006120+4*14))=0x8a4f5eec;
*((unsigned int *)((unsigned long)context_ptr+0x00006120+4*15))=0xb84f3d55;
*((unsigned int *)((unsigned long)context_ptr+0x00006120+4*16))=0xba20ff3c;
*((unsigned int *)((unsigned long)context_ptr+0x00006120+4*17))=0x404b2310;
*((unsigned int *)((unsigned long)context_ptr+0x00006168))=0x01ea1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006168+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006168+4*2))=0xfaa75d65;
*((unsigned int *)((unsigned long)context_ptr+0x00006168+4*3))=0x374b43cc;
*((unsigned int *)((unsigned long)context_ptr+0x00006168+4*4))=0xcbd51c5a;
*((unsigned int *)((unsigned long)context_ptr+0x00006168+4*5))=0x0eee9206;
*((unsigned int *)((unsigned long)context_ptr+0x00006168+4*6))=0xd3237aa4;
*((unsigned int *)((unsigned long)context_ptr+0x00006168+4*7))=0x49f43a4c;
*((unsigned int *)((unsigned long)context_ptr+0x00006168+4*8))=0xe21aa2db;
*((unsigned int *)((unsigned long)context_ptr+0x00006168+4*9))=0x0c50c778;
*((unsigned int *)((unsigned long)context_ptr+0x00006168+4*10))=0xd5e3af0e;
*((unsigned int *)((unsigned long)context_ptr+0x00006168+4*11))=0x6c2e4113;
*((unsigned int *)((unsigned long)context_ptr+0x00006168+4*12))=0xeb2f6a6a;
*((unsigned int *)((unsigned long)context_ptr+0x00006168+4*13))=0xcc5a372d;
*((unsigned int *)((unsigned long)context_ptr+0x00006168+4*14))=0x47fda451;
*((unsigned int *)((unsigned long)context_ptr+0x00006168+4*15))=0xe895b06d;
*((unsigned int *)((unsigned long)context_ptr+0x00006168+4*16))=0x8aa1bf23;
*((unsigned int *)((unsigned long)context_ptr+0x00006168+4*17))=0xd541f152;
*((unsigned int *)((unsigned long)context_ptr+0x000061b0))=0x01ea1002;
*((unsigned int *)((unsigned long)context_ptr+0x000061b0+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000061b0+4*2))=0x7d60d52d;
*((unsigned int *)((unsigned long)context_ptr+0x000061b0+4*3))=0x4cdc19f6;
*((unsigned int *)((unsigned long)context_ptr+0x000061b0+4*4))=0x12a9e4d2;
*((unsigned int *)((unsigned long)context_ptr+0x000061b0+4*5))=0xdca0b79f;
*((unsigned int *)((unsigned long)context_ptr+0x000061b0+4*6))=0x0f20661c;
*((unsigned int *)((unsigned long)context_ptr+0x000061b0+4*7))=0x547e6c09;
*((unsigned int *)((unsigned long)context_ptr+0x000061b0+4*8))=0x876a95de;
*((unsigned int *)((unsigned long)context_ptr+0x000061b0+4*9))=0x25d8ec1e;
*((unsigned int *)((unsigned long)context_ptr+0x000061b0+4*10))=0xf06d10b5;
*((unsigned int *)((unsigned long)context_ptr+0x000061b0+4*11))=0x82f05f19;
*((unsigned int *)((unsigned long)context_ptr+0x000061b0+4*12))=0xd411b862;
*((unsigned int *)((unsigned long)context_ptr+0x000061b0+4*13))=0x357f789a;
*((unsigned int *)((unsigned long)context_ptr+0x000061b0+4*14))=0xc304db39;
*((unsigned int *)((unsigned long)context_ptr+0x000061b0+4*15))=0x6d9e5145;
*((unsigned int *)((unsigned long)context_ptr+0x000061b0+4*16))=0xc93f9c03;
*((unsigned int *)((unsigned long)context_ptr+0x000061b0+4*17))=0xf357daae;
*((unsigned int *)((unsigned long)context_ptr+0x000061f8))=0x01ea1002;
*((unsigned int *)((unsigned long)context_ptr+0x000061f8+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000061f8+4*2))=0x9fd7df5d;
*((unsigned int *)((unsigned long)context_ptr+0x000061f8+4*3))=0x66332fdf;
*((unsigned int *)((unsigned long)context_ptr+0x000061f8+4*4))=0x89cce4eb;
*((unsigned int *)((unsigned long)context_ptr+0x000061f8+4*5))=0x5bad15ab;
*((unsigned int *)((unsigned long)context_ptr+0x000061f8+4*6))=0x26f81109;
*((unsigned int *)((unsigned long)context_ptr+0x000061f8+4*7))=0xc29ff415;
*((unsigned int *)((unsigned long)context_ptr+0x000061f8+4*8))=0x20b96b66;
*((unsigned int *)((unsigned long)context_ptr+0x000061f8+4*9))=0x6e23de0a;
*((unsigned int *)((unsigned long)context_ptr+0x000061f8+4*10))=0xb7d05111;
*((unsigned int *)((unsigned long)context_ptr+0x000061f8+4*11))=0xad54255e;
*((unsigned int *)((unsigned long)context_ptr+0x000061f8+4*12))=0x60c2f23b;
*((unsigned int *)((unsigned long)context_ptr+0x000061f8+4*13))=0x6c5ee91d;
*((unsigned int *)((unsigned long)context_ptr+0x000061f8+4*14))=0x4af5efd9;
*((unsigned int *)((unsigned long)context_ptr+0x000061f8+4*15))=0x74c707dc;
*((unsigned int *)((unsigned long)context_ptr+0x000061f8+4*16))=0xdce5944d;
*((unsigned int *)((unsigned long)context_ptr+0x000061f8+4*17))=0x0324b41a;
*((unsigned int *)((unsigned long)context_ptr+0x00006240))=0x01ea1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006240+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006240+4*2))=0xc9a9b4ac;
*((unsigned int *)((unsigned long)context_ptr+0x00006240+4*3))=0xce4e9475;
*((unsigned int *)((unsigned long)context_ptr+0x00006240+4*4))=0xfbed3b4b;
*((unsigned int *)((unsigned long)context_ptr+0x00006240+4*5))=0x49073ca4;
*((unsigned int *)((unsigned long)context_ptr+0x00006240+4*6))=0xc992a638;
*((unsigned int *)((unsigned long)context_ptr+0x00006240+4*7))=0x1a70873f;
*((unsigned int *)((unsigned long)context_ptr+0x00006240+4*8))=0xa6e55ca6;
*((unsigned int *)((unsigned long)context_ptr+0x00006240+4*9))=0x6538969b;
*((unsigned int *)((unsigned long)context_ptr+0x00006240+4*10))=0xe1d3da46;
*((unsigned int *)((unsigned long)context_ptr+0x00006240+4*11))=0xe57077c2;
*((unsigned int *)((unsigned long)context_ptr+0x00006240+4*12))=0x58e740ed;
*((unsigned int *)((unsigned long)context_ptr+0x00006240+4*13))=0x91e04db1;
*((unsigned int *)((unsigned long)context_ptr+0x00006240+4*14))=0xfa0141b6;
*((unsigned int *)((unsigned long)context_ptr+0x00006240+4*15))=0x83e9ad7a;
*((unsigned int *)((unsigned long)context_ptr+0x00006240+4*16))=0xbbe8bfd6;
*((unsigned int *)((unsigned long)context_ptr+0x00006240+4*17))=0xbb1adf6e;
*((unsigned int *)((unsigned long)context_ptr+0x00006288))=0x01ea1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006288+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006288+4*2))=0xc5b68500;
*((unsigned int *)((unsigned long)context_ptr+0x00006288+4*3))=0x7c7bccfd;
*((unsigned int *)((unsigned long)context_ptr+0x00006288+4*4))=0xf4b4f578;
*((unsigned int *)((unsigned long)context_ptr+0x00006288+4*5))=0xf537a575;
*((unsigned int *)((unsigned long)context_ptr+0x00006288+4*6))=0xc15c9f42;
*((unsigned int *)((unsigned long)context_ptr+0x00006288+4*7))=0xe1d294fc;
*((unsigned int *)((unsigned long)context_ptr+0x00006288+4*8))=0x16940c0d;
*((unsigned int *)((unsigned long)context_ptr+0x00006288+4*9))=0xa329fcf6;
*((unsigned int *)((unsigned long)context_ptr+0x00006288+4*10))=0x48a80a5c;
*((unsigned int *)((unsigned long)context_ptr+0x00006288+4*11))=0x81c85398;
*((unsigned int *)((unsigned long)context_ptr+0x00006288+4*12))=0xaae13ba0;
*((unsigned int *)((unsigned long)context_ptr+0x00006288+4*13))=0x0aeb9596;
*((unsigned int *)((unsigned long)context_ptr+0x00006288+4*14))=0x9fcc0530;
*((unsigned int *)((unsigned long)context_ptr+0x00006288+4*15))=0x01c06470;
*((unsigned int *)((unsigned long)context_ptr+0x00006288+4*16))=0x58c80694;
*((unsigned int *)((unsigned long)context_ptr+0x00006288+4*17))=0x72e8a460;
*((unsigned int *)((unsigned long)context_ptr+0x000062d0))=0x01ea1002;
*((unsigned int *)((unsigned long)context_ptr+0x000062d0+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000062d0+4*2))=0xc5b68500;
*((unsigned int *)((unsigned long)context_ptr+0x000062d0+4*3))=0x7c7bccfd;
*((unsigned int *)((unsigned long)context_ptr+0x000062d0+4*4))=0xf4b4f578;
*((unsigned int *)((unsigned long)context_ptr+0x000062d0+4*5))=0xf537a575;
*((unsigned int *)((unsigned long)context_ptr+0x000062d0+4*6))=0xc15c9f42;
*((unsigned int *)((unsigned long)context_ptr+0x000062d0+4*7))=0xe1d294fc;
*((unsigned int *)((unsigned long)context_ptr+0x000062d0+4*8))=0x16940c0d;
*((unsigned int *)((unsigned long)context_ptr+0x000062d0+4*9))=0xa329fcf6;
*((unsigned int *)((unsigned long)context_ptr+0x000062d0+4*10))=0x48a80a5c;
*((unsigned int *)((unsigned long)context_ptr+0x000062d0+4*11))=0x81c85398;
*((unsigned int *)((unsigned long)context_ptr+0x000062d0+4*12))=0xaae13ba0;
*((unsigned int *)((unsigned long)context_ptr+0x000062d0+4*13))=0x0aeb9596;
*((unsigned int *)((unsigned long)context_ptr+0x000062d0+4*14))=0x9fcc0530;
*((unsigned int *)((unsigned long)context_ptr+0x000062d0+4*15))=0x01c06470;
*((unsigned int *)((unsigned long)context_ptr+0x000062d0+4*16))=0x58c80694;
*((unsigned int *)((unsigned long)context_ptr+0x000062d0+4*17))=0x72e8a460;
*((unsigned int *)((unsigned long)context_ptr+0x00006318))=0x01ea1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006318+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006318+4*2))=0x51cf90af;
*((unsigned int *)((unsigned long)context_ptr+0x00006318+4*3))=0xc61d9173;
*((unsigned int *)((unsigned long)context_ptr+0x00006318+4*4))=0x6709ebe3;
*((unsigned int *)((unsigned long)context_ptr+0x00006318+4*5))=0x672f8b60;
*((unsigned int *)((unsigned long)context_ptr+0x00006318+4*6))=0xc8ed4e2e;
*((unsigned int *)((unsigned long)context_ptr+0x00006318+4*7))=0x064a0335;
*((unsigned int *)((unsigned long)context_ptr+0x00006318+4*8))=0x024915f2;
*((unsigned int *)((unsigned long)context_ptr+0x00006318+4*9))=0xb34de9c6;
*((unsigned int *)((unsigned long)context_ptr+0x00006318+4*10))=0xb62d2e3b;
*((unsigned int *)((unsigned long)context_ptr+0x00006318+4*11))=0xf0c4ec66;
*((unsigned int *)((unsigned long)context_ptr+0x00006318+4*12))=0x38031854;
*((unsigned int *)((unsigned long)context_ptr+0x00006318+4*13))=0xa2b347da;
*((unsigned int *)((unsigned long)context_ptr+0x00006318+4*14))=0x6ba315d4;
*((unsigned int *)((unsigned long)context_ptr+0x00006318+4*15))=0x4294e655;
*((unsigned int *)((unsigned long)context_ptr+0x00006318+4*16))=0xd9c6809f;
*((unsigned int *)((unsigned long)context_ptr+0x00006318+4*17))=0x6108df3e;
*((unsigned int *)((unsigned long)context_ptr+0x00006360))=0x01ea1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006360+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006360+4*2))=0xfd136542;
*((unsigned int *)((unsigned long)context_ptr+0x00006360+4*3))=0x82a2c58f;
*((unsigned int *)((unsigned long)context_ptr+0x00006360+4*4))=0x69d9b2c4;
*((unsigned int *)((unsigned long)context_ptr+0x00006360+4*5))=0xba96e0cd;
*((unsigned int *)((unsigned long)context_ptr+0x00006360+4*6))=0x80add6aa;
*((unsigned int *)((unsigned long)context_ptr+0x00006360+4*7))=0x21f9fc58;
*((unsigned int *)((unsigned long)context_ptr+0x00006360+4*8))=0xcad52b32;
*((unsigned int *)((unsigned long)context_ptr+0x00006360+4*9))=0xf3c55b0e;
*((unsigned int *)((unsigned long)context_ptr+0x00006360+4*10))=0x47247188;
*((unsigned int *)((unsigned long)context_ptr+0x00006360+4*11))=0x9dd3fc56;
*((unsigned int *)((unsigned long)context_ptr+0x00006360+4*12))=0x1938f164;
*((unsigned int *)((unsigned long)context_ptr+0x00006360+4*13))=0x58c069e6;
*((unsigned int *)((unsigned long)context_ptr+0x00006360+4*14))=0x6466bf8f;
*((unsigned int *)((unsigned long)context_ptr+0x00006360+4*15))=0xcc5c09b5;
*((unsigned int *)((unsigned long)context_ptr+0x00006360+4*16))=0xe51d8606;
*((unsigned int *)((unsigned long)context_ptr+0x00006360+4*17))=0x83f1da1d;
*((unsigned int *)((unsigned long)context_ptr+0x000063a8))=0x01ea1002;
*((unsigned int *)((unsigned long)context_ptr+0x000063a8+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000063a8+4*2))=0x5984993f;
*((unsigned int *)((unsigned long)context_ptr+0x000063a8+4*3))=0x6c174f89;
*((unsigned int *)((unsigned long)context_ptr+0x000063a8+4*4))=0xc001cf65;
*((unsigned int *)((unsigned long)context_ptr+0x000063a8+4*5))=0x87d31ffe;
*((unsigned int *)((unsigned long)context_ptr+0x000063a8+4*6))=0x5a98be6a;
*((unsigned int *)((unsigned long)context_ptr+0x000063a8+4*7))=0xd5f1129a;
*((unsigned int *)((unsigned long)context_ptr+0x000063a8+4*8))=0xbadae281;
*((unsigned int *)((unsigned long)context_ptr+0x000063a8+4*9))=0x505ce871;
*((unsigned int *)((unsigned long)context_ptr+0x000063a8+4*10))=0xe84c513d;
*((unsigned int *)((unsigned long)context_ptr+0x000063a8+4*11))=0x4334b0ae;
*((unsigned int *)((unsigned long)context_ptr+0x000063a8+4*12))=0x51ebc506;
*((unsigned int *)((unsigned long)context_ptr+0x000063a8+4*13))=0x464cd1db;
*((unsigned int *)((unsigned long)context_ptr+0x000063a8+4*14))=0x991e7040;
*((unsigned int *)((unsigned long)context_ptr+0x000063a8+4*15))=0x2ff166cf;
*((unsigned int *)((unsigned long)context_ptr+0x000063a8+4*16))=0xd74cc48b;
*((unsigned int *)((unsigned long)context_ptr+0x000063a8+4*17))=0xf1739e32;
*((unsigned int *)((unsigned long)context_ptr+0x000063f0))=0x01ea1002;
*((unsigned int *)((unsigned long)context_ptr+0x000063f0+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000063f0+4*2))=0x6c4690b4;
*((unsigned int *)((unsigned long)context_ptr+0x000063f0+4*3))=0xd83a785a;
*((unsigned int *)((unsigned long)context_ptr+0x000063f0+4*4))=0xbcdc1514;
*((unsigned int *)((unsigned long)context_ptr+0x000063f0+4*5))=0x2f5e6f70;
*((unsigned int *)((unsigned long)context_ptr+0x000063f0+4*6))=0x7d74c34d;
*((unsigned int *)((unsigned long)context_ptr+0x000063f0+4*7))=0xb2d82ea7;
*((unsigned int *)((unsigned long)context_ptr+0x000063f0+4*8))=0x4d599629;
*((unsigned int *)((unsigned long)context_ptr+0x000063f0+4*9))=0xe134b119;
*((unsigned int *)((unsigned long)context_ptr+0x000063f0+4*10))=0xa1e330f3;
*((unsigned int *)((unsigned long)context_ptr+0x000063f0+4*11))=0x54d9f2dd;
*((unsigned int *)((unsigned long)context_ptr+0x000063f0+4*12))=0x7e22bfb3;
*((unsigned int *)((unsigned long)context_ptr+0x000063f0+4*13))=0xb5d64bbb;
*((unsigned int *)((unsigned long)context_ptr+0x000063f0+4*14))=0xbff7daac;
*((unsigned int *)((unsigned long)context_ptr+0x000063f0+4*15))=0x575eea51;
*((unsigned int *)((unsigned long)context_ptr+0x000063f0+4*16))=0x610897d1;
*((unsigned int *)((unsigned long)context_ptr+0x000063f0+4*17))=0x022a545c;
*((unsigned int *)((unsigned long)context_ptr+0x00006438))=0x01ea1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006438+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006438+4*2))=0x6c4690b4;
*((unsigned int *)((unsigned long)context_ptr+0x00006438+4*3))=0xd83a785a;
*((unsigned int *)((unsigned long)context_ptr+0x00006438+4*4))=0xbcdc1514;
*((unsigned int *)((unsigned long)context_ptr+0x00006438+4*5))=0x2f5e6f70;
*((unsigned int *)((unsigned long)context_ptr+0x00006438+4*6))=0x7d74c34d;
*((unsigned int *)((unsigned long)context_ptr+0x00006438+4*7))=0xb2d82ea7;
*((unsigned int *)((unsigned long)context_ptr+0x00006438+4*8))=0x4d599629;
*((unsigned int *)((unsigned long)context_ptr+0x00006438+4*9))=0xe134b119;
*((unsigned int *)((unsigned long)context_ptr+0x00006438+4*10))=0xa1e330f3;
*((unsigned int *)((unsigned long)context_ptr+0x00006438+4*11))=0x54d9f2dd;
*((unsigned int *)((unsigned long)context_ptr+0x00006438+4*12))=0x7e22bfb3;
*((unsigned int *)((unsigned long)context_ptr+0x00006438+4*13))=0xb5d64bbb;
*((unsigned int *)((unsigned long)context_ptr+0x00006438+4*14))=0xbff7daac;
*((unsigned int *)((unsigned long)context_ptr+0x00006438+4*15))=0x575eea51;
*((unsigned int *)((unsigned long)context_ptr+0x00006438+4*16))=0x610897d1;
*((unsigned int *)((unsigned long)context_ptr+0x00006438+4*17))=0x022a545c;
*((unsigned int *)((unsigned long)context_ptr+0x00006480))=0x01ea1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006480+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006480+4*2))=0x02020003;
*((unsigned int *)((unsigned long)context_ptr+0x00006480+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x00006490))=0x00636261;
*((unsigned int *)((unsigned long)context_ptr+0x00003000))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003000+4*1))=0x00006494;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000000+4*1))=0x00006490;
*((unsigned int *)((unsigned long)context_ptr+0x00000000+4*2))=0x00006480;
*((unsigned int *)((unsigned long)context_ptr+0x00000000+4*3))=0x02220003;
*((unsigned int *)((unsigned long)context_ptr+0x00000000+4*4))=0x037ab26b;
*((unsigned int *)((unsigned long)context_ptr+0x00000000+4*5))=0x00006000+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x000064b4))=0x01ea1002;
*((unsigned int *)((unsigned long)context_ptr+0x000064b4+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000064b4+4*2))=0x02020038;
*((unsigned int *)((unsigned long)context_ptr+0x000064b4+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x000064c4))=0x64636261;
*((unsigned int *)((unsigned long)context_ptr+0x000064c4+4*1))=0x65646362;
*((unsigned int *)((unsigned long)context_ptr+0x000064c4+4*2))=0x66656463;
*((unsigned int *)((unsigned long)context_ptr+0x000064c4+4*3))=0x67666564;
*((unsigned int *)((unsigned long)context_ptr+0x000064c4+4*4))=0x68676665;
*((unsigned int *)((unsigned long)context_ptr+0x000064c4+4*5))=0x69686766;
*((unsigned int *)((unsigned long)context_ptr+0x000064c4+4*6))=0x6a696867;
*((unsigned int *)((unsigned long)context_ptr+0x000064c4+4*7))=0x6b6a6968;
*((unsigned int *)((unsigned long)context_ptr+0x000064c4+4*8))=0x6c6b6a69;
*((unsigned int *)((unsigned long)context_ptr+0x000064c4+4*9))=0x6d6c6b6a;
*((unsigned int *)((unsigned long)context_ptr+0x000064c4+4*10))=0x6e6d6c6b;
*((unsigned int *)((unsigned long)context_ptr+0x000064c4+4*11))=0x6f6e6d6c;
*((unsigned int *)((unsigned long)context_ptr+0x000064c4+4*12))=0x706f6e6d;
*((unsigned int *)((unsigned long)context_ptr+0x000064c4+4*13))=0x71706f6e;
*((unsigned int *)((unsigned long)context_ptr+0x00003018))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003018+4*1))=0x000064fc;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000018))=0x04c00038;
*((unsigned int *)((unsigned long)context_ptr+0x00000018+4*1))=0x000064c4;
*((unsigned int *)((unsigned long)context_ptr+0x00000018+4*2))=0x000064b4;
*((unsigned int *)((unsigned long)context_ptr+0x00000018+4*3))=0x02220038;
*((unsigned int *)((unsigned long)context_ptr+0x00000018+4*4))=0x0349eb15;
*((unsigned int *)((unsigned long)context_ptr+0x00000018+4*5))=0x00006048+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x0000651c))=0x01ea1002;
*((unsigned int *)((unsigned long)context_ptr+0x0000651c+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x0000651c+4*2))=0x02020070;
*((unsigned int *)((unsigned long)context_ptr+0x0000651c+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x0000652c))=0x64636261;
*((unsigned int *)((unsigned long)context_ptr+0x0000652c+4*1))=0x65646362;
*((unsigned int *)((unsigned long)context_ptr+0x0000652c+4*2))=0x66656463;
*((unsigned int *)((unsigned long)context_ptr+0x0000652c+4*3))=0x67666564;
*((unsigned int *)((unsigned long)context_ptr+0x0000652c+4*4))=0x68676665;
*((unsigned int *)((unsigned long)context_ptr+0x0000652c+4*5))=0x69686766;
*((unsigned int *)((unsigned long)context_ptr+0x0000652c+4*6))=0x6a696867;
*((unsigned int *)((unsigned long)context_ptr+0x0000652c+4*7))=0x6b6a6968;
*((unsigned int *)((unsigned long)context_ptr+0x0000652c+4*8))=0x6c6b6a69;
*((unsigned int *)((unsigned long)context_ptr+0x0000652c+4*9))=0x6d6c6b6a;
*((unsigned int *)((unsigned long)context_ptr+0x0000652c+4*10))=0x6e6d6c6b;
*((unsigned int *)((unsigned long)context_ptr+0x0000652c+4*11))=0x6f6e6d6c;
*((unsigned int *)((unsigned long)context_ptr+0x0000652c+4*12))=0x706f6e6d;
*((unsigned int *)((unsigned long)context_ptr+0x0000652c+4*13))=0x71706f6e;
*((unsigned int *)((unsigned long)context_ptr+0x0000652c+4*14))=0x64636261;
*((unsigned int *)((unsigned long)context_ptr+0x0000652c+4*15))=0x65646362;
*((unsigned int *)((unsigned long)context_ptr+0x0000652c+4*16))=0x66656463;
*((unsigned int *)((unsigned long)context_ptr+0x0000652c+4*17))=0x67666564;
*((unsigned int *)((unsigned long)context_ptr+0x0000652c+4*18))=0x68676665;
*((unsigned int *)((unsigned long)context_ptr+0x0000652c+4*19))=0x69686766;
*((unsigned int *)((unsigned long)context_ptr+0x0000652c+4*20))=0x6a696867;
*((unsigned int *)((unsigned long)context_ptr+0x0000652c+4*21))=0x6b6a6968;
*((unsigned int *)((unsigned long)context_ptr+0x0000652c+4*22))=0x6c6b6a69;
*((unsigned int *)((unsigned long)context_ptr+0x0000652c+4*23))=0x6d6c6b6a;
*((unsigned int *)((unsigned long)context_ptr+0x0000652c+4*24))=0x6e6d6c6b;
*((unsigned int *)((unsigned long)context_ptr+0x0000652c+4*25))=0x6f6e6d6c;
*((unsigned int *)((unsigned long)context_ptr+0x0000652c+4*26))=0x706f6e6d;
*((unsigned int *)((unsigned long)context_ptr+0x0000652c+4*27))=0x71706f6e;
*((unsigned int *)((unsigned long)context_ptr+0x00003030))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003030+4*1))=0x0000659c;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000030))=0x04c00070;
*((unsigned int *)((unsigned long)context_ptr+0x00000030+4*1))=0x0000652c;
*((unsigned int *)((unsigned long)context_ptr+0x00000030+4*2))=0x0000651c;
*((unsigned int *)((unsigned long)context_ptr+0x00000030+4*3))=0x02220070;
*((unsigned int *)((unsigned long)context_ptr+0x00000030+4*4))=0x088ace65;
*((unsigned int *)((unsigned long)context_ptr+0x00000030+4*5))=0x00006090+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x000065bc))=0x01ea1002;
*((unsigned int *)((unsigned long)context_ptr+0x000065bc+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000065bc+4*2))=0x02020008;
*((unsigned int *)((unsigned long)context_ptr+0x000065bc+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x000065cc))=0x54206948;
*((unsigned int *)((unsigned long)context_ptr+0x000065cc+4*1))=0x65726568;
*((unsigned int *)((unsigned long)context_ptr+0x00003048))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003048+4*1))=0x000065d4;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000048))=0x04c00008;
*((unsigned int *)((unsigned long)context_ptr+0x00000048+4*1))=0x000065cc;
*((unsigned int *)((unsigned long)context_ptr+0x00000048+4*2))=0x000065bc;
*((unsigned int *)((unsigned long)context_ptr+0x00000048+4*3))=0x02220008;
*((unsigned int *)((unsigned long)context_ptr+0x00000048+4*4))=0x0a4cf0bd;
*((unsigned int *)((unsigned long)context_ptr+0x00000048+4*5))=0x000060d8+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x000065f4))=0x01ea1002;
*((unsigned int *)((unsigned long)context_ptr+0x000065f4+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000065f4+4*2))=0x02020008;
*((unsigned int *)((unsigned long)context_ptr+0x000065f4+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x00006604))=0x54206948;
*((unsigned int *)((unsigned long)context_ptr+0x00006604+4*1))=0x65726568;
*((unsigned int *)((unsigned long)context_ptr+0x00003060))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003060+4*1))=0x0000660c;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000060))=0x04c00008;
*((unsigned int *)((unsigned long)context_ptr+0x00000060+4*1))=0x00006604;
*((unsigned int *)((unsigned long)context_ptr+0x00000060+4*2))=0x000065f4;
*((unsigned int *)((unsigned long)context_ptr+0x00000060+4*3))=0x02220008;
*((unsigned int *)((unsigned long)context_ptr+0x00000060+4*4))=0x0ca7623a;
*((unsigned int *)((unsigned long)context_ptr+0x00000060+4*5))=0x00006120+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x0000662c))=0x01ea1002;
*((unsigned int *)((unsigned long)context_ptr+0x0000662c+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x0000662c+4*2))=0x0202001c;
*((unsigned int *)((unsigned long)context_ptr+0x0000662c+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x0000663c))=0x74616877;
*((unsigned int *)((unsigned long)context_ptr+0x0000663c+4*1))=0x206f6420;
*((unsigned int *)((unsigned long)context_ptr+0x0000663c+4*2))=0x77206179;
*((unsigned int *)((unsigned long)context_ptr+0x0000663c+4*3))=0x20746e61;
*((unsigned int *)((unsigned long)context_ptr+0x0000663c+4*4))=0x20726f66;
*((unsigned int *)((unsigned long)context_ptr+0x0000663c+4*5))=0x68746f6e;
*((unsigned int *)((unsigned long)context_ptr+0x0000663c+4*6))=0x3f676e69;
*((unsigned int *)((unsigned long)context_ptr+0x00003078))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003078+4*1))=0x00006658;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000078))=0x04c0001c;
*((unsigned int *)((unsigned long)context_ptr+0x00000078+4*1))=0x0000663c;
*((unsigned int *)((unsigned long)context_ptr+0x00000078+4*2))=0x0000662c;
*((unsigned int *)((unsigned long)context_ptr+0x00000078+4*3))=0x0222001c;
*((unsigned int *)((unsigned long)context_ptr+0x00000078+4*4))=0x0ec4f475;
*((unsigned int *)((unsigned long)context_ptr+0x00000078+4*5))=0x00006168+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x00006678))=0x01ea1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006678+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006678+4*2))=0x02020032;
*((unsigned int *)((unsigned long)context_ptr+0x00006678+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x00006688))=0xdddddddd;
*((unsigned int *)((unsigned long)context_ptr+0x00006688+4*1))=0xdddddddd;
*((unsigned int *)((unsigned long)context_ptr+0x00006688+4*2))=0xdddddddd;
*((unsigned int *)((unsigned long)context_ptr+0x00006688+4*3))=0xdddddddd;
*((unsigned int *)((unsigned long)context_ptr+0x00006688+4*4))=0xdddddddd;
*((unsigned int *)((unsigned long)context_ptr+0x00006688+4*5))=0xdddddddd;
*((unsigned int *)((unsigned long)context_ptr+0x00006688+4*6))=0xdddddddd;
*((unsigned int *)((unsigned long)context_ptr+0x00006688+4*7))=0xdddddddd;
*((unsigned int *)((unsigned long)context_ptr+0x00006688+4*8))=0xdddddddd;
*((unsigned int *)((unsigned long)context_ptr+0x00006688+4*9))=0xdddddddd;
*((unsigned int *)((unsigned long)context_ptr+0x00006688+4*10))=0xdddddddd;
*((unsigned int *)((unsigned long)context_ptr+0x00006688+4*11))=0xdddddddd;
*((unsigned int *)((unsigned long)context_ptr+0x00006688+4*12))=0x0000dddd;
*((unsigned int *)((unsigned long)context_ptr+0x00003090))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003090+4*1))=0x000066bc;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000090))=0x04c00032;
*((unsigned int *)((unsigned long)context_ptr+0x00000090+4*1))=0x00006688;
*((unsigned int *)((unsigned long)context_ptr+0x00000090+4*2))=0x00006678;
*((unsigned int *)((unsigned long)context_ptr+0x00000090+4*3))=0x02220032;
*((unsigned int *)((unsigned long)context_ptr+0x00000090+4*4))=0x0b7fe9c5;
*((unsigned int *)((unsigned long)context_ptr+0x00000090+4*5))=0x000061b0+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x000066dc))=0x01ea1002;
*((unsigned int *)((unsigned long)context_ptr+0x000066dc+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000066dc+4*2))=0x02020032;
*((unsigned int *)((unsigned long)context_ptr+0x000066dc+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x000066ec))=0xcdcdcdcd;
*((unsigned int *)((unsigned long)context_ptr+0x000066ec+4*1))=0xcdcdcdcd;
*((unsigned int *)((unsigned long)context_ptr+0x000066ec+4*2))=0xcdcdcdcd;
*((unsigned int *)((unsigned long)context_ptr+0x000066ec+4*3))=0xcdcdcdcd;
*((unsigned int *)((unsigned long)context_ptr+0x000066ec+4*4))=0xcdcdcdcd;
*((unsigned int *)((unsigned long)context_ptr+0x000066ec+4*5))=0xcdcdcdcd;
*((unsigned int *)((unsigned long)context_ptr+0x000066ec+4*6))=0xcdcdcdcd;
*((unsigned int *)((unsigned long)context_ptr+0x000066ec+4*7))=0xcdcdcdcd;
*((unsigned int *)((unsigned long)context_ptr+0x000066ec+4*8))=0xcdcdcdcd;
*((unsigned int *)((unsigned long)context_ptr+0x000066ec+4*9))=0xcdcdcdcd;
*((unsigned int *)((unsigned long)context_ptr+0x000066ec+4*10))=0xcdcdcdcd;
*((unsigned int *)((unsigned long)context_ptr+0x000066ec+4*11))=0xcdcdcdcd;
*((unsigned int *)((unsigned long)context_ptr+0x000066ec+4*12))=0x0000cdcd;
*((unsigned int *)((unsigned long)context_ptr+0x000030a8))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x000030a8+4*1))=0x00006720;
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
*((unsigned int *)((unsigned long)context_ptr+0x000000a8))=0x04c00032;
*((unsigned int *)((unsigned long)context_ptr+0x000000a8+4*1))=0x000066ec;
*((unsigned int *)((unsigned long)context_ptr+0x000000a8+4*2))=0x000066dc;
*((unsigned int *)((unsigned long)context_ptr+0x000000a8+4*3))=0x02220032;
*((unsigned int *)((unsigned long)context_ptr+0x000000a8+4*4))=0x0139b635;
*((unsigned int *)((unsigned long)context_ptr+0x000000a8+4*5))=0x000061f8+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x00006740))=0x01ea1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006740+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006740+4*2))=0x02020014;
*((unsigned int *)((unsigned long)context_ptr+0x00006740+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x00006750))=0x74736554;
*((unsigned int *)((unsigned long)context_ptr+0x00006750+4*1))=0x74695720;
*((unsigned int *)((unsigned long)context_ptr+0x00006750+4*2))=0x72542068;
*((unsigned int *)((unsigned long)context_ptr+0x00006750+4*3))=0x61636e75;
*((unsigned int *)((unsigned long)context_ptr+0x00006750+4*4))=0x6e6f6974;
*((unsigned int *)((unsigned long)context_ptr+0x000030c0))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x000030c0+4*1))=0x00006764;
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
*((unsigned int *)((unsigned long)context_ptr+0x000000c0))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x000000c0+4*1))=0x00006750;
*((unsigned int *)((unsigned long)context_ptr+0x000000c0+4*2))=0x00006740;
*((unsigned int *)((unsigned long)context_ptr+0x000000c0+4*3))=0x02220014;
*((unsigned int *)((unsigned long)context_ptr+0x000000c0+4*4))=0x09fea730;
*((unsigned int *)((unsigned long)context_ptr+0x000000c0+4*5))=0x00006240+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x00006784))=0x01ea1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006784+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006784+4*2))=0x02020036;
*((unsigned int *)((unsigned long)context_ptr+0x00006784+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x00006794))=0x74736554;
*((unsigned int *)((unsigned long)context_ptr+0x00006794+4*1))=0x69735520;
*((unsigned int *)((unsigned long)context_ptr+0x00006794+4*2))=0x4c20676e;
*((unsigned int *)((unsigned long)context_ptr+0x00006794+4*3))=0x65677261;
*((unsigned int *)((unsigned long)context_ptr+0x00006794+4*4))=0x68542072;
*((unsigned int *)((unsigned long)context_ptr+0x00006794+4*5))=0x42206e61;
*((unsigned int *)((unsigned long)context_ptr+0x00006794+4*6))=0x6b636f6c;
*((unsigned int *)((unsigned long)context_ptr+0x00006794+4*7))=0x7a69532d;
*((unsigned int *)((unsigned long)context_ptr+0x00006794+4*8))=0x654b2065;
*((unsigned int *)((unsigned long)context_ptr+0x00006794+4*9))=0x202d2079;
*((unsigned int *)((unsigned long)context_ptr+0x00006794+4*10))=0x68736148;
*((unsigned int *)((unsigned long)context_ptr+0x00006794+4*11))=0x79654b20;
*((unsigned int *)((unsigned long)context_ptr+0x00006794+4*12))=0x72694620;
*((unsigned int *)((unsigned long)context_ptr+0x00006794+4*13))=0x00007473;
*((unsigned int *)((unsigned long)context_ptr+0x000030d8))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x000030d8+4*1))=0x000067cc;
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
*((unsigned int *)((unsigned long)context_ptr+0x000000d8))=0x04c00036;
*((unsigned int *)((unsigned long)context_ptr+0x000000d8+4*1))=0x00006794;
*((unsigned int *)((unsigned long)context_ptr+0x000000d8+4*2))=0x00006784;
*((unsigned int *)((unsigned long)context_ptr+0x000000d8+4*3))=0x02220036;
*((unsigned int *)((unsigned long)context_ptr+0x000000d8+4*4))=0x08b4b7ad;
*((unsigned int *)((unsigned long)context_ptr+0x000000d8+4*5))=0x00006288+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x000067ec))=0x01ea1002;
*((unsigned int *)((unsigned long)context_ptr+0x000067ec+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000067ec+4*2))=0x02020049;
*((unsigned int *)((unsigned long)context_ptr+0x000067ec+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x000067fc))=0x74736554;
*((unsigned int *)((unsigned long)context_ptr+0x000067fc+4*1))=0x69735520;
*((unsigned int *)((unsigned long)context_ptr+0x000067fc+4*2))=0x4c20676e;
*((unsigned int *)((unsigned long)context_ptr+0x000067fc+4*3))=0x65677261;
*((unsigned int *)((unsigned long)context_ptr+0x000067fc+4*4))=0x68542072;
*((unsigned int *)((unsigned long)context_ptr+0x000067fc+4*5))=0x42206e61;
*((unsigned int *)((unsigned long)context_ptr+0x000067fc+4*6))=0x6b636f6c;
*((unsigned int *)((unsigned long)context_ptr+0x000067fc+4*7))=0x7a69532d;
*((unsigned int *)((unsigned long)context_ptr+0x000067fc+4*8))=0x654b2065;
*((unsigned int *)((unsigned long)context_ptr+0x000067fc+4*9))=0x6e612079;
*((unsigned int *)((unsigned long)context_ptr+0x000067fc+4*10))=0x614c2064;
*((unsigned int *)((unsigned long)context_ptr+0x000067fc+4*11))=0x72656772;
*((unsigned int *)((unsigned long)context_ptr+0x000067fc+4*12))=0x61685420;
*((unsigned int *)((unsigned long)context_ptr+0x000067fc+4*13))=0x6e4f206e;
*((unsigned int *)((unsigned long)context_ptr+0x000067fc+4*14))=0x6c422065;
*((unsigned int *)((unsigned long)context_ptr+0x000067fc+4*15))=0x2d6b636f;
*((unsigned int *)((unsigned long)context_ptr+0x000067fc+4*16))=0x657a6953;
*((unsigned int *)((unsigned long)context_ptr+0x000067fc+4*17))=0x74614420;
*((unsigned int *)((unsigned long)context_ptr+0x000067fc+4*18))=0x00000061;
*((unsigned int *)((unsigned long)context_ptr+0x000030f0))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x000030f0+4*1))=0x00006848;
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
*((unsigned int *)((unsigned long)context_ptr+0x000000f0))=0x04c00049;
*((unsigned int *)((unsigned long)context_ptr+0x000000f0+4*1))=0x000067fc;
*((unsigned int *)((unsigned long)context_ptr+0x000000f0+4*2))=0x000067ec;
*((unsigned int *)((unsigned long)context_ptr+0x000000f0+4*3))=0x02220049;
*((unsigned int *)((unsigned long)context_ptr+0x000000f0+4*4))=0x069d9b4b;
*((unsigned int *)((unsigned long)context_ptr+0x000000f0+4*5))=0x000062d0+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x00006868))=0x01ea1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006868+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006868+4*2))=0x02020032;
*((unsigned int *)((unsigned long)context_ptr+0x00006868+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x00006878))=0xdddddddd;
*((unsigned int *)((unsigned long)context_ptr+0x00006878+4*1))=0xdddddddd;
*((unsigned int *)((unsigned long)context_ptr+0x00006878+4*2))=0xdddddddd;
*((unsigned int *)((unsigned long)context_ptr+0x00006878+4*3))=0xdddddddd;
*((unsigned int *)((unsigned long)context_ptr+0x00006878+4*4))=0xdddddddd;
*((unsigned int *)((unsigned long)context_ptr+0x00006878+4*5))=0xdddddddd;
*((unsigned int *)((unsigned long)context_ptr+0x00006878+4*6))=0xdddddddd;
*((unsigned int *)((unsigned long)context_ptr+0x00006878+4*7))=0xdddddddd;
*((unsigned int *)((unsigned long)context_ptr+0x00006878+4*8))=0xdddddddd;
*((unsigned int *)((unsigned long)context_ptr+0x00006878+4*9))=0xdddddddd;
*((unsigned int *)((unsigned long)context_ptr+0x00006878+4*10))=0xdddddddd;
*((unsigned int *)((unsigned long)context_ptr+0x00006878+4*11))=0xdddddddd;
*((unsigned int *)((unsigned long)context_ptr+0x00006878+4*12))=0x0000dddd;
*((unsigned int *)((unsigned long)context_ptr+0x00003108))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003108+4*1))=0x000068ac;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000108))=0x04c00032;
*((unsigned int *)((unsigned long)context_ptr+0x00000108+4*1))=0x00006878;
*((unsigned int *)((unsigned long)context_ptr+0x00000108+4*2))=0x00006868;
*((unsigned int *)((unsigned long)context_ptr+0x00000108+4*3))=0x02220032;
*((unsigned int *)((unsigned long)context_ptr+0x00000108+4*4))=0x0eaae3fe;
*((unsigned int *)((unsigned long)context_ptr+0x00000108+4*5))=0x00006318+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x000068cc))=0x01ea1002;
*((unsigned int *)((unsigned long)context_ptr+0x000068cc+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x000068cc+4*2))=0x02020032;
*((unsigned int *)((unsigned long)context_ptr+0x000068cc+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x000068dc))=0xcdcdcdcd;
*((unsigned int *)((unsigned long)context_ptr+0x000068dc+4*1))=0xcdcdcdcd;
*((unsigned int *)((unsigned long)context_ptr+0x000068dc+4*2))=0xcdcdcdcd;
*((unsigned int *)((unsigned long)context_ptr+0x000068dc+4*3))=0xcdcdcdcd;
*((unsigned int *)((unsigned long)context_ptr+0x000068dc+4*4))=0xcdcdcdcd;
*((unsigned int *)((unsigned long)context_ptr+0x000068dc+4*5))=0xcdcdcdcd;
*((unsigned int *)((unsigned long)context_ptr+0x000068dc+4*6))=0xcdcdcdcd;
*((unsigned int *)((unsigned long)context_ptr+0x000068dc+4*7))=0xcdcdcdcd;
*((unsigned int *)((unsigned long)context_ptr+0x000068dc+4*8))=0xcdcdcdcd;
*((unsigned int *)((unsigned long)context_ptr+0x000068dc+4*9))=0xcdcdcdcd;
*((unsigned int *)((unsigned long)context_ptr+0x000068dc+4*10))=0xcdcdcdcd;
*((unsigned int *)((unsigned long)context_ptr+0x000068dc+4*11))=0xcdcdcdcd;
*((unsigned int *)((unsigned long)context_ptr+0x000068dc+4*12))=0x0000cdcd;
*((unsigned int *)((unsigned long)context_ptr+0x00003120))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003120+4*1))=0x00006910;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000120))=0x04c00032;
*((unsigned int *)((unsigned long)context_ptr+0x00000120+4*1))=0x000068dc;
*((unsigned int *)((unsigned long)context_ptr+0x00000120+4*2))=0x000068cc;
*((unsigned int *)((unsigned long)context_ptr+0x00000120+4*3))=0x02220032;
*((unsigned int *)((unsigned long)context_ptr+0x00000120+4*4))=0x08b3d5e9;
*((unsigned int *)((unsigned long)context_ptr+0x00000120+4*5))=0x00006360+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x00006930))=0x01ea1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006930+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006930+4*2))=0x02020014;
*((unsigned int *)((unsigned long)context_ptr+0x00006930+4*3))=0x21e60010;
*((unsigned int *)((unsigned long)context_ptr+0x00006940))=0x74736554;
*((unsigned int *)((unsigned long)context_ptr+0x00006940+4*1))=0x74695720;
*((unsigned int *)((unsigned long)context_ptr+0x00006940+4*2))=0x72542068;
*((unsigned int *)((unsigned long)context_ptr+0x00006940+4*3))=0x61636e75;
*((unsigned int *)((unsigned long)context_ptr+0x00006940+4*4))=0x6e6f6974;
*((unsigned int *)((unsigned long)context_ptr+0x00003138))=0x04c00010;
*((unsigned int *)((unsigned long)context_ptr+0x00003138+4*1))=0x00006954;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000138))=0x04c00014;
*((unsigned int *)((unsigned long)context_ptr+0x00000138+4*1))=0x00006940;
*((unsigned int *)((unsigned long)context_ptr+0x00000138+4*2))=0x00006930;
*((unsigned int *)((unsigned long)context_ptr+0x00000138+4*3))=0x02220014;
*((unsigned int *)((unsigned long)context_ptr+0x00000138+4*4))=0x01cad91f;
*((unsigned int *)((unsigned long)context_ptr+0x00000138+4*5))=0x000063a8+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
*((unsigned int *)((unsigned long)context_ptr+0x00006964))=0x01ea1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006964+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006964+4*2))=0x02020036;
*((unsigned int *)((unsigned long)context_ptr+0x00006964+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x00006974))=0x74736554;
*((unsigned int *)((unsigned long)context_ptr+0x00006974+4*1))=0x69735520;
*((unsigned int *)((unsigned long)context_ptr+0x00006974+4*2))=0x4c20676e;
*((unsigned int *)((unsigned long)context_ptr+0x00006974+4*3))=0x65677261;
*((unsigned int *)((unsigned long)context_ptr+0x00006974+4*4))=0x68542072;
*((unsigned int *)((unsigned long)context_ptr+0x00006974+4*5))=0x42206e61;
*((unsigned int *)((unsigned long)context_ptr+0x00006974+4*6))=0x6b636f6c;
*((unsigned int *)((unsigned long)context_ptr+0x00006974+4*7))=0x7a69532d;
*((unsigned int *)((unsigned long)context_ptr+0x00006974+4*8))=0x654b2065;
*((unsigned int *)((unsigned long)context_ptr+0x00006974+4*9))=0x202d2079;
*((unsigned int *)((unsigned long)context_ptr+0x00006974+4*10))=0x68736148;
*((unsigned int *)((unsigned long)context_ptr+0x00006974+4*11))=0x79654b20;
*((unsigned int *)((unsigned long)context_ptr+0x00006974+4*12))=0x72694620;
*((unsigned int *)((unsigned long)context_ptr+0x00006974+4*13))=0x00007473;
*((unsigned int *)((unsigned long)context_ptr+0x00003150))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003150+4*1))=0x000069ac;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000150))=0x04c00036;
*((unsigned int *)((unsigned long)context_ptr+0x00000150+4*1))=0x00006974;
*((unsigned int *)((unsigned long)context_ptr+0x00000150+4*2))=0x00006964;
*((unsigned int *)((unsigned long)context_ptr+0x00000150+4*3))=0x02220036;
*((unsigned int *)((unsigned long)context_ptr+0x00000150+4*4))=0x0174f916;
*((unsigned int *)((unsigned long)context_ptr+0x00000150+4*5))=0x000063f0+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000006&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006494,"\xa2\x1b\x1f\x5d\x4c\xf4\xf7\x3a\x4d\xd9\x39\x75\x0f\x7a\x06\x6a\x7f\x98\xcc\x13\x1c\xb1\x6a\x66\x92\x75\x90\x21\xcf\xab\x81\x81",32))
printf("strip: a21b1f5d4cf4f73a, Pass\n");
else
printf("strip: a21b1f5d4cf4f73a, Failed\n");
*((unsigned int *)((unsigned long)context_ptr+0x00006480))=0x01ea1002;
*((unsigned int *)((unsigned long)context_ptr+0x00006480+4*1))=0x00000001;
*((unsigned int *)((unsigned long)context_ptr+0x00006480+4*2))=0x02020098;
*((unsigned int *)((unsigned long)context_ptr+0x00006480+4*3))=0x21e60020;
*((unsigned int *)((unsigned long)context_ptr+0x000069cc))=0x73696854;
*((unsigned int *)((unsigned long)context_ptr+0x000069cc+4*1))=0x20736920;
*((unsigned int *)((unsigned long)context_ptr+0x000069cc+4*2))=0x65742061;
*((unsigned int *)((unsigned long)context_ptr+0x000069cc+4*3))=0x75207473;
*((unsigned int *)((unsigned long)context_ptr+0x000069cc+4*4))=0x676e6973;
*((unsigned int *)((unsigned long)context_ptr+0x000069cc+4*5))=0x6c206120;
*((unsigned int *)((unsigned long)context_ptr+0x000069cc+4*6))=0x65677261;
*((unsigned int *)((unsigned long)context_ptr+0x000069cc+4*7))=0x68742072;
*((unsigned int *)((unsigned long)context_ptr+0x000069cc+4*8))=0x62206e61;
*((unsigned int *)((unsigned long)context_ptr+0x000069cc+4*9))=0x6b636f6c;
*((unsigned int *)((unsigned long)context_ptr+0x000069cc+4*10))=0x7a69732d;
*((unsigned int *)((unsigned long)context_ptr+0x000069cc+4*11))=0x656b2065;
*((unsigned int *)((unsigned long)context_ptr+0x000069cc+4*12))=0x6e612079;
*((unsigned int *)((unsigned long)context_ptr+0x000069cc+4*13))=0x20612064;
*((unsigned int *)((unsigned long)context_ptr+0x000069cc+4*14))=0x6772616c;
*((unsigned int *)((unsigned long)context_ptr+0x000069cc+4*15))=0x74207265;
*((unsigned int *)((unsigned long)context_ptr+0x000069cc+4*16))=0x206e6168;
*((unsigned int *)((unsigned long)context_ptr+0x000069cc+4*17))=0x636f6c62;
*((unsigned int *)((unsigned long)context_ptr+0x000069cc+4*18))=0x69732d6b;
*((unsigned int *)((unsigned long)context_ptr+0x000069cc+4*19))=0x6420657a;
*((unsigned int *)((unsigned long)context_ptr+0x000069cc+4*20))=0x2e617461;
*((unsigned int *)((unsigned long)context_ptr+0x000069cc+4*21))=0x65685420;
*((unsigned int *)((unsigned long)context_ptr+0x000069cc+4*22))=0x79656b20;
*((unsigned int *)((unsigned long)context_ptr+0x000069cc+4*23))=0x65656e20;
*((unsigned int *)((unsigned long)context_ptr+0x000069cc+4*24))=0x74207364;
*((unsigned int *)((unsigned long)context_ptr+0x000069cc+4*25))=0x6562206f;
*((unsigned int *)((unsigned long)context_ptr+0x000069cc+4*26))=0x73616820;
*((unsigned int *)((unsigned long)context_ptr+0x000069cc+4*27))=0x20646568;
*((unsigned int *)((unsigned long)context_ptr+0x000069cc+4*28))=0x6f666562;
*((unsigned int *)((unsigned long)context_ptr+0x000069cc+4*29))=0x62206572;
*((unsigned int *)((unsigned long)context_ptr+0x000069cc+4*30))=0x676e6965;
*((unsigned int *)((unsigned long)context_ptr+0x000069cc+4*31))=0x65737520;
*((unsigned int *)((unsigned long)context_ptr+0x000069cc+4*32))=0x79622064;
*((unsigned int *)((unsigned long)context_ptr+0x000069cc+4*33))=0x65687420;
*((unsigned int *)((unsigned long)context_ptr+0x000069cc+4*34))=0x414d4820;
*((unsigned int *)((unsigned long)context_ptr+0x000069cc+4*35))=0x6c612043;
*((unsigned int *)((unsigned long)context_ptr+0x000069cc+4*36))=0x69726f67;
*((unsigned int *)((unsigned long)context_ptr+0x000069cc+4*37))=0x2e6d6874;
*((unsigned int *)((unsigned long)context_ptr+0x00003168))=0x04c00020;
*((unsigned int *)((unsigned long)context_ptr+0x00003168+4*1))=0x00006490;
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
*((unsigned int *)((unsigned long)context_ptr+0x00000168))=0x04c00098;
*((unsigned int *)((unsigned long)context_ptr+0x00000168+4*1))=0x000069cc;
*((unsigned int *)((unsigned long)context_ptr+0x00000168+4*2))=0x00006480;
*((unsigned int *)((unsigned long)context_ptr+0x00000168+4*3))=0x02220098;
*((unsigned int *)((unsigned long)context_ptr+0x00000168+4*4))=0x0214140f;
*((unsigned int *)((unsigned long)context_ptr+0x00000168+4*5))=0x00006438+(unsigned long)context_ptr;
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x0000000c&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000064fc,"\x10\x4f\xdc\x12\x57\x32\x8f\x08\x18\x4b\xa7\x31\x31\xc5\x3c\xae\xe6\x98\xe3\x61\x19\x42\x11\x49\xea\x8c\x71\x24\x56\x69\x7d\x30",32))
printf("strip: 104fdc1257328f08, Pass\n");
else
printf("strip: 104fdc1257328f08, Failed\n");
writel(0x00000012&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x0000659c,"\x47\x03\x05\xfc\x7e\x40\xfe\x34\xd3\xee\xb3\xe7\x73\xd9\x5a\xab\x73\xac\xf0\xfd\x06\x04\x47\xa5\xeb\x45\x95\xbf\x33\xa9\xd1\xa3",32))
printf("strip: 470305fc7e40fe34, Pass\n");
else
printf("strip: 470305fc7e40fe34, Failed\n");
writel(0x00000018&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000065d4,"\x19\x8a\x60\x7e\xb4\x4b\xfb\xc6\x99\x03\xa0\xf1\xcf\x2b\xbd\xc5\xba\x0a\xa3\xf3\xd9\xae\x3c\x1c\x7a\x3b\x16\x96\xa0\xb6\x8c\xf7",32))
printf("strip: 198a607eb44bfbc6, Pass\n");
else
printf("strip: 198a607eb44bfbc6, Failed\n");
writel(0x0000001e&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x0000660c,"\xb0\x34\x4c\x61\xd8\xdb\x38\x53\x5c\xa8\xaf\xce\xaf\x0b\xf1\x2b\x88\x1d\xc2\x00\xc9\x83\x3d\xa7\x26\xe9\x37\x6c\x2e\x32\xcf\xf7",32))
printf("strip: b0344c61d8db3853, Pass\n");
else
printf("strip: b0344c61d8db3853, Failed\n");
writel(0x00000024&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006658,"\x5b\xdc\xc1\x46\xbf\x60\x75\x4e\x6a\x04\x24\x26\x08\x95\x75\xc7\x5a\x00\x3f\x08\x9d\x27\x39\x83\x9d\xec\x58\xb9\x64\xec\x38\x43",32))
printf("strip: 5bdcc146bf60754e, Pass\n");
else
printf("strip: 5bdcc146bf60754e, Failed\n");
writel(0x0000002a&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000066bc,"\xcd\xcb\x12\x20\xd1\xec\xcc\xea\x91\xe5\x3a\xba\x30\x92\xf9\x62\xe5\x49\xfe\x6c\xe9\xed\x7f\xdc\x43\x19\x1f\xbd\xe4\x5c\x30\xb0",32))
printf("strip: cdcb1220d1ecccea, Pass\n");
else
printf("strip: cdcb1220d1ecccea, Failed\n");
writel(0x00000030&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006720,"\xd4\x63\x3c\x17\xf6\xfb\x8d\x74\x4c\x66\xde\xe0\xf8\xf0\x74\x55\x6e\xc4\xaf\x55\xef\x07\x99\x85\x41\x46\x8e\xb4\x9b\xd2\xe9\x17",32))
printf("strip: d4633c17f6fb8d74, Pass\n");
else
printf("strip: d4633c17f6fb8d74, Failed\n");
writel(0x00000036&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006764,"\x75\x46\xaf\x01\x84\x1f\xc0\x9b\x1a\xb9\xc3\x74\x9a\x5f\x1c\x17\xd4\xf5\x89\x66\x8a\x58\x7b\x27\x00\xa9\xc9\x7c\x11\x93\xcf\x42",32))
printf("strip: 7546af01841fc09b, Pass\n");
else
printf("strip: 7546af01841fc09b, Failed\n");
writel(0x0000003c&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000067cc,"\x69\x53\x02\x5e\xd9\x6f\x0c\x09\xf8\x0a\x96\xf7\x8e\x65\x38\xdb\xe2\xe7\xb8\x20\xe3\xdd\x97\x0e\x7d\xdd\x39\x09\x1b\x32\x35\x2f",32))
printf("strip: 6953025ed96f0c09, Pass\n");
else
printf("strip: 6953025ed96f0c09, Failed\n");
writel(0x00000042&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006848,"\x63\x55\xac\x22\xe8\x90\xd0\xa3\xc8\x48\x1a\x5c\xa4\x82\x5b\xc8\x84\xd3\xe7\xa1\xff\x98\xa2\xfc\x2a\xc7\xd8\xe0\x64\xc3\xb2\xe6",32))
printf("strip: 6355ac22e890d0a3, Pass\n");
else
printf("strip: 6355ac22e890d0a3, Failed\n");
writel(0x00000048&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000068ac,"\x77\x3e\xa9\x1e\x36\x80\x0e\x46\x85\x4d\xb8\xeb\xd0\x91\x81\xa7\x29\x59\x09\x8b\x3e\xf8\xc1\x22\xd9\x63\x55\x14\xce\xd5\x65\xfe",32))
printf("strip: 773ea91e36800e46, Pass\n");
else
printf("strip: 773ea91e36800e46, Failed\n");
writel(0x0000004e&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006910,"\x82\x55\x8a\x38\x9a\x44\x3c\x0e\xa4\xcc\x81\x98\x99\xf2\x08\x3a\x85\xf0\xfa\xa3\xe5\x78\xf8\x07\x7a\x2e\x3f\xf4\x67\x29\x66\x5b",32))
printf("strip: 82558a389a443c0e, Pass\n");
else
printf("strip: 82558a389a443c0e, Failed\n");
writel(0x00000054&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006954,"\xa3\xb6\x16\x74\x73\x10\x0e\xe0\x6e\x0c\x79\x6c\x29\x55\x55\x2b",16))
printf("strip: a3b6167473100ee0, Pass\n");
else
printf("strip: a3b6167473100ee0, Failed\n");
writel(0x0000005a&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x000069ac,"\x60\xe4\x31\x59\x1e\xe0\xb6\x7f\x0d\x8a\x26\xaa\xcb\xf5\xb7\x7f\x8e\x0b\xc6\x21\x37\x28\xc5\x14\x05\x46\x04\x0f\x0e\xe3\x7f\x54",32))
printf("strip: 60e431591ee0b67f, Pass\n");
else
printf("strip: 60e431591ee0b67f, Failed\n");
writel(0x00000060&0xffffffff,ivp_cae_base_addr+0x00000828);
while(1){
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)context_ptr+0x00006490,"\x9b\x09\xff\xa7\x1b\x94\x2f\xcb\x27\x63\x5f\xbc\xd5\xb0\xe9\x44\xbf\xdc\x63\x64\x4f\x07\x13\x93\x8a\x7f\x51\x53\x5c\x3a\x35\xe2",32))
printf("strip: 9b09ffa71b942fcb, Pass\n");
else
printf("strip: 9b09ffa71b942fcb, Failed\n");
}

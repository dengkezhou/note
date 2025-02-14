#include <common.h>
#include <malloc.h>

extern volatile unsigned int ivp_cae_base_addr;

void eip97_reg_test(void)
{
unsigned int *context_ptr=(unsigned int *)0x14000000;
unsigned int cnt=0;
printf("eip97_reg_test\n");
if(!context_ptr)
printf("context_ptr malloc failed!\n");
#if defined(CONFIG_COMPILE_FPGA) || defined(CONFIG_COMPILE_ASIC)
memset(context_ptr,0,64*1024);
#endif
itcs_module_reset(CPU,"cae");
writel(0xa7050f08&0xffffffff,ivp_cae_base_addr+0x0000f000);
writel(0x8000c807&0xffffffff,ivp_cae_base_addr+0x0000f400);
writel(0x00007500&0xffffffff,ivp_cae_base_addr+0x00010100);
writel(0x0000f800&0xffffffff,ivp_cae_base_addr+0x00010000);
writel(0x00000087&0xffffffff,ivp_cae_base_addr+0x00011c00);
writel(0x00410000&0xffffffff,ivp_cae_base_addr+0x00011000);
writel(0x00000225&0xffffffff,ivp_cae_base_addr+0x00011008);
itcs_module_reset(CPU,"cae");
if((readl(ivp_cae_base_addr+0x00000000)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 1\n");
if((readl(ivp_cae_base_addr+0x00000004)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 2\n");
if((readl(ivp_cae_base_addr+0x00000008)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 3\n");
if((readl(ivp_cae_base_addr+0x0000000c)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 4\n");
if((readl(ivp_cae_base_addr+0x00000010)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 5\n");
if((readl(ivp_cae_base_addr+0x00000014)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 6\n");
if((readl(ivp_cae_base_addr+0x00000018)&0x00fffffc)==(0x00000000&0x00fffffc))
cnt++;
else
printf("cnt: 7\n");
if((readl(ivp_cae_base_addr+0x0000001c)&0xe0ff003f)==(0x00000000&0xe0ff003f))
cnt++;
else
printf("cnt: 8\n");
if((readl(ivp_cae_base_addr+0x00000020)&0xf03f00ff)==(0x00000000&0xf03f00ff))
cnt++;
else
printf("cnt: 9\n");
if((readl(ivp_cae_base_addr+0x00000024)&0xff010101)==(0x01000000&0xff010101))
cnt++;
else
printf("cnt: 10\n");
if((readl(ivp_cae_base_addr+0x00000028)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 11\n");
if((readl(ivp_cae_base_addr+0x0000002c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 12\n");
if((readl(ivp_cae_base_addr+0x00000030)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 13\n");
if((readl(ivp_cae_base_addr+0x00000034)&0x00fffffc)==(0x00000000&0x00fffffc))
cnt++;
else
printf("cnt: 14\n");
if((readl(ivp_cae_base_addr+0x00000038)&0x00fffffc)==(0x00000000&0x00fffffc))
cnt++;
else
printf("cnt: 15\n");
if((readl(ivp_cae_base_addr+0x0000003c)&0xcfff0100)==(0x00200000&0xcfff0100))
cnt++;
else
printf("cnt: 16\n");
if((readl(ivp_cae_base_addr+0x000007f8)&0xb7ffffff)==(0x80a35514&0xb7ffffff))
cnt++;
else
printf("cnt: 17\n");
if((readl(ivp_cae_base_addr+0x000007fc)&0x0fffffff)==(0x027035ca&0x0fffffff))
cnt++;
else
printf("cnt: 18\n");
if((readl(ivp_cae_base_addr+0x00000800)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 19\n");
if((readl(ivp_cae_base_addr+0x00000804)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 20\n");
if((readl(ivp_cae_base_addr+0x00000808)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 21\n");
if((readl(ivp_cae_base_addr+0x0000080c)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 22\n");
if((readl(ivp_cae_base_addr+0x00000818)&0x00fffffc)==(0x00000000&0x00fffffc))
cnt++;
else
printf("cnt: 23\n");
if((readl(ivp_cae_base_addr+0x0000081c)&0xe0ff00ff)==(0x00000000&0xe0ff00ff))
cnt++;
else
printf("cnt: 24\n");
if((readl(ivp_cae_base_addr+0x00000820)&0xf03f00ff)==(0x00000000&0xf03f00ff))
cnt++;
else
printf("cnt: 25\n");
if((readl(ivp_cae_base_addr+0x00000824)&0xfff80101)==(0x01800000&0xfff80101))
cnt++;
else
printf("cnt: 26\n");
if((readl(ivp_cae_base_addr+0x00000828)&0xffbfffff)==(0x00000000&0xffbfffff))
cnt++;
else
printf("cnt: 27\n");
if((readl(ivp_cae_base_addr+0x0000082c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 28\n");
if((readl(ivp_cae_base_addr+0x00000830)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 29\n");
if((readl(ivp_cae_base_addr+0x00000834)&0x00fffffc)==(0x00000000&0x00fffffc))
cnt++;
else
printf("cnt: 30\n");
if((readl(ivp_cae_base_addr+0x00000838)&0x00fffffc)==(0x00000000&0x00fffffc))
cnt++;
else
printf("cnt: 31\n");
if((readl(ivp_cae_base_addr+0x0000083c)&0xafff1f00)==(0x00200000&0xafff1f00))
cnt++;
else
printf("cnt: 32\n");
if((readl(ivp_cae_base_addr+0x00000ff8)&0xb7ffffff)==(0x80a35514&0xb7ffffff))
cnt++;
else
printf("cnt: 33\n");
if((readl(ivp_cae_base_addr+0x00000ffc)&0x0fffffff)==(0x027035ca&0x0fffffff))
cnt++;
else
printf("cnt: 34\n");
if((readl(ivp_cae_base_addr+0x00001000)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 35\n");
if((readl(ivp_cae_base_addr+0x00001004)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 36\n");
if((readl(ivp_cae_base_addr+0x00001008)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 37\n");
if((readl(ivp_cae_base_addr+0x0000100c)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 38\n");
if((readl(ivp_cae_base_addr+0x00001010)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 39\n");
if((readl(ivp_cae_base_addr+0x00001014)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 40\n");
if((readl(ivp_cae_base_addr+0x00001018)&0x00fffffc)==(0x00000000&0x00fffffc))
cnt++;
else
printf("cnt: 41\n");
if((readl(ivp_cae_base_addr+0x0000101c)&0xe0ff003f)==(0x00000000&0xe0ff003f))
cnt++;
else
printf("cnt: 42\n");
if((readl(ivp_cae_base_addr+0x00001020)&0xf03f00ff)==(0x00000000&0xf03f00ff))
cnt++;
else
printf("cnt: 43\n");
if((readl(ivp_cae_base_addr+0x00001024)&0xff010101)==(0x01000000&0xff010101))
cnt++;
else
printf("cnt: 44\n");
if((readl(ivp_cae_base_addr+0x00001028)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 45\n");
if((readl(ivp_cae_base_addr+0x0000102c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 46\n");
if((readl(ivp_cae_base_addr+0x00001030)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 47\n");
if((readl(ivp_cae_base_addr+0x00001034)&0x00fffffc)==(0x00000000&0x00fffffc))
cnt++;
else
printf("cnt: 48\n");
if((readl(ivp_cae_base_addr+0x00001038)&0x00fffffc)==(0x00000000&0x00fffffc))
cnt++;
else
printf("cnt: 49\n");
if((readl(ivp_cae_base_addr+0x0000103c)&0xcfff0100)==(0x00200000&0xcfff0100))
cnt++;
else
printf("cnt: 50\n");
if((readl(ivp_cae_base_addr+0x000017f8)&0xb7ffffff)==(0x80a35514&0xb7ffffff))
cnt++;
else
printf("cnt: 51\n");
if((readl(ivp_cae_base_addr+0x000017fc)&0x0fffffff)==(0x027035ca&0x0fffffff))
cnt++;
else
printf("cnt: 52\n");
if((readl(ivp_cae_base_addr+0x00001800)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 53\n");
if((readl(ivp_cae_base_addr+0x00001804)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 54\n");
if((readl(ivp_cae_base_addr+0x00001808)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 55\n");
if((readl(ivp_cae_base_addr+0x0000180c)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 56\n");
if((readl(ivp_cae_base_addr+0x00001818)&0x00fffffc)==(0x00000000&0x00fffffc))
cnt++;
else
printf("cnt: 57\n");
if((readl(ivp_cae_base_addr+0x0000181c)&0xe0ff00ff)==(0x00000000&0xe0ff00ff))
cnt++;
else
printf("cnt: 58\n");
if((readl(ivp_cae_base_addr+0x00001820)&0xf03f00ff)==(0x00000000&0xf03f00ff))
cnt++;
else
printf("cnt: 59\n");
if((readl(ivp_cae_base_addr+0x00001824)&0xfff80101)==(0x01800000&0xfff80101))
cnt++;
else
printf("cnt: 60\n");
if((readl(ivp_cae_base_addr+0x00001828)&0xffbfffff)==(0x00000000&0xffbfffff))
cnt++;
else
printf("cnt: 61\n");
if((readl(ivp_cae_base_addr+0x0000182c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 62\n");
if((readl(ivp_cae_base_addr+0x00001830)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 63\n");
if((readl(ivp_cae_base_addr+0x00001834)&0x00fffffc)==(0x00000000&0x00fffffc))
cnt++;
else
printf("cnt: 64\n");
if((readl(ivp_cae_base_addr+0x00001838)&0x00fffffc)==(0x00000000&0x00fffffc))
cnt++;
else
printf("cnt: 65\n");
if((readl(ivp_cae_base_addr+0x0000183c)&0xafff1f00)==(0x00200000&0xafff1f00))
cnt++;
else
printf("cnt: 66\n");
if((readl(ivp_cae_base_addr+0x00001ff8)&0xb7ffffff)==(0x80a35514&0xb7ffffff))
cnt++;
else
printf("cnt: 67\n");
if((readl(ivp_cae_base_addr+0x00001ffc)&0x0fffffff)==(0x027035ca&0x0fffffff))
cnt++;
else
printf("cnt: 68\n");
if((readl(ivp_cae_base_addr+0x00002000)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 69\n");
if((readl(ivp_cae_base_addr+0x00002004)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 70\n");
if((readl(ivp_cae_base_addr+0x00002008)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 71\n");
if((readl(ivp_cae_base_addr+0x0000200c)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 72\n");
if((readl(ivp_cae_base_addr+0x00002010)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 73\n");
if((readl(ivp_cae_base_addr+0x00002014)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 74\n");
if((readl(ivp_cae_base_addr+0x00002018)&0x00fffffc)==(0x00000000&0x00fffffc))
cnt++;
else
printf("cnt: 75\n");
if((readl(ivp_cae_base_addr+0x0000201c)&0xe0ff003f)==(0x00000000&0xe0ff003f))
cnt++;
else
printf("cnt: 76\n");
if((readl(ivp_cae_base_addr+0x00002020)&0xf03f00ff)==(0x00000000&0xf03f00ff))
cnt++;
else
printf("cnt: 77\n");
if((readl(ivp_cae_base_addr+0x00002024)&0xff010101)==(0x01000000&0xff010101))
cnt++;
else
printf("cnt: 78\n");
if((readl(ivp_cae_base_addr+0x00002028)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 79\n");
if((readl(ivp_cae_base_addr+0x0000202c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 80\n");
if((readl(ivp_cae_base_addr+0x00002030)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 81\n");
if((readl(ivp_cae_base_addr+0x00002034)&0x00fffffc)==(0x00000000&0x00fffffc))
cnt++;
else
printf("cnt: 82\n");
if((readl(ivp_cae_base_addr+0x00002038)&0x00fffffc)==(0x00000000&0x00fffffc))
cnt++;
else
printf("cnt: 83\n");
if((readl(ivp_cae_base_addr+0x0000203c)&0xcfff0100)==(0x00200000&0xcfff0100))
cnt++;
else
printf("cnt: 84\n");
if((readl(ivp_cae_base_addr+0x000027f8)&0xb7ffffff)==(0x80a35514&0xb7ffffff))
cnt++;
else
printf("cnt: 85\n");
if((readl(ivp_cae_base_addr+0x000027fc)&0x0fffffff)==(0x027035ca&0x0fffffff))
cnt++;
else
printf("cnt: 86\n");
if((readl(ivp_cae_base_addr+0x00002800)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 87\n");
if((readl(ivp_cae_base_addr+0x00002804)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 88\n");
if((readl(ivp_cae_base_addr+0x00002808)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 89\n");
if((readl(ivp_cae_base_addr+0x0000280c)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 90\n");
if((readl(ivp_cae_base_addr+0x00002818)&0x00fffffc)==(0x00000000&0x00fffffc))
cnt++;
else
printf("cnt: 91\n");
if((readl(ivp_cae_base_addr+0x0000281c)&0xe0ff00ff)==(0x00000000&0xe0ff00ff))
cnt++;
else
printf("cnt: 92\n");
if((readl(ivp_cae_base_addr+0x00002820)&0xf03f00ff)==(0x00000000&0xf03f00ff))
cnt++;
else
printf("cnt: 93\n");
if((readl(ivp_cae_base_addr+0x00002824)&0xfff80101)==(0x01800000&0xfff80101))
cnt++;
else
printf("cnt: 94\n");
if((readl(ivp_cae_base_addr+0x00002828)&0xffbfffff)==(0x00000000&0xffbfffff))
cnt++;
else
printf("cnt: 95\n");
if((readl(ivp_cae_base_addr+0x0000282c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 96\n");
if((readl(ivp_cae_base_addr+0x00002830)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 97\n");
if((readl(ivp_cae_base_addr+0x00002834)&0x00fffffc)==(0x00000000&0x00fffffc))
cnt++;
else
printf("cnt: 98\n");
if((readl(ivp_cae_base_addr+0x00002838)&0x00fffffc)==(0x00000000&0x00fffffc))
cnt++;
else
printf("cnt: 99\n");
if((readl(ivp_cae_base_addr+0x0000283c)&0xafff1f00)==(0x00200000&0xafff1f00))
cnt++;
else
printf("cnt: 100\n");
if((readl(ivp_cae_base_addr+0x00002ff8)&0xb7ffffff)==(0x80a35514&0xb7ffffff))
cnt++;
else
printf("cnt: 101\n");
if((readl(ivp_cae_base_addr+0x00002ffc)&0x0fffffff)==(0x027035ca&0x0fffffff))
cnt++;
else
printf("cnt: 102\n");
if((readl(ivp_cae_base_addr+0x00003000)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 103\n");
if((readl(ivp_cae_base_addr+0x00003004)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 104\n");
if((readl(ivp_cae_base_addr+0x00003008)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 105\n");
if((readl(ivp_cae_base_addr+0x0000300c)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 106\n");
if((readl(ivp_cae_base_addr+0x00003010)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 107\n");
if((readl(ivp_cae_base_addr+0x00003014)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 108\n");
if((readl(ivp_cae_base_addr+0x00003018)&0x00fffffc)==(0x00000000&0x00fffffc))
cnt++;
else
printf("cnt: 109\n");
if((readl(ivp_cae_base_addr+0x0000301c)&0xe0ff003f)==(0x00000000&0xe0ff003f))
cnt++;
else
printf("cnt: 110\n");
if((readl(ivp_cae_base_addr+0x00003020)&0xf03f00ff)==(0x00000000&0xf03f00ff))
cnt++;
else
printf("cnt: 111\n");
if((readl(ivp_cae_base_addr+0x00003024)&0xff010101)==(0x01000000&0xff010101))
cnt++;
else
printf("cnt: 112\n");
if((readl(ivp_cae_base_addr+0x00003028)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 113\n");
if((readl(ivp_cae_base_addr+0x0000302c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 114\n");
if((readl(ivp_cae_base_addr+0x00003030)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 115\n");
if((readl(ivp_cae_base_addr+0x00003034)&0x00fffffc)==(0x00000000&0x00fffffc))
cnt++;
else
printf("cnt: 116\n");
if((readl(ivp_cae_base_addr+0x00003038)&0x00fffffc)==(0x00000000&0x00fffffc))
cnt++;
else
printf("cnt: 117\n");
if((readl(ivp_cae_base_addr+0x0000303c)&0xcfff0100)==(0x00200000&0xcfff0100))
cnt++;
else
printf("cnt: 118\n");
if((readl(ivp_cae_base_addr+0x000037f8)&0xb7ffffff)==(0x80a35514&0xb7ffffff))
cnt++;
else
printf("cnt: 119\n");
if((readl(ivp_cae_base_addr+0x000037fc)&0x0fffffff)==(0x027035ca&0x0fffffff))
cnt++;
else
printf("cnt: 120\n");
if((readl(ivp_cae_base_addr+0x00003800)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 121\n");
if((readl(ivp_cae_base_addr+0x00003804)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 122\n");
if((readl(ivp_cae_base_addr+0x00003808)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 123\n");
if((readl(ivp_cae_base_addr+0x0000380c)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 124\n");
if((readl(ivp_cae_base_addr+0x00003818)&0x00fffffc)==(0x00000000&0x00fffffc))
cnt++;
else
printf("cnt: 125\n");
if((readl(ivp_cae_base_addr+0x0000381c)&0xe0ff00ff)==(0x00000000&0xe0ff00ff))
cnt++;
else
printf("cnt: 126\n");
if((readl(ivp_cae_base_addr+0x00003820)&0xf03f00ff)==(0x00000000&0xf03f00ff))
cnt++;
else
printf("cnt: 127\n");
if((readl(ivp_cae_base_addr+0x00003824)&0xfff80101)==(0x01800000&0xfff80101))
cnt++;
else
printf("cnt: 128\n");
if((readl(ivp_cae_base_addr+0x00003828)&0xffbfffff)==(0x00000000&0xffbfffff))
cnt++;
else
printf("cnt: 129\n");
if((readl(ivp_cae_base_addr+0x0000382c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 130\n");
if((readl(ivp_cae_base_addr+0x00003830)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 131\n");
if((readl(ivp_cae_base_addr+0x00003834)&0x00fffffc)==(0x00000000&0x00fffffc))
cnt++;
else
printf("cnt: 132\n");
if((readl(ivp_cae_base_addr+0x00003838)&0x00fffffc)==(0x00000000&0x00fffffc))
cnt++;
else
printf("cnt: 133\n");
if((readl(ivp_cae_base_addr+0x0000383c)&0xafff1f00)==(0x00200000&0xafff1f00))
cnt++;
else
printf("cnt: 134\n");
if((readl(ivp_cae_base_addr+0x00003ff8)&0xb7ffffff)==(0x80a35514&0xb7ffffff))
cnt++;
else
printf("cnt: 135\n");
if((readl(ivp_cae_base_addr+0x00003ffc)&0x0fffffff)==(0x027035ca&0x0fffffff))
cnt++;
else
printf("cnt: 136\n");
if((readl(ivp_cae_base_addr+0x0000b000)&0x000000ff)==(0x00000000&0x000000ff))
cnt++;
else
printf("cnt: 137\n");
if((readl(ivp_cae_base_addr+0x0000b004)&0x000000ff)==(0x00000000&0x000000ff))
cnt++;
else
printf("cnt: 138\n");
if((readl(ivp_cae_base_addr+0x0000b008)&0x000000ff)==(0x00000000&0x000000ff))
cnt++;
else
printf("cnt: 139\n");
if((readl(ivp_cae_base_addr+0x0000b00c)&0x000000ff)==(0x00000000&0x000000ff))
cnt++;
else
printf("cnt: 140\n");
if((readl(ivp_cae_base_addr+0x0000b010)&0x000000ff)==(0x00000000&0x000000ff))
cnt++;
else
printf("cnt: 141\n");
if((readl(ivp_cae_base_addr+0x0000b014)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 142\n");
if((readl(ivp_cae_base_addr+0x0000b018)&0x000001bf)==(0x00000008&0x000001bf))
cnt++;
else
printf("cnt: 143\n");
if((readl(ivp_cae_base_addr+0x0000b01c)&0x0fffffff)==(0x014036c9&0x0fffffff))
cnt++;
else
printf("cnt: 144\n");
if((readl(ivp_cae_base_addr+0x0000c000)&0x000000ff)==(0x00000000&0x000000ff))
cnt++;
else
printf("cnt: 145\n");
if((readl(ivp_cae_base_addr+0x0000c004)&0x000000ff)==(0x00000000&0x000000ff))
cnt++;
else
printf("cnt: 146\n");
if((readl(ivp_cae_base_addr+0x0000c008)&0x000000ff)==(0x00000000&0x000000ff))
cnt++;
else
printf("cnt: 147\n");
if((readl(ivp_cae_base_addr+0x0000c00c)&0x000000ff)==(0x00000000&0x000000ff))
cnt++;
else
printf("cnt: 148\n");
if((readl(ivp_cae_base_addr+0x0000c010)&0x000000ff)==(0x00000000&0x000000ff))
cnt++;
else
printf("cnt: 149\n");
if((readl(ivp_cae_base_addr+0x0000c014)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 150\n");
if((readl(ivp_cae_base_addr+0x0000c018)&0x000001bf)==(0x00000008&0x000001bf))
cnt++;
else
printf("cnt: 151\n");
if((readl(ivp_cae_base_addr+0x0000c01c)&0x0fffffff)==(0x014036c9&0x0fffffff))
cnt++;
else
printf("cnt: 152\n");
if((readl(ivp_cae_base_addr+0x0000d000)&0x000000ff)==(0x00000000&0x000000ff))
cnt++;
else
printf("cnt: 153\n");
if((readl(ivp_cae_base_addr+0x0000d004)&0x000000ff)==(0x00000000&0x000000ff))
cnt++;
else
printf("cnt: 154\n");
if((readl(ivp_cae_base_addr+0x0000d008)&0x000000ff)==(0x00000000&0x000000ff))
cnt++;
else
printf("cnt: 155\n");
if((readl(ivp_cae_base_addr+0x0000d00c)&0x000000ff)==(0x00000000&0x000000ff))
cnt++;
else
printf("cnt: 156\n");
if((readl(ivp_cae_base_addr+0x0000d010)&0x000000ff)==(0x00000000&0x000000ff))
cnt++;
else
printf("cnt: 157\n");
if((readl(ivp_cae_base_addr+0x0000d014)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 158\n");
if((readl(ivp_cae_base_addr+0x0000d018)&0x000001bf)==(0x00000008&0x000001bf))
cnt++;
else
printf("cnt: 159\n");
if((readl(ivp_cae_base_addr+0x0000d01c)&0x0fffffff)==(0x014036c9&0x0fffffff))
cnt++;
else
printf("cnt: 160\n");
if((readl(ivp_cae_base_addr+0x0000e000)&0x000000ff)==(0x00000000&0x000000ff))
cnt++;
else
printf("cnt: 161\n");
if((readl(ivp_cae_base_addr+0x0000e004)&0x000000ff)==(0x00000000&0x000000ff))
cnt++;
else
printf("cnt: 162\n");
if((readl(ivp_cae_base_addr+0x0000e008)&0x000000ff)==(0x00000000&0x000000ff))
cnt++;
else
printf("cnt: 163\n");
if((readl(ivp_cae_base_addr+0x0000e00c)&0x000000ff)==(0x00000000&0x000000ff))
cnt++;
else
printf("cnt: 164\n");
if((readl(ivp_cae_base_addr+0x0000e010)&0x000000ff)==(0x00000000&0x000000ff))
cnt++;
else
printf("cnt: 165\n");
if((readl(ivp_cae_base_addr+0x0000e014)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 166\n");
if((readl(ivp_cae_base_addr+0x0000e018)&0x000001bf)==(0x00000008&0x000001bf))
cnt++;
else
printf("cnt: 167\n");
if((readl(ivp_cae_base_addr+0x0000e01c)&0x0fffffff)==(0x014036c9&0x0fffffff))
cnt++;
else
printf("cnt: 168\n");
if((readl(ivp_cae_base_addr+0x0000f000)&0xefff0fff)==(0x80000000&0xefff0fff))
cnt++;
else
printf("cnt: 169\n");
if((readl(ivp_cae_base_addr+0x0000f010)&0x8f8f8f8f)==(0x00000000&0x8f8f8f8f))
cnt++;
else
printf("cnt: 170\n");
if((readl(ivp_cae_base_addr+0x0000f078)&0xb7ffffff)==(0x80a35514&0xb7ffffff))
cnt++;
else
printf("cnt: 171\n");
if((readl(ivp_cae_base_addr+0x0000f07c)&0x0fffffff)==(0x027035ca&0x0fffffff))
cnt++;
else
printf("cnt: 172\n");
if((readl(ivp_cae_base_addr+0x0000f200)&0xe000000f)==(0x00000000&0xe000000f))
cnt++;
else
printf("cnt: 173\n");
if((readl(ivp_cae_base_addr+0x0000f204)&0xbfffffff)==(0x0000f000&0xbfffffff))
cnt++;
else
printf("cnt: 174\n");
if((readl(ivp_cae_base_addr+0x0000f208)&0xffc1ffff)==(0x00000000&0xffc1ffff))
cnt++;
else
printf("cnt: 175\n");
if((readl(ivp_cae_base_addr+0x0000f210)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 176\n");
if((readl(ivp_cae_base_addr+0x0000f214)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 177\n");
if((readl(ivp_cae_base_addr+0x0000f218)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 178\n");
if((readl(ivp_cae_base_addr+0x0000f21c)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 179\n");
if((readl(ivp_cae_base_addr+0x0000f400)&0xf000dfff)==(0x8000c000&0xf000dfff))
cnt++;
else
printf("cnt: 180\n");
if((readl(ivp_cae_base_addr+0x0000f478)&0xb7ffffff)==(0x80a35514&0xb7ffffff))
cnt++;
else
printf("cnt: 181\n");
if((readl(ivp_cae_base_addr+0x0000f47c)&0x0fffffff)==(0x027035ca&0x0fffffff))
cnt++;
else
printf("cnt: 182\n");
if((readl(ivp_cae_base_addr+0x0000f600)&0xe000000f)==(0x00000000&0xe000000f))
cnt++;
else
printf("cnt: 183\n");
if((readl(ivp_cae_base_addr+0x0000f604)&0xbfffffff)==(0x0000f000&0xbfffffff))
cnt++;
else
printf("cnt: 184\n");
if((readl(ivp_cae_base_addr+0x0000f608)&0xffc1ffff)==(0x00000000&0xffc1ffff))
cnt++;
else
printf("cnt: 185\n");
if((readl(ivp_cae_base_addr+0x0000f60c)&0xffc1ffff)==(0x00000000&0xffc1ffff))
cnt++;
else
printf("cnt: 186\n");
if((readl(ivp_cae_base_addr+0x0000f610)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 187\n");
if((readl(ivp_cae_base_addr+0x0000f614)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 188\n");
if((readl(ivp_cae_base_addr+0x0000f618)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 189\n");
if((readl(ivp_cae_base_addr+0x0000f61c)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 190\n");
if((readl(ivp_cae_base_addr+0x0000f620)&0x0000000f)==(0x00000000&0x0000000f))
cnt++;
else
printf("cnt: 191\n");
if((readl(ivp_cae_base_addr+0x0000f628)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 192\n");
if((readl(ivp_cae_base_addr+0x0000f62c)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 193\n");
if((readl(ivp_cae_base_addr+0x0000f800)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 194\n");
if((readl(ivp_cae_base_addr+0x0000f804)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 195\n");
if((readl(ivp_cae_base_addr+0x0000f808)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 196\n");
if((readl(ivp_cae_base_addr+0x0000f80c)&0xffffffff)==(0x40000000&0xffffffff))
cnt++;
else
printf("cnt: 197\n");
if((readl(ivp_cae_base_addr+0x0000f810)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 198\n");
if((readl(ivp_cae_base_addr+0x0000f814)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 199\n");
if((readl(ivp_cae_base_addr+0x0000f818)&0x000001bf)==(0x00000020&0x000001bf))
cnt++;
else
printf("cnt: 200\n");
if((readl(ivp_cae_base_addr+0x0000f81c)&0x0fffffff)==(0x014036c9&0x0fffffff))
cnt++;
else
printf("cnt: 201\n");
if((readl(ivp_cae_base_addr+0x0000fff4)&0x03fffff1)==(0x02000040&0x03fffff1))
cnt++;
else
printf("cnt: 202\n");
if((readl(ivp_cae_base_addr+0x0000fff8)&0xb7ffffff)==(0x80a35514&0xb7ffffff))
cnt++;
else
printf("cnt: 203\n");
if((readl(ivp_cae_base_addr+0x0000fffc)&0x0fffffff)==(0x027035ca&0x0fffffff))
cnt++;
else
printf("cnt: 204\n");
if((readl(ivp_cae_base_addr+0x00010000)&0xdfffff00)==(0x00008700&0xdfffff00))
cnt++;
else
printf("cnt: 205\n");
if((readl(ivp_cae_base_addr+0x00010100)&0x8000ff00)==(0x00006500&0x8000ff00))
cnt++;
else
printf("cnt: 206\n");
if((readl(ivp_cae_base_addr+0x00011000)&0xfffbffff)==(0x00004004&0xfffbffff))
cnt++;
else
printf("cnt: 207\n");
if((readl(ivp_cae_base_addr+0x00011004)&0xffffffff)==(0xffffffff&0xffffffff))
cnt++;
else
printf("cnt: 208\n");
if((readl(ivp_cae_base_addr+0x00011008)&0x0000033f)==(0x00000235&0x0000033f))
cnt++;
else
printf("cnt: 209\n");
if((readl(ivp_cae_base_addr+0x0001100c)&0xff3f7fff)==(0x00000000&0xff3f7fff))
cnt++;
else
printf("cnt: 210\n");
if((readl(ivp_cae_base_addr+0x00011018)&0xffffff00)==(0xfe400400&0xffffff00))
cnt++;
else
printf("cnt: 211\n");
if((readl(ivp_cae_base_addr+0x0001101c)&0xc00000f8)==(0x00000000&0xc00000f8))
cnt++;
else
printf("cnt: 212\n");
if((readl(ivp_cae_base_addr+0x00011020)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 213\n");
if((readl(ivp_cae_base_addr+0x00011024)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 214\n");
if((readl(ivp_cae_base_addr+0x00011028)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 215\n");
if((readl(ivp_cae_base_addr+0x0001102c)&0x0000000f)==(0x00000000&0x0000000f))
cnt++;
else
printf("cnt: 216\n");
if((readl(ivp_cae_base_addr+0x00011030)&0xffffffff)==(0xffffffff&0xffffffff))
cnt++;
else
printf("cnt: 217\n");
if((readl(ivp_cae_base_addr+0x00011040)&0x00000003)==(0x00000000&0x00000003))
cnt++;
else
printf("cnt: 218\n");
if((readl(ivp_cae_base_addr+0x00011044)&0x00000006)==(0x00000000&0x00000006))
cnt++;
else
printf("cnt: 219\n");
if((readl(ivp_cae_base_addr+0x00011048)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 220\n");
if((readl(ivp_cae_base_addr+0x0001104c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 221\n");
if((readl(ivp_cae_base_addr+0x00011050)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 222\n");
if((readl(ivp_cae_base_addr+0x00011054)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 223\n");
if((readl(ivp_cae_base_addr+0x00011058)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 224\n");
if((readl(ivp_cae_base_addr+0x0001105c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 225\n");
if((readl(ivp_cae_base_addr+0x00011060)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 226\n");
if((readl(ivp_cae_base_addr+0x00011064)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 227\n");
if((readl(ivp_cae_base_addr+0x00011068)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 228\n");
if((readl(ivp_cae_base_addr+0x0001106c)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 229\n");
if((readl(ivp_cae_base_addr+0x00011070)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 230\n");
if((readl(ivp_cae_base_addr+0x00011074)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 231\n");
if((readl(ivp_cae_base_addr+0x00011080)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 232\n");
if((readl(ivp_cae_base_addr+0x00011084)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 233\n");
if((readl(ivp_cae_base_addr+0x00011088)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 234\n");
if((readl(ivp_cae_base_addr+0x0001108c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 235\n");
if((readl(ivp_cae_base_addr+0x00011090)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 236\n");
if((readl(ivp_cae_base_addr+0x00011094)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 237\n");
if((readl(ivp_cae_base_addr+0x00011098)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 238\n");
if((readl(ivp_cae_base_addr+0x0001109c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 239\n");
if((readl(ivp_cae_base_addr+0x000110a0)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 240\n");
if((readl(ivp_cae_base_addr+0x000110a4)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 241\n");
if((readl(ivp_cae_base_addr+0x000110a8)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 242\n");
if((readl(ivp_cae_base_addr+0x000110ac)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 243\n");
if((readl(ivp_cae_base_addr+0x000110b0)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 244\n");
if((readl(ivp_cae_base_addr+0x000110b4)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 245\n");
if((readl(ivp_cae_base_addr+0x000110b8)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 246\n");
if((readl(ivp_cae_base_addr+0x000110bc)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 247\n");
if((readl(ivp_cae_base_addr+0x000110c0)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 248\n");
if((readl(ivp_cae_base_addr+0x000110c4)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 249\n");
if((readl(ivp_cae_base_addr+0x000110c8)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 250\n");
if((readl(ivp_cae_base_addr+0x000110cc)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 251\n");
if((readl(ivp_cae_base_addr+0x000110d0)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 252\n");
if((readl(ivp_cae_base_addr+0x000110d4)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 253\n");
if((readl(ivp_cae_base_addr+0x000110d8)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 254\n");
if((readl(ivp_cae_base_addr+0x000110dc)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 255\n");
if((readl(ivp_cae_base_addr+0x000110e0)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 256\n");
if((readl(ivp_cae_base_addr+0x000110e4)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 257\n");
if((readl(ivp_cae_base_addr+0x000110e8)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 258\n");
if((readl(ivp_cae_base_addr+0x000110ec)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 259\n");
if((readl(ivp_cae_base_addr+0x000110f0)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 260\n");
if((readl(ivp_cae_base_addr+0x000110f4)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 261\n");
if((readl(ivp_cae_base_addr+0x000110f8)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 262\n");
if((readl(ivp_cae_base_addr+0x000110fc)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 263\n");
if((readl(ivp_cae_base_addr+0x00011100)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 264\n");
if((readl(ivp_cae_base_addr+0x00011104)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 265\n");
if((readl(ivp_cae_base_addr+0x00011108)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 266\n");
if((readl(ivp_cae_base_addr+0x0001110c)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 267\n");
if((readl(ivp_cae_base_addr+0x00011110)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 268\n");
if((readl(ivp_cae_base_addr+0x00011114)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 269\n");
if((readl(ivp_cae_base_addr+0x00011118)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 270\n");
if((readl(ivp_cae_base_addr+0x0001111c)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 271\n");
if((readl(ivp_cae_base_addr+0x00011140)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 272\n");
if((readl(ivp_cae_base_addr+0x00011144)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 273\n");
if((readl(ivp_cae_base_addr+0x00011148)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 274\n");
if((readl(ivp_cae_base_addr+0x0001114c)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 275\n");
if((readl(ivp_cae_base_addr+0x00011150)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 276\n");
if((readl(ivp_cae_base_addr+0x00011154)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 277\n");
if((readl(ivp_cae_base_addr+0x00011158)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 278\n");
if((readl(ivp_cae_base_addr+0x0001115c)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 279\n");
if((readl(ivp_cae_base_addr+0x00011160)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 280\n");
if((readl(ivp_cae_base_addr+0x00011164)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 281\n");
if((readl(ivp_cae_base_addr+0x00011168)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 282\n");
if((readl(ivp_cae_base_addr+0x0001116c)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 283\n");
if((readl(ivp_cae_base_addr+0x00011170)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 284\n");
if((readl(ivp_cae_base_addr+0x00011174)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 285\n");
if((readl(ivp_cae_base_addr+0x00011178)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 286\n");
if((readl(ivp_cae_base_addr+0x0001117c)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 287\n");
if((readl(ivp_cae_base_addr+0x00011180)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 288\n");
if((readl(ivp_cae_base_addr+0x00011184)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 289\n");
if((readl(ivp_cae_base_addr+0x00011188)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 290\n");
if((readl(ivp_cae_base_addr+0x0001118c)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 291\n");
if((readl(ivp_cae_base_addr+0x00011190)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 292\n");
if((readl(ivp_cae_base_addr+0x00011194)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 293\n");
if((readl(ivp_cae_base_addr+0x00011198)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 294\n");
if((readl(ivp_cae_base_addr+0x0001119c)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 295\n");
if((readl(ivp_cae_base_addr+0x000111a0)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 296\n");
if((readl(ivp_cae_base_addr+0x000111a4)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 297\n");
if((readl(ivp_cae_base_addr+0x000111a8)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 298\n");
if((readl(ivp_cae_base_addr+0x000111ac)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 299\n");
if((readl(ivp_cae_base_addr+0x000111b0)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 300\n");
if((readl(ivp_cae_base_addr+0x000111b4)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 301\n");
if((readl(ivp_cae_base_addr+0x000111b8)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 302\n");
if((readl(ivp_cae_base_addr+0x000111bc)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 303\n");
if((readl(ivp_cae_base_addr+0x000111c0)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 304\n");
if((readl(ivp_cae_base_addr+0x000111c4)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 305\n");
if((readl(ivp_cae_base_addr+0x000111c8)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 306\n");
if((readl(ivp_cae_base_addr+0x000111cc)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 307\n");
if((readl(ivp_cae_base_addr+0x000111d0)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 308\n");
if((readl(ivp_cae_base_addr+0x000111d4)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 309\n");
if((readl(ivp_cae_base_addr+0x000111d8)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 310\n");
if((readl(ivp_cae_base_addr+0x000111dc)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 311\n");
if((readl(ivp_cae_base_addr+0x000111e4)&0x0000ffff)==(0x00000000&0x0000ffff))
cnt++;
else
printf("cnt: 312\n");
if((readl(ivp_cae_base_addr+0x00011200)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 313\n");
if((readl(ivp_cae_base_addr+0x00011204)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 314\n");
if((readl(ivp_cae_base_addr+0x00011208)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 315\n");
if((readl(ivp_cae_base_addr+0x0001120c)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 316\n");
if((readl(ivp_cae_base_addr+0x00011210)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 317\n");
if((readl(ivp_cae_base_addr+0x00011214)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 318\n");
if((readl(ivp_cae_base_addr+0x00011218)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 319\n");
if((readl(ivp_cae_base_addr+0x0001121c)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 320\n");
if((readl(ivp_cae_base_addr+0x00011220)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 321\n");
if((readl(ivp_cae_base_addr+0x00011224)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 322\n");
if((readl(ivp_cae_base_addr+0x00011228)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 323\n");
if((readl(ivp_cae_base_addr+0x0001122c)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 324\n");
if((readl(ivp_cae_base_addr+0x00011230)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 325\n");
if((readl(ivp_cae_base_addr+0x00011234)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 326\n");
if((readl(ivp_cae_base_addr+0x00011238)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 327\n");
if((readl(ivp_cae_base_addr+0x0001123c)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 328\n");
if((readl(ivp_cae_base_addr+0x00011240)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 329\n");
if((readl(ivp_cae_base_addr+0x00011244)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 330\n");
if((readl(ivp_cae_base_addr+0x00011248)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 331\n");
if((readl(ivp_cae_base_addr+0x0001124c)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 332\n");
if((readl(ivp_cae_base_addr+0x00011250)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 333\n");
if((readl(ivp_cae_base_addr+0x00011254)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 334\n");
if((readl(ivp_cae_base_addr+0x00011258)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 335\n");
if((readl(ivp_cae_base_addr+0x0001125c)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 336\n");
if((readl(ivp_cae_base_addr+0x00011260)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 337\n");
if((readl(ivp_cae_base_addr+0x00011264)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 338\n");
if((readl(ivp_cae_base_addr+0x00011268)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 339\n");
if((readl(ivp_cae_base_addr+0x0001126c)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 340\n");
if((readl(ivp_cae_base_addr+0x00011270)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 341\n");
if((readl(ivp_cae_base_addr+0x00011274)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 342\n");
if((readl(ivp_cae_base_addr+0x00011278)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 343\n");
if((readl(ivp_cae_base_addr+0x0001127c)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 344\n");
if((readl(ivp_cae_base_addr+0x00011280)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 345\n");
if((readl(ivp_cae_base_addr+0x00011284)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 346\n");
if((readl(ivp_cae_base_addr+0x00011288)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 347\n");
if((readl(ivp_cae_base_addr+0x0001128c)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 348\n");
if((readl(ivp_cae_base_addr+0x00011290)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 349\n");
if((readl(ivp_cae_base_addr+0x00011294)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 350\n");
if((readl(ivp_cae_base_addr+0x00011298)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 351\n");
if((readl(ivp_cae_base_addr+0x0001129c)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 352\n");
if((readl(ivp_cae_base_addr+0x000112a4)&0x0000ffff)==(0x00000000&0x0000ffff))
cnt++;
else
printf("cnt: 353\n");
if((readl(ivp_cae_base_addr+0x000112c0)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 354\n");
if((readl(ivp_cae_base_addr+0x000112c4)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 355\n");
if((readl(ivp_cae_base_addr+0x000112c8)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 356\n");
if((readl(ivp_cae_base_addr+0x000112cc)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 357\n");
if((readl(ivp_cae_base_addr+0x000112d0)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 358\n");
if((readl(ivp_cae_base_addr+0x000112d4)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 359\n");
if((readl(ivp_cae_base_addr+0x000112d8)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 360\n");
if((readl(ivp_cae_base_addr+0x000112dc)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 361\n");
if((readl(ivp_cae_base_addr+0x000112e0)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 362\n");
if((readl(ivp_cae_base_addr+0x000112e4)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 363\n");
if((readl(ivp_cae_base_addr+0x000112e8)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 364\n");
if((readl(ivp_cae_base_addr+0x000112ec)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 365\n");
if((readl(ivp_cae_base_addr+0x000112f0)&0x0000ffff)==(0x00000000&0x0000ffff))
cnt++;
else
printf("cnt: 366\n");
if((readl(ivp_cae_base_addr+0x00011300)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 367\n");
if((readl(ivp_cae_base_addr+0x00011304)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 368\n");
if((readl(ivp_cae_base_addr+0x00011308)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 369\n");
if((readl(ivp_cae_base_addr+0x0001130c)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 370\n");
if((readl(ivp_cae_base_addr+0x00011310)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 371\n");
if((readl(ivp_cae_base_addr+0x00011314)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 372\n");
if((readl(ivp_cae_base_addr+0x00011318)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 373\n");
if((readl(ivp_cae_base_addr+0x0001131c)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 374\n");
if((readl(ivp_cae_base_addr+0x00011320)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 375\n");
if((readl(ivp_cae_base_addr+0x00011324)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 376\n");
if((readl(ivp_cae_base_addr+0x00011328)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 377\n");
if((readl(ivp_cae_base_addr+0x0001132c)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 378\n");
if((readl(ivp_cae_base_addr+0x00011330)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 379\n");
if((readl(ivp_cae_base_addr+0x00011334)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 380\n");
if((readl(ivp_cae_base_addr+0x00011338)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 381\n");
if((readl(ivp_cae_base_addr+0x0001133c)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 382\n");
if((readl(ivp_cae_base_addr+0x00011340)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 383\n");
if((readl(ivp_cae_base_addr+0x00011344)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 384\n");
if((readl(ivp_cae_base_addr+0x00011348)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 385\n");
if((readl(ivp_cae_base_addr+0x0001134c)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 386\n");
if((readl(ivp_cae_base_addr+0x00011350)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 387\n");
if((readl(ivp_cae_base_addr+0x00011354)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 388\n");
if((readl(ivp_cae_base_addr+0x00011358)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 389\n");
if((readl(ivp_cae_base_addr+0x0001135c)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 390\n");
if((readl(ivp_cae_base_addr+0x00011360)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 391\n");
if((readl(ivp_cae_base_addr+0x00011364)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 392\n");
if((readl(ivp_cae_base_addr+0x00011368)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 393\n");
if((readl(ivp_cae_base_addr+0x0001136c)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 394\n");
if((readl(ivp_cae_base_addr+0x00011370)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 395\n");
if((readl(ivp_cae_base_addr+0x00011374)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 396\n");
if((readl(ivp_cae_base_addr+0x00011378)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 397\n");
if((readl(ivp_cae_base_addr+0x0001137c)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 398\n");
if((readl(ivp_cae_base_addr+0x00011380)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 399\n");
if((readl(ivp_cae_base_addr+0x00011384)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 400\n");
if((readl(ivp_cae_base_addr+0x00011388)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 401\n");
if((readl(ivp_cae_base_addr+0x0001138c)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 402\n");
if((readl(ivp_cae_base_addr+0x00011390)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 403\n");
if((readl(ivp_cae_base_addr+0x00011394)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 404\n");
if((readl(ivp_cae_base_addr+0x00011398)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 405\n");
if((readl(ivp_cae_base_addr+0x0001139c)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 406\n");
if((readl(ivp_cae_base_addr+0x000113c0)&0x0000000f)==(0x0000000f&0x0000000f))
cnt++;
else
printf("cnt: 407\n");
if((readl(ivp_cae_base_addr+0x000113c4)&0x0000000f)==(0x0000000f&0x0000000f))
cnt++;
else
printf("cnt: 408\n");
if((readl(ivp_cae_base_addr+0x000113c8)&0x0000000f)==(0x00000000&0x0000000f))
cnt++;
else
printf("cnt: 409\n");
if((readl(ivp_cae_base_addr+0x000113cc)&0x0000000f)==(0x00000000&0x0000000f))
cnt++;
else
printf("cnt: 410\n");
if((readl(ivp_cae_base_addr+0x000113d0)&0x0000000f)==(0x00000000&0x0000000f))
cnt++;
else
printf("cnt: 411\n");
if((readl(ivp_cae_base_addr+0x000113d4)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 412\n");
if((readl(ivp_cae_base_addr+0x000113d8)&0x000001bf)==(0x00000004&0x000001bf))
cnt++;
else
printf("cnt: 413\n");
if((readl(ivp_cae_base_addr+0x000113dc)&0x0fffffff)==(0x014036c9&0x0fffffff))
cnt++;
else
printf("cnt: 414\n");
if((readl(ivp_cae_base_addr+0x000113f8)&0xffffffe0)==(0x7fc1fc00&0xffffffe0))
cnt++;
else
printf("cnt: 415\n");
if((readl(ivp_cae_base_addr+0x000113fc)&0x0fffffff)==(0x04339f60&0x0fffffff))
cnt++;
else
printf("cnt: 416\n");
if((readl(ivp_cae_base_addr+0x00011c00)&0xcfff00ff)==(0x00000087&0xcfff00ff))
cnt++;
else
printf("cnt: 417\n");
if((readl(ivp_cae_base_addr+0x00011d00)&0xcfff0000)==(0x00000000&0xcfff0000))
cnt++;
else
printf("cnt: 418\n");
if((readl(ivp_cae_base_addr+0x00011f00)&0x0000001f)==(0x00000000&0x0000001f))
cnt++;
else
printf("cnt: 419\n");
if((readl(ivp_cae_base_addr+0x00011f04)&0x0000001f)==(0x00000000&0x0000001f))
cnt++;
else
printf("cnt: 420\n");
if((readl(ivp_cae_base_addr+0x00011f08)&0x0000001f)==(0x00000000&0x0000001f))
cnt++;
else
printf("cnt: 421\n");
if((readl(ivp_cae_base_addr+0x00011f0c)&0x0000001f)==(0x00000000&0x0000001f))
cnt++;
else
printf("cnt: 422\n");
if((readl(ivp_cae_base_addr+0x00011f10)&0x0000001f)==(0x00000000&0x0000001f))
cnt++;
else
printf("cnt: 423\n");
if((readl(ivp_cae_base_addr+0x00011f14)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 424\n");
if((readl(ivp_cae_base_addr+0x00011f18)&0x000001bf)==(0x00000005&0x000001bf))
cnt++;
else
printf("cnt: 425\n");
if((readl(ivp_cae_base_addr+0x00011f1c)&0x0fffffff)==(0x014036c9&0x0fffffff))
cnt++;
else
printf("cnt: 426\n");
if((readl(ivp_cae_base_addr+0x00011ff0)&0x00ff00ff)==(0x00000000&0x00ff00ff))
cnt++;
else
printf("cnt: 427\n");
if((readl(ivp_cae_base_addr+0x00011ff4)&0x80ff0001)==(0x00000000&0x80ff0001))
cnt++;
else
printf("cnt: 428\n");
if((readl(ivp_cae_base_addr+0x00011ff8)&0xfffc0fff)==(0x72e80060&0xfffc0fff))
cnt++;
else
printf("cnt: 429\n");
if((readl(ivp_cae_base_addr+0x00011ffc)&0x0fffffff)==(0x015031ce&0x0fffffff))
cnt++;
else
printf("cnt: 430\n");
if((readl(ivp_cae_base_addr+0x0001ffe4)&0x087b031f)==(0x00000000&0x087b031f))
cnt++;
else
printf("cnt: 431\n");
if((readl(ivp_cae_base_addr+0x0001ffe8)&0x087b031f)==(0x00000000&0x087b031f))
cnt++;
else
printf("cnt: 432\n");
if((readl(ivp_cae_base_addr+0x0001ffec)&0x087b031f)==(0x00000000&0x087b031f))
cnt++;
else
printf("cnt: 433\n");
if((readl(ivp_cae_base_addr+0x0001fff4)&0x000401ff)==(0x00000000&0x000401ff))
cnt++;
else
printf("cnt: 434\n");
if((readl(ivp_cae_base_addr+0x0001fff8)&0xc00fffff)==(0x00074751&0xc00fffff))
cnt++;
else
printf("cnt: 435\n");
if((readl(ivp_cae_base_addr+0x0001fffc)&0x0fffffff)==(0x02319e61&0x0fffffff))
cnt++;
else
printf("cnt: 436\n");
writel(0x11111111&0xffffffff,ivp_cae_base_addr+0x00000000);
if((readl(ivp_cae_base_addr+0x00000000)&0xffffffff)==(0x11111111&0xffffffff))
cnt++;
else
printf("cnt: 437\n");
writel(0x22222222&0xffffffff,ivp_cae_base_addr+0x00000000);
if((readl(ivp_cae_base_addr+0x00000000)&0xffffffff)==(0x22222222&0xffffffff))
cnt++;
else
printf("cnt: 438\n");
writel(0x44444444&0xffffffff,ivp_cae_base_addr+0x00000000);
if((readl(ivp_cae_base_addr+0x00000000)&0xffffffff)==(0x44444444&0xffffffff))
cnt++;
else
printf("cnt: 439\n");
writel(0x88888888&0xffffffff,ivp_cae_base_addr+0x00000000);
if((readl(ivp_cae_base_addr+0x00000000)&0xffffffff)==(0x88888888&0xffffffff))
cnt++;
else
printf("cnt: 440\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00000000);
if((readl(ivp_cae_base_addr+0x00000000)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 441\n");
writel(0xffffffff&0xffffffff,ivp_cae_base_addr+0x00000000);
if((readl(ivp_cae_base_addr+0x00000000)&0xffffffff)==(0xffffffff&0xffffffff))
cnt++;
else
printf("cnt: 442\n");
writel(0x11111111&0xffffffff,ivp_cae_base_addr+0x00000004);
if((readl(ivp_cae_base_addr+0x00000004)&0xffffffff)==(0x11111111&0xffffffff))
cnt++;
else
printf("cnt: 443\n");
writel(0x22222222&0xffffffff,ivp_cae_base_addr+0x00000004);
if((readl(ivp_cae_base_addr+0x00000004)&0xffffffff)==(0x22222222&0xffffffff))
cnt++;
else
printf("cnt: 444\n");
writel(0x44444444&0xffffffff,ivp_cae_base_addr+0x00000004);
if((readl(ivp_cae_base_addr+0x00000004)&0xffffffff)==(0x44444444&0xffffffff))
cnt++;
else
printf("cnt: 445\n");
writel(0x88888888&0xffffffff,ivp_cae_base_addr+0x00000004);
if((readl(ivp_cae_base_addr+0x00000004)&0xffffffff)==(0x88888888&0xffffffff))
cnt++;
else
printf("cnt: 446\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00000004);
if((readl(ivp_cae_base_addr+0x00000004)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 447\n");
writel(0xffffffff&0xffffffff,ivp_cae_base_addr+0x00000004);
if((readl(ivp_cae_base_addr+0x00000004)&0xffffffff)==(0xffffffff&0xffffffff))
cnt++;
else
printf("cnt: 448\n");
writel(0x11111111&0xffffffff,ivp_cae_base_addr+0x00000008);
if((readl(ivp_cae_base_addr+0x00000008)&0xffffffff)==(0x11111111&0xffffffff))
cnt++;
else
printf("cnt: 449\n");
writel(0x22222222&0xffffffff,ivp_cae_base_addr+0x00000008);
if((readl(ivp_cae_base_addr+0x00000008)&0xffffffff)==(0x22222222&0xffffffff))
cnt++;
else
printf("cnt: 450\n");
writel(0x44444444&0xffffffff,ivp_cae_base_addr+0x00000008);
if((readl(ivp_cae_base_addr+0x00000008)&0xffffffff)==(0x44444444&0xffffffff))
cnt++;
else
printf("cnt: 451\n");
writel(0x88888888&0xffffffff,ivp_cae_base_addr+0x00000008);
if((readl(ivp_cae_base_addr+0x00000008)&0xffffffff)==(0x88888888&0xffffffff))
cnt++;
else
printf("cnt: 452\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00000008);
if((readl(ivp_cae_base_addr+0x00000008)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 453\n");
writel(0xffffffff&0xffffffff,ivp_cae_base_addr+0x00000008);
if((readl(ivp_cae_base_addr+0x00000008)&0xffffffff)==(0xffffffff&0xffffffff))
cnt++;
else
printf("cnt: 454\n");
writel(0x11111111&0xffffffff,ivp_cae_base_addr+0x0000000c);
if((readl(ivp_cae_base_addr+0x0000000c)&0xffffffff)==(0x11111111&0xffffffff))
cnt++;
else
printf("cnt: 455\n");
writel(0x22222222&0xffffffff,ivp_cae_base_addr+0x0000000c);
if((readl(ivp_cae_base_addr+0x0000000c)&0xffffffff)==(0x22222222&0xffffffff))
cnt++;
else
printf("cnt: 456\n");
writel(0x44444444&0xffffffff,ivp_cae_base_addr+0x0000000c);
if((readl(ivp_cae_base_addr+0x0000000c)&0xffffffff)==(0x44444444&0xffffffff))
cnt++;
else
printf("cnt: 457\n");
writel(0x88888888&0xffffffff,ivp_cae_base_addr+0x0000000c);
if((readl(ivp_cae_base_addr+0x0000000c)&0xffffffff)==(0x88888888&0xffffffff))
cnt++;
else
printf("cnt: 458\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000000c);
if((readl(ivp_cae_base_addr+0x0000000c)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 459\n");
writel(0xffffffff&0xffffffff,ivp_cae_base_addr+0x0000000c);
if((readl(ivp_cae_base_addr+0x0000000c)&0xffffffff)==(0xffffffff&0xffffffff))
cnt++;
else
printf("cnt: 460\n");
writel(0x11111111&0xffffffff,ivp_cae_base_addr+0x00000010);
if((readl(ivp_cae_base_addr+0x00000010)&0xffffffff)==(0x11111111&0xffffffff))
cnt++;
else
printf("cnt: 461\n");
writel(0x22222222&0xffffffff,ivp_cae_base_addr+0x00000010);
if((readl(ivp_cae_base_addr+0x00000010)&0xffffffff)==(0x22222222&0xffffffff))
cnt++;
else
printf("cnt: 462\n");
writel(0x44444444&0xffffffff,ivp_cae_base_addr+0x00000010);
if((readl(ivp_cae_base_addr+0x00000010)&0xffffffff)==(0x44444444&0xffffffff))
cnt++;
else
printf("cnt: 463\n");
writel(0x88888888&0xffffffff,ivp_cae_base_addr+0x00000010);
if((readl(ivp_cae_base_addr+0x00000010)&0xffffffff)==(0x88888888&0xffffffff))
cnt++;
else
printf("cnt: 464\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00000010);
if((readl(ivp_cae_base_addr+0x00000010)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 465\n");
writel(0xffffffff&0xffffffff,ivp_cae_base_addr+0x00000010);
if((readl(ivp_cae_base_addr+0x00000010)&0xffffffff)==(0xffffffff&0xffffffff))
cnt++;
else
printf("cnt: 466\n");
writel(0x11111111&0xffffffff,ivp_cae_base_addr+0x00000014);
if((readl(ivp_cae_base_addr+0x00000014)&0xffffffff)==(0x11111111&0xffffffff))
cnt++;
else
printf("cnt: 467\n");
writel(0x22222222&0xffffffff,ivp_cae_base_addr+0x00000014);
if((readl(ivp_cae_base_addr+0x00000014)&0xffffffff)==(0x22222222&0xffffffff))
cnt++;
else
printf("cnt: 468\n");
writel(0x44444444&0xffffffff,ivp_cae_base_addr+0x00000014);
if((readl(ivp_cae_base_addr+0x00000014)&0xffffffff)==(0x44444444&0xffffffff))
cnt++;
else
printf("cnt: 469\n");
writel(0x88888888&0xffffffff,ivp_cae_base_addr+0x00000014);
if((readl(ivp_cae_base_addr+0x00000014)&0xffffffff)==(0x88888888&0xffffffff))
cnt++;
else
printf("cnt: 470\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00000014);
if((readl(ivp_cae_base_addr+0x00000014)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 471\n");
writel(0xffffffff&0xffffffff,ivp_cae_base_addr+0x00000014);
if((readl(ivp_cae_base_addr+0x00000014)&0xffffffff)==(0xffffffff&0xffffffff))
cnt++;
else
printf("cnt: 472\n");
writel(0x00111110&0xffffffff,ivp_cae_base_addr+0x00000018);
if((readl(ivp_cae_base_addr+0x00000018)&0x00fffffc)==(0x00111110&0x00fffffc))
cnt++;
else
printf("cnt: 473\n");
writel(0x00222220&0xffffffff,ivp_cae_base_addr+0x00000018);
if((readl(ivp_cae_base_addr+0x00000018)&0x00fffffc)==(0x00222220&0x00fffffc))
cnt++;
else
printf("cnt: 474\n");
writel(0x00444444&0xffffffff,ivp_cae_base_addr+0x00000018);
if((readl(ivp_cae_base_addr+0x00000018)&0x00fffffc)==(0x00444444&0x00fffffc))
cnt++;
else
printf("cnt: 475\n");
writel(0x00888888&0xffffffff,ivp_cae_base_addr+0x00000018);
if((readl(ivp_cae_base_addr+0x00000018)&0x00fffffc)==(0x00888888&0x00fffffc))
cnt++;
else
printf("cnt: 476\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00000018);
if((readl(ivp_cae_base_addr+0x00000018)&0x00fffffc)==(0x00000000&0x00fffffc))
cnt++;
else
printf("cnt: 477\n");
writel(0x00fffffc&0xffffffff,ivp_cae_base_addr+0x00000018);
if((readl(ivp_cae_base_addr+0x00000018)&0x00fffffc)==(0x00fffffc&0x00fffffc))
cnt++;
else
printf("cnt: 478\n");
writel(0x00110011&0xffffffff,ivp_cae_base_addr+0x0000001c);
if((readl(ivp_cae_base_addr+0x0000001c)&0xe0ff003f)==(0x00110011&0xe0ff003f))
cnt++;
else
printf("cnt: 479\n");
writel(0x20220022&0xffffffff,ivp_cae_base_addr+0x0000001c);
if((readl(ivp_cae_base_addr+0x0000001c)&0xe0ff003f)==(0x20220022&0xe0ff003f))
cnt++;
else
printf("cnt: 480\n");
writel(0x40440004&0xffffffff,ivp_cae_base_addr+0x0000001c);
if((readl(ivp_cae_base_addr+0x0000001c)&0xe0ff003f)==(0x40440004&0xe0ff003f))
cnt++;
else
printf("cnt: 481\n");
writel(0x80880008&0xffffffff,ivp_cae_base_addr+0x0000001c);
if((readl(ivp_cae_base_addr+0x0000001c)&0xe0ff003f)==(0x80880008&0xe0ff003f))
cnt++;
else
printf("cnt: 482\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000001c);
if((readl(ivp_cae_base_addr+0x0000001c)&0xe0ff003f)==(0x00000000&0xe0ff003f))
cnt++;
else
printf("cnt: 483\n");
writel(0xe0ff003f&0xffffffff,ivp_cae_base_addr+0x0000001c);
if((readl(ivp_cae_base_addr+0x0000001c)&0xe0ff003f)==(0xe0ff003f&0xe0ff003f))
cnt++;
else
printf("cnt: 484\n");
writel(0x10110011&0xffffffff,ivp_cae_base_addr+0x00000020);
if((readl(ivp_cae_base_addr+0x00000020)&0xf03f00ff)==(0x10110011&0xf03f00ff))
cnt++;
else
printf("cnt: 485\n");
writel(0x20220022&0xffffffff,ivp_cae_base_addr+0x00000020);
if((readl(ivp_cae_base_addr+0x00000020)&0xf03f00ff)==(0x20220022&0xf03f00ff))
cnt++;
else
printf("cnt: 486\n");
writel(0x40040044&0xffffffff,ivp_cae_base_addr+0x00000020);
if((readl(ivp_cae_base_addr+0x00000020)&0xf03f00ff)==(0x40040044&0xf03f00ff))
cnt++;
else
printf("cnt: 487\n");
writel(0x80080088&0xffffffff,ivp_cae_base_addr+0x00000020);
if((readl(ivp_cae_base_addr+0x00000020)&0xf03f00ff)==(0x80080088&0xf03f00ff))
cnt++;
else
printf("cnt: 488\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00000020);
if((readl(ivp_cae_base_addr+0x00000020)&0xf03f00ff)==(0x00000000&0xf03f00ff))
cnt++;
else
printf("cnt: 489\n");
writel(0xf03f00ff&0xffffffff,ivp_cae_base_addr+0x00000020);
if((readl(ivp_cae_base_addr+0x00000020)&0xf03f00ff)==(0xf03f00ff&0xf03f00ff))
cnt++;
else
printf("cnt: 490\n");
writel(0x11010101&0xffffffff,ivp_cae_base_addr+0x00000024);
if((readl(ivp_cae_base_addr+0x00000024)&0xff010101)==(0x11010101&0xff010101))
cnt++;
else
printf("cnt: 491\n");
writel(0x22000000&0xffffffff,ivp_cae_base_addr+0x00000024);
if((readl(ivp_cae_base_addr+0x00000024)&0xff010101)==(0x22000000&0xff010101))
cnt++;
else
printf("cnt: 492\n");
writel(0x44000000&0xffffffff,ivp_cae_base_addr+0x00000024);
if((readl(ivp_cae_base_addr+0x00000024)&0xff010101)==(0x44000000&0xff010101))
cnt++;
else
printf("cnt: 493\n");
writel(0x88000000&0xffffffff,ivp_cae_base_addr+0x00000024);
if((readl(ivp_cae_base_addr+0x00000024)&0xff010101)==(0x88000000&0xff010101))
cnt++;
else
printf("cnt: 494\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00000024);
if((readl(ivp_cae_base_addr+0x00000024)&0xff010101)==(0x00000000&0xff010101))
cnt++;
else
printf("cnt: 495\n");
writel(0xff010101&0xffffffff,ivp_cae_base_addr+0x00000024);
if((readl(ivp_cae_base_addr+0x00000024)&0xff010101)==(0xff010101&0xff010101))
cnt++;
else
printf("cnt: 496\n");
writel(0x11000000&0xffffffff,ivp_cae_base_addr+0x00000028);
if((readl(ivp_cae_base_addr+0x00000028)&0xffc00000)==(0x11000000&0xffc00000))
cnt++;
else
printf("cnt: 497\n");
writel(0x22000000&0xffffffff,ivp_cae_base_addr+0x00000028);
if((readl(ivp_cae_base_addr+0x00000028)&0xffc00000)==(0x22000000&0xffc00000))
cnt++;
else
printf("cnt: 498\n");
writel(0x44400000&0xffffffff,ivp_cae_base_addr+0x00000028);
if((readl(ivp_cae_base_addr+0x00000028)&0xffc00000)==(0x44400000&0xffc00000))
cnt++;
else
printf("cnt: 499\n");
writel(0x88800000&0xffffffff,ivp_cae_base_addr+0x00000028);
if((readl(ivp_cae_base_addr+0x00000028)&0xffc00000)==(0x88800000&0xffc00000))
cnt++;
else
printf("cnt: 500\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00000028);
if((readl(ivp_cae_base_addr+0x00000028)&0xffc00000)==(0x00000000&0xffc00000))
cnt++;
else
printf("cnt: 501\n");
writel(0xffc00000&0xffffffff,ivp_cae_base_addr+0x00000028);
if((readl(ivp_cae_base_addr+0x00000028)&0xffc00000)==(0xffc00000&0xffc00000))
cnt++;
else
printf("cnt: 502\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000002c);
if((readl(ivp_cae_base_addr+0x0000002c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 503\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000002c);
if((readl(ivp_cae_base_addr+0x0000002c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 504\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000002c);
if((readl(ivp_cae_base_addr+0x0000002c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 505\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000002c);
if((readl(ivp_cae_base_addr+0x0000002c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 506\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000002c);
if((readl(ivp_cae_base_addr+0x0000002c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 507\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000002c);
if((readl(ivp_cae_base_addr+0x0000002c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 508\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00000030);
if((readl(ivp_cae_base_addr+0x00000030)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 509\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00000030);
if((readl(ivp_cae_base_addr+0x00000030)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 510\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00000030);
if((readl(ivp_cae_base_addr+0x00000030)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 511\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00000030);
if((readl(ivp_cae_base_addr+0x00000030)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 512\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00000030);
if((readl(ivp_cae_base_addr+0x00000030)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 513\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00000030);
if((readl(ivp_cae_base_addr+0x00000030)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 514\n");
writel(0x00111110&0xffffffff,ivp_cae_base_addr+0x00000034);
if((readl(ivp_cae_base_addr+0x00000034)&0x00fffffc)==(0x00111110&0x00fffffc))
cnt++;
else
printf("cnt: 515\n");
writel(0x00222220&0xffffffff,ivp_cae_base_addr+0x00000034);
if((readl(ivp_cae_base_addr+0x00000034)&0x00fffffc)==(0x00222220&0x00fffffc))
cnt++;
else
printf("cnt: 516\n");
writel(0x00444444&0xffffffff,ivp_cae_base_addr+0x00000034);
if((readl(ivp_cae_base_addr+0x00000034)&0x00fffffc)==(0x00444444&0x00fffffc))
cnt++;
else
printf("cnt: 517\n");
writel(0x00888888&0xffffffff,ivp_cae_base_addr+0x00000034);
if((readl(ivp_cae_base_addr+0x00000034)&0x00fffffc)==(0x00888888&0x00fffffc))
cnt++;
else
printf("cnt: 518\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00000034);
if((readl(ivp_cae_base_addr+0x00000034)&0x00fffffc)==(0x00000000&0x00fffffc))
cnt++;
else
printf("cnt: 519\n");
writel(0x00fffffc&0xffffffff,ivp_cae_base_addr+0x00000034);
if((readl(ivp_cae_base_addr+0x00000034)&0x00fffffc)==(0x00fffffc&0x00fffffc))
cnt++;
else
printf("cnt: 520\n");
writel(0x00111110&0xffffffff,ivp_cae_base_addr+0x00000038);
if((readl(ivp_cae_base_addr+0x00000038)&0x00fffffc)==(0x00111110&0x00fffffc))
cnt++;
else
printf("cnt: 521\n");
writel(0x00222220&0xffffffff,ivp_cae_base_addr+0x00000038);
if((readl(ivp_cae_base_addr+0x00000038)&0x00fffffc)==(0x00222220&0x00fffffc))
cnt++;
else
printf("cnt: 522\n");
writel(0x00444444&0xffffffff,ivp_cae_base_addr+0x00000038);
if((readl(ivp_cae_base_addr+0x00000038)&0x00fffffc)==(0x00444444&0x00fffffc))
cnt++;
else
printf("cnt: 523\n");
writel(0x00888888&0xffffffff,ivp_cae_base_addr+0x00000038);
if((readl(ivp_cae_base_addr+0x00000038)&0x00fffffc)==(0x00888888&0x00fffffc))
cnt++;
else
printf("cnt: 524\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00000038);
if((readl(ivp_cae_base_addr+0x00000038)&0x00fffffc)==(0x00000000&0x00fffffc))
cnt++;
else
printf("cnt: 525\n");
writel(0x00fffffc&0xffffffff,ivp_cae_base_addr+0x00000038);
if((readl(ivp_cae_base_addr+0x00000038)&0x00fffffc)==(0x00fffffc&0x00fffffc))
cnt++;
else
printf("cnt: 526\n");
writel(0x00000011&0xffffffff,ivp_cae_base_addr+0x0000003c);
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000000)==(0x00000011&0x00000000))
cnt++;
else
printf("cnt: 527\n");
writel(0x00000022&0xffffffff,ivp_cae_base_addr+0x0000003c);
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000000)==(0x00000022&0x00000000))
cnt++;
else
printf("cnt: 528\n");
writel(0x00000004&0xffffffff,ivp_cae_base_addr+0x0000003c);
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000000)==(0x00000004&0x00000000))
cnt++;
else
printf("cnt: 529\n");
writel(0x00000008&0xffffffff,ivp_cae_base_addr+0x0000003c);
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000000)==(0x00000008&0x00000000))
cnt++;
else
printf("cnt: 530\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000003c);
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 531\n");
writel(0x0000003f&0xffffffff,ivp_cae_base_addr+0x0000003c);
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000000)==(0x0000003f&0x00000000))
cnt++;
else
printf("cnt: 532\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000007f8);
if((readl(ivp_cae_base_addr+0x000007f8)&0xb7ffffff)==(0x80a35514&0xb7ffffff))
cnt++;
else
printf("cnt: 533\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000007f8);
if((readl(ivp_cae_base_addr+0x000007f8)&0xb7ffffff)==(0x80a35514&0xb7ffffff))
cnt++;
else
printf("cnt: 534\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000007f8);
if((readl(ivp_cae_base_addr+0x000007f8)&0xb7ffffff)==(0x80a35514&0xb7ffffff))
cnt++;
else
printf("cnt: 535\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000007f8);
if((readl(ivp_cae_base_addr+0x000007f8)&0xb7ffffff)==(0x80a35514&0xb7ffffff))
cnt++;
else
printf("cnt: 536\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000007f8);
if((readl(ivp_cae_base_addr+0x000007f8)&0xb7ffffff)==(0x80a35514&0xb7ffffff))
cnt++;
else
printf("cnt: 537\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000007f8);
if((readl(ivp_cae_base_addr+0x000007f8)&0xb7ffffff)==(0x80a35514&0xb7ffffff))
cnt++;
else
printf("cnt: 538\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000007fc);
if((readl(ivp_cae_base_addr+0x000007fc)&0x0fffffff)==(0x027035ca&0x0fffffff))
cnt++;
else
printf("cnt: 539\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000007fc);
if((readl(ivp_cae_base_addr+0x000007fc)&0x0fffffff)==(0x027035ca&0x0fffffff))
cnt++;
else
printf("cnt: 540\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000007fc);
if((readl(ivp_cae_base_addr+0x000007fc)&0x0fffffff)==(0x027035ca&0x0fffffff))
cnt++;
else
printf("cnt: 541\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000007fc);
if((readl(ivp_cae_base_addr+0x000007fc)&0x0fffffff)==(0x027035ca&0x0fffffff))
cnt++;
else
printf("cnt: 542\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000007fc);
if((readl(ivp_cae_base_addr+0x000007fc)&0x0fffffff)==(0x027035ca&0x0fffffff))
cnt++;
else
printf("cnt: 543\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000007fc);
if((readl(ivp_cae_base_addr+0x000007fc)&0x0fffffff)==(0x027035ca&0x0fffffff))
cnt++;
else
printf("cnt: 544\n");
writel(0x11111111&0xffffffff,ivp_cae_base_addr+0x00000800);
if((readl(ivp_cae_base_addr+0x00000800)&0xffffffff)==(0x11111111&0xffffffff))
cnt++;
else
printf("cnt: 545\n");
writel(0x22222222&0xffffffff,ivp_cae_base_addr+0x00000800);
if((readl(ivp_cae_base_addr+0x00000800)&0xffffffff)==(0x22222222&0xffffffff))
cnt++;
else
printf("cnt: 546\n");
writel(0x44444444&0xffffffff,ivp_cae_base_addr+0x00000800);
if((readl(ivp_cae_base_addr+0x00000800)&0xffffffff)==(0x44444444&0xffffffff))
cnt++;
else
printf("cnt: 547\n");
writel(0x88888888&0xffffffff,ivp_cae_base_addr+0x00000800);
if((readl(ivp_cae_base_addr+0x00000800)&0xffffffff)==(0x88888888&0xffffffff))
cnt++;
else
printf("cnt: 548\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00000800);
if((readl(ivp_cae_base_addr+0x00000800)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 549\n");
writel(0xffffffff&0xffffffff,ivp_cae_base_addr+0x00000800);
if((readl(ivp_cae_base_addr+0x00000800)&0xffffffff)==(0xffffffff&0xffffffff))
cnt++;
else
printf("cnt: 550\n");
writel(0x11111111&0xffffffff,ivp_cae_base_addr+0x00000804);
if((readl(ivp_cae_base_addr+0x00000804)&0xffffffff)==(0x11111111&0xffffffff))
cnt++;
else
printf("cnt: 551\n");
writel(0x22222222&0xffffffff,ivp_cae_base_addr+0x00000804);
if((readl(ivp_cae_base_addr+0x00000804)&0xffffffff)==(0x22222222&0xffffffff))
cnt++;
else
printf("cnt: 552\n");
writel(0x44444444&0xffffffff,ivp_cae_base_addr+0x00000804);
if((readl(ivp_cae_base_addr+0x00000804)&0xffffffff)==(0x44444444&0xffffffff))
cnt++;
else
printf("cnt: 553\n");
writel(0x88888888&0xffffffff,ivp_cae_base_addr+0x00000804);
if((readl(ivp_cae_base_addr+0x00000804)&0xffffffff)==(0x88888888&0xffffffff))
cnt++;
else
printf("cnt: 554\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00000804);
if((readl(ivp_cae_base_addr+0x00000804)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 555\n");
writel(0xffffffff&0xffffffff,ivp_cae_base_addr+0x00000804);
if((readl(ivp_cae_base_addr+0x00000804)&0xffffffff)==(0xffffffff&0xffffffff))
cnt++;
else
printf("cnt: 556\n");
writel(0x11111111&0xffffffff,ivp_cae_base_addr+0x00000808);
if((readl(ivp_cae_base_addr+0x00000808)&0xffffffff)==(0x11111111&0xffffffff))
cnt++;
else
printf("cnt: 557\n");
writel(0x22222222&0xffffffff,ivp_cae_base_addr+0x00000808);
if((readl(ivp_cae_base_addr+0x00000808)&0xffffffff)==(0x22222222&0xffffffff))
cnt++;
else
printf("cnt: 558\n");
writel(0x44444444&0xffffffff,ivp_cae_base_addr+0x00000808);
if((readl(ivp_cae_base_addr+0x00000808)&0xffffffff)==(0x44444444&0xffffffff))
cnt++;
else
printf("cnt: 559\n");
writel(0x88888888&0xffffffff,ivp_cae_base_addr+0x00000808);
if((readl(ivp_cae_base_addr+0x00000808)&0xffffffff)==(0x88888888&0xffffffff))
cnt++;
else
printf("cnt: 560\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00000808);
if((readl(ivp_cae_base_addr+0x00000808)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 561\n");
writel(0xffffffff&0xffffffff,ivp_cae_base_addr+0x00000808);
if((readl(ivp_cae_base_addr+0x00000808)&0xffffffff)==(0xffffffff&0xffffffff))
cnt++;
else
printf("cnt: 562\n");
writel(0x11111111&0xffffffff,ivp_cae_base_addr+0x0000080c);
if((readl(ivp_cae_base_addr+0x0000080c)&0xffffffff)==(0x11111111&0xffffffff))
cnt++;
else
printf("cnt: 563\n");
writel(0x22222222&0xffffffff,ivp_cae_base_addr+0x0000080c);
if((readl(ivp_cae_base_addr+0x0000080c)&0xffffffff)==(0x22222222&0xffffffff))
cnt++;
else
printf("cnt: 564\n");
writel(0x44444444&0xffffffff,ivp_cae_base_addr+0x0000080c);
if((readl(ivp_cae_base_addr+0x0000080c)&0xffffffff)==(0x44444444&0xffffffff))
cnt++;
else
printf("cnt: 565\n");
writel(0x88888888&0xffffffff,ivp_cae_base_addr+0x0000080c);
if((readl(ivp_cae_base_addr+0x0000080c)&0xffffffff)==(0x88888888&0xffffffff))
cnt++;
else
printf("cnt: 566\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000080c);
if((readl(ivp_cae_base_addr+0x0000080c)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 567\n");
writel(0xffffffff&0xffffffff,ivp_cae_base_addr+0x0000080c);
if((readl(ivp_cae_base_addr+0x0000080c)&0xffffffff)==(0xffffffff&0xffffffff))
cnt++;
else
printf("cnt: 568\n");
writel(0x00111110&0xffffffff,ivp_cae_base_addr+0x00000818);
if((readl(ivp_cae_base_addr+0x00000818)&0x00fffffc)==(0x00111110&0x00fffffc))
cnt++;
else
printf("cnt: 569\n");
writel(0x00222220&0xffffffff,ivp_cae_base_addr+0x00000818);
if((readl(ivp_cae_base_addr+0x00000818)&0x00fffffc)==(0x00222220&0x00fffffc))
cnt++;
else
printf("cnt: 570\n");
writel(0x00444444&0xffffffff,ivp_cae_base_addr+0x00000818);
if((readl(ivp_cae_base_addr+0x00000818)&0x00fffffc)==(0x00444444&0x00fffffc))
cnt++;
else
printf("cnt: 571\n");
writel(0x00888888&0xffffffff,ivp_cae_base_addr+0x00000818);
if((readl(ivp_cae_base_addr+0x00000818)&0x00fffffc)==(0x00888888&0x00fffffc))
cnt++;
else
printf("cnt: 572\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00000818);
if((readl(ivp_cae_base_addr+0x00000818)&0x00fffffc)==(0x00000000&0x00fffffc))
cnt++;
else
printf("cnt: 573\n");
writel(0x00fffffc&0xffffffff,ivp_cae_base_addr+0x00000818);
if((readl(ivp_cae_base_addr+0x00000818)&0x00fffffc)==(0x00fffffc&0x00fffffc))
cnt++;
else
printf("cnt: 574\n");
writel(0x00110011&0xffffffff,ivp_cae_base_addr+0x0000081c);
if((readl(ivp_cae_base_addr+0x0000081c)&0xe0ff00ff)==(0x00110011&0xe0ff00ff))
cnt++;
else
printf("cnt: 575\n");
writel(0x20220022&0xffffffff,ivp_cae_base_addr+0x0000081c);
if((readl(ivp_cae_base_addr+0x0000081c)&0xe0ff00ff)==(0x20220022&0xe0ff00ff))
cnt++;
else
printf("cnt: 576\n");
writel(0x40440044&0xffffffff,ivp_cae_base_addr+0x0000081c);
if((readl(ivp_cae_base_addr+0x0000081c)&0xe0ff00ff)==(0x40440044&0xe0ff00ff))
cnt++;
else
printf("cnt: 577\n");
writel(0x80880088&0xffffffff,ivp_cae_base_addr+0x0000081c);
if((readl(ivp_cae_base_addr+0x0000081c)&0xe0ff00ff)==(0x80880088&0xe0ff00ff))
cnt++;
else
printf("cnt: 578\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000081c);
if((readl(ivp_cae_base_addr+0x0000081c)&0xe0ff00ff)==(0x00000000&0xe0ff00ff))
cnt++;
else
printf("cnt: 579\n");
writel(0xe0ff00ff&0xffffffff,ivp_cae_base_addr+0x0000081c);
if((readl(ivp_cae_base_addr+0x0000081c)&0xe0ff00ff)==(0xe0ff00ff&0xe0ff00ff))
cnt++;
else
printf("cnt: 580\n");
writel(0x10110011&0xffffffff,ivp_cae_base_addr+0x00000820);
if((readl(ivp_cae_base_addr+0x00000820)&0xf03f00ff)==(0x10110011&0xf03f00ff))
cnt++;
else
printf("cnt: 581\n");
writel(0x20220022&0xffffffff,ivp_cae_base_addr+0x00000820);
if((readl(ivp_cae_base_addr+0x00000820)&0xf03f00ff)==(0x20220022&0xf03f00ff))
cnt++;
else
printf("cnt: 582\n");
writel(0x40040044&0xffffffff,ivp_cae_base_addr+0x00000820);
if((readl(ivp_cae_base_addr+0x00000820)&0xf03f00ff)==(0x40040044&0xf03f00ff))
cnt++;
else
printf("cnt: 583\n");
writel(0x80080088&0xffffffff,ivp_cae_base_addr+0x00000820);
if((readl(ivp_cae_base_addr+0x00000820)&0xf03f00ff)==(0x80080088&0xf03f00ff))
cnt++;
else
printf("cnt: 584\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00000820);
if((readl(ivp_cae_base_addr+0x00000820)&0xf03f00ff)==(0x00000000&0xf03f00ff))
cnt++;
else
printf("cnt: 585\n");
writel(0xf03f00ff&0xffffffff,ivp_cae_base_addr+0x00000820);
if((readl(ivp_cae_base_addr+0x00000820)&0xf03f00ff)==(0xf03f00ff&0xf03f00ff))
cnt++;
else
printf("cnt: 586\n");
writel(0x11100101&0xffffffff,ivp_cae_base_addr+0x00000824);
if((readl(ivp_cae_base_addr+0x00000824)&0xfff80101)==(0x11100101&0xfff80101))
cnt++;
else
printf("cnt: 587\n");
writel(0x22200000&0xffffffff,ivp_cae_base_addr+0x00000824);
if((readl(ivp_cae_base_addr+0x00000824)&0xfff80101)==(0x22200000&0xfff80101))
cnt++;
else
printf("cnt: 588\n");
writel(0x44400000&0xffffffff,ivp_cae_base_addr+0x00000824);
if((readl(ivp_cae_base_addr+0x00000824)&0xfff80101)==(0x44400000&0xfff80101))
cnt++;
else
printf("cnt: 589\n");
writel(0x88880000&0xffffffff,ivp_cae_base_addr+0x00000824);
if((readl(ivp_cae_base_addr+0x00000824)&0xfff80101)==(0x88880000&0xfff80101))
cnt++;
else
printf("cnt: 590\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00000824);
if((readl(ivp_cae_base_addr+0x00000824)&0xfff80101)==(0x00000000&0xfff80101))
cnt++;
else
printf("cnt: 591\n");
writel(0xfff80101&0xffffffff,ivp_cae_base_addr+0x00000824);
if((readl(ivp_cae_base_addr+0x00000824)&0xfff80101)==(0xfff80101&0xfff80101))
cnt++;
else
printf("cnt: 592\n");
writel(0x11000000&0xffffffff,ivp_cae_base_addr+0x00000828);
if((readl(ivp_cae_base_addr+0x00000828)&0xff800000)==(0x11000000&0xff800000))
cnt++;
else
printf("cnt: 593\n");
writel(0x22000000&0xffffffff,ivp_cae_base_addr+0x00000828);
if((readl(ivp_cae_base_addr+0x00000828)&0xff800000)==(0x22000000&0xff800000))
cnt++;
else
printf("cnt: 594\n");
writel(0x44000000&0xffffffff,ivp_cae_base_addr+0x00000828);
if((readl(ivp_cae_base_addr+0x00000828)&0xff800000)==(0x44000000&0xff800000))
cnt++;
else
printf("cnt: 595\n");
writel(0x88800000&0xffffffff,ivp_cae_base_addr+0x00000828);
if((readl(ivp_cae_base_addr+0x00000828)&0xff800000)==(0x88800000&0xff800000))
cnt++;
else
printf("cnt: 596\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00000828);
if((readl(ivp_cae_base_addr+0x00000828)&0xff800000)==(0x00000000&0xff800000))
cnt++;
else
printf("cnt: 597\n");
writel(0xff800000&0xffffffff,ivp_cae_base_addr+0x00000828);
if((readl(ivp_cae_base_addr+0x00000828)&0xff800000)==(0xff800000&0xff800000))
cnt++;
else
printf("cnt: 598\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000082c);
if((readl(ivp_cae_base_addr+0x0000082c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 599\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000082c);
if((readl(ivp_cae_base_addr+0x0000082c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 600\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000082c);
if((readl(ivp_cae_base_addr+0x0000082c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 601\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000082c);
if((readl(ivp_cae_base_addr+0x0000082c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 602\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000082c);
if((readl(ivp_cae_base_addr+0x0000082c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 603\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000082c);
if((readl(ivp_cae_base_addr+0x0000082c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 604\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00000830);
if((readl(ivp_cae_base_addr+0x00000830)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 605\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00000830);
if((readl(ivp_cae_base_addr+0x00000830)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 606\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00000830);
if((readl(ivp_cae_base_addr+0x00000830)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 607\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00000830);
if((readl(ivp_cae_base_addr+0x00000830)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 608\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00000830);
if((readl(ivp_cae_base_addr+0x00000830)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 609\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00000830);
if((readl(ivp_cae_base_addr+0x00000830)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 610\n");
writel(0x00111110&0xffffffff,ivp_cae_base_addr+0x00000834);
if((readl(ivp_cae_base_addr+0x00000834)&0x00fffffc)==(0x00111110&0x00fffffc))
cnt++;
else
printf("cnt: 611\n");
writel(0x00222220&0xffffffff,ivp_cae_base_addr+0x00000834);
if((readl(ivp_cae_base_addr+0x00000834)&0x00fffffc)==(0x00222220&0x00fffffc))
cnt++;
else
printf("cnt: 612\n");
writel(0x00444444&0xffffffff,ivp_cae_base_addr+0x00000834);
if((readl(ivp_cae_base_addr+0x00000834)&0x00fffffc)==(0x00444444&0x00fffffc))
cnt++;
else
printf("cnt: 613\n");
writel(0x00888888&0xffffffff,ivp_cae_base_addr+0x00000834);
if((readl(ivp_cae_base_addr+0x00000834)&0x00fffffc)==(0x00888888&0x00fffffc))
cnt++;
else
printf("cnt: 614\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00000834);
if((readl(ivp_cae_base_addr+0x00000834)&0x00fffffc)==(0x00000000&0x00fffffc))
cnt++;
else
printf("cnt: 615\n");
writel(0x00fffffc&0xffffffff,ivp_cae_base_addr+0x00000834);
if((readl(ivp_cae_base_addr+0x00000834)&0x00fffffc)==(0x00fffffc&0x00fffffc))
cnt++;
else
printf("cnt: 616\n");
writel(0x00111110&0xffffffff,ivp_cae_base_addr+0x00000838);
if((readl(ivp_cae_base_addr+0x00000838)&0x00fffffc)==(0x00111110&0x00fffffc))
cnt++;
else
printf("cnt: 617\n");
writel(0x00222220&0xffffffff,ivp_cae_base_addr+0x00000838);
if((readl(ivp_cae_base_addr+0x00000838)&0x00fffffc)==(0x00222220&0x00fffffc))
cnt++;
else
printf("cnt: 618\n");
writel(0x00444444&0xffffffff,ivp_cae_base_addr+0x00000838);
if((readl(ivp_cae_base_addr+0x00000838)&0x00fffffc)==(0x00444444&0x00fffffc))
cnt++;
else
printf("cnt: 619\n");
writel(0x00888888&0xffffffff,ivp_cae_base_addr+0x00000838);
if((readl(ivp_cae_base_addr+0x00000838)&0x00fffffc)==(0x00888888&0x00fffffc))
cnt++;
else
printf("cnt: 620\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00000838);
if((readl(ivp_cae_base_addr+0x00000838)&0x00fffffc)==(0x00000000&0x00fffffc))
cnt++;
else
printf("cnt: 621\n");
writel(0x00fffffc&0xffffffff,ivp_cae_base_addr+0x00000838);
if((readl(ivp_cae_base_addr+0x00000838)&0x00fffffc)==(0x00fffffc&0x00fffffc))
cnt++;
else
printf("cnt: 622\n");
writel(0x00000011&0xffffffff,ivp_cae_base_addr+0x0000083c);
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000000)==(0x00000011&0x00000000))
cnt++;
else
printf("cnt: 623\n");
writel(0x00000022&0xffffffff,ivp_cae_base_addr+0x0000083c);
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000000)==(0x00000022&0x00000000))
cnt++;
else
printf("cnt: 624\n");
writel(0x00000044&0xffffffff,ivp_cae_base_addr+0x0000083c);
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000000)==(0x00000044&0x00000000))
cnt++;
else
printf("cnt: 625\n");
writel(0x00000088&0xffffffff,ivp_cae_base_addr+0x0000083c);
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000000)==(0x00000088&0x00000000))
cnt++;
else
printf("cnt: 626\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000083c);
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 627\n");
writel(0x000000ff&0xffffffff,ivp_cae_base_addr+0x0000083c);
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000000)==(0x000000ff&0x00000000))
cnt++;
else
printf("cnt: 628\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00000ff8);
if((readl(ivp_cae_base_addr+0x00000ff8)&0xb7ffffff)==(0x80a35514&0xb7ffffff))
cnt++;
else
printf("cnt: 629\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00000ff8);
if((readl(ivp_cae_base_addr+0x00000ff8)&0xb7ffffff)==(0x80a35514&0xb7ffffff))
cnt++;
else
printf("cnt: 630\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00000ff8);
if((readl(ivp_cae_base_addr+0x00000ff8)&0xb7ffffff)==(0x80a35514&0xb7ffffff))
cnt++;
else
printf("cnt: 631\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00000ff8);
if((readl(ivp_cae_base_addr+0x00000ff8)&0xb7ffffff)==(0x80a35514&0xb7ffffff))
cnt++;
else
printf("cnt: 632\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00000ff8);
if((readl(ivp_cae_base_addr+0x00000ff8)&0xb7ffffff)==(0x80a35514&0xb7ffffff))
cnt++;
else
printf("cnt: 633\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00000ff8);
if((readl(ivp_cae_base_addr+0x00000ff8)&0xb7ffffff)==(0x80a35514&0xb7ffffff))
cnt++;
else
printf("cnt: 634\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00000ffc);
if((readl(ivp_cae_base_addr+0x00000ffc)&0x0fffffff)==(0x027035ca&0x0fffffff))
cnt++;
else
printf("cnt: 635\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00000ffc);
if((readl(ivp_cae_base_addr+0x00000ffc)&0x0fffffff)==(0x027035ca&0x0fffffff))
cnt++;
else
printf("cnt: 636\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00000ffc);
if((readl(ivp_cae_base_addr+0x00000ffc)&0x0fffffff)==(0x027035ca&0x0fffffff))
cnt++;
else
printf("cnt: 637\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00000ffc);
if((readl(ivp_cae_base_addr+0x00000ffc)&0x0fffffff)==(0x027035ca&0x0fffffff))
cnt++;
else
printf("cnt: 638\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00000ffc);
if((readl(ivp_cae_base_addr+0x00000ffc)&0x0fffffff)==(0x027035ca&0x0fffffff))
cnt++;
else
printf("cnt: 639\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00000ffc);
if((readl(ivp_cae_base_addr+0x00000ffc)&0x0fffffff)==(0x027035ca&0x0fffffff))
cnt++;
else
printf("cnt: 640\n");
writel(0x11111111&0xffffffff,ivp_cae_base_addr+0x00001000);
if((readl(ivp_cae_base_addr+0x00001000)&0xffffffff)==(0x11111111&0xffffffff))
cnt++;
else
printf("cnt: 641\n");
writel(0x22222222&0xffffffff,ivp_cae_base_addr+0x00001000);
if((readl(ivp_cae_base_addr+0x00001000)&0xffffffff)==(0x22222222&0xffffffff))
cnt++;
else
printf("cnt: 642\n");
writel(0x44444444&0xffffffff,ivp_cae_base_addr+0x00001000);
if((readl(ivp_cae_base_addr+0x00001000)&0xffffffff)==(0x44444444&0xffffffff))
cnt++;
else
printf("cnt: 643\n");
writel(0x88888888&0xffffffff,ivp_cae_base_addr+0x00001000);
if((readl(ivp_cae_base_addr+0x00001000)&0xffffffff)==(0x88888888&0xffffffff))
cnt++;
else
printf("cnt: 644\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00001000);
if((readl(ivp_cae_base_addr+0x00001000)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 645\n");
writel(0xffffffff&0xffffffff,ivp_cae_base_addr+0x00001000);
if((readl(ivp_cae_base_addr+0x00001000)&0xffffffff)==(0xffffffff&0xffffffff))
cnt++;
else
printf("cnt: 646\n");
writel(0x11111111&0xffffffff,ivp_cae_base_addr+0x00001004);
if((readl(ivp_cae_base_addr+0x00001004)&0xffffffff)==(0x11111111&0xffffffff))
cnt++;
else
printf("cnt: 647\n");
writel(0x22222222&0xffffffff,ivp_cae_base_addr+0x00001004);
if((readl(ivp_cae_base_addr+0x00001004)&0xffffffff)==(0x22222222&0xffffffff))
cnt++;
else
printf("cnt: 648\n");
writel(0x44444444&0xffffffff,ivp_cae_base_addr+0x00001004);
if((readl(ivp_cae_base_addr+0x00001004)&0xffffffff)==(0x44444444&0xffffffff))
cnt++;
else
printf("cnt: 649\n");
writel(0x88888888&0xffffffff,ivp_cae_base_addr+0x00001004);
if((readl(ivp_cae_base_addr+0x00001004)&0xffffffff)==(0x88888888&0xffffffff))
cnt++;
else
printf("cnt: 650\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00001004);
if((readl(ivp_cae_base_addr+0x00001004)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 651\n");
writel(0xffffffff&0xffffffff,ivp_cae_base_addr+0x00001004);
if((readl(ivp_cae_base_addr+0x00001004)&0xffffffff)==(0xffffffff&0xffffffff))
cnt++;
else
printf("cnt: 652\n");
writel(0x11111111&0xffffffff,ivp_cae_base_addr+0x00001008);
if((readl(ivp_cae_base_addr+0x00001008)&0xffffffff)==(0x11111111&0xffffffff))
cnt++;
else
printf("cnt: 653\n");
writel(0x22222222&0xffffffff,ivp_cae_base_addr+0x00001008);
if((readl(ivp_cae_base_addr+0x00001008)&0xffffffff)==(0x22222222&0xffffffff))
cnt++;
else
printf("cnt: 654\n");
writel(0x44444444&0xffffffff,ivp_cae_base_addr+0x00001008);
if((readl(ivp_cae_base_addr+0x00001008)&0xffffffff)==(0x44444444&0xffffffff))
cnt++;
else
printf("cnt: 655\n");
writel(0x88888888&0xffffffff,ivp_cae_base_addr+0x00001008);
if((readl(ivp_cae_base_addr+0x00001008)&0xffffffff)==(0x88888888&0xffffffff))
cnt++;
else
printf("cnt: 656\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00001008);
if((readl(ivp_cae_base_addr+0x00001008)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 657\n");
writel(0xffffffff&0xffffffff,ivp_cae_base_addr+0x00001008);
if((readl(ivp_cae_base_addr+0x00001008)&0xffffffff)==(0xffffffff&0xffffffff))
cnt++;
else
printf("cnt: 658\n");
writel(0x11111111&0xffffffff,ivp_cae_base_addr+0x0000100c);
if((readl(ivp_cae_base_addr+0x0000100c)&0xffffffff)==(0x11111111&0xffffffff))
cnt++;
else
printf("cnt: 659\n");
writel(0x22222222&0xffffffff,ivp_cae_base_addr+0x0000100c);
if((readl(ivp_cae_base_addr+0x0000100c)&0xffffffff)==(0x22222222&0xffffffff))
cnt++;
else
printf("cnt: 660\n");
writel(0x44444444&0xffffffff,ivp_cae_base_addr+0x0000100c);
if((readl(ivp_cae_base_addr+0x0000100c)&0xffffffff)==(0x44444444&0xffffffff))
cnt++;
else
printf("cnt: 661\n");
writel(0x88888888&0xffffffff,ivp_cae_base_addr+0x0000100c);
if((readl(ivp_cae_base_addr+0x0000100c)&0xffffffff)==(0x88888888&0xffffffff))
cnt++;
else
printf("cnt: 662\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000100c);
if((readl(ivp_cae_base_addr+0x0000100c)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 663\n");
writel(0xffffffff&0xffffffff,ivp_cae_base_addr+0x0000100c);
if((readl(ivp_cae_base_addr+0x0000100c)&0xffffffff)==(0xffffffff&0xffffffff))
cnt++;
else
printf("cnt: 664\n");
writel(0x11111111&0xffffffff,ivp_cae_base_addr+0x00001010);
if((readl(ivp_cae_base_addr+0x00001010)&0xffffffff)==(0x11111111&0xffffffff))
cnt++;
else
printf("cnt: 665\n");
writel(0x22222222&0xffffffff,ivp_cae_base_addr+0x00001010);
if((readl(ivp_cae_base_addr+0x00001010)&0xffffffff)==(0x22222222&0xffffffff))
cnt++;
else
printf("cnt: 666\n");
writel(0x44444444&0xffffffff,ivp_cae_base_addr+0x00001010);
if((readl(ivp_cae_base_addr+0x00001010)&0xffffffff)==(0x44444444&0xffffffff))
cnt++;
else
printf("cnt: 667\n");
writel(0x88888888&0xffffffff,ivp_cae_base_addr+0x00001010);
if((readl(ivp_cae_base_addr+0x00001010)&0xffffffff)==(0x88888888&0xffffffff))
cnt++;
else
printf("cnt: 668\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00001010);
if((readl(ivp_cae_base_addr+0x00001010)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 669\n");
writel(0xffffffff&0xffffffff,ivp_cae_base_addr+0x00001010);
if((readl(ivp_cae_base_addr+0x00001010)&0xffffffff)==(0xffffffff&0xffffffff))
cnt++;
else
printf("cnt: 670\n");
writel(0x11111111&0xffffffff,ivp_cae_base_addr+0x00001014);
if((readl(ivp_cae_base_addr+0x00001014)&0xffffffff)==(0x11111111&0xffffffff))
cnt++;
else
printf("cnt: 671\n");
writel(0x22222222&0xffffffff,ivp_cae_base_addr+0x00001014);
if((readl(ivp_cae_base_addr+0x00001014)&0xffffffff)==(0x22222222&0xffffffff))
cnt++;
else
printf("cnt: 672\n");
writel(0x44444444&0xffffffff,ivp_cae_base_addr+0x00001014);
if((readl(ivp_cae_base_addr+0x00001014)&0xffffffff)==(0x44444444&0xffffffff))
cnt++;
else
printf("cnt: 673\n");
writel(0x88888888&0xffffffff,ivp_cae_base_addr+0x00001014);
if((readl(ivp_cae_base_addr+0x00001014)&0xffffffff)==(0x88888888&0xffffffff))
cnt++;
else
printf("cnt: 674\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00001014);
if((readl(ivp_cae_base_addr+0x00001014)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 675\n");
writel(0xffffffff&0xffffffff,ivp_cae_base_addr+0x00001014);
if((readl(ivp_cae_base_addr+0x00001014)&0xffffffff)==(0xffffffff&0xffffffff))
cnt++;
else
printf("cnt: 676\n");
writel(0x00111110&0xffffffff,ivp_cae_base_addr+0x00001018);
if((readl(ivp_cae_base_addr+0x00001018)&0x00fffffc)==(0x00111110&0x00fffffc))
cnt++;
else
printf("cnt: 677\n");
writel(0x00222220&0xffffffff,ivp_cae_base_addr+0x00001018);
if((readl(ivp_cae_base_addr+0x00001018)&0x00fffffc)==(0x00222220&0x00fffffc))
cnt++;
else
printf("cnt: 678\n");
writel(0x00444444&0xffffffff,ivp_cae_base_addr+0x00001018);
if((readl(ivp_cae_base_addr+0x00001018)&0x00fffffc)==(0x00444444&0x00fffffc))
cnt++;
else
printf("cnt: 679\n");
writel(0x00888888&0xffffffff,ivp_cae_base_addr+0x00001018);
if((readl(ivp_cae_base_addr+0x00001018)&0x00fffffc)==(0x00888888&0x00fffffc))
cnt++;
else
printf("cnt: 680\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00001018);
if((readl(ivp_cae_base_addr+0x00001018)&0x00fffffc)==(0x00000000&0x00fffffc))
cnt++;
else
printf("cnt: 681\n");
writel(0x00fffffc&0xffffffff,ivp_cae_base_addr+0x00001018);
if((readl(ivp_cae_base_addr+0x00001018)&0x00fffffc)==(0x00fffffc&0x00fffffc))
cnt++;
else
printf("cnt: 682\n");
writel(0x00110011&0xffffffff,ivp_cae_base_addr+0x0000101c);
if((readl(ivp_cae_base_addr+0x0000101c)&0xe0ff003f)==(0x00110011&0xe0ff003f))
cnt++;
else
printf("cnt: 683\n");
writel(0x20220022&0xffffffff,ivp_cae_base_addr+0x0000101c);
if((readl(ivp_cae_base_addr+0x0000101c)&0xe0ff003f)==(0x20220022&0xe0ff003f))
cnt++;
else
printf("cnt: 684\n");
writel(0x40440004&0xffffffff,ivp_cae_base_addr+0x0000101c);
if((readl(ivp_cae_base_addr+0x0000101c)&0xe0ff003f)==(0x40440004&0xe0ff003f))
cnt++;
else
printf("cnt: 685\n");
writel(0x80880008&0xffffffff,ivp_cae_base_addr+0x0000101c);
if((readl(ivp_cae_base_addr+0x0000101c)&0xe0ff003f)==(0x80880008&0xe0ff003f))
cnt++;
else
printf("cnt: 686\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000101c);
if((readl(ivp_cae_base_addr+0x0000101c)&0xe0ff003f)==(0x00000000&0xe0ff003f))
cnt++;
else
printf("cnt: 687\n");
writel(0xe0ff003f&0xffffffff,ivp_cae_base_addr+0x0000101c);
if((readl(ivp_cae_base_addr+0x0000101c)&0xe0ff003f)==(0xe0ff003f&0xe0ff003f))
cnt++;
else
printf("cnt: 688\n");
writel(0x10110011&0xffffffff,ivp_cae_base_addr+0x00001020);
if((readl(ivp_cae_base_addr+0x00001020)&0xf03f00ff)==(0x10110011&0xf03f00ff))
cnt++;
else
printf("cnt: 689\n");
writel(0x20220022&0xffffffff,ivp_cae_base_addr+0x00001020);
if((readl(ivp_cae_base_addr+0x00001020)&0xf03f00ff)==(0x20220022&0xf03f00ff))
cnt++;
else
printf("cnt: 690\n");
writel(0x40040044&0xffffffff,ivp_cae_base_addr+0x00001020);
if((readl(ivp_cae_base_addr+0x00001020)&0xf03f00ff)==(0x40040044&0xf03f00ff))
cnt++;
else
printf("cnt: 691\n");
writel(0x80080088&0xffffffff,ivp_cae_base_addr+0x00001020);
if((readl(ivp_cae_base_addr+0x00001020)&0xf03f00ff)==(0x80080088&0xf03f00ff))
cnt++;
else
printf("cnt: 692\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00001020);
if((readl(ivp_cae_base_addr+0x00001020)&0xf03f00ff)==(0x00000000&0xf03f00ff))
cnt++;
else
printf("cnt: 693\n");
writel(0xf03f00ff&0xffffffff,ivp_cae_base_addr+0x00001020);
if((readl(ivp_cae_base_addr+0x00001020)&0xf03f00ff)==(0xf03f00ff&0xf03f00ff))
cnt++;
else
printf("cnt: 694\n");
writel(0x11010101&0xffffffff,ivp_cae_base_addr+0x00001024);
if((readl(ivp_cae_base_addr+0x00001024)&0xff010101)==(0x11010101&0xff010101))
cnt++;
else
printf("cnt: 695\n");
writel(0x22000000&0xffffffff,ivp_cae_base_addr+0x00001024);
if((readl(ivp_cae_base_addr+0x00001024)&0xff010101)==(0x22000000&0xff010101))
cnt++;
else
printf("cnt: 696\n");
writel(0x44000000&0xffffffff,ivp_cae_base_addr+0x00001024);
if((readl(ivp_cae_base_addr+0x00001024)&0xff010101)==(0x44000000&0xff010101))
cnt++;
else
printf("cnt: 697\n");
writel(0x88000000&0xffffffff,ivp_cae_base_addr+0x00001024);
if((readl(ivp_cae_base_addr+0x00001024)&0xff010101)==(0x88000000&0xff010101))
cnt++;
else
printf("cnt: 698\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00001024);
if((readl(ivp_cae_base_addr+0x00001024)&0xff010101)==(0x00000000&0xff010101))
cnt++;
else
printf("cnt: 699\n");
writel(0xff010101&0xffffffff,ivp_cae_base_addr+0x00001024);
if((readl(ivp_cae_base_addr+0x00001024)&0xff010101)==(0xff010101&0xff010101))
cnt++;
else
printf("cnt: 700\n");
writel(0x11000000&0xffffffff,ivp_cae_base_addr+0x00001028);
if((readl(ivp_cae_base_addr+0x00001028)&0xffc00000)==(0x11000000&0xffc00000))
cnt++;
else
printf("cnt: 701\n");
writel(0x22000000&0xffffffff,ivp_cae_base_addr+0x00001028);
if((readl(ivp_cae_base_addr+0x00001028)&0xffc00000)==(0x22000000&0xffc00000))
cnt++;
else
printf("cnt: 702\n");
writel(0x44400000&0xffffffff,ivp_cae_base_addr+0x00001028);
if((readl(ivp_cae_base_addr+0x00001028)&0xffc00000)==(0x44400000&0xffc00000))
cnt++;
else
printf("cnt: 703\n");
writel(0x88800000&0xffffffff,ivp_cae_base_addr+0x00001028);
if((readl(ivp_cae_base_addr+0x00001028)&0xffc00000)==(0x88800000&0xffc00000))
cnt++;
else
printf("cnt: 704\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00001028);
if((readl(ivp_cae_base_addr+0x00001028)&0xffc00000)==(0x00000000&0xffc00000))
cnt++;
else
printf("cnt: 705\n");
writel(0xffc00000&0xffffffff,ivp_cae_base_addr+0x00001028);
if((readl(ivp_cae_base_addr+0x00001028)&0xffc00000)==(0xffc00000&0xffc00000))
cnt++;
else
printf("cnt: 706\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000102c);
if((readl(ivp_cae_base_addr+0x0000102c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 707\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000102c);
if((readl(ivp_cae_base_addr+0x0000102c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 708\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000102c);
if((readl(ivp_cae_base_addr+0x0000102c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 709\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000102c);
if((readl(ivp_cae_base_addr+0x0000102c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 710\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000102c);
if((readl(ivp_cae_base_addr+0x0000102c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 711\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000102c);
if((readl(ivp_cae_base_addr+0x0000102c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 712\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00001030);
if((readl(ivp_cae_base_addr+0x00001030)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 713\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00001030);
if((readl(ivp_cae_base_addr+0x00001030)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 714\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00001030);
if((readl(ivp_cae_base_addr+0x00001030)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 715\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00001030);
if((readl(ivp_cae_base_addr+0x00001030)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 716\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00001030);
if((readl(ivp_cae_base_addr+0x00001030)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 717\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00001030);
if((readl(ivp_cae_base_addr+0x00001030)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 718\n");
writel(0x00111110&0xffffffff,ivp_cae_base_addr+0x00001034);
if((readl(ivp_cae_base_addr+0x00001034)&0x00fffffc)==(0x00111110&0x00fffffc))
cnt++;
else
printf("cnt: 719\n");
writel(0x00222220&0xffffffff,ivp_cae_base_addr+0x00001034);
if((readl(ivp_cae_base_addr+0x00001034)&0x00fffffc)==(0x00222220&0x00fffffc))
cnt++;
else
printf("cnt: 720\n");
writel(0x00444444&0xffffffff,ivp_cae_base_addr+0x00001034);
if((readl(ivp_cae_base_addr+0x00001034)&0x00fffffc)==(0x00444444&0x00fffffc))
cnt++;
else
printf("cnt: 721\n");
writel(0x00888888&0xffffffff,ivp_cae_base_addr+0x00001034);
if((readl(ivp_cae_base_addr+0x00001034)&0x00fffffc)==(0x00888888&0x00fffffc))
cnt++;
else
printf("cnt: 722\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00001034);
if((readl(ivp_cae_base_addr+0x00001034)&0x00fffffc)==(0x00000000&0x00fffffc))
cnt++;
else
printf("cnt: 723\n");
writel(0x00fffffc&0xffffffff,ivp_cae_base_addr+0x00001034);
if((readl(ivp_cae_base_addr+0x00001034)&0x00fffffc)==(0x00fffffc&0x00fffffc))
cnt++;
else
printf("cnt: 724\n");
writel(0x00111110&0xffffffff,ivp_cae_base_addr+0x00001038);
if((readl(ivp_cae_base_addr+0x00001038)&0x00fffffc)==(0x00111110&0x00fffffc))
cnt++;
else
printf("cnt: 725\n");
writel(0x00222220&0xffffffff,ivp_cae_base_addr+0x00001038);
if((readl(ivp_cae_base_addr+0x00001038)&0x00fffffc)==(0x00222220&0x00fffffc))
cnt++;
else
printf("cnt: 726\n");
writel(0x00444444&0xffffffff,ivp_cae_base_addr+0x00001038);
if((readl(ivp_cae_base_addr+0x00001038)&0x00fffffc)==(0x00444444&0x00fffffc))
cnt++;
else
printf("cnt: 727\n");
writel(0x00888888&0xffffffff,ivp_cae_base_addr+0x00001038);
if((readl(ivp_cae_base_addr+0x00001038)&0x00fffffc)==(0x00888888&0x00fffffc))
cnt++;
else
printf("cnt: 728\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00001038);
if((readl(ivp_cae_base_addr+0x00001038)&0x00fffffc)==(0x00000000&0x00fffffc))
cnt++;
else
printf("cnt: 729\n");
writel(0x00fffffc&0xffffffff,ivp_cae_base_addr+0x00001038);
if((readl(ivp_cae_base_addr+0x00001038)&0x00fffffc)==(0x00fffffc&0x00fffffc))
cnt++;
else
printf("cnt: 730\n");
writel(0x00000011&0xffffffff,ivp_cae_base_addr+0x0000103c);
if((readl(ivp_cae_base_addr+0x0000103c)&0x00000000)==(0x00000011&0x00000000))
cnt++;
else
printf("cnt: 731\n");
writel(0x00000022&0xffffffff,ivp_cae_base_addr+0x0000103c);
if((readl(ivp_cae_base_addr+0x0000103c)&0x00000000)==(0x00000022&0x00000000))
cnt++;
else
printf("cnt: 732\n");
writel(0x00000004&0xffffffff,ivp_cae_base_addr+0x0000103c);
if((readl(ivp_cae_base_addr+0x0000103c)&0x00000000)==(0x00000004&0x00000000))
cnt++;
else
printf("cnt: 733\n");
writel(0x00000008&0xffffffff,ivp_cae_base_addr+0x0000103c);
if((readl(ivp_cae_base_addr+0x0000103c)&0x00000000)==(0x00000008&0x00000000))
cnt++;
else
printf("cnt: 734\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000103c);
if((readl(ivp_cae_base_addr+0x0000103c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 735\n");
writel(0x0000003f&0xffffffff,ivp_cae_base_addr+0x0000103c);
if((readl(ivp_cae_base_addr+0x0000103c)&0x00000000)==(0x0000003f&0x00000000))
cnt++;
else
printf("cnt: 736\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000017f8);
if((readl(ivp_cae_base_addr+0x000017f8)&0xb7ffffff)==(0x80a35514&0xb7ffffff))
cnt++;
else
printf("cnt: 737\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000017f8);
if((readl(ivp_cae_base_addr+0x000017f8)&0xb7ffffff)==(0x80a35514&0xb7ffffff))
cnt++;
else
printf("cnt: 738\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000017f8);
if((readl(ivp_cae_base_addr+0x000017f8)&0xb7ffffff)==(0x80a35514&0xb7ffffff))
cnt++;
else
printf("cnt: 739\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000017f8);
if((readl(ivp_cae_base_addr+0x000017f8)&0xb7ffffff)==(0x80a35514&0xb7ffffff))
cnt++;
else
printf("cnt: 740\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000017f8);
if((readl(ivp_cae_base_addr+0x000017f8)&0xb7ffffff)==(0x80a35514&0xb7ffffff))
cnt++;
else
printf("cnt: 741\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000017f8);
if((readl(ivp_cae_base_addr+0x000017f8)&0xb7ffffff)==(0x80a35514&0xb7ffffff))
cnt++;
else
printf("cnt: 742\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000017fc);
if((readl(ivp_cae_base_addr+0x000017fc)&0x0fffffff)==(0x027035ca&0x0fffffff))
cnt++;
else
printf("cnt: 743\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000017fc);
if((readl(ivp_cae_base_addr+0x000017fc)&0x0fffffff)==(0x027035ca&0x0fffffff))
cnt++;
else
printf("cnt: 744\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000017fc);
if((readl(ivp_cae_base_addr+0x000017fc)&0x0fffffff)==(0x027035ca&0x0fffffff))
cnt++;
else
printf("cnt: 745\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000017fc);
if((readl(ivp_cae_base_addr+0x000017fc)&0x0fffffff)==(0x027035ca&0x0fffffff))
cnt++;
else
printf("cnt: 746\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000017fc);
if((readl(ivp_cae_base_addr+0x000017fc)&0x0fffffff)==(0x027035ca&0x0fffffff))
cnt++;
else
printf("cnt: 747\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000017fc);
if((readl(ivp_cae_base_addr+0x000017fc)&0x0fffffff)==(0x027035ca&0x0fffffff))
cnt++;
else
printf("cnt: 748\n");
writel(0x11111111&0xffffffff,ivp_cae_base_addr+0x00001800);
if((readl(ivp_cae_base_addr+0x00001800)&0xffffffff)==(0x11111111&0xffffffff))
cnt++;
else
printf("cnt: 749\n");
writel(0x22222222&0xffffffff,ivp_cae_base_addr+0x00001800);
if((readl(ivp_cae_base_addr+0x00001800)&0xffffffff)==(0x22222222&0xffffffff))
cnt++;
else
printf("cnt: 750\n");
writel(0x44444444&0xffffffff,ivp_cae_base_addr+0x00001800);
if((readl(ivp_cae_base_addr+0x00001800)&0xffffffff)==(0x44444444&0xffffffff))
cnt++;
else
printf("cnt: 751\n");
writel(0x88888888&0xffffffff,ivp_cae_base_addr+0x00001800);
if((readl(ivp_cae_base_addr+0x00001800)&0xffffffff)==(0x88888888&0xffffffff))
cnt++;
else
printf("cnt: 752\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00001800);
if((readl(ivp_cae_base_addr+0x00001800)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 753\n");
writel(0xffffffff&0xffffffff,ivp_cae_base_addr+0x00001800);
if((readl(ivp_cae_base_addr+0x00001800)&0xffffffff)==(0xffffffff&0xffffffff))
cnt++;
else
printf("cnt: 754\n");
writel(0x11111111&0xffffffff,ivp_cae_base_addr+0x00001804);
if((readl(ivp_cae_base_addr+0x00001804)&0xffffffff)==(0x11111111&0xffffffff))
cnt++;
else
printf("cnt: 755\n");
writel(0x22222222&0xffffffff,ivp_cae_base_addr+0x00001804);
if((readl(ivp_cae_base_addr+0x00001804)&0xffffffff)==(0x22222222&0xffffffff))
cnt++;
else
printf("cnt: 756\n");
writel(0x44444444&0xffffffff,ivp_cae_base_addr+0x00001804);
if((readl(ivp_cae_base_addr+0x00001804)&0xffffffff)==(0x44444444&0xffffffff))
cnt++;
else
printf("cnt: 757\n");
writel(0x88888888&0xffffffff,ivp_cae_base_addr+0x00001804);
if((readl(ivp_cae_base_addr+0x00001804)&0xffffffff)==(0x88888888&0xffffffff))
cnt++;
else
printf("cnt: 758\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00001804);
if((readl(ivp_cae_base_addr+0x00001804)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 759\n");
writel(0xffffffff&0xffffffff,ivp_cae_base_addr+0x00001804);
if((readl(ivp_cae_base_addr+0x00001804)&0xffffffff)==(0xffffffff&0xffffffff))
cnt++;
else
printf("cnt: 760\n");
writel(0x11111111&0xffffffff,ivp_cae_base_addr+0x00001808);
if((readl(ivp_cae_base_addr+0x00001808)&0xffffffff)==(0x11111111&0xffffffff))
cnt++;
else
printf("cnt: 761\n");
writel(0x22222222&0xffffffff,ivp_cae_base_addr+0x00001808);
if((readl(ivp_cae_base_addr+0x00001808)&0xffffffff)==(0x22222222&0xffffffff))
cnt++;
else
printf("cnt: 762\n");
writel(0x44444444&0xffffffff,ivp_cae_base_addr+0x00001808);
if((readl(ivp_cae_base_addr+0x00001808)&0xffffffff)==(0x44444444&0xffffffff))
cnt++;
else
printf("cnt: 763\n");
writel(0x88888888&0xffffffff,ivp_cae_base_addr+0x00001808);
if((readl(ivp_cae_base_addr+0x00001808)&0xffffffff)==(0x88888888&0xffffffff))
cnt++;
else
printf("cnt: 764\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00001808);
if((readl(ivp_cae_base_addr+0x00001808)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 765\n");
writel(0xffffffff&0xffffffff,ivp_cae_base_addr+0x00001808);
if((readl(ivp_cae_base_addr+0x00001808)&0xffffffff)==(0xffffffff&0xffffffff))
cnt++;
else
printf("cnt: 766\n");
writel(0x11111111&0xffffffff,ivp_cae_base_addr+0x0000180c);
if((readl(ivp_cae_base_addr+0x0000180c)&0xffffffff)==(0x11111111&0xffffffff))
cnt++;
else
printf("cnt: 767\n");
writel(0x22222222&0xffffffff,ivp_cae_base_addr+0x0000180c);
if((readl(ivp_cae_base_addr+0x0000180c)&0xffffffff)==(0x22222222&0xffffffff))
cnt++;
else
printf("cnt: 768\n");
writel(0x44444444&0xffffffff,ivp_cae_base_addr+0x0000180c);
if((readl(ivp_cae_base_addr+0x0000180c)&0xffffffff)==(0x44444444&0xffffffff))
cnt++;
else
printf("cnt: 769\n");
writel(0x88888888&0xffffffff,ivp_cae_base_addr+0x0000180c);
if((readl(ivp_cae_base_addr+0x0000180c)&0xffffffff)==(0x88888888&0xffffffff))
cnt++;
else
printf("cnt: 770\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000180c);
if((readl(ivp_cae_base_addr+0x0000180c)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 771\n");
writel(0xffffffff&0xffffffff,ivp_cae_base_addr+0x0000180c);
if((readl(ivp_cae_base_addr+0x0000180c)&0xffffffff)==(0xffffffff&0xffffffff))
cnt++;
else
printf("cnt: 772\n");
writel(0x00111110&0xffffffff,ivp_cae_base_addr+0x00001818);
if((readl(ivp_cae_base_addr+0x00001818)&0x00fffffc)==(0x00111110&0x00fffffc))
cnt++;
else
printf("cnt: 773\n");
writel(0x00222220&0xffffffff,ivp_cae_base_addr+0x00001818);
if((readl(ivp_cae_base_addr+0x00001818)&0x00fffffc)==(0x00222220&0x00fffffc))
cnt++;
else
printf("cnt: 774\n");
writel(0x00444444&0xffffffff,ivp_cae_base_addr+0x00001818);
if((readl(ivp_cae_base_addr+0x00001818)&0x00fffffc)==(0x00444444&0x00fffffc))
cnt++;
else
printf("cnt: 775\n");
writel(0x00888888&0xffffffff,ivp_cae_base_addr+0x00001818);
if((readl(ivp_cae_base_addr+0x00001818)&0x00fffffc)==(0x00888888&0x00fffffc))
cnt++;
else
printf("cnt: 776\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00001818);
if((readl(ivp_cae_base_addr+0x00001818)&0x00fffffc)==(0x00000000&0x00fffffc))
cnt++;
else
printf("cnt: 777\n");
writel(0x00fffffc&0xffffffff,ivp_cae_base_addr+0x00001818);
if((readl(ivp_cae_base_addr+0x00001818)&0x00fffffc)==(0x00fffffc&0x00fffffc))
cnt++;
else
printf("cnt: 778\n");
writel(0x00110011&0xffffffff,ivp_cae_base_addr+0x0000181c);
if((readl(ivp_cae_base_addr+0x0000181c)&0xe0ff00ff)==(0x00110011&0xe0ff00ff))
cnt++;
else
printf("cnt: 779\n");
writel(0x20220022&0xffffffff,ivp_cae_base_addr+0x0000181c);
if((readl(ivp_cae_base_addr+0x0000181c)&0xe0ff00ff)==(0x20220022&0xe0ff00ff))
cnt++;
else
printf("cnt: 780\n");
writel(0x40440044&0xffffffff,ivp_cae_base_addr+0x0000181c);
if((readl(ivp_cae_base_addr+0x0000181c)&0xe0ff00ff)==(0x40440044&0xe0ff00ff))
cnt++;
else
printf("cnt: 781\n");
writel(0x80880088&0xffffffff,ivp_cae_base_addr+0x0000181c);
if((readl(ivp_cae_base_addr+0x0000181c)&0xe0ff00ff)==(0x80880088&0xe0ff00ff))
cnt++;
else
printf("cnt: 782\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000181c);
if((readl(ivp_cae_base_addr+0x0000181c)&0xe0ff00ff)==(0x00000000&0xe0ff00ff))
cnt++;
else
printf("cnt: 783\n");
writel(0xe0ff00ff&0xffffffff,ivp_cae_base_addr+0x0000181c);
if((readl(ivp_cae_base_addr+0x0000181c)&0xe0ff00ff)==(0xe0ff00ff&0xe0ff00ff))
cnt++;
else
printf("cnt: 784\n");
writel(0x10110011&0xffffffff,ivp_cae_base_addr+0x00001820);
if((readl(ivp_cae_base_addr+0x00001820)&0xf03f00ff)==(0x10110011&0xf03f00ff))
cnt++;
else
printf("cnt: 785\n");
writel(0x20220022&0xffffffff,ivp_cae_base_addr+0x00001820);
if((readl(ivp_cae_base_addr+0x00001820)&0xf03f00ff)==(0x20220022&0xf03f00ff))
cnt++;
else
printf("cnt: 786\n");
writel(0x40040044&0xffffffff,ivp_cae_base_addr+0x00001820);
if((readl(ivp_cae_base_addr+0x00001820)&0xf03f00ff)==(0x40040044&0xf03f00ff))
cnt++;
else
printf("cnt: 787\n");
writel(0x80080088&0xffffffff,ivp_cae_base_addr+0x00001820);
if((readl(ivp_cae_base_addr+0x00001820)&0xf03f00ff)==(0x80080088&0xf03f00ff))
cnt++;
else
printf("cnt: 788\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00001820);
if((readl(ivp_cae_base_addr+0x00001820)&0xf03f00ff)==(0x00000000&0xf03f00ff))
cnt++;
else
printf("cnt: 789\n");
writel(0xf03f00ff&0xffffffff,ivp_cae_base_addr+0x00001820);
if((readl(ivp_cae_base_addr+0x00001820)&0xf03f00ff)==(0xf03f00ff&0xf03f00ff))
cnt++;
else
printf("cnt: 790\n");
writel(0x11100101&0xffffffff,ivp_cae_base_addr+0x00001824);
if((readl(ivp_cae_base_addr+0x00001824)&0xfff80101)==(0x11100101&0xfff80101))
cnt++;
else
printf("cnt: 791\n");
writel(0x22200000&0xffffffff,ivp_cae_base_addr+0x00001824);
if((readl(ivp_cae_base_addr+0x00001824)&0xfff80101)==(0x22200000&0xfff80101))
cnt++;
else
printf("cnt: 792\n");
writel(0x44400000&0xffffffff,ivp_cae_base_addr+0x00001824);
if((readl(ivp_cae_base_addr+0x00001824)&0xfff80101)==(0x44400000&0xfff80101))
cnt++;
else
printf("cnt: 793\n");
writel(0x88880000&0xffffffff,ivp_cae_base_addr+0x00001824);
if((readl(ivp_cae_base_addr+0x00001824)&0xfff80101)==(0x88880000&0xfff80101))
cnt++;
else
printf("cnt: 794\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00001824);
if((readl(ivp_cae_base_addr+0x00001824)&0xfff80101)==(0x00000000&0xfff80101))
cnt++;
else
printf("cnt: 795\n");
writel(0xfff80101&0xffffffff,ivp_cae_base_addr+0x00001824);
if((readl(ivp_cae_base_addr+0x00001824)&0xfff80101)==(0xfff80101&0xfff80101))
cnt++;
else
printf("cnt: 796\n");
writel(0x11000000&0xffffffff,ivp_cae_base_addr+0x00001828);
if((readl(ivp_cae_base_addr+0x00001828)&0xff800000)==(0x11000000&0xff800000))
cnt++;
else
printf("cnt: 797\n");
writel(0x22000000&0xffffffff,ivp_cae_base_addr+0x00001828);
if((readl(ivp_cae_base_addr+0x00001828)&0xff800000)==(0x22000000&0xff800000))
cnt++;
else
printf("cnt: 798\n");
writel(0x44000000&0xffffffff,ivp_cae_base_addr+0x00001828);
if((readl(ivp_cae_base_addr+0x00001828)&0xff800000)==(0x44000000&0xff800000))
cnt++;
else
printf("cnt: 799\n");
writel(0x88800000&0xffffffff,ivp_cae_base_addr+0x00001828);
if((readl(ivp_cae_base_addr+0x00001828)&0xff800000)==(0x88800000&0xff800000))
cnt++;
else
printf("cnt: 800\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00001828);
if((readl(ivp_cae_base_addr+0x00001828)&0xff800000)==(0x00000000&0xff800000))
cnt++;
else
printf("cnt: 801\n");
writel(0xff800000&0xffffffff,ivp_cae_base_addr+0x00001828);
if((readl(ivp_cae_base_addr+0x00001828)&0xff800000)==(0xff800000&0xff800000))
cnt++;
else
printf("cnt: 802\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000182c);
if((readl(ivp_cae_base_addr+0x0000182c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 803\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000182c);
if((readl(ivp_cae_base_addr+0x0000182c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 804\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000182c);
if((readl(ivp_cae_base_addr+0x0000182c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 805\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000182c);
if((readl(ivp_cae_base_addr+0x0000182c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 806\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000182c);
if((readl(ivp_cae_base_addr+0x0000182c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 807\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000182c);
if((readl(ivp_cae_base_addr+0x0000182c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 808\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00001830);
if((readl(ivp_cae_base_addr+0x00001830)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 809\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00001830);
if((readl(ivp_cae_base_addr+0x00001830)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 810\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00001830);
if((readl(ivp_cae_base_addr+0x00001830)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 811\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00001830);
if((readl(ivp_cae_base_addr+0x00001830)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 812\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00001830);
if((readl(ivp_cae_base_addr+0x00001830)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 813\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00001830);
if((readl(ivp_cae_base_addr+0x00001830)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 814\n");
writel(0x00111110&0xffffffff,ivp_cae_base_addr+0x00001834);
if((readl(ivp_cae_base_addr+0x00001834)&0x00fffffc)==(0x00111110&0x00fffffc))
cnt++;
else
printf("cnt: 815\n");
writel(0x00222220&0xffffffff,ivp_cae_base_addr+0x00001834);
if((readl(ivp_cae_base_addr+0x00001834)&0x00fffffc)==(0x00222220&0x00fffffc))
cnt++;
else
printf("cnt: 816\n");
writel(0x00444444&0xffffffff,ivp_cae_base_addr+0x00001834);
if((readl(ivp_cae_base_addr+0x00001834)&0x00fffffc)==(0x00444444&0x00fffffc))
cnt++;
else
printf("cnt: 817\n");
writel(0x00888888&0xffffffff,ivp_cae_base_addr+0x00001834);
if((readl(ivp_cae_base_addr+0x00001834)&0x00fffffc)==(0x00888888&0x00fffffc))
cnt++;
else
printf("cnt: 818\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00001834);
if((readl(ivp_cae_base_addr+0x00001834)&0x00fffffc)==(0x00000000&0x00fffffc))
cnt++;
else
printf("cnt: 819\n");
writel(0x00fffffc&0xffffffff,ivp_cae_base_addr+0x00001834);
if((readl(ivp_cae_base_addr+0x00001834)&0x00fffffc)==(0x00fffffc&0x00fffffc))
cnt++;
else
printf("cnt: 820\n");
writel(0x00111110&0xffffffff,ivp_cae_base_addr+0x00001838);
if((readl(ivp_cae_base_addr+0x00001838)&0x00fffffc)==(0x00111110&0x00fffffc))
cnt++;
else
printf("cnt: 821\n");
writel(0x00222220&0xffffffff,ivp_cae_base_addr+0x00001838);
if((readl(ivp_cae_base_addr+0x00001838)&0x00fffffc)==(0x00222220&0x00fffffc))
cnt++;
else
printf("cnt: 822\n");
writel(0x00444444&0xffffffff,ivp_cae_base_addr+0x00001838);
if((readl(ivp_cae_base_addr+0x00001838)&0x00fffffc)==(0x00444444&0x00fffffc))
cnt++;
else
printf("cnt: 823\n");
writel(0x00888888&0xffffffff,ivp_cae_base_addr+0x00001838);
if((readl(ivp_cae_base_addr+0x00001838)&0x00fffffc)==(0x00888888&0x00fffffc))
cnt++;
else
printf("cnt: 824\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00001838);
if((readl(ivp_cae_base_addr+0x00001838)&0x00fffffc)==(0x00000000&0x00fffffc))
cnt++;
else
printf("cnt: 825\n");
writel(0x00fffffc&0xffffffff,ivp_cae_base_addr+0x00001838);
if((readl(ivp_cae_base_addr+0x00001838)&0x00fffffc)==(0x00fffffc&0x00fffffc))
cnt++;
else
printf("cnt: 826\n");
writel(0x00000011&0xffffffff,ivp_cae_base_addr+0x0000183c);
if((readl(ivp_cae_base_addr+0x0000183c)&0x00000000)==(0x00000011&0x00000000))
cnt++;
else
printf("cnt: 827\n");
writel(0x00000022&0xffffffff,ivp_cae_base_addr+0x0000183c);
if((readl(ivp_cae_base_addr+0x0000183c)&0x00000000)==(0x00000022&0x00000000))
cnt++;
else
printf("cnt: 828\n");
writel(0x00000044&0xffffffff,ivp_cae_base_addr+0x0000183c);
if((readl(ivp_cae_base_addr+0x0000183c)&0x00000000)==(0x00000044&0x00000000))
cnt++;
else
printf("cnt: 829\n");
writel(0x00000088&0xffffffff,ivp_cae_base_addr+0x0000183c);
if((readl(ivp_cae_base_addr+0x0000183c)&0x00000000)==(0x00000088&0x00000000))
cnt++;
else
printf("cnt: 830\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000183c);
if((readl(ivp_cae_base_addr+0x0000183c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 831\n");
writel(0x000000ff&0xffffffff,ivp_cae_base_addr+0x0000183c);
if((readl(ivp_cae_base_addr+0x0000183c)&0x00000000)==(0x000000ff&0x00000000))
cnt++;
else
printf("cnt: 832\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00001ff8);
if((readl(ivp_cae_base_addr+0x00001ff8)&0xb7ffffff)==(0x80a35514&0xb7ffffff))
cnt++;
else
printf("cnt: 833\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00001ff8);
if((readl(ivp_cae_base_addr+0x00001ff8)&0xb7ffffff)==(0x80a35514&0xb7ffffff))
cnt++;
else
printf("cnt: 834\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00001ff8);
if((readl(ivp_cae_base_addr+0x00001ff8)&0xb7ffffff)==(0x80a35514&0xb7ffffff))
cnt++;
else
printf("cnt: 835\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00001ff8);
if((readl(ivp_cae_base_addr+0x00001ff8)&0xb7ffffff)==(0x80a35514&0xb7ffffff))
cnt++;
else
printf("cnt: 836\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00001ff8);
if((readl(ivp_cae_base_addr+0x00001ff8)&0xb7ffffff)==(0x80a35514&0xb7ffffff))
cnt++;
else
printf("cnt: 837\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00001ff8);
if((readl(ivp_cae_base_addr+0x00001ff8)&0xb7ffffff)==(0x80a35514&0xb7ffffff))
cnt++;
else
printf("cnt: 838\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00001ffc);
if((readl(ivp_cae_base_addr+0x00001ffc)&0x0fffffff)==(0x027035ca&0x0fffffff))
cnt++;
else
printf("cnt: 839\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00001ffc);
if((readl(ivp_cae_base_addr+0x00001ffc)&0x0fffffff)==(0x027035ca&0x0fffffff))
cnt++;
else
printf("cnt: 840\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00001ffc);
if((readl(ivp_cae_base_addr+0x00001ffc)&0x0fffffff)==(0x027035ca&0x0fffffff))
cnt++;
else
printf("cnt: 841\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00001ffc);
if((readl(ivp_cae_base_addr+0x00001ffc)&0x0fffffff)==(0x027035ca&0x0fffffff))
cnt++;
else
printf("cnt: 842\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00001ffc);
if((readl(ivp_cae_base_addr+0x00001ffc)&0x0fffffff)==(0x027035ca&0x0fffffff))
cnt++;
else
printf("cnt: 843\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00001ffc);
if((readl(ivp_cae_base_addr+0x00001ffc)&0x0fffffff)==(0x027035ca&0x0fffffff))
cnt++;
else
printf("cnt: 844\n");
writel(0x11111111&0xffffffff,ivp_cae_base_addr+0x00002000);
if((readl(ivp_cae_base_addr+0x00002000)&0xffffffff)==(0x11111111&0xffffffff))
cnt++;
else
printf("cnt: 845\n");
writel(0x22222222&0xffffffff,ivp_cae_base_addr+0x00002000);
if((readl(ivp_cae_base_addr+0x00002000)&0xffffffff)==(0x22222222&0xffffffff))
cnt++;
else
printf("cnt: 846\n");
writel(0x44444444&0xffffffff,ivp_cae_base_addr+0x00002000);
if((readl(ivp_cae_base_addr+0x00002000)&0xffffffff)==(0x44444444&0xffffffff))
cnt++;
else
printf("cnt: 847\n");
writel(0x88888888&0xffffffff,ivp_cae_base_addr+0x00002000);
if((readl(ivp_cae_base_addr+0x00002000)&0xffffffff)==(0x88888888&0xffffffff))
cnt++;
else
printf("cnt: 848\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00002000);
if((readl(ivp_cae_base_addr+0x00002000)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 849\n");
writel(0xffffffff&0xffffffff,ivp_cae_base_addr+0x00002000);
if((readl(ivp_cae_base_addr+0x00002000)&0xffffffff)==(0xffffffff&0xffffffff))
cnt++;
else
printf("cnt: 850\n");
writel(0x11111111&0xffffffff,ivp_cae_base_addr+0x00002004);
if((readl(ivp_cae_base_addr+0x00002004)&0xffffffff)==(0x11111111&0xffffffff))
cnt++;
else
printf("cnt: 851\n");
writel(0x22222222&0xffffffff,ivp_cae_base_addr+0x00002004);
if((readl(ivp_cae_base_addr+0x00002004)&0xffffffff)==(0x22222222&0xffffffff))
cnt++;
else
printf("cnt: 852\n");
writel(0x44444444&0xffffffff,ivp_cae_base_addr+0x00002004);
if((readl(ivp_cae_base_addr+0x00002004)&0xffffffff)==(0x44444444&0xffffffff))
cnt++;
else
printf("cnt: 853\n");
writel(0x88888888&0xffffffff,ivp_cae_base_addr+0x00002004);
if((readl(ivp_cae_base_addr+0x00002004)&0xffffffff)==(0x88888888&0xffffffff))
cnt++;
else
printf("cnt: 854\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00002004);
if((readl(ivp_cae_base_addr+0x00002004)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 855\n");
writel(0xffffffff&0xffffffff,ivp_cae_base_addr+0x00002004);
if((readl(ivp_cae_base_addr+0x00002004)&0xffffffff)==(0xffffffff&0xffffffff))
cnt++;
else
printf("cnt: 856\n");
writel(0x11111111&0xffffffff,ivp_cae_base_addr+0x00002008);
if((readl(ivp_cae_base_addr+0x00002008)&0xffffffff)==(0x11111111&0xffffffff))
cnt++;
else
printf("cnt: 857\n");
writel(0x22222222&0xffffffff,ivp_cae_base_addr+0x00002008);
if((readl(ivp_cae_base_addr+0x00002008)&0xffffffff)==(0x22222222&0xffffffff))
cnt++;
else
printf("cnt: 858\n");
writel(0x44444444&0xffffffff,ivp_cae_base_addr+0x00002008);
if((readl(ivp_cae_base_addr+0x00002008)&0xffffffff)==(0x44444444&0xffffffff))
cnt++;
else
printf("cnt: 859\n");
writel(0x88888888&0xffffffff,ivp_cae_base_addr+0x00002008);
if((readl(ivp_cae_base_addr+0x00002008)&0xffffffff)==(0x88888888&0xffffffff))
cnt++;
else
printf("cnt: 860\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00002008);
if((readl(ivp_cae_base_addr+0x00002008)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 861\n");
writel(0xffffffff&0xffffffff,ivp_cae_base_addr+0x00002008);
if((readl(ivp_cae_base_addr+0x00002008)&0xffffffff)==(0xffffffff&0xffffffff))
cnt++;
else
printf("cnt: 862\n");
writel(0x11111111&0xffffffff,ivp_cae_base_addr+0x0000200c);
if((readl(ivp_cae_base_addr+0x0000200c)&0xffffffff)==(0x11111111&0xffffffff))
cnt++;
else
printf("cnt: 863\n");
writel(0x22222222&0xffffffff,ivp_cae_base_addr+0x0000200c);
if((readl(ivp_cae_base_addr+0x0000200c)&0xffffffff)==(0x22222222&0xffffffff))
cnt++;
else
printf("cnt: 864\n");
writel(0x44444444&0xffffffff,ivp_cae_base_addr+0x0000200c);
if((readl(ivp_cae_base_addr+0x0000200c)&0xffffffff)==(0x44444444&0xffffffff))
cnt++;
else
printf("cnt: 865\n");
writel(0x88888888&0xffffffff,ivp_cae_base_addr+0x0000200c);
if((readl(ivp_cae_base_addr+0x0000200c)&0xffffffff)==(0x88888888&0xffffffff))
cnt++;
else
printf("cnt: 866\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000200c);
if((readl(ivp_cae_base_addr+0x0000200c)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 867\n");
writel(0xffffffff&0xffffffff,ivp_cae_base_addr+0x0000200c);
if((readl(ivp_cae_base_addr+0x0000200c)&0xffffffff)==(0xffffffff&0xffffffff))
cnt++;
else
printf("cnt: 868\n");
writel(0x11111111&0xffffffff,ivp_cae_base_addr+0x00002010);
if((readl(ivp_cae_base_addr+0x00002010)&0xffffffff)==(0x11111111&0xffffffff))
cnt++;
else
printf("cnt: 869\n");
writel(0x22222222&0xffffffff,ivp_cae_base_addr+0x00002010);
if((readl(ivp_cae_base_addr+0x00002010)&0xffffffff)==(0x22222222&0xffffffff))
cnt++;
else
printf("cnt: 870\n");
writel(0x44444444&0xffffffff,ivp_cae_base_addr+0x00002010);
if((readl(ivp_cae_base_addr+0x00002010)&0xffffffff)==(0x44444444&0xffffffff))
cnt++;
else
printf("cnt: 871\n");
writel(0x88888888&0xffffffff,ivp_cae_base_addr+0x00002010);
if((readl(ivp_cae_base_addr+0x00002010)&0xffffffff)==(0x88888888&0xffffffff))
cnt++;
else
printf("cnt: 872\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00002010);
if((readl(ivp_cae_base_addr+0x00002010)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 873\n");
writel(0xffffffff&0xffffffff,ivp_cae_base_addr+0x00002010);
if((readl(ivp_cae_base_addr+0x00002010)&0xffffffff)==(0xffffffff&0xffffffff))
cnt++;
else
printf("cnt: 874\n");
writel(0x11111111&0xffffffff,ivp_cae_base_addr+0x00002014);
if((readl(ivp_cae_base_addr+0x00002014)&0xffffffff)==(0x11111111&0xffffffff))
cnt++;
else
printf("cnt: 875\n");
writel(0x22222222&0xffffffff,ivp_cae_base_addr+0x00002014);
if((readl(ivp_cae_base_addr+0x00002014)&0xffffffff)==(0x22222222&0xffffffff))
cnt++;
else
printf("cnt: 876\n");
writel(0x44444444&0xffffffff,ivp_cae_base_addr+0x00002014);
if((readl(ivp_cae_base_addr+0x00002014)&0xffffffff)==(0x44444444&0xffffffff))
cnt++;
else
printf("cnt: 877\n");
writel(0x88888888&0xffffffff,ivp_cae_base_addr+0x00002014);
if((readl(ivp_cae_base_addr+0x00002014)&0xffffffff)==(0x88888888&0xffffffff))
cnt++;
else
printf("cnt: 878\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00002014);
if((readl(ivp_cae_base_addr+0x00002014)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 879\n");
writel(0xffffffff&0xffffffff,ivp_cae_base_addr+0x00002014);
if((readl(ivp_cae_base_addr+0x00002014)&0xffffffff)==(0xffffffff&0xffffffff))
cnt++;
else
printf("cnt: 880\n");
writel(0x00111110&0xffffffff,ivp_cae_base_addr+0x00002018);
if((readl(ivp_cae_base_addr+0x00002018)&0x00fffffc)==(0x00111110&0x00fffffc))
cnt++;
else
printf("cnt: 881\n");
writel(0x00222220&0xffffffff,ivp_cae_base_addr+0x00002018);
if((readl(ivp_cae_base_addr+0x00002018)&0x00fffffc)==(0x00222220&0x00fffffc))
cnt++;
else
printf("cnt: 882\n");
writel(0x00444444&0xffffffff,ivp_cae_base_addr+0x00002018);
if((readl(ivp_cae_base_addr+0x00002018)&0x00fffffc)==(0x00444444&0x00fffffc))
cnt++;
else
printf("cnt: 883\n");
writel(0x00888888&0xffffffff,ivp_cae_base_addr+0x00002018);
if((readl(ivp_cae_base_addr+0x00002018)&0x00fffffc)==(0x00888888&0x00fffffc))
cnt++;
else
printf("cnt: 884\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00002018);
if((readl(ivp_cae_base_addr+0x00002018)&0x00fffffc)==(0x00000000&0x00fffffc))
cnt++;
else
printf("cnt: 885\n");
writel(0x00fffffc&0xffffffff,ivp_cae_base_addr+0x00002018);
if((readl(ivp_cae_base_addr+0x00002018)&0x00fffffc)==(0x00fffffc&0x00fffffc))
cnt++;
else
printf("cnt: 886\n");
writel(0x00110011&0xffffffff,ivp_cae_base_addr+0x0000201c);
if((readl(ivp_cae_base_addr+0x0000201c)&0xe0ff003f)==(0x00110011&0xe0ff003f))
cnt++;
else
printf("cnt: 887\n");
writel(0x20220022&0xffffffff,ivp_cae_base_addr+0x0000201c);
if((readl(ivp_cae_base_addr+0x0000201c)&0xe0ff003f)==(0x20220022&0xe0ff003f))
cnt++;
else
printf("cnt: 888\n");
writel(0x40440004&0xffffffff,ivp_cae_base_addr+0x0000201c);
if((readl(ivp_cae_base_addr+0x0000201c)&0xe0ff003f)==(0x40440004&0xe0ff003f))
cnt++;
else
printf("cnt: 889\n");
writel(0x80880008&0xffffffff,ivp_cae_base_addr+0x0000201c);
if((readl(ivp_cae_base_addr+0x0000201c)&0xe0ff003f)==(0x80880008&0xe0ff003f))
cnt++;
else
printf("cnt: 890\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000201c);
if((readl(ivp_cae_base_addr+0x0000201c)&0xe0ff003f)==(0x00000000&0xe0ff003f))
cnt++;
else
printf("cnt: 891\n");
writel(0xe0ff003f&0xffffffff,ivp_cae_base_addr+0x0000201c);
if((readl(ivp_cae_base_addr+0x0000201c)&0xe0ff003f)==(0xe0ff003f&0xe0ff003f))
cnt++;
else
printf("cnt: 892\n");
writel(0x10110011&0xffffffff,ivp_cae_base_addr+0x00002020);
if((readl(ivp_cae_base_addr+0x00002020)&0xf03f00ff)==(0x10110011&0xf03f00ff))
cnt++;
else
printf("cnt: 893\n");
writel(0x20220022&0xffffffff,ivp_cae_base_addr+0x00002020);
if((readl(ivp_cae_base_addr+0x00002020)&0xf03f00ff)==(0x20220022&0xf03f00ff))
cnt++;
else
printf("cnt: 894\n");
writel(0x40040044&0xffffffff,ivp_cae_base_addr+0x00002020);
if((readl(ivp_cae_base_addr+0x00002020)&0xf03f00ff)==(0x40040044&0xf03f00ff))
cnt++;
else
printf("cnt: 895\n");
writel(0x80080088&0xffffffff,ivp_cae_base_addr+0x00002020);
if((readl(ivp_cae_base_addr+0x00002020)&0xf03f00ff)==(0x80080088&0xf03f00ff))
cnt++;
else
printf("cnt: 896\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00002020);
if((readl(ivp_cae_base_addr+0x00002020)&0xf03f00ff)==(0x00000000&0xf03f00ff))
cnt++;
else
printf("cnt: 897\n");
writel(0xf03f00ff&0xffffffff,ivp_cae_base_addr+0x00002020);
if((readl(ivp_cae_base_addr+0x00002020)&0xf03f00ff)==(0xf03f00ff&0xf03f00ff))
cnt++;
else
printf("cnt: 898\n");
writel(0x11010101&0xffffffff,ivp_cae_base_addr+0x00002024);
if((readl(ivp_cae_base_addr+0x00002024)&0xff010101)==(0x11010101&0xff010101))
cnt++;
else
printf("cnt: 899\n");
writel(0x22000000&0xffffffff,ivp_cae_base_addr+0x00002024);
if((readl(ivp_cae_base_addr+0x00002024)&0xff010101)==(0x22000000&0xff010101))
cnt++;
else
printf("cnt: 900\n");
writel(0x44000000&0xffffffff,ivp_cae_base_addr+0x00002024);
if((readl(ivp_cae_base_addr+0x00002024)&0xff010101)==(0x44000000&0xff010101))
cnt++;
else
printf("cnt: 901\n");
writel(0x88000000&0xffffffff,ivp_cae_base_addr+0x00002024);
if((readl(ivp_cae_base_addr+0x00002024)&0xff010101)==(0x88000000&0xff010101))
cnt++;
else
printf("cnt: 902\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00002024);
if((readl(ivp_cae_base_addr+0x00002024)&0xff010101)==(0x00000000&0xff010101))
cnt++;
else
printf("cnt: 903\n");
writel(0xff010101&0xffffffff,ivp_cae_base_addr+0x00002024);
if((readl(ivp_cae_base_addr+0x00002024)&0xff010101)==(0xff010101&0xff010101))
cnt++;
else
printf("cnt: 904\n");
writel(0x11000000&0xffffffff,ivp_cae_base_addr+0x00002028);
if((readl(ivp_cae_base_addr+0x00002028)&0xffc00000)==(0x11000000&0xffc00000))
cnt++;
else
printf("cnt: 905\n");
writel(0x22000000&0xffffffff,ivp_cae_base_addr+0x00002028);
if((readl(ivp_cae_base_addr+0x00002028)&0xffc00000)==(0x22000000&0xffc00000))
cnt++;
else
printf("cnt: 906\n");
writel(0x44400000&0xffffffff,ivp_cae_base_addr+0x00002028);
if((readl(ivp_cae_base_addr+0x00002028)&0xffc00000)==(0x44400000&0xffc00000))
cnt++;
else
printf("cnt: 907\n");
writel(0x88800000&0xffffffff,ivp_cae_base_addr+0x00002028);
if((readl(ivp_cae_base_addr+0x00002028)&0xffc00000)==(0x88800000&0xffc00000))
cnt++;
else
printf("cnt: 908\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00002028);
if((readl(ivp_cae_base_addr+0x00002028)&0xffc00000)==(0x00000000&0xffc00000))
cnt++;
else
printf("cnt: 909\n");
writel(0xffc00000&0xffffffff,ivp_cae_base_addr+0x00002028);
if((readl(ivp_cae_base_addr+0x00002028)&0xffc00000)==(0xffc00000&0xffc00000))
cnt++;
else
printf("cnt: 910\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000202c);
if((readl(ivp_cae_base_addr+0x0000202c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 911\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000202c);
if((readl(ivp_cae_base_addr+0x0000202c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 912\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000202c);
if((readl(ivp_cae_base_addr+0x0000202c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 913\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000202c);
if((readl(ivp_cae_base_addr+0x0000202c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 914\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000202c);
if((readl(ivp_cae_base_addr+0x0000202c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 915\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000202c);
if((readl(ivp_cae_base_addr+0x0000202c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 916\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00002030);
if((readl(ivp_cae_base_addr+0x00002030)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 917\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00002030);
if((readl(ivp_cae_base_addr+0x00002030)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 918\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00002030);
if((readl(ivp_cae_base_addr+0x00002030)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 919\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00002030);
if((readl(ivp_cae_base_addr+0x00002030)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 920\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00002030);
if((readl(ivp_cae_base_addr+0x00002030)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 921\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00002030);
if((readl(ivp_cae_base_addr+0x00002030)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 922\n");
writel(0x00111110&0xffffffff,ivp_cae_base_addr+0x00002034);
if((readl(ivp_cae_base_addr+0x00002034)&0x00fffffc)==(0x00111110&0x00fffffc))
cnt++;
else
printf("cnt: 923\n");
writel(0x00222220&0xffffffff,ivp_cae_base_addr+0x00002034);
if((readl(ivp_cae_base_addr+0x00002034)&0x00fffffc)==(0x00222220&0x00fffffc))
cnt++;
else
printf("cnt: 924\n");
writel(0x00444444&0xffffffff,ivp_cae_base_addr+0x00002034);
if((readl(ivp_cae_base_addr+0x00002034)&0x00fffffc)==(0x00444444&0x00fffffc))
cnt++;
else
printf("cnt: 925\n");
writel(0x00888888&0xffffffff,ivp_cae_base_addr+0x00002034);
if((readl(ivp_cae_base_addr+0x00002034)&0x00fffffc)==(0x00888888&0x00fffffc))
cnt++;
else
printf("cnt: 926\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00002034);
if((readl(ivp_cae_base_addr+0x00002034)&0x00fffffc)==(0x00000000&0x00fffffc))
cnt++;
else
printf("cnt: 927\n");
writel(0x00fffffc&0xffffffff,ivp_cae_base_addr+0x00002034);
if((readl(ivp_cae_base_addr+0x00002034)&0x00fffffc)==(0x00fffffc&0x00fffffc))
cnt++;
else
printf("cnt: 928\n");
writel(0x00111110&0xffffffff,ivp_cae_base_addr+0x00002038);
if((readl(ivp_cae_base_addr+0x00002038)&0x00fffffc)==(0x00111110&0x00fffffc))
cnt++;
else
printf("cnt: 929\n");
writel(0x00222220&0xffffffff,ivp_cae_base_addr+0x00002038);
if((readl(ivp_cae_base_addr+0x00002038)&0x00fffffc)==(0x00222220&0x00fffffc))
cnt++;
else
printf("cnt: 930\n");
writel(0x00444444&0xffffffff,ivp_cae_base_addr+0x00002038);
if((readl(ivp_cae_base_addr+0x00002038)&0x00fffffc)==(0x00444444&0x00fffffc))
cnt++;
else
printf("cnt: 931\n");
writel(0x00888888&0xffffffff,ivp_cae_base_addr+0x00002038);
if((readl(ivp_cae_base_addr+0x00002038)&0x00fffffc)==(0x00888888&0x00fffffc))
cnt++;
else
printf("cnt: 932\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00002038);
if((readl(ivp_cae_base_addr+0x00002038)&0x00fffffc)==(0x00000000&0x00fffffc))
cnt++;
else
printf("cnt: 933\n");
writel(0x00fffffc&0xffffffff,ivp_cae_base_addr+0x00002038);
if((readl(ivp_cae_base_addr+0x00002038)&0x00fffffc)==(0x00fffffc&0x00fffffc))
cnt++;
else
printf("cnt: 934\n");
writel(0x00000011&0xffffffff,ivp_cae_base_addr+0x0000203c);
if((readl(ivp_cae_base_addr+0x0000203c)&0x00000000)==(0x00000011&0x00000000))
cnt++;
else
printf("cnt: 935\n");
writel(0x00000022&0xffffffff,ivp_cae_base_addr+0x0000203c);
if((readl(ivp_cae_base_addr+0x0000203c)&0x00000000)==(0x00000022&0x00000000))
cnt++;
else
printf("cnt: 936\n");
writel(0x00000004&0xffffffff,ivp_cae_base_addr+0x0000203c);
if((readl(ivp_cae_base_addr+0x0000203c)&0x00000000)==(0x00000004&0x00000000))
cnt++;
else
printf("cnt: 937\n");
writel(0x00000008&0xffffffff,ivp_cae_base_addr+0x0000203c);
if((readl(ivp_cae_base_addr+0x0000203c)&0x00000000)==(0x00000008&0x00000000))
cnt++;
else
printf("cnt: 938\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000203c);
if((readl(ivp_cae_base_addr+0x0000203c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 939\n");
writel(0x0000003f&0xffffffff,ivp_cae_base_addr+0x0000203c);
if((readl(ivp_cae_base_addr+0x0000203c)&0x00000000)==(0x0000003f&0x00000000))
cnt++;
else
printf("cnt: 940\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000027f8);
if((readl(ivp_cae_base_addr+0x000027f8)&0xb7ffffff)==(0x80a35514&0xb7ffffff))
cnt++;
else
printf("cnt: 941\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000027f8);
if((readl(ivp_cae_base_addr+0x000027f8)&0xb7ffffff)==(0x80a35514&0xb7ffffff))
cnt++;
else
printf("cnt: 942\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000027f8);
if((readl(ivp_cae_base_addr+0x000027f8)&0xb7ffffff)==(0x80a35514&0xb7ffffff))
cnt++;
else
printf("cnt: 943\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000027f8);
if((readl(ivp_cae_base_addr+0x000027f8)&0xb7ffffff)==(0x80a35514&0xb7ffffff))
cnt++;
else
printf("cnt: 944\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000027f8);
if((readl(ivp_cae_base_addr+0x000027f8)&0xb7ffffff)==(0x80a35514&0xb7ffffff))
cnt++;
else
printf("cnt: 945\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000027f8);
if((readl(ivp_cae_base_addr+0x000027f8)&0xb7ffffff)==(0x80a35514&0xb7ffffff))
cnt++;
else
printf("cnt: 946\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000027fc);
if((readl(ivp_cae_base_addr+0x000027fc)&0x0fffffff)==(0x027035ca&0x0fffffff))
cnt++;
else
printf("cnt: 947\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000027fc);
if((readl(ivp_cae_base_addr+0x000027fc)&0x0fffffff)==(0x027035ca&0x0fffffff))
cnt++;
else
printf("cnt: 948\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000027fc);
if((readl(ivp_cae_base_addr+0x000027fc)&0x0fffffff)==(0x027035ca&0x0fffffff))
cnt++;
else
printf("cnt: 949\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000027fc);
if((readl(ivp_cae_base_addr+0x000027fc)&0x0fffffff)==(0x027035ca&0x0fffffff))
cnt++;
else
printf("cnt: 950\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000027fc);
if((readl(ivp_cae_base_addr+0x000027fc)&0x0fffffff)==(0x027035ca&0x0fffffff))
cnt++;
else
printf("cnt: 951\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000027fc);
if((readl(ivp_cae_base_addr+0x000027fc)&0x0fffffff)==(0x027035ca&0x0fffffff))
cnt++;
else
printf("cnt: 952\n");
writel(0x11111111&0xffffffff,ivp_cae_base_addr+0x00002800);
if((readl(ivp_cae_base_addr+0x00002800)&0xffffffff)==(0x11111111&0xffffffff))
cnt++;
else
printf("cnt: 953\n");
writel(0x22222222&0xffffffff,ivp_cae_base_addr+0x00002800);
if((readl(ivp_cae_base_addr+0x00002800)&0xffffffff)==(0x22222222&0xffffffff))
cnt++;
else
printf("cnt: 954\n");
writel(0x44444444&0xffffffff,ivp_cae_base_addr+0x00002800);
if((readl(ivp_cae_base_addr+0x00002800)&0xffffffff)==(0x44444444&0xffffffff))
cnt++;
else
printf("cnt: 955\n");
writel(0x88888888&0xffffffff,ivp_cae_base_addr+0x00002800);
if((readl(ivp_cae_base_addr+0x00002800)&0xffffffff)==(0x88888888&0xffffffff))
cnt++;
else
printf("cnt: 956\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00002800);
if((readl(ivp_cae_base_addr+0x00002800)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 957\n");
writel(0xffffffff&0xffffffff,ivp_cae_base_addr+0x00002800);
if((readl(ivp_cae_base_addr+0x00002800)&0xffffffff)==(0xffffffff&0xffffffff))
cnt++;
else
printf("cnt: 958\n");
writel(0x11111111&0xffffffff,ivp_cae_base_addr+0x00002804);
if((readl(ivp_cae_base_addr+0x00002804)&0xffffffff)==(0x11111111&0xffffffff))
cnt++;
else
printf("cnt: 959\n");
writel(0x22222222&0xffffffff,ivp_cae_base_addr+0x00002804);
if((readl(ivp_cae_base_addr+0x00002804)&0xffffffff)==(0x22222222&0xffffffff))
cnt++;
else
printf("cnt: 960\n");
writel(0x44444444&0xffffffff,ivp_cae_base_addr+0x00002804);
if((readl(ivp_cae_base_addr+0x00002804)&0xffffffff)==(0x44444444&0xffffffff))
cnt++;
else
printf("cnt: 961\n");
writel(0x88888888&0xffffffff,ivp_cae_base_addr+0x00002804);
if((readl(ivp_cae_base_addr+0x00002804)&0xffffffff)==(0x88888888&0xffffffff))
cnt++;
else
printf("cnt: 962\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00002804);
if((readl(ivp_cae_base_addr+0x00002804)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 963\n");
writel(0xffffffff&0xffffffff,ivp_cae_base_addr+0x00002804);
if((readl(ivp_cae_base_addr+0x00002804)&0xffffffff)==(0xffffffff&0xffffffff))
cnt++;
else
printf("cnt: 964\n");
writel(0x11111111&0xffffffff,ivp_cae_base_addr+0x00002808);
if((readl(ivp_cae_base_addr+0x00002808)&0xffffffff)==(0x11111111&0xffffffff))
cnt++;
else
printf("cnt: 965\n");
writel(0x22222222&0xffffffff,ivp_cae_base_addr+0x00002808);
if((readl(ivp_cae_base_addr+0x00002808)&0xffffffff)==(0x22222222&0xffffffff))
cnt++;
else
printf("cnt: 966\n");
writel(0x44444444&0xffffffff,ivp_cae_base_addr+0x00002808);
if((readl(ivp_cae_base_addr+0x00002808)&0xffffffff)==(0x44444444&0xffffffff))
cnt++;
else
printf("cnt: 967\n");
writel(0x88888888&0xffffffff,ivp_cae_base_addr+0x00002808);
if((readl(ivp_cae_base_addr+0x00002808)&0xffffffff)==(0x88888888&0xffffffff))
cnt++;
else
printf("cnt: 968\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00002808);
if((readl(ivp_cae_base_addr+0x00002808)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 969\n");
writel(0xffffffff&0xffffffff,ivp_cae_base_addr+0x00002808);
if((readl(ivp_cae_base_addr+0x00002808)&0xffffffff)==(0xffffffff&0xffffffff))
cnt++;
else
printf("cnt: 970\n");
writel(0x11111111&0xffffffff,ivp_cae_base_addr+0x0000280c);
if((readl(ivp_cae_base_addr+0x0000280c)&0xffffffff)==(0x11111111&0xffffffff))
cnt++;
else
printf("cnt: 971\n");
writel(0x22222222&0xffffffff,ivp_cae_base_addr+0x0000280c);
if((readl(ivp_cae_base_addr+0x0000280c)&0xffffffff)==(0x22222222&0xffffffff))
cnt++;
else
printf("cnt: 972\n");
writel(0x44444444&0xffffffff,ivp_cae_base_addr+0x0000280c);
if((readl(ivp_cae_base_addr+0x0000280c)&0xffffffff)==(0x44444444&0xffffffff))
cnt++;
else
printf("cnt: 973\n");
writel(0x88888888&0xffffffff,ivp_cae_base_addr+0x0000280c);
if((readl(ivp_cae_base_addr+0x0000280c)&0xffffffff)==(0x88888888&0xffffffff))
cnt++;
else
printf("cnt: 974\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000280c);
if((readl(ivp_cae_base_addr+0x0000280c)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 975\n");
writel(0xffffffff&0xffffffff,ivp_cae_base_addr+0x0000280c);
if((readl(ivp_cae_base_addr+0x0000280c)&0xffffffff)==(0xffffffff&0xffffffff))
cnt++;
else
printf("cnt: 976\n");
writel(0x00111110&0xffffffff,ivp_cae_base_addr+0x00002818);
if((readl(ivp_cae_base_addr+0x00002818)&0x00fffffc)==(0x00111110&0x00fffffc))
cnt++;
else
printf("cnt: 977\n");
writel(0x00222220&0xffffffff,ivp_cae_base_addr+0x00002818);
if((readl(ivp_cae_base_addr+0x00002818)&0x00fffffc)==(0x00222220&0x00fffffc))
cnt++;
else
printf("cnt: 978\n");
writel(0x00444444&0xffffffff,ivp_cae_base_addr+0x00002818);
if((readl(ivp_cae_base_addr+0x00002818)&0x00fffffc)==(0x00444444&0x00fffffc))
cnt++;
else
printf("cnt: 979\n");
writel(0x00888888&0xffffffff,ivp_cae_base_addr+0x00002818);
if((readl(ivp_cae_base_addr+0x00002818)&0x00fffffc)==(0x00888888&0x00fffffc))
cnt++;
else
printf("cnt: 980\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00002818);
if((readl(ivp_cae_base_addr+0x00002818)&0x00fffffc)==(0x00000000&0x00fffffc))
cnt++;
else
printf("cnt: 981\n");
writel(0x00fffffc&0xffffffff,ivp_cae_base_addr+0x00002818);
if((readl(ivp_cae_base_addr+0x00002818)&0x00fffffc)==(0x00fffffc&0x00fffffc))
cnt++;
else
printf("cnt: 982\n");
writel(0x00110011&0xffffffff,ivp_cae_base_addr+0x0000281c);
if((readl(ivp_cae_base_addr+0x0000281c)&0xe0ff00ff)==(0x00110011&0xe0ff00ff))
cnt++;
else
printf("cnt: 983\n");
writel(0x20220022&0xffffffff,ivp_cae_base_addr+0x0000281c);
if((readl(ivp_cae_base_addr+0x0000281c)&0xe0ff00ff)==(0x20220022&0xe0ff00ff))
cnt++;
else
printf("cnt: 984\n");
writel(0x40440044&0xffffffff,ivp_cae_base_addr+0x0000281c);
if((readl(ivp_cae_base_addr+0x0000281c)&0xe0ff00ff)==(0x40440044&0xe0ff00ff))
cnt++;
else
printf("cnt: 985\n");
writel(0x80880088&0xffffffff,ivp_cae_base_addr+0x0000281c);
if((readl(ivp_cae_base_addr+0x0000281c)&0xe0ff00ff)==(0x80880088&0xe0ff00ff))
cnt++;
else
printf("cnt: 986\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000281c);
if((readl(ivp_cae_base_addr+0x0000281c)&0xe0ff00ff)==(0x00000000&0xe0ff00ff))
cnt++;
else
printf("cnt: 987\n");
writel(0xe0ff00ff&0xffffffff,ivp_cae_base_addr+0x0000281c);
if((readl(ivp_cae_base_addr+0x0000281c)&0xe0ff00ff)==(0xe0ff00ff&0xe0ff00ff))
cnt++;
else
printf("cnt: 988\n");
writel(0x10110011&0xffffffff,ivp_cae_base_addr+0x00002820);
if((readl(ivp_cae_base_addr+0x00002820)&0xf03f00ff)==(0x10110011&0xf03f00ff))
cnt++;
else
printf("cnt: 989\n");
writel(0x20220022&0xffffffff,ivp_cae_base_addr+0x00002820);
if((readl(ivp_cae_base_addr+0x00002820)&0xf03f00ff)==(0x20220022&0xf03f00ff))
cnt++;
else
printf("cnt: 990\n");
writel(0x40040044&0xffffffff,ivp_cae_base_addr+0x00002820);
if((readl(ivp_cae_base_addr+0x00002820)&0xf03f00ff)==(0x40040044&0xf03f00ff))
cnt++;
else
printf("cnt: 991\n");
writel(0x80080088&0xffffffff,ivp_cae_base_addr+0x00002820);
if((readl(ivp_cae_base_addr+0x00002820)&0xf03f00ff)==(0x80080088&0xf03f00ff))
cnt++;
else
printf("cnt: 992\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00002820);
if((readl(ivp_cae_base_addr+0x00002820)&0xf03f00ff)==(0x00000000&0xf03f00ff))
cnt++;
else
printf("cnt: 993\n");
writel(0xf03f00ff&0xffffffff,ivp_cae_base_addr+0x00002820);
if((readl(ivp_cae_base_addr+0x00002820)&0xf03f00ff)==(0xf03f00ff&0xf03f00ff))
cnt++;
else
printf("cnt: 994\n");
writel(0x11100101&0xffffffff,ivp_cae_base_addr+0x00002824);
if((readl(ivp_cae_base_addr+0x00002824)&0xfff80101)==(0x11100101&0xfff80101))
cnt++;
else
printf("cnt: 995\n");
writel(0x22200000&0xffffffff,ivp_cae_base_addr+0x00002824);
if((readl(ivp_cae_base_addr+0x00002824)&0xfff80101)==(0x22200000&0xfff80101))
cnt++;
else
printf("cnt: 996\n");
writel(0x44400000&0xffffffff,ivp_cae_base_addr+0x00002824);
if((readl(ivp_cae_base_addr+0x00002824)&0xfff80101)==(0x44400000&0xfff80101))
cnt++;
else
printf("cnt: 997\n");
writel(0x88880000&0xffffffff,ivp_cae_base_addr+0x00002824);
if((readl(ivp_cae_base_addr+0x00002824)&0xfff80101)==(0x88880000&0xfff80101))
cnt++;
else
printf("cnt: 998\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00002824);
if((readl(ivp_cae_base_addr+0x00002824)&0xfff80101)==(0x00000000&0xfff80101))
cnt++;
else
printf("cnt: 999\n");
writel(0xfff80101&0xffffffff,ivp_cae_base_addr+0x00002824);
if((readl(ivp_cae_base_addr+0x00002824)&0xfff80101)==(0xfff80101&0xfff80101))
cnt++;
else
printf("cnt: 1000\n");
writel(0x11000000&0xffffffff,ivp_cae_base_addr+0x00002828);
if((readl(ivp_cae_base_addr+0x00002828)&0xff800000)==(0x11000000&0xff800000))
cnt++;
else
printf("cnt: 1001\n");
writel(0x22000000&0xffffffff,ivp_cae_base_addr+0x00002828);
if((readl(ivp_cae_base_addr+0x00002828)&0xff800000)==(0x22000000&0xff800000))
cnt++;
else
printf("cnt: 1002\n");
writel(0x44000000&0xffffffff,ivp_cae_base_addr+0x00002828);
if((readl(ivp_cae_base_addr+0x00002828)&0xff800000)==(0x44000000&0xff800000))
cnt++;
else
printf("cnt: 1003\n");
writel(0x88800000&0xffffffff,ivp_cae_base_addr+0x00002828);
if((readl(ivp_cae_base_addr+0x00002828)&0xff800000)==(0x88800000&0xff800000))
cnt++;
else
printf("cnt: 1004\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00002828);
if((readl(ivp_cae_base_addr+0x00002828)&0xff800000)==(0x00000000&0xff800000))
cnt++;
else
printf("cnt: 1005\n");
writel(0xff800000&0xffffffff,ivp_cae_base_addr+0x00002828);
if((readl(ivp_cae_base_addr+0x00002828)&0xff800000)==(0xff800000&0xff800000))
cnt++;
else
printf("cnt: 1006\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000282c);
if((readl(ivp_cae_base_addr+0x0000282c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1007\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000282c);
if((readl(ivp_cae_base_addr+0x0000282c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1008\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000282c);
if((readl(ivp_cae_base_addr+0x0000282c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1009\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000282c);
if((readl(ivp_cae_base_addr+0x0000282c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1010\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000282c);
if((readl(ivp_cae_base_addr+0x0000282c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1011\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000282c);
if((readl(ivp_cae_base_addr+0x0000282c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1012\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00002830);
if((readl(ivp_cae_base_addr+0x00002830)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1013\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00002830);
if((readl(ivp_cae_base_addr+0x00002830)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1014\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00002830);
if((readl(ivp_cae_base_addr+0x00002830)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1015\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00002830);
if((readl(ivp_cae_base_addr+0x00002830)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1016\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00002830);
if((readl(ivp_cae_base_addr+0x00002830)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1017\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00002830);
if((readl(ivp_cae_base_addr+0x00002830)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1018\n");
writel(0x00111110&0xffffffff,ivp_cae_base_addr+0x00002834);
if((readl(ivp_cae_base_addr+0x00002834)&0x00fffffc)==(0x00111110&0x00fffffc))
cnt++;
else
printf("cnt: 1019\n");
writel(0x00222220&0xffffffff,ivp_cae_base_addr+0x00002834);
if((readl(ivp_cae_base_addr+0x00002834)&0x00fffffc)==(0x00222220&0x00fffffc))
cnt++;
else
printf("cnt: 1020\n");
writel(0x00444444&0xffffffff,ivp_cae_base_addr+0x00002834);
if((readl(ivp_cae_base_addr+0x00002834)&0x00fffffc)==(0x00444444&0x00fffffc))
cnt++;
else
printf("cnt: 1021\n");
writel(0x00888888&0xffffffff,ivp_cae_base_addr+0x00002834);
if((readl(ivp_cae_base_addr+0x00002834)&0x00fffffc)==(0x00888888&0x00fffffc))
cnt++;
else
printf("cnt: 1022\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00002834);
if((readl(ivp_cae_base_addr+0x00002834)&0x00fffffc)==(0x00000000&0x00fffffc))
cnt++;
else
printf("cnt: 1023\n");
writel(0x00fffffc&0xffffffff,ivp_cae_base_addr+0x00002834);
if((readl(ivp_cae_base_addr+0x00002834)&0x00fffffc)==(0x00fffffc&0x00fffffc))
cnt++;
else
printf("cnt: 1024\n");
writel(0x00111110&0xffffffff,ivp_cae_base_addr+0x00002838);
if((readl(ivp_cae_base_addr+0x00002838)&0x00fffffc)==(0x00111110&0x00fffffc))
cnt++;
else
printf("cnt: 1025\n");
writel(0x00222220&0xffffffff,ivp_cae_base_addr+0x00002838);
if((readl(ivp_cae_base_addr+0x00002838)&0x00fffffc)==(0x00222220&0x00fffffc))
cnt++;
else
printf("cnt: 1026\n");
writel(0x00444444&0xffffffff,ivp_cae_base_addr+0x00002838);
if((readl(ivp_cae_base_addr+0x00002838)&0x00fffffc)==(0x00444444&0x00fffffc))
cnt++;
else
printf("cnt: 1027\n");
writel(0x00888888&0xffffffff,ivp_cae_base_addr+0x00002838);
if((readl(ivp_cae_base_addr+0x00002838)&0x00fffffc)==(0x00888888&0x00fffffc))
cnt++;
else
printf("cnt: 1028\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00002838);
if((readl(ivp_cae_base_addr+0x00002838)&0x00fffffc)==(0x00000000&0x00fffffc))
cnt++;
else
printf("cnt: 1029\n");
writel(0x00fffffc&0xffffffff,ivp_cae_base_addr+0x00002838);
if((readl(ivp_cae_base_addr+0x00002838)&0x00fffffc)==(0x00fffffc&0x00fffffc))
cnt++;
else
printf("cnt: 1030\n");
writel(0x00000011&0xffffffff,ivp_cae_base_addr+0x0000283c);
if((readl(ivp_cae_base_addr+0x0000283c)&0x00000000)==(0x00000011&0x00000000))
cnt++;
else
printf("cnt: 1031\n");
writel(0x00000022&0xffffffff,ivp_cae_base_addr+0x0000283c);
if((readl(ivp_cae_base_addr+0x0000283c)&0x00000000)==(0x00000022&0x00000000))
cnt++;
else
printf("cnt: 1032\n");
writel(0x00000044&0xffffffff,ivp_cae_base_addr+0x0000283c);
if((readl(ivp_cae_base_addr+0x0000283c)&0x00000000)==(0x00000044&0x00000000))
cnt++;
else
printf("cnt: 1033\n");
writel(0x00000088&0xffffffff,ivp_cae_base_addr+0x0000283c);
if((readl(ivp_cae_base_addr+0x0000283c)&0x00000000)==(0x00000088&0x00000000))
cnt++;
else
printf("cnt: 1034\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000283c);
if((readl(ivp_cae_base_addr+0x0000283c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1035\n");
writel(0x000000ff&0xffffffff,ivp_cae_base_addr+0x0000283c);
if((readl(ivp_cae_base_addr+0x0000283c)&0x00000000)==(0x000000ff&0x00000000))
cnt++;
else
printf("cnt: 1036\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00002ff8);
if((readl(ivp_cae_base_addr+0x00002ff8)&0xb7ffffff)==(0x80a35514&0xb7ffffff))
cnt++;
else
printf("cnt: 1037\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00002ff8);
if((readl(ivp_cae_base_addr+0x00002ff8)&0xb7ffffff)==(0x80a35514&0xb7ffffff))
cnt++;
else
printf("cnt: 1038\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00002ff8);
if((readl(ivp_cae_base_addr+0x00002ff8)&0xb7ffffff)==(0x80a35514&0xb7ffffff))
cnt++;
else
printf("cnt: 1039\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00002ff8);
if((readl(ivp_cae_base_addr+0x00002ff8)&0xb7ffffff)==(0x80a35514&0xb7ffffff))
cnt++;
else
printf("cnt: 1040\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00002ff8);
if((readl(ivp_cae_base_addr+0x00002ff8)&0xb7ffffff)==(0x80a35514&0xb7ffffff))
cnt++;
else
printf("cnt: 1041\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00002ff8);
if((readl(ivp_cae_base_addr+0x00002ff8)&0xb7ffffff)==(0x80a35514&0xb7ffffff))
cnt++;
else
printf("cnt: 1042\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00002ffc);
if((readl(ivp_cae_base_addr+0x00002ffc)&0x0fffffff)==(0x027035ca&0x0fffffff))
cnt++;
else
printf("cnt: 1043\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00002ffc);
if((readl(ivp_cae_base_addr+0x00002ffc)&0x0fffffff)==(0x027035ca&0x0fffffff))
cnt++;
else
printf("cnt: 1044\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00002ffc);
if((readl(ivp_cae_base_addr+0x00002ffc)&0x0fffffff)==(0x027035ca&0x0fffffff))
cnt++;
else
printf("cnt: 1045\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00002ffc);
if((readl(ivp_cae_base_addr+0x00002ffc)&0x0fffffff)==(0x027035ca&0x0fffffff))
cnt++;
else
printf("cnt: 1046\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00002ffc);
if((readl(ivp_cae_base_addr+0x00002ffc)&0x0fffffff)==(0x027035ca&0x0fffffff))
cnt++;
else
printf("cnt: 1047\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00002ffc);
if((readl(ivp_cae_base_addr+0x00002ffc)&0x0fffffff)==(0x027035ca&0x0fffffff))
cnt++;
else
printf("cnt: 1048\n");
writel(0x11111111&0xffffffff,ivp_cae_base_addr+0x00003000);
if((readl(ivp_cae_base_addr+0x00003000)&0xffffffff)==(0x11111111&0xffffffff))
cnt++;
else
printf("cnt: 1049\n");
writel(0x22222222&0xffffffff,ivp_cae_base_addr+0x00003000);
if((readl(ivp_cae_base_addr+0x00003000)&0xffffffff)==(0x22222222&0xffffffff))
cnt++;
else
printf("cnt: 1050\n");
writel(0x44444444&0xffffffff,ivp_cae_base_addr+0x00003000);
if((readl(ivp_cae_base_addr+0x00003000)&0xffffffff)==(0x44444444&0xffffffff))
cnt++;
else
printf("cnt: 1051\n");
writel(0x88888888&0xffffffff,ivp_cae_base_addr+0x00003000);
if((readl(ivp_cae_base_addr+0x00003000)&0xffffffff)==(0x88888888&0xffffffff))
cnt++;
else
printf("cnt: 1052\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00003000);
if((readl(ivp_cae_base_addr+0x00003000)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 1053\n");
writel(0xffffffff&0xffffffff,ivp_cae_base_addr+0x00003000);
if((readl(ivp_cae_base_addr+0x00003000)&0xffffffff)==(0xffffffff&0xffffffff))
cnt++;
else
printf("cnt: 1054\n");
writel(0x11111111&0xffffffff,ivp_cae_base_addr+0x00003004);
if((readl(ivp_cae_base_addr+0x00003004)&0xffffffff)==(0x11111111&0xffffffff))
cnt++;
else
printf("cnt: 1055\n");
writel(0x22222222&0xffffffff,ivp_cae_base_addr+0x00003004);
if((readl(ivp_cae_base_addr+0x00003004)&0xffffffff)==(0x22222222&0xffffffff))
cnt++;
else
printf("cnt: 1056\n");
writel(0x44444444&0xffffffff,ivp_cae_base_addr+0x00003004);
if((readl(ivp_cae_base_addr+0x00003004)&0xffffffff)==(0x44444444&0xffffffff))
cnt++;
else
printf("cnt: 1057\n");
writel(0x88888888&0xffffffff,ivp_cae_base_addr+0x00003004);
if((readl(ivp_cae_base_addr+0x00003004)&0xffffffff)==(0x88888888&0xffffffff))
cnt++;
else
printf("cnt: 1058\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00003004);
if((readl(ivp_cae_base_addr+0x00003004)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 1059\n");
writel(0xffffffff&0xffffffff,ivp_cae_base_addr+0x00003004);
if((readl(ivp_cae_base_addr+0x00003004)&0xffffffff)==(0xffffffff&0xffffffff))
cnt++;
else
printf("cnt: 1060\n");
writel(0x11111111&0xffffffff,ivp_cae_base_addr+0x00003008);
if((readl(ivp_cae_base_addr+0x00003008)&0xffffffff)==(0x11111111&0xffffffff))
cnt++;
else
printf("cnt: 1061\n");
writel(0x22222222&0xffffffff,ivp_cae_base_addr+0x00003008);
if((readl(ivp_cae_base_addr+0x00003008)&0xffffffff)==(0x22222222&0xffffffff))
cnt++;
else
printf("cnt: 1062\n");
writel(0x44444444&0xffffffff,ivp_cae_base_addr+0x00003008);
if((readl(ivp_cae_base_addr+0x00003008)&0xffffffff)==(0x44444444&0xffffffff))
cnt++;
else
printf("cnt: 1063\n");
writel(0x88888888&0xffffffff,ivp_cae_base_addr+0x00003008);
if((readl(ivp_cae_base_addr+0x00003008)&0xffffffff)==(0x88888888&0xffffffff))
cnt++;
else
printf("cnt: 1064\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00003008);
if((readl(ivp_cae_base_addr+0x00003008)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 1065\n");
writel(0xffffffff&0xffffffff,ivp_cae_base_addr+0x00003008);
if((readl(ivp_cae_base_addr+0x00003008)&0xffffffff)==(0xffffffff&0xffffffff))
cnt++;
else
printf("cnt: 1066\n");
writel(0x11111111&0xffffffff,ivp_cae_base_addr+0x0000300c);
if((readl(ivp_cae_base_addr+0x0000300c)&0xffffffff)==(0x11111111&0xffffffff))
cnt++;
else
printf("cnt: 1067\n");
writel(0x22222222&0xffffffff,ivp_cae_base_addr+0x0000300c);
if((readl(ivp_cae_base_addr+0x0000300c)&0xffffffff)==(0x22222222&0xffffffff))
cnt++;
else
printf("cnt: 1068\n");
writel(0x44444444&0xffffffff,ivp_cae_base_addr+0x0000300c);
if((readl(ivp_cae_base_addr+0x0000300c)&0xffffffff)==(0x44444444&0xffffffff))
cnt++;
else
printf("cnt: 1069\n");
writel(0x88888888&0xffffffff,ivp_cae_base_addr+0x0000300c);
if((readl(ivp_cae_base_addr+0x0000300c)&0xffffffff)==(0x88888888&0xffffffff))
cnt++;
else
printf("cnt: 1070\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000300c);
if((readl(ivp_cae_base_addr+0x0000300c)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 1071\n");
writel(0xffffffff&0xffffffff,ivp_cae_base_addr+0x0000300c);
if((readl(ivp_cae_base_addr+0x0000300c)&0xffffffff)==(0xffffffff&0xffffffff))
cnt++;
else
printf("cnt: 1072\n");
writel(0x11111111&0xffffffff,ivp_cae_base_addr+0x00003010);
if((readl(ivp_cae_base_addr+0x00003010)&0xffffffff)==(0x11111111&0xffffffff))
cnt++;
else
printf("cnt: 1073\n");
writel(0x22222222&0xffffffff,ivp_cae_base_addr+0x00003010);
if((readl(ivp_cae_base_addr+0x00003010)&0xffffffff)==(0x22222222&0xffffffff))
cnt++;
else
printf("cnt: 1074\n");
writel(0x44444444&0xffffffff,ivp_cae_base_addr+0x00003010);
if((readl(ivp_cae_base_addr+0x00003010)&0xffffffff)==(0x44444444&0xffffffff))
cnt++;
else
printf("cnt: 1075\n");
writel(0x88888888&0xffffffff,ivp_cae_base_addr+0x00003010);
if((readl(ivp_cae_base_addr+0x00003010)&0xffffffff)==(0x88888888&0xffffffff))
cnt++;
else
printf("cnt: 1076\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00003010);
if((readl(ivp_cae_base_addr+0x00003010)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 1077\n");
writel(0xffffffff&0xffffffff,ivp_cae_base_addr+0x00003010);
if((readl(ivp_cae_base_addr+0x00003010)&0xffffffff)==(0xffffffff&0xffffffff))
cnt++;
else
printf("cnt: 1078\n");
writel(0x11111111&0xffffffff,ivp_cae_base_addr+0x00003014);
if((readl(ivp_cae_base_addr+0x00003014)&0xffffffff)==(0x11111111&0xffffffff))
cnt++;
else
printf("cnt: 1079\n");
writel(0x22222222&0xffffffff,ivp_cae_base_addr+0x00003014);
if((readl(ivp_cae_base_addr+0x00003014)&0xffffffff)==(0x22222222&0xffffffff))
cnt++;
else
printf("cnt: 1080\n");
writel(0x44444444&0xffffffff,ivp_cae_base_addr+0x00003014);
if((readl(ivp_cae_base_addr+0x00003014)&0xffffffff)==(0x44444444&0xffffffff))
cnt++;
else
printf("cnt: 1081\n");
writel(0x88888888&0xffffffff,ivp_cae_base_addr+0x00003014);
if((readl(ivp_cae_base_addr+0x00003014)&0xffffffff)==(0x88888888&0xffffffff))
cnt++;
else
printf("cnt: 1082\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00003014);
if((readl(ivp_cae_base_addr+0x00003014)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 1083\n");
writel(0xffffffff&0xffffffff,ivp_cae_base_addr+0x00003014);
if((readl(ivp_cae_base_addr+0x00003014)&0xffffffff)==(0xffffffff&0xffffffff))
cnt++;
else
printf("cnt: 1084\n");
writel(0x00111110&0xffffffff,ivp_cae_base_addr+0x00003018);
if((readl(ivp_cae_base_addr+0x00003018)&0x00fffffc)==(0x00111110&0x00fffffc))
cnt++;
else
printf("cnt: 1085\n");
writel(0x00222220&0xffffffff,ivp_cae_base_addr+0x00003018);
if((readl(ivp_cae_base_addr+0x00003018)&0x00fffffc)==(0x00222220&0x00fffffc))
cnt++;
else
printf("cnt: 1086\n");
writel(0x00444444&0xffffffff,ivp_cae_base_addr+0x00003018);
if((readl(ivp_cae_base_addr+0x00003018)&0x00fffffc)==(0x00444444&0x00fffffc))
cnt++;
else
printf("cnt: 1087\n");
writel(0x00888888&0xffffffff,ivp_cae_base_addr+0x00003018);
if((readl(ivp_cae_base_addr+0x00003018)&0x00fffffc)==(0x00888888&0x00fffffc))
cnt++;
else
printf("cnt: 1088\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00003018);
if((readl(ivp_cae_base_addr+0x00003018)&0x00fffffc)==(0x00000000&0x00fffffc))
cnt++;
else
printf("cnt: 1089\n");
writel(0x00fffffc&0xffffffff,ivp_cae_base_addr+0x00003018);
if((readl(ivp_cae_base_addr+0x00003018)&0x00fffffc)==(0x00fffffc&0x00fffffc))
cnt++;
else
printf("cnt: 1090\n");
writel(0x00110011&0xffffffff,ivp_cae_base_addr+0x0000301c);
if((readl(ivp_cae_base_addr+0x0000301c)&0xe0ff003f)==(0x00110011&0xe0ff003f))
cnt++;
else
printf("cnt: 1091\n");
writel(0x20220022&0xffffffff,ivp_cae_base_addr+0x0000301c);
if((readl(ivp_cae_base_addr+0x0000301c)&0xe0ff003f)==(0x20220022&0xe0ff003f))
cnt++;
else
printf("cnt: 1092\n");
writel(0x40440004&0xffffffff,ivp_cae_base_addr+0x0000301c);
if((readl(ivp_cae_base_addr+0x0000301c)&0xe0ff003f)==(0x40440004&0xe0ff003f))
cnt++;
else
printf("cnt: 1093\n");
writel(0x80880008&0xffffffff,ivp_cae_base_addr+0x0000301c);
if((readl(ivp_cae_base_addr+0x0000301c)&0xe0ff003f)==(0x80880008&0xe0ff003f))
cnt++;
else
printf("cnt: 1094\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000301c);
if((readl(ivp_cae_base_addr+0x0000301c)&0xe0ff003f)==(0x00000000&0xe0ff003f))
cnt++;
else
printf("cnt: 1095\n");
writel(0xe0ff003f&0xffffffff,ivp_cae_base_addr+0x0000301c);
if((readl(ivp_cae_base_addr+0x0000301c)&0xe0ff003f)==(0xe0ff003f&0xe0ff003f))
cnt++;
else
printf("cnt: 1096\n");
writel(0x10110011&0xffffffff,ivp_cae_base_addr+0x00003020);
if((readl(ivp_cae_base_addr+0x00003020)&0xf03f00ff)==(0x10110011&0xf03f00ff))
cnt++;
else
printf("cnt: 1097\n");
writel(0x20220022&0xffffffff,ivp_cae_base_addr+0x00003020);
if((readl(ivp_cae_base_addr+0x00003020)&0xf03f00ff)==(0x20220022&0xf03f00ff))
cnt++;
else
printf("cnt: 1098\n");
writel(0x40040044&0xffffffff,ivp_cae_base_addr+0x00003020);
if((readl(ivp_cae_base_addr+0x00003020)&0xf03f00ff)==(0x40040044&0xf03f00ff))
cnt++;
else
printf("cnt: 1099\n");
writel(0x80080088&0xffffffff,ivp_cae_base_addr+0x00003020);
if((readl(ivp_cae_base_addr+0x00003020)&0xf03f00ff)==(0x80080088&0xf03f00ff))
cnt++;
else
printf("cnt: 1100\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00003020);
if((readl(ivp_cae_base_addr+0x00003020)&0xf03f00ff)==(0x00000000&0xf03f00ff))
cnt++;
else
printf("cnt: 1101\n");
writel(0xf03f00ff&0xffffffff,ivp_cae_base_addr+0x00003020);
if((readl(ivp_cae_base_addr+0x00003020)&0xf03f00ff)==(0xf03f00ff&0xf03f00ff))
cnt++;
else
printf("cnt: 1102\n");
writel(0x11010101&0xffffffff,ivp_cae_base_addr+0x00003024);
if((readl(ivp_cae_base_addr+0x00003024)&0xff010101)==(0x11010101&0xff010101))
cnt++;
else
printf("cnt: 1103\n");
writel(0x22000000&0xffffffff,ivp_cae_base_addr+0x00003024);
if((readl(ivp_cae_base_addr+0x00003024)&0xff010101)==(0x22000000&0xff010101))
cnt++;
else
printf("cnt: 1104\n");
writel(0x44000000&0xffffffff,ivp_cae_base_addr+0x00003024);
if((readl(ivp_cae_base_addr+0x00003024)&0xff010101)==(0x44000000&0xff010101))
cnt++;
else
printf("cnt: 1105\n");
writel(0x88000000&0xffffffff,ivp_cae_base_addr+0x00003024);
if((readl(ivp_cae_base_addr+0x00003024)&0xff010101)==(0x88000000&0xff010101))
cnt++;
else
printf("cnt: 1106\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00003024);
if((readl(ivp_cae_base_addr+0x00003024)&0xff010101)==(0x00000000&0xff010101))
cnt++;
else
printf("cnt: 1107\n");
writel(0xff010101&0xffffffff,ivp_cae_base_addr+0x00003024);
if((readl(ivp_cae_base_addr+0x00003024)&0xff010101)==(0xff010101&0xff010101))
cnt++;
else
printf("cnt: 1108\n");
writel(0x11000000&0xffffffff,ivp_cae_base_addr+0x00003028);
if((readl(ivp_cae_base_addr+0x00003028)&0xffc00000)==(0x11000000&0xffc00000))
cnt++;
else
printf("cnt: 1109\n");
writel(0x22000000&0xffffffff,ivp_cae_base_addr+0x00003028);
if((readl(ivp_cae_base_addr+0x00003028)&0xffc00000)==(0x22000000&0xffc00000))
cnt++;
else
printf("cnt: 1110\n");
writel(0x44400000&0xffffffff,ivp_cae_base_addr+0x00003028);
if((readl(ivp_cae_base_addr+0x00003028)&0xffc00000)==(0x44400000&0xffc00000))
cnt++;
else
printf("cnt: 1111\n");
writel(0x88800000&0xffffffff,ivp_cae_base_addr+0x00003028);
if((readl(ivp_cae_base_addr+0x00003028)&0xffc00000)==(0x88800000&0xffc00000))
cnt++;
else
printf("cnt: 1112\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00003028);
if((readl(ivp_cae_base_addr+0x00003028)&0xffc00000)==(0x00000000&0xffc00000))
cnt++;
else
printf("cnt: 1113\n");
writel(0xffc00000&0xffffffff,ivp_cae_base_addr+0x00003028);
if((readl(ivp_cae_base_addr+0x00003028)&0xffc00000)==(0xffc00000&0xffc00000))
cnt++;
else
printf("cnt: 1114\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000302c);
if((readl(ivp_cae_base_addr+0x0000302c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1115\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000302c);
if((readl(ivp_cae_base_addr+0x0000302c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1116\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000302c);
if((readl(ivp_cae_base_addr+0x0000302c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1117\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000302c);
if((readl(ivp_cae_base_addr+0x0000302c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1118\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000302c);
if((readl(ivp_cae_base_addr+0x0000302c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1119\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000302c);
if((readl(ivp_cae_base_addr+0x0000302c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1120\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00003030);
if((readl(ivp_cae_base_addr+0x00003030)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1121\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00003030);
if((readl(ivp_cae_base_addr+0x00003030)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1122\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00003030);
if((readl(ivp_cae_base_addr+0x00003030)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1123\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00003030);
if((readl(ivp_cae_base_addr+0x00003030)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1124\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00003030);
if((readl(ivp_cae_base_addr+0x00003030)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1125\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00003030);
if((readl(ivp_cae_base_addr+0x00003030)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1126\n");
writel(0x00111110&0xffffffff,ivp_cae_base_addr+0x00003034);
if((readl(ivp_cae_base_addr+0x00003034)&0x00fffffc)==(0x00111110&0x00fffffc))
cnt++;
else
printf("cnt: 1127\n");
writel(0x00222220&0xffffffff,ivp_cae_base_addr+0x00003034);
if((readl(ivp_cae_base_addr+0x00003034)&0x00fffffc)==(0x00222220&0x00fffffc))
cnt++;
else
printf("cnt: 1128\n");
writel(0x00444444&0xffffffff,ivp_cae_base_addr+0x00003034);
if((readl(ivp_cae_base_addr+0x00003034)&0x00fffffc)==(0x00444444&0x00fffffc))
cnt++;
else
printf("cnt: 1129\n");
writel(0x00888888&0xffffffff,ivp_cae_base_addr+0x00003034);
if((readl(ivp_cae_base_addr+0x00003034)&0x00fffffc)==(0x00888888&0x00fffffc))
cnt++;
else
printf("cnt: 1130\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00003034);
if((readl(ivp_cae_base_addr+0x00003034)&0x00fffffc)==(0x00000000&0x00fffffc))
cnt++;
else
printf("cnt: 1131\n");
writel(0x00fffffc&0xffffffff,ivp_cae_base_addr+0x00003034);
if((readl(ivp_cae_base_addr+0x00003034)&0x00fffffc)==(0x00fffffc&0x00fffffc))
cnt++;
else
printf("cnt: 1132\n");
writel(0x00111110&0xffffffff,ivp_cae_base_addr+0x00003038);
if((readl(ivp_cae_base_addr+0x00003038)&0x00fffffc)==(0x00111110&0x00fffffc))
cnt++;
else
printf("cnt: 1133\n");
writel(0x00222220&0xffffffff,ivp_cae_base_addr+0x00003038);
if((readl(ivp_cae_base_addr+0x00003038)&0x00fffffc)==(0x00222220&0x00fffffc))
cnt++;
else
printf("cnt: 1134\n");
writel(0x00444444&0xffffffff,ivp_cae_base_addr+0x00003038);
if((readl(ivp_cae_base_addr+0x00003038)&0x00fffffc)==(0x00444444&0x00fffffc))
cnt++;
else
printf("cnt: 1135\n");
writel(0x00888888&0xffffffff,ivp_cae_base_addr+0x00003038);
if((readl(ivp_cae_base_addr+0x00003038)&0x00fffffc)==(0x00888888&0x00fffffc))
cnt++;
else
printf("cnt: 1136\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00003038);
if((readl(ivp_cae_base_addr+0x00003038)&0x00fffffc)==(0x00000000&0x00fffffc))
cnt++;
else
printf("cnt: 1137\n");
writel(0x00fffffc&0xffffffff,ivp_cae_base_addr+0x00003038);
if((readl(ivp_cae_base_addr+0x00003038)&0x00fffffc)==(0x00fffffc&0x00fffffc))
cnt++;
else
printf("cnt: 1138\n");
writel(0x00000011&0xffffffff,ivp_cae_base_addr+0x0000303c);
if((readl(ivp_cae_base_addr+0x0000303c)&0x00000000)==(0x00000011&0x00000000))
cnt++;
else
printf("cnt: 1139\n");
writel(0x00000022&0xffffffff,ivp_cae_base_addr+0x0000303c);
if((readl(ivp_cae_base_addr+0x0000303c)&0x00000000)==(0x00000022&0x00000000))
cnt++;
else
printf("cnt: 1140\n");
writel(0x00000004&0xffffffff,ivp_cae_base_addr+0x0000303c);
if((readl(ivp_cae_base_addr+0x0000303c)&0x00000000)==(0x00000004&0x00000000))
cnt++;
else
printf("cnt: 1141\n");
writel(0x00000008&0xffffffff,ivp_cae_base_addr+0x0000303c);
if((readl(ivp_cae_base_addr+0x0000303c)&0x00000000)==(0x00000008&0x00000000))
cnt++;
else
printf("cnt: 1142\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000303c);
if((readl(ivp_cae_base_addr+0x0000303c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1143\n");
writel(0x0000003f&0xffffffff,ivp_cae_base_addr+0x0000303c);
if((readl(ivp_cae_base_addr+0x0000303c)&0x00000000)==(0x0000003f&0x00000000))
cnt++;
else
printf("cnt: 1144\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000037f8);
if((readl(ivp_cae_base_addr+0x000037f8)&0xb7ffffff)==(0x80a35514&0xb7ffffff))
cnt++;
else
printf("cnt: 1145\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000037f8);
if((readl(ivp_cae_base_addr+0x000037f8)&0xb7ffffff)==(0x80a35514&0xb7ffffff))
cnt++;
else
printf("cnt: 1146\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000037f8);
if((readl(ivp_cae_base_addr+0x000037f8)&0xb7ffffff)==(0x80a35514&0xb7ffffff))
cnt++;
else
printf("cnt: 1147\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000037f8);
if((readl(ivp_cae_base_addr+0x000037f8)&0xb7ffffff)==(0x80a35514&0xb7ffffff))
cnt++;
else
printf("cnt: 1148\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000037f8);
if((readl(ivp_cae_base_addr+0x000037f8)&0xb7ffffff)==(0x80a35514&0xb7ffffff))
cnt++;
else
printf("cnt: 1149\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000037f8);
if((readl(ivp_cae_base_addr+0x000037f8)&0xb7ffffff)==(0x80a35514&0xb7ffffff))
cnt++;
else
printf("cnt: 1150\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000037fc);
if((readl(ivp_cae_base_addr+0x000037fc)&0x0fffffff)==(0x027035ca&0x0fffffff))
cnt++;
else
printf("cnt: 1151\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000037fc);
if((readl(ivp_cae_base_addr+0x000037fc)&0x0fffffff)==(0x027035ca&0x0fffffff))
cnt++;
else
printf("cnt: 1152\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000037fc);
if((readl(ivp_cae_base_addr+0x000037fc)&0x0fffffff)==(0x027035ca&0x0fffffff))
cnt++;
else
printf("cnt: 1153\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000037fc);
if((readl(ivp_cae_base_addr+0x000037fc)&0x0fffffff)==(0x027035ca&0x0fffffff))
cnt++;
else
printf("cnt: 1154\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000037fc);
if((readl(ivp_cae_base_addr+0x000037fc)&0x0fffffff)==(0x027035ca&0x0fffffff))
cnt++;
else
printf("cnt: 1155\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000037fc);
if((readl(ivp_cae_base_addr+0x000037fc)&0x0fffffff)==(0x027035ca&0x0fffffff))
cnt++;
else
printf("cnt: 1156\n");
writel(0x11111111&0xffffffff,ivp_cae_base_addr+0x00003800);
if((readl(ivp_cae_base_addr+0x00003800)&0xffffffff)==(0x11111111&0xffffffff))
cnt++;
else
printf("cnt: 1157\n");
writel(0x22222222&0xffffffff,ivp_cae_base_addr+0x00003800);
if((readl(ivp_cae_base_addr+0x00003800)&0xffffffff)==(0x22222222&0xffffffff))
cnt++;
else
printf("cnt: 1158\n");
writel(0x44444444&0xffffffff,ivp_cae_base_addr+0x00003800);
if((readl(ivp_cae_base_addr+0x00003800)&0xffffffff)==(0x44444444&0xffffffff))
cnt++;
else
printf("cnt: 1159\n");
writel(0x88888888&0xffffffff,ivp_cae_base_addr+0x00003800);
if((readl(ivp_cae_base_addr+0x00003800)&0xffffffff)==(0x88888888&0xffffffff))
cnt++;
else
printf("cnt: 1160\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00003800);
if((readl(ivp_cae_base_addr+0x00003800)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 1161\n");
writel(0xffffffff&0xffffffff,ivp_cae_base_addr+0x00003800);
if((readl(ivp_cae_base_addr+0x00003800)&0xffffffff)==(0xffffffff&0xffffffff))
cnt++;
else
printf("cnt: 1162\n");
writel(0x11111111&0xffffffff,ivp_cae_base_addr+0x00003804);
if((readl(ivp_cae_base_addr+0x00003804)&0xffffffff)==(0x11111111&0xffffffff))
cnt++;
else
printf("cnt: 1163\n");
writel(0x22222222&0xffffffff,ivp_cae_base_addr+0x00003804);
if((readl(ivp_cae_base_addr+0x00003804)&0xffffffff)==(0x22222222&0xffffffff))
cnt++;
else
printf("cnt: 1164\n");
writel(0x44444444&0xffffffff,ivp_cae_base_addr+0x00003804);
if((readl(ivp_cae_base_addr+0x00003804)&0xffffffff)==(0x44444444&0xffffffff))
cnt++;
else
printf("cnt: 1165\n");
writel(0x88888888&0xffffffff,ivp_cae_base_addr+0x00003804);
if((readl(ivp_cae_base_addr+0x00003804)&0xffffffff)==(0x88888888&0xffffffff))
cnt++;
else
printf("cnt: 1166\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00003804);
if((readl(ivp_cae_base_addr+0x00003804)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 1167\n");
writel(0xffffffff&0xffffffff,ivp_cae_base_addr+0x00003804);
if((readl(ivp_cae_base_addr+0x00003804)&0xffffffff)==(0xffffffff&0xffffffff))
cnt++;
else
printf("cnt: 1168\n");
writel(0x11111111&0xffffffff,ivp_cae_base_addr+0x00003808);
if((readl(ivp_cae_base_addr+0x00003808)&0xffffffff)==(0x11111111&0xffffffff))
cnt++;
else
printf("cnt: 1169\n");
writel(0x22222222&0xffffffff,ivp_cae_base_addr+0x00003808);
if((readl(ivp_cae_base_addr+0x00003808)&0xffffffff)==(0x22222222&0xffffffff))
cnt++;
else
printf("cnt: 1170\n");
writel(0x44444444&0xffffffff,ivp_cae_base_addr+0x00003808);
if((readl(ivp_cae_base_addr+0x00003808)&0xffffffff)==(0x44444444&0xffffffff))
cnt++;
else
printf("cnt: 1171\n");
writel(0x88888888&0xffffffff,ivp_cae_base_addr+0x00003808);
if((readl(ivp_cae_base_addr+0x00003808)&0xffffffff)==(0x88888888&0xffffffff))
cnt++;
else
printf("cnt: 1172\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00003808);
if((readl(ivp_cae_base_addr+0x00003808)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 1173\n");
writel(0xffffffff&0xffffffff,ivp_cae_base_addr+0x00003808);
if((readl(ivp_cae_base_addr+0x00003808)&0xffffffff)==(0xffffffff&0xffffffff))
cnt++;
else
printf("cnt: 1174\n");
writel(0x11111111&0xffffffff,ivp_cae_base_addr+0x0000380c);
if((readl(ivp_cae_base_addr+0x0000380c)&0xffffffff)==(0x11111111&0xffffffff))
cnt++;
else
printf("cnt: 1175\n");
writel(0x22222222&0xffffffff,ivp_cae_base_addr+0x0000380c);
if((readl(ivp_cae_base_addr+0x0000380c)&0xffffffff)==(0x22222222&0xffffffff))
cnt++;
else
printf("cnt: 1176\n");
writel(0x44444444&0xffffffff,ivp_cae_base_addr+0x0000380c);
if((readl(ivp_cae_base_addr+0x0000380c)&0xffffffff)==(0x44444444&0xffffffff))
cnt++;
else
printf("cnt: 1177\n");
writel(0x88888888&0xffffffff,ivp_cae_base_addr+0x0000380c);
if((readl(ivp_cae_base_addr+0x0000380c)&0xffffffff)==(0x88888888&0xffffffff))
cnt++;
else
printf("cnt: 1178\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000380c);
if((readl(ivp_cae_base_addr+0x0000380c)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 1179\n");
writel(0xffffffff&0xffffffff,ivp_cae_base_addr+0x0000380c);
if((readl(ivp_cae_base_addr+0x0000380c)&0xffffffff)==(0xffffffff&0xffffffff))
cnt++;
else
printf("cnt: 1180\n");
writel(0x00111110&0xffffffff,ivp_cae_base_addr+0x00003818);
if((readl(ivp_cae_base_addr+0x00003818)&0x00fffffc)==(0x00111110&0x00fffffc))
cnt++;
else
printf("cnt: 1181\n");
writel(0x00222220&0xffffffff,ivp_cae_base_addr+0x00003818);
if((readl(ivp_cae_base_addr+0x00003818)&0x00fffffc)==(0x00222220&0x00fffffc))
cnt++;
else
printf("cnt: 1182\n");
writel(0x00444444&0xffffffff,ivp_cae_base_addr+0x00003818);
if((readl(ivp_cae_base_addr+0x00003818)&0x00fffffc)==(0x00444444&0x00fffffc))
cnt++;
else
printf("cnt: 1183\n");
writel(0x00888888&0xffffffff,ivp_cae_base_addr+0x00003818);
if((readl(ivp_cae_base_addr+0x00003818)&0x00fffffc)==(0x00888888&0x00fffffc))
cnt++;
else
printf("cnt: 1184\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00003818);
if((readl(ivp_cae_base_addr+0x00003818)&0x00fffffc)==(0x00000000&0x00fffffc))
cnt++;
else
printf("cnt: 1185\n");
writel(0x00fffffc&0xffffffff,ivp_cae_base_addr+0x00003818);
if((readl(ivp_cae_base_addr+0x00003818)&0x00fffffc)==(0x00fffffc&0x00fffffc))
cnt++;
else
printf("cnt: 1186\n");
writel(0x00110011&0xffffffff,ivp_cae_base_addr+0x0000381c);
if((readl(ivp_cae_base_addr+0x0000381c)&0xe0ff00ff)==(0x00110011&0xe0ff00ff))
cnt++;
else
printf("cnt: 1187\n");
writel(0x20220022&0xffffffff,ivp_cae_base_addr+0x0000381c);
if((readl(ivp_cae_base_addr+0x0000381c)&0xe0ff00ff)==(0x20220022&0xe0ff00ff))
cnt++;
else
printf("cnt: 1188\n");
writel(0x40440044&0xffffffff,ivp_cae_base_addr+0x0000381c);
if((readl(ivp_cae_base_addr+0x0000381c)&0xe0ff00ff)==(0x40440044&0xe0ff00ff))
cnt++;
else
printf("cnt: 1189\n");
writel(0x80880088&0xffffffff,ivp_cae_base_addr+0x0000381c);
if((readl(ivp_cae_base_addr+0x0000381c)&0xe0ff00ff)==(0x80880088&0xe0ff00ff))
cnt++;
else
printf("cnt: 1190\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000381c);
if((readl(ivp_cae_base_addr+0x0000381c)&0xe0ff00ff)==(0x00000000&0xe0ff00ff))
cnt++;
else
printf("cnt: 1191\n");
writel(0xe0ff00ff&0xffffffff,ivp_cae_base_addr+0x0000381c);
if((readl(ivp_cae_base_addr+0x0000381c)&0xe0ff00ff)==(0xe0ff00ff&0xe0ff00ff))
cnt++;
else
printf("cnt: 1192\n");
writel(0x10110011&0xffffffff,ivp_cae_base_addr+0x00003820);
if((readl(ivp_cae_base_addr+0x00003820)&0xf03f00ff)==(0x10110011&0xf03f00ff))
cnt++;
else
printf("cnt: 1193\n");
writel(0x20220022&0xffffffff,ivp_cae_base_addr+0x00003820);
if((readl(ivp_cae_base_addr+0x00003820)&0xf03f00ff)==(0x20220022&0xf03f00ff))
cnt++;
else
printf("cnt: 1194\n");
writel(0x40040044&0xffffffff,ivp_cae_base_addr+0x00003820);
if((readl(ivp_cae_base_addr+0x00003820)&0xf03f00ff)==(0x40040044&0xf03f00ff))
cnt++;
else
printf("cnt: 1195\n");
writel(0x80080088&0xffffffff,ivp_cae_base_addr+0x00003820);
if((readl(ivp_cae_base_addr+0x00003820)&0xf03f00ff)==(0x80080088&0xf03f00ff))
cnt++;
else
printf("cnt: 1196\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00003820);
if((readl(ivp_cae_base_addr+0x00003820)&0xf03f00ff)==(0x00000000&0xf03f00ff))
cnt++;
else
printf("cnt: 1197\n");
writel(0xf03f00ff&0xffffffff,ivp_cae_base_addr+0x00003820);
if((readl(ivp_cae_base_addr+0x00003820)&0xf03f00ff)==(0xf03f00ff&0xf03f00ff))
cnt++;
else
printf("cnt: 1198\n");
writel(0x11100101&0xffffffff,ivp_cae_base_addr+0x00003824);
if((readl(ivp_cae_base_addr+0x00003824)&0xfff80101)==(0x11100101&0xfff80101))
cnt++;
else
printf("cnt: 1199\n");
writel(0x22200000&0xffffffff,ivp_cae_base_addr+0x00003824);
if((readl(ivp_cae_base_addr+0x00003824)&0xfff80101)==(0x22200000&0xfff80101))
cnt++;
else
printf("cnt: 1200\n");
writel(0x44400000&0xffffffff,ivp_cae_base_addr+0x00003824);
if((readl(ivp_cae_base_addr+0x00003824)&0xfff80101)==(0x44400000&0xfff80101))
cnt++;
else
printf("cnt: 1201\n");
writel(0x88880000&0xffffffff,ivp_cae_base_addr+0x00003824);
if((readl(ivp_cae_base_addr+0x00003824)&0xfff80101)==(0x88880000&0xfff80101))
cnt++;
else
printf("cnt: 1202\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00003824);
if((readl(ivp_cae_base_addr+0x00003824)&0xfff80101)==(0x00000000&0xfff80101))
cnt++;
else
printf("cnt: 1203\n");
writel(0xfff80101&0xffffffff,ivp_cae_base_addr+0x00003824);
if((readl(ivp_cae_base_addr+0x00003824)&0xfff80101)==(0xfff80101&0xfff80101))
cnt++;
else
printf("cnt: 1204\n");
writel(0x11000000&0xffffffff,ivp_cae_base_addr+0x00003828);
if((readl(ivp_cae_base_addr+0x00003828)&0xff800000)==(0x11000000&0xff800000))
cnt++;
else
printf("cnt: 1205\n");
writel(0x22000000&0xffffffff,ivp_cae_base_addr+0x00003828);
if((readl(ivp_cae_base_addr+0x00003828)&0xff800000)==(0x22000000&0xff800000))
cnt++;
else
printf("cnt: 1206\n");
writel(0x44000000&0xffffffff,ivp_cae_base_addr+0x00003828);
if((readl(ivp_cae_base_addr+0x00003828)&0xff800000)==(0x44000000&0xff800000))
cnt++;
else
printf("cnt: 1207\n");
writel(0x88800000&0xffffffff,ivp_cae_base_addr+0x00003828);
if((readl(ivp_cae_base_addr+0x00003828)&0xff800000)==(0x88800000&0xff800000))
cnt++;
else
printf("cnt: 1208\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00003828);
if((readl(ivp_cae_base_addr+0x00003828)&0xff800000)==(0x00000000&0xff800000))
cnt++;
else
printf("cnt: 1209\n");
writel(0xff800000&0xffffffff,ivp_cae_base_addr+0x00003828);
if((readl(ivp_cae_base_addr+0x00003828)&0xff800000)==(0xff800000&0xff800000))
cnt++;
else
printf("cnt: 1210\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000382c);
if((readl(ivp_cae_base_addr+0x0000382c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1211\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000382c);
if((readl(ivp_cae_base_addr+0x0000382c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1212\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000382c);
if((readl(ivp_cae_base_addr+0x0000382c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1213\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000382c);
if((readl(ivp_cae_base_addr+0x0000382c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1214\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000382c);
if((readl(ivp_cae_base_addr+0x0000382c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1215\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000382c);
if((readl(ivp_cae_base_addr+0x0000382c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1216\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00003830);
if((readl(ivp_cae_base_addr+0x00003830)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1217\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00003830);
if((readl(ivp_cae_base_addr+0x00003830)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1218\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00003830);
if((readl(ivp_cae_base_addr+0x00003830)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1219\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00003830);
if((readl(ivp_cae_base_addr+0x00003830)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1220\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00003830);
if((readl(ivp_cae_base_addr+0x00003830)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1221\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00003830);
if((readl(ivp_cae_base_addr+0x00003830)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1222\n");
writel(0x00111110&0xffffffff,ivp_cae_base_addr+0x00003834);
if((readl(ivp_cae_base_addr+0x00003834)&0x00fffffc)==(0x00111110&0x00fffffc))
cnt++;
else
printf("cnt: 1223\n");
writel(0x00222220&0xffffffff,ivp_cae_base_addr+0x00003834);
if((readl(ivp_cae_base_addr+0x00003834)&0x00fffffc)==(0x00222220&0x00fffffc))
cnt++;
else
printf("cnt: 1224\n");
writel(0x00444444&0xffffffff,ivp_cae_base_addr+0x00003834);
if((readl(ivp_cae_base_addr+0x00003834)&0x00fffffc)==(0x00444444&0x00fffffc))
cnt++;
else
printf("cnt: 1225\n");
writel(0x00888888&0xffffffff,ivp_cae_base_addr+0x00003834);
if((readl(ivp_cae_base_addr+0x00003834)&0x00fffffc)==(0x00888888&0x00fffffc))
cnt++;
else
printf("cnt: 1226\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00003834);
if((readl(ivp_cae_base_addr+0x00003834)&0x00fffffc)==(0x00000000&0x00fffffc))
cnt++;
else
printf("cnt: 1227\n");
writel(0x00fffffc&0xffffffff,ivp_cae_base_addr+0x00003834);
if((readl(ivp_cae_base_addr+0x00003834)&0x00fffffc)==(0x00fffffc&0x00fffffc))
cnt++;
else
printf("cnt: 1228\n");
writel(0x00111110&0xffffffff,ivp_cae_base_addr+0x00003838);
if((readl(ivp_cae_base_addr+0x00003838)&0x00fffffc)==(0x00111110&0x00fffffc))
cnt++;
else
printf("cnt: 1229\n");
writel(0x00222220&0xffffffff,ivp_cae_base_addr+0x00003838);
if((readl(ivp_cae_base_addr+0x00003838)&0x00fffffc)==(0x00222220&0x00fffffc))
cnt++;
else
printf("cnt: 1230\n");
writel(0x00444444&0xffffffff,ivp_cae_base_addr+0x00003838);
if((readl(ivp_cae_base_addr+0x00003838)&0x00fffffc)==(0x00444444&0x00fffffc))
cnt++;
else
printf("cnt: 1231\n");
writel(0x00888888&0xffffffff,ivp_cae_base_addr+0x00003838);
if((readl(ivp_cae_base_addr+0x00003838)&0x00fffffc)==(0x00888888&0x00fffffc))
cnt++;
else
printf("cnt: 1232\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00003838);
if((readl(ivp_cae_base_addr+0x00003838)&0x00fffffc)==(0x00000000&0x00fffffc))
cnt++;
else
printf("cnt: 1233\n");
writel(0x00fffffc&0xffffffff,ivp_cae_base_addr+0x00003838);
if((readl(ivp_cae_base_addr+0x00003838)&0x00fffffc)==(0x00fffffc&0x00fffffc))
cnt++;
else
printf("cnt: 1234\n");
writel(0x00000011&0xffffffff,ivp_cae_base_addr+0x0000383c);
if((readl(ivp_cae_base_addr+0x0000383c)&0x00000000)==(0x00000011&0x00000000))
cnt++;
else
printf("cnt: 1235\n");
writel(0x00000022&0xffffffff,ivp_cae_base_addr+0x0000383c);
if((readl(ivp_cae_base_addr+0x0000383c)&0x00000000)==(0x00000022&0x00000000))
cnt++;
else
printf("cnt: 1236\n");
writel(0x00000044&0xffffffff,ivp_cae_base_addr+0x0000383c);
if((readl(ivp_cae_base_addr+0x0000383c)&0x00000000)==(0x00000044&0x00000000))
cnt++;
else
printf("cnt: 1237\n");
writel(0x00000088&0xffffffff,ivp_cae_base_addr+0x0000383c);
if((readl(ivp_cae_base_addr+0x0000383c)&0x00000000)==(0x00000088&0x00000000))
cnt++;
else
printf("cnt: 1238\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000383c);
if((readl(ivp_cae_base_addr+0x0000383c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1239\n");
writel(0x000000ff&0xffffffff,ivp_cae_base_addr+0x0000383c);
if((readl(ivp_cae_base_addr+0x0000383c)&0x00000000)==(0x000000ff&0x00000000))
cnt++;
else
printf("cnt: 1240\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00003ff8);
if((readl(ivp_cae_base_addr+0x00003ff8)&0xb7ffffff)==(0x80a35514&0xb7ffffff))
cnt++;
else
printf("cnt: 1241\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00003ff8);
if((readl(ivp_cae_base_addr+0x00003ff8)&0xb7ffffff)==(0x80a35514&0xb7ffffff))
cnt++;
else
printf("cnt: 1242\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00003ff8);
if((readl(ivp_cae_base_addr+0x00003ff8)&0xb7ffffff)==(0x80a35514&0xb7ffffff))
cnt++;
else
printf("cnt: 1243\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00003ff8);
if((readl(ivp_cae_base_addr+0x00003ff8)&0xb7ffffff)==(0x80a35514&0xb7ffffff))
cnt++;
else
printf("cnt: 1244\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00003ff8);
if((readl(ivp_cae_base_addr+0x00003ff8)&0xb7ffffff)==(0x80a35514&0xb7ffffff))
cnt++;
else
printf("cnt: 1245\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00003ff8);
if((readl(ivp_cae_base_addr+0x00003ff8)&0xb7ffffff)==(0x80a35514&0xb7ffffff))
cnt++;
else
printf("cnt: 1246\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00003ffc);
if((readl(ivp_cae_base_addr+0x00003ffc)&0x0fffffff)==(0x027035ca&0x0fffffff))
cnt++;
else
printf("cnt: 1247\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00003ffc);
if((readl(ivp_cae_base_addr+0x00003ffc)&0x0fffffff)==(0x027035ca&0x0fffffff))
cnt++;
else
printf("cnt: 1248\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00003ffc);
if((readl(ivp_cae_base_addr+0x00003ffc)&0x0fffffff)==(0x027035ca&0x0fffffff))
cnt++;
else
printf("cnt: 1249\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00003ffc);
if((readl(ivp_cae_base_addr+0x00003ffc)&0x0fffffff)==(0x027035ca&0x0fffffff))
cnt++;
else
printf("cnt: 1250\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00003ffc);
if((readl(ivp_cae_base_addr+0x00003ffc)&0x0fffffff)==(0x027035ca&0x0fffffff))
cnt++;
else
printf("cnt: 1251\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00003ffc);
if((readl(ivp_cae_base_addr+0x00003ffc)&0x0fffffff)==(0x027035ca&0x0fffffff))
cnt++;
else
printf("cnt: 1252\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000b000);
if((readl(ivp_cae_base_addr+0x0000b000)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1253\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000b000);
if((readl(ivp_cae_base_addr+0x0000b000)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1254\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000b000);
if((readl(ivp_cae_base_addr+0x0000b000)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1255\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000b000);
if((readl(ivp_cae_base_addr+0x0000b000)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1256\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000b000);
if((readl(ivp_cae_base_addr+0x0000b000)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1257\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000b000);
if((readl(ivp_cae_base_addr+0x0000b000)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1258\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000b004);
if((readl(ivp_cae_base_addr+0x0000b004)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1259\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000b004);
if((readl(ivp_cae_base_addr+0x0000b004)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1260\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000b004);
if((readl(ivp_cae_base_addr+0x0000b004)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1261\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000b004);
if((readl(ivp_cae_base_addr+0x0000b004)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1262\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000b004);
if((readl(ivp_cae_base_addr+0x0000b004)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1263\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000b004);
if((readl(ivp_cae_base_addr+0x0000b004)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1264\n");
writel(0x00000011&0xffffffff,ivp_cae_base_addr+0x0000b008);
if((readl(ivp_cae_base_addr+0x0000b008)&0x000000ff)==(0x00000011&0x000000ff))
cnt++;
else
printf("cnt: 1265\n");
writel(0x00000022&0xffffffff,ivp_cae_base_addr+0x0000b008);
if((readl(ivp_cae_base_addr+0x0000b008)&0x000000ff)==(0x00000022&0x000000ff))
cnt++;
else
printf("cnt: 1266\n");
writel(0x00000044&0xffffffff,ivp_cae_base_addr+0x0000b008);
if((readl(ivp_cae_base_addr+0x0000b008)&0x000000ff)==(0x00000044&0x000000ff))
cnt++;
else
printf("cnt: 1267\n");
writel(0x00000088&0xffffffff,ivp_cae_base_addr+0x0000b008);
if((readl(ivp_cae_base_addr+0x0000b008)&0x000000ff)==(0x00000088&0x000000ff))
cnt++;
else
printf("cnt: 1268\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000b008);
if((readl(ivp_cae_base_addr+0x0000b008)&0x000000ff)==(0x00000000&0x000000ff))
cnt++;
else
printf("cnt: 1269\n");
writel(0x000000ff&0xffffffff,ivp_cae_base_addr+0x0000b008);
if((readl(ivp_cae_base_addr+0x0000b008)&0x000000ff)==(0x000000ff&0x000000ff))
cnt++;
else
printf("cnt: 1270\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000b00c);
if((readl(ivp_cae_base_addr+0x0000b00c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1271\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000b00c);
if((readl(ivp_cae_base_addr+0x0000b00c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1272\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000b00c);
if((readl(ivp_cae_base_addr+0x0000b00c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1273\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000b00c);
if((readl(ivp_cae_base_addr+0x0000b00c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1274\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000b00c);
if((readl(ivp_cae_base_addr+0x0000b00c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1275\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000b00c);
if((readl(ivp_cae_base_addr+0x0000b00c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1276\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000b010);
if((readl(ivp_cae_base_addr+0x0000b010)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1277\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000b010);
if((readl(ivp_cae_base_addr+0x0000b010)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1278\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000b010);
if((readl(ivp_cae_base_addr+0x0000b010)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1279\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000b010);
if((readl(ivp_cae_base_addr+0x0000b010)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1280\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000b010);
if((readl(ivp_cae_base_addr+0x0000b010)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1281\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000b010);
if((readl(ivp_cae_base_addr+0x0000b010)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1282\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000b014);
if((readl(ivp_cae_base_addr+0x0000b014)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1283\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000b014);
if((readl(ivp_cae_base_addr+0x0000b014)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1284\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000b014);
if((readl(ivp_cae_base_addr+0x0000b014)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1285\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000b014);
if((readl(ivp_cae_base_addr+0x0000b014)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1286\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000b014);
if((readl(ivp_cae_base_addr+0x0000b014)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1287\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000b014);
if((readl(ivp_cae_base_addr+0x0000b014)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1288\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000b018);
if((readl(ivp_cae_base_addr+0x0000b018)&0x000001bf)==(0x00000008&0x000001bf))
cnt++;
else
printf("cnt: 1289\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000b018);
if((readl(ivp_cae_base_addr+0x0000b018)&0x000001bf)==(0x00000008&0x000001bf))
cnt++;
else
printf("cnt: 1290\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000b018);
if((readl(ivp_cae_base_addr+0x0000b018)&0x000001bf)==(0x00000008&0x000001bf))
cnt++;
else
printf("cnt: 1291\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000b018);
if((readl(ivp_cae_base_addr+0x0000b018)&0x000001bf)==(0x00000008&0x000001bf))
cnt++;
else
printf("cnt: 1292\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000b018);
if((readl(ivp_cae_base_addr+0x0000b018)&0x000001bf)==(0x00000008&0x000001bf))
cnt++;
else
printf("cnt: 1293\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000b018);
if((readl(ivp_cae_base_addr+0x0000b018)&0x000001bf)==(0x00000008&0x000001bf))
cnt++;
else
printf("cnt: 1294\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000b01c);
if((readl(ivp_cae_base_addr+0x0000b01c)&0x0fffffff)==(0x014036c9&0x0fffffff))
cnt++;
else
printf("cnt: 1295\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000b01c);
if((readl(ivp_cae_base_addr+0x0000b01c)&0x0fffffff)==(0x014036c9&0x0fffffff))
cnt++;
else
printf("cnt: 1296\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000b01c);
if((readl(ivp_cae_base_addr+0x0000b01c)&0x0fffffff)==(0x014036c9&0x0fffffff))
cnt++;
else
printf("cnt: 1297\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000b01c);
if((readl(ivp_cae_base_addr+0x0000b01c)&0x0fffffff)==(0x014036c9&0x0fffffff))
cnt++;
else
printf("cnt: 1298\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000b01c);
if((readl(ivp_cae_base_addr+0x0000b01c)&0x0fffffff)==(0x014036c9&0x0fffffff))
cnt++;
else
printf("cnt: 1299\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000b01c);
if((readl(ivp_cae_base_addr+0x0000b01c)&0x0fffffff)==(0x014036c9&0x0fffffff))
cnt++;
else
printf("cnt: 1300\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000c000);
if((readl(ivp_cae_base_addr+0x0000c000)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1301\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000c000);
if((readl(ivp_cae_base_addr+0x0000c000)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1302\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000c000);
if((readl(ivp_cae_base_addr+0x0000c000)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1303\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000c000);
if((readl(ivp_cae_base_addr+0x0000c000)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1304\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000c000);
if((readl(ivp_cae_base_addr+0x0000c000)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1305\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000c000);
if((readl(ivp_cae_base_addr+0x0000c000)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1306\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000c004);
if((readl(ivp_cae_base_addr+0x0000c004)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1307\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000c004);
if((readl(ivp_cae_base_addr+0x0000c004)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1308\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000c004);
if((readl(ivp_cae_base_addr+0x0000c004)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1309\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000c004);
if((readl(ivp_cae_base_addr+0x0000c004)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1310\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000c004);
if((readl(ivp_cae_base_addr+0x0000c004)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1311\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000c004);
if((readl(ivp_cae_base_addr+0x0000c004)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1312\n");
writel(0x00000011&0xffffffff,ivp_cae_base_addr+0x0000c008);
if((readl(ivp_cae_base_addr+0x0000c008)&0x000000ff)==(0x00000011&0x000000ff))
cnt++;
else
printf("cnt: 1313\n");
writel(0x00000022&0xffffffff,ivp_cae_base_addr+0x0000c008);
if((readl(ivp_cae_base_addr+0x0000c008)&0x000000ff)==(0x00000022&0x000000ff))
cnt++;
else
printf("cnt: 1314\n");
writel(0x00000044&0xffffffff,ivp_cae_base_addr+0x0000c008);
if((readl(ivp_cae_base_addr+0x0000c008)&0x000000ff)==(0x00000044&0x000000ff))
cnt++;
else
printf("cnt: 1315\n");
writel(0x00000088&0xffffffff,ivp_cae_base_addr+0x0000c008);
if((readl(ivp_cae_base_addr+0x0000c008)&0x000000ff)==(0x00000088&0x000000ff))
cnt++;
else
printf("cnt: 1316\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000c008);
if((readl(ivp_cae_base_addr+0x0000c008)&0x000000ff)==(0x00000000&0x000000ff))
cnt++;
else
printf("cnt: 1317\n");
writel(0x000000ff&0xffffffff,ivp_cae_base_addr+0x0000c008);
if((readl(ivp_cae_base_addr+0x0000c008)&0x000000ff)==(0x000000ff&0x000000ff))
cnt++;
else
printf("cnt: 1318\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000c00c);
if((readl(ivp_cae_base_addr+0x0000c00c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1319\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000c00c);
if((readl(ivp_cae_base_addr+0x0000c00c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1320\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000c00c);
if((readl(ivp_cae_base_addr+0x0000c00c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1321\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000c00c);
if((readl(ivp_cae_base_addr+0x0000c00c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1322\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000c00c);
if((readl(ivp_cae_base_addr+0x0000c00c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1323\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000c00c);
if((readl(ivp_cae_base_addr+0x0000c00c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1324\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000c010);
if((readl(ivp_cae_base_addr+0x0000c010)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1325\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000c010);
if((readl(ivp_cae_base_addr+0x0000c010)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1326\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000c010);
if((readl(ivp_cae_base_addr+0x0000c010)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1327\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000c010);
if((readl(ivp_cae_base_addr+0x0000c010)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1328\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000c010);
if((readl(ivp_cae_base_addr+0x0000c010)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1329\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000c010);
if((readl(ivp_cae_base_addr+0x0000c010)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1330\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000c014);
if((readl(ivp_cae_base_addr+0x0000c014)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1331\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000c014);
if((readl(ivp_cae_base_addr+0x0000c014)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1332\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000c014);
if((readl(ivp_cae_base_addr+0x0000c014)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1333\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000c014);
if((readl(ivp_cae_base_addr+0x0000c014)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1334\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000c014);
if((readl(ivp_cae_base_addr+0x0000c014)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1335\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000c014);
if((readl(ivp_cae_base_addr+0x0000c014)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1336\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000c018);
if((readl(ivp_cae_base_addr+0x0000c018)&0x000001bf)==(0x00000008&0x000001bf))
cnt++;
else
printf("cnt: 1337\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000c018);
if((readl(ivp_cae_base_addr+0x0000c018)&0x000001bf)==(0x00000008&0x000001bf))
cnt++;
else
printf("cnt: 1338\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000c018);
if((readl(ivp_cae_base_addr+0x0000c018)&0x000001bf)==(0x00000008&0x000001bf))
cnt++;
else
printf("cnt: 1339\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000c018);
if((readl(ivp_cae_base_addr+0x0000c018)&0x000001bf)==(0x00000008&0x000001bf))
cnt++;
else
printf("cnt: 1340\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000c018);
if((readl(ivp_cae_base_addr+0x0000c018)&0x000001bf)==(0x00000008&0x000001bf))
cnt++;
else
printf("cnt: 1341\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000c018);
if((readl(ivp_cae_base_addr+0x0000c018)&0x000001bf)==(0x00000008&0x000001bf))
cnt++;
else
printf("cnt: 1342\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000c01c);
if((readl(ivp_cae_base_addr+0x0000c01c)&0x0fffffff)==(0x014036c9&0x0fffffff))
cnt++;
else
printf("cnt: 1343\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000c01c);
if((readl(ivp_cae_base_addr+0x0000c01c)&0x0fffffff)==(0x014036c9&0x0fffffff))
cnt++;
else
printf("cnt: 1344\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000c01c);
if((readl(ivp_cae_base_addr+0x0000c01c)&0x0fffffff)==(0x014036c9&0x0fffffff))
cnt++;
else
printf("cnt: 1345\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000c01c);
if((readl(ivp_cae_base_addr+0x0000c01c)&0x0fffffff)==(0x014036c9&0x0fffffff))
cnt++;
else
printf("cnt: 1346\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000c01c);
if((readl(ivp_cae_base_addr+0x0000c01c)&0x0fffffff)==(0x014036c9&0x0fffffff))
cnt++;
else
printf("cnt: 1347\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000c01c);
if((readl(ivp_cae_base_addr+0x0000c01c)&0x0fffffff)==(0x014036c9&0x0fffffff))
cnt++;
else
printf("cnt: 1348\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000d000);
if((readl(ivp_cae_base_addr+0x0000d000)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1349\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000d000);
if((readl(ivp_cae_base_addr+0x0000d000)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1350\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000d000);
if((readl(ivp_cae_base_addr+0x0000d000)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1351\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000d000);
if((readl(ivp_cae_base_addr+0x0000d000)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1352\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000d000);
if((readl(ivp_cae_base_addr+0x0000d000)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1353\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000d000);
if((readl(ivp_cae_base_addr+0x0000d000)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1354\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000d004);
if((readl(ivp_cae_base_addr+0x0000d004)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1355\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000d004);
if((readl(ivp_cae_base_addr+0x0000d004)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1356\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000d004);
if((readl(ivp_cae_base_addr+0x0000d004)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1357\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000d004);
if((readl(ivp_cae_base_addr+0x0000d004)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1358\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000d004);
if((readl(ivp_cae_base_addr+0x0000d004)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1359\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000d004);
if((readl(ivp_cae_base_addr+0x0000d004)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1360\n");
writel(0x00000011&0xffffffff,ivp_cae_base_addr+0x0000d008);
if((readl(ivp_cae_base_addr+0x0000d008)&0x000000ff)==(0x00000011&0x000000ff))
cnt++;
else
printf("cnt: 1361\n");
writel(0x00000022&0xffffffff,ivp_cae_base_addr+0x0000d008);
if((readl(ivp_cae_base_addr+0x0000d008)&0x000000ff)==(0x00000022&0x000000ff))
cnt++;
else
printf("cnt: 1362\n");
writel(0x00000044&0xffffffff,ivp_cae_base_addr+0x0000d008);
if((readl(ivp_cae_base_addr+0x0000d008)&0x000000ff)==(0x00000044&0x000000ff))
cnt++;
else
printf("cnt: 1363\n");
writel(0x00000088&0xffffffff,ivp_cae_base_addr+0x0000d008);
if((readl(ivp_cae_base_addr+0x0000d008)&0x000000ff)==(0x00000088&0x000000ff))
cnt++;
else
printf("cnt: 1364\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000d008);
if((readl(ivp_cae_base_addr+0x0000d008)&0x000000ff)==(0x00000000&0x000000ff))
cnt++;
else
printf("cnt: 1365\n");
writel(0x000000ff&0xffffffff,ivp_cae_base_addr+0x0000d008);
if((readl(ivp_cae_base_addr+0x0000d008)&0x000000ff)==(0x000000ff&0x000000ff))
cnt++;
else
printf("cnt: 1366\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000d00c);
if((readl(ivp_cae_base_addr+0x0000d00c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1367\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000d00c);
if((readl(ivp_cae_base_addr+0x0000d00c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1368\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000d00c);
if((readl(ivp_cae_base_addr+0x0000d00c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1369\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000d00c);
if((readl(ivp_cae_base_addr+0x0000d00c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1370\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000d00c);
if((readl(ivp_cae_base_addr+0x0000d00c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1371\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000d00c);
if((readl(ivp_cae_base_addr+0x0000d00c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1372\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000d010);
if((readl(ivp_cae_base_addr+0x0000d010)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1373\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000d010);
if((readl(ivp_cae_base_addr+0x0000d010)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1374\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000d010);
if((readl(ivp_cae_base_addr+0x0000d010)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1375\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000d010);
if((readl(ivp_cae_base_addr+0x0000d010)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1376\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000d010);
if((readl(ivp_cae_base_addr+0x0000d010)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1377\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000d010);
if((readl(ivp_cae_base_addr+0x0000d010)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1378\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000d014);
if((readl(ivp_cae_base_addr+0x0000d014)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1379\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000d014);
if((readl(ivp_cae_base_addr+0x0000d014)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1380\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000d014);
if((readl(ivp_cae_base_addr+0x0000d014)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1381\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000d014);
if((readl(ivp_cae_base_addr+0x0000d014)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1382\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000d014);
if((readl(ivp_cae_base_addr+0x0000d014)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1383\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000d014);
if((readl(ivp_cae_base_addr+0x0000d014)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1384\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000d018);
if((readl(ivp_cae_base_addr+0x0000d018)&0x000001bf)==(0x00000008&0x000001bf))
cnt++;
else
printf("cnt: 1385\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000d018);
if((readl(ivp_cae_base_addr+0x0000d018)&0x000001bf)==(0x00000008&0x000001bf))
cnt++;
else
printf("cnt: 1386\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000d018);
if((readl(ivp_cae_base_addr+0x0000d018)&0x000001bf)==(0x00000008&0x000001bf))
cnt++;
else
printf("cnt: 1387\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000d018);
if((readl(ivp_cae_base_addr+0x0000d018)&0x000001bf)==(0x00000008&0x000001bf))
cnt++;
else
printf("cnt: 1388\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000d018);
if((readl(ivp_cae_base_addr+0x0000d018)&0x000001bf)==(0x00000008&0x000001bf))
cnt++;
else
printf("cnt: 1389\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000d018);
if((readl(ivp_cae_base_addr+0x0000d018)&0x000001bf)==(0x00000008&0x000001bf))
cnt++;
else
printf("cnt: 1390\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000d01c);
if((readl(ivp_cae_base_addr+0x0000d01c)&0x0fffffff)==(0x014036c9&0x0fffffff))
cnt++;
else
printf("cnt: 1391\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000d01c);
if((readl(ivp_cae_base_addr+0x0000d01c)&0x0fffffff)==(0x014036c9&0x0fffffff))
cnt++;
else
printf("cnt: 1392\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000d01c);
if((readl(ivp_cae_base_addr+0x0000d01c)&0x0fffffff)==(0x014036c9&0x0fffffff))
cnt++;
else
printf("cnt: 1393\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000d01c);
if((readl(ivp_cae_base_addr+0x0000d01c)&0x0fffffff)==(0x014036c9&0x0fffffff))
cnt++;
else
printf("cnt: 1394\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000d01c);
if((readl(ivp_cae_base_addr+0x0000d01c)&0x0fffffff)==(0x014036c9&0x0fffffff))
cnt++;
else
printf("cnt: 1395\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000d01c);
if((readl(ivp_cae_base_addr+0x0000d01c)&0x0fffffff)==(0x014036c9&0x0fffffff))
cnt++;
else
printf("cnt: 1396\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000e000);
if((readl(ivp_cae_base_addr+0x0000e000)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1397\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000e000);
if((readl(ivp_cae_base_addr+0x0000e000)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1398\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000e000);
if((readl(ivp_cae_base_addr+0x0000e000)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1399\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000e000);
if((readl(ivp_cae_base_addr+0x0000e000)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1400\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000e000);
if((readl(ivp_cae_base_addr+0x0000e000)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1401\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000e000);
if((readl(ivp_cae_base_addr+0x0000e000)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1402\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000e004);
if((readl(ivp_cae_base_addr+0x0000e004)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1403\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000e004);
if((readl(ivp_cae_base_addr+0x0000e004)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1404\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000e004);
if((readl(ivp_cae_base_addr+0x0000e004)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1405\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000e004);
if((readl(ivp_cae_base_addr+0x0000e004)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1406\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000e004);
if((readl(ivp_cae_base_addr+0x0000e004)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1407\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000e004);
if((readl(ivp_cae_base_addr+0x0000e004)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1408\n");
writel(0x00000011&0xffffffff,ivp_cae_base_addr+0x0000e008);
if((readl(ivp_cae_base_addr+0x0000e008)&0x000000ff)==(0x00000011&0x000000ff))
cnt++;
else
printf("cnt: 1409\n");
writel(0x00000022&0xffffffff,ivp_cae_base_addr+0x0000e008);
if((readl(ivp_cae_base_addr+0x0000e008)&0x000000ff)==(0x00000022&0x000000ff))
cnt++;
else
printf("cnt: 1410\n");
writel(0x00000044&0xffffffff,ivp_cae_base_addr+0x0000e008);
if((readl(ivp_cae_base_addr+0x0000e008)&0x000000ff)==(0x00000044&0x000000ff))
cnt++;
else
printf("cnt: 1411\n");
writel(0x00000088&0xffffffff,ivp_cae_base_addr+0x0000e008);
if((readl(ivp_cae_base_addr+0x0000e008)&0x000000ff)==(0x00000088&0x000000ff))
cnt++;
else
printf("cnt: 1412\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000e008);
if((readl(ivp_cae_base_addr+0x0000e008)&0x000000ff)==(0x00000000&0x000000ff))
cnt++;
else
printf("cnt: 1413\n");
writel(0x000000ff&0xffffffff,ivp_cae_base_addr+0x0000e008);
if((readl(ivp_cae_base_addr+0x0000e008)&0x000000ff)==(0x000000ff&0x000000ff))
cnt++;
else
printf("cnt: 1414\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000e00c);
if((readl(ivp_cae_base_addr+0x0000e00c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1415\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000e00c);
if((readl(ivp_cae_base_addr+0x0000e00c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1416\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000e00c);
if((readl(ivp_cae_base_addr+0x0000e00c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1417\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000e00c);
if((readl(ivp_cae_base_addr+0x0000e00c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1418\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000e00c);
if((readl(ivp_cae_base_addr+0x0000e00c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1419\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000e00c);
if((readl(ivp_cae_base_addr+0x0000e00c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1420\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000e010);
if((readl(ivp_cae_base_addr+0x0000e010)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1421\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000e010);
if((readl(ivp_cae_base_addr+0x0000e010)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1422\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000e010);
if((readl(ivp_cae_base_addr+0x0000e010)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1423\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000e010);
if((readl(ivp_cae_base_addr+0x0000e010)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1424\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000e010);
if((readl(ivp_cae_base_addr+0x0000e010)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1425\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000e010);
if((readl(ivp_cae_base_addr+0x0000e010)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1426\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000e014);
if((readl(ivp_cae_base_addr+0x0000e014)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1427\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000e014);
if((readl(ivp_cae_base_addr+0x0000e014)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1428\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000e014);
if((readl(ivp_cae_base_addr+0x0000e014)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1429\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000e014);
if((readl(ivp_cae_base_addr+0x0000e014)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1430\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000e014);
if((readl(ivp_cae_base_addr+0x0000e014)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1431\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000e014);
if((readl(ivp_cae_base_addr+0x0000e014)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1432\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000e018);
if((readl(ivp_cae_base_addr+0x0000e018)&0x000001bf)==(0x00000008&0x000001bf))
cnt++;
else
printf("cnt: 1433\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000e018);
if((readl(ivp_cae_base_addr+0x0000e018)&0x000001bf)==(0x00000008&0x000001bf))
cnt++;
else
printf("cnt: 1434\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000e018);
if((readl(ivp_cae_base_addr+0x0000e018)&0x000001bf)==(0x00000008&0x000001bf))
cnt++;
else
printf("cnt: 1435\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000e018);
if((readl(ivp_cae_base_addr+0x0000e018)&0x000001bf)==(0x00000008&0x000001bf))
cnt++;
else
printf("cnt: 1436\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000e018);
if((readl(ivp_cae_base_addr+0x0000e018)&0x000001bf)==(0x00000008&0x000001bf))
cnt++;
else
printf("cnt: 1437\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000e018);
if((readl(ivp_cae_base_addr+0x0000e018)&0x000001bf)==(0x00000008&0x000001bf))
cnt++;
else
printf("cnt: 1438\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000e01c);
if((readl(ivp_cae_base_addr+0x0000e01c)&0x0fffffff)==(0x014036c9&0x0fffffff))
cnt++;
else
printf("cnt: 1439\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000e01c);
if((readl(ivp_cae_base_addr+0x0000e01c)&0x0fffffff)==(0x014036c9&0x0fffffff))
cnt++;
else
printf("cnt: 1440\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000e01c);
if((readl(ivp_cae_base_addr+0x0000e01c)&0x0fffffff)==(0x014036c9&0x0fffffff))
cnt++;
else
printf("cnt: 1441\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000e01c);
if((readl(ivp_cae_base_addr+0x0000e01c)&0x0fffffff)==(0x014036c9&0x0fffffff))
cnt++;
else
printf("cnt: 1442\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000e01c);
if((readl(ivp_cae_base_addr+0x0000e01c)&0x0fffffff)==(0x014036c9&0x0fffffff))
cnt++;
else
printf("cnt: 1443\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000e01c);
if((readl(ivp_cae_base_addr+0x0000e01c)&0x0fffffff)==(0x014036c9&0x0fffffff))
cnt++;
else
printf("cnt: 1444\n");
writel(0x01110111&0xffffffff,ivp_cae_base_addr+0x0000f000);
if((readl(ivp_cae_base_addr+0x0000f000)&0xefff0fff)==(0x01110111&0xefff0fff))
cnt++;
else
printf("cnt: 1445\n");
writel(0x22220222&0xffffffff,ivp_cae_base_addr+0x0000f000);
if((readl(ivp_cae_base_addr+0x0000f000)&0xefff0fff)==(0x22220222&0xefff0fff))
cnt++;
else
printf("cnt: 1446\n");
writel(0x44440444&0xffffffff,ivp_cae_base_addr+0x0000f000);
if((readl(ivp_cae_base_addr+0x0000f000)&0xefff0fff)==(0x44440444&0xefff0fff))
cnt++;
else
printf("cnt: 1447\n");
writel(0x88880888&0xffffffff,ivp_cae_base_addr+0x0000f000);
if((readl(ivp_cae_base_addr+0x0000f000)&0xefff0fff)==(0x88880888&0xefff0fff))
cnt++;
else
printf("cnt: 1448\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f000);
if((readl(ivp_cae_base_addr+0x0000f000)&0xefff0fff)==(0x00000000&0xefff0fff))
cnt++;
else
printf("cnt: 1449\n");
writel(0xefff0fff&0xffffffff,ivp_cae_base_addr+0x0000f000);
if((readl(ivp_cae_base_addr+0x0000f000)&0xefff0fff)==(0xefff0fff&0xefff0fff))
cnt++;
else
printf("cnt: 1450\n");
writel(0x01010101&0xffffffff,ivp_cae_base_addr+0x0000f010);
if((readl(ivp_cae_base_addr+0x0000f010)&0x8f8f8f8f)==(0x01010101&0x8f8f8f8f))
cnt++;
else
printf("cnt: 1451\n");
writel(0x02020202&0xffffffff,ivp_cae_base_addr+0x0000f010);
if((readl(ivp_cae_base_addr+0x0000f010)&0x8f8f8f8f)==(0x02020202&0x8f8f8f8f))
cnt++;
else
printf("cnt: 1452\n");
writel(0x04040404&0xffffffff,ivp_cae_base_addr+0x0000f010);
if((readl(ivp_cae_base_addr+0x0000f010)&0x8f8f8f8f)==(0x04040404&0x8f8f8f8f))
cnt++;
else
printf("cnt: 1453\n");
writel(0x88888888&0xffffffff,ivp_cae_base_addr+0x0000f010);
if((readl(ivp_cae_base_addr+0x0000f010)&0x8f8f8f8f)==(0x88888888&0x8f8f8f8f))
cnt++;
else
printf("cnt: 1454\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f010);
if((readl(ivp_cae_base_addr+0x0000f010)&0x8f8f8f8f)==(0x00000000&0x8f8f8f8f))
cnt++;
else
printf("cnt: 1455\n");
writel(0x8f8f8f8f&0xffffffff,ivp_cae_base_addr+0x0000f010);
if((readl(ivp_cae_base_addr+0x0000f010)&0x8f8f8f8f)==(0x8f8f8f8f&0x8f8f8f8f))
cnt++;
else
printf("cnt: 1456\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f078);
if((readl(ivp_cae_base_addr+0x0000f078)&0xb7ffffff)==(0x80a35514&0xb7ffffff))
cnt++;
else
printf("cnt: 1457\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f078);
if((readl(ivp_cae_base_addr+0x0000f078)&0xb7ffffff)==(0x80a35514&0xb7ffffff))
cnt++;
else
printf("cnt: 1458\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f078);
if((readl(ivp_cae_base_addr+0x0000f078)&0xb7ffffff)==(0x80a35514&0xb7ffffff))
cnt++;
else
printf("cnt: 1459\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f078);
if((readl(ivp_cae_base_addr+0x0000f078)&0xb7ffffff)==(0x80a35514&0xb7ffffff))
cnt++;
else
printf("cnt: 1460\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f078);
if((readl(ivp_cae_base_addr+0x0000f078)&0xb7ffffff)==(0x80a35514&0xb7ffffff))
cnt++;
else
printf("cnt: 1461\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f078);
if((readl(ivp_cae_base_addr+0x0000f078)&0xb7ffffff)==(0x80a35514&0xb7ffffff))
cnt++;
else
printf("cnt: 1462\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f07c);
if((readl(ivp_cae_base_addr+0x0000f07c)&0x0fffffff)==(0x027035ca&0x0fffffff))
cnt++;
else
printf("cnt: 1463\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f07c);
if((readl(ivp_cae_base_addr+0x0000f07c)&0x0fffffff)==(0x027035ca&0x0fffffff))
cnt++;
else
printf("cnt: 1464\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f07c);
if((readl(ivp_cae_base_addr+0x0000f07c)&0x0fffffff)==(0x027035ca&0x0fffffff))
cnt++;
else
printf("cnt: 1465\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f07c);
if((readl(ivp_cae_base_addr+0x0000f07c)&0x0fffffff)==(0x027035ca&0x0fffffff))
cnt++;
else
printf("cnt: 1466\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f07c);
if((readl(ivp_cae_base_addr+0x0000f07c)&0x0fffffff)==(0x027035ca&0x0fffffff))
cnt++;
else
printf("cnt: 1467\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f07c);
if((readl(ivp_cae_base_addr+0x0000f07c)&0x0fffffff)==(0x027035ca&0x0fffffff))
cnt++;
else
printf("cnt: 1468\n");
writel(0x00000001&0xffffffff,ivp_cae_base_addr+0x0000f200);
if((readl(ivp_cae_base_addr+0x0000f200)&0x0000000f)==(0x00000001&0x0000000f))
cnt++;
else
printf("cnt: 1469\n");
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000f200);
if((readl(ivp_cae_base_addr+0x0000f200)&0x0000000f)==(0x00000002&0x0000000f))
cnt++;
else
printf("cnt: 1470\n");
writel(0x00000004&0xffffffff,ivp_cae_base_addr+0x0000f200);
if((readl(ivp_cae_base_addr+0x0000f200)&0x0000000f)==(0x00000004&0x0000000f))
cnt++;
else
printf("cnt: 1471\n");
writel(0x00000008&0xffffffff,ivp_cae_base_addr+0x0000f200);
if((readl(ivp_cae_base_addr+0x0000f200)&0x0000000f)==(0x00000008&0x0000000f))
cnt++;
else
printf("cnt: 1472\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f200);
if((readl(ivp_cae_base_addr+0x0000f200)&0x0000000f)==(0x00000000&0x0000000f))
cnt++;
else
printf("cnt: 1473\n");
writel(0x0000000f&0xffffffff,ivp_cae_base_addr+0x0000f200);
if((readl(ivp_cae_base_addr+0x0000f200)&0x0000000f)==(0x0000000f&0x0000000f))
cnt++;
else
printf("cnt: 1474\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f204);
if((readl(ivp_cae_base_addr+0x0000f204)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1475\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f204);
if((readl(ivp_cae_base_addr+0x0000f204)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1476\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f204);
if((readl(ivp_cae_base_addr+0x0000f204)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1477\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f204);
if((readl(ivp_cae_base_addr+0x0000f204)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1478\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f204);
if((readl(ivp_cae_base_addr+0x0000f204)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1479\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f204);
if((readl(ivp_cae_base_addr+0x0000f204)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1480\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f208);
if((readl(ivp_cae_base_addr+0x0000f208)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1481\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f208);
if((readl(ivp_cae_base_addr+0x0000f208)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1482\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f208);
if((readl(ivp_cae_base_addr+0x0000f208)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1483\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f208);
if((readl(ivp_cae_base_addr+0x0000f208)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1484\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f208);
if((readl(ivp_cae_base_addr+0x0000f208)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1485\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f208);
if((readl(ivp_cae_base_addr+0x0000f208)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1486\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f210);
if((readl(ivp_cae_base_addr+0x0000f210)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1487\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f210);
if((readl(ivp_cae_base_addr+0x0000f210)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1488\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f210);
if((readl(ivp_cae_base_addr+0x0000f210)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1489\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f210);
if((readl(ivp_cae_base_addr+0x0000f210)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1490\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f210);
if((readl(ivp_cae_base_addr+0x0000f210)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1491\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f210);
if((readl(ivp_cae_base_addr+0x0000f210)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1492\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f214);
if((readl(ivp_cae_base_addr+0x0000f214)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1493\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f214);
if((readl(ivp_cae_base_addr+0x0000f214)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1494\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f214);
if((readl(ivp_cae_base_addr+0x0000f214)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1495\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f214);
if((readl(ivp_cae_base_addr+0x0000f214)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1496\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f214);
if((readl(ivp_cae_base_addr+0x0000f214)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1497\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f214);
if((readl(ivp_cae_base_addr+0x0000f214)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1498\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f218);
if((readl(ivp_cae_base_addr+0x0000f218)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1499\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f218);
if((readl(ivp_cae_base_addr+0x0000f218)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1500\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f218);
if((readl(ivp_cae_base_addr+0x0000f218)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1501\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f218);
if((readl(ivp_cae_base_addr+0x0000f218)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1502\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f218);
if((readl(ivp_cae_base_addr+0x0000f218)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1503\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f218);
if((readl(ivp_cae_base_addr+0x0000f218)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1504\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f21c);
if((readl(ivp_cae_base_addr+0x0000f21c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1505\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f21c);
if((readl(ivp_cae_base_addr+0x0000f21c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1506\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f21c);
if((readl(ivp_cae_base_addr+0x0000f21c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1507\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f21c);
if((readl(ivp_cae_base_addr+0x0000f21c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1508\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f21c);
if((readl(ivp_cae_base_addr+0x0000f21c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1509\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f21c);
if((readl(ivp_cae_base_addr+0x0000f21c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1510\n");
writel(0x10001111&0xffffffff,ivp_cae_base_addr+0x0000f400);
if((readl(ivp_cae_base_addr+0x0000f400)&0xf000dfff)==(0x10001111&0xf000dfff))
cnt++;
else
printf("cnt: 1511\n");
writel(0x20000222&0xffffffff,ivp_cae_base_addr+0x0000f400);
if((readl(ivp_cae_base_addr+0x0000f400)&0xf000dfff)==(0x20000222&0xf000dfff))
cnt++;
else
printf("cnt: 1512\n");
writel(0x40004444&0xffffffff,ivp_cae_base_addr+0x0000f400);
if((readl(ivp_cae_base_addr+0x0000f400)&0xf000dfff)==(0x40004444&0xf000dfff))
cnt++;
else
printf("cnt: 1513\n");
writel(0x80008888&0xffffffff,ivp_cae_base_addr+0x0000f400);
if((readl(ivp_cae_base_addr+0x0000f400)&0xf000dfff)==(0x80008888&0xf000dfff))
cnt++;
else
printf("cnt: 1514\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f400);
if((readl(ivp_cae_base_addr+0x0000f400)&0xf000dfff)==(0x00000000&0xf000dfff))
cnt++;
else
printf("cnt: 1515\n");
writel(0xf000dfff&0xffffffff,ivp_cae_base_addr+0x0000f400);
if((readl(ivp_cae_base_addr+0x0000f400)&0xf000dfff)==(0xf000dfff&0xf000dfff))
cnt++;
else
printf("cnt: 1516\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f478);
if((readl(ivp_cae_base_addr+0x0000f478)&0xb7ffffff)==(0x80a35514&0xb7ffffff))
cnt++;
else
printf("cnt: 1517\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f478);
if((readl(ivp_cae_base_addr+0x0000f478)&0xb7ffffff)==(0x80a35514&0xb7ffffff))
cnt++;
else
printf("cnt: 1518\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f478);
if((readl(ivp_cae_base_addr+0x0000f478)&0xb7ffffff)==(0x80a35514&0xb7ffffff))
cnt++;
else
printf("cnt: 1519\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f478);
if((readl(ivp_cae_base_addr+0x0000f478)&0xb7ffffff)==(0x80a35514&0xb7ffffff))
cnt++;
else
printf("cnt: 1520\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f478);
if((readl(ivp_cae_base_addr+0x0000f478)&0xb7ffffff)==(0x80a35514&0xb7ffffff))
cnt++;
else
printf("cnt: 1521\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f478);
if((readl(ivp_cae_base_addr+0x0000f478)&0xb7ffffff)==(0x80a35514&0xb7ffffff))
cnt++;
else
printf("cnt: 1522\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f47c);
if((readl(ivp_cae_base_addr+0x0000f47c)&0x0fffffff)==(0x027035ca&0x0fffffff))
cnt++;
else
printf("cnt: 1523\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f47c);
if((readl(ivp_cae_base_addr+0x0000f47c)&0x0fffffff)==(0x027035ca&0x0fffffff))
cnt++;
else
printf("cnt: 1524\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f47c);
if((readl(ivp_cae_base_addr+0x0000f47c)&0x0fffffff)==(0x027035ca&0x0fffffff))
cnt++;
else
printf("cnt: 1525\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f47c);
if((readl(ivp_cae_base_addr+0x0000f47c)&0x0fffffff)==(0x027035ca&0x0fffffff))
cnt++;
else
printf("cnt: 1526\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f47c);
if((readl(ivp_cae_base_addr+0x0000f47c)&0x0fffffff)==(0x027035ca&0x0fffffff))
cnt++;
else
printf("cnt: 1527\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f47c);
if((readl(ivp_cae_base_addr+0x0000f47c)&0x0fffffff)==(0x027035ca&0x0fffffff))
cnt++;
else
printf("cnt: 1528\n");
writel(0x00000001&0xffffffff,ivp_cae_base_addr+0x0000f600);
if((readl(ivp_cae_base_addr+0x0000f600)&0x0000000f)==(0x00000001&0x0000000f))
cnt++;
else
printf("cnt: 1529\n");
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000f600);
if((readl(ivp_cae_base_addr+0x0000f600)&0x0000000f)==(0x00000002&0x0000000f))
cnt++;
else
printf("cnt: 1530\n");
writel(0x00000004&0xffffffff,ivp_cae_base_addr+0x0000f600);
if((readl(ivp_cae_base_addr+0x0000f600)&0x0000000f)==(0x00000004&0x0000000f))
cnt++;
else
printf("cnt: 1531\n");
writel(0x00000008&0xffffffff,ivp_cae_base_addr+0x0000f600);
if((readl(ivp_cae_base_addr+0x0000f600)&0x0000000f)==(0x00000008&0x0000000f))
cnt++;
else
printf("cnt: 1532\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f600);
if((readl(ivp_cae_base_addr+0x0000f600)&0x0000000f)==(0x00000000&0x0000000f))
cnt++;
else
printf("cnt: 1533\n");
writel(0x0000000f&0xffffffff,ivp_cae_base_addr+0x0000f600);
if((readl(ivp_cae_base_addr+0x0000f600)&0x0000000f)==(0x0000000f&0x0000000f))
cnt++;
else
printf("cnt: 1534\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f604);
if((readl(ivp_cae_base_addr+0x0000f604)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1535\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f604);
if((readl(ivp_cae_base_addr+0x0000f604)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1536\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f604);
if((readl(ivp_cae_base_addr+0x0000f604)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1537\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f604);
if((readl(ivp_cae_base_addr+0x0000f604)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1538\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f604);
if((readl(ivp_cae_base_addr+0x0000f604)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1539\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f604);
if((readl(ivp_cae_base_addr+0x0000f604)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1540\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f608);
if((readl(ivp_cae_base_addr+0x0000f608)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1541\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f608);
if((readl(ivp_cae_base_addr+0x0000f608)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1542\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f608);
if((readl(ivp_cae_base_addr+0x0000f608)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1543\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f608);
if((readl(ivp_cae_base_addr+0x0000f608)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1544\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f608);
if((readl(ivp_cae_base_addr+0x0000f608)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1545\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f608);
if((readl(ivp_cae_base_addr+0x0000f608)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1546\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f60c);
if((readl(ivp_cae_base_addr+0x0000f60c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1547\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f60c);
if((readl(ivp_cae_base_addr+0x0000f60c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1548\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f60c);
if((readl(ivp_cae_base_addr+0x0000f60c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1549\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f60c);
if((readl(ivp_cae_base_addr+0x0000f60c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1550\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f60c);
if((readl(ivp_cae_base_addr+0x0000f60c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1551\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f60c);
if((readl(ivp_cae_base_addr+0x0000f60c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1552\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f610);
if((readl(ivp_cae_base_addr+0x0000f610)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1553\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f610);
if((readl(ivp_cae_base_addr+0x0000f610)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1554\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f610);
if((readl(ivp_cae_base_addr+0x0000f610)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1555\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f610);
if((readl(ivp_cae_base_addr+0x0000f610)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1556\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f610);
if((readl(ivp_cae_base_addr+0x0000f610)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1557\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f610);
if((readl(ivp_cae_base_addr+0x0000f610)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1558\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f614);
if((readl(ivp_cae_base_addr+0x0000f614)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1559\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f614);
if((readl(ivp_cae_base_addr+0x0000f614)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1560\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f614);
if((readl(ivp_cae_base_addr+0x0000f614)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1561\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f614);
if((readl(ivp_cae_base_addr+0x0000f614)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1562\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f614);
if((readl(ivp_cae_base_addr+0x0000f614)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1563\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f614);
if((readl(ivp_cae_base_addr+0x0000f614)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1564\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f618);
if((readl(ivp_cae_base_addr+0x0000f618)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1565\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f618);
if((readl(ivp_cae_base_addr+0x0000f618)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1566\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f618);
if((readl(ivp_cae_base_addr+0x0000f618)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1567\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f618);
if((readl(ivp_cae_base_addr+0x0000f618)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1568\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f618);
if((readl(ivp_cae_base_addr+0x0000f618)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1569\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f618);
if((readl(ivp_cae_base_addr+0x0000f618)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1570\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f61c);
if((readl(ivp_cae_base_addr+0x0000f61c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1571\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f61c);
if((readl(ivp_cae_base_addr+0x0000f61c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1572\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f61c);
if((readl(ivp_cae_base_addr+0x0000f61c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1573\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f61c);
if((readl(ivp_cae_base_addr+0x0000f61c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1574\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f61c);
if((readl(ivp_cae_base_addr+0x0000f61c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1575\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f61c);
if((readl(ivp_cae_base_addr+0x0000f61c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1576\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f620);
if((readl(ivp_cae_base_addr+0x0000f620)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1577\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f620);
if((readl(ivp_cae_base_addr+0x0000f620)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1578\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f620);
if((readl(ivp_cae_base_addr+0x0000f620)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1579\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f620);
if((readl(ivp_cae_base_addr+0x0000f620)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1580\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f620);
if((readl(ivp_cae_base_addr+0x0000f620)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1581\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f620);
if((readl(ivp_cae_base_addr+0x0000f620)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1582\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f628);
if((readl(ivp_cae_base_addr+0x0000f628)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1583\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f628);
if((readl(ivp_cae_base_addr+0x0000f628)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1584\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f628);
if((readl(ivp_cae_base_addr+0x0000f628)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1585\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f628);
if((readl(ivp_cae_base_addr+0x0000f628)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1586\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f628);
if((readl(ivp_cae_base_addr+0x0000f628)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1587\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f628);
if((readl(ivp_cae_base_addr+0x0000f628)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1588\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f62c);
if((readl(ivp_cae_base_addr+0x0000f62c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1589\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f62c);
if((readl(ivp_cae_base_addr+0x0000f62c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1590\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f62c);
if((readl(ivp_cae_base_addr+0x0000f62c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1591\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f62c);
if((readl(ivp_cae_base_addr+0x0000f62c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1592\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f62c);
if((readl(ivp_cae_base_addr+0x0000f62c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1593\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f62c);
if((readl(ivp_cae_base_addr+0x0000f62c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1594\n");
writel(0x11100000&0xffffffff,ivp_cae_base_addr+0x0000f800);
if((readl(ivp_cae_base_addr+0x0000f800)&0xfff00000)==(0x11100000&0xfff00000))
cnt++;
else
printf("cnt: 1595\n");
writel(0x22200000&0xffffffff,ivp_cae_base_addr+0x0000f800);
if((readl(ivp_cae_base_addr+0x0000f800)&0xfff00000)==(0x22200000&0xfff00000))
cnt++;
else
printf("cnt: 1596\n");
writel(0x44400000&0xffffffff,ivp_cae_base_addr+0x0000f800);
if((readl(ivp_cae_base_addr+0x0000f800)&0xfff00000)==(0x44400000&0xfff00000))
cnt++;
else
printf("cnt: 1597\n");
writel(0x88800000&0xffffffff,ivp_cae_base_addr+0x0000f800);
if((readl(ivp_cae_base_addr+0x0000f800)&0xfff00000)==(0x88800000&0xfff00000))
cnt++;
else
printf("cnt: 1598\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f800);
if((readl(ivp_cae_base_addr+0x0000f800)&0xfff00000)==(0x00000000&0xfff00000))
cnt++;
else
printf("cnt: 1599\n");
writel(0xfff00000&0xffffffff,ivp_cae_base_addr+0x0000f800);
if((readl(ivp_cae_base_addr+0x0000f800)&0xfff00000)==(0xfff00000&0xfff00000))
cnt++;
else
printf("cnt: 1600\n");
writel(0x11100000&0xffffffff,ivp_cae_base_addr+0x0000f804);
if((readl(ivp_cae_base_addr+0x0000f804)&0xfff00000)==(0x11100000&0xfff00000))
cnt++;
else
printf("cnt: 1601\n");
writel(0x22200000&0xffffffff,ivp_cae_base_addr+0x0000f804);
if((readl(ivp_cae_base_addr+0x0000f804)&0xfff00000)==(0x22200000&0xfff00000))
cnt++;
else
printf("cnt: 1602\n");
writel(0x44400000&0xffffffff,ivp_cae_base_addr+0x0000f804);
if((readl(ivp_cae_base_addr+0x0000f804)&0xfff00000)==(0x44400000&0xfff00000))
cnt++;
else
printf("cnt: 1603\n");
writel(0x88800000&0xffffffff,ivp_cae_base_addr+0x0000f804);
if((readl(ivp_cae_base_addr+0x0000f804)&0xfff00000)==(0x88800000&0xfff00000))
cnt++;
else
printf("cnt: 1604\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f804);
if((readl(ivp_cae_base_addr+0x0000f804)&0xfff00000)==(0x00000000&0xfff00000))
cnt++;
else
printf("cnt: 1605\n");
writel(0xfff00000&0xffffffff,ivp_cae_base_addr+0x0000f804);
if((readl(ivp_cae_base_addr+0x0000f804)&0xfff00000)==(0xfff00000&0xfff00000))
cnt++;
else
printf("cnt: 1606\n");
writel(0x11111111&0xffffffff,ivp_cae_base_addr+0x0000f808);
if((readl(ivp_cae_base_addr+0x0000f808)&0xffffffff)==(0x11111111&0xffffffff))
cnt++;
else
printf("cnt: 1607\n");
writel(0x22222222&0xffffffff,ivp_cae_base_addr+0x0000f808);
if((readl(ivp_cae_base_addr+0x0000f808)&0xffffffff)==(0x22222222&0xffffffff))
cnt++;
else
printf("cnt: 1608\n");
writel(0x44444444&0xffffffff,ivp_cae_base_addr+0x0000f808);
if((readl(ivp_cae_base_addr+0x0000f808)&0xffffffff)==(0x44444444&0xffffffff))
cnt++;
else
printf("cnt: 1609\n");
writel(0x88888888&0xffffffff,ivp_cae_base_addr+0x0000f808);
if((readl(ivp_cae_base_addr+0x0000f808)&0xffffffff)==(0x88888888&0xffffffff))
cnt++;
else
printf("cnt: 1610\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f808);
if((readl(ivp_cae_base_addr+0x0000f808)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 1611\n");
writel(0xffffffff&0xffffffff,ivp_cae_base_addr+0x0000f808);
if((readl(ivp_cae_base_addr+0x0000f808)&0xffffffff)==(0xffffffff&0xffffffff))
cnt++;
else
printf("cnt: 1612\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f80c);
if((readl(ivp_cae_base_addr+0x0000f80c)&0x00000000)==(0x40000000&0x00000000))
cnt++;
else
printf("cnt: 1613\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f80c);
if((readl(ivp_cae_base_addr+0x0000f80c)&0x00000000)==(0x40000000&0x00000000))
cnt++;
else
printf("cnt: 1614\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f80c);
if((readl(ivp_cae_base_addr+0x0000f80c)&0x00000000)==(0x40000000&0x00000000))
cnt++;
else
printf("cnt: 1615\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f80c);
if((readl(ivp_cae_base_addr+0x0000f80c)&0x00000000)==(0x40000000&0x00000000))
cnt++;
else
printf("cnt: 1616\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f80c);
if((readl(ivp_cae_base_addr+0x0000f80c)&0x00000000)==(0x40000000&0x00000000))
cnt++;
else
printf("cnt: 1617\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f80c);
if((readl(ivp_cae_base_addr+0x0000f80c)&0x00000000)==(0x40000000&0x00000000))
cnt++;
else
printf("cnt: 1618\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f810);
if((readl(ivp_cae_base_addr+0x0000f810)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1619\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f810);
if((readl(ivp_cae_base_addr+0x0000f810)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1620\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f810);
if((readl(ivp_cae_base_addr+0x0000f810)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1621\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f810);
if((readl(ivp_cae_base_addr+0x0000f810)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1622\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f810);
if((readl(ivp_cae_base_addr+0x0000f810)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1623\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f810);
if((readl(ivp_cae_base_addr+0x0000f810)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1624\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f814);
if((readl(ivp_cae_base_addr+0x0000f814)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1625\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f814);
if((readl(ivp_cae_base_addr+0x0000f814)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1626\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f814);
if((readl(ivp_cae_base_addr+0x0000f814)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1627\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f814);
if((readl(ivp_cae_base_addr+0x0000f814)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1628\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f814);
if((readl(ivp_cae_base_addr+0x0000f814)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1629\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f814);
if((readl(ivp_cae_base_addr+0x0000f814)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1630\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f818);
if((readl(ivp_cae_base_addr+0x0000f818)&0x000001bf)==(0x00000020&0x000001bf))
cnt++;
else
printf("cnt: 1631\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f818);
if((readl(ivp_cae_base_addr+0x0000f818)&0x000001bf)==(0x00000020&0x000001bf))
cnt++;
else
printf("cnt: 1632\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f818);
if((readl(ivp_cae_base_addr+0x0000f818)&0x000001bf)==(0x00000020&0x000001bf))
cnt++;
else
printf("cnt: 1633\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f818);
if((readl(ivp_cae_base_addr+0x0000f818)&0x000001bf)==(0x00000020&0x000001bf))
cnt++;
else
printf("cnt: 1634\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f818);
if((readl(ivp_cae_base_addr+0x0000f818)&0x000001bf)==(0x00000020&0x000001bf))
cnt++;
else
printf("cnt: 1635\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f818);
if((readl(ivp_cae_base_addr+0x0000f818)&0x000001bf)==(0x00000020&0x000001bf))
cnt++;
else
printf("cnt: 1636\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f81c);
if((readl(ivp_cae_base_addr+0x0000f81c)&0x0fffffff)==(0x014036c9&0x0fffffff))
cnt++;
else
printf("cnt: 1637\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f81c);
if((readl(ivp_cae_base_addr+0x0000f81c)&0x0fffffff)==(0x014036c9&0x0fffffff))
cnt++;
else
printf("cnt: 1638\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f81c);
if((readl(ivp_cae_base_addr+0x0000f81c)&0x0fffffff)==(0x014036c9&0x0fffffff))
cnt++;
else
printf("cnt: 1639\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f81c);
if((readl(ivp_cae_base_addr+0x0000f81c)&0x0fffffff)==(0x014036c9&0x0fffffff))
cnt++;
else
printf("cnt: 1640\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f81c);
if((readl(ivp_cae_base_addr+0x0000f81c)&0x0fffffff)==(0x014036c9&0x0fffffff))
cnt++;
else
printf("cnt: 1641\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f81c);
if((readl(ivp_cae_base_addr+0x0000f81c)&0x0fffffff)==(0x014036c9&0x0fffffff))
cnt++;
else
printf("cnt: 1642\n");
writel(0x00111111&0xffffffff,ivp_cae_base_addr+0x0000fff4);
if((readl(ivp_cae_base_addr+0x0000fff4)&0x00ff9ff1)==(0x00111111&0x00ff9ff1))
cnt++;
else
printf("cnt: 1643\n");
writel(0x00220220&0xffffffff,ivp_cae_base_addr+0x0000fff4);
if((readl(ivp_cae_base_addr+0x0000fff4)&0x00ff9ff1)==(0x00220220&0x00ff9ff1))
cnt++;
else
printf("cnt: 1644\n");
writel(0x00440440&0xffffffff,ivp_cae_base_addr+0x0000fff4);
if((readl(ivp_cae_base_addr+0x0000fff4)&0x00ff9ff1)==(0x00440440&0x00ff9ff1))
cnt++;
else
printf("cnt: 1645\n");
writel(0x00888880&0xffffffff,ivp_cae_base_addr+0x0000fff4);
if((readl(ivp_cae_base_addr+0x0000fff4)&0x00ff9ff1)==(0x00888880&0x00ff9ff1))
cnt++;
else
printf("cnt: 1646\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000fff4);
if((readl(ivp_cae_base_addr+0x0000fff4)&0x00ff9ff1)==(0x00000000&0x00ff9ff1))
cnt++;
else
printf("cnt: 1647\n");
writel(0x00ff9ff1&0xffffffff,ivp_cae_base_addr+0x0000fff4);
if((readl(ivp_cae_base_addr+0x0000fff4)&0x00ff9ff1)==(0x00ff9ff1&0x00ff9ff1))
cnt++;
else
printf("cnt: 1648\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000fff8);
if((readl(ivp_cae_base_addr+0x0000fff8)&0xb7ffffff)==(0x80a35514&0xb7ffffff))
cnt++;
else
printf("cnt: 1649\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000fff8);
if((readl(ivp_cae_base_addr+0x0000fff8)&0xb7ffffff)==(0x80a35514&0xb7ffffff))
cnt++;
else
printf("cnt: 1650\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000fff8);
if((readl(ivp_cae_base_addr+0x0000fff8)&0xb7ffffff)==(0x80a35514&0xb7ffffff))
cnt++;
else
printf("cnt: 1651\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000fff8);
if((readl(ivp_cae_base_addr+0x0000fff8)&0xb7ffffff)==(0x80a35514&0xb7ffffff))
cnt++;
else
printf("cnt: 1652\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000fff8);
if((readl(ivp_cae_base_addr+0x0000fff8)&0xb7ffffff)==(0x80a35514&0xb7ffffff))
cnt++;
else
printf("cnt: 1653\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000fff8);
if((readl(ivp_cae_base_addr+0x0000fff8)&0xb7ffffff)==(0x80a35514&0xb7ffffff))
cnt++;
else
printf("cnt: 1654\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000fffc);
if((readl(ivp_cae_base_addr+0x0000fffc)&0x0fffffff)==(0x027035ca&0x0fffffff))
cnt++;
else
printf("cnt: 1655\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000fffc);
if((readl(ivp_cae_base_addr+0x0000fffc)&0x0fffffff)==(0x027035ca&0x0fffffff))
cnt++;
else
printf("cnt: 1656\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000fffc);
if((readl(ivp_cae_base_addr+0x0000fffc)&0x0fffffff)==(0x027035ca&0x0fffffff))
cnt++;
else
printf("cnt: 1657\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000fffc);
if((readl(ivp_cae_base_addr+0x0000fffc)&0x0fffffff)==(0x027035ca&0x0fffffff))
cnt++;
else
printf("cnt: 1658\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000fffc);
if((readl(ivp_cae_base_addr+0x0000fffc)&0x0fffffff)==(0x027035ca&0x0fffffff))
cnt++;
else
printf("cnt: 1659\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000fffc);
if((readl(ivp_cae_base_addr+0x0000fffc)&0x0fffffff)==(0x027035ca&0x0fffffff))
cnt++;
else
printf("cnt: 1660\n");
writel(0x00001100&0xffffffff,ivp_cae_base_addr+0x00010000);
if((readl(ivp_cae_base_addr+0x00010000)&0xc000ff00)==(0x00001100&0xc000ff00))
cnt++;
else
printf("cnt: 1661\n");
writel(0x00002200&0xffffffff,ivp_cae_base_addr+0x00010000);
if((readl(ivp_cae_base_addr+0x00010000)&0xc000ff00)==(0x00002200&0xc000ff00))
cnt++;
else
printf("cnt: 1662\n");
writel(0x40004400&0xffffffff,ivp_cae_base_addr+0x00010000);
if((readl(ivp_cae_base_addr+0x00010000)&0xc000ff00)==(0x40004400&0xc000ff00))
cnt++;
else
printf("cnt: 1663\n");
writel(0x80008800&0xffffffff,ivp_cae_base_addr+0x00010000);
if((readl(ivp_cae_base_addr+0x00010000)&0xc000ff00)==(0x80008800&0xc000ff00))
cnt++;
else
printf("cnt: 1664\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00010000);
if((readl(ivp_cae_base_addr+0x00010000)&0xc000ff00)==(0x00000000&0xc000ff00))
cnt++;
else
printf("cnt: 1665\n");
writel(0xc000ff00&0xffffffff,ivp_cae_base_addr+0x00010000);
if((readl(ivp_cae_base_addr+0x00010000)&0xc000ff00)==(0xc000ff00&0xc000ff00))
cnt++;
else
printf("cnt: 1666\n");
writel(0x00001100&0xffffffff,ivp_cae_base_addr+0x00010100);
if((readl(ivp_cae_base_addr+0x00010100)&0x8000ff00)==(0x00001100&0x8000ff00))
cnt++;
else
printf("cnt: 1667\n");
writel(0x00002200&0xffffffff,ivp_cae_base_addr+0x00010100);
if((readl(ivp_cae_base_addr+0x00010100)&0x8000ff00)==(0x00002200&0x8000ff00))
cnt++;
else
printf("cnt: 1668\n");
writel(0x00004400&0xffffffff,ivp_cae_base_addr+0x00010100);
if((readl(ivp_cae_base_addr+0x00010100)&0x8000ff00)==(0x00004400&0x8000ff00))
cnt++;
else
printf("cnt: 1669\n");
writel(0x80008800&0xffffffff,ivp_cae_base_addr+0x00010100);
if((readl(ivp_cae_base_addr+0x00010100)&0x8000ff00)==(0x80008800&0x8000ff00))
cnt++;
else
printf("cnt: 1670\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00010100);
if((readl(ivp_cae_base_addr+0x00010100)&0x8000ff00)==(0x00000000&0x8000ff00))
cnt++;
else
printf("cnt: 1671\n");
writel(0x8000ff00&0xffffffff,ivp_cae_base_addr+0x00010100);
if((readl(ivp_cae_base_addr+0x00010100)&0x8000ff00)==(0x8000ff00&0x8000ff00))
cnt++;
else
printf("cnt: 1672\n");
writel(0x00110000&0xffffffff,ivp_cae_base_addr+0x00011000);
if((readl(ivp_cae_base_addr+0x00011000)&0x007b0000)==(0x00110000&0x007b0000))
cnt++;
else
printf("cnt: 1673\n");
writel(0x00220000&0xffffffff,ivp_cae_base_addr+0x00011000);
if((readl(ivp_cae_base_addr+0x00011000)&0x007b0000)==(0x00220000&0x007b0000))
cnt++;
else
printf("cnt: 1674\n");
writel(0x00400000&0xffffffff,ivp_cae_base_addr+0x00011000);
if((readl(ivp_cae_base_addr+0x00011000)&0x007b0000)==(0x00400000&0x007b0000))
cnt++;
else
printf("cnt: 1675\n");
writel(0x00080000&0xffffffff,ivp_cae_base_addr+0x00011000);
if((readl(ivp_cae_base_addr+0x00011000)&0x007b0000)==(0x00080000&0x007b0000))
cnt++;
else
printf("cnt: 1676\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011000);
if((readl(ivp_cae_base_addr+0x00011000)&0x007b0000)==(0x00000000&0x007b0000))
cnt++;
else
printf("cnt: 1677\n");
writel(0x007b0000&0xffffffff,ivp_cae_base_addr+0x00011000);
if((readl(ivp_cae_base_addr+0x00011000)&0x007b0000)==(0x007b0000&0x007b0000))
cnt++;
else
printf("cnt: 1678\n");
writel(0x11011111&0xffffffff,ivp_cae_base_addr+0x00011004);
if((readl(ivp_cae_base_addr+0x00011004)&0xff6f7f3f)==(0x11011111&0xff6f7f3f))
cnt++;
else
printf("cnt: 1679\n");
writel(0x22222222&0xffffffff,ivp_cae_base_addr+0x00011004);
if((readl(ivp_cae_base_addr+0x00011004)&0xff6f7f3f)==(0x22222222&0xff6f7f3f))
cnt++;
else
printf("cnt: 1680\n");
writel(0x44444404&0xffffffff,ivp_cae_base_addr+0x00011004);
if((readl(ivp_cae_base_addr+0x00011004)&0xff6f7f3f)==(0x44444404&0xff6f7f3f))
cnt++;
else
printf("cnt: 1681\n");
writel(0x88080808&0xffffffff,ivp_cae_base_addr+0x00011004);
if((readl(ivp_cae_base_addr+0x00011004)&0xff6f7f3f)==(0x88080808&0xff6f7f3f))
cnt++;
else
printf("cnt: 1682\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011004);
if((readl(ivp_cae_base_addr+0x00011004)&0xff6f7f3f)==(0x00000000&0xff6f7f3f))
cnt++;
else
printf("cnt: 1683\n");
writel(0xff6f7f3f&0xffffffff,ivp_cae_base_addr+0x00011004);
if((readl(ivp_cae_base_addr+0x00011004)&0xff6f7f3f)==(0xff6f7f3f&0xff6f7f3f))
cnt++;
else
printf("cnt: 1684\n");
writel(0x00000111&0xffffffff,ivp_cae_base_addr+0x00011008);
if((readl(ivp_cae_base_addr+0x00011008)&0x0000033f)==(0x00000111&0x0000033f))
cnt++;
else
printf("cnt: 1685\n");
writel(0x00000222&0xffffffff,ivp_cae_base_addr+0x00011008);
if((readl(ivp_cae_base_addr+0x00011008)&0x0000033f)==(0x00000222&0x0000033f))
cnt++;
else
printf("cnt: 1686\n");
writel(0x00000004&0xffffffff,ivp_cae_base_addr+0x00011008);
if((readl(ivp_cae_base_addr+0x00011008)&0x0000033f)==(0x00000004&0x0000033f))
cnt++;
else
printf("cnt: 1687\n");
writel(0x00000008&0xffffffff,ivp_cae_base_addr+0x00011008);
if((readl(ivp_cae_base_addr+0x00011008)&0x0000033f)==(0x00000008&0x0000033f))
cnt++;
else
printf("cnt: 1688\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011008);
if((readl(ivp_cae_base_addr+0x00011008)&0x0000033f)==(0x00000000&0x0000033f))
cnt++;
else
printf("cnt: 1689\n");
writel(0x0000033f&0xffffffff,ivp_cae_base_addr+0x00011008);
if((readl(ivp_cae_base_addr+0x00011008)&0x0000033f)==(0x0000033f&0x0000033f))
cnt++;
else
printf("cnt: 1690\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001100c);
if((readl(ivp_cae_base_addr+0x0001100c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1691\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001100c);
if((readl(ivp_cae_base_addr+0x0001100c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1692\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001100c);
if((readl(ivp_cae_base_addr+0x0001100c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1693\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001100c);
if((readl(ivp_cae_base_addr+0x0001100c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1694\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001100c);
if((readl(ivp_cae_base_addr+0x0001100c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1695\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001100c);
if((readl(ivp_cae_base_addr+0x0001100c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1696\n");
writel(0x00110000&0xffffffff,ivp_cae_base_addr+0x00011018);
if((readl(ivp_cae_base_addr+0x00011018)&0x00ff0000)==(0x00110000&0x00ff0000))
cnt++;
else
printf("cnt: 1697\n");
writel(0x00220000&0xffffffff,ivp_cae_base_addr+0x00011018);
if((readl(ivp_cae_base_addr+0x00011018)&0x00ff0000)==(0x00220000&0x00ff0000))
cnt++;
else
printf("cnt: 1698\n");
writel(0x00440000&0xffffffff,ivp_cae_base_addr+0x00011018);
if((readl(ivp_cae_base_addr+0x00011018)&0x00ff0000)==(0x00440000&0x00ff0000))
cnt++;
else
printf("cnt: 1699\n");
writel(0x00880000&0xffffffff,ivp_cae_base_addr+0x00011018);
if((readl(ivp_cae_base_addr+0x00011018)&0x00ff0000)==(0x00880000&0x00ff0000))
cnt++;
else
printf("cnt: 1700\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011018);
if((readl(ivp_cae_base_addr+0x00011018)&0x00ff0000)==(0x00000000&0x00ff0000))
cnt++;
else
printf("cnt: 1701\n");
writel(0x00ff0000&0xffffffff,ivp_cae_base_addr+0x00011018);
if((readl(ivp_cae_base_addr+0x00011018)&0x00ff0000)==(0x00ff0000&0x00ff0000))
cnt++;
else
printf("cnt: 1702\n");
writel(0x00000010&0xffffffff,ivp_cae_base_addr+0x0001101c);
if((readl(ivp_cae_base_addr+0x0001101c)&0xc00000f8)==(0x00000010&0xc00000f8))
cnt++;
else
printf("cnt: 1703\n");
writel(0x00000020&0xffffffff,ivp_cae_base_addr+0x0001101c);
if((readl(ivp_cae_base_addr+0x0001101c)&0xc00000f8)==(0x00000020&0xc00000f8))
cnt++;
else
printf("cnt: 1704\n");
writel(0x40000040&0xffffffff,ivp_cae_base_addr+0x0001101c);
if((readl(ivp_cae_base_addr+0x0001101c)&0xc00000f8)==(0x40000040&0xc00000f8))
cnt++;
else
printf("cnt: 1705\n");
writel(0x80000088&0xffffffff,ivp_cae_base_addr+0x0001101c);
if((readl(ivp_cae_base_addr+0x0001101c)&0xc00000f8)==(0x80000088&0xc00000f8))
cnt++;
else
printf("cnt: 1706\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001101c);
if((readl(ivp_cae_base_addr+0x0001101c)&0xc00000f8)==(0x00000000&0xc00000f8))
cnt++;
else
printf("cnt: 1707\n");
writel(0xc00000f8&0xffffffff,ivp_cae_base_addr+0x0001101c);
if((readl(ivp_cae_base_addr+0x0001101c)&0xc00000f8)==(0xc00000f8&0xc00000f8))
cnt++;
else
printf("cnt: 1708\n");
writel(0x11111111&0xffffffff,ivp_cae_base_addr+0x00011020);
if((readl(ivp_cae_base_addr+0x00011020)&0xffffffff)==(0x11111111&0xffffffff))
cnt++;
else
printf("cnt: 1709\n");
writel(0x22222222&0xffffffff,ivp_cae_base_addr+0x00011020);
if((readl(ivp_cae_base_addr+0x00011020)&0xffffffff)==(0x22222222&0xffffffff))
cnt++;
else
printf("cnt: 1710\n");
writel(0x44444444&0xffffffff,ivp_cae_base_addr+0x00011020);
if((readl(ivp_cae_base_addr+0x00011020)&0xffffffff)==(0x44444444&0xffffffff))
cnt++;
else
printf("cnt: 1711\n");
writel(0x88888888&0xffffffff,ivp_cae_base_addr+0x00011020);
if((readl(ivp_cae_base_addr+0x00011020)&0xffffffff)==(0x88888888&0xffffffff))
cnt++;
else
printf("cnt: 1712\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011020);
if((readl(ivp_cae_base_addr+0x00011020)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 1713\n");
writel(0xffffffff&0xffffffff,ivp_cae_base_addr+0x00011020);
if((readl(ivp_cae_base_addr+0x00011020)&0xffffffff)==(0xffffffff&0xffffffff))
cnt++;
else
printf("cnt: 1714\n");
writel(0x11111111&0xffffffff,ivp_cae_base_addr+0x00011024);
if((readl(ivp_cae_base_addr+0x00011024)&0xffffffff)==(0x11111111&0xffffffff))
cnt++;
else
printf("cnt: 1715\n");
writel(0x22222222&0xffffffff,ivp_cae_base_addr+0x00011024);
if((readl(ivp_cae_base_addr+0x00011024)&0xffffffff)==(0x22222222&0xffffffff))
cnt++;
else
printf("cnt: 1716\n");
writel(0x44444444&0xffffffff,ivp_cae_base_addr+0x00011024);
if((readl(ivp_cae_base_addr+0x00011024)&0xffffffff)==(0x44444444&0xffffffff))
cnt++;
else
printf("cnt: 1717\n");
writel(0x88888888&0xffffffff,ivp_cae_base_addr+0x00011024);
if((readl(ivp_cae_base_addr+0x00011024)&0xffffffff)==(0x88888888&0xffffffff))
cnt++;
else
printf("cnt: 1718\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011024);
if((readl(ivp_cae_base_addr+0x00011024)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 1719\n");
writel(0xffffffff&0xffffffff,ivp_cae_base_addr+0x00011024);
if((readl(ivp_cae_base_addr+0x00011024)&0xffffffff)==(0xffffffff&0xffffffff))
cnt++;
else
printf("cnt: 1720\n");
writel(0x11111111&0xffffffff,ivp_cae_base_addr+0x00011028);
if((readl(ivp_cae_base_addr+0x00011028)&0xffffffff)==(0x11111111&0xffffffff))
cnt++;
else
printf("cnt: 1721\n");
writel(0x22222222&0xffffffff,ivp_cae_base_addr+0x00011028);
if((readl(ivp_cae_base_addr+0x00011028)&0xffffffff)==(0x22222222&0xffffffff))
cnt++;
else
printf("cnt: 1722\n");
writel(0x44444444&0xffffffff,ivp_cae_base_addr+0x00011028);
if((readl(ivp_cae_base_addr+0x00011028)&0xffffffff)==(0x44444444&0xffffffff))
cnt++;
else
printf("cnt: 1723\n");
writel(0x88888888&0xffffffff,ivp_cae_base_addr+0x00011028);
if((readl(ivp_cae_base_addr+0x00011028)&0xffffffff)==(0x88888888&0xffffffff))
cnt++;
else
printf("cnt: 1724\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011028);
if((readl(ivp_cae_base_addr+0x00011028)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 1725\n");
writel(0xffffffff&0xffffffff,ivp_cae_base_addr+0x00011028);
if((readl(ivp_cae_base_addr+0x00011028)&0xffffffff)==(0xffffffff&0xffffffff))
cnt++;
else
printf("cnt: 1726\n");
writel(0x00000001&0xffffffff,ivp_cae_base_addr+0x0001102c);
if((readl(ivp_cae_base_addr+0x0001102c)&0x0000000f)==(0x00000001&0x0000000f))
cnt++;
else
printf("cnt: 1727\n");
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0001102c);
if((readl(ivp_cae_base_addr+0x0001102c)&0x0000000f)==(0x00000002&0x0000000f))
cnt++;
else
printf("cnt: 1728\n");
writel(0x00000004&0xffffffff,ivp_cae_base_addr+0x0001102c);
if((readl(ivp_cae_base_addr+0x0001102c)&0x0000000f)==(0x00000004&0x0000000f))
cnt++;
else
printf("cnt: 1729\n");
writel(0x00000008&0xffffffff,ivp_cae_base_addr+0x0001102c);
if((readl(ivp_cae_base_addr+0x0001102c)&0x0000000f)==(0x00000008&0x0000000f))
cnt++;
else
printf("cnt: 1730\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001102c);
if((readl(ivp_cae_base_addr+0x0001102c)&0x0000000f)==(0x00000000&0x0000000f))
cnt++;
else
printf("cnt: 1731\n");
writel(0x0000000f&0xffffffff,ivp_cae_base_addr+0x0001102c);
if((readl(ivp_cae_base_addr+0x0001102c)&0x0000000f)==(0x0000000f&0x0000000f))
cnt++;
else
printf("cnt: 1732\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011030);
if((readl(ivp_cae_base_addr+0x00011030)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1733\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011030);
if((readl(ivp_cae_base_addr+0x00011030)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1734\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011030);
if((readl(ivp_cae_base_addr+0x00011030)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1735\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011030);
if((readl(ivp_cae_base_addr+0x00011030)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1736\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011030);
if((readl(ivp_cae_base_addr+0x00011030)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1737\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011030);
if((readl(ivp_cae_base_addr+0x00011030)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1738\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011040);
if((readl(ivp_cae_base_addr+0x00011040)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1739\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011040);
if((readl(ivp_cae_base_addr+0x00011040)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1740\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011040);
if((readl(ivp_cae_base_addr+0x00011040)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1741\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011040);
if((readl(ivp_cae_base_addr+0x00011040)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1742\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011040);
if((readl(ivp_cae_base_addr+0x00011040)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1743\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011040);
if((readl(ivp_cae_base_addr+0x00011040)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1744\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011044);
if((readl(ivp_cae_base_addr+0x00011044)&0x00000004)==(0x00000000&0x00000004))
cnt++;
else
printf("cnt: 1745\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011044);
if((readl(ivp_cae_base_addr+0x00011044)&0x00000004)==(0x00000000&0x00000004))
cnt++;
else
printf("cnt: 1746\n");
writel(0x00000004&0xffffffff,ivp_cae_base_addr+0x00011044);
if((readl(ivp_cae_base_addr+0x00011044)&0x00000004)==(0x00000004&0x00000004))
cnt++;
else
printf("cnt: 1747\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011044);
if((readl(ivp_cae_base_addr+0x00011044)&0x00000004)==(0x00000000&0x00000004))
cnt++;
else
printf("cnt: 1748\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011044);
if((readl(ivp_cae_base_addr+0x00011044)&0x00000004)==(0x00000000&0x00000004))
cnt++;
else
printf("cnt: 1749\n");
writel(0x00000004&0xffffffff,ivp_cae_base_addr+0x00011044);
if((readl(ivp_cae_base_addr+0x00011044)&0x00000004)==(0x00000004&0x00000004))
cnt++;
else
printf("cnt: 1750\n");
writel(0x11111111&0xffffffff,ivp_cae_base_addr+0x00011048);
if((readl(ivp_cae_base_addr+0x00011048)&0x00000000)==(0x11111111&0x00000000))
cnt++;
else
printf("cnt: 1751\n");
writel(0x22222222&0xffffffff,ivp_cae_base_addr+0x00011048);
if((readl(ivp_cae_base_addr+0x00011048)&0x00000000)==(0x22222222&0x00000000))
cnt++;
else
printf("cnt: 1752\n");
writel(0x44444444&0xffffffff,ivp_cae_base_addr+0x00011048);
if((readl(ivp_cae_base_addr+0x00011048)&0x00000000)==(0x44444444&0x00000000))
cnt++;
else
printf("cnt: 1753\n");
writel(0x88888888&0xffffffff,ivp_cae_base_addr+0x00011048);
if((readl(ivp_cae_base_addr+0x00011048)&0x00000000)==(0x88888888&0x00000000))
cnt++;
else
printf("cnt: 1754\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011048);
if((readl(ivp_cae_base_addr+0x00011048)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1755\n");
writel(0xffffffff&0xffffffff,ivp_cae_base_addr+0x00011048);
if((readl(ivp_cae_base_addr+0x00011048)&0x00000000)==(0xffffffff&0x00000000))
cnt++;
else
printf("cnt: 1756\n");
writel(0x11111111&0xffffffff,ivp_cae_base_addr+0x0001104c);
if((readl(ivp_cae_base_addr+0x0001104c)&0x00000000)==(0x11111111&0x00000000))
cnt++;
else
printf("cnt: 1757\n");
writel(0x22222222&0xffffffff,ivp_cae_base_addr+0x0001104c);
if((readl(ivp_cae_base_addr+0x0001104c)&0x00000000)==(0x22222222&0x00000000))
cnt++;
else
printf("cnt: 1758\n");
writel(0x44444444&0xffffffff,ivp_cae_base_addr+0x0001104c);
if((readl(ivp_cae_base_addr+0x0001104c)&0x00000000)==(0x44444444&0x00000000))
cnt++;
else
printf("cnt: 1759\n");
writel(0x88888888&0xffffffff,ivp_cae_base_addr+0x0001104c);
if((readl(ivp_cae_base_addr+0x0001104c)&0x00000000)==(0x88888888&0x00000000))
cnt++;
else
printf("cnt: 1760\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001104c);
if((readl(ivp_cae_base_addr+0x0001104c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1761\n");
writel(0xffffffff&0xffffffff,ivp_cae_base_addr+0x0001104c);
if((readl(ivp_cae_base_addr+0x0001104c)&0x00000000)==(0xffffffff&0x00000000))
cnt++;
else
printf("cnt: 1762\n");
writel(0x11111111&0xffffffff,ivp_cae_base_addr+0x00011050);
if((readl(ivp_cae_base_addr+0x00011050)&0x00000000)==(0x11111111&0x00000000))
cnt++;
else
printf("cnt: 1763\n");
writel(0x22222222&0xffffffff,ivp_cae_base_addr+0x00011050);
if((readl(ivp_cae_base_addr+0x00011050)&0x00000000)==(0x22222222&0x00000000))
cnt++;
else
printf("cnt: 1764\n");
writel(0x44444444&0xffffffff,ivp_cae_base_addr+0x00011050);
if((readl(ivp_cae_base_addr+0x00011050)&0x00000000)==(0x44444444&0x00000000))
cnt++;
else
printf("cnt: 1765\n");
writel(0x88888888&0xffffffff,ivp_cae_base_addr+0x00011050);
if((readl(ivp_cae_base_addr+0x00011050)&0x00000000)==(0x88888888&0x00000000))
cnt++;
else
printf("cnt: 1766\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011050);
if((readl(ivp_cae_base_addr+0x00011050)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1767\n");
writel(0xffffffff&0xffffffff,ivp_cae_base_addr+0x00011050);
if((readl(ivp_cae_base_addr+0x00011050)&0x00000000)==(0xffffffff&0x00000000))
cnt++;
else
printf("cnt: 1768\n");
writel(0x11111111&0xffffffff,ivp_cae_base_addr+0x00011054);
if((readl(ivp_cae_base_addr+0x00011054)&0x00000000)==(0x11111111&0x00000000))
cnt++;
else
printf("cnt: 1769\n");
writel(0x22222222&0xffffffff,ivp_cae_base_addr+0x00011054);
if((readl(ivp_cae_base_addr+0x00011054)&0x00000000)==(0x22222222&0x00000000))
cnt++;
else
printf("cnt: 1770\n");
writel(0x44444444&0xffffffff,ivp_cae_base_addr+0x00011054);
if((readl(ivp_cae_base_addr+0x00011054)&0x00000000)==(0x44444444&0x00000000))
cnt++;
else
printf("cnt: 1771\n");
writel(0x88888888&0xffffffff,ivp_cae_base_addr+0x00011054);
if((readl(ivp_cae_base_addr+0x00011054)&0x00000000)==(0x88888888&0x00000000))
cnt++;
else
printf("cnt: 1772\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011054);
if((readl(ivp_cae_base_addr+0x00011054)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1773\n");
writel(0xffffffff&0xffffffff,ivp_cae_base_addr+0x00011054);
if((readl(ivp_cae_base_addr+0x00011054)&0x00000000)==(0xffffffff&0x00000000))
cnt++;
else
printf("cnt: 1774\n");
writel(0x11111111&0xffffffff,ivp_cae_base_addr+0x00011058);
if((readl(ivp_cae_base_addr+0x00011058)&0x00000000)==(0x11111111&0x00000000))
cnt++;
else
printf("cnt: 1775\n");
writel(0x22222222&0xffffffff,ivp_cae_base_addr+0x00011058);
if((readl(ivp_cae_base_addr+0x00011058)&0x00000000)==(0x22222222&0x00000000))
cnt++;
else
printf("cnt: 1776\n");
writel(0x44444444&0xffffffff,ivp_cae_base_addr+0x00011058);
if((readl(ivp_cae_base_addr+0x00011058)&0x00000000)==(0x44444444&0x00000000))
cnt++;
else
printf("cnt: 1777\n");
writel(0x88888888&0xffffffff,ivp_cae_base_addr+0x00011058);
if((readl(ivp_cae_base_addr+0x00011058)&0x00000000)==(0x88888888&0x00000000))
cnt++;
else
printf("cnt: 1778\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011058);
if((readl(ivp_cae_base_addr+0x00011058)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1779\n");
writel(0xffffffff&0xffffffff,ivp_cae_base_addr+0x00011058);
if((readl(ivp_cae_base_addr+0x00011058)&0x00000000)==(0xffffffff&0x00000000))
cnt++;
else
printf("cnt: 1780\n");
writel(0x11111111&0xffffffff,ivp_cae_base_addr+0x0001105c);
if((readl(ivp_cae_base_addr+0x0001105c)&0x00000000)==(0x11111111&0x00000000))
cnt++;
else
printf("cnt: 1781\n");
writel(0x22222222&0xffffffff,ivp_cae_base_addr+0x0001105c);
if((readl(ivp_cae_base_addr+0x0001105c)&0x00000000)==(0x22222222&0x00000000))
cnt++;
else
printf("cnt: 1782\n");
writel(0x44444444&0xffffffff,ivp_cae_base_addr+0x0001105c);
if((readl(ivp_cae_base_addr+0x0001105c)&0x00000000)==(0x44444444&0x00000000))
cnt++;
else
printf("cnt: 1783\n");
writel(0x88888888&0xffffffff,ivp_cae_base_addr+0x0001105c);
if((readl(ivp_cae_base_addr+0x0001105c)&0x00000000)==(0x88888888&0x00000000))
cnt++;
else
printf("cnt: 1784\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001105c);
if((readl(ivp_cae_base_addr+0x0001105c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1785\n");
writel(0xffffffff&0xffffffff,ivp_cae_base_addr+0x0001105c);
if((readl(ivp_cae_base_addr+0x0001105c)&0x00000000)==(0xffffffff&0x00000000))
cnt++;
else
printf("cnt: 1786\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011060);
if((readl(ivp_cae_base_addr+0x00011060)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1787\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011060);
if((readl(ivp_cae_base_addr+0x00011060)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1788\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011060);
if((readl(ivp_cae_base_addr+0x00011060)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1789\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011060);
if((readl(ivp_cae_base_addr+0x00011060)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1790\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011060);
if((readl(ivp_cae_base_addr+0x00011060)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1791\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011060);
if((readl(ivp_cae_base_addr+0x00011060)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1792\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011064);
if((readl(ivp_cae_base_addr+0x00011064)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1793\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011064);
if((readl(ivp_cae_base_addr+0x00011064)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1794\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011064);
if((readl(ivp_cae_base_addr+0x00011064)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1795\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011064);
if((readl(ivp_cae_base_addr+0x00011064)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1796\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011064);
if((readl(ivp_cae_base_addr+0x00011064)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1797\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011064);
if((readl(ivp_cae_base_addr+0x00011064)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1798\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011068);
if((readl(ivp_cae_base_addr+0x00011068)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1799\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011068);
if((readl(ivp_cae_base_addr+0x00011068)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1800\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011068);
if((readl(ivp_cae_base_addr+0x00011068)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1801\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011068);
if((readl(ivp_cae_base_addr+0x00011068)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1802\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011068);
if((readl(ivp_cae_base_addr+0x00011068)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1803\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011068);
if((readl(ivp_cae_base_addr+0x00011068)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1804\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001106c);
if((readl(ivp_cae_base_addr+0x0001106c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1805\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001106c);
if((readl(ivp_cae_base_addr+0x0001106c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1806\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001106c);
if((readl(ivp_cae_base_addr+0x0001106c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1807\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001106c);
if((readl(ivp_cae_base_addr+0x0001106c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1808\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001106c);
if((readl(ivp_cae_base_addr+0x0001106c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1809\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001106c);
if((readl(ivp_cae_base_addr+0x0001106c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1810\n");
writel(0x11111111&0xffffffff,ivp_cae_base_addr+0x00011070);
if((readl(ivp_cae_base_addr+0x00011070)&0xffffffff)==(0x11111111&0xffffffff))
cnt++;
else
printf("cnt: 1811\n");
writel(0x22222222&0xffffffff,ivp_cae_base_addr+0x00011070);
if((readl(ivp_cae_base_addr+0x00011070)&0xffffffff)==(0x22222222&0xffffffff))
cnt++;
else
printf("cnt: 1812\n");
writel(0x44444444&0xffffffff,ivp_cae_base_addr+0x00011070);
if((readl(ivp_cae_base_addr+0x00011070)&0xffffffff)==(0x44444444&0xffffffff))
cnt++;
else
printf("cnt: 1813\n");
writel(0x88888888&0xffffffff,ivp_cae_base_addr+0x00011070);
if((readl(ivp_cae_base_addr+0x00011070)&0xffffffff)==(0x88888888&0xffffffff))
cnt++;
else
printf("cnt: 1814\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011070);
if((readl(ivp_cae_base_addr+0x00011070)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 1815\n");
writel(0xffffffff&0xffffffff,ivp_cae_base_addr+0x00011070);
if((readl(ivp_cae_base_addr+0x00011070)&0xffffffff)==(0xffffffff&0xffffffff))
cnt++;
else
printf("cnt: 1816\n");
writel(0x11111111&0xffffffff,ivp_cae_base_addr+0x00011074);
if((readl(ivp_cae_base_addr+0x00011074)&0xffffffff)==(0x11111111&0xffffffff))
cnt++;
else
printf("cnt: 1817\n");
writel(0x22222222&0xffffffff,ivp_cae_base_addr+0x00011074);
if((readl(ivp_cae_base_addr+0x00011074)&0xffffffff)==(0x22222222&0xffffffff))
cnt++;
else
printf("cnt: 1818\n");
writel(0x44444444&0xffffffff,ivp_cae_base_addr+0x00011074);
if((readl(ivp_cae_base_addr+0x00011074)&0xffffffff)==(0x44444444&0xffffffff))
cnt++;
else
printf("cnt: 1819\n");
writel(0x88888888&0xffffffff,ivp_cae_base_addr+0x00011074);
if((readl(ivp_cae_base_addr+0x00011074)&0xffffffff)==(0x88888888&0xffffffff))
cnt++;
else
printf("cnt: 1820\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011074);
if((readl(ivp_cae_base_addr+0x00011074)&0xffffffff)==(0x00000000&0xffffffff))
cnt++;
else
printf("cnt: 1821\n");
writel(0xffffffff&0xffffffff,ivp_cae_base_addr+0x00011074);
if((readl(ivp_cae_base_addr+0x00011074)&0xffffffff)==(0xffffffff&0xffffffff))
cnt++;
else
printf("cnt: 1822\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011080);
if((readl(ivp_cae_base_addr+0x00011080)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1823\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011080);
if((readl(ivp_cae_base_addr+0x00011080)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1824\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011080);
if((readl(ivp_cae_base_addr+0x00011080)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1825\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011080);
if((readl(ivp_cae_base_addr+0x00011080)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1826\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011080);
if((readl(ivp_cae_base_addr+0x00011080)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1827\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011080);
if((readl(ivp_cae_base_addr+0x00011080)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1828\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011084);
if((readl(ivp_cae_base_addr+0x00011084)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1829\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011084);
if((readl(ivp_cae_base_addr+0x00011084)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1830\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011084);
if((readl(ivp_cae_base_addr+0x00011084)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1831\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011084);
if((readl(ivp_cae_base_addr+0x00011084)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1832\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011084);
if((readl(ivp_cae_base_addr+0x00011084)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1833\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011084);
if((readl(ivp_cae_base_addr+0x00011084)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1834\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011088);
if((readl(ivp_cae_base_addr+0x00011088)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1835\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011088);
if((readl(ivp_cae_base_addr+0x00011088)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1836\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011088);
if((readl(ivp_cae_base_addr+0x00011088)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1837\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011088);
if((readl(ivp_cae_base_addr+0x00011088)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1838\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011088);
if((readl(ivp_cae_base_addr+0x00011088)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1839\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011088);
if((readl(ivp_cae_base_addr+0x00011088)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1840\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001108c);
if((readl(ivp_cae_base_addr+0x0001108c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1841\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001108c);
if((readl(ivp_cae_base_addr+0x0001108c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1842\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001108c);
if((readl(ivp_cae_base_addr+0x0001108c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1843\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001108c);
if((readl(ivp_cae_base_addr+0x0001108c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1844\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001108c);
if((readl(ivp_cae_base_addr+0x0001108c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1845\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001108c);
if((readl(ivp_cae_base_addr+0x0001108c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1846\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011090);
if((readl(ivp_cae_base_addr+0x00011090)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1847\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011090);
if((readl(ivp_cae_base_addr+0x00011090)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1848\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011090);
if((readl(ivp_cae_base_addr+0x00011090)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1849\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011090);
if((readl(ivp_cae_base_addr+0x00011090)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1850\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011090);
if((readl(ivp_cae_base_addr+0x00011090)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1851\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011090);
if((readl(ivp_cae_base_addr+0x00011090)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1852\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011094);
if((readl(ivp_cae_base_addr+0x00011094)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1853\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011094);
if((readl(ivp_cae_base_addr+0x00011094)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1854\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011094);
if((readl(ivp_cae_base_addr+0x00011094)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1855\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011094);
if((readl(ivp_cae_base_addr+0x00011094)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1856\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011094);
if((readl(ivp_cae_base_addr+0x00011094)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1857\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011094);
if((readl(ivp_cae_base_addr+0x00011094)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1858\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011098);
if((readl(ivp_cae_base_addr+0x00011098)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1859\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011098);
if((readl(ivp_cae_base_addr+0x00011098)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1860\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011098);
if((readl(ivp_cae_base_addr+0x00011098)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1861\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011098);
if((readl(ivp_cae_base_addr+0x00011098)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1862\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011098);
if((readl(ivp_cae_base_addr+0x00011098)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1863\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011098);
if((readl(ivp_cae_base_addr+0x00011098)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1864\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001109c);
if((readl(ivp_cae_base_addr+0x0001109c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1865\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001109c);
if((readl(ivp_cae_base_addr+0x0001109c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1866\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001109c);
if((readl(ivp_cae_base_addr+0x0001109c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1867\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001109c);
if((readl(ivp_cae_base_addr+0x0001109c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1868\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001109c);
if((readl(ivp_cae_base_addr+0x0001109c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1869\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001109c);
if((readl(ivp_cae_base_addr+0x0001109c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1870\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110a0);
if((readl(ivp_cae_base_addr+0x000110a0)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1871\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110a0);
if((readl(ivp_cae_base_addr+0x000110a0)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1872\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110a0);
if((readl(ivp_cae_base_addr+0x000110a0)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1873\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110a0);
if((readl(ivp_cae_base_addr+0x000110a0)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1874\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110a0);
if((readl(ivp_cae_base_addr+0x000110a0)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1875\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110a0);
if((readl(ivp_cae_base_addr+0x000110a0)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1876\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110a4);
if((readl(ivp_cae_base_addr+0x000110a4)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1877\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110a4);
if((readl(ivp_cae_base_addr+0x000110a4)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1878\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110a4);
if((readl(ivp_cae_base_addr+0x000110a4)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1879\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110a4);
if((readl(ivp_cae_base_addr+0x000110a4)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1880\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110a4);
if((readl(ivp_cae_base_addr+0x000110a4)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1881\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110a4);
if((readl(ivp_cae_base_addr+0x000110a4)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1882\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110a8);
if((readl(ivp_cae_base_addr+0x000110a8)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1883\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110a8);
if((readl(ivp_cae_base_addr+0x000110a8)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1884\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110a8);
if((readl(ivp_cae_base_addr+0x000110a8)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1885\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110a8);
if((readl(ivp_cae_base_addr+0x000110a8)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1886\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110a8);
if((readl(ivp_cae_base_addr+0x000110a8)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1887\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110a8);
if((readl(ivp_cae_base_addr+0x000110a8)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1888\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110ac);
if((readl(ivp_cae_base_addr+0x000110ac)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1889\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110ac);
if((readl(ivp_cae_base_addr+0x000110ac)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1890\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110ac);
if((readl(ivp_cae_base_addr+0x000110ac)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1891\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110ac);
if((readl(ivp_cae_base_addr+0x000110ac)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1892\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110ac);
if((readl(ivp_cae_base_addr+0x000110ac)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1893\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110ac);
if((readl(ivp_cae_base_addr+0x000110ac)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1894\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110b0);
if((readl(ivp_cae_base_addr+0x000110b0)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1895\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110b0);
if((readl(ivp_cae_base_addr+0x000110b0)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1896\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110b0);
if((readl(ivp_cae_base_addr+0x000110b0)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1897\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110b0);
if((readl(ivp_cae_base_addr+0x000110b0)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1898\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110b0);
if((readl(ivp_cae_base_addr+0x000110b0)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1899\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110b0);
if((readl(ivp_cae_base_addr+0x000110b0)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1900\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110b4);
if((readl(ivp_cae_base_addr+0x000110b4)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1901\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110b4);
if((readl(ivp_cae_base_addr+0x000110b4)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1902\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110b4);
if((readl(ivp_cae_base_addr+0x000110b4)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1903\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110b4);
if((readl(ivp_cae_base_addr+0x000110b4)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1904\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110b4);
if((readl(ivp_cae_base_addr+0x000110b4)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1905\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110b4);
if((readl(ivp_cae_base_addr+0x000110b4)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1906\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110b8);
if((readl(ivp_cae_base_addr+0x000110b8)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1907\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110b8);
if((readl(ivp_cae_base_addr+0x000110b8)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1908\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110b8);
if((readl(ivp_cae_base_addr+0x000110b8)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1909\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110b8);
if((readl(ivp_cae_base_addr+0x000110b8)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1910\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110b8);
if((readl(ivp_cae_base_addr+0x000110b8)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1911\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110b8);
if((readl(ivp_cae_base_addr+0x000110b8)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1912\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110bc);
if((readl(ivp_cae_base_addr+0x000110bc)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1913\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110bc);
if((readl(ivp_cae_base_addr+0x000110bc)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1914\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110bc);
if((readl(ivp_cae_base_addr+0x000110bc)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1915\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110bc);
if((readl(ivp_cae_base_addr+0x000110bc)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1916\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110bc);
if((readl(ivp_cae_base_addr+0x000110bc)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1917\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110bc);
if((readl(ivp_cae_base_addr+0x000110bc)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1918\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110c0);
if((readl(ivp_cae_base_addr+0x000110c0)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1919\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110c0);
if((readl(ivp_cae_base_addr+0x000110c0)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1920\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110c0);
if((readl(ivp_cae_base_addr+0x000110c0)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1921\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110c0);
if((readl(ivp_cae_base_addr+0x000110c0)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1922\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110c0);
if((readl(ivp_cae_base_addr+0x000110c0)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1923\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110c0);
if((readl(ivp_cae_base_addr+0x000110c0)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1924\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110c4);
if((readl(ivp_cae_base_addr+0x000110c4)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1925\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110c4);
if((readl(ivp_cae_base_addr+0x000110c4)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1926\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110c4);
if((readl(ivp_cae_base_addr+0x000110c4)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1927\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110c4);
if((readl(ivp_cae_base_addr+0x000110c4)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1928\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110c4);
if((readl(ivp_cae_base_addr+0x000110c4)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1929\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110c4);
if((readl(ivp_cae_base_addr+0x000110c4)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1930\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110c8);
if((readl(ivp_cae_base_addr+0x000110c8)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1931\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110c8);
if((readl(ivp_cae_base_addr+0x000110c8)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1932\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110c8);
if((readl(ivp_cae_base_addr+0x000110c8)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1933\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110c8);
if((readl(ivp_cae_base_addr+0x000110c8)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1934\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110c8);
if((readl(ivp_cae_base_addr+0x000110c8)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1935\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110c8);
if((readl(ivp_cae_base_addr+0x000110c8)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1936\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110cc);
if((readl(ivp_cae_base_addr+0x000110cc)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1937\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110cc);
if((readl(ivp_cae_base_addr+0x000110cc)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1938\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110cc);
if((readl(ivp_cae_base_addr+0x000110cc)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1939\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110cc);
if((readl(ivp_cae_base_addr+0x000110cc)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1940\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110cc);
if((readl(ivp_cae_base_addr+0x000110cc)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1941\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110cc);
if((readl(ivp_cae_base_addr+0x000110cc)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1942\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110d0);
if((readl(ivp_cae_base_addr+0x000110d0)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1943\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110d0);
if((readl(ivp_cae_base_addr+0x000110d0)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1944\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110d0);
if((readl(ivp_cae_base_addr+0x000110d0)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1945\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110d0);
if((readl(ivp_cae_base_addr+0x000110d0)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1946\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110d0);
if((readl(ivp_cae_base_addr+0x000110d0)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1947\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110d0);
if((readl(ivp_cae_base_addr+0x000110d0)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1948\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110d4);
if((readl(ivp_cae_base_addr+0x000110d4)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1949\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110d4);
if((readl(ivp_cae_base_addr+0x000110d4)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1950\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110d4);
if((readl(ivp_cae_base_addr+0x000110d4)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1951\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110d4);
if((readl(ivp_cae_base_addr+0x000110d4)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1952\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110d4);
if((readl(ivp_cae_base_addr+0x000110d4)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1953\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110d4);
if((readl(ivp_cae_base_addr+0x000110d4)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1954\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110d8);
if((readl(ivp_cae_base_addr+0x000110d8)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1955\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110d8);
if((readl(ivp_cae_base_addr+0x000110d8)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1956\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110d8);
if((readl(ivp_cae_base_addr+0x000110d8)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1957\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110d8);
if((readl(ivp_cae_base_addr+0x000110d8)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1958\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110d8);
if((readl(ivp_cae_base_addr+0x000110d8)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1959\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110d8);
if((readl(ivp_cae_base_addr+0x000110d8)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1960\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110dc);
if((readl(ivp_cae_base_addr+0x000110dc)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1961\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110dc);
if((readl(ivp_cae_base_addr+0x000110dc)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1962\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110dc);
if((readl(ivp_cae_base_addr+0x000110dc)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1963\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110dc);
if((readl(ivp_cae_base_addr+0x000110dc)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1964\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110dc);
if((readl(ivp_cae_base_addr+0x000110dc)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1965\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110dc);
if((readl(ivp_cae_base_addr+0x000110dc)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1966\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110e0);
if((readl(ivp_cae_base_addr+0x000110e0)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1967\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110e0);
if((readl(ivp_cae_base_addr+0x000110e0)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1968\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110e0);
if((readl(ivp_cae_base_addr+0x000110e0)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1969\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110e0);
if((readl(ivp_cae_base_addr+0x000110e0)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1970\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110e0);
if((readl(ivp_cae_base_addr+0x000110e0)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1971\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110e0);
if((readl(ivp_cae_base_addr+0x000110e0)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1972\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110e4);
if((readl(ivp_cae_base_addr+0x000110e4)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1973\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110e4);
if((readl(ivp_cae_base_addr+0x000110e4)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1974\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110e4);
if((readl(ivp_cae_base_addr+0x000110e4)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1975\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110e4);
if((readl(ivp_cae_base_addr+0x000110e4)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1976\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110e4);
if((readl(ivp_cae_base_addr+0x000110e4)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1977\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110e4);
if((readl(ivp_cae_base_addr+0x000110e4)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1978\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110e8);
if((readl(ivp_cae_base_addr+0x000110e8)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1979\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110e8);
if((readl(ivp_cae_base_addr+0x000110e8)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1980\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110e8);
if((readl(ivp_cae_base_addr+0x000110e8)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1981\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110e8);
if((readl(ivp_cae_base_addr+0x000110e8)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1982\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110e8);
if((readl(ivp_cae_base_addr+0x000110e8)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1983\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110e8);
if((readl(ivp_cae_base_addr+0x000110e8)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1984\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110ec);
if((readl(ivp_cae_base_addr+0x000110ec)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1985\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110ec);
if((readl(ivp_cae_base_addr+0x000110ec)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1986\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110ec);
if((readl(ivp_cae_base_addr+0x000110ec)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1987\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110ec);
if((readl(ivp_cae_base_addr+0x000110ec)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1988\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110ec);
if((readl(ivp_cae_base_addr+0x000110ec)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1989\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110ec);
if((readl(ivp_cae_base_addr+0x000110ec)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1990\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110f0);
if((readl(ivp_cae_base_addr+0x000110f0)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1991\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110f0);
if((readl(ivp_cae_base_addr+0x000110f0)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1992\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110f0);
if((readl(ivp_cae_base_addr+0x000110f0)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1993\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110f0);
if((readl(ivp_cae_base_addr+0x000110f0)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1994\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110f0);
if((readl(ivp_cae_base_addr+0x000110f0)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1995\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110f0);
if((readl(ivp_cae_base_addr+0x000110f0)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1996\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110f4);
if((readl(ivp_cae_base_addr+0x000110f4)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1997\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110f4);
if((readl(ivp_cae_base_addr+0x000110f4)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1998\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110f4);
if((readl(ivp_cae_base_addr+0x000110f4)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 1999\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110f4);
if((readl(ivp_cae_base_addr+0x000110f4)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2000\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110f4);
if((readl(ivp_cae_base_addr+0x000110f4)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2001\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110f4);
if((readl(ivp_cae_base_addr+0x000110f4)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2002\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110f8);
if((readl(ivp_cae_base_addr+0x000110f8)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2003\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110f8);
if((readl(ivp_cae_base_addr+0x000110f8)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2004\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110f8);
if((readl(ivp_cae_base_addr+0x000110f8)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2005\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110f8);
if((readl(ivp_cae_base_addr+0x000110f8)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2006\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110f8);
if((readl(ivp_cae_base_addr+0x000110f8)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2007\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110f8);
if((readl(ivp_cae_base_addr+0x000110f8)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2008\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110fc);
if((readl(ivp_cae_base_addr+0x000110fc)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2009\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110fc);
if((readl(ivp_cae_base_addr+0x000110fc)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2010\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110fc);
if((readl(ivp_cae_base_addr+0x000110fc)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2011\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110fc);
if((readl(ivp_cae_base_addr+0x000110fc)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2012\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110fc);
if((readl(ivp_cae_base_addr+0x000110fc)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2013\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110fc);
if((readl(ivp_cae_base_addr+0x000110fc)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2014\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011100);
if((readl(ivp_cae_base_addr+0x00011100)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2015\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011100);
if((readl(ivp_cae_base_addr+0x00011100)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2016\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011100);
if((readl(ivp_cae_base_addr+0x00011100)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2017\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011100);
if((readl(ivp_cae_base_addr+0x00011100)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2018\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011100);
if((readl(ivp_cae_base_addr+0x00011100)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2019\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011100);
if((readl(ivp_cae_base_addr+0x00011100)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2020\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011104);
if((readl(ivp_cae_base_addr+0x00011104)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2021\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011104);
if((readl(ivp_cae_base_addr+0x00011104)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2022\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011104);
if((readl(ivp_cae_base_addr+0x00011104)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2023\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011104);
if((readl(ivp_cae_base_addr+0x00011104)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2024\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011104);
if((readl(ivp_cae_base_addr+0x00011104)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2025\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011104);
if((readl(ivp_cae_base_addr+0x00011104)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2026\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011108);
if((readl(ivp_cae_base_addr+0x00011108)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2027\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011108);
if((readl(ivp_cae_base_addr+0x00011108)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2028\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011108);
if((readl(ivp_cae_base_addr+0x00011108)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2029\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011108);
if((readl(ivp_cae_base_addr+0x00011108)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2030\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011108);
if((readl(ivp_cae_base_addr+0x00011108)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2031\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011108);
if((readl(ivp_cae_base_addr+0x00011108)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2032\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001110c);
if((readl(ivp_cae_base_addr+0x0001110c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2033\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001110c);
if((readl(ivp_cae_base_addr+0x0001110c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2034\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001110c);
if((readl(ivp_cae_base_addr+0x0001110c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2035\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001110c);
if((readl(ivp_cae_base_addr+0x0001110c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2036\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001110c);
if((readl(ivp_cae_base_addr+0x0001110c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2037\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001110c);
if((readl(ivp_cae_base_addr+0x0001110c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2038\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011110);
if((readl(ivp_cae_base_addr+0x00011110)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2039\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011110);
if((readl(ivp_cae_base_addr+0x00011110)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2040\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011110);
if((readl(ivp_cae_base_addr+0x00011110)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2041\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011110);
if((readl(ivp_cae_base_addr+0x00011110)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2042\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011110);
if((readl(ivp_cae_base_addr+0x00011110)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2043\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011110);
if((readl(ivp_cae_base_addr+0x00011110)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2044\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011114);
if((readl(ivp_cae_base_addr+0x00011114)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2045\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011114);
if((readl(ivp_cae_base_addr+0x00011114)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2046\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011114);
if((readl(ivp_cae_base_addr+0x00011114)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2047\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011114);
if((readl(ivp_cae_base_addr+0x00011114)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2048\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011114);
if((readl(ivp_cae_base_addr+0x00011114)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2049\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011114);
if((readl(ivp_cae_base_addr+0x00011114)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2050\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011118);
if((readl(ivp_cae_base_addr+0x00011118)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2051\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011118);
if((readl(ivp_cae_base_addr+0x00011118)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2052\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011118);
if((readl(ivp_cae_base_addr+0x00011118)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2053\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011118);
if((readl(ivp_cae_base_addr+0x00011118)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2054\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011118);
if((readl(ivp_cae_base_addr+0x00011118)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2055\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011118);
if((readl(ivp_cae_base_addr+0x00011118)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2056\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001111c);
if((readl(ivp_cae_base_addr+0x0001111c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2057\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001111c);
if((readl(ivp_cae_base_addr+0x0001111c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2058\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001111c);
if((readl(ivp_cae_base_addr+0x0001111c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2059\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001111c);
if((readl(ivp_cae_base_addr+0x0001111c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2060\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001111c);
if((readl(ivp_cae_base_addr+0x0001111c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2061\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001111c);
if((readl(ivp_cae_base_addr+0x0001111c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2062\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011140);
if((readl(ivp_cae_base_addr+0x00011140)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2063\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011140);
if((readl(ivp_cae_base_addr+0x00011140)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2064\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011140);
if((readl(ivp_cae_base_addr+0x00011140)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2065\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011140);
if((readl(ivp_cae_base_addr+0x00011140)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2066\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011140);
if((readl(ivp_cae_base_addr+0x00011140)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2067\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011140);
if((readl(ivp_cae_base_addr+0x00011140)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2068\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011144);
if((readl(ivp_cae_base_addr+0x00011144)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2069\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011144);
if((readl(ivp_cae_base_addr+0x00011144)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2070\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011144);
if((readl(ivp_cae_base_addr+0x00011144)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2071\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011144);
if((readl(ivp_cae_base_addr+0x00011144)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2072\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011144);
if((readl(ivp_cae_base_addr+0x00011144)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2073\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011144);
if((readl(ivp_cae_base_addr+0x00011144)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2074\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011148);
if((readl(ivp_cae_base_addr+0x00011148)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2075\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011148);
if((readl(ivp_cae_base_addr+0x00011148)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2076\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011148);
if((readl(ivp_cae_base_addr+0x00011148)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2077\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011148);
if((readl(ivp_cae_base_addr+0x00011148)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2078\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011148);
if((readl(ivp_cae_base_addr+0x00011148)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2079\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011148);
if((readl(ivp_cae_base_addr+0x00011148)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2080\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001114c);
if((readl(ivp_cae_base_addr+0x0001114c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2081\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001114c);
if((readl(ivp_cae_base_addr+0x0001114c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2082\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001114c);
if((readl(ivp_cae_base_addr+0x0001114c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2083\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001114c);
if((readl(ivp_cae_base_addr+0x0001114c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2084\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001114c);
if((readl(ivp_cae_base_addr+0x0001114c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2085\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001114c);
if((readl(ivp_cae_base_addr+0x0001114c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2086\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011150);
if((readl(ivp_cae_base_addr+0x00011150)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2087\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011150);
if((readl(ivp_cae_base_addr+0x00011150)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2088\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011150);
if((readl(ivp_cae_base_addr+0x00011150)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2089\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011150);
if((readl(ivp_cae_base_addr+0x00011150)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2090\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011150);
if((readl(ivp_cae_base_addr+0x00011150)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2091\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011150);
if((readl(ivp_cae_base_addr+0x00011150)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2092\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011154);
if((readl(ivp_cae_base_addr+0x00011154)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2093\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011154);
if((readl(ivp_cae_base_addr+0x00011154)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2094\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011154);
if((readl(ivp_cae_base_addr+0x00011154)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2095\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011154);
if((readl(ivp_cae_base_addr+0x00011154)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2096\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011154);
if((readl(ivp_cae_base_addr+0x00011154)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2097\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011154);
if((readl(ivp_cae_base_addr+0x00011154)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2098\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011158);
if((readl(ivp_cae_base_addr+0x00011158)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2099\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011158);
if((readl(ivp_cae_base_addr+0x00011158)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2100\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011158);
if((readl(ivp_cae_base_addr+0x00011158)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2101\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011158);
if((readl(ivp_cae_base_addr+0x00011158)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2102\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011158);
if((readl(ivp_cae_base_addr+0x00011158)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2103\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011158);
if((readl(ivp_cae_base_addr+0x00011158)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2104\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001115c);
if((readl(ivp_cae_base_addr+0x0001115c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2105\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001115c);
if((readl(ivp_cae_base_addr+0x0001115c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2106\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001115c);
if((readl(ivp_cae_base_addr+0x0001115c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2107\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001115c);
if((readl(ivp_cae_base_addr+0x0001115c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2108\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001115c);
if((readl(ivp_cae_base_addr+0x0001115c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2109\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001115c);
if((readl(ivp_cae_base_addr+0x0001115c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2110\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011160);
if((readl(ivp_cae_base_addr+0x00011160)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2111\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011160);
if((readl(ivp_cae_base_addr+0x00011160)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2112\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011160);
if((readl(ivp_cae_base_addr+0x00011160)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2113\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011160);
if((readl(ivp_cae_base_addr+0x00011160)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2114\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011160);
if((readl(ivp_cae_base_addr+0x00011160)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2115\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011160);
if((readl(ivp_cae_base_addr+0x00011160)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2116\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011164);
if((readl(ivp_cae_base_addr+0x00011164)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2117\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011164);
if((readl(ivp_cae_base_addr+0x00011164)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2118\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011164);
if((readl(ivp_cae_base_addr+0x00011164)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2119\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011164);
if((readl(ivp_cae_base_addr+0x00011164)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2120\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011164);
if((readl(ivp_cae_base_addr+0x00011164)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2121\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011164);
if((readl(ivp_cae_base_addr+0x00011164)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2122\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011168);
if((readl(ivp_cae_base_addr+0x00011168)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2123\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011168);
if((readl(ivp_cae_base_addr+0x00011168)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2124\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011168);
if((readl(ivp_cae_base_addr+0x00011168)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2125\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011168);
if((readl(ivp_cae_base_addr+0x00011168)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2126\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011168);
if((readl(ivp_cae_base_addr+0x00011168)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2127\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011168);
if((readl(ivp_cae_base_addr+0x00011168)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2128\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001116c);
if((readl(ivp_cae_base_addr+0x0001116c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2129\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001116c);
if((readl(ivp_cae_base_addr+0x0001116c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2130\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001116c);
if((readl(ivp_cae_base_addr+0x0001116c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2131\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001116c);
if((readl(ivp_cae_base_addr+0x0001116c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2132\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001116c);
if((readl(ivp_cae_base_addr+0x0001116c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2133\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001116c);
if((readl(ivp_cae_base_addr+0x0001116c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2134\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011170);
if((readl(ivp_cae_base_addr+0x00011170)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2135\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011170);
if((readl(ivp_cae_base_addr+0x00011170)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2136\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011170);
if((readl(ivp_cae_base_addr+0x00011170)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2137\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011170);
if((readl(ivp_cae_base_addr+0x00011170)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2138\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011170);
if((readl(ivp_cae_base_addr+0x00011170)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2139\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011170);
if((readl(ivp_cae_base_addr+0x00011170)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2140\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011174);
if((readl(ivp_cae_base_addr+0x00011174)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2141\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011174);
if((readl(ivp_cae_base_addr+0x00011174)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2142\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011174);
if((readl(ivp_cae_base_addr+0x00011174)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2143\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011174);
if((readl(ivp_cae_base_addr+0x00011174)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2144\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011174);
if((readl(ivp_cae_base_addr+0x00011174)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2145\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011174);
if((readl(ivp_cae_base_addr+0x00011174)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2146\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011178);
if((readl(ivp_cae_base_addr+0x00011178)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2147\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011178);
if((readl(ivp_cae_base_addr+0x00011178)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2148\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011178);
if((readl(ivp_cae_base_addr+0x00011178)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2149\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011178);
if((readl(ivp_cae_base_addr+0x00011178)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2150\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011178);
if((readl(ivp_cae_base_addr+0x00011178)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2151\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011178);
if((readl(ivp_cae_base_addr+0x00011178)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2152\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001117c);
if((readl(ivp_cae_base_addr+0x0001117c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2153\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001117c);
if((readl(ivp_cae_base_addr+0x0001117c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2154\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001117c);
if((readl(ivp_cae_base_addr+0x0001117c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2155\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001117c);
if((readl(ivp_cae_base_addr+0x0001117c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2156\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001117c);
if((readl(ivp_cae_base_addr+0x0001117c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2157\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001117c);
if((readl(ivp_cae_base_addr+0x0001117c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2158\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011180);
if((readl(ivp_cae_base_addr+0x00011180)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2159\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011180);
if((readl(ivp_cae_base_addr+0x00011180)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2160\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011180);
if((readl(ivp_cae_base_addr+0x00011180)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2161\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011180);
if((readl(ivp_cae_base_addr+0x00011180)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2162\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011180);
if((readl(ivp_cae_base_addr+0x00011180)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2163\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011180);
if((readl(ivp_cae_base_addr+0x00011180)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2164\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011184);
if((readl(ivp_cae_base_addr+0x00011184)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2165\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011184);
if((readl(ivp_cae_base_addr+0x00011184)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2166\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011184);
if((readl(ivp_cae_base_addr+0x00011184)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2167\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011184);
if((readl(ivp_cae_base_addr+0x00011184)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2168\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011184);
if((readl(ivp_cae_base_addr+0x00011184)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2169\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011184);
if((readl(ivp_cae_base_addr+0x00011184)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2170\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011188);
if((readl(ivp_cae_base_addr+0x00011188)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2171\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011188);
if((readl(ivp_cae_base_addr+0x00011188)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2172\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011188);
if((readl(ivp_cae_base_addr+0x00011188)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2173\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011188);
if((readl(ivp_cae_base_addr+0x00011188)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2174\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011188);
if((readl(ivp_cae_base_addr+0x00011188)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2175\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011188);
if((readl(ivp_cae_base_addr+0x00011188)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2176\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001118c);
if((readl(ivp_cae_base_addr+0x0001118c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2177\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001118c);
if((readl(ivp_cae_base_addr+0x0001118c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2178\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001118c);
if((readl(ivp_cae_base_addr+0x0001118c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2179\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001118c);
if((readl(ivp_cae_base_addr+0x0001118c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2180\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001118c);
if((readl(ivp_cae_base_addr+0x0001118c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2181\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001118c);
if((readl(ivp_cae_base_addr+0x0001118c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2182\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011190);
if((readl(ivp_cae_base_addr+0x00011190)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2183\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011190);
if((readl(ivp_cae_base_addr+0x00011190)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2184\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011190);
if((readl(ivp_cae_base_addr+0x00011190)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2185\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011190);
if((readl(ivp_cae_base_addr+0x00011190)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2186\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011190);
if((readl(ivp_cae_base_addr+0x00011190)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2187\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011190);
if((readl(ivp_cae_base_addr+0x00011190)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2188\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011194);
if((readl(ivp_cae_base_addr+0x00011194)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2189\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011194);
if((readl(ivp_cae_base_addr+0x00011194)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2190\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011194);
if((readl(ivp_cae_base_addr+0x00011194)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2191\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011194);
if((readl(ivp_cae_base_addr+0x00011194)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2192\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011194);
if((readl(ivp_cae_base_addr+0x00011194)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2193\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011194);
if((readl(ivp_cae_base_addr+0x00011194)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2194\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011198);
if((readl(ivp_cae_base_addr+0x00011198)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2195\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011198);
if((readl(ivp_cae_base_addr+0x00011198)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2196\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011198);
if((readl(ivp_cae_base_addr+0x00011198)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2197\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011198);
if((readl(ivp_cae_base_addr+0x00011198)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2198\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011198);
if((readl(ivp_cae_base_addr+0x00011198)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2199\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011198);
if((readl(ivp_cae_base_addr+0x00011198)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2200\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001119c);
if((readl(ivp_cae_base_addr+0x0001119c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2201\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001119c);
if((readl(ivp_cae_base_addr+0x0001119c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2202\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001119c);
if((readl(ivp_cae_base_addr+0x0001119c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2203\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001119c);
if((readl(ivp_cae_base_addr+0x0001119c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2204\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001119c);
if((readl(ivp_cae_base_addr+0x0001119c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2205\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001119c);
if((readl(ivp_cae_base_addr+0x0001119c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2206\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000111a0);
if((readl(ivp_cae_base_addr+0x000111a0)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2207\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000111a0);
if((readl(ivp_cae_base_addr+0x000111a0)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2208\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000111a0);
if((readl(ivp_cae_base_addr+0x000111a0)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2209\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000111a0);
if((readl(ivp_cae_base_addr+0x000111a0)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2210\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000111a0);
if((readl(ivp_cae_base_addr+0x000111a0)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2211\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000111a0);
if((readl(ivp_cae_base_addr+0x000111a0)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2212\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000111a4);
if((readl(ivp_cae_base_addr+0x000111a4)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2213\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000111a4);
if((readl(ivp_cae_base_addr+0x000111a4)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2214\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000111a4);
if((readl(ivp_cae_base_addr+0x000111a4)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2215\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000111a4);
if((readl(ivp_cae_base_addr+0x000111a4)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2216\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000111a4);
if((readl(ivp_cae_base_addr+0x000111a4)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2217\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000111a4);
if((readl(ivp_cae_base_addr+0x000111a4)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2218\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000111a8);
if((readl(ivp_cae_base_addr+0x000111a8)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2219\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000111a8);
if((readl(ivp_cae_base_addr+0x000111a8)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2220\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000111a8);
if((readl(ivp_cae_base_addr+0x000111a8)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2221\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000111a8);
if((readl(ivp_cae_base_addr+0x000111a8)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2222\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000111a8);
if((readl(ivp_cae_base_addr+0x000111a8)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2223\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000111a8);
if((readl(ivp_cae_base_addr+0x000111a8)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2224\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000111ac);
if((readl(ivp_cae_base_addr+0x000111ac)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2225\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000111ac);
if((readl(ivp_cae_base_addr+0x000111ac)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2226\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000111ac);
if((readl(ivp_cae_base_addr+0x000111ac)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2227\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000111ac);
if((readl(ivp_cae_base_addr+0x000111ac)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2228\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000111ac);
if((readl(ivp_cae_base_addr+0x000111ac)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2229\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000111ac);
if((readl(ivp_cae_base_addr+0x000111ac)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2230\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000111b0);
if((readl(ivp_cae_base_addr+0x000111b0)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2231\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000111b0);
if((readl(ivp_cae_base_addr+0x000111b0)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2232\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000111b0);
if((readl(ivp_cae_base_addr+0x000111b0)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2233\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000111b0);
if((readl(ivp_cae_base_addr+0x000111b0)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2234\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000111b0);
if((readl(ivp_cae_base_addr+0x000111b0)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2235\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000111b0);
if((readl(ivp_cae_base_addr+0x000111b0)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2236\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000111b4);
if((readl(ivp_cae_base_addr+0x000111b4)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2237\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000111b4);
if((readl(ivp_cae_base_addr+0x000111b4)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2238\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000111b4);
if((readl(ivp_cae_base_addr+0x000111b4)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2239\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000111b4);
if((readl(ivp_cae_base_addr+0x000111b4)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2240\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000111b4);
if((readl(ivp_cae_base_addr+0x000111b4)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2241\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000111b4);
if((readl(ivp_cae_base_addr+0x000111b4)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2242\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000111b8);
if((readl(ivp_cae_base_addr+0x000111b8)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2243\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000111b8);
if((readl(ivp_cae_base_addr+0x000111b8)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2244\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000111b8);
if((readl(ivp_cae_base_addr+0x000111b8)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2245\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000111b8);
if((readl(ivp_cae_base_addr+0x000111b8)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2246\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000111b8);
if((readl(ivp_cae_base_addr+0x000111b8)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2247\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000111b8);
if((readl(ivp_cae_base_addr+0x000111b8)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2248\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000111bc);
if((readl(ivp_cae_base_addr+0x000111bc)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2249\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000111bc);
if((readl(ivp_cae_base_addr+0x000111bc)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2250\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000111bc);
if((readl(ivp_cae_base_addr+0x000111bc)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2251\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000111bc);
if((readl(ivp_cae_base_addr+0x000111bc)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2252\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000111bc);
if((readl(ivp_cae_base_addr+0x000111bc)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2253\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000111bc);
if((readl(ivp_cae_base_addr+0x000111bc)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2254\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000111c0);
if((readl(ivp_cae_base_addr+0x000111c0)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2255\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000111c0);
if((readl(ivp_cae_base_addr+0x000111c0)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2256\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000111c0);
if((readl(ivp_cae_base_addr+0x000111c0)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2257\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000111c0);
if((readl(ivp_cae_base_addr+0x000111c0)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2258\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000111c0);
if((readl(ivp_cae_base_addr+0x000111c0)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2259\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000111c0);
if((readl(ivp_cae_base_addr+0x000111c0)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2260\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000111c4);
if((readl(ivp_cae_base_addr+0x000111c4)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2261\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000111c4);
if((readl(ivp_cae_base_addr+0x000111c4)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2262\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000111c4);
if((readl(ivp_cae_base_addr+0x000111c4)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2263\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000111c4);
if((readl(ivp_cae_base_addr+0x000111c4)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2264\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000111c4);
if((readl(ivp_cae_base_addr+0x000111c4)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2265\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000111c4);
if((readl(ivp_cae_base_addr+0x000111c4)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2266\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000111c8);
if((readl(ivp_cae_base_addr+0x000111c8)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2267\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000111c8);
if((readl(ivp_cae_base_addr+0x000111c8)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2268\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000111c8);
if((readl(ivp_cae_base_addr+0x000111c8)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2269\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000111c8);
if((readl(ivp_cae_base_addr+0x000111c8)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2270\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000111c8);
if((readl(ivp_cae_base_addr+0x000111c8)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2271\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000111c8);
if((readl(ivp_cae_base_addr+0x000111c8)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2272\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000111cc);
if((readl(ivp_cae_base_addr+0x000111cc)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2273\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000111cc);
if((readl(ivp_cae_base_addr+0x000111cc)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2274\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000111cc);
if((readl(ivp_cae_base_addr+0x000111cc)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2275\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000111cc);
if((readl(ivp_cae_base_addr+0x000111cc)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2276\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000111cc);
if((readl(ivp_cae_base_addr+0x000111cc)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2277\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000111cc);
if((readl(ivp_cae_base_addr+0x000111cc)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2278\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000111d0);
if((readl(ivp_cae_base_addr+0x000111d0)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2279\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000111d0);
if((readl(ivp_cae_base_addr+0x000111d0)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2280\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000111d0);
if((readl(ivp_cae_base_addr+0x000111d0)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2281\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000111d0);
if((readl(ivp_cae_base_addr+0x000111d0)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2282\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000111d0);
if((readl(ivp_cae_base_addr+0x000111d0)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2283\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000111d0);
if((readl(ivp_cae_base_addr+0x000111d0)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2284\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000111d4);
if((readl(ivp_cae_base_addr+0x000111d4)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2285\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000111d4);
if((readl(ivp_cae_base_addr+0x000111d4)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2286\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000111d4);
if((readl(ivp_cae_base_addr+0x000111d4)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2287\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000111d4);
if((readl(ivp_cae_base_addr+0x000111d4)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2288\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000111d4);
if((readl(ivp_cae_base_addr+0x000111d4)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2289\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000111d4);
if((readl(ivp_cae_base_addr+0x000111d4)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2290\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000111d8);
if((readl(ivp_cae_base_addr+0x000111d8)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2291\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000111d8);
if((readl(ivp_cae_base_addr+0x000111d8)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2292\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000111d8);
if((readl(ivp_cae_base_addr+0x000111d8)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2293\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000111d8);
if((readl(ivp_cae_base_addr+0x000111d8)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2294\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000111d8);
if((readl(ivp_cae_base_addr+0x000111d8)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2295\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000111d8);
if((readl(ivp_cae_base_addr+0x000111d8)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2296\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000111dc);
if((readl(ivp_cae_base_addr+0x000111dc)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2297\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000111dc);
if((readl(ivp_cae_base_addr+0x000111dc)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2298\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000111dc);
if((readl(ivp_cae_base_addr+0x000111dc)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2299\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000111dc);
if((readl(ivp_cae_base_addr+0x000111dc)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2300\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000111dc);
if((readl(ivp_cae_base_addr+0x000111dc)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2301\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000111dc);
if((readl(ivp_cae_base_addr+0x000111dc)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2302\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000111e4);
if((readl(ivp_cae_base_addr+0x000111e4)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2303\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000111e4);
if((readl(ivp_cae_base_addr+0x000111e4)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2304\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000111e4);
if((readl(ivp_cae_base_addr+0x000111e4)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2305\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000111e4);
if((readl(ivp_cae_base_addr+0x000111e4)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2306\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000111e4);
if((readl(ivp_cae_base_addr+0x000111e4)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2307\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000111e4);
if((readl(ivp_cae_base_addr+0x000111e4)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2308\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011200);
if((readl(ivp_cae_base_addr+0x00011200)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2309\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011200);
if((readl(ivp_cae_base_addr+0x00011200)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2310\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011200);
if((readl(ivp_cae_base_addr+0x00011200)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2311\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011200);
if((readl(ivp_cae_base_addr+0x00011200)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2312\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011200);
if((readl(ivp_cae_base_addr+0x00011200)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2313\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011200);
if((readl(ivp_cae_base_addr+0x00011200)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2314\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011204);
if((readl(ivp_cae_base_addr+0x00011204)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2315\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011204);
if((readl(ivp_cae_base_addr+0x00011204)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2316\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011204);
if((readl(ivp_cae_base_addr+0x00011204)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2317\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011204);
if((readl(ivp_cae_base_addr+0x00011204)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2318\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011204);
if((readl(ivp_cae_base_addr+0x00011204)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2319\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011204);
if((readl(ivp_cae_base_addr+0x00011204)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2320\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011208);
if((readl(ivp_cae_base_addr+0x00011208)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2321\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011208);
if((readl(ivp_cae_base_addr+0x00011208)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2322\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011208);
if((readl(ivp_cae_base_addr+0x00011208)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2323\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011208);
if((readl(ivp_cae_base_addr+0x00011208)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2324\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011208);
if((readl(ivp_cae_base_addr+0x00011208)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2325\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011208);
if((readl(ivp_cae_base_addr+0x00011208)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2326\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001120c);
if((readl(ivp_cae_base_addr+0x0001120c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2327\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001120c);
if((readl(ivp_cae_base_addr+0x0001120c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2328\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001120c);
if((readl(ivp_cae_base_addr+0x0001120c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2329\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001120c);
if((readl(ivp_cae_base_addr+0x0001120c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2330\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001120c);
if((readl(ivp_cae_base_addr+0x0001120c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2331\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001120c);
if((readl(ivp_cae_base_addr+0x0001120c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2332\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011210);
if((readl(ivp_cae_base_addr+0x00011210)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2333\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011210);
if((readl(ivp_cae_base_addr+0x00011210)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2334\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011210);
if((readl(ivp_cae_base_addr+0x00011210)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2335\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011210);
if((readl(ivp_cae_base_addr+0x00011210)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2336\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011210);
if((readl(ivp_cae_base_addr+0x00011210)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2337\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011210);
if((readl(ivp_cae_base_addr+0x00011210)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2338\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011214);
if((readl(ivp_cae_base_addr+0x00011214)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2339\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011214);
if((readl(ivp_cae_base_addr+0x00011214)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2340\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011214);
if((readl(ivp_cae_base_addr+0x00011214)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2341\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011214);
if((readl(ivp_cae_base_addr+0x00011214)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2342\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011214);
if((readl(ivp_cae_base_addr+0x00011214)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2343\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011214);
if((readl(ivp_cae_base_addr+0x00011214)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2344\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011218);
if((readl(ivp_cae_base_addr+0x00011218)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2345\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011218);
if((readl(ivp_cae_base_addr+0x00011218)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2346\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011218);
if((readl(ivp_cae_base_addr+0x00011218)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2347\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011218);
if((readl(ivp_cae_base_addr+0x00011218)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2348\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011218);
if((readl(ivp_cae_base_addr+0x00011218)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2349\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011218);
if((readl(ivp_cae_base_addr+0x00011218)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2350\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001121c);
if((readl(ivp_cae_base_addr+0x0001121c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2351\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001121c);
if((readl(ivp_cae_base_addr+0x0001121c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2352\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001121c);
if((readl(ivp_cae_base_addr+0x0001121c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2353\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001121c);
if((readl(ivp_cae_base_addr+0x0001121c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2354\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001121c);
if((readl(ivp_cae_base_addr+0x0001121c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2355\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001121c);
if((readl(ivp_cae_base_addr+0x0001121c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2356\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011220);
if((readl(ivp_cae_base_addr+0x00011220)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2357\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011220);
if((readl(ivp_cae_base_addr+0x00011220)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2358\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011220);
if((readl(ivp_cae_base_addr+0x00011220)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2359\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011220);
if((readl(ivp_cae_base_addr+0x00011220)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2360\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011220);
if((readl(ivp_cae_base_addr+0x00011220)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2361\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011220);
if((readl(ivp_cae_base_addr+0x00011220)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2362\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011224);
if((readl(ivp_cae_base_addr+0x00011224)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2363\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011224);
if((readl(ivp_cae_base_addr+0x00011224)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2364\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011224);
if((readl(ivp_cae_base_addr+0x00011224)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2365\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011224);
if((readl(ivp_cae_base_addr+0x00011224)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2366\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011224);
if((readl(ivp_cae_base_addr+0x00011224)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2367\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011224);
if((readl(ivp_cae_base_addr+0x00011224)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2368\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011228);
if((readl(ivp_cae_base_addr+0x00011228)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2369\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011228);
if((readl(ivp_cae_base_addr+0x00011228)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2370\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011228);
if((readl(ivp_cae_base_addr+0x00011228)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2371\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011228);
if((readl(ivp_cae_base_addr+0x00011228)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2372\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011228);
if((readl(ivp_cae_base_addr+0x00011228)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2373\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011228);
if((readl(ivp_cae_base_addr+0x00011228)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2374\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001122c);
if((readl(ivp_cae_base_addr+0x0001122c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2375\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001122c);
if((readl(ivp_cae_base_addr+0x0001122c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2376\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001122c);
if((readl(ivp_cae_base_addr+0x0001122c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2377\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001122c);
if((readl(ivp_cae_base_addr+0x0001122c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2378\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001122c);
if((readl(ivp_cae_base_addr+0x0001122c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2379\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001122c);
if((readl(ivp_cae_base_addr+0x0001122c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2380\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011230);
if((readl(ivp_cae_base_addr+0x00011230)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2381\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011230);
if((readl(ivp_cae_base_addr+0x00011230)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2382\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011230);
if((readl(ivp_cae_base_addr+0x00011230)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2383\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011230);
if((readl(ivp_cae_base_addr+0x00011230)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2384\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011230);
if((readl(ivp_cae_base_addr+0x00011230)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2385\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011230);
if((readl(ivp_cae_base_addr+0x00011230)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2386\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011234);
if((readl(ivp_cae_base_addr+0x00011234)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2387\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011234);
if((readl(ivp_cae_base_addr+0x00011234)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2388\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011234);
if((readl(ivp_cae_base_addr+0x00011234)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2389\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011234);
if((readl(ivp_cae_base_addr+0x00011234)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2390\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011234);
if((readl(ivp_cae_base_addr+0x00011234)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2391\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011234);
if((readl(ivp_cae_base_addr+0x00011234)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2392\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011238);
if((readl(ivp_cae_base_addr+0x00011238)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2393\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011238);
if((readl(ivp_cae_base_addr+0x00011238)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2394\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011238);
if((readl(ivp_cae_base_addr+0x00011238)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2395\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011238);
if((readl(ivp_cae_base_addr+0x00011238)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2396\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011238);
if((readl(ivp_cae_base_addr+0x00011238)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2397\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011238);
if((readl(ivp_cae_base_addr+0x00011238)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2398\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001123c);
if((readl(ivp_cae_base_addr+0x0001123c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2399\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001123c);
if((readl(ivp_cae_base_addr+0x0001123c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2400\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001123c);
if((readl(ivp_cae_base_addr+0x0001123c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2401\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001123c);
if((readl(ivp_cae_base_addr+0x0001123c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2402\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001123c);
if((readl(ivp_cae_base_addr+0x0001123c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2403\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001123c);
if((readl(ivp_cae_base_addr+0x0001123c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2404\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011240);
if((readl(ivp_cae_base_addr+0x00011240)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2405\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011240);
if((readl(ivp_cae_base_addr+0x00011240)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2406\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011240);
if((readl(ivp_cae_base_addr+0x00011240)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2407\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011240);
if((readl(ivp_cae_base_addr+0x00011240)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2408\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011240);
if((readl(ivp_cae_base_addr+0x00011240)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2409\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011240);
if((readl(ivp_cae_base_addr+0x00011240)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2410\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011244);
if((readl(ivp_cae_base_addr+0x00011244)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2411\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011244);
if((readl(ivp_cae_base_addr+0x00011244)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2412\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011244);
if((readl(ivp_cae_base_addr+0x00011244)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2413\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011244);
if((readl(ivp_cae_base_addr+0x00011244)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2414\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011244);
if((readl(ivp_cae_base_addr+0x00011244)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2415\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011244);
if((readl(ivp_cae_base_addr+0x00011244)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2416\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011248);
if((readl(ivp_cae_base_addr+0x00011248)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2417\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011248);
if((readl(ivp_cae_base_addr+0x00011248)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2418\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011248);
if((readl(ivp_cae_base_addr+0x00011248)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2419\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011248);
if((readl(ivp_cae_base_addr+0x00011248)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2420\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011248);
if((readl(ivp_cae_base_addr+0x00011248)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2421\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011248);
if((readl(ivp_cae_base_addr+0x00011248)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2422\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001124c);
if((readl(ivp_cae_base_addr+0x0001124c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2423\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001124c);
if((readl(ivp_cae_base_addr+0x0001124c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2424\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001124c);
if((readl(ivp_cae_base_addr+0x0001124c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2425\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001124c);
if((readl(ivp_cae_base_addr+0x0001124c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2426\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001124c);
if((readl(ivp_cae_base_addr+0x0001124c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2427\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001124c);
if((readl(ivp_cae_base_addr+0x0001124c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2428\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011250);
if((readl(ivp_cae_base_addr+0x00011250)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2429\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011250);
if((readl(ivp_cae_base_addr+0x00011250)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2430\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011250);
if((readl(ivp_cae_base_addr+0x00011250)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2431\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011250);
if((readl(ivp_cae_base_addr+0x00011250)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2432\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011250);
if((readl(ivp_cae_base_addr+0x00011250)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2433\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011250);
if((readl(ivp_cae_base_addr+0x00011250)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2434\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011254);
if((readl(ivp_cae_base_addr+0x00011254)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2435\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011254);
if((readl(ivp_cae_base_addr+0x00011254)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2436\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011254);
if((readl(ivp_cae_base_addr+0x00011254)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2437\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011254);
if((readl(ivp_cae_base_addr+0x00011254)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2438\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011254);
if((readl(ivp_cae_base_addr+0x00011254)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2439\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011254);
if((readl(ivp_cae_base_addr+0x00011254)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2440\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011258);
if((readl(ivp_cae_base_addr+0x00011258)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2441\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011258);
if((readl(ivp_cae_base_addr+0x00011258)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2442\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011258);
if((readl(ivp_cae_base_addr+0x00011258)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2443\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011258);
if((readl(ivp_cae_base_addr+0x00011258)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2444\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011258);
if((readl(ivp_cae_base_addr+0x00011258)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2445\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011258);
if((readl(ivp_cae_base_addr+0x00011258)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2446\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001125c);
if((readl(ivp_cae_base_addr+0x0001125c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2447\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001125c);
if((readl(ivp_cae_base_addr+0x0001125c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2448\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001125c);
if((readl(ivp_cae_base_addr+0x0001125c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2449\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001125c);
if((readl(ivp_cae_base_addr+0x0001125c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2450\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001125c);
if((readl(ivp_cae_base_addr+0x0001125c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2451\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001125c);
if((readl(ivp_cae_base_addr+0x0001125c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2452\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011260);
if((readl(ivp_cae_base_addr+0x00011260)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2453\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011260);
if((readl(ivp_cae_base_addr+0x00011260)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2454\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011260);
if((readl(ivp_cae_base_addr+0x00011260)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2455\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011260);
if((readl(ivp_cae_base_addr+0x00011260)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2456\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011260);
if((readl(ivp_cae_base_addr+0x00011260)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2457\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011260);
if((readl(ivp_cae_base_addr+0x00011260)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2458\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011264);
if((readl(ivp_cae_base_addr+0x00011264)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2459\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011264);
if((readl(ivp_cae_base_addr+0x00011264)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2460\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011264);
if((readl(ivp_cae_base_addr+0x00011264)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2461\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011264);
if((readl(ivp_cae_base_addr+0x00011264)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2462\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011264);
if((readl(ivp_cae_base_addr+0x00011264)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2463\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011264);
if((readl(ivp_cae_base_addr+0x00011264)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2464\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011268);
if((readl(ivp_cae_base_addr+0x00011268)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2465\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011268);
if((readl(ivp_cae_base_addr+0x00011268)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2466\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011268);
if((readl(ivp_cae_base_addr+0x00011268)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2467\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011268);
if((readl(ivp_cae_base_addr+0x00011268)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2468\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011268);
if((readl(ivp_cae_base_addr+0x00011268)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2469\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011268);
if((readl(ivp_cae_base_addr+0x00011268)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2470\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001126c);
if((readl(ivp_cae_base_addr+0x0001126c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2471\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001126c);
if((readl(ivp_cae_base_addr+0x0001126c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2472\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001126c);
if((readl(ivp_cae_base_addr+0x0001126c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2473\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001126c);
if((readl(ivp_cae_base_addr+0x0001126c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2474\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001126c);
if((readl(ivp_cae_base_addr+0x0001126c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2475\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001126c);
if((readl(ivp_cae_base_addr+0x0001126c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2476\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011270);
if((readl(ivp_cae_base_addr+0x00011270)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2477\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011270);
if((readl(ivp_cae_base_addr+0x00011270)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2478\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011270);
if((readl(ivp_cae_base_addr+0x00011270)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2479\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011270);
if((readl(ivp_cae_base_addr+0x00011270)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2480\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011270);
if((readl(ivp_cae_base_addr+0x00011270)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2481\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011270);
if((readl(ivp_cae_base_addr+0x00011270)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2482\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011274);
if((readl(ivp_cae_base_addr+0x00011274)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2483\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011274);
if((readl(ivp_cae_base_addr+0x00011274)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2484\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011274);
if((readl(ivp_cae_base_addr+0x00011274)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2485\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011274);
if((readl(ivp_cae_base_addr+0x00011274)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2486\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011274);
if((readl(ivp_cae_base_addr+0x00011274)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2487\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011274);
if((readl(ivp_cae_base_addr+0x00011274)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2488\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011278);
if((readl(ivp_cae_base_addr+0x00011278)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2489\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011278);
if((readl(ivp_cae_base_addr+0x00011278)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2490\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011278);
if((readl(ivp_cae_base_addr+0x00011278)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2491\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011278);
if((readl(ivp_cae_base_addr+0x00011278)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2492\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011278);
if((readl(ivp_cae_base_addr+0x00011278)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2493\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011278);
if((readl(ivp_cae_base_addr+0x00011278)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2494\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001127c);
if((readl(ivp_cae_base_addr+0x0001127c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2495\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001127c);
if((readl(ivp_cae_base_addr+0x0001127c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2496\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001127c);
if((readl(ivp_cae_base_addr+0x0001127c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2497\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001127c);
if((readl(ivp_cae_base_addr+0x0001127c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2498\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001127c);
if((readl(ivp_cae_base_addr+0x0001127c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2499\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001127c);
if((readl(ivp_cae_base_addr+0x0001127c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2500\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011280);
if((readl(ivp_cae_base_addr+0x00011280)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2501\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011280);
if((readl(ivp_cae_base_addr+0x00011280)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2502\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011280);
if((readl(ivp_cae_base_addr+0x00011280)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2503\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011280);
if((readl(ivp_cae_base_addr+0x00011280)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2504\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011280);
if((readl(ivp_cae_base_addr+0x00011280)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2505\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011280);
if((readl(ivp_cae_base_addr+0x00011280)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2506\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011284);
if((readl(ivp_cae_base_addr+0x00011284)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2507\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011284);
if((readl(ivp_cae_base_addr+0x00011284)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2508\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011284);
if((readl(ivp_cae_base_addr+0x00011284)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2509\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011284);
if((readl(ivp_cae_base_addr+0x00011284)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2510\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011284);
if((readl(ivp_cae_base_addr+0x00011284)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2511\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011284);
if((readl(ivp_cae_base_addr+0x00011284)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2512\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011288);
if((readl(ivp_cae_base_addr+0x00011288)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2513\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011288);
if((readl(ivp_cae_base_addr+0x00011288)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2514\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011288);
if((readl(ivp_cae_base_addr+0x00011288)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2515\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011288);
if((readl(ivp_cae_base_addr+0x00011288)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2516\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011288);
if((readl(ivp_cae_base_addr+0x00011288)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2517\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011288);
if((readl(ivp_cae_base_addr+0x00011288)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2518\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001128c);
if((readl(ivp_cae_base_addr+0x0001128c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2519\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001128c);
if((readl(ivp_cae_base_addr+0x0001128c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2520\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001128c);
if((readl(ivp_cae_base_addr+0x0001128c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2521\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001128c);
if((readl(ivp_cae_base_addr+0x0001128c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2522\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001128c);
if((readl(ivp_cae_base_addr+0x0001128c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2523\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001128c);
if((readl(ivp_cae_base_addr+0x0001128c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2524\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011290);
if((readl(ivp_cae_base_addr+0x00011290)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2525\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011290);
if((readl(ivp_cae_base_addr+0x00011290)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2526\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011290);
if((readl(ivp_cae_base_addr+0x00011290)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2527\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011290);
if((readl(ivp_cae_base_addr+0x00011290)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2528\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011290);
if((readl(ivp_cae_base_addr+0x00011290)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2529\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011290);
if((readl(ivp_cae_base_addr+0x00011290)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2530\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011294);
if((readl(ivp_cae_base_addr+0x00011294)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2531\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011294);
if((readl(ivp_cae_base_addr+0x00011294)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2532\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011294);
if((readl(ivp_cae_base_addr+0x00011294)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2533\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011294);
if((readl(ivp_cae_base_addr+0x00011294)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2534\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011294);
if((readl(ivp_cae_base_addr+0x00011294)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2535\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011294);
if((readl(ivp_cae_base_addr+0x00011294)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2536\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011298);
if((readl(ivp_cae_base_addr+0x00011298)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2537\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011298);
if((readl(ivp_cae_base_addr+0x00011298)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2538\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011298);
if((readl(ivp_cae_base_addr+0x00011298)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2539\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011298);
if((readl(ivp_cae_base_addr+0x00011298)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2540\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011298);
if((readl(ivp_cae_base_addr+0x00011298)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2541\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011298);
if((readl(ivp_cae_base_addr+0x00011298)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2542\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001129c);
if((readl(ivp_cae_base_addr+0x0001129c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2543\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001129c);
if((readl(ivp_cae_base_addr+0x0001129c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2544\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001129c);
if((readl(ivp_cae_base_addr+0x0001129c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2545\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001129c);
if((readl(ivp_cae_base_addr+0x0001129c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2546\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001129c);
if((readl(ivp_cae_base_addr+0x0001129c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2547\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001129c);
if((readl(ivp_cae_base_addr+0x0001129c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2548\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000112a4);
if((readl(ivp_cae_base_addr+0x000112a4)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2549\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000112a4);
if((readl(ivp_cae_base_addr+0x000112a4)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2550\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000112a4);
if((readl(ivp_cae_base_addr+0x000112a4)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2551\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000112a4);
if((readl(ivp_cae_base_addr+0x000112a4)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2552\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000112a4);
if((readl(ivp_cae_base_addr+0x000112a4)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2553\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000112a4);
if((readl(ivp_cae_base_addr+0x000112a4)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2554\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000112c0);
if((readl(ivp_cae_base_addr+0x000112c0)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2555\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000112c0);
if((readl(ivp_cae_base_addr+0x000112c0)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2556\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000112c0);
if((readl(ivp_cae_base_addr+0x000112c0)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2557\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000112c0);
if((readl(ivp_cae_base_addr+0x000112c0)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2558\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000112c0);
if((readl(ivp_cae_base_addr+0x000112c0)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2559\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000112c0);
if((readl(ivp_cae_base_addr+0x000112c0)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2560\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000112c4);
if((readl(ivp_cae_base_addr+0x000112c4)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2561\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000112c4);
if((readl(ivp_cae_base_addr+0x000112c4)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2562\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000112c4);
if((readl(ivp_cae_base_addr+0x000112c4)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2563\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000112c4);
if((readl(ivp_cae_base_addr+0x000112c4)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2564\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000112c4);
if((readl(ivp_cae_base_addr+0x000112c4)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2565\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000112c4);
if((readl(ivp_cae_base_addr+0x000112c4)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2566\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000112c8);
if((readl(ivp_cae_base_addr+0x000112c8)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2567\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000112c8);
if((readl(ivp_cae_base_addr+0x000112c8)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2568\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000112c8);
if((readl(ivp_cae_base_addr+0x000112c8)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2569\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000112c8);
if((readl(ivp_cae_base_addr+0x000112c8)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2570\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000112c8);
if((readl(ivp_cae_base_addr+0x000112c8)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2571\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000112c8);
if((readl(ivp_cae_base_addr+0x000112c8)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2572\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000112cc);
if((readl(ivp_cae_base_addr+0x000112cc)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2573\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000112cc);
if((readl(ivp_cae_base_addr+0x000112cc)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2574\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000112cc);
if((readl(ivp_cae_base_addr+0x000112cc)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2575\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000112cc);
if((readl(ivp_cae_base_addr+0x000112cc)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2576\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000112cc);
if((readl(ivp_cae_base_addr+0x000112cc)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2577\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000112cc);
if((readl(ivp_cae_base_addr+0x000112cc)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2578\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000112d0);
if((readl(ivp_cae_base_addr+0x000112d0)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2579\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000112d0);
if((readl(ivp_cae_base_addr+0x000112d0)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2580\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000112d0);
if((readl(ivp_cae_base_addr+0x000112d0)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2581\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000112d0);
if((readl(ivp_cae_base_addr+0x000112d0)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2582\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000112d0);
if((readl(ivp_cae_base_addr+0x000112d0)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2583\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000112d0);
if((readl(ivp_cae_base_addr+0x000112d0)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2584\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000112d4);
if((readl(ivp_cae_base_addr+0x000112d4)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2585\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000112d4);
if((readl(ivp_cae_base_addr+0x000112d4)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2586\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000112d4);
if((readl(ivp_cae_base_addr+0x000112d4)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2587\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000112d4);
if((readl(ivp_cae_base_addr+0x000112d4)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2588\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000112d4);
if((readl(ivp_cae_base_addr+0x000112d4)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2589\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000112d4);
if((readl(ivp_cae_base_addr+0x000112d4)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2590\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000112d8);
if((readl(ivp_cae_base_addr+0x000112d8)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2591\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000112d8);
if((readl(ivp_cae_base_addr+0x000112d8)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2592\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000112d8);
if((readl(ivp_cae_base_addr+0x000112d8)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2593\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000112d8);
if((readl(ivp_cae_base_addr+0x000112d8)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2594\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000112d8);
if((readl(ivp_cae_base_addr+0x000112d8)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2595\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000112d8);
if((readl(ivp_cae_base_addr+0x000112d8)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2596\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000112dc);
if((readl(ivp_cae_base_addr+0x000112dc)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2597\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000112dc);
if((readl(ivp_cae_base_addr+0x000112dc)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2598\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000112dc);
if((readl(ivp_cae_base_addr+0x000112dc)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2599\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000112dc);
if((readl(ivp_cae_base_addr+0x000112dc)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2600\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000112dc);
if((readl(ivp_cae_base_addr+0x000112dc)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2601\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000112dc);
if((readl(ivp_cae_base_addr+0x000112dc)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2602\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000112e0);
if((readl(ivp_cae_base_addr+0x000112e0)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2603\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000112e0);
if((readl(ivp_cae_base_addr+0x000112e0)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2604\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000112e0);
if((readl(ivp_cae_base_addr+0x000112e0)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2605\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000112e0);
if((readl(ivp_cae_base_addr+0x000112e0)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2606\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000112e0);
if((readl(ivp_cae_base_addr+0x000112e0)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2607\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000112e0);
if((readl(ivp_cae_base_addr+0x000112e0)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2608\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000112e4);
if((readl(ivp_cae_base_addr+0x000112e4)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2609\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000112e4);
if((readl(ivp_cae_base_addr+0x000112e4)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2610\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000112e4);
if((readl(ivp_cae_base_addr+0x000112e4)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2611\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000112e4);
if((readl(ivp_cae_base_addr+0x000112e4)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2612\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000112e4);
if((readl(ivp_cae_base_addr+0x000112e4)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2613\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000112e4);
if((readl(ivp_cae_base_addr+0x000112e4)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2614\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000112e8);
if((readl(ivp_cae_base_addr+0x000112e8)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2615\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000112e8);
if((readl(ivp_cae_base_addr+0x000112e8)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2616\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000112e8);
if((readl(ivp_cae_base_addr+0x000112e8)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2617\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000112e8);
if((readl(ivp_cae_base_addr+0x000112e8)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2618\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000112e8);
if((readl(ivp_cae_base_addr+0x000112e8)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2619\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000112e8);
if((readl(ivp_cae_base_addr+0x000112e8)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2620\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000112ec);
if((readl(ivp_cae_base_addr+0x000112ec)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2621\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000112ec);
if((readl(ivp_cae_base_addr+0x000112ec)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2622\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000112ec);
if((readl(ivp_cae_base_addr+0x000112ec)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2623\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000112ec);
if((readl(ivp_cae_base_addr+0x000112ec)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2624\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000112ec);
if((readl(ivp_cae_base_addr+0x000112ec)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2625\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000112ec);
if((readl(ivp_cae_base_addr+0x000112ec)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2626\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000112f0);
if((readl(ivp_cae_base_addr+0x000112f0)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2627\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000112f0);
if((readl(ivp_cae_base_addr+0x000112f0)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2628\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000112f0);
if((readl(ivp_cae_base_addr+0x000112f0)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2629\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000112f0);
if((readl(ivp_cae_base_addr+0x000112f0)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2630\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000112f0);
if((readl(ivp_cae_base_addr+0x000112f0)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2631\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000112f0);
if((readl(ivp_cae_base_addr+0x000112f0)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2632\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011300);
if((readl(ivp_cae_base_addr+0x00011300)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2633\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011300);
if((readl(ivp_cae_base_addr+0x00011300)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2634\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011300);
if((readl(ivp_cae_base_addr+0x00011300)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2635\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011300);
if((readl(ivp_cae_base_addr+0x00011300)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2636\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011300);
if((readl(ivp_cae_base_addr+0x00011300)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2637\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011300);
if((readl(ivp_cae_base_addr+0x00011300)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2638\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011304);
if((readl(ivp_cae_base_addr+0x00011304)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2639\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011304);
if((readl(ivp_cae_base_addr+0x00011304)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2640\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011304);
if((readl(ivp_cae_base_addr+0x00011304)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2641\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011304);
if((readl(ivp_cae_base_addr+0x00011304)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2642\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011304);
if((readl(ivp_cae_base_addr+0x00011304)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2643\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011304);
if((readl(ivp_cae_base_addr+0x00011304)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2644\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011308);
if((readl(ivp_cae_base_addr+0x00011308)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2645\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011308);
if((readl(ivp_cae_base_addr+0x00011308)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2646\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011308);
if((readl(ivp_cae_base_addr+0x00011308)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2647\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011308);
if((readl(ivp_cae_base_addr+0x00011308)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2648\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011308);
if((readl(ivp_cae_base_addr+0x00011308)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2649\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011308);
if((readl(ivp_cae_base_addr+0x00011308)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2650\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001130c);
if((readl(ivp_cae_base_addr+0x0001130c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2651\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001130c);
if((readl(ivp_cae_base_addr+0x0001130c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2652\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001130c);
if((readl(ivp_cae_base_addr+0x0001130c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2653\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001130c);
if((readl(ivp_cae_base_addr+0x0001130c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2654\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001130c);
if((readl(ivp_cae_base_addr+0x0001130c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2655\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001130c);
if((readl(ivp_cae_base_addr+0x0001130c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2656\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011310);
if((readl(ivp_cae_base_addr+0x00011310)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2657\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011310);
if((readl(ivp_cae_base_addr+0x00011310)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2658\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011310);
if((readl(ivp_cae_base_addr+0x00011310)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2659\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011310);
if((readl(ivp_cae_base_addr+0x00011310)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2660\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011310);
if((readl(ivp_cae_base_addr+0x00011310)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2661\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011310);
if((readl(ivp_cae_base_addr+0x00011310)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2662\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011314);
if((readl(ivp_cae_base_addr+0x00011314)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2663\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011314);
if((readl(ivp_cae_base_addr+0x00011314)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2664\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011314);
if((readl(ivp_cae_base_addr+0x00011314)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2665\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011314);
if((readl(ivp_cae_base_addr+0x00011314)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2666\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011314);
if((readl(ivp_cae_base_addr+0x00011314)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2667\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011314);
if((readl(ivp_cae_base_addr+0x00011314)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2668\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011318);
if((readl(ivp_cae_base_addr+0x00011318)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2669\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011318);
if((readl(ivp_cae_base_addr+0x00011318)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2670\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011318);
if((readl(ivp_cae_base_addr+0x00011318)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2671\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011318);
if((readl(ivp_cae_base_addr+0x00011318)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2672\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011318);
if((readl(ivp_cae_base_addr+0x00011318)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2673\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011318);
if((readl(ivp_cae_base_addr+0x00011318)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2674\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001131c);
if((readl(ivp_cae_base_addr+0x0001131c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2675\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001131c);
if((readl(ivp_cae_base_addr+0x0001131c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2676\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001131c);
if((readl(ivp_cae_base_addr+0x0001131c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2677\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001131c);
if((readl(ivp_cae_base_addr+0x0001131c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2678\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001131c);
if((readl(ivp_cae_base_addr+0x0001131c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2679\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001131c);
if((readl(ivp_cae_base_addr+0x0001131c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2680\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011320);
if((readl(ivp_cae_base_addr+0x00011320)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2681\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011320);
if((readl(ivp_cae_base_addr+0x00011320)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2682\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011320);
if((readl(ivp_cae_base_addr+0x00011320)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2683\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011320);
if((readl(ivp_cae_base_addr+0x00011320)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2684\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011320);
if((readl(ivp_cae_base_addr+0x00011320)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2685\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011320);
if((readl(ivp_cae_base_addr+0x00011320)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2686\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011324);
if((readl(ivp_cae_base_addr+0x00011324)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2687\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011324);
if((readl(ivp_cae_base_addr+0x00011324)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2688\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011324);
if((readl(ivp_cae_base_addr+0x00011324)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2689\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011324);
if((readl(ivp_cae_base_addr+0x00011324)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2690\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011324);
if((readl(ivp_cae_base_addr+0x00011324)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2691\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011324);
if((readl(ivp_cae_base_addr+0x00011324)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2692\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011328);
if((readl(ivp_cae_base_addr+0x00011328)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2693\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011328);
if((readl(ivp_cae_base_addr+0x00011328)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2694\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011328);
if((readl(ivp_cae_base_addr+0x00011328)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2695\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011328);
if((readl(ivp_cae_base_addr+0x00011328)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2696\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011328);
if((readl(ivp_cae_base_addr+0x00011328)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2697\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011328);
if((readl(ivp_cae_base_addr+0x00011328)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2698\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001132c);
if((readl(ivp_cae_base_addr+0x0001132c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2699\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001132c);
if((readl(ivp_cae_base_addr+0x0001132c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2700\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001132c);
if((readl(ivp_cae_base_addr+0x0001132c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2701\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001132c);
if((readl(ivp_cae_base_addr+0x0001132c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2702\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001132c);
if((readl(ivp_cae_base_addr+0x0001132c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2703\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001132c);
if((readl(ivp_cae_base_addr+0x0001132c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2704\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011330);
if((readl(ivp_cae_base_addr+0x00011330)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2705\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011330);
if((readl(ivp_cae_base_addr+0x00011330)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2706\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011330);
if((readl(ivp_cae_base_addr+0x00011330)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2707\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011330);
if((readl(ivp_cae_base_addr+0x00011330)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2708\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011330);
if((readl(ivp_cae_base_addr+0x00011330)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2709\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011330);
if((readl(ivp_cae_base_addr+0x00011330)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2710\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011334);
if((readl(ivp_cae_base_addr+0x00011334)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2711\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011334);
if((readl(ivp_cae_base_addr+0x00011334)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2712\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011334);
if((readl(ivp_cae_base_addr+0x00011334)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2713\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011334);
if((readl(ivp_cae_base_addr+0x00011334)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2714\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011334);
if((readl(ivp_cae_base_addr+0x00011334)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2715\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011334);
if((readl(ivp_cae_base_addr+0x00011334)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2716\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011338);
if((readl(ivp_cae_base_addr+0x00011338)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2717\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011338);
if((readl(ivp_cae_base_addr+0x00011338)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2718\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011338);
if((readl(ivp_cae_base_addr+0x00011338)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2719\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011338);
if((readl(ivp_cae_base_addr+0x00011338)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2720\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011338);
if((readl(ivp_cae_base_addr+0x00011338)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2721\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011338);
if((readl(ivp_cae_base_addr+0x00011338)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2722\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001133c);
if((readl(ivp_cae_base_addr+0x0001133c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2723\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001133c);
if((readl(ivp_cae_base_addr+0x0001133c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2724\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001133c);
if((readl(ivp_cae_base_addr+0x0001133c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2725\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001133c);
if((readl(ivp_cae_base_addr+0x0001133c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2726\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001133c);
if((readl(ivp_cae_base_addr+0x0001133c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2727\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001133c);
if((readl(ivp_cae_base_addr+0x0001133c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2728\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011340);
if((readl(ivp_cae_base_addr+0x00011340)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2729\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011340);
if((readl(ivp_cae_base_addr+0x00011340)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2730\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011340);
if((readl(ivp_cae_base_addr+0x00011340)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2731\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011340);
if((readl(ivp_cae_base_addr+0x00011340)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2732\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011340);
if((readl(ivp_cae_base_addr+0x00011340)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2733\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011340);
if((readl(ivp_cae_base_addr+0x00011340)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2734\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011344);
if((readl(ivp_cae_base_addr+0x00011344)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2735\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011344);
if((readl(ivp_cae_base_addr+0x00011344)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2736\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011344);
if((readl(ivp_cae_base_addr+0x00011344)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2737\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011344);
if((readl(ivp_cae_base_addr+0x00011344)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2738\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011344);
if((readl(ivp_cae_base_addr+0x00011344)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2739\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011344);
if((readl(ivp_cae_base_addr+0x00011344)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2740\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011348);
if((readl(ivp_cae_base_addr+0x00011348)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2741\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011348);
if((readl(ivp_cae_base_addr+0x00011348)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2742\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011348);
if((readl(ivp_cae_base_addr+0x00011348)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2743\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011348);
if((readl(ivp_cae_base_addr+0x00011348)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2744\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011348);
if((readl(ivp_cae_base_addr+0x00011348)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2745\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011348);
if((readl(ivp_cae_base_addr+0x00011348)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2746\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001134c);
if((readl(ivp_cae_base_addr+0x0001134c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2747\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001134c);
if((readl(ivp_cae_base_addr+0x0001134c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2748\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001134c);
if((readl(ivp_cae_base_addr+0x0001134c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2749\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001134c);
if((readl(ivp_cae_base_addr+0x0001134c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2750\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001134c);
if((readl(ivp_cae_base_addr+0x0001134c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2751\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001134c);
if((readl(ivp_cae_base_addr+0x0001134c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2752\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011350);
if((readl(ivp_cae_base_addr+0x00011350)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2753\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011350);
if((readl(ivp_cae_base_addr+0x00011350)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2754\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011350);
if((readl(ivp_cae_base_addr+0x00011350)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2755\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011350);
if((readl(ivp_cae_base_addr+0x00011350)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2756\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011350);
if((readl(ivp_cae_base_addr+0x00011350)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2757\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011350);
if((readl(ivp_cae_base_addr+0x00011350)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2758\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011354);
if((readl(ivp_cae_base_addr+0x00011354)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2759\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011354);
if((readl(ivp_cae_base_addr+0x00011354)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2760\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011354);
if((readl(ivp_cae_base_addr+0x00011354)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2761\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011354);
if((readl(ivp_cae_base_addr+0x00011354)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2762\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011354);
if((readl(ivp_cae_base_addr+0x00011354)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2763\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011354);
if((readl(ivp_cae_base_addr+0x00011354)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2764\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011358);
if((readl(ivp_cae_base_addr+0x00011358)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2765\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011358);
if((readl(ivp_cae_base_addr+0x00011358)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2766\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011358);
if((readl(ivp_cae_base_addr+0x00011358)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2767\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011358);
if((readl(ivp_cae_base_addr+0x00011358)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2768\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011358);
if((readl(ivp_cae_base_addr+0x00011358)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2769\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011358);
if((readl(ivp_cae_base_addr+0x00011358)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2770\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001135c);
if((readl(ivp_cae_base_addr+0x0001135c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2771\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001135c);
if((readl(ivp_cae_base_addr+0x0001135c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2772\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001135c);
if((readl(ivp_cae_base_addr+0x0001135c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2773\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001135c);
if((readl(ivp_cae_base_addr+0x0001135c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2774\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001135c);
if((readl(ivp_cae_base_addr+0x0001135c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2775\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001135c);
if((readl(ivp_cae_base_addr+0x0001135c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2776\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011360);
if((readl(ivp_cae_base_addr+0x00011360)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2777\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011360);
if((readl(ivp_cae_base_addr+0x00011360)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2778\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011360);
if((readl(ivp_cae_base_addr+0x00011360)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2779\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011360);
if((readl(ivp_cae_base_addr+0x00011360)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2780\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011360);
if((readl(ivp_cae_base_addr+0x00011360)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2781\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011360);
if((readl(ivp_cae_base_addr+0x00011360)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2782\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011364);
if((readl(ivp_cae_base_addr+0x00011364)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2783\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011364);
if((readl(ivp_cae_base_addr+0x00011364)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2784\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011364);
if((readl(ivp_cae_base_addr+0x00011364)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2785\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011364);
if((readl(ivp_cae_base_addr+0x00011364)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2786\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011364);
if((readl(ivp_cae_base_addr+0x00011364)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2787\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011364);
if((readl(ivp_cae_base_addr+0x00011364)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2788\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011368);
if((readl(ivp_cae_base_addr+0x00011368)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2789\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011368);
if((readl(ivp_cae_base_addr+0x00011368)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2790\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011368);
if((readl(ivp_cae_base_addr+0x00011368)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2791\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011368);
if((readl(ivp_cae_base_addr+0x00011368)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2792\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011368);
if((readl(ivp_cae_base_addr+0x00011368)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2793\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011368);
if((readl(ivp_cae_base_addr+0x00011368)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2794\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001136c);
if((readl(ivp_cae_base_addr+0x0001136c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2795\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001136c);
if((readl(ivp_cae_base_addr+0x0001136c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2796\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001136c);
if((readl(ivp_cae_base_addr+0x0001136c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2797\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001136c);
if((readl(ivp_cae_base_addr+0x0001136c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2798\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001136c);
if((readl(ivp_cae_base_addr+0x0001136c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2799\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001136c);
if((readl(ivp_cae_base_addr+0x0001136c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2800\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011370);
if((readl(ivp_cae_base_addr+0x00011370)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2801\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011370);
if((readl(ivp_cae_base_addr+0x00011370)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2802\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011370);
if((readl(ivp_cae_base_addr+0x00011370)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2803\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011370);
if((readl(ivp_cae_base_addr+0x00011370)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2804\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011370);
if((readl(ivp_cae_base_addr+0x00011370)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2805\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011370);
if((readl(ivp_cae_base_addr+0x00011370)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2806\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011374);
if((readl(ivp_cae_base_addr+0x00011374)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2807\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011374);
if((readl(ivp_cae_base_addr+0x00011374)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2808\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011374);
if((readl(ivp_cae_base_addr+0x00011374)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2809\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011374);
if((readl(ivp_cae_base_addr+0x00011374)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2810\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011374);
if((readl(ivp_cae_base_addr+0x00011374)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2811\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011374);
if((readl(ivp_cae_base_addr+0x00011374)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2812\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011378);
if((readl(ivp_cae_base_addr+0x00011378)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2813\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011378);
if((readl(ivp_cae_base_addr+0x00011378)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2814\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011378);
if((readl(ivp_cae_base_addr+0x00011378)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2815\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011378);
if((readl(ivp_cae_base_addr+0x00011378)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2816\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011378);
if((readl(ivp_cae_base_addr+0x00011378)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2817\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011378);
if((readl(ivp_cae_base_addr+0x00011378)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2818\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001137c);
if((readl(ivp_cae_base_addr+0x0001137c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2819\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001137c);
if((readl(ivp_cae_base_addr+0x0001137c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2820\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001137c);
if((readl(ivp_cae_base_addr+0x0001137c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2821\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001137c);
if((readl(ivp_cae_base_addr+0x0001137c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2822\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001137c);
if((readl(ivp_cae_base_addr+0x0001137c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2823\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001137c);
if((readl(ivp_cae_base_addr+0x0001137c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2824\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011380);
if((readl(ivp_cae_base_addr+0x00011380)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2825\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011380);
if((readl(ivp_cae_base_addr+0x00011380)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2826\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011380);
if((readl(ivp_cae_base_addr+0x00011380)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2827\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011380);
if((readl(ivp_cae_base_addr+0x00011380)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2828\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011380);
if((readl(ivp_cae_base_addr+0x00011380)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2829\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011380);
if((readl(ivp_cae_base_addr+0x00011380)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2830\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011384);
if((readl(ivp_cae_base_addr+0x00011384)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2831\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011384);
if((readl(ivp_cae_base_addr+0x00011384)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2832\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011384);
if((readl(ivp_cae_base_addr+0x00011384)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2833\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011384);
if((readl(ivp_cae_base_addr+0x00011384)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2834\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011384);
if((readl(ivp_cae_base_addr+0x00011384)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2835\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011384);
if((readl(ivp_cae_base_addr+0x00011384)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2836\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011388);
if((readl(ivp_cae_base_addr+0x00011388)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2837\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011388);
if((readl(ivp_cae_base_addr+0x00011388)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2838\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011388);
if((readl(ivp_cae_base_addr+0x00011388)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2839\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011388);
if((readl(ivp_cae_base_addr+0x00011388)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2840\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011388);
if((readl(ivp_cae_base_addr+0x00011388)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2841\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011388);
if((readl(ivp_cae_base_addr+0x00011388)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2842\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001138c);
if((readl(ivp_cae_base_addr+0x0001138c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2843\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001138c);
if((readl(ivp_cae_base_addr+0x0001138c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2844\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001138c);
if((readl(ivp_cae_base_addr+0x0001138c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2845\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001138c);
if((readl(ivp_cae_base_addr+0x0001138c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2846\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001138c);
if((readl(ivp_cae_base_addr+0x0001138c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2847\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001138c);
if((readl(ivp_cae_base_addr+0x0001138c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2848\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011390);
if((readl(ivp_cae_base_addr+0x00011390)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2849\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011390);
if((readl(ivp_cae_base_addr+0x00011390)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2850\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011390);
if((readl(ivp_cae_base_addr+0x00011390)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2851\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011390);
if((readl(ivp_cae_base_addr+0x00011390)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2852\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011390);
if((readl(ivp_cae_base_addr+0x00011390)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2853\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011390);
if((readl(ivp_cae_base_addr+0x00011390)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2854\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011394);
if((readl(ivp_cae_base_addr+0x00011394)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2855\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011394);
if((readl(ivp_cae_base_addr+0x00011394)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2856\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011394);
if((readl(ivp_cae_base_addr+0x00011394)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2857\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011394);
if((readl(ivp_cae_base_addr+0x00011394)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2858\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011394);
if((readl(ivp_cae_base_addr+0x00011394)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2859\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011394);
if((readl(ivp_cae_base_addr+0x00011394)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2860\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011398);
if((readl(ivp_cae_base_addr+0x00011398)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2861\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011398);
if((readl(ivp_cae_base_addr+0x00011398)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2862\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011398);
if((readl(ivp_cae_base_addr+0x00011398)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2863\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011398);
if((readl(ivp_cae_base_addr+0x00011398)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2864\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011398);
if((readl(ivp_cae_base_addr+0x00011398)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2865\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011398);
if((readl(ivp_cae_base_addr+0x00011398)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2866\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001139c);
if((readl(ivp_cae_base_addr+0x0001139c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2867\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001139c);
if((readl(ivp_cae_base_addr+0x0001139c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2868\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001139c);
if((readl(ivp_cae_base_addr+0x0001139c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2869\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001139c);
if((readl(ivp_cae_base_addr+0x0001139c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2870\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001139c);
if((readl(ivp_cae_base_addr+0x0001139c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2871\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001139c);
if((readl(ivp_cae_base_addr+0x0001139c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2872\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000113c0);
if((readl(ivp_cae_base_addr+0x000113c0)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2873\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000113c0);
if((readl(ivp_cae_base_addr+0x000113c0)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2874\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000113c0);
if((readl(ivp_cae_base_addr+0x000113c0)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2875\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000113c0);
if((readl(ivp_cae_base_addr+0x000113c0)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2876\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000113c0);
if((readl(ivp_cae_base_addr+0x000113c0)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2877\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000113c0);
if((readl(ivp_cae_base_addr+0x000113c0)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2878\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000113c4);
if((readl(ivp_cae_base_addr+0x000113c4)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2879\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000113c4);
if((readl(ivp_cae_base_addr+0x000113c4)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2880\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000113c4);
if((readl(ivp_cae_base_addr+0x000113c4)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2881\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000113c4);
if((readl(ivp_cae_base_addr+0x000113c4)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2882\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000113c4);
if((readl(ivp_cae_base_addr+0x000113c4)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2883\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000113c4);
if((readl(ivp_cae_base_addr+0x000113c4)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2884\n");
writel(0x00000001&0xffffffff,ivp_cae_base_addr+0x000113c8);
if((readl(ivp_cae_base_addr+0x000113c8)&0x0000000f)==(0x00000001&0x0000000f))
cnt++;
else
printf("cnt: 2885\n");
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x000113c8);
if((readl(ivp_cae_base_addr+0x000113c8)&0x0000000f)==(0x00000002&0x0000000f))
cnt++;
else
printf("cnt: 2886\n");
writel(0x00000004&0xffffffff,ivp_cae_base_addr+0x000113c8);
if((readl(ivp_cae_base_addr+0x000113c8)&0x0000000f)==(0x00000004&0x0000000f))
cnt++;
else
printf("cnt: 2887\n");
writel(0x00000008&0xffffffff,ivp_cae_base_addr+0x000113c8);
if((readl(ivp_cae_base_addr+0x000113c8)&0x0000000f)==(0x00000008&0x0000000f))
cnt++;
else
printf("cnt: 2888\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000113c8);
if((readl(ivp_cae_base_addr+0x000113c8)&0x0000000f)==(0x00000000&0x0000000f))
cnt++;
else
printf("cnt: 2889\n");
writel(0x0000000f&0xffffffff,ivp_cae_base_addr+0x000113c8);
if((readl(ivp_cae_base_addr+0x000113c8)&0x0000000f)==(0x0000000f&0x0000000f))
cnt++;
else
printf("cnt: 2890\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000113cc);
if((readl(ivp_cae_base_addr+0x000113cc)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2891\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000113cc);
if((readl(ivp_cae_base_addr+0x000113cc)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2892\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000113cc);
if((readl(ivp_cae_base_addr+0x000113cc)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2893\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000113cc);
if((readl(ivp_cae_base_addr+0x000113cc)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2894\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000113cc);
if((readl(ivp_cae_base_addr+0x000113cc)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2895\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000113cc);
if((readl(ivp_cae_base_addr+0x000113cc)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2896\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000113d0);
if((readl(ivp_cae_base_addr+0x000113d0)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2897\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000113d0);
if((readl(ivp_cae_base_addr+0x000113d0)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2898\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000113d0);
if((readl(ivp_cae_base_addr+0x000113d0)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2899\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000113d0);
if((readl(ivp_cae_base_addr+0x000113d0)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2900\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000113d0);
if((readl(ivp_cae_base_addr+0x000113d0)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2901\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000113d0);
if((readl(ivp_cae_base_addr+0x000113d0)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2902\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000113d4);
if((readl(ivp_cae_base_addr+0x000113d4)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2903\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000113d4);
if((readl(ivp_cae_base_addr+0x000113d4)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2904\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000113d4);
if((readl(ivp_cae_base_addr+0x000113d4)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2905\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000113d4);
if((readl(ivp_cae_base_addr+0x000113d4)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2906\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000113d4);
if((readl(ivp_cae_base_addr+0x000113d4)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2907\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000113d4);
if((readl(ivp_cae_base_addr+0x000113d4)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2908\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000113d8);
if((readl(ivp_cae_base_addr+0x000113d8)&0x000001bf)==(0x00000004&0x000001bf))
cnt++;
else
printf("cnt: 2909\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000113d8);
if((readl(ivp_cae_base_addr+0x000113d8)&0x000001bf)==(0x00000004&0x000001bf))
cnt++;
else
printf("cnt: 2910\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000113d8);
if((readl(ivp_cae_base_addr+0x000113d8)&0x000001bf)==(0x00000004&0x000001bf))
cnt++;
else
printf("cnt: 2911\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000113d8);
if((readl(ivp_cae_base_addr+0x000113d8)&0x000001bf)==(0x00000004&0x000001bf))
cnt++;
else
printf("cnt: 2912\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000113d8);
if((readl(ivp_cae_base_addr+0x000113d8)&0x000001bf)==(0x00000004&0x000001bf))
cnt++;
else
printf("cnt: 2913\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000113d8);
if((readl(ivp_cae_base_addr+0x000113d8)&0x000001bf)==(0x00000004&0x000001bf))
cnt++;
else
printf("cnt: 2914\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000113dc);
if((readl(ivp_cae_base_addr+0x000113dc)&0x0fffffff)==(0x014036c9&0x0fffffff))
cnt++;
else
printf("cnt: 2915\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000113dc);
if((readl(ivp_cae_base_addr+0x000113dc)&0x0fffffff)==(0x014036c9&0x0fffffff))
cnt++;
else
printf("cnt: 2916\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000113dc);
if((readl(ivp_cae_base_addr+0x000113dc)&0x0fffffff)==(0x014036c9&0x0fffffff))
cnt++;
else
printf("cnt: 2917\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000113dc);
if((readl(ivp_cae_base_addr+0x000113dc)&0x0fffffff)==(0x014036c9&0x0fffffff))
cnt++;
else
printf("cnt: 2918\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000113dc);
if((readl(ivp_cae_base_addr+0x000113dc)&0x0fffffff)==(0x014036c9&0x0fffffff))
cnt++;
else
printf("cnt: 2919\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000113dc);
if((readl(ivp_cae_base_addr+0x000113dc)&0x0fffffff)==(0x014036c9&0x0fffffff))
cnt++;
else
printf("cnt: 2920\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000113f8);
if((readl(ivp_cae_base_addr+0x000113f8)&0xffffffe0)==(0x7fc1fc00&0xffffffe0))
cnt++;
else
printf("cnt: 2921\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000113f8);
if((readl(ivp_cae_base_addr+0x000113f8)&0xffffffe0)==(0x7fc1fc00&0xffffffe0))
cnt++;
else
printf("cnt: 2922\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000113f8);
if((readl(ivp_cae_base_addr+0x000113f8)&0xffffffe0)==(0x7fc1fc00&0xffffffe0))
cnt++;
else
printf("cnt: 2923\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000113f8);
if((readl(ivp_cae_base_addr+0x000113f8)&0xffffffe0)==(0x7fc1fc00&0xffffffe0))
cnt++;
else
printf("cnt: 2924\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000113f8);
if((readl(ivp_cae_base_addr+0x000113f8)&0xffffffe0)==(0x7fc1fc00&0xffffffe0))
cnt++;
else
printf("cnt: 2925\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000113f8);
if((readl(ivp_cae_base_addr+0x000113f8)&0xffffffe0)==(0x7fc1fc00&0xffffffe0))
cnt++;
else
printf("cnt: 2926\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000113fc);
if((readl(ivp_cae_base_addr+0x000113fc)&0x0fffffff)==(0x04339f60&0x0fffffff))
cnt++;
else
printf("cnt: 2927\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000113fc);
if((readl(ivp_cae_base_addr+0x000113fc)&0x0fffffff)==(0x04339f60&0x0fffffff))
cnt++;
else
printf("cnt: 2928\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000113fc);
if((readl(ivp_cae_base_addr+0x000113fc)&0x0fffffff)==(0x04339f60&0x0fffffff))
cnt++;
else
printf("cnt: 2929\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000113fc);
if((readl(ivp_cae_base_addr+0x000113fc)&0x0fffffff)==(0x04339f60&0x0fffffff))
cnt++;
else
printf("cnt: 2930\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000113fc);
if((readl(ivp_cae_base_addr+0x000113fc)&0x0fffffff)==(0x04339f60&0x0fffffff))
cnt++;
else
printf("cnt: 2931\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000113fc);
if((readl(ivp_cae_base_addr+0x000113fc)&0x0fffffff)==(0x04339f60&0x0fffffff))
cnt++;
else
printf("cnt: 2932\n");
writel(0x00000011&0xffffffff,ivp_cae_base_addr+0x00011c00);
if((readl(ivp_cae_base_addr+0x00011c00)&0xc00000ff)==(0x00000011&0xc00000ff))
cnt++;
else
printf("cnt: 2933\n");
writel(0x00000022&0xffffffff,ivp_cae_base_addr+0x00011c00);
if((readl(ivp_cae_base_addr+0x00011c00)&0xc00000ff)==(0x00000022&0xc00000ff))
cnt++;
else
printf("cnt: 2934\n");
writel(0x40000044&0xffffffff,ivp_cae_base_addr+0x00011c00);
if((readl(ivp_cae_base_addr+0x00011c00)&0xc00000ff)==(0x40000044&0xc00000ff))
cnt++;
else
printf("cnt: 2935\n");
writel(0x80000088&0xffffffff,ivp_cae_base_addr+0x00011c00);
if((readl(ivp_cae_base_addr+0x00011c00)&0xc00000ff)==(0x80000088&0xc00000ff))
cnt++;
else
printf("cnt: 2936\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011c00);
if((readl(ivp_cae_base_addr+0x00011c00)&0xc00000ff)==(0x00000000&0xc00000ff))
cnt++;
else
printf("cnt: 2937\n");
writel(0xc00000ff&0xffffffff,ivp_cae_base_addr+0x00011c00);
if((readl(ivp_cae_base_addr+0x00011c00)&0xc00000ff)==(0xc00000ff&0xc00000ff))
cnt++;
else
printf("cnt: 2938\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011d00);
if((readl(ivp_cae_base_addr+0x00011d00)&0xc0000000)==(0x00000000&0xc0000000))
cnt++;
else
printf("cnt: 2939\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011d00);
if((readl(ivp_cae_base_addr+0x00011d00)&0xc0000000)==(0x00000000&0xc0000000))
cnt++;
else
printf("cnt: 2940\n");
writel(0x40000000&0xffffffff,ivp_cae_base_addr+0x00011d00);
if((readl(ivp_cae_base_addr+0x00011d00)&0xc0000000)==(0x40000000&0xc0000000))
cnt++;
else
printf("cnt: 2941\n");
writel(0x80000000&0xffffffff,ivp_cae_base_addr+0x00011d00);
if((readl(ivp_cae_base_addr+0x00011d00)&0xc0000000)==(0x80000000&0xc0000000))
cnt++;
else
printf("cnt: 2942\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011d00);
if((readl(ivp_cae_base_addr+0x00011d00)&0xc0000000)==(0x00000000&0xc0000000))
cnt++;
else
printf("cnt: 2943\n");
writel(0xc0000000&0xffffffff,ivp_cae_base_addr+0x00011d00);
if((readl(ivp_cae_base_addr+0x00011d00)&0xc0000000)==(0xc0000000&0xc0000000))
cnt++;
else
printf("cnt: 2944\n");
writel(0x00000011&0xffffffff,ivp_cae_base_addr+0x00011f00);
if((readl(ivp_cae_base_addr+0x00011f00)&0x0000001f)==(0x00000011&0x0000001f))
cnt++;
else
printf("cnt: 2945\n");
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x00011f00);
if((readl(ivp_cae_base_addr+0x00011f00)&0x0000001f)==(0x00000002&0x0000001f))
cnt++;
else
printf("cnt: 2946\n");
writel(0x00000004&0xffffffff,ivp_cae_base_addr+0x00011f00);
if((readl(ivp_cae_base_addr+0x00011f00)&0x0000001f)==(0x00000004&0x0000001f))
cnt++;
else
printf("cnt: 2947\n");
writel(0x00000008&0xffffffff,ivp_cae_base_addr+0x00011f00);
if((readl(ivp_cae_base_addr+0x00011f00)&0x0000001f)==(0x00000008&0x0000001f))
cnt++;
else
printf("cnt: 2948\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011f00);
if((readl(ivp_cae_base_addr+0x00011f00)&0x0000001f)==(0x00000000&0x0000001f))
cnt++;
else
printf("cnt: 2949\n");
writel(0x0000001f&0xffffffff,ivp_cae_base_addr+0x00011f00);
if((readl(ivp_cae_base_addr+0x00011f00)&0x0000001f)==(0x0000001f&0x0000001f))
cnt++;
else
printf("cnt: 2950\n");
writel(0x00000011&0xffffffff,ivp_cae_base_addr+0x00011f04);
if((readl(ivp_cae_base_addr+0x00011f04)&0x0000001f)==(0x00000011&0x0000001f))
cnt++;
else
printf("cnt: 2951\n");
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x00011f04);
if((readl(ivp_cae_base_addr+0x00011f04)&0x0000001f)==(0x00000002&0x0000001f))
cnt++;
else
printf("cnt: 2952\n");
writel(0x00000004&0xffffffff,ivp_cae_base_addr+0x00011f04);
if((readl(ivp_cae_base_addr+0x00011f04)&0x0000001f)==(0x00000004&0x0000001f))
cnt++;
else
printf("cnt: 2953\n");
writel(0x00000008&0xffffffff,ivp_cae_base_addr+0x00011f04);
if((readl(ivp_cae_base_addr+0x00011f04)&0x0000001f)==(0x00000008&0x0000001f))
cnt++;
else
printf("cnt: 2954\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011f04);
if((readl(ivp_cae_base_addr+0x00011f04)&0x0000001f)==(0x00000000&0x0000001f))
cnt++;
else
printf("cnt: 2955\n");
writel(0x0000001f&0xffffffff,ivp_cae_base_addr+0x00011f04);
if((readl(ivp_cae_base_addr+0x00011f04)&0x0000001f)==(0x0000001f&0x0000001f))
cnt++;
else
printf("cnt: 2956\n");
writel(0x00000011&0xffffffff,ivp_cae_base_addr+0x00011f08);
if((readl(ivp_cae_base_addr+0x00011f08)&0x0000001f)==(0x00000011&0x0000001f))
cnt++;
else
printf("cnt: 2957\n");
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x00011f08);
if((readl(ivp_cae_base_addr+0x00011f08)&0x0000001f)==(0x00000002&0x0000001f))
cnt++;
else
printf("cnt: 2958\n");
writel(0x00000004&0xffffffff,ivp_cae_base_addr+0x00011f08);
if((readl(ivp_cae_base_addr+0x00011f08)&0x0000001f)==(0x00000004&0x0000001f))
cnt++;
else
printf("cnt: 2959\n");
writel(0x00000008&0xffffffff,ivp_cae_base_addr+0x00011f08);
if((readl(ivp_cae_base_addr+0x00011f08)&0x0000001f)==(0x00000008&0x0000001f))
cnt++;
else
printf("cnt: 2960\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011f08);
if((readl(ivp_cae_base_addr+0x00011f08)&0x0000001f)==(0x00000000&0x0000001f))
cnt++;
else
printf("cnt: 2961\n");
writel(0x0000001f&0xffffffff,ivp_cae_base_addr+0x00011f08);
if((readl(ivp_cae_base_addr+0x00011f08)&0x0000001f)==(0x0000001f&0x0000001f))
cnt++;
else
printf("cnt: 2962\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011f0c);
if((readl(ivp_cae_base_addr+0x00011f0c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2963\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011f0c);
if((readl(ivp_cae_base_addr+0x00011f0c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2964\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011f0c);
if((readl(ivp_cae_base_addr+0x00011f0c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2965\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011f0c);
if((readl(ivp_cae_base_addr+0x00011f0c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2966\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011f0c);
if((readl(ivp_cae_base_addr+0x00011f0c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2967\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011f0c);
if((readl(ivp_cae_base_addr+0x00011f0c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2968\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011f10);
if((readl(ivp_cae_base_addr+0x00011f10)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2969\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011f10);
if((readl(ivp_cae_base_addr+0x00011f10)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2970\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011f10);
if((readl(ivp_cae_base_addr+0x00011f10)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2971\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011f10);
if((readl(ivp_cae_base_addr+0x00011f10)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2972\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011f10);
if((readl(ivp_cae_base_addr+0x00011f10)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2973\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011f10);
if((readl(ivp_cae_base_addr+0x00011f10)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2974\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011f14);
if((readl(ivp_cae_base_addr+0x00011f14)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2975\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011f14);
if((readl(ivp_cae_base_addr+0x00011f14)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2976\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011f14);
if((readl(ivp_cae_base_addr+0x00011f14)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2977\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011f14);
if((readl(ivp_cae_base_addr+0x00011f14)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2978\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011f14);
if((readl(ivp_cae_base_addr+0x00011f14)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2979\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011f14);
if((readl(ivp_cae_base_addr+0x00011f14)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2980\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011f18);
if((readl(ivp_cae_base_addr+0x00011f18)&0x000001bf)==(0x00000005&0x000001bf))
cnt++;
else
printf("cnt: 2981\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011f18);
if((readl(ivp_cae_base_addr+0x00011f18)&0x000001bf)==(0x00000005&0x000001bf))
cnt++;
else
printf("cnt: 2982\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011f18);
if((readl(ivp_cae_base_addr+0x00011f18)&0x000001bf)==(0x00000005&0x000001bf))
cnt++;
else
printf("cnt: 2983\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011f18);
if((readl(ivp_cae_base_addr+0x00011f18)&0x000001bf)==(0x00000005&0x000001bf))
cnt++;
else
printf("cnt: 2984\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011f18);
if((readl(ivp_cae_base_addr+0x00011f18)&0x000001bf)==(0x00000005&0x000001bf))
cnt++;
else
printf("cnt: 2985\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011f18);
if((readl(ivp_cae_base_addr+0x00011f18)&0x000001bf)==(0x00000005&0x000001bf))
cnt++;
else
printf("cnt: 2986\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011f1c);
if((readl(ivp_cae_base_addr+0x00011f1c)&0x0fffffff)==(0x014036c9&0x0fffffff))
cnt++;
else
printf("cnt: 2987\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011f1c);
if((readl(ivp_cae_base_addr+0x00011f1c)&0x0fffffff)==(0x014036c9&0x0fffffff))
cnt++;
else
printf("cnt: 2988\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011f1c);
if((readl(ivp_cae_base_addr+0x00011f1c)&0x0fffffff)==(0x014036c9&0x0fffffff))
cnt++;
else
printf("cnt: 2989\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011f1c);
if((readl(ivp_cae_base_addr+0x00011f1c)&0x0fffffff)==(0x014036c9&0x0fffffff))
cnt++;
else
printf("cnt: 2990\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011f1c);
if((readl(ivp_cae_base_addr+0x00011f1c)&0x0fffffff)==(0x014036c9&0x0fffffff))
cnt++;
else
printf("cnt: 2991\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011f1c);
if((readl(ivp_cae_base_addr+0x00011f1c)&0x0fffffff)==(0x014036c9&0x0fffffff))
cnt++;
else
printf("cnt: 2992\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011ff0);
if((readl(ivp_cae_base_addr+0x00011ff0)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2993\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011ff0);
if((readl(ivp_cae_base_addr+0x00011ff0)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2994\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011ff0);
if((readl(ivp_cae_base_addr+0x00011ff0)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2995\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011ff0);
if((readl(ivp_cae_base_addr+0x00011ff0)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2996\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011ff0);
if((readl(ivp_cae_base_addr+0x00011ff0)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2997\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011ff0);
if((readl(ivp_cae_base_addr+0x00011ff0)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 2998\n");
writel(0x00000001&0xffffffff,ivp_cae_base_addr+0x00011ff4);
if((readl(ivp_cae_base_addr+0x00011ff4)&0x80000001)==(0x00000001&0x80000001))
cnt++;
else
printf("cnt: 2999\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011ff4);
if((readl(ivp_cae_base_addr+0x00011ff4)&0x80000001)==(0x00000000&0x80000001))
cnt++;
else
printf("cnt: 3000\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011ff4);
if((readl(ivp_cae_base_addr+0x00011ff4)&0x80000001)==(0x00000000&0x80000001))
cnt++;
else
printf("cnt: 3001\n");
writel(0x80000000&0xffffffff,ivp_cae_base_addr+0x00011ff4);
if((readl(ivp_cae_base_addr+0x00011ff4)&0x80000001)==(0x80000000&0x80000001))
cnt++;
else
printf("cnt: 3002\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011ff4);
if((readl(ivp_cae_base_addr+0x00011ff4)&0x80000001)==(0x00000000&0x80000001))
cnt++;
else
printf("cnt: 3003\n");
writel(0x80000001&0xffffffff,ivp_cae_base_addr+0x00011ff4);
if((readl(ivp_cae_base_addr+0x00011ff4)&0x80000001)==(0x80000001&0x80000001))
cnt++;
else
printf("cnt: 3004\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011ff8);
if((readl(ivp_cae_base_addr+0x00011ff8)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3005\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011ff8);
if((readl(ivp_cae_base_addr+0x00011ff8)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3006\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011ff8);
if((readl(ivp_cae_base_addr+0x00011ff8)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3007\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011ff8);
if((readl(ivp_cae_base_addr+0x00011ff8)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3008\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011ff8);
if((readl(ivp_cae_base_addr+0x00011ff8)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3009\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011ff8);
if((readl(ivp_cae_base_addr+0x00011ff8)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3010\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011ffc);
if((readl(ivp_cae_base_addr+0x00011ffc)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3011\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011ffc);
if((readl(ivp_cae_base_addr+0x00011ffc)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3012\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011ffc);
if((readl(ivp_cae_base_addr+0x00011ffc)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3013\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011ffc);
if((readl(ivp_cae_base_addr+0x00011ffc)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3014\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011ffc);
if((readl(ivp_cae_base_addr+0x00011ffc)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3015\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011ffc);
if((readl(ivp_cae_base_addr+0x00011ffc)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3016\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001ffe4);
if((readl(ivp_cae_base_addr+0x0001ffe4)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3017\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001ffe4);
if((readl(ivp_cae_base_addr+0x0001ffe4)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3018\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001ffe4);
if((readl(ivp_cae_base_addr+0x0001ffe4)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3019\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001ffe4);
if((readl(ivp_cae_base_addr+0x0001ffe4)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3020\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001ffe4);
if((readl(ivp_cae_base_addr+0x0001ffe4)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3021\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001ffe4);
if((readl(ivp_cae_base_addr+0x0001ffe4)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3022\n");
writel(0x00110111&0xffffffff,ivp_cae_base_addr+0x0001ffe8);
if((readl(ivp_cae_base_addr+0x0001ffe8)&0x087b031f)==(0x00110111&0x087b031f))
cnt++;
else
printf("cnt: 3023\n");
writel(0x00220202&0xffffffff,ivp_cae_base_addr+0x0001ffe8);
if((readl(ivp_cae_base_addr+0x0001ffe8)&0x087b031f)==(0x00220202&0x087b031f))
cnt++;
else
printf("cnt: 3024\n");
writel(0x00400004&0xffffffff,ivp_cae_base_addr+0x0001ffe8);
if((readl(ivp_cae_base_addr+0x0001ffe8)&0x087b031f)==(0x00400004&0x087b031f))
cnt++;
else
printf("cnt: 3025\n");
writel(0x08080008&0xffffffff,ivp_cae_base_addr+0x0001ffe8);
if((readl(ivp_cae_base_addr+0x0001ffe8)&0x087b031f)==(0x08080008&0x087b031f))
cnt++;
else
printf("cnt: 3026\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001ffe8);
if((readl(ivp_cae_base_addr+0x0001ffe8)&0x087b031f)==(0x00000000&0x087b031f))
cnt++;
else
printf("cnt: 3027\n");
writel(0x087b031f&0xffffffff,ivp_cae_base_addr+0x0001ffe8);
if((readl(ivp_cae_base_addr+0x0001ffe8)&0x087b031f)==(0x087b031f&0x087b031f))
cnt++;
else
printf("cnt: 3028\n");
readl(ivp_cae_base_addr+0x0001ffec);
writel(0x00110111&0xffffffff,ivp_cae_base_addr+0x0001ffec);
if((readl(ivp_cae_base_addr+0x0001ffec)&0x087b031f)==(0x00110111&0x087b031f))
cnt++;
else
printf("cnt: 3029\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001ffec);
readl(ivp_cae_base_addr+0x0001ffec);
writel(0x00220202&0xffffffff,ivp_cae_base_addr+0x0001ffec);
if((readl(ivp_cae_base_addr+0x0001ffec)&0x087b031f)==(0x00220202&0x087b031f))
cnt++;
else
printf("cnt: 3030\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001ffec);
readl(ivp_cae_base_addr+0x0001ffec);
writel(0x00400004&0xffffffff,ivp_cae_base_addr+0x0001ffec);
if((readl(ivp_cae_base_addr+0x0001ffec)&0x087b031f)==(0x00400004&0x087b031f))
cnt++;
else
printf("cnt: 3031\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001ffec);
readl(ivp_cae_base_addr+0x0001ffec);
writel(0x08080008&0xffffffff,ivp_cae_base_addr+0x0001ffec);
if((readl(ivp_cae_base_addr+0x0001ffec)&0x087b031f)==(0x08080008&0x087b031f))
cnt++;
else
printf("cnt: 3032\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001ffec);
readl(ivp_cae_base_addr+0x0001ffec);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001ffec);
if((readl(ivp_cae_base_addr+0x0001ffec)&0x087b031f)==(0x00000000&0x087b031f))
cnt++;
else
printf("cnt: 3033\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001ffec);
readl(ivp_cae_base_addr+0x0001ffec);
writel(0x087b031f&0xffffffff,ivp_cae_base_addr+0x0001ffec);
if((readl(ivp_cae_base_addr+0x0001ffec)&0x087b031f)==(0x087b031f&0x087b031f))
cnt++;
else
printf("cnt: 3034\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001ffec);
writel(0x00000111&0xffffffff,ivp_cae_base_addr+0x0001fff4);
if((readl(ivp_cae_base_addr+0x0001fff4)&0x000401ff)==(0x00000111&0x000401ff))
cnt++;
else
printf("cnt: 3035\n");
writel(0x00000022&0xffffffff,ivp_cae_base_addr+0x0001fff4);
if((readl(ivp_cae_base_addr+0x0001fff4)&0x000401ff)==(0x00000022&0x000401ff))
cnt++;
else
printf("cnt: 3036\n");
writel(0x00040044&0xffffffff,ivp_cae_base_addr+0x0001fff4);
if((readl(ivp_cae_base_addr+0x0001fff4)&0x000401ff)==(0x00040044&0x000401ff))
cnt++;
else
printf("cnt: 3037\n");
writel(0x00000088&0xffffffff,ivp_cae_base_addr+0x0001fff4);
if((readl(ivp_cae_base_addr+0x0001fff4)&0x000401ff)==(0x00000088&0x000401ff))
cnt++;
else
printf("cnt: 3038\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001fff4);
if((readl(ivp_cae_base_addr+0x0001fff4)&0x000401ff)==(0x00000000&0x000401ff))
cnt++;
else
printf("cnt: 3039\n");
writel(0x000401ff&0xffffffff,ivp_cae_base_addr+0x0001fff4);
if((readl(ivp_cae_base_addr+0x0001fff4)&0x000401ff)==(0x000401ff&0x000401ff))
cnt++;
else
printf("cnt: 3040\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001fff8);
if((readl(ivp_cae_base_addr+0x0001fff8)&0xc00fffff)==(0x00074751&0xc00fffff))
cnt++;
else
printf("cnt: 3041\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001fff8);
if((readl(ivp_cae_base_addr+0x0001fff8)&0xc00fffff)==(0x00074751&0xc00fffff))
cnt++;
else
printf("cnt: 3042\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001fff8);
if((readl(ivp_cae_base_addr+0x0001fff8)&0xc00fffff)==(0x00074751&0xc00fffff))
cnt++;
else
printf("cnt: 3043\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001fff8);
if((readl(ivp_cae_base_addr+0x0001fff8)&0xc00fffff)==(0x00074751&0xc00fffff))
cnt++;
else
printf("cnt: 3044\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001fff8);
if((readl(ivp_cae_base_addr+0x0001fff8)&0xc00fffff)==(0x00074751&0xc00fffff))
cnt++;
else
printf("cnt: 3045\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001fff8);
if((readl(ivp_cae_base_addr+0x0001fff8)&0xc00fffff)==(0x00074751&0xc00fffff))
cnt++;
else
printf("cnt: 3046\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001fffc);
if((readl(ivp_cae_base_addr+0x0001fffc)&0x0fffffff)==(0x02319e61&0x0fffffff))
cnt++;
else
printf("cnt: 3047\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001fffc);
if((readl(ivp_cae_base_addr+0x0001fffc)&0x0fffffff)==(0x02319e61&0x0fffffff))
cnt++;
else
printf("cnt: 3048\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001fffc);
if((readl(ivp_cae_base_addr+0x0001fffc)&0x0fffffff)==(0x02319e61&0x0fffffff))
cnt++;
else
printf("cnt: 3049\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001fffc);
if((readl(ivp_cae_base_addr+0x0001fffc)&0x0fffffff)==(0x02319e61&0x0fffffff))
cnt++;
else
printf("cnt: 3050\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001fffc);
if((readl(ivp_cae_base_addr+0x0001fffc)&0x0fffffff)==(0x02319e61&0x0fffffff))
cnt++;
else
printf("cnt: 3051\n");
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001fffc);
if((readl(ivp_cae_base_addr+0x0001fffc)&0x0fffffff)==(0x02319e61&0x0fffffff))
cnt++;
else
printf("cnt: 3052\n");
writel(0xd82cc209&0xffffffff,ivp_cae_base_addr+0x00000000);
writel(0x6baa4248&0xffffffff,ivp_cae_base_addr+0x00000004);
writel(0x82e267a9&0xffffffff,ivp_cae_base_addr+0x00000008);
writel(0xc8a74da5&0xffffffff,ivp_cae_base_addr+0x0000000c);
writel(0x7a029558&0xffffffff,ivp_cae_base_addr+0x00000010);
writel(0xe87a8133&0xffffffff,ivp_cae_base_addr+0x00000014);
writel(0x0026c17c&0xffffffff,ivp_cae_base_addr+0x00000018);
writel(0x804d0021&0xffffffff,ivp_cae_base_addr+0x0000001c);
writel(0xe0250097&0xffffffff,ivp_cae_base_addr+0x00000020);
writel(0xcf000000&0xffffffff,ivp_cae_base_addr+0x00000024);
writel(0x4f400000&0xffffffff,ivp_cae_base_addr+0x00000028);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00000030);
writel(0x00259c60&0xffffffff,ivp_cae_base_addr+0x00000034);
writel(0x00bbf770&0xffffffff,ivp_cae_base_addr+0x00000038);
writel(0x00000004&0xffffffff,ivp_cae_base_addr+0x0000003c);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000007f8);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000007fc);
writel(0xb83e6619&0xffffffff,ivp_cae_base_addr+0x00000800);
writel(0xd329ab0c&0xffffffff,ivp_cae_base_addr+0x00000804);
writel(0x004a7e5b&0xffffffff,ivp_cae_base_addr+0x00000808);
writel(0xde1b3e70&0xffffffff,ivp_cae_base_addr+0x0000080c);
writel(0x0040ded4&0xffffffff,ivp_cae_base_addr+0x00000818);
writel(0x20e90048&0xffffffff,ivp_cae_base_addr+0x0000081c);
writel(0x301500b0&0xffffffff,ivp_cae_base_addr+0x00000820);
writel(0xcd980000&0xffffffff,ivp_cae_base_addr+0x00000824);
writel(0x14800000&0xffffffff,ivp_cae_base_addr+0x00000828);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00000830);
writel(0x00e18c24&0xffffffff,ivp_cae_base_addr+0x00000834);
writel(0x00808a50&0xffffffff,ivp_cae_base_addr+0x00000838);
writel(0x0000006a&0xffffffff,ivp_cae_base_addr+0x0000083c);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00000ff8);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00000ffc);
writel(0x935d4a53&0xffffffff,ivp_cae_base_addr+0x00001000);
writel(0x307b2fcd&0xffffffff,ivp_cae_base_addr+0x00001004);
writel(0x9cdea81a&0xffffffff,ivp_cae_base_addr+0x00001008);
writel(0x79fd16fe&0xffffffff,ivp_cae_base_addr+0x0000100c);
writel(0xc1f2e074&0xffffffff,ivp_cae_base_addr+0x00001010);
writel(0xec62d7ab&0xffffffff,ivp_cae_base_addr+0x00001014);
writel(0x00eeec4c&0xffffffff,ivp_cae_base_addr+0x00001018);
writel(0x8064002b&0xffffffff,ivp_cae_base_addr+0x0000101c);
writel(0xb00d008f&0xffffffff,ivp_cae_base_addr+0x00001020);
writel(0xcf000101&0xffffffff,ivp_cae_base_addr+0x00001024);
writel(0xe5000000&0xffffffff,ivp_cae_base_addr+0x00001028);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000102c);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00001030);
writel(0x000aeabc&0xffffffff,ivp_cae_base_addr+0x00001034);
writel(0x00171514&0xffffffff,ivp_cae_base_addr+0x00001038);
writel(0x00000007&0xffffffff,ivp_cae_base_addr+0x0000103c);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000017f8);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000017fc);
writel(0x1dfc3870&0xffffffff,ivp_cae_base_addr+0x00001800);
writel(0xcb695521&0xffffffff,ivp_cae_base_addr+0x00001804);
writel(0xd0df19c1&0xffffffff,ivp_cae_base_addr+0x00001808);
writel(0x2577b29a&0xffffffff,ivp_cae_base_addr+0x0000180c);
writel(0x009492e8&0xffffffff,ivp_cae_base_addr+0x00001818);
writel(0xe0f600c1&0xffffffff,ivp_cae_base_addr+0x0000181c);
writel(0xa03b00d5&0xffffffff,ivp_cae_base_addr+0x00001820);
writel(0xa2880100&0xffffffff,ivp_cae_base_addr+0x00001824);
writel(0x93000000&0xffffffff,ivp_cae_base_addr+0x00001828);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000182c);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00001830);
writel(0x00062f58&0xffffffff,ivp_cae_base_addr+0x00001834);
writel(0x00b735e8&0xffffffff,ivp_cae_base_addr+0x00001838);
writel(0x000000dd&0xffffffff,ivp_cae_base_addr+0x0000183c);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00001ff8);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00001ffc);
writel(0x3888a59c&0xffffffff,ivp_cae_base_addr+0x00002000);
writel(0x59ac2e29&0xffffffff,ivp_cae_base_addr+0x00002004);
writel(0x80ee0a14&0xffffffff,ivp_cae_base_addr+0x00002008);
writel(0x19d5fcfc&0xffffffff,ivp_cae_base_addr+0x0000200c);
writel(0x33085bca&0xffffffff,ivp_cae_base_addr+0x00002010);
writel(0xbb4ad69c&0xffffffff,ivp_cae_base_addr+0x00002014);
writel(0x00212b5c&0xffffffff,ivp_cae_base_addr+0x00002018);
writel(0xa032002f&0xffffffff,ivp_cae_base_addr+0x0000201c);
writel(0x001c001b&0xffffffff,ivp_cae_base_addr+0x00002020);
writel(0xd8010101&0xffffffff,ivp_cae_base_addr+0x00002024);
writel(0x40000000&0xffffffff,ivp_cae_base_addr+0x00002028);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000202c);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00002030);
writel(0x00b18230&0xffffffff,ivp_cae_base_addr+0x00002034);
writel(0x00ba5b6c&0xffffffff,ivp_cae_base_addr+0x00002038);
writel(0x0000003d&0xffffffff,ivp_cae_base_addr+0x0000203c);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000027f8);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000027fc);
writel(0x0bb247e7&0xffffffff,ivp_cae_base_addr+0x00002800);
writel(0x3d79f400&0xffffffff,ivp_cae_base_addr+0x00002804);
writel(0x5a2b49b2&0xffffffff,ivp_cae_base_addr+0x00002808);
writel(0x5bf4f268&0xffffffff,ivp_cae_base_addr+0x0000280c);
writel(0x003d9efc&0xffffffff,ivp_cae_base_addr+0x00002818);
writel(0xa0320055&0xffffffff,ivp_cae_base_addr+0x0000281c);
writel(0x6017009c&0xffffffff,ivp_cae_base_addr+0x00002820);
writel(0x00600101&0xffffffff,ivp_cae_base_addr+0x00002824);
writel(0x55800000&0xffffffff,ivp_cae_base_addr+0x00002828);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000282c);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00002830);
writel(0x001666f8&0xffffffff,ivp_cae_base_addr+0x00002834);
writel(0x00ab6b10&0xffffffff,ivp_cae_base_addr+0x00002838);
writel(0x000000f9&0xffffffff,ivp_cae_base_addr+0x0000283c);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00002ff8);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00002ffc);
writel(0x7cbd8fb8&0xffffffff,ivp_cae_base_addr+0x00003000);
writel(0xc167e245&0xffffffff,ivp_cae_base_addr+0x00003004);
writel(0x7e9c4fe3&0xffffffff,ivp_cae_base_addr+0x00003008);
writel(0x7786cf1d&0xffffffff,ivp_cae_base_addr+0x0000300c);
writel(0xe001cffa&0xffffffff,ivp_cae_base_addr+0x00003010);
writel(0x3020ffda&0xffffffff,ivp_cae_base_addr+0x00003014);
writel(0x0012155c&0xffffffff,ivp_cae_base_addr+0x00003018);
writel(0xa0bd0020&0xffffffff,ivp_cae_base_addr+0x0000301c);
writel(0x601d00b3&0xffffffff,ivp_cae_base_addr+0x00003020);
writel(0x50000001&0xffffffff,ivp_cae_base_addr+0x00003024);
writel(0xb7800000&0xffffffff,ivp_cae_base_addr+0x00003028);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000302c);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00003030);
writel(0x0036dfa4&0xffffffff,ivp_cae_base_addr+0x00003034);
writel(0x00acfa7c&0xffffffff,ivp_cae_base_addr+0x00003038);
writel(0x0000001b&0xffffffff,ivp_cae_base_addr+0x0000303c);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000037f8);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000037fc);
writel(0xcad6dc82&0xffffffff,ivp_cae_base_addr+0x00003800);
writel(0x22278557&0xffffffff,ivp_cae_base_addr+0x00003804);
writel(0xa69958d8&0xffffffff,ivp_cae_base_addr+0x00003808);
writel(0xdf324745&0xffffffff,ivp_cae_base_addr+0x0000380c);
writel(0x00c10a68&0xffffffff,ivp_cae_base_addr+0x00003818);
writel(0xa05500f0&0xffffffff,ivp_cae_base_addr+0x0000381c);
writel(0xf00d003d&0xffffffff,ivp_cae_base_addr+0x00003820);
writel(0xe8e80000&0xffffffff,ivp_cae_base_addr+0x00003824);
writel(0xbf800000&0xffffffff,ivp_cae_base_addr+0x00003828);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000382c);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00003830);
writel(0x005889b4&0xffffffff,ivp_cae_base_addr+0x00003834);
writel(0x0035964c&0xffffffff,ivp_cae_base_addr+0x00003838);
writel(0x000000a9&0xffffffff,ivp_cae_base_addr+0x0000383c);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00003ff8);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00003ffc);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000b000);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000b004);
writel(0x00000011&0xffffffff,ivp_cae_base_addr+0x0000b008);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000b00c);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000b010);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000b014);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000b018);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000b01c);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000c000);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000c004);
writel(0x000000ea&0xffffffff,ivp_cae_base_addr+0x0000c008);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000c00c);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000c010);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000c014);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000c018);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000c01c);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000d000);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000d004);
writel(0x000000a7&0xffffffff,ivp_cae_base_addr+0x0000d008);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000d00c);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000d010);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000d014);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000d018);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000d01c);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000e000);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000e004);
writel(0x00000013&0xffffffff,ivp_cae_base_addr+0x0000e008);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000e00c);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000e010);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000e014);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000e018);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000e01c);
writel(0x257702ae&0xffffffff,ivp_cae_base_addr+0x0000f000);
writel(0x00868b80&0xffffffff,ivp_cae_base_addr+0x0000f010);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f078);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f07c);
writel(0x0000000f&0xffffffff,ivp_cae_base_addr+0x0000f200);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f204);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f208);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f210);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f214);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f218);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f21c);
writel(0xe000d170&0xffffffff,ivp_cae_base_addr+0x0000f400);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f478);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f47c);
writel(0x0000000c&0xffffffff,ivp_cae_base_addr+0x0000f600);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f604);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f608);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f60c);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f610);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f614);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f618);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f61c);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f620);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f628);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f62c);
writel(0xce100000&0xffffffff,ivp_cae_base_addr+0x0000f800);
writel(0xfd900000&0xffffffff,ivp_cae_base_addr+0x0000f804);
writel(0xe7e134c3&0xffffffff,ivp_cae_base_addr+0x0000f808);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f80c);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f810);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f814);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f818);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f81c);
writel(0x000f0e91&0xffffffff,ivp_cae_base_addr+0x0000fff4);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000fff8);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000fffc);
writel(0xc0004d00&0xffffffff,ivp_cae_base_addr+0x00010000);
writel(0x0000cf00&0xffffffff,ivp_cae_base_addr+0x00010100);
writel(0x00700000&0xffffffff,ivp_cae_base_addr+0x00011000);
writel(0x2008493e&0xffffffff,ivp_cae_base_addr+0x00011004);
writel(0x00000237&0xffffffff,ivp_cae_base_addr+0x00011008);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001100c);
writel(0x00e80000&0xffffffff,ivp_cae_base_addr+0x00011018);
writel(0x80000068&0xffffffff,ivp_cae_base_addr+0x0001101c);
writel(0x26c0fc98&0xffffffff,ivp_cae_base_addr+0x00011020);
writel(0x69409c9d&0xffffffff,ivp_cae_base_addr+0x00011024);
writel(0x62fd0c0a&0xffffffff,ivp_cae_base_addr+0x00011028);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001102c);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011030);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011040);
writel(0x00000004&0xffffffff,ivp_cae_base_addr+0x00011044);
writel(0x6227c6c3&0xffffffff,ivp_cae_base_addr+0x00011048);
writel(0x7d85e19b&0xffffffff,ivp_cae_base_addr+0x0001104c);
writel(0x9c307799&0xffffffff,ivp_cae_base_addr+0x00011050);
writel(0xa1df567e&0xffffffff,ivp_cae_base_addr+0x00011054);
writel(0x1fd3aeba&0xffffffff,ivp_cae_base_addr+0x00011058);
writel(0x9f3dc9df&0xffffffff,ivp_cae_base_addr+0x0001105c);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011060);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011064);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011068);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001106c);
writel(0xc915306a&0xffffffff,ivp_cae_base_addr+0x00011070);
writel(0xc83871cf&0xffffffff,ivp_cae_base_addr+0x00011074);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011080);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011084);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011088);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001108c);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011090);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011094);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011098);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001109c);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110a0);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110a4);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110a8);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110ac);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110b0);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110b4);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110b8);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110bc);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110c0);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110c4);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110c8);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110cc);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110d0);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110d4);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110d8);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110dc);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110e0);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110e4);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110e8);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110ec);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110f0);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110f4);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110f8);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110fc);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011100);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011104);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011108);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001110c);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011110);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011114);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011118);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001111c);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011140);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011144);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011148);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001114c);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011150);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011154);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011158);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001115c);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011160);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011164);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011168);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001116c);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011170);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011174);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011178);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001117c);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011180);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011184);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011188);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001118c);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011190);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011194);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011198);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001119c);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000111a0);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000111a4);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000111a8);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000111ac);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000111b0);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000111b4);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000111b8);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000111bc);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000111c0);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000111c4);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000111c8);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000111cc);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000111d0);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000111d4);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000111d8);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000111dc);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000111e4);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011200);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011204);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011208);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001120c);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011210);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011214);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011218);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001121c);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011220);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011224);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011228);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001122c);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011230);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011234);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011238);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001123c);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011240);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011244);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011248);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001124c);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011250);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011254);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011258);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001125c);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011260);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011264);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011268);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001126c);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011270);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011274);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011278);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001127c);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011280);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011284);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011288);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001128c);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011290);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011294);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011298);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001129c);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000112a4);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000112c0);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000112c4);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000112c8);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000112cc);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000112d0);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000112d4);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000112d8);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000112dc);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000112e0);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000112e4);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000112e8);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000112ec);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000112f0);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011300);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011304);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011308);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001130c);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011310);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011314);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011318);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001131c);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011320);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011324);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011328);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001132c);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011330);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011334);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011338);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001133c);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011340);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011344);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011348);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001134c);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011350);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011354);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011358);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001135c);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011360);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011364);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011368);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001136c);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011370);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011374);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011378);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001137c);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011380);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011384);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011388);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001138c);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011390);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011394);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011398);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001139c);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000113c0);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000113c4);
writel(0x0000000d&0xffffffff,ivp_cae_base_addr+0x000113c8);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000113cc);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000113d0);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000113d4);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000113d8);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000113dc);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000113f8);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000113fc);
writel(0x80000019&0xffffffff,ivp_cae_base_addr+0x00011c00);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011d00);
writel(0x0000000d&0xffffffff,ivp_cae_base_addr+0x00011f00);
writel(0x0000000d&0xffffffff,ivp_cae_base_addr+0x00011f04);
writel(0x0000001b&0xffffffff,ivp_cae_base_addr+0x00011f08);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011f0c);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011f10);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011f14);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011f18);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011f1c);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011ff0);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011ff4);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011ff8);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011ffc);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001ffe4);
writel(0x0822010d&0xffffffff,ivp_cae_base_addr+0x0001ffe8);
readl(ivp_cae_base_addr+0x0001ffec);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001ffec);
writel(0x000000f2&0xffffffff,ivp_cae_base_addr+0x0001fff4);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001fff8);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001fffc);
if((readl(ivp_cae_base_addr+0x00000000)&0xffffffff)==(0xd82cc209&0xffffffff))
cnt++;
else
printf("cnt: 3053\n");
if((readl(ivp_cae_base_addr+0x00000004)&0xffffffff)==(0x6baa4248&0xffffffff))
cnt++;
else
printf("cnt: 3054\n");
if((readl(ivp_cae_base_addr+0x00000008)&0xffffffff)==(0x82e267a9&0xffffffff))
cnt++;
else
printf("cnt: 3055\n");
if((readl(ivp_cae_base_addr+0x0000000c)&0xffffffff)==(0xc8a74da5&0xffffffff))
cnt++;
else
printf("cnt: 3056\n");
if((readl(ivp_cae_base_addr+0x00000010)&0xffffffff)==(0x7a029558&0xffffffff))
cnt++;
else
printf("cnt: 3057\n");
if((readl(ivp_cae_base_addr+0x00000014)&0xffffffff)==(0xe87a8133&0xffffffff))
cnt++;
else
printf("cnt: 3058\n");
if((readl(ivp_cae_base_addr+0x00000018)&0x00fffffc)==(0x0026c17c&0x00fffffc))
cnt++;
else
printf("cnt: 3059\n");
if((readl(ivp_cae_base_addr+0x0000001c)&0xe0ff003f)==(0x804d0021&0xe0ff003f))
cnt++;
else
printf("cnt: 3060\n");
if((readl(ivp_cae_base_addr+0x00000020)&0xf03f00ff)==(0xe0250097&0xf03f00ff))
cnt++;
else
printf("cnt: 3061\n");
if((readl(ivp_cae_base_addr+0x00000024)&0xff010101)==(0xcf000000&0xff010101))
cnt++;
else
printf("cnt: 3062\n");
if((readl(ivp_cae_base_addr+0x00000028)&0xffc00000)==(0x4f400000&0xffc00000))
cnt++;
else
printf("cnt: 3063\n");
if((readl(ivp_cae_base_addr+0x0000002c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3064\n");
if((readl(ivp_cae_base_addr+0x00000030)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3065\n");
if((readl(ivp_cae_base_addr+0x00000034)&0x00fffffc)==(0x00259c60&0x00fffffc))
cnt++;
else
printf("cnt: 3066\n");
if((readl(ivp_cae_base_addr+0x00000038)&0x00fffffc)==(0x00bbf770&0x00fffffc))
cnt++;
else
printf("cnt: 3067\n");
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000000)==(0x00000004&0x00000000))
cnt++;
else
printf("cnt: 3068\n");
if((readl(ivp_cae_base_addr+0x000007f8)&0xb7ffffff)==(0x80a35514&0xb7ffffff))
cnt++;
else
printf("cnt: 3069\n");
if((readl(ivp_cae_base_addr+0x000007fc)&0x0fffffff)==(0x027035ca&0x0fffffff))
cnt++;
else
printf("cnt: 3070\n");
if((readl(ivp_cae_base_addr+0x00000800)&0xffffffff)==(0xb83e6619&0xffffffff))
cnt++;
else
printf("cnt: 3071\n");
if((readl(ivp_cae_base_addr+0x00000804)&0xffffffff)==(0xd329ab0c&0xffffffff))
cnt++;
else
printf("cnt: 3072\n");
if((readl(ivp_cae_base_addr+0x00000808)&0xffffffff)==(0x004a7e5b&0xffffffff))
cnt++;
else
printf("cnt: 3073\n");
if((readl(ivp_cae_base_addr+0x0000080c)&0xffffffff)==(0xde1b3e70&0xffffffff))
cnt++;
else
printf("cnt: 3074\n");
if((readl(ivp_cae_base_addr+0x00000818)&0x00fffffc)==(0x0040ded4&0x00fffffc))
cnt++;
else
printf("cnt: 3075\n");
if((readl(ivp_cae_base_addr+0x0000081c)&0xe0ff00ff)==(0x20e90048&0xe0ff00ff))
cnt++;
else
printf("cnt: 3076\n");
if((readl(ivp_cae_base_addr+0x00000820)&0xf03f00ff)==(0x301500b0&0xf03f00ff))
cnt++;
else
printf("cnt: 3077\n");
if((readl(ivp_cae_base_addr+0x00000824)&0xfff80101)==(0xcd980000&0xfff80101))
cnt++;
else
printf("cnt: 3078\n");
if((readl(ivp_cae_base_addr+0x00000828)&0xff800000)==(0x14800000&0xff800000))
cnt++;
else
printf("cnt: 3079\n");
if((readl(ivp_cae_base_addr+0x0000082c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3080\n");
if((readl(ivp_cae_base_addr+0x00000830)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3081\n");
if((readl(ivp_cae_base_addr+0x00000834)&0x00fffffc)==(0x00e18c24&0x00fffffc))
cnt++;
else
printf("cnt: 3082\n");
if((readl(ivp_cae_base_addr+0x00000838)&0x00fffffc)==(0x00808a50&0x00fffffc))
cnt++;
else
printf("cnt: 3083\n");
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000000)==(0x0000006a&0x00000000))
cnt++;
else
printf("cnt: 3084\n");
if((readl(ivp_cae_base_addr+0x00000ff8)&0xb7ffffff)==(0x80a35514&0xb7ffffff))
cnt++;
else
printf("cnt: 3085\n");
if((readl(ivp_cae_base_addr+0x00000ffc)&0x0fffffff)==(0x027035ca&0x0fffffff))
cnt++;
else
printf("cnt: 3086\n");
if((readl(ivp_cae_base_addr+0x00001000)&0xffffffff)==(0x935d4a53&0xffffffff))
cnt++;
else
printf("cnt: 3087\n");
if((readl(ivp_cae_base_addr+0x00001004)&0xffffffff)==(0x307b2fcd&0xffffffff))
cnt++;
else
printf("cnt: 3088\n");
if((readl(ivp_cae_base_addr+0x00001008)&0xffffffff)==(0x9cdea81a&0xffffffff))
cnt++;
else
printf("cnt: 3089\n");
if((readl(ivp_cae_base_addr+0x0000100c)&0xffffffff)==(0x79fd16fe&0xffffffff))
cnt++;
else
printf("cnt: 3090\n");
if((readl(ivp_cae_base_addr+0x00001010)&0xffffffff)==(0xc1f2e074&0xffffffff))
cnt++;
else
printf("cnt: 3091\n");
if((readl(ivp_cae_base_addr+0x00001014)&0xffffffff)==(0xec62d7ab&0xffffffff))
cnt++;
else
printf("cnt: 3092\n");
if((readl(ivp_cae_base_addr+0x00001018)&0x00fffffc)==(0x00eeec4c&0x00fffffc))
cnt++;
else
printf("cnt: 3093\n");
if((readl(ivp_cae_base_addr+0x0000101c)&0xe0ff003f)==(0x8064002b&0xe0ff003f))
cnt++;
else
printf("cnt: 3094\n");
if((readl(ivp_cae_base_addr+0x00001020)&0xf03f00ff)==(0xb00d008f&0xf03f00ff))
cnt++;
else
printf("cnt: 3095\n");
if((readl(ivp_cae_base_addr+0x00001024)&0xff010101)==(0xcf000101&0xff010101))
cnt++;
else
printf("cnt: 3096\n");
if((readl(ivp_cae_base_addr+0x00001028)&0xffc00000)==(0xe5000000&0xffc00000))
cnt++;
else
printf("cnt: 3097\n");
if((readl(ivp_cae_base_addr+0x0000102c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3098\n");
if((readl(ivp_cae_base_addr+0x00001030)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3099\n");
if((readl(ivp_cae_base_addr+0x00001034)&0x00fffffc)==(0x000aeabc&0x00fffffc))
cnt++;
else
printf("cnt: 3100\n");
if((readl(ivp_cae_base_addr+0x00001038)&0x00fffffc)==(0x00171514&0x00fffffc))
cnt++;
else
printf("cnt: 3101\n");
if((readl(ivp_cae_base_addr+0x0000103c)&0x00000000)==(0x00000007&0x00000000))
cnt++;
else
printf("cnt: 3102\n");
if((readl(ivp_cae_base_addr+0x000017f8)&0xb7ffffff)==(0x80a35514&0xb7ffffff))
cnt++;
else
printf("cnt: 3103\n");
if((readl(ivp_cae_base_addr+0x000017fc)&0x0fffffff)==(0x027035ca&0x0fffffff))
cnt++;
else
printf("cnt: 3104\n");
if((readl(ivp_cae_base_addr+0x00001800)&0xffffffff)==(0x1dfc3870&0xffffffff))
cnt++;
else
printf("cnt: 3105\n");
if((readl(ivp_cae_base_addr+0x00001804)&0xffffffff)==(0xcb695521&0xffffffff))
cnt++;
else
printf("cnt: 3106\n");
if((readl(ivp_cae_base_addr+0x00001808)&0xffffffff)==(0xd0df19c1&0xffffffff))
cnt++;
else
printf("cnt: 3107\n");
if((readl(ivp_cae_base_addr+0x0000180c)&0xffffffff)==(0x2577b29a&0xffffffff))
cnt++;
else
printf("cnt: 3108\n");
if((readl(ivp_cae_base_addr+0x00001818)&0x00fffffc)==(0x009492e8&0x00fffffc))
cnt++;
else
printf("cnt: 3109\n");
if((readl(ivp_cae_base_addr+0x0000181c)&0xe0ff00ff)==(0xe0f600c1&0xe0ff00ff))
cnt++;
else
printf("cnt: 3110\n");
if((readl(ivp_cae_base_addr+0x00001820)&0xf03f00ff)==(0xa03b00d5&0xf03f00ff))
cnt++;
else
printf("cnt: 3111\n");
if((readl(ivp_cae_base_addr+0x00001824)&0xfff80101)==(0xa2880100&0xfff80101))
cnt++;
else
printf("cnt: 3112\n");
if((readl(ivp_cae_base_addr+0x00001828)&0xff800000)==(0x93000000&0xff800000))
cnt++;
else
printf("cnt: 3113\n");
if((readl(ivp_cae_base_addr+0x0000182c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3114\n");
if((readl(ivp_cae_base_addr+0x00001830)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3115\n");
if((readl(ivp_cae_base_addr+0x00001834)&0x00fffffc)==(0x00062f58&0x00fffffc))
cnt++;
else
printf("cnt: 3116\n");
if((readl(ivp_cae_base_addr+0x00001838)&0x00fffffc)==(0x00b735e8&0x00fffffc))
cnt++;
else
printf("cnt: 3117\n");
if((readl(ivp_cae_base_addr+0x0000183c)&0x00000000)==(0x000000dd&0x00000000))
cnt++;
else
printf("cnt: 3118\n");
if((readl(ivp_cae_base_addr+0x00001ff8)&0xb7ffffff)==(0x80a35514&0xb7ffffff))
cnt++;
else
printf("cnt: 3119\n");
if((readl(ivp_cae_base_addr+0x00001ffc)&0x0fffffff)==(0x027035ca&0x0fffffff))
cnt++;
else
printf("cnt: 3120\n");
if((readl(ivp_cae_base_addr+0x00002000)&0xffffffff)==(0x3888a59c&0xffffffff))
cnt++;
else
printf("cnt: 3121\n");
if((readl(ivp_cae_base_addr+0x00002004)&0xffffffff)==(0x59ac2e29&0xffffffff))
cnt++;
else
printf("cnt: 3122\n");
if((readl(ivp_cae_base_addr+0x00002008)&0xffffffff)==(0x80ee0a14&0xffffffff))
cnt++;
else
printf("cnt: 3123\n");
if((readl(ivp_cae_base_addr+0x0000200c)&0xffffffff)==(0x19d5fcfc&0xffffffff))
cnt++;
else
printf("cnt: 3124\n");
if((readl(ivp_cae_base_addr+0x00002010)&0xffffffff)==(0x33085bca&0xffffffff))
cnt++;
else
printf("cnt: 3125\n");
if((readl(ivp_cae_base_addr+0x00002014)&0xffffffff)==(0xbb4ad69c&0xffffffff))
cnt++;
else
printf("cnt: 3126\n");
if((readl(ivp_cae_base_addr+0x00002018)&0x00fffffc)==(0x00212b5c&0x00fffffc))
cnt++;
else
printf("cnt: 3127\n");
if((readl(ivp_cae_base_addr+0x0000201c)&0xe0ff003f)==(0xa032002f&0xe0ff003f))
cnt++;
else
printf("cnt: 3128\n");
if((readl(ivp_cae_base_addr+0x00002020)&0xf03f00ff)==(0x001c001b&0xf03f00ff))
cnt++;
else
printf("cnt: 3129\n");
if((readl(ivp_cae_base_addr+0x00002024)&0xff010101)==(0xd8010101&0xff010101))
cnt++;
else
printf("cnt: 3130\n");
if((readl(ivp_cae_base_addr+0x00002028)&0xffc00000)==(0x40000000&0xffc00000))
cnt++;
else
printf("cnt: 3131\n");
if((readl(ivp_cae_base_addr+0x0000202c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3132\n");
if((readl(ivp_cae_base_addr+0x00002030)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3133\n");
if((readl(ivp_cae_base_addr+0x00002034)&0x00fffffc)==(0x00b18230&0x00fffffc))
cnt++;
else
printf("cnt: 3134\n");
if((readl(ivp_cae_base_addr+0x00002038)&0x00fffffc)==(0x00ba5b6c&0x00fffffc))
cnt++;
else
printf("cnt: 3135\n");
if((readl(ivp_cae_base_addr+0x0000203c)&0x00000000)==(0x0000003d&0x00000000))
cnt++;
else
printf("cnt: 3136\n");
if((readl(ivp_cae_base_addr+0x000027f8)&0xb7ffffff)==(0x80a35514&0xb7ffffff))
cnt++;
else
printf("cnt: 3137\n");
if((readl(ivp_cae_base_addr+0x000027fc)&0x0fffffff)==(0x027035ca&0x0fffffff))
cnt++;
else
printf("cnt: 3138\n");
if((readl(ivp_cae_base_addr+0x00002800)&0xffffffff)==(0x0bb247e7&0xffffffff))
cnt++;
else
printf("cnt: 3139\n");
if((readl(ivp_cae_base_addr+0x00002804)&0xffffffff)==(0x3d79f400&0xffffffff))
cnt++;
else
printf("cnt: 3140\n");
if((readl(ivp_cae_base_addr+0x00002808)&0xffffffff)==(0x5a2b49b2&0xffffffff))
cnt++;
else
printf("cnt: 3141\n");
if((readl(ivp_cae_base_addr+0x0000280c)&0xffffffff)==(0x5bf4f268&0xffffffff))
cnt++;
else
printf("cnt: 3142\n");
if((readl(ivp_cae_base_addr+0x00002818)&0x00fffffc)==(0x003d9efc&0x00fffffc))
cnt++;
else
printf("cnt: 3143\n");
if((readl(ivp_cae_base_addr+0x0000281c)&0xe0ff00ff)==(0xa0320055&0xe0ff00ff))
cnt++;
else
printf("cnt: 3144\n");
if((readl(ivp_cae_base_addr+0x00002820)&0xf03f00ff)==(0x6017009c&0xf03f00ff))
cnt++;
else
printf("cnt: 3145\n");
if((readl(ivp_cae_base_addr+0x00002824)&0xfff80101)==(0x00600101&0xfff80101))
cnt++;
else
printf("cnt: 3146\n");
if((readl(ivp_cae_base_addr+0x00002828)&0xff800000)==(0x55800000&0xff800000))
cnt++;
else
printf("cnt: 3147\n");
if((readl(ivp_cae_base_addr+0x0000282c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3148\n");
if((readl(ivp_cae_base_addr+0x00002830)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3149\n");
if((readl(ivp_cae_base_addr+0x00002834)&0x00fffffc)==(0x001666f8&0x00fffffc))
cnt++;
else
printf("cnt: 3150\n");
if((readl(ivp_cae_base_addr+0x00002838)&0x00fffffc)==(0x00ab6b10&0x00fffffc))
cnt++;
else
printf("cnt: 3151\n");
if((readl(ivp_cae_base_addr+0x0000283c)&0x00000000)==(0x000000f9&0x00000000))
cnt++;
else
printf("cnt: 3152\n");
if((readl(ivp_cae_base_addr+0x00002ff8)&0xb7ffffff)==(0x80a35514&0xb7ffffff))
cnt++;
else
printf("cnt: 3153\n");
if((readl(ivp_cae_base_addr+0x00002ffc)&0x0fffffff)==(0x027035ca&0x0fffffff))
cnt++;
else
printf("cnt: 3154\n");
if((readl(ivp_cae_base_addr+0x00003000)&0xffffffff)==(0x7cbd8fb8&0xffffffff))
cnt++;
else
printf("cnt: 3155\n");
if((readl(ivp_cae_base_addr+0x00003004)&0xffffffff)==(0xc167e245&0xffffffff))
cnt++;
else
printf("cnt: 3156\n");
if((readl(ivp_cae_base_addr+0x00003008)&0xffffffff)==(0x7e9c4fe3&0xffffffff))
cnt++;
else
printf("cnt: 3157\n");
if((readl(ivp_cae_base_addr+0x0000300c)&0xffffffff)==(0x7786cf1d&0xffffffff))
cnt++;
else
printf("cnt: 3158\n");
if((readl(ivp_cae_base_addr+0x00003010)&0xffffffff)==(0xe001cffa&0xffffffff))
cnt++;
else
printf("cnt: 3159\n");
if((readl(ivp_cae_base_addr+0x00003014)&0xffffffff)==(0x3020ffda&0xffffffff))
cnt++;
else
printf("cnt: 3160\n");
if((readl(ivp_cae_base_addr+0x00003018)&0x00fffffc)==(0x0012155c&0x00fffffc))
cnt++;
else
printf("cnt: 3161\n");
if((readl(ivp_cae_base_addr+0x0000301c)&0xe0ff003f)==(0xa0bd0020&0xe0ff003f))
cnt++;
else
printf("cnt: 3162\n");
if((readl(ivp_cae_base_addr+0x00003020)&0xf03f00ff)==(0x601d00b3&0xf03f00ff))
cnt++;
else
printf("cnt: 3163\n");
if((readl(ivp_cae_base_addr+0x00003024)&0xff010101)==(0x50000001&0xff010101))
cnt++;
else
printf("cnt: 3164\n");
if((readl(ivp_cae_base_addr+0x00003028)&0xffc00000)==(0xb7800000&0xffc00000))
cnt++;
else
printf("cnt: 3165\n");
if((readl(ivp_cae_base_addr+0x0000302c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3166\n");
if((readl(ivp_cae_base_addr+0x00003030)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3167\n");
if((readl(ivp_cae_base_addr+0x00003034)&0x00fffffc)==(0x0036dfa4&0x00fffffc))
cnt++;
else
printf("cnt: 3168\n");
if((readl(ivp_cae_base_addr+0x00003038)&0x00fffffc)==(0x00acfa7c&0x00fffffc))
cnt++;
else
printf("cnt: 3169\n");
if((readl(ivp_cae_base_addr+0x0000303c)&0x00000000)==(0x0000001b&0x00000000))
cnt++;
else
printf("cnt: 3170\n");
if((readl(ivp_cae_base_addr+0x000037f8)&0xb7ffffff)==(0x80a35514&0xb7ffffff))
cnt++;
else
printf("cnt: 3171\n");
if((readl(ivp_cae_base_addr+0x000037fc)&0x0fffffff)==(0x027035ca&0x0fffffff))
cnt++;
else
printf("cnt: 3172\n");
if((readl(ivp_cae_base_addr+0x00003800)&0xffffffff)==(0xcad6dc82&0xffffffff))
cnt++;
else
printf("cnt: 3173\n");
if((readl(ivp_cae_base_addr+0x00003804)&0xffffffff)==(0x22278557&0xffffffff))
cnt++;
else
printf("cnt: 3174\n");
if((readl(ivp_cae_base_addr+0x00003808)&0xffffffff)==(0xa69958d8&0xffffffff))
cnt++;
else
printf("cnt: 3175\n");
if((readl(ivp_cae_base_addr+0x0000380c)&0xffffffff)==(0xdf324745&0xffffffff))
cnt++;
else
printf("cnt: 3176\n");
if((readl(ivp_cae_base_addr+0x00003818)&0x00fffffc)==(0x00c10a68&0x00fffffc))
cnt++;
else
printf("cnt: 3177\n");
if((readl(ivp_cae_base_addr+0x0000381c)&0xe0ff00ff)==(0xa05500f0&0xe0ff00ff))
cnt++;
else
printf("cnt: 3178\n");
if((readl(ivp_cae_base_addr+0x00003820)&0xf03f00ff)==(0xf00d003d&0xf03f00ff))
cnt++;
else
printf("cnt: 3179\n");
if((readl(ivp_cae_base_addr+0x00003824)&0xfff80101)==(0xe8e80000&0xfff80101))
cnt++;
else
printf("cnt: 3180\n");
if((readl(ivp_cae_base_addr+0x00003828)&0xff800000)==(0xbf800000&0xff800000))
cnt++;
else
printf("cnt: 3181\n");
if((readl(ivp_cae_base_addr+0x0000382c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3182\n");
if((readl(ivp_cae_base_addr+0x00003830)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3183\n");
if((readl(ivp_cae_base_addr+0x00003834)&0x00fffffc)==(0x005889b4&0x00fffffc))
cnt++;
else
printf("cnt: 3184\n");
if((readl(ivp_cae_base_addr+0x00003838)&0x00fffffc)==(0x0035964c&0x00fffffc))
cnt++;
else
printf("cnt: 3185\n");
if((readl(ivp_cae_base_addr+0x0000383c)&0x00000000)==(0x000000a9&0x00000000))
cnt++;
else
printf("cnt: 3186\n");
if((readl(ivp_cae_base_addr+0x00003ff8)&0xb7ffffff)==(0x80a35514&0xb7ffffff))
cnt++;
else
printf("cnt: 3187\n");
if((readl(ivp_cae_base_addr+0x00003ffc)&0x0fffffff)==(0x027035ca&0x0fffffff))
cnt++;
else
printf("cnt: 3188\n");
if((readl(ivp_cae_base_addr+0x0000b000)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3189\n");
if((readl(ivp_cae_base_addr+0x0000b004)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3190\n");
if((readl(ivp_cae_base_addr+0x0000b008)&0x000000ff)==(0x00000011&0x000000ff))
cnt++;
else
printf("cnt: 3191\n");
if((readl(ivp_cae_base_addr+0x0000b00c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3192\n");
if((readl(ivp_cae_base_addr+0x0000b010)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3193\n");
if((readl(ivp_cae_base_addr+0x0000b014)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3194\n");
if((readl(ivp_cae_base_addr+0x0000b018)&0x000001bf)==(0x00000008&0x000001bf))
cnt++;
else
printf("cnt: 3195\n");
if((readl(ivp_cae_base_addr+0x0000b01c)&0x0fffffff)==(0x014036c9&0x0fffffff))
cnt++;
else
printf("cnt: 3196\n");
if((readl(ivp_cae_base_addr+0x0000c000)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3197\n");
if((readl(ivp_cae_base_addr+0x0000c004)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3198\n");
if((readl(ivp_cae_base_addr+0x0000c008)&0x000000ff)==(0x000000ea&0x000000ff))
cnt++;
else
printf("cnt: 3199\n");
if((readl(ivp_cae_base_addr+0x0000c00c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3200\n");
if((readl(ivp_cae_base_addr+0x0000c010)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3201\n");
if((readl(ivp_cae_base_addr+0x0000c014)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3202\n");
if((readl(ivp_cae_base_addr+0x0000c018)&0x000001bf)==(0x00000008&0x000001bf))
cnt++;
else
printf("cnt: 3203\n");
if((readl(ivp_cae_base_addr+0x0000c01c)&0x0fffffff)==(0x014036c9&0x0fffffff))
cnt++;
else
printf("cnt: 3204\n");
if((readl(ivp_cae_base_addr+0x0000d000)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3205\n");
if((readl(ivp_cae_base_addr+0x0000d004)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3206\n");
if((readl(ivp_cae_base_addr+0x0000d008)&0x000000ff)==(0x000000a7&0x000000ff))
cnt++;
else
printf("cnt: 3207\n");
if((readl(ivp_cae_base_addr+0x0000d00c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3208\n");
if((readl(ivp_cae_base_addr+0x0000d010)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3209\n");
if((readl(ivp_cae_base_addr+0x0000d014)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3210\n");
if((readl(ivp_cae_base_addr+0x0000d018)&0x000001bf)==(0x00000008&0x000001bf))
cnt++;
else
printf("cnt: 3211\n");
if((readl(ivp_cae_base_addr+0x0000d01c)&0x0fffffff)==(0x014036c9&0x0fffffff))
cnt++;
else
printf("cnt: 3212\n");
if((readl(ivp_cae_base_addr+0x0000e000)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3213\n");
if((readl(ivp_cae_base_addr+0x0000e004)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3214\n");
if((readl(ivp_cae_base_addr+0x0000e008)&0x000000ff)==(0x00000013&0x000000ff))
cnt++;
else
printf("cnt: 3215\n");
if((readl(ivp_cae_base_addr+0x0000e00c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3216\n");
if((readl(ivp_cae_base_addr+0x0000e010)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3217\n");
if((readl(ivp_cae_base_addr+0x0000e014)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3218\n");
if((readl(ivp_cae_base_addr+0x0000e018)&0x000001bf)==(0x00000008&0x000001bf))
cnt++;
else
printf("cnt: 3219\n");
if((readl(ivp_cae_base_addr+0x0000e01c)&0x0fffffff)==(0x014036c9&0x0fffffff))
cnt++;
else
printf("cnt: 3220\n");
if((readl(ivp_cae_base_addr+0x0000f000)&0xefff0fff)==(0x257702ae&0xefff0fff))
cnt++;
else
printf("cnt: 3221\n");
if((readl(ivp_cae_base_addr+0x0000f010)&0x8f8f8f8f)==(0x00868b80&0x8f8f8f8f))
cnt++;
else
printf("cnt: 3222\n");
if((readl(ivp_cae_base_addr+0x0000f078)&0xb7ffffff)==(0x80a35514&0xb7ffffff))
cnt++;
else
printf("cnt: 3223\n");
if((readl(ivp_cae_base_addr+0x0000f07c)&0x0fffffff)==(0x027035ca&0x0fffffff))
cnt++;
else
printf("cnt: 3224\n");
if((readl(ivp_cae_base_addr+0x0000f200)&0x0000000f)==(0x0000000f&0x0000000f))
cnt++;
else
printf("cnt: 3225\n");
if((readl(ivp_cae_base_addr+0x0000f204)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3226\n");
if((readl(ivp_cae_base_addr+0x0000f208)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3227\n");
if((readl(ivp_cae_base_addr+0x0000f210)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3228\n");
if((readl(ivp_cae_base_addr+0x0000f214)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3229\n");
if((readl(ivp_cae_base_addr+0x0000f218)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3230\n");
if((readl(ivp_cae_base_addr+0x0000f21c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3231\n");
if((readl(ivp_cae_base_addr+0x0000f400)&0xf000dfff)==(0xe000d170&0xf000dfff))
cnt++;
else
printf("cnt: 3232\n");
if((readl(ivp_cae_base_addr+0x0000f478)&0xb7ffffff)==(0x80a35514&0xb7ffffff))
cnt++;
else
printf("cnt: 3233\n");
if((readl(ivp_cae_base_addr+0x0000f47c)&0x0fffffff)==(0x027035ca&0x0fffffff))
cnt++;
else
printf("cnt: 3234\n");
if((readl(ivp_cae_base_addr+0x0000f600)&0x0000000f)==(0x0000000c&0x0000000f))
cnt++;
else
printf("cnt: 3235\n");
if((readl(ivp_cae_base_addr+0x0000f604)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3236\n");
if((readl(ivp_cae_base_addr+0x0000f608)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3237\n");
if((readl(ivp_cae_base_addr+0x0000f60c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3238\n");
if((readl(ivp_cae_base_addr+0x0000f610)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3239\n");
if((readl(ivp_cae_base_addr+0x0000f614)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3240\n");
if((readl(ivp_cae_base_addr+0x0000f618)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3241\n");
if((readl(ivp_cae_base_addr+0x0000f61c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3242\n");
if((readl(ivp_cae_base_addr+0x0000f620)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3243\n");
if((readl(ivp_cae_base_addr+0x0000f628)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3244\n");
if((readl(ivp_cae_base_addr+0x0000f62c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3245\n");
if((readl(ivp_cae_base_addr+0x0000f800)&0xfff00000)==(0xce100000&0xfff00000))
cnt++;
else
printf("cnt: 3246\n");
if((readl(ivp_cae_base_addr+0x0000f804)&0xfff00000)==(0xfd900000&0xfff00000))
cnt++;
else
printf("cnt: 3247\n");
if((readl(ivp_cae_base_addr+0x0000f808)&0xffffffff)==(0xe7e134c3&0xffffffff))
cnt++;
else
printf("cnt: 3248\n");
if((readl(ivp_cae_base_addr+0x0000f80c)&0x00000000)==(0x40000000&0x00000000))
cnt++;
else
printf("cnt: 3249\n");
if((readl(ivp_cae_base_addr+0x0000f810)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3250\n");
if((readl(ivp_cae_base_addr+0x0000f814)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3251\n");
if((readl(ivp_cae_base_addr+0x0000f818)&0x000001bf)==(0x00000020&0x000001bf))
cnt++;
else
printf("cnt: 3252\n");
if((readl(ivp_cae_base_addr+0x0000f81c)&0x0fffffff)==(0x014036c9&0x0fffffff))
cnt++;
else
printf("cnt: 3253\n");
if((readl(ivp_cae_base_addr+0x0000fff4)&0x00ff9ff1)==(0x000f0e91&0x00ff9ff1))
cnt++;
else
printf("cnt: 3254\n");
if((readl(ivp_cae_base_addr+0x0000fff8)&0xb7ffffff)==(0x80a35514&0xb7ffffff))
cnt++;
else
printf("cnt: 3255\n");
if((readl(ivp_cae_base_addr+0x0000fffc)&0x0fffffff)==(0x027035ca&0x0fffffff))
cnt++;
else
printf("cnt: 3256\n");
if((readl(ivp_cae_base_addr+0x00010000)&0xc000ff00)==(0xc0004d00&0xc000ff00))
cnt++;
else
printf("cnt: 3257\n");
if((readl(ivp_cae_base_addr+0x00010100)&0x8000ff00)==(0x0000cf00&0x8000ff00))
cnt++;
else
printf("cnt: 3258\n");
if((readl(ivp_cae_base_addr+0x00011000)&0x007b0000)==(0x00700000&0x007b0000))
cnt++;
else
printf("cnt: 3259\n");
if((readl(ivp_cae_base_addr+0x00011004)&0xff6f7f3f)==(0x2008493e&0xff6f7f3f))
cnt++;
else
printf("cnt: 3260\n");
if((readl(ivp_cae_base_addr+0x00011008)&0x0000033f)==(0x00000237&0x0000033f))
cnt++;
else
printf("cnt: 3261\n");
if((readl(ivp_cae_base_addr+0x0001100c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3262\n");
if((readl(ivp_cae_base_addr+0x00011018)&0x00ff0000)==(0x00e80000&0x00ff0000))
cnt++;
else
printf("cnt: 3263\n");
if((readl(ivp_cae_base_addr+0x0001101c)&0xc00000f8)==(0x80000068&0xc00000f8))
cnt++;
else
printf("cnt: 3264\n");
if((readl(ivp_cae_base_addr+0x00011020)&0xffffffff)==(0x26c0fc98&0xffffffff))
cnt++;
else
printf("cnt: 3265\n");
if((readl(ivp_cae_base_addr+0x00011024)&0xffffffff)==(0x69409c9d&0xffffffff))
cnt++;
else
printf("cnt: 3266\n");
if((readl(ivp_cae_base_addr+0x00011028)&0xffffffff)==(0x62fd0c0a&0xffffffff))
cnt++;
else
printf("cnt: 3267\n");
if((readl(ivp_cae_base_addr+0x0001102c)&0x0000000f)==(0x00000000&0x0000000f))
cnt++;
else
printf("cnt: 3268\n");
if((readl(ivp_cae_base_addr+0x00011030)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3269\n");
if((readl(ivp_cae_base_addr+0x00011040)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3270\n");
if((readl(ivp_cae_base_addr+0x00011044)&0x00000004)==(0x00000004&0x00000004))
cnt++;
else
printf("cnt: 3271\n");
if((readl(ivp_cae_base_addr+0x00011048)&0x00000000)==(0x6227c6c3&0x00000000))
cnt++;
else
printf("cnt: 3272\n");
if((readl(ivp_cae_base_addr+0x0001104c)&0x00000000)==(0x7d85e19b&0x00000000))
cnt++;
else
printf("cnt: 3273\n");
if((readl(ivp_cae_base_addr+0x00011050)&0x00000000)==(0x9c307799&0x00000000))
cnt++;
else
printf("cnt: 3274\n");
if((readl(ivp_cae_base_addr+0x00011054)&0x00000000)==(0xa1df567e&0x00000000))
cnt++;
else
printf("cnt: 3275\n");
if((readl(ivp_cae_base_addr+0x00011058)&0x00000000)==(0x1fd3aeba&0x00000000))
cnt++;
else
printf("cnt: 3276\n");
if((readl(ivp_cae_base_addr+0x0001105c)&0x00000000)==(0x9f3dc9df&0x00000000))
cnt++;
else
printf("cnt: 3277\n");
if((readl(ivp_cae_base_addr+0x00011060)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3278\n");
if((readl(ivp_cae_base_addr+0x00011064)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3279\n");
if((readl(ivp_cae_base_addr+0x00011068)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3280\n");
if((readl(ivp_cae_base_addr+0x0001106c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3281\n");
if((readl(ivp_cae_base_addr+0x00011070)&0xffffffff)==(0xc915306a&0xffffffff))
cnt++;
else
printf("cnt: 3282\n");
if((readl(ivp_cae_base_addr+0x00011074)&0xffffffff)==(0xc83871cf&0xffffffff))
cnt++;
else
printf("cnt: 3283\n");
if((readl(ivp_cae_base_addr+0x00011080)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3284\n");
if((readl(ivp_cae_base_addr+0x00011084)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3285\n");
if((readl(ivp_cae_base_addr+0x00011088)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3286\n");
if((readl(ivp_cae_base_addr+0x0001108c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3287\n");
if((readl(ivp_cae_base_addr+0x00011090)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3288\n");
if((readl(ivp_cae_base_addr+0x00011094)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3289\n");
if((readl(ivp_cae_base_addr+0x00011098)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3290\n");
if((readl(ivp_cae_base_addr+0x0001109c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3291\n");
if((readl(ivp_cae_base_addr+0x000110a0)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3292\n");
if((readl(ivp_cae_base_addr+0x000110a4)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3293\n");
if((readl(ivp_cae_base_addr+0x000110a8)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3294\n");
if((readl(ivp_cae_base_addr+0x000110ac)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3295\n");
if((readl(ivp_cae_base_addr+0x000110b0)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3296\n");
if((readl(ivp_cae_base_addr+0x000110b4)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3297\n");
if((readl(ivp_cae_base_addr+0x000110b8)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3298\n");
if((readl(ivp_cae_base_addr+0x000110bc)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3299\n");
if((readl(ivp_cae_base_addr+0x000110c0)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3300\n");
if((readl(ivp_cae_base_addr+0x000110c4)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3301\n");
if((readl(ivp_cae_base_addr+0x000110c8)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3302\n");
if((readl(ivp_cae_base_addr+0x000110cc)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3303\n");
if((readl(ivp_cae_base_addr+0x000110d0)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3304\n");
if((readl(ivp_cae_base_addr+0x000110d4)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3305\n");
if((readl(ivp_cae_base_addr+0x000110d8)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3306\n");
if((readl(ivp_cae_base_addr+0x000110dc)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3307\n");
if((readl(ivp_cae_base_addr+0x000110e0)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3308\n");
if((readl(ivp_cae_base_addr+0x000110e4)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3309\n");
if((readl(ivp_cae_base_addr+0x000110e8)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3310\n");
if((readl(ivp_cae_base_addr+0x000110ec)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3311\n");
if((readl(ivp_cae_base_addr+0x000110f0)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3312\n");
if((readl(ivp_cae_base_addr+0x000110f4)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3313\n");
if((readl(ivp_cae_base_addr+0x000110f8)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3314\n");
if((readl(ivp_cae_base_addr+0x000110fc)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3315\n");
if((readl(ivp_cae_base_addr+0x00011100)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3316\n");
if((readl(ivp_cae_base_addr+0x00011104)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3317\n");
if((readl(ivp_cae_base_addr+0x00011108)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3318\n");
if((readl(ivp_cae_base_addr+0x0001110c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3319\n");
if((readl(ivp_cae_base_addr+0x00011110)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3320\n");
if((readl(ivp_cae_base_addr+0x00011114)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3321\n");
if((readl(ivp_cae_base_addr+0x00011118)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3322\n");
if((readl(ivp_cae_base_addr+0x0001111c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3323\n");
if((readl(ivp_cae_base_addr+0x00011140)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3324\n");
if((readl(ivp_cae_base_addr+0x00011144)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3325\n");
if((readl(ivp_cae_base_addr+0x00011148)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3326\n");
if((readl(ivp_cae_base_addr+0x0001114c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3327\n");
if((readl(ivp_cae_base_addr+0x00011150)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3328\n");
if((readl(ivp_cae_base_addr+0x00011154)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3329\n");
if((readl(ivp_cae_base_addr+0x00011158)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3330\n");
if((readl(ivp_cae_base_addr+0x0001115c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3331\n");
if((readl(ivp_cae_base_addr+0x00011160)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3332\n");
if((readl(ivp_cae_base_addr+0x00011164)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3333\n");
if((readl(ivp_cae_base_addr+0x00011168)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3334\n");
if((readl(ivp_cae_base_addr+0x0001116c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3335\n");
if((readl(ivp_cae_base_addr+0x00011170)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3336\n");
if((readl(ivp_cae_base_addr+0x00011174)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3337\n");
if((readl(ivp_cae_base_addr+0x00011178)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3338\n");
if((readl(ivp_cae_base_addr+0x0001117c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3339\n");
if((readl(ivp_cae_base_addr+0x00011180)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3340\n");
if((readl(ivp_cae_base_addr+0x00011184)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3341\n");
if((readl(ivp_cae_base_addr+0x00011188)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3342\n");
if((readl(ivp_cae_base_addr+0x0001118c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3343\n");
if((readl(ivp_cae_base_addr+0x00011190)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3344\n");
if((readl(ivp_cae_base_addr+0x00011194)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3345\n");
if((readl(ivp_cae_base_addr+0x00011198)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3346\n");
if((readl(ivp_cae_base_addr+0x0001119c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3347\n");
if((readl(ivp_cae_base_addr+0x000111a0)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3348\n");
if((readl(ivp_cae_base_addr+0x000111a4)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3349\n");
if((readl(ivp_cae_base_addr+0x000111a8)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3350\n");
if((readl(ivp_cae_base_addr+0x000111ac)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3351\n");
if((readl(ivp_cae_base_addr+0x000111b0)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3352\n");
if((readl(ivp_cae_base_addr+0x000111b4)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3353\n");
if((readl(ivp_cae_base_addr+0x000111b8)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3354\n");
if((readl(ivp_cae_base_addr+0x000111bc)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3355\n");
if((readl(ivp_cae_base_addr+0x000111c0)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3356\n");
if((readl(ivp_cae_base_addr+0x000111c4)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3357\n");
if((readl(ivp_cae_base_addr+0x000111c8)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3358\n");
if((readl(ivp_cae_base_addr+0x000111cc)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3359\n");
if((readl(ivp_cae_base_addr+0x000111d0)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3360\n");
if((readl(ivp_cae_base_addr+0x000111d4)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3361\n");
if((readl(ivp_cae_base_addr+0x000111d8)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3362\n");
if((readl(ivp_cae_base_addr+0x000111dc)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3363\n");
if((readl(ivp_cae_base_addr+0x000111e4)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3364\n");
if((readl(ivp_cae_base_addr+0x00011200)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3365\n");
if((readl(ivp_cae_base_addr+0x00011204)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3366\n");
if((readl(ivp_cae_base_addr+0x00011208)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3367\n");
if((readl(ivp_cae_base_addr+0x0001120c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3368\n");
if((readl(ivp_cae_base_addr+0x00011210)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3369\n");
if((readl(ivp_cae_base_addr+0x00011214)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3370\n");
if((readl(ivp_cae_base_addr+0x00011218)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3371\n");
if((readl(ivp_cae_base_addr+0x0001121c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3372\n");
if((readl(ivp_cae_base_addr+0x00011220)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3373\n");
if((readl(ivp_cae_base_addr+0x00011224)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3374\n");
if((readl(ivp_cae_base_addr+0x00011228)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3375\n");
if((readl(ivp_cae_base_addr+0x0001122c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3376\n");
if((readl(ivp_cae_base_addr+0x00011230)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3377\n");
if((readl(ivp_cae_base_addr+0x00011234)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3378\n");
if((readl(ivp_cae_base_addr+0x00011238)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3379\n");
if((readl(ivp_cae_base_addr+0x0001123c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3380\n");
if((readl(ivp_cae_base_addr+0x00011240)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3381\n");
if((readl(ivp_cae_base_addr+0x00011244)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3382\n");
if((readl(ivp_cae_base_addr+0x00011248)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3383\n");
if((readl(ivp_cae_base_addr+0x0001124c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3384\n");
if((readl(ivp_cae_base_addr+0x00011250)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3385\n");
if((readl(ivp_cae_base_addr+0x00011254)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3386\n");
if((readl(ivp_cae_base_addr+0x00011258)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3387\n");
if((readl(ivp_cae_base_addr+0x0001125c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3388\n");
if((readl(ivp_cae_base_addr+0x00011260)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3389\n");
if((readl(ivp_cae_base_addr+0x00011264)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3390\n");
if((readl(ivp_cae_base_addr+0x00011268)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3391\n");
if((readl(ivp_cae_base_addr+0x0001126c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3392\n");
if((readl(ivp_cae_base_addr+0x00011270)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3393\n");
if((readl(ivp_cae_base_addr+0x00011274)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3394\n");
if((readl(ivp_cae_base_addr+0x00011278)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3395\n");
if((readl(ivp_cae_base_addr+0x0001127c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3396\n");
if((readl(ivp_cae_base_addr+0x00011280)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3397\n");
if((readl(ivp_cae_base_addr+0x00011284)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3398\n");
if((readl(ivp_cae_base_addr+0x00011288)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3399\n");
if((readl(ivp_cae_base_addr+0x0001128c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3400\n");
if((readl(ivp_cae_base_addr+0x00011290)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3401\n");
if((readl(ivp_cae_base_addr+0x00011294)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3402\n");
if((readl(ivp_cae_base_addr+0x00011298)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3403\n");
if((readl(ivp_cae_base_addr+0x0001129c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3404\n");
if((readl(ivp_cae_base_addr+0x000112a4)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3405\n");
if((readl(ivp_cae_base_addr+0x000112c0)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3406\n");
if((readl(ivp_cae_base_addr+0x000112c4)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3407\n");
if((readl(ivp_cae_base_addr+0x000112c8)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3408\n");
if((readl(ivp_cae_base_addr+0x000112cc)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3409\n");
if((readl(ivp_cae_base_addr+0x000112d0)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3410\n");
if((readl(ivp_cae_base_addr+0x000112d4)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3411\n");
if((readl(ivp_cae_base_addr+0x000112d8)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3412\n");
if((readl(ivp_cae_base_addr+0x000112dc)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3413\n");
if((readl(ivp_cae_base_addr+0x000112e0)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3414\n");
if((readl(ivp_cae_base_addr+0x000112e4)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3415\n");
if((readl(ivp_cae_base_addr+0x000112e8)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3416\n");
if((readl(ivp_cae_base_addr+0x000112ec)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3417\n");
if((readl(ivp_cae_base_addr+0x000112f0)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3418\n");
if((readl(ivp_cae_base_addr+0x00011300)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3419\n");
if((readl(ivp_cae_base_addr+0x00011304)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3420\n");
if((readl(ivp_cae_base_addr+0x00011308)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3421\n");
if((readl(ivp_cae_base_addr+0x0001130c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3422\n");
if((readl(ivp_cae_base_addr+0x00011310)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3423\n");
if((readl(ivp_cae_base_addr+0x00011314)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3424\n");
if((readl(ivp_cae_base_addr+0x00011318)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3425\n");
if((readl(ivp_cae_base_addr+0x0001131c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3426\n");
if((readl(ivp_cae_base_addr+0x00011320)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3427\n");
if((readl(ivp_cae_base_addr+0x00011324)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3428\n");
if((readl(ivp_cae_base_addr+0x00011328)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3429\n");
if((readl(ivp_cae_base_addr+0x0001132c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3430\n");
if((readl(ivp_cae_base_addr+0x00011330)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3431\n");
if((readl(ivp_cae_base_addr+0x00011334)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3432\n");
if((readl(ivp_cae_base_addr+0x00011338)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3433\n");
if((readl(ivp_cae_base_addr+0x0001133c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3434\n");
if((readl(ivp_cae_base_addr+0x00011340)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3435\n");
if((readl(ivp_cae_base_addr+0x00011344)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3436\n");
if((readl(ivp_cae_base_addr+0x00011348)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3437\n");
if((readl(ivp_cae_base_addr+0x0001134c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3438\n");
if((readl(ivp_cae_base_addr+0x00011350)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3439\n");
if((readl(ivp_cae_base_addr+0x00011354)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3440\n");
if((readl(ivp_cae_base_addr+0x00011358)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3441\n");
if((readl(ivp_cae_base_addr+0x0001135c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3442\n");
if((readl(ivp_cae_base_addr+0x00011360)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3443\n");
if((readl(ivp_cae_base_addr+0x00011364)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3444\n");
if((readl(ivp_cae_base_addr+0x00011368)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3445\n");
if((readl(ivp_cae_base_addr+0x0001136c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3446\n");
if((readl(ivp_cae_base_addr+0x00011370)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3447\n");
if((readl(ivp_cae_base_addr+0x00011374)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3448\n");
if((readl(ivp_cae_base_addr+0x00011378)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3449\n");
if((readl(ivp_cae_base_addr+0x0001137c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3450\n");
if((readl(ivp_cae_base_addr+0x00011380)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3451\n");
if((readl(ivp_cae_base_addr+0x00011384)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3452\n");
if((readl(ivp_cae_base_addr+0x00011388)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3453\n");
if((readl(ivp_cae_base_addr+0x0001138c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3454\n");
if((readl(ivp_cae_base_addr+0x00011390)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3455\n");
if((readl(ivp_cae_base_addr+0x00011394)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3456\n");
if((readl(ivp_cae_base_addr+0x00011398)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3457\n");
if((readl(ivp_cae_base_addr+0x0001139c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3458\n");
if((readl(ivp_cae_base_addr+0x000113c0)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3459\n");
if((readl(ivp_cae_base_addr+0x000113c4)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3460\n");
if((readl(ivp_cae_base_addr+0x000113c8)&0x0000000f)==(0x0000000d&0x0000000f))
cnt++;
else
printf("cnt: 3461\n");
if((readl(ivp_cae_base_addr+0x000113cc)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3462\n");
if((readl(ivp_cae_base_addr+0x000113d0)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3463\n");
if((readl(ivp_cae_base_addr+0x000113d4)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3464\n");
if((readl(ivp_cae_base_addr+0x000113d8)&0x000001bf)==(0x00000004&0x000001bf))
cnt++;
else
printf("cnt: 3465\n");
if((readl(ivp_cae_base_addr+0x000113dc)&0x0fffffff)==(0x014036c9&0x0fffffff))
cnt++;
else
printf("cnt: 3466\n");
if((readl(ivp_cae_base_addr+0x000113f8)&0xffffffe0)==(0x7fc1fc00&0xffffffe0))
cnt++;
else
printf("cnt: 3467\n");
if((readl(ivp_cae_base_addr+0x000113fc)&0x0fffffff)==(0x04339f60&0x0fffffff))
cnt++;
else
printf("cnt: 3468\n");
if((readl(ivp_cae_base_addr+0x00011c00)&0xc00000ff)==(0x80000019&0xc00000ff))
cnt++;
else
printf("cnt: 3469\n");
if((readl(ivp_cae_base_addr+0x00011d00)&0xc0000000)==(0x00000000&0xc0000000))
cnt++;
else
printf("cnt: 3470\n");
if((readl(ivp_cae_base_addr+0x00011f00)&0x0000001f)==(0x0000000d&0x0000001f))
cnt++;
else
printf("cnt: 3471\n");
if((readl(ivp_cae_base_addr+0x00011f04)&0x0000001f)==(0x0000000d&0x0000001f))
cnt++;
else
printf("cnt: 3472\n");
if((readl(ivp_cae_base_addr+0x00011f08)&0x0000001f)==(0x0000001b&0x0000001f))
cnt++;
else
printf("cnt: 3473\n");
if((readl(ivp_cae_base_addr+0x00011f0c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3474\n");
if((readl(ivp_cae_base_addr+0x00011f10)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3475\n");
if((readl(ivp_cae_base_addr+0x00011f14)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3476\n");
if((readl(ivp_cae_base_addr+0x00011f18)&0x000001bf)==(0x00000005&0x000001bf))
cnt++;
else
printf("cnt: 3477\n");
if((readl(ivp_cae_base_addr+0x00011f1c)&0x0fffffff)==(0x014036c9&0x0fffffff))
cnt++;
else
printf("cnt: 3478\n");
if((readl(ivp_cae_base_addr+0x00011ff0)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3479\n");
if((readl(ivp_cae_base_addr+0x00011ff4)&0x80000001)==(0x00000000&0x80000001))
cnt++;
else
printf("cnt: 3480\n");
if((readl(ivp_cae_base_addr+0x00011ff8)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3481\n");
if((readl(ivp_cae_base_addr+0x00011ffc)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3482\n");
if((readl(ivp_cae_base_addr+0x0001ffe4)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3483\n");
if((readl(ivp_cae_base_addr+0x0001ffe8)&0x087b031f)==(0x0822010d&0x087b031f))
cnt++;
else
printf("cnt: 3484\n");
if((readl(ivp_cae_base_addr+0x0001ffec)&0x087b031f)==(0x00000000&0x087b031f))
cnt++;
else
printf("cnt: 3485\n");
if((readl(ivp_cae_base_addr+0x0001fff4)&0x000401ff)==(0x000000f2&0x000401ff))
cnt++;
else
printf("cnt: 3486\n");
if((readl(ivp_cae_base_addr+0x0001fff8)&0xc00fffff)==(0x00074751&0xc00fffff))
cnt++;
else
printf("cnt: 3487\n");
if((readl(ivp_cae_base_addr+0x0001fffc)&0x0fffffff)==(0x02319e61&0x0fffffff))
cnt++;
else
printf("cnt: 3488\n");
writel(0x27d33df6&0xffffffff,ivp_cae_base_addr+0x00000000);
writel(0x9455bdb7&0xffffffff,ivp_cae_base_addr+0x00000004);
writel(0x7d1d9856&0xffffffff,ivp_cae_base_addr+0x00000008);
writel(0x3758b25a&0xffffffff,ivp_cae_base_addr+0x0000000c);
writel(0x85fd6aa7&0xffffffff,ivp_cae_base_addr+0x00000010);
writel(0x17857ecc&0xffffffff,ivp_cae_base_addr+0x00000014);
writel(0x00d93e80&0xffffffff,ivp_cae_base_addr+0x00000018);
writel(0x60b2001e&0xffffffff,ivp_cae_base_addr+0x0000001c);
writel(0x101a0068&0xffffffff,ivp_cae_base_addr+0x00000020);
writel(0x30010101&0xffffffff,ivp_cae_base_addr+0x00000024);
writel(0xb0800000&0xffffffff,ivp_cae_base_addr+0x00000028);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000002c);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00000030);
writel(0x00da639c&0xffffffff,ivp_cae_base_addr+0x00000034);
writel(0x0044088c&0xffffffff,ivp_cae_base_addr+0x00000038);
writel(0x0000003b&0xffffffff,ivp_cae_base_addr+0x0000003c);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000007f8);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000007fc);
writel(0x47c199e6&0xffffffff,ivp_cae_base_addr+0x00000800);
writel(0x2cd654f3&0xffffffff,ivp_cae_base_addr+0x00000804);
writel(0xffb581a4&0xffffffff,ivp_cae_base_addr+0x00000808);
writel(0x21e4c18f&0xffffffff,ivp_cae_base_addr+0x0000080c);
writel(0x00bf2128&0xffffffff,ivp_cae_base_addr+0x00000818);
writel(0xc01600b7&0xffffffff,ivp_cae_base_addr+0x0000081c);
writel(0xc02a004f&0xffffffff,ivp_cae_base_addr+0x00000820);
writel(0x32600101&0xffffffff,ivp_cae_base_addr+0x00000824);
writel(0xeb000000&0xffffffff,ivp_cae_base_addr+0x00000828);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000082c);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00000830);
writel(0x001e73d8&0xffffffff,ivp_cae_base_addr+0x00000834);
writel(0x007f75ac&0xffffffff,ivp_cae_base_addr+0x00000838);
writel(0x00000095&0xffffffff,ivp_cae_base_addr+0x0000083c);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00000ff8);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00000ffc);
writel(0x6ca2b5ac&0xffffffff,ivp_cae_base_addr+0x00001000);
writel(0xcf84d032&0xffffffff,ivp_cae_base_addr+0x00001004);
writel(0x632157e5&0xffffffff,ivp_cae_base_addr+0x00001008);
writel(0x8602e901&0xffffffff,ivp_cae_base_addr+0x0000100c);
writel(0x3e0d1f8b&0xffffffff,ivp_cae_base_addr+0x00001010);
writel(0x139d2854&0xffffffff,ivp_cae_base_addr+0x00001014);
writel(0x001113b0&0xffffffff,ivp_cae_base_addr+0x00001018);
writel(0x609b0014&0xffffffff,ivp_cae_base_addr+0x0000101c);
writel(0x40320070&0xffffffff,ivp_cae_base_addr+0x00001020);
writel(0x30010000&0xffffffff,ivp_cae_base_addr+0x00001024);
writel(0x1ac00000&0xffffffff,ivp_cae_base_addr+0x00001028);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000102c);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00001030);
writel(0x00f51540&0xffffffff,ivp_cae_base_addr+0x00001034);
writel(0x00e8eae8&0xffffffff,ivp_cae_base_addr+0x00001038);
writel(0x00000038&0xffffffff,ivp_cae_base_addr+0x0000103c);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000017f8);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000017fc);
writel(0xe203c78f&0xffffffff,ivp_cae_base_addr+0x00001800);
writel(0x3496aade&0xffffffff,ivp_cae_base_addr+0x00001804);
writel(0x2f20e63e&0xffffffff,ivp_cae_base_addr+0x00001808);
writel(0xda884d65&0xffffffff,ivp_cae_base_addr+0x0000180c);
writel(0x006b6d14&0xffffffff,ivp_cae_base_addr+0x00001818);
writel(0x0009003e&0xffffffff,ivp_cae_base_addr+0x0000181c);
writel(0x5004002a&0xffffffff,ivp_cae_base_addr+0x00001820);
writel(0x5d700001&0xffffffff,ivp_cae_base_addr+0x00001824);
writel(0x6c800000&0xffffffff,ivp_cae_base_addr+0x00001828);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000182c);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00001830);
writel(0x00f9d0a4&0xffffffff,ivp_cae_base_addr+0x00001834);
writel(0x0048ca14&0xffffffff,ivp_cae_base_addr+0x00001838);
writel(0x00000022&0xffffffff,ivp_cae_base_addr+0x0000183c);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00001ff8);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00001ffc);
writel(0xc7775a63&0xffffffff,ivp_cae_base_addr+0x00002000);
writel(0xa653d1d6&0xffffffff,ivp_cae_base_addr+0x00002004);
writel(0x7f11f5eb&0xffffffff,ivp_cae_base_addr+0x00002008);
writel(0xe62a0303&0xffffffff,ivp_cae_base_addr+0x0000200c);
writel(0xccf7a435&0xffffffff,ivp_cae_base_addr+0x00002010);
writel(0x44b52963&0xffffffff,ivp_cae_base_addr+0x00002014);
writel(0x00ded4a0&0xffffffff,ivp_cae_base_addr+0x00002018);
writel(0x40cd0010&0xffffffff,ivp_cae_base_addr+0x0000201c);
writel(0xf02300e4&0xffffffff,ivp_cae_base_addr+0x00002020);
writel(0x27000000&0xffffffff,ivp_cae_base_addr+0x00002024);
writel(0xbfc00000&0xffffffff,ivp_cae_base_addr+0x00002028);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000202c);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00002030);
writel(0x004e7dcc&0xffffffff,ivp_cae_base_addr+0x00002034);
writel(0x0045a490&0xffffffff,ivp_cae_base_addr+0x00002038);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x0000203c);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000027f8);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000027fc);
writel(0xf44db818&0xffffffff,ivp_cae_base_addr+0x00002800);
writel(0xc2860bff&0xffffffff,ivp_cae_base_addr+0x00002804);
writel(0xa5d4b64d&0xffffffff,ivp_cae_base_addr+0x00002808);
writel(0xa40b0d97&0xffffffff,ivp_cae_base_addr+0x0000280c);
writel(0x00c26100&0xffffffff,ivp_cae_base_addr+0x00002818);
writel(0x40cd00aa&0xffffffff,ivp_cae_base_addr+0x0000281c);
writel(0x90280063&0xffffffff,ivp_cae_base_addr+0x00002820);
writel(0xff980000&0xffffffff,ivp_cae_base_addr+0x00002824);
writel(0xaa000000&0xffffffff,ivp_cae_base_addr+0x00002828);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000282c);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00002830);
writel(0x00e99904&0xffffffff,ivp_cae_base_addr+0x00002834);
writel(0x005494ec&0xffffffff,ivp_cae_base_addr+0x00002838);
writel(0x00000006&0xffffffff,ivp_cae_base_addr+0x0000283c);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00002ff8);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00002ffc);
writel(0x83427047&0xffffffff,ivp_cae_base_addr+0x00003000);
writel(0x3e981dba&0xffffffff,ivp_cae_base_addr+0x00003004);
writel(0x8163b01c&0xffffffff,ivp_cae_base_addr+0x00003008);
writel(0x887930e2&0xffffffff,ivp_cae_base_addr+0x0000300c);
writel(0x1ffe3005&0xffffffff,ivp_cae_base_addr+0x00003010);
writel(0xcfdf0025&0xffffffff,ivp_cae_base_addr+0x00003014);
writel(0x00edeaa0&0xffffffff,ivp_cae_base_addr+0x00003018);
writel(0x4042001f&0xffffffff,ivp_cae_base_addr+0x0000301c);
writel(0x9022004c&0xffffffff,ivp_cae_base_addr+0x00003020);
writel(0xaf010100&0xffffffff,ivp_cae_base_addr+0x00003024);
writel(0x48400000&0xffffffff,ivp_cae_base_addr+0x00003028);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000302c);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00003030);
writel(0x00c92058&0xffffffff,ivp_cae_base_addr+0x00003034);
writel(0x00530580&0xffffffff,ivp_cae_base_addr+0x00003038);
writel(0x00000024&0xffffffff,ivp_cae_base_addr+0x0000303c);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000037f8);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000037fc);
writel(0x3529237d&0xffffffff,ivp_cae_base_addr+0x00003800);
writel(0xddd87aa8&0xffffffff,ivp_cae_base_addr+0x00003804);
writel(0x5966a727&0xffffffff,ivp_cae_base_addr+0x00003808);
writel(0x20cdb8ba&0xffffffff,ivp_cae_base_addr+0x0000380c);
writel(0x003ef594&0xffffffff,ivp_cae_base_addr+0x00003818);
writel(0x40aa000f&0xffffffff,ivp_cae_base_addr+0x0000381c);
writel(0x003200c2&0xffffffff,ivp_cae_base_addr+0x00003820);
writel(0x17100101&0xffffffff,ivp_cae_base_addr+0x00003824);
writel(0x40000000&0xffffffff,ivp_cae_base_addr+0x00003828);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000382c);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00003830);
writel(0x00a77648&0xffffffff,ivp_cae_base_addr+0x00003834);
writel(0x00ca69b0&0xffffffff,ivp_cae_base_addr+0x00003838);
writel(0x00000056&0xffffffff,ivp_cae_base_addr+0x0000383c);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00003ff8);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00003ffc);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000b000);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000b004);
writel(0x000000ee&0xffffffff,ivp_cae_base_addr+0x0000b008);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000b00c);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000b010);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000b014);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000b018);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000b01c);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000c000);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000c004);
writel(0x00000015&0xffffffff,ivp_cae_base_addr+0x0000c008);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000c00c);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000c010);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000c014);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000c018);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000c01c);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000d000);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000d004);
writel(0x00000058&0xffffffff,ivp_cae_base_addr+0x0000d008);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000d00c);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000d010);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000d014);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000d018);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000d01c);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000e000);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000e004);
writel(0x000000ec&0xffffffff,ivp_cae_base_addr+0x0000e008);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000e00c);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000e010);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000e014);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000e018);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000e01c);
writel(0xca880d51&0xffffffff,ivp_cae_base_addr+0x0000f000);
writel(0x8f09040f&0xffffffff,ivp_cae_base_addr+0x0000f010);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f078);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f07c);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f200);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f204);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f208);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f210);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f214);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f218);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f21c);
writel(0x10000e8f&0xffffffff,ivp_cae_base_addr+0x0000f400);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f478);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f47c);
writel(0x00000003&0xffffffff,ivp_cae_base_addr+0x0000f600);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f604);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f608);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f60c);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f610);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f614);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f618);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f61c);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f620);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f628);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f62c);
writel(0x31e00000&0xffffffff,ivp_cae_base_addr+0x0000f800);
writel(0x02600000&0xffffffff,ivp_cae_base_addr+0x0000f804);
writel(0x181ecb3c&0xffffffff,ivp_cae_base_addr+0x0000f808);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f80c);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f810);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f814);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f818);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000f81c);
writel(0x00f09160&0xffffffff,ivp_cae_base_addr+0x0000fff4);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000fff8);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0000fffc);
writel(0x0000b200&0xffffffff,ivp_cae_base_addr+0x00010000);
writel(0x80003000&0xffffffff,ivp_cae_base_addr+0x00010100);
writel(0x000b0000&0xffffffff,ivp_cae_base_addr+0x00011000);
writel(0xdf673601&0xffffffff,ivp_cae_base_addr+0x00011004);
writel(0x00000108&0xffffffff,ivp_cae_base_addr+0x00011008);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001100c);
writel(0x00170000&0xffffffff,ivp_cae_base_addr+0x00011018);
writel(0x40000090&0xffffffff,ivp_cae_base_addr+0x0001101c);
writel(0xd93f0367&0xffffffff,ivp_cae_base_addr+0x00011020);
writel(0x96bf6362&0xffffffff,ivp_cae_base_addr+0x00011024);
writel(0x9d02f3f5&0xffffffff,ivp_cae_base_addr+0x00011028);
writel(0x0000000f&0xffffffff,ivp_cae_base_addr+0x0001102c);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011030);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011040);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011044);
writel(0x9dd8393c&0xffffffff,ivp_cae_base_addr+0x00011048);
writel(0x827a1e64&0xffffffff,ivp_cae_base_addr+0x0001104c);
writel(0x63cf8866&0xffffffff,ivp_cae_base_addr+0x00011050);
writel(0x5e20a981&0xffffffff,ivp_cae_base_addr+0x00011054);
writel(0xe02c5145&0xffffffff,ivp_cae_base_addr+0x00011058);
writel(0x60c23620&0xffffffff,ivp_cae_base_addr+0x0001105c);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011060);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011064);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011068);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001106c);
writel(0x36eacf95&0xffffffff,ivp_cae_base_addr+0x00011070);
writel(0x37c78e30&0xffffffff,ivp_cae_base_addr+0x00011074);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011080);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011084);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011088);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001108c);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011090);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011094);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011098);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001109c);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110a0);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110a4);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110a8);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110ac);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110b0);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110b4);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110b8);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110bc);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110c0);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110c4);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110c8);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110cc);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110d0);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110d4);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110d8);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110dc);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110e0);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110e4);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110e8);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110ec);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110f0);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110f4);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110f8);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000110fc);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011100);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011104);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011108);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001110c);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011110);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011114);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011118);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001111c);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011140);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011144);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011148);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001114c);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011150);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011154);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011158);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001115c);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011160);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011164);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011168);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001116c);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011170);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011174);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011178);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001117c);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011180);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011184);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011188);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001118c);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011190);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011194);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011198);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001119c);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000111a0);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000111a4);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000111a8);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000111ac);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000111b0);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000111b4);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000111b8);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000111bc);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000111c0);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000111c4);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000111c8);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000111cc);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000111d0);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000111d4);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000111d8);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000111dc);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000111e4);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011200);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011204);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011208);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001120c);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011210);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011214);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011218);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001121c);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011220);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011224);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011228);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001122c);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011230);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011234);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011238);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001123c);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011240);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011244);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011248);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001124c);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011250);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011254);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011258);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001125c);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011260);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011264);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011268);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001126c);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011270);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011274);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011278);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001127c);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011280);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011284);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011288);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001128c);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011290);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011294);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011298);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001129c);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000112a4);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000112c0);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000112c4);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000112c8);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000112cc);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000112d0);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000112d4);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000112d8);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000112dc);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000112e0);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000112e4);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000112e8);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000112ec);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000112f0);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011300);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011304);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011308);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001130c);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011310);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011314);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011318);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001131c);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011320);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011324);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011328);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001132c);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011330);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011334);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011338);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001133c);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011340);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011344);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011348);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001134c);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011350);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011354);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011358);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001135c);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011360);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011364);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011368);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001136c);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011370);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011374);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011378);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001137c);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011380);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011384);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011388);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001138c);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011390);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011394);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011398);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001139c);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000113c0);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000113c4);
writel(0x00000002&0xffffffff,ivp_cae_base_addr+0x000113c8);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000113cc);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000113d0);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000113d4);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000113d8);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000113dc);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000113f8);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x000113fc);
writel(0x400000e6&0xffffffff,ivp_cae_base_addr+0x00011c00);
writel(0xc0000000&0xffffffff,ivp_cae_base_addr+0x00011d00);
writel(0x00000012&0xffffffff,ivp_cae_base_addr+0x00011f00);
writel(0x00000012&0xffffffff,ivp_cae_base_addr+0x00011f04);
writel(0x00000004&0xffffffff,ivp_cae_base_addr+0x00011f08);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011f0c);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011f10);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011f14);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011f18);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011f1c);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011ff0);
writel(0x80000001&0xffffffff,ivp_cae_base_addr+0x00011ff4);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011ff8);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x00011ffc);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001ffe4);
writel(0x00590212&0xffffffff,ivp_cae_base_addr+0x0001ffe8);
readl(ivp_cae_base_addr+0x0001ffec);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001ffec);
writel(0x0004010d&0xffffffff,ivp_cae_base_addr+0x0001fff4);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001fff8);
writel(0x00000000&0xffffffff,ivp_cae_base_addr+0x0001fffc);
if((readl(ivp_cae_base_addr+0x00000000)&0xffffffff)==(0x27d33df6&0xffffffff))
cnt++;
else
printf("cnt: 3489\n");
if((readl(ivp_cae_base_addr+0x00000004)&0xffffffff)==(0x9455bdb7&0xffffffff))
cnt++;
else
printf("cnt: 3490\n");
if((readl(ivp_cae_base_addr+0x00000008)&0xffffffff)==(0x7d1d9856&0xffffffff))
cnt++;
else
printf("cnt: 3491\n");
if((readl(ivp_cae_base_addr+0x0000000c)&0xffffffff)==(0x3758b25a&0xffffffff))
cnt++;
else
printf("cnt: 3492\n");
if((readl(ivp_cae_base_addr+0x00000010)&0xffffffff)==(0x85fd6aa7&0xffffffff))
cnt++;
else
printf("cnt: 3493\n");
if((readl(ivp_cae_base_addr+0x00000014)&0xffffffff)==(0x17857ecc&0xffffffff))
cnt++;
else
printf("cnt: 3494\n");
if((readl(ivp_cae_base_addr+0x00000018)&0x00fffffc)==(0x00d93e80&0x00fffffc))
cnt++;
else
printf("cnt: 3495\n");
if((readl(ivp_cae_base_addr+0x0000001c)&0xe0ff003f)==(0x60b2001e&0xe0ff003f))
cnt++;
else
printf("cnt: 3496\n");
if((readl(ivp_cae_base_addr+0x00000020)&0xf03f00ff)==(0x101a0068&0xf03f00ff))
cnt++;
else
printf("cnt: 3497\n");
if((readl(ivp_cae_base_addr+0x00000024)&0xff010101)==(0x30010101&0xff010101))
cnt++;
else
printf("cnt: 3498\n");
if((readl(ivp_cae_base_addr+0x00000028)&0xffc00000)==(0xb0800000&0xffc00000))
cnt++;
else
printf("cnt: 3499\n");
if((readl(ivp_cae_base_addr+0x0000002c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3500\n");
if((readl(ivp_cae_base_addr+0x00000030)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3501\n");
if((readl(ivp_cae_base_addr+0x00000034)&0x00fffffc)==(0x00da639c&0x00fffffc))
cnt++;
else
printf("cnt: 3502\n");
if((readl(ivp_cae_base_addr+0x00000038)&0x00fffffc)==(0x0044088c&0x00fffffc))
cnt++;
else
printf("cnt: 3503\n");
if((readl(ivp_cae_base_addr+0x0000003c)&0x00000000)==(0x0000003b&0x00000000))
cnt++;
else
printf("cnt: 3504\n");
if((readl(ivp_cae_base_addr+0x000007f8)&0xb7ffffff)==(0x80a35514&0xb7ffffff))
cnt++;
else
printf("cnt: 3505\n");
if((readl(ivp_cae_base_addr+0x000007fc)&0x0fffffff)==(0x027035ca&0x0fffffff))
cnt++;
else
printf("cnt: 3506\n");
if((readl(ivp_cae_base_addr+0x00000800)&0xffffffff)==(0x47c199e6&0xffffffff))
cnt++;
else
printf("cnt: 3507\n");
if((readl(ivp_cae_base_addr+0x00000804)&0xffffffff)==(0x2cd654f3&0xffffffff))
cnt++;
else
printf("cnt: 3508\n");
if((readl(ivp_cae_base_addr+0x00000808)&0xffffffff)==(0xffb581a4&0xffffffff))
cnt++;
else
printf("cnt: 3509\n");
if((readl(ivp_cae_base_addr+0x0000080c)&0xffffffff)==(0x21e4c18f&0xffffffff))
cnt++;
else
printf("cnt: 3510\n");
if((readl(ivp_cae_base_addr+0x00000818)&0x00fffffc)==(0x00bf2128&0x00fffffc))
cnt++;
else
printf("cnt: 3511\n");
if((readl(ivp_cae_base_addr+0x0000081c)&0xe0ff00ff)==(0xc01600b7&0xe0ff00ff))
cnt++;
else
printf("cnt: 3512\n");
if((readl(ivp_cae_base_addr+0x00000820)&0xf03f00ff)==(0xc02a004f&0xf03f00ff))
cnt++;
else
printf("cnt: 3513\n");
if((readl(ivp_cae_base_addr+0x00000824)&0xfff80101)==(0x32600101&0xfff80101))
cnt++;
else
printf("cnt: 3514\n");
if((readl(ivp_cae_base_addr+0x00000828)&0xff800000)==(0xeb000000&0xff800000))
cnt++;
else
printf("cnt: 3515\n");
if((readl(ivp_cae_base_addr+0x0000082c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3516\n");
if((readl(ivp_cae_base_addr+0x00000830)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3517\n");
if((readl(ivp_cae_base_addr+0x00000834)&0x00fffffc)==(0x001e73d8&0x00fffffc))
cnt++;
else
printf("cnt: 3518\n");
if((readl(ivp_cae_base_addr+0x00000838)&0x00fffffc)==(0x007f75ac&0x00fffffc))
cnt++;
else
printf("cnt: 3519\n");
if((readl(ivp_cae_base_addr+0x0000083c)&0x00000000)==(0x00000095&0x00000000))
cnt++;
else
printf("cnt: 3520\n");
if((readl(ivp_cae_base_addr+0x00000ff8)&0xb7ffffff)==(0x80a35514&0xb7ffffff))
cnt++;
else
printf("cnt: 3521\n");
if((readl(ivp_cae_base_addr+0x00000ffc)&0x0fffffff)==(0x027035ca&0x0fffffff))
cnt++;
else
printf("cnt: 3522\n");
if((readl(ivp_cae_base_addr+0x00001000)&0xffffffff)==(0x6ca2b5ac&0xffffffff))
cnt++;
else
printf("cnt: 3523\n");
if((readl(ivp_cae_base_addr+0x00001004)&0xffffffff)==(0xcf84d032&0xffffffff))
cnt++;
else
printf("cnt: 3524\n");
if((readl(ivp_cae_base_addr+0x00001008)&0xffffffff)==(0x632157e5&0xffffffff))
cnt++;
else
printf("cnt: 3525\n");
if((readl(ivp_cae_base_addr+0x0000100c)&0xffffffff)==(0x8602e901&0xffffffff))
cnt++;
else
printf("cnt: 3526\n");
if((readl(ivp_cae_base_addr+0x00001010)&0xffffffff)==(0x3e0d1f8b&0xffffffff))
cnt++;
else
printf("cnt: 3527\n");
if((readl(ivp_cae_base_addr+0x00001014)&0xffffffff)==(0x139d2854&0xffffffff))
cnt++;
else
printf("cnt: 3528\n");
if((readl(ivp_cae_base_addr+0x00001018)&0x00fffffc)==(0x001113b0&0x00fffffc))
cnt++;
else
printf("cnt: 3529\n");
if((readl(ivp_cae_base_addr+0x0000101c)&0xe0ff003f)==(0x609b0014&0xe0ff003f))
cnt++;
else
printf("cnt: 3530\n");
if((readl(ivp_cae_base_addr+0x00001020)&0xf03f00ff)==(0x40320070&0xf03f00ff))
cnt++;
else
printf("cnt: 3531\n");
if((readl(ivp_cae_base_addr+0x00001024)&0xff010101)==(0x30010000&0xff010101))
cnt++;
else
printf("cnt: 3532\n");
if((readl(ivp_cae_base_addr+0x00001028)&0xffc00000)==(0x1ac00000&0xffc00000))
cnt++;
else
printf("cnt: 3533\n");
if((readl(ivp_cae_base_addr+0x0000102c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3534\n");
if((readl(ivp_cae_base_addr+0x00001030)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3535\n");
if((readl(ivp_cae_base_addr+0x00001034)&0x00fffffc)==(0x00f51540&0x00fffffc))
cnt++;
else
printf("cnt: 3536\n");
if((readl(ivp_cae_base_addr+0x00001038)&0x00fffffc)==(0x00e8eae8&0x00fffffc))
cnt++;
else
printf("cnt: 3537\n");
if((readl(ivp_cae_base_addr+0x0000103c)&0x00000000)==(0x00000038&0x00000000))
cnt++;
else
printf("cnt: 3538\n");
if((readl(ivp_cae_base_addr+0x000017f8)&0xb7ffffff)==(0x80a35514&0xb7ffffff))
cnt++;
else
printf("cnt: 3539\n");
if((readl(ivp_cae_base_addr+0x000017fc)&0x0fffffff)==(0x027035ca&0x0fffffff))
cnt++;
else
printf("cnt: 3540\n");
if((readl(ivp_cae_base_addr+0x00001800)&0xffffffff)==(0xe203c78f&0xffffffff))
cnt++;
else
printf("cnt: 3541\n");
if((readl(ivp_cae_base_addr+0x00001804)&0xffffffff)==(0x3496aade&0xffffffff))
cnt++;
else
printf("cnt: 3542\n");
if((readl(ivp_cae_base_addr+0x00001808)&0xffffffff)==(0x2f20e63e&0xffffffff))
cnt++;
else
printf("cnt: 3543\n");
if((readl(ivp_cae_base_addr+0x0000180c)&0xffffffff)==(0xda884d65&0xffffffff))
cnt++;
else
printf("cnt: 3544\n");
if((readl(ivp_cae_base_addr+0x00001818)&0x00fffffc)==(0x006b6d14&0x00fffffc))
cnt++;
else
printf("cnt: 3545\n");
if((readl(ivp_cae_base_addr+0x0000181c)&0xe0ff00ff)==(0x0009003e&0xe0ff00ff))
cnt++;
else
printf("cnt: 3546\n");
if((readl(ivp_cae_base_addr+0x00001820)&0xf03f00ff)==(0x5004002a&0xf03f00ff))
cnt++;
else
printf("cnt: 3547\n");
if((readl(ivp_cae_base_addr+0x00001824)&0xfff80101)==(0x5d700001&0xfff80101))
cnt++;
else
printf("cnt: 3548\n");
if((readl(ivp_cae_base_addr+0x00001828)&0xff800000)==(0x6c800000&0xff800000))
cnt++;
else
printf("cnt: 3549\n");
if((readl(ivp_cae_base_addr+0x0000182c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3550\n");
if((readl(ivp_cae_base_addr+0x00001830)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3551\n");
if((readl(ivp_cae_base_addr+0x00001834)&0x00fffffc)==(0x00f9d0a4&0x00fffffc))
cnt++;
else
printf("cnt: 3552\n");
if((readl(ivp_cae_base_addr+0x00001838)&0x00fffffc)==(0x0048ca14&0x00fffffc))
cnt++;
else
printf("cnt: 3553\n");
if((readl(ivp_cae_base_addr+0x0000183c)&0x00000000)==(0x00000022&0x00000000))
cnt++;
else
printf("cnt: 3554\n");
if((readl(ivp_cae_base_addr+0x00001ff8)&0xb7ffffff)==(0x80a35514&0xb7ffffff))
cnt++;
else
printf("cnt: 3555\n");
if((readl(ivp_cae_base_addr+0x00001ffc)&0x0fffffff)==(0x027035ca&0x0fffffff))
cnt++;
else
printf("cnt: 3556\n");
if((readl(ivp_cae_base_addr+0x00002000)&0xffffffff)==(0xc7775a63&0xffffffff))
cnt++;
else
printf("cnt: 3557\n");
if((readl(ivp_cae_base_addr+0x00002004)&0xffffffff)==(0xa653d1d6&0xffffffff))
cnt++;
else
printf("cnt: 3558\n");
if((readl(ivp_cae_base_addr+0x00002008)&0xffffffff)==(0x7f11f5eb&0xffffffff))
cnt++;
else
printf("cnt: 3559\n");
if((readl(ivp_cae_base_addr+0x0000200c)&0xffffffff)==(0xe62a0303&0xffffffff))
cnt++;
else
printf("cnt: 3560\n");
if((readl(ivp_cae_base_addr+0x00002010)&0xffffffff)==(0xccf7a435&0xffffffff))
cnt++;
else
printf("cnt: 3561\n");
if((readl(ivp_cae_base_addr+0x00002014)&0xffffffff)==(0x44b52963&0xffffffff))
cnt++;
else
printf("cnt: 3562\n");
if((readl(ivp_cae_base_addr+0x00002018)&0x00fffffc)==(0x00ded4a0&0x00fffffc))
cnt++;
else
printf("cnt: 3563\n");
if((readl(ivp_cae_base_addr+0x0000201c)&0xe0ff003f)==(0x40cd0010&0xe0ff003f))
cnt++;
else
printf("cnt: 3564\n");
if((readl(ivp_cae_base_addr+0x00002020)&0xf03f00ff)==(0xf02300e4&0xf03f00ff))
cnt++;
else
printf("cnt: 3565\n");
if((readl(ivp_cae_base_addr+0x00002024)&0xff010101)==(0x27000000&0xff010101))
cnt++;
else
printf("cnt: 3566\n");
if((readl(ivp_cae_base_addr+0x00002028)&0xffc00000)==(0xbfc00000&0xffc00000))
cnt++;
else
printf("cnt: 3567\n");
if((readl(ivp_cae_base_addr+0x0000202c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3568\n");
if((readl(ivp_cae_base_addr+0x00002030)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3569\n");
if((readl(ivp_cae_base_addr+0x00002034)&0x00fffffc)==(0x004e7dcc&0x00fffffc))
cnt++;
else
printf("cnt: 3570\n");
if((readl(ivp_cae_base_addr+0x00002038)&0x00fffffc)==(0x0045a490&0x00fffffc))
cnt++;
else
printf("cnt: 3571\n");
if((readl(ivp_cae_base_addr+0x0000203c)&0x00000000)==(0x00000002&0x00000000))
cnt++;
else
printf("cnt: 3572\n");
if((readl(ivp_cae_base_addr+0x000027f8)&0xb7ffffff)==(0x80a35514&0xb7ffffff))
cnt++;
else
printf("cnt: 3573\n");
if((readl(ivp_cae_base_addr+0x000027fc)&0x0fffffff)==(0x027035ca&0x0fffffff))
cnt++;
else
printf("cnt: 3574\n");
if((readl(ivp_cae_base_addr+0x00002800)&0xffffffff)==(0xf44db818&0xffffffff))
cnt++;
else
printf("cnt: 3575\n");
if((readl(ivp_cae_base_addr+0x00002804)&0xffffffff)==(0xc2860bff&0xffffffff))
cnt++;
else
printf("cnt: 3576\n");
if((readl(ivp_cae_base_addr+0x00002808)&0xffffffff)==(0xa5d4b64d&0xffffffff))
cnt++;
else
printf("cnt: 3577\n");
if((readl(ivp_cae_base_addr+0x0000280c)&0xffffffff)==(0xa40b0d97&0xffffffff))
cnt++;
else
printf("cnt: 3578\n");
if((readl(ivp_cae_base_addr+0x00002818)&0x00fffffc)==(0x00c26100&0x00fffffc))
cnt++;
else
printf("cnt: 3579\n");
if((readl(ivp_cae_base_addr+0x0000281c)&0xe0ff00ff)==(0x40cd00aa&0xe0ff00ff))
cnt++;
else
printf("cnt: 3580\n");
if((readl(ivp_cae_base_addr+0x00002820)&0xf03f00ff)==(0x90280063&0xf03f00ff))
cnt++;
else
printf("cnt: 3581\n");
if((readl(ivp_cae_base_addr+0x00002824)&0xfff80101)==(0xff980000&0xfff80101))
cnt++;
else
printf("cnt: 3582\n");
if((readl(ivp_cae_base_addr+0x00002828)&0xff800000)==(0xaa000000&0xff800000))
cnt++;
else
printf("cnt: 3583\n");
if((readl(ivp_cae_base_addr+0x0000282c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3584\n");
if((readl(ivp_cae_base_addr+0x00002830)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3585\n");
if((readl(ivp_cae_base_addr+0x00002834)&0x00fffffc)==(0x00e99904&0x00fffffc))
cnt++;
else
printf("cnt: 3586\n");
if((readl(ivp_cae_base_addr+0x00002838)&0x00fffffc)==(0x005494ec&0x00fffffc))
cnt++;
else
printf("cnt: 3587\n");
if((readl(ivp_cae_base_addr+0x0000283c)&0x00000000)==(0x00000006&0x00000000))
cnt++;
else
printf("cnt: 3588\n");
if((readl(ivp_cae_base_addr+0x00002ff8)&0xb7ffffff)==(0x80a35514&0xb7ffffff))
cnt++;
else
printf("cnt: 3589\n");
if((readl(ivp_cae_base_addr+0x00002ffc)&0x0fffffff)==(0x027035ca&0x0fffffff))
cnt++;
else
printf("cnt: 3590\n");
if((readl(ivp_cae_base_addr+0x00003000)&0xffffffff)==(0x83427047&0xffffffff))
cnt++;
else
printf("cnt: 3591\n");
if((readl(ivp_cae_base_addr+0x00003004)&0xffffffff)==(0x3e981dba&0xffffffff))
cnt++;
else
printf("cnt: 3592\n");
if((readl(ivp_cae_base_addr+0x00003008)&0xffffffff)==(0x8163b01c&0xffffffff))
cnt++;
else
printf("cnt: 3593\n");
if((readl(ivp_cae_base_addr+0x0000300c)&0xffffffff)==(0x887930e2&0xffffffff))
cnt++;
else
printf("cnt: 3594\n");
if((readl(ivp_cae_base_addr+0x00003010)&0xffffffff)==(0x1ffe3005&0xffffffff))
cnt++;
else
printf("cnt: 3595\n");
if((readl(ivp_cae_base_addr+0x00003014)&0xffffffff)==(0xcfdf0025&0xffffffff))
cnt++;
else
printf("cnt: 3596\n");
if((readl(ivp_cae_base_addr+0x00003018)&0x00fffffc)==(0x00edeaa0&0x00fffffc))
cnt++;
else
printf("cnt: 3597\n");
if((readl(ivp_cae_base_addr+0x0000301c)&0xe0ff003f)==(0x4042001f&0xe0ff003f))
cnt++;
else
printf("cnt: 3598\n");
if((readl(ivp_cae_base_addr+0x00003020)&0xf03f00ff)==(0x9022004c&0xf03f00ff))
cnt++;
else
printf("cnt: 3599\n");
if((readl(ivp_cae_base_addr+0x00003024)&0xff010101)==(0xaf010100&0xff010101))
cnt++;
else
printf("cnt: 3600\n");
if((readl(ivp_cae_base_addr+0x00003028)&0xffc00000)==(0x48400000&0xffc00000))
cnt++;
else
printf("cnt: 3601\n");
if((readl(ivp_cae_base_addr+0x0000302c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3602\n");
if((readl(ivp_cae_base_addr+0x00003030)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3603\n");
if((readl(ivp_cae_base_addr+0x00003034)&0x00fffffc)==(0x00c92058&0x00fffffc))
cnt++;
else
printf("cnt: 3604\n");
if((readl(ivp_cae_base_addr+0x00003038)&0x00fffffc)==(0x00530580&0x00fffffc))
cnt++;
else
printf("cnt: 3605\n");
if((readl(ivp_cae_base_addr+0x0000303c)&0x00000000)==(0x00000024&0x00000000))
cnt++;
else
printf("cnt: 3606\n");
if((readl(ivp_cae_base_addr+0x000037f8)&0xb7ffffff)==(0x80a35514&0xb7ffffff))
cnt++;
else
printf("cnt: 3607\n");
if((readl(ivp_cae_base_addr+0x000037fc)&0x0fffffff)==(0x027035ca&0x0fffffff))
cnt++;
else
printf("cnt: 3608\n");
if((readl(ivp_cae_base_addr+0x00003800)&0xffffffff)==(0x3529237d&0xffffffff))
cnt++;
else
printf("cnt: 3609\n");
if((readl(ivp_cae_base_addr+0x00003804)&0xffffffff)==(0xddd87aa8&0xffffffff))
cnt++;
else
printf("cnt: 3610\n");
if((readl(ivp_cae_base_addr+0x00003808)&0xffffffff)==(0x5966a727&0xffffffff))
cnt++;
else
printf("cnt: 3611\n");
if((readl(ivp_cae_base_addr+0x0000380c)&0xffffffff)==(0x20cdb8ba&0xffffffff))
cnt++;
else
printf("cnt: 3612\n");
if((readl(ivp_cae_base_addr+0x00003818)&0x00fffffc)==(0x003ef594&0x00fffffc))
cnt++;
else
printf("cnt: 3613\n");
if((readl(ivp_cae_base_addr+0x0000381c)&0xe0ff00ff)==(0x40aa000f&0xe0ff00ff))
cnt++;
else
printf("cnt: 3614\n");
if((readl(ivp_cae_base_addr+0x00003820)&0xf03f00ff)==(0x003200c2&0xf03f00ff))
cnt++;
else
printf("cnt: 3615\n");
if((readl(ivp_cae_base_addr+0x00003824)&0xfff80101)==(0x17100101&0xfff80101))
cnt++;
else
printf("cnt: 3616\n");
if((readl(ivp_cae_base_addr+0x00003828)&0xff800000)==(0x40000000&0xff800000))
cnt++;
else
printf("cnt: 3617\n");
if((readl(ivp_cae_base_addr+0x0000382c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3618\n");
if((readl(ivp_cae_base_addr+0x00003830)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3619\n");
if((readl(ivp_cae_base_addr+0x00003834)&0x00fffffc)==(0x00a77648&0x00fffffc))
cnt++;
else
printf("cnt: 3620\n");
if((readl(ivp_cae_base_addr+0x00003838)&0x00fffffc)==(0x00ca69b0&0x00fffffc))
cnt++;
else
printf("cnt: 3621\n");
if((readl(ivp_cae_base_addr+0x0000383c)&0x00000000)==(0x00000056&0x00000000))
cnt++;
else
printf("cnt: 3622\n");
if((readl(ivp_cae_base_addr+0x00003ff8)&0xb7ffffff)==(0x80a35514&0xb7ffffff))
cnt++;
else
printf("cnt: 3623\n");
if((readl(ivp_cae_base_addr+0x00003ffc)&0x0fffffff)==(0x027035ca&0x0fffffff))
cnt++;
else
printf("cnt: 3624\n");
if((readl(ivp_cae_base_addr+0x0000b000)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3625\n");
if((readl(ivp_cae_base_addr+0x0000b004)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3626\n");
if((readl(ivp_cae_base_addr+0x0000b008)&0x000000ff)==(0x000000ee&0x000000ff))
cnt++;
else
printf("cnt: 3627\n");
if((readl(ivp_cae_base_addr+0x0000b00c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3628\n");
if((readl(ivp_cae_base_addr+0x0000b010)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3629\n");
if((readl(ivp_cae_base_addr+0x0000b014)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3630\n");
if((readl(ivp_cae_base_addr+0x0000b018)&0x000001bf)==(0x00000008&0x000001bf))
cnt++;
else
printf("cnt: 3631\n");
if((readl(ivp_cae_base_addr+0x0000b01c)&0x0fffffff)==(0x014036c9&0x0fffffff))
cnt++;
else
printf("cnt: 3632\n");
if((readl(ivp_cae_base_addr+0x0000c000)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3633\n");
if((readl(ivp_cae_base_addr+0x0000c004)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3634\n");
if((readl(ivp_cae_base_addr+0x0000c008)&0x000000ff)==(0x00000015&0x000000ff))
cnt++;
else
printf("cnt: 3635\n");
if((readl(ivp_cae_base_addr+0x0000c00c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3636\n");
if((readl(ivp_cae_base_addr+0x0000c010)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3637\n");
if((readl(ivp_cae_base_addr+0x0000c014)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3638\n");
if((readl(ivp_cae_base_addr+0x0000c018)&0x000001bf)==(0x00000008&0x000001bf))
cnt++;
else
printf("cnt: 3639\n");
if((readl(ivp_cae_base_addr+0x0000c01c)&0x0fffffff)==(0x014036c9&0x0fffffff))
cnt++;
else
printf("cnt: 3640\n");
if((readl(ivp_cae_base_addr+0x0000d000)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3641\n");
if((readl(ivp_cae_base_addr+0x0000d004)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3642\n");
if((readl(ivp_cae_base_addr+0x0000d008)&0x000000ff)==(0x00000058&0x000000ff))
cnt++;
else
printf("cnt: 3643\n");
if((readl(ivp_cae_base_addr+0x0000d00c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3644\n");
if((readl(ivp_cae_base_addr+0x0000d010)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3645\n");
if((readl(ivp_cae_base_addr+0x0000d014)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3646\n");
if((readl(ivp_cae_base_addr+0x0000d018)&0x000001bf)==(0x00000008&0x000001bf))
cnt++;
else
printf("cnt: 3647\n");
if((readl(ivp_cae_base_addr+0x0000d01c)&0x0fffffff)==(0x014036c9&0x0fffffff))
cnt++;
else
printf("cnt: 3648\n");
if((readl(ivp_cae_base_addr+0x0000e000)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3649\n");
if((readl(ivp_cae_base_addr+0x0000e004)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3650\n");
if((readl(ivp_cae_base_addr+0x0000e008)&0x000000ff)==(0x000000ec&0x000000ff))
cnt++;
else
printf("cnt: 3651\n");
if((readl(ivp_cae_base_addr+0x0000e00c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3652\n");
if((readl(ivp_cae_base_addr+0x0000e010)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3653\n");
if((readl(ivp_cae_base_addr+0x0000e014)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3654\n");
if((readl(ivp_cae_base_addr+0x0000e018)&0x000001bf)==(0x00000008&0x000001bf))
cnt++;
else
printf("cnt: 3655\n");
if((readl(ivp_cae_base_addr+0x0000e01c)&0x0fffffff)==(0x014036c9&0x0fffffff))
cnt++;
else
printf("cnt: 3656\n");
if((readl(ivp_cae_base_addr+0x0000f000)&0xefff0fff)==(0xca880d51&0xefff0fff))
cnt++;
else
printf("cnt: 3657\n");
if((readl(ivp_cae_base_addr+0x0000f010)&0x8f8f8f8f)==(0x8f09040f&0x8f8f8f8f))
cnt++;
else
printf("cnt: 3658\n");
if((readl(ivp_cae_base_addr+0x0000f078)&0xb7ffffff)==(0x80a35514&0xb7ffffff))
cnt++;
else
printf("cnt: 3659\n");
if((readl(ivp_cae_base_addr+0x0000f07c)&0x0fffffff)==(0x027035ca&0x0fffffff))
cnt++;
else
printf("cnt: 3660\n");
if((readl(ivp_cae_base_addr+0x0000f200)&0x0000000f)==(0x00000000&0x0000000f))
cnt++;
else
printf("cnt: 3661\n");
if((readl(ivp_cae_base_addr+0x0000f204)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3662\n");
if((readl(ivp_cae_base_addr+0x0000f208)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3663\n");
if((readl(ivp_cae_base_addr+0x0000f210)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3664\n");
if((readl(ivp_cae_base_addr+0x0000f214)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3665\n");
if((readl(ivp_cae_base_addr+0x0000f218)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3666\n");
if((readl(ivp_cae_base_addr+0x0000f21c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3667\n");
if((readl(ivp_cae_base_addr+0x0000f400)&0xf000dfff)==(0x10000e8f&0xf000dfff))
cnt++;
else
printf("cnt: 3668\n");
if((readl(ivp_cae_base_addr+0x0000f478)&0xb7ffffff)==(0x80a35514&0xb7ffffff))
cnt++;
else
printf("cnt: 3669\n");
if((readl(ivp_cae_base_addr+0x0000f47c)&0x0fffffff)==(0x027035ca&0x0fffffff))
cnt++;
else
printf("cnt: 3670\n");
if((readl(ivp_cae_base_addr+0x0000f600)&0x0000000f)==(0x00000003&0x0000000f))
cnt++;
else
printf("cnt: 3671\n");
if((readl(ivp_cae_base_addr+0x0000f604)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3672\n");
if((readl(ivp_cae_base_addr+0x0000f608)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3673\n");
if((readl(ivp_cae_base_addr+0x0000f60c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3674\n");
if((readl(ivp_cae_base_addr+0x0000f610)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3675\n");
if((readl(ivp_cae_base_addr+0x0000f614)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3676\n");
if((readl(ivp_cae_base_addr+0x0000f618)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3677\n");
if((readl(ivp_cae_base_addr+0x0000f61c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3678\n");
if((readl(ivp_cae_base_addr+0x0000f620)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3679\n");
if((readl(ivp_cae_base_addr+0x0000f628)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3680\n");
if((readl(ivp_cae_base_addr+0x0000f62c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3681\n");
if((readl(ivp_cae_base_addr+0x0000f800)&0xfff00000)==(0x31e00000&0xfff00000))
cnt++;
else
printf("cnt: 3682\n");
if((readl(ivp_cae_base_addr+0x0000f804)&0xfff00000)==(0x02600000&0xfff00000))
cnt++;
else
printf("cnt: 3683\n");
if((readl(ivp_cae_base_addr+0x0000f808)&0xffffffff)==(0x181ecb3c&0xffffffff))
cnt++;
else
printf("cnt: 3684\n");
if((readl(ivp_cae_base_addr+0x0000f80c)&0x00000000)==(0x40000000&0x00000000))
cnt++;
else
printf("cnt: 3685\n");
if((readl(ivp_cae_base_addr+0x0000f810)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3686\n");
if((readl(ivp_cae_base_addr+0x0000f814)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3687\n");
if((readl(ivp_cae_base_addr+0x0000f818)&0x000001bf)==(0x00000020&0x000001bf))
cnt++;
else
printf("cnt: 3688\n");
if((readl(ivp_cae_base_addr+0x0000f81c)&0x0fffffff)==(0x014036c9&0x0fffffff))
cnt++;
else
printf("cnt: 3689\n");
if((readl(ivp_cae_base_addr+0x0000fff4)&0x00ff9ff1)==(0x00f09160&0x00ff9ff1))
cnt++;
else
printf("cnt: 3690\n");
if((readl(ivp_cae_base_addr+0x0000fff8)&0xb7ffffff)==(0x80a35514&0xb7ffffff))
cnt++;
else
printf("cnt: 3691\n");
if((readl(ivp_cae_base_addr+0x0000fffc)&0x0fffffff)==(0x027035ca&0x0fffffff))
cnt++;
else
printf("cnt: 3692\n");
if((readl(ivp_cae_base_addr+0x00010000)&0xc000ff00)==(0x0000b200&0xc000ff00))
cnt++;
else
printf("cnt: 3693\n");
if((readl(ivp_cae_base_addr+0x00010100)&0x8000ff00)==(0x80003000&0x8000ff00))
cnt++;
else
printf("cnt: 3694\n");
if((readl(ivp_cae_base_addr+0x00011000)&0x007b0000)==(0x000b0000&0x007b0000))
cnt++;
else
printf("cnt: 3695\n");
if((readl(ivp_cae_base_addr+0x00011004)&0xff6f7f3f)==(0xdf673601&0xff6f7f3f))
cnt++;
else
printf("cnt: 3696\n");
if((readl(ivp_cae_base_addr+0x00011008)&0x0000033f)==(0x00000108&0x0000033f))
cnt++;
else
printf("cnt: 3697\n");
if((readl(ivp_cae_base_addr+0x0001100c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3698\n");
if((readl(ivp_cae_base_addr+0x00011018)&0x00ff0000)==(0x00170000&0x00ff0000))
cnt++;
else
printf("cnt: 3699\n");
if((readl(ivp_cae_base_addr+0x0001101c)&0xc00000f8)==(0x40000090&0xc00000f8))
cnt++;
else
printf("cnt: 3700\n");
if((readl(ivp_cae_base_addr+0x00011020)&0xffffffff)==(0xd93f0367&0xffffffff))
cnt++;
else
printf("cnt: 3701\n");
if((readl(ivp_cae_base_addr+0x00011024)&0xffffffff)==(0x96bf6362&0xffffffff))
cnt++;
else
printf("cnt: 3702\n");
if((readl(ivp_cae_base_addr+0x00011028)&0xffffffff)==(0x9d02f3f5&0xffffffff))
cnt++;
else
printf("cnt: 3703\n");
if((readl(ivp_cae_base_addr+0x0001102c)&0x0000000f)==(0x0000000f&0x0000000f))
cnt++;
else
printf("cnt: 3704\n");
if((readl(ivp_cae_base_addr+0x00011030)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3705\n");
if((readl(ivp_cae_base_addr+0x00011040)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3706\n");
if((readl(ivp_cae_base_addr+0x00011044)&0x00000004)==(0x00000000&0x00000004))
cnt++;
else
printf("cnt: 3707\n");
if((readl(ivp_cae_base_addr+0x00011048)&0x00000000)==(0x9dd8393c&0x00000000))
cnt++;
else
printf("cnt: 3708\n");
if((readl(ivp_cae_base_addr+0x0001104c)&0x00000000)==(0x827a1e64&0x00000000))
cnt++;
else
printf("cnt: 3709\n");
if((readl(ivp_cae_base_addr+0x00011050)&0x00000000)==(0x63cf8866&0x00000000))
cnt++;
else
printf("cnt: 3710\n");
if((readl(ivp_cae_base_addr+0x00011054)&0x00000000)==(0x5e20a981&0x00000000))
cnt++;
else
printf("cnt: 3711\n");
if((readl(ivp_cae_base_addr+0x00011058)&0x00000000)==(0xe02c5145&0x00000000))
cnt++;
else
printf("cnt: 3712\n");
if((readl(ivp_cae_base_addr+0x0001105c)&0x00000000)==(0x60c23620&0x00000000))
cnt++;
else
printf("cnt: 3713\n");
if((readl(ivp_cae_base_addr+0x00011060)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3714\n");
if((readl(ivp_cae_base_addr+0x00011064)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3715\n");
if((readl(ivp_cae_base_addr+0x00011068)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3716\n");
if((readl(ivp_cae_base_addr+0x0001106c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3717\n");
if((readl(ivp_cae_base_addr+0x00011070)&0xffffffff)==(0x36eacf95&0xffffffff))
cnt++;
else
printf("cnt: 3718\n");
if((readl(ivp_cae_base_addr+0x00011074)&0xffffffff)==(0x37c78e30&0xffffffff))
cnt++;
else
printf("cnt: 3719\n");
if((readl(ivp_cae_base_addr+0x00011080)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3720\n");
if((readl(ivp_cae_base_addr+0x00011084)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3721\n");
if((readl(ivp_cae_base_addr+0x00011088)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3722\n");
if((readl(ivp_cae_base_addr+0x0001108c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3723\n");
if((readl(ivp_cae_base_addr+0x00011090)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3724\n");
if((readl(ivp_cae_base_addr+0x00011094)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3725\n");
if((readl(ivp_cae_base_addr+0x00011098)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3726\n");
if((readl(ivp_cae_base_addr+0x0001109c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3727\n");
if((readl(ivp_cae_base_addr+0x000110a0)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3728\n");
if((readl(ivp_cae_base_addr+0x000110a4)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3729\n");
if((readl(ivp_cae_base_addr+0x000110a8)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3730\n");
if((readl(ivp_cae_base_addr+0x000110ac)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3731\n");
if((readl(ivp_cae_base_addr+0x000110b0)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3732\n");
if((readl(ivp_cae_base_addr+0x000110b4)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3733\n");
if((readl(ivp_cae_base_addr+0x000110b8)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3734\n");
if((readl(ivp_cae_base_addr+0x000110bc)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3735\n");
if((readl(ivp_cae_base_addr+0x000110c0)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3736\n");
if((readl(ivp_cae_base_addr+0x000110c4)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3737\n");
if((readl(ivp_cae_base_addr+0x000110c8)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3738\n");
if((readl(ivp_cae_base_addr+0x000110cc)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3739\n");
if((readl(ivp_cae_base_addr+0x000110d0)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3740\n");
if((readl(ivp_cae_base_addr+0x000110d4)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3741\n");
if((readl(ivp_cae_base_addr+0x000110d8)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3742\n");
if((readl(ivp_cae_base_addr+0x000110dc)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3743\n");
if((readl(ivp_cae_base_addr+0x000110e0)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3744\n");
if((readl(ivp_cae_base_addr+0x000110e4)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3745\n");
if((readl(ivp_cae_base_addr+0x000110e8)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3746\n");
if((readl(ivp_cae_base_addr+0x000110ec)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3747\n");
if((readl(ivp_cae_base_addr+0x000110f0)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3748\n");
if((readl(ivp_cae_base_addr+0x000110f4)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3749\n");
if((readl(ivp_cae_base_addr+0x000110f8)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3750\n");
if((readl(ivp_cae_base_addr+0x000110fc)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3751\n");
if((readl(ivp_cae_base_addr+0x00011100)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3752\n");
if((readl(ivp_cae_base_addr+0x00011104)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3753\n");
if((readl(ivp_cae_base_addr+0x00011108)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3754\n");
if((readl(ivp_cae_base_addr+0x0001110c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3755\n");
if((readl(ivp_cae_base_addr+0x00011110)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3756\n");
if((readl(ivp_cae_base_addr+0x00011114)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3757\n");
if((readl(ivp_cae_base_addr+0x00011118)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3758\n");
if((readl(ivp_cae_base_addr+0x0001111c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3759\n");
if((readl(ivp_cae_base_addr+0x00011140)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3760\n");
if((readl(ivp_cae_base_addr+0x00011144)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3761\n");
if((readl(ivp_cae_base_addr+0x00011148)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3762\n");
if((readl(ivp_cae_base_addr+0x0001114c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3763\n");
if((readl(ivp_cae_base_addr+0x00011150)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3764\n");
if((readl(ivp_cae_base_addr+0x00011154)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3765\n");
if((readl(ivp_cae_base_addr+0x00011158)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3766\n");
if((readl(ivp_cae_base_addr+0x0001115c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3767\n");
if((readl(ivp_cae_base_addr+0x00011160)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3768\n");
if((readl(ivp_cae_base_addr+0x00011164)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3769\n");
if((readl(ivp_cae_base_addr+0x00011168)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3770\n");
if((readl(ivp_cae_base_addr+0x0001116c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3771\n");
if((readl(ivp_cae_base_addr+0x00011170)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3772\n");
if((readl(ivp_cae_base_addr+0x00011174)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3773\n");
if((readl(ivp_cae_base_addr+0x00011178)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3774\n");
if((readl(ivp_cae_base_addr+0x0001117c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3775\n");
if((readl(ivp_cae_base_addr+0x00011180)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3776\n");
if((readl(ivp_cae_base_addr+0x00011184)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3777\n");
if((readl(ivp_cae_base_addr+0x00011188)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3778\n");
if((readl(ivp_cae_base_addr+0x0001118c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3779\n");
if((readl(ivp_cae_base_addr+0x00011190)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3780\n");
if((readl(ivp_cae_base_addr+0x00011194)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3781\n");
if((readl(ivp_cae_base_addr+0x00011198)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3782\n");
if((readl(ivp_cae_base_addr+0x0001119c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3783\n");
if((readl(ivp_cae_base_addr+0x000111a0)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3784\n");
if((readl(ivp_cae_base_addr+0x000111a4)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3785\n");
if((readl(ivp_cae_base_addr+0x000111a8)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3786\n");
if((readl(ivp_cae_base_addr+0x000111ac)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3787\n");
if((readl(ivp_cae_base_addr+0x000111b0)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3788\n");
if((readl(ivp_cae_base_addr+0x000111b4)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3789\n");
if((readl(ivp_cae_base_addr+0x000111b8)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3790\n");
if((readl(ivp_cae_base_addr+0x000111bc)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3791\n");
if((readl(ivp_cae_base_addr+0x000111c0)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3792\n");
if((readl(ivp_cae_base_addr+0x000111c4)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3793\n");
if((readl(ivp_cae_base_addr+0x000111c8)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3794\n");
if((readl(ivp_cae_base_addr+0x000111cc)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3795\n");
if((readl(ivp_cae_base_addr+0x000111d0)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3796\n");
if((readl(ivp_cae_base_addr+0x000111d4)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3797\n");
if((readl(ivp_cae_base_addr+0x000111d8)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3798\n");
if((readl(ivp_cae_base_addr+0x000111dc)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3799\n");
if((readl(ivp_cae_base_addr+0x000111e4)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3800\n");
if((readl(ivp_cae_base_addr+0x00011200)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3801\n");
if((readl(ivp_cae_base_addr+0x00011204)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3802\n");
if((readl(ivp_cae_base_addr+0x00011208)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3803\n");
if((readl(ivp_cae_base_addr+0x0001120c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3804\n");
if((readl(ivp_cae_base_addr+0x00011210)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3805\n");
if((readl(ivp_cae_base_addr+0x00011214)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3806\n");
if((readl(ivp_cae_base_addr+0x00011218)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3807\n");
if((readl(ivp_cae_base_addr+0x0001121c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3808\n");
if((readl(ivp_cae_base_addr+0x00011220)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3809\n");
if((readl(ivp_cae_base_addr+0x00011224)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3810\n");
if((readl(ivp_cae_base_addr+0x00011228)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3811\n");
if((readl(ivp_cae_base_addr+0x0001122c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3812\n");
if((readl(ivp_cae_base_addr+0x00011230)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3813\n");
if((readl(ivp_cae_base_addr+0x00011234)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3814\n");
if((readl(ivp_cae_base_addr+0x00011238)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3815\n");
if((readl(ivp_cae_base_addr+0x0001123c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3816\n");
if((readl(ivp_cae_base_addr+0x00011240)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3817\n");
if((readl(ivp_cae_base_addr+0x00011244)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3818\n");
if((readl(ivp_cae_base_addr+0x00011248)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3819\n");
if((readl(ivp_cae_base_addr+0x0001124c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3820\n");
if((readl(ivp_cae_base_addr+0x00011250)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3821\n");
if((readl(ivp_cae_base_addr+0x00011254)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3822\n");
if((readl(ivp_cae_base_addr+0x00011258)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3823\n");
if((readl(ivp_cae_base_addr+0x0001125c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3824\n");
if((readl(ivp_cae_base_addr+0x00011260)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3825\n");
if((readl(ivp_cae_base_addr+0x00011264)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3826\n");
if((readl(ivp_cae_base_addr+0x00011268)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3827\n");
if((readl(ivp_cae_base_addr+0x0001126c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3828\n");
if((readl(ivp_cae_base_addr+0x00011270)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3829\n");
if((readl(ivp_cae_base_addr+0x00011274)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3830\n");
if((readl(ivp_cae_base_addr+0x00011278)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3831\n");
if((readl(ivp_cae_base_addr+0x0001127c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3832\n");
if((readl(ivp_cae_base_addr+0x00011280)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3833\n");
if((readl(ivp_cae_base_addr+0x00011284)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3834\n");
if((readl(ivp_cae_base_addr+0x00011288)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3835\n");
if((readl(ivp_cae_base_addr+0x0001128c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3836\n");
if((readl(ivp_cae_base_addr+0x00011290)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3837\n");
if((readl(ivp_cae_base_addr+0x00011294)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3838\n");
if((readl(ivp_cae_base_addr+0x00011298)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3839\n");
if((readl(ivp_cae_base_addr+0x0001129c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3840\n");
if((readl(ivp_cae_base_addr+0x000112a4)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3841\n");
if((readl(ivp_cae_base_addr+0x000112c0)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3842\n");
if((readl(ivp_cae_base_addr+0x000112c4)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3843\n");
if((readl(ivp_cae_base_addr+0x000112c8)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3844\n");
if((readl(ivp_cae_base_addr+0x000112cc)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3845\n");
if((readl(ivp_cae_base_addr+0x000112d0)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3846\n");
if((readl(ivp_cae_base_addr+0x000112d4)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3847\n");
if((readl(ivp_cae_base_addr+0x000112d8)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3848\n");
if((readl(ivp_cae_base_addr+0x000112dc)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3849\n");
if((readl(ivp_cae_base_addr+0x000112e0)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3850\n");
if((readl(ivp_cae_base_addr+0x000112e4)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3851\n");
if((readl(ivp_cae_base_addr+0x000112e8)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3852\n");
if((readl(ivp_cae_base_addr+0x000112ec)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3853\n");
if((readl(ivp_cae_base_addr+0x000112f0)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3854\n");
if((readl(ivp_cae_base_addr+0x00011300)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3855\n");
if((readl(ivp_cae_base_addr+0x00011304)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3856\n");
if((readl(ivp_cae_base_addr+0x00011308)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3857\n");
if((readl(ivp_cae_base_addr+0x0001130c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3858\n");
if((readl(ivp_cae_base_addr+0x00011310)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3859\n");
if((readl(ivp_cae_base_addr+0x00011314)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3860\n");
if((readl(ivp_cae_base_addr+0x00011318)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3861\n");
if((readl(ivp_cae_base_addr+0x0001131c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3862\n");
if((readl(ivp_cae_base_addr+0x00011320)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3863\n");
if((readl(ivp_cae_base_addr+0x00011324)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3864\n");
if((readl(ivp_cae_base_addr+0x00011328)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3865\n");
if((readl(ivp_cae_base_addr+0x0001132c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3866\n");
if((readl(ivp_cae_base_addr+0x00011330)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3867\n");
if((readl(ivp_cae_base_addr+0x00011334)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3868\n");
if((readl(ivp_cae_base_addr+0x00011338)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3869\n");
if((readl(ivp_cae_base_addr+0x0001133c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3870\n");
if((readl(ivp_cae_base_addr+0x00011340)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3871\n");
if((readl(ivp_cae_base_addr+0x00011344)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3872\n");
if((readl(ivp_cae_base_addr+0x00011348)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3873\n");
if((readl(ivp_cae_base_addr+0x0001134c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3874\n");
if((readl(ivp_cae_base_addr+0x00011350)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3875\n");
if((readl(ivp_cae_base_addr+0x00011354)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3876\n");
if((readl(ivp_cae_base_addr+0x00011358)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3877\n");
if((readl(ivp_cae_base_addr+0x0001135c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3878\n");
if((readl(ivp_cae_base_addr+0x00011360)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3879\n");
if((readl(ivp_cae_base_addr+0x00011364)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3880\n");
if((readl(ivp_cae_base_addr+0x00011368)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3881\n");
if((readl(ivp_cae_base_addr+0x0001136c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3882\n");
if((readl(ivp_cae_base_addr+0x00011370)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3883\n");
if((readl(ivp_cae_base_addr+0x00011374)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3884\n");
if((readl(ivp_cae_base_addr+0x00011378)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3885\n");
if((readl(ivp_cae_base_addr+0x0001137c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3886\n");
if((readl(ivp_cae_base_addr+0x00011380)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3887\n");
if((readl(ivp_cae_base_addr+0x00011384)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3888\n");
if((readl(ivp_cae_base_addr+0x00011388)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3889\n");
if((readl(ivp_cae_base_addr+0x0001138c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3890\n");
if((readl(ivp_cae_base_addr+0x00011390)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3891\n");
if((readl(ivp_cae_base_addr+0x00011394)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3892\n");
if((readl(ivp_cae_base_addr+0x00011398)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3893\n");
if((readl(ivp_cae_base_addr+0x0001139c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3894\n");
if((readl(ivp_cae_base_addr+0x000113c0)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3895\n");
if((readl(ivp_cae_base_addr+0x000113c4)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3896\n");
if((readl(ivp_cae_base_addr+0x000113c8)&0x0000000f)==(0x00000002&0x0000000f))
cnt++;
else
printf("cnt: 3897\n");
if((readl(ivp_cae_base_addr+0x000113cc)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3898\n");
if((readl(ivp_cae_base_addr+0x000113d0)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3899\n");
if((readl(ivp_cae_base_addr+0x000113d4)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3900\n");
if((readl(ivp_cae_base_addr+0x000113d8)&0x000001bf)==(0x00000004&0x000001bf))
cnt++;
else
printf("cnt: 3901\n");
if((readl(ivp_cae_base_addr+0x000113dc)&0x0fffffff)==(0x014036c9&0x0fffffff))
cnt++;
else
printf("cnt: 3902\n");
if((readl(ivp_cae_base_addr+0x000113f8)&0xffffffe0)==(0x7fc1fc00&0xffffffe0))
cnt++;
else
printf("cnt: 3903\n");
if((readl(ivp_cae_base_addr+0x000113fc)&0x0fffffff)==(0x04339f60&0x0fffffff))
cnt++;
else
printf("cnt: 3904\n");
if((readl(ivp_cae_base_addr+0x00011c00)&0xc00000ff)==(0x400000e6&0xc00000ff))
cnt++;
else
printf("cnt: 3905\n");
if((readl(ivp_cae_base_addr+0x00011d00)&0xc0000000)==(0xc0000000&0xc0000000))
cnt++;
else
printf("cnt: 3906\n");
if((readl(ivp_cae_base_addr+0x00011f00)&0x0000001f)==(0x00000012&0x0000001f))
cnt++;
else
printf("cnt: 3907\n");
if((readl(ivp_cae_base_addr+0x00011f04)&0x0000001f)==(0x00000012&0x0000001f))
cnt++;
else
printf("cnt: 3908\n");
if((readl(ivp_cae_base_addr+0x00011f08)&0x0000001f)==(0x00000004&0x0000001f))
cnt++;
else
printf("cnt: 3909\n");
if((readl(ivp_cae_base_addr+0x00011f0c)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3910\n");
if((readl(ivp_cae_base_addr+0x00011f10)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3911\n");
if((readl(ivp_cae_base_addr+0x00011f14)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3912\n");
if((readl(ivp_cae_base_addr+0x00011f18)&0x000001bf)==(0x00000005&0x000001bf))
cnt++;
else
printf("cnt: 3913\n");
if((readl(ivp_cae_base_addr+0x00011f1c)&0x0fffffff)==(0x014036c9&0x0fffffff))
cnt++;
else
printf("cnt: 3914\n");
if((readl(ivp_cae_base_addr+0x00011ff0)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3915\n");
if((readl(ivp_cae_base_addr+0x00011ff4)&0x80000001)==(0x80000001&0x80000001))
cnt++;
else
printf("cnt: 3916\n");
if((readl(ivp_cae_base_addr+0x00011ff8)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3917\n");
if((readl(ivp_cae_base_addr+0x00011ffc)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3918\n");
if((readl(ivp_cae_base_addr+0x0001ffe4)&0x00000000)==(0x00000000&0x00000000))
cnt++;
else
printf("cnt: 3919\n");
if((readl(ivp_cae_base_addr+0x0001ffe8)&0x087b031f)==(0x00590212&0x087b031f))
cnt++;
else
printf("cnt: 3920\n");
if((readl(ivp_cae_base_addr+0x0001ffec)&0x087b031f)==(0x00000000&0x087b031f))
cnt++;
else
printf("cnt: 3921\n");
if((readl(ivp_cae_base_addr+0x0001fff4)&0x000401ff)==(0x0004010d&0x000401ff))
cnt++;
else
printf("cnt: 3922\n");
if((readl(ivp_cae_base_addr+0x0001fff8)&0xc00fffff)==(0x00074751&0xc00fffff))
cnt++;
else
printf("cnt: 3923\n");
if((readl(ivp_cae_base_addr+0x0001fffc)&0x0fffffff)==(0x02319e61&0x0fffffff))
cnt++;
else
printf("cnt: 3924\n");
if(cnt==3924)
printf("eip97_reg_test Pass\n");
else
printf("eip97_reg_test Failed, cnt: %d\n",cnt);
}

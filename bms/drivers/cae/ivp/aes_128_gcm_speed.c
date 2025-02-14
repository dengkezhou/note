#include <common.h>
#include <malloc.h>

#define CMD_DSCR_PKT_LEN (0x59c)
#define RESULT_DSCR_PKT_LEN (CMD_DSCR_PKT_LEN + 0x20)
#define MACSEC_PAYLOAD_LEN (CMD_DSCR_PKT_LEN - 0xc)
#define OUTPUT_DATA_LOCATION (0x100000 / 2)

typedef struct {
	unsigned int *context_ptr;
	volatile unsigned int ivp_cae_base_addr;
} core_desc;

extern volatile unsigned int ivp_cae_base_addr;

static void aes_128_gcm_make_input_data(core_desc *cd, int enc)
{
	int i = 0, j = 0;
	unsigned int len = 0;

	if (enc) {
		if (CMD_DSCR_PKT_LEN % 24 == 0) {
			len = CMD_DSCR_PKT_LEN / 24;
		} else {
			len = CMD_DSCR_PKT_LEN / 24 + 1;
		}

		for (i = 0; i < len; i++) {
			*((unsigned int *)((unsigned long)cd->context_ptr+0x00000c98+4*j))=0x4fbcac33;
			j++;
			*((unsigned int *)((unsigned long)cd->context_ptr+0x00000c98+4*j))=0xb65841dc;
			j++;
			*((unsigned int *)((unsigned long)cd->context_ptr+0x00000c98+4*j))=0x7512ef0b;
			j++;
			*((unsigned int *)((unsigned long)cd->context_ptr+0x00000c98+4*j))=0x0cb970eb;
			j++;
			*((unsigned int *)((unsigned long)cd->context_ptr+0x00000c98+4*j))=0x1e75facf;
			j++;
			*((unsigned int *)((unsigned long)cd->context_ptr+0x00000c98+4*j))=0x69c31914;
			j++;
		}
	} else {
		if (CMD_DSCR_PKT_LEN % 56 == 0) {
			len = CMD_DSCR_PKT_LEN / 56;
		} else {
			len = CMD_DSCR_PKT_LEN / 56 + 1;
		}

		for (i = 0; i < len; i++) {
			*((unsigned int *)((unsigned long)cd->context_ptr+0x00000cb4))=0x4fbcac33;
			j++;
			*((unsigned int *)((unsigned long)cd->context_ptr+0x00000cb4+4*1))=0xb65841dc;
			j++;
			*((unsigned int *)((unsigned long)cd->context_ptr+0x00000cb4+4*2))=0x7512ef0b;
			j++;
			*((unsigned int *)((unsigned long)cd->context_ptr+0x00000cb4+4*3))=0x0c2ce588;
			j++;
			*((unsigned int *)((unsigned long)cd->context_ptr+0x00000cb4+4*4))=0x21430000;
			j++;
			*((unsigned int *)((unsigned long)cd->context_ptr+0x00000cb4+4*5))=0x35651ead;
			j++;
			*((unsigned int *)((unsigned long)cd->context_ptr+0x00000cb4+4*6))=0x2537f20a;
			j++;
			*((unsigned int *)((unsigned long)cd->context_ptr+0x00000cb4+4*7))=0x8c3b321b;
			j++;
			*((unsigned int *)((unsigned long)cd->context_ptr+0x00000cb4+4*8))=0xa79885a5;
			j++;
			*((unsigned int *)((unsigned long)cd->context_ptr+0x00000cb4+4*9))=0x4b2cf08e;
			j++;
			*((unsigned int *)((unsigned long)cd->context_ptr+0x00000cb4+4*10))=0x7c631e9d;
			j++;
			*((unsigned int *)((unsigned long)cd->context_ptr+0x00000cb4+4*11))=0x9b4032c1;
			j++;
			*((unsigned int *)((unsigned long)cd->context_ptr+0x00000cb4+4*12))=0xde06f4ba;
			j++;
			*((unsigned int *)((unsigned long)cd->context_ptr+0x00000cb4+4*13))=0xb6c80033;
			j++;
		}
	}
}


static void aes_128_gcm_prepare(core_desc *cd)
{
if(!cd->context_ptr)
printf("cd->context_ptr malloc failed!\n");
#if defined(CONFIG_COMPILE_FPGA) || defined(CONFIG_COMPILE_ASIC)
//memset(cd->context_ptr,0,64*1024);
#endif
writel(0xa7050f08&0xffffffff,cd->ivp_cae_base_addr+0x0000f000);
writel(0x8000c807&0xffffffff,cd->ivp_cae_base_addr+0x0000f400);
writel(0x00007500&0xffffffff,cd->ivp_cae_base_addr+0x00010100);
writel(0x0000f800&0xffffffff,cd->ivp_cae_base_addr+0x00010000);
writel(0x00000087&0xffffffff,cd->ivp_cae_base_addr+0x00011c00);
writel(0x00410000&0xffffffff,cd->ivp_cae_base_addr+0x00011000);
writel(0x00000225&0xffffffff,cd->ivp_cae_base_addr+0x00011008);
writel(0x80000000&0xffffffff,cd->ivp_cae_base_addr+0x0000f200);
writel(0x80000000&0xffffffff,cd->ivp_cae_base_addr+0x0000f600);
readl(cd->ivp_cae_base_addr+0x0000f200);
writel(0x40000000&0xffffffff,cd->ivp_cae_base_addr+0x0000f200);
readl(cd->ivp_cae_base_addr+0x0000f600);
writel(0x40000000&0xffffffff,cd->ivp_cae_base_addr+0x0000f600);
writel(((unsigned long)cd->context_ptr+0x00000000)&0xffffffffffffffff,cd->ivp_cae_base_addr+0x00000008);
writel((((unsigned long)cd->context_ptr+0x00000000)>>32)&(0xffffffffffffffff>>32),cd->ivp_cae_base_addr+0x00000008+0x4);
writel(((unsigned long)cd->context_ptr+0x00000000)&0xffffffffffffffff,cd->ivp_cae_base_addr+0x00000010);
writel((((unsigned long)cd->context_ptr+0x00000000)>>32)&(0xffffffffffffffff>>32),cd->ivp_cae_base_addr+0x00000010+0x4);
writel(0x00000000&0xffffffff,cd->ivp_cae_base_addr+0x00000020);
writel(0x80000000&0xffffffff,cd->ivp_cae_base_addr+0x0000002c);
writel(0x00000000&0xffffffff,cd->ivp_cae_base_addr+0x00000034);
writel(0x00000000&0xffffffff,cd->ivp_cae_base_addr+0x00000038);
writel(0x00000600&0xffffffff,cd->ivp_cae_base_addr+0x00000018);
writel(((unsigned long)cd->context_ptr+0x00000000)&0xffffffffffffffff,cd->ivp_cae_base_addr+0x00000000);
writel((((unsigned long)cd->context_ptr+0x00000000)>>32)&(0xffffffffffffffff>>32),cd->ivp_cae_base_addr+0x00000000+0x4);
writel(0x80000000&0xffffffff,cd->ivp_cae_base_addr+0x00000030);
writel(0x01000000&0xffffffff,cd->ivp_cae_base_addr+0x00000024);
writel(0x40060006&0xffffffff,cd->ivp_cae_base_addr+0x0000001c);
writel(0x0000003f&0xffffffff,cd->ivp_cae_base_addr+0x0000003c);
writel(0x00120012&0xffffffff,cd->ivp_cae_base_addr+0x00000020);
readl(cd->ivp_cae_base_addr+0x0000f010);
writel(0x0000000f&0xffffffff,cd->ivp_cae_base_addr+0x0000f010);
readl(cd->ivp_cae_base_addr+0x0000f200);
writel(0x40000001&0xffffffff,cd->ivp_cae_base_addr+0x0000f200);
writel(0x01000000&0xffffffff,cd->ivp_cae_base_addr+0x00000824);
writel(((unsigned long)cd->context_ptr+0x00000000)&0xffffffffffffffff,cd->ivp_cae_base_addr+0x00000808);
writel((((unsigned long)cd->context_ptr+0x00000000)>>32)&(0xffffffffffffffff>>32),cd->ivp_cae_base_addr+0x00000808+0x4);
writel(((unsigned long)cd->context_ptr+0x00000600)&0xffffffffffffffff,cd->ivp_cae_base_addr+0x00000800);
writel((((unsigned long)cd->context_ptr+0x00000600)>>32)&(0xffffffffffffffff>>32),cd->ivp_cae_base_addr+0x00000800+0x4);
writel(0x00000600&0xffffffff,cd->ivp_cae_base_addr+0x00000818);
writel(0x00060006&0xffffffff,cd->ivp_cae_base_addr+0x0000081c);
writel(0x00080018&0xffffffff,cd->ivp_cae_base_addr+0x00000820);
writel(0x80000000&0xffffffff,cd->ivp_cae_base_addr+0x0000082c);
writel(0x80000000&0xffffffff,cd->ivp_cae_base_addr+0x00000830);
writel(0x00000000&0xffffffff,cd->ivp_cae_base_addr+0x00000834);
writel(0x00000000&0xffffffff,cd->ivp_cae_base_addr+0x00000838);
writel(0x00000000&0xffffffff,cd->ivp_cae_base_addr+0x00000828);
writel(0x000000ff&0xffffffff,cd->ivp_cae_base_addr+0x0000083c);
readl(cd->ivp_cae_base_addr+0x0000f410);
writel(0x0000000f&0xffffffff,cd->ivp_cae_base_addr+0x0000f410);
readl(cd->ivp_cae_base_addr+0x0000f600);
writel(0x40000001&0xffffffff,cd->ivp_cae_base_addr+0x0000f600);
*((unsigned int *)((unsigned long)cd->context_ptr+0x00000c00))=0x124b0b06;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00000c00+4*1))=0x4a020462;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00000c00+4*2))=0x268b6032;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00000c00+4*3))=0x6725fbfd;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00000c00+4*4))=0xea7ee0ae;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00000c00+4*5))=0xab7f7f52;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00000c00+4*6))=0x13b75384;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00000c00+4*7))=0xfe5a8063;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00000c00+4*8))=0x3f753964;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00000c00+4*9))=0x810879d4;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00000c00+4*10))=0x00004320;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00000c00+4*11))=0x35651ead;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00000c00+4*12))=0x2537f20a;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00000c34))=0x124b0b06;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00000c34+4*1))=0x4a020462;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00000c34+4*2))=0x0e2f153b;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00000c34+4*3))=0x9c9c2ca3;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00000c34+4*4))=0xe04883b4;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00000c34+4*5))=0x84a1755a;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00000c34+4*6))=0x62e76ae2;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00000c34+4*7))=0x0266f22b;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00000c34+4*8))=0xfb56a314;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00000c34+4*9))=0x9a7579d7;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00000c34+4*10))=0x00008764;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00000c34+4*11))=0x96f03238;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00000c34+4*12))=0x0000630c;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00000c68))=0x0300000c;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00000c68+4*1))=0x23d80004;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00000c68+4*2))=0x0c2ce588;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00000c68+4*3))=0x93996004;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00000c68+4*4))=0x9bd94008;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00000c68+4*5))=0x35651ead;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00000c68+4*6))=0x2537f20a;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00000c68+4*7))=0xa082001c;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00000c68+4*8))=0x25000010;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00000c68+4*9))=0x0f020000 | MACSEC_PAYLOAD_LEN;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00000c68+4*10))=0x21e60010;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00000c68+4*11))=0xe12e180a;

*((unsigned int *)((unsigned long)cd->context_ptr+0x00000600))=0x04c00000 | RESULT_DSCR_PKT_LEN;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00000600+4*1))=OUTPUT_DATA_LOCATION;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00000600+4*2))=0x77777777;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00000600+4*3))=0x77777777;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00000600+4*4))=0x77777777;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00000600+4*5))=0x77777777;
writel(0x00000018&0xffffffff,cd->ivp_cae_base_addr+0x0000082c);
writel(0x0000017a&0xffffffff,cd->ivp_cae_base_addr+0x00000028);
while(1){
if((readl(cd->ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(cd->ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,cd->ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)cd->context_ptr+0x00000000))=0x0cc00000 | CMD_DSCR_PKT_LEN;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00000000+4*1))=0x00000c98;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00000000+4*2))=0x00000c68;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00000000+4*3))=0x00220000 | CMD_DSCR_PKT_LEN;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00000000+4*4))=0x00441030;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00000000+4*5))=0x00000c00+(unsigned long)cd->context_ptr;
}

static void aes_128_gcm_start(core_desc *cd)
{
writel(0x00000018&0xffffffff,cd->ivp_cae_base_addr+0x0000002c);
writel(0x00000006&0xffffffff,cd->ivp_cae_base_addr+0x00000828);
}

static void aes_128_gcm_finish(core_desc *cd)
{
while(1){
if((readl(cd->ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(cd->ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,cd->ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)cd->context_ptr+OUTPUT_DATA_LOCATION,"\x33\xac\xbc\x4f\xdc\x41\x58\xb6\x0b\xef\x12\x75\x88\xe5\x2c\x0c\x00\x00\x43\x21\xad\x1e\x65\x35\x0a\xf2\x37\x25\x1b\x32\x3b\x8c\xa5\x85\x98\xa7\x8e\xf0\x2c\x4b\x5f\x0f\x86\x50\x58\x5b\x5f\x93\x5d\x39\x8f\xc1\xad\x80\x97\x0c\xa6\x53\x25\xea\xc4\x0f\x62\x3f\x8b\x4f\xff\xe2\x55\x54\x84\x26\xfa\x49\x69\x83\x1e\x4b\xcf\xe5\x82\x68\xbe\x4a\x9a\x8f\x39\x07\x70\x63\x1d\x21\x33\x25\x2b\x2a\x19\x6c\xfd\x08\xd3\xea\x31\xca\x60\x70\x01\x7c\xdd\x28\x24\xb9\x80\xaa\xc4\xbd\x56\xbf\x15\x43\x12\xc6\x28\x61\xc2\xd5\x33\x10\xdc\xf7\x90\x12\x54\x6c\x7d\x18\x85\x9a\xe0\xca\x58\x72\xdd\xa8\x74\xec\xc1\xc2\xcc\xd4\xf3\x90\x35\x6a\xef\xe2\x26\xf2\x4d\xd3\x94\x2b\x37\xf6\x3b\x3d\xe0\x1b\x7b\xde\x8e\x6c\x5e\xf5\x64\x3d\x03\xcd\x23\x49\x7d\xaf\x28\x62\xbb\xf7\xe1\x11\xb2\x37\x1c\xc4\x4d\x22\x63\x9e\x00\x63\x70\xa1\xc1\xb8\x73\x93\x38\xf8\x94\x65\x58\x5e\x22\x72\x0c\x0e\x96\x84\xfa\x5e\x82\x5c\xb0\xfb\x53\x52\x84\x04\xdc\xb5\x9e\x57\x7c\x75\x8b\xf8\xf5\xb6\x82\xcf\x60\x17\x81\x05\x1f\xaa\xac\xcc\xcb\xff\xa0\x58\x37\x14\xe3\xcb\x74\x12\x6e\x9c\x38\x87\xef\x98\x2f\x80\x48\x70\xea\x9d\xc2\x26\xa8\x2c\x55\x78\x94\x15\x46\x31\x96\xa7\x4d\xcf\x0d\x2d\x0a\x07\xc4\x60\xf1\x86\xf5\xb2\xb4\x26\x5e\x1c\x62\xe3\x5a\x07\x5a\x18\x61\xd9\x19\xad\x85\x30\x1b\x9c\xfa\x5a\x8d\x85\x05\xf7\x0f\xa8\x4b\x82\x9e\xd7\x71\x3c\x18\x33\xaa\x11\x32\xfa\x71\xe6\x84\x6c\x0c\x48\x0c\xe9\x87\x40\xe8\x22\xa2\x73\x36\xff\x36\x00\xc3\xc5\x12\x74\xdc\xdd\x4e\x44\xb9\x9b\x99\xe3\x9c\xbf\xe6\xd4\x22\x6f\x32\x7d\x85\xf9\x70\xe5\x89\x49\xfa\x04\x88\x1b\x49\x14\x16\xa3\xc7\x65\x4c\x79\x1a\xe4\x56\xca\x7c\xbb\x8b\xb2\x1c\x4c\xe3\xd0\x19\x7b\x1c\xb5\x68\x80\x45\x26\x6f\x34\x3d\x5f\x8a\xe2\xa4\xab\x36\xda\x0a\xed\xbb\x3d\x01\x82\xca\x6a\xae\x24\xbf\x4d\x5b\x01\x83\x0d\xe8\xe8\x78\xcf\x75\xb1\x72\xff\x09\x72\x1c\x56\x04\x52\xdc\xa4\xae\xb4\x7d\xaa\xd1\xa3\xa2\x5c\xc9\x84\x83\x04\xf8\xad\xcd\xd1\x00\x57\xfa\xd8\xc9\xb2\xd4\xc2\xd8\xda\xf6\xb5\xdd\x47\xc0\xd4\xe7\x31\x69\x5f\xc3\x30\x4e\xb4\x44\xd4\x25\x6e\x4e\xe6\x1f\xe8\x1f\x30\x1b\x99\xdd\xa4\xae\x1a\x10\x29\x3c\x17\x33\x5b\x0c\xbd\x05\x35\x01\x63\xb7\x09\x07\xcb\xb6\x38\xac\x91\xc3\xe7\x44\x1a\xfa\x26\xf9\xc8\x55\x71\x16\x31\x2b\xa7\x12\xfa\xc2\x3b\x5b\xc2\xcf\xf5\xbd\xd9\x63\xa8\x9e\xc0\xca\x39\x33\x92\xd4\x85\xa3\x79\xb2\x3d\xe0\xc6\x92\x39\x37\x60\x25\x0c\xf7\xfc\x2a\x05\x5d\xcd\xbe\xa2\x45\x0b\x08\x77\x99\xd2\x9a\xcd\xad\xc5\xf3\x1d\x76\xfe\xe3\x47\x59\xd1\xed\xf9\x43\xe5\xd4\xda\x89\xe5\x3e\x1e\x35\x5b\x27\x34\x7a\x2f\xa7\xc6\xcc\xfd\xbe\x51\xec\x14\x71\x39\xd4\x0d\x64\x7f\xbb\x6e\x8c\x64\xf9\x97\xa0\x4f\x5e\x82\x93\x81\x32\xd0\x2c\x97\xcd\x8e\x83\x16\xd8\x5d\xbc\x57\x5e\x86\xe7\x61\xf2\xf8\x0c\x14\x96\xc2\xee\xfe\x0e\xf3\x9f\x94\x81\xa1\x36\x16\x2b\x2c\x61\x96\x71\x6e\xe1\x2b\x68\xfa\x2c\xcc\xe8\x25\x9a\x97\x54\x32\xc7\xcc\x96\x35\x0b\xc4\xba\xfe\x71\xa7\x90\x24\xd9\x7c\xc4\xb6\xa7\x2e\x1f\xa6\xdc\x1e\xd9\xc2\xff\xd3\x97\x79\xc2\x68\x42\x25\x1c\x34\x1d\x02\x3f\x98\xc5\xee\x8a\xc3\x1b\x2e\x1c\x05\x37\xdd\x07\x9d\x8e\x34\x3c\xbd\xd4\x2b\x0b\x1e\xd4\x39\x0b\x9e\xa4\x9c\x97\x96\x71\x92\xf2\x24\x01\x9b\xca\x0f\x69\x68\x94\x53\x3c\x64\x2c\x22\x7b\x62\x57\xe8\xe5\x8c\x55\xa1\xbf\x91\x48\x14\x44\xa2\xe5\x8e\x99\xdd\xc3\xbb\xa0\x8e\xdb\x8e\x5d\x4f\x71\x8c\xeb\x86\x7f\xf8\xf2\xf4\xcc\x82\xa5\x13\xa7\xb7\xbc\x3e\xf0\x31\xc1\x71\xa9\x40\xbe\x6c\x83\x2c\x55\xd6\x5d\x78\x23\x31\xf3\xd2\x40\xc5\xbb\x29\x7e\x72\x78\xd7\x8a\x9a\x48\xde\x60\x71\x46\xa5\xff\xef\x4f\xf3\x1d\x8b\x7b\x1c\x82\x54\x35\x32\x8e\x1e\xb3\xe9\x7a\xe0\x80\x4f\xcc\x7d\xf1\x52\x7f\x05\xbe\x97\xf6\x39\x39\xa3\x14\xd6\xf9\xdf\xf2\x43\x26\x87\x36\x33\x26\x02\x82\xfb\xfd\x09\x53\xa2\xea\xd7\x0b\xcd\x48\x81\x3d\xe9\x23\x4e\x17\xb8\x27\xcb\xde\x16\x79\x87\x98\x8f\x0c\x5d\xe9\xaf\x0d\xde\xf5\x89\xe3\x4f\xe9\x12\x31\x13\xa1\x66\x49\xf8\x69\x5b\x30\x76\x75\x7f\xb7\x0e\x58\x60\xc4\x80\x37\xfe\x2b\x85\xae\x7f\x5e\x04\xe4\xf4\xe8\x01\xfd\xfb\x7b\xbc\x28\x1a\x29\xb3\x1f\x92\x41\xde\x41\xbe\x9e\x36\xa7\x97\x3c\x4a\xee\x20\x73\x30\x6b\x6d\x64\xac\x24\x48\x70\x84\x13\xa4\x50\x29\xb3\x30\xae\xe2\x7b\x97\x30\x82\xec\x79\x4e\xd5\x63\x96\xcd\x02\x8d\xcb\xc5\xe7\xe7\xe1\x4f\x5e\x13\xa7\xdc\xd2\x34\xcf\xe8\x75\xed\x09\x9d\xe2\x6c\x51\x55\x2b\xc8\xcd\x43\xda\x3d\xf8\x85\x63\x46\x60\xe9\x3a\xda\x18\x6b\x07\x7f\x49\x43\xe5\x80\x51\xcc\x97\xcf\x72\x56\x6d\xca\x8c\x9e\x66\xad\xdc\x73\x06\x88\xd3\x13\xcf\x60\xbb\x6d\x4b\x4e\xf0\x50\xc5\x2a\x97\x61\xad\x14\x83\x02\xdf\x18\x6e\x53\xe9\x6c\xda\x37\xeb\x17\x49\x26\xb5\xbf\x5c\xe0\xcf\x3d\x1e\xc7\x93\xaf\xbe\xab\x52\x12\x64\xe6\x62\xbe\x3a\x27\x9e\x24\x3e\x7f\x7f\x90\xde\xeb\xe1\xcc\xde\xcf\x64\x93\x35\xea\xaf\x97\x99\x6f\x90\x1a\xf7\xd2\x89\xcf\x5d\xec\xfe\x40\xad\x20\x9a\x28\xbf\x30\xfc\xfe\x55\x7d\x58\xef\x86\xc5\x73\x6d\xa2\x71\xa4\x5f\xce\xe9\x59\x12\x2e\x9e\x90\x66\xf1\x69\xc2\x89\xe6\xae\x7c\x0e\x65\xc5\xc7\x5c\xba\xc6\x3d\xe7\xfe\x05\x67\x47\xef\xe4\x88\xd8\xa6\x3e\xae\xae\xca\xe4\xa0\x84\x70\x33\xe2\xb8\xa7\xb8\x60\x86\x91\x67\xc1\x47\x4a\x35\x91\x3b\xe9\xea\xd5\xa1\xd2\xd2\x7a\x60\x5f\x90\xa7\xc4\x9f\xf6\x3e\x9e\xc3\x22\x60\xc2\x62\x9a\x09\x79\xdb\x90\x3a\x17\xff\xe6\x4e\xbe\xdc\x66\xb5\x09\xb3\x11\x55\x6c\x36\xac\x88\xe7\xcd\xbc\xf0\xc2\x45\x6f\xbc\x64\xdf\x73\x36\x47\x2f\xd5\x57\x93\xb5\xb6\xb2\xc1\x98\x06\xa9\xea\x89\x13\x03\xea\x0a\x90\x3b\xee\x27\x47\xd4\x10\x31\x46\xae\x3a\x79\x16\x20\x09\x81\xe5\x0c\x26\x11\xea\xc1\x2b\xb6\x20\x87\x75\x1c\xa0\x61\x88\x3d\x4f\x39\xb6\xfb\x54\x5e\x13\xd9\xe1\x57\x58\xb1\x28\x04\x5a\xe6\xd1\x6d\x0a\xdf\xd1\x4c\x36\x9f\xf5\x85\x8e\x67\x96\x1a\x4b\x39\x89\xb0\xa1\xfa\xe7\xa4\xa6\xc4\xe4\xd9\x3e\x67\xa8\x4a\x6b\x71\x4b\x1e\x12\x86\xaf\x93\x27\x65\xae\xd1\xc5\x7e\x50\xf7\x49\xe0\x3b\x6f\xea\xd2\x44\x2c\xa1\xad\x11\xaf\x9c\xa0\x78\x41\x05\x50\x8a\xb5\x86\xd6\x13\xcd\x59\x47\x96\x81\x70\x44\xff\x43\x8a\xa7\x6f\x34\x1a\x3c\x82\x4e\x0b\xe3\xcc\x63\x9f\x31\x1d\xa2\x3f\x11\x1e\xf7\xd9\x15\x6d\x53\x6a\xd6\x0d\x8c\xac\x56\x44\x4b\x4f\x72\x5c\x02\xd5\x18\x25\x2c\xe8\xe6",1468))
printf("strip: 33acbc4fdc4158b6, Pass\n");
else
printf("strip: 33acbc4fdc4158b6, Failed\n");
}

static void aes_128_gcm_dec_prepare(core_desc *cd)
{
if(!cd->context_ptr)
printf("cd->context_ptr malloc failed!\n");
#if defined(CONFIG_COMPILE_FPGA) || defined(CONFIG_COMPILE_ASIC)
//memset(cd->context_ptr,0,64*1024);
#endif
writel(0xa7050f08&0xffffffff,cd->ivp_cae_base_addr+0x0000f000);
writel(0x8000c807&0xffffffff,cd->ivp_cae_base_addr+0x0000f400);
writel(0x00007500&0xffffffff,cd->ivp_cae_base_addr+0x00010100);
writel(0x0000f800&0xffffffff,cd->ivp_cae_base_addr+0x00010000);
writel(0x00000087&0xffffffff,cd->ivp_cae_base_addr+0x00011c00);
writel(0x00410000&0xffffffff,cd->ivp_cae_base_addr+0x00011000);
writel(0x00000225&0xffffffff,cd->ivp_cae_base_addr+0x00011008);
writel(0x80000000&0xffffffff,cd->ivp_cae_base_addr+0x0000f200);
writel(0x80000000&0xffffffff,cd->ivp_cae_base_addr+0x0000f600);
readl(cd->ivp_cae_base_addr+0x0000f200);
writel(0x40000000&0xffffffff,cd->ivp_cae_base_addr+0x0000f200);
readl(cd->ivp_cae_base_addr+0x0000f600);
writel(0x40000000&0xffffffff,cd->ivp_cae_base_addr+0x0000f600);
writel(((unsigned long)cd->context_ptr+0x00000000)&0xffffffffffffffff,cd->ivp_cae_base_addr+0x00000008);
writel((((unsigned long)cd->context_ptr+0x00000000)>>32)&(0xffffffffffffffff>>32),cd->ivp_cae_base_addr+0x00000008+0x4);
writel(((unsigned long)cd->context_ptr+0x00000000)&0xffffffffffffffff,cd->ivp_cae_base_addr+0x00000010);
writel((((unsigned long)cd->context_ptr+0x00000000)>>32)&(0xffffffffffffffff>>32),cd->ivp_cae_base_addr+0x00000010+0x4);
writel(0x00000000&0xffffffff,cd->ivp_cae_base_addr+0x00000020);
writel(0x80000000&0xffffffff,cd->ivp_cae_base_addr+0x0000002c);
writel(0x00000000&0xffffffff,cd->ivp_cae_base_addr+0x00000034);
writel(0x00000000&0xffffffff,cd->ivp_cae_base_addr+0x00000038);
writel(0x00000600&0xffffffff,cd->ivp_cae_base_addr+0x00000018);
writel(((unsigned long)cd->context_ptr+0x00000000)&0xffffffffffffffff,cd->ivp_cae_base_addr+0x00000000);
writel((((unsigned long)cd->context_ptr+0x00000000)>>32)&(0xffffffffffffffff>>32),cd->ivp_cae_base_addr+0x00000000+0x4);
writel(0x80000000&0xffffffff,cd->ivp_cae_base_addr+0x00000030);
writel(0x01000000&0xffffffff,cd->ivp_cae_base_addr+0x00000024);
writel(0x40060006&0xffffffff,cd->ivp_cae_base_addr+0x0000001c);
writel(0x0000003f&0xffffffff,cd->ivp_cae_base_addr+0x0000003c);
writel(0x00120012&0xffffffff,cd->ivp_cae_base_addr+0x00000020);
readl(cd->ivp_cae_base_addr+0x0000f010);
writel(0x0000000f&0xffffffff,cd->ivp_cae_base_addr+0x0000f010);
readl(cd->ivp_cae_base_addr+0x0000f200);
writel(0x40000001&0xffffffff,cd->ivp_cae_base_addr+0x0000f200);
writel(0x01000000&0xffffffff,cd->ivp_cae_base_addr+0x00000824);
writel(((unsigned long)cd->context_ptr+0x00000000)&0xffffffffffffffff,cd->ivp_cae_base_addr+0x00000808);
writel((((unsigned long)cd->context_ptr+0x00000000)>>32)&(0xffffffffffffffff>>32),cd->ivp_cae_base_addr+0x00000808+0x4);
writel(((unsigned long)cd->context_ptr+0x00000600)&0xffffffffffffffff,cd->ivp_cae_base_addr+0x00000800);
writel((((unsigned long)cd->context_ptr+0x00000600)>>32)&(0xffffffffffffffff>>32),cd->ivp_cae_base_addr+0x00000800+0x4);
writel(0x00000600&0xffffffff,cd->ivp_cae_base_addr+0x00000818);
writel(0x00060006&0xffffffff,cd->ivp_cae_base_addr+0x0000081c);
writel(0x00080018&0xffffffff,cd->ivp_cae_base_addr+0x00000820);
writel(0x80000000&0xffffffff,cd->ivp_cae_base_addr+0x0000082c);
writel(0x80000000&0xffffffff,cd->ivp_cae_base_addr+0x00000830);
writel(0x00000000&0xffffffff,cd->ivp_cae_base_addr+0x00000834);
writel(0x00000000&0xffffffff,cd->ivp_cae_base_addr+0x00000838);
writel(0x00000000&0xffffffff,cd->ivp_cae_base_addr+0x00000828);
writel(0x000000ff&0xffffffff,cd->ivp_cae_base_addr+0x0000083c);
readl(cd->ivp_cae_base_addr+0x0000f410);
writel(0x0000000f&0xffffffff,cd->ivp_cae_base_addr+0x0000f410);
readl(cd->ivp_cae_base_addr+0x0000f600);
writel(0x40000001&0xffffffff,cd->ivp_cae_base_addr+0x0000f600);
*((unsigned int *)((unsigned long)cd->context_ptr+0x00000c00))=0xd24b0f0f;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00000c00+4*1))=0x4a820462;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00000c00+4*2))=0x268b6032;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00000c00+4*3))=0x6725fbfd;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00000c00+4*4))=0xea7ee0ae;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00000c00+4*5))=0xab7f7f52;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00000c00+4*6))=0x13b75384;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00000c00+4*7))=0xfe5a8063;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00000c00+4*8))=0x3f753964;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00000c00+4*9))=0x810879d4;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00000c00+4*10))=0x00004321;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00000c00+4*11))=0xffe00000;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00000c00+4*12))=0xffffffff;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00000c00+4*13))=0xffffffff;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00000c00+4*14))=0xffffffff;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00000c00+4*15))=0x35651ead;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00000c00+4*16))=0x2537f20a;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00000c44))=0xd24b0f0f;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00000c44+4*1))=0x4a820462;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00000c44+4*2))=0x0e2f153b;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00000c44+4*3))=0x9c9c2ca3;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00000c44+4*4))=0xe04883b4;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00000c44+4*5))=0x84a1755a;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00000c44+4*6))=0x62e76ae2;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00000c44+4*7))=0x0266f22b;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00000c44+4*8))=0xfb56a314;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00000c44+4*9))=0x9a7579d7;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00000c44+4*10))=0x00008765;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00000c44+4*11))=0x00000000;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00000c44+4*12))=0xfffffe00;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00000c44+4*13))=0xffffffff;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00000c44+4*14))=0xffffffff;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00000c44+4*15))=0x96f03238;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00000c44+4*16))=0x0000630c;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00000c88))=0x0300000c;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00000c88+4*1))=0x02000004;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00000c88+4*2))=0x42980004;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00000c88+4*3))=0x4aa00008;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00000c88+4*4))=0x90996004;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00000c88+4*5))=0xa082000c;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00000c88+4*6))=0x25000010;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00000c88+4*7))=0x0f02000c;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00000c88+4*8))=0x40e60010;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00000c88+4*9))=0xd8070010;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00000c88+4*10))=0xe12e380a;

*((unsigned int *)((unsigned long)cd->context_ptr+0x00000cb4))=0x4fbcac33;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00000cb4+4*1))=0xb65841dc;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00000cb4+4*2))=0x7512ef0b;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00000cb4+4*3))=0x0c2ce588;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00000cb4+4*4))=0x21430000;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00000cb4+4*5))=0x35651ead;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00000cb4+4*6))=0x2537f20a;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00000cb4+4*7))=0x8c3b321b;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00000cb4+4*8))=0xa79885a5;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00000cb4+4*9))=0x4b2cf08e;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00000cb4+4*10))=0x7c631e9d;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00000cb4+4*11))=0x9b4032c1;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00000cb4+4*12))=0xde06f4ba;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00000cb4+4*13))=0xb6c80033;

*((unsigned int *)((unsigned long)cd->context_ptr+0x00000600))=0x04c00018;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00000600+4*1))=0x00000cec;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00000600+4*2))=0x77777777;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00000600+4*3))=0x77777777;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00000600+4*4))=0x77777777;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00000600+4*5))=0x77777777;
writel(0x00000018&0xffffffff,cd->ivp_cae_base_addr+0x0000082c);
writel(0x0000017a&0xffffffff,cd->ivp_cae_base_addr+0x00000028);
while(1){
if((readl(cd->ivp_cae_base_addr+0x0000003c)&0x00000002)==0x00000002)
break;
}
readl(cd->ivp_cae_base_addr+0x0000002c);
writel(0x00000002&0xffffffff,cd->ivp_cae_base_addr+0x0000003c);
*((unsigned int *)((unsigned long)cd->context_ptr+0x00000000))=0x0bc00038;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00000000+4*1))=0x00000cb4;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00000000+4*2))=0x00000c88;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00000000+4*3))=0x00220038;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00000000+4*4))=0x00441030;
*((unsigned int *)((unsigned long)cd->context_ptr+0x00000000+4*5))=0x00000c00+(unsigned long)cd->context_ptr;
}

static void aes_128_gcm_dec_start(core_desc *cd)
{
writel(0x00000018&0xffffffff,cd->ivp_cae_base_addr+0x0000002c);
writel(0x00000006&0xffffffff,cd->ivp_cae_base_addr+0x00000828);
}

static void aes_128_gcm_dec_finish(core_desc *cd)
{
while(1){
if((readl(cd->ivp_cae_base_addr+0x0000083c)&0x00000010)==0x00000010)
break;
}
readl(cd->ivp_cae_base_addr+0x00000830);
writel(0x00000010&0xffffffff,cd->ivp_cae_base_addr+0x0000083c);
if(!memcmp((unsigned char *)cd->context_ptr+0x00000cec,"\x33\xac\xbc\x4f\xdc\x41\x58\xb6\x0b\xef\x12\x75\xeb\x70\xb9\x0c\xcf\xfa\x75\x1e\x14\x19\xc3\x69",24))
printf("strip: 33acbc4fdc4158b6, Pass\n");
else
printf("strip: 33acbc4fdc4158b6, Failed\n");
}

void aes_128_gcm_dual_core(int enc)
{
	core_desc core_0 = { .context_ptr = (unsigned int *)0x14000000,
			     .ivp_cae_base_addr = ITCS_C_CAE0_BASE };
	core_desc core_1 = { .context_ptr = (unsigned int *)(0x14000000 + 0x100000),
			     .ivp_cae_base_addr = ITCS_C_CAE1_BASE };

	if (enc) {
		printf("aes-128-gcm generate input data...\n");
		aes_128_gcm_make_input_data(&core_0, enc);
		aes_128_gcm_make_input_data(&core_1, enc);
		printf("aes-128-gcm generate input data done\n");
		/* 
		 * key: "\x32\x60\x8b\x26\xfd\xfb\x25\x67\xae\xe0\x7e\xea\x52\x7f\x7f\xab"
		 * iv: "\xad\x1e\x65\x35\x0a\xf2\x37\x25\x00\x00\x43\x21"
		 * aad: "\x33\xac\xbc\x4f\xdc\x41\x58\xb6\x0b\xef\x12\x75\x88\xe5\x2c\x0c\x00\x00\x43\x21\xad\x1e\x65\x35\x0a\xf2\x37\x25"
		 * icv(tag/hashed): 0d8cac56444b4f725c02d518252ce8e6
		 */
		aes_128_gcm_prepare(&core_0);
		aes_128_gcm_prepare(&core_1);
		aes_128_gcm_start(&core_0);
		aes_128_gcm_start(&core_1);
		aes_128_gcm_finish(&core_0);
		aes_128_gcm_finish(&core_1);
	} else {
		aes_128_gcm_dec_prepare(&core_0);
		aes_128_gcm_dec_prepare(&core_1);
		aes_128_gcm_dec_start(&core_0);
		aes_128_gcm_dec_start(&core_1);
		aes_128_gcm_dec_finish(&core_0);
		aes_128_gcm_dec_finish(&core_1);
	}
	printf("ivp dual core aes-128-gcm %s Pass.\n", enc ? "enc" : "dec");
}

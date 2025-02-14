#ifndef __VIDEO_STAB_H__
#define __VIDEO_STAB_H__
#include <vidstbapi.h>
#include <common.h>
#include <venc-common.h>
/************************************VideoStab Encoder************************************************/
typedef struct{
	char caseName[64];

	char inputFile[256];
	char outputFile[256];
	uint32_t  outputSize ; 
	uint32_t  outputCrc32;
	uint32_t inputWidth;
	uint32_t inputHeight;
	uint32_t stride;
	uint32_t stabilizedWidth;
	uint32_t stabilizedHeight;
	VideoStbInputFormat format;

}CAMSTABTBCFG,CamStabTbConfig;
#define DEFAULT_STAB_OUTPUT_SIZE   10240

#define STAB_RESULT_BUF_SIZE  64
/***********************************video stabilization*********************************************************/
static void camstab_free_buffer(VencLinearMem *referbuffer);
int camstab_allocate_buffer(VencLinearMem *referbuffer,uint32_t frameSize);
static void camstab_close(VideoStbInst stabinst);
static int camstab_open(VideoStbInst *stabinst,CamStabTbConfig *excfg);
int camstab_read_pic(FILE *file,VencLinearMem *buffer,uint32_t frameSize ,uint32_t imgSize,uint32_t index);
int32_t load_camstab_enocode_para_from_file(char *filename,CamStabTbConfig *cfg);


int camstab_encode(CamStabTbConfig *cfg);

#endif

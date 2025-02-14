#include <common.h>
#include <jpegencapi.h>
#include <venc-common.h>
#ifndef __JPEG_ENCODE_H__
#define  __JPEG_ENCODE_H__
const char JPEG_ENCODE_INPUT_FILE_FOLDER[]="";
const char JPEG_ENCODE_OUTPUT_FILE_FOLDER[]="venc/jpeg/output/";
/************************************Jpeg Encoder************************************************/
typedef struct{
	char caseName[64];
	char inputFile[256];
	char inputThumbnail[256];
//	char fileName[256];
//	char dir[256];
	char inputComment[256];
	char outputFile[256];
	uint32_t  outputCrc32;
	JpegEncCfg excfg;
	JpegEncThumb exthumbcfg;
	uint32_t irqEnable;
	uint32_t dmmuEnable ;
}JPEGENCCFG,JpegEncConfig;
/*********************************jpeg***************************************/
static int jpeg_open(JpegEncInst * instAddr,JpegEncCfg *cfg,JpegEncConfig *excfg);
static int jpeg_set_thumbnail(JpegEncInst *instAddr,JpegEncThumb *pJpegThumb,JpegEncConfig *excfg);
static int jpeg_allocate_buffer(VencLinearMem *input,VencLinearMem *output,JpegEncCfg *enccfg,JpegEncThumb *thumbcfg);
static void jpeg_free_buffer(VencLinearMem *input,VencLinearMem *output,JpegEncCfg *enccfg,JpegEncThumb *thumbcfg);
static void jpeg_close(JpegEncInst *instAddr);
static int jpeg_read_pic(char *image,int width,int height,int sliceNum,int sliceRows,char *name ,unsigned int inputMode);
int jpeg_encode(JpegEncConfig *cfg);

int32_t load_jpeg_enocode_para_from_file(char *filename,JpegEncConfig *cfg);
/*******************************H.264 *************************/
#endif

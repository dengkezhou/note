#ifndef __H264_ENCODE_H__
#define  __H264_ENCODE_H__

#include <common.h>
#include <venc-common.h>
#include <h264encapi.h>


/*buffer addr*/
#define DDR_BASE_ADDR   0x100000000
#define H264_INPUT_ADDR (DDR_BASE_ADDR + 0x10000000)
#define H264_OUTPUT_ADDR (DDR_BASE_ADDR + 0x20000000)
#define H264_STAB_ADDR (DDR_BASE_ADDR + 0x30000000)



/************************************H264 Encoder************************************************/
#define NALU_TABLE_SIZE     ((1920/16) + 3)
#define __WRITEOUT__
//fix me
//#define NAL_TO_ANNEXB_FORMAT
typedef struct{
	char caseName[64];
	char inputFile[256];
	char outputFile[256];
	char inputUserDataFile[256];
	int enablecodingctrl;
	int enableratectrl;
	int enablepreproc;
	uint32_t outputSize;
	uint32_t outputCrc32;

	int ex_picture_size;   /*picture size may be not equal to H*W*Type*/

	//init config
	H264EncConfig  exencconfig;
	//CodingControl
	H264EncCodingCtrl excodectrl;
	//RateControl
	H264EncRateCtrl   exratectrl;
	//PreProcessingCfg
	H264EncPreProcessingCfg expreproc;
}H264ENCTBCFG,H264EncTbCfg;


int h264_encode(H264EncTbCfg *cfg);
void h264_free_buffer(VencLinearMem *input,VencLinearMem *stabinput,VencLinearMem *output);
int h264_allocate_buffer(VencLinearMem *input,VencLinearMem *stabinput,VencLinearMem *output,H264EncTbCfg *excfg);
int h264_set_buffer_addr(VencLinearMem *input,VencLinearMem *stabinput,VencLinearMem *output,H264EncTbCfg *excfg);
void h264_close(H264EncInst h264inst);
int h264_open(H264EncTbCfg *excfg,H264EncInst *h264inst);
int h264_read_userdata(H264EncInst h264inst, char *pUsrData);
int h264_read_pic(char *pUsrData,VencLinearMem *input,int frameCnt,int imgSize,
						unsigned int width,unsigned int height,H264EncPictureType format);
int h264_process(VencLinearMem *input,VencLinearMem *stabinput,VencLinearMem *output,
										H264EncTbCfg *excfg,H264EncInst h264inst);
int32_t load_h264_enocode_para_from_file(char *filename,H264EncTbCfg *cfg);

#if 0
#define H1_H264_DBG(str...)  printf(str)
#define H1_H264_ERR(str...)  printf(str)
#define H1_H264_INFO(str...)  
#else 
#define H1_H264_DBG(str...)  printf(str)
#define H1_H264_ERR(str...)  printf(str)
#define H1_H264_INFO(str...)  printf(str) 
#endif
#endif

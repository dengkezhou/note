
#include <para.h>
#include <crc32.h>
#include <getopt.h>

#include "h264-encode.h"
#include "venc-common.h"
#include "venc_para.h"

/*****************************************************************************************/
/*
func:close the h264 instance which initialized in the h264_open funcion
params:the h264 instance to be closed
return:
*/
void h264_close(H264EncInst h264inst)
{
	H264EncRet ret;
	VENC_LOG(INFO,("%s h264_close()+++\n",MODULE_H264));
	if(h264inst ==NULL){
		VENC_LOG(ERR,("%s params is null!\n",MODULE_H264));
		return ;
	}
	//==========================================================================	
	ret = H264EncRelease(h264inst);

	if(ret != H264ENC_OK){
		VENC_LOG(ERR,("%s H264EncRelease() failed,return %d\n",MODULE_H264,ret));
	}
	VENC_LOG(INFO,("%s h264_close()---\n",MODULE_H264));
}

/*
func:init a h264 instance and do the rate control/coding control/preproc setting if necessary
params: excfg->point to the external setting configuration structure
return:0,open failed;
		1,open and setting success
*/
int h264_open(H264EncTbCfg *excfg,H264EncInst *h264inst)
{
	H264EncInst encoder;
	H264EncRet ret;
	H264EncConfig encCfg;
	H264EncCodingCtrl codingCfg;
	H264EncRateCtrl rcCfg;
	H264EncPreProcessingCfg preProcCfg;

	H264EncConfig *exEncCfg;
	H264EncCodingCtrl *exCodingCfg;
	H264EncRateCtrl *exRcCfg;
	H264EncPreProcessingCfg *exPreProcCfg;

	VENC_LOG(INFO,("%s h264_open()+++\n",MODULE_H264));
	if(excfg ==NULL || h264inst ==NULL){
		VENC_LOG(ERR,("%s params is null!\n",MODULE_H264));
		return 0;
	}

	memset2(&encoder,sizeof(H264EncInst),0);		
	memset2(&encCfg,sizeof(H264EncConfig),0);
	memset2(&codingCfg,sizeof(H264EncCodingCtrl),0);
	memset2(&rcCfg,sizeof(H264EncRateCtrl),0);
	memset2(&preProcCfg,sizeof(H264EncPreProcessingCfg),0);

	exEncCfg = &excfg->exencconfig;
	exCodingCfg = &excfg->excodectrl;
	exRcCfg = &excfg->exratectrl;
	exPreProcCfg = &excfg->expreproc;

	VENC_LOG(INFO,("%s H264 ENCODE CONFIGURATION LIST::\n\n",MODULE_H264));
	VENC_LOG(INFO,("%s streamType: %d\n",MODULE_H264,exEncCfg->streamType));
	VENC_LOG(INFO,("%s level: %d\n",MODULE_H264,exEncCfg->level));
	VENC_LOG(INFO,("%s width: %d\n",MODULE_H264,exEncCfg->width));
	VENC_LOG(INFO,("%s height: %d\n",MODULE_H264,exEncCfg->height));
	VENC_LOG(INFO,("%s frameRateNum: %d\n",MODULE_H264,exEncCfg->frameRateNum));
	VENC_LOG(INFO,("%s frameRateDenom: %d\n",MODULE_H264,exEncCfg->frameRateDenom));
	//VENC_LOG(INFO,("%s complexityLevel: %d\n",MODULE_H264,exEncCfg->complexityLevel));

	//simple checking
	//1,stream type checking
	if ((exEncCfg->streamType != H264ENC_BYTE_STREAM) && (exEncCfg->streamType != H264ENC_NAL_UNIT_STREAM)){
		VENC_LOG(ERR,("%s invalid streamType\n",MODULE_H264));
		return 0;
	}
	//2,stream size checking
	if(exEncCfg->width < 96 || exEncCfg->width>1920 ||(exEncCfg->width & 0x3) != 0){
		VENC_LOG(ERR,("%s invalid encode width %d\n",MODULE_H264,exEncCfg->width));
		return 0;
	}
	if(exEncCfg->height <96 || exEncCfg->height>1920 || (exEncCfg->height & 0x1) != 0){
		VENC_LOG(ERR,("%s invalid encode height %d\n",MODULE_H264,exEncCfg->height));
		return 0;
	}
	if(((exEncCfg->height + 15) / 16) * ((exEncCfg->width + 15) / 16) > 8160){
		VENC_LOG(ERR,("%s invalid width(%d) and height(%d),encoder can not process the mirco block,too big\n",
								MODULE_H264,exEncCfg->width,exEncCfg->height));
		return 0;
	}
	
	//3,framerate checking
	if(exEncCfg->frameRateNum == VENC_RANDOM_VALUE || 
		exEncCfg->frameRateDenom == VENC_RANDOM_VALUE){
		int max = 0;
		int min = 0;
		max = ((1 << 20) - 1);
		min = 1;
		exEncCfg->frameRateNum = (u32)venc_get_random_size(max,min);
		max =  exEncCfg->frameRateNum;
		min = 1;
		exEncCfg->frameRateDenom = (u32)venc_get_random_size(max,min);
	}
	if(exEncCfg->frameRateNum < 1 || exEncCfg->frameRateNum > ((1 << 20) - 1)){
		VENC_LOG(ERR,("%s invalid frameRateNum(%d)\n",MODULE_H264,exEncCfg->frameRateNum));
		return 0;
	}
	if(exEncCfg->frameRateDenom < 1){
		VENC_LOG(ERR,("%s invalid frameRateDenom(%d)\n",MODULE_H264,exEncCfg->frameRateDenom));
		return 0;
	}

	//4,level checking
	if((exEncCfg->level > H264ENC_LEVEL_4_1) &&
					(exEncCfg->level != H264ENC_LEVEL_1_b)){
		VENC_LOG(ERR,("%s invalid level(%d)\n",MODULE_H264,exEncCfg->level));
		return 0;
	}
	
	//5,complexity checking
	//fie me
#if 0
	if(exEncCfg->complexityLevel !=H264ENC_COMPLEXITY_1){
		VENC_LOG(ERR,("%s invalid complexityLevel(%d)\n",MODULE_H264,exEncCfg->complexityLevel));
		return 0;
	}
#endif
	//if everything is ok,now we can copy it to the internal configuration
	memcpy((void *)&encCfg,(void *)exEncCfg,sizeof(H264EncConfig));

	//==========================================================================	
	ret = H264EncInit(&encCfg, h264inst);
	if(ret  != H264ENC_OK){
		VENC_LOG(ERR,("%s H264EncInit() failed! return %d\n",MODULE_H264,ret));
		return 0;
	}
	encoder = *h264inst;

	//==========================================================================	
	/* Encoder setup: rate control */
	ret = H264EncGetRateCtrl(encoder, &rcCfg);
	if(ret != H264ENC_OK){
		VENC_LOG(ERR,("%s H264EncGetRateCtrl() failed! return %d\n",MODULE_H264,ret));
		h264_close(encoder);
		return 0;
	}

	if(excfg->enableratectrl){
		if(exRcCfg->qpHdr == VENC_RANDOM_VALUE ){
			exRcCfg->qpMin = 10;
			exRcCfg->qpMax = 51;
			exRcCfg->qpHdr = (u32)venc_get_random_size(51,10);
		}
		if(exRcCfg->bitPerSecond == VENC_RANDOM_VALUE){
			int max = 40000000;
			int min = 10000;
			exRcCfg->bitPerSecond = (u32)venc_get_random_size(max,min);
		}
		//TODO miss random hrdsize 
		if(exRcCfg->gopLen == VENC_RANDOM_VALUE){
			exRcCfg->gopLen = (u32)venc_get_random_size(150,1);
		}
		if(exRcCfg->intraQpDelta == VENC_RANDOM_VALUE){
			exRcCfg->intraQpDelta = venc_get_random_size(12,-12);
		}
		if(exRcCfg->fixedIntraQp == VENC_RANDOM_VALUE){
			exRcCfg->fixedIntraQp = (u32)venc_get_random_size(51,0);
		}
		if(exRcCfg->mbQpAdjustment == VENC_RANDOM_VALUE){
			exRcCfg->mbQpAdjustment = venc_get_random_size(7,-8);
		}
		VENC_LOG(INFO,("%s H264 ENCODE RATE CTRL CONFIGURATION LIST:\n\n",MODULE_H264));
		VENC_LOG(INFO,("external configuration vs default configuration\n"));
		VENC_LOG(INFO,("%s pictureRc %d:%d\n",MODULE_H264,exRcCfg->pictureRc,rcCfg.pictureRc));
		VENC_LOG(INFO,("%s mbRc %d:%d\n",MODULE_H264,exRcCfg->mbRc,rcCfg.mbRc));
		VENC_LOG(INFO,("%s pictureSkip %d:%d\n",MODULE_H264,exRcCfg->pictureSkip,rcCfg.pictureSkip));
		VENC_LOG(INFO,("%s qpHdr %d:%d\n",MODULE_H264,exRcCfg->qpHdr,rcCfg.qpHdr));
		VENC_LOG(INFO,("%s qpMin %d:%d\n",MODULE_H264,exRcCfg->qpMin,rcCfg.qpMin));
		VENC_LOG(INFO,("%s qpMax %d:%d\n",MODULE_H264,exRcCfg->qpMax,rcCfg.qpMax));
		VENC_LOG(INFO,("%s bitPerSecond %d:%d\n",MODULE_H264,exRcCfg->bitPerSecond,rcCfg.bitPerSecond));
		VENC_LOG(INFO,("%s hrd %d:%d\n",MODULE_H264,exRcCfg->hrd,rcCfg.hrd));
		VENC_LOG(INFO,("%s hrdCpbSize %d:%d\n",MODULE_H264,exRcCfg->hrdCpbSize,rcCfg.hrdCpbSize));
		VENC_LOG(INFO,("%s gopLen %d:%d\n",MODULE_H264,exRcCfg->gopLen,rcCfg.gopLen));
		VENC_LOG(INFO,("%s intraQpDelta %d:%d\n",MODULE_H264,exRcCfg->intraQpDelta,rcCfg.intraQpDelta));
		VENC_LOG(INFO,("%s fixedIntraQp %d:%d\n",MODULE_H264,exRcCfg->fixedIntraQp,rcCfg.fixedIntraQp));
		VENC_LOG(INFO,("%s mbQpAdjustment %d:%d\n",MODULE_H264,exRcCfg->mbQpAdjustment,rcCfg.mbQpAdjustment));	
		venc_copy_with_check((unsigned int *)&rcCfg,(unsigned int *)exRcCfg,	\
				sizeof(H264EncRateCtrl)/sizeof(unsigned int));		
		
		ret = H264EncSetRateCtrl(encoder, &rcCfg);
		if(ret != H264ENC_OK){
			VENC_LOG(INFO,("%s H264EncSetRateCtrl() failed!, return %d\n",MODULE_H264,ret));
			h264_close(encoder);
			return 0;
		}
	}	
	
	/* Encoder setup: coding control */ 
	ret = H264EncGetCodingCtrl(encoder, &codingCfg);
	if(ret != H264ENC_OK){
		VENC_LOG(ERR,("%s H264EncGetCodingCtrl() failed! return %d\n",MODULE_H264,ret));
		h264_close(encoder);
		return 0;
	}

	if(excfg->enablecodingctrl){		
		if(exCodingCfg->sliceSize == VENC_RANDOM_VALUE){
			int max = 0;
			int min = 0;
			max = exEncCfg->height/16>119?119:exEncCfg->height/16;
			exCodingCfg->sliceSize = (u32)venc_get_random_size(max,min);
		}
		VENC_LOG(INFO,("%s H264 ENCODE CODING CTRL CONFIGURATION LIST:\n\n",MODULE_H264));
		VENC_LOG(INFO,("external configuration vs default configuration\n"));
		VENC_LOG(INFO,("%s sliceSize %d:%d\n",MODULE_H264,exCodingCfg->sliceSize,codingCfg.sliceSize));
		VENC_LOG(INFO,("%s seiMessages %d:%d\n",MODULE_H264,exCodingCfg->seiMessages,codingCfg.seiMessages));
		VENC_LOG(INFO,("%s videoFullRange %d:%d\n",MODULE_H264,exCodingCfg->videoFullRange,codingCfg.videoFullRange));
		VENC_LOG(INFO,("%s constrainedIntraPrediction %d:%d\n",MODULE_H264,
					exCodingCfg->constrainedIntraPrediction,codingCfg.constrainedIntraPrediction));
		VENC_LOG(INFO,("%s disableDeblockingFilter %d:%d\n",MODULE_H264,
					exCodingCfg->disableDeblockingFilter,codingCfg.disableDeblockingFilter));
		VENC_LOG(INFO,("%s sampleAspectRatioWidth %d:%d\n",MODULE_H264,
					exCodingCfg->sampleAspectRatioWidth,codingCfg.sampleAspectRatioWidth));
		VENC_LOG(INFO,("%s sampleAspectRatioHeight %d:%d\n",MODULE_H264,
					exCodingCfg->sampleAspectRatioHeight,codingCfg.sampleAspectRatioHeight));
		VENC_LOG(INFO,("%s enableCabac %d:%d\n",MODULE_H264,exCodingCfg->enableCabac,codingCfg.enableCabac));
		VENC_LOG(INFO,("%s cabacInitIdc %d:%d\n",MODULE_H264,exCodingCfg->cabacInitIdc,codingCfg.cabacInitIdc));
		VENC_LOG(INFO,("%s transform8x8Mode %d:%d\n",MODULE_H264,
					exCodingCfg->transform8x8Mode,codingCfg.transform8x8Mode));
		VENC_LOG(INFO,("%s quarterPixelMv %d:%d\n",MODULE_H264,exCodingCfg->quarterPixelMv,codingCfg.quarterPixelMv));

		venc_copy_with_check((unsigned int *)&codingCfg,(unsigned int *)exCodingCfg,	\
						sizeof(H264EncCodingCtrl)/sizeof(unsigned int));
		
		ret = H264EncSetCodingCtrl(encoder, &codingCfg);
		if(ret  != H264ENC_OK){
			VENC_LOG(ERR,("%s H264EncSetCodingCtrl() failed!,return %d\n",MODULE_H264,ret));
			h264_close(encoder);
			return 0;
		}
	}

	/*encode: preprocess config*/
	ret = H264EncGetPreProcessing(encoder, &preProcCfg);
	if(ret != H264ENC_OK){
		VENC_LOG(ERR,("%s H264EncGetPreProcessing() failed! return %d\n",MODULE_H264,ret));
		h264_close(encoder);
		return 0;
	}
	if(excfg->enablepreproc){
		if(exPreProcCfg->xOffset == VENC_RANDOM_VALUE ||
				exPreProcCfg->yOffset == VENC_RANDOM_VALUE){
			int max = 0;
			int min = 0;
			if(exPreProcCfg->rotation != H264ENC_ROTATE_0)
				max = exPreProcCfg->origWidth - exEncCfg->height;
			else
				max = exPreProcCfg->origWidth - exEncCfg->width;
			exPreProcCfg->xOffset = venc_get_random_size(max,min);
			if(exPreProcCfg->rotation != H264ENC_ROTATE_0)
				max = exPreProcCfg->origHeight - exEncCfg->width;
			else
				max = exPreProcCfg->origHeight - exEncCfg->height;
			exPreProcCfg->yOffset = venc_get_random_size(max,min);
		}
		VENC_LOG(INFO,("%s H264 ENCODE PREPROC CTRL CONFIGURATION LIST:\n\n",MODULE_H264));
		VENC_LOG(INFO,("external configuration vs default configuration\n"));
		VENC_LOG(INFO,("%s origWidth %d:%d\n",MODULE_H264,exPreProcCfg->origWidth,preProcCfg.origWidth));
		VENC_LOG(INFO,("%s origHeight %d:%d\n",MODULE_H264,exPreProcCfg->origHeight,preProcCfg.origHeight));
		VENC_LOG(INFO,("%s xOffset %d:%d\n",MODULE_H264,exPreProcCfg->xOffset,preProcCfg.xOffset));
		VENC_LOG(INFO,("%s yOffset %d:%d\n",MODULE_H264,exPreProcCfg->yOffset,preProcCfg.yOffset));
		VENC_LOG(INFO,("%s inputType %d:%d\n",MODULE_H264,exPreProcCfg->inputType,preProcCfg.inputType));
		VENC_LOG(INFO,("%s rotation %d:%d\n",MODULE_H264,exPreProcCfg->rotation,preProcCfg.rotation));
		VENC_LOG(INFO,("%s videoStabilization %d:%d\n",MODULE_H264,
					exPreProcCfg->videoStabilization,preProcCfg.videoStabilization));
		VENC_LOG(INFO,("%s colorconversion.type %d:%d\n",MODULE_H264,
					exPreProcCfg->colorConversion.type,preProcCfg.colorConversion.type));
		VENC_LOG(INFO,("%s colorconversion.coeffA %d:%d\n",MODULE_H264,
					exPreProcCfg->colorConversion.coeffA,preProcCfg.colorConversion.coeffA));
		VENC_LOG(INFO,("%s colorconversion.coeffB %d:%d\n",MODULE_H264,
					exPreProcCfg->colorConversion.coeffB,preProcCfg.colorConversion.coeffB));
		VENC_LOG(INFO,("%s colorconversion.coeffC %d:%d\n",MODULE_H264,
					exPreProcCfg->colorConversion.coeffC,preProcCfg.colorConversion.coeffC));
		VENC_LOG(INFO,("%s colorconversion.coeffE %d:%d\n",MODULE_H264,
					exPreProcCfg->colorConversion.coeffE,preProcCfg.colorConversion.coeffE));
		VENC_LOG(INFO,("%s colorconversion.coeffF %d:%d\n",MODULE_H264,
					exPreProcCfg->colorConversion.coeffF,preProcCfg.colorConversion.coeffF));
		if(exPreProcCfg->origWidth != 0xFFFFFFFF){
			preProcCfg.origWidth = exPreProcCfg->origWidth;
		}
		if(exPreProcCfg->origHeight != 0xFFFFFFFF){
			preProcCfg.origHeight = exPreProcCfg->origHeight;
		}
		if(exPreProcCfg->xOffset != 0xFFFFFFFF){
			preProcCfg.xOffset = exPreProcCfg->xOffset;
		}
		if(exPreProcCfg->yOffset != 0xFFFFFFFF){
			preProcCfg.yOffset = exPreProcCfg->yOffset;
		}
		if(exPreProcCfg->inputType >H264ENC_BGR101010 ){
			VENC_LOG(ERR,("%s invalid preproc colorspace!\n",MODULE_H264));
			h264_close(encoder);
			return 0;
		}
		preProcCfg.inputType = exPreProcCfg->inputType;
		if(exPreProcCfg->rotation != H264ENC_ROTATE_0 &&
						exPreProcCfg->rotation != H264ENC_ROTATE_90R &&
						exPreProcCfg->rotation != H264ENC_ROTATE_90L){
			VENC_LOG(ERR,("%s invalid preproc rotation type!\n",MODULE_H264));
			h264_close(encoder);
			return 0;
		}
		preProcCfg.rotation = exPreProcCfg->rotation;
		if(exPreProcCfg->videoStabilization != 0 && exPreProcCfg->videoStabilization != 0xFFFFFFFF){
			exPreProcCfg->videoStabilization =1;
			preProcCfg.videoStabilization = 1;
		}else if(exPreProcCfg->videoStabilization == 0){
			preProcCfg.videoStabilization =0;
		}
		if(exPreProcCfg->inputType>=H264ENC_RGB565 &&exPreProcCfg->colorConversion.type != H264ENC_RGBTOYUV_BT601 &&
						exPreProcCfg->colorConversion.type != H264ENC_RGBTOYUV_BT709 &&
						exPreProcCfg->colorConversion.type != H264ENC_RGBTOYUV_USER_DEFINED){
			VENC_LOG(ERR,("%s invalid colorConversion context",MODULE_H264));
			h264_close(encoder);
			return 0;
		}
		memcpy((void *)&preProcCfg.colorConversion,(void *)&exPreProcCfg->colorConversion,	\
						sizeof(H264EncColorConversion));

		
		ret = H264EncSetPreProcessing(encoder, &preProcCfg);
		if(ret != H264ENC_OK){
			VENC_LOG(ERR,("%s H264EncSetPreProcessing() failed! return %d",MODULE_H264,ret));
			h264_close(encoder);
			return 0;
		}
	}
	VENC_LOG(INFO,("%s h264_open()---\n",MODULE_H264));
	return 1;
}

/*
func: free the input  stabilization input and output buffer 
params:
return:
*/
void h264_free_buffer(VencLinearMem *input,VencLinearMem *stabinput,VencLinearMem *output)
{
	VENC_LOG(INFO,("%s h264_free_buffer()+++\n",MODULE_H264));
	if(input !=NULL && input->vBuffer!=NULL){
		free( input->vBuffer);
		memset2((void *)input,sizeof(VencLinearMem),0);
	}
	if(stabinput !=NULL && stabinput->vBuffer !=NULL){
		free( stabinput->vBuffer);
		memset2((void *)stabinput,sizeof(VencLinearMem),0);
	}
	if(output !=NULL &&output->vBuffer != NULL){
		free( output->vBuffer);
		memset2((void *)output,sizeof(VencLinearMem),0);
	}

	VENC_LOG(INFO,("%s h264_free_buffer---\n",MODULE_H264));
}


int h264_set_buffer_addr(VencLinearMem *input,VencLinearMem *stabinput,VencLinearMem *output,H264EncTbCfg *excfg)
{
	if(input ==NULL ||  stabinput ==NULL || output ==NULL || excfg ==NULL){
		VENC_LOG(ERR,("%s params is null!\n",MODULE_H264));
		return 0;
	}

	unsigned int pictureSize= 0;

	if (excfg->ex_picture_size != 0)
	{
		pictureSize = excfg->ex_picture_size;
	}
	else
	{
		if(excfg->expreproc.inputType <= H264ENC_YUV420_SEMIPLANAR){
			pictureSize = ((excfg->expreproc.origWidth + 15) & (~15)) * excfg->expreproc.origHeight * 3 / 2;
		}else if(excfg->expreproc.inputType <= H264ENC_BGR444){
			pictureSize = ((excfg->expreproc.origWidth + 15) & (~15)) * excfg->expreproc.origHeight * 2;
		}else {
			pictureSize = ((excfg->expreproc.origWidth + 15) & (~15)) * excfg->expreproc.origHeight * 4;
		}
	}

	input->vBuffer = (uint32_t*)H264_INPUT_ADDR;
	input->bBuffer = (uint32_t )(unsigned long)(input->vBuffer);
	input->size = pictureSize;
	input->addr_y = input->bBuffer;
	if(excfg->expreproc.inputType == H264ENC_YUV420_PLANAR){
		input->addr_u = input->addr_y + pictureSize * 2 / 3;
		input->addr_v = input->addr_u + pictureSize / 6;
	}else if(excfg->expreproc.inputType == H264ENC_YUV420_SEMIPLANAR){
		input->addr_u = input->addr_y + pictureSize * 2 / 3;
	}else {
		input->addr_u = 0;  /*TODO: add for all picture type*/
	}

	output->vBuffer = (uint32_t*)H264_OUTPUT_ADDR;
	output->bBuffer = (uint32_t )(unsigned long)(output->vBuffer);
	output->size = pictureSize;

	stabinput->vBuffer = (uint32_t*)H264_STAB_ADDR;
	stabinput->bBuffer = (uint32_t )(unsigned long)(stabinput->vBuffer);
	stabinput->size = pictureSize;	

	return 1;
}

/*
func:allocate input and output and stabilization buffer acording to our configuration 
params:
return:
*/

int h264_allocate_buffer(VencLinearMem *input,VencLinearMem *stabinput,VencLinearMem *output,H264EncTbCfg *excfg)
{
	unsigned int pictureSize= 0;
	unsigned int outbufSize = 0;
	VENC_LOG(INFO,("%s h264_allocate_buffer()+++\n",MODULE_H264));
	if(input ==NULL ||  stabinput ==NULL || output ==NULL || excfg ==NULL){
		VENC_LOG(ERR,("%s params is null!\n",MODULE_H264));
		return 0;
	}
	if(excfg->enablepreproc){
		if(excfg->expreproc.inputType<=H264ENC_YUV420_SEMIPLANAR){
			pictureSize = ((excfg->expreproc.origWidth + 15) & (~15)) * excfg->expreproc.origHeight * 3 / 2;
		}else if(excfg->expreproc.inputType<=H264ENC_BGR444){
			pictureSize = ((excfg->expreproc.origWidth + 15) & (~15)) * excfg->expreproc.origHeight * 2;
		}else {
			pictureSize = ((excfg->expreproc.origWidth + 15) & (~15)) * excfg->expreproc.origHeight * 4;
		}
	}else{
		//TODO: this is a default value of pp precess	
		//preProcess.lumWidth = pEncCfg->width
		//preProcess.lumWidthSrc =H264GetAllowedWidth(pEncCfg->width, H264ENC_YUV420_PLANAR)
		//preProcess.lumHeight = pEncCfg->height
		//preProcess.lumHeightSrc = pEncCfg->height;
		//preProcess.horOffsetSrc = 0;
		//preProcess.verOffsetSrc = 0;
		//preProcess.rotation = ROTATE_0
		//preProcess.inputFormat = H264ENC_YUV420_PLANAR
		//preProcess.videoStab = 0;
		//preProcess.colorConversionType = 0;
		
		/*YUV420--- w*h*3/2 */
		pictureSize = ((excfg->exencconfig.width + 15) & (~15)) * excfg->exencconfig.height * 3 / 2;
	}

	input->vBuffer = (void *)malloc( pictureSize);
	input->bBuffer = (uint32_t )(unsigned long)(input->vBuffer);
	input->size = pictureSize;
	if(input->vBuffer ==NULL){
		VENC_LOG(ERR,("%s mm_malloc input buffer failed!\n",MODULE_H264));
		return 0;
	}
    printf("input buff %p ,insize = %d \n", input->vBuffer,input->size);

	stabinput->vBuffer = (void *)malloc( pictureSize);
	stabinput->bBuffer =(uint32_t )(unsigned long)(stabinput->vBuffer);
	stabinput->size = pictureSize;
	if(stabinput->vBuffer ==NULL){
		VENC_LOG(ERR,("%s mm_malloc input stabilization buffer failed!\n",MODULE_H264));
		return 0;
	}
	printf("stabinput buff %p ,insize = %d \n", stabinput->vBuffer,stabinput->size);

	outbufSize = 1024 * 1024 * 3 / 2;
	output->vBuffer = (void *)malloc( outbufSize);
	output->bBuffer = (uint32_t )(unsigned long)(output->vBuffer);
	output->size = outbufSize;
	if(output->vBuffer == NULL){
		VENC_LOG(ERR,("%s mm_malloc output buffer failed!\n",MODULE_H264));
		return 0;
	}
	printf("outbuff %p ,outsize = %d \n", output->vBuffer,output->size);

	VENC_LOG(INFO,("%s h264_allocate_buffer()---\n",MODULE_H264));

	return 1;
}
/*
func:read user data from userfile ,the data is needed to form sei header
params:
return:
*/
int h264_read_userdata(H264EncInst h264inst, char *pUsrData)
{
	int byteCnt =0;
	char *data =NULL; 
	H264EncRet ret;
	VENC_LOG(INFO,("%s h264_read_userdata()+++\n",MODULE_H264));
	if(pUsrData ==NULL){
		VENC_LOG(ERR,("%s params is null!\n",MODULE_H264));
		return 0;
	}

	data = pUsrData;
	//byteCnt = INPUT_DATA_SIZE;

	if (byteCnt < 16)
	{
		byteCnt = 16;
	}
	else if (byteCnt > 2048)
	{
		byteCnt = 2048;
	}

	VENC_LOG(INFO,("%s User data: %d bytes [%d %d %d %d ...]\n",
							MODULE_H264,byteCnt,data[0], data[1], data[2], data[3]));
	/* Pass the data buffer to encoder 
	 * The encoder reads the buffer during following H264EncStrmEncode() calls.
	 * User data writing must be disabled (with SetSeiUserData(enc, 0, 0)) */

	//==========================================================================	
	if((ret =H264EncSetSeiUserData(h264inst, (const unsigned char *)data, byteCnt))!= H264ENC_OK){
		VENC_LOG(ERR,("%s H264EncSetSeiUserData() failed!,return %d\n",MODULE_H264,ret));
		return 0;
	}
	//==========================================================================
	
	VENC_LOG(INFO,("%s h264_read_userdata()---\n",MODULE_H264));

	return 1;
}

/*
func:
params:
return:
*/
int h264_read_pic(char *pUsrData,VencLinearMem *input,int frameCnt,int imgSize,
						unsigned int width,unsigned int height,H264EncPictureType format)
{
	size_t readsize, leftsize, total_size;
	total_size = input->size;

	VENC_LOG(INFO,("%s h264_read_pic()+++\n",MODULE_H264));
	if(pUsrData ==NULL || input ==NULL){
		VENC_LOG(ERR,("%s params is null!\n",MODULE_H264));
		return 0;
	}

	if(imgSize * frameCnt > total_size){
		VENC_LOG(ERR,("%s can not seek input file to the %d position!\n",MODULE_H264,imgSize * frameCnt));
		return 0;
	}

	leftsize = total_size - imgSize * frameCnt;
	readsize = (leftsize > imgSize) ? imgSize : leftsize;

	if((width & 0x0f) == 0 ){
		memcpy(input->vBuffer, pUsrData, readsize);
		VENC_LOG(INFO,("read from file!--> %d\n", readsize));
	}else{
		int i =0;
		char *buf = (char *)(input->vBuffer);
		int scan = (width + 15) & (~0x0f);

		if(format == H264ENC_YUV420_PLANAR){
			/* Y */
			for(i = 0; i < height; i++){
				memcpy(buf, pUsrData, width);
				pUsrData += width;
				buf += scan;
			}
			/* Cb */
			for(i = 0; i < (height / 2); i++){
				memcpy(buf, pUsrData, width / 2);
				pUsrData += width / 2; 
				buf += scan / 2;
			}
			/* Cr */
			for(i = 0; i < (height / 2); i++){
				memcpy(buf, pUsrData, width / 2);
				pUsrData += width / 2; 
				buf += scan / 2;
			}
		}else if(format == H264ENC_YUV420_SEMIPLANAR){
			/* Y */ 
			for(i = 0; i < height; i++){
				memcpy(buf, pUsrData, width);
				pUsrData += width; 
				buf += scan;
			}
			/* CbCr */
			for(i = 0; i < (height / 2); i++){
				memcpy(buf, pUsrData, width);
				pUsrData += width; 
				buf += scan;
			}
		}else if((int )format <=9){
			for(i = 0; i < height; i++){
				memcpy(buf, pUsrData, width * 2);
				pUsrData += width * 2; 
				buf += scan * 2;
			}
		
		}else{
			for(i = 0;i<height;i++){
				memcpy(buf, pUsrData, width*4);
				pUsrData += width *4; 
				buf += scan * 4; 
			}
		}
	}

	//==========================================================================	
	//==========================================================================

	VENC_LOG(INFO,("%s h264_read_pic()---\n",MODULE_H264));
	return 1;
}

void h264enc_slice_ready_callnack_func(H264EncSliceReady *pdata){
	printf("h264 slice ready callback\n");
}

/*
func:
params:
return:
*/
int h264_process(VencLinearMem *input,VencLinearMem *stabinput,VencLinearMem *output,
						H264EncTbCfg *excfg,H264EncInst h264inst)
{
	int retValue = 1;
	H264EncIn encIn = {0};
	H264EncOut encOut = {0};
	H264EncRateCtrl rc  = {0};
	H264EncPreProcessingCfg pp = {0};
	H264EncRet ret;
	int  src_img_size =0;
	int totalFrameCnt =0;
	int frameCnt=0;
	int outFrameCnt = 0;
	unsigned int streamSize = 0;
	//unsigned int offset0 = 0;
	//unsigned int offset1 = 0;
	//unsigned int *pnalSizeBuf=NULL;
	//unsigned int outBufferOffset = 0;
	unsigned int wSrc =0;
	unsigned int hSrc = 0;
	H264EncPictureType formatSrc ;  
	int iPicPerNframes = 0;
	H264EncSliceReady encSliceReadyCallbackPdata ;	
	char *pUserData = NULL;
	char *pInputData = NULL;

	if(input==NULL || stabinput ==NULL || output ==NULL || excfg ==NULL || h264inst==NULL ||
					input->vBuffer==NULL || stabinput->vBuffer==NULL || output->vBuffer ==NULL){
		VENC_LOG(ERR,("%s params is null !\n",MODULE_H264));
		return 0;
	}
	VENC_LOG(INFO,("%s h264_process()+++\n",MODULE_H264));
	
	//1,set output buffer 
	encIn.pOutBuf = (unsigned int *)(output->vBuffer);
	encIn.busOutBuf  = output->bBuffer;
	encIn.outBufSize = output->size;

	//2,start do encode h264 stream 
	//==========================================================================	
	ret = H264EncStrmStart(h264inst, &encIn, &encOut); 
	//==========================================================================
	if(ret != H264ENC_OK){
		VENC_LOG(ERR,("%s H264EncStrmStart() failed!,return %d\n",MODULE_H264, ret));
		return 0;
	}

	streamSize += encOut.streamSize;

	if(excfg->enablepreproc){
		wSrc = excfg->expreproc.origWidth;
		hSrc = excfg->expreproc.origHeight;
		formatSrc = excfg->expreproc.inputType;
		if(excfg->expreproc.inputType<=1){
			src_img_size = excfg->expreproc.origWidth*excfg->expreproc.origHeight*3/2;
		}else if(excfg->expreproc.inputType<9){
			src_img_size = excfg->expreproc.origWidth*excfg->expreproc.origHeight*2;
		}else{
			src_img_size = excfg->expreproc.origWidth*excfg->expreproc.origHeight*4;
		}
	}else{
		formatSrc = H264ENC_YUV420_PLANAR;
		wSrc = excfg->exencconfig.width;
		hSrc = excfg->exencconfig.height;
		src_img_size  = excfg->exencconfig.width * excfg->exencconfig.height * 3 / 2;
	}

	//4,Setup encoder input
	{
		pInputData = (char*)input->vBuffer;
		totalFrameCnt = 1;                 //input->size / src_img_size;
		encIn.busLuma = input->bBuffer;
		encIn.busChromaU = input->addr_u;
		encIn.busChromaV = input->addr_v;
	} 

	 /* First frame is always intra with time increment = 0 */  
	encIn.codingType = H264ENC_INTRA_FRAME;
	encIn.timeIncrement = 0;
	encIn.busLumaStab = stabinput->bBuffer; 
	

	retValue = 1;
	while(frameCnt<totalFrameCnt){
		// if(!h264_read_pic(pInputData, input, frameCnt,src_img_size,wSrc,hSrc,formatSrc)){
		// 	VENC_LOG(ERR,("%s h264_read_pic() failed!\n",MODULE_H264));
		// 	retValue = 0;
		// 	break;
		// }

		if(excfg->enablepreproc && excfg->expreproc.videoStabilization){
			if(!h264_read_pic(pInputData, stabinput,(frameCnt+1)>=totalFrameCnt?frameCnt:(frameCnt+1),	\
									src_img_size,wSrc,hSrc,formatSrc)){
				VENC_LOG(ERR,("%s h264_read_pic() failed!\n",MODULE_H264));
				retValue = 0;
				break;
			}
		}

		if(excfg->enableratectrl && excfg->exratectrl.gopLen!=0xFFFFFFFF){
			iPicPerNframes = excfg->exratectrl.gopLen;
		}else{
			iPicPerNframes = 15;
		}
		
		if((frameCnt%iPicPerNframes)==0){
			encIn.codingType = H264ENC_INTRA_FRAME;
			if(frameCnt==0){
				encIn.timeIncrement = 0;
			}else{
				encIn.timeIncrement  = excfg->exencconfig.frameRateDenom; 
			}
		}else{
				encIn.codingType = H264ENC_PREDICTED_FRAME;
				encIn.timeIncrement  = excfg->exencconfig.frameRateDenom; 
		}

		VENC_LOG(INFO,("%s we want %s frame!\n",MODULE_H264,encIn.codingType == H264ENC_INTRA_FRAME?"I":"P"));
		
		//==========================================================================	
		//3,set user data to our encoder
		//fix me
		ret = H264EncStrmEncode(h264inst, &encIn, &encOut,h264enc_slice_ready_callnack_func ,&encSliceReadyCallbackPdata);
		if (ret != H264ENC_OK && ret != H264ENC_FRAME_READY ){
			VENC_LOG(ERR,("%s H264EncStrmEncode() failed!, ret = %d\n",MODULE_H264,ret));
			return 0;
		}

		//==========================================================================
		H264EncGetRateCtrl(h264inst, &rc);
		if(excfg->enablepreproc && excfg->expreproc.videoStabilization){
			H264EncGetPreProcessing(h264inst, &pp);
			VENC_LOG(INFO,("%s Video stabilization crop from(%d,%d) of (%d,%d)input source!\n",MODULE_H264,	\
					pp.xOffset,pp.yOffset,pp.origWidth,pp.origHeight));
		}

		streamSize += encOut.streamSize;
		switch(ret){
			case H264ENC_FRAME_READY:
				VENC_LOG(INFO,("H264ENC_FRAME_READY!\n"));
				VENC_LOG(INFO,("%5i  | %3i | %2i | %s | %7i %6i | \n",	\
								outFrameCnt,frameCnt,rc.qpHdr,encOut.codingType == H264ENC_INTRA_FRAME ? " I  " :	\
								encOut.codingType == H264ENC_PREDICTED_FRAME ? " P  " : "skip",	\
								streamSize,encOut.streamSize));

				if(pUserData && outFrameCnt == 0){
					/* We want the user data to be written only once so
					 * we disable the user data and free the memory after
					 * irst frame has been encoded. */
					//==========================================================================	
					if(H264EncSetSeiUserData(h264inst, NULL, 0)  != H264ENC_OK){
						VENC_LOG(WARN,("%s H264EncSetSeiUserData() failed!\n",MODULE_H264));
					}
				}
				outFrameCnt++;
				break;
			default:
				VENC_LOG(INFO,("%s H264EncStrmEncode() return %d\n",MODULE_H264,ret));
				retValue = 0;	
				break;
		}
		if(!retValue){
			VENC_LOG(ERR,("%s I'm sorry for the failure when encode %d picture\n",MODULE_H264,frameCnt));
			break;
		}

		frameCnt++;

		if(outFrameCnt>MAXENCODEDPICS){
			VENC_LOG(INFO,("%s api get enough encoded pcitures!\n",MODULE_H264));
			break;
		}

	}

	if(frameCnt != outFrameCnt){
		VENC_LOG(WARN,("%s total out frameCnt %d is not equal with total in frameCnt %d",	\
								MODULE_H264,outFrameCnt,frameCnt));
	}

	/* End stream */
	//==========================================================================	
	ret = H264EncStrmEnd(h264inst, &encIn, &encOut);
	if(ret != H264ENC_OK){
		VENC_LOG(ERR,("%s H264EncStrmEnd() failed!,return %d\n",MODULE_H264,ret));
		retValue = 0;
	}else{
		streamSize += encOut.streamSize;
		VENC_LOG(INFO,("%s       |     |    | END  |     | %7i %6i | \n",MODULE_H264,streamSize, encOut.streamSize));
		if(excfg->exencconfig.streamType == H264ENC_NAL_UNIT_STREAM){
#ifdef NAL_TO_ANNEXB_FORMAT
			pnalSizeBuf = encIn.pNaluSizeBuf;
			while(pnalSizeBuf[i] !=0){
				outBufferOffset += pnalSizeBuf[i];
				i++;
			}
			if(outBufferOffset != encOut.streamSize){
				VENC_LOG(WARN,("the out nal size is not equal with total out stream size!\n",MODULE_H264));
				retValue = 0;
			}
			i =0;
			outBufferOffset = 0;
#endif
		}
	}

	VENC_LOG(INFO,("%s h264_process()---\n",MODULE_H264));
	return retValue;
}

/*
func:h264 encode's main process function,should be call by our test case or 
by system api when do integration test
params:the pointer of H254EncCfg which contains all the  params to be set
return:0,encode failed
success,encode success
*/
int h264_encode(H264EncTbCfg *excfg)
{
	H264EncApiVersion ver;
	H264EncBuild build;
	H264EncInst h264inst;
	VencLinearMem inbuffer;
	VencLinearMem outbuffer;
	VencLinearMem stabinbuffer;
	H264EncTbCfg excfgbak;
	VENC_LOG(INFO,("%s h264_encode()+++\n",MODULE_H264));

	memset2(&ver,sizeof(H264EncApiVersion),0);
	memset2(&build,sizeof(H264EncBuild),0);
	memset2(&h264inst,sizeof(H264EncInst),0);
	memset2(&inbuffer,sizeof(VencLinearMem),0);
	memset2(&stabinbuffer,sizeof(VencLinearMem),0);
	memset2(&outbuffer,sizeof(VencLinearMem),0);
	memset2(&excfgbak,sizeof(H264EncTbCfg),0);


	//==========================================================================	
	ver = H264EncGetApiVersion();
	build = H264EncGetBuild();
	VENC_LOG(INFO,("%s H.264 Encoder API version %d.%d\n",MODULE_H264,ver.major,ver.minor));
	VENC_LOG(INFO,("%s HW ID: 0x%08x\t SW Build: %u.%u.%u\n",MODULE_H264,build.hwBuild,build.swBuild / 1000000,
							(build.swBuild / 1000) % 1000,build.swBuild % 1000));

	if(excfg==NULL){
		if(!venc_get_default_cfg(TYPE_H264,(void **)&excfg)){
			VENC_LOG(ERR,("%s venc_get_default_cfg() failed!\n",MODULE_H264));
			return 0;
		}	
	}
	memcpy((void *)&excfgbak,(void *)excfg,sizeof(H264EncTbCfg));

	if(!h264_open(excfg,&h264inst)){
		VENC_LOG(ERR,("%s h264_open() failed!\n",MODULE_H264));
		return 0;
	}

#if 0
	if(!h264_allocate_buffer(&inbuffer,&stabinbuffer,&outbuffer,excfg)){
		VENC_LOG(ERR,("% h264_allocate_buffer() failed!\n",MODULE_H264));
		goto ENCODE_FAIL;
	}
#else
	/*set buffer for Fixed address */
	if(!h264_set_buffer_addr(&inbuffer,&stabinbuffer,&outbuffer,excfg)){
		VENC_LOG(ERR,("%s h264_set_buffer_addr() failed!\n",MODULE_H264));
		goto ENCODE_FAIL;
	}
#endif

	if(!h264_process(&inbuffer,&stabinbuffer,&outbuffer,excfg,h264inst)){
		goto ENCODE_FAIL;
	}
	
	memcpy((void *)excfg,(void *)&excfgbak,sizeof(H264EncTbCfg));
	//h264_close(h264inst);
	//h264_free_buffer(&inbuffer,&stabinbuffer,&outbuffer); 


	VENC_LOG(INFO,("%s h264_encode()---\n",MODULE_H264));
	return 1;

ENCODE_FAIL:
	memcpy((void *)excfg,(void *)&excfgbak,sizeof(H264EncTbCfg));
	h264_close(h264inst);
	//h264_free_buffer(&inbuffer,&stabinbuffer,&outbuffer);
	return 0;
}

void  print_h264_enc_config(H264EncTbCfg *cfg){
#if 1
	printf("cfg common############################\n");
	printf("Case_Name               --> %s\n",cfg->caseName);
	printf("Input File              --> %s\n",cfg->inputFile);
	printf("Input user_Data         --> %s\n",cfg->inputUserDataFile);
	printf("Output File             --> %s\n",cfg->outputFile);
	printf("Output File Size        --> %d\n",cfg->outputSize);
	printf("Output File CRC32       --> 0x%x\n",cfg->outputCrc32);
	printf("enable Coding Ctrl      --> %d\n",cfg->enablecodingctrl);
	printf("enable rate ctrl        --> %d\n",cfg->enableratectrl);
	printf("enable pp               --> %d\n",cfg->enablepreproc);

	printf("\n\ncfg h264 Enc Config############################\n");
	printf("stream type --> %d\n",cfg->exencconfig.streamType);
	printf("level --> %d\n",cfg->exencconfig.level);
	printf("width --> %d\n",cfg->exencconfig.width);
	printf("height --> %d\n",cfg->exencconfig.height);
	printf("frameRateNum --> %d\n",cfg->exencconfig.frameRateNum);
	printf("frameRateDenom --> %d\n",cfg->exencconfig.frameRateDenom);
	//fix me
	//printf("complexityLevel --> %d\n",cfg->exencconfig.complexityLevel);
	printf("\n\ncfg h264 Coding Ctrl ############################\n");
	printf("Slice size --> %d\n",cfg->excodectrl.sliceSize);
	printf("seiMessages --> %d\n",cfg->excodectrl.seiMessages);
	printf("videoFullRange --> %d\n",cfg->excodectrl.videoFullRange);
	printf("constrainedIntraPrediction --> %d\n",cfg->excodectrl.constrainedIntraPrediction);
	printf("disableDeblockingFilter --> %d\n",cfg->excodectrl.disableDeblockingFilter);
	printf("sampleAspectRatioWidth --> %d\n",cfg->excodectrl.sampleAspectRatioHeight);
	printf("sampleAspectRatioHeight --> %d\n",cfg->excodectrl.sampleAspectRatioHeight);
	printf("enableCabac --> %d\n",cfg->excodectrl.enableCabac);
	printf("cabacInitIdc --> %d\n",cfg->excodectrl.cabacInitIdc);
	printf("transform8x8Mode --> %d\n",cfg->excodectrl.transform8x8Mode);
	printf("quarterPixelMv --> %d\n",cfg->excodectrl.quarterPixelMv);

	printf("\n\ncfg h264 Rate Ctrl ############################\n");
	printf("pictureRc --> %d\n",cfg->exratectrl.pictureRc);
	printf("mbRc --> %d\n",cfg->exratectrl.mbRc);
	printf("pictureSkip --> %d\n",cfg->exratectrl.pictureSkip);
	printf("qpHdr --> %d\n",cfg->exratectrl.qpHdr);
	printf("qpMin --> %d\n",cfg->exratectrl.qpMin);
	printf("qpMax --> %d\n",cfg->exratectrl.qpMax);
	printf("bitPerSecond --> %d\n",cfg->exratectrl.bitPerSecond);
	printf("hrd --> %d\n",cfg->exratectrl.hrd);
	printf("hrdCpbSize --> %d\n",cfg->exratectrl.hrdCpbSize);
	printf("gopLen --> %d\n",cfg->exratectrl.gopLen);
	printf("intraQpDelta --> %d\n",cfg->exratectrl.intraQpDelta);
	printf("fixedIntraQp --> %d\n",cfg->exratectrl.fixedIntraQp);
	printf("mbQpAdjustment --> %d\n",cfg->exratectrl.mbQpAdjustment);



	printf("\n\ncfg h264 PP ############################\n");
	printf("origWidth --> %d\n",cfg->expreproc.origWidth);
	printf("origHeight --> %d\n",cfg->expreproc.origHeight);
	printf("xOffset --> %d\n",cfg->expreproc.xOffset);
	printf("yOffset --> %d\n",cfg->expreproc.yOffset);
	printf("inputType --> %d\n",cfg->expreproc.inputType);
	printf("rotation --> %d\n",cfg->expreproc.rotation);
	printf("videoStabilization --> %d\n",cfg->expreproc.videoStabilization);
	printf("CC_type --> %d\n",cfg->expreproc.colorConversion.type);
	printf("cc_a --> %d\n",cfg->expreproc.colorConversion.coeffA);
	printf("cc_b --> %d\n",cfg->expreproc.colorConversion.coeffB);
	printf("cc_c --> %d\n",cfg->expreproc.colorConversion.coeffC);
	printf("cc_e --> %d\n",cfg->expreproc.colorConversion.coeffE);
	printf("cc_f --> %d\n",cfg->expreproc.colorConversion.coeffF);

	printf("cfg over ############################\n");
#endif
}
int32_t check_deal_h264_enc_config_data(H264EncTbCfg *cfg){
// should add more pre check actions	
	return 0;
//	cfg->excfg.pCom = cfg->inputComment;
//	cfg->excfg.comLength = strlen(cfg->excfg.pCom);	
//	return 0;
}
void h264_encode_set_default_config(H264EncTbCfg *cfg);

static int atoi(char *s) {
  int i;
  int n = 0;
  for (i = 0; s[i] >= '0' && s[i] <= '9'; ++i) {
    n = 10 * n + (s[i] - '0');
  }
  return n;
}

void venc_h264_show_usage()
{
	printf("Usage: venc [type] [OPTION]...\n\n");
	printf("type: jpeg h264 or stab \n\n");
	printf("-h \t\tcommand help\n");
	printf("-a <size>\t\t width\n");
	printf("-b <size>\t\t high\n");
	printf("-t <0-2> \t\t YCbCr type:0-420, 1-422, 2-440\n");
}

int32_t venc_h264_entry(int argc,char *argv[]){
	int32_t ret = 0;
	H264EncTbCfg h264_enc_cfg = {0};

	int c, tmp;
	int option_index = 0;
	static const char short_options[] = "a:b:t:s:cx";
  	static const struct option long_options[] = {
        { 0, 0, 0, 0 },
    };	

	h264_encode_set_default_config(&h264_enc_cfg);
	check_deal_h264_enc_config_data(&h264_enc_cfg);

	while ((c = getopt_long(argc, argv, short_options, long_options,
				&option_index)) != -1) {
    	switch (c) {
			case 'a':
			tmp = atoi(optarg);
			h264_enc_cfg.exencconfig.width = tmp;
			break;

			case 'b':
			tmp = atoi(optarg);
			h264_enc_cfg.exencconfig.height = tmp;
			break;

			case 't':
			tmp = atoi(optarg);
			h264_enc_cfg.exencconfig.streamType = tmp;
			break;

			case 's':
			tmp = atoi(optarg);
			h264_enc_cfg.ex_picture_size = tmp;
			break;

			case 'c':  /*Cropping: case 1152*/
			h264_enc_cfg.enablepreproc = 1;
			h264_enc_cfg.expreproc.origHeight = 144;
			h264_enc_cfg.expreproc.origWidth = 352;
			h264_enc_cfg.expreproc.xOffset = 0;
			h264_enc_cfg.expreproc.yOffset = 0;
			h264_enc_cfg.expreproc.inputType = H264ENC_YUV420_PLANAR;
			h264_enc_cfg.expreproc.rotation = H264ENC_ROTATE_90L;

			h264_enc_cfg.enableratectrl = 1;
			h264_enc_cfg.exratectrl.qpHdr = 26;
			break;
		}
	}

	venc_module_enable(0);

	/*set venc share memory*/
	writel(1, ITCS_C_STSM_VENC_BASE + 0x24); 
	
	ret = h264_encode(&h264_enc_cfg); 
	if(ret < 0)
		goto Fail;
	return TB_RET_MANUAL;
Fail:
	LOG_ERR("h264 venc case error -> %s\n",h264_enc_cfg.caseName);	
	return TB_RET_FAIL;
}

int32_t load_h264_enocode_para_from_file(char *filename,H264EncTbCfg *cfg){
	para_struct_t	para[] = {
		{"Case_Name", 	char_p,1, cfg->caseName }, 			//Case_Name
		{"Input_File", 	char_p,1, cfg->inputFile }, 		//Input_File
		{"Input_UserDataFile", 	char_p,1, cfg->inputUserDataFile  },	//Input_Thumbnail
		{"Output_File", 	char_p,1, cfg->outputFile  }, 		//Output_File
		{"Output_Size", 	u32_p,1, &cfg->outputSize  },		//Input_Comment
		{"Output_Crc32", 	u32_p,1, &cfg->outputCrc32  },		//Input_Comment
		//H264EncConfig part
		{"Enable_CodingCtrl", 	u32_p, 1, &cfg->enablecodingctrl  }, //Input_Width
		{"Enable_RateCtrl", 	u32_p, 1, &cfg->enableratectrl  },//Input_Height
		{"Enable_Preproc", 	u32_p, 1, &cfg->enablepreproc  },	//Input_Offset_X
		{"Enc_StreamType", 	u32_p, 1, &cfg->exencconfig.streamType  },	//Input_Offset_Y
		{"Enc_Level", 	u32_p, 1, &cfg->exencconfig.level  },	//Input_Offset_Y
		{"Enc_Width", 	u32_p, 1, &cfg->exencconfig.width  },	//Input_Offset_Y
		{"Enc_Height", 	u32_p, 1, &cfg->exencconfig.height  },	//Input_Offset_Y
		{"Enc_FrameRateNum", 	u32_p, 1, &cfg->exencconfig.frameRateNum  },	//Input_Offset_Y
		{"Enc_FrameRateDenom", 	u32_p, 1, &cfg->exencconfig.frameRateDenom  },	//Input_Offset_Y
		//{"Enc_ComplexityLevel", 	u32_p, 1, &cfg->exencconfig.complexityLevel  },	//Input_Offset_Y
		{"Enc_ScaledWidth", 	u32_p, 1, &cfg->exencconfig.scaledWidth  },	//Input_Offset_Y
		{"Enc_ScaledHeight", 	u32_p, 1, &cfg->exencconfig.scaledHeight  },	//Input_Offset_Y
		{"Enc_RefFrameAmount", 	u32_p, 1, &cfg->exencconfig.refFrameAmount },	//Input_Offset_Y
		//H264EncCodingCtrl
		{"CodingCtrl_SliceSize", 	u32_p, 1, &cfg->excodectrl.sliceSize  },	//Input_Offset_Y
		{"CodingCtrl_SeiMessage", 	u32_p, 1, &cfg->excodectrl.seiMessages  },	//Input_Offset_Y
		{"CodingCtrl_VideoFullRange", 	u32_p, 1, &cfg->excodectrl.videoFullRange  },	//Input_Offset_Y
		{"CodingCtrl_ConstraninedIntraPrediction", 	u32_p, 1, &cfg->excodectrl.constrainedIntraPrediction  },	//Input_Offset_Y
		{"CodingCtrl_DisableDeblockingFilter", 	u32_p, 1, &cfg->excodectrl.disableDeblockingFilter  },	//Input_Offset_Y
		{"CodingCtrl_SampleAspectRatioWidth", 	u32_p, 1, &cfg->excodectrl.sampleAspectRatioWidth  },	//Input_Offset_Y
		{"CodingCtrl_SampleAspectRatioHeight", 	u32_p, 1, &cfg->excodectrl.sampleAspectRatioHeight  },	//Input_Offset_Y
		{"CodingCtrl_EnableCabac", 	u32_p, 1, &cfg->excodectrl.enableCabac  },	//Input_Offset_Y
		{"CodingCtrl_CabacInitIdc", 	u32_p, 1, &cfg->excodectrl.cabacInitIdc  },	//Input_Offset_Y
		{"CodingCtrl_Transform8x8Mode", 	u32_p, 1, &cfg->excodectrl.transform8x8Mode  },	//Input_Offset_Y
		{"CodingCtrl_QuarterPixelMv", 	u32_p, 1, &cfg->excodectrl.quarterPixelMv  },	//Input_Offset_Y
		//H264EncRateCtrl
		{"RateCtrl_PictureRc", 	u32_p, 1, &cfg->exratectrl.pictureRc  },	//Input_Offset_Y
		{"RateCtrl_MbRc", 	u32_p, 1, &cfg->exratectrl.mbRc  },	//Input_Offset_Y
		{"RateCtrl_PictureSkip", 	u32_p, 1, &cfg->exratectrl.pictureSkip  },	//Input_Offset_Y
		{"RateCtrl_QpHdr", 	i32_p, 1, &cfg->exratectrl.qpHdr  },	//Input_Offset_Y
		{"RateCtrl_QpMin", 	u32_p, 1, &cfg->exratectrl.qpMin  },	//Input_Offset_Y
		{"RateCtrl_QpMax", 	u32_p, 1, &cfg->exratectrl.qpMax  },	//Input_Offset_Y
		{"RateCtrl_BitPerSecond", 	u32_p, 1, &cfg->exratectrl.bitPerSecond  },	//Input_Offset_Y
		{"RateCtrl_Hrd", 	u32_p, 1, &cfg->exratectrl.hrd  },	//Input_Offset_Y
		{"RateCtrl_HrdCpbSize", 	u32_p, 1, &cfg->exratectrl.hrdCpbSize  },	//Input_Offset_Y
		{"RateCtrl_GopLen", 	u32_p, 1, &cfg->exratectrl.gopLen  },	//Input_Offset_Y
		{"RateCtrl_IntraQpDelta", 	i32_p, 1, &cfg->exratectrl.intraQpDelta  },	//Input_Offset_Y
		{"RateCtrl_FixedIntraQp", 	u32_p, 1, &cfg->exratectrl.fixedIntraQp  },	//Input_Offset_Y
		{"RateCtrl_MbQpAdjustment", 	i32_p, 1, &cfg->exratectrl.mbQpAdjustment  },	//Input_Offset_Y
//	PP 
		{"PP_OrigWidth", 	u32_p, 1, &cfg->expreproc.origWidth  },	//Input_Offset_Y
		{"PP_OrigHeight", 	u32_p, 1, &cfg->expreproc.origHeight  },	//Input_Offset_Y
		{"PP_OffsetX", 	u32_p, 1, &cfg->expreproc.xOffset  },	//Input_Offset_Y
		{"PP_OffsetY", 	u32_p, 1, &cfg->expreproc.yOffset  },	//Input_Offset_Y
		{"PP_InputType", 	u32_p, 1, &cfg->expreproc.inputType  },	//Input_Offset_Y
		{"PP_Rotation", 	u32_p, 1, &cfg->expreproc.rotation  },	//Input_Offset_Y
		{"PP_VideoStabilization", 	u32_p, 1, &cfg->expreproc.videoStabilization  },	//Input_Offset_Y
		{"PP_CC_Type", 	u32_p, 1, &cfg->expreproc.colorConversion.type  },	//Input_Offset_Y
		{"PP_CC_A", 	u16_p, 1, &cfg->expreproc.colorConversion.coeffA  },	//Input_Offset_Y
		{"PP_CC_B", 	u16_p, 1, &cfg->expreproc.colorConversion.coeffB  },	//Input_Offset_Y
		{"PP_CC_C", 	u16_p, 1, &cfg->expreproc.colorConversion.coeffC  },	//Input_Offset_Y
		{"PP_CC_E", 	u16_p, 1, &cfg->expreproc.colorConversion.coeffE  },	//Input_Offset_Y
		{"PP_CC_F", 	u16_p, 1, &cfg->expreproc.colorConversion.coeffF  },	//Input_Offset_Y
	};
	int32_t para_num = sizeof(para) /sizeof(para_struct_t);
	return load_para_from_cfg_file((signed char *)filename,para,para_num);
}
void h264_encode_set_default_config(H264EncTbCfg *cfg){
	H264EncTbCfg default_cfg = 
	{
		"",
		"venc/h264/res/yuv420Semiplanar_progressive_w320_h240.yuv",
		"venc/h264/h264_w320_h240_testcase_encoding_level1_format.h264",
		"venc/h264/res/infotmuserdata.txt",
		0,
		0,
		0,
		0,
		0,
		0,
	    {
        	H264ENC_BYTE_STREAM,  
			0,
        	H264ENC_LEVEL_1_1,
        	320,           
        	240,          
        	15,    
        	1, 
			//fix me
        	//H264ENC_COMPLEXITY_1 
			0,//scaledWidth
			0,//scaledHeight
			1,//refFrameAmount
    	},
    		
    	{
    		0
		},
        {
			0
		},
		{
        	320,
			240,
			0,
			0,
			0,
			//H264ENC_YUV420_SEMIPLANAR,
			H264ENC_ROTATE_0,
			0,
        	{
				H264ENC_RGBTOYUV_BT601,
				0,
				0,
				0,
				0,
				0
			}
		}

	};
	memcpy( cfg,&default_cfg ,sizeof(H264EncTbCfg));
}



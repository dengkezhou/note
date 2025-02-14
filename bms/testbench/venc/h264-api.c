
#include <h264-api.h>
#include <h264encapi.h>
#include <asm/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if 0
#define H1_H264_API_DBG(str...)  printf(str)
#define H1_H264_API_ERR(str...)  printf(str)
#define H1_H264_API_INFO(str...)  
#else 
#define H1_H264_API_DBG(str...)  printf(str)
#define H1_H264_API_ERR(str...)  printf(str)
#define H1_H264_API_INFO(str...)  printf(str) 
#endif


typedef struct {
	uint32_t width;
	uint32_t height;
	uint32_t pFrameNum;
	uint32_t encPicNum ;
	uint32_t pollMode ;
	uint32_t frameFormat ; //0 :NV12   1: NV21  //may be add more
	char inYuv[128];
	char outStrm[128];
}H264EncodeApiTbCfg;

typedef struct {
	H264EncInst inst;
	H264EncConfig  encCfg;
	H264EncCodingCtrl codingCtrl;
	H264EncRateCtrl   rateCtrl;
	//PreProcessingCfg
	H264EncPreProcessingCfg ppCfg;
	H264EncIn encIn;
	H264EncOut encOut;
	int32_t encodeState;
	uint32_t pFrameNum;
	uint32_t decFrameNum;
}H264EncodeHandler;
extern uint32_t venc0_irq_mode_enable  ;
extern uint32_t venc0_irq_value ;
extern uint32_t venc0_irq_async_mode_enable ;

void *h264_encode_initial(H264EncodeApiTbCfg *para){
	void *hd = (void *) malloc(sizeof(H264EncodeHandler));
	H264EncodeHandler *handler =  (H264EncodeHandler *) hd;
	if(hd == NULL){
		printf("h264 malloc failed\n");
		return NULL;
	}
	if(para->pollMode == 0){
		venc0_irq_async_mode_enable = 1;
		venc0_irq_mode_enable =  1;
		venc0_irq_value = 0;
	}
	else {
		venc0_irq_async_mode_enable = 0;
		venc0_irq_mode_enable =  0;
		venc0_irq_value = 0;
	}
	
	memset(hd,0,sizeof(H264EncodeHandler));
	if(320 ==para->width && 240 == para->height ){
		handler->encCfg.level = H264ENC_LEVEL_1_1;
		handler->encCfg.frameRateNum = 5;
		handler->encCfg.frameRateDenom = 1;
	}
	else if(640 == para->width && 480 == para->height ){
		handler->encCfg.level = H264ENC_LEVEL_2_2;
		handler->encCfg.frameRateNum = 15;
		handler->encCfg.frameRateDenom = 1;
	}
	else if(1280 == para->width &&  720 == para->height ){
		handler->encCfg.level = H264ENC_LEVEL_3_1;
		handler->encCfg.frameRateNum = 30;
		handler->encCfg.frameRateDenom = 1;
	}
	else if(1920 == para->width && 1080 == para->height ){
		handler->encCfg.level = H264ENC_LEVEL_4;
		handler->encCfg.frameRateNum = 30;
		handler->encCfg.frameRateDenom = 1;
	}
	else if(1920 == para->width && 1088 == para->height ){
		handler->encCfg.level = H264ENC_LEVEL_4;
		handler->encCfg.frameRateNum = 30;
		handler->encCfg.frameRateDenom = 1;
	}
	else {
		H1_H264_API_ERR("not support setting now\n");
	}
	handler->encCfg.streamType = H264ENC_BYTE_STREAM;
	handler->encCfg.viewMode = 0;
	handler->encCfg.width  = para->width ;
	handler->encCfg.height =  para->height;
	handler->encCfg.refFrameAmount = 1;
	handler->pFrameNum =  para->pFrameNum;
	H264EncRet ret = 0;
	ret = H264EncInit(&handler->encCfg, &(handler->inst));
	if(ret != H264ENC_OK){
		H1_H264_API_ERR("h264 init  error -> %d\n",ret);
		goto ERROR_PROCESS ;
	}
	ret = H264EncGetRateCtrl(handler->inst, &handler->rateCtrl);
	if(ret != H264ENC_OK){

	}
	//ret = H264EncSetRateCtrl(handler->inst,handler->rateCtrl);
	if(ret != H264ENC_OK){

	}

	ret = H264EncGetCodingCtrl(handler->inst,&handler->codingCtrl);

	if(ret != H264ENC_OK){
	}
	//ret = H264EncSetCodingCtrl(handler->inst,&handler->codingCtrl);
	if(ret != H264ENC_OK){
	}
	ret = H264EncGetPreProcessing(handler->inst,&handler->ppCfg);

	if(ret != H264ENC_OK){
		H1_H264_API_ERR("get pre p error\n");
		goto ERROR_PROCESS;
	}
	switch (para->frameFormat){
		case  H264_INPUT_420SP_NV12 :
			handler->ppCfg.inputType =  H264ENC_YUV420_SEMIPLANAR ;
			break;
		case  H264_INPUT_420SP_NV21 :
			handler->ppCfg.inputType =  H264ENC_YUV420_SEMIPLANAR_VU ;
			break;
		case  H264_INPUT_420P :
			handler->ppCfg.inputType =  H264ENC_YUV420_PLANAR ;
			break;
		case  H264_INPUT_422_YUYV :
			handler->ppCfg.inputType =  H264ENC_YUV422_INTERLEAVED_YUYV ;
			break;
		case  H264_INPUT_422_UYVU :
			handler->ppCfg.inputType =  H264ENC_YUV422_INTERLEAVED_UYVY;
			break;
		case  H264_INPUT_RGB565 :
			handler->ppCfg.inputType =  H264ENC_RGB565 ;
			handler->ppCfg.colorConversion.type = H264ENC_RGBTOYUV_BT601;
			break;
		case  H264_INPUT_BGR565 :
			handler->ppCfg.inputType =  H264ENC_BGR565 ;
			handler->ppCfg.colorConversion.type = H264ENC_RGBTOYUV_BT601;
			break;
		case  H264_INPUT_RGB555 :
			handler->ppCfg.inputType =  H264ENC_RGB555 ;
			handler->ppCfg.colorConversion.type = H264ENC_RGBTOYUV_BT601;
			break;
		case  H264_INPUT_BGR555 :
			handler->ppCfg.inputType =  H264ENC_BGR555 ;
			handler->ppCfg.colorConversion.type = H264ENC_RGBTOYUV_BT601;
			break;
		case  H264_INPUT_RGB888 :
			handler->ppCfg.inputType =  H264ENC_RGB888 ;
			handler->ppCfg.colorConversion.type = H264ENC_RGBTOYUV_BT601;
			break;
		case  H264_INPUT_BGR888 :
			handler->ppCfg.inputType =  H264ENC_BGR888 ;
			handler->ppCfg.colorConversion.type = H264ENC_RGBTOYUV_BT601;
			break;
		case  H264_INPUT_RGB444 :
			handler->ppCfg.inputType =  H264ENC_RGB444 ;
			handler->ppCfg.colorConversion.type = H264ENC_RGBTOYUV_BT601;
			break;
		case  H264_INPUT_BGR444 :
			handler->ppCfg.inputType =  H264ENC_BGR444 ;
			handler->ppCfg.colorConversion.type = H264ENC_RGBTOYUV_BT601;
			break;
		case  H264_INPUT_RGB101010 :
			handler->ppCfg.inputType =  H264ENC_RGB101010 ;
			handler->ppCfg.colorConversion.type = H264ENC_RGBTOYUV_BT601;
			break;
		case  H264_INPUT_BGR101010 :
			handler->ppCfg.inputType =  H264ENC_BGR101010 ;
			handler->ppCfg.colorConversion.type = H264ENC_RGBTOYUV_BT601;
			break;
		default :
			H1_H264_API_ERR("not support input type \n");
			goto ERROR_PROCESS;
	}
	handler->ppCfg.origWidth = handler->encCfg.width;
	handler->ppCfg.origHeight =  handler->encCfg.height;
	handler->ppCfg.xOffset = 0;
	handler->ppCfg.yOffset = 0;
	handler->ppCfg.videoStabilization = 0;
	handler->ppCfg.scaledOutput =  0;
	handler->ppCfg.interlacedFrame = 0 ;
	ret = H264EncSetPreProcessing(handler->inst,&handler->ppCfg);
	if(ret != H264ENC_OK){
		H1_H264_API_ERR("set pre p error\n");
	}
	return hd;
ERROR_PROCESS :
	if(handler->inst != NULL){
		H264EncRelease(handler->inst);
	}
	if(handler != NULL )
		free(handler);
	handler = NULL;
	return NULL;
}
int h264_encode_get_start_stream(void *hd,uint32_t outBuf,uint32_t outBufSize){
	H264EncodeHandler *handler =  (H264EncodeHandler *) hd;
	H264EncRet ret ;
	handler->encIn.pOutBuf =  (uint32_t  *)(size_t)outBuf;
	handler->encIn.busOutBuf =  outBuf;
	handler->encIn.outBufSize = outBufSize; 
	ret = H264EncStrmStart(handler->inst ,&handler->encIn,&handler->encOut);
	if (ret != H264ENC_OK){
		H1_H264_API_ERR("h264 start stream error -> %d\n",ret);
		return ret ;
	}
	else {
		return handler->encOut.streamSize;
	}
}
int32_t h264_encode_frame(void *hd,uint32_t inFrameYBuf,uint32_t inFrameUvBuf,uint32_t outBuf,uint32_t outBufSize)  {
	H264EncodeHandler *handler =  (H264EncodeHandler *) hd;
	H264EncRet ret ;
	handler->encIn.pOutBuf =  (uint32_t *)(size_t)outBuf;
	handler->encIn.busOutBuf =  outBuf;
	handler->encIn.outBufSize = outBufSize; 
	
	if((handler->decFrameNum % handler->pFrameNum ) == 0){
		H1_H264_API_INFO("encode I frame\n");
		handler->encIn.codingType = H264ENC_INTRA_FRAME ;
		handler->encIn.timeIncrement = handler->decFrameNum == 0 ? 0 :1;
		handler->encIn.ipf = H264ENC_NO_REFERENCE_NO_REFRESH ;
		handler->encIn.ltrf = H264ENC_NO_REFERENCE_NO_REFRESH ;
	}
	else {
		H1_H264_API_INFO("encode P frame\n");
		handler->encIn.codingType = H264ENC_PREDICTED_FRAME ;
		handler->encIn.timeIncrement = 1;
		handler->encIn.ipf = H264ENC_REFERENCE_AND_REFRESH ;
		handler->encIn.ltrf = H264ENC_REFERENCE ;
	}
	handler->encIn.busLuma =  inFrameYBuf;
	handler->encIn.busChromaU = inFrameUvBuf ;
	handler->encIn.busChromaV =  0 ;//handler->encIn.busChromaU + handler->encCfg.width * handler->encCfg.height/ 4 ;

	ret = H264EncStrmEncode(handler->inst ,&handler->encIn,&handler->encOut,NULL,NULL);
	if (ret == H264ENC_OK){
		H1_H264_API_ERR("h264 encode stream ok -> %d\n",ret);
		return ret ;
	}
	else if (ret == H264ENC_FRAME_READY ){
		H1_H264_API_INFO("h264 encode stream ready -> %d  %d\n",ret,handler->decFrameNum++);
		return handler->encOut.streamSize;
	}
	else {
		H1_H264_API_ERR("h264 encode stream error -> %d\n",ret);
		return ret;
	}
}
int32_t h264_encode_frame_is_done(void *hd){
	H264EncodeHandler *handler =  (H264EncodeHandler *) hd;
	if(venc0_irq_value == 0x5){
		return readl(0x25100000 + 23*4)/8;
	}
	return -1;
}
int32_t h264_encode_get_end_stream(void *hd,uint32_t outBuf,uint32_t outBufSize){
	H264EncodeHandler *handler =  (H264EncodeHandler *) hd;
	H264EncRet ret ;
	handler->encIn.pOutBuf =  (uint32_t *)(size_t)outBuf;
	handler->encIn.busOutBuf =  outBuf;
	handler->encIn.outBufSize = outBufSize; 
	ret = H264EncStrmEnd(handler->inst ,&handler->encIn,&handler->encOut);
	if (ret != H264ENC_OK){
		H1_H264_API_ERR("h264 get end stream error -> %d\n",ret);
		return ret ;
	}
	else {
		return handler->encOut.streamSize;
	}
}
void h264_encode_deinital(void *hd){
	H264EncodeHandler *handler =  (H264EncodeHandler *) hd;
	if(handler->inst != NULL){
		H264EncRelease(handler->inst);
	}
	if(handler != NULL )
		free(handler);
	handler = NULL;
}


#define H1_H264_API_API_DEMO_BUF_SIZE  0xA00000
#define H264_INPUT_420SP_NV21 0
H264EncodeApiTbCfg h264ApiTbCfg[] = {
	{
		320,
		240,
		10,
		100,
		0,
		H264_INPUT_420SP_NV21,
		"venc/h264/res/api_demo_320x240.yuv",
		"venc/h264/api_demo_320x240.h264",
	},
	{
		640,
		480,
		10,
		100,
		0,
		H264_INPUT_420SP_NV12,
		"venc/h264/res/api_demo_640x480.yuv",
		"venc/h264/api_demo_640x480.h264",
	},
	{
		1920,
		1080,
		10,
		100,
		0,
		H264_INPUT_420SP_NV12,
		"venc/h264/res/api_demo_1920x1080.yuv",
		"venc/h264/api_demo_1920x1080.h264",
	},
	{
		1920,
		1088,
		10,
		100,
		0,
		H264_INPUT_420SP_NV12,
		"venc/h264/res/api_demo_1920x1088.yuv",
		"venc/h264/api_demo_1080p.h264",
	},
	{
		1280,
		720,
		10,
		100,
		0,
		H264_INPUT_420SP_NV12,
		"venc/h264/res/api_demo_720p.yuv",
		"venc/h264/api_demo_720p.h264",
	},
	{
		640,
		360,
		1,
		100,
		0,
		H264_INPUT_420SP_NV12,
		"venc/h264/res/api_demo_640x360_420sp.yuv",
		"venc/h264/api_demo_640x360.h264",
	},
};
int32_t h264_encode_api_demo(int argc ,char *argv[] ){
	void *handler = NULL;
	H264EncodeApiTbCfg *cfg = NULL;
	if(argc < 3 ){
		H1_H264_API_ERR("venc api qvga/vga/1080p\n");
		return -1;
	}
	if (strncmp(argv[2],"qvga",4) == 0 ){
		cfg = h264ApiTbCfg ;
		H1_H264_API_INFO("test h264 for qvga\n");
	}
	else if (strncmp(argv[2],"vga",3) == 0 ){
		H1_H264_API_INFO("test h264 for vga\n");
		cfg = h264ApiTbCfg +1  ;
	}
	else if(strncmp(argv[2],"1080",5 ) == 0 ){
		H1_H264_API_INFO("test h264 for 1080p\n");
		cfg = h264ApiTbCfg + 2 ;
	}
	else if(strncmp(argv[2],"1080p",5 ) == 0 ){
		H1_H264_API_INFO("test h264 for 1080p\n");
		cfg = h264ApiTbCfg + 3 ;
	}
	else if(strncmp(argv[2],"720p",5 ) == 0 ){
		H1_H264_API_INFO("test h264 for 720p\n");
		cfg = h264ApiTbCfg + 4 ;
	}
	else {
		H1_H264_API_ERR("test case not support -> %s\n,argv[2]");
		H1_H264_API_ERR("venc api qvga/vga/720p/1080p\n");
		return -1;
	}
	H1_H264_API_INFO("%s\n",cfg->inYuv);
	H1_H264_API_INFO("%s\n",cfg->outStrm);
	H1_H264_API_INFO("%d  %d  %d\n",cfg->width,cfg->height,cfg->pFrameNum,cfg->encPicNum);
	FILE *inFd = fopen(cfg->inYuv,"rb");
	if(inFd == NULL)
		goto ERROR_PROCESS;
	FILE *outFd = fopen(cfg->outStrm,"wb");
	if(outFd == NULL)
		goto ERROR_PROCESS;
	char *inBuf = (char *)malloc(H1_H264_API_API_DEMO_BUF_SIZE);
	if(inBuf == NULL)
		goto ERROR_PROCESS;
	char *outBuf =(char *)malloc(H1_H264_API_API_DEMO_BUF_SIZE);
	if(outBuf == NULL)
		goto ERROR_PROCESS;
	
	uint32_t frameSize = cfg->width * cfg->height *3/2;
	uint32_t i ;
	fseek(inFd,0,SEEK_END);
	uint32_t frameNum =  ftell(inFd)/frameSize;
	if (frameNum < cfg->encPicNum ){
		H1_H264_API_ERR("input data less than request %d %d\n",frameNum,cfg->encPicNum);
		return -1;
	}
	H1_H264_API_DBG("decode frame num->%d\n",frameNum);
	fseek(inFd,0,SEEK_SET);
	int32_t ret = 0 ;
	int32_t temp ;
	int32_t writeSize ;
	H264EncodeApiTbCfg para = {0};	
	para.width = cfg->width;
	para.height =  cfg->height;
	para.pFrameNum =  cfg->pFrameNum;
	para.pollMode =  cfg->pollMode ;
	para.frameFormat =  cfg->frameFormat;
	handler = h264_encode_initial(&para);
	if(handler == NULL ){
		H1_H264_API_ERR("h264 initial error\n");	
		goto ERROR_PROCESS;
	}
	ret = h264_encode_get_start_stream(handler,(uint32_t)(size_t)outBuf,
			H1_H264_API_API_DEMO_BUF_SIZE);
	if(ret <= 0 ){
		H1_H264_API_ERR("h264 get start stream  error\n");	
		goto ERROR_PROCESS;
	}
	H1_H264_API_INFO("start stream size ->%d\n",ret);
	temp =  fwrite(outBuf,ret ,1,outFd);
	if(temp != ret){
		H1_H264_API_ERR("h264 write start stream  error\n");	
		goto ERROR_PROCESS;
	}
	for(i = 0;i< cfg->encPicNum;i++){
		temp = fread(inBuf,frameSize,1,inFd);
		if(temp != frameSize){
			H1_H264_API_ERR("h264 read frame error\n");	
			goto ERROR_PROCESS;
		}
		ret = h264_encode_frame(handler,(uint32_t)(size_t)inBuf,
			((uint32_t)(size_t)inBuf) + cfg->width*cfg->height, 
				(uint32_t)(size_t)outBuf,
				H1_H264_API_API_DEMO_BUF_SIZE);
		if(ret < 0){
			H1_H264_API_INFO("h264 encode frame in process \n");
			udelay(1000);
			ret = h264_encode_frame_is_done(handler);
		}
		if(ret < 0 ){
			H1_H264_API_ERR("h264 encode frame error \n");
			goto ERROR_PROCESS;
		}
		else if (0 == ret ){
			H1_H264_API_DBG("on process\n");
			
		}
		H1_H264_API_INFO("stream size ->%d\n",ret);
		temp =  fwrite(outBuf,ret ,1,outFd);
		if(temp != ret){
			H1_H264_API_ERR("h264 write stream  error\n");	
			goto ERROR_PROCESS;
		}
	}
	
	ret = h264_encode_get_end_stream(handler,(uint32_t )(size_t)outBuf,H1_H264_API_API_DEMO_BUF_SIZE);
	if(ret <= 0 ){
		H1_H264_API_ERR("h264 get start stream  error\n");	
		goto ERROR_PROCESS;
	}
	H1_H264_API_INFO("end stream size ->%d\n",ret);
	temp =  fwrite(outBuf,ret ,1,outFd);
	if(temp != ret){
		H1_H264_API_ERR("h264 write start stream  error\n");	
		goto ERROR_PROCESS;
	}
ERROR_PROCESS :
	if(handler != NULL){
		h264_encode_deinital(handler);
	}
	if(inFd != NULL){
		fclose(inFd);
	}
	if(outFd != NULL){
		fclose(outFd);
	}
	if(inBuf != NULL){
		free(inBuf);
	}
	if(outBuf != NULL){
		free(outBuf);
	}
}

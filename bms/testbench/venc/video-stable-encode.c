#include "video-stable-encode.h"
#include "venc-common.h"
#include <para.h>
#include <crc32.h>
void camstab_close(VideoStbInst stabinst)
{
	VideoStbRet ret;
	if(stabinst ==NULL){
		VENC_LOG(ERR,("%s params is null!\n",MODULE_STAB));
		return;
	}
	
	//==========================================================================	
	ret = VideoStbRelease(stabinst); 

	if(ret != VIDEOSTB_OK){
		VENC_LOG(ERR,("%s release video stablization instance failed!\n",MODULE_STAB));
	}
}


int camstab_open(VideoStbInst *stabinst,CamStabTbConfig *excfg)
{
	VideoStbParam stabParam = {0};
	VideoStbRet ret;
	if(stabinst==NULL || excfg==NULL){
		VENC_LOG(ERR,("params is null!\n",MODULE_STAB));
		return 0;
	}

	//print the test configuration list
	VENC_LOG(INFO,("%s CAMERA STABILIZATION TEST CONFIGURATION LIST:\n",MODULE_STAB));
	VENC_LOG(INFO,("%s input file name :%s \n",MODULE_STAB,excfg->inputFile));
	VENC_LOG(INFO,("%s input image width:%d \n",MODULE_STAB,excfg->inputWidth));
	VENC_LOG(INFO,("%s input image height:%d \n",MODULE_STAB,excfg->inputHeight));
	VENC_LOG(INFO,("%s input image stride:%d \n",MODULE_STAB,excfg->stride));
	VENC_LOG(INFO,("%s input image stabilizedWidth:%d \n",MODULE_STAB,excfg->stabilizedWidth));
	VENC_LOG(INFO,("%s input image stabilizedHeight:%d \n",MODULE_STAB,excfg->stabilizedHeight));
	VENC_LOG(INFO,("%s input image format:%d \n",MODULE_STAB,excfg->format));
	
	//some simple checking
	if(excfg->inputWidth <104 || excfg->inputHeight<104){
		VENC_LOG(ERR,("%s invalid input size(%d,%d)\n",MODULE_STAB,excfg->inputWidth,excfg->inputHeight));
		return 0;
	}
	if(excfg->stabilizedWidth<96 || excfg->stabilizedHeight<96){
		VENC_LOG(ERR,("%s invalid stabilization size(%d,%d)\n",	\
								MODULE_STAB,excfg->stabilizedWidth,excfg->stabilizedHeight));
		return 0;
	}
	if(((excfg->stabilizedWidth & 3) != 0) ||
					((excfg->stabilizedHeight & 3) != 0)){
		VENC_LOG(ERR,("%s not aligned stabilization size(%d,%d)\n",	\
								MODULE_STAB,excfg->stabilizedWidth,excfg->stabilizedHeight));
		return 0;
	}
	if((excfg->inputWidth < (excfg->stabilizedWidth + 8)) ||
					(excfg->inputHeight < (excfg->stabilizedHeight + 8))){
		VENC_LOG(ERR,("%s the stabilizaton is 8 pixels smaller than input size !\n",MODULE_STAB));
		return 0;
	}

	if((excfg->stride < excfg->inputWidth) || (excfg->stride & 7) != 0){
		VENC_LOG(ERR,("%s invalid stride(%d)\n",MODULE_STAB,excfg->stride));
		return 0;
	}	
	if(excfg->format > VIDEOSTB_BGR101010){
		VENC_LOG(ERR,("%s invalid source format(%d)\n",MODULE_STAB,excfg->format));
		return 0;
	}

	stabParam.format = excfg->format;
	stabParam.inputWidth = excfg->inputWidth;
	stabParam.inputHeight = excfg->inputHeight;
	stabParam.stride = excfg->stride;
	stabParam.stabilizedWidth = excfg->stabilizedWidth;
	stabParam.stabilizedHeight = excfg->stabilizedHeight;
	

	//==========================================================================	
	ret = VideoStbInit(stabinst, &stabParam);

	if(ret != VIDEOSTB_OK){
		VENC_LOG(ERR,("%s VideoStbInit() failed!,return %d\n",MODULE_STAB,ret));
		return 0;
	}
	
	return 1;
}

/*
func:
params:
return:
*/
void camstab_free_buffer(VencLinearMem *referbuffer)
{
	if(referbuffer !=NULL && referbuffer->vBuffer != NULL ){
		free( referbuffer->vBuffer);
	}
}

/*
func:
params:
return:
*/
int camstab_allocate_buffer(VencLinearMem *buf,uint32_t frameSize)
{

	buf->vBuffer = (void *)malloc( frameSize);
	buf->bBuffer = (uint32_t )(unsigned long)buf->vBuffer;
	buf->size = frameSize;
	buf->offset = 0 ;
	if(buf->vBuffer ==NULL ){
		VENC_LOG(ERR,("malloc stab buffer or reference buffer failed!\n"));
		return -1;
	}
	return 1;
}

/*
func:
params:
return:
*/
int camstab_read_pic(FILE *file,VencLinearMem *buffer,uint32_t imgSize ,uint32_t frameSize,uint32_t index)
{
	VENC_LOG(INFO ,("read pic ->%d  %d  %d %d   %d\n",index,frameSize,imgSize,file->ssize,file->offset));
	if(fseek(file, imgSize*index, SEEK_SET) !=0){
		VENC_LOG(ERR,("%s can not seek the input file to the %d pistion!\n",MODULE_STAB,imgSize*index));
		return 0;
	}
	int32_t readSize =	fread(buffer->vBuffer,1,frameSize,file);
	if(readSize != frameSize)
	{
		VENC_LOG(INFO,("read frame error -> %d  %d \n",readSize,frameSize));
		return -1;
	}
	return readSize;
}


/*
func:
params:
return:
*/
#define STAB_RESULT_BUF_SIZE  64
int camstab_encode(CamStabTbConfig *excfg)
{
	VideoStbInst videoStab = {0} ;
	VideoStbApiVersion apiVer = {0} ;
	VideoStbBuild csBuild = {0} ;
	VideoStbResult outResult = {0} ;
	VencLinearMem frameBuf_1 = {0} ;	
	VencLinearMem frameBuf_2 = {0} ;
	CamStabTbConfig excfgbak = {0} ;
	VencLinearMem *curFrame= &frameBuf_1;
	VencLinearMem *nextFrame= &frameBuf_2;
	VencLinearMem outputBuf = {0};
	VideoStbRet ret = 0;
	uint32_t frameBusAddress =0;
	uint32_t nextFrameBusAddress = 0;
	uint32_t frameSize = 0;
	int32_t imgSize = 0;
	int32_t totalFrameCnt = 0;
	int32_t frameCnt = 0;
	int32_t stabError =0;
	FILE *inputFile =NULL;
	FILE *outputFile =NULL;
	char resultBuf[STAB_RESULT_BUF_SIZE]; 
	VENC_LOG(INFO,("%s camstab_encode()+++\n",MODULE_STAB));


	//=	apiVer = VideoStbGetApiVersion(); 
	csBuild = VideoStbGetBuild(); 

	VENC_LOG(INFO,("VideoStb API version %d.%d\n",apiVer.major, apiVer.minor));
	VENC_LOG(INFO,("HW ID: 0x%08x\t SW Build: %u.%u.%u\n",	\
				csBuild.hwBuild,csBuild.swBuild/1000000,(csBuild.swBuild/1000)%1000,csBuild.swBuild%1000));

	memcpy((void *)&excfgbak,(void *)excfg,sizeof(CamStabTbConfig));
	inputFile = fopen(excfg->inputFile,"rb");
	if(inputFile ==NULL){
		VENC_LOG(ERR,("can not open the camera stabilization input file %s\n",excfg->inputFile));
		return 0;
	}
	if(strlen(excfg->outputFile) <= 0){
		VENC_LOG(INFO,("output file name error\n" ));
	}
	outputFile = fopen(excfg->outputFile,"wb");
	if(outputFile ==NULL){
		VENC_LOG(ERR,("can not open the camera stabilization input file %s\n",excfg->inputFile));
		return 0;
	}

	if(!camstab_open(&videoStab,excfg)){
		VENC_LOG(ERR,("%s camstab_open() failed!",MODULE_STAB));
		fclose(inputFile);
		return 0;
	}

	switch(excfg->format){
		case VIDEOSTB_YUV420_PLANAR :
		case VIDEOSTB_YUV420_SEMIPLANAR  :
			frameSize = excfg->inputWidth* excfg->inputHeight;
			imgSize =  frameSize *3/2;
			break;
		case VIDEOSTB_YUV422_INTERLEAVED_YUYV:
		case VIDEOSTB_YUV422_INTERLEAVED_UYVY:
			frameSize = excfg->inputWidth* excfg->inputHeight;
			imgSize =  frameSize *3;
			break;
		case VIDEOSTB_RGB565 :
		case VIDEOSTB_BGR565 : 
		case VIDEOSTB_RGB555 :  
		case VIDEOSTB_BGR555 :   
			frameSize = excfg->inputWidth* excfg->inputHeight * 2;
			imgSize =  frameSize ;
			break;
		case VIDEOSTB_RGB444 :    
		case VIDEOSTB_BGR444 :     
			frameSize = excfg->inputWidth* excfg->inputHeight * 3;
			imgSize =  frameSize ;
			break;
		case VIDEOSTB_RGB888 :     
		case VIDEOSTB_BGR888 :      
			frameSize = excfg->inputWidth* excfg->inputHeight  * 2;
			imgSize =  frameSize ;
			break;
		case VIDEOSTB_RGB101010 :      
		case VIDEOSTB_BGR101010 :        
			frameSize = excfg->inputWidth* excfg->inputHeight * 2;
			imgSize =  frameSize ;
			break;
		default :
			VENC_LOG(INFO,("input format error -> %d\n",excfg->format));
			return -1;
			break;

	}
	if(camstab_allocate_buffer(curFrame,frameSize) < 0){
		VENC_LOG(ERR,("camstab_allocate cur frame failed!\n"));
		goto ENCODE_FAIL;
	}
	if(camstab_allocate_buffer(nextFrame,frameSize) < 0){
		VENC_LOG(ERR,("camstab_allocate next frame failed!\n"));
		goto ENCODE_FAIL;
	}
	uint32_t outputSize = excfg->outputSize ==0 ? DEFAULT_STAB_OUTPUT_SIZE : excfg->outputSize;
	VENC_LOG(INFO,("output buf size -> %d\n",outputSize));
	if(camstab_allocate_buffer(&outputBuf,outputSize) < 0){
		VENC_LOG(ERR,("camstab_allocate_output buffer failed!\n"));
		goto ENCODE_FAIL;
	}
	memset(outputBuf.vBuffer,0,outputBuf.size);
	

	fseek(inputFile, 0L, SEEK_END);
	totalFrameCnt = ftell(inputFile)/imgSize;
	fseek(inputFile,0L,SEEK_SET); 
	//==========================================================================	
	VENC_LOG(INFO,("%s total %d frame will be stabilized!\n",MODULE_STAB,totalFrameCnt-1));
	frameCnt = 0;
	if(camstab_read_pic(inputFile,curFrame,imgSize,frameSize,frameCnt++) < 0){
		VENC_LOG(ERR,("%s camstab_read_pic() failed!\n",MODULE_STAB));
		goto ENCODE_FAIL;
	}
	while(frameCnt<totalFrameCnt){
		VENC_LOG(INFO,("stab frame msg -> %d  %d \n",totalFrameCnt,frameCnt));
		if(camstab_read_pic(inputFile,nextFrame,imgSize,frameSize,frameCnt) < 0){
			VENC_LOG(ERR,("%s camstab_read_pic() failed!\n",MODULE_STAB));
			goto ENCODE_FAIL;
		}
		frameBusAddress = curFrame->bBuffer;
		nextFrameBusAddress = nextFrame->bBuffer;
		
		ret = VideoStbStabilize(videoStab, &outResult, frameBusAddress,nextFrameBusAddress);

		if(ret != VIDEOSTB_OK){
			VENC_LOG(ERR,("%s %d frame stabilized failed!\n",MODULE_STAB,frameCnt));
			stabError++;
		}
		memset(resultBuf,0,STAB_RESULT_BUF_SIZE);
		sprintf(resultBuf,"%d -> %d %d\n",frameCnt,outResult.stabOffsetX,outResult.stabOffsetY);
		VENC_LOG(INFO,("%s",resultBuf ));
		write_to_venc_linear_mem(&outputBuf,(int8_t *)resultBuf,strlen(resultBuf),0);
		outResult.stabOffsetX = 0;
		outResult.stabOffsetY = 0;
		if(frameCnt>MAXENCODEDPICS){
			VENC_LOG(INFO,("%s get enough videostabilization test example!\n",MODULE_STAB));
			break;
		}
		void *temp =  curFrame;
		curFrame = nextFrame;
		nextFrame = temp;
		frameCnt++;
	}

	if(stabError !=0){
		VENC_LOG(ERR,("%s the %s file failed to do stabilization\n",MODULE_STAB,excfg->outputFile));
		goto ENCODE_FAIL;
	}
	fclose(inputFile);
	if(dump_venc_linear_mem_to_file(outputFile,&outputBuf,excfg->outputCrc32) < 0)
		goto ENCODE_FAIL;
	if(outputFile)
		fclose(outputFile);
	camstab_close(videoStab);
	camstab_free_buffer(curFrame);
	camstab_free_buffer(nextFrame);
	camstab_free_buffer(&outputBuf);
	memcpy((void *)excfg,(void *)&excfgbak,sizeof(CamStabTbConfig));

	//==========================================================================

	VENC_LOG(INFO,("stab test case run over -> %s\n",excfg->caseName));
	return 1;
ENCODE_FAIL:
	if(inputFile)
		fclose(inputFile);
	if(outputFile)
		fclose(outputFile);
	camstab_close(videoStab);
	if(frameBuf_1.vBuffer)
		camstab_free_buffer(&frameBuf_1);
	if(frameBuf_2.vBuffer)
		camstab_free_buffer(&frameBuf_2);
	if(outputBuf.vBuffer)
		camstab_free_buffer(&outputBuf);
	//memcpy((void *)excfg,(void *)&excfgbak,sizeof(CamStabTbConfig));
	return 0;
}


void  print_camstab_enc_config(CamStabTbConfig *cfg){
#if 0
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

	printf("\n\ncfg camstab Enc Config############################\n");
	printf("stream type --> %d\n",cfg->exencconfig.streamType);
	printf("level --> %d\n",cfg->exencconfig.level);
	printf("width --> %d\n",cfg->exencconfig.width);
	printf("height --> %d\n",cfg->exencconfig.height);
	printf("frameRateNum --> %d\n",cfg->exencconfig.frameRateNum);
	printf("frameRateDenom --> %d\n",cfg->exencconfig.frameRateDenom);
	printf("complexityLevel --> %d\n",cfg->exencconfig.complexityLevel);
	printf("\n\ncfg camstab Coding Ctrl ############################\n");
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

	printf("\n\ncfg camstab Rate Ctrl ############################\n");
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



	printf("\n\ncfg camstab PP ############################\n");
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
int32_t check_deal_camstab_enc_config_data(CamStabTbConfig *cfg){
// should add more pre check actions	
	return 0;
//	cfg->excfg.pCom = cfg->inputComment;
//	cfg->excfg.comLength = strlen(cfg->excfg.pCom);	
//	return 0;
}
void camstab_encode_set_default_config(CamStabTbConfig *cfg);
int32_t venc_video_stable_entry(int argc,char *argv[]){
	int32_t ret = 0;	
	if (argc < 3){
		VENC_LOG(INFO,("venc camstab tb argc must >= 3\n"));
		return -1;
	}
	CamStabTbConfig camstab_enc_cfg = {0};
	if (strncmp(argv[2],"def",3) == 0){
		camstab_encode_set_default_config(&camstab_enc_cfg);
	}
	else {
		ret = load_camstab_enocode_para_from_file(argv[2],&camstab_enc_cfg);
		if(ret < 0){
			goto Fail;
		}
		check_deal_camstab_enc_config_data(&camstab_enc_cfg);
	}
	print_camstab_enc_config(&camstab_enc_cfg);
	ret = camstab_encode(&camstab_enc_cfg); 
	if(ret < 0)
		goto Fail;
	return TB_RET_MANUAL;
Fail:
	LOG_ERR("camstab venc case error -> %s\n",camstab_enc_cfg.caseName);	
	return TB_RET_FAIL;
}
int32_t load_camstab_enocode_para_from_file(char *filename,CamStabTbConfig *cfg){
	para_struct_t	para[] = {
		{"Case_Name", 		char_p,1, cfg->caseName }, 			//Case_Name
		{"Input_File", 		char_p,1, cfg->inputFile }, 		//Input_File
		{"Output_File", 	char_p,1, cfg->outputFile  }, 		//Output_File
		{"Output_Size", 	u32_p,1, &cfg->outputSize  },		//Input_Comment
		{"Output_Crc32", 	u32_p,1, &cfg->outputCrc32  },		//Input_Comment
		//camstab part
		{"Input_Format", 	u32_p, 1, &cfg->format  }, //Input_Width
		{"Input_Width", 	u32_p, 1, &cfg->inputWidth  }, //Input_Width
		{"Input_Height", 	u32_p, 1, &cfg->inputHeight  }, //Input_Width
		{"Stride", 			u32_p, 1, &cfg->stride  }, //Input_Width
		{"StabilizedWidth", u32_p, 1, &cfg->stabilizedWidth  }, //Input_Width
		{"StabilizedHeight",u32_p, 1, &cfg->stabilizedHeight  }, //Input_Width
	};
	int32_t para_num = sizeof(para) /sizeof(para_struct_t);
    return 0;
	//return load_para_from_cfg_file((signed char*)filename,para,para_num);
}
void camstab_encode_set_default_config(CamStabTbConfig *cfg){
	CamStabTbConfig default_cfg = {
		"CamStab Default",
		"venc/stab/camstab_w640_y480_yuv420sp.yuv"	,
		"venc/stab/CamStabDefault_crop_result.txt",
		0, // outputSize
		0x6c0de58d,// outputCrc32
		640,
		480,
		640,
		624,
		468,
		VIDEOSTB_YUV420_SEMIPLANAR
	};
	memcpy( cfg,&default_cfg ,sizeof(CamStabTbConfig));
}

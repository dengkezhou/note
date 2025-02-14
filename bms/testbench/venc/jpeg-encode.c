#include <jpeg-encode.h>
#include <venc-common.h>
#include <para.h>
#include <crc32.h>
char qTableLuma[256];
char qTableChroma[256];
static FILE * ftime =NULL;
/* An example of user defined quantization table */
const u8 jpeg_qtable[64] = {1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1};
int venc_jpeg_write_file(FILE *file,void *buffer,unsigned int size,int endian,uint32_t crc32)
{
#if 1
	unsigned int i = 0, words = (size + 3) / 4;
	unsigned int *strmbuf = (unsigned int *)buffer; 
	if(endian ==1){
		while(words){
			unsigned int val = strmbuf[i];
			unsigned int tmp =0;

			tmp |= (val & 0xFF) << 24; 
			tmp |= (val & 0xFF00) << 8;
			tmp |= (val & 0xFF0000) >> 8;
			tmp |= (val & 0xFF000000) >> 24;
			strmbuf[i] = tmp;
			words--; 
			i++;
		}
	}
	
	VENC_LOG(INFO,("JPEG Writing stream address %p (%d bytes)... \n",strmbuf, size));
	fwrite(strmbuf, 1, size, file);
	//==========================================================================	
	//==========================================================================
	if(crc32) {
		uint32_t cal = lib_crc32_le(0, buffer, size);
		if (crc32 == cal){
			VENC_LOG(INFO,("crc result passed -> %x  %x \n",crc32 ,cal));
		}
		else{
			VENC_LOG(INFO,("crc result failed -> %x  %x \n",crc32 ,cal));
		}
	}
	else {
		VENC_LOG(INFO,("not contain crc info ,not do crc32\n"));
	}
#endif
	return 1;
}
/*
func:use the external jpeg encode context to initalized a jpeg encode instance
params:instAddr->decode instance address;cfg->the jpegencconfig context which will be set
		excfg->the external application test example's jpegenc configuration
return:
*/
int jpeg_open(JpegEncInst * instAddr,JpegEncCfg *cfg,JpegEncConfig *excfg)
{
	JpegEncRet ret;
	JpegEncCfg *externalcfg;
	//FILE *fileCom =NULL;
	//char wholefilename[256];
	unsigned int width,height;
	int i,j;
	
	if(excfg==NULL || instAddr ==NULL || cfg ==NULL){
		VENC_LOG(ERR,(" params is null!\n"));
		return 0;
	}
	externalcfg = &excfg->excfg;
	//do some check of the configuration ,if you know clearly every setting's means, you can skip the checking of cource
	//acctualy in our 7280 encode lib,the decode wrap layer will also do that checking 
#if 1
	VENC_LOG(INFO,("external configuration list:\n"));
	VENC_LOG(INFO,("inputwidth = %d\n",externalcfg->inputWidth));
	VENC_LOG(INFO,("inputheight = %d\n",externalcfg->inputHeight));
	VENC_LOG(INFO,("xOffset = %d\n",externalcfg->xOffset));
	VENC_LOG(INFO,("yOffset = %d\n",externalcfg->yOffset));
	VENC_LOG(INFO,("codingWidth = %d\n",externalcfg->codingWidth));
	VENC_LOG(INFO,("codingHeight = %d\n",externalcfg->codingHeight));
	VENC_LOG(INFO,("restartInterval = %d\n",externalcfg->restartInterval));
	VENC_LOG(INFO,("qLevel = %d\n",externalcfg->qLevel));
	VENC_LOG(INFO,("qTableLuma = 0x%x\n",externalcfg->qTableLuma));
	VENC_LOG(INFO,("qTableChroma = 0x%x\n",externalcfg->qTableChroma));
	VENC_LOG(INFO,("frameType = %d\n",externalcfg->frameType));
	VENC_LOG(INFO,("colorConversion.type = %d\n",externalcfg->colorConversion.type));
	VENC_LOG(INFO,("colorConversion.coeffA = %d\n",externalcfg->colorConversion.coeffA));
	VENC_LOG(INFO,("colorConversion.coeffB = %d\n",externalcfg->colorConversion.coeffB));
	VENC_LOG(INFO,("colorConversion.coeffC = %d\n",externalcfg->colorConversion.coeffC));
	VENC_LOG(INFO,("colorConversion.coeffE = %d\n",externalcfg->colorConversion.coeffE));
	VENC_LOG(INFO,("colorConversion.coeffF = %d\n",externalcfg->colorConversion.coeffF));
	VENC_LOG(INFO,("rotation = %d\n",externalcfg->rotation));
	VENC_LOG(INFO,("codingType = %d\n",externalcfg->codingType));
	VENC_LOG(INFO,("codingMode = %d\n",externalcfg->codingMode));
	VENC_LOG(INFO,("unitsType = %d\n",externalcfg->unitsType));
	VENC_LOG(INFO,("markerType = %d\n",externalcfg->markerType));
	VENC_LOG(INFO,("xDensity = %d\n",externalcfg->xDensity));
	VENC_LOG(INFO,("yDensity = %d\n",externalcfg->yDensity));
	VENC_LOG(INFO,("comLength = %d\n",externalcfg->comLength));
	VENC_LOG(INFO,("pCom = %d\n",externalcfg->pCom));
#endif
	if(externalcfg->codingWidth ==0 || externalcfg->codingHeight==0){
		externalcfg->codingWidth = externalcfg->inputWidth - externalcfg->xOffset;
		externalcfg->codingHeight = externalcfg->inputHeight - externalcfg->yOffset;

		externalcfg->codingWidth &= ~0x03;
		externalcfg->codingHeight &= ~0x01;

		VENC_LOG(INFO,("coding width = %d,coding height = %d\n",	\
			externalcfg->codingWidth,externalcfg->codingHeight ));
	}
	//simple check
	//inputwidth and height checking 
	if(externalcfg->inputWidth&15 || externalcfg->inputWidth>8192 || externalcfg->inputHeight>8192 ||
					externalcfg->inputWidth<96 || externalcfg->inputHeight<32 || externalcfg->inputHeight&1){
		VENC_LOG(ERR,("input size is too small or too big\n"));
		return 0;
	}
	//input cropping width and height checking
	if(externalcfg->codingWidth>511 * 16 || externalcfg->codingWidth<96 || externalcfg->codingHeight>511 * 16 ||
					externalcfg->codingHeight<32 || externalcfg->codingWidth&3 || externalcfg->codingHeight&1 ||
					((externalcfg->codingWidth + 15) >> 4)*((externalcfg->codingHeight + 15) >> 4) > 261121 ||
					externalcfg->inputWidth < ((externalcfg->codingWidth + 15) & (~15))){
		VENC_LOG(ERR,("input coding size is too small or too big\n"));
		return 0;
	}
	//qlevel checking
	if(externalcfg->qLevel>10){
		VENC_LOG(ERR,("invalid qlevel setting!\n"));
		return 0;
	}
	if(externalcfg->qLevel == 10){
		if(externalcfg->qTableLuma==NULL || externalcfg->qTableChroma ==NULL){
			VENC_LOG(WARN,("TableLuma or TableChroma use defaul twhen use USER_DEFINE_QLEVEL mode!\n"));
			externalcfg->qTableLuma = jpeg_qtable;
			externalcfg->qTableChroma = jpeg_qtable;
		}
		VENC_LOG(INFO,("user define qTableLuma \t"));
		for(i=0;i<64;i++){
			VENC_LOG(INFO,("%d ",externalcfg->qTableLuma[i]));
		}
		VENC_LOG(INFO,("\n%suser define qTableChroma \t"));
		for(j=0;j<64;j++){
			VENC_LOG(INFO,("%d ",externalcfg->qTableChroma[j]));
		}
		VENC_LOG(INFO,("\n"));

	}else{
		if(externalcfg->qTableLuma !=NULL || externalcfg->qTableChroma !=NULL){
			VENC_LOG(ERR,("can not set qTableLuma or qTableChroma if not in USER_DEFINE_QLEVEL mode!\n"));
			return 0;
		}
	}

	//frameType checking
	switch(externalcfg->frameType){
		case JPEGENC_YUV420_PLANAR :
		case JPEGENC_YUV420_SEMIPLANAR :
		case JPEGENC_YUV422_INTERLEAVED_YUYV:
		case JPEGENC_YUV422_INTERLEAVED_UYVY :
		case JPEGENC_RGB565 :
		case JPEGENC_BGR565:
		case JPEGENC_RGB555:
		case JPEGENC_BGR555:
		case JPEGENC_RGB444:
		case JPEGENC_BGR444:
		case JPEGENC_RGB888:
		case JPEGENC_BGR888:
		case JPEGENC_RGB101010:
		case JPEGENC_BGR101010:
			break;
		default :
			VENC_LOG(ERR,("invalid frame type!\n"));
			return 0;
	}
#if 0
	if(externalcfg->frameType != JPEGENC_YUV420_PLANAR &&
					externalcfg->frameType != JPEGENC_YUV420_SEMIPLANAR&&
					externalcfg->frameType != JPEGENC_YUV422_INTERLEAVED_YUYV&&
					externalcfg->frameType != JPEGENC_YUV422_INTERLEAVED_UYVY&&
					externalcfg->frameType != JPEGENC_RGB565&&
					externalcfg->frameType != JPEGENC_BGR565&&
					externalcfg->frameType != JPEGENC_RGB555&&
					externalcfg->frameType != JPEGENC_BGR555&&
					externalcfg->frameType != JPEGENC_RGB444&&
					externalcfg->frameType != JPEGENC_BGR444&&
					externalcfg->frameType != JPEGENC_RGB888&&
					externalcfg->frameType != JPEGENC_BGR888&&
					externalcfg->frameType != JPEGENC_RGB101010&&
					externalcfg->frameType != JPEGENC_BGR101010){
		VENC_LOG(ERR,("invalid frame type!\n"));
		return 0;
	}
#endif

	//rotation checking
	switch(externalcfg->rotation){
		case JPEGENC_ROTATE_0:
		case JPEGENC_ROTATE_90R:
		case JPEGENC_ROTATE_90L:
			break;
		default :
			VENC_LOG(ERR,("invalid rotation type!\n"));
			return 0;
	}
#if 0
	if(externalcfg->rotation != JPEGENC_ROTATE_0 &&
					externalcfg->rotation != JPEGENC_ROTATE_90R &&
					externalcfg->rotation != JPEGENC_ROTATE_90L){
		VENC_LOG(ERR,("invalid rotation type!\n"));
		return 0;
	}
#endif
	//codingType checking
	if(externalcfg->codingType != JPEGENC_WHOLE_FRAME &&
					externalcfg->codingType != JPEGENC_SLICED_FRAME){
		VENC_LOG(ERR,("invalid codingType !\n"));
		return 0;
	}

	//codingMode checking
	if(externalcfg->codingMode != JPEGENC_420_MODE &&
					externalcfg->codingMode  != JPEGENC_422_MODE){
		VENC_LOG(ERR,("invalid coding mode!\n"));
		return 0;
	}
	//unitsType checking
	if(externalcfg->unitsType != JPEGENC_NO_UNITS &&
					externalcfg->unitsType != JPEGENC_DOTS_PER_INCH &&
					externalcfg->unitsType != JPEGENC_DOTS_PER_CM){
		
		VENC_LOG(ERR,("invalid unitsType!\n"));
		return 0;
	}
	//Xdensity and Ydensity checking
	if(externalcfg->xDensity > 0xFFFFU  ||
					externalcfg->yDensity>0xFFFFU){
		VENC_LOG(ERR,("invalid Xdensity and Ydensity\n"));
		return 0;
	}

	//makertype checking
	if(externalcfg->markerType != JPEGENC_SINGLE_MARKER &&
					externalcfg->markerType != JPEGENC_MULTI_MARKER){
		VENC_LOG(ERR,("invalid markerType!\n"));
		return 0;
	}
	//comment data checking
	if(externalcfg->comLength >0xFFFDU){
		VENC_LOG(ERR,("invalid comment data!\n"));
		return 0;
	}

	//blend together cheching
	width = externalcfg->codingWidth;
	height = externalcfg->codingHeight;
	if(externalcfg->rotation){
		unsigned int tmp;
		tmp = width;
		width = height;
		height = tmp;
	}
	if(externalcfg->xOffset  + width>externalcfg->inputWidth){
		VENC_LOG(ERR,("horizonal out of range!\n"));
		return 0;
	}
	if(externalcfg->yOffset+height >externalcfg->inputHeight){
		VENC_LOG(ERR,("vertical direction out of range!\n"));
		return 0;
	}
	
	if(externalcfg->codingType == JPEGENC_SLICED_FRAME){
		if(externalcfg->rotation != JPEGENC_ROTATE_0){
			VENC_LOG(ERR,("sliced_frame coding type can not support rotation!\n"));
			return 0;
		}
		if(externalcfg->restartInterval == 0){
			int max = 0;
			max = externalcfg->codingWidth/16 > 1048560/externalcfg->codingWidth?1048560/externalcfg->codingWidth:externalcfg->codingWidth/16;
			externalcfg->restartInterval = (u32)venc_get_random_size(max,1);
		}
		if((externalcfg->yOffset % (externalcfg->restartInterval * 16)) != 0){
			VENC_LOG(ERR,("yOffset not valid in sliced frame coding mode!\n"));
			externalcfg->yOffset = 0;
		}
	}
	
	memcpy((void *)cfg,(void *)externalcfg,sizeof(JpegEncCfg));
	cfg->comLength = strlen(excfg->inputComment);
	cfg->pCom = (unsigned char *)excfg->inputComment;
	VENC_LOG(INFO,("comment info -> %d  ->%s  0x%X\n",cfg->comLength,cfg->pCom,cfg->pCom));
#if 0
	if(cfg->comLength){
		strcpy(wholefilename,JPEG_ENCODE_INPUT_FILE_FOLDER);
		strcat(wholefilename,excfg->inputComment);
		fileCom = fopen(wholefilename, "rb");
		if(fileCom !=NULL){
			VENC_LOG(ERR,("can not open comment head file!\n"));
			free( (void *)(cfg->pCom));
			cfg->pCom =NULL;
		}
		fseek(fileCom, 0L, SEEK_END);
		cfg->comLength = ftell(fileCom); 
		//self malloc1
		cfg->pCom = (void *)malloc( cfg->comLength);
		if(cfg->pCom==NULL){
			VENC_LOG(ERR,("can not malloc pCom!\n"));
			return 0;
		}
		fseek(fileCom,0L,SEEK_SET);

		fread((char  *)(cfg->pCom), 1, cfg->comLength, fileCom);
		fclose(fileCom);

		//==========================================================================	
	}
#endif

	//==========================================================================	
	ret = JpegEncInit(cfg,instAddr);	
	if(ret != JPEGENC_OK){
		VENC_LOG(ERR,("JpegEncInit() failed!,return %d\n",ret));
		return 0;
	}
	return 1;
}


/*
func:use the external thumbnail configuration to config our jpeg encode instance's thumbnail if neccessary
params:instAddr->jpeg encode instance address
		pJpegThumb->the thumbnail encode configuration context which will be set to the encoder
		excfg->external application's configuraton context
return: 0,fail;
		1,success
*/
int jpeg_set_thumbnail(JpegEncInst *instAddr,JpegEncThumb *pJpegThumb,JpegEncConfig *excfg)
{
	FILE *fileThumb =NULL;
	void *p = NULL;
	unsigned int  dataLength;
	JpegEncThumb *exthumbcfg; 
	JpegEncRet ret;
	if(pJpegThumb==NULL || excfg==NULL){
		VENC_LOG(ERR,("params is null!\n"));
		goto Fail;
	}
	exthumbcfg = &excfg->exthumbcfg; 
	uint32_t len = strlen(excfg->inputThumbnail);
	if(len <= 0){
		VENC_LOG(INFO,("thumbnail info not ok,do not set thumbnail!\n"));
		return 1;
	}
	//do simple checking, if you are familiar with the checking rules,you can pass the task to 8170 decode lib
	if(exthumbcfg->width<16){
		VENC_LOG(ERR,("invalid thumb width,smaller than 16\n"));
		goto Fail;
	}
	if(exthumbcfg->height<16){
		VENC_LOG(ERR,("invalid thumb height,smaller than 16\n"));
		goto Fail;
	}

	fileThumb = fopen(excfg->inputThumbnail, "rb");
	if(fileThumb ==NULL){
		VENC_LOG(ERR,("fopen thumbnail data file failed!\n"));
		goto Fail;
	}
	fseek(fileThumb,0L,SEEK_END);
	exthumbcfg->dataLength = ftell(fileThumb);
	VENC_LOG(INFO,("thumbnail file size is %d\n",exthumbcfg->dataLength));
	fseek(fileThumb,0L,SEEK_SET);

	switch(exthumbcfg->format){
		case JPEGENC_THUMB_JPEG:
				dataLength = ((1<<16) - 1) - 8; 
				if(exthumbcfg->dataLength > dataLength){
					VENC_LOG(ERR,("invalid thumbnail data length!\n"));
					goto Fail;
				}
				break;
		case JPEGENC_THUMB_PALETTE_RGB8:
				dataLength = 3*256 + (exthumbcfg->width*exthumbcfg->height);
				if(dataLength > (((1<<16) - 1) - 10) ||
								exthumbcfg->dataLength != dataLength){
					VENC_LOG(ERR,("invalid thumbnail data length !\n"));
					goto Fail;
				}
				break;
		case JPEGENC_THUMB_RGB24:
				dataLength = (3*exthumbcfg->width*exthumbcfg->height);
				if(dataLength > (((1<<16) - 1) - 10) ||
								exthumbcfg->dataLength != dataLength){
					VENC_LOG(ERR,("invalid thumbnail data length !\n"));
					goto Fail;
				}
				break;
		default:
				VENC_LOG(ERR,("invalid thumbnail format!\n"));
				goto Fail;
	}


	memcpy((void *)pJpegThumb,(void *)exthumbcfg,sizeof(JpegEncThumb));
	//self malloc2
	pJpegThumb->data = (void *)malloc( pJpegThumb->dataLength);
	p = (void *)malloc( pJpegThumb->dataLength);
	if(p==NULL){
		VENC_LOG(ERR,("malloc pJpegThumb->data failed!\n"));
		goto Fail;
	}
	printf("thumbnail ddr-> 0x%X\n",p);
	uint32_t readsize = fread(p,1,pJpegThumb->dataLength,fileThumb);
	if(readsize !=  pJpegThumb->dataLength){
		VENC_LOG(INFO,("read thumbnail len error ->%s\n",readsize,pJpegThumb->dataLength));
		goto Fail;
	}
	pJpegThumb->data = p;
	fclose(fileThumb);
	fileThumb = NULL;
	//==========================================================================	
	//==========================================================================

	VENC_LOG(INFO,("\n%s external thumbnail configuration list:\n\t"));
	VENC_LOG(INFO,("thumb format is %d\n",exthumbcfg->format));
	VENC_LOG(INFO,("thumb width  is %d\n",exthumbcfg->width));
	VENC_LOG(INFO,("thumb height is %d\n",exthumbcfg->height));
	VENC_LOG(INFO,("thumb dataLength is %d\n",exthumbcfg->dataLength));
	VENC_LOG(INFO,("thumb data is 0x%X\n",exthumbcfg->data));
	

	ret = JpegEncSetThumbnail(*instAddr,pJpegThumb);

	if(ret != JPEGENC_OK){
		VENC_LOG(ERR,("JpegEncSetThumbnail() failed,return %d!\n",ret));
		goto Fail;
	}
	return 1;
Fail:
	if(p)
		free(p);
	if(fileThumb)
		fclose(fileThumb);
	return -1;

}

/*
func:allocate input buffer and output buffer according to our configuration
params:
return:
*/
int jpeg_allocate_buffer(VencLinearMem *input,VencLinearMem *output,JpegEncCfg *enccfg,JpegEncThumb *thumbcfg)
{
	int sliceRows =0;
	unsigned int pictureSize = 0;
	unsigned int outbufSize = 0;
	if(input ==NULL || output==NULL || enccfg==NULL || thumbcfg==NULL ){
		VENC_LOG(ERR,("params is null!\n"));
		return 0;
	}

	if(enccfg->codingType ==JPEGENC_SLICED_FRAME){
		sliceRows = enccfg->restartInterval * 16; 
	}else{
		sliceRows = enccfg->inputHeight;
	}

	outbufSize = enccfg->codingWidth * sliceRows * 2 + 100 * 1024;
	if(thumbcfg->dataLength){
		outbufSize += thumbcfg->width * thumbcfg->height;
	}

	if(enccfg->frameType <= JPEGENC_YUV420_SEMIPLANAR){
		pictureSize = enccfg->inputWidth * sliceRows * 3 / 2;
	}else if(enccfg->frameType <= JPEGENC_BGR444){
		pictureSize =  enccfg->inputWidth * sliceRows * 2;
	}else{
		pictureSize = enccfg->inputWidth * sliceRows * 4;
	}
	VENC_LOG(INFO,("sliceRows=%d,outbufSize=%d,pictureSize=%d\n",sliceRows,outbufSize,pictureSize));
	
	//input->vBuffer=(void *)malloc( pictureSize);
	input->vBuffer = (void *)0x110000000;
	input->bBuffer=(uint32_t )(unsigned long)input->vBuffer;
	input->size = pictureSize;
	
	//output->vBuffer = (void *)malloc( outbufSize);
	output->vBuffer = (void *)0x120000000;
	output->bBuffer = (uint32_t )(unsigned long)output->vBuffer;
	output->size = outbufSize;
	memset(output->vBuffer, 0 , outbufSize);
	if(input->vBuffer==NULL || output->vBuffer==NULL){
		VENC_LOG(ERR,("can  not allocate linear address for input and output buffer!\n"));
		return 0;
	}

	VENC_LOG(INFO,("jpeg_allocate_buffer()---\n"));
	return 1;
}


/*
func:free all the buffer allocated before
params:input->previous allocate input buffer;
		output->previous allocate output buffer ;
		enccfg->jpeg encode configuration context
		thumbcfg->jpeg encode thumbnail configuration context
return:
*/
void jpeg_free_buffer(VencLinearMem *input,VencLinearMem *output,JpegEncCfg *enccfg,JpegEncThumb *thumbcfg)
{
	if(input !=NULL &&input->vBuffer !=NULL){
		free( input->vBuffer);
		memset2((void *)input,sizeof(VencLinearMem),0);
	}
	if(output !=NULL && output->vBuffer !=NULL){
		free( output->vBuffer);
		memset2((void *)output,sizeof(VencLinearMem),0);
	}
	
	if(enccfg->pCom){
		free( (void *)enccfg->pCom);
		enccfg->pCom =NULL;
	}
	if(thumbcfg->data){
		free( (void *)(thumbcfg->data));
		thumbcfg->data =NULL;
	}

	return ;


}


/*
func:close the jpeg encode instance 
params:the instance to be release
return:
*/

void jpeg_close(JpegEncInst *instAddr)
{
	JpegEncRet ret = JPEGENC_ERROR;
#ifdef __VENC_PERFORMANCE_TEST__
#ifdef __VENC_USE_PWM_TIME__
	int timeTake = 0;
#endif
#endif
	if(instAddr ==NULL){
		VENC_LOG(ERR,("params is null!\n"));
		return ;
	}
#ifdef __VENC_PERFORMANCE_TEST__
#ifdef __VENC_USE_PWM_TIME__
	timeTake = sys_get_timer();
#elif defined(__VENC_USE_GPIO_TIME__)
	VENC_GPIO_MAKE_A_PULSE(0);
#endif
#endif

	//==========================================================================	
	ret = JpegEncRelease(*instAddr);

#ifdef __VENC_PERFORMANCE_TEST__
#ifdef __VENC_USE_PWM_TIME__
	VENC_WRITE_TIME(RELEASE,timeTake,JpegEncRelease);
#elif defined(__VENC_USE_GPIO_TIME__)
	VENC_GPIO_MAKE_A_PULSE(0);	
	VENC_HALT(0);
#endif
#endif
	if(ret  != JPEGENC_OK){
		VENC_LOG(ERR,("JpegEncRelease() failed\n"));
	}
	return ;
}

/*
func:read a frame or piece of slice from our input file
params:image->the data pool to be written to 
	   width->the input yuv or rgb picture's width
	   height->the input yuv or rgb picture's height
	   sliceNum->the num of which slice should be the read
	   sliceRows->how much lines the slice take of
	   name->input file name 
	   inputMode->specify the input file's data construction(yuv420P yuv42Sp...)
return:0 ,fail to read data
	1,success and get what we want.
*/
int jpeg_read_pic(char *image,int width,int height,int sliceNum,int sliceRows,char *name ,unsigned int inputMode)
{
	FILE *file = NULL;
	//char wholefilename[256];
	int sliceLumOffset =0;
	int sliceCbOffset =0;
	int sliceCrOffset = 0;
	int sliceLumSize = 0;	/* The size of one slice in bytes */
	int sliceCbSize = 0;
	int sliceCrSize = 0;
	int sliceLumSizeRead = 0;/* The size of the slice to be read */ 
	int sliceCbSizeRead = 0;
	int sliceCrSizeRead =0;

	if(image ==NULL || name ==NULL){
		VENC_LOG(ERR,("params is null!\n"));
		return 0;
	}
		
	if(sliceRows == 0){
		sliceRows = height;
	}
	if(inputMode == 0){
		/* YUV 4:2:0 planar */
		sliceLumSizeRead = sliceLumSize = width * sliceRows;
		sliceCbSizeRead = sliceCbSize = width / 2 * sliceRows / 2;
		sliceCrSizeRead = sliceCrSize = width / 2 * sliceRows / 2;
	}else if(inputMode == 1){
		/* YUV 4:2:0 semiplanar */
		sliceLumSizeRead = sliceLumSize = width * sliceRows;
		sliceCbSizeRead = sliceCbSize = width * sliceRows / 2;
		sliceCrSizeRead = sliceCrSize = 0;
	}else if(inputMode <= 9){
		/* YUYV 4:2:2, this includes both luminance and chrominance */
		sliceLumSizeRead = sliceLumSize = width * sliceRows * 2;
		sliceCbSizeRead = sliceCbSize = 0;
		sliceCrSizeRead = sliceCrSize = 0;

	}else{
		/* 32-bit RGB */
		sliceLumSizeRead = sliceLumSize = width * sliceRows * 4;
		sliceCbSizeRead = sliceCbSize = 0;
		sliceCrSizeRead = sliceCrSize = 0;
	}

	/* The bottom slice may be smaller than the others */
	if(sliceRows * (sliceNum + 1) > height)
	{
		sliceRows = height - sliceRows * sliceNum;
		if(inputMode == 0) {
			sliceLumSizeRead = width * sliceRows;
			sliceCbSizeRead = width / 2 * sliceRows / 2;
			sliceCrSizeRead = width / 2 * sliceRows / 2;
		}else if(inputMode == 1){
			sliceLumSizeRead = width * sliceRows; 
			sliceCbSizeRead = width * sliceRows / 2;
		}else if(inputMode<=9){
			 sliceLumSizeRead = width * sliceRows * 2;
		}else{
			sliceLumSizeRead = width * sliceRows * 4;
		}
	
	}
	/* Offset for slice luma start from start of frame */
	sliceLumOffset = sliceLumSize * sliceNum;
	/* Offset for slice cb start from start of frame */
	if(inputMode <= 1)
		sliceCbOffset = width * height + sliceCbSize * sliceNum;
	/* Offset for slice cr start from start of frame */
	if(inputMode == 0)
			sliceCrOffset = width * height +
					width/2 * height/2 + sliceCrSize * sliceNum;

	VENC_LOG(INFO,("Reading slice %d (%d bytes) from %s... \n",sliceNum,
					sliceLumSizeRead + sliceCbSizeRead + sliceCrSizeRead,name));

#if 0
	file = fopen(name, "rb");
	if(file == NULL){
		VENC_LOG(ERR,("can not open the input file %s !\n",name));
		return 0;
	}
	fseek(file,sliceLumOffset, SEEK_SET);
	fread(image, 1, sliceLumSizeRead, file);
	
	if (sliceCbSizeRead){
		fseek(file, sliceCbOffset, SEEK_SET);
		fread(image + sliceLumSize, 1, sliceCbSizeRead, file);			
	}
	if(sliceCrSizeRead){
		fseek(file, sliceCrOffset, SEEK_SET); 
		fread(image + sliceLumSize + sliceCbSize, 1, sliceCrSizeRead, file); 		
	}

	fclose(file);
#else
	char *p_file = (char*)0x130000000;
	memcpy(image, p_file + sliceLumOffset, sliceLumSizeRead);
	if (sliceCbSizeRead){
		memcpy(image + sliceLumSize, p_file + sliceCbOffset, sliceCbSizeRead);
	}
	if(sliceCrSizeRead){
		memcpy(image + sliceLumSize + sliceCbSize, p_file + sliceCrOffset, sliceCrSizeRead);
	}

	itcs_dcache_flush_range(image, sliceLumSizeRead + sliceCbSizeRead + sliceCrSizeRead);
#endif
	return 1;

}


/*
func:jpeg encode's main process function,should be called by our test case or call by system api when do integration test 
params:JpegEncConfig,jpeg's external config setting,all encode infomation can be got from this structure
return:1,encode success;0,encode failed
*/
extern uint32_t venc0_irq_mode_enable;
extern uint32_t venc0_irq_value ;
extern uint32_t venc0_dmmu_mode_enable ; //0 not use dmmu 1:use dmmu
int jpeg_encode(JpegEncConfig *excfg)
{ 
	JpegEncApiVersion ver ={0};
	JpegEncBuild build ={0};
	JpegEncInst jpeginst ={0};
	JpegEncCfg 	jpegenccfg ={0};
	JpegEncThumb jpegencthumb ={0};
	JpegEncIn	jpegin ={0};
	JpegEncOut	jpegout ={0};
	JpegEncRet ret ={0}; 
	//vdec_buffer mmutbl ={0};
	VencLinearMem inbuffer ={0};
	VencLinearMem outbuffer ={0};
	//char wholefilename[256] ={0};
	JpegEncConfig excfgbak;

	int slice = 0, sliceRows = 0;
	int widthSrc, heightSrc;
	FILE *fout =NULL;
	//save the external configuration
	memcpy((void *)&excfgbak,(void *)excfg,sizeof(JpegEncConfig));
	if(excfg->irqEnable)	
	{
		venc0_irq_mode_enable = 1;
		venc0_irq_value = 0;
	}
	if(excfg->dmmuEnable){
		venc0_dmmu_mode_enable = 1;
		//int32_t ret =  dmmu_enable("venc0");
		printf("enable venc0 dmmu -> %d\n",ret);
	}
	else {
		venc0_dmmu_mode_enable = 0;
	}
	//1,print the hw jpeg version and build configuration
	//==========================================================================	
	ver = JpegEncGetApiVersion();
	build = JpegEncGetBuild();
	VENC_LOG(INFO,("ver.major=%d, ver.minor=%d\n",ver.major, ver.minor)); 
	VENC_LOG(INFO,("build.hwBuild=%d, build.swBuild=%d\n", build.hwBuild, build.swBuild));
	//==========================================================================	

	//2,open jpeg decode instance
	if(!jpeg_open(&jpeginst,&jpegenccfg,excfg)){
		VENC_LOG(ERR,("jpeg_open() failed!\n"));
		return 0;
	}

#if 0 
	//3,set the thumbnail configuration if necessary
	if(jpeg_set_thumbnail(&jpeginst,&jpegencthumb,excfg) < 0){
		VENC_LOG(ERR,("jpeg_thumbnail() failed!\n"));
		goto ERROR_PROCESS;
	}
#endif

	//4,allocate input and output buffer
	if(!jpeg_allocate_buffer(&inbuffer,&outbuffer,&jpegenccfg,&jpegencthumb)){
		VENC_LOG(ERR,("jpeg_allocate_buffer() failed!\n"));
		goto ERROR_PROCESS;
	}

	
	//5,do jpeg encode
	 jpegin.pOutBuf = (u8 *)outbuffer.vBuffer;
	 jpegin.busOutBuf = outbuffer.bBuffer;
	 jpegin.outBufSize = outbuffer.size;
	 jpegin.frameHeader = 1;
	 
	 printf("jpeg in buffer-> 0x%X\n",inbuffer.bBuffer);
	 printf("jpeg out buffer-> 0x%X\n",outbuffer.bBuffer);

#if  0
	 VENC_LOG(INFO,("the output file name is %s\n",excfg->outputFile));
	 printf("the output file name is %s\n",excfg->outputFile);
	 fout = fopen(excfg->outputFile, "wb");
	 if(fout==NULL){
	 	VENC_LOG(ERR,(" failed to create an output file!\n"));
		goto ERROR_PROCESS;
	 }
#endif

	 {
		//==========================================================================	
		ret = JpegEncSetPictureSize(jpeginst, &jpegenccfg);
		if(ret != JPEGENC_OK){
			VENC_LOG(ERR,("JpegEncSetPictureSize() failed!,return %d\n",ret));
			goto ERROR_PROCESS;
		}
		if(jpegenccfg.codingType == JPEGENC_WHOLE_FRAME){
			sliceRows = jpegenccfg.inputHeight;
		}else{
			sliceRows = jpegenccfg.restartInterval * 16; 
		}

		widthSrc = jpegenccfg.inputWidth;
		heightSrc = jpegenccfg.inputHeight;
		if(jpegenccfg.frameType <= JPEGENC_YUV420_SEMIPLANAR){
			 jpegin.busLum = inbuffer.bBuffer;
			 jpegin.busCb = jpegin.busLum + (widthSrc * sliceRows);
			 jpegin.busCr = jpegin.busCb +(((widthSrc + 1) / 2) * ((sliceRows + 1) / 2));

			 jpegin.pLum = (u8 *)inbuffer.vBuffer;
			 jpegin.pCb = jpegin.pLum + (widthSrc * sliceRows);
			 jpegin.pCr = jpegin.pCb + (((widthSrc + 1) / 2) * ((sliceRows + 1) / 2));
		}else{
			jpegin.busLum = inbuffer.bBuffer; 
			jpegin.busCb = jpegin.busLum;
			jpegin.busCr = jpegin.busCb;

			jpegin.pLum = (u8 *)inbuffer.vBuffer;
			jpegin.pCb = jpegin.pLum;
			jpegin.pCr = jpegin.pCb;
		}
		ret = JPEGENC_FRAME_READY;

		//input = excfg->inputFile;
		do{
			if(!jpeg_read_pic((char *)inbuffer.vBuffer,widthSrc,heightSrc,slice,sliceRows,excfg->inputFile,jpegenccfg.frameType))
			{
				VENC_LOG(ERR,(" jpeg_read_pic() failed!--> %s\n",excfg->inputFile));
				goto ERROR_PROCESS;
			}

			//==========================================================================	
			ret = JpegEncEncode(jpeginst, &jpegin, &jpegout);
			VENC_LOG(INFO,("\n"));
			switch(ret){
				case JPEGENC_RESTART_INTERVAL:
					VENC_LOG(INFO,("JPEGENC_RESTART_INTERVAL!,return %d bytes!\n",jpegout.jfifSize));
					if(jpegenccfg.restartInterval ==0){
						VENC_LOG(ERR,("error JPEGENC_RESTART_INTERVAL because we in WHOLE FRAME mode!\n"));
					}
#ifdef __WRITEOUT__
					if(!venc_jpeg_write_file(fout,outbuffer.vBuffer,jpegout.jfifSize,0,excfg->outputCrc32)){
						VENC_LOG(ERR,("could not write jpeg data to outfile %s!\n",excfg->outputFile));
						goto ERROR_PROCESS;
					}
#endif
					slice++;
					break;
				case JPEGENC_FRAME_READY:
					VENC_LOG(INFO,("JPEGENC_FRAME_READY!,return %d bytes!\n",jpegout.jfifSize));
				#if 0
					if(!venc_jpeg_write_file(fout,outbuffer.vBuffer,jpegout.jfifSize,0,excfg->outputCrc32)){
						VENC_LOG(ERR,(" could not write jpeg data to outfile %s!\n",excfg->outputFile));
						goto ERROR_PROCESS;
					}
				#endif
					slice = 0;
					break;
				case JPEGENC_OUTPUT_BUFFER_OVERFLOW:
					VENC_LOG(ERR,("JPEGENC_OUTPUT_BUFFER_OVERFLOW!\n"));
#ifdef __WRITEOUT__
					if(!venc_jpeg_write_file(fout,outbuffer.vBuffer,jpegout.jfifSize,0,excfg->outputCrc32)){
						VENC_LOG(ERR,("could not write jpeg data to outfile %s!\n",excfg->outputFile));
						goto ERROR_PROCESS;
					}
#endif
					break;
				default:
					VENC_LOG(ERR,("jpeg do encode failed!,return %d\n",ret));
					goto ERROR_PROCESS;
			}
		}while(ret == JPEGENC_RESTART_INTERVAL);
	 
	 }

	jpeg_close(&jpeginst);
	if(fout!=NULL)
			fclose(fout);
	//jpeg_free_buffer(&inbuffer,&outbuffer,&jpegenccfg,&jpegencthumb);
	memcpy((void *)excfg,(void *)&excfgbak,sizeof(JpegEncConfig));
	venc0_irq_mode_enable = 0;
	if(venc0_irq_value != 0){
		printf("h1 irq test success\n");
	}
	if(excfg->dmmuEnable){
		//dmmu_disable("venc0");
		printf("disable venc0 dmmu \n");
	}
	return 1;
ERROR_PROCESS:
	jpeg_close(&jpeginst);
	if(fout !=NULL)
		fclose(fout);
	if(ftime)
		fclose(ftime);
	ftime =NULL;

	//jpeg_free_buffer(&inbuffer,&outbuffer,&jpegenccfg,&jpegencthumb);
	memcpy((void *)excfg,(void *)&excfgbak,sizeof(JpegEncConfig));
#ifdef VENC_MMU_ENABLE
	tb_venc_mmu_disable();
	tb_venc_mmu_deinit();
	tb_venc_free_linear_memory(&mmutbl);
#endif
#ifdef __VENC_PERFORMANCE_TEST__
#ifdef __VENC_USE_PWM_TIME__
	sys_stop_timer();
#endif
#endif
	venc0_irq_mode_enable = 0;
	if(venc0_irq_value != 0){
		printf("h1 irq test success\n");
	}
	if(excfg->dmmuEnable){
		//dmmu_disable("venc0");
		printf("disable venc0 dmmu \n");
	}
	return 0;	
}

void  print_jpeg_enc_config(JpegEncConfig *cfg){
	printf("cfg common############################\n");
	printf("Case_Name--> %s\n",cfg->caseName);
	printf("Input File--> %s\n",cfg->inputFile);
	printf("Input Thumbnail--> %s\n",cfg->inputThumbnail);
	//printf("File name--> %s\n",cfg->fileName);
	//printf("Dir--> %s\n",cfg->dir);
	printf("Comment--> %s\n",cfg->inputComment);
	printf("Output File--> %s\n",cfg->outputFile);
	printf("Output File CRC32--> 0x%x\n",cfg->outputCrc32);
	printf("cfg jpeg############################\n");
	printf("input width--> %d\n",cfg->excfg.inputWidth);
	printf("input height--> %d\n",cfg->excfg.inputHeight);
	printf("start x--> %d\n",cfg->excfg.xOffset);
	printf("start y--> %d\n",cfg->excfg.yOffset);
	printf("coding width--> %d\n",cfg->excfg.codingWidth);
	printf("coding height--> %d\n",cfg->excfg.codingHeight);
	printf("rtart interval --> %d\n",cfg->excfg.restartInterval);
	printf("qlevel --> %d\n",cfg->excfg.qLevel);
	printf("qTableChroma --> %s\n",qTableLuma);
	printf("qTableChroma --> %s\n",qTableChroma);
	printf("frame type --> %d\n",cfg->excfg.frameType);
	printf("colorConversion --> %d\n",cfg->excfg.colorConversion.type);
	printf("colorConversion_A --> %d\n",cfg->excfg.colorConversion.coeffA);
	printf("colorConversion_B --> %d\n",cfg->excfg.colorConversion.coeffB);
	printf("colorConversion_C --> %d\n",cfg->excfg.colorConversion.coeffC);
	printf("colorConversion_E --> %d\n",cfg->excfg.colorConversion.coeffE);
	printf("colorConversion_F --> %d\n",cfg->excfg.colorConversion.coeffF);
	printf("rotation --> %d\n",cfg->excfg.rotation);
	printf("codeing type--> %d\n",cfg->excfg.codingType);
	printf("code mode --> %d\n",cfg->excfg.codingMode);
	printf("units type --> %d\n",cfg->excfg.unitsType);
	printf("Marker_Type--> %d\n",cfg->excfg.markerType);
	printf("x density --> %d\n",cfg->excfg.xDensity);
	printf("y density --> %d\n",cfg->excfg.yDensity);
	printf("comment lenght --> %d\n",cfg->excfg.comLength);
	printf("comment --> %s\n",cfg->excfg.pCom);
	printf("cfg thumb############################\n");
	printf("thumbnail format --> %d\n",cfg->exthumbcfg.format);
	printf("thumbnail width --> %d\n",cfg->exthumbcfg.width);
	printf("thumbnail height --> %d\n",cfg->exthumbcfg.height);
	printf("irqEnable --> %d\n",cfg->irqEnable);
	printf("dmmuEnable  --> %d\n",cfg->dmmuEnable);
	printf("cfg over ############################\n");

}
int32_t check_deal_enc_config_data(JpegEncConfig *cfg){
// should add more pre check actions	
	return 0;
	cfg->excfg.comLength = strlen(cfg->inputComment);
	cfg->excfg.pCom = (unsigned char *)cfg->inputComment;
	return 0;
}
void jpeg_encode_set_default_config(JpegEncConfig *cfg);

int32_t venc_jpeg_entry(int argc,char *argv[]){

	venc_module_enable(0);

	int32_t ret = 0;	
	printf("%s  ++++++++++\n",__func__);
	if (argc < 2){
		VENC_LOG(INFO,("venc jpeg tb argc must >= 3\n"));
		return -1;
	}
	JpegEncConfig jpeg_enc_cfg = {0};
	if (strncmp(argv[1],"def",3) == 0){
		jpeg_encode_set_default_config(&jpeg_enc_cfg);
	}
	else {
		ret = load_jpeg_enocode_para_from_file(argv[2],&jpeg_enc_cfg);
		if(ret < 0){
			goto Fail;
		}
		check_deal_enc_config_data(&jpeg_enc_cfg);
	}
	print_jpeg_enc_config(&jpeg_enc_cfg);
	ret = jpeg_encode(&jpeg_enc_cfg); 
	if(ret < 0)
		goto Fail;
	return TB_RET_MANUAL;
Fail:
	LOG_ERR("Jpeg venc case error -> %s\n",jpeg_enc_cfg.caseName);	
	return TB_RET_FAIL;
}
int32_t load_jpeg_enocode_para_from_file(char *filename,JpegEncConfig *cfg){

	memset(qTableLuma,0,256);
	memset(qTableChroma,0,256);
	para_struct_t	para[] = {
		{"Case_Name", 	char_p,1, cfg->caseName }, 			//Case_Name
		{"Input_File", 	char_p,1, cfg->inputFile }, 		//Input_File
		{"Input_Thumbnail", 	char_p,1, cfg->inputThumbnail  },	//Input_Thumbnail
		{"Output_File", 	char_p,1, cfg->outputFile  }, 		//Output_File
		{"Input_Width", 	u32_p, 1, &cfg->excfg.inputWidth  }, //Input_Width
		{"Input_Height", 	u32_p, 1, &cfg->excfg.inputHeight  },//Input_Height
		{"Input_Offset_X", 	u32_p, 1, &cfg->excfg.xOffset  },	//Input_Offset_X
		{"Input_Offset_Y", 	u32_p, 1, &cfg->excfg.yOffset  },	//Input_Offset_Y
		{"Coding_Width", 	u32_p, 1, &cfg->excfg.codingWidth  },	//Coding_Width
		{"Coding_Height", 	u32_p, 1, &cfg->excfg.codingHeight  }, //Coding_Height
		{"Restart_Interval", 	u32_p, 1, &cfg->excfg.restartInterval  }, 
		{"Q_Level", 	u32_p, 1, &cfg->excfg.qLevel  },
		{"Q_Table_Luma", 	char_p, 1, qTableLuma  },
		{"Q_Table_Chroma", 	char_p, 1, qTableChroma  },
		{"Frame_Type", 	u32_p, 1, &cfg->excfg.frameType  },
		{"Color_Conversion_Type", 	u32_p, 1, &cfg->excfg.colorConversion.type  },
		{"Color_Conversion_A", 	u16_p, 1, &cfg->excfg.colorConversion.coeffA  },
		{"Color_Conversion_B", 	u16_p, 1, &cfg->excfg.colorConversion.coeffB  },
		{"Color_Conversion_C", 	u16_p, 1, &cfg->excfg.colorConversion.coeffC  },
		{"Color_Conversion_E", 	u16_p, 1, &cfg->excfg.colorConversion.coeffE  },
		{"Color_Conversion_F", 	u16_p, 1, &cfg->excfg.colorConversion.coeffF  },
		{"Rotation", 	u32_p, 1, &cfg->excfg.rotation  },
		{"Coding_Type", 	u32_p, 1, &cfg->excfg.codingType  },
		{"Coding_Mode", 	u32_p, 1, &cfg->excfg.codingMode  },
		{"Units", 	u32_p, 1, &cfg->excfg.unitsType  },
		{"Marker_Type", 	u32_p, 1, &cfg->excfg.markerType  },
		{"X_Density", 	u32_p, 1, &cfg->excfg.xDensity  },
		{"Y_Density", 	u32_p, 1, &cfg->excfg.yDensity  },
		{"Thumb_Format", 	u32_p, 1, &cfg->exthumbcfg.format  },
		{"Thumb_Width", 	u8_p, 1, &cfg->exthumbcfg.width  },
		{"Thumb_Height", 	u8_p, 1, &cfg->exthumbcfg.height  },
		{"Input_Comment", 	char_p,1, cfg->inputComment  },		//Input_Comment
		{"Output_Crc32", 	u32_p,1, &cfg->outputCrc32  },		//Input_Comment
		{"irqEnable", 	u32_p,1, &cfg->irqEnable  },		//Input_Comment
		{"dmmuEnable", 	u32_p,1, &cfg->dmmuEnable  },		//Input_Comment
	};
	int32_t para_num = sizeof(para) /sizeof(para_struct_t);
	return 0;
    //return load_para_from_cfg_file((signed char*)filename,para,para_num);
}
void jpeg_encode_set_default_config(JpegEncConfig *cfg){
	JpegEncConfig default_cfg = 
	{
		"Default",
		"venc/jpeg/res/640x480_420sp.yuv",//input file path and name
		//"",//thumbnail file name;
		"venc/jpeg/res/96_96_420sp.jpeg",//thumbnail file name;
	//	"File name example",//file name 
	//	"dir example",//dir 
		"Comment_By_Dandan!!", //comment
		"venc/jpeg/Default_640x480_420sp.jpeg", //output file name
		//0xdb1e6196,
		0,
		{
			640,//inputWidth
			480,//inputHeight
			0,//xOffset
			0,//yOffset
			640,//codingWidth
			480,//codingHeight
			0,//restartInterval
			5,//qLevel
			NULL,//qTableLuma
			NULL,//qTableChroma
			JPEGENC_RGB565,//frameType
			{
				JPEGENC_RGBTOYUV_BT601,
				0,//coeffA
				0,//coeffB
				0,//coeffC
				0,//coeffE
				0//coeffF
			},//colorConversion

			JPEGENC_ROTATE_0,
			JPEGENC_WHOLE_FRAME,
			JPEGENC_420_MODE,
			JPEGENC_NO_UNITS,
			JPEGENC_SINGLE_MARKER,
			0,//xDensity
			0,//yDensity
			0,//comLength
			NULL//pCom
		},//excfg
		{
			JPEGENC_THUMB_JPEG,
			0, //96,
			0, //96,
			NULL,
			0
		},
		0,
		0
	};
	memcpy( cfg,&default_cfg ,sizeof(JpegEncConfig));
}

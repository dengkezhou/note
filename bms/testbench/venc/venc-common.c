/*ABOUT THIS FILE:
 *1,function
 *  @h264 encode test case:
 *      //Coding Control 
 *      case a:SLICESIZE:
 *      	1,Introduction:Valid value range: [0, 119],Sets the size of a slice in macroblock rows,
 *      	This parameter can be updated during the encoding process, between any picture encoding. Default value is 0.
 *      	2,Bug exist and fixed:
 *      	3,Target and test feedback:
 *      		2011.4.20 OK,sliceSize coding control is ok
 *      case b:SEIMESSAGES:
 *      	1,Introduction:Valid value range: [0, 1],Enables insertion of picture timing and buffering period SEI 
 *      	messages into the stream in the beginning of every encoded frame
 *      	2,Bug exist and fixed:
 *      	3,Target and test feedback:
 *      		2011.4.20 OK,the seimessages function is ok
 *		case c:VIDEOFULLRANGE:
 *			1,Introduction:Valid value range: [0, 1],0 = Y range in [16, 235], Cb&Cr range in [16, 240],
 *			1 = Y, Cb and Cr range in [0, 255]
 *			2,Bug exist and fixed:
 *			3,Target and test feedback:
 *				2011.4.20 the videofullrange function is ok
 *      case d:CONSTRAINEDINTRAPREDCTION:
 *      	1,Valid value range: [0, 1],Sets the intra prediction to constrained mode allowing only intra 
 *      	macroblocks to be used for prediction
 *      	2,Bug exist and fixed:
 *      	3,Target and test feedback:
 *      		2011.4.20 the constraniedintraprediction coding function is ok
 *      case e:DISABLEDEBLOCKINGFILTER:
 *      	1,Introduction:Valid value range: [0, 2],Sets the mode of the deblocking filter.
 *      	Value 0 enables filtering on all macroblock edge ,Value 2 disables filtering on edges that 
 *      	are part of a slice border,Value 1 disables entirely the deblocking filter.
 *      	2,Bug exist and fixed:
 *      	3,Target and test feedback:
 *      		2011.4.20 the DEBLOCKINGFILTER coding control function is ok
 *      case f:SAMPLEASPECTRATIOWIDTH,SAMPLEASPECTRATIOHEIGHT
 *      	1,Introduction:Valid value range: [0, 65535],Horizontal size of the sample aspect 
 *      	ratio (in arbitrary units), 0 for unspecified.
 *      	2,Bug exist and fixed:
 *      		I just don't understand what the asptratio means
 *      	3,Target and test feedback:
 *      		2011.4.20 the aspectratio width and height is just set into the encoding streams.function is ok
 *      case g:ENALBECABAC,CABACINITIDC
 *      	1,Introduction:ENALBECABAC->Valid value range: [0, 1],Enables CABAC for entropy coding. 
 *      		Stream profile will be either Main or High.
 *      		CABACINITIDC->Valid value range: [0, 2],Selects one of the three CABAC initialization tables.
 *      	2,Bug exist and fixed:
 *      	3,Target and test feedback:
 *      		2011.4.20 the cacac function is ok
 *      case h:TRANSFROM8x8MODE:
 *      	1,Introduction:Valid value range: [0, 2].Controls the 8x8 transfrom usage. 
 *      	Stream profile will be set to High when enabled,Value 0 disables the usage;Value 1 enables 
 *      	the adaptive usage of 8x8 transform;value 2 forces the transform to be used always.
 *      	2,Bug exist and fixed:
 *      	we should note that this function is only meanfull to the 720p or more big video if we 
 *      	set the TRANSFROM8x8MODE to 1
 *      	3,Target and test feedback:
 *      		2011.4.20 the TRANSFROM8x8MODE function is ok
 *      case i:QUARTERPIXELMV:
 *      	1,Introduction:Valid value range: [0, 2].Controls the usage of 1⁄4 pixel motion estimation,
 *      	2,Bug exist and fixed:
 *      	3,Target and test feedback:
 *      		2011.4.20 the QUARTERPIXELMV function is ok
 *
 *      //Rate Control
 	 case j:NO RATE CONTROL:
 	 	1,Introduction:disable pic rate control,disable mb rate control,disable skip picture rate control ,disable hdr rate control
 	 	2,Bug exist and fixed:
 	 	3,Target and test feedback:
 	 		2011.4.21 we can set the const qphdr value ,and encoder will always use this qp to do encoder expect the first frame
 *      case k:PICTURERC:
 		1,Introduction:Valid value range: [0, 1].Enables rate control to adjust QP between frames. 
 		This should be enabled if targe is set.
 		2,Bug exist and fixed:
 		3,Target and  test feedback:
 			2011.4.21 the picture control rate function is ok
 *      case l:MBRC:
 		1,Introduction:Valid value range: [0, 1].Enables rate control to adjust QP inside frames.
 		2,Bug exist and fixed:
 		3,Target and test feedback:
 			2011.4.21 the mb rate control function is ok
 *      case m:PCITURESKIP:
 		1,Introduction:Valid value range: [0, 1].Allow rate control to skip pictures if not enough bits are available.
 			When HRD is enabled, the rate control may have to skip frames despite of this value.
 		2,Bug exist and fixed:
 			you can set the target bitrate to a small value,then the skip picture method will be used
 		3,Target and feedback:
 			2011.4.21,function is ok
 *      case n:QPHDR:
 		1,Introduction:Valid value range: -1 or [0, 51].The initial quantization parameter used by the encoder
 *      		QPMIN:Valid value range: [0, 51].The minimum QP that can be set by the RC in the stream.
 				Not recommended to be set lower than 10.
 *      		QPMAX:Valid value range: [qpMin, 51].The maximum QP that can be set by the RC in the stream.
		2,Bug exist and fixed:
		3,Target and test feedback:
			2011.4.21 ok
 *      case o:BITPERSECOND:
 		1,Introduction:Valid value range: [10000, 40000000].The target bit rate in bits per second (bps) 
 			when the rate control is enabled.
 		2,Bug exist and fixed:
 		if you are not sure how to set the target bitrate ,use the default value
 		3,Target and test feedback:
 			2011.4.21 ok
 *      case p:HRD:
 		1,Introduction:Valid value range: [0,1].Enables the use of Hypothetical Reference Decoder model to 
 			estrict the nstantaneous bitrate.Enabling the HRD will automatically enable the picture and MB rate control.
 		2,Bug exist and fixed:
 		3,Target and test feedback:
 			2011.4.21 ok
 *      case q:HRDCPDSIZE:
 		1,Introduction:Valid value range: [0, MaxCPB].Size in bits of the coded picture buffer (CPB) used by the HRD model.
 		2,Bug exist and fixed:
 		if you are not sure how to set the target bitrate ,use the default value
 		3,Target and test feedback:
 			2011.4.21 ok
 *      case r:GOPLEN:
 		1,Introduction:Valid value range: [1, 150].Length of group of pictures.
 		2,Bug exist and fixed:
 			i think it should use according to our bitrate when scene changed
 		3,Target and test feedback:
 			2011.4.21 ok
 *      case s:INTRAQPDELTA:
 		1,Introduction:Valid value range: [-12, 12].Value added to the Intra frame QP.
 		2,Bug exist and fixed:
 		3,Target and test feedback:
 			2011.4.21 ok
 *      case t:FIXEDINTRAQP:
 		1,Introduction:Valid value range: [0, 51].Use this value for all Intra picture quantization.Value 0 disables the feature.
 		2,Bug exist and fixed:
 		3,Target and test feedback:
 			2011.4.21 ok
 *      case u:MBQPADJUSTMENT:
 		1,Introduction:Valid value range: [-8, 7].Enables MAD thresholding for macroblock based QP adjustment,
 			Use this value for adjusting QP of all macroblocks under threshold,Enabling this will disable MB RC.
 		2,Bug exist and fixed:
 		3,Target and test feedback:
 			2011.4.21 ok
 *      
 *      //PreProcessing
 *      case v:CROP:
 		1,Introduction:origWidth,origHeight,xoffset,yoffset,the detail rules:
 		2,Bug exist and fixed:
 		3,Target and test feedback:
 			2011.4.21 ok
 *
 *      case w:COlORCONVERSION:
 		1,Introduction:input color space(H264ENC_YUV420_PLANAR,H264ENC_YUV420_SEMIPLANAR,
 			H264ENC_YUV422_INTERLEAVED_YUYV,H264ENC_YUV422_INTERLEAVED_UYVY,H264ENC_RGB565,
 			H264ENC_BGR565,H264ENC_RGB555,H264ENC_BGR555,H264ENC_RGB444,H264ENC_BGR444,H264ENC_RGB888
 *      		H264ENC_BGR888,H264ENC_RGB101010,H264ENC_BGR101010)==>planar YCbCr 4:2:0
 		2,Bug exist and fixed:
 			NOTE:the result of RGB444 BGR444 are not so smooth because of its source	
 		3,Target and test feedback:
 			2011.4.21 ok,TODO:yuv420p has not been tested.
 			
 *      case x:ROTATION:
 		1,Introduction:the rotation block rotates the picture 90 degrees clockwise or counter-clockwise
 		2,Bug exist and fixed:
 		3,Target and test feedback:
 			2011.4.21 ok 
 *      case y:STABILIZATION:
 		1,Introduction:The encoder has a stabilization block which is examining the next frame to detect 
 			camera movement and scene changes,When the encoder knows this information about the next frame 
 			it will adjust the encoding parameters to stabilize video and encode scene change as intra frames.
 		2,Bug exist and fixed:
 			TODO:i do not know how to detect the scene changes
			2011.5.17 videostabilization autoly detect the scene changes
 		3,Target and test feedback:
 			2011.4.21:still have something to do
 *
 *		//Encode 
 *		case z:H264ENCSTREAMTYPE:
 		1,Introduction:H264ENC_BYTE_STREAM,H264ENC_NAL_UNIT_STREAM
 		2,Bug exist and fixed:
 		3,Target and test feedback:
 			our bytestream is nal annextB format.Intert 0001 before every NAL plane 
 			2011.4.21 ok
 *		case a1:H264ENCLEVEL:
 		1,Introcution :Specifies according to the standard the level of the generated stream:H264ENC_LEVEL_1,
 			H264ENC_LEVEL_1_b,H264ENC_LEVEL_1_1,H264ENC_LEVEL_1_2,H264ENC_LEVEL_1_3,H264ENC_LEVEL_2,
 			H264ENC_LEVEL_2_1,H264ENC_LEVEL_2_2,H264ENC_LEVEL_3,H264ENC_LEVEL_3_1,H264ENC_LEVEL_3_2,
 			H264ENC_LEVEL_4_0,H264ENC_LEVEL_4_1
 		2,Bug exist and fixed:
 		3,Target and test feedback:
 			we must pay attention to the constrains of every level .
 			2011.4.21 ok 
 *		case b1:H264ENCSIZE:
 		1,Introcution:width,Valid value range: [96, 1920];height,Valid value range: [96, 1920].
 		2,Bug exist and fixed:
 			can not find 1920 x1920 orignal input source 
 		3,Target and test feedback:
 			2011.4.21:TODO test the max input size supportted
			2011.5.17: can support the max size
 *		case c1:H264ENCFRAMERATENUM:
 		1,Introcution:Valid value range: [1, 1048575],The numerator part of the input frame rate.
 		2,Bug exist and fixed:numerator,enominator have effect to the videostream output,
		but i do not understand the full means of the two params
 		3,Target and test feedback:
 			2011.4.21:the two params have effect width the fps and time scale of timestamp. 
				I will take time to figure out the full means
 *		case d1:H264ENCFRAMERATEDENOM:
 			1,Introduction:Valid value range: [1, 1048575],The denominator part of the input frame rate.
 			2,see case c1
 
 *
 *
 *
 * @Jpeg Encode test case 
 * 		case a:QUANTIZATION LEVEL
 * 		       1,Introduction:Small value = low image quality = small JFIF output size,Valid value range: [0, 10].
 * 		       Of cource,we can set the quantization table changing the qTableLuma and qTableChroma.
 * 			   2,Bug exist and fixed:
 * 			   		2.1,the interruption always generate a interruption which indicate that memory cache coherency test
 * 			   			==>because our ewl do not do memset when allocate jpeg instance
 * 			   		2.2,jpeg progress is ok,but can not open the jpeg file on pc ==>the encode configure file are not 
 * 			   			right,we should change it accroding to our system 
 * 			   3,Target and test infotmation
 * 			   		2011.4.14:completed,the qLevel control function is ok
 * 		case b:INPUT FORMAT:
 * 				1,Introduction:JPEGENC_YUV420_PLANAR,JPEGENC_YUV420_SEMIPLANAR,JPEGENC_YUV422_INTERLEAVED_YUYV,
 * 					JPEGENC_YUV422_INTERLEAVED_UYVY,JPEGENC_RGB565,JPEGENC_BGR565,JPEGENC_RGB555,
 * 					JPEGENC_BGR555,JPEGENC_RGB444,JPEGENC_BGR444,JPEGENC_RGB888,JPEGENC_BGR888,JPEGENC_RGB101010,
 * 					JPEGENC_BGR101010
 * 				2,Bug exist and fixed:
 * 				3,Target and test feedback
 * 		case c:ROTATION:
 * 				1,Introduction:JPEGENC_ROTATE_0,JPEGENC_ROTATE_90R,JPEGENC_ROTATE_90L
 * 				2,Bug exist and fixed:
 * 				3,Target and test feedback:
 * 					2011.4.14:completed,rotation 90L or 90R is ok
 * 					
 * 		case d:CROPPING:
 *				1,Introduction:
 *       						--------------------------------------inputwidth([96,8192],multiple of 16)
 *      						-		 		^yoffset			 -
 *      						-				-					 -
 *      						- xoffset		-cropwidth(mutipleof -
 *      						-<-	- ->------------------	4)		 -
 *      						-		-				 - 			 -
 *      						-		-				 - 			 -
 *      						-		-				 - 			 -
 *      						-		-				 - 			 -
 *      						-		-				 - 			 -
 *      						-		------------------			 -
 *      						-	cropheight(mutiple of 2)		 -
 *      						-									 -
 *      						-									 - 			
 *       inputheight([32,8192]) --------------------------------------
 *				2,Bug exist and fixed:
 *                         3,Target and test feedback:
 *					2011.4.16:completed,Crop function is ok
 *			
 * 		case e:APP0 HEADER:
 				1,Introduction:unitsType(JPEGENC_NO_UNITS/JPEGENC_DOTS_PER_INCH/JPEGENC_DOTS_PER_CM)
 				2,Bug exist and fixed:
 				3,Target and test feedback:
 					2011.4.16:completed,can add app0 header ,more detail need our jpeg decoder to find the app0 header
 				
 *		case f:DQT and DHT HEADER:
 				1,Introduction:markerType(JPEGENC_SINGLE_MARKER/JPEGENC_MULTI_MARKER)
 				2,Bug exist and fixed:
 				3,Target and test feedback:
 					2011.4.16:TODO:completed,can add DQT and DHT header in the two ways,
							more detail need our jpeg decoder to find the app0 header
 *		case g:COMMENT HEADER:
 				1,Introduction:
 				2,Bug exist and fixed:
 				3,Target and test feedback:
 					2011.4.16:completed,can insert the comment header.
 *		case h:INPUT SIZE:
 				1,Introduction:inputwidth:The width of the input image in pixels. 
					This value has to be multiple of 16,Valid value range: [96, 8192];
 *					inputheight:The height of the input image in pixels.Valid value range: [32, 8192]
 				2,Bug exist and fixed:Now only test the normal size which is below 1080P,and test result is ok.
					I need to get the bigger yuv/rgb pictures
 				3,Target and test feedback:
 					2011.4.16:TODO:need some bigger rgb/yuv source test data
					2011.5.17:support 8192x8192
 *		case i:CODING TYPE:
 				1,Introduction:Specifies the coding type of the input frame(JPEGENC_WHOLE_FRAME/JPEGENC_SLICED_FRAME)
 				2,Bug exist and fixed:
 				3,Target and test feedback:
 					2011..4.16:completed,the whole frame encoding type and slice-frame encoding type both ok.	
 *     case k:THUMBNAIL MODE:
 				1,Introduction:Insert a thumbnail as a JFIF APP0 extension data
 				2,Bug exist and fixed:
 					Now i have tested the thumbnail JPEG and rgb888 format,and do not test the Palette 
						RGB8 format thumbnail 
 				3,Target and test feedback:
					2011.4.16:TODO:need our decoder to find out if the thumbnail header is ok
 *      case l:OUTPUT TYPE:JPEGENC_420_MODE/ENC_422_MODE
 				1,Introduction:
 				2,Bug exist and fixed:now G1 decoder has shut down the micro which use to control coding type 422 mode,
 					so ,we only can use 420mode 
 				3,Target and test feedback:
 					422 mode is shut down by G1 decoder,i try to turn on the MICRO to use 422mode coding type ,the 
 					encoding process is ok ,but the output jpeg file encoded out is not right
 					so i think the function of coding type 422 mode is not ok!
 					
 *
 *@Video Stabilization test case 
 *		case a:inputSize
 *			1,Introduction: inputWidth,The width of the camera input frame in pixels.Valid values: [104, 4096];
 *							inputHeight,The height of the camera input frame in pixels.Valid values:[104,4096];
 *			2,Bug exist and fixed:
 *			3,Target and test feedback:
 *		case b:Stride
 *			1,Introduction:The camera input frame horizontal scanline in pixels. Has to be an 8 multiple
 *					Valid values:[104,4096]
 *			2,Bug exist and fixed:
 *			3,Target and test feedback:
 *		case c:stabilization Size:
 *			1,Introduction:stabilizedWidth,The width of the stabilized frame in pixels. Must be a multiple of 4.
 *									Valid values:[96, inputWidth-8]
 *						   stabilizedHeight,The height of the stabilized frame in pixels.Must be a multiple of 4.
 *						   			Valid values:[96,inputHeight-8]
 *			2,Bug exist and fixed:
 *			3,Target and test feedback:
 *		case d:source format:
 *			Specifies the input frame format.VIDEOSTB_YUV420_PLANAR,VIDEOSTB_YUV420_SEMIPLANAR,
 *				VIDEOSTB_YUV422_INTERLEAVED_YUYV,VIDEOSTB_YUV422_INTERLEAVED_UYVY,VIDEOSTB_RGB565,
 *				VIDEOSTB_BGR565,VIDEOSTB_RGB555,VIDEOSTB_BGR555,VIDEOSTB_RGB444,VIDEOSTB_BGR444,VIDEOSTB_RGB888,
 *				VIDEOSTB_BGR888,VIDEOSTB_RGB101010,VIDEOSTB_BGR101010
*/


#include <common.h>
#include <stdlib.h>
#include <malloc.h>
#include <linux/crc32.h>
#include <asm/io.h>
#include <linux/types.h>

#define PERI_BASE_PA        (0x20000000)
#define VDEC0_BASE_ADDR     (PERI_BASE_PA + 0x5000000)
#define VENC0_BASE_ADDR     ITCS_C_VENC_BASE
#define VDEC1_BASE_ADDR     (PERI_BASE_PA + 0x5200000)
#define VENC1_BASE_ADDR     (PERI_BASE_PA + 0x5100000)

#include "venc-common.h"
//#include <vidstbapi.h>
#include "8270-reg.h"
#include "h1-reg.h"
#include "h2-reg.h"
#define __DEBUG__
#ifdef  __DEBUG__
#define VENC_LOG(on,format) if(on)(printf format)
#else
#define VENC_LOG(on,format)
#endif


#define MODULE_COMMON "ENCODE_TEST::COMMON"
#define MODULE_JPEG  "GRAPHIC_ENC::JPEG"
#define MODULE_H264  "VIDEO_ENC::H264"
#define MODULE_STAB	  "STABILIZATION::CAMERA"

#define INFO 1
#define WARN 1
#define ERR  1
FILE *ftime = NULL;

#define VENC_WRITE_TIME(state,previoustime,function)	\
{		\
	int TimeTake = 0;	\
	TimeTake = sys_get_timer() - previoustime ;	\
	if(ftime)	\
		fprintf(ftime,"%s			%s			%d\n",#state,#function,TimeTake); 	\
}

#define VENC_GPIO_MAKE_A_PULSE(enable)	\
{	\
	if(enable)	\
	{	\
		int delay = 500;	\
		rGPLDAT = 1<<5;	\
		while(delay--);	\
		rGPLDAT = 0;	\
	}	\
}	

#define VENC_HALT(enable)	\
{	\
	if(enable)	\
	{	\
		int halt=0;	\
		log_printf("venc halt!\n");	\
		log_printf("please press any number key to go on!\n");	\
		scanf("%d",&halt);	\
	}	\
}

#if 0
int32_t tb_venc_alloc_linear_memory(VencLinearMem *buffer, int32_t size)
{
    printf((("%s()"), (__func__)));
    buffer->vBuffer = (void  *)malloc( size); 
    if(buffer->vBuffer == NULL){
        printf((("mm_module_malloc() failed!")));
        goto Fail;
    }   
	
    buffer->bBuffer =(uint32_t) (size_t)buffer->vBuffer;
    buffer->size = size;
	
    return 1;
Fail:
    return -1;   
}

int32_t tb_venc_free_linear_memory(vdec_buffer *buffer)
{
    printf((("%s()"), (__func__)));
    if(buffer->vir_addr != NULL){
        free( buffer->vir_addr);
    }   
    buffer->phy_addr = 0;
    buffer->size = 0;
    buffer->flag = 0;   
	
    return 1;
}	
		
#endif







const char CAMERA_STAB_INPUT_FILE_FOLDER[] = "venc/stab";
const char NALU_HEADER[4] = {0, 0, 0, 1};

int venc_get_random_size(int max,int min);











// ============================================================================


/*
func:autoly get a default configuration context when application just want to do a generally verification of encode mode
params:*excfg,the default context's address
return:0 ,fail to get the default context,maybe the default file can not be opened;
		1,success
*/
int venc_get_default_cfg(VENC_TYPE type,void **excfg)
{
	VENC_LOG(INFO,("%s venc_get_default_cfg()+++\n",MODULE_COMMON));
	if(excfg ==NULL){
		VENC_LOG(ERR,("%s params is null!\n",MODULE_COMMON));
		return 0;
	}
	if(type == TYPE_JPEG){
		//*excfg =(void *)&enc_jpeg_default_config;
	}else if(type == TYPE_H264){
		//*excfg =(void *)&enc_h264_default_config;
	}else if(type == TYPE_CAMSTAB){
//		*excfg = (void *)&enc_stab_default_config;
	}
	VENC_LOG(INFO,("%s venc_get_default_cfg()---\n",MODULE_COMMON));
	return 1;

}

/*
func:get the random size which is range in the special range
params:maxsize ,minsize ,offset
return:the available value 
*/

int venc_get_random_size(int max,int min)
{
	int random = 0;
	int max1 = max+1;
	int min1 = min;
	VENC_LOG(INFO,("%s venc_get_random_size()+++\n",MODULE_COMMON));
	if(max<min){
		max1 = min+1;
		min1 = max;
	}
	if(max1 == min1)
		return max1;
	//random =rand()%(max1-min1)+min1;
	random = (max+min)/2;
	return random;

}


/*
func:write a buffer's content to a special file
params:file --->the file write to 
		buffer--->the address of data to be written
		size ---->the size of data to be written
		endian--->big endian is 1,0 is little endian
return:0 failed to write
		1 success 
*/
int venc_write_file(FILE *file,void *buffer,unsigned int size,int endian)
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
	
	size_t writesize = fwrite(strmbuf, 1, size, file);
	VENC_LOG(INFO,("Writing stream address %p-> %d ->%d->%d \n",strmbuf, size,writesize,file->offset));
	//==========================================================================	
#endif
	return 1;
}

/*
func:check the src which bytes should be copied to dst,it need not to copy source to dst if the source bytes value is 0xFF
params:dst--->dst buffer pointer 
		src--->src buffer pointer
		size--->size checked and copied
return:
*/
void venc_copy_with_check(unsigned int *dst,unsigned int *src,int size)
{
	int i =0;
	VENC_LOG(INFO,("%s venc_copy_with_check()+++\n",MODULE_COMMON));
	if(dst ==NULL || src ==NULL){
		VENC_LOG(ERR,("%s params is null!\n",MODULE_COMMON));
		return;
	}
	for(;i<size;i++){
		if(src[i] != 0xFFFFFFFF)
			dst[i] = src[i];
	}

	VENC_LOG(INFO,("%s venc_copy_with_check()---\n",MODULE_COMMON));
}



int32_t venc_malloc_linear_buffer(VencLinearMem *mem,int32_t size){
	mem->vBuffer = (void *) malloc(size);

	if(mem->vBuffer == NULL){
		return -1;
	}
	mem->bBuffer = (uint32_t) (size_t) mem->vBuffer;
	mem->size = size;
	mem->offset = 0;
	return size;
}
/**
 * @brief vdec_free_linear_buffer 
 *
 * @param mem
 *
 * @return 
 */
int32_t venc_free_linear_buffer(VencLinearMem *mem){
	if(mem->vBuffer)
		free(mem->vBuffer);
	mem->vBuffer =  NULL;
	mem->bBuffer =  0;
	mem->size = 0;
	mem->offset = 0;
	return 0;
}




/*
func:
params:
return:
*/
int32_t dump_venc_linear_mem_to_file(FILE *fd ,VencLinearMem *mem,uint32_t crc32){
	assert(fd == NULL);
#ifdef CONFIG_COMPILE_RTL 
		printf("%s rtl mode ,do not do crc32  0x%X\n",crc32);
#else 
	if(crc32) {
		uint32_t cal = lib_crc32_le(0, (unsigned char*)mem->vBuffer, mem->offset);
		if (crc32 == cal){
			VENC_LOG(INFO,("crc result passed -> %X  %X \n",crc32 ,cal));
		}
		else{
			VENC_LOG(INFO,("crc result failed -> %X  %X \n",crc32 ,cal));
		}
	}
	else {
		VENC_LOG(INFO,("not contain crc info ,not do crc32\n"));
	}
#endif
	int32_t writeSize = fwrite(mem->vBuffer,mem->offset,1,fd);
	if(writeSize!= mem->offset){
		VENC_LOG(INFO,("write mem data to file erro -> %d  %d \n",mem->offset,writeSize));
		return -1;
	}
	return 1;
}
int32_t write_to_venc_linear_mem(VencLinearMem *mem,int8_t *buf,uint32_t len,int32_t resetFlag){
	if(resetFlag != 0){
		VENC_LOG(INFO,("write to buff at first time and reset the offset"));
	}
	if(len <= 0){
		return len;
	}
	if(mem->offset + len >= mem->size){
		VENC_LOG(INFO,("write buf may exceed the malloc size ,\
					please extend the size  -> %d  %d %d\n"\
					,mem->size,mem->offset ,len));
		len =  mem->size - mem->offset;
	}
	memcpy((mem->vBuffer+mem->offset),buf,len);
	mem->offset += len;
	return 0;
}

int32_t venc_load_file_to_mem(char *filename ,VencLinearMem *mem,uint32_t size){
	int fd = open(filename,O_RDONLY);
	uint32_t memSize = 0;
	if (fd < 0 ){
		return -1;
	}
	memSize = (size == 0) ?  flen(fd)  :size  ;
	if(venc_malloc_linear_buffer(mem,memSize + 1) <0 )
	{
		goto ERROR_PROCESS;
	}
	mem->offset  = read(fd,mem->vBuffer,memSize );
	if(mem->offset < 0){
		goto ERROR_PROCESS;
	}
	
	((char * )mem->vBuffer)[memSize] = '\0';
	close(fd);
	return mem->offset;

ERROR_PROCESS :
	if(fd >= 0)
		close(fd);
	venc_free_linear_buffer(mem);
	return -1;
}

int32_t venc_dump_mem_to_file(char *filename,VencLinearMem *mem,uint32_t crc32,char *msg){
	return 0;
}
#if defined(CONFIG_VDEC_VENC_X9) 
#define VENC0_BASE_ADDR   VENC_BASE_ADDR
#define VENC1_BASE_ADDR   VENC_BASE_ADDR
#else
#define VENC_BASE_ADDR    0
#endif



#define VENC_8270_REG_BASE  VENC_BASE_ADDR
#define VENC_8270_REG_HW_ID	0
#define VENC_8270_REG_CFG   	0x8
#define VENC_8270_RW_REG_BUS_1	0x34
#define VENC_8270_RW_REG_BUS_2	0x38

#define VENC_H1_REG_BASE 	VENC0_BASE_ADDR
#define VENC_H1_REG_HW_ID	0
#define VENC_H1_REG_CFG   	0x8
#define VENC_H1_RW_REG_BUS_1	0x34
#define VENC_H1_RW_REG_BUS_2	0x38

#define VENC_H2_REG_BASE  	VENC1_BASE_ADDR
#define VENC_H2_REG_HW_ID	0
#define VENC_H2_REG_CFG   	0x8
#define VENC_H2_RW_REG_BUS_1	0x100
#define VENC_H2_RW_REG_BUS_2	0x104
int venc_basic_reg_test(int32_t testType){
	uint32_t  value[4];
	if(testType == 0 ){//8270 module  basic 
		writel(0xAAAAAAAA,VENC_8270_RW_REG_BUS_1 + VENC_8270_REG_BASE);
		writel(0xBBBBBBBB,VENC_8270_RW_REG_BUS_2 + VENC_8270_REG_BASE);
		value[0] = readl(VENC_8270_REG_HW_ID + VENC_8270_REG_BASE);
		value[1] = readl(VENC_8270_REG_CFG + VENC_8270_REG_BASE);
		value[2] = readl(VENC_8270_RW_REG_BUS_1 + VENC_8270_REG_BASE);
		value[3] = readl(VENC_8270_RW_REG_BUS_2 + VENC_8270_REG_BASE);
		printf("VENC 8270 reg result -> 0x%X 0x%X 0x%X 0x%X\n",value[0],value[1],value[2],value[3]);
	}
	else if(testType == 1 ){//h1 module  basic
		writel(0xAAAAAAAA,VENC_H1_RW_REG_BUS_1 + VENC_H1_REG_BASE);
		writel(0xBBBBBBBB,VENC_H1_RW_REG_BUS_2 + VENC_H1_REG_BASE);
		value[0] = readl(VENC_H1_REG_HW_ID + VENC_H1_REG_BASE);
		value[1] = readl(VENC_H1_REG_CFG + VENC_H1_REG_BASE);
		value[2] = readl(VENC_H1_RW_REG_BUS_1 + VENC_H1_REG_BASE);
		value[3] = readl(VENC_H1_RW_REG_BUS_2 + VENC_H1_REG_BASE);
		printf("VENC h1 reg result -> 0x%X 0x%X 0x%X 0x%X\n",value[0],value[1],value[2],value[3]);
	}
	else if (testType == 2 ){//h2 module basic
		writel(0xAAAAAAAA,VENC_H2_RW_REG_BUS_1 + VENC_H2_REG_BASE);
		writel(0xBBBBBBBB,VENC_H2_RW_REG_BUS_2 + VENC_H2_REG_BASE);
		value[0] = readl(VENC_H2_REG_HW_ID + VENC_H2_REG_BASE);
		value[1] = readl(VENC_H2_REG_CFG + VENC_H2_REG_BASE);
		value[2] = readl(VENC_H2_RW_REG_BUS_1 + VENC_H2_REG_BASE);
		value[3] = readl(VENC_H2_RW_REG_BUS_2 + VENC_H2_REG_BASE);
		printf("venc h2 reg result -> 0x%X 0x%X 0x%X 0x%X\n",value[0],value[1],value[2],value[3]);
	}
	else if (testType == 3 ){//8270 full
		printf("8270 reg full access \n");
		venc_reg_access(h8270_reg_list,VENC_8270_REG_BASE);
	}
	else if (testType == 4 ){//h1 full 
		printf("h1 reg full access \n");
		venc_reg_access(h1_reg_list,VENC_H1_REG_BASE);
	}
	else if (testType == 5 ){//h2 full 
		printf("h2 reg full access \n");
		venc_reg_access(h2_reg_list,VENC_H2_REG_BASE);
	}
	else {
		printf("venc reg input para err \n");
		return -1;
	}
	return 1;
}
void venc_reg_access(const VENC_REG_ACCESS_INFO reg[],size_t base){
	int i;
	uint32_t value  =0 ;
	size_t address= 0 ;
	for(i = 0;; i++){
		if(reg[i].offset == 0xFFFFFFFF){
			printf("case over \n");
			break;
		}
		address =  base + reg[i].offset;
		switch(reg[i].rw){
			case 0: //read only 
				value =  readl(address);
				printf("RO reg -->%d 0x%X 0x%X\n",i,address,value);
				break;
			case 1://read write
				writel(0xFFFFFFFF,address);
				value =  readl(address);
				printf("RW reg -->%d 0x%X 0x%X\n",i,address,value);
				break;
			case 2://write only 
				writel(0xFFFFFFFF,address);
				writel(0xFFFFFFFF,address);
				value =  readl(address);
				printf("WO reg -->%d 0x%X 0x%X\n",i,address,value);
				break;
			default:
				break;
		}
	}
}

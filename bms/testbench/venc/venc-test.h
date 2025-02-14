

#ifndef _VENC_TEST_H_
#define _VENC_TEST_H_
#include "venc-api.h"


//#define  __H264ENCTEST__
//#define  __JPEGENCTEST__
#define  __VIDEOSTABTEST__ 


/*********************************************H264 ENCODE MICRO CONTROL****************************************************************/
//H264 encode test case 

//#define H264_TESTCASE_ENCODING_FORMAT
	#define H264_TESTCASE_ENCODING_BYTESTREAM_FORMAT
	#define H264_TESTCASE_ENCODING_NAL_FORMAT

//#define H264_TESTCASE_ENCODING_LEVEL
	#define H264_TESTCASE_ENCODING_LEVEL_1
	#define H264_TESTCASE_ENCODING_LEVEL_1_B
	#define H264_TESTCASE_ENCODING_LEVEL_1_1
	#define H264_TESTCASE_ENCODING_LEVEL_1_2
	#define H264_TESTCASE_ENCODING_LEVEL_1_3
	#define H264_TESTCASE_ENCODING_LEVEL_2
	#define H264_TESTCASE_ENCODING_LEVEL_2_1
	#define H264_TESTCASE_ENCODING_LEVEL_2_2
	#define H264_TESTCASE_ENCODING_LEVEL_3
	#define H264_TESTCASE_ENCODING_LEVEL_3_1
	#define H264_TESTCASE_ENCODING_LEVEL_3_2
	#define H264_TESTCASE_ENCODING_LEVEL_4_0
	#define H264_TESTCASE_ENCODING_LEVEL_4_1

//#define H264_TESTCASE_ENCODING_TARGET_FRAMERATE
	#define H264_TESTCASE_ENCODING_TARGET_FRAMERATE_1
	#define H264_TESTCASE_ENCODING_TARGET_FRAMERATE_5
	#define H264_TESTCASE_ENCODING_TARGET_FRAMERATE_15
	#define H264_TESTCASE_ENCODING_TARGET_FRAMERATE_23
	#define H264_TESTCASE_ENCODING_TARGET_FRAMERATE_30
	#define H264_TESTCASE_ENCODING_TARGET_FRAMERATE_60

//#define H264_TESTCASE_CODING_CTRL
	#define H264_TESTCASE_CODING_CTRL_SLICESIZE
	#define H264_TESTCASE_CODING_CTRL_SEIMESSAGES
	#define H264_TESTCASE_CODING_CTRL_VIDEOFULLRANGE
	#define H264_TESTCASE_CODING_CTRL_CONSTRAINEDINTRAPREDCTION
	#define H264_TESTCASE_CODING_CTRL_DISABLEDEBLOCKINGFILTER
	#define H264_TESTCASE_CODING_CTRL_SAMPLEASPECTRATIO
	#define H264_TESTCASE_CODING_CTRL_ENALBECABAC
	#define H264_TESTCASE_CODING_CTRL_TRANSFROM8x8MODE
	#define H264_TESTCASE_CODING_CTRL_QUARTERPIXELMV

//#define H264_TESTCASE_RATE_CTRL
	#define H264_TESTCASE_RATE_CTRL_CBR
	#define H264_TESTCASE_RATE_CTRL_VBR_PB
	#define H264_TESTCASE_RATE_CTRL_VBR_MB
	#define H264_TESTCASE_RATE_CTRL_VBR_SKIP_PIC
	#define H264_TESTCASE_RATE_CTRL_VBR_HDR
	
	#define H264_TESTCASE_RATE_CTRL_IQPDELTA
	#define H264_TESTCASE_RATE_CTRL_IQIPFIXED
	#define H264_TESTCASE_RATE_CTRL_MBQPADJUST
	#define H264_TESTCASE_RATE_CTRL_GOPLEN

//#define H264_TESTCASE_PRE_PROC
	#define H264_TESTCASE_PRE_PROC_SIZE
	#define H264_TESTCASE_PRE_PROC_FORMAT
	#define H264_TESTCASE_PRE_PROC_ROTATION
	//#define H264_TESTCASE_PRE_PROC_VIDEOSTABILIZATION
	#define H264_TESTCASE_PRE_PROC_CROP

#define H264_TESTCASE_INPUT_ISP

//#define H264_TESTCASE_PERFORMANCE

#define H264_RTLCASE
/*	#define H264_RTLCASE_41_LEVEL_1_2
	#define H264_RTLCASE_42_LEVEL_4_1
	#define H264_RTLCASE_43_FRAMERATE_15
	#define H264_RTLCASE_44_CODING_CTRL_SLICESIZE
	#define H264_RTLCASE_45_CODING_CTRL_ENALBECABAC
	#define H264_RTLCASE_46_CODING_CTRL_TRANSFROM8x8MODE
	#define H264_RTLCASE_47_RATE_CTRL_CBR
	#define H264_RTLCASE_48_RATE_CTRL_VBR_PB
	#define H264_RTLCASE_49_CTRL_VBR_HDR
	#define H264_RTLCASE_50_RATE_CTRL_MBQPADJUST
	#define H264_RTLCASE_51_PRE_PROC_SIZE_96x96
	#define H264_RTLCASE_52_PRE_PROC_SIZE_352x288
	#define H264_RTLCASE_53_PRE_PROC_SIZE_1280x720
	#define H264_RTLCASE_54_PRE_PROC_SIZE_1920x1080
	#define H264_RTLCASE_55_PRE_PROC_FORMAT_YUYV
	#define H264_RTLCASE_56_PRE_PROC_FORMAT_RGB565
	#define H264_RTLCASE_57_PRE_PROC_FORMAT_RGB888
	#define H264_RTLCASE_58_PROC_ROTATION_90L
	#define H264_RTLCASE_59_PROC_ROTATION_90R
*/	#define H264_RTLCASE_60_PROC_VIDEOSTABILIZATION
	//#define H264_RTLCASE_61_PROC_CROP

#ifdef H264_RTLCASE
	#undef H264_TESTCASE_ENCODING_FORMAT
	#undef H264_TESTCASE_ENCODING_LEVEL
	#undef H264_TESTCASE_ENCODING_TARGET_FRAMERATE
	#undef H264_TESTCASE_CODING_CTRL
	#undef H264_TESTCASE_RATE_CTRL
	#undef H264_TESTCASE_PRE_PROC
	#undef H264_TESTCASE_INPUT_ISP
	#undef H264_TESTCASE_PERFORMANCE
#endif	

/*********************************JPEG ENCODE MICRO CONTROL**************************/
//jpeg encode test case
//#define JPEG_TESTCASE_QLEVEL //qlevel
	#define JPEG_TESTCASE_QLEVEL_L0	
	#define JPEG_TESTCASE_QLEVEL_L1
	#define JPEG_TESTCASE_QLEVEL_L2
	#define JPEG_TESTCASE_QLEVEL_L3
	#define JPEG_TESTCASE_QLEVEL_L4
	#define JPEG_TESTCASE_QLEVEL_L5
	#define JPEG_TESTCASE_QLEVEL_L6
	#define JPEG_TESTCASE_QLEVEL_L7
	#define JPEG_TESTCASE_QLEVEL_L8
	#define JPEG_TESTCASE_QLEVEL_L9
	#define JPEG_TESTCASE_QLEVEL_L10

//#define JPEG_TESTCASE_INPUT_FORMAT
	#define JPEG_TESTCASE_INPUT_YUV420P
	#define JPEG_TESTCASE_INPUT_YUV420SP
	#define JPEG_TESTCASE_INPUT_YUV422_INTERLEAVED_YUYV
	#define JPEG_TESTCASE_INPUT_YUV422_INTERLEAVED_UYVY
	#define JPEG_TESTCASE_INPUT_RGB565
	#define JPEG_TESTCASE_INPUT_BGR565
	#define JPEG_TESTCASE_INPUT_RGB555
	#define JPEG_TESTCASE_INPUT_BGR555
	#define JPEG_TESTCASE_INPUT_RGB444
	#define JPEG_TESTCASE_INPUT_BGR444
	#define JPEG_TESTCASE_INPUT_RGB888
	#define JPEG_TESTCASE_INPUT_BGR888
	#define JPEG_TESTCASE_INPUT_RGB101010
	#define JPEG_TESTCASE_INPUT_BGR101010

//#define JPEG_TESTCASE_INPUT_ROTATION
	//#define JPEG_TESTCASE_INPUT_ROTATE_0
	#define JPEG_TESTCASE_INPUT_ROTATE_90R
	#define JPEG_TESTCASE_INPUT_ROTATE_90L

//#define JPEG_TESTCASE_INPUT_CROPPING
	#define JPEG_TESTCASE_INPUT_CROP_TOPLEFT
	#define JPEG_TESTCASE_INPUT_CROP_TOPRIGHT
	#define JPEG_TESTCASE_INPUT_CROP_BOTTOMLEFT
	#define JPEG_TESTCASE_INPUT_CROP_BOTTOMRIGHT
	#define JPEG_TESTCASE_INPUT_CROP_MIDDLE

//#define JPEG_TESTCASE_INPUT_SIZE
	#define JPEG_TESTCASE_INPUT_MIN//min
	//#define JPEG_TESTCASE_INPUT_MAX//max	// limited by memory, 8k*8k=64M.

	#define JPEG_TESTCASE_INPUT_MINW_MAXH//min width +max height
	#define JPEG_TESTCASE_INPUT_MAXW_MINH//max width + min height
	#define JPEG_TESTCASE_INPUT_SUB_QCIF//sub-QCIF(128x96)
	#define JPEG_TESTCASE_INPUT_QQVGA//QQVGA(160x120)
	#define JPEG_TESTCASE_INPUT_QCIF//QCIF(176x144)
	#define JPEG_TESTCASE_INPUT_QVGA//QVGA(320x240)
	#define JPEG_TESTCASE_INPUT_CIF//CIF(352x288)
	#define JPEG_TESTCASE_INPUT_VGA//VGA(640x480)
#if 1
	#define JPEG_TESTCASE_INPUT_PAL//PAL(768x576)
	#define JPEG_TESTCASE_INPUT_SVGA//SVGA(800*600)
	#define JPEG_TESTCASE_INPUT_XVGA//XVGA(1024*768)
	#define JPEG_TESTCASE_INPUT_720P//720p(1280X720)
	#define JPEG_TESTCASE_INPUT_SXGA//SXGA(1280x1024)
	#define JPEG_TESTCASE_INPUT_SXGAPlus//SXGA+(1400x1050)
	#define JPEG_TESTCASE_INPUT_UXGA//UXGA(1600x1200)
	#define JPEG_TESTCASE_INPUT_1080P//1080P(1920x1080)
	#define JPEG_TESTCASE_INPUT_WQXGA//WQXGA(2560x1600)
	#define JPEG_TESTCASE_INPUT_QUXGA//QUXGA(3200x2400)
	#define JPEG_TESTCASE_INPUT_QUXGA_W//QUXGA-W(3840x2400)
	#define JPEG_TESTCASE_INPUT_xxxx
#endif
	
//#define JPEG_TESTCASE_HEADER_APP0
	#define JPEG_TESTCASE_HEADER_APP0_NO_UNITS
	#define JPEG_TESTCASE_HEADER_APP0_DOTS_PER_INCH
	#define JPEG_TESTCASE_HEADER_APP0_DOTS_PER_CM


//#define JPEG_TESTCASE_HEADER_DQT_DHT  
	#define JPEG_TESTCASE_HEADER_SINGLE_MARKER
	#define JPEG_TESTCASE_HEADER_MULTI_MARKER

//#define JPEG_TESTCASE_HEADER_COMMENT
	

//#define JPEG_TESTCASE_HEADER_THUMBNAIL
	#define JPEG_TESTCASE_HEADER_THUMBNAIL_JPEG
	#define JPEG_TESTCASE_HEADER_THUMBNAIL_PALETTE_RGB8
	#define JPEG_TESTCASE_HEADER_THUMBNAIL_RGB24


//#define JPEG_TESTCASE_ENCODING_CODE_TYPE
	#define JPEG_TESTCASE_ENCODING_WHOLE_FRAME
	#define JPEG_TESTCASE_ENCODING_SLICE_FRAME

//#define JPEG_TESTCASE_ENCODING_MODE
	#define JPEG_TESTCASE_ENCODING_JPEG_420_MODE	// not implement.
	#define JPEG_TESTCASE_ENCODING_JPEG_422_MODE	// not implement.

#define JPEG_TESTCASE_INPUT_ISP

//#define JPEG_TESTCASE_PERFORMANCE

//#define JPEG_RTLCASE
	#define JPEG_RTLCASE_0_QLEVEL_L8
	#define JPEG_RTLCASE_1_INPUT_YUV420P
	#define JPEG_RTLCASE_2_INPUT_YUV422_INTERLEAVED_YUYV
	#define JPEG_RTLCASE_3_INPUT_RGB565
	#define JPEG_RTLCASE_4_INPUT_RGB101010
	#define JPEG_RTLCASE_5_INPUT_ROTATE_90R
	#define JPEG_RTLCASE_6_INPUT_ROTATE_90L
	#define JPEG_RTLCASE_7_INPUT_CROP_MIDDLE
	#define JPEG_RTLCASE_8_INPUT_MIN
	#define JPEG_RTLCASE_10_INPUT_1080P
	#define JPEG_RTLCASE_11_HEADER_APP0_DOTS_PER_INCH
	#define JPEG_RTLCASE_12_HEADER_MULTI_MARKER
	#define JPEG_RTLCASE_13_HEADER_COMMENT
	#define JPEG_RTLCASE_14_HEADER_THUMBNAIL_JPEG
	#define JPEG_RTLCASE_15_HEADER_THUMBNAIL_PALETTE_RGB8
	#define JPEG_RTLCASE_16_ENCODING_SLICE_FRAME

#ifdef JPEG_RTLCASE
	#undef JPEG_TESTCASE_QLEVEL
	#undef JPEG_TESTCASE_INPUT_FORMAT
	#undef JPEG_TESTCASE_INPUT_ROTATION
	#undef JPEG_TESTCASE_INPUT_CROPPING
	#undef JPEG_TESTCASE_INPUT_SIZE
	#undef JPEG_TESTCASE_HEADER_APP0
	#undef JPEG_TESTCASE_HEADER_DQT_DHT
	#undef JPEG_TESTCASE_HEADER_COMMENT
	#undef JPEG_TESTCASE_HEADER_THUMBNAIL
	#undef JPEG_TESTCASE_ENCODING_CODE_TYPE
	#undef JPEG_TESTCASE_ENCODING_MODE
	#undef JPEG_TESTCASE_INPUT_ISP
	#undef JPEG_TESTCASE_PERFORMANCE
#endif

/**************************************video stabilization test control*******************************************************/
#define STAB_RTLCASE





/************************************************H264 testcase******************************************************/
#ifdef __H264ENCTEST__
H264ENCCFG h264_enc_test[] ={
#ifdef H264_TESTCASE_ENCODING_FORMAT
	#ifdef H264_TESTCASE_ENCODING_BYTESTREAM_FORMAT
	{
		"",
		"yuv420Semiplanar_progressive_w320_h240.yuv",
		"h264_w320_h240_testcase_encoding_bytestream_format.h264",
		"infotmuserdata.txt",
		0,
		0,
		1,
	    {
        	H264ENC_BYTE_STREAM,  
        	H264ENC_LEVEL_1_1,
        	320,           
        	240,          
        	15,    
        	1, 
        	H264ENC_COMPLEXITY_1 
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
			H264ENC_YUV420_SEMIPLANAR,
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

	},
	#endif
	#ifdef H264_TESTCASE_ENCODING_NAL_FORMAT
	{
		"",
		"yuv420Semiplanar_progressive_w320_h240.yuv",
		"h264_w320_h240_testcase_encoding_nal_format.h264",
		"infotmuserdata.txt",
		0,
		0,
		1,

	    {
        	H264ENC_NAL_UNIT_STREAM,
        	H264ENC_LEVEL_1_1,
        	320,
        	240,
        	15,
        	1,
        	H264ENC_COMPLEXITY_1
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
			H264ENC_YUV420_SEMIPLANAR,
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

	},
	#endif
#endif
#ifdef H264_TESTCASE_ENCODING_LEVEL 
//99, 396, 396, 396, 396, 792, 1620, 1620,
//    3600, 5120, 8192, 8192, 8192, 22080, 36864
	//level1 max support mbSize is 99,mean max Revolution is 176x144(QCIF)
	//level1_1,level1_b,level1_2,level1_3,level2 ,max support mbSize is 396,mean max revolution is 352x288(CIF)
	//level2_1 max support mbSize is 792,mean max Revolution is 480x422
	//level2_2 1620  PAL(720x576)
	//level3  1620 PAL(720x576)
	//level3.1 3600
	#ifdef H264_TESTCASE_ENCODING_LEVEL_1
	{
		"",
		"yuv420Semiplanar_progressive_w320_h240.yuv",
		"h264_w320_h240_testcase_encoding_level1_format.h264",
		"infotmuserdata.txt",
		0,
		0,
		1,
	    {
        	H264ENC_BYTE_STREAM,  
        	H264ENC_LEVEL_1_b,
        	176,           
        	144,          
        	15,    
        	1, 
        	H264ENC_COMPLEXITY_1 
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
			H264ENC_YUV420_SEMIPLANAR,
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

	},
	#endif
	
	#ifdef H264_TESTCASE_ENCODING_LEVEL_1_B
	{
		"",
		"yuv420Semiplanar_progressive_w320_h240.yuv",
		"h264_w320_h240_testcase_encoding_level1b_format.h264",
		"infotmuserdata.txt",
		0,
		0,
		1,
	    {
        	H264ENC_BYTE_STREAM,  
        	H264ENC_LEVEL_1_b,
        	176,           
        	144,          
        	15,    
        	1, 
        	H264ENC_COMPLEXITY_1 
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
			H264ENC_YUV420_SEMIPLANAR,
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

	},
	#endif
	
	#ifdef H264_TESTCASE_ENCODING_LEVEL_1
	{
		"",
		"yuv420Semiplanar_progressive_w320_h240.yuv",
		"h264_w320_h240_testcase_encoding_level1_format.h264",
		"infotmuserdata.txt",
		0,
		0,
		1,
	    {
        	H264ENC_BYTE_STREAM,  
        	H264ENC_LEVEL_1,
        	176,           
        	144,          
        	15,    
        	1, 
        	H264ENC_COMPLEXITY_1 
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
			H264ENC_YUV420_SEMIPLANAR,
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

	},
	#endif
	
	#ifdef H264_TESTCASE_ENCODING_LEVEL_1_1
	{
		"",
		"yuv420Semiplanar_progressive_w320_h240.yuv",
		"h264_w320_h240_testcase_encoding_level11_format.h264",
		"infotmuserdata.txt",
		0,
		0,
		1,
	    {
        	H264ENC_BYTE_STREAM,  
        	H264ENC_LEVEL_1_1,
        	176,           
        	144,          
        	15,    
        	1, 
        	H264ENC_COMPLEXITY_1 
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
			H264ENC_YUV420_SEMIPLANAR,
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

	},
	#endif
	
	#ifdef H264_TESTCASE_ENCODING_LEVEL_1_2
	{
		"",
		"yuv420Semiplanar_progressive_w320_h240.yuv",
		"h264_w320_h240_testcase_encoding_level12_format.h264",
		"infotmuserdata.txt",
		0,
		0,
		1,
	    {
        	H264ENC_BYTE_STREAM,  
        	H264ENC_LEVEL_1_2,
        	176,           
        	144,          
        	15,    
        	1, 
        	H264ENC_COMPLEXITY_1 
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
			H264ENC_YUV420_SEMIPLANAR,
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

	},
	#endif
	
	#ifdef H264_TESTCASE_ENCODING_LEVEL_1_3
	{
		"",
		"yuv420Semiplanar_progressive_w320_h240.yuv",
		"h264_w320_h240_testcase_encoding_level13_format.h264",
		"infotmuserdata.txt",
		0,
		0,
		1,
	    {
        	H264ENC_BYTE_STREAM,  
        	H264ENC_LEVEL_1_3,
        	320,           
        	240,          
        	15,    
        	1, 
        	H264ENC_COMPLEXITY_1 
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
			H264ENC_YUV420_SEMIPLANAR,
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

	},
	#endif
	
	#ifdef H264_TESTCASE_ENCODING_LEVEL_2
	{
		"",
		"yuv420Semiplanar_progressive_w320_h240.yuv",
		"h264_w320_h240_testcase_encoding_level2_format.h264",
		"infotmuserdata.txt",
		0,
		0,
		1,
	    {
        	H264ENC_BYTE_STREAM,  
        	H264ENC_LEVEL_2,
        	320,           
        	240,          
        	15,    
        	1, 
        	H264ENC_COMPLEXITY_1 
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
			H264ENC_YUV420_SEMIPLANAR,
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

	},
	#endif
	
	#ifdef H264_TESTCASE_ENCODING_LEVEL_2_1
	{
		"",
		"yuv420Semiplanar_progressive_w320_h240.yuv",
		"h264_w320_h240_testcase_encoding_level21_format.h264",
		"infotmuserdata.txt",
		0,
		0,
		1,
	    {
        	H264ENC_BYTE_STREAM,  
        	H264ENC_LEVEL_2_1,
        	320,           
        	240,          
        	15,    
        	1, 
        	H264ENC_COMPLEXITY_1 
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
			H264ENC_YUV420_SEMIPLANAR,
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

	},
	#endif
	
	#ifdef H264_TESTCASE_ENCODING_LEVEL_2_2
	{
		"",
		"yuv420Semiplanar_progressive_w320_h240.yuv",
		"h264_w320_h240_testcase_encoding_level22_format.h264",
		"infotmuserdata.txt",
		0,
		0,
		1,
	    {
        	H264ENC_BYTE_STREAM,  
        	H264ENC_LEVEL_2_2,
        	320,           
        	240,          
        	15,    
        	1, 
        	H264ENC_COMPLEXITY_1 
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
			H264ENC_YUV420_SEMIPLANAR,
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

	},
	#endif
	
	#ifdef H264_TESTCASE_ENCODING_LEVEL_3
	{
		"",
		"yuv420Semiplanar_progressive_w320_h240.yuv",
		"h264_w320_h240_testcase_encoding_level3_format.h264",
		"infotmuserdata.txt",
		0,
		0,
		1,
	    {
        	H264ENC_BYTE_STREAM,  
        	H264ENC_LEVEL_3,
        	320,           
        	240,          
        	15,    
        	1, 
        	H264ENC_COMPLEXITY_1 
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
			H264ENC_YUV420_SEMIPLANAR,
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

	},
	#endif
	
	#ifdef H264_TESTCASE_ENCODING_LEVEL_3_1
	{
		"",
		"yuv420Semiplanar_progressive_w320_h240.yuv",
		"h264_w320_h240_testcase_encoding_level31_format.h264",
		"infotmuserdata.txt",
		0,
		0,
		1,
	    {
        	H264ENC_BYTE_STREAM,  
        	H264ENC_LEVEL_3_1,
        	320,           
        	240,          
        	15,    
        	1, 
        	H264ENC_COMPLEXITY_1 
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
			H264ENC_YUV420_SEMIPLANAR,
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

	},
	#endif
	
	#ifdef H264_TESTCASE_ENCODING_LEVEL_3_2
	{
		"",
		"yuv420Semiplanar_progressive_w320_h240.yuv",
		"h264_w320_h240_testcase_encoding_level32_format.h264",
		"infotmuserdata.txt",
		0,
		0,
		1,
	    {
        	H264ENC_BYTE_STREAM,  
        	H264ENC_LEVEL_3_2,
        	320,           
        	240,          
        	15,    
        	1, 
        	H264ENC_COMPLEXITY_1 
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
			H264ENC_YUV420_SEMIPLANAR,
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

	},
	#endif
	
	#ifdef H264_TESTCASE_ENCODING_LEVEL_4_0
	{
		"",
		"yuv420Semiplanar_progressive_w320_h240.yuv",
		"h264_w320_h240_testcase_encoding_level40_format.h264",
		"infotmuserdata.txt",
		0,
		0,
		1,
	    {
        	H264ENC_BYTE_STREAM,  
        	H264ENC_LEVEL_4_0,
        	320,           
        	240,          
        	15,    
        	1, 
        	H264ENC_COMPLEXITY_1 
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
			H264ENC_YUV420_SEMIPLANAR,
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

	},
	#endif
	
	#ifdef H264_TESTCASE_ENCODING_LEVEL_4_1
	{
		"",
		"yuv420Semiplanar_progressive_w320_h240.yuv",
		"h264_w320_h240_testcase_encoding_level41_format.h264",
		"infotmuserdata.txt",
		0,
		0,
		1,
	    {
        	H264ENC_BYTE_STREAM,  
        	H264ENC_LEVEL_4_1,
        	320,           
        	240,          
        	15,    
        	1, 
        	H264ENC_COMPLEXITY_1 
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
			H264ENC_YUV420_SEMIPLANAR,
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

	},
	#endif
#endif
#ifdef  H264_TESTCASE_ENCODING_TARGET_FRAMERATE
	#ifdef H264_TESTCASE_ENCODING_TARGET_FRAMERATE_1
	{
		"",
		"yuv420Semiplanar_progressive_w320_h240.yuv",
		"h264_w320_h240_testcase_encoding_target_framerate_1.h264",
		"infotmuserdata.txt",
		0,
		0,
		1,
	    {
        	H264ENC_BYTE_STREAM,  
        	H264ENC_LEVEL_1_1,
        	320,           
        	240,          
        	50,    
        	5, 
        	H264ENC_COMPLEXITY_1 
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
			H264ENC_YUV420_SEMIPLANAR,
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

	},
	#endif
	#ifdef H264_TESTCASE_ENCODING_TARGET_FRAMERATE_5
	{
		"",
		"yuv420Semiplanar_progressive_w320_h240.yuv",
		"h264_w320_h240_testcase_encoding_target_framerate_5.h264",
		"infotmuserdata.txt",
		0,
		0,
		1,
	    {
        	H264ENC_BYTE_STREAM,  
        	H264ENC_LEVEL_1_1,
        	320,           
        	240,          
        	5,//15    
        	1, //3
        	H264ENC_COMPLEXITY_1 
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
			H264ENC_YUV420_SEMIPLANAR,
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

	},
	#endif
	#ifdef H264_TESTCASE_ENCODING_TARGET_FRAMERATE_15
	{
		"",
		"yuv420Semiplanar_progressive_w320_h240.yuv",
		"h264_w320_h240_testcase_encoding_target_framerate_15.h264",
		"infotmuserdata.txt",
		0,
		0,
		1,
	    {
        	H264ENC_BYTE_STREAM,  
        	H264ENC_LEVEL_1_1,
        	320,           
        	240,          
        	15,//450    
        	1, //30
        	H264ENC_COMPLEXITY_1 
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
			H264ENC_YUV420_SEMIPLANAR,
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

	},
	#endif
	#ifdef H264_TESTCASE_ENCODING_TARGET_FRAMERATE_23
	{
		"",
		"yuv420Semiplanar_progressive_w320_h240.yuv",
		"h264_w320_h240_testcase_encoding_target_framerate_23.h264",
		"infotmuserdata.txt",
		0,
		0,
		1,
	    {
        	H264ENC_BYTE_STREAM,  
        	H264ENC_LEVEL_1_1,
        	320,           
        	240,          
        	23,//230  
        	1, //10
        	H264ENC_COMPLEXITY_1 
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
			H264ENC_YUV420_SEMIPLANAR,
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

	},
	#endif
	#ifdef H264_TESTCASE_ENCODING_TARGET_FRAMERATE_30
	{
		"",
		"yuv420Semiplanar_progressive_w320_h240.yuv",
		"h264_w320_h240_testcase_encoding_target_framerate_30.h264",
		"infotmuserdata.txt",
		0,
		0,
		1,
	    {
        	H264ENC_BYTE_STREAM,  
        	H264ENC_LEVEL_1_1,
        	320,           
        	240,          
        	30,//900    
        	1, //30
        	H264ENC_COMPLEXITY_1 
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
			H264ENC_YUV420_SEMIPLANAR,
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

	},
	#endif
	#ifdef H264_TESTCASE_ENCODING_TARGET_FRAMERATE_60
	{
		"",
		"yuv420Semiplanar_progressive_w320_h240.yuv",
		"h264_w320_h240_testcase_encoding_target_framerate_60.h264",
		"infotmuserdata.txt",
		0,
		0,
		1,
	    {
        	H264ENC_BYTE_STREAM,  
        	H264ENC_LEVEL_1_1,
        	320,           
        	240,          
        	60,//6000    
        	1, //100
        	H264ENC_COMPLEXITY_1 
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
			H264ENC_YUV420_SEMIPLANAR,
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

	},
	#endif
#endif
#ifdef H264_TESTCASE_CODING_CTRL
	#ifdef H264_TESTCASE_CODING_CTRL_SLICESIZE
	{
		"",
		"yuv420Semiplanar_progressive_w320_h240.yuv",
		"h264_w320_h240_testcase_coding_ctrl_slicesize.h264",
		"infotmuserdata.txt",
		1,
		0,
		1,
	    {
        	H264ENC_BYTE_STREAM,  
        	H264ENC_LEVEL_1_1,
        	320,           
        	240,          
        	25,//6000    
        	1, //100
        	H264ENC_COMPLEXITY_1 
    	},
    		
    	{
    		1,//sliceSize
			0xFFFFFFFF,//seiMessages
			0xFFFFFFFF,//videoFullRange
			0xFFFFFFFF,//constrainedIntraPrediction
			0xFFFFFFFF,//disableDeblockingFilter
			0xFFFFFFFF,//sampleAspectRatioWidth
			0xFFFFFFFF,//sampleAspectRatioHeight
			0xFFFFFFFF,//enableCabac
			0xFFFFFFFF,//cabacInitIdc
			0xFFFFFFFF,//transform8x8Mode
			0xFFFFFFFF//quarterPixelMv
		},
        {
			0
		},
		{
        	320,
			240,
			0,
			0,
			H264ENC_YUV420_SEMIPLANAR,
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

	},
	#endif
	#ifdef H264_TESTCASE_CODING_CTRL_SEIMESSAGES
	{
		"",
		"yuv420Semiplanar_progressive_w320_h240.yuv",
		"h264_w320_h240_testcase_coding_ctrl_seimessages.h264",
		"infotmuserdata.txt",
		1,
		0,
		1,
	    {
        	H264ENC_BYTE_STREAM,  
        	H264ENC_LEVEL_1_1,
        	320,           
        	240,          
        	25,//6000    
        	1, //100
        	H264ENC_COMPLEXITY_1 
    	},
    		
    	{
    		0xFFFFFFFF,
			1,//0xFFFFFFFF mean use default value
			0xFFFFFFFF,
			0xFFFFFFFF,
			0xFFFFFFFF,
			0xFFFFFFFF,
			0xFFFFFFFF,
			0xFFFFFFFF,
			0xFFFFFFFF,
			0xFFFFFFFF,
			0xFFFFFFFF
		},
        {
			0
		},
		{
        	320,
			240,
			0,
			0,
			H264ENC_YUV420_SEMIPLANAR,
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

	},
	#endif
	#ifdef H264_TESTCASE_CODING_CTRL_VIDEOFULLRANGE
 	{
 		"",
		"yuv420Semiplanar_progressive_w320_h240.yuv",
		"h264_w320_h240_testcase_coding_ctrl_videofullrange.h264",
		"infotmuserdata.txt",
		1,
		0,
		1,
	    {
        	H264ENC_BYTE_STREAM,  
        	H264ENC_LEVEL_1_1,
        	320,           
        	240,          
        	25,//6000    
        	1, //100
        	H264ENC_COMPLEXITY_1 
    	},
    		
    	{
    		0xFFFFFFFF,
			0xFFFFFFFF,//0xFFFFFFFF mean use default value
			1,
			0xFFFFFFFF,
			0xFFFFFFFF,
			0xFFFFFFFF,
			0xFFFFFFFF,
			0xFFFFFFFF,
			0xFFFFFFFF,
			0xFFFFFFFF,
			0xFFFFFFFF
		},
        {
			0
		},
		{
        	320,
			240,
			0,
			0,
			H264ENC_YUV420_SEMIPLANAR,
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

	},	
	#endif
	#ifdef H264_TESTCASE_CODING_CTRL_CONSTRAINEDINTRAPREDCTION
 	{
 		"",
		"yuv420Semiplanar_progressive_w320_h240.yuv",
		"h264_w320_h240_testcase_coding_ctrl_constrainedintraprediction.h264",
		"infotmuserdata.txt",
		1,
		0,
		1,
	    {
        	H264ENC_BYTE_STREAM,  
        	H264ENC_LEVEL_1_1,
        	320,           
        	240,          
        	25,//6000    
        	1, //100
        	H264ENC_COMPLEXITY_1 
    	},
    		
    	{
    		0xFFFFFFFF,
			0xFFFFFFFF,//0xFFFFFFFF mean use default value
			0xFFFFFFFF,
			1,
			0xFFFFFFFF,
			0xFFFFFFFF,
			0xFFFFFFFF,
			0xFFFFFFFF,
			0xFFFFFFFF,
			0xFFFFFFFF,
			0xFFFFFFFF
		},
        {
			0
		},
		{
        	320,
			240,
			0,
			0,
			H264ENC_YUV420_SEMIPLANAR,
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

	},	
	#endif
	#ifdef H264_TESTCASE_CODING_CTRL_DISABLEDEBLOCKINGFILTER
 	{
 		"",
		"yuv420Semiplanar_progressive_w320_h240.yuv",
		"h264_w320_h240_testcase_coding_ctrl_disableblockingfilter.h264",
		"infotmuserdata.txt",
		1,
		0,
		1,
	    {
        	H264ENC_BYTE_STREAM,  
        	H264ENC_LEVEL_1_1,
        	320,           
        	240,          
        	25,//6000    
        	1, //100
        	H264ENC_COMPLEXITY_1 
    	},
    		
    	{
    		0xFFFFFFFF,
			0xFFFFFFFF,//0xFFFFFFFF mean use default value
			0xFFFFFFFF,
			0xFFFFFFFF,
			2,
			0xFFFFFFFF,
			0xFFFFFFFF,
			0xFFFFFFFF,
			0xFFFFFFFF,
			0xFFFFFFFF,
			0xFFFFFFFF
		},
        {
			0
		},
		{
        	320,
			240,
			0,
			0,
			H264ENC_YUV420_SEMIPLANAR,
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

	},	
	#endif
	#ifdef H264_TESTCASE_CODING_CTRL_SAMPLEASPECTRATIO
 	{
 		"",
		"yuv420Semiplanar_progressive_w320_h240.yuv",
		"h264_w320_h240_testcase_coding_ctrl_sampleaspectratio.h264",
		"infotmuserdata.txt",
		1,
		0,
		1,
	    {
        	H264ENC_BYTE_STREAM,  
        	H264ENC_LEVEL_1_1,
        	320,           
        	240,          
        	25,//6000    
        	1, //100
        	H264ENC_COMPLEXITY_1 
    	},
    		
    	{
    		0xFFFFFFFF,
			0xFFFFFFFF,//0xFFFFFFFF mean use default value
			0xFFFFFFFF,
			0xFFFFFFFF,
			0xFFFFFFFF,
			400,
			33,
			0xFFFFFFFF,
			0xFFFFFFFF,
			0xFFFFFFFF,
			0xFFFFFFFF
		},
        {
			0
		},
		{
        	320,
			240,
			0,
			0,
			H264ENC_YUV420_SEMIPLANAR,
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

	},	
	#endif
	#ifdef H264_TESTCASE_CODING_CTRL_ENALBECABAC
 	{
 		"",
		"yuv420Semiplanar_progressive_w320_h240.yuv",
		"h264_w320_h240_testcase_coding_ctrl_enablecabac.h264",
		"infotmuserdata.txt",
		1,
		0,
		1,
	    {
        	H264ENC_BYTE_STREAM,  
        	H264ENC_LEVEL_1_1,
        	320,           
        	240,          
        	25,//6000    
        	1, //100
        	H264ENC_COMPLEXITY_1 
    	},
    		
    	{
    		0xFFFFFFFF,//sliceSize
			0xFFFFFFFF,//seiMessages
			0xFFFFFFFF,//videoFullRange
			0xFFFFFFFF,//constrainedIntraPrediction
			0xFFFFFFFF,//disableDeblockingFilter
			0xFFFFFFFF,//sampleAspectRatioWidth
			0xFFFFFFFF,//sampleAspectRatioHeight
			1,			//enableCabac
			2,//cabac table
			0xFFFFFFFF,//transform8x8Mode
			0xFFFFFFFF//quarterPixelMv
		},
        {
			0
		},
		{
        	320,
			240,
			0,
			0,
			H264ENC_YUV420_SEMIPLANAR,
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

	},	
	#endif
	#ifdef H264_TESTCASE_CODING_CTRL_TRANSFROM8x8MODE
 	{
 		"",
		"yuv420Semiplanar_progressive_w320_h240.yuv",
		"h264_w320_h240_testcase_coding_ctrl_transfrom8x8mode.h264",
		"infotmuserdata.txt",
		1,
		0,
		1,
	    {
        	H264ENC_BYTE_STREAM,  
        	H264ENC_LEVEL_1_1,
        	320,           
        	240,          
        	25,//6000    
        	1, //100
        	H264ENC_COMPLEXITY_1 
    	},
    		
    	{
    		0xFFFFFFFF,
			0xFFFFFFFF,//0xFFFFFFFF mean use default value
			0xFFFFFFFF,
			0xFFFFFFFF,
			0xFFFFFFFF,
			0xFFFFFFFF,
			0xFFFFFFFF,
			0xFFFFFFFF,
			0xFFFFFFFF,
			2,
			0xFFFFFFFF
		},
        {
			0
		},
		{
        	320,
			240,
			0,
			0,
			H264ENC_YUV420_SEMIPLANAR,
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

	},	
	#endif
	#ifdef H264_TESTCASE_CODING_CTRL_QUARTERPIXELMV
 	{
 		"",
		"yuv420Semiplanar_progressive_w320_h240.yuv",
		"h264_w320_h240_testcase_coding_ctrl_quarterpixelmv.h264",
		"infotmuserdata.txt",
		1,
		0,
		1,
	    {
        	H264ENC_BYTE_STREAM,  
        	H264ENC_LEVEL_1_1,
        	320,           
        	240,          
        	25,//6000    
        	1, //100
        	H264ENC_COMPLEXITY_1 
    	},
    		
    	{
    		0xFFFFFFFF,
			0xFFFFFFFF,//0xFFFFFFFF mean use default value
			0xFFFFFFFF,
			0xFFFFFFFF,
			0xFFFFFFFF,
			0xFFFFFFFF,
			0xFFFFFFFF,
			0xFFFFFFFF,
			0xFFFFFFFF,
			0xFFFFFFFF,
			2
		},
        {
			0
		},
		{
        	320,
			240,
			0,
			0,
			H264ENC_YUV420_SEMIPLANAR,
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

	},	
	#endif
#endif

#ifdef H264_TESTCASE_RATE_CTRL
	#ifdef  H264_TESTCASE_RATE_CTRL_CBR
 	{
 		"",
		"h264_w720_h576_testcase_rate_ctrl_rgb565.rgb",
		"h264_w720_h576_testcase_rate_ctrl_cbr.h264",
		"infotmuserdata.txt",
		0,
		1,
		1,
	    {
        	H264ENC_BYTE_STREAM,  
        	H264ENC_LEVEL_3,
        	720,           
        	576,          
        	25,//6000    
        	1, //100
        	H264ENC_COMPLEXITY_1 
    	},
    		
    	{
			0	
		},
        {
			0,//pictureRc
			0,//mbRc
			0,//pictureSkip
			20,//qpHdr,in this case,this should not be alert
			10,//qpMin
			50,//qpMax
			0xFFFFFFFF,//bitPerSecond,the this case ,we do not set this
			0,//hrd
			0xFFFFFFFF,//hrdCpbSize
			0xFFFFFFFF,//gopLen
			0xFFFFFFFF,//intraQpDelta
			0xFFFFFFFF,//fixedIntraQp
			0xFFFFFFFF,//mbQpAdjustment
			
		},
		{
        	720,
			576,
			0,
			0,
			H264ENC_RGB565,
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
	},	
	#endif
	#ifdef  H264_TESTCASE_RATE_CTRL_VBR_PB
 	{
 		"",
		"h264_w720_h576_testcase_rate_ctrl_rgb565.rgb",
		"h264_w720_h576_testcase_rate_ctrl_vbr_pb.h264",
		"infotmuserdata.txt",
		0,
		1,
		1,
	    {
        	H264ENC_BYTE_STREAM,  
        	H264ENC_LEVEL_3,
        	720,           
        	576,          
        	25,//6000    
        	1, //100
        	H264ENC_COMPLEXITY_1 
    	},
    		
    	{
			0	
		},
        {
			1,//pictureRc
			0,//mbRc
			0,//pictureSkip
			-1,
			0xFFFFFFFF,//qpMin
			0xFFFFFFFF,//qpMax
			10000000,//bitPerSecond,the target bps we want
			0,//hrd
			0xFFFFFFFF,//hrdCpbSize
			0xFFFFFFFF,//gopLen
			0xFFFFFFFF,//intraQpDelta
			0xFFFFFFFF,//fixedIntraQp
			0xFFFFFFFF,//mbQpAdjustment
			
		},
		{
        	720,
			576,
			0,
			0,
			H264ENC_RGB565,
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
	},	
	#endif
	#ifdef  H264_TESTCASE_RATE_CTRL_VBR_MB
 	{
 		"",
		"h264_w720_h576_testcase_rate_ctrl_rgb565.rgb",
		"h264_w720_h576_testcase_rate_ctrl_vbr_mb.h264",
		"infotmuserdata.txt",
		0,
		1,
		1,
	    {
        	H264ENC_BYTE_STREAM,  
        	H264ENC_LEVEL_3,
        	720,           
        	576,          
        	25,//6000    
        	1, //100
        	H264ENC_COMPLEXITY_1 
    	},
    		
    	{
			0	
		},
        {
			0,//pictureRc
			1,//mbRc
			0,//pictureSkip
			-1,//qpHdr
			0xFFFFFFFF,//qpMin
			0xFFFFFFFF,//qpMax
			10000000,//bitPerSecond,the target bps we want
			0,//hrd
			0xFFFFFFFF,//hrdCpbSize
			0xFFFFFFFF,//gopLen
			0xFFFFFFFF,//intraQpDelta
			0xFFFFFFFF,//fixedIntraQp
			0,//mbQpAdjustment//enable mbqpAdujustment will disable mb rate control
			
		},
		{
        	720,
			576,
			0,
			0,
			H264ENC_RGB565,
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
	},	
	#endif
	#ifdef  H264_TESTCASE_RATE_CTRL_VBR_SKIP_PIC
 	{
 		"",
		"h264_w720_h576_testcase_rate_ctrl_rgb565.rgb",
		"h264_w720_h576_testcase_rate_ctrl_vbr_skip_pic.h264",
		"infotmuserdata.txt",
		0,
		1,
		1,
	    {
        	H264ENC_BYTE_STREAM,  
        	H264ENC_LEVEL_3,
        	720,           
        	576,          
        	25,//6000    
        	1, //100
        	H264ENC_COMPLEXITY_1 
    	},
    		
    	{
			0	
		},
        {
			0,//pictureRc
			0,//mbRc
			1,//pictureSkip
			-1,//qpHdr
			0xFFFFFFFF,//qpMin
			0xFFFFFFFF,//qpMax
			10000000,//bitPerSecond,the target bps we want,make the small to make our encoder skip picture
			0,//hrd
			0xFFFFFFFF,//hrdCpbSize
			0xFFFFFFFF,//gopLen
			0xFFFFFFFF,//intraQpDelta
			0xFFFFFFFF,//fixedIntraQp
			0xFFFFFFFF,//mbQpAdjustment//enable mbqpAdujustment will disable mb rate control
			
		},
		{
        	720,
			576,
			0,
			0,
			H264ENC_RGB565,
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
	},	
	#endif
	#ifdef  H264_TESTCASE_RATE_CTRL_VBR_HDR
 	{
 		"",
		"h264_w720_h576_testcase_rate_ctrl_rgb565.rgb",
		"h264_w720_h576_testcase_rate_ctrl_vbr_hdr.h264",
		"infotmuserdata.txt",
		0,
		1,
		1,
	    {
        	H264ENC_BYTE_STREAM,  
        	H264ENC_LEVEL_3,
        	720,           
        	576,          
        	25,//6000    
        	1, //100
        	H264ENC_COMPLEXITY_1 
    	},
    		
    	{
			0	
		},
        {
			0xFFFFFFFF,//pictureRc
			0xFFFFFFFF,//mbRc
			0xFFFFFFFF,//pictureSkip
			-1,//qpHdr
			0xFFFFFFFF,//qpMin
			0xFFFFFFFF,//qpMax
			0xFFFFFFFF,//bitPerSecond,the target bps we want
			1,//hrd
			0xFFFFFFFF,//hrdCpbSize
			0xFFFFFFFF,//gopLen
			0xFFFFFFFF,//intraQpDelta
			0xFFFFFFFF,//fixedIntraQp
			0xFFFFFFFF,//mbQpAdjustment//enable mbqpAdujustment will disable mb rate control
			
		},
		{
        	720,
			576,
			0,
			0,
			H264ENC_RGB565,
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
	},	
	#endif
	#ifdef H264_TESTCASE_RATE_CTRL_IQPDELTA
 	{
 		"",
		"h264_w720_h576_testcase_rate_ctrl_rgb565.rgb",
		"h264_w720_h576_testcase_rate_ctrl_iqpdelta.h264",
		"infotmuserdata.txt",
		0,
		1,
		1,
	    {
        	H264ENC_BYTE_STREAM,  
        	H264ENC_LEVEL_3,
        	720,           
        	576,          
        	25,//6000    
        	1, //100
        	H264ENC_COMPLEXITY_1 
    	},
    		
    	{
			0	
		},
        {
			0xFFFFFFFF,//pictureRc
			0xFFFFFFFF,//mbRc
			0xFFFFFFFF,//pictureSkip
			0xFFFFFFFF,//qpHdr
			0xFFFFFFFF,//qpMin
			0xFFFFFFFF,//qpMax
			0xFFFFFFFF,//bitPerSecond,the target bps we want
			0xFFFFFFFF,//hrd
			0xFFFFFFFF,//hrdCpbSize
			0xFFFFFFFF,//gopLen
			-12,//intraQpDelta
			0xFFFFFFFF,//fixedIntraQp
			0xFFFFFFFF,//mbQpAdjustment//enable mbqpAdujustment will disable mb rate control
			
		},
		{
        	720,
			576,
			0,
			0,
			H264ENC_RGB565,
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
	},
	#endif
	#ifdef H264_TESTCASE_RATE_CTRL_IQIPFIXED
 	{
 		"",
		"h264_w720_h576_testcase_rate_ctrl_rgb565.rgb",
		"h264_w720_h576_testcase_rate_ctrl_iqpfixed.h264",
		"infotmuserdata.txt",
		0,
		1,
		1,
	    {
        	H264ENC_BYTE_STREAM,  
        	H264ENC_LEVEL_3,
        	720,           
        	576,          
        	25,//6000    
        	1, //100
        	H264ENC_COMPLEXITY_1 
    	},
    		
    	{
			0	
		},
        {
			0xFFFFFFFF,//pictureRc
			0xFFFFFFFF,//mbRc
			0xFFFFFFFF,//pictureSkip
			0xFFFFFFFF,//qpHdr
			0xFFFFFFFF,//qpMin
			0xFFFFFFFF,//qpMax
			0xFFFFFFFF,//bitPerSecond,the target bps we want
			0xFFFFFFFF,//hrd
			0xFFFFFFFF,//hrdCpbSize
			0xFFFFFFFF,//gopLen
			0xFFFFFFFF,//intraQpDelta
			30,//fixedIntraQp
			0xFFFFFFFF,//mbQpAdjustment//enable mbqpAdujustment will disable mb rate control
			
		},
		{
        	720,
			576,
			0,
			0,
			H264ENC_RGB565,
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
	},
	#endif
	#ifdef H264_TESTCASE_RATE_CTRL_MBQPADJUST
 	{
 		"",
		"h264_w720_h576_testcase_rate_ctrl_rgb565.rgb",
		"h264_w720_h576_testcase_rate_ctrl_mbqpadust.h264",
		"infotmuserdata.txt",
		0,
		1,
		1,
	    {
        	H264ENC_BYTE_STREAM,  
        	H264ENC_LEVEL_3,
        	720,           
        	576,          
        	25,//6000    
        	1, //100
        	H264ENC_COMPLEXITY_1 
    	},
    		
    	{
			0	
		},
        {
			0xFFFFFFFF,//pictureRc
			0xFFFFFFFF,//mbRc
			0xFFFFFFFF,//pictureSkip
			0xFFFFFFFF,//qpHdr
			0xFFFFFFFF,//qpMin
			0xFFFFFFFF,//qpMax
			0xFFFFFFFF,//bitPerSecond,the target bps we want
			0xFFFFFFFF,//hrd
			0xFFFFFFFF,//hrdCpbSize
			0xFFFFFFFF,//gopLen
			0xFFFFFFFF,//intraQpDelta
			0xFFFFFFFF,//fixedIntraQp
			-4,//mbQpAdjustment//enable mbqpAdujustment will disable mb rate control
			
		},
		{
        	720,
			576,
			0,
			0,
			H264ENC_RGB565,
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
	},
	#endif
#endif
#ifdef H264_TESTCASE_PRE_PROC
	#ifdef  H264_TESTCASE_PRE_PROC_SIZE
 	{
 		"",
		"h264_w96_h96_testcase_preproc_size_yuv420sp.yuv",
		"h264_w96_h96_testcase_preproc.h264",
		"infotmuserdata.txt",
		0,
		0,
		1,
	    {
        	H264ENC_BYTE_STREAM,  
        	H264ENC_LEVEL_1,
        	96,           
        	96,          
        	15,//6000    
        	1, //100
        	H264ENC_COMPLEXITY_1 
    	},
    		
    	{
			0	
		},
        {
			0			
		},
		{
        	96,
			96,
			0,
			0,
			H264ENC_YUV420_SEMIPLANAR,
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
	},
	{
		"",
		"yuv420Semiplanar_progressive_w640_h480.yuv",
		"h264_w352_h288_testcase_preproc.h264",
		"infotmuserdata.txt",
		0,
		0,
		1,
	    {
        	H264ENC_BYTE_STREAM,  
        	H264ENC_LEVEL_2,
        	352,           
        	288,          
        	15,//6000    
        	1, //100
        	H264ENC_COMPLEXITY_1 
    	},
    		
    	{
			0	
		},
        {
			0			
		},
		{
        	640,
			480,
			0,
			0,
			H264ENC_YUV420_SEMIPLANAR,
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
	},
	
	
	{
		"",
		"h264_w648_h482_testcase_preproc_size_yuv420sp.yuv",
		"h264_w648_h482_testcase_preproc.h264",
		"infotmuserdata.txt",
		0,
		0,
		1,
	    {
        	H264ENC_BYTE_STREAM,  
        	H264ENC_LEVEL_3,
        	480,           
        	320,          
        	30,//6000    
        	1, //100
        	H264ENC_COMPLEXITY_1 
    	},
    	{
			0	
		},
        {
			0			
		},
		{
        	648,
			482,
			VENC_RANDOM_VALUE,
			VENC_RANDOM_VALUE,
			H264ENC_YUV420_SEMIPLANAR,
			VENC_RANDOM_VALUE,//H264ENC_ROTATE_0,
			1,
        	{
				H264ENC_RGBTOYUV_BT601,
				0,
				0,
				0,
				0,
				0
			}
		}
	},
	{
		"",
		"h264_w800_h600_testcase_preproc_size_yuv420sp.yuv",
		"h264_w800_h600_testcase_preproc.h264",
		"infotmuserdata.txt",
		0,
		0,
		1,
	    {
        	H264ENC_BYTE_STREAM,  
        	H264ENC_LEVEL_3_1,
        	320,           
        	240,          
        	30,//6000    
        	1, //100
        	H264ENC_COMPLEXITY_1 
    	},
    		
    	{
			0	
		},
        {
			0			
		},
		{
        	800,
			600,
			VENC_RANDOM_VALUE,
			VENC_RANDOM_VALUE,
			H264ENC_YUV420_SEMIPLANAR,
			H264ENC_ROTATE_90L,
			1,
        	{
				H264ENC_RGBTOYUV_BT601,
				0,
				0,
				0,
				0,
				0
			}
		}
	},
	{
		"",
		"h264_w1280_h720_testcase_preproc_size_yuv420sp.yuv",
		"h264_w1280_h720_testcase_preproc.h264",
		"infotmuserdata.txt",
		0,
		0,
		1,
	    {
        	H264ENC_BYTE_STREAM,  
        	H264ENC_LEVEL_3_1,
        	1280,           
        	720,          
        	15,//6000    
        	1, //100
        	H264ENC_COMPLEXITY_1 
    	},
    		
    	{
			0	
		},
        {
			0			
		},
		{
        	1280,
			720,
			0,
			0,
			H264ENC_YUV420_SEMIPLANAR,
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
	},
	{
		"",
		"h264_w1920_h1080_testcase_preproc_size_yuv420sp.yuv",
		"h264_w1920_h1080_testcase_preproc.h264",
		"infotmuserdata.txt",
		0,
		0,
		1,
	    {
        	H264ENC_BYTE_STREAM,  
        	H264ENC_LEVEL_4_1,
        	1920,           
        	1080,          
        	15,//6000    
        	1, //100
        	H264ENC_COMPLEXITY_1 
    	},
    		
    	{
			0	
		},
        {
			0			
		},
		{
        	1920,
			1080,
			0,
			0,
			H264ENC_YUV420_SEMIPLANAR,
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
	},
	#endif
	#ifdef H264_TESTCASE_PRE_PROC_FORMAT
 	{
 		"",
		"h264_w640_h480_testcase_preproc_format_yuyv422.yuv",
		"h264_w640_h480_testcase_preproc_format_yuyv422.h264",
		"infotmuserdata.txt",
		0,
		0,
		1,
	    {
        	H264ENC_BYTE_STREAM,  
        	H264ENC_LEVEL_3,
        	640,           
        	480,          
        	15,//6000    
        	1, //100
        	H264ENC_COMPLEXITY_1 
    	},
    		
    	{
			0	
		},
        {
			0			
		},
		{
        	640,
			480,
			0,
			0,
			H264ENC_YUV422_INTERLEAVED_YUYV,
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
	},
	{
		"",
		"h264_w640_h480_testcase_preproc_format_uyvy422.yuv",
		"h264_w640_h480_testcase_preproc_format_uvvy422.h264",
		"infotmuserdata.txt",
		0,
		0,
		1,
	    {
        	H264ENC_BYTE_STREAM,  
        	H264ENC_LEVEL_3,
        	640,           
        	480,          
        	15,//6000    
        	1, //100
        	H264ENC_COMPLEXITY_1 
    	},
    		
    	{
			0	
		},
        {
			0			
		},
		{
        	640,
			480,
			0,
			0,
			H264ENC_YUV422_INTERLEAVED_UYVY,
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
	},
	{
		"",
		"h264_w640_h480_testcase_preproc_format_rgb565.rgb",
		"h264_w640_h480_testcase_preproc_format_rgb565.h264",
		"infotmuserdata.txt",
		0,
		0,
		1,
	    {
        	H264ENC_BYTE_STREAM,  
        	H264ENC_LEVEL_3,
        	640,           
        	480,          
        	15,//6000    
        	1, //100
        	H264ENC_COMPLEXITY_1 
    	},
    		
    	{
			0	
		},
        {
			0			
		},
		{
        	640,
			480,
			0,
			0,
			H264ENC_RGB565,
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
	},
	{
		"",
		"h264_w640_h480_testcase_preproc_format_bgr565.rgb",
		"h264_w640_h480_testcase_preproc_format_bgr565.h264",
		"infotmuserdata.txt",
		0,
		0,
		1,
	    {
        	H264ENC_BYTE_STREAM,  
        	H264ENC_LEVEL_3,
        	640,           
        	480,          
        	15,//6000    
        	1, //100
        	H264ENC_COMPLEXITY_1 
    	},
    		
    	{
			0	
		},
        {
			0			
		},
		{
        	640,
			480,
			0,
			0,
			H264ENC_BGR565,
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
	},
	{
		"",
		"h264_w640_h480_testcase_preproc_format_rgb555.rgb",
		"h264_w640_h480_testcase_preproc_format_rgb555.h264",
		"infotmuserdata.txt",
		0,
		0,
		1,
	    {
        	H264ENC_BYTE_STREAM,  
        	H264ENC_LEVEL_3,
        	640,           
        	480,          
        	15,//6000    
        	1, //100
        	H264ENC_COMPLEXITY_1 
    	},
    		
    	{
			0	
		},
        {
			0			
		},
		{
        	640,
			480,
			0,
			0,
			H264ENC_RGB555,
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
	},
	{
		"",
		"h264_w640_h480_testcase_preproc_format_bgr555.rgb",
		"h264_w640_h480_testcase_preproc_format_bgr555.h264",
		"infotmuserdata.txt",
		0,
		0,
		1,
	    {
        	H264ENC_BYTE_STREAM,  
        	H264ENC_LEVEL_3,
        	640,           
        	480,          
        	15,//6000    
        	1, //100
        	H264ENC_COMPLEXITY_1 
    	},
    		
    	{
			0	
		},
        {
			0			
		},
		{
        	640,
			480,
			0,
			0,
			H264ENC_BGR555,
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
	},
	{
		"",
		"h264_w640_h480_testcase_preproc_format_rgb444.rgb",
		"h264_w640_h480_testcase_preproc_format_rgb444.h264",
		"infotmuserdata.txt",
		0,
		0,
		1,
	    {
        	H264ENC_BYTE_STREAM,  
        	H264ENC_LEVEL_3,
        	640,           
        	480,          
        	15,//6000    
        	1, //100
        	H264ENC_COMPLEXITY_1 
    	},
    		
    	{
			0	
		},
        {
			0			
		},
		{
        	640,
			480,
			0,
			0,
			H264ENC_RGB444,
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
	},
	{
		"",
		"h264_w640_h480_testcase_preproc_format_bgr444.rgb",
		"h264_w640_h480_testcase_preproc_format_bgr444.h264",
		"infotmuserdata.txt",
		0,
		0,
		1,
	    {
        	H264ENC_BYTE_STREAM,  
        	H264ENC_LEVEL_3,
        	640,           
        	480,          
        	15,//6000    
        	1, //100
        	H264ENC_COMPLEXITY_1 
    	},
    		
    	{
			0	
		},
        {
			0			
		},
		{
        	640,
			480,
			0,
			0,
			H264ENC_BGR444,
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
	},
	{
		"",
		"h264_w640_h480_testcase_preproc_format_rgb888.rgb",
		"h264_w640_h480_testcase_preproc_format_rgb888.h264",
		"infotmuserdata.txt",
		0,
		0,
		1,
	    {
        	H264ENC_BYTE_STREAM,  
        	H264ENC_LEVEL_3,
        	640,           
        	480,          
        	15,//6000    
        	1, //100
        	H264ENC_COMPLEXITY_1 
    	},
    		
    	{
			0	
		},
        {
			0			
		},
		{
        	640,
			480,
			0,
			0,
			H264ENC_RGB888,
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
	},
	{
		"",
		"h264_w640_h480_testcase_preproc_format_bgr888.rgb",
		"h264_w640_h480_testcase_preproc_format_bgr888.h264",
		"infotmuserdata.txt",
		0,
		0,
		1,
	    {
        	H264ENC_BYTE_STREAM,  
        	H264ENC_LEVEL_3,
        	640,           
        	480,          
        	15,//6000    
        	1, //100
        	H264ENC_COMPLEXITY_1 
    	},
    		
    	{
			0	
		},
        {
			0			
		},
		{
        	640,
			480,
			0,
			0,
			H264ENC_BGR888,
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
	},
	{
		"",
		"h264_w640_h480_testcase_preproc_format_rgb101010.rgb",
		"h264_w640_h480_testcase_preproc_format_rgb101010.h264",
		"infotmuserdata.txt",
		0,
		0,
		1,
	    {
        	H264ENC_BYTE_STREAM,  
        	H264ENC_LEVEL_3,
        	640,           
        	480,          
        	15,//6000    
        	1, //100
        	H264ENC_COMPLEXITY_1 
    	},
    		
    	{
			0	
		},
        {
			0			
		},
		{
        	640,
			480,
			0,
			0,
			H264ENC_RGB101010,
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
	},
	{
		"",
		"h264_w640_h480_testcase_preproc_format_bgr101010.rgb",
		"h264_w640_h480_testcase_preproc_format_bgr101010.h264",
		"infotmuserdata.txt",
		0,
		0,
		1,
	    {
        	H264ENC_BYTE_STREAM,  
        	H264ENC_LEVEL_3,
        	640,           
        	480,          
        	15,//6000    
        	1, //100
        	H264ENC_COMPLEXITY_1 
    	},
    		
    	{
			0	
		},
        {
			0			
		},
		{
        	640,
			480,
			0,
			0,
			H264ENC_BGR101010,
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
	},
   	#endif
	
	#ifdef H264_TESTCASE_PRE_PROC_ROTATION
	{
		"",
		"h264_w640_h480_testcase_preproc_format_bgr101010.rgb",
		"h264_w640_h480_testcase_preproc_rotation90L.h264",
		"infotmuserdata.txt",
		0,
		0,
		1,
	    {
        	H264ENC_BYTE_STREAM,  
        	H264ENC_LEVEL_3,
        	480,           
        	640,          
        	15,//6000    
        	1, //100
        	H264ENC_COMPLEXITY_1 
    	},
    		
    	{
			0	
		},
        {
			0			
		},
		{
        	640,
			480,
			0,
			0,
			H264ENC_BGR101010,
			H264ENC_ROTATE_90L,
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
	},
	{
		"",
		"h264_w640_h480_testcase_preproc_format_bgr101010.rgb",
		"h264_w640_h480_testcase_preproc_rotation90R.h264",
		"infotmuserdata.txt",
		0,
		0,
		1,
	    {
        	H264ENC_BYTE_STREAM,  
        	H264ENC_LEVEL_3,
        	480,           
        	640,          
        	15,//6000    
        	1, //100
        	H264ENC_COMPLEXITY_1 
    	},
    		
    	{
			0	
		},
        {
			0			
		},
		{
        	640,
			480,
			0,
			0,
			H264ENC_BGR101010,
			H264ENC_ROTATE_90R,
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
	},	
	#endif
	#ifdef H264_TESTCASE_PRE_PROC_VIDEOSTABILIZATION
	{
		"",
		"camstab_w104_h104_yuv420sp.yuv",
		"h264_w00_h00_testcase_preproc_videostabilization.h264",
		"infotmuserdata.txt",
		0,
		0,
		1,
	    {
        	H264ENC_BYTE_STREAM,  
        	H264ENC_LEVEL_1,
        	96,           
        	96,          
        	15,//6000    
        	1, //100
        	H264ENC_COMPLEXITY_1 
    	},
    		
    	{
			0	
		},
        {
			0			
		},
		{
        	104,
			104,
			0,
			0,
			H264ENC_YUV420_SEMIPLANAR,
			H264ENC_ROTATE_0,
			1,
        	{
				H264ENC_RGBTOYUV_BT601,
				0,
				0,
				0,
				0,
				0
			}
		}
	},
	#endif
	#ifdef H264_TESTCASE_PRE_PROC_CROP
	{
		"",
		"h264_w640_h480_testcase_preproc_format_rgb565.rgb",
		"h264_w320_h240_testcase_preproc_crop.h264",
		"infotmuserdata.txt",
		0,
		0,
		1,
	    {
        	H264ENC_BYTE_STREAM,  
        	H264ENC_LEVEL_3,
        	320,           
        	240,          
        	15,//6000    
        	1, //100
        	H264ENC_COMPLEXITY_1 
    	},
    		
    	{
			0	
		},
        {
			0			
		},
		{
        	640,
			480,
			120,
			120,
			H264ENC_RGB565,
			H264ENC_ROTATE_90L,
			0,
        	{
				H264ENC_RGBTOYUV_USER_DEFINED,
				19589,
				38443,
				7504,
				37008,
				40740
			}
		}
	},
	#endif

#endif

#ifdef H264_TESTCASE_INPUT_ISP
	/*{
		"",
		"dma_RGB565_640_480.bin",
		"dma_RGB565_640_480.h264",
		"infotmuserdata.txt",
		0,
		0,
		1,
		
	    	{
        	H264ENC_BYTE_STREAM,  
        	H264ENC_LEVEL_4_1,
        	640,           
        	480,          
        	15,//6000    
        	1, //100
        	H264ENC_COMPLEXITY_1 
    		},
    		
    		{
		0	
		},
		
        	{
		0			
		},
		
		{
        	640,
		480,
		0,
		0,
		H264ENC_RGB565,
		H264ENC_ROTATE_0,
		0,
        		{
			H264ENC_RGBTOYUV_USER_DEFINED,
			19589,
			38443,
			7504,
			37008,
			40740
			}
		}
	},

	{
		"",
		"dma_RGB565_1280_960.bin",
		"dma_RGB565_1280_960.h264",
		"infotmuserdata.txt",
		0,
		0,
		1,
		
	    	{
        	H264ENC_BYTE_STREAM,  
        	H264ENC_LEVEL_4_1,
        	1280,           
        	960,          
        	15,//6000    
        	1, //100
        	H264ENC_COMPLEXITY_1 
    		},
    		
    		{
		0	
		},
		
        	{
		0			
		},
		
		{
        	1280,
		960,
		0,
		0,
		H264ENC_RGB565,
		H264ENC_ROTATE_0,
		0,
        		{
			H264ENC_RGBTOYUV_USER_DEFINED,
			19589,
			38443,
			7504,
			37008,
			40740
			}
		}
	},	

	{
		"",
		"dma_UYVY422_1280_960.bin",
		"dma_UYVY422_1280_960.h264",
		"infotmuserdata.txt",
		0,
		0,
		1,
		
	    	{
        	H264ENC_BYTE_STREAM,  
        	H264ENC_LEVEL_4_1,
        	1280,           
        	960,          
        	15,//6000    
        	1, //100
        	H264ENC_COMPLEXITY_1 
    		},
    		
    		{
		0	
		},
		
        	{
		0			
		},
		
		{
        	1280,
		960,
		0,
		0,
		H264ENC_YUV422_INTERLEAVED_UYVY,
		H264ENC_ROTATE_0,
		0,
        		{
			H264ENC_RGBTOYUV_USER_DEFINED,
			19589,
			38443,
			7504,
			37008,
			40740
			}
		}
	},	

	{
		"",
		"dma_YUYV422_1280_960.bin",
		"dma_YUYV422_1280_960.h264",
		"infotmuserdata.txt",
		0,
		0,
		1,
		
	    	{
        	H264ENC_BYTE_STREAM,  
        	H264ENC_LEVEL_4_1,
        	1280,           
        	960,          
        	15,//6000    
        	1, //100
        	H264ENC_COMPLEXITY_1 
    		},
    		
    		{
		0	
		},
		
        	{
		0			
		},
		
		{
        	1280,
		960,
		0,
		0,
		H264ENC_YUV422_INTERLEAVED_YUYV,
		H264ENC_ROTATE_0,
		0,
        		{
			H264ENC_RGBTOYUV_USER_DEFINED,
			19589,
			38443,
			7504,
			37008,
			40740
			}
		}
	},		

	{
		"",
		"isp_rgb888_640_480.bin",
		"isp_rgb888_640_480.h264",
		"infotmuserdata.txt",
		0,
		0,
		1,
		
	    	{
        	H264ENC_BYTE_STREAM,  
        	H264ENC_LEVEL_4_1,
        	640,           
        	480,          
        	15,//6000    
        	1, //100
        	H264ENC_COMPLEXITY_1 
    		},
    		
    		{
		0	
		},
		
        	{
		0			
		},
		
		{
        	640,
		480,
		0,
		0,
		H264ENC_RGB888,
		H264ENC_ROTATE_0,
		0,
        		{
			H264ENC_RGBTOYUV_USER_DEFINED,
			19589,
			38443,
			7504,
			37008,
			40740
			}
		}
	},	

	{
		"",
		"isp_yuv420p_640_480.bin",
		"isp_yuv420p_640_480.h264",
		"infotmuserdata.txt",
		0,
		0,
		1,
		
	    	{
        	H264ENC_BYTE_STREAM,  
        	H264ENC_LEVEL_4_1,
        	640,           
        	480,          
        	15,//6000    
        	1, //100
        	H264ENC_COMPLEXITY_1 
    		},
    		
    		{
		0	
		},
		
        	{
		0			
		},
		
		{
        	640,
		480,
		0,
		0,
		H264ENC_YUV420_PLANAR,
		H264ENC_ROTATE_0,
		0,
        		{
			H264ENC_RGBTOYUV_USER_DEFINED,
			19589,
			38443,
			7504,
			37008,
			40740
			}
		}
	},*/

	{
		"",
		"isp_yuv420p_2592_1944.bin",
		"isp_yuv420p_2592_1944.h264",
		"infotmuserdata.txt",
		0,
		0,
		1,
		
	    	{
        	H264ENC_BYTE_STREAM,  
        	H264ENC_LEVEL_4_1,
        	1920,           
        	1088,          
        	15,//6000    
        	1, //100
        	H264ENC_COMPLEXITY_1 
    		},
    		
    		{
		0	
		},
		
        	{
		0			
		},
		
		{
        	2592,
		1944,
		0,
		0,
		H264ENC_YUV420_PLANAR,
		H264ENC_ROTATE_0,
		0,
        		{
			H264ENC_RGBTOYUV_USER_DEFINED,
			19589,
			38443,
			7504,
			37008,
			40740
			}
		}
	},

	{
		"",
		"isp_yuv420sp_2592_1944.bin",
		"isp_yuv420sp_2592_1944.h264",
		"infotmuserdata.txt",
		0,
		0,
		1,
		
	    	{
        	H264ENC_BYTE_STREAM,  
        	H264ENC_LEVEL_4_1,
        	1920,           
        	1088,          
        	15,//6000    
        	1, //100
        	H264ENC_COMPLEXITY_1 
    		},
    		
    		{
		0	
		},
		
        	{
		0			
		},
		
		{
        	2592,
		1944,
		0,
		0,
		H264ENC_YUV420_SEMIPLANAR,
		H264ENC_ROTATE_0,
		0,
        		{
			H264ENC_RGBTOYUV_USER_DEFINED,
			19589,
			38443,
			7504,
			37008,
			40740
			}
		}
	},
#endif

#ifdef H264_TESTCASE_PERFORMANCE
	{
		"",
		"w640_h480_bgr565.rgb16",
		"h264_w100_h480_testcase_performance.h264",
		"infotmuserdata.txt",
		0,
		1,
		1,
	    	{
        		H264ENC_BYTE_STREAM,  
        		H264ENC_LEVEL_3,
        		640,           
        		480,          
        		30,//6000    
        		1, //100
        		H264ENC_COMPLEXITY_1 
    		},
    		
    		{
			0	
		},
        	{
			0xFFFFFFFF,//pictureRc
			0xFFFFFFFF,//mbRc
			0xFFFFFFFF,//pictureSkip
			0xFFFFFFFF,//qpHdr,in this case,this should not be alert
			0xFFFFFFFF,//qpMin
			0xFFFFFFFF,//qpMax
			10000*1200,//bitPerSecond,max bitrate
			0xFFFFFFFF,//hrd
			0xFFFFFFFF,//hrdCpbSize
			0xFFFFFFFF,//gopLen
			0xFFFFFFFF,//intraQpDelta
			0xFFFFFFFF,//fixedIntraQp
			0xFFFFFFFF,//mbQpAdjustment
			
		},
		{
        		640,
			480,
			0,
			0,
			H264ENC_BGR565,
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
	},

#endif

#ifdef H264_RTLCASE
/*	#ifdef H264_RTLCASE_40_NAL_FORMAT
	{
		"case40",
		"yuv420Semiplanar_progressive_w320_h240.yuv",
		"h264_w320_h240_testcase_encoding_nal_format.h264",
		"infotmuserdata.txt",
		0,
		0,
		1,

	    {
        	H264ENC_NAL_UNIT_STREAM,
        	H264ENC_LEVEL_1_1,
        	160,
        	120,
        	15,
        	1,
        	H264ENC_COMPLEXITY_1
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
			H264ENC_YUV420_SEMIPLANAR,
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

	},
	#endif*/
	#ifdef H264_RTLCASE_41_LEVEL_1_2
	{
		"case41",
		"yuv420Semiplanar_progressive_w320_h240.yuv",
		"h264_w320_h240_testcase_encoding_level12_format.h264",
		"infotmuserdata.txt",
		0,
		0,
		1,
	    {
        	H264ENC_BYTE_STREAM,  
        	H264ENC_LEVEL_1_2,
        	176,           
        	144,          
        	15,    
        	1, 
        	H264ENC_COMPLEXITY_1 
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
			H264ENC_YUV420_SEMIPLANAR,
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

	},
	#endif
	#ifdef H264_RTLCASE_42_LEVEL_4_1
	{
		"case42",
		"yuv420Semiplanar_progressive_w320_h240.yuv",
		"h264_w320_h240_testcase_encoding_level41_format.h264",
		"infotmuserdata.txt",
		0,
		0,
		1,
	    {
        	H264ENC_BYTE_STREAM,  
        	H264ENC_LEVEL_4_1,
        	160,           
        	120,          
        	15,    
        	1, 
        	H264ENC_COMPLEXITY_1 
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
			H264ENC_YUV420_SEMIPLANAR,
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

	},
	#endif
	#ifdef H264_RTLCASE_43_FRAMERATE_15
	{
		"case43",
		"yuv420Semiplanar_progressive_w320_h240.yuv",
		"h264_w320_h240_testcase_encoding_target_framerate_15.h264",
		"infotmuserdata.txt",
		0,
		0,
		1,
	    {
        	H264ENC_BYTE_STREAM,  
        	H264ENC_LEVEL_1_1,
        	160,           
        	120,          
        	15,//450    
        	1, //30
        	H264ENC_COMPLEXITY_1 
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
			H264ENC_YUV420_SEMIPLANAR,
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

	},
	#endif
	#ifdef H264_RTLCASE_44_CODING_CTRL_SLICESIZE
	{
		"case44",
		"yuv420Semiplanar_progressive_w320_h240.yuv",
		"h264_w320_h240_testcase_coding_ctrl_slicesize.h264",
		"infotmuserdata.txt",
		1,
		0,
		1,
	    {
        	H264ENC_BYTE_STREAM,  
        	H264ENC_LEVEL_1_1,
        	320,           
        	240,          
        	25,//6000    
        	1, //100
        	H264ENC_COMPLEXITY_1 
    	},
    		
    	{
    		1,//sliceSize
			0xFFFFFFFF,//seiMessages
			0xFFFFFFFF,//videoFullRange
			0xFFFFFFFF,//constrainedIntraPrediction
			0xFFFFFFFF,//disableDeblockingFilter
			0xFFFFFFFF,//sampleAspectRatioWidth
			0xFFFFFFFF,//sampleAspectRatioHeight
			0xFFFFFFFF,//enableCabac
			0xFFFFFFFF,//cabacInitIdc
			0xFFFFFFFF,//transform8x8Mode
			0xFFFFFFFF//quarterPixelMv
		},
        {
			0
		},
		{
        	320,
			240,
			0,
			0,
			H264ENC_YUV420_SEMIPLANAR,
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

	},
	#endif
	#ifdef H264_RTLCASE_45_CODING_CTRL_ENALBECABAC
	{
 		"case45",
		"yuv420Semiplanar_progressive_w320_h240.yuv",
		"h264_w320_h240_testcase_coding_ctrl_enablecabac.h264",
		"infotmuserdata.txt",
		1,
		0,
		1,
	    {
        	H264ENC_BYTE_STREAM,  
        	H264ENC_LEVEL_1_1,
        	128,           
        	96,          
        	25,//6000    
        	1, //100
        	H264ENC_COMPLEXITY_1 
    	},
    		
    	{
    		0xFFFFFFFF,//sliceSize
			0xFFFFFFFF,//seiMessages
			0xFFFFFFFF,//videoFullRange
			0xFFFFFFFF,//constrainedIntraPrediction
			0xFFFFFFFF,//disableDeblockingFilter
			0xFFFFFFFF,//sampleAspectRatioWidth
			0xFFFFFFFF,//sampleAspectRatioHeight
			1,			//enableCabac
			2,//cabac table
			0xFFFFFFFF,//transform8x8Mode
			0xFFFFFFFF//quarterPixelMv
		},
        {
			0
		},
		{
        	320,
			240,
			0,
			0,
			H264ENC_YUV420_SEMIPLANAR,
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

	},
	#endif
	#ifdef H264_RTLCASE_46_CODING_CTRL_TRANSFROM8x8MODE
	{
 		"case46",
		"yuv420Semiplanar_progressive_w320_h240.yuv",
		"h264_w320_h240_testcase_coding_ctrl_transfrom8x8mode.h264",
		"infotmuserdata.txt",
		1,
		0,
		1,
	    {
        	H264ENC_BYTE_STREAM,  
        	H264ENC_LEVEL_1_1,
        	176,           
        	144,          
        	25,//6000    
        	1, //100
        	H264ENC_COMPLEXITY_1 
    	},
    		
    	{
    		0xFFFFFFFF,
			0xFFFFFFFF,//0xFFFFFFFF mean use default value
			0xFFFFFFFF,
			0xFFFFFFFF,
			0xFFFFFFFF,
			0xFFFFFFFF,
			0xFFFFFFFF,
			0xFFFFFFFF,
			0xFFFFFFFF,
			2,
			0xFFFFFFFF
		},
        {
			0
		},
		{
        	320,
			240,
			0,
			0,
			H264ENC_YUV420_SEMIPLANAR,
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

	},
	#endif
	#ifdef H264_RTLCASE_47_RATE_CTRL_CBR
	{
 		"case47",
		"h264_w720_h576_testcase_rate_ctrl_rgb565.rgb",
		"h264_w720_h576_testcase_rate_ctrl_cbr.h264",
		"infotmuserdata.txt",
		0,
		1,
		1,
	    {
        	H264ENC_BYTE_STREAM,  
        	H264ENC_LEVEL_3,
        	160,           
        	120,          
        	25,//6000    
        	1, //100
        	H264ENC_COMPLEXITY_1 
    	},
    		
    	{
			0	
		},
        {
			0,//pictureRc
			0,//mbRc
			0,//pictureSkip
			20,//qpHdr,in this case,this should not be alert
			10,//qpMin
			50,//qpMax
			0xFFFFFFFF,//bitPerSecond,the this case ,we do not set this
			0,//hrd
			0xFFFFFFFF,//hrdCpbSize
			0xFFFFFFFF,//gopLen
			0xFFFFFFFF,//intraQpDelta
			0xFFFFFFFF,//fixedIntraQp
			0xFFFFFFFF,//mbQpAdjustment
			
		},
		{
        	720,
			576,
			120,
			120,
			H264ENC_RGB565,
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
	},
	#endif
	#ifdef H264_RTLCASE_48_RATE_CTRL_VBR_PB
	{
 		"case48",
		"h264_w720_h576_testcase_rate_ctrl_rgb565.rgb",
		"h264_w720_h576_testcase_rate_ctrl_vbr_pb.h264",
		"infotmuserdata.txt",
		0,
		1,
		1,
	    {
        	H264ENC_BYTE_STREAM,  
        	H264ENC_LEVEL_3,
        	160,           
        	120,          
        	25,//6000    
        	1, //100
        	H264ENC_COMPLEXITY_1 
    	},
    		
    	{
			0	
		},
        {
			1,//pictureRc
			0,//mbRc
			0,//pictureSkip
			-1,
			0xFFFFFFFF,//qpMin
			0xFFFFFFFF,//qpMax
			10000000,//bitPerSecond,the target bps we want
			0,//hrd
			0xFFFFFFFF,//hrdCpbSize
			0xFFFFFFFF,//gopLen
			0xFFFFFFFF,//intraQpDelta
			0xFFFFFFFF,//fixedIntraQp
			0xFFFFFFFF,//mbQpAdjustment
			
		},
		{
        	720,
			576,
			0,
			0,
			H264ENC_RGB565,
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
	},
	#endif
	#ifdef H264_RTLCASE_49_CTRL_VBR_HDR
	{
 		"case49",
		"h264_w720_h576_testcase_rate_ctrl_rgb565.rgb",
		"h264_w720_h576_testcase_rate_ctrl_vbr_hdr.h264",
		"infotmuserdata.txt",
		0,
		1,
		1,
	    {
        	H264ENC_BYTE_STREAM,  
        	H264ENC_LEVEL_3,
        	352,           
        	288,          
        	25,//6000    
        	1, //100
        	H264ENC_COMPLEXITY_1 
    	},
    		
    	{
			0	
		},
        {
			0xFFFFFFFF,//pictureRc
			0xFFFFFFFF,//mbRc
			0xFFFFFFFF,//pictureSkip
			-1,//qpHdr
			0xFFFFFFFF,//qpMin
			0xFFFFFFFF,//qpMax
			0xFFFFFFFF,//bitPerSecond,the target bps we want
			1,//hrd
			0xFFFFFFFF,//hrdCpbSize
			0xFFFFFFFF,//gopLen
			0xFFFFFFFF,//intraQpDelta
			0xFFFFFFFF,//fixedIntraQp
			0xFFFFFFFF,//mbQpAdjustment//enable mbqpAdujustment will disable mb rate control
			
		},
		{
        	720,
			576,
			0,
			0,
			H264ENC_RGB565,
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
	},
	#endif
	#ifdef H264_RTLCASE_50_RATE_CTRL_MBQPADJUST
	{
 		"case50",
		"h264_w720_h576_testcase_rate_ctrl_rgb565.rgb",
		"h264_w720_h576_testcase_rate_ctrl_mbqpadust.h264",
		"infotmuserdata.txt",
		0,
		1,
		1,
	    {
        	H264ENC_BYTE_STREAM,  
        	H264ENC_LEVEL_3,
        	128,           
        	96,          
        	25,//6000    
        	1, //100
        	H264ENC_COMPLEXITY_1 
    	},
    		
    	{
			0	
		},
        {
			0xFFFFFFFF,//pictureRc
			0xFFFFFFFF,//mbRc
			0xFFFFFFFF,//pictureSkip
			0xFFFFFFFF,//qpHdr
			0xFFFFFFFF,//qpMin
			0xFFFFFFFF,//qpMax
			0xFFFFFFFF,//bitPerSecond,the target bps we want
			0xFFFFFFFF,//hrd
			0xFFFFFFFF,//hrdCpbSize
			0xFFFFFFFF,//gopLen
			0xFFFFFFFF,//intraQpDelta
			0xFFFFFFFF,//fixedIntraQp
			-4,//mbQpAdjustment//enable mbqpAdujustment will disable mb rate control
			
		},
		{
        	720,
			576,
			0,
			0,
			H264ENC_RGB565,
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
	},
	#endif
	#ifdef H264_RTLCASE_51_PRE_PROC_SIZE_96x96
	{
 		"case51",
		"h264_w96_h96_testcase_preproc_size_yuv420sp.yuv",
		"h264_w96_h96_testcase_preproc.h264",
		"infotmuserdata.txt",
		0,
		0,
		1,
	    {
        	H264ENC_BYTE_STREAM,  
        	H264ENC_LEVEL_1,
        	96,           
        	96,          
        	15,//6000    
        	1, //100
        	H264ENC_COMPLEXITY_1 
    	},
    		
    	{
			0	
		},
        {
			0			
		},
		{
        	96,
			96,
			0,
			0,
			H264ENC_YUV420_SEMIPLANAR,
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
	},
	#endif
	#ifdef H264_RTLCASE_52_PRE_PROC_SIZE_352x288
	{
		"case52",
		"yuv420Semiplanar_progressive_w640_h480.yuv",
		"h264_w352_h288_testcase_preproc.h264",
		"infotmuserdata.txt",
		0,
		0,
		1,
	    {
        	H264ENC_BYTE_STREAM,  
        	H264ENC_LEVEL_2,
        	352,           
        	288,          
        	15,//6000    
        	1, //100
        	H264ENC_COMPLEXITY_1 
    	},
    		
    	{
			0	
		},
        {
			0			
		},
		{
        	640,
			480,
			0,
			0,
			H264ENC_YUV420_SEMIPLANAR,
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
	},
	#endif
	#ifdef H264_RTLCASE_53_PRE_PROC_SIZE_1280x720
	{
		"case53",
		"h264_w1280_h720_testcase_preproc_size_yuv420sp.yuv",
		"h264_w1280_h720_testcase_preproc.h264",
		"infotmuserdata.txt",
		0,
		0,
		1,
	    {
        	H264ENC_BYTE_STREAM,  
        	H264ENC_LEVEL_3_1,
        	1280,           
        	720,          
        	15,//6000    
        	1, //100
        	H264ENC_COMPLEXITY_1 
    	},
    		
    	{
			0	
		},
        {
			0			
		},
		{
        	1280,
			720,
			0,
			0,
			H264ENC_YUV420_SEMIPLANAR,
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
	},
	#endif
	#ifdef H264_RTLCASE_54_PRE_PROC_SIZE_1920x1080
	{
		"case54",
		"h264_w1920_h1080_testcase_preproc_size_yuv420sp.yuv",
		"h264_w1920_h1080_testcase_preproc.h264",
		"infotmuserdata.txt",
		0,
		0,
		1,
	    {
        	H264ENC_BYTE_STREAM,  
        	H264ENC_LEVEL_4_1,
        	1920,           
        	1080,          
        	15,//6000    
        	1, //100
        	H264ENC_COMPLEXITY_1 
    	},
    		
    	{
			0	
		},
        {
			0			
		},
		{
        	1920,
			1080,
			0,
			0,
			H264ENC_YUV420_SEMIPLANAR,
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
	},
	#endif
	#ifdef H264_RTLCASE_55_PRE_PROC_FORMAT_YUYV
	{
 		"case55",
		"h264_w640_h480_testcase_preproc_format_yuyv422.yuv",
		"h264_w640_h480_testcase_preproc_format_yuyv422.h264",
		"infotmuserdata.txt",
		0,
		0,
		1,
	    {
        	H264ENC_BYTE_STREAM,  
        	H264ENC_LEVEL_3,
        	160,           
        	120,          
        	15,//6000    
        	1, //100
        	H264ENC_COMPLEXITY_1 
    	},
    		
    	{
			0	
		},
        {
			0			
		},
		{
        	640,
			480,
			0,
			0,
			H264ENC_YUV422_INTERLEAVED_YUYV,
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
	},
	#endif
	#ifdef H264_RTLCASE_56_PRE_PROC_FORMAT_RGB565
	{
		"case56",
		"h264_w640_h480_testcase_preproc_format_rgb565.rgb",
		"h264_w640_h480_testcase_preproc_format_rgb565.h264",
		"infotmuserdata.txt",
		0,
		0,
		1,
	    {
        	H264ENC_BYTE_STREAM,  
        	H264ENC_LEVEL_3,
        	160,           
        	120,          
        	15,//6000    
        	1, //100
        	H264ENC_COMPLEXITY_1 
    	},
    		
    	{
			0	
		},
        {
			0			
		},
		{
        	640,
			480,
			0,
			0,
			H264ENC_RGB565,
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
	},
	#endif
	#ifdef H264_RTLCASE_57_PRE_PROC_FORMAT_RGB888
	{
		"case57",
		"h264_w640_h480_testcase_preproc_format_rgb888.rgb",
		"h264_w640_h480_testcase_preproc_format_rgb888.h264",
		"infotmuserdata.txt",
		0,
		0,
		1,
	    {
        	H264ENC_BYTE_STREAM,  
        	H264ENC_LEVEL_3,
        	160,           
        	120,          
        	15,//6000    
        	1, //100
        	H264ENC_COMPLEXITY_1 
    	},
    		
    	{
			0	
		},
        {
			0			
		},
		{
        	640,
			480,
			0,
			0,
			H264ENC_RGB888,
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
	},
	#endif
	#ifdef H264_RTLCASE_58_PROC_ROTATION_90L
	{
		"case58",
		"h264_w640_h480_testcase_preproc_format_bgr101010.rgb",
		"h264_w640_h480_testcase_preproc_rotation90L.h264",
		"infotmuserdata.txt",
		0,
		0,
		1,
	    {
        	H264ENC_BYTE_STREAM,  
        	H264ENC_LEVEL_3,
        	120,           
        	160,          
        	15,//6000    
        	1, //100
        	H264ENC_COMPLEXITY_1 
    	},
    		
    	{
			0	
		},
        {
			0			
		},
		{
        	640,
			480,
			0,
			0,
			H264ENC_BGR101010,
			H264ENC_ROTATE_90L,
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
	},
	#endif
	#ifdef H264_RTLCASE_59_PROC_ROTATION_90R
	{
		"case59",
		"h264_w640_h480_testcase_preproc_format_bgr101010.rgb",
		"h264_w640_h480_testcase_preproc_rotation90R.h264",
		"infotmuserdata.txt",
		0,
		0,
		1,
	    {
        	H264ENC_BYTE_STREAM,  
        	H264ENC_LEVEL_3,
        	120,           
        	160,          
        	15,//6000    
        	1, //100
        	H264ENC_COMPLEXITY_1 
    	},
    		
    	{
			0	
		},
        {
			0			
		},
		{
        	640,
			480,
			0,
			0,
			H264ENC_BGR101010,
			H264ENC_ROTATE_90R,
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
	},
	#endif
	#ifdef H264_RTLCASE_60_PROC_VIDEOSTABILIZATION
	{
		"case60",
		"camstab_w104_h104_yuv420sp.yuv",
		"h264_w00_h00_testcase_preproc_videostabilization.h264",
		"infotmuserdata.txt",
		0,
		0,
		1,
	    {
        	H264ENC_BYTE_STREAM,  
        	H264ENC_LEVEL_1,
        	96,           
        	96,          
        	15,//6000    
        	1, //100
        	H264ENC_COMPLEXITY_1 
    	},
    		
    	{
			0	
		},
        {
			0			
		},
		{
        	104,
			104,
			0,
			0,
			H264ENC_YUV420_SEMIPLANAR,
			H264ENC_ROTATE_0,
			1,
        	{
				H264ENC_RGBTOYUV_BT601,
				0,
				0,
				0,
				0,
				0
			}
		}
	},
	#endif
	#ifdef H264_RTLCASE_61_PROC_CROP
	{
		"case61",
		"h264_w640_h480_testcase_preproc_format_rgb565.rgb",
		"h264_w100_h480_testcase_preproc_crop.h264",
		"infotmuserdata.txt",
		0,
		0,
		1,
	    {
        	H264ENC_BYTE_STREAM,  
        	H264ENC_LEVEL_3,
        	128,           
        	96,          
        	15,//6000    
        	1, //100
        	H264ENC_COMPLEXITY_1 
    	},
    		
    	{
			0	
		},
        {
			0			
		},
		{
        	640,
			480,
			120,
			120,
			H264ENC_RGB565,
			H264ENC_ROTATE_90L,
			0,
        	{
				H264ENC_RGBTOYUV_USER_DEFINED,
				19589,
				38443,
				7504,
				37008,
				40740
			}
		}
	},
	#endif
#endif	

};
#endif

#ifdef  __JPEGENCTEST__
JPEGENCCFG jpeg_enc_test[] = {
#ifdef JPEG_TESTCASE_QLEVEL
	#ifdef JPEG_TESTCASE_QLEVEL_L0
	{
	"",
	"jpeg_w240_h240_testcase_qlevel.yuvsp",//input file name 
	"",//thumbnail file name;
	"",//comment header file name 
	"jpeg_w240_h240_testcase_qlevel_0.jpeg",//output file name

	//
	{
		240,//inputWidth
		240,//inputHeight
		0,//xOffset
		0,//yOffset
		240,//codingWidth
		240,//codingHeight
		0,//restartInterval
		0,//qLevel
		NULL,//qTableLuma
		NULL,//qTableChroma
		JPEGENC_YUV420_SEMIPLANAR,//frameType
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
		96,
		96,
		NULL,
		0
	}
	},
	#endif
	#ifdef JPEG_TESTCASE_QLEVEL_L1
	{
	"",
	"jpeg_w240_h240_testcase_qlevel.yuvsp",//input file name 
	"",//thumbnail file name;
	"",//comment header file name 
	"jpeg_w240_h240_testcase_qlevel_1.jpeg",//output file name

	//
	{
		240,//inputWidth
		240,//inputHeight
		0,//xOffset
		0,//yOffset
		240,//codingWidth
		240,//codingHeight
		0,//restartInterval
		1,//qLevel
		NULL,//qTableLuma
		NULL,//qTableChroma
		JPEGENC_YUV420_SEMIPLANAR,//frameType
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
		25,
		25,
		NULL,
		0
	}
	},
	#endif
	#ifdef JPEG_TESTCASE_QLEVEL_L2
	{
	"",
	"jpeg_w240_h240_testcase_qlevel.yuvsp",//input file name 
	"",//thumbnail file name;
	"",//comment header file name 
	"jpeg_w240_h240_testcase_qlevel_2.jpeg",//output file name

	//
	{
		240,//inputWidth
		240,//inputHeight
		0,//xOffset
		0,//yOffset
		240,//codingWidth
		240,//codingHeight
		0,//restartInterval
		2,//qLevel
		NULL,//qTableLuma
		NULL,//qTableChroma
		JPEGENC_YUV420_SEMIPLANAR,//frameType
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
		25,
		25,
		NULL,
		0
	}
	},
	#endif
	#ifdef JPEG_TESTCASE_QLEVEL_L3
	{
	"",
	"jpeg_w240_h240_testcase_qlevel.yuvsp",//input file name 
	"",//thumbnail file name;
	"",//comment header file name 
	"jpeg_w240_h240_testcase_qlevel_3.jpeg",//output file name

	//
	{
		240,//inputWidth
		240,//inputHeight
		0,//xOffset
		0,//yOffset
		240,//codingWidth
		240,//codingHeight
		0,//restartInterval
		3,//qLevel
		NULL,//qTableLuma
		NULL,//qTableChroma
		JPEGENC_YUV420_SEMIPLANAR,//frameType
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
		25,
		25,
		NULL,
		0
	}
	},
	#endif
	#ifdef JPEG_TESTCASE_QLEVEL_L4
	{
	"",
	"jpeg_w240_h240_testcase_qlevel.yuvsp",//input file name 
	"",//thumbnail file name;
	"",//comment header file name 
	"jpeg_w240_h240_testcase_qlevel_4.jpeg",//output file name

	//
	{
		240,//inputWidth
		240,//inputHeight
		0,//xOffset
		0,//yOffset
		240,//codingWidth
		240,//codingHeight
		0,//restartInterval
		4,//qLevel
		NULL,//qTableLuma
		NULL,//qTableChroma
		JPEGENC_YUV420_SEMIPLANAR,//frameType
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
		25,
		25,
		NULL,
		0
	}
	},
	#endif
	#ifdef JPEG_TESTCASE_QLEVEL_L5
	{
	"",
	"jpeg_w240_h240_testcase_qlevel.yuvsp",//input file name 
	"",//thumbnail file name;
	"",//comment header file name 
	"jpeg_w240_h240_testcase_qlevel_5.jpeg",//output file name

	//
	{
		240,//inputWidth
		240,//inputHeight
		0,//xOffset
		0,//yOffset
		240,//codingWidth
		240,//codingHeight
		0,//restartInterval
		5,//qLevel
		NULL,//qTableLuma
		NULL,//qTableChroma
		JPEGENC_YUV420_SEMIPLANAR,//frameType
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
		25,
		25,
		NULL,
		0
	}
	},
	#endif
	#ifdef JPEG_TESTCASE_QLEVEL_L6
	{
	"",
	"jpeg_w240_h240_testcase_qlevel.yuvsp",//input file name 
	"",//thumbnail file name;
	"",//comment header file name 
	"jpeg_w240_h240_testcase_qlevel_6.jpeg",//output file name

	//
	{
		240,//inputWidth
		240,//inputHeight
		0,//xOffset
		0,//yOffset
		240,//codingWidth
		240,//codingHeight
		0,//restartInterval
		6,//qLevel
		NULL,//qTableLuma
		NULL,//qTableChroma
		JPEGENC_YUV420_SEMIPLANAR,//frameType
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
		25,
		25,
		NULL,
		0
	}
	},
	#endif
	#ifdef JPEG_TESTCASE_QLEVEL_L7
	{
	"",
	"jpeg_w240_h240_testcase_qlevel.yuvsp",//input file name 
	"",//thumbnail file name;
	"",//comment header file name 
	"jpeg_w240_h240_testcase_qlevel_7.jpeg",//output file name

	//
	{
		240,//inputWidth
		240,//inputHeight
		0,//xOffset
		0,//yOffset
		240,//codingWidth
		240,//codingHeight
		0,//restartInterval
		7,//qLevel
		NULL,//qTableLuma
		NULL,//qTableChroma
		JPEGENC_YUV420_SEMIPLANAR,//frameType
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
		25,
		25,
		NULL,
		0
	}
	},
	#endif
	#ifdef JPEG_TESTCASE_QLEVEL_L8
	{
	"",
	"jpeg_w240_h240_testcase_qlevel.yuvsp",//input file name 
	"",//thumbnail file name;
	"",//comment header file name 
	"jpeg_w240_h240_testcase_qlevel_8.jpeg",//output file name

	//
	{
		240,//inputWidth
		240,//inputHeight
		0,//xOffset
		0,//yOffset
		240,//codingWidth
		240,//codingHeight
		0,//restartInterval
		8,//qLevel
		NULL,//qTableLuma
		NULL,//qTableChroma
		JPEGENC_YUV420_SEMIPLANAR,//frameType
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
		25,
		25,
		NULL,
		0
	}
	},
	#endif
	#ifdef JPEG_TESTCASE_QLEVEL_L9
	{
	"",
	"jpeg_w240_h240_testcase_qlevel.yuvsp",//input file name 
	"",//thumbnail file name;
	"",//comment header file name 
	"jpeg_w240_h240_testcase_qlevel_9.jpeg",//output file name

	//
	{
		240,//inputWidth
		240,//inputHeight
		0,//xOffset
		0,//yOffset
		240,//codingWidth
		240,//codingHeight
		0,//restartInterval
		9,//qLevel
		NULL,//qTableLuma
		NULL,//qTableChroma
		JPEGENC_YUV420_SEMIPLANAR,//frameType
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
		25,
		25,
		NULL,
		0
	}
	},
	#endif
	#ifdef JPEG_TESTCASE_QLEVEL_L10
	{
	"",
	"jpeg_w240_h240_testcase_qlevel.yuvsp",//input file name 
	"",//thumbnail file name;
	"",//comment header file name 
	"jpeg_w240_h240_testcase_qlevel_10.jpeg",//output file name

	//
	{
		240,//inputWidth
		240,//inputHeight
		0,//xOffset
		0,//yOffset
		240,//codingWidth
		240,//codingHeight
		0,//restartInterval
		10,//qLevel
		NULL,//qTableLuma
		NULL,//qTableChroma
		JPEGENC_YUV420_SEMIPLANAR,//frameType
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
		25,
		25,
		NULL,
		0
	}
	},
	#endif
#endif

#ifdef JPEG_TESTCASE_INPUT_FORMAT
	#ifdef  JPEG_TESTCASE_INPUT_YUV420P
	{
	"",
	"jpeg_w640_h480_testcase_inputformat_yuv420p.yuv",//input file name 
	"",//thumbnail file name;
	"",//comment header file name 
	"jpeg_w640_h480_testcase_inputformat_yuv420p.jpeg",//output file name
	//
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
		JPEGENC_YUV420_PLANAR,//frameType
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
		25,
		25,
		NULL,
		0
	}
	},
	#endif
	#ifdef  JPEG_TESTCASE_INPUT_YUV420SP
	{
	"",
	"jpeg_w240_h240_testcase_inputformat_yuv420sp.yuv",//input file name 
	"",//thumbnail file name;
	"",//comment header file name 
	"jpeg_w240_h240_testcase_inputformat_yuv420sp.jpeg",//output file name

	//
	{
		240,//inputWidth
		240,//inputHeight
		0,//xOffset
		0,//yOffset
		240,//codingWidth
		240,//codingHeight
		0,//restartInterval
		5,//qLevel
		NULL,//qTableLuma
		NULL,//qTableChroma
		JPEGENC_YUV420_SEMIPLANAR,//frameType
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
		25,
		25,
		NULL,
		0
	}
	},
	#endif
	#ifdef JPEG_TESTCASE_INPUT_YUV422_INTERLEAVED_YUYV
	{
	"",
	"jpeg_w640_h480_testcase_inputformat_yuyv422.yuv",//input file name 
	"",//thumbnail file name;
	"",//comment header file name 
	"jpeg_w640_h480_testcase_inputformat_yuyv422.jpeg",//output file name

	//
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
		JPEGENC_YUV422_INTERLEAVED_YUYV,//frameType
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
		25,
		25,
		NULL,
		0
	}
	},
	#endif

	//TODO:
	#ifdef JPEG_TESTCASE_INPUT_YUV422_INTERLEAVED_UYVY//
	{
	"",
	"jpeg_w1024_h426_testcase_inputformat_uyvy422.yuv",//input file name 
	"",//thumbnail file name;
	"",//comment header file name 
	"jpeg_w1024_h426_testcase_inputformat_uyvy422.jpeg",//output file name

	//
	{
		1024,//inputWidth
		426,//inputHeight
		0,//xOffset
		0,//yOffset
		1024,//codingWidth
		426,//codingHeight
		0,//restartInterval
		5,//qLevel
		NULL,//qTableLuma
		NULL,//qTableChroma
		JPEGENC_YUV422_INTERLEAVED_UYVY,//frameType
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
		25,
		25,
		NULL,
		0
	}
	},	
	#endif
	#ifdef JPEG_TESTCASE_INPUT_RGB565
	{
	"",
	"jpeg_w800_h600_testcase_inputformat_rgb565.rgb",//input file name 
	"",//thumbnail file name;
	"",//comment header file name 
	"jpeg_w800_h600_testcase_inputformat_rgb565.jpeg",//output file name

	//
	{
		800,//inputWidth
		600,//inputHeight
		0,//xOffset
		0,//yOffset
		800,//codingWidth
		600,//codingHeight
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
		25,
		25,
		NULL,
		0
	}
	},
   	#endif	
	#ifdef JPEG_TESTCASE_INPUT_BGR565
	{
	"",
	"jpeg_w480_h384_testcase_inputformat_bgr565.rgb",//input file name 
	"",//thumbnail file name;
	"",//comment header file name 
	"jpeg_w480_h384_testcase_inputformat_bgr565.jpeg",//output file name

	//
	{
		480,//inputWidth
		384,//inputHeight
		0,//xOffset
		0,//yOffset
		480,//codingWidth
		384,//codingHeight
		0,//restartInterval
		5,//qLevel
		NULL,//qTableLuma
		NULL,//qTableChroma
		JPEGENC_BGR565,//frameType
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
		25,
		25,
		NULL,
		0
	}
	},
   	#endif	
	#ifdef JPEG_TESTCASE_INPUT_RGB555
	{
	"",
	"jpeg_w1024_h576_testcase_inputformat_rgb555.rgb",//input file name 
	"",//thumbnail file name;
	"",//comment header file name 
	"jpeg_w1024_h576_testcase_inputformat_rgb555.jpeg",//output file name

	//
	{
		1024,//inputWidth
		576,//inputHeight
		0,//xOffset
		0,//yOffset
		1024,//codingWidth
		576,//codingHeight
		0,//restartInterval
		5,//qLevel
		NULL,//qTableLuma
		NULL,//qTableChroma
		JPEGENC_RGB555,//frameType
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
		25,
		25,
		NULL,
		0
	}
	},
	#endif
	#ifdef JPEG_TESTCASE_INPUT_BGR555
	{
	"",
	"jpeg_w1024_h426_testcase_inputformat_bgr555.rgb",//input file name 
	"",//thumbnail file name;
	"",//comment header file name 
	"jpeg_w1024_h426_testcase_inputformat_bgr555.jpeg",//output file name

	//
	{
		1024,//inputWidth
		426,//inputHeight
		0,//xOffset
		0,//yOffset
		1024,//codingWidth
		426,//codingHeight
		0,//restartInterval
		5,//qLevel
		NULL,//qTableLuma
		NULL,//qTableChroma
		JPEGENC_BGR555,//frameType
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
		25,
		25,
		NULL,
		0
	}
	},	
	#endif
	#ifdef JPEG_TESTCASE_INPUT_RGB444
	{
	"",
	"jpeg_w1024_h576_testcase_inputformat_rgb444.rgb",//input file name 
	"",//thumbnail file name;
	"",//comment header file name 
	"jpeg_w1024_h576_testcase_inputformat_rgb444.jpeg",//output file name

	//
	{
		1024,//inputWidth
		576,//inputHeight
		0,//xOffset
		0,//yOffset
		1024,//codingWidth
		576,//codingHeight
		0,//restartInterval
		10,//qLevel
		NULL,//qTableLuma
		NULL,//qTableChroma
		JPEGENC_RGB444,//frameType
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
		25,
		25,
		NULL,
		0
	}
	},	
	#endif
	#ifdef JPEG_TESTCASE_INPUT_BGR444
	{
	"",
	"jpeg_w800_h600_testcase_inputformat_bgr444.rgb",//input file name 
	"",//thumbnail file name;
	"",//comment header file name 
	"jpeg_w800_h600_testcase_inputformat_bgr444.jpeg",//output file name

	//
	{
		800,//inputWidth
		600,//inputHeight
		0,//xOffset
		0,//yOffset
		800,//codingWidth
		600,//codingHeight
		0,//restartInterval
		10,//qLevel
		NULL,//qTableLuma
		NULL,//qTableChroma
		JPEGENC_BGR444,//frameType
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
		25,
		25,
		NULL,
		0
	}
	},	
	#endif
	#ifdef JPEG_TESTCASE_INPUT_RGB888
	{
	"",
	"jpeg_w1024_h574_testcase_inputformat_rgb32.rgb",//input file name 
	"",//thumbnail file name;
	"",//comment header file name 
	"jpeg_w1024_h574_testcase_inputformat_rgb32.jpeg",//output file name

	//
	{
		1024,//inputWidth
		574,//inputHeight
		0,//xOffset
		0,//yOffset
		1024,//codingWidth
		574,//codingHeight
		0,//restartInterval
		5,//qLevel
		NULL,//qTableLuma
		NULL,//qTableChroma
		JPEGENC_RGB888,//frameType
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
		25,
		25,
		NULL,
		0
	}
	},
	#endif
	#ifdef JPEG_TESTCASE_INPUT_BGR888
	{
	"",
	"jpeg_w1024_h426_testcase_inputformat_bgr32.rgb",//input file name 
	"",//thumbnail file name;
	"",//comment header file name 
	"jpeg_w1024_h426_testcase_inputformat_bgr32.jpeg",//output file name

	//
	{
		1024,//inputWidth
		426,//inputHeight
		0,//xOffset
		0,//yOffset
		1024,//codingWidth
		426,//codingHeight
		0,//restartInterval
		5,//qLevel
		NULL,//qTableLuma
		NULL,//qTableChroma
		JPEGENC_BGR888,//frameType
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
		25,
		25,
		NULL,
		0
	}
	},
	#endif
	#ifdef JPEG_TESTCASE_INPUT_RGB101010
	{
	"",
	"jpeg_w1024_h576_testcase_inputformat_rgb101010.rgb",//input file name 
	"",//thumbnail file name;
	"",//comment header file name 
	"jpeg_w1024_h576_testcase_inputformat_rgb101010.jpeg",//output file name

	//
	{
		1024,//inputWidth
		576,//inputHeight
		0,//xOffset
		0,//yOffset
		1024,//codingWidth
		576,//codingHeight
		0,//restartInterval
		10,//qLevel
		NULL,//qTableLuma
		NULL,//qTableChroma
		JPEGENC_RGB101010,//frameType
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
		25,
		25,
		NULL,
		0
	}
	},
	#endif
	#ifdef JPEG_TESTCASE_INPUT_BGR101010
	{
	"",
	"jpeg_w1024_h576_testcase_inputformat_bgr101010.rgb",//input file name 
	"",//thumbnail file name;
	"",//comment header file name 
	"jpeg_w1024_h576_testcase_inputformat_bgr101010.jpeg",//output file name

	//
	{
		1024,//inputWidth
		576,//inputHeight
		0,//xOffset
		0,//yOffset
		1024,//codingWidth
		576,//codingHeight
		0,//restartInterval
		10,//qLevel
		NULL,//qTableLuma
		NULL,//qTableChroma
		JPEGENC_BGR101010,//frameType
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
		25,
		25,
		NULL,
		0
	}
	},
	#endif
#endif
#ifdef JPEG_TESTCASE_INPUT_ROTATION
	#ifdef JPEG_TESTCASE_INPUT_ROTATE_90R
	{
	"",
	"jpeg_w640_h480_testcase_input_rotation.yuv",//input file name
	"",//thumbnail file name;
	"",//comment header file name 
	"jpeg_w640_h480_testcase_input_rotation90R.jpeg",//output file name
	//
	{
		640,//inputWidth
		480,//inputHeight
		0/*5*/,//xOffset
		0/*4*/,//yOffset
		480/*240*/,//codingWidth
		640/*200*/,//codingHeight
		0,//restartInterval
		10,//qLevel
		NULL,//qTableLuma
		NULL,//qTableChroma
		JPEGENC_YUV420_PLANAR,//frameType
		{
			JPEGENC_RGBTOYUV_BT601,
			0,//coeffA
			0,//coeffB
			0,//coeffC
			0,//coeffE
			0//coeffF
		},//colorConversion

		JPEGENC_ROTATE_90R,
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
		25,
		25,
		NULL,
		0
	}
	},
	#endif
	#ifdef JPEG_TESTCASE_INPUT_ROTATE_90L
	{
	"",
	"jpeg_w640_h480_testcase_input_rotation.yuv",//input file name 
	"",//thumbnail file name;
	"",//comment header file name 
	"jpeg_w640_h480_testcase_input_rotation90L.jpeg",//output file name
	//
	{
		640,//inputWidth
		480,//inputHeight
		0/*100*/,//xOffset
		0/*90*/,//yOffset
		480/*96*/,//codingWidth
		640/*100*/,//codingHeight
		0,//restartInterval
		10,//qLevel
		NULL,//qTableLuma
		NULL,//qTableChroma
		JPEGENC_YUV420_PLANAR,//frameType
		{
			JPEGENC_RGBTOYUV_BT601,
			0,//coeffA
			0,//coeffB
			0,//coeffC
			0,//coeffE
			0//coeffF
		},//colorConversion

		JPEGENC_ROTATE_90L,
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
		25,
		25,
		NULL,
		0
	}
	},
	#endif
#endif
#ifdef JPEG_TESTCASE_INPUT_CROPPING
	#ifdef JPEG_TESTCASE_INPUT_CROP_TOPLEFT
	{
	"",
	"jpeg_w640_h480_testcase_input_cropping.yuv",//input file name 
	"",//thumbnail file name;
	"",//comment header file name 
	"jpeg_w120_h96_testcase_input_crop_top_left.jpeg",//output file name
	//
	{
		640,//inputWidth
		480,//inputHeight
		241,//xOffset
		352,//yOffset
		120,//codingWidth
		96,//codingHeight
		0,//restartInterval
		5,//qLevel
		NULL,//qTableLuma
		NULL,//qTableChroma
		JPEGENC_YUV420_PLANAR,//frameType
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
		25,
		25,
		NULL,
		0
	}
	},
	#endif

	#ifdef JPEG_TESTCASE_INPUT_CROP_TOPRIGHT
	{
	"",
	"jpeg_w640_h480_testcase_input_cropping.yuv",//input file name 
	"",//thumbnail file name;
	"",//comment header file name 
	"jpeg_w120_h96_testcase_input_crop_top_right.jpeg",//output file name
	//
	{
		640,//inputWidth
		480,//inputHeight
		480,//xOffset
		0,//yOffset
		120,//codingWidth
		96,//codingHeight
		0,//restartInterval
		5,//qLevel
		NULL,//qTableLuma
		NULL,//qTableChroma
		JPEGENC_YUV420_PLANAR,//frameType
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
		25,
		25,
		NULL,
		0
	}
	},
	#endif
	#ifdef JPEG_TESTCASE_INPUT_CROP_BOTTOMLEFT
	{
	"",
	"jpeg_w640_h480_testcase_input_cropping.yuv",//input file name 
	"",//thumbnail file name;
	"",//comment header file name 
	"jpeg_w120_h96_testcase_input_crop_bottom_left.jpeg",//output file name
	//
	{
		640,//inputWidth
		480,//inputHeight
		0,//xOffset
		320,//yOffset
		120,//codingWidth
		96,//codingHeight
		0,//restartInterval
		5,//qLevel
		NULL,//qTableLuma
		NULL,//qTableChroma
		JPEGENC_YUV420_PLANAR,//frameType
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
		25,
		25,
		NULL,
		0
	}
	},
	#endif
	#ifdef JPEG_TESTCASE_INPUT_CROP_BOTTOMRIGHT
	{
	"",
	"jpeg_w640_h480_testcase_input_cropping.yuv",//input file name 
	"",//thumbnail file name;
	"",//comment header file name 
	"jpeg_w120_h96_testcase_input_crop_bottom_right.jpeg",//output file name
	//
	{
		640,//inputWidth
		480,//inputHeight
		480,//xOffset
		320,//yOffset
		120,//codingWidth
		96,//codingHeight
		0,//restartInterval
		5,//qLevel
		NULL,//qTableLuma
		NULL,//qTableChroma
		JPEGENC_YUV420_PLANAR,//frameType
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
		25,
		25,
		NULL,
		0
	}
	},
	#endif
	#ifdef JPEG_TESTCASE_INPUT_CROP_MIDDLE
	{
	"",
	"jpeg_w640_h480_testcase_input_cropping.yuv",//input file name 
	"",//thumbnail file name;
	"",//comment header file name 
	"jpeg_w120_h96_testcase_input_crop_middle.jpeg",//output file name
	//
	{
		640,//inputWidth
		480,//inputHeight
		240,//xOffset
		192,//yOffset
		120,//codingWidth
		96,//codingHeight
		0,//restartInterval
		5,//qLevel
		NULL,//qTableLuma
		NULL,//qTableChroma
		JPEGENC_YUV420_PLANAR,//frameType
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
		25,
		25,
		NULL,
		0
	}	
	},
	#endif
#endif
#ifdef JPEG_TESTCASE_INPUT_SIZE
	#ifdef JPEG_TESTCASE_INPUT_MIN
	{
	"",
	"jpeg_w96_h32_testcase_inputsize_yuv420sp.yuv",//input file name 
	"",//thumbnail file name;
	"",//comment header file name 
	"jpeg_w96_h32_testcase_inputsize_min.jpeg",//output file name
	//
	{
		96,//inputWidth
		32,//inputHeight
		0,//xOffset
		0,//yOffset
		96,//codingWidth
		32,//codingHeight
		0,//restartInterval
		9,//qLevel
		NULL,//qTableLuma
		NULL,//qTableChroma
		JPEGENC_YUV420_SEMIPLANAR,//frameType
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
		25,
		25,
		NULL,
		0
	}	
	},
	
	#endif

	#ifdef  JPEG_TESTCASE_INPUT_MAX	
	{
	"",
	"jpeg_w8192_h8192_testcase_inputsize_yuv420sp.yuv",//input file name 
	"",//thumbnail file name;
	"",//comment header file name 
	"jpeg_w8192_h8192_testcase_inputsize_max.jpeg",//output file name
	//
	{
		8192,//inputWidth
		8192,//inputHeight
		0,//xOffset
		0,//yOffset
		0,//codingWidth
		0,//codingHeight
		0,//restartInterval
		9,//qLevel
		NULL,//qTableLuma
		NULL,//qTableChroma
		JPEGENC_YUV420_SEMIPLANAR,//frameType
		{
			JPEGENC_RGBTOYUV_BT601,
			0,//coeffA
			0,//coeffB
			0,//coeffC
			0,//coeffE
			0//coeffF
		},//colorConversion

		JPEGENC_ROTATE_0,
		JPEGENC_SLICED_FRAME,
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
		25,
		25,
		NULL,
		0
	}	
	},
	
	#endif
	#ifdef  JPEG_TESTCASE_INPUT_MINW_MAXH
	#endif
	#ifdef  JPEG_TESTCASE_INPUT_MAXW_MINH
	#endif
	#ifdef  JPEG_TESTCASE_INPUT_16W
	#endif
	#ifdef  JPEG_TESTCASE_INPUT_NOT16W
	#endif
	#ifdef  JPEG_TESTCASE_INPUT_2H
	#endif
	#ifdef  JPEG_TESTCASE_INPUT_NOT2H
	#endif 
	#ifdef JPEG_TESTCASE_INPUT_NOT2H
	#endif
	#ifdef JPEG_TESTCASE_INPUT_SUB_QCIF
	{
	"",
	"jpeg_w128_h96_testcase_inputsize_yuv420sp.yuv",//input file name 
	"",//thumbnail file name;
	"",//comment header file name 
	"jpeg_w128_h96_testcase_inputsize_subqcif.jpeg",//output file name
	//
	{
		128,//inputWidth
		96,//inputHeight
		0,//xOffset
		0,//yOffset
		128,//codingWidth
		96,//codingHeight
		0,//restartInterval
		9,//qLevel
		NULL,//qTableLuma
		NULL,//qTableChroma
		JPEGENC_YUV420_SEMIPLANAR,//frameType
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
		25,
		25,
		NULL,
		0
	}	
	},	
	#endif 
	#ifdef JPEG_TESTCASE_INPUT_QQVGA
	{
	"",
	"jpeg_w160_h120_testcase_inputsize_yuv420sp.yuv",//input file name 
	"",//thumbnail file name;
	"",//comment header file name 
	"jpeg_w160_h120_testcase_inputsize_qqvga.jpeg",//output file name
	//
	{
		160,//inputWidth
		120,//inputHeight
		0,//xOffset
		0,//yOffset
		160,//codingWidth
		120,//codingHeight
		0,//restartInterval
		9,//qLevel
		NULL,//qTableLuma
		NULL,//qTableChroma
		JPEGENC_YUV420_SEMIPLANAR,//frameType
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
		25,
		25,
		NULL,
		0
	}	
	},	
	#endif
	#ifdef JPEG_TESTCASE_INPUT_QCIF
	#endif
	#ifdef JPEG_TESTCASE_INPUT_QVGA
	#endif
	#ifdef JPEG_TESTCASE_INPUT_CIF
	#endif
	#ifdef JPEG_TESTCASE_INPUT_VGA
	{
	"",
	"jpeg_w640_h480_testcase_inputsize_rgb565.rgb",//input file name 
	"",//thumbnail file name;
	"",//comment header file name 
	"jpeg_w640_h480_testcase_inputsize_vga.jpeg",//output file name
	//
	{
		640,//inputWidth
		480,//inputHeight
		0,//xOffset
		0,//yOffset
		0,//codingWidth
		0,//codingHeight
		0,//restartInterval
		9,//qLevel
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
		JPEGENC_SLICED_FRAME,
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
		25,
		25,
		NULL,
		0
	}	
	},		
	#endif
	#ifdef JPEG_TESTCASE_INPUT_PAL
	#endif
	#ifdef JPEG_TESTCASE_INPUT_SVGA
	#endif
	#ifdef JPEG_TESTCASE_INPUT_XVGA
	#endif
	#ifdef JPEG_TESTCASE_INPUT_720P
	{
	"",
	"jpeg_w1280_h720_testcase_inputsize_yuv420sp.yuv",//input file name 
	"",//thumbnail file name;
	"",//comment header file name 
	"jpeg_w1280_h720_testcase_inputsize_720p.jpeg",//output file name
	//
	{
		1280,//inputWidth
		720,//inputHeight
		0,//xOffset
		0,//yOffset
		1280,//codingWidth
		720,//codingHeight
		0,//restartInterval
		9,//qLevel
		NULL,//qTableLuma
		NULL,//qTableChroma
		JPEGENC_YUV420_SEMIPLANAR,//frameType
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
		25,
		25,
		NULL,
		0
	}	
	},	
	#endif
	#ifdef JPEG_TESTCASE_INPUT_SXGA
	#endif
	#ifdef JPEG_TESTCASE_INPUT_SXGAPlus
	#endif
	#ifdef JPEG_TESTCASE_INPUT_UXGA
	#endif
	#ifdef JPEG_TESTCASE_INPUT_1080P
	{
	"",
	"jpeg_w1920_h1080_testcase_inputsize_yuv420sp.yuv",//input file name 
	"",//thumbnail file name;
	"",//comment header file name 
	"jpeg_w1920_h1080_testcase_inputsize_1080p.jpeg",//output file name
	//
	{
		1920,//inputWidth
		1080,//inputHeight
		0,//xOffset
		0,//yOffset
		1920,//codingWidth
		1080,//codingHeight
		0,//restartInterval
		9,//qLevel
		NULL,//qTableLuma
		NULL,//qTableChroma
		JPEGENC_YUV420_SEMIPLANAR,//frameType
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
		25,
		25,
		NULL,
		0
	}	
	},		
	#endif
	#ifdef JPEG_TESTCASE_INPUT_WQXGA
	#endif
	#ifdef JPEG_TESTCASE_INPUT_QUXGA
	#endif
	#ifdef JPEG_TESTCASE_INPUT_QUXGA_W
	#endif
#endif
#ifdef JPEG_TESTCASE_HEADER_APP0
	#ifdef  JPEG_TESTCASE_HEADER_APP0_NO_UNITS
	{
	"",
	"jpeg_w640_h480_testcase_header_APP0.yuv",//input file name 
	"",//thumbnail file name;
	"",//comment header file name 
	"jpeg_w640_h480_testcase_app0_no_units.jpeg",//output file name
	//
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
		JPEGENC_YUV420_PLANAR,//frameType
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
		25,
		25,
		NULL,
		0
	}
	},

	#endif
	#ifdef JPEG_TESTCASE_HEADER_APP0_DOTS_PER_INCH
	{
	"",
	"jpeg_w640_h480_testcase_header_APP0.yuv",//input file name 
	"",//thumbnail file name;
	"",//comment header file name 
	"jpeg_w640_h480_testcase_app0_dots_per_inch.jpeg",//output file name
	//
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
		JPEGENC_YUV420_PLANAR,//frameType
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
		JPEGENC_DOTS_PER_INCH,
		JPEGENC_SINGLE_MARKER,
		10000,//xDensity
		10000,//yDensity
		0,//comLength
		NULL//pCom
	},//excfg
	{
		JPEGENC_THUMB_JPEG,
		25,
		25,
		NULL,
		0
	}
	},
	#endif
	#ifdef JPEG_TESTCASE_HEADER_APP0_DOTS_PER_CM
	{
	"",
	"jpeg_w640_h480_testcase_header_APP0.yuv",//input file name 
	"",//thumbnail file name;
	"",//comment header file name 
	"jpeg_w640_h480_testcase_app0_dots_per_cm.jpeg",//output file name
	//
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
		JPEGENC_YUV420_PLANAR,//frameType
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
		JPEGENC_DOTS_PER_CM,
		JPEGENC_SINGLE_MARKER,
		1000,//xDensity
		1000,//yDensity
		0,//comLength
		NULL//pCom
	},//excfg
	{
		JPEGENC_THUMB_JPEG,
		25,
		25,
		NULL,
		0
	}
	},
	#endif
#endif
#ifdef JPEG_TESTCASE_HEADER_DQT_DHT
	#ifdef JPEG_TESTCASE_HEADER_SINGLE_MARKER
	{
	"",
	"jpeg_w640_h480_testcase_header_dqt_dht.yuv",//input file name 
	"",//thumbnail file name;
	"",//comment header file name 
	"jpeg_w640_h480_testcase_dqtdht_signal_marker.jpeg",//output file name
	//
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
		JPEGENC_YUV420_PLANAR,//frameType
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
		25,
		25,
		NULL,
		0
	}
	},
	#endif
	#ifdef JPEG_TESTCASE_HEADER_MULTI_MARKER
	{
	"",
	"jpeg_w640_h480_testcase_header_dqt_dht.yuv",//input file name 
	"",//thumbnail file name;
	"",//comment header file name 
	"jpeg_w640_h480_testcase_dqtdht_multi_marker.jpeg",//output file name
	//
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
		JPEGENC_YUV420_PLANAR,//frameType
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
		JPEGENC_MULTI_MARKER,
		0,//xDensity
		0,//yDensity
		0,//comLength
		NULL//pCom
	},//excfg
	{
		JPEGENC_THUMB_JPEG,
		25,
		25,
		NULL,
		0
	}
	},
	#endif
#endif
#ifdef JPEG_TESTCASE_HEADER_COMMENT
	{
	"",
	"jpeg_w640_h480_testcase_header_comment.yuv",//input file name 
	"",//thumbnail file name;
	"jpeg_comment_header_file.txt",//comment header file name 
	"jpeg_w640_h480_testcase_comment_header.jpeg",//output file name
	//
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
		JPEGENC_YUV420_PLANAR,//frameType
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
		1,//comLength,fake set 
		NULL//pCom
	},//excfg
	{
		JPEGENC_THUMB_JPEG,
		25,
		25,
		NULL,
		0
	}
	},
#endif

#ifdef JPEG_TESTCASE_HEADER_THUMBNAIL
	#ifdef JPEG_TESTCASE_HEADER_THUMBNAIL_JPEG
	{
	"",
	"jpeg_w640_h480_testcase_header_thumbnail.yuv",//input file name 
	"jpeg_w120_h96_testcase_jpeg_thumbnail.jpeg",//thumbnail file name;
	"",//comment header file name 
	"jpeg_w640_h480_testcase_jpeg_thumbnail_header.jpeg",//output file name
	//
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
		JPEGENC_YUV420_PLANAR,//frameType
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
		0,//comLength,fake set 
		NULL//pCom
	},//excfg
	{
		JPEGENC_THUMB_JPEG,
		120,
		96,
		NULL,
		1 //fake set
	}
	},
	#endif
	#ifdef  JPEG_TESTCASE_HEADER_THUMBNAIL_PALETTE_RGB8
	{
	"",
	"jpeg_w640_h480_testcase_header_thumbnail.yuv",//input file name 
	"jpeg_w120_h96_testcase_rgb24_thumbnal.rgb",//thumbnail file name;
	"",//comment header file name 
	"jpeg_w640_h480_testcase_jpeg_thumbnail_header.jpeg",//output file name
	//
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
		JPEGENC_YUV420_PLANAR,//frameType
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
		0,//comLength,fake set 
		NULL//pCom
	},//excfg
	{
		JPEGENC_THUMB_RGB24,
		120,
		96,
		NULL,
		1 //fake set
	}
	},
	#endif
	#ifdef  JPEG_TESTCASE_HEADER_THUMBNAIL_RGB24
	{
	"",
	"jpeg_w640_h480_testcase_header_thumbnail.yuv",//input file name 
	"jpeg_w120_h96_testcase_rgb24_thumbnal.rgb",//thumbnail file name;
	"",//comment header file name 
	"jpeg_w640_h480_testcase_rgb24_thumbnail_header.jpeg",//output file name
	//
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
		JPEGENC_YUV420_PLANAR,//frameType
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
		0,//comLength,fake set 
		NULL//pCom
	},//excfg
	{
		JPEGENC_THUMB_RGB24,
		120,
		96,
		NULL,
		1 //fake set
	}
	},
	#endif
#endif

#ifdef JPEG_TESTCASE_ENCODING_CODE_TYPE
	#ifdef JPEG_TESTCASE_ENCODING_WHOLE_FRAME
	{
	"",
	"jpeg_w800_h600_testcase_codingtype_rgb565.rgb",//input file name 
	"",//thumbnail file name;
	"",//comment header file name 
	"jpeg_w800_h600_testcase_codingtype_wholeframe_rgb565.jpeg",//output file name

	//
	{
		800,//inputWidth
		600,//inputHeight
		0,//xOffset
		0,//yOffset
		800,//codingWidth
		600,//codingHeight
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
		25,
		25,
		NULL,
		0
	}
	},
	#endif
	#ifdef JPEG_TESTCASE_ENCODING_SLICE_FRAME
	{
	"",
	"jpeg_w800_h600_testcase_codingtype_rgb565.rgb",//input file name 
	"",//thumbnail file name;
	"",//comment header file name 
	"jpeg_w800_h600_testcase_codingtype_sliceframe_rgb565.jpeg",//output file name

	//
	{
		800,//inputWidth
		600,//inputHeight
		0,//xOffset
		0,//yOffset
		800,//codingWidth
		600,//codingHeight
		10,//restartInterval
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
		JPEGENC_SLICED_FRAME,
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
		25,
		25,
		NULL,
		0
	}
	},
	#endif
#endif
#ifdef JPEG_TESTCASE_ENCODING_MODE
	#ifdef  JPEG_TESTCASE_ENCODING_JPEG_420_MODE
	#endif
	#ifdef JPEG_TESTCASE_ENCODING_JPEG_422_MODE 
	#endif
#endif

#ifdef JPEG_TESTCASE_INPUT_ISP
	{
	"",
	"dma_rgb565_640_480_frm7.bin",//input file name 
	"",//thumbnail file name;
	"",//comment header file name 
	"dma_rgb565_640_480_frm7.jpeg",//output file name

	//
	{
		640,//inputWidth
		480,//inputHeight
		0,//xOffset
		0,//yOffset
		640,//codingWidth
		480,//codingHeight
		10,//restartInterval
		8,//qLevel
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
		25,
		25,
		NULL,
		0
	}
	},

{
	"",
	"dma_rgb565_1280_960_frm4.bin",//input file name 
	"",//thumbnail file name;
	"",//comment header file name 
	"dma_rgb565_1280_960_frm4.jpeg",//output file name

	//
	{
		1280,//inputWidth
		960,//inputHeight
		0,//xOffset
		0,//yOffset
		1280,//codingWidth
		960,//codingHeight
		10,//restartInterval
		8,//qLevel
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
		25,
		25,
		NULL,
		0
	}
	},

	{
	"",
	"dma_uyvy422_1280_960_frm3.bin",//input file name 
	"",//thumbnail file name;
	"",//comment header file name 
	"dma_uyvy422_1280_960_frm3.jpeg",//output file name

	//
	{
		1280,//inputWidth
		960,//inputHeight
		0,//xOffset
		0,//yOffset
		1280,//codingWidth
		960,//codingHeight
		10,//restartInterval
		8,//qLevel
		NULL,//qTableLuma
		NULL,//qTableChroma
		JPEGENC_YUV422_INTERLEAVED_UYVY,//frameType
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
		25,
		25,
		NULL,
		0
	}
	},	

	{
	"",
	"dma_uyvy_2592_1944_frm1.bin",//input file name 
	"",//thumbnail file name;
	"",//comment header file name 
	"dma_uyvy_2592_1944_frm1.jpeg",//output file name

	//
	{
		2592,//inputWidth
		1944,//inputHeight
		0,//xOffset
		0,//yOffset
		2592,//codingWidth
		1944,//codingHeight
		10,//restartInterval
		8,//qLevel
		NULL,//qTableLuma
		NULL,//qTableChroma
		JPEGENC_YUV422_INTERLEAVED_UYVY,//frameType
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
		25,
		25,
		NULL,
		0
	}
	},

	{
	"",
	"dma_yuyv_1280_960_frm5.bin",//input file name 
	"",//thumbnail file name;
	"",//comment header file name 
	"dma_yuyv_1280_960_frm5.jpeg",//output file name

	//
	{
		1280,//inputWidth
		960,//inputHeight
		0,//xOffset
		0,//yOffset
		1280,//codingWidth
		960,//codingHeight
		10,//restartInterval
		8,//qLevel
		NULL,//qTableLuma
		NULL,//qTableChroma
		JPEGENC_YUV422_INTERLEAVED_YUYV,//frameType
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
		25,
		25,
		NULL,
		0
	}
	},

	{
	"",
	"dma_yuyv_2592_1944_frm1.bin",//input file name 
	"",//thumbnail file name;
	"",//comment header file name 
	"dma_yuyv_2592_1944_frm1.jpeg",//output file name

	//
	{
		2592,//inputWidth
		1944,//inputHeight
		0,//xOffset
		0,//yOffset
		2592,//codingWidth
		1944,//codingHeight
		10,//restartInterval
		8,//qLevel
		NULL,//qTableLuma
		NULL,//qTableChroma
		JPEGENC_YUV422_INTERLEAVED_YUYV,//frameType
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
		25,
		25,
		NULL,
		0
	}
	},

	{
	"",
	"isp_rgb888_640_480_frm3.bin",//input file name 
	"",//thumbnail file name;
	"",//comment header file name 
	"isp_rgb888_640_480_frm3.jpeg",//output file name

	//
	{
		640,//inputWidth
		480,//inputHeight
		0,//xOffset
		0,//yOffset
		640,//codingWidth
		480,//codingHeight
		10,//restartInterval
		8,//qLevel
		NULL,//qTableLuma
		NULL,//qTableChroma
		JPEGENC_RGB888,//frameType
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
		25,
		25,
		NULL,
		0
	}
	},

	{
	"",
	"isp_yuv420p_2592_1944_frm1.bin",//input file name 
	"",//thumbnail file name;
	"",//comment header file name 
	"isp_yuv420p_2592_1944_frm1.jpeg",//output file name

	//
	{
		2592,//inputWidth
		1944,//inputHeight
		0,//xOffset
		0,//yOffset
		2592,//codingWidth
		1944,//codingHeight
		10,//restartInterval
		8,//qLevel
		NULL,//qTableLuma
		NULL,//qTableChroma
		JPEGENC_YUV420_PLANAR,//frameType
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
		25,
		25,
		NULL,
		0
	}
	},

	{
	"",
	"isp_yuv420sp_2592_1944.bin",//input file name 
	"",//thumbnail file name;
	"",//comment header file name 
	"isp_yuv420sp_2592_1944.jpeg",//output file name

	//
	{
		2592,//inputWidth
		1944,//inputHeight
		0,//xOffset
		0,//yOffset
		2592,//codingWidth
		1944,//codingHeight
		10,//restartInterval
		8,//qLevel
		NULL,//qTableLuma
		NULL,//qTableChroma
		JPEGENC_YUV420_SEMIPLANAR,//frameType
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
		25,
		25,
		NULL,
		0
	}
	},

	{
	"",
	"isp_yuv420p_640_480.bin",//input file name 
	"",//thumbnail file name;
	"",//comment header file name 
	"isp_yuv420p_640_480.jpeg",//output file name

	//
	{
		640,//inputWidth
		480,//inputHeight
		0,//xOffset
		0,//yOffset
		640,//codingWidth
		480,//codingHeight
		10,//restartInterval
		8,//qLevel
		NULL,//qTableLuma
		NULL,//qTableChroma
		JPEGENC_YUV420_PLANAR,//frameType
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
		25,
		25,
		NULL,
		0
	}
	},

	{
	"",
	"isp_yuv420p_2592_1944.bin",//input file name 
	"",//thumbnail file name;
	"",//comment header file name 
	"isp_yuv420p_2592_1944.jpeg",//output file name

	//
	{
		2592,//inputWidth
		1944,//inputHeight
		0,//xOffset
		0,//yOffset
		2592,//codingWidth
		1944,//codingHeight
		10,//restartInterval
		8,//qLevel
		NULL,//qTableLuma
		NULL,//qTableChroma
		JPEGENC_YUV420_PLANAR,//frameType
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
		25,
		25,
		NULL,
		0
	}
	},

#endif

#ifdef JPEG_TESTCASE_PERFORMANCE
	{
	"",
	"jpeg_w640_h480_testcase_inputformat_yuv420p.yuv",//input file name 
	"",//thumbnail file name;
	"",//comment header file name 
	"jpeg_w1920_h1080_testcase_performance.jpeg",//output file name

	//
	{
		640,//inputWidth
		480,//inputHeight
		0,//xOffset
		0,//yOffset
		640,//codingWidth
		480,//codingHeight
		0,//restartInterval
		9,//qLevel
		NULL,//qTableLuma
		NULL,//qTableChroma
		JPEGENC_YUV420_SEMIPLANAR,//frameType
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
		25,
		25,
		NULL,
		0
	}
	},

#endif
#ifdef JPEG_RTLCASE
	#ifdef JPEG_RTLCASE_0_QLEVEL_L8
	{
	"case0",
	"jpeg_w240_h240_testcase_qlevel.yuvsp",//input file name 
	"",//thumbnail file name;
	"",//comment header file name 
	"jpeg_w240_h240_testcase_qlevel_8.jpeg",//output file name

	//
	{
		240,//inputWidth
		240,//inputHeight
		0,//xOffset
		0,//yOffset
		160,//codingWidth
		120,//codingHeight
		0,//restartInterval
		8,//qLevel
		NULL,//qTableLuma
		NULL,//qTableChroma
		JPEGENC_YUV420_SEMIPLANAR,//frameType
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
		25,
		25,
		NULL,
		0
	}
	},	
	#endif
	#ifdef JPEG_RTLCASE_1_INPUT_YUV420P
	{
	"case1",
	"jpeg_w640_h480_testcase_inputformat_yuv420p.yuv",//input file name 
	"",//thumbnail file name;
	"",//comment header file name 
	"jpeg_w640_h480_testcase_inputformat_yuv420p.jpeg",//output file name
	//
	{
		640,//inputWidth
		480,//inputHeight
		0,//xOffset
		0,//yOffset
		176,//codingWidth
		144,//codingHeight
		0,//restartInterval
		5,//qLevel
		NULL,//qTableLuma
		NULL,//qTableChroma
		JPEGENC_YUV420_PLANAR,//frameType
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
		25,
		25,
		NULL,
		0
	}
	},
	#endif
	#ifdef JPEG_RTLCASE_2_INPUT_YUV422_INTERLEAVED_YUYV
	{
	"case2",
	"jpeg_w640_h480_testcase_inputformat_yuyv422.yuv",//input file name 
	"",//thumbnail file name;
	"",//comment header file name 
	"jpeg_w640_h480_testcase_inputformat_yuyv422.jpeg",//output file name

	//
	{
		320,//inputWidth
		240,//inputHeight
		0,//xOffset
		0,//yOffset
		320,//codingWidth
		240,//codingHeight
		0,//restartInterval
		5,//qLevel
		NULL,//qTableLuma
		NULL,//qTableChroma
		JPEGENC_YUV422_INTERLEAVED_YUYV,//frameType
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
		25,
		25,
		NULL,
		0
	}
	},
	#endif
	#ifdef JPEG_RTLCASE_3_INPUT_RGB565
	{
	"case3",
	"jpeg_w800_h600_testcase_inputformat_rgb565.rgb",//input file name 
	"",//thumbnail file name;
	"",//comment header file name 
	"jpeg_w800_h600_testcase_inputformat_rgb565.jpeg",//output file name

	//
	{
		160,//inputWidth
		120,//inputHeight
		0,//xOffset
		0,//yOffset
		100,//codingWidth
		80,//codingHeight
		0,//restartInterval
		9,//qLevel
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
		25,
		25,
		NULL,
		0
	}
	},
	#endif
	#ifdef JPEG_RTLCASE_4_INPUT_RGB101010
	{
	"case4",
	"jpeg_w1024_h576_testcase_inputformat_rgb101010.rgb",//input file name 
	"",//thumbnail file name;
	"",//comment header file name 
	"jpeg_w1024_h576_testcase_inputformat_rgb101010.jpeg",//output file name

	//
	{
		720,//inputWidth
		576,//inputHeight
		0,//xOffset
		0,//yOffset
		720,//codingWidth
		576,//codingHeight
		0,//restartInterval
		1,//qLevel
		NULL,//qTableLuma
		NULL,//qTableChroma
		JPEGENC_RGB101010,//frameType
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
		25,
		25,
		NULL,
		0
	}
	},
	#endif
	#ifdef JPEG_RTLCASE_5_INPUT_ROTATE_90R
	{
	"case5",
	"jpeg_w640_h480_testcase_input_rotation.yuv",//input file name 
	"",//thumbnail file name;
	"",//comment header file name 
	"jpeg_w640_h480_testcase_input_rotation90R.jpeg",//output file name
	//
	{
		176,//inputWidth
		144,//inputHeight
		0,//xOffset
		0,//yOffset
		144,//codingWidth
		176,//codingHeight
		0,//restartInterval
		10,//qLevel
		NULL,//qTableLuma
		NULL,//qTableChroma
		JPEGENC_YUV420_PLANAR,//frameType
		{
			JPEGENC_RGBTOYUV_BT601,
			0,//coeffA
			0,//coeffB
			0,//coeffC
			0,//coeffE
			0//coeffF
		},//colorConversion

		JPEGENC_ROTATE_90R,
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
		25,
		25,
		NULL,
		0
	}
	},
	#endif
	#ifdef JPEG_RTLCASE_6_INPUT_ROTATE_90L
	{
	"case6",
	"jpeg_w640_h480_testcase_input_rotation.yuv",//input file name 
	"",//thumbnail file name;
	"",//comment header file name 
	"jpeg_w640_h480_testcase_input_rotation90L.jpeg",//output file name
	//
	{
		640,//inputWidth
		480,//inputHeight
		100,//xOffset
		90,//yOffset
		160,//codingWidth
		120,//codingHeight
		0,//restartInterval
		5,//qLevel
		NULL,//qTableLuma
		NULL,//qTableChroma
		JPEGENC_YUV420_PLANAR,//frameType
		{
			JPEGENC_RGBTOYUV_BT601,
			0,//coeffA
			0,//coeffB
			0,//coeffC
			0,//coeffE
			0//coeffF
		},//colorConversion

		JPEGENC_ROTATE_90L,
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
		25,
		25,
		NULL,
		0
	}
	},
	#endif
	#ifdef JPEG_RTLCASE_7_INPUT_CROP_MIDDLE
	{
	"case7",
	"jpeg_w640_h480_testcase_input_cropping.yuv",//input file name 
	"",//thumbnail file name;
	"",//comment header file name 
	"jpeg_w120_h96_testcase_input_crop_middle.jpeg",//output file name
	//
	{
		640,//inputWidth
		480,//inputHeight
		240,//xOffset
		192,//yOffset
		120,//codingWidth
		96,//codingHeight
		0,//restartInterval
		5,//qLevel
		NULL,//qTableLuma
		NULL,//qTableChroma
		JPEGENC_YUV420_PLANAR,//frameType
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
		25,
		25,
		NULL,
		0
	}	
	},
	#endif
	#ifdef JPEG_RTLCASE_8_INPUT_MIN
	{
	"case8",
	"jpeg_w96_h32_testcase_inputsize_yuv420sp.yuv",//input file name 
	"",//thumbnail file name;
	"",//comment header file name 
	"jpeg_w96_h32_testcase_inputsize_min.jpeg",//output file name
	//
	{
		96,//inputWidth
		32,//inputHeight
		0,//xOffset
		0,//yOffset
		96,//codingWidth
		32,//codingHeight
		0,//restartInterval
		9,//qLevel
		NULL,//qTableLuma
		NULL,//qTableChroma
		JPEGENC_YUV420_SEMIPLANAR,//frameType
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
		25,
		25,
		NULL,
		0
	}	
	},
	#endif
	#ifdef JPEG_RTLCASE_10_INPUT_1080P
	{
	"case10",
	"jpeg_w1920_h1080_testcase_inputsize_yuv420sp.yuv",//input file name 
	"",//thumbnail file name;
	"",//comment header file name 
	"jpeg_w1920_h1080_testcase_inputsize_1080p.jpeg",//output file name
	//
	{
		1920,//inputWidth
		1080,//inputHeight
		0,//xOffset
		0,//yOffset
		1920,//codingWidth
		1080,//codingHeight
		0,//restartInterval
		9,//qLevel
		NULL,//qTableLuma
		NULL,//qTableChroma
		JPEGENC_YUV420_SEMIPLANAR,//frameType
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
		25,
		25,
		NULL,
		0
	}	
	},
	#endif
	#ifdef JPEG_RTLCASE_11_HEADER_APP0_DOTS_PER_INCH
	{
	"case11",
	"jpeg_w640_h480_testcase_header_APP0.yuv",//input file name 
	"",//thumbnail file name;
	"",//comment header file name 
	"jpeg_w640_h480_testcase_app0_dots_per_inch.jpeg",//output file name
	//
	{
		640,//inputWidth
		480,//inputHeight
		0,//xOffset
		0,//yOffset
		128,//codingWidth
		96,//codingHeight
		0,//restartInterval
		5,//qLevel
		NULL,//qTableLuma
		NULL,//qTableChroma
		JPEGENC_YUV420_PLANAR,//frameType
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
		JPEGENC_DOTS_PER_INCH,
		JPEGENC_SINGLE_MARKER,
		10000,//xDensity
		10000,//yDensity
		0,//comLength
		NULL//pCom
	},//excfg
	{
		JPEGENC_THUMB_JPEG,
		25,
		25,
		NULL,
		0
	}
	},
	#endif
	#ifdef JPEG_RTLCASE_12_HEADER_MULTI_MARKER
	{
	"case12",
	"jpeg_w640_h480_testcase_header_dqt_dht.yuv",//input file name 
	"",//thumbnail file name;
	"",//comment header file name 
	"jpeg_w640_h480_testcase_dqtdht_multi_marker.jpeg",//output file name
	//
	{
		128,//inputWidth
		96,//inputHeight
		0,//xOffset
		0,//yOffset
		128,//codingWidth
		96,//codingHeight
		0,//restartInterval
		5,//qLevel
		NULL,//qTableLuma
		NULL,//qTableChroma
		JPEGENC_YUV420_PLANAR,//frameType
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
		JPEGENC_MULTI_MARKER,
		0,//xDensity
		0,//yDensity
		0,//comLength
		NULL//pCom
	},//excfg
	{
		JPEGENC_THUMB_JPEG,
		25,
		25,
		NULL,
		0
	}
	},
	#endif
	#ifdef JPEG_RTLCASE_13_HEADER_COMMENT
	{
	"case13",
	"jpeg_w640_h480_testcase_header_comment.yuv",//input file name 
	"",//thumbnail file name;
	"jpeg_comment_header_file.txt",//comment header file name 
	"jpeg_w640_h480_testcase_comment_header.jpeg",//output file name
	//
	{
		320,//inputWidth
		240,//inputHeight
		0,//xOffset
		0,//yOffset
		320,//codingWidth
		240,//codingHeight
		0,//restartInterval
		5,//qLevel
		NULL,//qTableLuma
		NULL,//qTableChroma
		JPEGENC_YUV420_PLANAR,//frameType
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
		1,//comLength,fake set 
		NULL//pCom
	},//excfg
	{
		JPEGENC_THUMB_JPEG,
		25,
		25,
		NULL,
		0
	}
	},
	#endif
	#ifdef JPEG_RTLCASE_14_HEADER_THUMBNAIL_JPEG
	{
	"case14",
	"jpeg_w640_h480_testcase_header_thumbnail.yuv",//input file name 
	"jpeg_w120_h96_testcase_jpeg_thumbnail.jpeg",//thumbnail file name;
	"",//comment header file name 
	"jpeg_w640_h480_testcase_jpeg_thumbnail_header.jpeg",//output file name
	//
	{
		160,//inputWidth
		120,//inputHeight
		0,//xOffset
		0,//yOffset
		160,//codingWidth
		120,//codingHeight
		0,//restartInterval
		5,//qLevel
		NULL,//qTableLuma
		NULL,//qTableChroma
		JPEGENC_YUV420_PLANAR,//frameType
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
		0,//comLength,fake set 
		NULL//pCom
	},//excfg
	{
		JPEGENC_THUMB_JPEG,
		120,
		96,
		NULL,
		1 //fake set
	}
	},
	#endif
	#ifdef JPEG_RTLCASE_15_HEADER_THUMBNAIL_PALETTE_RGB8
	{
	"case15",
	"jpeg_w640_h480_testcase_header_thumbnail.yuv",//input file name 
	"jpeg_w120_h96_testcase_rgb24_thumbnal.rgb",//thumbnail file name;
	"",//comment header file name 
	"jpeg_w640_h480_testcase_jpeg_thumbnail_header.jpeg",//output file name
	//
	{
		160,//inputWidth
		120,//inputHeight
		0,//xOffset
		0,//yOffset
		160,//codingWidth
		120,//codingHeight
		0,//restartInterval
		5,//qLevel
		NULL,//qTableLuma
		NULL,//qTableChroma
		JPEGENC_YUV420_PLANAR,//frameType
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
		0,//comLength,fake set 
		NULL//pCom
	},//excfg
	{
		JPEGENC_THUMB_RGB24,
		120,
		96,
		NULL,
		1 //fake set
	}
	},
	#endif
	#ifdef JPEG_RTLCASE_16_ENCODING_SLICE_FRAME
	{
	"case16",
	"jpeg_w800_h600_testcase_codingtype_rgb565.rgb",//input file name 
	"",//thumbnail file name;
	"",//comment header file name 
	"jpeg_w800_h600_testcase_codingtype_sliceframe_rgb565.jpeg",//output file name

	//
	{
		800,//inputWidth
		600,//inputHeight
		0,//xOffset
		0,//yOffset
		800,//codingWidth
		600,//codingHeight
		10,//restartInterval
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
		JPEGENC_SLICED_FRAME,
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
		25,
		25,
		NULL,
		0
	}
	}
	#endif
#endif
};

#endif

#ifdef __VIDEOSTABTEST__

CAMSTABCFG camstab_enc_test[] ={
#ifdef STAB_RTLCASE
	{
		"case80",
		"camstab_w104_h104_yuv420sp.yuv"	,
		"",

		104,
		104,
		104,
		96,
		96,
		VIDEOSTB_YUV420_SEMIPLANAR
	},
#else
	{
		"",
		"camstab_w104_h104_yuv420sp.yuv"	,
		"",

		104,
		104,
		104,
		96,
		96,
		VIDEOSTB_YUV420_SEMIPLANAR
	},

	{
		"",
		"camstab_w352_h288_rgb565.rgb"	,
		"",

		350,
		288,
		352,
		340,
		252,
		VIDEOSTB_RGB565
	},


	{
		"",
		"camstab_w640_y480_yuv420sp.yuv"	,
		"",

		640,
		480,
		640,
		624,
		468,
		VIDEOSTB_YUV420_SEMIPLANAR
	},
	{
		"",
		"camstab_w800_h600_rgb32.rgb"	,
		"",

		792,
		594,
		800,
		780,
		572,
		VIDEOSTB_RGB888
	},
#endif
};
#endif

#endif


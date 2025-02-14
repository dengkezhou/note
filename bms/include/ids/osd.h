#ifndef __INFOTM_OSD_H__
#define __INFOTM_OSD_H__

#define bool    _Bool
#define true    1    
#define false   0    


#define OVCDCR			0x1000
#define OVCPCR			0x1004
#define OVCBKCOLOR		0x1008
#define OVCWPR			0x100c
#define OVCW0CR			0x1080
#define OVCW0PCAR		0x1084
#define OVCW0PCBR		0x1088	
#define OVCW0VSSR		0x108c
#define OVCW0CMR		0x1090
#define OVCW0B0SAR		0x1094
#define OVCW0B1SAR		0x1098
#define OVCW0B2SAR		0x109c
#define OVCW0B3SAR		0x10a0
#define OVCW1CR			0x1100
#define OVCW1PCAR		0x1104
#define OVCW1PCBR		0x1108
#define OVCW1PCCR		0x110c
#define OVCW1VSSR		0x1110
#define OVCW1CKCR		0x1114
#define OVCW1CKR		0x1118
#define OVCW1CMR		0x111c
#define OVCW1B0SAR		0x1120
#define OVCW1B1SAR		0x1124
#define OVCW1B2SAR		0x1128
#define OVCW1B3SAR		0x112c	
/* yuv to rgb */	
#define OVCBRB0SAR		0x1300
#define OVCBRB1SAR		0x1304
#define OVCBRB2SAR		0x1308
#define OVCBRB3SAR		0x130c

#define OVCOMC			0x1310
#define OVCOEF11		0x1314
#define OVCOEF12		0x1318
#define CICOEF13		0x131c
#define OVCOEF21		0x1320
#define OVCOEF22		0x1324
#define OVCOEF23		0x1328
#define OVCOEF31		0x132c
#define OVCOEF32		0x1330
#define OVCOEF33		0x1334

/* for prescaler */
#define OVCPSCCR		0x13c0
#define OVCPSCPCR		0x13c4
#define OVCPSVSSR		0x13c8
#define OVCPSB0SAR		0x13cc
#define OVCPSB1SAR		0x13d0
#define OVCPSB2SAR		0x13d4
#define OVCPSB3SAR		0x13d8
#define OVCPSCB0SAR		0x13dc
#define OVCPSCB1SAR		0x13e0
#define OVCPSCB2SAR		0x13e4
#define OVCPSCB3SAR		0x13e8
/* for scaler after osd */
#if 0
#define SCLIFSR			0x5100
#define SCLOFSR			0x5104
#define SCLOFOR			0x5108
#define SCLCR			0x510c
#define HSCLSET0(n)		(0x5200 + 0x4 * n)
#define	HSCLSET1(n)		(0x5300 + 0x4 * n)
#define HSCLSET2(n)		(0x5400 + 0x4 * n)
#define HSCLSET3(n)		(0x5500 + 0x4 * n)
#define VSCLSET0(n)		(0x5600 + 0x4 * n)
#define VSCLSET1(n)		(0x5700 + 0x4 * n)
#else
#define SCALER_RSL_IN_V_H           (0x5000)
#define SCALER_RSL_OUT_V_H          (0x5004)
#define SCALER_RATIO_H              (0x5008)
#define SCALER_RATIO_V              (0x500c)
#define SCALER_CNTL_REG             (0x5010)
#define SCALER_ALG_ZOOM_IN			(0x5014)
#define SCALER_ALG_ZOOM_OUT			(0x5018)
#define SCALER_COE_INTERP_00		(0x501c)
#define SCALER_COE_INTERP_01		(0x5020)
#define SCALER_COE_INTERP_02		(0x5024)
#define SCALER_COE_INTERP_03		(0x5028)
#define SCALER_COE_INTERP_04		(0x502c)
#define SCALER_COE_INTERP_05		(0x5030)
#define SCALER_COE_INTERP_06		(0x5034)
#define SCALER_COE_INTERP_07		(0x5038)
#define SCALER_COE_INTERP_08		(0x503c)
#define SCALER_COE_INTERP_09		(0x5040)
#define SCALER_COE_INTERP_10		(0x5044)
#define SCALER_COE_INTERP_11		(0x5048)
#define SCALER_COE_INTERP_12		(0x504c)
#define SCALER_COE_INTERP_13		(0x5050)
#define SCALER_COE_INTERP_14		(0x5054)
#define SCALER_COE_INTERP_15		(0x5058)
#define SCALER_COE_INTERP_16		(0x505c)
#define SCALER_COE_INTERP_17		(0x5060)
#define SCALER_COE_INTERP_18		(0x5064)
#define SCALER_COE_INTERP_19		(0x5068)
#define SCALER_COE_INTERP_20		(0x506c)
#define SCALER_COE_INTERP_21		(0x5070)
#define SCALER_COE_INTERP_22		(0x5074)
#define SCALER_COE_INTERP_23		(0x5078)
#define SCALER_COE_INTERP_24		(0x507c)
#define SCALER_COE_INTERP_25		(0x5080)
#define SCALER_COE_INTERP_26		(0x5084)
#define SCALER_COE_INTERP_27		(0x5088)
#define SCALER_COE_INTERP_28		(0x508c)
#define SCALER_COE_INTERP_29		(0x5090)
#define SCALER_COE_INTERP_30		(0x5094)
#define SCALER_COE_INTERP_31		(0x5098)
#define SCALER_COE_INTERP_32		(0x509c)
#define SCALER_COE_INTERP_33		(0x50a0)
#define SCALER_COE_INTERP_34		(0x50a4)
#define SCALER_COE_INTERP_35		(0x50a8)
#define SCALER_COE_INTERP_36		(0x50ac)
#define SCALER_COE_INTERP_37		(0x50b0)
#define SCALER_COE_INTERP_38		(0x50b4)
#define SCALER_COE_INTERP_39		(0x50b8)
#define SCALER_COE_INTERP_40		(0x50bc)
#define SCALER_COE_INTERP_41		(0x50c0)
#define SCALER_COE_INTERP_42		(0x50c4)
#define SCALER_COE_INTERP_43		(0x50c8)
#define SCALER_COE_INTERP_44		(0x50cc)
#define SCALER_COE_INTERP_45		(0x50d0)
#define SCALER_COE_INTERP_46		(0x50d4)
#define SCALER_COE_INTERP_47		(0x50d8)
#define SCALER_COE_INTERP_48		(0x50dc)
#define SCALER_COE_INTERP_49		(0x50e0)
#define SCALER_COE_INTERP_50		(0x50e4)
#define SCALER_COE_INTERP_51		(0x50e8)
#define SCALER_COE_INTERP_52		(0x50ec)
#define SCALER_COE_INTERP_53		(0x50f0)
#define SCALER_COE_INTERP_54		(0x50f4)
#define SCALER_COE_INTERP_55		(0x50f8)
#define SCALER_COE_INTERP_56		(0x50fc)
#define SCALER_COE_INTERP_57		(0x5100)
#define SCALER_COE_INTERP_58		(0x5104)
#define SCALER_COE_INTERP_59		(0x5108)
#define SCALER_COE_INTERP_60		(0x510c)
#define SCALER_COE_INTERP_61		(0x5110)
#define SCALER_COE_INTERP_62		(0x5114)
#define SCALER_COE_INTERP_63		(0x5118)
#define SCALER_CNT_RSL_IN_V_H		(0x511c)
#define SCALER_CNT_RSL_OUT_V_H		(0x5120)

#endif

#define OVCW0PAL0		0x1400
#define OVCW1PAL0		0x1800
#define OVCPSPAL0		0x1f80

// OVCDCR
#define OVCDCR_IMAGE_BYPASS			(22)
#define OVCDCR_W1_AUTOBUFFER_SOURCE	(14)
#define OVCDCR_W0_AUTOBUFFER_SOURCE	(13)
#define OVCDCR_SP_LOAD_EN	(12)
#define OVCDCR_LOAD_EN		(11)
#define OVCDCR_ScalerMode	(10)
#define OVCDCR_Enrefetch	(9)
#define OVCDCR_Enrelax		(8)
#define OVCDCR_WaitTime		(4)
#define OVCDCR_SafeBand		(3)
#define OVCDCR_AllFetch		(2)
#define OVCDCR_IfType		(1)
#define OVCDCR_Interlace	(0)

// OVCPCR
#define OVCPCR_UPDATE_PAL	(15)
#define OVCPCR_W1PALFM		(3)
#define OVCPCR_W0PALFM		(0)

#define OVCWPR_OSDWinY      (12)
#define OVCWPR_OSDWinX      (0) 

// OVCWxCR
#define OVCWxCR_BUFSEL		(17)
#define OVCWxCR_BUFAUTOEN	(16)
#define OVCWxCR_BUFNUM		(14)
#define OVCWxCR_HAWSWP(x)	(9 + x)
#define OVCWxCR_BYTSWP(x)   (10 + x)
#define OVCWxCR_Bits4SWP(x)	(11 + x)
#define OVCWxCR_Bits2SWP(x)	(12 + x)
#define OVCWxCR_BITSWP(x)	(13 + x)
#define OVCWxCR_ALPHA_SEL	(8)
#define OVCWxCR_BLD_PIX		(7)
#define OVCWxCR_RBEXG       (6)
#define OVCWxCR_BPPMODE		(1)
#define OVCWxCR_ENWIN		(0)

#define	SCALER_INPUT_FRAME_VER	(16)
#define SCALER_INPUT_FRAME_HOR	(0)
#define	SCALER_OUTPUT_FRAME_VER	(16)
#define SCALER_OUTPUT_FRAME_HOR	(0)
#define	SCALER_OFFSET_FRAME_VER	(16)
#define SCALER_OFFSET_FRAME_HOR	(0)
#define SCALER_CTRL_VROUND		(31)
#define SCALER_CTRL_VPASSBY		(30)
#define SCALER_CTRL_VSCALING_ZOOMOUT    (26)
#define SCALER_CTRL_VSCALING_ZOOMIN		(16)
#define SCALER_CTRL_HROUND		(15)
#define SCALER_CTRL_HPASSBY		(14)
#define SCALER_CTRL_HSCALING_ZOOMOUT	(10)
#define SCALER_CTRL_HSCALING_ZOOMIN	    (0)

// OVCWxPCAR
#define OVCWxPCAR_FIELDSTATUS	(31)
#define OVCWxPCAR_BUFSTATUS	(29)
#define OVCWxPCAR_LeftTopY	(16)
#define OVCWxPCAR_LeftTopX	(0)

// OVCWxPCBR
#define OVCWxPCBR_RightBotY	(16)
#define OVCWxPCBR_RightBotX	(0)

#define OVCWxPCCR_ALPHA0_R	(20)
#define OVCWxPCCR_ALPHA0_G	(16)
#define OVCWxPCCR_ALPHA0_B	(12)
#define OVCWxPCCR_ALPHA1_R	(8)
#define OVCWxPCCR_ALPHA1_G	(4)
#define OVCWxPCCR_ALPHA1_B	(0)

#define OVCWxCKCR_KEYBLEN	(26)
#define OVCWxCKCR_KEYEN		(25)
#define OVCWxCKCR_DIRCON	(24)
#define OVCWxCKCR_COMPKEY	(0)


//OVCWVSSR
#define OVCWVSSR_VW_WIDTH	(0)

//OVCWCMRx
#define	OVCWCMRx_ENABLE		(24)
#define OVCWCMRx_COLOR		(0)
// OVCOMC
#define OVCOMC_ToRGB		(31)
#define OVCOMC_OddEven		(24)
#define OVCOMC_BitSwap		(20)
#define OVCOMC_Bits2Swap	(19)
#define OVCOMC_Bits4Swap	(18)
#define OVCOMC_ByteSwap		(17)
#define OVCOMC_HawSwap		(16)
#define OVCOMC_oft_b		(8)
#define OVCOMC_oft_a		(0)

#define OSD_IMAGE_PAL_BPP1      0     
#define OSD_IMAGE_PAL_BPP2      1    
#define OSD_IMAGE_PAL_BPP4      2     
#define OSD_IMAGE_PAL_BPP8      3     
#define OSD_IMAGE_RGB_BPP8_1A232    4 
#define OSD_IMAGE_RGB_BPP16_565     5 
#define OSD_IMAGE_RGB_BPP16_1A555   6
#define OSD_IMAGE_RGB_BPP16_I555    7 
#define OSD_IMAGE_RGB_BPP18_666     8
#define OSD_IMAGE_RGB_BPP18_1A665   9 
#define OSD_IMAGE_RGB_BPP19_1A666   10
#define OSD_IMAGE_RGB_BPP24_888     11
#define OSD_IMAGE_RGB_BPP24_1A887   12
#define OSD_IMAGE_RGB_BPP25_1A888   13
#define OSD_IMAGE_RGB_BPP28_4A888   14
#define OSD_IMAGE_RGB_BPP16_4A444   15
#define OSD_IMAGE_RGB_BPP32_8A888   16
#define OSD_IMAGE_YUV_420SP     17 
#define OSD_IMAGE_RGB_BPP32_888A    18
#define OSD_IMAGE_RGB_BPP16_555A    19
#define OSD_IMAGE_RGB_BPP16_555I    20
#define OSD_IMAGE_PAL_DEFAULT	    0xff

#define OSD_PALLETE_TABLE		7

#define Min(x, y)		 ((x)>(y)?(y):(x))

struct dma_buffer {
	void *vir_addr;
	uint64_t phy_addr;
	int size;
	int flags;
};

#define DISABLE		0
#define ENABLE		1

enum osd_alpha_type {
	ALPHA_PER_PLANE,
	ALPHA_PER_PIXEL,
	ALPHA_DEFAULT,
};

enum osd_channel {
	WINDOWS0,
	WINDOWS1,
	BOTH_CHANNEL,
};

enum win_fetch_buf {
	FETCH_BUF0,
	FETCH_BUF1,
	FETCH_BUF2,
	FETCH_BUF3,
};

enum win_buf_ctrl {
	BUF_FIXED,
	BUF_AUTO_CHANGE,
};

enum win_buf_num {
	BUF_NUM1,
	BUF_NUM2,
	BUF_NUM3,
	BUF_NUM4,
};

enum palette_mode {
	OSD_ARGB888,
	OSD_RGB888,
	OSD_ARGB666,
	OSD_ARGB665,
	OSD_RGB666,
	OSD_ARGB555,
	OSD_RGB565,
};

enum scaler_mode {
	SCALER_AFTER_OSD_MODULE,
	SCALER_BEFORE_OSD_MODULE,
};

enum output_format {
	IF_RGB,
	IF_ITU_R
};

enum TVIF_MODE {
	PROGRESSIVE,
	INTERLACE,
};

struct osd_output_format {
	enum output_format iftype;
	enum TVIF_MODE interlace;
};

enum alpha_sel {
	ALPHA_KEY,
	ALPHA_NOKEY,
};

enum alpha_blend {
	ALPHA_PLANE_BLENDING,
	ALPHA_PIXEL_BLENDING,
};

enum colorkey_dir {
	OSD_COLORKEY_DIR_MATCH_FORGROUND,
	OSD_COLORKEY_DIR_MATCH_BACKGROUND,
};

enum osd_pixel_swap {
	OSD_HALFWORDSWAP,
	OSD_BYTESWAP,
	OSD_BIT4SWAP,
	OSD_BIT2SWAP,
	OSD_BIT1SWAP,
	OSD_EXCHANGERB,
	OSD_DEFAULT,
};

struct osd_cfg {
	enum osd_channel mode;
	int interlaced;
	int ituInterface;
	int screenWidth;
	int screenHeight;
	int gbcolor;
};

struct osd_yuv {
	int enable;
	int out_oft_b;
	int out_oft_a;
	int out_coef[9];
};

struct osd_swap {
	int enable;
	int swap;
};

struct osd_buf_mode {
	int bufsel;
	int bufauto;
	int bufnum;
};

struct osd_xy {
	int leftx;
	int lefty;
	int rightx;
	int righty;
};

struct osd_pallete {
	uint32_t format;
	uint32_t tableLength;
	const uint32_t *table;
};

struct osd_mapcolor {
	bool enable;
	int color;
};

struct osd_dma {
	int dma_num;
	struct dma_buffer buf[4];
};

struct prescaler_para {
	int window;
	int format;
	int x;
	int y;
	struct osd_dma *dma;
};

struct osd_alpha {
	uint32_t path;
	uint32_t blendmode;
	uint32_t alpha0_r;
	uint32_t alpha0_g;
	uint32_t alpha0_b;
	uint32_t alpha1_r;
	uint32_t alpha1_g;
	uint32_t alpha1_b;
};

struct osd_scaler_case {
	int input_h;
	int input_v;
	int output_h;
	int output_v;
};

struct osd_size {
	int height;
	int width;
};

#define OSD_SIZE_INIT(_height, _width)	\
{ \
	.height = _height,					\
	.width = _width,					\
}

struct osd_colorkey {
	int enable;
	int enableBlend;
	int dircon;
	int compkey;
	int colval;
};

struct osd_scaler {
	int enable;
	int roundpolicy;
	int zoomout;
	int zoomin;
};

struct osd_win_cfg {
	int nr;
	struct osd_buf_mode buf_mode;
	bool exchangeRB;
	struct osd_swap swap;
	int format;
	struct osd_xy coord;
	struct osd_mapcolor mapcolor;
	struct osd_dma dma;
	struct osd_pallete pallete;
	/* only for windows 1 */
	struct osd_alpha alpha;
	struct osd_colorkey colorkey;
};

enum osd_test {
	OSD_TEST_CASE_CHECKREGS = 1,
	OSD_TEST_CASE_BPPMODE,
	OSD_TEST_CASE_PREBPPMODE,
	OSD_TEST_CASE_COLORKEY,  
	OSD_TEST_CASE_MAPCOLOR, 
	OSD_TEST_CASE_ALPHA,
	OSD_TEST_CASE_POSITION,  
	OSD_TEST_CASE_DITHER, 
	OSD_TEST_CASE_PRE_SCALER,
	OSD_TEST_CASE_AFT_SCALER,
	OSD_TEST_CASE_BUFFAUTO,
	OSD_TEST_CASE_YUV,
	OSD_TEST_CASE_PERFORMANCE,
	OSD_TEST_CASE_MAX
};


#define OSD_TEST_CASE_BIT1SWAP 1
#define OSD_TEST_CASE_BIT2SWAP 2
#define OSD_TEST_CASE_BIT4SWAP 3
#define OSD_TEST_CASE_BYTESWAP 4
#define OSD_TEST_CASE_HALFWORDSWAP 5
#define OSD_TEST_CASE_EXCHANGERB 6

#endif

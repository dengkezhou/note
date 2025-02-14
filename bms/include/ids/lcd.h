#ifndef __INFOTM_LCD_H__
#define __INFOTM_LCD_H__

#define LCDCON1				(0x000)   //LCD control 1        
#define LCDCON2             (0x004)   //LCD control 2        
#define LCDCON3             (0x008)   //LCD control 3        
#define LCDCON4             (0x00c)   //LCD control 4        
#define LCDCON5             (0x010)   //LCD control 5        
#define LCDCON6             (0x018)                          
#define LCDVCLKFSR			(0x030)
#define IDSINTPND           (0x054)   //LCD Interrupt pending
#define IDSSRCPND           (0x058)   //LCD Interrupt source 
#define IDSINTMSK           (0x05c)   //LCD Interrupt mask   

// rIDS_LCDCON1
#define LCDCON1_LINECNT		18	// [29:18]
#define LCDCON1_CLKVAL			8	// [17:8]
#define LCDCON1_VMMODE		7	// [7:7]
#define LCDCON1_PNRMODE		5
#define LCDCON1_STNBPP			1
#define LCDCON1_ENVID			0	// [0:0]

// rIDS_LCDCON2
#define LCDCON2_VBPD			16	// [26:16]
#define LCDCON2_VFPD			0	// [10:0]

// rIDS_LCDCON3
#define LCDCON3_VSPW			16	// [26:16]
#define LCDCON3_HSPW			0	// [10:0]

// rIDS_LCDCON4
#define LCDCON4_HBPD 			16	// [26:16]
#define LCDCON4_HFPD			0	// [10:0]

// rIDS_LCDCON5
#define LCDCON5_RGB565			31
#define LCDCON5_RGBORDER		24	// [29:24]
#define LCDCON5_CONFIGORDER		20	// [22:20] 0->dsi24bpp, 1->dsi16bpp1, 2->dsi16bpp2,3->dsi16bpp3,4->dsi18bpp1,5->dsi18bpp2
#define LCDCON5_VSTATUS		15	// [16:15]
#define LCDCON5_HSTATUS 		13	// [14:13]
#define LCDCON5_DSPTYPE		11	// [12:11]
#define LCDCON5_INVVCLK		10	// [10:10]
#define LCDCON5_INVVLINE		9	// [9:9]
#define LCDCON5_INVVFRAME		8	// [8:8]
#define LCDCON5_INVVD			7	// [7:7]
#define LCDCON5_INVVDEN		6	// [6:6]
#define LCDCON5_INVPWREN		5	// [5:5]
#define LCDCON5_PWREN			3	// [3:3]

// rIDS_LCDCON6
#define LCDCON6_LINEVAL 		16	// [26:16]
#define LCDCON6_HOZVAL			0	// [10:0]

// rIDS_LCDVCLKFSR
#define LCDVCLKFSR_CDOWN 		24	// [27:24]
#define LCDVCLKFSR_RFRM_NUM 	16	// [21:16]
#define LCDVCLKFSR_CLKVAL 		4	// [13:4]
#define LCDVCLKFSR_VCLKFAC 	0	// [0:0]

// rIDS_IDSINTPND
#define IDSINTPND_TVIFINT	7
#define IDSINTPND_OSDW2INT 	6	// [6:6]
#define IDSINTPND_I80INT 		5	// [5:5]
#define IDSINTPND_OSDERR 		4	// [4:4]
#define IDSINTPND_OSDW1INT 	3	// [3:3]
#define IDSINTPND_OSDW0INT 	2	// [2:2]
#define IDSINTPND_VCLKINT 		1	// [1:1]
#define IDSINTPND_LCDINT 		0	// [0:0]

// rIDS_IDSSRCPND
#define IDSSRCPND_OSDW2INT 	6	// [6:6]
#define IDSSRCPND_I80INT 		5	// [5:5]
#define IDSSRCPND_OSDERR 		4	// [4:4]
#define IDSSRCPND_OSDW1INT 	3	// [3:3]
#define IDSSRCPND_OSDW0INT 	2	// [2:2]
#define IDSSRCPND_VCLKINT 		1	// [1:1]
#define IDSSRCPND_LCDINT 		0	// [0:0]

// rIDS_IDSINTMSK
#define IDSINTMSK_OSDW2INT 	6	// [6:6]
#define IDSINTMSK_I80INT 		5	// [5:5]
#define IDSINTMSK_OSDERR 		4	// [4:4]
#define IDSINTMSK_OSDW1INT 	3	// [3:3]
#define IDSINTMSK_OSDW0INT 	2	// [2:2]
#define IDSINTMSK_VCLKINT 		1	// [1:1]
#define IDSINTMSK_LCDINT 		0	// [0:0]

// interrupt offset, "which" parameter.
#define IDS_INTR_WIN2		6
#define IDS_INTR_I80		5
#define IDS_INTR_OSDERR	4
#define IDS_INTR_WIN1		3
#define IDS_INTR_WIN0		2
#define IDS_INTR_VCLK		1
#define IDS_INTR_LCD		0

enum RGB_ORDER {
	RGB_ORDER,
	RBG_ORDER,
	GRB_ORDER,
	GBR_ORDER,
	BRG_ORDER,
	BGR_ORDER,
};

enum BPP_MODE {
	RGB888,
	RGB565,
};

enum EXT_DISPLAY_TYPE {
	TFT_LCD,
	I80_LCD,
	TV_DISPLAY,
};

enum LCD_TYPE {
	LCD_TYPE_320_240,
	LCD_TYPE_640_480,
	LCD_TYPE_800_480,
	LCD_TYPE_1024_768,
	LCD_TYPE_1920_1080,
};

struct lcd_param {
	char name[20];
	int mPixelClock;          
	int mInterlaced;           
	int mHActive;             
	int mHBackPorch;           
	int mHFrontPorch;             
	int mHSyncPulseWidth;     
	int mHSyncPolarity;        
	int mVActive;             
	int mVBackPorch;           
	int mVFrontPorch;             
	int mVSyncPulseWidth;     
	int mVSyncPolarity;      
	int VclkPolarity;
	int VDPolarity;
	int VdenPolarity;
	int Vpwren;
	int Pwren;
	int rgb_seq;
	int rgb_bpp;
	int display_type;
};

#endif

#ifndef __CVBS_H__
#define __CVBS_H__

#include <linux/list.h>

#define CVBS_DEBUG
#ifdef CVBS_DEBUG
#define cvbs_dbg(fmt...)     printf(fmt)
#else
#define cvbs_dbg(...)        do {} while (0)
#endif
#define cvbs_err(fmt...)     printf(fmt)

#define TVIF_BASE_ADDR      (0x2000)

#define TVIF_CLK_CFG_ADDR       (TVIF_BASE_ADDR+0x00)
#define TVIF_CFG_ADDR           (TVIF_BASE_ADDR+0x04)
#define TVIF_COEF11_ADDR        (TVIF_BASE_ADDR+0x08)
#define TVIF_COEF12_ADDR        (TVIF_BASE_ADDR+0x0C)
#define TVIF_COEF13_ADDR        (TVIF_BASE_ADDR+0x10)
#define TVIF_COEF21_ADDR        (TVIF_BASE_ADDR+0x14)
#define TVIF_COEF22_ADDR        (TVIF_BASE_ADDR+0x18)
#define TVIF_COEF23_ADDR        (TVIF_BASE_ADDR+0x1C)
#define TVIF_COEF31_ADDR        (TVIF_BASE_ADDR+0x20)
#define TVIF_COEF32_ADDR        (TVIF_BASE_ADDR+0x24)
#define TVIF_COEF33_ADDR        (TVIF_BASE_ADDR+0x28)
#define TVIF_MATRIX_CFG_ADDR    (TVIF_BASE_ADDR+0x2C)
#define TVIF_UBA1_LEN_ADDR      (TVIF_BASE_ADDR+0x30)
#define TVIF_UNBA_LEN_ADDR      (TVIF_BASE_ADDR+0x34)
#define TVIF_UBA2_LEN_ADDR      (TVIF_BASE_ADDR+0x38)
#define TVIF_LBA1_LEN_ADDR      (TVIF_BASE_ADDR+0x3C)
#define TVIF_LNBA_LEN_ADDR      (TVIF_BASE_ADDR+0x40)
#define TVIF_LBA2_LEN_ADDR      (TVIF_BASE_ADDR+0x44)
#define TVIF_BLANK_LEN_ADDR     (TVIF_BASE_ADDR+0x48)
#define TVIF_VIDEO_LEN_ADDR     (TVIF_BASE_ADDR+0x4C)
#define TVIF_HSYNC_ADDR         (TVIF_BASE_ADDR+0x50)
#define TVIF_VSYNC_UPPER_ADDR   (TVIF_BASE_ADDR+0x54)
#define TVIF_VSYNC_LOWER_ADDR   (TVIF_BASE_ADDR+0x58)
#define TVIF_DISP_XSIZE_ADDR    (TVIF_BASE_ADDR+0x5C)
#define TVIF_DISP_YSIZE_ADDR    (TVIF_BASE_ADDR+0x60)
#define TVIF_STATUS_ADDR        (TVIF_BASE_ADDR+0x64)

#define TVIF_CLK_CFG_EN_CLOCK           (31)
#define TVIF_CLK_CFG_PB_CLOCK           (11)
#define TVIF_CLK_CFG_DIV2_CLOCK         (10)
#define TVIF_CLK_CFG_INV_CLOCK          (9) 
#define TVIF_CLK_CFG_SEL_CLOCK          (8) 
#define TVIF_CLK_CFG_DIVER_CLOCK        (0) 
                                            
#define TVIF_CFG_TVIF_EN                (31)
#define TVIF_CFG_ITU601_656n            (30)
#define TVIF_CFG_BIT16ofITU601          (29)
#define TVIF_CFG_DIRECT_DATA            (28)
#define TVIF_CFG_BITSWAP                (18)
#define TVIF_CFG_DATA_ORDER             (16)
#define TVIF_CFG_INV_VSYNC              (13)
#define TVIF_CFG_INV_HSYNC              (12)
#define TVIF_CFG_INV_HREF               (11)
#define TVIF_CFG_INV_FIELD              (10)
#define TVIF_CFG_Begin_by_EAV           (0) 
                                            
#define TVIF_MATRIX_CFG_toRGB           (31)
#define TVIF_MATRIX_CFG_PASSBY          (30)
#define TVIF_MATRIX_CFG_INV_MSB_IN      (29)
#define TVIF_MATRIX_CFG_INV_MSB_OUT     (28)
#define TVIF_MATRIX_CFG_OFT_B           (8) 
#define TVIF_MATRIX_CFG_OFT_A           (0) 
                                            
#define TVIF_HSYNC_VBI_CTRL             (30)
#define TVIF_HSYNC_DELAY                (16)
#define TVIF_HSYNC_EXTEND               (0) 
                                            
#define TVIF_VSYNC_DELAY                (16)
#define TVIF_VSYNC_EXTEND               (0) 

#define TV_MODE							2

enum cvbs_test_case {
	CVBS_TEST_CASE_CHECKREGS,
	CVBS_TEST_CASE_DISPLAY,
	CVBS_TEST_CASE_IRQ,
};	

enum cvbs_display_type {
	f_PAL,
	f_NTSC,
};

enum cvbs_matrix_type {
	MATRIX_RGB2YUV,
	MATRIX_BYPASS,
};

enum cvbs_interface {
	CVBS_ITU656,
	CVBS_ITU601,
	CVBS_ITU1120,
};

enum cvbs_width {
	CVBS_8BIT,
	CVBS_16BIT,
	CVBS_24BIT,
};

enum cvbs_type {
	CVBS_YUV,
	CVBS_RGB,
};

enum cvbs_line_begin {
	LINE_WITH_BLANK,
	LINE_WITH_EAV,
};

struct cvbs_cfg {
	int itu601_656n;
	int Bit16ofITU60;
	int Direct_data; 
	int bitsSwap;
	int dataOrder;
	int invVsync;
	int invHsync;
	int invHref;
	int invField;
	int beginEAV;
};


struct cvbs_coef {
	int out_oft_b;
	int out_oft_a;
	int out_coef11;
	int out_coef12;
	int out_coef13;
	int out_coef21;
	int out_coef22;
	int out_coef23;
	int out_coef31;
	int out_coef32;
	int out_coef33;
};

struct cvbs_matrix {
	int mode;
	int bypass;
	int inv_MSB_in;     // switch input cb cr 
	int inv_MSB_out;    // switch output cb cr
	struct cvbs_coef coef;
};

struct cvbs_len_cfg {
	int uba1_len;
	int unba_len;
	int uba2_len;
	int lba1_len;
	int lnba_len;
	int lba2_len;
	int blank_len;
	int video_len;
};

struct cvbs_sync_cfg {
	int Hsync_VBI_ctrl;
	int Hsync_delay;
	int Hsync_extend;
	int Vsync_delay_upper;
	int Vsync_extend_upper;
	int Vsync_delay_lower;
	int Vsync_extend_lower;
};

struct cvbs_display {
	int xsize;
	int ysize;
};

struct cvbs_default_cfg {
	struct cvbs_display display;
	struct cvbs_sync_cfg sync_cfg;
	struct cvbs_len_cfg len_cfg;
	struct cvbs_matrix param;
	struct cvbs_cfg cfg;
};

struct cvbs_i2c {
	uint8_t addr;
	uint8_t val;
};

struct cvbs_i2c_cfg {
	char name[64];
	int i2c_num;
	int i2c_addr;
	int cvbs_reset;
};

struct cvbs_dev {
	char *name;
	struct list_head link;
	int (*config)(void);
	int (*open)(void);
	int (*close)(void);
};

extern int cv2880_init(void);
extern int rtl_cvbs_init(void);

extern int cvbs_register(struct cvbs_dev *dev);
extern int cvbs_reg_check(void);
extern int cvbs_open(char *name);
extern int cvbs_close(void);
extern int cvbs_dev_cfg(void);
/* tvif interface */
extern void tvif_irq_mode(void);
extern int tvif_init(void);
extern int tvif_open();
extern int tvif_cfg(int flags, int mode, int bit);
extern int tvif_close(void);
extern void tvif_get_display(int *xsize, int *ysize);
extern void tvif_set_display(struct cvbs_display *cfg);
extern void tvif_ctrl(int flags);
extern int tvif_reg_check(void);
extern void tvif_wait_frame(void);
extern void tvif_set_matrix(struct cvbs_matrix *param);
extern void tvif_set_cfg(struct cvbs_cfg *cfg);
#endif

#ifndef __INFOTM_IDS_H__
#define __INFOTM_IDS_H__

#include <common.h>
#include <ids/lcd.h>
#include <ids/osd.h>
#include <regcheck.h>
#include <ids/dith.h>
#include <ids/scaler.h>

//#define IDS_DEBUG
#ifdef IDS_DEBUG
#define ids_dbg(fmt...)     printf(fmt)
#else
#define ids_dbg(...)        do {} while (0)
#endif
#define ids_err(fmt...)     printf(fmt)

#define bool    _Bool
#define true    1    
#define false   0  

#define STRING_LEN	0x40

#define IDS_RDONLY	0x0

enum image_type { 
	OSD_TEST_IMAGE_TYPE_FILL_COLOR,
	OSD_TEST_IMAGE_TYPE_HOR_BAR,
	OSD_TEST_IMAGE_TYPE_VER_BAR,
	OSD_TEST_IMAGE_TYPE_GRID,
};

enum bpp_mode {
	PALLETE_BPP,
	RGB_BPP,
	ARGB_BPP,
	RGBA_BPP,
	A4RGB_BPP,
	A8RGB_BPP,
	IRGB_BPP,
	RGBI_BPP,
};

enum osd_mode {
	LCD_MODE,
	CVBS_MODE,
};

enum hdmi_type {
	HDMI_RGB,
	HDMI_YUV444,
	HDMI_YUV422,
};

static inline void ids_writel(uint32_t val, uint32_t addr)
{
	//writel(addr, val);
	writel(val, addr);
}

static inline uint32_t ids_readl(uint32_t addr)
{
	return readl(addr);
}

#define BPPSET(a, r, g, b)		((a << 12) | (r << 8) | (g << 4) | b)
#define BPPGETMODE(mode)		((mode >> 12) & 0xf)
#define BPPGETB(mode)			(mode & 0xf)
#define BPPGETG(mode)			((mode >> 4) & 0xf)
#define BPPGETR(mode)			((mode >> 8) & 0xf)
#define BPPGETBMASK(bits)		((0x1 << bits) - 1)
#define BPPSETB(color, mode)	(color & BPPGETBMASK(BPPGETB(mode)))
#define BPPSETG(color, mode)    ((color & BPPGETBMASK(BPPGETG(mode))) << BPPGETB(mode))
#define BPPSETR(color, mode)	((color & BPPGETBMASK(BPPGETR(mode))) << (BPPGETB(mode) + BPPGETG(mode)))
#define BPP888SETCOLOR(color, mode) (BPPSETB((color & 0xff), mode) | \
									 BPPSETG(((color >> 8) & 0xff), mode) | \
									 BPPSETR(((color >> 16) & 0xff), mode))
#define BPPRGB(mode)			(BPPGETB(mode) + BPPGETG(mode) + BPPGETR(mode))

/* 1 pixel need bitnum bits */
struct bpp_color_params {
	uint32_t format;
	uint32_t bitnum;
	uint32_t pixelmode;
};

#define BPP_COLOR(_format, _bitnum, _pixelmode)	\
{ \
	.format = _format,							\
	.bitnum = _bitnum,							\
	.pixelmode = _pixelmode,					\
}

struct ids_mannual_image {
	int set;		/* if to use defualt set */
	int format;		/* bpp mode */
	int type;		/* pattern image */
	uint32_t color;	/* image color: [31:24]no use, [23:16]red, [15:8]green, [7:0]blue*/
	int alpha;
	int mHBar;		/* horizontal bar pixel width */
	int mVBar;		/* vertical bar pixel width */
	int width;
	int height;
	uintptr_t *mem;
	uint8_t *YUV;
   	int fd;
	char name[64];
};
/* common interfce */
extern int ids_draw_image(struct ids_mannual_image *imagecfg, int flags);
extern int ids_read_image(char *path, struct osd_dma *dma);
extern void osd_dma_init(struct osd_dma *dma, int flags, int dma_num);
void osd_dma_init_wh(struct osd_dma *dma, int flags, int dma_num, int width, int height);
extern void osd_dma_init_no_malloc(struct osd_dma *dma, int flags, int dma_num, uintptr_t bmp_addr);
extern void osd_common_init(int nr, enum osd_mode mode, struct osd_dma *dma);
extern int ids_fill_framebuffer(struct ids_mannual_image *cfg);
/* lcd interface */
extern uint32_t reg_base;
extern uint32_t irq_num;
extern int lcd_init(void);
extern void lcd_enable(int enable);
extern int lcd_open(char *name);
extern int lcd_set_pixel_clk(int rate);
extern int lcd_close(void);
extern int lcd_reg_check(void);
extern void lcd_irq_mode(void);
extern void lcd_exchang_ids(int ids_num);
extern void lcd_in_polarity(void);
extern void lcd_wait_frame(void);
extern void lcd_get_screen_size(int *width, int *height);
extern void lcd_set_rgb_cfgorder(int order);
extern void lcd_set_output_if(enum EXT_DISPLAY_TYPE flags);
extern void lcd_set_panel(int lineval, int hozval);
extern void lcd_set_screen_size(int width, int height);
extern void lcd_set_vsync_polarity(int flags);
/* mipi interface */
#if 0
extern int mipi_init(void);
extern int mipi_open(char *name);
extern int mipi_close(void);
extern int mipi_reg_check(void);
extern int mipi_get_screen_size(int *width, int *height);
extern void mipi_get_err_status(void);
extern void mipi_display_ctrl(int enable);
extern void mipi_switch_mode(int mode);
extern void mipi_ctrl_power(int enable);
extern void mipi_send_ctrl(uint8_t *buf, int length);
extern int mipi_recv_cmd(uint8_t *buf, int length);
extern int mipi_set_pixel_format(dsih_color_coding_t format);
extern int mipi_set_transfer_mode(dsih_video_mode_t mode);
extern void dsi_send_long_packet(uint8_t *cmd_buffer, unsigned int length);
#endif
/* osd interface */
extern void osd_init(struct osd_cfg *cfg);
extern void osd_open(int nr);
extern void osd_close(int nr);
extern void osd_win_init(struct osd_win_cfg *cfg);
extern int osd_reg_check(void);
extern void osd_set_output_format(struct osd_output_format *format);
extern void osd_set_coord(int nr, struct osd_xy *coord);
extern void osd_colormap_ctrl(int nr, int enable, int color);
extern void osd_set_pixel_swap(int nr, struct osd_swap *swap);
extern void osd_set_dma_mode(int nr, struct osd_buf_mode *mode);
extern void osd_set_bppmode(int nr, int mode);
extern void osd_set_pallete(int nr, struct osd_pallete *pallete);
extern void osd_set_alpha(int nr, struct osd_alpha *alpha);
extern void osd_set_bg_color(uint32_t val);
extern void osd_set_colorkey(int nr, struct osd_colorkey *colorkey);
extern void osd_set_scale_xy(int x, int y);
extern void osd_set_end_xy(int nr, int x, int y);
extern void osd_set_vm_width(int nr, int val);
extern void osd_set_global_load(int enable);
extern void osd_set_yuvtorgb(struct osd_yuv *yuv);
extern void osd_set_dma_channel(int nr, int num, struct dma_buffer *dma);
/* osd prescaler */
extern void osd_set_scaler_mode(enum scaler_mode mode);
extern void osd_set_prescaler_param(struct prescaler_para *para);
extern void osd_prescaler_enable(int flags);
extern void osd_set_pre_pallete(struct osd_pallete *pallete);
extern void osd_prescalser_cood(int x, int y);
extern void osd_prescaler_bppmode(int mode);
#if 0
extern void osd_set_scaler_input_size(int height, int width);
extern void osd_set_scaler_output_size(int height, int width);
extern void osd_set_scaler_output_offset(int height, int width);
extern void osd_set_height_scaler(struct osd_scaler *scaler);
extern void osd_set_width_scaler(struct osd_scaler *scaler);
#else
extern void scaler_para_load(int flags);
extern void scaler_init(struct scaler_module *dev);
extern void scaler_set_resolution(int flags, struct scaler_resolution *resolution);
extern void scaler_get_resolution(int flags, struct scaler_resolution *resolution);
extern int scaler_set_reslution_ratio(struct scaler_resolution *input, struct scaler_resolution *output);
extern void scaler_set_zoominout(struct zoom_cfg *cfg);
#endif
/* dith interface */
extern void dith_init(void);
extern void dith_ctrl_dither(int enable);
extern void dith_ctrl_temporal(int enable);
extern void dith_set_size(int width, int height);
extern void dith_set_coefficient(int value, enum dit_dmco coefficient);
extern void dith_reduce_rgb(int rchan, int gchan, int bchan);
/* hdmi interface */
extern void hdmi_init(int flags);
extern int hdmi_open(int flags);
extern void hdmi_close(void);
extern void hdmi_ctrl_switch(int flags);
extern void hdmi_set_output(enum hdmi_type format);
extern int hdmi_reg_check(void);
extern int cec_test(void);
extern int hdmi_set_hdcp(void);
extern int hdmi_wait_edid(void);
#endif

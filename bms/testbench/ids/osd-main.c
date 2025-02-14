/*
 * (C) Copyright 2000
 * Wolfgang Denk, DENX Software Engineering, wd@denx.de.
 *
 * See file CREDITS for list of people who contributed to this
 * project.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

/*
 * Memory Functions
 *
 * Copied from FADS ROM, Dan Malek (dmalek@jlc.net)
 */

#include <common.h>
#include <command.h>
#include <getopt.h>
#include <testbench.h>
#include <exports.h>
#include <malloc.h>
#include <rand48.h>
#include <ids/ids.h>
#include <rtlfs.h>
//#include <dmmu.h>
#include "palette.c"
#include "scaler_random.h"
#include <rtlfs.h>
#include <cache.h>
#include "img_2.h"
#include "img_512x300.h"

static const char *casename[] = {
	" ",
	"osd register",
	"osd bpp mode",
	"osd pre bpp mode",
	"osd colorkey",
	"osd mapcolor",
	"osd alpha",
	"osd position",
	"osd dither",
	"osd swap bpp",
	"osd pre scaler",
	"osd aft scaler",
	"osd auto switch buf",
	"osd yuv420sp mode",
	"osd performance",
	NULL,
};

#ifdef CONFIG_COMPILE_RTL
#ifdef IDS_DEBUG
static const char *zoomname[5] = {
	"variable_average",
	"average_4_4",
	"spline_0_5",
	"spline_1_0",
	"bilinear"
};
#endif

static uint32_t zoom[5][65] = {
	{0x0},
	{0x4,
	 0x0400, 0x0400, 0x0400, 0x0400},
	{0x40,
	0x0ff6, 0x1000, 0x0fab, 0x0fda, 0x0f1d, 0x0f6c, 0x0e56, 0x0ec1,
	0x0d5f, 0x0de0, 0x0c40, 0x0cd4, 0x0b02, 0x0ba4, 0x09af, 0x0a5b,
	0x084f, 0x0900, 0x06ec, 0x079e, 0x058e, 0x063c, 0x043f, 0x04e5,
	0x0308, 0x03a0, 0x01f1, 0x0278, 0x0103, 0x0174, 0x0048, 0x009f,
	0x203c, 0x0000, 0x209e, 0x2071, 0x20e4, 0x20c4, 0x2111, 0x20fe,
	0x212a, 0x2120, 0x212f, 0x212f, 0x2125, 0x212c, 0x210f, 0x211c,
	0x20ef, 0x2100, 0x20c9, 0x20dd, 0x209f, 0x20b4, 0x2074, 0x208a,
	0x204d, 0x2060, 0x202a, 0x203b, 0x2010, 0x201c, 0x2002, 0x2008},
	{0x40,
	0x0ff8, 0x1000, 0x0fbb, 0x0fe1, 0x0f48, 0x0f88, 0x0ea3, 0x0efb,
	0x0dd3, 0x0e40, 0x0cde, 0x0d5d, 0x0bcb, 0x0c58, 0x0a9e, 0x0b37,
	0x095e, 0x0a00, 0x0811, 0x08b9, 0x06be, 0x0768, 0x0569, 0x0613,
	0x0419, 0x04c0, 0x02d4, 0x0375, 0x01a1, 0x0238, 0x0084, 0x010f,
	0x2078, 0x0000, 0x213b, 0x20e1, 0x21c8, 0x2188, 0x2223, 0x21fb,
	0x2253, 0x2240, 0x225e, 0x225d, 0x224b, 0x2258, 0x221e, 0x2237,
	0x21de, 0x2200, 0x2191, 0x21b9, 0x213e, 0x2168, 0x20e9, 0x2113,
	0x2099, 0x20c0, 0x2054, 0x2075, 0x2021, 0x2038, 0x2004, 0x200f},
	{0x0},
};
#endif

static uint32_t mapcolor[] = {
	0x0000ff, 0x00ff00, 0xff0000, 0x0, 0x808080, 0xffffff, 0x808000, 0x800080,
	0x008080,
};

struct osd_scaler_case scaler_case[] = {
	{ 1024, 600, 512, 300},
	{ 64, 8, 320, 164 },
	{ 64, 8, 800, 480 },
	{ 320, 164, 1280, 720 },
	{ 800, 480, 800, 480 },
	{ 800, 480, 1280, 720 },
	{ 800, 480, 1920, 1080 },
	{ 1280, 720, 1280, 720 },
	{ 1280, 720, 1920, 1080 },
	{ 1920, 1080, 1920, 1080},
	{ 224, 24, 64, 8 },
	{ 720, 576, 800, 480 },
 	{ 1280, 720, 800, 480 },
	{ 1920, 1080, 1280, 720 },
};

static int osd_draw_image(struct ids_mannual_image *imagecfg)
{
	imagecfg->set = 1;
	imagecfg->format = OSD_IMAGE_RGB_BPP24_888;
	imagecfg->type = OSD_TEST_IMAGE_TYPE_VER_BAR;
	imagecfg->mHBar = 8;
	lcd_get_screen_size(&imagecfg->width, &imagecfg->height);
	ids_draw_image(imagecfg, LCD_MODE);
	return 0;
}

/* 
 * 1.init lcd output
 * 2.init osd win0 and framebuffer0
 * 3.init osd win1 and framebuffer1
 **/
static void osd_init_lcd(int ids)
{
	if (lcd_init() < 0)
		return;
	
	if (lcd_open("ZDYZ_1024_600") < 0) {
		printf("Open lcd err\n");
		return;
	}
}

static void osd_compose_windows(struct osd_dma *dma, int enable)
{
	struct ids_mannual_image image;
	struct osd_xy coord;
	struct osd_dma buf;
	int i, j;
	
	memset(&image, 0, sizeof(struct ids_mannual_image));
	
	for (j = 0; j < 2; j++) {
		if (dma) {
			for (i = 0; i < dma[j].dma_num; i++) {
				image.mem = dma[j].buf[i].vir_addr;
				#if 1
				if (j == WINDOWS0){
					printf("compose windows ids draw horizental 8 pixel bar image for window[%d]\n", j);
					ids_draw_image(&image, LCD_MODE);
				}
				else{
					printf("compose windows osd draw vertical 8 pixel bar image for window[%d]\n", j);
					osd_draw_image(&image);
				}
				#endif
			}
			printf("osd common init %d\n", j);
			osd_common_init(j, LCD_MODE, &dma[j]);
		} else {
			printf("dma null, here\n");
			osd_dma_init(&buf, LCD_MODE, 1);
			image.mem = buf.buf[0].vir_addr;
			if (j == WINDOWS0) 
				ids_draw_image(&image, LCD_MODE);
			else
				osd_draw_image(&image);
			osd_common_init(j, LCD_MODE, &buf);
		}
	}
	
    osd_set_scaler_mode(SCALER_BEFORE_OSD_MODULE);
	coord.leftx = 0;                                      
	coord.lefty = 0;                                      
	lcd_get_screen_size(&coord.rightx, &coord.righty);
	coord.rightx /= 2;
	osd_set_coord(0, &coord);
	coord.leftx = coord.rightx;
	coord.rightx *= 2;
	osd_set_coord(1, &coord);
	
	if (enable) {
		osd_open(WINDOWS0);
		osd_open(WINDOWS1);
		lcd_enable(1);
	}
}

static void osd_test_colorkey(void)
{
	struct ids_mannual_image imagecfg;
	struct osd_alpha alpha;
	struct osd_colorkey colorkey;
	struct osd_dma dma[2];
	int i, j;

	//osd_init_lcd(1);
	if (lcd_init() < 0)
		return;

	if (lcd_open("ZDYZ_1024_600") < 0) {
		ids_err("Open lcd err\n");
		return ;
	}

	printf("osd dma init window0\n");
	osd_dma_init(&dma[0], LCD_MODE, 1);
	memset(&imagecfg, 0, sizeof(struct ids_mannual_image));             
	imagecfg.mem = dma[0].buf[0].vir_addr;
	printf("osd dma draw\n");
	osd_draw_image(&imagecfg);
	printf("osd common init window0\n");
	osd_common_init(WINDOWS0, LCD_MODE, &dma[0]);
	memset(&imagecfg, 0, sizeof(struct ids_mannual_image));

	printf("osd dma init window1\n");
	osd_dma_init(&dma[1], LCD_MODE, 1);
	imagecfg.mem = dma[1].buf[0].vir_addr;
	printf("osd dma draw\n");
	ids_draw_image(&imagecfg, LCD_MODE); 
	printf("osd common init window1\n");                            
	osd_common_init(WINDOWS1, LCD_MODE, &dma[1]);    
	printf("init done \n");

   	osd_set_scaler_mode(SCALER_BEFORE_OSD_MODULE);   
	osd_open(WINDOWS0);
	osd_open(WINDOWS1);
	lcd_enable(1);     
	
	/* set background 0xffffff */	
	osd_set_bg_color(0xffffff);
	alpha.path = ALPHA_KEY;
	alpha.blendmode = ALPHA_PIXEL_BLENDING;
	alpha.alpha0_r = 4;
	alpha.alpha0_g = 4;
	alpha.alpha0_b = 4;
	alpha.alpha1_r = 0xb;
	alpha.alpha1_g = 0xb;
	alpha.alpha1_b = 0xb;
	osd_set_alpha(WINDOWS1, &alpha);
	for (i = 0; i < 2; i++)
		for (j = 0; j < 2; j++) {
			colorkey.enable = ENABLE;
			colorkey.enableBlend = i;
			colorkey.dircon = j;
			colorkey.compkey = 0x00ff00;
			colorkey.colval = 0x007f00;
			osd_set_colorkey(WINDOWS1, &colorkey);
			printf("wait frame %d\n", j);
			lcd_wait_frame();
#ifndef CONFIG_COMPILE_RTL
			udelay(1000*1000); 
#endif
		}
	lcd_wait_frame();
}

static void osd_test_alpha(int flags, int format)
{
	struct ids_mannual_image imagecfg;
	struct osd_alpha alpha;
	struct osd_dma dma[2];
	int i, j, color = 0;

	osd_init_lcd(1);
	osd_dma_init(&dma[0], LCD_MODE, 1);
	memset(&imagecfg, 0, sizeof(struct ids_mannual_image));
	imagecfg.mem = dma[0].buf[0].vir_addr;
	ids_draw_image(&imagecfg, LCD_MODE);

	osd_common_init(WINDOWS0, LCD_MODE, &dma[0]);
	osd_dma_init(&dma[1], LCD_MODE, 1);                                 
	imagecfg.mem = dma[1].buf[0].vir_addr;                    
	osd_draw_image(&imagecfg);   

	osd_common_init(WINDOWS1, LCD_MODE, &dma[1]);            
   	osd_set_scaler_mode(SCALER_BEFORE_OSD_MODULE);      
	if (flags == ALPHA_PER_PLANE || flags == ALPHA_DEFAULT) {
		osd_open(WINDOWS0);
		osd_open(WINDOWS1);
		lcd_enable(1);     
		lcd_wait_frame();
	}
	ids_dbg("alpha blend in per plane mode\n");
	ids_writel(0x0, 0x24001114);
	/* per plane blend mode*/
#ifndef CONFIG_COMPILE_RTL
#define ALPHA_NUM	16
#else
#define ALPHA_NUM	2
#endif
	if (flags == ALPHA_PER_PLANE || flags == ALPHA_DEFAULT) {
		for (i = 0; i < 2; i++) 
			for (j = 0; j < ALPHA_NUM; j++) {
				alpha.path = i;
				alpha.blendmode = ALPHA_PLANE_BLENDING;
				alpha.alpha0_r = j * (16 / ALPHA_NUM);
				alpha.alpha0_g = j * (16 / ALPHA_NUM);
				alpha.alpha0_b = j * (16 / ALPHA_NUM);
				alpha.alpha1_r = j * (16 / ALPHA_NUM);
				alpha.alpha1_g = j * (16 / ALPHA_NUM);
				alpha.alpha1_b = j * (16 / ALPHA_NUM);
				osd_set_alpha(WINDOWS1, &alpha);
				lcd_wait_frame();
#ifndef CONFIG_COMPILE_RTL
				//udelay(500000); 
#endif 
			}
#ifdef CONFIG_COMPILE_RTL
		lcd_wait_frame();
		return;
#endif
	}

	ids_dbg("alpha blend in per pixel mode\n");
#ifndef CONFIG_COMPILE_RTL
	for (i = OSD_IMAGE_RGB_BPP8_1A232; i <= OSD_IMAGE_RGB_BPP16_555I; i++) {
#else
	{
		i = format;
#endif
		if((i == OSD_IMAGE_RGB_BPP16_565) || (i == OSD_IMAGE_RGB_BPP16_I555) ||
		   (i == OSD_IMAGE_RGB_BPP18_666) || (i == OSD_IMAGE_RGB_BPP24_888) ||
		   (i == OSD_IMAGE_YUV_420SP) || (i == OSD_IMAGE_RGB_BPP16_555I))
#ifndef CONFIG_COMPILE_RTL
			continue;
#else
			return;
#endif
		
		alpha.path = 0;	
		alpha.blendmode = ALPHA_PIXEL_BLENDING;	
		alpha.alpha0_r = 0;
		alpha.alpha0_g = 0;
		alpha.alpha0_b = 0;
		alpha.alpha1_r = 0xf;
		alpha.alpha1_g = 0xf;
		alpha.alpha1_b = 0xf;
		
		if((i == OSD_IMAGE_RGB_BPP8_1A232) || (i == OSD_IMAGE_RGB_BPP16_1A555) ||
		   (i == OSD_IMAGE_RGB_BPP18_1A665) || (i == OSD_IMAGE_RGB_BPP19_1A666) ||
		   (i == OSD_IMAGE_RGB_BPP24_1A887) || (i == OSD_IMAGE_RGB_BPP25_1A888) ||
		   (i == OSD_IMAGE_RGB_BPP16_555A))
			color = 2;
		
		if((i == OSD_IMAGE_RGB_BPP28_4A888) || (i == OSD_IMAGE_RGB_BPP16_4A444)) {
			color = 16;
			alpha.path = 1;
		}

		if (i == OSD_IMAGE_RGB_BPP32_8A888) {
			color = 256;
			alpha.path = 1;
		}

		osd_set_bppmode(WINDOWS1, i);
		osd_set_alpha(WINDOWS1, &alpha);
		imagecfg.set = 1;                                       
		imagecfg.format = i;     
		imagecfg.mHBar = 8;
		imagecfg.type = OSD_TEST_IMAGE_TYPE_VER_BAR;         
		lcd_get_screen_size(&imagecfg.width, &imagecfg.height);
#ifndef CONFIG_COMPILE_RTL
		for (j = 0; j < min(4, color); j++) {
			imagecfg.alpha = j;
			if (color > 4)
				imagecfg.alpha = j * (color / 2);
			sprintf(imagecfg.name, "ids/osd/ver_bar_%d_%d", imagecfg.alpha, imagecfg.format);
			ids_draw_image(&imagecfg, LCD_MODE);
			lcd_wait_frame();
			//udelay(1000000); 
		}
#else
		imagecfg.alpha = color / 2;
		sprintf(imagecfg.name, "ids/osd/ver_bar_%d_%d", imagecfg.alpha, imagecfg.format);
		ids_draw_image(&imagecfg, LCD_MODE);
		osd_open(WINDOWS0);
		osd_open(WINDOWS1);
		lcd_enable(1);     
		lcd_wait_frame();  
#endif
	}
   lcd_wait_frame();
}

static void osd_test_mapcolor(int window)
{
	int j;
	
	//osd_init_lcd(1);
	if (lcd_init() < 0)
		return;
	
	if (lcd_open("ZDYZ_1024_600") < 0) {
		ids_err("Open lcd err\n");
		return ;
	}

	printf("osd compose windows\n");
	osd_compose_windows(NULL, 1);
	printf("osd compose windows done\n");
	lcd_wait_frame();
	for (j = 0; j < 3; j++) {
		printf("osd colormap %d\n", j);
		osd_colormap_ctrl(window, 1, mapcolor[j]);
		lcd_wait_frame();
		#ifndef CONFIG_COMPILE_RTL
		udelay(1000 * 1000);
		#endif
	}
	lcd_wait_frame();

}

static void osd_set_coord_position(int x, int y)
{
	struct osd_xy coord;

	coord.leftx = x;
	coord.lefty = y;
	coord.rightx = coord.leftx + 40;
	coord.righty = coord.lefty + 40;
	ids_dbg("start coord (%d, %d), end coord (%d, %d)\n",
			coord.leftx, coord.lefty, coord.rightx, coord.righty);
	//osd_set_global_load(DISABLE);
	osd_set_coord(1, &coord);
	//osd_set_global_load(ENABLE);
}

static void osd_test_position(void)
{
	struct ids_mannual_image imagecfg;
	struct osd_dma dma;
#ifndef CONFIG_COMPILE_RTL
	int i;
#endif

	osd_init_lcd(1);
	osd_common_init(WINDOWS0, LCD_MODE, NULL);
	memset(&imagecfg, 0, sizeof(struct ids_mannual_image));
	osd_dma_init(&dma, LCD_MODE, 1);
	imagecfg.mem = dma.buf[0].vir_addr;
	ids_draw_image(&imagecfg, LCD_MODE);

	osd_common_init(WINDOWS1, LCD_MODE, &dma);
	/* set win0 display BLUE */
	osd_colormap_ctrl(0, ENABLE, 0xff);	
   	osd_set_scaler_mode(SCALER_BEFORE_OSD_MODULE);	
	/* disable colorkey, reset maybe not 0 */
	ids_writel(0x0, 0x24001114);
	osd_open(WINDOWS0);
	osd_open(WINDOWS1);
	lcd_enable(1);

#ifndef CONFIG_COMPILE_RTL		
	srand(get_timer(0));
	for (i = 0; i < 1000; i++) {
		osd_set_coord_position(rand() % (imagecfg.width - 40),
					rand() % (imagecfg.height - 40));
		lcd_wait_frame();
	}
#else
	lcd_wait_frame();
	osd_set_coord_position(0, 0);
	lcd_wait_frame();
	osd_set_coord_position(imagecfg.width - 40, 0);	
	lcd_wait_frame();
	osd_set_coord_position(0, imagecfg.height - 40);
	lcd_wait_frame();
	osd_set_coord_position(imagecfg.width - 40, imagecfg.height - 40);
	lcd_wait_frame();
	lcd_wait_frame();
#endif	
}

static void osd_test_buffauto(int window)
{
	struct ids_mannual_image imagecfg;
	struct osd_dma dma[2];
	struct osd_buf_mode mode;
	int i, j;

	osd_init_lcd(1);

	osd_dma_init(&dma[WINDOWS0], LCD_MODE, 4);
	osd_dma_init(&dma[WINDOWS1], LCD_MODE, 4);

	/* draw 4 image for dma transfer */
	memset(&imagecfg, 0, sizeof(struct ids_mannual_image));
	imagecfg.set = 1;
	imagecfg.format = OSD_IMAGE_RGB_BPP24_888;
	imagecfg.type = OSD_TEST_IMAGE_TYPE_FILL_COLOR;
	lcd_get_screen_size(&imagecfg.width, &imagecfg.height);
	osd_compose_windows(dma, 0);
#ifndef CONFIG_COMPILE_RTL	
	for (i = 0; i < 2; i++)
#else
	i = window;
#endif
	for (j = 0; j < 4; j++) {
		imagecfg.mem = dma[i].buf[j].vir_addr;
		imagecfg.color = mapcolor[j + 1];
		ids_draw_image(&imagecfg, LCD_MODE);            
	}
	ids_dbg("draw image ok\n");
	osd_open(WINDOWS0);
	osd_open(WINDOWS1);
	lcd_enable(1);
	lcd_wait_frame();

#ifndef CONFIG_COMPILE_RTL
	for (i = 0; i < 2; i++)
#else
	i = window;
#endif
	for (j = 0; j < 4; j++) {
		ids_dbg("mannual switch %d\n", j);
		/* mannual switch */
		mode.bufsel = j;
		mode.bufauto = BUF_FIXED;
		osd_set_dma_mode(i, &mode);	
		lcd_wait_frame();
#ifndef CONFIG_COMPILE_RTL
		udelay(1000 * 1000);
#endif
	}
	lcd_wait_frame();
}

static void osd_test_performance(void)
{
	struct ids_mannual_image imagecfg;
	struct osd_dma dma[2];
	struct osd_buf_mode mode;
	int i, j;
	
	/* init ids0 */
	osd_init_lcd(0);
	osd_dma_init(&dma[WINDOWS0], LCD_MODE, 4);
	osd_dma_init(&dma[WINDOWS1], LCD_MODE, 4);
	osd_compose_windows(dma, 1);
	/* init ids1 */	
	osd_init_lcd(1);
	osd_compose_windows(dma, 1);

	imagecfg.set = 1;
	imagecfg.format = OSD_IMAGE_RGB_BPP24_888;
	imagecfg.type = OSD_TEST_IMAGE_TYPE_FILL_COLOR;
	lcd_get_screen_size(&imagecfg.width, &imagecfg.height);
	
	for (i = 0; i < 2; i++)
		for (j = 0; j < 4; j++) {
			imagecfg.mem = dma[i].buf[j].vir_addr;
			imagecfg.color = mapcolor[j + 1];
			ids_draw_image(&imagecfg, LCD_MODE);            
		}

	for (i = 0; i < 2; i++)
		for (j = 0; j < 4; j++) {
			ids_dbg("mannual switch %d\n", j);
			/* mannual switch */
			mode.bufsel = j;
			mode.bufauto = BUF_FIXED;
			osd_set_dma_mode(i, &mode);	
			lcd_wait_frame();         
			udelay(500000);
		}
}

static void osd_test_bppmode(int window, int pallete_mode, int format)
{
	struct ids_mannual_image imagecfg;
	struct osd_dma dma[2];
	int i;
	itcs_dcache_flush();
	memset(&imagecfg, 0, sizeof(struct ids_mannual_image));

	if (lcd_init() < 0)
		return;
	
	if (lcd_open("ZDYZ_1024_600") < 0) {
		printf("Open lcd err\n");
		return;
	}

	lcd_get_screen_size(&imagecfg.width, &imagecfg.height);

	osd_dma_init(&dma[WINDOWS0], LCD_MODE, 1);
	osd_dma_init(&dma[WINDOWS1], LCD_MODE, 1);
   	osd_set_scaler_mode(SCALER_BEFORE_OSD_MODULE);
#ifndef CONFIG_COMPILE_RTL
	osd_compose_windows(dma, 1);
#else
	osd_compose_windows(dma, 0);
#endif

	if (format > OSD_IMAGE_PAL_BPP8) {
		imagecfg.set = 1;
		imagecfg.mVBar = 5;
		imagecfg.type = OSD_TEST_IMAGE_TYPE_HOR_BAR;
		imagecfg.format = format;
		imagecfg.mem = dma[window].buf[0].vir_addr;
		lcd_get_screen_size(&imagecfg.width, &imagecfg.height);
		ids_draw_image(&imagecfg, LCD_MODE);
		osd_set_bppmode(window, format);
		osd_open(WINDOWS0);
		osd_open(WINDOWS1);
		lcd_enable(1);

		for (i = 0; i < 3; i++){
			printf("wait frame %d\n", i);
			lcd_wait_frame();
		}
		return;
	}else{
		printf("bpp format %d not support now\n", format);
	}


}

static void osd_test_pre_bppmode(int window, int pallete_mode, int format)
{
	struct ids_mannual_image imagecfg;
	struct osd_dma dma[2];
	struct prescaler_para para;
	struct scaler_module dev;
	int i;

	osd_init_lcd(1);

	osd_dma_init(&dma[WINDOWS0], LCD_MODE, 1);
	osd_dma_init(&dma[WINDOWS1], LCD_MODE, 1);
	osd_compose_windows(dma, 0);
	osd_set_scaler_mode(SCALER_BEFORE_OSD_MODULE);
	
	memset(&imagecfg, 0, sizeof(struct ids_mannual_image));
	imagecfg.set = 1;
	imagecfg.type = OSD_TEST_IMAGE_TYPE_FILL_COLOR;
	lcd_get_screen_size(&imagecfg.width, &imagecfg.height);
	
	para.window = window;       
	para.format = format;   //OSD_IMAGE_RGB_BPP24_888;
	para.x = 1024; 
	para.y = 600;                                                  
	para.dma = &dma[window];                                               
	osd_set_prescaler_param(&para);
	osd_prescalser_cood(para.x / 2, para.y); 
	dev.bypass = 1;
	dev.out_resolute.horizontal = 1024;
	dev.out_resolute.vertical = 600;
	dev.in_resolute.horizontal = 1024;
	dev.in_resolute.vertical = 600;
	scaler_init(&dev);

	if (format > OSD_IMAGE_PAL_BPP8) {
		imagecfg.set = 1;
		imagecfg.type = OSD_TEST_IMAGE_TYPE_HOR_BAR;
		imagecfg.mVBar = 100;	
		imagecfg.format = format;
		imagecfg.mem = dma[window].buf[0].vir_addr;
		lcd_get_screen_size(&imagecfg.width, &imagecfg.height);
		ids_draw_image(&imagecfg, LCD_MODE);
		osd_prescaler_enable(1);
		osd_open(WINDOWS0);
		osd_open(WINDOWS1);
		lcd_enable(1);
		for (i = 0; i < 2; i++)
			lcd_wait_frame();
		return;
	}
}

static int osd_test_aft_scaler(void)
{
	struct osd_dma dma;
	struct scaler_module dev;

	if (lcd_init() < 0)
		return -1;

	if (lcd_open("ZDYZ_1024_600") < 0) {
		ids_err("Open lcd err\n");
		return -1;
	}

	osd_dma_init(&dma, LCD_MODE, 1);

#ifdef CONFIG_COMPILE_RTL
	int fd;
	fd = open("ids/osd/1920_1080.bmp", O_RDONLY);
	if (fd < 0) {
		ids_err("open file err\n");
		return -1;
	}
	if (read(fd, dma.buf[0].vir_addr, 1920 * 1080 * 4) < 0) {
		ids_err("read file err\n");
		return -1;
	} 
	close(fd);
#else
	memcpy(dma.buf[0].vir_addr, img_512x300, dma.buf[0].size);
	itcs_dcache_flush();
#endif

	osd_common_init(WINDOWS0, LCD_MODE, &dma);
	osd_set_scaler_mode(SCALER_AFTER_OSD_MODULE);
	osd_set_scale_xy(512, 300);
	osd_set_end_xy(WINDOWS0, 512, 300);
	osd_set_vm_width(WINDOWS0, 512);	
	dev.bypass = 0;
	dev.out_resolute.horizontal = 1024;
	dev.out_resolute.vertical = 600;
	dev.in_resolute.horizontal = 512;
	dev.in_resolute.vertical = 300;
	scaler_init(&dev);
	lcd_set_panel(dev.out_resolute.vertical, dev.out_resolute.horizontal);
	osd_open(WINDOWS0);
	lcd_enable(1);
	lcd_wait_frame();
	return 0;
}

static void osd_test_pre_scaler(int window)
{
	struct osd_dma dma;
	struct scaler_module dev;
	struct prescaler_para para;

	if (lcd_init() < 0)
		return;
	
	if (lcd_open("ZDYZ_1024_600") < 0) {
		ids_err("Open lcd err\n");
		return ;
	}

#ifdef CONFIG_COMPILE_RTL
	int fd;
	uintptr_t bmp_data_addr;
	fd = open("ids/1024_600.argb",O_RDONLY);
	if (fd < 0) {
		ids_err("open file err: %d\n", fd);
		return ;
	}

	bmp_data_addr = faddr(fd);
	close(fd);

	printf("image addr = 0x%llx\n", bmp_data_addr);
	osd_dma_init_no_malloc(&dma, LCD_MODE, 1, bmp_data_addr);
#else
	osd_dma_init(&dma, LCD_MODE, 1);
	memcpy(dma.buf[0].vir_addr, img_512x300, dma.buf[0].size);
	itcs_dcache_flush();
#endif
	osd_common_init(window, LCD_MODE, &dma);

	printf("set scaler mode\n");	
	osd_set_scaler_mode(SCALER_BEFORE_OSD_MODULE);
	para.window = window;
	para.format = OSD_IMAGE_RGB_BPP24_888;
	para.x = 512;
	para.y = 300;
	para.dma = &dma;
	printf("set scaler param\n");
	osd_set_prescaler_param(&para);	
	dev.bypass = 0;
	dev.out_resolute.horizontal = 1024;
	dev.out_resolute.vertical = 600;
	dev.in_resolute.horizontal = 512;
	dev.in_resolute.vertical = 300;
	printf("scaler init\n");
	printf("scaler: in[%dx%d], out[%dx%d]\n", dev.in_resolute.horizontal, dev.in_resolute.vertical,
	dev.out_resolute.horizontal, dev.out_resolute.vertical);
	scaler_init(&dev);
	printf("scaler enable\n");
	osd_prescaler_enable(1);
	osd_open(window);
	lcd_enable(1);
	printf("wait frame\n");
	lcd_wait_frame();
	printf("wait frame done\n");
}

//static int32_t YCbCr2RGB[] = {16, 0, 596, 0, 817, 596, 3895, 3680, 596, 1033, 0};
static int32_t YCbCr2RGB[] = {16, 0, 298, 0, 409, 298, 1984, 1840, 298, 516, 0};

static void osd_test_yuv(int window)
{
	struct osd_yuv yuv;
	struct osd_dma dma;
	int fd;
	int i;

	if (lcd_init() < 0)
		return;
	
	if (lcd_open("KR070PB2S_800_480") < 0)
		return;
	osd_dma_init(&dma, LCD_MODE, 2);
	
	fd = open("ids/yuv420", O_RDONLY);	
	if (fd < 0) {
		ids_err("open file err: %d\n", fd);
		return;
	}
	if (read(fd, dma.buf[0].vir_addr, 800 * 480) < 0) {
		ids_err("osd read file err\n");
		return;
	}
	if (read(fd, dma.buf[1].vir_addr, 800 * 480 / 2) < 0) {
		ids_err("osd read file err\n");
		return;
	}
	close(fd);

	osd_common_init(window, LCD_MODE, &dma);
	/* scaler after osd */
	osd_set_bppmode(window, OSD_IMAGE_YUV_420SP);
	ids_writel((uintptr_t)dma.buf[1].vir_addr, 0x24001300);
	ids_dbg("scaler after osd\n");	
	osd_set_scaler_mode(SCALER_BEFORE_OSD_MODULE);
	yuv.enable = 1;
	memcpy(&(yuv.out_oft_b), YCbCr2RGB, 11 * 4);
	osd_set_yuvtorgb(&yuv);
	osd_open(window);
	lcd_enable(1);
	for (i = 0; i < 2; i++)
	    lcd_wait_frame();
}

static void osd_test_pre_yuv(int window)
{
	struct prescaler_para para;
	struct osd_yuv yuv;
	struct osd_dma dma;
	struct scaler_module dev;
	int fd;
	int i;

	if (lcd_init() < 0)
		return;
	
	if (lcd_open("KR070PB2S_800_480") < 0)
		return;
	osd_dma_init(&dma, LCD_MODE, 2);
	fd = open("ids/yuv420", O_RDONLY);	
	if (fd < 0) {
		ids_err("open file err: %d\n", fd);
		return;
	}
	if (read(fd, dma.buf[0].vir_addr, 800 * 480) < 0) {
		ids_err("osd read file err\n");
		return;
	}
	if (read(fd, dma.buf[1].vir_addr, 800 * 480 / 2) < 0) {
		ids_err("osd read file err\n");
		return;
	}
	close(fd);
	osd_common_init(window, LCD_MODE, &dma);
	osd_set_scaler_mode(SCALER_BEFORE_OSD_MODULE);
	/* scaler after osd */
	para.window = window;
	para.format = OSD_IMAGE_YUV_420SP;   //OSD_IMAGE_RGB_BPP24_888;
	para.x = 800;
	para.y = 480;
	para.dma = &dma;
	osd_set_prescaler_param(&para);
	ids_err("scaler after osd\n");	
	yuv.enable = 1;
	memcpy(&(yuv.out_oft_b), YCbCr2RGB, 11 * 4);
	osd_set_yuvtorgb(&yuv);
	dev.bypass = 1;
	dev.out_resolute.horizontal = 800;
	dev.out_resolute.vertical = 480;
	dev.in_resolute.horizontal = 800;
	dev.in_resolute.vertical = 480;
	scaler_init(&dev);
	osd_prescaler_enable(1);
	printf("osd_prescaler_enable\n");
	osd_open(window);
	lcd_enable(1);
	for (i = 0; i < 2; i++)
	    lcd_wait_frame();
}

static int swap_mode = 0;

static int osd_case_test_dispatch(int num, int window, int format, int pallete, int pre)
{
	switch (num) {
		case OSD_TEST_CASE_CHECKREGS:
			osd_init_lcd(1);
			if (osd_reg_check() < 0)
				return -1;
			break;
		case OSD_TEST_CASE_BPPMODE:
			osd_test_bppmode(window, pallete, format);
			break;
		case OSD_TEST_CASE_PREBPPMODE:
			osd_test_pre_bppmode(window, pallete, format);
			break;
		case OSD_TEST_CASE_POSITION:
			osd_test_position();
			break;
		case OSD_TEST_CASE_MAPCOLOR:
			osd_test_mapcolor(window);
			break;
		case OSD_TEST_CASE_ALPHA:
			osd_test_alpha(ALPHA_PER_PLANE, format);
			break;
		case OSD_TEST_CASE_COLORKEY:
			osd_test_colorkey();
			break;
		case OSD_TEST_CASE_BUFFAUTO:
			osd_test_buffauto(window);
			break;
		case OSD_TEST_CASE_PERFORMANCE:
			osd_test_performance();
			break;
		case OSD_TEST_CASE_PRE_SCALER:
			osd_test_pre_scaler(window);
			break;
		case OSD_TEST_CASE_AFT_SCALER:
			osd_test_aft_scaler();
			break;
		case OSD_TEST_CASE_YUV:
			if (format)
				osd_test_yuv(window);
			else
				osd_test_pre_yuv(window);
			break;
		default:
			printf("Not support this case: %d\n", num);
			return -1;
	}

	printf("%s test pass\n", casename[num]);
	return 0;
}

static void osd_show_usage(void)
{
	int i = 0;
	
	printf("Usage: osd [OPTION]...\n"
		   "-h, --help\t\t\tcommand help\n"
		   "-c, --case\t\t\tcase num\n");
	printf("------------------------------------------------\n");
	printf("Supported case:\n");
	printf("\tcase num\t\tcase name\n");
	while (casename[i] != NULL) {
		printf("\t%8d\t\t%s\n", i, casename[i]);
		i++;
	}
}

int osd_main(int argc, char *argv[])
{
	int opt, ret = 0;
	int case_num = -1;
	int window = -1;
	int format = -1;
	int pallete = -1;
	int pre = -1;
	
	for (optind = 1; (opt = getopt(argc, argv, "c:w:f:p:r:s:h")) != -1;) {
		switch (opt) {
			case 'c':
				case_num = simple_strtoul(optarg, NULL, 10);
				break;
			case 'w':
				window = simple_strtoul(optarg, NULL, 10);
				break;
			case 'f':
				format = simple_strtoul(optarg, NULL, 10);
				break;
			case 'p':
				pallete = simple_strtoul(optarg, NULL, 10);
				break;
			case 'r':
				pre = simple_strtoul(optarg, NULL, 10);
				break;
			case 's':
				swap_mode = simple_strtoul(optarg, NULL, 10);
				break;
			case 'h':
			default:
				osd_show_usage();
				ret = -1;
				goto err;
		}
	}
	if (optind == 1) {
		osd_show_usage();
		ret = -1;
		goto err;
	}

	osd_case_test_dispatch(case_num, window, format, pallete, pre);
err: 
	return ret;
}

int osd_rtl(int id)
{
	printf("invoking id: %d\n", id);
	return 0;
}

void osdtest_init(void)
{
	register_testbench("osd", osd_main, osd_rtl);
}

testbench_init(osdtest_init);

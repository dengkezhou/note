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
#include <malloc.h>
#include <ids/ids.h>
#include <ids/cvbs.h>
#include <rtlfs.h>
#include <cache.h>

static const char *casename[] = {
	"cvbs register",
	"cvbs display a picture",
	"cvbs irq mode",
	NULL,
};

static void cvbstest_show_usage(void)
{
	int i = 0;

	printf("Usage: cvbs [OPTION]...\n"
		"-h, --help\t\t\thelp\n"
		"-c, --case\t\t\ttest num\n"
		"-m, --mode\t\t\tITU656 or ITU601\n"
		"-b, --bit\t\t\tBit mode\n");
	printf("------------------------------------------------\n");
	printf("Supported case:\n");
	printf("\tcase num\t\tcase name\n");
	while (casename[i] != NULL) {
		printf("\t%8d\t\t%s\n", i, casename[i]);
		i++;
	}
}

static int cvbs_normal_display(int mode, enum cvbs_width bit)
{
	struct osd_dma dma;
	struct cvbs_display cfg;
	struct cvbs_cfg cvbs;
	struct osd_output_format format;
	int i = 0;
	
	memset(&cvbs, 0, sizeof(struct cvbs_cfg));
	if (lcd_init() || tvif_init())
		return -1;

	/* unmask all interrupt */
	ids_writel(0x0, reg_base + IDSINTMSK); 
	
	/* set relution */
	cfg.xsize = 1280;
	cfg.ysize = 720; 

	tvif_set_display(&cfg);

	#if 0
	printf("read ids/1280_720.argb\n");
	int fd;
	uintptr_t bmp_data_addr;
	fd = open("ids/1280_720.argb",O_RDONLY);
	if (fd < 0) {
		ids_err("open file err: %d\n", fd);
		return -1;
	}
	bmp_data_addr = faddr(fd) ;
	printf("rtlfs image addr = 0x%llx\n", bmp_data_addr);
	printf("ids osd_dma_init\n");
	osd_dma_init_no_malloc(&dma, CVBS_MODE, 1, bmp_data_addr);
	itcs_dcache_flush_range(bmp_data_addr, 1280*720*4); 
	printf("ids osd_dma_init done\n");
	#else
	/* mannual draw image */
	struct ids_mannual_image imagecfg;
	printf("ids osd_dma_init\n");
	osd_dma_init(&dma, CVBS_MODE, 1);
	printf("ids osd_dma_init done\n");
	memset(&imagecfg, 0, sizeof(struct ids_mannual_image));
	imagecfg.set = 1;
	imagecfg.format = OSD_IMAGE_RGB_BPP24_888;
	imagecfg.type = OSD_TEST_IMAGE_TYPE_HOR_BAR;
	imagecfg.color = 0xff0000;
	imagecfg.mem = dma.buf[0].vir_addr;
	imagecfg.width = 1280;
	imagecfg.height = 720;
	imagecfg.mHBar = 80;
	imagecfg.mVBar = 80;
	itcs_dcache_invalid_range((phys_addr_t)imagecfg.mem, dma.buf[0].size);
	ids_draw_image(&imagecfg, LCD_MODE);
	itcs_dcache_flush_range(imagecfg.mem, 1280*720*4);          
	#endif

	/* init osd module */
	printf("ids osd_common_init\n");
	
	osd_common_init(WINDOWS0, CVBS_MODE, &dma);
	printf("ids osd_set_scaler_mode\n");
	osd_set_scaler_mode(SCALER_BEFORE_OSD_MODULE);
	printf("ids tvif_cfg\n");
	/* set cvbs */
	if (tvif_cfg(f_PAL, mode, bit)) {
		ids_err("Tvif cfg err\n");
		return -1;
	};
	
	format.iftype = IF_ITU_R;
	format.interlace = PROGRESSIVE;
	printf("osd_set_output_format ...\n");
	osd_set_output_format(&format);
	
	printf("osd_open ...\n");
	/* enable osd*/
	osd_open(WINDOWS0);
	printf("tvif_ctrl ...\n");
	/* tvif ctrl */
	
	tvif_ctrl(ENABLE);
	for(i = 0; i <3; i++){
		printf("tvif_wait_frame ...\n");
		tvif_wait_frame();
		printf("tvif_wait_frame ok\n");
	}
	return 0;
}

static int cvbs_irq_display(void)
{
	struct osd_dma dma;
	struct cvbs_display cfg;
	struct osd_output_format format;
	int fd;

	if (lcd_init() || tvif_init())
		return -1;
	
	tvif_irq_mode();	
	/* unmask all interrupt */
	ids_writel(0x0, reg_base + IDSINTMSK); 
	
	/* set relution */
	cfg.xsize = 1280;
	cfg.ysize = 720; 

	tvif_set_display(&cfg);

	#if 1
	printf("read ids/1280_720.bmp\n");
	uintptr_t bmp_data_addr;
	fd = open("ids/1280_720.bmp",O_RDONLY);
	if (fd < 0) {
		ids_err("open file err: %d\n", fd);
		return -1;
	}
	bmp_data_addr = faddr(fd) + 0x36;//skip 0x36 bytes of bmp header
	#else
	writel(0x1000000,  0xc9201090);//osd自动填充色彩，0x1000000低三字节表示RGB的白色
	#endif
	
	/* mannual draw image */
	printf("ids osd_dma_init\n");
	osd_dma_init_no_malloc(&dma, CVBS_MODE, 1, bmp_data_addr);
	printf("ids osd_dma_init done\n");
	
	/* init osd module */
	printf("ids osd_common_init\n");
	osd_common_init(WINDOWS0, CVBS_MODE, &dma);
	printf("ids osd_set_scaler_mode\n");
	osd_set_scaler_mode(SCALER_BEFORE_OSD_MODULE);
	printf("ids set cvbs\n");
	/* set cvbs */
	if (tvif_cfg(f_PAL, 0, 0)) {
		ids_err("Tvif cfg err\n");
		return -1;
	}
	/* set ouput format */
	format.iftype = IF_ITU_R;
	format.interlace = PROGRESSIVE;
	printf("ids set cvbs\n");
	osd_set_output_format(&format);
	/* enable osd*/
	osd_open(WINDOWS0);
	/* tvif ctrl */
	tvif_ctrl(ENABLE);
	
	while (irq_num < 2)
		udelay(10);	
	return 0;
}

static int cvbs_case_test_dispatch(int num, int mode, int bit)
{
	int ret;

	switch (num) {
		case CVBS_TEST_CASE_CHECKREGS:
			lcd_init();
			ret = tvif_reg_check();
			break;
		case CVBS_TEST_CASE_DISPLAY:
			ret = cvbs_normal_display(mode, bit);
			break;
		case CVBS_TEST_CASE_IRQ:
			ret = cvbs_irq_display();
			break;
		default:
			printf("Not support this case: %d\n", num);
			return -1;
	}
	
	printf("%s test %s\n", casename[num], !ret ? "pass":"failed");
	return 0;
}

int cvbstest_main(int argc, char *argv[])
{
	int opt, ret = 0;
	int case_num = -1;
	int mode = 0;
	int bit = -1;
	
	for (optind = 1; (opt = getopt(argc, argv, "c:m:b:h")) != -1;) {
		switch (opt) {
			case 'c':
				case_num = simple_strtoul(optarg, NULL, 10);
				break;
			case 'm':
				mode = simple_strtoul(optarg, NULL, 10);	
				break;
			case 'b':
				bit = simple_strtoul(optarg, NULL, 10);
				break;
			case 'h':
			default:
				cvbstest_show_usage();
				ret = -1;
				goto err;

		}
	}

	if (optind == 1) {   
		cvbstest_show_usage();
		ret = -1;        
		goto err;        
	}

	cvbs_case_test_dispatch(case_num, mode, bit);
err: 
	optind = 1;
	return ret;
}

int cvbstest_rtl(int id)
{
	printf("invoking id: %d\n", id);
	return 0;
}

void cvbstest_init(void)
{
	register_testbench("cvbs", cvbstest_main, cvbstest_rtl);
}

testbench_init(cvbstest_init);

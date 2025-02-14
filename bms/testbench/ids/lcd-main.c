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
#include <cache.h>
#include <rtlfs.h>
#include "img_1.h"

static const char *result[] = {
	"PASS", "FAILED"
};

enum lcd_test_case {
	LCD_TEST_REGISTER,
	LCD_TEST_DISPLAY,
	LCD_TEST_RGBORDER,
	LCD_TEST_POLARITY,
	LCD_TEST_SWITCH,
	LCD_TEST_IRQ,	
};

static const char *casename[] = {
	"lcd test register",
	"lcd display",
	"lcd rgb order",
	"lcd polarity",
	"lcd switch",
	"lcd irq",
	NULL,	
};

static void lcdtest_show_usage(void)
{
	int i = 0;

	printf("Usage: lcd [OPTION]...\n"
		"\n"
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

static int rgb_value[6] = {
	0x6, 0x9, 0x12, 0x18, 0x21, 0x24
};
extern int lcd_frame_irq(void);
int ids_rgb888_perf_test_init(void * param){
	struct osd_dma dma;
	int fd;
	uintptr_t bmp_data_addr;

	fd = open("ids/1920_1080.argb",O_RDONLY);
	if (fd < 0) {
		ids_err("open file err: %d\n", fd);
		return -1
		;
	}

	bmp_data_addr = faddr(fd);
	close(fd);

	if (lcd_init() < 0) {
		ids_err("Init ids0 err\n");
		return -1;
	}

	if (lcd_open("RTL") < 0) {
		ids_err("Open lcd err\n");
		return -1;
	}

	osd_dma_init_no_malloc(&dma, LCD_MODE, 1, bmp_data_addr);
	/* init osd module */
	osd_common_init(WINDOWS0, LCD_MODE, &dma);

	osd_set_scaler_mode(SCALER_BEFORE_OSD_MODULE);
	/* enable osd*/
	osd_open(WINDOWS0);
	lcd_enable(1);
	return 0;
}

int ids_rgb888_perf_test_start(int count){
	return 0;
}

int ids_rgb888_perf_test_get_status(void){
	int ret = lcd_frame_irq();
	if(ret == 0){
		return 1;//success
	}else{
		return 0;
	}
}

static int lcd_test_register(void)
{
	if (lcd_init() < 0)
		return -1;

	if (lcd_reg_check() < 0)
		return -1;
	return 0;
}

static int lcd_test_display(char *name){
	struct osd_dma dma;
	int i;

	if (lcd_init() < 0) {
		ids_err("Init ids0 err\n");
		return -1;
	}

	if (lcd_open(name) < 0) {
		ids_err("Open lcd err\n");
		return -1;
	}

#ifdef CONFIG_COMPILE_RTL
	int fd;
	uintptr_t bmp_data_addr;
	itcs_dcache_flush();

	fd = open("ids/1024_600.argb",O_RDONLY);
	if (fd < 0) {
		ids_err("open file err: %d\n", fd);
		return -1
		;
	}

	bmp_data_addr = faddr(fd);
	printf("image addr = 0x%llx\n", bmp_data_addr);
	osd_dma_init_no_malloc(&dma, LCD_MODE, 1, bmp_data_addr);
#else
	osd_dma_init(&dma, LCD_MODE, 1);
	memcpy(dma.buf[0].vir_addr, image_data_1, dma.buf[0].size);
	itcs_dcache_flush();
#endif
	/* init osd module */
	osd_common_init(WINDOWS0, LCD_MODE, &dma);

	osd_set_scaler_mode(SCALER_BEFORE_OSD_MODULE);
	/* enable osd*/
	osd_open(WINDOWS0);
	/* enable lcd */	
	lcd_enable(1);
	for (i = 0; i < 2; i++)
		lcd_wait_frame();

	return 0;
}

static int lcd_test_irq(char *name)
{
	struct osd_dma dma;
	int fd;

	if (lcd_init() < 0) {
		ids_err("Init ids0 err\n");
		return -1;
	}

	if (lcd_open(name) < 0) {
		ids_err("Open lcd err\n");
		return -1;
	}
	
	lcd_irq_mode();
	osd_dma_init(&dma, LCD_MODE, 1);

	fd = open("ids/1024_600.argb",O_RDONLY);
	if (fd < 0) {
		ids_err("open file err: %d\n", fd);
		return -1;
	}
	if (read(fd, dma.buf[0].vir_addr, dma.buf[0].size) !=
			dma.buf[0].size) {
		ids_err("Lcd read file err\n");
		return -1;
	}
	close(fd);
	/* init osd module */
	osd_common_init(WINDOWS0, LCD_MODE, &dma);

	osd_set_scaler_mode(SCALER_BEFORE_OSD_MODULE);
	/* enable osd*/
	osd_open(WINDOWS0);
	/* enable lcd */	
	lcd_enable(1);
	
	while (irq_num < 2)
		udelay(10);
	return 0;
}

static int lcd_test_rgborder(char *name)
{
	int i;

	if (lcd_test_display(name) < 0)
		return 1;
	
	for (i = 0; i < 6; i++) {
		lcd_set_rgb_cfgorder(rgb_value[i]);
		lcd_wait_frame();
		#ifndef CONFIG_COMPILE_RTL
		udelay(1000 * 2000);
		#endif
	}
	lcd_wait_frame();

	return 0;
}

static int lcd_test_polarity(char *name)
{
	int i;

	if (lcd_test_display(name) < 0)
		return 1;

	lcd_in_polarity();
	for (i = 0; i < 2; i++)
		lcd_wait_frame();
	return 0;
}

static int lcd_test_switch(char *name)
{
	int i;

	if (lcd_test_display(name) < 0)
		return 1;
#ifdef CONFIG_COMPILE_RTL
   lcd_enable(0);
   return 0;
#endif
   for (i = 0; i < 2; i++) {
		lcd_enable(i);
      udelay(2000000);
	}
	return 0;
}

static int lcd_case_test_dispatch(char *name, int case_num)
{
	int ret;

	switch (case_num) {
		case LCD_TEST_REGISTER:
			ret = lcd_test_register();
			break;
		case LCD_TEST_DISPLAY:
			ret = lcd_test_display(name);
			break;
		case LCD_TEST_RGBORDER:
			ret = lcd_test_rgborder(name);
			break;
		case LCD_TEST_POLARITY:
			ret = lcd_test_polarity(name);
			break;
		case LCD_TEST_SWITCH:
			ret = lcd_test_switch(name);
			break;
		case LCD_TEST_IRQ:
			ret = lcd_test_irq(name);
			break;
		default:
			lcdtest_show_usage();
			return -1;
	}

	printf("%s test %s\n", casename[case_num], result[ret]);
	return ret;
}

int lcdtest_main(int argc, char *argv[])
{
	int option_index = 0, c, ret = 0;
	static const char short_options[] = "n:c:h";
	static const struct option long_options[] = {
		{"name", 1, 0, 'n'},
		{"case", 1, 0, 'c'},
		{"help", 0, 0, 'h'},
		{0, 0, 0, 0},
	};
	char name[20] = "ZDYZ_1024_600";
	int case_num = -1;

	while ((c = getopt_long(argc, argv, short_options, long_options, &option_index)) != -1) {
		switch (c) {
			case 'n':
				memcpy(name, optarg, strlen(optarg));
				break;
			case 'c':
				case_num = simple_strtoul(optarg, NULL, 10);
				break;
			case 'h':
			default:
				lcdtest_show_usage();
				ret = -1;
				goto err;
		}
	}

	if (optind == 1) {   
		lcdtest_show_usage();
		ret = -1;        
		goto err;        
	}

	ret = lcd_case_test_dispatch(name, case_num);
err: 
	optind = 1;
	return ret;
}

int lcdtest_rtl(int id)
{
	printf("invoking id: %d\n", id);
	return 0;
}

void lcdtest_init(void)
{
	register_testbench("lcd", lcdtest_main, lcdtest_rtl);
}

testbench_init(lcdtest_init);


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
#include <ids/ids_api.h>

#define RGB_HOZVAL		1024
#define RGB_LINEVAL		600
#define YUV_HOZVAL	800
#define YUV_LINEVAL	480
#define VIR_HOZVAL	640
#define VIR_LINEVAL	480



static const char *result[] = {
	"PASS", "FAILED"
};

enum idsapi_test_case {
	IDS_API_TEST_RGB,
	IDS_API_TEST_YUV,
};

static const char *casename[] = {
	"ids test rgb",
	"ids test yuv",
	NULL,	
};

static void idsapitest_show_usage(void)
{
	int i = 0;

	printf("Usage: idsapi [OPTION]...\n"
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

int idsapi_test_rgb(void)
{
	uint8_t *yaddr;
	int fd, size;
	int i;

	if (ids_init() < 0)
		return -1;

	size = RGB_HOZVAL * RGB_LINEVAL * 4;
	/* read lcd picture */	
	yaddr = malloc(size);
	if (!yaddr)
		return -1;

	fd = open("ids/1024_600.bmp",O_RDONLY);
	if (fd < 0) {
		ids_err("open file err: %d\n", fd);
		return -1;
	}
	if (read(fd, yaddr, size) != size) {
		ids_err("Lcd read file err\n");
		return -1;
	}
	close(fd);
	/* configure ids reg */
	ids_set_format(IDS_RGB_BPP24_888);
	ids_set_vm_width(RGB_HOZVAL);
	ids_set_resolution(VIR_HOZVAL, VIR_LINEVAL);
	ids_set_dma_addr(yaddr, NULL);
	ids_enable(1);
	for (i = 0; i < 2; i++)
		lcd_wait_frame();
	return 0;
}

int idsapi_test_yuv(void)
{
	uint8_t *yaddr;
	int fd, size;
	int i;

	if (ids_init() < 0)
		return -1;

	size = YUV_HOZVAL * YUV_LINEVAL * 3 / 2;
	/* read lcd picture */	
	yaddr = malloc(size);
	if (!yaddr)
		return -1;

	fd = open("ids/yuv420",O_RDONLY);
	if (fd < 0) {
		ids_err("open file err: %d\n", fd);
		return -1;
	}
	if (read(fd, yaddr, size) != size) {
		ids_err("Lcd read file err\n");
		return -1;
	}
	close(fd);
	/* configure ids reg */
	ids_set_format(IDS_YUV_420SP);
	ids_set_vm_width(YUV_HOZVAL);
	ids_set_resolution(YUV_HOZVAL, YUV_LINEVAL);
	ids_set_dma_addr(yaddr, yaddr + YUV_HOZVAL * YUV_LINEVAL);
	ids_enable(1);
	for (i = 0; i < 2; i++)
		lcd_wait_frame();
	return 0;
}

static int idsapi_case_test_dispatch(int case_num)
{
	int ret;

	switch (case_num) {
		case IDS_API_TEST_RGB:
			ret = idsapi_test_rgb();
			break;
		case IDS_API_TEST_YUV:
			ret = idsapi_test_yuv();
			break;
		default:
			idsapitest_show_usage();
			return -1;
	}

	printf("%s test %s\n", casename[case_num], result[ret]);
	return ret;
}

int idsapitest_main(int argc, char *argv[])
{
	int option_index = 0, c, ret = 0;
	static const char short_options[] = "c:h";
	static const struct option long_options[] = {
		{"case", 1, 0, 'c'},
		{"help", 0, 0, 'h'},
		{0, 0, 0, 0},
	};
	int case_num = -1;

	while ((c = getopt_long(argc, argv, short_options, long_options, &option_index)) != -1) {
		switch (c) {
			case 'c':
				case_num = simple_strtoul(optarg, NULL, 10);
				break;
			case 'h':
			default:
				idsapitest_show_usage();
				ret = -1;
				goto err;
		}
	}

	if (optind == 1) {   
		idsapitest_show_usage();
		ret = -1;        
		goto err;        
	}

	ret = idsapi_case_test_dispatch(case_num);
err: 
	optind = 1;
	return ret;
}

int idsapitest_rtl(int id)
{
	printf("invoking id: %d\n", id);
	return 0;
}

void idsapitest_init(void)
{
	register_testbench("idsapi", idsapitest_main, idsapitest_rtl);
}

testbench_init(idsapitest_init);

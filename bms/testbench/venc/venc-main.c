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
#include <testbench.h>
#include <semihost.h>

extern int32_t venc_jpeg_entry(int argc,char *argv[]);
extern int32_t venc_h264_entry(int argc,char *argv[]);
extern int32_t venc_video_stable_entry(int argc,char *argv[]);

static void venc_show_usage(void)
{
	printf("Usage: venc [type] [OPTION]...\n\n");
	printf("type: jpeg h264 or stab \n\n");
	printf("-h \t\tcommand help\n");
	printf("-w <size>\t\t width\n");
	printf("-h <size>\t\t high\n");
	printf("-t <0-2> \t\t YCbCr type:0-420, 1-422, 2-440\n");

}

int venc_main(int argc, char *argv[])
{
	int32_t ret = 0;
	
	if (argc < 3){
		venc_show_usage();
		return TB_RET_FAIL;
	}
	
	if(strncmp(argv[1], "jpeg", 4) == 0) {
		ret= venc_jpeg_entry(argc - 2 ,argv + 2);
	}
	else if(strncmp(argv[1], "h264", 4) == 0) {
		ret= venc_h264_entry(argc - 1 ,argv + 1);
	}
	else if(strncmp(argv[1], "stab", 4) == 0) {
		ret= venc_video_stable_entry(argc - 2, argv + 2);
	}
	else{
		venc_show_usage();
		return TB_RET_FAIL;
	}

	if(ret  >= 0 ){
	//	printf("test case run over ,and may need more manual check\n");
		return TB_RET_MANUAL;
	}
	else {
		printf("test case run failed\n");
		return TB_RET_FAIL;
	}
}

#ifndef CONFIG_TBH_VENC_LOCALCASE
int venc_module_enable(int id)
{
    int ret;
    char *module_name = "venc0";

    ret = itcs_module_enable(CPU, module_name);
    if (ret < 0)
        return ret;

    return 0;
}
#endif

void venc_init(void)
{
	register_testbench("venc_h264", venc_h264_entry, NULL);
	register_testbench("venc_jpeg", venc_jpeg_entry, NULL);
}

testbench_init(venc_init);


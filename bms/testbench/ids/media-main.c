#include <common.h>
#include <stdio.h>
#include <command.h>
#include <testbench.h>
#include <malloc.h>
#include <irq.h>
#include <asm/io.h>
#include <cache.h>
#include <sysm.h>

//#define MEDIA_DEBUG

#ifdef MEDIA_DEBUG
#define media_dbg(...) printf(__VA_ARGS__)
#else
#define media_dbg(...)
#endif

#define MEDIA_PERF_VENC 0
#define MEDIA_PERF_VDEC 1
#define MEDIA_PERF_NPU  2
#define MEDIA_PERF_IDS  3
extern unsigned  long g_ticks_per_us;

extern int venc_joint_test_init(void * param);
extern int venc_joint_test_start(int count);
extern int venc_joint_test_get_status(void);

extern int vdec_h264_perf_test_init(void * param);
extern int vdec_h264_perf_test_start(int index);
extern int vdec_h264_perf_test_get_status(void);

extern int npu_perf_test_init(void * param);
extern int npu_perf_test_start(int count);
extern int npu_perf_test_get_status(void);

extern int ids_rgb888_perf_test_init(void * param);
extern int ids_rgb888_perf_test_start(int count);
extern int ids_rgb888_perf_test_get_status(void);

int media_performance_module_init(int module, void * param)
{
	int ret = -1;
	switch(module){
		case MEDIA_PERF_VENC:
			media_dbg("venc init start...\n");
			ret = venc_joint_test_init(NULL);
			media_dbg("venc init end\n");
		break;
		case MEDIA_PERF_VDEC:
			media_dbg("vdec init start...\n");
			ret = vdec_h264_perf_test_init(NULL);
			media_dbg("vdec init end\n");
		break;
		case MEDIA_PERF_NPU:
			media_dbg("npu  init start...\n");
			ret = npu_perf_test_init(NULL);
			media_dbg("npu  init end\n");
		break;
		case MEDIA_PERF_IDS:
			media_dbg("ids init start...\n");
			ret = ids_rgb888_perf_test_init(NULL);
			media_dbg("ids init end\n");
		break;
		default:
			printf("media init module %d not support\n", module);
		break;
	}
	return ret;
}

int media_performance_module_start(int module, int index)
{
	int ret = -1;
	switch(module){
		case MEDIA_PERF_VENC:
			media_dbg("venc start start...\n");
			ret = venc_joint_test_start(index);
			media_dbg("venc start end...\n");
		break;
		case MEDIA_PERF_VDEC:
			media_dbg("vdec start start...\n");
			ret = vdec_h264_perf_test_start(index);
			media_dbg("vdec start end...\n");
		break;
		case MEDIA_PERF_NPU:
			media_dbg("npu  start start...\n");
			ret = npu_perf_test_start(index);
			media_dbg("npu  start end...\n");
		break;
		case MEDIA_PERF_IDS:
			media_dbg("ids start start...\n");
			ret = ids_rgb888_perf_test_start(index);
			media_dbg("ids start end...\n");
		break;
		default:
			printf("media start module %d not support\n", module);
		break;
	}
	return ret;
}

int media_performance_module_get_status(int module)
{
	int ret = -1;
	switch(module){
		case MEDIA_PERF_VENC:
			media_dbg("venc status start...\n");
			ret = venc_joint_test_get_status();
			media_dbg("venc status end...\n");
		break;
		case MEDIA_PERF_VDEC:
			media_dbg("vdec status start...\n");
			ret = vdec_h264_perf_test_get_status();
			media_dbg("vdec status end...\n");
		break;
		case MEDIA_PERF_NPU:
			media_dbg("npu  status start...\n");
			ret = npu_perf_test_get_status();
			media_dbg("npu  status end...\n");
		break;
		case MEDIA_PERF_IDS:
			media_dbg("ids status start...\n");
			ret = ids_rgb888_perf_test_get_status();
			media_dbg("ids status end...\n");
		break;
		default:
			//printf("media status module %d not support\n", module);
		break;
	}
	return ret;
}

static void media_show_usage(void) {
  printf("Usage: wdt [OPTION]...\n\n");
  printf("-h, --help\t\tcommand help\n");
  printf("-i, --individual\t\tindividual test \n");
  printf("-u, --union\t\tunion test \n");
}

unsigned long long ticks_record_venc[512][2];
unsigned long long ticks_record_vdec[512][2];
unsigned long long ticks_record_npu[512][2];
unsigned long long ticks_record_ids[512][2];


int media_individual_test(void){
	int ret = 0;
	int i = 0;
	int fc[4] = {0, 0, 0, 0}; // frame count arry
	
	unsigned long long start_ticks,end_ticks;
    itcs_dcache_flush();
	
	//initialization 
	for(i = 0; i < 4; i++){
		ret = media_performance_module_init(i, NULL);
		if(ret){
			printf("%d init failed\n", i);
			return -1;
		}
		if(i == MEDIA_PERF_VENC){
			ticks_record_venc[fc[i]][0] = get_ticks();
		}else if(i == MEDIA_PERF_VDEC){
			ticks_record_vdec[fc[i]][0] = get_ticks();
		}else if(i == MEDIA_PERF_NPU){
			ticks_record_npu[fc[i]][0] = get_ticks();
		}else if(i == MEDIA_PERF_IDS){
			ticks_record_ids[fc[i]][0] = get_ticks();
		}
	}

	start_ticks = get_ticks();
	for(i = 0; i<4; i++){
		if(fc[i] == 0){
			media_performance_module_start(i, fc[i]);
		}
	}

	while(1){
		for(i = 0; i<4; i++){
			ret = media_performance_module_get_status(i);
			if(ret){
				media_dbg("[%s] status ok\n", i);
				//end ticks
				if(i == MEDIA_PERF_VENC){
					ticks_record_venc[fc[i]][1] = get_ticks();
				}else if(i == MEDIA_PERF_VDEC){
					ticks_record_vdec[fc[i]][1] = get_ticks();
				}else if(i == MEDIA_PERF_NPU){
					ticks_record_npu[fc[i]][1] = get_ticks();
				}else if(i == MEDIA_PERF_IDS){
					ticks_record_ids[fc[i]][1] = get_ticks();
				}

				if(fc[MEDIA_PERF_VENC] >= 1 && fc[MEDIA_PERF_NPU] >= 1){
					int fps = 0;
					end_ticks = get_ticks();
					printf("--------------------------------------------------\n");
					printf("venc frame count:%d\n", fc[0]);
					for(i = 0; i< fc[0]; i++){
						printf("frame[%d] start:%lld, end:%lld\n", i, ticks_record_venc[i][0], ticks_record_venc[i][1]);
					}
					printf("--------------------------------------------------\n");
					printf("vdec frame count:%d\n", fc[1]);
					for(i = 0; i< fc[1]; i++){
						printf("frame[%d] start:%lld, end:%lld\n", i, ticks_record_vdec[i][0], ticks_record_vdec[i][1]);
					}
					printf("--------------------------------------------------\n");
					printf("npu  frame count:%d\n", fc[2]);
					for(i = 0; i< fc[2]; i++){
						printf("frame[%d] start:%lld, end:%lld\n", i, ticks_record_npu[i][0], ticks_record_npu[i][1]);
					}
					printf("--------------------------------------------------\n");
					printf("ids  frame count:%d\n", fc[3]);
					for(i = 0; i< fc[3]; i++){
						printf("frame[%d] start:%lld, end:%lld\n", i, ticks_record_ids[i][0], ticks_record_ids[i][1]);
					}
					printf("--------------------------------------------------\n");

					printf("whole start:%lld, end:%lld\n",start_ticks, end_ticks);
					printf("ticks per us: %lld\n", g_ticks_per_us);
					fps = (fc[0] * 1000 * 1000) / ((ticks_record_venc[fc[0] -1][1]- ticks_record_venc[0][0]) / g_ticks_per_us);
					printf("venc fps[%d]\n", fps);
					fps = (fc[1] * 1000 * 1000) / ((ticks_record_vdec[fc[1] -1][1]- ticks_record_vdec[0][0]) / g_ticks_per_us);
					printf("vdec fps[%d]\n", fps);
					fps = (fc[2] * 1000 * 1000) / ((ticks_record_npu[fc[2] -1][1] - ticks_record_npu[0][0]) / g_ticks_per_us);
					printf("npu  fps[%d]\n", fps);
					fps = (fc[3] * 1000 * 1000) / ((ticks_record_ids[fc[3] -1][1] - ticks_record_ids[0][0]) / g_ticks_per_us);
					printf("ids  fps[%d]\n", fps);
					printf("--------------------------------------------------\n");

					return 0;
				}
				fc[i]++;

				//start ticks
				media_performance_module_start(i, fc[i]);
				if(i == MEDIA_PERF_VENC){
					ticks_record_venc[fc[i]][0] = get_ticks();
				}else if(i == MEDIA_PERF_VDEC){
					ticks_record_vdec[fc[i]][0] = get_ticks();
				}else if(i == MEDIA_PERF_NPU){
					ticks_record_npu[fc[i]][0] = get_ticks();
				}else if(i == MEDIA_PERF_IDS){
					ticks_record_ids[fc[i]][0] = get_ticks();
				}

			}
		}

	}

    return 0;

}

int media_union_test(void){
	return 0;
}


int media_main(int argc, char *argv[]) {
  int mode = 0;

  if(argc != 2){
	printf("argc = %d error!\n", argc);
	media_show_usage();
	return -1;
  }

  if(strcmp(argv[1], "-i") == 0){
	mode = 0;
  }else if(strcmp(argv[1], "-u") == 0){
	mode = 1;
  }else{
	media_show_usage();
	return -1;
  }
  printf("Enable DDR Sample\n");
  //enable pmu sample statistic
  #ifdef CONFIG_TB_RUN_DDR1
  writel(0xffffffff,0xc3010000+ 0x100000+0x4);
  writel(0x1,0xc3010000+0x100000+0x0);
  #else
  int bootm = itcs_sysm_get_boot_mode(SAP) & 0xf;
  if(bootm == BOOTM_LPDDR4_WITH_INTLEAVE){
	printf("");
	writel(0xffffffff,0xc3010000+ 0x100000+0x4);
  	writel(0x1,0xc3010000+0x100000+0x0);
	writel(0xffffffff,0xc3010000+0x4);
  	writel(0x1,0xc3010000+0x0);
  }else if(bootm == BOOTM_LPDDR4_NO_INTLEAVE){
	writel(0xffffffff,0xc3010000+0x4);
  	writel(0x1,0xc3010000+0x0);
  }

  #endif
  printf("Enable DDR Sample done\n");


  if(mode){
	printf("Test Media Union Performance start...\n");
	media_union_test();
	printf("Test Media Union Performance Pass.\n");
  }else{
	printf("Test Media Individual Performance start...\n");
	media_individual_test();
	printf("Test Media Individual Performance Pass.\n");
  }

  return 0;
}

void media_init(void) { register_testbench("media", media_main, NULL); }

testbench_init(media_init);

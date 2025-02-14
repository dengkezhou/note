#ifndef VENC_LOCALCASE_H
#define VENC_LOCALCASE_H

#include "venc_localcase_func.h"
#include <common.h>
#include <fs.h>

extern unsigned int __lds_soc_base[];
#define VENC_DATA_BASE_ADDR ((unsigned long)__lds_soc_base)

#define VENC_READ_DATA_FROM_RTLFS 0
#define VENC_READ_DATA_FROM_SD    1

#define VENC_DATA_FROM VENC_READ_DATA_FROM_RTLFS
//#define VENC_DATA_FROM VENC_READ_DATA_FROM_SD

#if VENC_DATA_FROM == VENC_READ_DATA_FROM_SD

/* venc input/golden data, read from sd, instead of malloc */
#define VENC_OUTPUT_GOLDEN  (0x20000000UL + VENC_DATA_BASE_ADDR)
#define VENC_INPUT_DATA     (0x30000000UL + VENC_DATA_BASE_ADDR)
#define VENC_INPUT_CTABLE   (0x34000000UL + VENC_DATA_BASE_ADDR)
#define VENC_INPUT_STAB     (0x38000000UL + VENC_DATA_BASE_ADDR)

#elif VENC_DATA_FROM == VENC_READ_DATA_FROM_RTLFS
#define VENC_RTLFS_ADDR CONFIG_RTLFS_LOCATION
#endif

#define VENC_FILE_NAME_COUNT 64

/* venc output data, write to venc reg, the base_addr is VENC_OUTPUT_OFFSET */
#define VENC_OUTPUT_OFFSET          (0x10000000 + VENC_DATA_BASE_ADDR)
#define VENC0_EX_OUTPUT_OFFSET      0x50000000
#define VENC1_EX_OUTPUT_OFFSET      0x60000000
#define CASE_2042_OUTPUT5_ADDR      (0x1020ef88 + VENC_DATA_BASE_ADDR)

/*在menuconfig 中配置*/
//#define DEBUG_VENC_SPEED_TEST   /*速率测试，去除对比*/
//#define VENC_JOINT_TEST         /*联调测试，去除DEBUG_VENC_SPEED_TEST 中的时间获取，只对 venc_write_reg 和最终打印 做了处理，*/

#ifdef DEBUG_VENC_SPEED_TEST
#define VENC_NORMAL_LOG(format, ...)
#else
#define VENC_NORMAL_LOG(format, ...) printf(format, ##__VA_ARGS__)
#endif

typedef void (*TEST_CASE_FUNC)(); 

struct venc_localcase{
    char case_name[5];
    TEST_CASE_FUNC func;
    int pic_size;
    int pic_output;
    int pic_count;
};

struct venc_file_once{
    char file_name[VENC_FILE_NAME_COUNT];
    int fd;
    unsigned int reg_addr;
    void *real_addr; 
    ssize_t file_size;
};

struct venc_file_all{
    struct venc_file_once input_data_str;
    struct venc_file_once input_data_ctable;
    struct venc_file_once input_data_stab;
    struct venc_file_once output_data_golden;
};

struct venc_dev_id{
    int id;
    unsigned long base_addr;
    unsigned long sysm_addr;
};

static inline int atoi(char *s) {
  int i;
  int n = 0;
  for (i = 0; s[i] >= '0' && s[i] <= '9'; ++i) {
    n = 10 * n + (s[i] - '0');
  }
  return n;
}

int venc_module_enable(int id);

int __venc_load_file(struct venc_file_once *tmp);
void __venc_free_file(struct venc_file_once *tmp);
int venc_load_total_file(char * case_name);

int venc_load_file(struct venc_file_all *venc_file, char * case_name, int frame_num);
void venc_free_file(struct venc_file_all *venc_file);

int venc_read_reg(unsigned int reg);

struct venc_localcase * venc_get_case(char *case_name);

void venc_case_2300_frame(); /*jpeg 1080p yuv420sp*/
void venc_case_2400_frame(); /*jpeg 1080p rgb888*/

void venc_case_3000_frame(); /*jpeg use with pc*/
#endif

#ifndef __NPU_H__
#define __NPU_H__

#include <common.h>
#include <command.h>
#include <testbench.h>
#include <getopt.h>
#include <malloc.h>
#include <uart.h>
#include <cdns_uart.h>
#include <asm/io.h>
#include <getopt.h>
#include <pads.h>
#include <pll.h>
#include <cache.h>
#include <semihost.h>
#include <asm/io.h>
#include <asm/sizes.h>
#include <irq.h>
// #include <rtlfs.h>
#include <fs.h>
#include <crc32.h>
#include <malloc.h>
#include <hash.h>
#include <pmic.h>

#ifdef CONFIG_TB_RUN_DDR1
#define RTL_DUMP_ADDR 0x500000000
#else
#define RTL_DUMP_ADDR 0x100000000
#endif

#ifndef LPDDR4 
#define LPDDR4 1
#endif
#ifndef MPU_NUM 
#define MPU_NUM 0 //0 dd0 ,1 ddr ,2 dual ddr define
#endif
#ifndef EXTD_MODE 
#define EXTD_MODE 0
#endif
#ifndef SINGLE_BUS 
#define SINGLE_BUS  0
#endif
#ifndef AFE_MODE 
    //#define AFE_MODE 0  // bus0/1 by VIP id
#define AFE_MODE 0  // bus0/1 by afe id
#endif

#define MA_OUTW(addr,value) writel((value),(addr))
#define MA_INW(addr) readl(addr)

#define CLKGEN_BASE 0xc2f08000
#define SCLKGEN_BASE 0xd2f08000

#define  EVB_DEBUG_LOG 0

extern int pmic_vol_set(int pmic_id, char *name, int voltage);
extern int pmic_vol_get(int pmic_id, char *name, int *voltage);

int set_npu_clock();

void soc_dump0(uint64_t src_addr, uint32_t size);

void soc_dump1(uint64_t src_addr, uint32_t size);

int soc_dump0_compare(uint64_t src_addr, uint32_t size);

int regist_init();

int close_file_node(int*fd,int count);

int open_file_node(char* file_name[],unsigned long int*addrs,int* fd,int count);

int npu_input_file_batch(const char *filename,int start,int end);

int npu_only_rtl(char*cmd_s);
int npu_9200_evb_test(char *input_cmd);

void yolov5s_id3_2core_DV(int64_t core_clk);
void  yolov5_id3_core0_DV(int64_t core_clk);
void  yolov5s_id3_core1_DV(int64_t core_clk);

int npu_compare(const char *filename);

void soc_dump0(uint64_t src_addr, uint32_t size);

void clk_up_test();

int test_npu_freq(void);

#ifdef CONFIG_COMPILE_RTL
void AluFunction_0_test_dump();

void sp_AluFunction_test1_dump();


void kernel3x3_pooling0();

void sp_AluFunction_0_dump();

void sp_AluFunction_2_dump();

void nn_read_and_ot_dump();

void nn_write_dump();

void storageSame_dump();

void convStride_1_dump();
void in2ndChnum_16_dump();
void inChnum_16_dump();
void image_Type_0_2_dump();
void kernel_image_Date1_dump();

void inimage_Data_7_8_dump();

void kernel1_pooling_0_dump();
void kernelData_0_2_dump();

void kernelData_7_dump();
void control1_ch2_fromV11V12();


void outChNum_16_dump();

void OutimageData_0_2_dump();

void OutimageData_1_7_dump();


void OutimageData_4_dump();
void OutimageData_8_dump();
#else
int AluFunction_0_test_dump();

int sp_AluFunction_test1_dump();


int kernel3x3_pooling0();

int sp_AluFunction_0_dump();

int sp_AluFunction_2_dump();

int nn_read_and_ot_dump();

int nn_write_dump();

int storageSame_dump();

int convStride_1_dump();
int in2ndChnum_16_dump();
int inChnum_16_dump();
int image_Type_0_2_dump();
int kernel_image_Date1_dump();

int inimage_Data_7_8_dump();

int kernel1_pooling_0_dump();
int kernelData_0_2_dump();

int kernelData_7_dump();
int control1_ch2_fromV11V12();


int outChNum_16_dump();

int OutimageData_0_2_dump();

int OutimageData_1_7_dump();


int OutimageData_4_dump();
int OutimageData_8_dump();
#endif

#endif
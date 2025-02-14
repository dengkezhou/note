#ifndef _VENC_API_H_
#define  _VENC_API_H_


//#include <h264encapi.h>
//#include <jpegencapi.h>
//#include <vidstbapi.h>
#include <common.h>
#include <assert.h>
#include <asm/io.h>
//#include <jpeg-encode.h>

#define INFO 1
#define WARN 1
#define ERR  1

#define __DEBUG__
#ifdef  __DEBUG__
#define VENC_LOG(on,format) if(on)(printf format)
#else
#define VENC_LOG(on,format)
#endif

#define MODULE_COMMON "ENCODE_TEST::COMMON"
#define MODULE_JPEG  "GRAPHIC_ENC::JPEG"
#define MODULE_H264  "VIDEO_ENC::H264"
#define MODULE_STAB	  "STABILIZATION::CAMERA"


/***********************************Common Encoder*******************************************************/
#define MAXENCODEDPICS 10000000
#define VENC_RANDOM_VALUE  (0xFFFFFFFF-2)

//#define VENC_H264_TRACE_8270_API
//#define VENC_JPEG_TRACE_8270_API
//#define VENC_VS_TRACE_8270_API
//#define __OSDDISPLAY__
//#define __VENC_PERFORMANCE_TEST__

#ifdef __VENC_PERFORMANCE_TEST__
	//#define __VENC_USE_PWM_TIME__
#define __VENC_USE_GPIO_TIME__
#endif

#define CHECK_JUMP_ERROR(exp)		if((exp) < 0 ){goto ERROR_PROCESS;}
typedef enum{
	TYPE_H264=0,
	TYPE_JPEG,
	TYPE_CAMSTAB,
	TYPE_VP8,
}VENC_TYPE,Venc_type;

typedef struct{
	uint32_t  *vBuffer;
	uint32_t bBuffer;
	uint32_t  size;
	int32_t offset ;

	uint32_t addr_y;
	uint32_t addr_u;
	uint32_t addr_v;
}VencLinearMem;


typedef struct{
	uint32_t *vir_addr;
	uint32_t phy_addr;
	uint32_t size;
	uint32_t flag;
}vdec_buffer;


typedef struct {
	unsigned int offset ;
	int rw ; //0,r0;1,rw;2,wo
}VENC_REG_ACCESS_INFO;





int venc_write_file(FILE *file,void *buffer,unsigned int size,int endian);


void venc_copy_with_check(unsigned int *dst,unsigned int *src,int size);
int venc_write_file(FILE *file,void *buffer,unsigned int size,int endian);
int32_t dump_venc_linear_mem_to_file(FILE *fd ,VencLinearMem *mem,uint32_t crc32);
int32_t write_to_venc_linear_mem(VencLinearMem *mem,int8_t *buf,uint32_t len,int32_t resetFlag);

int venc_basic_reg_test(int32_t testType);
void venc_reg_access(const VENC_REG_ACCESS_INFO *reg,size_t base);


int32_t venc_load_file_to_mem(char *filename ,VencLinearMem *mem,uint32_t size);
int32_t venc_dump_mem_to_file(char *filename,VencLinearMem *mem,uint32_t crc32,char *msg);
int32_t venc_free_linear_buffer(VencLinearMem *mem);
int32_t venc_malloc_linear_buffer(VencLinearMem *mem,int32_t size);

int venc_get_random_size(int max,int min);
int venc_get_default_cfg(VENC_TYPE type,void **excfg);
#endif









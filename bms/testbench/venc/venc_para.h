#ifndef VENC_LOCALCASE_H
#define VENC_LOCALCASE_H


#include <h264encapi.h>
#define VENC_INPUT_ADDR 0x110000000
#define VENC_OUTPUT_ADDR 0x110000000
#define VENC_CMP_ADDR 0x110000000

struct venc_localcase_h264_para
{
    int width;
    int height; 
    int size;  

    H264EncPictureType inputType;

    unsigned long input_addr;
    unsigned int input_addr_y;
    unsigned int input_addr_u;
    unsigned int input_addr_v;
    
    unsigned long output_addr;

    char *cmp_addr;
};

int32_t venc_localcase_encode(int argc,char *argv[]);
void venc_localcase_cmp(struct venc_localcase_h264_para *para);
int venc_module_enable(int id);

void venc_case_1152();





#endif
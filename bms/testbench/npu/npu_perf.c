#include <common.h>

#define NPU_ADDR_BASE_0 0xc7000000
#define NPU_ADDR_BASE_1 0xc7800000

#define MA_OUTW(addr,value) writel((value),(addr))
#define MA_INW(addr) readl(addr)



#ifndef SINGLE_BUS 
#define SINGLE_BUS  0
#endif
#ifndef AFE_MODE 
    
#define AFE_MODE 1  // bus0/1 by afe id
#endif

typedef enum {
    YOLOV_IDS_2CORE = 0,
    YOLOV_DUAL_CORE_DDR0,
    YOLOV_SINGLE_CORE_DDR0,
    YOLOV_DUAL_CORE0_DDR0_EVB,
    YOLOV_DUAL_CORE1_DDR0_EVB,
    YOLOV_DUAL_2CORE_DDR0_EVB
}NPU_PERF_CTL;

extern int npu_input_file_batch(const char *filename,int start,int end);

int get_status_0(){
    
    uint32_t npu_status = MA_INW(NPU_ADDR_BASE_0+0x04);
    if(npu_status == 0x7fffffff ){
        // MA_INW((NPU_ADDR_BASE_0 + 0x000078));
        return 1;
    }
    return 0;
}
int get_status_1(){
    
    uint32_t npu_status = MA_INW(NPU_ADDR_BASE_1+0x04);
     if(npu_status == 0x7fffffff){
        // MA_INW((NPU_ADDR_BASE_1 + 0x000078));
        return 1;
    }
    return 0;
}
/*返回 */
int npu_perf_test_get_status(int id){
   
    if(id == 0){
        if(get_status_0() == 1){
            return 1;
        }
    }else if(id == 1){
        if(get_status_1() == 1){
            return 1;
        }
    }else{
        if((get_status_0() == 1)  && (get_status_1() == 1)){
            return 1;
        }
    }
   
    return 0;
}



int start_core_1(){
    

    MA_OUTW((NPU_ADDR_BASE_1 + 0x000000), 0x070900);
    MA_OUTW((NPU_ADDR_BASE_1 + 0x000104), 0x000000);
    MA_OUTW((NPU_ADDR_BASE_1 + 0x00010C), 0x15A0881);
    MA_OUTW((NPU_ADDR_BASE_1 + 0x00010C), 0x15A0880);
    MA_OUTW((NPU_ADDR_BASE_1 + 0x000000), 0x070B00);
    MA_OUTW((NPU_ADDR_BASE_1 + 0x000000), 0x070900);
    MA_OUTW((NPU_ADDR_BASE_1 + 0x000000), 0x0F0900);
    MA_OUTW((NPU_ADDR_BASE_1 + 0x0003A8), 0x000001);
    MA_OUTW((NPU_ADDR_BASE_1 + 0x0003A8), 0x000000);
    MA_OUTW((NPU_ADDR_BASE_1 + 0x000000), 0x0F0900);
    MA_OUTW((NPU_ADDR_BASE_1 + 0x000000), 0x070900);
    MA_INW((NPU_ADDR_BASE_1 + 0x000004));
    MA_INW((NPU_ADDR_BASE_1 + 0x000000));
    MA_INW((NPU_ADDR_BASE_1 + 0x000388));
    MA_OUTW((NPU_ADDR_BASE_1 + 0x000104), 0x000000);
    MA_OUTW((NPU_ADDR_BASE_1 + 0x00010C), 0x15A0881);
    MA_OUTW((NPU_ADDR_BASE_1 + 0x00010C), 0x15A0880);
    MA_OUTW((NPU_ADDR_BASE_1 + 0x000000), 0x070B00);
    MA_OUTW((NPU_ADDR_BASE_1 + 0x000000), 0x070900);
    MA_OUTW((NPU_ADDR_BASE_1 + 0x000000), 0x0F0900);
    MA_OUTW((NPU_ADDR_BASE_1 + 0x0003A8), 0x000001);
    MA_OUTW((NPU_ADDR_BASE_1 + 0x0003A8), 0x000000);
    MA_OUTW((NPU_ADDR_BASE_1 + 0x000000), 0x0F0900);
    MA_OUTW((NPU_ADDR_BASE_1 + 0x000000), 0x070900);
    MA_INW((NPU_ADDR_BASE_1 + 0x000004));
    MA_INW((NPU_ADDR_BASE_1 + 0x000000));
    MA_INW((NPU_ADDR_BASE_1 + 0x000388));
    MA_OUTW((NPU_ADDR_BASE_1 + 0x00055C), 0xFFFFFF);
    MA_OUTW((NPU_ADDR_BASE_1 + 0x000090), 0x000000);
    MA_OUTW((NPU_ADDR_BASE_1 + 0x000000), 0x070900);
    MA_OUTW((NPU_ADDR_BASE_1 + 0x000000), 0x070100);
    MA_OUTW((NPU_ADDR_BASE_1 + 0x0003A8), 0x000002);
    MA_OUTW((NPU_ADDR_BASE_1 + 0x00003C), 0xFFFFFFFF);
    MA_OUTW((NPU_ADDR_BASE_1 + 0x00003C), 0x000000);
    MA_OUTW((NPU_ADDR_BASE_1 + 0x000100), 0x140021);
    MA_OUTW((NPU_ADDR_BASE_1 + 0x000104), 0x000000);
    MA_OUTW((NPU_ADDR_BASE_1 + 0x00010C), 0x15A0880);
    MA_OUTW((NPU_ADDR_BASE_1 + 0x000090), 0x000040);
    MA_OUTW((NPU_ADDR_BASE_1 + 0x000414), 0x000000);
    MA_OUTW((NPU_ADDR_BASE_1 + 0x000014), 0xFFFFFFFF);
    MA_OUTW((NPU_ADDR_BASE_1 + 0x0003B4), 0x5200020);
    MA_OUTW((NPU_ADDR_BASE_1 + 0x000388), 0x000021);
    MA_OUTW((NPU_ADDR_BASE_1 + 0x000654), 0x25005000);
    MA_OUTW((NPU_ADDR_BASE_1 + 0x0003A4), 0x010013);

   
    return 0;
}

int start_core_0(){
    
     MA_OUTW((NPU_ADDR_BASE_0 + 0x000000), 0x070900);
    MA_OUTW((NPU_ADDR_BASE_0 + 0x000104), 0x000000);
    MA_OUTW((NPU_ADDR_BASE_0 + 0x00010C), 0x15A0881);
    MA_OUTW((NPU_ADDR_BASE_0 + 0x00010C), 0x15A0880);
    MA_OUTW((NPU_ADDR_BASE_0 + 0x000000), 0x070B00);
    MA_OUTW((NPU_ADDR_BASE_0 + 0x000000), 0x070900);
    MA_OUTW((NPU_ADDR_BASE_0 + 0x000000), 0x0F0900);
    MA_OUTW((NPU_ADDR_BASE_0 + 0x0003A8), 0x000001);
    MA_OUTW((NPU_ADDR_BASE_0 + 0x0003A8), 0x000000);
    MA_OUTW((NPU_ADDR_BASE_0 + 0x000000), 0x0F0900);
    MA_OUTW((NPU_ADDR_BASE_0 + 0x000000), 0x070900);
    MA_INW((NPU_ADDR_BASE_0 + 0x000004));
    MA_INW((NPU_ADDR_BASE_0 + 0x000000));
    MA_INW((NPU_ADDR_BASE_0 + 0x000388));
    MA_OUTW((NPU_ADDR_BASE_0 + 0x000104), 0x000000);
    MA_OUTW((NPU_ADDR_BASE_0 + 0x00010C), 0x15A0881);
    MA_OUTW((NPU_ADDR_BASE_0 + 0x00010C), 0x15A0880);
    MA_OUTW((NPU_ADDR_BASE_0 + 0x000000), 0x070B00);
    MA_OUTW((NPU_ADDR_BASE_0 + 0x000000), 0x070900);
    MA_OUTW((NPU_ADDR_BASE_0 + 0x000000), 0x0F0900);
    MA_OUTW((NPU_ADDR_BASE_0 + 0x0003A8), 0x000001);
    MA_OUTW((NPU_ADDR_BASE_0 + 0x0003A8), 0x000000);
    MA_OUTW((NPU_ADDR_BASE_0 + 0x000000), 0x0F0900);
    MA_OUTW((NPU_ADDR_BASE_0 + 0x000000), 0x070900);
    MA_INW((NPU_ADDR_BASE_0 + 0x000004));
    MA_INW((NPU_ADDR_BASE_0 + 0x000000));
    MA_INW((NPU_ADDR_BASE_0 + 0x000388));
    MA_OUTW((NPU_ADDR_BASE_0 + 0x00055C), 0xFFFFFF);
    MA_OUTW((NPU_ADDR_BASE_0 + 0x000090), 0x000000);
       
    MA_OUTW((NPU_ADDR_BASE_0 + 0x000000), 0x070900);
    MA_OUTW((NPU_ADDR_BASE_0 + 0x000000), 0x070100);
    MA_OUTW((NPU_ADDR_BASE_0 + 0x0003A8), 0x000002);
    MA_OUTW((NPU_ADDR_BASE_0 + 0x00003C), 0xFFFFFFFF);
    MA_OUTW((NPU_ADDR_BASE_0 + 0x00003C), 0x000000);
    MA_OUTW((NPU_ADDR_BASE_0 + 0x000100), 0x140021);
    MA_OUTW((NPU_ADDR_BASE_0 + 0x000104), 0x000000);
    MA_OUTW((NPU_ADDR_BASE_0 + 0x00010C), 0x15A0880);
    MA_OUTW((NPU_ADDR_BASE_0 + 0x000090), 0x000040);
    MA_OUTW((NPU_ADDR_BASE_0 + 0x000414), 0x000000);
    MA_OUTW((NPU_ADDR_BASE_0 + 0x000014), 0xFFFFFFFF);
       
    MA_OUTW((NPU_ADDR_BASE_0 + 0x0003B4), 0x5100020);
    MA_OUTW((NPU_ADDR_BASE_0 + 0x000388), 0x000021);
    MA_OUTW((NPU_ADDR_BASE_0 + 0x000654), 0x25005000);
    MA_OUTW((NPU_ADDR_BASE_0 + 0x0003A4), 0x010013);
    
    
    return 0;
}

void yolov5s_init_core0(){
    
    printf("npu yolov5s_core0_DV test start!\n");
        
        MA_OUTW((NPU_ADDR_BASE_0 + 0x000078),0);
        MA_OUTW((NPU_ADDR_BASE_0 + 0x000000), 0x070900);
        MA_OUTW((NPU_ADDR_BASE_0 + 0x000104), 0x000000);
        MA_OUTW((NPU_ADDR_BASE_0 + 0x00010C), 0x15A0881);
        MA_OUTW((NPU_ADDR_BASE_0 + 0x00010C), 0x15A0880);
        MA_OUTW((NPU_ADDR_BASE_0 + 0x000000), 0x070B00);
        MA_OUTW((NPU_ADDR_BASE_0 + 0x000000), 0x070900);
        MA_OUTW((NPU_ADDR_BASE_0 + 0x000000), 0x0F0900);
        MA_OUTW((NPU_ADDR_BASE_0 + 0x0003A8), 0x000001);
        MA_OUTW((NPU_ADDR_BASE_0 + 0x0003A8), 0x000000);
        MA_OUTW((NPU_ADDR_BASE_0 + 0x000000), 0x0F0900);
        MA_OUTW((NPU_ADDR_BASE_0 + 0x000000), 0x070900);
        MA_INW((NPU_ADDR_BASE_0 + 0x000004));
        MA_INW((NPU_ADDR_BASE_0 + 0x000000));
        MA_INW((NPU_ADDR_BASE_0 + 0x000388));
        MA_OUTW((NPU_ADDR_BASE_0 + 0x000104), 0x000000);
        MA_OUTW((NPU_ADDR_BASE_0 + 0x00010C), 0x15A0881);
        MA_OUTW((NPU_ADDR_BASE_0 + 0x00010C), 0x15A0880);
        MA_OUTW((NPU_ADDR_BASE_0 + 0x000000), 0x070B00);
        MA_OUTW((NPU_ADDR_BASE_0 + 0x000000), 0x070900);
        MA_OUTW((NPU_ADDR_BASE_0 + 0x000000), 0x0F0900);
        MA_OUTW((NPU_ADDR_BASE_0 + 0x0003A8), 0x000001);
        MA_OUTW((NPU_ADDR_BASE_0 + 0x0003A8), 0x000000);
        MA_OUTW((NPU_ADDR_BASE_0 + 0x000000), 0x0F0900);
        MA_OUTW((NPU_ADDR_BASE_0 + 0x000000), 0x070900);
        MA_INW((NPU_ADDR_BASE_0 + 0x000004));
        MA_INW((NPU_ADDR_BASE_0 + 0x000000));
        MA_INW((NPU_ADDR_BASE_0 + 0x000388));
        MA_OUTW((NPU_ADDR_BASE_0 + 0x00055C), 0xFFFFFF);
        MA_OUTW((NPU_ADDR_BASE_0 + 0x000090), 0x000000);
    
        MA_OUTW((NPU_ADDR_BASE_0 + 0x000000), 0x070900);
        MA_OUTW((NPU_ADDR_BASE_0 + 0x000000), 0x070100);
        MA_OUTW((NPU_ADDR_BASE_0 + 0x0003A8), 0x000002);
        MA_OUTW((NPU_ADDR_BASE_0 + 0x00003C), 0xFFFFFFFF);
        MA_OUTW((NPU_ADDR_BASE_0 + 0x00003C), 0x000000);
        MA_OUTW((NPU_ADDR_BASE_0 + 0x000100), 0x140021);
        MA_OUTW((NPU_ADDR_BASE_0 + 0x000104), 0x000000);
        MA_OUTW((NPU_ADDR_BASE_0 + 0x00010C), 0x15A0880);
        MA_OUTW((NPU_ADDR_BASE_0 + 0x000090), 0x000040);
        MA_OUTW((NPU_ADDR_BASE_0 + 0x000414), 0x000000);
        MA_OUTW((NPU_ADDR_BASE_0 + 0x000014), 0xFFFFFFFF);
  
#ifdef CONFIG_TB_RUN_DDR1
        MA_OUTW((NPU_ADDR_BASE_0 + 0x0003B4), 0x5100020);
#else
        MA_OUTW((NPU_ADDR_BASE_0 + 0x0003B4), 0x1100020);
#endif 
        MA_OUTW((NPU_ADDR_BASE_0 + 0x000388), 0x000021);

        MA_OUTW((NPU_ADDR_BASE_0 + 0x000654), 0x25005000);
        MA_OUTW((NPU_ADDR_BASE_0 + 0x0003A4), 0x010013);
}

void yolov5s_init_core1(){
    printf("npu yolov5s_id3_core1_DV test start!\n"); 
       
        MA_OUTW((NPU_ADDR_BASE_1 + 0x000000), 0x070900);
        MA_OUTW((NPU_ADDR_BASE_1 + 0x000104), 0x000000);
        MA_OUTW((NPU_ADDR_BASE_1 + 0x00010C), 0x15A0881);
        MA_OUTW((NPU_ADDR_BASE_1 + 0x00010C), 0x15A0880);
        MA_OUTW((NPU_ADDR_BASE_1 + 0x000000), 0x070B00);
        MA_OUTW((NPU_ADDR_BASE_1 + 0x000000), 0x070900);
        MA_OUTW((NPU_ADDR_BASE_1 + 0x000000), 0x0F0900);
        MA_OUTW((NPU_ADDR_BASE_1 + 0x0003A8), 0x000001);
        MA_OUTW((NPU_ADDR_BASE_1 + 0x0003A8), 0x000000);
        MA_OUTW((NPU_ADDR_BASE_1 + 0x000000), 0x0F0900);
        MA_OUTW((NPU_ADDR_BASE_1 + 0x000000), 0x070900);
        MA_INW((NPU_ADDR_BASE_1 + 0x000004));
        MA_INW((NPU_ADDR_BASE_1 + 0x000000));
        MA_INW((NPU_ADDR_BASE_1 + 0x000388));
        MA_OUTW((NPU_ADDR_BASE_1 + 0x000104), 0x000000);
        MA_OUTW((NPU_ADDR_BASE_1 + 0x00010C), 0x15A0881);
        MA_OUTW((NPU_ADDR_BASE_1 + 0x00010C), 0x15A0880);
        MA_OUTW((NPU_ADDR_BASE_1 + 0x000000), 0x070B00);
        MA_OUTW((NPU_ADDR_BASE_1 + 0x000000), 0x070900);
        MA_OUTW((NPU_ADDR_BASE_1 + 0x000000), 0x0F0900);
        MA_OUTW((NPU_ADDR_BASE_1 + 0x0003A8), 0x000001);
        MA_OUTW((NPU_ADDR_BASE_1 + 0x0003A8), 0x000000);
        MA_OUTW((NPU_ADDR_BASE_1 + 0x000000), 0x0F0900);
        MA_OUTW((NPU_ADDR_BASE_1 + 0x000000), 0x070900);
        MA_INW((NPU_ADDR_BASE_1 + 0x000004));
        MA_INW((NPU_ADDR_BASE_1 + 0x000000));
        MA_INW((NPU_ADDR_BASE_1 + 0x000388));
        MA_OUTW((NPU_ADDR_BASE_1 + 0x00055C), 0xFFFFFF);
        MA_OUTW((NPU_ADDR_BASE_1 + 0x000090), 0x000000);           
  
        MA_OUTW((NPU_ADDR_BASE_1 + 0x000000), 0x070900);
        MA_OUTW((NPU_ADDR_BASE_1 + 0x000000), 0x070100);
        MA_OUTW((NPU_ADDR_BASE_1 + 0x0003A8), 0x000002);
        MA_OUTW((NPU_ADDR_BASE_1 + 0x00003C), 0xFFFFFFFF);
        MA_OUTW((NPU_ADDR_BASE_1 + 0x00003C), 0x000000);
        MA_OUTW((NPU_ADDR_BASE_1 + 0x000100), 0x140021);
        MA_OUTW((NPU_ADDR_BASE_1 + 0x000104), 0x000000);
        MA_OUTW((NPU_ADDR_BASE_1 + 0x00010C), 0x15A0880);
        MA_OUTW((NPU_ADDR_BASE_1 + 0x000090), 0x000040);
        MA_OUTW((NPU_ADDR_BASE_1 + 0x000414), 0x000000);
        MA_OUTW((NPU_ADDR_BASE_1 + 0x000014), 0xFFFFFFFF);
   

#ifdef CONFIG_TB_RUN_DDR1
        MA_OUTW((NPU_ADDR_BASE_1 + 0x0003B4), 0x5200020);
#else
        MA_OUTW((NPU_ADDR_BASE_1 + 0x0003B4), 0x1200020);
#endif
        MA_OUTW((NPU_ADDR_BASE_1 + 0x000388), 0x000021);

        MA_OUTW((NPU_ADDR_BASE_1 + 0x000654), 0x25005000);
        MA_OUTW((NPU_ADDR_BASE_1 + 0x0003A4), 0x010013);
}


int start_core_dual_kernal_0(){
   
    MA_OUTW((NPU_ADDR_BASE_0 + 0x000000), 0x070900);
    MA_OUTW((NPU_ADDR_BASE_0 + 0x000104), 0x000000);
    MA_OUTW((NPU_ADDR_BASE_0 + 0x00010C), 0x15A0881);
    MA_OUTW((NPU_ADDR_BASE_0 + 0x00010C), 0x15A0880);
    MA_OUTW((NPU_ADDR_BASE_0 + 0x000000), 0x070B00);
    MA_OUTW((NPU_ADDR_BASE_0 + 0x000000), 0x070900);
    MA_OUTW((NPU_ADDR_BASE_0 + 0x000000), 0x0F0900);
    MA_OUTW((NPU_ADDR_BASE_0 + 0x0003A8), 0x000001);
    MA_OUTW((NPU_ADDR_BASE_0 + 0x0003A8), 0x000000);
    MA_OUTW((NPU_ADDR_BASE_0 + 0x000000), 0x0F0900);
    MA_OUTW((NPU_ADDR_BASE_0 + 0x000004), 0x7FFFFFFF);
    MA_INW((NPU_ADDR_BASE_0 + 0x000000));
    MA_INW((NPU_ADDR_BASE_0 + 0x000388));
    MA_INW((NPU_ADDR_BASE_0 + 0x000388));
    MA_OUTW((NPU_ADDR_BASE_0 + 0x000104), 0x000000);
    MA_OUTW((NPU_ADDR_BASE_0 + 0x00010C), 0x15A0881);
    MA_OUTW((NPU_ADDR_BASE_0 + 0x00010C), 0x15A0880);
    MA_OUTW((NPU_ADDR_BASE_0 + 0x000000), 0x070B00);
    MA_OUTW((NPU_ADDR_BASE_0 + 0x000000), 0x070900);
    MA_OUTW((NPU_ADDR_BASE_0 + 0x000000), 0x0F0900);
    MA_OUTW((NPU_ADDR_BASE_0 + 0x0003A8), 0x000001);
    MA_OUTW((NPU_ADDR_BASE_0 + 0x0003A8), 0x000000);
    MA_OUTW((NPU_ADDR_BASE_0 + 0x000000), 0x0F0900);
    MA_OUTW((NPU_ADDR_BASE_0 + 0x000004), 0x7FFFFFFF);
    MA_INW((NPU_ADDR_BASE_0 + 0x000000));
    MA_INW((NPU_ADDR_BASE_0 + 0x000388));
    MA_INW((NPU_ADDR_BASE_0 + 0x000388));
    MA_OUTW((NPU_ADDR_BASE_0 + 0x000090), 0x000000);
    MA_OUTW((NPU_ADDR_BASE_0 + 0x000090), 0x000000);

    MA_OUTW((NPU_ADDR_BASE_0 + 0x000000), 0x070900);
    MA_OUTW((NPU_ADDR_BASE_0 + 0x000000), 0x070100);
    MA_OUTW((NPU_ADDR_BASE_0 + 0x0003A8), 0x000002);
    MA_OUTW((NPU_ADDR_BASE_0 + 0x00003C), 0xFFFFFFFF);
    MA_OUTW((NPU_ADDR_BASE_0 + 0x00003C), 0x000000);
    MA_OUTW((NPU_ADDR_BASE_0 + 0x000100), 0x140021);
    MA_OUTW((NPU_ADDR_BASE_0 + 0x00010C), 0x15A0880);
    MA_OUTW((NPU_ADDR_BASE_0 + 0x000090), 0x000000);
    MA_OUTW((NPU_ADDR_BASE_0 + 0x000414), 0x000000);
    MA_OUTW((NPU_ADDR_BASE_0 + 0x000414), 0x000000);
    MA_OUTW((NPU_ADDR_BASE_0 + 0x000388), 0x000001);

    MA_OUTW((NPU_ADDR_BASE_0 + 0x0003B4), 0x5100020);
    MA_OUTW((NPU_ADDR_BASE_0 + 0x000388), 0x000021);

    MA_OUTW((NPU_ADDR_BASE_0 + 0x000654), 0x25005000);
    MA_OUTW((NPU_ADDR_BASE_0 + 0x0003A4), 0x010013);
    
    return 0;
}
int start_core_dual_kernal_1(){
    
    MA_OUTW((NPU_ADDR_BASE_1 + 0x000000), 0x070900);
    MA_OUTW((NPU_ADDR_BASE_1 + 0x000104), 0x000000);
    MA_OUTW((NPU_ADDR_BASE_1 + 0x00010C), 0x15A0881);
    MA_OUTW((NPU_ADDR_BASE_1 + 0x00010C), 0x15A0880);
    MA_OUTW((NPU_ADDR_BASE_1 + 0x000000), 0x070B00);
    MA_OUTW((NPU_ADDR_BASE_1 + 0x000000), 0x070900);
    MA_OUTW((NPU_ADDR_BASE_1 + 0x000000), 0x0F0900);
    MA_OUTW((NPU_ADDR_BASE_1 + 0x0003A8), 0x000001);
    MA_OUTW((NPU_ADDR_BASE_1 + 0x0003A8), 0x000000);
    MA_OUTW((NPU_ADDR_BASE_1 + 0x000000), 0x0F0900);
    MA_OUTW((NPU_ADDR_BASE_1 + 0x000004), 0x7FFFFFFF);
    MA_INW((NPU_ADDR_BASE_1 + 0x000000));
    MA_INW((NPU_ADDR_BASE_1 + 0x000388));
    MA_INW((NPU_ADDR_BASE_1 + 0x000388));
    MA_OUTW((NPU_ADDR_BASE_1 + 0x000104), 0x000000);
    MA_OUTW((NPU_ADDR_BASE_1 + 0x00010C), 0x15A0881);
    MA_OUTW((NPU_ADDR_BASE_1 + 0x00010C), 0x15A0880);
    MA_OUTW((NPU_ADDR_BASE_1 + 0x000000), 0x070B00);
    MA_OUTW((NPU_ADDR_BASE_1 + 0x000000), 0x070900);
    MA_OUTW((NPU_ADDR_BASE_1 + 0x000000), 0x0F0900);
    MA_OUTW((NPU_ADDR_BASE_1 + 0x0003A8), 0x000001);
    MA_OUTW((NPU_ADDR_BASE_1 + 0x0003A8), 0x000000);
    MA_OUTW((NPU_ADDR_BASE_1 + 0x000000), 0x0F0900);
    MA_OUTW((NPU_ADDR_BASE_1 + 0x000004), 0x7FFFFFFF);
    MA_INW((NPU_ADDR_BASE_1 + 0x000000));
    MA_INW((NPU_ADDR_BASE_1 + 0x000388));
    MA_INW((NPU_ADDR_BASE_1 + 0x000388));
    MA_OUTW((NPU_ADDR_BASE_1 + 0x000090), 0x000000);
    MA_OUTW((NPU_ADDR_BASE_1 + 0x000090), 0x000000);

    MA_OUTW((NPU_ADDR_BASE_1 + 0x000000), 0x070900);
    MA_OUTW((NPU_ADDR_BASE_1 + 0x000000), 0x070100);
    MA_OUTW((NPU_ADDR_BASE_1 + 0x0003A8), 0x000002);
    MA_OUTW((NPU_ADDR_BASE_1 + 0x00003C), 0xFFFFFFFF);
    MA_OUTW((NPU_ADDR_BASE_1 + 0x00003C), 0x000000);
    MA_OUTW((NPU_ADDR_BASE_1 + 0x000100), 0x140021);
    MA_OUTW((NPU_ADDR_BASE_1 + 0x00010C), 0x15A0880);
    MA_OUTW((NPU_ADDR_BASE_1 + 0x000090), 0x000000);
    MA_OUTW((NPU_ADDR_BASE_1 + 0x000414), 0x000000);
    MA_OUTW((NPU_ADDR_BASE_1 + 0x000414), 0x000000);
    MA_OUTW((NPU_ADDR_BASE_1 + 0x000388), 0x000001);

    MA_OUTW((NPU_ADDR_BASE_1 + 0x0003B4), 0x5200020);
    MA_OUTW((NPU_ADDR_BASE_1 + 0x000388), 0x000021);

    MA_OUTW((NPU_ADDR_BASE_1 + 0x000654), 0x25005000);
    MA_OUTW((NPU_ADDR_BASE_1 + 0x0003A4), 0x010013);

    
    return 0;
}

int start_core_single_kernel_0(){
    
    MA_OUTW((NPU_ADDR_BASE_0 + 0x000000), 0x070900);
    MA_OUTW((NPU_ADDR_BASE_0 + 0x000104), 0x000000);
    MA_OUTW((NPU_ADDR_BASE_0 + 0x00010C), 0x15A0881);
    MA_OUTW((NPU_ADDR_BASE_0 + 0x00010C), 0x15A0880);
    MA_OUTW((NPU_ADDR_BASE_0 + 0x000000), 0x070B00);
    MA_OUTW((NPU_ADDR_BASE_0 + 0x000000), 0x070900);
    MA_OUTW((NPU_ADDR_BASE_0 + 0x000000), 0x0F0900);
    MA_OUTW((NPU_ADDR_BASE_0 + 0x0003A8), 0x000001);
    MA_OUTW((NPU_ADDR_BASE_0 + 0x0003A8), 0x000000);
    MA_OUTW((NPU_ADDR_BASE_0 + 0x000000), 0x0F0900);
    MA_OUTW((NPU_ADDR_BASE_0 + 0x000004), 0x7FFFFFFF);
    MA_INW((NPU_ADDR_BASE_0 + 0x000000));
    MA_INW((NPU_ADDR_BASE_0 + 0x000388));
    MA_INW((NPU_ADDR_BASE_0 + 0x000388));
    MA_OUTW((NPU_ADDR_BASE_0 + 0x000104), 0x000000);
    MA_OUTW((NPU_ADDR_BASE_0 + 0x00010C), 0x15A0881);
    MA_OUTW((NPU_ADDR_BASE_0 + 0x00010C), 0x15A0880);
    MA_OUTW((NPU_ADDR_BASE_0 + 0x000000), 0x070B00);
    MA_OUTW((NPU_ADDR_BASE_0 + 0x000000), 0x070900);
    MA_OUTW((NPU_ADDR_BASE_0 + 0x000000), 0x0F0900);
    MA_OUTW((NPU_ADDR_BASE_0 + 0x0003A8), 0x000001);
    MA_OUTW((NPU_ADDR_BASE_0 + 0x0003A8), 0x000000);
    MA_OUTW((NPU_ADDR_BASE_0 + 0x000000), 0x0F0900);
    MA_OUTW((NPU_ADDR_BASE_0 + 0x000004), 0x7FFFFFFF);
    MA_INW((NPU_ADDR_BASE_0 + 0x000000));
    MA_INW((NPU_ADDR_BASE_0 + 0x000388));
    MA_INW((NPU_ADDR_BASE_0 + 0x000388));
    MA_OUTW((NPU_ADDR_BASE_0 + 0x000090), 0x000000);
    MA_OUTW((NPU_ADDR_BASE_0 + 0x000090), 0x000000);

    MA_OUTW((NPU_ADDR_BASE_0 + 0x000000), 0x070900);
    MA_OUTW((NPU_ADDR_BASE_0 + 0x000000), 0x070100);
    MA_OUTW((NPU_ADDR_BASE_0 + 0x0003A8), 0x000002);
    MA_OUTW((NPU_ADDR_BASE_0 + 0x00003C), 0xFFFFFFFF);
    MA_OUTW((NPU_ADDR_BASE_0 + 0x00003C), 0x000000);
    MA_OUTW((NPU_ADDR_BASE_0 + 0x000100), 0x140021);
    MA_OUTW((NPU_ADDR_BASE_0 + 0x00010C), 0x15A0880);
    MA_OUTW((NPU_ADDR_BASE_0 + 0x000090), 0x000000);
    MA_OUTW((NPU_ADDR_BASE_0 + 0x000414), 0x000000);
    MA_OUTW((NPU_ADDR_BASE_0 + 0x000414), 0x000000);
    MA_OUTW((NPU_ADDR_BASE_0 + 0x000388), 0x000001);

    MA_OUTW((NPU_ADDR_BASE_0 + 0x0003B4), 0x5100020);
    MA_OUTW((NPU_ADDR_BASE_0 + 0x000388), 0x000021);

    MA_OUTW((NPU_ADDR_BASE_0 + 0x000654), 0x25005000);
    MA_OUTW((NPU_ADDR_BASE_0 + 0x0003A4), 0x010013);

    
    return 0;
}
int start_core_single_kernel_1(){

    
    MA_OUTW((NPU_ADDR_BASE_1 + 0x000000), 0x070900);
    MA_OUTW((NPU_ADDR_BASE_1 + 0x000104), 0x000000);
    MA_OUTW((NPU_ADDR_BASE_1 + 0x00010C), 0x15A0881);
    MA_OUTW((NPU_ADDR_BASE_1 + 0x00010C), 0x15A0880);
    MA_OUTW((NPU_ADDR_BASE_1 + 0x000000), 0x070B00);
    MA_OUTW((NPU_ADDR_BASE_1 + 0x000000), 0x070900);
    MA_OUTW((NPU_ADDR_BASE_1 + 0x000000), 0x0F0900);
    MA_OUTW((NPU_ADDR_BASE_1 + 0x0003A8), 0x000001);
    MA_OUTW((NPU_ADDR_BASE_1 + 0x0003A8), 0x000000);
    MA_OUTW((NPU_ADDR_BASE_1 + 0x000000), 0x0F0900);
    MA_OUTW((NPU_ADDR_BASE_1 + 0x000004), 0x7FFFFFFF);
    MA_INW((NPU_ADDR_BASE_1 + 0x000000));
    MA_INW((NPU_ADDR_BASE_1 + 0x000388));
    MA_INW((NPU_ADDR_BASE_1 + 0x000388));
    MA_OUTW((NPU_ADDR_BASE_1 + 0x000104), 0x000000);
    MA_OUTW((NPU_ADDR_BASE_1 + 0x00010C), 0x15A0881);
    MA_OUTW((NPU_ADDR_BASE_1 + 0x00010C), 0x15A0880);
    MA_OUTW((NPU_ADDR_BASE_1 + 0x000000), 0x070B00);
    MA_OUTW((NPU_ADDR_BASE_1 + 0x000000), 0x070900);
    MA_OUTW((NPU_ADDR_BASE_1 + 0x000000), 0x0F0900);
    MA_OUTW((NPU_ADDR_BASE_1 + 0x0003A8), 0x000001);
    MA_OUTW((NPU_ADDR_BASE_1 + 0x0003A8), 0x000000);
    MA_OUTW((NPU_ADDR_BASE_1 + 0x000000), 0x0F0900);
    MA_OUTW((NPU_ADDR_BASE_1 + 0x000004), 0x7FFFFFFF);
    MA_INW((NPU_ADDR_BASE_1 + 0x000000));
    MA_INW((NPU_ADDR_BASE_1 + 0x000388));
    MA_INW((NPU_ADDR_BASE_1 + 0x000388));
    MA_OUTW((NPU_ADDR_BASE_1 + 0x000090), 0x000000);
    MA_OUTW((NPU_ADDR_BASE_1 + 0x000090), 0x000000);

    MA_OUTW((NPU_ADDR_BASE_1 + 0x000000), 0x070900);
    MA_OUTW((NPU_ADDR_BASE_1 + 0x000000), 0x070100);
    MA_OUTW((NPU_ADDR_BASE_1 + 0x0003A8), 0x000002);
    MA_OUTW((NPU_ADDR_BASE_1 + 0x00003C), 0xFFFFFFFF);
    MA_OUTW((NPU_ADDR_BASE_1 + 0x00003C), 0x000000);
    MA_OUTW((NPU_ADDR_BASE_1 + 0x000100), 0x140021);
    MA_OUTW((NPU_ADDR_BASE_1 + 0x00010C), 0x15A0880);
    MA_OUTW((NPU_ADDR_BASE_1 + 0x000090), 0x000000);
    MA_OUTW((NPU_ADDR_BASE_1 + 0x000414), 0x000000);
    MA_OUTW((NPU_ADDR_BASE_1 + 0x000414), 0x000000);
    MA_OUTW((NPU_ADDR_BASE_1 + 0x000388), 0x000001);

    MA_OUTW((NPU_ADDR_BASE_1 + 0x0003B4), 0x1200020);
    MA_OUTW((NPU_ADDR_BASE_1 + 0x000388), 0x000021);

    MA_OUTW((NPU_ADDR_BASE_1 + 0x000654), 0x25005000);
    MA_OUTW((NPU_ADDR_BASE_1 + 0x0003A4), 0x010013);

    return 0;
}

int start_ids_2core(int delay_us){
    
    start_core_0();
    start_core_1();
    while(npu_perf_test_get_status(2) == 0){

    }
    MA_OUTW((NPU_ADDR_BASE_0 + 0x000654), 0x259A6030);
    MA_OUTW((NPU_ADDR_BASE_0 + 0x0003A4), 0x01025B);
    udelay(delay_us);
    MA_OUTW((NPU_ADDR_BASE_1 + 0x000654), 0x259A6030);
    MA_OUTW((NPU_ADDR_BASE_1 + 0x0003A4), 0x01025B);
    
    return 1;

}

int start_dual_core_ddr0(int delay_us){
    
    start_core_dual_kernal_0();
    start_core_dual_kernal_1();
    while(npu_perf_test_get_status(2) == 0){

    }
    MA_OUTW((NPU_ADDR_BASE_0 + 0x000654), 0x259A6030);
    MA_OUTW((NPU_ADDR_BASE_0 + 0x0003A4), 0x0115B8);
    udelay(delay_us);
    MA_OUTW((NPU_ADDR_BASE_1 + 0x000654), 0x259A6030);
    MA_OUTW((NPU_ADDR_BASE_1 + 0x0003A4), 0x0115B8);
    return 0;
}

int start_single_core_ddr0(int delay_us){

    start_core_single_kernel_0();
    start_core_single_kernel_1();
    while(npu_perf_test_get_status(2) == 0){

    }
    MA_OUTW((NPU_ADDR_BASE_0 + 0x000654), 0x259A6030);
    MA_OUTW((NPU_ADDR_BASE_0 + 0x0003A4), 0x0115B8);
    udelay(delay_us);

    MA_OUTW((NPU_ADDR_BASE_1 + 0x000654), 0x259A6030);
    MA_OUTW((NPU_ADDR_BASE_1 + 0x0003A4), 0x0115B8);
    return 0;
}

int npu_perf_test_init(void * param){
    
    itcs_module_set_clock(CPU, "vip0", "cpll", 1008000000, false);
    itcs_module_set_clock(CPU, "vip1", "cpll", 1008000000, false);
   
    
    unsigned int s_base0 = 0xc7f00000;
    int ret_value = 0;

    MA_OUTW((s_base0+0x48 ),(0x00));//power isolation // npu0 和 npu1 的上下电保护设置
    ret_value = MA_INW(s_base0+0x48);
    // printf("power isolation register %x\n",ret_value);
    if(ret_value != 0x00){
        printf("power isolation failed\n");
        return -1;
    }
    // printf("power isolation set to low\n");
    MA_OUTW((s_base0+0x4 ),(0xffff)); // clkgate en //npu0 0x147 npu1 0x1aa //bit8 设置npu0和npu1交互时钟
    MA_OUTW((s_base0+0x0 ),(0xff));   //npu0 reset 0x47 npu0 restet 0xaa 高电平有效
   
    // MA_OUTW((s_base0+0x1c),(0x1));  //  clock gated enable
    MA_OUTW((s_base0+0xc ),(0x3));    // bus en
    MA_OUTW((s_base0+0x0 ),(0x0));   // reset release 

      //MA_OUTW((s_base0+0x1c),(0x1));  // reset clock enable 
    ret_value = MA_INW((s_base0+0xc)); 
    // printf("bus value %d\n",ret_value);

    if(SINGLE_BUS == 1 ) {
        if(AFE_MODE == 0 ) {
            // printf("npu yolov5s_640 test start with single bus & afe bypass"); 
        } else {
            // printf("npu yolov5s_640 test start with single bus & afe enable"); 

            // single bus afe enable
            // ret_value=MA_INW(0xC710002c);  // npu0 afe 
            // MA_OUTW(0xC710002c, ret_value & (~(1<<6))); 
            // ret_value=MA_INW(0xc790002c);  // npu1 afe 
            // MA_OUTW(0xC790002c, ret_value & (~(1<<6))); 
        }
    }
    else{
        //afe ratio set
        printf("dual bus set \n");

        MA_OUTW((s_base0+0x30 ),(0x6a));  // set npu0 read bus0:bus1=7:4
        MA_OUTW((s_base0+0x38 ),(0x6a));  // set npu1 read bus0:bus1=7:4
        MA_OUTW((s_base0+0x40 ),(0x101)); // enable npu1/npu0 read dual bus in afe mode

        MA_OUTW((s_base0+0x34 ),(0x36));  // set npu0 write bus0:bus1=4:3
        MA_OUTW((s_base0+0x3c ),(0x36));  // set npu1 write bus0:bus1=4:3
        MA_OUTW((s_base0+0x40 ),(0x1111)); // enable npu1/npu0 write/read dual bus in afe mode
    }
    npu_input_file_batch("yolov5s_id3_2core_DV_data/mem",0,531);
    return 0;
}


int npu_perf_test_start(NPU_PERF_CTL npu_perf_case,int delay_us){
    

    switch (npu_perf_case)
    {
    case YOLOV_IDS_2CORE:
        start_ids_2core(delay_us);
        break;
    case YOLOV_DUAL_CORE_DDR0:
        start_dual_core_ddr0(delay_us);
        break;
    case YOLOV_SINGLE_CORE_DDR0:
        start_single_core_ddr0(delay_us);
        break;
    case YOLOV_DUAL_CORE0_DDR0_EVB:
        yolov5s_init_core0();
        while(get_status_0()==0){

        }
        MA_OUTW((NPU_ADDR_BASE_0 + 0x000654), 0x259A6030);
        MA_OUTW((NPU_ADDR_BASE_0 + 0x0003A4), 0x01025B);
        break;
    case YOLOV_DUAL_CORE1_DDR0_EVB:
        yolov5s_init_core1();
        while(get_status_1()==0){

        }
        MA_OUTW((NPU_ADDR_BASE_1 + 0x000654), 0x259A6030);
        MA_OUTW((NPU_ADDR_BASE_1 + 0x0003A4), 0x01025B);
        break;
    case YOLOV_DUAL_2CORE_DDR0_EVB:
        yolov5s_init_core0();
        yolov5s_init_core1();
        while(npu_perf_test_get_status(2)==0){

        }
        MA_OUTW((NPU_ADDR_BASE_0 + 0x000654), 0x259A6030);
        MA_OUTW((NPU_ADDR_BASE_0 + 0x0003A4), 0x01025B);
        udelay(delay_us);
        MA_OUTW((NPU_ADDR_BASE_1 + 0x000654), 0x259A6030);
        MA_OUTW((NPU_ADDR_BASE_1 + 0x0003A4), 0x01025B);
        // while(npu_perf_test_get_status(2)==0){

        // }
        break;
    default:
        break;
    }
    return 0;
}


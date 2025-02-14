#include<npu.h>

#define ADDR_OFFSET 8
#define MA_OUTW(addr,value) writel((value),(addr))
#define MA_INW(addr) readl(addr)

#define CLKGEN_BASE 0xc2f08000
#define SCLKGEN_BASE 0xd2f08000
#define TEST_NPU_LITE 0

#ifndef LPDDR4 
#define LPDDR4 1
#endif
#ifndef MPU_NUM 
#define MPU_NUM 1 //0 dd0 ,1 ddr ,2 dual ddr define
#endif
#ifndef EXTD_MODE 
#define EXTD_MODE 0
#endif

#ifndef AFE_MODE 
    //#define AFE_MODE 0  // bus0/1 by VIP id
#define AFE_MODE 1  // bus0/1 by afe id
#endif

#define NPU1_EN 0

extern int npu_perf_test_get_status(int id);

extern int npu_perf_test_init(void * param);

extern int npu_perf_test_start(int npu_perf_case,int delay_us);

extern int get_status_0();
#define CORE2 1

#define S1 1
#define S2 1
#define MS 1
#define NN8 1
#define NN16 1
#define NN_W 1
#define NN_R 1
#define K1 1
#define K3 1
#define MT 1
#define NTP 1
#define NTD 1
#define PER 1
#define MMU_ET 1
#define NNM 1
#define IFI 1
#define LS1 1
#define LS2 1
#define LS4 1
#define IBW 1
#define IBM 1
#define DEBUG_NPU 0
#define YOLOV_NEW 0
#define YOLOV_ALGOR 0
#define YOLOV_IDS 0
#define YOLOV_PPU 0
#define YOLOV_CORE 0
#define DAUL_KERNEL

typedef enum{
    NPU_0_IRQ = 0,
    NPU_1_IRQ = 1,
}NPU_IRQ;

typedef enum{
    MPU_0_IRQ = 0,
    MPU_1_IRQ = 1,
}MPU_IRQ;

typedef enum {
    SHARED_COPY = 0,
    SHARED_COPY_R2H,
    TRANSPOSE,
    TENSORADD,
    PERQUANTIZATION,
    MMU_32BIT,
    MAX_OT,
    KERNEL_1,
    KERNEL_3,
    DDR_WRITE,
    DDR_READ,
    CONVOLUTION_INT8,
    CONVOLUTION_INT16,
    EXTENT4GADDR,
    LSTORAGE,
    LSTORAGE_NEW,
    LSTORAGE_4CORE,
    IMAGE_FILTER,
    IMAGE_BLEND_DW,
    IMAGE_BLEND_MMU,
    BW_WRITE,
    BW_READ,
    BW_WRITE_READ,
    MASK_IMAGE,
    NETWORK_LENET,
    NETWORK_YOLOV5,
    PPU_ABSDIFF,
    PPU_WARPAFFINE,
    NETWORK_YOLOV_ALGO,
    NETWORK_YOLOV_PPU,
    NETWORK_YOLOV_CORE2
} NPU_CASE;


#if 0
void soc_dump0(uint64_t src_addr, uint32_t size) { 
    //////////// memory dump test///////
    uint32_t cmd_type ;

    // printf("dump 0x%0lx size 0x%0x\n", src_addr, size);

    cmd_type    = 0x25;    // memory dump with 64 align

    soc_cmd((( src_addr        & 0xffff) << 16) | 0xa5f0);
    soc_cmd((((src_addr >> 16) & 0xffff) << 16) | 0xa5f1);
    soc_cmd((((src_addr >> 32) & 0xffff) << 16) | 0xa5f2);
    soc_cmd((((src_addr >> 48) & 0xffff) << 16) | 0xa5f3);

    soc_cmd((( size            & 0xffff) << 16) | 0xa5fc);
    soc_cmd((((size     >> 16) & 0xffff) << 16) | 0xa5fd);

    soc_cmd((( cmd_type         & 0xffff) << 16) | 0xa5fe);
}

void soc_dump1(uint64_t src_addr, uint32_t size) { 
    //////////// memory dump test///////
    uint32_t cmd_type ;

    // printf("dump 0x%0lx size 0x%0x\n", src_addr, size);

    cmd_type    = 0x24;    // memory dump with 64 align

    soc_cmd((( src_addr        & 0xffff) << 16) | 0xa5f0);
    soc_cmd((((src_addr >> 16) & 0xffff) << 16) | 0xa5f1);
    soc_cmd((((src_addr >> 32) & 0xffff) << 16) | 0xa5f2);
    soc_cmd((((src_addr >> 48) & 0xffff) << 16) | 0xa5f3);

    soc_cmd((( size            & 0xffff) << 16) | 0xa5fc);
    soc_cmd((((size     >> 16) & 0xffff) << 16) | 0xa5fd);

    soc_cmd((( cmd_type         & 0xffff) << 16) | 0xa5fe);
}
#endif

 int64_t clk_fre[][2] = {
        {1603200000,801600000},
        {1713600000,856800000},
        {1800000000,900000000},
        {1920000000,960000000},
        {2016000000,1008000000},
        {2112000000,1056000000},

        {2208000000,1104000000},
        {2304000000,1152000000},
        {2400000000,1200000000},
        {2544000000,1272000000},
        {1308000000,1308000000},
    };

int64_t power_vol[][2] = {
        {800,800},
        {850,800},
        {900,900},
        {950,900},
        {1000,1000},
};

int npu_init_config(){
    unsigned int s_base0 = 0xc7f00000;
    int ret_value = 0;
   
    // power_up_set(1);

    // MA_OUTW(0xc3010000+0x0,0x1);//enable pmu module
    // MA_OUTW(0xc3010000+0x4,0x37100);//
    // MA_OUTW(0xc3010000+0x8,0x1); //endle interrup
    // MA_OUTW(0xc3010000+0xc,0);

    MA_OUTW((s_base0+0x48 ),(0x00));//power isolation // npu0 和 npu1 的上下电保护设置
    ret_value = MA_INW(s_base0+0x48);
    printf("power isolation register %x\n",ret_value);
    if(ret_value != 0x00){
        printf("power isolation failed\n");
        return -1;
    }
    printf("power isolation set to low\n");
    MA_OUTW((s_base0+0x4 ),(0xffff)); // clkgate en //npu0 0x147 npu1 0x1aa //bit8 设置npu0和npu1交互时钟
    MA_OUTW((s_base0+0x0 ),(0xff));   //npu0 reset 0x47 npu0 restet 0xaa 高电平有效
   
    // MA_OUTW((s_base0+0x1c),(0x1));  //  clock gated enable
    MA_OUTW((s_base0+0xc ),(0x3));    // bus en
    MA_OUTW((s_base0+0x0 ),(0x0));   // reset release 

      //MA_OUTW((s_base0+0x1c),(0x1));  // reset clock enable 
    ret_value = MA_INW((s_base0+0xc)); 
    printf("bus value %d\n",ret_value);


    
  
    // printf("interrup reg %x\n",MA_INW(0xc3010000+0xc));

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
        // MA_OUTW((s_base0+0x30 ),(0x3));   // set npu0 rid 3 to axi1 set read bus ratio (npu1 0x38)
        // // MA_OUTW((s_base0+0x400+0x34 ),(0x3));//npu0 set write bus ratio (npu 0x3c)
        // MA_OUTW((s_base0+0x40 ),(0x1));   // enable npu0 rid 3 to axi1
        // MA_OUTW((s_base0+0x44 ),(0x1));   // vip id mode

        // printf("npu yolov5s_640 test start with afe bypass!\n"); 

        //npu afe must set to bypass mode(default mode)
        // afe mode
        // MA_OUTW((s_base0+0x30 ),(0x6a));  // set npu0 read bus0:bus1=8:3
        // MA_OUTW((s_base0+0x38 ),(0x6a));
        // MA_OUTW((s_base0+0x40 ),(0x101));   // enable npu0 read dual bus in afe mode
        printf("dual bus set \n");

        MA_OUTW((s_base0+0x30 ),(0x6a));  // set npu0 read bus0:bus1=7:4
        MA_OUTW((s_base0+0x38 ),(0x6a));  // set npu1 read bus0:bus1=7:4
        MA_OUTW((s_base0+0x40 ),(0x101)); // enable npu1/npu0 read dual bus in afe mode

        MA_OUTW((s_base0+0x34 ),(0x36));  // set npu0 write bus0:bus1=4:3
        MA_OUTW((s_base0+0x3c ),(0x36));  // set npu1 write bus0:bus1=4:3
        MA_OUTW((s_base0+0x40 ),(0x1111)); // enable npu1/npu0 write/read dual bus in afe mode
        //MA_OUTW((s_base0+i*0x400+0x34 ),(0x12));  // set npu0 write bus0:bus1=2:1
        //rd_val = MA_INW((s_base0+i*0x400+0x40)); 
        //MA_OUTW((s_base0+i*0x400+0x40 ),(0x10 | rd_val));   // enable npu0 write dual bus in afe mode

        // dual bus afe enable
        // ret_value=MA_INW(0xC710002c);  // npu0 afe 
        // MA_OUTW(0xC710002c, ret_value & (~(1<<6))); 
        // ret_value=MA_INW(0xc790002c);  // npu1 afe 
        // MA_OUTW(0xC790002c, ret_value & (~(1<<6))); 

        // printf("npu yolov5s_640 test start with afe mode!\n"); 
    }
#if EVB_DEBUG_LOG
    unsigned int npu_base0 = 0xc7000000;
    unsigned int npu_base1 = 0xc7800000;
    ret_value=MA_INW(npu_base0 + 0x100);//power ctl
    printf("npu0 power ctl id %x\n",ret_value);
    ret_value=MA_INW(npu_base1 + 0x100);//power ctl
    printf("npu1 power ctl id %x\n",ret_value);

    ret_value=MA_INW(npu_base0 + 0x20);//product id
    printf("npu0 id %x\n",ret_value);
    ret_value=MA_INW(npu_base1 + 0x20);//product id
    printf("npu1 id %x\n",ret_value);  

    ret_value=MA_INW(npu_base0 + 0x24);//chip id
    printf("npu0 chip id %x\n",ret_value); 
    ret_value=MA_INW(npu_base1 + 0x24);//chip id
    printf("npu1 chip id %x\n",ret_value);

    ret_value=MA_INW(npu_base0 + 0x28);//chip data
    printf("npu0 chip data %x\n",ret_value); 
    ret_value=MA_INW(npu_base1 + 0x28);//chip data
    printf("npu1 chip data %x\n",ret_value);

    ret_value=MA_INW(npu_base0 + 0x30);//chip cid
    printf("npu0 chip cid %x\n",ret_value); 
    ret_value=MA_INW(npu_base1 + 0x30);//chip cid
    printf("npu1 chip cid %x\n",ret_value);  

    ret_value=MA_INW(npu_base0 + 0xa8);//product id
    printf("npu0 product id %x\n",ret_value);
    ret_value=MA_INW(npu_base1 + 0xa8);//product id
    printf("npu1 product id %x\n",ret_value);  


    ret_value=MA_INW(npu_base0 + 0x04);//product id
    printf("npu0 idle %x\n",ret_value);  
#endif
    return 0;
}

int npu_close_config(){
    unsigned int s_base0 = 0xc7f00000;
    int ret_value = 0;
    MA_OUTW((s_base0+0x48 ),(0x3));//power isolation
    ret_value = MA_INW(s_base0+0x48);
    printf("power isolation register %x",ret_value);
    if(ret_value != 0x3){
        printf("power isolation set failed\n");
        return -1;
    }
    MA_OUTW((s_base0+0x8 ),(0x0));//power down
    printf("power isolation set to high\n");
    return 0;
}

int cul_ddr_ratio(int cycle){


    //get interupt status
    // printf("------ddr ratio--- \n");
    // printf("enable reg %x,%x, %x\n",MA_INW(0xc3010000+0x8),MA_INW(0xc3010000+0x0),MA_INW(0xc3010000+0x4));
    // printf("interrup reg %x\n",MA_INW(0xc3010000+0xc));
    int rel = MA_INW(0xc3010000+0xc);
    while(MA_INW(0xc3010000)==0x1){
        unsigned int rfsh_cnt = MA_INW(0xc3010000+0xe0);// rfsh_cnt
        unsigned int pchr_cnt = MA_INW(0xc3010000+0xe4);//pchr_cnt 
        unsigned int actr_cnt = MA_INW(0xc3010000+0xe8);//actvcr_cnt
        unsigned int wr_cnt = MA_INW(0xc3010000+0xf0);//wcr_cnt
        unsigned int rd_cnt = MA_INW(0xc3010000+0xe4);//rd_cnt
        printf("rfsh_cnt %d\n",rfsh_cnt);
        printf("pchr_cnt %d\n",pchr_cnt);
        printf("actvcr_cnt %d\n",actr_cnt);
        printf("wcr_cnt %d\n",wr_cnt);
        printf("rd_cnt %d\n",rd_cnt);
        int ratio = 16;
        unsigned int time_cnt = ratio * 0x3710613;
        ratio = 64;
        unsigned long total_ddr_access  =  (wr_cnt + rd_cnt)*ratio;

        // float ddr_rate = 0.0;
        printf("time_cnt %d,total_ddr_access %d\n",time_cnt,total_ddr_access);
        return 0;
    }
    MA_OUTW(0xc3010000+0xc,0x1);
    printf("read ddr ratio failed\n");
    return -1;

}

int set_npu_clock(){
    itcs_module_set_clock(CPU, "vip0", "cpll", 8000000, false);
    itcs_module_set_clock(CPU, "vip1", "cpll", 8000000, false);

   
    #if DEBUG_NPU
    printf("npu system START!\n"); 
    #endif
    // unsigned int  s_base0 = 0xc7f00000;
   
    // int i = 0;

    // MA_OUTW((s_base0+i*0x400+0x0 ),(0xff));   // reset release 
    // MA_OUTW((s_base0+i*0x400+0x8 ),(0x1));   // power up
        
    // MA_OUTW((s_base0+i*0x400+0x8 ),(0x1));   // power up & iso disable
    
    // //MA_OUTW((s_base0+i*0x400+0x1c),(0x1));  // reset clock enable 

    // MA_OUTW((s_base0+i*0x400+0x4 ),(0xff)); // clkgate en
    // MA_OUTW((s_base0+i*0x400+0xc ),(0x3));    // bus en
   

    // int rd_val=MA_INW((s_base0+i*0x400+0xc));   // check bus enable register
        
    // MA_OUTW((s_base0+i*0x400+0x0 ),(0x0));   // reset release 

    // MA_OUTW((s_base0+i*0x400+0x30 ),(0x3));   // set npu0 rid 3 to axil
    // MA_OUTW((s_base0+i*0x400+0x40 ),(0x1));   // enable npu0 rid 3 to axil
    // rd_val = MA_INW(0xc710002c);// npu0 afe
    // MA_OUTW(0xc710002c,rd_val & (~(1<<6)) );   // reset release
    // int rd_val;

    unsigned int s_base0 = 0xc7f00000;
    int i = 0;    

    MA_OUTW((s_base0+i*0x400+0x0 ),(0xff));   // reset release 
    MA_OUTW((s_base0+i*0x400+0x8 ),(0x1));   // power up
        
    // MA_OUTW((s_base0+i*0x400+0x8 ),(0x1));   // power up & iso disable
    //隔离电流
    MA_OUTW((s_base0+i*0x400+0x48 ),(0x3)); 
    //MA_OUTW((s_base0+i*0x400+0x1c),(0x1));  // reset clock enable 

    MA_OUTW((s_base0+i*0x400+0x4 ),(0xffff)); // clkgate en
    MA_OUTW((s_base0+i*0x400+0xc ),(0x3));    // bus en
    MA_OUTW((s_base0+i*0x400+0x18),(0x1));    // io in en

    // rd_val = MA_INW((s_base0+i*0x400+0xc));   // check bus enable register
        
    MA_OUTW((s_base0+i*0x400+0x0 ),(0x0));   // reset release 

    //默认单bus
    if(SINGLE_BUS == 1 ) {
        if(AFE_MODE == 0 ) {
            // printf("npu yolov5s_640 test start with single bus & afe bypass"); 
        } else {
            // printf("npu yolov5s_640 test start with single bus & afe enable"); 

            // single bus afe enable
            // rd_val=MA_INW(0xC710002c);  // npu0 afe 
            // MA_OUTW(0xC710002c, rd_val & (~(1<<6))); 
            // rd_val=MA_INW(0xc790002c);  // npu1 afe 
            // MA_OUTW(0xC790002c, rd_val & (~(1<<6))); 
        }
    }
    else if(AFE_MODE == 0 ) {
        MA_OUTW((s_base0+i*0x400+0x30 ),(0x3));   // set npu0 rid 3 to axi1 //高位为总的数据，低位为bus0传的数据


        MA_OUTW((s_base0+i*0x400+0x40 ),(0x1));   // enable npu0 rid 3 to axi1
        MA_OUTW((s_base0+i*0x400+0x44 ),(0x1));   // vip id mode

        // printf("npu yolov5s_640 test start with afe bypass!\n"); 

        //npu afe must set to bypass mode(default mode)
    } else {    // afe mode
        MA_OUTW((s_base0+i*0x400+0x30 ),(0x6a));  // set npu0 read bus0:bus1=8:3
        MA_OUTW((s_base0+i*0x400+0x38 ),(0x6a));
        MA_OUTW((s_base0+i*0x400+0x40 ),(0x101));   // enable npu0 read dual bus in afe mode
    
        //MA_OUTW((s_base0+i*0x400+0x34 ),(0x12));  // set npu0 write bus0:bus1=2:1
        //rd_val = MA_INW((s_base0+i*0x400+0x40)); 
        //MA_OUTW((s_base0+i*0x400+0x40 ),(0x10 | rd_val));   // enable npu0 write dual bus in afe mode

        // // dual bus afe enable //默认开启 
        // rd_val=MA_INW(0xC710002c);  // npu0 afe 
        // MA_OUTW(0xC710002c, rd_val & (~(1<<6))); 
        // rd_val=MA_INW(0xc790002c);  // npu1 afe 
        // MA_OUTW(0xC790002c, rd_val & (~(1<<6))); 

        // printf("npu yolov5s_640 test start with afe mode!\n"); 
    }

    return 0;
}

/*初始化，成功返回0，失败返回-1*/

/*npu开始工作，count=0 first_phase count = 1 second_phase，总是返回0*/

#if 0
int Test_proformence(void){
    npu_perf_test_init(NULL);
    npu_perf_test_start(0);
    
    while(npu_perf_test_get_status(0) == 0 ){
        //printf("first phase running\n");
    }
    // npu_perf_test_start(1);
    // while(npu_perf_test_get_status(0) == 0 ){
    //     //printf("second phase running\n");
    // }
    itcs_dcache_flush();
    int rd_val = MA_INW((0xc7000000 + 0x000078));
    printf("0x000078 = %d \n" , rd_val);
    printf("NPU TEST FINISH!\n"); 
    int fd = open("yolov5_new/result0.bin",O_RDONLY);
    printf("%x\n",*((int*)faddr(fd)));
    int ret = memcmp((char*)0x1025fe000,(char*)(faddr(fd))+ADDR_OFFSET,flen(fd)-ADDR_OFFSET);
    close(fd);
    fd = open("yolov5_new/result1.bin",O_RDONLY);
    printf("%x\n",*((int*)faddr(fd)));
    ret = memcmp((char*)0x102662000,(char*)(faddr(fd))+ADDR_OFFSET,flen(fd)-ADDR_OFFSET);
    close(fd);

    fd = open("yolov5_new/result2.bin",O_RDONLY);
    printf("%x\n",*((int*)faddr(fd)));
    ret = memcmp((char*)0x10267b000,(char*)(faddr(fd))+ADDR_OFFSET,flen(fd)-ADDR_OFFSET);
    close(fd);
    return ret;
}
#endif
int regist_init(){
    // set_npu_clock();
    
#if 1
    unsigned int base0 = 0xC7000000;
    unsigned int base1 = 0xC7800000;
    MA_OUTW((base0 + 0x000000), 0x070900);
    MA_OUTW((base0 + 0x000104), 0x000000);
    MA_OUTW((base0 + 0x00010C), 0x15A0881);
    MA_OUTW((base0 + 0x00010C), 0x15A0880);
    MA_OUTW((base0 + 0x000000), 0x070B00);
    MA_OUTW((base0 + 0x000000), 0x070900);
    MA_OUTW((base0 + 0x000000), 0x0F0900);
    MA_OUTW((base0 + 0x0003A8), 0x000001);
    MA_OUTW((base0 + 0x0003A8), 0x000000);
    MA_OUTW((base0 + 0x000000), 0x0F0900);
    MA_OUTW((base0 + 0x000000), 0x070900);
    MA_INW((base0 + 0x000004));
    MA_INW((base0 + 0x000000));
    MA_INW((base0 + 0x000388));
    MA_OUTW((base0 + 0x000104), 0x000000);
    MA_OUTW((base0 + 0x00010C), 0x15A0881);
    MA_OUTW((base0 + 0x00010C), 0x15A0880);
    MA_OUTW((base0 + 0x000000), 0x070B00);
    MA_OUTW((base0 + 0x000000), 0x070900);
    MA_OUTW((base0 + 0x000000), 0x0F0900);
    MA_OUTW((base0 + 0x0003A8), 0x000001);
    MA_OUTW((base0 + 0x0003A8), 0x000000);
    MA_OUTW((base0 + 0x000000), 0x0F0900);
    MA_OUTW((base0 + 0x000000), 0x070900);
    MA_INW((base0 + 0x000004));
    MA_INW((base0 + 0x000000));
    MA_INW((base0 + 0x000388));
    MA_OUTW((base0 + 0x00055C), 0xFFFFFF);
    MA_OUTW((base0 + 0x000090), 0x000000);
    MA_OUTW((base1 + 0x000000), 0x070900);
    MA_OUTW((base1 + 0x000104), 0x000000);
    MA_OUTW((base1 + 0x00010C), 0x15A0881);
    MA_OUTW((base1 + 0x00010C), 0x15A0880);
    MA_OUTW((base1 + 0x000000), 0x070B00);
    MA_OUTW((base1 + 0x000000), 0x070900);
    MA_OUTW((base1 + 0x000000), 0x0F0900);
    MA_OUTW((base1 + 0x0003A8), 0x000001);
    MA_OUTW((base1 + 0x0003A8), 0x000000);
    MA_OUTW((base1 + 0x000000), 0x0F0900);
    MA_OUTW((base1 + 0x000000), 0x070900);
    MA_INW((base1 + 0x000004));
    MA_INW((base1 + 0x000000));
    MA_INW((base1 + 0x000388));
    MA_OUTW((base1 + 0x000104), 0x000000);
    MA_OUTW((base1 + 0x00010C), 0x15A0881);
    MA_OUTW((base1 + 0x00010C), 0x15A0880);
    MA_OUTW((base1 + 0x000000), 0x070B00);
    MA_OUTW((base1 + 0x000000), 0x070900);
    MA_OUTW((base1 + 0x000000), 0x0F0900);
    MA_OUTW((base1 + 0x0003A8), 0x000001);
    MA_OUTW((base1 + 0x0003A8), 0x000000);
    MA_OUTW((base1 + 0x000000), 0x0F0900);
    MA_OUTW((base1 + 0x000000), 0x070900);
    MA_INW((base1 + 0x000004));
    MA_INW((base1 + 0x000000));
    MA_INW((base1 + 0x000388));
    MA_OUTW((base1 + 0x00055C), 0xFFFFFF);
    MA_OUTW((base1 + 0x000090), 0x000000);
    MA_OUTW((base0 + 0x000000), 0x070900);
    MA_OUTW((base0 + 0x000000), 0x070100);
    MA_OUTW((base0 + 0x0003A8), 0x000002);
    MA_OUTW((base0 + 0x00003C), 0xFFFFFFFF);
    MA_OUTW((base0 + 0x00003C), 0x000000);
    MA_OUTW((base0 + 0x000100), 0x140021);
    MA_OUTW((base0 + 0x000104), 0x000000);
    MA_OUTW((base0 + 0x00010C), 0x15A0880);
    MA_OUTW((base0 + 0x000414), 0x000000);
    MA_OUTW((base0 + 0x000014), 0xFFFFFFFF);
    MA_OUTW((base1 + 0x000000), 0x070900);
    MA_OUTW((base1 + 0x000000), 0x070100);
    MA_OUTW((base1 + 0x0003A8), 0x000002);
    MA_OUTW((base1 + 0x00003C), 0xFFFFFFFF);
    MA_OUTW((base1 + 0x00003C), 0x000000);
    MA_OUTW((base1 + 0x000100), 0x140021);
    MA_OUTW((base1 + 0x000104), 0x000000);
    MA_OUTW((base1 + 0x00010C), 0x15A0880);
    MA_OUTW((base1 + 0x000414), 0x000000);
    MA_OUTW((base1 + 0x000014), 0xFFFFFFFF);
#endif
#if 0
    unsigned int base0 = 0xC7000000;
    unsigned int base1 = 0xC7800000;
    #if DEBUG_NPU
    printf("NPU TEST START!\n");
    #endif 
     // npu_test_code start
    MA_OUTW((base0 + 0x000000), 0x070900);
    MA_OUTW((base0 + 0x000104), 0x000000);
    MA_OUTW((base0 + 0x00010C), 0x15A0881);
    MA_OUTW((base0 + 0x00010C), 0x15A0880);
    MA_OUTW((base0 + 0x000000), 0x070B00);
    MA_OUTW((base0 + 0x000000), 0x070900);
    MA_OUTW((base0 + 0x000000), 0x0F0900);
    MA_OUTW((base0 + 0x0003A8), 0x000001);
    MA_OUTW((base0 + 0x0003A8), 0x000000);
    MA_OUTW((base0 + 0x000000), 0x0F0900);
    MA_OUTW((base0 + 0x000000), 0x070900);
    MA_INW((base0 + 0x000004));
    MA_INW((base0 + 0x000000));
    MA_INW((base0 + 0x000388));
    MA_OUTW((base0 + 0x000104), 0x000000);
    MA_OUTW((base0 + 0x00010C), 0x15A0881);
    MA_OUTW((base0 + 0x00010C), 0x15A0880);
    MA_OUTW((base0 + 0x000000), 0x070B00);
    MA_OUTW((base0 + 0x000000), 0x070900);
    MA_OUTW((base0 + 0x000000), 0x0F0900);
    MA_OUTW((base0 + 0x0003A8), 0x000001);
    MA_OUTW((base0 + 0x0003A8), 0x000000);
    MA_OUTW((base0 + 0x000000), 0x0F0900);
    MA_OUTW((base0 + 0x000000), 0x070900);
    MA_INW((base0 + 0x000004));
    MA_INW((base0 + 0x000000));
    MA_INW((base0 + 0x000388));
    MA_OUTW((base0 + 0x00055C), 0xFFFFFF);
    MA_OUTW((base0 + 0x000090), 0x000000);
    MA_OUTW((base1 + 0x000000), 0x070900);
    MA_OUTW((base1 + 0x000104), 0x000000);
    MA_OUTW((base1 + 0x00010C), 0x15A0881);
    MA_OUTW((base1 + 0x00010C), 0x15A0880);
    MA_OUTW((base1 + 0x000000), 0x070B00);
    MA_OUTW((base1 + 0x000000), 0x070900);
    MA_OUTW((base1 + 0x000000), 0x0F0900);
    MA_OUTW((base1 + 0x0003A8), 0x000001);
    MA_OUTW((base1 + 0x0003A8), 0x000000);
    MA_OUTW((base1 + 0x000000), 0x0F0900);
    MA_OUTW((base1 + 0x000000), 0x070900);
    MA_INW((base1 + 0x000004));
    MA_INW((base1 + 0x000000));
    MA_INW((base1 + 0x000388));
    MA_OUTW((base1 + 0x000104), 0x000000);
    MA_OUTW((base1 + 0x00010C), 0x15A0881);
    MA_OUTW((base1 + 0x00010C), 0x15A0880);
    MA_OUTW((base1 + 0x000000), 0x070B00);
    MA_OUTW((base1 + 0x000000), 0x070900);
    MA_OUTW((base1 + 0x000000), 0x0F0900);
    MA_OUTW((base1 + 0x0003A8), 0x000001);
    MA_OUTW((base1 + 0x0003A8), 0x000000);
    MA_OUTW((base1 + 0x000000), 0x0F0900);
    MA_OUTW((base1 + 0x000000), 0x070900);
    MA_INW((base1 + 0x000004));
    MA_INW((base1 + 0x000000));
    MA_INW((base1 + 0x000388));
    MA_OUTW((base1 + 0x00055C), 0xFFFFFF);
    MA_OUTW((base1 + 0x000090), 0x000000);
    MA_OUTW((base0 + 0x000000), 0x070900);
    MA_OUTW((base0 + 0x000000), 0x070100);
    MA_OUTW((base0 + 0x0003A8), 0x000002);
    MA_OUTW((base0 + 0x00003C), 0xFFFFFFFF);
    MA_OUTW((base0 + 0x00003C), 0x000000);
    MA_OUTW((base0 + 0x000100), 0x140021);
    MA_OUTW((base0 + 0x000104), 0x000000);
    MA_OUTW((base0 + 0x00010C), 0x15A0880);
    MA_OUTW((base0 + 0x000414), 0x000000);
    MA_OUTW((base0 + 0x000014), 0xFFFFFFFF);
    MA_OUTW((base1 + 0x000000), 0x070900);
    MA_OUTW((base1 + 0x000000), 0x070100);
    MA_OUTW((base1 + 0x0003A8), 0x000002);
    MA_OUTW((base1 + 0x00003C), 0xFFFFFFFF);
    MA_OUTW((base1 + 0x00003C), 0x000000);
    MA_OUTW((base1 + 0x000100), 0x140021);
    MA_OUTW((base1 + 0x000104), 0x000000);
    MA_OUTW((base1 + 0x00010C), 0x15A0880);
    MA_OUTW((base1 + 0x000414), 0x000000);
    MA_OUTW((base1 + 0x000014), 0xFFFFFFFF);
   
#endif

    return 0;
}

volatile int is_npu0_finish = 0;
volatile int is_npu1_finish = 0;

int NPU0_irq_handler(int irq, void *args){
    unsigned int base0 = 0xc7000000;
    unsigned int flag0 = MA_INW(base0+0x04);
    printf("INTR_NPU0 = %x\n",MA_INW(base0+0x10));
    if(flag0 == 0x7fffffff){
        is_npu0_finish = 1;
    }
    return 0;
}

int NPU1_irq_handler(int irq, void *args){
    unsigned int base1 = 0xc7800000;
    unsigned int flag1 = MA_INW(base1+0x04);
    printf("INTR_NPU1 = %x\n",MA_INW(base1+0x10));
    
    if(flag1 == 0x7fffffff){
        is_npu1_finish = 1;
    }
    return 0;
}
int request_npu_irq(NPU_IRQ id){
    if(id == NPU_0_IRQ){
        request_irq(C_NPU0_IRQn, NPU0_irq_handler,
				  "npu0_irq", NULL);
    }else if(id == NPU_1_IRQ){
        request_irq(C_NPU1_IRQn, NPU1_irq_handler,
				  "npu1_irq", NULL);
    }else{
        printf("not irq_id match\n");
    }
    return 0;
}

int MPU0_irq_handler(int irq, void *args){
   
   
    cul_ddr_ratio(0);
    return 0;
}

int MPU1_irq_handler(int irq, void *args){
    unsigned int base1 = 0xc7800000;
    unsigned int flag1 = MA_INW(base1+0x04);
    printf("INTR_MPU1 = %x\n",MA_INW(base1+0x10));
    
    if(flag1 == 0x7fffffff){
        is_npu1_finish = 1;
    }
    return 0;
}

int request_mpu_irq(MPU_IRQ id){
    if(id == MPU_0_IRQ){
        request_irq(C_MPU0_IRQn, MPU0_irq_handler,
				  "mpu0_irq", NULL);
    }else if(id == MPU_1_IRQ){
        request_irq(C_MPU1_IRQn, MPU1_irq_handler,
				  "mpu1_irq", NULL);
    }else{
        printf("not irq_id match\n");
    }
    return 0;
}

int PrintBuf(char *buf,int len){
    #if 0
    return 0;
    #endif
    printf("ADDR =%p\n",buf);
    for(int i =0;i<len;i++){
        printf("%02x ",buf[i]);
        if(i%32==0){
            printf("\n");
        }
    }
    printf("\n");
    return 0;
}  

void clock_config(){
    uint32_t  i,rd_val;
    unsigned int s_base; 
    //PLLOUT = REF / DIVR_VAL * 4 * DIVF_VAL / DIVQ_VAL
    //VCO    = REF / DIVR_VAL * 4 * DIVF_VAL (1200 ~ 6000 MHz)
    
    printf("CPU PLL Test!\n"); 
    // APLL =  MHZ
    MA_OUTW(CLKGEN_ALDCFG   , 3);     // load parameter, newdiv[2], load[1], oute[0]
    MA_OUTW(CLKGEN_AEN      , 1);     // pll enable
    rd_val = 0;
    while(rd_val != 0x1) {
        rd_val = MA_INW(CLKGEN_ALOCK) & 0x1;    //check apll lock
    }
    MA_OUTW(CLKGEN_ASEL, 2);     // pll source sel and output sel
////////////////////////////////////////////////////////////////////////////////////////////////////// 

    // DPLL = 1500 MHZ
    MA_OUTW(CLKGEN_DLDCFG   , 3);     // load parameter, newdiv[2], load[1], oute[0]
    MA_OUTW(CLKGEN_DEN      , 1);     // pll enable
    // EPLL = 2016 MHZ
    MA_OUTW(CLKGEN_ELDCFG   , 3);     // load parameter, newdiv[2], load[1], oute[0]
    MA_OUTW(CLKGEN_EEN      , 1);     // pll enable
    // VPLL = 2112 MHZ
    MA_OUTW(CLKGEN_VLDCFG   , 3);     // load parameter, newdiv[2], load[1], oute[0]
    MA_OUTW(CLKGEN_VEN      , 1);     // pll enable

    rd_val = 0;
    while(rd_val != 0x1) {
        rd_val = MA_INW(CLKGEN_DLOCK) & 0x1;    //check dpll lock
    }
    rd_val = 0;
    while(rd_val != 0x1) {
        rd_val = MA_INW(CLKGEN_ELOCK) & 0x1;    //check epll lock
    }
    rd_val = 0;
    while(rd_val != 0x1) {
        rd_val = MA_INW(CLKGEN_VLOCK) & 0x1;    //check vpll lock
    }

    MA_OUTW(CLKGEN_DSEL, 2);     // pll source sel and output sel
    MA_OUTW(CLKGEN_ESEL, 2);     // pll source sel and output sel
    MA_OUTW(CLKGEN_VSEL, 2);     // pll source sel and output sel

////////////////////////////////////////////////////////////////////////////////////////////////////// 
    //PLLOUT = REF / DIVR_VAL * 4 * DIVF_VAL / DIVQ_VAL
    //VCO    = REF / DIVR_VAL * 4 * DIVF_VAL (1200 ~ 6000 MHz)
    printf("SAP PLL Test!\n"); 
////////////////////////////////////////////////////////////////////////////////////////////////////// 
//clk enable


    MA_OUTW(CLKGEN_BASE+0x100, 2);    // axi clk 
    MA_OUTW(CLKGEN_BASE+0x104, 7);    // set ratio
    MA_OUTW(CLKGEN_BASE+0x10c, 0);    // load enable

    MA_OUTW(CLKGEN_BASE+0x190, 2);    // ahb clk 
    MA_OUTW(CLKGEN_BASE+0x194, 7);    // set ratio
    MA_OUTW(CLKGEN_BASE+0x19c, 0);    // load enable


    MA_OUTW(CLKGEN_BASE+0x2d0, 2);    // core clk
    MA_OUTW(CLKGEN_BASE+0x2d4, 7);    // set ratio
    MA_OUTW(CLKGEN_BASE+0x2dc, 0);    // load enable

    
    s_base = 0xc7f00000;
    i = 0;    
    MA_OUTW((s_base+i*0x400+0x20 ),(0x1));
    MA_OUTW((s_base+i*0x400+0x0 ),(0xff));   // reset release 
    MA_OUTW((s_base+i*0x400+0x8 ),(0x1));   // power up
        
    MA_OUTW((s_base+i*0x400+0x8 ),(0x1));   // power up & iso disable
    
    //MA_OUTW((s_base+i*0x400+0x1c),(0x1));  // reset clock enable 

    MA_OUTW((s_base+i*0x400+0x4 ),(0xff)); // clkgate en
    MA_OUTW((s_base+i*0x400+0xc ),(0x3));    // bus en
    MA_OUTW((s_base+i*0x400+0x18),(0x1));    // io in en

    rd_val = MA_INW((s_base+i*0x400+0xc));   // check bus enable register
        
    MA_OUTW((s_base+i*0x400+0x0 ),(0x0));   // reset release 

//    sysm_address = 0xc6f00000;
//    i = 0;
//    MA_OUTW(sysm_address+i*0x100+0x8,0x1);                // power up
//    rd_val = 0;
//    while(!rd_val) {
//       rd_val = MA_INW(sysm_address+i*0x100+0x8) & 0x10;  // polling power-ack 
//    }
//    MA_OUTW(sysm_address+i*0x100+0x8,0x1);		// power up & iso disable
    //MA_OUTW(sysm_address+i*0x100+0x1c,0x1); 		// reset clock enable 
//    MA_OUTW(sysm_address+i*0x100+0x4,0xffff);		// clkgate en
//    MA_OUTW(sysm_address+i*0x100+0xc,0x3);   		// bus en
//    MA_OUTW(sysm_address+i*0x100+0x18,0x1);   		// io in en

//    rd_val = MA_INW(sysm_address+i*0x100+0xc);   		// check bus enable register
//    if(rd_val != 0x3) {
//       printf("apb sysm read/write error\n");
//    }
//    MA_OUTW(sysm_address+i*0x100+0x0,0x0);   		// reset release 
    //MA_OUTW(sysm_address+i*0x100+0x1c,0x0);   		// reset clock disable 
    


}

int close_file_node(int*fd,int count){
    for(int i=0;i<count;i++){ 
        close(fd[i]);
        fd[i] = 0;
    }
    return 0;
}

int open_file_node(char* file_name[],unsigned long int*addrs,int* fd,int count){
    uintptr_t addr = 0;
    for(int i=0;i<count;i++){
        fd[i] = open(file_name[i], O_RDONLY);
        if(fd[i]==-1){
            close_file_node(fd,i);
            printf("%s\n",file_name[i]);
            printf("fd: %d\n", fd[i]);
            return -1;
        }
        addr = faddr(fd[i]);
        addrs[i]=addr;
    #if 0
        printf("fd: %d\n", fd[i]);
        printf("addr = %llx\n",addr);
    #endif
    }
    return 0;
}
#if 0
int yolov5_ppu(){

    // npu_perf_test_init(NULL);
    npu_perf_test_start(0);
    
    while(npu_perf_test_get_status(0) == 0 ){
        //printf("first phase running\n");
    }
    // npu_perf_test_start(1);
    // while(npu_perf_test_get_status(0) == 0 ){
    //     //printf("second phase running\n");
    // }
    itcs_dcache_flush();
    int rd_val = MA_INW((0xc7000000 + 0x000078));
    printf("0x000078 = %d \n" , rd_val);
    printf("NPU TEST FINISH!\n"); 
   
    char file_name[32] ="npu/ppu_yolov5s_DV/result\0";
    char temp[64] = {0};
    char tail[8] = ".bin\0";
    int fd = 0,ret=0;
    unsigned long  p ,result_addr= 0;

    for(int i=0; i < 2; i++){
        sprintf(temp, "%s%d%s", file_name,i,tail);
        fd = open(temp,O_RDONLY);
        p = faddr(fd);
        memcpy(&result_addr, (void*)p, ADDR_OFFSET);
        // printf("%x\n",result_addr);
        ret = memcmp((char*)result_addr,(char*)(faddr(fd))+ADDR_OFFSET,flen(fd)-ADDR_OFFSET);
        close(fd);
    }
    return ret;
   
}

int NetworkYolov5_3_21_algorithm(){

    npu_perf_test_init(NULL);
    npu_perf_test_start(0);
    
    while(npu_perf_test_get_status(0) == 0 ){
        //printf("first phase running\n");
    }
    // npu_perf_test_start(1);
    // while(npu_perf_test_get_status(0) == 0 ){
    //     //printf("second phase running\n");
    // }
    itcs_dcache_flush();
    //result
    int rd_val = MA_INW((0xc7000000 + 0x000078));
    printf("0x000078 = %d \n" , rd_val);
    printf("NPU TEST FINISH!\n"); 
   
    char file_name[32] ="yolov5_merge/result\0";
    char temp[64] = {0};
    char tail[8] = ".bin\0";
    int fd = 0,ret=0;
    unsigned long  p ,result_addr= 0;

    for(int i=0; i < 6; i++){
        sprintf(temp, "%s%d%s", file_name,i,tail);
        fd = open(temp,O_RDONLY);
        p = faddr(fd);
        memcpy(&result_addr, (void*)p, ADDR_OFFSET);
        // printf("%x\n",result_addr);
        ret = memcmp((char*)result_addr,(char*)(faddr(fd))+ADDR_OFFSET,flen(fd)-ADDR_OFFSET);
        close(fd);
    }
    return ret;


   

}

int YOVOLV5s_ids(){
    npu_perf_test_init(NULL);
    npu_perf_test_start(0);
    
    while(npu_perf_test_get_status(0) == 0 ){
        //printf("first phase running\n");
    }
    // npu_perf_test_start(1);
    // while(npu_perf_test_get_status(0) == 0 ){
    //     //printf("second phase running\n");
    // }
    itcs_dcache_flush();
     int rd_val = MA_INW((0xc7000000 + 0x000078));
    printf("0x000078 = %d \n" , rd_val);
    printf("NPU TEST FINISH!\n"); 
   
    char file_name[32] ="npu/yolov5s_id3_DV/result\0";
    char temp[64] = {0};
    char tail[8] = ".bin\0";
    int fd = 0,ret=0;
    unsigned long  p ,result_addr= 0;

    for(int i=0; i < 3; i++){
        sprintf(temp, "%s%d%s", file_name,i,tail);
        fd = open(temp,O_RDONLY);
        p = faddr(fd);
        memcpy(&result_addr, (void*)p, ADDR_OFFSET);
        // printf("%x\n",result_addr);
        ret = memcmp((char*)result_addr,(char*)(faddr(fd))+ADDR_OFFSET,flen(fd)-ADDR_OFFSET);
        close(fd);
    }
    return ret;
}
#endif
int NetworkYolov5_new(int file_num){

    char file_name[32] ="yolov5_new/mem\0";
    char temp[64] = {0};
    char tail[8] = ".bin\0";
    int fd = 0;
    unsigned long  p ,des_addr= 0;
    npu_input_file_batch(file_name,0,681);
    for(int i = 0;i < file_num;i++){
        sprintf(temp, "%s%d%s", file_name,i,tail);
        printf("%s\n",temp);
     
        fd = open(temp, O_RDONLY);
        if(fd < 0){
            printf("open filed %s failed\n",temp);
        }
        // printf("ss");
        unsigned long fp = faddr(fd);
        memcpy(&p, (void*)fp, ADDR_OFFSET);
        close(fd);
        printf("addr = %llx\n",p);
        if(p < 0x100000000 ){
            des_addr = p + 0x100000000;
            //des_addr = des_addr + 0x100000000 -0x40000000;
            
        }else {
            des_addr = p;
           
        }
        if(des_addr < 0x102000000 || des_addr > 0x112000000){
            printf("%llx\n",des_addr);
        }
        
        // printf("%llx\n",fp+ADDR_OFFSET);
        memset((char*)des_addr,0,flen(fd) - ADDR_OFFSET);
        memcpy((char*)des_addr, (char*)(fp + ADDR_OFFSET), flen(fd) - ADDR_OFFSET);
        itcs_dcache_flush();
        //PrintBuf((char*)(des_addr),16);
       
     
    }
    unsigned int base0 = 0xC7000000;
    unsigned int rd_val;
    // fd = open("networkyolov/mem0.bin",O_RDONLY);
    // memcmp((char*)0x110000000,(char*)faddr(fd),flen(fd));
    // close(fd);
    regist_init();
    MA_OUTW((base0 + 0x000654), 0x51000000);
    MA_OUTW((base0 + 0x0003A4), 0x010015);
    rd_val = 0x1;
   while(rd_val != 0x0){
   rd_val = MA_INW((base0+0x4)) ^ 0x7fffffff;
    }
    MA_OUTW((base0 + 0x000654), 0x5101F030);
    MA_OUTW((base0 + 0x0003A4), 0x0145C9);
    rd_val = 0x1;
   while(rd_val != 0x0){
   rd_val = MA_INW((base0+0x4)) ^ 0x7fffffff;
    }
    rd_val = MA_INW((base0 + 0x000078));
     printf("0x000078 = %d \n" , rd_val);
    rd_val = MA_INW((base0 + 0x00007C)); 
    printf("0x000078 = %d \n" , rd_val);
    printf("NPU TEST FINISH!\n"); 
    fd = open("networkyolov/result.bin",O_RDONLY);
    //printf("%x\n",*((int*)(faddr(fd)+ADDR_OFFSET)));
    int ret = memcmp((char*)0x1025fe000,(char*)(faddr(fd))+ADDR_OFFSET,flen(fd)-ADDR_OFFSET);
    close(fd);
    return ret;
}

int NetworkYolov5(void){

 
    uint32_t rd_val;
    unsigned int base0,base1; 
 
    char file_name[32] ="networkyolov/mem\0";
    char temp[64] = {0};
    char tail[8] = ".bin\0";
    int fd = 0;
    for(int i = 1;i < 288;i++){
        sprintf(temp, "%s%d%s", file_name,i,tail);
        printf("%s\n",temp);
     
        fd = open(temp, O_RDONLY);
        unsigned long  p ,des_addr= 0;
        unsigned long fp = faddr(fd);
        memcpy(&p, (void*)fp, ADDR_OFFSET);
        printf("addr = %llx\n",p);
        if(p < 0x100000000 ){
            des_addr = p + 0x80000000;
            //des_addr = des_addr + 0x100000000 -0x40000000;
            
        }else {
            des_addr = p;
           
        }
        printf("%llx\n",des_addr);
        printf("%llx\n",fp+ADDR_OFFSET);
        memset((char*)des_addr,0,flen(fd) - ADDR_OFFSET);
        memcpy((char*)des_addr, (char*)(fp + ADDR_OFFSET), 100);
        itcs_dcache_flush();
        //PrintBuf((char*)(des_addr),16);
        close(fd);
     
    }
    fd = open("networkyolov/mem0.bin",O_RDONLY);
    memcmp((char*)0x110000000,(char*)faddr(fd),flen(fd));
    close(fd);

    fd = open("networkyolov/mem288.bin",O_RDONLY);
    memcmp((char*)0x11000b030,(char*)faddr(fd),flen(fd));
    close(fd);

    itcs_dcache_flush();


    // npu test start
    base0 = 0xC7000000;
    base1 = 0xC8000000;
    printf("NPU TEST START!\n"); 

    // npu_test_code start
    MA_OUTW((base0 + 0x000000), 0x070900);
    MA_OUTW((base0 + 0x000104), 0x000000);
    MA_OUTW((base0 + 0x00010C), 0x15A0881);
    MA_OUTW((base0 + 0x00010C), 0x15A0880);
    MA_OUTW((base0 + 0x000000), 0x070B00);
    MA_OUTW((base0 + 0x000000), 0x070900);
    MA_OUTW((base0 + 0x000000), 0x0F0900);
    MA_OUTW((base0 + 0x0003A8), 0x000001);
    MA_OUTW((base0 + 0x0003A8), 0x000000);
    MA_OUTW((base0 + 0x000000), 0x0F0900);
    MA_OUTW((base0 + 0x000000), 0x070900);
    MA_INW((base0 + 0x000004));
    MA_INW((base0 + 0x000000));
    MA_INW((base0 + 0x000388));
    MA_OUTW((base0 + 0x000104), 0x000000);
    MA_OUTW((base0 + 0x00010C), 0x15A0881);
    MA_OUTW((base0 + 0x00010C), 0x15A0880);
    MA_OUTW((base0 + 0x000000), 0x070B00);
    MA_OUTW((base0 + 0x000000), 0x070900);
    MA_OUTW((base0 + 0x000000), 0x0F0900);
    MA_OUTW((base0 + 0x0003A8), 0x000001);
    MA_OUTW((base0 + 0x0003A8), 0x000000);
    MA_OUTW((base0 + 0x000000), 0x0F0900);
    MA_OUTW((base0 + 0x000000), 0x070900);
    MA_INW((base0 + 0x000004));
    MA_INW((base0 + 0x000000));
    MA_INW((base0 + 0x000388));
    MA_OUTW((base0 + 0x00055C), 0xFFFFFF);
    MA_OUTW((base0 + 0x000090), 0x000000);
    MA_OUTW((base1 + 0x000000), 0x070900);
    MA_OUTW((base1 + 0x000104), 0x000000);
    MA_OUTW((base1 + 0x00010C), 0x15A0881);
    MA_OUTW((base1 + 0x00010C), 0x15A0880);
    MA_OUTW((base1 + 0x000000), 0x070B00);
    MA_OUTW((base1 + 0x000000), 0x070900);
    MA_OUTW((base1 + 0x000000), 0x0F0900);
    MA_OUTW((base1 + 0x0003A8), 0x000001);
    MA_OUTW((base1 + 0x0003A8), 0x000000);
    MA_OUTW((base1 + 0x000000), 0x0F0900);
    MA_OUTW((base1 + 0x000000), 0x070900);
    MA_INW((base1 + 0x000004));
    MA_INW((base1 + 0x000000));
    MA_INW((base1 + 0x000388));
    MA_OUTW((base1 + 0x000104), 0x000000);
    MA_OUTW((base1 + 0x00010C), 0x15A0881);
    MA_OUTW((base1 + 0x00010C), 0x15A0880);
    MA_OUTW((base1 + 0x000000), 0x070B00);
    MA_OUTW((base1 + 0x000000), 0x070900);
    MA_OUTW((base1 + 0x000000), 0x0F0900);
    MA_OUTW((base1 + 0x0003A8), 0x000001);
    MA_OUTW((base1 + 0x0003A8), 0x000000);
    MA_OUTW((base1 + 0x000000), 0x0F0900);
    MA_OUTW((base1 + 0x000000), 0x070900);
    MA_INW((base1 + 0x000004));
    MA_INW((base1 + 0x000000));
    MA_INW((base1 + 0x000388));
    MA_OUTW((base1 + 0x00055C), 0xFFFFFF);
    MA_OUTW((base1 + 0x000090), 0x000000);
    MA_OUTW((base0 + 0x000000), 0x070900);
    MA_OUTW((base0 + 0x000000), 0x070100);
    MA_OUTW((base0 + 0x0003A8), 0x000002);
    MA_OUTW((base0 + 0x00003C), 0xFFFFFFFF);
    MA_OUTW((base0 + 0x00003C), 0x000000);
    MA_OUTW((base0 + 0x000100), 0x140021);
    MA_OUTW((base0 + 0x000104), 0x000000);
    MA_OUTW((base0 + 0x00010C), 0x15A0880);
    MA_OUTW((base0 + 0x000414), 0x000000);
    MA_OUTW((base0 + 0x000014), 0xFFFFFFFF);
    MA_OUTW((base1 + 0x000000), 0x070900);
    MA_OUTW((base1 + 0x000000), 0x070100);
    MA_OUTW((base1 + 0x0003A8), 0x000002);
    MA_OUTW((base1 + 0x00003C), 0xFFFFFFFF);
    MA_OUTW((base1 + 0x00003C), 0x000000);
    MA_OUTW((base1 + 0x000100), 0x140021);
    MA_OUTW((base1 + 0x000104), 0x000000);
    MA_OUTW((base1 + 0x00010C), 0x15A0880);
    MA_OUTW((base1 + 0x000414), 0x000000);
    MA_OUTW((base1 + 0x000014), 0xFFFFFFFF);
    MA_OUTW((base0 + 0x000654), 0x51000000);
    MA_OUTW((base0 + 0x0003A4), 0x010015);
    rd_val = 0x1;
    printf("begin\n");
   while(rd_val != 0x0){
   rd_val = MA_INW((base0+0x4)) ^ 0x7fffffff;
    }
    MA_OUTW((base0 + 0x000654), 0x5100B030);
    MA_OUTW((base0 + 0x0003A4), 0x01094C);
    rd_val = 0x1;
   while(rd_val != 0x0){
   rd_val = MA_INW((base0+0x4)) ^ 0x7fffffff;
    }
    MA_INW((base0 + 0x000078));
    MA_INW((base1 + 0x000078));
    itcs_dcache_flush();
    fd = open("networkyolov/result.bin",O_RDONLY);

    int ret = memcmp((char*)0x1027c5000, (char*)faddr(fd), flen(fd));
    close(fd);
    return ret;

    // printf("NPU TEST FINISH!\n"); 
    // soc_dump0(0x100000000 + 0x02636000, 0x0018e700);
    // soc_dump0(0x100000000 + 0x027c5000, 0x000639c0);
    // soc_dump0(0x100000000 + 0x02829000, 0x00018e70);

    // npu_test_code finish
    
    // MA_OUTW(base + 0x000,0x70900);
    // MA_OUTW(base + 0x0104,0x00);
    // MA_OUTW(base + 0x010c,0x15a0881);
    // MA_OUTW(base + 0x010c,0x15a0880);

    

    return 0;
}

int NetworkLenet(void){

    uint32_t  rd_val;
    unsigned int base; 
    // clock_config();
    char *file_name_1[]={"networkLenet/hal_dump_lenet_DV/mem0.bin",
                        "networkLenet/hal_dump_lenet_DV/mem1.bin",
                        "networkLenet/hal_dump_lenet_DV/mem2.bin",
                        "networkLenet/hal_dump_lenet_DV/mem3.bin",
                        "networkLenet/hal_dump_lenet_DV/mem4.bin",
                        "networkLenet/hal_dump_lenet_DV/mem5.bin",
                        "networkLenet/hal_dump_lenet_DV/mem6.bin",
                        "networkLenet/hal_dump_lenet_DV/mem7.bin"  
                          };

    char *file_name_2[]={"networkLenet/hal_dump_lenet_DV/mem8.bin",
                        "networkLenet/hal_dump_lenet_DV/mem9.bin",
                        "networkLenet/hal_dump_lenet_DV/mem10.bin",
                        "networkLenet/hal_dump_lenet_DV/mem11.bin",
                        "networkLenet/hal_dump_lenet_DV/mem12.bin",
                        "networkLenet/hal_dump_lenet_DV/mem13.bin",
                        "networkLenet/hal_dump_lenet_DV/mem14.bin",
                        "networkLenet/hal_dump_lenet_DV/mem15.bin"
                        };

    char *file_name_3[]={"networkLenet/hal_dump_lenet_DV/mem16.bin",
                        "networkLenet/hal_dump_lenet_DV/mem17.bin",
                        "networkLenet/hal_dump_lenet_DV/mem18.bin",
                        "networkLenet/hal_dump_lenet_DV/mem19.bin",
                        "networkLenet/hal_dump_lenet_DV/mem20.bin",
                        "networkLenet/hal_dump_lenet_DV/result.bin"
                        };
    unsigned long int addrs[8]={0};
    int fd[8]={0};

    open_file_node(file_name_1,addrs,fd,8);
    
    memcpy((char *)0x100324100,(char*)addrs[0],flen(fd[0]));
    memcpy((char *)0x100325100,(char*)addrs[1],flen(fd[1]));
    memcpy((char *)0x100324100,(char*)addrs[2],flen(fd[2]));

    // memcpy((char *)0x000000000,(char*)addrs[3],flen(fd[3]));//mem3 00000000?
    memcpy((char *)0x100327000,(char*)addrs[4],flen(fd[4]));
    memcpy((char *)0x100326000,(char*)addrs[5],flen(fd[5]));
    memcpy((char *)0x1003273c0,(char*)addrs[6],flen(fd[6]));
    memcpy((char *)0x1003260c0,(char*)addrs[7],flen(fd[7]));
    close_file_node(fd,8);
    itcs_dcache_flush();
    open_file_node(file_name_2,addrs,fd,8);

    memset((char *)0x10032d340, 0, 409600);
    memcpy((char *)0x10032d340,(char*)addrs[0],flen(fd[0]));

    memcpy((char *)0x100326180,(char*)addrs[1],flen(fd[1]));
    memcpy((char *)0x10038e900,(char*)addrs[2],flen(fd[2]));
    memcpy((char *)0x100326240,(char*)addrs[3],flen(fd[3]));
    memcpy((char *)0x100326300,(char*)addrs[4],flen(fd[4]));
    memcpy((char *)0x1003263c0,(char*)addrs[5],flen(fd[5]));
    memcpy((char *)0x10038fd00,(char*)addrs[6],flen(fd[6]));
    memcpy((char *)0x100326480,(char*)addrs[7],flen(fd[7]));
    itcs_dcache_flush();
    close_file_node(fd,8);

    open_file_node(file_name_3,addrs,fd,6);
    //cmd1 mem19
    memcpy((char *)0x120000000,(char*)addrs[3],flen(fd[3]));
    //cmd2 mem20
    memcpy((char *)0x120004db8,(char*)addrs[4],flen(fd[4]));
    memcpy((char *)0x100390d40,(char*)addrs[0],flen(fd[0]));
    memcpy((char *)0x100326540,(char*)addrs[1],flen(fd[1]));
    memcpy((char *)0x100326600,(char*)addrs[2],flen(fd[2]));
    itcs_dcache_flush();
    base = 0xC7000000;
    
    MA_OUTW((base + 0x000654), 0x60000000);
    printf("cmd buffer = %x\n",MA_INW(base+0x664));
    MA_OUTW((base + 0x0003A4), 0x01ffff);
    printf("1\n");
    rd_val = 0x01;
    while(rd_val != 0x0){  
        rd_val = MA_INW((base+0x4)) ^ 0x7fffffff;
        // printf("idle reg %x\n",MA_INW(base+0x4));
    }
    rd_val = 0x01;
    while(rd_val != 0x0){  
        rd_val = MA_INW((base+0x4)) ^ 0x7fffffff;
    }
    printf("1\n");
    itcs_dcache_flush();
    MA_OUTW((base + 0x000654), 0x60004db8);
    
    MA_OUTW((base + 0x0003A4), 0x01ffff);
    rd_val = 0x01;
     while(rd_val != 0x0){  

        rd_val = MA_INW((base+0x4)) ^ 0x7fffffff;
        printf("idle reg %x\n",MA_INW(base+0x4));
    }
    itcs_dcache_invalid();
    int ret = memcmp((char *)0x100325100,(char*)addrs[5],flen(fd[5]));
    close_file_node(fd,6);

    return ret;
    return 0;
}

int ppu_absdiff_test(void){
    
    int ret =0;
    char file_name[32] ="absdiff_DV/mem\0";
    char temp[64] = {0};
    char tail[8] = ".bin\0";
    int fd = 0;
    for(int i = 0;i < 5;i++){
        sprintf(temp, "%s%d%s", file_name,i,tail);
        // printf("%s\n",temp);
     
        fd = open(temp, O_RDONLY);
        unsigned long  p ,des_addr= 0;
        unsigned long fp = faddr(fd);
        memcpy(&p, (void*)fp, ADDR_OFFSET);
        // printf("addr = %llx\n",p);
        if(p < 0x100000000 ){
            des_addr = p + 0x80000000 +0x10000000;
            //des_addr = des_addr + 0x100000000 -0x40000000;
            
        }else {
            des_addr = p;
           
        }
        printf("des_addr = %llx\n",des_addr);
        printf("src_addr = %llx\n",fp+ADDR_OFFSET);
        //memset((char*)des_addr,0,flen(fd) - ADDR_OFFSET);
        memcpy((char*)des_addr, (char*)(fp + ADDR_OFFSET), flen(fd) - ADDR_OFFSET);
        // PrintBuf((char*)(des_addr),176);
        // PrintBuf((char*)(des_addr)+flen(fd) - ADDR_OFFSET-16,16);
        itcs_dcache_flush();
        //PrintBuf((char*)(des_addr),16);
        close(fd);
     
    }
    unsigned int base0 = 0xC7000000; 
    fd = open("absdiff_DV/result.bin",O_RDONLY);
    //ret = memcmp((char*)0x10209d000,(char*)(faddr(fd)+ADDR_OFFSET),flen(fd)-8);
    regist_init();
    MA_OUTW((base0 + 0x000654), 0x51000000);
    printf("cmd buffer = %x\n",MA_INW(base0+0x664));
    //MA_OUTW((base0 + 0x0003A4), 0x01ffff);
    MA_OUTW((base0 + 0x0003A4), 0x010015);
    while (get_status_0() == 0)
    {
    }
    MA_OUTW((base0 + 0x000654), 0x51002030);
    printf("cmd buffer = %x\n",MA_INW(base0+0x664));
    MA_OUTW((base0 + 0x0003A4), 0x010055);
    while (get_status_0() == 0)
    {
    }
    printf("0x000078 = %d \n", MA_INW(base0 + 0x000078));
    ret = memcmp((char*)0x10209d000, (char*)(faddr(fd)+ADDR_OFFSET), flen(fd) - 8);
    #if CONFIG_COMPILE_RTL
    // printf("dump result\n");
    // soc_dump0(0x100000000 + 0x0209d000, 0x004B008);
    #endif
    close(fd);
    return ret;
}

int ppu_warp_affine(void){
    
    int ret =0;
    char file_name[32] ="warpaffine_DV/mem\0";
    char temp[64] = {0};
    char tail[8] = ".bin\0";
    int fd = 0;
    for(int i = 0;i < 5;i++){
        sprintf(temp, "%s%d%s", file_name,i,tail);
        // printf("%s\n",temp);
     
        fd = open(temp, O_RDONLY);
        unsigned long  p ,des_addr= 0;
        unsigned long fp = faddr(fd);
        memcpy(&p, (void*)fp, ADDR_OFFSET);
        // printf("addr = %llx\n",p);
        if(p < 0x100000000 ){
            des_addr = p + 0x40000000;
            //des_addr = des_addr + 0x100000000 -0x40000000;
            
        }else {
            des_addr = p;
           
        }
        printf("des_addr = %llx\n",des_addr);
        // printf("src_addr = %llx\n",fp+ADDR_OFFSET);
        //memset((char*)des_addr,0,flen(fd) - ADDR_OFFSET);
        memcpy((char*)des_addr, (char*)(fp + ADDR_OFFSET), flen(fd) - ADDR_OFFSET);
        itcs_dcache_flush();
        //PrintBuf((char*)(des_addr),16);
        close(fd);
     
    }
    regist_init();
    unsigned int base0 = 0xC7000000;
    MA_OUTW((base0 + 0x000654), 0x51000000);
    printf("cmd buffer = %x\n",MA_INW(base0+0x664));
    //MA_OUTW((base0 + 0x0003A4), 0x01ffff);
    MA_OUTW((base0 + 0x0003A4), 0x010015);
    while (get_status_0() == 0)
    {
    }
    MA_OUTW((base0 + 0x000654), 0x51002030);
    printf("cmd buffer = %x\n",MA_INW(base0+0x664));
    MA_OUTW((base0 + 0x0003A4), 0x010057);
    while (get_status_0() == 0)
    {
    }
    printf("0x000078 = %d \n", MA_INW(base0 + 0x000078));
    itcs_dcache_flush();
    fd = open("warpaffine_DV/result.bin",O_RDONLY);
    ret = memcmp((char*)0x102134000,(char*)(faddr(fd) + ADDR_OFFSET), flen(fd) - ADDR_OFFSET);
    close(fd);
    return ret;
}

int shared_copy_test(void)
{
   #if S1
    uint32_t  rd_val;
    unsigned int base; 
  
    // npu test start
    base = 0xC7000000;
   
    printf("NPU TEST START!\n"); 
   
    unsigned long int addrs[3]={0};
    int fd[3]={0};
    char* file_name[]={"shader_copy_test/shader_copy_data/mem0_cmd_buffer.bin",
                        "shader_copy_test/shader_copy_data/mem1_vshader_buffer.bin",
                        "shader_copy_test/shader_copy_data/mem2_src_buffer.bin"};
    //load_rtlfs(file_name,3,addrs);
    open_file_node(file_name,addrs,fd,3);
    memcpy((char*)0x110000000,(char*)addrs[0],flen(fd[0]));
    memcpy((char*)0x112000000,(char*)addrs[1],flen(fd[1]));
    memcpy((char*)0x111000000,(char*)addrs[2],flen(fd[2]));
    itcs_dcache_flush();
   

    // MA_OUTW((base + 0x00038C), 0x000010);
    MA_OUTW((base + 0x00010C), 0x020000);
    MA_OUTW((base + 0x000654), 0x50000000);
    
    MA_OUTW((base + 0x0003A4), 0x010028);
    
    rd_val = 0x1;
   
    while(rd_val != 0x0){  
        rd_val = MA_INW((base+0x4)) ^ 0x7fffffff;
    }
    itcs_dcache_invalid();

    int ret =memcmp((char*)0x111000000,(char *)0x114000000,4096);
    close_file_node(fd,3);
    return ret;
  #endif 
    return 1;


}

int shared_copy_ram2hit_test(void)
{
     #if S2
    uint32_t  rd_val;
    unsigned int base; 


    char* file_name[]={"shader_copy_ram2hit_test/shader_copy_ram2hit_data/mem0_cmd_buffer.bin",
                        "shader_copy_ram2hit_test/shader_copy_ram2hit_data/mem1_shader_buffer.bin",
                        "shader_copy_ram2hit_test/shader_copy_ram2hit_data/mem2_src_buffer.bin"};
    int fd[3]={0};                  
    unsigned long int addrs[3]={0};                   
    open_file_node(file_name,addrs,fd,3);

    memcpy((char *)0x120000000,(char *)addrs[0],flen(fd[0]));
    memcpy((char*)0x112000000,(char*)addrs[1],flen(fd[1]));
    memcpy((char*)0x113000000,(char*)addrs[2],flen(fd[2]));

    close_file_node(fd,3);
    itcs_dcache_flush();
 
//////////////////////////////
    // npu test start
    base = 0xC7000000;
    printf("NPU TEST START!\n"); 

    // npu_test_code start
    MA_OUTW((base + 0x000100), 0x140021);
    MA_OUTW((base + 0x00010C), 0x020000);
    MA_OUTW((base + 0x000654), 0x60000000);
    MA_OUTW((base + 0x0003A4), 0x01FFFF);

    rd_val = 0x1;
   while(rd_val != 0x0){
        rd_val = MA_INW((base+0x4)) ^ 0x7fffffff;
    }
   
    itcs_dcache_invalid();
    // npu_test_code finish

    
    int ret = memcmp((char*)0x113000000,(char *)0x114000000,4096);
    close_file_node(fd,3);
    return ret;
    #endif
    return 0;
}

int nn_transpose_test(void)
{
    #if NTP
    uint32_t  rd_val;
    unsigned int base; 


    char* file_name[]={"nn_transpose_test/nn_transpose_data/mem0.bin",
                        "nn_transpose_test/nn_transpose_data/mem2.bin",
                        "nn_transpose_test/nn_transpose_data/mem3.bin",
                        "nn_transpose_test/nn_transpose_data/mem4.bin",
                        "nn_transpose_test/nn_transpose_data/mem5.bin",
                        "nn_transpose_test/nn_transpose_data/result.bin"
                        };
    int fd[6]={0};                  
    unsigned long int addrs[6]={0};                   
    open_file_node(file_name,addrs,fd,6);

    //PrintBuf((char*)addrs[5],16);
    //udelay(6000*1000);
    memcpy((char*)0x110000000,(char*)addrs[4],flen(fd[4]));
    memcpy((char*)0x100100800,(char*)addrs[3],flen(fd[3]));
  
    memcpy((char*)0x101000040,(char*)addrs[2],flen(fd[2]));
    memcpy((char*)0x101000000,(char*)addrs[1],flen(fd[1]));
    memcpy((char*)0x102000400,(char*)addrs[0],flen(fd[0]));
  
    itcs_dcache_flush();
//////////////////////////////
    // npu test start
    base = 0xC7000000;
    printf("NPU TEST START!\n"); 

    // npu_test_code start
    MA_OUTW((base + 0x000000), 0x070900);
    MA_OUTW((base + 0x000014), 0x00FFFF);
    MA_OUTW((base + 0x000090), 0x000040);
    MA_OUTW((base + 0x000100), 0x140021);
    MA_OUTW((base + 0x000178), 0x000000);
    MA_OUTW((base + 0x00010C), 0x15B0880);
    MA_OUTW((base + 0x000654), 0x50000000);
    MA_OUTW((base + 0x0003A4), 0x01FFFF);

    rd_val = 0x1;
    while(rd_val != 0x0){
        rd_val = MA_INW((base+0x4)) ^ 0x7fffffff;
    }
   
     itcs_dcache_invalid();
    // npu_test_code finish
   
    int ret = memcmp((char*)0x102000000,(char*)faddr(fd[5]),flen(fd[5]));
    close_file_node(fd,6);
    return ret;
    #endif
    return 0;
}

int nn_tensoradd_test(void)
{
    #if NTD
    uint32_t  rd_val;
    unsigned int base; 

   char* file_name[]={ "nn_tensoradd_test/nn_tensoradd_data/mem0.bin",
                        "nn_tensoradd_test/nn_tensoradd_data/mem1.bin",
                        "nn_tensoradd_test/nn_tensoradd_data/mem2.bin",
                        "nn_tensoradd_test/nn_tensoradd_data/mem3.bin",
                        "nn_tensoradd_test/nn_tensoradd_data/mem4.bin",
                        "nn_tensoradd_test/nn_tensoradd_data/mem5.bin",
                        "nn_tensoradd_test/nn_tensoradd_data/mem6.bin",
                        "nn_tensoradd_test/nn_tensoradd_data/result.bin"
                        };
    int fd[8]={0};                  
    unsigned long int addrs[8]={0};                   
    open_file_node(file_name,addrs,fd,8);

   
    memcpy((char*)0x110000000,(char*)addrs[6],flen(fd[6]));
    memcpy((char*)0x100100800,(char*)addrs[5],flen(fd[5]));
    memcpy((char*)0x1010000c0,(char*)addrs[4],flen(fd[4]));
    memcpy((char*)0x101000040,(char*)addrs[3],flen(fd[3]));
    memcpy((char*)0x101000000,(char*)addrs[2],flen(fd[2]));
    memcpy((char*)0x102000140,(char*)addrs[1],flen(fd[1]));
    memcpy((char*)0x102000200,(char*)addrs[0],flen(fd[0]));

    itcs_dcache_flush();

//////////////////////////////
    // npu test start
    base = 0xC7000000;
    printf("NPU TEST START!\n"); 

    // npu_test_code start
    MA_OUTW((base + 0x000000), 0x070900);
    MA_OUTW((base + 0x000014), 0x00FFFF);
    MA_OUTW((base + 0x000090), 0x000040);
    MA_OUTW((base + 0x000100), 0x140021);
    MA_OUTW((base + 0x000178), 0x000000);
    MA_OUTW((base + 0x00010C), 0x15B0880);
    MA_OUTW((base + 0x000654), 0x50000000);
    MA_OUTW((base + 0x0003A4), 0x01FFFF);

    rd_val = 0x1;
   while(rd_val != 0x0){
   rd_val = MA_INW((base+0x4)) ^ 0x7fffffff;
    }
     itcs_dcache_invalid();
    int ret =  memcmp((char*)0x102000000,(char*)addrs[7],flen(fd[7]));
    close_file_node(fd,8);
    return ret;
    #endif
    return 0;
}

int nn_perchquantization_test(void)
{
    #if PER
    uint32_t  rd_val;
    unsigned int base; 
   
    char* file_name[]={ "nn_perchquantization_test/nn_perchquantization_data/mem0.bin",
                        "nn_perchquantization_test/nn_perchquantization_data/mem2.bin",
                        "nn_perchquantization_test/nn_perchquantization_data/mem3.bin",
                        "nn_perchquantization_test/nn_perchquantization_data/mem4.bin",
                        "nn_perchquantization_test/nn_perchquantization_data/mem5.bin",
                        "nn_perchquantization_test/nn_perchquantization_data/mem6.bin",
                        "nn_perchquantization_test/nn_perchquantization_data/result.bin"
                        };
    int fd[7]={0};                  
    unsigned long int addrs[7]={0};                   
    open_file_node(file_name,addrs,fd,7);
 
    
    memcpy((char*)0x110000000,(char*)addrs[5],flen(fd[5]));
    memcpy((char*)0x100100800,(char*)addrs[4],flen(fd[4]));
    memcpy((char*)0x101001640,(char*)addrs[3],flen(fd[3]));
    memcpy((char*)0x101000040,(char*)addrs[2],flen(fd[2]));
    memcpy((char*)0x101000000,(char*)addrs[1],flen(fd[1]));
    memcpy((char*)0x102004040,(char*)addrs[0],flen(fd[0]));
    itcs_dcache_flush();

//////////////////////////////
    // npu test start
    base = 0xC7000000;
    printf("NPU TEST START!\n"); 

    // npu_test_code start
    MA_OUTW((base + 0x000000), 0x070900);
    MA_OUTW((base + 0x000014), 0x00FFFF);
    MA_OUTW((base + 0x000090), 0x000040);
    MA_OUTW((base + 0x000100), 0x140021);
    MA_OUTW((base + 0x000178), 0x000000);
    MA_OUTW((base + 0x00010C), 0x15B0880);
    
    MA_OUTW((base + 0x000654), 0x50000000);
    MA_OUTW((base + 0x0003A4), 0x01FFFF);

    rd_val = 0x1;
   while(rd_val != 0x0){
   rd_val = MA_INW((base+0x4)) ^ 0x7fffffff;
    }
     itcs_dcache_invalid();
    int ret=  memcmp((char*)0x102000000,(char*)addrs[6],flen(fd[6]));
    close_file_node(fd,7);
    return ret;
    #endif
    return 0;
}

int nn_mmu_32bit_test(void)
{
    #if NNM
    uint32_t  rd_val=0;
    unsigned int base; 

    char* file_name_1[]={"nn_mmu_32bit_test/nn_mmu_32bit_data/mem0.bin",
                        "nn_mmu_32bit_test/nn_mmu_32bit_data/mem1.bin",
                        "nn_mmu_32bit_test/nn_mmu_32bit_data/mem2.bin",
                        "nn_mmu_32bit_test/nn_mmu_32bit_data/mem3.bin",
                        "nn_mmu_32bit_test/nn_mmu_32bit_data/mem4.bin",
                        "nn_mmu_32bit_test/nn_mmu_32bit_data/mem5.bin",
                        "nn_mmu_32bit_test/nn_mmu_32bit_data/mem7.bin",
                        "nn_mmu_32bit_test/nn_mmu_32bit_data/mem8.bin"                     
                        };
    char* file_name_2[]={ "nn_mmu_32bit_test/nn_mmu_32bit_data/mem9.bin",
                        "nn_mmu_32bit_test/nn_mmu_32bit_data/mem10.bin",
                        "nn_mmu_32bit_test/nn_mmu_32bit_data/result.bin"};
    int fd[8]={0};                  
    unsigned long int addrs[8]={0};                   
    open_file_node(file_name_1,addrs,fd,8);

    memcpy((char*)0x101000040,(char*)addrs[7],flen(fd[7]));
    memcpy((char*)0x101000000,(char*)addrs[6],flen(fd[6]));
    memcpy((char*)0x102000040,(char*)addrs[5],flen(fd[5]));
    memcpy((char*)0x120001000,(char*)addrs[4],flen(fd[4]));


    memcpy((char*)0x11fffbcf0,(char*)addrs[3],flen(fd[3]));
    memcpy((char*)0x111000400,(char*)addrs[2],flen(fd[2]));
    memcpy((char*)0x111000000,(char*)addrs[1],flen(fd[1]));
    memcpy((char*)0x120000000,(char*)addrs[0],flen(fd[0]));
    itcs_dcache_flush();
    close_file_node(fd,8);
    
    open_file_node(file_name_2,addrs,fd,3);
    
    memcpy((char*)0x120001020,(char*)addrs[1],flen(fd[1]));
    memcpy((char*)0x100100800,(char*)addrs[0],flen(fd[0]));

  
    itcs_dcache_flush();
//////////////////////////////
    // npu test start
    base = 0xC7000000;
    printf("NPU TEST START!\n"); 

    // npu_test_code start
    MA_OUTW((base + 0x000000), 0x070900);
    MA_OUTW((base + 0x000014), 0x00FFFF);
    MA_OUTW((base + 0x000090), 0x000040);
    MA_OUTW((base + 0x000100), 0x140021);
    MA_OUTW((base + 0x000178), 0x000000);
    MA_OUTW((base + 0x00010C), 0x15B0880);
    MA_OUTW((base + 0x00038C), 0x60000000);

    MA_OUTW((base + 0x000390), 0x000000);
    MA_OUTW((base + 0x000398), 0x5fFFBCF0);
    MA_OUTW((base + 0x00039C), 0x5fFFBCF0);
    MA_OUTW((base + 0x000654), 0x60001000);
    printf("cmd1 = %x\n",MA_INW(base+0x664));
    MA_OUTW((base + 0x0003A4), 0x10004);
    while(rd_val != 0x0){
        rd_val = MA_INW((base+0x4)) ^ 0x7fffffff;
    }
   
    MA_OUTW((base + 0x000388), 0x000001);
    MA_OUTW((base + 0x000654), 0x60001020);
    printf("cmd buffer = %x\n",MA_INW(base+0x664));
    MA_OUTW((base + 0x0003A4), 0x01FFFF);

    rd_val = 0x1;
    while(rd_val != 0x0){
        rd_val = MA_INW((base+0x4)) ^ 0x7fffffff;
    }
    PrintBuf((char*)0x102000000,8);
    itcs_dcache_invalid();
    PrintBuf((char*)0x102000000,8);

    int ret = memcmp((char*)0x102000000,(char*)addrs[2],flen(fd[2]));
    close_file_node(fd,3);
    return ret;
    #endif

    return 0;
}

int nn_max_ot_test(void)
{
    #if MT
    uint32_t  rd_val;
    unsigned int base; 
   
    
    char* file_name[]={"nn_max_ot_test/nn_max_ot_data/mem0.bin",
                        "nn_max_ot_test/nn_max_ot_data/mem2.bin",
                        "nn_max_ot_test/nn_max_ot_data/mem3.bin",
                        "nn_max_ot_test/nn_max_ot_data/mem4.bin",
                        "nn_max_ot_test/nn_max_ot_data/mem5.bin",
                        "nn_max_ot_test/nn_max_ot_data/result.bin"
                        };
    int fd[6]={0};                  
    unsigned long int addrs[6]={0};                   
    open_file_node(file_name,addrs,fd,6);

    memcpy((char*)0x110000000,(char*)addrs[4],flen(fd[4]));
    memcpy((char*)0x100100800,(char*)addrs[3],flen(fd[3]));
  
    memcpy((char*)0x101000040,(char*)addrs[2],flen(fd[2]));
    memcpy((char*)0x101000000,(char*)addrs[1],flen(fd[1]));
    memcpy((char*)0x102004800,(char*)addrs[0],flen(fd[0]));
   
    //udelay(6000*1000);
    itcs_dcache_flush();
   
//////////////////////////////
    // npu test start
    base = 0xC7000000;
    printf("NPU TEST START!\n"); 

    // npu_test_code start
    MA_OUTW((base + 0x000000), 0x070900);
    MA_OUTW((base + 0x000014), 0x00FFFF);
    MA_OUTW((base + 0x000090), 0x000040);
    MA_OUTW((base + 0x000100), 0x140021);
    MA_OUTW((base + 0x000178), 0x000000);
    MA_OUTW((base + 0x00010C), 0x15B0880);
    MA_OUTW((base + 0x000654), 0x50000000);
    MA_OUTW((base + 0x0003A4), 0x01FFFF);

    rd_val = 0x1;
   while(rd_val != 0x0){
   rd_val = MA_INW((base+0x4)) ^ 0x7fffffff;
    }
    itcs_dcache_invalid();
   
    int ret =  memcmp((char*)0x102000000,(char*)addrs[5],flen(fd[5]));
    close_file_node(fd,6);
    return ret;
    #endif
    return 0;
}

int nn_kernel_1_1_test(void)
{
    #if K1
    uint32_t  rd_val;
    unsigned int base; 
    
     char* file_name[]={"nn_kernel_1x1_test/nn_kernel_1x1_data/mem0.bin",
                        "nn_kernel_1x1_test/nn_kernel_1x1_data/mem2.bin",
                        "nn_kernel_1x1_test/nn_kernel_1x1_data/mem3.bin",
                        "nn_kernel_1x1_test/nn_kernel_1x1_data/mem4.bin",
                        "nn_kernel_1x1_test/nn_kernel_1x1_data/mem5.bin",
                        "nn_kernel_1x1_test/nn_kernel_1x1_data/result.bin"
                        };
    int fd[6]={0};                  
    unsigned long int addrs[6]={0};                   
    open_file_node(file_name,addrs,fd,6);
  
    memcpy((char*)0x110000000,(char*)addrs[4],flen(fd[4]));
    memcpy((char*)0x100100800,(char*)addrs[3],flen(fd[3]));
  
    memcpy((char*)0x101000040,(char*)addrs[2],flen(fd[2]));
    memcpy((char*)0x101000000,(char*)addrs[1],flen(fd[1]));
    memcpy((char*)0x102000040,(char*)addrs[0],flen(fd[0]));
    itcs_dcache_flush();
//////////////////////////////
    // npu test start
    base = 0xC7000000;
    printf("NPU TEST START!\n"); 

    // npu_test_code start
    MA_OUTW((base + 0x000000), 0x070900);
    MA_OUTW((base + 0x000014), 0x00FFFF);
    MA_OUTW((base + 0x000090), 0x000040);
    MA_OUTW((base + 0x000100), 0x140021);
    MA_OUTW((base + 0x000178), 0x000000);
    MA_OUTW((base + 0x00010C), 0x15B0880);
    MA_OUTW((base + 0x000654), 0x50000000);
    MA_OUTW((base + 0x0003A4), 0x01FFFF);

    rd_val = 0x1;
   while(rd_val != 0x0){
        rd_val = MA_INW((base+0x4)) ^ 0x7fffffff;
    }
    itcs_dcache_invalid();
    int ret =  memcmp((char*)0x42000000,(char*)addrs[5],flen(fd[5]));
    close_file_node(fd,6);
    return ret;
    #endif
    return 0;
}

int nn_kernel_3_3_test(void)
{
    #if K3
     uint32_t  rd_val;
    unsigned int base;

    char* file_name[]={"nn_kernel_3x3_test/nn_kernel_3x3_data/mem0.bin",
                        "nn_kernel_3x3_test/nn_kernel_3x3_data/mem2.bin",
                        "nn_kernel_3x3_test/nn_kernel_3x3_data/mem3.bin",
                        "nn_kernel_3x3_test/nn_kernel_3x3_data/mem4.bin",
                        "nn_kernel_3x3_test/nn_kernel_3x3_data/mem5.bin",
                        "nn_kernel_3x3_test/nn_kernel_3x3_data/mem6.bin",
                        "nn_kernel_3x3_test/nn_kernel_3x3_data/result.bin"
                        };
    int fd[7]={0};                  
    unsigned long int addrs[7]={0};                   
    open_file_node(file_name,addrs,fd,7);
   
   
    memcpy((char*)0x110000000,(char*)addrs[5],flen(fd[5]));
    memcpy((char*)0x100100800,(char*)addrs[4],flen(fd[4]));
    memcpy((char*)0x1010000c0,(char*)addrs[3],flen(fd[3]));
    memcpy((char*)0x101000040,(char*)addrs[2],flen(fd[2]));
    memcpy((char*)0x101000000,(char*)addrs[1],flen(fd[1]));
    memcpy((char*)0x102000040,(char*)addrs[0],flen(fd[0]));
    itcs_dcache_flush();
//////////////////////////////
    // npu test start
    base = 0xC7000000;
    printf("NPU TEST START!\n"); 

    // npu_test_code start
    MA_OUTW((base + 0x000000), 0x070900);
    MA_OUTW((base + 0x000014), 0x00FFFF);
    MA_OUTW((base + 0x000090), 0x000040);
    MA_OUTW((base + 0x000100), 0x140021);
    MA_OUTW((base + 0x000178), 0x000000);
    MA_OUTW((base + 0x00010C), 0x15B0880);
    MA_OUTW((base + 0x000654), 0x50000000);
    MA_OUTW((base + 0x0003A4), 0x01FFFF);

    rd_val = 0x1;
   while(rd_val != 0x0){
   rd_val = MA_INW((base+0x4)) ^ 0x7fffffff;
    }
     itcs_dcache_invalid();
    int ret = memcmp((char*)0x102000000,(char*)addrs[6],flen(fd[6]));
    close_file_node(fd,7);
    return ret;
    #endif
    return 0;
}

int nn_ddr_write_test(void)
{
    #if NN_W
    uint32_t  rd_val;
    unsigned int base; 
   
     char* file_name[]={"nn_ddr_write_test/nn_ddr_write_data/mem0.bin",
                        "nn_ddr_write_test/nn_ddr_write_data/mem2.bin",
                        "nn_ddr_write_test/nn_ddr_write_data/mem3.bin",
                        "nn_ddr_write_test/nn_ddr_write_data/mem4.bin",
                        "nn_ddr_write_test/nn_ddr_write_data/mem5.bin",
                        "nn_ddr_write_test/nn_ddr_write_data/result.bin"
                        };
    int fd[6]={0};                  
    unsigned long int addrs[6]={0};                   
    open_file_node(file_name,addrs,fd,6);
    memcpy((char*)0x110000000,(char*)addrs[4],flen(fd[4]));
    memcpy((char*)0x100100800,(char*)addrs[3],flen(fd[3]));
    memcpy((char*)0x101000040,(char*)addrs[2],flen(fd[2]));
    memcpy((char*)0x101000000,(char*)addrs[1],flen(fd[1]));
    memcpy((char*)0x102120000,(char*)addrs[0],flen(fd[0]));
    itcs_dcache_flush();

    // npu test start
    base = 0xC7000000;
    printf("NPU TEST START!\n"); 
    printf("idle reg %x\n",MA_INW(base+0x4));
    // npu_test_code start
   
    MA_OUTW((base + 0x000000), 0x070900);
    MA_OUTW((base + 0x000014), 0x00FFFF);
    MA_OUTW((base + 0x000090), 0x000040);
    MA_OUTW((base + 0x000100), 0x140021);
    MA_OUTW((base + 0x000178), 0x000000);
    MA_OUTW((base + 0x00010C), 0x15B0880);
    MA_OUTW((base + 0x000654), 0x50000000);
    
    MA_OUTW((base + 0x0003A4), 0x01ffff);
    
    rd_val = 0x1;
   while(rd_val != 0x0){
        rd_val = MA_INW((base+0x4)) ^ 0x7fffffff;
        printf("idle reg %x\n",MA_INW(base+0x4));
    }
    itcs_dcache_flush();

   
    int ret =  memcmp((char*)0x102000000,(char*)addrs[5],flen(fd[5]));
    close_file_node(fd,6);
    return ret;
    #endif
    return 0;
}

int nn_ddr_read_test(void)
{
    #if NN_R
    uint32_t  rd_val;
    unsigned int base; 

   
     char* file_name[]={"nn_ddr_read_test/nn_ddr_read_data/mem0.bin",
                        "nn_ddr_read_test/nn_ddr_read_data/mem2.bin",
                        "nn_ddr_read_test/nn_ddr_read_data/mem3.bin",
                        "nn_ddr_read_test/nn_ddr_read_data/mem4.bin",
                        "nn_ddr_read_test/nn_ddr_read_data/mem5.bin",
                        "nn_ddr_read_test/nn_ddr_read_data/result.bin"
                        };
    int fd[6]={0};                  
    unsigned long int addrs[6]={0};                   
    open_file_node(file_name,addrs,fd,6);

 
    
    memcpy((char*)0x110000000,(char*)addrs[4],flen(fd[4]));
    memcpy((char*)0x100100800,(char*)addrs[3],flen(fd[3]));
    memcpy((char*)0x101000040,(char*)addrs[2],flen(fd[2]));
    memcpy((char*)0x101000000,(char*)addrs[1],flen(fd[1]));
    memcpy((char*)0x102004800,(char*)addrs[0],flen(fd[0]));
    itcs_dcache_flush();
    PrintBuf((char*)0x42004800,8);
//////////////////////////////
    // npu test start
    base = 0xC7000000;
    printf("NPU TEST START!\n"); 

    // npu_test_code start
    MA_OUTW((base + 0x000000), 0x070900);
    MA_OUTW((base + 0x000014), 0x00FFFF);
    MA_OUTW((base + 0x000090), 0x000040);
    MA_OUTW((base + 0x000100), 0x140021);
    MA_OUTW((base + 0x000178), 0x000000);
    MA_OUTW((base + 0x00010C), 0x15B0880);
    MA_OUTW((base + 0x000654), 0x50000000);
    MA_OUTW((base + 0x0003A4), 0x01FFFF);

    rd_val = 0x1;
   while(rd_val != 0x0){
   rd_val = MA_INW((base+0x4)) ^ 0x7fffffff;
    }
    itcs_dcache_invalid();
    int ret = memcmp((char*)0x102000000,(char*)addrs[5],flen(fd[5]));
    close_file_node(fd,6);
    return ret;
    #endif
    return 0;
}

int nn_convolution_int8_test(void)
{
    #if NN8
    uint32_t   rd_val;
    unsigned int base;
   
    char* file_name[]={"nn_convolution_int8_test/nn_convolution_int8_data/mem0.bin",
                        "nn_convolution_int8_test/nn_convolution_int8_data/mem2.bin",
                        "nn_convolution_int8_test/nn_convolution_int8_data/mem3.bin",
                        "nn_convolution_int8_test/nn_convolution_int8_data/mem4.bin",
                        "nn_convolution_int8_test/nn_convolution_int8_data/mem5.bin",
                        "nn_convolution_int8_test/nn_convolution_int8_data/mem6.bin",
                        "nn_convolution_int8_test/nn_convolution_int8_data/result.bin"
                        };
    int fd[7]={0};                  
    unsigned long int addrs[7]={0};                   
    open_file_node(file_name,addrs,fd,7);

    memcpy((char*)0x110000000,(char*)addrs[5],flen(fd[5]));
    memcpy((char*)0x100100800,(char*)addrs[4],flen(fd[4]));
    memcpy((char*)0x1010000c0,(char*)addrs[3],flen(fd[3]));
    memcpy((char*)0x101000040,(char*)addrs[2],flen(fd[2]));
    memcpy((char*)0x101000000,(char*)addrs[1],flen(fd[1]));
    memcpy((char*)0x102000040,(char*)addrs[0],flen(fd[0]));
    itcs_dcache_flush();

    // npu test start
    base = 0xC7000000;
    printf("NPU TEST START!\n"); 

    // npu_test_code start
    MA_OUTW((base + 0x000000), 0x070900);
   
    MA_OUTW((base + 0x000014), 0x00FFFF);

    MA_OUTW((base + 0x000090), 0x000040);
    MA_OUTW((base + 0x000100), 0x140021);
    MA_OUTW((base + 0x000178), 0x000000);
    MA_OUTW((base + 0x00010C), 0x15B0880);
    MA_OUTW((base + 0x000654), 0x50000000);
   
    MA_OUTW((base + 0x0003A4), 0x01FFFF);
    
    rd_val = 0x1;
   while(rd_val != 0x0){
    //  printf("idle reg %x\n",MA_INW(base+0x4));
   rd_val = MA_INW((base+0x4)) ^ 0x7fffffff;
  
    }
     itcs_dcache_invalid();
    PrintBuf((char*)0x102000000,64);
    int ret = memcmp((char*)0x102000000,(char*)addrs[6],flen(fd[6]));
    close_file_node(fd,7);
    return ret;
    #endif
    return 0;
}

int nn_convolution_int16_test(void)
{
    #if NN16
    uint32_t  rd_val;
    unsigned int base; 

    char* file_name[]={"nn_convolution_int16_test/nn_convolution_int16_data/mem0.bin",
                        "nn_convolution_int16_test/nn_convolution_int16_data/mem2.bin",
                        "nn_convolution_int16_test/nn_convolution_int16_data/mem3.bin",
                        "nn_convolution_int16_test/nn_convolution_int16_data/mem4.bin",
                        "nn_convolution_int16_test/nn_convolution_int16_data/mem5.bin",
                        "nn_convolution_int16_test/nn_convolution_int16_data/mem6.bin",
                        "nn_convolution_int16_test/nn_convolution_int16_data/result.bin"
                        };
    int fd[7]={0};                  
    unsigned long int addrs[7]={0};                   
    open_file_node(file_name,addrs,fd,7);
   
    memset((char*)0x42000000,0,128);
    memcpy((char*)0x110000000,(char*)addrs[5],flen(fd[5]));
    memcpy((char*)0x100100800,(char*)addrs[4],flen(fd[4]));
    memcpy((char*)0x1010000c0,(char*)addrs[3],flen(fd[3]));
    memcpy((char*)0x101000040,(char*)addrs[2],flen(fd[2]));
    memcpy((char*)0x101000000,(char*)addrs[1],flen(fd[1]));
    memcpy((char*)0x102000080,(char*)addrs[0],flen(fd[0]));
    itcs_dcache_flush();
   
    // npu test start
    base = 0xC7000000;
    printf("NPU TEST START!\n"); 

    // npu_test_code start
    MA_OUTW((base + 0x000000), 0x070900);
    MA_OUTW((base + 0x000014), 0x00FFFF);
    MA_OUTW((base + 0x000090), 0x000040);
    MA_OUTW((base + 0x000100), 0x140021);
    MA_OUTW((base + 0x000178), 0x000000);
    MA_OUTW((base + 0x00010C), 0x15B0880);
    MA_OUTW((base + 0x000654), 0x50000000);
    MA_OUTW((base + 0x0003A4), 0x01FFFF);

    rd_val = 0x1;
   
   while(rd_val != 0x0){
   rd_val = MA_INW((base+0x4)) ^ 0x7fffffff;
    }
    itcs_dcache_invalid();
    int ret = memcmp((char*)0x102000000,(char*)addrs[6],flen(fd[6]));
    close_file_node(fd,7);
    return ret;
    #endif
    
    return 0;
    
}

int localstorageaccess_new_test(void)
{
    #if LS1 
    uint32_t  rd_val;
    unsigned int base; 

    char* file_name[]={"localstorageaccess_new_test/localstorageaccess_new_data/mem0_cmd_buffer_0.bin",
                        "localstorageaccess_new_test/localstorageaccess_new_data/mem1_cmd_buffer_1.bin",
                        "localstorageaccess_new_test/localstorageaccess_new_data/mem2_cmd_buffer_2.bin",
                        "localstorageaccess_new_test/localstorageaccess_new_data/mem3_shader_buffer.bin",
                        "localstorageaccess_new_test/localstorageaccess_new_data/mem0_result.bin",
                        "localstorageaccess_new_test/localstorageaccess_new_data/mem4_clear_buffer.bin"};
    int fd[6]={0};                  
    unsigned long int addrs[6]={0};                   
    open_file_node(file_name,addrs,fd,6);
 
    memcpy((char*)0x111000000,(char *)addrs[0],flen(fd[0]));
    memcpy((char*)0x111010000,(char *)addrs[1],flen(fd[1]));
    memcpy((char*)0x111020000,(char *)addrs[2],flen(fd[2]));
    memcpy((char*)0x112000000,(char *)addrs[3],flen(fd[3]));
    memcpy((char*)0x114000000,(char *)addrs[5],flen(fd[5]));
    itcs_dcache_flush();
    
//////////////////////////////
    // npu test start
    base = 0xC7000000;
    printf("NPU TEST START!\n"); 

    // npu_test_code start
    MA_OUTW((base + 0x000654), 0x51000000);
    MA_OUTW((base + 0x0003A4), 0x01FFFF);
    MA_OUTW((base + 0x000654), 0x51010000);
    MA_OUTW((base + 0x0003A4), 0x01FFFF);
    MA_OUTW((base + 0x000654), 0x51020000);
    MA_OUTW((base + 0x0003A4), 0x01FFFF);

    rd_val = 0x1;
   while(rd_val != 0x0){
   rd_val = MA_INW((base+0x4)) ^ 0x7fffffff;
    }

   
    // npu_test_code finish
   
    // npu_test_code finish
     itcs_dcache_invalid();
     
     int ret = memcmp((char*)0x114000000,(char*)faddr(fd[4]),128);
     close_file_node(fd,6);
    return ret;
    #endif
    return 0;
}

int localstorageaccess_4core_test(void)
{
    #if LS4
    uint32_t  rd_val;
    unsigned int base; 
   
    char* file_name[]={"localstorageaccess_4core_test/localstorageaccess_4core_data/mem0_cmd_buffer.bin",
                        "localstorageaccess_4core_test/localstorageaccess_4core_data/mem1_shader_buffer.bin",
                        "localstorageaccess_4core_test/localstorageaccess_4core_data/mem2_clear_buffer.bin",
                        "localstorageaccess_4core_test/localstorageaccess_4core_data/mem0_result.bin"
                        };
    int fd[4]={0};                  
    unsigned long int addrs[4]={0};                   
    open_file_node(file_name,addrs,fd,4);

    memcpy((char*)0x111000000,(char *)addrs[0],flen(fd[0]));
    memcpy((char*)0x112000000,(char *)addrs[1],flen(fd[1]));
    memcpy((char*)0x114000000,(char *)addrs[2],flen(fd[2]));
    
    PrintBuf((char*)0x111000000,4);
    PrintBuf((char*)0x112000000,4);
   
 
    itcs_dcache_flush();
//////////////////////////////
    // npu test start
    base = 0xC7000000;
    printf("NPU TEST START!\n"); 

    // npu_test_code start
    MA_OUTW((base + 0x00010C), 0x020000);
    MA_OUTW((base + 0x000654), 0x51000000);
    MA_OUTW((base + 0x0003A4), 0x01FFFF);
    rd_val = 0x1;

    while(rd_val != 0x0){
        rd_val = MA_INW((base+0x4)) ^ 0x7fffffff;
    }
    
    MA_OUTW((base + 0x000654), 0x51000030);
    MA_OUTW((base + 0x0003A4), 0x01FFFF);
    rd_val = 0x1;
    while(rd_val != 0x0){
        rd_val = MA_INW((base+0x4)) ^ 0x7fffffff;
    }

    itcs_dcache_invalid();
    int ret = memcmp((char*)0x114000000,(char*)faddr(fd[3]),128);
    close_file_node(fd,4);
    return ret;
    #endif
    return 0;
}

int localstorageaccess_test(void){
    #if LS2
    uint32_t  rd_val;
    unsigned int base;
    
     char* file_name[]={"localstorageaccess_test/localstorageaccess_data/mem0_cmd_buffer.bin",
                        "localstorageaccess_test/localstorageaccess_data/mem1_shader_buffer.bin",
                        "localstorageaccess_test/localstorageaccess_data/mem2_clear_buffer.bin",
                        "localstorageaccess_test/localstorageaccess_data/mem0_result.bin"
                        };
    int fd[4]={0};                  
    unsigned long int addrs[4]={0};                   
    open_file_node(file_name,addrs,fd,4);

    memcpy((char*)0x111000000,(char *)addrs[0],flen(fd[0]));
    memcpy((char*)0x112000000,(char *)addrs[1],flen(fd[1]));
    memcpy((char*)0x114000000,(char *)addrs[2],flen(fd[2]));
    
  
     itcs_dcache_flush();

    // npu test start
    base = 0xC7000000;
    printf("NPU TEST START!\n"); 

    // npu_test_code start
    MA_OUTW((base + 0x000014), 0xFFFFFFFF);
    MA_OUTW((base + 0x00010C), 0x020000);
    MA_OUTW((base + 0x000654), 0x51000000);
    MA_OUTW((base + 0x0003A4), 0x01FFFF);

    rd_val = 0x1;
   while(rd_val != 0x0){
   rd_val = MA_INW((base+0x4)) ^ 0x7fffffff;
    }
   
    itcs_dcache_invalid();
    int ret = memcmp((char*)0x114000000,(char*)faddr(fd[3]),128);
    close_file_node(fd,4);
    return ret;
    #endif
    return 0;
}

int image_filter_test(void)
{
    #if IFI
    uint32_t  rd_val;
    unsigned int base;

     char* file_name[]={"image_filter_test/image_filter_data/mem0_cmd_buffer.bin",
                        "image_filter_test/image_filter_data/mem1_pshader_buffer.bin",
                        "image_filter_test/image_filter_data/mem2_tex_buffer.bin",
                        "image_filter_test/image_filter_data/mem3_clear_buffer.bin",
                        "image_filter_test/image_filter_data/mem0_result.bin"
                        };
    int fd[5]={0};                  
    unsigned long int addrs[5]={0};                   
    open_file_node(file_name,addrs,fd,5);

    memcpy((char*)0x111000000,(char *)addrs[0],flen(fd[0]));
    memcpy((char*)0x112001000,(char *)addrs[1],flen(fd[1]));
    memcpy((char*)0x114000000,(char *)addrs[2],flen(fd[2]));
    memcpy((char*)0x118000000,(char *)addrs[3],flen(fd[3]));
    
    itcs_dcache_flush();
//////////////////////////////
    // npu test start
    base = 0xC7000000;
    printf("NPU TEST START!\n"); 

    // npu_test_code start
    MA_OUTW((base + 0x000014), 0xFFFFFFFF);
    MA_OUTW((base + 0x000100), 0x140021);
    MA_OUTW((base + 0x000654), 0x51000000);
    MA_OUTW((base + 0x0003A4), 0x010039);

    rd_val = 0x1;
   while(rd_val != 0x0){
   rd_val = MA_INW((base+0x4)) ^ 0x7fffffff;
    }
    
    itcs_dcache_invalid();
    int ret = memcmp((char*)0x118000000,(char*)faddr(fd[4]),flen(fd[4]));
    close_file_node(fd,5);
    return ret;
    #endif
    // npu_test_code finish
    
   
    return 0;
}

int image_blend_12288dw_test(void)
{
    #if IBW
    uint32_t  rd_val;
    unsigned int base;

    char* file_name[]={"image_blend_12288dw_test/image_blend_12288dw_data/mem0_cmd_buffer.bin",
                        "image_blend_12288dw_test/image_blend_12288dw_data/mem1_shader_buffer.bin",
                        "image_blend_12288dw_test/image_blend_12288dw_data/mem2_clear_buffer.bin",
                        "image_blend_12288dw_test/image_blend_12288dw_data/mem3_image_buffer0.bin",
                        "image_blend_12288dw_test/image_blend_12288dw_data/mem4_image_buffer1.bin",
                        "image_blend_12288dw_test/image_blend_12288dw_data/mem0_result.bin"
                        };
    int fd[6]={0};                  
    unsigned long int addrs[6]={0};                   
    open_file_node(file_name,addrs,fd,6);

    memcpy((char*)0x111000000,(char*)faddr(fd[0]),flen(fd[0]));
    memcpy((char*)0x112000000,(char*)faddr(fd[1]),flen(fd[1]));
    memcpy((char*)0x121000000,(char*)faddr(fd[2]),flen(fd[2]));
    memcpy((char*)0x114000000,(char*)faddr(fd[3]),flen(fd[3]));
    memcpy((char*)0x118000000,(char*)faddr(fd[4]),flen(fd[4]));
    itcs_dcache_flush();
//////////////////////////////
    // npu test start
    base = 0xC7000000;
    printf("NPU TEST START!\n"); 

    // npu_test_code start
    MA_OUTW((base + 0x00010C), 0x020000);
    MA_OUTW((base + 0x000654), 0x51000000);
    MA_OUTW((base + 0x0003A4), 0x01FFFF);

    rd_val = 0x1;
   while(rd_val != 0x0){
   rd_val = MA_INW((base+0x4)) ^ 0x7fffffff;
    }
    
    // npu_test_code finish
    itcs_dcache_invalid();
    int ret = memcmp((char*)0x121000000,(char*)faddr(fd[5]),flen(fd[5]));
    close_file_node(fd,6);
    return ret;
    #endif
    return 0;
}

int image_blend_mmu(void){
    #if IBM
    uint32_t  rd_val =0;
    unsigned int base;

    char* file_name[]={"image_blend_mmu_test/image_blend_mmu_data/mem0_cmd_buffer.bin",
                        "image_blend_mmu_test/image_blend_mmu_data/mem4_pshader_buffer.bin",
                        "image_blend_mmu_test/image_blend_mmu_data/mem1_tlb_index_buffer.bin",
                        "image_blend_mmu_test/image_blend_mmu_data/mem2_tlb_buffer.bin",
                        // "mmu_extend4gaddr_test/mmu_extend4gaddr_data/mem4_tlb_index_buffer.bin",
                        // "mmu_extend4gaddr_test/mmu_extend4gaddr_data/mem3_tlb_buffer.bin",
                        "image_blend_mmu_test/image_blend_mmu_data/mem6_image0_buffer.bin",
                        "image_blend_mmu_test/image_blend_mmu_data/mem7_image1_buffer.bin",
                        "image_blend_mmu_test/image_blend_mmu_data/mem0_result.bin"
                        };
    int fd[7]={0};                  
    unsigned long int addrs[7]={0};                   
    open_file_node(file_name,addrs,fd,7);
    memset((char*)0x121000000,0,1228800);
    
    memcpy((char*)0x110000000,(char*)faddr(fd[0]),flen(fd[0]));
    memcpy((char*)0x10a000000,(char*)faddr(fd[1]),flen(fd[1]));
    
    memcpy((char*)0x160000000,(char*)faddr(fd[2]),flen(fd[2]));
    memcpy((char*)0x151000000,(char*)faddr(fd[3]),flen(fd[3]));
    memcpy((char*)0x114000000,(char*)faddr(fd[4]),flen(fd[4]));
    memcpy((char*)0x118000000,(char*)faddr(fd[5]),flen(fd[5]));
    memset((char*)0x15fffbcf0,0,256);
    
    //memset((char*)0x44000000,0,4096);
    
    itcs_dcache_flush();
    // PrintBuf((char*)0x1510007f8,8);
    // PrintBuf((char*)0x160000000,8);
    // PrintBuf((char*)0x110000040,16);
    // PrintBuf((char*)0x110000258,8);
//////////////////////////////
    // npu test start
    base = 0xC7000000;
    printf("NPU TEST START!\n"); 

    // npu_test_code start
    MA_OUTW((base + 0x000014), 0xFFFFFFFF);
    MA_OUTW((base + 0x000100), 0x140021);
    MA_OUTW((base + 0x00038C), 0x60000000);//tlb_index
   
    MA_OUTW((base + 0x000398), 0x5fFFBCF0);//save_zone
    MA_OUTW((base + 0x00039C), 0x5fFFBCF0);//
    MA_OUTW((base + 0x000390), 0x000001);
    MA_OUTW((base + 0x000654), 0x50000000);
    printf("cmd buffer = %x\n",MA_INW(base+0x664));
    MA_OUTW((base + 0x0003A4), 0x010005);
      while(rd_val != 0x0){
     rd_val = MA_INW((base+0x4)) ^ 0x7fffffff;
    }
    MA_OUTW((base + 0x000388), 0x000001);
    MA_OUTW((base + 0x000654), 0x10000040);
    printf("cmd buffer = %x\n",MA_INW(base+0x664));
    MA_OUTW((base + 0x0003A4), 0x01FFFF);

    rd_val = 0x1;
   while(rd_val != 0x0){
        rd_val = MA_INW((base+0x4)) ^ 0x7fffffff;
    }
   
    itcs_dcache_invalid();
    
    PrintBuf((char*)0x121000000,16);
    int ret = memcmp((char*)0x121000000,(char*)faddr(fd[6]),flen(fd[6]));
    close_file_node(fd,7);
    return ret;
    #endif
    return 0;
}

int mask_image_test(void){
    #if MS 
    uint32_t  rd_val;
    unsigned int base; 
   
    char* file_name[]={"mask_image_test/mask_image_data/mem0_cmd_buffer.bin",
                        "mask_image_test/mask_image_data/mem1_vshader_buffer.bin",
                        "mask_image_test/mask_image_data/mem2_clear_buffer.bin",
                        "mask_image_test/mask_image_data/mem3_input_buffer.bin",
                        "mask_image_test/mask_image_data/mem0_result.bin"
                        };
    int fd[5]={0};                  
    unsigned long int addrs[5]={0};                   
    open_file_node(file_name,addrs,fd,5);

    memcpy((char*)0x111000000,(char *)addrs[0],flen(fd[0]));
    memcpy((char*)0x112000000,(char *)addrs[1],flen(fd[1]));
    memcpy((char*)0x121000000,(char *)addrs[2],flen(fd[2]));
    memcpy((char*)0x113000000,(char *)addrs[3],flen(fd[3]));
 
    itcs_dcache_flush();
//////////////////////////////
    // npu test start
    base = 0xC7000000;
    printf("NPU TEST START!\n"); 
    
    // npu_test_code start
    MA_OUTW((base + 0x00010C), 0x020000);
    MA_OUTW((base + 0x000654), 0x51000000);
    MA_OUTW((base + 0x0003A4), 0x01011C);
  
    rd_val = 0x1;
   while(rd_val != 0x0){
   rd_val = MA_INW((base+0x4)) ^ 0x7fffffff;
    }
    itcs_dcache_invalid();
    
    int ret = memcmp((char*)0x121000000,(char*)faddr(fd[4]),flen(fd[4]));
    close_file_node(fd,5);
    return ret;
    #endif
    return 0;
}

int ddr_bw_write_only_test(void)
{
    
    uint32_t  rd_val;
    unsigned int base; 
    
   
    char* file_name[]={"ddr_bw_test_write_only_test/ddr_bw_test_write_only_data/mem0_cmd_buffer.bin",
                        "ddr_bw_test_write_only_test/ddr_bw_test_write_only_data/mem1_shader_buffer.bin"                
                        };
    int fd[2]={0};                  
    unsigned long int addrs[2]={0};                   
    open_file_node(file_name,addrs,fd,2);
   

    //memset((char*)0x43000000,1,)
    //memset((char*)0x41400000,0,sizeof(mem1_vshader_buffer_bin));
    memset((char*)0x113000000,0,6144000);
    memset((char*)0x114000000,0,6144000);
    memcpy((char*)0x111000000,(char*)faddr(fd[0]),flen(fd[0]));
    memcpy((char*)0x112000000,(char*)faddr(fd[1]),flen(fd[1]));
  
    itcs_dcache_flush();
 
    // npu test start
    base = 0xC7000000;
    printf("NPU TEST START!\n"); 

    // npu_test_code start
    MA_OUTW((base + 0x000014), 0xFFFFFFFF);
  
    MA_OUTW((base + 0x00010C), 0x200000);
    MA_OUTW((base + 0x000100), 0x140021);
   
    MA_OUTW((base + 0x000654), 0x51000000);
    MA_OUTW((base + 0x0003A4), 0x010022);
    
    rd_val = 0x1;
   while(rd_val != 0x0){
   rd_val = MA_INW((base+0x4)) ^ 0x7fffffff;
    }
    
    itcs_dcache_invalid();
    int ret = memcmp((char*)0x114000000,(char*)0x113000000,6144000);
    close_file_node(fd,4);
    return ret;
}

int ddr_bw_write_read_test(void)
{
    
    uint32_t  rd_val;
    unsigned int base; 
   char* file_name[]={"ddr_bw_test_read_write_test/ddr_bw_test_read_write_data/mem0_cmd_buffer.bin",
                        "ddr_bw_test_read_write_test/ddr_bw_test_read_write_data/mem1_shader_buffer.bin"
                        };
    int fd[2]={0};                  
    unsigned long int addrs[2]={0};                   
    open_file_node(file_name,addrs,fd,2);
   
    memcpy((char*)0x111000000,(char*)faddr(fd[0]),flen(fd[0]));
    memcpy((char*)0x112000000,(char*)faddr(fd[1]),flen(fd[1]));
    memset((char*)0x113000000,0,6144000);
    memset((char*)0x114000000,0,6144000);
    itcs_dcache_flush();
    printf("restore\n");
    //udelay(6000*1000);
    

//////////////////////////////
    // npu test start
    base = 0xC7000000;
    printf("NPU TEST START!\n"); 
    printf("reg power ctl = %x\n",MA_INW(base+0x100));
    // npu_test_code start
    MA_OUTW((base + 0x000014), 0xFFFFFFFF);
    printf("interrupt reg = %x\n",MA_INW(base+0x014));
    MA_OUTW((base + 0x00010C), 0x200000);
    MA_OUTW((base + 0x000100), 0x140021);
    printf("idle reg = %x\n",MA_INW(base+0x04));
    MA_OUTW((base + 0x000654), 0x51000000);
    MA_OUTW((base + 0x0003A4), 0x010022);

    rd_val = 0x1;
   while(rd_val != 0x0){
   rd_val = MA_INW((base+0x4)) ^ 0x7fffffff;
    }
   
    itcs_dcache_invalid();
    // npu_test_code finish
    int ret =  memcmp((char*)0x114000000,(char*)0x113000000,6144000);
    close_file_node(fd,2);
    return ret;
    //return 0;
}

int ddr_bw_read_only_test(void){
    
     uint32_t  rd_val;
    unsigned int base; 
  
     char* file_name[]={"ddr_bw_test_read_only/mem0_cmd_buffer.bin",
                        "ddr_bw_test_read_only/mem1_shader_buffer.bin"
                        };
    int fd[2]={0};                  
    unsigned long int addrs[2]={0};                   
    open_file_node(file_name,addrs,fd,2);
    
    memcpy((char*)0x111000000,(char*)faddr(fd[0]),flen(fd[0]));
    memcpy((char*)0x112000000,(char*)faddr(fd[1]),flen(fd[1]));
    memset((char*)0x113000000,0,6144000);
    memset((char*)0x114000000,0,6144000);
    itcs_dcache_flush();
//////////////////////////////
    // npu test start
    base = 0xC7000000;
    printf("NPU TEST START!\n"); 
    
    // npu_test_code start
    MA_OUTW((base + 0x000014), 0xFFFFFFFF);
    
    MA_OUTW((base + 0x00010C), 0x200000);
    MA_OUTW((base + 0x000100), 0x140021);
    
    MA_OUTW((base + 0x000654), 0x51000000);
    MA_OUTW((base + 0x0003A4), 0x010022);

    rd_val = 0x1;
   while(rd_val != 0x0){
   rd_val = MA_INW((base+0x4)) ^ 0x7fffffff;
    }
   
    itcs_dcache_invalid();
    // npu_test_code finish
    int ret = memcmp((char*)0x114000000,(char*)0x113000000,6144000);
    close_file_node(fd,2);
    return ret;
}

int mmu_extend4gaddr_test(void){
    #if MMU_ET
    uint32_t  rd_val = 0;
    unsigned int base; 
    
    //mem0 0x40001000
      char* file_name[]={"mmu_extend4gaddr_test/mmu_extend4gaddr_data/mem0_cmd_buffer_before_mmu.bin",
                        "mmu_extend4gaddr_test/mmu_extend4gaddr_data/mem1_src_buffer.bin",
                        "mmu_extend4gaddr_test/mmu_extend4gaddr_data/mem2_shader_inst_buffer.bin",
                        "mmu_extend4gaddr_test/mmu_extend4gaddr_data/mem3_tlb_buffer.bin",
                        "mmu_extend4gaddr_test/mmu_extend4gaddr_data/mem4_tlb_index_buffer.bin",
                        "mmu_extend4gaddr_test/mmu_extend4gaddr_data/mem5_safezone_buffer.bin",
                        "mmu_extend4gaddr_test/mmu_extend4gaddr_data/mem6_cmd_buffer_after_mmu.bin",
                        "mmu_extend4gaddr_test/mmu_extend4gaddr_data/mem0_result.bin"
                        };
    int fd[8]={0};                  
    unsigned long int addrs[8]={0};                   
    open_file_node(file_name,addrs,fd,8);
//////////////////////////////
    //memset((char*)0x54000000,0,4096);
    //input 42000000 result 44000000 shader 43000000 120000000
    memcpy((char*)0x110000100,(char*)faddr(fd[1]),flen(fd[1]));
    memcpy((char*)0x10a000000,(char*)faddr(fd[2]),flen(fd[2]));
    memcpy((char*)0x120001000,(char*)faddr(fd[0]),flen(fd[0]));
    memcpy((char*)0x120001018,(char*)faddr(fd[6]),flen(fd[6]));
    memcpy((char*)0x160000000,(char*)faddr(fd[4]),flen(fd[4]));
    memcpy((char*)0x151000000,(char*)faddr(fd[3]),flen(fd[3]));
    memcpy((char*)0x151FFBCF0,(char*)faddr(fd[5]),flen(fd[5]));
    memset((char*)0x54000000,0,4096);
    itcs_dcache_flush();
 
    printf("restore\n");
   
    base = 0xC7000000;
    printf("NPU TEST START!\n"); 
    // npu_test_code start
    MA_OUTW((base + 0x000014), 0xFFFFFFFF);
    MA_OUTW((base + 0x000100), 0x140021);
    MA_OUTW((base + 0x00038C), 0x60000000);//50000001,
    MA_OUTW((base + 0x000390), 0x000001);

    MA_OUTW((base + 0x000398), 0x51FFBCF0);
    MA_OUTW((base + 0x00039C), 0x51FFBCF0);
    MA_OUTW((base + 0x000654), 0x60001000);
    // printf("cmd reg =%x\n",MA_INW(base+0x664));
    MA_OUTW((base + 0x0003A4), 0x010003);
    while(rd_val != 0x0){
     rd_val = MA_INW((base+0x4)) ^ 0x7fffffff;
    }
    //itcs_dcache_flush();
    MA_OUTW((base + 0x0003AC), 0x000000);
    MA_OUTW((base + 0x000388), 0x000001);
   
    MA_OUTW((base + 0x000654), 0x20001018);
    //itcs_dcache_flush();
    MA_OUTW((base + 0x0003A4), 0x01FFFF);
   
    rd_val = 0x1;
   while(rd_val != 0x0){
   rd_val = MA_INW((base+0x4)) ^ 0x7fffffff;
    }
    
    itcs_dcache_invalid();
    PrintBuf((char*)0x114000000,16);
    int ret = memcmp((char*)0x114000000,(char*)faddr(fd[7]),flen(fd[7]));
    close_file_node(fd,8);
    return ret;
    #endif
 
    return 0;
}

int npu_show_usage(void){
    printf("Usage: npu [OPTION]...\n\n");
	printf("-h, --help\t\tcommand help\n");
	printf("-s1, \t\tnpu shared copy test\n");
	printf("-s2, \t\tnpu shared copy ram2hit test\n");
	printf("-ntp, \t\tnn transpose test\n");
	printf("-ntd, \t\tnn tensoradd test\n");
    printf("-pq, \t\tnn perchquantization test\n");
    printf("-m32, \t\tnn mmu 32bit test\n");
    printf("-mt, \t\tnn max ot test\n");
    printf("-k1, \t\tnn kernel 1*1 test\n");
    printf("-k3, \t\tnn kernel 3*3 test\n");
    printf("-ndw, \t\tnn ddr write test\n");
    printf("-ndr, \t\tnn ddr read test\n");
    printf("-c8, \t\tnn convolution int8 test\n");
    printf("-c16, \t\tnn convolution int16 test\n");
    printf("-me, \t\tmmu extent4gaddr test\n");
    printf("-ls1, \t\tlocalstorageaccess test\n");
    printf("-ls1, \t\tlocalstorageaccess new test\n");
    printf("-ls4, \t\tlocalstorageaccess 4core test\n"); 
    printf("-ifi, \t\timage filter test\n");
    printf("-mi, \t\tmask image test\n");
    printf("-ibw, \t\timage blend 12288dw test\n");
    printf("-ibm, \t\timage blend mmu test\n");
    printf("-bw, \t\tddr bw write only test\n");
    printf("-brw, \t\tddr bw write read test\n");
  
    return 0;

}
#if 1
int npu_2core_ddr1(){
    unsigned int base0 = 0xC7000000;
    unsigned int base1 = 0xC7800000;

//     // NPU TEST START

    // npu_test_code start
    printf("npu yolov5s_id3_2core_ddr1_DV test start!\n"); 

    MA_OUTW((base0 + 0x000078),0);
    MA_OUTW((base1 + 0x000078),0);
    MA_OUTW((base0 + 0x00007C),0);
    MA_OUTW((base1 + 0x00007C),0);
    printf("base0:0x000078 = %d \n" , MA_INW((base0 + 0x000078))); 

    MA_OUTW((base0 + 0x000000), 0x070900);
    MA_OUTW((base0 + 0x000104), 0x000000);
    MA_OUTW((base0 + 0x00010C), 0x15A0881);
    MA_OUTW((base0 + 0x00010C), 0x15A0880);
    MA_OUTW((base0 + 0x000000), 0x070B00);
    MA_OUTW((base0 + 0x000000), 0x070900);
    MA_OUTW((base0 + 0x000000), 0x0F0900);
    MA_OUTW((base0 + 0x0003A8), 0x000001);
    MA_OUTW((base0 + 0x0003A8), 0x000000);
    MA_OUTW((base0 + 0x000000), 0x0F0900);
    MA_OUTW((base0 + 0x000000), 0x070900);
    MA_OUTW((base0 + 0x000004), 0x000000);
    MA_INW((base0 + 0x000004));
    MA_INW((base0 + 0x000000));
    MA_INW((base0 + 0x000388));
    MA_OUTW((base0 + 0x000104), 0x000000);
    MA_OUTW((base0 + 0x00010C), 0x15A0881);
    MA_OUTW((base0 + 0x00010C), 0x15A0880);
    MA_OUTW((base0 + 0x000000), 0x070B00);
    MA_OUTW((base0 + 0x000000), 0x070900);
    MA_OUTW((base0 + 0x000000), 0x0F0900);
    MA_OUTW((base0 + 0x0003A8), 0x000001);
    MA_OUTW((base0 + 0x0003A8), 0x000000);
    MA_OUTW((base0 + 0x000000), 0x0F0900);
    MA_OUTW((base0 + 0x000000), 0x070900);
    MA_INW((base0 + 0x000004));
    MA_INW((base0 + 0x000000));
    MA_INW((base0 + 0x000388));
    MA_OUTW((base0 + 0x00055C), 0xFFFFFF);
    MA_OUTW((base0 + 0x000090), 0x000000);
    MA_OUTW((base1 + 0x000000), 0x070900);
    MA_OUTW((base1 + 0x000104), 0x000000);
    MA_OUTW((base1 + 0x00010C), 0x15A0881);
    MA_OUTW((base1 + 0x00010C), 0x15A0880);
    MA_OUTW((base1 + 0x000000), 0x070B00);
    MA_OUTW((base1 + 0x000000), 0x070900);
    MA_OUTW((base1 + 0x000000), 0x0F0900);
    MA_OUTW((base1 + 0x0003A8), 0x000001);
    MA_OUTW((base1 + 0x0003A8), 0x000000);
    MA_OUTW((base1 + 0x000000), 0x0F0900);
    MA_OUTW((base1 + 0x000000), 0x070900);
    MA_INW((base1 + 0x000004));
    MA_INW((base1 + 0x000000));
    MA_INW((base1 + 0x000388));
    MA_OUTW((base1 + 0x000104), 0x000000);
    MA_OUTW((base1 + 0x00010C), 0x15A0881);
    MA_OUTW((base1 + 0x00010C), 0x15A0880);
    MA_OUTW((base1 + 0x000000), 0x070B00);
    MA_OUTW((base1 + 0x000000), 0x070900);
    MA_OUTW((base1 + 0x000000), 0x0F0900);
    MA_OUTW((base1 + 0x0003A8), 0x000001);
    MA_OUTW((base1 + 0x0003A8), 0x000000);
    MA_OUTW((base1 + 0x000000), 0x0F0900);
    MA_OUTW((base1 + 0x000000), 0x070900);
    MA_INW((base1 + 0x000004));
    MA_INW((base1 + 0x000000));
    MA_INW((base1 + 0x000388));
    MA_OUTW((base1 + 0x00055C), 0xFFFFFF);
    MA_OUTW((base1 + 0x000090), 0x000000);
    MA_OUTW((base0 + 0x000000), 0x070900);
    MA_OUTW((base0 + 0x000000), 0x070100);
    MA_OUTW((base0 + 0x0003A8), 0x000002);
    MA_OUTW((base0 + 0x00003C), 0xFFFFFFFF);
    MA_OUTW((base0 + 0x00003C), 0x000000);
    MA_OUTW((base0 + 0x000100), 0x140021);
    MA_OUTW((base0 + 0x000104), 0x000000);
    MA_OUTW((base0 + 0x00010C), 0x15A0880);
    MA_OUTW((base0 + 0x000090), 0x000040);
    MA_OUTW((base0 + 0x000414), 0x000000);
    MA_OUTW((base0 + 0x000014), 0xFFFFFFFF);
    MA_OUTW((base1 + 0x000000), 0x070900);
    MA_OUTW((base1 + 0x000000), 0x070100);
    MA_OUTW((base1 + 0x0003A8), 0x000002);
    MA_OUTW((base1 + 0x00003C), 0xFFFFFFFF);
    MA_OUTW((base1 + 0x00003C), 0x000000);
    MA_OUTW((base1 + 0x000100), 0x140021);
    MA_OUTW((base1 + 0x000104), 0x000000);
    MA_OUTW((base1 + 0x00010C), 0x15A0880);
    MA_OUTW((base1 + 0x000090), 0x000040);
    MA_OUTW((base1 + 0x000414), 0x000000);
    MA_OUTW((base1 + 0x000014), 0xFFFFFFFF);
    MA_OUTW((base0 + 0x0003B4), 0x1100020);
    MA_OUTW((base0 + 0x0003B4), 0x1FFFF01);
    MA_OUTW((base0 + 0x000388), 0x000021);
    MA_OUTW((base0 + 0x000654), 0x25005000);
    MA_OUTW((base0 + 0x0003A4), 0x010015);
    udelay(5000);
    MA_OUTW((base1 + 0x0003B4), 0x1200020);
    MA_OUTW((base1 + 0x000388), 0x000021);
    MA_OUTW((base1 + 0x000654), 0x25005000);
    MA_OUTW((base1 + 0x0003A4), 0x010015);
    udelay(5000);
    int rd_val = 0x1;
   while(rd_val != 0x0){
   rd_val = MA_INW((base0+0x4)) ^ 0x7fffffff;
    }
    rd_val = 0x1;
   while(rd_val != 0x0){
   rd_val = MA_INW((base1+0x4)) ^ 0x7fffffff;
    }
    MA_OUTW((base0 + 0x000654), 0x259A6030);
    MA_OUTW((base0 + 0x0003A4), 0x01025B);
    udelay(50);
    MA_OUTW((base1 + 0x000654), 0x259A6030);
    MA_OUTW((base1 + 0x0003A4), 0x01025B);
    rd_val = 0x1;
    udelay(100);
   while(rd_val != 0x0){
   rd_val = MA_INW((base0+0x4)) ^ 0x7fffffff;
    }
    rd_val = 0x1;
   while(rd_val != 0x0){
   rd_val = MA_INW((base1+0x4)) ^ 0x7fffffff;
    }

    // npu_perf_test_init(NULL);
    // npu_perf_test_start(0);
    udelay(5000);
    // npu_perf_test_start(1);
    // while(npu_perf_test_get_status(0) == 0 ){

    // }
  
     rd_val = MA_INW((base0 + 0x000078));
    printf("base0:0x000078 = %d \n" , rd_val); 
     rd_val = MA_INW((base0 + 0x00007C));
    printf("base0:0x00007c = %d \n" , rd_val); 
    // while(!npu_perf_test_get_status(1) == 0){
        
    // }
    rd_val = MA_INW((base1 + 0x000078));
    printf("base1:0x000078 = %d \n" , rd_val);
    rd_val = MA_INW((base1 + 0x00007c));
    printf("base1:0x00007c = %d \n" , rd_val);
    printf("npu test finish!\n"); 
    return 0;
}
#endif
int npu_main(int argc,char *argv[]){
    int ret = 0;
    int test_case = -1;
    
    
    // clock_config();
    set_npu_clock();
    // set_all_npu();
    if (strncmp(argv[1], "-s1", 3) == 0) {
        test_case = SHARED_COPY;
    } else if (strncmp(argv[1], "-s2", 3) == 0) {
        test_case = SHARED_COPY_R2H;
    } else if (strncmp(argv[1], "-ntp", 4) == 0) {
        test_case = TRANSPOSE;
    } else if (strncmp(argv[1], "-ntd", 4) == 0) {
        test_case = TENSORADD;
    } else if (strncmp(argv[1], "-pq", 3) == 0) {
        test_case = PERQUANTIZATION;
    } else if (strncmp(argv[1], "-m32", 4) == 0) {
        test_case = MMU_32BIT;
    } else if (strncmp(argv[1], "-mt", 3) == 0) {
        test_case = MAX_OT;
    } else if (strncmp(argv[1], "-k1", 3) == 0) {
        test_case = KERNEL_1;
    } else if (strncmp(argv[1], "-k3", 3) == 0) {
        test_case = KERNEL_3;
    } else if (strncmp(argv[1], "-ndw", 4) == 0) {
        test_case = DDR_WRITE;
    } else if (strncmp(argv[1], "-ndr", 4) == 0){
        test_case = DDR_READ;
    }else if (strncmp(argv[1], "-c8", 3) == 0){
        test_case = CONVOLUTION_INT8;
    }else if (strncmp(argv[1], "-c16", 4) == 0){
        test_case = CONVOLUTION_INT16;
    }else if (strncmp(argv[1], "-me", 3) == 0){
        test_case = EXTENT4GADDR;
    }else if (strncmp(argv[1], "-ls2", 4) == 0){
        test_case = LSTORAGE_NEW;
    }else if (strncmp(argv[1], "-ls4", 4) == 0){
        test_case = LSTORAGE_4CORE;
    }else if (strncmp(argv[1], "-ifi", 4) == 0){
        test_case = IMAGE_FILTER;
    }else if (strncmp(argv[1], "-ibw", 4) == 0){
        test_case = IMAGE_BLEND_DW;
    }else if (strncmp(argv[1], "-bw", 3) == 0){
        test_case = BW_WRITE;
    }else if (strncmp(argv[1], "-brw", 4) == 0){
        test_case = BW_WRITE_READ;
    }else if(strncmp(argv[1],"-ibm",4)==0){
        test_case = IMAGE_BLEND_MMU;
    }else if(strncmp(argv[1],"-ls1",3)==0){
        test_case=LSTORAGE;
    }else if(strncmp(argv[1],"-br",3)==0){
        test_case=BW_READ;
    }else if(strncmp(argv[1],"-mi",3)==0){
        test_case=MASK_IMAGE;
    }else if(strncmp(argv[1],"-network",8)==0){
        test_case = NETWORK_LENET;
    }else if(strncmp(argv[1],"-yolo",5)==0){
        
        test_case = NETWORK_YOLOV5;
    }else if(strncmp(argv[1],"-ppabs",6)==0){
        
        test_case = PPU_ABSDIFF;
    }else if(strncmp(argv[1],"-ppwaf",6)==0){
        test_case = PPU_WARPAFFINE;
        
    }else if(strncmp(argv[1],"-ids_yolov5s",12) == 0){
        
        test_case = NETWORK_YOLOV_ALGO;
    }else if(strncmp(argv[1],"-ppu_yolov5s",12) == 0){
        
        test_case = NETWORK_YOLOV_PPU;
    }else if(strncmp(argv[1],"-core2_yolov5",13) == 0){
        
        test_case = NETWORK_YOLOV_CORE2;
    }else{}
    itcs_dcache_flush();
    printf("test begin\n");

    switch (test_case) {
        case SHARED_COPY:
            printf("shared copy test\n");
           
            ret = shared_copy_test();
            printf("shared copy test");            
            break;
        case SHARED_COPY_R2H:
            printf("shared copy ram2hit test\n");
            ret = shared_copy_ram2hit_test();
            printf("shared copy ram2hit test");
            break;
        case TRANSPOSE:
            printf("nn transpose test\n");
            ret = nn_transpose_test();
            printf("nn transpose test");
            break;
        case TENSORADD:
            printf("nn tensoradd test\n");
            ret = nn_tensoradd_test();
            printf("nn tensoradd test");
            break;
        case PERQUANTIZATION:
            printf("nn perchquantization test\n");
            ret = nn_perchquantization_test();
            printf("nn perchquantization test");
            break;
        case MMU_32BIT:
            printf("nn mmu 32bit test\n");
            ret = nn_mmu_32bit_test();
            printf("nn mmu 32bit test");
            break;
        case MAX_OT:
            printf("nn max ot test\n");
            ret = nn_max_ot_test();
            printf("nn max ot test");
            break;
        case KERNEL_1:
            printf("nn kernel 1*1 test\n");
            ret = nn_kernel_1_1_test();
            printf("nn kernel 1*1 test");
            break;
        case KERNEL_3:
            printf("nn kernel 3*3 test\n");
            ret = nn_kernel_3_3_test();
            printf("nn kernel 3*3 test");
            break;
        case DDR_WRITE:
            printf("nn ddr write test\n");
            ret = nn_ddr_write_test();
            printf("nn ddr write test");
            break;
        case DDR_READ:
            printf("nn ddr read test\n");
            ret = nn_ddr_read_test();
            printf("nn ddr read test");
            break;
        case CONVOLUTION_INT8:
            printf("nn convolution int8 test\n");
            ret = nn_convolution_int8_test();
            printf("nn convolution int8 test");
            break;
        case CONVOLUTION_INT16:
            printf("nn convolution int16 test\n");
            ret = nn_convolution_int16_test();
            printf("nn convolution int16");
            break;
        case EXTENT4GADDR:
            printf("nn extent4gaddr test\n");
            ret = mmu_extend4gaddr_test();
            printf("nn extent4gaddr test");
            break;
        case LSTORAGE_NEW:
            printf("localstorageaccess new test\n");
            ret = localstorageaccess_new_test();
            printf("localstorageaccess new test");
            break;
        case LSTORAGE_4CORE:
            printf("localstorageaccess 4core test\n");
            ret = localstorageaccess_4core_test();
            printf("localstorageaccess 4core test");
            break;
        case IMAGE_FILTER:
            printf("image filter test\n");
            ret = image_filter_test();
            printf("image filter test");
            break;
        case IMAGE_BLEND_DW:
            printf("image blend 12288dw test\n");
            ret = image_blend_12288dw_test();
            printf("image blend 12288dw");
            break;
        case MASK_IMAGE:
            printf("mask image test\n");
            ret = mask_image_test();
            printf("mask image");
            break;
        case BW_WRITE:
            printf("ddr dw write only test\n");
            ret = ddr_bw_write_only_test();
            printf("ddr dw write only test");
            break;
        case BW_WRITE_READ:
            printf("ddr dw write read test\n");
            ret = ddr_bw_write_read_test();
            printf("ddr dw write read");
            break;
        case BW_READ:
            printf("ddr bw write read only\n");
            ret = ddr_bw_read_only_test();
            printf("ddr bw write read");
            break;
        case LSTORAGE:
            printf("localstorageaccess test\n");
            ret = localstorageaccess_test();
            printf("localstorageaccess test");
            break;
        case IMAGE_BLEND_MMU:
            printf("image blend mmu test\n");
            ret = image_blend_mmu();
            printf("image blend mmu");
            break;
        case NETWORK_LENET:
            printf("network lenet test\n");
            ret = NetworkLenet();

            printf("network lenet");
            break;
        case NETWORK_YOLOV5:
            printf("network yolov5 test\n");
            // ret = NetworkYolov5_new(682);
            // ret = Test_proformence();
            printf("network yolov");
            break;
        case NETWORK_YOLOV_ALGO:
            printf("network yolov5s test\n");
            // ret = NetworkYolov5_3_21_algorithm();
            // ret = Test_proformence();
            printf("network yolov5s");
            break;
        case NETWORK_YOLOV_PPU:
            printf("ppu yolov5s test\n");
            // ret = yolov5_ppu();
            printf("ppu yolov5s");
            break;
        case PPU_ABSDIFF:
            printf("ppu absdiff test\n");
            ret = ppu_absdiff_test();
            printf("ppu absdiff");
            break;
        case PPU_WARPAFFINE:
            printf("ppu warpaffine test\n");
            ret = ppu_warp_affine();
            printf("ppu warpaffine");
            break;
        case NETWORK_YOLOV_CORE2:
            printf("core2 yolov5s test\n");
            ret = npu_2core_ddr1();
            printf("core2 yolov5s");
            break;
        default:
            npu_show_usage();
            ret = -1;
    }
    if(ret==0){
        printf(" Pass\n");
        
    }else{
        //printf("ret = %d",ret);
        printf(" Failed\n");
    }
    return ret;
}


int yolov5s_id3_core_DV(){

    unsigned int base0 = 0xc7000000; 
    //  unsigned int base1 = 0xc7800000;
     MA_OUTW((base0 + 0x000078),0);
     npu_input_file_batch("yolov5s_id3_DV_data/mem",0,265);
    printf("npu yolov5s_core0_DV test start!\n");
    MA_OUTW((base0 + 0x000000), 0x070900);
        MA_OUTW((base0 + 0x000104), 0x000000);
        MA_OUTW((base0 + 0x00010C), 0x15A0881);
        MA_OUTW((base0 + 0x00010C), 0x15A0880);
        MA_OUTW((base0 + 0x000000), 0x070B00);
        MA_OUTW((base0 + 0x000000), 0x070900);
        MA_OUTW((base0 + 0x000000), 0x0F0900);
        MA_OUTW((base0 + 0x0003A8), 0x000001);
        MA_OUTW((base0 + 0x0003A8), 0x000000);
        MA_OUTW((base0 + 0x000000), 0x0F0900);
        MA_OUTW((base0 + 0x000000), 0x070900);
        MA_INW((base0 + 0x000004));
        MA_INW((base0 + 0x000000));
        MA_INW((base0 + 0x000388));
        MA_OUTW((base0 + 0x000104), 0x000000);
        MA_OUTW((base0 + 0x00010C), 0x15A0881);
        MA_OUTW((base0 + 0x00010C), 0x15A0880);
        MA_OUTW((base0 + 0x000000), 0x070B00);
        MA_OUTW((base0 + 0x000000), 0x070900);
        MA_OUTW((base0 + 0x000000), 0x0F0900);
        MA_OUTW((base0 + 0x0003A8), 0x000001);
        MA_OUTW((base0 + 0x0003A8), 0x000000);
        MA_OUTW((base0 + 0x000000), 0x0F0900);
        MA_OUTW((base0 + 0x000000), 0x070900);
        MA_INW((base0 + 0x000004));
        MA_INW((base0 + 0x000000));
        MA_INW((base0 + 0x000388));
        MA_OUTW((base0 + 0x00055C), 0xFFFFFF);
        MA_OUTW((base0 + 0x000090), 0x000000);
        MA_OUTW((base0 + 0x000000), 0x070900);
        MA_OUTW((base0 + 0x000000), 0x070100);
        MA_OUTW((base0 + 0x0003A8), 0x000002);
        MA_OUTW((base0 + 0x00003C), 0xFFFFFFFF);
        MA_OUTW((base0 + 0x00003C), 0x000000);
        MA_OUTW((base0 + 0x000100), 0x140021);
        MA_OUTW((base0 + 0x000104), 0x000000);
        MA_OUTW((base0 + 0x00010C), 0x15A0880);
        MA_OUTW((base0 + 0x000090), 0x000040);
        MA_OUTW((base0 + 0x000414), 0x000000);
        MA_OUTW((base0 + 0x000014), 0xFFFFFFFF);
#ifdef CONFIG_TB_RUN_DDR1
            MA_OUTW((base0 + 0x0003B4), 0x5100020);
#else
            MA_OUTW((base0 + 0x0003B4), 0x1100020);
#endif
        MA_OUTW((base0 + 0x000388), 0x000021);
        MA_OUTW((base0 + 0x000654), 0x25005000);
        MA_OUTW((base0 + 0x0003A4), 0x010013);
        // udelay(100);
        int rd_val = 0x1;
      
        while(rd_val != 0x0){
            rd_val = MA_INW((base0+0x4)) ^ 0x7fffffff;
        }
        printf("-------------phase 1  finish--------\n");
        MA_OUTW((base0 + 0x000654), 0x259A6030);
        MA_OUTW((base0 + 0x0003A4), 0x01025B);
        udelay(100);
        rd_val = 0x1;
          
        while(rd_val != 0x0){
            rd_val = MA_INW((base0+0x4)) ^ 0x7fffffff;
        }
         rd_val = MA_INW((base0 + 0x000078));
        printf("0x000078 = %d \n" , rd_val); 
         rd_val = MA_INW((base0 + 0x00007C));
        printf("0x00007C = %d \n" , rd_val); 
        printf("npu test finish!\n");
        
         soc_dump0(0x100000000 + 0x11609000, 0x000639c0);
         soc_dump0(0x100000000 + 0x1166d000, 0x00018e70);
         soc_dump0(0x100000000 + 0x11686000, 0x0018e700);
        // printf("npu test finish!\n"); 
    return 0;
}


void yolov5_id3_core0_DV(int64_t core_clk){

        unsigned int base0 = 0xc7000000; 
        // unsigned int base1 = 0xc7800000;
        npu_input_file_batch("yolov5s_id3_2core_DV_data/mem",0,265);

        printf("npu yolov5s_core0_DV test start!\n");
        
        MA_OUTW((base0 + 0x000078),0);
        MA_OUTW((base0 + 0x000000), 0x070900);
        MA_OUTW((base0 + 0x000104), 0x000000);
        MA_OUTW((base0 + 0x00010C), 0x15A0881);
        MA_OUTW((base0 + 0x00010C), 0x15A0880);
        MA_OUTW((base0 + 0x000000), 0x070B00);
        MA_OUTW((base0 + 0x000000), 0x070900);
        MA_OUTW((base0 + 0x000000), 0x0F0900);
        MA_OUTW((base0 + 0x0003A8), 0x000001);
        MA_OUTW((base0 + 0x0003A8), 0x000000);
        MA_OUTW((base0 + 0x000000), 0x0F0900);
        MA_OUTW((base0 + 0x000000), 0x070900);
        MA_INW((base0 + 0x000004));
        MA_INW((base0 + 0x000000));
        MA_INW((base0 + 0x000388));
        MA_OUTW((base0 + 0x000104), 0x000000);
        MA_OUTW((base0 + 0x00010C), 0x15A0881);
        MA_OUTW((base0 + 0x00010C), 0x15A0880);
        MA_OUTW((base0 + 0x000000), 0x070B00);
        MA_OUTW((base0 + 0x000000), 0x070900);
        MA_OUTW((base0 + 0x000000), 0x0F0900);
        MA_OUTW((base0 + 0x0003A8), 0x000001);
        MA_OUTW((base0 + 0x0003A8), 0x000000);
        MA_OUTW((base0 + 0x000000), 0x0F0900);
        MA_OUTW((base0 + 0x000000), 0x070900);
        MA_INW((base0 + 0x000004));
        MA_INW((base0 + 0x000000));
        MA_INW((base0 + 0x000388));
        MA_OUTW((base0 + 0x00055C), 0xFFFFFF);
        MA_OUTW((base0 + 0x000090), 0x000000);
    
        MA_OUTW((base0 + 0x000000), 0x070900);
        MA_OUTW((base0 + 0x000000), 0x070100);
        MA_OUTW((base0 + 0x0003A8), 0x000002);
        MA_OUTW((base0 + 0x00003C), 0xFFFFFFFF);
        MA_OUTW((base0 + 0x00003C), 0x000000);
        MA_OUTW((base0 + 0x000100), 0x140021);
        MA_OUTW((base0 + 0x000104), 0x000000);
        MA_OUTW((base0 + 0x00010C), 0x15A0880);
        MA_OUTW((base0 + 0x000090), 0x000040);
        MA_OUTW((base0 + 0x000414), 0x000000);
        MA_OUTW((base0 + 0x000014), 0xFFFFFFFF);
  
#ifdef CONFIG_TB_RUN_DDR1
            MA_OUTW((base0 + 0x0003B4), 0x5100020);
#else
            MA_OUTW((base0 + 0x0003B4), 0x1100020);
#endif 
        MA_OUTW((base0 + 0x000388), 0x000021);
        MA_OUTW((base0 + 0x000654), 0x25005000);
        MA_OUTW((base0 + 0x0003A4), 0x010013);
        
        // udelay(100);
        int rd_val = 0x1;
        while(rd_val != 0x0){
            rd_val = MA_INW((base0+0x4)) ^ 0x7fffffff;
        }

       
        MA_OUTW((base0 + 0x000654), 0x259A6030);
        MA_OUTW((base0 + 0x0003A4), 0x01025B);
        itcs_hwmon_print_one_info(0, 11);

        // udelay(100);
        rd_val = 0x1;
        
        while(rd_val != 0x0){
            rd_val = MA_INW((base0+0x4)) ^ 0x7fffffff;
        }
       
        rd_val = MA_INW((base0 + 0x000078));

        // cul_ddr_ratio(rd_val);
       
        printf("npu0 0x000078 = %d \n" , rd_val);    
        printf("npu0 fps %d\n",core_clk/rd_val);
        printf("npu test finish!\n"); 
        soc_dump0(0x100000000 + 0x11609000, 0x000639c0);
        soc_dump0(0x100000000 + 0x1166d000, 0x00018e70);
        soc_dump0(0x100000000 + 0x11686000, 0x0018e700);

        npu_compare("result.bin");
        // cul_ddr_ratio();
       
}

void yolov5s_id3_2core_DV(int64_t core_clk){

        unsigned int base0 = 0xc7000000; 
        unsigned int base1 = 0xc7800000;
        npu_input_file_batch("yolov5s_id3_2core_DV_data/mem",0,531);

    printf("npu yolov5s_core0_DV test start!\n");
        MA_OUTW((base0 + 0x000078),0);
     
        MA_OUTW((base0 + 0x000000), 0x070900);
        MA_OUTW((base0 + 0x000104), 0x000000);
        MA_OUTW((base0 + 0x00010C), 0x15A0881);
        MA_OUTW((base0 + 0x00010C), 0x15A0880);
        MA_OUTW((base0 + 0x000000), 0x070B00);
        MA_OUTW((base0 + 0x000000), 0x070900);
        MA_OUTW((base0 + 0x000000), 0x0F0900);
        MA_OUTW((base0 + 0x0003A8), 0x000001);
        MA_OUTW((base0 + 0x0003A8), 0x000000);
        MA_OUTW((base0 + 0x000000), 0x0F0900);
        MA_OUTW((base0 + 0x000000), 0x070900);
        MA_INW((base0 + 0x000004));
        MA_INW((base0 + 0x000000));
        MA_INW((base0 + 0x000388));
        MA_OUTW((base0 + 0x000104), 0x000000);
        MA_OUTW((base0 + 0x00010C), 0x15A0881);
        MA_OUTW((base0 + 0x00010C), 0x15A0880);
        MA_OUTW((base0 + 0x000000), 0x070B00);
        MA_OUTW((base0 + 0x000000), 0x070900);
        MA_OUTW((base0 + 0x000000), 0x0F0900);
        MA_OUTW((base0 + 0x0003A8), 0x000001);
        MA_OUTW((base0 + 0x0003A8), 0x000000);
        MA_OUTW((base0 + 0x000000), 0x0F0900);
        MA_OUTW((base0 + 0x000000), 0x070900);
        MA_INW((base0 + 0x000004));
        MA_INW((base0 + 0x000000));
        MA_INW((base0 + 0x000388));
        MA_OUTW((base0 + 0x00055C), 0xFFFFFF);
        MA_OUTW((base0 + 0x000090), 0x000000);
    
        MA_OUTW((base0 + 0x000000), 0x070900);
        MA_OUTW((base0 + 0x000000), 0x070100);
        MA_OUTW((base0 + 0x0003A8), 0x000002);
        MA_OUTW((base0 + 0x00003C), 0xFFFFFFFF);
        MA_OUTW((base0 + 0x00003C), 0x000000);
        MA_OUTW((base0 + 0x000100), 0x140021);
        MA_OUTW((base0 + 0x000104), 0x000000);
        MA_OUTW((base0 + 0x00010C), 0x15A0880);
        MA_OUTW((base0 + 0x000090), 0x000040);
        MA_OUTW((base0 + 0x000414), 0x000000);
        MA_OUTW((base0 + 0x000014), 0xFFFFFFFF);
  
#ifdef CONFIG_TB_RUN_DDR1
            MA_OUTW((base0 + 0x0003B4), 0x5100020);
#else
            MA_OUTW((base0 + 0x0003B4), 0x1100020);
#endif 

        MA_OUTW((base0 + 0x000388), 0x000021);
        MA_OUTW((base0 + 0x000654), 0x25005000);
        MA_OUTW((base0 + 0x0003A4), 0x010013);

        // udelay(100);
        int rd_val = 0x1;
        while(rd_val != 0x0){
            rd_val = MA_INW((base0+0x4)) ^ 0x7fffffff;
        }

   
        MA_OUTW((base0 + 0x000654), 0x259A6030);
        MA_OUTW((base0 + 0x0003A4), 0x01025B);


        // printf("-------------phase 0  finish--------\n");
        MA_OUTW((base0 + 0x000654), 0x259A6030);
        MA_OUTW((base0 + 0x0003A4), 0x01025B);
        udelay(100);
        rd_val = 0x1;
        

        // printf("npu yolov5s_id3_core1_DV test start!\n"); 
       
        MA_OUTW((base1 + 0x000078),0);

        MA_OUTW((base1 + 0x000000), 0x070900);
        MA_OUTW((base1 + 0x000104), 0x000000);
        MA_OUTW((base1 + 0x00010C), 0x15A0881);
        MA_OUTW((base1 + 0x00010C), 0x15A0880);
        MA_OUTW((base1 + 0x000000), 0x070B00);
        MA_OUTW((base1 + 0x000000), 0x070900);
        MA_OUTW((base1 + 0x000000), 0x0F0900);
        MA_OUTW((base1 + 0x0003A8), 0x000001);
        MA_OUTW((base1 + 0x0003A8), 0x000000);
        MA_OUTW((base1 + 0x000000), 0x0F0900);
        MA_OUTW((base1 + 0x000000), 0x070900);
        MA_INW((base1 + 0x000004));
        MA_INW((base1 + 0x000000));
        MA_INW((base1 + 0x000388));
        MA_OUTW((base1 + 0x000104), 0x000000);
        MA_OUTW((base1 + 0x00010C), 0x15A0881);
        MA_OUTW((base1 + 0x00010C), 0x15A0880);
        MA_OUTW((base1 + 0x000000), 0x070B00);
        MA_OUTW((base1 + 0x000000), 0x070900);
        MA_OUTW((base1 + 0x000000), 0x0F0900);
        MA_OUTW((base1 + 0x0003A8), 0x000001);
        MA_OUTW((base1 + 0x0003A8), 0x000000);
        MA_OUTW((base1 + 0x000000), 0x0F0900);
        MA_OUTW((base1 + 0x000000), 0x070900);
        MA_INW((base1 + 0x000004));
        MA_INW((base1 + 0x000000));
        MA_INW((base1 + 0x000388));
        MA_OUTW((base1 + 0x00055C), 0xFFFFFF);
        MA_OUTW((base1 + 0x000090), 0x000000);
   
        
  
        MA_OUTW((base1 + 0x000000), 0x070900);
        MA_OUTW((base1 + 0x000000), 0x070100);
        MA_OUTW((base1 + 0x0003A8), 0x000002);
        MA_OUTW((base1 + 0x00003C), 0xFFFFFFFF);
        MA_OUTW((base1 + 0x00003C), 0x000000);
        MA_OUTW((base1 + 0x000100), 0x140021);
        MA_OUTW((base1 + 0x000104), 0x000000);
        MA_OUTW((base1 + 0x00010C), 0x15A0880);
        MA_OUTW((base1 + 0x000090), 0x000040);
        MA_OUTW((base1 + 0x000414), 0x000000);
        MA_OUTW((base1 + 0x000014), 0xFFFFFFFF);

#ifdef CONFIG_TB_RUN_DDR1
            MA_OUTW((base1 + 0x0003B4), 0x5200020);
#else
            MA_OUTW((base1 + 0x0003B4), 0x1200020);
#endif
        MA_OUTW((base1 + 0x000388), 0x000021);
        MA_OUTW((base1 + 0x000654), 0x25005000);
        MA_OUTW((base1 + 0x0003A4), 0x010013);

        rd_val = 0x1;        
        // udelay(100);
        while(rd_val != 0x0){
            rd_val = MA_INW((base1+0x4)) ^ 0x7fffffff;
        }

        MA_OUTW((base1 + 0x000654), 0x259A6030);
        MA_OUTW((base1 + 0x0003A4), 0x01025B);

        // udelay(100);
       
        rd_val = 0x1;
        while(rd_val != 0x0){
            rd_val = MA_INW((base1+0x4)) ^ 0x7fffffff;
        }

         while(rd_val != 0x0){
            rd_val = MA_INW((base0+0x4)) ^ 0x7fffffff;
        }
      
        
        rd_val = MA_INW((base0 + 0x000078));
        printf("npu0 0x000078 = %d , %d fps\n" , rd_val,core_clk/rd_val);    
        rd_val = MA_INW((base1 + 0x000078));
        printf("npu1 0x000078 = %d , %d fps\n" , rd_val,core_clk/rd_val);
        printf("npu test finish!\n"); 
        soc_dump0(0x100000000 + 0x11609000, 0x000639c0);
        soc_dump0(0x100000000 + 0x1166d000, 0x00018e70);
        soc_dump0(0x100000000 + 0x11686000, 0x0018e700);
        soc_dump0(0x100000000 + 0x21609000, 0x000639c0);
        soc_dump0(0x100000000 + 0x2166d000, 0x00018e70);
        soc_dump0(0x100000000 + 0x21686000, 0x0018e700);

        // cul_ddr_ratio(0);
        npu_compare("result.bin");
   
}


void yolov5s_id3_core1_DV(int64_t core_clk){

    npu_input_file_batch("yolov5s_id3_2core_DV_data/mem",266,531);
    // npu_input_file_batch("yolov5s_id3_2core_DV_data/mem",0,265);
        // unsigned int base0 = 0xc7000000; 
        unsigned int base1 = 0xc7800000;
        // MA_OUTW((base0 + 0x000078),0);
        MA_OUTW((base1 + 0x000078),0);
    printf("npu yolov5s_id3_core1_DV test start!\n"); 
       
    
        MA_OUTW((base1 + 0x000000), 0x070900);
        MA_OUTW((base1 + 0x000104), 0x000000);
        MA_OUTW((base1 + 0x00010C), 0x15A0881);
        MA_OUTW((base1 + 0x00010C), 0x15A0880);
        MA_OUTW((base1 + 0x000000), 0x070B00);
        MA_OUTW((base1 + 0x000000), 0x070900);
        MA_OUTW((base1 + 0x000000), 0x0F0900);
        MA_OUTW((base1 + 0x0003A8), 0x000001);
        MA_OUTW((base1 + 0x0003A8), 0x000000);
        MA_OUTW((base1 + 0x000000), 0x0F0900);
        MA_OUTW((base1 + 0x000000), 0x070900);
        MA_INW((base1 + 0x000004));
        MA_INW((base1 + 0x000000));
        MA_INW((base1 + 0x000388));
        MA_OUTW((base1 + 0x000104), 0x000000);
        MA_OUTW((base1 + 0x00010C), 0x15A0881);
        MA_OUTW((base1 + 0x00010C), 0x15A0880);
        MA_OUTW((base1 + 0x000000), 0x070B00);
        MA_OUTW((base1 + 0x000000), 0x070900);
        MA_OUTW((base1 + 0x000000), 0x0F0900);
        MA_OUTW((base1 + 0x0003A8), 0x000001);
        MA_OUTW((base1 + 0x0003A8), 0x000000);
        MA_OUTW((base1 + 0x000000), 0x0F0900);
        MA_OUTW((base1 + 0x000000), 0x070900);
        MA_INW((base1 + 0x000004));
        MA_INW((base1 + 0x000000));
        MA_INW((base1 + 0x000388));
        MA_OUTW((base1 + 0x00055C), 0xFFFFFF);
        MA_OUTW((base1 + 0x000090), 0x000000);
   
        
  
        MA_OUTW((base1 + 0x000000), 0x070900);
        MA_OUTW((base1 + 0x000000), 0x070100);
        MA_OUTW((base1 + 0x0003A8), 0x000002);
        MA_OUTW((base1 + 0x00003C), 0xFFFFFFFF);
        MA_OUTW((base1 + 0x00003C), 0x000000);
        MA_OUTW((base1 + 0x000100), 0x140021);
        MA_OUTW((base1 + 0x000104), 0x000000);
        MA_OUTW((base1 + 0x00010C), 0x15A0880);
        MA_OUTW((base1 + 0x000090), 0x000040);
        MA_OUTW((base1 + 0x000414), 0x000000);
        MA_OUTW((base1 + 0x000014), 0xFFFFFFFF);
   

#ifdef CONFIG_TB_RUN_DDR1
            MA_OUTW((base1 + 0x0003B4), 0x5200020);
#else
            MA_OUTW((base1 + 0x0003B4), 0x1200020);
#endif
        MA_OUTW((base1 + 0x000388), 0x000021);
        MA_OUTW((base1 + 0x000654), 0x25005000);
        MA_OUTW((base1 + 0x0003A4), 0x010013);

    
        int rd_val = 0x1;
        
        udelay(100);
        
        while(rd_val != 0x0){
            rd_val = MA_INW((base1+0x4)) ^ 0x7fffffff;
        }
        MA_OUTW((base1 + 0x000654), 0x259A6030);
        MA_OUTW((base1 + 0x0003A4), 0x01025B);

       itcs_hwmon_print_one_info(0, 12);
   
        udelay(100);
        rd_val = 0x1;
        while(rd_val != 0x0){
            rd_val = MA_INW((base1+0x4)) ^ 0x7fffffff;
        }

        // rd_val = MA_INW((base0 + 0x000078));
        // printf("0x000078 = %d \n" , rd_val); 
       
        rd_val = MA_INW((base1 + 0x000078));
       
        printf("npu1 0x000078 = %d \n" , rd_val);   
        printf("npu1 fps %d\n",core_clk/rd_val);
        printf("npu test finish!\n"); 

        soc_dump0(0x100000000 + 0x21609000, 0x000639c0);
        soc_dump0(0x100000000 + 0x2166d000, 0x00018e70);
        soc_dump0(0x100000000 + 0x21686000, 0x0018e700);

        npu_compare("result.bin");
        // npu_test_code finish
}

void clk_up_test(void (*func)()){
   
    for(int i = 3; i < 4; i++){
        itcs_pll_set_clock(CPU, "cpll", clk_fre[i][0], false);
        int64_t clock_fre= itcs_pll_get_clock(CPU,"cpll");
        
        itcs_module_set_clock(CPU, "vip0", "cpll", clk_fre[i][1], false);
        itcs_module_set_clock(CPU, "vip1", "cpll", clk_fre[i][1], false);
        MA_OUTW(0xc2f082d4,0x1);
        printf("npu0 clk %ld ,npu1 clk %ld ,cpll %ld\n",itcs_module_get_clock(CPU,"vip0"),itcs_module_get_clock(CPU,"vip1"),clock_fre);
        func(clk_fre[i][1]);
    }
}

void power_up_set(int index){
    //soc vol
    int vol = 0;
    pmic_vol_set(0, "dcdc2", power_vol[index][1]);

    pmic_vol_get(0,"dcdc2",&vol);
    
    printf("SOC vol set %d\n",vol);

    pmic_vol_set(1, "page1", power_vol[index][0]);
    pmic_vol_get(0,"page1",&vol);

    printf("NPU vol set %d\n",vol);

}


int npu_complete(int argc,char *argv[]){
    printf("---npu 9200O test---\n");
    // request_npu_irq(0);
    // request_npu_irq(1);
    // request_mpu_irq(0);
    
    
    // request_mpu_irq(MPU_0_IRQ);
    itcs_module_set_clock(CPU, "vip0", "cpll", 1008000000, false);
    itcs_module_set_clock(CPU, "vip1", "cpll", 1008000000, false);
    

    // itcs_pll_set_clock(CPU,"epll",1392000000,false);
    // // // itcs_pll_set_clock(CPU,"bpll",1296000000,false);

    // itcs_module_set_clock(CPU,"bus4","epll",696000000,false);
    // itcs_module_set_clock(CPU,"bus5","epll",696000000,false);
    // // itcs_module_set_clock(CPU,"bus6","bpll",648000000,false);
    // // // MA_OUTW(0xc2f08104,0x1);
    // // // MA_OUTW(0xc2f08114,0x1);
    // int64_t ral_clock = itcs_module_get_clock(CPU,"vip0");
    // printf("npu clk %ld\n",ral_clock);
    // ral_clock = itcs_module_get_clock(CPU,"bus5");
    // printf("bus5 clk %ld\n",ral_clock);
    // ral_clock = itcs_module_get_clock(CPU,"bus6");
    // printf("bus6 clk %ld\n",ral_clock);
    // ral_clock = itcs_module_get_clock(CPU,"bus4");
    // printf("bus4 clk %ld\n",ral_clock);
    // ral_clock = itcs_pll_get_clock(CPU,"epll");
    // printf("epll clk %ld\n",ral_clock);
    // ral_clock = itcs_pll_get_clock(CPU,"bpll");
    // printf("bpll clk %ld\n",ral_clock);

    
    npu_init_config();
    // npu_perf_test_init(NULL);
    // npu_input_file_batch("yolov5s_id3_2core_DV_data/mem",0,531);
    // npu_perf_test_start(5,50);
    // int rd_val = MA_INW((0xc7000000 + 0x000078));
    
    // printf("npu0 0x000078 = %d \n" , rd_val);  

    if(strncmp(argv[1], "init",  strlen(argv[1])) == 0){
        npu_close_config();
        return 0;
    }
    if( argc != 2){
        printf("please input correct argv\n");
         npu_close_config();
        return 0;
    }
    npu_9200_evb_test(argv[1]);
    npu_close_config();
// #else
//     npu_only_rtl(argv[1]);
// #endif
   
    return 0;
}
void npu_init(void){
    // register_testbench("npu",npu_main,NULL);
#if TEST_NPU_LITE
    register_testbench("npu",npu_main,NULL);
#else 
    register_testbench("npu",npu_complete,NULL);
#endif
    
    }
testbench_init(npu_init);


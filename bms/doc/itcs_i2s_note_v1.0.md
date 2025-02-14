# I2s相关接口说明

## 头文件
```c
#include <i2s.h>
```
## 接口说明

* i2s初始化
  
```c
I2S_HandleDef* itcs_i2s_init(I2S_InitDef* init);
```

i2s初始化函数
参数列表:  
|参数名|参数说明|
|--|--|
|I2S_InitDef|指向I2S初始化配置结构体|
|返回值|返回I2S结构体指针|

结构体说明：
1. I2S_InitDef

参数列表:  
|参数名|参数说明|
|--|--|
|i2sidx|i2s索引|
|mode| 设置全双工半双工下Master和Slave模式:<br>I2S_MODE_MASTER： 半双工Master<br>   I2S_MODE_SLAVE： 半双工Slave<br> I2S_MODE_FULL_DUPLEX_MASTER :全双工Master<br> I2S_MODE_FULL_DUPLEX_SLAVE：全双工Slave|
|standard|设置I2S标准： <br>    I2S_PHILIPS_STANDRAD_MODE<br> I2S_LEFT_JUSTIFIED_MODE<br>    I2_RIGHT_JUSTIFIED_MODE<br>   I2S_DSP_MODE <br>I2S_TDM_MODE|
|channel|信道类型：<br>  I2S_MONO:单声道 <br> I2S_STEREO：立体声<br>  I2S_TDM:TDM模式|
|chnwidth|信道位宽：<br>I2S_CHN_WIDTH_8BIT: 8BIT位宽 <br>I2S_CHN_WIDTH_16BIT: 16BIT位宽<br> I2S_CHN_WIDTH_24BIT: 24BIT位宽<br> I2S_CHN_WIDTH_32BIT: 32BIT位宽|
|sample_resolution|采样精度：<br>I2S_SAMPLE_8BIT:8BIT精度<br> I2S_SAMPLE_16BIT:16BIT精度<br> I2S_SAMPLE_24BIT:24BIT精度<br> I2S_SAMPLE_32BIT:32BIT精度|
|audio_sample_freq|音频采样频率|
|use_dmaflag|dma传输标志|
|use_tdm_chn_num|使用tdm的信道数目|
 


* i2s写
  
```c
uint8_t itcs_i2s_write(I2S_HandleTypeDef *i2sHandler, uint8_t *buf, uint8_t len,BlockFlag isblocked)
```

参数列表:  
|参数名|参数说明|
|--|--|
|I2S_HandleDef|指向I2S结构体指针|
|buf|指向写缓存指针|
|len|写的字节长度|
|isblocked|阻塞模式标记:<br> BLOCK:阻塞 <br>NONBLOCK:非阻塞
|返回值|返回值说明|
|0   |写入成功|
|-1   |写入失败|

* i2s读
  
```c
uint8_t itcs_i2s_read(I2S_HandleTypeDef *i2sHandler, uint8_t *buf, uint8_t len,BlockFlag isblocked) 
```

参数列表:  
|参数名|参数说明|
|--|--|
|I2S_HandleDef|指向I2S结构体指针|
|buf|指向读缓存指针|
|len|读的字节长度|
|isblocked|阻塞模式标记:<br> BLOCK:阻塞 <br>NONBLOCK:非阻塞 
|返回值|返回值说明|
|0  |成功|
|-1  |失败|

```c
uint8_t itcs_set_i2s_samples_resolution(I2S_HandleTypeDef *i2sHandler,i2s_sample_resolution_e sample_resolution)
```

参数列表:  
|参数名|参数说明|
|--|--|
|I2S_HandleDef|指向I2S结构体指针|
|sample_resolution|采样精度值: <br> I2S_SAMPLE_8BIT:8BIT <br> I2S_SAMPLE_16BIT:16BIT <br> I2S_SAMPLE_24BIT:24BIT <br>I2S_SAMPLE_32BIT:32BIT|
|返回值|返回值说明|
|0   |成功|
|-1  |失败|

```c
uint8_t itcs_set_i2s_samplerate(I2S_HandleTypeDef *i2sHandler,uint32_t audio_sample_freq,i2s_chn_width_e chn_width,   i2s_channel_type channel)
```

参数列表:  
|参数名|参数说明|
|--|--|
|I2S_HandleDef|指向I2S结构体指针|
|audio_sample_freq|音频采样频率 KHZ|
|chn_width|位宽:<br> I2S_CHN_WIDTH_8BIT: 8BIT位宽 <br>I2S_CHN_WIDTH_16BIT: 16BIT位宽<br> I2S_CHN_WIDTH_24BIT: 24BIT位宽<br> I2S_CHN_WIDTH_32BIT: 32BIT位宽 |
|channel|信道类型：<br>  I2S_MONO:单声道 <br> I2S_STEREO：立体声 <br> I2S_TDM:TDM模式 |
|返回值|返回值说明|
|0   |成功|
|-1   |失败|

```c
int itcs_i2s_is_completed(I2S_HandleTypeDef *i2sHandler)
```
参数列表:  
|参数名|参数说明|
|--|--|
|I2S_HandleDef|指向I2S结构体指针|
|0   |成功|
|-1   |空指针或者异常|


## 示例代码

```c
#include <common.h>
#include <command.h>
#include <testbench.h>
#include <malloc.h>
#include <asm/io.h>
#include <getopt.h>
#include <i2s.h>
#include <riscv/core_rv64.h>
I2S_InitDef init_set0;
I2S_InitDef init_set1;
uint8_t readdata[BUFFERSIZE];
uint8_t writedata[BUFFERSIZE];

extern int i2s_is_completed(I2S_HandleTypeDef *i2sHandler);
extern uint8_t itcs_i2s_write(I2S_HandleTypeDef *i2sHandler, uint8_t *buf,
                              uint8_t len, BlockFlag isblocked);
extern uint8_t itcs_i2s_read(I2S_HandleTypeDef *i2sHandler, uint8_t *buf,
                             uint8_t len, BlockFlag isblocked);
extern I2S_HandleTypeDef *itcs_i2s_init(I2S_InitDef *init);

uint8_t config_i2s_parameter_buf(uint8_t masterindex, uint8_t slaveindex,
                                 uint8_t i2s_standard, uint8_t i2s_halffull,
                                 uint8_t i2s_dma,
                                 i2s_testcase_group_e testcase_group_e) {
  /* 每次设置的时候初始化数据*/
  memset(readdata, 0, BUFFERSIZE);
  for (int i = 0; i < BUFFERSIZE; i++) {
    writedata[i] = i;
  }

  if (i2s_dma == 0) {
    init_set0.use_dmaflag = 0;
    init_set1.use_dmaflag = 0;

  } else {
    init_set0.use_dmaflag = 1;
    init_set1.use_dmaflag = 1;
  }

  init_set0.chnwidth = I2S_CHN_WIDTH_32BIT;
  init_set0.standard = i2s_standard;
  init_set1.standard = i2s_standard;

  /*I2S0: MASTER,I2S1: SLAVE  I2S的编号和SET集一致*/
  if (i2s_halffull == 0 && masterindex == 0 && slaveindex == 1) {
    init_set0.i2sidx = I2S0;
    init_set1.i2sidx = I2S1;
    switch (testcase_group_e) {
    case MASTER_W_SLAVE_R:
      init_set0.mode = I2S_MODE_MASTER;
      init_set1.mode = I2S_MODE_SLAVE;
      break;

    case SLAVE_W_MASTER_R:
      init_set0.mode = I2S_MODE_MASTER;
      init_set1.mode = I2S_MODE_SLAVE;
      break;
    default:
      return FAIL;
    }
  }
  /*I2S0: SLAVE  I2S1: MASTER  */
  if (i2s_halffull == 0 && masterindex == 1 && slaveindex == 0) {
    init_set0.i2sidx = I2S0;
    init_set1.i2sidx = I2S1;
    switch (testcase_group_e) {
    case MASTER_W_SLAVE_R:
      init_set0.mode = I2S_MODE_SLAVE;
      init_set1.mode = I2S_MODE_MASTER;
      break;
    case SLAVE_W_MASTER_R:
      init_set0.mode = I2S_MODE_SLAVE;
      init_set1.mode = I2S_MODE_MASTER;
      break;
    default:
      return FAIL;
    }
  }

  if (i2s_halffull == 1 && masterindex == 0 && slaveindex == 1) {
    init_set0.mode = I2S_MODE_FULL_DUPLEX_MASTER;
    init_set1.mode = I2S_MODE_FULL_DUPLEX_SLAVE;
  }
  if (i2s_halffull == 1 && masterindex == 1 && slaveindex == 0) {
    init_set0.mode = I2S_MODE_FULL_DUPLEX_SLAVE;
    init_set1.mode = I2S_MODE_FULL_DUPLEX_MASTER;
  }

  return SUCCESS;
};

uint8_t config_i2s_common_parameter() {
  init_set0.chnwidth          = I2S_CHN_WIDTH_32BIT;
  init_set0.sample_resolution = I2S_SAMPLE_24BIT;
  init_set0.channel           = I2S_STEREO;
  init_set0.audio_sample_freq = 16000;

  init_set1.chnwidth          = I2S_CHN_WIDTH_32BIT;
  init_set1.sample_resolution = I2S_SAMPLE_24BIT;
  init_set1.channel           = I2S_STEREO;
  init_set1.audio_sample_freq = 16000;
  return SUCCESS;
}

uint8_t test_i2s_readwrite(uint8_t masterindex, uint8_t slaveindex,
                           uint8_t i2s_standard, uint8_t i2s_halffull,
                           uint8_t i2s_dma,
                           i2s_testcase_group_e testcase_group_e) {

  int timeout          = 5000;
  uint8_t flagcomplete = 0;
  uint8_t ret;
  char *testgroup_string = "";
  char *duplex_string    = "";
  char *standard_string  = "";
  char *dma_string       = "";
  uint8_t i2s_readdataidx = 0; /*用于标记读数据的I2S的编号 打印中区分使用
                                  根据读写区分自动获取I2S编号*/
  uint8_t i2s_writedataidx = 0; /*用于标记写数据的I2S的编号 打印中区分使用
                                   根据读写区分自动获取I2S编号*/
  ret = config_i2s_common_parameter();
  // CHECK_I2S_TESTCASE_COMMON_PARA(ret);
  ret = config_i2s_parameter_buf(masterindex, slaveindex, i2s_standard,
                                 i2s_halffull, i2s_dma, testcase_group_e);
  switch (i2s_standard) {
  case 0:
    standard_string = "PHLIPS MODE";
    break;
  case 1:
    standard_string = "I2S LEFT JUSTIFIED MODE";
    break;
  case 2:
    standard_string = "I2S RIGHT JUSTIFIED MODE";
    break;
  case 3:
    standard_string = "I2S DSP MODE";
    break;
  case 4:
    standard_string = "I2S TDM MODE";
    break;
  default:
    break;
  }
  if (i2s_dma) {
    dma_string = "DMA support";
    printf("%s\n", dma_string);
  }
  if (testcase_group_e == MASTER_W_SLAVE_R) {
    testgroup_string = "Master Write Slave Read Case 1";
  }
  if (testcase_group_e == SLAVE_W_MASTER_R) {
    testgroup_string = "Slave Write Master Read Case 2";
  }
  I2S_HandleTypeDef *test_i2s0_handler = itcs_i2s_init(&init_set0);
  I2S_HandleTypeDef *test_i2s1_handler = itcs_i2s_init(&init_set1);
  if (i2s_halffull == 0) {
    duplex_string = "HAL-DUPLEX";
      if (testcase_group_e == MASTER_W_SLAVE_R) {
        printf("enter MASTER WRITE -SLAVE READ mode \n");
        i2s_readdataidx  = init_set1.i2sidx;
        i2s_writedataidx = init_set0.i2sidx;
        itcs_i2s_read(test_i2s1_handler, readdata, BUFFERSIZE, NONBLOCK);
        itcs_i2s_write(test_i2s0_handler, writedata, BUFFERSIZE, BLOCK);
       } else if (testcase_group_e == SLAVE_W_MASTER_R) {
        printf("enter SLAVE READ -MASTER WRITE mode \n");
        i2s_readdataidx  = init_set0.i2sidx;
        i2s_writedataidx = init_set1.i2sidx;
        itcs_i2s_read(test_i2s0_handler, readdata, BUFFERSIZE, NONBLOCK);
        itcs_i2s_write(test_i2s1_handler, writedata, BUFFERSIZE, BLOCK);
       } else {
        printf("EXCEPTION CONDITION 2\n");
        return FAIL;
      }
  } else {
    if(testcase_group_e ==FULL_DUPLEX_WR) {
        duplex_string = "DUPLEX";
        itcs_i2s_read(test_i2s0_handler, readdata, BUFFERSIZE, NONBLOCK);
        itcs_i2s_write(test_i2s1_handler, writedata, BUFFERSIZE, NONBLOCK);

        itcs_i2s_read(test_i2s1_handler, readdata, BUFFERSIZE, NONBLOCK);
        itcs_i2s_write(test_i2s0_handler, writedata, BUFFERSIZE, NONBLOCK);
      }
    }
  while (1) {
    if (timeout < 0) {
      break;
    }
    if (itcs_i2s_is_completed(test_i2s0_handler) == 0 ||
        itcs_i2s_is_completed(test_i2s1_handler) == 0) {
      flagcomplete = 1;
      break;
    }
    timeout--;
  }
  if (flagcomplete == 1) {
    ret = memcmp(readdata, writedata, BUFFERSIZE);
    if (i2s_halffull == 0) {
      if (ret == 0) {
        printf("Debug Test Case %s ,%s mode i2s%d read data and i2s%d write data is equal Pass!",
               testgroup_string, duplex_string, i2s_readdataidx,
               i2s_writedataidx);
        printf("I2S HALF-Duplex Mode read write data equal Pass!",
              testgroup_string, duplex_string, i2s_readdataidx,
              i2s_writedataidx);       
        return SUCCESS;
      } else {
        printf("Debug Test Case %s ,%s mode i2s%d read data and i2s%d write data is not equal Fail!",
               testgroup_string, duplex_string, i2s_readdataidx,
               i2s_writedataidx);
        return FAIL;
      }
    } else if (i2s_halffull == 1) {
      if (ret == 0) {
        printf("I2S Duplex Mode,%s standard read write data is equal Pass!",
               standard_string);
        return SUCCESS;
      } else {
        printf("I2S Duplex Mode,%s standard read write data is not equal Fail!",
               standard_string);
        return FAIL;
      }
    } else {
      printf("EXCEPTION CONDITON 1\n");
      return FAIL;
    }
    return FAIL;
  } else {
    printf("Test Fail Data not Transfer Finish！\n");
    return FAIL;
  }
  return FAIL;
}

int i2s_main(int argc, char *argv[]) {

  int masterindex = 0;       /* master的索引*/
  int slaveindex = 1;        /* slave的索引*/
  int fullhalfindex = 1;     /* 全双工: 1  半双工:0*/
  int dmaindex = 0;          /* 0:不支持DMA  1:支持DMA*/
  int standardindex = 1;     /* 0:PHILPS 1：LEFT 2:RIGHT 3:DSP 4:TDM */
  if(fullhalfindex==0) {
    test_i2s_readwrite(masterindex, slaveindex, standardindex, fullhalfindex,
                        dmaindex, MASTER_W_SLAVE_R);
    test_i2s_readwrite(masterindex, slaveindex, standardindex, fullhalfindex,
                        dmaindex, SLAVE_W_MASTER_R);}
  else if(fullhalfindex==1) {
        test_i2s_readwrite(masterindex, slaveindex, standardindex, fullhalfindex,
                        dmaindex, FULL_DUPLEX_WR);
  }else{
      printf("parameters  not in range!\n");
  }
  
  return 0; 
}
```

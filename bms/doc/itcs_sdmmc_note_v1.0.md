# SDMMC相关公共接口说明

## 头文件

```c
#include <sdmmc.h>
```

## 相关数据结构



## 接口说明

* SDMMC驱动初始化
	```c 
	SDMMC_Handler *itcs_sdmmc_init(SDMMC_InitTypeDef *init);
	```
	|参数/返回值|说明|
	|--|--|
	|init| 初始化结构体，见上述SDMMC_InitTypeDef 结构体描述|
	|返回值|返回值说明|
	|NULL|初始化失败|
	|!NULL|初始化成功|


	结构体说明:<br>
	  1.SDMMC_InitTypeDef

	|结构体参数|必填|参数说明|
	|--|--|--|
	|slot_num|是|sdmmc 对应槽位,取值范围:<br>SLOT_0<br>SLOT_1<br>SLOT_2|
	|speed_mode|是|sdmmc 速度模式,取值范围:<br>slot_num != SLOT_0时:<br>SD_DS_MODE<br>SD_HS_MODE<br>SD_UHSI_SDR12_MODE<br>SD_UHSI_SDR25_MODE<br>SD_UHSI_SDR50_MODE<br>SD_UHSI_SDR104_MODE<br>SD_UHSI_DDR50_MODE<br><br>slot_num == SLOT_0时:<br>eMMC_Legacy_MODE<br>eMMC_SDR_MODE<br>eMMC_DDR_MODE<br>eMMC_HS200_SDR_MODE<br>eMMC_HS400_DDR_MODE<br>eMMC_HS400_DDR_ES_MODE<br>|
	|bus_width|是|sdmmc 数据总线宽度,取值范围:<br>BUS_WIDTH_1<br>BUS_WIDTH_4<br>BUS_WIDTH_8 (slot_num == SLOT_0 时可用)|
	|freq_mhz|是|sdmmc 总线频率,取值范围:<br>典型值:<br>SD_FREQ_25_MHZ (SD_DS_MODE或SD_UHSI_SDR12_MODE模式下)<br>SD_FREQ_50_MHZ (SD_HS_MODE或SD_UHSI_SDR25_MODE或SD_UHSI_DDR50_MODE模式下)<br>SD_FREQ_100_MHZ (SD_UHSI_SDR50_MODE模式下)<br>SD_FREQ_208_MHZ(SD_UHSI_SDR104_MODE模式下) <br>MMC_FREQ_26_MHZ (eMMC_Legacy_MODE或eMMC_SDR_MODE模式下) <br>MMC_FREQ_52_MHZ (eMMC_DDR_MODE模式下)<br>MMC_FREQ_200_MHZ (eMMC_HS200_SDR_MODE或eMMC_HS200_DDR_MODE或eMMC_HS400_DDR_ES_MODE模式下)<br><br>补充:<br>典型值为相应模式下可支持的最大频率<br>可以设置为小于该最大值的任何值<br>单位为mhz|
	|dma_mode|是|sdmmc DMA选项,取值范围:<br>SDMMC_DMA_MODE_NONE<br>SDMMC_DMA_MODE_SDMA<br>SDMMC_DMA_MODE_ADMA2|
	|insert_cb|否|卡片插入回调函数,取值范围:<br>回调函数名 或 NULL|
	|remove_cb|否|卡片拔出回调函数,取值范围:<br>回调函数名 或 NULL|
	|error_cb|否|axi总线错误回调函数,取值范围:<br>回调函数名 或 NULL|

* SDMMC去初始化
	```c 
	void itcs_sdmmc_deinit(SDMMC_Handler *handler);
	```
	|参数/返回值|说明|
	|--|--|
	|handler| SDMMC句柄|
	|返回值|-|	


* SDMMC读
	```c 
	int itcs_sdmmc_read(SDMMC_Handler *handler, uint32_t addr, size_t size, void* buf);	
	```
	|参数/返回值|说明|
	|--|--|
	|handler| SDMMC句柄|
	|addr| 读取的起始地址，取值需要被block length整除|
	|size| 读取的字节数，取值需要被block length整除|
	|buf| 读取后存放数据的buffer地址|
	|返回值|返回值说明|
	|负值|读取失败，并返回错误码|
	|正值|读取成功的字节数|	

* SDMMC写
	```c 
	int itcs_sdmmc_write(SDMMC_Handler *handler, uint32_t addr, size_t size, void* buf);	
	```
	|参数/返回值|说明|
	|--|--|
	|handler| SDMMC句柄|
	|addr| 读取的起始地址，取值需要被block length整除|
	|size| 读取的字节数，取值需要被block length整除|
	|buf| 要写入sdmmc数据的buffer地址|
	|返回值|返回值说明|
	|负值|写入失败，并返回错误码|
	|正值|写入成功的字节数|


* SDMMC擦除
	```c 
	int itcs_sdmmc_erase(SDMMC_Handler *handler, uint32_t addr, size_t size);	
	```
	|参数/返回值|说明|
	|--|--|
	|handler| SDMMC句柄|
	|addr| 读取的起始地址，取值需要被block length整除|
	|size| 读取的字节数，取值需要被block length整除|
	|返回值|返回值说明|
	|负值|擦除失败，并返回错误码|
	|正值|擦除成功的字节数|

* SDMMC获取block length
	```c 
	int itcs_sdmmc_get_block_len(SDMMC_Handler *handler);	
	```
	|参数/返回值|说明|
	|--|--|
	|handler| SDMMC句柄|
	|返回值|返回值说明|
	|负值|block length未知|
	|正值|一个block length的字节数|

## 示例代码
```c 
#include <sdmmc.h>

static int write_read_test(SDMMC_InitTypeDef *init)
{
  SDMMC_Handler handler = NULL;
  uint8_t read_buf[512] = {0};
  uint8_t write_buf[512] = {0};
  size_t size = 512;
  uint64_t block_addr = 512; // start address : block 1
  int count = 0;

  /* Initialize sdmmc.*/
  handler = itcs_sdmmc_init(&init);
  if(handler == NULL){
    printf("sdmmc initialize failed!\n")
    return -1;
  }

  /* Format buffer data */
  for(int i = 0; i < 512 ; i++){
    if(i < 256)
      write_buf[i] = i;
    else
      write_buf[i] = i -256;
  }

  /* Write one block */
  count = itcs_sdmmc_write(handler, block_addr, size, write_buf);
  if(count != size){
    printf("itcs_sdmmc_write failed!.\n");
    return -1;
  }

  /* Read one block */
  count = itcs_sdmmc_read(handler, block_addr, size, read_buf);
  if(count != size){
    printf("itcs_sdmmc_read failed!.\n");
    return -1;
  }

  /* Compares the read_buf with write_buf */
  if(memcmp(write_buf, read_buf, size)){
    printf("read result isn`t same as write result, sdmmc block addr start:0x%x, size:%d.\n",block_addr,size);
    return -1;
  }

  printf("Write read test passed!\n");
  
  return 0;
}

int main(int argc, char *argv[]) {
  SDMMC_InitTypeDef init;
  memset(&init,0,sizeof(SDMMC_InitTypeDef));
  init.freq_khz = 25000;
  init.speed_mode = SD_DS_MODE;
  init.slot_num = slot;
  init.bus_width = 4;
  init.use_dma = 1;
  write_read_test(&init);
}
```

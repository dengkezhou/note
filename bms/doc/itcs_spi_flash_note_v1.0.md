# SPI FLASH相关公共接口说明

## 头文件

```c
#include <spi_flash.h>
```

## 接口说明

* SPI FLASH初始化
	```c 
	struct spi_flash_obj *itcs_spi_flash_init(struct spi_flash_init_s *init);
	```
	|参数/返回值|说明|
	|--|--|
	|init| 初始化结构体|
	|返回值|返回值说明|
	|NULL|初始化失败|
	|!NULL|初始化成功，返回SPI FLASH对象句柄|

	结构体说明:<br>

    1.spi_flash_init_s

	|结构体参数|类型|必填|参数说明|
	|--|--|--|--|
    |is_xspi|bool|是|是否为xspi接口，取值范围:true/false|
    |ip_type|uint8_t|是|当非xspi时，选择spi控制器类型，取值范围：SPI_TYPE_DWC_SSI或SPI_TYPE_ARM_SSP|
	|compatible_name|uint16_t|是|SPI控制器接口，取值范围:<br>SPI0 ~ SPI3<br>XSPI0~XSPI1|
    |dataSize|uint32_t|是|SPI数据位，取值范围:<br>SPI_DATASIZE_8BIT<br>SPI_DATASIZE_16BIT|
    |mode|int|是|spi模式选择，取值范围:<br>0~4|
    |freq_hz|uint32_t|是|SPI频率，取值范围: 0-2000000|
    |cs_mode|int|是|SPI软件/硬件片选，取值范围:HW_SPI_CS_MODE/GPIO_CS_MODE|
    |cs_pin|int|是|SPI软件/硬件片选端口，取值范围:GPIO号或者硬件片选号|
    |line_num|int|是|SPI可用线数，取值范围:~1/2/4/8|
	|flash_type|int|是|spi flash 类型，取值范围：SPI_NOR_FLASH或SPI_NAND_FLASH或HYPER_RAM或HYPER_FLASH|
	|dev_discovery|bool|是|是否开启xspi自动发现spi flash设备，取值范围:true/false|
	
    

* SPI FLASH读
	```c 
	uint16_t itcs_spi_flash_read(struct spi_flash_obj *obj, uint8_t *pBuffer, uint32_t addr, uint16_t byte_num);
	```
	|参数/返回值|说明|
	|--|--|
	|obj| SPI FLASH对象|
    |pBuffer| 读取后存放数据的buffer地址|
	|addr| FLASH起始地址|
    |byte_num|读取的字节数|
	|返回值|返回值说明|
	|负值|读取失败，并返回错误码|
	|0|读取失败|
    |正值|完成读取的字节数|	

* SPI FLASH写
	```c 
	uint16_t itcs_spi_flash_write(struct spi_flash_obj *obj, uint8_t *pBuffer, uint32_t addr, uint16_t byte_num);
	```
	|参数/返回值|说明|
	|--|--|
	|obj| SPI FLASH对象|
    |pBuffer| 要写入的数据存放的buffer地址|
	|addr| FLASH起始地址|
    |byte_num|写入的字节数|
	|返回值|返回值说明|
	|负值|写入失败，并返回错误码|
	|0|写入失败|
    |正值|完成写入的字节数|	

* SPI FLASH擦除
	```c 
	bool itcs_spi_flash_erase(struct spi_flash_obj *obj, SPI_FLASH_ERASE_TYPE type, uint32_t addr);
	```
	|参数/返回值|说明|
	|--|--|
	|obj| XSPI FLASH对象|
    |type| 擦除类型，SPI_FLASH_ERASE_FULL_CHIP或SPI_FLASH_ERASE_SECTOR或SPI_FLASH_ERASE_BLOCK|
	|addr| FLASH起始地址|
	|返回值|返回值说明|
	|true|擦除成功|
    |false|擦除失败|

* SPI FLASH写保护
	```c 
	bool itcs_spi_flash_write_protect(struct spi_flash_obj *obj, bool enable);
	```
	|参数/返回值|说明|
	|--|--|
	|obj| SPI FLASH对象|
    |enable| 是否开启写保护|
	|返回值|返回值说明|
	|true|设置成功|
    |false|设置失败|

* 获取SPI FLASH对齐字节
	```c 
	uint32_t itcs_spi_flash_get_alignment(struct spi_flash_obj *obj);
	```
	|参数/返回值|说明|
	|--|--|
	|obj| SPI FLASH对象|
	|返回值|返回值说明|
	|0|获取失败|
    |正值|对齐字节数|


## 示例代码


```c 

#include <common.h>
#include <command.h>
#include <testbench.h>
#include <spi.h>
#include <stdbool.h>
#include <getopt.h>
#include "spi_flash.h"
#include <pads.h>

#define SPI_BUF_MAX_SIZE 1024

#define SPI_FLASH_TEST_ADDR 0

#define SPI_FLASH_DEFAULT_INIT_PARAM                                           \
  {                                                                            \
    false, SPI_TYPE_DWC_SSI, NULL, SPI0, SPI_DATASIZE_8BIT, 0, 1000000,        \
    HW_SPI_CS_MODE, 0, 1, SPI_NOR_FLASH, false                                 \
  }

int main() {
  int res;
  struct spi_flash_obj *flash;
  struct spi_flash_init_s init = SPI_FLASH_DEFAULT_INIT_PARAM;
  init.flash_type              = SPI_NAND_FLASH;
  init.cs_mode                 = GPIO_CS_MODE;
  init.cs_pin                  = 54;
  init.compatible_name         = "spi_nand";

  uint8_t spi_tx_buffer[SPI_BUF_MAX_SIZE];
  uint8_t spi_rx_buffer[SPI_BUF_MAX_SIZE];

  init.spi_instance = master;

  flash = itcs_spi_flash_init(&init);

  for (int i = 0; i < SPI_BUF_MAX_SIZE; i++) {
    spi_tx_buffer[i] = i;
  }

  itcs_spi_flash_write(flash, spi_tx_buffer, SPI_FLASH_TEST_ADDR,
                       SPI_BUF_MAX_SIZE);

  itcs_spi_flash_read(flash, spi_rx_buffer, SPI_FLASH_TEST_ADDR,
                      SPI_BUF_MAX_SIZE);
  
  for (int i = 0; i < SPI_BUF_MAX_SIZE; i++) {
    printf("read buf[%d] = %d\n",i ,spi_rx_buffer[i]);
  }
  
  res = memcmp(spi_tx_buffer, spi_rx_buffer, SPI_BUF_MAX_SIZE);
  if (!res) {
    printf("Test SPI Connect With Nand Flash Pass.\n");
  } else {
    printf("Inconsistent reading and writing of SPI flash.\n");
    return -1;
  }

  return 0;
}
```

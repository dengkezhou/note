# SPI相关公共接口说明

## 头文件

```c
#include <spi.h>
```

## 接口说明

* SPI初始化
	```c 
	SPI_HandleTypeDef* itcs_spi_init(SPI_InitTypeDef* init);	
	```
	|参数/返回值|说明|
	|--|--|
	|init| 初始化结构体|
	|返回值|返回值说明|
	|NULL|初始化失败|
	|!NULL|初始化成功，返回SPI句柄|


	结构体说明:<br>
	1.SPI_InitTypeDef

	|结构体参数|必填|参数说明|
	|--|--|--|
	|SPIx|是|SPI控制器接口，取值范围:<br>SPI0<br>SPI1<br>SPI2<br>SPI3|
	|type|是|SPI控制器类型，取值范围:<br>SPI_TYPE_DWC_SSI|
	|enable_dma|是|是否启动DMA传输，取值范围:<br>true<br>false|
	|enable_ddr|是|是否启动双边沿采样:<br>true<br>false|
	|mode|是|SPI控制器模式，取值范围:<br>SPI_MODE_SLAVE<br>SPI_MODE_MASTER|
	|dataSize|是|SPI数据尺寸，取值范围:<br>SPI_DATASIZE_8BIT<br>SPI_DATASIZE_16BIT|
	|CLKPolarity|是|SPI极性，取值范围:<br>SPI_POLARITY_LOW<br>SPI_POLARITY_HIGH|
	|CLKPhase|是|SPI采样边沿，取值范围:<br>SPI_PHASE_1EDGE<br>SPI_PHASE_2EDGE|
	|freq_hz|是|SPI时钟频率，取值范围:0-100000000|


* SPI去初始化
	```c 
	void itcs_spi_deinit(SPI_HandleTypeDef *spiHandler);
	```
	|参数/返回值|说明|
	|--|--|
	|spiHandler| SPI句柄|
	|返回值|-|		

* SPI接收
	```c 
	int itcs_spi_receive(SPI_HandleTypeDef *spiHandler, uint8_t *data, uint32_t size, uint8_t isBlock);
	```
	|参数/返回值|说明|
	|--|--|
	|spiHandler| SPI句柄|
    |data| 读取后存放数据的buffer地址|
	|size| 读取的字节数|
    |isBlock|是否阻塞接收|
	|返回值|返回值说明|
	|负值|接收失败，并返回错误码|
	|0|非阻塞返回|
  |正值|阻塞转态下完成接收的字节数|	

* SPI发送
	```c 
	int itcs_spi_transmit(SPI_HandleTypeDef *spiHandler, uint8_t *data, uint32_t size, uint8_t isBlock);
	```
	|参数/返回值|说明|
	|--|--|
	|spiHandler| SPI句柄|
    |data| 存放发送数据的buffer地址|
	|size| 发送的字节数|
    |isBlock|是否阻塞接发送|
	|返回值|返回值说明|
	|负值|发送失败，并返回错误码|
	|0|非阻塞返回|
  |正值|阻塞转态下完成发送的字节数|	

* SPI发送接收
	```c 
	int itcs_spi_transmit_receive(SPI_HandleTypeDef *spiHandler, uint8_t *tx_data, uint8_t *rx_data, uint32_t size, bool isBlock);
	```
	|参数/返回值|说明|
	|--|--|
	|spiHandler| SPI句柄|
    |tx_data| 存放发送数据的buffer地址|
    |rx_data| 存放接收数据的buffer地址|
	|size| 发送的字节数|
    |isBlock|是否阻塞接发送|
	|返回值|返回值说明|
	|负值|发送失败，并返回错误码|
	|0|非阻塞返回|
    |正值|阻塞转态下完成发送的字节数|	

* 获取SPI传输状态
	```c 
	int itcs_spi_get_transfer_status(SPI_HandleTypeDef *spiHandler, bool tx);
	```
	|参数/返回值|说明|
	|--|--|
	|spiHandler| SPI句柄|
	|tx| 是否为发送|
	|返回值|返回值说明|
	|TRANSFERING|数据正在传输，还未完成|
	|TRANSFER_COMPLETE|数据传输完成|
	|TRANSFER_ERROR|数据传输发生错误|

## 示例代码

```c 
#include <common.h>
#include <command.h>
#include <testbench.h>
#include <spi.h>
#include <stdbool.h>
#include <getopt.h>

#define SPI_BUF_MAX_SIZE 1024

#define DW_SPI_DEFAULT_INIT_PARAM                                              \
  {                                                                            \
    SPI0,SPI_TYPE_DWC_SSI,false,false,SPI_MODE_MASTER,SPI_DATASIZE_8BIT,       \
    SPI_POLARITY_LOW,SPI_PHASE_1EDGE,1000000,false                             \
  }

int main()
{
    SPI_InitTypeDef init_a = DW_SPI_DEFAULT_INIT_PARAM;
    SPI_InitTypeDef init_b = DW_SPI_DEFAULT_INIT_PARAM;
    SPI_HandleTypeDef *handler_a, *handler_b; 
    uint8_t spi_a_rx_buffer[SPI_BUF_MAX_SIZE];
    uint8_t spi_a_tx_buffer[SPI_BUF_MAX_SIZE];
    uint8_t spi_b_rx_buffer[SPI_BUF_MAX_SIZE];
    uint8_t spi_b_tx_buffer[SPI_BUF_MAX_SIZE];

    init_b.SPIx = SPI1
    init_b.mode = SPI_MODE_SLAVE;

    handler_a = itcs_spi_init(&init_a);
    handler_b = itcs_spi_init(&init_b);

    itcs_spi_receive(handler_a, spi_a_rx_buffer, SPI_BUF_MAX_SIZE, false);
    itcs_spi_receive(handler_b, spi_b_rx_buffer, SPI_BUF_MAX_SIZE, false);

    for (int i = 0; i < SPI_BUF_MAX_SIZE; i++) {
        spi_a_tx_buffer[i] = i;
    }

    itcs_spi_transmit(handler_a, spi_a_tx_buffer, SPI_BUF_MAX_SIZE, false);
    while (1){
        if(itcs_spi_get_transfer_status(handler_b, false) == SPI_STA_RX_COMPLETE){
            if(!memcmp(spi_b_rx_buffer, spi_a_tx_buffer, SPI_BUF_MAX_SIZE)){
                memcpy(spi_b_tx_buffer, spi_b_rx_buffer, SPI_BUF_MAX_SIZE);
                itcs_spi_transmit(handler_b, spi_b_tx_buffer, SPI_BUF_MAX_SIZE, false);
            }else{
                printf("The bytes received is not same as transmitted!\n");
            }
        }

        if(itcs_spi_get_transfer_status(handler_a, false) == SPI_STA_RX_COMPLETE){
            if(!memcmp(spi_a_rx_buffer, spi_b_tx_buffer, SPI_BUF_MAX_SIZE)){
                if(ddr){
                    printf("Test SPI DDR-Interrupt Pass\n"); 
                    return 0;
                }

                if(dma){
                    printf("Test SPI DMA Pass\n"); 
                    return 0;
                }

                switch(mode){
                    case 0: printf("Test SPI Interrupt-mode0 Pass\n"); return 0; break;
                    case 1: printf("Test SPI Interrupt-mode1 Pass\n"); return 0; break;
                    case 2: printf("Test SPI Interrupt-mode2 Pass\n"); return 0; break;
                    case 3: printf("Test SPI Interrupt-mode3 Pass\n"); return 0; break;
                }
               
            }else{
                 printf("The bytes received is not same as transmitted!\n");
                 return -1;
            }
        }

    }
    return 0;
}
```

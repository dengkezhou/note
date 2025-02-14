# MU相关公共接口说明

## 头文件

```c
#include <mu.h>
```

## 接口说明

* MU驱动初始化
	```c 
	MU_Handler *itcs_mu_init(domain_t domain, int mu_side, int irq_group)
	```
	|参数/返回值|说明|
    |--|--|
    |domain| MU模块选择，可填SAP或CPU|
    |mu_side| 设置为角色A或者角色B，可填MU_A_SIDE或MU_B_SIDE|
    |irq_group| 设置为0即可，当设置为0的时候使用中断0和1，否则使用中断2和3|
	|返回值|返回值说明|
	|NULL|初始化失败|
	|!NULL|初始化成功|

* MU写
	```c 
	uint16_t itcs_mu_write(MU_Handler * handler,uint8_t * buf, uint16_t size, bool isBlock);
	```
	|参数/返回值|说明|
	|--|--|
	|handler| MU句柄|
    |buf|要发送的数据首地址|
    |size|要发送的数据字节数|
    |isBlock|是否阻塞发送|
	|返回值|返回值说明|
	|正值|阻塞状态下成功发送的字节数|
	|零|非阻塞状态下的返回|
    |负值|发送失败|

* MU读
	```c 
	uint16_t itcs_mu_read(MU_Handler * handler, uint8_t * buf, uint16_t size, bool isBlock);
	```
	|参数/返回值|说明|
	|--|--|
	|handler| MU句柄|
    |buf|接收缓冲区的首地址|
    |size|接收缓冲区的长度|
    |isBlock|是否阻塞接收|
	|返回值|返回值说明|
	|正值|阻塞状态下成功接收的字节数|
	|零|非阻塞状态下的返回|
    |负值|接收失败|

* MU读写状态
	```c 
	uint16_t itcs_mu_get_status(MU_Handler * handler, uint8_t read_write);
	```
	|参数/返回值|说明|
	|--|--|
	|handler| MU句柄|
    |read_write|是否查询写状态，MU_WRITE为查询写，MU_READ为查询读|
	|返回值|返回值说明|
	|MU_RX_COMPLETE|读完成|
	|MU_TX_COMPLETE|写完成|
    |负值|读写失败，返回错误码|

## 示例代码
```c 
#include <common.h>
#include <stdio.h>
#include <command.h>
#include <testbench.h>
#include <malloc.h>
#include <irq.h>
#include <mu.h>
#include <asm/io.h>
#include <getopt.h>

static int mu_local_cpu_test(domain_t domain, int irq_group){
    MU_Handler *a_handler = NULL;
    MU_Handler *b_handler = NULL;
    uint8_t a_tx_buf[MU_BUF_LEN];
    uint8_t a_rx_buf[MU_BUF_LEN];
    uint8_t b_tx_buf[MU_BUF_LEN];
    uint8_t b_rx_buf[MU_BUF_LEN];

    a_handler = itcs_mu_init(domain, MU_A_SIDE, irq_group);
    b_handler = itcs_mu_init(domain, MU_B_SIDE, irq_group);

    if (!a_handler || !b_handler)
      return -1;
    
    for(int i = 0; i<MU_BUF_LEN; i++){
      a_tx_buf[i] = i;
    }

    itcs_mu_read(b_handler, b_rx_buf, MU_BUF_LEN, false);
    itcs_mu_write(a_handler, a_tx_buf, MU_BUF_LEN, true);
    while (1) {
        uint16_t status =  itcs_mu_get_status(b_handler, MU_READ);
        if (status == MU_RX_COMPLETE) {
            if(memcmp(b_rx_buf, a_tx_buf, MU_BUF_LEN)){
                printf("Test MU a->b Failed.\n");
                return -1;
            }else{
                memcpy(b_tx_buf, b_rx_buf, MU_BUF_LEN);
                itcs_mu_read(a_handler, a_rx_buf, MU_BUF_LEN, false);
                itcs_mu_write(b_handler, b_tx_buf, MU_BUF_LEN, true);
                while(1){
                    uint16_t status =  itcs_mu_get_status(a_handler, MU_READ);
                    if (status == MU_RX_COMPLETE) {
                        if(memcmp(a_rx_buf, b_tx_buf, MU_BUF_LEN)){
                            printf("Test MU b->a Failed.\n");
                            return -1;
                        }else{
                            printf("Test MU Pass.\n");
                            return 0;
                        }
                    }
                }
            }
        }
        udelay(1000);
    }
}
```

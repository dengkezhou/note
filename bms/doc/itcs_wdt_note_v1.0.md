# WDT相关接口说明

## 头文件

```c
#include <wdt.h>
```

## 接口说明

* 初始化看门狗
	启动看门狗，具体实现将MODE寄存器第0位置1
	```c 
	struct wdt_handler_s* itcs_wdt_init(struct wdt_init_s * init);
	```
    |参数名|参数说明|
	|--|--|
	|init| 看门狗初始化结构体|
	|返回值|返回值说明|
	|--|--|
	|非NULL|初始化成功|
	|NULL|初始化失败|



* 启动看门狗
	启动看门狗，具体实现将MODE寄存器第0位置1
	```c 
	uint32_t itcs_wdt_start(struct wdt_handler_s* handler);
	```
    |参数名|参数说明|
	|--|--|
	|handler| 看门狗句柄|
	|返回值|返回值说明|
	|--|--|
	|0|配置成功|
	|负值|配置失败|

* 停止看门狗
	停止看门狗，具体实现将MODE寄存器第0位置0
	```c 
	uint32_t itcs_wdt_stop(struct wdt_handler_s* handler);
	```
    |参数名|参数说明|
	|--|--|
	|handler| 看门狗句柄|
	|返回值|返回值说明|
	|--|--|
	|0|配置成功|
	|负值|配置失败|
	
* 看门狗超时后输出模式配置
	用来配置看门狗的模式寄存器MODE Register的1到11位，控制看门狗超时后的输出方式和保持时钟周期
	```c 
	uint32_t itcs_wdt_mode_config(struct wdt_handler_s* handler, unsigned char enable, WDT_MODE mode, uint32_t hold_time);
	```
	|参数名|参数说明|
	|--|--|
	|handler| 看门狗句柄|
	|enable|使能看门狗超时后的信号输出模式开关0：关闭，1：打开|
	|mode|使能看门狗超时后的信号输出模式只能为MODE_RST/MODE_IRQ/MODE_EXT或者三者的位或|
	|hold_time|该信号输出方式下的保持时间，取值为2的n次幂，MODE_RST模式下2<=hold_time<=256，MODE_IRQ模式下4<=hold_time<=32，MODE_EXT模式下8<=hold_time<=2048|
	|返回值|返回值说明|
	|--|--|
	|0|配置成功|
	|负值|配置失败|
	
	
* 看门狗计数器控制寄存器配置
	用来配置看门狗的计数器控制寄存器MODE Register
	```c 
	uint32_t itcs_wdt_counter_ctrl(struct wdt_handler_s* handler, uint32_t crv, unsigned char prescale);
	```
	|参数名|参数说明|
	|--|--|
	|handler| 看门狗句柄|
	|crv|counter start value, 0x0<=crv<=0xffff|
	|prescale|value of prescale must be 0/1/2/3|
	|返回值|返回值说明|
	|--|--|
	|0|配置成功|
	|负值|配置失败|
	
* 看门狗重新计数
	用来使看门狗重新开始计数，可以理解为喂狗
	```c 
	uint32_t itcs_wdt_feed(struct wdt_handler_s* handler);
	```
    |参数名|参数说明|
	|--|--|
	|handler| 看门狗句柄|
	|返回值|返回值说明|
	|--|--|
	|0|配置成功|
	|负值|配置失败|


## 示例代码
```c 
#include <common.h>
#include <command.h>
#include <testbench.h>
#include <malloc.h>
#include <wdt.h>
#include <irq.h>
#include <asm/io.h>
#include <getopt.h>


int main(){ 
    int ret;
    struct wdt_handler_s* handler;
    struct wdt_init_s init;
    init.callback = NULL;
    init.mode = MODE_RST;
    init.timeout_ms = 1000;
    init.WDTx = WDT0;

    handler = itcs_wdt_init(&init);
    if(handler == NULL){
         return -1;
    }

    ret = itcs_wdt_start(handler);
    if (ret != ITCS_RET_SUCCESS) {
        return -1;
    }

    return 0;
}
```


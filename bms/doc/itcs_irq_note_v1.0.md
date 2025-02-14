# IRQ相关接口说明

## 头文件

```c
#include <irq.h>
```

## 接口说明

* 中断申请
  
```c
int request_irq(unsigned int irq, irq_handler_t handler, const char *name, void *dev)
```

为模块中断注册一个处理函数，当模块的中断触发时，会调用到这个函数。对同一个中断号使用同样
的名字注册将会失败，但使用不同的名字注册则会当作共享中断来处理  
参数列表:  
|参数名|参数说明|
|--|--|
|irq|所申请的中断号|
|handler|中断的处理函数，在触发时调用|
|name|本次申请的名字，用来表示申请者的身份，在申请时不提供名字会导致申请失败。名字可以任意取，但为了方便识别，推荐字义和该模块相关|
|dev|在中断函数中以args的形式返回|
|返回值|返回值说明|
|0|申请成功|
|负值|申请失败|

* 中断使能

```c
void enable_irq(unsigned int irq)
```

使能一个已注册的中断，中断使用 request_irq 注册后默认处于使能状态  
参数列表:  
|参数名|参数说明|
|--|--|
|irq|所申请的中断号|

* 中断禁用

```c
void disable_irq(unsigned int irq)
```

指定一个已注册中断的响应 CPU  
参数列表：   
|参数名|参数说明|
|--|--|
|irq|所申请的中断号|

* 设置中断分发的CPU

```c
int irq_set_affinity(unsigned int irq, unsigned int cpu)
```

指定一个已注册中断的响应 CPU  
参数列表：  
|参数名|参数说明|
|--|--|
|irq|所申请的中断号|
|cpu|对应的 processor_id，processor_id 从 0 开始。比如说 4 核就是: 0, 1, 2, 3|

## 示例代码

```c
/* prepare the irq handler */
int demo_irq_handler(int irq, void * x)
{
    printf(“*** in the irq handler ***\n”);
}
int demo_main(int argc, char *argv[])
{
    /* request IRQ no.35, which is a common timer IRQ.
     * after doing this request, function demo_irq_handler
     * will be invoked when IRQ 35 triggered.
     */
    request_irq(35, demo_irq_handler, “common timer”);
}
```
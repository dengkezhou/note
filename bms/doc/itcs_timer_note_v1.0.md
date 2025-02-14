# TIMER相关接口说明

## 头文件

```c
#include <timer.h>
```

## 接口说明

* 定时器初始化
  
```c
timer_handle_t itcs_timer_init(timer_handle_t handle,
                               timer_event_cb_t cb_event)
```

定时器初始化函数
参数列表:  
|参数名|参数说明|
|--|--|
|handle|计时器结构参数体指针|
|cb_event|触发中断的回调函数|
|返回值|返回值说明|
|timer_handle_t|返回定时器结构体参数|

* 定时器设置

```c
int32_t itcs_timer_config(timer_handle_t handle, timer_mode_e mode,int risedown, timer_match_t match);
```

设置中断计数器
参数列表:  
|参数名|参数说明|
|--|--|
|handle|计时器结构参数体指针|
|mode|定时器模式|
|risedown|定时器递增递减|
|timer_match_t|设置定时器match模式:<br>match1_en： match1使能 1:开 0:关<br>   match2_en： match2使能 1:开 0:关<br> match3_en： match3使能 1:开 0:关<br> match1:match1时长 ms<br>match2:match2时长 ms<br>match3:match2时长 ms<br>|
|返回值|返回值说明|
|0     |成功|
|-1     |失败|  

* 定时器启动

```c
int32_t itcs_timer_start(timer_handle_t handle)
```

参数列表:  
|参数名|参数说明|
|--|--|
|handle|计时器结构参数体指针|
|返回值|返回值说明|
|0     |成功|
|-1     |失败|

* 定时器停止

```c
int32_t itcs_timer_stop(timer_handle_t handle)
```

参数列表:  
|参数名|参数说明|
|--|--|
|handle|计时器结构参数体指针|
|返回值|返回值说明|
|0     |成功|
|-1     |失败|



## 示例代码

```c
#include <common.h>
#include <command.h>
#include <testbench.h>
#include <malloc.h>
#include <asm/io.h>
#include <getopt.h>
#include <timer.h>
#define CONFIG_TIMER_NUM 2
uint32_t g_begintime;
uint32_t g_endtime;
uint32_t g_endtimematch1;
uint32_t g_endtimematch2;
uint32_t g_endtimematch3;
uint32_t g_match1time;
uint32_t g_match2time;
uint32_t g_match3time;
uint32_t g_matchnum;
uint32_t g_intevaltime;
uint32_t g_stopflag;

timer_priv_t timer[CONFIG_TIMER_NUM];
timer_match_t timer_match;
extern int32_t itcs_timer_stop(timer_handle_t handle);
void timer_event_cb_fun(timer_handle_t handle) {
  timer_priv_t *timer_priv = handle;
  if (timer_priv->enum_interrupt == TIMER_INTERVAL_INTERRUPT){ 
    itcs_timer_stop(timer_priv);
  }
   printf("Call back fun Receiver Interrupt!\n");
  return;
}

int demo_main(int argc, char *argv[]) {
 
  int mode =1, risedown = 1, settime = 5000,idx=0 ,timeridx=1;
  timer_priv->idx = idx;
  timer_priv->timeridx = timeridx; 
  timer_priv_t *timer_priv = &timer[idx];
  if (mode == 1 && g_matchnum == 0) {
    timer_priv           = itcs_timer_init(timer_priv, timer_event_cb_fun);
    timer_priv->inittime = settime;
    itcs_timer_config(timer_priv, TIMER_MODE_INTERVAL, risedown,
                      timer_match_data);
    itcs_timer_start(timer_priv);
    while (!g_stopflag) {
      udelay(500);
    }
  
  return 0;
}
```

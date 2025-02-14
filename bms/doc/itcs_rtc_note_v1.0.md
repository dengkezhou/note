# RTC相关接口说明

## 头文件

```c
#include <rtc.h>
```

## 接口说明

* rtc初始化
  
```c
rtc_device_t *itcs_rtc_init(rtc_setting_t *settings)
```

初始化rtc模块  
参数/返回值列表: 

|参数名|参数说明|
|--|--|
|settings|rtc初始化配置|  

|返回值|返回值说明|
|--|--|
|!NULL|成功|
|NULL|失败|

结构体说明:  

1. rtc_setting_t

|结构体参数|必填|参数说明|
|--|--|--|
|hourMode|是|Time模式，目前支持HOUR24_MODE, HOUR12_MODE|
|callback|是|回调函数，在RTC中断函数中调用|
|callback_param|是|回调参数|

* rtc去初始化

```c
void itcs_rtc_deinit(rtc_device_t *dev)
```

去初始化rtc模块  
参数/返回值列表:  

|参数名|参数说明|
|--|--|
|dev|rtc驱动句柄，itcs_rtc_init获得|
* rtc初始化time

```c
void itcs_rtc_init_time(rtc_time_t *time, int year, int month, int day,
                          int hour, int min, int sec, int hsec);
```

参数值列表:

|参数名|参数说明|
|--|--|
|time|存储rtc time的结构体，见下|
|year|年|
|month|月|
|day|日|
|hour|小时|
|min|分钟|
|sec|秒|
|hsec|百分之一秒|

结构体说明:  

<a id="tm_struct"></a>

1. rtc_time_t

|结构体参数|必填|参数说明|
|--|--|--|
|tm_hsec|否|1/100 秒|
|tm_sec|否|秒|
|tm_min|否|分|
|tm_hour|否|小时|
|tm_mday|否|天|
|tm_mon|否|月|
|tm_year|否|年|
|tm_wday|否|周几|
* rtc获得当前time

```c
int itcs_rtc_get_time(rtc_device_t *dev, rtc_time_t *tm)
```

获得当前time 
参数/返回值列表:

|参数名|参数说明|
|--|--|
|dev|rtc驱动句柄，itcs_rtc_init获得|
|tm|存储rtc time的结构体|

|返回值|返回值说明|
|--|--|
|0|成功|
|负数|失败|

* rtc设置time

```c
int itcs_rtc_set_time(rtc_device_t *dev, rtc_time_t *tm)
```

设置time  
参数/返回值列表:  

|参数名|参数说明|
|--|--|
|dev|rtc驱动句柄，itcs_rtc_init获得|
|tm|存储rtc time的结构体，[见上](#tm_struct)|

|返回值|返回值说明|
|--|--|
|0|成功|
|负数|失败|

* rtc获得当前alarm设置

```c
int itcs_rtc_get_alarm(rtc_device_t *dev, rtc_time_t *alarm)
```

获得当前alarm设置  
参数/返回值列表:
|参数名|参数说明|
|--|--|
|dev|rtc驱动句柄，itcs_rtc_init获得|
|alarm|存储rtc time的结构体，[见上](#tm_struct)|

|返回值|返回值说明|
|--|--|
|0|成功|
|负数|失败|

* rtc设置alarm

```c
int itcs_rtc_set_alarm(rtc_device_t *dev, rtc_time_t *alarm)
```

设置alarm
参数/返回值列表:  
|参数名|参数说明|
|--|--|
|dev|rtc驱动句柄，itcs_rtc_init获得|
|alarm|存储rtc time的结构体，[见上](#tm_struct)|

|返回值|返回值说明|
|--|--|
|0|成功|
|负数|失败|

* rtc设置event irq

```c
void itcs_rtc_event_set_irq_enable(rtc_device_t *dev, int val, bool enabled)
```

设置alarm
参数/返回值列表:  

| 参数名  | 参数说明                               |
| ------- | -------------------------------------- |
| dev     | rtc驱动句柄，itcs_rtc_init获得         |
| val     | 具体的触发事件类型，[见下](#trig_type) |
| enabled | true表示开中断，false表示关中断        |

事件类型:

<a id="trig_type"></a>

| 事件类型      | 事件说明           |
| ------------- | ------------------ |
| RTC_HOS_TRIG  | 百分之一秒变化触发 |
| RTC_SEC_TRIG  | 秒变化触发         |
| RTC_MIN_TRIG  | 分变化触发         |
| RTC_HOUR_TRIG | 小时变化触发       |
| RTC_DATE_TRIG | 日期变化触发       |
| RTC_MNTH_TRIG | 月份变化触发       |
| RTC_ALRM_TRIG | 闹钟触发           |

## 示例代码

```c
static volatile int complete = -1;

static void rtc_event_callback(void *arg, int status)
{
  if (status & RTC_MIN_TRIG)
	complete = 0;
}

static int rtc_event_test(void)
{
  rtc_setting_t sets = {
      .hourMode = HOUR24_MODE,
      .callback = rtc_event_callback,
  };
  rtc_device_t *dev;
  rtc_time_t time0, time1;
  int ret = -1;

  dev = itcs_rtc_init(&sets);
  if (!dev)
    return ret;

  itcs_rtc_init_time(&time0, 2022, 7, 21, 12, 7, 59, 0);
  itcs_rtc_set_time(dev, &time0);
  itcs_rtc_event_set_irq_enable(dev, RTC_MIN_TRIG, true);

  while (complete < 0)
    udelay(10);

  itcs_rtc_event_set_irq_enable(dev, RTC_MIN_TRIG, false);
  itcs_rtc_get_time(dev, &time1);

  if ((time1.tm_min - time0.tm_min) == 1)
    ret = 0;

  return ret;
}

int rtc_main(int argc, char *argv[])
{
   return rtc_event_test(); 
}
```
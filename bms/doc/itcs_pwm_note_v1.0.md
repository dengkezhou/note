# WDT相关接口说明

## 头文件

```c
#include <pwm.h>
```

## 接口说明

* pwm通道配置

  ```c 
    pwm_device_t *itcs_pwm_config(domain_t sysmode, uint32_t channel, pwm_init_t *init)
  ```

  | 参数名  | 参数说明                       |
  | ------- | ------------------------------ |
  | sysmode | 系统单元CPU、SAP、RTC(0、1、2) |
  | channel | pwm通道号0~7                   |
  | init    | 初始化配置                     |

  | 返回值         | 返回值说明       |
  | -------------- | ---------------- |
  | pwm_device_t * | 返回配置通道句柄 |

* pwm通道周期更新

  ```c 
    void itcs_pwm_period_update(pwm_device_t *dev, uint32_t period)
  ```

  | 参数名 | 参数说明               |
  | ------ | ---------------------- |
  | dev    | 通道句柄               |
  | period | 更新周期0 ~ 0xFFFFFFFF |

  | 返回值 | 返回值说明 |
  | ------ | ---------- |
  | none   | --         |

* pwm通道占空比更新

  ```c 
    void itcs_pwm_duty_update(pwm_device_t *dev, uint32_t duty)
  ```

  | 参数名 | 参数说明          |
  | ------ | ----------------- |
  | dev    | 通道句柄          |
  | duty   | 更新占空比0%~100% |

  | 返回值 | 返回值说明 |
  | ------ | ---------- |
  | none   | --         |

* pwm开启通道输出

  ```c 
    void itcs_pwm_start(pwm_device_t *dev)
  ```

  | 参数名 | 参数说明 |
  | ------ | -------- |
  | dev    | 通道句柄 |

  | 返回值 | 返回值说明 |
  | ------ | ---------- |
  | none   | --         |

* pwm关闭通道输出

  ```c 
    void itcs_pwm_stop(pwm_device_t *dev)
  ```

  | 参数名 | 参数说明 |
  | ------ | -------- |
  | dev    | 通道句柄 |

  | 返回值 | 返回值说明 |
  | ------ | ---------- |
  | none   | --         |


## 示例代码

```c 
#include <command.h>
#include <common.h>
#include <malloc.h>
#include <testbench.h>
#include <asm/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <pwm.h>


int main()
{ 
    pwm_device_t *pwm0_dev;
    pwm_device_t *pwm1_dev;
    pwm_init_t init;
    uint32_t channel;

    init.period             = 10000;
    init.duty               = 50;
    init.channel_int_enable = PWM_CHANNEL_INT_DISABLE;

    pwm0_dev = itcs_pwm_config(0, &init);
    itcs_pwm_start(pwm0_dev);
    itcs_pwm_stop(pwm0_dev);

    pwm1_dev = itcs_pwm_config(1, &init);
    itcs_pwm_start(pwm1_dev);
    itcs_pwm_stop(pwm1_dev);
}
```


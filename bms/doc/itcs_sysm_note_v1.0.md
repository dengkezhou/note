# SYSM 相关接口说明

## 头文件

```c
#include <common.h>
```

## 接口说明

### 模块功耗相关API

模块设置的名字module，目前仅支持如下几个，如果要添加，可以在 driver/sysm/domain.c 文件中自行添加

CPU系统下支持：  
|||||||
|--|--|--|--|--|--|
|wdt|gpio|ttc0|ttc1|spi1|spi2|
|spi3|iic2|iic3|iic4|iic5|uart2|
|uart3|mu|iis0|iis1|pwm0|pwm1|
|pwm2|pwm3|pwm4|pwm5|pwm6|pwm7|
|ddr|usb0|usb1|usb2|usb3|gmac0|
|gmac1|emmc0|ospi|sd1|sd2|qspi|
|cae|dma0|dma1|rxa0|rxa1|rxa2|
|rxa3|

SAP系统下支持：
|||||||
|--|--|--|--|--|--|
|wdt|gpio|ttc|spi|iic0|iic1|
|uart0|uart1|mu|pwm0|

RTC系统下支持
|||||||
|--|--|--|--|--|--|
|pwm0|rtc|

#### 模块上电

```c
int itcs_module_enable(domain_t mode, const char *module)
```

给当前模块上电，在模块驱动初始化后第一步的操作。  
参数/返回值列表:  
|参数名|参数说明|
|--|--|
|mode|系统类型，目前支持CPU，SAP，RTC 3种类型|
|module|模块名，当前未确定|

|返回值|返回值说明|
|--|--|
|0|模块上电成功|
|负值|模块上电失败|

#### 模块下电

```c
int itcs_module_disable(domain_t mode, const char *module)
```

关闭模块，在降低功耗时一般需要此操作。  
参数/返回值列表:  
|参数名|参数说明|
|--|--|
|mode|系统类型，目前支持CPU，SAP，RTC 3种类型|
|module|模块名，当前未确定|

|返回值|返回值说明|
|--|--|
|0|关闭模块成功|
|负值|关闭模块失败|

#### 模块重启

```c
int itcs_module_reset(domain_t mode, const char *module)
```

软重启模块，在某些软件操作中需要。  
参数/返回值列表:  
|参数名|参数说明|
|--|--|
|mode|系统类型，目前支持CPU，SAP，RTC 3种类型|
|module|模块名，当前未确定|

|返回值|返回值说明|
|--|--|
|0|软重启模块成功|
|负值|软重启模块失败|

### PLL时钟相关API

PLL设置的名字pll目前仅支持如下几个
||||||
|--|--|--|--|--|
|apll|dpll|epll|vpll|spll|

#### PLL设置时钟

```c
int64_t itcs_pll_set_clock(domain_t mode, const char *pll, int64_t freq, bool fraction)
```

设置某个 PLL 为要求的频率。  
参数/返回值列表:  
|参数名|参数说明|
|--|--|
|mode|系统类型，目前支持CPU，SAP，RTC 3种类型|
|pll|所需要设置的 PLL 名称|
|freq|需要指定 PLL 的频率|
|fraction|是否需要小数分频|

|返回值|返回值说明|
|--|--|
|正数|设置好的 PLL 的 freq|
|负值|设定失败，可能原因是 freq 值不在范围内或者无此 PLL|

#### 获得PLL时钟

```c
int64_t itcs_pll_get_clock(domain_t mode, const char *pll)
```

得到某个 PLL 的频率值。  
参数/返回值列表:  
|参数名|参数说明|
|--|--|
|mode|系统类型，目前支持CPU，SAP，RTC 3种类型|
|pll|所需要设置的 PLL 名称|

|返回值|返回值说明|
|--|--|
|正数|PLL 的 freq|
|负值|获得失败，无此 PLL|

### 模块时钟相关API

模块设置的名字module，目前仅支持如下几个，如果要添加，可以在 driver/sysm/clock.c 文件中自行添加

CPU系统：  
|||||||
|--|--|--|--|--|--|
|apb|bus1|bus2|bus3|bus4|bus5|
|bus6|ddr|ttc|spi|uart|iis|
|extern|reg bus|emmc0|sd1|sd2|qspi|

SAP系统：  
|||||||
|--|--|--|--|--|--|
|apc|apb|bus1|ttc|spi|uart|

#### Module设置时钟

```c
int64_t itcs_module_set_clock(domain_t mode, const char *module, const char *pll, int64_t freq, bool nco)
```

设置某个模块为要求的频率。  
参数/返回值列表:  
|参数名|参数说明|
|--|--|
|mode|系统类型，目前支持CPU，SAP，RTC 3种类型|
|module|所需要设置的模块名称|
|pll|parent时钟设置, 目前可选apll, epll, vpll, dpll, spll(SAP系统专用)|
|freq|需要指定模块的频率|
|nco|nco分频模式|

|返回值|返回值说明|
|--|--|
|正数|设置好的模块的 freq|
|负值|设定失败，可能原因是 freq 值不在范围内或者无此模块|

#### 获得模块时钟

```c
int64_t itcs_module_get_clock(domain_t mode, const char *module)
```

得到某个模块的频率值。  
参数/返回值列表:  
|参数名|参数说明|
|--|--|
|mode|系统类型，目前支持CPU，SAP，RTC 3种类型|
|module|所需要设置的模块名称|

|返回值|返回值说明|
|--|--|
|正数|模块的 freq|
|负值|获得失败，无此模块|

### 管脚API

#### 获得管脚模式

```c
int itcs_pads_get_mode(domain_t mode, uint32_t index)
```

得到某一个 PAD 的状态，有输入、输出和 FUNC 三种模式。  
参数/返回值列表:  
|参数名|参数说明|
|--|--|
|mode|系统类型，目前支持CPU，SAP，RTC 3种类型|
|index|需要得到状态的某一个 IO pad|

|返回值|返回值说明|
|--|--|
|0|输出模式|
|1|输入模式|
|2|Func模式|
|负值|获得失败，没有此 GPIO|

#### 设置管脚模式

```c
int itcs_pads_set_mode(domain_t mode, uint32_t range, int mode, uint32_t value)
```

将某一个 pad 或者连续几个 pads 的状态设置为 mode 模式。  
参数/返回值列表:  
|参数名|参数说明|
|--|--|
|mode|系统类型，目前支持CPU，SAP，RTC 3种类型|
|range|需要得到状态的某一个 IO pad, 也可以设置连续的一组 gpio 操作模式。如果要操作一组 pads，需要使用宏 PADSRANGE(start, end)，作为 range 参数|
|mode|需要设置的 pads 状态：<br>PADS_MODE_OUT: GPIO 输出模式<br>PADS_MODE_IN: GPIO 输入模式<br>PADS_MODE_FUNC: Func 模式|
|value|当 mode 输出模式，value 对应高、低电平<br>当 mode 为Func模式时，value 对应Func功能（PADS_FUNC0, PADS_FUNC1, PADS_FUNC2, PADS_FUNC3, PADS_FUNC4, PADS_FUNC5），具体请参照Frigoris_IOM_v03.xlsx <br>当 mode 为输入模式，则略过此参数|

|返回值|返回值说明|
|--|--|
|0|设置管脚模式成功|
|负值|设置失败，没有此 GPIO|

#### 获得管脚上下拉

```c
int itcs_pads_get_pull(domain_t mode, uint32_t index)
```

得到某一个 pad上下拉状态。  
参数/返回值列表:  
|参数名|参数说明|
|--|--|
|mode|系统类型，目前支持CPU，SAP，RTC 3种类型|
|index|需要得到状态的某一个 IO pad|

|返回值|返回值说明|
|--|--|
|0|此 pin 上拉使能|
|1|此 pin 下拉使能|
|2|此 pin 无上下拉|

#### 设置管脚上下拉

```c
int itcs_pads_set_pull(domain_t mode, uint32_t range,  uint32_t en, uint32_t pattern)
```

设置某一个 PAD 或者连续几个 PADS 的上下拉状态。  
参数/返回值列表:  
|参数名|参数说明|
|--|--|
|mode|系统类型，目前支持CPU，SAP，RTC 3种类型|
|range|需要得到状态的某一个 IO pad, 也可以设置连续的一组 gpio 操作模式。如果要操作一组 pads，需要使用宏 PADSRANGE(start, end)，作为 range 参数|
|en|是否需要启动上下拉功能，每个 bit 对应相应的一位|
|pattern|PADS_PULL_UP: 上拉<br>PADS_PULL_DOWN: 下拉<br>PADS_PULL_NO: 不设置上下拉|

|返回值|返回值说明|
|--|--|
|0|设置管脚上下拉成功|
|负值|设置失败，没有此 GPIO|

#### 获得管脚输入电平

```c
int itcs_pads_get_value(domain_t mode, uint32_t index, int *mode)
```

得到某一个pad 的电平值。  
参数/返回值列表:  
|参数名|参数说明|
|--|--|
|mode|系统类型，目前支持CPU，SAP，RTC 3种类型|
|index|需要得到状态的某一个 IO pad|
|*mode|获得pad设置的模式: <br>PADS_MODE_OUT: GPIO 输出模式<br>PADS_MODE_IN: GPIO 输入模式<br>PADS_MODE_FUNC: Func 模式|

|返回值|返回值说明|
|--|--|
|0|此输入 pin 为低电平|
|1|此输入 pin 为高电平|
|-1|获得输入状态出错或此IO pad为Func模式|

#### 设置管脚输入电平

```c
int itcs_pads_set_value(domain_t mode, uint32_t range,  uint32_t high)
```

设置某一个 PAD 或者连续几个 PADS 输出 IO 的值。  
参数/返回值列表:  
|参数名|参数说明|
|--|--|
|mode|系统类型，目前支持CPU，SAP，RTC 3种类型|
|range|需要得到状态的某一个 IO pad, 也可以设置连续的一组 gpio 操作模式。如果要操作一组 pads，需要使用 PADSRANGE(start, end)，作为 range 参数|
|high|需要设置输出 pads 的电平值|

|返回值|返回值说明|
|--|--|
|0|设置管脚电平成功|
|负值|设置失败，没有此 GPIO|

#### 设置模块管脚function模式

```c
int itcs_module_set_pads(domain_t mode, int bitmode, const char *name)
```

设置某一个模块的一组 IO 为 FUNC 模式。  
参数/返回值列表:  
|参数名|参数说明|
|--|--|
|mode|系统类型，目前支持CPU，SAP，RTC 3种类型|
|bitmode|硬件版本IO模式，目前支持，具体参考frigo_FPGA_PIN_bit_version.xlsx：<br>FPGA_BIT_V_RGMII: eth, codec，usb等外设版本<br>FPGA_BIT_V_EMMC: emmc版本<br>FPGA_BIT_V_OSPI: ospi版本|
|name|需要设置的某一组 io 的模块名字|

|返回值|返回值说明|
|--|--|
|0|模块function功能设置完成|
|负值|没有这个模块名|

name目前仅支持如下几个，如果要添加，可以在 driver/sysm/pads.c 文件中自行添加：  
bitmode为FPGA_BIT_V_RGMII时：
|||||||
|--|--|--|--|--|--|
|gmac0|gmac1|iic0|iic1|iic2|iic3|
|iic4|uart0|iis0|jtag|

bitmode为FPGA_BIT_V_EMMC时：
|||||||
|--|--|--|--|--|--|
|emmc|sd1|sd2|iis0|iis1|spi0|
|spi1|spi2|spi3|qspi|iic0|iic1|
|iic2|iic3|iic4|iic5|uart0|uart1|
|uart2|uart3|pwm0|pwm1|pwm2|pwm3|
|pwm4|pwm5|pwm6|pwm7|jtag|

bitmode为FPGA_BIT_V_OSPI时：
|||||||
|--|--|--|--|--|--|
|ospi|qspi|sd1|sd2|iis0|iis1|
|iic0|iic1|iic2|iic3|iic4|iic5|
|uart0|uart1|uart2|uart3|pwm0|pwm1|
|pwm2|pwm3|pwm4|pwm5|pwm6|pwm7|
|jtag|



## 示例代码

```c
int sysm_main(int argc, char *argv[])
{
  itcs_pll_set_clock(CPU, "apll", 1000000000, false);
  itcs_pll_get_clock(CPU, "apll");
  itcs_module_set_clock(CPU, "apb", "apll", 1000000000);
  itcs_module_get_clock(CPU, "apb");
  itcs_pads_set_mode(CPU, PADSRANGE(50, 51), PADS_MODE_FUNC, PADS_FUNC0);
  itcs_module_set_pads(CPU, FPGA_BIT_V_RGMII, "iic0");
}

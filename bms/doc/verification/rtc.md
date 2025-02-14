# RTC 相关测试例

## RTC TIME测试

----
`FPGA`  `P0`

**Description**

1. fpga母板RPAD_XRTCGP1不接任何管脚，即拉高(如果bit文件支持通过此管脚选择时钟来源，RPAD_XRTCGP1可拉低，即J16.9接到J16.10，s2cclk_1可设置为4.194MHZ，经过128分频可得到约32.768KHz时钟)
2. 设置当前TIME(TIMR,CALR)
3. 过1s后，读取TIME，并对比

**Expectation**

1. 时间相差1s
2. 打印Test RTC TIME Pass

**FPGA&RTL Params**

```c
rtc --time
```

## RTC ALARM测试

----
`FPGA` `RTL` `P0`

**Description**

1. fpga母板RPAD_XRTCGP1不接任何管脚，即拉高(如果bit文件支持通过此管脚选择时钟来源，RPAD_XRTCGP1可拉低，即J16.9接到J16.10，s2cclk_1可设置为4.194MHZ，经过128分频可得到约32.768KHz时钟)
2. 设置当前TIME(TIMR,CALR)
3. 设置ALARM(TIMAR,CALAR)，设置ALARM为当前TIME过后的1s(1s rtl)，并使能ALARM中断

**Expectation**

1. 中断正常产生
2. 打印Test RTC ALARM Pass

**FPGA&RTL Params**

```c
rtc --alarm
```

## RTC EVENT测试

----
`FPGA` `RTL` `P0`

**Description**

1. fpga母板RPAD_XRTCGP1不接任何管脚，即拉高(如果bit文件支持通过此管脚选择时钟来源，RPAD_XRTCGP1可拉低，即J16.9接到J16.10，s2cclk_1可设置为4.194MHZ，经过128分频可得到约32.768KHz时钟)
2. 设置当前TIME(TIMR,CALR)
3. 并使能MIN中断

**Expectation**

1. EVENT中断正常产生
2. 打印Test RTC EVENT Pass

**FPGA&RTL Params**

```c
rtc --event
```

## Keep RTC

----
`FPGA` `RTL` `P0`

**Description**

1. fpga母板RPAD_XRTCGP1不接任何管脚，即拉高(如果bit文件支持通过此管脚选择时钟来源，RPAD_XRTCGP1可拉低，即J16.9接到J16.10，s2cclk_1可设置为4.194MHZ，经过128分频可得到约32.768KHz时钟)
2. 设置当前time(TIMR,CALR)，alarm(TIMAR,CALAR)
3. reset RTC控制器
4. 立即读time(TIMR,CALR)，alarm(TIMAR,CALAR)

**Expectation**

1. 读取的time等于设置的time，alarm为复位值
2. 打印Test RTC KEEP Pass

**FPGA&RTL Params**

```c
rtc --keep
```

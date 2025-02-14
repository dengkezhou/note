# PWM 相关测试例

## PWM 输出控制

----

`FPGA` `RTL` `P0`

**Description**  

1. 配置PWM寄存器，配置输出1MHz(rtc pwm is 1365Hz)，占空比为25%的波形。开启输出使能。  

**Expectation**  

1. 成功输出1MHz,占空比为25%的波形，并能通过测试仪器（逻辑分析仪，示波器）捕获正确波形.

**FPGA&RTL Params**  


```c
pwm -m 0 -c 0 7 -i 1 -p 100 -d 25
pwm -m 1 -c 0 0 -i 1 -p 100 -d 25
pwm -m 2 -c 0 0 -i 1 -p 24 -d 25
```

## PWM周期测试

----

`FPGA` `RTL` `P0`

**Description**  

1. 配置PWM寄存器

   配置输出1ms的1MHz，占空比为25%的波形。1ms后切换为2M，1ms后再切换为3M,输出1ms后关闭输出。

**Expectation**  

1. 能按照配置输出波形，并能通过测试仪器（逻辑分析仪，示波器）捕获正确波形,并能够关闭输出。

**FPGA&RTL Params**  

```c
pwm -m 0 -c 0 7 -i 2 -p 100 -d 25
pwm -m 1 -c 0 0 -i 2 -p 100 -d 25
pwm -m 2 -c 0 0 -i 2 -p 24 -d 25
```

## PWM占空比测试

----

`FPGA` `RTL` `P0`

**Description**  

1. 配置PWM寄存器

   配置输出1ms的1MHz，占空比为25%的波形。1ms后切换占空比为25%，1ms后切换占空比为50%,1ms后切换占空比75%.

**Expectation**  

1. 能按照配置输出波形，并能通过测试仪器（逻辑分析仪，示波器）捕获正确波形。

**FPGA&RTL Params**  

```c
pwm -m 0 -c 0 7 -i 3 -p 100 -d 25
pwm -m 1 -c 0 0 -i 3 -p 100 -d 25
pwm -m 2 -c 0 0 -i 3 -p 24 -d 25
```

## PWM中断测试

----

`FPGA` `RTL` `P0`

**Description**  

1. 配置PWM寄存器

  配置输出占空比为50%的波形，并开启中断。

**Expectation**  

1. 能进入中断并打印中断计数，在int count 计数高于10后，清除中断状态，关闭中断使能，并输出中断测试结束log。

**FPGA&RTL Params**  

```c
pwm -m 0 -c 0 7 -i 4
pwm -m 1 -c 0 0 -i 4
pwm -m 2 -c 0 0 -i 4
```

## PWM复用测试

----

`FPGA` `RTL` `P0`

**Description**  

1. 配置PWM寄存器

  配置输出占空比为50%的波形。

**Expectation**  

1. 能按照配置输出波形，并能通过测试仪器（逻辑分析仪，示波器）捕获正确波形。

**FPGA&RTL Params**  

```c
pwm -m 0 -c 4 7 -i 5 -p 100 -d 50 -x 1
pwm -m 0 -c 4 7 -i 5 -p 100 -d 50 -x 2
pwm -m 0 -c 4 7 -i 5 -p 24 -d 50 -x 3
```

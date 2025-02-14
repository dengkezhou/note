# LPDDR4 相关测试例

## LPDDR4 phy loopback

----
`RTL` `P0`

**Description**

1. 开启lpddr4内部或外部loopback，配置好起始地址，结束地址，进行测试。控制器自动比较读写的数据
2. rtl下路径经过opad后返回ipad，比较二者数据

**Expectation**

1. 检查寄存器的结果，未发生数据读写不一致情况

**FPGA&RTL Params**

```c
```

## LPDDR4 phy pll bypass

----
`RTL` `P0`

**Description**

1. pll在bypass模式下读写，（controller与phy单独供时钟，phy时钟是controller两倍）
2. 进行数据读写，并比较数据

**Expectation**

1. 数据比较正确

**FPGA&RTL Params**

```c
```

## LPDDR4 phy dll bist测试

----
`RTL` `P0`

**Description**

1. 路径经过各级delay line后loopback，并比较数据

**Expectation**

1. 数据比对正确

**FPGA&RTL Params**

```c
```

## LPDDR4 pi初始化与training

----
`RTL` `P0`

**Description**

1. phy pi初始化并training lpddr4

**Expectation**

1. 完成training基本步骤，且delay line值有变化，可以读写

**FPGA&RTL Params**

```c
```

## LPDDR4 axi测试

----
`RTL` `P0`

**Description**

1. 读写addr线扫过两块ddr的col、bank、row、cs
2. 检查ddr总线上命令是否符合规范与满足读写row18命令

**Expectation**

1. 符合预期

**FPGA&RTL Params**

```c
```

## LPDDR4 低功耗模式

----
`RTL` `P0`

**Description**

1. 退出进入低功耗模式（self-refresh）

**Expectation**

1. 进入低功耗模式，寄存器标志被正确拉起。退出低功耗后可正常读写

**FPGA&RTL Params**

```c
```

## LPDDR4 动态调频

----
`RTL` `P0`

**Description**

1. 预期两个频率分别是4266mhz和1600mhz，通过controller切换频率

**Expectation**

1. 切换后可以正常读写

**FPGA&RTL Params**

```c
```

## LPDDR4 zq校准

----
`RTL` `P0`

**Description**

1. ddr初始化后，启用zq校准，校准值发生变化

**Expectation**

1. 校准后可以正常读写

**FPGA&RTL Params**

```c
```

## LPDDR4 修改axi优先级或带宽限制后读写

----
`RTL` `P0`

**Description**

1. 修改controller端口各个port的读写优先级，进行读写并观察带宽效率是否变化
2. 修改controller带宽限制，进行读写并观察带宽效率是否变化

**Expectation**

1. 带宽效率有变化且能正常读写

**FPGA&RTL Params**

```c
```

## LPDDR4 后门访问ddr并前门读取

----
`P0`

**Description**

1. 后门写入ddr内部数组并通过cpu来访问

**Expectation**

1. 读回的数据与预先写入的一致

**FPGA&RTL Params**

```c
```

## LPDDR4 axi0-7并发访问ddr

----
`P0`

**Description**

1. controller各个端口同时读写

**Expectation**

1. 数据比对正确

**FPGA&RTL Params**

```c
```

## LPDDR4 jtag使能loopback测试

----
`P0`

**Description**

1. 通过jtag端口配置phy为loopback，phy内部和外部自己进行读写

**Expectation**

1. 内部和外部比较数据pass

**FPGA&RTL Params**

```c
```

## LPDDR4 jtag进行边界测试

----
`RTL` `P0`

**Description**

1. jtag配置phy端口输出数据，并通过jtag读数据

**Expectation**

1. 读到的数据与输出的一致

**FPGA&RTL Params**

```c
```

## LPDDR4低频率下测试

----
`RTL` `P0`

**Description**

1. 配置频率为1066MHz，进行测试

**Expectation**

1. 结果与预期一致

**FPGA&RTL Params**

```c
lpddr4 -lf
```

## LPDDR4 mpu0和mpu1读写测试

----
`FPGA` `P0`

**Description**

1. mpu0与mpu1分别进行ddr读写

**Expectation**

1. 数据读写无错误

**FPGA&RTL Params**

```c
lpddr4 -w 32 -n 1
```

## LPDDR4 ASIC测试

----
`P0`

**Description**

1. 支持DDRAPP交互，ASIC功能性测试和压力测试，通过输入要测试的项目的序号进行测试

**Expectation**

1. 能够正确进入到对应的测试
2. 测试结果符合预期

**FPGA&RTL Params**

```c
lpddr4 -bp
```

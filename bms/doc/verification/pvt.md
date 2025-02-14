# PVT 相关测试例

## PVT temperature模式

----
`RTL` `P0`

**Description**

1. 将PVT控制器配置成temperature模式，将TRIMEO设为0，TRIMG设为0xf，读取data_out的值

**Expectation**

1. 读取的data_out值符合我们期望
2. 打印Test PVT temperature Pass

**FPGA&RTL Params**

```c
pvt -m 0
```

## PVT voltage模式

----
`RTL` `P0`

**Description**

1. 将PVT控制器配置成voltage模式，读取电压的data_out值

**Expectation**

1. data_out值符合期望
2. 打印Test PVT voltage Pass

**FPGA&RTL Params**

```c
pvt -m 1
```

## PVT process模式

----
`RTL` `P0`

**Description**

1. 将PVT控制器配置成process模式，分别配置成LVT、ULVT、SVT模式的data_out的值

**Expectation**

1. data_out值在特殊的范围内
2. 打印Test PVT process Pass

**FPGA&RTL Params**

```c
pvt -m 2 -p 0
pvt -m 2 -p 1
pvt -m 2 -p 2
```


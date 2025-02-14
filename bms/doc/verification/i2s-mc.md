# I2S-MC相关测试例
#### 测试描述

* 由于I2S发送与接收的数据大小为1~32 bits，是可以配置的，所以在下面的描述中，**数据单位为“个”，而非“Byte”**
* I2s mc共8路sd，两组 sck 和 ws信号，所以将 sdi_n 连接 sdo_m, sdo_n 连接 sdi_m 称为第n路与第m路数据相连；将 tscki 连接 rscko，tscko连接rscki ,  twsi 连接 rwso，twso连接rwsi  称为时钟相连。 

## I2S MC normal Test

----
`FPGA` `RTL` `P0`

**Description**

1. 将i2s-mc时钟相连接、第0路与第1路数据相连、第2路与第3路数据相连、第4路与第5路数据相连、第6路与第7路数据相连（下面均简称“I2S MC 自环连接”）。
2. 将i2s-mc配置为中断传输模式
3. 将偶数路i2s配置为发送、master端，奇数路i2s配置为接收、slave端
5. i2s自环收发65个数据
6. 将i2s接收到的数据与发送数据做对比，并打印结果
7. 将偶数路i2s配置为发送、slave端，奇数路i2s配置成接收、master端，重复步骤5-6
8. 将偶数路i2s配置为接收、master端，奇数路i2s配置成发送、slave端，重复步骤5-6
9. 将偶数路i2s配置为接收、slave端，奇数路i2s配置成发送、master端，重复步骤5-6

**Expectation**

1. 打印normal mode, Interrupt Mode, Test Size: 260 Bytes,  Pass
1. 打印Loop Back mode, Interrupt Mode, Test Size: 260 Bytes,  Pass

**FPGA&RTL Params**

```c
i2s_mc -m 0 -o 0 -n 260
i2s_mc -m 1 -o 0 -n 260
i2s_mc -m 0 -o 1 -n 260
i2s_mc -m 1 -o 1 -n 260
i2s_mc -m 0 -o 0 -n 260 -l 1
```


## I2S MC DMA Test

----
`FPGA` `RTL` `P0`

**Description**

1. i2s-mc 自环连接。
2. 将I2S-mc 配置为DMA传输模式
3. 将偶数路i2s配置为发送、master端，奇数路i2s配置为接收、slave端
4. i2s自环收发65个数据
5. 将i2s接收到的数据与发送数据做对比，并打印结果
6. 将偶数路i2s配置为接收、slave端，奇数路i2s配置成发送、master端，重复步骤5-6

**Expectation**

1. 打印normal mode, DMA Mode, Test Size: 260 Bytes,  Pass

**FPGA&RTL Params**

```c
i2s_mc -m 0 -o 0 -n 260 -d
i2s_mc -m 1 -o 0 -n 260 -d
```

## I2S MC Standard Test

----
`FPGA` `RTL` `P0`

**Description**

1. i2s-mc 自环连接。
2. 将i2s-mc配置为中断传输模式
3. 将偶数路i2s配置为发送、master端，奇数路i2s配置为接收、slave端
4. 将i2s-mc设为"Right Justified mode"
5. i2s自环收发65个数据
6. 将i2s接收到的数据与发送数据做对比，并打印结果
7. 分别将I2S-mc设为"Left Justified mode"和"DSP mode"，重复步骤3~6

**Expectation**

1. 打印normal mode, Right Justified mode, Interrupt Mode, Test Size: 260 Bytes , Pass
1. 打印 normal  mode, Left Justified mode, Interrupt Mode, Test Size: 260 Bytes Pass
1. 打印 normal  mode, DSP mode, Interrupt Mode, Test Size: 260 Bytes Pass

**FPGA&RTL Params**

```c
i2s_mc -m 0 -o 0 -n 260 -t 1
i2s_mc -m 0 -o 0 -n 260 -t 2
i2s_mc -m 0 -o 0 -n 260 -t 3
```
## I2S MC 连接实际codec

----
`FPGA` `P0`

**Description**

1. 通过i2c初始化外部codec，配置i2s-mc master  recv模式
2. 录制人声
3. 导出声音到pc

**Expectation**

1. 播放的人声正常

**FPGA&RTL Params**

```c
i2s_mc -r
i2s_mc -m 0 -o 2 -l 0 -p
```


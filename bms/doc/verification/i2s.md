# I2S 相关测试例
#### 测试数据描述

* 由于I2S发送与接收的数据大小为1~32 bits，是可以配置的，所以在下面的描述中，**数据单位为“个”，而非“Byte”**

## I2S Half Duplex Test: Master Transmit and Slave Receive

----
`FPGA` `RTL` `P0`

**Description**

1. I2S0 SCLK连接I2S1 SCLK，I2S0 WS连接I2S1 WS，I2S0 SDO连接I2S1 SDI，I2S0 SDI连接I2S1 SDO（下面均简称“I2S0与I2S1对接”）。
2. 将I2S0与I2S1配置为中断传输模式
3. 将**I2S0**配置为*Half Duplex Master Transmit*模式，**I2S1**配置为*Half Duplex Slave Receive*模式
4. **I2S0**发送65个数据到**I2S1**，**I2S1**收到数据后比对发送的数据是否正确。
5. 将**I2S0**配置为*Half Duplex Slave Receive*模式，**I2S1**配置为*Half Duplex Master Transmit*模式
6. **I2S1**发送65个数据到 **I2S0**，**I2S0**收到数据后比对发送的数据是否正确。

**Expectation**

1. 打印Half Duplex, Interrupt Mode, Test Size: 130 Bytes, I2S0 Master Transmit, I2S1 Slave Receive, Pass
2. 打印Half Duplex, Interrupt Mode, Test Size: 130 Bytes, I2S1 Master Transmit, I2S0 Slave Receive, Pass
**FPGA&RTL Params**

```c
i2s -m 0 -o 0 -n 130
i2s -m 1 -o 0 -n 130
```

## I2S Half Duplex Test: Master Receive and Slave Transmit

----
`FPGA` `RTL` `P0`

**Description**

1. I2S0与I2S1对接。
2. 将I2S0与I2S1配置为中断传输模式
3. 将**I2S0**配置为*Half Duplex Master Receive*模式，**I2S1**配置为*Half Duplex Slave Transmit*模式
4. **I2S1**发送65个数据到**I2S0**，**I2S0**收到数据后比对发送的数据是否正确。
5. 将**I2S0**配置为*Half Duplex Slave Transmit*模式，**I2S1**配置为*Half Duplex Master Receive*模式
6. **I2S0**发送65个数据到 **I2S1**，**I2S1**收到数据后比对发送的数据是否正确。
7. 将I2S0与I2S1配置为DMA传输模式，重复步骤3~6

**Expectation**

1. 打印Half Duplex, Interrupt Mode, Test Size: 130 Bytes, I2S0 Master Receive, I2S1 Slave Transmit, Pass
2. 打印Half Duplex, Interrupt Mode, Test Size: 130 Bytes, I2S1 Master Receive, I2S0 Slave Transmit, Pass

**FPGA&RTL Params**

```c
i2s -m 0 -o 1 -n 130
i2s -m 1 -o 1 -n 130
```

## I2S Full Duplex Test

----
`FPGA` `RTL` `P0`

**Description**

1. I2S0与I2S1对接。
2. 将I2S0与I2S1配置为中断传输模式
3. 将**I2S0**配置为*Full Duplex Master*模式，**I2S1**配置为*Full Duplex Slave*模式
4. **I2S0**与**I2S1**同时发送、接收65个数据。
5. 比对I2S1接收到的数据与I2S0发送的数据是否相同，I2S0接收到的数据与I2S1发送的数据是否相同
6. 将**I2S1**配置为*Full Duplex Master*模式，**I2S0**配置为*Full Duplex Slave*模式
7. **I2S0**与**I2S1**同时发送、接收65个数据。
8. 比对I2S1接收到的数据与I2S0发送的数据是否相同，I2S0接收到的数据与I2S1发送的数据是否相同


**Expectation**

1. 打印Full Duplex, Interrupt Mode, Test Size: 130 Bytes, I2S0 Master Receive, I2S1 Slave Receive, Pass
2. 打印Full Duplex, Interrupt Mode, Test Size: 130 Bytes, I2S1 Master Receive, I2S0 Slave Receive, Pass

**FPGA&RTL Params**

```c
i2s -f -m 0 -n 130
i2s -f -m 1 -n 130
```


## I2S DMA Test

----
`FPGA` `RTL` `P0`

**Description**

1. I2S0与I2S1对接。
2. 将I2S0与I2S1配置为DMA传输模式
3. 将**I2S0**配置为*Half Duplex Master Receive*模式，**I2S1**配置为*Half Duplex Slave Transmit*模式
4. **I2S1**发送65个数据到**I2S0**，**I2S0**收到数据后比对发送的数据是否正确。
5. 将**I2S0**配置为*Half Duplex Slave Transmit*模式，**I2S1**配置为*Half Duplex Master Receive*模式
6. **I2S0**发送65个数据到 **I2S1**，**I2S1**收到数据后比对发送的数据是否正确。

**Expectation**

1. 打印Half Duplex, DMA Mode, Test Size: 130 Bytes, I2S0 Master Transmit, I2S1 Slave Receive, Pass
2. 打印Half Duplex, DMA Mode, Test Size: 130 Bytes, I2S1 Master Transmit, I2S0 Slave Receive, Pass

**FPGA&RTL Params**

```c
i2s -m 0 -o 0 -n 130 -d
i2s -m 1 -o 0 -n 130 -d
```

## I2S Standard Test

----
`FPGA` `RTL` `P0`

**Description**

1. I2S0与I2S1对接。
2. 将I2S0与I2S1配置为中断传输模式
3. 将**I2S0**配置为*Half Duplex Master Receive*模式，**I2S1**配置为*Half Duplex Slave Transmit*模式
4. 将I2S0/I2S1设为"Right Justified mode"
5. **I2S0**发送65个数据到 **I2S1**，**I2S1**收到数据后比对发送的数据是否正确。
6. 分别将I2S0/I2S1设为"Left Justified mode"和"DSP mode"，重复步骤3~5

**Expectation**

1. 打印Half Duplex, Right Justified mode, Interrupt Mode, Test Size: 130 Bytes, I2S0 Master Transmit, I2S1 Slave Receive, Pass
1. 打印Half Duplex, Left Justified mode, Interrupt Mode, Test Size: 130 Bytes, I2S0 Master Transmit, I2S1 Slave Receive, Pass
1. 打印Half Duplex, DSP mode, Interrupt Mode, Test Size: 130 Bytes, I2S0 Master Transmit, I2S1 Slave Receive, Pass

**FPGA&RTL Params**

```c
i2s -m 0 -o 0 -n 130 -t 1
i2s -m 0 -o 0 -n 130 -t 2
i2s -m 0 -o 0 -n 130 -t 3
```
## I2S TDM Test

----
`FPGA` `RTL` `P0`

**Description**

1. I2S0与I2S1对接。
2. 将I2S0与I2S1配置为中断传输模式
3. 将**I2S0**配置为*Half Duplex Master Receive*模式，**I2S1**配置为*Half Duplex Slave Transmit*模式
4. 将I2S0/I2S1设为"Time Division Multiplexed mode"，通道数为1
5. 设置I2S0/I2S1 "ws_mode = 0"
6. **I2S0**发送65个数据到 **I2S1**，**I2S1**收到数据后比对发送的数据是否正确
7. 设置I2S0/I2S1通道数为2~16，重复步骤3~6。

**Expectation**

1. 打印Half Duplex, TDM mode, Interrupt Mode, Test Size: 130 Bytes, I2S0 Master Transmit, I2S1 Slave Receive, Pass

**FPGA&RTL Params**

```c
i2s -m 0 -o 0 -n 130 -c 1 -w 0 -v
i2s -m 0 -o 0 -n 130 -c 10 -w 0 -v
i2s -m 0 -o 0 -n 130 -c 16 -w 0 -v
```

## I2S Pin Test

----
`ASIC` `P0`

**Description**

1. I2S0与I2S1对接。
2. 将I2S0与I2S1配置为中断传输模式
3. 配置i2S0的功能引脚和I2S1的功能引脚
4. 将**I2S0**配置为*Half Duplex Master Receive*模式，**I2S1**配置为*Half Duplex Slave Transmit*模式
5. **I2S1**发送65个数据到**I2S0**，**I2S0**收到数据后比对发送的数据是否正确。

**Expectation**

1. 打印Half Duplex, Interrupt Mode, Test Size: 130 Bytes, I2S0 Master Receive, pads index 1, I2S1 Slave Transmit, pads index 1, Pass
2. 打印Half Duplex, Interrupt Mode, Test Size: 130 Bytes, I2S0 Master Receive, pads index 2, I2S1 Slave Transmit, pads index 2, Pass
3. 打印Half Duplex, Interrupt Mode, Test Size: 130 Bytes, I2S0 Master Receive, pads index 3, I2S1 Slave Transmit, pads index 3, Pass
4. 打印Half Duplex, Interrupt Mode, Test Size: 130 Bytes, I2S0 Master Receive, pads index 4, I2S1 Slave Transmit, pads index 0, Pass
5. 打印Half Duplex, Interrupt Mode, Test Size: 130 Bytes, I2S0 Master Receive, pads index 5, I2S1 Slave Transmit, pads index 0, Pass

**FPGA&RTL Params**

```c
i2s -m 0 -o 1 -a 0 -b 0 -n 130
i2s -m 1 -o 1 -a 0 -b 0 -n 130
i2s -m 0 -o 1 -a 1 -b 1 -n 130
i2s -m 1 -o 1 -a 1 -b 1 -n 130
i2s -m 0 -o 1 -a 2 -b 2 -n 130
i2s -m 1 -o 1 -a 2 -b 2 -n 130
i2s -m 0 -o 1 -a 3 -b 3 -n 130
i2s -m 1 -o 1 -a 3 -b 3 -n 130
i2s -m 0 -o 1 -a 4 -b 0 -n 130
i2s -m 0 -o 1 -a 5 -b 0 -n 130
```

## I2S 连接实际codec

----
`FPGA` `P0`

**Description**

1. 配置i2s0 full-duplex master模式,并通过i2c初始化外部codec
2. 录制人声
3. 播放刚录制的人声
4. 配置i2s1 full-duplex master模式,并通过i2c初始化外部codec
5. 重复步骤 2-3

**Expectation**

1. 播放的人声正常

**FPGA&RTL Params**

```c
i2s -m 0 -a 1 -r
i2s -m 0 -a 1 -p
i2s -m 1 -a 1 -r
i2s -m 1 -a 1 -p
```


## I2S Mux 测试

----
`RTL` `P0`

**Description**

1. 分别将I2S0和I2S1的引脚设为不同的MUX，测试所有引脚的可用性
2. 进行一次Half Duplex 传输

**Expectation**

1. 打印Half Duplex, Interrupt Mode, Test Size: 130 Bytes, I2S0 Master Transmit, I2S1 Slave Receive, Pass

**FPGA&RTL Params**

```c
i2s -x 0 -f -m 0 -n 130
i2s -x 1 -f -m 0 -n 130
i2s -x 2 -f -m 0 -n 130
```

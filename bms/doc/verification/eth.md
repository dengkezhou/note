# ETH 相关测试例

## ETH loopback测试

----
`FPGA` `RTL` `P0`

**Description**

1. ETHx设为设置为Loopback模式
2. ETHx发1500(rtl 64)字节数据
3. ETHx接收到自己发送的1500(rtl 64)字节数据

**Expectation**

1. 2与3中的收发数据一致
2. 打印Test ETH loopback Pass

**FPGA&RTL Params**

```c
eth -lo 0 -rgmii
eth -lo 1 -rgmii
eth -lo 2 -rgmii
eth -lo 3 -rgmii
eth -lo 0 -rmii ext
eth -lo 1 -rmii ext
eth -lo 2 -rmii ext
eth -lo 3 -rmii ext
```

## ETH 收发包(10M) DMA测试

----
`FPGA` `RTL` `P0`

**Description**

1. ETH0、ETH1或eth2、eth3设为设置为10M DMA TX+RX模式（全双工模式）
2. ETH0/eth2发1500(rtl 64)字节数据给ETH1/eth3，同时ETH1/eth3发1500(rtl 64)字节数据给ETH0/eth2
3. fpga上rmii使用phy lan8742a，rgmii使用88e1116r

**Expectation**

1. 步骤2中ETH1/eth3收到的数据等于ETH0/eth2发送的数据并且ETH0/eth2收到的数据等于ETH1/eth3发送的数据
2. 打印Test ETH 10M DMA Mode Pass
3. eth2、eth3预期与上述一致

**FPGA&RTL Params**

```c
eth -s 0 -rgmii
eth -s 3 -rgmii
eth -s 0 -rmii ext
eth -s 3 -rmii ext # rtl下eth2使用外部时钟，eth3使用内部时钟
```

## ETH 收发包(100M) DMA测试

----
`FPGA` `RTL` `P0`

**Description**

1. ETH0、ETH1设为设置为100M DMA TX+RX模式（全双工模式）
2. ETH0发1500(rtl 64)字节数据给ETH1，同时ETH1发1500(rtl 64)字节数据给ETH0
3. 同样的，对eth2、eth3进行测试
4. fpga上rmii使用phy lan8742a，rgmii使用88e1116r

**Expectation**

1. 步骤2中ETH1收到的数据等于ETH0发送的数据并且ETH0收到的数据等于ETH1发送的数据
2. 打印Test ETH 100M DMA Mode Pass
3. eth2、eth3预期与上述一致

**FPGA&RTL Params**

```c
eth -s 1 -rgmii
eth -s 4 -rgmii
eth -s 1 -rmii ext
eth -s 4 -rmii ext
```

## ETH 收发包(1000M) DMA测试

----
`FPGA` `RTL` `P0`

**Description**

1. fpga上先使用命令eth -in 0 -rgmii -phase和eth -in 1 -rgmii -phase确定调相次数，修改代码对应的宏定义
2. ETH0、ETH1设为设置为1000M DMA TX+RX模式（全双工模式）
3. ETH0发1500(rtl 64)字节数据给ETH1，同时ETH1发1500(rtl 64)字节数据给ETH0
4. 同样的，对eth2、eth3进行测试
5. fpga上rgmii使用phy 88e1116r

**Expectation**

1. 步骤2中ETH1收到的数据等于ETH0发送的数据并且ETH0收到的数据等于ETH1发送的数据
2. 打印Test ETH 1000M DMA Mode Pass
3. eth2、eth3预期与上述一致

**FPGA&RTL Params**

```c
eth -s 2 -rgmii
eth -s 5 -rgmii
```

## ETH接收包过滤测试
----
`FPGA` `RTL` `P0`

**Description**

1. ETH0、ETH1设为设置为100M DMA RX+TX（全双工模式）
2. ETH0设置过滤目的mac地址不为本机mac的数据包
3. ETH1发1500(rtl 64)字节目的地址为ETH0数据给ETH0，此时ETH0能收到全部数据
4. ETH1发1500(rtl 64)字节目的地址不为ETH0 mac的数据给ETH0，期望时间内未收到数据包认为过滤成功
5. ETH0到ETH1类似上述
6. 同样的，对eth2、eth3进行测试
7. fpga上rmii使用phy lan8742a，rgmii使用88e1116r

**Expectation**

1. 测试符合预期，打印Test ETH MAC Filter Mode Pass
2. eth2、eth3预期与上述一致

**FPGA&RTL Params**

```c
eth -f 0 -rgmii
eth -f 1 -rgmii
eth -f 2 -rgmii
eth -f 3 -rgmii
eth -f 0 -rmii ext
eth -f 1 -rmii ext
eth -f 2 -rmii ext # rtl下eth2使用外部时钟，eth3使用内部时钟
eth -f 3 -rmii ext
```

## ETH PC连接测试

----
`FPGA`  `P0`

**Description**

1. ETHx与PC ETH网口相连，设置为100M DMA模式
2. pc端对于rgmii执行sudo ethtool -s enp5s0 speed 100 duplex full autoneg on设置网口速率，rmii执行sudo ethtool -s enp5s0 speed 100 duplex full autoneg off
3. ETHx发1500(rtl 64)字节数据给PC，PC端收到修改目的和源mac地址后并送回1500(rtl 64)字节给ETHx
4. ETHx接收到来自PC的数据
5. fpga上rmii使用phy lan8742a，rgmii使用88e1116r

**Expectation**

1. ETHx发送和ETHx接收的数据在前12字节后一致
2. 打印Test ETH Connection With PC Pass

**FPGA&RTL Params**

```c
eth -in 0 -rgmii
eth -in 1 -rgmii
eth -in 2 -rgmii
eth -in 3 -rgmii
eth -in 0 -rmii ext
eth -in 1 -rmii ext
eth -in 2 -rmii ext
eth -in 3 -rmii ext
```

## ETH巨帧测试
----
`FPGA` `RTL` `P0`

**Description**

1. ETH0、ETH1设为设置为1000M DMA TX+RX模式（全双工模式）并开启巨帧模式
2. ETH0发16287字节(需看phy支持的最大)数据给ETH1，同时ETH1发16287字节数据给ETH0
3. 同样的，对eth2、eth3进行测试
4. fpga上rgmii使用phy 88e1116r
5. rmii使用internal模式

**Expectation**

1. 步骤2中ETH1收到的数据等于ETH0发送的数据并且ETH0收到的数据等于ETH1发送的数据
2. 打印Test ETH Jumbo Frame Pass
3. eth2、eth3预期与上述一致

**FPGA&RTL Params**

```c
eth -j 0 -rgmii
eth -j 0 -rmii
eth -j 1 -rgmii
eth -j 1 -rmii
```

## ETH emac测试

----
`FPGA` `RTL` `P0`

**Description**

1. ETH0、ETH1设为设置为1000M DMA TX+RX模式（全双工模式）
2. ETH0发1500(rtl 64)字节数据给ETH1，同时ETH1发1500(rtl 64)字节数据给ETH0
3. 同样的，对eth2、eth3进行测试
4. fpga上rgmii使用phy 88e1116r

**Expectation**

1. 步骤2中ETH1收到的数据等于ETH0发送的数据并且ETH0收到的数据等于ETH1发送的数据
2. 打印Test ETH emac 1000M DMA Mode Pass
3. eth2、eth3预期与上述一致

**FPGA&RTL Params**

```c
eth -e 0 -rgmii
eth -e 1 -rgmii
```

## WOL模式测试
----
`FPGA`  `P0`

**Description**

1. ETH0 PHY配置WOL使能模式
2. PC发送Magic Packet给PHY，PHY能识别此数据包，产生wol中断
3. fpga上rmii使用phy lan8742a

**Expectation**

1. phy wol pin有电平变化

**FPGA&RTL Params**

```c
eth -w 0 -rmii ext
```

## mdio测试
----
`RTL`  `P0`

**Description**

1. mdio进行读phy bmcr操作
2. 读到phy bmcr后打印结果，同时使能phy loopback将值写回phy bmcr

**Expectation**

1. mdio能正确读写phy bmcr，打印Pass

**FPGA&RTL Params**

```c
eth -m 0 -rgmii
eth -m 1 -rmii ext
eth -m 2 -rgmii
eth -m 3 -rmii ext
```

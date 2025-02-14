# SPI 相关测试例

## SPI loopback测试

----
`FPGA` `RTL` `P0`

**Description**

1. 配置spi0 master loopback模式
2. spi0发送1024bytes(rtl:32bytes)数据
3. 接收到自己发出的1024bytes(rtl:32bytes)数据

**Expectation**

1. 写入和读取的数据一致
2. 打印Test SPI Loopback Test Pass

**FPGA&RTL Params**

```c
spi -m 0 --loop
spi -m 1 --loop
spi -m 2 --loop
spi -m 3 --loop
```

## SPI 中断模式(Mode 0)读写

----
`FPGA` `RTL` `P0`

**Description**

1. 配置spi0 master中断模式，spi1 slave中断模式
2. spi0 写1024bytes(rtl:32bytes)数据到spi1，spi1对比数据是否正确

**Expectation**

1. 步骤2和步骤3数据对比正确
2. 打印Test SPI Interrupt-mode0 Pass

**FPGA&RTL Params**

```c
spi -m 0 -s 1 -e 0
spi -m 1 -s 0 -e 0
spi -m 2 -s 3 -e 0
spi -m 3 -s 2 -e 0
```

## SPI 中断模式(Mode 1)读写

----
`FPGA` `RTL` `P0`

**Description**

1. 配置spi0 master中断mode 1模式，spi1 slave中断mode 1模式
2. spi0 写1024bytes(rtl:32bytes)数据到spi1，spi1对比数据是否正确

**Expectation**

1. 步骤2和步骤3数据对比正确
2. 打印Test SPI Interrupt-mode1 Pass

**FPGA&RTL Params**

```c
spi -m 0 -s 1 -e 1
spi -m 1 -s 0 -e 1
spi -m 2 -s 3 -e 1
spi -m 3 -s 2 -e 1
```

## SPI 中断模式(Mode 2)读写

----
`FPGA` `RTL` `P0`

**Description**

1. 配置spi0 master中断mode 2模式，spi1 slave中断mode 2模式
2. spi0 写1024bytes(rtl:32bytes)数据到spi1，spi1对比数据是否正确

**Expectation**

1. 步骤2和步骤3数据对比正确
2. 打印Test SPI Interrupt-mode2 Pass

**FPGA&RTL Params**

```c
spi -m 0 -s 1 -e 2
spi -m 1 -s 0 -e 2
spi -m 2 -s 3 -e 2
spi -m 3 -s 2 -e 2
```

## SPI 中断模式(Mode 3)读写

----
`FPGA` `RTL` `P0`

**Description**

1. 配置spi0 master中断mode 3模式，spi1 slave中断mode 3模式
2. spi0 写1024bytes(rtl:32bytes)数据到spi1，spi1对比数据是否正确

**Expectation**

1. 步骤2和步骤3数据对比正确
2. 打印Test SPI Interrupt-mode3 Pass

**FPGA&RTL Params**

```c
spi -m 0 -s 1 -e 3
spi -m 1 -s 0 -e 3
spi -m 2 -s 3 -e 3
spi -m 3 -s 2 -e 3
```


## SPI DMA模式读写

----
`FPGA` `RTL` `P0`

**Description**

1. 配置spi0 master DMA模式，spi1 slave DMA模式
2. spi0 写1024bytes(rtl:32bytes)数据到spi1，spi1对比数据是否正确

**Expectation**

1. 步骤2和步骤3数据对比正确
2. 打印Test SPI DMA Pass

**FPGA&RTL Params**

```c
spi -m 0 -s 1 -d
spi -m 1 -s 0 -d
spi -m 2 -s 3 -d
spi -m 3 -s 2 -d
```

## SPI 外接1线 spi nand flash读写

----
`FPGA` `P0`

**Description**

1. 配置spi0 master中断模式，并按照外接的spi nand flash配置寄存器
2. spi0 先写1024bytes(rtl:32bytes)数据到flash，然后再从flash中读32bytes

**Expectation**

1. 写入和读取flash的数据一致
2. 打印Test SPI Connect With Nand Flash Pass

**FPGA&RTL Params**

```c
spi -m 0 --nand
spi -m 1 --nand
spi -m 2 --nand
spi -m 3 --nand
```

## SPI 外接1线 spi nor flash读写

----
`FPGA` `P0`

**Description**

1. 配置spi0 master中断模式，并按照外接的spi nor flash配置寄存器
2. spi0 先写1024bytes(rtl:32bytes)数据到flash，然后再从flash中读32bytes

**Expectation**

1. 写入和读取flash的数据一致
2. 打印Test SPI Connect With Nor Flash Pass

**FPGA&RTL Params**

```c
spi -m 0 --nor
spi -m 1 --nor
spi -m 2 --nor
spi -m 3 --nor
```

## SPI FUNC功能测试

----
`RTL` `P0`

**Description**

1. spi1-func1-cpads-29-32，连接到spi3-func1-cpads-23-26
2. spi1-func1-cpads-80-83，连接到spi3-func1-cpads-39-42
3. spi2-func1-cpads-35-38，连接到spi0-func0-spads-4-7
4. 双方进行收发数据

**Expectation**

1. 数据对比正确
2. 打印Test SPI Function Mode Pass.

**FPGA&RTL Params**

```c
spi -m 0 --func 
spi -m 1 --func 
spi -m 2 --func 
```
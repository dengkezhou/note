# SD&MMC 相关测试例
###  测试数据描述

数据为0xxx-0xff的递增，到0xff后重新从0x00开始递增
当写入数据大于256个字节，0-255字节分别为0xxx-0xff，第257个字节开始又从0x00开始递增


## SD 中断模式读写

----
`FPGA` `RTL` `P0`

**Description**

1. SD设置为Default-Speed，中断模式
2. SD写1block大小的数据，再读取1block大小的数据

**Expectation**

1. 比较读写数据是否相同
2. 打印Test SD Default-Speed IRQ Mode Pass

**FPGA&RTL Params**

```c
sdmmc -p 1 -a 0 -f 25000 -w 4 -g 5 -i
sdmmc -p 2 -a 0 -f 25000 -w 4 -g 5 -i
```

## SD 1bit Bus-Width(10M)读写

----
`FPGA` `RTL` `P0`

**Description**

1. SD设置为1bit Bus-Width(10M) DMA模式
2. SD写1block大小的数据，再读取1block大小的数据

**Expectation**

1. 比较读写数据是否相同
2. 打印Test SD, DS/SDR12 mode, DMA, 1bit@10M, Pass

**FPGA&RTL Params**

```c
sdmmc -p 1 -a 0 -f 10000 -w 1 -g 5 -v
sdmmc -p 2 -a 0 -f 10000 -w 1 -g 5 -v
```

## SD Default-Speed(25Mhz 3.3V) DMA读写

----
`FPGA` `RTL` `P0`

**Description**

1. SD设置为Default-Speed，DMA模式
2. SD写1block大小的数据，再读取1block大小的数据

**Expectation**

1. 比较读写数据是否相同
2. 打印Test SD Default-Speed DMA Mode Pass

**FPGA&RTL Params**

```c
sdmmc -p 1 -a 0 -f 25000 -w 4 -g 5 -v
sdmmc -p 2 -a 0 -f 25000 -w 4 -g 5 -v
```

## SD High-Speed(50Mhz 3.3V) DMA读写

----
`FPGA` `RTL` `P0`

**Description**

1. SD设置为High-Speed，DMA模式
2. SD写1block大小的数据，再读取1block大小的数据

**Expectation**

1. 比较读写数据是否相同
2. 打印Test SD High-Speed DMA Mode Pass

**FPGA&RTL Params**

```c
sdmmc -p 1 -a 1 -f 50000 -w 4 -g 5 -v
sdmmc -p 2 -a 1 -f 50000 -w 4 -g 5 -v
```

## SD UHS-I SDR12(25Mhz 1.8V) DMA读写

----
`FPGA` `RTL` `P0`

**Description**

1. SD设置为UHS-I SDR12，DMA模式
2. SD写1block大小的数据，再读取1block大小的数据

**Expectation**

1. 比较读写数据是否相同
2. 打印Test SD, SDR12 mode, DMA, 4bit@25M, Pass

**FPGA&RTL Params**

```c
sdmmc -p 1 -a 0 -f 25000 -w 4 -g 5
sdmmc -p 2 -a 0 -f 25000 -w 4 -g 5
```

## SD UHS-I SDR25(50Mhz 1.8V) DMA读写

----
`FPGA` `RTL` `P0`

**Description**

1. SD设置为UHS-I SDR25，DMA模式
2. SD写1block大小的数据，再读取1block大小的数据

**Expectation**

1. 比较读写数据是否相同
2. 打印Test SD UHS-I SDR25 DMA Mode Pass

**FPGA&RTL Params**

```c
sdmmc -p 1 -a 1 -f 50000 -w 4 -g 5
sdmmc -p 2 -a 1 -f 50000 -w 4 -g 5
```

## SD UHS-I SDR50(100Mhz 1.8V) DMA读写

----
`FPGA` `RTL` `P0`

**Description**

1. SD设置为UHS-I SDR50，DMA模式
2. SD写1block大小的数据，再读取1block大小的数据

**Expectation**

1. 比较读写数据是否相同
2. 打印Test SD UHS-I SDR50 DMA Mode Pass

**FPGA&RTL Params**

```c
sdmmc -p 1 -a 2 -f 30000 -w 4 -g 5
sdmmc -p 2 -a 2 -f 30000 -w 4 -g 5
```


## SD UHS-I SDR104(208Mhz 1.8V) DMA读写

----
`FPGA` `RTL` `P0`

**Description**

1. SD设置为UHS-I SDR104，DMA模式
2. SD写1block大小的数据，再读取1block大小的数据

**Expectation**

1. 比较读写数据是否相同
2. 打印Test SD UHS-I SDR104 DMA Mode Pass

**FPGA&RTL Params**

```c
sdmmc -p 1 -a 3 -f 208000 -w 4 -g 5
sdmmc -p 2 -a 3 -f 208000 -w 4 -g 5
```

## SD UHS-I DDR50(50Mhz 1.8V) DMA读写

----
`FPGA` `RTL` `P0`

**Description**

1. SD设置为UHS-I DDR50，DMA模式
2. SD写1block大小的数据，再读取1block大小的数据

**Expectation**

1. 比较读写数据是否相同
2. 打印Test SD UHS-I DDR50 DMA Mode Pass

**FPGA&RTL Params**

```c
sdmmc -p 1 -a 4 -f 30000 -w 4 -g 5
sdmmc -p 2 -a 4 -f 30000 -w 4 -g 5
```

## eMMC 1bit Bus-Width(10M)读写

----
`FPGA` `RTL` `P0`

**Description**

1. eMMC设置为1bit Bus-Width(10M) DMA模式
2. eMMC写1block大小的数据，再读取1block大小的数据

**Expectation**

1. 比较读写数据是否相同
2. 打印Test eMMC, Legacy mode, DMA, 1bit@10M, Pass

**FPGA&RTL Params**

```c
sdmmc -p 0 -a 6 -f 10000 -w 1 -g 5
```


## eMMC 4bit Bus-Width(10M)读写

----
`FPGA` `RTL` `P0`

**Description**

1. eMMC设置为8bit Bus-Width(10M) DMA模式
2. eMMC写1block大小的数据，再读取1block大小的数据

**Expectation**

1. 比较读写数据是否相同
2. 打印Test eMMC, Legacy mode, DMA, 4bit@10M, Pass

**FPGA&RTL Params**

```c
sdmmc -p 0 -a 6 -f 10000 -w 4 -g 5
```

## eMMC Legacy(SDR 26Mhz) DMA读写

----
`FPGA` `RTL` `P0`

**Description**

1. eMMC设置为Legacy，DMA模式
2. eMMC写1block大小的数据，再读取1block大小的数据

**Expectation**

1. 比较读写数据是否相同
2. 打印Test eMMC, Legacy mode, DMA, 4bit@26M, Pass

**FPGA&RTL Params**

```c
sdmmc -p 0 -a 6 -f 26000 -w 4 -g 5
```

## eMMC HS(SDR 52Mhz) DMA读写

----
`FPGA` `RTL` `P0`

**Description**

1. eMMC设置为HS(SDR)，DMA模式
2. eMMC写1block大小的数据，再读取1block大小的数据

**Expectation**

1. 比较读写数据是否相同
2. 打印Test eMMC, High Speed SDR mode, DMA, 8bit@52M, Pass

**FPGA&RTL Params**

```c
sdmmc -p 0 -a 7 -f 52000 -w 8 -g 5
```

## eMMC HS(DDR 52Mhz) DMA读写

----
`FPGA` `RTL` `P0`

**Description**

1. eMMC设置为HS(DDR)，DMA模式
2. eMMC写1block大小的数据，再读取1block大小的数据

**Expectation**

1. 比较读写数据是否相同
2. 打印Test eMMC, High Speed DDR mode, DMA, 8bit@10M, Pass

**FPGA&RTL Params**

```c
sdmmc -p 0 -a 8 -f 52000 -w 8 -g 5
```

## eMMC HS200(SDR 200Mhz) DMA读写

----
`FPGA` `RTL` `P0`

**Description**

1. eMMC设置为HS200(SDR)，DMA模式
2. eMMC写1block大小的数据，再读取1block大小的数据

**Expectation**

1. 比较读写数据是否相同
2. 打印Test eMMC HS200(SDR) DMA Pass

**FPGA&RTL Params**

```c
sdmmc -p 0 -a 9 -f 200000 -w 8 -g 5
```

## eMMC HS400(DDR 200Mhz) DMA读写

----
`FPGA` `RTL` `P0`

**Description**

1. eMMC设置为HS400(DDR)，DMA模式
2. eMMC写1block大小的数据，再读取1block大小的数据

**Expectation**

1. 比较读写数据是否相同
2. 打印Test eMMC HS400(DDR) DMA Pass

**FPGA&RTL Params**

```c
sdmmc -p 0 -a 10 -f 200000 -w 8 -g 5
```

## eMMC HS400_ES(DDR 200Mhz) DMA读写

----
`FPGA` `RTL` `P0`

**Description**

1. eMMC设置为HS400_ES(DDR)，DMA模式
2. eMMC写1block大小的数据，再读取1block大小的数据

**Expectation**

1. 比较读写数据是否相同
2. 打印Test eMMC HS400_ES(DDR) DMA Pass

**FPGA&RTL Params**

```c
sdmmc -p 0 -a 11 -f 200000 -w 8 -g 5
```

## SD&eMMC 卡插拔中断

----
`FPGA` `P0`

**Description**

1. 插入SD卡，等待10S
2. 拔出SD卡

**Expectation**

1. 能正常产生中断
2. 打印Card was removed
3. 打印Card was inserted
4. 打印SD Insertion/Removal Test Pass

**FPGA&RTL Params**

```c
sdmmc -p 1 -g 6
```

# DMA 相关测试例

## DMA memtomem模式

----
`FPGA` `RTL` `P0`

**Description**

1. DMA配置成memtomem模式，从memory搬运8192(16 rtl)字节数据到memory

**Expectation**

1. 比较memory，数据比对正确
2. 打印Test DMA MemToMem Pass

**FPGA&RTL Params**

```c
dma --memtomem
```

## DMA memtodev dma0模式

----
`FPGA` `RTL` `P0`

**Description**

1. uart3配置成loopback模式
2. DMA0配置成memtodev模式，从memory搬运8192(16 rtl)字节数据uart3 tx
3. 在步骤2的同时，uart3用polling模式接收8192(16 rtl)字节

**Expectation**

1. 比较DMA搬移的数据和uart接收到的数据一致
2. 打印Test DMA MemToDev dma0 Pass

**FPGA&RTL Params**

```c
dma --memtodev dma0
```

## DMA devtomem dma0模式

----
`FPGA` `RTL` `P0`

**Description**

1. uart3配置成loopback模式
2. uart3用polling模式发送8192(16 rtl)字节
3. 在步骤2的同时，DMA0配置成devtomem模式，从uart3 rx搬运8192(16 rtl)字节数据到memory

**Expectation**

1. 比较uart发送的数据和DMA搬移的数据一致
2. 打印Test DMA DevToMem dma0 Pass

**FPGA&RTL Params**

```c
dma --devtomem dma0
```

## DMA devtodev dma0模式

----
`FPGA` `RTL` `P0`

**Description**

1. uart1和uart3配置成正常模式，并在外部通过导线交叉相连
2. uart1写64(16 rtl)字节到tx，DMA0配置成devtodev模式，dma从uart3 rx搬运64(16 rtl)字节到uart3 tx
3. 在步骤2的同时，从uart1 rx读64(16 rtl)字节数据

**Expectation**

1. 比较步骤2 uart1 tx和步骤3 uart1 rx的数据是否一致
2. 打印Test DMA DevToDev dma0 Pass

**FPGA&RTL Params**

```c
dma --devtodev dma0
```

## DMA memtodev dma1模式

----

`FPGA` `RTL` `P0`

**Description**

1. uart1配置成loopback模式
2. DMA1配置成memtodev模式，从memory搬运8192(16 rtl)字节数据uart tx
3. 在步骤2的同时，uart1用polling模式接收8192(16 rtl)字节

**Expectation**

1. 比较DMA搬移的数据和uart接收到的数据一致
2. 打印Test DMA MemToDev dma1 Pass

**FPGA&RTL Params**

```c
dma --memtodev dma1
```

## DMA devtomem dma1模式

----

`FPGA` `RTL` `P0`

**Description**

1. uart1配置成loopback模式
2. uart1用polling模式发送8192(16 rtl)字节
3. 在步骤2的同时，DMA1配置成devtomem模式，从uart1 rx搬运8192(16 rtl)字节数据到memory

**Expectation**

1. 比较uart发送的数据和DMA搬移的数据一致
2. 打印Test DMA DevToMem dma1 Pass

**FPGA&RTL Params**

```c
dma --devtomem dma1
```

## DMA devtodev dma1模式

----

`FPGA` `RTL` `P0`

**Description**

1. uart1和uart3配置成正常模式，并在外部通过导线交叉相连
2. uart3写64(16 rtl)字节到tx，DMA1配置成devtodev模式，dma从uart1 rx搬运64(16 rtl)字节到uart1 tx
3. 在步骤2的同时，从uart3 rx读64(16 rtl)字节数据

**Expectation**

1. 比较步骤2 uart3 tx和步骤3 uart3 rx的数据是否一致
2. 打印Test DMA DevToDev dma1 Pass

**FPGA&RTL Params**

```c
dma --devtodev dma1
```

## DMA多路memtomem模式

----
`FPGA` `RTL` `P0`

**Description**

1. DMA配置成memtomem模式，同时申请2路channel，分别并同时从memory搬运8192(16 rtl)数据到memory

**Expectation**

1. 分别比较2路memory数据，且比对正确
2. 打印Test DMA Multi-MemToMem Pass

**FPGA&RTL Params**

```c
dma --multi-memtomem
```

## DMA 8路memtomem speed测试

----
`FPGA` `RTL` `P0`

**Description**

1. DMA配置成memtomem模式，同时申请8路channel，分别并同时从memory搬运8192(8192 rtl)数据到memory

**Expectation**

1. 分别比较8路memory数据，且比对正确
2. 打印各路搬运花费时间与速度，打印总的起始到结束时间与总的速率

**FPGA&RTL Params**

```c
dma --speed
```

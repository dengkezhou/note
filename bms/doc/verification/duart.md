# DWC UART 相关测试例

#### 测试数据描述
测试数据单位由字节组成，每两个连续的字节满足：例如A(n) ,A(n+1) <br>
A(0) = 0， A(1) = 1 <br>
0x00<=A(n)<=0xff <br>
A(n+1) = A(n) +1 <br>
并且当A(n)=0xff时， A(n) +1 = 0，重新开始从0到255连续。<br>


## UART RS232读写模式+FIFO测试

----
`FPGA` `RTL` `P0`

**Description**

1. 将第一组串口(uart0,1)设置为RS232模式
2. uart0发送1024(rtl:32)bytes到uart1,uart1对比数据是否正确
3. uart1发送1024(rtl:32)bytes到uart0,uart0对比数据是否正确
4. 将第二组串口(uart2,3)设置为RS232模式，重复2、3步骤

**Expectation**

1. 两组串口交互下，步骤2和步骤3都数据对比正确
2. 打印Test Uart 0,1 RS232 Pass 
3. 打印Test Uart 2,3 RS232 Pass
4. 打印Test Uart FIFO Pass

**FPGA&RTL Params**

```c
duart -rf
```

## UART IrDA模式

----
`FPGA` `RTL` `P0`

**Description**

1. 将第一组串口(uart0,1)设置为IrDA模式 
2. uart0发送1024(rtl:32)bytes到uart1,uart1对比数据是否正确 
3. uart1发送1024(rtl:32)bytes到uart0,uart0对比数据是否正确
4. 将第二组串口(uart2,3)设置为IrDA模式，重复2、3步骤

**Expectation**

1. 两组串口交互下，步骤2和步骤3都数据对比正确
2. 打印Test Uart 0,1 IrDA Pass
3. 打印Test Uart 2,3 IrDA Pass

**FPGA&RTL Params**

```c
duart -ir
```

## UART Flowctrl模式

----
`FPGA` `RTL` `P0`

**Description**

1. 将第一组串口(uart0,1)设置为RS232, Flowctrl读写模式
2. uart0 写1024(rtl:32)bytes数据到uart1，uart1对比数据是否正确
3. uart1 写1024(rtl:32)bytes数据到uart0，uart0对比数据是否正确
4. 将第二组串口(uart2,3)设置为IrDA模式，重复2、3步骤

**Expectation**
1. 两组串口交互下，步骤2和步骤3都数据对比正确
2. 打印Test Uart 0,1 Flowctrl Pass
3. 打印Test Uart 2,3 Flowctrl Pass

**FPGA&RTL Params**

```c
duart -fl
```

## UART DMA模式

----
`FPGA` `RTL` `P0`

**Description**

1. 将第一组串口(uart0,1)设置为RS232,DMA读写模式
2. uart0写1024(rtl:32)bytes数据到uart1，uart1对比数据是否正确
3. uart1写1024(rtl:32)bytes数据到uart0，uart0对比数据是否正确
4. 将第二组串口(uart2,3)设置为RS232,DMA读写模式，重复2、3步骤

**Expectation**

1. 两组串口交互下，步骤2和步骤3都数据对比正确
2. 打印Test Uart 0,1 DMA Pass
3. 打印Test Uart 2,3 DMA Pass

**FPGA&RTL Params**

```c
duart -dm
```

## UART 与PC交互模式

----
`FPGA` `P0`

**Description**

1. 将uart0设置为RS232模式并拿232串口线连接PC 
2. uart0发送1024bytes到PC,PC对比数据是否正确 
3. PC发送1024bytes到uart0,uart0对比数据是否正确
4. 分别将uart0换成uart1,2,3再进行三次(1-3)的步骤

**Expectation**

1. 四个串口与PC的交互下，步骤2和步骤3都数据对比正确
2. 打印Test Uart 0 Interaction Pass 
3. 打印Test Uart 1 Interaction Pass
4. 打印Test Uart 2 Interaction Pass
5. 打印Test Uart 3 Interaction Pass

**FPGA&RTL Params**

```c
duart -in
```

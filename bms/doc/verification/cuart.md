# Cadence UART 相关测试例

#### 测试数据描述
测试数据单位由字节组成，每两个连续的字节满足：例如A(n) ,A(n+1) 

A(0) = 0， A(1) = 1 

0x00<=A(n)<=0xff 

A(n+1) = A(n) +1 

并且当A(n)=0xff时， A(n) +1 = 0，重新开始从0到255连续。

## UART normal 1byte读写模式

----
`FPGA` `RTL` `P0`

**Description**

1. 配置uart0，uart1为normal 1byte读写模式
2. uart0 先写1024bytes(rtl:32bytes)数据到uart1，uart1对比数据是否正确
3. uart1 先写1024bytes(rtl:32bytes)数据到uart0，uart0对比数据是否正确
4. 将uart2和uart3也进行一遍上述uart0和uart1的操作

**Expectation**

1. 在uart0+uart1以及uart2+uart3两组测试下，步骤2和步骤3数据对比正确
2. 打印Test Uart Normal 1byte Pass.

**FPGA&RTL Params**

```c
cuart -n1 -first 0 -second 1
cuart -n1 -first 2 -second 3
cuart -n1 -first 4 -second 5
cuart -n1 -first 6 -second 7
cuart -n1 -first 8 -second 9
cuart -n1 -first 10 -second 11
```

## UART normal 2byte读写模式

----
`FPGA` `RTL` `P0`

**Description**

1. 配置uart0，uart1为normal 2byte读写模式
2. uart0 先写1024bytes(rtl:32bytes)数据到uart1，uart1对比数据是否正确
3. uart1 先写1024bytes(rtl:32bytes)数据到uart0，uart0对比数据是否正确
4. 将uart2和uart3也进行一遍上述uart0和uart1的操作

**Expectation**

1. 在uart0+uart1以及uart2+uart3两组测试下，步骤2和步骤3数据对比正确
2. 打印Test Uart Normal 2byte Pass.

**FPGA&RTL Params**

```c
cuart -n2 -first 0 -second 1
cuart -n2 -first 2 -second 3
cuart -n2 -first 4 -second 5
cuart -n2 -first 6 -second 7
cuart -n2 -first 8 -second 9
cuart -n2 -first 10 -second 11
```

## UART normal 4byte读写模式

----
`FPGA` `RTL` `P0`

**Description**

1. 配置uart0，uart1为normal 4byte读写模式
2. uart0 先写1024bytes(rtl:32bytes)数据到uart1，uart1对比数据是否正确
3. uart1 先写1024bytes(rtl:32bytes)数据到uart0，uart0对比数据是否正确
4. 将uart2和uart3也进行一遍上述uart0和uart1的操作

**Expectation**

1. 在uart0+uart1以及uart2+uart3两组测试下，步骤2和步骤3数据对比正确
2. 打印Test Uart Normal 4byte Pass.

**FPGA&RTL Params**

```c
cuart -n4 -first 0 -second 1
cuart -n4 -first 2 -second 3
cuart -n4 -first 4 -second 5
cuart -n4 -first 6 -second 7
cuart -n4 -first 8 -second 9
cuart -n4 -first 10 -second 11
```

## UART Automatic Echo模式

----
`FPGA` `RTL` `P0`

**Description**

1. 配置uart0 Automatic Echo模式，uart1为normal 1byte模式
2. uart1 先写1024bytes(rtl:32bytes)数据到uart0，uart0对比数据是否正确，uart1也同时接收到uart0转发的数据，uart1对比数据是否正确
3. 配置uart1 Automatic Echo模式，uart0为normal 1byte模式
4. uart0先写1024bytes(rtl:32bytes)数据到uart1，uart1对比数据是否正确，uart0也同时接收到uart1转发的数据，uart0对比数据是否正确
5. 将uart2和3这组串口替换上述uart0和1，重复1~4的步骤

**Expectation**

1. 在uart0+uart1以及uart2+uart3两组测试下，步骤2和步骤3对比数据正确
2. 打印Test Uart Automatic Echo Pass.

**FPGA&RTL Params**

```c
cuart -ae -first 0 -second 1
cuart -ae -first 2 -second 3
cuart -ae -first 4 -second 5
cuart -ae -first 6 -second 7
cuart -ae -first 8 -second 9
cuart -ae -first 10 -second 11
```

## UART Local Loopback模式

----
`FPGA` `RTL` `P0`

**Description**

1. 配置uart0为Local Loopback模式
2. uart0 先写1024bytes(rtl:32bytes)数据，uart0将接收到自己发送的32bytes字节，对比数据是否正确
3. 将uart1,2,3也重复1~2的步骤。

**Expectation**

1. uart0~3数据都正确
2. 打印Test Uart Local Loopback Pass.

**FPGA&RTL Params**

```c
cuart -ll -port 0
cuart -ll -port 1
cuart -ll -port 2
cuart -ll -port 3
cuart -ll -port 4
cuart -ll -port 5
cuart -ll -port 6
cuart -ll -port 7
cuart -ll -port 8
cuart -ll -port 9
cuart -ll -port 10
cuart -ll -port 11
```

## UART IrDA模式

----
`FPGA` `RTL` `P0`

**Description**

1. 配置uart0，uart1为IrDA读写模式
2. uart0 先写1024bytes(rtl:32bytes)数据到uart1，uart1对比数据是否正确
3. uart1 先写1024bytes(rtl:32bytes)数据到uart0，uart0对比数据是否正确
4. 将uart2和uart3也进行一遍上述uart0和uart1的操作

**Expectation**

1. 在uart0+uart1以及uart2+uart3两组测试下，步骤2和步骤3数据对比正确
2. 打印Test Uart IrDA Pass.

**FPGA&RTL Params**

```c
cuart -ir -first 0 -second 1
cuart -ir -first 2 -second 3
cuart -ir -first 4 -second 5
cuart -ir -first 6 -second 7
cuart -ir -first 8 -second 9
cuart -ir -first 10 -second 11
```

## UART Flowctrl模式

----
`FPGA` `RTL` `P0`

**Description**
1. 配置uart0，uart1为自动硬件流控读写模式
2. uart0 先写1024bytes(rtl:32bytes)数据到uart1，uart1对比数据是否正确
3. uart1 先写1024bytes(rtl:32bytes)数据到uart0，uart0对比数据是否正确
4. 将uart2和uart3也进行一遍上述uart0和uart1的操作

**Expectation**

1. 在uart0+uart1以及uart2+uart3两组测试下，步骤2和步骤3数据对比正确
2. 打印Test Uart IrDA Pass.

**FPGA&RTL Params**

```c
cuart -fl -first 2 -second 3
```

## UART DMA模式

----
`FPGA`  `RTL` `P0`

**Description**

1. 配置uart0，uart1为DMA读写模式
2. uart0 先写1024bytes(rtl:32bytes)数据到uart1，uart1对比数据是否正确
3. uart1 先写1024bytes(rtl:32bytes)数据到uart0，uart0对比数据是否正确
4. 将uart2和uart3也进行一遍上述uart0和uart1的操作

**Expectation**

1. 在uart0+uart1以及uart2+uart3两组测试下，步骤2和步骤3数据对比正确
2. 打印Test Uart DMA Pass.

**FPGA&RTL Params**

```c
cuart -dm -first 0 -second 1
cuart -dm -first 2 -second 3
cuart -dm -first 4 -second 5
cuart -dm -first 6 -second 7
cuart -dm -first 8 -second 9
cuart -dm -first 10 -second 11
```

## UART 与PC交互模式

----
`FPGA` `P0`

**Description**

1. 配置uart0为RS232读写模式
2. PC端传输1024bytes(rtl:32bytes)数据给uart0
3. uart0把接受到的数据传输给PC，PC端比较数据是否正确
4. 将uart1,2,3重复上述1~3步骤

**Expectation**

1. uart0,1,2,3的步骤3数据对比正确
2. 打印Test Uart Interaction Pass.

**FPGA&RTL Params**

```c
cuart -in -port 0
cuart -in -port 1
cuart -in -port 2
cuart -in -port 3
cuart -in -port 4
cuart -in -port 5
cuart -in -port 6
cuart -in -port 7
cuart -in -port 8
cuart -in -port 9
cuart -in -port 10
cuart -in -port 11
```

## UART FUNC功能测试

----
`RTL` `P0`

**Description**

1. uart3-func1-cpads-14-15，连接到uart1-func0-spads-11-12
2. uart3-func1-cpads-72-75，连接到uart2-func1-cpads-68-71
3. uart3-func2-cpads-80-83，连接到uart2-func1-cpads-89-92
4. uart4-func1-cpads-99-100,连接到uart5-func1-cpads-101-102
5. uart6-func1-cpads-103-104，连接到uart7-func1-cpads-105-106
6. uart8-func1-cpads-107-108，连接到uart9-func1-cpads-109-110
7. uart10-func1-cpads-111-112，连接到uart11-func1-cpads-78-79
8. uart4-func2-cpads-23-24,连接到uart5-func2-cpads-25-26
9. uart6-func2-cpads-27-28,连接到uart7-func1-cpads-94-95
10. uart8-func1-cpads-96-97,连接到uart7-func1-cpads-94-95
11. 双方进行收发数据

**Expectation**

1. 数据对比正确
2. 打印Test Uart Function Mode Pass.

**FPGA&RTL Params**

```c
cuart -fc -port 0
cuart -fc -port 1
cuart -fc -port 2
cuart -fc -port 3
cuart -fc -port 4
cuart -fc -port 5
cuart -fc -port 6
cuart -fc -port 7
cuart -fc -port 8
cuart -fc -port 9
```

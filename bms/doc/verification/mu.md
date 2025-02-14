# MU 相关测试例


## C_MU 读写测试 

----
`FPGA` `RTL` `P0`

**Description**
1. SAP端使能a2b_irq[x]
2. CPU端使能b2a_irq[x]，填充24字节数据到数据寄存器，触发a2b_irq[x]数据寄存器非空中断
3. SAP端接收到a2b_irq[x]数据寄存器非空中断后，接收数据,并触发b2a_irq[x]数据寄存器空中断
4. SAP端填充收到的24字节数据到数据寄存器，触发b2a_irq[x]数据寄存器非空中断
5. CPU端接收到b2a_irq[x]数据寄存器非空中断后，接收数据,并触发a2b_irq[x]数据寄存器空中断


**Expectation**

1. 步骤3 CPU端能收到中断并且收到数据
2. 步骤5 SAP端能收到中断并且收到的数据与步骤2发送的一致
3. SAP端打印 Test C_MU ReadWrite Pass

**FPGA&RTL Params**

```c
(SAP)mu -p 0 -i 0 --rw --sap (CPU)mu -p 0 -i 0 --wr --cpu 
(SAP)mu -p 0 -i 1 --rw --sap (CPU)mu -p 0 -i 1 --wr --cpu 
```
## S_MU 读写测试 

----
`FPGA` `RTL` `P0`

**Description**
1. SAP端使能a2b_irq[x]
2. CPU端使能b2a_irq[x]，填充24字节数据到数据寄存器，触发a2b_irq[x]数据寄存器非空中断
3. SAP端接收到a2b_irq[x]数据寄存器非空中断后，接收数据,并触发b2a_irq[x]数据寄存器空中断
4. SAP端填充收到的24字节数据到数据寄存器，触发b2a_irq[x]数据寄存器非空中断
5. CPU端接收到b2a_irq[x]数据寄存器非空中断后，接收数据,并触发a2b_irq[x]数据寄存器空中断

**Expectation**

1. 步骤3 SAP端能收到中断并且收到数据
2. 步骤5 CPU端能收到中断并且收到的数据与步骤2发送的一致
3. CPU端打印 Test S_MU ReadWrite Pass

**FPGA&RTL Params**

```c
(SAP)mu -p 1 -i 0 --rw --sap (CPU)mu -p 1 -i 0 --wr --cpu 
(SAP)mu -p 1 -i 1 --rw --sap (CPU)mu -p 1 -i 1 --wr --cpu 
```

## C_MU Atomic Lock寄存器读写测试

----
`FPGA` `RTL` `P0`

**Description**
1. Atomic Lock0 ~ Atomic Lock31共32个寄存器，SAP端写入0x1
2. CPU端读出Atomic Lock0 ~ Atomic Lock31共32个寄存器的值


**Expectation**

1. 步骤2中读取到32个寄存器的值为步骤一中写入的值
3. CPU端打印 Test C_MU Atomic Lock Pass

**FPGA&RTL Params**

```c
(SAP)mu -p 0 --al --rw --sap (CPU)mu -p 0 --al --wr --cpu  
```

## S_MU Atomic Lock寄存器读写测试

----
`FPGA` `RTL` `P0`

**Description**
1. Atomic Lock0 ~ Atomic Lock31共32个寄存器，SAP端写入0x1
2. CPU端读出Atomic Lock0 ~ Atomic Lock31共32个寄存器的值


**Expectation**

1. 步骤2中读取到32个寄存器的值为步骤一中写入的值
3. CPU端打印 Test S_MU Atomic Lock Pass

**FPGA&RTL Params**

```c
(SAP)mu -p 1 --al --rw --sap (CPU)mu -p 1 --al --wr --cpu 
```
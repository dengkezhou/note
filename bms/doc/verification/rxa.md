# RXA 相关测试例

## RXA 单指令功能验证

----
`FPGA` `RTL` `P0`

**Description**

1. RXA执行单个指令xxx，比较预期结果

**Expectation**

1. 出现Exec done中断，结果符合执行的单指令预期
2. 打印Test RXA Single CMD xxx Pass

**FPGA&RTL Params**

```c
rxa -c 0 -n NOP
rxa -c 0 -n LD
rxa -c 0 -n LD.ADD
rxa -c 0 -n ST
rxa -c 0 -n VLD
rxa -c 0 -n VLDQ.XOR
rxa -c 0 -n VLD.W
rxa -c 0 -n VLDQ.W
rxa -c 0 -n VSTQ
rxa -c 0 -n PRFC
rxa -c 0 -n XOR
rxa -c 0 -n ROR
rxa -c 0 -n RORI
rxa -c 0 -n SWAP
rxa -c 0 -n ADDSL
rxa -c 0 -n ADDI
rxa -c 0 -n ADD
rxa -c 0 -n SUB
rxa -c 0 -n NEG
rxa -c 0 -n MUL
rxa -c 0 -n MULH
rxa -c 0 -n MULHU
rxa -c 0 -n VXOR
rxa -c 0 -n VSWAP
rxa -c 0 -n VADD.D
rxa -c 0 -n VSUB.D
rxa -c 0 -n VMUL.D
rxa -c 0 -n VDIV.D
rxa -c 0 -n VSQRT.D
rxa -c 0 -n VCVT.D.W
rxa -c 0 -n RXSFRM
rxa -c 0 -n RXSSP
rxa -c 0 -n RXSMXA
rxa -c 0 -n RXB
rxa -c 0 -n BRK
rxa -c 0 -n BGT
rxa -c 0 -n END
```

## RXA Blake2b功能

----
`FPGA` `RTL` `P0`

**Description**

1. 输入78字节数，计算Blake2b
2. 计算得到的值与软件计算结果对比

**Expectation**

1. 结果对比是否一致
2. 打印Test RXA Blake2b Pass
   
**FPGA&RTL Params**

```c
rxa -c 0 -i 0 -b 8 -n RXBLK2B
```

## RXA Aes1R4功能

----
`FPGA` `RTL` `P0`

**Description**

1. 输入64字节数，计算Aes1R4，得到2M数据
2. 计算得到的值与软件计算结果对比

**Expectation**

1. 结果对比是否一致
2. 打印Test RXA Aes1R4 Pass
   
**FPGA&RTL Params**

```c
rxa -c 0 -i 0 -b 8 -n RXAES1RX4
```

## RXA Aes1R4 Hash功能

----
`FPGA` `RTL` `P0`

**Description**

1. 输入2M字节数，计算Aes1R4 Hash
2. 计算得到的值与软件计算结果对比

**Expectation**

1. 结果对比是否一致
2. 打印Test RXA Aes1R4 Hash Pass
   
**FPGA&RTL Params**

```c
rxa -c 0 -n "Aes1R4 Hash"
```

## RXA Aes1R4 MUTI功能

----
`FPGA` `RTL` `P0`

**Description**

1. 输入2M字节数，计算Aes1R4 Muti 
2. 计算得到的值与软件计算结果对比

**Expectation**

1. 结果对比是否一致
2. 打印Test RXA Aes1R4 Muti Pass
   
**FPGA&RTL Params**

```c
rxa -c 0 -n RXAES1RX4_MUTI
```

## RXA Aes4R4功能

----
`FPGA` `RTL` `P0`

**Description**

1. 输入64字节数，计算Aes4R4
2. 计算得到的值与软件计算结果对比

**Expectation**

1. 结果对比是否一致
2. 打印Test RXA Aes4R4 Pass
   
**FPGA&RTL Params**

```c
rxa -c 0 -i 0 -b 1 -n RXAES4RX4
```

## RXA 读写general registers功能

----
`FPGA` `RTL` `P0`

**Description**

1. 通过DBG_GREG_Wn寄存器，写入v1_0寄存器值0xaaaaaaaaaaaaaaaa，读出v1_0的值

**Expectation**

1. 读出的值为0xaaaaaaaaaaaaaaaa
2. 打印Test RXA Read&Write General Register Pass
   
**FPGA&RTL Params**

```c
rxa -c 2
```

## RXA step模式执行指令

----
`FPGA` `RTL` `P0`

**Description**

1. rxa配置成step指令模式，并把DBG_CTRL配置成2

**Expectation**

1. 出现Exec paused中断，DBG_PC为2
2. 打印Test RXA Read&Write General Register Pass
   
**FPGA&RTL Params**

```c
rxa -c 3
```

## RXA break匹配暂停功能

----
`FPGA` `RTL` `P0`

**Description**

1. rxa配置成normal指令模式，并将DBG_BRK0，DBG_BRK1，DBG_BRK2，DBG_BRK3，DBG_BRK4配置成1，3，7，13，21
2. 出现Exec paused中断，DBG_PC符合DBG_BRKn设置，并配置rxa重新开始，知道出现第5次Exec paused，且DBG_PC符合DBG_BRK4设置

**Expectation**

1. 打印Test RXA Break Func Pass
   
**FPGA&RTL Params**

```c
rxa -c 4
```

## RXA normal 1-instruction模式功能

----
`FPGA` `RTL` `P0`

**Description**

1. rxa配置成normal 1-instruction指令模式
2. 运行randomx联调rxa模块，能正常产生1个nonce(应用已经产生好的指令来运行rxa模块，且指令由2048轮减少到2轮)

**Expectation**

1. 步骤2产生的结果与randomx在pc端跑的结果一致
2. 打印Test RXA 1-instruction Pass
   
**FPGA&RTL Params**

```c
rxa -c 5 -b 1
```

## RXA normal 2-instruction模式功能

----
`FPGA` `RTL` `P1`

**Description**

1. rxa配置成normal 2-instruction指令模式
2. 运行randomx联调rxa模块，能正常产生1个nonce(应用已经产生好的指令来运行rxa模块，且指令由2048轮减少到2轮)

**Expectation**

1. 步骤2产生的结果与randomx在pc端跑的结果一致
2. 打印Test RXA 2-instruction Pass
   
**FPGA&RTL Params**

```c
rxa -c 5 -b 2
```

## RXA normal 4-instruction模式功能

----
`FPGA` `RTL` `P1`

**Description**

1. rxa配置成normal 4-instruction指令模式
2. 运行randomx联调rxa模块，能正常产生1个nonce(应用已经产生好的指令来运行rxa模块，且指令由2048轮减少到2轮)

**Expectation**

1. 步骤2产生的结果与randomx在pc端跑的结果一致
2. 打印Test RXA 4-instruction Pass
   
**FPGA&RTL Params**

```c
rxa -c 5 -b 4
```

## RXA normal 8-instruction模式功能

----
`FPGA` `RTL` `P0`

**Description**

1. rxa配置成normal 8-instruction指令模式
2. 运行randomx联调rxa模块，能正常产生1个nonce(应用已经产生好的指令来运行rxa模块，且指令由2048轮减少到2轮)

**Expectation**

1. 步骤2产生的结果与randomx在pc端跑的结果一致
2. 打印Test RXA 8-instruction Pass
   
**FPGA&RTL Params**

```c
rxa -c 5 -b 8
```

## RXA normal 8-instruction模式压力功能

----
`FPGA` `P0`

**Description**

1. rxa配置成normal 8-instruction指令模式
2. 运行randomx联调rxa模块，并运行1天

**Expectation**

1. 步骤2产生的结果与randomx在pc端跑的结果一致
2. 打印Test RXA 8-instruction Pass
   
**FPGA&RTL Params**

```c
rxa -c 6 -b 8
```

## RXA 与挖矿软件联调

----
`FPGA` `P2`

**Description**

1. 通过x9矿机主控板，运行randomx挖矿代码，通过spi接口与fpga交互
2. 控制bms端的randomx代码和rxa模块，执行挖矿程序，并把结果发送会x9主控板，x9主控板把结果上传矿池

**Expectation**

1. 矿池能接口bms上传的nonce
   
**FPGA&RTL Params**

```c
rxa -c 7 -b 1
rxa -c 7 -b 8
```

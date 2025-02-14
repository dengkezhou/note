# TTC 相关测试例

## TTC在Interval模式下, 计数器递增测试

----
`FPGA` `RTL` `P0`

**Description**

1. 在Interval模式下，计数器配置成递增，设置1000ms(10ms rtl)后产生中断

**Expectation**

1. 能正常中断，打印Test Interval Timing, Incrementing count Pass

**FPGA&RTL Params**

```c
timer -u 0 -c 0 -m 1 -r 1 -s 1000
timer -u 0 -c 1 -m 1 -r 1 -s 1000
timer -u 0 -c 2 -m 1 -r 1 -s 1000
timer -u 1 -c 0 -m 1 -r 1 -s 1000
timer -u 1 -c 1 -m 1 -r 1 -s 1000
timer -u 1 -c 2 -m 1 -r 1 -s 1000
timer -u 2 -c 0 -m 1 -r 1 -s 1000
timer -u 2 -c 1 -m 1 -r 1 -s 1000
timer -u 2 -c 2 -m 1 -r 1 -s 1000 
```

## TTC在Interval模式下, 计数器递减测试

----
`FPGA` `RTL` `P0`

**Description**

1. 在Interval模式下，计数器配置成递减，设置1000ms(10ms rtl)后产生中断

**Expectation**

1. 能正常中断，打印Test Interval Timing, decrementing count Pass

**FPGA&RTL Params**

```c
timer -u 0 -c 0 -m 1 -r 0 -s 1000
timer -u 0 -c 1 -m 1 -r 0 -s 1000
timer -u 0 -c 2 -m 1 -r 0 -s 1000
timer -u 1 -c 0 -m 1 -r 0 -s 1000
timer -u 1 -c 1 -m 1 -r 0 -s 1000
timer -u 1 -c 2 -m 1 -r 0 -s 1000
timer -u 2 -c 0 -m 1 -r 0 -s 1000
timer -u 2 -c 1 -m 1 -r 0 -s 1000
timer -u 2 -c 2 -m 1 -r 0 -s 1000
```

## TTC在overflow模式下, 计数器递增测试

----
`FPGA` `RTL` `P0`

**Description**

1. 在overflow模式下，计数器配置成递增，超过定时最大值后产生中断

**Expectation**

1. 能正常中断，打印Test overflow Timing, Incrementing count Pass

**FPGA&RTL Params**

```c
timer -u 0 -c 0 -m 0 -r 1 
timer -u 0 -c 1 -m 0 -r 1 
timer -u 0 -c 2 -m 0 -r 1 
timer -u 1 -c 0 -m 0 -r 1 
timer -u 1 -c 1 -m 0 -r 1 
timer -u 1 -c 2 -m 0 -r 1 
timer -u 2 -c 0 -m 0 -r 1
timer -u 2 -c 1 -m 0 -r 1
timer -u 2 -c 2 -m 0 -r 1
```

## TTC在overflow模式下, 计数器递减测试

----
`FPGA` `RTL` `P0`

**Description**

1. 在overflow模式下，计数器配置成递减，超过定时器最大值后产生中断

**Expectation**

1. 能正常中断，打印Test overflow Timing, decrementing count Pass

**FPGA&RTL Params**

```c
timer -u 0 -c 0 -m 0 -r 0 
timer -u 0 -c 1 -m 0 -r 0 
timer -u 0 -c 2 -m 0 -r 0 
timer -u 1 -c 0 -m 0 -r 0 
timer -u 1 -c 1 -m 0 -r 0 
timer -u 1 -c 2 -m 0 -r 0 
timer -u 2 -c 0 -m 0 -r 0
timer -u 2 -c 1 -m 0 -r 0
timer -u 2 -c 2 -m 0 -r 0
```

## TTC match模式测试

----
`FPGA` `RTL` `P0`

**Description**

1. 在overflow模式下，配置match模式，配置match寄存器，使之分别在1000ms，2000ms，3000ms(10ms, 20ms, 30ms rtl)后产生中断

**Expectation**

1. 能正常中断，对应match1 match2  match3 分别产生打印Test  MATCH1   Pass ,Test  MATCH2   Pass,Test  MATCH3   Pass


**FPGA&RTL Params**

```c
timer -u 0 -c 0 -m 0 -r 1 -t 1000:2000:3000
timer -u 0 -c 1 -m 0 -r 1 -t 1000:2000:3000
timer -u 0 -c 2 -m 0 -r 1 -t 1000:2000:3000
timer -u 1 -c 0 -m 0 -r 1 -t 1000:2000:3000
timer -u 1 -c 1 -m 0 -r 1 -t 1000:2000:3000
timer -u 1 -c 2 -m 0 -r 1 -t 1000:2000:3000
timer -u 2 -c 0 -m 0 -r 1 -t 1000:2000:3000
timer -u 2 -c 1 -m 0 -r 1 -t 1000:2000:3000
timer -u 2 -c 2 -m 0 -r 1 -t 1000:2000:3000
```

## TTC级联测试

----
`FPGA` `RTL` `P0`

**Description**

1. 将TTC配置成Interval模式,将3个32位的Counter级联

**Expectation**

1. 能正常产生Interval中断，并打印Cascade test Pass

**FPGA&RTL Params**

```c
timer -u 0 -c 0 -o 1
timer -u 1 -c 0 -o 1
timer -u 2 -c 0 -o 1

```

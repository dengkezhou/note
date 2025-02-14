# E906 IRQ 相关测试例

## IRQ软中断测试

----
`FPGA` `RTL` `P0`

**Description**

1. 配置寄存器，使之能在1s(0.01s rtl)后触发软中断

**Expectation**

1. 能正常触发软中断，打印Test Soft IRQ Pass

**FPGA&RTL Params**

```c
irq --sirq 0
```

## IRQcore timer中断测试

----
`FPGA` `RTL` `P0`

**Description**

1. 配置寄存器，使之能在1s(0.01s rtl)后触发core timer中断

**Expectation**

1. 能正常触发core timer中断，打印Test Coret IRQ Pass

**FPGA&RTL Params**

```c
irq --coret 0
```

## IRQ外部设备中断测试

----
`FPGA` `RTL` `P0`

**Description**

1. 调用外部watchdog接口，使之能在1s(0.01s rtl)后触发外部watchdog中断

**Expectation**

1. 能正常触发外部watchdog中断，打印Test External IRQ(16) Pass

**FPGA&RTL Params**

```c
irq --eirq 0
```

## IRQ NMI异常

----
`FPGA` `RTL` `P0`

**Description**

1. 调用外部watchdog接口，使之能在1s(0.01s rtl)后触发NMI中断

**Expectation**

1. 能正常触发NMI中断，打印Test NMI IRQ Pass

**FPGA&RTL Params**

```c
irq --nmi 0
```

## IRQ EXT异常

----
`FPGA` `RTL` `P0`

**Description**

1. 调用外部watchdog接口，使之能在1s(0.01s rtl)后触发外部中断

**Expectation**

1. 能正常触发外部中断，打印Test External IRQ(11) Pass

**FPGA&RTL Params**

```c
irq --extirq 0
```


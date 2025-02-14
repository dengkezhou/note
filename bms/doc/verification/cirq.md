# C920 IRQ 相关测试例

## IRQ软中断测试

----
`FPGA` `RTL` `P0`

**Description**

1. 配置寄存器，使之能在1s(0.01s rtl)后触发软中断(rtl下需要使能cci)

**Expectation**

1. 能正常触发软中断，打印Test Soft IRQ Pass

**FPGA&RTL Params**

```c
irq --sirq 0
sysm --powerupcore-test 2;irq --sirq 1
sysm --powerupcore-test 3;irq --sirq 2
sysm --powerupcore-test 4;irq --sirq 3
sysm --powerupcore-test 5;irq --sirq 4
sysm --powerupcore-test 6;irq --sirq 5
sysm --powerupcore-test 7;irq --sirq 6
sysm --powerupcore-test 8;irq --sirq 7
```

## IRQcore timer中断测试

----
`FPGA` `RTL` `P0`

**Description**

1. 配置寄存器，使之能在1s后触发core timer中断(rtl下需要使能cci)

**Expectation**

1. 能正常触发core timer中断，打印Test Coret IRQ Pass

**FPGA&RTL Params**

```c
irq --timer 0
sysm --powerupcore-test 2;irq --timer 1
sysm --powerupcore-test 3;irq --timer 2
sysm --powerupcore-test 4;irq --timer 3
sysm --powerupcore-test 5;irq --timer 4
sysm --powerupcore-test 6;irq --timer 5
sysm --powerupcore-test 7;irq --timer 6
sysm --powerupcore-test 8;irq --timer 7
```

## IRQ外部设备中断测试

----
`FPGA` `RTL` `P0`

**Description**

1. 调用外部watchdog接口，使之能触发外部watchdog中断(rtl下需要使能cci)

**Expectation**

1. 能正常触发外部watchdog中断，打印Test External IRQ Pass

**FPGA&RTL Params**

```c
irq --eirq 0
sysm --powerupcore-test 2;irq --eirq 1
sysm --powerupcore-test 3;irq --eirq 2
sysm --powerupcore-test 4;irq --eirq 3
sysm --powerupcore-test 5;irq --eirq 4
sysm --powerupcore-test 6;irq --eirq 5
sysm --powerupcore-test 7;irq --eirq 6
sysm --powerupcore-test 8;irq --eirq 7
```

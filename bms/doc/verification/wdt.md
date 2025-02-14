# WDT 相关测试例

## SAP_WDT Reset测试

----
`FPGA` `RTL` `P0`

**Description**
1. SAP_WDT使能Reset Mode，设置1s(1s rtl)超时


**Expectation**

1. CPU端和SAP端都能够产生复位
2. 打印Test WDT Reset Pass

**FPGA&RTL Params**

```c
wdt -r
```

## CPU_WDT External reset测试

----
`FPGA` `RTL` `P0`

**Description**
1. CPU_WDT使能External，设置1s(1s rtl)超时

**Expectation**

1. CPU端和SAP端都能够产生复位
2. 打印Test WDT External Pass

**FPGA&RTL Params**

```c
wdt -e
```

## CPU_WDT Restart测试

----
`FPGA` `RTL` `P0`

**Description**

1. WDT使能interrupt，设置1s超时，并重复三次

**Expectation**

1. 能正常触发中断，打印Test WDT Restart Pass

**FPGA&RTL Params**

```c
wdt -a --cpu
```
## SAP_WDT Restart测试

----
`FPGA` `RTL` `P0`

**Description**

1. WDT使能interrupt，设置1s超时，并重复三次

**Expectation**

1. 能正常触发中断，打印Test WDT Restart Pass

**FPGA&RTL Params**

```c
wdt -a --sap
```


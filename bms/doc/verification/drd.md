# DRD 相关测试例

## DRD usb3.0 Device&Host  Loopback
----
`FPGA` `RTL` `P0`

**Description**

1. drd配置成支持usb3.0协议模式，并配置成loopback模式

**Expectation**

1. 读写的数据一致
2. 打印Test DRD usb3.0 Device&Host Loopback Mode Pass

**FPGA&RTL Params**

```c
drd -p 0 -q 1 -v 3 -l #mode:3.0, host:0, dev:1
drd -p 1 -q 0 -v 3 -l #mode:3.0, host:1, dev:0
drd -p 2 -q 3 -v 3 -l #mode:3.0, host:2, dev:3
drd -p 3 -q 2 -v 3 -l #mode:3.0, host:3, dev:2
```

## DRD usb2.0 Device&Host  Loopback
----
`FPGA` `RTL` `P0`

**Description**

1. drd配置成支持usb2.0协议模式，并配置成loopback模式

**Expectation**

1. 读写的数据一致
2. 打印Test DRD usb2.0 Device&Host Loopback Mode Pass

**FPGA&RTL Params**

```c
drd -p 0 -q 1 -v 2 -l #mode:2.0, host:0, dev:1
drd -p 1 -q 0 -v 2 -l #mode:2.0, host:1, dev:0
drd -p 2 -q 3 -v 2 -l #mode:2.0, host:2, dev:3
drd -p 3 -q 2 -v 2 -l #mode:2.0, host:3, dev:2
```
## DRD usb2.0 EP端点测试
----
`FPGA` `RTL` `P0`

**Description**

1. drd配置成支持usb2.0协议模式，测试端点

**Expectation**

1. 读写的数据一致
2. 打印Test DRD ep%d Test Pass.

**FPGA&RTL Params**

```c
drd -p 0 -q 1 -v 2 -e 1 #mode:2.0, host:0, dev:1, ep:1
drd -p 0 -q 1 -v 2 -e 2 #mode:2.0, host:0, dev:1, ep:2
drd -p 0 -q 1 -v 2 -e 3 #mode:2.0, host:0, dev:1, ep:3
drd -p 0 -q 1 -v 2 -e 4 #mode:2.0, host:0, dev:1, ep:4
drd -p 0 -q 1 -v 2 -e 5 #mode:2.0, host:0, dev:1, ep:5
drd -p 0 -q 1 -v 2 -e 6 #mode:2.0, host:0, dev:1, ep:6
drd -p 0 -q 1 -v 2 -e 7 #mode:2.0, host:0, dev:1, ep:7
drd -p 2 -q 3 -v 2 -e 1 #mode:2.0, host:2, dev:3, ep:1  
drd -p 2 -q 3 -v 2 -e 2 #mode:2.0, host:2, dev:3, ep:2
drd -p 2 -q 3 -v 2 -e 3 #mode:2.0, host:2, dev:3, ep:3
drd -p 2 -q 3 -v 2 -e 4 #mode:2.0, host:2, dev:3, ep:4
drd -p 2 -q 3 -v 2 -e 5 #mode:2.0, host:2, dev:3, ep:5
drd -p 2 -q 3 -v 2 -e 6 #mode:2.0, host:2, dev:3, ep:6
drd -p 2 -q 3 -v 2 -e 7 #mode:2.0, host:2, dev:3, ep:7

```

## DRD usb3.0 EP端点测试
----
`FPGA` `RTL` `P0`

**Description**

1. drd配置成支持usb3.0协议模式，测试端点

**Expectation**

1. 读写的数据一致
2. 打印Test DRD ep%d Test Pass.

**FPGA&RTL Params**

```c
drd -p 0 -q 1 -v 3 -e 1 #mode:3.0, host:0, dev:1, ep:1
drd -p 0 -q 1 -v 3 -e 2 #mode:3.0, host:0, dev:1, ep:2
drd -p 0 -q 1 -v 3 -e 3 #mode:3.0, host:0, dev:1, ep:3
drd -p 0 -q 1 -v 3 -e 4 #mode:3.0, host:0, dev:1, ep:4
drd -p 0 -q 1 -v 3 -e 5 #mode:3.0, host:0, dev:1, ep:5
drd -p 0 -q 1 -v 3 -e 6 #mode:3.0, host:0, dev:1, ep:6
drd -p 0 -q 1 -v 3 -e 7 #mode:3.0, host:0, dev:1, ep:7
drd -p 2 -q 3 -v 3 -e 1 #mode:3.0, host:2, dev:3, ep:1
drd -p 2 -q 3 -v 3 -e 2 #mode:3.0, host:2, dev:3, ep:2
drd -p 2 -q 3 -v 3 -e 3 #mode:3.0, host:2, dev:3, ep:3
drd -p 2 -q 3 -v 3 -e 4 #mode:3.0, host:2, dev:3, ep:4
drd -p 2 -q 3 -v 3 -e 5 #mode:3.0, host:2, dev:3, ep:5
drd -p 2 -q 3 -v 3 -e 6 #mode:3.0, host:2, dev:3, ep:6
drd -p 2 -q 3 -v 3 -e 7 #mode:3.0, host:2, dev:3, ep:7

```



## DRD usb2.0 传输模式测试
----
`FPGA` `RTL` `P0`

**Description**

1. drd配置成支持usb2.0协议模式，测试四种传输模式

**Expectation**

1. 读写的数据一致
2. 打印Test DRD transfer mode%d Test Pass.

**FPGA&RTL Params**

```c
drd -p 0 -q 1 -v 2 -t 1 #mode:2.0, host:0, dev:1, trans:1
drd -p 0 -q 1 -v 2 -t 2 #mode:2.0, host:0, dev:1, trans:2
drd -p 0 -q 1 -v 2 -t 3 #mode:2.0, host:0, dev:1, trans:3
drd -p 2 -q 3 -v 2 -t 1 #mode:2.0, host:2, dev:3, trans:1
drd -p 2 -q 3 -v 2 -t 2 #mode:2.0, host:2, dev:3, trans:2
drd -p 2 -q 3 -v 2 -t 3 #mode:2.0, host:2, dev:3, trans:3

```

## DRD usb3.0 传输模式测试
----
`FPGA` `RTL` `P0`

**Description**

1. drd配置成支持usb3.0协议模式，测试四种传输模式

**Expectation**

1. 读写的数据一致
2. 打印Test DRD transfer mode%d Test Pass.

**FPGA&RTL Params**

```c
drd -p 0 -q 1 -v 3 -t 1 #mode:3.0, host:0, dev:1, trans:1
drd -p 0 -q 1 -v 3 -t 2 #mode:3.0, host:0, dev:1, trans:2
drd -p 0 -q 1 -v 3 -t 3 #mode:3.0, host:0, dev:1, trans:3
drd -p 2 -q 3 -v 3 -t 1 #mode:3.0, host:2, dev:3, trans:1
drd -p 2 -q 3 -v 3 -t 2 #mode:3.0, host:2, dev:3, trans:2
drd -p 2 -q 3 -v 3 -t 3 #mode:3.0, host:2, dev:3, trans:3 

```



## DRD usb3.0传输带宽测试
----
`FPGA` `RTL` `P0`

**Description**

1. drd配置成支持usb3.0协议模式，测试传输带宽

**Expectation**

1. 打印Test DRD Band Width Test Pass.

**FPGA&RTL Params**

```c
drd -p 0 -q 1 -v 3 -b #mode:3.0, host:0, dev:1, bandwidth
```
# QSPI 相关测试例


## QSPI 1线 DIRECT模式读写
* (颗粒型号: GD5F1GM7RE)
----
`FPGA` `P0`

**Description**

1. 配置qspi 1线 master direct模式
2. qspi 先写32bytes数据到flash(GD5F1G)，再从flash读32bytes字节

**Expectation**

1. 比较读写的值是否一致
2. 打印Test QSPI 1-wire DIRECT Pass
   
**FPGA&RTL Params**

```c
xspi -p 1 -l 1 -m 0 --nand
```

## QSPI 1线 STIG模式读写
* (颗粒型号: GD5F1GM7RE)
----
`FPGA` `P0`

**Description**

1. 配置qspi 1线 master stig模式
2. qspi 先写32bytes数据到flash(GD5F1G)，再从flash读32bytes字节

**Expectation**

1. 比较读写的值是否一致
2. 打印Test QSPI 1-wire STIG Pass

**FPGA&RTL Params**

```c
xspi -p 1 -l 1 -m 1 --nand
```

## QSPI 1线 PIO模式读写
* (颗粒型号: GD5F1GM7RE)
----
`FPGA` `P0`

**Description**

1. 配置qspi 1线 master PIO模式
2. qspi 先写32bytes数据到flash(GD5F1G)，再从flash读32bytes字节

**Expectation**

1. 比较读写的值是否一致
2. 打印Test QSPI 1-wire PIO Pass

**FPGA&RTL Params**

```c
xspi -p 1 -l 1 -m 2 --nand
```

## QSPI 1线 CDMA模式读写
* (颗粒型号: GD5F1GM7RE)
----
`FPGA` `P0`

**Description**

1. 配置qspi 1线 master CDMA模式
2. qspi 先写32bytes数据到flash(GD5F1G)，再从flash读32bytes字节

**Expectation**

1. 比较读写的值是否一致
2. 打印Test QSPI 1-wire CDMA Pass

**FPGA&RTL Params**

```c
xspi -p 1 -l 1 -m 3 --nand
```



## QSPI 2线 DIRECT模式读写
* (颗粒型号: GD5F1GM7RE)
----
`FPGA` `P0`

**Description**

1. 配置qspi 2线 master direct模式
2. qspi 先写32bytes数据到flash(GD5F1G)，再从flash读32bytes字节

**Expectation**

1. 比较读写的值是否一致
2. 打印Test QSPI 2-wire DIRECT Pass
   
**FPGA&RTL Params**

```c
xspi -p 1 -l 2 -m 0 --nand
```

## QSPI 2线 STIG模式读写
* (颗粒型号: GD5F1GM7RE)
----
`FPGA` `P0`

**Description**

1. 配置qspi 2线 master stig模式
2. qspi 先写32bytes数据到flash(GD5F1G)，再从flash读32bytes字节

**Expectation**

1. 比较读写的值是否一致
2. 打印Test QSPI 2-wire STIG Pass

**FPGA&RTL Params**

```c
xspi -p 1 -l 2 -m 1 --nand
```

## QSPI 2线 PIO模式读写
* (颗粒型号: GD5F1GM7RE)
----
`FPGA` `P0`

**Description**

1. 配置qspi 2线 master PIO模式
2. qspi 先写32bytes数据到flash(GD5F1G)，再从flash读32bytes字节

**Expectation**

1. 比较读写的值是否一致
2. 打印Test QSPI 2-wire PIO Pass

**FPGA&RTL Params**

```c
xspi -p 1 -l 2 -m 2 --nand
```

## QSPI 2线 CDMA模式读写
* (颗粒型号: GD5F1GM7RE)
----
`FPGA` `P0`

**Description**

1. 配置qspi 2线 master CDMA模式
2. qspi 先写32bytes数据到flash(GD5F1G)，再从flash读32bytes字节

**Expectation**

1. 比较读写的值是否一致
2. 打印Test QSPI 2-wire CDMA Pass

**FPGA&RTL Params**

```c
xspi -p 1 -l 2 -m 3 --nand
```



## QSPI 4线 DIRECT模式读写
* (颗粒型号: GD5F1GM7RE)
----
`FPGA` `P0`

**Description**

1. 配置qspi 4线 master direct模式
2. qspi 先写32bytes数据到flash(GD5F1G)，再从flash读32bytes字节

**Expectation**

1. 比较读写的值是否一致
2. 打印Test QSPI 4-wire DIRECT Pass
   
**FPGA&RTL Params**

```c
xspi -p 1 -l 4 -m 0 --nand
```

## QSPI 4线 STIG模式读写
* (颗粒型号: GD5F1GM7RE)
----
`FPGA` `P0`

**Description**

1. 配置qspi 4线 master stig模式
2. qspi 先写32bytes数据到flash(GD5F1G)，再从flash读32bytes字节

**Expectation**

1. 比较读写的值是否一致
2. 打印Test QSPI 4-wire STIG Pass

**FPGA&RTL Params**

```c
xspi -p 1 -l 4 -m 1 --nand
```

## QSPI 4线 PIO模式读写
* (颗粒型号: GD5F1GM7RE)
----
`FPGA` `P0`

**Description**

1. 配置qspi 4线 master PIO模式
2. qspi 先写32bytes数据到flash(GD5F1G)，再从flash读32bytes字节

**Expectation**

1. 比较读写的值是否一致
2. 打印Test QSPI 4-wire PIO Pass

**FPGA&RTL Params**

```c
xspi -p 1 -l 4 -m 2 --nand
```

## QSPI 4线 CDMA模式读写
* (颗粒型号: GD5F1GM7RE)
----
`FPGA` `P0`

**Description**

1. 配置qspi 4线 master CDMA模式
2. qspi 先写32bytes数据到flash(GD5F1G)，再从flash读32bytes字节

**Expectation**

1. 比较读写的值是否一致
2. 打印Test QSPI 4-wire CDMA Pass

**FPGA&RTL Params**

```c
xspi -p 1 -l 4 -m 3 --nand
```


## QSPI 外接1线 spi flash读写

* (颗粒型号: GD25LB256E)
----
`FPGA` `P0`

**Description**

1. 配置qspi master DMA模式，并按照外接的1线spi flash配置寄存器
2. qspi 先写32bytes数据到flash，然后再从flash中读32bytes

**Expectation**

1. 写入和读取flash的数据一致
2. 打印Test QSPI Connect With 1-wire SPI Flash Pass

**FPGA&RTL Params**

```c
xspi -p 1 -l 1 -m 1 --nor
```

## QSPI 外接2线 spi flash读写

* (颗粒型号: GD5F1GM7RE)

----
`FPGA` `P0`

**Description**

1. 配置qspi master DMA模式，并按照外接的2线spi flash配置寄存器
2. qspi 先写32bytes数据到flash，然后再从flash中读32bytes

**Expectation**

1. 写入和读取flash的数据一致
2. 打印Test QSPI Connect With 2-wire SPI Flash Pass

**FPGA&RTL Params**

```c
xspi -p 1 -l 2 -m 1 --nor
```

## QSPI 外接4线 spi flash读写

* (颗粒型号: GD25LB256E)

----
`FPGA` `P0`

**Description**

1. 配置qspi master DMA模式，并按照外接的4线spi flash配置寄存器
2. qspi 先写32bytes数据到flash，然后再从flash中读32bytes

**Expectation**

1. 写入和读取flash的数据一致
2. 打印Test QSPI Connect With 4-wire SPI Flash Pass

**FPGA&RTL Params**

```c
xspi -p 1 -l 4 -m 1 --nor
```

## QSPI DDR(DTR)读写
* (颗粒型号: GD25LB256E)
----
`FPGA` `P0`

**Description**

1. 配置qspi master DMA模式，并按照外接的1线spi flash配置寄存器
2. qspi 先写32bytes数据到flash，然后再从flash中读32bytes

**Expectation**

1. 写入和读取的数据一致
2. 打印Test QSPI DTR Pass

**FPGA&RTL Params**

```c
xspi -p 1 -l 1 -m 1 -d --nor
```

## QSPI XIP模式
* (颗粒型号: GD25LB256E)
----
`FPGA` `P0`

**Description**

1. 配置qspi master DMA模式，并按照外接的1线spi flash配置寄存器
2. qspi 先写32bytes数据到flash，然后再从flash中读32bytes

**Expectation**

1. 写入和读取的数据一致
2. 打印Test QSPI XIP Pass

**FPGA&RTL Params**

```c
xspi -p 1 -l 1 -m 1 --xip --nor
```


## QSPI 全自动模式device discovery功能
* (颗粒型号: GD25LB256E)
----
`FPGA` `P0`

**Description**

device discovery 分三种模式

* 非预设SDFP设备发现，为下面第一点进行的测试
* 预设SDFP设备发现，为下面第二点进行的测试
* 不开启device discovery，该用例不用测试，后续的其他测试都是该情况
   
1. qspi配置成全自动模式device discovery，外界未知几线的spi flash，启动


**Expectation**

1. 检测到discovery完成标志
2. 打印Test QSPI SDFP FULL AutoMated Mode DD Pass

**FPGA&RTL Params**

```c
xspi -p 1 -l 1 -f 1
```

## QSPI 预设SDFP自动模式device discovery功能
* (颗粒型号: GD25LB256E)
----
`FPGA` `P0`

**Description**
   
1. 设置spi flash线数
2. qspi配置成预设SDFP模式device discovery

**Expectation**

1. 检测到discovery完成标志
2. 打印Test QSPI SDFP Pre-configured AutoMated Mode DD Pass

**FPGA&RTL Params**

```c
xspi -p 1 -l 1 -f 2
xspi -p 1 -l 2 -f 2
xspi -p 1 -l 4 -f 2
```

## QSPI boot功能
* (颗粒型号: GD25LB256E)
----
`FPGA` `P0`

**Description**

1. 将镜像转成的image.c文件中的bms_image_arr数组加上头部后写入到flash中
2. qspi assert reset
3. boot_en位写1
4. release reset

**Expectation**

1. 能正常出现boot完成标志，并且镜像被自动拷贝到指定地址
2. 指定地址的镜像和之前写入flash的镜像所有字节比对一致
2. 打印Test QSPI Boot Pass

**FPGA&RTL Params**

```c
xspi -p 1 -l 1 -m 1 -b --nor 
```

## QSPI CPU访问功能
* (颗粒型号: GD25LB256E)
----
`FPGA` `P0`

**Description**

1. 配置qspi为1线DIRECT模式
2. 使用CPU写256字节到flash，再从flash读取256字节

**Expectation**

1. 写入读取flash的所有字节比对一致
2. 打印Test CPU Access Pass

**FPGA&RTL Params**

```c
xspi -p 1 -l 1 -m 0 -c --nor 
```

## QSPI 1线 DIRECT模式读写
* (颗粒型号: MX25U6432F)
----
`RTL` `P0`

**Description**

1. 配置qspi 1线 master direct模式
2. qspi 先写32bytes数据到flash，再从flash读32bytes字节

**Expectation**

1. 比较读写的值是否一致
2. 打印Test QSPI 1-wire DIRECT Pass
   
**FPGA&RTL Params**

```c
xspi -p 1 -l 1 -m 0 --nor # 使用MX25U6432FM2I02
```

## QSPI 1线 STIG模式读写
* (颗粒型号: MX25U6432F)
----
`RTL` `P0`

**Description**

1. 配置qspi 1线 master stig模式
2. qspi 先写32bytes数据到flash，再从flash读32bytes字节

**Expectation**

1. 比较读写的值是否一致
2. 打印Test QSPI 1-wire STIG Pass

**FPGA&RTL Params**

```c
xspi -p 1 -l 1 -m 1 --nor # 使用MX25U6432FM2I02
```

## QSPI 1线 PIO模式读写
* (颗粒型号: MX25U6432F)
----
`RTL` `P0`

**Description**

1. 配置qspi 1线 master PIO模式
2. qspi 先写32bytes数据到flash，再从flash读32bytes字节

**Expectation**

1. 比较读写的值是否一致
2. 打印Test QSPI 1-wire PIO Pass

**FPGA&RTL Params**

```c
xspi -p 1 -l 1 -m 2 --nor # 使用MX25U6432FM2I02
```

## QSPI 1线 CDMA模式读写
* (颗粒型号: MX25U6432F)
----
`RTL` `P0`

**Description**

1. 配置qspi 1线 master CDMA模式
2. qspi 先写32bytes数据到flash，再从flash读32bytes字节

**Expectation**

1. 比较读写的值是否一致
2. 打印Test QSPI 1-wire CDMA Pass

**FPGA&RTL Params**

```c
xspi -p 1 -l 1 -m 3 --nor # 使用MX25U6432FM2I02
```



## QSPI 2线 DIRECT模式读写
* (颗粒型号: MX25U6432F)
----
`RTL` `P0`

**Description**

1. 配置qspi 2线 master direct模式
2. qspi 先写32bytes数据到flash，再从flash读32bytes字节

**Expectation**

1. 比较读写的值是否一致
2. 打印Test QSPI 2-wire DIRECT Pass
   
**FPGA&RTL Params**

```c
xspi -p 1 -l 2 -m 0 --nor # 使用MX25U6432FM2I02
```

## QSPI 2线 STIG模式读写
* (颗粒型号: MX25U6432F)
----
`RTL` `P0`

**Description**

1. 配置qspi 2线 master stig模式
2. qspi 先写32bytes数据到flash，再从flash读32bytes字节

**Expectation**

1. 比较读写的值是否一致
2. 打印Test QSPI 2-wire STIG Pass

**FPGA&RTL Params**

```c
xspi -p 1 -l 2 -m 1 --nor # 使用MX25U6432FM2I02
```

## QSPI 2线 PIO模式读写
* (颗粒型号: MX25U6432F)
----
`RTL` `P0`

**Description**

1. 配置qspi 2线 master PIO模式
2. qspi 先写32bytes数据到flash，再从flash读32bytes字节

**Expectation**

1. 比较读写的值是否一致
2. 打印Test QSPI 2-wire PIO Pass

**FPGA&RTL Params**

```c
xspi -p 1 -l 2 -m 2 --nor # 使用MX25U6432FM2I02
```

## QSPI 2线 CDMA模式读写
* (颗粒型号: MX25U6432F)
----
`RTL` `P0`

**Description**

1. 配置qspi 2线 master CDMA模式
2. qspi 先写32bytes数据到flash，再从flash读32bytes字节

**Expectation**

1. 比较读写的值是否一致
2. 打印Test QSPI 2-wire CDMA Pass

**FPGA&RTL Params**

```c
xspi -p 1 -l 2 -m 3 --nor # 使用MX25U6432FM2I02
```



## QSPI 4线 DIRECT模式读写
* (颗粒型号: MX25U6432F)
----
`RTL` `P0`

**Description**

1. 配置qspi 4线 master direct模式
2. qspi 先写32bytes数据到flash，再从flash读32bytes字节

**Expectation**

1. 比较读写的值是否一致
2. 打印Test QSPI 4-wire DIRECT Pass
   
**FPGA&RTL Params**

```c
xspi -p 1 -l 4 -m 0 --nor # 使用MX25U6432FM2I02
```

## QSPI 4线 STIG模式读写
* (颗粒型号: MX25U6432F)
----
`RTL` `P0`

**Description**

1. 配置qspi 4线 master stig模式
2. qspi 先写32bytes数据到flash，再从flash读32bytes字节

**Expectation**

1. 比较读写的值是否一致
2. 打印Test QSPI 4-wire STIG Pass

**FPGA&RTL Params**

```c
xspi -p 1 -l 4 -m 1 --nor # 使用MX25U6432FM2I02
```

## QSPI 4线 PIO模式读写
* (颗粒型号: MX25U6432F)
----
`RTL` `P0`

**Description**

1. 配置qspi 4线 master PIO模式
2. qspi 先写32bytes数据到flash，再从flash读32bytes字节

**Expectation**

1. 比较读写的值是否一致
2. 打印Test QSPI 4-wire PIO Pass

**FPGA&RTL Params**

```c
xspi -p 1 -l 4 -m 2 --nor # 使用MX25U6432FM2I02
```

## QSPI 4线 CDMA模式读写
* (颗粒型号: MX25U6432F)
----
`RTL` `P0`

**Description**

1. 配置qspi 4线 master CDMA模式
2. qspi 先写32bytes数据到flash，再从flash读32bytes字节

**Expectation**

1. 比较读写的值是否一致
2. 打印Test QSPI 4-wire CDMA Pass

**FPGA&RTL Params**

```c
xspi -p 1 -l 4 -m 3 --nor # 使用MX25U6432FM2I02
```

## QSPI DDR(DTR)读写
* (颗粒型号: GD25LB256E)
----
`RTL` `P0`

**Description**

1. 配置qspi master DMA模式，并按照外接的1线spi flash配置寄存器
2. qspi 先写32bytes数据到flash，然后再从flash中读32bytes

**Expectation**

1. 写入和读取的数据一致
2. 打印Test QSPI DTR Pass

**FPGA&RTL Params**

```c
xspi -p 1 -l 1 -m 1 -d --nor # 使用GD25LB256E
```

## QSPI XIP模式
* (颗粒型号: GD25LB256E)
----
`RTL` `P0`

**Description**

1. 配置qspi master DMA模式，并按照外接的1线spi flash配置寄存器
2. qspi 先写32bytes数据到flash，然后再从flash中读32bytes

**Expectation**

1. 写入和读取的数据一致
2. 打印Test QSPI XIP Pass

**FPGA&RTL Params**

```c
xspi -p 1 -l 1 -m 1 --xip --nor # 使用GD25LB256E
```


## QSPI 全自动模式device discovery功能
* (颗粒型号: GD25LB256E)
----
`RTL` `P0`

**Description**

device discovery 分三种模式

* 非预设SDFP设备发现，为下面第一点进行的测试
* 预设SDFP设备发现，为下面第二点进行的测试
* 不开启device discovery，该用例不用测试，后续的其他测试都是该情况
   
1. qspi配置成全自动模式device discovery，外界未知几线的spi flash，启动


**Expectation**

1. 检测到discovery完成标志
2. 打印Test QSPI SDFP FULL AutoMated Mode DD Pass

**FPGA&RTL Params**

```c
xspi -p 1 -l 1 -f 1 # 使用GD25LB256E
```

## QSPI 预设SDFP自动模式device discovery功能
* (颗粒型号: GD25LB256E)
----
`RTL` `P0`

**Description**
   
1. 设置spi flash线数
2. qspi配置成预设SDFP模式device discovery

**Expectation**

1. 检测到discovery完成标志
2. 打印Test QSPI SDFP Pre-configured AutoMated Mode DD Pass

**FPGA&RTL Params**

```c
xspi -p 1 -l 1 -f 2 # 使用GD25LB256E
xspi -p 1 -l 2 -f 2
xspi -p 1 -l 4 -f 2
```

## QSPI boot功能
* (颗粒型号: GD25LB256E)
----
`RTL` `P0`

**Description**

1. 将镜像转成的image.c文件中的bms_image_arr数组加上头部后写入到flash中
2. qspi assert reset
3. boot_en位写1
4. release reset

**Expectation**

1. 能正常出现boot完成标志，并且镜像被自动拷贝到指定地址
2. 指定地址的镜像和之前写入flash的镜像所有字节比对一致
2. 打印Test QSPI Boot Pass

**FPGA&RTL Params**

```c
xspi -p 1 -l 1 -m 1 -b --nor # 使用GD25LB256E
```
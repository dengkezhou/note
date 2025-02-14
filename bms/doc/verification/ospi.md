# OSPI 相关测试例


## OSPI 1线 DIRECT模式读写
* (颗粒型号: GD5F1GM7RE)
----
`FPGA` `P0`

**Description**

1. 配置ospi 1线 master direct模式
2. ospi 先写32bytes数据到flash，再从flash读32bytes字节

**Expectation**

1. 比较读写的值是否一致
2. 打印Test OSPI 1-wire DIRECT Pass
   
**FPGA&RTL Params**

```c
xspi -p 0 -l 1 -m 0 --nand
```

## OSPI 1线 STIG模式读写
* (颗粒型号: GD5F1GM7RE)
----
`FPGA` `P0`

**Description**

1. 配置ospi 1线 master stig模式
2. ospi 先写32bytes数据到flash，再从flash读32bytes字节

**Expectation**

1. 比较读写的值是否一致
2. 打印Test OSPI 1-wire STIG Pass

**FPGA&RTL Params**

```c
xspi -p 0 -l 1 -m 1 --nand
```

## OSPI 1线 PIO模式读写
* (颗粒型号: GD5F1GM7RE)
----
`FPGA` `P0`

**Description**

1. 配置ospi 1线 master PIO模式
2. ospi 先写32bytes数据到flash，再从flash读32bytes字节

**Expectation**

1. 比较读写的值是否一致
2. 打印Test OSPI 1-wire PIO Pass

**FPGA&RTL Params**

```c
xspi -p 0 -l 1 -m 2 --nand
```

## OSPI 1线 CDMA模式读写
* (颗粒型号: GD5F1GM7RE)
----
`FPGA` `P0`

**Description**

1. 配置ospi 1线 master CDMA模式
2. ospi 先写32bytes数据到flash，再从flash读32bytes字节

**Expectation**

1. 比较读写的值是否一致
2. 打印Test OSPI 1-wire CDMA Pass

**FPGA&RTL Params**

```c
xspi -p 0 -l 1 -m 3 --nand
```



## OSPI 2线 DIRECT模式读写
* (颗粒型号: GD5F1GM7RE)
----
`FPGA` `P0`

**Description**

1. 配置ospi 2线 master direct模式
2. ospi 先写32bytes数据到flash，再从flash读32bytes字节

**Expectation**

1. 比较读写的值是否一致
2. 打印Test OSPI 2-wire DIRECT Pass
   
**FPGA&RTL Params**

```c
xspi -p 0 -l 2 -m 0 --nand
```

## OSPI 2线 STIG模式读写
* (颗粒型号: GD5F1GM7RE)
----
`FPGA` `P0`

**Description**

1. 配置ospi 2线 master stig模式
2. ospi 先写32bytes数据到flash，再从flash读32bytes字节

**Expectation**

1. 比较读写的值是否一致
2. 打印Test OSPI 2-wire STIG Pass

**FPGA&RTL Params**

```c
xspi -p 0 -l 2 -m 1 --nand
```

## OSPI 2线 PIO模式读写
* (颗粒型号: GD5F1GM7RE)
----
`FPGA` `P0`

**Description**

1. 配置ospi 2线 master PIO模式
2. ospi 先写32bytes数据到flash，再从flash读32bytes字节

**Expectation**

1. 比较读写的值是否一致
2. 打印Test OSPI 2-wire PIO Pass

**FPGA&RTL Params**

```c
xspi -p 0 -l 2 -m 2 --nand
```

## OSPI 2线 CDMA模式读写
* (颗粒型号: GD5F1GM7RE)
----
`FPGA` `P0`

**Description**

1. 配置ospi 2线 master CDMA模式
2. ospi 先写32bytes数据到flash，再从flash读32bytes字节

**Expectation**

1. 比较读写的值是否一致
2. 打印Test OSPI 2-wire CDMA Pass

**FPGA&RTL Params**

```c
xspi -p 0 -l 2 -m 3 --nand
```



## OSPI 4线 DIRECT模式读写
* (颗粒型号: GD5F1GM7RE)
----
`FPGA` `P0`

**Description**

1. 配置ospi 4线 master direct模式
2. ospi 先写32bytes数据到flash，再从flash读32bytes字节

**Expectation**

1. 比较读写的值是否一致
2. 打印Test OSPI 4-wire DIRECT Pass
   
**FPGA&RTL Params**

```c
xspi -p 0 -l 4 -m 0 --nand
```

## OSPI 4线 STIG模式读写
* (颗粒型号: GD5F1GM7RE)
----
`FPGA` `P0`

**Description**

1. 配置ospi 4线 master stig模式
2. ospi 先写32bytes数据到flash，再从flash读32bytes字节

**Expectation**

1. 比较读写的值是否一致
2. 打印Test OSPI 4-wire STIG Pass

**FPGA&RTL Params**

```c
xspi -p 0 -l 4 -m 1 --nand
```

## OSPI 4线 PIO模式读写
* (颗粒型号: GD5F1GM7RE)
----
`FPGA` `P0`

**Description**

1. 配置ospi 4线 master PIO模式
2. ospi 先写32bytes数据到flash，再从flash读32bytes字节

**Expectation**

1. 比较读写的值是否一致
2. 打印Test OSPI 4-wire PIO Pass

**FPGA&RTL Params**

```c
xspi -p 0 -l 4 -m 2 --nand
```

## OSPI 4线 CDMA模式读写
* (颗粒型号: GD5F1GM7RE)
----
`FPGA` `P0`

**Description**

1. 配置ospi 4线 master CDMA模式
2. ospi 先写32bytes数据到flash，再从flash读32bytes字节

**Expectation**

1. 比较读写的值是否一致
2. 打印Test OSPI 4-wire CDMA Pass

**FPGA&RTL Params**

```c
xspi -p 0 -l 4 -m 3 --nand
```

## xSPI 8线 DIRECT模式读写
* (颗粒型号: GD25LX256E)
----
`FPGA` `P0`

**Description**

1. 配置ospi 8线 master direct模式
2. ospi 先写32bytes数据到flash(OSPI:GD25LX256E)，再读32bytes字节

**Expectation**

1. 比较读写的值是否一致
2. 打印Test xSPI 8-wire DIRECT Pass
   
**FPGA&RTL Params**

```c
xspi -p 0 -l 8 -m 0 --nor
```

## xSPI 8线 STIG模式读写
* (颗粒型号: GD25LX256E)
----
`FPGA` `P0`

**Description**

1. 配置ospi 8线 master stig模式
2. ospi 先写32bytes数据到flash(OSPI:GD25LX256E)，再读32bytes字节

**Expectation**

1. 比较读写的值是否一致
2. 打印Test xSPI 8-wire STIG Pass

**FPGA&RTL Params**

```c
xspi -p 0 -l 8 -m 1 --nor
```

## xSPI 8线 PIO模式读写
* (颗粒型号: GD25LX256E)
----
`FPGA` `P0`

**Description**

1. 配置ospi 8线 master PIO模式
2. ospi 先写32bytes数据到flash(OSPI:GD25LX256E)，再读32bytes字节

**Expectation**

1. 比较读写的值是否一致
2. 打印Test xSPI 8-wire PIO Pass

**FPGA&RTL Params**

```c
xspi -p 0 -l 8 -m 2 --nor
```

## xSPI 8线 CDMA模式读写
* (颗粒型号: GD25LX256E)
----
`FPGA` `P0`

**Description**

1. 配置ospi 8线 master CDMA模式
2. ospi 先写32bytes数据到flash(OSPI:GD25LX256E)，再读32bytes字节

**Expectation**

1. 比较读写的值是否一致
2. 打印Test xSPI 8-wire CDMA Pass

**FPGA&RTL Params**

```c
xspi -p 0 -l 8 -m 3 --nor
```

## OSPI 外接1线 spi flash读写

* (颗粒型号: GD25LB256E)
----
`FPGA` `P0`

**Description**

1. 配置ospi master DMA模式，并按照外接的1线spi flash配置寄存器
2. ospi 先写32bytes数据到flash，然后再从flash中读32bytes

**Expectation**

1. 写入和读取flash的数据一致
2. 打印Test OSPI Connect With 1-wire SPI Flash Pass

**FPGA&RTL Params**

```c
xspi -p 0 -l 1 -m 2 --nor
```

## OSPI 外接2线 spi flash读写

* (颗粒型号: GD5F1GM7RE)

----
`FPGA` `P0`

**Description**

1. 配置ospi master DMA模式，并按照外接的2线spi flash配置寄存器
2. ospi 先写32bytes数据到flash，然后再从flash中读32bytes

**Expectation**

1. 写入和读取flash的数据一致
2. 打印Test OSPI Connect With 2-wire SPI Flash Pass

**FPGA&RTL Params**

```c
xspi -p 0 -l 2 -m 2 --nand
```

## OSPI 外接4线 spi flash读写

* (颗粒型号: GD25LB256E)

----
`FPGA` `P0`

**Description**

1. 配置ospi master DMA模式，并按照外接的4线spi flash配置寄存器
2. ospi 先写32bytes数据到flash，然后再从flash中读32bytes

**Expectation**

1. 写入和读取flash的数据一致
2. 打印Test OSPI Connect With 4-wire SPI Flash Pass

**FPGA&RTL Params**

```c
xspi -p 0 -l 4 -m 2 --nor
```


## OSPI 外接8线 spi flash读写
(颗粒型号: GD25LB256E)
----
`FPGA` `P0`

**Description**

1. 配置ospi master DMA模式，并按照外接的4线spi flash配置寄存器
2. ospi 先写32bytes数据到flash，然后再从flash中读32bytess

**Expectation**

1. 写入和读取flash的数据一致
2. 打印Test xSPI Connect With 8-wire SPI Flash Pass

**FPGA&RTL Params**

```c
xspi -p 0 -l 8 -m 2 --nor
```


## SPI 外接8线 HYPERFLASH读写

* （颗粒型号: S26KS256SDABHI020）

----
`FPGA` `P0`

**Description**

1. 配置ospi master DMA模式，并按照外接的8线hyperflash配置寄存器
2. ospi 先写32bytes数据到hyperflash，然后再从hyperflash中读32bytes

**Expectation**

1. 写入和读取hyperflash的数据一致
2. 打印Test xSPI Connect With 8-wire HYPERFLASH Pass

**FPGA&RTL Params**

```c
xspi -p 0 -l 8 -m 2 --hf
```

## SPI 外接8线 HYPERRAM读写

* （颗粒型号: S270KS1282DABHI020）

----
`FPGA` `P0`

**Description**

1. 配置ospi master DMA模式，并按照外接的8线hyperram配置寄存器
2. ospi 先写32bytes数据到hyperram，然后再从hyperram中读32bytes

**Expectation**

1. 写入和读取hyperram的数据一致
2. 打印Test xSPI Connect With 8-wire HYPERRAM Pass

**FPGA&RTL Params**

```c
xspi -p 0 -l 8 -m 2 --hr
```

## OSPI DDR(DTR)读写
* (颗粒型号: GD25LB256E)
----
`FPGA` `P0`

**Description**

1. 配置ospi master DMA模式，并按照外接的1线spi flash配置寄存器
2. ospi 先写32bytes数据到flash，然后再从flash中读32bytes

**Expectation**

1. 写入和读取的数据一致
2. 打印Test OSPI DTR Pass

**FPGA&RTL Params**

```c
xspi -p 0 -l 1 -m 1 -d --nor
```

## OSPI XIP模式
* (颗粒型号: GD25LB256E)
----
`FPGA` `P0`

**Description**

1. 配置ospi master DMA模式，并按照外接的1线spi flash配置寄存器
2. ospi 先写32bytes数据到flash，然后再从flash中读32bytes

**Expectation**

1. 写入和读取的数据一致
2. 打印Test OSPI XIP Pass

**FPGA&RTL Params**

```c
xspi -p 0 -l 1 -m 1 --xip --nor
```


## OSPI 全自动模式device discovery功能
* (颗粒型号: GD25LB256E)
----
`FPGA` `P0`

**Description**

device discovery 分三种模式

* 非预设SDFP设备发现，为下面第一点进行的测试
* 预设SDFP设备发现，为下面第二点进行的测试
* 不开启device discovery，该用例不用测试，后续的其他测试都是该情况
   
1. ospi配置成全自动模式device discovery，外界未知几线的spi flash，启动


**Expectation**

1. 检测到discovery完成标志
2. 打印Test OSPI SDFP FULL AutoMated Mode DD Pass

**FPGA&RTL Params**

```c
xspi -p 0 -l 1 -f 1
```

## OSPI 预设SDFP自动模式device discovery功能
* (颗粒型号: GD25LB256E)
----
`FPGA` `P0`

**Description**
   
1. 设置spi flash线数
2. ospi配置成预设SDFP模式device discovery

**Expectation**

1. 检测到discovery完成标志
2. 打印Test OSPI SDFP Pre-config AutoMated Mode DD Pass

**FPGA&RTL Params**

```c
xspi -p 0 -l 1 -f 2
xspi -p 0 -l 2 -f 2
xspi -p 0 -l 4 -f 2
xspi -p 0 -l 8 -f 2
```

## OSPI boot功能
* (颗粒型号: GD25LB256E)
----
`FPGA` `P0`

**Description**

1. 将镜像转成的image.c文件中的bms_image_arr数组加上头部后写入到flash中
2. ospi assert reset
3. boot_en位写1
4. release reset

**Expectation**

1. 能正常出现boot完成标志，并且镜像被自动拷贝到指定地址
2. 指定地址的镜像和之前写入flash的镜像所有字节比对一致
2. 打印Test OSPI boot Pass

**FPGA&RTL Params**

```c
xspi -p 0 -l 1 -m 1 -b --nor 
```

## OSPI CPU访问功能
* (颗粒型号: GD25LB256E)
----
`FPGA` `P0`

**Description**

1. 配置ospi为1线DIRECT模式
2. 使用CPU写256字节到flash，再从flash读取256字节

**Expectation**

1. 写入读取flash的所有字节比对一致
2. 打印Test CPU Access Pass

**FPGA&RTL Params**

```c
xspi -p 0 -l 1 -m 0 -c --nor 
```

## OSPI 1线 DIRECT模式读写
----
`RTL` `P0`

**Description**

1. 配置ospi 1线 master direct模式
2. ospi 先写32bytes数据到flash，再从flash读32bytes字节

**Expectation**

1. 比较读写的值是否一致
2. 打印Test OSPI 1-wire DIRECT Pass
   
**FPGA&RTL Params**

```c
xspi -p 0 -l 1 -m 0 --nor # 使用MX25U6432FM2I02
```

## OSPI 1线 STIG模式读写
----
`RTL` `P0`

**Description**

1. 配置ospi 1线 master stig模式
2. ospi 先写32bytes数据到flash，再从flash读32bytes字节

**Expectation**

1. 比较读写的值是否一致
2. 打印Test OSPI 1-wire STIG Pass

**FPGA&RTL Params**

```c
xspi -p 0 -l 1 -m 1 --nor # 使用MX25U6432FM2I02
```

## OSPI 1线 PIO模式读写
----
`RTL` `P0`

**Description**

1. 配置ospi 1线 master PIO模式
2. ospi 先写32bytes数据到flash，再从flash读32bytes字节

**Expectation**

1. 比较读写的值是否一致
2. 打印Test OSPI 1-wire PIO Pass

**FPGA&RTL Params**

```c
xspi -p 0 -l 1 -m 2 --nor # 使用MX25U6432FM2I02
```

## OSPI 1线 CDMA模式读写
----
`RTL` `P0`

**Description**

1. 配置ospi 1线 master CDMA模式
2. ospi 先写32bytes数据到flash，再从flash读32bytes字节

**Expectation**

1. 比较读写的值是否一致
2. 打印Test OSPI 1-wire CDMA Pass

**FPGA&RTL Params**

```c
xspi -p 0 -l 1 -m 3 --nor # 使用MX25U6432FM2I02
```



## OSPI 2线 DIRECT模式读写
----
`RTL` `P0`

**Description**

1. 配置ospi 2线 master direct模式
2. ospi 先写32bytes数据到flash，再从flash读32bytes字节

**Expectation**

1. 比较读写的值是否一致
2. 打印Test OSPI 2-wire DIRECT Pass
   
**FPGA&RTL Params**

```c
xspi -p 0 -l 2 -m 0 --nor # 使用MX25U6432FM2I02
```

## OSPI 2线 STIG模式读写
----
`RTL` `P0`

**Description**

1. 配置ospi 2线 master stig模式
2. ospi 先写32bytes数据到flash，再从flash读32bytes字节

**Expectation**

1. 比较读写的值是否一致
2. 打印Test OSPI 2-wire STIG Pass

**FPGA&RTL Params**

```c
xspi -p 0 -l 2 -m 1 --nor # 使用MX25U6432FM2I02
```

## OSPI 2线 PIO模式读写
----
`RTL` `P0`

**Description**

1. 配置ospi 2线 master PIO模式
2. ospi 先写32bytes数据到flash，再从flash读32bytes字节

**Expectation**

1. 比较读写的值是否一致
2. 打印Test OSPI 2-wire PIO Pass

**FPGA&RTL Params**

```c
xspi -p 0 -l 2 -m 2 --nor # 使用MX25U6432FM2I02
```

## OSPI 2线 CDMA模式读写
----
`RTL` `P0`

**Description**

1. 配置ospi 2线 master CDMA模式
2. ospi 先写32bytes数据到flash，再从flash读32bytes字节

**Expectation**

1. 比较读写的值是否一致
2. 打印Test OSPI 2-wire CDMA Pass

**FPGA&RTL Params**

```c
xspi -p 0 -l 2 -m 3 --nor # 使用MX25U6432FM2I02
```



## OSPI 4线 DIRECT模式读写
----
`RTL` `P0`

**Description**

1. 配置ospi 4线 master direct模式
2. ospi 先写32bytes数据到flash，再从flash读32bytes字节

**Expectation**

1. 比较读写的值是否一致
2. 打印Test OSPI 4-wire DIRECT Pass
   
**FPGA&RTL Params**

```c
xspi -p 0 -l 4 -m 0 --nor # 使用MX25U6432FM2I02
```

## OSPI 4线 STIG模式读写
----
`RTL` `P0`

**Description**

1. 配置ospi 4线 master stig模式
2. ospi 先写32bytes数据到flash，再从flash读32bytes字节

**Expectation**

1. 比较读写的值是否一致
2. 打印Test OSPI 4-wire STIG Pass

**FPGA&RTL Params**

```c
xspi -p 0 -l 4 -m 1 --nor # 使用MX25U6432FM2I02
```

## OSPI 4线 PIO模式读写
----
`RTL` `P0`

**Description**

1. 配置ospi 4线 master PIO模式
2. ospi 先写32bytes数据到flash，再从flash读32bytes字节

**Expectation**

1. 比较读写的值是否一致
2. 打印Test OSPI 4-wire PIO Pass

**FPGA&RTL Params**

```c
xspi -p 0 -l 4 -m 2 --nor # 使用MX25U6432FM2I02
```

## OSPI 4线 CDMA模式读写
----
`RTL` `P0`

**Description**

1. 配置ospi 4线 master CDMA模式
2. ospi 先写32bytes数据到flash，再从flash读32bytes字节

**Expectation**

1. 比较读写的值是否一致
2. 打印Test OSPI 4-wire CDMA Pass

**FPGA&RTL Params**

```c
xspi -p 0 -l 4 -m 3 --nor # 使用MX25U6432FM2I02
```

## xSPI 8线 DIRECT模式读写
----
`RTL` `P0`

**Description**

1. 配置ospi 8线 master direct模式
2. ospi 先写32bytes数据到flash(OSPI:GD25LX256E)，再读32bytes字节

**Expectation**

1. 比较读写的值是否一致
2. 打印Test xSPI 8-wire DIRECT Pass
   
**FPGA&RTL Params**

```c
xspi -p 0 -l 8 -m 0 --nor # 使用GD25LX256E
```

## xSPI 8线 STIG模式读写
----
`RTL` `P0`

**Description**

1. 配置ospi 8线 master stig模式
2. ospi 先写32bytes数据到flash(OSPI:GD25LX256E)，再读32bytes字节

**Expectation**

1. 比较读写的值是否一致
2. 打印Test xSPI 8-wire STIG Pass

**FPGA&RTL Params**

```c
xspi -p 0 -l 8 -m 1 --nor # 使用GD25LX256E
```

## xSPI 8线 PIO模式读写
----
`RTL` `P0`

**Description**

1. 配置ospi 8线 master PIO模式
2. ospi 先写32bytes数据到flash(OSPI:GD25LX256E)，再读32bytes字节

**Expectation**

1. 比较读写的值是否一致
2. 打印Test xSPI 8-wire PIO Pass

**FPGA&RTL Params**

```c
xspi -p 0 -l 8 -m 2 --nor # 使用GD25LX256E
```

## xSPI 8线 CDMA模式读写
----
`RTL` `P0`

**Description**

1. 配置ospi 8线 master CDMA模式
2. ospi 先写32bytes数据到flash(OSPI:GD25LX256E)，再读32bytes字节

**Expectation**

1. 比较读写的值是否一致
2. 打印Test xSPI 8-wire CDMA Pass

**FPGA&RTL Params**

```c
xspi -p 0 -l 8 -m 3 --nor # 使用GD25LX256E
```

## OSPI DDR(DTR)读写
----
`RTL` `P0`

**Description**

1. 配置ospi master DMA模式，并按照外接的1线spi flash配置寄存器
2. ospi 先写32bytes数据到flash，然后再从flash中读32bytes

**Expectation**

1. 写入和读取的数据一致
2. 打印Test OSPI DTR Pass

**FPGA&RTL Params**

```c
xspi -p 0 -l 1 -m 1 -d --nor # 使用GD25LB256E
```

## OSPI XIP模式
----
`RTL` `P0`

**Description**

1. 配置ospi master DMA模式，并按照外接的1线spi flash配置寄存器
2. ospi 先写32bytes数据到flash，然后再从flash中读32bytes

**Expectation**

1. 写入和读取的数据一致
2. 打印Test OSPI XIP Pass

**FPGA&RTL Params**

```c
xspi -p 0 -l 1 -m 1 --xip --nor # 使用GD25LB256E
```


## OSPI 全自动模式device discovery功能
----
`RTL` `P0`

**Description**

device discovery 分三种模式

* 非预设SDFP设备发现，为下面第一点进行的测试
* 预设SDFP设备发现，为下面第二点进行的测试
* 不开启device discovery，该用例不用测试，后续的其他测试都是该情况
   
1. ospi配置成全自动模式device discovery，外界未知几线的spi flash，启动


**Expectation**

1. 检测到discovery完成标志
2. 打印Test OSPI SDFP FULL AutoMated Mode DD Pass

**FPGA&RTL Params**

```c
xspi -p 0 -l 1 -f 1 # 使用GD25LB256E
```

## OSPI 预设SDFP自动模式device discovery功能
----
`RTL` `P0`

**Description**
   
1. 设置spi flash线数
2. ospi配置成预设SDFP模式device discovery

**Expectation**

1. 检测到discovery完成标志
2. 打印Test OSPI SDFP Pre-config AutoMated Mode DD Pass

**FPGA&RTL Params**

```c
xspi -p 0 -l 1 -f 2 # 使用GD25LB256E
xspi -p 0 -l 2 -f 2
xspi -p 0 -l 4 -f 2
xspi -p 0 -l 8 -f 2
```

## OSPI boot功能
----
`RTL` `P0`

**Description**

1. 将镜像转成的image.c文件中的bms_image_arr数组加上头部后写入到flash中
2. ospi assert reset
3. boot_en位写1
4. release reset

**Expectation**

1. 能正常出现boot完成标志，并且镜像被自动拷贝到指定地址
2. 指定地址的镜像和之前写入flash的镜像所有字节比对一致
2. 打印Test OSPI boot Pass

**FPGA&RTL Params**

```c
xspi -p 0 -l 1 -m 1 -b --nor # 使用GD25LB256E
```
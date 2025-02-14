# SYSM 相关测试例

## SYSM PLL和Module clock设置

----
`RTL` `P0`

**Description**

1. 设置5路pll时钟，以及所有的module时钟
2. 并读取当前的时钟，比较读取的值
3. 最后，关闭时钟(除了cpu_pll, ddr_pll, apb, ahb)

**Expectation**

1. RTL查看各路时钟是否与设置及读取的值一致
2. 打印Test SYSM PLL & Module Clock Pass

**FPGA&RTL Params**

```c
sysm --clk-test
```

## SYSM GPIO输入输出功能

----
`FPGA` `RTL` `P0`

**Description**

1. gpio id号为奇数设置成输入，gpio id号为偶数的设置成输出，并将输出设为0(CPU: GPIO0 ~ GPIO142, RTC: GP0 ~ GP5, EGP0 ~ EGP7, SAP: GPIO0 ~ GPIO33)
2. gpio id号为奇数的读取当前IO的值
3. gpio id号为偶数的输出设置为1
4. gpio id号为奇数的读取当前IO的值
5. 反过来gpio id号为奇数设置成输出，并将输出设为0，gpio id号为偶数的设置成输入
6. gpio id号为偶数的读取当前IO的值
7. gpio id号为奇数的输出设置为1
8. gpio id号为偶数的读取当前IO的值

**Expectation**

1. 步骤2和步骤6的值分别都为0，步骤4和步骤8读取的值都为1
2. 打印Test SYSM CPU GPIO Input & OutPut Pass

**FPGA&RTL Params**

```c
sysm --gpio-test CPU 0 142;sysm --gpio-test SAP 0 33;sysm --gpio-test RTC 0 13 # CPU: GPIO0~GPIO142, RTC: GP0~GP5, EGP0~EGP7 SAP: GPIO0~GPIO33
```

## SYSM GPIO中断模式功能

----
`FPGA` `RTL` `P0`

**Description**

1. gpio id号为奇数设置成输入，gpio id号为偶数的设置成输出，并将输出设为0
2. gpio id号为奇数使能中断功能，且设置为上升沿中断
3. gpio id号为偶数的输出设置为1

**Expectation**

1. 产生相应的gpio中断
2. 打印Test SYSM GPIO Interrupt Pass

**FPGA&RTL Params**

```c
sysm --gpioint-test CPU 0 142;sysm --gpioint-test SAP 0 33;sysm --gpioint-test RTC 0 13 # CPU: GPIO0~GPIO142, RTC: GP0~GP5, EGP0~EGP7 SAP: GPIO0~GPIO33
```

## SYSM Module电源管理功能

----
`FPGA` `RTL` `P0`

**Description**

1. 使能所有模块的电源
2. reset所有模块
3. 关闭所有模块电源

**Expectation**

1. RTL查看各路电源管理模块是否正常工作
2. 打印Test SYSM Module Power Manage Pass

**FPGA&RTL Params**

```c
sysm --domain-test
```

## SYSM RTCINFO功能

----
`FPGA` `RTL` `P0`

**Description**

1. CPU GPIO2管脚作为是否复位的标志
2. CPU GPIO2为低电平设置RTCINFO寄存器(32*4bytes)，fpga母板sw2、sw3分别为硬件复位和上电复位
3. 重启系统，SPAD_00为高电平读RTCINFO寄存器

**Expectation**

1. RTCINFO读取的值与设置值一致
2. 打印Test SYSM RTCINFO Pass

**FPGA&RTL Params**

```c
sysm --rtcinfo-test poweron_reset CPU 0 # rtl CPU gpio 0 输出先拉低，再拉高
sysm --rtcinfo-test hardware_reset CPU 1 # rtl CPU gpio 1 输出先拉低，再拉高
```

## SYSM SoftReset功能

----
`FPGA` `RTL` `P0`

**Description**

1. 配置寄存器走正常reset流程

**Expectation**

1. 能正常reset
2. 打印Test SYSM SoftReset Pass

**FPGA&RTL Params**

```c
sysm --softreset-test
```

## SYSM Shutdown功能

----
`FPGA` `RTL` `P0`

**Description**

1. 配置寄存器走正常Shutdown流程

**Expectation**

1. 能正常Shutdown
2. 打印Test SYSM ShutDown Pass

**FPGA&RTL Params**

```c
sysm --softpowerdown-test  # 需要检测关机信号，拉住reset管脚
```

## SYSM C920 Core开关功能

----
`FPGA` `RTL` `P0`

**Description**

1. 开启C920核1 ~ 7
2. 关闭C920核1 ~ 7
3. fpga下需要选中CONFIG_CCI_COHERENCY_EN
4. rtl下e906_rtl_orom_defconfig与c920_rtl_ddr_soc_defconfig需要选中CONFIG_CCI_COHERENCY_EN

**Expectation**

1. 能正常开关机
2. 打印Test SYSM ShutDown Pass

**FPGA&RTL Params**

```c
sysm --powerupcore-test 8;sysm --powerdowncore-test 8 #rtl只测c920
```

## SYSM RTC-Wakeup功能

----
`FPGA` `RTL` `P0`

**Description**

1. 设置RTC 3s后唤醒cpu(rtl 1s)
2. 配置寄存器走正常休眠流程

**Expectation**

1. 1s后唤醒
2. fpga eclipse重新连接并且不加载文件与符号，只设置pc地址，重新运行，打印Test SYSM RTC-ALARM Wakeup Pass

**FPGA&RTL Params**

```c
sysm --suspendresume-test RTC-ALARM #rtl只测c920
```

## SYSM GP0~GP5 low/high唤醒功能

----
`FPGA` `RTL` `P0`

**Description**

1. 配置寄存器走正常休眠流程
2. GP0(GP3, GP5)高电平或低电平触发唤醒

**Expectation**

1. GPn是否按照预定电平唤醒
2. fpga eclipse重新连接并且不加载文件与符号，只设置pc地址，重新运行，打印Test SYSM GPn-Low/High Wakeup Pass

**FPGA&RTL Params**

```c
sysm --suspendresume-test GP0 0   #rtl只测c920，需要检测休眠信号，后续拉低GP0唤醒
sysm --suspendresume-test GP0 1   #rtl只测c920，需要检测休眠信号，后续拉高GP0唤醒
sysm --suspendresume-test GP3 0   #rtl只测c920，需要检测休眠信号，后续拉低GP3唤醒
sysm --suspendresume-test GP3 1   #rtl只测c920，需要检测休眠信号，后续拉高GP3唤醒
sysm --suspendresume-test GP5 0   #rtl只测c920，需要检测休眠信号，后续拉低GP5唤醒
sysm --suspendresume-test GP5 1   #rtl只测c920，需要检测休眠信号，后续拉高GP5唤醒
```

## SYSM EGP0~EGP7 low/high唤醒功能

----
`FPGA` `RTL` `P0`

**Description**

1. 配置寄存器走正常休眠流程
2. EGP0~EGP7高电平或低电平触发唤醒

**Expectation**

1. EGPn是否按照预定电平唤醒
2. fpga eclipse重新连接并且不加载文件与符号，只设置pc地址，重新运行，打印Test SYSM EGPn-Low/High Wakeup Pass

**FPGA&RTL Params**

```c
sysm --suspendresume-test EGP0 0   #rtl只测c920，需要检测休眠信号，后续拉低EGP0唤醒
sysm --suspendresume-test EGP0 1   #rtl只测c920，需要检测休眠信号，后续拉高EGP0唤醒
sysm --suspendresume-test EGP1 0   #rtl只测c920，需要检测休眠信号，后续拉低EGP1唤醒
sysm --suspendresume-test EGP1 1   #rtl只测c920，需要检测休眠信号，后续拉高EGP1唤醒
sysm --suspendresume-test EGP2 0   #rtl只测c920，需要检测休眠信号，后续拉低EGP2唤醒
sysm --suspendresume-test EGP2 1   #rtl只测c920，需要检测休眠信号，后续拉高EGP2唤醒
sysm --suspendresume-test EGP3 0   #rtl只测c920，需要检测休眠信号，后续拉低EGP3唤醒
sysm --suspendresume-test EGP3 1   #rtl只测c920，需要检测休眠信号，后续拉高EGP3唤醒
sysm --suspendresume-test EGP4 0   #rtl只测c920，需要检测休眠信号，后续拉低EGP4唤醒
sysm --suspendresume-test EGP4 1   #rtl只测c920，需要检测休眠信号，后续拉高EGP4唤醒
sysm --suspendresume-test EGP5 0   #rtl只测c920，需要检测休眠信号，后续拉低EGP5唤醒
sysm --suspendresume-test EGP5 1   #rtl只测c920，需要检测休眠信号，后续拉高EGP5唤醒
sysm --suspendresume-test EGP6 0   #rtl只测c920，需要检测休眠信号，后续拉低EGP6唤醒
sysm --suspendresume-test EGP6 1   #rtl只测c920，需要检测休眠信号，后续拉高EGP6唤醒
sysm --suspendresume-test EGP7 0   #rtl只测c920，需要检测休眠信号，后续拉低EGP7唤醒
sysm --suspendresume-test EGP7 1   #rtl只测c920，需要检测休眠信号，后续拉高EGP7唤醒
```

## SYSM 安全模式下访问功能

----
`FPGA` `RTL` `P0`

**Description**

1. C920核在非安全模式下，访问SRAM和E906 Core寄存器正确
2. C920核在安全模式下，无法访问SRAM和E906 Core

**Expectation**

1. 按照步骤1和2描述
2. 打印Test SYSM Security Pass

**FPGA&RTL Params**

```c
sysm --security-test
```

## SYSM HW SPI Norflash(Security)启动

----
`P0`

**Description**

1. 启动pin脚设为1，security mode使能
2. 启动

**Expectation**

1. 能正常从0地址启动ROM，SYS_BM_CFG值为1
2. 打印Test SYSM HW SPI Norflash(Security) Pass

**FPGA&RTL Params**

```c
```

## SYSM HW SPI Norflash启动

----
`P0`

**Description**

1. 启动pin脚设为1，关闭security mode
2. 启动

**Expectation**

1. 在Norflash中镜像读到IRAM，并能正常启动
2. 打印Test SYSM HW SPI Norflash Pass

**FPGA&RTL Params**

```c
```

## SYSM HW SD0(Security)启动

----
`P0`

**Description**

1. 启动pin脚设为2, security mode使能
2. 启动

**Expectation**

1. 能正常从0地址启动ROM，SYS_BM_CFG值为2
2. 打印Test SYSM HW SD0(Security) Pass

**FPGA&RTL Params**

```c
```

## SYSM HW SD0启动

----
`P0`

**Description**

1. 启动pin脚设为2，关闭security mode
2. 启动

**Expectation**

1. 在SD0中镜像读到IRAM，能正常启动
2. 打印Test SYSM HW SD0 Pass

**FPGA&RTL Params**

```c
```

## SYSM BootM值读取

----
`FPGA` `P0`

**Description**

1. SPAD_XOM0 - SPAD_XOM3共4个pin连接bootm 4个pin脚
2. 设置pin值，并读取bootm的值

**Expectation**

1. 读取的值与设置的pin脚值一致
2. 打印Test SYSM Bootm Pass

**FPGA&RTL Params**

```c
sysm --bootm-test #需要把SPAD_XOM0 - SPAD_XOM3共4个管脚连接到bootm0 - bootm3 4个管脚
```

## SYSM BootM值读取(Security)

----
`FPGA` `P0`

**Description**

1. SPAD_XOM0 - SPAD_XOM3共4个pin连接bootm 4个pin脚
2. 设置pin值，并读取bootm的值

**Expectation**

1. 读取的值与设置的pin脚值一致
2. 打印Test SYSM Bootm(Security) Pass

**FPGA&RTL Params**

```c
sysm --bootm-test security #需要把SPAD_XOM0 - SPAD_XOM3共4个管脚连接到bootm0 - bootm3 4个管脚
```

## C920 remap到E906测试

----
`FPGA` `RTL` `P0`

**Description**

1. 将E906编译运行在0地址的soc.bin(asic下，用tools/sysm/remap_e906_soc.bin)放到0x140000000
2. C920将0x140000000映射到0x40000000，然后将0x40000000 remap到0地址
3. 自动运行e906 soc.bin
4. 重新输入测试命令sysm --remap-e906-test
5. asic下只测c920 ddr和交织
6. restore /home/liu/src/frigob/bms/tools/sysm/remap_e906_soc.bin binary 0x140000000
7. elipse设置pc地址为0

**Expectation**

1. e906正常启动
2. 第二次执行命令后打印Test C920 REMAP E906 Pass

**FPGA&RTL Params**

```c 
(SAP) sysm --remap-e906-test (CPU) sysm --remap-e906-test #rtl只测c920，把运行在0地址的e906 soc.bin加载到0x140000000
```

## C920 E906 LPDDR4地址共享测试

----
`FPGA` `RTL` `P0`

**Description**

1. C920 soc.bin运行在ddr，在lpddr4地址0x101000000, 0x141000000分别写入0x11111111, 0x22222222
2. E906 soc.bin运行在ram，按照LPDDR4不同偏移设置，分别在地址0x41000000读出4字节数。对于e906，ddr偏移0x1000000后的地址为uncacheable
3. rtl下e906_rtl_orom_defconfig需要选中CONFIG_TBH_SYSM，去掉CONFIG_LIB_CRYPTO。rtl无需加载额外bin文件，只测c920
4. asic下先跑c920输入命令，之后通过jtag连接e906，再次输入命令
5. asic下只测c920 ddr和交织

**Expectation**

1. E906读出的值分别为0x11111111, 0x22222222
2. 打印Test SYSM ShareDDR Pass

**FPGA&RTL Params**

```c
(SAP) sysm --ddr-share-test 2 (CPU) sysm --ddr-share-test 2 #rtl只测c920
```

## RTCCLk输出功能

----
`FPGA` `RTL` `P0`

**Description**

1. 配置XRTCPWM成FUNC MUX2模式

**Expectation**

1. 测量XRTCPWM看是否能输出32K时钟
2. 打印Test SYSM RTCCLK Pass

**FPGA&RTL Params**

```c
sysm --rtciofunc-test rtcclk
```

## E906 AHB测试

----
`FPGA` `RTL` `P0`

**Description**

1. 把e906运行在ddr的soc.bin(asic下，用tools/sysm/ahb_test_e906_soc.bin)放到0x140000000
2. C920拉低E906 reset
3. 配置IAHB为0x40000000 - 0x80000000 1G空间
4. 配置DAHB为0x4000000 - 0x3ff00000
5. c920 remap 0x140000000 - 0x180000000到0x40000000
4. 配置Reset地址为0x40000000
5. C920放开E906 reset
5. asic下只测c920 ddr和交织
6. restore /home/liu/src/frigob/bms/tools/sysm/ahb_test_e906_soc.bin binary 0x140000000
7. eclipse运行地址为0x40000000

**Expectation**

1. E906能正常运行在0x40000000，可以看到有新log打印出来
2. 重新输入测试命令sysm --ahb-e906-test，打印Test SYSM AHB E906 Pass

**FPGA&RTL Params**

```c 
sysm --ahb-e906-test #rtl只测c920，把运行在ddr的e906 soc.bin放到0x140000000
```

## reserved zone读写测试

----
`FPGA` `P0`

**Description**

1. 将0x80000000 - 0xc0000000设置为cacheable
2. 读写这片区域
3. 修改rom-main.c将0x80000000 - 0xc0000000设置为uncacheable
4. 读写这片区域

**Expectation**

1. 步骤2、4读写后代码运行正常，能正常打印信息

**FPGA&RTL Params**

```c
sysm --rsvd_test
```

## cci多cluster开cache下cacheable区域读写测试

----
`FPGA` `P0`

**Description**

1. 软件在整个过程不进行任何cache操作，fpga端将0x120000000之后的内存读写区域设置为cacheable，编译一个运行在0地址的使能CONFIG_CCI_COHERENCY_EN和ddr的rom.elf来替换bit中的
2. cluster0写4KBytes到ddr某一地址
3. cluster1从此地址读4KBytes判断是否符合预期，并在紧接其后的4KBytes大小写同样的数据
4. cluster0读后4KBytes读数据并判断
5. asic下只测c920 ddr和交织

**Expectation**

1. 步骤3、4读数据与预期一致

**FPGA&RTL Params**

```c
sysm --cci_cache_test
```

## cci多cluster开cache下uncacheable区域读写测试

----
`FPGA` `P0`

**Description**

1. 软件在整个过程不进行任何cache操作，fpga端将0x120000000之后的内存读写区域设置为uncacheable，编译一个运行在0地址的使能CONFIG_CCI_COHERENCY_EN和ddr的rom.elf来替换bit中的
2. cluster0写4KBytes到ddr某一地址
3. cluster1从此地址读4KBytes判断是否符合预期，并在紧接其后的4KBytes大小写同样的数据
4. cluster0读后4KBytes读数据并判断
5. asic下只测c920 ddr和交织

**Expectation**

1. 步骤3、4读数据与预期一致

**FPGA&RTL Params**

```c
sysm --cci_uncache_test
```

## cci多cluster cache flush_range测试

----
`FPGA` `P0`

**Description**

1. fpga端编译一个运行在0地址的使能CONFIG_CCI_COHERENCY_EN和ddr的rom.elf来替换bit中的
2. 首先，cluster0朝某一内存地址写0x1，然后flush，进行初始化。cluster1朝此内存地址写0xaaaaaaaa55555555，cluster0写0x55555555aaaaaaaa
3. cluster0 flush_range，cluster1读此地址
4. cluster1 flush_range，cluster0读此地址
5. asic下只测c920 ddr和交织

**Expectation**

1. 步骤2中cluster1读结果应为0x55555555aaaaaaaa
2. 步骤3中cluster0读结果应为0x55555555aaaaaaaa，不为0xaaaaaaaa55555555

**FPGA&RTL Params**

```c
sysm --cci_flush_test
```

## cci多cluster cache invalid_range测试

----
`FPGA` `P0`

**Description**

1. fpga端编译一个运行在0地址的使能CONFIG_CCI_COHERENCY_EN和ddr的rom.elf来替换bit中的
2. 首先，cluster0朝某一内存地址写0x1，然后flush，进行初始化。cluster1朝此内存地址写0xaaaaaaaa55555555，cluster0写0x55555555aaaaaaaa
3. cluster0 invalid_range，cluster1读此地址
4. cluster1 invalid_range，cluster1读此地址
5. asic下只测c920 ddr和交织

**Expectation**

1. 步骤2中cluster1读结果应为0x1，不为0x55555555aaaaaaaa
2. 步骤3中cluster1读结果应为0x1

**FPGA&RTL Params**

```c
sysm --cci_invalid_test
```

## cci多cluster L1 cache invalid与flush大数据量测试

----
`FPGA` `RTL` `P0`

**Description**

1. core0写随机数据32KB，计算crc并保存到rtcinfo寄存器，flush dcache到内存，core4读数据前先invalid icache和dcache，之后从内存读32KB数据，计算crc并与rtcinfo寄存器中的值比较(fpga端编译一个运行在0地址的使能CONFIG_CCI_COHERENCY_EN和ddr的rom.elf来替换bit中的)
2. 紧接着进行同样的操作，core4写随机数据，core0读数据，之后比较crc
3. 多次进行上述操作
4. rtl下e906_rtl_orom_defconfig与c920_rtl_ddr_soc_defconfig需要选中CONFIG_CCI_COHERENCY_EN
5. asic下只测c920 ddr和交织

**Expectation**

1. 每次crc结果比对无问题

**FPGA&RTL Params**

```c
sysm --cci_l1_test #rtl只测c920
```

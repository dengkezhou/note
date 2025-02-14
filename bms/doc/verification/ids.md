# IDS  相关测试例

## IDS TVIF ITU1120模式输出

----
`FPGA` `RTL` `P0`

**Description**

1. 将ids模块配置成TVIF ITU1120模式输出

**Expectation**

1. 能正常被转成CVBS的格式识别，并能在屏上正常显示图片

**FPGA&RTL Params**

```c
cvbs -c 1 -m 0 -b 1 #RES:1280*720
```

## IDS TVIF ITU656模式输出

----
`FPGA` `RTL` `P0`

**Description**

1. 将ids模块配置成TVIF ITU656模式输出

**Expectation**

1. 能正常被转成CVBS的格式识别，并能在屏上正常显示图片

**FPGA&RTL Params**

```c
cvbs -c 1 -m 0 -b 0 #RES:1280*720
```

## IDS TVIF ITU601模式输出

----
`FPGA` `RTL` `P0`

**Description**

1. 将ids模块配置成TVIF ITU601模式输出

**Expectation**

1. 能正常被转成CVBS的格式识别，并能在屏上正常显示图片

**FPGA&RTL Params**

```c
cvbs -c 1 -m 1 -b 0 #RES:1280*720
```

## IDS LCD RGB显示输出

----
`FPGA` `RTL` `P0`

**Description**

1. 将ids模块配置成RGB888输出

**Expectation**

1. 能正常在屏上显示图片

**FPGA&RTL Params**

```c
lcd -c 1 #RGB888测试 RES:1024*600

```

## IDS RGB输出顺序

----
`FPGA` `RTL` `P0`

**Description**

1. 将ids模块配置成RGB888
2. RGB输出顺序改为RGB，RBG，BGR，BRG，GBR，GRB6种顺序

**Expectation**

1. 能正常在屏上显示图片

**FPGA&RTL Params**

```c
lcd -c 2 #RGB 6种ORDER测试 RES:1024*600
```

## IDS OSD colorkey功能

----
`FPGA` `RTL` `P0`

**Description**

1. 将ids模块配置成RGB888
2. 使能colorkey功能(blend mode(disable or blending using alpha0 and alpha1) and color key direction)

**Expectation**

1. 能在屏上正常显示图片

**FPGA&RTL Params**

```c
osd -c 4  #RES:80*45
```

## IDS OSD mapcolor功能

----
`FPGA` `RTL` `P0`

**Description**

1. 将ids模块配置成RGB888
2. 使mapcolor功能

**Expectation**

1. 能在屏上正常显示图片

**FPGA&RTL Params**

```c
osd -w 0 -c 5 #RES:80*45
```

## IDS OSD prescaler功能

----
`FPGA` `RTL` `P0`

**Description**

1. 将ids模块配置成RGB888
2. 输入1024*600的图片，scaler成512*300的图片

**Expectation**

1. 能在屏上正常显示图片

**FPGA&RTL Params**

```c
osd -w 0 -c 9 #RES:512*300
```

## IDS OSD afterscaler功能

----
`FPGA` `RTL` `P0`

**Description**

1. 将ids模块配置成RGB888
2. 输入1024*600的图片，scaler成512*300的图片

**Expectation**

1. 能在屏上正常显示图片

**FPGA&RTL Params**

```c
osd -c 10 #RES:512*300
```


## IDS OSD bpp模式

----
`FPGA` `RTL` `P0`

**Description**

1. 将ids模块配置成RGB888模式输出
2. windows(0 or 1)配置成不同的BPP模式(8BPP(A1R2G3B2), 16BPP(R5G6B5), 16BPP(A1R5G5B5), 16BPP(IR5G5B5),
	 unpacked 18BPP(R6G6B6), unpacked 18BPP(A1R6G6B5), unpacked 19BPP(A1R6G6B6), unpacked 24BPP(R8G8B8), unpacked 24BPP(A1R8G8B7),
	 unpacked 25BPP(A1R8G8B8), unpacked 28BPP(A4R8G8B8), unpacked 16BPP(A4R4G4B4), unpacked 32BPP(A8R8G8B8), YUV420,
	 unpacked 32BPP(R8G8B8A8), unpacked 16BPP(R5G5B5A1), unpacked 16BPP(R5G5B5I1),)

**Expectation**

1. 能在屏上正常显示图片

**FPGA&RTL Params**

```c
osd -c 2 -w 0 -f 4  #RES:80*45
osd -c 2 -w 0 -f 5
osd -c 2 -w 0 -f 6
osd -c 2 -w 0 -f 7
osd -c 2 -w 0 -f 8
osd -c 2 -w 0 -f 9
osd -c 2 -w 0 -f 10
osd -c 2 -w 0 -f 11
osd -c 2 -w 0 -f 12
osd -c 2 -w 0 -f 13
osd -c 2 -w 0 -f 14
osd -c 2 -w 0 -f 15
osd -c 2 -w 0 -f 16

osd -c 2 -w 0 -f 17
osd -c 2 -w 0 -f 18
osd -c 2 -w 0 -f 19
osd -c 2 -w 0 -f 20

osd -c 2 -w 1 -f 4
osd -c 2 -w 1 -f 5
osd -c 2 -w 1 -f 6
osd -c 2 -w 1 -f 7
osd -c 2 -w 1 -f 8
osd -c 2 -w 1 -f 9
osd -c 2 -w 1 -f 10
osd -c 2 -w 1 -f 11
osd -c 2 -w 1 -f 12
osd -c 2 -w 1 -f 13
osd -c 2 -w 1 -f 14
osd -c 2 -w 1 -f 15
osd -c 2 -w 1 -f 16

osd -c 2 -w 1 -f 17
osd -c 2 -w 1 -f 18
osd -c 2 -w 1 -f 19
osd -c 2 -w 1 -f 20

```


## IDS OSD buffauto功能

----
`FPGA`  `P0`

**Description**

1. 将ids模块配置成RGB888
2. 4路图片输入，人工切换buff

**Expectation**

1. 能在屏上正常显示图片

**FPGA&RTL Params**

```c
osd -w 0 -c 11
```

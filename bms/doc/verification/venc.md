# VENC 相关测试例

## VENC  RGB转YUV测试

----
`FPGA` `RTL` `P0`

**Description**
1. 输入一段RGB数据
2. 使用VENC模块将RGB转换为YUV数据

**Expectation**
1. 查看VENC编码后的数据与GOLDEN数据是否一致
2. 打印Test VENC conver RGB to YUV  Pass.

**FPGA&RTL Params**

```c
venc --conv1
```

## VENC  YUV422转YUV420测试

----
`FPGA` `RTL` `P0`

**Description**
1. 输入一段YUV422数据
2. 使用VENC模块将YUV422数据转换为YUV420

**Expectation**
1. 查看VENC编码后的数据与GOLDEN数据是否一致
2. 打印Test VENC conver 422 to 420 Pass.

**FPGA&RTL Params**

```c
venc --conv2
```

## VENC  H264分辨率测试

----
`FPGA` `RTL` `P0`

**Description**
1. 输入一段YUV(144X96 ~ 4080x4080)数据（1080P？）
2. 使用VENC模块将YUV数据编码为H264

**Expectation**
1. 查看VENC编码后的数据与GOLDEN数据是否一致
2. 打印Test VENC resolution Pass.

**FPGA&RTL Params**

```c
venc --resol
```

## VENC  性能测试

----
`RTL` `P0`

**Description**
1. 输入一段1080P的YUV/RGB的数据，使用VENC进行编码成h264/jpeg

**Expectation**
1. h264的性能达到60帧/s
2. jpeg的性能达到800帧/s

**FPGA&RTL Params**

```c
venc --perf --vedio
venc --perf --jpeg
```

## VENC  localcase测试

----

`FPGA` `RTL` `P0`

**Description**

1. 将输入数据和输出golden数据都加载到ddr中，
2. 运行localcase进行编码,
3. 将输出数据与golden数据进行对比.

**Expectation**

1. 打印venc localcase test  pass.

**FPGA&RTL Params**

```c
venc 1152
venc 1155
venc 1200
venc 1522
venc 1526
venc 1740
venc 1741
venc 1751
venc 1757
venc 1763
venc 1768
venc 1773
venc 1786
venc 1795
venc 1811
venc 1905
venc 1912
venc 1913
venc 1960
venc 1961
venc 1979
venc 2007
venc 2042
venc 2200
venc 1525
venc 1975
venc 1976
venc 1152 1
venc 1155 1
venc 1200 1
venc 1522 1
venc 1526 1
venc 1740 1
venc 1741 1
venc 1751 1
venc 1757 1
venc 1763 1
venc 1768 1
venc 1773 1
venc 1786 1
venc 1795 1
venc 1811 1
venc 1905 1
venc 1912 1
venc 1913 1
venc 1960 1
venc 1961 1
venc 1979 1
venc 2007 1
venc 2042 1
venc 2200 1
venc 1525 1
venc 1975 1
venc 1976 1
```

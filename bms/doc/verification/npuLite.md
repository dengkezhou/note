# NPU Lite相关测试例

## NPU Local Case nn_convolution_int8测试

----
`FPGA` `RTL` `P0`

**Description**
1. 输入数据为int8格式
2. 在nncore进行卷积操作
3. 对应地址会存储计算结果


**Expectation**
1. 查看NPU处理后的数据与GOLDEN数据是否一致
2. 打印Test nn_convolution_int8 Pass.

**FPGA&RTL Params**
```c
npu -c8 
```

## NPU Local Case nn_convolution_int16测试

----
`FPGA` `RTL` `P0`

**Description**
1. 输入数据为int16格式
2. 在nncore进行卷积操作
3. 对应地址会存储计算结果


**Expectation**
1. 查看NPU处理后的数据与GOLDEN数据是否一致
2. 打印Test nn_convolution_int16 Pass.

**FPGA&RTL Params**

```c
npu -c16
```

## NPU Local Case nn_ddr_read测试

----
`FPGA` `RTL` `P0`

**Description**
1. nncore模块从外部ddr多次读入数据
2. 进行计算操作
2. 计算结果写入到ddr地址


**Expectation**
1. 查看NPU处理后的数据与GOLDEN数据是否一致
2. 打印Test nn_ddr_read Pass.

**FPGA&RTL Params**

```c
npu -ndr
```
## NPU Local Case nn_ddr_write测试

----
`FPGA` `RTL` `P0`

**Description**
1. nncore模块从外部ddr拿数据
2. 进行计算操作
1. 计算结果多次写入ddr


**Expectation**
1. 查看NPU处理后的数据与GOLDEN数据是否一致
2. 打印Test nn_ddr_write Pass.

**FPGA&RTL Params**

```c
npu -ndw
```
## NPU Local Case nn_kernel_1*1测试

----
`FPGA` `RTL` `P0`

**Description**
1. 卷积核大小为1*1
2. nncore中进行卷积计算

**Expectation**
1. 查看NPU处理后的数据与GOLDEN数据是否一致
2. 打印Test nn_kernel_1*1 Pass.

**FPGA&RTL Params**

```c
npu -k1
```
## NPU Local Case nn_kernel_3*3测试

----
`FPGA` `RTL` `P0`

**Description**
1. 卷积核大小为3*3
2. nncore中进行卷积计算

**Expectation**
1. 查看NPU处理后的数据与GOLDEN数据是否一致
2. 打印Test nn_kernel_3*3 Pass.

**FPGA&RTL Params**

```c
npu -k3
```

## NPU Local Case nn_max_ot测试

----
`FPGA` `RTL` `P0`

**Description**
1. kernel size 3*3
2. 对fp张量数据进行最大池化操作
3. nncore中进行操作


**Expectation**
1. 查看NPU处理后的数据与GOLDEN数据是否一致
2. 打印Test nn_max_ot Pass.

**FPGA&RTL Params**

```c
npu -mt
```

## NPU Local Case nn_tensoradd测试

----
`FPGA` `RTL` `P0`

**Description**
1. 在nncore对输入数据相加进行操作
2. 结果存储在相应地址


**Expectation**
1. 查看NPU处理后的数据与GOLDEN数据是否一致
2. 打印Test nn_tensoradd Pass.

**FPGA&RTL Params**

```c
npu -ntd
```

## NPU Local Case nn_transpose测试

----
`FPGA` `RTL` `P0`

**Description**
1. 对数据矩阵进行转置操作，在nncore中进行
2. 对应结果存储在相应的地址


**Expectation**
1. 查看NPU处理后的数据与GOLDEN数据是否一致
2. 打印Test nn_transpose Pass.

**FPGA&RTL Params**

```c
npu -ntp
```

## NPU Local Case nn_perchquatization测试

----
`FPGA` `RTL` `P0`

**Description**
1. 将浮点数表示转换为低精度的整数
2. 计算结果放ddr

**Expectation**
1. 查看NPU处理后的数据与GOLDEN数据是否一致
2. 打印Test nn_perchquatization Pass.

**FPGA&RTL Params**

```c
npu -pq
```

## NPU Local Case nn_mmu_32bit测试

----
`FPGA` `RTL` `P0`

**Description**
1. mmu地址映射
2. nncore访问虚拟地址数据操作

**Expectation**
1. 查看NPU处理后的数据与GOLDEN数据是否一致
2. 打印Test nn_mmu_32bit Pass.

**FPGA&RTL Params**

```c
npu -m32
```

## NPU Local Case ddr_bw_test_read_only测试

----
`FPGA` `RTL` `P0`

**Description**
1. 每个循环有15条存储指令，循环计数为100，只进行读操作
2. 内存访问模式是否良好，并且该测试受内存带宽限制。


**Expectation**
1. 查看NPU处理后的数据与GOLDEN数据是否一致
2. 打印Test ddr_bw_read_only Pass.

**FPGA&RTL Params**

```c
npu -br
```
## NPU Local Case ddr_bw_test_read_write测试

----
`FPGA` `RTL` `P0`

**Description**
1. 每个循环存储15条交叉指令，循环记数为100.
2. 该测试适用于影响内存子系统中读/写的瓶颈，包括但不限于内存访问模式是否良好，并且该测试受内存带宽限制。


**Expectation**
1. 查看NPU处理后的数据与GOLDEN数据是否一致
2. 打印Test ddr_bw_read_write Pass.

**FPGA&RTL Params**

```c
npu -brw
```
## NPU Local Case ddr_bw_test_write_only测试

----
`FPGA` `RTL` `P0`

**Description**
1. 每个循环有15条存储指令，循环计数为100，此测试只生成写入流量。
2. 包括但不限于内存访问模式是否良好，并且该测试受内存带宽限制。


**Expectation**
1. 查看NPU处理后的数据与GOLDEN数据是否一致
2. 打印Test 运行ddr_bw_write_only Pass.

**FPGA&RTL Params**

```c
npu -bw
```
## NPU Local Case image_blend_mmu测试

----
`FPGA` `RTL` `P0`

**Description**
1. 写寄存器使能mmu
1. 进行mmu地址映射后的opencl测试


**Expectation**
1. 查看NPU处理后的数据与GOLDEN数据是否一致
2. 打印Test image_blend_mmu Pass.

**FPGA&RTL Params**

```c
npu -ibm
```
## NPU Local Case image_blend_12288dw测试

----
`FPGA` `RTL` `P0`

**Description**
1. openCL测试，对两张输入图片数据进行求均值操作
2. 执行单元在ppu


**Expectation**
1. 查看NPU处理后的数据与GOLDEN数据是否一致
2. 打印Test image_blend_12288dw Pass.

**FPGA&RTL Params**

```c
npu -ibw
```

## NPU Local Case image_filter测试

----
`FPGA` `RTL` `P0`

**Description**
1. 输入图片64*64做filter操作
2. 每帧为32位数据


**Expectation**
1. 查看NPU处理后的数据与GOLDEN数据是否一致
2. 打印Test image_filter Pass.

**FPGA&RTL Params**

```c
npu -ifi
```


## NPU Local Case mask_image测试

----
`FPGA` `RTL` `P0`

**Description**
1. 输入图片640*480做filter操作
2. ppu计算完结果存入某个地址


**Expectation**
1. 查看NPU处理后的数据与GOLDEN数据是否一致
2. 打印Test mask_image Pass.

**FPGA&RTL Params**

```c
npu -mi
```

## NPU Local Case shader_copy_conn测试

----
`FPGA` `RTL` `P0`

**Description**
1. 拷贝外部ddr数据到vipsram
2. 再从vipsram读取数据到外部

**Expectation**
1. 查看NPU处理后的数据与GOLDEN数据是否一致
2. 打印Test shader_copy Pass.

**FPGA&RTL Params**

```c
npu -s1
```

## NPU Local Case shader_copy_ram2hit测试

----
`FPGA` `RTL` `P0`

**Description**
1. 拷贝外部ddr数据到vipsram
2. 再从vipsram读取数据到外部
3. 拷贝的数据量大小与shader_copy_conn测试不同


**Expectation**
1. 查看NPU处理后的数据与GOLDEN数据是否一致
2. 打印Test shader_copy_ram2hit Pass.

**FPGA&RTL Params**
```c
npu -s2
```


## NPU Local Case localstorageaccess测试

----
`FPGA` `RTL` `P0`

**Description**
1. Universal Storage cache 操作，读写功能测试


**Expectation**
1. 查看NPU处理后的数据与GOLDEN数据是否一致
2. 打印Test localstorageaccess new Pass.

**FPGA&RTL Params**
```c
npu -ls1
```


## NPU Local Case localstorageaccess_new测试

----
`FPGA` `RTL` `P0`

**Description**
1. Universal Storage cache 操作，多次读写功能测试


**Expectation**
1. 查看NPU处理后的数据与GOLDEN数据是否一致
2. 打印Test localstorageaccess new Pass.

**FPGA&RTL Params**
```c
npu -ls2
```


## NPU Local Case localstorageaccess_4core测试

----
`FPGA` `RTL` `P0`

**Description**
1. Universal Storage cache 操作，多次进行读写


**Expectation**
1. 查看NPU处理后的数据与GOLDEN数据是否一致
2. 打印Test localstorageaccess_4core Pass.

**FPGA&RTL Params**
```c
npu -ls4
```

## NPU Local Case mmu_extend4gaddr测试

----
`FPGA` `RTL` `P0`

**Description**
1. 利用cmd配置mmu
2. 写寄存器使能mmu
3. 读写该地址数据


**Expectation**
1. 查看NPU处理后的数据与GOLDEN数据是否一致
2. 打印Test mmu_extend4gaddr Pass.

**FPGA&RTL Params**

```c
npu -me
```

## NPU 神经网络模型测试

----
`FPGA` `RTL` `P0`

**Description**
1. 通过NBG（network binary file）文件来载入网络模型及权重文件
2. 网络层次切分，包含卷积，归一化等操作，在nn模块或ppu模块进行计算
3. 数据图像输入，cpu拿取指令进行计算，较为复杂的计算在npu模块中进行


**Expectation**
1. 对比inference后的结果与golden data进行对比。
2. 打印Tset NPU Network Pass.

**FPGA&RTL Params**

```c
npu -network
```

## yolov5 神经网络模型测试

----
`RTL` `P0`

**Description**
1、性能测试,仅运行在RTL环境
2、yolov5是一种目标检测算法


**Expectation**
1. 对比inference后的结果与golden data进行对比。
2. 打印Tset NPU yolov5 Pass.

**FPGA&RTL Params**

```c
npu -yolo
```

## PPU absdiff测试

----
`RTL` `P0`

**Description**
1、计算两张图的绝对值
2、利用NPU模块的ppu计算


**Expectation**
1. 对比计算后的结果与golden data进行对比。
2. 打印Tset PPU absdiff Pass.

**FPGA&RTL Params**

```c
npu -ppabs
```

## PPU warpaffine测试

----
`RTL` `P0`

**Description**
1、图像的仿射变换
2、利用NPU模块的ppu计算


**Expectation**
1. 对比计算后的结果与golden data进行对比。
2. 打印Tset PPU warpaffine Pass.

**FPGA&RTL Params**

```c
npu -ppwaf
```

## NETWORK YOLOV5S测试

----
`RTL` `P0`

**Description**
1、对yolov5s模型进行了优化
2、提升帧率


**Expectation**
1. 对比计算后的结果与golden data进行对比。
2. 打印Tset yolov5s ids Pass.

**FPGA&RTL Params**

```c
npu -ids_yolov5
```

## NETWORK YOLOV5S归一化测试

----
`RTL` `P0`

**Description**
1、对yolov5s模型进行了优化，在模型之前使用ppu进行归一化
2、提升帧率


**Expectation**
1. 对比计算后的结果与golden data进行对比。
2. 打印Tset yolov5s normalization Pass.

**FPGA&RTL Params**

```c
npu -ppu_yolov5
```

## NETWORK dual_core_npu测试
----
`RTL` `P0`

**Description**
1、对yolov5s模型进行了优化，在模型之前使用ppu进行归一化
2、提升帧率


**Expectation**
1. 对比计算后的结果与golden data进行对比。
2. 打印Tset yolov5s dual core Pass.

**FPGA&RTL Params**

```c
npu -core2_yolov5
```
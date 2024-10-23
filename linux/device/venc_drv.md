## h264编码执行流程

根据h264 驱动提供的 api 接口，说明编码的执行流程。

总体流程图如下：

![image-20240102172915562](/home/intchains/.config/Typora/typora-user-images/image-20240102172915562.png)

代码架构

app -> api -> drv -> ewl -> hw

主要在drv外封装了一层ewl编码器系统包装层，提供系统相关操作，如：物理内存分配、硬件I/O寄存器访问等。

## 缓冲区

缓冲区可以被编码器访问，需要是线性连续的地址，64位对齐，和图片的分辨率、类型、大小有关。

输入图像缓冲区：外部分配，仅供硬件使用的内存缓冲区，由图像的大小决定。

输出流缓冲区：外部分配，硬件和应用程序均可访问，因为编码器生成的数据量因分辨率和量化而异，无法预订此缓冲区的大小。该缓冲区必须足够大，能够容纳一帧数据，建议等于输入编码图片的大小。

硬件内部缓冲区：软件通过EWLMallocRefFrm()函数完成分配，用于存储编码过程中的参考帧。缓冲区分配的数量取决于所选的stream view mode。

软硬件共享内存：软件通过EWLMallocLinear()函数完成分配。NAL大小缓冲区和MV输出缓冲区在编码期间由硬件写入，指针在帧输出完成后返回到软件，在下一帧编码时，硬件将覆盖该输出。CABAC上下文表由控制软件在流编码开始时写入一次，硬件将在每个帧编码的开头读取此表。

## 初始化

```c
H264EncRet H264EncInit( const H264EncConfig *pEncCfg, H264EncInst *instAddr );
/*
设置属性：
streamType：流类型， 				0x48 bit16   
viewMode：流视频模式，				   控制编码器内部缓冲区个数需求
level：编码水平，						控制编码图片的最大siez, frame rate, bit rate
width,宽度						   0x38 value / 16 
heigh，高度						  0x38 value / 16 
frameRateNum, 流速率分子
frameRateDenom,流速率分母  
scaledWidth,缩小后输出图像宽度         0x3A0 0-disable
scaledHeight,缩小后输出图像高度		  0x3A4 0-disable
refFrameAmount，参考图像数量
*/
```

初始化过程创建一个编码器实例，设置内部结构，初始化EWL，并分配所需要的内存。完成后返回句柄指针。

在初始化过程中，并没有设置属性对应的寄存器，而是在 EncStrmEncode过程中设置。

H264ENC_NAL_UNIT_STREAM ：NALU流，去除起始位，只保存nalu的数据部分。

H264ENC_BYTE_STREAM ：字节流格式，普通的NAL单元组成

##   编码控制

RateCtrl

```c
H264EncRet H264EncSetRateCtrl(H264EncInst inst, const H264EncRateCtrl * pRateCtrl);
/*
 pictureRc;        
 mbRc;            
 pictureSkip;     
 qpHdr;              
 qpMin;             0x6c 量化的区间
 qpMax;           
 bitPerSecond;    
 hrd;             
 hrdCpbSize;      
 gopLen;          
 intraQpDelta;    
 fixedIntraQp;    
 mbQpAdjustment;   
 longTermPicRate; 
 mbQpAutoBoost;   
*/
```



## 功能描述

0xc9f00000 +  0x24, 1  设置使用venc内部buffer。

**公用属性**

```

```

**颜色转换 color conversion**

以30、24、16、15、12bit的RGB格式 或 交错YCbCr4:2:2 格式为输入图像，将其转换为planar YCbCr4:2:0.

```
RGB转换使能：0xfc bit28, 0-disable 1-enable
RGB转换系数：
在配置阶段进行配置H264EncPreProcessingCfg->colorConversion
0xd4 -> 0xdc
```

**缩放 scale**

```
缩放后的w、h: H264EncConfig->scaledWidth, scaledHigh
缩放的比例:  H264EncConfig->width / H264EncConfig->scaledWidth
0x3a0 0x3a4

缩放后的输出lum  base addr,  
H264EncOut->busScaledLuma
H264EncPreProcessingCfg->scaledOutput
0x39c
```

**旋转 rotation**

```
旋转角度:
0x3c bit0-1 ; 0-disable , 1-90 right, 2-90 left
配置阶段配置 H264EncPreProcessingCfg->rotation
```

**裁剪 cropping**

```
偏移（裁剪后的起始）： H264EncPreProcessingCfg->xOffset 、yOffset 
通过该参数计算偏移后yuv地址进行编码
0x3c bit26-28 Input luminance  offset
	 bit29-31 Input chrominanc offset
0x2c 输入图片基地址	 

裁剪大小： H264EncConfig->width
0x38

图片原始大小: H264EncPreProcessingCfg->origWidth 
用来做检查： origWidth >= xOffset + width
```

## 差异

```shell
0x60  HWStreamDataCount
0x94  RLC codeword count div4 output.
0x98  Macroblock count with MAD value under threshold output
0x3b0 Squared error output calculated for 13x13 pixels per macroblock. 32-­‐bit
0x3b4 Macroblock count with MAD value under threshold output
0x3b8 Macroblock count with MAD value under threshold output
```

```
地址
输出 0x14 - 0x28
输入 0x2c - 0x34
next pic lum addr 0x9c		/*input stab*/
cabac context tables 0xcc  /*input ctable*/
MV output writing    0xd0
VP8 segmentation map 0x11c
output of down-scaled  0x39c
```


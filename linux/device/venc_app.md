视频编码介绍

## 功能

```
h264
颜色转换   color conversion RGB、YUV422-> YUV420
剪切      cropping
缩小      scale-down
旋转	    rotation
防抖	    stabilization

pp后直接的输出----

多视图编码 	MV
隔行扫描
预处理 	 pre-processor
速率控制

JPEG
颜色转换   color conversion RGB、YUV422-> YUV420
剪切      cropping
缩小      scale-down
旋转	    rotation
预处理 	 pre-processor

```



## H264压缩

### 缩略语

```
MVC,  multiple view coding  多视图编码
inter frame   p帧
intra frame   I帧
scale  缩小
cropping 裁剪
rotate  旋转
QP, quantization parameter 量化参数
RC, rate control  速率控制
MAD, Mean Absolute Difference 平均绝对差值 (所有像素的差值和 / (W*H))
```

### 概念

h.264编码也称为高级视频编码(Advanced Video Coding, VAC)，是一种高精度视频录制、压缩和发布格式。

h.264中，句法元素可以分为序列、图像（帧）、片(slice)、宏块(MB)、子宏块五个层次。

![img](https://pic3.zhimg.com/80/v2-a043963a63c0aa598e38028088f6abfa_720w.webp)

在视频中，一段时间内相邻的图像的像素、亮度与色温的差别通常很小，所以没有必要对每一帧图片进行完整的编码，而是选取第一帧图片进行编码（I帧），而下一帧图像只记录与第一帧完整图像在亮度、色温等特征的差值（B帧、P帧）。

序列：即这段时间内图像变化不大的图像集，也即两个I帧之间的图像集合(左包含)。也可以成为一组GOP，GOP的第一个帧称为IDR，是特殊的I帧，一组中只有一个IDR帧，但可以有多个I帧。

帧：一幅视频图像编码后的数据为一帧。

宏块：MB, 由16*16的YUV数据组成，是H.264编码的基本单位。

I帧：是一个全帧压缩编码帧，是P帧和B帧的参考帧，占用的信息量较大，其质量影响同组中以后各帧质量。

P帧：前向预测编码图像帧，参考之前的I帧和前一个P帧进行编码。

B帧：双向预测编码图像帧，参考之前的I帧后P帧，及之后的P帧进行编码，有最高的压缩率。

### 码流结构

H.264的主要目的是具有高的视频压缩比和网络亲和性，为了达到这两个目的，H264系统框架分为两个层面：视频编码层VCL，网络抽象层NAL

视频编码层：对视频编码核心算法过程、宏块、片等概念的定义。编码完成后输出原始数据Sting of Data bits，SODB。

网络抽象出：是对图像序列、图像等概念的定义，将bit流适配到各种网络和多元环境中。将SODB数据打包成RBSP,Raw Byte Sequence Payload，实际上是在原始数据后面添加结束比特，一个比特1和若干比特0，用于字节对齐。然后再RBSP头部添加NAL 头，组成一个NAL单元。

NALU,Network Abstract Layer Unit 网络抽象单元：编码器按片将RBSP数据组合成NALU，一个NALU由NAL Header +头部信息(1B) +  RBSP组成，NAL Header 是0x000001 或0x00000001，头部信息由固定语法组成。

bit7 --forbidden_zero_bit  必须为0

bit6-5 --nal_ref_idc 重要性指示位，00-11，取值越大，表明越重要，需要优先受到保护。对于 属于参考帧的片、序列参数集、图像参数集合等重要的NALU，该标志必须大于0.

bit4-0--nal_unit_type，数据类型。

![image-20240103141112562](/home/intchains/.config/Typora/typora-user-images/image-20240103141112562.png)

H.264原始码流由一个接一个的NAL单元组成。

![img](https://pic3.zhimg.com/80/v2-9b190fd9493433b5480fa6fb913274da_720w.webp)

序列参数集SPS：保存了一组编码后图像序列的依赖的全局参数，如：编码等级、当前序列参数集ID，编码方式、图像宽度、高度等。

图像参数集PPS:保存了每一帧编码后的图像所依赖的参数，如：PPS的id,关联的SPS的id，熵编码方式等。

补充增强信息SEI:提供了向视频码流中加入额外信息的方法，非必选。

片：一帧图像可编码成一个或多个片，分片的目的是为了限制错误码的扩散和传输，使编码片相互保持独立。

### 输入图像YUV

参考 https://blog.csdn.net/qq_19923217/article/details/85197268

yuv 即 YCrCb ，是常见的原始视频数据格式，YUV分为3个分量，Y表示明亮度Luma，Luminace，也即灰度值，U和V表示色度 Chroma, Chrominance，描述影像色彩及饱和度，用于指定像素的颜色。

其中uv也使用 Cr 和 Cb表示。

采样存储方式：按像素分布规律可分为 packed --- YUV分量按采样交错存储； planar---先存储Y分量再存储U分量、V分量

按采样频率比分为 YUV444 & YUV422 & YUV420

一个分量为8位，一个像素包含一个Y分量。

对于YUV444而言，一个Y分量和一组UV分量组成一个像素，每个像素24位；

对于YUV422而言，两个Y分量共有一组UV分量，每个像素16位 --- 8 +（16/2）

对于YUV420而言，四个Y分量共有一组UV分量，每个像素12位 --- 8 +（16/4）

所以对于packed 的 yuv422的图片，数据分布为：Y U Y V  Y U Y  V

对于planar的yuv422的图片，数据分布为 Y Y Y Y... U U ... V V... 

YUV存储的先后顺序可能有变化。

对于分辨率为 weight * hig的图片，其所占内存为：

YUV444: w * h * 3

YUV422: w * h * 2

YUV420: w * h * 3/2

### 编码参数

量化参数 qp : 为了压缩视频帧，编码器执行量化，通过调整量化参数来控制量化量。QP越高，量化越多，视觉质量越低，压缩越多。QP的值低于20时，通常很难看到原始视频和压缩视频之间的差异。

速率控制 RC：目的是调整QP，以便生成的流具有用户所需的位数。

## JPEP压缩

https://blog.csdn.net/yun_hen/article/details/78135122

JPEG是一种常用的图像存储格式，是24位的图像文件格式，是一种高效率的压缩格式。

图片格式：SOI（文件头）+APP0（图像识别信息）+ DQT（定义量化表）+ SOF0（图像基本信息）+ DHT（定义Huffman表） + DRI（定义重新开始间隔）+ SOS（扫描行开始）+ EOI（文件尾）；  其中DRI是不必须的。

JPEG文件的每一个格式都按照段来存储的，段的多少和长度不定。每个段必要的部分：段的标识，由两个字节构成，第一个是0xff，第二个值为编码类型，对于不同段值不同；紧接着是段的长度，由两个字节组成，高位在前，低位在后，值 = 段长度（2） + 段内容（n）。

有些段没有长度和内存描述，比如SOI,EOI; 段与段之间可以填充任意个FF，在解码时需要忽略；对于JPEG文件中的长度、高度、间隔等描述，都采用高位在前，低位在后。

**段类型**

```
名称 	 标记码    	 说明
---------------------------------------
SOI     D8          文件头
EOI     D9          文件尾
SOF0    C0          帧开始（标准 JPEG）
SOF1    C1          同上
DHT     C4          定义 Huffman 表（霍夫曼表）
SOS 	DA          扫描行开始
DQT 	DB          定义量化表
DRI     DD          定义重新开始间隔
APP0    E0          定义交换格式和图像识别信息
COM 	FE          注释
-----------------------------------------------------------
```

APP0, 图像识别信息：

```
--------------------------------------------------------------------------
名称      字节数        值                   说明
--------------------------------------------------------------------------
段标识       1         FF
段类型       1         E0
段长度       2         0010                 如果有RGB缩略图就＝16＋3n
　　
（以下为段内容）
交换格式      5         4A46494600          “JFIF”的ASCII码
主版本号      1
次版本号      1  
密度单位      1         0＝无单位；1＝点数/英寸；2＝点数/厘米
X像素密度     2                             水平方向的密度   
Y像素密度     2                             垂直方向的密度
缩略图X像素    1                           缩略图水平像素数目  
缩略图Y像素    1                           缩略图垂直像素数目
（如果“缩略图X像素”和“缩略图Y像素”的值均＞0，那么才有下面的数据）
RGB缩略图  3×n         n＝缩略图像素总数＝缩略图X像素×缩略图Y像素， 缩略图的每个像素占24位
--------------------------------------------------------------------------
```

DQT定义量化表：JPEG文件一般有2个DQT段，分别定义亮度Y 和 色度C，一个DQT段可以有多个QT。

```
--------------------------------------------------------------------------
名称  字节数 值       说明
--------------------------------------------------------------------------
段标识   1     FF
段类型   1     DB
段长度   2     3+n      （当只有一个QT时）
（以下为段内容）
QT信息   1     0－3位： QT号
			   4－7位： QT精度（0＝8bit，1字节；否则＝16bit，2字节）
QT       n     n＝64×QT精度的字节数
--------------------------------------------------------------------------
```

**RGB**

使用ffmpeg 打开rgb格式图片 ：

ffmpeg -s 640x480 -pix_fmt nv12 -i input.nv12 -f image2 output.png

生成一个图片：

ffmpeg -f lavfi -i testsrc=size=640*480:duration=1 -pix_fmt yuv420 -frames:v 1 -vf format=yuv420 output.yuv

## 编码图片在pc上显示

1 获取硬件生成的strm

下载图片到ddr

```
restore /home/intchains/project/bms/src/venc_case/3000_test/output.yuv binary 0x130000000
```

使用Localcase程序获取strm，如case_2500，生成图片大小为 0x60寄存器值 / 8 向上取整。

导出图片时也需要8字节对其大小，方便64位转序。

2 获取jpeg头部

 使用venc 驱动运行，drivers/venc/jpeg/Encjpeg.c 中函数EncJpegHdr生成头部信息，可以在函数末尾加断点，获取头部长度并导出。

3 转序

编码器输出数据流为大端序，软件输出jpeg头部为小端序，在pc上显示时，需要将编码器输出流进行64位转序，然后使用cat命令将头和数据合并。

## 编码驱动测试

将yuv图片放入文件系统中启动，使用jpeg进行编码

kernel_module:  venc读写寄存器，需要给定基地址和中断号，并做power_on。

memalloc : venc申请内存空间的大小，需要给定线性的起始地址和长度，该地址描述在reserve_mem中。

测试命令：

```
jpeg_testenc [options] -i inputfile

必要的参数：
-x 编码宽度
-y 编码高度
-w 原图片宽度
-h 原图片高度
-g 图片类型
-i 输入图片
默认参数：
-q 5 量化等级



jpeg_testenc -x 640 -y 480 -w 640 -h 480 -g 5  -i 640.rgb
jpeg_testenc -x 640 -y 480 -w 640 -h 480 -g 3 -q 5 -i 640.yuyv422.yuv
jpeg_testenc -x 1920 -y 1088 -w 1920 -h 1088 -g 3 -q 5 -i 1088.yuyv422.yuv

jpeg_testenc -x 640 -y 480 -w 640 -h 480 -g 5 -v 1 -G 1 -i 640.rgb565   //旋转、色域转换
jpeg_testenc -w 640 -h 480 -x 64 -y 64 -X 160 -Y 160 -g 5  -i 640.rgb565    //裁剪
jpeg_testenc -x 640 -y 480 -w 640 -h 480 -g 5 -q 0 -i 640.rgb565  //量化等级




h264_testenc -w 640 -h 480 -l 5 -x 640 -y 480 -i 640.rgb565
h264_testenc -w 640 -h 480 -l 0 -x 640 -y 480 -i 640.yuv420p
h264_testenc -w 640 -h 480 -l 5 -x 640 -y 480 -r 1 -i 640.rgb565   //旋转
h264_testenc -w 640 -h 480 -l 5 -x 320 -y 320 -X 160 -Y 160 -i 640.rgb565       //裁剪
h264_testenc -w 640 -h 480 -l 5 -x 640 -y 480 -O 1 -i 640.rgb565   //色域转换
h264_testenc -w 640 -h 480 -l 5 -x 640 -y 480 -n -q 10 -i 640.rgb565       //量化等级
h264_testenc -w 640 -h 480 -l 5 -x 640 -y 480 -R 1 -i 640.rgb565  //输出模式
h264_testenc -w 640 -h 480 -l 5 -x 640 -y 480 -S 1 -z usr.bin -i 640.rgb565
h264_testenc -w 1920 -h 1088 -l 5 -x 1920 -y 1088 -i 1088.rgb565
h264_testenc -w 352 -h 288 -l 0 -x 352 -y 288 -i 352-288.300.yuv420p  -j 25 -L 20 -q 26
```

```
ffplay -video_size 352x288 -pixel_format yuv420p -framerate 30 output.yuv

/*转换、播放*/
ffmpeg -i 1088.jpeg -pix_fmt rgb565 -video_size 1920x1080 1088.rgb
ffplay -video_size 1920x1088 -pixel_format rgb565  1088.rgb

/*视频流转换*/
dd if=input.yuv of=output_25frames.yuv bs=152064 count=25
ffmpeg -s 352x288 -pix_fmt yuv420p -i output_25frames.yuv -pix_fmt rgb565 output.rgb

/*生成缩略图*/
ffmpeg -i 640.jpg -vf "scale=64:64" thumbnail.jpg

```

```
验证方式：
1 loaclcase: head + data 生成图片
	编码生成的图片需要64为转序
	
结果：图片打开之后和内核结果一致。

2 Localcase跟换图片编码查看--
	如无竖条--寄存器对比
	若有竖条--rlt仿真？

3 bms drv 调试

```



编码 api 接口及其对应参数，功能对应的参数

clk 3 4时钟约束，最大是多少

刘总要求的功能和case

继续编码的其他case




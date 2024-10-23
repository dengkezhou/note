## 测试

缩略语

```
MVC, multiple view coding  多视图编码
inter frame   p帧
intra frame   I帧


```

=================================================================================

1 stream profile an level indication

流规格和水平指示，设置支持源文件-的最大分辨率、fps 和 bit rate

2 stream type 

H264ENC_NAL_UNIT_STREAM ：NALU流，去除起始位，只保存nalu的数据部分。

H264ENC_BYTE_STREAM ：字节流格式，普通的NAL单元组成

3 view mode 指定单缓冲区（无HRD）和双缓冲区

4 Encode picture size ：

编码图片大小，必须指定像素的width 、 height，需要区分相机捕获图像的大小和最终输入编码图像的大小。

Width 必须是4的倍数，高度是2的倍数，最小 144*96，最大4080 *4080，且由stream profile an level indication限制。

水平扫描是16的倍数，即像素行的开头到下一个像素行的开头内存偏移是16的倍数。



异常修改：

\#define H264_INPUT_420SP_NV21 0



/===================================================================================

# H264

## 特征

**编码功能**： h264编码 和  JPEG编码

输入：YCbCr 格式 或 RGB格式

输出: h264--字节流、Nalu流； JPEG--JFIF，non-progressive JPEG

**预处理功能**：

输入格式转换，将输入数据转换为YCbCr420格式

裁剪，视频--从8192*8192到任何支持的大小，通过设置x-off, y-off, code_weight, code_high指定裁剪的部分。

旋转，90或270度

图像缩小，两个维度分别采用任意整数缩放比例，无限的降频比。

**防抖动功能**：

**连接功能**

**多实例功能**：可以进行多个初始化？？

**多核功能**: 使用多个核同时对同一实例编码，可以支持更高的帧率和分辨率。

## 流程：

1 初始化 H264EncInit  cfg , handle_p

初始化，配置必要的视频属性 cfg，申请必要的资源，返回操作的句柄



2  配置控制属性

H264EncSetRateCtrl  handle rate_ctl   设置速率

H264EncGetCodingCtrl             设置编码控制

H264EncGetPreProcessing        预处理



3 流产生

H264EncStrmStart 设备输出流的buffer和大小，返回输出流的属性。

H264EncSetSeiUserData  设置用户数据输入，大小 16-2048，并不是真正的输入流，而是在每帧之前添加附加消息SEI,Supplemental Enhancement Information，用于图像增强、字母显示、广播信号等，每个SEI消息都是一个NALU，其类型为6。

H264EncStrmEncode   流编码，每次编码一帧，需要循环调用，其中需要设置输入。输入源写入encIn中的busLuma ---图片总线地址。

H264EncStrmEnd  结束

## 输入

参考 https://blog.csdn.net/qq_19923217/article/details/85197268

yuv 即 YCrCb ，是常见的原始视频数据格式，YUV分为3个分量，Y表示明亮度Luma，Luminace，也即灰度值，U和V表示色度 Chroma, Chrominance，描述影像色彩及饱和度，用于指定像素的颜色。

其中uv也使用 Cr 和 Cb表示。

### 采样 存储

按像素分布规律可分为 packed --- YUV分量按采样交错存储； planar---先存储Y分量再存储U分量、V分量

按采样频率比分为 YUV444 & YUV422 & YUV420

一个分量为8位

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

## 输出

编码器按帧将输入数据编成NALU,Network Abstract Layer Unit 网络抽象单元。

最终的输出可以分为两类 byte stream 、RTP包格式。

字节流格式，h264编码器的默认封装格式，在每个NALU前添加起始码0x000001 或 0x00000001。

所以一个NALU可以分为---起始码 + 头部信息(1B) + 负载数据RBSP

头部信息由固定的语法

bit7 --forbidden_zero_bit  必须为0

bit6-5 --nal_ref_idc 重要性指示位，00-11，取值越大，表明越重要，需要优先受到保护。对于 属于参考帧的片、序列参数集、图像参数集合等重要的NALU，该标志必须大于0.

bit4-0--nal_unit_type，数据类型。

![img](https://img-blog.csdnimg.cn/20210910175307782.png?x-oss-process=image/watermark,type_ZHJvaWRzYW5zZmFsbGJhY2s,shadow_50,text_Q1NETiBATG9vbmcueHU=,size_20,color_FFFFFF,t_70,g_se,x_16)



## 配置

初始化--H264EncInit

```c
    typedef struct
    {
        H264EncStreamType streamType;   /* Byte stream */
        H264EncViewMode viewMode;       /* default H264ENC_BASE_VIEW_DOUBLE_BUFFER*/
        H264EncLevel level;             /*LEVEL_1_1*/
        u32 width;           /* Encoded picture width in pixels, multiple of 4 */
        u32 height;          /* Encoded picture height in pixels, multiple of 2 */
        u32 frameRateNum;    /* The stream time scale, [1..1048575] */
        u32 frameRateDenom;  /* Maximum frame rate is frameRateNum/frameRateDenom
                              * in frames/second. The actual frame rate will be
                              * defined by timeIncrement of encoded pictures,
                              * [1..frameRateNum] */
        u32 scaledWidth;    /* Optional down-scaled output picture width,
                               multiple of 4. 0=disabled. [16..width] */
        u32 scaledHeight;   /* Optional down-scaled output picture height,
                               multiple of 2. [96..height]                    */
        u32 refFrameAmount; /* Amount of reference frame buffers, [1..2]
                             * 1 = only last frame buffered,
                             * 2 = last and long term frames buffered */
    } H264EncConfig;
```

## 重要寄存器

```
0x2c 输入图片色度Y分量地址
0x30 输入图片亮度u分量地址
0x3c 输入图片亮度v分量地址
```



/===================================================================================

# JPEG

## 问题：




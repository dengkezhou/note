i2s

## 概念

I2S，inter-IC Sound 总线，又称集成电路内置音频总线，用于数字音频设备之间的音频数据传输。

音频：人耳可以听到的声音频率在20Hz ~ 20KHz的声波

采样频率 fs: 每秒钟取得样本的次数。采样频率越高，音质越好，占用资源越大，且由于人耳的分辨率有限，超过48000或96000的采样意义不大。22050Hz的采样频率是常用的，44100已是CD音质。如果是双声道，则采样就是双份的，文件也差不多要大一倍。

采样位数 : 将样本幅度量化，用来描述声音幅度的变化，也即声卡的分辨率。如8bit可记录256个数，即将幅度划分为256个等级。

通道数：可分为单通道和多通道，特别的如立体声有两个通道，左通道右通道。

帧：记录了一个声音单元，长度为 采样位数 * 通道数。

周期：音频设备一次处理所需要的帧数，音频设备数据的存储和访问都是以此为单位的。

交错模式：数字音频信号的存储方式，交错模式：数据以连续帧的方式存放，即先记录帧1的左、右声道样本，再记录帧2的左、右声道样本；非交错模式： 先记录一个周期内所有帧的左声道样本，再记录右声道样本。

比特率：音频数据每秒传输的速率 bps。

slot：槽，传输一帧数据中单个通道数据的时间窗口。

通道宽度,ch_width：表示通道的数据位数，通道宽度和采样位数相等，且一般为 16bit 或 24bit。



## 特点

支持半双工\全双工模式

支持主从模式

支持多通道的时分复用，支持多声道。

单通道Signal-Channel、多通道 Multi-Channels

## 信号线

MCLK,主时钟，也是参考时钟，一个系统应该使用同一个MCLK，以保证时钟同步的要求。常见的频率是256fs、384fs。

SCLK,串行时钟，对应数字音频的每一位数据。。sclk = (chn_cnt * chn_width *  2) * bclk

LRCK,帧时钟，也称作WS，word select ，或bclk，用于切换左右声道的数据。为1时表示传输右声道数据，为0时表示传输左声道数据,其频率就是采样频率fs。

SDI、SDO，输入输出数据。

**连接**: SCLK--SCLK WS--WS  SDI--SDO

发送SCLK的设备被称为master，其他设备是slave。

通过增加I2S接口的数目或其他I2S设备，可以实现多声道的应用。

## interfaces

标准模式：左右声道的数据MSB均是在WS变化后的第二个SCLK上升沿有效。

左对齐、右对齐

DSP模式：在 ws下降沿开始迁移数据，在左声道数据采样完成之后右声道立即采样，且都在ws低电平时采样。

TDM模式，时分复用，为了传输多通道的数据，引用了slot（槽）的概念

## FIFO

一个采样样本的大小由采样位数确定。

缓冲区的深度由硬件设定，单位一般为64bit，但是在软件使用时，fifo的单位为单个样本大小。

fifo_level 表明fifo中当前存储的样本个数。

软件写fifo时使用writel以64bit为单位，但生效位由样本大小确定。

## 配置流程--寄存器

初始化

| 功能               | offset  0x | name                      | bit  | set value | 说明                                          |
| ------------------ | ---------- | ------------------------- | ---- | --------- | --------------------------------------------- |
| 寄存器复位         | 0          | Control                   | 3    | 0         | 低电平使能                                    |
| 分辨率（采样位数） | 8          | Sample Resolution         | 0-4  | 0-31      | 采样位数为value + 1，分辨率为 2^（value +1 ） |
| 采样率             | 10         | Sample Rate               | 0-19 |           | Mclk / (fs * chn_cnt * chn_width)             |
| 通道宽度           | 0          | Control                   | 5-7  | 查表      | 等于采样位数                                  |
| ms_cfg             | 0          | Control                   | 2    | 0-1       | 设置master 、slave                            |
| dir_cfg            | 0          | Control                   | 1    | 0-1       | 设置transmitter、Receiver                     |
| 双工模式           | 4          | Full-Duplex Mode  Control | 0    |           | 使能全双工模式                                |
| 采样模式           |            |                           | 8-22 |           | 标准模式、左对齐...                           |

## 收发流程

发送：每次调用接口发送 fifo_depth - fifo_level 个样本，在发送之前需要关闭发送中断，发送完成之后打开发送中断。

发送中断：FIFO 为Empty 或 AEmpty 时进入中断处理函数，继续执行发送函数。

接收：每次接收完fifo中所有的数据，然后使能中断。

接收中断：在FIFI为Full 或AFull时进入中断处理函数，继续执行接收函数。

收发的中断处理函数为同一个，在触发中断时，同时处理接收与发送。

## dma

i2s dma实施外部dma握手接口，拥有两组互补的信号，一组控制外部dma向发生tx_fifo中写数据，一组控制外部dma从rx_fifo中读数据。

(dma controller burst request)

dmacbreq - Data burst request; 当i2s fifo almost full (rx_fifo, dmacbreq_rx)或 almost empty(tx_fifo, dmacbreq_tx)时触发，dma收到请求后读写对应的fifo。

dmaclbreq - Last burst request; 当i2s fifo almost full (tx_fifo, dmacbreq_tx)或 almost empty(rx_fifo, dmacbreq_rx), 并且有对应的dmacbreq 信号活跃时触发。dma收到请求后做最后的读写访问。当fifo almost empty level 设置为empty，或almost full level 设置为full时，因为fifo不可读写，所以该请求无效。

dmaclr - dma request clear; 由dma控制器对I2s请求的应答，表示burst的结束。

bms TDM 配置

```
0x0 CTRL 
ws_mode

0x30 TDM Ctrl
tdm_en    1-enable
chn_no    v-- cnt-1
chn_en    使能通道传输

0x34 TDM 全双工通道控制
使能禁止通道的接收或发送功能
```

## i2s多路

mi2s的每一路都可以独立配置为发送端或接收端，但所有的发送端必须同时是master 或 slave。

mi2s收发同步信号独立，即有两组ws sclk，分别控制收发同步，也使得接收和发送采样率和采样位数可以不一致。

 mi2s拥有两个的fifo控制器，分别控制收发fifo。拥有两组dma信号，分别对应收发请求。

### **功能**

**looo back**:相邻的两个通道可以用来做回环测试，由寄存器 I2S_CTRL 配置。8路通道由4个bit位配置分为4组：0-1；2-3； 4-5；6-7。单路I2s不能自回环，因为其收发共享逻辑块。此回环也是通过外部连线的外回环。此外，为了所有发送端或接收端的同步，还需要设置I2S_CTRL的 t/r sync_loop_back 位。

**t/r sync_rst**: 寄存器I2S_CTRL的bit 25、26,复位收发同步单元，低电平有效，其默认值也为0。所以在使能收到通道时，也需要同时设置该位为high。

underrun：当发送fifo为空，且需要进行发送时，会根据对齐向外发送0

**overrun**: 接收样本丢失，是一种错误，并且会触发中断。在清零INT_STAT寄存器的rdata_overr位时，会复位所有的接收机和接收fifo，但不会影响其他寄存器的内容。

**sample rate** : = Fmclk / (fs  * 2 * chn_width)，对比单通道发现，多路i2s设置了通道数为2，即左右声道，不再支持tdm模式。Fmclk 是系统时钟频率，fs是采样频率，也是 ws信号的频率，在非dsp模式下，chn_width是固定的值I2SMC_CHN_WIDTH，一般为24或32，由硬件决定。因为设置该寄存器时是向下取值，所以实际的fs = Fmclk / (sample_rate * 2 * chn_width) 会偏高。bclk 的周期 = fs * 2 * chn_width。

**resolution**:采样位数，对于非dsp模式的master，该寄存器为固定的值 (I2SMC_CHN_WIDTH - 1)，对于dsp模式或slave端，该位为实际的chn_width -1。

channel clock enable 、tx clock enable

### 寄存器

INTR_STAT:显示i2s产生的事件，CID_CTRL 对应的mask 为low，会禁止对应的事件产生中断，但状态仍会显示在INTR_STAT中。


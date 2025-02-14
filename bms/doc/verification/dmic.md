# DMIC 相关测试例

## DMIC 数据直接接收测试

----
`RTL` `P0`

**Description**

1. 将DMIC0设置为mode1，输入48Byte数据,对比收到的数据与输入是否一致
2. 重复步骤1，分别设置DMIC2/3/4为mode1,对比收到的数据与输入是否一致


**Expectation**

1. 数据对比全部正确
2. 打印Test RTL DMICx Pass

**FPGA&RTL Params**

```c
dmic -n 0 -m 6 
dmic -n 1 -m 6
dmic -n 2 -m 6
dmic -n 3 -m 6
```

## DMIC 级联数据DMA接收测试 

----
`RTL` `P0`

**Description**

1. 将DMIC0/1/2/3设置为mode1，打开DMA分别输入48Byte数据,对比收到的数据与输入是否一致
2. 重复步骤1，分别设置为mode2/3/4/5/6,对比收到的数据与输入是否一致

**Expectation**

1. 数据对比全部正确
2. 打印Test RTL DMA DMIC Pass

**FPGA&RTL Params**

```c
dmic -m 0 -d
dmic -m 1 -d
dmic -m 2 -d
dmic -m 3 -d
dmic -m 4 -d
dmic -m 5 -d
dmic -m 6 -d
```

## DMIC 连接数字麦克风直接接收测试 

----
`FPGA` `P0`

**Description**

1. 将DMIC0设置为mode 6
2. 录制音频
3. 下载音频，转码，播放PCM格式音频
4. 重复1~3，分别对DMIC1/2/3进行验证

**Expectation**

1.输出声音正常

**FPGA&RTL Params**

```c
dmic -n 0 -m 6 -t 100 
dmic -n 1 -m 6 -t 100
dmic -n 2 -m 6 -t 100
dmic -n 3 -m 6 -t 100
```

## DMIC 连接数字麦克风级联DMA接收测试 

----
`FPGA` `P0`

**Description**

1. 将DMIC0/1/2/3设置为mode1，开启DMA
2. 录制音频
3. 下载音频，转码，分别播放DMIC0/1/2/3音频
4. 重复1~3，进行mode2/3/4/5/6不同的模式验证

**Expectation**

1.输出声音正常

**FPGA&RTL Params**

```c
dmic -m 0 -t 100 -d
dmic -m 1 -t 100 -d
dmic -m 2 -t 100 -d
dmic -m 3 -t 100 -d
dmic -m 4 -t 100 -d
dmic -m 5 -t 100 -d
dmic -m 6 -t 100 -d
```
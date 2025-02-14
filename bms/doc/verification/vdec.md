# VDEC  相关测试例



## DUMMY

-----
`P0`


## VDEC 10bit To 8bit测试

-----
`FPGA` `RTL` `P0`

**Description**
1. 准备一段YUV 10bit NV12编码后的视频
2. 使用VDEC 解码为YUV 8bit NV12
3. 解码后的数据与GOLDEN数据进行对比



**Expectation**
1. 查看VDEC 解码后的数据与GOLDEN数据是否一致

**FPGA&RTL Params**

```c
vdec --bit

```


## VDEC 性能测试

-----
`RTL` `P0`

**Description**
1. 准备一段（1080P）H264/H265视频或（1080P）的JPEG图片
2. 使用VDEC解码
3. 分析解码速度



**Expectation**
1. 当采用h264/h265进行解码时，速度应达到480帧/s
2. 当采用jpeg解码时，速度应达到540帧/s

**FPGA&RTL Params**

```c
vdec --perf --jpeg --frame 1 --local 210 # [JPEG, PP1: 1920x1080 RGB8]
vdec --perf --h264 --frame 5 --local 400 # [H264, PP1: 1920x1080 RGB8]
vdec --perf --h264 --frame 5 --local 401 # [H264, PP0: 1920x1080 NV12, PP1: 640x480 RGB8]
vdec --perf --h265 --frame 5 --local 300 # [H265, PP1: 1920x1080 RGB8]
vdec --perf --h264 --frame 5 --local 4   # [H264, 1920x1080 NV12]
vdec --perf --h265 --frame 5 --local 4   # [H265, 1920x1080 NV12]
vdec --perf --jpeg --frame 1 --local 200 # [JPEG, 1920x1080 NV12]

```


## VDEC Local Case H264@0
----
`FPGA` `RTL` `P0`

**Description**
1. [MIN_SIZE] H264 stream input, rfc enabled, all pp channels disabled IBBBP for memory cover

**Expectation**
1. 查看VDEC 解码后的数据与GOLDEN数据是否一致


**FPGA&RTL Params**

```c
vdec --h264 --frame 5 --local 0

```


## VDEC Local Case H264@1
----
`FPGA` `RTL` `P0`

**Description**
1. [MAX_SIZE] H264 stream input, rfc enabled, all pp channels disabled

**Expectation**
1. 查看VDEC 解码后的数据与GOLDEN数据是否一致


**FPGA&RTL Params**

```c
vdec --h264 --frame 2 --local 1
```


## VDEC Local Case H264@2
----
`FPGA` `RTL` `P0`

**Description**
1. [ERROR] H264 error concealment case, stream has error in slice data

**Expectation**
1. 查看VDEC 解码后的数据与GOLDEN数据是否一致


**FPGA&RTL Params**

```c
vdec --h264 --frame 5 --local 2
```


## VDEC Local Case H264@3
----
`FPGA` `RTL` `P0`

**Description**
1. [SUBSYS_PP] H264 stream input, rfc enabled, enable all IPs and all pp, test crop and scale

**Expectation**
1. 查看VDEC 解码后的数据与GOLDEN数据是否一致


**FPGA&RTL Params**

```c
vdec --h264 --frame 5 --local 3
```


## VDEC Local Case H264@4
----
`FPGA` `RTL` `P0`

**Description**
1. [PERFORMANCE] H264 stream input, rfc enabled, bit depth 8bit typical performance case; GOP info: IBBBP

**Expectation**
1. 查看VDEC 解码后的数据与GOLDEN数据是否一致


**FPGA&RTL Params**

```c
vdec --h264 --frame 5 --local 4
```


## VDEC Local Case H264@5
----
`FPGA` `RTL` `P0`

**Description**
1. [PERFORMANCE] H264 stream input, rfc enabled, bit depth 10bit performance stream. 30fps/10Mbps. 720p; GOP info: IBPBP

**Expectation**
1. 查看VDEC 解码后的数据与GOLDEN数据是否一致


**FPGA&RTL Params**

```c
vdec --h264 --frame 5 --local 5
```


## VDEC Local Case H264@21
----
`FPGA` `RTL` `P0`

**Description**
1. [H264_MVC] test h264 mvc stream

**Expectation**
1. 查看VDEC 解码后的数据与GOLDEN数据是否一致


**FPGA&RTL Params**

```c
vdec --h264 --frame 5 --local 21
```


## VDEC Local Case H264@22
----
`FPGA` `RTL` `P0`

**Description**
1. [H264_SVC] test h264 svc stream

**Expectation**
1. 查看VDEC 解码后的数据与GOLDEN数据是否一致


**FPGA&RTL Params**

```c
vdec --h264 --frame 5 --local 22
```


## VDEC Local Case H264@23
----
`FPGA` `RTL` `P0`

**Description**
1. [SRAM] IBBBP for cover memory g2_emd_stpr_bsd_ram and g2_mvd_h264_poc_ram

**Expectation**
1. 查看VDEC 解码后的数据与GOLDEN数据是否一致


**FPGA&RTL Params**

```c
vdec --h264 --frame 5 --local 23
```


## VDEC Local Case HEVC@0
----
`FPGA` `RTL` `P0`

**Description**
1. [MIN_SIZE] HEVC stream input, rfc enabled, all pp channels disabled

**Expectation**
1. 查看VDEC 解码后的数据与GOLDEN数据是否一致


**FPGA&RTL Params**

```c
vdec --h265 --frame 5 --local 0
```


## VDEC Local Case HEVC@1
----
`FPGA` `RTL` `P0`

**Description**
1. [MAX_SIZE] HEVC stream input, rfc enabled, all pp channels disabled

**Expectation**
1. 查看VDEC 解码后的数据与GOLDEN数据是否一致


**FPGA&RTL Params**

```c
vdec --h265 --frame 2  --local 1
```


## VDEC Local Case HEVC@2
----
`FPGA` `RTL` `P0`

**Description**
1. [ERROR] HEVC error concealment case, stream has error in slice header

**Expectation**
1. 查看VDEC 解码后的数据与GOLDEN数据是否一致


**FPGA&RTL Params**

```c
vdec --h265 --frame 3  --local 2
```


## VDEC Local Case HEVC@3
----
`FPGA` `RTL` `P0`

**Description**
1. [SUBSYS_PP] HEVC stream input, rfc enabled, enable all IPs and all pp, test crop and scale

**Expectation**
1. 查看VDEC 解码后的数据与GOLDEN数据是否一致


**FPGA&RTL Params**

```c
vdec --h265 --frame 1  --local 3
```


## VDEC Local Case HEVC@4
----
`FPGA` `RTL` `P0`

**Description**
1. [PERFORMANCE] HEVC stream input, rfc enabled, bit depth 8bit

**Expectation**
1. 查看VDEC 解码后的数据与GOLDEN数据是否一致


**FPGA&RTL Params**

```c
vdec --h265 --frame 5  --local 4
```


## VDEC Local Case HEVC@5
----
`FPGA` `RTL` `P0`

**Description**
1. [PERFORMANCE] HEVC stream input, rfc enabled, bit depth 10bit

**Expectation**
1. 查看VDEC 解码后的数据与GOLDEN数据是否一致


**FPGA&RTL Params**

```c
vdec --h265 --frame 5  --local 5
```


## VDEC Local Case HEVC@8
----
`FPGA` `RTL` `P0`

**Description**
1. [MAX_SIZE_PP] all pp output max size

**Expectation**
1. 查看VDEC 解码后的数据与GOLDEN数据是否一致


**FPGA&RTL Params**

```c
vdec --h265 --frame 2  --local 8
```


## VDEC Local Case HEVC@21
----
`FPGA` `RTL` `P0`

**Description**
1. [400 SAMPLE] 400 test for HEVC

**Expectation**
1. 查看VDEC 解码后的数据与GOLDEN数据是否一致


**FPGA&RTL Params**

```c
vdec --h265 --frame 5  --local 21
```


## VDEC Local Case HEVC@22
----
`FPGA` `RTL` `P0`

**Description**
1. [SRAM] cover memory ppx_sca_tile_rd/wr_ram

**Expectation**
1. 查看VDEC 解码后的数据与GOLDEN数据是否一致


**FPGA&RTL Params**

```c
vdec --h265 --frame 5  --local 22
```


## VDEC Local Case HEVC@23
----
`FPGA` `RTL` `P0`

**Description**
1. [SRAM] main10 case, cover memory ppx_res_bits_ram

**Expectation**
1. 查看VDEC 解码后的数据与GOLDEN数据是否一致


**FPGA&RTL Params**

```c
vdec --h265 --frame 5  --local 23
```


## VDEC Local Case HEVC@25
----
`FPGA` `RTL` `P0`

**Description**
1. [SRAM] cover memory ppx_tile_c/y_edge_rd/wr_ram

**Expectation**
1. 查看VDEC 解码后的数据与GOLDEN数据是否一致


**FPGA&RTL Params**

```c
vdec --h265 --frame 5  --local 25
```


## VDEC Local Case HEVC@101
----
`FPGA` `RTL` `P0`

**Description**
1. [PP] HEVC stream input, pp output format: RGB888_P

**Expectation**
1. 查看VDEC 解码后的数据与GOLDEN数据是否一致


**FPGA&RTL Params**

```c
vdec --h265 --frame 5  --local 101
```


## VDEC Local Case HEVC@30
----
`FPGA` `RTL` `P0`

**Description**
1. [PP] HEVC stream input, pp output format: YUV420

**Expectation**
1. 查看VDEC 解码后的数据与GOLDEN数据是否一致


**FPGA&RTL Params**

```c
vdec --h265 --frame 5  --local 30
```


## VDEC Local Case HEVC@31
----
`FPGA` `RTL` `P0`

**Description**
1. [PP] HEVC stream input, pp output format: YUV420_P010

**Expectation**
1. 查看VDEC 解码后的数据与GOLDEN数据是否一致


**FPGA&RTL Params**

```c
vdec --h265 --frame 5  --local 31
```


## VDEC Local Case JPEG@0
----
`FPGA` `RTL` `P0`

**Description**
1. [MIN_SIZE] JPEG stream input, rfc disabled, all pp channels disabled

**Expectation**
1. 查看VDEC 解码后的数据与GOLDEN数据是否一致


**FPGA&RTL Params**

```c
vdec --jpeg --frame 1 --local 0
```


## VDEC Local Case JPEG@2
----
`FPGA` `RTL` `P0`

**Description**
1. [ERROR] JPEG stream input, rfc disabled, all pp channels disabled

**Expectation**
1. 查看VDEC 解码后的数据与GOLDEN数据是否一致


**FPGA&RTL Params**

```c
vdec --jpeg --frame 1 --local 2
```


## VDEC Local Case JPEG@3
----
`FPGA` `RTL` `P0`

**Description**
1. [SUBSYS_PP] JPEG stream input, rfc disabled, enable all IPs and all pp, test crop and scale

**Expectation**
1. 查看VDEC 解码后的数据与GOLDEN数据是否一致


**FPGA&RTL Params**

```c
vdec --jpeg --frame 1 --local 3
```


## VDEC Local Case JPEG@4
----
`FPGA` `RTL` `P0`

**Description**
1. [PERFORMANCE] JPEG stream input, rfc disabled, bit depth 8bit

**Expectation**
1. 查看VDEC 解码后的数据与GOLDEN数据是否一致


**FPGA&RTL Params**

```c
vdec --jpeg --frame 1 --local 4
```


## VDEC Local Case JPEG@10
----
`FPGA` `RTL` `P0`

**Description**
1. [400_SAMPLE] 400 test for PJPEG

**Expectation**
1. 查看VDEC 解码后的数据与GOLDEN数据是否一致


**FPGA&RTL Params**

```c
vdec --jpeg --frame 1 --local 10
```


## VDEC Local Case JPEG@11
----
`FPGA` `RTL` `P0`

**Description**
1. [411_SAMPLE] 411 test for PJPEG

**Expectation**
1. 查看VDEC 解码后的数据与GOLDEN数据是否一致


**FPGA&RTL Params**

```c
vdec --jpeg --frame 1 --local 11
```


## VDEC Local Case JPEG@12
----
`FPGA` `RTL` `P0`

**Description**
1. [420_SAMPLE] 420 test for PJPEG

**Expectation**
1. 查看VDEC 解码后的数据与GOLDEN数据是否一致


**FPGA&RTL Params**

```c
vdec --jpeg --frame 1 --local 12
```


## VDEC Local Case JPEG@13
----
`FPGA` `RTL` `P0`

**Description**
1. [422_SAMPLE] 422 test for PJPEG

**Expectation**
1. 查看VDEC 解码后的数据与GOLDEN数据是否一致


**FPGA&RTL Params**

```c
vdec --jpeg --frame 1 --local 13
```


## VDEC Local Case JPEG@14
----
`FPGA` `RTL` `P0`

**Description**
1. [440_SAMPLE] 440 test for PJPEG

**Expectation**
1. 查看VDEC 解码后的数据与GOLDEN数据是否一致


**FPGA&RTL Params**

```c
vdec --jpeg --frame 1 --local 14
```


## VDEC Local Case JPEG@15
----
`FPGA` `RTL` `P0`

**Description**
1. [444_SAMPLE] 444 test for PJPEG

**Expectation**
1. 查看VDEC 解码后的数据与GOLDEN数据是否一致


**FPGA&RTL Params**

```c
vdec --jpeg --frame 1 --local 15
```


## VDEC Local Case JPEG@16
----
`FPGA` `RTL` `P0`

**Description**
1. [400_SAMPLE] 400 test for HJPEG

**Expectation**
1. 查看VDEC 解码后的数据与GOLDEN数据是否一致


**FPGA&RTL Params**

```c
vdec --jpeg --frame 1 --local 16
```


## VDEC Local Case JPEG@17
----
`FPGA` `RTL` `P0`

**Description**
1. [411_SAMPLE] 411 test for HJPEG

**Expectation**
1. 查看VDEC 解码后的数据与GOLDEN数据是否一致


**FPGA&RTL Params**

```c
vdec --jpeg --frame 1 --local 17
```


## VDEC Local Case JPEG@18
----
`FPGA` `RTL` `P0`

**Description**
1. [420_SAMPLE] 420 test for HJPEG

**Expectation**
1. 查看VDEC 解码后的数据与GOLDEN数据是否一致


**FPGA&RTL Params**

```c
vdec --jpeg --frame 1 --local 18
```


## VDEC Local Case JPEG@19
----
`FPGA` `RTL` `P0`

**Description**
1. [422_SAMPLE] 422 test for HJPEG

**Expectation**
1. 查看VDEC 解码后的数据与GOLDEN数据是否一致


**FPGA&RTL Params**

```c
vdec --jpeg --frame 1 --local 19
```


## VDEC Local Case JPEG@20
----
`FPGA` `RTL` `P0`

**Description**
1. [440_SAMPLE] 440 test for HJPEG

**Expectation**
1. 查看VDEC 解码后的数据与GOLDEN数据是否一致


**FPGA&RTL Params**

```c
vdec --jpeg --frame 1 --local 20
```


## VDEC Local Case JPEG@21
----
`FPGA` `RTL` `P0`

**Description**
1. [444_SAMPLE] 444 test for HJPEG

**Expectation**
1. 查看VDEC 解码后的数据与GOLDEN数据是否一致


**FPGA&RTL Params**

```c
vdec --jpeg --frame 1 --local 21
```


## VDEC Local Case JPEG@22
----
`FPGA` `RTL` `P0`

**Description**
1. [12BIT] 12bit test for HJPEG

**Expectation**
1. 查看VDEC 解码后的数据与GOLDEN数据是否一致


**FPGA&RTL Params**

```c
vdec --jpeg --frame 1 --local 22
```


## VDEC Local Case JPEG@23
----
`FPGA` `RTL` `P0`

**Description**
1. [SRAM] 12bit case, cover memory ppx_res_bits_ram

**Expectation**
1. 查看VDEC 解码后的数据与GOLDEN数据是否一致


**FPGA&RTL Params**

```c
vdec --jpeg --frame 1 --local 23
```


## VDEC Local Case PPONLY@8
----
`FPGA` `RTL` `P0`

**Description**
1. [MAX_SIZE_PP] all pp output max size

**Expectation**
1. 查看VDEC 解码后的数据与GOLDEN数据是否一致


**FPGA&RTL Params**

```c
vdec --pp --frame 2 --local 8
```


## VDEC Local Case PPONLY@3
----
`FPGA` `RTL` `P0`

**Description**
1. [SUBSYS_PP] HEVC stream input, rfc enabled, enable all IPs and all pp, test crop and scale

**Expectation**
1. 查看VDEC 解码后的数据与GOLDEN数据是否一致


**FPGA&RTL Params**

```c
vdec --pp --frame 1 --local 3
```


## VDEC Local Case PPONLY@101
----
`FPGA` `RTL` `P0`

**Description**
1. [PP] HEVC stream input, pp output format: RGB888_P

**Expectation**
1. 查看VDEC 解码后的数据与GOLDEN数据是否一致


**FPGA&RTL Params**

```c
vdec --pp --frame 5 --local 101
```


## VDEC Local Case PPONLY@30
----
`FPGA` `RTL` `P0`

**Description**
1. [PP] HEVC stream input, pp output format: YUV420

**Expectation**
1. 查看VDEC 解码后的数据与GOLDEN数据是否一致


**FPGA&RTL Params**

```c
vdec --pp --frame 5 --local 30
```


## VDEC Local Case PPONLY@31
----
`FPGA` `RTL` `P0`

**Description**
1. [PP] HEVC stream input, pp output format: YUV420_P010

**Expectation**
1. 查看VDEC 解码后的数据与GOLDEN数据是否一致


**FPGA&RTL Params**

```c
vdec --pp --frame 5 --local 31
```


## VDEC Local Case INT@0
----
`FPGA` `RTL` `P0`

**Description**
1. [INT] test abort interrupt

**Expectation**
1. 查看VDEC 解码后的数据与GOLDEN数据是否一致


**FPGA&RTL Params**

```c
vdec --int --frame 1 --local 0
```


## VDEC Local Case INT@1
----
`FPGA` `RTL` `P0`

**Description**
1. [INT] test bus error interrupt

**Expectation**
1. 查看VDEC 解码后的数据与GOLDEN数据是否一致


**FPGA&RTL Params**

```c
vdec --int --frame 1 --local 1
```


## VDEC Local Case INT@2
----
`FPGA` `RTL` `P0`

**Description**
1. [INT] test internal timeout interrupt

**Expectation**
1. 查看VDEC 解码后的数据与GOLDEN数据是否一致


**FPGA&RTL Params**

```c
vdec --int --frame 1 --local 2
```


## VDEC Local Case INT@3
----
`FPGA` `RTL` `P0`

**Description**
1. [INT] test external timeout interrupt

**Expectation**
1. 查看VDEC 解码后的数据与GOLDEN数据是否一致


**FPGA&RTL Params**

```c
vdec --int --frame 1 --local 3
```

## VDEC Local Case JPEG@209
----
`FPGA` `RTL` `P0`

**Description**
1. [PERFORMANCE] JPEG stream input, 32768x48, rfc disabled, bit depth 8bit

**Expectation**
1. 查看VDEC 解码后的数据与GOLDEN数据是否一致


**FPGA&RTL Params**

```c
vdec --jpeg --frame 1 --local 209 # [32768x48 NV12]
```



## VDEC PP@C6100000 Local Case PPONLY@8
----
`FPGA` `RTL` `P0`

**Description**
1. [MAX_SIZE_PP] all pp output max size

**Expectation**
1. 查看VDEC 解码后的数据与GOLDEN数据是否一致


**FPGA&RTL Params**

```c
vdec --pp -c --frame 2 --local 8
```


## VDEC PP@C6100000 Local Case PPONLY@3
----
`FPGA` `RTL` `P0`

**Description**
1. [SUBSYS_PP] HEVC stream input, rfc enabled, enable all IPs and all pp, test crop and scale

**Expectation**
1. 查看VDEC 解码后的数据与GOLDEN数据是否一致


**FPGA&RTL Params**

```c
vdec --pp -c --frame 1 --local 3
```

## VDEC PP@C6100000 Local Case PPONLY@30
----
`FPGA` `RTL` `P0`

**Description**
1. [PP] HEVC stream input, pp output format: YUV420

**Expectation**
1. 查看VDEC 解码后的数据与GOLDEN数据是否一致


**FPGA&RTL Params**

```c
vdec --pp -c --frame 5 --local 30
```


## VDEC PP@C6100000 Local Case PPONLY@31
----
`FPGA` `RTL` `P0`

**Description**
1. [PP] HEVC stream input, pp output format: YUV420_P010

**Expectation**
1. 查看VDEC 解码后的数据与GOLDEN数据是否一致


**FPGA&RTL Params**

```c
vdec --pp -c --frame 5 --local 31
```

## VDEC PP@C6100000 Local Case INT@0
----
`FPGA` `RTL` `P0`

**Description**
1. [INT] test abort interrupt

**Expectation**
1. 查看VDEC 解码后的数据与GOLDEN数据是否一致


**FPGA&RTL Params**

```c
vdec --int -c --frame 1 --local 0
```


## VDEC PP@C6100000 Local Case INT@1
----
`FPGA` `RTL` `P0`

**Description**
1. [INT] test bus error interrupt

**Expectation**
1. 查看VDEC 解码后的数据与GOLDEN数据是否一致


**FPGA&RTL Params**

```c
vdec --int -c --frame 1 --local 1
```
# I2C 相关测试例

## I2C 7 bits地址读写

----
`FPGA` `RTL` `P0`

**Description**

1. 配置i2c0 master模式，i2c1 slave模式，配置成7bit地址模式，i2c速度为100khz（rtl强制设置为4mhz）
2. i2c0 先写256bytes(rtl 32bytes)数据到i2c1，对比i2c1数据是否正确
3. i2c0 从i2c1读取256bytes(rtl 32bytes)数据，对比i2c0数据是否正确
4. 配置i2c1 master模式，i2c0 slave模式，配置成7bit地址模式，i2c速度为100khz（rtl强制设置为4mhz）。类似地，重复步骤2、3
5. 配置i2c2 master模式，i2c3 slave模式，配置成7bit地址模式，i2c速度为400khz（rtl强制设置为4mhz）。类似地，重复步骤2、3
6. 配置i2c3 master模式，i2c2 slave模式，配置成7bit地址模式，i2c速度为400khz（rtl强制设置为4mhz）。类似地，重复步骤2、3
7. 配置i2c4 master模式，i2c5 slave模式，配置成7bit地址模式，i2c速度为1mhz（rtl强制设置为4mhz）。类似地，重复步骤2、3
8. 配置i2c5 master模式，i2c4 slave模式，配置成7bit地址模式，i2c速度为1mhz（rtl强制设置为4mhz）。类似地，重复步骤2、3
9. 配置i2c6 master模式，i2c7 slave模式，配置成7bit地址模式，i2c速度为1mhz（rtl强制设置为4mhz）。类似地，重复步骤2、3
10. 配置i2c7 master模式，i2c6 slave模式，配置成7bit地址模式，i2c速度为1mhz（rtl强制设置为4mhz）。类似地，重复步骤2、3

**Expectation**

1. 数据对比全部正确
2. 打印Test I2C 7 bits addr Pass

**FPGA&RTL Params**

```c
i2c -m 0 -s 1 -a 7 -d 0
i2c -m 1 -s 0 -a 7 -d 0
i2c -m 2 -s 3 -a 7 -d 1
i2c -m 3 -s 2 -a 7 -d 1
i2c -m 4 -s 5 -a 7 -d 2
i2c -m 5 -s 4 -a 7 -d 2
i2c -m 6 -s 7 -a 7 -d 2
i2c -m 7 -s 6 -a 7 -d 2
```

## I2C 10 bits地址读写

----
`FPGA` `RTL` `P0`

**Description**

1. 配置i2c0 master模式，i2c1 slave模式，并配置成10bit地址模式，i2c速度为100khz（rtl强制设置为4mhz）
2. i2c0 先写256bytes(rtl 32bytes)数据到i2c1，对比i2c1数据是否正确
3. i2c0 从i2c1读取256bytes(rtl 32bytes)数据，对比i2c0数据是否正确
4. 配置i2c1 master模式，i2c0 slave模式，配置成10bit地址模式，i2c速度为100khz（rtl强制设置为4mhz）。类似地，重复步骤2、3
5. 配置i2c2 master模式，i2c3 slave模式，配置成10bit地址模式，i2c速度为400khz（rtl强制设置为4mhz）。类似地，重复步骤2、3
6. 配置i2c3 master模式，i2c2 slave模式，配置成10bit地址模式，i2c速度为400khz（rtl强制设置为4mhz）。类似地，重复步骤2、3
7. 配置i2c4 master模式，i2c5 slave模式，配置成10bit地址模式，i2c速度为1mhz（rtl强制设置为4mhz）。类似地，重复步骤2、3
8. 配置i2c5 master模式，i2c4 slave模式，配置成10bit地址模式，i2c速度为1mhz（rtl强制设置为4mhz）。类似地，重复步骤2、3
9. 配置i2c6 master模式，i2c7 slave模式，配置成10bit地址模式，i2c速度为1mhz（rtl强制设置为4mhz）。类似地，重复步骤2、3
10. 配置i2c7 master模式，i2c6 slave模式，配置成10bit地址模式，i2c速度为1mhz（rtl强制设置为4mhz）。类似地，重复步骤2、3

**Expectation**

1. 所有数据对比正确
1. 打印Test I2C 10 bits addr Pass

**FPGA&RTL Params**

```c
i2c -m 0 -s 1 -a 10 -d 0
i2c -m 1 -s 0 -a 10 -d 0
i2c -m 2 -s 3 -a 10 -d 1
i2c -m 3 -s 2 -a 10 -d 1
i2c -m 4 -s 5 -a 10 -d 2
i2c -m 5 -s 4 -a 10 -d 2
i2c -m 6 -s 7 -a 10 -d 2
i2c -m 7 -s 6 -a 10 -d 2
```

## I2C slave monitor模式测试

----
`FPGA` `RTL` `P0`

**Description**

1. 配置i2c0 master模式，i2c1 slave模式，并配置成7bit地址模式，i2c速度为100khz（rtl强制设置为4mhz）
2. i2c0配置成slvmon模式
3. 配置i2c1 master模式，i2c0 slave模式，配置成7bit地址模式，i2c速度为100khz（rtl强制设置为4mhz）。类似地，重复步骤2
4. 配置i2c2 master模式，i2c3 slave模式，配置成7bit地址模式，i2c速度为400khz（rtl强制设置为4mhz）。类似地，重复步骤2
5. 配置i2c3 master模式，i2c2 slave模式，配置成7bit地址模式，i2c速度为400khz（rtl强制设置为4mhz）。类似地，重复步骤2
6. 配置i2c4 master模式，i2c5 slave模式，配置成7bit地址模式，i2c速度为1mhz（rtl强制设置为4mhz）。类似地，重复步骤2
7. 配置i2c5 master模式，i2c4 slave模式，配置成7bit地址模式，i2c速度为1mhz（rtl强制设置为4mhz）。类似地，重复步骤2
8. 配置i2c6 master模式，i2c7 slave模式，配置成7bit地址模式，i2c速度为1mhz（rtl强制设置为4mhz）。类似地，重复步骤2、3
9. 配置i2c7 master模式，i2c6 slave模式，配置成7bit地址模式，i2c速度为1mhz（rtl强制设置为4mhz）。类似地，重复步骤2、3

**Expectation**

1. 产生slv-rdy中断, 打印Test I2C slave monitor Pass

**FPGA&RTL Params**

```c
i2c -m 0 -s 1 -a 7 -d 0 -t
i2c -m 1 -s 0 -a 7 -d 0 -t
i2c -m 2 -s 3 -a 7 -d 1 -t
i2c -m 3 -s 2 -a 7 -d 1 -t
i2c -m 4 -s 5 -a 7 -d 2 -t
i2c -m 5 -s 4 -a 7 -d 2 -t
i2c -m 6 -s 7 -a 7 -d 2 -t
i2c -m 7 -s 6 -a 7 -d 2 -t
```

## I2C 连接实际外设（E2PROM）

----
`FPGA` `P0`

**Description**

1. 配置i2c1 master模式，按照I2C外设（E2PROM）的需求配置i2c1 master
2. 写E2PROM 256字节
3. 读E2PROM 256字节

**Expectation**

1. 比较读写的数据一致，打印Test I2C Read&Write E2PROM Pass

**FPGA&RTL Params**

```c
i2c -m 1 -a 7 -d 0 -e
```

## I2C3/4/5管脚复用测试

----
`RTL` `P0`

**Description**

1. 配置i2c3 pad管脚映射到cpad_063、cpad_064，i2c2 master模式，i2c3 slave模式，配置成7bit地址模式，i2c速度为1mhz（rtl强制设置为4mhz）
2. i2c2 先写256bytes(rtl 32bytes)数据到i2c3，对比i2c3数据是否正确
3. i2c2 从i2c3读取256bytes(rtl 32bytes)数据，对比i2c2数据是否正确
4. 配置i2c4 pad管脚映射到cpad_107、cpad_108，配置i2c5 pad管脚映射到cpad_109、cpad_110,i2c4 master模式，i2c5 slave模式，配置成7bit地址模式，i2c速度为1mhz（rtl强制设置为4mhz）
5. i2c4 先写256bytes(rtl 32bytes)数据到i2c5，对比i2c5数据是否正确
6. i2c5 从i2c4读取256bytes(rtl 32bytes)数据，对比i2c4数据是否正确

**Expectation**

1. 数据对比全部正确
2. 打印Test I2C 7 bits addr multiplex Pass

**FPGA&RTL Params**

```c
i2c -m 2 -s 3 -a 7 -d 2 -p
i2c -m 4 -s 5 -a 7 -d 2 -p
```

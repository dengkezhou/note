# I2C相关接口说明

## 头文件

```c
#include <i2c.h>
```

## 接口说明

* i2c初始化
  
```c
i2c_dev_t *itcs_i2c_init(i2c_chan index, i2c_mode mode, i2c_addr_mode addr_mode, int devaddr, i2c_speed_mode speed);
```

参数/返回值列表:

|参数名|参数说明|
|--|--|
|index|i2c控制器号，[见下](#i2c_id)|
|mode|i2c模式，[见下](#i2c_mode)|
|addr_mode|地址模式，[见下](#i2c_addr)|
|devaddr|只用于i2c控制器用作slave，master时为0|
|speed|传输速度，[见下](#i2c_speed)|

|返回值|返回值说明|
|--|--|
|!NULL|成功|
|NULL|失败|

i2c控制器号:

<a id="i2c_id"></a>

| 模式      | 说明 |
| --------- | ---- |
| I2C_CHAN0 | i2c0 |
| I2C_CHAN1 | i2c1 |
| I2C_CHAN2 | i2c2 |
| I2C_CHAN3 | i2c3 |
| I2C_CHAN4 | i2c4 |
| I2C_CHAN5 | i2c5 |

i2c模式:

<a id="i2c_mode"></a>

| 模式       | 说明          |
| ---------- | ------------- |
| I2C_SLAVE  | i2c控制器作从 |
| I2C_MASTER | i2c控制器作主 |

地址模式:

<a id="i2c_addr"></a>

| 模式        | 说明         |
| ----------- | ------------ |
| ADDR_7BITS  | 7位地址模式  |
| ADDR_10BITS | 10位地址模式 |

传输速度:

<a id="i2c_speed"></a>

| 模式      | 说明   |
| --------- | ------ |
| NORMAL    | 100KHZ |
| FAST      | 400KHZ |
| FAST_PLUS | 1MHZ   |


* i2c传输

```c
int itcs_i2c_transfer(i2c_dev_t *dev, i2c_msg_t *msg, int num);
```

参数/返回值列表:

| 参数名 | 参数说明                       |
| ------ | ------------------------------ |
| dev    | 由itcs_i2c_init获得            |
| msg    | 传输描述结构，[见下](#i2c_msg) |
| num    | msg结构体个数                  |

| 返回值 | 返回值说明 |
| ------ | ---------- |
| 0      | 传输成功   |
| -1     | 传输失败   |

i2c传输描述结构i2c_msg_t:

<a id="i2c_msg"></a>

| 结构体参数 | 必填 | 参数说明                                |
| ---------- | ---- | --------------------------------------- |
| addr       | 是   | 从设备7位或10位地址                     |
| flags      | 是   | 读或写或10位地址标志，[见下](#i2c_flag) |
| len        | 是   | 传输长度                                |
| buf        | 是   | 传输buffer                              |

读或写或10位地址标志:

<a id="i2c_flag"></a>

| 模式           | 说明         |
| -------------- | ------------ |
| CDNS_I2C_WRITE | 写           |
| CDNS_I2C_READ  | 读           |
| CDNS_I2C_M_TEN | 10位地址模式 |


* i2c写

```c
int itcs_i2c_write(i2c_dev_t *dev, int devaddr, unsigned char *buf, int len, bool blocked);
```

参数/返回值列表:
|参数名|参数说明|
|--|--|
|dev|由itcs_i2c_init获得|
|devaddr|从设备地址|
|buf|写缓冲首地址|
|len|写长度|
|blocked|阻塞标志位，true表示阻塞，false为非阻塞|

|返回值|返回值说明|
|--|--|
|0|写成功|
|-1|写失败|

* i2c读

```c
int itcs_i2c_read(i2c_dev_t *dev, int devaddr, unsigned char *buf, int len, bool blocked);
```

参数/返回值列表:
|参数名|参数说明|
|--|--|
|dev|由itcs_i2c_init获得|
|devaddr|从设备地址|
|buf|读缓冲首地址|
|len|读长度|
|blocked|阻塞标志位，true表示阻塞，false为非阻塞|

|返回值|返回值说明|
|--|--|
|0|读成功|
|-1|读失败|

* i2c传输是否完成
```c
int itcs_i2c_is_completed(i2c_dev_t *dev);
```
参数/返回值列表:
|参数名|参数说明|
|--|--|
|dev|由itcs_i2c_init获得|

|返回值|返回值说明|
|--|--|
|1|传输已完成|
|0|传输未完成|
|-1|传输错误|

* i2c slave设备是否检测到

```c
int itcs_i2c_slv_mon_is_rdy(i2c_dev_t *dev);
```

参数/返回值列表:

| 参数名 | 参数说明            |
| ------ | ------------------- |
| dev    | 由itcs_i2c_init获得 |

| 返回值 | 返回值说明    |
| ------ | ------------- |
| 1      | 监测到slave   |
| 0      | 未监测到slave |

* i2c slave设备检测功能使能

```c
int itcs_i2c_slv_mon_config(i2c_dev_t *dev, int devaddr, int interval);
```

参数/返回值列表:

| 参数名   | 参数说明                                           |
| -------- | -------------------------------------------------- |
| dev      | 由itcs_i2c_init获得                                |
| devaddr  | slave设备地址                                      |
| interval | 每次探测slave间隔时间，最大不超过SLV_MON_PAUSE_MAX |

| 返回值 | 返回值说明 |
| ------ | ---------- |
| 0      | 使能成功   |
| -1     | 使能失败   |

* i2c退出

```c
void itcs_i2c_exit(i2c_dev_t *dev);
```
参数列表:
|参数名|参数说明|
|--|--|
|dev|由itcs_i2c_init获得|


## 示例代码

```c
#include <common.h>
#include <command.h>
#include <testbench.h>
#include <malloc.h>
#include <asm/io.h>
#include <getopt.h>
#include <pads.h>
#include <i2c.h>

#define ADDR_TEST_LEN 12

uint8_t readdata[ADDR_TEST_LEN] = { 0 }, writedata[ADDR_TEST_LEN] = { 0 };

static int i2c_test(i2c_chan master, i2c_chan slave, i2c_addr_mode addr_mode,
		    i2c_speed_mode speed)
{
	int finish_flag = 0;
	int ret, i;
	i2c_dev_t *ms, *slv;
	int devaddr = 0x55;

	printf("test len: %d bytes\n", ADDR_TEST_LEN);

	for (i = 0; i < ADDR_TEST_LEN; i++)
		writedata[i] = i;

	ms = itcs_i2c_init(master, I2C_MASTER, addr_mode, 0, speed);
	slv = itcs_i2c_init(slave, I2C_SLAVE, addr_mode, devaddr, speed);
	if (!ms || !slv) {
		printf("i2c init failed\n");
		return -1;
	}

	itcs_i2c_read(slv, devaddr, readdata, ADDR_TEST_LEN, false);
	itcs_i2c_write(ms, devaddr, writedata, ADDR_TEST_LEN, true);
	while (1) {
		if (itcs_i2c_is_completed(slv)) {
			finish_flag = 1;
			break;
		}
		udelay(1);
	}
	if (finish_flag == 1) {
		ret = memcmp(readdata, writedata, ADDR_TEST_LEN);
		if (ret == 0)
			printf("Test I2C %d bits addr Pass\n",
		       addr_mode == ADDR_7BITS ? 7 : 10);
	}
	itcs_i2c_exit(slv);
	itcs_i2c_exit(ms);
	return ret;
}

int main(void)
{
    return i2c_test(I2C_CHAN0, I2C_CHAN2, ADDR_7BITS, NORMAL);
}
```

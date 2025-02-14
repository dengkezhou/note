# EEPROM相关接口说明

## 头文件

```c
#include <i2c.h>
#include <eeprom.h>
```

## 接口说明

* eeprom绑定具体i2c控制器
```c
eeprom_dev_t *itcs_eeprom_attach_i2c(char *name, i2c_chan index, i2c_addr_mode addr_mode, i2c_speed_mode speed);
```

参数/返回值列表:

|参数名|参数说明|
|--|--|
|name|eeprom型号名|
|index|i2c控制器号，见itcs_i2c_note_v1.0.md|
|addr_mode|地址模式，见itcs_i2c_note_v1.0.md|
|speed|传输速度，见itcs_i2c_note_v1.0.md|

|返回值|返回值说明|
|--|--|
|!NULL|成功|
|NULL|失败|


* eeprom写

```c
int itcs_eeprom_write(eeprom_dev_t *dev, unsigned int addr, unsigned char *buf, int len);
```

参数/返回值列表:

| 参数名 | 参数说明                     |
| ------ | ---------------------------- |
| dev    | 由itcs_eeprom_attach_i2c获得 |
| addr   | 绝对地址                     |
| buf    | 要写入数据首地址             |
| len    | 要写入数据长度               |

| 返回值 | 返回值说明 |
| ------ | ---------- |
| 0      | 写成功     |
| -1     | 写失败     |


* eeprom读

```c
int itcs_eeprom_read(eeprom_dev_t *dev, unsigned int addr, unsigned char *buf, int len);
```

参数/返回值列表:
|参数名|参数说明|
|--|--|
|dev|由itcs_eeprom_attach_i2c获得|
|addr|绝对地址|
|buf|要写入数据首地址|
|len|要写入数据长度|

|返回值|返回值说明|
|--|--|
|0|读成功|
|-1|读失败|

* eeprom与i2c控制器解绑

```c
void itcs_eeprom_deattach_i2c(eeprom_dev_t *dev);
```

参数/返回值列表:
|参数名|参数说明|
|--|--|
|dev|由itcs_eeprom_attach_i2c获得|


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
#include <eeprom.h>

#define ADDR_TEST_LEN 12

uint8_t readdata[ADDR_TEST_LEN] = { 0 }, writedata[ADDR_TEST_LEN] = { 0 };

static int e2prom_test(void)
{
	int ret;
	eeprom_dev_t *dev;
	unsigned int addr = 0x8;

	printf("test len: %d\n", ADDR_TEST_LEN);

	dev = itcs_eeprom_attach_i2c(MICRO_24AA08_NAME, I2C_CHAN1, ADDR_7BITS, NORMAL);
	if (!dev) {
                printf("eeprom attach failed\n");
                return -1;
        }

	for (int i = 0; i < ADDR_TEST_LEN; i++) {
		writedata[i] = i;
		printf("0x%x ", writedata[i]);
	}
	printf("\n");

	ret = itcs_eeprom_write(dev, addr, writedata, ADDR_TEST_LEN);
	if (ret == -1) {
		printf("eeprom write failed\n");
		return -1;
	}
	ret = itcs_eeprom_read(dev, addr, readdata, ADDR_TEST_LEN);
	if (ret == -1) {
                printf("eeprom read failed\n");
                return -1;
        }
	for (int i = 0; i < ADDR_TEST_LEN; i++) {
		printf("0x%x ", readdata[i]);
	}
	printf("\n");
	ret = memcmp(readdata, writedata, ADDR_TEST_LEN);
	if (ret == 0) {
		printf("i2c eeprom test pass\n");
	} else {
		printf("i2c eeprom test failed\n");
		ret = -1;
	}

	itcs_eeprom_deattach_i2c(dev);
	return ret;
}

int main(void)
{
    return e2prom_test();
}
```

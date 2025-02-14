# ETH相关公共接口说明

## 头文件

```c
#include <eth.h>
```

## 相关数据结构
```c

typedef enum { ETH0 = 0, ETH1 = 1 } eth_id;

typedef enum {
	ETH_MODE_NORMAL,
	ETH_MODE_LOCAL_LOOPBACK,
	ETH_MODE_SERDES_LOOPBACK
} eth_mode;

typedef enum { ETH_SPEED_10M, ETH_SPEED_100M, ETH_SPEED_1000M } eth_speed;

typedef enum { ETH_HALF_DUPLEX, ETH_FULL_DUPLEX } duplex_mode;

typedef enum { ETH_RGMII, ETH_RMII } eth_interface;

typedef struct {
	eth_id id;
	eth_speed speed; /* 10/100/1000, must be ETH_SPEED_xx */
	eth_mode mode; /* normal or loopback */
	duplex_mode duplex;
	bool jumbo_en; /* giant frame support */
	bool auto_nego_en;
	eth_interface interface;
	bool enable_emac;
	/* phy loopback for rgmii phase modulation. */
	bool phy_loopback;
	bool ext_ref_clk;
	bool phy_enable_wol;
} eth_config;

```

## 接口说明

* ETH初始化
	```c 
	eth_device *itcs_eth_init(eth_config *config);
	```
	|参数|说明|
	|--|--|
	|config| 初始化结构体，见上述结构体描述|
	
	|返回值|说明|
	|--|--|
	|NULL|初始化失败|
	|!NULL|初始化成功|
	
* ETH MAC地址设置
	```c 
	int itcs_eth_set_mac_addr(eth_device *dev, mac_addr *addr);
	```
	|参数|说明|
	|--|--|
	|dev| 以太网句柄|
	| addr        | MAC地址结构体指针|
	
	|返回值|说明|
	|--|--|
	|0|设置成功|
	|-1|设置失败|
	
* ETH MAC地址获取
	```c 
	mac_addr *itcs_eth_get_mac_addr(eth_device *dev);
	```
	|参数|说明|
	|--|--|
	|dev| 以太网句柄|
	
	|返回值|说明|
	|--|--|
	|NULL|获取失败|
	|!NULL|获取成功，返回MAC地址结构体指针|
	
* ETH MAC地址过滤设置
	```c 
	int itcs_eth_filter_mac_addr(eth_device *dev, mac_addr *addr, filter_type type, bool enable);
	```
	|参数|说明|
	|--|--|
	|dev| 以太网句柄|
	|addr| 要过滤的MAC地址结构体指针|
	|type|源地址过滤（ETH_FILTER_SRC）或目的地址过滤（ETH_FILTER_DES）|
	|enable| ETH_FILTER_ENABLE表示使能过滤，ETH_FILTER_DISABLE表示关闭过滤 |
	
	|返回值|说明|
	|--|--|
	| 0      | 设置过滤成功 |
	| -1     | 设置过滤失败 |
	
* ETH去初始化
	```c 
	void itcs_eth_exit(eth_device *dev);
	```
	|参数|说明|
	|--|--|
	|dev| 以太网句柄|
	
* ETH发送
	```c 
	int itcs_eth_send(eth_device *dev, unsigned char *buf, unsigned int size,
  		      unsigned char is_block);	
	```
	|参数|说明|
	|--|--|
	|dev| 以太网句柄|
	|buf| 发送buffer地址|
	|size| 发送buffer长度|
	|is_block| 是否阻塞发送|
	
	|返回值|说明|
	|--|--|
	| 0      | 非阻塞模式下立即返回0；阻塞模式下接收成功返回0 |
	| -1     | 发送失败                                       |
	
* ETH接收
	```c 
	int itcs_eth_recv(eth_device *dev, unsigned char *buf, unsigned int size,
  		     unsigned char is_block);	
	```
	|参数|说明|
	|--|--|
	|dev| 以太网句柄|
	|buf| 接收buffer地址|
	|size| 接收buffer长度|
	|is_block| 是否阻塞接收，可选NONBLOCK或BLOCK |
	
	|返回值|说明|
	|--|--|
	| 0      | 非阻塞模式下立即返回0；阻塞模式下接收成功返回0 |
	| -1     | 接收失败                                       |
	
* ETH接收或发送是否完成

	```c 
	eth_status itcs_eth_is_completed(eth_device *dev, eth_check check);
	```
	|参数|说明|
	|--|--|
	|dev| 以太网句柄|
	|check|传入ETH_RX_CHECK或ETH_TX_CHECK|
	
	|返回值|说明|
	|--|--|
	| 0        | 传输中 |
	| 1        | 传输完成 |
	| -1 | 传输失败 |
	
* PHY初始化

	```c 
	int itcs_eth_phy_init(eth_device *dev);
	```
	|参数|说明|
	|--|--|
	|dev| 以太网句柄 |

	|返回值|说明|
	|--|--|
	| 0      | 初始化成功 |
	| -1     | 初始化失败 |

## 示例代码
```c 
#include <common.h>
#include <command.h>
#include <testbench.h>
#include <malloc.h>
#include <eth.h>
#include <getopt.h>

#ifdef CONFIG_COMPILE_FPGA
#define ETH_TEST_LEN 1500
#elif defined(CONFIG_COMPILE_RTL)
#define ETH_TEST_LEN 48
#endif

static int eth_loopback_test(eth_id id)
{
	eth_config config_0 = { ETH0,
				ETH_SPEED_1000M,
				ETH_MODE_LOCAL_LOOPBACK,
				ETH_FULL_DUPLEX,
				ETH_JUMBO_DISABLE,
				ETH_AUTO_NEGOTIATION_DISABLE,
				ETH_RGMII,
				ETH_EMAC_DISABLE,
				PHY_LOOPBACK_DISABLE,
				RMII_INT_REF_CLK,
				PHY_WOL_DISABLE };
	eth_config config_1 = { ETH1,
				ETH_SPEED_1000M,
				ETH_MODE_LOCAL_LOOPBACK,
				ETH_FULL_DUPLEX,
				ETH_JUMBO_DISABLE,
				ETH_AUTO_NEGOTIATION_DISABLE,
				ETH_RGMII,
				ETH_EMAC_DISABLE,
				PHY_LOOPBACK_DISABLE,
				RMII_INT_REF_CLK,
				PHY_WOL_DISABLE };
	eth_config *config;
	eth_device *dev;
	int i, ret;
	unsigned char *rx_buf = NULL;
	unsigned char *tx_buf = NULL;

	rx_buf = malloc(ETH_TEST_LEN);
	tx_buf = malloc(ETH_TEST_LEN);
	if (!rx_buf || !tx_buf) {
		printf("malloc failed!\n");
		return -1;
	}
	memset(rx_buf, 0, ETH_TEST_LEN);
	memset(tx_buf, 0, ETH_TEST_LEN);

	printf("eth loopback test\n");
	printf("test len: %d\n", ETH_TEST_LEN);

	for (i = 0; i < ETH_TEST_LEN; i++)
		tx_buf[i] = i;

	if (id == ETH0) {
		config = &config_0;
	} else if (id == ETH1) {
		config = &config_1;
	} else {
		printf("param error\n");
		return -1;
	}

	dev = itcs_eth_init(config);
	if (!dev) {
		printf("eth init failed!\n");
		return -1;
	}

	itcs_eth_recv(dev, rx_buf, ETH_TEST_LEN, NONBLOCK);
	itcs_eth_send(dev, tx_buf, ETH_TEST_LEN, NONBLOCK);

	while (1) {
		if (itcs_eth_is_completed(dev, ETH_RX_CHECK)) {
			if (!memcmp(tx_buf, rx_buf, ETH_TEST_LEN)) {
				printf("Test ETH loopback Pass\n");
				ret = 0;
				goto exit;
			} else {
				printf("Test ETH loopback Failed!\n");
				ret = -1;
				goto exit;
			}
		}
	}
exit:
	itcs_eth_exit(dev);
	free(rx_buf);
	free(tx_buf);
	return ret;
}

int eth_main(int argc, char *argv[])
{
    return eth_loopback_test(0);
}

```

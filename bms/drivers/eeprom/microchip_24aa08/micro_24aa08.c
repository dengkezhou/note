#include <common.h>
#include <malloc.h>
#include <irq.h>
#include <asm/io.h>
#include <linux/err.h>
#include <pads.h>
#include <i2c.h>
#include <eeprom.h>

static int get_access_addr(eeprom_dev_t *dev, unsigned int addr)
{
	return MICRO_24AA08_ADDR_MASK | addr / dev->id->block_size;
}

static int get_offset(eeprom_dev_t *dev, int addr)
{
	return (addr - addr / dev->id->block_size * dev->id->block_size);
}

int itcs_eeprom_read(eeprom_dev_t *dev, unsigned int addr, unsigned char *buf, int len)
{
	int ret;
	unsigned int dev_addr, offset;
	unsigned char reg;
	i2c_msg_t rx_msg[2];

	dev_addr = get_access_addr(dev, addr);
	offset = get_offset(dev, addr);

	reg = offset;
	rx_msg[0].addr = dev_addr;
	rx_msg[0].flags = CDNS_I2C_WRITE;
	rx_msg[0].buf = &reg;
	rx_msg[0].len = 1;
	rx_msg[1].addr = dev_addr;
	rx_msg[1].flags = CDNS_I2C_READ;
	rx_msg[1].buf = buf;
	rx_msg[1].len = len;
	ret = itcs_i2c_transfer(dev->i2c_dev, rx_msg, 2);
	if(ret == -1) {
		printf("eeprom transfer read failed!\n");
		ret = -1;
	}
	return ret;
}

static int eeprom_page_write(eeprom_dev_t *dev, unsigned int addr, unsigned char *buf, int len)
{
	int ret;
	unsigned int dev_addr, offset;
	unsigned char *trans_buf;
	i2c_msg_t tx_msg;

	if (len > dev->id->page_size) {
		printf("beyond page size\n");
		return -1;
	}

	dev_addr = get_access_addr(dev, addr);
	offset = get_offset(dev, addr);

	trans_buf = (unsigned char *)malloc(len + 1);
	if (!trans_buf)
		return -1;

	*trans_buf = offset;
	memcpy(trans_buf + 1, buf, len);
	tx_msg.addr = dev_addr;
	tx_msg.flags = CDNS_I2C_WRITE;
	tx_msg.buf = trans_buf;
	tx_msg.len = len + 1;
	ret = itcs_i2c_transfer(dev->i2c_dev, &tx_msg, 1);
	if(ret == -1) {
		printf("eeprom transfer write failed!\n");
		goto err;
	}

	udelay(10000);
	
#if 0
	itcs_i2c_slv_mon_config(dev->i2c_dev, dev_addr, 3);
	while (1) {
		udelay(10);
		if (itcs_i2c_slv_mon_is_rdy(dev->i2c_dev))
			break;
	}
#endif

err:
	free(trans_buf);
	return ret;
}

int itcs_eeprom_write(eeprom_dev_t *dev, unsigned int addr, unsigned char *buf, int len)
{
	int ret, i = 0;
	unsigned int avail_in_page, left_data, page_cnt, offset;

	if (len > dev->id->capacity) {
		printf("beyond eeprom capacity size\n");
                return -1;
        }

	avail_in_page = dev->id->page_size - addr % dev->id->page_size;
	if (len < avail_in_page) {
		ret = eeprom_page_write(dev, addr, buf, len);
		if (ret == -1) {
			printf("eeprom one page write failed!\n");
			return -1;
		}
	} else {
		ret = eeprom_page_write(dev, addr, buf, avail_in_page);
		if (ret == -1) {
			printf("eeprom page available write failed!\n");
			return -1;
		}
		left_data = len - avail_in_page;
		page_cnt = left_data / dev->id->page_size;
		while (page_cnt-- > 0) {
			offset = avail_in_page + dev->id->page_size * i;
			ret = eeprom_page_write(dev, addr + offset, buf + offset, dev->id->page_size);
			i++;
			if (ret == -1) {
				printf("eeprom page write failed\n");
				return -1;
			}
		}

		offset = avail_in_page + dev->id->page_size * i;
		if (left_data % dev->id->page_size != 0) {
			ret = eeprom_page_write(dev, addr + offset, buf + offset, left_data % dev->id->page_size);
			if (ret == -1) {
				printf("eeprom page left part write failed\n");
				return -1;
			}
		}
	}
	return ret;
}

eeprom_dev_t *itcs_eeprom_attach_i2c(char *name, i2c_chan index, i2c_addr_mode addr_mode,
		       i2c_speed_mode speed)
{
	int i;
	eeprom_dev_t *dev;
	dev = (eeprom_dev_t *)malloc(sizeof(eeprom_dev_t));
	if (!dev)
		goto err;
	memset(dev, 0, sizeof(eeprom_dev_t));

	strcpy(dev->compatible, name);
	for (i = 0; i < MAX_SUPPORT_ID_NUM; i++) {
		if (!strncmp(dev->compatible, eeprom_id[i].name, strlen(dev->compatible)))
			dev->id = &eeprom_id[i];
	}
	if (dev->id == NULL) {
                printf("eeprom find failed, don't support this eeprom!\n");
                goto err_attach;
        }

	dev->i2c_dev = itcs_i2c_init(index, I2C_MASTER, addr_mode, 0, speed);
	if (!dev->i2c_dev) {
		printf("eeprom i2c attach failed\n");
		goto err_attach;
	}
	return dev;
err_attach:
	free(dev);
err:
	return NULL;
}

void itcs_eeprom_deattach_i2c(eeprom_dev_t *dev)
{
	if (dev) {
		itcs_i2c_exit(dev->i2c_dev);
		free(dev);
		dev = NULL;
	}
}

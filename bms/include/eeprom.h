#ifndef __EEPROM_H__
#define __EEPROM_H__

#define MICRO_24AA08_NAME "micro_24aa08"
#define MICRO_24AA08_PAGE_SIZE 8
#define MICRO_24AA08_BLOCK_SIZE 256
#define MICRO_24AA08_CAPCITY_SIZE 1024
#define MICRO_24AA08_ADDR_MASK 0x50

#define COMPATIBLE_LEN 16
#define MAX_SUPPORT_ID_NUM 16

typedef struct eeprom_id_table {
	char name[COMPATIBLE_LEN];
	unsigned int page_size;
	unsigned int block_size;
	unsigned int capacity;
} eeprom_id_table_t;

extern eeprom_id_table_t eeprom_id[MAX_SUPPORT_ID_NUM];

typedef struct eeprom_dev {
	char compatible[16];
	i2c_dev_t *i2c_dev;
	eeprom_id_table_t *id;
} eeprom_dev_t;

eeprom_dev_t *itcs_eeprom_attach_i2c(char *name, i2c_chan index, i2c_addr_mode addr_mode,
		       i2c_speed_mode speed);
int itcs_eeprom_write(eeprom_dev_t *dev, unsigned int addr, unsigned char *buf, int len);
int itcs_eeprom_read(eeprom_dev_t *dev, unsigned int addr, unsigned char *buf, int len);
void itcs_eeprom_deattach_i2c(eeprom_dev_t *dev);
#endif

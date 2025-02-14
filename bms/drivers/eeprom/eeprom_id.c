#include <common.h>
#include <malloc.h>
#include <irq.h>
#include <asm/io.h>
#include <linux/err.h>
#include <pads.h>
#include <i2c.h>
#include <eeprom.h>

eeprom_id_table_t eeprom_id[MAX_SUPPORT_ID_NUM] = {
	{
		.name = MICRO_24AA08_NAME, 
		.page_size = MICRO_24AA08_PAGE_SIZE,
		.block_size = MICRO_24AA08_BLOCK_SIZE,
		.capacity = MICRO_24AA08_CAPCITY_SIZE
	}
};

/*
 * Driver for power monitor chip
 */

#include <common.h>
#include <malloc.h>
#include <irq.h>
#include <asm/io.h>
#include <linux/err.h>
#include <pads.h>
#include <i2c.h>
#include <irq.h>
#include <asm/bits.h>
#include <pmic.h>
#include <stdbool.h>
#include <hwmon.h>

#include "ina226.h"

static struct hwmon_dev *hwmondev[MAX_HWMON_VARIANTS];
static unsigned int init_flag;

struct hwmon_ids {
	char name[16];
	int (* init)(struct hwmon_dev *hwmondev);
};

static int is_inited(unsigned int hwmon_id){
	return init_flag & BIT(hwmon_id);
}

struct hwmon_ids hwmon_table[] = {
	{ .name = "ina226", .init = ina226_init },
	{/* other module*/},
};

int itsc_hwmon_init(unsigned int hwmon_id){
	struct hwmon_dev *dev;
	int ret;

	if(is_inited(hwmon_id))
		return 0;

	hwmondev[hwmon_id] = malloc(sizeof(*dev));
	memset(hwmondev[hwmon_id], 0, sizeof(*dev));

	ret = hwmon_table[hwmon_id].init(hwmondev[hwmon_id]);
	if(ret < 0)
		return -1;
	init_flag |= BIT(hwmon_id);

	return 0;
}

struct hwmon_sub *itcs_hwmon_get(unsigned int hwmon_id, const char *name){
	int i;

	for(i = 0; i < hwmondev[hwmon_id]->nsub; i++){
		if(!strcmp(hwmondev[hwmon_id]->sub[i]->name, name))
			return hwmondev[hwmon_id]->sub[i];
	}

	printf("no hwmon %s find\n", name);
	return NULL;
}

int itcs_hwmon_get_shunt_voltage(struct hwmon_sub *hwmonsub){
	return hwmonsub->hwmondev->ops->get_shunt_voltage(hwmonsub);
}

int itcs_hwmon_get_bus_voltage(struct hwmon_sub *hwmonsub){
	return hwmonsub->hwmondev->ops->get_bus_voltage(hwmonsub);
}

int itcs_hwmon_get_power(struct hwmon_sub *hwmonsub){
	return hwmonsub->hwmondev->ops->get_power(hwmonsub);
}

int itcs_hwmon_get_current(struct hwmon_sub *hwmonsub){
	return hwmonsub->hwmondev->ops->get_current(hwmonsub);
}

int itcs_hwmon_print_all_info(unsigned int hwmon_id){
	int i;
	int shunt[16], bus[16], current[16], power[16];
	
	itsc_hwmon_init(hwmon_id);

    unsigned long t;
    t = get_timer_us(0);

	for(i = 0; i < hwmondev[hwmon_id]->nsub; i++)
	//for(i = 0; i < 1; i++) 
	{
		shunt[i]   = itcs_hwmon_get_shunt_voltage(hwmondev[hwmon_id]->sub[i]);
		bus[i]     = itcs_hwmon_get_bus_voltage(hwmondev[hwmon_id]->sub[i]);
		current[i] = itcs_hwmon_get_current(hwmondev[hwmon_id]->sub[i]);
		power[i]   = itcs_hwmon_get_power(hwmondev[hwmon_id]->sub[i]);
	}

	t = get_timer_us(t);
	printf("12 time = %ld us\n", t);

	printf("%-15s %-25s %-25s %-10s %-20s\n", "Name", "Shunt Voltage/mV", "Bus Voltage/mV", "Current/mA", "power/uW");
	printf("-------------------------------------------------------------------------------\n");
	for(i = 0; i < hwmondev[hwmon_id]->nsub; i++) {
		printf("%-15s %-25d %-15d %-10d %-20d\n", hwmondev[hwmon_id]->sub[i]->name,
			shunt[i],
			bus[i],
			current[i],
			power[i]);
	}

	return 0;
}


#define  TEST_CNT 30
int itcs_hwmon_print_one_info(unsigned int hwmon_id, unsigned int sub_id){
	int i;
	int shunt[TEST_CNT + 1], bus[TEST_CNT + 1], current[TEST_CNT + 1], power[TEST_CNT + 1];
	
	itsc_hwmon_init(hwmon_id);

    unsigned long t;
    t = get_timer_us(0);

    shunt[TEST_CNT] = 0;
    bus[TEST_CNT] = 0;
    current[TEST_CNT] = 0;
    power[TEST_CNT] = 0;

	for(i = 0; i < TEST_CNT; i++)
	{
		shunt[i]   = itcs_hwmon_get_shunt_voltage(hwmondev[hwmon_id]->sub[sub_id]);
		bus[i]     = itcs_hwmon_get_bus_voltage(hwmondev[hwmon_id]->sub[sub_id]);
		current[i] = itcs_hwmon_get_current(hwmondev[hwmon_id]->sub[sub_id]);
		power[i]   = itcs_hwmon_get_power(hwmondev[hwmon_id]->sub[sub_id]);
	}

	t = get_timer_us(t);
	printf("12 time = %ld us\n", t);

	printf("%-15s %-25s %-25s %-10s %-20s\n", "Name", "Shunt Voltage/mV", "Bus Voltage/mV", "Current/mA", "power/uW");
	printf("-------------------------------------------------------------------------------\n");
	
	for(i = 0; i < TEST_CNT; i++) {
		printf("%-15s %-25d %-15d %-10d %-20d\n", hwmondev[hwmon_id]->sub[sub_id]->name,
			shunt[i],
			bus[i],
			current[i],
			power[i]);

		shunt[TEST_CNT] += shunt[i];
		bus[TEST_CNT] += bus[i];
		current[TEST_CNT] += current[i];
		power[TEST_CNT] += power[i];
	}

	printf("%-15s %-25d %-15d %-10d %-20d\n", hwmondev[hwmon_id]->sub[sub_id]->name,
		shunt[TEST_CNT] / TEST_CNT,
		bus[TEST_CNT] / TEST_CNT,
		current[TEST_CNT] / TEST_CNT,
		power[TEST_CNT] / TEST_CNT);

	return 0;
}
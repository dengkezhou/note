#ifndef __HWMON_H__
#define __HWMON_H__

enum hwmon_variants {
	INA226_ID = 0,
	MAX_HWMON_VARIANTS,
};

struct hwmon_i2c {
	i2c_dev_t *i2c_dev;
	int addr;
	int bus;
};

struct hwmon_sub;

struct hwmon_ops {
	int (*get_shunt_voltage)(struct hwmon_sub *hwmonsub);
	int (*get_bus_voltage)(struct hwmon_sub *hwmonsub);
	int (*get_power)(struct hwmon_sub *hwmonsub);
	int (*get_current)(struct hwmon_sub *hwmonsub);
};

struct hwmon_dev{
	const char *name;
	unsigned int id;

	struct hwmon_sub **sub;
	uint32_t nsub;

	struct hwmon_ops *ops;
};

struct hwmon_sub{
	struct hwmon_dev *hwmondev;

	char *name;
	uint8_t id;

	/*i2c config*/
	i2c_dev_t *i2c_dev;
	uint8_t i2c_addr;
	uint8_t i2c_bus;

	const struct ina2xx_config *config;

	long rshunt;
	long current_lsb_uA;
	long power_lsb_uW;
};

int itsc_hwmon_init(unsigned int hwmon_id);
struct hwmon_sub *itcs_hwmon_get(unsigned int hwmon_id, const char *name);
int itcs_hwmon_get_shunt_voltage(struct hwmon_sub *hwmonsub);
int itcs_hwmon_get_bus_voltage(struct hwmon_sub *hwmonsub);
int itcs_hwmon_get_power(struct hwmon_sub *hwmonsub);
int itcs_hwmon_get_current(struct hwmon_sub *hwmonsub);
int itcs_hwmon_print_all_info(unsigned int hwmon_id);

#endif

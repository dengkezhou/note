/*
 * Driver for Texas Instruments INA226 power monitor chip
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

/* common register definitions */
#define INA2XX_CONFIG			0x00
#define INA2XX_SHUNT_VOLTAGE		0x01 /* readonly */
#define INA2XX_BUS_VOLTAGE		0x02 /* readonly */
#define INA2XX_POWER			0x03 /* readonly */
#define INA2XX_CURRENT			0x04 /* readonly */
#define INA2XX_CALIBRATION		0x05

/* register count */
#define INA226_REGISTERS		8

#define INA2XX_MAX_REGISTERS		8

#define SHUNT_RESISTOR 5000 //uohms

/* settings - depend on use case */
#define INA226_CONFIG_DEFAULT		0x4325	/* averages=4 */

#define NUM_MODULES 13

/*
 * Divide positive or negative dividend by positive or negative divisor
 * and round to closest integer. Result is undefined for negative
 * divisors if the dividend variable type is unsigned and for negative
 * dividends if the divisor variable type is unsigned.
 */
#define DIV_ROUND_CLOSEST(x, divisor)(			\
{							\
	typeof(x) __x = x;				\
	typeof(divisor) __d = divisor;			\
	(((typeof(x))-1) > 0 ||				\
	 ((typeof(divisor))-1) > 0 ||			\
	 (((__x) > 0) == ((__d) > 0))) ?		\
		(((__x) + ((__d) / 2)) / (__d)) :	\
		(((__x) - ((__d) / 2)) / (__d));	\
}							\
)

struct ina2xx_config {
	uint16_t config_default;
	int calibration_value;
	int registers;
	int shunt_div;
	int bus_voltage_shift;
	int bus_voltage_lsb;	/* uV */
	int power_lsb_factor;
};

static const struct ina2xx_config ina2xx_config = {
	.config_default = INA226_CONFIG_DEFAULT,
	.calibration_value = 2048,
	.registers = INA226_REGISTERS,
	.shunt_div = 400,
	.bus_voltage_shift = 0,
	.bus_voltage_lsb = 1250,
	.power_lsb_factor = 25,
};

struct submod_info{
	char name[128];
	uint8_t id;
	uint8_t i2c_addr;
	uint8_t i2c_bus;
};

static struct submod_info submodinfo[NUM_MODULES] = {
	[0] = {
		.name = "VDD1_DDR_1P8",
		.id = 0,
		.i2c_addr = 0x40,
		.i2c_bus = 0x2,
	},
	[1] = {
		.name = "VDDQ_DDR_0P6",
		.id = 1,
		.i2c_addr = 0x44,
		.i2c_bus = 0x2,
	},
	[2] = {
		.name = "VDD2_DDR_1P1",
		.id = 2,
		.i2c_addr = 0x41,
		.i2c_bus = 0x2,
	},
	[3] = {
		.name = "VDD_DDR_0P8",
		.id = 3,
		.i2c_addr = 0x45,
		.i2c_bus = 0x2,
	},
	[4] = {
		.name = "VSYS_4P1_S5",
		.id = 4,
		.i2c_addr = 0x47,
		.i2c_bus = 0x2,
	},
	[5] = {
		.name = "VDD_SOC",
		.id = 5,
		.i2c_addr = 0x46,
		.i2c_bus = 0x2,
	},
	[6] = {
		.name = "VSYS_3P3_S3",
		.id = 6,
		.i2c_addr = 0x49,
		.i2c_bus = 0x2,
	},
	[7] = {
		.name = "VSYS_5P0_S0",
		.id = 7,
		.i2c_addr = 0x48,
		.i2c_bus = 0x2,
	},
	[8] = {
		.name = "VSYS_1P8_S0",
		.id = 8,
		.i2c_addr = 0x4c,
		.i2c_bus = 0x2,
	},
	[9] = {
		.name = "VDD_SAP_0P8",
		.id = 9,
		.i2c_addr = 0x4d,
		.i2c_bus = 0x2,
	},
	[10] = {
		.name = "VDD_CPU",
		.id = 10,
		.i2c_addr = 0x45,
		.i2c_bus = 0x1,
	},
	[11] = {
		.name = "VDD_NPU0",
		.id = 11,
		.i2c_addr = 0x46,
		.i2c_bus = 0x1,
	},
	[12] = {
		.name = "VDD_NPU1",
		.id = 12,
		.i2c_addr = 0x47,
		.i2c_bus = 0x1,
	}
};

static struct hwmon_sub *hwmonsub[NUM_MODULES];

static int i2c_read_word(struct hwmon_sub *hwmonsub, uint8_t reg, uint8_t *rbuf){
	i2c_msg_t msg[2];
	int ret;

	if (!hwmonsub)
		return -1;

	msg[0].addr = hwmonsub->i2c_addr;
	msg[0].flags = 0;
	msg[0].buf = &reg;
	msg[0].len = 1;
	msg[1].addr = hwmonsub->i2c_addr;
	msg[1].flags = CDNS_I2C_READ;
	msg[1].buf = rbuf;
	msg[1].len = 2;

	//unsigned long t;
	//t = get_timer_us(0);

	ret = itcs_i2c_transfer(hwmonsub->i2c_dev, msg, 2);
	if (ret < 0) {
		printf("i2c_read_word failed, ret = %d\n", ret);
		return ret;
	}

	//t = get_timer_us(t);
    //printf("itcs_i2c_transfer time = %ld us\n", t);

	return 0;
}

static int i2c_write_word(struct hwmon_sub *hwmonsub, uint8_t reg, uint8_t *val){
	i2c_msg_t msg;
	uint8_t buf[3];
	int ret;

	if (!hwmonsub)
		return -1;

	buf[0] = reg;
	buf[1] = val[0];
	buf[2] = val[1];

	msg.addr = hwmonsub->i2c_addr;
	msg.flags = 0;
	msg.buf = buf;
	msg.len = sizeof(buf);

	ret = itcs_i2c_transfer(hwmonsub->i2c_dev, &msg, 1);
	if (ret < 0) {
		printf("i2c_write_word failed, ret = %d\n", ret);
		return ret;
	}
	
	return 0;
}

static int ina226_get_value(struct hwmon_sub *hwmonsub, uint8_t reg,
			    unsigned int regval)
{
	int val;

	switch (reg) {
	case INA2XX_SHUNT_VOLTAGE:
		/* signed register */
		//val = DIV_ROUND_CLOSEST((int16_t)regval, hwmonsub->config->shunt_div);
		val = regval * 2500;
		break;
	case INA2XX_BUS_VOLTAGE:
		val = (regval >> hwmonsub->config->bus_voltage_shift)
		  * hwmonsub->config->bus_voltage_lsb;
		val = DIV_ROUND_CLOSEST(val, 1000);
		break;
	case INA2XX_POWER:
		val = regval * hwmonsub->power_lsb_uW;
		break;
	case INA2XX_CURRENT:
		/* signed register, result in mA */
		val = (int16_t)regval * hwmonsub->current_lsb_uA;
		//val = DIV_ROUND_CLOSEST(val, 1000);
		break;
	case INA2XX_CALIBRATION:
		val = regval;
		break;
	default:
		/* programmer goofed */
		val = 0;
		break;
	}

	return val;
}

static int ina226_value_show(struct hwmon_sub *hwmonsub, uint8_t reg)
{	uint8_t regval[2];
	unsigned int val;

	int err = i2c_read_word(hwmonsub, reg, regval);
	if (err < 0)
		return err;

	val = regval[0] << 8 | regval[1];
	return ina226_get_value(hwmonsub, reg, val);
}

int ina226_get_shunt_voltage(struct hwmon_sub *hwmonsub){
	return ina226_value_show(hwmonsub, INA2XX_SHUNT_VOLTAGE);
}

int ina226_get_bus_voltage(struct hwmon_sub *hwmonsub){
	return ina226_value_show(hwmonsub, INA2XX_BUS_VOLTAGE);
}

int ina226_get_power(struct hwmon_sub *hwmonsub){
	return ina226_value_show(hwmonsub, INA2XX_POWER);
}

int ina226_get_current(struct hwmon_sub *hwmonsub){
	return ina226_value_show(hwmonsub, INA2XX_CURRENT);
}

static struct hwmon_ops hwmon_ops = {
	.get_shunt_voltage = ina226_get_shunt_voltage,
	.get_bus_voltage = ina226_get_bus_voltage,
	.get_power = ina226_get_power,
	.get_current = ina226_get_current,
};

static int ina266_set_shunt(struct hwmon_sub *hwmonsub, long val){
	unsigned int dividend = DIV_ROUND_CLOSEST(1000000000,
						  hwmonsub->config->shunt_div);
	if (val <= 0 || val > dividend)
		return -EINVAL;

	hwmonsub->rshunt = val;
	hwmonsub->current_lsb_uA = DIV_ROUND_CLOSEST(dividend, val);
	hwmonsub->power_lsb_uW = hwmonsub->config->power_lsb_factor *
			     hwmonsub->current_lsb_uA;


	printf("---value = %d, current_lsb_uA = %d, power_lsb_uW = %d\n",val, 
		hwmonsub->current_lsb_uA, hwmonsub->power_lsb_uW);
	return 0;
}

static int ina266_sub_init(struct hwmon_sub *hwmonsub){
	uint8_t val[2];
	int ret;
	val[0] = hwmonsub->config->config_default >> 8;
	val[1] = hwmonsub->config->config_default;

	ret = i2c_write_word(hwmonsub, INA2XX_CONFIG, val);
	if (ret < 0)
		return ret;


	int calibration_value = 102;
#if 1
	if (hwmonsub->id >= 10)
		calibration_value = 512;
#else
	calibration_value = 2048;

	if (hwmonsub->id >= 10)
		calibration_value = 512;
#endif

	val[0] = calibration_value >> 8;
	val[1] = calibration_value;

	return i2c_write_word(hwmonsub, INA2XX_CALIBRATION, val);
}

/*ina226 init*/
int ina226_init(struct hwmon_dev *hwmondev){
	int i;

	hwmondev->id = INA226_ID;
	hwmondev->name = "ina226";
	hwmondev->sub = hwmonsub;
	hwmondev->nsub = ARRAY_SIZE(hwmonsub);
	hwmondev->ops = &hwmon_ops;

	/*init all sub*/
	for(i = 0; i < NUM_MODULES; i++){
		hwmonsub[i] = malloc(sizeof(struct hwmon_sub));
		memset(hwmonsub[i], 0, sizeof(struct hwmon_sub));

		hwmonsub[i]->hwmondev = hwmondev;

		hwmonsub[i]->name = submodinfo[i].name;
		hwmonsub[i]->id = i;

		hwmonsub[i]->config = &ina2xx_config;

		if( i < 10 )
			ina266_set_shunt(hwmonsub[i], SHUNT_RESISTOR);
		else
			ina266_set_shunt(hwmonsub[i], 4000);

		hwmonsub[i]->i2c_addr = submodinfo[i].i2c_addr;
		hwmonsub[i]->i2c_bus = submodinfo[i].i2c_bus;
		if(i == 0){
			hwmonsub[i]->i2c_dev = itcs_i2c_init(hwmonsub[i]->i2c_bus, I2C_MASTER,
           			ADDR_7BITS, hwmonsub[i]->i2c_addr, I2C_MAX_FAST_MODE_FREQ);
		}else if( i < 10){
			hwmonsub[i]->i2c_dev = hwmonsub[0]->i2c_dev;
		}else if( i == 10 ){
			hwmonsub[i]->i2c_dev = itcs_i2c_init(hwmonsub[i]->i2c_bus, I2C_MASTER,
           			ADDR_7BITS, hwmonsub[i]->i2c_addr, I2C_MAX_FAST_MODE_FREQ);
		}else{
			hwmonsub[i]->i2c_dev = hwmonsub[10]->i2c_dev;
		}

	   	if(!hwmonsub[i]->i2c_dev){
			printf("get i2c client: %s failed!\n",hwmonsub[i]->name);
			continue;
		} else
			ina266_sub_init(hwmonsub[i]);
	}

	return 0;
}

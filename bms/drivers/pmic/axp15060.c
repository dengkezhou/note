/*
 * AXP15060 regulators driver.
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
#include "axp15060.h"

/* AXP15060 I2C BUS ID */
#define AXP15060_I2C_BUS      0

/* AXP15060 I2C address */
#define AXP15060_I2C_ADDR     0x36

#define AXP15060_DCDC1_V_CTRL_MASK		GENMASK(4, 0)
#define AXP15060_DCDC2_V_CTRL_MASK		GENMASK(6, 0)
#define AXP15060_DCDC3_V_CTRL_MASK		GENMASK(6, 0)
#define AXP15060_DCDC4_V_CTRL_MASK		GENMASK(6, 0)
#define AXP15060_DCDC5_V_CTRL_MASK		GENMASK(6, 0)
#define AXP15060_DCDC6_V_CTRL_MASK		GENMASK(4, 0)
#define AXP15060_ALDO1_V_CTRL_MASK		GENMASK(4, 0)
#define AXP15060_ALDO2_V_CTRL_MASK		GENMASK(4, 0)
#define AXP15060_ALDO3_V_CTRL_MASK		GENMASK(4, 0)
#define AXP15060_ALDO4_V_CTRL_MASK		GENMASK(4, 0)
#define AXP15060_ALDO5_V_CTRL_MASK		GENMASK(4, 0)
#define AXP15060_BLDO1_V_CTRL_MASK		GENMASK(4, 0)
#define AXP15060_BLDO2_V_CTRL_MASK		GENMASK(4, 0)
#define AXP15060_BLDO3_V_CTRL_MASK		GENMASK(4, 0)
#define AXP15060_BLDO4_V_CTRL_MASK		GENMASK(4, 0)
#define AXP15060_BLDO5_V_CTRL_MASK		GENMASK(4, 0)
#define AXP15060_CLDO1_V_CTRL_MASK		GENMASK(4, 0)
#define AXP15060_CLDO2_V_CTRL_MASK		GENMASK(4, 0)
#define AXP15060_CLDO3_V_CTRL_MASK		GENMASK(4, 0)
#define AXP15060_CLDO4_V_CTRL_MASK		GENMASK(5, 0)
#define AXP15060_CPUSLDO_V_CTRL_MASK		GENMASK(3, 0)

#define AXP15060_PWR_OUT_DCDC1_MASK	BIT_MASK(0)
#define AXP15060_PWR_OUT_DCDC2_MASK	BIT_MASK(1)
#define AXP15060_PWR_OUT_DCDC3_MASK	BIT_MASK(2)
#define AXP15060_PWR_OUT_DCDC4_MASK	BIT_MASK(3)
#define AXP15060_PWR_OUT_DCDC5_MASK	BIT_MASK(4)
#define AXP15060_PWR_OUT_DCDC6_MASK	BIT_MASK(5)
#define AXP15060_PWR_OUT_ALDO1_MASK	BIT_MASK(0)
#define AXP15060_PWR_OUT_ALDO2_MASK	BIT_MASK(1)
#define AXP15060_PWR_OUT_ALDO3_MASK	BIT_MASK(2)
#define AXP15060_PWR_OUT_ALDO4_MASK	BIT_MASK(3)
#define AXP15060_PWR_OUT_ALDO5_MASK	BIT_MASK(4)
#define AXP15060_PWR_OUT_BLDO1_MASK	BIT_MASK(5)
#define AXP15060_PWR_OUT_BLDO2_MASK	BIT_MASK(6)
#define AXP15060_PWR_OUT_BLDO3_MASK	BIT_MASK(7)
#define AXP15060_PWR_OUT_BLDO4_MASK	BIT_MASK(0)
#define AXP15060_PWR_OUT_BLDO5_MASK	BIT_MASK(1)
#define AXP15060_PWR_OUT_CLDO1_MASK	BIT_MASK(2)
#define AXP15060_PWR_OUT_CLDO2_MASK	BIT_MASK(3)
#define AXP15060_PWR_OUT_CLDO3_MASK	BIT_MASK(4)
#define AXP15060_PWR_OUT_CLDO4_MASK	BIT_MASK(5)
#define AXP15060_PWR_OUT_CPUSLDO_MASK	BIT_MASK(6)
#define AXP15060_PWR_OUT_SW_MASK		BIT_MASK(7)

#define AXP15060_DCDC23_POLYPHASE_DUAL_MASK		BIT_MASK(6)
#define AXP15060_DCDC46_POLYPHASE_DUAL_MASK		BIT_MASK(7)

#define AXP15060_DCDC234_500mV_START	0x00
#define AXP15060_DCDC234_500mV_STEPS	70
#define AXP15060_DCDC234_500mV_END		\
	(AXP15060_DCDC234_500mV_START + AXP15060_DCDC234_500mV_STEPS)
#define AXP15060_DCDC234_1220mV_START	0x47
#define AXP15060_DCDC234_1220mV_STEPS	16
#define AXP15060_DCDC234_1220mV_END		\
	(AXP15060_DCDC234_1220mV_START + AXP15060_DCDC234_1220mV_STEPS)
#define AXP15060_DCDC234_NUM_VOLTAGES	88

#define AXP15060_DCDC5_800mV_START	0x00
#define AXP15060_DCDC5_800mV_STEPS	32
#define AXP15060_DCDC5_800mV_END		\
	(AXP15060_DCDC5_800mV_START + AXP15060_DCDC5_800mV_STEPS)
#define AXP15060_DCDC5_1140mV_START	0x21
#define AXP15060_DCDC5_1140mV_STEPS	35
#define AXP15060_DCDC5_1140mV_END		\
	(AXP15060_DCDC5_1140mV_START + AXP15060_DCDC5_1140mV_STEPS)
#define AXP15060_DCDC5_NUM_VOLTAGES	69

#define AXP_DESC(_family, _id, _match, _supply, _min, _max, _step, _vreg,	\
		 _vmask, _ereg, _emask) 					\
	[_family##_##_id] = {							\
		.name		= (_match),					\
		.supply_name	= (_supply),					\
		.id		= _family##_##_id,				\
		.n_voltages	= (((_max) - (_min)) / (_step) + 1),		\
		.min_uV		= (_min) * 1000,				\
		.max_uV		= (_max) * 1000,				\
		.uV_step	= (_step) * 1000,				\
		.vsel_reg	= (_vreg),					\
		.vsel_mask	= (_vmask),					\
		.enable_reg	= (_ereg),					\
		.enable_mask	= (_emask),					\
	}

#define AXP_DESC_RANGES(_family, _id, _match, _supply, _ranges, _n_voltages,	\
			_vreg, _vmask, _ereg, _emask)				\
	[_family##_##_id] = {							\
		.name		= (_match),					\
		.supply_name	= (_supply),					\
		.id		= _family##_##_id,				\
		.n_voltages	= (_n_voltages),				\
		.vsel_reg	= (_vreg),					\
		.vsel_mask	= (_vmask),					\
		.enable_reg	= (_ereg),					\
		.enable_mask	= (_emask),					\
		.linear_ranges	= (_ranges),					\
		.n_linear_ranges = ARRAY_SIZE(_ranges),				\
	}

#define AXP_DESC_SW(_family, _id, _match, _supply, _ereg, _emask)		\
	[_family##_##_id] = {							\
		.name		= (_match),					\
		.supply_name	= (_supply),					\
		.id		= _family##_##_id,				\
		.enable_reg	= (_ereg),					\
		.enable_mask	= (_emask),					\
	}

#define AXP_DESC_FIXED(_family, _id, _match, _supply, _volt)			\
	[_family##_##_id] = {							\
		.name		= (_match),					\
		.supply_name	= (_supply),					\
		.id		= _family##_##_id,				\
		.n_voltages	= 1,						\
		.min_uV		= (_volt) * 1000,				\
	}

static const struct linear_range axp15060_dcdc234_ranges[] = {
	REGULATOR_LINEAR_RANGE(500000,
			       AXP15060_DCDC234_500mV_START,
			       AXP15060_DCDC234_500mV_END,
			       10000),
	REGULATOR_LINEAR_RANGE(1220000,
			       AXP15060_DCDC234_1220mV_START,
			       AXP15060_DCDC234_1220mV_END,
			       20000),
};

static const struct linear_range axp15060_dcdc5_ranges[] = {
	REGULATOR_LINEAR_RANGE(800000,
			       AXP15060_DCDC5_800mV_START,
			       AXP15060_DCDC5_800mV_END,
			       10000),
	REGULATOR_LINEAR_RANGE(1140000,
			       AXP15060_DCDC5_1140mV_START,
			       AXP15060_DCDC5_1140mV_END,
			       20000),
};

static const struct regulator_desc axp15060_regulators[] = {
	AXP_DESC(AXP15060, DCDC1, "dcdc1", "vin1", 1500, 3400, 100,
		 AXP15060_DCDC1_V_CTRL, AXP15060_DCDC1_V_CTRL_MASK,
		 AXP15060_PWR_OUT_CTRL1, AXP15060_PWR_OUT_DCDC1_MASK),
	AXP_DESC_RANGES(AXP15060, DCDC2, "dcdc2", "vin2",
			axp15060_dcdc234_ranges, AXP15060_DCDC234_NUM_VOLTAGES,
			AXP15060_DCDC2_V_CTRL, AXP15060_DCDC2_V_CTRL_MASK,
			AXP15060_PWR_OUT_CTRL1, AXP15060_PWR_OUT_DCDC2_MASK),
	AXP_DESC_RANGES(AXP15060, DCDC3, "dcdc3", "vin3",
			axp15060_dcdc234_ranges, AXP15060_DCDC234_NUM_VOLTAGES,
			AXP15060_DCDC3_V_CTRL, AXP15060_DCDC3_V_CTRL_MASK,
			AXP15060_PWR_OUT_CTRL1, AXP15060_PWR_OUT_DCDC3_MASK),
	AXP_DESC_RANGES(AXP15060, DCDC4, "dcdc4", "vin4",
			axp15060_dcdc234_ranges, AXP15060_DCDC234_NUM_VOLTAGES,
			AXP15060_DCDC4_V_CTRL, AXP15060_DCDC4_V_CTRL_MASK,
			AXP15060_PWR_OUT_CTRL1, AXP15060_PWR_OUT_DCDC4_MASK),
	AXP_DESC_RANGES(AXP15060, DCDC5, "dcdc5", "vin5",
			axp15060_dcdc5_ranges, AXP15060_DCDC5_NUM_VOLTAGES,
			AXP15060_DCDC5_V_CTRL, AXP15060_DCDC5_V_CTRL_MASK,
			AXP15060_PWR_OUT_CTRL1, AXP15060_PWR_OUT_DCDC5_MASK),
	AXP_DESC(AXP15060, DCDC6, "dcdc6", "vin6", 500, 3400, 100,
		 AXP15060_DCDC6_V_CTRL, AXP15060_DCDC6_V_CTRL_MASK,
		 AXP15060_PWR_OUT_CTRL1, AXP15060_PWR_OUT_DCDC6_MASK),
	AXP_DESC(AXP15060, ALDO1, "aldo1", "aldoin", 700, 3300, 100,
		 AXP15060_ALDO1_V_CTRL, AXP15060_ALDO1_V_CTRL_MASK,
		 AXP15060_PWR_OUT_CTRL2, AXP15060_PWR_OUT_ALDO1_MASK),
	AXP_DESC(AXP15060, ALDO2, "aldo2", "aldoin", 700, 3300, 100,
		 AXP15060_ALDO2_V_CTRL, AXP15060_ALDO2_V_CTRL_MASK,
		 AXP15060_PWR_OUT_CTRL2, AXP15060_PWR_OUT_ALDO2_MASK),
	AXP_DESC(AXP15060, ALDO3, "aldo3", "aldoin", 700, 3300, 100,
		 AXP15060_ALDO3_V_CTRL, AXP15060_ALDO3_V_CTRL_MASK,
		 AXP15060_PWR_OUT_CTRL2, AXP15060_PWR_OUT_ALDO3_MASK),
	AXP_DESC(AXP15060, ALDO4, "aldo4", "aldoin", 700, 3300, 100,
		 AXP15060_ALDO4_V_CTRL, AXP15060_ALDO4_V_CTRL_MASK,
		 AXP15060_PWR_OUT_CTRL2, AXP15060_PWR_OUT_ALDO4_MASK),
	AXP_DESC(AXP15060, ALDO5, "aldo5", "aldoin", 700, 3300, 100,
		 AXP15060_ALDO5_V_CTRL, AXP15060_ALDO5_V_CTRL_MASK,
		 AXP15060_PWR_OUT_CTRL2, AXP15060_PWR_OUT_ALDO5_MASK),
	AXP_DESC(AXP15060, BLDO1, "bldo1", "bldoin", 700, 3300, 100,
		 AXP15060_BLDO1_V_CTRL, AXP15060_BLDO1_V_CTRL_MASK,
		 AXP15060_PWR_OUT_CTRL2, AXP15060_PWR_OUT_BLDO1_MASK),
	AXP_DESC(AXP15060, BLDO2, "bldo2", "bldoin", 700, 3300, 100,
		 AXP15060_BLDO2_V_CTRL, AXP15060_BLDO2_V_CTRL_MASK,
		 AXP15060_PWR_OUT_CTRL2, AXP15060_PWR_OUT_BLDO2_MASK),
	AXP_DESC(AXP15060, BLDO3, "bldo3", "bldoin", 700, 3300, 100,
		 AXP15060_BLDO3_V_CTRL, AXP15060_BLDO3_V_CTRL_MASK,
		 AXP15060_PWR_OUT_CTRL2, AXP15060_PWR_OUT_BLDO3_MASK),
	AXP_DESC(AXP15060, BLDO4, "bldo4", "bldoin", 700, 3300, 100,
		 AXP15060_BLDO4_V_CTRL, AXP15060_BLDO4_V_CTRL_MASK,
		 AXP15060_PWR_OUT_CTRL3, AXP15060_PWR_OUT_BLDO4_MASK),
	AXP_DESC(AXP15060, BLDO5, "bldo5", "bldoin", 700, 3300, 100,
		 AXP15060_BLDO5_V_CTRL, AXP15060_BLDO5_V_CTRL_MASK,
		 AXP15060_PWR_OUT_CTRL3, AXP15060_PWR_OUT_BLDO5_MASK),
	AXP_DESC(AXP15060, CLDO1, "cldo1", "cldoin", 700, 3300, 100,
		 AXP15060_CLDO1_V_CTRL, AXP15060_CLDO1_V_CTRL_MASK,
		 AXP15060_PWR_OUT_CTRL3, AXP15060_PWR_OUT_CLDO1_MASK),
	AXP_DESC(AXP15060, CLDO2, "cldo2", "cldoin", 700, 3300, 100,
		 AXP15060_CLDO2_V_CTRL, AXP15060_CLDO2_V_CTRL_MASK,
		 AXP15060_PWR_OUT_CTRL3, AXP15060_PWR_OUT_CLDO2_MASK),
	AXP_DESC(AXP15060, CLDO3, "cldo3", "cldoin", 700, 3300, 100,
		 AXP15060_CLDO3_V_CTRL, AXP15060_CLDO3_V_CTRL_MASK,
		 AXP15060_PWR_OUT_CTRL3, AXP15060_PWR_OUT_CLDO3_MASK),
	AXP_DESC(AXP15060, CLDO4, "cldo4", "cldoin", 700, 4200, 100,
		 AXP15060_CLDO4_V_CTRL, AXP15060_CLDO4_V_CTRL_MASK,
		 AXP15060_PWR_OUT_CTRL3, AXP15060_PWR_OUT_CLDO4_MASK),
	/* Supply comes from DCDC5 */
	AXP_DESC(AXP15060, CPUSLDO, "cpusldo", NULL, 700, 1400, 50,
		 AXP15060_CPUSLDO_V_CTRL, AXP15060_CPUSLDO_V_CTRL_MASK,
		 AXP15060_PWR_OUT_CTRL3, AXP15060_PWR_OUT_CPUSLDO_MASK),
	/* Supply comes from DCDC1 */
	AXP_DESC_SW(AXP15060, SW, "sw", NULL,
		    AXP15060_PWR_OUT_CTRL3, AXP15060_PWR_OUT_SW_MASK),
	/* Supply comes from ALDO1 */
	AXP_DESC_FIXED(AXP15060, RTC_LDO, "rtc-ldo", NULL, 1800),
};

static int regulator_read(struct regulator_dev *rdev, uint8_t reg, uint8_t *rbuf, uint32_t rlen){
	i2c_msg_t msg[2];
	int ret;

	if (!rdev)
		return -1;

	msg[0].addr = rdev->pmic_dev->i2c.addr;
	msg[0].flags = 0;
	msg[0].buf = &reg;
	msg[0].len = 1;
	msg[1].addr = rdev->pmic_dev->i2c.addr;
	msg[1].flags = CDNS_I2C_READ;
	msg[1].buf = rbuf;
	msg[1].len = rlen;
	ret = itcs_i2c_transfer(rdev->pmic_dev->i2c.i2c_dev, msg, 2);
	if (ret < 0) {
		printf("regulator read from 0x%x failed\n", reg);
		return ret;
	}

	return 0;
}

static int regulator_read_reg(struct regulator_dev *rdev, uint8_t reg, uint8_t *rbuf) {
	return regulator_read(rdev, reg, rbuf, 1);
}

static int regulator_write_reg(struct regulator_dev *rdev, uint8_t reg, uint8_t val) {
	i2c_msg_t msg;
	uint8_t buf[2];
	int ret;

	if (!rdev)
		return -1;

	buf[0] = reg;
	buf[1] = val;

	msg.addr = rdev->pmic_dev->i2c.addr;
	msg.flags = 0;
	msg.buf = buf;
	msg.len = sizeof(buf);

	ret = itcs_i2c_transfer(rdev->pmic_dev->i2c.i2c_dev, &msg, 1);
	if (ret < 0) {
		printf("regulator reg write 0x%x to 0x%x failed\n", val, reg);
		return ret;
	}

	return 0;
}

static int regulator_update_bits(struct regulator_dev *rdev, unsigned int reg, unsigned int mask, unsigned int val) {
	int ret;
	uint8_t current_val, new_val;

	ret = regulator_read_reg(rdev, reg, &current_val);
	if (ret < 0) {
		return ret;
	}

	new_val = (current_val & ~mask) | (val & mask);

	if (new_val == current_val) {
		return 0;
	}

	ret = regulator_write_reg(rdev, reg, new_val);
	if (ret < 0) {
		return ret;
	}

	return 0;
}

static int get_voltage_sel(struct regulator_dev *rdev){
	uint8_t val;
	int ret;

	ret = regulator_read_reg(rdev, rdev->desc->vsel_reg, &val);
	if (ret != 0)
		return ret;

	val &= rdev->desc->vsel_mask;
	val >>= ffs(rdev->desc->vsel_mask) - 1;

	return val; 
}

static int linear_range_get_value(const struct linear_range *r, unsigned int selector,
			   unsigned int *val)
{
	if (r->min_sel > selector || r->max_sel < selector)
		return -EINVAL;

	*val = r->min + (selector - r->min_sel) * r->step;

	return 0;
}

static int linear_range_get_value_array(const struct linear_range *r, int ranges,
				 unsigned int selector, unsigned int *val)
{
	int i;

	for (i = 0; i < ranges; i++)
		if (r[i].min_sel <= selector && r[i].max_sel >= selector)
			return linear_range_get_value(&r[i], selector, val);

	return -EINVAL;
}

static int regulator_list_voltage_linear_range(struct regulator_dev *rdev,
					     unsigned int selector)
{
	unsigned int val;
	int ret;

	ret = linear_range_get_value_array(rdev->desc->linear_ranges,
					   rdev->desc->n_linear_ranges, selector,
					   &val);
	if (ret)
		return ret;

	return val;
}

static int regulator_list_voltage_linear(struct regulator_dev *rdev,
				  unsigned int selector){
	if (selector >= rdev->desc->n_voltages)
		return -EINVAL;

	if (selector < rdev->desc->linear_min_sel)
		return 0;

	selector -= rdev->desc->linear_min_sel;

	return rdev->desc->min_uV + (rdev->desc->uV_step * selector);
}

static unsigned int linear_range_get_max_value(const struct linear_range *r)
{
	return r->min + (r->max_sel - r->min_sel) * r->step;
}

static int linear_range_get_selector_high(const struct linear_range *r,
				   unsigned int val, unsigned int *selector,
				   bool *found)
{
	*found = false;

	if (linear_range_get_max_value(r) < val)
		return -EINVAL;

	if (r->min > val) {
		*selector = r->min_sel;
		return 0;
	}

	*found = true;

	if (r->step == 0)
		*selector = r->max_sel;
	else
		*selector = DIV_ROUND_UP(val - r->min, r->step) + r->min_sel;

	return 0;
}

static int regulator_map_voltage_linear_range(struct regulator_dev *rdev,
				       int min_uV, int max_uV)
{
	const struct linear_range *range;
	int ret = -EINVAL;
	unsigned int sel;
	bool found;
	int voltage, i;

	if (!rdev->desc->n_linear_ranges) {
		return -EINVAL;
	}

	for (i = 0; i < rdev->desc->n_linear_ranges; i++) {
		range = &rdev->desc->linear_ranges[i];

		ret = linear_range_get_selector_high(range, min_uV, &sel,
						     &found);
		if (ret)
			continue;
		ret = sel;

		/*
		 * Map back into a voltage to verify we're still in bounds.
		 * If we are not, then continue checking rest of the ranges.
		 */
		voltage = regulator_list_voltage_linear_range(rdev, sel);
		if (voltage >= min_uV && voltage <= max_uV)
			break;
	}

	if (i == rdev->desc->n_linear_ranges)
		return -EINVAL;

	return ret;
}

static int regulator_map_voltage_linear(struct regulator_dev *rdev,
				 int min_uV, int max_uV)
{
	int ret, voltage;

	/* Allow uV_step to be 0 for fixed voltage */
	if (rdev->desc->n_voltages == 1 && rdev->desc->uV_step == 0) {
		if (min_uV <= rdev->desc->min_uV && rdev->desc->min_uV <= max_uV)
			return 0;
		else
			return -EINVAL;
	}

	if (!rdev->desc->uV_step) {
		BUG_ON(!rdev->desc->uV_step);
		return -EINVAL;
	}

	if (min_uV < rdev->desc->min_uV)
		min_uV = rdev->desc->min_uV;

	ret = DIV_ROUND_UP(min_uV - rdev->desc->min_uV, rdev->desc->uV_step);
	if (ret < 0)
		return ret;

	ret += rdev->desc->linear_min_sel;

	/* Map back into a voltage to verify we're still in bounds */
	voltage = regulator_list_voltage_linear(rdev, ret);
	if (voltage < min_uV || voltage > max_uV)
		return -EINVAL;

	return ret;
}

static int regulator_map_voltage(struct regulator_dev *rdev, int min_uV,
				 int max_uV)
{
	const struct regulator_desc *desc = rdev->desc;

	if (desc->linear_ranges)
		return regulator_map_voltage_linear_range(rdev, min_uV, max_uV);
	return regulator_map_voltage_linear(rdev, min_uV, max_uV);
}

static int set_voltage_sel(struct regulator_dev *rdev, unsigned sel)
{
	int ret;

	sel <<= ffs(rdev->desc->vsel_mask) - 1;

	ret = regulator_update_bits(rdev, rdev->desc->vsel_reg,
				  rdev->desc->vsel_mask, sel);

	return ret;
}

static int axp15060_enable(struct regulator_dev *rdev){
	unsigned int val;

	val = rdev->desc->enable_mask;
	return regulator_update_bits(rdev, rdev->desc->enable_reg,rdev->desc->enable_mask, val);
}

static int axp15060_disable(struct regulator_dev *rdev){
	unsigned int val;

	val = !rdev->desc->enable_mask;
	return regulator_update_bits(rdev, rdev->desc->enable_reg,rdev->desc->enable_mask, val);
}

static int axp15060_set_voltage(struct regulator_dev *rdev, int min_uV, int max_uV){
	int ret;
	int best_val = 0;
	unsigned int selector;
	int old_selector = rdev->selector;

	ret = regulator_map_voltage(rdev, min_uV, max_uV);
	if (ret >= 0) {
		if(rdev->desc->linear_ranges)
			best_val =regulator_list_voltage_linear_range(rdev, ret);
		else
			best_val =regulator_list_voltage_linear(rdev, ret);
		if (min_uV <= best_val && max_uV >= best_val) {
			selector = ret;
			if (old_selector == selector)
				ret = 0;
			else{
				ret = set_voltage_sel(rdev, selector);
				if(ret >=0)
					rdev->selector = selector;
			}
		} else {
			ret = -EINVAL;
		}
	}
	
	return ret;
}

static int axp15060_get_voltage(struct regulator_dev *rdev){
	int sel;

	sel = get_voltage_sel(rdev);

	if(rdev->desc->linear_ranges)
		return regulator_list_voltage_linear_range(rdev, sel);

	return regulator_list_voltage_linear(rdev, sel);
}

int axp15060_is_enabled(struct regulator_dev *rdev) {
	int ret;
	uint8_t current_val;

	ret = regulator_read_reg(rdev, rdev->desc->enable_reg, &current_val);
	if (ret < 0) {
		return ret;
	}

	return current_val & rdev->desc->enable_mask;
}

static struct regulator_ops axp15060_ops = {
	.enable = axp15060_enable,
	.disable = axp15060_disable,
	.set_voltage = axp15060_set_voltage,
	.get_voltage = axp15060_get_voltage,
	.get_current = NULL,
	.is_enabled = axp15060_is_enabled,
};

/*axp15060 init*/
int axp15060_init(struct pmic_dev *pmdev){
	pmdev->id = AXP15060_ID;
	pmdev->name = "axp15060";
	pmdev->desc = axp15060_regulators;
	pmdev->ndesc = ARRAY_SIZE(axp15060_regulators);
	pmdev->nrdev = 0;
	pmdev->ops = &axp15060_ops;

	pmdev->i2c.addr = AXP15060_I2C_ADDR;
	pmdev->i2c.bus = AXP15060_I2C_BUS;
	pmdev->i2c.i2c_dev = itcs_i2c_init(pmdev->i2c.bus, I2C_MASTER,
           ADDR_7BITS, pmdev->i2c.addr, I2C_MAX_FAST_MODE_FREQ);
	if(!pmdev->i2c.i2c_dev)
		return -1;

	return 0;
}

/*
 * ISL68221 pmic driver.
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
#include "isl68221.h"

/* ISL68221 I2C BUS ID */
#define ISL68221_I2C_BUS      1

/* ISL68221 I2C address */
#define ISL68221_I2C_ADDR     0x60

#define ISL_DESC(_family, _id, _match, _min, _max, _step, _vsmask, _vgmask, _ereg, _emask)\
	[_family##_##_id] = {							\
		.name		= (_match),					\
		.id		= _family##_##_id,				\
		.min_uV		= (_min) * 1000,				\
		.max_uV		= (_max) * 1000,				\
		.uV_step	= (_step) * 1000,				\
		.vset_mask	= (_vsmask),					\
		.vget_mask	= (_vgmask),					\
		.enable_reg	= (_ereg),					\
		.enable_mask	= (_emask),					\
	}

static const struct regulator_desc isl68221_regulators[] = {
	ISL_DESC(ISL68221, PAGE0, "page0", 0, 3050, 1,
		PMBUS_VOUT_COMMAND, PMBUS_READ_VOUT,
		PMBUS_OPERATION, OPERATION_CONTROL_ON),
	ISL_DESC(ISL68221, PAGE1, "page1", 0, 3050, 1,
		PMBUS_VOUT_COMMAND, PMBUS_READ_VOUT,
		PMBUS_OPERATION, OPERATION_CONTROL_ON),	
	ISL_DESC(ISL68221, PAGE2, "page2", 0, 3050, 1,
		PMBUS_VOUT_COMMAND, PMBUS_READ_VOUT,
		PMBUS_OPERATION, OPERATION_CONTROL_ON),
};

/*read word need rbuf is 2 bytes,low date byte first trans.*/
static int _i2c_pmbus_read_word(struct regulator_dev *rdev, uint8_t reg, uint8_t *rbuf){
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
	msg[1].len = 2;
	ret = itcs_i2c_transfer(rdev->pmic_dev->i2c.i2c_dev, msg, 2);
	if (ret < 0) {
		printf("i2c_pmbus_read_word failed\n");
		return ret;
	}

	return 0;
}

/*write word need rbuf is 2 bytes*/
static int _i2c_pmbus_write_word(struct regulator_dev *rdev, uint8_t reg, uint8_t *val){
	i2c_msg_t msg;
	uint8_t buf[3];
	int ret;

	if (!rdev)
		return -1;

	buf[0] = reg;
	buf[1] = val[0];
	buf[2] = val[1];

	msg.addr = rdev->pmic_dev->i2c.addr;
	msg.flags = 0;
	msg.buf = buf;
	msg.len = sizeof(buf);

	ret = itcs_i2c_transfer(rdev->pmic_dev->i2c.i2c_dev, &msg, 1);
	if (ret < 0) {
		printf("i2c_pmbus_write_word failed\n");
		return ret;
	}

	return 0;
}

static int _i2c_pmbus_write_byte(struct regulator_dev *rdev, uint8_t reg, uint8_t val){
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
		printf("i2c_pmbus_write_word failed\n");
		return ret;
	}

	return 0;
}

static int _i2c_pmbus_read_byte(struct regulator_dev *rdev, uint8_t reg, uint8_t *rbuf){
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
	msg[1].len = 1;
	ret = itcs_i2c_transfer(rdev->pmic_dev->i2c.i2c_dev, msg, 2);
	if (ret < 0) {
		printf("i2c_pmbus_read_word failed\n");
		return ret;
	}

	return 0;
}

static int i2c_pmbus_set_page(struct regulator_dev *rdev){
	int ret;

	ret = _i2c_pmbus_write_byte(rdev, PMBUS_PAGE, rdev->desc->id);
	if (ret < 0) {
		printf("_i2c_pmbus_write_byte failed\n");
		return ret;
	}

	return 0;
}

static int i2c_pmbus_read_word(struct regulator_dev *rdev, uint8_t reg, uint8_t *rbuf){
	int ret;

	ret = i2c_pmbus_set_page(rdev);//do we need the PMUBS_PHASE 0XFF??
	if (ret < 0) {
		printf("i2c_pmbus_set_page failed\n");
		return ret;
	}

	return _i2c_pmbus_read_word(rdev, reg, rbuf);

}

static int i2c_pmbus_write_word(struct regulator_dev *rdev, uint8_t reg, uint8_t *val){
	int ret;

	ret = i2c_pmbus_set_page(rdev);
	if (ret < 0) {
		printf("i2c_pmbus_set_page failed\n");
		return ret;
	}

	return _i2c_pmbus_write_word(rdev, reg, val);
}

static int i2c_pmbus_write_byte(struct regulator_dev *rdev, uint8_t reg, uint8_t val){
	int ret;

	ret = i2c_pmbus_set_page(rdev);
	if (ret < 0) {
		printf("i2c_pmbus_set_page failed\n");
		return ret;
	}
	return _i2c_pmbus_write_byte(rdev, reg, val);
}

static int i2c_pmbus_read_byte(struct regulator_dev *rdev, uint8_t reg, uint8_t *rbuf){
	int ret;

	ret = i2c_pmbus_set_page(rdev);
	if (ret < 0) {
		printf("i2c_pmbus_set_page failed\n");
		return ret;
	}
	return _i2c_pmbus_read_byte(rdev, reg, rbuf);
}

static int i2c_update_bits_byte(struct regulator_dev *rdev, unsigned int reg, unsigned int mask, unsigned int val) {
	int ret;
	uint8_t current_val, new_val;

	ret = i2c_pmbus_read_byte(rdev, reg, &current_val);
	if (ret < 0) {
		return ret;
	}

	new_val = (current_val & ~mask) | (val & mask);

	if (new_val == current_val) {
		return 0;
	}

	ret = i2c_pmbus_write_byte(rdev, reg, new_val);
	if (ret < 0) {
		return ret;
	}

	return 0;
}


static int isl68221_enable(struct regulator_dev *rdev){
	int ret;

	/*need enable software control first*/
	ret = i2c_update_bits_byte(rdev, PMBUS_ON_OFF_CONFIG, EN_OPERATION_COMMAND, EN_OPERATION_COMMAND);
	if (ret < 0) {
		printf("enable software control failed\n");
		return ret;
	}

	ret = i2c_update_bits_byte(rdev, PMBUS_OPERATION, OPERATION_CONTROL_ON, OPERATION_CONTROL_ON);
	if (ret < 0) {
		printf("isl68221 enable failed\n");
		return ret;
	}

	return 0;
}

static int isl68221_disable(struct regulator_dev *rdev){
	int ret;

	/*need enable software control first*/
	ret = i2c_update_bits_byte(rdev, PMBUS_ON_OFF_CONFIG, EN_OPERATION_COMMAND, EN_OPERATION_COMMAND);
	if (ret < 0) {
		printf("enable software control failed\n");
		return ret;
	}

	ret = i2c_update_bits_byte(rdev, PMBUS_OPERATION, OPERATION_CONTROL_ON, ~OPERATION_CONTROL_ON);
	if (ret < 0) {
		printf("isl68221 disable failed\n");
		return ret;
	}

	return 0;
}

/*need mV*/
static int isl68221_set_voltage(struct regulator_dev *rdev, int min_uV, int max_uV){
	int min_mV;
	uint8_t val[2];
	int ret;

	if( min_uV != max_uV){
		printf("isl68221 only support set same voltage present\n");
		return -1;
	}
	if( min_uV < rdev->desc->min_uV || max_uV > rdev->desc->max_uV){
		printf("voltage is not support\n");
		return -1;
	}

	min_mV = min_uV / 1000;
	val[0] = min_mV;
	val[1] = min_mV >> 8;
	ret = i2c_pmbus_write_word(rdev, PMBUS_VOUT_COMMAND, val);
	if (ret < 0) {
		printf("isl68221 set voltage failed\n");
		return ret;
	}
	return 0;
}

static int isl68221_get_voltage(struct regulator_dev *rdev){
	uint8_t rbuf[2];
	int val = 0;
	int ret;

	ret = i2c_pmbus_read_word(rdev, PMBUS_READ_VOUT, rbuf);
	if (ret < 0) {
		printf("isl68221 get voltage failed\n");
		return ret;
	}

	val = rbuf[0] | (rbuf[1] << 8);

	/*return uV*/
	return val * 1000;
}

static int isl68221_get_current(struct regulator_dev *rdev){
	uint8_t rbuf[2];
	int val = 0;
	int ret;

	ret = i2c_pmbus_read_word(rdev, PMBUS_READ_IOUT, rbuf);
	if (ret < 0) {
		printf("isl68221 get current failed\n");
		return ret;
	}

	val = rbuf[0] | (rbuf[1] << 8);
	
	/*return mA*/
	return val * 100;
}

int isl68221_is_enabled(struct regulator_dev *rdev){
	uint8_t rbuf;
	int ret;

	/*need enable software control first*/
	ret = i2c_update_bits_byte(rdev, PMBUS_ON_OFF_CONFIG, EN_OPERATION_COMMAND, EN_OPERATION_COMMAND);
	if (ret < 0) {
		printf("enable software control failed\n");
		return ret;
	}

	ret = i2c_pmbus_read_byte(rdev, PMBUS_OPERATION, &rbuf);
	if (ret < 0) {
		printf("isl68221 disable failed\n");
		return ret;
	}

	return rbuf & OPERATION_CONTROL_ON;
}

static struct regulator_ops isl68221_ops = {
	.enable = isl68221_enable,
	.disable = isl68221_disable,
	.set_voltage = isl68221_set_voltage,
	.get_voltage = isl68221_get_voltage,
	.get_current = isl68221_get_current,
	.is_enabled = isl68221_is_enabled,
};

int isl68221_init(struct pmic_dev *pmdev){
	pmdev->id = ISL68221_ID;
	pmdev->name = "	isl68221";
	pmdev->desc = isl68221_regulators;
	pmdev->ndesc = ARRAY_SIZE(isl68221_regulators);
	pmdev->nrdev = 0;
	pmdev->ops = &isl68221_ops;

	pmdev->i2c.addr = ISL68221_I2C_ADDR;
	pmdev->i2c.bus = ISL68221_I2C_BUS;
	pmdev->i2c.i2c_dev = itcs_i2c_init(pmdev->i2c.bus, I2C_MASTER,
		ADDR_7BITS, pmdev->i2c.addr, I2C_MAX_FAST_MODE_FREQ);
	if(!pmdev->i2c.i2c_dev)
		return -1;
	return 0;
}

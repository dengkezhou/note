#ifndef __PMIC_H__
#define __PMIC_H__

enum pmic_variants {
	AXP15060_ID = 0,
	ISL68221_ID,
	MAX_PMIC_VARIANTS,
};

/**
 * struct regulator_desc - Static regulator descriptor
 *
 * Each regulator registered with the core is described with a
 * structure of this type and a struct regulator_config.  This
 * structure contains the non-varying parts of the regulator
 * description.
 */
struct regulator_desc {
	const char *name;
	const char *supply_name;

	int id;
	unsigned int continuous_voltage_range:1;
	unsigned n_voltages;
	unsigned int n_current_limits;

	unsigned int min_uV;
	unsigned int max_uV;

	unsigned int uV_step;
	unsigned int linear_min_sel;

	const struct linear_range *linear_ranges;

	int n_linear_ranges;

	unsigned int vsel_reg;
	unsigned int vsel_mask;

	unsigned int vset_reg;
	unsigned int vset_mask;
	unsigned int vget_reg;
	unsigned int vget_mask;

	unsigned int enable_reg;
	unsigned int enable_mask;
	unsigned int enable_val;
	unsigned int disable_val;
};

struct linear_range {
	unsigned int min;
	unsigned int min_sel;
	unsigned int max_sel;
	unsigned int step;
};

/* Initialize struct linear_range for regulators */
#define REGULATOR_LINEAR_RANGE(_min_uV, _min_sel, _max_sel, _step_uV)	\
{									\
	.min		= _min_uV,					\
	.min_sel	= _min_sel,					\
	.max_sel	= _max_sel,					\
	.step		= _step_uV,					\
}

typedef struct cdns_i2c i2c_dev_t;

struct pmic_i2c {
	i2c_dev_t *i2c_dev;
	int addr;
	int bus;
};

struct regulator_dev;

struct regulator_ops {
	int (*enable)(struct regulator_dev *rdev);
	int (*disable)(struct regulator_dev *rdev);
	int (*set_voltage)(struct regulator_dev *rdev, int min_uV, int max_uV);
	int (*get_voltage)(struct regulator_dev *rdev);
	int (*get_current)(struct regulator_dev *rdev);
	int (*is_enabled)(struct regulator_dev *rdev);
};

struct pmic_dev{
	const char *name;
	unsigned int id;
	const struct regulator_desc *desc;
	uint32_t ndesc;
	struct pmic_i2c i2c;
	struct regulator_dev *rdev;
	uint32_t nrdev;
	struct regulator_ops *ops;
};

struct regulator_dev{
	struct pmic_dev *pmic_dev;
	const struct regulator_desc *desc;
	unsigned int selector;
	struct regulator_dev *next;
};

int itcs_print_pmic_all_voltages(unsigned int pmic);
int itcs_regulator_get_current(struct regulator_dev *rdev);
int itcs_regulator_set_voltage(struct regulator_dev *rdev, int min_uV, int max_uV);
int itcs_regulator_get_voltage(struct regulator_dev *rdev);
int itcs_regulator_disable(struct regulator_dev *rdev);
int itcs_regulator_enable(struct regulator_dev *rdev);
void itcs_regulator_put(struct regulator_dev *rdev);
struct regulator_dev *itcs_regulator_get(unsigned int pmic,const char *name);
int itcs_pmic_info(unsigned int pmic);
int itcs_regulator_is_enabled(struct regulator_dev *rdev);

#endif

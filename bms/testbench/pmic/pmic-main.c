#include <common.h>
#include <command.h>
#include <testbench.h>
#include <malloc.h>
#include <asm/io.h>
#include <i2c.h>
#include <pads.h>
#include <asm/bits.h>
#include <getopt.h>
#include <pmic.h>

static void pmic_show_usage(void) {
	printf("Usage: pmic [OPTION]...\n\n");
	printf("-h, --help\t\tcommand help\n");
	printf("-p\t\tpmic_id, 0: axp15060 ,1: isl68221\n");
	printf("-r\t\tregulator name\n");
	printf("-i\t\tpmic info\n");
	printf("-s\t\tset voltage,unit: mv\n");
	printf("-g\t\tget voltage,unit: mv\n");
	printf("-a\t\tget all regulators' voltage,unit: mv\n");
	printf("For example:\n");
	printf("see the pmic axp15060 info:\n \
	pmic -p 0 -i\n");
	printf("print all voltage of pmic axp15060:\n \
	pmic -p 0 -a\n");
	printf("get voltage of dcdc1 of apx15060:\n \
	pmic -p 0 -r dcdc1 -g\n");
	printf("set voltage 3330mv of dcdc1 of apx15060:\n \
	pmic -p 0 -r dcdc1 -s 3300\n");
}

/*get pmic info: all regulators' voltage range, step*/
static int pmic_regulators_info(int pmic_id) {
	int ret;

	ret = itcs_pmic_info(pmic_id);
	if (ret) {
		return -1;
	}
	return 0;
}

static int pmic_vol_all(int pmic_id) {
	int ret;

	ret = itcs_print_pmic_all_voltages(pmic_id);
	if (ret) {
		return -1;
	}
	return 0;
}

int pmic_vol_get(int pmic_id, char *name, int *voltage) {
	struct regulator_dev *rdev;
	int ret;

	rdev = itcs_regulator_get(pmic_id, name);
	if (!rdev) {
		return -1;
	}
	ret = itcs_regulator_enable(rdev);
	if (ret) {
		return -1;
	}
	*voltage = itcs_regulator_get_voltage(rdev) / 1000;

	itcs_regulator_put(rdev);
	return 0;
}

int pmic_cur_get(int pmic_id, char *name, int *cur) {
	struct regulator_dev *rdev;
	int ret;

	rdev = itcs_regulator_get(pmic_id, name);
	if (!rdev) {
		return -1;
	}
	ret = itcs_regulator_enable(rdev);
	if (ret) {
		return -1;
	}
	*cur = itcs_regulator_get_current(rdev);

	itcs_regulator_put(rdev);
	return 0;
}

int pmic_vol_set(int pmic_id, char *name, int voltage) {
	struct regulator_dev *rdev;
	int ret;

	rdev = itcs_regulator_get(pmic_id, name);
	if (!rdev) {
		printf("regulator get failed!\n");
		return -1;
	}
	ret = itcs_regulator_enable(rdev);
	if (ret) {
		printf("regulator enable failed!\n");
		goto err;
	}
	ret = itcs_regulator_set_voltage(rdev, voltage * 1000, voltage * 1000);
	if (ret) {
		printf("set %s voltage %dmv error!\n", rdev->desc->name, voltage);
		goto err;
	}

err:
	itcs_regulator_put(rdev);
	return ret;
}

int pmic_main(int argc, char *argv[]) {
	int option_index = 0, c, pmic_id = 0, voltage = 0, get = 0, getinfo = 0,
		getall = 0, ret = 0, cur = 0;
	char *name = NULL;
	static const char short_options[]         = "p:r:s:iagh";
	static const struct option long_options[] = {
		{"pmic_id", 0, 0, 'p'}, {"regulator", 0, 0, 'r'},
		{"setmv", 0, 0, 's'},   {"gmv", 0, 0, 'g'},
		{"all", 0, 0, 'a'},     {"info", 0, 0, 'i'},
		{"help", 0, 0, 'h'},    {0, 0, 0, 0},
	};

	while ((c = getopt_long(argc, argv, short_options, long_options,
                          &option_index)) != -1) {
		switch (c) {
		case 'p':
			pmic_id = simple_strtoul(optarg, NULL, 10);
			break;
		case 'r':
			name = optarg;
			break;
		case 's':
			get     = 0;
			voltage = simple_strtoul(optarg, NULL, 10);
			break;
		case 'g':
			get = 1;
			break;
		case 'i':
			getinfo = 1;
			break;
		case 'a':
			getall = 1;
			break;
		case 'h':
		default:
			pmic_show_usage();
			ret = -1;
			goto err;
		}
	}

	if (getall) {
		ret = pmic_vol_all(pmic_id);
		if (ret) {
			printf("get pmic all voltage error!\n");
		}
  	} else if (getinfo) {
		ret = pmic_regulators_info(pmic_id);
		if (ret) {
			printf("get pmic info error!\n");
		}
	} else if (get) {
		ret = pmic_vol_get(pmic_id, name, &voltage);
		if (ret) {
			printf("get voltage error!\n");
			goto err;
		}
		ret = pmic_cur_get(pmic_id, name, &cur);
		printf("regulator: %s, voltage: %dmv", name, voltage);
		if (cur >= 0)
			printf(", current: %dmA\n", cur);
		else
			printf("\n");
	} else {
		ret = pmic_vol_set(pmic_id, name, voltage);
		if (ret) {
			printf("set voltage error!\n");
		}
	}

	if (optind == 1) {
		pmic_show_usage();
		ret = 0;
		goto err;
	}
err:
	optind = 1;
	return ret;
}

void pmic_init(void) { register_testbench("pmic", pmic_main, NULL); }

testbench_init(pmic_init);

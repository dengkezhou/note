#include <common.h>
#include <command.h>
#include <testbench.h>
#include <malloc.h>
#include <asm/io.h>
#include <i2c.h>
#include <pads.h>
#include <asm/bits.h>
#include <getopt.h>
#include <hwmon.h>

static void hwmon_show_usage(void) {
	printf("Usage: hwmon [OPTION]...\n\n");
	printf("-h, --help\t\tcommand help\n");
	printf("-m\t\thwmon_id, 0: ina226\n");
	printf("-n\t\tname\n");
	printf("-b\t\tbus voltage,unit: mV\n");
	printf("-s\t\tshunt voltage,unit: mV\n");
	printf("-p\t\tpower,unit: uW\n");
	printf("-c\t\tcurrent,unit: mA\n");
	printf("-a\t\tget all properties of one module\n");
	printf("-z\t\tget all info of this hwmon\n");
	printf("For example:\n");
	printf("get the ina226,VDD_CPU power :\n \
	hwmon -m 0 -n VDD_CPU -p\n");
	printf("get the ina226,VDD_NPU0 power :\n \
	hwmon -m 0 -n VDD_NPU0 -p\n");
	printf("get the ina226,VDD_NPU1 power :\n \
	hwmon -m 0 -n VDD_NPU1 -p\n");
	printf("get the ina226,VDD_SOC power :\n \
	hwmon -m 0 -n VDD_SOC -p\n");
}

int hwmon_main(int argc, char *argv[]) {
	int option_index = 0, c, hwmon_id = 0, shunt = 0, bus = 0, power = 0, current = 0, all = 0, mall = 0, ret = 0;
	char *name = NULL;
	struct hwmon_sub * hwmonsub;
	static const char short_options[]         = "m:n:sbpcazh";
	static const struct option long_options[] = {
		{"module", 0, 0, 'm'}, {"name", 0, 0, 'n'},
		{"bus", 0, 0, 'b'}, {"power", 0, 0, 'p'},
		{"current", 0, 0, 'c'}, {"all", 0, 0, 'a'},
		{"allmodules", 0, 0, 'z'}, {"shunt", 0, 0, 's'},
		{"help", 0, 0, 'h'}, {0, 0, 0, 0},
	};

	while ((c = getopt_long(argc, argv, short_options, long_options,
                          &option_index)) != -1) {
		switch (c) {
		case 'm':
			hwmon_id = simple_strtoul(optarg, NULL, 10);
			break;
		case 'n':
			name = optarg;
			break;
		case 's':
			shunt = 1;
			break;
		case 'b':
			bus = 1;
			break;
		case 'p':
			power = 1;
			break;
		case 'c':
			current = 1;
			break;
		case 'a':
			all = 1;
			break;
		case 'z':
			mall = 1;
			break;
		case 'h':
		default:
			hwmon_show_usage();
			ret = -1;
			goto err;
		}
	}

	if(mall){
		ret = itcs_hwmon_print_all_info(hwmon_id);
		if (ret) {
			printf("get hwmon all error!\n");
		}
	} else {
		ret = itsc_hwmon_init(hwmon_id);
		if (ret) {
			printf("hwmon init error!\n");
		}
		hwmonsub = itcs_hwmon_get(hwmon_id, name);

		if (all){
			printf("%-10s %-25s %-15s %-10s %-20s\n", "Name", "Shunt Voltage/mV", "Bus Voltage/mV", "Current/mA", "power/uW");
			printf("-------------------------------------------------------------------------------\n");
			printf("%-10s %-25d %-15d %-10d %-20d\n", hwmonsub->name,
				itcs_hwmon_get_shunt_voltage(hwmonsub),
				itcs_hwmon_get_bus_voltage(hwmonsub),
				itcs_hwmon_get_current(hwmonsub),
				itcs_hwmon_get_power(hwmonsub));
		} else if (shunt){
			printf("Name: %s: shunt_voltage = %dmV\n", hwmonsub->name, itcs_hwmon_get_shunt_voltage(hwmonsub));
		} else if (bus) {
			printf("Name: %s: bus_voltage = %dmV\n", hwmonsub->name, itcs_hwmon_get_bus_voltage(hwmonsub));
		} else if (current) {
			printf("Name: %s: current = %dmA\n", hwmonsub->name, itcs_hwmon_get_current(hwmonsub));
		} else if (power) {
			printf("Name: %s: power = %duW\n", hwmonsub->name, itcs_hwmon_get_power(hwmonsub));
		} else {
			optind = 1;
			printf("error happened\n");
		}
	}

	if (optind == 1) {
		hwmon_show_usage();
		ret = 0;
		goto err;
	}
err:
	optind = 1;
	return ret;
}

void hwmon_init(void) { register_testbench("hwmon", hwmon_main, NULL); }

testbench_init(hwmon_init);


#include <common.h>
#include <command.h>
#include <testbench.h>
#include <malloc.h>
#include <asm/io.h>
#include <getopt.h>

extern int ddr_stress_test(void);

int ddr_test(void)
{
	int ret;
	printf("start ddr test with bus....\n");
	ret = ddr_stress_test();
	printf("end ddr test\n");
	return ret;
}

static void ddr_show_usage(void)
{
	printf("Usage: ddr [OPTION]...\n\n");
	printf("-h, --help\t\tcommand help\n");
	printf("-s, --stress\t\tstress test\n");
}

int ddr_main(int argc, char *argv[])
{
	int option_index = 0, c, ret = 0;
	static const char short_options[] = "sh";
	static const struct option long_options[] = {
		{ "stress", 0, 0, 's' },
		{ "help", 0, 0, 'h' },
		{ 0, 0, 0, 0 },
	};

	while ((c = getopt_long(argc, argv, short_options, long_options,
				&option_index)) != -1) {
		switch (c) {
		case 's':
			ret = ddr_test();
			break;
		case 'h':
		default:
			ddr_show_usage();
			ret = -1;
			goto err;
		}
	}

	if (optind == 1) {
		ddr_show_usage();
		ret = -1;
		goto err;
	}

err:
	optind = 1;
	return ret;
}

int ddr_rtl(int id)
{
	printf("invoking id: %d\n", id);
	return 0;
}

void ddr_init(void)
{
	register_testbench("ddr", ddr_main, ddr_rtl);
}

testbench_init(ddr_init);

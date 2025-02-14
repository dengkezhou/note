
#include <common.h>
#include <command.h>
#include <testbench.h>
#include <malloc.h>
#include <asm/io.h>
#include <getopt.h>
#include <lpddr4.h>

typedef enum {
	NULL_TEST,
	READ_WRITE_TEST,
	BUS_STRESS_TEST
} test_case;

volatile int def_low_freq = 0;
volatile int def_init_disable = 0;
volatile int def_phy_pll_bypass = 0;
volatile int def_phy_bist = 0;
volatile int def_phy_loopback = 0;
volatile int def_pi_training = 0;
volatile int def_jtag_boundary_test = 0;
volatile int def_axi_base_test = 0;
volatile int def_lp_test = 0;
volatile int def_dfs_test = 0;
volatile int def_zq_cal = 0;
volatile int def_axi_priority = 0;
volatile int def_mr_test = 0;
volatile int def_parallel_test = 0;
volatile int def_march_c_test = 0;
volatile int def_prbs_test = 0;
volatile int def_rambuster = 0;

extern int lpddr4_initialize(void);
extern int lpddr4_rw_test(void);
extern int lpddr4_bus_stress_test(void);
extern int lpddr4_rtl_asic_test(void);

extern int lpddr4_bringup_test(int num);

static void lpddr4_show_usage(void)
{
	printf("Usage: lpddr4 [OPTION]...\n\n");
	printf("-h, --help\t\tcommand help\n");
	printf("-w, --widtht\tlpddr4 chip width\n");
	printf("-n, --nums\t\tlpddr4 chip numbers\n");
	printf("-s, --stress\t\tbus stress test\n");
}

static int read_write_test(int width, int num)
{
	printf("read and write test\n");
	lpddr4_initialize();
	return lpddr4_rw_test();
}

static int bus_stress_test(void)
{
	printf("bus stress test\n");
	lpddr4_initialize();
	return lpddr4_bus_stress_test();
}

static void clear_rtl_def(void)
{
	def_low_freq = 0;
	def_init_disable = 0;
	def_phy_pll_bypass = 0;
	def_phy_bist = 0;
	def_phy_loopback = 0;
	def_pi_training = 0;
	def_jtag_boundary_test = 0;
	def_axi_base_test = 0;
	def_lp_test = 0;
	def_dfs_test = 0;
	def_zq_cal = 0;
	def_axi_priority = 0;
	def_mr_test = 0;
	def_parallel_test = 0;
	def_march_c_test = 0;
	def_prbs_test = 0;
	def_rambuster = 0;
}

static int axi_test(bool en_low_freq)
{
	clear_rtl_def();
	if (en_low_freq)
		def_low_freq = 1;
	def_axi_base_test = 1;
	lpddr4_rtl_asic_test();
	printf("Test AXI Pass\n");
	return 0;
}
static int pi_training_test(void)
{
	clear_rtl_def();
	def_pi_training = 1;
	def_init_disable = 1;
	lpddr4_rtl_asic_test();
	printf("Test PI Training Pass\n");
	return 0;
}

static int lp_test(void)
{
	clear_rtl_def();
	def_lp_test = 1;
	lpddr4_rtl_asic_test();
	printf("Test Low Power Pass\n");
	return 0;
}

static int dfs_test(void)
{
	clear_rtl_def();
	def_dfs_test = 1;
	lpddr4_rtl_asic_test();
	printf("Test DVFS Pass\n");
	return 0;
}

static int zq_cal_test(void)
{
	clear_rtl_def();
	def_zq_cal = 1;
	lpddr4_rtl_asic_test();
	printf("Test ZQ cal Pass\n");
	return 0;
}

static int axi_priority_test(void)
{
	clear_rtl_def();
	def_axi_priority = 1;
	lpddr4_rtl_asic_test();
	printf("Test AXI priority Pass\n");
	return 0;
}

static int pll_bypass_test(void)
{
	clear_rtl_def();
	def_phy_pll_bypass = 1;
	lpddr4_rtl_asic_test();
	printf("Test PLL bypass Pass\n");
	return 0;
}

static int jtag_bound_test(void)
{
	clear_rtl_def();
	def_jtag_boundary_test = 1;
	lpddr4_rtl_asic_test();
	printf("Test JTAG boundary Pass\n");
	return 0;
}

static int dll_bist_test(void)
{
	clear_rtl_def();
	def_phy_bist = 1;
	lpddr4_rtl_asic_test();
	printf("Test DLL BIST Pass\n");
	return 0;
}

static int low_freq_test(void)
{
	clear_rtl_def();
	def_low_freq = 1;
	lpddr4_rtl_asic_test();
	printf("Test Low Freq Pass\n");
	return 0;
}

static int phy_loopback_test(void)
{
	clear_rtl_def();
	def_phy_loopback = 1;
	lpddr4_rtl_asic_test();
	printf("Test PHY Loopback Pass\n");
	return 0;
}

static int lpddr4_bringup_monitor(void)
{
	char num_str[8] = { 0 };
	int number = 0;

	printf("Please select the test case\n");
	printf("%d: DDRAPP for MPU0\n", DDRAPP_TEST_MPU0);
	printf("%d: DDRAPP for MPU1\n", DDRAPP_TEST_MPU1);
	printf("%d: PI Training Test\n", LPDDR4_PI_TEST);
	printf("%d: Low Freq Test\n", LPDDR4_1066MHZ_TEST);
	printf("%d: PHY Loopback Test\n", LPDDR4_PHY_LOOPBACK_TEST);
	printf("%d: PHY PLL Bypass Test\n", LPDDR4_PHY_PLL_BYPASS_TEST);
	printf("%d: PHY BIST Test\n", LPDDR4_PHY_DLL_MBIST_TEST);
	printf("%d: AXI Test\n", LPDDR4_AXI_TEST);
	printf("%d: Low Power Test\n", LPDDR4_LOW_POWER_TEST);
	printf("%d: DVFS Test\n", LPDDR4_DFS_TEST);
	printf("%d: ZQ Cal Test\n", LPDDR4_ZQ_CAL_TEST);
	printf("%d: AXI Priority Test\n", LPDDR4_AXI_PRIORITY_TEST);
	printf("%d: JTAG Boundary Test\n", LPDDR4_JTAG_BOUNDARY_TEST);
	printf("%d: Mode Reg Test\n", LPDDR4_MODE_REG_TEST);
	printf("%d: BIST March C Test\n", LPDDR4_BIST_MARCH_C_TEST);
	printf("%d: BIST PRBS Test\n", LPDDR4_BIST_PRBS_TEST);
	printf("%d: parallel multi port conflict Test\n", LPDDR4_MULTI_PORT_PARALLEL_TEST);
	printf("%d: memtester Test for MPU0\n", LPDDR4_MEMTESTER_TEST_MPU0);
	printf("%d: memtester Test for MPU1\n", LPDDR4_MEMTESTER_TEST_MPU1);
	printf("%d: ram buster Test\n", RAMBUSTER_TEST);
	printf("Please enter your choice: ");

	while (1) {
		num_str[number] = (char)getc();
		if (num_str[number] == '\n') {
			if (number == 0)
				continue;
			else
				break;
		} else if (num_str[number] == '\r') {
			if (number == 0)
				continue;
			else
				break;
		}
		number++;
	}
	number = simple_strtoul(num_str, NULL, 10);
	printf("%d\n", number);
	printf("Start test...\n");

	clear_rtl_def();
	def_pi_training = 1;
	def_init_disable = 1;

	switch (number) {
	case DDRAPP_TEST_MPU0:
	case DDRAPP_TEST_MPU1:
	case LPDDR4_MEMTESTER_TEST_MPU0:
	case LPDDR4_MEMTESTER_TEST_MPU1:
		return lpddr4_bringup_test(number);
	case LPDDR4_PI_TEST:
		break;
	case LPDDR4_1066MHZ_TEST:
		def_low_freq = 1;
		break;
	case LPDDR4_PHY_LOOPBACK_TEST:
		def_phy_loopback = 1;
		break;
	case LPDDR4_PHY_PLL_BYPASS_TEST:
		def_phy_pll_bypass = 1;
		break;
	case LPDDR4_PHY_DLL_MBIST_TEST:
		def_phy_bist = 1;
		break;
	case LPDDR4_AXI_TEST:
		def_axi_base_test = 1;
		break;
	case LPDDR4_LOW_POWER_TEST:
		def_lp_test = 1;
		break;
	case LPDDR4_DFS_TEST:
		def_dfs_test = 1;
		break;
	case LPDDR4_ZQ_CAL_TEST:	
		def_zq_cal = 1;
		break;
	case LPDDR4_AXI_PRIORITY_TEST:
		def_axi_priority = 1;
		break;
	case LPDDR4_JTAG_BOUNDARY_TEST:	
		def_jtag_boundary_test = 1;
		break;
	case LPDDR4_MODE_REG_TEST:
		def_mr_test = 1;
		break;
	case LPDDR4_BIST_MARCH_C_TEST:
		def_march_c_test = 1;
		break;
	case LPDDR4_BIST_PRBS_TEST:
		def_prbs_test = 1;
		break;
	case LPDDR4_MULTI_PORT_PARALLEL_TEST:
		def_parallel_test = 1;
		break;
	case RAMBUSTER_TEST:
		def_rambuster = 1;
		break;
	default:
		break;
	}
	lpddr4_rtl_asic_test();
	return 0;
}

int lpddr4_main(int argc, char *argv[])
{
	int option_index = 0, c, ret = 0;
	static const char short_options[] = "w:n:bsh";
	static const struct option long_options[] = {
		{ "width", 1, 0, 'w' },	    { "nums", 1, 0, 'n' },
		{ "stress", 0, 0, 's' },
		{ "help", 0, 0, 'h' },	    { 0, 0, 0, 0 },
	};
	test_case t_case = NULL_TEST;
	int width = 0, nums = 0;
	int is_rtl = 1;

	if (strncmp(argv[1], "-loop", 5) == 0) {
		phy_loopback_test();
	} else if (strncmp(argv[1], "-bypass", 7) == 0) {
		pll_bypass_test();
	} else if (strncmp(argv[1], "-bist", 5) == 0) {
		dll_bist_test();
	} else if (strncmp(argv[1], "-pi", 3) == 0) {
		pi_training_test();
	} else if (strncmp(argv[1], "-axi", 4) == 0) {
		axi_test(0);
	} else if (strncmp(argv[1], "-lp", 3) == 0) {
		lp_test();
	} else if (strncmp(argv[1], "-dvfs", 5) == 0) {
		dfs_test();
	} else if (strncmp(argv[1], "-zq", 3) == 0) {
		zq_cal_test();
	} else if (strncmp(argv[1], "-prio", 5) == 0) {
		axi_priority_test();
	} else if (strncmp(argv[1], "-bound", 6) == 0) {
		jtag_bound_test();
	} else if (strncmp(argv[1], "-lf", 3) == 0) {
		low_freq_test();
	} else if (!strncmp(argv[1], "-bp", 3)) {
		lpddr4_bringup_monitor();
		return 0;
	} else {
		is_rtl = 0;
	}
	if (is_rtl)
		return 0;

	while ((c = getopt_long(argc, argv, short_options, long_options,
				&option_index)) != -1) {
		switch (c) {
		case 'w':
			t_case = READ_WRITE_TEST;
			if (!strcmp(optarg, "16")) {
				width = 16;
			} else if (!strcmp(optarg, "32")) {
				width = 32;
			} else {
				printf("params error\n");
				ret = -1;
				goto err;
			}
			break;
		case 'n':
			t_case = READ_WRITE_TEST;
			if (!strcmp(optarg, "1")) {
				nums = 1;
			} else if (!strcmp(optarg, "2")) {
				nums = 2;
			} else {
				printf("params error\n");
				ret = -1;
				goto err;
			}
			break;
		case 's':
			t_case = BUS_STRESS_TEST;
			break;
		case 'h':
		default:
			lpddr4_show_usage();
			ret = -1;
			goto err;
		}
	}

	if (t_case == READ_WRITE_TEST) {
		ret = read_write_test(width, nums);
	} else if (t_case == BUS_STRESS_TEST) {
		ret = bus_stress_test();
	} else {
		lpddr4_show_usage();
		ret = -1;
		goto err;
	}

	if (optind == 1) {
		lpddr4_show_usage();
		ret = -1;
		goto err;
	}

err:
	optind = 1;
	return ret;
}

int lpddr4_rtl(int id)
{
	printf("invoking id: %d\n", id);
	return 0;
}

void lpddr4_tb_init(void)
{
	register_testbench("lpddr4", lpddr4_main, lpddr4_rtl);
}

testbench_init(lpddr4_tb_init);

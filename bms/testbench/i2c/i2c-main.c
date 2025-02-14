#include <common.h>
#include <command.h>
#include <testbench.h>
#include <malloc.h>
#include <asm/io.h>
#include <getopt.h>
#include <pads.h>
#include <i2c.h>
#include <eeprom.h>

#if defined(CONFIG_COMPILE_FPGA) || defined(CONFIG_COMPILE_ASIC)
/* ADDR_TEST_LEN can't be greater than 256 because of unsigned char type. */
#define ADDR_TEST_LEN 256
#elif defined(CONFIG_COMPILE_RTL)
#define ADDR_TEST_LEN 32
#endif

uint8_t readdata[ADDR_TEST_LEN] = { 0 }, writedata[ADDR_TEST_LEN] = { 0 };
unsigned int i2cx_multiplex_enable = 0;

static int i2c_test(i2c_chan master, i2c_chan slave, i2c_addr_mode addr_mode,
		    i2c_speed_mode speed)
{
	int finish_flag = 0, correct0 = 0, correct1 = 0;
	int ret, i;
	i2c_dev_t *ms, *slv;
	int devaddr = 0x55;

	printf("test len: %d bytes\n", ADDR_TEST_LEN);

	for (i = 0; i < ADDR_TEST_LEN; i++)
		writedata[i] = i;

	ms = itcs_i2c_init(master, I2C_MASTER, addr_mode, 0, speed);
	slv = itcs_i2c_init(slave, I2C_SLAVE, addr_mode, devaddr, speed);
	if (!ms || !slv) {
		printf("i2c init failed\n");
		return -1;
	}

	itcs_set_irq_priority(ms->irq, IRQ_PRIORITY_0);
	itcs_set_irq_priority(slv->irq, IRQ_PRIORITY_1);

	itcs_i2c_read(slv, devaddr, readdata, ADDR_TEST_LEN, false);
	itcs_i2c_write(ms, devaddr, writedata, ADDR_TEST_LEN, true);
	while (1) {
		if (itcs_i2c_is_completed(slv)) {
			finish_flag = 1;
			break;
		}
		udelay(1);
	}
	if (finish_flag == 1) {
		ret = memcmp(readdata, writedata, ADDR_TEST_LEN);
		if (ret == 0)
			correct0 = 1;
	}

	/* master recv and slave send test. */
	finish_flag = 0;
	memset(readdata, 0x0, sizeof(readdata));

	itcs_set_irq_priority(ms->irq, IRQ_PRIORITY_1);
	itcs_set_irq_priority(slv->irq, IRQ_PRIORITY_0);

	itcs_i2c_write(slv, devaddr, writedata, ADDR_TEST_LEN, false);
	itcs_i2c_read(ms, devaddr, readdata, ADDR_TEST_LEN, true);
	while (1) {
		if (itcs_i2c_is_completed(ms)) {
			finish_flag = 1;
			break;
		}
		udelay(1);
	}
	if (finish_flag == 1) {
		ret = memcmp(readdata, writedata, ADDR_TEST_LEN);
		if (ret == 0)
			correct1 = 1;
	}

	if (correct0 == 1 && correct1 == 1) {
		if (i2cx_multiplex_enable)
			printf("Test I2C %d bits addr multiplex Pass\n",
			       addr_mode == ADDR_7BITS ? 7 : 10);
		else
			printf("Test I2C %d bits addr Pass\n",
			       addr_mode == ADDR_7BITS ? 7 : 10);
	} else {
		if (i2cx_multiplex_enable)
			printf("Test I2C %d bits addr multiplex Failed\n",
			       addr_mode == ADDR_7BITS ? 7 : 10);
		else
			printf("Test I2C %d bits addr Failed\n",
			       addr_mode == ADDR_7BITS ? 7 : 10);
	}

	itcs_i2c_exit(slv);
	itcs_i2c_exit(ms);
	return ret;
}

static int monitor_test(i2c_chan master, i2c_chan slave, i2c_addr_mode addr_mode,
			i2c_speed_mode speed)
{
	i2c_dev_t *ms, *slv;
	int devaddr = 0x55;
	int success = 0;
	int timeout = 1000;

	ms = itcs_i2c_init(master, I2C_MASTER, addr_mode, 0, speed);
	slv = itcs_i2c_init(slave, I2C_SLAVE, addr_mode, devaddr, speed);
	if (!ms || !slv) {
		printf("i2c init failed\n");
		return -1;
	}

	itcs_i2c_slv_mon_config(ms, devaddr, 3);
	while (timeout--) {
		udelay(10);
		if (itcs_i2c_slv_mon_is_rdy(ms)) {
			success = 1;
			break;
		}
	}
	if (success == 1)
		printf("Test I2C slave monitor Pass\n");
	else
		printf("Test I2C slave monitor failed\n");
	return success == 1 ? 0 : -1;
}

#if defined(CONFIG_COMPILE_FPGA) || defined(CONFIG_COMPILE_ASIC)
static int e2prom_test(i2c_chan master, i2c_addr_mode addr_mode,
		       i2c_speed_mode speed)
{
	int ret;
	eeprom_dev_t *dev;
	unsigned int addr = 0x0;

	printf("test len: %d\n", ADDR_TEST_LEN);

	dev = itcs_eeprom_attach_i2c(MICRO_24AA08_NAME, master, addr_mode, speed);
	if (!dev) {
                printf("eeprom attach failed\n");
                return -1;
        }

	for (int i = 0; i < ADDR_TEST_LEN; i++)
		writedata[i] = i;

	ret = itcs_eeprom_write(dev, addr, writedata, ADDR_TEST_LEN);
	if (ret == -1) {
		printf("eeprom write failed\n");
		return -1;
	}
	ret = itcs_eeprom_read(dev, addr, readdata, ADDR_TEST_LEN);
	if (ret == -1) {
                printf("eeprom read failed\n");
                return -1;
        }
	ret = memcmp(readdata, writedata, ADDR_TEST_LEN);
	if (ret == 0) {
		printf("i2c eeprom test pass\n");
	} else {
		printf("i2c eeprom test failed\n");
		ret = -1;
	}

	itcs_eeprom_deattach_i2c(dev);
	return ret;
}
#endif

static void i2c_show_usage(void)
{
	printf("Usage: i2c [OPTION]...\n\n");
	printf("-h, --help\t\tcommand help\n");
	printf("-m\t\tmaster mode\n");
	printf("-s\t\tslave mode\n");
	printf("-a\t\taddr mode\n");
	printf("-d\t\tspeed\n");
	printf("-t\t\tslave monitor test\n");
#if defined(CONFIG_COMPILE_FPGA) || defined(CONFIG_COMPILE_ASIC)
	printf("-e\t\te2prom read and write test\n");
#endif
}

int i2c_main(int argc, char *argv[])
{
	int option_index = 0, c, ret = 0;
#if defined(CONFIG_COMPILE_FPGA)
	static const char short_options[] = "m:s:a:d:teh";
	static const struct option long_options[] = {
		{ "master", 0, 0, 'm' },  { "slave", 0, 0, 's' },
		{ "addr", 0, 0, 'a' },	  { "speed", 0, 0, 'd' },
		{ "monitor", 0, 0, 't' }, { "e2prom", 0, 0, 'e' },
		{ "help", 0, 0, 'h' },	  { 0, 0, 0, 0 },
	};
#elif defined(CONFIG_COMPILE_ASIC)
	static const char short_options[] = "m:s:a:d:tpeh";
	static const struct option long_options[] = {
		{ "master", 0, 0, 'm' },  { "slave", 0, 0, 's' },
		{ "addr", 0, 0, 'a' },	  { "speed", 0, 0, 'd' },
		{ "monitor", 0, 0, 't' }, { "e2prom", 0, 0, 'e' },
		{ "help", 0, 0, 'h' },	  { "multiplex", 0, 0, 'p' },
		{ 0, 0, 0, 0 },
	};
#elif defined(CONFIG_COMPILE_RTL)
	static const char short_options[] = "m:s:a:d:tph";
	static const struct option long_options[] = {
		{ "master", 0, 0, 'm' },  { "slave", 0, 0, 's' },
		{ "addr", 0, 0, 'a' },	  { "speed", 0, 0, 'd' },
		{ "monitor", 0, 0, 't' }, { "multiplex", 0, 0, 'p' },
		{ "help", 0, 0, 'h' },
		{ 0, 0, 0, 0 },
	};
#endif
	i2c_chan master = I2C_CHAN0;
	i2c_chan slave = I2C_CHAN1;
	i2c_addr_mode addr_mode = ADDR_7BITS;
	i2c_speed_mode speed = NORMAL;
#if defined(CONFIG_COMPILE_FPGA) || defined(CONFIG_COMPILE_ASIC)
	int monitor = 0, e2prom = 0;
#elif defined(CONFIG_COMPILE_RTL)
	int monitor = 0;
#endif

	while ((c = getopt_long(argc, argv, short_options, long_options,
				&option_index)) != -1) {
		switch (c) {
		case 'm':
			master = simple_strtoul(optarg, NULL, 10);
			break;
		case 's':
			slave = simple_strtoul(optarg, NULL, 10);
			break;
		case 'a':
			if (!strcmp(optarg, "7"))
				addr_mode = ADDR_7BITS;
			else if (!strcmp(optarg, "10"))
				addr_mode = ADDR_10BITS;
			break;
		case 'd':
			if (!strcmp(optarg, "0"))
				speed = NORMAL;
			else if (!strcmp(optarg, "1"))
				speed = FAST;
			else if (!strcmp(optarg, "2"))
				speed = FAST_PLUS;
#ifdef CONFIG_COMPILE_RTL
			speed = I2C_RTL_SPEED;
#endif
			break;
		case 't':
			monitor = 1;
			break;
#if defined(CONFIG_COMPILE_RTL) || defined(CONFIG_COMPILE_ASIC)
		case 'p':
			i2cx_multiplex_enable = 1;
			break;
#endif
#if defined(CONFIG_COMPILE_FPGA) || defined(CONFIG_COMPILE_ASIC)
		case 'e':
			e2prom = 1;
			break;
#endif
		case 'h':
		default:
			i2c_show_usage();
			ret = -1;
			goto err;
		}
	}
#if defined(CONFIG_COMPILE_FPGA) || defined(CONFIG_COMPILE_ASIC)
	if (!monitor && !e2prom)
		ret = i2c_test(master, slave, addr_mode, speed);
	else if (monitor)
		ret = monitor_test(master, slave, addr_mode, speed);
	else if (e2prom)
		ret = e2prom_test(master, addr_mode, speed);
#elif defined(CONFIG_COMPILE_RTL)
	if (!monitor)
		ret = i2c_test(master, slave, addr_mode, speed);
	else if (monitor)
		ret = monitor_test(master, slave, addr_mode, speed);
#endif

	if (optind == 1) {
		i2c_show_usage();
		ret = -1;
		goto err;
	}
err:
	optind = 1;
	return ret;
}

void i2c_init(void)
{
	register_testbench("i2c", i2c_main, NULL);
}

testbench_init(i2c_init);

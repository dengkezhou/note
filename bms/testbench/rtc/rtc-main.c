
#include <common.h>
#include <command.h>
#include <testbench.h>
#include <malloc.h>
#include <rtc.h>
#include <asm/io.h>
#include <getopt.h>

static volatile int complete = -1;

static void rtc_dump_time(const char *ops, rtc_time_t *time)
{
	printf("rtc %s time %04d-%02d-%02d %02d:%02d:%02d:%02d\n", ops,
	       time->tm_year + 1900, time->tm_mon + 1, time->tm_mday,
	       time->tm_hour, time->tm_min, time->tm_sec, time->tm_hsec);
}

#ifndef CONFIG_COMPILE_RTL
static int rtc_time_test(void)
{
	rtc_setting_t sets = {
		.hourMode = HOUR24_MODE,
		.callback = NULL,
	};
	rtc_device_t *dev;
	rtc_time_t time0, time1;
	int subtime = 1000;
	int ret = -1;

	dev = itcs_rtc_init(&sets);
	if (!dev)
		return ret;

	itcs_rtc_init_time(&time0, 2022, 7, 21, 0, 0, 0, 0);
	rtc_dump_time("set", &time0);
	itcs_rtc_set_time(dev, &time0);

	udelay(subtime * 1000);

	itcs_rtc_get_time(dev, &time1);

	rtc_dump_time("get", &time1);

	if (time1.tm_sec - time0.tm_sec == 1)
		ret = 0;

	if (!ret)
		printf("Test RTC TIME Pass\n");

	itcs_rtc_deinit(dev);
	return ret;
}
#endif

static void rtc_alarm_callback(void *arg, int status)
{
	if (status & RTC_ALRM_TRIG)
		complete = 0;
}

static int rtc_alarm_test(void)
{
	rtc_setting_t sets = {
		.hourMode = HOUR24_MODE,
		.callback = rtc_alarm_callback,
	};
	rtc_device_t *dev;
	rtc_time_t time0, time1, time2;
	int ret = -1;

	dev = itcs_rtc_init(&sets);
	if (!dev)
		return ret;

	/* init time and avoid generating alarm interrupt immediately. */
	itcs_rtc_init_time(&time0, 2022, 7, 21, 12, 7, 0, 0);
	itcs_rtc_set_time(dev, &time0);
	rtc_dump_time("init", &time0);

	/* alarm doesn't support year setting, here we set it as 2022. */
	itcs_rtc_init_time(&time1, 2022, 7, 21, 12, 7, 22, 0);

	rtc_dump_time("set alarm", &time1);
	itcs_rtc_set_alarm(dev, &time1);

	itcs_rtc_init_time(&time0, 2022, 7, 21, 12, 7, 21, 0);
	itcs_rtc_set_time(dev, &time0);

	complete = -1;

	while (complete < 0)
		udelay(10);

	itcs_rtc_event_set_irq_enable(dev, RTC_ALRM_TRIG, false);
	itcs_rtc_get_time(dev, &time2);
	rtc_dump_time("set", &time0);
	rtc_dump_time("get", &time2);

	if (time2.tm_sec - time0.tm_sec == 1)
		ret = 0;

	if (!ret)
		printf("Test RTC ALARM Pass\n");

	itcs_rtc_deinit(dev);
	return ret;
}

static void rtc_event_callback(void *arg, int status)
{
	if (status & RTC_MIN_TRIG)
		complete = 0;
}

static int rtc_event_test(void)
{
	rtc_setting_t sets = {
		.hourMode = HOUR24_MODE,
		.callback = rtc_event_callback,
	};
	rtc_device_t *dev;
	rtc_time_t time0, time1;
	int ret = -1;

	dev = itcs_rtc_init(&sets);
	if (!dev)
		return ret;

	itcs_rtc_init_time(&time0, 2022, 7, 21, 12, 7, 59, 0);

	rtc_dump_time("set", &time0);
	itcs_rtc_set_time(dev, &time0);

	complete = -1;

	/* it's better to enable int after setting time. */
	itcs_rtc_event_set_irq_enable(dev, RTC_MIN_TRIG, true);

	while (complete < 0)
		udelay(10);

	itcs_rtc_event_set_irq_enable(dev, RTC_MIN_TRIG, false);
	itcs_rtc_get_time(dev, &time1);
	rtc_dump_time("get", &time1);

	if ((time1.tm_min - time0.tm_min) == 1)
		ret = 0;

	if (!ret)
		printf("Test RTC EVENT Pass\n");

	itcs_rtc_deinit(dev);
	return ret;
}

static int rtc_keep_test(void)
{
	rtc_setting_t sets = {
		.hourMode = HOUR24_MODE,
		.callback = NULL,
	};
	rtc_device_t *dev;
	rtc_time_t time0, time1, time2;
	rtc_time_t ctime0;
	rtc_time_t alr_time;
	int ret = -1;

	memset(&alr_time, 0, sizeof(rtc_time_t));
	itcs_rtc_init_time(&alr_time, 1900, 1, 1, 0, 0, 0, 0);

	dev = itcs_rtc_init(&sets);
	if (!dev)
		return ret;

	itcs_rtc_init_time(&time0, 2022, 7, 21, 12, 7, 12, 0);
	itcs_rtc_set_time(dev, &time0);
	itcs_rtc_init_time(&time1, 2022, 7, 21, 12, 7, 22, 0);
	itcs_rtc_set_alarm(dev, &time1);

	itcs_module_reset(RTC, "rtc");

	itcs_rtc_get_time(dev, &ctime0);
	itcs_rtc_get_alarm(dev, &time2);

	rtc_dump_time("set", &time0);
	rtc_dump_time("set alarm", &time1);
	rtc_dump_time("get", &ctime0);
	rtc_dump_time("get alarm", &time2);

	if (!memcmp(&time0, &ctime0, sizeof(time0)) &&
	    !memcmp(&time2, &alr_time, sizeof(time2)))
		ret = 0;

	if (!ret)
		printf("Test RTC KEEP Pass\n");
	else
		printf("Test RTC KEEP Failed\n");

	itcs_rtc_deinit(dev);
	return ret;
}

static void rtc_show_usage(void)
{
	printf("Usage: rtc [OPTION]...\n\n");
	printf("-h, --help\t\tcommand help\n");
#ifndef CONFIG_COMPILE_RTL
	printf("-t, --time\t\trtc time accuracy case\n");
#endif
	printf("-a, --alarm\t\trtc irq case\n");
	printf("-e, --event\t\trtc event irq case\n");
	printf("-k, --keep\t\trtc keep\n");
}

int rtc_main(int argc, char *argv[])
{
	int option_index = 0, c, ret = 0;
#ifndef CONFIG_COMPILE_RTL
	static const char short_options[] = "taekh";
	static const struct option long_options[] = {
		{ "time", 0, 0, 't' },	{ "alarm", 0, 0, 'a' },
		{ "event", 0, 0, 'e' }, { "keep", 0, 0, 'k' },
		{ "help", 0, 0, 'h' },	{ 0, 0, 0, 0 },
	};
#else
	static const char short_options[] = "aekh";
	static const struct option long_options[] = {
		{ "alarm", 0, 0, 'a' }, { "event", 0, 0, 'e' },
		{ "keep", 0, 0, 'k' },	{ "help", 0, 0, 'h' },
		{ 0, 0, 0, 0 },
	};
#endif

	while ((c = getopt_long(argc, argv, short_options, long_options,
				&option_index)) != -1) {
		switch (c) {
#ifndef CONFIG_COMPILE_RTL
		case 't':
			ret = rtc_time_test();
			break;
#endif
		case 'a':
			ret = rtc_alarm_test();
			break;
		case 'e':
			ret = rtc_event_test();
			break;
		case 'k':
			ret = rtc_keep_test();
			break;
		case 'h':
		default:
			rtc_show_usage();
			ret = -1;
			goto err;
		}
	}

	if (optind == 1) {
		rtc_show_usage();
		ret = -1;
		goto err;
	}

err:
	optind = 1;
	return ret;
}

int rtc_rtl(int id)
{
	printf("invoking id: %d\n", id);
	return 0;
}

void rtc_init(void)
{
	register_testbench("rtc", rtc_main, rtc_rtl);
}

testbench_init(rtc_init);

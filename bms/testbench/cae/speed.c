
#include <common.h>
#include <command.h>
#include <testbench.h>
#include <malloc.h>
#include <getopt.h>
#include <cae.h>
#include <rtc.h>
#include <sys/limits.h>

#define SIZE_NUM 6
#define SIZE_NUM_IVP 1
#define MAX_BLOCK_SIZE 128
#define DURATION_SECONDS 3
#define REDUNDANCY_SIZE 128

extern int crypto_enum_to_string(cipher crypto_type,
				 unsigned char *str_crypto_type);
extern void enable_cae_module(void);
extern void make_input_data(int enc);
extern void cae_ivp_fpga_speed_test(int enc);

static const int lengths_list[] = { 16, 64, 256, 1024, 8 * 1024, 16 * 1024 };

static const int lengths_list_ivp[] = { 128 * 1024 - 4 };

static const unsigned char key32[32 * 3] =
	"123456789abcdef03456789abcdef01256789abcdef01234789abcdef0123456";

static unsigned char iv[2 * MAX_BLOCK_SIZE / 8 * 3] =
	"00000000000000000000000000000000";

static volatile int run = 0;

static int mr = 0; /* machine-readeable output format to merge fork results */

static unsigned long results[SIZE_NUM];

static void print_message(const char *s, int length, int tm)
{
	printf(mr ? "+DT:%s:%d:%d\n" : "Doing %s for %ds on %d size blocks: ",
	       s, tm, length);
}

static void print_result(char *alg, int run_no, int count,
			 unsigned long time_used, int ivp)
{
#ifdef CONFIG_E906
	printf(mr ? "+R:%d:%s:%f\n" : "%d %s's in %ldms\n", count, alg,
	       time_used);
	if (ivp)
		results[run_no] = ((unsigned long)count) * lengths_list_ivp[run_no] / time_used * 1000;
	else
		results[run_no] = ((unsigned long)count) * lengths_list[run_no] / time_used * 1000;
#else
	printf(mr ? "+R:%d:%s:%f\n" : "%d %s's in %ldus\n", count, alg,
	       time_used);
	if (ivp)
		results[run_no] = ((unsigned long)count) * lengths_list_ivp[run_no] * 1000 * 1000 /
				  time_used;
	else
		results[run_no] = ((unsigned long)count) * lengths_list[run_no] * 1000 * 1000 /
				  time_used;
#endif
}

static void rtc_int_callback(void *arg, int status)
{
	if (status & RTC_ALRM_TRIG)
		run = 0;
	if (!(status & RTC_ALRM_TRIG) && status & RTC_SEC_TRIG)
		run = 1;
}

int rtc_alarm_set(rtc_device_t *dev, unsigned int duration)
{
	rtc_time_t time0, time1;

	itcs_rtc_init_time(&time0, 2022, 7, 21, 12, 7, 0, 0);
	itcs_rtc_set_time(dev, &time0);

	/* duration is 3s. */
	itcs_rtc_init_time(&time1, 2022, 7, 21, 12, 7, 21 + duration, 0);
	itcs_rtc_set_alarm(dev, &time1);

	itcs_rtc_init_time(&time0, 2022, 7, 21, 12, 7, 20, 0);
	itcs_rtc_set_time(dev, &time0);

	/* for more accurate time. */
	itcs_rtc_event_set_irq_enable(dev, RTC_SEC_TRIG, true);
	while (run == 0);
	itcs_rtc_event_set_irq_enable(dev, RTC_SEC_TRIG, false);
	return 0;
}

static rtc_device_t *rtc_alarm_init(rtc_setting_t *sets)
{
	rtc_device_t *dev;

	dev = itcs_rtc_init(sets);
	if (!dev)
		return NULL;
	else
		return dev;
}

static void rtc_alarm_exit(rtc_device_t *dev)
{
	itcs_rtc_deinit(dev);
}

static int fpga_speed_test(cae_id id, cipher crypto_type, int speed_enc)
{
	int ret = -1;
	int i, j;
	cipher_ctx *ctx = NULL;
	int tmp_len = 0;
	int out_len = 0;
	unsigned char *in = NULL;
	unsigned char *key = (unsigned char *)key32;
	unsigned char *out = NULL;
	unsigned char str_crypto_type[30] = { 0 };
	unsigned long start_time = 0, stop_time = 0;
	rtc_device_t *dev;
	int block_count;
	cae_device *c_dev;
	bool block = CAE_UPDATE_BLOCK;
	rtc_setting_t sets = {
		.hourMode = HOUR24_MODE,
		.callback = rtc_int_callback,
	};

	dev = rtc_alarm_init(&sets);
	if (dev == NULL) {
		printf("rtc alarm init failed\n");
		return -1;
	}

	in = malloc(lengths_list[SIZE_NUM - 1] + REDUNDANCY_SIZE);
	out = malloc(lengths_list[SIZE_NUM - 1] + REDUNDANCY_SIZE);
	if (in == NULL || out == NULL) {
		printf("speed test buf malloc failed\n");
		return -1;
	}

	c_dev = itcs_cae_init(id);
	if (!c_dev) {
		printf("cae%d init failed!\n", id);
		return -1;
	}

	if (crypto_enum_to_string(crypto_type, str_crypto_type) == -1)
		goto cleanup;
	if (speed_enc)
		printf("core %d enc speed test, cipher type: %s\n", id, str_crypto_type);
	else
		printf("core %d dec speed test, cipher type: %s\n", id, str_crypto_type);

	ctx = itcs_cipher_ctx_new(c_dev);
	if (!ctx)
		return ret;
	if (!speed_enc) {
		if (itcs_cipher_ctx_set_padding(ctx, PADDING_ZERO) != 1)
			goto cleanup;
	} else {
		if (itcs_cipher_ctx_set_padding(ctx, PADDING_PKCS7) != 1)
			goto cleanup;
	}

	for (i = 0; i < SIZE_NUM; i++) {
		if (itcs_cipher_init(ctx, crypto_type, key, iv, speed_enc) != 1)
			goto cleanup;
		block_count = 0;
		print_message((char *)str_crypto_type, lengths_list[i],
			      DURATION_SECONDS);
		rtc_alarm_set(dev, DURATION_SECONDS);
#ifdef CONFIG_E906
		start_time = get_timer(0);
#else
		start_time = get_timer_us(0);
#endif
		for (j = 0; run && j < INT_MAX; j++) {
			if (itcs_cipher_update(ctx, out, &tmp_len, in,
					       lengths_list[i], block) != 1)
				goto cleanup;
			block_count++;
		}
		if (itcs_cipher_final(ctx, out, &out_len) != 1)
			goto cleanup;
#ifdef CONFIG_E906
		stop_time = get_timer(0);
#else
		stop_time = get_timer_us(0);
#endif
		print_result((char *)str_crypto_type, i, block_count,
			     stop_time - start_time, 0);
	}

	if (mr) {
		printf("+H");
	} else {
		printf("The 'numbers' are in 1024s of bytes per second processed.\n");
		printf("type        ");
	}
	for (i = 0; i < SIZE_NUM; i++)
		printf(mr ? ":%d" : "%7d bytes", lengths_list[i]);
	printf("\n");

	if (mr)
		printf("+F:%s", str_crypto_type);
	else
		printf("%-13s", str_crypto_type);
	for (i = 0; i < SIZE_NUM; i++) {
		if (results[i] > 10000 && !mr)
			printf(" %10ldK", results[i] / 1024);
		else
			printf(mr ? ":%.2f" : "%11ldB", results[i]);
	}
	printf("\n");
cleanup:
	itcs_cipher_ctx_free(ctx);
	itcs_cae_exit(c_dev);
	rtc_alarm_exit(dev);
	return ret;
}

#if defined(CONFIG_DRV_CAE_IVP)
static int fpga_ivp_speed_test(cae_id id, cipher crypto_type, int speed_enc)
{
	int ret = -1;
	int i, j;
	unsigned char str_crypto_type[30] = { 0 };
	unsigned long start_time = 0, stop_time = 0;
	rtc_device_t *dev;
	int block_count;
	rtc_setting_t sets = {
		.hourMode = HOUR24_MODE,
		.callback = rtc_int_callback,
	};

	dev = rtc_alarm_init(&sets);
	if (dev == NULL) {
		printf("rtc alarm init failed\n");
		return -1;
	}

	enable_cae_module();

	if (crypto_enum_to_string(crypto_type, str_crypto_type) == -1)
		goto cleanup;
	if (speed_enc)
		printf("core %d ivp enc speed test, cipher type: %s\n", id, str_crypto_type);
	else
		printf("core %d ivp dec speed test, cipher type: %s\n", id, str_crypto_type);

	for (i = 0; i < SIZE_NUM_IVP; i++) {
		make_input_data(speed_enc);
		block_count = 0;
		print_message((char *)str_crypto_type, lengths_list_ivp[i],
			      DURATION_SECONDS);
		rtc_alarm_set(dev, DURATION_SECONDS);
#ifdef CONFIG_E906
		start_time = get_timer(0);
#else
		start_time = get_timer_us(0);
#endif
		for (j = 0; run && j < INT_MAX; j++) {
			cae_ivp_fpga_speed_test(speed_enc);
			block_count++;
		}
#ifdef CONFIG_E906
		stop_time = get_timer(0);
#else
		stop_time = get_timer_us(0);
#endif
		print_result((char *)str_crypto_type, i, block_count,
			     stop_time - start_time, 1);
	}

	if (mr) {
		printf("+H");
	} else {
		printf("The 'numbers' are in 1024s of bytes per second processed.\n");
		printf("type        ");
	}
	for (i = 0; i < SIZE_NUM_IVP; i++)
		printf(mr ? ":%d" : "%9d bytes", lengths_list_ivp[i]);
	printf("\n");

	if (mr)
		printf("+F:%s", str_crypto_type);
	else
		printf("%-13s", str_crypto_type);
	for (i = 0; i < SIZE_NUM_IVP; i++) {
		if (results[i] > 10000 && !mr)
			printf(" %10ldK", results[i] / 1024);
		else
			printf(mr ? ":%.2f" : "%11ldB", results[i]);
	}
	printf("\n");
cleanup:
	rtc_alarm_exit(dev);
	return ret;
}
#endif

int cae_speed_test(cae_id id, cipher crypto_type, int speed_enc, int ivp)
{
	int ret;

	if (ivp) {
#if defined(CONFIG_DRV_CAE_IVP)
		ret = fpga_ivp_speed_test(id, crypto_type, speed_enc);
#else
		printf("please select CONFIG_DRV_CAE_IVP using make menuconfig\n");
#endif
	} else {
		ret = fpga_speed_test(id, crypto_type, speed_enc);
	}

	return ret;
}

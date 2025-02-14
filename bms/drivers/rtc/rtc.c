#include <common.h>
#include <rtc.h>
#include <malloc.h>
#include <irq.h>

static void rtc_set_enabled(rtc_device_t *dev, bool enabled)
{
	uint32_t val = enabled ? 0 : CDNS_RTC_CTLR_TIME_CAL;

	writel(val, dev->regs + CDNS_RTC_CTLR);
}

static bool is_rtc_enabled(rtc_device_t *dev)
{
	return !(readl(dev->regs + CDNS_RTC_CTLR) & CDNS_RTC_CTLR_TIME_CAL);
}

void itcs_rtc_event_set_irq_enable(rtc_device_t *dev, int val, bool enabled)
{
	if (enabled)
		writel(val, dev->regs + CDNS_RTC_IENR);
	else
		writel(val, dev->regs + CDNS_RTC_IDISR);
}

static int rtc_post_meridiem(uint32_t reg)
{
	return GetNbit(reg, CDNS_RTC_TIME_PM_MASK, CDNS_RTC_TIME_PM_OFFSET);
}

static void rtc_reg2time(uint32_t reg, rtc_time_t *tm, int hourMode)
{
	if (!tm)
		return;

	tm->tm_hsec = bcd2bin(
		GetNbit(reg, CDNS_RTC_TIME_H_MASK, CDNS_RTC_TIME_H_OFFSET));
	tm->tm_sec = bcd2bin(
		GetNbit(reg, CDNS_RTC_TIME_S_MASK, CDNS_RTC_TIME_S_OFFSET));
	tm->tm_min = bcd2bin(
		GetNbit(reg, CDNS_RTC_TIME_M_MASK, CDNS_RTC_TIME_M_OFFSET));
	tm->tm_hour = bcd2bin(
		GetNbit(reg, CDNS_RTC_TIME_HR_MASK, CDNS_RTC_TIME_HR_OFFSET));

	if (hourMode == HOUR12_MODE && rtc_post_meridiem(reg))
		tm->tm_hour += 12;
}

static uint32_t rtc_time2reg(rtc_time_t *tm, int hourMode)
{
	uint32_t reg = SetNbit(bin2bcd(tm->tm_hsec), CDNS_RTC_TIME_H_MASK,
			       CDNS_RTC_TIME_H_OFFSET) |
		       SetNbit(bin2bcd(tm->tm_sec), CDNS_RTC_TIME_S_MASK,
			       CDNS_RTC_TIME_S_OFFSET) |
		       SetNbit(bin2bcd(tm->tm_min), CDNS_RTC_TIME_M_MASK,
			       CDNS_RTC_TIME_M_OFFSET);

	if (hourMode == HOUR12_MODE && tm->tm_hour > 12)
		reg |= SetNbit(bin2bcd(tm->tm_hour - 12), CDNS_RTC_TIME_HR_MASK,
			       CDNS_RTC_TIME_HR_OFFSET) |
		       SetNbit(1, CDNS_RTC_TIME_PM_MASK,
			       CDNS_RTC_TIME_PM_OFFSET);
	else
		reg |= SetNbit(bin2bcd(tm->tm_hour), CDNS_RTC_TIME_HR_MASK,
			       CDNS_RTC_TIME_HR_OFFSET);

	return reg;
}

void itcs_rtc_init_time(rtc_time_t *time, int year, int month, int day,
			int hour, int min, int sec, int hsec)
{
	if (!time)
		return;

	if (year < 1900 || month < 1) {
		printf("unsupported year or month!\n");
		return;
	}

	time->tm_year = year - 1900;
	time->tm_mon = month - 1;
	time->tm_mday = day;
	time->tm_hour = hour;
	time->tm_min = min;
	time->tm_sec = sec;
	time->tm_hsec = hsec;
}

int itcs_rtc_get_time(rtc_device_t *dev, rtc_time_t *tm)
{
	uint32_t val;

	if (!dev || !tm)
		return -1;

	if (!is_rtc_enabled(dev)) {
		printf("RTC is disabled\n");
		return -1;
	}
	/* disable rtc first */
	rtc_set_enabled(dev, false);
	/* get timr */
	val = readl(dev->regs + CDNS_RTC_TIMR);
	rtc_reg2time(val, tm, dev->hourMode);
	/* get calr */
	val = readl(dev->regs + CDNS_RTC_CALR);
	tm->tm_mday = bcd2bin(
		GetNbit(val, CDNS_RTC_CAL_D_MASK, CDNS_RTC_CAL_D_OFFSET));
	tm->tm_mon = bcd2bin(GetNbit(val, CDNS_RTC_CAL_M_MASK,
				     CDNS_RTC_CAL_M_OFFSET)) -
		     1;
	tm->tm_year = bcd2bin(GetNbit(val, CDNS_RTC_CAL_Y_MASK,
				      CDNS_RTC_CAL_Y_OFFSET)) +
		      bcd2bin(GetNbit(val, CDNS_RTC_CAL_C_MASK,
				      CDNS_RTC_CAL_C_OFFSET)) *
			      100 -
		      1900;
	if (tm->tm_year < 0)
		tm->tm_year = 0;
	tm->tm_wday = bcd2bin(GetNbit(val, CDNS_RTC_CAL_DAY_MASK,
				      CDNS_RTC_CAL_DAY_OFFSET)) -
		      1;
	if (tm->tm_wday < 0)
		tm->tm_wday = 0;
	rtc_set_enabled(dev, true);
	return 0;
}

static void wait_proper_chance(rtc_device_t *dev)
{
	/* wait change interrupt. */
	enable_irq(dev->change_irq);
	rtc_set_enabled(dev, true);
	while (!dev->in_position)
		;
	dev->in_position = 0;
	disable_irq(dev->change_irq);
}

int itcs_rtc_set_time(rtc_device_t *dev, rtc_time_t *tm)
{
	uint32_t timr, calr, stats, val;
	int year;
	int ret = -1;

	if (!dev || !tm)
		return -1;

	/* wait and after going to set time. */
	wait_proper_chance(dev);

	/* read mask reg. */
	val = readl(dev->regs + CDNS_RTC_IMSKR);
	/* turn off all int. ignore hos bit. */
	writel(CDNS_RTC_AEI_ALL, dev->regs + CDNS_RTC_IDISR);

	rtc_set_enabled(dev, false);

	/* set timr. */
	timr = rtc_time2reg(tm, dev->hourMode);

	/* set calr */
	year = tm->tm_year + 1900;
	calr = SetNbit(bin2bcd(tm->tm_mday), CDNS_RTC_CAL_D_MASK,
		       CDNS_RTC_CAL_D_OFFSET) |
	       SetNbit(bin2bcd(tm->tm_mon + 1), CDNS_RTC_CAL_M_MASK,
		       CDNS_RTC_CAL_M_OFFSET) |
	       SetNbit(bin2bcd(year / 100), CDNS_RTC_CAL_C_MASK,
		       CDNS_RTC_CAL_C_OFFSET) |
	       SetNbit(bin2bcd(year % 100), CDNS_RTC_CAL_Y_MASK,
		       CDNS_RTC_CAL_Y_OFFSET) |
	       SetNbit(bin2bcd(tm->tm_wday + 1), CDNS_RTC_CAL_DAY_MASK,
		       CDNS_RTC_CAL_DAY_OFFSET);

	for (int i = 0; i < CDNS_RTC_MAX_REGS_TRIES; i++) {
		writel(timr, dev->regs + CDNS_RTC_TIMR);
		writel(calr, dev->regs + CDNS_RTC_CALR);
		stats = readl(dev->regs + CDNS_RTC_STSR);
		if ((stats & CDNS_RTC_STSR_VT_VC) == CDNS_RTC_STSR_VT_VC) {
			ret = 0;
			break;
		}
	}
	/* must read CDNS_RTC_EFLR to clear int flag after CDNS_RTC_TIMR and CDNS_RTC_CALR setting . */
	readl(dev->regs + CDNS_RTC_EFLR);
	/* restore int. ignore hos bit. */
	writel(~val & CDNS_RTC_AEI_ALL, dev->regs + CDNS_RTC_IENR);

	if (!ret)
		rtc_set_enabled(dev, true);

	return ret;
}

static void rtc_alarm_set_irq_enabled(rtc_device_t *dev, bool enabled)
{
	if (!dev)
		return;

	if (enabled) {
		/* enable alarm */
		writel(CDNS_RTC_AEI_ALL, dev->regs + CDNS_RTC_AENR);
		/* enable alarm irq */
		writel(CDNS_RTC_AEI_ALRM, dev->regs + CDNS_RTC_IENR);
	} else {
		/* disable alarm */
		writel(0, dev->regs + CDNS_RTC_AENR);
		/* disable alarm irq */
		writel(CDNS_RTC_AEI_ALRM, dev->regs + CDNS_RTC_IDISR);
	}
}

int itcs_rtc_get_alarm(rtc_device_t *dev, rtc_time_t *alarm)
{
	uint32_t val;

	if (!dev || !alarm)
		return -1;

	/* alarm mode don't support year, reset all data to 0 */
	memset(alarm, 0, sizeof(rtc_time_t));

	/* get timar */
	val = readl(dev->regs + CDNS_RTC_TIMAR);
	rtc_reg2time(val, alarm, dev->hourMode);
	/* get calar */
	val = readl(dev->regs + CDNS_RTC_CALAR);
	alarm->tm_mday = bcd2bin(
		GetNbit(val, CDNS_RTC_CAL_D_MASK, CDNS_RTC_CAL_D_OFFSET));
	if (alarm->tm_mday == 0)
		alarm->tm_mday = 1;
	alarm->tm_mon = bcd2bin(GetNbit(val, CDNS_RTC_CAL_M_MASK,
					CDNS_RTC_CAL_M_OFFSET)) -
			1;
	if (alarm->tm_mon < 0)
		alarm->tm_mon = 0;

	return 0;
}

int itcs_rtc_set_alarm(rtc_device_t *dev, rtc_time_t *alarm)
{
	int ret = -1;
	uint32_t timar, calar, stsr, val;

	if (!dev || !alarm)
		return -1;

	/* read mask reg. */
	val = readl(dev->regs + CDNS_RTC_IMSKR);
	/* turn off all int. ignore hos bit. */
	writel(CDNS_RTC_AEI_ALL, dev->regs + CDNS_RTC_IDISR);

	rtc_alarm_set_irq_enabled(dev, false);
	timar = rtc_time2reg(alarm, dev->hourMode);

	/* set calr */
	calar = SetNbit(bin2bcd(alarm->tm_mday), CDNS_RTC_CAL_D_MASK,
			CDNS_RTC_CAL_D_OFFSET) |
		SetNbit(bin2bcd(alarm->tm_mon + 1), CDNS_RTC_CAL_M_MASK,
			CDNS_RTC_CAL_M_OFFSET);

	for (int i = 0; i < CDNS_RTC_MAX_REGS_TRIES; i++) {
		writel(timar, dev->regs + CDNS_RTC_TIMAR);
		writel(calar, dev->regs + CDNS_RTC_CALAR);
		stsr = readl(dev->regs + CDNS_RTC_STSR);

		if ((stsr & CDNS_RTC_STSR_VTA_VCA) == CDNS_RTC_STSR_VTA_VCA) {
			ret = 0;
			break;
		}
	}
	/* must read CDNS_RTC_EFLR to clear int flag after CDNS_RTC_TIMR and CDNS_RTC_CALR setting . */
	readl(dev->regs + CDNS_RTC_EFLR);
	/* restore int. ignore hos bit. */
	writel(~val & CDNS_RTC_AEI_ALL, dev->regs + CDNS_RTC_IENR);

	if (!ret)
		rtc_alarm_set_irq_enabled(dev, true);

	return ret;
}

int rtc_irq_handler(int irq, void *args)
{
	rtc_device_t *dev = (rtc_device_t *)args;
	uint32_t val;

	val = readl(dev->regs + CDNS_RTC_EFLR);
	if (irq == dev->irq) {
		if (dev->callback)
			dev->callback(dev->callback_param, val);
	} else if (irq == dev->change_irq) {
		dev->in_position = 1;
	}

	return 0;
}

rtc_device_t *itcs_rtc_init(rtc_setting_t *settings)
{
	rtc_device_t *dev = NULL;
	int ret;

	itcs_module_enable(RTC, "rtc");

	dev = (rtc_device_t *)malloc(sizeof(rtc_device_t));
	if (!dev)
		return NULL;

	memset(dev, 0, sizeof(rtc_device_t));

	dev->regs = ITCS_R_RTC_BASE;
	dev->irq = RTC4_IRQn;
	dev->change_irq = RTC12_IRQn;
	dev->hourMode = settings->hourMode;
	dev->in_position = 0;

	/* rtc keep. */
	writel(CDNS_RTC_KRTCR_KRTC, dev->regs + CDNS_RTC_KRTCR);
	//writel(0, dev->regs + CDNS_RTC_KRTCR);

	if (is_rtc_enabled(dev))
		rtc_set_enabled(dev, false);

	/* set Hour Mode */
	writel(dev->hourMode, dev->regs + CDNS_RTC_HMR);

	if (settings->callback) {
		dev->callback = settings->callback;
		dev->callback_param = settings->callback_param;
	}
	ret = request_irq(dev->irq, rtc_irq_handler, "rtc", dev);
	if (ret < 0) {
		free(dev);
		return NULL;
	}
	ret = request_irq(dev->change_irq, rtc_irq_handler, "rtc_change", dev);
	if (ret < 0) {
		free(dev);
		return NULL;
	}

	return dev;
}

void itcs_rtc_deinit(rtc_device_t *dev)
{
	rtc_set_enabled(dev, false);
	if (dev) {
		free(dev);
		dev = NULL;
	}
}

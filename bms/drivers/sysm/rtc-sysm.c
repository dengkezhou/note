#include <common.h>
#include <pads.h>
#include <rtc-sysm.h>

int is_rtc(domain_t sysmode)
{
	return (sysmode == RTC);
}

static int is_rtcfunc(int index)
{
	return (index == RTCGP2 || index == RTCGP5 || index == RTCGP4);
}

static int rtc_set_func(uint32_t index, int mode)
{
	if (!is_rtcfunc(index))
		return 0;

	if (index == RTCGP2) {
		if (mode != RTC_MUX1 && mode != RTC_GPIO)
			return -1;

		pads_writel(RTC_GPOEN, GPIO_XRTCGP2FUNC_MASK,
			    GPIO_XRTCGP2FUNC_OFFSET, mode);
	} else if (index == RTCGP5) {
		switch (mode) {
		case RTC_MUX2:
			pads_writel(RTC_CTRL, GPIO_XRTCGP5FUNC2_MASK,
				    GPIO_XRTCGP5FUNC2_OFFSET, 1);
			pads_writel(RTC_GPOEN, GPIO_XRTCGP5FUNC_MASK,
				    GPIO_XRTCGP5FUNC_OFFSET, 1);
			pads_writel(RTC_GPOEN, GPIO_XRTCXGP_MASK(index),
				    GPIO_XRTCXGP_OFFSET(index), 0);
			break;
		case RTC_MUX1:
			pads_writel(RTC_CTRL, GPIO_XRTCGP5FUNC2_MASK,
				    GPIO_XRTCGP5FUNC2_OFFSET, 0);
			pads_writel(RTC_GPOEN, GPIO_XRTCGP5FUNC_MASK,
				    GPIO_XRTCGP5FUNC_OFFSET, 0);
			break;
		case RTC_GPIO:
			pads_writel(RTC_CTRL, GPIO_XRTCGP5FUNC2_MASK,
				    GPIO_XRTCGP5FUNC2_OFFSET, 0);
			pads_writel(RTC_GPOEN, GPIO_XRTCGP5FUNC_MASK,
				    GPIO_XRTCGP5FUNC_OFFSET, 1);
			break;
		default:
			return -1;
		}
	} else if (index == RTCGP4) {
		if (mode != RTC_MUX1 && mode != RTC_GPIO)
			return -1;

		pads_writel(RTC_GPOUT, GPIO_XRTCGP4FUNC_MASK,
			    GPIO_XRTCGP4FUNC_OFFSET, mode);
	}

	return 0;
}

int rtc_get_mode(uint32_t index)
{
	switch (index) {
	case RTCGP2:
		if (pads_readl(RTC_GPOEN, GPIO_XRTCGP2FUNC_MASK,
			       GPIO_XRTCGP2FUNC_OFFSET))
			return PADS_MODE_FUNC;
		else if (pads_readl(RTC_XGPOEN(index), GPIO_XRTCXGP_MASK(index),
				    GPIO_XRTCXGP_OFFSET(index)))
			return PADS_MODE_IN;
		else
			return PADS_MODE_OUT;
		break;
	case RTCGP4:
		if (pads_readl(RTC_GPOUT, GPIO_XRTCGP4FUNC_MASK,
			       GPIO_XRTCGP4FUNC_OFFSET))
			return PADS_MODE_FUNC;
		else if (pads_readl(RTC_XGPOEN(index), GPIO_XRTCXGP_MASK(index),
				    GPIO_XRTCXGP_OFFSET(index)))
			return PADS_MODE_IN;
		else
			return PADS_MODE_OUT;
	case RTCGP5:
		if (pads_readl(RTC_CTRL, GPIO_XRTCGP5FUNC2_MASK,
			       GPIO_XRTCGP5FUNC2_OFFSET))
			return PADS_MODE_FUNC;
		else if (!pads_readl(RTC_GPOEN, GPIO_XRTCGP5FUNC_MASK,
				     GPIO_XRTCGP5FUNC_OFFSET))
			return PADS_MODE_FUNC;
		else if (pads_readl(RTC_XGPOEN(index), GPIO_XRTCXGP_MASK(index),
				    GPIO_XRTCXGP_OFFSET(index)))
			return PADS_MODE_IN;
		else
			return PADS_MODE_OUT;
		break;
	case RTCGP0:
	case RTCGP1:
	case RTCGP3:
	case RTCEGP0 ... RTCEGP7:
		if (pads_readl(RTC_XGPOEN(index), GPIO_XRTCXGP_MASK(index),
			       GPIO_XRTCXGP_OFFSET(index)))
			return PADS_MODE_IN;
		else
			return PADS_MODE_OUT;
		break;
	default:
		return -1;
	}
	return 0;
}

int rtc_set_mode(uint32_t range, int mode, uint32_t value)
{
	int start = GetStart(range);
	int end = GetEnd(range);
	int i;

	if (!end)
		end = start;

	/* invalid range */
	if (end < start) {
		printf("Range Err\n");
		return -1;
	}

	for (i = start; i <= end; i++) {
		switch (mode) {
		case PADS_MODE_FUNC:
			rtc_set_func(i, value);
			break;
		case PADS_MODE_IN:
			rtc_set_func(i, RTC_GPIO);
			pads_writel(RTC_XGIE(i), GPIO_XRTCXGP_MASK(i),
				    GPIO_XRTCXGP_OFFSET(i), 1);
			pads_writel(RTC_XGPOEN(i), GPIO_XRTCXGP_MASK(i),
				    GPIO_XRTCXGP_OFFSET(i), 1);
			break;
		case PADS_MODE_OUT:
			rtc_set_func(i, RTC_GPIO);
			pads_writel(RTC_XGPOEN(i), GPIO_XRTCXGP_MASK(i),
				    GPIO_XRTCXGP_OFFSET(i), 0);
			pads_writel(RTC_XGIE(i), GPIO_XRTCXGP_MASK(i),
				    GPIO_XRTCXGP_OFFSET(i), 0);
			if (i == RTCGP0)
				pads_writel(RTC_GPOUT2, GPIO_XRTCXGP_MASK(i),
					    GPIO_XRTCXGP_OFFSET(i), value);
			else
				pads_writel(RTC_XGPOUT(i), GPIO_XRTCXGP_MASK(i),
					    GPIO_XRTCXGP_OFFSET(i), value);
			break;
		default:
			printf("unknown RTC pads mode %d\n", mode);
			return -1;
		}
	}
	return 0;
}

int rtc_set_pull(uint32_t range, int en, uint32_t pattern)
{
	int start = GetStart(range);
	int end = GetEnd(range);
	int i;

	if (!end)
		end = start;

	/* invalid range */
	if (end < start) {
		printf("Range Err\n");
		return -1;
	}

	for (i = start; i <= end; i++) {
		switch (pattern) {
		case PADS_PULL_UP:
		case PADS_PULL_DOWN:
			pads_writel(RTC_XGPEN(i), GPIO_XRTCXGP_MASK(i),
				    GPIO_XRTCXGP_OFFSET(i), en);
			pads_writel(RTC_XGPS(i), GPIO_XRTCXGP_MASK(i),
				    GPIO_XRTCXGP_OFFSET(i), pattern);
			break;
		case PADS_PULL_NO:
			pads_writel(RTC_XGPEN(i), GPIO_XRTCXGP_MASK(i),
				    GPIO_XRTCXGP_OFFSET(i), 0);
			break;
		default:
			printf("Set Pull Pattern Err: %d\n", pattern);
			return -1;
		}
	}
	return 0;
}

int rtc_get_pull(uint32_t index)
{
	if (!pads_readl(RTC_XGPEN(index), GPIO_XRTCXGP_MASK(index),
			GPIO_XRTCXGP_OFFSET(index)))
		return PADS_PULL_NO;
	else
		return pads_readl(RTC_XGPS(index), GPIO_XRTCXGP_MASK(index),
				  GPIO_XRTCXGP_OFFSET(index));
}

int rtc_set_value(uint32_t range, uint32_t high)
{
	int start = GetStart(range);
	int end = GetEnd(range);
	int i = 0;

	if (!end)
		end = start;

	/* invalid range */
	if (end < start)
		return -1;

	for (i = start; i <= end; i++) {
		if (itcs_pads_get_mode(RTC, i) != PADS_MODE_OUT)
			continue;

		if (i == RTCGP0)
			pads_writel(RTC_GPOUT2, GPIO_XRTCXGP_MASK(i),
				    GPIO_XRTCXGP_OFFSET(i), high);
		else
			pads_writel(RTC_XGPOUT(i), GPIO_XRTCXGP_MASK(i),
				    GPIO_XRTCXGP_OFFSET(i), high);
	}
	return 0;
};

int rtc_get_value(uint32_t index, int *mode)
{
	int value = -1;

	*mode = itcs_pads_get_mode(RTC, index);
	switch (*mode) {
	case PADS_MODE_FUNC:
		break;
	case PADS_MODE_IN:
	case PADS_MODE_OUT:
		value = pads_readl(RTC_XGPIN(index), GPIO_XRTCXGP_MASK(index),
				   GPIO_XRTCXGP_OFFSET(index));
		break;
	default:
		printf("Mode Err: %d\n", *mode);
		return -1;
	}

	return value;
}

int is_rtcio(int index)
{
	return ((index >= RTCGP0) && (index <= RTCEGP7));
}

void rtc_irq_eoi(int index)
{
	if (!is_rtcio(index)) {
		printf("Do not support this io in RTC: %d\n", index);
		return;
	}

	pads_writel(RTC_XGPINTCLRSTS(index), RTC_XGPINT_MASK(index),
		    RTC_XGPINT_OFFSET(index), 1);
}

void rtc_irq_enable(int index)
{
	if (!is_rtcio(index)) {
		printf("Do not support this io in RTC: %d\n", index);
		return;
	}
	pads_writel(RTC_XGPINTEN(index), RTC_XGPINTEN_MASK(index),
		    RTC_XGPINTEN_OFFSET(index), 1);
}

void rtc_irq_disable(int index)
{
	if (!is_rtcio(index)) {
		printf("Do not support this io in RTC: %d\n", index);
		return;
	}
	pads_writel(RTC_XGPINTEN(index), RTC_XGPINTEN_MASK(index),
		    RTC_XGPINTEN_OFFSET(index), 0);
}

int rtc_set_type(int index, int type)
{
	int mode;

	switch (type) {
	case IRQ_TYPE_LEVEL_HIGH:
		mode = GPIO_LEVEL_HIGH;
		break;
	case IRQ_TYPE_LEVEL_LOW:
		mode = GPIO_LEVEL_LOW;
		break;
	default:
		printf("Do not support this IRQ Flags in RTC: %d\n", type);
		return -1;
	}

	pads_writel(RTC_XGPINTPOL(index), RTC_XGPINTPOL_MASK(index),
		    RTC_XGPINTPOL_OFFSET(index), mode);
	return 0;
}

static rtc_gpio_t rtc_ios[RTCGPMAX] = {
	{ RTC5_IRQn, false, "rtc gp0", { { RTCGP0 }, { ERRPAR } } },
	{ RTC6_IRQn, false, "rtc gp1", { { RTCGP1 }, { ERRPAR } } },
	{ RTC7_IRQn, false, "rtc gp2", { { RTCGP2 }, { ERRPAR } } },
	{ RTC0_IRQn, false, "rtc gp3", { { RTCGP3 }, { ERRPAR } } },
	{ RTC8_IRQn, false, "rtc gp4", { { RTCGP4 }, { ERRPAR } } },
	{ RTC9_IRQn, false, "rtc gp5", { { RTCGP5 }, { ERRPAR } } },
	{ RTC11_IRQn,
	  false,
	  "rtc egp0~7",
	  { { RTCEGP0 },
	    { RTCEGP1 },
	    { RTCEGP2 },
	    { RTCEGP3 },
	    { RTCEGP4 },
	    { RTCEGP5 },
	    { RTCEGP6 },
	    { RTCEGP7 },
	    { ERRPAR } } },
	{ ERRPAR }
};

rtc_gpio_t *get_rtc_ios_dev(int index)
{
	for (int i = 0; !isParErr(rtc_ios[i].irq); i++) {
		for (int j = 0; j < RTC_SHAREIRQ_MAX &&
				!isParErr(rtc_ios[i].sirq[j].index);
		     j++)
			if (rtc_ios[i].sirq[j].index == index)
				return &rtc_ios[i];
	}

	return NULL;
}

rtc_gpio_sirq_t *get_rtc_sirq(rtc_gpio_t *ios, int index)
{
	if (!ios)
		return NULL;

	for (int j = 0; j < RTC_SHAREIRQ_MAX && !isParErr(ios->sirq[j].index);
	     j++)
		if (ios->sirq[j].index == index)
			return &(ios->sirq[j]);

	return NULL;
}

int rtc_general_handle_irq(int irq, void *args)
{
	rtc_gpio_t *ios = (rtc_gpio_t *)args;
	rtc_gpio_sirq_t *sirq = ios->sirq;
	uint32_t status;

	if (!ios->requested)
		return -1;

	for (int i = 0; i < RTC_SHAREIRQ_MAX && !isParErr(sirq[i].index); i++) {
		status = pads_readl(RTC_XGPINTSTS(sirq[i].index),
				    RTC_XGPINT_MASK(sirq[i].index),
				    RTC_XGPINT_OFFSET(sirq[i].index));
		if (status) {
			if (sirq[i].handler)
				sirq[i].handler(sirq[i].index,
						sirq[i].private_data);

			rtc_irq_eoi(sirq[i].index);
		}
	}
	return 0;
}

int rtc_to_irq(int index)
{
	if (!is_rtcio(index)) {
		printf("Do not support this io in RTC: %d\n", index);
		return -1;
	}

	return get_rtc_ios_dev(index)->irq;
}

int rtc_request_irq(int index, irq_handler_t handler, int flags,
		    const char *name, void *dev)
{
	int ret;
	rtc_gpio_t *ios = NULL;
	rtc_gpio_sirq_t *sirq = NULL;

	if (!is_rtcio(index)) {
		printf("Do not support this io in RTC: %d\n", index);
		return -1;
	}

	if (rtc_set_type(index, flags) < 0)
		return -1;

	ios = get_rtc_ios_dev(index);
	if (!ios) {
		printf("Do not support this io in RTC: %d\n", index);
		return -1;
	}

	sirq = get_rtc_sirq(ios, index);
	sirq->handler = handler;
	sirq->private_data = dev;
	if (name)
		ios->name = name;

	if (!ios->requested) {
		ret = request_irq(ios->irq, rtc_general_handle_irq, ios->name, ios);
		if (ret)
			return ret;
		ios->requested = true;
	}
#if defined(CONFIG_COMPILE_FPGA) || defined(CONFIG_ASIC_TEST_ON_FPGA)
	rtc_irq_eoi(index);
#endif
	rtc_irq_enable(index);
	return 0;
}

int rtc_replace_irq(int index, irq_handler_t handler, int flags,
		    const char *name, void *dev)
{
	rtc_gpio_t *ios = NULL;
	rtc_gpio_sirq_t *sirq = NULL;

	if (!is_rtcio(index)) {
		printf("Do not support this io in RTC: %d\n", index);
		return -1;
	}

	rtc_irq_disable(index);
	if (rtc_set_type(index, flags) < 0) {
		rtc_irq_enable(index);
		return -1;
	}

	ios = get_rtc_ios_dev(index);
	if (!ios) {
		printf("Do not support this io in RTC: %d\n", index);
		return -1;
	}

	sirq = get_rtc_sirq(ios, index);

	sirq->handler = handler;
	sirq->private_data = dev;
	if (name)
		ios->name = name;

	rtc_irq_enable(index);
	return 0;
}

bool is_wakeup_reset(void)
{
	uint32_t val;
	val = pads_readl(RTC_RESETSTS, RTC_WKUPRSTSTS_MASK,
			 RTC_WKUPRSTSTS_OFFSET);
	if (val) {
		pads_writel(RTC_RSTINTCLR, RTC_WKUPRSTSTS_MASK,
			    RTC_WKUPRSTSTS_OFFSET, 1);
		return true;
	}
	return false;
}

bool is_soft_reset(void)
{
	uint32_t val;

	val = pads_readl(RTC_RESETSTS, RTC_SOFTRST_MASK, RTC_SOFTRST_OFFSET);
	if (val) {
		pads_writel(RTC_RSTINTCLR, RTC_SOFTRST_MASK, RTC_SOFTRST_OFFSET,
			    1);
		return true;
	}
	return false;
}

void rtc_info_set(int mode, int index, uint8_t val)
{
	if (mode != RSTCLR && mode != RSTUNCLR) {
		printf("RTC INFO mode Err: %d\n", mode);
		return;
	}

	if (((mode == RSTCLR) && (index < 0 || index > RINFO_RSTCLR_SUM)) ||
	    ((mode == RSTUNCLR) && (index < 0 || index > RINFO_RSTUNCLR_SUM))) {
		printf("RTC(%s) index Err: %d\n",
		       (mode == RSTCLR) ? "RstClr" : "RstUnclr", index);
		return;
	}

	pads_writel(RTC_INFO(mode, index), RTC_INFO_MASK, RTC_INFO_OFFSET, val);
}

uint8_t rtc_info_get(int mode, int index)
{
	if (mode != RSTCLR && mode != RSTUNCLR) {
		printf("RTC INFO mode Err: %d\n", mode);
		return -1;
	}

	if (((mode == RSTCLR) && (index < 0 || index > RINFO_RSTCLR_SUM)) ||
	    ((mode == RSTUNCLR) && (index < 0 || index > RINFO_RSTUNCLR_SUM))) {
		printf("RTC(%s) index Err: %d\n",
		       (mode == RSTCLR) ? "RstClr" : "RstUnclr", index);
		return -1;
	}

	return pads_readl(RTC_INFO(mode, index), RTC_INFO_MASK,
			  RTC_INFO_OFFSET);
}

void rtc_set_event(int event)
{
	if (event < RTC_IDLE || event > RTC_SOFTRESET) {
		printf("Do not support this event in RTC: %d\n", event);
		return;
	}

	pads_writel(RTC_EVENT, RTC_EVENT_MASK, RTC_EVENT_OFFSET, event);
}

void rtc_set_resume_source(int source, bool only)
{
	if (source < RESUME_RTCGP0 || source > RESUME_EVENT_MAX)
		return;

	pads_writel(RTC_INTMSK, RTC_WKUPMSK_MASK, RTC_WKUPMSK_OFFSET, 0);
	if (source <= RESUME_RTCGP5) {
		if (only) {
			pads_writel(RTC_PWRSADCLR, RTC_SETALL_MASK,
				    RTC_SETALL_OFFSET, 0xff);
			pads_writel(RTC_EPWRSADCLR, RTC_SETALL_MASK,
				    RTC_SETALL_OFFSET, 0xff);
		}
		pads_writel(RTC_PWRSADCLR, RTC_WKUPSOURCEMSK_MASK(source),
			    RTC_WKUPSOURCEMSK_OFFSET(source), 0);
	} else {
		if (only) {
			pads_writel(RTC_EPWRSADCLR, RTC_SETALL_MASK,
				    RTC_SETALL_OFFSET, 0xff);
			pads_writel(RTC_PWRSADCLR, RTC_SETALL_MASK,
				    RTC_SETALL_OFFSET, 0xff);
		}
		pads_writel(RTC_EPWRSADCLR, RTC_WKUPSOURCEMSK_MASK(source),
			    RTC_WKUPSOURCEMSK_OFFSET(source), 0);
	}
}

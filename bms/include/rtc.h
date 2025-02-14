#ifndef __RTC_H__
#define __RTC_H__

#include <asm/io.h>
#include <stdbool.h>

#define CDNS_RTC_CTLR 0x00
#define CDNS_RTC_HMR 0x04
#define CDNS_RTC_TIMR 0x08
#define CDNS_RTC_CALR 0x0C
#define CDNS_RTC_TIMAR 0x10
#define CDNS_RTC_CALAR 0x14
#define CDNS_RTC_AENR 0x18
#define CDNS_RTC_EFLR 0x1C
#define CDNS_RTC_IENR 0x20
#define CDNS_RTC_IDISR 0x24
#define CDNS_RTC_IMSKR 0x28
#define CDNS_RTC_STSR 0x2C
#define CDNS_RTC_KRTCR 0x30

#define CDNS_RTC_CTLR_TIME (1 << 0x0)
#define CDNS_RTC_CTLR_CAL (1 << 0x1)
#define CDNS_RTC_CTLR_TIME_CAL (CDNS_RTC_CTLR_TIME | CDNS_RTC_CTLR_CAL)

/* Time */
#define CDNS_RTC_TIME_H_OFFSET 0
#define CDNS_RTC_TIME_H_MASK (0xff << CDNS_RTC_TIME_H_OFFSET)
#define CDNS_RTC_TIME_S_OFFSET 8
#define CDNS_RTC_TIME_S_MASK (0x7f << CDNS_RTC_TIME_S_OFFSET)
#define CDNS_RTC_TIME_M_OFFSET 16
#define CDNS_RTC_TIME_M_MASK (0x7f << CDNS_RTC_TIME_M_OFFSET)
#define CDNS_RTC_TIME_HR_OFFSET 24
#define CDNS_RTC_TIME_HR_MASK (0x3f << CDNS_RTC_TIME_HR_OFFSET)
#define CDNS_RTC_TIME_PM_OFFSET 30
#define CDNS_RTC_TIME_PM_MASK (1 << CDNS_RTC_TIME_PM_OFFSET)
#define CDNS_RTC_TIME_CH_OFFSET 31
#define CDNS_RTC_TIME_CH_MASK (1 << CDNS_RTC_TIME_CH_OFFSET)

/* Calendar */
#define CDNS_RTC_CAL_DAY_OFFSET 0
#define CDNS_RTC_CAL_DAY_MASK (0x7 << CDNS_RTC_CAL_DAY_OFFSET)
#define CDNS_RTC_CAL_M_OFFSET 3
#define CDNS_RTC_CAL_M_MASK (0x1f << CDNS_RTC_CAL_M_OFFSET)
#define CDNS_RTC_CAL_D_OFFSET 8
#define CDNS_RTC_CAL_D_MASK (0x3f << CDNS_RTC_CAL_D_OFFSET)
#define CDNS_RTC_CAL_Y_OFFSET 16
#define CDNS_RTC_CAL_Y_MASK (0xff << CDNS_RTC_CAL_Y_OFFSET)
#define CDNS_RTC_CAL_C_OFFSET 24
#define CDNS_RTC_CAL_C_MASK (0x3f << CDNS_RTC_CAL_C_OFFSET)
#define CDNS_RTC_CAL_CH_OFFSET 31
#define CDNS_RTC_CAL_CH_MASK (1 << CDNS_RTC_CAL_CH_OFFSET)

#define CDNS_RTC_STSR_VT (1 << 0)
#define CDNS_RTC_STSR_VC (1 << 1)
#define CDNS_RTC_STSR_VTA (1 << 2)
#define CDNS_RTC_STSR_VCA (1 << 3)
#define CDNS_RTC_STSR_VT_VC (CDNS_RTC_STSR_VT | CDNS_RTC_STSR_VC)
#define CDNS_RTC_STSR_VTA_VCA (CDNS_RTC_STSR_VTA | CDNS_RTC_STSR_VCA)

#define CDNS_RTC_AEI_HOS (1 << 0)
#define CDNS_RTC_AEI_SEC (1 << 1)
#define CDNS_RTC_AEI_MIN (1 << 2)
#define CDNS_RTC_AEI_HOUR (1 << 3)
#define CDNS_RTC_AEI_DATE (1 << 4)
#define CDNS_RTC_AEI_MNTH (1 << 5)
#define CDNS_RTC_AEI_ALRM (1 << 6)
#define CDNS_RTC_AEI_ALL                                           \
	(CDNS_RTC_AEI_SEC | CDNS_RTC_AEI_MIN | CDNS_RTC_AEI_HOUR | \
	 CDNS_RTC_AEI_DATE | CDNS_RTC_AEI_MNTH | CDNS_RTC_AEI_ALRM)

#define RTC_HOS_TRIG (1 << 0)
#define RTC_SEC_TRIG (1 << 1)
#define RTC_MIN_TRIG (1 << 2)
#define RTC_HOUR_TRIG (1 << 3)
#define RTC_DATE_TRIG (1 << 4)
#define RTC_MNTH_TRIG (1 << 5)
#define RTC_ALRM_TRIG (1 << 6)

#define CDNS_RTC_MAX_REGS_TRIES 3

#define CDNS_RTC_KRTCR_KRTC (1 << 0)

#define GetNbit(reg, mask, offset) ((reg & mask) >> offset)
#define SetNbit(reg, mask, offset) ((reg << offset) & mask)

enum { HOUR24_MODE, HOUR12_MODE };

typedef struct rtc_setting {
	int hourMode;
	void (*callback)(void *arg, int status);
	void *callback_param;
} rtc_setting_t;

typedef struct rtc_device {
	unsigned long regs;
	int irq;
	int change_irq;
	int hourMode;
	void (*callback)(void *arg, int status);
	void *callback_param;
	volatile unsigned int in_position;
} rtc_device_t;

#define bcd2bin(x) (((x)&0x0f) + ((x) >> 4) * 10)
#define bin2bcd(x) ((((x) / 10) << 4) + (x) % 10)

/*
 * The struct used to pass data via the following ioctl. Similar to the
 * struct tm in <time.h>, but it needs to be here so that the kernel
 * source is self contained, allowing cross-compiles, etc. etc.
 */

typedef struct rtc_time {
	int tm_hsec; // hundreadths of a second
	int tm_sec;
	int tm_min;
	int tm_hour;
	int tm_mday;
	int tm_mon;
	int tm_year;
	int tm_wday;
#if 0
	int tm_yday;
	int tm_isdst;
#endif
} rtc_time_t;

void itcs_rtc_init_time(rtc_time_t *time, int year, int month, int day,
			int hour, int min, int sec, int hsec);
int itcs_rtc_get_time(rtc_device_t *dev, rtc_time_t *tm);
int itcs_rtc_set_time(rtc_device_t *dev, rtc_time_t *tm);
int itcs_rtc_get_alarm(rtc_device_t *dev, rtc_time_t *alarm);
int itcs_rtc_set_alarm(rtc_device_t *dev, rtc_time_t *alarm);
rtc_device_t *itcs_rtc_init(rtc_setting_t *settings);
void itcs_rtc_deinit(rtc_device_t *dev);
void itcs_rtc_event_set_irq_enable(rtc_device_t *dev, int val, bool enabled);
#endif

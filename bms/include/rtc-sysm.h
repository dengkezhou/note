#ifndef __RTC_SYSM_H__
#define __RTC_SYSM_H__

#include <irq.h>

#define RTC_EVENT     (ITCS_R_BASE + 0x0)
#define RTC_INTCLR    (ITCS_R_BASE + 0x4)
#define RTC_STS       (ITCS_R_BASE + 0x8)
#define RTC_INTMSK    (ITCS_R_BASE + 0xc)
#define RTC_RESETSTS  (ITCS_R_BASE + 0x10)
#define RTC_RSTINTCLR (ITCS_R_BASE + 0x14)
#define RTC_PWRSADCLR (ITCS_R_BASE + 0x20)
#define RTC_SDCNT     (ITCS_R_BASE + 0x24)

#define RTC_SETALL_OFFSET 0
#define RTC_SETALL_MASK   (0xff << RTC_SETALL_OFFSET)

#define RTC_EVENT_OFFSET 0
#define RTC_EVENT_MASK   (0x3 << RTC_EVENT_OFFSET)

#define RTC_GP0IRQ_OFFSET   3
#define RTC_GP0IRQ_MASK     (0x1 << RTC_GP0IRQ_OFFSET)
#define RTC_GP1IRQ_OFFSET   4
#define RTC_GP1IRQ_MASK     (0x1 << RTC_GP1IRQ_OFFSET)
#define RTC_GP2IRQ_OFFSET   5
#define RTC_GP2IRQ_MASK     (0x1 << RTC_GP2IRQ_OFFSET)
#define RTC_GP3IRQ_OFFSET   6
#define RTC_GP3IRQ_MASK     (0x1 << RTC_GP3IRQ_OFFSET)
#define RTC_TIMERIRQ_OFFSET 7
#define RTC_TIMERIRQ_MASK   (0x1 << RTC_TIMERIRQ_OFFSET)

#define RTC_WKUPMSK_OFFSET 3
#define RTC_WKUPMSK_MASK   (1 << RTC_WKUPMSK_OFFSET)

#define RTC_WKUPRSTSTS_OFFSET 1
#define RTC_WKUPRSTSTS_MASK   (0x1 << RTC_WKUPRSTSTS_OFFSET)
#define RTC_SOFTRST_OFFSET    2
#define RTC_SOFTRST_MASK      (1 << RTC_SOFTRST_OFFSET)

#define RTC_WKUPRSTCLR_OFFSET 1
#define RTC_WKUPRSTCLR_MASK   (0x1 << RTC_WKUPRSTCLR_OFFSET)

#define RTC_GP0MSKWKUP_OFFSET   0
#define RTC_GP0MSKWKUP_MASK     (0x1 << RTC_GP0MSKWKUP_OFFSET)
#define RTC_GP1MSKWKUP_OFFSET   1
#define RTC_GP1MSKWKUP_MASK     (0x1 << RTC_GP1MSKWKUP_OFFSET)
#define RTC_GP2MSKWKUP_OFFSET   2
#define RTC_GP2MSKWKUP_MASK     (0x1 << RTC_GP2MSKWKUP_OFFSET)
#define RTC_GP3MSKWKUP_OFFSET   3
#define RTC_GP3MSKWKUP_MASK     (0x1 << RTC_GP3MSKWKUP_OFFSET)
#define RTC_MSKTIMERWKUP_OFFSET 4
#define RTC_MSKTIMERWKUP_MASK   (0x1 << RTC_MSKTIMERWKUP_OFFSET)
#define RTC_GP4MSKWKUP_OFFSET   5
#define RTC_GP4MSKWKUP_MASK     (0x1 << RTC_GP4MSKWKUP_OFFSET)
#define RTC_GP5MSKWKUP_OFFSET   6
#define RTC_GP5MSKWKUP_MASK     (0x1 << RTC_GP5MSKWKUP_OFFSET)

#define RTC_SDCNT_OFFSET 0
#define RTC_SDCNT_MASK   (0xff << RTC_SDCNT_OFFSET)

#define RTC_EPWRSADCLR (ITCS_R_BASE + 0x28)
#define RTC_EGPPOL     (ITCS_R_BASE + 0x2c)
#define RTC_EGPINTE    (ITCS_R_BASE + 0x30)
#define RTC_EGPSTATUS  (ITCS_R_BASE + 0x34)
#define RTC_EGPEN      (ITCS_R_BASE + 0x68)
#define RTC_EGPS       (ITCS_R_BASE + 0x6c)
#define RTC_EGIE       (ITCS_R_BASE + 0x70)
#define RTC_EGPOEN     (ITCS_R_BASE + 0x74)
#define RTC_EGPOUT     (ITCS_R_BASE + 0x78)
#define RTC_EGPIN      (ITCS_R_BASE + 0x7c)

#define RTC_GPEN   (ITCS_R_BASE + 0x40)
#define RTC_GPS    (ITCS_R_BASE + 0x44)
#define RTC_GIE    (ITCS_R_BASE + 0x48)
#define RTC_GPOEN  (ITCS_R_BASE + 0x4c)
#define RTC_GPOUT  (ITCS_R_BASE + 0x50)
#define RTC_GPOUT2 (ITCS_R_BASE + 0x54)
#define RTC_GPIN   (ITCS_R_BASE + 0x58)
#define RTC_IRQ    (ITCS_R_BASE + 0x5c)
#define RTC_CTRL   (ITCS_R_BASE + 0x60)
#define RTC_IRQSTS (ITCS_R_BASE + 0x64)
#define RTC_INFO(mod, idx)                                                     \
  (ITCS_R_BASE + ((mod == RSTCLR) ? 0xc0 : 0x100) + 0x4 * idx)
#define RINFO_RSTCLR_SUM   16
#define RINFO_RSTUNCLR_SUM 32

#define RTC_INFO_OFFSET 0
#define RTC_INFO_MASK   (0xff << RTC_INFO_OFFSET)

#define RTC_GP0INTPOL_OFFSET 4
#define RTC_GP0INTPOL_MASK   (0x1 << RTC_GP0INTPOL_OFFSET)
#define RTC_GP1INTPOL_OFFSET 5
#define RTC_GP1INTPOL_MASK   (0x1 << RTC_GP1INTPOL_OFFSET)
#define RTC_GP2INTPOL_OFFSET 6
#define RTC_GP2INTPOL_MASK   (0x1 << RTC_GP2INTPOL_OFFSET)
#define RTC_GP3INTPOL_OFFSET 7
#define RTC_GP3INTPOL_MASK   (0x1 << RTC_GP3INTPOL_OFFSET)
#define RTC_GP0INTEN_OFFSET  0
#define RTC_GP0INTEN_MASK    (0x1 << RTC_GP0INTEN_OFFSET)
#define RTC_GP1INTEN_OFFSET  1
#define RTC_GP1INTEN_MASK    (0x1 << RTC_GP1INTEN_OFFSET)
#define RTC_GP2INTEN_OFFSET  2
#define RTC_GP2INTEN_MASK    (0x1 << RTC_GP2INTEN_OFFSET)
#define RTC_GP3INTEN_OFFSET  3
#define RTC_GP3INTEN_MASK    (0x1 << RTC_GP3INTEN_OFFSET)

#define RTC_GP4INTEN_OFFSET  0
#define RTC_GP4INTEN_MASK    (0x1 << RTC_GP4INTEN_OFFSET)
#define RTC_GP5INTEN_OFFSET  1
#define RTC_GP5INTEN_MASK    (0x1 << RTC_GP5INTEN_OFFSET)
#define RTC_GP4INTPOL_OFFSET 2
#define RTC_GP4INTPOL_MASK   (0x1 << RTC_GP4INTPOL_OFFSET)
#define RTC_GP5INTPOL_OFFSET 3
#define RTC_GP5INTPOL_MASK   (0x1 << RTC_GP5INTPOL_OFFSET)

#define RTC_GPINTEN_OFFSET(n)  ((n < 4) ? n : n - 4)
#define RTC_GPINTEN_MASK(n)    (0x1 << RTC_GPINTEN_OFFSET(n))
#define RTC_GPINTPOL_OFFSET(n) ((n < 4) ? 4 + n : n - 2)
#define RTC_GPINTPOL_MASK(n)   (0x1 << RTC_GPINTPOL_OFFSET(n))

#define RTC_GP4IRQ_OFFSET 0
#define RTC_GP4IRQ_MASK   (0x1 << RTC_GP4IRQ_OFFSET)
#define RTC_GP5IRQ_OFFSET 1
#define RTC_GP5IRQ_MASK   (0x1 << RTC_GP5IRQ_OFFSET)

#define RTC_GPINT_OFFSET(n) ((n < 4) ? 3 + n : n - 4)
#define RTC_GPIRQ_MASK(n)   (0x1 << RTC_GPINT_OFFSET(n))

enum {
  RTCGP0,
  RTCGP1,
  RTCGP2,
  RTCGP3,
  RTCGP4,
  RTCGP5,
  RTCEGP0,
  RTCEGP1,
  RTCEGP2,
  RTCEGP3,
  RTCEGP4,
  RTCEGP5,
  RTCEGP6,
  RTCEGP7,
  RTCGPMAX
};

enum {
  RTC_GPIO,
  RTC_MUX1,
  RTC_MUX2,
};

enum {
  RSTCLR,
  RSTUNCLR,
};

enum { RTC_IDLE, RTC_SLEEP, RTC_SHUTDOWN, RTC_SOFTRESET };

enum {
  RESUME_RTCGP0,
  RESUME_RTCGP1,
  RESUME_RTCGP2,
  RESUME_RTCGP3,
  RESUME_RTCALARM,
  RESUME_RTCGP4,
  RESUME_RTCGP5,
  RESUME_RTCEGP0,
  RESUME_RTCEGP1,
  RESUME_RTCEGP2,
  RESUME_RTCEGP3,
  RESUME_RTCEGP4,
  RESUME_RTCEGP5,
  RESUME_RTCEGP6,
  RESUME_RTCEGP7,
  RESUME_EVENT_MAX
};

#define RTC_WKUPSOURCEMSK_OFFSET(n)                                            \
  ((n > RESUME_RTCGP5) ? n - RESUME_RTCEGP0 : n)
#define RTC_WKUPSOURCEMSK_MASK(n) (1 << RTC_WKUPSOURCEMSK_OFFSET(n))

#define RTCTEST_RESET_MAGIC 0xaa

#define GPIO_XRTCGP_OFFSET(n) (n)
#define GPIO_XRTCGP_MASK(n)   (1 << GPIO_XRTCGP_OFFSET(n))

#define GPIO_XRTCGP2FUNC_OFFSET  6
#define GPIO_XRTCGP2FUNC_MASK    (1 << GPIO_XRTCGP2FUNC_OFFSET)
#define GPIO_XRTCGP4FUNC_OFFSET  6
#define GPIO_XRTCGP4FUNC_MASK    (1 << GPIO_XRTCGP4FUNC_OFFSET)
#define GPIO_XRTCGP5FUNC_OFFSET  7
#define GPIO_XRTCGP5FUNC_MASK    (1 << GPIO_XRTCGP5FUNC_OFFSET)
#define GPIO_XRTCGP5FUNC2_OFFSET 4
#define GPIO_XRTCGP5FUNC2_MASK   (1 << GPIO_XRTCGP5FUNC2_OFFSET)

#define GPIO_XRTCEGP_OFFSET(n)  (n - RTCEGP0)
#define GPIO_XRTCEGP_MASK(n)    (1 << GPIO_XRTCEGP_OFFSET(n))
#define RTC_EGPINTPOL_OFFSET(n) (n - RTCEGP0)
#define RTC_EGPINTPOL_MASK(n)   (0x1 << RTC_EGPINTPOL_OFFSET(n))
#define RTC_EGPINTEN_OFFSET(n)  (n - RTCEGP0)
#define RTC_EGPINTEN_MASK(n)    (0x1 << RTC_EGPINTEN_OFFSET(n))
#define RTC_EGPINT_OFFSET(n)    (n - RTCEGP0)
#define RTC_EGPINT_MASK(n)      (0x1 << RTC_EGPINT_OFFSET(n))

#define ERRPAR      -1
#define isE(n)      ((n >= RTCEGP0) && (n <= RTCEGP7))
#define isSpecIO(n) ((n >= RTCGP4) && (n <= RTCGP5))
#define isParErr(n) (n == ERRPAR)

#define GPIO_XRTCXGP_OFFSET(n)                                                 \
  (isE(n) ? GPIO_XRTCEGP_OFFSET(n) : GPIO_XRTCGP_OFFSET(n))
#define GPIO_XRTCXGP_MASK(n) (1 << GPIO_XRTCXGP_OFFSET(n))

#define RTC_XGIE(n)   (isE(n) ? RTC_EGIE : RTC_GIE)
#define RTC_XGPOEN(n) (isE(n) ? RTC_EGPOEN : RTC_GPOEN)
#define RTC_XGPOUT(n) (isE(n) ? RTC_EGPOUT : RTC_GPOUT)
#define RTC_XGPEN(n)  (isE(n) ? RTC_EGPEN : RTC_GPEN)
#define RTC_XGPS(n)   (isE(n) ? RTC_EGPS : RTC_GPS)
#define RTC_XGPIN(n)  (isE(n) ? RTC_EGPIN : RTC_GPIN)
#define RTC_XGPINTSTS(n)                                                       \
  (isE(n) ? RTC_EGPSTATUS : (isSpecIO(n) ? RTC_IRQSTS : RTC_STS))
#define RTC_XGPINTCLRSTS(n)                                                    \
  (isE(n) ? RTC_EGPSTATUS : (isSpecIO(n) ? RTC_IRQSTS : RTC_INTCLR))
#define RTC_XGPINTEN(n)                                                        \
  (isE(n) ? RTC_EGPINTE : (isSpecIO(n) ? RTC_CTRL : RTC_IRQ))
#define RTC_XGPINTPOL(n)                                                       \
  (isE(n) ? RTC_EGPPOL : (isSpecIO(n) ? RTC_CTRL : RTC_IRQ))

#define RTC_XGPINTPOL_OFFSET(n)                                                \
  (isE(n) ? RTC_EGPINTPOL_OFFSET(n) : RTC_GPINTPOL_OFFSET(n))
#define RTC_XGPINTPOL_MASK(n) (0x1 << RTC_XGPINTPOL_OFFSET(n))
#define RTC_XGPINTEN_OFFSET(n)                                                 \
  (isE(n) ? RTC_EGPINTEN_OFFSET(n) : RTC_GPINTEN_OFFSET(n))
#define RTC_XGPINTEN_MASK(n) (0x1 << RTC_XGPINTEN_OFFSET(n))
#define RTC_XGPINT_OFFSET(n)                                                   \
  (isE(n) ? RTC_EGPINT_OFFSET(n) : RTC_GPINT_OFFSET(n))
#define RTC_XGPINT_MASK(n) (0x1 << RTC_XGPINT_OFFSET(n))

#define RTC_SHAREIRQ_MAX 16

typedef struct rtc_gpio_sirq {
  int index;
  irq_handler_t handler;
  char *private_data;
} rtc_gpio_sirq_t;

typedef struct rtc_gpio {
  int irq;
  bool requested;
  const char *name;
  rtc_gpio_sirq_t sirq[RTC_SHAREIRQ_MAX];
} rtc_gpio_t;

int is_rtc(domain_t sysmode);
int rtc_get_mode(uint32_t index);
int rtc_set_mode(uint32_t range, int mode, uint32_t value);
int rtc_set_pull(uint32_t range, int en, uint32_t pattern);
int rtc_get_pull(uint32_t index);
int rtc_set_value(uint32_t range, uint32_t high);
int rtc_get_value(uint32_t index, int *mode);
void rtc_irq_eoi(int index);
int rtc_to_irq(int index);
void rtc_irq_enable(int index);
void rtc_irq_disable(int index);
int rtc_set_type(int index, int type);
int rtc_replace_irq(int index, irq_handler_t handler, int flags,
                    const char *name, void *dev);
int rtc_request_irq(int index, irq_handler_t handler, int flags,
                    const char *name, void *dev);
void rtc_info_set(int mode, int index, uint8_t val);
uint8_t rtc_info_get(int mode, int index);
bool is_wakeup_reset(void);
bool is_soft_reset(void);
void rtc_set_event(int event);
void rtc_set_resume_source(int source, bool only);
#endif

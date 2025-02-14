#ifndef __TIMER_H__
#define __TIMER_H__

#include <stdint.h>

#define DEBUG_TTC
#ifdef DEBUG_TTC
#define DEBUG_LOG_TTC(format, ...) printf(format, ##__VA_ARGS__)
#else
#define DEBUG_LOG_TTC(format, ...)
#endif

typedef void *timer_handle_t;
#define GET_BIT(x, bit)  ((x & (1 << bit)) >> bit) /*  check bit if 1 or 0*/

#define CLKCR_CSRC_ENABLE (1UL << 5) /*BIT5 0:pclk 1:ext-clk*/
#define CLKCR_PSE_ENABLE  (1UL << 0) /*BIT0 0:prescaled 1:define by CSRC*/
#define CLKCR_EXTE_ENABLE (1UL << 6) /*BIT6 0:         1:negative edge */ 


#define CCR_DISC_ENABLE   (1UL << 0) /* 默认1:关闭,打开:0*/
#define CCR_WEN_ENABLE    (1UL << 5)                                                    
#define CCR_RST_ENABLE    (1UL << 4) 
#define CCR_MCHE_ENABLE    (1UL << 3)        
#define CCR_WEN_WPOL_ENABLE   (1UL << 6) /*BIT5 0: Disable waveform output 1:enable  */                                 
#define CCR_INTE_ENABLE (1UL << 1) /*BIT1 0:OVERFLOW 1:INTERVAL  */
#define CCR_RST_ENABLE   (1UL << 4) /*BIT4 0:DISABLE 1:ENABLE  */
#define CCR_DECC_ENABLE  (1UL << 2) /*BIT2 0:DISABLE up 1:ENABLE down */

#define IER_EVNT_ENABLE  (1UL << 5) /*BIT5 0:DISABLE 1:ENABLE  */
#define IER_OVFL_ENABLE  (1UL << 4) /*BIT4 0:DISABLE 1:ENABLE  */
#define IER_ITRV_ENABLE  (1UL << 0) /*BIT0 0:DISABLE 1:ENABLE  Interval模式 中断开关*/    
#define IER_M1_ENABLE    (1UL << 1) /*BIT1 0:DISABLE 1:ENABLE  */
#define IER_M2_ENABLE    (1UL << 2) /*BIT2 0:DISABLE 1:ENABLE  */
#define IER_M3_ENABLE    (1UL << 3) /*BIT3 0:DISABLE 1:ENABLE  */

#define ETCR_ETEN_ENABLE (1UL << 0) /*BIT0 0:DISABLE 1:ENABLE  */
#define ETCR_ECM_ENABLE  (1UL << 1) /*BIT1 0:DISABLE 1:ENABLE  */
#define ETCR_EOV_ENABLE  (1UL << 2) /*BIT2 0:DISABLE 1:ENABLE  */
#define ETCR_ETTM_ENABLE (1UL << 3) /*BIT3 0:DISABLE 1:ENABLE  */
#define CVAL1 (1UL << 1)
#define CVAL0 (1UL << 0)

#define TIMER_CLK_CONTROL_C1 0x00
#define TIMER_CLK_CONTROL_C2 0x04
#define TIMER_CLK_CONTROL_C3 0x08
#define TIMER_CCR_CONTROL_C1 0x0C
#define TIMER_CCR_CONTROL_C2 0x10
#define TIMER_CCR_CONTROL_C3 0x14
#define TIMER_CVR_VALUE_C1   0x18
#define TIMER_CVR_VALUE_C2   0x1C
#define TIMER_CVR_VALUE_C3   0x20
#define TIMER_IVLR_VALUE_C1  0x24
#define TIMER_IVLR_VALUE_C2  0x28
#define TIMER_IVLR_VALUE_C3  0x2C
#define TIMER_MATCH1_C1      0x30
#define TIMER_MATCH1_C2      0x34
#define TIMER_MATCH1_C3      0x38
#define TIMER_MATCH2_C1      0x3c
#define TIMER_MATCH2_C2      0x40
#define TIMER_MATCH2_C3      0x44
#define TIMER_MATCH3_C1      0x48
#define TIMER_MATCH3_C2      0x4c
#define TIMER_MATCH3_C3      0x50
#define TIMER_ISR_C1         0x54
#define TIMER_ISR_C2         0x58
#define TIMER_ISR_C3         0x5C
#define TIMER_IER_C1         0x60
#define TIMER_IER_C2         0x64
#define TIMER_IER_C3         0x68
#define TIMER_ETCR_C1        0x6C
#define TIMER_ETCR_C2        0x70
#define TIMER_ETCR_C3        0x74
#define TIMER_ETVR_C1        0x78
#define TIMER_ETVR_C2        0x7C
#define TIMER_ETVR_C3        0x80

#define S_SYSM_TTC (0xD2F00800UL)
#define C_SYSM_TTC (0xC2F00800UL)
typedef void (*timer_event_cb_t)(
    timer_handle_t handle); /// : TIMER Event call back.

typedef enum {
  TIMER_OVERFLOW_INTERRUPT       = 0,
  TIMER_INTERVAL_INTERRUPT       = 1,
  TIMER_EVENTCOUNTMODE_INTERRUPT = 2,
  TIMER_MATCH1_INTERRUPT         = 3,
  TIMER_MATCH2_INTERRUPT         = 4,
  TIMER_MATCH3_INTERRUPT         = 5,
} timer_interrupt_e;
#if 0
typedef struct {
	uint32_t OutputHz;	/* Output frequency */
	uint16_t Interval;	/* Interval value */
	uint8_t Prescaler;	/* Prescaler value */
	uint32_t Options;	  /* Option settings */
} TmrCntrSetup;
#endif
typedef struct {
  uint8_t idx;
  uint8_t timeridx;
  uint64_t base;
  uint32_t irq;
  timer_event_cb_t cb_event;
  uint32_t mode;
  uint32_t risedownflag;
  uint32_t inittime;
  uint32_t endtime;
  uint32_t bytes;
  uint8_t waveformflag;
  uint8_t interruptflag;
  timer_interrupt_e enum_interrupt;
} timer_priv_t;

typedef struct {
 uint8_t  match1_en;
 uint8_t  match2_en;
 uint8_t  match3_en;
 uint32_t  match1;
 uint32_t  match2;
 uint32_t  match3;
} timer_match_t;

typedef enum {
  TIMER_MODE_OVERFLOW       = 0,
  TIMER_MODE_INTERVAL       = 1,
  TIMER_MODE_WAREFORM       = 2,
  TIMER_MODE_EVENTCOUNTMODE = 3,
  TIMER_MODE_TEST = 4,
} timer_mode_e;
#if 0 
static TmrCntrSetup SettingsTable[1] = {
      {10, 0, 0, 0},    /* Ticker timer counter initial setup, only output freq */
};
#endif
/**
\brief TIMER Status
*/
typedef struct {
    uint32_t active   : 1;                        ///< timer active flag
    uint32_t timeout  : 1;                        ///< timeout flag
} timer_status_t;

timer_handle_t itcs_timer_init(timer_handle_t handle,
                                      timer_event_cb_t cb_event);
int32_t itcs_timer_start(timer_handle_t handle);
int itcs_timer_irq(int32_t idx, void *args);
int32_t itcs_timer_config(timer_handle_t handle, timer_match_t match);
int set_clock_type(timer_handle_t handle,const char *module);
int set_freq_div(timer_handle_t handle,uint32_t divnum);
int32_t itcs_timer_stop(timer_handle_t handle); 

timer_handle_t csi_timer_initialize(int32_t idx, timer_event_cb_t cb_event);
int32_t csi_timer_uninitialize(timer_handle_t handle);
int32_t csi_timer_config(timer_handle_t handle, uint32_t mode);
int32_t csi_timer_set_timeout(timer_handle_t handle, uint32_t timeout);
int32_t csi_timer_start(timer_handle_t handle);
int32_t csi_timer_stop(timer_handle_t handle);

#endif /* __TIMER_H__ */

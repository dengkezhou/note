#ifndef __WDT_H__
#define __WDT_H__

#include <stdint.h>
#include <irq.h>

#define CDNS_WDT_ENABLE  1
#define CDNS_WDT_DISABLE 0
#define CDNS_RET_SUCCESS 0
#define CDNS_RET_FAILED  1


#define CDNS_WDT_ADDR_MODE    (0)
#define CDNS_WDT_ADDR_CTRL    (0x04)
#define CDNS_WDT_ADDR_RESTART (0x08)
#define CDNS_WDT_ADDR_STATUS  (0x0C)

#define CDNS_WDT_MR_WDEN_MASK  (0x01)
#define CDNS_WDT_MR_RSTEN_MASK (0x02)
#define CDNS_WDT_MR_IRQEN_MASK (0x04)
#define CDNS_WDT_MR_EXTEN_MASK (0x08)
#define CDNS_WDT_MR_RSTLN_MASK (0x70)
#define CDNS_WDT_MR_IRQLN_MASK (0x180)
#define CDNS_WDT_MR_EXTLN_MASK (0xE00)
#define CDNS_WDT_MR_ZKEY_MASK  (0x00FFF000)

#define CDNS_WDT_CCR_CLKSEL_MASK  (0x03)
#define CDNS_WDT_CCR_CRV_MASK     (0x3C)
#define CDNS_WDT_CCR_CKEY_MASK    (0x3FFC0)

#define CDNS_WDT_RR_RSTKEY_MASK    (0xFFFF)

#define CDNS_WDT_SR_STATUSKEY_MASK (0x1)


#ifdef DEBUG_WDT
#define DEBUG_WDT_LOG(format, ...) printf(format, ##__VA_ARGS__)
#else
#define DEBUG_WDT_LOG(format, ...) 
#endif

typedef enum { MODE_RST = 0x1, MODE_IRQ = 0x2, MODE_EXT = 0x4 } WDT_MODE;

typedef enum {
  CPU_WDT = 0,
  SAP_WDT,
} WDT;

typedef struct wdt_handler_s wdt_handler_t;
typedef void (*wdt_callback) (wdt_handler_t* ) ;

typedef struct wdt_init_s{
    WDT WDTx;
    uint8_t mode;
    uint32_t timeout_ms;
    wdt_callback callback;
}wdt_init_t;

struct wdt_handler_s{
    struct wdt_init_s init;
    uint32_t crv;
    unsigned char prescale;
};

struct wdt_handler_s* itcs_wdt_init(struct wdt_init_s * init);
uint32_t itcs_wdt_start(struct wdt_handler_s* handler);
uint32_t itcs_wdt_stop(struct wdt_handler_s* handler);
uint32_t itcs_wdt_mode_config(struct wdt_handler_s* handler, bool enable, WDT_MODE mode);
uint32_t itcs_wdt_counter_ctrl(struct wdt_handler_s* handler, uint32_t crv, unsigned char prescale);
uint32_t itcs_wdt_feed(struct wdt_handler_s* handler);

#endif /*__WDT_H__*/

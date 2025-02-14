/*
 * Copyright (C) intchains Holding Limited
 */

/******************************************************************************
 * @file     wdt.c
 * @brief    watch dog Driver
 * @version  V1.0
 * @date     03.28 2022
 * @name     wdt
 * @author   jason.liu
 ******************************************************************************/
#include <common.h>
#include <asm/io.h>
#include <wdt.h>
#include <malloc.h>

// sap reset: reset sap & cpu
// sap external: unused
// cpu reset: reset cpu
// cpu external: reset sap & cpu

static unsigned long wdt_get_base_addr(WDT WDTx){
  switch(WDTx){
    case CPU_WDT: return ITCS_C_WDT_BASE;
    break;
    case SAP_WDT: return ITCS_S_WDT_BASE;
    break;
    default: return 0;
    break;
  }
} 

static int wdt_irqhandler(int irq, void *args) {
  struct wdt_handler_s* handler = (struct wdt_handler_s*)(args);
  DEBUG_WDT_LOG("wdt%d irq trigger\n",(int)(handler->init.WDTx));
  if(handler->init.callback){
    handler->init.callback(handler);
  }
  return 0;
}

static uint32_t wdt_register_irq(struct wdt_handler_s* handler) {
  int ret = CDNS_RET_FAILED; 
  switch(handler->init.WDTx){
    case CPU_WDT: 
        ret = request_irq(C_WDT_IRQn, wdt_irqhandler, "cpu-wdt", handler);
        DEBUG_WDT_LOG("cpu-wdt register irq!\n");
    break;
    case SAP_WDT: 
        ret = request_irq(S_WDT_IRQn, wdt_irqhandler, "sap-wdt", handler);
        DEBUG_WDT_LOG("sap-wdt register irq!\n");
    break;
    default:
    break;
  }

  if(ret)
    return CDNS_RET_FAILED;

  return CDNS_RET_SUCCESS;
}

struct wdt_handler_s* itcs_wdt_init(struct wdt_init_s * init){
    struct wdt_handler_s * handler;
    uint32_t ret;
    domain_t domain;
    int pre_val;

    handler = (struct wdt_handler_s *)malloc(sizeof(struct wdt_handler_s));
    if(handler == NULL){
        DEBUG_WDT_LOG("wdt%d malloc error!\n",(int)(handler->init.WDTx));
        return NULL;
    }

    memset(handler, 0, sizeof(struct wdt_handler_s));

    handler->init = *init;


    //module enable
    if(init->WDTx == CPU_WDT){
        domain = CPU;
    }else if(init->WDTx == SAP_WDT){
        domain = SAP;
    }else{
        free(handler);
        DEBUG_WDT_LOG("wrong wdt instance name!\n");
        return NULL;
    }

    itcs_module_enable(domain, "wdt");
    
    ret = itcs_wdt_stop(handler);
    if (ret != CDNS_RET_SUCCESS) {
        free(handler);
        DEBUG_WDT_LOG("wdt%d stop error!\n",(int)(handler->init.WDTx));
        return NULL;
    }

    if(handler->init.mode & MODE_RST){
        itcs_wdt_mode_config(handler, true, MODE_RST);
    }else{
        itcs_wdt_mode_config(handler, false, MODE_RST);
    }

    if(handler->init.mode & MODE_IRQ){
        itcs_wdt_mode_config(handler, true, MODE_IRQ);
    }else{
        itcs_wdt_mode_config(handler, false, MODE_IRQ);
    }
    
    if(handler->init.mode & MODE_EXT){
        itcs_wdt_mode_config(handler, true, MODE_EXT);
    }else{
        itcs_wdt_mode_config(handler, false, MODE_EXT);
    }

    ret = wdt_register_irq(handler);
    if (ret != CDNS_RET_SUCCESS) {
        free(handler);
        DEBUG_WDT_LOG("wdt%d register irq error!\n",(int)(handler->init.WDTx));
        return NULL;
    }
    
    int clk = itcs_module_get_clock(domain, "apb");
    int max_timeout_ms_prescale_8 = (0x10000 * 1000)/(clk/8);
    if(handler->init.timeout_ms < max_timeout_ms_prescale_8){
      handler->prescale = 0;
      pre_val = 8;
    }else if(handler->init.timeout_ms < (max_timeout_ms_prescale_8 * 8)){
      handler->prescale = 1;
      pre_val = 64;
    }else if(handler->init.timeout_ms < (max_timeout_ms_prescale_8 * 64)){
      handler->prescale = 2;
      pre_val = 512;
    }else if(handler->init.timeout_ms < (max_timeout_ms_prescale_8 * 512)){
      handler->prescale = 3;
      pre_val = 4096;
    }else{
      free(handler);
      DEBUG_WDT_LOG("wdt pclk=%d  timeout_ms=%d, max_timeout_ms=%d\n",clk,handler->init.timeout_ms, max_timeout_ms_prescale_8);
      return NULL;
    }

    DEBUG_WDT_LOG("wdt pclk=%d  timeout_ms=%d, handler->prescale=%d\n",clk,handler->init.timeout_ms,handler->prescale);

    handler->crv = (handler->init.timeout_ms * (clk/(1000*pre_val)) ) / 0x1000;
    if(handler->crv > 0xf){
        handler->crv = 0xf;
    }

    DEBUG_WDT_LOG("crv=0x%x\n",handler->crv);
    ret = itcs_wdt_counter_ctrl(handler, handler->crv, handler->prescale);

    if (ret != CDNS_RET_SUCCESS) {
        free(handler);
        DEBUG_WDT_LOG("wdt%d ctrl error!\n",(int)(handler->init.WDTx));
        return NULL;
    }
    if(handler)
      itcs_wdt_feed(handler);
    return handler;
}

uint32_t itcs_wdt_start(struct wdt_handler_s* handler) {
  DEBUG_WDT_LOG("-------------wdt%d start!-----------------\n",(int)(handler->init.WDTx));
  WDT WDTx =  handler->init.WDTx;
  unsigned long base = wdt_get_base_addr(WDTx);
  uint32_t value                  = readl(base+CDNS_WDT_ADDR_MODE);
  value |= CDNS_WDT_MR_WDEN_MASK;
  value |= 0xABC000;
  //DEBUG_WDT_LOG("wdt%d base=0x%x!, value=0x%x\n",(int)(handler->init.WDTx),base,value);
  
  writel(value, base+CDNS_WDT_ADDR_MODE);
  #ifdef DEBUG_WDT
    value     = readl(base+CDNS_WDT_ADDR_MODE);
    //DEBUG_WDT_LOG("wdt%d mr=0x%x!\n",(int)(handler->init.WDTx),value);
  #endif // DEBUG
  //DEBUG_WDT_LOG("------------------------------------------\n\n");
  return CDNS_RET_SUCCESS;
}

uint32_t itcs_wdt_stop(struct wdt_handler_s* handler) {
  DEBUG_WDT_LOG("-------------wdt%d stop!------------------\n",(int)(handler->init.WDTx));
  WDT WDTx =  handler->init.WDTx;
  unsigned long base = wdt_get_base_addr(WDTx);
  uint32_t value                  = readl(base+CDNS_WDT_ADDR_MODE);
  DEBUG_WDT_LOG("mr raw value=0x%x\n",value);
  value &= ~CDNS_WDT_MR_WDEN_MASK;
  value |= 0xABC000;
  DEBUG_WDT_LOG("wdt%d base=0x%x!, value=0x%x\n",(int)(handler->init.WDTx),base,value);
  writel(value, base+CDNS_WDT_ADDR_MODE);
#ifdef DEBUG_WDT
  value     = readl(base+CDNS_WDT_ADDR_MODE);
  DEBUG_WDT_LOG("wdt%d mr=0x%x!\n",(int)(handler->init.WDTx),value);
#endif // DEBUG
  DEBUG_WDT_LOG("------------------------------------------\n\n");
  return CDNS_RET_SUCCESS;
}

uint32_t itcs_wdt_mode_config(struct wdt_handler_s* handler, bool enable, WDT_MODE mode) {
  DEBUG_WDT_LOG("-------------wdt%d config!----------------\n",(int)(handler->init.WDTx));
  WDT WDTx =  handler->init.WDTx;
  unsigned long base = wdt_get_base_addr(WDTx);
  uint32_t value     = readl(base+CDNS_WDT_ADDR_MODE);
  DEBUG_WDT_LOG("mr raw value=0x%x\n",value);
  value |= 0xABC000;
  if(enable){
    handler->init.mode |= ((uint8_t) mode);
  }else{
    handler->init.mode &= ( (~(uint8_t)mode) & (MODE_RST|MODE_IRQ|MODE_EXT));
  }


  switch (mode) {
  case MODE_RST:
    if (enable == true) {
      value |= CDNS_WDT_MR_RSTEN_MASK;
    } else {
      value &= ~CDNS_WDT_MR_RSTEN_MASK;
    }

    value |=  CDNS_WDT_MR_RSTLN_MASK;
    writel(value, base+CDNS_WDT_ADDR_MODE);
    break;
  case MODE_IRQ:
    if (enable == true) {
      value |= CDNS_WDT_MR_IRQEN_MASK;
    } else {
      value &= ~CDNS_WDT_MR_IRQEN_MASK;
    }

    value |=  CDNS_WDT_MR_IRQLN_MASK;
    writel(value, base+CDNS_WDT_ADDR_MODE);
    break;
  case MODE_EXT:
   if (enable == true) {
      value |= CDNS_WDT_MR_EXTEN_MASK;
    } else {
      value &= ~CDNS_WDT_MR_EXTEN_MASK;
    }

    value |=  CDNS_WDT_MR_EXTLN_MASK;
    writel(value, base+CDNS_WDT_ADDR_MODE);
    break;
  default:
    break;
  }
  DEBUG_WDT_LOG("wdt%d base=0x%x!, value=0x%x\n",(int)(handler->init.WDTx),base,value);
#ifdef DEBUG_WDT
  value     = readl(base+CDNS_WDT_ADDR_MODE);
  DEBUG_WDT_LOG("wdt%d mr=0x%x!\n",(int)(handler->init.WDTx),value);
#endif // DEBUG
  DEBUG_WDT_LOG("------------------------------------------\n\n");
  return CDNS_RET_SUCCESS;
}

uint32_t itcs_wdt_counter_ctrl(struct wdt_handler_s* handler, uint32_t crv, unsigned char prescale) {
  DEBUG_WDT_LOG("-------------wdt%d control!----------------\n",(int)(handler->init.WDTx));
  WDT WDTx =  handler->init.WDTx;
  unsigned long base = wdt_get_base_addr(WDTx);
  uint32_t value     = readl(base+CDNS_WDT_ADDR_CTRL);
  DEBUG_WDT_LOG("ccr raw value=0x%x\n",value);
  handler->crv = crv;
  handler->prescale = prescale;

  if (prescale < 4) {
    value &= ~CDNS_WDT_CCR_CLKSEL_MASK;
    value |= prescale;
  } else {
    printf("prescale is out of range, must be 0~3!\n");
    return CDNS_RET_FAILED;
  }

  if (crv < 0x10) {
    value &= ~CDNS_WDT_CCR_CRV_MASK;
    value |= (crv<<2);
  } else {
    printf("crv is out of range, must be 0~0xffff!\n");
    return CDNS_RET_FAILED;
  }
  value &= ~CDNS_WDT_CCR_CKEY_MASK;
  value |= (0x248 << 6);
  DEBUG_WDT_LOG("wdt%d base=0x%x, value=0x%x\n",(int)(handler->init.WDTx),base,value);
  writel(value, base+CDNS_WDT_ADDR_CTRL);
#ifdef DEBUG_WDT
  value     = readl(base+CDNS_WDT_ADDR_CTRL);
  DEBUG_WDT_LOG("wdt%d ccr=0x%x!\n",(int)(handler->init.WDTx),value);
#endif // DEBUG
  DEBUG_WDT_LOG("------------------------------------------\n\n");
  return CDNS_RET_SUCCESS;
}

uint32_t itcs_wdt_feed(struct wdt_handler_s* handler) {
  DEBUG_WDT_LOG("-------------wdt%d restart!---------------\n",(int)(handler->init.WDTx));
  WDT WDTx =  handler->init.WDTx;
  unsigned long base = wdt_get_base_addr(WDTx);
  
  // this is a write only register
  writel(0x1999, base+CDNS_WDT_ADDR_RESTART);
  DEBUG_WDT_LOG("wdt%d base=0x%x, value=0x1999\n",(int)(handler->init.WDTx),base);
  DEBUG_WDT_LOG("------------------------------------------\n\n");
  return CDNS_RET_SUCCESS;
}

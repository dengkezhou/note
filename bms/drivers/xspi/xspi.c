#include <xspi.h>
#include <irq.h>
#include <pads.h>
#include <malloc.h>
#include "xspi_init.h"
#include "dma_ctrl.h"
#include <cache.h>

#define check_req_irq_ret(ret)                                                 \
  do {                                                                         \
    if (ret) {                                                                 \
      return ret;                                                              \
    }                                                                          \
  } while (0)

#define MAX_CDMA_COMMANDS_PER_THREAD 2

#define XSPI_IRTR_STATUS_REG  0x0110 
#define XSPI_IRTR_REG_OFFSET  0x0114 

#define	XSPI_IRQ_GLOBAL_EN    0x80000000U
#define	XSPI_IRQ_SDMA_TRIGGER 0x00200000U


// callback functions registerd with driver (these functions normally are
// provided by user)
void ospi_direct_sdma_err_cb(XSPI_PrivateData *pD) {
  vDbgMsg(DBG_GEN_MSG, DBG_FYI, "Interrupt event 1 arised\n");
}

void ospi_direct_invalid_cmd_seq_cb(XSPI_PrivateData *pD) {
  vDbgMsg(DBG_GEN_MSG, DBG_FYI, "Interrupt event 2 arised\n");
}

void qspi_direct_sdma_err_cb(XSPI_PrivateData *pD) {
  vDbgMsg(DBG_GEN_MSG, DBG_FYI, "Interrupt event 1 arised\n");
}

void qspi_direct_invalid_cmd_seq_cb(XSPI_PrivateData *pD) {
  vDbgMsg(DBG_GEN_MSG, DBG_FYI, "Interrupt event 2 arised\n");
}

void ospi_direct_sdma_cb(XSPI_PrivateData *pD, XSPI_DirectSdmaTransInfo sdmaInfo) {
    //DEBUG_XSPI_LOG("ospi direct sdma cb, direction = %d, directSdmaBuff = %p, transferSize = %d\n", sdmaInfo.direction, sdmaInfo.directSdmaBuff,sdmaInfo.transferSize);
    //itcs_dcache_flush();
    if(sdmaInfo.direction == XSPI_DATA_TRANS_DIR_READ){
        dma_read_data((uint64_t)sdmaInfo.directSdmaBuff, (uint64_t)OSPI_SDMA_BASE, sdmaInfo.transferSize);
    }else{
        dma_write_data((uint64_t)sdmaInfo.directSdmaBuff, (uint64_t)OSPI_SDMA_BASE, sdmaInfo.transferSize);
    }
    dma_wait();
    //itcs_dcache_invalid();
}

void ospi_stig_sdma_cb(XSPI_PrivateData* pD, XSPI_StigSdmaIrqInfo irqInfo)
{
    //DEBUG_XSPI_LOG("ospi stig sdma cb direction = %d, stigSdmaBuff = %p, transferSize = %d\n", irqInfo.direction, irqInfo.stigSdmaBuff,irqInfo.transferSize);
    //itcs_dcache_flush();
    if(irqInfo.direction == XSPI_DATA_TRANS_DIR_READ){
        dma_read_data((uint64_t)irqInfo.stigSdmaBuff, (uint64_t)OSPI_SDMA_BASE, irqInfo.transferSize);
    }else{
        dma_write_data((uint64_t)irqInfo.stigSdmaBuff, (uint64_t)OSPI_SDMA_BASE, irqInfo.transferSize);
    }

    dma_wait();
    //itcs_dcache_invalid();
}

void qspi_direct_sdma_cb(XSPI_PrivateData *pD, XSPI_DirectSdmaTransInfo sdmaInfo) {
    //DEBUG_XSPI_LOG("qspi direct sdma cb, direction = %d, directSdmaBuff = %p, transferSize = %d\n", sdmaInfo.direction, sdmaInfo.directSdmaBuff,sdmaInfo.transferSize);
    //itcs_dcache_flush();
    if(sdmaInfo.direction == XSPI_DATA_TRANS_DIR_READ){
        dma_read_data((uint64_t)sdmaInfo.directSdmaBuff, (uint64_t)QSPI_SDMA_BASE, sdmaInfo.transferSize);
    }else{
        dma_write_data((uint64_t)sdmaInfo.directSdmaBuff, (uint64_t)QSPI_SDMA_BASE, sdmaInfo.transferSize);
    }
    dma_wait();
    //itcs_dcache_invalid();
}

void qspi_stig_sdma_cb(XSPI_PrivateData* pD, XSPI_StigSdmaIrqInfo irqInfo)
{
    //DEBUG_XSPI_LOG("qspi stig sdma cb direction = %d, stigSdmaBuff = %p, transferSize = %d\n", irqInfo.direction, irqInfo.stigSdmaBuff,irqInfo.transferSize);
    //itcs_dcache_flush();
    if(irqInfo.direction == XSPI_DATA_TRANS_DIR_READ){
        dma_read_data((uint64_t)irqInfo.stigSdmaBuff, (uint64_t)QSPI_SDMA_BASE, irqInfo.transferSize);
    }else{
        dma_write_data((uint64_t)irqInfo.stigSdmaBuff, (uint64_t)QSPI_SDMA_BASE, irqInfo.transferSize);
    }
    dma_wait();
    //itcs_dcache_invalid();
}

int cdns_xspi_config(XSPI_HandleTypeDef *profile) {
  uint32_t events; // interrupts to be enabled
  XSPI_Callbacks cb;
  // Get and Set callbacks
  if (profile->drv->getCallbacks(profile->pD, &cb) != 0) {
    vDbgMsg(DBG_GEN_MSG, DBG_FYI, "Error: getCallbacks\n");
    return -1;
  }
  if(profile->init.XSPIx == OSPI){
    cb.sdmaCb.stigSdmaTransactionHandler         = ospi_stig_sdma_cb;
    cb.sdmaCb.directSdmaTransactionHandler       = ospi_direct_sdma_cb;
    cb.sdmaCb.sdmaErrorHandler                   = ospi_direct_sdma_err_cb;
    cb.directErrorCb.dirInvalidCommandSeqHandler = ospi_direct_invalid_cmd_seq_cb;
  }else{
    cb.sdmaCb.stigSdmaTransactionHandler         = qspi_stig_sdma_cb;
    cb.sdmaCb.directSdmaTransactionHandler       = qspi_direct_sdma_cb;
    cb.sdmaCb.sdmaErrorHandler                   = qspi_direct_sdma_err_cb;
    cb.directErrorCb.dirInvalidCommandSeqHandler = qspi_direct_invalid_cmd_seq_cb;
  }


  //profile->cb = cb;
  memcpy(&profile->cb, &cb, sizeof(XSPI_Callbacks));

  if (profile->drv->setCallbacks(profile->pD,  profile->cb) != 0) {
    vDbgMsg(DBG_GEN_MSG, DBG_FYI, "Error: setCallbacks\n");
    return -1;
  }

  // Enable interrupts
  if (profile->drv->getEventEnable(profile->pD, &events) != 0) {
    vDbgMsg(DBG_GEN_MSG, DBG_FYI, "Error: getEventEnable\n");
    return -1;
  }

  events = XSPI_EVENT_DWM_CMD_ERROR | XSPI_EVENT_SDMA_ERROR;

  if (profile->drv->setEventEnable(profile->pD, events) != 0) {
    vDbgMsg(DBG_GEN_MSG, DBG_FYI, "Error: setEventEnable\n");
    return -1;
  }

  if (profile->drv->start(profile->pD) != 0) {
    vDbgMsg(DBG_GEN_MSG, DBG_FYI, "Error: Driver->start\n");
    return -1;
  }

  if (profile->init.ClockMode == 0)
    profile->drv->setSpiClockMode(profile->pD, XSPI_SPI_CLOCK_MODE_0);
  else
    profile->drv->setSpiClockMode(profile->pD, XSPI_SPI_CLOCK_MODE_3);

  return 0;
}

static int cdns_xspi_irq_handler(int irq, void *args) {
  XSPI_HandleTypeDef *profile = (XSPI_HandleTypeDef *)args;
  //DEBUG_XSPI_LOG("%s irq arrive.\n",(profile->reg_base == ITCS_C_OSPI_BASE) ? "ospi":"qspi");
  writel(0x0, (profile->reg_base  + XSPI_IRTR_REG_OFFSET));
  profile->drv->isr(profile->pD);
  // error interrupt process
  return 0;
}

static int cdns_xspi_register_irq(XSPI_e XSPIx, XSPI_HandleTypeDef *profile) {
  int ret = 0;
  switch (XSPIx) {
  case QSPI:
    ret = request_irq(C_XSPI1_IRQn, cdns_xspi_irq_handler, "qspi-irq",
                      (void *)profile);
    check_req_irq_ret(ret);
    break;
  case OSPI:
    ret = request_irq(C_XSPI0_IRQn, cdns_xspi_irq_handler, "ospi-irq",
                      (void *)profile);
    check_req_irq_ret(ret);
    break;

  default:
    return -1;
    break;
  }

  return 0;
}

#if 0
static int cdns_xspi_module_enable(XSPI_e SPIx, bool enable) {
  char *module_name = NULL;
  switch (SPIx) {
  case QSPI:
    module_name = "qspi";
    break;
  case OSPI:
    module_name = "ospi";
    break;
  }
  if (enable)
    itcs_module_enable(CPU, module_name);
  else
    itcs_module_disable(CPU, module_name);
  return 0;
}
#endif
static int cdns_xspi_module_set_clock(XSPI_e SPIx) {
  char *module_name = NULL;
  switch (SPIx) {
  case QSPI:
    module_name = "qspi";
    break;
  case OSPI:
    module_name = "ospi";
    break;
  }
  itcs_module_set_clock(CPU, module_name, NULL, 25000000, false);
  return 0;
}


static int cdns_xspi_module_set_pads(XSPI_e xSPIx) {
  switch (xSPIx) {
  case QSPI:
    itcs_module_set_pads(CPU, FPGA_BIT_V_EMMC, "qspi");
    break;
  case OSPI:
    itcs_module_set_pads(CPU, FPGA_BIT_V_OSPI, "ospi");
    break;
  }
  
  return 0;
}

XSPI_HandleTypeDef *itcs_xspi_init(XSPI_InitTypeDef *init) {
  XSPI_Config xSpiDrvCfg    = {0};
  XSPI_SysReq xSpiDrvSysReq = {0};
  uint32_t result           = 0;

  XSPI_HandleTypeDef *handler = 
      (XSPI_HandleTypeDef *)malloc(sizeof(XSPI_HandleTypeDef));
  if (handler == NULL) {
    printf("Malloc memory for XSPI_HandleTypeDef failed!\n");
    return NULL;
  }
  memset(handler, 0, sizeof(XSPI_HandleTypeDef));
  
  memcpy(&(handler->init), init, sizeof(XSPI_InitTypeDef));

  if(cdns_xspi_before_driver_init(init->XSPIx)){
    vDbgMsg(DBG_GEN_MSG, DBG_FYI, "Error: xspi low level init!\n");
    free(handler);
    return NULL;
  }
  
  cdns_xspi_module_set_pads(init->XSPIx);
  cdns_xspi_module_set_clock(init->XSPIx);

  vDbgMsg(DBG_GEN_MSG, DBG_FYI, "Creating XSPI Core Driver instance\n");
  handler->drv = XSPI_GetInstance();
  if(handler->drv == NULL) {
    vDbgMsg(DBG_GEN_MSG, DBG_FYI, "XSPI_GetInstance failed\n");
    free(handler);
    return NULL;
  }

  if (init->XSPIx == QSPI) {
    vDbgMsg(DBG_GEN_MSG, DBG_FYI, "XSPI_Init QSPI, 0x%x\n",ITCS_C_QSPI_BASE);
    xSpiDrvCfg.regsBase = (volatile XSPI_Regs *)ITCS_C_QSPI_BASE;
    handler->reg_base = ITCS_C_QSPI_BASE;
  } else {
    vDbgMsg(DBG_GEN_MSG, DBG_FYI, "XSPI_Init OSPI, 0x%x\n",ITCS_C_OSPI_BASE);
    xSpiDrvCfg.regsBase = (volatile XSPI_Regs *)ITCS_C_OSPI_BASE;
    handler->reg_base = ITCS_C_OSPI_BASE;
  }

  xSpiDrvCfg.cdmaCmdsMaxNum = MAX_CDMA_COMMANDS_PER_THREAD;

  result = handler->drv->probe(&xSpiDrvCfg, &xSpiDrvSysReq);
  if (result != 0) {
    vDbgMsg(DBG_GEN_MSG, DBG_FYI, "Error: drv ->probe! result=%d\n",result);
    free(handler);
    return NULL;
  }

  if ((xSpiDrvCfg.cdmaCmdsDescBase =
           (uintptr_t)malloc(xSpiDrvSysReq.cdmaCmdsDescTotalSize)) == 0) {
    vDbgMsg(DBG_GEN_MSG, DBG_FYI, "Error: allocating driver data\n");
    free(handler);
    return NULL;
  }
  memset((void *)xSpiDrvCfg.cdmaCmdsDescBase, 0, xSpiDrvSysReq.cdmaCmdsDescTotalSize );

  if ((xSpiDrvCfg.privateDataBase =
           (uintptr_t)malloc(xSpiDrvSysReq.privateDataSize)) == 0) {
    vDbgMsg(DBG_GEN_MSG, DBG_FYI, "Error: allocating driver private data\n");
    if (xSpiDrvCfg.cdmaCmdsDescBase != 0) {
      free((void *)xSpiDrvCfg.cdmaCmdsDescBase);
      xSpiDrvCfg.cdmaCmdsDescBase = 0;
    }
    free(handler);
    return NULL;
  }
  memset((void *)xSpiDrvCfg.privateDataBase, 0, xSpiDrvSysReq.privateDataSize );
  
  handler->pD = (XSPI_PrivateData *)xSpiDrvCfg.privateDataBase;

  if ((result = handler->drv->init(handler->pD, &xSpiDrvCfg)) != 0) {
    vDbgMsg(DBG_GEN_MSG, DBG_FYI, "Error: Driver ->init! result=%d\n",result);
    free(handler);
    return NULL;
  }
  
  writel(0x0, (handler->reg_base  + XSPI_IRTR_REG_OFFSET));

  /* Register irq */
  if (cdns_xspi_register_irq(init->XSPIx, handler)) {
    free(handler);
    return NULL;
  }

  if (cdns_xspi_config(handler)) {
    vDbgMsg(DBG_GEN_MSG, DBG_FYI, "Error: xspi config!\n");
    free(handler);
    return NULL;
  }
  DEBUG_XSPI_LOG("[XSPI] xspi init done\n");
  return handler;
}

int cdns_xspi_send_acmd_pio_command(XSPI_HandleTypeDef *xspi_handler,
                                    XSPI_PioCommand *cmd) {

  XSPI_OBJ *xSpiIf         = xspi_handler->drv;
  XSPI_PrivateData *xSpiPd = xspi_handler->pD;
  XSPI_PioCommand *pioCmd  = cmd;
  XSPI_WorkMode work_mode;
  uint8_t threadNum = 0U;

  xSpiIf->getWorkMode(xSpiPd, &work_mode);
  if (work_mode != XSPI_WORK_MODE_AUTO_COMMAND) {
    xSpiIf->setWorkMode(xSpiPd, XSPI_WORK_MODE_AUTO_COMMAND);
  }
  xSpiIf->sendPioCommand(xSpiPd, threadNum, pioCmd);
  do {
    udelay(10);
    xSpiIf->isr(xSpiPd);
    xSpiIf->getPioCommandStatus(xSpiPd, threadNum, pioCmd);
  } while (pioCmd->statusInfo.status == XSPI_COMMAND_STATUS_PENDING);

  // normal: XSPI_COMMAND_STATUS_SUCCESS
  return pioCmd->statusInfo.status;
}

int cdns_xspi_send_acmd_cdma_command(XSPI_HandleTypeDef *xspi_handler,
                                     XSPI_CdmaCommand *cmd) {
  XSPI_OBJ *xSpiIf          = xspi_handler->drv;
  XSPI_PrivateData *xSpiPd  = xspi_handler->pD;
  XSPI_CdmaCommand *cdmaCmd = cmd;
  XSPI_WorkMode work_mode;

  xSpiIf->getWorkMode(xSpiPd, &work_mode);
  if (work_mode != XSPI_WORK_MODE_AUTO_COMMAND) {
    xSpiIf->setWorkMode(xSpiPd, XSPI_WORK_MODE_AUTO_COMMAND);
  }
  /*
  xSpiIf->sendCdmaCommand(xSpiPd, threadNum, cdmaCmd);
  do {
    xSpiIf->isr(xSpiPd);
    xSpiIf->getCdmaCommandStatus(xSpiPd, threadNum, cdmaCmd);
  } while (cdmaCmd->statusInfo.status == XSPI_COMMAND_STATUS_PENDING);
  */
  XSPI_CdmaCommandChain cdmaChain = { 0 };
  cdmaChain.chain = cdmaCmd;
  cdmaChain.chainLength = 1U;
  cdmaChain.thread = 0;
  xSpiIf->sendCdmaCommandChain(xSpiPd, &cdmaChain);
  do {
      // Delay();
      xSpiIf->isr(xSpiPd);
      xSpiIf->getCdmaChainStatus(xSpiPd, &cdmaChain);
  } while (!cdmaChain.chainStatus.isCompleted);
  return 0;
}

int cdns_xspi_send_direct_command(XSPI_HandleTypeDef *xspi_handler,
                                  XSPI_DirectCmd *cmd) {

  XSPI_OBJ *xSpiIf          = xspi_handler->drv;
  XSPI_PrivateData *xSpiPd  = xspi_handler->pD;
  XSPI_DirectCmd *directCmd = cmd;
  //XSPI_WorkMode work_mode;
  XSPI_DirectModeConfig directModeCfg;
  uint32_t addr, base;

/* Set direct mode config */
  if (xSpiIf->getDirectModeConfig(xSpiPd, &directModeCfg) != 0) {
    printf("XSPI get direct mode config failed\n");
    return -1;
  }
  
  directModeCfg.disableAutoPoll = false;
  directModeCfg.disableAutoWelInstr = false;
  directModeCfg.disXipMb = false;
  directModeCfg.enXipMb = false;
  directModeCfg.bankSelect = 0;
  directModeCfg.remapAddrEn = true;
  if(xspi_handler->init.XSPIx == OSPI){
    directModeCfg.remapAddrVal = OSPI_SDMA_BASE;
    addr = OSPI_SDMA_BASE;
    base = ITCS_C_OSPI_BASE;
  }else{
    directModeCfg.remapAddrVal = QSPI_SDMA_BASE;
    addr = QSPI_SDMA_BASE;
    base = ITCS_C_QSPI_BASE;
  }
  

  if (xSpiIf->setDirectModeConfig(xSpiPd, (const XSPI_DirectModeConfig *)&directModeCfg) != 0) {
    printf("XSPI set direct mode config failed\n");
    return -1;
  }

  /* Set direct mode */
  if (xSpiIf->setWorkMode(xSpiPd, (const XSPI_WorkMode)XSPI_WORK_MODE_DIRECT) != 0) {
    printf("XSPI set work mode failed\n");
    return -1;
  }
  
  // enable irq or dma
  //writel((XSPI_IRQ_SDMA_TRIGGER|XSPI_IRQ_GLOBAL_EN), (xspi_handler->reg_base  + XSPI_IRTR_REG_OFFSET));

  //printf("send direct command\n");
  if(xspi_handler->cpu_access){
    // if case can not pass, please try to remaincount = 1 
    int remain_counts = cmd->transferSize;
    unsigned int i = 0;
    if(cmd->direction == XSPI_DATA_TRANS_DIR_READ){
      while(readl(base + 0x100) & 0x10);
      while(remain_counts){
        if(sizeof(uintptr_t) == 8){
          if(remain_counts >= 8){
            *((uint64_t *)(uintptr_t)(cmd->sysMemPtr + i)) = *((uint64_t *) (uintptr_t)(addr + cmd->transferAddr + i));
            i += 8;
            remain_counts -= 8;
            continue;
          }
        }

        if(remain_counts >= 4){
          *((uint32_t *)(uintptr_t)(cmd->sysMemPtr + i)) = *((uint32_t *)(uintptr_t) (addr + cmd->transferAddr + i));
          i += 4;
          remain_counts -= 4;
        }else{
          *((uint8_t *)(uintptr_t)(cmd->sysMemPtr + i)) = *((uint8_t *) (uintptr_t)(addr + cmd->transferAddr + i));
          i += 1;
          remain_counts -= 1;
        }
                
      }
    }else{
      while(remain_counts){
        if(sizeof(uintptr_t) == 8){
          if(remain_counts >= 8){
            *((uint32_t *)(uintptr_t) (addr + cmd->transferAddr + i)) = *((uint32_t *)(uintptr_t)(cmd->sysMemPtr + i)) ;
            i += 8;
            remain_counts -= 8;
            continue;
          }
        }

        if(remain_counts >= 4){
          *((uint32_t *)(uintptr_t)(addr + cmd->transferAddr + i)) = *((uint32_t *)(uintptr_t)(cmd->sysMemPtr + i)) ;
          i += 4;
          remain_counts -= 4;
        }else{
          *((uint8_t *) (uintptr_t)(addr + cmd->transferAddr + i)) = *((uint8_t *)(uintptr_t)(cmd->sysMemPtr + i)) ;
          i += 1;
          remain_counts -= 1;
        }
      }
    }
    return 0;
  }

  if (xSpiIf->sendDirectCommand(xSpiPd, directCmd) != 0) {
    printf("xspi send direct command failed!\n");
    return -1;
  }

  do {
    udelay(10);
  } while (xSpiIf->isDirectCmdEngBusy(xSpiPd));

  return 0;
}

int cdns_xspi_send_stig_command(XSPI_HandleTypeDef *xspi_handler,
                                XSPI_StigCommand *cmd) {
  XSPI_OBJ *xSpiIf          = xspi_handler->drv;
  XSPI_PrivateData *xSpiPd  = xspi_handler->pD;
  XSPI_StigCommand *stigCmd = cmd;
  XSPI_WorkMode work_mode;

  xSpiIf->getWorkMode(xSpiPd, &work_mode);
  if (work_mode != XSPI_WORK_MODE_STIG) {
    xSpiIf->setWorkMode(xSpiPd, XSPI_WORK_MODE_STIG);
  }
  
  // enable irq or dma
  writel((XSPI_IRQ_SDMA_TRIGGER|XSPI_IRQ_GLOBAL_EN), (xspi_handler->reg_base  + XSPI_IRTR_REG_OFFSET));
  if (xSpiIf->sendStigCommand(xSpiPd, stigCmd) != 0) {
    printf("xspi send stig command failed!\n");
    return 1;
  }

  do {
    xSpiIf->getStigStatus(xSpiPd, stigCmd);
  } while (stigCmd->statusInfo.status != XSPI_COMMAND_STATUS_SUCCESS);

  return stigCmd->statusInfo.status;
}

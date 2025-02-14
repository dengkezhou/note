/******************************************************************************
 *
 * Copyright (C) 2014-2023 Cadence Design Systems, Inc.
 * All rights reserved worldwide
 * The material contained herein is the proprietary and confidential
 * information of Cadence or its licensors, and is supplied subject to, and may
 * be used only by Cadence's customer in accordance with a previously executed
 * license and maintenance agreement between Cadence and that customer.
 *
 ******************************************************************************
 * edd_int.h
 * Private declarations for Ethernet DMA-MAC Driver
 *
 ***********************************************************************/
#ifndef EDD_INT_H
#define EDD_INT_H

#include "cedi_if.h"
#include "cedi_priv.h"
#include "cedi_structs_if.h"
#include "cedi_sanity.h"


/******************************************************************************
 * Private Constants
 *****************************************************************************/

#define GEM_GXL_MODULE_ID_V0    (0x0007U)
#define GEM_GXL_MODULE_ID_V1    (0x0107U)
#define GEM_GXL_MODULE_ID_V2    (0x000AU)
#define GEM_XL_MODULE_ID        (0x0008U)
#define GEM_AUTO_MODULE_ID_V0   (0x0207U)
#define GEM_AUTO_MODULE_ID_V1   (0x020AU)
#define GEM_10G_MODULE_ID_V0    (0x020CU)
#define GEM_10G_MODULE_ID_V1    (0x000CU)

#define XGM_GXL_MODULE_ID       (0x000BU)

#define OFFLOADS_GEM_GXL_REV    (0x0107U)

#define MAX_JUMBO_FRAME_LENGTH  (16383U)

#define MAX_PKT_BUF_SIZE	(16U)

/******************************************************************************
 * Local macros - assume pD is privateData parameter in function scope, and
 * cfg has been initialised with register base address
 *****************************************************************************/


/**
* Obtains register offset from base address of the emac_regs structure.
* REG_NAME_ is the name of the field from emac_regs structure.
*  e.g. spec_add1_bottom
*/
# define CEDI_RegOff(REG_NAME_) \
    (&((struct emac_regs*)0)->REG_NAME_)

/************************ Internal Driver objects ****************************/
extern volatile uint32_t* const transmitPtrReg[15];

/*********************** Internal Driver functions ***************************/
#endif /* multiple inclusion protection */

void getJumboFramesRx(const CEDI_PrivateData *pD, uint8_t *enable);
uint8_t IsGem1p09(const CEDI_PrivateData *pD);
uint8_t IsGem1p11(const CEDI_PrivateData *pD);
uint8_t IsGem1p12(const CEDI_PrivateData *pD);
uint8_t IsGem1p13(const CEDI_PrivateData *pD);
uint8_t IsEnstSupported(const CEDI_PrivateData *pD);
uint8_t IsSetMinIpgSupported(const CEDI_PrivateData *pD);
uint32_t subNsTsuInc24bSupport(const CEDI_PrivateData *pD);
void addRegBase(const CEDI_PrivateData *pD, volatile uint32_t **ptr);
uint32_t *uintptrToPtrU32(uintptr_t addr);
CEDI_RxDesc *rxDescAddrToPtr(uintptr_t descAddr);
void moveRxDescAddr(CEDI_RxDesc **ptr, int32_t offset);

/*
 * Check if function is supported according to GEMs version.
 * @param pD pointer to specific driver's PrivateData structure
 * @param IsGemVersion pointer to function which checks version
 * @param funcName name of function (to print in debug mode)
 * @return CDN_EOK if is supported
 * @return CDN_ENOTSUP if not supported
 */
uint32_t checkFunctionSupport(const CEDI_PrivateData* pD, uint8_t (*IsGemVersion)(const CEDI_PrivateData* pD), const char* funcName);

/* Check if Rx&Tx datapath for PCS25G is enabled
 * @param pD pointer to specific driver's PrivateData structure
 * @param funcName name of function (to print in debug mode)
 * @return 'true' is Rx or Tx datapath is enabled
 */
bool isPcs25gDatapathsEnabled(const CEDI_PrivateData* pD, const char* funcName);

/** Get pointer of qx_control register for given queue. */
volatile uint32_t* getQxControlRegAddr(const CEDI_PrivateData *pD, uint8_t queueNum);

/** Get pointer of qx_status register for given queue. */
volatile uint32_t* getQxStatusRegAddr(const CEDI_PrivateData *pD, uint8_t queueNum);

/* Check if PCS25G is supported
 * @param[in] cfg - pointer to driver configuration structure
 * @param[in] hwCfg - pointer to HW configuration
 * @return CDN_EOK if is supported
 * @return CDN_ENOSUP if PCS25G is not included into design or if high-speed interface
 * (%P_IFSP_SERDES) is not choosen
 */
uint32_t isPcs25gSupported(const CEDI_Config* cfg, const CEDI_DesignCfg* hwCfg);

/* Checks, if private data describes Express MAC
 * @param[in] pD pointer to PrivateData's structure
 * @return true if eMac
 * @return false if not eMac or eMac is not required by config
 */
bool checkIfEmac(const CEDI_PrivateData* pD, const char* funcName);
//***************************** edd_tx.c ************************************
uint32_t DoSetSegAlloc(CEDI_PrivateData *pD, const CEDI_SegmentsPerQueue *seqmentsPerQueue,
        uint8_t numOfQueues);

uint32_t DoGetSegAlloc(CEDI_PrivateData *pD, CEDI_SegmentsPerQueue *seqmentsPerQueue,
        uint8_t numOfQueues);

uint32_t getAllSegAlloctCount(const CEDI_PrivateData *pD, uint32_t *numberOfSegments);
uint32_t getTxQueueNum(const CEDI_PrivateData *pD, uint8_t *numQueues);

//***************************** edd_rx.c ************************************
void setTxQueueDisableBit(CEDI_PrivateData *pD, uint8_t queue,
             uint8_t disable);

void setRxQueueDisableBit(CEDI_PrivateData *pD, uint8_t queue,
             uint8_t disable);


// find start addresses for given rx queue
uint32_t findQBaseAddr(const CEDI_PrivateData* pD, uint8_t queueNum, CEDI_RxQueue* rxQ, uint32_t* pAddr,
        uintptr_t* vAddr);

